<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		802.1Q VLAN
 *		Ethernet-type device handling.
 *
 * Authors:	Ben Greear <greearb@candelatech.com>
 *              Please send support related email to: netdev@vger.kernel.org
 *              VLAN Home Page: http://www.candelatech.com/~greear/vlan.hपंचांगl
 *
 * Fixes:
 *              Fix क्रम packet capture - Nick Eggleston <nick@dccinc.com>;
 *		Add HW acceleration hooks - David S. Miller <davem@redhat.com>;
 *		Correct all the locking - David S. Miller <davem@redhat.com>;
 *		Use hash table क्रम VLAN groups - David S. Miller <davem@redhat.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/rculist.h>
#समावेश <net/p8022.h>
#समावेश <net/arp.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/notअगरier.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/अगर_vlan.h>
#समावेश "vlan.h"
#समावेश "vlanproc.h"

#घोषणा DRV_VERSION "1.8"

/* Global VLAN variables */

अचिन्हित पूर्णांक vlan_net_id __पढ़ो_mostly;

स्थिर अक्षर vlan_fullname[] = "802.1Q VLAN Support";
स्थिर अक्षर vlan_version[] = DRV_VERSION;

/* End of global variables definitions. */

अटल पूर्णांक vlan_group_pपुनः_स्मृति_vid(काष्ठा vlan_group *vg,
				   __be16 vlan_proto, u16 vlan_id)
अणु
	काष्ठा net_device **array;
	अचिन्हित पूर्णांक vidx;
	अचिन्हित पूर्णांक size;
	पूर्णांक pidx;

	ASSERT_RTNL();

	pidx  = vlan_proto_idx(vlan_proto);
	अगर (pidx < 0)
		वापस -EINVAL;

	vidx  = vlan_id / VLAN_GROUP_ARRAY_PART_LEN;
	array = vg->vlan_devices_arrays[pidx][vidx];
	अगर (array != शून्य)
		वापस 0;

	size = माप(काष्ठा net_device *) * VLAN_GROUP_ARRAY_PART_LEN;
	array = kzalloc(size, GFP_KERNEL);
	अगर (array == शून्य)
		वापस -ENOBUFS;

	/* paired with smp_rmb() in __vlan_group_get_device() */
	smp_wmb();

	vg->vlan_devices_arrays[pidx][vidx] = array;
	वापस 0;
पूर्ण

अटल व्योम vlan_stacked_transfer_operstate(स्थिर काष्ठा net_device *rootdev,
					    काष्ठा net_device *dev,
					    काष्ठा vlan_dev_priv *vlan)
अणु
	अगर (!(vlan->flags & VLAN_FLAG_BRIDGE_BINDING))
		netअगर_stacked_transfer_operstate(rootdev, dev);
पूर्ण

