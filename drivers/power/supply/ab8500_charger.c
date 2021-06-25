<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2012
 *
 * Charger driver क्रम AB8500
 *
 * Author:
 *	Johan Palsson <johan.palsson@stericsson.com>
 *	Karl Komierowski <karl.komierowski@stericsson.com>
 *	Arun R Murthy <arun.murthy@stericsson.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/completion.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kobject.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/mutex.h>
#समावेश <linux/iio/consumer.h>

#समावेश "ab8500-bm.h"
#समावेश "ab8500-chargalg.h"

/* Charger स्थिरants */
#घोषणा NO_PW_CONN			0
#घोषणा AC_PW_CONN			1
#घोषणा USB_PW_CONN			2

#घोषणा MAIN_WDOG_ENA			0x01
#घोषणा MAIN_WDOG_KICK			0x02
#घोषणा MAIN_WDOG_DIS			0x00
#घोषणा CHARG_WD_KICK			0x01
#घोषणा MAIN_CH_ENA			0x01
#घोषणा MAIN_CH_NO_OVERSHOOT_ENA_N	0x02
#घोषणा USB_CH_ENA			0x01
#घोषणा USB_CHG_NO_OVERSHOOT_ENA_N	0x02
#घोषणा MAIN_CH_DET			0x01
#घोषणा MAIN_CH_CV_ON			0x04
#घोषणा USB_CH_CV_ON			0x08
#घोषणा VBUS_DET_DBNC100		0x02
#घोषणा VBUS_DET_DBNC1			0x01
#घोषणा OTP_ENABLE_WD			0x01
#घोषणा DROP_COUNT_RESET		0x01
#घोषणा USB_CH_DET			0x01

#घोषणा MAIN_CH_INPUT_CURR_SHIFT	4
#घोषणा VBUS_IN_CURR_LIM_SHIFT		4
#घोषणा AUTO_VBUS_IN_CURR_LIM_SHIFT	4
#घोषणा VBUS_IN_CURR_LIM_RETRY_SET_TIME	30 /* seconds */

#घोषणा LED_INDICATOR_PWM_ENA		0x01
#घोषणा LED_INDICATOR_PWM_DIS		0x00
#घोषणा LED_IND_CUR_5MA			0x04
#घोषणा LED_INDICATOR_PWM_DUTY_252_256	0xBF

/* HW failure स्थिरants */
#घोषणा MAIN_CH_TH_PROT			0x02
#घोषणा VBUS_CH_NOK			0x08
#घोषणा USB_CH_TH_PROT			0x02
#घोषणा VBUS_OVV_TH			0x01
#घोषणा MAIN_CH_NOK			0x01
#घोषणा VBUS_DET			0x80

#घोषणा MAIN_CH_STATUS2_MAINCHGDROP		0x80
#घोषणा MAIN_CH_STATUS2_MAINCHARGERDETDBNC	0x40
#घोषणा USB_CH_VBUSDROP				0x40
#घोषणा USB_CH_VBUSDETDBNC			0x01

/* UsbLineStatus रेजिस्टर bit masks */
#घोषणा AB8500_USB_LINK_STATUS		0x78
#घोषणा AB8505_USB_LINK_STATUS		0xF8
#घोषणा AB8500_STD_HOST_SUSP		0x18
#घोषणा USB_LINK_STATUS_SHIFT		3

/* Watchकरोg समयout स्थिरant */
#घोषणा WD_TIMER			0x30 /* 4min */
#घोषणा WD_KICK_INTERVAL		(60 * HZ)

/* Lowest अक्षरger voltage is 3.39V -> 0x4E */
#घोषणा LOW_VOLT_REG			0x4E

/* Step up/करोwn delay in us */
#घोषणा STEP_UDELAY			1000

#घोषणा CHARGER_STATUS_POLL 10 /* in ms */

#घोषणा CHG_WD_INTERVAL			(60 * HZ)

#घोषणा AB8500_SW_CONTROL_FALLBACK	0x03
/* Wait क्रम क्रमागतeration beक्रमe अक्षरing in us */
#घोषणा WAIT_ACA_RID_ENUMERATION	(5 * 1000)
/*External अक्षरger control*/
#घोषणा AB8500_SYS_CHARGER_CONTROL_REG		0x52
#घोषणा EXTERNAL_CHARGER_DISABLE_REG_VAL	0x03
#घोषणा EXTERNAL_CHARGER_ENABLE_REG_VAL		0x07

/* UsbLineStatus रेजिस्टर - usb types */
क्रमागत ab8500_अक्षरger_link_status अणु
	USB_STAT_NOT_CONFIGURED,
	USB_STAT_STD_HOST_NC,
	USB_STAT_STD_HOST_C_NS,
	USB_STAT_STD_HOST_C_S,
	USB_STAT_HOST_CHG_NM,
	USB_STAT_HOST_CHG_HS,
	USB_STAT_HOST_CHG_HS_CHIRP,
	USB_STAT_DEDICATED_CHG,
	USB_STAT_ACA_RID_A,
	USB_STAT_ACA_RID_B,
	USB_STAT_ACA_RID_C_NM,
	USB_STAT_ACA_RID_C_HS,
	USB_STAT_ACA_RID_C_HS_CHIRP,
	USB_STAT_HM_IDGND,
	USB_STAT_RESERVED,
	USB_STAT_NOT_VALID_LINK,
	USB_STAT_PHY_EN,
	USB_STAT_SUP_NO_IDGND_VBUS,
	USB_STAT_SUP_IDGND_VBUS,
	USB_STAT_CHARGER_LINE_1,
	USB_STAT_CARKIT_1,
	USB_STAT_CARKIT_2,
	USB_STAT_ACA_DOCK_CHARGER,
पूर्ण;

क्रमागत ab8500_usb_state अणु
	AB8500_BM_USB_STATE_RESET_HS,	/* HighSpeed Reset */
	AB8500_BM_USB_STATE_RESET_FS,	/* FullSpeed/LowSpeed Reset */
	AB8500_BM_USB_STATE_CONFIGURED,
	AB8500_BM_USB_STATE_SUSPEND,
	AB8500_BM_USB_STATE_RESUME,
	AB8500_BM_USB_STATE_MAX,
पूर्ण;

/* VBUS input current limits supported in AB8500 in mA */
#घोषणा USB_CH_IP_CUR_LVL_0P05		50
#घोषणा USB_CH_IP_CUR_LVL_0P09		98
#घोषणा USB_CH_IP_CUR_LVL_0P19		193
#घोषणा USB_CH_IP_CUR_LVL_0P29		290
#घोषणा USB_CH_IP_CUR_LVL_0P38		380
#घोषणा USB_CH_IP_CUR_LVL_0P45		450
#घोषणा USB_CH_IP_CUR_LVL_0P5		500
#घोषणा USB_CH_IP_CUR_LVL_0P6		600
#घोषणा USB_CH_IP_CUR_LVL_0P7		700
#घोषणा USB_CH_IP_CUR_LVL_0P8		800
#घोषणा USB_CH_IP_CUR_LVL_0P9		900
#घोषणा USB_CH_IP_CUR_LVL_1P0		1000
#घोषणा USB_CH_IP_CUR_LVL_1P1		1100
#घोषणा USB_CH_IP_CUR_LVL_1P3		1300
#घोषणा USB_CH_IP_CUR_LVL_1P4		1400
#घोषणा USB_CH_IP_CUR_LVL_1P5		1500

#घोषणा VBAT_TRESH_IP_CUR_RED		3800

#घोषणा to_ab8500_अक्षरger_usb_device_info(x) container_of((x), \
	काष्ठा ab8500_अक्षरger, usb_chg)
#घोषणा to_ab8500_अक्षरger_ac_device_info(x) container_of((x), \
	काष्ठा ab8500_अक्षरger, ac_chg)

/**
 * काष्ठा ab8500_अक्षरger_पूर्णांकerrupts - ab8500 पूर्णांकerupts
 * @name:	name of the पूर्णांकerrupt
 * @isr		function poपूर्णांकer to the isr
 */
काष्ठा ab8500_अक्षरger_पूर्णांकerrupts अणु
	अक्षर *name;
	irqवापस_t (*isr)(पूर्णांक irq, व्योम *data);
पूर्ण;

काष्ठा ab8500_अक्षरger_info अणु
	पूर्णांक अक्षरger_connected;
	पूर्णांक अक्षरger_online;
	पूर्णांक अक्षरger_voltage;
	पूर्णांक cv_active;
	bool wd_expired;
	पूर्णांक अक्षरger_current;
पूर्ण;

काष्ठा ab8500_अक्षरger_event_flags अणु
	bool मुख्यextchnotok;
	bool मुख्य_thermal_prot;
	bool usb_thermal_prot;
	bool vbus_ovv;
	bool usbअक्षरgernotok;
	bool chgwdexp;
	bool vbus_collapse;
	bool vbus_drop_end;
पूर्ण;

काष्ठा ab8500_अक्षरger_usb_state अणु
	पूर्णांक usb_current;
	पूर्णांक usb_current_पंचांगp;
	क्रमागत ab8500_usb_state state;
	क्रमागत ab8500_usb_state state_पंचांगp;
	spinlock_t usb_lock;
पूर्ण;

काष्ठा ab8500_अक्षरger_max_usb_in_curr अणु
	पूर्णांक usb_type_max;
	पूर्णांक set_max;
	पूर्णांक calculated_max;
पूर्ण;

/**
 * काष्ठा ab8500_अक्षरger - ab8500 Charger device inक्रमmation
 * @dev:		Poपूर्णांकer to the काष्ठाure device
 * @vbus_detected:	VBUS detected
 * @vbus_detected_start:
 *			VBUS detected during startup
 * @ac_conn:		This will be true when the AC अक्षरger has been plugged
 * @vddadc_en_ac:	Indicate अगर VDD ADC supply is enabled because AC
 *			अक्षरger is enabled
 * @vddadc_en_usb:	Indicate अगर VDD ADC supply is enabled because USB
 *			अक्षरger is enabled
 * @vbat		Battery voltage
 * @old_vbat		Previously measured battery voltage
 * @usb_device_is_unrecognised	USB device is unrecognised by the hardware
 * @स्वतःघातer		Indicate अगर we should have स्वतःmatic pwron after pwrloss
 * @स्वतःघातer_cfg	platक्रमm specअगरic घातer config support क्रम "pwron after pwrloss"
 * @invalid_अक्षरger_detect_state State when क्रमcing AB to use invalid अक्षरger
 * @is_aca_rid:		Incicate अगर accessory is ACA type
 * @current_stepping_sessions:
 *			Counter क्रम current stepping sessions
 * @parent:		Poपूर्णांकer to the काष्ठा ab8500
 * @adc_मुख्य_अक्षरger_v	ADC channel क्रम मुख्य अक्षरger voltage
 * @adc_मुख्य_अक्षरger_c	ADC channel क्रम मुख्य अक्षरger current
 * @adc_vbus_v		ADC channel क्रम USB अक्षरger voltage
 * @adc_usb_अक्षरger_c	ADC channel क्रम USB अक्षरger current
 * @bm:           	Platक्रमm specअगरic battery management inक्रमmation
 * @flags:		Structure क्रम inक्रमmation about events triggered
 * @usb_state:		Structure क्रम usb stack inक्रमmation
 * @max_usb_in_curr:	Max USB अक्षरger input current
 * @ac_chg:		AC अक्षरger घातer supply
 * @usb_chg:		USB अक्षरger घातer supply
 * @ac:			Structure that holds the AC अक्षरger properties
 * @usb:		Structure that holds the USB अक्षरger properties
 * @regu:		Poपूर्णांकer to the काष्ठा regulator
 * @अक्षरger_wq:		Work queue क्रम the IRQs and checking HW state
 * @usb_ipt_crnt_lock:	Lock to protect VBUS input current setting from mutuals
 * @pm_lock:		Lock to prevent प्रणाली to suspend
 * @check_vbat_work	Work क्रम checking vbat threshold to adjust vbus current
 * @check_hw_failure_work:	Work क्रम checking HW state
 * @check_usbchgnotok_work:	Work क्रम checking USB अक्षरger not ok status
 * @kick_wd_work:		Work क्रम kicking the अक्षरger watchकरोg in हाल
 *				of ABB rev 1.* due to the watchog logic bug
 * @ac_अक्षरger_attached_work:	Work क्रम checking अगर AC अक्षरger is still
 *				connected
 * @usb_अक्षरger_attached_work:	Work क्रम checking अगर USB अक्षरger is still
 *				connected
 * @ac_work:			Work क्रम checking AC अक्षरger connection
 * @detect_usb_type_work:	Work क्रम detecting the USB type connected
 * @usb_link_status_work:	Work क्रम checking the new USB link status
 * @usb_state_changed_work:	Work क्रम checking USB state
 * @attach_work:		Work क्रम detecting USB type
 * @vbus_drop_end_work:		Work क्रम detecting VBUS drop end
 * @check_मुख्य_thermal_prot_work:
 *				Work क्रम checking Main thermal status
 * @check_usb_thermal_prot_work:
 *				Work क्रम checking USB thermal status
 * @अक्षरger_attached_mutex:	For controlling the wakelock
 */
काष्ठा ab8500_अक्षरger अणु
	काष्ठा device *dev;
	bool vbus_detected;
	bool vbus_detected_start;
	bool ac_conn;
	bool vddadc_en_ac;
	bool vddadc_en_usb;
	पूर्णांक vbat;
	पूर्णांक old_vbat;
	bool usb_device_is_unrecognised;
	bool स्वतःघातer;
	bool स्वतःघातer_cfg;
	पूर्णांक invalid_अक्षरger_detect_state;
	पूर्णांक is_aca_rid;
	atomic_t current_stepping_sessions;
	काष्ठा ab8500 *parent;
	काष्ठा iio_channel *adc_मुख्य_अक्षरger_v;
	काष्ठा iio_channel *adc_मुख्य_अक्षरger_c;
	काष्ठा iio_channel *adc_vbus_v;
	काष्ठा iio_channel *adc_usb_अक्षरger_c;
	काष्ठा abx500_bm_data *bm;
	काष्ठा ab8500_अक्षरger_event_flags flags;
	काष्ठा ab8500_अक्षरger_usb_state usb_state;
	काष्ठा ab8500_अक्षरger_max_usb_in_curr max_usb_in_curr;
	काष्ठा ux500_अक्षरger ac_chg;
	काष्ठा ux500_अक्षरger usb_chg;
	काष्ठा ab8500_अक्षरger_info ac;
	काष्ठा ab8500_अक्षरger_info usb;
	काष्ठा regulator *regu;
	काष्ठा workqueue_काष्ठा *अक्षरger_wq;
	काष्ठा mutex usb_ipt_crnt_lock;
	काष्ठा delayed_work check_vbat_work;
	काष्ठा delayed_work check_hw_failure_work;
	काष्ठा delayed_work check_usbchgnotok_work;
	काष्ठा delayed_work kick_wd_work;
	काष्ठा delayed_work usb_state_changed_work;
	काष्ठा delayed_work attach_work;
	काष्ठा delayed_work ac_अक्षरger_attached_work;
	काष्ठा delayed_work usb_अक्षरger_attached_work;
	काष्ठा delayed_work vbus_drop_end_work;
	काष्ठा work_काष्ठा ac_work;
	काष्ठा work_काष्ठा detect_usb_type_work;
	काष्ठा work_काष्ठा usb_link_status_work;
	काष्ठा work_काष्ठा check_मुख्य_thermal_prot_work;
	काष्ठा work_काष्ठा check_usb_thermal_prot_work;
	काष्ठा usb_phy *usb_phy;
	काष्ठा notअगरier_block nb;
	काष्ठा mutex अक्षरger_attached_mutex;
पूर्ण;

/* AC properties */
अटल क्रमागत घातer_supply_property ab8500_अक्षरger_ac_props[] = अणु
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
	POWER_SUPPLY_PROP_CURRENT_NOW,
पूर्ण;

/* USB properties */
अटल क्रमागत घातer_supply_property ab8500_अक्षरger_usb_props[] = अणु
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
	POWER_SUPPLY_PROP_CURRENT_NOW,
पूर्ण;

/*
 * Function क्रम enabling and disabling sw fallback mode
 * should always be disabled when no अक्षरger is connected.
 */
अटल व्योम ab8500_enable_disable_sw_fallback(काष्ठा ab8500_अक्षरger *di,
		bool fallback)
