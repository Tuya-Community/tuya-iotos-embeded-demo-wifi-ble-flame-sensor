/**
 * @File: tuya_flame.c 
 * @Author: shiliu.yang@tuya.com 
 * @Last Modified time: 2021-01-05 
 * @Description: flame detection demo 
 */

#include "tuya_dp_process.h"
#include "tuya_flame.h"
#include "tuya_iot_com_api.h"
#include "uni_log.h"

#include "FreeRTOS.h"
#include "task.h"
#include "uni_thread.h"


VOID check_flame_task(VOID);

VOID flame_sensor_init(VOID)
{
    tuya_gpio_inout_set(FLAME_SENSOR_PIN, TRUE);

    tuya_hal_thread_create(NULL, "check_flame", 512, TRD_PRIO_2, check_flame_task, NULL);
}

VOID check_flame_task(VOID)
{
    while (1) {
        if (FALSE == tuya_gpio_read(FLAME_SENSOR_PIN)) {
            flame_sensor_status.flame_sta = flame_alarm;
        } else {
            flame_sensor_status.flame_sta = normal;
        }
        updata_dp_all();
        tuya_hal_system_sleep(1000);
    }
}

