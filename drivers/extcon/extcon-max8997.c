<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// extcon-max8997.c - MAX8997 extcon driver to support MAX8997 MUIC
//
//  Copyright (C) 2012 Samsung Electronics
//  Donggeun Kim <dg77.kim@samsung.com>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kobject.h>
#समावेश <linux/mfd/max8997.h>
#समावेश <linux/mfd/max8997-निजी.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/irqकरोमुख्य.h>

#घोषणा	DEV_NAME			"max8997-muic"
#घोषणा	DELAY_MS_DEFAULT		20000		/* unit: millisecond */

क्रमागत max8997_muic_adc_debounce_समय अणु
	ADC_DEBOUNCE_TIME_0_5MS = 0,	/* 0.5ms */
	ADC_DEBOUNCE_TIME_10MS,		/* 10ms */
	ADC_DEBOUNCE_TIME_25MS,		/* 25ms */
	ADC_DEBOUNCE_TIME_38_62MS,	/* 38.62ms */
पूर्ण;

काष्ठा max8997_muic_irq अणु
	अचिन्हित पूर्णांक irq;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक virq;
पूर्ण;

अटल काष्ठा max8997_muic_irq muic_irqs[] = अणु
	अणु MAX8997_MUICIRQ_ADCError,	"muic-ADCERROR" पूर्ण,
	अणु MAX8997_MUICIRQ_ADCLow,	"muic-ADCLOW" पूर्ण,
	अणु MAX8997_MUICIRQ_ADC,		"muic-ADC" पूर्ण,
	अणु MAX8997_MUICIRQ_VBVolt,	"muic-VBVOLT" पूर्ण,
	अणु MAX8997_MUICIRQ_DBChg,	"muic-DBCHG" पूर्ण,
	अणु MAX8997_MUICIRQ_DCDTmr,	"muic-DCDTMR" पूर्ण,
	अणु MAX8997_MUICIRQ_ChgDetRun,	"muic-CHGDETRUN" पूर्ण,
	अणु MAX8997_MUICIRQ_ChgTyp,	"muic-CHGTYP" पूर्ण,
	अणु MAX8997_MUICIRQ_OVP,		"muic-OVP" पूर्ण,
	अणु MAX8997_PMICIRQ_CHGINS,	"pmic-CHGINS" पूर्ण,
	अणु MAX8997_PMICIRQ_CHGRM,	"pmic-CHGRM" पूर्ण,
पूर्ण;

/* Define supported cable type */
क्रमागत max8997_muic_acc_type अणु
	MAX8997_MUIC_ADC_GROUND = 0x0,
	MAX8997_MUIC_ADC_MHL,			/* MHL*/
	MAX8997_MUIC_ADC_REMOTE_S1_BUTTON,
	MAX8997_MUIC_ADC_REMOTE_S2_BUTTON,
	MAX8997_MUIC_ADC_REMOTE_S3_BUTTON,
	MAX8997_MUIC_ADC_REMOTE_S4_BUTTON,
	MAX8997_MUIC_ADC_REMOTE_S5_BUTTON,
	MAX8997_MUIC_ADC_REMOTE_S6_BUTTON,
	MAX8997_MUIC_ADC_REMOTE_S7_BUTTON,
	MAX8997_MUIC_ADC_REMOTE_S8_BUTTON,
	MAX8997_MUIC_ADC_REMOTE_S9_BUTTON,
	MAX8997_MUIC_ADC_REMOTE_S10_BUTTON,
	MAX8997_MUIC_ADC_REMOTE_S11_BUTTON,
	MAX8997_MUIC_ADC_REMOTE_S12_BUTTON,
	MAX8997_MUIC_ADC_RESERVED_ACC_1,
	MAX8997_MUIC_ADC_RESERVED_ACC_2,
	MAX8997_MUIC_ADC_RESERVED_ACC_3,
	MAX8997_MUIC_ADC_RESERVED_ACC_4,
	MAX8997_MUIC_ADC_RESERVED_ACC_5,
	MAX8997_MUIC_ADC_CEA936_AUDIO,
	MAX8997_MUIC_ADC_PHONE_POWERED_DEV,
	MAX8997_MUIC_ADC_TTY_CONVERTER,
	MAX8997_MUIC_ADC_UART_CABLE,
	MAX8997_MUIC_ADC_CEA936A_TYPE1_CHG,
	MAX8997_MUIC_ADC_FACTORY_MODE_USB_OFF,	/* JIG-USB-OFF */
	MAX8997_MUIC_ADC_FACTORY_MODE_USB_ON,	/* JIG-USB-ON */
	MAX8997_MUIC_ADC_AV_CABLE_NOLOAD,	/* DESKDOCK */
	MAX8997_MUIC_ADC_CEA936A_TYPE2_CHG,
	MAX8997_MUIC_ADC_FACTORY_MODE_UART_OFF,	/* JIG-UART */
	MAX8997_MUIC_ADC_FACTORY_MODE_UART_ON,	/* CARDOCK */
	MAX8997_MUIC_ADC_AUDIO_MODE_REMOTE,
	MAX8997_MUIC_ADC_OPEN,			/* OPEN */
