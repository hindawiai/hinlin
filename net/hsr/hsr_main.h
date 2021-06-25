<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 *
 * include file क्रम HSR and PRP.
 */

#अगर_अघोषित __HSR_PRIVATE_H
#घोषणा __HSR_PRIVATE_H

#समावेश <linux/netdevice.h>
#समावेश <linux/list.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_hsr.h>

/* Time स्थिरants as specअगरied in the HSR specअगरication (IEC-62439-3 2010)
 * Table 8.
 * All values in milliseconds.
 */
#घोषणा HSR_LIFE_CHECK_INTERVAL		 2000 /* ms */
#घोषणा HSR_NODE_FORGET_TIME		60000 /* ms */
#घोषणा HSR_ANNOUNCE_INTERVAL		  100 /* ms */
#घोषणा HSR_ENTRY_FORGET_TIME		  400 /* ms */

/* By how much may slave1 and slave2 बारtamps of latest received frame from
 * each node dअगरfer beक्रमe we notअगरy of communication problem?
 */
#घोषणा MAX_SLAVE_DIFF			 3000 /* ms */
#घोषणा HSR_SEQNR_START			(अच_लघु_उच्च - 1024)
#घोषणा HSR_SUP_SEQNR_START		(HSR_SEQNR_START / 2)

/* How often shall we check क्रम broken ring and हटाओ node entries older than
 * HSR_NODE_FORGET_TIME?
 */
#घोषणा PRUNE_PERIOD			 3000 /* ms */

#घोषणा HSR_TLV_ANNOUNCE		   22
#घोषणा HSR_TLV_LIFE_CHECK		   23
/* PRP V1 lअगरe check क्रम Duplicate discard */
#घोषणा PRP_TLV_LIFE_CHECK_DD		   20
/* PRP V1 lअगरe check क्रम Duplicate Accept */
#घोषणा PRP_TLV_LIFE_CHECK_DA		   21

/* HSR Tag.
 * As defined in IEC-62439-3:2010, the HSR tag is really अणु ethertype = 0x88FB,
 * path, LSDU_size, sequence Nr पूर्ण. But we let eth_header() create अणु h_dest,
 * h_source, h_proto = 0x88FB पूर्ण, and add अणु path, LSDU_size, sequence Nr,
 * encapsulated protocol पूर्ण instead.
 *
 * Field names as defined in the IEC:2010 standard क्रम HSR.
 */
काष्ठा hsr_tag अणु
	__be16		path_and_LSDU_size;
	__be16		sequence_nr;
	__be16		encap_proto;
पूर्ण __packed;

#घोषणा HSR_HLEN	6

#घोषणा HSR_V1_SUP_LSDUSIZE		52

/* The helper functions below assumes that 'path' occupies the 4 most
 * signअगरicant bits of the 16-bit field shared by 'path' and 'LSDU_size' (or
 * equivalently, the 4 most signअगरicant bits of HSR tag byte 14).
 *
 * This is unclear in the IEC specअगरication; its definition of MAC addresses
 * indicates the spec is written with the least signअगरicant bit first (to the
 * left). This, however, would mean that the LSDU field would be split in two
 * with the path field in-between, which seems strange. I'm guessing the MAC
 * address definition is in error.
 */

अटल अंतरभूत व्योम set_hsr_tag_path(काष्ठा hsr_tag *ht, u16 path)
अणु
	ht->path_and_LSDU_size =
		htons((ntohs(ht->path_and_LSDU_size) & 0x0FFF) | (path << 12));
पूर्ण

अटल अंतरभूत व्योम set_hsr_tag_LSDU_size(काष्ठा hsr_tag *ht, u16 LSDU_size)
अणु
	ht->path_and_LSDU_size = htons((ntohs(ht->path_and_LSDU_size) &
				       0xF000) | (LSDU_size & 0x0FFF));
पूर्ण

काष्ठा hsr_ethhdr अणु
	काष्ठा ethhdr	ethhdr;
	काष्ठा hsr_tag	hsr_tag;
पूर्ण __packed;

काष्ठा hsr_vlan_ethhdr अणु
	काष्ठा vlan_ethhdr vlanhdr;
	काष्ठा hsr_tag	hsr_tag;
पूर्ण __packed;

/* HSR/PRP Supervision Frame data types.
 * Field names as defined in the IEC:2010 standard क्रम HSR.
 */
काष्ठा hsr_sup_tag अणु
	__be16		path_and_HSR_ver;
	__be16		sequence_nr;
	__u8		HSR_TLV_type;
	__u8		HSR_TLV_length;
पूर्ण __packed;

काष्ठा hsr_sup_payload अणु
	अचिन्हित अक्षर	macaddress_A[ETH_ALEN];
पूर्ण __packed;

