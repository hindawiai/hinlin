<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
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

#समावेश <linux/types.h>
#समावेश <linux/rculist.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/audit.h>
#समावेश <linux/slab.h>
#समावेश <net/netlabel.h>
#समावेश <net/cipso_ipv4.h>
#समावेश <net/calipso.h>
#समावेश <यंत्र/bug.h>

#समावेश "netlabel_mgmt.h"
#समावेश "netlabel_addrlist.h"
#समावेश "netlabel_calipso.h"
#समावेश "netlabel_domainhash.h"
#समावेश "netlabel_user.h"

काष्ठा netlbl_करोmhsh_tbl अणु
	काष्ठा list_head *tbl;
	u32 size;
पूर्ण;

/* Doमुख्य hash table */
/* updates should be so rare that having one spinlock क्रम the entire hash table
 * should be okay */
अटल DEFINE_SPINLOCK(netlbl_करोmhsh_lock);
#घोषणा netlbl_करोmhsh_rcu_deref(p) \
	rcu_dereference_check(p, lockdep_is_held(&netlbl_करोmhsh_lock))
अटल काष्ठा netlbl_करोmhsh_tbl __rcu *netlbl_करोmhsh;
अटल काष्ठा netlbl_करोm_map __rcu *netlbl_करोmhsh_def_ipv4;
अटल काष्ठा netlbl_करोm_map __rcu *netlbl_करोmhsh_def_ipv6;

/*
 * Doमुख्य Hash Table Helper Functions
 */

/**
 * netlbl_करोmhsh_मुक्त_entry - Frees a करोमुख्य hash table entry
 * @entry: the entry's RCU field
 *
 * Description:
 * This function is deचिन्हित to be used as a callback to the call_rcu()
 * function so that the memory allocated to a hash table entry can be released
 * safely.
 *
 */
अटल व्योम netlbl_करोmhsh_मुक्त_entry(काष्ठा rcu_head *entry)
अणु
	काष्ठा netlbl_करोm_map *ptr;
	काष्ठा netlbl_af4list *iter4;
	काष्ठा netlbl_af4list *पंचांगp4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा netlbl_af6list *iter6;
	काष्ठा netlbl_af6list *पंचांगp6;
#पूर्ण_अगर /* IPv6 */

	ptr = container_of(entry, काष्ठा netlbl_करोm_map, rcu);
	अगर (ptr->def.type == NETLBL_NLTYPE_ADDRSELECT) अणु
		netlbl_af4list_क्रमeach_safe(iter4, पंचांगp4,
					    &ptr->def.addrsel->list4) अणु
			netlbl_af4list_हटाओ_entry(iter4);
			kमुक्त(netlbl_करोmhsh_addr4_entry(iter4));
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
		netlbl_af6list_क्रमeach_safe(iter6, पंचांगp6,
					    &ptr->def.addrsel->list6) अणु
			netlbl_af6list_हटाओ_entry(iter6);
			kमुक्त(netlbl_करोmhsh_addr6_entry(iter6));
		पूर्ण
#पूर्ण_अगर /* IPv6 */
		kमुक्त(ptr->def.addrsel);
	पूर्ण
	kमुक्त(ptr->करोमुख्य);
	kमुक्त(ptr);
पूर्ण

/**
 * netlbl_करोmhsh_hash - Hashing function क्रम the करोमुख्य hash table
 * @key: the करोमुख्य name to hash
 *
 * Description:
 * This is the hashing function क्रम the करोमुख्य hash table, it वापसs the
 * correct bucket number क्रम the करोमुख्य.  The caller is responsible क्रम
 * ensuring that the hash table is रक्षित with either a RCU पढ़ो lock or the
 * hash table lock.
 *
 */
अटल u32 netlbl_करोmhsh_hash(स्थिर अक्षर *key)
अणु
	u32 iter;
	u32 val;
	u32 len;

	/* This is taken (with slight modअगरication) from
	 * security/selinux/ss/symtab.c:symhash() */

	क्रम (iter = 0, val = 0, len = म_माप(key); iter < len; iter++)
		val = (val << 4 | (val >> (8 * माप(u32) - 4))) ^ key[iter];
	वापस val & (netlbl_करोmhsh_rcu_deref(netlbl_करोmhsh)->size - 1);
पूर्ण

अटल bool netlbl_family_match(u16 f1, u16 f2)
अणु
	वापस (f1 == f2) || (f1 == AF_UNSPEC) || (f2 == AF_UNSPEC);
पूर्ण

/**
 * netlbl_करोmhsh_search - Search क्रम a करोमुख्य entry
 * @करोमुख्य: the करोमुख्य
 * @family: the address family
 *
 * Description:
 * Searches the करोमुख्य hash table and वापसs a poपूर्णांकer to the hash table
 * entry अगर found, otherwise शून्य is वापसed.  @family may be %AF_UNSPEC
 * which matches any address family entries.  The caller is responsible क्रम
 * ensuring that the hash table is रक्षित with either a RCU पढ़ो lock or the
 * hash table lock.
 *
 */
