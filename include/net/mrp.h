<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_MRP_H
#घोषणा _NET_MRP_H

#घोषणा MRP_END_MARK		0x0

काष्ठा mrp_pdu_hdr अणु
	u8	version;
पूर्ण;

काष्ठा mrp_msg_hdr अणु
	u8	attrtype;
	u8	attrlen;
पूर्ण;

काष्ठा mrp_vecattr_hdr अणु
	__be16	lenflags;
	अचिन्हित अक्षर	firstattrvalue[];
#घोषणा MRP_VECATTR_HDR_LEN_MASK cpu_to_be16(0x1FFF)
#घोषणा MRP_VECATTR_HDR_FLAG_LA cpu_to_be16(0x2000)
पूर्ण;

क्रमागत mrp_vecattr_event अणु
	MRP_VECATTR_EVENT_NEW,
	MRP_VECATTR_EVENT_JOIN_IN,
	MRP_VECATTR_EVENT_IN,
	MRP_VECATTR_EVENT_JOIN_MT,
	MRP_VECATTR_EVENT_MT,
	MRP_VECATTR_EVENT_LV,
	__MRP_VECATTR_EVENT_MAX
पूर्ण;

काष्ठा mrp_skb_cb अणु
	काष्ठा mrp_msg_hdr	*mh;
	काष्ठा mrp_vecattr_hdr	*vah;
	अचिन्हित अक्षर		attrvalue[];
पूर्ण;

अटल अंतरभूत काष्ठा mrp_skb_cb *mrp_cb(काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा mrp_skb_cb) >
		     माप_field(काष्ठा sk_buff, cb));
	वापस (काष्ठा mrp_skb_cb *)skb->cb;
पूर्ण

क्रमागत mrp_applicant_state अणु
	MRP_APPLICANT_INVALID,
	MRP_APPLICANT_VO,
	MRP_APPLICANT_VP,
	MRP_APPLICANT_VN,
	MRP_APPLICANT_AN,
	MRP_APPLICANT_AA,
	MRP_APPLICANT_QA,
	MRP_APPLICANT_LA,
	MRP_APPLICANT_AO,
	MRP_APPLICANT_QO,
	MRP_APPLICANT_AP,
	MRP_APPLICANT_QP,
	__MRP_APPLICANT_MAX
पूर्ण;
#घोषणा MRP_APPLICANT_MAX	(__MRP_APPLICANT_MAX - 1)

क्रमागत mrp_event अणु
	MRP_EVENT_NEW,
	MRP_EVENT_JOIN,
	MRP_EVENT_LV,
	MRP_EVENT_TX,
	MRP_EVENT_R_NEW,
	MRP_EVENT_R_JOIN_IN,
	MRP_EVENT_R_IN,
	MRP_EVENT_R_JOIN_MT,
	MRP_EVENT_R_MT,
	MRP_EVENT_R_LV,
	MRP_EVENT_R_LA,
	MRP_EVENT_REDECLARE,
	MRP_EVENT_PERIODIC,
	__MRP_EVENT_MAX
पूर्ण;
#घोषणा MRP_EVENT_MAX		(__MRP_EVENT_MAX - 1)

क्रमागत mrp_tx_action अणु
	MRP_TX_ACTION_NONE,
	MRP_TX_ACTION_S_NEW,
	MRP_TX_ACTION_S_JOIN_IN,
	MRP_TX_ACTION_S_JOIN_IN_OPTIONAL,
	MRP_TX_ACTION_S_IN_OPTIONAL,
	MRP_TX_ACTION_S_LV,
पूर्ण;

काष्ठा mrp_attr अणु
	काष्ठा rb_node			node;
	क्रमागत mrp_applicant_state	state;
	u8				type;
	u8				len;
	अचिन्हित अक्षर			value[];
पूर्ण;

क्रमागत mrp_applications अणु
	MRP_APPLICATION_MVRP,
	__MRP_APPLICATION_MAX
पूर्ण;
#घोषणा MRP_APPLICATION_MAX	(__MRP_APPLICATION_MAX - 1)

काष्ठा mrp_application अणु
	क्रमागत mrp_applications	type;
	अचिन्हित पूर्णांक		maxattr;
	काष्ठा packet_type	pkttype;
	अचिन्हित अक्षर		group_address[ETH_ALEN];
	u8			version;
पूर्ण;

काष्ठा mrp_applicant अणु
	काष्ठा mrp_application	*app;
	काष्ठा net_device	*dev;
	काष्ठा समयr_list	join_समयr;
	काष्ठा समयr_list	periodic_समयr;

	spinlock_t		lock;
	काष्ठा sk_buff_head	queue;
	काष्ठा sk_buff		*pdu;
	काष्ठा rb_root		mad;
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा mrp_port अणु
	काष्ठा mrp_applicant __rcu	*applicants[MRP_APPLICATION_MAX + 1];
	काष्ठा rcu_head			rcu;
पूर्ण;

पूर्णांक mrp_रेजिस्टर_application(काष्ठा mrp_application *app);
व्योम mrp_unरेजिस्टर_application(काष्ठा mrp_application *app);

पूर्णांक mrp_init_applicant(काष्ठा net_device *dev, काष्ठा mrp_application *app);
व्योम mrp_uninit_applicant(काष्ठा net_device *dev, काष्ठा mrp_application *app);

पूर्णांक mrp_request_join(स्थिर काष्ठा net_device *dev,
		     स्थिर काष्ठा mrp_application *app,
		     स्थिर व्योम *value, u8 len, u8 type);
व्योम mrp_request_leave(स्थिर काष्ठा net_device *dev,
		       स्थिर काष्ठा mrp_application *app,
		       स्थिर व्योम *value, u8 len, u8 type);

#पूर्ण_अगर /* _NET_MRP_H */
