<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * VLAN		An implementation of 802.1Q VLAN tagging.
 *
 * Authors:	Ben Greear <greearb@candelatech.com>
 */
#अगर_अघोषित _LINUX_IF_VLAN_H_
#घोषणा _LINUX_IF_VLAN_H_

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/bug.h>
#समावेश <uapi/linux/अगर_vlan.h>

#घोषणा VLAN_HLEN	4		/* The additional bytes required by VLAN
					 * (in addition to the Ethernet header)
					 */
#घोषणा VLAN_ETH_HLEN	18		/* Total octets in header.	 */
#घोषणा VLAN_ETH_ZLEN	64		/* Min. octets in frame sans FCS */

/*
 * According to 802.3ac, the packet can be 4 bytes दीर्घer. --Klika Jan
 */
#घोषणा VLAN_ETH_DATA_LEN	1500	/* Max. octets in payload	 */
#घोषणा VLAN_ETH_FRAME_LEN	1518	/* Max. octets in frame sans FCS */

#घोषणा VLAN_MAX_DEPTH	8		/* Max. number of nested VLAN tags parsed */

/*
 * 	काष्ठा vlan_hdr - vlan header
 * 	@h_vlan_TCI: priority and VLAN ID
 *	@h_vlan_encapsulated_proto: packet type ID or len
 */
काष्ठा vlan_hdr अणु
	__be16	h_vlan_TCI;
	__be16	h_vlan_encapsulated_proto;
पूर्ण;

/**
 *	काष्ठा vlan_ethhdr - vlan ethernet header (ethhdr + vlan_hdr)
 *	@h_dest: destination ethernet address
 *	@h_source: source ethernet address
 *	@h_vlan_proto: ethernet protocol
 *	@h_vlan_TCI: priority and VLAN ID
 *	@h_vlan_encapsulated_proto: packet type ID or len
 */
काष्ठा vlan_ethhdr अणु
	अचिन्हित अक्षर	h_dest[ETH_ALEN];
	अचिन्हित अक्षर	h_source[ETH_ALEN];
	__be16		h_vlan_proto;
	__be16		h_vlan_TCI;
	__be16		h_vlan_encapsulated_proto;
पूर्ण;

#समावेश <linux/skbuff.h>

अटल अंतरभूत काष्ठा vlan_ethhdr *vlan_eth_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा vlan_ethhdr *)skb_mac_header(skb);
पूर्ण

#घोषणा VLAN_PRIO_MASK		0xe000 /* Priority Code Poपूर्णांक */
#घोषणा VLAN_PRIO_SHIFT		13
#घोषणा VLAN_CFI_MASK		0x1000 /* Canonical Format Indicator / Drop Eligible Indicator */
#घोषणा VLAN_VID_MASK		0x0fff /* VLAN Identअगरier */
#घोषणा VLAN_N_VID		4096

/* found in socket.c */
बाह्य व्योम vlan_ioctl_set(पूर्णांक (*hook)(काष्ठा net *, व्योम __user *));

अटल अंतरभूत bool is_vlan_dev(स्थिर काष्ठा net_device *dev)
अणु
        वापस dev->priv_flags & IFF_802_1Q_VLAN;
पूर्ण

#घोषणा skb_vlan_tag_present(__skb)	((__skb)->vlan_present)
#घोषणा skb_vlan_tag_get(__skb)		((__skb)->vlan_tci)
#घोषणा skb_vlan_tag_get_id(__skb)	((__skb)->vlan_tci & VLAN_VID_MASK)
#घोषणा skb_vlan_tag_get_cfi(__skb)	(!!((__skb)->vlan_tci & VLAN_CFI_MASK))
#घोषणा skb_vlan_tag_get_prio(__skb)	(((__skb)->vlan_tci & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT)

अटल अंतरभूत पूर्णांक vlan_get_rx_ctag_filter_info(काष्ठा net_device *dev)
अणु
	ASSERT_RTNL();
	वापस notअगरier_to_त्रुटि_सं(call_netdevice_notअगरiers(NETDEV_CVLAN_FILTER_PUSH_INFO, dev));
पूर्ण

अटल अंतरभूत व्योम vlan_drop_rx_ctag_filter_info(काष्ठा net_device *dev)
अणु
	ASSERT_RTNL();
	call_netdevice_notअगरiers(NETDEV_CVLAN_FILTER_DROP_INFO, dev);
