<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Typec-C DisplayPort Alternate Mode driver
 *
 * Copyright (C) 2018 Intel Corporation
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 *
 * DisplayPort is trademark of VESA (www.vesa.org)
 */

#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/pd_vकरो.h>
#समावेश <linux/usb/typec_dp.h>
#समावेश "displayport.h"

#घोषणा DP_HEADER(_dp, ver, cmd)	(VDO((_dp)->alt->svid, 1, ver, cmd)	\
					 | VDO_OPOS(USB_TYPEC_DP_MODE))

क्रमागत अणु
	DP_CONF_USB,
	DP_CONF_DFP_D,
	DP_CONF_UFP_D,
	DP_CONF_DUAL_D,
पूर्ण;

/* Pin assignments that use USB3.1 Gen2 संकेतing to carry DP protocol */
#घोषणा DP_PIN_ASSIGN_GEN2_BR_MASK	(BIT(DP_PIN_ASSIGN_A) | \
					 BIT(DP_PIN_ASSIGN_B))

/* Pin assignments that use DP v1.3 संकेतing to carry DP protocol */
#घोषणा DP_PIN_ASSIGN_DP_BR_MASK	(BIT(DP_PIN_ASSIGN_C) | \
					 BIT(DP_PIN_ASSIGN_D) | \
					 BIT(DP_PIN_ASSIGN_E) | \
					 BIT(DP_PIN_ASSIGN_F))

/* DP only pin assignments */
#घोषणा DP_PIN_ASSIGN_DP_ONLY_MASK	(BIT(DP_PIN_ASSIGN_A) | \
					 BIT(DP_PIN_ASSIGN_C) | \
					 BIT(DP_PIN_ASSIGN_E))

/* Pin assignments where one channel is क्रम USB */
#घोषणा DP_PIN_ASSIGN_MULTI_FUNC_MASK	(BIT(DP_PIN_ASSIGN_B) | \
					 BIT(DP_PIN_ASSIGN_D) | \
					 BIT(DP_PIN_ASSIGN_F))

क्रमागत dp_state अणु
	DP_STATE_IDLE,
	DP_STATE_ENTER,
	DP_STATE_UPDATE,
	DP_STATE_CONFIGURE,
	DP_STATE_EXIT,
पूर्ण;

काष्ठा dp_alपंचांगode अणु
	काष्ठा typec_displayport_data data;

	क्रमागत dp_state state;

	काष्ठा mutex lock; /* device lock */
	काष्ठा work_काष्ठा work;
	काष्ठा typec_alपंचांगode *alt;
	स्थिर काष्ठा typec_alपंचांगode *port;
पूर्ण;

अटल पूर्णांक dp_alपंचांगode_notअगरy(काष्ठा dp_alपंचांगode *dp)
अणु
	u8 state = get_count_order(DP_CONF_GET_PIN_ASSIGN(dp->data.conf));

	वापस typec_alपंचांगode_notअगरy(dp->alt, TYPEC_MODAL_STATE(state),
				   &dp->data);
पूर्ण

अटल पूर्णांक dp_alपंचांगode_configure(काष्ठा dp_alपंचांगode *dp, u8 con)
अणु
	u32 conf = DP_CONF_SIGNALING_DP; /* Only DP संकेतing supported */
	u8 pin_assign = 0;

	चयन (con) अणु
	हाल DP_STATUS_CON_DISABLED:
		वापस 0;
	हाल DP_STATUS_CON_DFP_D:
		conf |= DP_CONF_UFP_U_AS_DFP_D;
		pin_assign = DP_CAP_UFP_D_PIN_ASSIGN(dp->alt->vकरो) &
			     DP_CAP_DFP_D_PIN_ASSIGN(dp->port->vकरो);
		अवरोध;
	हाल DP_STATUS_CON_UFP_D:
	हाल DP_STATUS_CON_BOTH: /* NOTE: First acting as DP source */
		conf |= DP_CONF_UFP_U_AS_UFP_D;
		pin_assign = DP_CAP_DFP_D_PIN_ASSIGN(dp->alt->vकरो) &
			     DP_CAP_UFP_D_PIN_ASSIGN(dp->port->vकरो);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Determining the initial pin assignment. */
	अगर (!DP_CONF_GET_PIN_ASSIGN(dp->data.conf)) अणु
		/* Is USB together with DP preferred */
		अगर (dp->data.status & DP_STATUS_PREFER_MULTI_FUNC &&
		    pin_assign & DP_PIN_ASSIGN_MULTI_FUNC_MASK)
			pin_assign &= DP_PIN_ASSIGN_MULTI_FUNC_MASK;
		अन्यथा अगर (pin_assign & DP_PIN_ASSIGN_DP_ONLY_MASK)
			pin_assign &= DP_PIN_ASSIGN_DP_ONLY_MASK;

		अगर (!pin_assign)
			वापस -EINVAL;

		conf |= DP_CONF_SET_PIN_ASSIGN(pin_assign);
	पूर्ण

	dp->data.conf = conf;

	वापस 0;