पूर्ण;

क्रमागत max8997_muic_cable_group अणु
	MAX8997_CABLE_GROUP_ADC = 0,
	MAX8997_CABLE_GROUP_ADC_GND,
	MAX8997_CABLE_GROUP_CHG,
	MAX8997_CABLE_GROUP_VBVOLT,
पूर्ण;

क्रमागत max8997_muic_usb_type अणु
	MAX8997_USB_HOST,
	MAX8997_USB_DEVICE,
पूर्ण;

क्रमागत max8997_muic_अक्षरger_type अणु
	MAX8997_CHARGER_TYPE_NONE = 0,
	MAX8997_CHARGER_TYPE_USB,
	MAX8997_CHARGER_TYPE_DOWNSTREAM_PORT,
	MAX8997_CHARGER_TYPE_DEDICATED_CHG,
	MAX8997_CHARGER_TYPE_500MA,
	MAX8997_CHARGER_TYPE_1A,
	MAX8997_CHARGER_TYPE_DEAD_BATTERY = 7,
पूर्ण;

काष्ठा max8997_muic_info अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *muic;
	काष्ठा extcon_dev *edev;
	पूर्णांक prev_cable_type;
	पूर्णांक prev_chg_type;
	u8 status[2];

	पूर्णांक irq;
	काष्ठा work_काष्ठा irq_work;
	काष्ठा mutex mutex;

	काष्ठा max8997_muic_platक्रमm_data *muic_pdata;
	क्रमागत max8997_muic_अक्षरger_type pre_अक्षरger_type;

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

अटल स्थिर अचिन्हित पूर्णांक max8997_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_CHG_USB_FAST,
	EXTCON_CHG_USB_SLOW,
	EXTCON_CHG_USB_CDP,
	EXTCON_DISP_MHL,
	EXTCON_DOCK,
	EXTCON_JIG,
	EXTCON_NONE,
पूर्ण;

/*
 * max8997_muic_set_debounce_समय - Set the debounce समय of ADC
 * @info: the instance including निजी data of max8997 MUIC
 * @समय: the debounce समय of ADC
 */
अटल पूर्णांक max8997_muic_set_debounce_समय(काष्ठा max8997_muic_info *info,
		क्रमागत max8997_muic_adc_debounce_समय समय)
अणु
	पूर्णांक ret;

	चयन (समय) अणु
	हाल ADC_DEBOUNCE_TIME_0_5MS:
	हाल ADC_DEBOUNCE_TIME_10MS:
	हाल ADC_DEBOUNCE_TIME_25MS:
	हाल ADC_DEBOUNCE_TIME_38_62MS:
		ret = max8997_update_reg(info->muic,
					  MAX8997_MUIC_REG_CONTROL3,
					  समय << CONTROL3_ADCDBSET_SHIFT,
					  CONTROL3_ADCDBSET_MASK);
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
 * max8997_muic_set_path - Set hardware line according to attached cable
 * @info: the instance including निजी data of max8997 MUIC
 * @value: the path according to attached cable
 * @attached: the state of cable (true:attached, false:detached)
 *
 * The max8997 MUIC device share outside H/W line among a varity of cables,
 * so this function set पूर्णांकernal path of H/W line according to the type of
 * attached cable.
 */
