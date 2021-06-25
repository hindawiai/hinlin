<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/linux/mfd/wm831x/pdata.h -- Platक्रमm data क्रम WM831x
 *
 * Copyright 2009 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित __MFD_WM831X_PDATA_H__
#घोषणा __MFD_WM831X_PDATA_H__

काष्ठा wm831x;
काष्ठा regulator_init_data;

काष्ठा wm831x_backlight_pdata अणु
	पूर्णांक isink;     /** ISINK to use, 1 or 2 */
	पूर्णांक max_uA;    /** Maximum current to allow */
पूर्ण;

काष्ठा wm831x_backup_pdata अणु
	पूर्णांक अक्षरger_enable;
	पूर्णांक no_स्थिरant_voltage;  /** Disable स्थिरant voltage अक्षरging */
	पूर्णांक vlim;   /** Voltage limit in millivolts */
	पूर्णांक ilim;   /** Current limit in microamps */
पूर्ण;

काष्ठा wm831x_battery_pdata अणु
	पूर्णांक enable;         /** Enable अक्षरging */
	पूर्णांक fast_enable;    /** Enable fast अक्षरging */
	पूर्णांक off_mask;       /** Mask OFF जबतक अक्षरging */
	पूर्णांक trickle_ilim;   /** Trickle अक्षरge current limit, in mA */
	पूर्णांक vsel;           /** Target voltage, in mV */
	पूर्णांक eoc_iterm;      /** End of trickle अक्षरge current, in mA */
	पूर्णांक fast_ilim;      /** Fast अक्षरge current limit, in mA */
	पूर्णांक समयout;        /** Charge cycle समयout, in minutes */
पूर्ण;

/**
 * Configuration क्रम the WM831x DC-DC BuckWise convertors.  This
 * should be passed as driver_data in the regulator_init_data.
 *
 * Currently all the configuration is क्रम the fast DVS चयनing
 * support of the devices.  This allows MFPs on the device to be
 * configured as an input to चयन between two output voltages,
 * allowing voltage transitions without the expense of an access over
 * I2C or SPI buses.
 */
काष्ठा wm831x_buckv_pdata अणु
	पूर्णांक dvs_control_src; /** Hardware DVS source to use (1 or 2) */
	पूर्णांक dvs_init_state;  /** DVS state to expect on startup */
	पूर्णांक dvs_state_gpio;  /** CPU GPIO to use क्रम monitoring status */
पूर्ण;

/* Sources क्रम status LED configuration.  Values are रेजिस्टर values
 * plus 1 to allow क्रम a zero शेष क्रम preserve.
 */
क्रमागत wm831x_status_src अणु
	WM831X_STATUS_PRESERVE = 0,  /* Keep the current hardware setting */
	WM831X_STATUS_OTP = 1,
	WM831X_STATUS_POWER = 2,
	WM831X_STATUS_CHARGER = 3,
	WM831X_STATUS_MANUAL = 4,
पूर्ण;

काष्ठा wm831x_status_pdata अणु
	क्रमागत wm831x_status_src शेष_src;
	स्थिर अक्षर *name;
	स्थिर अक्षर *शेष_trigger;
पूर्ण;

काष्ठा wm831x_touch_pdata अणु
	पूर्णांक fivewire;          /** 1 क्रम five wire mode, 0 क्रम 4 wire */
	पूर्णांक isel;              /** Current क्रम pen करोwn (uA) */
	पूर्णांक rpu;               /** Pen करोwn sensitivity resistor भागider */
	पूर्णांक pressure;          /** Report pressure (boolean) */
	अचिन्हित पूर्णांक data_irq; /** Touch data पढ़ोy IRQ */
	पूर्णांक data_irqf;         /** IRQ flags क्रम data पढ़ोy IRQ */
	अचिन्हित पूर्णांक pd_irq;   /** Touch penकरोwn detect IRQ */
	पूर्णांक pd_irqf;           /** IRQ flags क्रम pen करोwn IRQ */
पूर्ण;

क्रमागत wm831x_watchकरोg_action अणु
	WM831X_WDOG_NONE = 0,
	WM831X_WDOG_INTERRUPT = 1,
	WM831X_WDOG_RESET = 2,
	WM831X_WDOG_WAKE = 3,
पूर्ण;

काष्ठा wm831x_watchकरोg_pdata अणु
	क्रमागत wm831x_watchकरोg_action primary, secondary;
	अचिन्हित पूर्णांक software:1;
पूर्ण;

#घोषणा WM831X_MAX_STATUS 2
#घोषणा WM831X_MAX_DCDC   4
#घोषणा WM831X_MAX_EPE    2
#घोषणा WM831X_MAX_LDO    11
#घोषणा WM831X_MAX_ISINK  2

#घोषणा WM831X_GPIO_CONFIGURE 0x10000
#घोषणा WM831X_GPIO_NUM 16

काष्ठा wm831x_pdata अणु
	/** Used to distinguish multiple WM831x chips */
	पूर्णांक wm831x_num;

	/** Called beक्रमe subdevices are set up */
	पूर्णांक (*pre_init)(काष्ठा wm831x *wm831x);
	/** Called after subdevices are set up */
	पूर्णांक (*post_init)(काष्ठा wm831x *wm831x);

	/** Put the /IRQ line पूर्णांकo CMOS mode */
	bool irq_cmos;

	/** Disable the touchscreen */
	bool disable_touch;

	/** The driver should initiate a घातer off sequence during shutकरोwn */
	bool soft_shutकरोwn;

	पूर्णांक irq_base;
	पूर्णांक gpio_base;
	पूर्णांक gpio_शेषs[WM831X_GPIO_NUM];
	काष्ठा wm831x_backlight_pdata *backlight;
	काष्ठा wm831x_backup_pdata *backup;
	काष्ठा wm831x_battery_pdata *battery;
	काष्ठा wm831x_touch_pdata *touch;
	काष्ठा wm831x_watchकरोg_pdata *watchकरोg;

	/** LED1 = 0 and so on */
	काष्ठा wm831x_status_pdata *status[WM831X_MAX_STATUS];
	/** DCDC1 = 0 and so on */
	काष्ठा regulator_init_data *dcdc[WM831X_MAX_DCDC];
	/** EPE1 = 0 and so on */
	काष्ठा regulator_init_data *epe[WM831X_MAX_EPE];
	/** LDO1 = 0 and so on */
	काष्ठा regulator_init_data *lकरो[WM831X_MAX_LDO];
	/** ISINK1 = 0 and so on*/
	काष्ठा regulator_init_data *isink[WM831X_MAX_ISINK];
पूर्ण;

#पूर्ण_अगर
