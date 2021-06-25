<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	STP SAP demux
 *
 *	Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 */
#समावेश <linux/mutex.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/llc.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <net/llc.h>
#समावेश <net/llc_pdu.h>
#समावेश <net/stp.h>

/* 01:80:c2:00:00:20 - 01:80:c2:00:00:2F */
#घोषणा GARP_ADDR_MIN	0x20
#घोषणा GARP_ADDR_MAX	0x2F
#घोषणा GARP_ADDR_RANGE	(GARP_ADDR_MAX - GARP_ADDR_MIN)

अटल स्थिर काष्ठा stp_proto __rcu *garp_protos[GARP_ADDR_RANGE + 1] __पढ़ो_mostly;
अटल स्थिर काष्ठा stp_proto __rcu *stp_proto __पढ़ो_mostly;

अटल काष्ठा llc_sap *sap __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक sap_रेजिस्टरed;
अटल DEFINE_MUTEX(stp_proto_mutex);

/* Called under rcu_पढ़ो_lock from LLC */
अटल पूर्णांक stp_pdu_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		       काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	स्थिर काष्ठा ethhdr *eh = eth_hdr(skb);
	स्थिर काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);
	स्थिर काष्ठा stp_proto *proto;

	अगर (pdu->ssap != LLC_SAP_BSPAN ||
	    pdu->dsap != LLC_SAP_BSPAN ||
	    pdu->ctrl_1 != LLC_PDU_TYPE_U)
		जाओ err;

	अगर (eh->h_dest[5] >= GARP_ADDR_MIN && eh->h_dest[5] <= GARP_ADDR_MAX) अणु
		proto = rcu_dereference(garp_protos[eh->h_dest[5] -
						    GARP_ADDR_MIN]);
		अगर (proto &&
		    !ether_addr_equal(eh->h_dest, proto->group_address))
			जाओ err;
	पूर्ण अन्यथा
		proto = rcu_dereference(stp_proto);

	अगर (!proto)
		जाओ err;

	proto->rcv(proto, skb, dev);
	वापस 0;

err:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

पूर्णांक stp_proto_रेजिस्टर(स्थिर काष्ठा stp_proto *proto)
अणु
	पूर्णांक err = 0;

	mutex_lock(&stp_proto_mutex);
	अगर (sap_रेजिस्टरed++ == 0) अणु
		sap = llc_sap_खोलो(LLC_SAP_BSPAN, stp_pdu_rcv);
		अगर (!sap) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (is_zero_ether_addr(proto->group_address))
		rcu_assign_poपूर्णांकer(stp_proto, proto);
	अन्यथा
		rcu_assign_poपूर्णांकer(garp_protos[proto->group_address[5] -
					       GARP_ADDR_MIN], proto);
out:
	mutex_unlock(&stp_proto_mutex);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(stp_proto_रेजिस्टर);

व्योम stp_proto_unरेजिस्टर(स्थिर काष्ठा stp_proto *proto)
अणु
	mutex_lock(&stp_proto_mutex);
	अगर (is_zero_ether_addr(proto->group_address))
		RCU_INIT_POINTER(stp_proto, शून्य);
	अन्यथा
		RCU_INIT_POINTER(garp_protos[proto->group_address[5] -
					       GARP_ADDR_MIN], शून्य);
	synchronize_rcu();

	अगर (--sap_रेजिस्टरed == 0)
		llc_sap_put(sap);
	mutex_unlock(&stp_proto_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(stp_proto_unरेजिस्टर);

MODULE_LICENSE("GPL");
