<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	IEEE 802.1D Generic Attribute Registration Protocol (GARP)
 *
 *	Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/llc.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <net/llc.h>
#समावेश <net/llc_pdu.h>
#समावेश <net/garp.h>
#समावेश <यंत्र/unaligned.h>

अटल अचिन्हित पूर्णांक garp_join_समय __पढ़ो_mostly = 200;
module_param(garp_join_समय, uपूर्णांक, 0644);
MODULE_PARM_DESC(garp_join_समय, "Join time in ms (default 200ms)");
MODULE_LICENSE("GPL");

अटल स्थिर काष्ठा garp_state_trans अणु
	u8	state;
	u8	action;
पूर्ण garp_applicant_state_table[GARP_APPLICANT_MAX + 1][GARP_EVENT_MAX + 1] = अणु
	[GARP_APPLICANT_VA] = अणु
		[GARP_EVENT_TRANSMIT_PDU]	= अणु .state = GARP_APPLICANT_AA,
						    .action = GARP_ACTION_S_JOIN_IN पूर्ण,
		[GARP_EVENT_R_JOIN_IN]		= अणु .state = GARP_APPLICANT_AA पूर्ण,
		[GARP_EVENT_R_JOIN_EMPTY]	= अणु .state = GARP_APPLICANT_VA पूर्ण,
		[GARP_EVENT_R_EMPTY]		= अणु .state = GARP_APPLICANT_VA पूर्ण,
		[GARP_EVENT_R_LEAVE_IN]		= अणु .state = GARP_APPLICANT_VA पूर्ण,
		[GARP_EVENT_R_LEAVE_EMPTY]	= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_REQ_JOIN]		= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
		[GARP_EVENT_REQ_LEAVE]		= अणु .state = GARP_APPLICANT_LA पूर्ण,
	पूर्ण,
	[GARP_APPLICANT_AA] = अणु
		[GARP_EVENT_TRANSMIT_PDU]	= अणु .state = GARP_APPLICANT_QA,
						    .action = GARP_ACTION_S_JOIN_IN पूर्ण,
		[GARP_EVENT_R_JOIN_IN]		= अणु .state = GARP_APPLICANT_QA पूर्ण,
		[GARP_EVENT_R_JOIN_EMPTY]	= अणु .state = GARP_APPLICANT_VA पूर्ण,
		[GARP_EVENT_R_EMPTY]		= अणु .state = GARP_APPLICANT_VA पूर्ण,
		[GARP_EVENT_R_LEAVE_IN]		= अणु .state = GARP_APPLICANT_VA पूर्ण,
		[GARP_EVENT_R_LEAVE_EMPTY]	= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_REQ_JOIN]		= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
		[GARP_EVENT_REQ_LEAVE]		= अणु .state = GARP_APPLICANT_LA पूर्ण,
	पूर्ण,
	[GARP_APPLICANT_QA] = अणु
		[GARP_EVENT_TRANSMIT_PDU]	= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
		[GARP_EVENT_R_JOIN_IN]		= अणु .state = GARP_APPLICANT_QA पूर्ण,
		[GARP_EVENT_R_JOIN_EMPTY]	= अणु .state = GARP_APPLICANT_VA पूर्ण,
		[GARP_EVENT_R_EMPTY]		= अणु .state = GARP_APPLICANT_VA पूर्ण,
		[GARP_EVENT_R_LEAVE_IN]		= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_R_LEAVE_EMPTY]	= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_REQ_JOIN]		= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
		[GARP_EVENT_REQ_LEAVE]		= अणु .state = GARP_APPLICANT_LA पूर्ण,
	पूर्ण,
	[GARP_APPLICANT_LA] = अणु
		[GARP_EVENT_TRANSMIT_PDU]	= अणु .state = GARP_APPLICANT_VO,
						    .action = GARP_ACTION_S_LEAVE_EMPTY पूर्ण,
		[GARP_EVENT_R_JOIN_IN]		= अणु .state = GARP_APPLICANT_LA पूर्ण,
		[GARP_EVENT_R_JOIN_EMPTY]	= अणु .state = GARP_APPLICANT_VO पूर्ण,
		[GARP_EVENT_R_EMPTY]		= अणु .state = GARP_APPLICANT_LA पूर्ण,
		[GARP_EVENT_R_LEAVE_IN]		= अणु .state = GARP_APPLICANT_LA पूर्ण,
		[GARP_EVENT_R_LEAVE_EMPTY]	= अणु .state = GARP_APPLICANT_VO पूर्ण,
		[GARP_EVENT_REQ_JOIN]		= अणु .state = GARP_APPLICANT_VA पूर्ण,
		[GARP_EVENT_REQ_LEAVE]		= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
	पूर्ण,
	[GARP_APPLICANT_VP] = अणु
		[GARP_EVENT_TRANSMIT_PDU]	= अणु .state = GARP_APPLICANT_AA,
						    .action = GARP_ACTION_S_JOIN_IN पूर्ण,
		[GARP_EVENT_R_JOIN_IN]		= अणु .state = GARP_APPLICANT_AP पूर्ण,
		[GARP_EVENT_R_JOIN_EMPTY]	= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_R_EMPTY]		= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_R_LEAVE_IN]		= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_R_LEAVE_EMPTY]	= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_REQ_JOIN]		= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
		[GARP_EVENT_REQ_LEAVE]		= अणु .state = GARP_APPLICANT_VO पूर्ण,
	पूर्ण,
	[GARP_APPLICANT_AP] = अणु
		[GARP_EVENT_TRANSMIT_PDU]	= अणु .state = GARP_APPLICANT_QA,
						    .action = GARP_ACTION_S_JOIN_IN पूर्ण,
		[GARP_EVENT_R_JOIN_IN]		= अणु .state = GARP_APPLICANT_QP पूर्ण,
		[GARP_EVENT_R_JOIN_EMPTY]	= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_R_EMPTY]		= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_R_LEAVE_IN]		= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_R_LEAVE_EMPTY]	= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_REQ_JOIN]		= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
		[GARP_EVENT_REQ_LEAVE]		= अणु .state = GARP_APPLICANT_AO पूर्ण,
	पूर्ण,
	[GARP_APPLICANT_QP] = अणु
		[GARP_EVENT_TRANSMIT_PDU]	= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
		[GARP_EVENT_R_JOIN_IN]		= अणु .state = GARP_APPLICANT_QP पूर्ण,
		[GARP_EVENT_R_JOIN_EMPTY]	= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_R_EMPTY]		= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_R_LEAVE_IN]		= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_R_LEAVE_EMPTY]	= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_REQ_JOIN]		= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
		[GARP_EVENT_REQ_LEAVE]		= अणु .state = GARP_APPLICANT_QO पूर्ण,
	पूर्ण,
	[GARP_APPLICANT_VO] = अणु
		[GARP_EVENT_TRANSMIT_PDU]	= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
		[GARP_EVENT_R_JOIN_IN]		= अणु .state = GARP_APPLICANT_AO पूर्ण,
		[GARP_EVENT_R_JOIN_EMPTY]	= अणु .state = GARP_APPLICANT_VO पूर्ण,
		[GARP_EVENT_R_EMPTY]		= अणु .state = GARP_APPLICANT_VO पूर्ण,
		[GARP_EVENT_R_LEAVE_IN]		= अणु .state = GARP_APPLICANT_VO पूर्ण,
		[GARP_EVENT_R_LEAVE_EMPTY]	= अणु .state = GARP_APPLICANT_VO पूर्ण,
		[GARP_EVENT_REQ_JOIN]		= अणु .state = GARP_APPLICANT_VP पूर्ण,
		[GARP_EVENT_REQ_LEAVE]		= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
	पूर्ण,
	[GARP_APPLICANT_AO] = अणु
		[GARP_EVENT_TRANSMIT_PDU]	= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
		[GARP_EVENT_R_JOIN_IN]		= अणु .state = GARP_APPLICANT_QO पूर्ण,
		[GARP_EVENT_R_JOIN_EMPTY]	= अणु .state = GARP_APPLICANT_VO पूर्ण,
		[GARP_EVENT_R_EMPTY]		= अणु .state = GARP_APPLICANT_VO पूर्ण,
		[GARP_EVENT_R_LEAVE_IN]		= अणु .state = GARP_APPLICANT_VO पूर्ण,
		[GARP_EVENT_R_LEAVE_EMPTY]	= अणु .state = GARP_APPLICANT_VO पूर्ण,
		[GARP_EVENT_REQ_JOIN]		= अणु .state = GARP_APPLICANT_AP पूर्ण,
		[GARP_EVENT_REQ_LEAVE]		= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
	पूर्ण,
	[GARP_APPLICANT_QO] = अणु
		[GARP_EVENT_TRANSMIT_PDU]	= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
		[GARP_EVENT_R_JOIN_IN]		= अणु .state = GARP_APPLICANT_QO पूर्ण,
		[GARP_EVENT_R_JOIN_EMPTY]	= अणु .state = GARP_APPLICANT_VO पूर्ण,
		[GARP_EVENT_R_EMPTY]		= अणु .state = GARP_APPLICANT_VO पूर्ण,
		[GARP_EVENT_R_LEAVE_IN]		= अणु .state = GARP_APPLICANT_VO पूर्ण,
		[GARP_EVENT_R_LEAVE_EMPTY]	= अणु .state = GARP_APPLICANT_VO पूर्ण,
		[GARP_EVENT_REQ_JOIN]		= अणु .state = GARP_APPLICANT_QP पूर्ण,
		[GARP_EVENT_REQ_LEAVE]		= अणु .state = GARP_APPLICANT_INVALID पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक garp_attr_cmp(स्थिर काष्ठा garp_attr *attr,
			 स्थिर व्योम *data, u8 len, u8 type)
