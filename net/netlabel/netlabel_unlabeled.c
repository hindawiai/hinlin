<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NetLabel Unlabeled Support
 *
 * This file defines functions क्रम dealing with unlabeled packets क्रम the
 * NetLabel प्रणाली.  The NetLabel प्रणाली manages अटल and dynamic label
 * mappings क्रम network protocols such as CIPSO and RIPSO.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006 - 2008
 */

#समावेश <linux/types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/socket.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/audit.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/security.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netlabel.h>
#समावेश <यंत्र/bug.h>
#समावेश <linux/atomic.h>

#समावेश "netlabel_user.h"
#समावेश "netlabel_addrlist.h"
#समावेश "netlabel_domainhash.h"
#समावेश "netlabel_unlabeled.h"
#समावेश "netlabel_mgmt.h"

/* NOTE: at present we always use init's network namespace since we don't
 *       presently support dअगरferent namespaces even though the majority of
 *       the functions in this file are "namespace safe" */

/* The unlabeled connection hash table which we use to map network पूर्णांकerfaces
 * and addresses of unlabeled packets to a user specअगरied secid value क्रम the
 * LSM.  The hash table is used to lookup the network पूर्णांकerface entry
 * (काष्ठा netlbl_unlhsh_अगरace) and then the पूर्णांकerface entry is used to
 * lookup an IP address match from an ordered list.  If a network पूर्णांकerface
 * match can not be found in the hash table then the शेष entry
 * (netlbl_unlhsh_def) is used.  The IP address entry list
 * (काष्ठा netlbl_unlhsh_addr) is ordered such that the entries with a
 * larger neपंचांगask come first.
 */
काष्ठा netlbl_unlhsh_tbl अणु
	काष्ठा list_head *tbl;
	u32 size;
पूर्ण;
#घोषणा netlbl_unlhsh_addr4_entry(iter) \
	container_of(iter, काष्ठा netlbl_unlhsh_addr4, list)
काष्ठा netlbl_unlhsh_addr4 अणु
	u32 secid;

	काष्ठा netlbl_af4list list;
	काष्ठा rcu_head rcu;
पूर्ण;
#घोषणा netlbl_unlhsh_addr6_entry(iter) \
	container_of(iter, काष्ठा netlbl_unlhsh_addr6, list)
काष्ठा netlbl_unlhsh_addr6 अणु
	u32 secid;

	काष्ठा netlbl_af6list list;
	काष्ठा rcu_head rcu;
पूर्ण;
काष्ठा netlbl_unlhsh_अगरace अणु
	पूर्णांक अगरindex;
	काष्ठा list_head addr4_list;
	काष्ठा list_head addr6_list;

	u32 valid;
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
पूर्ण;

/* Argument काष्ठा क्रम netlbl_unlhsh_walk() */
काष्ठा netlbl_unlhsh_walk_arg अणु
	काष्ठा netlink_callback *nl_cb;
	काष्ठा sk_buff *skb;
	u32 seq;
पूर्ण;

/* Unlabeled connection hash table */
/* updates should be so rare that having one spinlock क्रम the entire
 * hash table should be okay */
अटल DEFINE_SPINLOCK(netlbl_unlhsh_lock);
#घोषणा netlbl_unlhsh_rcu_deref(p) \
	rcu_dereference_check(p, lockdep_is_held(&netlbl_unlhsh_lock))
अटल काष्ठा netlbl_unlhsh_tbl __rcu *netlbl_unlhsh;
अटल काष्ठा netlbl_unlhsh_अगरace __rcu *netlbl_unlhsh_def;

/* Accept unlabeled packets flag */
अटल u8 netlabel_unlabel_acceptflg;

/* NetLabel Generic NETLINK unlabeled family */
अटल काष्ठा genl_family netlbl_unlabel_gnl_family;

/* NetLabel Netlink attribute policy */
अटल स्थिर काष्ठा nla_policy netlbl_unlabel_genl_policy[NLBL_UNLABEL_A_MAX + 1] = अणु
	[NLBL_UNLABEL_A_ACPTFLG] = अणु .type = NLA_U8 पूर्ण,
	[NLBL_UNLABEL_A_IPV6ADDR] = अणु .type = NLA_BINARY,
				      .len = माप(काष्ठा in6_addr) पूर्ण,
	[NLBL_UNLABEL_A_IPV6MASK] = अणु .type = NLA_BINARY,
				      .len = माप(काष्ठा in6_addr) पूर्ण,
	[NLBL_UNLABEL_A_IPV4ADDR] = अणु .type = NLA_BINARY,
				      .len = माप(काष्ठा in_addr) पूर्ण,
	[NLBL_UNLABEL_A_IPV4MASK] = अणु .type = NLA_BINARY,
				      .len = माप(काष्ठा in_addr) पूर्ण,
	[NLBL_UNLABEL_A_IFACE] = अणु .type = NLA_NUL_STRING,
				   .len = IFNAMSIZ - 1 पूर्ण,
	[NLBL_UNLABEL_A_SECCTX] = अणु .type = NLA_BINARY पूर्ण
पूर्ण;

/*
 * Unlabeled Connection Hash Table Functions
 */

/**
 * netlbl_unlhsh_मुक्त_अगरace - Frees an पूर्णांकerface entry from the hash table
 * @entry: the entry's RCU field
 *
 * Description:
 * This function is deचिन्हित to be used as a callback to the call_rcu()
 * function so that memory allocated to a hash table पूर्णांकerface entry can be
 * released safely.  It is important to note that this function करोes not मुक्त
 * the IPv4 and IPv6 address lists contained as part of an पूर्णांकerface entry.  It
 * is up to the rest of the code to make sure an पूर्णांकerface entry is only मुक्तd
 * once it's address lists are empty.
 *
 */
अटल व्योम netlbl_unlhsh_मुक्त_अगरace(काष्ठा rcu_head *entry)
अणु
	काष्ठा netlbl_unlhsh_अगरace *अगरace;
	काष्ठा netlbl_af4list *iter4;
	काष्ठा netlbl_af4list *पंचांगp4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा netlbl_af6list *iter6;
	काष्ठा netlbl_af6list *पंचांगp6;
#पूर्ण_अगर /* IPv6 */

	अगरace = container_of(entry, काष्ठा netlbl_unlhsh_अगरace, rcu);

	/* no need क्रम locks here since we are the only one with access to this
	 * काष्ठाure */

	netlbl_af4list_क्रमeach_safe(iter4, पंचांगp4, &अगरace->addr4_list) अणु
		netlbl_af4list_हटाओ_entry(iter4);
		kमुक्त(netlbl_unlhsh_addr4_entry(iter4));
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	netlbl_af6list_क्रमeach_safe(iter6, पंचांगp6, &अगरace->addr6_list) अणु
		netlbl_af6list_हटाओ_entry(iter6);
		kमुक्त(netlbl_unlhsh_addr6_entry(iter6));
	पूर्ण
#पूर्ण_अगर /* IPv6 */
	kमुक्त(अगरace);
पूर्ण

/**
 * netlbl_unlhsh_hash - Hashing function क्रम the hash table
 * @अगरindex: the network पूर्णांकerface/device to hash
 *
 * Description:
 * This is the hashing function क्रम the unlabeled hash table, it वापसs the
 * bucket number क्रम the given device/पूर्णांकerface.  The caller is responsible क्रम
 * ensuring that the hash table is रक्षित with either a RCU पढ़ो lock or
 * the hash table lock.
 *
 */