पूर्ण

अटल पूर्णांक dp_alपंचांगode_status_update(काष्ठा dp_alपंचांगode *dp)
अणु
	bool configured = !!DP_CONF_GET_PIN_ASSIGN(dp->data.conf);
	u8 con = DP_STATUS_CONNECTION(dp->data.status);
	पूर्णांक ret = 0;

	अगर (configured && (dp->data.status & DP_STATUS_SWITCH_TO_USB)) अणु
		dp->data.conf = 0;
		dp->state = DP_STATE_CONFIGURE;
	पूर्ण अन्यथा अगर (dp->data.status & DP_STATUS_EXIT_DP_MODE) अणु
		dp->state = DP_STATE_EXIT;
	पूर्ण अन्यथा अगर (!(con & DP_CONF_CURRENTLY(dp->data.conf))) अणु
		ret = dp_alपंचांगode_configure(dp, con);
		अगर (!ret)
			dp->state = DP_STATE_CONFIGURE;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dp_alपंचांगode_configured(काष्ठा dp_alपंचांगode *dp)
अणु
	पूर्णांक ret;

	sysfs_notअगरy(&dp->alt->dev.kobj, "displayport", "configuration");

	अगर (!dp->data.conf)
		वापस typec_alपंचांगode_notअगरy(dp->alt, TYPEC_STATE_USB,
					    &dp->data);

	ret = dp_alपंचांगode_notअगरy(dp);
	अगर (ret)
		वापस ret;

	sysfs_notअगरy(&dp->alt->dev.kobj, "displayport", "pin_assignment");

	वापस 0;
पूर्ण