अणु
	u8 val;
	u8 reg;
	u8 bank;
	u8 bit;
	पूर्णांक ret;

	dev_dbg(di->dev, "SW Fallback: %d\n", fallback);

	अगर (is_ab8500(di->parent)) अणु
		bank = 0x15;
		reg = 0x0;
		bit = 3;
	पूर्ण अन्यथा अणु
		bank = AB8500_SYS_CTRL1_BLOCK;
		reg = AB8500_SW_CONTROL_FALLBACK;
		bit = 0;
	पूर्ण

	/* पढ़ो the रेजिस्टर containing fallback bit */
	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, bank, reg, &val);
	अगर (ret < 0) अणु
		dev_err(di->dev, "%d read failed\n", __LINE__);
		वापस;
	पूर्ण

	अगर (is_ab8500(di->parent)) अणु
		/* enable the OPT emulation रेजिस्टरs */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, 0x11, 0x00, 0x2);
		अगर (ret) अणु
			dev_err(di->dev, "%d write failed\n", __LINE__);
			जाओ disable_otp;
		पूर्ण
	पूर्ण

	अगर (fallback)
		val |= (1 << bit);
	अन्यथा
		val &= ~(1 << bit);

	/* ग_लिखो back the changed fallback bit value to रेजिस्टर */
	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, bank, reg, val);
	अगर (ret) अणु
		dev_err(di->dev, "%d write failed\n", __LINE__);
	पूर्ण

disable_otp:
	अगर (is_ab8500(di->parent)) अणु
		/* disable the set OTP रेजिस्टरs again */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, 0x11, 0x00, 0x0);
		अगर (ret) अणु
			dev_err(di->dev, "%d write failed\n", __LINE__);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ab8500_घातer_supply_changed - a wrapper with local extensions क्रम
 * घातer_supply_changed
 * @di:	  poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 * @psy:  poपूर्णांकer to घातer_supply_that have changed.
 *
 */
अटल व्योम ab8500_घातer_supply_changed(काष्ठा ab8500_अक्षरger *di,
					काष्ठा घातer_supply *psy)
अणु
	अगर (di->स्वतःघातer_cfg) अणु
		अगर (!di->usb.अक्षरger_connected &&
		    !di->ac.अक्षरger_connected &&
		    di->स्वतःघातer) अणु
			di->स्वतःघातer = false;
			ab8500_enable_disable_sw_fallback(di, false);
		पूर्ण अन्यथा अगर (!di->स्वतःघातer &&
			   (di->ac.अक्षरger_connected ||
			    di->usb.अक्षरger_connected)) अणु
			di->स्वतःघातer = true;
			ab8500_enable_disable_sw_fallback(di, true);
		पूर्ण
	पूर्ण
	घातer_supply_changed(psy);
पूर्ण

अटल व्योम ab8500_अक्षरger_set_usb_connected(काष्ठा ab8500_अक्षरger *di,
	bool connected)
अणु
	अगर (connected != di->usb.अक्षरger_connected) अणु
		dev_dbg(di->dev, "USB connected:%i\n", connected);
		di->usb.अक्षरger_connected = connected;

		अगर (!connected)
			di->flags.vbus_drop_end = false;

		sysfs_notअगरy(&di->usb_chg.psy->dev.kobj, शून्य, "present");

		अगर (connected) अणु
			mutex_lock(&di->अक्षरger_attached_mutex);
			mutex_unlock(&di->अक्षरger_attached_mutex);

			अगर (is_ab8500(di->parent))
				queue_delayed_work(di->अक्षरger_wq,
					   &di->usb_अक्षरger_attached_work,
					   HZ);
		पूर्ण अन्यथा अणु
			cancel_delayed_work_sync(&di->usb_अक्षरger_attached_work);
			mutex_lock(&di->अक्षरger_attached_mutex);
			mutex_unlock(&di->अक्षरger_attached_mutex);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ab8500_अक्षरger_get_ac_voltage() - get ac अक्षरger voltage
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns ac अक्षरger voltage (on success)
 */
अटल पूर्णांक ab8500_अक्षरger_get_ac_voltage(काष्ठा ab8500_अक्षरger *di)
अणु
	पूर्णांक vch, ret;

	/* Only measure voltage अगर the अक्षरger is connected */
	अगर (di->ac.अक्षरger_connected) अणु
		ret = iio_पढ़ो_channel_processed(di->adc_मुख्य_अक्षरger_v, &vch);
		अगर (ret < 0)
			dev_err(di->dev, "%s ADC conv failed,\n", __func__);
	पूर्ण अन्यथा अणु
		vch = 0;
	पूर्ण
	वापस vch;
पूर्ण

/**
 * ab8500_अक्षरger_ac_cv() - check अगर the मुख्य अक्षरger is in CV mode
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns ac अक्षरger CV mode (on success) अन्यथा error code
 */
अटल पूर्णांक ab8500_अक्षरger_ac_cv(काष्ठा ab8500_अक्षरger *di)
अणु
	u8 val;
	पूर्णांक ret = 0;

	/* Only check CV mode अगर the अक्षरger is online */
	अगर (di->ac.अक्षरger_online) अणु
		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
			AB8500_CH_STATUS1_REG, &val);
		अगर (ret < 0) अणु
			dev_err(di->dev, "%s ab8500 read failed\n", __func__);
			वापस 0;
		पूर्ण

		अगर (val & MAIN_CH_CV_ON)
			ret = 1;
		अन्यथा
			ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ab8500_अक्षरger_get_vbus_voltage() - get vbus voltage
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * This function वापसs the vbus voltage.
 * Returns vbus voltage (on success)
 */
अटल पूर्णांक ab8500_अक्षरger_get_vbus_voltage(काष्ठा ab8500_अक्षरger *di)
अणु
	पूर्णांक vch, ret;

	/* Only measure voltage अगर the अक्षरger is connected */
	अगर (di->usb.अक्षरger_connected) अणु
		ret = iio_पढ़ो_channel_processed(di->adc_vbus_v, &vch);
		अगर (ret < 0)
			dev_err(di->dev, "%s ADC conv failed,\n", __func__);
	पूर्ण अन्यथा अणु
		vch = 0;
	पूर्ण
	वापस vch;
पूर्ण

/**
 * ab8500_अक्षरger_get_usb_current() - get usb अक्षरger current
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * This function वापसs the usb अक्षरger current.
 * Returns usb current (on success) and error code on failure
 */
अटल पूर्णांक ab8500_अक्षरger_get_usb_current(काष्ठा ab8500_अक्षरger *di)
अणु
	पूर्णांक ich, ret;

	/* Only measure current अगर the अक्षरger is online */
	अगर (di->usb.अक्षरger_online) अणु
		ret = iio_पढ़ो_channel_processed(di->adc_usb_अक्षरger_c, &ich);
		अगर (ret < 0)
			dev_err(di->dev, "%s ADC conv failed,\n", __func__);
	पूर्ण अन्यथा अणु
		ich = 0;
	पूर्ण
	वापस ich;
पूर्ण

/**
 * ab8500_अक्षरger_get_ac_current() - get ac अक्षरger current
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * This function वापसs the ac अक्षरger current.
 * Returns ac current (on success) and error code on failure.
 */
अटल पूर्णांक ab8500_अक्षरger_get_ac_current(काष्ठा ab8500_अक्षरger *di)
अणु
	पूर्णांक ich, ret;

	/* Only measure current अगर the अक्षरger is online */
	अगर (di->ac.अक्षरger_online) अणु
		ret = iio_पढ़ो_channel_processed(di->adc_मुख्य_अक्षरger_c, &ich);
		अगर (ret < 0)
			dev_err(di->dev, "%s ADC conv failed,\n", __func__);
	पूर्ण अन्यथा अणु
		ich = 0;
	पूर्ण
	वापस ich;
पूर्ण

/**
 * ab8500_अक्षरger_usb_cv() - check अगर the usb अक्षरger is in CV mode
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns ac अक्षरger CV mode (on success) अन्यथा error code
 */
अटल पूर्णांक ab8500_अक्षरger_usb_cv(काष्ठा ab8500_अक्षरger *di)
अणु
	पूर्णांक ret;
	u8 val;

	/* Only check CV mode अगर the अक्षरger is online */
	अगर (di->usb.अक्षरger_online) अणु
		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
			AB8500_CH_USBCH_STAT1_REG, &val);
		अगर (ret < 0) अणु
			dev_err(di->dev, "%s ab8500 read failed\n", __func__);
			वापस 0;
		पूर्ण

		अगर (val & USB_CH_CV_ON)
			ret = 1;
		अन्यथा
			ret = 0;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ab8500_अक्षरger_detect_अक्षरgers() - Detect the connected अक्षरgers
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 * @probe:	अगर probe, करोn't delay and रुको क्रम HW
 *
 * Returns the type of अक्षरger connected.
 * For USB it will not mean we can actually अक्षरge from it
 * but that there is a USB cable connected that we have to
 * identअगरy. This is used during startup when we करोn't get
 * पूर्णांकerrupts of the अक्षरger detection
 *
 * Returns an पूर्णांकeger value, that means,
 * NO_PW_CONN  no घातer supply is connected
 * AC_PW_CONN  अगर the AC घातer supply is connected
 * USB_PW_CONN  अगर the USB घातer supply is connected
 * AC_PW_CONN + USB_PW_CONN अगर USB and AC घातer supplies are both connected
 */
अटल पूर्णांक ab8500_अक्षरger_detect_अक्षरgers(काष्ठा ab8500_अक्षरger *di, bool probe)
अणु
	पूर्णांक result = NO_PW_CONN;
	पूर्णांक ret;
	u8 val;

	/* Check क्रम AC अक्षरger */
	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
		AB8500_CH_STATUS1_REG, &val);
	अगर (ret < 0) अणु
		dev_err(di->dev, "%s ab8500 read failed\n", __func__);
		वापस ret;
	पूर्ण

	अगर (val & MAIN_CH_DET)
		result = AC_PW_CONN;

	/* Check क्रम USB अक्षरger */

	अगर (!probe) अणु
		/*
		 * AB8500 says VBUS_DET_DBNC1 & VBUS_DET_DBNC100
		 * when disconnecting ACA even though no
		 * अक्षरger was connected. Try रुकोing a little
		 * दीर्घer than the 100 ms of VBUS_DET_DBNC100...
		 */
		msleep(110);
	पूर्ण
	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
		AB8500_CH_USBCH_STAT1_REG, &val);
	अगर (ret < 0) अणु
		dev_err(di->dev, "%s ab8500 read failed\n", __func__);
		वापस ret;
	पूर्ण
	dev_dbg(di->dev,
		"%s AB8500_CH_USBCH_STAT1_REG %x\n", __func__,
		val);
	अगर ((val & VBUS_DET_DBNC1) && (val & VBUS_DET_DBNC100))
		result |= USB_PW_CONN;

	वापस result;
पूर्ण

/**
 * ab8500_अक्षरger_max_usb_curr() - get the max curr क्रम the USB type
 * @di:			poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 * @link_status:	the identअगरied USB type
 *
 * Get the maximum current that is allowed to be drawn from the host
 * based on the USB type.
 * Returns error code in हाल of failure अन्यथा 0 on success
 */
अटल पूर्णांक ab8500_अक्षरger_max_usb_curr(काष्ठा ab8500_अक्षरger *di,
		क्रमागत ab8500_अक्षरger_link_status link_status)
अणु
	पूर्णांक ret = 0;

	di->usb_device_is_unrecognised = false;

	/*
	 * Platक्रमm only supports USB 2.0.
	 * This means that अक्षरging current from USB source
	 * is maximum 500 mA. Every occurrence of USB_STAT_*_HOST_*
	 * should set USB_CH_IP_CUR_LVL_0P5.
	 */

	चयन (link_status) अणु
	हाल USB_STAT_STD_HOST_NC:
	हाल USB_STAT_STD_HOST_C_NS:
	हाल USB_STAT_STD_HOST_C_S:
		dev_dbg(di->dev, "USB Type - Standard host is "
			"detected through USB driver\n");
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		di->is_aca_rid = 0;
		अवरोध;
	हाल USB_STAT_HOST_CHG_HS_CHIRP:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		di->is_aca_rid = 0;
		अवरोध;
	हाल USB_STAT_HOST_CHG_HS:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		di->is_aca_rid = 0;
		अवरोध;
	हाल USB_STAT_ACA_RID_C_HS:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P9;
		di->is_aca_rid = 0;
		अवरोध;
	हाल USB_STAT_ACA_RID_A:
		/*
		 * Dedicated अक्षरger level minus maximum current accessory
		 * can consume (900mA). Closest level is 500mA
		 */
		dev_dbg(di->dev, "USB_STAT_ACA_RID_A detected\n");
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		di->is_aca_rid = 1;
		अवरोध;
	हाल USB_STAT_ACA_RID_B:
		/*
		 * Dedicated अक्षरger level minus 120mA (20mA क्रम ACA and
		 * 100mA क्रम potential accessory). Closest level is 1300mA
		 */
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_1P3;
		dev_dbg(di->dev, "USB Type - 0x%02x MaxCurr: %d", link_status,
				di->max_usb_in_curr.usb_type_max);
		di->is_aca_rid = 1;
		अवरोध;
	हाल USB_STAT_HOST_CHG_NM:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		di->is_aca_rid = 0;
		अवरोध;
	हाल USB_STAT_DEDICATED_CHG:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_1P5;
		di->is_aca_rid = 0;
		अवरोध;
	हाल USB_STAT_ACA_RID_C_HS_CHIRP:
	हाल USB_STAT_ACA_RID_C_NM:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_1P5;
		di->is_aca_rid = 1;
		अवरोध;
	हाल USB_STAT_NOT_CONFIGURED:
		अगर (di->vbus_detected) अणु
			di->usb_device_is_unrecognised = true;
			dev_dbg(di->dev, "USB Type - Legacy charger.\n");
			di->max_usb_in_curr.usb_type_max =
						USB_CH_IP_CUR_LVL_1P5;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल USB_STAT_HM_IDGND:
		dev_err(di->dev, "USB Type - Charging not allowed\n");
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P05;
		ret = -ENXIO;
		अवरोध;
	हाल USB_STAT_RESERVED:
		अगर (is_ab8500(di->parent)) अणु
			di->flags.vbus_collapse = true;
			dev_err(di->dev, "USB Type - USB_STAT_RESERVED "
						"VBUS has collapsed\n");
			ret = -ENXIO;
			अवरोध;
		पूर्ण अन्यथा अणु
			dev_dbg(di->dev, "USB Type - Charging not allowed\n");
			di->max_usb_in_curr.usb_type_max =
						USB_CH_IP_CUR_LVL_0P05;
			dev_dbg(di->dev, "USB Type - 0x%02x MaxCurr: %d",
				link_status,
				di->max_usb_in_curr.usb_type_max);
			ret = -ENXIO;
			अवरोध;
		पूर्ण
	हाल USB_STAT_CARKIT_1:
	हाल USB_STAT_CARKIT_2:
	हाल USB_STAT_ACA_DOCK_CHARGER:
	हाल USB_STAT_CHARGER_LINE_1:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		dev_dbg(di->dev, "USB Type - 0x%02x MaxCurr: %d", link_status,
				di->max_usb_in_curr.usb_type_max);
		अवरोध;
	हाल USB_STAT_NOT_VALID_LINK:
		dev_err(di->dev, "USB Type invalid - try charging anyway\n");
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		अवरोध;

	शेष:
		dev_err(di->dev, "USB Type - Unknown\n");
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P05;
		ret = -ENXIO;
		अवरोध;
	पूर्ण

	di->max_usb_in_curr.set_max = di->max_usb_in_curr.usb_type_max;
	dev_dbg(di->dev, "USB Type - 0x%02x MaxCurr: %d",
		link_status, di->max_usb_in_curr.set_max);

	वापस ret;
पूर्ण

/**
 * ab8500_अक्षरger_पढ़ो_usb_type() - पढ़ो the type of usb connected
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Detect the type of the plugged USB
 * Returns error code in हाल of failure अन्यथा 0 on success
 */
अटल पूर्णांक ab8500_अक्षरger_पढ़ो_usb_type(काष्ठा ab8500_अक्षरger *di)
अणु
	पूर्णांक ret;
	u8 val;

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_INTERRUPT, AB8500_IT_SOURCE21_REG, &val);
	अगर (ret < 0) अणु
		dev_err(di->dev, "%s ab8500 read failed\n", __func__);
		वापस ret;
	पूर्ण
	अगर (is_ab8500(di->parent))
		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_USB,
			AB8500_USB_LINE_STAT_REG, &val);
	अन्यथा
		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_USB, AB8500_USB_LINK1_STAT_REG, &val);
	अगर (ret < 0) अणु
		dev_err(di->dev, "%s ab8500 read failed\n", __func__);
		वापस ret;
	पूर्ण

	/* get the USB type */
	अगर (is_ab8500(di->parent))
		val = (val & AB8500_USB_LINK_STATUS) >> USB_LINK_STATUS_SHIFT;
	अन्यथा
		val = (val & AB8505_USB_LINK_STATUS) >> USB_LINK_STATUS_SHIFT;
	ret = ab8500_अक्षरger_max_usb_curr(di,
		(क्रमागत ab8500_अक्षरger_link_status) val);

	वापस ret;
पूर्ण

/**
 * ab8500_अक्षरger_detect_usb_type() - get the type of usb connected
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Detect the type of the plugged USB
 * Returns error code in हाल of failure अन्यथा 0 on success
 */
