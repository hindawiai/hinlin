<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// extcon-max77843.c - Maxim MAX77843 extcon driver to support
//			MUIC(Micro USB Interface Controller)
//
// Copyright (C) 2015 Samsung Electronics
// Author: Jaewon Kim <jaewon02.kim@samsung.com>

#समावेश <linux/extcon-provider.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/max77693-common.h>
#समावेश <linux/mfd/max77843-निजी.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>

#घोषणा DELAY_MS_DEFAULT		15000	/* unit: millisecond */

क्रमागत max77843_muic_status अणु
	MAX77843_MUIC_STATUS1 = 0,
	MAX77843_MUIC_STATUS2,
	MAX77843_MUIC_STATUS3,

	MAX77843_MUIC_STATUS_NUM,
पूर्ण;

काष्ठा max77843_muic_info अणु
	काष्ठा device *dev;
	काष्ठा max77693_dev *max77843;
	काष्ठा extcon_dev *edev;

	काष्ठा mutex mutex;
	काष्ठा work_काष्ठा irq_work;
	काष्ठा delayed_work wq_detcable;

	u8 status[MAX77843_MUIC_STATUS_NUM];
	पूर्णांक prev_cable_type;
	पूर्णांक prev_chg_type;
	पूर्णांक prev_gnd_type;

	bool irq_adc;
	bool irq_chg;
पूर्ण;

क्रमागत max77843_muic_cable_group अणु
	MAX77843_CABLE_GROUP_ADC = 0,
	MAX77843_CABLE_GROUP_ADC_GND,
	MAX77843_CABLE_GROUP_CHG,
पूर्ण;

क्रमागत max77843_muic_adc_debounce_समय अणु
	MAX77843_DEBOUNCE_TIME_5MS = 0,
	MAX77843_DEBOUNCE_TIME_10MS,
	MAX77843_DEBOUNCE_TIME_25MS,
	MAX77843_DEBOUNCE_TIME_38_62MS,
पूर्ण;

/* Define accessory cable type */
क्रमागत max77843_muic_accessory_type अणु
	MAX77843_MUIC_ADC_GROUND = 0,
	MAX77843_MUIC_ADC_SEND_END_BUTTON,
	MAX77843_MUIC_ADC_REMOTE_S1_BUTTON,
	MAX77843_MUIC_ADC_REMOTE_S2_BUTTON,
	MAX77843_MUIC_ADC_REMOTE_S3_BUTTON,
	MAX77843_MUIC_ADC_REMOTE_S4_BUTTON,
	MAX77843_MUIC_ADC_REMOTE_S5_BUTTON,
	MAX77843_MUIC_ADC_REMOTE_S6_BUTTON,
	MAX77843_MUIC_ADC_REMOTE_S7_BUTTON,
	MAX77843_MUIC_ADC_REMOTE_S8_BUTTON,
	MAX77843_MUIC_ADC_REMOTE_S9_BUTTON,
	MAX77843_MUIC_ADC_REMOTE_S10_BUTTON,
	MAX77843_MUIC_ADC_REMOTE_S11_BUTTON,
	MAX77843_MUIC_ADC_REMOTE_S12_BUTTON,
	MAX77843_MUIC_ADC_RESERVED_ACC_1,
	MAX77843_MUIC_ADC_RESERVED_ACC_2,
	MAX77843_MUIC_ADC_RESERVED_ACC_3, /* SmartDock */
	MAX77843_MUIC_ADC_RESERVED_ACC_4,
	MAX77843_MUIC_ADC_RESERVED_ACC_5,
	MAX77843_MUIC_ADC_AUDIO_DEVICE_TYPE2,
	MAX77843_MUIC_ADC_PHONE_POWERED_DEV,
	MAX77843_MUIC_ADC_TTY_CONVERTER,
	MAX77843_MUIC_ADC_UART_CABLE,
	MAX77843_MUIC_ADC_CEA936A_TYPE1_CHG,
	MAX77843_MUIC_ADC_FACTORY_MODE_USB_OFF,
	MAX77843_MUIC_ADC_FACTORY_MODE_USB_ON,
	MAX77843_MUIC_ADC_AV_CABLE_NOLOAD,
	MAX77843_MUIC_ADC_CEA936A_TYPE2_CHG,
	MAX77843_MUIC_ADC_FACTORY_MODE_UART_OFF,
	MAX77843_MUIC_ADC_FACTORY_MODE_UART_ON,
	MAX77843_MUIC_ADC_AUDIO_DEVICE_TYPE1,
	MAX77843_MUIC_ADC_OPEN,

	/*
	 * The below accessories should check
	 * not only ADC value but also ADC1K and VBVolt value.
	 */
						/* Offset|ADC1K|VBVolt| */
	MAX77843_MUIC_GND_USB_HOST = 0x100,	/*    0x1|    0|     0| */
	MAX77843_MUIC_GND_USB_HOST_VB = 0x101,	/*    0x1|    0|     1| */
	MAX77843_MUIC_GND_MHL = 0x102,		/*    0x1|    1|     0| */
	MAX77843_MUIC_GND_MHL_VB = 0x103,	/*    0x1|    1|     1| */
