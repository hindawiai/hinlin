<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020 Facebook Inc.

#समावेश <linux/debugfs.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <net/udp_tunnel.h>

#समावेश "netdevsim.h"

अटल पूर्णांक
nsim_udp_tunnel_set_port(काष्ठा net_device *dev, अचिन्हित पूर्णांक table,
			 अचिन्हित पूर्णांक entry, काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	पूर्णांक ret;

	ret = -ns->udp_ports.inject_error;
	ns->udp_ports.inject_error = 0;

	अगर (ns->udp_ports.sleep)
		msleep(ns->udp_ports.sleep);

	अगर (!ret) अणु
		अगर (ns->udp_ports.ports[table][entry]) अणु
			WARN(1, "entry already in use\n");
			ret = -EBUSY;
		पूर्ण अन्यथा अणु
			ns->udp_ports.ports[table][entry] =
				be16_to_cpu(ti->port) << 16 | ti->type;
		पूर्ण
	पूर्ण

	netdev_info(dev, "set [%d, %d] type %d family %d port %d - %d\n",
		    table, entry, ti->type, ti->sa_family, ntohs(ti->port),
		    ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
nsim_udp_tunnel_unset_port(काष्ठा net_device *dev, अचिन्हित पूर्णांक table,
			   अचिन्हित पूर्णांक entry, काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	पूर्णांक ret;

	ret = -ns->udp_ports.inject_error;
	ns->udp_ports.inject_error = 0;

	अगर (ns->udp_ports.sleep)
		msleep(ns->udp_ports.sleep);
	अगर (!ret) अणु
		u32 val = be16_to_cpu(ti->port) << 16 | ti->type;

		अगर (val == ns->udp_ports.ports[table][entry]) अणु
			ns->udp_ports.ports[table][entry] = 0;
		पूर्ण अन्यथा अणु
			WARN(1, "entry not installed %x vs %x\n",
			     val, ns->udp_ports.ports[table][entry]);
			ret = -ENOENT;
		पूर्ण
	पूर्ण

	netdev_info(dev, "unset [%d, %d] type %d family %d port %d - %d\n",
		    table, entry, ti->type, ti->sa_family, ntohs(ti->port),
		    ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
nsim_udp_tunnel_sync_table(काष्ठा net_device *dev, अचिन्हित पूर्णांक table)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	काष्ठा udp_tunnel_info ti;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = -ns->udp_ports.inject_error;
	ns->udp_ports.inject_error = 0;

	क्रम (i = 0; i < NSIM_UDP_TUNNEL_N_PORTS; i++) अणु
		udp_tunnel_nic_get_port(dev, table, i, &ti);
		ns->udp_ports.ports[table][i] =
			be16_to_cpu(ti.port) << 16 | ti.type;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info nsim_udp_tunnel_info = अणु
	.set_port	= nsim_udp_tunnel_set_port,
	.unset_port	= nsim_udp_tunnel_unset_port,
	.sync_table	= nsim_udp_tunnel_sync_table,

	.tables = अणु
		अणु
			.n_entries	= NSIM_UDP_TUNNEL_N_PORTS,
			.tunnel_types	= UDP_TUNNEL_TYPE_VXLAN,
		पूर्ण,
		अणु
			.n_entries	= NSIM_UDP_TUNNEL_N_PORTS,
			.tunnel_types	= UDP_TUNNEL_TYPE_GENEVE |
					  UDP_TUNNEL_TYPE_VXLAN_GPE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल sमाप_प्रकार
nsim_udp_tunnels_info_reset_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा net_device *dev = file->निजी_data;
	काष्ठा netdevsim *ns = netdev_priv(dev);

	स_रखो(ns->udp_ports.ports, 0, माप(ns->udp_ports.__ports));
	rtnl_lock();
	udp_tunnel_nic_reset_ntf(dev);
	rtnl_unlock();

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations nsim_udp_tunnels_info_reset_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = nsim_udp_tunnels_info_reset_ग_लिखो,
	.llseek = generic_file_llseek,
	.owner = THIS_MODULE,
पूर्ण;

पूर्णांक nsim_udp_tunnels_info_create(काष्ठा nsim_dev *nsim_dev,
				 काष्ठा net_device *dev)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	काष्ठा udp_tunnel_nic_info *info;

	अगर (nsim_dev->udp_ports.shared && nsim_dev->udp_ports.खोलो_only) अणु
		dev_err(&nsim_dev->nsim_bus_dev->dev,
			"shared can't be used in conjunction with open_only\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!nsim_dev->udp_ports.shared)
		ns->udp_ports.ports = ns->udp_ports.__ports;
	अन्यथा
		ns->udp_ports.ports = nsim_dev->udp_ports.__ports;

	debugfs_create_u32("udp_ports_inject_error", 0600,
			   ns->nsim_dev_port->ddir,
			   &ns->udp_ports.inject_error);

	ns->udp_ports.dfs_ports[0].array = ns->udp_ports.ports[0];
	ns->udp_ports.dfs_ports[0].n_elements = NSIM_UDP_TUNNEL_N_PORTS;
	debugfs_create_u32_array("udp_ports_table0", 0400,
				 ns->nsim_dev_port->ddir,
				 &ns->udp_ports.dfs_ports[0]);

	ns->udp_ports.dfs_ports[1].array = ns->udp_ports.ports[1];
	ns->udp_ports.dfs_ports[1].n_elements = NSIM_UDP_TUNNEL_N_PORTS;
	debugfs_create_u32_array("udp_ports_table1", 0400,
				 ns->nsim_dev_port->ddir,
				 &ns->udp_ports.dfs_ports[1]);

	debugfs_create_file("udp_ports_reset", 0200, ns->nsim_dev_port->ddir,
			    dev, &nsim_udp_tunnels_info_reset_fops);

	/* Note: it's not normal to allocate the info काष्ठा like this!
	 * Drivers are expected to use a अटल स्थिर one, here we're testing.
	 */
	info = kmemdup(&nsim_udp_tunnel_info, माप(nsim_udp_tunnel_info),
		       GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	ns->udp_ports.sleep = nsim_dev->udp_ports.sleep;

	अगर (nsim_dev->udp_ports.sync_all) अणु
		info->set_port = शून्य;
		info->unset_port = शून्य;
	पूर्ण अन्यथा अणु
		info->sync_table = शून्य;
	पूर्ण

	अगर (ns->udp_ports.sleep)
		info->flags |= UDP_TUNNEL_NIC_INFO_MAY_SLEEP;
	अगर (nsim_dev->udp_ports.खोलो_only)
		info->flags |= UDP_TUNNEL_NIC_INFO_OPEN_ONLY;
	अगर (nsim_dev->udp_ports.ipv4_only)
		info->flags |= UDP_TUNNEL_NIC_INFO_IPV4_ONLY;
	अगर (nsim_dev->udp_ports.shared)
		info->shared = &nsim_dev->udp_ports.utn_shared;
	अगर (nsim_dev->udp_ports.अटल_iana_vxlan)
		info->flags |= UDP_TUNNEL_NIC_INFO_STATIC_IANA_VXLAN;

	dev->udp_tunnel_nic_info = info;
	वापस 0;
पूर्ण

व्योम nsim_udp_tunnels_info_destroy(काष्ठा net_device *dev)
अणु
	kमुक्त(dev->udp_tunnel_nic_info);
	dev->udp_tunnel_nic_info = शून्य;
पूर्ण

व्योम nsim_udp_tunnels_debugfs_create(काष्ठा nsim_dev *nsim_dev)
अणु
	debugfs_create_bool("udp_ports_sync_all", 0600, nsim_dev->ddir,
			    &nsim_dev->udp_ports.sync_all);
	debugfs_create_bool("udp_ports_open_only", 0600, nsim_dev->ddir,
			    &nsim_dev->udp_ports.खोलो_only);
	debugfs_create_bool("udp_ports_ipv4_only", 0600, nsim_dev->ddir,
			    &nsim_dev->udp_ports.ipv4_only);
	debugfs_create_bool("udp_ports_shared", 0600, nsim_dev->ddir,
			    &nsim_dev->udp_ports.shared);
	debugfs_create_bool("udp_ports_static_iana_vxlan", 0600, nsim_dev->ddir,
			    &nsim_dev->udp_ports.अटल_iana_vxlan);
	debugfs_create_u32("udp_ports_sleep", 0600, nsim_dev->ddir,
			   &nsim_dev->udp_ports.sleep);
पूर्ण
