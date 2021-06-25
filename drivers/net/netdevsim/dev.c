<शैली गुरु>
/*
 * Copyright (c) 2018 Cumulus Networks. All rights reserved.
 * Copyright (c) 2018 David Ahern <dsa@cumulusnetworks.com>
 * Copyright (c) 2019 Mellanox Technologies. All rights reserved.
 *
 * This software is licensed under the GNU General License Version 2,
 * June 1991 as shown in the file COPYING in the top-level directory of this
 * source tree.
 *
 * THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS"
 * WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE
 * OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME
 * THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/inet.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/workqueue.h>
#समावेश <net/devlink.h>
#समावेश <net/ip.h>
#समावेश <net/flow_offload.h>
#समावेश <uapi/linux/devlink.h>
#समावेश <uapi/linux/ip.h>
#समावेश <uapi/linux/udp.h>

#समावेश "netdevsim.h"

अटल काष्ठा dentry *nsim_dev_ddir;

#घोषणा NSIM_DEV_DUMMY_REGION_SIZE (1024 * 32)

अटल पूर्णांक
nsim_dev_take_snapshot(काष्ठा devlink *devlink,
		       स्थिर काष्ठा devlink_region_ops *ops,
		       काष्ठा netlink_ext_ack *extack,
		       u8 **data)
अणु
	व्योम *dummy_data;

	dummy_data = kदो_स्मृति(NSIM_DEV_DUMMY_REGION_SIZE, GFP_KERNEL);
	अगर (!dummy_data)
		वापस -ENOMEM;

	get_अक्रमom_bytes(dummy_data, NSIM_DEV_DUMMY_REGION_SIZE);

	*data = dummy_data;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार nsim_dev_take_snapshot_ग_लिखो(काष्ठा file *file,
					    स्थिर अक्षर __user *data,
					    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा nsim_dev *nsim_dev = file->निजी_data;
	काष्ठा devlink *devlink;
	u8 *dummy_data;
	पूर्णांक err;
	u32 id;

	devlink = priv_to_devlink(nsim_dev);

	err = nsim_dev_take_snapshot(devlink, शून्य, शून्य, &dummy_data);
	अगर (err)
		वापस err;

	err = devlink_region_snapshot_id_get(devlink, &id);
	अगर (err) अणु
		pr_err("Failed to get snapshot id\n");
		kमुक्त(dummy_data);
		वापस err;
	पूर्ण
	err = devlink_region_snapshot_create(nsim_dev->dummy_region,
					     dummy_data, id);
	devlink_region_snapshot_id_put(devlink, id);
	अगर (err) अणु
		pr_err("Failed to create region snapshot\n");
		kमुक्त(dummy_data);
		वापस err;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations nsim_dev_take_snapshot_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = nsim_dev_take_snapshot_ग_लिखो,
	.llseek = generic_file_llseek,
	.owner = THIS_MODULE,
पूर्ण;

अटल sमाप_प्रकार nsim_dev_trap_fa_cookie_पढ़ो(काष्ठा file *file,
					    अक्षर __user *data,
					    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा nsim_dev *nsim_dev = file->निजी_data;
	काष्ठा flow_action_cookie *fa_cookie;
	अचिन्हित पूर्णांक buf_len;
	sमाप_प्रकार ret;
	अक्षर *buf;

	spin_lock(&nsim_dev->fa_cookie_lock);
	fa_cookie = nsim_dev->fa_cookie;
	अगर (!fa_cookie) अणु
		ret = -EINVAL;
		जाओ errout;
	पूर्ण
	buf_len = fa_cookie->cookie_len * 2;
	buf = kदो_स्मृति(buf_len, GFP_ATOMIC);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ errout;
	पूर्ण
	bin2hex(buf, fa_cookie->cookie, fa_cookie->cookie_len);
	spin_unlock(&nsim_dev->fa_cookie_lock);

	ret = simple_पढ़ो_from_buffer(data, count, ppos, buf, buf_len);

	kमुक्त(buf);
	वापस ret;

errout:
	spin_unlock(&nsim_dev->fa_cookie_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार nsim_dev_trap_fa_cookie_ग_लिखो(काष्ठा file *file,
					     स्थिर अक्षर __user *data,
					     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा nsim_dev *nsim_dev = file->निजी_data;
	काष्ठा flow_action_cookie *fa_cookie;
	माप_प्रकार cookie_len;
	sमाप_प्रकार ret;
	अक्षर *buf;

	अगर (*ppos != 0)
		वापस -EINVAL;
	cookie_len = (count - 1) / 2;
	अगर ((count - 1) % 2)
		वापस -EINVAL;
	buf = kदो_स्मृति(count, GFP_KERNEL | __GFP_NOWARN);
	अगर (!buf)
		वापस -ENOMEM;

	ret = simple_ग_लिखो_to_buffer(buf, count, ppos, data, count);
	अगर (ret < 0)
		जाओ मुक्त_buf;

	fa_cookie = kदो_स्मृति(माप(*fa_cookie) + cookie_len,
			    GFP_KERNEL | __GFP_NOWARN);
	अगर (!fa_cookie) अणु
		ret = -ENOMEM;
		जाओ मुक्त_buf;
	पूर्ण

	fa_cookie->cookie_len = cookie_len;
	ret = hex2bin(fa_cookie->cookie, buf, cookie_len);
	अगर (ret)
		जाओ मुक्त_fa_cookie;
	kमुक्त(buf);

	spin_lock(&nsim_dev->fa_cookie_lock);
	kमुक्त(nsim_dev->fa_cookie);
	nsim_dev->fa_cookie = fa_cookie;
	spin_unlock(&nsim_dev->fa_cookie_lock);

	वापस count;

मुक्त_fa_cookie:
	kमुक्त(fa_cookie);
मुक्त_buf:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations nsim_dev_trap_fa_cookie_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = nsim_dev_trap_fa_cookie_पढ़ो,
	.ग_लिखो = nsim_dev_trap_fa_cookie_ग_लिखो,
	.llseek = generic_file_llseek,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक nsim_dev_debugfs_init(काष्ठा nsim_dev *nsim_dev)
अणु
	अक्षर dev_ddir_name[माप(DRV_NAME) + 10];

	प्र_लिखो(dev_ddir_name, DRV_NAME "%u", nsim_dev->nsim_bus_dev->dev.id);
	nsim_dev->ddir = debugfs_create_dir(dev_ddir_name, nsim_dev_ddir);
	अगर (IS_ERR(nsim_dev->ddir))
		वापस PTR_ERR(nsim_dev->ddir);
	nsim_dev->ports_ddir = debugfs_create_dir("ports", nsim_dev->ddir);
	अगर (IS_ERR(nsim_dev->ports_ddir))
		वापस PTR_ERR(nsim_dev->ports_ddir);
	debugfs_create_bool("fw_update_status", 0600, nsim_dev->ddir,
			    &nsim_dev->fw_update_status);
	debugfs_create_u32("fw_update_overwrite_mask", 0600, nsim_dev->ddir,
			    &nsim_dev->fw_update_overग_लिखो_mask);
	debugfs_create_u32("max_macs", 0600, nsim_dev->ddir,
			   &nsim_dev->max_macs);
	debugfs_create_bool("test1", 0600, nsim_dev->ddir,
			    &nsim_dev->test1);
	nsim_dev->take_snapshot = debugfs_create_file("take_snapshot",
						      0200,
						      nsim_dev->ddir,
						      nsim_dev,
						&nsim_dev_take_snapshot_fops);
	debugfs_create_bool("dont_allow_reload", 0600, nsim_dev->ddir,
			    &nsim_dev->करोnt_allow_reload);
	debugfs_create_bool("fail_reload", 0600, nsim_dev->ddir,
			    &nsim_dev->fail_reload);
	debugfs_create_file("trap_flow_action_cookie", 0600, nsim_dev->ddir,
			    nsim_dev, &nsim_dev_trap_fa_cookie_fops);
	debugfs_create_bool("fail_trap_group_set", 0600,
			    nsim_dev->ddir,
			    &nsim_dev->fail_trap_group_set);
	debugfs_create_bool("fail_trap_policer_set", 0600,
			    nsim_dev->ddir,
			    &nsim_dev->fail_trap_policer_set);
	debugfs_create_bool("fail_trap_policer_counter_get", 0600,
			    nsim_dev->ddir,
			    &nsim_dev->fail_trap_policer_counter_get);
	nsim_udp_tunnels_debugfs_create(nsim_dev);
	वापस 0;
पूर्ण

अटल व्योम nsim_dev_debugfs_निकास(काष्ठा nsim_dev *nsim_dev)
अणु
	debugfs_हटाओ_recursive(nsim_dev->ports_ddir);
	debugfs_हटाओ_recursive(nsim_dev->ddir);
पूर्ण

अटल पूर्णांक nsim_dev_port_debugfs_init(काष्ठा nsim_dev *nsim_dev,
				      काष्ठा nsim_dev_port *nsim_dev_port)
अणु
	अक्षर port_ddir_name[16];
	अक्षर dev_link_name[32];

	प्र_लिखो(port_ddir_name, "%u", nsim_dev_port->port_index);
	nsim_dev_port->ddir = debugfs_create_dir(port_ddir_name,
						 nsim_dev->ports_ddir);
	अगर (IS_ERR(nsim_dev_port->ddir))
		वापस PTR_ERR(nsim_dev_port->ddir);

	प्र_लिखो(dev_link_name, "../../../" DRV_NAME "%u",
		nsim_dev->nsim_bus_dev->dev.id);
	debugfs_create_symlink("dev", nsim_dev_port->ddir, dev_link_name);

	वापस 0;
पूर्ण

अटल व्योम nsim_dev_port_debugfs_निकास(काष्ठा nsim_dev_port *nsim_dev_port)
अणु
	debugfs_हटाओ_recursive(nsim_dev_port->ddir);
पूर्ण

अटल पूर्णांक nsim_dev_resources_रेजिस्टर(काष्ठा devlink *devlink)
अणु
	काष्ठा devlink_resource_size_params params = अणु
		.size_max = (u64)-1,
		.size_granularity = 1,
		.unit = DEVLINK_RESOURCE_UNIT_ENTRY
	पूर्ण;
	पूर्णांक err;

	/* Resources क्रम IPv4 */
	err = devlink_resource_रेजिस्टर(devlink, "IPv4", (u64)-1,
					NSIM_RESOURCE_IPV4,
					DEVLINK_RESOURCE_ID_PARENT_TOP,
					&params);
	अगर (err) अणु
		pr_err("Failed to register IPv4 top resource\n");
		जाओ out;
	पूर्ण

	err = devlink_resource_रेजिस्टर(devlink, "fib", (u64)-1,
					NSIM_RESOURCE_IPV4_FIB,
					NSIM_RESOURCE_IPV4, &params);
	अगर (err) अणु
		pr_err("Failed to register IPv4 FIB resource\n");
		वापस err;
	पूर्ण

	err = devlink_resource_रेजिस्टर(devlink, "fib-rules", (u64)-1,
					NSIM_RESOURCE_IPV4_FIB_RULES,
					NSIM_RESOURCE_IPV4, &params);
	अगर (err) अणु
		pr_err("Failed to register IPv4 FIB rules resource\n");
		वापस err;
	पूर्ण

	/* Resources क्रम IPv6 */
	err = devlink_resource_रेजिस्टर(devlink, "IPv6", (u64)-1,
					NSIM_RESOURCE_IPV6,
					DEVLINK_RESOURCE_ID_PARENT_TOP,
					&params);
	अगर (err) अणु
		pr_err("Failed to register IPv6 top resource\n");
		जाओ out;
	पूर्ण

	err = devlink_resource_रेजिस्टर(devlink, "fib", (u64)-1,
					NSIM_RESOURCE_IPV6_FIB,
					NSIM_RESOURCE_IPV6, &params);
	अगर (err) अणु
		pr_err("Failed to register IPv6 FIB resource\n");
		वापस err;
	पूर्ण

	err = devlink_resource_रेजिस्टर(devlink, "fib-rules", (u64)-1,
					NSIM_RESOURCE_IPV6_FIB_RULES,
					NSIM_RESOURCE_IPV6, &params);
	अगर (err) अणु
		pr_err("Failed to register IPv6 FIB rules resource\n");
		वापस err;
	पूर्ण

	/* Resources क्रम nexthops */
	err = devlink_resource_रेजिस्टर(devlink, "nexthops", (u64)-1,
					NSIM_RESOURCE_NEXTHOPS,
					DEVLINK_RESOURCE_ID_PARENT_TOP,
					&params);

