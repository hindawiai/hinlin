<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_GARP_H
#घोषणा _NET_GARP_H

#समावेश <net/stp.h>

#घोषणा GARP_PROTOCOL_ID	0x1
#घोषणा GARP_END_MARK		0x0

काष्ठा garp_pdu_hdr अणु
	__be16	protocol;
पूर्ण;

काष्ठा garp_msg_hdr अणु
	u8	attrtype;
पूर्ण;

क्रमागत garp_attr_event अणु
	GARP_LEAVE_ALL,
	GARP_JOIN_EMPTY,
	GARP_JOIN_IN,
	GARP_LEAVE_EMPTY,
	GARP_LEAVE_IN,
	GARP_EMPTY,
पूर्ण;

काष्ठा garp_attr_hdr अणु
	u8	len;
	u8	event;
	u8	data[];
पूर्ण;

काष्ठा garp_skb_cb अणु
	u8	cur_type;
पूर्ण;

अटल अंतरभूत काष्ठा garp_skb_cb *garp_cb(काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा garp_skb_cb) >
		     माप_field(काष्ठा sk_buff, cb));
	वापस (काष्ठा garp_skb_cb *)skb->cb;
पूर्ण

क्रमागत garp_applicant_state अणु
	GARP_APPLICANT_INVALID,
	GARP_APPLICANT_VA,
	GARP_APPLICANT_AA,
	GARP_APPLICANT_QA,
	GARP_APPLICANT_LA,
	GARP_APPLICANT_VP,
	GARP_APPLICANT_AP,
	GARP_APPLICANT_QP,
	GARP_APPLICANT_VO,
	GARP_APPLICANT_AO,
	GARP_APPLICANT_QO,
	__GARP_APPLICANT_MAX
पूर्ण;
#घोषणा GARP_APPLICANT_MAX	(__GARP_APPLICANT_MAX - 1)

क्रमागत garp_event अणु
	GARP_EVENT_REQ_JOIN,
	GARP_EVENT_REQ_LEAVE,
	GARP_EVENT_R_JOIN_IN,
	GARP_EVENT_R_JOIN_EMPTY,
	GARP_EVENT_R_EMPTY,
	GARP_EVENT_R_LEAVE_IN,
	GARP_EVENT_R_LEAVE_EMPTY,
	GARP_EVENT_TRANSMIT_PDU,
	__GARP_EVENT_MAX
पूर्ण;
#घोषणा GARP_EVENT_MAX		(__GARP_EVENT_MAX - 1)

क्रमागत garp_action अणु
	GARP_ACTION_NONE,
	GARP_ACTION_S_JOIN_IN,
	GARP_ACTION_S_LEAVE_EMPTY,
पूर्ण;

काष्ठा garp_attr अणु
	काष्ठा rb_node			node;
	क्रमागत garp_applicant_state	state;
	u8				type;
	u8				dlen;
	अचिन्हित अक्षर			data[];
पूर्ण;

क्रमागत garp_applications अणु
	GARP_APPLICATION_GVRP,
	__GARP_APPLICATION_MAX
पूर्ण;
#घोषणा GARP_APPLICATION_MAX	(__GARP_APPLICATION_MAX - 1)

काष्ठा garp_application अणु
	क्रमागत garp_applications	type;
	अचिन्हित पूर्णांक		maxattr;
	काष्ठा stp_proto	proto;
पूर्ण;

काष्ठा garp_applicant अणु
	काष्ठा garp_application	*app;
	काष्ठा net_device	*dev;
	काष्ठा समयr_list	join_समयr;

	spinlock_t		lock;
	काष्ठा sk_buff_head	queue;
	काष्ठा sk_buff		*pdu;
	काष्ठा rb_root		gid;
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा garp_port अणु
	काष्ठा garp_applicant __rcu	*applicants[GARP_APPLICATION_MAX + 1];
	काष्ठा rcu_head			rcu;
पूर्ण;

पूर्णांक garp_रेजिस्टर_application(काष्ठा garp_application *app);
व्योम garp_unरेजिस्टर_application(काष्ठा garp_application *app);

पूर्णांक garp_init_applicant(काष्ठा net_device *dev, काष्ठा garp_application *app);
व्योम garp_uninit_applicant(काष्ठा net_device *dev,
			   काष्ठा garp_application *app);

पूर्णांक garp_request_join(स्थिर काष्ठा net_device *dev,
		      स्थिर काष्ठा garp_application *app, स्थिर व्योम *data,
		      u8 len, u8 type);
व्योम garp_request_leave(स्थिर काष्ठा net_device *dev,
			स्थिर काष्ठा garp_application *app,
			स्थिर व्योम *data, u8 len, u8 type);

#पूर्ण_अगर /* _NET_GARP_H */
