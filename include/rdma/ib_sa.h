<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Voltaire, Inc.  All rights reserved.
 * Copyright (c) 2006 Intel Corporation.  All rights reserved.
 */

#अगर_अघोषित IB_SA_H
#घोषणा IB_SA_H

#समावेश <linux/completion.h>
#समावेश <linux/compiler.h>

#समावेश <linux/atomic.h>
#समावेश <linux/netdevice.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/opa_addr.h>

क्रमागत अणु
	IB_SA_CLASS_VERSION		= 2,	/* IB spec version 1.1/1.2 */

	IB_SA_METHOD_GET_TABLE		= 0x12,
	IB_SA_METHOD_GET_TABLE_RESP	= 0x92,
	IB_SA_METHOD_DELETE		= 0x15,
	IB_SA_METHOD_DELETE_RESP	= 0x95,
	IB_SA_METHOD_GET_MULTI		= 0x14,
	IB_SA_METHOD_GET_MULTI_RESP	= 0x94,
	IB_SA_METHOD_GET_TRACE_TBL	= 0x13
पूर्ण;

#घोषणा OPA_SA_CLASS_VERSION	0x80
क्रमागत अणु
	IB_SA_ATTR_CLASS_PORTINFO    = 0x01,
	IB_SA_ATTR_NOTICE	     = 0x02,
	IB_SA_ATTR_INFORM_INFO	     = 0x03,
	IB_SA_ATTR_NODE_REC	     = 0x11,
	IB_SA_ATTR_PORT_INFO_REC     = 0x12,
	IB_SA_ATTR_SL2VL_REC	     = 0x13,
	IB_SA_ATTR_SWITCH_REC	     = 0x14,
	IB_SA_ATTR_LINEAR_FDB_REC    = 0x15,
	IB_SA_ATTR_RANDOM_FDB_REC    = 0x16,
	IB_SA_ATTR_MCAST_FDB_REC     = 0x17,
	IB_SA_ATTR_SM_INFO_REC	     = 0x18,
	IB_SA_ATTR_LINK_REC	     = 0x20,
	IB_SA_ATTR_GUID_INFO_REC     = 0x30,
	IB_SA_ATTR_SERVICE_REC	     = 0x31,
	IB_SA_ATTR_PARTITION_REC     = 0x33,
	IB_SA_ATTR_PATH_REC	     = 0x35,
	IB_SA_ATTR_VL_ARB_REC	     = 0x36,
	IB_SA_ATTR_MC_MEMBER_REC     = 0x38,
	IB_SA_ATTR_TRACE_REC	     = 0x39,
	IB_SA_ATTR_MULTI_PATH_REC    = 0x3a,
	IB_SA_ATTR_SERVICE_ASSOC_REC = 0x3b,
	IB_SA_ATTR_INFORM_INFO_REC   = 0xf3
पूर्ण;

क्रमागत ib_sa_selector अणु
	IB_SA_GT   = 0,
	IB_SA_LT   = 1,
	IB_SA_EQ   = 2,
	/*
	 * The meaning of "best" depends on the attribute: क्रम
	 * example, क्रम MTU best will वापस the largest available
	 * MTU, जबतक क्रम packet lअगरe समय, best will वापस the
	 * smallest available lअगरe समय.
	 */
	IB_SA_BEST = 3
पूर्ण;

/*
 * There are 4 types of join states:
 * FullMember, NonMember, SendOnlyNonMember, SendOnlyFullMember.
 * The order corresponds to JoinState bits in MCMemberRecord.
 */
क्रमागत ib_sa_mc_join_states अणु
	FULLMEMBER_JOIN,
	NONMEMBER_JOIN,
	SENDONLY_NONMEBER_JOIN,
	SENDONLY_FULLMEMBER_JOIN,
	NUM_JOIN_MEMBERSHIP_TYPES,
पूर्ण;

#घोषणा IB_SA_CAP_MASK2_SENDONLY_FULL_MEM_SUPPORT	BIT(12)