अणु
	अगर (attr->type != type)
		वापस attr->type - type;
	अगर (attr->dlen != len)
		वापस attr->dlen - len;
	वापस स_भेद(attr->data, data, len);
पूर्ण

अटल काष्ठा garp_attr *garp_attr_lookup(स्थिर काष्ठा garp_applicant *app,
					  स्थिर व्योम *data, u8 len, u8 type)
अणु
	काष्ठा rb_node *parent = app->gid.rb_node;
	काष्ठा garp_attr *attr;
	पूर्णांक d;

	जबतक (parent) अणु
		attr = rb_entry(parent, काष्ठा garp_attr, node);
		d = garp_attr_cmp(attr, data, len, type);
		अगर (d > 0)
			parent = parent->rb_left;
		अन्यथा अगर (d < 0)
			parent = parent->rb_right;
		अन्यथा
			वापस attr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा garp_attr *garp_attr_create(काष्ठा garp_applicant *app,
					  स्थिर व्योम *data, u8 len, u8 type)
अणु
	काष्ठा rb_node *parent = शून्य, **p = &app->gid.rb_node;
	काष्ठा garp_attr *attr;
	पूर्णांक d;

	जबतक (*p) अणु
		parent = *p;
		attr = rb_entry(parent, काष्ठा garp_attr, node);
		d = garp_attr_cmp(attr, data, len, type);
		अगर (d > 0)
			p = &parent->rb_left;
		अन्यथा अगर (d < 0)
			p = &parent->rb_right;
		अन्यथा अणु
			/* The attribute alपढ़ोy exists; re-use it. */
			वापस attr;
		पूर्ण
	पूर्ण
	attr = kदो_स्मृति(माप(*attr) + len, GFP_ATOMIC);
	अगर (!attr)
		वापस attr;
	attr->state = GARP_APPLICANT_VO;
	attr->type  = type;
	attr->dlen  = len;
	स_नकल(attr->data, data, len);

	rb_link_node(&attr->node, parent, p);
	rb_insert_color(&attr->node, &app->gid);
	वापस attr;
