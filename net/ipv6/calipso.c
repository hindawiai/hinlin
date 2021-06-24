<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CALIPSO - Common Architecture Label IPv6 Security Option
 *
 * This is an implementation of the CALIPSO protocol as specअगरied in
 * RFC 5570.
 *
 * Authors: Paul Moore <paul.moore@hp.com>
 *          Huw Davies <huw@codeweavers.com>
 */

/* (c) Copyright Hewlett-Packard Development Company, L.P., 2006, 2008
 * (c) Copyright Huw Davies <huw@codeweavers.com>, 2015
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/jhash.h>
#समावेश <linux/audit.h>
#समावेश <linux/slab.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/tcp.h>
#समावेश <net/netlabel.h>
#समावेश <net/calipso.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bug.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/crc-ccitt.h>

/* Maximium size of the calipso option including
 * the two-byte TLV header.
 */
#घोषणा CALIPSO_OPT_LEN_MAX (2 + 252)

/* Size of the minimum calipso option including
 * the two-byte TLV header.
 */
#घोषणा CALIPSO_HDR_LEN (2 + 8)

/* Maximium size of the calipso option including
 * the two-byte TLV header and upto 3 bytes of
 * leading pad and 7 bytes of trailing pad.
 */
#घोषणा CALIPSO_OPT_LEN_MAX_WITH_PAD (3 + CALIPSO_OPT_LEN_MAX + 7)

 /* Maximium size of u32 aligned buffer required to hold calipso
  * option.  Max of 3 initial pad bytes starting from buffer + 3.
  * i.e. the worst हाल is when the previous tlv finishes on 4n + 3.
  */
#घोषणा CALIPSO_MAX_BUFFER (6 + CALIPSO_OPT_LEN_MAX)

/* List of available DOI definitions */
अटल DEFINE_SPINLOCK(calipso_करोi_list_lock);
अटल LIST_HEAD(calipso_करोi_list);

/* Label mapping cache */
पूर्णांक calipso_cache_enabled = 1;
पूर्णांक calipso_cache_bucketsize = 10;
#घोषणा CALIPSO_CACHE_BUCKETBITS     7
#घोषणा CALIPSO_CACHE_BUCKETS        BIT(CALIPSO_CACHE_BUCKETBITS)
#घोषणा CALIPSO_CACHE_REORDERLIMIT   10
काष्ठा calipso_map_cache_bkt अणु
	spinlock_t lock;
	u32 size;
	काष्ठा list_head list;
पूर्ण;

काष्ठा calipso_map_cache_entry अणु
	u32 hash;
	अचिन्हित अक्षर *key;
	माप_प्रकार key_len;

	काष्ठा netlbl_lsm_cache *lsm_data;

	u32 activity;
	काष्ठा list_head list;
पूर्ण;

अटल काष्ठा calipso_map_cache_bkt *calipso_cache;

अटल व्योम calipso_cache_invalidate(व्योम);
अटल व्योम calipso_करोi_putdef(काष्ठा calipso_करोi *करोi_def);

/* Label Mapping Cache Functions
 */

/**
 * calipso_cache_entry_मुक्त - Frees a cache entry
 * @entry: the entry to मुक्त
 *
 * Description:
 * This function मुक्तs the memory associated with a cache entry including the
 * LSM cache data अगर there are no दीर्घer any users, i.e. reference count == 0.
 *
 */
अटल व्योम calipso_cache_entry_मुक्त(काष्ठा calipso_map_cache_entry *entry)
अणु
	अगर (entry->lsm_data)
		netlbl_secattr_cache_मुक्त(entry->lsm_data);
	kमुक्त(entry->key);
	kमुक्त(entry);
पूर्ण

/**
 * calipso_map_cache_hash - Hashing function क्रम the CALIPSO cache
 * @key: the hash key
 * @key_len: the length of the key in bytes
 *
 * Description:
 * The CALIPSO tag hashing function.  Returns a 32-bit hash value.
 *
 */
अटल u32 calipso_map_cache_hash(स्थिर अचिन्हित अक्षर *key, u32 key_len)
अणु
	वापस jhash(key, key_len, 0);
पूर्ण

/**
 * calipso_cache_init - Initialize the CALIPSO cache
 *
 * Description:
 * Initializes the CALIPSO label mapping cache, this function should be called
 * beक्रमe any of the other functions defined in this file.  Returns zero on
 * success, negative values on error.
 *
 */
अटल पूर्णांक __init calipso_cache_init(व्योम)
अणु
	u32 iter;

	calipso_cache = kसुस्मृति(CALIPSO_CACHE_BUCKETS,
				माप(काष्ठा calipso_map_cache_bkt),
				GFP_KERNEL);
	अगर (!calipso_cache)
		वापस -ENOMEM;

	क्रम (iter = 0; iter < CALIPSO_CACHE_BUCKETS; iter++) अणु
		spin_lock_init(&calipso_cache[iter].lock);
		calipso_cache[iter].size = 0;
		INIT_LIST_HEAD(&calipso_cache[iter].list);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * calipso_cache_invalidate - Invalidates the current CALIPSO cache
 *
 * Description:
 * Invalidates and मुक्तs any entries in the CALIPSO cache.  Returns zero on
 * success and negative values on failure.
 *
 */
अटल व्योम calipso_cache_invalidate(व्योम)
अणु
	काष्ठा calipso_map_cache_entry *entry, *पंचांगp_entry;
	u32 iter;

	क्रम (iter = 0; iter < CALIPSO_CACHE_BUCKETS; iter++) अणु
		spin_lock_bh(&calipso_cache[iter].lock);
		list_क्रम_each_entry_safe(entry,
					 पंचांगp_entry,
					 &calipso_cache[iter].list, list) अणु
			list_del(&entry->list);
			calipso_cache_entry_मुक्त(entry);
		पूर्ण
		calipso_cache[iter].size = 0;
		spin_unlock_bh(&calipso_cache[iter].lock);
	पूर्ण
पूर्ण

/**
 * calipso_cache_check - Check the CALIPSO cache क्रम a label mapping
 * @key: the buffer to check
 * @key_len: buffer length in bytes
 * @secattr: the security attribute काष्ठा to use
 *
 * Description:
 * This function checks the cache to see अगर a label mapping alपढ़ोy exists क्रम
 * the given key.  If there is a match then the cache is adjusted and the
 * @secattr काष्ठा is populated with the correct LSM security attributes.  The
 * cache is adjusted in the following manner अगर the entry is not alपढ़ोy the
 * first in the cache bucket:
 *
 *  1. The cache entry's activity counter is incremented
 *  2. The previous (higher ranking) entry's activity counter is decremented
 *  3. If the dअगरference between the two activity counters is geater than
 *     CALIPSO_CACHE_REORDERLIMIT the two entries are swapped
 *
 * Returns zero on success, -ENOENT क्रम a cache miss, and other negative values
 * on error.
 *
 */
