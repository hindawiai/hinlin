<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2013
 *    Author(s): Eugene Crosser <eugene.crosser@ru.ibm.com>
 */

#समावेश <linux/slab.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश "qeth_core.h"
#समावेश "qeth_l2.h"

अटल sमाप_प्रकार qeth_bridge_port_role_state_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf,
				पूर्णांक show_state)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	क्रमागत qeth_sbp_states state = QETH_SBP_STATE_INACTIVE;
	पूर्णांक rc = 0;
	अक्षर *word;

	अगर (!qeth_bridgeport_allowed(card))
		वापस प्र_लिखो(buf, "n/a (VNIC characteristics)\n");

	mutex_lock(&card->sbp_lock);
	अगर (qeth_card_hw_is_reachable(card) &&
					card->options.sbp.supported_funcs)
		rc = qeth_bridgeport_query_ports(card,
			&card->options.sbp.role, &state);
	अगर (!rc) अणु
		अगर (show_state)
			चयन (state) अणु
			हाल QETH_SBP_STATE_INACTIVE:
				word = "inactive"; अवरोध;
			हाल QETH_SBP_STATE_STANDBY:
				word = "standby"; अवरोध;
			हाल QETH_SBP_STATE_ACTIVE:
				word = "active"; अवरोध;
			शेष:
				rc = -EIO;
			पूर्ण
		अन्यथा
			चयन (card->options.sbp.role) अणु
			हाल QETH_SBP_ROLE_NONE:
				word = "none"; अवरोध;
			हाल QETH_SBP_ROLE_PRIMARY:
				word = "primary"; अवरोध;
			हाल QETH_SBP_ROLE_SECONDARY:
				word = "secondary"; अवरोध;
			शेष:
				rc = -EIO;
			पूर्ण
		अगर (rc)
			QETH_CARD_TEXT_(card, 2, "SBP%02x:%02x",
				card->options.sbp.role, state);
		अन्यथा
			rc = प्र_लिखो(buf, "%s\n", word);
	पूर्ण
	mutex_unlock(&card->sbp_lock);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार qeth_bridge_port_role_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	अगर (!qeth_bridgeport_allowed(card))
		वापस प्र_लिखो(buf, "n/a (VNIC characteristics)\n");

	वापस qeth_bridge_port_role_state_show(dev, attr, buf, 0);
पूर्ण

अटल sमाप_प्रकार qeth_bridge_port_role_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	पूर्णांक rc = 0;
	क्रमागत qeth_sbp_roles role;

	अगर (sysfs_streq(buf, "primary"))
		role = QETH_SBP_ROLE_PRIMARY;
	अन्यथा अगर (sysfs_streq(buf, "secondary"))
		role = QETH_SBP_ROLE_SECONDARY;
	अन्यथा अगर (sysfs_streq(buf, "none"))
		role = QETH_SBP_ROLE_NONE;
	अन्यथा
		वापस -EINVAL;

	mutex_lock(&card->conf_mutex);
	mutex_lock(&card->sbp_lock);

	अगर (!qeth_bridgeport_allowed(card))
		rc = -EBUSY;
	अन्यथा अगर (card->options.sbp.reflect_promisc)
		/* Forbid direct manipulation */
		rc = -EPERM;
	अन्यथा अगर (qeth_card_hw_is_reachable(card)) अणु
		rc = qeth_bridgeport_setrole(card, role);
		अगर (!rc)
			card->options.sbp.role = role;
	पूर्ण अन्यथा
		card->options.sbp.role = role;

	mutex_unlock(&card->sbp_lock);
	mutex_unlock(&card->conf_mutex);

	वापस rc ? rc : count;
पूर्ण

अटल DEVICE_ATTR(bridge_role, 0644, qeth_bridge_port_role_show,
		   qeth_bridge_port_role_store);

अटल sमाप_प्रकार qeth_bridge_port_state_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	अगर (!qeth_bridgeport_allowed(card))
		वापस प्र_लिखो(buf, "n/a (VNIC characteristics)\n");

	वापस qeth_bridge_port_role_state_show(dev, attr, buf, 1);
पूर्ण

अटल DEVICE_ATTR(bridge_state, 0444, qeth_bridge_port_state_show,
		   शून्य);

अटल sमाप_प्रकार qeth_bridgeport_hostnotअगरication_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	पूर्णांक enabled;

	अगर (!qeth_bridgeport_allowed(card))
		वापस प्र_लिखो(buf, "n/a (VNIC characteristics)\n");

	enabled = card->options.sbp.hostnotअगरication;

	वापस प्र_लिखो(buf, "%d\n", enabled);