पूर्ण;

/* Define अक्षरger cable type */
क्रमागत max77843_muic_अक्षरger_type अणु
	MAX77843_MUIC_CHG_NONE = 0,
	MAX77843_MUIC_CHG_USB,
	MAX77843_MUIC_CHG_DOWNSTREAM,
	MAX77843_MUIC_CHG_DEDICATED,
	MAX77843_MUIC_CHG_SPECIAL_500MA,
	MAX77843_MUIC_CHG_SPECIAL_1A,
	MAX77843_MUIC_CHG_SPECIAL_BIAS,
	MAX77843_MUIC_CHG_RESERVED,
	MAX77843_MUIC_CHG_GND,
	MAX77843_MUIC_CHG_DOCK,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक max77843_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_CHG_USB_CDP,
	EXTCON_CHG_USB_FAST,
	EXTCON_CHG_USB_SLOW,
	EXTCON_DISP_MHL,
	EXTCON_DOCK,
	EXTCON_JIG,
	EXTCON_NONE,
पूर्ण;

काष्ठा max77843_muic_irq अणु
	अचिन्हित पूर्णांक irq;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक virq;
पूर्ण;

अटल काष्ठा max77843_muic_irq max77843_muic_irqs[] = अणु
	अणु MAX77843_MUIC_IRQ_INT1_ADC,		"MUIC-ADC" पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT1_ADCERROR,	"MUIC-ADC_ERROR" पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT1_ADC1K,		"MUIC-ADC1K" पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT2_CHGTYP,	"MUIC-CHGTYP" पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT2_CHGDETRUN,	"MUIC-CHGDETRUN" पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT2_DCDTMR,	"MUIC-DCDTMR" पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT2_DXOVP,		"MUIC-DXOVP" पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT2_VBVOLT,	"MUIC-VBVOLT" पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT3_VBADC,		"MUIC-VBADC" पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT3_VDNMON,	"MUIC-VDNMON" पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT3_DNRES,		"MUIC-DNRES" पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT3_MPNACK,	"MUIC-MPNACK"पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT3_MRXBUFOW,	"MUIC-MRXBUFOW"पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT3_MRXTRF,	"MUIC-MRXTRF"पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT3_MRXPERR,	"MUIC-MRXPERR"पूर्ण,
	अणु MAX77843_MUIC_IRQ_INT3_MRXRDY,	"MUIC-MRXRDY"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max77843_muic_regmap_config = अणु
	.reg_bits       = 8,
	.val_bits       = 8,
	.max_रेजिस्टर   = MAX77843_MUIC_REG_END,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max77843_muic_irq[] = अणु
	/* INT1 पूर्णांकerrupt */
	अणु .reg_offset = 0, .mask = MAX77843_MUIC_ADC, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX77843_MUIC_ADCERROR, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX77843_MUIC_ADC1K, पूर्ण,

	/* INT2 पूर्णांकerrupt */
	अणु .reg_offset = 1, .mask = MAX77843_MUIC_CHGTYP, पूर्ण,
	अणु .reg_offset = 1, .mask = MAX77843_MUIC_CHGDETRUN, पूर्ण,
	अणु .reg_offset = 1, .mask = MAX77843_MUIC_DCDTMR, पूर्ण,
	अणु .reg_offset = 1, .mask = MAX77843_MUIC_DXOVP, पूर्ण,
	अणु .reg_offset = 1, .mask = MAX77843_MUIC_VBVOLT, पूर्ण,

	/* INT3 पूर्णांकerrupt */
	अणु .reg_offset = 2, .mask = MAX77843_MUIC_VBADC, पूर्ण,
	अणु .reg_offset = 2, .mask = MAX77843_MUIC_VDNMON, पूर्ण,
	अणु .reg_offset = 2, .mask = MAX77843_MUIC_DNRES, पूर्ण,
	अणु .reg_offset = 2, .mask = MAX77843_MUIC_MPNACK, पूर्ण,
	अणु .reg_offset = 2, .mask = MAX77843_MUIC_MRXBUFOW, पूर्ण,
	अणु .reg_offset = 2, .mask = MAX77843_MUIC_MRXTRF, पूर्ण,
	अणु .reg_offset = 2, .mask = MAX77843_MUIC_MRXPERR, पूर्ण,
	अणु .reg_offset = 2, .mask = MAX77843_MUIC_MRXRDY, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max77843_muic_irq_chip = अणु
	.name           = "max77843-muic",
	.status_base    = MAX77843_MUIC_REG_INT1,
	.mask_base      = MAX77843_MUIC_REG_INTMASK1,
	.mask_invert    = true,
	.num_regs       = 3,
	.irqs           = max77843_muic_irq,
	.num_irqs       = ARRAY_SIZE(max77843_muic_irq),
पूर्ण;

अटल पूर्णांक max77843_muic_set_path(काष्ठा max77843_muic_info *info,
		u8 val, bool attached, bool nobccomp)
