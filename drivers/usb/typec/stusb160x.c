<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * STMicroelectronics STUSB160x Type-C controller family driver
 *
 * Copyright (C) 2020, STMicroelectronics
 * Author(s): Amelie Delaunay <amelie.delaunay@st.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/usb/role.h>
#समावेश <linux/usb/typec.h>

#घोषणा STUSB160X_ALERT_STATUS			0x0B /* RC */
#घोषणा STUSB160X_ALERT_STATUS_MASK_CTRL	0x0C /* RW */
#घोषणा STUSB160X_CC_CONNECTION_STATUS_TRANS	0x0D /* RC */
#घोषणा STUSB160X_CC_CONNECTION_STATUS		0x0E /* RO */
#घोषणा STUSB160X_MONITORING_STATUS_TRANS	0x0F /* RC */
#घोषणा STUSB160X_MONITORING_STATUS		0x10 /* RO */
#घोषणा STUSB160X_CC_OPERATION_STATUS		0x11 /* RO */
#घोषणा STUSB160X_HW_FAULT_STATUS_TRANS		0x12 /* RC */
#घोषणा STUSB160X_HW_FAULT_STATUS		0x13 /* RO */
#घोषणा STUSB160X_CC_CAPABILITY_CTRL		0x18 /* RW */
#घोषणा STUSB160X_CC_VCONN_SWITCH_CTRL		0x1E /* RW */
#घोषणा STUSB160X_VCONN_MONITORING_CTRL		0x20 /* RW */
#घोषणा STUSB160X_VBUS_MONITORING_RANGE_CTRL	0x22 /* RW */
#घोषणा STUSB160X_RESET_CTRL			0x23 /* RW */
#घोषणा STUSB160X_VBUS_DISCHARGE_TIME_CTRL	0x25 /* RW */
#घोषणा STUSB160X_VBUS_DISCHARGE_STATUS		0x26 /* RO */
#घोषणा STUSB160X_VBUS_ENABLE_STATUS		0x27 /* RO */
#घोषणा STUSB160X_CC_POWER_MODE_CTRL		0x28 /* RW */
#घोषणा STUSB160X_VBUS_MONITORING_CTRL		0x2E /* RW */
#घोषणा STUSB1600_REG_MAX			0x2F /* RO - Reserved */

/* STUSB160X_ALERT_STATUS/STUSB160X_ALERT_STATUS_MASK_CTRL bitfields */
#घोषणा STUSB160X_HW_FAULT			BIT(4)
#घोषणा STUSB160X_MONITORING			BIT(5)
#घोषणा STUSB160X_CC_CONNECTION			BIT(6)
#घोषणा STUSB160X_ALL_ALERTS			GENMASK(6, 4)

/* STUSB160X_CC_CONNECTION_STATUS_TRANS bitfields */
#घोषणा STUSB160X_CC_ATTACH_TRANS		BIT(0)

/* STUSB160X_CC_CONNECTION_STATUS bitfields */
#घोषणा STUSB160X_CC_ATTACH			BIT(0)
#घोषणा STUSB160X_CC_VCONN_SUPPLY		BIT(1)
#घोषणा STUSB160X_CC_DATA_ROLE(s)		(!!((s) & BIT(2)))
#घोषणा STUSB160X_CC_POWER_ROLE(s)		(!!((s) & BIT(3)))
#घोषणा STUSB160X_CC_ATTACHED_MODE		GENMASK(7, 5)

/* STUSB160X_MONITORING_STATUS_TRANS bitfields */
#घोषणा STUSB160X_VCONN_PRESENCE_TRANS		BIT(0)
#घोषणा STUSB160X_VBUS_PRESENCE_TRANS		BIT(1)
#घोषणा STUSB160X_VBUS_VSAFE0V_TRANS		BIT(2)
#घोषणा STUSB160X_VBUS_VALID_TRANS		BIT(3)

/* STUSB160X_MONITORING_STATUS bitfields */
#घोषणा STUSB160X_VCONN_PRESENCE		BIT(0)
#घोषणा STUSB160X_VBUS_PRESENCE			BIT(1)
#घोषणा STUSB160X_VBUS_VSAFE0V			BIT(2)
#घोषणा STUSB160X_VBUS_VALID			BIT(3)

/* STUSB160X_CC_OPERATION_STATUS bitfields */
#घोषणा STUSB160X_TYPEC_FSM_STATE		GENMASK(4, 0)
#घोषणा STUSB160X_SINK_POWER_STATE		GENMASK(6, 5)
#घोषणा STUSB160X_CC_ATTACHED			BIT(7)

