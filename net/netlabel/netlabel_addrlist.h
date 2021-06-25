<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NetLabel Network Address Lists
 *
 * This file contains network address list functions used to manage ordered
 * lists of network addresses क्रम use by the NetLabel subप्रणाली.  The NetLabel
 * प्रणाली manages अटल and dynamic label mappings क्रम network protocols such
 * as CIPSO and RIPSO.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2008
 */

#अगर_अघोषित _NETLABEL_ADDRLIST_H
#घोषणा _NETLABEL_ADDRLIST_H

#समावेश <linux/types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/list.h>
#समावेश <linux/in6.h>
#समावेश <linux/audit.h>

/**
 * काष्ठा netlbl_af4list - NetLabel IPv4 address list
 * @addr: IPv4 address
 * @mask: IPv4 address mask
 * @valid: valid flag
 * @list: list काष्ठाure, used पूर्णांकernally
 */
काष्ठा netlbl_af4list अणु
	__be32 addr;
	__be32 mask;

	u32 valid;
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा netlbl_af6list - NetLabel IPv6 address list
 * @addr: IPv6 address
 * @mask: IPv6 address mask
 * @valid: valid flag
 * @list: list काष्ठाure, used पूर्णांकernally
 */
काष्ठा netlbl_af6list अणु
	काष्ठा in6_addr addr;
	काष्ठा in6_addr mask;

	u32 valid;
	काष्ठा list_head list;
पूर्ण;

#घोषणा __af4list_entry(ptr) container_of(ptr, काष्ठा netlbl_af4list, list)

अटल अंतरभूत काष्ठा netlbl_af4list *__af4list_valid(काष्ठा list_head *s,
						     काष्ठा list_head *h)
अणु
	काष्ठा list_head *i = s;
	काष्ठा netlbl_af4list *n = __af4list_entry(s);
	जबतक (i != h && !n->valid) अणु
		i = i->next;
		n = __af4list_entry(i);
	पूर्ण
	वापस n;
पूर्ण

अटल अंतरभूत काष्ठा netlbl_af4list *__af4list_valid_rcu(काष्ठा list_head *s,
							 काष्ठा list_head *h)
अणु
	काष्ठा list_head *i = s;
	काष्ठा netlbl_af4list *n = __af4list_entry(s);
	जबतक (i != h && !n->valid) अणु
		i = rcu_dereference(list_next_rcu(i));
		n = __af4list_entry(i);
	पूर्ण
	वापस n;
पूर्ण

#घोषणा netlbl_af4list_क्रमeach(iter, head)				\
	क्रम (iter = __af4list_valid((head)->next, head);		\
	     &iter->list != (head);					\
	     iter = __af4list_valid(iter->list.next, head))

#घोषणा netlbl_af4list_क्रमeach_rcu(iter, head)				\
	क्रम (iter = __af4list_valid_rcu((head)->next, head);		\
	     &iter->list != (head);					\
	     iter = __af4list_valid_rcu(iter->list.next, head))

#घोषणा netlbl_af4list_क्रमeach_safe(iter, पंचांगp, head)			\
	क्रम (iter = __af4list_valid((head)->next, head),		\
		     पंचांगp = __af4list_valid(iter->list.next, head);	\
	     &iter->list != (head);					\
	     iter = पंचांगp, पंचांगp = __af4list_valid(iter->list.next, head))

पूर्णांक netlbl_af4list_add(काष्ठा netlbl_af4list *entry,
		       काष्ठा list_head *head);
काष्ठा netlbl_af4list *netlbl_af4list_हटाओ(__be32 addr, __be32 mask,
					     काष्ठा list_head *head);
व्योम netlbl_af4list_हटाओ_entry(काष्ठा netlbl_af4list *entry);
काष्ठा netlbl_af4list *netlbl_af4list_search(__be32 addr,
					     काष्ठा list_head *head);
काष्ठा netlbl_af4list *netlbl_af4list_search_exact(__be32 addr,
						   __be32 mask,
						   काष्ठा list_head *head);