अणु
	काष्ठा max77693_dev *max77843 = info->max77843;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक ctrl1, ctrl2;

	अगर (attached)
		ctrl1 = val;
	अन्यथा
		ctrl1 = MAX77843_MUIC_CONTROL1_SW_OPEN;
	अगर (nobccomp) अणु
		/* Disable BC1.2 protocol and क्रमce manual चयन control */
		ctrl1 |= MAX77843_MUIC_CONTROL1_NOBCCOMP_MASK;
	पूर्ण

	ret = regmap_update_bits(max77843->regmap_muic,
			MAX77843_MUIC_REG_CONTROL1,
			MAX77843_MUIC_CONTROL1_COM_SW |
				MAX77843_MUIC_CONTROL1_NOBCCOMP_MASK,
			ctrl1);
	अगर (ret < 0) अणु
		dev_err(info->dev, "Cannot switch MUIC port\n");
		वापस ret;
	पूर्ण

	अगर (attached)
		ctrl2 = MAX77843_MUIC_CONTROL2_CPEN_MASK;
	अन्यथा
		ctrl2 = MAX77843_MUIC_CONTROL2_LOWPWR_MASK;

	ret = regmap_update_bits(max77843->regmap_muic,
			MAX77843_MUIC_REG_CONTROL2,
			MAX77843_MUIC_CONTROL2_LOWPWR_MASK |
			MAX77843_MUIC_CONTROL2_CPEN_MASK, ctrl2);
	अगर (ret < 0) अणु
		dev_err(info->dev, "Cannot update lowpower mode\n");
		वापस ret;
	पूर्ण

	dev_dbg(info->dev,
		"CONTROL1 : 0x%02x, CONTROL2 : 0x%02x, state : %s\n",
		ctrl1, ctrl2, attached ? "attached" : "detached");

	वापस 0;
पूर्ण

अटल व्योम max77843_अक्षरger_set_otg_vbus(काष्ठा max77843_muic_info *info,
		 bool on)
अणु
	काष्ठा max77693_dev *max77843 = info->max77843;
	अचिन्हित पूर्णांक cnfg00;

	अगर (on)
		cnfg00 = MAX77843_CHG_OTG_MASK | MAX77843_CHG_BOOST_MASK;
	अन्यथा
		cnfg00 = MAX77843_CHG_ENABLE | MAX77843_CHG_BUCK_MASK;

	regmap_update_bits(max77843->regmap_chg, MAX77843_CHG_REG_CHG_CNFG_00,
			   MAX77843_CHG_MODE_MASK, cnfg00);
पूर्ण

अटल पूर्णांक max77843_muic_get_cable_type(काष्ठा max77843_muic_info *info,
		क्रमागत max77843_muic_cable_group group, bool *attached)
अणु
	पूर्णांक adc, chg_type, cable_type, gnd_type;

	adc = info->status[MAX77843_MUIC_STATUS1] &
			MAX77843_MUIC_STATUS1_ADC_MASK;
	adc >>= MAX77843_MUIC_STATUS1_ADC_SHIFT;

	चयन (group) अणु
	हाल MAX77843_CABLE_GROUP_ADC:
		अगर (adc == MAX77843_MUIC_ADC_OPEN) अणु
			*attached = false;
			cable_type = info->prev_cable_type;
			info->prev_cable_type = MAX77843_MUIC_ADC_OPEN;
		पूर्ण अन्यथा अणु
			*attached = true;
			cable_type = info->prev_cable_type = adc;
		पूर्ण
		अवरोध;
	हाल MAX77843_CABLE_GROUP_CHG:
		chg_type = info->status[MAX77843_MUIC_STATUS2] &
				MAX77843_MUIC_STATUS2_CHGTYP_MASK;

		/* Check GROUND accessory with अक्षरger cable */
		अगर (adc == MAX77843_MUIC_ADC_GROUND) अणु
			अगर (chg_type == MAX77843_MUIC_CHG_NONE) अणु
				/*
				 * The following state when अक्षरger cable is
				 * disconnected but the GROUND accessory still
				 * connected.
				 */
				*attached = false;
				cable_type = info->prev_chg_type;
				info->prev_chg_type = MAX77843_MUIC_CHG_NONE;
			पूर्ण अन्यथा अणु

				/*
				 * The following state when अक्षरger cable is
				 * connected on the GROUND accessory.
				 */
				*attached = true;
				cable_type = MAX77843_MUIC_CHG_GND;
				info->prev_chg_type = MAX77843_MUIC_CHG_GND;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (adc == MAX77843_MUIC_ADC_RESERVED_ACC_3) अणु /* SmartDock */
			अगर (chg_type == MAX77843_MUIC_CHG_NONE) अणु
				*attached = false;
				cable_type = info->prev_chg_type;
				info->prev_chg_type = MAX77843_MUIC_CHG_NONE;
			पूर्ण अन्यथा अणु
				*attached = true;
				cable_type = MAX77843_MUIC_CHG_DOCK;
				info->prev_chg_type = MAX77843_MUIC_CHG_DOCK;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (chg_type == MAX77843_MUIC_CHG_NONE) अणु
			*attached = false;
			cable_type = info->prev_chg_type;
			info->prev_chg_type = MAX77843_MUIC_CHG_NONE;
		पूर्ण अन्यथा अणु
			*attached = true;
			cable_type = info->prev_chg_type = chg_type;
		पूर्ण
		अवरोध;
	हाल MAX77843_CABLE_GROUP_ADC_GND:
		अगर (adc == MAX77843_MUIC_ADC_OPEN) अणु
			*attached = false;
			cable_type = info->prev_gnd_type;
			info->prev_gnd_type = MAX77843_MUIC_ADC_OPEN;
		पूर्ण अन्यथा अणु
			*attached = true;

			/*
			 * Offset|ADC1K|VBVolt|
			 *    0x1|    0|     0| USB-HOST
			 *    0x1|    0|     1| USB-HOST with VB
			 *    0x1|    1|     0| MHL
			 *    0x1|    1|     1| MHL with VB
			 */
			/* Get ADC1K रेजिस्टर bit */
			gnd_type = (info->status[MAX77843_MUIC_STATUS1] &
					MAX77843_MUIC_STATUS1_ADC1K_MASK);

			/* Get VBVolt रेजिस्टर bit */
			gnd_type |= (info->status[MAX77843_MUIC_STATUS2] &
					MAX77843_MUIC_STATUS2_VBVOLT_MASK);
			gnd_type >>= MAX77843_MUIC_STATUS2_VBVOLT_SHIFT;

			/* Offset of GND cable */
			gnd_type |= MAX77843_MUIC_GND_USB_HOST;
			cable_type = info->prev_gnd_type = gnd_type;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(info->dev, "Unknown cable group (%d)\n", group);
		cable_type = -EINVAL;
		अवरोध;
	पूर्ण

	वापस cable_type;