out:
	वापस err;
पूर्ण

क्रमागत nsim_devlink_param_id अणु
	NSIM_DEVLINK_PARAM_ID_BASE = DEVLINK_PARAM_GENERIC_ID_MAX,
	NSIM_DEVLINK_PARAM_ID_TEST1,
पूर्ण;

अटल स्थिर काष्ठा devlink_param nsim_devlink_params[] = अणु
	DEVLINK_PARAM_GENERIC(MAX_MACS,
			      BIT(DEVLINK_PARAM_CMODE_DRIVERINIT),
			      शून्य, शून्य, शून्य),
	DEVLINK_PARAM_DRIVER(NSIM_DEVLINK_PARAM_ID_TEST1,
			     "test1", DEVLINK_PARAM_TYPE_BOOL,
			     BIT(DEVLINK_PARAM_CMODE_DRIVERINIT),
			     शून्य, शून्य, शून्य),
पूर्ण;

अटल व्योम nsim_devlink_set_params_init_values(काष्ठा nsim_dev *nsim_dev,
						काष्ठा devlink *devlink)
अणु
	जोड़ devlink_param_value value;

	value.vu32 = nsim_dev->max_macs;
	devlink_param_driverinit_value_set(devlink,
					   DEVLINK_PARAM_GENERIC_ID_MAX_MACS,
					   value);
	value.vbool = nsim_dev->test1;
	devlink_param_driverinit_value_set(devlink,
					   NSIM_DEVLINK_PARAM_ID_TEST1,
					   value);
