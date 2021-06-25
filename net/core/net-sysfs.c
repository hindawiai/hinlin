<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net-sysfs.c - network device class and attributes
 *
 * Copyright (c) 2003 Stephen Hemminger <shemminger@osdl.org>
 */

#समावेश <linux/capability.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/isolation.h>
#समावेश <linux/nsproxy.h>
#समावेश <net/sock.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/cpu.h>

#समावेश "net-sysfs.h"

#अगर_घोषित CONFIG_SYSFS
अटल स्थिर अक्षर fmt_hex[] = "%#x\n";
अटल स्थिर अक्षर fmt_dec[] = "%d\n";
अटल स्थिर अक्षर fmt_uदीर्घ[] = "%lu\n";
अटल स्थिर अक्षर fmt_u64[] = "%llu\n";

अटल अंतरभूत पूर्णांक dev_isalive(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->reg_state <= NETREG_REGISTERED;
पूर्ण

/* use same locking rules as GIF* ioctl's */
अटल sमाप_प्रकार netdev_show(स्थिर काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf,
			   sमाप_प्रकार (*क्रमmat)(स्थिर काष्ठा net_device *, अक्षर *))
अणु
	काष्ठा net_device *ndev = to_net_dev(dev);
	sमाप_प्रकार ret = -EINVAL;

	पढ़ो_lock(&dev_base_lock);
	अगर (dev_isalive(ndev))
		ret = (*क्रमmat)(ndev, buf);
	पढ़ो_unlock(&dev_base_lock);

	वापस ret;
पूर्ण

/* generate a show function क्रम simple field */
#घोषणा NETDEVICE_SHOW(field, क्रमmat_string)				\
अटल sमाप_प्रकार क्रमmat_##field(स्थिर काष्ठा net_device *dev, अक्षर *buf)	\
अणु									\
	वापस प्र_लिखो(buf, क्रमmat_string, dev->field);			\
पूर्ण									\
अटल sमाप_प्रकार field##_show(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	वापस netdev_show(dev, attr, buf, क्रमmat_##field);		\
पूर्ण									\

#घोषणा NETDEVICE_SHOW_RO(field, क्रमmat_string)				\
NETDEVICE_SHOW(field, क्रमmat_string);					\
अटल DEVICE_ATTR_RO(field)

#घोषणा NETDEVICE_SHOW_RW(field, क्रमmat_string)				\
NETDEVICE_SHOW(field, क्रमmat_string);					\
अटल DEVICE_ATTR_RW(field)

/* use same locking and permission rules as SIF* ioctl's */
अटल sमाप_प्रकार netdev_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार len,
			    पूर्णांक (*set)(काष्ठा net_device *, अचिन्हित दीर्घ))
अणु
	काष्ठा net_device *netdev = to_net_dev(dev);
	काष्ठा net *net = dev_net(netdev);
	अचिन्हित दीर्घ new;
	पूर्णांक ret;

	अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	ret = kम_से_अदीर्घ(buf, 0, &new);
	अगर (ret)
		जाओ err;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	अगर (dev_isalive(netdev)) अणु
		ret = (*set)(netdev, new);
		अगर (ret == 0)
			ret = len;
	पूर्ण
	rtnl_unlock();
 err:
	वापस ret;
पूर्ण

NETDEVICE_SHOW_RO(dev_id, fmt_hex);
NETDEVICE_SHOW_RO(dev_port, fmt_dec);
NETDEVICE_SHOW_RO(addr_assign_type, fmt_dec);
NETDEVICE_SHOW_RO(addr_len, fmt_dec);
NETDEVICE_SHOW_RO(अगरindex, fmt_dec);
NETDEVICE_SHOW_RO(type, fmt_dec);
NETDEVICE_SHOW_RO(link_mode, fmt_dec);

अटल sमाप_प्रकार अगरlink_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा net_device *ndev = to_net_dev(dev);

	वापस प्र_लिखो(buf, fmt_dec, dev_get_अगरlink(ndev));
पूर्ण
अटल DEVICE_ATTR_RO(अगरlink);

अटल sमाप_प्रकार क्रमmat_name_assign_type(स्थिर काष्ठा net_device *dev, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, fmt_dec, dev->name_assign_type);
पूर्ण

अटल sमाप_प्रकार name_assign_type_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा net_device *ndev = to_net_dev(dev);
	sमाप_प्रकार ret = -EINVAL;

	अगर (ndev->name_assign_type != NET_NAME_UNKNOWN)
		ret = netdev_show(dev, attr, buf, क्रमmat_name_assign_type);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(name_assign_type);

/* use same locking rules as GIFHWADDR ioctl's */
अटल sमाप_प्रकार address_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा net_device *ndev = to_net_dev(dev);
	sमाप_प्रकार ret = -EINVAL;

	पढ़ो_lock(&dev_base_lock);
	अगर (dev_isalive(ndev))
		ret = sysfs_क्रमmat_mac(buf, ndev->dev_addr, ndev->addr_len);
	पढ़ो_unlock(&dev_base_lock);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(address);

अटल sमाप_प्रकार broadcast_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *ndev = to_net_dev(dev);

	अगर (dev_isalive(ndev))
		वापस sysfs_क्रमmat_mac(buf, ndev->broadcast, ndev->addr_len);
	वापस -EINVAL;
पूर्ण
अटल DEVICE_ATTR_RO(broadcast);

अटल पूर्णांक change_carrier(काष्ठा net_device *dev, अचिन्हित दीर्घ new_carrier)
अणु
	अगर (!netअगर_running(dev))
		वापस -EINVAL;
	वापस dev_change_carrier(dev, (bool)new_carrier);
पूर्ण

अटल sमाप_प्रकार carrier_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस netdev_store(dev, attr, buf, len, change_carrier);
पूर्ण

अटल sमाप_प्रकार carrier_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *netdev = to_net_dev(dev);

	अगर (netअगर_running(netdev))
		वापस प्र_लिखो(buf, fmt_dec, !!netअगर_carrier_ok(netdev));

	वापस -EINVAL;
पूर्ण
अटल DEVICE_ATTR_RW(carrier);

अटल sमाप_प्रकार speed_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *netdev = to_net_dev(dev);
	पूर्णांक ret = -EINVAL;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	अगर (netअगर_running(netdev)) अणु
		काष्ठा ethtool_link_ksettings cmd;

		अगर (!__ethtool_get_link_ksettings(netdev, &cmd))
			ret = प्र_लिखो(buf, fmt_dec, cmd.base.speed);
	पूर्ण
	rtnl_unlock();
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(speed);

अटल sमाप_प्रकार duplex_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *netdev = to_net_dev(dev);
	पूर्णांक ret = -EINVAL;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	अगर (netअगर_running(netdev)) अणु
		काष्ठा ethtool_link_ksettings cmd;

		अगर (!__ethtool_get_link_ksettings(netdev, &cmd)) अणु
			स्थिर अक्षर *duplex;

			चयन (cmd.base.duplex) अणु
			हाल DUPLEX_HALF:
				duplex = "half";
				अवरोध;
			हाल DUPLEX_FULL:
				duplex = "full";
				अवरोध;
			शेष:
				duplex = "unknown";
				अवरोध;
			पूर्ण
			ret = प्र_लिखो(buf, "%s\n", duplex);
		पूर्ण
	पूर्ण
	rtnl_unlock();
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(duplex);

अटल sमाप_प्रकार testing_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *netdev = to_net_dev(dev);

	अगर (netअगर_running(netdev))
		वापस प्र_लिखो(buf, fmt_dec, !!netअगर_testing(netdev));

	वापस -EINVAL;
पूर्ण
अटल DEVICE_ATTR_RO(testing);

अटल sमाप_प्रकार करोrmant_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *netdev = to_net_dev(dev);

	अगर (netअगर_running(netdev))
		वापस प्र_लिखो(buf, fmt_dec, !!netअगर_करोrmant(netdev));

	वापस -EINVAL;
पूर्ण
अटल DEVICE_ATTR_RO(करोrmant);

अटल स्थिर अक्षर *स्थिर operstates[] = अणु
	"unknown",
	"notpresent", /* currently unused */
	"down",
	"lowerlayerdown",
	"testing",
	"dormant",
	"up"
पूर्ण;