अटल u32 netlbl_unlhsh_hash(पूर्णांक अगरindex)
अणु
	वापस अगरindex & (netlbl_unlhsh_rcu_deref(netlbl_unlhsh)->size - 1);
पूर्ण

/**
 * netlbl_unlhsh_search_अगरace - Search क्रम a matching पूर्णांकerface entry
 * @अगरindex: the network पूर्णांकerface
 *
 * Description:
 * Searches the unlabeled connection hash table and वापसs a poपूर्णांकer to the
 * पूर्णांकerface entry which matches @अगरindex, otherwise शून्य is वापसed.  The
 * caller is responsible क्रम ensuring that the hash table is रक्षित with
 * either a RCU पढ़ो lock or the hash table lock.
 *
 */
अटल काष्ठा netlbl_unlhsh_अगरace *netlbl_unlhsh_search_अगरace(पूर्णांक अगरindex)
अणु
	u32 bkt;
	काष्ठा list_head *bkt_list;
	काष्ठा netlbl_unlhsh_अगरace *iter;

	bkt = netlbl_unlhsh_hash(अगरindex);
	bkt_list = &netlbl_unlhsh_rcu_deref(netlbl_unlhsh)->tbl[bkt];
	list_क्रम_each_entry_rcu(iter, bkt_list, list,
				lockdep_is_held(&netlbl_unlhsh_lock))
		अगर (iter->valid && iter->अगरindex == अगरindex)
			वापस iter;

	वापस शून्य;
पूर्ण

/**
 * netlbl_unlhsh_add_addr4 - Add a new IPv4 address entry to the hash table
 * @अगरace: the associated पूर्णांकerface entry
 * @addr: IPv4 address in network byte order
 * @mask: IPv4 address mask in network byte order
 * @secid: LSM secid value क्रम entry
 *
 * Description:
 * Add a new address entry पूर्णांकo the unlabeled connection hash table using the
 * पूर्णांकerface entry specअगरied by @अगरace.  On success zero is वापसed, otherwise
 * a negative value is वापसed.
 *
 */
अटल पूर्णांक netlbl_unlhsh_add_addr4(काष्ठा netlbl_unlhsh_अगरace *अगरace,
				   स्थिर काष्ठा in_addr *addr,
				   स्थिर काष्ठा in_addr *mask,
				   u32 secid)
अणु
	पूर्णांक ret_val;
	काष्ठा netlbl_unlhsh_addr4 *entry;

	entry = kzalloc(माप(*entry), GFP_ATOMIC);
	अगर (entry == शून्य)
		वापस -ENOMEM;

	entry->list.addr = addr->s_addr & mask->s_addr;
	entry->list.mask = mask->s_addr;
	entry->list.valid = 1;
	entry->secid = secid;

	spin_lock(&netlbl_unlhsh_lock);
	ret_val = netlbl_af4list_add(&entry->list, &अगरace->addr4_list);
	spin_unlock(&netlbl_unlhsh_lock);

	अगर (ret_val != 0)
		kमुक्त(entry);
	वापस ret_val;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/**
 * netlbl_unlhsh_add_addr6 - Add a new IPv6 address entry to the hash table
 * @अगरace: the associated पूर्णांकerface entry
 * @addr: IPv6 address in network byte order
 * @mask: IPv6 address mask in network byte order
 * @secid: LSM secid value क्रम entry
 *
 * Description:
 * Add a new address entry पूर्णांकo the unlabeled connection hash table using the
 * पूर्णांकerface entry specअगरied by @अगरace.  On success zero is वापसed, otherwise
 * a negative value is वापसed.
 *
 */
अटल पूर्णांक netlbl_unlhsh_add_addr6(काष्ठा netlbl_unlhsh_अगरace *अगरace,
				   स्थिर काष्ठा in6_addr *addr,
				   स्थिर काष्ठा in6_addr *mask,
				   u32 secid)
अणु
	पूर्णांक ret_val;
	काष्ठा netlbl_unlhsh_addr6 *entry;

	entry = kzalloc(माप(*entry), GFP_ATOMIC);
	अगर (entry == शून्य)
		वापस -ENOMEM;

	entry->list.addr = *addr;
	entry->list.addr.s6_addr32[0] &= mask->s6_addr32[0];
	entry->list.addr.s6_addr32[1] &= mask->s6_addr32[1];
	entry->list.addr.s6_addr32[2] &= mask->s6_addr32[2];
	entry->list.addr.s6_addr32[3] &= mask->s6_addr32[3];
	entry->list.mask = *mask;
	entry->list.valid = 1;
	entry->secid = secid;

	spin_lock(&netlbl_unlhsh_lock);
	ret_val = netlbl_af6list_add(&entry->list, &अगरace->addr6_list);
	spin_unlock(&netlbl_unlhsh_lock);

	अगर (ret_val != 0)
		kमुक्त(entry);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* IPv6 */

/**
 * netlbl_unlhsh_add_अगरace - Adds a new पूर्णांकerface entry to the hash table
 * @अगरindex: network पूर्णांकerface
 *
 * Description:
 * Add a new, empty, पूर्णांकerface entry पूर्णांकo the unlabeled connection hash table.
 * On success a poपूर्णांकer to the new पूर्णांकerface entry is वापसed, on failure शून्य
 * is वापसed.
 *
 */
अटल काष्ठा netlbl_unlhsh_अगरace *netlbl_unlhsh_add_अगरace(पूर्णांक अगरindex)
अणु
	u32 bkt;
	काष्ठा netlbl_unlhsh_अगरace *अगरace;

	अगरace = kzalloc(माप(*अगरace), GFP_ATOMIC);
	अगर (अगरace == शून्य)
		वापस शून्य;

	अगरace->अगरindex = अगरindex;
	INIT_LIST_HEAD(&अगरace->addr4_list);
	INIT_LIST_HEAD(&अगरace->addr6_list);
	अगरace->valid = 1;

	spin_lock(&netlbl_unlhsh_lock);
	अगर (अगरindex > 0) अणु
		bkt = netlbl_unlhsh_hash(अगरindex);
		अगर (netlbl_unlhsh_search_अगरace(अगरindex) != शून्य)
			जाओ add_अगरace_failure;
		list_add_tail_rcu(&अगरace->list,
			     &netlbl_unlhsh_rcu_deref(netlbl_unlhsh)->tbl[bkt]);
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&अगरace->list);
		अगर (netlbl_unlhsh_rcu_deref(netlbl_unlhsh_def) != शून्य)
			जाओ add_अगरace_failure;
		rcu_assign_poपूर्णांकer(netlbl_unlhsh_def, अगरace);
	पूर्ण
	spin_unlock(&netlbl_unlhsh_lock);

	वापस अगरace;

add_अगरace_failure:
	spin_unlock(&netlbl_unlhsh_lock);
	kमुक्त(अगरace);
	वापस शून्य;
पूर्ण

/**
 * netlbl_unlhsh_add - Adds a new entry to the unlabeled connection hash table
 * @net: network namespace
 * @dev_name: पूर्णांकerface name
 * @addr: IP address in network byte order
 * @mask: address mask in network byte order
 * @addr_len: length of address/mask (4 क्रम IPv4, 16 क्रम IPv6)
 * @secid: LSM secid value क्रम the entry
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Adds a new entry to the unlabeled connection hash table.  Returns zero on
 * success, negative values on failure.
 *
 */