/*
 * Structures क्रम SA records are named "struct ib_sa_xxx_rec."  No
 * attempt is made to pack काष्ठाures to match the physical layout of
 * SA records in SA MADs; all packing and unpacking is handled by the
 * SA query code.
 *
 * For a record with काष्ठाure ib_sa_xxx_rec, the naming convention
 * क्रम the component mask value क्रम field yyy is IB_SA_XXX_REC_YYY (we
 * never use dअगरferent abbreviations or otherwise change the spelling
 * of xxx/yyy between ib_sa_xxx_rec.yyy and IB_SA_XXX_REC_YYY).
 *
 * Reserved rows are indicated with comments to help मुख्यtainability.
 */

#घोषणा IB_SA_PATH_REC_SERVICE_ID		       (IB_SA_COMP_MASK( 0) |\
							IB_SA_COMP_MASK( 1))
#घोषणा IB_SA_PATH_REC_DGID				IB_SA_COMP_MASK( 2)
#घोषणा IB_SA_PATH_REC_SGID				IB_SA_COMP_MASK( 3)
#घोषणा IB_SA_PATH_REC_DLID				IB_SA_COMP_MASK( 4)
#घोषणा IB_SA_PATH_REC_SLID				IB_SA_COMP_MASK( 5)
#घोषणा IB_SA_PATH_REC_RAW_TRAFFIC			IB_SA_COMP_MASK( 6)
/* reserved:								 7 */
#घोषणा IB_SA_PATH_REC_FLOW_LABEL       		IB_SA_COMP_MASK( 8)
#घोषणा IB_SA_PATH_REC_HOP_LIMIT			IB_SA_COMP_MASK( 9)
#घोषणा IB_SA_PATH_REC_TRAFFIC_CLASS			IB_SA_COMP_MASK(10)
#घोषणा IB_SA_PATH_REC_REVERSIBLE			IB_SA_COMP_MASK(11)
#घोषणा IB_SA_PATH_REC_NUMB_PATH			IB_SA_COMP_MASK(12)
#घोषणा IB_SA_PATH_REC_PKEY				IB_SA_COMP_MASK(13)
#घोषणा IB_SA_PATH_REC_QOS_CLASS			IB_SA_COMP_MASK(14)
#घोषणा IB_SA_PATH_REC_SL				IB_SA_COMP_MASK(15)
#घोषणा IB_SA_PATH_REC_MTU_SELECTOR			IB_SA_COMP_MASK(16)
#घोषणा IB_SA_PATH_REC_MTU				IB_SA_COMP_MASK(17)
#घोषणा IB_SA_PATH_REC_RATE_SELECTOR			IB_SA_COMP_MASK(18)
#घोषणा IB_SA_PATH_REC_RATE				IB_SA_COMP_MASK(19)
#घोषणा IB_SA_PATH_REC_PACKET_LIFE_TIME_SELECTOR	IB_SA_COMP_MASK(20)
#घोषणा IB_SA_PATH_REC_PACKET_LIFE_TIME			IB_SA_COMP_MASK(21)
#घोषणा IB_SA_PATH_REC_PREFERENCE			IB_SA_COMP_MASK(22)

क्रमागत sa_path_rec_type अणु
	SA_PATH_REC_TYPE_IB,
	SA_PATH_REC_TYPE_ROCE_V1,
	SA_PATH_REC_TYPE_ROCE_V2,
	SA_PATH_REC_TYPE_OPA
पूर्ण;

काष्ठा sa_path_rec_ib अणु
	__be16       dlid;
	__be16       slid;
	u8           raw_traffic;
पूर्ण;

/**
 * काष्ठा sa_path_rec_roce - RoCE specअगरic portion of the path record entry
 * @route_resolved:	When set, it indicates that this route is alपढ़ोy
 *			resolved क्रम this path record entry.
 * @dmac:		Destination mac address क्रम the given DGID entry
 *			of the path record entry.
 */
