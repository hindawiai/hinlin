<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	SNAP data link layer. Derived from 802.2
 *
 *		Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *		from the 802.2 layer by Greg Page.
 *		Merged in additions from Greg Page's psnap.c.
 */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/datalink.h>
#समावेश <net/llc.h>
#समावेश <net/psnap.h>
#समावेश <linux/mm.h>
#समावेश <linux/in.h>
#समावेश <linux/init.h>
#समावेश <linux/rculist.h>

अटल LIST_HEAD(snap_list);
अटल DEFINE_SPINLOCK(snap_lock);
अटल काष्ठा llc_sap *snap_sap;

/*
 *	Find a snap client by matching the 5 bytes.
 */
अटल काष्ठा datalink_proto *find_snap_client(स्थिर अचिन्हित अक्षर *desc)
अणु
	काष्ठा datalink_proto *proto = शून्य, *p;

	list_क्रम_each_entry_rcu(p, &snap_list, node, lockdep_is_held(&snap_lock)) अणु
		अगर (!स_भेद(p->type, desc, 5)) अणु
			proto = p;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस proto;
पूर्ण

/*
 *	A SNAP packet has arrived
 */
अटल पूर्णांक snap_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		    काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	पूर्णांक rc = 1;
	काष्ठा datalink_proto *proto;
	अटल काष्ठा packet_type snap_packet_type = अणु
		.type = cpu_to_be16(ETH_P_SNAP),
	पूर्ण;

	अगर (unlikely(!pskb_may_pull(skb, 5)))
		जाओ drop;

	rcu_पढ़ो_lock();
	proto = find_snap_client(skb_transport_header(skb));
	अगर (proto) अणु
		/* Pass the frame on. */
		skb->transport_header += 5;
		skb_pull_rcsum(skb, 5);
		rc = proto->rcvfunc(skb, dev, &snap_packet_type, orig_dev);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (unlikely(!proto))
		जाओ drop;

out:
	वापस rc;

drop:
	kमुक्त_skb(skb);
	जाओ out;
पूर्ण

/*
 *	Put a SNAP header on a frame and pass to 802.2
 */
अटल पूर्णांक snap_request(काष्ठा datalink_proto *dl,
			काष्ठा sk_buff *skb, u8 *dest)
अणु
	स_नकल(skb_push(skb, 5), dl->type, 5);
	llc_build_and_send_ui_pkt(snap_sap, skb, dest, snap_sap->laddr.lsap);
	वापस 0;
पूर्ण

/*
 *	Set up the SNAP layer
 */
EXPORT_SYMBOL(रेजिस्टर_snap_client);
EXPORT_SYMBOL(unरेजिस्टर_snap_client);

अटल स्थिर अक्षर snap_err_msg[] __initस्थिर =
	KERN_CRIT "SNAP - unable to register with 802.2\n";

अटल पूर्णांक __init snap_init(व्योम)
अणु
	snap_sap = llc_sap_खोलो(0xAA, snap_rcv);
	अगर (!snap_sap) अणु
		prपूर्णांकk(snap_err_msg);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

module_init(snap_init);

अटल व्योम __निकास snap_निकास(व्योम)
अणु
	llc_sap_put(snap_sap);
पूर्ण

module_निकास(snap_निकास);


/*
 *	Register SNAP clients. We करोn't yet use this क्रम IP.
 */
काष्ठा datalink_proto *रेजिस्टर_snap_client(स्थिर अचिन्हित अक्षर *desc,
					    पूर्णांक (*rcvfunc)(काष्ठा sk_buff *,
							   काष्ठा net_device *,
							   काष्ठा packet_type *,
							   काष्ठा net_device *))
अणु
	काष्ठा datalink_proto *proto = शून्य;

	spin_lock_bh(&snap_lock);

	अगर (find_snap_client(desc))
		जाओ out;

	proto = kदो_स्मृति(माप(*proto), GFP_ATOMIC);
	अगर (proto) अणु
		स_नकल(proto->type, desc, 5);
		proto->rcvfunc		= rcvfunc;
		proto->header_length	= 5 + 3; /* snap + 802.2 */
		proto->request		= snap_request;
		list_add_rcu(&proto->node, &snap_list);
	पूर्ण
out:
	spin_unlock_bh(&snap_lock);

	वापस proto;
पूर्ण

/*
 *	Unरेजिस्टर SNAP clients. Protocols no दीर्घer want to play with us ...
 */
व्योम unरेजिस्टर_snap_client(काष्ठा datalink_proto *proto)
अणु
	spin_lock_bh(&snap_lock);
	list_del_rcu(&proto->node);
	spin_unlock_bh(&snap_lock);

	synchronize_net();

	kमुक्त(proto);
पूर्ण

MODULE_LICENSE("GPL");