पूर्ण

अटल पूर्णांक max77843_muic_adc_gnd_handler(काष्ठा max77843_muic_info *info)
अणु
	पूर्णांक ret, gnd_cable_type;
	bool attached;

	gnd_cable_type = max77843_muic_get_cable_type(info,
			MAX77843_CABLE_GROUP_ADC_GND, &attached);
	dev_dbg(info->dev, "external connector is %s (gnd:0x%02x)\n",
			attached ? "attached" : "detached", gnd_cable_type);

	चयन (gnd_cable_type) अणु
	हाल MAX77843_MUIC_GND_USB_HOST:
	हाल MAX77843_MUIC_GND_USB_HOST_VB:
		ret = max77843_muic_set_path(info,
					     MAX77843_MUIC_CONTROL1_SW_USB,
					     attached, false);
		अगर (ret < 0)
			वापस ret;

		extcon_set_state_sync(info->edev, EXTCON_USB_HOST, attached);
		max77843_अक्षरger_set_otg_vbus(info, attached);
		अवरोध;
	हाल MAX77843_MUIC_GND_MHL_VB:
	हाल MAX77843_MUIC_GND_MHL:
		ret = max77843_muic_set_path(info,
					     MAX77843_MUIC_CONTROL1_SW_OPEN,
					     attached, false);
		अगर (ret < 0)
			वापस ret;

		extcon_set_state_sync(info->edev, EXTCON_DISP_MHL, attached);
		अवरोध;
	शेष:
		dev_err(info->dev, "failed to detect %s accessory(gnd:0x%x)\n",
			attached ? "attached" : "detached", gnd_cable_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77843_muic_jig_handler(काष्ठा max77843_muic_info *info,
		पूर्णांक cable_type, bool attached)
अणु
	पूर्णांक ret;
	u8 path = MAX77843_MUIC_CONTROL1_SW_OPEN;

	dev_dbg(info->dev, "external connector is %s (adc:0x%02x)\n",
			attached ? "attached" : "detached", cable_type);

	चयन (cable_type) अणु
	हाल MAX77843_MUIC_ADC_FACTORY_MODE_USB_OFF:
	हाल MAX77843_MUIC_ADC_FACTORY_MODE_USB_ON:
		path = MAX77843_MUIC_CONTROL1_SW_USB;
		अवरोध;
	हाल MAX77843_MUIC_ADC_FACTORY_MODE_UART_OFF:
		path = MAX77843_MUIC_CONTROL1_SW_UART;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = max77843_muic_set_path(info, path, attached, false);
	अगर (ret < 0)
		वापस ret;

	extcon_set_state_sync(info->edev, EXTCON_JIG, attached);

	वापस 0;
पूर्ण

अटल पूर्णांक max77843_muic_करोck_handler(काष्ठा max77843_muic_info *info,
		bool attached)
अणु
	पूर्णांक ret;

	dev_dbg(info->dev, "external connector is %s (adc: 0x10)\n",
			attached ? "attached" : "detached");

	ret = max77843_muic_set_path(info, MAX77843_MUIC_CONTROL1_SW_USB,
				     attached, attached);
	अगर (ret < 0)
		वापस ret;

	extcon_set_state_sync(info->edev, EXTCON_DISP_MHL, attached);
	extcon_set_state_sync(info->edev, EXTCON_USB_HOST, attached);
	extcon_set_state_sync(info->edev, EXTCON_DOCK, attached);

	वापस 0;
पूर्ण

अटल पूर्णांक max77843_muic_adc_handler(काष्ठा max77843_muic_info *info)
अणु
	पूर्णांक ret, cable_type;
	bool attached;

	cable_type = max77843_muic_get_cable_type(info,
			MAX77843_CABLE_GROUP_ADC, &attached);

	dev_dbg(info->dev,
		"external connector is %s (adc:0x%02x, prev_adc:0x%x)\n",
		attached ? "attached" : "detached", cable_type,
		info->prev_cable_type);

	चयन (cable_type) अणु
	हाल MAX77843_MUIC_ADC_RESERVED_ACC_3: /* SmartDock */
		ret = max77843_muic_करोck_handler(info, attached);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल MAX77843_MUIC_ADC_GROUND:
		ret = max77843_muic_adc_gnd_handler(info);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल MAX77843_MUIC_ADC_FACTORY_MODE_USB_OFF:
	हाल MAX77843_MUIC_ADC_FACTORY_MODE_USB_ON:
	हाल MAX77843_MUIC_ADC_FACTORY_MODE_UART_OFF:
		ret = max77843_muic_jig_handler(info, cable_type, attached);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल MAX77843_MUIC_ADC_SEND_END_BUTTON:
	हाल MAX77843_MUIC_ADC_REMOTE_S1_BUTTON:
	हाल MAX77843_MUIC_ADC_REMOTE_S2_BUTTON:
	हाल MAX77843_MUIC_ADC_REMOTE_S3_BUTTON:
	हाल MAX77843_MUIC_ADC_REMOTE_S4_BUTTON:
	हाल MAX77843_MUIC_ADC_REMOTE_S5_BUTTON:
	हाल MAX77843_MUIC_ADC_REMOTE_S6_BUTTON:
	हाल MAX77843_MUIC_ADC_REMOTE_S7_BUTTON:
	हाल MAX77843_MUIC_ADC_REMOTE_S8_BUTTON:
	हाल MAX77843_MUIC_ADC_REMOTE_S9_BUTTON:
	हाल MAX77843_MUIC_ADC_REMOTE_S10_BUTTON:
	हाल MAX77843_MUIC_ADC_REMOTE_S11_BUTTON:
	हाल MAX77843_MUIC_ADC_REMOTE_S12_BUTTON:
	हाल MAX77843_MUIC_ADC_RESERVED_ACC_1:
	हाल MAX77843_MUIC_ADC_RESERVED_ACC_2:
	हाल MAX77843_MUIC_ADC_RESERVED_ACC_4:
	हाल MAX77843_MUIC_ADC_RESERVED_ACC_5:
	हाल MAX77843_MUIC_ADC_AUDIO_DEVICE_TYPE2:
	हाल MAX77843_MUIC_ADC_PHONE_POWERED_DEV:
	हाल MAX77843_MUIC_ADC_TTY_CONVERTER:
	हाल MAX77843_MUIC_ADC_UART_CABLE:
	हाल MAX77843_MUIC_ADC_CEA936A_TYPE1_CHG:
	हाल MAX77843_MUIC_ADC_AV_CABLE_NOLOAD:
	हाल MAX77843_MUIC_ADC_CEA936A_TYPE2_CHG:
	हाल MAX77843_MUIC_ADC_FACTORY_MODE_UART_ON:
	हाल MAX77843_MUIC_ADC_AUDIO_DEVICE_TYPE1:
	हाल MAX77843_MUIC_ADC_OPEN:
		dev_err(info->dev,
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

अटल पूर्णांक max77843_muic_chg_handler(काष्ठा max77843_muic_info *info)
अणु
	पूर्णांक ret, chg_type, gnd_type;
	bool attached;

	chg_type = max77843_muic_get_cable_type(info,
			MAX77843_CABLE_GROUP_CHG, &attached);

	dev_dbg(info->dev,
		"external connector is %s(chg_type:0x%x, prev_chg_type:0x%x)\n",
		attached ? "attached" : "detached",
		chg_type, info->prev_chg_type);

	चयन (chg_type) अणु
	हाल MAX77843_MUIC_CHG_USB:
		ret = max77843_muic_set_path(info,
					     MAX77843_MUIC_CONTROL1_SW_USB,
					     attached, false);
		अगर (ret < 0)
			वापस ret;

		extcon_set_state_sync(info->edev, EXTCON_USB, attached);
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
					attached);
		अवरोध;
	हाल MAX77843_MUIC_CHG_DOWNSTREAM:
		ret = max77843_muic_set_path(info,
					     MAX77843_MUIC_CONTROL1_SW_OPEN,
					     attached, false);
		अगर (ret < 0)
			वापस ret;

		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_CDP,
					attached);
		अवरोध;
	हाल MAX77843_MUIC_CHG_DEDICATED:
		ret = max77843_muic_set_path(info,
					     MAX77843_MUIC_CONTROL1_SW_OPEN,
					     attached, false);
		अगर (ret < 0)
			वापस ret;

		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_DCP,
					attached);
		अवरोध;
	हाल MAX77843_MUIC_CHG_SPECIAL_500MA:
		ret = max77843_muic_set_path(info,
					     MAX77843_MUIC_CONTROL1_SW_OPEN,
					     attached, false);
		अगर (ret < 0)
			वापस ret;

		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SLOW,
					attached);
		अवरोध;
	हाल MAX77843_MUIC_CHG_SPECIAL_1A:
		ret = max77843_muic_set_path(info,
					     MAX77843_MUIC_CONTROL1_SW_OPEN,
					     attached, false);
		अगर (ret < 0)
			वापस ret;

		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_FAST,
					attached);
		अवरोध;
	हाल MAX77843_MUIC_CHG_GND:
		gnd_type = max77843_muic_get_cable_type(info,
				MAX77843_CABLE_GROUP_ADC_GND, &attached);

		/* Charger cable on MHL accessory is attach or detach */
		अगर (gnd_type == MAX77843_MUIC_GND_MHL_VB)
			extcon_set_state_sync(info->edev, EXTCON_CHG_USB_DCP,
						true);
		अन्यथा अगर (gnd_type == MAX77843_MUIC_GND_MHL)
			extcon_set_state_sync(info->edev, EXTCON_CHG_USB_DCP,
						false);
		अवरोध;
	हाल MAX77843_MUIC_CHG_DOCK:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_DCP, attached);
		अवरोध;
	हाल MAX77843_MUIC_CHG_NONE:
		अवरोध;
	शेष:
		dev_err(info->dev,
			"failed to detect %s accessory (chg_type:0x%x)\n",
			attached ? "attached" : "detached", chg_type);

		max77843_muic_set_path(info, MAX77843_MUIC_CONTROL1_SW_OPEN,
				       attached, false);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम max77843_muic_irq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max77843_muic_info *info = container_of(work,
			काष्ठा max77843_muic_info, irq_work);
	काष्ठा max77693_dev *max77843 = info->max77843;
	पूर्णांक ret = 0;

	mutex_lock(&info->mutex);

	ret = regmap_bulk_पढ़ो(max77843->regmap_muic,
			MAX77843_MUIC_REG_STATUS1, info->status,
			MAX77843_MUIC_STATUS_NUM);
	अगर (ret) अणु
		dev_err(info->dev, "Cannot read STATUS registers\n");
		mutex_unlock(&info->mutex);
		वापस;
	पूर्ण

	अगर (info->irq_adc) अणु
		ret = max77843_muic_adc_handler(info);
		अगर (ret)
			dev_err(info->dev, "Unknown cable type\n");
		info->irq_adc = false;
	पूर्ण

	अगर (info->irq_chg) अणु
		ret = max77843_muic_chg_handler(info);
		अगर (ret)
			dev_err(info->dev, "Unknown charger type\n");
		info->irq_chg = false;
	पूर्ण

	mutex_unlock(&info->mutex);