#अगर_घोषित CONFIG_AUDIT
व्योम netlbl_af4list_audit_addr(काष्ठा audit_buffer *audit_buf,
			       पूर्णांक src, स्थिर अक्षर *dev,
			       __be32 addr, __be32 mask);
#अन्यथा
अटल अंतरभूत व्योम netlbl_af4list_audit_addr(काष्ठा audit_buffer *audit_buf,
					     पूर्णांक src, स्थिर अक्षर *dev,
					     __be32 addr, __be32 mask)
अणु
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)

#घोषणा __af6list_entry(ptr) container_of(ptr, काष्ठा netlbl_af6list, list)

अटल अंतरभूत काष्ठा netlbl_af6list *__af6list_valid(काष्ठा list_head *s,
						     काष्ठा list_head *h)
अणु
	काष्ठा list_head *i = s;
	काष्ठा netlbl_af6list *n = __af6list_entry(s);
	जबतक (i != h && !n->valid) अणु
		i = i->next;
		n = __af6list_entry(i);
	पूर्ण
	वापस n;
पूर्ण

अटल अंतरभूत काष्ठा netlbl_af6list *__af6list_valid_rcu(काष्ठा list_head *s,
							 काष्ठा list_head *h)
अणु
	काष्ठा list_head *i = s;
	काष्ठा netlbl_af6list *n = __af6list_entry(s);
	जबतक (i != h && !n->valid) अणु
		i = rcu_dereference(list_next_rcu(i));
		n = __af6list_entry(i);
	पूर्ण
	वापस n;
पूर्ण

#घोषणा netlbl_af6list_क्रमeach(iter, head)				\
	क्रम (iter = __af6list_valid((head)->next, head);		\
	     &iter->list != (head);					\
	     iter = __af6list_valid(iter->list.next, head))

#घोषणा netlbl_af6list_क्रमeach_rcu(iter, head)				\
	क्रम (iter = __af6list_valid_rcu((head)->next, head);		\
	     &iter->list != (head);					\
	     iter = __af6list_valid_rcu(iter->list.next, head))

#घोषणा netlbl_af6list_क्रमeach_safe(iter, पंचांगp, head)			\
	क्रम (iter = __af6list_valid((head)->next, head),		\
		     पंचांगp = __af6list_valid(iter->list.next, head);	\
	     &iter->list != (head);					\
	     iter = पंचांगp, पंचांगp = __af6list_valid(iter->list.next, head))

पूर्णांक netlbl_af6list_add(काष्ठा netlbl_af6list *entry,
		       काष्ठा list_head *head);
काष्ठा netlbl_af6list *netlbl_af6list_हटाओ(स्थिर काष्ठा in6_addr *addr,
					     स्थिर काष्ठा in6_addr *mask,
					     काष्ठा list_head *head);
व्योम netlbl_af6list_हटाओ_entry(काष्ठा netlbl_af6list *entry);
काष्ठा netlbl_af6list *netlbl_af6list_search(स्थिर काष्ठा in6_addr *addr,
					     काष्ठा list_head *head);
काष्ठा netlbl_af6list *netlbl_af6list_search_exact(स्थिर काष्ठा in6_addr *addr,
						   स्थिर काष्ठा in6_addr *mask,
						   काष्ठा list_head *head);

#अगर_घोषित CONFIG_AUDIT
व्योम netlbl_af6list_audit_addr(काष्ठा audit_buffer *audit_buf,
			       पूर्णांक src,
			       स्थिर अक्षर *dev,
			       स्थिर काष्ठा in6_addr *addr,
			       स्थिर काष्ठा in6_addr *mask);
#अन्यथा
अटल अंतरभूत व्योम netlbl_af6list_audit_addr(काष्ठा audit_buffer *audit_buf,
					     पूर्णांक src,
					     स्थिर अक्षर *dev,
					     स्थिर काष्ठा in6_addr *addr,
					     स्थिर काष्ठा in6_addr *mask)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* IPV6 */

#पूर्ण_अगर
