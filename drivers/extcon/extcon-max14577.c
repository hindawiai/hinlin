<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// extcon-max14577.c - MAX14577/77836 extcon driver to support MUIC
//
// Copyright (C) 2013,2014 Samsung Electronics
// Chanwoo Choi <cw00.choi@samsung.com>
// Krzysztof Kozlowski <krzk@kernel.org>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/max14577.h>
#समावेश <linux/mfd/max14577-निजी.h>
#समावेश <linux/extcon-provider.h>

#घोषणा	DELAY_MS_DEFAULT		17000		/* unit: millisecond */

क्रमागत max14577_muic_adc_debounce_समय अणु
	ADC_DEBOUNCE_TIME_5MS = 0,
	ADC_DEBOUNCE_TIME_10MS,
	ADC_DEBOUNCE_TIME_25MS,
	ADC_DEBOUNCE_TIME_38_62MS,
पूर्ण;

क्रमागत max14577_muic_status अणु
	MAX14577_MUIC_STATUS1 = 0,
	MAX14577_MUIC_STATUS2 = 1,
	MAX14577_MUIC_STATUS_END,
पूर्ण;

/**
 * काष्ठा max14577_muic_irq
 * @irq: the index of irq list of MUIC device.
 * @name: the name of irq.
 * @virq: the भव irq to use irq करोमुख्य
 */
काष्ठा max14577_muic_irq अणु
	अचिन्हित पूर्णांक irq;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक virq;
पूर्ण;

अटल काष्ठा max14577_muic_irq max14577_muic_irqs[] = अणु
	अणु MAX14577_IRQ_INT1_ADC,	"muic-ADC" पूर्ण,
	अणु MAX14577_IRQ_INT1_ADCLOW,	"muic-ADCLOW" पूर्ण,
	अणु MAX14577_IRQ_INT1_ADCERR,	"muic-ADCError" पूर्ण,
	अणु MAX14577_IRQ_INT2_CHGTYP,	"muic-CHGTYP" पूर्ण,
	अणु MAX14577_IRQ_INT2_CHGDETRUN,	"muic-CHGDETRUN" पूर्ण,
	अणु MAX14577_IRQ_INT2_DCDTMR,	"muic-DCDTMR" पूर्ण,
	अणु MAX14577_IRQ_INT2_DBCHG,	"muic-DBCHG" पूर्ण,
	अणु MAX14577_IRQ_INT2_VBVOLT,	"muic-VBVOLT" पूर्ण,
पूर्ण;

अटल काष्ठा max14577_muic_irq max77836_muic_irqs[] = अणु
	अणु MAX14577_IRQ_INT1_ADC,	"muic-ADC" पूर्ण,
	अणु MAX14577_IRQ_INT1_ADCLOW,	"muic-ADCLOW" पूर्ण,
	अणु MAX14577_IRQ_INT1_ADCERR,	"muic-ADCError" पूर्ण,
	अणु MAX77836_IRQ_INT1_ADC1K,	"muic-ADC1K" पूर्ण,
	अणु MAX14577_IRQ_INT2_CHGTYP,	"muic-CHGTYP" पूर्ण,
	अणु MAX14577_IRQ_INT2_CHGDETRUN,	"muic-CHGDETRUN" पूर्ण,
	अणु MAX14577_IRQ_INT2_DCDTMR,	"muic-DCDTMR" पूर्ण,
	अणु MAX14577_IRQ_INT2_DBCHG,	"muic-DBCHG" पूर्ण,
	अणु MAX14577_IRQ_INT2_VBVOLT,	"muic-VBVOLT" पूर्ण,
	अणु MAX77836_IRQ_INT2_VIDRM,	"muic-VIDRM" पूर्ण,
पूर्ण;