अटल काष्ठा netlbl_करोm_map *netlbl_करोmhsh_search(स्थिर अक्षर *करोमुख्य,
						   u16 family)
अणु
	u32 bkt;
	काष्ठा list_head *bkt_list;
	काष्ठा netlbl_करोm_map *iter;

	अगर (करोमुख्य != शून्य) अणु
		bkt = netlbl_करोmhsh_hash(करोमुख्य);
		bkt_list = &netlbl_करोmhsh_rcu_deref(netlbl_करोmhsh)->tbl[bkt];
		list_क्रम_each_entry_rcu(iter, bkt_list, list,
					lockdep_is_held(&netlbl_करोmhsh_lock))
			अगर (iter->valid &&
			    netlbl_family_match(iter->family, family) &&
			    म_भेद(iter->करोमुख्य, करोमुख्य) == 0)
				वापस iter;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * netlbl_करोmhsh_search_def - Search क्रम a करोमुख्य entry
 * @करोमुख्य: the करोमुख्य
 * @family: the address family
 *
 * Description:
 * Searches the करोमुख्य hash table and वापसs a poपूर्णांकer to the hash table
 * entry अगर an exact match is found, अगर an exact match is not present in the
 * hash table then the शेष entry is वापसed अगर valid otherwise शून्य is
 * वापसed.  @family may be %AF_UNSPEC which matches any address family
 * entries.  The caller is responsible ensuring that the hash table is
 * रक्षित with either a RCU पढ़ो lock or the hash table lock.
 *
 */
अटल काष्ठा netlbl_करोm_map *netlbl_करोmhsh_search_def(स्थिर अक्षर *करोमुख्य,
						       u16 family)
अणु
	काष्ठा netlbl_करोm_map *entry;

	entry = netlbl_करोmhsh_search(करोमुख्य, family);
	अगर (entry != शून्य)
		वापस entry;
	अगर (family == AF_INET || family == AF_UNSPEC) अणु
		entry = netlbl_करोmhsh_rcu_deref(netlbl_करोmhsh_def_ipv4);
		अगर (entry != शून्य && entry->valid)
			वापस entry;
	पूर्ण
	अगर (family == AF_INET6 || family == AF_UNSPEC) अणु
		entry = netlbl_करोmhsh_rcu_deref(netlbl_करोmhsh_def_ipv6);
		अगर (entry != शून्य && entry->valid)
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * netlbl_करोmhsh_audit_add - Generate an audit entry क्रम an add event
 * @entry: the entry being added
 * @addr4: the IPv4 address inक्रमmation
 * @addr6: the IPv6 address inक्रमmation
 * @result: the result code
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Generate an audit record क्रम adding a new NetLabel/LSM mapping entry with
 * the given inक्रमmation.  Caller is responsible क्रम holding the necessary
 * locks.
 *
 */
अटल व्योम netlbl_करोmhsh_audit_add(काष्ठा netlbl_करोm_map *entry,
				    काष्ठा netlbl_af4list *addr4,
				    काष्ठा netlbl_af6list *addr6,
				    पूर्णांक result,
				    काष्ठा netlbl_audit *audit_info)
अणु
	काष्ठा audit_buffer *audit_buf;
	काष्ठा cipso_v4_करोi *cipsov4 = शून्य;
	काष्ठा calipso_करोi *calipso = शून्य;
	u32 type;

	audit_buf = netlbl_audit_start_common(AUDIT_MAC_MAP_ADD, audit_info);
	अगर (audit_buf != शून्य) अणु
		audit_log_क्रमmat(audit_buf, " nlbl_domain=%s",
				 entry->करोमुख्य ? entry->करोमुख्य : "(default)");
		अगर (addr4 != शून्य) अणु
			काष्ठा netlbl_करोmaddr4_map *map4;
			map4 = netlbl_करोmhsh_addr4_entry(addr4);
			type = map4->def.type;
			cipsov4 = map4->def.cipso;
			netlbl_af4list_audit_addr(audit_buf, 0, शून्य,
						  addr4->addr, addr4->mask);
#अगर IS_ENABLED(CONFIG_IPV6)
		पूर्ण अन्यथा अगर (addr6 != शून्य) अणु
			काष्ठा netlbl_करोmaddr6_map *map6;
			map6 = netlbl_करोmhsh_addr6_entry(addr6);
			type = map6->def.type;
			calipso = map6->def.calipso;
			netlbl_af6list_audit_addr(audit_buf, 0, शून्य,
						  &addr6->addr, &addr6->mask);