अटल sमाप_प्रकार operstate_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा net_device *netdev = to_net_dev(dev);
	अचिन्हित अक्षर operstate;

	पढ़ो_lock(&dev_base_lock);
	operstate = netdev->operstate;
	अगर (!netअगर_running(netdev))
		operstate = IF_OPER_DOWN;
	पढ़ो_unlock(&dev_base_lock);

	अगर (operstate >= ARRAY_SIZE(operstates))
		वापस -EINVAL; /* should not happen */

	वापस प्र_लिखो(buf, "%s\n", operstates[operstate]);
पूर्ण
अटल DEVICE_ATTR_RO(operstate);

अटल sमाप_प्रकार carrier_changes_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा net_device *netdev = to_net_dev(dev);

	वापस प्र_लिखो(buf, fmt_dec,
		       atomic_पढ़ो(&netdev->carrier_up_count) +
		       atomic_पढ़ो(&netdev->carrier_करोwn_count));
पूर्ण
अटल DEVICE_ATTR_RO(carrier_changes);

अटल sमाप_प्रकार carrier_up_count_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा net_device *netdev = to_net_dev(dev);

	वापस प्र_लिखो(buf, fmt_dec, atomic_पढ़ो(&netdev->carrier_up_count));
पूर्ण
अटल DEVICE_ATTR_RO(carrier_up_count);

अटल sमाप_प्रकार carrier_करोwn_count_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा net_device *netdev = to_net_dev(dev);

	वापस प्र_लिखो(buf, fmt_dec, atomic_पढ़ो(&netdev->carrier_करोwn_count));
पूर्ण
अटल DEVICE_ATTR_RO(carrier_करोwn_count);

/* पढ़ो-ग_लिखो attributes */

अटल पूर्णांक change_mtu(काष्ठा net_device *dev, अचिन्हित दीर्घ new_mtu)
अणु
	वापस dev_set_mtu(dev, (पूर्णांक)new_mtu);
पूर्ण

अटल sमाप_प्रकार mtu_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस netdev_store(dev, attr, buf, len, change_mtu);
पूर्ण
NETDEVICE_SHOW_RW(mtu, fmt_dec);

अटल पूर्णांक change_flags(काष्ठा net_device *dev, अचिन्हित दीर्घ new_flags)
अणु
	वापस dev_change_flags(dev, (अचिन्हित पूर्णांक)new_flags, शून्य);
पूर्ण

अटल sमाप_प्रकार flags_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस netdev_store(dev, attr, buf, len, change_flags);
पूर्ण
NETDEVICE_SHOW_RW(flags, fmt_hex);

अटल sमाप_प्रकार tx_queue_len_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	वापस netdev_store(dev, attr, buf, len, dev_change_tx_queue_len);
पूर्ण
NETDEVICE_SHOW_RW(tx_queue_len, fmt_dec);

