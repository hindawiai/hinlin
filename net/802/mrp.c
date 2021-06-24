<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	IEEE 802.1Q Multiple Registration Protocol (MRP)
 *
 *	Copyright (c) 2012 Massachusetts Institute of Technology
 *
 *	Adapted from code in net/802/garp.c
 *	Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <net/mrp.h>
#समावेश <यंत्र/unaligned.h>

अटल अचिन्हित पूर्णांक mrp_join_समय __पढ़ो_mostly = 200;
module_param(mrp_join_समय, uपूर्णांक, 0644);
MODULE_PARM_DESC(mrp_join_समय, "Join time in ms (default 200ms)");

अटल अचिन्हित पूर्णांक mrp_periodic_समय __पढ़ो_mostly = 1000;
module_param(mrp_periodic_समय, uपूर्णांक, 0644);
MODULE_PARM_DESC(mrp_periodic_समय, "Periodic time in ms (default 1s)");

MODULE_LICENSE("GPL");

अटल स्थिर u8
mrp_applicant_state_table[MRP_APPLICANT_MAX + 1][MRP_EVENT_MAX + 1] = अणु
	[MRP_APPLICANT_VO] = अणु
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_VP,
		[MRP_EVENT_LV]		= MRP_APPLICANT_VO,
		[MRP_EVENT_TX]		= MRP_APPLICANT_VO,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_VO,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_AO,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_VO,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_VO,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_VO,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VO,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VO,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VO,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_VO,
	पूर्ण,
	[MRP_APPLICANT_VP] = अणु
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_VP,
		[MRP_EVENT_LV]		= MRP_APPLICANT_VO,
		[MRP_EVENT_TX]		= MRP_APPLICANT_AA,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_AP,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VP,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VP,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_VP,
	पूर्ण,
	[MRP_APPLICANT_VN] = अणु
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_VN,
		[MRP_EVENT_LV]		= MRP_APPLICANT_LA,
		[MRP_EVENT_TX]		= MRP_APPLICANT_AN,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VN,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VN,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_VN,
	पूर्ण,
	[MRP_APPLICANT_AN] = अणु
		[MRP_EVENT_NEW]		= MRP_APPLICANT_AN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_AN,
		[MRP_EVENT_LV]		= MRP_APPLICANT_LA,
		[MRP_EVENT_TX]		= MRP_APPLICANT_QA,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_AN,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_AN,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_AN,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_AN,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_AN,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VN,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VN,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_AN,
	पूर्ण,
	[MRP_APPLICANT_AA] = अणु
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_AA,
		[MRP_EVENT_LV]		= MRP_APPLICANT_LA,
		[MRP_EVENT_TX]		= MRP_APPLICANT_QA,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_AA,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_QA,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_AA,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_AA,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_AA,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VP,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VP,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_AA,
	पूर्ण,
	[MRP_APPLICANT_QA] = अणु
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_QA,
		[MRP_EVENT_LV]		= MRP_APPLICANT_LA,
		[MRP_EVENT_TX]		= MRP_APPLICANT_QA,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_QA,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_QA,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_QA,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_AA,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_AA,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VP,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VP,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_AA,
	पूर्ण,
	[MRP_APPLICANT_LA] = अणु
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_AA,
		[MRP_EVENT_LV]		= MRP_APPLICANT_LA,
		[MRP_EVENT_TX]		= MRP_APPLICANT_VO,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_LA,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_LA,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_LA,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_LA,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_LA,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_LA,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_LA,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_LA,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_LA,
	पूर्ण,
	[MRP_APPLICANT_AO] = अणु
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_AP,
		[MRP_EVENT_LV]		= MRP_APPLICANT_AO,
		[MRP_EVENT_TX]		= MRP_APPLICANT_AO,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_AO,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_QO,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_AO,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_AO,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_AO,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VO,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VO,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VO,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_AO,
	पूर्ण,
	[MRP_APPLICANT_QO] = अणु
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_QP,
		[MRP_EVENT_LV]		= MRP_APPLICANT_QO,
		[MRP_EVENT_TX]		= MRP_APPLICANT_QO,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_QO,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_QO,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_QO,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_AO,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_AO,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VO,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VO,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VO,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_QO,
	पूर्ण,
	[MRP_APPLICANT_AP] = अणु
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_AP,
		[MRP_EVENT_LV]		= MRP_APPLICANT_AO,
		[MRP_EVENT_TX]		= MRP_APPLICANT_QA,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_AP,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_QP,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_AP,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_AP,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_AP,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VP,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VP,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_AP,
	पूर्ण,
	[MRP_APPLICANT_QP] = अणु
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_QP,
		[MRP_EVENT_LV]		= MRP_APPLICANT_QO,
		[MRP_EVENT_TX]		= MRP_APPLICANT_QP,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_QP,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_QP,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_QP,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_AP,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_AP,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VP,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VP,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_AP,
	पूर्ण,