काष्ठा sa_path_rec_roce अणु
	bool	route_resolved;
	u8	dmac[ETH_ALEN];
पूर्ण;

काष्ठा sa_path_rec_opa अणु
	__be32       dlid;
	__be32       slid;
	u8           raw_traffic;
	u8	     l2_8B;
	u8	     l2_10B;
	u8	     l2_9B;
	u8	     l2_16B;
	u8	     qos_type;
	u8	     qos_priority;
पूर्ण;

काष्ठा sa_path_rec अणु
	जोड़ ib_gid dgid;
	जोड़ ib_gid sgid;
	__be64       service_id;
	/* reserved */
	__be32       flow_label;
	u8           hop_limit;
	u8           traffic_class;
	u8           reversible;
	u8           numb_path;
	__be16       pkey;
	__be16       qos_class;
	u8           sl;
	u8           mtu_selector;
	u8           mtu;
	u8           rate_selector;
	u8           rate;
	u8           packet_lअगरe_समय_selector;
	u8           packet_lअगरe_समय;
	u8           preference;
	जोड़ अणु
		काष्ठा sa_path_rec_ib ib;
		काष्ठा sa_path_rec_roce roce;
		काष्ठा sa_path_rec_opa opa;
	पूर्ण;
	क्रमागत sa_path_rec_type rec_type;
पूर्ण;

अटल अंतरभूत क्रमागत ib_gid_type
		sa_conv_pathrec_to_gid_type(काष्ठा sa_path_rec *rec)
अणु
	चयन (rec->rec_type) अणु
	हाल SA_PATH_REC_TYPE_ROCE_V1:
		वापस IB_GID_TYPE_ROCE;
	हाल SA_PATH_REC_TYPE_ROCE_V2:
		वापस IB_GID_TYPE_ROCE_UDP_ENCAP;
	शेष:
		वापस IB_GID_TYPE_IB;
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत sa_path_rec_type
		sa_conv_gid_to_pathrec_type(क्रमागत ib_gid_type type)
अणु
	चयन (type) अणु
	हाल IB_GID_TYPE_ROCE:
		वापस SA_PATH_REC_TYPE_ROCE_V1;
	हाल IB_GID_TYPE_ROCE_UDP_ENCAP:
		वापस SA_PATH_REC_TYPE_ROCE_V2;
	शेष:
		वापस SA_PATH_REC_TYPE_IB;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम path_conv_opa_to_ib(काष्ठा sa_path_rec *ib,
				       काष्ठा sa_path_rec *opa)
अणु
	अगर ((be32_to_cpu(opa->opa.dlid) >=
	     be16_to_cpu(IB_MULTICAST_LID_BASE)) ||
	    (be32_to_cpu(opa->opa.slid) >=
	     be16_to_cpu(IB_MULTICAST_LID_BASE))) अणु
		/* Create OPA GID and zero out the LID */
		ib->dgid.global.पूर्णांकerface_id
				= OPA_MAKE_ID(be32_to_cpu(opa->opa.dlid));
		ib->dgid.global.subnet_prefix
				= opa->dgid.global.subnet_prefix;
		ib->sgid.global.पूर्णांकerface_id
				= OPA_MAKE_ID(be32_to_cpu(opa->opa.slid));
		ib->dgid.global.subnet_prefix
				= opa->dgid.global.subnet_prefix;
		ib->ib.dlid	= 0;

		ib->ib.slid	= 0;
	पूर्ण अन्यथा अणु
		ib->ib.dlid	= htons(ntohl(opa->opa.dlid));
		ib->ib.slid	= htons(ntohl(opa->opa.slid));
	पूर्ण
	ib->service_id		= opa->service_id;
	ib->ib.raw_traffic	= opa->opa.raw_traffic;
पूर्ण

अटल अंतरभूत व्योम path_conv_ib_to_opa(काष्ठा sa_path_rec *opa,
				       काष्ठा sa_path_rec *ib)