पूर्ण

अटल sमाप_प्रकार qeth_bridgeport_hostnotअगरication_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	bool enable;
	पूर्णांक rc;

	rc = kstrtobool(buf, &enable);
	अगर (rc)
		वापस rc;

	mutex_lock(&card->conf_mutex);
	mutex_lock(&card->sbp_lock);

	अगर (!qeth_bridgeport_allowed(card))
		rc = -EBUSY;
	अन्यथा अगर (qeth_card_hw_is_reachable(card)) अणु
		rc = qeth_bridgeport_an_set(card, enable);
		/* sbp_lock ensures ordering vs notअगरications-stopped events */
		अगर (!rc)
			card->options.sbp.hostnotअगरication = enable;
	पूर्ण अन्यथा
		card->options.sbp.hostnotअगरication = enable;

	mutex_unlock(&card->sbp_lock);
	mutex_unlock(&card->conf_mutex);

	वापस rc ? rc : count;
पूर्ण

अटल DEVICE_ATTR(bridge_hostnotअगरy, 0644,
			qeth_bridgeport_hostnotअगरication_show,
			qeth_bridgeport_hostnotअगरication_store);

अटल sमाप_प्रकार qeth_bridgeport_reflect_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	अक्षर *state;

	अगर (!qeth_bridgeport_allowed(card))
		वापस प्र_लिखो(buf, "n/a (VNIC characteristics)\n");

	अगर (card->options.sbp.reflect_promisc) अणु
		अगर (card->options.sbp.reflect_promisc_primary)
			state = "primary";
		अन्यथा
			state = "secondary";
	पूर्ण अन्यथा
		state = "none";

	वापस प्र_लिखो(buf, "%s\n", state);
पूर्ण

अटल sमाप_प्रकार qeth_bridgeport_reflect_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	पूर्णांक enable, primary;
	पूर्णांक rc = 0;

	अगर (sysfs_streq(buf, "none")) अणु
		enable = 0;
		primary = 0;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "primary")) अणु
		enable = 1;
		primary = 1;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "secondary")) अणु
		enable = 1;
		primary = 0;
	पूर्ण अन्यथा
		वापस -EINVAL;

	mutex_lock(&card->conf_mutex);
	mutex_lock(&card->sbp_lock);

	अगर (!qeth_bridgeport_allowed(card))
		rc = -EBUSY;
	अन्यथा अगर (card->options.sbp.role != QETH_SBP_ROLE_NONE)
		rc = -EPERM;
	अन्यथा अणु
		card->options.sbp.reflect_promisc = enable;
		card->options.sbp.reflect_promisc_primary = primary;
		rc = 0;
	पूर्ण

	mutex_unlock(&card->sbp_lock);
	mutex_unlock(&card->conf_mutex);

	वापस rc ? rc : count;
पूर्ण

अटल DEVICE_ATTR(bridge_reflect_promisc, 0644,
			qeth_bridgeport_reflect_show,
			qeth_bridgeport_reflect_store);

अटल काष्ठा attribute *qeth_l2_bridgeport_attrs[] = अणु
	&dev_attr_bridge_role.attr,
	&dev_attr_bridge_state.attr,
	&dev_attr_bridge_hostnotअगरy.attr,
	&dev_attr_bridge_reflect_promisc.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group qeth_l2_bridgeport_attr_group = अणु
	.attrs = qeth_l2_bridgeport_attrs,
पूर्ण;

/* VNIC CHARS support */

/* convert sysfs attr name to VNIC अक्षरacteristic */
अटल u32 qeth_l2_vnicc_sysfs_attr_to_अक्षर(स्थिर अक्षर *attr_name)
अणु
	अगर (sysfs_streq(attr_name, "flooding"))
		वापस QETH_VNICC_FLOODING;
	अन्यथा अगर (sysfs_streq(attr_name, "mcast_flooding"))
		वापस QETH_VNICC_MCAST_FLOODING;
	अन्यथा अगर (sysfs_streq(attr_name, "learning"))
		वापस QETH_VNICC_LEARNING;
	अन्यथा अगर (sysfs_streq(attr_name, "takeover_setvmac"))
		वापस QETH_VNICC_TAKEOVER_SETVMAC;
	अन्यथा अगर (sysfs_streq(attr_name, "takeover_learning"))
		वापस QETH_VNICC_TAKEOVER_LEARNING;
	अन्यथा अगर (sysfs_streq(attr_name, "bridge_invisible"))
		वापस QETH_VNICC_BRIDGE_INVISIBLE;
	अन्यथा अगर (sysfs_streq(attr_name, "rx_bcast"))
		वापस QETH_VNICC_RX_BCAST;

	वापस 0;