/* STUSB160X_HW_FAULT_STATUS_TRANS bitfields */
#घोषणा STUSB160X_VCONN_SW_OVP_FAULT_TRANS	BIT(0)
#घोषणा STUSB160X_VCONN_SW_OCP_FAULT_TRANS	BIT(1)
#घोषणा STUSB160X_VCONN_SW_RVP_FAULT_TRANS	BIT(2)
#घोषणा STUSB160X_VPU_VALID_TRANS		BIT(4)
#घोषणा STUSB160X_VPU_OVP_FAULT_TRANS		BIT(5)
#घोषणा STUSB160X_THERMAL_FAULT			BIT(7)

/* STUSB160X_HW_FAULT_STATUS bitfields */
#घोषणा STUSB160X_VCONN_SW_OVP_FAULT_CC2	BIT(0)
#घोषणा STUSB160X_VCONN_SW_OVP_FAULT_CC1	BIT(1)
#घोषणा STUSB160X_VCONN_SW_OCP_FAULT_CC2	BIT(2)
#घोषणा STUSB160X_VCONN_SW_OCP_FAULT_CC1	BIT(3)
#घोषणा STUSB160X_VCONN_SW_RVP_FAULT_CC2	BIT(4)
#घोषणा STUSB160X_VCONN_SW_RVP_FAULT_CC1	BIT(5)
#घोषणा STUSB160X_VPU_VALID			BIT(6)
#घोषणा STUSB160X_VPU_OVP_FAULT			BIT(7)

/* STUSB160X_CC_CAPABILITY_CTRL bitfields */
#घोषणा STUSB160X_CC_VCONN_SUPPLY_EN		BIT(0)
#घोषणा STUSB160X_CC_VCONN_DISCHARGE_EN		BIT(4)
#घोषणा STUSB160X_CC_CURRENT_ADVERTISED		GENMASK(7, 6)

/* STUSB160X_VCONN_SWITCH_CTRL bitfields */
#घोषणा STUSB160X_CC_VCONN_SWITCH_ILIM		GENMASK(3, 0)

/* STUSB160X_VCONN_MONITORING_CTRL bitfields */
#घोषणा STUSB160X_VCONN_UVLO_THRESHOLD		BIT(6)
#घोषणा STUSB160X_VCONN_MONITORING_EN		BIT(7)

/* STUSB160X_VBUS_MONITORING_RANGE_CTRL bitfields */
#घोषणा STUSB160X_SHIFT_LOW_VBUS_LIMIT		GENMASK(3, 0)
#घोषणा STUSB160X_SHIFT_HIGH_VBUS_LIMIT		GENMASK(7, 4)

/* STUSB160X_RESET_CTRL bitfields */
#घोषणा STUSB160X_SW_RESET_EN			BIT(0)

/* STUSB160X_VBUS_DISCHARGE_TIME_CTRL bitfields */
#घोषणा STUSBXX02_VBUS_DISCHARGE_TIME_TO_PDO	GENMASK(3, 0)
#घोषणा STUSB160X_VBUS_DISCHARGE_TIME_TO_0V	GENMASK(7, 4)

/* STUSB160X_VBUS_DISCHARGE_STATUS bitfields */
#घोषणा STUSB160X_VBUS_DISCHARGE_EN		BIT(7)

/* STUSB160X_VBUS_ENABLE_STATUS bitfields */
#घोषणा STUSB160X_VBUS_SOURCE_EN		BIT(0)
#घोषणा STUSB160X_VBUS_SINK_EN			BIT(1)

/* STUSB160X_CC_POWER_MODE_CTRL bitfields */
#घोषणा STUSB160X_CC_POWER_MODE			GENMASK(2, 0)

/* STUSB160X_VBUS_MONITORING_CTRL bitfields */
#घोषणा STUSB160X_VDD_UVLO_DISABLE		BIT(0)
#घोषणा STUSB160X_VBUS_VSAFE0V_THRESHOLD	GENMASK(2, 1)
#घोषणा STUSB160X_VBUS_RANGE_DISABLE		BIT(4)
#घोषणा STUSB160X_VDD_OVLO_DISABLE		BIT(6)

क्रमागत stusb160x_pwr_mode अणु
	SOURCE_WITH_ACCESSORY,
	SINK_WITH_ACCESSORY,
	SINK_WITHOUT_ACCESSORY,
	DUAL_WITH_ACCESSORY,
	DUAL_WITH_ACCESSORY_AND_TRY_SRC,
	DUAL_WITH_ACCESSORY_AND_TRY_SNK,