अणु
	__be32 slid, dlid;

	अगर ((ib_is_opa_gid(&ib->sgid)) ||
	    (ib_is_opa_gid(&ib->dgid))) अणु
		slid = htonl(opa_get_lid_from_gid(&ib->sgid));
		dlid = htonl(opa_get_lid_from_gid(&ib->dgid));
	पूर्ण अन्यथा अणु
		slid = htonl(ntohs(ib->ib.slid));
		dlid = htonl(ntohs(ib->ib.dlid));
	पूर्ण
	opa->opa.slid		= slid;
	opa->opa.dlid		= dlid;
	opa->service_id		= ib->service_id;
	opa->opa.raw_traffic	= ib->ib.raw_traffic;
पूर्ण

/* Convert from OPA to IB path record */
अटल अंतरभूत व्योम sa_convert_path_opa_to_ib(काष्ठा sa_path_rec *dest,
					     काष्ठा sa_path_rec *src)
अणु
	अगर (src->rec_type != SA_PATH_REC_TYPE_OPA)
		वापस;

	*dest = *src;
	dest->rec_type = SA_PATH_REC_TYPE_IB;
	path_conv_opa_to_ib(dest, src);
पूर्ण

/* Convert from IB to OPA path record */
अटल अंतरभूत व्योम sa_convert_path_ib_to_opa(काष्ठा sa_path_rec *dest,
					     काष्ठा sa_path_rec *src)
अणु
	अगर (src->rec_type != SA_PATH_REC_TYPE_IB)
		वापस;

	/* Do a काष्ठाure copy and overग_लिखो the relevant fields */
	*dest = *src;
	dest->rec_type = SA_PATH_REC_TYPE_OPA;
	path_conv_ib_to_opa(dest, src);
पूर्ण

#घोषणा IB_SA_MCMEMBER_REC_MGID				IB_SA_COMP_MASK( 0)
#घोषणा IB_SA_MCMEMBER_REC_PORT_GID			IB_SA_COMP_MASK( 1)
#घोषणा IB_SA_MCMEMBER_REC_QKEY				IB_SA_COMP_MASK( 2)
#घोषणा IB_SA_MCMEMBER_REC_MLID				IB_SA_COMP_MASK( 3)
#घोषणा IB_SA_MCMEMBER_REC_MTU_SELECTOR			IB_SA_COMP_MASK( 4)
#घोषणा IB_SA_MCMEMBER_REC_MTU				IB_SA_COMP_MASK( 5)
#घोषणा IB_SA_MCMEMBER_REC_TRAFFIC_CLASS		IB_SA_COMP_MASK( 6)
#घोषणा IB_SA_MCMEMBER_REC_PKEY				IB_SA_COMP_MASK( 7)
#घोषणा IB_SA_MCMEMBER_REC_RATE_SELECTOR		IB_SA_COMP_MASK( 8)
#घोषणा IB_SA_MCMEMBER_REC_RATE				IB_SA_COMP_MASK( 9)
#घोषणा IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME_SELECTOR	IB_SA_COMP_MASK(10)
#घोषणा IB_SA_MCMEMBER_REC_PACKET_LIFE_TIME		IB_SA_COMP_MASK(11)
#घोषणा IB_SA_MCMEMBER_REC_SL				IB_SA_COMP_MASK(12)
#घोषणा IB_SA_MCMEMBER_REC_FLOW_LABEL			IB_SA_COMP_MASK(13)
#घोषणा IB_SA_MCMEMBER_REC_HOP_LIMIT			IB_SA_COMP_MASK(14)
#घोषणा IB_SA_MCMEMBER_REC_SCOPE			IB_SA_COMP_MASK(15)
#घोषणा IB_SA_MCMEMBER_REC_JOIN_STATE			IB_SA_COMP_MASK(16)
#घोषणा IB_SA_MCMEMBER_REC_PROXY_JOIN			IB_SA_COMP_MASK(17)