पूर्ण

अटल अंतरभूत पूर्णांक vlan_get_rx_stag_filter_info(काष्ठा net_device *dev)
अणु
	ASSERT_RTNL();
	वापस notअगरier_to_त्रुटि_सं(call_netdevice_notअगरiers(NETDEV_SVLAN_FILTER_PUSH_INFO, dev));
पूर्ण

अटल अंतरभूत व्योम vlan_drop_rx_stag_filter_info(काष्ठा net_device *dev)
अणु
	ASSERT_RTNL();
	call_netdevice_notअगरiers(NETDEV_SVLAN_FILTER_DROP_INFO, dev);
पूर्ण

/**
 *	काष्ठा vlan_pcpu_stats - VLAN percpu rx/tx stats
 *	@rx_packets: number of received packets
 *	@rx_bytes: number of received bytes
 *	@rx_multicast: number of received multicast packets
 *	@tx_packets: number of transmitted packets
 *	@tx_bytes: number of transmitted bytes
 *	@syncp: synchronization poपूर्णांक क्रम 64bit counters
 *	@rx_errors: number of rx errors
 *	@tx_dropped: number of tx drops
 */
काष्ठा vlan_pcpu_stats अणु
	u64			rx_packets;
	u64			rx_bytes;
	u64			rx_multicast;
	u64			tx_packets;
	u64			tx_bytes;
	काष्ठा u64_stats_sync	syncp;
	u32			rx_errors;
	u32			tx_dropped;
पूर्ण;

#अगर defined(CONFIG_VLAN_8021Q) || defined(CONFIG_VLAN_8021Q_MODULE)

बाह्य काष्ठा net_device *__vlan_find_dev_deep_rcu(काष्ठा net_device *real_dev,
					       __be16 vlan_proto, u16 vlan_id);
बाह्य पूर्णांक vlan_क्रम_each(काष्ठा net_device *dev,
			 पूर्णांक (*action)(काष्ठा net_device *dev, पूर्णांक vid,
				       व्योम *arg), व्योम *arg);
बाह्य काष्ठा net_device *vlan_dev_real_dev(स्थिर काष्ठा net_device *dev);
बाह्य u16 vlan_dev_vlan_id(स्थिर काष्ठा net_device *dev);
बाह्य __be16 vlan_dev_vlan_proto(स्थिर काष्ठा net_device *dev);

/**
 *	काष्ठा vlan_priority_tci_mapping - vlan egress priority mappings
 *	@priority: skb priority
 *	@vlan_qos: vlan priority: (skb->priority << 13) & 0xE000
 *	@next: poपूर्णांकer to next काष्ठा
 */
काष्ठा vlan_priority_tci_mapping अणु
	u32					priority;
	u16					vlan_qos;
	काष्ठा vlan_priority_tci_mapping	*next;
पूर्ण;

काष्ठा proc_dir_entry;
काष्ठा netpoll;

/**
 *	काष्ठा vlan_dev_priv - VLAN निजी device data
 *	@nr_ingress_mappings: number of ingress priority mappings
 *	@ingress_priority_map: ingress priority mappings
 *	@nr_egress_mappings: number of egress priority mappings
 *	@egress_priority_map: hash of egress priority mappings
 *	@vlan_proto: VLAN encapsulation protocol
 *	@vlan_id: VLAN identअगरier
 *	@flags: device flags
 *	@real_dev: underlying netdevice
 *	@real_dev_addr: address of underlying netdevice
 *	@dent: proc dir entry
 *	@vlan_pcpu_stats: ptr to percpu rx stats
 */
काष्ठा vlan_dev_priv अणु
	अचिन्हित पूर्णांक				nr_ingress_mappings;
	u32					ingress_priority_map[8];
	अचिन्हित पूर्णांक				nr_egress_mappings;
	काष्ठा vlan_priority_tci_mapping	*egress_priority_map[16];

	__be16					vlan_proto;
	u16					vlan_id;
	u16					flags;

	काष्ठा net_device			*real_dev;
	अचिन्हित अक्षर				real_dev_addr[ETH_ALEN];

	काष्ठा proc_dir_entry			*dent;
	काष्ठा vlan_pcpu_stats __percpu		*vlan_pcpu_stats;
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	काष्ठा netpoll				*netpoll;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा vlan_dev_priv *vlan_dev_priv(स्थिर काष्ठा net_device *dev)
अणु
	वापस netdev_priv(dev);
