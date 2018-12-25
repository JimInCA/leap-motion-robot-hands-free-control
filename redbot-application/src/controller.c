/******************************************************************************\
 * Copyright (C) 2019 Jim Newman. All rights reserved.                        *
\******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>

#include "LeapC.h"
#include "connection.h"

#define ANGLE_MAX (float)(60.0)
#define MOTOR_MAX (float)(256.0)
#define GAIN (float)(MOTOR_MAX/ANGLE_MAX)
#define DEAD_ZONE (float)(10.0)

static const float RAD_TO_DEG = 57.295779513f;
int64_t lastFrameID = 0; //The last frame received

HANDLE uart;

float inline get_pitch(LEAP_VECTOR *vec)
{
    return (atan2f(vec->y, -(vec->z)) * RAD_TO_DEG);
}

float inline get_yaw(LEAP_VECTOR *vec)
{
    return (atan2f(vec->x, -(vec->z)) * RAD_TO_DEG);
}

float inline get_roll(LEAP_VECTOR *vec)
{
    return (atan2f(vec->x, -(vec->y)) * RAD_TO_DEG);
}

int16_t init_uart(uint8_t *serial_port, uint32_t baud)
{
    COMMTIMEOUTS timeouts;

    timeouts.ReadIntervalTimeout = 20;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.ReadTotalTimeoutConstant = 100;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 100;

    uart = CreateFile(serial_port,
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        0);

    if (uart == INVALID_HANDLE_VALUE)
    {
        DWORD err = GetLastError();
        printf("Failed to connet to UART on port %s.  Error code: %x\n", serial_port, err);
        return 1;
    }
    else
    {
        printf("Successfully connected to UART on port %s at baud rate %d.\n", serial_port, baud);
    }

    if (!SetCommTimeouts(uart, &timeouts))
        printf("Error setting time-outs.\n");

    DCB dcb = { 0 };

    if (!GetCommState(uart, &dcb))
        printf("Error getting current DCB settings.\n");
    else
        printf("DCB is ready for use.\n");

    FillMemory(&dcb, sizeof(dcb), 0);
    if (!GetCommState(uart, &dcb))     // get current DCB
    {
        printf("Error in GetCommState.\n");
        return 1;
    }

    // Update DCB rate.
    dcb.BaudRate = baud;

    // Set new state.
    if (!SetCommState(uart, &dcb))
    {
        printf("Error in SetCommState. Possibly a problem with the communications,\n");
        printf("port handle, or a problem with the DCB structure itself.\n");
        return 1;
    }

    return 0;
}


int main(int argc, char** argv)
{
    uint8_t str[128];
    uint32_t num_written;
    float pitch, roll;

    // set default serial port and baud rate
    uint8_t *port = "COM4";
    uint32_t baud = 115200;

    // simple command line parser
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-p") == 0)
        {
            port = argv[++i];
        }
        else if (strcmp(argv[i], "-b") == 0)
        {
            baud = atoi(argv[++i]);
        }
    }

    if (init_uart(port, baud) != 0)
        return 1;

    OpenConnection();
    while(!IsConnected)
        millisleep(100); //wait a bit to let the connection complete

    printf("Successfully connected to Leap Motion Controller.\n");
    LEAP_DEVICE_INFO* deviceProps = GetDeviceProperties();
    if(deviceProps)
        printf("Using device %s.\n", deviceProps->serial);
    fflush(stdout);

    while(1)
    {
        LEAP_TRACKING_EVENT *frame = GetFrame();
        if(frame && (frame->tracking_frame_id > lastFrameID))
        {
            lastFrameID = frame->tracking_frame_id;
            for(uint32_t h = 0; h < frame->nHands; h++)
            {
                LEAP_HAND* hand = &frame->pHands[h];
                LEAP_VECTOR* vector = &hand->palm.normal;
                if (hand->type == eLeapHandType_Left)
                {
                    // pitch will be used for throttle
                    pitch = get_pitch(vector) + (float)90.0;
                    if (fabsf(pitch) < DEAD_ZONE)
                        pitch = (float)0.0;
                    else if (fabsf(pitch) > ANGLE_MAX)
                        pitch = pitch > (float)0.0 ? ANGLE_MAX : -1.f * ANGLE_MAX;
                    pitch *= GAIN;
                    // roll will be used for turning
                    roll = get_roll(vector);
                    if (fabsf(roll) < DEAD_ZONE)
                        roll = (float)0.0;
                    else if (fabsf(roll) > ANGLE_MAX)
                        roll = roll > (float)0.0 ? ANGLE_MAX : -1.f * ANGLE_MAX;
                    roll *= GAIN * (float)0.5;
                    // calculate values for left and right motors
                    int32_t left_motor = (int32_t)(pitch - roll);
                    int32_t right_motor = (int32_t)(-1.f * (pitch + roll));
                    sprintf(str, "%8d %8d\r\n", left_motor, right_motor);
                    if (!WriteFile(uart, str, (DWORD)strlen(str), &num_written, NULL))
                    {
                        if (GetLastError() != ERROR_IO_PENDING)
                            printf("UART failed to write.");
                    }
                }
            }
        }
    } //ctrl-c to exit

    CloseHandle(uart);

    return 0;
}
