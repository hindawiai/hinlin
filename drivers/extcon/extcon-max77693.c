<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// extcon-max77693.c - MAX77693 extcon driver to support MAX77693 MUIC
//
// Copyright (C) 2012 Samsung Electrnoics
// Chanwoo Choi <cw00.choi@samsung.com>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/max77693.h>
#समावेश <linux/mfd/max77693-common.h>
#समावेश <linux/mfd/max77693-निजी.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/regmap.h>
#समावेश <linux/irqकरोमुख्य.h>

#घोषणा	DEV_NAME			"max77693-muic"
#घोषणा	DELAY_MS_DEFAULT		20000		/* unit: millisecond */

/*
 * Default value of MAX77693 रेजिस्टर to bring up MUIC device.
 * If user करोn't set some initial value क्रम MUIC device through platक्रमm data,
 * extcon-max77693 driver use 'default_init_data' to bring up base operation
 * of MAX77693 MUIC device.
 */
अटल काष्ठा max77693_reg_data शेष_init_data[] = अणु
	अणु
		/* STATUS2 - [3]ChgDetRun */
		.addr = MAX77693_MUIC_REG_STATUS2,
		.data = MAX77693_STATUS2_CHGDETRUN_MASK,
	पूर्ण, अणु
		/* INTMASK1 - Unmask [3]ADC1KM,[0]ADCM */
		.addr = MAX77693_MUIC_REG_INTMASK1,
		.data = INTMASK1_ADC1K_MASK
			| INTMASK1_ADC_MASK,
	पूर्ण, अणु
		/* INTMASK2 - Unmask [0]ChgTypM */
		.addr = MAX77693_MUIC_REG_INTMASK2,
		.data = INTMASK2_CHGTYP_MASK,
	पूर्ण, अणु
		/* INTMASK3 - Mask all of पूर्णांकerrupts */
		.addr = MAX77693_MUIC_REG_INTMASK3,
		.data = 0x0,
	पूर्ण, अणु
		/* CDETCTRL2 */
		.addr = MAX77693_MUIC_REG_CDETCTRL2,
		.data = CDETCTRL2_VIDRMEN_MASK
			| CDETCTRL2_DXOVPEN_MASK,
	पूर्ण,
पूर्ण;

क्रमागत max77693_muic_adc_debounce_समय अणु
	ADC_DEBOUNCE_TIME_5MS = 0,
	ADC_DEBOUNCE_TIME_10MS,
	ADC_DEBOUNCE_TIME_25MS,
	ADC_DEBOUNCE_TIME_38_62MS,
पूर्ण;

काष्ठा max77693_muic_info अणु
	काष्ठा device *dev;
	काष्ठा max77693_dev *max77693;
	काष्ठा extcon_dev *edev;
	पूर्णांक prev_cable_type;
	पूर्णांक prev_cable_type_gnd;
	पूर्णांक prev_chg_type;
	पूर्णांक prev_button_type;
	u8 status[2];

	पूर्णांक irq;
	काष्ठा work_काष्ठा irq_work;
	काष्ठा mutex mutex;

	/*
	 * Use delayed workqueue to detect cable state and then
	 * notअगरy cable state to notअगरiee/platक्रमm through uevent.
	 * After completing the booting of platक्रमm, the extcon provider
	 * driver should notअगरy cable state to upper layer.
	 */
	काष्ठा delayed_work wq_detcable;

	/* Button of करोck device */
	काष्ठा input_dev *करोck;

	/*
	 * Default usb/uart path whether UART/USB or AUX_UART/AUX_USB
	 * h/w path of COMP2/COMN1 on CONTROL1 रेजिस्टर.
	 */
	पूर्णांक path_usb;
	पूर्णांक path_uart;
पूर्ण;

क्रमागत max77693_muic_cable_group अणु
	MAX77693_CABLE_GROUP_ADC = 0,
	MAX77693_CABLE_GROUP_ADC_GND,
	MAX77693_CABLE_GROUP_CHG,
	MAX77693_CABLE_GROUP_VBVOLT,
पूर्ण;

क्रमागत max77693_muic_अक्षरger_type अणु
	MAX77693_CHARGER_TYPE_NONE = 0,
	MAX77693_CHARGER_TYPE_USB,
	MAX77693_CHARGER_TYPE_DOWNSTREAM_PORT,
	MAX77693_CHARGER_TYPE_DEDICATED_CHG,
	MAX77693_CHARGER_TYPE_APPLE_500MA,
	MAX77693_CHARGER_TYPE_APPLE_1A_2A,
	MAX77693_CHARGER_TYPE_DEAD_BATTERY = 7,
पूर्ण;

/**
 * काष्ठा max77693_muic_irq
 * @irq: the index of irq list of MUIC device.
 * @name: the name of irq.
 * @virq: the भव irq to use irq करोमुख्य
 */
काष्ठा max77693_muic_irq अणु
	अचिन्हित पूर्णांक irq;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक virq;
पूर्ण;

अटल काष्ठा max77693_muic_irq muic_irqs[] = अणु
	अणु MAX77693_MUIC_IRQ_INT1_ADC,		"muic-ADC" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT1_ADC_LOW,	"muic-ADCLOW" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT1_ADC_ERR,	"muic-ADCError" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT1_ADC1K,		"muic-ADC1K" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT2_CHGTYP,	"muic-CHGTYP" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT2_CHGDETREUN,	"muic-CHGDETREUN" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT2_DCDTMR,	"muic-DCDTMR" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT2_DXOVP,		"muic-DXOVP" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT2_VBVOLT,	"muic-VBVOLT" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT2_VIDRM,		"muic-VIDRM" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT3_EOC,		"muic-EOC" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT3_CGMBC,		"muic-CGMBC" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT3_OVP,		"muic-OVP" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT3_MBCCHG_ERR,	"muic-MBCCHG_ERR" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT3_CHG_ENABLED,	"muic-CHG_ENABLED" पूर्ण,
	अणु MAX77693_MUIC_IRQ_INT3_BAT_DET,	"muic-BAT_DET" पूर्ण,
पूर्ण;