पूर्ण

अटल व्योम garp_attr_destroy(काष्ठा garp_applicant *app, काष्ठा garp_attr *attr)
अणु
	rb_erase(&attr->node, &app->gid);
	kमुक्त(attr);
पूर्ण

अटल पूर्णांक garp_pdu_init(काष्ठा garp_applicant *app)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा garp_pdu_hdr *gp;

#घोषणा LLC_RESERVE	माप(काष्ठा llc_pdu_un)
	skb = alloc_skb(app->dev->mtu + LL_RESERVED_SPACE(app->dev),
			GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	skb->dev = app->dev;
	skb->protocol = htons(ETH_P_802_2);
	skb_reserve(skb, LL_RESERVED_SPACE(app->dev) + LLC_RESERVE);

	gp = __skb_put(skb, माप(*gp));
	put_unaligned(htons(GARP_PROTOCOL_ID), &gp->protocol);

	app->pdu = skb;
	वापस 0;
पूर्ण

अटल पूर्णांक garp_pdu_append_end_mark(काष्ठा garp_applicant *app)
अणु
	अगर (skb_tailroom(app->pdu) < माप(u8))
		वापस -1;
	__skb_put_u8(app->pdu, GARP_END_MARK);
	वापस 0;
पूर्ण

अटल व्योम garp_pdu_queue(काष्ठा garp_applicant *app)
अणु
	अगर (!app->pdu)
		वापस;

	garp_pdu_append_end_mark(app);
	garp_pdu_append_end_mark(app);

	llc_pdu_header_init(app->pdu, LLC_PDU_TYPE_U, LLC_SAP_BSPAN,
			    LLC_SAP_BSPAN, LLC_PDU_CMD);
	llc_pdu_init_as_ui_cmd(app->pdu);
	llc_mac_hdr_init(app->pdu, app->dev->dev_addr,
			 app->app->proto.group_address);

	skb_queue_tail(&app->queue, app->pdu);
	app->pdu = शून्य;
पूर्ण

अटल व्योम garp_queue_xmit(काष्ठा garp_applicant *app)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&app->queue)))
		dev_queue_xmit(skb);