पूर्णांक netlbl_unlhsh_add(काष्ठा net *net,
		      स्थिर अक्षर *dev_name,
		      स्थिर व्योम *addr,
		      स्थिर व्योम *mask,
		      u32 addr_len,
		      u32 secid,
		      काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val;
	पूर्णांक अगरindex;
	काष्ठा net_device *dev;
	काष्ठा netlbl_unlhsh_अगरace *अगरace;
	काष्ठा audit_buffer *audit_buf = शून्य;
	अक्षर *secctx = शून्य;
	u32 secctx_len;

	अगर (addr_len != माप(काष्ठा in_addr) &&
	    addr_len != माप(काष्ठा in6_addr))
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	अगर (dev_name != शून्य) अणु
		dev = dev_get_by_name_rcu(net, dev_name);
		अगर (dev == शून्य) अणु
			ret_val = -ENODEV;
			जाओ unlhsh_add_वापस;
		पूर्ण
		अगरindex = dev->अगरindex;
		अगरace = netlbl_unlhsh_search_अगरace(अगरindex);
	पूर्ण अन्यथा अणु
		अगरindex = 0;
		अगरace = rcu_dereference(netlbl_unlhsh_def);
	पूर्ण
	अगर (अगरace == शून्य) अणु
		अगरace = netlbl_unlhsh_add_अगरace(अगरindex);
		अगर (अगरace == शून्य) अणु
			ret_val = -ENOMEM;
			जाओ unlhsh_add_वापस;
		पूर्ण
	पूर्ण
	audit_buf = netlbl_audit_start_common(AUDIT_MAC_UNLBL_STCADD,
					      audit_info);
	चयन (addr_len) अणु
	हाल माप(काष्ठा in_addr): अणु
		स्थिर काष्ठा in_addr *addr4 = addr;
		स्थिर काष्ठा in_addr *mask4 = mask;

		ret_val = netlbl_unlhsh_add_addr4(अगरace, addr4, mask4, secid);
		अगर (audit_buf != शून्य)
			netlbl_af4list_audit_addr(audit_buf, 1,
						  dev_name,
						  addr4->s_addr,
						  mask4->s_addr);
		अवरोध;
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल माप(काष्ठा in6_addr): अणु
		स्थिर काष्ठा in6_addr *addr6 = addr;
		स्थिर काष्ठा in6_addr *mask6 = mask;

		ret_val = netlbl_unlhsh_add_addr6(अगरace, addr6, mask6, secid);
		अगर (audit_buf != शून्य)
			netlbl_af6list_audit_addr(audit_buf, 1,
						  dev_name,
						  addr6, mask6);
		अवरोध;
	पूर्ण
#पूर्ण_अगर /* IPv6 */
	शेष:
		ret_val = -EINVAL;
	पूर्ण
	अगर (ret_val == 0)
		atomic_inc(&netlabel_mgmt_protocount);

unlhsh_add_वापस:
	rcu_पढ़ो_unlock();
	अगर (audit_buf != शून्य) अणु
		अगर (security_secid_to_secctx(secid,
					     &secctx,
					     &secctx_len) == 0) अणु
			audit_log_क्रमmat(audit_buf, " sec_obj=%s", secctx);
			security_release_secctx(secctx, secctx_len);
		पूर्ण
		audit_log_क्रमmat(audit_buf, " res=%u", ret_val == 0 ? 1 : 0);
		audit_log_end(audit_buf);
	पूर्ण
	वापस ret_val;
पूर्ण

/**
 * netlbl_unlhsh_हटाओ_addr4 - Remove an IPv4 address entry
 * @net: network namespace
 * @अगरace: पूर्णांकerface entry
 * @addr: IP address
 * @mask: IP address mask
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Remove an IP address entry from the unlabeled connection hash table.
 * Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_unlhsh_हटाओ_addr4(काष्ठा net *net,
				      काष्ठा netlbl_unlhsh_अगरace *अगरace,
				      स्थिर काष्ठा in_addr *addr,
				      स्थिर काष्ठा in_addr *mask,
				      काष्ठा netlbl_audit *audit_info)
अणु
	काष्ठा netlbl_af4list *list_entry;
	काष्ठा netlbl_unlhsh_addr4 *entry;
	काष्ठा audit_buffer *audit_buf;
	काष्ठा net_device *dev;
	अक्षर *secctx;
	u32 secctx_len;

	spin_lock(&netlbl_unlhsh_lock);
	list_entry = netlbl_af4list_हटाओ(addr->s_addr, mask->s_addr,
					   &अगरace->addr4_list);
	spin_unlock(&netlbl_unlhsh_lock);
	अगर (list_entry != शून्य)
		entry = netlbl_unlhsh_addr4_entry(list_entry);
	अन्यथा
		entry = शून्य;

	audit_buf = netlbl_audit_start_common(AUDIT_MAC_UNLBL_STCDEL,
					      audit_info);
	अगर (audit_buf != शून्य) अणु
		dev = dev_get_by_index(net, अगरace->अगरindex);
		netlbl_af4list_audit_addr(audit_buf, 1,
					  (dev != शून्य ? dev->name : शून्य),
					  addr->s_addr, mask->s_addr);
		अगर (dev != शून्य)
			dev_put(dev);
		अगर (entry != शून्य &&
		    security_secid_to_secctx(entry->secid,
					     &secctx, &secctx_len) == 0) अणु
			audit_log_क्रमmat(audit_buf, " sec_obj=%s", secctx);
			security_release_secctx(secctx, secctx_len);
		पूर्ण
		audit_log_क्रमmat(audit_buf, " res=%u", entry != शून्य ? 1 : 0);
		audit_log_end(audit_buf);
	पूर्ण

	अगर (entry == शून्य)
		वापस -ENOENT;

	kमुक्त_rcu(entry, rcu);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/**
 * netlbl_unlhsh_हटाओ_addr6 - Remove an IPv6 address entry
 * @net: network namespace
 * @अगरace: पूर्णांकerface entry
 * @addr: IP address
 * @mask: IP address mask
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Remove an IP address entry from the unlabeled connection hash table.
 * Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_unlhsh_हटाओ_addr6(काष्ठा net *net,
				      काष्ठा netlbl_unlhsh_अगरace *अगरace,
				      स्थिर काष्ठा in6_addr *addr,
				      स्थिर काष्ठा in6_addr *mask,
				      काष्ठा netlbl_audit *audit_info)
अणु
	काष्ठा netlbl_af6list *list_entry;
	काष्ठा netlbl_unlhsh_addr6 *entry;
	काष्ठा audit_buffer *audit_buf;
	काष्ठा net_device *dev;
	अक्षर *secctx;
	u32 secctx_len;

	spin_lock(&netlbl_unlhsh_lock);
	list_entry = netlbl_af6list_हटाओ(addr, mask, &अगरace->addr6_list);
	spin_unlock(&netlbl_unlhsh_lock);
	अगर (list_entry != शून्य)
		entry = netlbl_unlhsh_addr6_entry(list_entry);
	अन्यथा
		entry = शून्य;

	audit_buf = netlbl_audit_start_common(AUDIT_MAC_UNLBL_STCDEL,
					      audit_info);
	अगर (audit_buf != शून्य) अणु
		dev = dev_get_by_index(net, अगरace->अगरindex);
		netlbl_af6list_audit_addr(audit_buf, 1,
					  (dev != शून्य ? dev->name : शून्य),
					  addr, mask);
		अगर (dev != शून्य)
			dev_put(dev);
		अगर (entry != शून्य &&
		    security_secid_to_secctx(entry->secid,
					     &secctx, &secctx_len) == 0) अणु
			audit_log_क्रमmat(audit_buf, " sec_obj=%s", secctx);
			security_release_secctx(secctx, secctx_len);
		पूर्ण
		audit_log_क्रमmat(audit_buf, " res=%u", entry != शून्य ? 1 : 0);
		audit_log_end(audit_buf);
	पूर्ण

	अगर (entry == शून्य)
		वापस -ENOENT;

	kमुक्त_rcu(entry, rcu);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* IPv6 */

/**
 * netlbl_unlhsh_condहटाओ_अगरace - Remove an पूर्णांकerface entry
 * @अगरace: the पूर्णांकerface entry
 *
 * Description:
 * Remove an पूर्णांकerface entry from the unlabeled connection hash table अगर it is
 * empty.  An पूर्णांकerface entry is considered to be empty अगर there are no
 * address entries asचिन्हित to it.
 *
 */
अटल व्योम netlbl_unlhsh_condहटाओ_अगरace(काष्ठा netlbl_unlhsh_अगरace *अगरace)
अणु
	काष्ठा netlbl_af4list *iter4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा netlbl_af6list *iter6;
#पूर्ण_अगर /* IPv6 */

	spin_lock(&netlbl_unlhsh_lock);
	netlbl_af4list_क्रमeach_rcu(iter4, &अगरace->addr4_list)
		जाओ unlhsh_condहटाओ_failure;
#अगर IS_ENABLED(CONFIG_IPV6)
	netlbl_af6list_क्रमeach_rcu(iter6, &अगरace->addr6_list)
		जाओ unlhsh_condहटाओ_failure;
#पूर्ण_अगर /* IPv6 */
	अगरace->valid = 0;
	अगर (अगरace->अगरindex > 0)
		list_del_rcu(&अगरace->list);
	अन्यथा
		RCU_INIT_POINTER(netlbl_unlhsh_def, शून्य);
	spin_unlock(&netlbl_unlhsh_lock);

	call_rcu(&अगरace->rcu, netlbl_unlhsh_मुक्त_अगरace);
	वापस;

unlhsh_condहटाओ_failure:
	spin_unlock(&netlbl_unlhsh_lock);
पूर्ण

/**
 * netlbl_unlhsh_हटाओ - Remove an entry from the unlabeled hash table
 * @net: network namespace
 * @dev_name: पूर्णांकerface name
 * @addr: IP address in network byte order
 * @mask: address mask in network byte order
 * @addr_len: length of address/mask (4 क्रम IPv4, 16 क्रम IPv6)
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Removes and existing entry from the unlabeled connection hash table.
 * Returns zero on success, negative values on failure.
 *
 */
पूर्णांक netlbl_unlhsh_हटाओ(काष्ठा net *net,
			 स्थिर अक्षर *dev_name,
			 स्थिर व्योम *addr,
			 स्थिर व्योम *mask,
			 u32 addr_len,
			 काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val;
	काष्ठा net_device *dev;
	काष्ठा netlbl_unlhsh_अगरace *अगरace;

	अगर (addr_len != माप(काष्ठा in_addr) &&
	    addr_len != माप(काष्ठा in6_addr))
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	अगर (dev_name != शून्य) अणु
		dev = dev_get_by_name_rcu(net, dev_name);
		अगर (dev == शून्य) अणु
			ret_val = -ENODEV;
			जाओ unlhsh_हटाओ_वापस;
		पूर्ण
		अगरace = netlbl_unlhsh_search_अगरace(dev->अगरindex);
	पूर्ण अन्यथा
		अगरace = rcu_dereference(netlbl_unlhsh_def);
	अगर (अगरace == शून्य) अणु
		ret_val = -ENOENT;
		जाओ unlhsh_हटाओ_वापस;
	पूर्ण
	चयन (addr_len) अणु
	हाल माप(काष्ठा in_addr):
		ret_val = netlbl_unlhsh_हटाओ_addr4(net,
						     अगरace, addr, mask,
						     audit_info);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल माप(काष्ठा in6_addr):
		ret_val = netlbl_unlhsh_हटाओ_addr6(net,
						     अगरace, addr, mask,
						     audit_info);
		अवरोध;
#पूर्ण_अगर /* IPv6 */
	शेष:
		ret_val = -EINVAL;
	पूर्ण
	अगर (ret_val == 0) अणु
		netlbl_unlhsh_condहटाओ_अगरace(अगरace);
		atomic_dec(&netlabel_mgmt_protocount);
	पूर्ण

unlhsh_हटाओ_वापस:
	rcu_पढ़ो_unlock();
	वापस ret_val;
पूर्ण

/*
 * General Helper Functions
 */

/**
 * netlbl_unlhsh_netdev_handler - Network device notअगरication handler
 * @this: notअगरier block
 * @event: the event
 * @ptr: the netdevice notअगरier info (cast to व्योम)
 *
 * Description:
 * Handle network device events, although at present all we care about is a
 * network device going away.  In the हाल of a device going away we clear any
 * related entries from the unlabeled connection hash table.
 *
 */
अटल पूर्णांक netlbl_unlhsh_netdev_handler(काष्ठा notअगरier_block *this,
					अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा netlbl_unlhsh_अगरace *अगरace = शून्य;

	अगर (!net_eq(dev_net(dev), &init_net))
		वापस NOTIFY_DONE;

	/* XXX - should this be a check क्रम NETDEV_DOWN or _UNREGISTER? */
	अगर (event == NETDEV_DOWN) अणु
		spin_lock(&netlbl_unlhsh_lock);
		अगरace = netlbl_unlhsh_search_अगरace(dev->अगरindex);
		अगर (अगरace != शून्य && अगरace->valid) अणु
			अगरace->valid = 0;
			list_del_rcu(&अगरace->list);
		पूर्ण अन्यथा
			अगरace = शून्य;
		spin_unlock(&netlbl_unlhsh_lock);
	पूर्ण

	अगर (अगरace != शून्य)
		call_rcu(&अगरace->rcu, netlbl_unlhsh_मुक्त_अगरace);

	वापस NOTIFY_DONE;
पूर्ण

/**
 * netlbl_unlabel_acceptflg_set - Set the unlabeled accept flag
 * @value: desired value
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Set the value of the unlabeled accept flag to @value.
 *
 */
अटल व्योम netlbl_unlabel_acceptflg_set(u8 value,
					 काष्ठा netlbl_audit *audit_info)
अणु
	काष्ठा audit_buffer *audit_buf;
	u8 old_val;

	old_val = netlabel_unlabel_acceptflg;
	netlabel_unlabel_acceptflg = value;
	audit_buf = netlbl_audit_start_common(AUDIT_MAC_UNLBL_ALLOW,
					      audit_info);
	अगर (audit_buf != शून्य) अणु
		audit_log_क्रमmat(audit_buf,
				 " unlbl_accept=%u old=%u", value, old_val);
		audit_log_end(audit_buf);
	पूर्ण
पूर्ण

/**
 * netlbl_unlabel_addrinfo_get - Get the IPv4/6 address inक्रमmation
 * @info: the Generic NETLINK info block
 * @addr: the IP address
 * @mask: the IP address mask
 * @len: the address length
 *
 * Description:
 * Examine the Generic NETLINK message and extract the IP address inक्रमmation.
 * Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_unlabel_addrinfo_get(काष्ठा genl_info *info,
				       व्योम **addr,
				       व्योम **mask,
				       u32 *len)
अणु
	u32 addr_len;

	अगर (info->attrs[NLBL_UNLABEL_A_IPV4ADDR] &&
	    info->attrs[NLBL_UNLABEL_A_IPV4MASK]) अणु
		addr_len = nla_len(info->attrs[NLBL_UNLABEL_A_IPV4ADDR]);
		अगर (addr_len != माप(काष्ठा in_addr) &&
		    addr_len != nla_len(info->attrs[NLBL_UNLABEL_A_IPV4MASK]))
			वापस -EINVAL;
		*len = addr_len;
		*addr = nla_data(info->attrs[NLBL_UNLABEL_A_IPV4ADDR]);
		*mask = nla_data(info->attrs[NLBL_UNLABEL_A_IPV4MASK]);
		वापस 0;
	पूर्ण अन्यथा अगर (info->attrs[NLBL_UNLABEL_A_IPV6ADDR]) अणु
		addr_len = nla_len(info->attrs[NLBL_UNLABEL_A_IPV6ADDR]);
		अगर (addr_len != माप(काष्ठा in6_addr) &&
		    addr_len != nla_len(info->attrs[NLBL_UNLABEL_A_IPV6MASK]))
			वापस -EINVAL;
		*len = addr_len;
		*addr = nla_data(info->attrs[NLBL_UNLABEL_A_IPV6ADDR]);
		*mask = nla_data(info->attrs[NLBL_UNLABEL_A_IPV6MASK]);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * NetLabel Command Handlers
 */

/**
 * netlbl_unlabel_accept - Handle an ACCEPT message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated ACCEPT message and set the accept flag accordingly.
 * Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_unlabel_accept(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	u8 value;
	काष्ठा netlbl_audit audit_info;

	अगर (info->attrs[NLBL_UNLABEL_A_ACPTFLG]) अणु
		value = nla_get_u8(info->attrs[NLBL_UNLABEL_A_ACPTFLG]);
		अगर (value == 1 || value == 0) अणु
			netlbl_netlink_auditinfo(skb, &audit_info);
			netlbl_unlabel_acceptflg_set(value, &audit_info);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * netlbl_unlabel_list - Handle a LIST message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated LIST message and respond with the current status.
 * Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_unlabel_list(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक ret_val = -EINVAL;
	काष्ठा sk_buff *ans_skb;
	व्योम *data;

	ans_skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (ans_skb == शून्य)
		जाओ list_failure;
	data = genlmsg_put_reply(ans_skb, info, &netlbl_unlabel_gnl_family,
				 0, NLBL_UNLABEL_C_LIST);
	अगर (data == शून्य) अणु
		ret_val = -ENOMEM;
		जाओ list_failure;
	पूर्ण

	ret_val = nla_put_u8(ans_skb,
			     NLBL_UNLABEL_A_ACPTFLG,
			     netlabel_unlabel_acceptflg);
	अगर (ret_val != 0)
		जाओ list_failure;

	genlmsg_end(ans_skb, data);
	वापस genlmsg_reply(ans_skb, info);

list_failure:
	kमुक्त_skb(ans_skb);
	वापस ret_val;
पूर्ण

/**
 * netlbl_unlabel_अटलadd - Handle a STATICADD message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated STATICADD message and add a new unlabeled
 * connection entry to the hash table.  Returns zero on success, negative
 * values on failure.
 *
 */
अटल पूर्णांक netlbl_unlabel_अटलadd(काष्ठा sk_buff *skb,
				    काष्ठा genl_info *info)
अणु
	पूर्णांक ret_val;
	अक्षर *dev_name;
	व्योम *addr;
	व्योम *mask;
	u32 addr_len;
	u32 secid;
	काष्ठा netlbl_audit audit_info;

	/* Don't allow users to add both IPv4 and IPv6 addresses क्रम a
	 * single entry.  However, allow users to create two entries, one each
	 * क्रम IPv4 and IPv4, with the same LSM security context which should
	 * achieve the same result. */
	अगर (!info->attrs[NLBL_UNLABEL_A_SECCTX] ||
	    !info->attrs[NLBL_UNLABEL_A_IFACE] ||
	    !((!info->attrs[NLBL_UNLABEL_A_IPV4ADDR] ||
	       !info->attrs[NLBL_UNLABEL_A_IPV4MASK]) ^
	      (!info->attrs[NLBL_UNLABEL_A_IPV6ADDR] ||
	       !info->attrs[NLBL_UNLABEL_A_IPV6MASK])))
		वापस -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);

	ret_val = netlbl_unlabel_addrinfo_get(info, &addr, &mask, &addr_len);
	अगर (ret_val != 0)
		वापस ret_val;
	dev_name = nla_data(info->attrs[NLBL_UNLABEL_A_IFACE]);
	ret_val = security_secctx_to_secid(
		                  nla_data(info->attrs[NLBL_UNLABEL_A_SECCTX]),
				  nla_len(info->attrs[NLBL_UNLABEL_A_SECCTX]),
				  &secid);
	अगर (ret_val != 0)
		वापस ret_val;

	वापस netlbl_unlhsh_add(&init_net,
				 dev_name, addr, mask, addr_len, secid,
				 &audit_info);
पूर्ण

/**
 * netlbl_unlabel_अटलadddef - Handle a STATICADDDEF message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated STATICADDDEF message and add a new शेष
 * unlabeled connection entry.  Returns zero on success, negative values on
 * failure.
 *
 */
अटल पूर्णांक netlbl_unlabel_अटलadddef(काष्ठा sk_buff *skb,
				       काष्ठा genl_info *info)
अणु
	पूर्णांक ret_val;
	व्योम *addr;
	व्योम *mask;
	u32 addr_len;
	u32 secid;
	काष्ठा netlbl_audit audit_info;

	/* Don't allow users to add both IPv4 and IPv6 addresses क्रम a
	 * single entry.  However, allow users to create two entries, one each
	 * क्रम IPv4 and IPv6, with the same LSM security context which should
	 * achieve the same result. */
	अगर (!info->attrs[NLBL_UNLABEL_A_SECCTX] ||
	    !((!info->attrs[NLBL_UNLABEL_A_IPV4ADDR] ||
	       !info->attrs[NLBL_UNLABEL_A_IPV4MASK]) ^
	      (!info->attrs[NLBL_UNLABEL_A_IPV6ADDR] ||
	       !info->attrs[NLBL_UNLABEL_A_IPV6MASK])))
		वापस -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);

	ret_val = netlbl_unlabel_addrinfo_get(info, &addr, &mask, &addr_len);
	अगर (ret_val != 0)
		वापस ret_val;
	ret_val = security_secctx_to_secid(
		                  nla_data(info->attrs[NLBL_UNLABEL_A_SECCTX]),
				  nla_len(info->attrs[NLBL_UNLABEL_A_SECCTX]),
				  &secid);
	अगर (ret_val != 0)
		वापस ret_val;

	वापस netlbl_unlhsh_add(&init_net,
				 शून्य, addr, mask, addr_len, secid,
				 &audit_info);
पूर्ण

/**
 * netlbl_unlabel_अटलहटाओ - Handle a STATICREMOVE message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated STATICREMOVE message and हटाओ the specअगरied
 * unlabeled connection entry.  Returns zero on success, negative values on
 * failure.
 *
 */
अटल पूर्णांक netlbl_unlabel_अटलहटाओ(काष्ठा sk_buff *skb,
				       काष्ठा genl_info *info)
अणु
	पूर्णांक ret_val;
	अक्षर *dev_name;
	व्योम *addr;
	व्योम *mask;
	u32 addr_len;
	काष्ठा netlbl_audit audit_info;

	/* See the note in netlbl_unlabel_अटलadd() about not allowing both
	 * IPv4 and IPv6 in the same entry. */
	अगर (!info->attrs[NLBL_UNLABEL_A_IFACE] ||
	    !((!info->attrs[NLBL_UNLABEL_A_IPV4ADDR] ||
	       !info->attrs[NLBL_UNLABEL_A_IPV4MASK]) ^
	      (!info->attrs[NLBL_UNLABEL_A_IPV6ADDR] ||
	       !info->attrs[NLBL_UNLABEL_A_IPV6MASK])))
		वापस -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);

	ret_val = netlbl_unlabel_addrinfo_get(info, &addr, &mask, &addr_len);
	अगर (ret_val != 0)
		वापस ret_val;
	dev_name = nla_data(info->attrs[NLBL_UNLABEL_A_IFACE]);

	वापस netlbl_unlhsh_हटाओ(&init_net,
				    dev_name, addr, mask, addr_len,
				    &audit_info);