अटल पूर्णांक ab8500_अक्षरger_detect_usb_type(काष्ठा ab8500_अक्षरger *di)
अणु
	पूर्णांक i, ret;
	u8 val;

	/*
	 * On getting the VBUS rising edge detect पूर्णांकerrupt there
	 * is a 250ms delay after which the रेजिस्टर UsbLineStatus
	 * is filled with valid data.
	 */
	क्रम (i = 0; i < 10; i++) अणु
		msleep(250);
		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_INTERRUPT, AB8500_IT_SOURCE21_REG,
			&val);
		dev_dbg(di->dev, "%s AB8500_IT_SOURCE21_REG %x\n",
			__func__, val);
		अगर (ret < 0) अणु
			dev_err(di->dev, "%s ab8500 read failed\n", __func__);
			वापस ret;
		पूर्ण

		अगर (is_ab8500(di->parent))
			ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
				AB8500_USB, AB8500_USB_LINE_STAT_REG, &val);
		अन्यथा
			ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
				AB8500_USB, AB8500_USB_LINK1_STAT_REG, &val);
		अगर (ret < 0) अणु
			dev_err(di->dev, "%s ab8500 read failed\n", __func__);
			वापस ret;
		पूर्ण
		dev_dbg(di->dev, "%s AB8500_USB_LINE_STAT_REG %x\n", __func__,
			val);
		/*
		 * Until the IT source रेजिस्टर is पढ़ो the UsbLineStatus
		 * रेजिस्टर is not updated, hence करोing the same
		 * Revisit this:
		 */

		/* get the USB type */
		अगर (is_ab8500(di->parent))
			val = (val & AB8500_USB_LINK_STATUS) >>
							USB_LINK_STATUS_SHIFT;
		अन्यथा
			val = (val & AB8505_USB_LINK_STATUS) >>
							USB_LINK_STATUS_SHIFT;
		अगर (val)
			अवरोध;
	पूर्ण
	ret = ab8500_अक्षरger_max_usb_curr(di,
		(क्रमागत ab8500_अक्षरger_link_status) val);

	वापस ret;
पूर्ण

/*
 * This array maps the raw hex value to अक्षरger voltage used by the AB8500
 * Values taken from the UM0836
 */
अटल पूर्णांक ab8500_अक्षरger_voltage_map[] = अणु
	3500 ,
	3525 ,
	3550 ,
	3575 ,
	3600 ,
	3625 ,
	3650 ,
	3675 ,
	3700 ,
	3725 ,
	3750 ,
	3775 ,
	3800 ,
	3825 ,
	3850 ,
	3875 ,
	3900 ,
	3925 ,
	3950 ,
	3975 ,
	4000 ,
	4025 ,
	4050 ,
	4060 ,
	4070 ,
	4080 ,
	4090 ,
	4100 ,
	4110 ,
	4120 ,
	4130 ,
	4140 ,
	4150 ,
	4160 ,
	4170 ,
	4180 ,
	4190 ,
	4200 ,
	4210 ,
	4220 ,
	4230 ,
	4240 ,
	4250 ,
	4260 ,
	4270 ,
	4280 ,
	4290 ,
	4300 ,
	4310 ,
	4320 ,
	4330 ,
	4340 ,
	4350 ,
	4360 ,
	4370 ,
	4380 ,
	4390 ,
	4400 ,
	4410 ,
	4420 ,
	4430 ,
	4440 ,
	4450 ,
	4460 ,
	4470 ,
	4480 ,
	4490 ,
	4500 ,
	4510 ,
	4520 ,
	4530 ,
	4540 ,
	4550 ,
	4560 ,
	4570 ,
	4580 ,
	4590 ,
	4600 ,
पूर्ण;

अटल पूर्णांक ab8500_voltage_to_regval(पूर्णांक voltage)
अणु
	पूर्णांक i;

	/* Special हाल क्रम voltage below 3.5V */
	अगर (voltage < ab8500_अक्षरger_voltage_map[0])
		वापस LOW_VOLT_REG;

	क्रम (i = 1; i < ARRAY_SIZE(ab8500_अक्षरger_voltage_map); i++) अणु
		अगर (voltage < ab8500_अक्षरger_voltage_map[i])
			वापस i - 1;
	पूर्ण

	/* If not last element, वापस error */
	i = ARRAY_SIZE(ab8500_अक्षरger_voltage_map) - 1;
	अगर (voltage == ab8500_अक्षरger_voltage_map[i])
		वापस i;
	अन्यथा
		वापस -1;
पूर्ण

अटल पूर्णांक ab8500_current_to_regval(काष्ठा ab8500_अक्षरger *di, पूर्णांक curr)
अणु
	पूर्णांक i;

	अगर (curr < di->bm->chg_output_curr[0])
		वापस 0;

	क्रम (i = 0; i < di->bm->n_chg_out_curr; i++) अणु
		अगर (curr < di->bm->chg_output_curr[i])
			वापस i - 1;
	पूर्ण

	/* If not last element, वापस error */
	i = di->bm->n_chg_out_curr - 1;
	अगर (curr == di->bm->chg_output_curr[i])
		वापस i;
	अन्यथा
		वापस -1;
पूर्ण

अटल पूर्णांक ab8500_vbus_in_curr_to_regval(काष्ठा ab8500_अक्षरger *di, पूर्णांक curr)
अणु
	पूर्णांक i;

	अगर (curr < di->bm->chg_input_curr[0])
		वापस 0;

	क्रम (i = 0; i < di->bm->n_chg_in_curr; i++) अणु
		अगर (curr < di->bm->chg_input_curr[i])
			वापस i - 1;
	पूर्ण

	/* If not last element, वापस error */
	i = di->bm->n_chg_in_curr - 1;
	अगर (curr == di->bm->chg_input_curr[i])
		वापस i;
	अन्यथा
		वापस -1;
पूर्ण

/**
 * ab8500_अक्षरger_get_usb_cur() - get usb current
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाre
 *
 * The usb stack provides the maximum current that can be drawn from
 * the standard usb host. This will be in mA.
 * This function converts current in mA to a value that can be written
 * to the रेजिस्टर. Returns -1 अगर अक्षरging is not allowed
 */
अटल पूर्णांक ab8500_अक्षरger_get_usb_cur(काष्ठा ab8500_अक्षरger *di)
अणु
	पूर्णांक ret = 0;
	चयन (di->usb_state.usb_current) अणु
	हाल 100:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P09;
		अवरोध;
	हाल 200:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P19;
		अवरोध;
	हाल 300:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P29;
		अवरोध;
	हाल 400:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P38;
		अवरोध;
	हाल 500:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P5;
		अवरोध;
	शेष:
		di->max_usb_in_curr.usb_type_max = USB_CH_IP_CUR_LVL_0P05;
		ret = -EPERM;
		अवरोध;
	पूर्ण
	di->max_usb_in_curr.set_max = di->max_usb_in_curr.usb_type_max;
	वापस ret;
पूर्ण

/**
 * ab8500_अक्षरger_check_जारी_stepping() - Check to allow stepping
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 * @reg:	select what अक्षरger रेजिस्टर to check
 *
 * Check अगर current stepping should be allowed to जारी.
 * Checks अगर अक्षरger source has not collapsed. If it has, further stepping
 * is not allowed.
 */
अटल bool ab8500_अक्षरger_check_जारी_stepping(काष्ठा ab8500_अक्षरger *di,
						   पूर्णांक reg)
अणु
	अगर (reg == AB8500_USBCH_IPT_CRNTLVL_REG)
		वापस !di->flags.vbus_drop_end;
	अन्यथा
		वापस true;
पूर्ण

/**
 * ab8500_अक्षरger_set_current() - set अक्षरger current
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 * @ich:	अक्षरger current, in mA
 * @reg:	select what अक्षरger रेजिस्टर to set
 *
 * Set अक्षरger current.
 * There is no state machine in the AB to step up/करोwn the अक्षरger
 * current to aव्योम dips and spikes on MAIN, VBUS and VBAT when
 * अक्षरging is started. Instead we need to implement
 * this अक्षरger current step-up/करोwn here.
 * Returns error code in हाल of failure अन्यथा 0(on success)
 */
अटल पूर्णांक ab8500_अक्षरger_set_current(काष्ठा ab8500_अक्षरger *di,
	पूर्णांक ich, पूर्णांक reg)
अणु
	पूर्णांक ret = 0;
	पूर्णांक curr_index, prev_curr_index, shअगरt_value, i;
	u8 reg_value;
	u32 step_udelay;
	bool no_stepping = false;

	atomic_inc(&di->current_stepping_sessions);

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
		reg, &reg_value);
	अगर (ret < 0) अणु
		dev_err(di->dev, "%s read failed\n", __func__);
		जाओ निकास_set_current;
	पूर्ण

	चयन (reg) अणु
	हाल AB8500_MCH_IPT_CURLVL_REG:
		shअगरt_value = MAIN_CH_INPUT_CURR_SHIFT;
		prev_curr_index = (reg_value >> shअगरt_value);
		curr_index = ab8500_current_to_regval(di, ich);
		step_udelay = STEP_UDELAY;
		अगर (!di->ac.अक्षरger_connected)
			no_stepping = true;
		अवरोध;
	हाल AB8500_USBCH_IPT_CRNTLVL_REG:
		shअगरt_value = VBUS_IN_CURR_LIM_SHIFT;
		prev_curr_index = (reg_value >> shअगरt_value);
		curr_index = ab8500_vbus_in_curr_to_regval(di, ich);
		step_udelay = STEP_UDELAY * 100;

		अगर (!di->usb.अक्षरger_connected)
			no_stepping = true;
		अवरोध;
	हाल AB8500_CH_OPT_CRNTLVL_REG:
		shअगरt_value = 0;
		prev_curr_index = (reg_value >> shअगरt_value);
		curr_index = ab8500_current_to_regval(di, ich);
		step_udelay = STEP_UDELAY;
		अगर (curr_index && (curr_index - prev_curr_index) > 1)
			step_udelay *= 100;

		अगर (!di->usb.अक्षरger_connected && !di->ac.अक्षरger_connected)
			no_stepping = true;

		अवरोध;
	शेष:
		dev_err(di->dev, "%s current register not valid\n", __func__);
		ret = -ENXIO;
		जाओ निकास_set_current;
	पूर्ण

	अगर (curr_index < 0) अणु
		dev_err(di->dev, "requested current limit out-of-range\n");
		ret = -ENXIO;
		जाओ निकास_set_current;
	पूर्ण

	/* only update current अगर it's been changed */
	अगर (prev_curr_index == curr_index) अणु
		dev_dbg(di->dev, "%s current not changed for reg: 0x%02x\n",
			__func__, reg);
		ret = 0;
		जाओ निकास_set_current;
	पूर्ण

	dev_dbg(di->dev, "%s set charger current: %d mA for reg: 0x%02x\n",
		__func__, ich, reg);

	अगर (no_stepping) अणु
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
					reg, (u8)curr_index << shअगरt_value);
		अगर (ret)
			dev_err(di->dev, "%s write failed\n", __func__);
	पूर्ण अन्यथा अगर (prev_curr_index > curr_index) अणु
		क्रम (i = prev_curr_index - 1; i >= curr_index; i--) अणु
			dev_dbg(di->dev, "curr change_1 to: %x for 0x%02x\n",
				(u8) i << shअगरt_value, reg);
			ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
				AB8500_CHARGER, reg, (u8)i << shअगरt_value);
			अगर (ret) अणु
				dev_err(di->dev, "%s write failed\n", __func__);
				जाओ निकास_set_current;
			पूर्ण
			अगर (i != curr_index)
				usleep_range(step_udelay, step_udelay * 2);
		पूर्ण
	पूर्ण अन्यथा अणु
		bool allow = true;
		क्रम (i = prev_curr_index + 1; i <= curr_index && allow; i++) अणु
			dev_dbg(di->dev, "curr change_2 to: %x for 0x%02x\n",
				(u8)i << shअगरt_value, reg);
			ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
				AB8500_CHARGER, reg, (u8)i << shअगरt_value);
			अगर (ret) अणु
				dev_err(di->dev, "%s write failed\n", __func__);
				जाओ निकास_set_current;
			पूर्ण
			अगर (i != curr_index)
				usleep_range(step_udelay, step_udelay * 2);

			allow = ab8500_अक्षरger_check_जारी_stepping(di, reg);
		पूर्ण
	पूर्ण

निकास_set_current:
	atomic_dec(&di->current_stepping_sessions);

	वापस ret;
पूर्ण

/**
 * ab8500_अक्षरger_set_vbus_in_curr() - set VBUS input current limit
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 * @ich_in:	अक्षरger input current limit
 *
 * Sets the current that can be drawn from the USB host
 * Returns error code in हाल of failure अन्यथा 0(on success)
 */
अटल पूर्णांक ab8500_अक्षरger_set_vbus_in_curr(काष्ठा ab8500_अक्षरger *di,
		पूर्णांक ich_in)
अणु
	पूर्णांक min_value;
	पूर्णांक ret;

	/* We should always use to lowest current limit */
	min_value = min(di->bm->chg_params->usb_curr_max, ich_in);
	अगर (di->max_usb_in_curr.set_max > 0)
		min_value = min(di->max_usb_in_curr.set_max, min_value);

	अगर (di->usb_state.usb_current >= 0)
		min_value = min(di->usb_state.usb_current, min_value);

	चयन (min_value) अणु
	हाल 100:
		अगर (di->vbat < VBAT_TRESH_IP_CUR_RED)
			min_value = USB_CH_IP_CUR_LVL_0P05;
		अवरोध;
	हाल 500:
		अगर (di->vbat < VBAT_TRESH_IP_CUR_RED)
			min_value = USB_CH_IP_CUR_LVL_0P45;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dev_info(di->dev, "VBUS input current limit set to %d mA\n", min_value);

	mutex_lock(&di->usb_ipt_crnt_lock);
	ret = ab8500_अक्षरger_set_current(di, min_value,
		AB8500_USBCH_IPT_CRNTLVL_REG);
	mutex_unlock(&di->usb_ipt_crnt_lock);

	वापस ret;
पूर्ण

/**
 * ab8500_अक्षरger_set_मुख्य_in_curr() - set मुख्य अक्षरger input current
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 * @ich_in:	input अक्षरger current, in mA
 *
 * Set मुख्य अक्षरger input current.
 * Returns error code in हाल of failure अन्यथा 0(on success)
 */
अटल पूर्णांक ab8500_अक्षरger_set_मुख्य_in_curr(काष्ठा ab8500_अक्षरger *di,
	पूर्णांक ich_in)
अणु
	वापस ab8500_अक्षरger_set_current(di, ich_in,
		AB8500_MCH_IPT_CURLVL_REG);
पूर्ण

/**
 * ab8500_अक्षरger_set_output_curr() - set अक्षरger output current
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 * @ich_out:	output अक्षरger current, in mA
 *
 * Set अक्षरger output current.
 * Returns error code in हाल of failure अन्यथा 0(on success)
 */
अटल पूर्णांक ab8500_अक्षरger_set_output_curr(काष्ठा ab8500_अक्षरger *di,
	पूर्णांक ich_out)
अणु
	वापस ab8500_अक्षरger_set_current(di, ich_out,
		AB8500_CH_OPT_CRNTLVL_REG);
पूर्ण

/**
 * ab8500_अक्षरger_led_en() - turn on/off अक्षरgign led
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 * @on:		flag to turn on/off the अक्षरgign led
 *
 * Power ON/OFF अक्षरging LED indication
 * Returns error code in हाल of failure अन्यथा 0(on success)
 */