पूर्ण;

अटल स्थिर u8
mrp_tx_action_table[MRP_APPLICANT_MAX + 1] = अणु
	[MRP_APPLICANT_VO] = MRP_TX_ACTION_S_IN_OPTIONAL,
	[MRP_APPLICANT_VP] = MRP_TX_ACTION_S_JOIN_IN,
	[MRP_APPLICANT_VN] = MRP_TX_ACTION_S_NEW,
	[MRP_APPLICANT_AN] = MRP_TX_ACTION_S_NEW,
	[MRP_APPLICANT_AA] = MRP_TX_ACTION_S_JOIN_IN,
	[MRP_APPLICANT_QA] = MRP_TX_ACTION_S_JOIN_IN_OPTIONAL,
	[MRP_APPLICANT_LA] = MRP_TX_ACTION_S_LV,
	[MRP_APPLICANT_AO] = MRP_TX_ACTION_S_IN_OPTIONAL,
	[MRP_APPLICANT_QO] = MRP_TX_ACTION_S_IN_OPTIONAL,
	[MRP_APPLICANT_AP] = MRP_TX_ACTION_S_JOIN_IN,
	[MRP_APPLICANT_QP] = MRP_TX_ACTION_S_IN_OPTIONAL,
पूर्ण;

अटल व्योम mrp_attrvalue_inc(व्योम *value, u8 len)
अणु
	u8 *v = (u8 *)value;

	/* Add 1 to the last byte. If it becomes zero,
	 * go to the previous byte and repeat.
	 */
	जबतक (len > 0 && !++v[--len])
		;
पूर्ण

अटल पूर्णांक mrp_attr_cmp(स्थिर काष्ठा mrp_attr *attr,
			 स्थिर व्योम *value, u8 len, u8 type)
अणु
	अगर (attr->type != type)
		वापस attr->type - type;
	अगर (attr->len != len)
		वापस attr->len - len;
	वापस स_भेद(attr->value, value, len);
पूर्ण

अटल काष्ठा mrp_attr *mrp_attr_lookup(स्थिर काष्ठा mrp_applicant *app,
					स्थिर व्योम *value, u8 len, u8 type)
अणु
	काष्ठा rb_node *parent = app->mad.rb_node;
	काष्ठा mrp_attr *attr;
	पूर्णांक d;

	जबतक (parent) अणु
		attr = rb_entry(parent, काष्ठा mrp_attr, node);
		d = mrp_attr_cmp(attr, value, len, type);
		अगर (d > 0)
			parent = parent->rb_left;
		अन्यथा अगर (d < 0)
			parent = parent->rb_right;
		अन्यथा
			वापस attr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mrp_attr *mrp_attr_create(काष्ठा mrp_applicant *app,
					स्थिर व्योम *value, u8 len, u8 type)