पूर्ण

/**
 * netlbl_unlabel_अटलहटाओdef - Handle a STATICREMOVEDEF message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated STATICREMOVEDEF message and हटाओ the शेष
 * unlabeled connection entry.  Returns zero on success, negative values on
 * failure.
 *
 */
अटल पूर्णांक netlbl_unlabel_अटलहटाओdef(काष्ठा sk_buff *skb,
					  काष्ठा genl_info *info)
अणु
	पूर्णांक ret_val;
	व्योम *addr;
	व्योम *mask;
	u32 addr_len;
	काष्ठा netlbl_audit audit_info;

	/* See the note in netlbl_unlabel_अटलadd() about not allowing both
	 * IPv4 and IPv6 in the same entry. */
	अगर (!((!info->attrs[NLBL_UNLABEL_A_IPV4ADDR] ||
	       !info->attrs[NLBL_UNLABEL_A_IPV4MASK]) ^
	      (!info->attrs[NLBL_UNLABEL_A_IPV6ADDR] ||
	       !info->attrs[NLBL_UNLABEL_A_IPV6MASK])))
		वापस -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);

	ret_val = netlbl_unlabel_addrinfo_get(info, &addr, &mask, &addr_len);
	अगर (ret_val != 0)
		वापस ret_val;

	वापस netlbl_unlhsh_हटाओ(&init_net,
				    शून्य, addr, mask, addr_len,
				    &audit_info);
