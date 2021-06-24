<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007-2012 Nicira, Inc.
 */

#समावेश <linux/netdevice.h>
#समावेश <net/genetlink.h>
#समावेश <net/netns/generic.h>

#समावेश "datapath.h"
#समावेश "vport-internal_dev.h"
#समावेश "vport-netdev.h"

अटल व्योम dp_detach_port_notअगरy(काष्ठा vport *vport)
अणु
	काष्ठा sk_buff *notअगरy;
	काष्ठा datapath *dp;

	dp = vport->dp;
	notअगरy = ovs_vport_cmd_build_info(vport, ovs_dp_get_net(dp),
					  0, 0, OVS_VPORT_CMD_DEL);
	ovs_dp_detach_port(vport);
	अगर (IS_ERR(notअगरy)) अणु
		genl_set_err(&dp_vport_genl_family, ovs_dp_get_net(dp), 0,
			     0, PTR_ERR(notअगरy));
		वापस;
	पूर्ण

	genlmsg_multicast_netns(&dp_vport_genl_family,
				ovs_dp_get_net(dp), notअगरy, 0,
				0, GFP_KERNEL);
पूर्ण

व्योम ovs_dp_notअगरy_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ovs_net *ovs_net = container_of(work, काष्ठा ovs_net, dp_notअगरy_work);
	काष्ठा datapath *dp;

	ovs_lock();
	list_क्रम_each_entry(dp, &ovs_net->dps, list_node) अणु
		पूर्णांक i;

		क्रम (i = 0; i < DP_VPORT_HASH_BUCKETS; i++) अणु
			काष्ठा vport *vport;
			काष्ठा hlist_node *n;

			hlist_क्रम_each_entry_safe(vport, n, &dp->ports[i], dp_hash_node) अणु
				अगर (vport->ops->type == OVS_VPORT_TYPE_INTERNAL)
					जारी;

				अगर (!(netअगर_is_ovs_port(vport->dev)))
					dp_detach_port_notअगरy(vport);
			पूर्ण
		पूर्ण
	पूर्ण
	ovs_unlock();
पूर्ण

अटल पूर्णांक dp_device_event(काष्ठा notअगरier_block *unused, अचिन्हित दीर्घ event,
			   व्योम *ptr)
अणु
	काष्ठा ovs_net *ovs_net;
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा vport *vport = शून्य;

	अगर (!ovs_is_पूर्णांकernal_dev(dev))
		vport = ovs_netdev_get_vport(dev);

	अगर (!vport)
		वापस NOTIFY_DONE;

	अगर (event == NETDEV_UNREGISTER) अणु
		/* upper_dev_unlink and decrement promisc immediately */
		ovs_netdev_detach_dev(vport);

		/* schedule vport destroy, dev_put and genl notअगरication */
		ovs_net = net_generic(dev_net(dev), ovs_net_id);
		queue_work(प्रणाली_wq, &ovs_net->dp_notअगरy_work);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

काष्ठा notअगरier_block ovs_dp_device_notअगरier = अणु
	.notअगरier_call = dp_device_event
पूर्ण;
