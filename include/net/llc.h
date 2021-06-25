<शैली गुरु>
#अगर_अघोषित LLC_H
#घोषणा LLC_H
/*
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

#समावेश <linux/अगर.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rculist_nulls.h>
#समावेश <linux/hash.h>
#समावेश <linux/jhash.h>

#समावेश <linux/atomic.h>

काष्ठा net_device;
काष्ठा packet_type;
काष्ठा sk_buff;

काष्ठा llc_addr अणु
	अचिन्हित अक्षर lsap;
	अचिन्हित अक्षर mac[IFHWADDRLEN];
पूर्ण;

#घोषणा LLC_SAP_STATE_INACTIVE	1
#घोषणा LLC_SAP_STATE_ACTIVE	2

#घोषणा LLC_SK_DEV_HASH_BITS 6
#घोषणा LLC_SK_DEV_HASH_ENTRIES (1<<LLC_SK_DEV_HASH_BITS)

#घोषणा LLC_SK_LADDR_HASH_BITS 6
#घोषणा LLC_SK_LADDR_HASH_ENTRIES (1<<LLC_SK_LADDR_HASH_BITS)

/**
 * काष्ठा llc_sap - Defines the SAP component
 *
 * @station - station this sap beदीर्घs to
 * @state - sap state
 * @p_bit - only lowest-order bit used
 * @f_bit - only lowest-order bit used
 * @laddr - SAP value in this 'lsap'
 * @node - entry in station sap_list
 * @sk_list - LLC sockets this one manages
 */
काष्ठा llc_sap अणु
	अचिन्हित अक्षर	 state;
	अचिन्हित अक्षर	 p_bit;
	अचिन्हित अक्षर	 f_bit;
	refcount_t		 refcnt;
	पूर्णांक		 (*rcv_func)(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev,
				     काष्ठा packet_type *pt,
				     काष्ठा net_device *orig_dev);
	काष्ठा llc_addr	 laddr;
	काष्ठा list_head node;
	spinlock_t sk_lock;
	पूर्णांक sk_count;
	काष्ठा hlist_nulls_head sk_laddr_hash[LLC_SK_LADDR_HASH_ENTRIES];
	काष्ठा hlist_head sk_dev_hash[LLC_SK_DEV_HASH_ENTRIES];
	काष्ठा rcu_head rcu;
पूर्ण;

अटल अंतरभूत
काष्ठा hlist_head *llc_sk_dev_hash(काष्ठा llc_sap *sap, पूर्णांक अगरindex)
अणु
	वापस &sap->sk_dev_hash[अगरindex % LLC_SK_DEV_HASH_ENTRIES];
पूर्ण

अटल अंतरभूत
u32 llc_sk_laddr_hashfn(काष्ठा llc_sap *sap, स्थिर काष्ठा llc_addr *laddr)
अणु
	वापस hash_32(jhash(laddr->mac, माप(laddr->mac), 0),
		       LLC_SK_LADDR_HASH_BITS);
पूर्ण

अटल अंतरभूत
काष्ठा hlist_nulls_head *llc_sk_laddr_hash(काष्ठा llc_sap *sap,
					   स्थिर काष्ठा llc_addr *laddr)
अणु
	वापस &sap->sk_laddr_hash[llc_sk_laddr_hashfn(sap, laddr)];
पूर्ण

#घोषणा LLC_DEST_INVALID         0      /* Invalid LLC PDU type */
#घोषणा LLC_DEST_SAP             1      /* Type 1 goes here */
#घोषणा LLC_DEST_CONN            2      /* Type 2 goes here */

बाह्य काष्ठा list_head llc_sap_list;

पूर्णांक llc_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev, काष्ठा packet_type *pt,
	    काष्ठा net_device *orig_dev);

पूर्णांक llc_mac_hdr_init(काष्ठा sk_buff *skb, स्थिर अचिन्हित अक्षर *sa,
		     स्थिर अचिन्हित अक्षर *da);

व्योम llc_add_pack(पूर्णांक type,
		  व्योम (*handler)(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb));
व्योम llc_हटाओ_pack(पूर्णांक type);

व्योम llc_set_station_handler(व्योम (*handler)(काष्ठा sk_buff *skb));

काष्ठा llc_sap *llc_sap_खोलो(अचिन्हित अक्षर lsap,
			     पूर्णांक (*rcv)(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev,
					काष्ठा packet_type *pt,
					काष्ठा net_device *orig_dev));
अटल अंतरभूत व्योम llc_sap_hold(काष्ठा llc_sap *sap)
अणु
	refcount_inc(&sap->refcnt);
पूर्ण

अटल अंतरभूत bool llc_sap_hold_safe(काष्ठा llc_sap *sap)
अणु
	वापस refcount_inc_not_zero(&sap->refcnt);
पूर्ण

व्योम llc_sap_बंद(काष्ठा llc_sap *sap);

अटल अंतरभूत व्योम llc_sap_put(काष्ठा llc_sap *sap)
अणु
	अगर (refcount_dec_and_test(&sap->refcnt))
		llc_sap_बंद(sap);
पूर्ण

काष्ठा llc_sap *llc_sap_find(अचिन्हित अक्षर sap_value);

पूर्णांक llc_build_and_send_ui_pkt(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb,
			      अचिन्हित अक्षर *dmac, अचिन्हित अक्षर dsap);

व्योम llc_sap_handler(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);
व्योम llc_conn_handler(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);

व्योम llc_station_init(व्योम);
व्योम llc_station_निकास(व्योम);

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक llc_proc_init(व्योम);
व्योम llc_proc_निकास(व्योम);
#अन्यथा
#घोषणा llc_proc_init()	(0)
#घोषणा llc_proc_निकास()	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर /* CONFIG_PROC_FS */
#अगर_घोषित CONFIG_SYSCTL
पूर्णांक llc_sysctl_init(व्योम);
व्योम llc_sysctl_निकास(व्योम);

बाह्य पूर्णांक sysctl_llc2_ack_समयout;
बाह्य पूर्णांक sysctl_llc2_busy_समयout;
बाह्य पूर्णांक sysctl_llc2_p_समयout;
बाह्य पूर्णांक sysctl_llc2_rej_समयout;
#अन्यथा
#घोषणा llc_sysctl_init() (0)
#घोषणा llc_sysctl_निकास() करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर /* CONFIG_SYSCTL */
#पूर्ण_अगर /* LLC_H */
