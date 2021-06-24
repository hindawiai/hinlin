<शैली गुरु>
/*
 * Copyright (C) 2017 Netronome Systems, Inc.
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
#समावेश <linux/ethtool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <net/devlink.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/xdp.h>

#घोषणा DRV_NAME	"netdevsim"

#घोषणा NSIM_XDP_MAX_MTU	4000

#घोषणा NSIM_EA(extack, msg)	NL_SET_ERR_MSG_MOD((extack), msg)

#घोषणा NSIM_IPSEC_MAX_SA_COUNT		33
#घोषणा NSIM_IPSEC_VALID		BIT(31)
#घोषणा NSIM_UDP_TUNNEL_N_PORTS		4

काष्ठा nsim_sa अणु
	काष्ठा xfrm_state *xs;
	__be32 ipaddr[4];
	u32 key[4];
	u32 salt;
	bool used;
	bool crypt;
	bool rx;
पूर्ण;

काष्ठा nsim_ipsec अणु
	काष्ठा nsim_sa sa[NSIM_IPSEC_MAX_SA_COUNT];
	काष्ठा dentry *pfile;
	u32 count;
	u32 tx;
	u32 ok;
पूर्ण;

काष्ठा nsim_ethtool_छोड़ोparam अणु
	bool rx;
	bool tx;
	bool report_stats_rx;
	bool report_stats_tx;
पूर्ण;

काष्ठा nsim_ethtool अणु
	u32 get_err;
	u32 set_err;
	काष्ठा nsim_ethtool_छोड़ोparam छोड़ोparam;
	काष्ठा ethtool_coalesce coalesce;
	काष्ठा ethtool_ringparam ring;
	काष्ठा ethtool_fecparam fec;
पूर्ण;

काष्ठा netdevsim अणु
	काष्ठा net_device *netdev;
	काष्ठा nsim_dev *nsim_dev;
	काष्ठा nsim_dev_port *nsim_dev_port;

	u64 tx_packets;
	u64 tx_bytes;
	काष्ठा u64_stats_sync syncp;

	काष्ठा nsim_bus_dev *nsim_bus_dev;

	काष्ठा bpf_prog	*bpf_offloaded;
	u32 bpf_offloaded_id;

	काष्ठा xdp_attachment_info xdp;
	काष्ठा xdp_attachment_info xdp_hw;

	bool bpf_tc_accept;
	bool bpf_tc_non_bound_accept;
	bool bpf_xdpdrv_accept;
	bool bpf_xdpoffload_accept;

	bool bpf_map_accept;
	काष्ठा nsim_ipsec ipsec;
	काष्ठा अणु
		u32 inject_error;
		u32 sleep;
		u32 __ports[2][NSIM_UDP_TUNNEL_N_PORTS];
		u32 (*ports)[NSIM_UDP_TUNNEL_N_PORTS];
		काष्ठा debugfs_u32_array dfs_ports[2];
	पूर्ण udp_ports;

	काष्ठा nsim_ethtool ethtool;
पूर्ण;

काष्ठा netdevsim *
nsim_create(काष्ठा nsim_dev *nsim_dev, काष्ठा nsim_dev_port *nsim_dev_port);
व्योम nsim_destroy(काष्ठा netdevsim *ns);

व्योम nsim_ethtool_init(काष्ठा netdevsim *ns);

व्योम nsim_udp_tunnels_debugfs_create(काष्ठा nsim_dev *nsim_dev);
पूर्णांक nsim_udp_tunnels_info_create(काष्ठा nsim_dev *nsim_dev,
				 काष्ठा net_device *dev);
व्योम nsim_udp_tunnels_info_destroy(काष्ठा net_device *dev);

#अगर_घोषित CONFIG_BPF_SYSCALL
पूर्णांक nsim_bpf_dev_init(काष्ठा nsim_dev *nsim_dev);
व्योम nsim_bpf_dev_निकास(काष्ठा nsim_dev *nsim_dev);
पूर्णांक nsim_bpf_init(काष्ठा netdevsim *ns);
व्योम nsim_bpf_uninit(काष्ठा netdevsim *ns);
पूर्णांक nsim_bpf(काष्ठा net_device *dev, काष्ठा netdev_bpf *bpf);
पूर्णांक nsim_bpf_disable_tc(काष्ठा netdevsim *ns);
पूर्णांक nsim_bpf_setup_tc_block_cb(क्रमागत tc_setup_type type,
			       व्योम *type_data, व्योम *cb_priv);
#अन्यथा

अटल अंतरभूत पूर्णांक nsim_bpf_dev_init(काष्ठा nsim_dev *nsim_dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nsim_bpf_dev_निकास(काष्ठा nsim_dev *nsim_dev)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक nsim_bpf_init(काष्ठा netdevsim *ns)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nsim_bpf_uninit(काष्ठा netdevsim *ns)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक nsim_bpf(काष्ठा net_device *dev, काष्ठा netdev_bpf *bpf)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nsim_bpf_disable_tc(काष्ठा netdevsim *ns)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
nsim_bpf_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data,
			   व्योम *cb_priv)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

क्रमागत nsim_resource_id अणु
	NSIM_RESOURCE_NONE,   /* DEVLINK_RESOURCE_ID_PARENT_TOP */
	NSIM_RESOURCE_IPV4,
	NSIM_RESOURCE_IPV4_FIB,
	NSIM_RESOURCE_IPV4_FIB_RULES,
	NSIM_RESOURCE_IPV6,
	NSIM_RESOURCE_IPV6_FIB,
	NSIM_RESOURCE_IPV6_FIB_RULES,
	NSIM_RESOURCE_NEXTHOPS,