काष्ठा max14577_muic_info अणु
	काष्ठा device *dev;
	काष्ठा max14577 *max14577;
	काष्ठा extcon_dev *edev;
	पूर्णांक prev_cable_type;
	पूर्णांक prev_chg_type;
	u8 status[MAX14577_MUIC_STATUS_END];

	काष्ठा max14577_muic_irq *muic_irqs;
	अचिन्हित पूर्णांक muic_irqs_num;
	bool irq_adc;
	bool irq_chg;
	काष्ठा work_काष्ठा irq_work;
	काष्ठा mutex mutex;

	/*
	 * Use delayed workqueue to detect cable state and then
	 * notअगरy cable state to notअगरiee/platक्रमm through uevent.
	 * After completing the booting of platक्रमm, the extcon provider
	 * driver should notअगरy cable state to upper layer.
	 */
	काष्ठा delayed_work wq_detcable;

	/*
	 * Default usb/uart path whether UART/USB or AUX_UART/AUX_USB
	 * h/w path of COMP2/COMN1 on CONTROL1 रेजिस्टर.
	 */
	पूर्णांक path_usb;
	पूर्णांक path_uart;
पूर्ण;

क्रमागत max14577_muic_cable_group अणु
	MAX14577_CABLE_GROUP_ADC = 0,
	MAX14577_CABLE_GROUP_CHG,
पूर्ण;

/* Define supported accessory type */
क्रमागत max14577_muic_acc_type अणु
	MAX14577_MUIC_ADC_GROUND = 0x0,
	MAX14577_MUIC_ADC_SEND_END_BUTTON,
	MAX14577_MUIC_ADC_REMOTE_S1_BUTTON,
	MAX14577_MUIC_ADC_REMOTE_S2_BUTTON,
	MAX14577_MUIC_ADC_REMOTE_S3_BUTTON,
	MAX14577_MUIC_ADC_REMOTE_S4_BUTTON,
	MAX14577_MUIC_ADC_REMOTE_S5_BUTTON,
	MAX14577_MUIC_ADC_REMOTE_S6_BUTTON,
	MAX14577_MUIC_ADC_REMOTE_S7_BUTTON,
	MAX14577_MUIC_ADC_REMOTE_S8_BUTTON,
	MAX14577_MUIC_ADC_REMOTE_S9_BUTTON,
	MAX14577_MUIC_ADC_REMOTE_S10_BUTTON,
	MAX14577_MUIC_ADC_REMOTE_S11_BUTTON,
	MAX14577_MUIC_ADC_REMOTE_S12_BUTTON,
	MAX14577_MUIC_ADC_RESERVED_ACC_1,
	MAX14577_MUIC_ADC_RESERVED_ACC_2,
	MAX14577_MUIC_ADC_RESERVED_ACC_3,
	MAX14577_MUIC_ADC_RESERVED_ACC_4,
	MAX14577_MUIC_ADC_RESERVED_ACC_5,
	MAX14577_MUIC_ADC_AUDIO_DEVICE_TYPE2,
	MAX14577_MUIC_ADC_PHONE_POWERED_DEV,
	MAX14577_MUIC_ADC_TTY_CONVERTER,
	MAX14577_MUIC_ADC_UART_CABLE,
	MAX14577_MUIC_ADC_CEA936A_TYPE1_CHG,
	MAX14577_MUIC_ADC_FACTORY_MODE_USB_OFF,
	MAX14577_MUIC_ADC_FACTORY_MODE_USB_ON,
	MAX14577_MUIC_ADC_AV_CABLE_NOLOAD,
	MAX14577_MUIC_ADC_CEA936A_TYPE2_CHG,
	MAX14577_MUIC_ADC_FACTORY_MODE_UART_OFF,
	MAX14577_MUIC_ADC_FACTORY_MODE_UART_ON,
	MAX14577_MUIC_ADC_AUDIO_DEVICE_TYPE1, /* with Remote and Simple Ctrl */
	MAX14577_MUIC_ADC_OPEN,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक max14577_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_CHG_USB_FAST,
	EXTCON_CHG_USB_SLOW,
	EXTCON_CHG_USB_CDP,
	EXTCON_JIG,
	EXTCON_NONE,