#पूर्ण_अगर /* IPv6 */
		पूर्ण अन्यथा अणु
			type = entry->def.type;
			cipsov4 = entry->def.cipso;
			calipso = entry->def.calipso;
		पूर्ण
		चयन (type) अणु
		हाल NETLBL_NLTYPE_UNLABELED:
			audit_log_क्रमmat(audit_buf, " nlbl_protocol=unlbl");
			अवरोध;
		हाल NETLBL_NLTYPE_CIPSOV4:
			BUG_ON(cipsov4 == शून्य);
			audit_log_क्रमmat(audit_buf,
					 " nlbl_protocol=cipsov4 cipso_doi=%u",
					 cipsov4->करोi);
			अवरोध;
		हाल NETLBL_NLTYPE_CALIPSO:
			BUG_ON(calipso == शून्य);
			audit_log_क्रमmat(audit_buf,
					 " nlbl_protocol=calipso calipso_doi=%u",
					 calipso->करोi);
			अवरोध;
		पूर्ण
		audit_log_क्रमmat(audit_buf, " res=%u", result == 0 ? 1 : 0);
		audit_log_end(audit_buf);
	पूर्ण
पूर्ण

/**
 * netlbl_करोmhsh_validate - Validate a new करोमुख्य mapping entry
 * @entry: the entry to validate
 *
 * This function validates the new करोमुख्य mapping entry to ensure that it is
 * a valid entry.  Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_करोmhsh_validate(स्थिर काष्ठा netlbl_करोm_map *entry)
अणु
	काष्ठा netlbl_af4list *iter4;
	काष्ठा netlbl_करोmaddr4_map *map4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा netlbl_af6list *iter6;
	काष्ठा netlbl_करोmaddr6_map *map6;
#पूर्ण_अगर /* IPv6 */

	अगर (entry == शून्य)
		वापस -EINVAL;

	अगर (entry->family != AF_INET && entry->family != AF_INET6 &&
	    (entry->family != AF_UNSPEC ||
	     entry->def.type != NETLBL_NLTYPE_UNLABELED))
		वापस -EINVAL;

	चयन (entry->def.type) अणु
	हाल NETLBL_NLTYPE_UNLABELED:
		अगर (entry->def.cipso != शून्य || entry->def.calipso != शून्य ||
		    entry->def.addrsel != शून्य)
			वापस -EINVAL;
		अवरोध;
	हाल NETLBL_NLTYPE_CIPSOV4:
		अगर (entry->family != AF_INET ||
		    entry->def.cipso == शून्य)
			वापस -EINVAL;
		अवरोध;
	हाल NETLBL_NLTYPE_CALIPSO:
		अगर (entry->family != AF_INET6 ||
		    entry->def.calipso == शून्य)
			वापस -EINVAL;
		अवरोध;
	हाल NETLBL_NLTYPE_ADDRSELECT:
		netlbl_af4list_क्रमeach(iter4, &entry->def.addrsel->list4) अणु
			map4 = netlbl_करोmhsh_addr4_entry(iter4);
			चयन (map4->def.type) अणु
			हाल NETLBL_NLTYPE_UNLABELED:
				अगर (map4->def.cipso != शून्य)
					वापस -EINVAL;
				अवरोध;
			हाल NETLBL_NLTYPE_CIPSOV4:
				अगर (map4->def.cipso == शून्य)
					वापस -EINVAL;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
		netlbl_af6list_क्रमeach(iter6, &entry->def.addrsel->list6) अणु
			map6 = netlbl_करोmhsh_addr6_entry(iter6);
			चयन (map6->def.type) अणु
			हाल NETLBL_NLTYPE_UNLABELED:
				अगर (map6->def.calipso != शून्य)
					वापस -EINVAL;
				अवरोध;
			हाल NETLBL_NLTYPE_CALIPSO:
				अगर (map6->def.calipso == शून्य)
					वापस -EINVAL;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण
#पूर्ण_अगर /* IPv6 */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Doमुख्य Hash Table Functions
 */

/**
 * netlbl_करोmhsh_init - Init क्रम the करोमुख्य hash
 * @size: the number of bits to use क्रम the hash buckets
 *
 * Description:
 * Initializes the करोमुख्य hash table, should be called only by
 * netlbl_user_init() during initialization.  Returns zero on success, non-zero
 * values on error.
 *
 */
पूर्णांक __init netlbl_करोmhsh_init(u32 size)
अणु
	u32 iter;
	काष्ठा netlbl_करोmhsh_tbl *hsh_tbl;

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

	spin_lock(&netlbl_करोmhsh_lock);
	rcu_assign_poपूर्णांकer(netlbl_करोmhsh, hsh_tbl);
	spin_unlock(&netlbl_करोmhsh_lock);

	वापस 0;
पूर्ण

/**
 * netlbl_करोmhsh_add - Adds a entry to the करोमुख्य hash table
 * @entry: the entry to add
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Adds a new entry to the करोमुख्य hash table and handles any updates to the
 * lower level protocol handler (i.e. CIPSO).  @entry->family may be set to
 * %AF_UNSPEC which will add an entry that matches all address families.  This
 * is only useful क्रम the unlabelled type and will only succeed अगर there is no
 * existing entry क्रम any address family with the same करोमुख्य.  Returns zero
 * on success, negative on failure.
 *
 */
