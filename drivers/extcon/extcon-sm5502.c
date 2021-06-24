<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * extcon-sm5502.c - Silicon Mitus SM5502 extcon drvier to support USB चयनes
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd
 * Author: Chanwoo Choi <cw00.choi@samsung.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/extcon-provider.h>

#समावेश "extcon-sm5502.h"

#घोषणा	DELAY_MS_DEFAULT		17000	/* unit: millisecond */

काष्ठा muic_irq अणु
	अचिन्हित पूर्णांक irq;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक virq;
पूर्ण;

काष्ठा reg_data अणु
	u8 reg;
	अचिन्हित पूर्णांक val;
	bool invert;
पूर्ण;

काष्ठा sm5502_muic_info अणु
	काष्ठा device *dev;
	काष्ठा extcon_dev *edev;

	काष्ठा i2c_client *i2c;
	काष्ठा regmap *regmap;

	काष्ठा regmap_irq_chip_data *irq_data;
	काष्ठा muic_irq *muic_irqs;
	अचिन्हित पूर्णांक num_muic_irqs;
	पूर्णांक irq;
	bool irq_attach;
	bool irq_detach;
	काष्ठा work_काष्ठा irq_work;

	काष्ठा reg_data *reg_data;
	अचिन्हित पूर्णांक num_reg_data;

	काष्ठा mutex mutex;

	/*
	 * Use delayed workqueue to detect cable state and then
	 * notअगरy cable state to notअगरiee/platक्रमm through uevent.
	 * After completing the booting of platक्रमm, the extcon provider
	 * driver should notअगरy cable state to upper layer.
	 */
	काष्ठा delayed_work wq_detcable;
पूर्ण;

/* Default value of SM5502 रेजिस्टर to bring up MUIC device. */
अटल काष्ठा reg_data sm5502_reg_data[] = अणु
	अणु
		.reg = SM5502_REG_RESET,
		.val = SM5502_REG_RESET_MASK,
		.invert = true,
	पूर्ण, अणु
		.reg = SM5502_REG_CONTROL,
		.val = SM5502_REG_CONTROL_MASK_INT_MASK,
		.invert = false,
	पूर्ण, अणु
		.reg = SM5502_REG_INTMASK1,
		.val = SM5502_REG_INTM1_KP_MASK
			| SM5502_REG_INTM1_LKP_MASK
			| SM5502_REG_INTM1_LKR_MASK,
		.invert = true,
	पूर्ण, अणु
		.reg = SM5502_REG_INTMASK2,
		.val = SM5502_REG_INTM2_VBUS_DET_MASK
			| SM5502_REG_INTM2_REV_ACCE_MASK
			| SM5502_REG_INTM2_ADC_CHG_MASK
			| SM5502_REG_INTM2_STUCK_KEY_MASK
			| SM5502_REG_INTM2_STUCK_KEY_RCV_MASK
			| SM5502_REG_INTM2_MHL_MASK,
		.invert = true,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/* List of detectable cables */
अटल स्थिर अचिन्हित पूर्णांक sm5502_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_NONE,
पूर्ण;