काष्ठा ib_sa_mcmember_rec अणु
	जोड़ ib_gid mgid;
	जोड़ ib_gid port_gid;
	__be32       qkey;
	__be16       mlid;
	u8           mtu_selector;
	u8           mtu;
	u8           traffic_class;
	__be16       pkey;
	u8 	     rate_selector;
	u8 	     rate;
	u8 	     packet_lअगरe_समय_selector;
	u8 	     packet_lअगरe_समय;
	u8           sl;
	__be32       flow_label;
	u8           hop_limit;
	u8           scope;
	u8           join_state;
	u8           proxy_join;
पूर्ण;

/* Service Record Component Mask Sec 15.2.5.14 Ver 1.1	*/
#घोषणा IB_SA_SERVICE_REC_SERVICE_ID			IB_SA_COMP_MASK( 0)
#घोषणा IB_SA_SERVICE_REC_SERVICE_GID			IB_SA_COMP_MASK( 1)
#घोषणा IB_SA_SERVICE_REC_SERVICE_PKEY			IB_SA_COMP_MASK( 2)
/* reserved:								 3 */
#घोषणा IB_SA_SERVICE_REC_SERVICE_LEASE			IB_SA_COMP_MASK( 4)
#घोषणा IB_SA_SERVICE_REC_SERVICE_KEY			IB_SA_COMP_MASK( 5)
#घोषणा IB_SA_SERVICE_REC_SERVICE_NAME			IB_SA_COMP_MASK( 6)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_0		IB_SA_COMP_MASK( 7)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_1		IB_SA_COMP_MASK( 8)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_2		IB_SA_COMP_MASK( 9)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_3		IB_SA_COMP_MASK(10)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_4		IB_SA_COMP_MASK(11)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_5		IB_SA_COMP_MASK(12)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_6		IB_SA_COMP_MASK(13)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_7		IB_SA_COMP_MASK(14)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_8		IB_SA_COMP_MASK(15)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_9		IB_SA_COMP_MASK(16)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_10		IB_SA_COMP_MASK(17)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_11		IB_SA_COMP_MASK(18)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_12		IB_SA_COMP_MASK(19)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_13		IB_SA_COMP_MASK(20)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_14		IB_SA_COMP_MASK(21)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA8_15		IB_SA_COMP_MASK(22)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA16_0		IB_SA_COMP_MASK(23)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA16_1		IB_SA_COMP_MASK(24)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA16_2		IB_SA_COMP_MASK(25)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA16_3		IB_SA_COMP_MASK(26)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA16_4		IB_SA_COMP_MASK(27)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA16_5		IB_SA_COMP_MASK(28)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA16_6		IB_SA_COMP_MASK(29)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA16_7		IB_SA_COMP_MASK(30)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA32_0		IB_SA_COMP_MASK(31)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA32_1		IB_SA_COMP_MASK(32)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA32_2		IB_SA_COMP_MASK(33)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA32_3		IB_SA_COMP_MASK(34)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA64_0		IB_SA_COMP_MASK(35)
#घोषणा IB_SA_SERVICE_REC_SERVICE_DATA64_1		IB_SA_COMP_MASK(36)

#घोषणा IB_DEFAULT_SERVICE_LEASE 	0xFFFFFFFF

काष्ठा ib_sa_service_rec अणु
	u64		id;
	जोड़ ib_gid	gid;
	__be16 		pkey;
	/* reserved */
	u32		lease;
	u8		key[16];
	u8		name[64];
	u8		data8[16];
	u16		data16[8];
	u32		data32[4];
	u64		data64[2];
पूर्ण;