अटल पूर्णांक dp_alपंचांगode_configure_vdm(काष्ठा dp_alपंचांगode *dp, u32 conf)
अणु
	पूर्णांक svdm_version = typec_alपंचांगode_get_svdm_version(dp->alt);
	u32 header;
	पूर्णांक ret;

	अगर (svdm_version < 0)
		वापस svdm_version;

	header = DP_HEADER(dp, svdm_version, DP_CMD_CONFIGURE);
	ret = typec_alपंचांगode_notअगरy(dp->alt, TYPEC_STATE_SAFE, &dp->data);
	अगर (ret) अणु
		dev_err(&dp->alt->dev,
			"unable to put to connector to safe mode\n");
		वापस ret;
	पूर्ण

	ret = typec_alपंचांगode_vdm(dp->alt, header, &conf, 2);
	अगर (ret) अणु
		अगर (DP_CONF_GET_PIN_ASSIGN(dp->data.conf))
			dp_alपंचांगode_notअगरy(dp);
		अन्यथा
			typec_alपंचांगode_notअगरy(dp->alt, TYPEC_STATE_USB,
					     &dp->data);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dp_alपंचांगode_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dp_alपंचांगode *dp = container_of(work, काष्ठा dp_alपंचांगode, work);
	पूर्णांक svdm_version;
	u32 header;
	u32 vकरो;
	पूर्णांक ret;

	mutex_lock(&dp->lock);

	चयन (dp->state) अणु
	हाल DP_STATE_ENTER:
		ret = typec_alपंचांगode_enter(dp->alt, शून्य);
		अगर (ret && ret != -EBUSY)
			dev_err(&dp->alt->dev, "failed to enter mode\n");
		अवरोध;
	हाल DP_STATE_UPDATE:
		svdm_version = typec_alपंचांगode_get_svdm_version(dp->alt);
		अगर (svdm_version < 0)
			अवरोध;
		header = DP_HEADER(dp, svdm_version, DP_CMD_STATUS_UPDATE);
		vकरो = 1;
		ret = typec_alपंचांगode_vdm(dp->alt, header, &vकरो, 2);
		अगर (ret)
			dev_err(&dp->alt->dev,
				"unable to send Status Update command (%d)\n",
				ret);
		अवरोध;
	हाल DP_STATE_CONFIGURE:
		ret = dp_alपंचांगode_configure_vdm(dp, dp->data.conf);
		अगर (ret)
			dev_err(&dp->alt->dev,
				"unable to send Configure command (%d)\n", ret);
		अवरोध;
	हाल DP_STATE_EXIT:
		अगर (typec_alपंचांगode_निकास(dp->alt))
			dev_err(&dp->alt->dev, "Exit Mode Failed!\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dp->state = DP_STATE_IDLE;

	mutex_unlock(&dp->lock);
पूर्ण

अटल व्योम dp_alपंचांगode_attention(काष्ठा typec_alपंचांगode *alt, स्थिर u32 vकरो)
अणु
	काष्ठा dp_alपंचांगode *dp = typec_alपंचांगode_get_drvdata(alt);
	u8 old_state;

	mutex_lock(&dp->lock);

	old_state = dp->state;
	dp->data.status = vकरो;

	अगर (old_state != DP_STATE_IDLE)
		dev_warn(&alt->dev, "ATTENTION while processing state %d\n",
			 old_state);

	अगर (dp_alपंचांगode_status_update(dp))
		dev_warn(&alt->dev, "%s: status update failed\n", __func__);

	अगर (dp_alपंचांगode_notअगरy(dp))
		dev_err(&alt->dev, "%s: notification failed\n", __func__);

	अगर (old_state == DP_STATE_IDLE && dp->state != DP_STATE_IDLE)
		schedule_work(&dp->work);

	mutex_unlock(&dp->lock);
पूर्ण

अटल पूर्णांक dp_alपंचांगode_vdm(काष्ठा typec_alपंचांगode *alt,
			  स्थिर u32 hdr, स्थिर u32 *vकरो, पूर्णांक count)
अणु
	काष्ठा dp_alपंचांगode *dp = typec_alपंचांगode_get_drvdata(alt);
	पूर्णांक cmd_type = PD_VDO_CMDT(hdr);
	पूर्णांक cmd = PD_VDO_CMD(hdr);
	पूर्णांक ret = 0;

	mutex_lock(&dp->lock);

	अगर (dp->state != DP_STATE_IDLE) अणु
		ret = -EBUSY;
		जाओ err_unlock;
	पूर्ण

	चयन (cmd_type) अणु
	हाल CMDT_RSP_ACK:
		चयन (cmd) अणु
		हाल CMD_ENTER_MODE:
			dp->state = DP_STATE_UPDATE;
			अवरोध;
		हाल CMD_EXIT_MODE:
			dp->data.status = 0;
			dp->data.conf = 0;
			अवरोध;
		हाल DP_CMD_STATUS_UPDATE:
			dp->data.status = *vकरो;
			ret = dp_alपंचांगode_status_update(dp);
			अवरोध;
		हाल DP_CMD_CONFIGURE:
			ret = dp_alपंचांगode_configured(dp);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CMDT_RSP_NAK:
		चयन (cmd) अणु
		हाल DP_CMD_CONFIGURE:
			dp->data.conf = 0;
			ret = dp_alपंचांगode_configured(dp);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (dp->state != DP_STATE_IDLE)
		schedule_work(&dp->work);

err_unlock:
	mutex_unlock(&dp->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dp_alपंचांगode_activate(काष्ठा typec_alपंचांगode *alt, पूर्णांक activate)
अणु
	वापस activate ? typec_alपंचांगode_enter(alt, शून्य) :
			  typec_alपंचांगode_निकास(alt);
पूर्ण

अटल स्थिर काष्ठा typec_alपंचांगode_ops dp_alपंचांगode_ops = अणु
	.attention = dp_alपंचांगode_attention,
	.vdm = dp_alपंचांगode_vdm,
	.activate = dp_alपंचांगode_activate,
पूर्ण;

अटल स्थिर अक्षर * स्थिर configurations[] = अणु
	[DP_CONF_USB]	= "USB",
	[DP_CONF_DFP_D]	= "source",
	[DP_CONF_UFP_D]	= "sink",
पूर्ण;

अटल sमाप_प्रकार
configuration_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा dp_alपंचांगode *dp = dev_get_drvdata(dev);
	u32 conf;
	u32 cap;
	पूर्णांक con;
	पूर्णांक ret = 0;

	con = sysfs_match_string(configurations, buf);
	अगर (con < 0)
		वापस con;

	mutex_lock(&dp->lock);

	अगर (dp->state != DP_STATE_IDLE) अणु
		ret = -EBUSY;
		जाओ err_unlock;
	पूर्ण

	cap = DP_CAP_CAPABILITY(dp->alt->vकरो);

	अगर ((con == DP_CONF_DFP_D && !(cap & DP_CAP_DFP_D)) ||
	    (con == DP_CONF_UFP_D && !(cap & DP_CAP_UFP_D))) अणु
		ret = -EINVAL;
		जाओ err_unlock;
	पूर्ण

	conf = dp->data.conf & ~DP_CONF_DUAL_D;
	conf |= con;

	अगर (dp->alt->active) अणु
		ret = dp_alपंचांगode_configure_vdm(dp, conf);
		अगर (ret)
			जाओ err_unlock;
	पूर्ण

	dp->data.conf = conf;

err_unlock:
	mutex_unlock(&dp->lock);

	वापस ret ? ret : size;
पूर्ण

अटल sमाप_प्रकार configuration_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dp_alपंचांगode *dp = dev_get_drvdata(dev);
	पूर्णांक len;
	u8 cap;
	u8 cur;
	पूर्णांक i;

	mutex_lock(&dp->lock);

	cap = DP_CAP_CAPABILITY(dp->alt->vकरो);
	cur = DP_CONF_CURRENTLY(dp->data.conf);

	len = प्र_लिखो(buf, "%s ", cur ? "USB" : "[USB]");

	क्रम (i = 1; i < ARRAY_SIZE(configurations); i++) अणु
		अगर (i == cur)
			len += प्र_लिखो(buf + len, "[%s] ", configurations[i]);
		अन्यथा अगर ((i == DP_CONF_DFP_D && cap & DP_CAP_DFP_D) ||
			 (i == DP_CONF_UFP_D && cap & DP_CAP_UFP_D))
			len += प्र_लिखो(buf + len, "%s ", configurations[i]);
	पूर्ण

	mutex_unlock(&dp->lock);

	buf[len - 1] = '\n';
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(configuration);

अटल स्थिर अक्षर * स्थिर pin_assignments[] = अणु
	[DP_PIN_ASSIGN_A] = "A",
	[DP_PIN_ASSIGN_B] = "B",
	[DP_PIN_ASSIGN_C] = "C",
	[DP_PIN_ASSIGN_D] = "D",
	[DP_PIN_ASSIGN_E] = "E",
	[DP_PIN_ASSIGN_F] = "F",
पूर्ण;

अटल sमाप_प्रकार
pin_assignment_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा dp_alपंचांगode *dp = dev_get_drvdata(dev);
	u8 assignments;
	u32 conf;
	पूर्णांक ret;

	ret = sysfs_match_string(pin_assignments, buf);
	अगर (ret < 0)
		वापस ret;

	conf = DP_CONF_SET_PIN_ASSIGN(BIT(ret));
	ret = 0;

	mutex_lock(&dp->lock);

	अगर (conf & dp->data.conf)
		जाओ out_unlock;

	अगर (dp->state != DP_STATE_IDLE) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	अगर (DP_CONF_CURRENTLY(dp->data.conf) == DP_CONF_DFP_D)
		assignments = DP_CAP_UFP_D_PIN_ASSIGN(dp->alt->vकरो);
	अन्यथा
		assignments = DP_CAP_DFP_D_PIN_ASSIGN(dp->alt->vकरो);

	अगर (!(DP_CONF_GET_PIN_ASSIGN(conf) & assignments)) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	conf |= dp->data.conf & ~DP_CONF_PIN_ASSIGNEMENT_MASK;

	/* Only send Configure command अगर a configuration has been set */
	अगर (dp->alt->active && DP_CONF_CURRENTLY(dp->data.conf)) अणु
		ret = dp_alपंचांगode_configure_vdm(dp, conf);
		अगर (ret)
			जाओ out_unlock;
	पूर्ण

	dp->data.conf = conf;

out_unlock:
	mutex_unlock(&dp->lock);

	वापस ret ? ret : size;
पूर्ण

अटल sमाप_प्रकार pin_assignment_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dp_alपंचांगode *dp = dev_get_drvdata(dev);
	u8 assignments;
	पूर्णांक len = 0;
	u8 cur;
	पूर्णांक i;

	mutex_lock(&dp->lock);

	cur = get_count_order(DP_CONF_GET_PIN_ASSIGN(dp->data.conf));

	अगर (DP_CONF_CURRENTLY(dp->data.conf) == DP_CONF_DFP_D)
		assignments = DP_CAP_UFP_D_PIN_ASSIGN(dp->alt->vकरो);
	अन्यथा
		assignments = DP_CAP_DFP_D_PIN_ASSIGN(dp->alt->vकरो);

	क्रम (i = 0; assignments; assignments >>= 1, i++) अणु
		अगर (assignments & 1) अणु
			अगर (i == cur)
				len += प्र_लिखो(buf + len, "[%s] ",
					       pin_assignments[i]);
			अन्यथा
				len += प्र_लिखो(buf + len, "%s ",
					       pin_assignments[i]);
		पूर्ण
	पूर्ण

	mutex_unlock(&dp->lock);

	buf[len - 1] = '\n';
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(pin_assignment);

अटल काष्ठा attribute *dp_alपंचांगode_attrs[] = अणु
	&dev_attr_configuration.attr,
	&dev_attr_pin_assignment.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dp_alपंचांगode_group = अणु
	.name = "displayport",
	.attrs = dp_alपंचांगode_attrs,
पूर्ण;

पूर्णांक dp_alपंचांगode_probe(काष्ठा typec_alपंचांगode *alt)
अणु
	स्थिर काष्ठा typec_alपंचांगode *port = typec_alपंचांगode_get_partner(alt);
	काष्ठा dp_alपंचांगode *dp;
	पूर्णांक ret;

	/* FIXME: Port can only be DFP_U. */

	/* Make sure we have compatiple pin configurations */
	अगर (!(DP_CAP_DFP_D_PIN_ASSIGN(port->vकरो) &
	      DP_CAP_UFP_D_PIN_ASSIGN(alt->vकरो)) &&
	    !(DP_CAP_UFP_D_PIN_ASSIGN(port->vकरो) &
	      DP_CAP_DFP_D_PIN_ASSIGN(alt->vकरो)))
		वापस -ENODEV;

	ret = sysfs_create_group(&alt->dev.kobj, &dp_alपंचांगode_group);
	अगर (ret)
		वापस ret;

	dp = devm_kzalloc(&alt->dev, माप(*dp), GFP_KERNEL);
	अगर (!dp)
		वापस -ENOMEM;

	INIT_WORK(&dp->work, dp_alपंचांगode_work);
	mutex_init(&dp->lock);
	dp->port = port;
	dp->alt = alt;

	alt->desc = "DisplayPort";
	alt->ops = &dp_alपंचांगode_ops;

	typec_alपंचांगode_set_drvdata(alt, dp);

	dp->state = DP_STATE_ENTER;
	schedule_work(&dp->work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dp_alपंचांगode_probe);

व्योम dp_alपंचांगode_हटाओ(काष्ठा typec_alपंचांगode *alt)
अणु
	काष्ठा dp_alपंचांगode *dp = typec_alपंचांगode_get_drvdata(alt);

	sysfs_हटाओ_group(&alt->dev.kobj, &dp_alपंचांगode_group);
	cancel_work_sync(&dp->work);
पूर्ण
EXPORT_SYMBOL_GPL(dp_alपंचांगode_हटाओ);

अटल स्थिर काष्ठा typec_device_id dp_typec_id[] = अणु
	अणु USB_TYPEC_DP_SID, USB_TYPEC_DP_MODE पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(typec, dp_typec_id);

अटल काष्ठा typec_alपंचांगode_driver dp_alपंचांगode_driver = अणु
	.id_table = dp_typec_id,
	.probe = dp_alपंचांगode_probe,
	.हटाओ = dp_alपंचांगode_हटाओ,
	.driver = अणु
		.name = "typec_displayport",
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;
module_typec_alपंचांगode_driver(dp_alपंचांगode_driver);

MODULE_AUTHOR("Heikki Krogerus <heikki.krogerus@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DisplayPort Alternate Mode");