/* Define supported accessory type */
क्रमागत max77693_muic_acc_type अणु
	MAX77693_MUIC_ADC_GROUND = 0x0,
	MAX77693_MUIC_ADC_SEND_END_BUTTON,
	MAX77693_MUIC_ADC_REMOTE_S1_BUTTON,
	MAX77693_MUIC_ADC_REMOTE_S2_BUTTON,
	MAX77693_MUIC_ADC_REMOTE_S3_BUTTON,
	MAX77693_MUIC_ADC_REMOTE_S4_BUTTON,
	MAX77693_MUIC_ADC_REMOTE_S5_BUTTON,
	MAX77693_MUIC_ADC_REMOTE_S6_BUTTON,
	MAX77693_MUIC_ADC_REMOTE_S7_BUTTON,
	MAX77693_MUIC_ADC_REMOTE_S8_BUTTON,
	MAX77693_MUIC_ADC_REMOTE_S9_BUTTON,
	MAX77693_MUIC_ADC_REMOTE_S10_BUTTON,
	MAX77693_MUIC_ADC_REMOTE_S11_BUTTON,
	MAX77693_MUIC_ADC_REMOTE_S12_BUTTON,
	MAX77693_MUIC_ADC_RESERVED_ACC_1,
	MAX77693_MUIC_ADC_RESERVED_ACC_2,
	MAX77693_MUIC_ADC_RESERVED_ACC_3,
	MAX77693_MUIC_ADC_RESERVED_ACC_4,
	MAX77693_MUIC_ADC_RESERVED_ACC_5,
	MAX77693_MUIC_ADC_CEA936_AUDIO,
	MAX77693_MUIC_ADC_PHONE_POWERED_DEV,
	MAX77693_MUIC_ADC_TTY_CONVERTER,
	MAX77693_MUIC_ADC_UART_CABLE,
	MAX77693_MUIC_ADC_CEA936A_TYPE1_CHG,
	MAX77693_MUIC_ADC_FACTORY_MODE_USB_OFF,
	MAX77693_MUIC_ADC_FACTORY_MODE_USB_ON,
	MAX77693_MUIC_ADC_AV_CABLE_NOLOAD,
	MAX77693_MUIC_ADC_CEA936A_TYPE2_CHG,
	MAX77693_MUIC_ADC_FACTORY_MODE_UART_OFF,
	MAX77693_MUIC_ADC_FACTORY_MODE_UART_ON,
	MAX77693_MUIC_ADC_AUDIO_MODE_REMOTE,
	MAX77693_MUIC_ADC_OPEN,

	/*
	 * The below accessories have same ADC value so ADCLow and
	 * ADC1K bit is used to separate specअगरic accessory.
	 */
						/* ADC|VBVolot|ADCLow|ADC1K| */
	MAX77693_MUIC_GND_USB_HOST = 0x100,	/* 0x0|      0|     0|    0| */
	MAX77693_MUIC_GND_USB_HOST_VB = 0x104,	/* 0x0|      1|     0|    0| */
	MAX77693_MUIC_GND_AV_CABLE_LOAD = 0x102,/* 0x0|      0|     1|    0| */
	MAX77693_MUIC_GND_MHL = 0x103,		/* 0x0|      0|     1|    1| */
	MAX77693_MUIC_GND_MHL_VB = 0x107,	/* 0x0|      1|     1|    1| */
पूर्ण;

/*
 * MAX77693 MUIC device support below list of accessories(बाह्यal connector)
 */
अटल स्थिर अचिन्हित पूर्णांक max77693_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_CHG_USB_FAST,
	EXTCON_CHG_USB_SLOW,
	EXTCON_CHG_USB_CDP,
	EXTCON_DISP_MHL,
	EXTCON_JIG,
	EXTCON_DOCK,
	EXTCON_NONE,
पूर्ण;

/*
 * max77693_muic_set_debounce_समय - Set the debounce समय of ADC
 * @info: the instance including निजी data of max77693 MUIC
 * @समय: the debounce समय of ADC
 */
अटल पूर्णांक max77693_muic_set_debounce_समय(काष्ठा max77693_muic_info *info,
		क्रमागत max77693_muic_adc_debounce_समय समय)