/* Define supported accessory type */
क्रमागत sm5502_muic_acc_type अणु
	SM5502_MUIC_ADC_GROUND = 0x0,
	SM5502_MUIC_ADC_SEND_END_BUTTON,
	SM5502_MUIC_ADC_REMOTE_S1_BUTTON,
	SM5502_MUIC_ADC_REMOTE_S2_BUTTON,
	SM5502_MUIC_ADC_REMOTE_S3_BUTTON,
	SM5502_MUIC_ADC_REMOTE_S4_BUTTON,
	SM5502_MUIC_ADC_REMOTE_S5_BUTTON,
	SM5502_MUIC_ADC_REMOTE_S6_BUTTON,
	SM5502_MUIC_ADC_REMOTE_S7_BUTTON,
	SM5502_MUIC_ADC_REMOTE_S8_BUTTON,
	SM5502_MUIC_ADC_REMOTE_S9_BUTTON,
	SM5502_MUIC_ADC_REMOTE_S10_BUTTON,
	SM5502_MUIC_ADC_REMOTE_S11_BUTTON,
	SM5502_MUIC_ADC_REMOTE_S12_BUTTON,
	SM5502_MUIC_ADC_RESERVED_ACC_1,
	SM5502_MUIC_ADC_RESERVED_ACC_2,
	SM5502_MUIC_ADC_RESERVED_ACC_3,
	SM5502_MUIC_ADC_RESERVED_ACC_4,
	SM5502_MUIC_ADC_RESERVED_ACC_5,
	SM5502_MUIC_ADC_AUDIO_TYPE2,
	SM5502_MUIC_ADC_PHONE_POWERED_DEV,
	SM5502_MUIC_ADC_TTY_CONVERTER,
	SM5502_MUIC_ADC_UART_CABLE,
	SM5502_MUIC_ADC_TYPE1_CHARGER,
	SM5502_MUIC_ADC_FACTORY_MODE_BOOT_OFF_USB,
	SM5502_MUIC_ADC_FACTORY_MODE_BOOT_ON_USB,
	SM5502_MUIC_ADC_AUDIO_VIDEO_CABLE,
	SM5502_MUIC_ADC_TYPE2_CHARGER,
	SM5502_MUIC_ADC_FACTORY_MODE_BOOT_OFF_UART,
	SM5502_MUIC_ADC_FACTORY_MODE_BOOT_ON_UART,
	SM5502_MUIC_ADC_AUDIO_TYPE1,
	SM5502_MUIC_ADC_OPEN = 0x1f,

	/*
	 * The below accessories have same ADC value (0x1f or 0x1e).
	 * So, Device type1 is used to separate specअगरic accessory.
	 */
							/* |---------|--ADC| */
							/* |    [7:5]|[4:0]| */
	SM5502_MUIC_ADC_AUDIO_TYPE1_FULL_REMOTE = 0x3e,	/* |      001|11110| */
	SM5502_MUIC_ADC_AUDIO_TYPE1_SEND_END = 0x5e,	/* |      010|11110| */
							/* |Dev Type1|--ADC| */
	SM5502_MUIC_ADC_GROUND_USB_OTG = 0x80,		/* |      100|00000| */
	SM5502_MUIC_ADC_OPEN_USB = 0x5f,		/* |      010|11111| */
	SM5502_MUIC_ADC_OPEN_TA = 0xdf,			/* |      110|11111| */
	SM5502_MUIC_ADC_OPEN_USB_OTG = 0xff,		/* |      111|11111| */
पूर्ण;

/* List of supported पूर्णांकerrupt क्रम SM5502 */
अटल काष्ठा muic_irq sm5502_muic_irqs[] = अणु
	अणु SM5502_IRQ_INT1_ATTACH,	"muic-attach" पूर्ण,
	अणु SM5502_IRQ_INT1_DETACH,	"muic-detach" पूर्ण,
	अणु SM5502_IRQ_INT1_KP,		"muic-kp" पूर्ण,
	अणु SM5502_IRQ_INT1_LKP,		"muic-lkp" पूर्ण,
	अणु SM5502_IRQ_INT1_LKR,		"muic-lkr" पूर्ण,
	अणु SM5502_IRQ_INT1_OVP_EVENT,	"muic-ovp-event" पूर्ण,
	अणु SM5502_IRQ_INT1_OCP_EVENT,	"muic-ocp-event" पूर्ण,
	अणु SM5502_IRQ_INT1_OVP_OCP_DIS,	"muic-ovp-ocp-dis" पूर्ण,
	अणु SM5502_IRQ_INT2_VBUS_DET,	"muic-vbus-det" पूर्ण,
	अणु SM5502_IRQ_INT2_REV_ACCE,	"muic-rev-acce" पूर्ण,
	अणु SM5502_IRQ_INT2_ADC_CHG,	"muic-adc-chg" पूर्ण,
	अणु SM5502_IRQ_INT2_STUCK_KEY,	"muic-stuck-key" पूर्ण,
	अणु SM5502_IRQ_INT2_STUCK_KEY_RCV, "muic-stuck-key-rcv" पूर्ण,
	अणु SM5502_IRQ_INT2_MHL,		"muic-mhl" पूर्ण,
पूर्ण;