अणु
	काष्ठा rb_node *parent = शून्य, **p = &app->mad.rb_node;
	काष्ठा mrp_attr *attr;
	पूर्णांक d;

	जबतक (*p) अणु
		parent = *p;
		attr = rb_entry(parent, काष्ठा mrp_attr, node);
		d = mrp_attr_cmp(attr, value, len, type);
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
	attr->state = MRP_APPLICANT_VO;
	attr->type  = type;
	attr->len   = len;
	स_नकल(attr->value, value, len);

	rb_link_node(&attr->node, parent, p);
	rb_insert_color(&attr->node, &app->mad);
	वापस attr;
पूर्ण

अटल व्योम mrp_attr_destroy(काष्ठा mrp_applicant *app, काष्ठा mrp_attr *attr)
अणु
	rb_erase(&attr->node, &app->mad);
	kमुक्त(attr);
पूर्ण

अटल पूर्णांक mrp_pdu_init(काष्ठा mrp_applicant *app)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा mrp_pdu_hdr *ph;

	skb = alloc_skb(app->dev->mtu + LL_RESERVED_SPACE(app->dev),
			GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	skb->dev = app->dev;
	skb->protocol = app->app->pkttype.type;
	skb_reserve(skb, LL_RESERVED_SPACE(app->dev));
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);

	ph = __skb_put(skb, माप(*ph));
	ph->version = app->app->version;

	app->pdu = skb;
	वापस 0;
पूर्ण

अटल पूर्णांक mrp_pdu_append_end_mark(काष्ठा mrp_applicant *app)
अणु
	__be16 *endmark;

	अगर (skb_tailroom(app->pdu) < माप(*endmark))
		वापस -1;
	endmark = __skb_put(app->pdu, माप(*endmark));
	put_unaligned(MRP_END_MARK, endmark);
	वापस 0;
पूर्ण

अटल व्योम mrp_pdu_queue(काष्ठा mrp_applicant *app)
अणु
	अगर (!app->pdu)
		वापस;

	अगर (mrp_cb(app->pdu)->mh)
		mrp_pdu_append_end_mark(app);
	mrp_pdu_append_end_mark(app);

	dev_hard_header(app->pdu, app->dev, ntohs(app->app->pkttype.type),
			app->app->group_address, app->dev->dev_addr,
			app->pdu->len);

	skb_queue_tail(&app->queue, app->pdu);
	app->pdu = शून्य;
पूर्ण

अटल व्योम mrp_queue_xmit(काष्ठा mrp_applicant *app)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&app->queue)))
		dev_queue_xmit(skb);
पूर्ण

अटल पूर्णांक mrp_pdu_append_msg_hdr(काष्ठा mrp_applicant *app,
				  u8 attrtype, u8 attrlen)
अणु
	काष्ठा mrp_msg_hdr *mh;

	अगर (mrp_cb(app->pdu)->mh) अणु
		अगर (mrp_pdu_append_end_mark(app) < 0)
			वापस -1;
		mrp_cb(app->pdu)->mh = शून्य;
		mrp_cb(app->pdu)->vah = शून्य;
	पूर्ण

	अगर (skb_tailroom(app->pdu) < माप(*mh))
		वापस -1;
	mh = __skb_put(app->pdu, माप(*mh));
	mh->attrtype = attrtype;
	mh->attrlen = attrlen;
	mrp_cb(app->pdu)->mh = mh;
	वापस 0;
पूर्ण

अटल पूर्णांक mrp_pdu_append_vecattr_hdr(काष्ठा mrp_applicant *app,
				      स्थिर व्योम *firstattrvalue, u8 attrlen)
अणु
	काष्ठा mrp_vecattr_hdr *vah;

	अगर (skb_tailroom(app->pdu) < माप(*vah) + attrlen)
		वापस -1;
	vah = __skb_put(app->pdu, माप(*vah) + attrlen);
	put_unaligned(0, &vah->lenflags);
	स_नकल(vah->firstattrvalue, firstattrvalue, attrlen);
	mrp_cb(app->pdu)->vah = vah;
	स_नकल(mrp_cb(app->pdu)->attrvalue, firstattrvalue, attrlen);
	वापस 0;
पूर्ण

