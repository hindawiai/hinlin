<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	NET3:	Support क्रम 802.2 demultiplexing off Ethernet
 *
 *		Demultiplex 802.2 encoded protocols. We match the entry by the
 *		SSAP/DSAP pair and then deliver to the रेजिस्टरed datalink that
 *		matches. The control byte is ignored and handling of such items
 *		is up to the routine passed the frame.
 *
 *		Unlike the 802.3 datalink we have a list of 802.2 entries as
 *		there are multiple protocols to demux. The list is currently
 *		लघु (3 or 4 entries at most). The current demux assumes this.
 */
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/datalink.h>
#समावेश <linux/mm.h>
#समावेश <linux/in.h>
#समावेश <linux/init.h>
#समावेश <net/llc.h>
#समावेश <net/p8022.h>

अटल पूर्णांक p8022_request(काष्ठा datalink_proto *dl, काष्ठा sk_buff *skb,
			 अचिन्हित अक्षर *dest)
अणु
	llc_build_and_send_ui_pkt(dl->sap, skb, dest, dl->sap->laddr.lsap);
	वापस 0;
पूर्ण

काष्ठा datalink_proto *रेजिस्टर_8022_client(अचिन्हित अक्षर type,
					    पूर्णांक (*func)(काष्ठा sk_buff *skb,
							काष्ठा net_device *dev,
							काष्ठा packet_type *pt,
							काष्ठा net_device *orig_dev))
अणु
	काष्ठा datalink_proto *proto;

	proto = kदो_स्मृति(माप(*proto), GFP_ATOMIC);
	अगर (proto) अणु
		proto->type[0]		= type;
		proto->header_length	= 3;
		proto->request		= p8022_request;
		proto->sap = llc_sap_खोलो(type, func);
		अगर (!proto->sap) अणु
			kमुक्त(proto);
			proto = शून्य;
		पूर्ण
	पूर्ण
	वापस proto;
पूर्ण

व्योम unरेजिस्टर_8022_client(काष्ठा datalink_proto *proto)
अणु
	llc_sap_put(proto->sap);
	kमुक्त(proto);
पूर्ण

EXPORT_SYMBOL(रेजिस्टर_8022_client);
EXPORT_SYMBOL(unरेजिस्टर_8022_client);

MODULE_LICENSE("GPL");