व्योम unरेजिस्टर_vlan_dev(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	काष्ठा net_device *real_dev = vlan->real_dev;
	काष्ठा vlan_info *vlan_info;
	काष्ठा vlan_group *grp;
	u16 vlan_id = vlan->vlan_id;

	ASSERT_RTNL();

	vlan_info = rtnl_dereference(real_dev->vlan_info);
	BUG_ON(!vlan_info);

	grp = &vlan_info->grp;

	grp->nr_vlan_devs--;

	अगर (vlan->flags & VLAN_FLAG_MVRP)
		vlan_mvrp_request_leave(dev);
	अगर (vlan->flags & VLAN_FLAG_GVRP)
		vlan_gvrp_request_leave(dev);

	vlan_group_set_device(grp, vlan->vlan_proto, vlan_id, शून्य);

	netdev_upper_dev_unlink(real_dev, dev);
	/* Because unरेजिस्टर_netdevice_queue() makes sure at least one rcu
	 * grace period is respected beक्रमe device मुक्तing,
	 * we करोnt need to call synchronize_net() here.
	 */
	unरेजिस्टर_netdevice_queue(dev, head);

	अगर (grp->nr_vlan_devs == 0) अणु
		vlan_mvrp_uninit_applicant(real_dev);
		vlan_gvrp_uninit_applicant(real_dev);
	पूर्ण

	vlan_vid_del(real_dev, vlan->vlan_proto, vlan_id);

	/* Get rid of the vlan's reference to real_dev */
	dev_put(real_dev);
पूर्ण

पूर्णांक vlan_check_real_dev(काष्ठा net_device *real_dev,
			__be16 protocol, u16 vlan_id,
			काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर अक्षर *name = real_dev->name;

	अगर (real_dev->features & NETIF_F_VLAN_CHALLENGED) अणु
		pr_info("VLANs not supported on %s\n", name);
		NL_SET_ERR_MSG_MOD(extack, "VLANs not supported on device");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (vlan_find_dev(real_dev, protocol, vlan_id) != शून्य) अणु
		NL_SET_ERR_MSG_MOD(extack, "VLAN device already exists");
		वापस -EEXIST;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक रेजिस्टर_vlan_dev(काष्ठा net_device *dev, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	काष्ठा net_device *real_dev = vlan->real_dev;
	u16 vlan_id = vlan->vlan_id;
	काष्ठा vlan_info *vlan_info;
	काष्ठा vlan_group *grp;
	पूर्णांक err;

	err = vlan_vid_add(real_dev, vlan->vlan_proto, vlan_id);
	अगर (err)
		वापस err;

	vlan_info = rtnl_dereference(real_dev->vlan_info);
	/* vlan_info should be there now. vlan_vid_add took care of it */
	BUG_ON(!vlan_info);

	grp = &vlan_info->grp;
	अगर (grp->nr_vlan_devs == 0) अणु
		err = vlan_gvrp_init_applicant(real_dev);
		अगर (err < 0)
			जाओ out_vid_del;
		err = vlan_mvrp_init_applicant(real_dev);
		अगर (err < 0)
			जाओ out_uninit_gvrp;
	पूर्ण

	err = vlan_group_pपुनः_स्मृति_vid(grp, vlan->vlan_proto, vlan_id);
	अगर (err < 0)
		जाओ out_uninit_mvrp;

	err = रेजिस्टर_netdevice(dev);
	अगर (err < 0)
		जाओ out_uninit_mvrp;

	err = netdev_upper_dev_link(real_dev, dev, extack);
	अगर (err)
		जाओ out_unरेजिस्टर_netdev;

	/* Account क्रम reference in काष्ठा vlan_dev_priv */
	dev_hold(real_dev);

	vlan_stacked_transfer_operstate(real_dev, dev, vlan);
	linkwatch_fire_event(dev); /* _MUST_ call rfc2863_policy() */

	/* So, got the sucker initialized, now lets place
	 * it पूर्णांकo our local काष्ठाure.
	 */
	vlan_group_set_device(grp, vlan->vlan_proto, vlan_id, dev);
	grp->nr_vlan_devs++;

	वापस 0;

out_unरेजिस्टर_netdev:
	unरेजिस्टर_netdevice(dev);
out_uninit_mvrp:
	अगर (grp->nr_vlan_devs == 0)
		vlan_mvrp_uninit_applicant(real_dev);
out_uninit_gvrp:
	अगर (grp->nr_vlan_devs == 0)
		vlan_gvrp_uninit_applicant(real_dev);
out_vid_del:
	vlan_vid_del(real_dev, vlan->vlan_proto, vlan_id);
	वापस err;
पूर्ण

/*  Attach a VLAN device to a mac address (ie Ethernet Card).
 *  Returns 0 अगर the device was created or a negative error code otherwise.
 */
अटल पूर्णांक रेजिस्टर_vlan_device(काष्ठा net_device *real_dev, u16 vlan_id)
अणु
	काष्ठा net_device *new_dev;
	काष्ठा vlan_dev_priv *vlan;
	काष्ठा net *net = dev_net(real_dev);
	काष्ठा vlan_net *vn = net_generic(net, vlan_net_id);
	अक्षर name[IFNAMSIZ];
	पूर्णांक err;

	अगर (vlan_id >= VLAN_VID_MASK)
		वापस -दुस्फल;

	err = vlan_check_real_dev(real_dev, htons(ETH_P_8021Q), vlan_id,
				  शून्य);
	अगर (err < 0)
		वापस err;

	/* Gotta set up the fields क्रम the device. */
	चयन (vn->name_type) अणु
	हाल VLAN_NAME_TYPE_RAW_PLUS_VID:
		/* name will look like:	 eth1.0005 */
		snम_लिखो(name, IFNAMSIZ, "%s.%.4i", real_dev->name, vlan_id);
		अवरोध;
	हाल VLAN_NAME_TYPE_PLUS_VID_NO_PAD:
		/* Put our vlan.VID in the name.
		 * Name will look like:	 vlan5
		 */
		snम_लिखो(name, IFNAMSIZ, "vlan%i", vlan_id);
		अवरोध;
	हाल VLAN_NAME_TYPE_RAW_PLUS_VID_NO_PAD:
		/* Put our vlan.VID in the name.
		 * Name will look like:	 eth0.5
		 */
		snम_लिखो(name, IFNAMSIZ, "%s.%i", real_dev->name, vlan_id);
		अवरोध;
	हाल VLAN_NAME_TYPE_PLUS_VID:
		/* Put our vlan.VID in the name.
		 * Name will look like:	 vlan0005
		 */
	शेष:
		snम_लिखो(name, IFNAMSIZ, "vlan%.4i", vlan_id);
	पूर्ण

	new_dev = alloc_netdev(माप(काष्ठा vlan_dev_priv), name,
			       NET_NAME_UNKNOWN, vlan_setup);

	अगर (new_dev == शून्य)
		वापस -ENOBUFS;

	dev_net_set(new_dev, net);
	/* need 4 bytes क्रम extra VLAN header info,
	 * hope the underlying device can handle it.
	 */
	new_dev->mtu = real_dev->mtu;

	vlan = vlan_dev_priv(new_dev);
	vlan->vlan_proto = htons(ETH_P_8021Q);
	vlan->vlan_id = vlan_id;
	vlan->real_dev = real_dev;
	vlan->dent = शून्य;
	vlan->flags = VLAN_FLAG_REORDER_HDR;

	new_dev->rtnl_link_ops = &vlan_link_ops;
	err = रेजिस्टर_vlan_dev(new_dev, शून्य);
	अगर (err < 0)
		जाओ out_मुक्त_newdev;

	वापस 0;

out_मुक्त_newdev:
	मुक्त_netdev(new_dev);
	वापस err;
पूर्ण

अटल व्योम vlan_sync_address(काष्ठा net_device *dev,
			      काष्ठा net_device *vlandev)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(vlandev);

	/* May be called without an actual change */
	अगर (ether_addr_equal(vlan->real_dev_addr, dev->dev_addr))
		वापस;

	/* vlan जारीs to inherit address of lower device */
	अगर (vlan_dev_inherit_address(vlandev, dev))
		जाओ out;

	/* vlan address was dअगरferent from the old address and is equal to
	 * the new address */
	अगर (!ether_addr_equal(vlandev->dev_addr, vlan->real_dev_addr) &&
	    ether_addr_equal(vlandev->dev_addr, dev->dev_addr))
		dev_uc_del(dev, vlandev->dev_addr);

	/* vlan address was equal to the old address and is dअगरferent from
	 * the new address */
	अगर (ether_addr_equal(vlandev->dev_addr, vlan->real_dev_addr) &&
	    !ether_addr_equal(vlandev->dev_addr, dev->dev_addr))
		dev_uc_add(dev, vlandev->dev_addr);

out:
	ether_addr_copy(vlan->real_dev_addr, dev->dev_addr);
पूर्ण

अटल व्योम vlan_transfer_features(काष्ठा net_device *dev,
				   काष्ठा net_device *vlandev)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(vlandev);

	vlandev->gso_max_size = dev->gso_max_size;
	vlandev->gso_max_segs = dev->gso_max_segs;

	अगर (vlan_hw_offload_capable(dev->features, vlan->vlan_proto))
		vlandev->hard_header_len = dev->hard_header_len;
	अन्यथा
		vlandev->hard_header_len = dev->hard_header_len + VLAN_HLEN;

#अगर IS_ENABLED(CONFIG_FCOE)
	vlandev->fcoe_ddp_xid = dev->fcoe_ddp_xid;
#पूर्ण_अगर

	vlandev->priv_flags &= ~IFF_XMIT_DST_RELEASE;
	vlandev->priv_flags |= (vlan->real_dev->priv_flags & IFF_XMIT_DST_RELEASE);
	vlandev->hw_enc_features = vlan_tnl_features(vlan->real_dev);

	netdev_update_features(vlandev);
पूर्ण

अटल पूर्णांक __vlan_device_event(काष्ठा net_device *dev, अचिन्हित दीर्घ event)
अणु
	पूर्णांक err = 0;

	चयन (event) अणु
	हाल NETDEV_CHANGENAME:
		vlan_proc_rem_dev(dev);
		err = vlan_proc_add_dev(dev);
		अवरोध;
	हाल NETDEV_REGISTER:
		err = vlan_proc_add_dev(dev);
		अवरोध;
	हाल NETDEV_UNREGISTER:
		vlan_proc_rem_dev(dev);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक vlan_device_event(काष्ठा notअगरier_block *unused, अचिन्हित दीर्घ event,
			     व्योम *ptr)
अणु
	काष्ठा netlink_ext_ack *extack = netdev_notअगरier_info_to_extack(ptr);
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा vlan_group *grp;
	काष्ठा vlan_info *vlan_info;
	पूर्णांक i, flgs;
	काष्ठा net_device *vlandev;
	काष्ठा vlan_dev_priv *vlan;
	bool last = false;
	LIST_HEAD(list);
	पूर्णांक err;

	अगर (is_vlan_dev(dev)) अणु
		पूर्णांक err = __vlan_device_event(dev, event);

		अगर (err)
			वापस notअगरier_from_त्रुटि_सं(err);
	पूर्ण

	अगर ((event == NETDEV_UP) &&
	    (dev->features & NETIF_F_HW_VLAN_CTAG_FILTER)) अणु
		pr_info("adding VLAN 0 to HW filter on device %s\n",
			dev->name);
		vlan_vid_add(dev, htons(ETH_P_8021Q), 0);
	पूर्ण
	अगर (event == NETDEV_DOWN &&
	    (dev->features & NETIF_F_HW_VLAN_CTAG_FILTER))
		vlan_vid_del(dev, htons(ETH_P_8021Q), 0);

	vlan_info = rtnl_dereference(dev->vlan_info);
	अगर (!vlan_info)
		जाओ out;
	grp = &vlan_info->grp;

	/* It is OK that we करो not hold the group lock right now,
	 * as we run under the RTNL lock.
	 */

	चयन (event) अणु
	हाल NETDEV_CHANGE:
		/* Propagate real device state to vlan devices */
		vlan_group_क्रम_each_dev(grp, i, vlandev)
			vlan_stacked_transfer_operstate(dev, vlandev,
							vlan_dev_priv(vlandev));
		अवरोध;

	हाल NETDEV_CHANGEADDR:
		/* Adjust unicast filters on underlying device */
		vlan_group_क्रम_each_dev(grp, i, vlandev) अणु
			flgs = vlandev->flags;
			अगर (!(flgs & IFF_UP))
				जारी;

			vlan_sync_address(dev, vlandev);
		पूर्ण
		अवरोध;

	हाल NETDEV_CHANGEMTU:
		vlan_group_क्रम_each_dev(grp, i, vlandev) अणु
			अगर (vlandev->mtu <= dev->mtu)
				जारी;

			dev_set_mtu(vlandev, dev->mtu);
		पूर्ण
		अवरोध;

	हाल NETDEV_FEAT_CHANGE:
		/* Propagate device features to underlying device */
		vlan_group_क्रम_each_dev(grp, i, vlandev)
			vlan_transfer_features(dev, vlandev);
		अवरोध;

	हाल NETDEV_DOWN: अणु
		काष्ठा net_device *पंचांगp;
		LIST_HEAD(बंद_list);

		/* Put all VLANs क्रम this dev in the करोwn state too.  */
		vlan_group_क्रम_each_dev(grp, i, vlandev) अणु
			flgs = vlandev->flags;
			अगर (!(flgs & IFF_UP))
				जारी;

			vlan = vlan_dev_priv(vlandev);
			अगर (!(vlan->flags & VLAN_FLAG_LOOSE_BINDING))
				list_add(&vlandev->बंद_list, &बंद_list);
		पूर्ण

		dev_बंद_many(&बंद_list, false);

		list_क्रम_each_entry_safe(vlandev, पंचांगp, &बंद_list, बंद_list) अणु
			vlan_stacked_transfer_operstate(dev, vlandev,
							vlan_dev_priv(vlandev));
			list_del_init(&vlandev->बंद_list);
		पूर्ण
		list_del(&बंद_list);
		अवरोध;
	पूर्ण
	हाल NETDEV_UP:
		/* Put all VLANs क्रम this dev in the up state too.  */
		vlan_group_क्रम_each_dev(grp, i, vlandev) अणु
			flgs = dev_get_flags(vlandev);
			अगर (flgs & IFF_UP)
				जारी;

			vlan = vlan_dev_priv(vlandev);
			अगर (!(vlan->flags & VLAN_FLAG_LOOSE_BINDING))
				dev_change_flags(vlandev, flgs | IFF_UP,
						 extack);
			vlan_stacked_transfer_operstate(dev, vlandev, vlan);
		पूर्ण
		अवरोध;

	हाल NETDEV_UNREGISTER:
		/* twiddle thumbs on netns device moves */
		अगर (dev->reg_state != NETREG_UNREGISTERING)
			अवरोध;

		vlan_group_क्रम_each_dev(grp, i, vlandev) अणु
			/* removal of last vid destroys vlan_info, पात
			 * afterwards */
			अगर (vlan_info->nr_vids == 1)
				last = true;

			unरेजिस्टर_vlan_dev(vlandev, &list);
			अगर (last)
				अवरोध;
		पूर्ण
		unरेजिस्टर_netdevice_many(&list);
		अवरोध;

	हाल NETDEV_PRE_TYPE_CHANGE:
		/* Forbid underlaying device to change its type. */
		अगर (vlan_uses_dev(dev))
			वापस NOTIFY_BAD;
		अवरोध;

	हाल NETDEV_NOTIFY_PEERS:
	हाल NETDEV_BONDING_FAILOVER:
	हाल NETDEV_RESEND_IGMP:
		/* Propagate to vlan devices */
		vlan_group_क्रम_each_dev(grp, i, vlandev)
			call_netdevice_notअगरiers(event, vlandev);
		अवरोध;

	हाल NETDEV_CVLAN_FILTER_PUSH_INFO:
		err = vlan_filter_push_vids(vlan_info, htons(ETH_P_8021Q));
		अगर (err)
			वापस notअगरier_from_त्रुटि_सं(err);
		अवरोध;

	हाल NETDEV_CVLAN_FILTER_DROP_INFO:
		vlan_filter_drop_vids(vlan_info, htons(ETH_P_8021Q));
		अवरोध;

	हाल NETDEV_SVLAN_FILTER_PUSH_INFO:
		err = vlan_filter_push_vids(vlan_info, htons(ETH_P_8021AD));
		अगर (err)
			वापस notअगरier_from_त्रुटि_सं(err);
		अवरोध;

	हाल NETDEV_SVLAN_FILTER_DROP_INFO:
		vlan_filter_drop_vids(vlan_info, htons(ETH_P_8021AD));
		अवरोध;
	पूर्ण

out:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block vlan_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call = vlan_device_event,
पूर्ण;

/*
 *	VLAN IOCTL handler.
 *	o execute requested action or pass command to the device driver
 *   arg is really a काष्ठा vlan_ioctl_args __user *.
 */
अटल पूर्णांक vlan_ioctl_handler(काष्ठा net *net, व्योम __user *arg)
अणु
	पूर्णांक err;
	काष्ठा vlan_ioctl_args args;
	काष्ठा net_device *dev = शून्य;

	अगर (copy_from_user(&args, arg, माप(काष्ठा vlan_ioctl_args)))
		वापस -EFAULT;

	/* Null terminate this sucker, just in हाल. */
	args.device1[माप(args.device1) - 1] = 0;
	args.u.device2[माप(args.u.device2) - 1] = 0;

	rtnl_lock();

	चयन (args.cmd) अणु
	हाल SET_VLAN_INGRESS_PRIORITY_CMD:
	हाल SET_VLAN_EGRESS_PRIORITY_CMD:
	हाल SET_VLAN_FLAG_CMD:
	हाल ADD_VLAN_CMD:
	हाल DEL_VLAN_CMD:
	हाल GET_VLAN_REALDEV_NAME_CMD:
	हाल GET_VLAN_VID_CMD:
		err = -ENODEV;
		dev = __dev_get_by_name(net, args.device1);
		अगर (!dev)
			जाओ out;

		err = -EINVAL;
		अगर (args.cmd != ADD_VLAN_CMD && !is_vlan_dev(dev))
			जाओ out;
	पूर्ण

	चयन (args.cmd) अणु
	हाल SET_VLAN_INGRESS_PRIORITY_CMD:
		err = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			अवरोध;
		vlan_dev_set_ingress_priority(dev,
					      args.u.skb_priority,
					      args.vlan_qos);
		err = 0;
		अवरोध;

	हाल SET_VLAN_EGRESS_PRIORITY_CMD:
		err = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			अवरोध;
		err = vlan_dev_set_egress_priority(dev,
						   args.u.skb_priority,
						   args.vlan_qos);
		अवरोध;

	हाल SET_VLAN_FLAG_CMD:
		err = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			अवरोध;
		err = vlan_dev_change_flags(dev,
					    args.vlan_qos ? args.u.flag : 0,
					    args.u.flag);
		अवरोध;

	हाल SET_VLAN_NAME_TYPE_CMD:
		err = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			अवरोध;
		अगर (args.u.name_type < VLAN_NAME_TYPE_HIGHEST) अणु
			काष्ठा vlan_net *vn;

			vn = net_generic(net, vlan_net_id);
			vn->name_type = args.u.name_type;
			err = 0;
		पूर्ण अन्यथा अणु
			err = -EINVAL;
		पूर्ण
		अवरोध;

	हाल ADD_VLAN_CMD:
		err = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			अवरोध;
		err = रेजिस्टर_vlan_device(dev, args.u.VID);
		अवरोध;

	हाल DEL_VLAN_CMD:
		err = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			अवरोध;
		unरेजिस्टर_vlan_dev(dev, शून्य);
		err = 0;
		अवरोध;

	हाल GET_VLAN_REALDEV_NAME_CMD:
		err = 0;
		vlan_dev_get_realdev_name(dev, args.u.device2);
		अगर (copy_to_user(arg, &args,
				 माप(काष्ठा vlan_ioctl_args)))
			err = -EFAULT;
		अवरोध;

	हाल GET_VLAN_VID_CMD:
		err = 0;
		args.u.VID = vlan_dev_vlan_id(dev);
		अगर (copy_to_user(arg, &args,
				 माप(काष्ठा vlan_ioctl_args)))
		      err = -EFAULT;
		अवरोध;

	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
out:
	rtnl_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक __net_init vlan_init_net(काष्ठा net *net)
अणु
	काष्ठा vlan_net *vn = net_generic(net, vlan_net_id);
	पूर्णांक err;

	vn->name_type = VLAN_NAME_TYPE_RAW_PLUS_VID_NO_PAD;

	err = vlan_proc_init(net);

	वापस err;
पूर्ण

अटल व्योम __net_निकास vlan_निकास_net(काष्ठा net *net)
अणु
	vlan_proc_cleanup(net);
पूर्ण

अटल काष्ठा pernet_operations vlan_net_ops = अणु
	.init = vlan_init_net,
	.निकास = vlan_निकास_net,
	.id   = &vlan_net_id,
	.size = माप(काष्ठा vlan_net),
पूर्ण;

अटल पूर्णांक __init vlan_proto_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("%s v%s\n", vlan_fullname, vlan_version);

	err = रेजिस्टर_pernet_subsys(&vlan_net_ops);
	अगर (err < 0)
		जाओ err0;

	err = रेजिस्टर_netdevice_notअगरier(&vlan_notअगरier_block);
	अगर (err < 0)
		जाओ err2;

	err = vlan_gvrp_init();
	अगर (err < 0)
		जाओ err3;

	err = vlan_mvrp_init();
	अगर (err < 0)
		जाओ err4;

	err = vlan_netlink_init();
	अगर (err < 0)
		जाओ err5;

	vlan_ioctl_set(vlan_ioctl_handler);
	वापस 0;

err5:
	vlan_mvrp_uninit();
err4:
	vlan_gvrp_uninit();
err3:
	unरेजिस्टर_netdevice_notअगरier(&vlan_notअगरier_block);
err2:
	unरेजिस्टर_pernet_subsys(&vlan_net_ops);
err0:
	वापस err;
पूर्ण

अटल व्योम __निकास vlan_cleanup_module(व्योम)
अणु
	vlan_ioctl_set(शून्य);

	vlan_netlink_fini();

	unरेजिस्टर_netdevice_notअगरier(&vlan_notअगरier_block);

	unरेजिस्टर_pernet_subsys(&vlan_net_ops);
	rcu_barrier(); /* Wait क्रम completion of call_rcu()'s */

	vlan_mvrp_uninit();
	vlan_gvrp_uninit();
पूर्ण

module_init(vlan_proto_init);
module_निकास(vlan_cleanup_module);

MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