/* Define पूर्णांकerrupt list of SM5502 to रेजिस्टर regmap_irq */
अटल स्थिर काष्ठा regmap_irq sm5502_irqs[] = अणु
	/* INT1 पूर्णांकerrupts */
	अणु .reg_offset = 0, .mask = SM5502_IRQ_INT1_ATTACH_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = SM5502_IRQ_INT1_DETACH_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = SM5502_IRQ_INT1_KP_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = SM5502_IRQ_INT1_LKP_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = SM5502_IRQ_INT1_LKR_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = SM5502_IRQ_INT1_OVP_EVENT_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = SM5502_IRQ_INT1_OCP_EVENT_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = SM5502_IRQ_INT1_OVP_OCP_DIS_MASK, पूर्ण,

	/* INT2 पूर्णांकerrupts */
	अणु .reg_offset = 1, .mask = SM5502_IRQ_INT2_VBUS_DET_MASK,पूर्ण,
	अणु .reg_offset = 1, .mask = SM5502_IRQ_INT2_REV_ACCE_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = SM5502_IRQ_INT2_ADC_CHG_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = SM5502_IRQ_INT2_STUCK_KEY_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = SM5502_IRQ_INT2_STUCK_KEY_RCV_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = SM5502_IRQ_INT2_MHL_MASK, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip sm5502_muic_irq_chip = अणु
	.name			= "sm5502",
	.status_base		= SM5502_REG_INT1,
	.mask_base		= SM5502_REG_INTMASK1,
	.mask_invert		= false,
	.num_regs		= 2,
	.irqs			= sm5502_irqs,
	.num_irqs		= ARRAY_SIZE(sm5502_irqs),
पूर्ण;

/* Define regmap configuration of SM5502 क्रम I2C communication  */
अटल bool sm5502_muic_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SM5502_REG_INTMASK1:
	हाल SM5502_REG_INTMASK2:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config sm5502_muic_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.अस्थिर_reg	= sm5502_muic_अस्थिर_reg,
	.max_रेजिस्टर	= SM5502_REG_END,
पूर्ण;

/* Change DM_CON/DP_CON/VBUSIN चयन according to cable type */
अटल पूर्णांक sm5502_muic_set_path(काष्ठा sm5502_muic_info *info,
				अचिन्हित पूर्णांक con_sw, अचिन्हित पूर्णांक vbus_sw,
				bool attached)