अटल अंतरभूत व्योम set_hsr_stag_path(काष्ठा hsr_sup_tag *hst, u16 path)
अणु
	set_hsr_tag_path((काष्ठा hsr_tag *)hst, path);
पूर्ण

अटल अंतरभूत व्योम set_hsr_stag_HSR_ver(काष्ठा hsr_sup_tag *hst, u16 HSR_ver)
अणु
	set_hsr_tag_LSDU_size((काष्ठा hsr_tag *)hst, HSR_ver);
पूर्ण

काष्ठा hsrv0_ethhdr_sp अणु
	काष्ठा ethhdr		ethhdr;
	काष्ठा hsr_sup_tag	hsr_sup;
पूर्ण __packed;

काष्ठा hsrv1_ethhdr_sp अणु
	काष्ठा ethhdr		ethhdr;
	काष्ठा hsr_tag		hsr;
	काष्ठा hsr_sup_tag	hsr_sup;
पूर्ण __packed;

क्रमागत hsr_port_type अणु
	HSR_PT_NONE = 0,	/* Must be 0, used by framereg */
	HSR_PT_SLAVE_A,
	HSR_PT_SLAVE_B,
	HSR_PT_INTERLINK,
	HSR_PT_MASTER,
	HSR_PT_PORTS,	/* This must be the last item in the क्रमागत */
पूर्ण;

/* PRP Redunancy Control Trailor (RCT).
 * As defined in IEC-62439-4:2012, the PRP RCT is really अणु sequence Nr,
 * Lan indentअगरier (LanId), LSDU_size and PRP_suffix = 0x88FB पूर्ण.
 *
 * Field names as defined in the IEC:2012 standard क्रम PRP.
 */
काष्ठा prp_rct अणु
	__be16          sequence_nr;
	__be16          lan_id_and_LSDU_size;
	__be16          PRP_suffix;
पूर्ण __packed;

अटल अंतरभूत u16 get_prp_LSDU_size(काष्ठा prp_rct *rct)
अणु
	वापस ntohs(rct->lan_id_and_LSDU_size) & 0x0FFF;
पूर्ण

अटल अंतरभूत व्योम set_prp_lan_id(काष्ठा prp_rct *rct, u16 lan_id)
अणु
	rct->lan_id_and_LSDU_size = htons((ntohs(rct->lan_id_and_LSDU_size) &
					  0x0FFF) | (lan_id << 12));
पूर्ण
अटल अंतरभूत व्योम set_prp_LSDU_size(काष्ठा prp_rct *rct, u16 LSDU_size)
अणु
	rct->lan_id_and_LSDU_size = htons((ntohs(rct->lan_id_and_LSDU_size) &
					  0xF000) | (LSDU_size & 0x0FFF));
पूर्ण

काष्ठा hsr_port अणु
	काष्ठा list_head	port_list;
	काष्ठा net_device	*dev;
	काष्ठा hsr_priv		*hsr;
	क्रमागत hsr_port_type	type;
पूर्ण;

काष्ठा hsr_frame_info;
काष्ठा hsr_node;

काष्ठा hsr_proto_ops अणु
	/* क्रमmat and send supervision frame */
	व्योम (*send_sv_frame)(काष्ठा hsr_port *port, अचिन्हित दीर्घ *पूर्णांकerval);
	व्योम (*handle_san_frame)(bool san, क्रमागत hsr_port_type port,
				 काष्ठा hsr_node *node);
	bool (*drop_frame)(काष्ठा hsr_frame_info *frame, काष्ठा hsr_port *port);
	काष्ठा sk_buff * (*get_untagged_frame)(काष्ठा hsr_frame_info *frame,
					       काष्ठा hsr_port *port);
	काष्ठा sk_buff * (*create_tagged_frame)(काष्ठा hsr_frame_info *frame,
						काष्ठा hsr_port *port);
	पूर्णांक (*fill_frame_info)(__be16 proto, काष्ठा sk_buff *skb,
			       काष्ठा hsr_frame_info *frame);
	bool (*invalid_dan_ingress_frame)(__be16 protocol);
	व्योम (*update_san_info)(काष्ठा hsr_node *node, bool is_sup);
पूर्ण;

काष्ठा hsr_priv अणु
	काष्ठा rcu_head		rcu_head;
	काष्ठा list_head	ports;
	काष्ठा list_head	node_db;	/* Known HSR nodes */
	काष्ठा list_head	self_node_db;	/* MACs of slaves */
	काष्ठा समयr_list	announce_समयr;	/* Supervision frame dispatch */
	काष्ठा समयr_list	prune_समयr;
	पूर्णांक announce_count;
	u16 sequence_nr;
	u16 sup_sequence_nr;	/* For HSRv1 separate seq_nr क्रम supervision */
	क्रमागत hsr_version prot_version;	/* Indicate अगर HSRv0, HSRv1 or PRPv1 */
	spinlock_t seqnr_lock;	/* locking क्रम sequence_nr */
	spinlock_t list_lock;	/* locking क्रम node list */
	काष्ठा hsr_proto_ops	*proto_ops;
