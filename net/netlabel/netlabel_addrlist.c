<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
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

#समावेश <linux/types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <linux/audit.h>

#समावेश "netlabel_addrlist.h"

/*
 * Address List Functions
 */

/**
 * netlbl_af4list_search - Search क्रम a matching IPv4 address entry
 * @addr: IPv4 address
 * @head: the list head
 *
 * Description:
 * Searches the IPv4 address list given by @head.  If a matching address entry
 * is found it is वापसed, otherwise शून्य is वापसed.  The caller is
 * responsible क्रम calling the rcu_पढ़ो_[un]lock() functions.
 *
 */
काष्ठा netlbl_af4list *netlbl_af4list_search(__be32 addr,
					     काष्ठा list_head *head)
अणु
	काष्ठा netlbl_af4list *iter;

	list_क्रम_each_entry_rcu(iter, head, list)
		अगर (iter->valid && (addr & iter->mask) == iter->addr)
			वापस iter;

	वापस शून्य;
पूर्ण

/**
 * netlbl_af4list_search_exact - Search क्रम an exact IPv4 address entry
 * @addr: IPv4 address
 * @mask: IPv4 address mask
 * @head: the list head
 *
 * Description:
 * Searches the IPv4 address list given by @head.  If an exact match अगर found
 * it is वापसed, otherwise शून्य is वापसed.  The caller is responsible क्रम
 * calling the rcu_पढ़ो_[un]lock() functions.
 *
 */
काष्ठा netlbl_af4list *netlbl_af4list_search_exact(__be32 addr,
						   __be32 mask,
						   काष्ठा list_head *head)
अणु
	काष्ठा netlbl_af4list *iter;

	list_क्रम_each_entry_rcu(iter, head, list)
		अगर (iter->valid && iter->addr == addr && iter->mask == mask)
			वापस iter;

	वापस शून्य;
पूर्ण


#अगर IS_ENABLED(CONFIG_IPV6)
/**
 * netlbl_af6list_search - Search क्रम a matching IPv6 address entry
 * @addr: IPv6 address
 * @head: the list head
 *
 * Description:
 * Searches the IPv6 address list given by @head.  If a matching address entry
 * is found it is वापसed, otherwise शून्य is वापसed.  The caller is
 * responsible क्रम calling the rcu_पढ़ो_[un]lock() functions.
 *
 */
काष्ठा netlbl_af6list *netlbl_af6list_search(स्थिर काष्ठा in6_addr *addr,
					     काष्ठा list_head *head)
अणु
	काष्ठा netlbl_af6list *iter;

	list_क्रम_each_entry_rcu(iter, head, list)
		अगर (iter->valid &&
		    ipv6_masked_addr_cmp(&iter->addr, &iter->mask, addr) == 0)
			वापस iter;

	वापस शून्य;
पूर्ण

/**
 * netlbl_af6list_search_exact - Search क्रम an exact IPv6 address entry
 * @addr: IPv6 address
 * @mask: IPv6 address mask
 * @head: the list head
 *
 * Description:
 * Searches the IPv6 address list given by @head.  If an exact match अगर found
 * it is वापसed, otherwise शून्य is वापसed.  The caller is responsible क्रम
 * calling the rcu_पढ़ो_[un]lock() functions.
 *
 */
काष्ठा netlbl_af6list *netlbl_af6list_search_exact(स्थिर काष्ठा in6_addr *addr,
						   स्थिर काष्ठा in6_addr *mask,
						   काष्ठा list_head *head)
अणु
	काष्ठा netlbl_af6list *iter;

	list_क्रम_each_entry_rcu(iter, head, list)
		अगर (iter->valid &&
		    ipv6_addr_equal(&iter->addr, addr) &&
		    ipv6_addr_equal(&iter->mask, mask))
			वापस iter;

	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* IPv6 */

/**
 * netlbl_af4list_add - Add a new IPv4 address entry to a list
 * @entry: address entry
 * @head: the list head
 *
 * Description:
 * Add a new address entry to the list poपूर्णांकed to by @head.  On success zero is
 * वापसed, otherwise a negative value is वापसed.  The caller is responsible
 * क्रम calling the necessary locking functions.
 *
 */
