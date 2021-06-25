<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम TI TPS6598x USB Power Delivery controller family
 *
 * Copyright (C) 2017, Intel Corporation
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb/typec.h>
#समावेश <linux/usb/role.h>

#समावेश "tps6598x.h"
#समावेश "trace.h"

/* Register offsets */
#घोषणा TPS_REG_VID			0x00
#घोषणा TPS_REG_MODE			0x03
#घोषणा TPS_REG_CMD1			0x08
#घोषणा TPS_REG_DATA1			0x09
#घोषणा TPS_REG_INT_EVENT1		0x14
#घोषणा TPS_REG_INT_EVENT2		0x15
#घोषणा TPS_REG_INT_MASK1		0x16
#घोषणा TPS_REG_INT_MASK2		0x17
#घोषणा TPS_REG_INT_CLEAR1		0x18
#घोषणा TPS_REG_INT_CLEAR2		0x19
#घोषणा TPS_REG_STATUS			0x1a
#घोषणा TPS_REG_SYSTEM_CONF		0x28
#घोषणा TPS_REG_CTRL_CONF		0x29
#घोषणा TPS_REG_POWER_STATUS		0x3f
#घोषणा TPS_REG_RX_IDENTITY_SOP		0x48
#घोषणा TPS_REG_DATA_STATUS		0x5f

/* TPS_REG_SYSTEM_CONF bits */
#घोषणा TPS_SYSCONF_PORTINFO(c)		((c) & 7)

क्रमागत अणु
	TPS_PORTINFO_SINK,
	TPS_PORTINFO_SINK_ACCESSORY,
	TPS_PORTINFO_DRP_UFP,
	TPS_PORTINFO_DRP_UFP_DRD,
	TPS_PORTINFO_DRP_DFP,
	TPS_PORTINFO_DRP_DFP_DRD,
	TPS_PORTINFO_SOURCE,
पूर्ण;

/* TPS_REG_RX_IDENTITY_SOP */
काष्ठा tps6598x_rx_identity_reg अणु
	u8 status;
	काष्ठा usb_pd_identity identity;
पूर्ण __packed;

/* Standard Task वापस codes */
#घोषणा TPS_TASK_TIMEOUT		1
#घोषणा TPS_TASK_REJECTED		3

क्रमागत अणु
	TPS_MODE_APP,
	TPS_MODE_BOOT,
	TPS_MODE_BIST,
	TPS_MODE_DISC,
पूर्ण;

अटल स्थिर अक्षर *स्थिर modes[] = अणु
	[TPS_MODE_APP]	= "APP ",
	[TPS_MODE_BOOT]	= "BOOT",
	[TPS_MODE_BIST]	= "BIST",
	[TPS_MODE_DISC]	= "DISC",
पूर्ण;

/* Unrecognized commands will be replaced with "!CMD" */
#घोषणा INVALID_CMD(_cmd_)		(_cmd_ == 0x444d4321)

काष्ठा tps6598x अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा mutex lock; /* device lock */
	u8 i2c_protocol:1;

	काष्ठा typec_port *port;
	काष्ठा typec_partner *partner;
	काष्ठा usb_pd_identity partner_identity;
	काष्ठा usb_role_चयन *role_sw;
	काष्ठा typec_capability typec_cap;

	काष्ठा घातer_supply *psy;
	काष्ठा घातer_supply_desc psy_desc;
	क्रमागत घातer_supply_usb_type usb_type;
पूर्ण;

अटल क्रमागत घातer_supply_property tps6598x_psy_props[] = अणु
	POWER_SUPPLY_PROP_USB_TYPE,
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल क्रमागत घातer_supply_usb_type tps6598x_psy_usb_types[] = अणु
	POWER_SUPPLY_USB_TYPE_C,
	POWER_SUPPLY_USB_TYPE_PD,
पूर्ण;

अटल स्थिर अक्षर *tps6598x_psy_name_prefix = "tps6598x-source-psy-";