अटल पूर्णांक calipso_cache_check(स्थिर अचिन्हित अक्षर *key,
			       u32 key_len,
			       काष्ठा netlbl_lsm_secattr *secattr)
अणु
	u32 bkt;
	काष्ठा calipso_map_cache_entry *entry;
	काष्ठा calipso_map_cache_entry *prev_entry = शून्य;
	u32 hash;

	अगर (!calipso_cache_enabled)
		वापस -ENOENT;

	hash = calipso_map_cache_hash(key, key_len);
	bkt = hash & (CALIPSO_CACHE_BUCKETS - 1);
	spin_lock_bh(&calipso_cache[bkt].lock);
	list_क्रम_each_entry(entry, &calipso_cache[bkt].list, list) अणु
		अगर (entry->hash == hash &&
		    entry->key_len == key_len &&
		    स_भेद(entry->key, key, key_len) == 0) अणु
			entry->activity += 1;
			refcount_inc(&entry->lsm_data->refcount);
			secattr->cache = entry->lsm_data;
			secattr->flags |= NETLBL_SECATTR_CACHE;
			secattr->type = NETLBL_NLTYPE_CALIPSO;
			अगर (!prev_entry) अणु
				spin_unlock_bh(&calipso_cache[bkt].lock);
				वापस 0;
			पूर्ण

			अगर (prev_entry->activity > 0)
				prev_entry->activity -= 1;
			अगर (entry->activity > prev_entry->activity &&
			    entry->activity - prev_entry->activity >
			    CALIPSO_CACHE_REORDERLIMIT) अणु
				__list_del(entry->list.prev, entry->list.next);
				__list_add(&entry->list,
					   prev_entry->list.prev,
					   &prev_entry->list);
			पूर्ण

			spin_unlock_bh(&calipso_cache[bkt].lock);
			वापस 0;
		पूर्ण
		prev_entry = entry;
	पूर्ण
	spin_unlock_bh(&calipso_cache[bkt].lock);

	वापस -ENOENT;
पूर्ण

/**
 * calipso_cache_add - Add an entry to the CALIPSO cache
 * @calipso_ptr: the CALIPSO option
 * @secattr: the packet's security attributes
 *
 * Description:
 * Add a new entry पूर्णांकo the CALIPSO label mapping cache.  Add the new entry to
 * head of the cache bucket's list, अगर the cache bucket is out of room हटाओ
 * the last entry in the list first.  It is important to note that there is
 * currently no checking क्रम duplicate keys.  Returns zero on success,
 * negative values on failure.  The key stored starts at calipso_ptr + 2,
 * i.e. the type and length bytes are not stored, this corresponds to
 * calipso_ptr[1] bytes of data.
 *
 */