पूर्ण;

क्रमागत stusb160x_attached_mode अणु
	NO_DEVICE_ATTACHED,
	SINK_ATTACHED,
	SOURCE_ATTACHED,
	DEBUG_ACCESSORY_ATTACHED,
	AUDIO_ACCESSORY_ATTACHED,
पूर्ण;

काष्ठा stusb160x अणु
	काष्ठा device		*dev;
	काष्ठा regmap		*regmap;
	काष्ठा regulator	*vdd_supply;
	काष्ठा regulator	*vsys_supply;
	काष्ठा regulator	*vconn_supply;
	काष्ठा regulator	*मुख्य_supply;

	काष्ठा typec_port	*port;
	काष्ठा typec_capability capability;
	काष्ठा typec_partner	*partner;

	क्रमागत typec_port_type	port_type;
	क्रमागत typec_pwr_opmode	pwr_opmode;
	bool			vbus_on;

	काष्ठा usb_role_चयन	*role_sw;
पूर्ण;

अटल bool stusb160x_reg_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल STUSB160X_ALERT_STATUS_MASK_CTRL:
	हाल STUSB160X_CC_CAPABILITY_CTRL:
	हाल STUSB160X_CC_VCONN_SWITCH_CTRL:
	हाल STUSB160X_VCONN_MONITORING_CTRL:
	हाल STUSB160X_VBUS_MONITORING_RANGE_CTRL:
	हाल STUSB160X_RESET_CTRL:
	हाल STUSB160X_VBUS_DISCHARGE_TIME_CTRL:
	हाल STUSB160X_CC_POWER_MODE_CTRL:
	हाल STUSB160X_VBUS_MONITORING_CTRL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool stusb160x_reg_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg <= 0x0A ||
	    (reg >= 0x14 && reg <= 0x17) ||
	    (reg >= 0x19 && reg <= 0x1D) ||
	    (reg >= 0x29 && reg <= 0x2D) ||
	    (reg == 0x1F || reg == 0x21 || reg == 0x24 || reg == 0x2F))
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल bool stusb160x_reg_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल STUSB160X_ALERT_STATUS:
	हाल STUSB160X_CC_CONNECTION_STATUS_TRANS:
	हाल STUSB160X_CC_CONNECTION_STATUS:
	हाल STUSB160X_MONITORING_STATUS_TRANS:
	हाल STUSB160X_MONITORING_STATUS:
	हाल STUSB160X_CC_OPERATION_STATUS:
	हाल STUSB160X_HW_FAULT_STATUS_TRANS:
	हाल STUSB160X_HW_FAULT_STATUS:
	हाल STUSB160X_VBUS_DISCHARGE_STATUS:
	हाल STUSB160X_VBUS_ENABLE_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool stusb160x_reg_precious(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल STUSB160X_ALERT_STATUS:
	हाल STUSB160X_CC_CONNECTION_STATUS_TRANS:
	हाल STUSB160X_MONITORING_STATUS_TRANS:
	हाल STUSB160X_HW_FAULT_STATUS_TRANS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config stusb1600_regmap_config = अणु
	.reg_bits	= 8,
	.reg_stride	= 1,
	.val_bits	= 8,
	.max_रेजिस्टर	= STUSB1600_REG_MAX,
	.ग_लिखोable_reg	= stusb160x_reg_ग_लिखोable,
	.पढ़ोable_reg	= stusb160x_reg_पढ़ोable,
	.अस्थिर_reg	= stusb160x_reg_अस्थिर,
	.precious_reg	= stusb160x_reg_precious,
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

अटल bool stusb160x_get_vconn(काष्ठा stusb160x *chip)
अणु
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(chip->regmap, STUSB160X_CC_CAPABILITY_CTRL, &val);
	अगर (ret) अणु
		dev_err(chip->dev, "Unable to get Vconn status: %d\n", ret);
		वापस false;
	पूर्ण

	वापस !!FIELD_GET(STUSB160X_CC_VCONN_SUPPLY_EN, val);
पूर्ण

अटल पूर्णांक stusb160x_set_vconn(काष्ठा stusb160x *chip, bool on)
अणु
	पूर्णांक ret;

	/* Manage VCONN input supply */
	अगर (chip->vconn_supply) अणु
		अगर (on) अणु
			ret = regulator_enable(chip->vconn_supply);
			अगर (ret) अणु
				dev_err(chip->dev,
					"failed to enable vconn supply: %d\n",
					ret);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			regulator_disable(chip->vconn_supply);
		पूर्ण
	पूर्ण

	/* Manage VCONN monitoring and घातer path */
	ret = regmap_update_bits(chip->regmap, STUSB160X_VCONN_MONITORING_CTRL,
				 STUSB160X_VCONN_MONITORING_EN,
				 on ? STUSB160X_VCONN_MONITORING_EN : 0);
	अगर (ret)
		जाओ vconn_reg_disable;

	वापस 0;

vconn_reg_disable:
	अगर (chip->vconn_supply && on)
		regulator_disable(chip->vconn_supply);

	वापस ret;
पूर्ण

अटल क्रमागत typec_pwr_opmode stusb160x_get_pwr_opmode(काष्ठा stusb160x *chip)
अणु
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(chip->regmap, STUSB160X_CC_CAPABILITY_CTRL, &val);
	अगर (ret) अणु
		dev_err(chip->dev, "Unable to get pwr opmode: %d\n", ret);
		वापस TYPEC_PWR_MODE_USB;
	पूर्ण

	वापस FIELD_GET(STUSB160X_CC_CURRENT_ADVERTISED, val);
पूर्ण

अटल क्रमागत typec_accessory stusb160x_get_accessory(u32 status)
अणु
	क्रमागत stusb160x_attached_mode mode;

	mode = FIELD_GET(STUSB160X_CC_ATTACHED_MODE, status);

	चयन (mode) अणु
	हाल DEBUG_ACCESSORY_ATTACHED:
		वापस TYPEC_ACCESSORY_DEBUG;
	हाल AUDIO_ACCESSORY_ATTACHED:
		वापस TYPEC_ACCESSORY_AUDIO;
	शेष:
		वापस TYPEC_ACCESSORY_NONE;
	पूर्ण
पूर्ण

अटल क्रमागत typec_role stusb160x_get_vconn_role(u32 status)
अणु
	अगर (FIELD_GET(STUSB160X_CC_VCONN_SUPPLY, status))
		वापस TYPEC_SOURCE;

	वापस TYPEC_SINK;
पूर्ण

अटल व्योम stusb160x_set_data_role(काष्ठा stusb160x *chip,
				    क्रमागत typec_data_role data_role,
				    bool attached)
अणु
	क्रमागत usb_role usb_role = USB_ROLE_NONE;

	अगर (attached) अणु
		अगर (data_role == TYPEC_HOST)
			usb_role = USB_ROLE_HOST;
		अन्यथा
			usb_role = USB_ROLE_DEVICE;
	पूर्ण

	usb_role_चयन_set_role(chip->role_sw, usb_role);
	typec_set_data_role(chip->port, data_role);
पूर्ण

अटल पूर्णांक stusb160x_attach(काष्ठा stusb160x *chip, u32 status)
अणु
	काष्ठा typec_partner_desc desc;
	पूर्णांक ret;

	अगर ((STUSB160X_CC_POWER_ROLE(status) == TYPEC_SOURCE) &&
	    chip->vdd_supply) अणु
		ret = regulator_enable(chip->vdd_supply);
		अगर (ret) अणु
			dev_err(chip->dev,
				"Failed to enable Vbus supply: %d\n", ret);
			वापस ret;
		पूर्ण
		chip->vbus_on = true;
	पूर्ण

	desc.usb_pd = false;
	desc.accessory = stusb160x_get_accessory(status);
	desc.identity = शून्य;

	chip->partner = typec_रेजिस्टर_partner(chip->port, &desc);
	अगर (IS_ERR(chip->partner)) अणु
		ret = PTR_ERR(chip->partner);
		जाओ vbus_disable;
	पूर्ण

	typec_set_pwr_role(chip->port, STUSB160X_CC_POWER_ROLE(status));
	typec_set_pwr_opmode(chip->port, stusb160x_get_pwr_opmode(chip));
	typec_set_vconn_role(chip->port, stusb160x_get_vconn_role(status));
	stusb160x_set_data_role(chip, STUSB160X_CC_DATA_ROLE(status), true);

	वापस 0;

vbus_disable:
	अगर (chip->vbus_on) अणु
		regulator_disable(chip->vdd_supply);
		chip->vbus_on = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम stusb160x_detach(काष्ठा stusb160x *chip, u32 status)
अणु
	typec_unरेजिस्टर_partner(chip->partner);
	chip->partner = शून्य;

	typec_set_pwr_role(chip->port, STUSB160X_CC_POWER_ROLE(status));
	typec_set_pwr_opmode(chip->port, TYPEC_PWR_MODE_USB);
	typec_set_vconn_role(chip->port, stusb160x_get_vconn_role(status));
	stusb160x_set_data_role(chip, STUSB160X_CC_DATA_ROLE(status), false);

	अगर (chip->vbus_on) अणु
		regulator_disable(chip->vdd_supply);
		chip->vbus_on = false;
	पूर्ण
पूर्ण

अटल irqवापस_t stusb160x_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा stusb160x *chip = data;
	u32 pending, trans, status;
	पूर्णांक ret;

	ret = regmap_पढ़ो(chip->regmap, STUSB160X_ALERT_STATUS, &pending);
	अगर (ret)
		जाओ err;

	अगर (pending & STUSB160X_CC_CONNECTION) अणु
		ret = regmap_पढ़ो(chip->regmap,
				  STUSB160X_CC_CONNECTION_STATUS_TRANS, &trans);
		अगर (ret)
			जाओ err;
		ret = regmap_पढ़ो(chip->regmap,
				  STUSB160X_CC_CONNECTION_STATUS, &status);
		अगर (ret)
			जाओ err;

		अगर (trans & STUSB160X_CC_ATTACH_TRANS) अणु
			अगर (status & STUSB160X_CC_ATTACH) अणु
				ret = stusb160x_attach(chip, status);
				अगर (ret)
					जाओ err;
			पूर्ण अन्यथा अणु
				stusb160x_detach(chip, status);
			पूर्ण
		पूर्ण
	पूर्ण
err:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक stusb160x_irq_init(काष्ठा stusb160x *chip, पूर्णांक irq)
अणु
	u32 status;
	पूर्णांक ret;

	ret = regmap_पढ़ो(chip->regmap,
			  STUSB160X_CC_CONNECTION_STATUS, &status);
	अगर (ret)
		वापस ret;

	अगर (status & STUSB160X_CC_ATTACH) अणु
		ret = stusb160x_attach(chip, status);
		अगर (ret)
			dev_err(chip->dev, "attach failed: %d\n", ret);
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(chip->dev, irq, शून्य,
					stusb160x_irq_handler, IRQF_ONESHOT,
					dev_name(chip->dev), chip);
	अगर (ret)
		जाओ partner_unरेजिस्टर;

	/* Unmask CC_CONNECTION events */
	ret = regmap_ग_लिखो_bits(chip->regmap, STUSB160X_ALERT_STATUS_MASK_CTRL,
				STUSB160X_CC_CONNECTION, 0);
	अगर (ret)
		जाओ partner_unरेजिस्टर;

	वापस 0;

partner_unरेजिस्टर:
	अगर (chip->partner) अणु
		typec_unरेजिस्टर_partner(chip->partner);
		chip->partner = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक stusb160x_chip_init(काष्ठा stusb160x *chip)
अणु
	u32 val;
	पूर्णांक ret;

	/* Change the शेष Type-C घातer mode */
	अगर (chip->port_type == TYPEC_PORT_SRC)
		ret = regmap_update_bits(chip->regmap,
					 STUSB160X_CC_POWER_MODE_CTRL,
					 STUSB160X_CC_POWER_MODE,
					 SOURCE_WITH_ACCESSORY);
	अन्यथा अगर (chip->port_type == TYPEC_PORT_SNK)
		ret = regmap_update_bits(chip->regmap,
					 STUSB160X_CC_POWER_MODE_CTRL,
					 STUSB160X_CC_POWER_MODE,
					 SINK_WITH_ACCESSORY);
	अन्यथा /* (chip->port_type == TYPEC_PORT_DRP) */
		ret = regmap_update_bits(chip->regmap,
					 STUSB160X_CC_POWER_MODE_CTRL,
					 STUSB160X_CC_POWER_MODE,
					 DUAL_WITH_ACCESSORY);
	अगर (ret)
		वापस ret;

	अगर (chip->port_type == TYPEC_PORT_SNK)
		जाओ skip_src;

	/* Change the शेष Type-C Source घातer operation mode capability */
	ret = regmap_update_bits(chip->regmap, STUSB160X_CC_CAPABILITY_CTRL,
				 STUSB160X_CC_CURRENT_ADVERTISED,
				 FIELD_PREP(STUSB160X_CC_CURRENT_ADVERTISED,
					    chip->pwr_opmode));
	अगर (ret)
		वापस ret;

	/* Manage Type-C Source Vconn supply */
	अगर (stusb160x_get_vconn(chip)) अणु
		ret = stusb160x_set_vconn(chip, true);
		अगर (ret)
			वापस ret;
	पूर्ण

skip_src:
	/* Mask all events पूर्णांकerrupts - to be unmasked with पूर्णांकerrupt support */
	ret = regmap_update_bits(chip->regmap, STUSB160X_ALERT_STATUS_MASK_CTRL,
				 STUSB160X_ALL_ALERTS, STUSB160X_ALL_ALERTS);
	अगर (ret)
		वापस ret;

	/* Read status at least once to clear any stale पूर्णांकerrupts */
	regmap_पढ़ो(chip->regmap, STUSB160X_ALERT_STATUS, &val);
	regmap_पढ़ो(chip->regmap, STUSB160X_CC_CONNECTION_STATUS_TRANS, &val);
	regmap_पढ़ो(chip->regmap, STUSB160X_MONITORING_STATUS_TRANS, &val);
	regmap_पढ़ो(chip->regmap, STUSB160X_HW_FAULT_STATUS_TRANS, &val);

	वापस 0;
पूर्ण

अटल पूर्णांक stusb160x_get_fw_caps(काष्ठा stusb160x *chip,
				 काष्ठा fwnode_handle *fwnode)
अणु
	स्थिर अक्षर *cap_str;
	पूर्णांक ret;

	chip->capability.fwnode = fwnode;

	/*
	 * Supported port type can be configured through device tree
	 * अन्यथा it is पढ़ो from chip रेजिस्टरs in stusb160x_get_caps.
	 */
	ret = fwnode_property_पढ़ो_string(fwnode, "power-role", &cap_str);
	अगर (!ret) अणु
		ret = typec_find_port_घातer_role(cap_str);
		अगर (ret < 0)
			वापस ret;
		chip->port_type = ret;
	पूर्ण
	chip->capability.type = chip->port_type;

	/* Skip DRP/Source capabilities in हाल of Sink only */
	अगर (chip->port_type == TYPEC_PORT_SNK)
		वापस 0;

	अगर (chip->port_type == TYPEC_PORT_DRP)
		chip->capability.prefer_role = TYPEC_SINK;

	/*
	 * Supported घातer operation mode can be configured through device tree
	 * अन्यथा it is पढ़ो from chip रेजिस्टरs in stusb160x_get_caps.
	 */
	ret = fwnode_property_पढ़ो_string(fwnode, "typec-power-opmode", &cap_str);
	अगर (!ret) अणु
		ret = typec_find_pwr_opmode(cap_str);
		/* Power delivery not yet supported */
		अगर (ret < 0 || ret == TYPEC_PWR_MODE_PD) अणु
			dev_err(chip->dev, "bad power operation mode: %d\n", ret);
			वापस -EINVAL;
		पूर्ण
		chip->pwr_opmode = ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stusb160x_get_caps(काष्ठा stusb160x *chip)
अणु
	क्रमागत typec_port_type *type = &chip->capability.type;
	क्रमागत typec_port_data *data = &chip->capability.data;
	क्रमागत typec_accessory *accessory = chip->capability.accessory;
	u32 val;
	पूर्णांक ret;

	chip->capability.revision = USB_TYPEC_REV_1_2;

	ret = regmap_पढ़ो(chip->regmap, STUSB160X_CC_POWER_MODE_CTRL, &val);
	अगर (ret)
		वापस ret;

	चयन (FIELD_GET(STUSB160X_CC_POWER_MODE, val)) अणु
	हाल SOURCE_WITH_ACCESSORY:
		*type = TYPEC_PORT_SRC;
		*data = TYPEC_PORT_DFP;
		*accessory++ = TYPEC_ACCESSORY_AUDIO;
		*accessory++ = TYPEC_ACCESSORY_DEBUG;
		अवरोध;
	हाल SINK_WITH_ACCESSORY:
		*type = TYPEC_PORT_SNK;
		*data = TYPEC_PORT_UFP;
		*accessory++ = TYPEC_ACCESSORY_AUDIO;
		*accessory++ = TYPEC_ACCESSORY_DEBUG;
		अवरोध;
	हाल SINK_WITHOUT_ACCESSORY:
		*type = TYPEC_PORT_SNK;
		*data = TYPEC_PORT_UFP;
		अवरोध;
	हाल DUAL_WITH_ACCESSORY:
	हाल DUAL_WITH_ACCESSORY_AND_TRY_SRC:
	हाल DUAL_WITH_ACCESSORY_AND_TRY_SNK:
		*type = TYPEC_PORT_DRP;
		*data = TYPEC_PORT_DRD;
		*accessory++ = TYPEC_ACCESSORY_AUDIO;
		*accessory++ = TYPEC_ACCESSORY_DEBUG;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	chip->port_type = *type;
	chip->pwr_opmode = stusb160x_get_pwr_opmode(chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id stusb160x_of_match[] = अणु
	अणु .compatible = "st,stusb1600", .data = &stusb1600_regmap_configपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, stusb160x_of_match);

अटल पूर्णांक stusb160x_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा stusb160x *chip;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा regmap_config *regmap_config;
	काष्ठा fwnode_handle *fwnode;
	पूर्णांक ret;

	chip = devm_kzalloc(&client->dev, माप(काष्ठा stusb160x), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	i2c_set_clientdata(client, chip);

	match = i2c_of_match_device(stusb160x_of_match, client);
	regmap_config = (काष्ठा regmap_config *)match->data;
	chip->regmap = devm_regmap_init_i2c(client, regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		ret = PTR_ERR(chip->regmap);
		dev_err(&client->dev,
			"Failed to allocate register map:%d\n", ret);
		वापस ret;
	पूर्ण

	chip->dev = &client->dev;

	chip->vsys_supply = devm_regulator_get_optional(chip->dev, "vsys");
	अगर (IS_ERR(chip->vsys_supply)) अणु
		ret = PTR_ERR(chip->vsys_supply);
		अगर (ret != -ENODEV)
			वापस ret;
		chip->vsys_supply = शून्य;
	पूर्ण

	chip->vdd_supply = devm_regulator_get_optional(chip->dev, "vdd");
	अगर (IS_ERR(chip->vdd_supply)) अणु
		ret = PTR_ERR(chip->vdd_supply);
		अगर (ret != -ENODEV)
			वापस ret;
		chip->vdd_supply = शून्य;
	पूर्ण

	chip->vconn_supply = devm_regulator_get_optional(chip->dev, "vconn");
	अगर (IS_ERR(chip->vconn_supply)) अणु
		ret = PTR_ERR(chip->vconn_supply);
		अगर (ret != -ENODEV)
			वापस ret;
		chip->vconn_supply = शून्य;
	पूर्ण

	fwnode = device_get_named_child_node(chip->dev, "connector");
	अगर (!fwnode)
		वापस -ENODEV;

	/*
	 * When both VDD and VSYS घातer supplies are present, the low घातer
	 * supply VSYS is selected when VSYS voltage is above 3.1 V.
	 * Otherwise VDD is selected.
	 */
	अगर (chip->vdd_supply &&
	    (!chip->vsys_supply ||
	     (regulator_get_voltage(chip->vsys_supply) <= 3100000)))
		chip->मुख्य_supply = chip->vdd_supply;
	अन्यथा
		chip->मुख्य_supply = chip->vsys_supply;

	अगर (chip->मुख्य_supply) अणु
		ret = regulator_enable(chip->मुख्य_supply);
		अगर (ret) अणु
			dev_err(chip->dev,
				"Failed to enable main supply: %d\n", ret);
			जाओ fwnode_put;
		पूर्ण
	पूर्ण

	/* Get configuration from chip */
	ret = stusb160x_get_caps(chip);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to get port caps: %d\n", ret);
		जाओ मुख्य_reg_disable;
	पूर्ण

	/* Get optional re-configuration from device tree */
	ret = stusb160x_get_fw_caps(chip, fwnode);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to get connector caps: %d\n", ret);
		जाओ मुख्य_reg_disable;
	पूर्ण

	ret = stusb160x_chip_init(chip);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to init port: %d\n", ret);
		जाओ मुख्य_reg_disable;
	पूर्ण

	chip->port = typec_रेजिस्टर_port(chip->dev, &chip->capability);
	अगर (IS_ERR(chip->port)) अणु
		ret = PTR_ERR(chip->port);
		जाओ all_reg_disable;
	पूर्ण

	/*
	 * Default घातer operation mode initialization: will be updated upon
	 * attach/detach पूर्णांकerrupt
	 */
	typec_set_pwr_opmode(chip->port, chip->pwr_opmode);

	अगर (client->irq) अणु
		ret = stusb160x_irq_init(chip, client->irq);
		अगर (ret)
			जाओ port_unरेजिस्टर;

		chip->role_sw = fwnode_usb_role_चयन_get(fwnode);
		अगर (IS_ERR(chip->role_sw)) अणु
			ret = PTR_ERR(chip->role_sw);
			अगर (ret != -EPROBE_DEFER)
				dev_err(chip->dev,
					"Failed to get usb role switch: %d\n",
					ret);
			जाओ port_unरेजिस्टर;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * If Source or Dual घातer role, need to enable VDD supply
		 * providing Vbus अगर present. In हाल of पूर्णांकerrupt support,
		 * VDD supply will be dynamically managed upon attach/detach
		 * पूर्णांकerrupt.
		 */
		अगर (chip->port_type != TYPEC_PORT_SNK && chip->vdd_supply) अणु
			ret = regulator_enable(chip->vdd_supply);
			अगर (ret) अणु
				dev_err(chip->dev,
					"Failed to enable VDD supply: %d\n",
					ret);
				जाओ port_unरेजिस्टर;
			पूर्ण
			chip->vbus_on = true;
		पूर्ण
	पूर्ण

	fwnode_handle_put(fwnode);

	वापस 0;

port_unरेजिस्टर:
	typec_unरेजिस्टर_port(chip->port);
all_reg_disable:
	अगर (stusb160x_get_vconn(chip))
		stusb160x_set_vconn(chip, false);
मुख्य_reg_disable:
	अगर (chip->मुख्य_supply)
		regulator_disable(chip->मुख्य_supply);
fwnode_put:
	fwnode_handle_put(fwnode);

	वापस ret;
पूर्ण

अटल पूर्णांक stusb160x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा stusb160x *chip = i2c_get_clientdata(client);

	अगर (chip->partner) अणु
		typec_unरेजिस्टर_partner(chip->partner);
		chip->partner = शून्य;
	पूर्ण

	अगर (chip->vbus_on)
		regulator_disable(chip->vdd_supply);

	अगर (chip->role_sw)
		usb_role_चयन_put(chip->role_sw);

	typec_unरेजिस्टर_port(chip->port);

	अगर (stusb160x_get_vconn(chip))
		stusb160x_set_vconn(chip, false);

	अगर (chip->मुख्य_supply)
		regulator_disable(chip->मुख्य_supply);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused stusb160x_suspend(काष्ठा device *dev)
अणु
	काष्ठा stusb160x *chip = dev_get_drvdata(dev);

	/* Mask पूर्णांकerrupts */
	वापस regmap_update_bits(chip->regmap,
				  STUSB160X_ALERT_STATUS_MASK_CTRL,
				  STUSB160X_ALL_ALERTS, STUSB160X_ALL_ALERTS);
पूर्ण

अटल पूर्णांक __maybe_unused stusb160x_resume(काष्ठा device *dev)
अणु
	काष्ठा stusb160x *chip = dev_get_drvdata(dev);
	u32 status;
	पूर्णांक ret;

	ret = regcache_sync(chip->regmap);
	अगर (ret)
		वापस ret;

	/* Check अगर attach/detach occurred during low घातer */
	ret = regmap_पढ़ो(chip->regmap,
			  STUSB160X_CC_CONNECTION_STATUS, &status);
	अगर (ret)
		वापस ret;

	अगर (chip->partner && !(status & STUSB160X_CC_ATTACH))
		stusb160x_detach(chip, status);

	अगर (!chip->partner && (status & STUSB160X_CC_ATTACH)) अणु
		ret = stusb160x_attach(chip, status);
		अगर (ret)
			dev_err(chip->dev, "attach failed: %d\n", ret);
	पूर्ण

	/* Unmask पूर्णांकerrupts */
	वापस regmap_ग_लिखो_bits(chip->regmap, STUSB160X_ALERT_STATUS_MASK_CTRL,
				 STUSB160X_CC_CONNECTION, 0);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(stusb160x_pm_ops, stusb160x_suspend, stusb160x_resume);

अटल काष्ठा i2c_driver stusb160x_driver = अणु
	.driver = अणु
		.name = "stusb160x",
		.pm = &stusb160x_pm_ops,
		.of_match_table = stusb160x_of_match,
	पूर्ण,
	.probe_new = stusb160x_probe,
	.हटाओ = stusb160x_हटाओ,
पूर्ण;
module_i2c_driver(stusb160x_driver);

MODULE_AUTHOR("Amelie Delaunay <amelie.delaunay@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STUSB160x Type-C controller driver");
MODULE_LICENSE("GPL v2");