अटल पूर्णांक mrp_pdu_append_vecattr_event(काष्ठा mrp_applicant *app,
					स्थिर काष्ठा mrp_attr *attr,
					क्रमागत mrp_vecattr_event vaevent)
अणु
	u16 len, pos;
	u8 *vaevents;
	पूर्णांक err;
again:
	अगर (!app->pdu) अणु
		err = mrp_pdu_init(app);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* If there is no Message header in the PDU, or the Message header is
	 * क्रम a dअगरferent attribute type, add an EndMark (अगर necessary) and a
	 * new Message header to the PDU.
	 */
	अगर (!mrp_cb(app->pdu)->mh ||
	    mrp_cb(app->pdu)->mh->attrtype != attr->type ||
	    mrp_cb(app->pdu)->mh->attrlen != attr->len) अणु
		अगर (mrp_pdu_append_msg_hdr(app, attr->type, attr->len) < 0)
			जाओ queue;
	पूर्ण

	/* If there is no VectorAttribute header क्रम this Message in the PDU,
	 * or this attribute's value करोes not sequentially follow the previous
	 * attribute's value, add a new VectorAttribute header to the PDU.
	 */
	अगर (!mrp_cb(app->pdu)->vah ||
	    स_भेद(mrp_cb(app->pdu)->attrvalue, attr->value, attr->len)) अणु
		अगर (mrp_pdu_append_vecattr_hdr(app, attr->value, attr->len) < 0)
			जाओ queue;
	पूर्ण

	len = be16_to_cpu(get_unaligned(&mrp_cb(app->pdu)->vah->lenflags));
	pos = len % 3;

	/* Events are packed पूर्णांकo Vectors in the PDU, three to a byte. Add a
	 * byte to the end of the Vector अगर necessary.
	 */
	अगर (!pos) अणु
		अगर (skb_tailroom(app->pdu) < माप(u8))
			जाओ queue;
		vaevents = __skb_put(app->pdu, माप(u8));
	पूर्ण अन्यथा अणु
		vaevents = (u8 *)(skb_tail_poपूर्णांकer(app->pdu) - माप(u8));
	पूर्ण

	चयन (pos) अणु
	हाल 0:
		*vaevents = vaevent * (__MRP_VECATTR_EVENT_MAX *
				       __MRP_VECATTR_EVENT_MAX);
		अवरोध;
	हाल 1:
		*vaevents += vaevent * __MRP_VECATTR_EVENT_MAX;
		अवरोध;
	हाल 2:
		*vaevents += vaevent;
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	/* Increment the length of the VectorAttribute in the PDU, as well as
	 * the value of the next attribute that would जारी its Vector.
	 */
	put_unaligned(cpu_to_be16(++len), &mrp_cb(app->pdu)->vah->lenflags);
	mrp_attrvalue_inc(mrp_cb(app->pdu)->attrvalue, attr->len);

	वापस 0;

queue:
	mrp_pdu_queue(app);
	जाओ again;
पूर्ण

अटल व्योम mrp_attr_event(काष्ठा mrp_applicant *app,
			   काष्ठा mrp_attr *attr, क्रमागत mrp_event event)
अणु
	क्रमागत mrp_applicant_state state;

	state = mrp_applicant_state_table[attr->state][event];
	अगर (state == MRP_APPLICANT_INVALID) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	अगर (event == MRP_EVENT_TX) अणु
		/* When appending the attribute fails, करोn't update its state
		 * in order to retry at the next TX event.
		 */

		चयन (mrp_tx_action_table[attr->state]) अणु
		हाल MRP_TX_ACTION_NONE:
		हाल MRP_TX_ACTION_S_JOIN_IN_OPTIONAL:
		हाल MRP_TX_ACTION_S_IN_OPTIONAL:
			अवरोध;
		हाल MRP_TX_ACTION_S_NEW:
			अगर (mrp_pdu_append_vecattr_event(
				    app, attr, MRP_VECATTR_EVENT_NEW) < 0)
				वापस;
			अवरोध;
		हाल MRP_TX_ACTION_S_JOIN_IN:
			अगर (mrp_pdu_append_vecattr_event(
				    app, attr, MRP_VECATTR_EVENT_JOIN_IN) < 0)
				वापस;
			अवरोध;
		हाल MRP_TX_ACTION_S_LV:
			अगर (mrp_pdu_append_vecattr_event(
				    app, attr, MRP_VECATTR_EVENT_LV) < 0)
				वापस;
			/* As a pure applicant, sending a leave message
			 * implies that the attribute was unरेजिस्टरed and
			 * can be destroyed.
			 */
			mrp_attr_destroy(app, attr);
			वापस;
		शेष:
			WARN_ON(1);
		पूर्ण
	पूर्ण

	attr->state = state;