अटल पूर्णांक change_gro_flush_समयout(काष्ठा net_device *dev, अचिन्हित दीर्घ val)
अणु
	WRITE_ONCE(dev->gro_flush_समयout, val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार gro_flush_समयout_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	वापस netdev_store(dev, attr, buf, len, change_gro_flush_समयout);
पूर्ण
NETDEVICE_SHOW_RW(gro_flush_समयout, fmt_uदीर्घ);

अटल पूर्णांक change_napi_defer_hard_irqs(काष्ठा net_device *dev, अचिन्हित दीर्घ val)
अणु
	WRITE_ONCE(dev->napi_defer_hard_irqs, val);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार napi_defer_hard_irqs_store(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	वापस netdev_store(dev, attr, buf, len, change_napi_defer_hard_irqs);
पूर्ण
NETDEVICE_SHOW_RW(napi_defer_hard_irqs, fmt_dec);

अटल sमाप_प्रकार अगरalias_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा net_device *netdev = to_net_dev(dev);
	काष्ठा net *net = dev_net(netdev);
	माप_प्रकार count = len;
	sमाप_प्रकार ret = 0;

	अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	/* ignore trailing newline */
	अगर (len >  0 && buf[len - 1] == '\n')
		--count;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	अगर (dev_isalive(netdev)) अणु
		ret = dev_set_alias(netdev, buf, count);
		अगर (ret < 0)
			जाओ err;
		ret = len;
		netdev_state_change(netdev);
	पूर्ण
err:
	rtnl_unlock();

	वापस ret;
पूर्ण

अटल sमाप_प्रकार अगरalias_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा net_device *netdev = to_net_dev(dev);
	अक्षर पंचांगp[IFALIASZ];
	sमाप_प्रकार ret = 0;

	ret = dev_get_alias(netdev, पंचांगp, माप(पंचांगp));
	अगर (ret > 0)
		ret = प्र_लिखो(buf, "%s\n", पंचांगp);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RW(अगरalias);

अटल पूर्णांक change_group(काष्ठा net_device *dev, अचिन्हित दीर्घ new_group)
अणु
	dev_set_group(dev, (पूर्णांक)new_group);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार group_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस netdev_store(dev, attr, buf, len, change_group);
पूर्ण
NETDEVICE_SHOW(group, fmt_dec);
अटल DEVICE_ATTR(netdev_group, 0644, group_show, group_store);

अटल पूर्णांक change_proto_करोwn(काष्ठा net_device *dev, अचिन्हित दीर्घ proto_करोwn)
अणु
	वापस dev_change_proto_करोwn(dev, (bool)proto_करोwn);
पूर्ण

अटल sमाप_प्रकार proto_करोwn_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस netdev_store(dev, attr, buf, len, change_proto_करोwn);
पूर्ण
NETDEVICE_SHOW_RW(proto_करोwn, fmt_dec);

अटल sमाप_प्रकार phys_port_id_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *netdev = to_net_dev(dev);
	sमाप_प्रकार ret = -EINVAL;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	अगर (dev_isalive(netdev)) अणु
		काष्ठा netdev_phys_item_id ppid;

		ret = dev_get_phys_port_id(netdev, &ppid);
		अगर (!ret)
			ret = प्र_लिखो(buf, "%*phN\n", ppid.id_len, ppid.id);
	पूर्ण
	rtnl_unlock();

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(phys_port_id);

अटल sमाप_प्रकार phys_port_name_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *netdev = to_net_dev(dev);
	sमाप_प्रकार ret = -EINVAL;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	अगर (dev_isalive(netdev)) अणु
		अक्षर name[IFNAMSIZ];

		ret = dev_get_phys_port_name(netdev, name, माप(name));
		अगर (!ret)
			ret = प्र_लिखो(buf, "%s\n", name);
	पूर्ण
	rtnl_unlock();

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(phys_port_name);

अटल sमाप_प्रकार phys_चयन_id_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *netdev = to_net_dev(dev);
	sमाप_प्रकार ret = -EINVAL;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	अगर (dev_isalive(netdev)) अणु
		काष्ठा netdev_phys_item_id ppid = अणु पूर्ण;

		ret = dev_get_port_parent_id(netdev, &ppid, false);
		अगर (!ret)
			ret = प्र_लिखो(buf, "%*phN\n", ppid.id_len, ppid.id);
	पूर्ण
	rtnl_unlock();

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(phys_चयन_id);

अटल sमाप_प्रकार thपढ़ोed_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *netdev = to_net_dev(dev);
	sमाप_प्रकार ret = -EINVAL;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	अगर (dev_isalive(netdev))
		ret = प्र_लिखो(buf, fmt_dec, netdev->thपढ़ोed);

	rtnl_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक modअगरy_napi_thपढ़ोed(काष्ठा net_device *dev, अचिन्हित दीर्घ val)
अणु
	पूर्णांक ret;

	अगर (list_empty(&dev->napi_list))
		वापस -EOPNOTSUPP;

	अगर (val != 0 && val != 1)
		वापस -EOPNOTSUPP;

	ret = dev_set_thपढ़ोed(dev, val);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार thपढ़ोed_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस netdev_store(dev, attr, buf, len, modअगरy_napi_thपढ़ोed);
पूर्ण
अटल DEVICE_ATTR_RW(thपढ़ोed);

अटल काष्ठा attribute *net_class_attrs[] __ro_after_init = अणु
	&dev_attr_netdev_group.attr,
	&dev_attr_type.attr,
	&dev_attr_dev_id.attr,
	&dev_attr_dev_port.attr,
	&dev_attr_अगरlink.attr,
	&dev_attr_अगरindex.attr,
	&dev_attr_name_assign_type.attr,
	&dev_attr_addr_assign_type.attr,
	&dev_attr_addr_len.attr,
	&dev_attr_link_mode.attr,
	&dev_attr_address.attr,
	&dev_attr_broadcast.attr,
	&dev_attr_speed.attr,
	&dev_attr_duplex.attr,
	&dev_attr_करोrmant.attr,
	&dev_attr_testing.attr,
	&dev_attr_operstate.attr,
	&dev_attr_carrier_changes.attr,
	&dev_attr_अगरalias.attr,
	&dev_attr_carrier.attr,
	&dev_attr_mtu.attr,
	&dev_attr_flags.attr,
	&dev_attr_tx_queue_len.attr,
	&dev_attr_gro_flush_समयout.attr,
	&dev_attr_napi_defer_hard_irqs.attr,
	&dev_attr_phys_port_id.attr,
	&dev_attr_phys_port_name.attr,
	&dev_attr_phys_चयन_id.attr,
	&dev_attr_proto_करोwn.attr,
	&dev_attr_carrier_up_count.attr,
	&dev_attr_carrier_करोwn_count.attr,
	&dev_attr_thपढ़ोed.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(net_class);

/* Show a given an attribute in the statistics group */
अटल sमाप_प्रकार netstat_show(स्थिर काष्ठा device *d,
			    काष्ठा device_attribute *attr, अक्षर *buf,
			    अचिन्हित दीर्घ offset)
अणु
	काष्ठा net_device *dev = to_net_dev(d);
	sमाप_प्रकार ret = -EINVAL;

	WARN_ON(offset > माप(काष्ठा rtnl_link_stats64) ||
		offset % माप(u64) != 0);

	पढ़ो_lock(&dev_base_lock);
	अगर (dev_isalive(dev)) अणु
		काष्ठा rtnl_link_stats64 temp;
		स्थिर काष्ठा rtnl_link_stats64 *stats = dev_get_stats(dev, &temp);

		ret = प्र_लिखो(buf, fmt_u64, *(u64 *)(((u8 *)stats) + offset));
	पूर्ण
	पढ़ो_unlock(&dev_base_lock);
	वापस ret;
पूर्ण

/* generate a पढ़ो-only statistics attribute */
#घोषणा NETSTAT_ENTRY(name)						\
अटल sमाप_प्रकार name##_show(काष्ठा device *d,				\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	वापस netstat_show(d, attr, buf,				\
			    दुरत्व(काष्ठा rtnl_link_stats64, name));	\
पूर्ण									\
अटल DEVICE_ATTR_RO(name)

NETSTAT_ENTRY(rx_packets);
NETSTAT_ENTRY(tx_packets);
NETSTAT_ENTRY(rx_bytes);
NETSTAT_ENTRY(tx_bytes);
NETSTAT_ENTRY(rx_errors);
NETSTAT_ENTRY(tx_errors);
NETSTAT_ENTRY(rx_dropped);
NETSTAT_ENTRY(tx_dropped);
NETSTAT_ENTRY(multicast);
NETSTAT_ENTRY(collisions);
NETSTAT_ENTRY(rx_length_errors);
NETSTAT_ENTRY(rx_over_errors);
NETSTAT_ENTRY(rx_crc_errors);
NETSTAT_ENTRY(rx_frame_errors);
NETSTAT_ENTRY(rx_fअगरo_errors);
NETSTAT_ENTRY(rx_missed_errors);
NETSTAT_ENTRY(tx_पातed_errors);
NETSTAT_ENTRY(tx_carrier_errors);
NETSTAT_ENTRY(tx_fअगरo_errors);
NETSTAT_ENTRY(tx_heartbeat_errors);
NETSTAT_ENTRY(tx_winकरोw_errors);
NETSTAT_ENTRY(rx_compressed);
NETSTAT_ENTRY(tx_compressed);
NETSTAT_ENTRY(rx_nohandler);

अटल काष्ठा attribute *netstat_attrs[] __ro_after_init = अणु
	&dev_attr_rx_packets.attr,
	&dev_attr_tx_packets.attr,
	&dev_attr_rx_bytes.attr,
	&dev_attr_tx_bytes.attr,
	&dev_attr_rx_errors.attr,
	&dev_attr_tx_errors.attr,
	&dev_attr_rx_dropped.attr,
	&dev_attr_tx_dropped.attr,
	&dev_attr_multicast.attr,
	&dev_attr_collisions.attr,
	&dev_attr_rx_length_errors.attr,
	&dev_attr_rx_over_errors.attr,
	&dev_attr_rx_crc_errors.attr,
	&dev_attr_rx_frame_errors.attr,
	&dev_attr_rx_fअगरo_errors.attr,
	&dev_attr_rx_missed_errors.attr,
	&dev_attr_tx_पातed_errors.attr,
	&dev_attr_tx_carrier_errors.attr,
	&dev_attr_tx_fअगरo_errors.attr,
	&dev_attr_tx_heartbeat_errors.attr,
	&dev_attr_tx_winकरोw_errors.attr,
	&dev_attr_rx_compressed.attr,
	&dev_attr_tx_compressed.attr,
	&dev_attr_rx_nohandler.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group netstat_group = अणु
	.name  = "statistics",
	.attrs  = netstat_attrs,
पूर्ण;

#अगर IS_ENABLED(CONFIG_WIRELESS_EXT) || IS_ENABLED(CONFIG_CFG80211)
अटल काष्ठा attribute *wireless_attrs[] = अणु
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group wireless_group = अणु
	.name = "wireless",
	.attrs = wireless_attrs,
पूर्ण;
#पूर्ण_अगर

#अन्यथा /* CONFIG_SYSFS */
#घोषणा net_class_groups	शून्य
#पूर्ण_अगर /* CONFIG_SYSFS */

#अगर_घोषित CONFIG_SYSFS
#घोषणा to_rx_queue_attr(_attr) \
	container_of(_attr, काष्ठा rx_queue_attribute, attr)

#घोषणा to_rx_queue(obj) container_of(obj, काष्ठा netdev_rx_queue, kobj)

अटल sमाप_प्रकार rx_queue_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				  अक्षर *buf)
अणु
	स्थिर काष्ठा rx_queue_attribute *attribute = to_rx_queue_attr(attr);
	काष्ठा netdev_rx_queue *queue = to_rx_queue(kobj);

	अगर (!attribute->show)
		वापस -EIO;

	वापस attribute->show(queue, buf);
पूर्ण

अटल sमाप_प्रकार rx_queue_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	स्थिर काष्ठा rx_queue_attribute *attribute = to_rx_queue_attr(attr);
	काष्ठा netdev_rx_queue *queue = to_rx_queue(kobj);

	अगर (!attribute->store)
		वापस -EIO;

	वापस attribute->store(queue, buf, count);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops rx_queue_sysfs_ops = अणु
	.show = rx_queue_attr_show,
	.store = rx_queue_attr_store,
पूर्ण;

#अगर_घोषित CONFIG_RPS
अटल sमाप_प्रकार show_rps_map(काष्ठा netdev_rx_queue *queue, अक्षर *buf)
अणु
	काष्ठा rps_map *map;
	cpumask_var_t mask;
	पूर्णांक i, len;

	अगर (!zalloc_cpumask_var(&mask, GFP_KERNEL))
		वापस -ENOMEM;

	rcu_पढ़ो_lock();
	map = rcu_dereference(queue->rps_map);
	अगर (map)
		क्रम (i = 0; i < map->len; i++)
			cpumask_set_cpu(map->cpus[i], mask);

	len = snम_लिखो(buf, PAGE_SIZE, "%*pb\n", cpumask_pr_args(mask));
	rcu_पढ़ो_unlock();
	मुक्त_cpumask_var(mask);

	वापस len < PAGE_SIZE ? len : -EINVAL;
पूर्ण