पूर्ण

अटल पूर्णांक garp_pdu_append_msg(काष्ठा garp_applicant *app, u8 attrtype)
अणु
	काष्ठा garp_msg_hdr *gm;

	अगर (skb_tailroom(app->pdu) < माप(*gm))
		वापस -1;
	gm = __skb_put(app->pdu, माप(*gm));
	gm->attrtype = attrtype;
	garp_cb(app->pdu)->cur_type = attrtype;
	वापस 0;
पूर्ण

अटल पूर्णांक garp_pdu_append_attr(काष्ठा garp_applicant *app,
				स्थिर काष्ठा garp_attr *attr,
				क्रमागत garp_attr_event event)
अणु
	काष्ठा garp_attr_hdr *ga;
	अचिन्हित पूर्णांक len;
	पूर्णांक err;
again:
	अगर (!app->pdu) अणु
		err = garp_pdu_init(app);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (garp_cb(app->pdu)->cur_type != attr->type) अणु
		अगर (garp_cb(app->pdu)->cur_type &&
		    garp_pdu_append_end_mark(app) < 0)
			जाओ queue;
		अगर (garp_pdu_append_msg(app, attr->type) < 0)
			जाओ queue;
	पूर्ण

	len = माप(*ga) + attr->dlen;
	अगर (skb_tailroom(app->pdu) < len)
		जाओ queue;
	ga = __skb_put(app->pdu, len);
	ga->len   = len;
	ga->event = event;
	स_नकल(ga->data, attr->data, attr->dlen);
	वापस 0;