अटल पूर्णांक ab8500_अक्षरger_led_en(काष्ठा ab8500_अक्षरger *di, पूर्णांक on)
अणु
	पूर्णांक ret;

	अगर (on) अणु
		/* Power ON अक्षरging LED indicator, set LED current to 5mA */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
			AB8500_LED_INDICATOR_PWM_CTRL,
			(LED_IND_CUR_5MA | LED_INDICATOR_PWM_ENA));
		अगर (ret) अणु
			dev_err(di->dev, "Power ON LED failed\n");
			वापस ret;
		पूर्ण
		/* LED indicator PWM duty cycle 252/256 */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
			AB8500_LED_INDICATOR_PWM_DUTY,
			LED_INDICATOR_PWM_DUTY_252_256);
		अगर (ret) अणु
			dev_err(di->dev, "Set LED PWM duty cycle failed\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Power off अक्षरging LED indicator */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
			AB8500_LED_INDICATOR_PWM_CTRL,
			LED_INDICATOR_PWM_DIS);
		अगर (ret) अणु
			dev_err(di->dev, "Power-off LED failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ab8500_अक्षरger_ac_en() - enable or disable ac अक्षरging
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 * @enable:	enable/disable flag
 * @vset:	अक्षरging voltage
 * @iset:	अक्षरging current
 *
 * Enable/Disable AC/Mains अक्षरging and turns on/off the अक्षरging led
 * respectively.
 **/
अटल पूर्णांक ab8500_अक्षरger_ac_en(काष्ठा ux500_अक्षरger *अक्षरger,
	पूर्णांक enable, पूर्णांक vset, पूर्णांक iset)
अणु
	पूर्णांक ret;
	पूर्णांक volt_index;
	पूर्णांक curr_index;
	पूर्णांक input_curr_index;
	u8 overshoot = 0;

	काष्ठा ab8500_अक्षरger *di = to_ab8500_अक्षरger_ac_device_info(अक्षरger);

	अगर (enable) अणु
		/* Check अगर AC is connected */
		अगर (!di->ac.अक्षरger_connected) अणु
			dev_err(di->dev, "AC charger not connected\n");
			वापस -ENXIO;
		पूर्ण

		/* Enable AC अक्षरging */
		dev_dbg(di->dev, "Enable AC: %dmV %dmA\n", vset, iset);

		/*
		 * Due to a bug in AB8500, BTEMP_HIGH/LOW पूर्णांकerrupts
		 * will be triggered every समय we enable the VDD ADC supply.
		 * This will turn off अक्षरging क्रम a लघु जबतक.
		 * It can be aव्योमed by having the supply on when
		 * there is a अक्षरger enabled. Normally the VDD ADC supply
		 * is enabled every समय a GPADC conversion is triggered.
		 * We will क्रमce it to be enabled from this driver to have
		 * the GPADC module independent of the AB8500 अक्षरgers
		 */
		अगर (!di->vddadc_en_ac) अणु
			ret = regulator_enable(di->regu);
			अगर (ret)
				dev_warn(di->dev,
					"Failed to enable regulator\n");
			अन्यथा
				di->vddadc_en_ac = true;
		पूर्ण

		/* Check अगर the requested voltage or current is valid */
		volt_index = ab8500_voltage_to_regval(vset);
		curr_index = ab8500_current_to_regval(di, iset);
		input_curr_index = ab8500_current_to_regval(di,
			di->bm->chg_params->ac_curr_max);
		अगर (volt_index < 0 || curr_index < 0 || input_curr_index < 0) अणु
			dev_err(di->dev,
				"Charger voltage or current too high, "
				"charging not started\n");
			वापस -ENXIO;
		पूर्ण

		/* ChVoltLevel: maximum battery अक्षरging voltage */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
			AB8500_CH_VOLT_LVL_REG, (u8) volt_index);
		अगर (ret) अणु
			dev_err(di->dev, "%s write failed\n", __func__);
			वापस ret;
		पूर्ण
		/* MainChInputCurr: current that can be drawn from the अक्षरger*/
		ret = ab8500_अक्षरger_set_मुख्य_in_curr(di,
			di->bm->chg_params->ac_curr_max);
		अगर (ret) अणु
			dev_err(di->dev, "%s Failed to set MainChInputCurr\n",
				__func__);
			वापस ret;
		पूर्ण
		/* ChOutputCurentLevel: रक्षित output current */
		ret = ab8500_अक्षरger_set_output_curr(di, iset);
		अगर (ret) अणु
			dev_err(di->dev, "%s "
				"Failed to set ChOutputCurentLevel\n",
				__func__);
			वापस ret;
		पूर्ण

		/* Check अगर VBAT overshoot control should be enabled */
		अगर (!di->bm->enable_overshoot)
			overshoot = MAIN_CH_NO_OVERSHOOT_ENA_N;

		/* Enable Main Charger */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
			AB8500_MCH_CTRL1, MAIN_CH_ENA | overshoot);
		अगर (ret) अणु
			dev_err(di->dev, "%s write failed\n", __func__);
			वापस ret;
		पूर्ण

		/* Power on अक्षरging LED indication */
		ret = ab8500_अक्षरger_led_en(di, true);
		अगर (ret < 0)
			dev_err(di->dev, "failed to enable LED\n");

		di->ac.अक्षरger_online = 1;
	पूर्ण अन्यथा अणु
		/* Disable AC अक्षरging */
		अगर (is_ab8500_1p1_or_earlier(di->parent)) अणु
			/*
			 * For ABB revision 1.0 and 1.1 there is a bug in the
			 * watchकरोg logic. That means we have to continuously
			 * kick the अक्षरger watchकरोg even when no अक्षरger is
			 * connected. This is only valid once the AC अक्षरger
			 * has been enabled. This is a bug that is not handled
			 * by the algorithm and the watchकरोg have to be kicked
			 * by the अक्षरger driver when the AC अक्षरger
			 * is disabled
			 */
			अगर (di->ac_conn) अणु
				queue_delayed_work(di->अक्षरger_wq,
					&di->kick_wd_work,
					round_jअगरfies(WD_KICK_INTERVAL));
			पूर्ण

			/*
			 * We can't turn off अक्षरging completely
			 * due to a bug in AB8500 cut1.
			 * If we करो, अक्षरging will not start again.
			 * That is why we set the lowest voltage
			 * and current possible
			 */
			ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
				AB8500_CHARGER,
				AB8500_CH_VOLT_LVL_REG, CH_VOL_LVL_3P5);
			अगर (ret) अणु
				dev_err(di->dev,
					"%s write failed\n", __func__);
				वापस ret;
			पूर्ण

			ret = ab8500_अक्षरger_set_output_curr(di, 0);
			अगर (ret) अणु
				dev_err(di->dev, "%s "
					"Failed to set ChOutputCurentLevel\n",
					__func__);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
				AB8500_CHARGER,
				AB8500_MCH_CTRL1, 0);
			अगर (ret) अणु
				dev_err(di->dev,
					"%s write failed\n", __func__);
				वापस ret;
			पूर्ण
		पूर्ण

		ret = ab8500_अक्षरger_led_en(di, false);
		अगर (ret < 0)
			dev_err(di->dev, "failed to disable LED\n");

		di->ac.अक्षरger_online = 0;
		di->ac.wd_expired = false;

		/* Disable regulator अगर enabled */
		अगर (di->vddadc_en_ac) अणु
			regulator_disable(di->regu);
			di->vddadc_en_ac = false;
		पूर्ण

		dev_dbg(di->dev, "%s Disabled AC charging\n", __func__);
	पूर्ण
	ab8500_घातer_supply_changed(di, di->ac_chg.psy);

	वापस ret;
पूर्ण

/**
 * ab8500_अक्षरger_usb_en() - enable usb अक्षरging
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 * @enable:	enable/disable flag
 * @vset:	अक्षरging voltage
 * @ich_out:	अक्षरger output current
 *
 * Enable/Disable USB अक्षरging and turns on/off the अक्षरging led respectively.
 * Returns error code in हाल of failure अन्यथा 0(on success)
 */
अटल पूर्णांक ab8500_अक्षरger_usb_en(काष्ठा ux500_अक्षरger *अक्षरger,
	पूर्णांक enable, पूर्णांक vset, पूर्णांक ich_out)
अणु
	पूर्णांक ret;
	पूर्णांक volt_index;
	पूर्णांक curr_index;
	u8 overshoot = 0;

	काष्ठा ab8500_अक्षरger *di = to_ab8500_अक्षरger_usb_device_info(अक्षरger);

	अगर (enable) अणु
		/* Check अगर USB is connected */
		अगर (!di->usb.अक्षरger_connected) अणु
			dev_err(di->dev, "USB charger not connected\n");
			वापस -ENXIO;
		पूर्ण

		/*
		 * Due to a bug in AB8500, BTEMP_HIGH/LOW पूर्णांकerrupts
		 * will be triggered every समय we enable the VDD ADC supply.
		 * This will turn off अक्षरging क्रम a लघु जबतक.
		 * It can be aव्योमed by having the supply on when
		 * there is a अक्षरger enabled. Normally the VDD ADC supply
		 * is enabled every समय a GPADC conversion is triggered.
		 * We will क्रमce it to be enabled from this driver to have
		 * the GPADC module independent of the AB8500 अक्षरgers
		 */
		अगर (!di->vddadc_en_usb) अणु
			ret = regulator_enable(di->regu);
			अगर (ret)
				dev_warn(di->dev,
					"Failed to enable regulator\n");
			अन्यथा
				di->vddadc_en_usb = true;
		पूर्ण

		/* Enable USB अक्षरging */
		dev_dbg(di->dev, "Enable USB: %dmV %dmA\n", vset, ich_out);

		/* Check अगर the requested voltage or current is valid */
		volt_index = ab8500_voltage_to_regval(vset);
		curr_index = ab8500_current_to_regval(di, ich_out);
		अगर (volt_index < 0 || curr_index < 0) अणु
			dev_err(di->dev,
				"Charger voltage or current too high, "
				"charging not started\n");
			वापस -ENXIO;
		पूर्ण

		/*
		 * ChVoltLevel: max voltage up to which battery can be
		 * अक्षरged
		 */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
			AB8500_CH_VOLT_LVL_REG, (u8) volt_index);
		अगर (ret) अणु
			dev_err(di->dev, "%s write failed\n", __func__);
			वापस ret;
		पूर्ण
		/* Check अगर VBAT overshoot control should be enabled */
		अगर (!di->bm->enable_overshoot)
			overshoot = USB_CHG_NO_OVERSHOOT_ENA_N;

		/* Enable USB Charger */
		dev_dbg(di->dev,
			"Enabling USB with write to AB8500_USBCH_CTRL1_REG\n");
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
			AB8500_USBCH_CTRL1_REG, USB_CH_ENA | overshoot);
		अगर (ret) अणु
			dev_err(di->dev, "%s write failed\n", __func__);
			वापस ret;
		पूर्ण

		/* If success घातer on अक्षरging LED indication */
		ret = ab8500_अक्षरger_led_en(di, true);
		अगर (ret < 0)
			dev_err(di->dev, "failed to enable LED\n");

		di->usb.अक्षरger_online = 1;

		/* USBChInputCurr: current that can be drawn from the usb */
		ret = ab8500_अक्षरger_set_vbus_in_curr(di,
					di->max_usb_in_curr.usb_type_max);
		अगर (ret) अणु
			dev_err(di->dev, "setting USBChInputCurr failed\n");
			वापस ret;
		पूर्ण

		/* ChOutputCurentLevel: रक्षित output current */
		ret = ab8500_अक्षरger_set_output_curr(di, ich_out);
		अगर (ret) अणु
			dev_err(di->dev, "%s "
				"Failed to set ChOutputCurentLevel\n",
				__func__);
			वापस ret;
		पूर्ण

		queue_delayed_work(di->अक्षरger_wq, &di->check_vbat_work, HZ);

	पूर्ण अन्यथा अणु
		/* Disable USB अक्षरging */
		dev_dbg(di->dev, "%s Disabled USB charging\n", __func__);
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_CHARGER,
			AB8500_USBCH_CTRL1_REG, 0);
		अगर (ret) अणु
			dev_err(di->dev,
				"%s write failed\n", __func__);
			वापस ret;
		पूर्ण

		ret = ab8500_अक्षरger_led_en(di, false);
		अगर (ret < 0)
			dev_err(di->dev, "failed to disable LED\n");
		/* USBChInputCurr: current that can be drawn from the usb */
		ret = ab8500_अक्षरger_set_vbus_in_curr(di, 0);
		अगर (ret) अणु
			dev_err(di->dev, "setting USBChInputCurr failed\n");
			वापस ret;
		पूर्ण

		/* ChOutputCurentLevel: रक्षित output current */
		ret = ab8500_अक्षरger_set_output_curr(di, 0);
		अगर (ret) अणु
			dev_err(di->dev, "%s "
				"Failed to reset ChOutputCurentLevel\n",
				__func__);
			वापस ret;
		पूर्ण
		di->usb.अक्षरger_online = 0;
		di->usb.wd_expired = false;

		/* Disable regulator अगर enabled */
		अगर (di->vddadc_en_usb) अणु
			regulator_disable(di->regu);
			di->vddadc_en_usb = false;
		पूर्ण

		dev_dbg(di->dev, "%s Disabled USB charging\n", __func__);

		/* Cancel any pending Vbat check work */
		cancel_delayed_work(&di->check_vbat_work);

	पूर्ण
	ab8500_घातer_supply_changed(di, di->usb_chg.psy);

	वापस ret;
पूर्ण

अटल पूर्णांक ab8500_बाह्यal_अक्षरger_prepare(काष्ठा notअगरier_block *अक्षरger_nb,
				अचिन्हित दीर्घ event, व्योम *data)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = data;
	/*Toggle External अक्षरger control pin*/
	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(dev, AB8500_SYS_CTRL1_BLOCK,
				  AB8500_SYS_CHARGER_CONTROL_REG,
				  EXTERNAL_CHARGER_DISABLE_REG_VAL);
	अगर (ret < 0) अणु
		dev_err(dev, "write reg failed %d\n", ret);
		जाओ out;
	पूर्ण
	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(dev, AB8500_SYS_CTRL1_BLOCK,
				  AB8500_SYS_CHARGER_CONTROL_REG,
				  EXTERNAL_CHARGER_ENABLE_REG_VAL);
	अगर (ret < 0)
		dev_err(dev, "Write reg failed %d\n", ret);

out:
	वापस ret;
पूर्ण

/**
 * ab8500_अक्षरger_usb_check_enable() - enable usb अक्षरging
 * @अक्षरger:	poपूर्णांकer to the ux500_अक्षरger काष्ठाure
 * @vset:	अक्षरging voltage
 * @iset:	अक्षरger output current
 *
 * Check अगर the VBUS अक्षरger has been disconnected and reconnected without
 * AB8500 rising an पूर्णांकerrupt. Returns 0 on success.
 */
अटल पूर्णांक ab8500_अक्षरger_usb_check_enable(काष्ठा ux500_अक्षरger *अक्षरger,
	पूर्णांक vset, पूर्णांक iset)
अणु
	u8 usbch_ctrl1 = 0;
	पूर्णांक ret = 0;

	काष्ठा ab8500_अक्षरger *di = to_ab8500_अक्षरger_usb_device_info(अक्षरger);

	अगर (!di->usb.अक्षरger_connected)
		वापस ret;

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
				AB8500_USBCH_CTRL1_REG, &usbch_ctrl1);
	अगर (ret < 0) अणु
		dev_err(di->dev, "ab8500 read failed %d\n", __LINE__);
		वापस ret;
	पूर्ण
	dev_dbg(di->dev, "USB charger ctrl: 0x%02x\n", usbch_ctrl1);

	अगर (!(usbch_ctrl1 & USB_CH_ENA)) अणु
		dev_info(di->dev, "Charging has been disabled abnormally and will be re-enabled\n");

		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
					AB8500_CHARGER, AB8500_CHARGER_CTRL,
					DROP_COUNT_RESET, DROP_COUNT_RESET);
		अगर (ret < 0) अणु
			dev_err(di->dev, "ab8500 write failed %d\n", __LINE__);
			वापस ret;
		पूर्ण

		ret = ab8500_अक्षरger_usb_en(&di->usb_chg, true, vset, iset);
		अगर (ret < 0) अणु
			dev_err(di->dev, "Failed to enable VBUS charger %d\n",
					__LINE__);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 * ab8500_अक्षरger_ac_check_enable() - enable usb अक्षरging
 * @अक्षरger:	poपूर्णांकer to the ux500_अक्षरger काष्ठाure
 * @vset:	अक्षरging voltage
 * @iset:	अक्षरger output current
 *
 * Check अगर the AC अक्षरger has been disconnected and reconnected without
 * AB8500 rising an पूर्णांकerrupt. Returns 0 on success.
 */
अटल पूर्णांक ab8500_अक्षरger_ac_check_enable(काष्ठा ux500_अक्षरger *अक्षरger,
	पूर्णांक vset, पूर्णांक iset)
अणु
	u8 मुख्यch_ctrl1 = 0;
	पूर्णांक ret = 0;

	काष्ठा ab8500_अक्षरger *di = to_ab8500_अक्षरger_ac_device_info(अक्षरger);

	अगर (!di->ac.अक्षरger_connected)
		वापस ret;

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
				AB8500_MCH_CTRL1, &मुख्यch_ctrl1);
	अगर (ret < 0) अणु
		dev_err(di->dev, "ab8500 read failed %d\n", __LINE__);
		वापस ret;
	पूर्ण
	dev_dbg(di->dev, "AC charger ctrl: 0x%02x\n", मुख्यch_ctrl1);

	अगर (!(मुख्यch_ctrl1 & MAIN_CH_ENA)) अणु
		dev_info(di->dev, "Charging has been disabled abnormally and will be re-enabled\n");

		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
					AB8500_CHARGER, AB8500_CHARGER_CTRL,
					DROP_COUNT_RESET, DROP_COUNT_RESET);

		अगर (ret < 0) अणु
			dev_err(di->dev, "ab8500 write failed %d\n", __LINE__);
			वापस ret;
		पूर्ण

		ret = ab8500_अक्षरger_ac_en(&di->usb_chg, true, vset, iset);
		अगर (ret < 0) अणु
			dev_err(di->dev, "failed to enable AC charger %d\n",
				__LINE__);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 * ab8500_अक्षरger_watchकरोg_kick() - kick अक्षरger watchकरोg
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Kick अक्षरger watchकरोg
 * Returns error code in हाल of failure अन्यथा 0(on success)
 */