पूर्ण


/**
 * netlbl_unlabel_अटलlist_gen - Generate messages क्रम STATICLIST[DEF]
 * @cmd: command/message
 * @अगरace: the पूर्णांकerface entry
 * @addr4: the IPv4 address entry
 * @addr6: the IPv6 address entry
 * @arg: the netlbl_unlhsh_walk_arg काष्ठाure
 *
 * Description:
 * This function is deचिन्हित to be used to generate a response क्रम a
 * STATICLIST or STATICLISTDEF message.  When called either @addr4 or @addr6
 * can be specअगरied, not both, the other unspecअगरied entry should be set to
 * शून्य by the caller.  Returns the size of the message on success, negative
 * values on failure.
 *
 */
अटल पूर्णांक netlbl_unlabel_अटलlist_gen(u32 cmd,
				       स्थिर काष्ठा netlbl_unlhsh_अगरace *अगरace,
				       स्थिर काष्ठा netlbl_unlhsh_addr4 *addr4,
				       स्थिर काष्ठा netlbl_unlhsh_addr6 *addr6,
				       व्योम *arg)
अणु
	पूर्णांक ret_val = -ENOMEM;
	काष्ठा netlbl_unlhsh_walk_arg *cb_arg = arg;
	काष्ठा net_device *dev;
	व्योम *data;
	u32 secid;
	अक्षर *secctx;
	u32 secctx_len;

	data = genlmsg_put(cb_arg->skb, NETLINK_CB(cb_arg->nl_cb->skb).portid,
			   cb_arg->seq, &netlbl_unlabel_gnl_family,
			   NLM_F_MULTI, cmd);
	अगर (data == शून्य)
		जाओ list_cb_failure;

	अगर (अगरace->अगरindex > 0) अणु
		dev = dev_get_by_index(&init_net, अगरace->अगरindex);
		अगर (!dev) अणु
			ret_val = -ENODEV;
			जाओ list_cb_failure;
		पूर्ण
		ret_val = nla_put_string(cb_arg->skb,
					 NLBL_UNLABEL_A_IFACE, dev->name);
		dev_put(dev);
		अगर (ret_val != 0)
			जाओ list_cb_failure;
	पूर्ण

	अगर (addr4) अणु
		काष्ठा in_addr addr_काष्ठा;

		addr_काष्ठा.s_addr = addr4->list.addr;
		ret_val = nla_put_in_addr(cb_arg->skb,
					  NLBL_UNLABEL_A_IPV4ADDR,
					  addr_काष्ठा.s_addr);
		अगर (ret_val != 0)
			जाओ list_cb_failure;

		addr_काष्ठा.s_addr = addr4->list.mask;
		ret_val = nla_put_in_addr(cb_arg->skb,
					  NLBL_UNLABEL_A_IPV4MASK,
					  addr_काष्ठा.s_addr);
		अगर (ret_val != 0)
			जाओ list_cb_failure;

		secid = addr4->secid;
	पूर्ण अन्यथा अणु
		ret_val = nla_put_in6_addr(cb_arg->skb,
					   NLBL_UNLABEL_A_IPV6ADDR,
					   &addr6->list.addr);
		अगर (ret_val != 0)
			जाओ list_cb_failure;

		ret_val = nla_put_in6_addr(cb_arg->skb,
					   NLBL_UNLABEL_A_IPV6MASK,
					   &addr6->list.mask);
		अगर (ret_val != 0)
			जाओ list_cb_failure;

		secid = addr6->secid;
	पूर्ण

	ret_val = security_secid_to_secctx(secid, &secctx, &secctx_len);
	अगर (ret_val != 0)
		जाओ list_cb_failure;
	ret_val = nla_put(cb_arg->skb,
			  NLBL_UNLABEL_A_SECCTX,
			  secctx_len,
			  secctx);
	security_release_secctx(secctx, secctx_len);
	अगर (ret_val != 0)
		जाओ list_cb_failure;

	cb_arg->seq++;
	genlmsg_end(cb_arg->skb, data);
	वापस 0;