queue:
	garp_pdu_queue(app);
	जाओ again;
पूर्ण

अटल व्योम garp_attr_event(काष्ठा garp_applicant *app,
			    काष्ठा garp_attr *attr, क्रमागत garp_event event)
अणु
	क्रमागत garp_applicant_state state;

	state = garp_applicant_state_table[attr->state][event].state;
	अगर (state == GARP_APPLICANT_INVALID)
		वापस;

	चयन (garp_applicant_state_table[attr->state][event].action) अणु
	हाल GARP_ACTION_NONE:
		अवरोध;
	हाल GARP_ACTION_S_JOIN_IN:
		/* When appending the attribute fails, करोn't update state in
		 * order to retry on next TRANSMIT_PDU event. */
		अगर (garp_pdu_append_attr(app, attr, GARP_JOIN_IN) < 0)
			वापस;
		अवरोध;
	हाल GARP_ACTION_S_LEAVE_EMPTY:
		garp_pdu_append_attr(app, attr, GARP_LEAVE_EMPTY);
		/* As a pure applicant, sending a leave message implies that
		 * the attribute was unरेजिस्टरed and can be destroyed. */
		garp_attr_destroy(app, attr);
		वापस;
	शेष:
		WARN_ON(1);
	पूर्ण

	attr->state = state;
पूर्ण

पूर्णांक garp_request_join(स्थिर काष्ठा net_device *dev,
		      स्थिर काष्ठा garp_application *appl,
		      स्थिर व्योम *data, u8 len, u8 type)