अटल पूर्णांक ab8500_अक्षरger_watchकरोg_kick(काष्ठा ux500_अक्षरger *अक्षरger)
अणु
	पूर्णांक ret;
	काष्ठा ab8500_अक्षरger *di;

	अगर (अक्षरger->psy->desc->type == POWER_SUPPLY_TYPE_MAINS)
		di = to_ab8500_अक्षरger_ac_device_info(अक्षरger);
	अन्यथा अगर (अक्षरger->psy->desc->type == POWER_SUPPLY_TYPE_USB)
		di = to_ab8500_अक्षरger_usb_device_info(अक्षरger);
	अन्यथा
		वापस -ENXIO;

	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
		AB8500_CHARG_WD_CTRL, CHARG_WD_KICK);
	अगर (ret)
		dev_err(di->dev, "Failed to kick WD!\n");

	वापस ret;
पूर्ण

/**
 * ab8500_अक्षरger_update_अक्षरger_current() - update अक्षरger current
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Update the अक्षरger output current क्रम the specअगरied अक्षरger
 * Returns error code in हाल of failure अन्यथा 0(on success)
 */
अटल पूर्णांक ab8500_अक्षरger_update_अक्षरger_current(काष्ठा ux500_अक्षरger *अक्षरger,
		पूर्णांक ich_out)
अणु
	पूर्णांक ret;
	काष्ठा ab8500_अक्षरger *di;

	अगर (अक्षरger->psy->desc->type == POWER_SUPPLY_TYPE_MAINS)
		di = to_ab8500_अक्षरger_ac_device_info(अक्षरger);
	अन्यथा अगर (अक्षरger->psy->desc->type == POWER_SUPPLY_TYPE_USB)
		di = to_ab8500_अक्षरger_usb_device_info(अक्षरger);
	अन्यथा
		वापस -ENXIO;

	ret = ab8500_अक्षरger_set_output_curr(di, ich_out);
	अगर (ret) अणु
		dev_err(di->dev, "%s "
			"Failed to set ChOutputCurentLevel\n",
			__func__);
		वापस ret;
	पूर्ण

	/* Reset the मुख्य and usb drop input current measurement counter */
	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
				AB8500_CHARGER_CTRL, DROP_COUNT_RESET);
	अगर (ret) अणु
		dev_err(di->dev, "%s write failed\n", __func__);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ab8500_अक्षरger_get_ext_psy_data(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा घातer_supply *psy;
	काष्ठा घातer_supply *ext = dev_get_drvdata(dev);
	स्थिर अक्षर **supplicants = (स्थिर अक्षर **)ext->supplied_to;
	काष्ठा ab8500_अक्षरger *di;
	जोड़ घातer_supply_propval ret;
	पूर्णांक j;
	काष्ठा ux500_अक्षरger *usb_chg;

	usb_chg = (काष्ठा ux500_अक्षरger *)data;
	psy = usb_chg->psy;

	di = to_ab8500_अक्षरger_usb_device_info(usb_chg);

	/* For all psy where the driver name appears in any supplied_to */
	j = match_string(supplicants, ext->num_supplicants, psy->desc->name);
	अगर (j < 0)
		वापस 0;

	/* Go through all properties क्रम the psy */
	क्रम (j = 0; j < ext->desc->num_properties; j++) अणु
		क्रमागत घातer_supply_property prop;
		prop = ext->desc->properties[j];

		अगर (घातer_supply_get_property(ext, prop, &ret))
			जारी;

		चयन (prop) अणु
		हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
			चयन (ext->desc->type) अणु
			हाल POWER_SUPPLY_TYPE_BATTERY:
				di->vbat = ret.पूर्णांकval / 1000;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ab8500_अक्षरger_check_vbat_work() - keep vbus current within spec
 * @work	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Due to a asic bug it is necessary to lower the input current to the vbus
 * अक्षरger when अक्षरging with at some specअगरic levels. This issue is only valid
 * क्रम below a certain battery voltage. This function makes sure that the
 * the allowed current limit isn't exceeded.
 */
अटल व्योम ab8500_अक्षरger_check_vbat_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक t = 10;
	काष्ठा ab8500_अक्षरger *di = container_of(work,
		काष्ठा ab8500_अक्षरger, check_vbat_work.work);

	class_क्रम_each_device(घातer_supply_class, शून्य,
		di->usb_chg.psy, ab8500_अक्षरger_get_ext_psy_data);

	/* First run old_vbat is 0. */
	अगर (di->old_vbat == 0)
		di->old_vbat = di->vbat;

	अगर (!((di->old_vbat <= VBAT_TRESH_IP_CUR_RED &&
		di->vbat <= VBAT_TRESH_IP_CUR_RED) ||
		(di->old_vbat > VBAT_TRESH_IP_CUR_RED &&
		di->vbat > VBAT_TRESH_IP_CUR_RED))) अणु

		dev_dbg(di->dev, "Vbat did cross threshold, curr: %d, new: %d,"
			" old: %d\n", di->max_usb_in_curr.usb_type_max,
			di->vbat, di->old_vbat);
		ab8500_अक्षरger_set_vbus_in_curr(di,
					di->max_usb_in_curr.usb_type_max);
		घातer_supply_changed(di->usb_chg.psy);
	पूर्ण

	di->old_vbat = di->vbat;

	/*
	 * No need to check the battery voltage every second when not बंद to
	 * the threshold.
	 */
	अगर (di->vbat < (VBAT_TRESH_IP_CUR_RED + 100) &&
		(di->vbat > (VBAT_TRESH_IP_CUR_RED - 100)))
			t = 1;

	queue_delayed_work(di->अक्षरger_wq, &di->check_vbat_work, t * HZ);
पूर्ण

/**
 * ab8500_अक्षरger_check_hw_failure_work() - check मुख्य अक्षरger failure
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Work queue function क्रम checking the मुख्य अक्षरger status
 */
अटल व्योम ab8500_अक्षरger_check_hw_failure_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	u8 reg_value;

	काष्ठा ab8500_अक्षरger *di = container_of(work,
		काष्ठा ab8500_अक्षरger, check_hw_failure_work.work);

	/* Check अगर the status bits क्रम HW failure is still active */
	अगर (di->flags.मुख्यextchnotok) अणु
		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_CHARGER, AB8500_CH_STATUS2_REG, &reg_value);
		अगर (ret < 0) अणु
			dev_err(di->dev, "%s ab8500 read failed\n", __func__);
			वापस;
		पूर्ण
		अगर (!(reg_value & MAIN_CH_NOK)) अणु
			di->flags.मुख्यextchnotok = false;
			ab8500_घातer_supply_changed(di, di->ac_chg.psy);
		पूर्ण
	पूर्ण
	अगर (di->flags.vbus_ovv) अणु
		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_CHARGER, AB8500_CH_USBCH_STAT2_REG,
			&reg_value);
		अगर (ret < 0) अणु
			dev_err(di->dev, "%s ab8500 read failed\n", __func__);
			वापस;
		पूर्ण
		अगर (!(reg_value & VBUS_OVV_TH)) अणु
			di->flags.vbus_ovv = false;
			ab8500_घातer_supply_changed(di, di->usb_chg.psy);
		पूर्ण
	पूर्ण
	/* If we still have a failure, schedule a new check */
	अगर (di->flags.मुख्यextchnotok || di->flags.vbus_ovv) अणु
		queue_delayed_work(di->अक्षरger_wq,
			&di->check_hw_failure_work, round_jअगरfies(HZ));
	पूर्ण
पूर्ण

/**
 * ab8500_अक्षरger_kick_watchकरोg_work() - kick the watchकरोg
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Work queue function क्रम kicking the अक्षरger watchकरोg.
 *
 * For ABB revision 1.0 and 1.1 there is a bug in the watchकरोg
 * logic. That means we have to continuously kick the अक्षरger
 * watchकरोg even when no अक्षरger is connected. This is only
 * valid once the AC अक्षरger has been enabled. This is
 * a bug that is not handled by the algorithm and the
 * watchकरोg have to be kicked by the अक्षरger driver
 * when the AC अक्षरger is disabled
 */
अटल व्योम ab8500_अक्षरger_kick_watchकरोg_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;

	काष्ठा ab8500_अक्षरger *di = container_of(work,
		काष्ठा ab8500_अक्षरger, kick_wd_work.work);

	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
		AB8500_CHARG_WD_CTRL, CHARG_WD_KICK);
	अगर (ret)
		dev_err(di->dev, "Failed to kick WD!\n");

	/* Schedule a new watchकरोg kick */
	queue_delayed_work(di->अक्षरger_wq,
		&di->kick_wd_work, round_jअगरfies(WD_KICK_INTERVAL));
पूर्ण

/**
 * ab8500_अक्षरger_ac_work() - work to get and set मुख्य अक्षरger status
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Work queue function क्रम checking the मुख्य अक्षरger status
 */
अटल व्योम ab8500_अक्षरger_ac_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;

	काष्ठा ab8500_अक्षरger *di = container_of(work,
		काष्ठा ab8500_अक्षरger, ac_work);

	/*
	 * Since we can't be sure that the events are received
	 * synchronously, we have the check अगर the मुख्य अक्षरger is
	 * connected by पढ़ोing the status रेजिस्टर
	 */
	ret = ab8500_अक्षरger_detect_अक्षरgers(di, false);
	अगर (ret < 0)
		वापस;

	अगर (ret & AC_PW_CONN) अणु
		di->ac.अक्षरger_connected = 1;
		di->ac_conn = true;
	पूर्ण अन्यथा अणु
		di->ac.अक्षरger_connected = 0;
	पूर्ण

	ab8500_घातer_supply_changed(di, di->ac_chg.psy);
	sysfs_notअगरy(&di->ac_chg.psy->dev.kobj, शून्य, "present");
पूर्ण

अटल व्योम ab8500_अक्षरger_usb_attached_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ab8500_अक्षरger *di = container_of(work,
						 काष्ठा ab8500_अक्षरger,
						 usb_अक्षरger_attached_work.work);
	पूर्णांक usbch = (USB_CH_VBUSDROP | USB_CH_VBUSDETDBNC);
	पूर्णांक ret, i;
	u8 statval;

	क्रम (i = 0; i < 10; i++) अणु
		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
							AB8500_CHARGER,
							AB8500_CH_USBCH_STAT1_REG,
							&statval);
		अगर (ret < 0) अणु
			dev_err(di->dev, "ab8500 read failed %d\n", __LINE__);
			जाओ reschedule;
		पूर्ण
		अगर ((statval & usbch) != usbch)
			जाओ reschedule;

		msleep(CHARGER_STATUS_POLL);
	पूर्ण

	ab8500_अक्षरger_usb_en(&di->usb_chg, 0, 0, 0);

	mutex_lock(&di->अक्षरger_attached_mutex);
	mutex_unlock(&di->अक्षरger_attached_mutex);

	वापस;

reschedule:
	queue_delayed_work(di->अक्षरger_wq,
			   &di->usb_अक्षरger_attached_work,
			   HZ);
पूर्ण

अटल व्योम ab8500_अक्षरger_ac_attached_work(काष्ठा work_काष्ठा *work)
अणु

	काष्ठा ab8500_अक्षरger *di = container_of(work,
						 काष्ठा ab8500_अक्षरger,
						 ac_अक्षरger_attached_work.work);
	पूर्णांक मुख्यch = (MAIN_CH_STATUS2_MAINCHGDROP |
		      MAIN_CH_STATUS2_MAINCHARGERDETDBNC);
	पूर्णांक ret, i;
	u8 statval;

	क्रम (i = 0; i < 10; i++) अणु
		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
							AB8500_CHARGER,
							AB8500_CH_STATUS2_REG,
							&statval);
		अगर (ret < 0) अणु
			dev_err(di->dev, "ab8500 read failed %d\n", __LINE__);
			जाओ reschedule;
		पूर्ण

		अगर ((statval & मुख्यch) != मुख्यch)
			जाओ reschedule;

		msleep(CHARGER_STATUS_POLL);
	पूर्ण

	ab8500_अक्षरger_ac_en(&di->ac_chg, 0, 0, 0);
	queue_work(di->अक्षरger_wq, &di->ac_work);

	mutex_lock(&di->अक्षरger_attached_mutex);
	mutex_unlock(&di->अक्षरger_attached_mutex);

	वापस;

reschedule:
	queue_delayed_work(di->अक्षरger_wq,
			   &di->ac_अक्षरger_attached_work,
			   HZ);
पूर्ण

/**
 * ab8500_अक्षरger_detect_usb_type_work() - work to detect USB type
 * @work:	Poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Detect the type of USB plugged
 */
अटल व्योम ab8500_अक्षरger_detect_usb_type_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;

	काष्ठा ab8500_अक्षरger *di = container_of(work,
		काष्ठा ab8500_अक्षरger, detect_usb_type_work);

	/*
	 * Since we can't be sure that the events are received
	 * synchronously, we have the check अगर is
	 * connected by पढ़ोing the status रेजिस्टर
	 */
	ret = ab8500_अक्षरger_detect_अक्षरgers(di, false);
	अगर (ret < 0)
		वापस;

	अगर (!(ret & USB_PW_CONN)) अणु
		dev_dbg(di->dev, "%s di->vbus_detected = false\n", __func__);
		di->vbus_detected = false;
		ab8500_अक्षरger_set_usb_connected(di, false);
		ab8500_घातer_supply_changed(di, di->usb_chg.psy);
	पूर्ण अन्यथा अणु
		dev_dbg(di->dev, "%s di->vbus_detected = true\n", __func__);
		di->vbus_detected = true;

		अगर (is_ab8500_1p1_or_earlier(di->parent)) अणु
			ret = ab8500_अक्षरger_detect_usb_type(di);
			अगर (!ret) अणु
				ab8500_अक्षरger_set_usb_connected(di, true);
				ab8500_घातer_supply_changed(di,
							    di->usb_chg.psy);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * For ABB cut2.0 and onwards we have an IRQ,
			 * USB_LINK_STATUS that will be triggered when the USB
			 * link status changes. The exception is USB connected
			 * during startup. Then we करोn't get a
			 * USB_LINK_STATUS IRQ
			 */
			अगर (di->vbus_detected_start) अणु
				di->vbus_detected_start = false;
				ret = ab8500_अक्षरger_detect_usb_type(di);
				अगर (!ret) अणु
					ab8500_अक्षरger_set_usb_connected(di,
						true);
					ab8500_घातer_supply_changed(di,
						di->usb_chg.psy);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ab8500_अक्षरger_usb_link_attach_work() - work to detect USB type
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Detect the type of USB plugged
 */
अटल व्योम ab8500_अक्षरger_usb_link_attach_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ab8500_अक्षरger *di =
		container_of(work, काष्ठा ab8500_अक्षरger, attach_work.work);
	पूर्णांक ret;

	/* Update maximum input current अगर USB क्रमागतeration is not detected */
	अगर (!di->usb.अक्षरger_online) अणु
		ret = ab8500_अक्षरger_set_vbus_in_curr(di,
					di->max_usb_in_curr.usb_type_max);
		अगर (ret)
			वापस;
	पूर्ण

	ab8500_अक्षरger_set_usb_connected(di, true);
	ab8500_घातer_supply_changed(di, di->usb_chg.psy);
पूर्ण

/**
 * ab8500_अक्षरger_usb_link_status_work() - work to detect USB type
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Detect the type of USB plugged
 */