पूर्णांक netlbl_af4list_add(काष्ठा netlbl_af4list *entry, काष्ठा list_head *head)
अणु
	काष्ठा netlbl_af4list *iter;

	iter = netlbl_af4list_search(entry->addr, head);
	अगर (iter != शून्य &&
	    iter->addr == entry->addr && iter->mask == entry->mask)
		वापस -EEXIST;

	/* in order to speed up address searches through the list (the common
	 * हाल) we need to keep the list in order based on the size of the
	 * address mask such that the entry with the widest mask (smallest
	 * numerical value) appears first in the list */
	list_क्रम_each_entry_rcu(iter, head, list)
		अगर (iter->valid &&
		    ntohl(entry->mask) > ntohl(iter->mask)) अणु
			__list_add_rcu(&entry->list,
				       iter->list.prev,
				       &iter->list);
			वापस 0;
		पूर्ण
	list_add_tail_rcu(&entry->list, head);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/**
 * netlbl_af6list_add - Add a new IPv6 address entry to a list
 * @entry: address entry
 * @head: the list head
 *
 * Description:
 * Add a new address entry to the list poपूर्णांकed to by @head.  On success zero is
 * वापसed, otherwise a negative value is वापसed.  The caller is responsible
 * क्रम calling the necessary locking functions.
 *
 */
पूर्णांक netlbl_af6list_add(काष्ठा netlbl_af6list *entry, काष्ठा list_head *head)
अणु
	काष्ठा netlbl_af6list *iter;

	iter = netlbl_af6list_search(&entry->addr, head);
	अगर (iter != शून्य &&
	    ipv6_addr_equal(&iter->addr, &entry->addr) &&
	    ipv6_addr_equal(&iter->mask, &entry->mask))
		वापस -EEXIST;

	/* in order to speed up address searches through the list (the common
	 * हाल) we need to keep the list in order based on the size of the
	 * address mask such that the entry with the widest mask (smallest
	 * numerical value) appears first in the list */
	list_क्रम_each_entry_rcu(iter, head, list)
		अगर (iter->valid &&
		    ipv6_addr_cmp(&entry->mask, &iter->mask) > 0) अणु
			__list_add_rcu(&entry->list,
				       iter->list.prev,
				       &iter->list);
			वापस 0;
		पूर्ण
	list_add_tail_rcu(&entry->list, head);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* IPv6 */

/**
 * netlbl_af4list_हटाओ_entry - Remove an IPv4 address entry
 * @entry: address entry
 *
 * Description:
 * Remove the specअगरied IP address entry.  The caller is responsible क्रम
 * calling the necessary locking functions.
 *
 */
व्योम netlbl_af4list_हटाओ_entry(काष्ठा netlbl_af4list *entry)
अणु
	entry->valid = 0;
	list_del_rcu(&entry->list);
पूर्ण

/**
 * netlbl_af4list_हटाओ - Remove an IPv4 address entry
 * @addr: IP address
 * @mask: IP address mask
 * @head: the list head
 *
 * Description:
 * Remove an IP address entry from the list poपूर्णांकed to by @head.  Returns the
 * entry on success, शून्य on failure.  The caller is responsible क्रम calling
 * the necessary locking functions.
 *
 */
काष्ठा netlbl_af4list *netlbl_af4list_हटाओ(__be32 addr, __be32 mask,
					     काष्ठा list_head *head)
अणु
	काष्ठा netlbl_af4list *entry;

	entry = netlbl_af4list_search_exact(addr, mask, head);
	अगर (entry == शून्य)
		वापस शून्य;
	netlbl_af4list_हटाओ_entry(entry);
	वापस entry;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/**
 * netlbl_af6list_हटाओ_entry - Remove an IPv6 address entry
 * @entry: address entry
 *
 * Description:
 * Remove the specअगरied IP address entry.  The caller is responsible क्रम
 * calling the necessary locking functions.
 *
 */