#घोषणा PRP_LAN_ID	0x5     /* 0x1010 क्रम A and 0x1011 क्रम B. Bit 0 is set
				 * based on SLAVE_A or SLAVE_B
				 */
	u8 net_id;		/* क्रम PRP, it occupies most signअगरicant 3 bits
				 * of lan_id
				 */
	अचिन्हित अक्षर		sup_multicast_addr[ETH_ALEN] __aligned(माप(u16));
				/* Align to u16 boundary to aव्योम unaligned access
				 * in ether_addr_equal
				 */
#अगर_घोषित	CONFIG_DEBUG_FS
	काष्ठा dentry *node_tbl_root;
#पूर्ण_अगर
पूर्ण;

#घोषणा hsr_क्रम_each_port(hsr, port) \
	list_क्रम_each_entry_rcu((port), &(hsr)->ports, port_list)

काष्ठा hsr_port *hsr_port_get_hsr(काष्ठा hsr_priv *hsr, क्रमागत hsr_port_type pt);

/* Caller must ensure skb is a valid HSR frame */
अटल अंतरभूत u16 hsr_get_skb_sequence_nr(काष्ठा sk_buff *skb)
अणु
	काष्ठा hsr_ethhdr *hsr_ethhdr;

	hsr_ethhdr = (काष्ठा hsr_ethhdr *)skb_mac_header(skb);
	वापस ntohs(hsr_ethhdr->hsr_tag.sequence_nr);
पूर्ण

अटल अंतरभूत काष्ठा prp_rct *skb_get_PRP_rct(काष्ठा sk_buff *skb)
अणु
	अचिन्हित अक्षर *tail = skb_tail_poपूर्णांकer(skb) - HSR_HLEN;

	काष्ठा prp_rct *rct = (काष्ठा prp_rct *)tail;

	अगर (rct->PRP_suffix == htons(ETH_P_PRP))
		वापस rct;

	वापस शून्य;
पूर्ण

/* Assume caller has confirmed this skb is PRP suffixed */
अटल अंतरभूत u16 prp_get_skb_sequence_nr(काष्ठा prp_rct *rct)
अणु
	वापस ntohs(rct->sequence_nr);
पूर्ण

अटल अंतरभूत u16 get_prp_lan_id(काष्ठा prp_rct *rct)
अणु
	वापस ntohs(rct->lan_id_and_LSDU_size) >> 12;
पूर्ण

/* assume there is a valid rct */
अटल अंतरभूत bool prp_check_lsdu_size(काष्ठा sk_buff *skb,
				       काष्ठा prp_rct *rct,
				       bool is_sup)
अणु
	काष्ठा ethhdr *ethhdr;
	पूर्णांक expected_lsdu_size;

	अगर (is_sup) अणु
		expected_lsdu_size = HSR_V1_SUP_LSDUSIZE;
	पूर्ण अन्यथा अणु
		ethhdr = (काष्ठा ethhdr *)skb_mac_header(skb);
		expected_lsdu_size = skb->len - 14;
		अगर (ethhdr->h_proto == htons(ETH_P_8021Q))
			expected_lsdu_size -= 4;
	पूर्ण

	वापस (expected_lsdu_size == get_prp_LSDU_size(rct));
पूर्ण

#अगर IS_ENABLED(CONFIG_DEBUG_FS)
व्योम hsr_debugfs_नाम(काष्ठा net_device *dev);
व्योम hsr_debugfs_init(काष्ठा hsr_priv *priv, काष्ठा net_device *hsr_dev);
व्योम hsr_debugfs_term(काष्ठा hsr_priv *priv);
व्योम hsr_debugfs_create_root(व्योम);
व्योम hsr_debugfs_हटाओ_root(व्योम);
#अन्यथा
अटल अंतरभूत व्योम hsr_debugfs_नाम(काष्ठा net_device *dev)
अणु
पूर्ण
अटल अंतरभूत व्योम hsr_debugfs_init(काष्ठा hsr_priv *priv,
				    काष्ठा net_device *hsr_dev)
अणुपूर्ण
अटल अंतरभूत व्योम hsr_debugfs_term(काष्ठा hsr_priv *priv)
अणुपूर्ण
अटल अंतरभूत व्योम hsr_debugfs_create_root(व्योम)
अणुपूर्ण
अटल अंतरभूत व्योम hsr_debugfs_हटाओ_root(व्योम)
अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /*  __HSR_PRIVATE_H */