/*
 * Max data bytes क्रम Data1, Data2, and other रेजिस्टरs. See ch 1.3.2:
 * https://www.ti.com/lit/ug/slvuan1a/slvuan1a.pdf
 */
#घोषणा TPS_MAX_LEN	64

अटल पूर्णांक
tps6598x_block_पढ़ो(काष्ठा tps6598x *tps, u8 reg, व्योम *val, माप_प्रकार len)
अणु
	u8 data[TPS_MAX_LEN + 1];
	पूर्णांक ret;

	अगर (WARN_ON(len + 1 > माप(data)))
		वापस -EINVAL;

	अगर (!tps->i2c_protocol)
		वापस regmap_raw_पढ़ो(tps->regmap, reg, val, len);

	ret = regmap_raw_पढ़ो(tps->regmap, reg, data, माप(data));
	अगर (ret)
		वापस ret;

	अगर (data[0] < len)
		वापस -EIO;

	स_नकल(val, &data[1], len);
	वापस 0;
पूर्ण

अटल पूर्णांक tps6598x_block_ग_लिखो(काष्ठा tps6598x *tps, u8 reg,
				स्थिर व्योम *val, माप_प्रकार len)
अणु
	u8 data[TPS_MAX_LEN + 1];

	अगर (!tps->i2c_protocol)
		वापस regmap_raw_ग_लिखो(tps->regmap, reg, val, len);

	data[0] = len;
	स_नकल(&data[1], val, len);

	वापस regmap_raw_ग_लिखो(tps->regmap, reg, data, माप(data));
पूर्ण

अटल अंतरभूत पूर्णांक tps6598x_पढ़ो16(काष्ठा tps6598x *tps, u8 reg, u16 *val)
अणु
	वापस tps6598x_block_पढ़ो(tps, reg, val, माप(u16));
पूर्ण

अटल अंतरभूत पूर्णांक tps6598x_पढ़ो32(काष्ठा tps6598x *tps, u8 reg, u32 *val)
अणु
	वापस tps6598x_block_पढ़ो(tps, reg, val, माप(u32));
पूर्ण

अटल अंतरभूत पूर्णांक tps6598x_पढ़ो64(काष्ठा tps6598x *tps, u8 reg, u64 *val)
अणु
	वापस tps6598x_block_पढ़ो(tps, reg, val, माप(u64));
पूर्ण

अटल अंतरभूत पूर्णांक tps6598x_ग_लिखो16(काष्ठा tps6598x *tps, u8 reg, u16 val)
अणु
	वापस tps6598x_block_ग_लिखो(tps, reg, &val, माप(u16));
पूर्ण

अटल अंतरभूत पूर्णांक tps6598x_ग_लिखो32(काष्ठा tps6598x *tps, u8 reg, u32 val)
अणु
	वापस tps6598x_block_ग_लिखो(tps, reg, &val, माप(u32));
पूर्ण

अटल अंतरभूत पूर्णांक tps6598x_ग_लिखो64(काष्ठा tps6598x *tps, u8 reg, u64 val)
अणु
	वापस tps6598x_block_ग_लिखो(tps, reg, &val, माप(u64));
पूर्ण

अटल अंतरभूत पूर्णांक
tps6598x_ग_लिखो_4cc(काष्ठा tps6598x *tps, u8 reg, स्थिर अक्षर *val)
अणु
	वापस tps6598x_block_ग_लिखो(tps, reg, val, 4);
पूर्ण

अटल पूर्णांक tps6598x_पढ़ो_partner_identity(काष्ठा tps6598x *tps)
अणु
	काष्ठा tps6598x_rx_identity_reg id;
	पूर्णांक ret;

	ret = tps6598x_block_पढ़ो(tps, TPS_REG_RX_IDENTITY_SOP,
				  &id, माप(id));
	अगर (ret)
		वापस ret;

	tps->partner_identity = id.identity;

	वापस 0;