पूर्ण;

/*
 * max14577_muic_set_debounce_समय - Set the debounce समय of ADC
 * @info: the instance including निजी data of max14577 MUIC
 * @समय: the debounce समय of ADC
 */
अटल पूर्णांक max14577_muic_set_debounce_समय(काष्ठा max14577_muic_info *info,
		क्रमागत max14577_muic_adc_debounce_समय समय)
अणु
	u8 ret;

	चयन (समय) अणु
	हाल ADC_DEBOUNCE_TIME_5MS:
	हाल ADC_DEBOUNCE_TIME_10MS:
	हाल ADC_DEBOUNCE_TIME_25MS:
	हाल ADC_DEBOUNCE_TIME_38_62MS:
		ret = max14577_update_reg(info->max14577->regmap,
					  MAX14577_MUIC_REG_CONTROL3,
					  CTRL3_ADCDBSET_MASK,
					  समय << CTRL3_ADCDBSET_SHIFT);
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
 * max14577_muic_set_path - Set hardware line according to attached cable
 * @info: the instance including निजी data of max14577 MUIC
 * @value: the path according to attached cable
 * @attached: the state of cable (true:attached, false:detached)
 *
 * The max14577 MUIC device share outside H/W line among a varity of cables
 * so, this function set पूर्णांकernal path of H/W line according to the type of
 * attached cable.
 */
अटल पूर्णांक max14577_muic_set_path(काष्ठा max14577_muic_info *info,
		u8 val, bool attached)
अणु
	u8 ctrl1, ctrl2 = 0;
	पूर्णांक ret;

	/* Set खोलो state to path beक्रमe changing hw path */
	ret = max14577_update_reg(info->max14577->regmap,
				MAX14577_MUIC_REG_CONTROL1,
				CLEAR_IDBEN_MICEN_MASK, CTRL1_SW_OPEN);
	अगर (ret < 0) अणु
		dev_err(info->dev, "failed to update MUIC register\n");
		वापस ret;
	पूर्ण

	अगर (attached)
		ctrl1 = val;
	अन्यथा
		ctrl1 = CTRL1_SW_OPEN;

	ret = max14577_update_reg(info->max14577->regmap,
				MAX14577_MUIC_REG_CONTROL1,
				CLEAR_IDBEN_MICEN_MASK, ctrl1);
	अगर (ret < 0) अणु
		dev_err(info->dev, "failed to update MUIC register\n");
		वापस ret;
	पूर्ण

	अगर (attached)
		ctrl2 |= CTRL2_CPEN_MASK;	/* LowPwr=0, CPEn=1 */
	अन्यथा
		ctrl2 |= CTRL2_LOWPWR_MASK;	/* LowPwr=1, CPEn=0 */

	ret = max14577_update_reg(info->max14577->regmap,
			MAX14577_REG_CONTROL2,
			CTRL2_LOWPWR_MASK | CTRL2_CPEN_MASK, ctrl2);
	अगर (ret < 0) अणु
		dev_err(info->dev, "failed to update MUIC register\n");
		वापस ret;
	पूर्ण

	dev_dbg(info->dev,
		"CONTROL1 : 0x%02x, CONTROL2 : 0x%02x, state : %s\n",
		ctrl1, ctrl2, attached ? "attached" : "detached");

	वापस 0;
पूर्ण

/*
 * max14577_muic_get_cable_type - Return cable type and check cable state
 * @info: the instance including निजी data of max14577 MUIC
 * @group: the path according to attached cable
 * @attached: store cable state and वापस
 *
 * This function check the cable state either attached or detached,
 * and then भागide precise type of cable according to cable group.
 *	- max14577_CABLE_GROUP_ADC
 *	- max14577_CABLE_GROUP_CHG
 */
अटल पूर्णांक max14577_muic_get_cable_type(काष्ठा max14577_muic_info *info,
		क्रमागत max14577_muic_cable_group group, bool *attached)
