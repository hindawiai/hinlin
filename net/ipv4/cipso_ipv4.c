<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CIPSO - Commercial IP Security Option
 *
 * This is an implementation of the CIPSO 2.2 protocol as specअगरied in
 * draft-ietf-cipso-ipsecurity-01.txt with additional tag types as found in
 * FIPS-188.  While CIPSO never became a full IETF RFC standard many venकरोrs
 * have chosen to aकरोpt the protocol and over the years it has become a
 * de-facto standard क्रम labeled networking.
 *
 * The CIPSO draft specअगरication can be found in the kernel's Documentation
 * directory as well as the following URL:
 *   https://tools.ietf.org/id/draft-ietf-cipso-ipsecurity-01.txt
 * The FIPS-188 specअगरication can be found at the following URL:
 *   https://www.itl.nist.gov/fipspubs/fip188.hपंचांग
 *
 * Author: Paul Moore <paul.moore@hp.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006, 2008
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
#समावेश <net/cipso_ipv4.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bug.h>
#समावेश <यंत्र/unaligned.h>

/* List of available DOI definitions */
/* XXX - This currently assumes a minimal number of dअगरferent DOIs in use,
 * अगर in practice there are a lot of dअगरferent DOIs this list should
 * probably be turned पूर्णांकo a hash table or something similar so we
 * can करो quick lookups. */
अटल DEFINE_SPINLOCK(cipso_v4_करोi_list_lock);
अटल LIST_HEAD(cipso_v4_करोi_list);

/* Label mapping cache */
पूर्णांक cipso_v4_cache_enabled = 1;
पूर्णांक cipso_v4_cache_bucketsize = 10;
#घोषणा CIPSO_V4_CACHE_BUCKETBITS     7
#घोषणा CIPSO_V4_CACHE_BUCKETS        (1 << CIPSO_V4_CACHE_BUCKETBITS)
#घोषणा CIPSO_V4_CACHE_REORDERLIMIT   10
काष्ठा cipso_v4_map_cache_bkt अणु
	spinlock_t lock;
	u32 size;
	काष्ठा list_head list;
पूर्ण;

काष्ठा cipso_v4_map_cache_entry अणु
	u32 hash;
	अचिन्हित अक्षर *key;
	माप_प्रकार key_len;

	काष्ठा netlbl_lsm_cache *lsm_data;

	u32 activity;
	काष्ठा list_head list;
पूर्ण;

अटल काष्ठा cipso_v4_map_cache_bkt *cipso_v4_cache;

/* Restricted biपंचांगap (tag #1) flags */
पूर्णांक cipso_v4_rbm_optfmt = 0;
पूर्णांक cipso_v4_rbm_strictvalid = 1;

/*
 * Protocol Constants
 */

/* Maximum size of the CIPSO IP option, derived from the fact that the maximum
 * IPv4 header size is 60 bytes and the base IPv4 header is 20 bytes दीर्घ. */
#घोषणा CIPSO_V4_OPT_LEN_MAX          40

/* Length of the base CIPSO option, this includes the option type (1 byte), the
 * option length (1 byte), and the DOI (4 bytes). */
#घोषणा CIPSO_V4_HDR_LEN              6

/* Base length of the restrictive category biपंचांगap tag (tag #1). */
#घोषणा CIPSO_V4_TAG_RBM_BLEN         4

/* Base length of the क्रमागतerated category tag (tag #2). */
#घोषणा CIPSO_V4_TAG_ENUM_BLEN        4

/* Base length of the ranged categories biपंचांगap tag (tag #5). */
#घोषणा CIPSO_V4_TAG_RNG_BLEN         4
/* The maximum number of category ranges permitted in the ranged category tag
 * (tag #5).  You may note that the IETF draft states that the maximum number
 * of category ranges is 7, but अगर the low end of the last category range is
 * zero then it is possible to fit 8 category ranges because the zero should
 * be omitted. */
#घोषणा CIPSO_V4_TAG_RNG_CAT_MAX      8

/* Base length of the local tag (non-standard tag).
 *  Tag definition (may change between kernel versions)
 *
 * 0          8          16         24         32
 * +----------+----------+----------+----------+
 * | 10000000 | 00000110 | 32-bit secid value  |
 * +----------+----------+----------+----------+
 * | in (host byte order)|
 * +----------+----------+
 *
 */
#घोषणा CIPSO_V4_TAG_LOC_BLEN         6

/*
 * Helper Functions
 */

/**
 * cipso_v4_cache_entry_मुक्त - Frees a cache entry
 * @entry: the entry to मुक्त
 *
 * Description:
 * This function मुक्तs the memory associated with a cache entry including the
 * LSM cache data अगर there are no दीर्घer any users, i.e. reference count == 0.
 *
 */
अटल व्योम cipso_v4_cache_entry_मुक्त(काष्ठा cipso_v4_map_cache_entry *entry)
अणु
	अगर (entry->lsm_data)
		netlbl_secattr_cache_मुक्त(entry->lsm_data);
	kमुक्त(entry->key);
	kमुक्त(entry);
पूर्ण

/**
 * cipso_v4_map_cache_hash - Hashing function क्रम the CIPSO cache
 * @key: the hash key
 * @key_len: the length of the key in bytes
 *
 * Description:
 * The CIPSO tag hashing function.  Returns a 32-bit hash value.
 *
 */
अटल u32 cipso_v4_map_cache_hash(स्थिर अचिन्हित अक्षर *key, u32 key_len)
अणु
	वापस jhash(key, key_len, 0);
पूर्ण

/*
 * Label Mapping Cache Functions
 */

/**
 * cipso_v4_cache_init - Initialize the CIPSO cache
 *
 * Description:
 * Initializes the CIPSO label mapping cache, this function should be called
 * beक्रमe any of the other functions defined in this file.  Returns zero on
 * success, negative values on error.
 *
 */
अटल पूर्णांक __init cipso_v4_cache_init(व्योम)
अणु
	u32 iter;

	cipso_v4_cache = kसुस्मृति(CIPSO_V4_CACHE_BUCKETS,
				 माप(काष्ठा cipso_v4_map_cache_bkt),
				 GFP_KERNEL);
	अगर (!cipso_v4_cache)
		वापस -ENOMEM;

	क्रम (iter = 0; iter < CIPSO_V4_CACHE_BUCKETS; iter++) अणु
		spin_lock_init(&cipso_v4_cache[iter].lock);
		cipso_v4_cache[iter].size = 0;
		INIT_LIST_HEAD(&cipso_v4_cache[iter].list);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cipso_v4_cache_invalidate - Invalidates the current CIPSO cache
 *
 * Description:
 * Invalidates and मुक्तs any entries in the CIPSO cache.  Returns zero on
 * success and negative values on failure.
 *
 */
व्योम cipso_v4_cache_invalidate(व्योम)
अणु
	काष्ठा cipso_v4_map_cache_entry *entry, *पंचांगp_entry;
	u32 iter;

	क्रम (iter = 0; iter < CIPSO_V4_CACHE_BUCKETS; iter++) अणु
		spin_lock_bh(&cipso_v4_cache[iter].lock);
		list_क्रम_each_entry_safe(entry,
					 पंचांगp_entry,
					 &cipso_v4_cache[iter].list, list) अणु
			list_del(&entry->list);
			cipso_v4_cache_entry_मुक्त(entry);
		पूर्ण
		cipso_v4_cache[iter].size = 0;
		spin_unlock_bh(&cipso_v4_cache[iter].lock);
	पूर्ण
पूर्ण

/**
 * cipso_v4_cache_check - Check the CIPSO cache क्रम a label mapping
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
 *     CIPSO_V4_CACHE_REORDERLIMIT the two entries are swapped
 *
 * Returns zero on success, -ENOENT क्रम a cache miss, and other negative values
 * on error.
 *
 */
अटल पूर्णांक cipso_v4_cache_check(स्थिर अचिन्हित अक्षर *key,
				u32 key_len,
				काष्ठा netlbl_lsm_secattr *secattr)
अणु
	u32 bkt;
	काष्ठा cipso_v4_map_cache_entry *entry;
	काष्ठा cipso_v4_map_cache_entry *prev_entry = शून्य;
	u32 hash;

	अगर (!cipso_v4_cache_enabled)
		वापस -ENOENT;

	hash = cipso_v4_map_cache_hash(key, key_len);
	bkt = hash & (CIPSO_V4_CACHE_BUCKETS - 1);
	spin_lock_bh(&cipso_v4_cache[bkt].lock);
	list_क्रम_each_entry(entry, &cipso_v4_cache[bkt].list, list) अणु
		अगर (entry->hash == hash &&
		    entry->key_len == key_len &&
		    स_भेद(entry->key, key, key_len) == 0) अणु
			entry->activity += 1;
			refcount_inc(&entry->lsm_data->refcount);
			secattr->cache = entry->lsm_data;
			secattr->flags |= NETLBL_SECATTR_CACHE;
			secattr->type = NETLBL_NLTYPE_CIPSOV4;
			अगर (!prev_entry) अणु
				spin_unlock_bh(&cipso_v4_cache[bkt].lock);
				वापस 0;
			पूर्ण

			अगर (prev_entry->activity > 0)
				prev_entry->activity -= 1;
			अगर (entry->activity > prev_entry->activity &&
			    entry->activity - prev_entry->activity >
			    CIPSO_V4_CACHE_REORDERLIMIT) अणु
				__list_del(entry->list.prev, entry->list.next);
				__list_add(&entry->list,
					   prev_entry->list.prev,
					   &prev_entry->list);
			पूर्ण

			spin_unlock_bh(&cipso_v4_cache[bkt].lock);
			वापस 0;
		पूर्ण
		prev_entry = entry;
	पूर्ण
	spin_unlock_bh(&cipso_v4_cache[bkt].lock);

	वापस -ENOENT;
पूर्ण

/**
 * cipso_v4_cache_add - Add an entry to the CIPSO cache
 * @cipso_ptr: poपूर्णांकer to CIPSO IP option
 * @secattr: the packet's security attributes
 *
 * Description:
 * Add a new entry पूर्णांकo the CIPSO label mapping cache.  Add the new entry to
 * head of the cache bucket's list, अगर the cache bucket is out of room हटाओ
 * the last entry in the list first.  It is important to note that there is
 * currently no checking क्रम duplicate keys.  Returns zero on success,
 * negative values on failure.
 *
 */