पूर्ण;

काष्ठा nsim_dev_health अणु
	काष्ठा devlink_health_reporter *empty_reporter;
	काष्ठा devlink_health_reporter *dummy_reporter;
	काष्ठा dentry *ddir;
	अक्षर *recovered_अवरोध_msg;
	u32 binary_len;
	bool fail_recover;
पूर्ण;

पूर्णांक nsim_dev_health_init(काष्ठा nsim_dev *nsim_dev, काष्ठा devlink *devlink);
व्योम nsim_dev_health_निकास(काष्ठा nsim_dev *nsim_dev);

#अगर IS_ENABLED(CONFIG_PSAMPLE)
पूर्णांक nsim_dev_psample_init(काष्ठा nsim_dev *nsim_dev);
व्योम nsim_dev_psample_निकास(काष्ठा nsim_dev *nsim_dev);
#अन्यथा
अटल अंतरभूत पूर्णांक nsim_dev_psample_init(काष्ठा nsim_dev *nsim_dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nsim_dev_psample_निकास(काष्ठा nsim_dev *nsim_dev)
अणु
पूर्ण
#पूर्ण_अगर

काष्ठा nsim_dev_port अणु
	काष्ठा list_head list;
	काष्ठा devlink_port devlink_port;
	अचिन्हित पूर्णांक port_index;
	काष्ठा dentry *ddir;
	काष्ठा netdevsim *ns;
पूर्ण;

काष्ठा nsim_dev अणु
	काष्ठा nsim_bus_dev *nsim_bus_dev;
	काष्ठा nsim_fib_data *fib_data;
	काष्ठा nsim_trap_data *trap_data;
	काष्ठा dentry *ddir;
	काष्ठा dentry *ports_ddir;
	काष्ठा dentry *take_snapshot;
	काष्ठा bpf_offload_dev *bpf_dev;
	bool bpf_bind_accept;
	bool bpf_bind_verअगरier_accept;
	u32 bpf_bind_verअगरier_delay;
	काष्ठा dentry *ddir_bpf_bound_progs;
	u32 prog_id_gen;
	काष्ठा list_head bpf_bound_progs;
	काष्ठा list_head bpf_bound_maps;
	काष्ठा netdev_phys_item_id चयन_id;
	काष्ठा list_head port_list;
	काष्ठा mutex port_list_lock; /* protects port list */
	bool fw_update_status;
	u32 fw_update_overग_लिखो_mask;
	u32 max_macs;
	bool test1;
	bool करोnt_allow_reload;
	bool fail_reload;
	काष्ठा devlink_region *dummy_region;
	काष्ठा nsim_dev_health health;
	काष्ठा flow_action_cookie *fa_cookie;
	spinlock_t fa_cookie_lock; /* protects fa_cookie */
	bool fail_trap_group_set;
	bool fail_trap_policer_set;
	bool fail_trap_policer_counter_get;
	काष्ठा अणु
		काष्ठा udp_tunnel_nic_shared utn_shared;
		u32 __ports[2][NSIM_UDP_TUNNEL_N_PORTS];
		bool sync_all;
		bool खोलो_only;
		bool ipv4_only;
		bool shared;
		bool अटल_iana_vxlan;
		u32 sleep;
	पूर्ण udp_ports;
	काष्ठा nsim_dev_psample *psample;
पूर्ण;

अटल अंतरभूत काष्ठा net *nsim_dev_net(काष्ठा nsim_dev *nsim_dev)
अणु
	वापस devlink_net(priv_to_devlink(nsim_dev));
पूर्ण

पूर्णांक nsim_dev_init(व्योम);
व्योम nsim_dev_निकास(व्योम);
पूर्णांक nsim_dev_probe(काष्ठा nsim_bus_dev *nsim_bus_dev);
व्योम nsim_dev_हटाओ(काष्ठा nsim_bus_dev *nsim_bus_dev);
पूर्णांक nsim_dev_port_add(काष्ठा nsim_bus_dev *nsim_bus_dev,
		      अचिन्हित पूर्णांक port_index);
पूर्णांक nsim_dev_port_del(काष्ठा nsim_bus_dev *nsim_bus_dev,
		      अचिन्हित पूर्णांक port_index);

काष्ठा nsim_fib_data *nsim_fib_create(काष्ठा devlink *devlink,
				      काष्ठा netlink_ext_ack *extack);
व्योम nsim_fib_destroy(काष्ठा devlink *devlink, काष्ठा nsim_fib_data *fib_data);
u64 nsim_fib_get_val(काष्ठा nsim_fib_data *fib_data,
		     क्रमागत nsim_resource_id res_id, bool max);

#अगर IS_ENABLED(CONFIG_XFRM_OFFLOAD)
व्योम nsim_ipsec_init(काष्ठा netdevsim *ns);
व्योम nsim_ipsec_tearकरोwn(काष्ठा netdevsim *ns);
bool nsim_ipsec_tx(काष्ठा netdevsim *ns, काष्ठा sk_buff *skb);
#अन्यथा
अटल अंतरभूत व्योम nsim_ipsec_init(काष्ठा netdevsim *ns)
अणु
पूर्ण

अटल अंतरभूत व्योम nsim_ipsec_tearकरोwn(काष्ठा netdevsim *ns)
अणु
पूर्ण

अटल अंतरभूत bool nsim_ipsec_tx(काष्ठा netdevsim *ns, काष्ठा sk_buff *skb)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

काष्ठा nsim_vf_config अणु
	पूर्णांक link_state;
	u16 min_tx_rate;
	u16 max_tx_rate;
	u16 vlan;
	__be16 vlan_proto;
	u16 qos;
	u8 vf_mac[ETH_ALEN];
	bool spoofchk_enabled;
	bool trusted;
	bool rss_query_enabled;
पूर्ण;

काष्ठा nsim_bus_dev अणु
	काष्ठा device dev;
	काष्ठा list_head list;
	अचिन्हित पूर्णांक port_count;
	काष्ठा net *initial_net; /* Purpose of this is to carry net poपूर्णांकer
				  * during the probe समय only.
				  */
	अचिन्हित पूर्णांक num_vfs;
	काष्ठा nsim_vf_config *vfconfigs;
	/* Lock क्रम devlink->reload_enabled in netdevsim module */
	काष्ठा mutex nsim_bus_reload_lock;
	bool init;
पूर्ण;

पूर्णांक nsim_bus_init(व्योम);
व्योम nsim_bus_निकास(व्योम);