#घोषणा IB_SA_GUIDINFO_REC_LID		IB_SA_COMP_MASK(0)
#घोषणा IB_SA_GUIDINFO_REC_BLOCK_NUM	IB_SA_COMP_MASK(1)
#घोषणा IB_SA_GUIDINFO_REC_RES1		IB_SA_COMP_MASK(2)
#घोषणा IB_SA_GUIDINFO_REC_RES2		IB_SA_COMP_MASK(3)
#घोषणा IB_SA_GUIDINFO_REC_GID0		IB_SA_COMP_MASK(4)
#घोषणा IB_SA_GUIDINFO_REC_GID1		IB_SA_COMP_MASK(5)
#घोषणा IB_SA_GUIDINFO_REC_GID2		IB_SA_COMP_MASK(6)
#घोषणा IB_SA_GUIDINFO_REC_GID3		IB_SA_COMP_MASK(7)
#घोषणा IB_SA_GUIDINFO_REC_GID4		IB_SA_COMP_MASK(8)
#घोषणा IB_SA_GUIDINFO_REC_GID5		IB_SA_COMP_MASK(9)
#घोषणा IB_SA_GUIDINFO_REC_GID6		IB_SA_COMP_MASK(10)
#घोषणा IB_SA_GUIDINFO_REC_GID7		IB_SA_COMP_MASK(11)

काष्ठा ib_sa_guidinfo_rec अणु
	__be16	lid;
	u8	block_num;
	/* reserved */
	u8	res1;
	__be32	res2;
	u8	guid_info_list[64];
पूर्ण;

काष्ठा ib_sa_client अणु
	atomic_t users;
	काष्ठा completion comp;
पूर्ण;

/**
 * ib_sa_रेजिस्टर_client - Register an SA client.
 */
व्योम ib_sa_रेजिस्टर_client(काष्ठा ib_sa_client *client);

/**
 * ib_sa_unरेजिस्टर_client - Deरेजिस्टर an SA client.
 * @client: Client object to deरेजिस्टर.
 */
व्योम ib_sa_unरेजिस्टर_client(काष्ठा ib_sa_client *client);

काष्ठा ib_sa_query;

व्योम ib_sa_cancel_query(पूर्णांक id, काष्ठा ib_sa_query *query);

पूर्णांक ib_sa_path_rec_get(काष्ठा ib_sa_client *client, काष्ठा ib_device *device,
		       u32 port_num, काष्ठा sa_path_rec *rec,
		       ib_sa_comp_mask comp_mask, अचिन्हित दीर्घ समयout_ms,
		       gfp_t gfp_mask,
		       व्योम (*callback)(पूर्णांक status, काष्ठा sa_path_rec *resp,
					व्योम *context),
		       व्योम *context, काष्ठा ib_sa_query **query);

पूर्णांक ib_sa_service_rec_query(काष्ठा ib_sa_client *client,
			    काष्ठा ib_device *device, u32 port_num, u8 method,
			    काष्ठा ib_sa_service_rec *rec,
			    ib_sa_comp_mask comp_mask, अचिन्हित दीर्घ समयout_ms,
			    gfp_t gfp_mask,
			    व्योम (*callback)(पूर्णांक status,
					     काष्ठा ib_sa_service_rec *resp,
					     व्योम *context),
			    व्योम *context, काष्ठा ib_sa_query **sa_query);

काष्ठा ib_sa_multicast अणु
	काष्ठा ib_sa_mcmember_rec rec;
	ib_sa_comp_mask		comp_mask;
	पूर्णांक			(*callback)(पूर्णांक status,
					    काष्ठा ib_sa_multicast *multicast);
	व्योम			*context;
पूर्ण;

/**
 * ib_sa_join_multicast - Initiates a join request to the specअगरied multicast
 *   group.
 * @client: SA client
 * @device: Device associated with the multicast group.
 * @port_num: Port on the specअगरied device to associate with the multicast
 *   group.
 * @rec: SA multicast member record specअगरying group attributes.
 * @comp_mask: Component mask indicating which group attributes of %rec are
 *   valid.
 * @gfp_mask: GFP mask क्रम memory allocations.
 * @callback: User callback invoked once the join operation completes.
 * @context: User specअगरied context stored with the ib_sa_multicast काष्ठाure.
 *
 * This call initiates a multicast join request with the SA क्रम the specअगरied
 * multicast group.  If the join operation is started successfully, it वापसs
 * an ib_sa_multicast काष्ठाure that is used to track the multicast operation.
 * Users must मुक्त this काष्ठाure by calling ib_मुक्त_multicast, even अगर the
 * join operation later fails.  (The callback status is non-zero.)
 *
 * If the join operation fails; status will be non-zero, with the following
 * failures possible:
 * -ETIMEDOUT: The request समयd out.
 * -EIO: An error occurred sending the query.
 * -EINVAL: The MCMemberRecord values dअगरfered from the existing group's.
 * -ENETRESET: Indicates that an fatal error has occurred on the multicast
 *   group, and the user must rejoin the group to जारी using it.
 */