पूर्ण

अटल व्योम nsim_devlink_param_load_driverinit_values(काष्ठा devlink *devlink)
अणु
	काष्ठा nsim_dev *nsim_dev = devlink_priv(devlink);
	जोड़ devlink_param_value saved_value;
	पूर्णांक err;

	err = devlink_param_driverinit_value_get(devlink,
						 DEVLINK_PARAM_GENERIC_ID_MAX_MACS,
						 &saved_value);
	अगर (!err)
		nsim_dev->max_macs = saved_value.vu32;
	err = devlink_param_driverinit_value_get(devlink,
						 NSIM_DEVLINK_PARAM_ID_TEST1,
						 &saved_value);
	अगर (!err)
		nsim_dev->test1 = saved_value.vbool;
पूर्ण

#घोषणा NSIM_DEV_DUMMY_REGION_SNAPSHOT_MAX 16

अटल स्थिर काष्ठा devlink_region_ops dummy_region_ops = अणु
	.name = "dummy",
	.deकाष्ठाor = &kमुक्त,
	.snapshot = nsim_dev_take_snapshot,
पूर्ण;

अटल पूर्णांक nsim_dev_dummy_region_init(काष्ठा nsim_dev *nsim_dev,
				      काष्ठा devlink *devlink)
अणु
	nsim_dev->dummy_region =
		devlink_region_create(devlink, &dummy_region_ops,
				      NSIM_DEV_DUMMY_REGION_SNAPSHOT_MAX,
				      NSIM_DEV_DUMMY_REGION_SIZE);
	वापस PTR_ERR_OR_ZERO(nsim_dev->dummy_region);
पूर्ण

अटल व्योम nsim_dev_dummy_region_निकास(काष्ठा nsim_dev *nsim_dev)
अणु
	devlink_region_destroy(nsim_dev->dummy_region);
पूर्ण

काष्ठा nsim_trap_item अणु
	व्योम *trap_ctx;
	क्रमागत devlink_trap_action action;
पूर्ण;

काष्ठा nsim_trap_data अणु
	काष्ठा delayed_work trap_report_dw;
	काष्ठा nsim_trap_item *trap_items_arr;
	u64 *trap_policers_cnt_arr;
	काष्ठा nsim_dev *nsim_dev;
	spinlock_t trap_lock;	/* Protects trap_items_arr */
पूर्ण;

/* All driver-specअगरic traps must be करोcumented in
 * Documentation/networking/devlink/netdevsim.rst
 */
क्रमागत अणु
	NSIM_TRAP_ID_BASE = DEVLINK_TRAP_GENERIC_ID_MAX,
	NSIM_TRAP_ID_FID_MISS,
पूर्ण;

#घोषणा NSIM_TRAP_NAME_FID_MISS "fid_miss"

#घोषणा NSIM_TRAP_METADATA DEVLINK_TRAP_METADATA_TYPE_F_IN_PORT

#घोषणा NSIM_TRAP_DROP(_id, _group_id)					      \
	DEVLINK_TRAP_GENERIC(DROP, DROP, _id,				      \
			     DEVLINK_TRAP_GROUP_GENERIC_ID_##_group_id,	      \
			     NSIM_TRAP_METADATA)
#घोषणा NSIM_TRAP_DROP_EXT(_id, _group_id, _metadata)			      \
	DEVLINK_TRAP_GENERIC(DROP, DROP, _id,				      \
			     DEVLINK_TRAP_GROUP_GENERIC_ID_##_group_id,	      \
			     NSIM_TRAP_METADATA | (_metadata))
#घोषणा NSIM_TRAP_EXCEPTION(_id, _group_id)				      \
	DEVLINK_TRAP_GENERIC(EXCEPTION, TRAP, _id,			      \
			     DEVLINK_TRAP_GROUP_GENERIC_ID_##_group_id,	      \
			     NSIM_TRAP_METADATA)
#घोषणा NSIM_TRAP_CONTROL(_id, _group_id, _action)			      \
	DEVLINK_TRAP_GENERIC(CONTROL, _action, _id,			      \
			     DEVLINK_TRAP_GROUP_GENERIC_ID_##_group_id,	      \
			     NSIM_TRAP_METADATA)
#घोषणा NSIM_TRAP_DRIVER_EXCEPTION(_id, _group_id)			      \
	DEVLINK_TRAP_DRIVER(EXCEPTION, TRAP, NSIM_TRAP_ID_##_id,	      \
			    NSIM_TRAP_NAME_##_id,			      \
			    DEVLINK_TRAP_GROUP_GENERIC_ID_##_group_id,	      \
			    NSIM_TRAP_METADATA)

#घोषणा NSIM_DEV_TRAP_POLICER_MIN_RATE	1
#घोषणा NSIM_DEV_TRAP_POLICER_MAX_RATE	8000
#घोषणा NSIM_DEV_TRAP_POLICER_MIN_BURST	8
#घोषणा NSIM_DEV_TRAP_POLICER_MAX_BURST	65536

#घोषणा NSIM_TRAP_POLICER(_id, _rate, _burst)				      \
	DEVLINK_TRAP_POLICER(_id, _rate, _burst,			      \
			     NSIM_DEV_TRAP_POLICER_MAX_RATE,		      \
			     NSIM_DEV_TRAP_POLICER_MIN_RATE,		      \
			     NSIM_DEV_TRAP_POLICER_MAX_BURST,		      \
			     NSIM_DEV_TRAP_POLICER_MIN_BURST)

अटल स्थिर काष्ठा devlink_trap_policer nsim_trap_policers_arr[] = अणु
	NSIM_TRAP_POLICER(1, 1000, 128),
	NSIM_TRAP_POLICER(2, 2000, 256),
	NSIM_TRAP_POLICER(3, 3000, 512),
पूर्ण;

