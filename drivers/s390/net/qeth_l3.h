<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Copyright IBM Corp. 2007
 *    Author(s): Utz Bacher <utz.bacher@de.ibm.com>,
 *		 Frank Pavlic <fpavlic@de.ibm.com>,
 *		 Thomas Spatzier <tspat@de.ibm.com>,
 *		 Frank Blaschka <frank.blaschka@de.ibm.com>
 */

#अगर_अघोषित __QETH_L3_H__
#घोषणा __QETH_L3_H__

#समावेश "qeth_core.h"
#समावेश <linux/hashtable.h>

क्रमागत qeth_ip_types अणु
	QETH_IP_TYPE_NORMAL,
	QETH_IP_TYPE_VIPA,
	QETH_IP_TYPE_RXIP,
पूर्ण;

काष्ठा qeth_ipaddr अणु
	काष्ठा hlist_node hnode;
	क्रमागत qeth_ip_types type;
	u8 is_multicast:1;
	u8 disp_flag:2;
	u8 ipato:1;			/* ucast only */

	/* is changed only क्रम normal ip addresses
	 * क्रम non-normal addresses it always is  1
	 */
	पूर्णांक  ref_counter;
	क्रमागत qeth_prot_versions proto;
	जोड़ अणु
		काष्ठा अणु
			__be32 addr;
			__be32 mask;
		पूर्ण a4;
		काष्ठा अणु
			काष्ठा in6_addr addr;
			अचिन्हित पूर्णांक pfxlen;
		पूर्ण a6;
	पूर्ण u;
पूर्ण;

अटल अंतरभूत व्योम qeth_l3_init_ipaddr(काष्ठा qeth_ipaddr *addr,
				       क्रमागत qeth_ip_types type,
				       क्रमागत qeth_prot_versions proto)
अणु
	स_रखो(addr, 0, माप(*addr));
	addr->type = type;
	addr->proto = proto;
	addr->disp_flag = QETH_DISP_ADDR_DO_NOTHING;
	addr->ref_counter = 1;
पूर्ण

अटल अंतरभूत bool qeth_l3_addr_match_ip(काष्ठा qeth_ipaddr *a1,
					 काष्ठा qeth_ipaddr *a2)
अणु
	अगर (a1->proto != a2->proto)
		वापस false;
	अगर (a1->proto == QETH_PROT_IPV6)
		वापस ipv6_addr_equal(&a1->u.a6.addr, &a2->u.a6.addr);
	वापस a1->u.a4.addr == a2->u.a4.addr;
पूर्ण

अटल अंतरभूत bool qeth_l3_addr_match_all(काष्ठा qeth_ipaddr *a1,
					  काष्ठा qeth_ipaddr *a2)
अणु
	/* Assumes that the pair was obtained via qeth_l3_addr_find_by_ip(),
	 * so 'proto' and 'addr' match क्रम sure.
	 *
	 * For ucast:
	 * -	'mask'/'pfxlen' क्रम RXIP/VIPA is always 0. For NORMAL, matching
	 *	values are required to aव्योम mixups in takeover eligibility.
	 *
	 * For mcast,
	 * -	'mask'/'pfxlen' is always 0.
	 */
	अगर (a1->type != a2->type)
		वापस false;
	अगर (a1->proto == QETH_PROT_IPV6)
		वापस a1->u.a6.pfxlen == a2->u.a6.pfxlen;
	वापस a1->u.a4.mask == a2->u.a4.mask;
पूर्ण

अटल अंतरभूत u32 qeth_l3_ipaddr_hash(काष्ठा qeth_ipaddr *addr)
अणु
	अगर (addr->proto == QETH_PROT_IPV6)
		वापस ipv6_addr_hash(&addr->u.a6.addr);
	अन्यथा
		वापस ipv4_addr_hash(addr->u.a4.addr);
पूर्ण

काष्ठा qeth_ipato_entry अणु
	काष्ठा list_head entry;
	क्रमागत qeth_prot_versions proto;
	अक्षर addr[16];
	अचिन्हित पूर्णांक mask_bits;
पूर्ण;

बाह्य स्थिर काष्ठा attribute_group *qeth_l3_attr_groups[];

पूर्णांक qeth_l3_ipaddr_to_string(क्रमागत qeth_prot_versions proto, स्थिर u8 *addr,
			     अक्षर *buf);
पूर्णांक qeth_l3_setrouting_v4(काष्ठा qeth_card *);
पूर्णांक qeth_l3_setrouting_v6(काष्ठा qeth_card *);
पूर्णांक qeth_l3_add_ipato_entry(काष्ठा qeth_card *, काष्ठा qeth_ipato_entry *);
पूर्णांक qeth_l3_del_ipato_entry(काष्ठा qeth_card *card,
			    क्रमागत qeth_prot_versions proto, u8 *addr,
			    अचिन्हित पूर्णांक mask_bits);
व्योम qeth_l3_update_ipato(काष्ठा qeth_card *card);
पूर्णांक qeth_l3_modअगरy_hsuid(काष्ठा qeth_card *card, bool add);
पूर्णांक qeth_l3_modअगरy_rxip_vipa(काष्ठा qeth_card *card, bool add, स्थिर u8 *ip,
			     क्रमागत qeth_ip_types type,
			     क्रमागत qeth_prot_versions proto);

#पूर्ण_अगर /* __QETH_L3_H__ */