पूर्ण

पूर्णांक mrp_request_join(स्थिर काष्ठा net_device *dev,
		     स्थिर काष्ठा mrp_application *appl,
		     स्थिर व्योम *value, u8 len, u8 type)
अणु
	काष्ठा mrp_port *port = rtnl_dereference(dev->mrp_port);
	काष्ठा mrp_applicant *app = rtnl_dereference(
		port->applicants[appl->type]);
	काष्ठा mrp_attr *attr;

	अगर (माप(काष्ठा mrp_skb_cb) + len >
	    माप_field(काष्ठा sk_buff, cb))
		वापस -ENOMEM;

	spin_lock_bh(&app->lock);
	attr = mrp_attr_create(app, value, len, type);
	अगर (!attr) अणु
		spin_unlock_bh(&app->lock);
		वापस -ENOMEM;
	पूर्ण
	mrp_attr_event(app, attr, MRP_EVENT_JOIN);
	spin_unlock_bh(&app->lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mrp_request_join);

व्योम mrp_request_leave(स्थिर काष्ठा net_device *dev,
		       स्थिर काष्ठा mrp_application *appl,
		       स्थिर व्योम *value, u8 len, u8 type)
अणु
	काष्ठा mrp_port *port = rtnl_dereference(dev->mrp_port);
	काष्ठा mrp_applicant *app = rtnl_dereference(
		port->applicants[appl->type]);
	काष्ठा mrp_attr *attr;

	अगर (माप(काष्ठा mrp_skb_cb) + len >
	    माप_field(काष्ठा sk_buff, cb))
		वापस;

	spin_lock_bh(&app->lock);
	attr = mrp_attr_lookup(app, value, len, type);
	अगर (!attr) अणु
		spin_unlock_bh(&app->lock);
		वापस;
	पूर्ण
	mrp_attr_event(app, attr, MRP_EVENT_LV);
	spin_unlock_bh(&app->lock);
पूर्ण
EXPORT_SYMBOL_GPL(mrp_request_leave);

अटल व्योम mrp_mad_event(काष्ठा mrp_applicant *app, क्रमागत mrp_event event)
अणु
	काष्ठा rb_node *node, *next;
	काष्ठा mrp_attr *attr;

	क्रम (node = rb_first(&app->mad);
	     next = node ? rb_next(node) : शून्य, node != शून्य;
	     node = next) अणु
		attr = rb_entry(node, काष्ठा mrp_attr, node);
		mrp_attr_event(app, attr, event);
	पूर्ण
पूर्ण

अटल व्योम mrp_join_समयr_arm(काष्ठा mrp_applicant *app)
अणु
	अचिन्हित दीर्घ delay;

	delay = (u64)msecs_to_jअगरfies(mrp_join_समय) * pअक्रमom_u32() >> 32;
	mod_समयr(&app->join_समयr, jअगरfies + delay);
पूर्ण

अटल व्योम mrp_join_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा mrp_applicant *app = from_समयr(app, t, join_समयr);

	spin_lock(&app->lock);
	mrp_mad_event(app, MRP_EVENT_TX);
	mrp_pdu_queue(app);
	spin_unlock(&app->lock);

	mrp_queue_xmit(app);
	mrp_join_समयr_arm(app);