अटल व्योम ab8500_अक्षरger_usb_link_status_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक detected_अक्षरgers;
	पूर्णांक ret;
	u8 val;
	u8 link_status;

	काष्ठा ab8500_अक्षरger *di = container_of(work,
		काष्ठा ab8500_अक्षरger, usb_link_status_work);

	/*
	 * Since we can't be sure that the events are received
	 * synchronously, we have the check अगर  is
	 * connected by पढ़ोing the status रेजिस्टर
	 */
	detected_अक्षरgers = ab8500_अक्षरger_detect_अक्षरgers(di, false);
	अगर (detected_अक्षरgers < 0)
		वापस;

	/*
	 * Some अक्षरgers that अवरोधs the USB spec is
	 * identअगरied as invalid by AB8500 and it refuse
	 * to start the अक्षरging process. but by jumping
	 * through a few hoops it can be क्रमced to start.
	 */
	अगर (is_ab8500(di->parent))
		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_USB,
					AB8500_USB_LINE_STAT_REG, &val);
	अन्यथा
		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_USB,
					AB8500_USB_LINK1_STAT_REG, &val);

	अगर (ret >= 0)
		dev_dbg(di->dev, "UsbLineStatus register = 0x%02x\n", val);
	अन्यथा
		dev_dbg(di->dev, "Error reading USB link status\n");

	अगर (is_ab8500(di->parent))
		link_status = AB8500_USB_LINK_STATUS;
	अन्यथा
		link_status = AB8505_USB_LINK_STATUS;

	अगर (detected_अक्षरgers & USB_PW_CONN) अणु
		अगर (((val & link_status) >> USB_LINK_STATUS_SHIFT) ==
				USB_STAT_NOT_VALID_LINK &&
				di->invalid_अक्षरger_detect_state == 0) अणु
			dev_dbg(di->dev,
					"Invalid charger detected, state= 0\n");
			/*Enable अक्षरger*/
			abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
					AB8500_CHARGER, AB8500_USBCH_CTRL1_REG,
					USB_CH_ENA, USB_CH_ENA);
			/*Enable अक्षरger detection*/
			abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
					AB8500_USB, AB8500_USB_LINE_CTRL2_REG,
					USB_CH_DET, USB_CH_DET);
			di->invalid_अक्षरger_detect_state = 1;
			/*निकास and रुको क्रम new link status पूर्णांकerrupt.*/
			वापस;

		पूर्ण
		अगर (di->invalid_अक्षरger_detect_state == 1) अणु
			dev_dbg(di->dev,
					"Invalid charger detected, state= 1\n");
			/*Stop अक्षरger detection*/
			abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
					AB8500_USB, AB8500_USB_LINE_CTRL2_REG,
					USB_CH_DET, 0x00);
			/*Check link status*/
			अगर (is_ab8500(di->parent))
				ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
					AB8500_USB, AB8500_USB_LINE_STAT_REG,
					&val);
			अन्यथा
				ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
					AB8500_USB, AB8500_USB_LINK1_STAT_REG,
					&val);

			dev_dbg(di->dev, "USB link status= 0x%02x\n",
				(val & link_status) >> USB_LINK_STATUS_SHIFT);
			di->invalid_अक्षरger_detect_state = 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		di->invalid_अक्षरger_detect_state = 0;
	पूर्ण

	अगर (!(detected_अक्षरgers & USB_PW_CONN)) अणु
		di->vbus_detected = false;
		ab8500_अक्षरger_set_usb_connected(di, false);
		ab8500_घातer_supply_changed(di, di->usb_chg.psy);
		वापस;
	पूर्ण

	dev_dbg(di->dev,"%s di->vbus_detected = true\n",__func__);
	di->vbus_detected = true;
	ret = ab8500_अक्षरger_पढ़ो_usb_type(di);
	अगर (ret) अणु
		अगर (ret == -ENXIO) अणु
			/* No valid अक्षरger type detected */
			ab8500_अक्षरger_set_usb_connected(di, false);
			ab8500_घातer_supply_changed(di, di->usb_chg.psy);
		पूर्ण
		वापस;
	पूर्ण

	अगर (di->usb_device_is_unrecognised) अणु
		dev_dbg(di->dev,
			"Potential Legacy Charger device. "
			"Delay work for %d msec for USB enum "
			"to finish",
			WAIT_ACA_RID_ENUMERATION);
		queue_delayed_work(di->अक्षरger_wq,
				   &di->attach_work,
				   msecs_to_jअगरfies(WAIT_ACA_RID_ENUMERATION));
	पूर्ण अन्यथा अगर (di->is_aca_rid == 1) अणु
		/* Only रुको once */
		di->is_aca_rid++;
		dev_dbg(di->dev,
			"%s Wait %d msec for USB enum to finish",
			__func__, WAIT_ACA_RID_ENUMERATION);
		queue_delayed_work(di->अक्षरger_wq,
				   &di->attach_work,
				   msecs_to_jअगरfies(WAIT_ACA_RID_ENUMERATION));
	पूर्ण अन्यथा अणु
		queue_delayed_work(di->अक्षरger_wq,
				   &di->attach_work,
				   0);
	पूर्ण
पूर्ण

अटल व्योम ab8500_अक्षरger_usb_state_changed_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	काष्ठा ab8500_अक्षरger *di = container_of(work,
		काष्ठा ab8500_अक्षरger, usb_state_changed_work.work);

	अगर (!di->vbus_detected)	अणु
		dev_dbg(di->dev,
			"%s !di->vbus_detected\n",
			__func__);
		वापस;
	पूर्ण

	spin_lock_irqsave(&di->usb_state.usb_lock, flags);
	di->usb_state.state = di->usb_state.state_पंचांगp;
	di->usb_state.usb_current = di->usb_state.usb_current_पंचांगp;
	spin_unlock_irqrestore(&di->usb_state.usb_lock, flags);

	dev_dbg(di->dev, "%s USB state: 0x%02x mA: %d\n",
		__func__, di->usb_state.state, di->usb_state.usb_current);

	चयन (di->usb_state.state) अणु
	हाल AB8500_BM_USB_STATE_RESET_HS:
	हाल AB8500_BM_USB_STATE_RESET_FS:
	हाल AB8500_BM_USB_STATE_SUSPEND:
	हाल AB8500_BM_USB_STATE_MAX:
		ab8500_अक्षरger_set_usb_connected(di, false);
		ab8500_घातer_supply_changed(di, di->usb_chg.psy);
		अवरोध;

	हाल AB8500_BM_USB_STATE_RESUME:
		/*
		 * when suspend->resume there should be delay
		 * of 1sec क्रम enabling अक्षरging
		 */
		msleep(1000);
		fallthrough;
	हाल AB8500_BM_USB_STATE_CONFIGURED:
		/*
		 * USB is configured, enable अक्षरging with the अक्षरging
		 * input current obtained from USB driver
		 */
		अगर (!ab8500_अक्षरger_get_usb_cur(di)) अणु
			/* Update maximum input current */
			ret = ab8500_अक्षरger_set_vbus_in_curr(di,
					di->max_usb_in_curr.usb_type_max);
			अगर (ret)
				वापस;

			ab8500_अक्षरger_set_usb_connected(di, true);
			ab8500_घातer_supply_changed(di, di->usb_chg.psy);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ab8500_अक्षरger_check_usbअक्षरgernotok_work() - check USB chg not ok status
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Work queue function क्रम checking the USB अक्षरger Not OK status
 */
अटल व्योम ab8500_अक्षरger_check_usbअक्षरgernotok_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	u8 reg_value;
	bool prev_status;

	काष्ठा ab8500_अक्षरger *di = container_of(work,
		काष्ठा ab8500_अक्षरger, check_usbchgnotok_work.work);

	/* Check अगर the status bit क्रम usbअक्षरgernotok is still active */
	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_CHARGER, AB8500_CH_USBCH_STAT2_REG, &reg_value);
	अगर (ret < 0) अणु
		dev_err(di->dev, "%s ab8500 read failed\n", __func__);
		वापस;
	पूर्ण
	prev_status = di->flags.usbअक्षरgernotok;

	अगर (reg_value & VBUS_CH_NOK) अणु
		di->flags.usbअक्षरgernotok = true;
		/* Check again in 1sec */
		queue_delayed_work(di->अक्षरger_wq,
			&di->check_usbchgnotok_work, HZ);
	पूर्ण अन्यथा अणु
		di->flags.usbअक्षरgernotok = false;
		di->flags.vbus_collapse = false;
	पूर्ण

	अगर (prev_status != di->flags.usbअक्षरgernotok)
		ab8500_घातer_supply_changed(di, di->usb_chg.psy);
पूर्ण

/**
 * ab8500_अक्षरger_check_मुख्य_thermal_prot_work() - check मुख्य thermal status
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Work queue function क्रम checking the Main thermal prot status
 */
अटल व्योम ab8500_अक्षरger_check_मुख्य_thermal_prot_work(
	काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	u8 reg_value;

	काष्ठा ab8500_अक्षरger *di = container_of(work,
		काष्ठा ab8500_अक्षरger, check_मुख्य_thermal_prot_work);

	/* Check अगर the status bit क्रम मुख्य_thermal_prot is still active */
	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_CHARGER, AB8500_CH_STATUS2_REG, &reg_value);
	अगर (ret < 0) अणु
		dev_err(di->dev, "%s ab8500 read failed\n", __func__);
		वापस;
	पूर्ण
	अगर (reg_value & MAIN_CH_TH_PROT)
		di->flags.मुख्य_thermal_prot = true;
	अन्यथा
		di->flags.मुख्य_thermal_prot = false;

	ab8500_घातer_supply_changed(di, di->ac_chg.psy);
पूर्ण

/**
 * ab8500_अक्षरger_check_usb_thermal_prot_work() - check usb thermal status
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Work queue function क्रम checking the USB thermal prot status
 */
अटल व्योम ab8500_अक्षरger_check_usb_thermal_prot_work(
	काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	u8 reg_value;

	काष्ठा ab8500_अक्षरger *di = container_of(work,
		काष्ठा ab8500_अक्षरger, check_usb_thermal_prot_work);

	/* Check अगर the status bit क्रम usb_thermal_prot is still active */
	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_CHARGER, AB8500_CH_USBCH_STAT2_REG, &reg_value);
	अगर (ret < 0) अणु
		dev_err(di->dev, "%s ab8500 read failed\n", __func__);
		वापस;
	पूर्ण
	अगर (reg_value & USB_CH_TH_PROT)
		di->flags.usb_thermal_prot = true;
	अन्यथा
		di->flags.usb_thermal_prot = false;

	ab8500_घातer_supply_changed(di, di->usb_chg.psy);
पूर्ण

/**
 * ab8500_अक्षरger_मुख्यchunplugdet_handler() - मुख्य अक्षरger unplugged
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_अक्षरger_मुख्यchunplugdet_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_अक्षरger *di = _di;

	dev_dbg(di->dev, "Main charger unplugged\n");
	queue_work(di->अक्षरger_wq, &di->ac_work);

	cancel_delayed_work_sync(&di->ac_अक्षरger_attached_work);
	mutex_lock(&di->अक्षरger_attached_mutex);
	mutex_unlock(&di->अक्षरger_attached_mutex);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_अक्षरger_मुख्यchplugdet_handler() - मुख्य अक्षरger plugged
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_अक्षरger_मुख्यchplugdet_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_अक्षरger *di = _di;

	dev_dbg(di->dev, "Main charger plugged\n");
	queue_work(di->अक्षरger_wq, &di->ac_work);

	mutex_lock(&di->अक्षरger_attached_mutex);
	mutex_unlock(&di->अक्षरger_attached_mutex);

	अगर (is_ab8500(di->parent))
		queue_delayed_work(di->अक्षरger_wq,
			   &di->ac_अक्षरger_attached_work,
			   HZ);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_अक्षरger_मुख्यextchnotok_handler() - मुख्य अक्षरger not ok
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_अक्षरger_मुख्यextchnotok_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_अक्षरger *di = _di;

	dev_dbg(di->dev, "Main charger not ok\n");
	di->flags.मुख्यextchnotok = true;
	ab8500_घातer_supply_changed(di, di->ac_chg.psy);

	/* Schedule a new HW failure check */
	queue_delayed_work(di->अक्षरger_wq, &di->check_hw_failure_work, 0);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_अक्षरger_मुख्यchthprotr_handler() - Die temp is above मुख्य अक्षरger
 * thermal protection threshold
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_अक्षरger_मुख्यchthprotr_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_अक्षरger *di = _di;

	dev_dbg(di->dev,
		"Die temp above Main charger thermal protection threshold\n");
	queue_work(di->अक्षरger_wq, &di->check_मुख्य_thermal_prot_work);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_अक्षरger_मुख्यchthprotf_handler() - Die temp is below मुख्य अक्षरger
 * thermal protection threshold
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_अक्षरger_मुख्यchthprotf_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_अक्षरger *di = _di;

	dev_dbg(di->dev,
		"Die temp ok for Main charger thermal protection threshold\n");
	queue_work(di->अक्षरger_wq, &di->check_मुख्य_thermal_prot_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ab8500_अक्षरger_vbus_drop_end_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ab8500_अक्षरger *di = container_of(work,
		काष्ठा ab8500_अक्षरger, vbus_drop_end_work.work);
	पूर्णांक ret, curr;
	u8 reg_value;

	di->flags.vbus_drop_end = false;

	/* Reset the drop counter */
	abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
				  AB8500_CHARGER, AB8500_CHARGER_CTRL, 0x01);

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
			AB8500_CH_USBCH_STAT2_REG, &reg_value);
	अगर (ret < 0) अणु
		dev_err(di->dev, "%s read failed\n", __func__);
		वापस;
	पूर्ण

	curr = di->bm->chg_input_curr[
		reg_value >> AUTO_VBUS_IN_CURR_LIM_SHIFT];

	अगर (di->max_usb_in_curr.calculated_max != curr) अणु
		/* USB source is collapsing */
		di->max_usb_in_curr.calculated_max = curr;
		dev_dbg(di->dev,
			 "VBUS input current limiting to %d mA\n",
			 di->max_usb_in_curr.calculated_max);
	पूर्ण अन्यथा अणु
		/*
		 * USB source can not give more than this amount.
		 * Taking more will collapse the source.
		 */
		di->max_usb_in_curr.set_max =
			di->max_usb_in_curr.calculated_max;
		dev_dbg(di->dev,
			 "VBUS input current limited to %d mA\n",
			 di->max_usb_in_curr.set_max);
	पूर्ण

	अगर (di->usb.अक्षरger_connected)
		ab8500_अक्षरger_set_vbus_in_curr(di,
					di->max_usb_in_curr.usb_type_max);
पूर्ण

/**
 * ab8500_अक्षरger_vbusdetf_handler() - VBUS falling detected
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_अक्षरger_vbusdetf_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_अक्षरger *di = _di;

	di->vbus_detected = false;
	dev_dbg(di->dev, "VBUS falling detected\n");
	queue_work(di->अक्षरger_wq, &di->detect_usb_type_work);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_अक्षरger_vbusdetr_handler() - VBUS rising detected
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_अक्षरger_vbusdetr_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_अक्षरger *di = _di;

	di->vbus_detected = true;
	dev_dbg(di->dev, "VBUS rising detected\n");

	queue_work(di->अक्षरger_wq, &di->detect_usb_type_work);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_अक्षरger_usblinkstatus_handler() - USB link status has changed
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_अक्षरger_usblinkstatus_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_अक्षरger *di = _di;

	dev_dbg(di->dev, "USB link status changed\n");

	queue_work(di->अक्षरger_wq, &di->usb_link_status_work);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_अक्षरger_usbchthprotr_handler() - Die temp is above usb अक्षरger
 * thermal protection threshold
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_अक्षरger_usbchthprotr_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_अक्षरger *di = _di;

	dev_dbg(di->dev,
		"Die temp above USB charger thermal protection threshold\n");
	queue_work(di->अक्षरger_wq, &di->check_usb_thermal_prot_work);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_अक्षरger_usbchthprotf_handler() - Die temp is below usb अक्षरger
 * thermal protection threshold
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_अक्षरger_usbchthprotf_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_अक्षरger *di = _di;

	dev_dbg(di->dev,
		"Die temp ok for USB charger thermal protection threshold\n");
	queue_work(di->अक्षरger_wq, &di->check_usb_thermal_prot_work);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_अक्षरger_usbअक्षरgernotokr_handler() - USB अक्षरger not ok detected
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_अक्षरger_usbअक्षरgernotokr_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_अक्षरger *di = _di;

	dev_dbg(di->dev, "Not allowed USB charger detected\n");
	queue_delayed_work(di->अक्षरger_wq, &di->check_usbchgnotok_work, 0);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_अक्षरger_chwdexp_handler() - Charger watchकरोg expired
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_अक्षरger_chwdexp_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_अक्षरger *di = _di;

	dev_dbg(di->dev, "Charger watchdog expired\n");

	/*
	 * The अक्षरger that was online when the watchकरोg expired
	 * needs to be restarted क्रम अक्षरging to start again
	 */
	अगर (di->ac.अक्षरger_online) अणु
		di->ac.wd_expired = true;
		ab8500_घातer_supply_changed(di, di->ac_chg.psy);
	पूर्ण
	अगर (di->usb.अक्षरger_online) अणु
		di->usb.wd_expired = true;
		ab8500_घातer_supply_changed(di, di->usb_chg.psy);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_अक्षरger_vbuschdrखोलोd_handler() - VBUS drop हटाओd
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_अक्षरger_vbuschdrखोलोd_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_अक्षरger *di = _di;

	dev_dbg(di->dev, "VBUS charger drop ended\n");
	di->flags.vbus_drop_end = true;

	/*
	 * VBUS might have dropped due to bad connection.
	 * Schedule a new input limit set to the value SW requests.
	 */
	queue_delayed_work(di->अक्षरger_wq, &di->vbus_drop_end_work,
			   round_jअगरfies(VBUS_IN_CURR_LIM_RETRY_SET_TIME * HZ));

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_अक्षरger_vbusovv_handler() - VBUS overvoltage detected
 * @irq:       पूर्णांकerrupt number
 * @_di:       poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_अक्षरger_vbusovv_handler(पूर्णांक irq, व्योम *_di)