अणु
	पूर्णांक ret;

	चयन (समय) अणु
	हाल ADC_DEBOUNCE_TIME_5MS:
	हाल ADC_DEBOUNCE_TIME_10MS:
	हाल ADC_DEBOUNCE_TIME_25MS:
	हाल ADC_DEBOUNCE_TIME_38_62MS:
		/*
		 * Don't touch BTLDset, JIGset when you want to change adc
		 * debounce समय. If it ग_लिखोs other than 0 to BTLDset, JIGset
		 * muic device will be reset and loose current state.
		 */
		ret = regmap_ग_लिखो(info->max77693->regmap_muic,
				  MAX77693_MUIC_REG_CTRL3,
				  समय << MAX77693_CONTROL3_ADCDBSET_SHIFT);
		अगर (ret) अणु
			dev_err(info->dev, "failed to set ADC debounce time\n");
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(info->dev, "invalid ADC debounce time\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण;

/*
 * max77693_muic_set_path - Set hardware line according to attached cable
 * @info: the instance including निजी data of max77693 MUIC
 * @value: the path according to attached cable
 * @attached: the state of cable (true:attached, false:detached)
 *
 * The max77693 MUIC device share outside H/W line among a varity of cables
 * so, this function set पूर्णांकernal path of H/W line according to the type of
 * attached cable.
 */
अटल पूर्णांक max77693_muic_set_path(काष्ठा max77693_muic_info *info,
		u8 val, bool attached)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक ctrl1, ctrl2 = 0;

	अगर (attached)
		ctrl1 = val;
	अन्यथा
		ctrl1 = MAX77693_CONTROL1_SW_OPEN;

	ret = regmap_update_bits(info->max77693->regmap_muic,
			MAX77693_MUIC_REG_CTRL1, COMP_SW_MASK, ctrl1);
	अगर (ret < 0) अणु
		dev_err(info->dev, "failed to update MUIC register\n");
		वापस ret;
	पूर्ण

	अगर (attached)
		ctrl2 |= MAX77693_CONTROL2_CPEN_MASK;	/* LowPwr=0, CPEn=1 */
	अन्यथा
		ctrl2 |= MAX77693_CONTROL2_LOWPWR_MASK;	/* LowPwr=1, CPEn=0 */

	ret = regmap_update_bits(info->max77693->regmap_muic,
			MAX77693_MUIC_REG_CTRL2,
			MAX77693_CONTROL2_LOWPWR_MASK | MAX77693_CONTROL2_CPEN_MASK,
			ctrl2);
	अगर (ret < 0) अणु
		dev_err(info->dev, "failed to update MUIC register\n");
		वापस ret;
	पूर्ण

	dev_info(info->dev,
		"CONTROL1 : 0x%02x, CONTROL2 : 0x%02x, state : %s\n",
		ctrl1, ctrl2, attached ? "attached" : "detached");

	वापस 0;
पूर्ण

/*
 * max77693_muic_get_cable_type - Return cable type and check cable state
 * @info: the instance including निजी data of max77693 MUIC
 * @group: the path according to attached cable
 * @attached: store cable state and वापस
 *
 * This function check the cable state either attached or detached,
 * and then भागide precise type of cable according to cable group.
 *	- MAX77693_CABLE_GROUP_ADC
 *	- MAX77693_CABLE_GROUP_ADC_GND
 *	- MAX77693_CABLE_GROUP_CHG
 *	- MAX77693_CABLE_GROUP_VBVOLT
 */
अटल पूर्णांक max77693_muic_get_cable_type(काष्ठा max77693_muic_info *info,
		क्रमागत max77693_muic_cable_group group, bool *attached)
अणु
	पूर्णांक cable_type = 0;
	पूर्णांक adc;
	पूर्णांक adc1k;
	पूर्णांक adclow;
	पूर्णांक vbvolt;
	पूर्णांक chg_type;

	चयन (group) अणु
	हाल MAX77693_CABLE_GROUP_ADC:
		/*
		 * Read ADC value to check cable type and decide cable state
		 * according to cable type
		 */
		adc = info->status[0] & MAX77693_STATUS1_ADC_MASK;
		adc >>= MAX77693_STATUS1_ADC_SHIFT;

		/*
		 * Check current cable state/cable type and store cable type
		 * (info->prev_cable_type) क्रम handling cable when cable is
		 * detached.
		 */
		अगर (adc == MAX77693_MUIC_ADC_OPEN) अणु
			*attached = false;

			cable_type = info->prev_cable_type;
			info->prev_cable_type = MAX77693_MUIC_ADC_OPEN;
		पूर्ण अन्यथा अणु
			*attached = true;

			cable_type = info->prev_cable_type = adc;
		पूर्ण
		अवरोध;
	हाल MAX77693_CABLE_GROUP_ADC_GND:
		/*
		 * Read ADC value to check cable type and decide cable state
		 * according to cable type
		 */
		adc = info->status[0] & MAX77693_STATUS1_ADC_MASK;
		adc >>= MAX77693_STATUS1_ADC_SHIFT;

		/*
		 * Check current cable state/cable type and store cable type
		 * (info->prev_cable_type/_gnd) क्रम handling cable when cable
		 * is detached.
		 */
		अगर (adc == MAX77693_MUIC_ADC_OPEN) अणु
			*attached = false;

			cable_type = info->prev_cable_type_gnd;
			info->prev_cable_type_gnd = MAX77693_MUIC_ADC_OPEN;
		पूर्ण अन्यथा अणु
			*attached = true;

			adclow = info->status[0] & MAX77693_STATUS1_ADCLOW_MASK;
			adclow >>= MAX77693_STATUS1_ADCLOW_SHIFT;
			adc1k = info->status[0] & MAX77693_STATUS1_ADC1K_MASK;
			adc1k >>= MAX77693_STATUS1_ADC1K_SHIFT;

			vbvolt = info->status[1] & MAX77693_STATUS2_VBVOLT_MASK;
			vbvolt >>= MAX77693_STATUS2_VBVOLT_SHIFT;

			/**
			 * [0x1|VBVolt|ADCLow|ADC1K]
			 * [0x1|     0|     0|    0] USB_HOST
			 * [0x1|     1|     0|    0] USB_HSOT_VB
			 * [0x1|     0|     1|    0] Audio Video cable with load
			 * [0x1|     0|     1|    1] MHL without अक्षरging cable
			 * [0x1|     1|     1|    1] MHL with अक्षरging cable
			 */
			cable_type = ((0x1 << 8)
					| (vbvolt << 2)
					| (adclow << 1)
					| adc1k);

			info->prev_cable_type = adc;
			info->prev_cable_type_gnd = cable_type;
		पूर्ण

		अवरोध;
	हाल MAX77693_CABLE_GROUP_CHG:
		/*
		 * Read अक्षरger type to check cable type and decide cable state
		 * according to type of अक्षरger cable.
		 */
		chg_type = info->status[1] & MAX77693_STATUS2_CHGTYP_MASK;
		chg_type >>= MAX77693_STATUS2_CHGTYP_SHIFT;

		अगर (chg_type == MAX77693_CHARGER_TYPE_NONE) अणु
			*attached = false;

			cable_type = info->prev_chg_type;
			info->prev_chg_type = MAX77693_CHARGER_TYPE_NONE;
		पूर्ण अन्यथा अणु
			*attached = true;

			/*
			 * Check current cable state/cable type and store cable
			 * type(info->prev_chg_type) क्रम handling cable when
			 * अक्षरger cable is detached.
			 */
			cable_type = info->prev_chg_type = chg_type;
		पूर्ण

		अवरोध;
	हाल MAX77693_CABLE_GROUP_VBVOLT:
		/*
		 * Read ADC value to check cable type and decide cable state
		 * according to cable type
		 */
		adc = info->status[0] & MAX77693_STATUS1_ADC_MASK;
		adc >>= MAX77693_STATUS1_ADC_SHIFT;
		chg_type = info->status[1] & MAX77693_STATUS2_CHGTYP_MASK;
		chg_type >>= MAX77693_STATUS2_CHGTYP_SHIFT;

		अगर (adc == MAX77693_MUIC_ADC_OPEN
				&& chg_type == MAX77693_CHARGER_TYPE_NONE)
			*attached = false;
		अन्यथा
			*attached = true;

		/*
		 * Read vbvolt field, अगर vbvolt is 1,
		 * this cable is used क्रम अक्षरging.
		 */
		vbvolt = info->status[1] & MAX77693_STATUS2_VBVOLT_MASK;
		vbvolt >>= MAX77693_STATUS2_VBVOLT_SHIFT;

		cable_type = vbvolt;
		अवरोध;
	शेष:
		dev_err(info->dev, "Unknown cable group (%d)\n", group);
		cable_type = -EINVAL;
		अवरोध;
	पूर्ण

	वापस cable_type;
पूर्ण

अटल पूर्णांक max77693_muic_करोck_handler(काष्ठा max77693_muic_info *info,
		पूर्णांक cable_type, bool attached)
अणु
	पूर्णांक ret = 0;
	पूर्णांक vbvolt;
	bool cable_attached;
	अचिन्हित पूर्णांक करोck_id;

	dev_info(info->dev,
		"external connector is %s (adc:0x%02x)\n",
		attached ? "attached" : "detached", cable_type);

	चयन (cable_type) अणु
	हाल MAX77693_MUIC_ADC_RESERVED_ACC_3:		/* Dock-Smart */
		/*
		 * Check घातer cable whether attached or detached state.
		 * The Dock-Smart device need surely बाह्यal घातer supply.
		 * If घातer cable(USB/TA) isn't connected to Dock device,
		 * user can't use Dock-Smart क्रम desktop mode.
		 */
		vbvolt = max77693_muic_get_cable_type(info,
				MAX77693_CABLE_GROUP_VBVOLT, &cable_attached);
		अगर (attached && !vbvolt) अणु
			dev_warn(info->dev,
				"Cannot detect external power supply\n");
			वापस 0;
		पूर्ण

		/*
		 * Notअगरy Dock/MHL state.
		 * - Dock device include three type of cable which
		 * are HDMI, USB क्रम mouse/keyboard and micro-usb port
		 * क्रम USB/TA cable. Dock device need always exteranl
		 * घातer supply(USB/TA cable through micro-usb cable). Dock
		 * device support screen output of target to separate
		 * monitor and mouse/keyboard क्रम desktop mode.
		 *
		 * Features of 'USB/TA cable with Dock device'
		 * - Support MHL
		 * - Support बाह्यal output feature of audio
		 * - Support अक्षरging through micro-usb port without data
		 *	     connection अगर TA cable is connected to target.
		 * - Support अक्षरging and data connection through micro-usb port
		 *           अगर USB cable is connected between target and host
		 *	     device.
		 * - Support OTG(On-The-Go) device (Ex: Mouse/Keyboard)
		 */
		ret = max77693_muic_set_path(info, info->path_usb, attached);
		अगर (ret < 0)
			वापस ret;

		extcon_set_state_sync(info->edev, EXTCON_DOCK, attached);
		extcon_set_state_sync(info->edev, EXTCON_DISP_MHL, attached);
		जाओ out;
	हाल MAX77693_MUIC_ADC_AUDIO_MODE_REMOTE:	/* Dock-Desk */
		करोck_id = EXTCON_DOCK;
		अवरोध;
	हाल MAX77693_MUIC_ADC_AV_CABLE_NOLOAD:		/* Dock-Audio */
		करोck_id = EXTCON_DOCK;
		अगर (!attached) अणु
			extcon_set_state_sync(info->edev, EXTCON_USB, false);
			extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
						false);
		पूर्ण
		अवरोध;
	शेष:
		dev_err(info->dev, "failed to detect %s dock device\n",
			attached ? "attached" : "detached");
		वापस -EINVAL;
	पूर्ण

	/* Dock-Car/Desk/Audio, PATH:AUDIO */
	ret = max77693_muic_set_path(info, MAX77693_CONTROL1_SW_AUDIO,
					attached);
	अगर (ret < 0)
		वापस ret;
	extcon_set_state_sync(info->edev, करोck_id, attached);