पूर्ण

अटल व्योम tps6598x_set_data_role(काष्ठा tps6598x *tps,
				   क्रमागत typec_data_role role, bool connected)
अणु
	क्रमागत usb_role role_val;

	अगर (role == TYPEC_HOST)
		role_val = USB_ROLE_HOST;
	अन्यथा
		role_val = USB_ROLE_DEVICE;

	अगर (!connected)
		role_val = USB_ROLE_NONE;

	usb_role_चयन_set_role(tps->role_sw, role_val);
	typec_set_data_role(tps->port, role);
पूर्ण

अटल पूर्णांक tps6598x_connect(काष्ठा tps6598x *tps, u32 status)
अणु
	काष्ठा typec_partner_desc desc;
	क्रमागत typec_pwr_opmode mode;
	u16 pwr_status;
	पूर्णांक ret;

	अगर (tps->partner)
		वापस 0;

	ret = tps6598x_पढ़ो16(tps, TPS_REG_POWER_STATUS, &pwr_status);
	अगर (ret < 0)
		वापस ret;

	mode = TPS_POWER_STATUS_PWROPMODE(pwr_status);

	desc.usb_pd = mode == TYPEC_PWR_MODE_PD;
	desc.accessory = TYPEC_ACCESSORY_NONE; /* XXX: handle accessories */
	desc.identity = शून्य;

	अगर (desc.usb_pd) अणु
		ret = tps6598x_पढ़ो_partner_identity(tps);
		अगर (ret)
			वापस ret;
		desc.identity = &tps->partner_identity;
	पूर्ण

	typec_set_pwr_opmode(tps->port, mode);
	typec_set_pwr_role(tps->port, TPS_STATUS_TO_TYPEC_PORTROLE(status));
	typec_set_vconn_role(tps->port, TPS_STATUS_TO_TYPEC_VCONN(status));
	tps6598x_set_data_role(tps, TPS_STATUS_TO_TYPEC_DATAROLE(status), true);

	tps->partner = typec_रेजिस्टर_partner(tps->port, &desc);
	अगर (IS_ERR(tps->partner))
		वापस PTR_ERR(tps->partner);

	अगर (desc.identity)
		typec_partner_set_identity(tps->partner);

	घातer_supply_changed(tps->psy);

	वापस 0;
पूर्ण

अटल व्योम tps6598x_disconnect(काष्ठा tps6598x *tps, u32 status)
अणु
	अगर (!IS_ERR(tps->partner))
		typec_unरेजिस्टर_partner(tps->partner);
	tps->partner = शून्य;
	typec_set_pwr_opmode(tps->port, TYPEC_PWR_MODE_USB);
	typec_set_pwr_role(tps->port, TPS_STATUS_TO_TYPEC_PORTROLE(status));
	typec_set_vconn_role(tps->port, TPS_STATUS_TO_TYPEC_VCONN(status));
	tps6598x_set_data_role(tps, TPS_STATUS_TO_TYPEC_DATAROLE(status), false);

	घातer_supply_changed(tps->psy);
पूर्ण

अटल पूर्णांक tps6598x_exec_cmd(काष्ठा tps6598x *tps, स्थिर अक्षर *cmd,
			     माप_प्रकार in_len, u8 *in_data,
			     माप_प्रकार out_len, u8 *out_data)
