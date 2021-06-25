<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NetLabel Doमुख्य Hash Table
 *
 * This file manages the करोमुख्य hash table that NetLabel uses to determine
 * which network labeling protocol to use क्रम a given करोमुख्य.  The NetLabel
 * प्रणाली manages अटल and dynamic label mappings क्रम network protocols such
 * as CIPSO and RIPSO.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006, 2008
 */

#अगर_अघोषित _NETLABEL_DOMAINHASH_H
#घोषणा _NETLABEL_DOMAINHASH_H

#समावेश <linux/types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/list.h>

#समावेश "netlabel_addrlist.h"

/* Doमुख्य hash table size */
/* XXX - currently this number is an uneducated guess */
#घोषणा NETLBL_DOMHSH_BITSIZE       7

/* Doमुख्य mapping definition काष्ठाures */
काष्ठा netlbl_करोmaddr_map अणु
	काष्ठा list_head list4;
	काष्ठा list_head list6;
पूर्ण;
काष्ठा netlbl_करोmmap_def अणु
	u32 type;
	जोड़ अणु
		काष्ठा netlbl_करोmaddr_map *addrsel;
		काष्ठा cipso_v4_करोi *cipso;
		काष्ठा calipso_करोi *calipso;
	पूर्ण;
पूर्ण;
#घोषणा netlbl_करोmhsh_addr4_entry(iter) \
	container_of(iter, काष्ठा netlbl_करोmaddr4_map, list)
काष्ठा netlbl_करोmaddr4_map अणु
	काष्ठा netlbl_करोmmap_def def;

	काष्ठा netlbl_af4list list;
पूर्ण;
#घोषणा netlbl_करोmhsh_addr6_entry(iter) \
	container_of(iter, काष्ठा netlbl_करोmaddr6_map, list)
काष्ठा netlbl_करोmaddr6_map अणु
	काष्ठा netlbl_करोmmap_def def;

	काष्ठा netlbl_af6list list;
पूर्ण;

काष्ठा netlbl_करोm_map अणु
	अक्षर *करोमुख्य;
	u16 family;
	काष्ठा netlbl_करोmmap_def def;

	u32 valid;
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
पूर्ण;

/* init function */
पूर्णांक netlbl_करोmhsh_init(u32 size);

/* Manipulate the करोमुख्य hash table */
पूर्णांक netlbl_करोmhsh_add(काष्ठा netlbl_करोm_map *entry,
		      काष्ठा netlbl_audit *audit_info);
पूर्णांक netlbl_करोmhsh_add_शेष(काष्ठा netlbl_करोm_map *entry,
			      काष्ठा netlbl_audit *audit_info);
पूर्णांक netlbl_करोmhsh_हटाओ_entry(काष्ठा netlbl_करोm_map *entry,
			       काष्ठा netlbl_audit *audit_info);
पूर्णांक netlbl_करोmhsh_हटाओ_af4(स्थिर अक्षर *करोमुख्य,
			     स्थिर काष्ठा in_addr *addr,
			     स्थिर काष्ठा in_addr *mask,
			     काष्ठा netlbl_audit *audit_info);
पूर्णांक netlbl_करोmhsh_हटाओ_af6(स्थिर अक्षर *करोमुख्य,
			     स्थिर काष्ठा in6_addr *addr,
			     स्थिर काष्ठा in6_addr *mask,
			     काष्ठा netlbl_audit *audit_info);
पूर्णांक netlbl_करोmhsh_हटाओ(स्थिर अक्षर *करोमुख्य, u16 family,
			 काष्ठा netlbl_audit *audit_info);
पूर्णांक netlbl_करोmhsh_हटाओ_शेष(u16 family, काष्ठा netlbl_audit *audit_info);
काष्ठा netlbl_करोm_map *netlbl_करोmhsh_getentry(स्थिर अक्षर *करोमुख्य, u16 family);
काष्ठा netlbl_करोmmap_def *netlbl_करोmhsh_getentry_af4(स्थिर अक्षर *करोमुख्य,
						     __be32 addr);
#अगर IS_ENABLED(CONFIG_IPV6)
काष्ठा netlbl_करोmmap_def *netlbl_करोmhsh_getentry_af6(स्थिर अक्षर *करोमुख्य,
						   स्थिर काष्ठा in6_addr *addr);
पूर्णांक netlbl_करोmhsh_हटाओ_af6(स्थिर अक्षर *करोमुख्य,
			     स्थिर काष्ठा in6_addr *addr,
			     स्थिर काष्ठा in6_addr *mask,
			     काष्ठा netlbl_audit *audit_info);
#पूर्ण_अगर /* IPv6 */

पूर्णांक netlbl_करोmhsh_walk(u32 *skip_bkt,
		     u32 *skip_chain,
		     पूर्णांक (*callback) (काष्ठा netlbl_करोm_map *entry, व्योम *arg),
		     व्योम *cb_arg);

#पूर्ण_अगर
