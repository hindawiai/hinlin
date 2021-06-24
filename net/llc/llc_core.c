<शैली गुरु>
/*
 * llc_core.c - Minimum needed routines क्रम sap handling and module init/निकास
 *
 * Copyright (c) 1997 by Procom Technology, Inc.
 * 		 2001-2003 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <net/net_namespace.h>
#समावेश <net/llc.h>

LIST_HEAD(llc_sap_list);
अटल DEFINE_SPINLOCK(llc_sap_list_lock);

/**
 *	llc_sap_alloc - allocates and initializes sap.
 *
 *	Allocates and initializes sap.
 */
अटल काष्ठा llc_sap *llc_sap_alloc(व्योम)
अणु
	काष्ठा llc_sap *sap = kzalloc(माप(*sap), GFP_ATOMIC);
	पूर्णांक i;

	अगर (sap) अणु
		/* sap->laddr.mac - leave as a null, it's filled by bind */
		sap->state = LLC_SAP_STATE_ACTIVE;
		spin_lock_init(&sap->sk_lock);
		क्रम (i = 0; i < LLC_SK_LADDR_HASH_ENTRIES; i++)
			INIT_HLIST_शून्यS_HEAD(&sap->sk_laddr_hash[i], i);
		refcount_set(&sap->refcnt, 1);
	पूर्ण
	वापस sap;
पूर्ण

अटल काष्ठा llc_sap *__llc_sap_find(अचिन्हित अक्षर sap_value)
अणु
	काष्ठा llc_sap *sap;

	list_क्रम_each_entry(sap, &llc_sap_list, node)
		अगर (sap->laddr.lsap == sap_value)
			जाओ out;
	sap = शून्य;
out:
	वापस sap;
पूर्ण

/**
 *	llc_sap_find - searches a SAP in station
 *	@sap_value: sap to be found
 *
 *	Searches क्रम a sap in the sap list of the LLC's station upon the sap ID.
 *	If the sap is found it will be refcounted and the user will have to करो
 *	a llc_sap_put after use.
 *	Returns the sap or %शून्य अगर not found.
 */
काष्ठा llc_sap *llc_sap_find(अचिन्हित अक्षर sap_value)
अणु
	काष्ठा llc_sap *sap;

	rcu_पढ़ो_lock_bh();
	sap = __llc_sap_find(sap_value);
	अगर (!sap || !llc_sap_hold_safe(sap))
		sap = शून्य;
	rcu_पढ़ो_unlock_bh();
	वापस sap;
पूर्ण

/**
 *	llc_sap_खोलो - खोलो पूर्णांकerface to the upper layers.
 *	@lsap: SAP number.
 *	@func: rcv func क्रम datalink protos
 *
 *	Interface function to upper layer. Each one who wants to get a SAP
 *	(क्रम example NetBEUI) should call this function. Returns the खोलोed
 *	SAP क्रम success, शून्य क्रम failure.
 */
काष्ठा llc_sap *llc_sap_खोलो(अचिन्हित अक्षर lsap,
			     पूर्णांक (*func)(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev,
					 काष्ठा packet_type *pt,
					 काष्ठा net_device *orig_dev))
अणु
	काष्ठा llc_sap *sap = शून्य;

	spin_lock_bh(&llc_sap_list_lock);
	अगर (__llc_sap_find(lsap)) /* SAP alपढ़ोy exists */
		जाओ out;
	sap = llc_sap_alloc();
	अगर (!sap)
		जाओ out;
	sap->laddr.lsap = lsap;
	sap->rcv_func	= func;
	list_add_tail_rcu(&sap->node, &llc_sap_list);
out:
	spin_unlock_bh(&llc_sap_list_lock);
	वापस sap;
पूर्ण

/**
 *	llc_sap_बंद - बंद पूर्णांकerface क्रम upper layers.
 *	@sap: SAP to be बंदd.
 *
 *	Close पूर्णांकerface function to upper layer. Each one who wants to
 *	बंद an खोलो SAP (क्रम example NetBEUI) should call this function.
 * 	Removes this sap from the list of saps in the station and then
 * 	मुक्तs the memory क्रम this sap.
 */
व्योम llc_sap_बंद(काष्ठा llc_sap *sap)
अणु
	WARN_ON(sap->sk_count);

	spin_lock_bh(&llc_sap_list_lock);
	list_del_rcu(&sap->node);
	spin_unlock_bh(&llc_sap_list_lock);

	kमुक्त_rcu(sap, rcu);
पूर्ण

अटल काष्ठा packet_type llc_packet_type __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_802_2),
	.func = llc_rcv,
पूर्ण;

अटल काष्ठा packet_type llc_tr_packet_type __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_TR_802_2),
	.func = llc_rcv,
पूर्ण;

अटल पूर्णांक __init llc_init(व्योम)
अणु
	dev_add_pack(&llc_packet_type);
	dev_add_pack(&llc_tr_packet_type);
	वापस 0;
पूर्ण

अटल व्योम __निकास llc_निकास(व्योम)
अणु
	dev_हटाओ_pack(&llc_packet_type);
	dev_हटाओ_pack(&llc_tr_packet_type);
पूर्ण

module_init(llc_init);
module_निकास(llc_निकास);

EXPORT_SYMBOL(llc_sap_list);
EXPORT_SYMBOL(llc_sap_find);
EXPORT_SYMBOL(llc_sap_खोलो);
EXPORT_SYMBOL(llc_sap_बंद);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Procom 1997, Jay Schullist 2001, Arnaldo C. Melo 2001-2003");
MODULE_DESCRIPTION("LLC IEEE 802.2 core support");
