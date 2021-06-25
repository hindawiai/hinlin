<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * extcon-rt8973a.c - Richtek RT8973A extcon driver to support USB चयनes
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd
 * Author: Chanwoo Choi <cw00.choi@samsung.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/extcon-provider.h>

#समावेश "extcon-rt8973a.h"

#घोषणा	DELAY_MS_DEFAULT		20000	/* unit: millisecond */

काष्ठा muic_irq अणु
	अचिन्हित पूर्णांक irq;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक virq;
पूर्ण;

काष्ठा reg_data अणु
	u8 reg;
	u8 mask;
	u8 val;
	bool invert;
पूर्ण;

काष्ठा rt8973a_muic_info अणु
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
	bool irq_ovp;
	bool irq_otp;
	काष्ठा work_काष्ठा irq_work;

	काष्ठा reg_data *reg_data;
	अचिन्हित पूर्णांक num_reg_data;
	bool स्वतः_config;

	काष्ठा mutex mutex;

	/*
	 * Use delayed workqueue to detect cable state and then
	 * notअगरy cable state to notअगरiee/platक्रमm through uevent.
	 * After completing the booting of platक्रमm, the extcon provider
	 * driver should notअगरy cable state to upper layer.
	 */
	काष्ठा delayed_work wq_detcable;
पूर्ण;

/* Default value of RT8973A रेजिस्टर to bring up MUIC device. */
अटल काष्ठा reg_data rt8973a_reg_data[] = अणु
	अणु
		.reg = RT8973A_REG_CONTROL1,
		.mask = RT8973A_REG_CONTROL1_ADC_EN_MASK
			| RT8973A_REG_CONTROL1_USB_CHD_EN_MASK
			| RT8973A_REG_CONTROL1_CHGTYP_MASK
			| RT8973A_REG_CONTROL1_SWITCH_OPEN_MASK
			| RT8973A_REG_CONTROL1_AUTO_CONFIG_MASK
			| RT8973A_REG_CONTROL1_INTM_MASK,
		.val = RT8973A_REG_CONTROL1_ADC_EN_MASK
			| RT8973A_REG_CONTROL1_USB_CHD_EN_MASK
			| RT8973A_REG_CONTROL1_CHGTYP_MASK,
		.invert = false,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

/* List of detectable cables */
अटल स्थिर अचिन्हित पूर्णांक rt8973a_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_JIG,
	EXTCON_NONE,
पूर्ण;

/* Define OVP (Over Voltage Protection), OTP (Over Temperature Protection) */
क्रमागत rt8973a_event_type अणु
	RT8973A_EVENT_ATTACH = 1,
	RT8973A_EVENT_DETACH,
	RT8973A_EVENT_OVP,
	RT8973A_EVENT_OTP,
पूर्ण;

/* Define supported accessory type */
क्रमागत rt8973a_muic_acc_type अणु
	RT8973A_MUIC_ADC_OTG = 0x0,
	RT8973A_MUIC_ADC_AUDIO_SEND_END_BUTTON,
	RT8973A_MUIC_ADC_AUDIO_REMOTE_S1_BUTTON,
	RT8973A_MUIC_ADC_AUDIO_REMOTE_S2_BUTTON,
	RT8973A_MUIC_ADC_AUDIO_REMOTE_S3_BUTTON,
	RT8973A_MUIC_ADC_AUDIO_REMOTE_S4_BUTTON,
	RT8973A_MUIC_ADC_AUDIO_REMOTE_S5_BUTTON,
	RT8973A_MUIC_ADC_AUDIO_REMOTE_S6_BUTTON,
	RT8973A_MUIC_ADC_AUDIO_REMOTE_S7_BUTTON,
	RT8973A_MUIC_ADC_AUDIO_REMOTE_S8_BUTTON,
	RT8973A_MUIC_ADC_AUDIO_REMOTE_S9_BUTTON,
	RT8973A_MUIC_ADC_AUDIO_REMOTE_S10_BUTTON,
	RT8973A_MUIC_ADC_AUDIO_REMOTE_S11_BUTTON,
	RT8973A_MUIC_ADC_AUDIO_REMOTE_S12_BUTTON,
	RT8973A_MUIC_ADC_RESERVED_ACC_1,
	RT8973A_MUIC_ADC_RESERVED_ACC_2,
	RT8973A_MUIC_ADC_RESERVED_ACC_3,
	RT8973A_MUIC_ADC_RESERVED_ACC_4,
	RT8973A_MUIC_ADC_RESERVED_ACC_5,
	RT8973A_MUIC_ADC_AUDIO_TYPE2,
	RT8973A_MUIC_ADC_PHONE_POWERED_DEV,
	RT8973A_MUIC_ADC_UNKNOWN_ACC_1,
	RT8973A_MUIC_ADC_UNKNOWN_ACC_2,
	RT8973A_MUIC_ADC_TA,
	RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_OFF_USB,
	RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_ON_USB,
	RT8973A_MUIC_ADC_UNKNOWN_ACC_3,
	RT8973A_MUIC_ADC_UNKNOWN_ACC_4,
	RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_OFF_UART,
	RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_ON_UART,
	RT8973A_MUIC_ADC_UNKNOWN_ACC_5,
	RT8973A_MUIC_ADC_OPEN = 0x1f,

	/*
	 * The below accessories has same ADC value (0x1f).
	 * So, Device type1 is used to separate specअगरic accessory.
	 */
					/* |---------|--ADC| */
					/* |    [7:5]|[4:0]| */
	RT8973A_MUIC_ADC_USB = 0x3f,	/* |      001|11111| */
