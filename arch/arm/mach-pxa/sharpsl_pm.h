<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * SharpSL Battery/PM Driver
 *
 * Copyright (c) 2004-2005 Riअक्षरd Purdie
 */
#अगर_अघोषित _MACH_SHARPSL_PM
#घोषणा _MACH_SHARPSL_PM

काष्ठा sharpsl_अक्षरger_machinfo अणु
	व्योम (*init)(व्योम);
	व्योम (*निकास)(व्योम);
	पूर्णांक gpio_acin;
	पूर्णांक gpio_batfull;
	पूर्णांक batfull_irq;
	पूर्णांक gpio_batlock;
	पूर्णांक gpio_fatal;
	व्योम (*disअक्षरge)(पूर्णांक);
	व्योम (*disअक्षरge1)(पूर्णांक);
	व्योम (*अक्षरge)(पूर्णांक);
	व्योम (*measure_temp)(पूर्णांक);
	व्योम (*presuspend)(व्योम);
	व्योम (*postsuspend)(व्योम);
	व्योम (*earlyresume)(व्योम);
	अचिन्हित दीर्घ (*पढ़ो_devdata)(पूर्णांक);
#घोषणा SHARPSL_BATT_VOLT       1
#घोषणा SHARPSL_BATT_TEMP       2
#घोषणा SHARPSL_ACIN_VOLT       3
#घोषणा SHARPSL_STATUS_ACIN     4
#घोषणा SHARPSL_STATUS_LOCK     5
#घोषणा SHARPSL_STATUS_CHRGFULL 6
#घोषणा SHARPSL_STATUS_FATAL    7
	bool (*अक्षरger_wakeup)(व्योम);
	पूर्णांक (*should_wakeup)(अचिन्हित पूर्णांक resume_on_alarm);
	व्योम (*backlight_limit)(पूर्णांक);
	पूर्णांक (*backlight_get_status) (व्योम);
	पूर्णांक अक्षरge_on_volt;
	पूर्णांक अक्षरge_on_temp;
	पूर्णांक अक्षरge_acin_high;
	पूर्णांक अक्षरge_acin_low;
	पूर्णांक fatal_acin_volt;
	पूर्णांक fatal_noacin_volt;
	पूर्णांक bat_levels;
	काष्ठा battery_thresh *bat_levels_noac;
	काष्ठा battery_thresh *bat_levels_acin;
	काष्ठा battery_thresh *bat_levels_noac_bl;
	काष्ठा battery_thresh *bat_levels_acin_bl;
	पूर्णांक status_high_acin;
	पूर्णांक status_low_acin;
	पूर्णांक status_high_noac;
	पूर्णांक status_low_noac;
पूर्ण;

काष्ठा battery_thresh अणु
	पूर्णांक voltage;
	पूर्णांक percentage;
पूर्ण;

काष्ठा battery_stat अणु
	पूर्णांक ac_status;         /* APM AC Present/Not Present */
	पूर्णांक मुख्यbat_status;    /* APM Main Battery Status */
	पूर्णांक मुख्यbat_percent;   /* Main Battery Percentage Charge */
	पूर्णांक मुख्यbat_voltage;   /* Main Battery Voltage */
पूर्ण;

काष्ठा sharpsl_pm_status अणु
	काष्ठा device *dev;
	काष्ठा समयr_list ac_समयr;
	काष्ठा समयr_list chrg_full_समयr;

	पूर्णांक अक्षरge_mode;
#घोषणा CHRG_ERROR    (-1)
#घोषणा CHRG_OFF      (0)
#घोषणा CHRG_ON       (1)
#घोषणा CHRG_DONE     (2)

	अचिन्हित पूर्णांक flags;
#घोषणा SHARPSL_SUSPENDED       (1 << 0)  /* Device is Suspended */
#घोषणा SHARPSL_ALARM_ACTIVE    (1 << 1)  /* Alarm is क्रम अक्षरging event (not user) */
#घोषणा SHARPSL_BL_LIMIT        (1 << 2)  /* Backlight Intensity Limited */
#घोषणा SHARPSL_APM_QUEUED      (1 << 3)  /* APM Event Queued */
#घोषणा SHARPSL_DO_OFFLINE_CHRG (1 << 4)  /* Trigger the offline अक्षरger */

	पूर्णांक full_count;
	अचिन्हित दीर्घ अक्षरge_start_समय;
	काष्ठा sharpsl_अक्षरger_machinfo *machinfo;
	काष्ठा battery_stat battstat;
पूर्ण;

बाह्य काष्ठा sharpsl_pm_status sharpsl_pm;

बाह्य काष्ठा battery_thresh sharpsl_battery_levels_acin[];
बाह्य काष्ठा battery_thresh sharpsl_battery_levels_noac[];

#घोषणा SHARPSL_LED_ERROR  2
#घोषणा SHARPSL_LED_ON     1
#घोषणा SHARPSL_LED_OFF    0

व्योम sharpsl_battery_kick(व्योम);
व्योम sharpsl_pm_led(पूर्णांक val);

/* MAX1111 Channel Definitions */
#घोषणा MAX1111_BATT_VOLT   4u
#घोषणा MAX1111_BATT_TEMP   2u
#घोषणा MAX1111_ACIN_VOLT   6u
पूर्णांक sharpsl_pm_pxa_पढ़ो_max1111(पूर्णांक channel);

व्योम corgi_lcd_limit_पूर्णांकensity(पूर्णांक limit);
#पूर्ण_अगर