पूर्ण

अटल व्योम mrp_periodic_समयr_arm(काष्ठा mrp_applicant *app)
अणु
	mod_समयr(&app->periodic_समयr,
		  jअगरfies + msecs_to_jअगरfies(mrp_periodic_समय));
पूर्ण

अटल व्योम mrp_periodic_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा mrp_applicant *app = from_समयr(app, t, periodic_समयr);

	spin_lock(&app->lock);
	mrp_mad_event(app, MRP_EVENT_PERIODIC);
	mrp_pdu_queue(app);
	spin_unlock(&app->lock);

	mrp_periodic_समयr_arm(app);
पूर्ण

अटल पूर्णांक mrp_pdu_parse_end_mark(काष्ठा sk_buff *skb, पूर्णांक *offset)
अणु
	__be16 endmark;

	अगर (skb_copy_bits(skb, *offset, &endmark, माप(endmark)) < 0)
		वापस -1;
	अगर (endmark == MRP_END_MARK) अणु
		*offset += माप(endmark);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mrp_pdu_parse_vecattr_event(काष्ठा mrp_applicant *app,
					काष्ठा sk_buff *skb,
					क्रमागत mrp_vecattr_event vaevent)
अणु
	काष्ठा mrp_attr *attr;
	क्रमागत mrp_event event;

	attr = mrp_attr_lookup(app, mrp_cb(skb)->attrvalue,
			       mrp_cb(skb)->mh->attrlen,
			       mrp_cb(skb)->mh->attrtype);
	अगर (attr == शून्य)
		वापस;

	चयन (vaevent) अणु
	हाल MRP_VECATTR_EVENT_NEW:
		event = MRP_EVENT_R_NEW;
		अवरोध;
	हाल MRP_VECATTR_EVENT_JOIN_IN:
		event = MRP_EVENT_R_JOIN_IN;
		अवरोध;
	हाल MRP_VECATTR_EVENT_IN:
		event = MRP_EVENT_R_IN;
		अवरोध;
	हाल MRP_VECATTR_EVENT_JOIN_MT:
		event = MRP_EVENT_R_JOIN_MT;
		अवरोध;
	हाल MRP_VECATTR_EVENT_MT:
		event = MRP_EVENT_R_MT;
		अवरोध;
	हाल MRP_VECATTR_EVENT_LV:
		event = MRP_EVENT_R_LV;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	mrp_attr_event(app, attr, event);
पूर्ण

अटल पूर्णांक mrp_pdu_parse_vecattr(काष्ठा mrp_applicant *app,
				 काष्ठा sk_buff *skb, पूर्णांक *offset)