पूर्ण

अटल अंतरभूत u16
vlan_dev_get_egress_qos_mask(काष्ठा net_device *dev, u32 skprio)
अणु
	काष्ठा vlan_priority_tci_mapping *mp;

	smp_rmb(); /* coupled with smp_wmb() in vlan_dev_set_egress_priority() */

	mp = vlan_dev_priv(dev)->egress_priority_map[(skprio & 0xF)];
	जबतक (mp) अणु
		अगर (mp->priority == skprio) अणु
			वापस mp->vlan_qos; /* This should alपढ़ोy be shअगरted
					      * to mask correctly with the
					      * VLAN's TCI */
		पूर्ण
		mp = mp->next;
	पूर्ण
	वापस 0;
पूर्ण

बाह्य bool vlan_करो_receive(काष्ठा sk_buff **skb);

बाह्य पूर्णांक vlan_vid_add(काष्ठा net_device *dev, __be16 proto, u16 vid);
बाह्य व्योम vlan_vid_del(काष्ठा net_device *dev, __be16 proto, u16 vid);

बाह्य पूर्णांक vlan_vids_add_by_dev(काष्ठा net_device *dev,
				स्थिर काष्ठा net_device *by_dev);
बाह्य व्योम vlan_vids_del_by_dev(काष्ठा net_device *dev,
				 स्थिर काष्ठा net_device *by_dev);

बाह्य bool vlan_uses_dev(स्थिर काष्ठा net_device *dev);

#अन्यथा
अटल अंतरभूत काष्ठा net_device *
__vlan_find_dev_deep_rcu(काष्ठा net_device *real_dev,
		     __be16 vlan_proto, u16 vlan_id)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक
vlan_क्रम_each(काष्ठा net_device *dev,
	      पूर्णांक (*action)(काष्ठा net_device *dev, पूर्णांक vid, व्योम *arg),
	      व्योम *arg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा net_device *vlan_dev_real_dev(स्थिर काष्ठा net_device *dev)
अणु
	BUG();
	वापस शून्य;
पूर्ण

अटल अंतरभूत u16 vlan_dev_vlan_id(स्थिर काष्ठा net_device *dev)
अणु
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत __be16 vlan_dev_vlan_proto(स्थिर काष्ठा net_device *dev)
अणु
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत u16 vlan_dev_get_egress_qos_mask(काष्ठा net_device *dev,
					       u32 skprio)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool vlan_करो_receive(काष्ठा sk_buff **skb)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक vlan_vid_add(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम vlan_vid_del(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक vlan_vids_add_by_dev(काष्ठा net_device *dev,
				       स्थिर काष्ठा net_device *by_dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम vlan_vids_del_by_dev(काष्ठा net_device *dev,
					स्थिर काष्ठा net_device *by_dev)
अणु
पूर्ण

अटल अंतरभूत bool vlan_uses_dev(स्थिर काष्ठा net_device *dev)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/**
 * eth_type_vlan - check क्रम valid vlan ether type.
 * @ethertype: ether type to check
 *
 * Returns true अगर the ether type is a vlan ether type.
 */
अटल अंतरभूत bool eth_type_vlan(__be16 ethertype)
अणु
	चयन (ethertype) अणु
	हाल htons(ETH_P_8021Q):
	हाल htons(ETH_P_8021AD):
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत bool vlan_hw_offload_capable(netdev_features_t features,
					   __be16 proto)
अणु
	अगर (proto == htons(ETH_P_8021Q) && features & NETIF_F_HW_VLAN_CTAG_TX)
		वापस true;
	अगर (proto == htons(ETH_P_8021AD) && features & NETIF_F_HW_VLAN_STAG_TX)
		वापस true;
	वापस false;
पूर्ण

/**
 * __vlan_insert_inner_tag - inner VLAN tag inserting
 * @skb: skbuff to tag
 * @vlan_proto: VLAN encapsulation protocol
 * @vlan_tci: VLAN TCI to insert
 * @mac_len: MAC header length including outer vlan headers
 *
 * Inserts the VLAN tag पूर्णांकo @skb as part of the payload at offset mac_len
 * Returns error अगर skb_cow_head fails.
 *
 * Does not change skb->protocol so this function can be used during receive.
 */
अटल अंतरभूत पूर्णांक __vlan_insert_inner_tag(काष्ठा sk_buff *skb,
					  __be16 vlan_proto, u16 vlan_tci,
					  अचिन्हित पूर्णांक mac_len)
अणु
	काष्ठा vlan_ethhdr *veth;

	अगर (skb_cow_head(skb, VLAN_HLEN) < 0)
		वापस -ENOMEM;

	skb_push(skb, VLAN_HLEN);

	/* Move the mac header sans proto to the beginning of the new header. */
	अगर (likely(mac_len > ETH_TLEN))
		स_हटाओ(skb->data, skb->data + VLAN_HLEN, mac_len - ETH_TLEN);
	skb->mac_header -= VLAN_HLEN;

	veth = (काष्ठा vlan_ethhdr *)(skb->data + mac_len - ETH_HLEN);

	/* first, the ethernet type */
	अगर (likely(mac_len >= ETH_TLEN)) अणु
		/* h_vlan_encapsulated_proto should alपढ़ोy be populated, and
		 * skb->data has space क्रम h_vlan_proto
		 */
		veth->h_vlan_proto = vlan_proto;
	पूर्ण अन्यथा अणु
		/* h_vlan_encapsulated_proto should not be populated, and
		 * skb->data has no space क्रम h_vlan_proto
		 */
		veth->h_vlan_encapsulated_proto = skb->protocol;
	पूर्ण

	/* now, the TCI */
	veth->h_vlan_TCI = htons(vlan_tci);

	वापस 0;
पूर्ण

/**
 * __vlan_insert_tag - regular VLAN tag inserting
 * @skb: skbuff to tag
 * @vlan_proto: VLAN encapsulation protocol
 * @vlan_tci: VLAN TCI to insert
 *
 * Inserts the VLAN tag पूर्णांकo @skb as part of the payload
 * Returns error अगर skb_cow_head fails.
 *
 * Does not change skb->protocol so this function can be used during receive.
 */
अटल अंतरभूत पूर्णांक __vlan_insert_tag(काष्ठा sk_buff *skb,
				    __be16 vlan_proto, u16 vlan_tci)
अणु
	वापस __vlan_insert_inner_tag(skb, vlan_proto, vlan_tci, ETH_HLEN);
पूर्ण

/**
 * vlan_insert_inner_tag - inner VLAN tag inserting
 * @skb: skbuff to tag
 * @vlan_proto: VLAN encapsulation protocol
 * @vlan_tci: VLAN TCI to insert
 * @mac_len: MAC header length including outer vlan headers
 *
 * Inserts the VLAN tag पूर्णांकo @skb as part of the payload at offset mac_len
 * Returns a VLAN tagged skb. If a new skb is created, @skb is मुक्तd.
 *
 * Following the skb_unshare() example, in हाल of error, the calling function
 * करोesn't have to worry about मुक्तing the original skb.
 *
 * Does not change skb->protocol so this function can be used during receive.
 */
अटल अंतरभूत काष्ठा sk_buff *vlan_insert_inner_tag(काष्ठा sk_buff *skb,
						    __be16 vlan_proto,
						    u16 vlan_tci,
						    अचिन्हित पूर्णांक mac_len)
अणु
	पूर्णांक err;

	err = __vlan_insert_inner_tag(skb, vlan_proto, vlan_tci, mac_len);
	अगर (err) अणु
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण
	वापस skb;
पूर्ण

/**
 * vlan_insert_tag - regular VLAN tag inserting
 * @skb: skbuff to tag
 * @vlan_proto: VLAN encapsulation protocol
 * @vlan_tci: VLAN TCI to insert
 *
 * Inserts the VLAN tag पूर्णांकo @skb as part of the payload
 * Returns a VLAN tagged skb. If a new skb is created, @skb is मुक्तd.
 *
 * Following the skb_unshare() example, in हाल of error, the calling function
 * करोesn't have to worry about मुक्तing the original skb.
 *
 * Does not change skb->protocol so this function can be used during receive.
 */
अटल अंतरभूत काष्ठा sk_buff *vlan_insert_tag(काष्ठा sk_buff *skb,
					      __be16 vlan_proto, u16 vlan_tci)
अणु
	वापस vlan_insert_inner_tag(skb, vlan_proto, vlan_tci, ETH_HLEN);
पूर्ण

/**
 * vlan_insert_tag_set_proto - regular VLAN tag inserting
 * @skb: skbuff to tag
 * @vlan_proto: VLAN encapsulation protocol
 * @vlan_tci: VLAN TCI to insert
 *
 * Inserts the VLAN tag पूर्णांकo @skb as part of the payload
 * Returns a VLAN tagged skb. If a new skb is created, @skb is मुक्तd.
 *
 * Following the skb_unshare() example, in हाल of error, the calling function
 * करोesn't have to worry about मुक्तing the original skb.
 */
अटल अंतरभूत काष्ठा sk_buff *vlan_insert_tag_set_proto(काष्ठा sk_buff *skb,
							__be16 vlan_proto,
							u16 vlan_tci)
अणु
	skb = vlan_insert_tag(skb, vlan_proto, vlan_tci);
	अगर (skb)
		skb->protocol = vlan_proto;
	वापस skb;
पूर्ण

/**
 * __vlan_hwaccel_clear_tag - clear hardware accelerated VLAN info
 * @skb: skbuff to clear
 *
 * Clears the VLAN inक्रमmation from @skb
 */
अटल अंतरभूत व्योम __vlan_hwaccel_clear_tag(काष्ठा sk_buff *skb)
अणु
	skb->vlan_present = 0;
पूर्ण

/**
 * __vlan_hwaccel_copy_tag - copy hardware accelerated VLAN info from another skb
 * @dst: skbuff to copy to
 * @src: skbuff to copy from
 *
 * Copies VLAN inक्रमmation from @src to @dst (क्रम branchless code)
 */
अटल अंतरभूत व्योम __vlan_hwaccel_copy_tag(काष्ठा sk_buff *dst, स्थिर काष्ठा sk_buff *src)
अणु
	dst->vlan_present = src->vlan_present;
	dst->vlan_proto = src->vlan_proto;
	dst->vlan_tci = src->vlan_tci;
पूर्ण

/*
 * __vlan_hwaccel_push_inside - pushes vlan tag to the payload
 * @skb: skbuff to tag
 *
 * Pushes the VLAN tag from @skb->vlan_tci inside to the payload.
 *
 * Following the skb_unshare() example, in हाल of error, the calling function
 * करोesn't have to worry about मुक्तing the original skb.
 */
अटल अंतरभूत काष्ठा sk_buff *__vlan_hwaccel_push_inside(काष्ठा sk_buff *skb)
अणु
	skb = vlan_insert_tag_set_proto(skb, skb->vlan_proto,
					skb_vlan_tag_get(skb));
	अगर (likely(skb))
		__vlan_hwaccel_clear_tag(skb);
	वापस skb;
पूर्ण

/**
 * __vlan_hwaccel_put_tag - hardware accelerated VLAN inserting
 * @skb: skbuff to tag
 * @vlan_proto: VLAN encapsulation protocol
 * @vlan_tci: VLAN TCI to insert
 *
 * Puts the VLAN TCI in @skb->vlan_tci and lets the device करो the rest
 */
अटल अंतरभूत व्योम __vlan_hwaccel_put_tag(काष्ठा sk_buff *skb,
					  __be16 vlan_proto, u16 vlan_tci)
अणु
	skb->vlan_proto = vlan_proto;
	skb->vlan_tci = vlan_tci;
	skb->vlan_present = 1;
पूर्ण

/**
 * __vlan_get_tag - get the VLAN ID that is part of the payload
 * @skb: skbuff to query
 * @vlan_tci: buffer to store value
 *
 * Returns error अगर the skb is not of VLAN type
 */
अटल अंतरभूत पूर्णांक __vlan_get_tag(स्थिर काष्ठा sk_buff *skb, u16 *vlan_tci)
अणु
	काष्ठा vlan_ethhdr *veth = (काष्ठा vlan_ethhdr *)skb->data;

	अगर (!eth_type_vlan(veth->h_vlan_proto))
		वापस -EINVAL;

	*vlan_tci = ntohs(veth->h_vlan_TCI);
	वापस 0;
पूर्ण

/**
 * __vlan_hwaccel_get_tag - get the VLAN ID that is in @skb->cb[]
 * @skb: skbuff to query
 * @vlan_tci: buffer to store value
 *
 * Returns error अगर @skb->vlan_tci is not set correctly
 */
अटल अंतरभूत पूर्णांक __vlan_hwaccel_get_tag(स्थिर काष्ठा sk_buff *skb,
					 u16 *vlan_tci)
अणु
	अगर (skb_vlan_tag_present(skb)) अणु
		*vlan_tci = skb_vlan_tag_get(skb);
		वापस 0;
	पूर्ण अन्यथा अणु
		*vlan_tci = 0;
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * vlan_get_tag - get the VLAN ID from the skb
 * @skb: skbuff to query
 * @vlan_tci: buffer to store value
 *
 * Returns error अगर the skb is not VLAN tagged
 */
अटल अंतरभूत पूर्णांक vlan_get_tag(स्थिर काष्ठा sk_buff *skb, u16 *vlan_tci)
अणु
	अगर (skb->dev->features & NETIF_F_HW_VLAN_CTAG_TX) अणु
		वापस __vlan_hwaccel_get_tag(skb, vlan_tci);
	पूर्ण अन्यथा अणु
		वापस __vlan_get_tag(skb, vlan_tci);
	पूर्ण
पूर्ण

/**
 * vlan_get_protocol - get protocol EtherType.
 * @skb: skbuff to query
 * @type: first vlan protocol
 * @depth: buffer to store length of eth and vlan tags in bytes
 *
 * Returns the EtherType of the packet, regardless of whether it is
 * vlan encapsulated (normal or hardware accelerated) or not.
 */
अटल अंतरभूत __be16 __vlan_get_protocol(स्थिर काष्ठा sk_buff *skb, __be16 type,
					 पूर्णांक *depth)
अणु
	अचिन्हित पूर्णांक vlan_depth = skb->mac_len, parse_depth = VLAN_MAX_DEPTH;

	/* अगर type is 802.1Q/AD then the header should alपढ़ोy be
	 * present at mac_len - VLAN_HLEN (अगर mac_len > 0), or at
	 * ETH_HLEN otherwise
	 */
	अगर (eth_type_vlan(type)) अणु
		अगर (vlan_depth) अणु
			अगर (WARN_ON(vlan_depth < VLAN_HLEN))
				वापस 0;
			vlan_depth -= VLAN_HLEN;
		पूर्ण अन्यथा अणु
			vlan_depth = ETH_HLEN;
		पूर्ण
		करो अणु
			काष्ठा vlan_hdr vhdr, *vh;

			vh = skb_header_poपूर्णांकer(skb, vlan_depth, माप(vhdr), &vhdr);
			अगर (unlikely(!vh || !--parse_depth))
				वापस 0;

			type = vh->h_vlan_encapsulated_proto;
			vlan_depth += VLAN_HLEN;
		पूर्ण जबतक (eth_type_vlan(type));
	पूर्ण

	अगर (depth)
		*depth = vlan_depth;

	वापस type;
पूर्ण

/**
 * vlan_get_protocol - get protocol EtherType.
 * @skb: skbuff to query
 *
 * Returns the EtherType of the packet, regardless of whether it is
 * vlan encapsulated (normal or hardware accelerated) or not.
 */
अटल अंतरभूत __be16 vlan_get_protocol(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस __vlan_get_protocol(skb, skb->protocol, शून्य);
पूर्ण

/* A getter क्रम the SKB protocol field which will handle VLAN tags consistently
 * whether VLAN acceleration is enabled or not.
 */
अटल अंतरभूत __be16 skb_protocol(स्थिर काष्ठा sk_buff *skb, bool skip_vlan)
अणु
	अगर (!skip_vlan)
		/* VLAN acceleration strips the VLAN header from the skb and
		 * moves it to skb->vlan_proto
		 */
		वापस skb_vlan_tag_present(skb) ? skb->vlan_proto : skb->protocol;

	वापस vlan_get_protocol(skb);
पूर्ण

अटल अंतरभूत व्योम vlan_set_encap_proto(काष्ठा sk_buff *skb,
					काष्ठा vlan_hdr *vhdr)
अणु
	__be16 proto;
	अचिन्हित लघु *rawp;

	/*
	 * Was a VLAN packet, grab the encapsulated protocol, which the layer
	 * three protocols care about.
	 */

	proto = vhdr->h_vlan_encapsulated_proto;
	अगर (eth_proto_is_802_3(proto)) अणु
		skb->protocol = proto;
		वापस;
	पूर्ण

	rawp = (अचिन्हित लघु *)(vhdr + 1);
	अगर (*rawp == 0xFFFF)
		/*
		 * This is a magic hack to spot IPX packets. Older Novell
		 * अवरोधs the protocol design and runs IPX over 802.3 without
		 * an 802.2 LLC layer. We look क्रम FFFF which isn't a used
		 * 802.2 SSAP/DSAP. This won't work क्रम fault tolerant netware
		 * but करोes क्रम the rest.
		 */
		skb->protocol = htons(ETH_P_802_3);
	अन्यथा
		/*
		 * Real 802.2 LLC
		 */
		skb->protocol = htons(ETH_P_802_2);
पूर्ण

/**
 * skb_vlan_tagged - check अगर skb is vlan tagged.
 * @skb: skbuff to query
 *
 * Returns true अगर the skb is tagged, regardless of whether it is hardware
 * accelerated or not.
 */
अटल अंतरभूत bool skb_vlan_tagged(स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (!skb_vlan_tag_present(skb) &&
	    likely(!eth_type_vlan(skb->protocol)))
		वापस false;

	वापस true;
पूर्ण

/**
 * skb_vlan_tagged_multi - check अगर skb is vlan tagged with multiple headers.
 * @skb: skbuff to query
 *
 * Returns true अगर the skb is tagged with multiple vlan headers, regardless
 * of whether it is hardware accelerated or not.
 */
अटल अंतरभूत bool skb_vlan_tagged_multi(काष्ठा sk_buff *skb)
अणु
	__be16 protocol = skb->protocol;

	अगर (!skb_vlan_tag_present(skb)) अणु
		काष्ठा vlan_ethhdr *veh;

		अगर (likely(!eth_type_vlan(protocol)))
			वापस false;

		अगर (unlikely(!pskb_may_pull(skb, VLAN_ETH_HLEN)))
			वापस false;

		veh = (काष्ठा vlan_ethhdr *)skb->data;
		protocol = veh->h_vlan_encapsulated_proto;
	पूर्ण

	अगर (!eth_type_vlan(protocol))
		वापस false;

	वापस true;
पूर्ण

/**
 * vlan_features_check - drop unsafe features क्रम skb with multiple tags.
 * @skb: skbuff to query
 * @features: features to be checked
 *
 * Returns features without unsafe ones अगर the skb has multiple tags.
 */
अटल अंतरभूत netdev_features_t vlan_features_check(काष्ठा sk_buff *skb,
						    netdev_features_t features)
अणु
	अगर (skb_vlan_tagged_multi(skb)) अणु
		/* In the हाल of multi-tagged packets, use a direct mask
		 * instead of using netdev_पूर्णांकeresect_features(), to make
		 * sure that only devices supporting NETIF_F_HW_CSUM will
		 * have checksum offloading support.
		 */
		features &= NETIF_F_SG | NETIF_F_HIGHDMA | NETIF_F_HW_CSUM |
			    NETIF_F_FRAGLIST | NETIF_F_HW_VLAN_CTAG_TX |
			    NETIF_F_HW_VLAN_STAG_TX;
	पूर्ण

	वापस features;
पूर्ण

/**
 * compare_vlan_header - Compare two vlan headers
 * @h1: Poपूर्णांकer to vlan header
 * @h2: Poपूर्णांकer to vlan header
 *
 * Compare two vlan headers, वापसs 0 अगर equal.
 *
 * Please note that alignment of h1 & h2 are only guaranteed to be 16 bits.
 */
अटल अंतरभूत अचिन्हित दीर्घ compare_vlan_header(स्थिर काष्ठा vlan_hdr *h1,
						स्थिर काष्ठा vlan_hdr *h2)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	वापस *(u32 *)h1 ^ *(u32 *)h2;
#अन्यथा
	वापस ((__क्रमce u32)h1->h_vlan_TCI ^ (__क्रमce u32)h2->h_vlan_TCI) |
	       ((__क्रमce u32)h1->h_vlan_encapsulated_proto ^
		(__क्रमce u32)h2->h_vlan_encapsulated_proto);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर /* !(_LINUX_IF_VLAN_H_) */