अणु
	पूर्णांक ret;

	अगर (!attached) अणु
		con_sw	= DM_DP_SWITCH_OPEN;
		vbus_sw	= VBUSIN_SWITCH_OPEN;
	पूर्ण

	चयन (con_sw) अणु
	हाल DM_DP_SWITCH_OPEN:
	हाल DM_DP_SWITCH_USB:
	हाल DM_DP_SWITCH_AUDIO:
	हाल DM_DP_SWITCH_UART:
		ret = regmap_update_bits(info->regmap, SM5502_REG_MANUAL_SW1,
					 SM5502_REG_MANUAL_SW1_DP_MASK |
					 SM5502_REG_MANUAL_SW1_DM_MASK,
					 con_sw);
		अगर (ret < 0) अणु
			dev_err(info->dev,
				"cannot update DM_CON/DP_CON switch\n");
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(info->dev, "Unknown DM_CON/DP_CON switch type (%d)\n",
				con_sw);
		वापस -EINVAL;
	पूर्ण

	चयन (vbus_sw) अणु
	हाल VBUSIN_SWITCH_OPEN:
	हाल VBUSIN_SWITCH_VBUSOUT:
	हाल VBUSIN_SWITCH_MIC:
	हाल VBUSIN_SWITCH_VBUSOUT_WITH_USB:
		ret = regmap_update_bits(info->regmap, SM5502_REG_MANUAL_SW1,
					 SM5502_REG_MANUAL_SW1_VBUSIN_MASK,
					 vbus_sw);
		अगर (ret < 0) अणु
			dev_err(info->dev,
				"cannot update VBUSIN switch\n");
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(info->dev, "Unknown VBUS switch type (%d)\n", vbus_sw);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Return cable type of attached or detached accessories */
अटल अचिन्हित पूर्णांक sm5502_muic_get_cable_type(काष्ठा sm5502_muic_info *info)
अणु
	अचिन्हित पूर्णांक cable_type, adc, dev_type1;
	पूर्णांक ret;

	/* Read ADC value according to बाह्यal cable or button */
	ret = regmap_पढ़ो(info->regmap, SM5502_REG_ADC, &adc);
	अगर (ret) अणु
		dev_err(info->dev, "failed to read ADC register\n");
		वापस ret;
	पूर्ण

	/*
	 * If ADC is SM5502_MUIC_ADC_GROUND(0x0), बाह्यal cable hasn't
	 * connected with to MUIC device.
	 */
	cable_type = adc & SM5502_REG_ADC_MASK;

	चयन (cable_type) अणु
	हाल SM5502_MUIC_ADC_GROUND:
		ret = regmap_पढ़ो(info->regmap, SM5502_REG_DEV_TYPE1,
				  &dev_type1);
		अगर (ret) अणु
			dev_err(info->dev, "failed to read DEV_TYPE1 reg\n");
			वापस ret;
		पूर्ण

		चयन (dev_type1) अणु
		हाल SM5502_REG_DEV_TYPE1_USB_OTG_MASK:
			cable_type = SM5502_MUIC_ADC_GROUND_USB_OTG;
			अवरोध;
		शेष:
			dev_dbg(info->dev,
				"cannot identify the cable type: adc(0x%x), dev_type1(0x%x)\n",
				adc, dev_type1);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SM5502_MUIC_ADC_SEND_END_BUTTON:
	हाल SM5502_MUIC_ADC_REMOTE_S1_BUTTON:
	हाल SM5502_MUIC_ADC_REMOTE_S2_BUTTON:
	हाल SM5502_MUIC_ADC_REMOTE_S3_BUTTON:
	हाल SM5502_MUIC_ADC_REMOTE_S4_BUTTON:
	हाल SM5502_MUIC_ADC_REMOTE_S5_BUTTON:
	हाल SM5502_MUIC_ADC_REMOTE_S6_BUTTON:
	हाल SM5502_MUIC_ADC_REMOTE_S7_BUTTON:
	हाल SM5502_MUIC_ADC_REMOTE_S8_BUTTON:
	हाल SM5502_MUIC_ADC_REMOTE_S9_BUTTON:
	हाल SM5502_MUIC_ADC_REMOTE_S10_BUTTON:
	हाल SM5502_MUIC_ADC_REMOTE_S11_BUTTON:
	हाल SM5502_MUIC_ADC_REMOTE_S12_BUTTON:
	हाल SM5502_MUIC_ADC_RESERVED_ACC_1:
	हाल SM5502_MUIC_ADC_RESERVED_ACC_2:
	हाल SM5502_MUIC_ADC_RESERVED_ACC_3:
	हाल SM5502_MUIC_ADC_RESERVED_ACC_4:
	हाल SM5502_MUIC_ADC_RESERVED_ACC_5:
	हाल SM5502_MUIC_ADC_AUDIO_TYPE2:
	हाल SM5502_MUIC_ADC_PHONE_POWERED_DEV:
	हाल SM5502_MUIC_ADC_TTY_CONVERTER:
	हाल SM5502_MUIC_ADC_UART_CABLE:
	हाल SM5502_MUIC_ADC_TYPE1_CHARGER:
	हाल SM5502_MUIC_ADC_FACTORY_MODE_BOOT_OFF_USB:
	हाल SM5502_MUIC_ADC_FACTORY_MODE_BOOT_ON_USB:
	हाल SM5502_MUIC_ADC_AUDIO_VIDEO_CABLE:
	हाल SM5502_MUIC_ADC_TYPE2_CHARGER:
	हाल SM5502_MUIC_ADC_FACTORY_MODE_BOOT_OFF_UART:
	हाल SM5502_MUIC_ADC_FACTORY_MODE_BOOT_ON_UART:
		अवरोध;
	हाल SM5502_MUIC_ADC_AUDIO_TYPE1:
		/*
		 * Check whether cable type is
		 * SM5502_MUIC_ADC_AUDIO_TYPE1_FULL_REMOTE
		 * or SM5502_MUIC_ADC_AUDIO_TYPE1_SEND_END
		 * by using Button event.
		 */
		अवरोध;
	हाल SM5502_MUIC_ADC_OPEN:
		ret = regmap_पढ़ो(info->regmap, SM5502_REG_DEV_TYPE1,
				  &dev_type1);
		अगर (ret) अणु
			dev_err(info->dev, "failed to read DEV_TYPE1 reg\n");
			वापस ret;
		पूर्ण

		चयन (dev_type1) अणु
		हाल SM5502_REG_DEV_TYPE1_USB_SDP_MASK:
			cable_type = SM5502_MUIC_ADC_OPEN_USB;
			अवरोध;
		हाल SM5502_REG_DEV_TYPE1_DEDICATED_CHG_MASK:
			cable_type = SM5502_MUIC_ADC_OPEN_TA;
			अवरोध;
		हाल SM5502_REG_DEV_TYPE1_USB_OTG_MASK:
			cable_type = SM5502_MUIC_ADC_OPEN_USB_OTG;
			अवरोध;
		शेष:
			dev_dbg(info->dev,
				"cannot identify the cable type: adc(0x%x)\n",
				adc);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(info->dev,
			"failed to identify the cable type: adc(0x%x)\n", adc);
		वापस -EINVAL;
	पूर्ण

	वापस cable_type;