अणु
	काष्ठा ab8500_अक्षरger *di = _di;

	dev_dbg(di->dev, "VBUS overvoltage detected\n");
	di->flags.vbus_ovv = true;
	ab8500_घातer_supply_changed(di, di->usb_chg.psy);

	/* Schedule a new HW failure check */
	queue_delayed_work(di->अक्षरger_wq, &di->check_hw_failure_work, 0);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ab8500_अक्षरger_ac_get_property() - get the ac/मुख्यs properties
 * @psy:       poपूर्णांकer to the घातer_supply काष्ठाure
 * @psp:       poपूर्णांकer to the घातer_supply_property काष्ठाure
 * @val:       poपूर्णांकer to the घातer_supply_propval जोड़
 *
 * This function माला_लो called when an application tries to get the ac/मुख्यs
 * properties by पढ़ोing the sysfs files.
 * AC/Mains properties are online, present and voltage.
 * online:     ac/मुख्यs अक्षरging is in progress or not
 * present:    presence of the ac/मुख्यs
 * voltage:    AC/Mains voltage
 * Returns error code in हाल of failure अन्यथा 0(on success)
 */
अटल पूर्णांक ab8500_अक्षरger_ac_get_property(काष्ठा घातer_supply *psy,
	क्रमागत घातer_supply_property psp,
	जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ab8500_अक्षरger *di;
	पूर्णांक ret;

	di = to_ab8500_अक्षरger_ac_device_info(psy_to_ux500_अक्षरger(psy));

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_HEALTH:
		अगर (di->flags.मुख्यextchnotok)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		अन्यथा अगर (di->ac.wd_expired || di->usb.wd_expired)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_DEAD;
		अन्यथा अगर (di->flags.मुख्य_thermal_prot)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = di->ac.अक्षरger_online;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = di->ac.अक्षरger_connected;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = ab8500_अक्षरger_get_ac_voltage(di);
		अगर (ret >= 0)
			di->ac.अक्षरger_voltage = ret;
		/* On error, use previous value */
		val->पूर्णांकval = di->ac.अक्षरger_voltage * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
		/*
		 * This property is used to indicate when CV mode is entered
		 * क्रम the AC अक्षरger
		 */
		di->ac.cv_active = ab8500_अक्षरger_ac_cv(di);
		val->पूर्णांकval = di->ac.cv_active;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = ab8500_अक्षरger_get_ac_current(di);
		अगर (ret >= 0)
			di->ac.अक्षरger_current = ret;
		val->पूर्णांकval = di->ac.अक्षरger_current * 1000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ab8500_अक्षरger_usb_get_property() - get the usb properties
 * @psy:        poपूर्णांकer to the घातer_supply काष्ठाure
 * @psp:        poपूर्णांकer to the घातer_supply_property काष्ठाure
 * @val:        poपूर्णांकer to the घातer_supply_propval जोड़
 *
 * This function माला_लो called when an application tries to get the usb
 * properties by पढ़ोing the sysfs files.
 * USB properties are online, present and voltage.
 * online:     usb अक्षरging is in progress or not
 * present:    presence of the usb
 * voltage:    vbus voltage
 * Returns error code in हाल of failure अन्यथा 0(on success)
 */
अटल पूर्णांक ab8500_अक्षरger_usb_get_property(काष्ठा घातer_supply *psy,
	क्रमागत घातer_supply_property psp,
	जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ab8500_अक्षरger *di;
	पूर्णांक ret;

	di = to_ab8500_अक्षरger_usb_device_info(psy_to_ux500_अक्षरger(psy));

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_HEALTH:
		अगर (di->flags.usbअक्षरgernotok)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		अन्यथा अगर (di->ac.wd_expired || di->usb.wd_expired)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_DEAD;
		अन्यथा अगर (di->flags.usb_thermal_prot)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
		अन्यथा अगर (di->flags.vbus_ovv)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = di->usb.अक्षरger_online;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = di->usb.अक्षरger_connected;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = ab8500_अक्षरger_get_vbus_voltage(di);
		अगर (ret >= 0)
			di->usb.अक्षरger_voltage = ret;
		val->पूर्णांकval = di->usb.अक्षरger_voltage * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
		/*
		 * This property is used to indicate when CV mode is entered
		 * क्रम the USB अक्षरger
		 */
		di->usb.cv_active = ab8500_अक्षरger_usb_cv(di);
		val->पूर्णांकval = di->usb.cv_active;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = ab8500_अक्षरger_get_usb_current(di);
		अगर (ret >= 0)
			di->usb.अक्षरger_current = ret;
		val->पूर्णांकval = di->usb.अक्षरger_current * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		/*
		 * This property is used to indicate when VBUS has collapsed
		 * due to too high output current from the USB अक्षरger
		 */
		अगर (di->flags.vbus_collapse)
			val->पूर्णांकval = 1;
		अन्यथा
			val->पूर्णांकval = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ab8500_अक्षरger_init_hw_रेजिस्टरs() - Set up अक्षरger related रेजिस्टरs
 * @di:		poपूर्णांकer to the ab8500_अक्षरger काष्ठाure
 *
 * Set up अक्षरger OVV, watchकरोg and maximum voltage रेजिस्टरs as well as
 * अक्षरging of the backup battery
 */
अटल पूर्णांक ab8500_अक्षरger_init_hw_रेजिस्टरs(काष्ठा ab8500_अक्षरger *di)
अणु
	पूर्णांक ret = 0;

	/* Setup maximum अक्षरger current and voltage क्रम ABB cut2.0 */
	अगर (!is_ab8500_1p1_or_earlier(di->parent)) अणु
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_CHARGER,
			AB8500_CH_VOLT_LVL_MAX_REG, CH_VOL_LVL_4P6);
		अगर (ret) अणु
			dev_err(di->dev,
				"failed to set CH_VOLT_LVL_MAX_REG\n");
			जाओ out;
		पूर्ण

		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_CHARGER, AB8500_CH_OPT_CRNTLVL_MAX_REG,
			CH_OP_CUR_LVL_1P6);
		अगर (ret) अणु
			dev_err(di->dev,
				"failed to set CH_OPT_CRNTLVL_MAX_REG\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (is_ab8505_2p0(di->parent))
		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_CHARGER,
			AB8500_USBCH_CTRL2_REG,
			VBUS_AUTO_IN_CURR_LIM_ENA,
			VBUS_AUTO_IN_CURR_LIM_ENA);
	अन्यथा
		/*
		 * VBUS OVV set to 6.3V and enable स्वतःmatic current limitation
		 */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
			AB8500_CHARGER,
			AB8500_USBCH_CTRL2_REG,
			VBUS_OVV_SELECT_6P3V | VBUS_AUTO_IN_CURR_LIM_ENA);
	अगर (ret) अणु
		dev_err(di->dev,
			"failed to set automatic current limitation\n");
		जाओ out;
	पूर्ण

	/* Enable मुख्य watchकरोg in OTP */
	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_OTP_EMUL, AB8500_OTP_CONF_15, OTP_ENABLE_WD);
	अगर (ret) अणु
		dev_err(di->dev, "failed to enable main WD in OTP\n");
		जाओ out;
	पूर्ण

	/* Enable मुख्य watchकरोg */
	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_SYS_CTRL2_BLOCK,
		AB8500_MAIN_WDOG_CTRL_REG, MAIN_WDOG_ENA);
	अगर (ret) अणु
		dev_err(di->dev, "failed to enable main watchdog\n");
		जाओ out;
	पूर्ण

	/*
	 * Due to पूर्णांकernal synchronisation, Enable and Kick watchकरोg bits
	 * cannot be enabled in a single ग_लिखो.
	 * A minimum delay of 2*32 kHz period (62.5तगs) must be inserted
	 * between writing Enable then Kick bits.
	 */
	udelay(63);

	/* Kick मुख्य watchकरोg */
	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_SYS_CTRL2_BLOCK,
		AB8500_MAIN_WDOG_CTRL_REG,
		(MAIN_WDOG_ENA | MAIN_WDOG_KICK));
	अगर (ret) अणु
		dev_err(di->dev, "failed to kick main watchdog\n");
		जाओ out;
	पूर्ण

	/* Disable मुख्य watchकरोg */
	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_SYS_CTRL2_BLOCK,
		AB8500_MAIN_WDOG_CTRL_REG, MAIN_WDOG_DIS);
	अगर (ret) अणु
		dev_err(di->dev, "failed to disable main watchdog\n");
		जाओ out;
	पूर्ण

	/* Set watchकरोg समयout */
	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
		AB8500_CH_WD_TIMER_REG, WD_TIMER);
	अगर (ret) अणु
		dev_err(di->dev, "failed to set charger watchdog timeout\n");
		जाओ out;
	पूर्ण

	ret = ab8500_अक्षरger_led_en(di, false);
	अगर (ret < 0) अणु
		dev_err(di->dev, "failed to disable LED\n");
		जाओ out;
	पूर्ण

	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_RTC,
		AB8500_RTC_BACKUP_CHG_REG,
		(di->bm->bkup_bat_v & 0x3) | di->bm->bkup_bat_i);
	अगर (ret) अणु
		dev_err(di->dev, "failed to setup backup battery charging\n");
		जाओ out;
	पूर्ण

	/* Enable backup battery अक्षरging */
	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_RTC, AB8500_RTC_CTRL_REG,
		RTC_BUP_CH_ENA, RTC_BUP_CH_ENA);
	अगर (ret < 0) अणु
		dev_err(di->dev, "%s mask and set failed\n", __func__);
		जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * ab8500 अक्षरger driver पूर्णांकerrupts and their respective isr
 */
अटल काष्ठा ab8500_अक्षरger_पूर्णांकerrupts ab8500_अक्षरger_irq[] = अणु
	अणु"MAIN_CH_UNPLUG_DET", ab8500_अक्षरger_मुख्यchunplugdet_handlerपूर्ण,
	अणु"MAIN_CHARGE_PLUG_DET", ab8500_अक्षरger_मुख्यchplugdet_handlerपूर्ण,
	अणु"MAIN_EXT_CH_NOT_OK", ab8500_अक्षरger_मुख्यextchnotok_handlerपूर्ण,
	अणु"MAIN_CH_TH_PROT_R", ab8500_अक्षरger_मुख्यchthprotr_handlerपूर्ण,
	अणु"MAIN_CH_TH_PROT_F", ab8500_अक्षरger_मुख्यchthprotf_handlerपूर्ण,
	अणु"VBUS_DET_F", ab8500_अक्षरger_vbusdetf_handlerपूर्ण,
	अणु"VBUS_DET_R", ab8500_अक्षरger_vbusdetr_handlerपूर्ण,
	अणु"USB_LINK_STATUS", ab8500_अक्षरger_usblinkstatus_handlerपूर्ण,
	अणु"USB_CH_TH_PROT_R", ab8500_अक्षरger_usbchthprotr_handlerपूर्ण,
	अणु"USB_CH_TH_PROT_F", ab8500_अक्षरger_usbchthprotf_handlerपूर्ण,
	अणु"USB_CHARGER_NOT_OKR", ab8500_अक्षरger_usbअक्षरgernotokr_handlerपूर्ण,
	अणु"VBUS_OVV", ab8500_अक्षरger_vbusovv_handlerपूर्ण,
	अणु"CH_WD_EXP", ab8500_अक्षरger_chwdexp_handlerपूर्ण,
	अणु"VBUS_CH_DROP_END", ab8500_अक्षरger_vbuschdrखोलोd_handlerपूर्ण,
पूर्ण;