अटल sमाप_प्रकार store_rps_map(काष्ठा netdev_rx_queue *queue,
			     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा rps_map *old_map, *map;
	cpumask_var_t mask;
	पूर्णांक err, cpu, i, hk_flags;
	अटल DEFINE_MUTEX(rps_map_mutex);

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!alloc_cpumask_var(&mask, GFP_KERNEL))
		वापस -ENOMEM;

	err = biपंचांगap_parse(buf, len, cpumask_bits(mask), nr_cpumask_bits);
	अगर (err) अणु
		मुक्त_cpumask_var(mask);
		वापस err;
	पूर्ण

	अगर (!cpumask_empty(mask)) अणु
		hk_flags = HK_FLAG_DOMAIN | HK_FLAG_WQ;
		cpumask_and(mask, mask, housekeeping_cpumask(hk_flags));
		अगर (cpumask_empty(mask)) अणु
			मुक्त_cpumask_var(mask);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	map = kzalloc(max_t(अचिन्हित पूर्णांक,
			    RPS_MAP_SIZE(cpumask_weight(mask)), L1_CACHE_BYTES),
		      GFP_KERNEL);
	अगर (!map) अणु
		मुक्त_cpumask_var(mask);
		वापस -ENOMEM;
	पूर्ण

	i = 0;
	क्रम_each_cpu_and(cpu, mask, cpu_online_mask)
		map->cpus[i++] = cpu;

	अगर (i) अणु
		map->len = i;
	पूर्ण अन्यथा अणु
		kमुक्त(map);
		map = शून्य;
	पूर्ण

	mutex_lock(&rps_map_mutex);
	old_map = rcu_dereference_रक्षित(queue->rps_map,
					    mutex_is_locked(&rps_map_mutex));
	rcu_assign_poपूर्णांकer(queue->rps_map, map);

	अगर (map)
		अटल_branch_inc(&rps_needed);
	अगर (old_map)
		अटल_branch_dec(&rps_needed);

	mutex_unlock(&rps_map_mutex);

	अगर (old_map)
		kमुक्त_rcu(old_map, rcu);

	मुक्त_cpumask_var(mask);
	वापस len;
पूर्ण

अटल sमाप_प्रकार show_rps_dev_flow_table_cnt(काष्ठा netdev_rx_queue *queue,
					   अक्षर *buf)
अणु
	काष्ठा rps_dev_flow_table *flow_table;
	अचिन्हित दीर्घ val = 0;

	rcu_पढ़ो_lock();
	flow_table = rcu_dereference(queue->rps_flow_table);
	अगर (flow_table)
		val = (अचिन्हित दीर्घ)flow_table->mask + 1;
	rcu_पढ़ो_unlock();

	वापस प्र_लिखो(buf, "%lu\n", val);
पूर्ण

अटल व्योम rps_dev_flow_table_release(काष्ठा rcu_head *rcu)
अणु
	काष्ठा rps_dev_flow_table *table = container_of(rcu,
	    काष्ठा rps_dev_flow_table, rcu);
	vमुक्त(table);
पूर्ण

अटल sमाप_प्रकार store_rps_dev_flow_table_cnt(काष्ठा netdev_rx_queue *queue,
					    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ mask, count;
	काष्ठा rps_dev_flow_table *table, *old_table;
	अटल DEFINE_SPINLOCK(rps_dev_flow_lock);
	पूर्णांक rc;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	rc = kम_से_अदीर्घ(buf, 0, &count);
	अगर (rc < 0)
		वापस rc;

	अगर (count) अणु
		mask = count - 1;
		/* mask = roundup_घात_of_two(count) - 1;
		 * without overflows...
		 */
		जबतक ((mask | (mask >> 1)) != mask)
			mask |= (mask >> 1);
		/* On 64 bit arches, must check mask fits in table->mask (u32),
		 * and on 32bit arches, must check
		 * RPS_DEV_FLOW_TABLE_SIZE(mask + 1) करोesn't overflow.
		 */
#अगर BITS_PER_LONG > 32
		अगर (mask > (अचिन्हित दीर्घ)(u32)mask)
			वापस -EINVAL;
#अन्यथा
		अगर (mask > (अच_दीर्घ_उच्च - RPS_DEV_FLOW_TABLE_SIZE(1))
				/ माप(काष्ठा rps_dev_flow)) अणु
			/* Enक्रमce a limit to prevent overflow */
			वापस -EINVAL;
		पूर्ण
#पूर्ण_अगर
		table = vदो_स्मृति(RPS_DEV_FLOW_TABLE_SIZE(mask + 1));
		अगर (!table)
			वापस -ENOMEM;

		table->mask = mask;
		क्रम (count = 0; count <= mask; count++)
			table->flows[count].cpu = RPS_NO_CPU;
	पूर्ण अन्यथा अणु
		table = शून्य;
	पूर्ण

	spin_lock(&rps_dev_flow_lock);
	old_table = rcu_dereference_रक्षित(queue->rps_flow_table,
					      lockdep_is_held(&rps_dev_flow_lock));
	rcu_assign_poपूर्णांकer(queue->rps_flow_table, table);
	spin_unlock(&rps_dev_flow_lock);

	अगर (old_table)
		call_rcu(&old_table->rcu, rps_dev_flow_table_release);

	वापस len;
पूर्ण

अटल काष्ठा rx_queue_attribute rps_cpus_attribute __ro_after_init
	= __ATTR(rps_cpus, 0644, show_rps_map, store_rps_map);

अटल काष्ठा rx_queue_attribute rps_dev_flow_table_cnt_attribute __ro_after_init
	= __ATTR(rps_flow_cnt, 0644,
		 show_rps_dev_flow_table_cnt, store_rps_dev_flow_table_cnt);
#पूर्ण_अगर /* CONFIG_RPS */

अटल काष्ठा attribute *rx_queue_शेष_attrs[] __ro_after_init = अणु
#अगर_घोषित CONFIG_RPS
	&rps_cpus_attribute.attr,
	&rps_dev_flow_table_cnt_attribute.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(rx_queue_शेष);

अटल व्योम rx_queue_release(काष्ठा kobject *kobj)
अणु
	काष्ठा netdev_rx_queue *queue = to_rx_queue(kobj);
#अगर_घोषित CONFIG_RPS
	काष्ठा rps_map *map;
	काष्ठा rps_dev_flow_table *flow_table;

	map = rcu_dereference_रक्षित(queue->rps_map, 1);
	अगर (map) अणु
		RCU_INIT_POINTER(queue->rps_map, शून्य);
		kमुक्त_rcu(map, rcu);
	पूर्ण

	flow_table = rcu_dereference_रक्षित(queue->rps_flow_table, 1);
	अगर (flow_table) अणु
		RCU_INIT_POINTER(queue->rps_flow_table, शून्य);
		call_rcu(&flow_table->rcu, rps_dev_flow_table_release);
	पूर्ण
#पूर्ण_अगर

	स_रखो(kobj, 0, माप(*kobj));
	dev_put(queue->dev);
पूर्ण

अटल स्थिर व्योम *rx_queue_namespace(काष्ठा kobject *kobj)
अणु
	काष्ठा netdev_rx_queue *queue = to_rx_queue(kobj);
	काष्ठा device *dev = &queue->dev->dev;
	स्थिर व्योम *ns = शून्य;

	अगर (dev->class && dev->class->ns_type)
		ns = dev->class->namespace(dev);

	वापस ns;
पूर्ण

अटल व्योम rx_queue_get_ownership(काष्ठा kobject *kobj,
				   kuid_t *uid, kgid_t *gid)
अणु
	स्थिर काष्ठा net *net = rx_queue_namespace(kobj);

	net_ns_get_ownership(net, uid, gid);
पूर्ण

अटल काष्ठा kobj_type rx_queue_ktype __ro_after_init = अणु
	.sysfs_ops = &rx_queue_sysfs_ops,
	.release = rx_queue_release,
	.शेष_groups = rx_queue_शेष_groups,
	.namespace = rx_queue_namespace,
	.get_ownership = rx_queue_get_ownership,
पूर्ण;

अटल पूर्णांक rx_queue_add_kobject(काष्ठा net_device *dev, पूर्णांक index)
अणु
	काष्ठा netdev_rx_queue *queue = dev->_rx + index;
	काष्ठा kobject *kobj = &queue->kobj;
	पूर्णांक error = 0;

	/* Kobject_put later will trigger rx_queue_release call which
	 * decreases dev refcount: Take that reference here
	 */
	dev_hold(queue->dev);

	kobj->kset = dev->queues_kset;
	error = kobject_init_and_add(kobj, &rx_queue_ktype, शून्य,
				     "rx-%u", index);
	अगर (error)
		जाओ err;

	अगर (dev->sysfs_rx_queue_group) अणु
		error = sysfs_create_group(kobj, dev->sysfs_rx_queue_group);
		अगर (error)
			जाओ err;
	पूर्ण

	kobject_uevent(kobj, KOBJ_ADD);

	वापस error;

err:
	kobject_put(kobj);
	वापस error;
पूर्ण

अटल पूर्णांक rx_queue_change_owner(काष्ठा net_device *dev, पूर्णांक index, kuid_t kuid,
				 kgid_t kgid)
अणु
	काष्ठा netdev_rx_queue *queue = dev->_rx + index;
	काष्ठा kobject *kobj = &queue->kobj;
	पूर्णांक error;

	error = sysfs_change_owner(kobj, kuid, kgid);
	अगर (error)
		वापस error;

	अगर (dev->sysfs_rx_queue_group)
		error = sysfs_group_change_owner(
			kobj, dev->sysfs_rx_queue_group, kuid, kgid);

	वापस error;
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSFS */

पूर्णांक
net_rx_queue_update_kobjects(काष्ठा net_device *dev, पूर्णांक old_num, पूर्णांक new_num)
अणु
#अगर_घोषित CONFIG_SYSFS
	पूर्णांक i;
	पूर्णांक error = 0;

#अगर_अघोषित CONFIG_RPS
	अगर (!dev->sysfs_rx_queue_group)
		वापस 0;
#पूर्ण_अगर
	क्रम (i = old_num; i < new_num; i++) अणु
		error = rx_queue_add_kobject(dev, i);
		अगर (error) अणु
			new_num = old_num;
			अवरोध;
		पूर्ण
	पूर्ण

	जबतक (--i >= new_num) अणु
		काष्ठा kobject *kobj = &dev->_rx[i].kobj;

		अगर (!refcount_पढ़ो(&dev_net(dev)->ns.count))
			kobj->uevent_suppress = 1;
		अगर (dev->sysfs_rx_queue_group)
			sysfs_हटाओ_group(kobj, dev->sysfs_rx_queue_group);
		kobject_put(kobj);
	पूर्ण

	वापस error;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक net_rx_queue_change_owner(काष्ठा net_device *dev, पूर्णांक num,
				     kuid_t kuid, kgid_t kgid)
अणु
#अगर_घोषित CONFIG_SYSFS
	पूर्णांक error = 0;
	पूर्णांक i;

#अगर_अघोषित CONFIG_RPS
	अगर (!dev->sysfs_rx_queue_group)
		वापस 0;
#पूर्ण_अगर
	क्रम (i = 0; i < num; i++) अणु
		error = rx_queue_change_owner(dev, i, kuid, kgid);
		अगर (error)
			अवरोध;
	पूर्ण

	वापस error;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_SYSFS
/*
 * netdev_queue sysfs काष्ठाures and functions.
 */
काष्ठा netdev_queue_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा netdev_queue *queue, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा netdev_queue *queue,
			 स्थिर अक्षर *buf, माप_प्रकार len);