out:
	वापस 0;
पूर्ण

अटल पूर्णांक max77693_muic_करोck_button_handler(काष्ठा max77693_muic_info *info,
		पूर्णांक button_type, bool attached)
अणु
	काष्ठा input_dev *करोck = info->करोck;
	अचिन्हित पूर्णांक code;

	चयन (button_type) अणु
	हाल MAX77693_MUIC_ADC_REMOTE_S3_BUTTON-1
		... MAX77693_MUIC_ADC_REMOTE_S3_BUTTON+1:
		/* DOCK_KEY_PREV */
		code = KEY_PREVIOUSSONG;
		अवरोध;
	हाल MAX77693_MUIC_ADC_REMOTE_S7_BUTTON-1
		... MAX77693_MUIC_ADC_REMOTE_S7_BUTTON+1:
		/* DOCK_KEY_NEXT */
		code = KEY_NEXTSONG;
		अवरोध;
	हाल MAX77693_MUIC_ADC_REMOTE_S9_BUTTON:
		/* DOCK_VOL_DOWN */
		code = KEY_VOLUMEDOWN;
		अवरोध;
	हाल MAX77693_MUIC_ADC_REMOTE_S10_BUTTON:
		/* DOCK_VOL_UP */
		code = KEY_VOLUMEUP;
		अवरोध;
	हाल MAX77693_MUIC_ADC_REMOTE_S12_BUTTON-1
		... MAX77693_MUIC_ADC_REMOTE_S12_BUTTON+1:
		/* DOCK_KEY_PLAY_PAUSE */
		code = KEY_PLAYPAUSE;
		अवरोध;
	शेष:
		dev_err(info->dev,
			"failed to detect %s key (adc:0x%x)\n",
			attached ? "pressed" : "released", button_type);
		वापस -EINVAL;
	पूर्ण

	input_event(करोck, EV_KEY, code, attached);
	input_sync(करोck);

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_muic_adc_ground_handler(काष्ठा max77693_muic_info *info)
अणु
	पूर्णांक cable_type_gnd;
	पूर्णांक ret = 0;
	bool attached;

	cable_type_gnd = max77693_muic_get_cable_type(info,
				MAX77693_CABLE_GROUP_ADC_GND, &attached);

	चयन (cable_type_gnd) अणु
	हाल MAX77693_MUIC_GND_USB_HOST:
	हाल MAX77693_MUIC_GND_USB_HOST_VB:
		/* USB_HOST, PATH: AP_USB */
		ret = max77693_muic_set_path(info, MAX77693_CONTROL1_SW_USB,
						attached);
		अगर (ret < 0)
			वापस ret;
		extcon_set_state_sync(info->edev, EXTCON_USB_HOST, attached);
		अवरोध;
	हाल MAX77693_MUIC_GND_AV_CABLE_LOAD:
		/* Audio Video Cable with load, PATH:AUDIO */
		ret = max77693_muic_set_path(info, MAX77693_CONTROL1_SW_AUDIO,
						attached);
		अगर (ret < 0)
			वापस ret;
		extcon_set_state_sync(info->edev, EXTCON_USB, attached);
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
					attached);
		अवरोध;
	हाल MAX77693_MUIC_GND_MHL:
	हाल MAX77693_MUIC_GND_MHL_VB:
		/* MHL or MHL with USB/TA cable */
		extcon_set_state_sync(info->edev, EXTCON_DISP_MHL, attached);
		अवरोध;
	शेष:
		dev_err(info->dev, "failed to detect %s cable of gnd type\n",
			attached ? "attached" : "detached");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_muic_jig_handler(काष्ठा max77693_muic_info *info,
		पूर्णांक cable_type, bool attached)
