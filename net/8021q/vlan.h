<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __BEN_VLAN_802_1Q_INC__
#घोषणा __BEN_VLAN_802_1Q_INC__

#समावेश <linux/अगर_vlan.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <linux/list.h>

/* अगर this changes, algorithm will have to be reworked because this
 * depends on completely exhausting the VLAN identअगरier space.  Thus
 * it gives स्थिरant समय look-up, but in many हालs it wastes memory.
 */
#घोषणा VLAN_GROUP_ARRAY_SPLIT_PARTS  8
#घोषणा VLAN_GROUP_ARRAY_PART_LEN     (VLAN_N_VID/VLAN_GROUP_ARRAY_SPLIT_PARTS)

क्रमागत vlan_protos अणु
	VLAN_PROTO_8021Q	= 0,
	VLAN_PROTO_8021AD,
	VLAN_PROTO_NUM,
पूर्ण;

काष्ठा vlan_group अणु
	अचिन्हित पूर्णांक		nr_vlan_devs;
	काष्ठा hlist_node	hlist;	/* linked list */
	काष्ठा net_device **vlan_devices_arrays[VLAN_PROTO_NUM]
					       [VLAN_GROUP_ARRAY_SPLIT_PARTS];
पूर्ण;

काष्ठा vlan_info अणु
	काष्ठा net_device	*real_dev; /* The ethernet(like) device
					    * the vlan is attached to.
					    */
	काष्ठा vlan_group	grp;
	काष्ठा list_head	vid_list;
	अचिन्हित पूर्णांक		nr_vids;
	काष्ठा rcu_head		rcu;
पूर्ण;

अटल अंतरभूत पूर्णांक vlan_proto_idx(__be16 proto)
अणु
	चयन (proto) अणु
	हाल htons(ETH_P_8021Q):
		वापस VLAN_PROTO_8021Q;
	हाल htons(ETH_P_8021AD):
		वापस VLAN_PROTO_8021AD;
	शेष:
		WARN(1, "invalid VLAN protocol: 0x%04x\n", ntohs(proto));
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा net_device *__vlan_group_get_device(काष्ठा vlan_group *vg,
							 अचिन्हित पूर्णांक pidx,
							 u16 vlan_id)
अणु
	काष्ठा net_device **array;

	array = vg->vlan_devices_arrays[pidx]
				       [vlan_id / VLAN_GROUP_ARRAY_PART_LEN];

	/* paired with smp_wmb() in vlan_group_pपुनः_स्मृति_vid() */
	smp_rmb();

	वापस array ? array[vlan_id % VLAN_GROUP_ARRAY_PART_LEN] : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा net_device *vlan_group_get_device(काष्ठा vlan_group *vg,
						       __be16 vlan_proto,
						       u16 vlan_id)
अणु
	पूर्णांक pidx = vlan_proto_idx(vlan_proto);

	अगर (pidx < 0)
		वापस शून्य;

	वापस __vlan_group_get_device(vg, pidx, vlan_id);
पूर्ण

अटल अंतरभूत व्योम vlan_group_set_device(काष्ठा vlan_group *vg,
					 __be16 vlan_proto, u16 vlan_id,
					 काष्ठा net_device *dev)
अणु
	पूर्णांक pidx = vlan_proto_idx(vlan_proto);
	काष्ठा net_device **array;

	अगर (!vg || pidx < 0)
		वापस;
	array = vg->vlan_devices_arrays[pidx]
				       [vlan_id / VLAN_GROUP_ARRAY_PART_LEN];
	array[vlan_id % VLAN_GROUP_ARRAY_PART_LEN] = dev;
पूर्ण

/* Must be invoked with rcu_पढ़ो_lock or with RTNL. */
अटल अंतरभूत काष्ठा net_device *vlan_find_dev(काष्ठा net_device *real_dev,
					       __be16 vlan_proto, u16 vlan_id)
अणु
	काष्ठा vlan_info *vlan_info = rcu_dereference_rtnl(real_dev->vlan_info);

	अगर (vlan_info)
		वापस vlan_group_get_device(&vlan_info->grp,
					     vlan_proto, vlan_id);

	वापस शून्य;
पूर्ण

अटल अंतरभूत netdev_features_t vlan_tnl_features(काष्ठा net_device *real_dev)
अणु
	netdev_features_t ret;

	ret = real_dev->hw_enc_features &
	      (NETIF_F_CSUM_MASK | NETIF_F_ALL_TSO | NETIF_F_GSO_ENCAP_ALL);

	अगर ((ret & NETIF_F_GSO_ENCAP_ALL) && (ret & NETIF_F_CSUM_MASK))
		वापस (ret & ~NETIF_F_CSUM_MASK) | NETIF_F_HW_CSUM;
	वापस 0;
पूर्ण

#घोषणा vlan_group_क्रम_each_dev(grp, i, dev) \
	क्रम ((i) = 0; i < VLAN_PROTO_NUM * VLAN_N_VID; i++) \
		अगर (((dev) = __vlan_group_get_device((grp), (i) / VLAN_N_VID, \
							    (i) % VLAN_N_VID)))