list_cb_failure:
	genlmsg_cancel(cb_arg->skb, data);
	वापस ret_val;
पूर्ण

/**
 * netlbl_unlabel_अटलlist - Handle a STATICLIST message
 * @skb: the NETLINK buffer
 * @cb: the NETLINK callback
 *
 * Description:
 * Process a user generated STATICLIST message and dump the unlabeled
 * connection hash table in a क्रमm suitable क्रम use in a kernel generated
 * STATICLIST message.  Returns the length of @skb.
 *
 */
अटल पूर्णांक netlbl_unlabel_अटलlist(काष्ठा sk_buff *skb,
				     काष्ठा netlink_callback *cb)
अणु
	काष्ठा netlbl_unlhsh_walk_arg cb_arg;
	u32 skip_bkt = cb->args[0];
	u32 skip_chain = cb->args[1];
	u32 skip_addr4 = cb->args[2];
	u32 iter_bkt, iter_chain = 0, iter_addr4 = 0, iter_addr6 = 0;
	काष्ठा netlbl_unlhsh_अगरace *अगरace;
	काष्ठा list_head *iter_list;
	काष्ठा netlbl_af4list *addr4;
#अगर IS_ENABLED(CONFIG_IPV6)
	u32 skip_addr6 = cb->args[3];
	काष्ठा netlbl_af6list *addr6;