पूर्ण

अटल irqवापस_t max77843_muic_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max77843_muic_info *info = data;
	पूर्णांक i, irq_type = -1;

	क्रम (i = 0; i < ARRAY_SIZE(max77843_muic_irqs); i++)
		अगर (irq == max77843_muic_irqs[i].virq)
			irq_type = max77843_muic_irqs[i].irq;

	चयन (irq_type) अणु
	हाल MAX77843_MUIC_IRQ_INT1_ADC:
	हाल MAX77843_MUIC_IRQ_INT1_ADCERROR:
	हाल MAX77843_MUIC_IRQ_INT1_ADC1K:
		info->irq_adc = true;
		अवरोध;
	हाल MAX77843_MUIC_IRQ_INT2_CHGTYP:
	हाल MAX77843_MUIC_IRQ_INT2_CHGDETRUN:
	हाल MAX77843_MUIC_IRQ_INT2_DCDTMR:
	हाल MAX77843_MUIC_IRQ_INT2_DXOVP:
	हाल MAX77843_MUIC_IRQ_INT2_VBVOLT:
		info->irq_chg = true;
		अवरोध;
	हाल MAX77843_MUIC_IRQ_INT3_VBADC:
	हाल MAX77843_MUIC_IRQ_INT3_VDNMON:
	हाल MAX77843_MUIC_IRQ_INT3_DNRES:
	हाल MAX77843_MUIC_IRQ_INT3_MPNACK:
	हाल MAX77843_MUIC_IRQ_INT3_MRXBUFOW:
	हाल MAX77843_MUIC_IRQ_INT3_MRXTRF:
	हाल MAX77843_MUIC_IRQ_INT3_MRXPERR:
	हाल MAX77843_MUIC_IRQ_INT3_MRXRDY:
		अवरोध;
	शेष:
		dev_err(info->dev, "Cannot recognize IRQ(%d)\n", irq_type);
		अवरोध;
	पूर्ण

	schedule_work(&info->irq_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम max77843_muic_detect_cable_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max77843_muic_info *info = container_of(to_delayed_work(work),
			काष्ठा max77843_muic_info, wq_detcable);
	काष्ठा max77693_dev *max77843 = info->max77843;
	पूर्णांक chg_type, adc, ret;
	bool attached;

	mutex_lock(&info->mutex);

	ret = regmap_bulk_पढ़ो(max77843->regmap_muic,
			MAX77843_MUIC_REG_STATUS1, info->status,
			MAX77843_MUIC_STATUS_NUM);
	अगर (ret) अणु
		dev_err(info->dev, "Cannot read STATUS registers\n");
		जाओ err_cable_wq;
	पूर्ण

	adc = max77843_muic_get_cable_type(info,
			MAX77843_CABLE_GROUP_ADC, &attached);
	अगर (attached && adc != MAX77843_MUIC_ADC_OPEN) अणु
		ret = max77843_muic_adc_handler(info);
		अगर (ret < 0) अणु
			dev_err(info->dev, "Cannot detect accessory\n");
			जाओ err_cable_wq;
		पूर्ण
	पूर्ण

	chg_type = max77843_muic_get_cable_type(info,
			MAX77843_CABLE_GROUP_CHG, &attached);
	अगर (attached && chg_type != MAX77843_MUIC_CHG_NONE) अणु
		ret = max77843_muic_chg_handler(info);
		अगर (ret < 0) अणु
			dev_err(info->dev, "Cannot detect charger accessory\n");
			जाओ err_cable_wq;
		पूर्ण
	पूर्ण

err_cable_wq:
	mutex_unlock(&info->mutex);
पूर्ण

अटल पूर्णांक max77843_muic_set_debounce_समय(काष्ठा max77843_muic_info *info,
		क्रमागत max77843_muic_adc_debounce_समय समय)
अणु
	काष्ठा max77693_dev *max77843 = info->max77843;
	पूर्णांक ret;

	चयन (समय) अणु
	हाल MAX77843_DEBOUNCE_TIME_5MS:
	हाल MAX77843_DEBOUNCE_TIME_10MS:
	हाल MAX77843_DEBOUNCE_TIME_25MS:
	हाल MAX77843_DEBOUNCE_TIME_38_62MS:
		ret = regmap_update_bits(max77843->regmap_muic,
				MAX77843_MUIC_REG_CONTROL4,
				MAX77843_MUIC_CONTROL4_ADCDBSET_MASK,
				समय << MAX77843_MUIC_CONTROL4_ADCDBSET_SHIFT);
		अगर (ret < 0) अणु
			dev_err(info->dev, "Cannot write MUIC regmap\n");
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(info->dev, "Invalid ADC debounce time\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77843_init_muic_regmap(काष्ठा max77693_dev *max77843)
अणु
	पूर्णांक ret;

	max77843->i2c_muic = i2c_new_dummy_device(max77843->i2c->adapter,
			I2C_ADDR_MUIC);
	अगर (IS_ERR(max77843->i2c_muic)) अणु
		dev_err(&max77843->i2c->dev,
				"Cannot allocate I2C device for MUIC\n");
		वापस PTR_ERR(max77843->i2c_muic);
	पूर्ण

	i2c_set_clientdata(max77843->i2c_muic, max77843);

	max77843->regmap_muic = devm_regmap_init_i2c(max77843->i2c_muic,
			&max77843_muic_regmap_config);
	अगर (IS_ERR(max77843->regmap_muic)) अणु
		ret = PTR_ERR(max77843->regmap_muic);
		जाओ err_muic_i2c;
	पूर्ण

	ret = regmap_add_irq_chip(max77843->regmap_muic, max77843->irq,
			IRQF_TRIGGER_LOW | IRQF_ONESHOT | IRQF_SHARED,
			0, &max77843_muic_irq_chip, &max77843->irq_data_muic);
	अगर (ret < 0) अणु
		dev_err(&max77843->i2c->dev, "Cannot add MUIC IRQ chip\n");
		जाओ err_muic_i2c;
	पूर्ण

	वापस 0;

err_muic_i2c:
	i2c_unरेजिस्टर_device(max77843->i2c_muic);

	वापस ret;
पूर्ण

अटल पूर्णांक max77843_muic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77693_dev *max77843 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max77843_muic_info *info;
	अचिन्हित पूर्णांक id;
	पूर्णांक cable_type;
	bool attached;
	पूर्णांक i, ret;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = &pdev->dev;
	info->max77843 = max77843;

	platक्रमm_set_drvdata(pdev, info);
	mutex_init(&info->mutex);

	/* Initialize i2c and regmap */
	ret = max77843_init_muic_regmap(max77843);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to init MUIC regmap\n");
		वापस ret;
	पूर्ण

	/* Turn off स्वतः detection configuration */
	ret = regmap_update_bits(max77843->regmap_muic,
			MAX77843_MUIC_REG_CONTROL4,
			MAX77843_MUIC_CONTROL4_USBAUTO_MASK |
			MAX77843_MUIC_CONTROL4_FCTAUTO_MASK,
			CONTROL4_AUTO_DISABLE);

	/* Initialize extcon device */
	info->edev = devm_extcon_dev_allocate(&pdev->dev,
			max77843_extcon_cable);
	अगर (IS_ERR(info->edev)) अणु
		dev_err(&pdev->dev, "Failed to allocate memory for extcon\n");
		ret = PTR_ERR(info->edev);
		जाओ err_muic_irq;
	पूर्ण

	ret = devm_extcon_dev_रेजिस्टर(&pdev->dev, info->edev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register extcon device\n");
		जाओ err_muic_irq;
	पूर्ण

	/* Set ADC debounce समय */
	max77843_muic_set_debounce_समय(info, MAX77843_DEBOUNCE_TIME_25MS);

	/* Set initial path क्रम UART when JIG is connected to get serial logs */
	ret = regmap_bulk_पढ़ो(max77843->regmap_muic,
			MAX77843_MUIC_REG_STATUS1, info->status,
			MAX77843_MUIC_STATUS_NUM);
	अगर (ret) अणु
		dev_err(info->dev, "Cannot read STATUS registers\n");
		जाओ err_muic_irq;
	पूर्ण
	cable_type = max77843_muic_get_cable_type(info, MAX77843_CABLE_GROUP_ADC,
					 &attached);
	अगर (attached && cable_type == MAX77843_MUIC_ADC_FACTORY_MODE_UART_OFF)
		max77843_muic_set_path(info, MAX77843_MUIC_CONTROL1_SW_UART,
				       true, false);

	/* Check revision number of MUIC device */
	ret = regmap_पढ़ो(max77843->regmap_muic, MAX77843_MUIC_REG_ID, &id);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to read revision number\n");
		जाओ err_muic_irq;
	पूर्ण
	dev_info(info->dev, "MUIC device ID : 0x%x\n", id);

	/* Support भव irq करोमुख्य क्रम max77843 MUIC device */
	INIT_WORK(&info->irq_work, max77843_muic_irq_work);

	/* Clear IRQ bits beक्रमe request IRQs */
	ret = regmap_bulk_पढ़ो(max77843->regmap_muic,
			MAX77843_MUIC_REG_INT1, info->status,
			MAX77843_MUIC_STATUS_NUM);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to Clear IRQ bits\n");
		जाओ err_muic_irq;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(max77843_muic_irqs); i++) अणु
		काष्ठा max77843_muic_irq *muic_irq = &max77843_muic_irqs[i];
		पूर्णांक virq = 0;

		virq = regmap_irq_get_virq(max77843->irq_data_muic,
				muic_irq->irq);
		अगर (virq <= 0) अणु
			ret = -EINVAL;
			जाओ err_muic_irq;
		पूर्ण
		muic_irq->virq = virq;

		ret = devm_request_thपढ़ोed_irq(&pdev->dev, virq, शून्य,
				max77843_muic_irq_handler, IRQF_NO_SUSPEND,
				muic_irq->name, info);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Failed to request irq (IRQ: %d, error: %d)\n",
				muic_irq->irq, ret);
			जाओ err_muic_irq;
		पूर्ण
	पूर्ण

	/* Detect accessory after completing the initialization of platक्रमm */
	INIT_DELAYED_WORK(&info->wq_detcable, max77843_muic_detect_cable_wq);
	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			&info->wq_detcable, msecs_to_jअगरfies(DELAY_MS_DEFAULT));

	वापस 0;