व्योम netlbl_af6list_हटाओ_entry(काष्ठा netlbl_af6list *entry)
अणु
	entry->valid = 0;
	list_del_rcu(&entry->list);
पूर्ण

/**
 * netlbl_af6list_हटाओ - Remove an IPv6 address entry
 * @addr: IP address
 * @mask: IP address mask
 * @head: the list head
 *
 * Description:
 * Remove an IP address entry from the list poपूर्णांकed to by @head.  Returns the
 * entry on success, शून्य on failure.  The caller is responsible क्रम calling
 * the necessary locking functions.
 *
 */
काष्ठा netlbl_af6list *netlbl_af6list_हटाओ(स्थिर काष्ठा in6_addr *addr,
					     स्थिर काष्ठा in6_addr *mask,
					     काष्ठा list_head *head)
अणु
	काष्ठा netlbl_af6list *entry;

	entry = netlbl_af6list_search_exact(addr, mask, head);
	अगर (entry == शून्य)
		वापस शून्य;
	netlbl_af6list_हटाओ_entry(entry);
	वापस entry;
पूर्ण
#पूर्ण_अगर /* IPv6 */

/*
 * Audit Helper Functions
 */

#अगर_घोषित CONFIG_AUDIT
/**
 * netlbl_af4list_audit_addr - Audit an IPv4 address
 * @audit_buf: audit buffer
 * @src: true अगर source address, false अगर destination
 * @dev: network पूर्णांकerface
 * @addr: IP address
 * @mask: IP address mask
 *
 * Description:
 * Write the IPv4 address and address mask, अगर necessary, to @audit_buf.
 *
 */
व्योम netlbl_af4list_audit_addr(काष्ठा audit_buffer *audit_buf,
					पूर्णांक src, स्थिर अक्षर *dev,
					__be32 addr, __be32 mask)
अणु
	u32 mask_val = ntohl(mask);
	अक्षर *dir = (src ? "src" : "dst");

	अगर (dev != शून्य)
		audit_log_क्रमmat(audit_buf, " netif=%s", dev);
	audit_log_क्रमmat(audit_buf, " %s=%pI4", dir, &addr);
	अगर (mask_val != 0xffffffff) अणु
		u32 mask_len = 0;
		जबतक (mask_val > 0) अणु
			mask_val <<= 1;
			mask_len++;
		पूर्ण
		audit_log_क्रमmat(audit_buf, " %s_prefixlen=%d", dir, mask_len);
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/**
 * netlbl_af6list_audit_addr - Audit an IPv6 address
 * @audit_buf: audit buffer
 * @src: true अगर source address, false अगर destination
 * @dev: network पूर्णांकerface
 * @addr: IP address
 * @mask: IP address mask
 *
 * Description:
 * Write the IPv6 address and address mask, अगर necessary, to @audit_buf.
 *
 */
व्योम netlbl_af6list_audit_addr(काष्ठा audit_buffer *audit_buf,
				 पूर्णांक src,
				 स्थिर अक्षर *dev,
				 स्थिर काष्ठा in6_addr *addr,
				 स्थिर काष्ठा in6_addr *mask)
अणु
	अक्षर *dir = (src ? "src" : "dst");

	अगर (dev != शून्य)
		audit_log_क्रमmat(audit_buf, " netif=%s", dev);
	audit_log_क्रमmat(audit_buf, " %s=%pI6", dir, addr);
	अगर (ntohl(mask->s6_addr32[3]) != 0xffffffff) अणु
		u32 mask_len = 0;
		u32 mask_val;
		पूर्णांक iter = -1;
		जबतक (ntohl(mask->s6_addr32[++iter]) == 0xffffffff)
			mask_len += 32;
		mask_val = ntohl(mask->s6_addr32[iter]);
		जबतक (mask_val > 0) अणु
			mask_val <<= 1;
			mask_len++;
		पूर्ण
		audit_log_क्रमmat(audit_buf, " %s_prefixlen=%d", dir, mask_len);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* IPv6 */
#पूर्ण_अगर /* CONFIG_AUDIT */