पूर्ण

अटल पूर्णांक sm5502_muic_cable_handler(काष्ठा sm5502_muic_info *info,
				     bool attached)
अणु
	अटल अचिन्हित पूर्णांक prev_cable_type = SM5502_MUIC_ADC_GROUND;
	अचिन्हित पूर्णांक cable_type = SM5502_MUIC_ADC_GROUND;
	अचिन्हित पूर्णांक con_sw = DM_DP_SWITCH_OPEN;
	अचिन्हित पूर्णांक vbus_sw = VBUSIN_SWITCH_OPEN;
	अचिन्हित पूर्णांक id;
	पूर्णांक ret;

	/* Get the type of attached or detached cable */
	अगर (attached)
		cable_type = sm5502_muic_get_cable_type(info);
	अन्यथा
		cable_type = prev_cable_type;
	prev_cable_type = cable_type;

	चयन (cable_type) अणु
	हाल SM5502_MUIC_ADC_OPEN_USB:
		id	= EXTCON_USB;
		con_sw	= DM_DP_SWITCH_USB;
		vbus_sw	= VBUSIN_SWITCH_VBUSOUT_WITH_USB;
		अवरोध;
	हाल SM5502_MUIC_ADC_OPEN_TA:
		id	= EXTCON_CHG_USB_DCP;
		con_sw	= DM_DP_SWITCH_OPEN;
		vbus_sw	= VBUSIN_SWITCH_VBUSOUT;
		अवरोध;
	हाल SM5502_MUIC_ADC_GROUND_USB_OTG:
	हाल SM5502_MUIC_ADC_OPEN_USB_OTG:
		id	= EXTCON_USB_HOST;
		con_sw	= DM_DP_SWITCH_USB;
		vbus_sw	= VBUSIN_SWITCH_OPEN;
		अवरोध;
	शेष:
		dev_dbg(info->dev,
			"cannot handle this cable_type (0x%x)\n", cable_type);
		वापस 0;
	पूर्ण

	/* Change पूर्णांकernal hardware path(DM_CON/DP_CON, VBUSIN) */
	ret = sm5502_muic_set_path(info, con_sw, vbus_sw, attached);
	अगर (ret < 0)
		वापस ret;

	/* Change the state of बाह्यal accessory */
	extcon_set_state_sync(info->edev, id, attached);
	अगर (id == EXTCON_USB)
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
					attached);

	वापस 0;
पूर्ण

अटल व्योम sm5502_muic_irq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sm5502_muic_info *info = container_of(work,
			काष्ठा sm5502_muic_info, irq_work);
	पूर्णांक ret = 0;

	अगर (!info->edev)
		वापस;

	mutex_lock(&info->mutex);

	/* Detect attached or detached cables */
	अगर (info->irq_attach) अणु
		ret = sm5502_muic_cable_handler(info, true);
		info->irq_attach = false;
	पूर्ण
	अगर (info->irq_detach) अणु
		ret = sm5502_muic_cable_handler(info, false);
		info->irq_detach = false;
	पूर्ण

	अगर (ret < 0)
		dev_err(info->dev, "failed to handle MUIC interrupt\n");

	mutex_unlock(&info->mutex);
पूर्ण

/*
 * Sets irq_attach or irq_detach in sm5502_muic_info and वापसs 0.
 * Returns -ESRCH अगर irq_type करोes not match रेजिस्टरed IRQ क्रम this dev type.
 */