अणु
	अचिन्हित दीर्घ समयout;
	u32 val;
	पूर्णांक ret;

	ret = tps6598x_पढ़ो32(tps, TPS_REG_CMD1, &val);
	अगर (ret)
		वापस ret;
	अगर (val && !INVALID_CMD(val))
		वापस -EBUSY;

	अगर (in_len) अणु
		ret = tps6598x_block_ग_लिखो(tps, TPS_REG_DATA1,
					   in_data, in_len);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = tps6598x_ग_लिखो_4cc(tps, TPS_REG_CMD1, cmd);
	अगर (ret < 0)
		वापस ret;

	/* XXX: Using 1s क्रम now, but it may not be enough क्रम every command. */
	समयout = jअगरfies + msecs_to_jअगरfies(1000);

	करो अणु
		ret = tps6598x_पढ़ो32(tps, TPS_REG_CMD1, &val);
		अगर (ret)
			वापस ret;
		अगर (INVALID_CMD(val))
			वापस -EINVAL;

		अगर (समय_is_beक्रमe_jअगरfies(समयout))
			वापस -ETIMEDOUT;
	पूर्ण जबतक (val);

	अगर (out_len) अणु
		ret = tps6598x_block_पढ़ो(tps, TPS_REG_DATA1,
					  out_data, out_len);
		अगर (ret)
			वापस ret;
		val = out_data[0];
	पूर्ण अन्यथा अणु
		ret = tps6598x_block_पढ़ो(tps, TPS_REG_DATA1, &val, माप(u8));
		अगर (ret)
			वापस ret;
	पूर्ण

	चयन (val) अणु
	हाल TPS_TASK_TIMEOUT:
		वापस -ETIMEDOUT;
	हाल TPS_TASK_REJECTED:
		वापस -EPERM;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tps6598x_dr_set(काष्ठा typec_port *port, क्रमागत typec_data_role role)
अणु
	स्थिर अक्षर *cmd = (role == TYPEC_DEVICE) ? "SWUF" : "SWDF";
	काष्ठा tps6598x *tps = typec_get_drvdata(port);
	u32 status;
	पूर्णांक ret;

	mutex_lock(&tps->lock);

	ret = tps6598x_exec_cmd(tps, cmd, 0, शून्य, 0, शून्य);
	अगर (ret)
		जाओ out_unlock;

	ret = tps6598x_पढ़ो32(tps, TPS_REG_STATUS, &status);
	अगर (ret)
		जाओ out_unlock;

	अगर (role != TPS_STATUS_TO_TYPEC_DATAROLE(status)) अणु
		ret = -EPROTO;
		जाओ out_unlock;
	पूर्ण

	tps6598x_set_data_role(tps, role, true);

