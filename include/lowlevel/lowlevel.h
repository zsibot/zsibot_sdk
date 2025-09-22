#ifndef _ROBOT_LOWLEVEL_INTERFACE_H_
#define _ROBOT_LOWLEVEL_INTERFACE_H_

#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

    enum
    {
        CONSUMER_CONTROL,
        CONSUMER_OTHER,
        CONSUMER_MAX,
    };

    // leg index
    enum
    {
        LEG_FRONT_RIGHT = 0,
        LEG_FRONT_LEFT = 1,
        LEG_BACK_RIGHT = 2,
        LEG_BACK_LEFT = 3,
        LEG_MAX,
    };

    typedef struct joint_control_def
    {
        float p_des; // rad
        float v_des; // rad/s
        float kp;
        float kd;
        float t_ff; // n*m
    } __attribute__((packed)) joint_control_t,
        *joint_control_p;

    typedef struct leg_control_def
    {
        joint_control_t abad;
        joint_control_t hip;
        joint_control_t knee;
        joint_control_t foot;
        int32_t flags; // allways set to 1
    } __attribute__((packed)) leg_control_t,
        *leg_control_p;

    typedef struct spi_command_def
    {
        leg_control_t legs[LEG_MAX];
        uint32_t consumer_flags[CONSUMER_MAX];
    } __attribute__((packed)) spline_cmd_data_t,
        *spline_cmd_data_p;

    typedef struct joint_state_def
    {
        /**
         * bit23-bit16: voltage(0 ~ 255V)
         * bit15-bit8: temperature(-40 ~ 215℃)
         * bit7: reserved
         * bit6: reserved
         * bit5: dual coding fault
         * bit4: overspeed fault
         * bit3: over temperature fault
         * bit2: overcurrent fault
         * bit1: overvoltage fault
         * bit0: motor enable flag
         */
        int32_t flags;
        float p; // rad
        float v; // rad/s
        float t; // n*m
    } __attribute__((packed)) joint_state_t,
        *joint_state_p;

    typedef struct leg_state_def
    {
        joint_state_t abad;
        joint_state_t hip;
        joint_state_t knee;
        joint_state_t foot;
    } __attribute__((packed)) leg_state_t,
        *leg_state_p;

    typedef struct spline_state_def
    {
        leg_state_t legs[LEG_MAX];
        uint32_t consumer_flags[CONSUMER_MAX];
    } __attribute__((packed)) spline_state_data_t,
        *spline_state_data_p;

    /**
     * SPLINE DAEMON handles motor communication every 1 ms via shared memory(SHM).
     * 
     * Roles:
     * - consumes motor control commands.
     * - produces motor status data for other modules.
     *
     * Consumer flag semantics:
     * - producers set `consumer_flags[...]`; consumers clear them.
     * - `CONSUMER_CONTROL` indexes the motion control flag.
     * - `CONSUMER_OTHER` indexes the flags for other modules.
     *
     * Control path (1 ms cadence):
     * - if `spline_cmd_data_p->consumer_flags[CONSUMER_CONTROL] != 0`,
     *   transmit `spline_cmd_data_p->legs` to the motor and reset the flag.
     * - otherwise resend the previous control frame; after repeated misses
     *   (≈10 cycles) clear the motor control command.
     *
     * State path (1 ms cadence):
     * - update `spline_state_data_t->legs` and set
     *   `spline_state_data_t->consumer_flags[0..CONSUMER_MAX - 1]`.
     * - motion control reads `consumer_flags[CONSUMER_CONTROL]`; zero means
     *   motor status is unavailable and SPLINE may be hung after a timeout.
     * - middleware modules use `consumer_flags[CONSUMER_OTHER]` similarly.
     */
    typedef struct spline_data_def
    {
        spline_cmd_data_t cmd;
        spline_state_data_t state;
    } __attribute__((packed)) spline_data_t,
        *spline_data_p;

    static inline spline_data_p create_spline_shm(void)
    {
        const char *SHM_PATH = "/spline_shm";
        const size_t SHM_SIZE = (1024 * 10);

        int shm_fd = shm_open(SHM_PATH, O_CREAT | O_RDWR, 0666);
        if (shm_fd == -1)
        {
            perror("spline shm_open.");
            exit(1);
        }
        if (ftruncate(shm_fd, SHM_SIZE) == -1)
        {
            perror("spline ftruncate");
            exit(1);
        }
        void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (shm_ptr == MAP_FAILED)
        {
            perror("spline mmap");
            exit(1);
        }
        close(shm_fd);
        return (spline_data_p)shm_ptr;
    }

    static inline void destroy_spline_shm(spline_data_p ptr)
    {
        // don't need to unlink and unmap.
    }

    typedef struct nav_imu_def
    {
        size_t timestamp; // NanoSeconds
        float acc[3];     // m/s^2
        float gyro[3];    // rad/s
        float q[4];       // w, x, y, z ,rotation order zyx
    } __attribute__((packed)) nav_imu_t,
        *nav_imu_p;

    static inline nav_imu_p create_imu_shm(void)
    {
        const char *SHM_PATH = "/imu_shm";
        const size_t SHM_SIZE = (1024 * 1);
        int shm_fd = shm_open(SHM_PATH, O_CREAT | O_RDWR, 0666);
        if (shm_fd == -1)
        {
            perror("imu shm_open.");
            exit(1);
        }
        if (ftruncate(shm_fd, SHM_SIZE) == -1)
        {
            perror("imu ftruncate");
            exit(1);
        }
        void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (shm_ptr == MAP_FAILED)
        {
            perror("imu mmap");
            exit(1);
        }
        close(shm_fd);
        return (nav_imu_p)shm_ptr;
    }

    static inline void destroy_imu_shm(nav_imu_p ptr)
    {
        // don't need to unlink and unmap.
    }

#ifdef __cplusplus
}
#endif

#endif