अटल स्थिर काष्ठा devlink_trap_group nsim_trap_groups_arr[] = अणु
	DEVLINK_TRAP_GROUP_GENERIC(L2_DROPS, 0),
	DEVLINK_TRAP_GROUP_GENERIC(L3_DROPS, 1),
	DEVLINK_TRAP_GROUP_GENERIC(L3_EXCEPTIONS, 1),
	DEVLINK_TRAP_GROUP_GENERIC(BUFFER_DROPS, 2),
	DEVLINK_TRAP_GROUP_GENERIC(ACL_DROPS, 3),
	DEVLINK_TRAP_GROUP_GENERIC(MC_SNOOPING, 3),
पूर्ण;

अटल स्थिर काष्ठा devlink_trap nsim_traps_arr[] = अणु
	NSIM_TRAP_DROP(SMAC_MC, L2_DROPS),
	NSIM_TRAP_DROP(VLAN_TAG_MISMATCH, L2_DROPS),
	NSIM_TRAP_DROP(INGRESS_VLAN_FILTER, L2_DROPS),
	NSIM_TRAP_DROP(INGRESS_STP_FILTER, L2_DROPS),
	NSIM_TRAP_DROP(EMPTY_TX_LIST, L2_DROPS),
	NSIM_TRAP_DROP(PORT_LOOPBACK_FILTER, L2_DROPS),
	NSIM_TRAP_DRIVER_EXCEPTION(FID_MISS, L2_DROPS),
	NSIM_TRAP_DROP(BLACKHOLE_ROUTE, L3_DROPS),
	NSIM_TRAP_EXCEPTION(TTL_ERROR, L3_EXCEPTIONS),
	NSIM_TRAP_DROP(TAIL_DROP, BUFFER_DROPS),
	NSIM_TRAP_DROP_EXT(INGRESS_FLOW_ACTION_DROP, ACL_DROPS,
			   DEVLINK_TRAP_METADATA_TYPE_F_FA_COOKIE),
	NSIM_TRAP_DROP_EXT(EGRESS_FLOW_ACTION_DROP, ACL_DROPS,
			   DEVLINK_TRAP_METADATA_TYPE_F_FA_COOKIE),
	NSIM_TRAP_CONTROL(IGMP_QUERY, MC_SNOOPING, MIRROR),
	NSIM_TRAP_CONTROL(IGMP_V1_REPORT, MC_SNOOPING, TRAP),
पूर्ण;

#घोषणा NSIM_TRAP_L4_DATA_LEN 100

अटल काष्ठा sk_buff *nsim_dev_trap_skb_build(व्योम)
अणु
	पूर्णांक tot_len, data_len = NSIM_TRAP_L4_DATA_LEN;
	काष्ठा sk_buff *skb;
	काष्ठा udphdr *udph;
	काष्ठा ethhdr *eth;
	काष्ठा iphdr *iph;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;
	tot_len = माप(काष्ठा iphdr) + माप(काष्ठा udphdr) + data_len;

	skb_reset_mac_header(skb);
	eth = skb_put(skb, माप(काष्ठा ethhdr));
	eth_अक्रमom_addr(eth->h_dest);
	eth_अक्रमom_addr(eth->h_source);
	eth->h_proto = htons(ETH_P_IP);
	skb->protocol = htons(ETH_P_IP);

	skb_set_network_header(skb, skb->len);
	iph = skb_put(skb, माप(काष्ठा iphdr));
	iph->protocol = IPPROTO_UDP;
	iph->saddr = in_aton("192.0.2.1");
	iph->daddr = in_aton("198.51.100.1");
	iph->version = 0x4;
	iph->frag_off = 0;
	iph->ihl = 0x5;
	iph->tot_len = htons(tot_len);
	iph->ttl = 100;
	iph->check = 0;
	iph->check = ip_fast_csum((अचिन्हित अक्षर *)iph, iph->ihl);

	skb_set_transport_header(skb, skb->len);
	udph = skb_put_zero(skb, माप(काष्ठा udphdr) + data_len);
	get_अक्रमom_bytes(&udph->source, माप(u16));
	get_अक्रमom_bytes(&udph->dest, माप(u16));
	udph->len = htons(माप(काष्ठा udphdr) + data_len);

	वापस skb;
पूर्ण

अटल व्योम nsim_dev_trap_report(काष्ठा nsim_dev_port *nsim_dev_port)
अणु
	काष्ठा nsim_dev *nsim_dev = nsim_dev_port->ns->nsim_dev;
	काष्ठा devlink *devlink = priv_to_devlink(nsim_dev);
	काष्ठा nsim_trap_data *nsim_trap_data;
	पूर्णांक i;

	nsim_trap_data = nsim_dev->trap_data;

	spin_lock(&nsim_trap_data->trap_lock);
	क्रम (i = 0; i < ARRAY_SIZE(nsim_traps_arr); i++) अणु
		काष्ठा flow_action_cookie *fa_cookie = शून्य;
		काष्ठा nsim_trap_item *nsim_trap_item;
		काष्ठा sk_buff *skb;
		bool has_fa_cookie;

		has_fa_cookie = nsim_traps_arr[i].metadata_cap &
				DEVLINK_TRAP_METADATA_TYPE_F_FA_COOKIE;

		nsim_trap_item = &nsim_trap_data->trap_items_arr[i];
		अगर (nsim_trap_item->action == DEVLINK_TRAP_ACTION_DROP)
			जारी;

		skb = nsim_dev_trap_skb_build();
		अगर (!skb)
			जारी;
		skb->dev = nsim_dev_port->ns->netdev;

		/* Trapped packets are usually passed to devlink in softIRQ,
		 * but in this हाल they are generated in a workqueue. Disable
		 * softIRQs to prevent lockdep from complaining about
		 * "incosistent lock state".
		 */

		spin_lock_bh(&nsim_dev->fa_cookie_lock);
		fa_cookie = has_fa_cookie ? nsim_dev->fa_cookie : शून्य;
		devlink_trap_report(devlink, skb, nsim_trap_item->trap_ctx,
				    &nsim_dev_port->devlink_port, fa_cookie);
		spin_unlock_bh(&nsim_dev->fa_cookie_lock);
		consume_skb(skb);
	पूर्ण
	spin_unlock(&nsim_trap_data->trap_lock);
पूर्ण

#घोषणा NSIM_TRAP_REPORT_INTERVAL_MS	100

अटल व्योम nsim_dev_trap_report_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nsim_trap_data *nsim_trap_data;
	काष्ठा nsim_dev_port *nsim_dev_port;
	काष्ठा nsim_dev *nsim_dev;

	nsim_trap_data = container_of(work, काष्ठा nsim_trap_data,
				      trap_report_dw.work);
	nsim_dev = nsim_trap_data->nsim_dev;

	/* For each running port and enabled packet trap, generate a UDP
	 * packet with a अक्रमom 5-tuple and report it.
	 */
	mutex_lock(&nsim_dev->port_list_lock);
	list_क्रम_each_entry(nsim_dev_port, &nsim_dev->port_list, list) अणु
		अगर (!netअगर_running(nsim_dev_port->ns->netdev))
			जारी;

		nsim_dev_trap_report(nsim_dev_port);
	पूर्ण
	mutex_unlock(&nsim_dev->port_list_lock);

	schedule_delayed_work(&nsim_dev->trap_data->trap_report_dw,
			      msecs_to_jअगरfies(NSIM_TRAP_REPORT_INTERVAL_MS));