out_unlock:
	mutex_unlock(&tps->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tps6598x_pr_set(काष्ठा typec_port *port, क्रमागत typec_role role)
अणु
	स्थिर अक्षर *cmd = (role == TYPEC_SINK) ? "SWSk" : "SWSr";
	काष्ठा tps6598x *tps = typec_get_drvdata(port);
	u32 status;
	पूर्णांक ret;

	mutex_lock(&tps->lock);

	ret = tps6598x_exec_cmd(tps, cmd, 0, शून्य, 0, शून्य);
	अगर (ret)
		जाओ out_unlock;

	ret = tps6598x_पढ़ो32(tps, TPS_REG_STATUS, &status);
	अगर (ret)
		जाओ out_unlock;

	अगर (role != TPS_STATUS_TO_TYPEC_PORTROLE(status)) अणु
		ret = -EPROTO;
		जाओ out_unlock;
	पूर्ण

	typec_set_pwr_role(tps->port, role);

out_unlock:
	mutex_unlock(&tps->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा typec_operations tps6598x_ops = अणु
	.dr_set = tps6598x_dr_set,
	.pr_set = tps6598x_pr_set,
पूर्ण;

अटल irqवापस_t tps6598x_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tps6598x *tps = data;
	u64 event1;
	u64 event2;
	u32 status, data_status;
	u16 pwr_status;
	पूर्णांक ret;

	mutex_lock(&tps->lock);

	ret = tps6598x_पढ़ो64(tps, TPS_REG_INT_EVENT1, &event1);
	ret |= tps6598x_पढ़ो64(tps, TPS_REG_INT_EVENT2, &event2);
	अगर (ret) अणु
		dev_err(tps->dev, "%s: failed to read events\n", __func__);
		जाओ err_unlock;
	पूर्ण
	trace_tps6598x_irq(event1, event2);

	ret = tps6598x_पढ़ो32(tps, TPS_REG_STATUS, &status);
	अगर (ret) अणु
		dev_err(tps->dev, "%s: failed to read status\n", __func__);
		जाओ err_clear_पूर्णांकs;
	पूर्ण
	trace_tps6598x_status(status);

	अगर ((event1 | event2) & TPS_REG_INT_POWER_STATUS_UPDATE) अणु
		ret = tps6598x_पढ़ो16(tps, TPS_REG_POWER_STATUS, &pwr_status);
		अगर (ret < 0) अणु
			dev_err(tps->dev, "failed to read power status: %d\n", ret);
			जाओ err_clear_पूर्णांकs;
		पूर्ण
		trace_tps6598x_घातer_status(pwr_status);
	पूर्ण

	अगर ((event1 | event2) & TPS_REG_INT_DATA_STATUS_UPDATE) अणु
		ret = tps6598x_पढ़ो32(tps, TPS_REG_DATA_STATUS, &data_status);
		अगर (ret < 0) अणु
			dev_err(tps->dev, "failed to read data status: %d\n", ret);
			जाओ err_clear_पूर्णांकs;
		पूर्ण
		trace_tps6598x_data_status(data_status);
	पूर्ण

	/* Handle plug insert or removal */
	अगर ((event1 | event2) & TPS_REG_INT_PLUG_EVENT) अणु
		अगर (status & TPS_STATUS_PLUG_PRESENT) अणु
			ret = tps6598x_connect(tps, status);
			अगर (ret)
				dev_err(tps->dev,
					"failed to register partner\n");
		पूर्ण अन्यथा अणु
			tps6598x_disconnect(tps, status);
		पूर्ण
	पूर्ण

err_clear_पूर्णांकs:
	tps6598x_ग_लिखो64(tps, TPS_REG_INT_CLEAR1, event1);
	tps6598x_ग_लिखो64(tps, TPS_REG_INT_CLEAR2, event2);

err_unlock:
	mutex_unlock(&tps->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tps6598x_check_mode(काष्ठा tps6598x *tps)
अणु
	अक्षर mode[5] = अणु पूर्ण;
	पूर्णांक ret;

	ret = tps6598x_पढ़ो32(tps, TPS_REG_MODE, (व्योम *)mode);
	अगर (ret)
		वापस ret;

	चयन (match_string(modes, ARRAY_SIZE(modes), mode)) अणु
	हाल TPS_MODE_APP:
		वापस 0;
	हाल TPS_MODE_BOOT:
		dev_warn(tps->dev, "dead-battery condition\n");
		वापस 0;
	हाल TPS_MODE_BIST:
	हाल TPS_MODE_DISC:
	शेष:
		dev_err(tps->dev, "controller in unsupported mode \"%s\"\n",
			mode);
		अवरोध;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा regmap_config tps6598x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x7F,
पूर्ण;

अटल पूर्णांक tps6598x_psy_get_online(काष्ठा tps6598x *tps,
				   जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret;
	u16 pwr_status;

	ret = tps6598x_पढ़ो16(tps, TPS_REG_POWER_STATUS, &pwr_status);
	अगर (ret < 0)
		वापस ret;

	अगर (TPS_POWER_STATUS_CONNECTION(pwr_status) &&
	    TPS_POWER_STATUS_SOURCESINK(pwr_status)) अणु
		val->पूर्णांकval = 1;
	पूर्ण अन्यथा अणु
		val->पूर्णांकval = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tps6598x_psy_get_prop(काष्ठा घातer_supply *psy,
				 क्रमागत घातer_supply_property psp,
				 जोड़ घातer_supply_propval *val)
अणु
	काष्ठा tps6598x *tps = घातer_supply_get_drvdata(psy);
	u16 pwr_status;
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_USB_TYPE:
		ret = tps6598x_पढ़ो16(tps, TPS_REG_POWER_STATUS, &pwr_status);
		अगर (ret < 0)
			वापस ret;
		अगर (TPS_POWER_STATUS_PWROPMODE(pwr_status) == TYPEC_PWR_MODE_PD)
			val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_PD;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_C;
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = tps6598x_psy_get_online(tps, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक devm_tps6598_psy_रेजिस्टर(काष्ठा tps6598x *tps)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	स्थिर अक्षर *port_dev_name = dev_name(tps->dev);
	अक्षर *psy_name;

	psy_cfg.drv_data = tps;
	psy_cfg.fwnode = dev_fwnode(tps->dev);

	psy_name = devm_kaप्र_लिखो(tps->dev, GFP_KERNEL, "%s%s", tps6598x_psy_name_prefix,
				  port_dev_name);
	अगर (!psy_name)
		वापस -ENOMEM;

	tps->psy_desc.name = psy_name;
	tps->psy_desc.type = POWER_SUPPLY_TYPE_USB;
	tps->psy_desc.usb_types = tps6598x_psy_usb_types;
	tps->psy_desc.num_usb_types = ARRAY_SIZE(tps6598x_psy_usb_types);
	tps->psy_desc.properties = tps6598x_psy_props;
	tps->psy_desc.num_properties = ARRAY_SIZE(tps6598x_psy_props);
	tps->psy_desc.get_property = tps6598x_psy_get_prop;

	tps->usb_type = POWER_SUPPLY_USB_TYPE_C;

	tps->psy = devm_घातer_supply_रेजिस्टर(tps->dev, &tps->psy_desc,
					       &psy_cfg);
	वापस PTR_ERR_OR_ZERO(tps->psy);
पूर्ण

अटल पूर्णांक tps6598x_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा typec_capability typec_cap = अणु पूर्ण;
	काष्ठा tps6598x *tps;
	काष्ठा fwnode_handle *fwnode;
	u32 status;
	u32 conf;
	u32 vid;
	पूर्णांक ret;

	tps = devm_kzalloc(&client->dev, माप(*tps), GFP_KERNEL);
	अगर (!tps)
		वापस -ENOMEM;

	mutex_init(&tps->lock);
	tps->dev = &client->dev;

	tps->regmap = devm_regmap_init_i2c(client, &tps6598x_regmap_config);
	अगर (IS_ERR(tps->regmap))
		वापस PTR_ERR(tps->regmap);

	ret = tps6598x_पढ़ो32(tps, TPS_REG_VID, &vid);
	अगर (ret < 0 || !vid)
		वापस -ENODEV;

	/*
	 * Checking can the adapter handle SMBus protocol. If it can not, the
	 * driver needs to take care of block पढ़ोs separately.
	 *
	 * FIXME: Testing with I2C_FUNC_I2C. regmap-i2c uses I2C protocol
	 * unconditionally अगर the adapter has I2C_FUNC_I2C set.
	 */
	अगर (i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		tps->i2c_protocol = true;

	/* Make sure the controller has application firmware running */
	ret = tps6598x_check_mode(tps);
	अगर (ret)
		वापस ret;

	ret = tps6598x_पढ़ो32(tps, TPS_REG_STATUS, &status);
	अगर (ret < 0)
		वापस ret;
	trace_tps6598x_status(status);

	ret = tps6598x_पढ़ो32(tps, TPS_REG_SYSTEM_CONF, &conf);
	अगर (ret < 0)
		वापस ret;

	fwnode = device_get_named_child_node(&client->dev, "connector");
	अगर (!fwnode)
		वापस -ENODEV;

	tps->role_sw = fwnode_usb_role_चयन_get(fwnode);
	अगर (IS_ERR(tps->role_sw)) अणु
		ret = PTR_ERR(tps->role_sw);
		जाओ err_fwnode_put;
	पूर्ण

	typec_cap.revision = USB_TYPEC_REV_1_2;
	typec_cap.pd_revision = 0x200;
	typec_cap.prefer_role = TYPEC_NO_PREFERRED_ROLE;
	typec_cap.driver_data = tps;
	typec_cap.ops = &tps6598x_ops;
	typec_cap.fwnode = fwnode;

	चयन (TPS_SYSCONF_PORTINFO(conf)) अणु
	हाल TPS_PORTINFO_SINK_ACCESSORY:
	हाल TPS_PORTINFO_SINK:
		typec_cap.type = TYPEC_PORT_SNK;
		typec_cap.data = TYPEC_PORT_UFP;
		अवरोध;
	हाल TPS_PORTINFO_DRP_UFP_DRD:
	हाल TPS_PORTINFO_DRP_DFP_DRD:
		typec_cap.type = TYPEC_PORT_DRP;
		typec_cap.data = TYPEC_PORT_DRD;
		अवरोध;
	हाल TPS_PORTINFO_DRP_UFP:
		typec_cap.type = TYPEC_PORT_DRP;
		typec_cap.data = TYPEC_PORT_UFP;
		अवरोध;
	हाल TPS_PORTINFO_DRP_DFP:
		typec_cap.type = TYPEC_PORT_DRP;
		typec_cap.data = TYPEC_PORT_DFP;
		अवरोध;
	हाल TPS_PORTINFO_SOURCE:
		typec_cap.type = TYPEC_PORT_SRC;
		typec_cap.data = TYPEC_PORT_DFP;
		अवरोध;
	शेष:
		ret = -ENODEV;
		जाओ err_role_put;
	पूर्ण

	ret = devm_tps6598_psy_रेजिस्टर(tps);
	अगर (ret)
		वापस ret;

	tps->port = typec_रेजिस्टर_port(&client->dev, &typec_cap);
	अगर (IS_ERR(tps->port)) अणु
		ret = PTR_ERR(tps->port);
		जाओ err_role_put;
	पूर्ण
	fwnode_handle_put(fwnode);

	अगर (status & TPS_STATUS_PLUG_PRESENT) अणु
		ret = tps6598x_connect(tps, status);
		अगर (ret)
			dev_err(&client->dev, "failed to register partner\n");
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
					tps6598x_पूर्णांकerrupt,
					IRQF_SHARED | IRQF_ONESHOT,
					dev_name(&client->dev), tps);
	अगर (ret) अणु
		tps6598x_disconnect(tps, 0);
		typec_unरेजिस्टर_port(tps->port);
		जाओ err_role_put;
	पूर्ण

	i2c_set_clientdata(client, tps);

	वापस 0;

err_role_put:
	usb_role_चयन_put(tps->role_sw);
err_fwnode_put:
	fwnode_handle_put(fwnode);

	वापस ret;
पूर्ण

अटल पूर्णांक tps6598x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tps6598x *tps = i2c_get_clientdata(client);

	tps6598x_disconnect(tps, 0);
	typec_unरेजिस्टर_port(tps->port);
	usb_role_चयन_put(tps->role_sw);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tps6598x_of_match[] = अणु
	अणु .compatible = "ti,tps6598x", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tps6598x_of_match);

अटल स्थिर काष्ठा i2c_device_id tps6598x_id[] = अणु
	अणु "tps6598x" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tps6598x_id);

अटल काष्ठा i2c_driver tps6598x_i2c_driver = अणु
	.driver = अणु
		.name = "tps6598x",
		.of_match_table = tps6598x_of_match,
	पूर्ण,
	.probe_new = tps6598x_probe,
	.हटाओ = tps6598x_हटाओ,
	.id_table = tps6598x_id,
पूर्ण;
module_i2c_driver(tps6598x_i2c_driver);

MODULE_AUTHOR("Heikki Krogerus <heikki.krogerus@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI TPS6598x USB Power Delivery Controller Driver");