पूर्ण

/* get current समयout setting */
अटल sमाप_प्रकार qeth_vnicc_समयout_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	u32 समयout;
	पूर्णांक rc;

	rc = qeth_l2_vnicc_get_समयout(card, &समयout);
	अगर (rc == -EBUSY)
		वापस प्र_लिखो(buf, "n/a (BridgePort)\n");
	अगर (rc == -EOPNOTSUPP)
		वापस प्र_लिखो(buf, "n/a\n");
	वापस rc ? rc : प्र_लिखो(buf, "%d\n", समयout);
पूर्ण

/* change समयout setting */
अटल sमाप_प्रकार qeth_vnicc_समयout_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	u32 समयout;
	पूर्णांक rc;

	rc = kstrtou32(buf, 10, &समयout);
	अगर (rc)
		वापस rc;

	mutex_lock(&card->conf_mutex);
	rc = qeth_l2_vnicc_set_समयout(card, समयout);
	mutex_unlock(&card->conf_mutex);
	वापस rc ? rc : count;
पूर्ण

/* get current setting of अक्षरacteristic */
अटल sमाप_प्रकार qeth_vnicc_अक्षर_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	bool state;
	u32 vnicc;
	पूर्णांक rc;

	vnicc = qeth_l2_vnicc_sysfs_attr_to_अक्षर(attr->attr.name);
	rc = qeth_l2_vnicc_get_state(card, vnicc, &state);

	अगर (rc == -EBUSY)
		वापस प्र_लिखो(buf, "n/a (BridgePort)\n");
	अगर (rc == -EOPNOTSUPP)
		वापस प्र_लिखो(buf, "n/a\n");
	वापस rc ? rc : प्र_लिखो(buf, "%d\n", state);
पूर्ण

/* change setting of अक्षरacteristic */
अटल sमाप_प्रकार qeth_vnicc_अक्षर_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	bool state;
	u32 vnicc;
	पूर्णांक rc;

	अगर (kstrtobool(buf, &state))
		वापस -EINVAL;

	vnicc = qeth_l2_vnicc_sysfs_attr_to_अक्षर(attr->attr.name);
	mutex_lock(&card->conf_mutex);
	rc = qeth_l2_vnicc_set_state(card, vnicc, state);
	mutex_unlock(&card->conf_mutex);

	वापस rc ? rc : count;
पूर्ण

अटल DEVICE_ATTR(flooding, 0644, qeth_vnicc_अक्षर_show, qeth_vnicc_अक्षर_store);
अटल DEVICE_ATTR(mcast_flooding, 0644, qeth_vnicc_अक्षर_show,
		   qeth_vnicc_अक्षर_store);
अटल DEVICE_ATTR(learning, 0644, qeth_vnicc_अक्षर_show, qeth_vnicc_अक्षर_store);
अटल DEVICE_ATTR(learning_समयout, 0644, qeth_vnicc_समयout_show,
		   qeth_vnicc_समयout_store);
अटल DEVICE_ATTR(takeover_setvmac, 0644, qeth_vnicc_अक्षर_show,
		   qeth_vnicc_अक्षर_store);
अटल DEVICE_ATTR(takeover_learning, 0644, qeth_vnicc_अक्षर_show,
		   qeth_vnicc_अक्षर_store);
अटल DEVICE_ATTR(bridge_invisible, 0644, qeth_vnicc_अक्षर_show,
		   qeth_vnicc_अक्षर_store);
अटल DEVICE_ATTR(rx_bcast, 0644, qeth_vnicc_अक्षर_show, qeth_vnicc_अक्षर_store);

अटल काष्ठा attribute *qeth_l2_vnicc_attrs[] = अणु
	&dev_attr_flooding.attr,
	&dev_attr_mcast_flooding.attr,
	&dev_attr_learning.attr,
	&dev_attr_learning_समयout.attr,
	&dev_attr_takeover_setvmac.attr,
	&dev_attr_takeover_learning.attr,
	&dev_attr_bridge_invisible.attr,
	&dev_attr_rx_bcast.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group qeth_l2_vnicc_attr_group = अणु
	.attrs = qeth_l2_vnicc_attrs,
	.name = "vnicc",
पूर्ण;

स्थिर काष्ठा attribute_group *qeth_l2_attr_groups[] = अणु
	&qeth_l2_bridgeport_attr_group,
	&qeth_l2_vnicc_attr_group,
	शून्य,
पूर्ण;