अणु
	पूर्णांक cable_type = 0;
	पूर्णांक adc;
	पूर्णांक chg_type;

	चयन (group) अणु
	हाल MAX14577_CABLE_GROUP_ADC:
		/*
		 * Read ADC value to check cable type and decide cable state
		 * according to cable type
		 */
		adc = info->status[MAX14577_MUIC_STATUS1] & STATUS1_ADC_MASK;
		adc >>= STATUS1_ADC_SHIFT;

		/*
		 * Check current cable state/cable type and store cable type
		 * (info->prev_cable_type) क्रम handling cable when cable is
		 * detached.
		 */
		अगर (adc == MAX14577_MUIC_ADC_OPEN) अणु
			*attached = false;

			cable_type = info->prev_cable_type;
			info->prev_cable_type = MAX14577_MUIC_ADC_OPEN;
		पूर्ण अन्यथा अणु
			*attached = true;

			cable_type = info->prev_cable_type = adc;
		पूर्ण
		अवरोध;
	हाल MAX14577_CABLE_GROUP_CHG:
		/*
		 * Read अक्षरger type to check cable type and decide cable state
		 * according to type of अक्षरger cable.
		 */
		chg_type = info->status[MAX14577_MUIC_STATUS2] &
			STATUS2_CHGTYP_MASK;
		chg_type >>= STATUS2_CHGTYP_SHIFT;

		अगर (chg_type == MAX14577_CHARGER_TYPE_NONE) अणु
			*attached = false;

			cable_type = info->prev_chg_type;
			info->prev_chg_type = MAX14577_CHARGER_TYPE_NONE;
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
	शेष:
		dev_err(info->dev, "Unknown cable group (%d)\n", group);
		cable_type = -EINVAL;
		अवरोध;
	पूर्ण

	वापस cable_type;
पूर्ण

अटल पूर्णांक max14577_muic_jig_handler(काष्ठा max14577_muic_info *info,
		पूर्णांक cable_type, bool attached)
अणु
	पूर्णांक ret = 0;
	u8 path = CTRL1_SW_OPEN;

	dev_dbg(info->dev,
		"external connector is %s (adc:0x%02x)\n",
		attached ? "attached" : "detached", cable_type);

	चयन (cable_type) अणु
	हाल MAX14577_MUIC_ADC_FACTORY_MODE_USB_OFF:	/* ADC_JIG_USB_OFF */
	हाल MAX14577_MUIC_ADC_FACTORY_MODE_USB_ON:	/* ADC_JIG_USB_ON */
		/* PATH:AP_USB */
		path = CTRL1_SW_USB;
		अवरोध;
	हाल MAX14577_MUIC_ADC_FACTORY_MODE_UART_OFF:	/* ADC_JIG_UART_OFF */
		/* PATH:AP_UART */
		path = CTRL1_SW_UART;
		अवरोध;
	शेष:
		dev_err(info->dev, "failed to detect %s jig cable\n",
			attached ? "attached" : "detached");
		वापस -EINVAL;
	पूर्ण

	ret = max14577_muic_set_path(info, path, attached);
	अगर (ret < 0)
		वापस ret;

	extcon_set_state_sync(info->edev, EXTCON_JIG, attached);

	वापस 0;
पूर्ण