पूर्ण

अटल पूर्णांक nsim_dev_traps_init(काष्ठा devlink *devlink)
अणु
	माप_प्रकार policers_count = ARRAY_SIZE(nsim_trap_policers_arr);
	काष्ठा nsim_dev *nsim_dev = devlink_priv(devlink);
	काष्ठा nsim_trap_data *nsim_trap_data;
	पूर्णांक err;

	nsim_trap_data = kzalloc(माप(*nsim_trap_data), GFP_KERNEL);
	अगर (!nsim_trap_data)
		वापस -ENOMEM;

	nsim_trap_data->trap_items_arr = kसुस्मृति(ARRAY_SIZE(nsim_traps_arr),
						 माप(काष्ठा nsim_trap_item),
						 GFP_KERNEL);
	अगर (!nsim_trap_data->trap_items_arr) अणु
		err = -ENOMEM;
		जाओ err_trap_data_मुक्त;
	पूर्ण

	nsim_trap_data->trap_policers_cnt_arr = kसुस्मृति(policers_count,
							माप(u64),
							GFP_KERNEL);
	अगर (!nsim_trap_data->trap_policers_cnt_arr) अणु
		err = -ENOMEM;
		जाओ err_trap_items_मुक्त;
	पूर्ण

	/* The lock is used to protect the action state of the रेजिस्टरed
	 * traps. The value is written by user and पढ़ो in delayed work when
	 * iterating over all the traps.
	 */
	spin_lock_init(&nsim_trap_data->trap_lock);
	nsim_trap_data->nsim_dev = nsim_dev;
	nsim_dev->trap_data = nsim_trap_data;

	err = devlink_trap_policers_रेजिस्टर(devlink, nsim_trap_policers_arr,
					     policers_count);
	अगर (err)
		जाओ err_trap_policers_cnt_मुक्त;

	err = devlink_trap_groups_रेजिस्टर(devlink, nsim_trap_groups_arr,
					   ARRAY_SIZE(nsim_trap_groups_arr));
	अगर (err)
		जाओ err_trap_policers_unरेजिस्टर;

	err = devlink_traps_रेजिस्टर(devlink, nsim_traps_arr,
				     ARRAY_SIZE(nsim_traps_arr), शून्य);
	अगर (err)
		जाओ err_trap_groups_unरेजिस्टर;

	INIT_DELAYED_WORK(&nsim_dev->trap_data->trap_report_dw,
			  nsim_dev_trap_report_work);
	schedule_delayed_work(&nsim_dev->trap_data->trap_report_dw,
			      msecs_to_jअगरfies(NSIM_TRAP_REPORT_INTERVAL_MS));

	वापस 0;

err_trap_groups_unरेजिस्टर:
	devlink_trap_groups_unरेजिस्टर(devlink, nsim_trap_groups_arr,
				       ARRAY_SIZE(nsim_trap_groups_arr));
err_trap_policers_unरेजिस्टर:
	devlink_trap_policers_unरेजिस्टर(devlink, nsim_trap_policers_arr,
					 ARRAY_SIZE(nsim_trap_policers_arr));
err_trap_policers_cnt_मुक्त:
	kमुक्त(nsim_trap_data->trap_policers_cnt_arr);
err_trap_items_मुक्त:
	kमुक्त(nsim_trap_data->trap_items_arr);
err_trap_data_मुक्त:
	kमुक्त(nsim_trap_data);
	वापस err;
पूर्ण

अटल व्योम nsim_dev_traps_निकास(काष्ठा devlink *devlink)
अणु
	काष्ठा nsim_dev *nsim_dev = devlink_priv(devlink);

	cancel_delayed_work_sync(&nsim_dev->trap_data->trap_report_dw);
	devlink_traps_unरेजिस्टर(devlink, nsim_traps_arr,
				 ARRAY_SIZE(nsim_traps_arr));
	devlink_trap_groups_unरेजिस्टर(devlink, nsim_trap_groups_arr,
				       ARRAY_SIZE(nsim_trap_groups_arr));
	devlink_trap_policers_unरेजिस्टर(devlink, nsim_trap_policers_arr,
					 ARRAY_SIZE(nsim_trap_policers_arr));
	kमुक्त(nsim_dev->trap_data->trap_policers_cnt_arr);
	kमुक्त(nsim_dev->trap_data->trap_items_arr);
	kमुक्त(nsim_dev->trap_data);
पूर्ण

अटल पूर्णांक nsim_dev_reload_create(काष्ठा nsim_dev *nsim_dev,
				  काष्ठा netlink_ext_ack *extack);
अटल व्योम nsim_dev_reload_destroy(काष्ठा nsim_dev *nsim_dev);