पूर्णांक netlbl_करोmhsh_add(काष्ठा netlbl_करोm_map *entry,
		      काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val = 0;
	काष्ठा netlbl_करोm_map *entry_old, *entry_b;
	काष्ठा netlbl_af4list *iter4;
	काष्ठा netlbl_af4list *पंचांगp4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा netlbl_af6list *iter6;
	काष्ठा netlbl_af6list *पंचांगp6;
#पूर्ण_अगर /* IPv6 */

	ret_val = netlbl_करोmhsh_validate(entry);
	अगर (ret_val != 0)
		वापस ret_val;

	/* XXX - we can हटाओ this RCU पढ़ो lock as the spinlock protects the
	 *       entire function, but beक्रमe we करो we need to fixup the
	 *       netlbl_af[4,6]list RCU functions to करो "the right thing" with
	 *       respect to rcu_dereference() when only a spinlock is held. */
	rcu_पढ़ो_lock();
	spin_lock(&netlbl_करोmhsh_lock);
	अगर (entry->करोमुख्य != शून्य)
		entry_old = netlbl_करोmhsh_search(entry->करोमुख्य, entry->family);
	अन्यथा
		entry_old = netlbl_करोmhsh_search_def(entry->करोमुख्य,
						     entry->family);
	अगर (entry_old == शून्य) अणु
		entry->valid = 1;

		अगर (entry->करोमुख्य != शून्य) अणु
			u32 bkt = netlbl_करोmhsh_hash(entry->करोमुख्य);
			list_add_tail_rcu(&entry->list,
				    &rcu_dereference(netlbl_करोmhsh)->tbl[bkt]);
		पूर्ण अन्यथा अणु
			INIT_LIST_HEAD(&entry->list);
			चयन (entry->family) अणु
			हाल AF_INET:
				rcu_assign_poपूर्णांकer(netlbl_करोmhsh_def_ipv4,
						   entry);
				अवरोध;
			हाल AF_INET6:
				rcu_assign_poपूर्णांकer(netlbl_करोmhsh_def_ipv6,
						   entry);
				अवरोध;
			हाल AF_UNSPEC:
				अगर (entry->def.type !=
				    NETLBL_NLTYPE_UNLABELED) अणु
					ret_val = -EINVAL;
					जाओ add_वापस;
				पूर्ण
				entry_b = kzalloc(माप(*entry_b), GFP_ATOMIC);
				अगर (entry_b == शून्य) अणु
					ret_val = -ENOMEM;
					जाओ add_वापस;
				पूर्ण
				entry_b->family = AF_INET6;
				entry_b->def.type = NETLBL_NLTYPE_UNLABELED;
				entry_b->valid = 1;
				entry->family = AF_INET;
				rcu_assign_poपूर्णांकer(netlbl_करोmhsh_def_ipv4,
						   entry);
				rcu_assign_poपूर्णांकer(netlbl_करोmhsh_def_ipv6,
						   entry_b);
				अवरोध;
			शेष:
				/* Alपढ़ोy checked in
				 * netlbl_करोmhsh_validate(). */
				ret_val = -EINVAL;
				जाओ add_वापस;
			पूर्ण
		पूर्ण

		अगर (entry->def.type == NETLBL_NLTYPE_ADDRSELECT) अणु
			netlbl_af4list_क्रमeach_rcu(iter4,
						   &entry->def.addrsel->list4)
				netlbl_करोmhsh_audit_add(entry, iter4, शून्य,
							ret_val, audit_info);
#अगर IS_ENABLED(CONFIG_IPV6)
			netlbl_af6list_क्रमeach_rcu(iter6,
						   &entry->def.addrsel->list6)
				netlbl_करोmhsh_audit_add(entry, शून्य, iter6,
							ret_val, audit_info);
#पूर्ण_अगर /* IPv6 */
		पूर्ण अन्यथा
			netlbl_करोmhsh_audit_add(entry, शून्य, शून्य,
						ret_val, audit_info);
	पूर्ण अन्यथा अगर (entry_old->def.type == NETLBL_NLTYPE_ADDRSELECT &&
		   entry->def.type == NETLBL_NLTYPE_ADDRSELECT) अणु
		काष्ठा list_head *old_list4;
		काष्ठा list_head *old_list6;

		old_list4 = &entry_old->def.addrsel->list4;
		old_list6 = &entry_old->def.addrsel->list6;

		/* we only allow the addition of address selectors अगर all of
		 * the selectors करो not exist in the existing करोमुख्य map */
		netlbl_af4list_क्रमeach_rcu(iter4, &entry->def.addrsel->list4)
			अगर (netlbl_af4list_search_exact(iter4->addr,
							iter4->mask,
							old_list4)) अणु
				ret_val = -EEXIST;
				जाओ add_वापस;
			पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
		netlbl_af6list_क्रमeach_rcu(iter6, &entry->def.addrsel->list6)
			अगर (netlbl_af6list_search_exact(&iter6->addr,
							&iter6->mask,
							old_list6)) अणु
				ret_val = -EEXIST;
				जाओ add_वापस;
			पूर्ण
#पूर्ण_अगर /* IPv6 */

		netlbl_af4list_क्रमeach_safe(iter4, पंचांगp4,
					    &entry->def.addrsel->list4) अणु
			netlbl_af4list_हटाओ_entry(iter4);
			iter4->valid = 1;
			ret_val = netlbl_af4list_add(iter4, old_list4);
			netlbl_करोmhsh_audit_add(entry_old, iter4, शून्य,
						ret_val, audit_info);
			अगर (ret_val != 0)
				जाओ add_वापस;
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
		netlbl_af6list_क्रमeach_safe(iter6, पंचांगp6,
					    &entry->def.addrsel->list6) अणु
			netlbl_af6list_हटाओ_entry(iter6);
			iter6->valid = 1;
			ret_val = netlbl_af6list_add(iter6, old_list6);
			netlbl_करोmhsh_audit_add(entry_old, शून्य, iter6,
						ret_val, audit_info);
			अगर (ret_val != 0)
				जाओ add_वापस;
		पूर्ण
#पूर्ण_अगर /* IPv6 */
		/* cleanup the new entry since we've moved everything over */
		netlbl_करोmhsh_मुक्त_entry(&entry->rcu);
	पूर्ण अन्यथा
		ret_val = -EINVAL;

add_वापस:
	spin_unlock(&netlbl_करोmhsh_lock);
	rcu_पढ़ो_unlock();
	वापस ret_val;
पूर्ण

/**
 * netlbl_करोmhsh_add_शेष - Adds the शेष entry to the करोमुख्य hash table
 * @entry: the entry to add
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Adds a new शेष entry to the करोमुख्य hash table and handles any updates
 * to the lower level protocol handler (i.e. CIPSO).  Returns zero on success,
 * negative on failure.
 *
 */
पूर्णांक netlbl_करोmhsh_add_शेष(काष्ठा netlbl_करोm_map *entry,
			      काष्ठा netlbl_audit *audit_info)
अणु
	वापस netlbl_करोmhsh_add(entry, audit_info);
पूर्ण

/**
 * netlbl_करोmhsh_हटाओ_entry - Removes a given entry from the करोमुख्य table
 * @entry: the entry to हटाओ
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Removes an entry from the करोमुख्य hash table and handles any updates to the
 * lower level protocol handler (i.e. CIPSO).  Caller is responsible क्रम
 * ensuring that the RCU पढ़ो lock is held.  Returns zero on success, negative
 * on failure.
 *
 */
पूर्णांक netlbl_करोmhsh_हटाओ_entry(काष्ठा netlbl_करोm_map *entry,
			       काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val = 0;
	काष्ठा audit_buffer *audit_buf;
	काष्ठा netlbl_af4list *iter4;
	काष्ठा netlbl_करोmaddr4_map *map4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा netlbl_af6list *iter6;
	काष्ठा netlbl_करोmaddr6_map *map6;
#पूर्ण_अगर /* IPv6 */

	अगर (entry == शून्य)
		वापस -ENOENT;

	spin_lock(&netlbl_करोmhsh_lock);
	अगर (entry->valid) अणु
		entry->valid = 0;
		अगर (entry == rcu_dereference(netlbl_करोmhsh_def_ipv4))
			RCU_INIT_POINTER(netlbl_करोmhsh_def_ipv4, शून्य);
		अन्यथा अगर (entry == rcu_dereference(netlbl_करोmhsh_def_ipv6))
			RCU_INIT_POINTER(netlbl_करोmhsh_def_ipv6, शून्य);
		अन्यथा
			list_del_rcu(&entry->list);
	पूर्ण अन्यथा
		ret_val = -ENOENT;
	spin_unlock(&netlbl_करोmhsh_lock);

	अगर (ret_val)
		वापस ret_val;

	audit_buf = netlbl_audit_start_common(AUDIT_MAC_MAP_DEL, audit_info);
	अगर (audit_buf != शून्य) अणु
		audit_log_क्रमmat(audit_buf,
				 " nlbl_domain=%s res=1",
				 entry->करोमुख्य ? entry->करोमुख्य : "(default)");
		audit_log_end(audit_buf);
	पूर्ण

	चयन (entry->def.type) अणु
	हाल NETLBL_NLTYPE_ADDRSELECT:
		netlbl_af4list_क्रमeach_rcu(iter4, &entry->def.addrsel->list4) अणु
			map4 = netlbl_करोmhsh_addr4_entry(iter4);
			cipso_v4_करोi_putdef(map4->def.cipso);
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
		netlbl_af6list_क्रमeach_rcu(iter6, &entry->def.addrsel->list6) अणु
			map6 = netlbl_करोmhsh_addr6_entry(iter6);
			calipso_करोi_putdef(map6->def.calipso);
		पूर्ण
#पूर्ण_अगर /* IPv6 */
		अवरोध;
	हाल NETLBL_NLTYPE_CIPSOV4:
		cipso_v4_करोi_putdef(entry->def.cipso);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल NETLBL_NLTYPE_CALIPSO:
		calipso_करोi_putdef(entry->def.calipso);
		अवरोध;
#पूर्ण_अगर /* IPv6 */
	पूर्ण
	call_rcu(&entry->rcu, netlbl_करोmhsh_मुक्त_entry);

	वापस ret_val;
पूर्ण

/**
 * netlbl_करोmhsh_हटाओ_af4 - Removes an address selector entry
 * @करोमुख्य: the करोमुख्य
 * @addr: IPv4 address
 * @mask: IPv4 address mask
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Removes an inभागidual address selector from a करोमुख्य mapping and potentially
 * the entire mapping अगर it is empty.  Returns zero on success, negative values
 * on failure.
 *
 */
पूर्णांक netlbl_करोmhsh_हटाओ_af4(स्थिर अक्षर *करोमुख्य,
			     स्थिर काष्ठा in_addr *addr,
			     स्थिर काष्ठा in_addr *mask,
			     काष्ठा netlbl_audit *audit_info)
अणु
	काष्ठा netlbl_करोm_map *entry_map;
	काष्ठा netlbl_af4list *entry_addr;
	काष्ठा netlbl_af4list *iter4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा netlbl_af6list *iter6;
#पूर्ण_अगर /* IPv6 */
	काष्ठा netlbl_करोmaddr4_map *entry;

	rcu_पढ़ो_lock();

	अगर (करोमुख्य)
		entry_map = netlbl_करोmhsh_search(करोमुख्य, AF_INET);
	अन्यथा
		entry_map = netlbl_करोmhsh_search_def(करोमुख्य, AF_INET);
	अगर (entry_map == शून्य ||
	    entry_map->def.type != NETLBL_NLTYPE_ADDRSELECT)
		जाओ हटाओ_af4_failure;

	spin_lock(&netlbl_करोmhsh_lock);
	entry_addr = netlbl_af4list_हटाओ(addr->s_addr, mask->s_addr,
					   &entry_map->def.addrsel->list4);
	spin_unlock(&netlbl_करोmhsh_lock);

	अगर (entry_addr == शून्य)
		जाओ हटाओ_af4_failure;
	netlbl_af4list_क्रमeach_rcu(iter4, &entry_map->def.addrsel->list4)
		जाओ हटाओ_af4_single_addr;
#अगर IS_ENABLED(CONFIG_IPV6)
	netlbl_af6list_क्रमeach_rcu(iter6, &entry_map->def.addrsel->list6)
		जाओ हटाओ_af4_single_addr;
#पूर्ण_अगर /* IPv6 */
	/* the करोमुख्य mapping is empty so हटाओ it from the mapping table */
	netlbl_करोmhsh_हटाओ_entry(entry_map, audit_info);

हटाओ_af4_single_addr:
	rcu_पढ़ो_unlock();
	/* yick, we can't use call_rcu here because we don't have a rcu head
	 * poपूर्णांकer but hopefully this should be a rare हाल so the छोड़ो
	 * shouldn't be a problem */
	synchronize_rcu();
	entry = netlbl_करोmhsh_addr4_entry(entry_addr);
	cipso_v4_करोi_putdef(entry->def.cipso);
	kमुक्त(entry);
	वापस 0;

हटाओ_af4_failure:
	rcu_पढ़ो_unlock();
	वापस -ENOENT;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/**
 * netlbl_करोmhsh_हटाओ_af6 - Removes an address selector entry
 * @करोमुख्य: the करोमुख्य
 * @addr: IPv6 address
 * @mask: IPv6 address mask
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Removes an inभागidual address selector from a करोमुख्य mapping and potentially
 * the entire mapping अगर it is empty.  Returns zero on success, negative values
 * on failure.
 *
 */
पूर्णांक netlbl_करोmhsh_हटाओ_af6(स्थिर अक्षर *करोमुख्य,
			     स्थिर काष्ठा in6_addr *addr,
			     स्थिर काष्ठा in6_addr *mask,
			     काष्ठा netlbl_audit *audit_info)
अणु
	काष्ठा netlbl_करोm_map *entry_map;
	काष्ठा netlbl_af6list *entry_addr;
	काष्ठा netlbl_af4list *iter4;
	काष्ठा netlbl_af6list *iter6;
	काष्ठा netlbl_करोmaddr6_map *entry;

	rcu_पढ़ो_lock();

	अगर (करोमुख्य)
		entry_map = netlbl_करोmhsh_search(करोमुख्य, AF_INET6);
	अन्यथा
		entry_map = netlbl_करोmhsh_search_def(करोमुख्य, AF_INET6);
	अगर (entry_map == शून्य ||
	    entry_map->def.type != NETLBL_NLTYPE_ADDRSELECT)
		जाओ हटाओ_af6_failure;

	spin_lock(&netlbl_करोmhsh_lock);
	entry_addr = netlbl_af6list_हटाओ(addr, mask,
					   &entry_map->def.addrsel->list6);
	spin_unlock(&netlbl_करोmhsh_lock);

	अगर (entry_addr == शून्य)
		जाओ हटाओ_af6_failure;
	netlbl_af4list_क्रमeach_rcu(iter4, &entry_map->def.addrsel->list4)
		जाओ हटाओ_af6_single_addr;
	netlbl_af6list_क्रमeach_rcu(iter6, &entry_map->def.addrsel->list6)
		जाओ हटाओ_af6_single_addr;
	/* the करोमुख्य mapping is empty so हटाओ it from the mapping table */
	netlbl_करोmhsh_हटाओ_entry(entry_map, audit_info);

हटाओ_af6_single_addr:
	rcu_पढ़ो_unlock();
	/* yick, we can't use call_rcu here because we don't have a rcu head
	 * poपूर्णांकer but hopefully this should be a rare हाल so the छोड़ो
	 * shouldn't be a problem */
	synchronize_rcu();
	entry = netlbl_करोmhsh_addr6_entry(entry_addr);
	calipso_करोi_putdef(entry->def.calipso);
	kमुक्त(entry);
	वापस 0;

हटाओ_af6_failure:
	rcu_पढ़ो_unlock();
	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर /* IPv6 */

/**
 * netlbl_करोmhsh_हटाओ - Removes an entry from the करोमुख्य hash table
 * @करोमुख्य: the करोमुख्य to हटाओ
 * @family: address family
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Removes an entry from the करोमुख्य hash table and handles any updates to the
 * lower level protocol handler (i.e. CIPSO).  @family may be %AF_UNSPEC which
 * हटाओs all address family entries.  Returns zero on success, negative on
 * failure.
 *
 */
पूर्णांक netlbl_करोmhsh_हटाओ(स्थिर अक्षर *करोमुख्य, u16 family,
			 काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val = -EINVAL;
	काष्ठा netlbl_करोm_map *entry;

	rcu_पढ़ो_lock();

	अगर (family == AF_INET || family == AF_UNSPEC) अणु
		अगर (करोमुख्य)
			entry = netlbl_करोmhsh_search(करोमुख्य, AF_INET);
		अन्यथा
			entry = netlbl_करोmhsh_search_def(करोमुख्य, AF_INET);
		ret_val = netlbl_करोmhsh_हटाओ_entry(entry, audit_info);
		अगर (ret_val && ret_val != -ENOENT)
			जाओ करोne;
	पूर्ण
	अगर (family == AF_INET6 || family == AF_UNSPEC) अणु
		पूर्णांक ret_val2;

		अगर (करोमुख्य)
			entry = netlbl_करोmhsh_search(करोमुख्य, AF_INET6);
		अन्यथा
			entry = netlbl_करोmhsh_search_def(करोमुख्य, AF_INET6);
		ret_val2 = netlbl_करोmhsh_हटाओ_entry(entry, audit_info);
		अगर (ret_val2 != -ENOENT)
			ret_val = ret_val2;
	पूर्ण
करोne:
	rcu_पढ़ो_unlock();

	वापस ret_val;
पूर्ण

/**
 * netlbl_करोmhsh_हटाओ_शेष - Removes the शेष entry from the table
 * @family: address family
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Removes/resets the शेष entry corresponding to @family from the करोमुख्य
 * hash table and handles any updates to the lower level protocol handler
 * (i.e. CIPSO).  @family may be %AF_UNSPEC which हटाओs all address family
 * entries.  Returns zero on success, negative on failure.
 *
 */
पूर्णांक netlbl_करोmhsh_हटाओ_शेष(u16 family, काष्ठा netlbl_audit *audit_info)
अणु
	वापस netlbl_करोmhsh_हटाओ(शून्य, family, audit_info);
पूर्ण

/**
 * netlbl_करोmhsh_getentry - Get an entry from the करोमुख्य hash table
 * @करोमुख्य: the करोमुख्य name to search क्रम
 * @family: address family
 *
 * Description:
 * Look through the करोमुख्य hash table searching क्रम an entry to match @करोमुख्य,
 * with address family @family, वापस a poपूर्णांकer to a copy of the entry or
 * शून्य.  The caller is responsible क्रम ensuring that rcu_पढ़ो_[un]lock() is
 * called.
 *
 */
काष्ठा netlbl_करोm_map *netlbl_करोmhsh_getentry(स्थिर अक्षर *करोमुख्य, u16 family)
अणु
	अगर (family == AF_UNSPEC)
		वापस शून्य;
	वापस netlbl_करोmhsh_search_def(करोमुख्य, family);
पूर्ण

/**
 * netlbl_करोmhsh_getentry_af4 - Get an entry from the करोमुख्य hash table
 * @करोमुख्य: the करोमुख्य name to search क्रम
 * @addr: the IP address to search क्रम
 *
 * Description:
 * Look through the करोमुख्य hash table searching क्रम an entry to match @करोमुख्य
 * and @addr, वापस a poपूर्णांकer to a copy of the entry or शून्य.  The caller is
 * responsible क्रम ensuring that rcu_पढ़ो_[un]lock() is called.
 *
 */
काष्ठा netlbl_करोmmap_def *netlbl_करोmhsh_getentry_af4(स्थिर अक्षर *करोमुख्य,
						     __be32 addr)
अणु
	काष्ठा netlbl_करोm_map *करोm_iter;
	काष्ठा netlbl_af4list *addr_iter;

	करोm_iter = netlbl_करोmhsh_search_def(करोमुख्य, AF_INET);
	अगर (करोm_iter == शून्य)
		वापस शून्य;

	अगर (करोm_iter->def.type != NETLBL_NLTYPE_ADDRSELECT)
		वापस &करोm_iter->def;
	addr_iter = netlbl_af4list_search(addr, &करोm_iter->def.addrsel->list4);
	अगर (addr_iter == शून्य)
		वापस शून्य;
	वापस &(netlbl_करोmhsh_addr4_entry(addr_iter)->def);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/**
 * netlbl_करोmhsh_getentry_af6 - Get an entry from the करोमुख्य hash table
 * @करोमुख्य: the करोमुख्य name to search क्रम
 * @addr: the IP address to search क्रम
 *
 * Description:
 * Look through the करोमुख्य hash table searching क्रम an entry to match @करोमुख्य
 * and @addr, वापस a poपूर्णांकer to a copy of the entry or शून्य.  The caller is
 * responsible क्रम ensuring that rcu_पढ़ो_[un]lock() is called.
 *
 */
काष्ठा netlbl_करोmmap_def *netlbl_करोmhsh_getentry_af6(स्थिर अक्षर *करोमुख्य,
						   स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा netlbl_करोm_map *करोm_iter;
	काष्ठा netlbl_af6list *addr_iter;

	करोm_iter = netlbl_करोmhsh_search_def(करोमुख्य, AF_INET6);
	अगर (करोm_iter == शून्य)
		वापस शून्य;

	अगर (करोm_iter->def.type != NETLBL_NLTYPE_ADDRSELECT)
		वापस &करोm_iter->def;
	addr_iter = netlbl_af6list_search(addr, &करोm_iter->def.addrsel->list6);
	अगर (addr_iter == शून्य)
		वापस शून्य;
	वापस &(netlbl_करोmhsh_addr6_entry(addr_iter)->def);
पूर्ण
#पूर्ण_अगर /* IPv6 */

/**
 * netlbl_करोmhsh_walk - Iterate through the करोमुख्य mapping hash table
 * @skip_bkt: the number of buckets to skip at the start
 * @skip_chain: the number of entries to skip in the first iterated bucket
 * @callback: callback क्रम each entry
 * @cb_arg: argument क्रम the callback function
 *
 * Description:
 * Interate over the करोमुख्य mapping hash table, skipping the first @skip_bkt
 * buckets and @skip_chain entries.  For each entry in the table call
 * @callback, अगर @callback वापसs a negative value stop 'walking' through the
 * table and वापस.  Updates the values in @skip_bkt and @skip_chain on
 * वापस.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक netlbl_करोmhsh_walk(u32 *skip_bkt,
		     u32 *skip_chain,
		     पूर्णांक (*callback) (काष्ठा netlbl_करोm_map *entry, व्योम *arg),
		     व्योम *cb_arg)
अणु
	पूर्णांक ret_val = -ENOENT;
	u32 iter_bkt;
	काष्ठा list_head *iter_list;
	काष्ठा netlbl_करोm_map *iter_entry;
	u32 chain_cnt = 0;

	rcu_पढ़ो_lock();
	क्रम (iter_bkt = *skip_bkt;
	     iter_bkt < rcu_dereference(netlbl_करोmhsh)->size;
	     iter_bkt++, chain_cnt = 0) अणु
		iter_list = &rcu_dereference(netlbl_करोmhsh)->tbl[iter_bkt];
		list_क्रम_each_entry_rcu(iter_entry, iter_list, list)
			अगर (iter_entry->valid) अणु
				अगर (chain_cnt++ < *skip_chain)
					जारी;
				ret_val = callback(iter_entry, cb_arg);
				अगर (ret_val < 0) अणु
					chain_cnt--;
					जाओ walk_वापस;
				पूर्ण
			पूर्ण
	पूर्ण

walk_वापस:
	rcu_पढ़ो_unlock();
	*skip_bkt = iter_bkt;
	*skip_chain = chain_cnt;
	वापस ret_val;
पूर्ण