पूर्णांक vlan_filter_push_vids(काष्ठा vlan_info *vlan_info, __be16 proto);
व्योम vlan_filter_drop_vids(काष्ठा vlan_info *vlan_info, __be16 proto);

/* found in vlan_dev.c */
व्योम vlan_dev_set_ingress_priority(स्थिर काष्ठा net_device *dev,
				   u32 skb_prio, u16 vlan_prio);
पूर्णांक vlan_dev_set_egress_priority(स्थिर काष्ठा net_device *dev,
				 u32 skb_prio, u16 vlan_prio);
पूर्णांक vlan_dev_change_flags(स्थिर काष्ठा net_device *dev, u32 flag, u32 mask);
व्योम vlan_dev_get_realdev_name(स्थिर काष्ठा net_device *dev, अक्षर *result);

पूर्णांक vlan_check_real_dev(काष्ठा net_device *real_dev,
			__be16 protocol, u16 vlan_id,
			काष्ठा netlink_ext_ack *extack);
व्योम vlan_setup(काष्ठा net_device *dev);
पूर्णांक रेजिस्टर_vlan_dev(काष्ठा net_device *dev, काष्ठा netlink_ext_ack *extack);
व्योम unरेजिस्टर_vlan_dev(काष्ठा net_device *dev, काष्ठा list_head *head);
व्योम vlan_dev_uninit(काष्ठा net_device *dev);
bool vlan_dev_inherit_address(काष्ठा net_device *dev,
			      काष्ठा net_device *real_dev);

अटल अंतरभूत u32 vlan_get_ingress_priority(काष्ठा net_device *dev,
					    u16 vlan_tci)
अणु
	काष्ठा vlan_dev_priv *vip = vlan_dev_priv(dev);

	वापस vip->ingress_priority_map[(vlan_tci >> VLAN_PRIO_SHIFT) & 0x7];
पूर्ण

#अगर_घोषित CONFIG_VLAN_8021Q_GVRP
पूर्णांक vlan_gvrp_request_join(स्थिर काष्ठा net_device *dev);
व्योम vlan_gvrp_request_leave(स्थिर काष्ठा net_device *dev);
पूर्णांक vlan_gvrp_init_applicant(काष्ठा net_device *dev);
व्योम vlan_gvrp_uninit_applicant(काष्ठा net_device *dev);
पूर्णांक vlan_gvrp_init(व्योम);
व्योम vlan_gvrp_uninit(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक vlan_gvrp_request_join(स्थिर काष्ठा net_device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम vlan_gvrp_request_leave(स्थिर काष्ठा net_device *dev) अणुपूर्ण
अटल अंतरभूत पूर्णांक vlan_gvrp_init_applicant(काष्ठा net_device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम vlan_gvrp_uninit_applicant(काष्ठा net_device *dev) अणुपूर्ण
अटल अंतरभूत पूर्णांक vlan_gvrp_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम vlan_gvrp_uninit(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_VLAN_8021Q_MVRP
पूर्णांक vlan_mvrp_request_join(स्थिर काष्ठा net_device *dev);
व्योम vlan_mvrp_request_leave(स्थिर काष्ठा net_device *dev);
पूर्णांक vlan_mvrp_init_applicant(काष्ठा net_device *dev);
व्योम vlan_mvrp_uninit_applicant(काष्ठा net_device *dev);
पूर्णांक vlan_mvrp_init(व्योम);
व्योम vlan_mvrp_uninit(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक vlan_mvrp_request_join(स्थिर काष्ठा net_device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम vlan_mvrp_request_leave(स्थिर काष्ठा net_device *dev) अणुपूर्ण
अटल अंतरभूत पूर्णांक vlan_mvrp_init_applicant(काष्ठा net_device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम vlan_mvrp_uninit_applicant(काष्ठा net_device *dev) अणुपूर्ण
अटल अंतरभूत पूर्णांक vlan_mvrp_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम vlan_mvrp_uninit(व्योम) अणुपूर्ण
#पूर्ण_अगर

बाह्य स्थिर अक्षर vlan_fullname[];
बाह्य स्थिर अक्षर vlan_version[];
पूर्णांक vlan_netlink_init(व्योम);
व्योम vlan_netlink_fini(व्योम);

बाह्य काष्ठा rtnl_link_ops vlan_link_ops;

बाह्य अचिन्हित पूर्णांक vlan_net_id;

काष्ठा proc_dir_entry;

काष्ठा vlan_net अणु
	/* /proc/net/vlan */
	काष्ठा proc_dir_entry *proc_vlan_dir;
	/* /proc/net/vlan/config */
	काष्ठा proc_dir_entry *proc_vlan_conf;
	/* Determines पूर्णांकerface naming scheme. */
	अचिन्हित लघु name_type;
पूर्ण;

#पूर्ण_अगर /* !(__BEN_VLAN_802_1Q_INC__) */