पूर्ण;

/* List of supported पूर्णांकerrupt क्रम RT8973A */
अटल काष्ठा muic_irq rt8973a_muic_irqs[] = अणु
	अणु RT8973A_INT1_ATTACH,		"muic-attach" पूर्ण,
	अणु RT8973A_INT1_DETACH,		"muic-detach" पूर्ण,
	अणु RT8973A_INT1_CHGDET,		"muic-chgdet" पूर्ण,
	अणु RT8973A_INT1_DCD_T,		"muic-dcd-t" पूर्ण,
	अणु RT8973A_INT1_OVP,		"muic-ovp" पूर्ण,
	अणु RT8973A_INT1_CONNECT,		"muic-connect" पूर्ण,
	अणु RT8973A_INT1_ADC_CHG,		"muic-adc-chg" पूर्ण,
	अणु RT8973A_INT1_OTP,		"muic-otp" पूर्ण,
	अणु RT8973A_INT2_UVLO,		"muic-uvlo" पूर्ण,
	अणु RT8973A_INT2_POR,		"muic-por" पूर्ण,
	अणु RT8973A_INT2_OTP_FET,		"muic-otp-fet" पूर्ण,
	अणु RT8973A_INT2_OVP_FET,		"muic-ovp-fet" पूर्ण,
	अणु RT8973A_INT2_OCP_LATCH,	"muic-ocp-latch" पूर्ण,
	अणु RT8973A_INT2_OCP,		"muic-ocp" पूर्ण,
	अणु RT8973A_INT2_OVP_OCP,		"muic-ovp-ocp" पूर्ण,
पूर्ण;

/* Define पूर्णांकerrupt list of RT8973A to रेजिस्टर regmap_irq */
अटल स्थिर काष्ठा regmap_irq rt8973a_irqs[] = अणु
	/* INT1 पूर्णांकerrupts */
	अणु .reg_offset = 0, .mask = RT8973A_INT1_ATTACH_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = RT8973A_INT1_DETACH_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = RT8973A_INT1_CHGDET_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = RT8973A_INT1_DCD_T_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = RT8973A_INT1_OVP_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = RT8973A_INT1_CONNECT_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = RT8973A_INT1_ADC_CHG_MASK, पूर्ण,
	अणु .reg_offset = 0, .mask = RT8973A_INT1_OTP_MASK, पूर्ण,

	/* INT2 पूर्णांकerrupts */
	अणु .reg_offset = 1, .mask = RT8973A_INT2_UVLOT_MASK,पूर्ण,
	अणु .reg_offset = 1, .mask = RT8973A_INT2_POR_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = RT8973A_INT2_OTP_FET_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = RT8973A_INT2_OVP_FET_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = RT8973A_INT2_OCP_LATCH_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = RT8973A_INT2_OCP_MASK, पूर्ण,
	अणु .reg_offset = 1, .mask = RT8973A_INT2_OVP_OCP_MASK, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip rt8973a_muic_irq_chip = अणु
	.name			= "rt8973a",
	.status_base		= RT8973A_REG_INT1,
	.mask_base		= RT8973A_REG_INTM1,
	.mask_invert		= false,
	.num_regs		= 2,
	.irqs			= rt8973a_irqs,
	.num_irqs		= ARRAY_SIZE(rt8973a_irqs),