#पूर्ण_अगर

	cb_arg.nl_cb = cb;
	cb_arg.skb = skb;
	cb_arg.seq = cb->nlh->nlmsg_seq;

	rcu_पढ़ो_lock();
	क्रम (iter_bkt = skip_bkt;
	     iter_bkt < rcu_dereference(netlbl_unlhsh)->size;
	     iter_bkt++) अणु
		iter_list = &rcu_dereference(netlbl_unlhsh)->tbl[iter_bkt];
		list_क्रम_each_entry_rcu(अगरace, iter_list, list) अणु
			अगर (!अगरace->valid ||
			    iter_chain++ < skip_chain)
				जारी;
			netlbl_af4list_क्रमeach_rcu(addr4,
						   &अगरace->addr4_list) अणु
				अगर (iter_addr4++ < skip_addr4)
					जारी;
				अगर (netlbl_unlabel_अटलlist_gen(
					      NLBL_UNLABEL_C_STATICLIST,
					      अगरace,
					      netlbl_unlhsh_addr4_entry(addr4),
					      शून्य,
					      &cb_arg) < 0) अणु
					iter_addr4--;
					iter_chain--;
					जाओ unlabel_अटलlist_वापस;
				पूर्ण
			पूर्ण
			iter_addr4 = 0;
			skip_addr4 = 0;
#अगर IS_ENABLED(CONFIG_IPV6)
			netlbl_af6list_क्रमeach_rcu(addr6,
						   &अगरace->addr6_list) अणु
				अगर (iter_addr6++ < skip_addr6)
					जारी;
				अगर (netlbl_unlabel_अटलlist_gen(
					      NLBL_UNLABEL_C_STATICLIST,
					      अगरace,
					      शून्य,
					      netlbl_unlhsh_addr6_entry(addr6),
					      &cb_arg) < 0) अणु
					iter_addr6--;
					iter_chain--;
					जाओ unlabel_अटलlist_वापस;
				पूर्ण
			पूर्ण
			iter_addr6 = 0;
			skip_addr6 = 0;
#पूर्ण_अगर /* IPv6 */
		पूर्ण
		iter_chain = 0;
		skip_chain = 0;
	पूर्ण

unlabel_अटलlist_वापस:
	rcu_पढ़ो_unlock();
	cb->args[0] = iter_bkt;
	cb->args[1] = iter_chain;
	cb->args[2] = iter_addr4;
	cb->args[3] = iter_addr6;
	वापस skb->len;
पूर्ण

/**
 * netlbl_unlabel_अटलlistdef - Handle a STATICLISTDEF message
 * @skb: the NETLINK buffer
 * @cb: the NETLINK callback
 *
 * Description:
 * Process a user generated STATICLISTDEF message and dump the शेष
 * unlabeled connection entry in a क्रमm suitable क्रम use in a kernel generated
 * STATICLISTDEF message.  Returns the length of @skb.
 *
 */
अटल पूर्णांक netlbl_unlabel_अटलlistdef(काष्ठा sk_buff *skb,
					काष्ठा netlink_callback *cb)
अणु
	काष्ठा netlbl_unlhsh_walk_arg cb_arg;
	काष्ठा netlbl_unlhsh_अगरace *अगरace;
	u32 iter_addr4 = 0, iter_addr6 = 0;
	काष्ठा netlbl_af4list *addr4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा netlbl_af6list *addr6;
#पूर्ण_अगर

	cb_arg.nl_cb = cb;
	cb_arg.skb = skb;
	cb_arg.seq = cb->nlh->nlmsg_seq;

	rcu_पढ़ो_lock();
	अगरace = rcu_dereference(netlbl_unlhsh_def);
	अगर (अगरace == शून्य || !अगरace->valid)
		जाओ unlabel_अटलlistdef_वापस;

	netlbl_af4list_क्रमeach_rcu(addr4, &अगरace->addr4_list) अणु
		अगर (iter_addr4++ < cb->args[0])
			जारी;
		अगर (netlbl_unlabel_अटलlist_gen(NLBL_UNLABEL_C_STATICLISTDEF,
					      अगरace,
					      netlbl_unlhsh_addr4_entry(addr4),
					      शून्य,
					      &cb_arg) < 0) अणु
			iter_addr4--;
			जाओ unlabel_अटलlistdef_वापस;
		पूर्ण
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	netlbl_af6list_क्रमeach_rcu(addr6, &अगरace->addr6_list) अणु
		अगर (iter_addr6++ < cb->args[1])
			जारी;
		अगर (netlbl_unlabel_अटलlist_gen(NLBL_UNLABEL_C_STATICLISTDEF,
					      अगरace,
					      शून्य,
					      netlbl_unlhsh_addr6_entry(addr6),
					      &cb_arg) < 0) अणु
			iter_addr6--;
			जाओ unlabel_अटलlistdef_वापस;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* IPv6 */

unlabel_अटलlistdef_वापस:
	rcu_पढ़ो_unlock();
	cb->args[0] = iter_addr4;
	cb->args[1] = iter_addr6;
	वापस skb->len;
पूर्ण

/*
 * NetLabel Generic NETLINK Command Definitions
 */

अटल स्थिर काष्ठा genl_small_ops netlbl_unlabel_genl_ops[] = अणु
	अणु
	.cmd = NLBL_UNLABEL_C_STATICADD,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = GENL_ADMIN_PERM,
	.करोit = netlbl_unlabel_अटलadd,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_UNLABEL_C_STATICREMOVE,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = GENL_ADMIN_PERM,
	.करोit = netlbl_unlabel_अटलहटाओ,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_UNLABEL_C_STATICLIST,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = 0,
	.करोit = शून्य,
	.dumpit = netlbl_unlabel_अटलlist,
	पूर्ण,
	अणु
	.cmd = NLBL_UNLABEL_C_STATICADDDEF,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = GENL_ADMIN_PERM,
	.करोit = netlbl_unlabel_अटलadddef,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_UNLABEL_C_STATICREMOVEDEF,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = GENL_ADMIN_PERM,
	.करोit = netlbl_unlabel_अटलहटाओdef,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_UNLABEL_C_STATICLISTDEF,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = 0,
	.करोit = शून्य,
	.dumpit = netlbl_unlabel_अटलlistdef,
	पूर्ण,
	अणु
	.cmd = NLBL_UNLABEL_C_ACCEPT,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = GENL_ADMIN_PERM,
	.करोit = netlbl_unlabel_accept,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_UNLABEL_C_LIST,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = 0,
	.करोit = netlbl_unlabel_list,
	.dumpit = शून्य,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family netlbl_unlabel_gnl_family __ro_after_init = अणु
	.hdrsize = 0,
	.name = NETLBL_NLTYPE_UNLABELED_NAME,
	.version = NETLBL_PROTO_VERSION,
	.maxattr = NLBL_UNLABEL_A_MAX,
	.policy = netlbl_unlabel_genl_policy,
	.module = THIS_MODULE,
	.small_ops = netlbl_unlabel_genl_ops,
	.n_small_ops = ARRAY_SIZE(netlbl_unlabel_genl_ops),