err_muic_irq:
	regmap_del_irq_chip(max77843->irq, max77843->irq_data_muic);
	i2c_unरेजिस्टर_device(max77843->i2c_muic);

	वापस ret;
पूर्ण

अटल पूर्णांक max77843_muic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77843_muic_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा max77693_dev *max77843 = info->max77843;

	cancel_work_sync(&info->irq_work);
	regmap_del_irq_chip(max77843->irq, max77843->irq_data_muic);
	i2c_unरेजिस्टर_device(max77843->i2c_muic);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max77843_muic_id[] = अणु
	अणु "max77843-muic", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max77843_muic_id);

अटल काष्ठा platक्रमm_driver max77843_muic_driver = अणु
	.driver		= अणु
		.name		= "max77843-muic",
	पूर्ण,
	.probe		= max77843_muic_probe,
	.हटाओ		= max77843_muic_हटाओ,
	.id_table	= max77843_muic_id,
पूर्ण;

अटल पूर्णांक __init max77843_muic_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&max77843_muic_driver);
पूर्ण
subsys_initcall(max77843_muic_init);

MODULE_DESCRIPTION("Maxim MAX77843 Extcon driver");
MODULE_AUTHOR("Jaewon Kim <jaewon02.kim@samsung.com>");
MODULE_LICENSE("GPL");