काष्ठा ib_sa_multicast *ib_sa_join_multicast(काष्ठा ib_sa_client *client,
					     काष्ठा ib_device *device,
					     u32 port_num,
					     काष्ठा ib_sa_mcmember_rec *rec,
					     ib_sa_comp_mask comp_mask, gfp_t gfp_mask,
					     पूर्णांक (*callback)(पूर्णांक status,
							     काष्ठा ib_sa_multicast
								    *multicast),
					     व्योम *context);

/**
 * ib_मुक्त_multicast - Frees the multicast tracking काष्ठाure, and releases
 *    any reference on the multicast group.
 * @multicast: Multicast tracking काष्ठाure allocated by ib_join_multicast.
 *
 * This call blocks until the multicast identअगरier is destroyed.  It may
 * not be called from within the multicast callback; however, वापसing a non-
 * zero value from the callback will result in destroying the multicast
 * tracking काष्ठाure.
 */
व्योम ib_sa_मुक्त_multicast(काष्ठा ib_sa_multicast *multicast);

/**
 * ib_get_mcmember_rec - Looks up a multicast member record by its MGID and
 *   वापसs it अगर found.
 * @device: Device associated with the multicast group.
 * @port_num: Port on the specअगरied device to associate with the multicast
 *   group.
 * @mgid: MGID of multicast group.
 * @rec: Location to copy SA multicast member record.
 */
पूर्णांक ib_sa_get_mcmember_rec(काष्ठा ib_device *device, u32 port_num,
			   जोड़ ib_gid *mgid, काष्ठा ib_sa_mcmember_rec *rec);

/**
 * ib_init_ah_from_mcmember - Initialize address handle attributes based on
 * an SA multicast member record.
 */
पूर्णांक ib_init_ah_from_mcmember(काष्ठा ib_device *device, u32 port_num,
			     काष्ठा ib_sa_mcmember_rec *rec,
			     काष्ठा net_device *ndev,
			     क्रमागत ib_gid_type gid_type,
			     काष्ठा rdma_ah_attr *ah_attr);

पूर्णांक ib_init_ah_attr_from_path(काष्ठा ib_device *device, u32 port_num,
			      काष्ठा sa_path_rec *rec,
			      काष्ठा rdma_ah_attr *ah_attr,
			      स्थिर काष्ठा ib_gid_attr *sgid_attr);

/**
 * ib_sa_pack_path - Conert a path record from काष्ठा ib_sa_path_rec
 * to IB MAD wire क्रमmat.
 */
व्योम ib_sa_pack_path(काष्ठा sa_path_rec *rec, व्योम *attribute);

/**
 * ib_sa_unpack_path - Convert a path record from MAD क्रमmat to काष्ठा
 * ib_sa_path_rec.
 */
व्योम ib_sa_unpack_path(व्योम *attribute, काष्ठा sa_path_rec *rec);

/* Support GuidInfoRecord */
पूर्णांक ib_sa_guid_info_rec_query(काष्ठा ib_sa_client *client,
			      काष्ठा ib_device *device, u32 port_num,
			      काष्ठा ib_sa_guidinfo_rec *rec,
			      ib_sa_comp_mask comp_mask, u8 method,
			      अचिन्हित दीर्घ समयout_ms, gfp_t gfp_mask,
			      व्योम (*callback)(पूर्णांक status,
					       काष्ठा ib_sa_guidinfo_rec *resp,
					       व्योम *context),
			      व्योम *context, काष्ठा ib_sa_query **sa_query);