अटल पूर्णांक nsim_dev_reload_करोwn(काष्ठा devlink *devlink, bool netns_change,
				क्रमागत devlink_reload_action action, क्रमागत devlink_reload_limit limit,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nsim_dev *nsim_dev = devlink_priv(devlink);

	अगर (nsim_dev->करोnt_allow_reload) अणु
		/* For testing purposes, user set debugfs करोnt_allow_reload
		 * value to true. So क्रमbid it.
		 */
		NL_SET_ERR_MSG_MOD(extack, "User forbid the reload for testing purposes");
		वापस -EOPNOTSUPP;
	पूर्ण

	nsim_dev_reload_destroy(nsim_dev);
	वापस 0;
पूर्ण

अटल पूर्णांक nsim_dev_reload_up(काष्ठा devlink *devlink, क्रमागत devlink_reload_action action,
			      क्रमागत devlink_reload_limit limit, u32 *actions_perक्रमmed,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nsim_dev *nsim_dev = devlink_priv(devlink);

	अगर (nsim_dev->fail_reload) अणु
		/* For testing purposes, user set debugfs fail_reload
		 * value to true. Fail right away.
		 */
		NL_SET_ERR_MSG_MOD(extack, "User setup the reload to fail for testing purposes");
		वापस -EINVAL;
	पूर्ण

	*actions_perक्रमmed = BIT(DEVLINK_RELOAD_ACTION_DRIVER_REINIT);
	वापस nsim_dev_reload_create(nsim_dev, extack);
पूर्ण

अटल पूर्णांक nsim_dev_info_get(काष्ठा devlink *devlink,
			     काष्ठा devlink_info_req *req,
			     काष्ठा netlink_ext_ack *extack)
अणु
	वापस devlink_info_driver_name_put(req, DRV_NAME);
पूर्ण

#घोषणा NSIM_DEV_FLASH_SIZE 500000
#घोषणा NSIM_DEV_FLASH_CHUNK_SIZE 1000
#घोषणा NSIM_DEV_FLASH_CHUNK_TIME_MS 10

अटल पूर्णांक nsim_dev_flash_update(काष्ठा devlink *devlink,
				 काष्ठा devlink_flash_update_params *params,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nsim_dev *nsim_dev = devlink_priv(devlink);
	पूर्णांक i;

	अगर ((params->overग_लिखो_mask & ~nsim_dev->fw_update_overग_लिखो_mask) != 0)
		वापस -EOPNOTSUPP;

	अगर (nsim_dev->fw_update_status) अणु
		devlink_flash_update_status_notअगरy(devlink,
						   "Preparing to flash",
						   params->component, 0, 0);
	पूर्ण

	क्रम (i = 0; i < NSIM_DEV_FLASH_SIZE / NSIM_DEV_FLASH_CHUNK_SIZE; i++) अणु
		अगर (nsim_dev->fw_update_status)
			devlink_flash_update_status_notअगरy(devlink, "Flashing",
							   params->component,
							   i * NSIM_DEV_FLASH_CHUNK_SIZE,
							   NSIM_DEV_FLASH_SIZE);
		msleep(NSIM_DEV_FLASH_CHUNK_TIME_MS);
	पूर्ण

	अगर (nsim_dev->fw_update_status) अणु
		devlink_flash_update_status_notअगरy(devlink, "Flashing",
						   params->component,
						   NSIM_DEV_FLASH_SIZE,
						   NSIM_DEV_FLASH_SIZE);
		devlink_flash_update_समयout_notअगरy(devlink, "Flash select",
						    params->component, 81);
		devlink_flash_update_status_notअगरy(devlink, "Flashing done",
						   params->component, 0, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा nsim_trap_item *
nsim_dev_trap_item_lookup(काष्ठा nsim_dev *nsim_dev, u16 trap_id)
अणु
	काष्ठा nsim_trap_data *nsim_trap_data = nsim_dev->trap_data;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nsim_traps_arr); i++) अणु
		अगर (nsim_traps_arr[i].id == trap_id)
			वापस &nsim_trap_data->trap_items_arr[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक nsim_dev_devlink_trap_init(काष्ठा devlink *devlink,
				      स्थिर काष्ठा devlink_trap *trap,
				      व्योम *trap_ctx)
अणु
	काष्ठा nsim_dev *nsim_dev = devlink_priv(devlink);
	काष्ठा nsim_trap_item *nsim_trap_item;

	nsim_trap_item = nsim_dev_trap_item_lookup(nsim_dev, trap->id);
	अगर (WARN_ON(!nsim_trap_item))
		वापस -ENOENT;

	nsim_trap_item->trap_ctx = trap_ctx;
	nsim_trap_item->action = trap->init_action;

	वापस 0;
पूर्ण

अटल पूर्णांक
nsim_dev_devlink_trap_action_set(काष्ठा devlink *devlink,
				 स्थिर काष्ठा devlink_trap *trap,
				 क्रमागत devlink_trap_action action,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nsim_dev *nsim_dev = devlink_priv(devlink);
	काष्ठा nsim_trap_item *nsim_trap_item;

	nsim_trap_item = nsim_dev_trap_item_lookup(nsim_dev, trap->id);
	अगर (WARN_ON(!nsim_trap_item))
		वापस -ENOENT;

	spin_lock(&nsim_dev->trap_data->trap_lock);
	nsim_trap_item->action = action;
	spin_unlock(&nsim_dev->trap_data->trap_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
nsim_dev_devlink_trap_group_set(काष्ठा devlink *devlink,
				स्थिर काष्ठा devlink_trap_group *group,
				स्थिर काष्ठा devlink_trap_policer *policer,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nsim_dev *nsim_dev = devlink_priv(devlink);

	अगर (nsim_dev->fail_trap_group_set)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
nsim_dev_devlink_trap_policer_set(काष्ठा devlink *devlink,
				  स्थिर काष्ठा devlink_trap_policer *policer,
				  u64 rate, u64 burst,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nsim_dev *nsim_dev = devlink_priv(devlink);

	अगर (nsim_dev->fail_trap_policer_set) अणु
		NL_SET_ERR_MSG_MOD(extack, "User setup the operation to fail for testing purposes");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nsim_dev_devlink_trap_policer_counter_get(काष्ठा devlink *devlink,
					  स्थिर काष्ठा devlink_trap_policer *policer,
					  u64 *p_drops)
अणु
	काष्ठा nsim_dev *nsim_dev = devlink_priv(devlink);
	u64 *cnt;

	अगर (nsim_dev->fail_trap_policer_counter_get)
		वापस -EINVAL;

	cnt = &nsim_dev->trap_data->trap_policers_cnt_arr[policer->id - 1];
	*p_drops = (*cnt)++;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devlink_ops nsim_dev_devlink_ops = अणु
	.supported_flash_update_params = DEVLINK_SUPPORT_FLASH_UPDATE_COMPONENT |
					 DEVLINK_SUPPORT_FLASH_UPDATE_OVERWRITE_MASK,
	.reload_actions = BIT(DEVLINK_RELOAD_ACTION_DRIVER_REINIT),
	.reload_करोwn = nsim_dev_reload_करोwn,
	.reload_up = nsim_dev_reload_up,
	.info_get = nsim_dev_info_get,
	.flash_update = nsim_dev_flash_update,
	.trap_init = nsim_dev_devlink_trap_init,
	.trap_action_set = nsim_dev_devlink_trap_action_set,
	.trap_group_set = nsim_dev_devlink_trap_group_set,
	.trap_policer_set = nsim_dev_devlink_trap_policer_set,
	.trap_policer_counter_get = nsim_dev_devlink_trap_policer_counter_get,
पूर्ण;

#घोषणा NSIM_DEV_MAX_MACS_DEFAULT 32
#घोषणा NSIM_DEV_TEST1_DEFAULT true

अटल पूर्णांक __nsim_dev_port_add(काष्ठा nsim_dev *nsim_dev,
			       अचिन्हित पूर्णांक port_index)
अणु
	काष्ठा devlink_port_attrs attrs = अणुपूर्ण;
	काष्ठा nsim_dev_port *nsim_dev_port;
	काष्ठा devlink_port *devlink_port;
	पूर्णांक err;

	nsim_dev_port = kzalloc(माप(*nsim_dev_port), GFP_KERNEL);
	अगर (!nsim_dev_port)
		वापस -ENOMEM;
	nsim_dev_port->port_index = port_index;

	devlink_port = &nsim_dev_port->devlink_port;
	attrs.flavour = DEVLINK_PORT_FLAVOUR_PHYSICAL;
	attrs.phys.port_number = port_index + 1;
	स_नकल(attrs.चयन_id.id, nsim_dev->चयन_id.id, nsim_dev->चयन_id.id_len);
	attrs.चयन_id.id_len = nsim_dev->चयन_id.id_len;
	devlink_port_attrs_set(devlink_port, &attrs);
	err = devlink_port_रेजिस्टर(priv_to_devlink(nsim_dev), devlink_port,
				    port_index);
	अगर (err)
		जाओ err_port_मुक्त;

	err = nsim_dev_port_debugfs_init(nsim_dev, nsim_dev_port);
	अगर (err)
		जाओ err_dl_port_unरेजिस्टर;

	nsim_dev_port->ns = nsim_create(nsim_dev, nsim_dev_port);
	अगर (IS_ERR(nsim_dev_port->ns)) अणु
		err = PTR_ERR(nsim_dev_port->ns);
		जाओ err_port_debugfs_निकास;
	पूर्ण

	devlink_port_type_eth_set(devlink_port, nsim_dev_port->ns->netdev);
	list_add(&nsim_dev_port->list, &nsim_dev->port_list);

	वापस 0;

err_port_debugfs_निकास:
	nsim_dev_port_debugfs_निकास(nsim_dev_port);
err_dl_port_unरेजिस्टर:
	devlink_port_unरेजिस्टर(devlink_port);
err_port_मुक्त:
	kमुक्त(nsim_dev_port);
	वापस err;
पूर्ण

अटल व्योम __nsim_dev_port_del(काष्ठा nsim_dev_port *nsim_dev_port)
अणु
	काष्ठा devlink_port *devlink_port = &nsim_dev_port->devlink_port;

	list_del(&nsim_dev_port->list);
	devlink_port_type_clear(devlink_port);
	nsim_destroy(nsim_dev_port->ns);
	nsim_dev_port_debugfs_निकास(nsim_dev_port);
	devlink_port_unरेजिस्टर(devlink_port);
	kमुक्त(nsim_dev_port);
पूर्ण

अटल व्योम nsim_dev_port_del_all(काष्ठा nsim_dev *nsim_dev)
अणु
	काष्ठा nsim_dev_port *nsim_dev_port, *पंचांगp;

	mutex_lock(&nsim_dev->port_list_lock);
	list_क्रम_each_entry_safe(nsim_dev_port, पंचांगp,
				 &nsim_dev->port_list, list)
		__nsim_dev_port_del(nsim_dev_port);
	mutex_unlock(&nsim_dev->port_list_lock);
पूर्ण

अटल पूर्णांक nsim_dev_port_add_all(काष्ठा nsim_dev *nsim_dev,
				 अचिन्हित पूर्णांक port_count)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < port_count; i++) अणु
		err = __nsim_dev_port_add(nsim_dev, i);
		अगर (err)
			जाओ err_port_del_all;
	पूर्ण
	वापस 0;

err_port_del_all:
	nsim_dev_port_del_all(nsim_dev);
	वापस err;
पूर्ण

अटल पूर्णांक nsim_dev_reload_create(काष्ठा nsim_dev *nsim_dev,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nsim_bus_dev *nsim_bus_dev = nsim_dev->nsim_bus_dev;
	काष्ठा devlink *devlink;
	पूर्णांक err;

	devlink = priv_to_devlink(nsim_dev);
	nsim_dev = devlink_priv(devlink);
	INIT_LIST_HEAD(&nsim_dev->port_list);
	mutex_init(&nsim_dev->port_list_lock);
	nsim_dev->fw_update_status = true;
	nsim_dev->fw_update_overग_लिखो_mask = 0;

	nsim_devlink_param_load_driverinit_values(devlink);

	err = nsim_dev_dummy_region_init(nsim_dev, devlink);
	अगर (err)
		वापस err;

	err = nsim_dev_traps_init(devlink);
	अगर (err)
		जाओ err_dummy_region_निकास;

	nsim_dev->fib_data = nsim_fib_create(devlink, extack);
	अगर (IS_ERR(nsim_dev->fib_data)) अणु
		err = PTR_ERR(nsim_dev->fib_data);
		जाओ err_traps_निकास;
	पूर्ण

	err = nsim_dev_health_init(nsim_dev, devlink);
	अगर (err)
		जाओ err_fib_destroy;

	err = nsim_dev_psample_init(nsim_dev);
	अगर (err)
		जाओ err_health_निकास;

	err = nsim_dev_port_add_all(nsim_dev, nsim_bus_dev->port_count);
	अगर (err)
		जाओ err_psample_निकास;

	nsim_dev->take_snapshot = debugfs_create_file("take_snapshot",
						      0200,
						      nsim_dev->ddir,
						      nsim_dev,
						&nsim_dev_take_snapshot_fops);
	वापस 0;

err_psample_निकास:
	nsim_dev_psample_निकास(nsim_dev);
err_health_निकास:
	nsim_dev_health_निकास(nsim_dev);
err_fib_destroy:
	nsim_fib_destroy(devlink, nsim_dev->fib_data);
err_traps_निकास:
	nsim_dev_traps_निकास(devlink);
err_dummy_region_निकास:
	nsim_dev_dummy_region_निकास(nsim_dev);
	वापस err;
पूर्ण

पूर्णांक nsim_dev_probe(काष्ठा nsim_bus_dev *nsim_bus_dev)
अणु
	काष्ठा nsim_dev *nsim_dev;
	काष्ठा devlink *devlink;
	पूर्णांक err;

	devlink = devlink_alloc(&nsim_dev_devlink_ops, माप(*nsim_dev));
	अगर (!devlink)
		वापस -ENOMEM;
	devlink_net_set(devlink, nsim_bus_dev->initial_net);
	nsim_dev = devlink_priv(devlink);
	nsim_dev->nsim_bus_dev = nsim_bus_dev;
	nsim_dev->चयन_id.id_len = माप(nsim_dev->चयन_id.id);
	get_अक्रमom_bytes(nsim_dev->चयन_id.id, nsim_dev->चयन_id.id_len);
	INIT_LIST_HEAD(&nsim_dev->port_list);
	mutex_init(&nsim_dev->port_list_lock);
	nsim_dev->fw_update_status = true;
	nsim_dev->fw_update_overग_लिखो_mask = 0;
	nsim_dev->max_macs = NSIM_DEV_MAX_MACS_DEFAULT;
	nsim_dev->test1 = NSIM_DEV_TEST1_DEFAULT;
	spin_lock_init(&nsim_dev->fa_cookie_lock);

	dev_set_drvdata(&nsim_bus_dev->dev, nsim_dev);

	err = nsim_dev_resources_रेजिस्टर(devlink);
	अगर (err)
		जाओ err_devlink_मुक्त;

	err = devlink_रेजिस्टर(devlink, &nsim_bus_dev->dev);
	अगर (err)
		जाओ err_resources_unरेजिस्टर;

	err = devlink_params_रेजिस्टर(devlink, nsim_devlink_params,
				      ARRAY_SIZE(nsim_devlink_params));
	अगर (err)
		जाओ err_dl_unरेजिस्टर;
	nsim_devlink_set_params_init_values(nsim_dev, devlink);

	err = nsim_dev_dummy_region_init(nsim_dev, devlink);
	अगर (err)
		जाओ err_params_unरेजिस्टर;

	err = nsim_dev_traps_init(devlink);
	अगर (err)
		जाओ err_dummy_region_निकास;

	err = nsim_dev_debugfs_init(nsim_dev);
	अगर (err)
		जाओ err_traps_निकास;

	nsim_dev->fib_data = nsim_fib_create(devlink, शून्य);
	अगर (IS_ERR(nsim_dev->fib_data)) अणु
		err = PTR_ERR(nsim_dev->fib_data);
		जाओ err_debugfs_निकास;
	पूर्ण

	err = nsim_dev_health_init(nsim_dev, devlink);
	अगर (err)
		जाओ err_fib_destroy;

	err = nsim_bpf_dev_init(nsim_dev);
	अगर (err)
		जाओ err_health_निकास;

	err = nsim_dev_psample_init(nsim_dev);
	अगर (err)
		जाओ err_bpf_dev_निकास;

	err = nsim_dev_port_add_all(nsim_dev, nsim_bus_dev->port_count);
	अगर (err)
		जाओ err_psample_निकास;

	devlink_params_publish(devlink);
	devlink_reload_enable(devlink);
	वापस 0;

err_psample_निकास:
	nsim_dev_psample_निकास(nsim_dev);
err_bpf_dev_निकास:
	nsim_bpf_dev_निकास(nsim_dev);
err_health_निकास:
	nsim_dev_health_निकास(nsim_dev);
err_fib_destroy:
	nsim_fib_destroy(devlink, nsim_dev->fib_data);
err_debugfs_निकास:
	nsim_dev_debugfs_निकास(nsim_dev);
err_traps_निकास:
	nsim_dev_traps_निकास(devlink);
err_dummy_region_निकास:
	nsim_dev_dummy_region_निकास(nsim_dev);
err_params_unरेजिस्टर:
	devlink_params_unरेजिस्टर(devlink, nsim_devlink_params,
				  ARRAY_SIZE(nsim_devlink_params));
err_dl_unरेजिस्टर:
	devlink_unरेजिस्टर(devlink);
err_resources_unरेजिस्टर:
	devlink_resources_unरेजिस्टर(devlink, शून्य);
err_devlink_मुक्त:
	devlink_मुक्त(devlink);
	वापस err;
पूर्ण

अटल व्योम nsim_dev_reload_destroy(काष्ठा nsim_dev *nsim_dev)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(nsim_dev);

	अगर (devlink_is_reload_failed(devlink))
		वापस;
	debugfs_हटाओ(nsim_dev->take_snapshot);
	nsim_dev_port_del_all(nsim_dev);
	nsim_dev_psample_निकास(nsim_dev);
	nsim_dev_health_निकास(nsim_dev);
	nsim_fib_destroy(devlink, nsim_dev->fib_data);
	nsim_dev_traps_निकास(devlink);
	nsim_dev_dummy_region_निकास(nsim_dev);
	mutex_destroy(&nsim_dev->port_list_lock);
पूर्ण

व्योम nsim_dev_हटाओ(काष्ठा nsim_bus_dev *nsim_bus_dev)
अणु
	काष्ठा nsim_dev *nsim_dev = dev_get_drvdata(&nsim_bus_dev->dev);
	काष्ठा devlink *devlink = priv_to_devlink(nsim_dev);

	devlink_reload_disable(devlink);

	nsim_dev_reload_destroy(nsim_dev);

	nsim_bpf_dev_निकास(nsim_dev);
	nsim_dev_debugfs_निकास(nsim_dev);
	devlink_params_unरेजिस्टर(devlink, nsim_devlink_params,
				  ARRAY_SIZE(nsim_devlink_params));
	devlink_unरेजिस्टर(devlink);
	devlink_resources_unरेजिस्टर(devlink, शून्य);
	devlink_मुक्त(devlink);
पूर्ण

अटल काष्ठा nsim_dev_port *
__nsim_dev_port_lookup(काष्ठा nsim_dev *nsim_dev, अचिन्हित पूर्णांक port_index)
अणु
	काष्ठा nsim_dev_port *nsim_dev_port;

	list_क्रम_each_entry(nsim_dev_port, &nsim_dev->port_list, list)
		अगर (nsim_dev_port->port_index == port_index)
			वापस nsim_dev_port;
	वापस शून्य;
पूर्ण

पूर्णांक nsim_dev_port_add(काष्ठा nsim_bus_dev *nsim_bus_dev,
		      अचिन्हित पूर्णांक port_index)
अणु
	काष्ठा nsim_dev *nsim_dev = dev_get_drvdata(&nsim_bus_dev->dev);
	पूर्णांक err;

	mutex_lock(&nsim_dev->port_list_lock);
	अगर (__nsim_dev_port_lookup(nsim_dev, port_index))
		err = -EEXIST;
	अन्यथा
		err = __nsim_dev_port_add(nsim_dev, port_index);
	mutex_unlock(&nsim_dev->port_list_lock);
	वापस err;
पूर्ण

पूर्णांक nsim_dev_port_del(काष्ठा nsim_bus_dev *nsim_bus_dev,
		      अचिन्हित पूर्णांक port_index)
अणु
	काष्ठा nsim_dev *nsim_dev = dev_get_drvdata(&nsim_bus_dev->dev);
	काष्ठा nsim_dev_port *nsim_dev_port;
	पूर्णांक err = 0;

	mutex_lock(&nsim_dev->port_list_lock);
	nsim_dev_port = __nsim_dev_port_lookup(nsim_dev, port_index);
	अगर (!nsim_dev_port)
		err = -ENOENT;
	अन्यथा
		__nsim_dev_port_del(nsim_dev_port);
	mutex_unlock(&nsim_dev->port_list_lock);
	वापस err;
पूर्ण

पूर्णांक nsim_dev_init(व्योम)
अणु
	nsim_dev_ddir = debugfs_create_dir(DRV_NAME, शून्य);
	वापस PTR_ERR_OR_ZERO(nsim_dev_ddir);
पूर्ण

व्योम nsim_dev_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(nsim_dev_ddir);
पूर्ण