अटल पूर्णांक sm5502_parse_irq(काष्ठा sm5502_muic_info *info, पूर्णांक irq_type)
अणु
	चयन (irq_type) अणु
	हाल SM5502_IRQ_INT1_ATTACH:
		info->irq_attach = true;
		अवरोध;
	हाल SM5502_IRQ_INT1_DETACH:
		info->irq_detach = true;
		अवरोध;
	हाल SM5502_IRQ_INT1_KP:
	हाल SM5502_IRQ_INT1_LKP:
	हाल SM5502_IRQ_INT1_LKR:
	हाल SM5502_IRQ_INT1_OVP_EVENT:
	हाल SM5502_IRQ_INT1_OCP_EVENT:
	हाल SM5502_IRQ_INT1_OVP_OCP_DIS:
	हाल SM5502_IRQ_INT2_VBUS_DET:
	हाल SM5502_IRQ_INT2_REV_ACCE:
	हाल SM5502_IRQ_INT2_ADC_CHG:
	हाल SM5502_IRQ_INT2_STUCK_KEY:
	हाल SM5502_IRQ_INT2_STUCK_KEY_RCV:
	हाल SM5502_IRQ_INT2_MHL:
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t sm5502_muic_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sm5502_muic_info *info = data;
	पूर्णांक i, irq_type = -1, ret;

	क्रम (i = 0; i < info->num_muic_irqs; i++)
		अगर (irq == info->muic_irqs[i].virq)
			irq_type = info->muic_irqs[i].irq;

	ret = sm5502_parse_irq(info, irq_type);
	अगर (ret < 0) अणु
		dev_warn(info->dev, "cannot handle is interrupt:%d\n",
				    irq_type);
		वापस IRQ_HANDLED;
	पूर्ण
	schedule_work(&info->irq_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sm5502_muic_detect_cable_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sm5502_muic_info *info = container_of(to_delayed_work(work),
				काष्ठा sm5502_muic_info, wq_detcable);
	पूर्णांक ret;

	/* Notअगरy the state of connector cable or not  */
	ret = sm5502_muic_cable_handler(info, true);
	अगर (ret < 0)
		dev_warn(info->dev, "failed to detect cable state\n");
पूर्ण

अटल व्योम sm5502_init_dev_type(काष्ठा sm5502_muic_info *info)
अणु
	अचिन्हित पूर्णांक reg_data, venकरोr_id, version_id;
	पूर्णांक i, ret;

	/* To test I2C, Prपूर्णांक version_id and venकरोr_id of SM5502 */
	ret = regmap_पढ़ो(info->regmap, SM5502_REG_DEVICE_ID, &reg_data);
	अगर (ret) अणु
		dev_err(info->dev,
			"failed to read DEVICE_ID register: %d\n", ret);
		वापस;
	पूर्ण

	venकरोr_id = ((reg_data & SM5502_REG_DEVICE_ID_VENDOR_MASK) >>
				SM5502_REG_DEVICE_ID_VENDOR_SHIFT);
	version_id = ((reg_data & SM5502_REG_DEVICE_ID_VERSION_MASK) >>
				SM5502_REG_DEVICE_ID_VERSION_SHIFT);

	dev_info(info->dev, "Device type: version: 0x%x, vendor: 0x%x\n",
			    version_id, venकरोr_id);

	/* Initiazle the रेजिस्टर of SM5502 device to bring-up */
	क्रम (i = 0; i < info->num_reg_data; i++) अणु
		अचिन्हित पूर्णांक val = 0;

		अगर (!info->reg_data[i].invert)
			val |= ~info->reg_data[i].val;
		अन्यथा
			val = info->reg_data[i].val;
		regmap_ग_लिखो(info->regmap, info->reg_data[i].reg, val);
	पूर्ण
पूर्ण

अटल पूर्णांक sm5022_muic_i2c_probe(काष्ठा i2c_client *i2c,
				 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device_node *np = i2c->dev.of_node;
	काष्ठा sm5502_muic_info *info;
	पूर्णांक i, ret, irq_flags;

	अगर (!np)
		वापस -EINVAL;

	info = devm_kzalloc(&i2c->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	i2c_set_clientdata(i2c, info);

	info->dev = &i2c->dev;
	info->i2c = i2c;
	info->irq = i2c->irq;
	info->muic_irqs = sm5502_muic_irqs;
	info->num_muic_irqs = ARRAY_SIZE(sm5502_muic_irqs);
	info->reg_data = sm5502_reg_data;
	info->num_reg_data = ARRAY_SIZE(sm5502_reg_data);

	mutex_init(&info->mutex);

	INIT_WORK(&info->irq_work, sm5502_muic_irq_work);

	info->regmap = devm_regmap_init_i2c(i2c, &sm5502_muic_regmap_config);
	अगर (IS_ERR(info->regmap)) अणु
		ret = PTR_ERR(info->regmap);
		dev_err(info->dev, "failed to allocate register map: %d\n",
				   ret);
		वापस ret;
	पूर्ण

	/* Support irq करोमुख्य क्रम SM5502 MUIC device */
	irq_flags = IRQF_TRIGGER_FALLING | IRQF_ONESHOT | IRQF_SHARED;
	ret = regmap_add_irq_chip(info->regmap, info->irq, irq_flags, 0,
				  &sm5502_muic_irq_chip, &info->irq_data);
	अगर (ret != 0) अणु
		dev_err(info->dev, "failed to request IRQ %d: %d\n",
				    info->irq, ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < info->num_muic_irqs; i++) अणु
		काष्ठा muic_irq *muic_irq = &info->muic_irqs[i];
		पूर्णांक virq = 0;

		virq = regmap_irq_get_virq(info->irq_data, muic_irq->irq);
		अगर (virq <= 0)
			वापस -EINVAL;
		muic_irq->virq = virq;

		ret = devm_request_thपढ़ोed_irq(info->dev, virq, शून्य,
						sm5502_muic_irq_handler,
						IRQF_NO_SUSPEND | IRQF_ONESHOT,
						muic_irq->name, info);
		अगर (ret) अणु
			dev_err(info->dev,
				"failed: irq request (IRQ: %d, error :%d)\n",
				muic_irq->irq, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Allocate extcon device */
	info->edev = devm_extcon_dev_allocate(info->dev, sm5502_extcon_cable);
	अगर (IS_ERR(info->edev)) अणु
		dev_err(info->dev, "failed to allocate memory for extcon\n");
		वापस -ENOMEM;
	पूर्ण

	/* Register extcon device */
	ret = devm_extcon_dev_रेजिस्टर(info->dev, info->edev);
	अगर (ret) अणु
		dev_err(info->dev, "failed to register extcon device\n");
		वापस ret;
	पूर्ण

	/*
	 * Detect accessory after completing the initialization of platक्रमm
	 *
	 * - Use delayed workqueue to detect cable state and then
	 * notअगरy cable state to notअगरiee/platक्रमm through uevent.
	 * After completing the booting of platक्रमm, the extcon provider
	 * driver should notअगरy cable state to upper layer.
	 */
	INIT_DELAYED_WORK(&info->wq_detcable, sm5502_muic_detect_cable_wq);
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &info->wq_detcable,
			msecs_to_jअगरfies(DELAY_MS_DEFAULT));

	/* Initialize SM5502 device and prपूर्णांक venकरोr id and version id */
	sm5502_init_dev_type(info);

	वापस 0;
पूर्ण

अटल पूर्णांक sm5502_muic_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा sm5502_muic_info *info = i2c_get_clientdata(i2c);

	regmap_del_irq_chip(info->irq, info->irq_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sm5502_dt_match[] = अणु
	अणु .compatible = "siliconmitus,sm5502-muic" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sm5502_dt_match);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sm5502_muic_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा sm5502_muic_info *info = i2c_get_clientdata(i2c);

	enable_irq_wake(info->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक sm5502_muic_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा sm5502_muic_info *info = i2c_get_clientdata(i2c);

	disable_irq_wake(info->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sm5502_muic_pm_ops,
			 sm5502_muic_suspend, sm5502_muic_resume);

अटल स्थिर काष्ठा i2c_device_id sm5502_i2c_id[] = अणु
	अणु "sm5502", TYPE_SM5502 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sm5502_i2c_id);

अटल काष्ठा i2c_driver sm5502_muic_i2c_driver = अणु
	.driver		= अणु
		.name	= "sm5502",
		.pm	= &sm5502_muic_pm_ops,
		.of_match_table = sm5502_dt_match,
	पूर्ण,
	.probe	= sm5022_muic_i2c_probe,
	.हटाओ	= sm5502_muic_i2c_हटाओ,
	.id_table = sm5502_i2c_id,
पूर्ण;

अटल पूर्णांक __init sm5502_muic_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&sm5502_muic_i2c_driver);
पूर्ण
subsys_initcall(sm5502_muic_i2c_init);

MODULE_DESCRIPTION("Silicon Mitus SM5502 Extcon driver");
MODULE_AUTHOR("Chanwoo Choi <cw00.choi@samsung.com>");
MODULE_LICENSE("GPL");