पूर्ण;

/* Define regmap configuration of RT8973A क्रम I2C communication  */
अटल bool rt8973a_muic_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT8973A_REG_INTM1:
	हाल RT8973A_REG_INTM2:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config rt8973a_muic_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.अस्थिर_reg	= rt8973a_muic_अस्थिर_reg,
	.max_रेजिस्टर	= RT8973A_REG_END,
पूर्ण;

/* Change DM_CON/DP_CON/VBUSIN चयन according to cable type */
अटल पूर्णांक rt8973a_muic_set_path(काष्ठा rt8973a_muic_info *info,
				अचिन्हित पूर्णांक con_sw, bool attached)
अणु
	पूर्णांक ret;

	/*
	 * Don't need to set h/w path according to cable type
	 * अगर Auto-configuration mode of CONTROL1 रेजिस्टर is true.
	 */
	अगर (info->स्वतः_config)
		वापस 0;

	अगर (!attached)
		con_sw	= DM_DP_SWITCH_UART;

	चयन (con_sw) अणु
	हाल DM_DP_SWITCH_OPEN:
	हाल DM_DP_SWITCH_USB:
	हाल DM_DP_SWITCH_UART:
		ret = regmap_update_bits(info->regmap, RT8973A_REG_MANUAL_SW1,
					RT8973A_REG_MANUAL_SW1_DP_MASK |
					RT8973A_REG_MANUAL_SW1_DM_MASK,
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

	वापस 0;
पूर्ण

अटल पूर्णांक rt8973a_muic_get_cable_type(काष्ठा rt8973a_muic_info *info)
अणु
	अचिन्हित पूर्णांक adc, dev1;
	पूर्णांक ret, cable_type;

	/* Read ADC value according to बाह्यal cable or button */
	ret = regmap_पढ़ो(info->regmap, RT8973A_REG_ADC, &adc);
	अगर (ret) अणु
		dev_err(info->dev, "failed to read ADC register\n");
		वापस ret;
	पूर्ण
	cable_type = adc & RT8973A_REG_ADC_MASK;

	/* Read Device 1 reigster to identअगरy correct cable type */
	ret = regmap_पढ़ो(info->regmap, RT8973A_REG_DEV1, &dev1);
	अगर (ret) अणु
		dev_err(info->dev, "failed to read DEV1 register\n");
		वापस ret;
	पूर्ण

	चयन (adc) अणु
	हाल RT8973A_MUIC_ADC_OPEN:
		अगर (dev1 & RT8973A_REG_DEV1_USB_MASK)
			cable_type = RT8973A_MUIC_ADC_USB;
		अन्यथा अगर (dev1 & RT8973A_REG_DEV1_DCPORT_MASK)
			cable_type = RT8973A_MUIC_ADC_TA;
		अन्यथा
			cable_type = RT8973A_MUIC_ADC_OPEN;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस cable_type;
पूर्ण

अटल पूर्णांक rt8973a_muic_cable_handler(काष्ठा rt8973a_muic_info *info,
					क्रमागत rt8973a_event_type event)
अणु
	अटल अचिन्हित पूर्णांक prev_cable_type;
	अचिन्हित पूर्णांक con_sw = DM_DP_SWITCH_UART;
	पूर्णांक ret, cable_type;
	अचिन्हित पूर्णांक id;
	bool attached = false;

	चयन (event) अणु
	हाल RT8973A_EVENT_ATTACH:
		cable_type = rt8973a_muic_get_cable_type(info);
		attached = true;
		अवरोध;
	हाल RT8973A_EVENT_DETACH:
		cable_type = prev_cable_type;
		attached = false;
		अवरोध;
	हाल RT8973A_EVENT_OVP:
	हाल RT8973A_EVENT_OTP:
		dev_warn(info->dev,
			"happen Over %s issue. Need to disconnect all cables\n",
			event == RT8973A_EVENT_OVP ? "Voltage" : "Temperature");
		cable_type = prev_cable_type;
		attached = false;
		अवरोध;
	शेष:
		dev_err(info->dev,
			"Cannot handle this event (event:%d)\n", event);
		वापस -EINVAL;
	पूर्ण
	prev_cable_type = cable_type;

	चयन (cable_type) अणु
	हाल RT8973A_MUIC_ADC_OTG:
		id = EXTCON_USB_HOST;
		con_sw = DM_DP_SWITCH_USB;
		अवरोध;
	हाल RT8973A_MUIC_ADC_TA:
		id = EXTCON_CHG_USB_DCP;
		con_sw = DM_DP_SWITCH_OPEN;
		अवरोध;
	हाल RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_OFF_USB:
	हाल RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_ON_USB:
		id = EXTCON_JIG;
		con_sw = DM_DP_SWITCH_USB;
		अवरोध;
	हाल RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_OFF_UART:
	हाल RT8973A_MUIC_ADC_FACTORY_MODE_BOOT_ON_UART:
		id = EXTCON_JIG;
		con_sw = DM_DP_SWITCH_UART;
		अवरोध;
	हाल RT8973A_MUIC_ADC_USB:
		id = EXTCON_USB;
		con_sw = DM_DP_SWITCH_USB;
		अवरोध;
	हाल RT8973A_MUIC_ADC_OPEN:
		वापस 0;
	हाल RT8973A_MUIC_ADC_UNKNOWN_ACC_1:
	हाल RT8973A_MUIC_ADC_UNKNOWN_ACC_2:
	हाल RT8973A_MUIC_ADC_UNKNOWN_ACC_3:
	हाल RT8973A_MUIC_ADC_UNKNOWN_ACC_4:
	हाल RT8973A_MUIC_ADC_UNKNOWN_ACC_5:
		dev_warn(info->dev,
			"Unknown accessory type (adc:0x%x)\n", cable_type);
		वापस 0;
	हाल RT8973A_MUIC_ADC_AUDIO_SEND_END_BUTTON:
	हाल RT8973A_MUIC_ADC_AUDIO_REMOTE_S1_BUTTON:
	हाल RT8973A_MUIC_ADC_AUDIO_REMOTE_S2_BUTTON:
	हाल RT8973A_MUIC_ADC_AUDIO_REMOTE_S3_BUTTON:
	हाल RT8973A_MUIC_ADC_AUDIO_REMOTE_S4_BUTTON:
	हाल RT8973A_MUIC_ADC_AUDIO_REMOTE_S5_BUTTON:
	हाल RT8973A_MUIC_ADC_AUDIO_REMOTE_S6_BUTTON:
	हाल RT8973A_MUIC_ADC_AUDIO_REMOTE_S7_BUTTON:
	हाल RT8973A_MUIC_ADC_AUDIO_REMOTE_S8_BUTTON:
	हाल RT8973A_MUIC_ADC_AUDIO_REMOTE_S9_BUTTON:
	हाल RT8973A_MUIC_ADC_AUDIO_REMOTE_S10_BUTTON:
	हाल RT8973A_MUIC_ADC_AUDIO_REMOTE_S11_BUTTON:
	हाल RT8973A_MUIC_ADC_AUDIO_REMOTE_S12_BUTTON:
	हाल RT8973A_MUIC_ADC_AUDIO_TYPE2:
		dev_warn(info->dev,
			"Audio device/button type (adc:0x%x)\n", cable_type);
		वापस 0;
	हाल RT8973A_MUIC_ADC_RESERVED_ACC_1:
	हाल RT8973A_MUIC_ADC_RESERVED_ACC_2:
	हाल RT8973A_MUIC_ADC_RESERVED_ACC_3:
	हाल RT8973A_MUIC_ADC_RESERVED_ACC_4:
	हाल RT8973A_MUIC_ADC_RESERVED_ACC_5:
	हाल RT8973A_MUIC_ADC_PHONE_POWERED_DEV:
		वापस 0;
	शेष:
		dev_err(info->dev,
			"Cannot handle this cable_type (adc:0x%x)\n",
			cable_type);
		वापस -EINVAL;
	पूर्ण

	/* Change पूर्णांकernal hardware path(DM_CON/DP_CON) */
	ret = rt8973a_muic_set_path(info, con_sw, attached);
	अगर (ret < 0)
		वापस ret;

	/* Change the state of बाह्यal accessory */
	extcon_set_state_sync(info->edev, id, attached);
	अगर (id == EXTCON_USB)
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
					attached);

	वापस 0;