पूर्ण;

/*
 * NetLabel Generic NETLINK Protocol Functions
 */

/**
 * netlbl_unlabel_genl_init - Register the Unlabeled NetLabel component
 *
 * Description:
 * Register the unlabeled packet NetLabel component with the Generic NETLINK
 * mechanism.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक __init netlbl_unlabel_genl_init(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&netlbl_unlabel_gnl_family);
पूर्ण

/*
 * NetLabel KAPI Hooks
 */

अटल काष्ठा notअगरier_block netlbl_unlhsh_netdev_notअगरier = अणु
	.notअगरier_call = netlbl_unlhsh_netdev_handler,
पूर्ण;

/**
 * netlbl_unlabel_init - Initialize the unlabeled connection hash table
 * @size: the number of bits to use क्रम the hash buckets
 *
 * Description:
 * Initializes the unlabeled connection hash table and रेजिस्टरs a network
 * device notअगरication handler.  This function should only be called by the
 * NetLabel subप्रणाली itself during initialization.  Returns zero on success,
 * non-zero values on error.
 *
 */
पूर्णांक __init netlbl_unlabel_init(u32 size)
अणु
	u32 iter;
	काष्ठा netlbl_unlhsh_tbl *hsh_tbl;

	अगर (size == 0)
		वापस -EINVAL;

	hsh_tbl = kदो_स्मृति(माप(*hsh_tbl), GFP_KERNEL);
	अगर (hsh_tbl == शून्य)
		वापस -ENOMEM;
	hsh_tbl->size = 1 << size;
	hsh_tbl->tbl = kसुस्मृति(hsh_tbl->size,
			       माप(काष्ठा list_head),
			       GFP_KERNEL);
	अगर (hsh_tbl->tbl == शून्य) अणु
		kमुक्त(hsh_tbl);
		वापस -ENOMEM;
	पूर्ण
	क्रम (iter = 0; iter < hsh_tbl->size; iter++)
		INIT_LIST_HEAD(&hsh_tbl->tbl[iter]);

	spin_lock(&netlbl_unlhsh_lock);
	rcu_assign_poपूर्णांकer(netlbl_unlhsh, hsh_tbl);
	spin_unlock(&netlbl_unlhsh_lock);

	रेजिस्टर_netdevice_notअगरier(&netlbl_unlhsh_netdev_notअगरier);

	वापस 0;
पूर्ण

/**
 * netlbl_unlabel_getattr - Get the security attributes क्रम an unlabled packet
 * @skb: the packet
 * @family: protocol family
 * @secattr: the security attributes
 *
 * Description:
 * Determine the security attributes, अगर any, क्रम an unlabled packet and वापस
 * them in @secattr.  Returns zero on success and negative values on failure.
 *
 */
पूर्णांक netlbl_unlabel_getattr(स्थिर काष्ठा sk_buff *skb,
			   u16 family,
			   काष्ठा netlbl_lsm_secattr *secattr)
अणु
	काष्ठा netlbl_unlhsh_अगरace *अगरace;

	rcu_पढ़ो_lock();
	अगरace = netlbl_unlhsh_search_अगरace(skb->skb_iअगर);
	अगर (अगरace == शून्य)
		अगरace = rcu_dereference(netlbl_unlhsh_def);
	अगर (अगरace == शून्य || !अगरace->valid)
		जाओ unlabel_getattr_nolabel;

#अगर IS_ENABLED(CONFIG_IPV6)
	/* When resolving a fallback label, check the sk_buff version as
	 * it is possible (e.g. SCTP) to have family = PF_INET6 जबतक
	 * receiving ip_hdr(skb)->version = 4.
	 */
	अगर (family == PF_INET6 && ip_hdr(skb)->version == 4)
		family = PF_INET;
#पूर्ण_अगर /* IPv6 */

	चयन (family) अणु
	हाल PF_INET: अणु
		काष्ठा iphdr *hdr4;
		काष्ठा netlbl_af4list *addr4;

		hdr4 = ip_hdr(skb);
		addr4 = netlbl_af4list_search(hdr4->saddr,
					      &अगरace->addr4_list);
		अगर (addr4 == शून्य)
			जाओ unlabel_getattr_nolabel;
		secattr->attr.secid = netlbl_unlhsh_addr4_entry(addr4)->secid;
		अवरोध;
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल PF_INET6: अणु
		काष्ठा ipv6hdr *hdr6;
		काष्ठा netlbl_af6list *addr6;

		hdr6 = ipv6_hdr(skb);
		addr6 = netlbl_af6list_search(&hdr6->saddr,
					      &अगरace->addr6_list);
		अगर (addr6 == शून्य)
			जाओ unlabel_getattr_nolabel;
		secattr->attr.secid = netlbl_unlhsh_addr6_entry(addr6)->secid;
		अवरोध;
	पूर्ण
#पूर्ण_अगर /* IPv6 */
	शेष:
		जाओ unlabel_getattr_nolabel;
	पूर्ण
	rcu_पढ़ो_unlock();

	secattr->flags |= NETLBL_SECATTR_SECID;
	secattr->type = NETLBL_NLTYPE_UNLABELED;
	वापस 0;

unlabel_getattr_nolabel:
	rcu_पढ़ो_unlock();
	अगर (netlabel_unlabel_acceptflg == 0)
		वापस -ENOMSG;
	secattr->type = NETLBL_NLTYPE_UNLABELED;
	वापस 0;
पूर्ण

/**
 * netlbl_unlabel_defconf - Set the शेष config to allow unlabeled packets
 *
 * Description:
 * Set the शेष NetLabel configuration to allow incoming unlabeled packets
 * and to send unlabeled network traffic by शेष.
 *
 */
पूर्णांक __init netlbl_unlabel_defconf(व्योम)
अणु
	पूर्णांक ret_val;
	काष्ठा netlbl_करोm_map *entry;
	काष्ठा netlbl_audit audit_info;

	/* Only the kernel is allowed to call this function and the only समय
	 * it is called is at bootup beक्रमe the audit subप्रणाली is reporting
	 * messages so करोn't worry to much about these values. */
	security_task_माला_लोecid_subj(current, &audit_info.secid);
	audit_info.loginuid = GLOBAL_ROOT_UID;
	audit_info.sessionid = 0;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (entry == शून्य)
		वापस -ENOMEM;
	entry->family = AF_UNSPEC;
	entry->def.type = NETLBL_NLTYPE_UNLABELED;
	ret_val = netlbl_करोmhsh_add_शेष(entry, &audit_info);
	अगर (ret_val != 0)
		वापस ret_val;

	netlbl_unlabel_acceptflg_set(1, &audit_info);

	वापस 0;
पूर्ण
