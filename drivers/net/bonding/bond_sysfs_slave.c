<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*	Sysfs attributes of bond slaves
 *
 *      Copyright (c) 2014 Scott Feldman <sfeldma@cumulusnetworks.com>
 */

#समावेश <linux/capability.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>

#समावेश <net/bonding.h>

काष्ठा slave_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा slave *, अक्षर *);
पूर्ण;

#घोषणा SLAVE_ATTR(_name, _mode, _show)				\
स्थिर काष्ठा slave_attribute slave_attr_##_name = अणु		\
	.attr = अणु.name = __stringअगरy(_name),			\
		 .mode = _mode पूर्ण,				\
	.show	= _show,					\
पूर्ण;
#घोषणा SLAVE_ATTR_RO(_name)					\
	SLAVE_ATTR(_name, 0444, _name##_show)

अटल sमाप_प्रकार state_show(काष्ठा slave *slave, अक्षर *buf)
अणु
	चयन (bond_slave_state(slave)) अणु
	हाल BOND_STATE_ACTIVE:
		वापस प्र_लिखो(buf, "active\n");
	हाल BOND_STATE_BACKUP:
		वापस प्र_लिखो(buf, "backup\n");
	शेष:
		वापस प्र_लिखो(buf, "UNKNOWN\n");
	पूर्ण
पूर्ण
अटल SLAVE_ATTR_RO(state);

अटल sमाप_प्रकार mii_status_show(काष्ठा slave *slave, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", bond_slave_link_status(slave->link));
पूर्ण
अटल SLAVE_ATTR_RO(mii_status);

अटल sमाप_प्रकार link_failure_count_show(काष्ठा slave *slave, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", slave->link_failure_count);
पूर्ण
अटल SLAVE_ATTR_RO(link_failure_count);

अटल sमाप_प्रकार perm_hwaddr_show(काष्ठा slave *slave, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%*phC\n",
		       slave->dev->addr_len,
		       slave->perm_hwaddr);
पूर्ण
अटल SLAVE_ATTR_RO(perm_hwaddr);

अटल sमाप_प्रकार queue_id_show(काष्ठा slave *slave, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", slave->queue_id);
पूर्ण
अटल SLAVE_ATTR_RO(queue_id);

अटल sमाप_प्रकार ad_aggregator_id_show(काष्ठा slave *slave, अक्षर *buf)
अणु
	स्थिर काष्ठा aggregator *agg;

	अगर (BOND_MODE(slave->bond) == BOND_MODE_8023AD) अणु
		agg = SLAVE_AD_INFO(slave)->port.aggregator;
		अगर (agg)
			वापस प्र_लिखो(buf, "%d\n",
				       agg->aggregator_identअगरier);
	पूर्ण

	वापस प्र_लिखो(buf, "N/A\n");
पूर्ण
अटल SLAVE_ATTR_RO(ad_aggregator_id);

अटल sमाप_प्रकार ad_actor_oper_port_state_show(काष्ठा slave *slave, अक्षर *buf)
अणु
	स्थिर काष्ठा port *ad_port;

	अगर (BOND_MODE(slave->bond) == BOND_MODE_8023AD) अणु
		ad_port = &SLAVE_AD_INFO(slave)->port;
		अगर (ad_port->aggregator)
			वापस प्र_लिखो(buf, "%u\n",
				       ad_port->actor_oper_port_state);
	पूर्ण

	वापस प्र_लिखो(buf, "N/A\n");
पूर्ण
अटल SLAVE_ATTR_RO(ad_actor_oper_port_state);

अटल sमाप_प्रकार ad_partner_oper_port_state_show(काष्ठा slave *slave, अक्षर *buf)
अणु
	स्थिर काष्ठा port *ad_port;

	अगर (BOND_MODE(slave->bond) == BOND_MODE_8023AD) अणु
		ad_port = &SLAVE_AD_INFO(slave)->port;
		अगर (ad_port->aggregator)
			वापस प्र_लिखो(buf, "%u\n",
				       ad_port->partner_oper.port_state);
	पूर्ण

	वापस प्र_लिखो(buf, "N/A\n");
पूर्ण
अटल SLAVE_ATTR_RO(ad_partner_oper_port_state);

अटल स्थिर काष्ठा slave_attribute *slave_attrs[] = अणु
	&slave_attr_state,
	&slave_attr_mii_status,
	&slave_attr_link_failure_count,
	&slave_attr_perm_hwaddr,
	&slave_attr_queue_id,
	&slave_attr_ad_aggregator_id,
	&slave_attr_ad_actor_oper_port_state,
	&slave_attr_ad_partner_oper_port_state,
	शून्य
पूर्ण;

#घोषणा to_slave_attr(_at) container_of(_at, काष्ठा slave_attribute, attr)

अटल sमाप_प्रकार slave_show(काष्ठा kobject *kobj,
			  काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा slave_attribute *slave_attr = to_slave_attr(attr);
	काष्ठा slave *slave = to_slave(kobj);

	वापस slave_attr->show(slave, buf);
पूर्ण

स्थिर काष्ठा sysfs_ops slave_sysfs_ops = अणु
	.show = slave_show,
पूर्ण;

पूर्णांक bond_sysfs_slave_add(काष्ठा slave *slave)
अणु
	स्थिर काष्ठा slave_attribute **a;
	पूर्णांक err;

	क्रम (a = slave_attrs; *a; ++a) अणु
		err = sysfs_create_file(&slave->kobj, &((*a)->attr));
		अगर (err) अणु
			kobject_put(&slave->kobj);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम bond_sysfs_slave_del(काष्ठा slave *slave)
अणु
	स्थिर काष्ठा slave_attribute **a;

	क्रम (a = slave_attrs; *a; ++a)
		sysfs_हटाओ_file(&slave->kobj, &((*a)->attr));
पूर्ण