अटल पूर्णांक max14577_muic_adc_handler(काष्ठा max14577_muic_info *info)
अणु
	पूर्णांक cable_type;
	bool attached;
	पूर्णांक ret = 0;

	/* Check accessory state which is either detached or attached */
	cable_type = max14577_muic_get_cable_type(info,
				MAX14577_CABLE_GROUP_ADC, &attached);

	dev_dbg(info->dev,
		"external connector is %s (adc:0x%02x, prev_adc:0x%x)\n",
		attached ? "attached" : "detached", cable_type,
		info->prev_cable_type);

	चयन (cable_type) अणु
	हाल MAX14577_MUIC_ADC_FACTORY_MODE_USB_OFF:
	हाल MAX14577_MUIC_ADC_FACTORY_MODE_USB_ON:
	हाल MAX14577_MUIC_ADC_FACTORY_MODE_UART_OFF:
		/* JIG */
		ret = max14577_muic_jig_handler(info, cable_type, attached);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल MAX14577_MUIC_ADC_GROUND:
	हाल MAX14577_MUIC_ADC_SEND_END_BUTTON:
	हाल MAX14577_MUIC_ADC_REMOTE_S1_BUTTON:
	हाल MAX14577_MUIC_ADC_REMOTE_S2_BUTTON:
	हाल MAX14577_MUIC_ADC_REMOTE_S3_BUTTON:
	हाल MAX14577_MUIC_ADC_REMOTE_S4_BUTTON:
	हाल MAX14577_MUIC_ADC_REMOTE_S5_BUTTON:
	हाल MAX14577_MUIC_ADC_REMOTE_S6_BUTTON:
	हाल MAX14577_MUIC_ADC_REMOTE_S7_BUTTON:
	हाल MAX14577_MUIC_ADC_REMOTE_S8_BUTTON:
	हाल MAX14577_MUIC_ADC_REMOTE_S9_BUTTON:
	हाल MAX14577_MUIC_ADC_REMOTE_S10_BUTTON:
	हाल MAX14577_MUIC_ADC_REMOTE_S11_BUTTON:
	हाल MAX14577_MUIC_ADC_REMOTE_S12_BUTTON:
	हाल MAX14577_MUIC_ADC_RESERVED_ACC_1:
	हाल MAX14577_MUIC_ADC_RESERVED_ACC_2:
	हाल MAX14577_MUIC_ADC_RESERVED_ACC_3:
	हाल MAX14577_MUIC_ADC_RESERVED_ACC_4:
	हाल MAX14577_MUIC_ADC_RESERVED_ACC_5:
	हाल MAX14577_MUIC_ADC_AUDIO_DEVICE_TYPE2:
	हाल MAX14577_MUIC_ADC_PHONE_POWERED_DEV:
	हाल MAX14577_MUIC_ADC_TTY_CONVERTER:
	हाल MAX14577_MUIC_ADC_UART_CABLE:
	हाल MAX14577_MUIC_ADC_CEA936A_TYPE1_CHG:
	हाल MAX14577_MUIC_ADC_AV_CABLE_NOLOAD:
	हाल MAX14577_MUIC_ADC_CEA936A_TYPE2_CHG:
	हाल MAX14577_MUIC_ADC_FACTORY_MODE_UART_ON:
	हाल MAX14577_MUIC_ADC_AUDIO_DEVICE_TYPE1:
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