पूर्णांक cipso_v4_cache_add(स्थिर अचिन्हित अक्षर *cipso_ptr,
		       स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val = -EPERM;
	u32 bkt;
	काष्ठा cipso_v4_map_cache_entry *entry = शून्य;
	काष्ठा cipso_v4_map_cache_entry *old_entry = शून्य;
	u32 cipso_ptr_len;

	अगर (!cipso_v4_cache_enabled || cipso_v4_cache_bucketsize <= 0)
		वापस 0;

	cipso_ptr_len = cipso_ptr[1];

	entry = kzalloc(माप(*entry), GFP_ATOMIC);
	अगर (!entry)
		वापस -ENOMEM;
	entry->key = kmemdup(cipso_ptr, cipso_ptr_len, GFP_ATOMIC);
	अगर (!entry->key) अणु
		ret_val = -ENOMEM;
		जाओ cache_add_failure;
	पूर्ण
	entry->key_len = cipso_ptr_len;
	entry->hash = cipso_v4_map_cache_hash(cipso_ptr, cipso_ptr_len);
	refcount_inc(&secattr->cache->refcount);
	entry->lsm_data = secattr->cache;

	bkt = entry->hash & (CIPSO_V4_CACHE_BUCKETS - 1);
	spin_lock_bh(&cipso_v4_cache[bkt].lock);
	अगर (cipso_v4_cache[bkt].size < cipso_v4_cache_bucketsize) अणु
		list_add(&entry->list, &cipso_v4_cache[bkt].list);
		cipso_v4_cache[bkt].size += 1;
	पूर्ण अन्यथा अणु
		old_entry = list_entry(cipso_v4_cache[bkt].list.prev,
				       काष्ठा cipso_v4_map_cache_entry, list);
		list_del(&old_entry->list);
		list_add(&entry->list, &cipso_v4_cache[bkt].list);
		cipso_v4_cache_entry_मुक्त(old_entry);
	पूर्ण
	spin_unlock_bh(&cipso_v4_cache[bkt].lock);

	वापस 0;

cache_add_failure:
	अगर (entry)
		cipso_v4_cache_entry_मुक्त(entry);
	वापस ret_val;
पूर्ण

/*
 * DOI List Functions
 */

/**
 * cipso_v4_करोi_search - Searches क्रम a DOI definition
 * @करोi: the DOI to search क्रम
 *
 * Description:
 * Search the DOI definition list क्रम a DOI definition with a DOI value that
 * matches @करोi.  The caller is responsible क्रम calling rcu_पढ़ो_[un]lock().
 * Returns a poपूर्णांकer to the DOI definition on success and शून्य on failure.
 */
अटल काष्ठा cipso_v4_करोi *cipso_v4_करोi_search(u32 करोi)
अणु
	काष्ठा cipso_v4_करोi *iter;

	list_क्रम_each_entry_rcu(iter, &cipso_v4_करोi_list, list)
		अगर (iter->करोi == करोi && refcount_पढ़ो(&iter->refcount))
			वापस iter;
	वापस शून्य;
पूर्ण

/**
 * cipso_v4_करोi_add - Add a new DOI to the CIPSO protocol engine
 * @करोi_def: the DOI काष्ठाure
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * The caller defines a new DOI क्रम use by the CIPSO engine and calls this
 * function to add it to the list of acceptable करोमुख्यs.  The caller must
 * ensure that the mapping table specअगरied in @करोi_def->map meets all of the
 * requirements of the mapping type (see cipso_ipv4.h क्रम details).  Returns
 * zero on success and non-zero on failure.
 *
 */
पूर्णांक cipso_v4_करोi_add(काष्ठा cipso_v4_करोi *करोi_def,
		     काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val = -EINVAL;
	u32 iter;
	u32 करोi;
	u32 करोi_type;
	काष्ठा audit_buffer *audit_buf;

	करोi = करोi_def->करोi;
	करोi_type = करोi_def->type;

	अगर (करोi_def->करोi == CIPSO_V4_DOI_UNKNOWN)
		जाओ करोi_add_वापस;
	क्रम (iter = 0; iter < CIPSO_V4_TAG_MAXCNT; iter++) अणु
		चयन (करोi_def->tags[iter]) अणु
		हाल CIPSO_V4_TAG_RBITMAP:
			अवरोध;
		हाल CIPSO_V4_TAG_RANGE:
		हाल CIPSO_V4_TAG_ENUM:
			अगर (करोi_def->type != CIPSO_V4_MAP_PASS)
				जाओ करोi_add_वापस;
			अवरोध;
		हाल CIPSO_V4_TAG_LOCAL:
			अगर (करोi_def->type != CIPSO_V4_MAP_LOCAL)
				जाओ करोi_add_वापस;
			अवरोध;
		हाल CIPSO_V4_TAG_INVALID:
			अगर (iter == 0)
				जाओ करोi_add_वापस;
			अवरोध;
		शेष:
			जाओ करोi_add_वापस;
		पूर्ण
	पूर्ण

	refcount_set(&करोi_def->refcount, 1);

	spin_lock(&cipso_v4_करोi_list_lock);
	अगर (cipso_v4_करोi_search(करोi_def->करोi)) अणु
		spin_unlock(&cipso_v4_करोi_list_lock);
		ret_val = -EEXIST;
		जाओ करोi_add_वापस;
	पूर्ण
	list_add_tail_rcu(&करोi_def->list, &cipso_v4_करोi_list);
	spin_unlock(&cipso_v4_करोi_list_lock);
	ret_val = 0;

करोi_add_वापस:
	audit_buf = netlbl_audit_start(AUDIT_MAC_CIPSOV4_ADD, audit_info);
	अगर (audit_buf) अणु
		स्थिर अक्षर *type_str;
		चयन (करोi_type) अणु
		हाल CIPSO_V4_MAP_TRANS:
			type_str = "trans";
			अवरोध;
		हाल CIPSO_V4_MAP_PASS:
			type_str = "pass";
			अवरोध;
		हाल CIPSO_V4_MAP_LOCAL:
			type_str = "local";
			अवरोध;
		शेष:
			type_str = "(unknown)";
		पूर्ण
		audit_log_क्रमmat(audit_buf,
				 " cipso_doi=%u cipso_type=%s res=%u",
				 करोi, type_str, ret_val == 0 ? 1 : 0);
		audit_log_end(audit_buf);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * cipso_v4_करोi_मुक्त - Frees a DOI definition
 * @करोi_def: the DOI definition
 *
 * Description:
 * This function मुक्तs all of the memory associated with a DOI definition.
 *
 */
व्योम cipso_v4_करोi_मुक्त(काष्ठा cipso_v4_करोi *करोi_def)
अणु
	अगर (!करोi_def)
		वापस;

	चयन (करोi_def->type) अणु
	हाल CIPSO_V4_MAP_TRANS:
		kमुक्त(करोi_def->map.std->lvl.cipso);
		kमुक्त(करोi_def->map.std->lvl.local);
		kमुक्त(करोi_def->map.std->cat.cipso);
		kमुक्त(करोi_def->map.std->cat.local);
		kमुक्त(करोi_def->map.std);
		अवरोध;
	पूर्ण
	kमुक्त(करोi_def);
पूर्ण

/**
 * cipso_v4_करोi_मुक्त_rcu - Frees a DOI definition via the RCU poपूर्णांकer
 * @entry: the entry's RCU field
 *
 * Description:
 * This function is deचिन्हित to be used as a callback to the call_rcu()
 * function so that the memory allocated to the DOI definition can be released
 * safely.
 *
 */
अटल व्योम cipso_v4_करोi_मुक्त_rcu(काष्ठा rcu_head *entry)
अणु
	काष्ठा cipso_v4_करोi *करोi_def;

	करोi_def = container_of(entry, काष्ठा cipso_v4_करोi, rcu);
	cipso_v4_करोi_मुक्त(करोi_def);
पूर्ण

/**
 * cipso_v4_करोi_हटाओ - Remove an existing DOI from the CIPSO protocol engine
 * @करोi: the DOI value
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Removes a DOI definition from the CIPSO engine.  The NetLabel routines will
 * be called to release their own LSM करोमुख्य mappings as well as our own
 * करोमुख्य list.  Returns zero on success and negative values on failure.
 *
 */
पूर्णांक cipso_v4_करोi_हटाओ(u32 करोi, काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val;
	काष्ठा cipso_v4_करोi *करोi_def;
	काष्ठा audit_buffer *audit_buf;

	spin_lock(&cipso_v4_करोi_list_lock);
	करोi_def = cipso_v4_करोi_search(करोi);
	अगर (!करोi_def) अणु
		spin_unlock(&cipso_v4_करोi_list_lock);
		ret_val = -ENOENT;
		जाओ करोi_हटाओ_वापस;
	पूर्ण
	list_del_rcu(&करोi_def->list);
	spin_unlock(&cipso_v4_करोi_list_lock);

	cipso_v4_करोi_putdef(करोi_def);
	ret_val = 0;

करोi_हटाओ_वापस:
	audit_buf = netlbl_audit_start(AUDIT_MAC_CIPSOV4_DEL, audit_info);
	अगर (audit_buf) अणु
		audit_log_क्रमmat(audit_buf,
				 " cipso_doi=%u res=%u",
				 करोi, ret_val == 0 ? 1 : 0);
		audit_log_end(audit_buf);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * cipso_v4_करोi_getdef - Returns a reference to a valid DOI definition
 * @करोi: the DOI value
 *
 * Description:
 * Searches क्रम a valid DOI definition and अगर one is found it is वापसed to
 * the caller.  Otherwise शून्य is वापसed.  The caller must ensure that
 * rcu_पढ़ो_lock() is held जबतक accessing the वापसed definition and the DOI
 * definition reference count is decremented when the caller is करोne.
 *
 */
काष्ठा cipso_v4_करोi *cipso_v4_करोi_getdef(u32 करोi)
अणु
	काष्ठा cipso_v4_करोi *करोi_def;

	rcu_पढ़ो_lock();
	करोi_def = cipso_v4_करोi_search(करोi);
	अगर (!करोi_def)
		जाओ करोi_getdef_वापस;
	अगर (!refcount_inc_not_zero(&करोi_def->refcount))
		करोi_def = शून्य;

करोi_getdef_वापस:
	rcu_पढ़ो_unlock();
	वापस करोi_def;
पूर्ण

/**
 * cipso_v4_करोi_putdef - Releases a reference क्रम the given DOI definition
 * @करोi_def: the DOI definition
 *
 * Description:
 * Releases a DOI definition reference obtained from cipso_v4_करोi_getdef().
 *
 */
व्योम cipso_v4_करोi_putdef(काष्ठा cipso_v4_करोi *करोi_def)
अणु
	अगर (!करोi_def)
		वापस;

	अगर (!refcount_dec_and_test(&करोi_def->refcount))
		वापस;

	cipso_v4_cache_invalidate();
	call_rcu(&करोi_def->rcu, cipso_v4_करोi_मुक्त_rcu);
पूर्ण

/**
 * cipso_v4_करोi_walk - Iterate through the DOI definitions
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
पूर्णांक cipso_v4_करोi_walk(u32 *skip_cnt,
		     पूर्णांक (*callback) (काष्ठा cipso_v4_करोi *करोi_def, व्योम *arg),
		     व्योम *cb_arg)
अणु
	पूर्णांक ret_val = -ENOENT;
	u32 करोi_cnt = 0;
	काष्ठा cipso_v4_करोi *iter_करोi;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(iter_करोi, &cipso_v4_करोi_list, list)
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

/*
 * Label Mapping Functions
 */

/**
 * cipso_v4_map_lvl_valid - Checks to see अगर the given level is understood
 * @करोi_def: the DOI definition
 * @level: the level to check
 *
 * Description:
 * Checks the given level against the given DOI definition and वापसs a
 * negative value अगर the level करोes not have a valid mapping and a zero value
 * अगर the level is defined by the DOI.
 *
 */
अटल पूर्णांक cipso_v4_map_lvl_valid(स्थिर काष्ठा cipso_v4_करोi *करोi_def, u8 level)
अणु
	चयन (करोi_def->type) अणु
	हाल CIPSO_V4_MAP_PASS:
		वापस 0;
	हाल CIPSO_V4_MAP_TRANS:
		अगर ((level < करोi_def->map.std->lvl.cipso_size) &&
		    (करोi_def->map.std->lvl.cipso[level] < CIPSO_V4_INV_LVL))
			वापस 0;
		अवरोध;
	पूर्ण

	वापस -EFAULT;
पूर्ण

/**
 * cipso_v4_map_lvl_hton - Perक्रमm a level mapping from the host to the network
 * @करोi_def: the DOI definition
 * @host_lvl: the host MLS level
 * @net_lvl: the network/CIPSO MLS level
 *
 * Description:
 * Perक्रमm a label mapping to translate a local MLS level to the correct
 * CIPSO level using the given DOI definition.  Returns zero on success,
 * negative values otherwise.
 *
 */
अटल पूर्णांक cipso_v4_map_lvl_hton(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				 u32 host_lvl,
				 u32 *net_lvl)
अणु
	चयन (करोi_def->type) अणु
	हाल CIPSO_V4_MAP_PASS:
		*net_lvl = host_lvl;
		वापस 0;
	हाल CIPSO_V4_MAP_TRANS:
		अगर (host_lvl < करोi_def->map.std->lvl.local_size &&
		    करोi_def->map.std->lvl.local[host_lvl] < CIPSO_V4_INV_LVL) अणु
			*net_lvl = करोi_def->map.std->lvl.local[host_lvl];
			वापस 0;
		पूर्ण
		वापस -EPERM;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * cipso_v4_map_lvl_ntoh - Perक्रमm a level mapping from the network to the host
 * @करोi_def: the DOI definition
 * @net_lvl: the network/CIPSO MLS level
 * @host_lvl: the host MLS level
 *
 * Description:
 * Perक्रमm a label mapping to translate a CIPSO level to the correct local MLS
 * level using the given DOI definition.  Returns zero on success, negative
 * values otherwise.
 *
 */
अटल पूर्णांक cipso_v4_map_lvl_ntoh(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				 u32 net_lvl,
				 u32 *host_lvl)
अणु
	काष्ठा cipso_v4_std_map_tbl *map_tbl;

	चयन (करोi_def->type) अणु
	हाल CIPSO_V4_MAP_PASS:
		*host_lvl = net_lvl;
		वापस 0;
	हाल CIPSO_V4_MAP_TRANS:
		map_tbl = करोi_def->map.std;
		अगर (net_lvl < map_tbl->lvl.cipso_size &&
		    map_tbl->lvl.cipso[net_lvl] < CIPSO_V4_INV_LVL) अणु
			*host_lvl = करोi_def->map.std->lvl.cipso[net_lvl];
			वापस 0;
		पूर्ण
		वापस -EPERM;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * cipso_v4_map_cat_rbm_valid - Checks to see अगर the category biपंचांगap is valid
 * @करोi_def: the DOI definition
 * @biपंचांगap: category biपंचांगap
 * @biपंचांगap_len: biपंचांगap length in bytes
 *
 * Description:
 * Checks the given category biपंचांगap against the given DOI definition and
 * वापसs a negative value अगर any of the categories in the biपंचांगap करो not have
 * a valid mapping and a zero value अगर all of the categories are valid.
 *
 */
अटल पूर्णांक cipso_v4_map_cat_rbm_valid(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				      स्थिर अचिन्हित अक्षर *biपंचांगap,
				      u32 biपंचांगap_len)
अणु
	पूर्णांक cat = -1;
	u32 biपंचांगap_len_bits = biपंचांगap_len * 8;
	u32 cipso_cat_size;
	u32 *cipso_array;

	चयन (करोi_def->type) अणु
	हाल CIPSO_V4_MAP_PASS:
		वापस 0;
	हाल CIPSO_V4_MAP_TRANS:
		cipso_cat_size = करोi_def->map.std->cat.cipso_size;
		cipso_array = करोi_def->map.std->cat.cipso;
		क्रम (;;) अणु
			cat = netlbl_biपंचांगap_walk(biपंचांगap,
						 biपंचांगap_len_bits,
						 cat + 1,
						 1);
			अगर (cat < 0)
				अवरोध;
			अगर (cat >= cipso_cat_size ||
			    cipso_array[cat] >= CIPSO_V4_INV_CAT)
				वापस -EFAULT;
		पूर्ण

		अगर (cat == -1)
			वापस 0;
		अवरोध;
	पूर्ण

	वापस -EFAULT;
पूर्ण

/**
 * cipso_v4_map_cat_rbm_hton - Perक्रमm a category mapping from host to network
 * @करोi_def: the DOI definition
 * @secattr: the security attributes
 * @net_cat: the zero'd out category biपंचांगap in network/CIPSO क्रमmat
 * @net_cat_len: the length of the CIPSO biपंचांगap in bytes
 *
 * Description:
 * Perक्रमm a label mapping to translate a local MLS category biपंचांगap to the
 * correct CIPSO biपंचांगap using the given DOI definition.  Returns the minimum
 * size in bytes of the network biपंचांगap on success, negative values otherwise.
 *
 */
अटल पूर्णांक cipso_v4_map_cat_rbm_hton(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				     स्थिर काष्ठा netlbl_lsm_secattr *secattr,
				     अचिन्हित अक्षर *net_cat,
				     u32 net_cat_len)
अणु
	पूर्णांक host_spot = -1;
	u32 net_spot = CIPSO_V4_INV_CAT;
	u32 net_spot_max = 0;
	u32 net_clen_bits = net_cat_len * 8;
	u32 host_cat_size = 0;
	u32 *host_cat_array = शून्य;

	अगर (करोi_def->type == CIPSO_V4_MAP_TRANS) अणु
		host_cat_size = करोi_def->map.std->cat.local_size;
		host_cat_array = करोi_def->map.std->cat.local;
	पूर्ण

	क्रम (;;) अणु
		host_spot = netlbl_caपंचांगap_walk(secattr->attr.mls.cat,
					       host_spot + 1);
		अगर (host_spot < 0)
			अवरोध;

		चयन (करोi_def->type) अणु
		हाल CIPSO_V4_MAP_PASS:
			net_spot = host_spot;
			अवरोध;
		हाल CIPSO_V4_MAP_TRANS:
			अगर (host_spot >= host_cat_size)
				वापस -EPERM;
			net_spot = host_cat_array[host_spot];
			अगर (net_spot >= CIPSO_V4_INV_CAT)
				वापस -EPERM;
			अवरोध;
		पूर्ण
		अगर (net_spot >= net_clen_bits)
			वापस -ENOSPC;
		netlbl_biपंचांगap_setbit(net_cat, net_spot, 1);

		अगर (net_spot > net_spot_max)
			net_spot_max = net_spot;
	पूर्ण

	अगर (++net_spot_max % 8)
		वापस net_spot_max / 8 + 1;
	वापस net_spot_max / 8;
पूर्ण

/**
 * cipso_v4_map_cat_rbm_ntoh - Perक्रमm a category mapping from network to host
 * @करोi_def: the DOI definition
 * @net_cat: the category biपंचांगap in network/CIPSO क्रमmat
 * @net_cat_len: the length of the CIPSO biपंचांगap in bytes
 * @secattr: the security attributes
 *
 * Description:
 * Perक्रमm a label mapping to translate a CIPSO biपंचांगap to the correct local
 * MLS category biपंचांगap using the given DOI definition.  Returns zero on
 * success, negative values on failure.
 *
 */
अटल पूर्णांक cipso_v4_map_cat_rbm_ntoh(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				     स्थिर अचिन्हित अक्षर *net_cat,
				     u32 net_cat_len,
				     काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	पूर्णांक net_spot = -1;
	u32 host_spot = CIPSO_V4_INV_CAT;
	u32 net_clen_bits = net_cat_len * 8;
	u32 net_cat_size = 0;
	u32 *net_cat_array = शून्य;

	अगर (करोi_def->type == CIPSO_V4_MAP_TRANS) अणु
		net_cat_size = करोi_def->map.std->cat.cipso_size;
		net_cat_array = करोi_def->map.std->cat.cipso;
	पूर्ण

	क्रम (;;) अणु
		net_spot = netlbl_biपंचांगap_walk(net_cat,
					      net_clen_bits,
					      net_spot + 1,
					      1);
		अगर (net_spot < 0) अणु
			अगर (net_spot == -2)
				वापस -EFAULT;
			वापस 0;
		पूर्ण

		चयन (करोi_def->type) अणु
		हाल CIPSO_V4_MAP_PASS:
			host_spot = net_spot;
			अवरोध;
		हाल CIPSO_V4_MAP_TRANS:
			अगर (net_spot >= net_cat_size)
				वापस -EPERM;
			host_spot = net_cat_array[net_spot];
			अगर (host_spot >= CIPSO_V4_INV_CAT)
				वापस -EPERM;
			अवरोध;
		पूर्ण
		ret_val = netlbl_caपंचांगap_setbit(&secattr->attr.mls.cat,
						       host_spot,
						       GFP_ATOMIC);
		अगर (ret_val != 0)
			वापस ret_val;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * cipso_v4_map_cat_क्रमागत_valid - Checks to see अगर the categories are valid
 * @करोi_def: the DOI definition
 * @क्रमागतcat: category list
 * @क्रमागतcat_len: length of the category list in bytes
 *
 * Description:
 * Checks the given categories against the given DOI definition and वापसs a
 * negative value अगर any of the categories करो not have a valid mapping and a
 * zero value अगर all of the categories are valid.
 *
 */
अटल पूर्णांक cipso_v4_map_cat_क्रमागत_valid(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				       स्थिर अचिन्हित अक्षर *क्रमागतcat,
				       u32 क्रमागतcat_len)
अणु
	u16 cat;
	पूर्णांक cat_prev = -1;
	u32 iter;

	अगर (करोi_def->type != CIPSO_V4_MAP_PASS || क्रमागतcat_len & 0x01)
		वापस -EFAULT;

	क्रम (iter = 0; iter < क्रमागतcat_len; iter += 2) अणु
		cat = get_unaligned_be16(&क्रमागतcat[iter]);
		अगर (cat <= cat_prev)
			वापस -EFAULT;
		cat_prev = cat;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cipso_v4_map_cat_क्रमागत_hton - Perक्रमm a category mapping from host to network
 * @करोi_def: the DOI definition
 * @secattr: the security attributes
 * @net_cat: the zero'd out category list in network/CIPSO क्रमmat
 * @net_cat_len: the length of the CIPSO category list in bytes
 *
 * Description:
 * Perक्रमm a label mapping to translate a local MLS category biपंचांगap to the
 * correct CIPSO category list using the given DOI definition.   Returns the
 * size in bytes of the network category biपंचांगap on success, negative values
 * otherwise.
 *
 */
अटल पूर्णांक cipso_v4_map_cat_क्रमागत_hton(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				      स्थिर काष्ठा netlbl_lsm_secattr *secattr,
				      अचिन्हित अक्षर *net_cat,
				      u32 net_cat_len)
अणु
	पूर्णांक cat = -1;
	u32 cat_iter = 0;

	क्रम (;;) अणु
		cat = netlbl_caपंचांगap_walk(secattr->attr.mls.cat, cat + 1);
		अगर (cat < 0)
			अवरोध;
		अगर ((cat_iter + 2) > net_cat_len)
			वापस -ENOSPC;

		*((__be16 *)&net_cat[cat_iter]) = htons(cat);
		cat_iter += 2;
	पूर्ण

	वापस cat_iter;
पूर्ण

/**
 * cipso_v4_map_cat_क्रमागत_ntoh - Perक्रमm a category mapping from network to host
 * @करोi_def: the DOI definition
 * @net_cat: the category list in network/CIPSO क्रमmat
 * @net_cat_len: the length of the CIPSO biपंचांगap in bytes
 * @secattr: the security attributes
 *
 * Description:
 * Perक्रमm a label mapping to translate a CIPSO category list to the correct
 * local MLS category biपंचांगap using the given DOI definition.  Returns zero on
 * success, negative values on failure.
 *
 */
अटल पूर्णांक cipso_v4_map_cat_क्रमागत_ntoh(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				      स्थिर अचिन्हित अक्षर *net_cat,
				      u32 net_cat_len,
				      काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	u32 iter;

	क्रम (iter = 0; iter < net_cat_len; iter += 2) अणु
		ret_val = netlbl_caपंचांगap_setbit(&secattr->attr.mls.cat,
					     get_unaligned_be16(&net_cat[iter]),
					     GFP_ATOMIC);
		अगर (ret_val != 0)
			वापस ret_val;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cipso_v4_map_cat_rng_valid - Checks to see अगर the categories are valid
 * @करोi_def: the DOI definition
 * @rngcat: category list
 * @rngcat_len: length of the category list in bytes
 *
 * Description:
 * Checks the given categories against the given DOI definition and वापसs a
 * negative value अगर any of the categories करो not have a valid mapping and a
 * zero value अगर all of the categories are valid.
 *
 */
अटल पूर्णांक cipso_v4_map_cat_rng_valid(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				      स्थिर अचिन्हित अक्षर *rngcat,
				      u32 rngcat_len)
अणु
	u16 cat_high;
	u16 cat_low;
	u32 cat_prev = CIPSO_V4_MAX_REM_CATS + 1;
	u32 iter;

	अगर (करोi_def->type != CIPSO_V4_MAP_PASS || rngcat_len & 0x01)
		वापस -EFAULT;

	क्रम (iter = 0; iter < rngcat_len; iter += 4) अणु
		cat_high = get_unaligned_be16(&rngcat[iter]);
		अगर ((iter + 4) <= rngcat_len)
			cat_low = get_unaligned_be16(&rngcat[iter + 2]);
		अन्यथा
			cat_low = 0;

		अगर (cat_high > cat_prev)
			वापस -EFAULT;

		cat_prev = cat_low;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cipso_v4_map_cat_rng_hton - Perक्रमm a category mapping from host to network
 * @करोi_def: the DOI definition
 * @secattr: the security attributes
 * @net_cat: the zero'd out category list in network/CIPSO क्रमmat
 * @net_cat_len: the length of the CIPSO category list in bytes
 *
 * Description:
 * Perक्रमm a label mapping to translate a local MLS category biपंचांगap to the
 * correct CIPSO category list using the given DOI definition.   Returns the
 * size in bytes of the network category biपंचांगap on success, negative values
 * otherwise.
 *
 */
अटल पूर्णांक cipso_v4_map_cat_rng_hton(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				     स्थिर काष्ठा netlbl_lsm_secattr *secattr,
				     अचिन्हित अक्षर *net_cat,
				     u32 net_cat_len)
अणु
	पूर्णांक iter = -1;
	u16 array[CIPSO_V4_TAG_RNG_CAT_MAX * 2];
	u32 array_cnt = 0;
	u32 cat_size = 0;

	/* make sure we करोn't overflow the 'array[]' variable */
	अगर (net_cat_len >
	    (CIPSO_V4_OPT_LEN_MAX - CIPSO_V4_HDR_LEN - CIPSO_V4_TAG_RNG_BLEN))
		वापस -ENOSPC;

	क्रम (;;) अणु
		iter = netlbl_caपंचांगap_walk(secattr->attr.mls.cat, iter + 1);
		अगर (iter < 0)
			अवरोध;
		cat_size += (iter == 0 ? 0 : माप(u16));
		अगर (cat_size > net_cat_len)
			वापस -ENOSPC;
		array[array_cnt++] = iter;

		iter = netlbl_caपंचांगap_walkrng(secattr->attr.mls.cat, iter);
		अगर (iter < 0)
			वापस -EFAULT;
		cat_size += माप(u16);
		अगर (cat_size > net_cat_len)
			वापस -ENOSPC;
		array[array_cnt++] = iter;
	पूर्ण

	क्रम (iter = 0; array_cnt > 0;) अणु
		*((__be16 *)&net_cat[iter]) = htons(array[--array_cnt]);
		iter += 2;
		array_cnt--;
		अगर (array[array_cnt] != 0) अणु
			*((__be16 *)&net_cat[iter]) = htons(array[array_cnt]);
			iter += 2;
		पूर्ण
	पूर्ण

	वापस cat_size;
पूर्ण

/**
 * cipso_v4_map_cat_rng_ntoh - Perक्रमm a category mapping from network to host
 * @करोi_def: the DOI definition
 * @net_cat: the category list in network/CIPSO क्रमmat
 * @net_cat_len: the length of the CIPSO biपंचांगap in bytes
 * @secattr: the security attributes
 *
 * Description:
 * Perक्रमm a label mapping to translate a CIPSO category list to the correct
 * local MLS category biपंचांगap using the given DOI definition.  Returns zero on
 * success, negative values on failure.
 *
 */
अटल पूर्णांक cipso_v4_map_cat_rng_ntoh(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				     स्थिर अचिन्हित अक्षर *net_cat,
				     u32 net_cat_len,
				     काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	u32 net_iter;
	u16 cat_low;
	u16 cat_high;

	क्रम (net_iter = 0; net_iter < net_cat_len; net_iter += 4) अणु
		cat_high = get_unaligned_be16(&net_cat[net_iter]);
		अगर ((net_iter + 4) <= net_cat_len)
			cat_low = get_unaligned_be16(&net_cat[net_iter + 2]);
		अन्यथा
			cat_low = 0;

		ret_val = netlbl_caपंचांगap_setrng(&secattr->attr.mls.cat,
					       cat_low,
					       cat_high,
					       GFP_ATOMIC);
		अगर (ret_val != 0)
			वापस ret_val;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Protocol Handling Functions
 */

/**
 * cipso_v4_gentag_hdr - Generate a CIPSO option header
 * @करोi_def: the DOI definition
 * @len: the total tag length in bytes, not including this header
 * @buf: the CIPSO option buffer
 *
 * Description:
 * Write a CIPSO header पूर्णांकo the beginning of @buffer.
 *
 */
अटल व्योम cipso_v4_gentag_hdr(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				अचिन्हित अक्षर *buf,
				u32 len)
अणु
	buf[0] = IPOPT_CIPSO;
	buf[1] = CIPSO_V4_HDR_LEN + len;
	put_unaligned_be32(करोi_def->करोi, &buf[2]);
पूर्ण

/**
 * cipso_v4_gentag_rbm - Generate a CIPSO restricted biपंचांगap tag (type #1)
 * @करोi_def: the DOI definition
 * @secattr: the security attributes
 * @buffer: the option buffer
 * @buffer_len: length of buffer in bytes
 *
 * Description:
 * Generate a CIPSO option using the restricted biपंचांगap tag, tag type #1.  The
 * actual buffer length may be larger than the indicated size due to
 * translation between host and network category biपंचांगaps.  Returns the size of
 * the tag on success, negative values on failure.
 *
 */
अटल पूर्णांक cipso_v4_gentag_rbm(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
			       स्थिर काष्ठा netlbl_lsm_secattr *secattr,
			       अचिन्हित अक्षर *buffer,
			       u32 buffer_len)
अणु
	पूर्णांक ret_val;
	u32 tag_len;
	u32 level;

	अगर ((secattr->flags & NETLBL_SECATTR_MLS_LVL) == 0)
		वापस -EPERM;

	ret_val = cipso_v4_map_lvl_hton(करोi_def,
					secattr->attr.mls.lvl,
					&level);
	अगर (ret_val != 0)
		वापस ret_val;

	अगर (secattr->flags & NETLBL_SECATTR_MLS_CAT) अणु
		ret_val = cipso_v4_map_cat_rbm_hton(करोi_def,
						    secattr,
						    &buffer[4],
						    buffer_len - 4);
		अगर (ret_val < 0)
			वापस ret_val;

		/* This will send packets using the "optimized" क्रमmat when
		 * possible as specअगरied in  section 3.4.2.6 of the
		 * CIPSO draft. */
		अगर (cipso_v4_rbm_optfmt && ret_val > 0 && ret_val <= 10)
			tag_len = 14;
		अन्यथा
			tag_len = 4 + ret_val;
	पूर्ण अन्यथा
		tag_len = 4;

	buffer[0] = CIPSO_V4_TAG_RBITMAP;
	buffer[1] = tag_len;
	buffer[3] = level;

	वापस tag_len;
पूर्ण

/**
 * cipso_v4_parsetag_rbm - Parse a CIPSO restricted biपंचांगap tag
 * @करोi_def: the DOI definition
 * @tag: the CIPSO tag
 * @secattr: the security attributes
 *
 * Description:
 * Parse a CIPSO restricted biपंचांगap tag (tag type #1) and वापस the security
 * attributes in @secattr.  Return zero on success, negatives values on
 * failure.
 *
 */
अटल पूर्णांक cipso_v4_parsetag_rbm(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				 स्थिर अचिन्हित अक्षर *tag,
				 काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	u8 tag_len = tag[1];
	u32 level;

	ret_val = cipso_v4_map_lvl_ntoh(करोi_def, tag[3], &level);
	अगर (ret_val != 0)
		वापस ret_val;
	secattr->attr.mls.lvl = level;
	secattr->flags |= NETLBL_SECATTR_MLS_LVL;

	अगर (tag_len > 4) अणु
		ret_val = cipso_v4_map_cat_rbm_ntoh(करोi_def,
						    &tag[4],
						    tag_len - 4,
						    secattr);
		अगर (ret_val != 0) अणु
			netlbl_caपंचांगap_मुक्त(secattr->attr.mls.cat);
			वापस ret_val;
		पूर्ण

		अगर (secattr->attr.mls.cat)
			secattr->flags |= NETLBL_SECATTR_MLS_CAT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cipso_v4_gentag_क्रमागत - Generate a CIPSO क्रमागतerated tag (type #2)
 * @करोi_def: the DOI definition
 * @secattr: the security attributes
 * @buffer: the option buffer
 * @buffer_len: length of buffer in bytes
 *
 * Description:
 * Generate a CIPSO option using the क्रमागतerated tag, tag type #2.  Returns the
 * size of the tag on success, negative values on failure.
 *
 */
अटल पूर्णांक cipso_v4_gentag_क्रमागत(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				स्थिर काष्ठा netlbl_lsm_secattr *secattr,
				अचिन्हित अक्षर *buffer,
				u32 buffer_len)
अणु
	पूर्णांक ret_val;
	u32 tag_len;
	u32 level;

	अगर (!(secattr->flags & NETLBL_SECATTR_MLS_LVL))
		वापस -EPERM;

	ret_val = cipso_v4_map_lvl_hton(करोi_def,
					secattr->attr.mls.lvl,
					&level);
	अगर (ret_val != 0)
		वापस ret_val;

	अगर (secattr->flags & NETLBL_SECATTR_MLS_CAT) अणु
		ret_val = cipso_v4_map_cat_क्रमागत_hton(करोi_def,
						     secattr,
						     &buffer[4],
						     buffer_len - 4);
		अगर (ret_val < 0)
			वापस ret_val;

		tag_len = 4 + ret_val;
	पूर्ण अन्यथा
		tag_len = 4;

	buffer[0] = CIPSO_V4_TAG_ENUM;
	buffer[1] = tag_len;
	buffer[3] = level;

	वापस tag_len;
पूर्ण

/**
 * cipso_v4_parsetag_क्रमागत - Parse a CIPSO क्रमागतerated tag
 * @करोi_def: the DOI definition
 * @tag: the CIPSO tag
 * @secattr: the security attributes
 *
 * Description:
 * Parse a CIPSO क्रमागतerated tag (tag type #2) and वापस the security
 * attributes in @secattr.  Return zero on success, negatives values on
 * failure.
 *
 */
अटल पूर्णांक cipso_v4_parsetag_क्रमागत(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				  स्थिर अचिन्हित अक्षर *tag,
				  काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	u8 tag_len = tag[1];
	u32 level;

	ret_val = cipso_v4_map_lvl_ntoh(करोi_def, tag[3], &level);
	अगर (ret_val != 0)
		वापस ret_val;
	secattr->attr.mls.lvl = level;
	secattr->flags |= NETLBL_SECATTR_MLS_LVL;

	अगर (tag_len > 4) अणु
		ret_val = cipso_v4_map_cat_क्रमागत_ntoh(करोi_def,
						     &tag[4],
						     tag_len - 4,
						     secattr);
		अगर (ret_val != 0) अणु
			netlbl_caपंचांगap_मुक्त(secattr->attr.mls.cat);
			वापस ret_val;
		पूर्ण

		secattr->flags |= NETLBL_SECATTR_MLS_CAT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cipso_v4_gentag_rng - Generate a CIPSO ranged tag (type #5)
 * @करोi_def: the DOI definition
 * @secattr: the security attributes
 * @buffer: the option buffer
 * @buffer_len: length of buffer in bytes
 *
 * Description:
 * Generate a CIPSO option using the ranged tag, tag type #5.  Returns the
 * size of the tag on success, negative values on failure.
 *
 */
अटल पूर्णांक cipso_v4_gentag_rng(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
			       स्थिर काष्ठा netlbl_lsm_secattr *secattr,
			       अचिन्हित अक्षर *buffer,
			       u32 buffer_len)
अणु
	पूर्णांक ret_val;
	u32 tag_len;
	u32 level;

	अगर (!(secattr->flags & NETLBL_SECATTR_MLS_LVL))
		वापस -EPERM;

	ret_val = cipso_v4_map_lvl_hton(करोi_def,
					secattr->attr.mls.lvl,
					&level);
	अगर (ret_val != 0)
		वापस ret_val;

	अगर (secattr->flags & NETLBL_SECATTR_MLS_CAT) अणु
		ret_val = cipso_v4_map_cat_rng_hton(करोi_def,
						    secattr,
						    &buffer[4],
						    buffer_len - 4);
		अगर (ret_val < 0)
			वापस ret_val;

		tag_len = 4 + ret_val;
	पूर्ण अन्यथा
		tag_len = 4;

	buffer[0] = CIPSO_V4_TAG_RANGE;
	buffer[1] = tag_len;
	buffer[3] = level;

	वापस tag_len;
पूर्ण

/**
 * cipso_v4_parsetag_rng - Parse a CIPSO ranged tag
 * @करोi_def: the DOI definition
 * @tag: the CIPSO tag
 * @secattr: the security attributes
 *
 * Description:
 * Parse a CIPSO ranged tag (tag type #5) and वापस the security attributes
 * in @secattr.  Return zero on success, negatives values on failure.
 *
 */
अटल पूर्णांक cipso_v4_parsetag_rng(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				 स्थिर अचिन्हित अक्षर *tag,
				 काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	u8 tag_len = tag[1];
	u32 level;

	ret_val = cipso_v4_map_lvl_ntoh(करोi_def, tag[3], &level);
	अगर (ret_val != 0)
		वापस ret_val;
	secattr->attr.mls.lvl = level;
	secattr->flags |= NETLBL_SECATTR_MLS_LVL;

	अगर (tag_len > 4) अणु
		ret_val = cipso_v4_map_cat_rng_ntoh(करोi_def,
						    &tag[4],
						    tag_len - 4,
						    secattr);
		अगर (ret_val != 0) अणु
			netlbl_caपंचांगap_मुक्त(secattr->attr.mls.cat);
			वापस ret_val;
		पूर्ण

		अगर (secattr->attr.mls.cat)
			secattr->flags |= NETLBL_SECATTR_MLS_CAT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cipso_v4_gentag_loc - Generate a CIPSO local tag (non-standard)
 * @करोi_def: the DOI definition
 * @secattr: the security attributes
 * @buffer: the option buffer
 * @buffer_len: length of buffer in bytes
 *
 * Description:
 * Generate a CIPSO option using the local tag.  Returns the size of the tag
 * on success, negative values on failure.
 *
 */
अटल पूर्णांक cipso_v4_gentag_loc(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
			       स्थिर काष्ठा netlbl_lsm_secattr *secattr,
			       अचिन्हित अक्षर *buffer,
			       u32 buffer_len)
अणु
	अगर (!(secattr->flags & NETLBL_SECATTR_SECID))
		वापस -EPERM;

	buffer[0] = CIPSO_V4_TAG_LOCAL;
	buffer[1] = CIPSO_V4_TAG_LOC_BLEN;
	*(u32 *)&buffer[2] = secattr->attr.secid;

	वापस CIPSO_V4_TAG_LOC_BLEN;
पूर्ण

/**
 * cipso_v4_parsetag_loc - Parse a CIPSO local tag
 * @करोi_def: the DOI definition
 * @tag: the CIPSO tag
 * @secattr: the security attributes
 *
 * Description:
 * Parse a CIPSO local tag and वापस the security attributes in @secattr.
 * Return zero on success, negatives values on failure.
 *
 */
अटल पूर्णांक cipso_v4_parsetag_loc(स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				 स्थिर अचिन्हित अक्षर *tag,
				 काष्ठा netlbl_lsm_secattr *secattr)
अणु
	secattr->attr.secid = *(u32 *)&tag[2];
	secattr->flags |= NETLBL_SECATTR_SECID;

	वापस 0;
पूर्ण

/**
 * cipso_v4_optptr - Find the CIPSO option in the packet
 * @skb: the packet
 *
 * Description:
 * Parse the packet's IP header looking क्रम a CIPSO option.  Returns a poपूर्णांकer
 * to the start of the CIPSO option on success, शून्य अगर one is not found.
 *
 */
अचिन्हित अक्षर *cipso_v4_optptr(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	अचिन्हित अक्षर *optptr = (अचिन्हित अक्षर *)&(ip_hdr(skb)[1]);
	पूर्णांक optlen;
	पूर्णांक taglen;

	क्रम (optlen = iph->ihl*4 - माप(काष्ठा iphdr); optlen > 1; ) अणु
		चयन (optptr[0]) अणु
		हाल IPOPT_END:
			वापस शून्य;
		हाल IPOPT_NOOP:
			taglen = 1;
			अवरोध;
		शेष:
			taglen = optptr[1];
		पूर्ण
		अगर (!taglen || taglen > optlen)
			वापस शून्य;
		अगर (optptr[0] == IPOPT_CIPSO)
			वापस optptr;

		optlen -= taglen;
		optptr += taglen;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * cipso_v4_validate - Validate a CIPSO option
 * @skb: the packet
 * @option: the start of the option, on error it is set to poपूर्णांक to the error
 *
 * Description:
 * This routine is called to validate a CIPSO option, it checks all of the
 * fields to ensure that they are at least valid, see the draft snippet below
 * क्रम details.  If the option is valid then a zero value is वापसed and
 * the value of @option is unchanged.  If the option is invalid then a
 * non-zero value is वापसed and @option is adjusted to poपूर्णांक to the
 * offending portion of the option.  From the IETF draft ...
 *
 *  "If any field within the CIPSO options, such as the DOI identअगरier, is not
 *   recognized the IP datagram is discarded and an ICMP 'parameter problem'
 *   (type 12) is generated and वापसed.  The ICMP code field is set to 'bad
 *   parameter' (code 0) and the poपूर्णांकer is set to the start of the CIPSO field
 *   that is unrecognized."
 *
 */
पूर्णांक cipso_v4_validate(स्थिर काष्ठा sk_buff *skb, अचिन्हित अक्षर **option)
अणु
	अचिन्हित अक्षर *opt = *option;
	अचिन्हित अक्षर *tag;
	अचिन्हित अक्षर opt_iter;
	अचिन्हित अक्षर err_offset = 0;
	u8 opt_len;
	u8 tag_len;
	काष्ठा cipso_v4_करोi *करोi_def = शून्य;
	u32 tag_iter;

	/* caller alपढ़ोy checks क्रम length values that are too large */
	opt_len = opt[1];
	अगर (opt_len < 8) अणु
		err_offset = 1;
		जाओ validate_वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	करोi_def = cipso_v4_करोi_search(get_unaligned_be32(&opt[2]));
	अगर (!करोi_def) अणु
		err_offset = 2;
		जाओ validate_वापस_locked;
	पूर्ण

	opt_iter = CIPSO_V4_HDR_LEN;
	tag = opt + opt_iter;
	जबतक (opt_iter < opt_len) अणु
		क्रम (tag_iter = 0; करोi_def->tags[tag_iter] != tag[0];)
			अगर (करोi_def->tags[tag_iter] == CIPSO_V4_TAG_INVALID ||
			    ++tag_iter == CIPSO_V4_TAG_MAXCNT) अणु
				err_offset = opt_iter;
				जाओ validate_वापस_locked;
			पूर्ण

		अगर (opt_iter + 1 == opt_len) अणु
			err_offset = opt_iter;
			जाओ validate_वापस_locked;
		पूर्ण
		tag_len = tag[1];
		अगर (tag_len > (opt_len - opt_iter)) अणु
			err_offset = opt_iter + 1;
			जाओ validate_वापस_locked;
		पूर्ण

		चयन (tag[0]) अणु
		हाल CIPSO_V4_TAG_RBITMAP:
			अगर (tag_len < CIPSO_V4_TAG_RBM_BLEN) अणु
				err_offset = opt_iter + 1;
				जाओ validate_वापस_locked;
			पूर्ण

			/* We are alपढ़ोy going to करो all the verअगरication
			 * necessary at the socket layer so from our poपूर्णांक of
			 * view it is safe to turn these checks off (and less
			 * work), however, the CIPSO draft says we should करो
			 * all the CIPSO validations here but it करोesn't
			 * really specअगरy _exactly_ what we need to validate
			 * ... so, just make it a sysctl tunable. */
			अगर (cipso_v4_rbm_strictvalid) अणु
				अगर (cipso_v4_map_lvl_valid(करोi_def,
							   tag[3]) < 0) अणु
					err_offset = opt_iter + 3;
					जाओ validate_वापस_locked;
				पूर्ण
				अगर (tag_len > CIPSO_V4_TAG_RBM_BLEN &&
				    cipso_v4_map_cat_rbm_valid(करोi_def,
							    &tag[4],
							    tag_len - 4) < 0) अणु
					err_offset = opt_iter + 4;
					जाओ validate_वापस_locked;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल CIPSO_V4_TAG_ENUM:
			अगर (tag_len < CIPSO_V4_TAG_ENUM_BLEN) अणु
				err_offset = opt_iter + 1;
				जाओ validate_वापस_locked;
			पूर्ण

			अगर (cipso_v4_map_lvl_valid(करोi_def,
						   tag[3]) < 0) अणु
				err_offset = opt_iter + 3;
				जाओ validate_वापस_locked;
			पूर्ण
			अगर (tag_len > CIPSO_V4_TAG_ENUM_BLEN &&
			    cipso_v4_map_cat_क्रमागत_valid(करोi_def,
							&tag[4],
							tag_len - 4) < 0) अणु
				err_offset = opt_iter + 4;
				जाओ validate_वापस_locked;
			पूर्ण
			अवरोध;
		हाल CIPSO_V4_TAG_RANGE:
			अगर (tag_len < CIPSO_V4_TAG_RNG_BLEN) अणु
				err_offset = opt_iter + 1;
				जाओ validate_वापस_locked;
			पूर्ण

			अगर (cipso_v4_map_lvl_valid(करोi_def,
						   tag[3]) < 0) अणु
				err_offset = opt_iter + 3;
				जाओ validate_वापस_locked;
			पूर्ण
			अगर (tag_len > CIPSO_V4_TAG_RNG_BLEN &&
			    cipso_v4_map_cat_rng_valid(करोi_def,
						       &tag[4],
						       tag_len - 4) < 0) अणु
				err_offset = opt_iter + 4;
				जाओ validate_वापस_locked;
			पूर्ण
			अवरोध;
		हाल CIPSO_V4_TAG_LOCAL:
			/* This is a non-standard tag that we only allow क्रम
			 * local connections, so अगर the incoming पूर्णांकerface is
			 * not the loopback device drop the packet. Further,
			 * there is no legitimate reason क्रम setting this from
			 * userspace so reject it अगर skb is शून्य. */
			अगर (!skb || !(skb->dev->flags & IFF_LOOPBACK)) अणु
				err_offset = opt_iter;
				जाओ validate_वापस_locked;
			पूर्ण
			अगर (tag_len != CIPSO_V4_TAG_LOC_BLEN) अणु
				err_offset = opt_iter + 1;
				जाओ validate_वापस_locked;
			पूर्ण
			अवरोध;
		शेष:
			err_offset = opt_iter;
			जाओ validate_वापस_locked;
		पूर्ण

		tag += tag_len;
		opt_iter += tag_len;
	पूर्ण

validate_वापस_locked:
	rcu_पढ़ो_unlock();
validate_वापस:
	*option = opt + err_offset;
	वापस err_offset;
पूर्ण

/**
 * cipso_v4_error - Send the correct response क्रम a bad packet
 * @skb: the packet
 * @error: the error code
 * @gateway: CIPSO gateway flag
 *
 * Description:
 * Based on the error code given in @error, send an ICMP error message back to
 * the originating host.  From the IETF draft ...
 *
 *  "If the contents of the CIPSO [option] are valid but the security label is
 *   outside of the configured host or port label range, the datagram is
 *   discarded and an ICMP 'destination unreachable' (type 3) is generated and
 *   वापसed.  The code field of the ICMP is set to 'communication with
 *   destination network administratively prohibited' (code 9) or to
 *   'communication with destination host administratively prohibited'
 *   (code 10).  The value of the code is dependent on whether the originator
 *   of the ICMP message is acting as a CIPSO host or a CIPSO gateway.  The
 *   recipient of the ICMP message MUST be able to handle either value.  The
 *   same procedure is perक्रमmed अगर a CIPSO [option] can not be added to an
 *   IP packet because it is too large to fit in the IP options area."
 *
 *  "If the error is triggered by receipt of an ICMP message, the message is
 *   discarded and no response is permitted (consistent with general ICMP
 *   processing rules)."
 *
 */
व्योम cipso_v4_error(काष्ठा sk_buff *skb, पूर्णांक error, u32 gateway)
अणु
	अचिन्हित अक्षर optbuf[माप(काष्ठा ip_options) + 40];
	काष्ठा ip_options *opt = (काष्ठा ip_options *)optbuf;
	पूर्णांक res;

	अगर (ip_hdr(skb)->protocol == IPPROTO_ICMP || error != -EACCES)
		वापस;

	/*
	 * We might be called above the IP layer,
	 * so we can not use icmp_send and IPCB here.
	 */

	स_रखो(opt, 0, माप(काष्ठा ip_options));
	opt->optlen = ip_hdr(skb)->ihl*4 - माप(काष्ठा iphdr);
	rcu_पढ़ो_lock();
	res = __ip_options_compile(dev_net(skb->dev), opt, skb, शून्य);
	rcu_पढ़ो_unlock();

	अगर (res)
		वापस;

	अगर (gateway)
		__icmp_send(skb, ICMP_DEST_UNREACH, ICMP_NET_ANO, 0, opt);
	अन्यथा
		__icmp_send(skb, ICMP_DEST_UNREACH, ICMP_HOST_ANO, 0, opt);
पूर्ण

/**
 * cipso_v4_genopt - Generate a CIPSO option
 * @buf: the option buffer
 * @buf_len: the size of opt_buf
 * @करोi_def: the CIPSO DOI to use
 * @secattr: the security attributes
 *
 * Description:
 * Generate a CIPSO option using the DOI definition and security attributes
 * passed to the function.  Returns the length of the option on success and
 * negative values on failure.
 *
 */
अटल पूर्णांक cipso_v4_genopt(अचिन्हित अक्षर *buf, u32 buf_len,
			   स्थिर काष्ठा cipso_v4_करोi *करोi_def,
			   स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	u32 iter;

	अगर (buf_len <= CIPSO_V4_HDR_LEN)
		वापस -ENOSPC;

	/* XXX - This code assumes only one tag per CIPSO option which isn't
	 * really a good assumption to make but since we only support the MAC
	 * tags right now it is a safe assumption. */
	iter = 0;
	करो अणु
		स_रखो(buf, 0, buf_len);
		चयन (करोi_def->tags[iter]) अणु
		हाल CIPSO_V4_TAG_RBITMAP:
			ret_val = cipso_v4_gentag_rbm(करोi_def,
						   secattr,
						   &buf[CIPSO_V4_HDR_LEN],
						   buf_len - CIPSO_V4_HDR_LEN);
			अवरोध;
		हाल CIPSO_V4_TAG_ENUM:
			ret_val = cipso_v4_gentag_क्रमागत(करोi_def,
						   secattr,
						   &buf[CIPSO_V4_HDR_LEN],
						   buf_len - CIPSO_V4_HDR_LEN);
			अवरोध;
		हाल CIPSO_V4_TAG_RANGE:
			ret_val = cipso_v4_gentag_rng(करोi_def,
						   secattr,
						   &buf[CIPSO_V4_HDR_LEN],
						   buf_len - CIPSO_V4_HDR_LEN);
			अवरोध;
		हाल CIPSO_V4_TAG_LOCAL:
			ret_val = cipso_v4_gentag_loc(करोi_def,
						   secattr,
						   &buf[CIPSO_V4_HDR_LEN],
						   buf_len - CIPSO_V4_HDR_LEN);
			अवरोध;
		शेष:
			वापस -EPERM;
		पूर्ण

		iter++;
	पूर्ण जबतक (ret_val < 0 &&
		 iter < CIPSO_V4_TAG_MAXCNT &&
		 करोi_def->tags[iter] != CIPSO_V4_TAG_INVALID);
	अगर (ret_val < 0)
		वापस ret_val;
	cipso_v4_gentag_hdr(करोi_def, buf, ret_val);
	वापस CIPSO_V4_HDR_LEN + ret_val;
पूर्ण

/**
 * cipso_v4_sock_setattr - Add a CIPSO option to a socket
 * @sk: the socket
 * @करोi_def: the CIPSO DOI to use
 * @secattr: the specअगरic security attributes of the socket
 *
 * Description:
 * Set the CIPSO option on the given socket using the DOI definition and
 * security attributes passed to the function.  This function requires
 * exclusive access to @sk, which means it either needs to be in the
 * process of being created or locked.  Returns zero on success and negative
 * values on failure.
 *
 */
पूर्णांक cipso_v4_sock_setattr(काष्ठा sock *sk,
			  स्थिर काष्ठा cipso_v4_करोi *करोi_def,
			  स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val = -EPERM;
	अचिन्हित अक्षर *buf = शून्य;
	u32 buf_len;
	u32 opt_len;
	काष्ठा ip_options_rcu *old, *opt = शून्य;
	काष्ठा inet_sock *sk_inet;
	काष्ठा inet_connection_sock *sk_conn;

	/* In the हाल of sock_create_lite(), the sock->sk field is not
	 * defined yet but it is not a problem as the only users of these
	 * "lite" PF_INET sockets are functions which करो an accept() call
	 * afterwards so we will label the socket as part of the accept(). */
	अगर (!sk)
		वापस 0;

	/* We allocate the maximum CIPSO option size here so we are probably
	 * being a little wasteful, but it makes our lअगरe _much_ easier later
	 * on and after all we are only talking about 40 bytes. */
	buf_len = CIPSO_V4_OPT_LEN_MAX;
	buf = kदो_स्मृति(buf_len, GFP_ATOMIC);
	अगर (!buf) अणु
		ret_val = -ENOMEM;
		जाओ socket_setattr_failure;
	पूर्ण

	ret_val = cipso_v4_genopt(buf, buf_len, करोi_def, secattr);
	अगर (ret_val < 0)
		जाओ socket_setattr_failure;
	buf_len = ret_val;

	/* We can't use ip_options_get() directly because it makes a call to
	 * ip_options_get_alloc() which allocates memory with GFP_KERNEL and
	 * we won't always have CAP_NET_RAW even though we _always_ want to
	 * set the IPOPT_CIPSO option. */
	opt_len = (buf_len + 3) & ~3;
	opt = kzalloc(माप(*opt) + opt_len, GFP_ATOMIC);
	अगर (!opt) अणु
		ret_val = -ENOMEM;
		जाओ socket_setattr_failure;
	पूर्ण
	स_नकल(opt->opt.__data, buf, buf_len);
	opt->opt.optlen = opt_len;
	opt->opt.cipso = माप(काष्ठा iphdr);
	kमुक्त(buf);
	buf = शून्य;

	sk_inet = inet_sk(sk);

	old = rcu_dereference_रक्षित(sk_inet->inet_opt,
					lockdep_sock_is_held(sk));
	अगर (sk_inet->is_icsk) अणु
		sk_conn = inet_csk(sk);
		अगर (old)
			sk_conn->icsk_ext_hdr_len -= old->opt.optlen;
		sk_conn->icsk_ext_hdr_len += opt->opt.optlen;
		sk_conn->icsk_sync_mss(sk, sk_conn->icsk_pmtu_cookie);
	पूर्ण
	rcu_assign_poपूर्णांकer(sk_inet->inet_opt, opt);
	अगर (old)
		kमुक्त_rcu(old, rcu);

	वापस 0;

socket_setattr_failure:
	kमुक्त(buf);
	kमुक्त(opt);
	वापस ret_val;
पूर्ण

/**
 * cipso_v4_req_setattr - Add a CIPSO option to a connection request socket
 * @req: the connection request socket
 * @करोi_def: the CIPSO DOI to use
 * @secattr: the specअगरic security attributes of the socket
 *
 * Description:
 * Set the CIPSO option on the given socket using the DOI definition and
 * security attributes passed to the function.  Returns zero on success and
 * negative values on failure.
 *
 */
पूर्णांक cipso_v4_req_setattr(काष्ठा request_sock *req,
			 स्थिर काष्ठा cipso_v4_करोi *करोi_def,
			 स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val = -EPERM;
	अचिन्हित अक्षर *buf = शून्य;
	u32 buf_len;
	u32 opt_len;
	काष्ठा ip_options_rcu *opt = शून्य;
	काष्ठा inet_request_sock *req_inet;

	/* We allocate the maximum CIPSO option size here so we are probably
	 * being a little wasteful, but it makes our lअगरe _much_ easier later
	 * on and after all we are only talking about 40 bytes. */
	buf_len = CIPSO_V4_OPT_LEN_MAX;
	buf = kदो_स्मृति(buf_len, GFP_ATOMIC);
	अगर (!buf) अणु
		ret_val = -ENOMEM;
		जाओ req_setattr_failure;
	पूर्ण

	ret_val = cipso_v4_genopt(buf, buf_len, करोi_def, secattr);
	अगर (ret_val < 0)
		जाओ req_setattr_failure;
	buf_len = ret_val;

	/* We can't use ip_options_get() directly because it makes a call to
	 * ip_options_get_alloc() which allocates memory with GFP_KERNEL and
	 * we won't always have CAP_NET_RAW even though we _always_ want to
	 * set the IPOPT_CIPSO option. */
	opt_len = (buf_len + 3) & ~3;
	opt = kzalloc(माप(*opt) + opt_len, GFP_ATOMIC);
	अगर (!opt) अणु
		ret_val = -ENOMEM;
		जाओ req_setattr_failure;
	पूर्ण
	स_नकल(opt->opt.__data, buf, buf_len);
	opt->opt.optlen = opt_len;
	opt->opt.cipso = माप(काष्ठा iphdr);
	kमुक्त(buf);
	buf = शून्य;

	req_inet = inet_rsk(req);
	opt = xchg((__क्रमce काष्ठा ip_options_rcu **)&req_inet->ireq_opt, opt);
	अगर (opt)
		kमुक्त_rcu(opt, rcu);

	वापस 0;

req_setattr_failure:
	kमुक्त(buf);
	kमुक्त(opt);
	वापस ret_val;
पूर्ण

/**
 * cipso_v4_delopt - Delete the CIPSO option from a set of IP options
 * @opt_ptr: IP option poपूर्णांकer
 *
 * Description:
 * Deletes the CIPSO IP option from a set of IP options and makes the necessary
 * adjusपंचांगents to the IP option काष्ठाure.  Returns zero on success, negative
 * values on failure.
 *
 */
अटल पूर्णांक cipso_v4_delopt(काष्ठा ip_options_rcu __rcu **opt_ptr)
अणु
	काष्ठा ip_options_rcu *opt = rcu_dereference_रक्षित(*opt_ptr, 1);
	पूर्णांक hdr_delta = 0;

	अगर (!opt || opt->opt.cipso == 0)
		वापस 0;
	अगर (opt->opt.srr || opt->opt.rr || opt->opt.ts || opt->opt.router_alert) अणु
		u8 cipso_len;
		u8 cipso_off;
		अचिन्हित अक्षर *cipso_ptr;
		पूर्णांक iter;
		पूर्णांक optlen_new;

		cipso_off = opt->opt.cipso - माप(काष्ठा iphdr);
		cipso_ptr = &opt->opt.__data[cipso_off];
		cipso_len = cipso_ptr[1];

		अगर (opt->opt.srr > opt->opt.cipso)
			opt->opt.srr -= cipso_len;
		अगर (opt->opt.rr > opt->opt.cipso)
			opt->opt.rr -= cipso_len;
		अगर (opt->opt.ts > opt->opt.cipso)
			opt->opt.ts -= cipso_len;
		अगर (opt->opt.router_alert > opt->opt.cipso)
			opt->opt.router_alert -= cipso_len;
		opt->opt.cipso = 0;

		स_हटाओ(cipso_ptr, cipso_ptr + cipso_len,
			opt->opt.optlen - cipso_off - cipso_len);

		/* determining the new total option length is tricky because of
		 * the padding necessary, the only thing i can think to करो at
		 * this poपूर्णांक is walk the options one-by-one, skipping the
		 * padding at the end to determine the actual option size and
		 * from there we can determine the new total option length */
		iter = 0;
		optlen_new = 0;
		जबतक (iter < opt->opt.optlen)
			अगर (opt->opt.__data[iter] != IPOPT_NOP) अणु
				iter += opt->opt.__data[iter + 1];
				optlen_new = iter;
			पूर्ण अन्यथा
				iter++;
		hdr_delta = opt->opt.optlen;
		opt->opt.optlen = (optlen_new + 3) & ~3;
		hdr_delta -= opt->opt.optlen;
	पूर्ण अन्यथा अणु
		/* only the cipso option was present on the socket so we can
		 * हटाओ the entire option काष्ठा */
		*opt_ptr = शून्य;
		hdr_delta = opt->opt.optlen;
		kमुक्त_rcu(opt, rcu);
	पूर्ण

	वापस hdr_delta;
पूर्ण

/**
 * cipso_v4_sock_delattr - Delete the CIPSO option from a socket
 * @sk: the socket
 *
 * Description:
 * Removes the CIPSO option from a socket, अगर present.
 *
 */
व्योम cipso_v4_sock_delattr(काष्ठा sock *sk)
अणु
	काष्ठा inet_sock *sk_inet;
	पूर्णांक hdr_delta;

	sk_inet = inet_sk(sk);

	hdr_delta = cipso_v4_delopt(&sk_inet->inet_opt);
	अगर (sk_inet->is_icsk && hdr_delta > 0) अणु
		काष्ठा inet_connection_sock *sk_conn = inet_csk(sk);
		sk_conn->icsk_ext_hdr_len -= hdr_delta;
		sk_conn->icsk_sync_mss(sk, sk_conn->icsk_pmtu_cookie);
	पूर्ण
पूर्ण

/**
 * cipso_v4_req_delattr - Delete the CIPSO option from a request socket
 * @req: the request socket
 *
 * Description:
 * Removes the CIPSO option from a request socket, अगर present.
 *
 */
व्योम cipso_v4_req_delattr(काष्ठा request_sock *req)
अणु
	cipso_v4_delopt(&inet_rsk(req)->ireq_opt);
पूर्ण

/**
 * cipso_v4_getattr - Helper function क्रम the cipso_v4_*_getattr functions
 * @cipso: the CIPSO v4 option
 * @secattr: the security attributes
 *
 * Description:
 * Inspect @cipso and वापस the security attributes in @secattr.  Returns zero
 * on success and negative values on failure.
 *
 */
पूर्णांक cipso_v4_getattr(स्थिर अचिन्हित अक्षर *cipso,
		     काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val = -ENOMSG;
	u32 करोi;
	काष्ठा cipso_v4_करोi *करोi_def;

	अगर (cipso_v4_cache_check(cipso, cipso[1], secattr) == 0)
		वापस 0;

	करोi = get_unaligned_be32(&cipso[2]);
	rcu_पढ़ो_lock();
	करोi_def = cipso_v4_करोi_search(करोi);
	अगर (!करोi_def)
		जाओ getattr_वापस;
	/* XXX - This code assumes only one tag per CIPSO option which isn't
	 * really a good assumption to make but since we only support the MAC
	 * tags right now it is a safe assumption. */
	चयन (cipso[6]) अणु
	हाल CIPSO_V4_TAG_RBITMAP:
		ret_val = cipso_v4_parsetag_rbm(करोi_def, &cipso[6], secattr);
		अवरोध;
	हाल CIPSO_V4_TAG_ENUM:
		ret_val = cipso_v4_parsetag_क्रमागत(करोi_def, &cipso[6], secattr);
		अवरोध;
	हाल CIPSO_V4_TAG_RANGE:
		ret_val = cipso_v4_parsetag_rng(करोi_def, &cipso[6], secattr);
		अवरोध;
	हाल CIPSO_V4_TAG_LOCAL:
		ret_val = cipso_v4_parsetag_loc(करोi_def, &cipso[6], secattr);
		अवरोध;
	पूर्ण
	अगर (ret_val == 0)
		secattr->type = NETLBL_NLTYPE_CIPSOV4;

getattr_वापस:
	rcu_पढ़ो_unlock();
	वापस ret_val;
पूर्ण

/**
 * cipso_v4_sock_getattr - Get the security attributes from a sock
 * @sk: the sock
 * @secattr: the security attributes
 *
 * Description:
 * Query @sk to see अगर there is a CIPSO option attached to the sock and अगर
 * there is वापस the CIPSO security attributes in @secattr.  This function
 * requires that @sk be locked, or निजीly held, but it करोes not करो any
 * locking itself.  Returns zero on success and negative values on failure.
 *
 */
पूर्णांक cipso_v4_sock_getattr(काष्ठा sock *sk, काष्ठा netlbl_lsm_secattr *secattr)
अणु
	काष्ठा ip_options_rcu *opt;
	पूर्णांक res = -ENOMSG;

	rcu_पढ़ो_lock();
	opt = rcu_dereference(inet_sk(sk)->inet_opt);
	अगर (opt && opt->opt.cipso)
		res = cipso_v4_getattr(opt->opt.__data +
						opt->opt.cipso -
						माप(काष्ठा iphdr),
				       secattr);
	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण

/**
 * cipso_v4_skbuff_setattr - Set the CIPSO option on a packet
 * @skb: the packet
 * @करोi_def: the DOI काष्ठाure
 * @secattr: the security attributes
 *
 * Description:
 * Set the CIPSO option on the given packet based on the security attributes.
 * Returns a poपूर्णांकer to the IP header on success and शून्य on failure.
 *
 */
पूर्णांक cipso_v4_skbuff_setattr(काष्ठा sk_buff *skb,
			    स्थिर काष्ठा cipso_v4_करोi *करोi_def,
			    स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	काष्ठा iphdr *iph;
	काष्ठा ip_options *opt = &IPCB(skb)->opt;
	अचिन्हित अक्षर buf[CIPSO_V4_OPT_LEN_MAX];
	u32 buf_len = CIPSO_V4_OPT_LEN_MAX;
	u32 opt_len;
	पूर्णांक len_delta;

	ret_val = cipso_v4_genopt(buf, buf_len, करोi_def, secattr);
	अगर (ret_val < 0)
		वापस ret_val;
	buf_len = ret_val;
	opt_len = (buf_len + 3) & ~3;

	/* we overग_लिखो any existing options to ensure that we have enough
	 * room क्रम the CIPSO option, the reason is that we _need_ to guarantee
	 * that the security label is applied to the packet - we करो the same
	 * thing when using the socket options and it hasn't caused a problem,
	 * अगर we need to we can always revisit this choice later */

	len_delta = opt_len - opt->optlen;
	/* अगर we करोn't ensure enough headroom we could panic on the skb_push()
	 * call below so make sure we have enough, we are also "mangling" the
	 * packet so we should probably करो a copy-on-ग_लिखो call anyway */
	ret_val = skb_cow(skb, skb_headroom(skb) + len_delta);
	अगर (ret_val < 0)
		वापस ret_val;

	अगर (len_delta > 0) अणु
		/* we assume that the header + opt->optlen have alपढ़ोy been
		 * "pushed" in ip_options_build() or similar */
		iph = ip_hdr(skb);
		skb_push(skb, len_delta);
		स_हटाओ((अक्षर *)iph - len_delta, iph, iph->ihl << 2);
		skb_reset_network_header(skb);
		iph = ip_hdr(skb);
	पूर्ण अन्यथा अगर (len_delta < 0) अणु
		iph = ip_hdr(skb);
		स_रखो(iph + 1, IPOPT_NOP, opt->optlen);
	पूर्ण अन्यथा
		iph = ip_hdr(skb);

	अगर (opt->optlen > 0)
		स_रखो(opt, 0, माप(*opt));
	opt->optlen = opt_len;
	opt->cipso = माप(काष्ठा iphdr);
	opt->is_changed = 1;

	/* we have to करो the following because we are being called from a
	 * netfilter hook which means the packet alपढ़ोy has had the header
	 * fields populated and the checksum calculated - yes this means we
	 * are करोing more work than needed but we करो it to keep the core
	 * stack clean and tidy */
	स_नकल(iph + 1, buf, buf_len);
	अगर (opt_len > buf_len)
		स_रखो((अक्षर *)(iph + 1) + buf_len, 0, opt_len - buf_len);
	अगर (len_delta != 0) अणु
		iph->ihl = 5 + (opt_len >> 2);
		iph->tot_len = htons(skb->len);
	पूर्ण
	ip_send_check(iph);

	वापस 0;
पूर्ण

/**
 * cipso_v4_skbuff_delattr - Delete any CIPSO options from a packet
 * @skb: the packet
 *
 * Description:
 * Removes any and all CIPSO options from the given packet.  Returns zero on
 * success, negative values on failure.
 *
 */
पूर्णांक cipso_v4_skbuff_delattr(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret_val;
	काष्ठा iphdr *iph;
	काष्ठा ip_options *opt = &IPCB(skb)->opt;
	अचिन्हित अक्षर *cipso_ptr;

	अगर (opt->cipso == 0)
		वापस 0;

	/* since we are changing the packet we should make a copy */
	ret_val = skb_cow(skb, skb_headroom(skb));
	अगर (ret_val < 0)
		वापस ret_val;

	/* the easiest thing to करो is just replace the cipso option with noop
	 * options since we करोn't change the size of the packet, although we
	 * still need to recalculate the checksum */

	iph = ip_hdr(skb);
	cipso_ptr = (अचिन्हित अक्षर *)iph + opt->cipso;
	स_रखो(cipso_ptr, IPOPT_NOOP, cipso_ptr[1]);
	opt->cipso = 0;
	opt->is_changed = 1;

	ip_send_check(iph);

	वापस 0;
पूर्ण

/*
 * Setup Functions
 */

/**
 * cipso_v4_init - Initialize the CIPSO module
 *
 * Description:
 * Initialize the CIPSO module and prepare it क्रम use.  Returns zero on success
 * and negative values on failure.
 *
 */
अटल पूर्णांक __init cipso_v4_init(व्योम)
अणु
	पूर्णांक ret_val;

	ret_val = cipso_v4_cache_init();
	अगर (ret_val != 0)
		panic("Failed to initialize the CIPSO/IPv4 cache (%d)\n",
		      ret_val);

	वापस 0;
पूर्ण

subsys_initcall(cipso_v4_init);