पूर्ण

अटल व्योम rt8973a_muic_irq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt8973a_muic_info *info = container_of(work,
			काष्ठा rt8973a_muic_info, irq_work);
	पूर्णांक ret = 0;

	अगर (!info->edev)
		वापस;

	mutex_lock(&info->mutex);

	/* Detect attached or detached cables */
	अगर (info->irq_attach) अणु
		ret = rt8973a_muic_cable_handler(info, RT8973A_EVENT_ATTACH);
		info->irq_attach = false;
	पूर्ण

	अगर (info->irq_detach) अणु
		ret = rt8973a_muic_cable_handler(info, RT8973A_EVENT_DETACH);
		info->irq_detach = false;
	पूर्ण

	अगर (info->irq_ovp) अणु
		ret = rt8973a_muic_cable_handler(info, RT8973A_EVENT_OVP);
		info->irq_ovp = false;
	पूर्ण

	अगर (info->irq_otp) अणु
		ret = rt8973a_muic_cable_handler(info, RT8973A_EVENT_OTP);
		info->irq_otp = false;
	पूर्ण

	अगर (ret < 0)
		dev_err(info->dev, "failed to handle MUIC interrupt\n");

	mutex_unlock(&info->mutex);
पूर्ण

अटल irqवापस_t rt8973a_muic_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rt8973a_muic_info *info = data;
	पूर्णांक i, irq_type = -1;

	क्रम (i = 0; i < info->num_muic_irqs; i++)
		अगर (irq == info->muic_irqs[i].virq)
			irq_type = info->muic_irqs[i].irq;

	चयन (irq_type) अणु
	हाल RT8973A_INT1_ATTACH:
		info->irq_attach = true;
		अवरोध;
	हाल RT8973A_INT1_DETACH:
		info->irq_detach = true;
		अवरोध;
	हाल RT8973A_INT1_OVP:
		info->irq_ovp = true;
		अवरोध;
	हाल RT8973A_INT1_OTP:
		info->irq_otp = true;
		अवरोध;
	हाल RT8973A_INT1_CHGDET:
	हाल RT8973A_INT1_DCD_T:
	हाल RT8973A_INT1_CONNECT:
	हाल RT8973A_INT1_ADC_CHG:
	हाल RT8973A_INT2_UVLO:
	हाल RT8973A_INT2_POR:
	हाल RT8973A_INT2_OTP_FET:
	हाल RT8973A_INT2_OVP_FET:
	हाल RT8973A_INT2_OCP_LATCH:
	हाल RT8973A_INT2_OCP:
	हाल RT8973A_INT2_OVP_OCP:
	शेष:
		dev_dbg(info->dev,
			"Cannot handle this interrupt (%d)\n", irq_type);
		अवरोध;
	पूर्ण

	schedule_work(&info->irq_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rt8973a_muic_detect_cable_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt8973a_muic_info *info = container_of(to_delayed_work(work),
				काष्ठा rt8973a_muic_info, wq_detcable);
	पूर्णांक ret;

	/* Notअगरy the state of connector cable or not  */
	ret = rt8973a_muic_cable_handler(info, RT8973A_EVENT_ATTACH);
	अगर (ret < 0)
		dev_warn(info->dev, "failed to detect cable state\n");
पूर्ण

अटल व्योम rt8973a_init_dev_type(काष्ठा rt8973a_muic_info *info)
अणु
	अचिन्हित पूर्णांक data, venकरोr_id, version_id;
	पूर्णांक i, ret;

	/* To test I2C, Prपूर्णांक version_id and venकरोr_id of RT8973A */
	ret = regmap_पढ़ो(info->regmap, RT8973A_REG_DEVICE_ID, &data);
	अगर (ret) अणु
		dev_err(info->dev,
			"failed to read DEVICE_ID register: %d\n", ret);
		वापस;
	पूर्ण

	venकरोr_id = ((data & RT8973A_REG_DEVICE_ID_VENDOR_MASK) >>
				RT8973A_REG_DEVICE_ID_VENDOR_SHIFT);
	version_id = ((data & RT8973A_REG_DEVICE_ID_VERSION_MASK) >>
				RT8973A_REG_DEVICE_ID_VERSION_SHIFT);

	dev_info(info->dev, "Device type: version: 0x%x, vendor: 0x%x\n",
			    version_id, venकरोr_id);

	/* Initiazle the रेजिस्टर of RT8973A device to bring-up */
	क्रम (i = 0; i < info->num_reg_data; i++) अणु
		u8 reg = info->reg_data[i].reg;
		u8 mask = info->reg_data[i].mask;
		u8 val = 0;

		अगर (info->reg_data[i].invert)
			val = ~info->reg_data[i].val;
		अन्यथा
			val = info->reg_data[i].val;

		regmap_update_bits(info->regmap, reg, mask, val);
	पूर्ण

	/* Check whether RT8973A is स्वतः चयनing mode or not */
	ret = regmap_पढ़ो(info->regmap, RT8973A_REG_CONTROL1, &data);
	अगर (ret) अणु
		dev_err(info->dev,
			"failed to read CONTROL1 register: %d\n", ret);
		वापस;
	पूर्ण

	data &= RT8973A_REG_CONTROL1_AUTO_CONFIG_MASK;
	अगर (data) अणु
		info->स्वतः_config = true;
		dev_info(info->dev,
			"Enable Auto-configuration for internal path\n");
	पूर्ण
पूर्ण

अटल पूर्णांक rt8973a_muic_i2c_probe(काष्ठा i2c_client *i2c,
				 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device_node *np = i2c->dev.of_node;
	काष्ठा rt8973a_muic_info *info;
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
	info->muic_irqs = rt8973a_muic_irqs;
	info->num_muic_irqs = ARRAY_SIZE(rt8973a_muic_irqs);
	info->reg_data = rt8973a_reg_data;
	info->num_reg_data = ARRAY_SIZE(rt8973a_reg_data);

	mutex_init(&info->mutex);

	INIT_WORK(&info->irq_work, rt8973a_muic_irq_work);

	info->regmap = devm_regmap_init_i2c(i2c, &rt8973a_muic_regmap_config);
	अगर (IS_ERR(info->regmap)) अणु
		ret = PTR_ERR(info->regmap);
		dev_err(info->dev, "failed to allocate register map: %d\n",
				   ret);
		वापस ret;
	पूर्ण

	/* Support irq करोमुख्य क्रम RT8973A MUIC device */
	irq_flags = IRQF_TRIGGER_FALLING | IRQF_ONESHOT | IRQF_SHARED;
	ret = regmap_add_irq_chip(info->regmap, info->irq, irq_flags, 0,
				  &rt8973a_muic_irq_chip, &info->irq_data);
	अगर (ret != 0) अणु
		dev_err(info->dev, "failed to add irq_chip (irq:%d, err:%d)\n",
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
						rt8973a_muic_irq_handler,
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
	info->edev = devm_extcon_dev_allocate(info->dev, rt8973a_extcon_cable);
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
	INIT_DELAYED_WORK(&info->wq_detcable, rt8973a_muic_detect_cable_wq);
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &info->wq_detcable,
			msecs_to_jअगरfies(DELAY_MS_DEFAULT));

	/* Initialize RT8973A device and prपूर्णांक venकरोr id and version id */
	rt8973a_init_dev_type(info);

	वापस 0;
पूर्ण

अटल पूर्णांक rt8973a_muic_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा rt8973a_muic_info *info = i2c_get_clientdata(i2c);

	regmap_del_irq_chip(info->irq, info->irq_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rt8973a_dt_match[] = अणु
	अणु .compatible = "richtek,rt8973a-muic" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt8973a_dt_match);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rt8973a_muic_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा rt8973a_muic_info *info = i2c_get_clientdata(i2c);

	enable_irq_wake(info->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक rt8973a_muic_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा rt8973a_muic_info *info = i2c_get_clientdata(i2c);

	disable_irq_wake(info->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(rt8973a_muic_pm_ops,
			 rt8973a_muic_suspend, rt8973a_muic_resume);

अटल स्थिर काष्ठा i2c_device_id rt8973a_i2c_id[] = अणु
	अणु "rt8973a", TYPE_RT8973A पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt8973a_i2c_id);

अटल काष्ठा i2c_driver rt8973a_muic_i2c_driver = अणु
	.driver		= अणु
		.name	= "rt8973a",
		.pm	= &rt8973a_muic_pm_ops,
		.of_match_table = rt8973a_dt_match,
	पूर्ण,
	.probe	= rt8973a_muic_i2c_probe,
	.हटाओ	= rt8973a_muic_i2c_हटाओ,
	.id_table = rt8973a_i2c_id,
पूर्ण;

अटल पूर्णांक __init rt8973a_muic_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&rt8973a_muic_i2c_driver);
पूर्ण
subsys_initcall(rt8973a_muic_i2c_init);

MODULE_DESCRIPTION("Richtek RT8973A Extcon driver");
MODULE_AUTHOR("Chanwoo Choi <cw00.choi@samsung.com>");
MODULE_LICENSE("GPL");