अटल पूर्णांक max14577_muic_chg_handler(काष्ठा max14577_muic_info *info)
अणु
	पूर्णांक chg_type;
	bool attached;
	पूर्णांक ret = 0;

	chg_type = max14577_muic_get_cable_type(info,
				MAX14577_CABLE_GROUP_CHG, &attached);

	dev_dbg(info->dev,
		"external connector is %s(chg_type:0x%x, prev_chg_type:0x%x)\n",
			attached ? "attached" : "detached",
			chg_type, info->prev_chg_type);

	चयन (chg_type) अणु
	हाल MAX14577_CHARGER_TYPE_USB:
		/* PATH:AP_USB */
		ret = max14577_muic_set_path(info, info->path_usb, attached);
		अगर (ret < 0)
			वापस ret;

		extcon_set_state_sync(info->edev, EXTCON_USB, attached);
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
					attached);
		अवरोध;
	हाल MAX14577_CHARGER_TYPE_DEDICATED_CHG:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_DCP,
					attached);
		अवरोध;
	हाल MAX14577_CHARGER_TYPE_DOWNSTREAM_PORT:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_CDP,
					attached);
		अवरोध;
	हाल MAX14577_CHARGER_TYPE_SPECIAL_500MA:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SLOW,
					attached);
		अवरोध;
	हाल MAX14577_CHARGER_TYPE_SPECIAL_1A:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_FAST,
					attached);
		अवरोध;
	हाल MAX14577_CHARGER_TYPE_NONE:
	हाल MAX14577_CHARGER_TYPE_DEAD_BATTERY:
		अवरोध;
	शेष:
		dev_err(info->dev,
			"failed to detect %s accessory (chg_type:0x%x)\n",
			attached ? "attached" : "detached", chg_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम max14577_muic_irq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max14577_muic_info *info = container_of(work,
			काष्ठा max14577_muic_info, irq_work);
	पूर्णांक ret = 0;

	अगर (!info->edev)
		वापस;

	mutex_lock(&info->mutex);

	ret = max14577_bulk_पढ़ो(info->max14577->regmap,
			MAX14577_MUIC_REG_STATUS1, info->status, 2);
	अगर (ret) अणु
		dev_err(info->dev, "failed to read MUIC register\n");
		mutex_unlock(&info->mutex);
		वापस;
	पूर्ण

	अगर (info->irq_adc) अणु
		ret = max14577_muic_adc_handler(info);
		info->irq_adc = false;
	पूर्ण
	अगर (info->irq_chg) अणु
		ret = max14577_muic_chg_handler(info);
		info->irq_chg = false;
	पूर्ण

	अगर (ret < 0)
		dev_err(info->dev, "failed to handle MUIC interrupt\n");

	mutex_unlock(&info->mutex);
पूर्ण

/*
 * Sets irq_adc or irq_chg in max14577_muic_info and वापसs 1.
 * Returns 0 अगर irq_type करोes not match रेजिस्टरed IRQ क्रम this device type.
 */
अटल पूर्णांक max14577_parse_irq(काष्ठा max14577_muic_info *info, पूर्णांक irq_type)
अणु
	चयन (irq_type) अणु
	हाल MAX14577_IRQ_INT1_ADC:
	हाल MAX14577_IRQ_INT1_ADCLOW:
	हाल MAX14577_IRQ_INT1_ADCERR:
		/*
		 * Handle all of accessory except क्रम
		 * type of अक्षरger accessory.
		 */
		info->irq_adc = true;
		वापस 1;
	हाल MAX14577_IRQ_INT2_CHGTYP:
	हाल MAX14577_IRQ_INT2_CHGDETRUN:
	हाल MAX14577_IRQ_INT2_DCDTMR:
	हाल MAX14577_IRQ_INT2_DBCHG:
	हाल MAX14577_IRQ_INT2_VBVOLT:
		/* Handle अक्षरger accessory */
		info->irq_chg = true;
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Sets irq_adc or irq_chg in max14577_muic_info and वापसs 1.
 * Returns 0 अगर irq_type करोes not match रेजिस्टरed IRQ क्रम this device type.
 */
अटल पूर्णांक max77836_parse_irq(काष्ठा max14577_muic_info *info, पूर्णांक irq_type)
अणु
	/* First check common max14577 पूर्णांकerrupts */
	अगर (max14577_parse_irq(info, irq_type))
		वापस 1;

	चयन (irq_type) अणु
	हाल MAX77836_IRQ_INT1_ADC1K:
		info->irq_adc = true;
		वापस 1;
	हाल MAX77836_IRQ_INT2_VIDRM:
		/* Handle अक्षरger accessory */
		info->irq_chg = true;
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल irqवापस_t max14577_muic_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max14577_muic_info *info = data;
	पूर्णांक i, irq_type = -1;
	bool irq_parsed;

	/*
	 * We may be called multiple बार क्रम dअगरferent nested IRQ-s.
	 * Including changes in INT1_ADC and INT2_CGHTYP at once.
	 * However we only need to know whether it was ADC, अक्षरger
	 * or both पूर्णांकerrupts so decode IRQ and turn on proper flags.
	 */
	क्रम (i = 0; i < info->muic_irqs_num; i++)
		अगर (irq == info->muic_irqs[i].virq)
			irq_type = info->muic_irqs[i].irq;

	चयन (info->max14577->dev_type) अणु
	हाल MAXIM_DEVICE_TYPE_MAX77836:
		irq_parsed = max77836_parse_irq(info, irq_type);
		अवरोध;
	हाल MAXIM_DEVICE_TYPE_MAX14577:
	शेष:
		irq_parsed = max14577_parse_irq(info, irq_type);
		अवरोध;
	पूर्ण

	अगर (!irq_parsed) अणु
		dev_err(info->dev, "muic interrupt: irq %d occurred, skipped\n",
				irq_type);
		वापस IRQ_HANDLED;
	पूर्ण
	schedule_work(&info->irq_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max14577_muic_detect_accessory(काष्ठा max14577_muic_info *info)
अणु
	पूर्णांक ret = 0;
	पूर्णांक adc;
	पूर्णांक chg_type;
	bool attached;

	mutex_lock(&info->mutex);

	/* Read STATUSx रेजिस्टर to detect accessory */
	ret = max14577_bulk_पढ़ो(info->max14577->regmap,
			MAX14577_MUIC_REG_STATUS1, info->status, 2);
	अगर (ret) अणु
		dev_err(info->dev, "failed to read MUIC register\n");
		mutex_unlock(&info->mutex);
		वापस ret;
	पूर्ण

	adc = max14577_muic_get_cable_type(info, MAX14577_CABLE_GROUP_ADC,
					&attached);
	अगर (attached && adc != MAX14577_MUIC_ADC_OPEN) अणु
		ret = max14577_muic_adc_handler(info);
		अगर (ret < 0) अणु
			dev_err(info->dev, "Cannot detect accessory\n");
			mutex_unlock(&info->mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	chg_type = max14577_muic_get_cable_type(info, MAX14577_CABLE_GROUP_CHG,
					&attached);
	अगर (attached && chg_type != MAX14577_CHARGER_TYPE_NONE) अणु
		ret = max14577_muic_chg_handler(info);
		अगर (ret < 0) अणु
			dev_err(info->dev, "Cannot detect charger accessory\n");
			mutex_unlock(&info->mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_unlock(&info->mutex);

	वापस 0;
पूर्ण

अटल व्योम max14577_muic_detect_cable_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max14577_muic_info *info = container_of(to_delayed_work(work),
				काष्ठा max14577_muic_info, wq_detcable);

	max14577_muic_detect_accessory(info);
पूर्ण

अटल पूर्णांक max14577_muic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max14577 *max14577 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max14577_muic_info *info;
	पूर्णांक delay_jअगरfies;
	पूर्णांक cable_type;
	bool attached;
	पूर्णांक ret;
	पूर्णांक i;
	u8 id;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = &pdev->dev;
	info->max14577 = max14577;

	platक्रमm_set_drvdata(pdev, info);
	mutex_init(&info->mutex);

	INIT_WORK(&info->irq_work, max14577_muic_irq_work);

	चयन (max14577->dev_type) अणु
	हाल MAXIM_DEVICE_TYPE_MAX77836:
		info->muic_irqs = max77836_muic_irqs;
		info->muic_irqs_num = ARRAY_SIZE(max77836_muic_irqs);
		अवरोध;
	हाल MAXIM_DEVICE_TYPE_MAX14577:
	शेष:
		info->muic_irqs = max14577_muic_irqs;
		info->muic_irqs_num = ARRAY_SIZE(max14577_muic_irqs);
	पूर्ण

	/* Support irq करोमुख्य क्रम max14577 MUIC device */
	क्रम (i = 0; i < info->muic_irqs_num; i++) अणु
		काष्ठा max14577_muic_irq *muic_irq = &info->muic_irqs[i];
		पूर्णांक virq = 0;

		virq = regmap_irq_get_virq(max14577->irq_data, muic_irq->irq);
		अगर (virq <= 0)
			वापस -EINVAL;
		muic_irq->virq = virq;

		ret = devm_request_thपढ़ोed_irq(&pdev->dev, virq, शून्य,
				max14577_muic_irq_handler,
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
					      max14577_extcon_cable);
	अगर (IS_ERR(info->edev)) अणु
		dev_err(&pdev->dev, "failed to allocate memory for extcon\n");
		वापस PTR_ERR(info->edev);
	पूर्ण

	ret = devm_extcon_dev_रेजिस्टर(&pdev->dev, info->edev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register extcon device\n");
		वापस ret;
	पूर्ण

	/* Default h/w line path */
	info->path_usb = CTRL1_SW_USB;
	info->path_uart = CTRL1_SW_UART;
	delay_jअगरfies = msecs_to_jअगरfies(DELAY_MS_DEFAULT);

	/* Set initial path क्रम UART when JIG is connected to get serial logs */
	ret = max14577_bulk_पढ़ो(info->max14577->regmap,
			MAX14577_MUIC_REG_STATUS1, info->status, 2);
	अगर (ret) अणु
		dev_err(info->dev, "Cannot read STATUS registers\n");
		वापस ret;
	पूर्ण
	cable_type = max14577_muic_get_cable_type(info, MAX14577_CABLE_GROUP_ADC,
					 &attached);
	अगर (attached && cable_type == MAX14577_MUIC_ADC_FACTORY_MODE_UART_OFF)
		max14577_muic_set_path(info, info->path_uart, true);

	/* Check revision number of MUIC device*/
	ret = max14577_पढ़ो_reg(info->max14577->regmap,
			MAX14577_REG_DEVICEID, &id);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to read revision number\n");
		वापस ret;
	पूर्ण
	dev_info(info->dev, "device ID : 0x%x\n", id);

	/* Set ADC debounce समय */
	max14577_muic_set_debounce_समय(info, ADC_DEBOUNCE_TIME_25MS);

	/*
	 * Detect accessory after completing the initialization of platक्रमm
	 *
	 * - Use delayed workqueue to detect cable state and then
	 * notअगरy cable state to notअगरiee/platक्रमm through uevent.
	 * After completing the booting of platक्रमm, the extcon provider
	 * driver should notअगरy cable state to upper layer.
	 */
	INIT_DELAYED_WORK(&info->wq_detcable, max14577_muic_detect_cable_wq);
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &info->wq_detcable,
			delay_jअगरfies);

	वापस ret;
पूर्ण

अटल पूर्णांक max14577_muic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max14577_muic_info *info = platक्रमm_get_drvdata(pdev);

	cancel_work_sync(&info->irq_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max14577_muic_id[] = अणु
	अणु "max14577-muic", MAXIM_DEVICE_TYPE_MAX14577, पूर्ण,
	अणु "max77836-muic", MAXIM_DEVICE_TYPE_MAX77836, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max14577_muic_id);

अटल स्थिर काष्ठा of_device_id of_max14577_muic_dt_match[] = अणु
	अणु .compatible = "maxim,max14577-muic",
	  .data = (व्योम *)MAXIM_DEVICE_TYPE_MAX14577, पूर्ण,
	अणु .compatible = "maxim,max77836-muic",
	  .data = (व्योम *)MAXIM_DEVICE_TYPE_MAX77836, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_max14577_muic_dt_match);

अटल काष्ठा platक्रमm_driver max14577_muic_driver = अणु
	.driver		= अणु
		.name	= "max14577-muic",
		.of_match_table = of_max14577_muic_dt_match,
	पूर्ण,
	.probe		= max14577_muic_probe,
	.हटाओ		= max14577_muic_हटाओ,
	.id_table	= max14577_muic_id,
पूर्ण;

module_platक्रमm_driver(max14577_muic_driver);

MODULE_DESCRIPTION("Maxim 14577/77836 Extcon driver");
MODULE_AUTHOR("Chanwoo Choi <cw00.choi@samsung.com>, Krzysztof Kozlowski <krzk@kernel.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:extcon-max14577");