अटल पूर्णांक max8997_muic_set_path(काष्ठा max8997_muic_info *info,
		u8 val, bool attached)
अणु
	पूर्णांक ret;
	u8 ctrl1, ctrl2 = 0;

	अगर (attached)
		ctrl1 = val;
	अन्यथा
		ctrl1 = CONTROL1_SW_OPEN;

	ret = max8997_update_reg(info->muic,
			MAX8997_MUIC_REG_CONTROL1, ctrl1, COMP_SW_MASK);
	अगर (ret < 0) अणु
		dev_err(info->dev, "failed to update MUIC register\n");
		वापस ret;
	पूर्ण

	अगर (attached)
		ctrl2 |= CONTROL2_CPEN_MASK;	/* LowPwr=0, CPEn=1 */
	अन्यथा
		ctrl2 |= CONTROL2_LOWPWR_MASK;	/* LowPwr=1, CPEn=0 */

	ret = max8997_update_reg(info->muic,
			MAX8997_MUIC_REG_CONTROL2, ctrl2,
			CONTROL2_LOWPWR_MASK | CONTROL2_CPEN_MASK);
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
 * max8997_muic_get_cable_type - Return cable type and check cable state
 * @info: the instance including निजी data of max8997 MUIC
 * @group: the path according to attached cable
 * @attached: store cable state and वापस
 *
 * This function check the cable state either attached or detached,
 * and then भागide precise type of cable according to cable group.
 *	- MAX8997_CABLE_GROUP_ADC
 *	- MAX8997_CABLE_GROUP_CHG
 */
अटल पूर्णांक max8997_muic_get_cable_type(काष्ठा max8997_muic_info *info,
		क्रमागत max8997_muic_cable_group group, bool *attached)
अणु
	पूर्णांक cable_type = 0;
	पूर्णांक adc;
	पूर्णांक chg_type;

	चयन (group) अणु
	हाल MAX8997_CABLE_GROUP_ADC:
		/*
		 * Read ADC value to check cable type and decide cable state
		 * according to cable type
		 */
		adc = info->status[0] & STATUS1_ADC_MASK;
		adc >>= STATUS1_ADC_SHIFT;

		/*
		 * Check current cable state/cable type and store cable type
		 * (info->prev_cable_type) क्रम handling cable when cable is
		 * detached.
		 */
		अगर (adc == MAX8997_MUIC_ADC_OPEN) अणु
			*attached = false;

			cable_type = info->prev_cable_type;
			info->prev_cable_type = MAX8997_MUIC_ADC_OPEN;
		पूर्ण अन्यथा अणु
			*attached = true;

			cable_type = info->prev_cable_type = adc;
		पूर्ण
		अवरोध;
	हाल MAX8997_CABLE_GROUP_CHG:
		/*
		 * Read अक्षरger type to check cable type and decide cable state
		 * according to type of अक्षरger cable.
		 */
		chg_type = info->status[1] & STATUS2_CHGTYP_MASK;
		chg_type >>= STATUS2_CHGTYP_SHIFT;

		अगर (chg_type == MAX8997_CHARGER_TYPE_NONE) अणु
			*attached = false;

			cable_type = info->prev_chg_type;
			info->prev_chg_type = MAX8997_CHARGER_TYPE_NONE;
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

अटल पूर्णांक max8997_muic_handle_usb(काष्ठा max8997_muic_info *info,
			क्रमागत max8997_muic_usb_type usb_type, bool attached)
अणु
	पूर्णांक ret = 0;

	ret = max8997_muic_set_path(info, info->path_usb, attached);
	अगर (ret < 0) अणु
		dev_err(info->dev, "failed to update muic register\n");
		वापस ret;
	पूर्ण

	चयन (usb_type) अणु
	हाल MAX8997_USB_HOST:
		extcon_set_state_sync(info->edev, EXTCON_USB_HOST, attached);
		अवरोध;
	हाल MAX8997_USB_DEVICE:
		extcon_set_state_sync(info->edev, EXTCON_USB, attached);
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
					attached);
		अवरोध;
	शेष:
		dev_err(info->dev, "failed to detect %s usb cable\n",
			attached ? "attached" : "detached");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max8997_muic_handle_करोck(काष्ठा max8997_muic_info *info,
			पूर्णांक cable_type, bool attached)