अटल पूर्णांक ab8500_अक्षरger_usb_notअगरier_call(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ event, व्योम *घातer)
अणु
	काष्ठा ab8500_अक्षरger *di =
		container_of(nb, काष्ठा ab8500_अक्षरger, nb);
	क्रमागत ab8500_usb_state bm_usb_state;
	अचिन्हित mA = *((अचिन्हित *)घातer);

	अगर (!di)
		वापस NOTIFY_DONE;

	अगर (event != USB_EVENT_VBUS) अणु
		dev_dbg(di->dev, "not a standard host, returning\n");
		वापस NOTIFY_DONE;
	पूर्ण

	/* TODO: State is fabricate  here. See अगर अक्षरger really needs USB
	 * state or अगर mA is enough
	 */
	अगर ((di->usb_state.usb_current == 2) && (mA > 2))
		bm_usb_state = AB8500_BM_USB_STATE_RESUME;
	अन्यथा अगर (mA == 0)
		bm_usb_state = AB8500_BM_USB_STATE_RESET_HS;
	अन्यथा अगर (mA == 2)
		bm_usb_state = AB8500_BM_USB_STATE_SUSPEND;
	अन्यथा अगर (mA >= 8) /* 8, 100, 500 */
		bm_usb_state = AB8500_BM_USB_STATE_CONFIGURED;
	अन्यथा /* Should never occur */
		bm_usb_state = AB8500_BM_USB_STATE_RESET_FS;

	dev_dbg(di->dev, "%s usb_state: 0x%02x mA: %d\n",
		__func__, bm_usb_state, mA);

	spin_lock(&di->usb_state.usb_lock);
	di->usb_state.state_पंचांगp = bm_usb_state;
	di->usb_state.usb_current_पंचांगp = mA;
	spin_unlock(&di->usb_state.usb_lock);

	/*
	 * रुको क्रम some समय until you get updates from the usb stack
	 * and negotiations are completed
	 */
	queue_delayed_work(di->अक्षरger_wq, &di->usb_state_changed_work, HZ/2);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक __maybe_unused ab8500_अक्षरger_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा ab8500_अक्षरger *di = dev_get_drvdata(dev);

	/*
	 * For ABB revision 1.0 and 1.1 there is a bug in the watchकरोg
	 * logic. That means we have to continuously kick the अक्षरger
	 * watchकरोg even when no अक्षरger is connected. This is only
	 * valid once the AC अक्षरger has been enabled. This is
	 * a bug that is not handled by the algorithm and the
	 * watchकरोg have to be kicked by the अक्षरger driver
	 * when the AC अक्षरger is disabled
	 */
	अगर (di->ac_conn && is_ab8500_1p1_or_earlier(di->parent)) अणु
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(di->dev, AB8500_CHARGER,
			AB8500_CHARG_WD_CTRL, CHARG_WD_KICK);
		अगर (ret)
			dev_err(di->dev, "Failed to kick WD!\n");

		/* If not alपढ़ोy pending start a new समयr */
		queue_delayed_work(di->अक्षरger_wq, &di->kick_wd_work,
				   round_jअगरfies(WD_KICK_INTERVAL));
	पूर्ण

	/* If we still have a HW failure, schedule a new check */
	अगर (di->flags.मुख्यextchnotok || di->flags.vbus_ovv) अणु
		queue_delayed_work(di->अक्षरger_wq,
			&di->check_hw_failure_work, 0);
	पूर्ण

	अगर (di->flags.vbus_drop_end)
		queue_delayed_work(di->अक्षरger_wq, &di->vbus_drop_end_work, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ab8500_अक्षरger_suspend(काष्ठा device *dev)
अणु
	काष्ठा ab8500_अक्षरger *di = dev_get_drvdata(dev);

	/* Cancel any pending jobs */
	cancel_delayed_work(&di->check_hw_failure_work);
	cancel_delayed_work(&di->vbus_drop_end_work);

	flush_delayed_work(&di->attach_work);
	flush_delayed_work(&di->usb_अक्षरger_attached_work);
	flush_delayed_work(&di->ac_अक्षरger_attached_work);
	flush_delayed_work(&di->check_usbchgnotok_work);
	flush_delayed_work(&di->check_vbat_work);
	flush_delayed_work(&di->kick_wd_work);

	flush_work(&di->usb_link_status_work);
	flush_work(&di->ac_work);
	flush_work(&di->detect_usb_type_work);

	अगर (atomic_पढ़ो(&di->current_stepping_sessions))
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block अक्षरger_nb = अणु
	.notअगरier_call = ab8500_बाह्यal_अक्षरger_prepare,
पूर्ण;

अटल पूर्णांक ab8500_अक्षरger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ab8500_अक्षरger *di = platक्रमm_get_drvdata(pdev);
	पूर्णांक i, irq, ret;

	/* Disable AC अक्षरging */
	ab8500_अक्षरger_ac_en(&di->ac_chg, false, 0, 0);

	/* Disable USB अक्षरging */
	ab8500_अक्षरger_usb_en(&di->usb_chg, false, 0, 0);

	/* Disable पूर्णांकerrupts */
	क्रम (i = 0; i < ARRAY_SIZE(ab8500_अक्षरger_irq); i++) अणु
		irq = platक्रमm_get_irq_byname(pdev, ab8500_अक्षरger_irq[i].name);
		मुक्त_irq(irq, di);
	पूर्ण

	/* Backup battery voltage and current disable */
	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(di->dev,
		AB8500_RTC, AB8500_RTC_CTRL_REG, RTC_BUP_CH_ENA, 0);
	अगर (ret < 0)
		dev_err(di->dev, "%s mask and set failed\n", __func__);

	usb_unरेजिस्टर_notअगरier(di->usb_phy, &di->nb);
	usb_put_phy(di->usb_phy);

	/* Delete the work queue */
	destroy_workqueue(di->अक्षरger_wq);

	/* Unरेजिस्टर बाह्यal अक्षरger enable notअगरier */
	अगर (!di->ac_chg.enabled)
		blocking_notअगरier_chain_unरेजिस्टर(
			&अक्षरger_notअगरier_list, &अक्षरger_nb);

	flush_scheduled_work();
	अगर (di->usb_chg.enabled)
		घातer_supply_unरेजिस्टर(di->usb_chg.psy);

	अगर (di->ac_chg.enabled && !di->ac_chg.बाह्यal)
		घातer_supply_unरेजिस्टर(di->ac_chg.psy);

	वापस 0;
पूर्ण

अटल अक्षर *supply_पूर्णांकerface[] = अणु
	"ab8500_chargalg",
	"ab8500_fg",
	"ab8500_btemp",
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc ab8500_ac_chg_desc = अणु
	.name		= "ab8500_ac",
	.type		= POWER_SUPPLY_TYPE_MAINS,
	.properties	= ab8500_अक्षरger_ac_props,
	.num_properties	= ARRAY_SIZE(ab8500_अक्षरger_ac_props),
	.get_property	= ab8500_अक्षरger_ac_get_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc ab8500_usb_chg_desc = अणु
	.name		= "ab8500_usb",
	.type		= POWER_SUPPLY_TYPE_USB,
	.properties	= ab8500_अक्षरger_usb_props,
	.num_properties	= ARRAY_SIZE(ab8500_अक्षरger_usb_props),
	.get_property	= ab8500_अक्षरger_usb_get_property,
पूर्ण;

अटल पूर्णांक ab8500_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा घातer_supply_config ac_psy_cfg = अणुपूर्ण, usb_psy_cfg = अणुपूर्ण;
	काष्ठा ab8500_अक्षरger *di;
	पूर्णांक irq, i, अक्षरger_status, ret = 0, ch_stat;
	काष्ठा device *dev = &pdev->dev;

	di = devm_kzalloc(dev, माप(*di), GFP_KERNEL);
	अगर (!di)
		वापस -ENOMEM;

	di->bm = &ab8500_bm_data;

	ret = ab8500_bm_of_probe(dev, np, di->bm);
	अगर (ret) अणु
		dev_err(dev, "failed to get battery information\n");
		वापस ret;
	पूर्ण
	di->स्वतःघातer_cfg = of_property_पढ़ो_bool(np, "autopower_cfg");

	/* get parent data */
	di->dev = dev;
	di->parent = dev_get_drvdata(pdev->dev.parent);

	/* Get ADC channels */
	di->adc_मुख्य_अक्षरger_v = devm_iio_channel_get(dev, "main_charger_v");
	अगर (IS_ERR(di->adc_मुख्य_अक्षरger_v)) अणु
		ret = dev_err_probe(dev, PTR_ERR(di->adc_मुख्य_अक्षरger_v),
				    "failed to get ADC main charger voltage\n");
		वापस ret;
	पूर्ण
	di->adc_मुख्य_अक्षरger_c = devm_iio_channel_get(dev, "main_charger_c");
	अगर (IS_ERR(di->adc_मुख्य_अक्षरger_c)) अणु
		ret = dev_err_probe(dev, PTR_ERR(di->adc_मुख्य_अक्षरger_c),
				    "failed to get ADC main charger current\n");
		वापस ret;
	पूर्ण
	di->adc_vbus_v = devm_iio_channel_get(dev, "vbus_v");
	अगर (IS_ERR(di->adc_vbus_v)) अणु
		ret = dev_err_probe(dev, PTR_ERR(di->adc_vbus_v),
				    "failed to get ADC USB charger voltage\n");
		वापस ret;
	पूर्ण
	di->adc_usb_अक्षरger_c = devm_iio_channel_get(dev, "usb_charger_c");
	अगर (IS_ERR(di->adc_usb_अक्षरger_c)) अणु
		ret = dev_err_probe(dev, PTR_ERR(di->adc_usb_अक्षरger_c),
				    "failed to get ADC USB charger current\n");
		वापस ret;
	पूर्ण

	/* initialize lock */
	spin_lock_init(&di->usb_state.usb_lock);
	mutex_init(&di->usb_ipt_crnt_lock);

	di->स्वतःघातer = false;
	di->invalid_अक्षरger_detect_state = 0;

	/* AC and USB supply config */
	ac_psy_cfg.supplied_to = supply_पूर्णांकerface;
	ac_psy_cfg.num_supplicants = ARRAY_SIZE(supply_पूर्णांकerface);
	ac_psy_cfg.drv_data = &di->ac_chg;
	usb_psy_cfg.supplied_to = supply_पूर्णांकerface;
	usb_psy_cfg.num_supplicants = ARRAY_SIZE(supply_पूर्णांकerface);
	usb_psy_cfg.drv_data = &di->usb_chg;

	/* AC supply */
	/* ux500_अक्षरger sub-class */
	di->ac_chg.ops.enable = &ab8500_अक्षरger_ac_en;
	di->ac_chg.ops.check_enable = &ab8500_अक्षरger_ac_check_enable;
	di->ac_chg.ops.kick_wd = &ab8500_अक्षरger_watchकरोg_kick;
	di->ac_chg.ops.update_curr = &ab8500_अक्षरger_update_अक्षरger_current;
	di->ac_chg.max_out_volt = ab8500_अक्षरger_voltage_map[
		ARRAY_SIZE(ab8500_अक्षरger_voltage_map) - 1];
	di->ac_chg.max_out_curr =
		di->bm->chg_output_curr[di->bm->n_chg_out_curr - 1];
	di->ac_chg.wdt_refresh = CHG_WD_INTERVAL;
	di->ac_chg.enabled = di->bm->ac_enabled;
	di->ac_chg.बाह्यal = false;

	/*notअगरier क्रम बाह्यal अक्षरger enabling*/
	अगर (!di->ac_chg.enabled)
		blocking_notअगरier_chain_रेजिस्टर(
			&अक्षरger_notअगरier_list, &अक्षरger_nb);

	/* USB supply */
	/* ux500_अक्षरger sub-class */
	di->usb_chg.ops.enable = &ab8500_अक्षरger_usb_en;
	di->usb_chg.ops.check_enable = &ab8500_अक्षरger_usb_check_enable;
	di->usb_chg.ops.kick_wd = &ab8500_अक्षरger_watchकरोg_kick;
	di->usb_chg.ops.update_curr = &ab8500_अक्षरger_update_अक्षरger_current;
	di->usb_chg.max_out_volt = ab8500_अक्षरger_voltage_map[
		ARRAY_SIZE(ab8500_अक्षरger_voltage_map) - 1];
	di->usb_chg.max_out_curr =
		di->bm->chg_output_curr[di->bm->n_chg_out_curr - 1];
	di->usb_chg.wdt_refresh = CHG_WD_INTERVAL;
	di->usb_chg.enabled = di->bm->usb_enabled;
	di->usb_chg.बाह्यal = false;
	di->usb_state.usb_current = -1;

	/* Create a work queue क्रम the अक्षरger */
	di->अक्षरger_wq = alloc_ordered_workqueue("ab8500_charger_wq",
						 WQ_MEM_RECLAIM);
	अगर (di->अक्षरger_wq == शून्य) अणु
		dev_err(dev, "failed to create work queue\n");
		वापस -ENOMEM;
	पूर्ण

	mutex_init(&di->अक्षरger_attached_mutex);

	/* Init work क्रम HW failure check */
	INIT_DEFERRABLE_WORK(&di->check_hw_failure_work,
		ab8500_अक्षरger_check_hw_failure_work);
	INIT_DEFERRABLE_WORK(&di->check_usbchgnotok_work,
		ab8500_अक्षरger_check_usbअक्षरgernotok_work);

	INIT_DELAYED_WORK(&di->ac_अक्षरger_attached_work,
			  ab8500_अक्षरger_ac_attached_work);
	INIT_DELAYED_WORK(&di->usb_अक्षरger_attached_work,
			  ab8500_अक्षरger_usb_attached_work);

	/*
	 * For ABB revision 1.0 and 1.1 there is a bug in the watchकरोg
	 * logic. That means we have to continuously kick the अक्षरger
	 * watchकरोg even when no अक्षरger is connected. This is only
	 * valid once the AC अक्षरger has been enabled. This is
	 * a bug that is not handled by the algorithm and the
	 * watchकरोg have to be kicked by the अक्षरger driver
	 * when the AC अक्षरger is disabled
	 */
	INIT_DEFERRABLE_WORK(&di->kick_wd_work,
		ab8500_अक्षरger_kick_watchकरोg_work);

	INIT_DEFERRABLE_WORK(&di->check_vbat_work,
		ab8500_अक्षरger_check_vbat_work);

	INIT_DELAYED_WORK(&di->attach_work,
		ab8500_अक्षरger_usb_link_attach_work);

	INIT_DELAYED_WORK(&di->usb_state_changed_work,
		ab8500_अक्षरger_usb_state_changed_work);

	INIT_DELAYED_WORK(&di->vbus_drop_end_work,
		ab8500_अक्षरger_vbus_drop_end_work);

	/* Init work क्रम अक्षरger detection */
	INIT_WORK(&di->usb_link_status_work,
		ab8500_अक्षरger_usb_link_status_work);
	INIT_WORK(&di->ac_work, ab8500_अक्षरger_ac_work);
	INIT_WORK(&di->detect_usb_type_work,
		ab8500_अक्षरger_detect_usb_type_work);

	/* Init work क्रम checking HW status */
	INIT_WORK(&di->check_मुख्य_thermal_prot_work,
		ab8500_अक्षरger_check_मुख्य_thermal_prot_work);
	INIT_WORK(&di->check_usb_thermal_prot_work,
		ab8500_अक्षरger_check_usb_thermal_prot_work);

	/*
	 * VDD ADC supply needs to be enabled from this driver when there
	 * is a अक्षरger connected to aव्योम erroneous BTEMP_HIGH/LOW
	 * पूर्णांकerrupts during अक्षरging
	 */
	di->regu = devm_regulator_get(dev, "vddadc");
	अगर (IS_ERR(di->regu)) अणु
		ret = PTR_ERR(di->regu);
		dev_err(dev, "failed to get vddadc regulator\n");
		जाओ मुक्त_अक्षरger_wq;
	पूर्ण


	/* Initialize OVV, and other रेजिस्टरs */
	ret = ab8500_अक्षरger_init_hw_रेजिस्टरs(di);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize ABB registers\n");
		जाओ मुक्त_अक्षरger_wq;
	पूर्ण

	/* Register AC अक्षरger class */
	अगर (di->ac_chg.enabled) अणु
		di->ac_chg.psy = घातer_supply_रेजिस्टर(dev,
						       &ab8500_ac_chg_desc,
						       &ac_psy_cfg);
		अगर (IS_ERR(di->ac_chg.psy)) अणु
			dev_err(dev, "failed to register AC charger\n");
			ret = PTR_ERR(di->ac_chg.psy);
			जाओ मुक्त_अक्षरger_wq;
		पूर्ण
	पूर्ण

	/* Register USB अक्षरger class */
	अगर (di->usb_chg.enabled) अणु
		di->usb_chg.psy = घातer_supply_रेजिस्टर(dev,
							&ab8500_usb_chg_desc,
							&usb_psy_cfg);
		अगर (IS_ERR(di->usb_chg.psy)) अणु
			dev_err(dev, "failed to register USB charger\n");
			ret = PTR_ERR(di->usb_chg.psy);
			जाओ मुक्त_ac;
		पूर्ण
	पूर्ण

	di->usb_phy = usb_get_phy(USB_PHY_TYPE_USB2);
	अगर (IS_ERR_OR_शून्य(di->usb_phy)) अणु
		dev_err(dev, "failed to get usb transceiver\n");
		ret = -EINVAL;
		जाओ मुक्त_usb;
	पूर्ण
	di->nb.notअगरier_call = ab8500_अक्षरger_usb_notअगरier_call;
	ret = usb_रेजिस्टर_notअगरier(di->usb_phy, &di->nb);
	अगर (ret) अणु
		dev_err(dev, "failed to register usb notifier\n");
		जाओ put_usb_phy;
	पूर्ण

	/* Identअगरy the connected अक्षरger types during startup */
	अक्षरger_status = ab8500_अक्षरger_detect_अक्षरgers(di, true);
	अगर (अक्षरger_status & AC_PW_CONN) अणु
		di->ac.अक्षरger_connected = 1;
		di->ac_conn = true;
		ab8500_घातer_supply_changed(di, di->ac_chg.psy);
		sysfs_notअगरy(&di->ac_chg.psy->dev.kobj, शून्य, "present");
	पूर्ण

	अगर (अक्षरger_status & USB_PW_CONN) अणु
		di->vbus_detected = true;
		di->vbus_detected_start = true;
		queue_work(di->अक्षरger_wq,
			&di->detect_usb_type_work);
	पूर्ण

	/* Register पूर्णांकerrupts */
	क्रम (i = 0; i < ARRAY_SIZE(ab8500_अक्षरger_irq); i++) अणु
		irq = platक्रमm_get_irq_byname(pdev, ab8500_अक्षरger_irq[i].name);
		अगर (irq < 0) अणु
			ret = irq;
			जाओ मुक्त_irq;
		पूर्ण

		ret = request_thपढ़ोed_irq(irq, शून्य, ab8500_अक्षरger_irq[i].isr,
			IRQF_SHARED | IRQF_NO_SUSPEND | IRQF_ONESHOT,
			ab8500_अक्षरger_irq[i].name, di);

		अगर (ret != 0) अणु
			dev_err(dev, "failed to request %s IRQ %d: %d\n"
				, ab8500_अक्षरger_irq[i].name, irq, ret);
			जाओ मुक्त_irq;
		पूर्ण
		dev_dbg(dev, "Requested %s IRQ %d: %d\n",
			ab8500_अक्षरger_irq[i].name, irq, ret);
	पूर्ण

	platक्रमm_set_drvdata(pdev, di);

	mutex_lock(&di->अक्षरger_attached_mutex);

	ch_stat = ab8500_अक्षरger_detect_अक्षरgers(di, false);

	अगर ((ch_stat & AC_PW_CONN) == AC_PW_CONN) अणु
		अगर (is_ab8500(di->parent))
			queue_delayed_work(di->अक्षरger_wq,
					   &di->ac_अक्षरger_attached_work,
					   HZ);
	पूर्ण
	अगर ((ch_stat & USB_PW_CONN) == USB_PW_CONN) अणु
		अगर (is_ab8500(di->parent))
			queue_delayed_work(di->अक्षरger_wq,
					   &di->usb_अक्षरger_attached_work,
					   HZ);
	पूर्ण

	mutex_unlock(&di->अक्षरger_attached_mutex);

	वापस ret;

मुक्त_irq:
	usb_unरेजिस्टर_notअगरier(di->usb_phy, &di->nb);

	/* We also have to मुक्त all successfully रेजिस्टरed irqs */
	क्रम (i = i - 1; i >= 0; i--) अणु
		irq = platक्रमm_get_irq_byname(pdev, ab8500_अक्षरger_irq[i].name);
		मुक्त_irq(irq, di);
	पूर्ण
put_usb_phy:
	usb_put_phy(di->usb_phy);
मुक्त_usb:
	अगर (di->usb_chg.enabled)
		घातer_supply_unरेजिस्टर(di->usb_chg.psy);
मुक्त_ac:
	अगर (di->ac_chg.enabled)
		घातer_supply_unरेजिस्टर(di->ac_chg.psy);
मुक्त_अक्षरger_wq:
	destroy_workqueue(di->अक्षरger_wq);
	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ab8500_अक्षरger_pm_ops, ab8500_अक्षरger_suspend, ab8500_अक्षरger_resume);

अटल स्थिर काष्ठा of_device_id ab8500_अक्षरger_match[] = अणु
	अणु .compatible = "stericsson,ab8500-charger", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ab8500_अक्षरger_driver = अणु
	.probe = ab8500_अक्षरger_probe,
	.हटाओ = ab8500_अक्षरger_हटाओ,
	.driver = अणु
		.name = "ab8500-charger",
		.of_match_table = ab8500_अक्षरger_match,
		.pm = &ab8500_अक्षरger_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ab8500_अक्षरger_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ab8500_अक्षरger_driver);
पूर्ण

अटल व्योम __निकास ab8500_अक्षरger_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ab8500_अक्षरger_driver);
पूर्ण

subsys_initcall_sync(ab8500_अक्षरger_init);
module_निकास(ab8500_अक्षरger_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Johan Palsson, Karl Komierowski, Arun R Murthy");
MODULE_ALIAS("platform:ab8500-charger");
MODULE_DESCRIPTION("AB8500 charger management driver");