अटल अंतरभूत bool sa_path_is_roce(काष्ठा sa_path_rec *rec)
अणु
	वापस ((rec->rec_type == SA_PATH_REC_TYPE_ROCE_V1) ||
		(rec->rec_type == SA_PATH_REC_TYPE_ROCE_V2));
पूर्ण

अटल अंतरभूत bool sa_path_is_opa(काष्ठा sa_path_rec *rec)
अणु
	वापस (rec->rec_type == SA_PATH_REC_TYPE_OPA);
पूर्ण

अटल अंतरभूत व्योम sa_path_set_slid(काष्ठा sa_path_rec *rec, u32 slid)
अणु
	अगर (rec->rec_type == SA_PATH_REC_TYPE_IB)
		rec->ib.slid = cpu_to_be16(slid);
	अन्यथा अगर (rec->rec_type == SA_PATH_REC_TYPE_OPA)
		rec->opa.slid = cpu_to_be32(slid);
पूर्ण

अटल अंतरभूत व्योम sa_path_set_dlid(काष्ठा sa_path_rec *rec, u32 dlid)
अणु
	अगर (rec->rec_type == SA_PATH_REC_TYPE_IB)
		rec->ib.dlid = cpu_to_be16(dlid);
	अन्यथा अगर (rec->rec_type == SA_PATH_REC_TYPE_OPA)
		rec->opa.dlid = cpu_to_be32(dlid);
पूर्ण

अटल अंतरभूत व्योम sa_path_set_raw_traffic(काष्ठा sa_path_rec *rec,
					   u8 raw_traffic)
अणु
	अगर (rec->rec_type == SA_PATH_REC_TYPE_IB)
		rec->ib.raw_traffic = raw_traffic;
	अन्यथा अगर (rec->rec_type == SA_PATH_REC_TYPE_OPA)
		rec->opa.raw_traffic = raw_traffic;
पूर्ण

अटल अंतरभूत __be32 sa_path_get_slid(काष्ठा sa_path_rec *rec)
अणु
	अगर (rec->rec_type == SA_PATH_REC_TYPE_IB)
		वापस htonl(ntohs(rec->ib.slid));
	अन्यथा अगर (rec->rec_type == SA_PATH_REC_TYPE_OPA)
		वापस rec->opa.slid;
	वापस 0;
पूर्ण

अटल अंतरभूत __be32 sa_path_get_dlid(काष्ठा sa_path_rec *rec)
अणु
	अगर (rec->rec_type == SA_PATH_REC_TYPE_IB)
		वापस htonl(ntohs(rec->ib.dlid));
	अन्यथा अगर (rec->rec_type == SA_PATH_REC_TYPE_OPA)
		वापस rec->opa.dlid;
	वापस 0;
पूर्ण

अटल अंतरभूत u8 sa_path_get_raw_traffic(काष्ठा sa_path_rec *rec)
अणु
	अगर (rec->rec_type == SA_PATH_REC_TYPE_IB)
		वापस rec->ib.raw_traffic;
	अन्यथा अगर (rec->rec_type == SA_PATH_REC_TYPE_OPA)
		वापस rec->opa.raw_traffic;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sa_path_set_dmac(काष्ठा sa_path_rec *rec, u8 *dmac)
अणु
	अगर (sa_path_is_roce(rec))
		स_नकल(rec->roce.dmac, dmac, ETH_ALEN);
पूर्ण

अटल अंतरभूत व्योम sa_path_set_dmac_zero(काष्ठा sa_path_rec *rec)
अणु
	अगर (sa_path_is_roce(rec))
		eth_zero_addr(rec->roce.dmac);
पूर्ण

अटल अंतरभूत u8 *sa_path_get_dmac(काष्ठा sa_path_rec *rec)
अणु
	अगर (sa_path_is_roce(rec))
		वापस rec->roce.dmac;
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* IB_SA_H */