अणु
	पूर्णांक ret = 0;
	u8 path = MAX77693_CONTROL1_SW_OPEN;

	dev_info(info->dev,
		"external connector is %s (adc:0x%02x)\n",
		attached ? "attached" : "detached", cable_type);

	चयन (cable_type) अणु
	हाल MAX77693_MUIC_ADC_FACTORY_MODE_USB_OFF:	/* ADC_JIG_USB_OFF */
	हाल MAX77693_MUIC_ADC_FACTORY_MODE_USB_ON:	/* ADC_JIG_USB_ON */
		/* PATH:AP_USB */
		path = MAX77693_CONTROL1_SW_USB;
		अवरोध;
	हाल MAX77693_MUIC_ADC_FACTORY_MODE_UART_OFF:	/* ADC_JIG_UART_OFF */
	हाल MAX77693_MUIC_ADC_FACTORY_MODE_UART_ON:	/* ADC_JIG_UART_ON */
		/* PATH:AP_UART */
		path = MAX77693_CONTROL1_SW_UART;
		अवरोध;
	शेष:
		dev_err(info->dev, "failed to detect %s jig cable\n",
			attached ? "attached" : "detached");
		वापस -EINVAL;
	पूर्ण

	ret = max77693_muic_set_path(info, path, attached);
	अगर (ret < 0)
		वापस ret;

	extcon_set_state_sync(info->edev, EXTCON_JIG, attached);

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_muic_adc_handler(काष्ठा max77693_muic_info *info)
अणु
	पूर्णांक cable_type;
	पूर्णांक button_type;
	bool attached;
	पूर्णांक ret = 0;

	/* Check accessory state which is either detached or attached */
	cable_type = max77693_muic_get_cable_type(info,
				MAX77693_CABLE_GROUP_ADC, &attached);

	dev_info(info->dev,
		"external connector is %s (adc:0x%02x, prev_adc:0x%x)\n",
		attached ? "attached" : "detached", cable_type,
		info->prev_cable_type);

	चयन (cable_type) अणु
	हाल MAX77693_MUIC_ADC_GROUND:
		/* USB_HOST/MHL/Audio */
		max77693_muic_adc_ground_handler(info);
		अवरोध;
	हाल MAX77693_MUIC_ADC_FACTORY_MODE_USB_OFF:
	हाल MAX77693_MUIC_ADC_FACTORY_MODE_USB_ON:
	हाल MAX77693_MUIC_ADC_FACTORY_MODE_UART_OFF:
	हाल MAX77693_MUIC_ADC_FACTORY_MODE_UART_ON:
		/* JIG */
		ret = max77693_muic_jig_handler(info, cable_type, attached);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल MAX77693_MUIC_ADC_RESERVED_ACC_3:		/* Dock-Smart */
	हाल MAX77693_MUIC_ADC_AUDIO_MODE_REMOTE:	/* Dock-Desk */
	हाल MAX77693_MUIC_ADC_AV_CABLE_NOLOAD:		/* Dock-Audio */
		/*
		 * DOCK device
		 *
		 * The MAX77693 MUIC device can detect total 34 cable type
		 * except of अक्षरger cable and MUIC device didn't define
		 * specfic role of cable in the range of from 0x01 to 0x12
		 * of ADC value. So, can use/define cable with no role according
		 * to schema of hardware board.
		 */
		ret = max77693_muic_करोck_handler(info, cable_type, attached);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल MAX77693_MUIC_ADC_REMOTE_S3_BUTTON:      /* DOCK_KEY_PREV */
	हाल MAX77693_MUIC_ADC_REMOTE_S7_BUTTON:      /* DOCK_KEY_NEXT */
	हाल MAX77693_MUIC_ADC_REMOTE_S9_BUTTON:      /* DOCK_VOL_DOWN */
	हाल MAX77693_MUIC_ADC_REMOTE_S10_BUTTON:     /* DOCK_VOL_UP */
	हाल MAX77693_MUIC_ADC_REMOTE_S12_BUTTON:     /* DOCK_KEY_PLAY_PAUSE */
		/*
		 * Button of DOCK device
		 * - the Prev/Next/Volume Up/Volume Down/Play-Pause button
		 *
		 * The MAX77693 MUIC device can detect total 34 cable type
		 * except of अक्षरger cable and MUIC device didn't define
		 * specfic role of cable in the range of from 0x01 to 0x12
		 * of ADC value. So, can use/define cable with no role according
		 * to schema of hardware board.
		 */
		अगर (attached)
			button_type = info->prev_button_type = cable_type;
		अन्यथा
			button_type = info->prev_button_type;

		ret = max77693_muic_करोck_button_handler(info, button_type,
							attached);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल MAX77693_MUIC_ADC_SEND_END_BUTTON:
	हाल MAX77693_MUIC_ADC_REMOTE_S1_BUTTON:
	हाल MAX77693_MUIC_ADC_REMOTE_S2_BUTTON:
	हाल MAX77693_MUIC_ADC_REMOTE_S4_BUTTON:
	हाल MAX77693_MUIC_ADC_REMOTE_S5_BUTTON:
	हाल MAX77693_MUIC_ADC_REMOTE_S6_BUTTON:
	हाल MAX77693_MUIC_ADC_REMOTE_S8_BUTTON:
	हाल MAX77693_MUIC_ADC_REMOTE_S11_BUTTON:
	हाल MAX77693_MUIC_ADC_RESERVED_ACC_1:
	हाल MAX77693_MUIC_ADC_RESERVED_ACC_2:
	हाल MAX77693_MUIC_ADC_RESERVED_ACC_4:
	हाल MAX77693_MUIC_ADC_RESERVED_ACC_5:
	हाल MAX77693_MUIC_ADC_CEA936_AUDIO:
	हाल MAX77693_MUIC_ADC_PHONE_POWERED_DEV:
	हाल MAX77693_MUIC_ADC_TTY_CONVERTER:
	हाल MAX77693_MUIC_ADC_UART_CABLE:
	हाल MAX77693_MUIC_ADC_CEA936A_TYPE1_CHG:
	हाल MAX77693_MUIC_ADC_CEA936A_TYPE2_CHG:
		/*
		 * This accessory isn't used in general हाल अगर it is specially
		 * needed to detect additional accessory, should implement
		 * proper operation when this accessory is attached/detached.
		 */
		dev_info(info->dev,
			"accessory is %s but it isn't used (adc:0x%x)\n",
			attached ? "attached" : "detached", cable_type);
		वापस -EAGAIN;
	शेष:
		dev_err(info->dev,
			"failed to detect %s accessory (adc:0x%x)\n",
			attached ? "attached" : "detached", cable_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_muic_chg_handler(काष्ठा max77693_muic_info *info)
अणु
	पूर्णांक chg_type;
	पूर्णांक cable_type_gnd;
	पूर्णांक cable_type;
	bool attached;
	bool cable_attached;
	पूर्णांक ret = 0;

	chg_type = max77693_muic_get_cable_type(info,
				MAX77693_CABLE_GROUP_CHG, &attached);

	dev_info(info->dev,
		"external connector is %s(chg_type:0x%x, prev_chg_type:0x%x)\n",
			attached ? "attached" : "detached",
			chg_type, info->prev_chg_type);

	चयन (chg_type) अणु
	हाल MAX77693_CHARGER_TYPE_USB:
	हाल MAX77693_CHARGER_TYPE_DEDICATED_CHG:
	हाल MAX77693_CHARGER_TYPE_NONE:
		/* Check MAX77693_CABLE_GROUP_ADC_GND type */
		cable_type_gnd = max77693_muic_get_cable_type(info,
					MAX77693_CABLE_GROUP_ADC_GND,
					&cable_attached);
		चयन (cable_type_gnd) अणु
		हाल MAX77693_MUIC_GND_MHL:
		हाल MAX77693_MUIC_GND_MHL_VB:
			/*
			 * MHL cable with USB/TA cable
			 * - MHL cable include two port(HDMI line and separate
			 * micro-usb port. When the target connect MHL cable,
			 * extcon driver check whether USB/TA cable is
			 * connected. If USB/TA cable is connected, extcon
			 * driver notअगरy state to notअगरiee क्रम अक्षरging battery.
			 *
			 * Features of 'USB/TA with MHL cable'
			 * - Support MHL
			 * - Support अक्षरging through micro-usb port without
			 *   data connection
			 */
			extcon_set_state_sync(info->edev, EXTCON_CHG_USB_DCP,
						attached);
			extcon_set_state_sync(info->edev, EXTCON_DISP_MHL,
						cable_attached);
			अवरोध;
		पूर्ण

		/* Check MAX77693_CABLE_GROUP_ADC type */
		cable_type = max77693_muic_get_cable_type(info,
					MAX77693_CABLE_GROUP_ADC,
					&cable_attached);
		चयन (cable_type) अणु
		हाल MAX77693_MUIC_ADC_AV_CABLE_NOLOAD:		/* Dock-Audio */
			/*
			 * Dock-Audio device with USB/TA cable
			 * - Dock device include two port(Dock-Audio and micro-
			 * usb port). When the target connect Dock-Audio device,
			 * extcon driver check whether USB/TA cable is connected
			 * or not. If USB/TA cable is connected, extcon driver
			 * notअगरy state to notअगरiee क्रम अक्षरging battery.
			 *
			 * Features of 'USB/TA cable with Dock-Audio device'
			 * - Support बाह्यal output feature of audio.
			 * - Support अक्षरging through micro-usb port without
			 *   data connection.
			 */
			extcon_set_state_sync(info->edev, EXTCON_USB,
						attached);
			extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
						attached);

			अगर (!cable_attached)
				extcon_set_state_sync(info->edev, EXTCON_DOCK,
							cable_attached);
			अवरोध;
		हाल MAX77693_MUIC_ADC_RESERVED_ACC_3:		/* Dock-Smart */
			/*
			 * Dock-Smart device with USB/TA cable
			 * - Dock-Desk device include three type of cable which
			 * are HDMI, USB क्रम mouse/keyboard and micro-usb port
			 * क्रम USB/TA cable. Dock-Smart device need always
			 * exteranl घातer supply(USB/TA cable through micro-usb
			 * cable). Dock-Smart device support screen output of
			 * target to separate monitor and mouse/keyboard क्रम
			 * desktop mode.
			 *
			 * Features of 'USB/TA cable with Dock-Smart device'
			 * - Support MHL
			 * - Support बाह्यal output feature of audio
			 * - Support अक्षरging through micro-usb port without
			 *   data connection अगर TA cable is connected to target.
			 * - Support अक्षरging and data connection through micro-
			 *   usb port अगर USB cable is connected between target
			 *   and host device
			 * - Support OTG(On-The-Go) device (Ex: Mouse/Keyboard)
			 */
			ret = max77693_muic_set_path(info, info->path_usb,
						    attached);
			अगर (ret < 0)
				वापस ret;

			extcon_set_state_sync(info->edev, EXTCON_DOCK,
						attached);
			extcon_set_state_sync(info->edev, EXTCON_DISP_MHL,
						attached);
			अवरोध;
		पूर्ण

		/* Check MAX77693_CABLE_GROUP_CHG type */
		चयन (chg_type) अणु
		हाल MAX77693_CHARGER_TYPE_NONE:
			/*
			 * When MHL(with USB/TA cable) or Dock-Audio with USB/TA
			 * cable is attached, muic device happen below two irq.
			 * - 'MAX77693_MUIC_IRQ_INT1_ADC' क्रम detecting
			 *    MHL/Dock-Audio.
			 * - 'MAX77693_MUIC_IRQ_INT2_CHGTYP' क्रम detecting
			 *    USB/TA cable connected to MHL or Dock-Audio.
			 * Always, happen eariler MAX77693_MUIC_IRQ_INT1_ADC
			 * irq than MAX77693_MUIC_IRQ_INT2_CHGTYP irq.
			 *
			 * If user attach MHL (with USB/TA cable and immediately
			 * detach MHL with USB/TA cable beक्रमe MAX77693_MUIC_IRQ
			 * _INT2_CHGTYP irq is happened, USB/TA cable reमुख्य
			 * connected state to target. But USB/TA cable isn't
			 * connected to target. The user be face with unusual
			 * action. So, driver should check this situation in
			 * spite of, that previous अक्षरger type is N/A.
			 */
			अवरोध;
		हाल MAX77693_CHARGER_TYPE_USB:
			/* Only USB cable, PATH:AP_USB */
			ret = max77693_muic_set_path(info, info->path_usb,
						    attached);
			अगर (ret < 0)
				वापस ret;

			extcon_set_state_sync(info->edev, EXTCON_USB,
						attached);
			extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
						attached);
			अवरोध;
		हाल MAX77693_CHARGER_TYPE_DEDICATED_CHG:
			/* Only TA cable */
			extcon_set_state_sync(info->edev, EXTCON_CHG_USB_DCP,
						attached);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MAX77693_CHARGER_TYPE_DOWNSTREAM_PORT:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_CDP,
					attached);
		अवरोध;
	हाल MAX77693_CHARGER_TYPE_APPLE_500MA:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SLOW,
					attached);
		अवरोध;
	हाल MAX77693_CHARGER_TYPE_APPLE_1A_2A:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_FAST,
					attached);
		अवरोध;
	हाल MAX77693_CHARGER_TYPE_DEAD_BATTERY:
		अवरोध;
	शेष:
		dev_err(info->dev,
			"failed to detect %s accessory (chg_type:0x%x)\n",
			attached ? "attached" : "detached", chg_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम max77693_muic_irq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max77693_muic_info *info = container_of(work,
			काष्ठा max77693_muic_info, irq_work);
	पूर्णांक irq_type = -1;
	पूर्णांक i, ret = 0;

	अगर (!info->edev)
		वापस;

	mutex_lock(&info->mutex);

	क्रम (i = 0; i < ARRAY_SIZE(muic_irqs); i++)
		अगर (info->irq == muic_irqs[i].virq)
			irq_type = muic_irqs[i].irq;

	ret = regmap_bulk_पढ़ो(info->max77693->regmap_muic,
			MAX77693_MUIC_REG_STATUS1, info->status, 2);
	अगर (ret) अणु
		dev_err(info->dev, "failed to read MUIC register\n");
		mutex_unlock(&info->mutex);
		वापस;
	पूर्ण

	चयन (irq_type) अणु
	हाल MAX77693_MUIC_IRQ_INT1_ADC:
	हाल MAX77693_MUIC_IRQ_INT1_ADC_LOW:
	हाल MAX77693_MUIC_IRQ_INT1_ADC_ERR:
	हाल MAX77693_MUIC_IRQ_INT1_ADC1K:
		/*
		 * Handle all of accessory except क्रम
		 * type of अक्षरger accessory.
		 */
		ret = max77693_muic_adc_handler(info);
		अवरोध;
	हाल MAX77693_MUIC_IRQ_INT2_CHGTYP:
	हाल MAX77693_MUIC_IRQ_INT2_CHGDETREUN:
	हाल MAX77693_MUIC_IRQ_INT2_DCDTMR:
	हाल MAX77693_MUIC_IRQ_INT2_DXOVP:
	हाल MAX77693_MUIC_IRQ_INT2_VBVOLT:
	हाल MAX77693_MUIC_IRQ_INT2_VIDRM:
		/* Handle अक्षरger accessory */
		ret = max77693_muic_chg_handler(info);
		अवरोध;
	हाल MAX77693_MUIC_IRQ_INT3_EOC:
	हाल MAX77693_MUIC_IRQ_INT3_CGMBC:
	हाल MAX77693_MUIC_IRQ_INT3_OVP:
	हाल MAX77693_MUIC_IRQ_INT3_MBCCHG_ERR:
	हाल MAX77693_MUIC_IRQ_INT3_CHG_ENABLED:
	हाल MAX77693_MUIC_IRQ_INT3_BAT_DET:
		अवरोध;
	शेष:
		dev_err(info->dev, "muic interrupt: irq %d occurred\n",
				irq_type);
		mutex_unlock(&info->mutex);
		वापस;
	पूर्ण

	अगर (ret < 0)
		dev_err(info->dev, "failed to handle MUIC interrupt\n");

	mutex_unlock(&info->mutex);
पूर्ण

अटल irqवापस_t max77693_muic_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max77693_muic_info *info = data;

	info->irq = irq;
	schedule_work(&info->irq_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा regmap_config max77693_muic_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक max77693_muic_detect_accessory(काष्ठा max77693_muic_info *info)
अणु
	पूर्णांक ret = 0;
	पूर्णांक adc;
	पूर्णांक chg_type;
	bool attached;

	mutex_lock(&info->mutex);

	/* Read STATUSx रेजिस्टर to detect accessory */
	ret = regmap_bulk_पढ़ो(info->max77693->regmap_muic,
			MAX77693_MUIC_REG_STATUS1, info->status, 2);
	अगर (ret) अणु
		dev_err(info->dev, "failed to read MUIC register\n");
		mutex_unlock(&info->mutex);
		वापस ret;
	पूर्ण

	adc = max77693_muic_get_cable_type(info, MAX77693_CABLE_GROUP_ADC,
					&attached);
	अगर (attached && adc != MAX77693_MUIC_ADC_OPEN) अणु
		ret = max77693_muic_adc_handler(info);
		अगर (ret < 0) अणु
			dev_err(info->dev, "Cannot detect accessory\n");
			mutex_unlock(&info->mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	chg_type = max77693_muic_get_cable_type(info, MAX77693_CABLE_GROUP_CHG,
					&attached);
	अगर (attached && chg_type != MAX77693_CHARGER_TYPE_NONE) अणु
		ret = max77693_muic_chg_handler(info);
		अगर (ret < 0) अणु
			dev_err(info->dev, "Cannot detect charger accessory\n");
			mutex_unlock(&info->mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_unlock(&info->mutex);

	वापस 0;
पूर्ण

अटल व्योम max77693_muic_detect_cable_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max77693_muic_info *info = container_of(to_delayed_work(work),
				काष्ठा max77693_muic_info, wq_detcable);

	max77693_muic_detect_accessory(info);
पूर्ण

अटल पूर्णांक max77693_muic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77693_dev *max77693 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max77693_platक्रमm_data *pdata = dev_get_platdata(max77693->dev);
	काष्ठा max77693_muic_info *info;
	काष्ठा max77693_reg_data *init_data;
	पूर्णांक num_init_data;
	पूर्णांक delay_jअगरfies;
	पूर्णांक cable_type;
	bool attached;
	पूर्णांक ret;
	पूर्णांक i;
	अचिन्हित पूर्णांक id;

	info = devm_kzalloc(&pdev->dev, माप(काष्ठा max77693_muic_info),
				   GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = &pdev->dev;
	info->max77693 = max77693;
	अगर (info->max77693->regmap_muic) अणु
		dev_dbg(&pdev->dev, "allocate register map\n");
	पूर्ण अन्यथा अणु
		info->max77693->regmap_muic = devm_regmap_init_i2c(
						info->max77693->i2c_muic,
						&max77693_muic_regmap_config);
		अगर (IS_ERR(info->max77693->regmap_muic)) अणु
			ret = PTR_ERR(info->max77693->regmap_muic);
			dev_err(max77693->dev,
				"failed to allocate register map: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Register input device क्रम button of करोck device */
	info->करोck = devm_input_allocate_device(&pdev->dev);
	अगर (!info->करोck) अणु
		dev_err(&pdev->dev, "%s: failed to allocate input\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	info->करोck->name = "max77693-muic/dock";
	info->करोck->phys = "max77693-muic/extcon";
	info->करोck->dev.parent = &pdev->dev;

	__set_bit(EV_REP, info->करोck->evbit);

	input_set_capability(info->करोck, EV_KEY, KEY_VOLUMEUP);
	input_set_capability(info->करोck, EV_KEY, KEY_VOLUMEDOWN);
	input_set_capability(info->करोck, EV_KEY, KEY_PLAYPAUSE);
	input_set_capability(info->करोck, EV_KEY, KEY_PREVIOUSSONG);
	input_set_capability(info->करोck, EV_KEY, KEY_NEXTSONG);

	ret = input_रेजिस्टर_device(info->करोck);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Cannot register input device error(%d)\n",
				ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);
	mutex_init(&info->mutex);

	INIT_WORK(&info->irq_work, max77693_muic_irq_work);

	/* Support irq करोमुख्य क्रम MAX77693 MUIC device */
	क्रम (i = 0; i < ARRAY_SIZE(muic_irqs); i++) अणु
		काष्ठा max77693_muic_irq *muic_irq = &muic_irqs[i];
		पूर्णांक virq;

		virq = regmap_irq_get_virq(max77693->irq_data_muic,
					muic_irq->irq);
		अगर (virq <= 0)
			वापस -EINVAL;
		muic_irq->virq = virq;

		ret = devm_request_thपढ़ोed_irq(&pdev->dev, virq, शून्य,
				max77693_muic_irq_handler,
				IRQF_NO_SUSPEND,
				muic_irq->name, info);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"failed: irq request (IRQ: %d, error :%d)\n",
				muic_irq->irq, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Initialize extcon device */
	info->edev = devm_extcon_dev_allocate(&pdev->dev,
					      max77693_extcon_cable);
	अगर (IS_ERR(info->edev)) अणु
		dev_err(&pdev->dev, "failed to allocate memory for extcon\n");
		वापस PTR_ERR(info->edev);
	पूर्ण

	ret = devm_extcon_dev_रेजिस्टर(&pdev->dev, info->edev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register extcon device\n");
		वापस ret;
	पूर्ण

	/* Initialize MUIC रेजिस्टर by using platक्रमm data or शेष data */
	अगर (pdata && pdata->muic_data) अणु
		init_data = pdata->muic_data->init_data;
		num_init_data = pdata->muic_data->num_init_data;
	पूर्ण अन्यथा अणु
		init_data = शेष_init_data;
		num_init_data = ARRAY_SIZE(शेष_init_data);
	पूर्ण

	क्रम (i = 0; i < num_init_data; i++) अणु
		regmap_ग_लिखो(info->max77693->regmap_muic,
				init_data[i].addr,
				init_data[i].data);
	पूर्ण

	अगर (pdata && pdata->muic_data) अणु
		काष्ठा max77693_muic_platक्रमm_data *muic_pdata
						   = pdata->muic_data;

		/*
		 * Default usb/uart path whether UART/USB or AUX_UART/AUX_USB
		 * h/w path of COMP2/COMN1 on CONTROL1 रेजिस्टर.
		 */
		अगर (muic_pdata->path_uart)
			info->path_uart = muic_pdata->path_uart;
		अन्यथा
			info->path_uart = MAX77693_CONTROL1_SW_UART;

		अगर (muic_pdata->path_usb)
			info->path_usb = muic_pdata->path_usb;
		अन्यथा
			info->path_usb = MAX77693_CONTROL1_SW_USB;

		/*
		 * Default delay समय क्रम detecting cable state
		 * after certain समय.
		 */
		अगर (muic_pdata->detcable_delay_ms)
			delay_jअगरfies =
				msecs_to_jअगरfies(muic_pdata->detcable_delay_ms);
		अन्यथा
			delay_jअगरfies = msecs_to_jअगरfies(DELAY_MS_DEFAULT);
	पूर्ण अन्यथा अणु
		info->path_usb = MAX77693_CONTROL1_SW_USB;
		info->path_uart = MAX77693_CONTROL1_SW_UART;
		delay_jअगरfies = msecs_to_jअगरfies(DELAY_MS_DEFAULT);
	पूर्ण

	/* Set initial path क्रम UART when JIG is connected to get serial logs */
	ret = regmap_bulk_पढ़ो(info->max77693->regmap_muic,
			MAX77693_MUIC_REG_STATUS1, info->status, 2);
	अगर (ret) अणु
		dev_err(info->dev, "failed to read MUIC register\n");
		वापस ret;
	पूर्ण
	cable_type = max77693_muic_get_cable_type(info,
					   MAX77693_CABLE_GROUP_ADC, &attached);
	अगर (attached && (cable_type == MAX77693_MUIC_ADC_FACTORY_MODE_UART_ON ||
			 cable_type == MAX77693_MUIC_ADC_FACTORY_MODE_UART_OFF))
		max77693_muic_set_path(info, info->path_uart, true);

	/* Check revision number of MUIC device*/
	ret = regmap_पढ़ो(info->max77693->regmap_muic,
			MAX77693_MUIC_REG_ID, &id);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to read revision number\n");
		वापस ret;
	पूर्ण
	dev_info(info->dev, "device ID : 0x%x\n", id);

	/* Set ADC debounce समय */
	max77693_muic_set_debounce_समय(info, ADC_DEBOUNCE_TIME_25MS);

	/*
	 * Detect accessory after completing the initialization of platक्रमm
	 *
	 * - Use delayed workqueue to detect cable state and then
	 * notअगरy cable state to notअगरiee/platक्रमm through uevent.
	 * After completing the booting of platक्रमm, the extcon provider
	 * driver should notअगरy cable state to upper layer.
	 */
	INIT_DELAYED_WORK(&info->wq_detcable, max77693_muic_detect_cable_wq);
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &info->wq_detcable,
			delay_jअगरfies);

	वापस ret;
पूर्ण

अटल पूर्णांक max77693_muic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77693_muic_info *info = platक्रमm_get_drvdata(pdev);

	cancel_work_sync(&info->irq_work);
	input_unरेजिस्टर_device(info->करोck);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver max77693_muic_driver = अणु
	.driver		= अणु
		.name	= DEV_NAME,
	पूर्ण,
	.probe		= max77693_muic_probe,
	.हटाओ		= max77693_muic_हटाओ,
पूर्ण;

module_platक्रमm_driver(max77693_muic_driver);

MODULE_DESCRIPTION("Maxim MAX77693 Extcon driver");
MODULE_AUTHOR("Chanwoo Choi <cw00.choi@samsung.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:max77693-muic");