अटल पूर्णांक calipso_cache_add(स्थिर अचिन्हित अक्षर *calipso_ptr,
			     स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val = -EPERM;
	u32 bkt;
	काष्ठा calipso_map_cache_entry *entry = शून्य;
	काष्ठा calipso_map_cache_entry *old_entry = शून्य;
	u32 calipso_ptr_len;

	अगर (!calipso_cache_enabled || calipso_cache_bucketsize <= 0)
		वापस 0;

	calipso_ptr_len = calipso_ptr[1];

	entry = kzalloc(माप(*entry), GFP_ATOMIC);
	अगर (!entry)
		वापस -ENOMEM;
	entry->key = kmemdup(calipso_ptr + 2, calipso_ptr_len, GFP_ATOMIC);
	अगर (!entry->key) अणु
		ret_val = -ENOMEM;
		जाओ cache_add_failure;
	पूर्ण
	entry->key_len = calipso_ptr_len;
	entry->hash = calipso_map_cache_hash(calipso_ptr, calipso_ptr_len);
	refcount_inc(&secattr->cache->refcount);
	entry->lsm_data = secattr->cache;

	bkt = entry->hash & (CALIPSO_CACHE_BUCKETS - 1);
	spin_lock_bh(&calipso_cache[bkt].lock);
	अगर (calipso_cache[bkt].size < calipso_cache_bucketsize) अणु
		list_add(&entry->list, &calipso_cache[bkt].list);
		calipso_cache[bkt].size += 1;
	पूर्ण अन्यथा अणु
		old_entry = list_entry(calipso_cache[bkt].list.prev,
				       काष्ठा calipso_map_cache_entry, list);
		list_del(&old_entry->list);
		list_add(&entry->list, &calipso_cache[bkt].list);
		calipso_cache_entry_मुक्त(old_entry);
	पूर्ण
	spin_unlock_bh(&calipso_cache[bkt].lock);

	वापस 0;

cache_add_failure:
	अगर (entry)
		calipso_cache_entry_मुक्त(entry);
	वापस ret_val;
पूर्ण

/* DOI List Functions
 */

/**
 * calipso_करोi_search - Searches क्रम a DOI definition
 * @करोi: the DOI to search क्रम
 *
 * Description:
 * Search the DOI definition list क्रम a DOI definition with a DOI value that
 * matches @करोi.  The caller is responsible क्रम calling rcu_पढ़ो_[un]lock().
 * Returns a poपूर्णांकer to the DOI definition on success and शून्य on failure.
 */
अटल काष्ठा calipso_करोi *calipso_करोi_search(u32 करोi)
अणु
	काष्ठा calipso_करोi *iter;

	list_क्रम_each_entry_rcu(iter, &calipso_करोi_list, list)
		अगर (iter->करोi == करोi && refcount_पढ़ो(&iter->refcount))
			वापस iter;
	वापस शून्य;
पूर्ण

/**
 * calipso_करोi_add - Add a new DOI to the CALIPSO protocol engine
 * @करोi_def: the DOI काष्ठाure
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * The caller defines a new DOI क्रम use by the CALIPSO engine and calls this
 * function to add it to the list of acceptable करोमुख्यs.  The caller must
 * ensure that the mapping table specअगरied in @करोi_def->map meets all of the
 * requirements of the mapping type (see calipso.h क्रम details).  Returns
 * zero on success and non-zero on failure.
 *
 */
अटल पूर्णांक calipso_करोi_add(काष्ठा calipso_करोi *करोi_def,
			   काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val = -EINVAL;
	u32 करोi;
	u32 करोi_type;
	काष्ठा audit_buffer *audit_buf;

	करोi = करोi_def->करोi;
	करोi_type = करोi_def->type;

	अगर (करोi_def->करोi == CALIPSO_DOI_UNKNOWN)
		जाओ करोi_add_वापस;

	refcount_set(&करोi_def->refcount, 1);

	spin_lock(&calipso_करोi_list_lock);
	अगर (calipso_करोi_search(करोi_def->करोi)) अणु
		spin_unlock(&calipso_करोi_list_lock);
		ret_val = -EEXIST;
		जाओ करोi_add_वापस;
	पूर्ण
	list_add_tail_rcu(&करोi_def->list, &calipso_करोi_list);
	spin_unlock(&calipso_करोi_list_lock);
	ret_val = 0;

करोi_add_वापस:
	audit_buf = netlbl_audit_start(AUDIT_MAC_CALIPSO_ADD, audit_info);
	अगर (audit_buf) अणु
		स्थिर अक्षर *type_str;

		चयन (करोi_type) अणु
		हाल CALIPSO_MAP_PASS:
			type_str = "pass";
			अवरोध;
		शेष:
			type_str = "(unknown)";
		पूर्ण
		audit_log_क्रमmat(audit_buf,
				 " calipso_doi=%u calipso_type=%s res=%u",
				 करोi, type_str, ret_val == 0 ? 1 : 0);
		audit_log_end(audit_buf);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * calipso_करोi_मुक्त - Frees a DOI definition
 * @करोi_def: the DOI definition
 *
 * Description:
 * This function मुक्तs all of the memory associated with a DOI definition.
 *
 */
अटल व्योम calipso_करोi_मुक्त(काष्ठा calipso_करोi *करोi_def)
अणु
	kमुक्त(करोi_def);
पूर्ण

/**
 * calipso_करोi_मुक्त_rcu - Frees a DOI definition via the RCU poपूर्णांकer
 * @entry: the entry's RCU field
 *
 * Description:
 * This function is deचिन्हित to be used as a callback to the call_rcu()
 * function so that the memory allocated to the DOI definition can be released
 * safely.
 *
 */
अटल व्योम calipso_करोi_मुक्त_rcu(काष्ठा rcu_head *entry)
अणु
	काष्ठा calipso_करोi *करोi_def;

	करोi_def = container_of(entry, काष्ठा calipso_करोi, rcu);
	calipso_करोi_मुक्त(करोi_def);
पूर्ण

/**
 * calipso_करोi_हटाओ - Remove an existing DOI from the CALIPSO protocol engine
 * @करोi: the DOI value
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Removes a DOI definition from the CALIPSO engine.  The NetLabel routines will
 * be called to release their own LSM करोमुख्य mappings as well as our own
 * करोमुख्य list.  Returns zero on success and negative values on failure.
 *
 */
अटल पूर्णांक calipso_करोi_हटाओ(u32 करोi, काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val;
	काष्ठा calipso_करोi *करोi_def;
	काष्ठा audit_buffer *audit_buf;

	spin_lock(&calipso_करोi_list_lock);
	करोi_def = calipso_करोi_search(करोi);
	अगर (!करोi_def) अणु
		spin_unlock(&calipso_करोi_list_lock);
		ret_val = -ENOENT;
		जाओ करोi_हटाओ_वापस;
	पूर्ण
	list_del_rcu(&करोi_def->list);
	spin_unlock(&calipso_करोi_list_lock);

	calipso_करोi_putdef(करोi_def);
	ret_val = 0;

करोi_हटाओ_वापस:
	audit_buf = netlbl_audit_start(AUDIT_MAC_CALIPSO_DEL, audit_info);
	अगर (audit_buf) अणु
		audit_log_क्रमmat(audit_buf,
				 " calipso_doi=%u res=%u",
				 करोi, ret_val == 0 ? 1 : 0);
		audit_log_end(audit_buf);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * calipso_करोi_getdef - Returns a reference to a valid DOI definition
 * @करोi: the DOI value
 *
 * Description:
 * Searches क्रम a valid DOI definition and अगर one is found it is वापसed to
 * the caller.  Otherwise शून्य is वापसed.  The caller must ensure that
 * calipso_करोi_putdef() is called when the caller is करोne.
 *
 */
अटल काष्ठा calipso_करोi *calipso_करोi_getdef(u32 करोi)
अणु
	काष्ठा calipso_करोi *करोi_def;

	rcu_पढ़ो_lock();
	करोi_def = calipso_करोi_search(करोi);
	अगर (!करोi_def)
		जाओ करोi_getdef_वापस;
	अगर (!refcount_inc_not_zero(&करोi_def->refcount))
		करोi_def = शून्य;

करोi_getdef_वापस:
	rcu_पढ़ो_unlock();
	वापस करोi_def;
पूर्ण

/**
 * calipso_करोi_putdef - Releases a reference क्रम the given DOI definition
 * @करोi_def: the DOI definition
 *
 * Description:
 * Releases a DOI definition reference obtained from calipso_करोi_getdef().
 *
 */
अटल व्योम calipso_करोi_putdef(काष्ठा calipso_करोi *करोi_def)
अणु
	अगर (!करोi_def)
		वापस;

	अगर (!refcount_dec_and_test(&करोi_def->refcount))
		वापस;

	calipso_cache_invalidate();
	call_rcu(&करोi_def->rcu, calipso_करोi_मुक्त_rcu);
पूर्ण

/**
 * calipso_करोi_walk - Iterate through the DOI definitions
 * @skip_cnt: skip past this number of DOI definitions, updated
 * @callback: callback क्रम each DOI definition
 * @cb_arg: argument क्रम the callback function
 *
 * Description:
 * Iterate over the DOI definition list, skipping the first @skip_cnt entries.
 * For each entry call @callback, अगर @callback वापसs a negative value stop
 * 'walking' through the list and वापस.  Updates the value in @skip_cnt upon
 * वापस.  Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक calipso_करोi_walk(u32 *skip_cnt,
			    पूर्णांक (*callback)(काष्ठा calipso_करोi *करोi_def,
					    व्योम *arg),
			    व्योम *cb_arg)
अणु
	पूर्णांक ret_val = -ENOENT;
	u32 करोi_cnt = 0;
	काष्ठा calipso_करोi *iter_करोi;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(iter_करोi, &calipso_करोi_list, list)
		अगर (refcount_पढ़ो(&iter_करोi->refcount) > 0) अणु
			अगर (करोi_cnt++ < *skip_cnt)
				जारी;
			ret_val = callback(iter_करोi, cb_arg);
			अगर (ret_val < 0) अणु
				करोi_cnt--;
				जाओ करोi_walk_वापस;
			पूर्ण
		पूर्ण

करोi_walk_वापस:
	rcu_पढ़ो_unlock();
	*skip_cnt = करोi_cnt;
	वापस ret_val;
पूर्ण

/**
 * calipso_validate - Validate a CALIPSO option
 * @skb: the packet
 * @option: the start of the option
 *
 * Description:
 * This routine is called to validate a CALIPSO option.
 * If the option is valid then %true is वापसed, otherwise
 * %false is वापसed.
 *
 * The caller should have alपढ़ोy checked that the length of the
 * option (including the TLV header) is >= 10 and that the caपंचांगap
 * length is consistent with the option length.
 *
 * We leave checks on the level and categories to the socket layer.
 */
bool calipso_validate(स्थिर काष्ठा sk_buff *skb, स्थिर अचिन्हित अक्षर *option)
अणु
	काष्ठा calipso_करोi *करोi_def;
	bool ret_val;
	u16 crc, len = option[1] + 2;
	अटल स्थिर u8 zero[2];

	/* The original CRC runs over the option including the TLV header
	 * with the CRC-16 field (at offset 8) zeroed out. */
	crc = crc_ccitt(0xffff, option, 8);
	crc = crc_ccitt(crc, zero, माप(zero));
	अगर (len > 10)
		crc = crc_ccitt(crc, option + 10, len - 10);
	crc = ~crc;
	अगर (option[8] != (crc & 0xff) || option[9] != ((crc >> 8) & 0xff))
		वापस false;

	rcu_पढ़ो_lock();
	करोi_def = calipso_करोi_search(get_unaligned_be32(option + 2));
	ret_val = !!करोi_def;
	rcu_पढ़ो_unlock();

	वापस ret_val;
पूर्ण

/**
 * calipso_map_cat_hton - Perक्रमm a category mapping from host to network
 * @करोi_def: the DOI definition
 * @secattr: the security attributes
 * @net_cat: the zero'd out category biपंचांगap in network/CALIPSO क्रमmat
 * @net_cat_len: the length of the CALIPSO biपंचांगap in bytes
 *
 * Description:
 * Perक्रमm a label mapping to translate a local MLS category biपंचांगap to the
 * correct CALIPSO biपंचांगap using the given DOI definition.  Returns the minimum
 * size in bytes of the network biपंचांगap on success, negative values otherwise.
 *
 */
अटल पूर्णांक calipso_map_cat_hton(स्थिर काष्ठा calipso_करोi *करोi_def,
				स्थिर काष्ठा netlbl_lsm_secattr *secattr,
				अचिन्हित अक्षर *net_cat,
				u32 net_cat_len)
अणु
	पूर्णांक spot = -1;
	u32 net_spot_max = 0;
	u32 net_clen_bits = net_cat_len * 8;

	क्रम (;;) अणु
		spot = netlbl_caपंचांगap_walk(secattr->attr.mls.cat,
					  spot + 1);
		अगर (spot < 0)
			अवरोध;
		अगर (spot >= net_clen_bits)
			वापस -ENOSPC;
		netlbl_biपंचांगap_setbit(net_cat, spot, 1);

		अगर (spot > net_spot_max)
			net_spot_max = spot;
	पूर्ण

	वापस (net_spot_max / 32 + 1) * 4;
पूर्ण

/**
 * calipso_map_cat_ntoh - Perक्रमm a category mapping from network to host
 * @करोi_def: the DOI definition
 * @net_cat: the category biपंचांगap in network/CALIPSO क्रमmat
 * @net_cat_len: the length of the CALIPSO biपंचांगap in bytes
 * @secattr: the security attributes
 *
 * Description:
 * Perक्रमm a label mapping to translate a CALIPSO biपंचांगap to the correct local
 * MLS category biपंचांगap using the given DOI definition.  Returns zero on
 * success, negative values on failure.
 *
 */
अटल पूर्णांक calipso_map_cat_ntoh(स्थिर काष्ठा calipso_करोi *करोi_def,
				स्थिर अचिन्हित अक्षर *net_cat,
				u32 net_cat_len,
				काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	पूर्णांक spot = -1;
	u32 net_clen_bits = net_cat_len * 8;

	क्रम (;;) अणु
		spot = netlbl_biपंचांगap_walk(net_cat,
					  net_clen_bits,
					  spot + 1,
					  1);
		अगर (spot < 0) अणु
			अगर (spot == -2)
				वापस -EFAULT;
			वापस 0;
		पूर्ण

		ret_val = netlbl_caपंचांगap_setbit(&secattr->attr.mls.cat,
					       spot,
					       GFP_ATOMIC);
		अगर (ret_val != 0)
			वापस ret_val;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * calipso_pad_ग_लिखो - Writes pad bytes in TLV क्रमmat
 * @buf: the buffer
 * @offset: offset from start of buffer to ग_लिखो padding
 * @count: number of pad bytes to ग_लिखो
 *
 * Description:
 * Write @count bytes of TLV padding पूर्णांकo @buffer starting at offset @offset.
 * @count should be less than 8 - see RFC 4942.
 *
 */
अटल पूर्णांक calipso_pad_ग_लिखो(अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक offset,
			     अचिन्हित पूर्णांक count)
अणु
	अगर (WARN_ON_ONCE(count >= 8))
		वापस -EINVAL;

	चयन (count) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		buf[offset] = IPV6_TLV_PAD1;
		अवरोध;
	शेष:
		buf[offset] = IPV6_TLV_PADN;
		buf[offset + 1] = count - 2;
		अगर (count > 2)
			स_रखो(buf + offset + 2, 0, count - 2);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * calipso_genopt - Generate a CALIPSO option
 * @buf: the option buffer
 * @start: offset from which to ग_लिखो
 * @buf_len: the size of opt_buf
 * @करोi_def: the CALIPSO DOI to use
 * @secattr: the security attributes
 *
 * Description:
 * Generate a CALIPSO option using the DOI definition and security attributes
 * passed to the function. This also generates upto three bytes of leading
 * padding that ensures that the option is 4n + 2 aligned.  It वापसs the
 * number of bytes written (including any initial padding).
 */
अटल पूर्णांक calipso_genopt(अचिन्हित अक्षर *buf, u32 start, u32 buf_len,
			  स्थिर काष्ठा calipso_करोi *करोi_def,
			  स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	u32 len, pad;
	u16 crc;
	अटल स्थिर अचिन्हित अक्षर padding[4] = अणु2, 1, 0, 3पूर्ण;
	अचिन्हित अक्षर *calipso;

	/* CALIPSO has 4n + 2 alignment */
	pad = padding[start & 3];
	अगर (buf_len <= start + pad + CALIPSO_HDR_LEN)
		वापस -ENOSPC;

	अगर ((secattr->flags & NETLBL_SECATTR_MLS_LVL) == 0)
		वापस -EPERM;

	len = CALIPSO_HDR_LEN;

	अगर (secattr->flags & NETLBL_SECATTR_MLS_CAT) अणु
		ret_val = calipso_map_cat_hton(करोi_def,
					       secattr,
					       buf + start + pad + len,
					       buf_len - start - pad - len);
		अगर (ret_val < 0)
			वापस ret_val;
		len += ret_val;
	पूर्ण

	calipso_pad_ग_लिखो(buf, start, pad);
	calipso = buf + start + pad;

	calipso[0] = IPV6_TLV_CALIPSO;
	calipso[1] = len - 2;
	*(__be32 *)(calipso + 2) = htonl(करोi_def->करोi);
	calipso[6] = (len - CALIPSO_HDR_LEN) / 4;
	calipso[7] = secattr->attr.mls.lvl;
	crc = ~crc_ccitt(0xffff, calipso, len);
	calipso[8] = crc & 0xff;
	calipso[9] = (crc >> 8) & 0xff;
	वापस pad + len;
पूर्ण

/* Hop-by-hop hdr helper functions
 */

/**
 * calipso_opt_update - Replaces socket's hop options with a new set
 * @sk: the socket
 * @hop: new hop options
 *
 * Description:
 * Replaces @sk's hop options with @hop.  @hop may be शून्य to leave
 * the socket with no hop options.
 *
 */
अटल पूर्णांक calipso_opt_update(काष्ठा sock *sk, काष्ठा ipv6_opt_hdr *hop)
अणु
	काष्ठा ipv6_txoptions *old = txopt_get(inet6_sk(sk)), *txopts;

	txopts = ipv6_renew_options(sk, old, IPV6_HOPOPTS, hop);
	txopt_put(old);
	अगर (IS_ERR(txopts))
		वापस PTR_ERR(txopts);

	txopts = ipv6_update_options(sk, txopts);
	अगर (txopts) अणु
		atomic_sub(txopts->tot_len, &sk->sk_omem_alloc);
		txopt_put(txopts);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * calipso_tlv_len - Returns the length of the TLV
 * @opt: the option header
 * @offset: offset of the TLV within the header
 *
 * Description:
 * Returns the length of the TLV option at offset @offset within
 * the option header @opt.  Checks that the entire TLV fits inside
 * the option header, वापसs a negative value अगर this is not the हाल.
 */
अटल पूर्णांक calipso_tlv_len(काष्ठा ipv6_opt_hdr *opt, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित अक्षर *tlv = (अचिन्हित अक्षर *)opt;
	अचिन्हित पूर्णांक opt_len = ipv6_optlen(opt), tlv_len;

	अगर (offset < माप(*opt) || offset >= opt_len)
		वापस -EINVAL;
	अगर (tlv[offset] == IPV6_TLV_PAD1)
		वापस 1;
	अगर (offset + 1 >= opt_len)
		वापस -EINVAL;
	tlv_len = tlv[offset + 1] + 2;
	अगर (offset + tlv_len > opt_len)
		वापस -EINVAL;
	वापस tlv_len;
पूर्ण

/**
 * calipso_opt_find - Finds the CALIPSO option in an IPv6 hop options header
 * @hop: the hop options header
 * @start: on वापस holds the offset of any leading padding
 * @end: on वापस holds the offset of the first non-pad TLV after CALIPSO
 *
 * Description:
 * Finds the space occupied by a CALIPSO option (including any leading and
 * trailing padding).
 *
 * If a CALIPSO option exists set @start and @end to the
 * offsets within @hop of the start of padding beक्रमe the first
 * CALIPSO option and the end of padding after the first CALIPSO
 * option.  In this हाल the function वापसs 0.
 *
 * In the असलence of a CALIPSO option, @start and @end will be
 * set to the start and end of any trailing padding in the header.
 * This is useful when appending a new option, as the caller may want
 * to overग_लिखो some of this padding.  In this हाल the function will
 * वापस -ENOENT.
 */
अटल पूर्णांक calipso_opt_find(काष्ठा ipv6_opt_hdr *hop, अचिन्हित पूर्णांक *start,
			    अचिन्हित पूर्णांक *end)
अणु
	पूर्णांक ret_val = -ENOENT, tlv_len;
	अचिन्हित पूर्णांक opt_len, offset, offset_s = 0, offset_e = 0;
	अचिन्हित अक्षर *opt = (अचिन्हित अक्षर *)hop;

	opt_len = ipv6_optlen(hop);
	offset = माप(*hop);

	जबतक (offset < opt_len) अणु
		tlv_len = calipso_tlv_len(hop, offset);
		अगर (tlv_len < 0)
			वापस tlv_len;

		चयन (opt[offset]) अणु
		हाल IPV6_TLV_PAD1:
		हाल IPV6_TLV_PADN:
			अगर (offset_e)
				offset_e = offset;
			अवरोध;
		हाल IPV6_TLV_CALIPSO:
			ret_val = 0;
			offset_e = offset;
			अवरोध;
		शेष:
			अगर (offset_e == 0)
				offset_s = offset;
			अन्यथा
				जाओ out;
		पूर्ण
		offset += tlv_len;
	पूर्ण

out:
	अगर (offset_s)
		*start = offset_s + calipso_tlv_len(hop, offset_s);
	अन्यथा
		*start = माप(*hop);
	अगर (offset_e)
		*end = offset_e + calipso_tlv_len(hop, offset_e);
	अन्यथा
		*end = opt_len;

	वापस ret_val;
पूर्ण

/**
 * calipso_opt_insert - Inserts a CALIPSO option पूर्णांकo an IPv6 hop opt hdr
 * @hop: the original hop options header
 * @करोi_def: the CALIPSO DOI to use
 * @secattr: the specअगरic security attributes of the socket
 *
 * Description:
 * Creates a new hop options header based on @hop with a
 * CALIPSO option added to it.  If @hop alपढ़ोy contains a CALIPSO
 * option this is overwritten, otherwise the new option is appended
 * after any existing options.  If @hop is शून्य then the new header
 * will contain just the CALIPSO option and any needed padding.
 *
 */
अटल काष्ठा ipv6_opt_hdr *
calipso_opt_insert(काष्ठा ipv6_opt_hdr *hop,
		   स्थिर काष्ठा calipso_करोi *करोi_def,
		   स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	अचिन्हित पूर्णांक start, end, buf_len, pad, hop_len;
	काष्ठा ipv6_opt_hdr *new;
	पूर्णांक ret_val;

	अगर (hop) अणु
		hop_len = ipv6_optlen(hop);
		ret_val = calipso_opt_find(hop, &start, &end);
		अगर (ret_val && ret_val != -ENOENT)
			वापस ERR_PTR(ret_val);
	पूर्ण अन्यथा अणु
		hop_len = 0;
		start = माप(*hop);
		end = 0;
	पूर्ण

	buf_len = hop_len + start - end + CALIPSO_OPT_LEN_MAX_WITH_PAD;
	new = kzalloc(buf_len, GFP_ATOMIC);
	अगर (!new)
		वापस ERR_PTR(-ENOMEM);

	अगर (start > माप(*hop))
		स_नकल(new, hop, start);
	ret_val = calipso_genopt((अचिन्हित अक्षर *)new, start, buf_len, करोi_def,
				 secattr);
	अगर (ret_val < 0) अणु
		kमुक्त(new);
		वापस ERR_PTR(ret_val);
	पूर्ण

	buf_len = start + ret_val;
	/* At this poपूर्णांक buf_len aligns to 4n, so (buf_len & 4) pads to 8n */
	pad = ((buf_len & 4) + (end & 7)) & 7;
	calipso_pad_ग_लिखो((अचिन्हित अक्षर *)new, buf_len, pad);
	buf_len += pad;

	अगर (end != hop_len) अणु
		स_नकल((अक्षर *)new + buf_len, (अक्षर *)hop + end, hop_len - end);
		buf_len += hop_len - end;
	पूर्ण
	new->nexthdr = 0;
	new->hdrlen = buf_len / 8 - 1;

	वापस new;
पूर्ण

/**
 * calipso_opt_del - Removes the CALIPSO option from an option header
 * @hop: the original header
 * @new: the new header
 *
 * Description:
 * Creates a new header based on @hop without any CALIPSO option.  If @hop
 * करोesn't contain a CALIPSO option it वापसs -ENOENT.  If @hop contains
 * no other non-padding options, it वापसs zero with @new set to शून्य.
 * Otherwise it वापसs zero, creates a new header without the CALIPSO
 * option (and removing as much padding as possible) and वापसs with
 * @new set to that header.
 *
 */
अटल पूर्णांक calipso_opt_del(काष्ठा ipv6_opt_hdr *hop,
			   काष्ठा ipv6_opt_hdr **new)
अणु
	पूर्णांक ret_val;
	अचिन्हित पूर्णांक start, end, delta, pad, hop_len;

	ret_val = calipso_opt_find(hop, &start, &end);
	अगर (ret_val)
		वापस ret_val;

	hop_len = ipv6_optlen(hop);
	अगर (start == माप(*hop) && end == hop_len) अणु
		/* There's no other option in the header so वापस शून्य */
		*new = शून्य;
		वापस 0;
	पूर्ण

	delta = (end - start) & ~7;
	*new = kzalloc(hop_len - delta, GFP_ATOMIC);
	अगर (!*new)
		वापस -ENOMEM;

	स_नकल(*new, hop, start);
	(*new)->hdrlen -= delta / 8;
	pad = (end - start) & 7;
	calipso_pad_ग_लिखो((अचिन्हित अक्षर *)*new, start, pad);
	अगर (end != hop_len)
		स_नकल((अक्षर *)*new + start + pad, (अक्षर *)hop + end,
		       hop_len - end);

	वापस 0;
पूर्ण

/**
 * calipso_opt_getattr - Get the security attributes from a memory block
 * @calipso: the CALIPSO option
 * @secattr: the security attributes
 *
 * Description:
 * Inspect @calipso and वापस the security attributes in @secattr.
 * Returns zero on success and negative values on failure.
 *
 */
अटल पूर्णांक calipso_opt_getattr(स्थिर अचिन्हित अक्षर *calipso,
			       काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val = -ENOMSG;
	u32 करोi, len = calipso[1], cat_len = calipso[6] * 4;
	काष्ठा calipso_करोi *करोi_def;

	अगर (cat_len + 8 > len)
		वापस -EINVAL;

	अगर (calipso_cache_check(calipso + 2, calipso[1], secattr) == 0)
		वापस 0;

	करोi = get_unaligned_be32(calipso + 2);
	rcu_पढ़ो_lock();
	करोi_def = calipso_करोi_search(करोi);
	अगर (!करोi_def)
		जाओ getattr_वापस;

	secattr->attr.mls.lvl = calipso[7];
	secattr->flags |= NETLBL_SECATTR_MLS_LVL;

	अगर (cat_len) अणु
		ret_val = calipso_map_cat_ntoh(करोi_def,
					       calipso + 10,
					       cat_len,
					       secattr);
		अगर (ret_val != 0) अणु
			netlbl_caपंचांगap_मुक्त(secattr->attr.mls.cat);
			जाओ getattr_वापस;
		पूर्ण

		अगर (secattr->attr.mls.cat)
			secattr->flags |= NETLBL_SECATTR_MLS_CAT;
	पूर्ण

	secattr->type = NETLBL_NLTYPE_CALIPSO;

getattr_वापस:
	rcu_पढ़ो_unlock();
	वापस ret_val;
पूर्ण

/* sock functions.
 */

/**
 * calipso_sock_getattr - Get the security attributes from a sock
 * @sk: the sock
 * @secattr: the security attributes
 *
 * Description:
 * Query @sk to see अगर there is a CALIPSO option attached to the sock and अगर
 * there is वापस the CALIPSO security attributes in @secattr.  This function
 * requires that @sk be locked, or निजीly held, but it करोes not करो any
 * locking itself.  Returns zero on success and negative values on failure.
 *
 */
अटल पूर्णांक calipso_sock_getattr(काष्ठा sock *sk,
				काष्ठा netlbl_lsm_secattr *secattr)
अणु
	काष्ठा ipv6_opt_hdr *hop;
	पूर्णांक opt_len, len, ret_val = -ENOMSG, offset;
	अचिन्हित अक्षर *opt;
	काष्ठा ipv6_txoptions *txopts = txopt_get(inet6_sk(sk));

	अगर (!txopts || !txopts->hopopt)
		जाओ करोne;

	hop = txopts->hopopt;
	opt = (अचिन्हित अक्षर *)hop;
	opt_len = ipv6_optlen(hop);
	offset = माप(*hop);
	जबतक (offset < opt_len) अणु
		len = calipso_tlv_len(hop, offset);
		अगर (len < 0) अणु
			ret_val = len;
			जाओ करोne;
		पूर्ण
		चयन (opt[offset]) अणु
		हाल IPV6_TLV_CALIPSO:
			अगर (len < CALIPSO_HDR_LEN)
				ret_val = -EINVAL;
			अन्यथा
				ret_val = calipso_opt_getattr(&opt[offset],
							      secattr);
			जाओ करोne;
		शेष:
			offset += len;
			अवरोध;
		पूर्ण
	पूर्ण
करोne:
	txopt_put(txopts);
	वापस ret_val;
पूर्ण

/**
 * calipso_sock_setattr - Add a CALIPSO option to a socket
 * @sk: the socket
 * @करोi_def: the CALIPSO DOI to use
 * @secattr: the specअगरic security attributes of the socket
 *
 * Description:
 * Set the CALIPSO option on the given socket using the DOI definition and
 * security attributes passed to the function.  This function requires
 * exclusive access to @sk, which means it either needs to be in the
 * process of being created or locked.  Returns zero on success and negative
 * values on failure.
 *
 */
अटल पूर्णांक calipso_sock_setattr(काष्ठा sock *sk,
				स्थिर काष्ठा calipso_करोi *करोi_def,
				स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	काष्ठा ipv6_opt_hdr *old, *new;
	काष्ठा ipv6_txoptions *txopts = txopt_get(inet6_sk(sk));

	old = शून्य;
	अगर (txopts)
		old = txopts->hopopt;

	new = calipso_opt_insert(old, करोi_def, secattr);
	txopt_put(txopts);
	अगर (IS_ERR(new))
		वापस PTR_ERR(new);

	ret_val = calipso_opt_update(sk, new);

	kमुक्त(new);
	वापस ret_val;
पूर्ण

/**
 * calipso_sock_delattr - Delete the CALIPSO option from a socket
 * @sk: the socket
 *
 * Description:
 * Removes the CALIPSO option from a socket, अगर present.
 *
 */
अटल व्योम calipso_sock_delattr(काष्ठा sock *sk)
अणु
	काष्ठा ipv6_opt_hdr *new_hop;
	काष्ठा ipv6_txoptions *txopts = txopt_get(inet6_sk(sk));

	अगर (!txopts || !txopts->hopopt)
		जाओ करोne;

	अगर (calipso_opt_del(txopts->hopopt, &new_hop))
		जाओ करोne;

	calipso_opt_update(sk, new_hop);
	kमुक्त(new_hop);

करोne:
	txopt_put(txopts);
पूर्ण

/* request sock functions.
 */

/**
 * calipso_req_setattr - Add a CALIPSO option to a connection request socket
 * @req: the connection request socket
 * @करोi_def: the CALIPSO DOI to use
 * @secattr: the specअगरic security attributes of the socket
 *
 * Description:
 * Set the CALIPSO option on the given socket using the DOI definition and
 * security attributes passed to the function.  Returns zero on success and
 * negative values on failure.
 *
 */
अटल पूर्णांक calipso_req_setattr(काष्ठा request_sock *req,
			       स्थिर काष्ठा calipso_करोi *करोi_def,
			       स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	काष्ठा ipv6_txoptions *txopts;
	काष्ठा inet_request_sock *req_inet = inet_rsk(req);
	काष्ठा ipv6_opt_hdr *old, *new;
	काष्ठा sock *sk = sk_to_full_sk(req_to_sk(req));

	अगर (req_inet->ipv6_opt && req_inet->ipv6_opt->hopopt)
		old = req_inet->ipv6_opt->hopopt;
	अन्यथा
		old = शून्य;

	new = calipso_opt_insert(old, करोi_def, secattr);
	अगर (IS_ERR(new))
		वापस PTR_ERR(new);

	txopts = ipv6_renew_options(sk, req_inet->ipv6_opt, IPV6_HOPOPTS, new);

	kमुक्त(new);

	अगर (IS_ERR(txopts))
		वापस PTR_ERR(txopts);

	txopts = xchg(&req_inet->ipv6_opt, txopts);
	अगर (txopts) अणु
		atomic_sub(txopts->tot_len, &sk->sk_omem_alloc);
		txopt_put(txopts);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * calipso_req_delattr - Delete the CALIPSO option from a request socket
 * @req: the request socket
 *
 * Description:
 * Removes the CALIPSO option from a request socket, अगर present.
 *
 */
अटल व्योम calipso_req_delattr(काष्ठा request_sock *req)
अणु
	काष्ठा inet_request_sock *req_inet = inet_rsk(req);
	काष्ठा ipv6_opt_hdr *new;
	काष्ठा ipv6_txoptions *txopts;
	काष्ठा sock *sk = sk_to_full_sk(req_to_sk(req));

	अगर (!req_inet->ipv6_opt || !req_inet->ipv6_opt->hopopt)
		वापस;

	अगर (calipso_opt_del(req_inet->ipv6_opt->hopopt, &new))
		वापस; /* Nothing to करो */

	txopts = ipv6_renew_options(sk, req_inet->ipv6_opt, IPV6_HOPOPTS, new);

	अगर (!IS_ERR(txopts)) अणु
		txopts = xchg(&req_inet->ipv6_opt, txopts);
		अगर (txopts) अणु
			atomic_sub(txopts->tot_len, &sk->sk_omem_alloc);
			txopt_put(txopts);
		पूर्ण
	पूर्ण
	kमुक्त(new);
पूर्ण

/* skbuff functions.
 */

/**
 * calipso_skbuff_optptr - Find the CALIPSO option in the packet
 * @skb: the packet
 *
 * Description:
 * Parse the packet's IP header looking क्रम a CALIPSO option.  Returns a poपूर्णांकer
 * to the start of the CALIPSO option on success, शून्य अगर one अगर not found.
 *
 */
अटल अचिन्हित अक्षर *calipso_skbuff_optptr(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ipv6hdr *ip6_hdr = ipv6_hdr(skb);
	पूर्णांक offset;

	अगर (ip6_hdr->nexthdr != NEXTHDR_HOP)
		वापस शून्य;

	offset = ipv6_find_tlv(skb, माप(*ip6_hdr), IPV6_TLV_CALIPSO);
	अगर (offset >= 0)
		वापस (अचिन्हित अक्षर *)ip6_hdr + offset;

	वापस शून्य;
पूर्ण

/**
 * calipso_skbuff_setattr - Set the CALIPSO option on a packet
 * @skb: the packet
 * @करोi_def: the CALIPSO DOI to use
 * @secattr: the security attributes
 *
 * Description:
 * Set the CALIPSO option on the given packet based on the security attributes.
 * Returns a poपूर्णांकer to the IP header on success and शून्य on failure.
 *
 */
अटल पूर्णांक calipso_skbuff_setattr(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा calipso_करोi *करोi_def,
				  स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	काष्ठा ipv6hdr *ip6_hdr;
	काष्ठा ipv6_opt_hdr *hop;
	अचिन्हित अक्षर buf[CALIPSO_MAX_BUFFER];
	पूर्णांक len_delta, new_end, pad, payload;
	अचिन्हित पूर्णांक start, end;

	ip6_hdr = ipv6_hdr(skb);
	अगर (ip6_hdr->nexthdr == NEXTHDR_HOP) अणु
		hop = (काष्ठा ipv6_opt_hdr *)(ip6_hdr + 1);
		ret_val = calipso_opt_find(hop, &start, &end);
		अगर (ret_val && ret_val != -ENOENT)
			वापस ret_val;
	पूर्ण अन्यथा अणु
		start = 0;
		end = 0;
	पूर्ण

	स_रखो(buf, 0, माप(buf));
	ret_val = calipso_genopt(buf, start & 3, माप(buf), करोi_def, secattr);
	अगर (ret_val < 0)
		वापस ret_val;

	new_end = start + ret_val;
	/* At this poपूर्णांक new_end aligns to 4n, so (new_end & 4) pads to 8n */
	pad = ((new_end & 4) + (end & 7)) & 7;
	len_delta = new_end - (पूर्णांक)end + pad;
	ret_val = skb_cow(skb, skb_headroom(skb) + len_delta);
	अगर (ret_val < 0)
		वापस ret_val;

	ip6_hdr = ipv6_hdr(skb); /* Reset as skb_cow() may have moved it */

	अगर (len_delta) अणु
		अगर (len_delta > 0)
			skb_push(skb, len_delta);
		अन्यथा
			skb_pull(skb, -len_delta);
		स_हटाओ((अक्षर *)ip6_hdr - len_delta, ip6_hdr,
			माप(*ip6_hdr) + start);
		skb_reset_network_header(skb);
		ip6_hdr = ipv6_hdr(skb);
		payload = ntohs(ip6_hdr->payload_len);
		ip6_hdr->payload_len = htons(payload + len_delta);
	पूर्ण

	hop = (काष्ठा ipv6_opt_hdr *)(ip6_hdr + 1);
	अगर (start == 0) अणु
		काष्ठा ipv6_opt_hdr *new_hop = (काष्ठा ipv6_opt_hdr *)buf;

		new_hop->nexthdr = ip6_hdr->nexthdr;
		new_hop->hdrlen = len_delta / 8 - 1;
		ip6_hdr->nexthdr = NEXTHDR_HOP;
	पूर्ण अन्यथा अणु
		hop->hdrlen += len_delta / 8;
	पूर्ण
	स_नकल((अक्षर *)hop + start, buf + (start & 3), new_end - start);
	calipso_pad_ग_लिखो((अचिन्हित अक्षर *)hop, new_end, pad);

	वापस 0;
पूर्ण

/**
 * calipso_skbuff_delattr - Delete any CALIPSO options from a packet
 * @skb: the packet
 *
 * Description:
 * Removes any and all CALIPSO options from the given packet.  Returns zero on
 * success, negative values on failure.
 *
 */
अटल पूर्णांक calipso_skbuff_delattr(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret_val;
	काष्ठा ipv6hdr *ip6_hdr;
	काष्ठा ipv6_opt_hdr *old_hop;
	u32 old_hop_len, start = 0, end = 0, delta, size, pad;

	अगर (!calipso_skbuff_optptr(skb))
		वापस 0;

	/* since we are changing the packet we should make a copy */
	ret_val = skb_cow(skb, skb_headroom(skb));
	अगर (ret_val < 0)
		वापस ret_val;

	ip6_hdr = ipv6_hdr(skb);
	old_hop = (काष्ठा ipv6_opt_hdr *)(ip6_hdr + 1);
	old_hop_len = ipv6_optlen(old_hop);

	ret_val = calipso_opt_find(old_hop, &start, &end);
	अगर (ret_val)
		वापस ret_val;

	अगर (start == माप(*old_hop) && end == old_hop_len) अणु
		/* There's no other option in the header so we delete
		 * the whole thing. */
		delta = old_hop_len;
		size = माप(*ip6_hdr);
		ip6_hdr->nexthdr = old_hop->nexthdr;
	पूर्ण अन्यथा अणु
		delta = (end - start) & ~7;
		अगर (delta)
			old_hop->hdrlen -= delta / 8;
		pad = (end - start) & 7;
		size = माप(*ip6_hdr) + start + pad;
		calipso_pad_ग_लिखो((अचिन्हित अक्षर *)old_hop, start, pad);
	पूर्ण

	अगर (delta) अणु
		skb_pull(skb, delta);
		स_हटाओ((अक्षर *)ip6_hdr + delta, ip6_hdr, size);
		skb_reset_network_header(skb);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा netlbl_calipso_ops ops = अणु
	.करोi_add          = calipso_करोi_add,
	.करोi_मुक्त         = calipso_करोi_मुक्त,
	.करोi_हटाओ       = calipso_करोi_हटाओ,
	.करोi_getdef       = calipso_करोi_getdef,
	.करोi_putdef       = calipso_करोi_putdef,
	.करोi_walk         = calipso_करोi_walk,
	.sock_getattr     = calipso_sock_getattr,
	.sock_setattr     = calipso_sock_setattr,
	.sock_delattr     = calipso_sock_delattr,
	.req_setattr      = calipso_req_setattr,
	.req_delattr      = calipso_req_delattr,
	.opt_getattr      = calipso_opt_getattr,
	.skbuff_optptr    = calipso_skbuff_optptr,
	.skbuff_setattr   = calipso_skbuff_setattr,
	.skbuff_delattr   = calipso_skbuff_delattr,
	.cache_invalidate = calipso_cache_invalidate,
	.cache_add        = calipso_cache_add
पूर्ण;

/**
 * calipso_init - Initialize the CALIPSO module
 *
 * Description:
 * Initialize the CALIPSO module and prepare it क्रम use.  Returns zero on
 * success and negative values on failure.
 *
 */
पूर्णांक __init calipso_init(व्योम)
अणु
	पूर्णांक ret_val;

	ret_val = calipso_cache_init();
	अगर (!ret_val)
		netlbl_calipso_ops_रेजिस्टर(&ops);
	वापस ret_val;
पूर्ण

व्योम calipso_निकास(व्योम)
अणु
	netlbl_calipso_ops_रेजिस्टर(शून्य);
	calipso_cache_invalidate();
	kमुक्त(calipso_cache);
पूर्ण