पूर्ण;
#घोषणा to_netdev_queue_attr(_attr) \
	container_of(_attr, काष्ठा netdev_queue_attribute, attr)

#घोषणा to_netdev_queue(obj) container_of(obj, काष्ठा netdev_queue, kobj)

अटल sमाप_प्रकार netdev_queue_attr_show(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा netdev_queue_attribute *attribute
		= to_netdev_queue_attr(attr);
	काष्ठा netdev_queue *queue = to_netdev_queue(kobj);

	अगर (!attribute->show)
		वापस -EIO;

	वापस attribute->show(queue, buf);
पूर्ण

अटल sमाप_प्रकार netdev_queue_attr_store(काष्ठा kobject *kobj,
				       काष्ठा attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	स्थिर काष्ठा netdev_queue_attribute *attribute
		= to_netdev_queue_attr(attr);
	काष्ठा netdev_queue *queue = to_netdev_queue(kobj);

	अगर (!attribute->store)
		वापस -EIO;

	वापस attribute->store(queue, buf, count);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops netdev_queue_sysfs_ops = अणु
	.show = netdev_queue_attr_show,
	.store = netdev_queue_attr_store,
पूर्ण;

अटल sमाप_प्रकार tx_समयout_show(काष्ठा netdev_queue *queue, अक्षर *buf)
अणु
	अचिन्हित दीर्घ trans_समयout;

	spin_lock_irq(&queue->_xmit_lock);
	trans_समयout = queue->trans_समयout;
	spin_unlock_irq(&queue->_xmit_lock);

	वापस प्र_लिखो(buf, fmt_uदीर्घ, trans_समयout);
पूर्ण

अटल अचिन्हित पूर्णांक get_netdev_queue_index(काष्ठा netdev_queue *queue)
अणु
	काष्ठा net_device *dev = queue->dev;
	अचिन्हित पूर्णांक i;

	i = queue - dev->_tx;
	BUG_ON(i >= dev->num_tx_queues);

	वापस i;
पूर्ण

अटल sमाप_प्रकार traffic_class_show(काष्ठा netdev_queue *queue,
				  अक्षर *buf)
अणु
	काष्ठा net_device *dev = queue->dev;
	पूर्णांक num_tc, tc;
	पूर्णांक index;

	अगर (!netअगर_is_multiqueue(dev))
		वापस -ENOENT;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	index = get_netdev_queue_index(queue);

	/* If queue beदीर्घs to subordinate dev use its TC mapping */
	dev = netdev_get_tx_queue(dev, index)->sb_dev ? : dev;

	num_tc = dev->num_tc;
	tc = netdev_txq_to_tc(dev, index);

	rtnl_unlock();

	अगर (tc < 0)
		वापस -EINVAL;

	/* We can report the traffic class one of two ways:
	 * Subordinate device traffic classes are reported with the traffic
	 * class first, and then the subordinate class so क्रम example TC0 on
	 * subordinate device 2 will be reported as "0-2". If the queue
	 * beदीर्घs to the root device it will be reported with just the
	 * traffic class, so just "0" क्रम TC 0 क्रम example.
	 */
	वापस num_tc < 0 ? प्र_लिखो(buf, "%d%d\n", tc, num_tc) :
			    प्र_लिखो(buf, "%d\n", tc);
पूर्ण

#अगर_घोषित CONFIG_XPS
अटल sमाप_प्रकार tx_maxrate_show(काष्ठा netdev_queue *queue,
			       अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lu\n", queue->tx_maxrate);
पूर्ण

अटल sमाप_प्रकार tx_maxrate_store(काष्ठा netdev_queue *queue,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा net_device *dev = queue->dev;
	पूर्णांक err, index = get_netdev_queue_index(queue);
	u32 rate = 0;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	err = kstrtou32(buf, 10, &rate);
	अगर (err < 0)
		वापस err;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	err = -EOPNOTSUPP;
	अगर (dev->netdev_ops->nकरो_set_tx_maxrate)
		err = dev->netdev_ops->nकरो_set_tx_maxrate(dev, index, rate);

	rtnl_unlock();
	अगर (!err) अणु
		queue->tx_maxrate = rate;
		वापस len;
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा netdev_queue_attribute queue_tx_maxrate __ro_after_init
	= __ATTR_RW(tx_maxrate);
#पूर्ण_अगर

अटल काष्ठा netdev_queue_attribute queue_trans_समयout __ro_after_init
	= __ATTR_RO(tx_समयout);

अटल काष्ठा netdev_queue_attribute queue_traffic_class __ro_after_init
	= __ATTR_RO(traffic_class);

#अगर_घोषित CONFIG_BQL
/*
 * Byte queue limits sysfs काष्ठाures and functions.
 */
अटल sमाप_प्रकार bql_show(अक्षर *buf, अचिन्हित पूर्णांक value)
अणु
	वापस प्र_लिखो(buf, "%u\n", value);
पूर्ण

अटल sमाप_प्रकार bql_set(स्थिर अक्षर *buf, स्थिर माप_प्रकार count,
		       अचिन्हित पूर्णांक *pvalue)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक err;

	अगर (!म_भेद(buf, "max") || !म_भेद(buf, "max\n")) अणु
		value = DQL_MAX_LIMIT;
	पूर्ण अन्यथा अणु
		err = kstrtouपूर्णांक(buf, 10, &value);
		अगर (err < 0)
			वापस err;
		अगर (value > DQL_MAX_LIMIT)
			वापस -EINVAL;
	पूर्ण

	*pvalue = value;

	वापस count;
पूर्ण

अटल sमाप_प्रकार bql_show_hold_समय(काष्ठा netdev_queue *queue,
				  अक्षर *buf)
अणु
	काष्ठा dql *dql = &queue->dql;

	वापस प्र_लिखो(buf, "%u\n", jअगरfies_to_msecs(dql->slack_hold_समय));
पूर्ण

अटल sमाप_प्रकार bql_set_hold_समय(काष्ठा netdev_queue *queue,
				 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा dql *dql = &queue->dql;
	अचिन्हित पूर्णांक value;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &value);
	अगर (err < 0)
		वापस err;

	dql->slack_hold_समय = msecs_to_jअगरfies(value);

	वापस len;
पूर्ण

अटल काष्ठा netdev_queue_attribute bql_hold_समय_attribute __ro_after_init
	= __ATTR(hold_समय, 0644,
		 bql_show_hold_समय, bql_set_hold_समय);

अटल sमाप_प्रकार bql_show_inflight(काष्ठा netdev_queue *queue,
				 अक्षर *buf)
अणु
	काष्ठा dql *dql = &queue->dql;

	वापस प्र_लिखो(buf, "%u\n", dql->num_queued - dql->num_completed);
पूर्ण

अटल काष्ठा netdev_queue_attribute bql_inflight_attribute __ro_after_init =
	__ATTR(inflight, 0444, bql_show_inflight, शून्य);

#घोषणा BQL_ATTR(NAME, FIELD)						\
अटल sमाप_प्रकार bql_show_ ## NAME(काष्ठा netdev_queue *queue,		\
				 अक्षर *buf)				\
अणु									\
	वापस bql_show(buf, queue->dql.FIELD);				\
पूर्ण									\
									\
अटल sमाप_प्रकार bql_set_ ## NAME(काष्ठा netdev_queue *queue,		\
				स्थिर अक्षर *buf, माप_प्रकार len)		\
अणु									\
	वापस bql_set(buf, len, &queue->dql.FIELD);			\
पूर्ण									\
									\
अटल काष्ठा netdev_queue_attribute bql_ ## NAME ## _attribute __ro_after_init \
	= __ATTR(NAME, 0644,				\
		 bql_show_ ## NAME, bql_set_ ## NAME)

BQL_ATTR(limit, limit);
BQL_ATTR(limit_max, max_limit);
BQL_ATTR(limit_min, min_limit);

अटल काष्ठा attribute *dql_attrs[] __ro_after_init = अणु
	&bql_limit_attribute.attr,
	&bql_limit_max_attribute.attr,
	&bql_limit_min_attribute.attr,
	&bql_hold_समय_attribute.attr,
	&bql_inflight_attribute.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dql_group = अणु
	.name  = "byte_queue_limits",
	.attrs  = dql_attrs,
पूर्ण;
#पूर्ण_अगर /* CONFIG_BQL */

#अगर_घोषित CONFIG_XPS
अटल sमाप_प्रकार xps_queue_show(काष्ठा net_device *dev, अचिन्हित पूर्णांक index,
			      पूर्णांक tc, अक्षर *buf, क्रमागत xps_map_type type)
अणु
	काष्ठा xps_dev_maps *dev_maps;
	अचिन्हित दीर्घ *mask;
	अचिन्हित पूर्णांक nr_ids;
	पूर्णांक j, len;

	rcu_पढ़ो_lock();
	dev_maps = rcu_dereference(dev->xps_maps[type]);

	/* Default to nr_cpu_ids/dev->num_rx_queues and करो not just वापस 0
	 * when dev_maps hasn't been allocated yet, to be backward compatible.
	 */
	nr_ids = dev_maps ? dev_maps->nr_ids :
		 (type == XPS_CPUS ? nr_cpu_ids : dev->num_rx_queues);

	mask = biपंचांगap_zalloc(nr_ids, GFP_NOWAIT);
	अगर (!mask) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOMEM;
	पूर्ण

	अगर (!dev_maps || tc >= dev_maps->num_tc)
		जाओ out_no_maps;

	क्रम (j = 0; j < nr_ids; j++) अणु
		पूर्णांक i, tci = j * dev_maps->num_tc + tc;
		काष्ठा xps_map *map;

		map = rcu_dereference(dev_maps->attr_map[tci]);
		अगर (!map)
			जारी;

		क्रम (i = map->len; i--;) अणु
			अगर (map->queues[i] == index) अणु
				set_bit(j, mask);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
out_no_maps:
	rcu_पढ़ो_unlock();

	len = biपंचांगap_prपूर्णांक_to_pagebuf(false, buf, mask, nr_ids);
	biपंचांगap_मुक्त(mask);

	वापस len < PAGE_SIZE ? len : -EINVAL;
पूर्ण

अटल sमाप_प्रकार xps_cpus_show(काष्ठा netdev_queue *queue, अक्षर *buf)
अणु
	काष्ठा net_device *dev = queue->dev;
	अचिन्हित पूर्णांक index;
	पूर्णांक len, tc;

	अगर (!netअगर_is_multiqueue(dev))
		वापस -ENOENT;

	index = get_netdev_queue_index(queue);

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	/* If queue beदीर्घs to subordinate dev use its map */
	dev = netdev_get_tx_queue(dev, index)->sb_dev ? : dev;

	tc = netdev_txq_to_tc(dev, index);
	अगर (tc < 0) अणु
		rtnl_unlock();
		वापस -EINVAL;
	पूर्ण

	/* Make sure the subordinate device can't be मुक्तd */
	get_device(&dev->dev);
	rtnl_unlock();

	len = xps_queue_show(dev, index, tc, buf, XPS_CPUS);

	put_device(&dev->dev);
	वापस len;
पूर्ण

अटल sमाप_प्रकार xps_cpus_store(काष्ठा netdev_queue *queue,
			      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा net_device *dev = queue->dev;
	अचिन्हित पूर्णांक index;
	cpumask_var_t mask;
	पूर्णांक err;

	अगर (!netअगर_is_multiqueue(dev))
		वापस -ENOENT;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!alloc_cpumask_var(&mask, GFP_KERNEL))
		वापस -ENOMEM;

	index = get_netdev_queue_index(queue);

	err = biपंचांगap_parse(buf, len, cpumask_bits(mask), nr_cpumask_bits);
	अगर (err) अणु
		मुक्त_cpumask_var(mask);
		वापस err;
	पूर्ण

	अगर (!rtnl_trylock()) अणु
		मुक्त_cpumask_var(mask);
		वापस restart_syscall();
	पूर्ण

	err = netअगर_set_xps_queue(dev, mask, index);
	rtnl_unlock();

	मुक्त_cpumask_var(mask);

	वापस err ? : len;
पूर्ण

अटल काष्ठा netdev_queue_attribute xps_cpus_attribute __ro_after_init
	= __ATTR_RW(xps_cpus);

अटल sमाप_प्रकार xps_rxqs_show(काष्ठा netdev_queue *queue, अक्षर *buf)
अणु
	काष्ठा net_device *dev = queue->dev;
	अचिन्हित पूर्णांक index;
	पूर्णांक tc;

	index = get_netdev_queue_index(queue);

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	tc = netdev_txq_to_tc(dev, index);
	rtnl_unlock();
	अगर (tc < 0)
		वापस -EINVAL;

	वापस xps_queue_show(dev, index, tc, buf, XPS_RXQS);
पूर्ण

अटल sमाप_प्रकार xps_rxqs_store(काष्ठा netdev_queue *queue, स्थिर अक्षर *buf,
			      माप_प्रकार len)
अणु
	काष्ठा net_device *dev = queue->dev;
	काष्ठा net *net = dev_net(dev);
	अचिन्हित दीर्घ *mask;
	अचिन्हित पूर्णांक index;
	पूर्णांक err;

	अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	mask = biपंचांगap_zalloc(dev->num_rx_queues, GFP_KERNEL);
	अगर (!mask)
		वापस -ENOMEM;

	index = get_netdev_queue_index(queue);

	err = biपंचांगap_parse(buf, len, mask, dev->num_rx_queues);
	अगर (err) अणु
		biपंचांगap_मुक्त(mask);
		वापस err;
	पूर्ण

	अगर (!rtnl_trylock()) अणु
		biपंचांगap_मुक्त(mask);
		वापस restart_syscall();
	पूर्ण

	cpus_पढ़ो_lock();
	err = __netअगर_set_xps_queue(dev, mask, index, XPS_RXQS);
	cpus_पढ़ो_unlock();

	rtnl_unlock();

	biपंचांगap_मुक्त(mask);
	वापस err ? : len;
पूर्ण

अटल काष्ठा netdev_queue_attribute xps_rxqs_attribute __ro_after_init
	= __ATTR_RW(xps_rxqs);
#पूर्ण_अगर /* CONFIG_XPS */

अटल काष्ठा attribute *netdev_queue_शेष_attrs[] __ro_after_init = अणु
	&queue_trans_समयout.attr,
	&queue_traffic_class.attr,
#अगर_घोषित CONFIG_XPS
	&xps_cpus_attribute.attr,
	&xps_rxqs_attribute.attr,
	&queue_tx_maxrate.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(netdev_queue_शेष);

अटल व्योम netdev_queue_release(काष्ठा kobject *kobj)
अणु
	काष्ठा netdev_queue *queue = to_netdev_queue(kobj);

	स_रखो(kobj, 0, माप(*kobj));
	dev_put(queue->dev);
पूर्ण

अटल स्थिर व्योम *netdev_queue_namespace(काष्ठा kobject *kobj)
अणु
	काष्ठा netdev_queue *queue = to_netdev_queue(kobj);
	काष्ठा device *dev = &queue->dev->dev;
	स्थिर व्योम *ns = शून्य;

	अगर (dev->class && dev->class->ns_type)
		ns = dev->class->namespace(dev);

	वापस ns;
पूर्ण

अटल व्योम netdev_queue_get_ownership(काष्ठा kobject *kobj,
				       kuid_t *uid, kgid_t *gid)
अणु
	स्थिर काष्ठा net *net = netdev_queue_namespace(kobj);

	net_ns_get_ownership(net, uid, gid);
पूर्ण

अटल काष्ठा kobj_type netdev_queue_ktype __ro_after_init = अणु
	.sysfs_ops = &netdev_queue_sysfs_ops,
	.release = netdev_queue_release,
	.शेष_groups = netdev_queue_शेष_groups,
	.namespace = netdev_queue_namespace,
	.get_ownership = netdev_queue_get_ownership,
पूर्ण;

अटल पूर्णांक netdev_queue_add_kobject(काष्ठा net_device *dev, पूर्णांक index)
अणु
	काष्ठा netdev_queue *queue = dev->_tx + index;
	काष्ठा kobject *kobj = &queue->kobj;
	पूर्णांक error = 0;

	/* Kobject_put later will trigger netdev_queue_release call
	 * which decreases dev refcount: Take that reference here
	 */
	dev_hold(queue->dev);

	kobj->kset = dev->queues_kset;
	error = kobject_init_and_add(kobj, &netdev_queue_ktype, शून्य,
				     "tx-%u", index);
	अगर (error)
		जाओ err;

#अगर_घोषित CONFIG_BQL
	error = sysfs_create_group(kobj, &dql_group);
	अगर (error)
		जाओ err;
#पूर्ण_अगर

	kobject_uevent(kobj, KOBJ_ADD);
	वापस 0;

err:
	kobject_put(kobj);
	वापस error;
पूर्ण

अटल पूर्णांक tx_queue_change_owner(काष्ठा net_device *ndev, पूर्णांक index,
				 kuid_t kuid, kgid_t kgid)
अणु
	काष्ठा netdev_queue *queue = ndev->_tx + index;
	काष्ठा kobject *kobj = &queue->kobj;
	पूर्णांक error;

	error = sysfs_change_owner(kobj, kuid, kgid);
	अगर (error)
		वापस error;

#अगर_घोषित CONFIG_BQL
	error = sysfs_group_change_owner(kobj, &dql_group, kuid, kgid);
#पूर्ण_अगर
	वापस error;
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSFS */

पूर्णांक
netdev_queue_update_kobjects(काष्ठा net_device *dev, पूर्णांक old_num, पूर्णांक new_num)
अणु
#अगर_घोषित CONFIG_SYSFS
	पूर्णांक i;
	पूर्णांक error = 0;

	क्रम (i = old_num; i < new_num; i++) अणु
		error = netdev_queue_add_kobject(dev, i);
		अगर (error) अणु
			new_num = old_num;
			अवरोध;
		पूर्ण
	पूर्ण

	जबतक (--i >= new_num) अणु
		काष्ठा netdev_queue *queue = dev->_tx + i;

		अगर (!refcount_पढ़ो(&dev_net(dev)->ns.count))
			queue->kobj.uevent_suppress = 1;
#अगर_घोषित CONFIG_BQL
		sysfs_हटाओ_group(&queue->kobj, &dql_group);
#पूर्ण_अगर
		kobject_put(&queue->kobj);
	पूर्ण

	वापस error;
#अन्यथा
	वापस 0;
#पूर्ण_अगर /* CONFIG_SYSFS */
पूर्ण

अटल पूर्णांक net_tx_queue_change_owner(काष्ठा net_device *dev, पूर्णांक num,
				     kuid_t kuid, kgid_t kgid)
अणु
#अगर_घोषित CONFIG_SYSFS
	पूर्णांक error = 0;
	पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		error = tx_queue_change_owner(dev, i, kuid, kgid);
		अगर (error)
			अवरोध;
	पूर्ण

	वापस error;
#अन्यथा
	वापस 0;
#पूर्ण_अगर /* CONFIG_SYSFS */
पूर्ण

अटल पूर्णांक रेजिस्टर_queue_kobjects(काष्ठा net_device *dev)
अणु
	पूर्णांक error = 0, txq = 0, rxq = 0, real_rx = 0, real_tx = 0;

#अगर_घोषित CONFIG_SYSFS
	dev->queues_kset = kset_create_and_add("queues",
					       शून्य, &dev->dev.kobj);
	अगर (!dev->queues_kset)
		वापस -ENOMEM;
	real_rx = dev->real_num_rx_queues;
#पूर्ण_अगर
	real_tx = dev->real_num_tx_queues;

	error = net_rx_queue_update_kobjects(dev, 0, real_rx);
	अगर (error)
		जाओ error;
	rxq = real_rx;

	error = netdev_queue_update_kobjects(dev, 0, real_tx);
	अगर (error)
		जाओ error;
	txq = real_tx;

	वापस 0;

error:
	netdev_queue_update_kobjects(dev, txq, 0);
	net_rx_queue_update_kobjects(dev, rxq, 0);
#अगर_घोषित CONFIG_SYSFS
	kset_unरेजिस्टर(dev->queues_kset);
#पूर्ण_अगर
	वापस error;
पूर्ण

अटल पूर्णांक queue_change_owner(काष्ठा net_device *ndev, kuid_t kuid, kgid_t kgid)
अणु
	पूर्णांक error = 0, real_rx = 0, real_tx = 0;

#अगर_घोषित CONFIG_SYSFS
	अगर (ndev->queues_kset) अणु
		error = sysfs_change_owner(&ndev->queues_kset->kobj, kuid, kgid);
		अगर (error)
			वापस error;
	पूर्ण
	real_rx = ndev->real_num_rx_queues;
#पूर्ण_अगर
	real_tx = ndev->real_num_tx_queues;

	error = net_rx_queue_change_owner(ndev, real_rx, kuid, kgid);
	अगर (error)
		वापस error;

	error = net_tx_queue_change_owner(ndev, real_tx, kuid, kgid);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल व्योम हटाओ_queue_kobjects(काष्ठा net_device *dev)
अणु
	पूर्णांक real_rx = 0, real_tx = 0;

#अगर_घोषित CONFIG_SYSFS
	real_rx = dev->real_num_rx_queues;
#पूर्ण_अगर
	real_tx = dev->real_num_tx_queues;

	net_rx_queue_update_kobjects(dev, real_rx, 0);
	netdev_queue_update_kobjects(dev, real_tx, 0);
#अगर_घोषित CONFIG_SYSFS
	kset_unरेजिस्टर(dev->queues_kset);
#पूर्ण_अगर
पूर्ण

अटल bool net_current_may_mount(व्योम)
अणु
	काष्ठा net *net = current->nsproxy->net_ns;

	वापस ns_capable(net->user_ns, CAP_SYS_ADMIN);
पूर्ण

अटल व्योम *net_grab_current_ns(व्योम)
अणु
	काष्ठा net *ns = current->nsproxy->net_ns;
#अगर_घोषित CONFIG_NET_NS
	अगर (ns)
		refcount_inc(&ns->passive);
#पूर्ण_अगर
	वापस ns;
पूर्ण

अटल स्थिर व्योम *net_initial_ns(व्योम)
अणु
	वापस &init_net;
पूर्ण

अटल स्थिर व्योम *net_netlink_ns(काष्ठा sock *sk)
अणु
	वापस sock_net(sk);
पूर्ण

स्थिर काष्ठा kobj_ns_type_operations net_ns_type_operations = अणु
	.type = KOBJ_NS_TYPE_NET,
	.current_may_mount = net_current_may_mount,
	.grab_current_ns = net_grab_current_ns,
	.netlink_ns = net_netlink_ns,
	.initial_ns = net_initial_ns,
	.drop_ns = net_drop_ns,
पूर्ण;
EXPORT_SYMBOL_GPL(net_ns_type_operations);

अटल पूर्णांक netdev_uevent(काष्ठा device *d, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा net_device *dev = to_net_dev(d);
	पूर्णांक retval;

	/* pass पूर्णांकerface to uevent. */
	retval = add_uevent_var(env, "INTERFACE=%s", dev->name);
	अगर (retval)
		जाओ निकास;

	/* pass अगरindex to uevent.
	 * अगरindex is useful as it won't change (पूर्णांकerface name may change)
	 * and is what RtNetlink uses natively.
	 */
	retval = add_uevent_var(env, "IFINDEX=%d", dev->अगरindex);

निकास:
	वापस retval;
पूर्ण

/*
 *	netdev_release -- destroy and मुक्त a dead device.
 *	Called when last reference to device kobject is gone.
 */
अटल व्योम netdev_release(काष्ठा device *d)
अणु
	काष्ठा net_device *dev = to_net_dev(d);

	BUG_ON(dev->reg_state != NETREG_RELEASED);

	/* no need to रुको क्रम rcu grace period:
	 * device is dead and about to be मुक्तd.
	 */
	kमुक्त(rcu_access_poपूर्णांकer(dev->अगरalias));
	netdev_मुक्तmem(dev);
पूर्ण

अटल स्थिर व्योम *net_namespace(काष्ठा device *d)
अणु
	काष्ठा net_device *dev = to_net_dev(d);

	वापस dev_net(dev);
पूर्ण

अटल व्योम net_get_ownership(काष्ठा device *d, kuid_t *uid, kgid_t *gid)
अणु
	काष्ठा net_device *dev = to_net_dev(d);
	स्थिर काष्ठा net *net = dev_net(dev);

	net_ns_get_ownership(net, uid, gid);
पूर्ण

अटल काष्ठा class net_class __ro_after_init = अणु
	.name = "net",
	.dev_release = netdev_release,
	.dev_groups = net_class_groups,
	.dev_uevent = netdev_uevent,
	.ns_type = &net_ns_type_operations,
	.namespace = net_namespace,
	.get_ownership = net_get_ownership,
पूर्ण;

#अगर_घोषित CONFIG_OF_NET
अटल पूर्णांक of_dev_node_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	क्रम (; dev; dev = dev->parent) अणु
		अगर (dev->of_node == data)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * of_find_net_device_by_node - lookup the net device क्रम the device node
 * @np: OF device node
 *
 * Looks up the net_device काष्ठाure corresponding with the device node.
 * If successful, वापसs a poपूर्णांकer to the net_device with the embedded
 * काष्ठा device refcount incremented by one, or शून्य on failure. The
 * refcount must be dropped when करोne with the net_device.
 */
काष्ठा net_device *of_find_net_device_by_node(काष्ठा device_node *np)
अणु
	काष्ठा device *dev;

	dev = class_find_device(&net_class, शून्य, np, of_dev_node_match);
	अगर (!dev)
		वापस शून्य;

	वापस to_net_dev(dev);
पूर्ण
EXPORT_SYMBOL(of_find_net_device_by_node);
#पूर्ण_अगर

/* Delete sysfs entries but hold kobject reference until after all
 * netdev references are gone.
 */
व्योम netdev_unरेजिस्टर_kobject(काष्ठा net_device *ndev)
अणु
	काष्ठा device *dev = &ndev->dev;

	अगर (!refcount_पढ़ो(&dev_net(ndev)->ns.count))
		dev_set_uevent_suppress(dev, 1);

	kobject_get(&dev->kobj);

	हटाओ_queue_kobjects(ndev);

	pm_runसमय_set_meदो_स्मृति_noio(dev, false);

	device_del(dev);
पूर्ण

/* Create sysfs entries क्रम network device. */
पूर्णांक netdev_रेजिस्टर_kobject(काष्ठा net_device *ndev)
अणु
	काष्ठा device *dev = &ndev->dev;
	स्थिर काष्ठा attribute_group **groups = ndev->sysfs_groups;
	पूर्णांक error = 0;

	device_initialize(dev);
	dev->class = &net_class;
	dev->platक्रमm_data = ndev;
	dev->groups = groups;

	dev_set_name(dev, "%s", ndev->name);

#अगर_घोषित CONFIG_SYSFS
	/* Allow क्रम a device specअगरic group */
	अगर (*groups)
		groups++;

	*groups++ = &netstat_group;

#अगर IS_ENABLED(CONFIG_WIRELESS_EXT) || IS_ENABLED(CONFIG_CFG80211)
	अगर (ndev->ieee80211_ptr)
		*groups++ = &wireless_group;
#अगर IS_ENABLED(CONFIG_WIRELESS_EXT)
	अन्यथा अगर (ndev->wireless_handlers)
		*groups++ = &wireless_group;
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_SYSFS */

	error = device_add(dev);
	अगर (error)
		वापस error;

	error = रेजिस्टर_queue_kobjects(ndev);
	अगर (error) अणु
		device_del(dev);
		वापस error;
	पूर्ण

	pm_runसमय_set_meदो_स्मृति_noio(dev, true);

	वापस error;
पूर्ण

/* Change owner क्रम sysfs entries when moving network devices across network
 * namespaces owned by dअगरferent user namespaces.
 */
पूर्णांक netdev_change_owner(काष्ठा net_device *ndev, स्थिर काष्ठा net *net_old,
			स्थिर काष्ठा net *net_new)
अणु
	काष्ठा device *dev = &ndev->dev;
	kuid_t old_uid, new_uid;
	kgid_t old_gid, new_gid;
	पूर्णांक error;

	net_ns_get_ownership(net_old, &old_uid, &old_gid);
	net_ns_get_ownership(net_new, &new_uid, &new_gid);

	/* The network namespace was changed but the owning user namespace is
	 * identical so there's no need to change the owner of sysfs entries.
	 */
	अगर (uid_eq(old_uid, new_uid) && gid_eq(old_gid, new_gid))
		वापस 0;

	error = device_change_owner(dev, new_uid, new_gid);
	अगर (error)
		वापस error;

	error = queue_change_owner(ndev, new_uid, new_gid);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

पूर्णांक netdev_class_create_file_ns(स्थिर काष्ठा class_attribute *class_attr,
				स्थिर व्योम *ns)
अणु
	वापस class_create_file_ns(&net_class, class_attr, ns);
पूर्ण
EXPORT_SYMBOL(netdev_class_create_file_ns);

व्योम netdev_class_हटाओ_file_ns(स्थिर काष्ठा class_attribute *class_attr,
				 स्थिर व्योम *ns)
अणु
	class_हटाओ_file_ns(&net_class, class_attr, ns);
पूर्ण
EXPORT_SYMBOL(netdev_class_हटाओ_file_ns);

पूर्णांक __init netdev_kobject_init(व्योम)
अणु
	kobj_ns_type_रेजिस्टर(&net_ns_type_operations);
	वापस class_रेजिस्टर(&net_class);
पूर्ण