अणु
	पूर्णांक ret = 0;

	ret = max8997_muic_set_path(info, CONTROL1_SW_AUDIO, attached);
	अगर (ret) अणु
		dev_err(info->dev, "failed to update muic register\n");
		वापस ret;
	पूर्ण

	चयन (cable_type) अणु
	हाल MAX8997_MUIC_ADC_AV_CABLE_NOLOAD:
	हाल MAX8997_MUIC_ADC_FACTORY_MODE_UART_ON:
		extcon_set_state_sync(info->edev, EXTCON_DOCK, attached);
		अवरोध;
	शेष:
		dev_err(info->dev, "failed to detect %s dock device\n",
			attached ? "attached" : "detached");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max8997_muic_handle_jig_uart(काष्ठा max8997_muic_info *info,
			bool attached)
अणु
	पूर्णांक ret = 0;

	/* चयन to UART */
	ret = max8997_muic_set_path(info, info->path_uart, attached);
	अगर (ret) अणु
		dev_err(info->dev, "failed to update muic register\n");
		वापस ret;
	पूर्ण

	extcon_set_state_sync(info->edev, EXTCON_JIG, attached);

	वापस 0;
पूर्ण

अटल पूर्णांक max8997_muic_adc_handler(काष्ठा max8997_muic_info *info)
अणु
	पूर्णांक cable_type;
	bool attached;
	पूर्णांक ret = 0;

	/* Check cable state which is either detached or attached */
	cable_type = max8997_muic_get_cable_type(info,
				MAX8997_CABLE_GROUP_ADC, &attached);

	चयन (cable_type) अणु
	हाल MAX8997_MUIC_ADC_GROUND:
		ret = max8997_muic_handle_usb(info, MAX8997_USB_HOST, attached);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल MAX8997_MUIC_ADC_MHL:
		extcon_set_state_sync(info->edev, EXTCON_DISP_MHL, attached);
		अवरोध;
	हाल MAX8997_MUIC_ADC_FACTORY_MODE_USB_OFF:
	हाल MAX8997_MUIC_ADC_FACTORY_MODE_USB_ON:
		ret = max8997_muic_handle_usb(info,
					     MAX8997_USB_DEVICE, attached);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल MAX8997_MUIC_ADC_AV_CABLE_NOLOAD:
	हाल MAX8997_MUIC_ADC_FACTORY_MODE_UART_ON:
		ret = max8997_muic_handle_करोck(info, cable_type, attached);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल MAX8997_MUIC_ADC_FACTORY_MODE_UART_OFF:
		ret = max8997_muic_handle_jig_uart(info, attached);
		अवरोध;
	हाल MAX8997_MUIC_ADC_REMOTE_S1_BUTTON:
	हाल MAX8997_MUIC_ADC_REMOTE_S2_BUTTON:
	हाल MAX8997_MUIC_ADC_REMOTE_S3_BUTTON:
	हाल MAX8997_MUIC_ADC_REMOTE_S4_BUTTON:
	हाल MAX8997_MUIC_ADC_REMOTE_S5_BUTTON:
	हाल MAX8997_MUIC_ADC_REMOTE_S6_BUTTON:
	हाल MAX8997_MUIC_ADC_REMOTE_S7_BUTTON:
	हाल MAX8997_MUIC_ADC_REMOTE_S8_BUTTON:
	हाल MAX8997_MUIC_ADC_REMOTE_S9_BUTTON:
	हाल MAX8997_MUIC_ADC_REMOTE_S10_BUTTON:
	हाल MAX8997_MUIC_ADC_REMOTE_S11_BUTTON:
	हाल MAX8997_MUIC_ADC_REMOTE_S12_BUTTON:
	हाल MAX8997_MUIC_ADC_RESERVED_ACC_1:
	हाल MAX8997_MUIC_ADC_RESERVED_ACC_2:
	हाल MAX8997_MUIC_ADC_RESERVED_ACC_3:
	हाल MAX8997_MUIC_ADC_RESERVED_ACC_4:
	हाल MAX8997_MUIC_ADC_RESERVED_ACC_5:
	हाल MAX8997_MUIC_ADC_CEA936_AUDIO:
	हाल MAX8997_MUIC_ADC_PHONE_POWERED_DEV:
	हाल MAX8997_MUIC_ADC_TTY_CONVERTER:
	हाल MAX8997_MUIC_ADC_UART_CABLE:
	हाल MAX8997_MUIC_ADC_CEA936A_TYPE1_CHG:
	हाल MAX8997_MUIC_ADC_CEA936A_TYPE2_CHG:
	हाल MAX8997_MUIC_ADC_AUDIO_MODE_REMOTE:
		/*
		 * This cable isn't used in general हाल अगर it is specially
		 * needed to detect additional cable, should implement
		 * proper operation when this cable is attached/detached.
		 */
		dev_info(info->dev,
			"cable is %s but it isn't used (type:0x%x)\n",
			attached ? "attached" : "detached", cable_type);
		वापस -EAGAIN;
	शेष:
		dev_err(info->dev,
			"failed to detect %s unknown cable (type:0x%x)\n",
			attached ? "attached" : "detached", cable_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max8997_muic_chg_handler(काष्ठा max8997_muic_info *info)
अणु
	पूर्णांक chg_type;
	bool attached;
	पूर्णांक adc;

	chg_type = max8997_muic_get_cable_type(info,
				MAX8997_CABLE_GROUP_CHG, &attached);

	चयन (chg_type) अणु
	हाल MAX8997_CHARGER_TYPE_NONE:
		अवरोध;
	हाल MAX8997_CHARGER_TYPE_USB:
		adc = info->status[0] & STATUS1_ADC_MASK;
		adc >>= STATUS1_ADC_SHIFT;

		अगर ((adc & STATUS1_ADC_MASK) == MAX8997_MUIC_ADC_OPEN) अणु
			max8997_muic_handle_usb(info,
					MAX8997_USB_DEVICE, attached);
		पूर्ण
		अवरोध;
	हाल MAX8997_CHARGER_TYPE_DOWNSTREAM_PORT:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_CDP,
					attached);
		अवरोध;
	हाल MAX8997_CHARGER_TYPE_DEDICATED_CHG:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_DCP,
					attached);
		अवरोध;
	हाल MAX8997_CHARGER_TYPE_500MA:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SLOW,
					attached);
		अवरोध;
	हाल MAX8997_CHARGER_TYPE_1A:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_FAST,
					attached);
		अवरोध;
	शेष:
		dev_err(info->dev,
			"failed to detect %s unknown chg cable (type:0x%x)\n",
			attached ? "attached" : "detached", chg_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम max8997_muic_irq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max8997_muic_info *info = container_of(work,
			काष्ठा max8997_muic_info, irq_work);
	पूर्णांक irq_type = 0;
	पूर्णांक i, ret;

	अगर (!info->edev)
		वापस;

	mutex_lock(&info->mutex);

	क्रम (i = 0; i < ARRAY_SIZE(muic_irqs); i++)
		अगर (info->irq == muic_irqs[i].virq)
			irq_type = muic_irqs[i].irq;

	ret = max8997_bulk_पढ़ो(info->muic, MAX8997_MUIC_REG_STATUS1,
				2, info->status);
	अगर (ret) अणु
		dev_err(info->dev, "failed to read muic register\n");
		mutex_unlock(&info->mutex);
		वापस;
	पूर्ण

	चयन (irq_type) अणु
	हाल MAX8997_MUICIRQ_ADCError:
	हाल MAX8997_MUICIRQ_ADCLow:
	हाल MAX8997_MUICIRQ_ADC:
		/* Handle all of cable except क्रम अक्षरger cable */
		ret = max8997_muic_adc_handler(info);
		अवरोध;
	हाल MAX8997_MUICIRQ_VBVolt:
	हाल MAX8997_MUICIRQ_DBChg:
	हाल MAX8997_MUICIRQ_DCDTmr:
	हाल MAX8997_MUICIRQ_ChgDetRun:
	हाल MAX8997_MUICIRQ_ChgTyp:
	हाल MAX8997_PMICIRQ_CHGINS:
	हाल MAX8997_PMICIRQ_CHGRM:
		/* Handle अक्षरger cable */
		ret = max8997_muic_chg_handler(info);
		अवरोध;
	हाल MAX8997_MUICIRQ_OVP:
		अवरोध;
	शेष:
		dev_info(info->dev, "misc interrupt: irq %d occurred\n",
				irq_type);
		mutex_unlock(&info->mutex);
		वापस;
	पूर्ण

	अगर (ret < 0)
		dev_err(info->dev, "failed to handle MUIC interrupt\n");

	mutex_unlock(&info->mutex);
पूर्ण

अटल irqवापस_t max8997_muic_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max8997_muic_info *info = data;

	dev_dbg(info->dev, "irq:%d\n", irq);
	info->irq = irq;

	schedule_work(&info->irq_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max8997_muic_detect_dev(काष्ठा max8997_muic_info *info)
अणु
	पूर्णांक ret = 0;
	पूर्णांक adc;
	पूर्णांक chg_type;
	bool attached;

	mutex_lock(&info->mutex);

	/* Read STATUSx रेजिस्टर to detect accessory */
	ret = max8997_bulk_पढ़ो(info->muic,
			MAX8997_MUIC_REG_STATUS1, 2, info->status);
	अगर (ret) अणु
		dev_err(info->dev, "failed to read MUIC register\n");
		mutex_unlock(&info->mutex);
		वापस ret;
	पूर्ण

	adc = max8997_muic_get_cable_type(info, MAX8997_CABLE_GROUP_ADC,
					&attached);
	अगर (attached && adc != MAX8997_MUIC_ADC_OPEN) अणु
		ret = max8997_muic_adc_handler(info);
		अगर (ret < 0) अणु
			dev_err(info->dev, "Cannot detect ADC cable\n");
			mutex_unlock(&info->mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	chg_type = max8997_muic_get_cable_type(info, MAX8997_CABLE_GROUP_CHG,
					&attached);
	अगर (attached && chg_type != MAX8997_CHARGER_TYPE_NONE) अणु
		ret = max8997_muic_chg_handler(info);
		अगर (ret < 0) अणु
			dev_err(info->dev, "Cannot detect charger cable\n");
			mutex_unlock(&info->mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_unlock(&info->mutex);

	वापस 0;
पूर्ण

अटल व्योम max8997_muic_detect_cable_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max8997_muic_info *info = container_of(to_delayed_work(work),
				काष्ठा max8997_muic_info, wq_detcable);
	पूर्णांक ret;

	ret = max8997_muic_detect_dev(info);
	अगर (ret < 0)
		dev_err(info->dev, "failed to detect cable type\n");
पूर्ण

अटल पूर्णांक max8997_muic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8997_dev *max8997 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max8997_platक्रमm_data *pdata = dev_get_platdata(max8997->dev);
	काष्ठा max8997_muic_info *info;
	पूर्णांक delay_jअगरfies;
	पूर्णांक cable_type;
	bool attached;
	पूर्णांक ret, i;

	info = devm_kzalloc(&pdev->dev, माप(काष्ठा max8997_muic_info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = &pdev->dev;
	info->muic = max8997->muic;

	platक्रमm_set_drvdata(pdev, info);
	mutex_init(&info->mutex);

	INIT_WORK(&info->irq_work, max8997_muic_irq_work);

	क्रम (i = 0; i < ARRAY_SIZE(muic_irqs); i++) अणु
		काष्ठा max8997_muic_irq *muic_irq = &muic_irqs[i];
		अचिन्हित पूर्णांक virq = 0;

		virq = irq_create_mapping(max8997->irq_करोमुख्य, muic_irq->irq);
		अगर (!virq) अणु
			ret = -EINVAL;
			जाओ err_irq;
		पूर्ण
		muic_irq->virq = virq;

		ret = request_thपढ़ोed_irq(virq, शून्य,
				max8997_muic_irq_handler,
				IRQF_NO_SUSPEND,
				muic_irq->name, info);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"failed: irq request (IRQ: %d, error :%d)\n",
				muic_irq->irq, ret);
			जाओ err_irq;
		पूर्ण
	पूर्ण

	/* External connector */
	info->edev = devm_extcon_dev_allocate(&pdev->dev, max8997_extcon_cable);
	अगर (IS_ERR(info->edev)) अणु
		dev_err(&pdev->dev, "failed to allocate memory for extcon\n");
		ret = PTR_ERR(info->edev);
		जाओ err_irq;
	पूर्ण

	ret = devm_extcon_dev_रेजिस्टर(&pdev->dev, info->edev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register extcon device\n");
		जाओ err_irq;
	पूर्ण

	अगर (pdata && pdata->muic_pdata) अणु
		काष्ठा max8997_muic_platक्रमm_data *muic_pdata
			= pdata->muic_pdata;

		/* Initialize रेजिस्टरs according to platक्रमm data */
		क्रम (i = 0; i < muic_pdata->num_init_data; i++) अणु
			max8997_ग_लिखो_reg(info->muic,
					muic_pdata->init_data[i].addr,
					muic_pdata->init_data[i].data);
		पूर्ण

		/*
		 * Default usb/uart path whether UART/USB or AUX_UART/AUX_USB
		 * h/w path of COMP2/COMN1 on CONTROL1 रेजिस्टर.
		 */
		अगर (muic_pdata->path_uart)
			info->path_uart = muic_pdata->path_uart;
		अन्यथा
			info->path_uart = CONTROL1_SW_UART;

		अगर (muic_pdata->path_usb)
			info->path_usb = muic_pdata->path_usb;
		अन्यथा
			info->path_usb = CONTROL1_SW_USB;

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
		info->path_uart = CONTROL1_SW_UART;
		info->path_usb = CONTROL1_SW_USB;
		delay_jअगरfies = msecs_to_jअगरfies(DELAY_MS_DEFAULT);
	पूर्ण

	/* Set initial path क्रम UART when JIG is connected to get serial logs */
	ret = max8997_bulk_पढ़ो(info->muic, MAX8997_MUIC_REG_STATUS1,
				2, info->status);
	अगर (ret) अणु
		dev_err(info->dev, "failed to read MUIC register\n");
		वापस ret;
	पूर्ण
	cable_type = max8997_muic_get_cable_type(info,
					   MAX8997_CABLE_GROUP_ADC, &attached);
	अगर (attached && cable_type == MAX8997_MUIC_ADC_FACTORY_MODE_UART_OFF)
		max8997_muic_set_path(info, info->path_uart, true);

	/* Set ADC debounce समय */
	max8997_muic_set_debounce_समय(info, ADC_DEBOUNCE_TIME_25MS);

	/*
	 * Detect accessory after completing the initialization of platक्रमm
	 *
	 * - Use delayed workqueue to detect cable state and then
	 * notअगरy cable state to notअगरiee/platक्रमm through uevent.
	 * After completing the booting of platक्रमm, the extcon provider
	 * driver should notअगरy cable state to upper layer.
	 */
	INIT_DELAYED_WORK(&info->wq_detcable, max8997_muic_detect_cable_wq);
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &info->wq_detcable,
			delay_jअगरfies);

	वापस 0;

err_irq:
	जबतक (--i >= 0)
		मुक्त_irq(muic_irqs[i].virq, info);
	वापस ret;
पूर्ण

अटल पूर्णांक max8997_muic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8997_muic_info *info = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(muic_irqs); i++)
		मुक्त_irq(muic_irqs[i].virq, info);
	cancel_work_sync(&info->irq_work);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver max8997_muic_driver = अणु
	.driver		= अणु
		.name	= DEV_NAME,
	पूर्ण,
	.probe		= max8997_muic_probe,
	.हटाओ		= max8997_muic_हटाओ,
पूर्ण;

module_platक्रमm_driver(max8997_muic_driver);

MODULE_DESCRIPTION("Maxim MAX8997 Extcon driver");
MODULE_AUTHOR("Donggeun Kim <dg77.kim@samsung.com>");
MODULE_LICENSE("GPL");