अणु
	काष्ठा mrp_vecattr_hdr _vah;
	u16 valen;
	u8 vaevents, vaevent;

	mrp_cb(skb)->vah = skb_header_poपूर्णांकer(skb, *offset, माप(_vah),
					      &_vah);
	अगर (!mrp_cb(skb)->vah)
		वापस -1;
	*offset += माप(_vah);

	अगर (get_unaligned(&mrp_cb(skb)->vah->lenflags) &
	    MRP_VECATTR_HDR_FLAG_LA)
		mrp_mad_event(app, MRP_EVENT_R_LA);
	valen = be16_to_cpu(get_unaligned(&mrp_cb(skb)->vah->lenflags) &
			    MRP_VECATTR_HDR_LEN_MASK);

	/* The VectorAttribute काष्ठाure in a PDU carries event inक्रमmation
	 * about one or more attributes having consecutive values. Only the
	 * value क्रम the first attribute is contained in the काष्ठाure. So
	 * we make a copy of that value, and then increment it each समय we
	 * advance to the next event in its Vector.
	 */
	अगर (माप(काष्ठा mrp_skb_cb) + mrp_cb(skb)->mh->attrlen >
	    माप_field(काष्ठा sk_buff, cb))
		वापस -1;
	अगर (skb_copy_bits(skb, *offset, mrp_cb(skb)->attrvalue,
			  mrp_cb(skb)->mh->attrlen) < 0)
		वापस -1;
	*offset += mrp_cb(skb)->mh->attrlen;

	/* In a VectorAttribute, the Vector contains events which are packed
	 * three to a byte. We process one byte of the Vector at a समय.
	 */
	जबतक (valen > 0) अणु
		अगर (skb_copy_bits(skb, *offset, &vaevents,
				  माप(vaevents)) < 0)
			वापस -1;
		*offset += माप(vaevents);

		/* Extract and process the first event. */
		vaevent = vaevents / (__MRP_VECATTR_EVENT_MAX *
				      __MRP_VECATTR_EVENT_MAX);
		अगर (vaevent >= __MRP_VECATTR_EVENT_MAX) अणु
			/* The byte is malक्रमmed; stop processing. */
			वापस -1;
		पूर्ण
		mrp_pdu_parse_vecattr_event(app, skb, vaevent);

		/* If present, extract and process the second event. */
		अगर (!--valen)
			अवरोध;
		mrp_attrvalue_inc(mrp_cb(skb)->attrvalue,
				  mrp_cb(skb)->mh->attrlen);
		vaevents %= (__MRP_VECATTR_EVENT_MAX *
			     __MRP_VECATTR_EVENT_MAX);
		vaevent = vaevents / __MRP_VECATTR_EVENT_MAX;
		mrp_pdu_parse_vecattr_event(app, skb, vaevent);

		/* If present, extract and process the third event. */
		अगर (!--valen)
			अवरोध;
		mrp_attrvalue_inc(mrp_cb(skb)->attrvalue,
				  mrp_cb(skb)->mh->attrlen);
		vaevents %= __MRP_VECATTR_EVENT_MAX;
		vaevent = vaevents;
		mrp_pdu_parse_vecattr_event(app, skb, vaevent);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mrp_pdu_parse_msg(काष्ठा mrp_applicant *app, काष्ठा sk_buff *skb,
			     पूर्णांक *offset)
अणु
	काष्ठा mrp_msg_hdr _mh;

	mrp_cb(skb)->mh = skb_header_poपूर्णांकer(skb, *offset, माप(_mh), &_mh);
	अगर (!mrp_cb(skb)->mh)
		वापस -1;
	*offset += माप(_mh);

	अगर (mrp_cb(skb)->mh->attrtype == 0 ||
	    mrp_cb(skb)->mh->attrtype > app->app->maxattr ||
	    mrp_cb(skb)->mh->attrlen == 0)
		वापस -1;

	जबतक (skb->len > *offset) अणु
		अगर (mrp_pdu_parse_end_mark(skb, offset) < 0)
			अवरोध;
		अगर (mrp_pdu_parse_vecattr(app, skb, offset) < 0)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mrp_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		   काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा mrp_application *appl = container_of(pt, काष्ठा mrp_application,
						    pkttype);
	काष्ठा mrp_port *port;
	काष्ठा mrp_applicant *app;
	काष्ठा mrp_pdu_hdr _ph;
	स्थिर काष्ठा mrp_pdu_hdr *ph;
	पूर्णांक offset = skb_network_offset(skb);

	/* If the पूर्णांकerface is in promiscuous mode, drop the packet अगर
	 * it was unicast to another host.
	 */
	अगर (unlikely(skb->pkt_type == PACKET_OTHERHOST))
		जाओ out;
	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (unlikely(!skb))
		जाओ out;
	port = rcu_dereference(dev->mrp_port);
	अगर (unlikely(!port))
		जाओ out;
	app = rcu_dereference(port->applicants[appl->type]);
	अगर (unlikely(!app))
		जाओ out;

	ph = skb_header_poपूर्णांकer(skb, offset, माप(_ph), &_ph);
	अगर (!ph)
		जाओ out;
	offset += माप(_ph);

	अगर (ph->version != app->app->version)
		जाओ out;

	spin_lock(&app->lock);
	जबतक (skb->len > offset) अणु
		अगर (mrp_pdu_parse_end_mark(skb, &offset) < 0)
			अवरोध;
		अगर (mrp_pdu_parse_msg(app, skb, &offset) < 0)
			अवरोध;
	पूर्ण
	spin_unlock(&app->lock);
out:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक mrp_init_port(काष्ठा net_device *dev)
अणु
	काष्ठा mrp_port *port;

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;
	rcu_assign_poपूर्णांकer(dev->mrp_port, port);
	वापस 0;
पूर्ण

अटल व्योम mrp_release_port(काष्ठा net_device *dev)
अणु
	काष्ठा mrp_port *port = rtnl_dereference(dev->mrp_port);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i <= MRP_APPLICATION_MAX; i++) अणु
		अगर (rtnl_dereference(port->applicants[i]))
			वापस;
	पूर्ण
	RCU_INIT_POINTER(dev->mrp_port, शून्य);
	kमुक्त_rcu(port, rcu);
पूर्ण

पूर्णांक mrp_init_applicant(काष्ठा net_device *dev, काष्ठा mrp_application *appl)
अणु
	काष्ठा mrp_applicant *app;
	पूर्णांक err;

	ASSERT_RTNL();

	अगर (!rtnl_dereference(dev->mrp_port)) अणु
		err = mrp_init_port(dev);
		अगर (err < 0)
			जाओ err1;
	पूर्ण

	err = -ENOMEM;
	app = kzalloc(माप(*app), GFP_KERNEL);
	अगर (!app)
		जाओ err2;

	err = dev_mc_add(dev, appl->group_address);
	अगर (err < 0)
		जाओ err3;

	app->dev = dev;
	app->app = appl;
	app->mad = RB_ROOT;
	spin_lock_init(&app->lock);
	skb_queue_head_init(&app->queue);
	rcu_assign_poपूर्णांकer(dev->mrp_port->applicants[appl->type], app);
	समयr_setup(&app->join_समयr, mrp_join_समयr, 0);
	mrp_join_समयr_arm(app);
	समयr_setup(&app->periodic_समयr, mrp_periodic_समयr, 0);
	mrp_periodic_समयr_arm(app);
	वापस 0;

err3:
	kमुक्त(app);
err2:
	mrp_release_port(dev);
err1:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mrp_init_applicant);

व्योम mrp_uninit_applicant(काष्ठा net_device *dev, काष्ठा mrp_application *appl)
अणु
	काष्ठा mrp_port *port = rtnl_dereference(dev->mrp_port);
	काष्ठा mrp_applicant *app = rtnl_dereference(
		port->applicants[appl->type]);

	ASSERT_RTNL();

	RCU_INIT_POINTER(port->applicants[appl->type], शून्य);

	/* Delete समयr and generate a final TX event to flush out
	 * all pending messages beक्रमe the applicant is gone.
	 */
	del_समयr_sync(&app->join_समयr);
	del_समयr_sync(&app->periodic_समयr);

	spin_lock_bh(&app->lock);
	mrp_mad_event(app, MRP_EVENT_TX);
	mrp_pdu_queue(app);
	spin_unlock_bh(&app->lock);

	mrp_queue_xmit(app);

	dev_mc_del(dev, appl->group_address);
	kमुक्त_rcu(app, rcu);
	mrp_release_port(dev);
पूर्ण
EXPORT_SYMBOL_GPL(mrp_uninit_applicant);

पूर्णांक mrp_रेजिस्टर_application(काष्ठा mrp_application *appl)
अणु
	appl->pkttype.func = mrp_rcv;
	dev_add_pack(&appl->pkttype);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mrp_रेजिस्टर_application);

व्योम mrp_unरेजिस्टर_application(काष्ठा mrp_application *appl)
अणु
	dev_हटाओ_pack(&appl->pkttype);
पूर्ण
EXPORT_SYMBOL_GPL(mrp_unरेजिस्टर_application);