अणु
	काष्ठा garp_port *port = rtnl_dereference(dev->garp_port);
	काष्ठा garp_applicant *app = rtnl_dereference(port->applicants[appl->type]);
	काष्ठा garp_attr *attr;

	spin_lock_bh(&app->lock);
	attr = garp_attr_create(app, data, len, type);
	अगर (!attr) अणु
		spin_unlock_bh(&app->lock);
		वापस -ENOMEM;
	पूर्ण
	garp_attr_event(app, attr, GARP_EVENT_REQ_JOIN);
	spin_unlock_bh(&app->lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(garp_request_join);

व्योम garp_request_leave(स्थिर काष्ठा net_device *dev,
			स्थिर काष्ठा garp_application *appl,
			स्थिर व्योम *data, u8 len, u8 type)
अणु
	काष्ठा garp_port *port = rtnl_dereference(dev->garp_port);
	काष्ठा garp_applicant *app = rtnl_dereference(port->applicants[appl->type]);
	काष्ठा garp_attr *attr;

	spin_lock_bh(&app->lock);
	attr = garp_attr_lookup(app, data, len, type);
	अगर (!attr) अणु
		spin_unlock_bh(&app->lock);
		वापस;
	पूर्ण
	garp_attr_event(app, attr, GARP_EVENT_REQ_LEAVE);
	spin_unlock_bh(&app->lock);
पूर्ण
EXPORT_SYMBOL_GPL(garp_request_leave);

अटल व्योम garp_gid_event(काष्ठा garp_applicant *app, क्रमागत garp_event event)
अणु
	काष्ठा rb_node *node, *next;
	काष्ठा garp_attr *attr;

	क्रम (node = rb_first(&app->gid);
	     next = node ? rb_next(node) : शून्य, node != शून्य;
	     node = next) अणु
		attr = rb_entry(node, काष्ठा garp_attr, node);
		garp_attr_event(app, attr, event);
	पूर्ण
पूर्ण

अटल व्योम garp_join_समयr_arm(काष्ठा garp_applicant *app)
अणु
	अचिन्हित दीर्घ delay;

	delay = (u64)msecs_to_jअगरfies(garp_join_समय) * pअक्रमom_u32() >> 32;
	mod_समयr(&app->join_समयr, jअगरfies + delay);
पूर्ण

अटल व्योम garp_join_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा garp_applicant *app = from_समयr(app, t, join_समयr);

	spin_lock(&app->lock);
	garp_gid_event(app, GARP_EVENT_TRANSMIT_PDU);
	garp_pdu_queue(app);
	spin_unlock(&app->lock);

	garp_queue_xmit(app);
	garp_join_समयr_arm(app);
पूर्ण

अटल पूर्णांक garp_pdu_parse_end_mark(काष्ठा sk_buff *skb)
अणु
	अगर (!pskb_may_pull(skb, माप(u8)))
		वापस -1;
	अगर (*skb->data == GARP_END_MARK) अणु
		skb_pull(skb, माप(u8));
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक garp_pdu_parse_attr(काष्ठा garp_applicant *app, काष्ठा sk_buff *skb,
			       u8 attrtype)
अणु
	स्थिर काष्ठा garp_attr_hdr *ga;
	काष्ठा garp_attr *attr;
	क्रमागत garp_event event;
	अचिन्हित पूर्णांक dlen;

	अगर (!pskb_may_pull(skb, माप(*ga)))
		वापस -1;
	ga = (काष्ठा garp_attr_hdr *)skb->data;
	अगर (ga->len < माप(*ga))
		वापस -1;

	अगर (!pskb_may_pull(skb, ga->len))
		वापस -1;
	skb_pull(skb, ga->len);
	dlen = माप(*ga) - ga->len;

	अगर (attrtype > app->app->maxattr)
		वापस 0;

	चयन (ga->event) अणु
	हाल GARP_LEAVE_ALL:
		अगर (dlen != 0)
			वापस -1;
		garp_gid_event(app, GARP_EVENT_R_LEAVE_EMPTY);
		वापस 0;
	हाल GARP_JOIN_EMPTY:
		event = GARP_EVENT_R_JOIN_EMPTY;
		अवरोध;
	हाल GARP_JOIN_IN:
		event = GARP_EVENT_R_JOIN_IN;
		अवरोध;
	हाल GARP_LEAVE_EMPTY:
		event = GARP_EVENT_R_LEAVE_EMPTY;
		अवरोध;
	हाल GARP_EMPTY:
		event = GARP_EVENT_R_EMPTY;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (dlen == 0)
		वापस -1;
	attr = garp_attr_lookup(app, ga->data, dlen, attrtype);
	अगर (attr == शून्य)
		वापस 0;
	garp_attr_event(app, attr, event);
	वापस 0;
पूर्ण

अटल पूर्णांक garp_pdu_parse_msg(काष्ठा garp_applicant *app, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा garp_msg_hdr *gm;

	अगर (!pskb_may_pull(skb, माप(*gm)))
		वापस -1;
	gm = (काष्ठा garp_msg_hdr *)skb->data;
	अगर (gm->attrtype == 0)
		वापस -1;
	skb_pull(skb, माप(*gm));

	जबतक (skb->len > 0) अणु
		अगर (garp_pdu_parse_attr(app, skb, gm->attrtype) < 0)
			वापस -1;
		अगर (garp_pdu_parse_end_mark(skb) < 0)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम garp_pdu_rcv(स्थिर काष्ठा stp_proto *proto, काष्ठा sk_buff *skb,
			 काष्ठा net_device *dev)
अणु
	काष्ठा garp_application *appl = proto->data;
	काष्ठा garp_port *port;
	काष्ठा garp_applicant *app;
	स्थिर काष्ठा garp_pdu_hdr *gp;

	port = rcu_dereference(dev->garp_port);
	अगर (!port)
		जाओ err;
	app = rcu_dereference(port->applicants[appl->type]);
	अगर (!app)
		जाओ err;

	अगर (!pskb_may_pull(skb, माप(*gp)))
		जाओ err;
	gp = (काष्ठा garp_pdu_hdr *)skb->data;
	अगर (get_unaligned(&gp->protocol) != htons(GARP_PROTOCOL_ID))
		जाओ err;
	skb_pull(skb, माप(*gp));

	spin_lock(&app->lock);
	जबतक (skb->len > 0) अणु
		अगर (garp_pdu_parse_msg(app, skb) < 0)
			अवरोध;
		अगर (garp_pdu_parse_end_mark(skb) < 0)
			अवरोध;
	पूर्ण
	spin_unlock(&app->lock);
err:
	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक garp_init_port(काष्ठा net_device *dev)
अणु
	काष्ठा garp_port *port;

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;
	rcu_assign_poपूर्णांकer(dev->garp_port, port);
	वापस 0;
पूर्ण

अटल व्योम garp_release_port(काष्ठा net_device *dev)
अणु
	काष्ठा garp_port *port = rtnl_dereference(dev->garp_port);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i <= GARP_APPLICATION_MAX; i++) अणु
		अगर (rtnl_dereference(port->applicants[i]))
			वापस;
	पूर्ण
	RCU_INIT_POINTER(dev->garp_port, शून्य);
	kमुक्त_rcu(port, rcu);
पूर्ण

पूर्णांक garp_init_applicant(काष्ठा net_device *dev, काष्ठा garp_application *appl)
अणु
	काष्ठा garp_applicant *app;
	पूर्णांक err;

	ASSERT_RTNL();

	अगर (!rtnl_dereference(dev->garp_port)) अणु
		err = garp_init_port(dev);
		अगर (err < 0)
			जाओ err1;
	पूर्ण

	err = -ENOMEM;
	app = kzalloc(माप(*app), GFP_KERNEL);
	अगर (!app)
		जाओ err2;

	err = dev_mc_add(dev, appl->proto.group_address);
	अगर (err < 0)
		जाओ err3;

	app->dev = dev;
	app->app = appl;
	app->gid = RB_ROOT;
	spin_lock_init(&app->lock);
	skb_queue_head_init(&app->queue);
	rcu_assign_poपूर्णांकer(dev->garp_port->applicants[appl->type], app);
	समयr_setup(&app->join_समयr, garp_join_समयr, 0);
	garp_join_समयr_arm(app);
	वापस 0;

err3:
	kमुक्त(app);
err2:
	garp_release_port(dev);
err1:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(garp_init_applicant);

व्योम garp_uninit_applicant(काष्ठा net_device *dev, काष्ठा garp_application *appl)
अणु
	काष्ठा garp_port *port = rtnl_dereference(dev->garp_port);
	काष्ठा garp_applicant *app = rtnl_dereference(port->applicants[appl->type]);

	ASSERT_RTNL();

	RCU_INIT_POINTER(port->applicants[appl->type], शून्य);

	/* Delete समयr and generate a final TRANSMIT_PDU event to flush out
	 * all pending messages beक्रमe the applicant is gone. */
	del_समयr_sync(&app->join_समयr);

	spin_lock_bh(&app->lock);
	garp_gid_event(app, GARP_EVENT_TRANSMIT_PDU);
	garp_pdu_queue(app);
	spin_unlock_bh(&app->lock);

	garp_queue_xmit(app);

	dev_mc_del(dev, appl->proto.group_address);
	kमुक्त_rcu(app, rcu);
	garp_release_port(dev);
पूर्ण
EXPORT_SYMBOL_GPL(garp_uninit_applicant);

पूर्णांक garp_रेजिस्टर_application(काष्ठा garp_application *appl)
अणु
	appl->proto.rcv = garp_pdu_rcv;
	appl->proto.data = appl;
	वापस stp_proto_रेजिस्टर(&appl->proto);
पूर्ण
EXPORT_SYMBOL_GPL(garp_रेजिस्टर_application);

व्योम garp_unरेजिस्टर_application(काष्ठा garp_application *appl)
अणु
	stp_proto_unरेजिस्टर(&appl->proto);
पूर्ण
EXPORT_SYMBOL_GPL(garp_unरेजिस्टर_application);
