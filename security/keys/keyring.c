<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Keyring handling
 *
 * Copyright (C) 2004-2005, 2008, 2013 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/security.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/err.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/nsproxy.h>
#समावेश <keys/keyring-type.h>
#समावेश <keys/user-type.h>
#समावेश <linux/assoc_array_priv.h>
#समावेश <linux/uaccess.h>
#समावेश <net/net_namespace.h>
#समावेश "internal.h"

/*
 * When plumbing the depths of the key tree, this sets a hard limit
 * set on how deep we're willing to go.
 */
#घोषणा KEYRING_SEARCH_MAX_DEPTH 6

/*
 * We mark poपूर्णांकers we pass to the associative array with bit 1 set अगर
 * they're keyrings and clear otherwise.
 */
#घोषणा KEYRING_PTR_SUBTYPE	0x2UL

अटल अंतरभूत bool keyring_ptr_is_keyring(स्थिर काष्ठा assoc_array_ptr *x)
अणु
	वापस (अचिन्हित दीर्घ)x & KEYRING_PTR_SUBTYPE;
पूर्ण
अटल अंतरभूत काष्ठा key *keyring_ptr_to_key(स्थिर काष्ठा assoc_array_ptr *x)
अणु
	व्योम *object = assoc_array_ptr_to_leaf(x);
	वापस (काष्ठा key *)((अचिन्हित दीर्घ)object & ~KEYRING_PTR_SUBTYPE);
पूर्ण
अटल अंतरभूत व्योम *keyring_key_to_ptr(काष्ठा key *key)
अणु
	अगर (key->type == &key_type_keyring)
		वापस (व्योम *)((अचिन्हित दीर्घ)key | KEYRING_PTR_SUBTYPE);
	वापस key;
पूर्ण

अटल DEFINE_RWLOCK(keyring_name_lock);

/*
 * Clean up the bits of user_namespace that beदीर्घ to us.
 */
व्योम key_मुक्त_user_ns(काष्ठा user_namespace *ns)
अणु
	ग_लिखो_lock(&keyring_name_lock);
	list_del_init(&ns->keyring_name_list);
	ग_लिखो_unlock(&keyring_name_lock);

	key_put(ns->user_keyring_रेजिस्टर);
#अगर_घोषित CONFIG_PERSISTENT_KEYRINGS
	key_put(ns->persistent_keyring_रेजिस्टर);
#पूर्ण_अगर
पूर्ण

/*
 * The keyring key type definition.  Keyrings are simply keys of this type and
 * can be treated as ordinary keys in addition to having their own special
 * operations.
 */
अटल पूर्णांक keyring_preparse(काष्ठा key_preparsed_payload *prep);
अटल व्योम keyring_मुक्त_preparse(काष्ठा key_preparsed_payload *prep);
अटल पूर्णांक keyring_instantiate(काष्ठा key *keyring,
			       काष्ठा key_preparsed_payload *prep);
अटल व्योम keyring_revoke(काष्ठा key *keyring);
अटल व्योम keyring_destroy(काष्ठा key *keyring);
अटल व्योम keyring_describe(स्थिर काष्ठा key *keyring, काष्ठा seq_file *m);
अटल दीर्घ keyring_पढ़ो(स्थिर काष्ठा key *keyring,
			 अक्षर __user *buffer, माप_प्रकार buflen);

काष्ठा key_type key_type_keyring = अणु
	.name		= "keyring",
	.def_datalen	= 0,
	.preparse	= keyring_preparse,
	.मुक्त_preparse	= keyring_मुक्त_preparse,
	.instantiate	= keyring_instantiate,
	.revoke		= keyring_revoke,
	.destroy	= keyring_destroy,
	.describe	= keyring_describe,
	.पढ़ो		= keyring_पढ़ो,
पूर्ण;
EXPORT_SYMBOL(key_type_keyring);

/*
 * Semaphore to serialise link/link calls to prevent two link calls in parallel
 * पूर्णांकroducing a cycle.
 */
अटल DEFINE_MUTEX(keyring_serialise_link_lock);

/*
 * Publish the name of a keyring so that it can be found by name (अगर it has
 * one and it करोesn't begin with a करोt).
 */
अटल व्योम keyring_publish_name(काष्ठा key *keyring)
अणु
	काष्ठा user_namespace *ns = current_user_ns();

	अगर (keyring->description &&
	    keyring->description[0] &&
	    keyring->description[0] != '.') अणु
		ग_लिखो_lock(&keyring_name_lock);
		list_add_tail(&keyring->name_link, &ns->keyring_name_list);
		ग_लिखो_unlock(&keyring_name_lock);
	पूर्ण
पूर्ण

/*
 * Preparse a keyring payload
 */
अटल पूर्णांक keyring_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	वापस prep->datalen != 0 ? -EINVAL : 0;
पूर्ण

/*
 * Free a preparse of a user defined key payload
 */
अटल व्योम keyring_मुक्त_preparse(काष्ठा key_preparsed_payload *prep)
अणु
पूर्ण

/*
 * Initialise a keyring.
 *
 * Returns 0 on success, -EINVAL अगर given any data.
 */
अटल पूर्णांक keyring_instantiate(काष्ठा key *keyring,
			       काष्ठा key_preparsed_payload *prep)
अणु
	assoc_array_init(&keyring->keys);
	/* make the keyring available by name अगर it has one */
	keyring_publish_name(keyring);
	वापस 0;
पूर्ण

/*
 * Multiply 64-bits by 32-bits to 96-bits and fold back to 64-bit.  Ideally we'd
 * fold the carry back too, but that requires अंतरभूत यंत्र.
 */
अटल u64 mult_64x32_and_fold(u64 x, u32 y)
अणु
	u64 hi = (u64)(u32)(x >> 32) * y;
	u64 lo = (u64)(u32)(x) * y;
	वापस lo + ((u64)(u32)hi << 32) + (u32)(hi >> 32);
पूर्ण

/*
 * Hash a key type and description.
 */
अटल व्योम hash_key_type_and_desc(काष्ठा keyring_index_key *index_key)
अणु
	स्थिर अचिन्हित level_shअगरt = ASSOC_ARRAY_LEVEL_STEP;
	स्थिर अचिन्हित दीर्घ fan_mask = ASSOC_ARRAY_FAN_MASK;
	स्थिर अक्षर *description = index_key->description;
	अचिन्हित दीर्घ hash, type;
	u32 piece;
	u64 acc;
	पूर्णांक n, desc_len = index_key->desc_len;

	type = (अचिन्हित दीर्घ)index_key->type;
	acc = mult_64x32_and_fold(type, desc_len + 13);
	acc = mult_64x32_and_fold(acc, 9207);
	piece = (अचिन्हित दीर्घ)index_key->करोमुख्य_tag;
	acc = mult_64x32_and_fold(acc, piece);
	acc = mult_64x32_and_fold(acc, 9207);

	क्रम (;;) अणु
		n = desc_len;
		अगर (n <= 0)
			अवरोध;
		अगर (n > 4)
			n = 4;
		piece = 0;
		स_नकल(&piece, description, n);
		description += n;
		desc_len -= n;
		acc = mult_64x32_and_fold(acc, piece);
		acc = mult_64x32_and_fold(acc, 9207);
	पूर्ण

	/* Fold the hash करोwn to 32 bits अगर need be. */
	hash = acc;
	अगर (ASSOC_ARRAY_KEY_CHUNK_SIZE == 32)
		hash ^= acc >> 32;

	/* Squidge all the keyrings पूर्णांकo a separate part of the tree to
	 * ordinary keys by making sure the lowest level segment in the hash is
	 * zero क्रम keyrings and non-zero otherwise.
	 */
	अगर (index_key->type != &key_type_keyring && (hash & fan_mask) == 0)
		hash |= (hash >> (ASSOC_ARRAY_KEY_CHUNK_SIZE - level_shअगरt)) | 1;
	अन्यथा अगर (index_key->type == &key_type_keyring && (hash & fan_mask) != 0)
		hash = (hash + (hash << level_shअगरt)) & ~fan_mask;
	index_key->hash = hash;
पूर्ण

/*
 * Finalise an index key to include a part of the description actually in the
 * index key, to set the करोमुख्य tag and to calculate the hash.
 */
व्योम key_set_index_key(काष्ठा keyring_index_key *index_key)
अणु
	अटल काष्ठा key_tag शेष_करोमुख्य_tag = अणु .usage = REFCOUNT_INIT(1), पूर्ण;
	माप_प्रकार n = min_t(माप_प्रकार, index_key->desc_len, माप(index_key->desc));

	स_नकल(index_key->desc, index_key->description, n);

	अगर (!index_key->करोमुख्य_tag) अणु
		अगर (index_key->type->flags & KEY_TYPE_NET_DOMAIN)
			index_key->करोमुख्य_tag = current->nsproxy->net_ns->key_करोमुख्य;
		अन्यथा
			index_key->करोमुख्य_tag = &शेष_करोमुख्य_tag;
	पूर्ण

	hash_key_type_and_desc(index_key);
पूर्ण

/**
 * key_put_tag - Release a ref on a tag.
 * @tag: The tag to release.
 *
 * This releases a reference the given tag and वापसs true अगर that ref was the
 * last one.
 */
bool key_put_tag(काष्ठा key_tag *tag)
अणु
	अगर (refcount_dec_and_test(&tag->usage)) अणु
		kमुक्त_rcu(tag, rcu);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * key_हटाओ_करोमुख्य - Kill off a key करोमुख्य and gc its keys
 * @करोमुख्य_tag: The करोमुख्य tag to release.
 *
 * This marks a करोमुख्य tag as being dead and releases a ref on it.  If that
 * wasn't the last reference, the garbage collector is poked to try and delete
 * all keys that were in the करोमुख्य.
 */
व्योम key_हटाओ_करोमुख्य(काष्ठा key_tag *करोमुख्य_tag)
अणु
	करोमुख्य_tag->हटाओd = true;
	अगर (!key_put_tag(करोमुख्य_tag))
		key_schedule_gc_links();
पूर्ण

/*
 * Build the next index key chunk.
 *
 * We वापस it one word-sized chunk at a समय.
 */
अटल अचिन्हित दीर्घ keyring_get_key_chunk(स्थिर व्योम *data, पूर्णांक level)
अणु
	स्थिर काष्ठा keyring_index_key *index_key = data;
	अचिन्हित दीर्घ chunk = 0;
	स्थिर u8 *d;
	पूर्णांक desc_len = index_key->desc_len, n = माप(chunk);

	level /= ASSOC_ARRAY_KEY_CHUNK_SIZE;
	चयन (level) अणु
	हाल 0:
		वापस index_key->hash;
	हाल 1:
		वापस index_key->x;
	हाल 2:
		वापस (अचिन्हित दीर्घ)index_key->type;
	हाल 3:
		वापस (अचिन्हित दीर्घ)index_key->करोमुख्य_tag;
	शेष:
		level -= 4;
		अगर (desc_len <= माप(index_key->desc))
			वापस 0;

		d = index_key->description + माप(index_key->desc);
		d += level * माप(दीर्घ);
		desc_len -= माप(index_key->desc);
		अगर (desc_len > n)
			desc_len = n;
		करो अणु
			chunk <<= 8;
			chunk |= *d++;
		पूर्ण जबतक (--desc_len > 0);
		वापस chunk;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ keyring_get_object_key_chunk(स्थिर व्योम *object, पूर्णांक level)
अणु
	स्थिर काष्ठा key *key = keyring_ptr_to_key(object);
	वापस keyring_get_key_chunk(&key->index_key, level);
पूर्ण

अटल bool keyring_compare_object(स्थिर व्योम *object, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा keyring_index_key *index_key = data;
	स्थिर काष्ठा key *key = keyring_ptr_to_key(object);

	वापस key->index_key.type == index_key->type &&
		key->index_key.करोमुख्य_tag == index_key->करोमुख्य_tag &&
		key->index_key.desc_len == index_key->desc_len &&
		स_भेद(key->index_key.description, index_key->description,
		       index_key->desc_len) == 0;
पूर्ण

/*
 * Compare the index keys of a pair of objects and determine the bit position
 * at which they dअगरfer - अगर they dअगरfer.
 */
अटल पूर्णांक keyring_dअगरf_objects(स्थिर व्योम *object, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा key *key_a = keyring_ptr_to_key(object);
	स्थिर काष्ठा keyring_index_key *a = &key_a->index_key;
	स्थिर काष्ठा keyring_index_key *b = data;
	अचिन्हित दीर्घ seg_a, seg_b;
	पूर्णांक level, i;

	level = 0;
	seg_a = a->hash;
	seg_b = b->hash;
	अगर ((seg_a ^ seg_b) != 0)
		जाओ dअगरfer;
	level += ASSOC_ARRAY_KEY_CHUNK_SIZE / 8;

	/* The number of bits contributed by the hash is controlled by a
	 * स्थिरant in the assoc_array headers.  Everything अन्यथा thereafter we
	 * can deal with as being machine word-size dependent.
	 */
	seg_a = a->x;
	seg_b = b->x;
	अगर ((seg_a ^ seg_b) != 0)
		जाओ dअगरfer;
	level += माप(अचिन्हित दीर्घ);

	/* The next bit may not work on big endian */
	seg_a = (अचिन्हित दीर्घ)a->type;
	seg_b = (अचिन्हित दीर्घ)b->type;
	अगर ((seg_a ^ seg_b) != 0)
		जाओ dअगरfer;
	level += माप(अचिन्हित दीर्घ);

	seg_a = (अचिन्हित दीर्घ)a->करोमुख्य_tag;
	seg_b = (अचिन्हित दीर्घ)b->करोमुख्य_tag;
	अगर ((seg_a ^ seg_b) != 0)
		जाओ dअगरfer;
	level += माप(अचिन्हित दीर्घ);

	i = माप(a->desc);
	अगर (a->desc_len <= i)
		जाओ same;

	क्रम (; i < a->desc_len; i++) अणु
		seg_a = *(अचिन्हित अक्षर *)(a->description + i);
		seg_b = *(अचिन्हित अक्षर *)(b->description + i);
		अगर ((seg_a ^ seg_b) != 0)
			जाओ dअगरfer_plus_i;
	पूर्ण

same:
	वापस -1;

dअगरfer_plus_i:
	level += i;
dअगरfer:
	i = level * 8 + __ffs(seg_a ^ seg_b);
	वापस i;
पूर्ण

/*
 * Free an object after stripping the keyring flag off of the poपूर्णांकer.
 */
अटल व्योम keyring_मुक्त_object(व्योम *object)
अणु
	key_put(keyring_ptr_to_key(object));
पूर्ण

/*
 * Operations क्रम keyring management by the index-tree routines.
 */
अटल स्थिर काष्ठा assoc_array_ops keyring_assoc_array_ops = अणु
	.get_key_chunk		= keyring_get_key_chunk,
	.get_object_key_chunk	= keyring_get_object_key_chunk,
	.compare_object		= keyring_compare_object,
	.dअगरf_objects		= keyring_dअगरf_objects,
	.मुक्त_object		= keyring_मुक्त_object,
पूर्ण;

/*
 * Clean up a keyring when it is destroyed.  Unpublish its name अगर it had one
 * and dispose of its data.
 *
 * The garbage collector detects the final key_put(), हटाओs the keyring from
 * the serial number tree and then करोes RCU synchronisation beक्रमe coming here,
 * so we shouldn't need to worry about code poking around here with the RCU
 * पढ़ोlock held by this समय.
 */
अटल व्योम keyring_destroy(काष्ठा key *keyring)
अणु
	अगर (keyring->description) अणु
		ग_लिखो_lock(&keyring_name_lock);

		अगर (keyring->name_link.next != शून्य &&
		    !list_empty(&keyring->name_link))
			list_del(&keyring->name_link);

		ग_लिखो_unlock(&keyring_name_lock);
	पूर्ण

	अगर (keyring->restrict_link) अणु
		काष्ठा key_restriction *keyres = keyring->restrict_link;

		key_put(keyres->key);
		kमुक्त(keyres);
	पूर्ण

	assoc_array_destroy(&keyring->keys, &keyring_assoc_array_ops);
पूर्ण

/*
 * Describe a keyring क्रम /proc.
 */
अटल व्योम keyring_describe(स्थिर काष्ठा key *keyring, काष्ठा seq_file *m)
अणु
	अगर (keyring->description)
		seq_माला_दो(m, keyring->description);
	अन्यथा
		seq_माला_दो(m, "[anon]");

	अगर (key_is_positive(keyring)) अणु
		अगर (keyring->keys.nr_leaves_on_tree != 0)
			seq_म_लिखो(m, ": %lu", keyring->keys.nr_leaves_on_tree);
		अन्यथा
			seq_माला_दो(m, ": empty");
	पूर्ण
पूर्ण

काष्ठा keyring_पढ़ो_iterator_context अणु
	माप_प्रकार			buflen;
	माप_प्रकार			count;
	key_serial_t		*buffer;
पूर्ण;

अटल पूर्णांक keyring_पढ़ो_iterator(स्थिर व्योम *object, व्योम *data)
अणु
	काष्ठा keyring_पढ़ो_iterator_context *ctx = data;
	स्थिर काष्ठा key *key = keyring_ptr_to_key(object);

	kenter("{%s,%d},,{%zu/%zu}",
	       key->type->name, key->serial, ctx->count, ctx->buflen);

	अगर (ctx->count >= ctx->buflen)
		वापस 1;

	*ctx->buffer++ = key->serial;
	ctx->count += माप(key->serial);
	वापस 0;
पूर्ण

/*
 * Read a list of key IDs from the keyring's contents in binary क्रमm
 *
 * The keyring's semaphore is पढ़ो-locked by the caller.  This prevents someone
 * from modअगरying it under us - which could cause us to पढ़ो key IDs multiple
 * बार.
 */
अटल दीर्घ keyring_पढ़ो(स्थिर काष्ठा key *keyring,
			 अक्षर *buffer, माप_प्रकार buflen)
अणु
	काष्ठा keyring_पढ़ो_iterator_context ctx;
	दीर्घ ret;

	kenter("{%d},,%zu", key_serial(keyring), buflen);

	अगर (buflen & (माप(key_serial_t) - 1))
		वापस -EINVAL;

	/* Copy as many key IDs as fit पूर्णांकo the buffer */
	अगर (buffer && buflen) अणु
		ctx.buffer = (key_serial_t *)buffer;
		ctx.buflen = buflen;
		ctx.count = 0;
		ret = assoc_array_iterate(&keyring->keys,
					  keyring_पढ़ो_iterator, &ctx);
		अगर (ret < 0) अणु
			kleave(" = %ld [iterate]", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Return the size of the buffer needed */
	ret = keyring->keys.nr_leaves_on_tree * माप(key_serial_t);
	अगर (ret <= buflen)
		kleave("= %ld [ok]", ret);
	अन्यथा
		kleave("= %ld [buffer too small]", ret);
	वापस ret;
पूर्ण

/*
 * Allocate a keyring and link पूर्णांकo the destination keyring.
 */
काष्ठा key *keyring_alloc(स्थिर अक्षर *description, kuid_t uid, kgid_t gid,
			  स्थिर काष्ठा cred *cred, key_perm_t perm,
			  अचिन्हित दीर्घ flags,
			  काष्ठा key_restriction *restrict_link,
			  काष्ठा key *dest)
अणु
	काष्ठा key *keyring;
	पूर्णांक ret;

	keyring = key_alloc(&key_type_keyring, description,
			    uid, gid, cred, perm, flags, restrict_link);
	अगर (!IS_ERR(keyring)) अणु
		ret = key_instantiate_and_link(keyring, शून्य, 0, dest, शून्य);
		अगर (ret < 0) अणु
			key_put(keyring);
			keyring = ERR_PTR(ret);
		पूर्ण
	पूर्ण

	वापस keyring;
पूर्ण
EXPORT_SYMBOL(keyring_alloc);

/**
 * restrict_link_reject - Give -EPERM to restrict link
 * @keyring: The keyring being added to.
 * @type: The type of key being added.
 * @payload: The payload of the key पूर्णांकended to be added.
 * @restriction_key: Keys providing additional data क्रम evaluating restriction.
 *
 * Reject the addition of any links to a keyring.  It can be overridden by
 * passing KEY_ALLOC_BYPASS_RESTRICTION to key_instantiate_and_link() when
 * adding a key to a keyring.
 *
 * This is meant to be stored in a key_restriction काष्ठाure which is passed
 * in the restrict_link parameter to keyring_alloc().
 */
पूर्णांक restrict_link_reject(काष्ठा key *keyring,
			 स्थिर काष्ठा key_type *type,
			 स्थिर जोड़ key_payload *payload,
			 काष्ठा key *restriction_key)
अणु
	वापस -EPERM;
पूर्ण

/*
 * By शेष, we keys found by getting an exact match on their descriptions.
 */
bool key_शेष_cmp(स्थिर काष्ठा key *key,
		     स्थिर काष्ठा key_match_data *match_data)
अणु
	वापस म_भेद(key->description, match_data->raw_data) == 0;
पूर्ण

/*
 * Iteration function to consider each key found.
 */
अटल पूर्णांक keyring_search_iterator(स्थिर व्योम *object, व्योम *iterator_data)
अणु
	काष्ठा keyring_search_context *ctx = iterator_data;
	स्थिर काष्ठा key *key = keyring_ptr_to_key(object);
	अचिन्हित दीर्घ kflags = READ_ONCE(key->flags);
	लघु state = READ_ONCE(key->state);

	kenter("{%d}", key->serial);

	/* ignore keys not of this type */
	अगर (key->type != ctx->index_key.type) अणु
		kleave(" = 0 [!type]");
		वापस 0;
	पूर्ण

	/* skip invalidated, revoked and expired keys */
	अगर (ctx->flags & KEYRING_SEARCH_DO_STATE_CHECK) अणु
		समय64_t expiry = READ_ONCE(key->expiry);

		अगर (kflags & ((1 << KEY_FLAG_INVALIDATED) |
			      (1 << KEY_FLAG_REVOKED))) अणु
			ctx->result = ERR_PTR(-EKEYREVOKED);
			kleave(" = %d [invrev]", ctx->skipped_ret);
			जाओ skipped;
		पूर्ण

		अगर (expiry && ctx->now >= expiry) अणु
			अगर (!(ctx->flags & KEYRING_SEARCH_SKIP_EXPIRED))
				ctx->result = ERR_PTR(-EKEYEXPIRED);
			kleave(" = %d [expire]", ctx->skipped_ret);
			जाओ skipped;
		पूर्ण
	पूर्ण

	/* keys that करोn't match */
	अगर (!ctx->match_data.cmp(key, &ctx->match_data)) अणु
		kleave(" = 0 [!match]");
		वापस 0;
	पूर्ण

	/* key must have search permissions */
	अगर (!(ctx->flags & KEYRING_SEARCH_NO_CHECK_PERM) &&
	    key_task_permission(make_key_ref(key, ctx->possessed),
				ctx->cred, KEY_NEED_SEARCH) < 0) अणु
		ctx->result = ERR_PTR(-EACCES);
		kleave(" = %d [!perm]", ctx->skipped_ret);
		जाओ skipped;
	पूर्ण

	अगर (ctx->flags & KEYRING_SEARCH_DO_STATE_CHECK) अणु
		/* we set a dअगरferent error code अगर we pass a negative key */
		अगर (state < 0) अणु
			ctx->result = ERR_PTR(state);
			kleave(" = %d [neg]", ctx->skipped_ret);
			जाओ skipped;
		पूर्ण
	पूर्ण

	/* Found */
	ctx->result = make_key_ref(key, ctx->possessed);
	kleave(" = 1 [found]");
	वापस 1;

skipped:
	वापस ctx->skipped_ret;
पूर्ण

/*
 * Search inside a keyring क्रम a key.  We can search by walking to it
 * directly based on its index-key or we can iterate over the entire
 * tree looking क्रम it, based on the match function.
 */
अटल पूर्णांक search_keyring(काष्ठा key *keyring, काष्ठा keyring_search_context *ctx)
अणु
	अगर (ctx->match_data.lookup_type == KEYRING_SEARCH_LOOKUP_सूचीECT) अणु
		स्थिर व्योम *object;

		object = assoc_array_find(&keyring->keys,
					  &keyring_assoc_array_ops,
					  &ctx->index_key);
		वापस object ? ctx->iterator(object, ctx) : 0;
	पूर्ण
	वापस assoc_array_iterate(&keyring->keys, ctx->iterator, ctx);
पूर्ण

/*
 * Search a tree of keyrings that poपूर्णांक to other keyrings up to the maximum
 * depth.
 */
अटल bool search_nested_keyrings(काष्ठा key *keyring,
				   काष्ठा keyring_search_context *ctx)
अणु
	काष्ठा अणु
		काष्ठा key *keyring;
		काष्ठा assoc_array_node *node;
		पूर्णांक slot;
	पूर्ण stack[KEYRING_SEARCH_MAX_DEPTH];

	काष्ठा assoc_array_लघुcut *लघुcut;
	काष्ठा assoc_array_node *node;
	काष्ठा assoc_array_ptr *ptr;
	काष्ठा key *key;
	पूर्णांक sp = 0, slot;

	kenter("{%d},{%s,%s}",
	       keyring->serial,
	       ctx->index_key.type->name,
	       ctx->index_key.description);

#घोषणा STATE_CHECKS (KEYRING_SEARCH_NO_STATE_CHECK | KEYRING_SEARCH_DO_STATE_CHECK)
	BUG_ON((ctx->flags & STATE_CHECKS) == 0 ||
	       (ctx->flags & STATE_CHECKS) == STATE_CHECKS);

	अगर (ctx->index_key.description)
		key_set_index_key(&ctx->index_key);

	/* Check to see अगर this top-level keyring is what we are looking क्रम
	 * and whether it is valid or not.
	 */
	अगर (ctx->match_data.lookup_type == KEYRING_SEARCH_LOOKUP_ITERATE ||
	    keyring_compare_object(keyring, &ctx->index_key)) अणु
		ctx->skipped_ret = 2;
		चयन (ctx->iterator(keyring_key_to_ptr(keyring), ctx)) अणु
		हाल 1:
			जाओ found;
		हाल 2:
			वापस false;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	ctx->skipped_ret = 0;

	/* Start processing a new keyring */
descend_to_keyring:
	kdebug("descend to %d", keyring->serial);
	अगर (keyring->flags & ((1 << KEY_FLAG_INVALIDATED) |
			      (1 << KEY_FLAG_REVOKED)))
		जाओ not_this_keyring;

	/* Search through the keys in this keyring beक्रमe its searching its
	 * subtrees.
	 */
	अगर (search_keyring(keyring, ctx))
		जाओ found;

	/* Then manually iterate through the keyrings nested in this one.
	 *
	 * Start from the root node of the index tree.  Because of the way the
	 * hash function has been set up, keyrings cluster on the lefपंचांगost
	 * branch of the root node (root slot 0) or in the root node itself.
	 * Non-keyrings aव्योम the lefपंचांगost branch of the root entirely (root
	 * slots 1-15).
	 */
	अगर (!(ctx->flags & KEYRING_SEARCH_RECURSE))
		जाओ not_this_keyring;

	ptr = READ_ONCE(keyring->keys.root);
	अगर (!ptr)
		जाओ not_this_keyring;

	अगर (assoc_array_ptr_is_लघुcut(ptr)) अणु
		/* If the root is a लघुcut, either the keyring only contains
		 * keyring poपूर्णांकers (everything clusters behind root slot 0) or
		 * करोesn't contain any keyring poपूर्णांकers.
		 */
		लघुcut = assoc_array_ptr_to_लघुcut(ptr);
		अगर ((लघुcut->index_key[0] & ASSOC_ARRAY_FAN_MASK) != 0)
			जाओ not_this_keyring;

		ptr = READ_ONCE(लघुcut->next_node);
		node = assoc_array_ptr_to_node(ptr);
		जाओ begin_node;
	पूर्ण

	node = assoc_array_ptr_to_node(ptr);
	ptr = node->slots[0];
	अगर (!assoc_array_ptr_is_meta(ptr))
		जाओ begin_node;

descend_to_node:
	/* Descend to a more distal node in this keyring's content tree and go
	 * through that.
	 */
	kdebug("descend");
	अगर (assoc_array_ptr_is_लघुcut(ptr)) अणु
		लघुcut = assoc_array_ptr_to_लघुcut(ptr);
		ptr = READ_ONCE(लघुcut->next_node);
		BUG_ON(!assoc_array_ptr_is_node(ptr));
	पूर्ण
	node = assoc_array_ptr_to_node(ptr);

begin_node:
	kdebug("begin_node");
	slot = 0;
ascend_to_node:
	/* Go through the slots in a node */
	क्रम (; slot < ASSOC_ARRAY_FAN_OUT; slot++) अणु
		ptr = READ_ONCE(node->slots[slot]);

		अगर (assoc_array_ptr_is_meta(ptr) && node->back_poपूर्णांकer)
			जाओ descend_to_node;

		अगर (!keyring_ptr_is_keyring(ptr))
			जारी;

		key = keyring_ptr_to_key(ptr);

		अगर (sp >= KEYRING_SEARCH_MAX_DEPTH) अणु
			अगर (ctx->flags & KEYRING_SEARCH_DETECT_TOO_DEEP) अणु
				ctx->result = ERR_PTR(-ELOOP);
				वापस false;
			पूर्ण
			जाओ not_this_keyring;
		पूर्ण

		/* Search a nested keyring */
		अगर (!(ctx->flags & KEYRING_SEARCH_NO_CHECK_PERM) &&
		    key_task_permission(make_key_ref(key, ctx->possessed),
					ctx->cred, KEY_NEED_SEARCH) < 0)
			जारी;

		/* stack the current position */
		stack[sp].keyring = keyring;
		stack[sp].node = node;
		stack[sp].slot = slot;
		sp++;

		/* begin again with the new keyring */
		keyring = key;
		जाओ descend_to_keyring;
	पूर्ण

	/* We've dealt with all the slots in the current node, so now we need
	 * to ascend to the parent and जारी processing there.
	 */
	ptr = READ_ONCE(node->back_poपूर्णांकer);
	slot = node->parent_slot;

	अगर (ptr && assoc_array_ptr_is_लघुcut(ptr)) अणु
		लघुcut = assoc_array_ptr_to_लघुcut(ptr);
		ptr = READ_ONCE(लघुcut->back_poपूर्णांकer);
		slot = लघुcut->parent_slot;
	पूर्ण
	अगर (!ptr)
		जाओ not_this_keyring;
	node = assoc_array_ptr_to_node(ptr);
	slot++;

	/* If we've ascended to the root (zero backpoपूर्णांकer), we must have just
	 * finished processing the lefपंचांगost branch rather than the root slots -
	 * so there can't be any more keyrings क्रम us to find.
	 */
	अगर (node->back_poपूर्णांकer) अणु
		kdebug("ascend %d", slot);
		जाओ ascend_to_node;
	पूर्ण

	/* The keyring we're looking at was disqualified or didn't contain a
	 * matching key.
	 */
not_this_keyring:
	kdebug("not_this_keyring %d", sp);
	अगर (sp <= 0) अणु
		kleave(" = false");
		वापस false;
	पूर्ण

	/* Resume the processing of a keyring higher up in the tree */
	sp--;
	keyring = stack[sp].keyring;
	node = stack[sp].node;
	slot = stack[sp].slot + 1;
	kdebug("ascend to %d [%d]", keyring->serial, slot);
	जाओ ascend_to_node;

	/* We found a viable match */
found:
	key = key_ref_to_ptr(ctx->result);
	key_check(key);
	अगर (!(ctx->flags & KEYRING_SEARCH_NO_UPDATE_TIME)) अणु
		key->last_used_at = ctx->now;
		keyring->last_used_at = ctx->now;
		जबतक (sp > 0)
			stack[--sp].keyring->last_used_at = ctx->now;
	पूर्ण
	kleave(" = true");
	वापस true;
पूर्ण

/**
 * keyring_search_rcu - Search a keyring tree क्रम a matching key under RCU
 * @keyring_ref: A poपूर्णांकer to the keyring with possession indicator.
 * @ctx: The keyring search context.
 *
 * Search the supplied keyring tree क्रम a key that matches the criteria given.
 * The root keyring and any linked keyrings must grant Search permission to the
 * caller to be searchable and keys can only be found अगर they too grant Search
 * to the caller. The possession flag on the root keyring poपूर्णांकer controls use
 * of the possessor bits in permissions checking of the entire tree.  In
 * addition, the LSM माला_लो to क्रमbid keyring searches and key matches.
 *
 * The search is perक्रमmed as a bपढ़ोth-then-depth search up to the prescribed
 * limit (KEYRING_SEARCH_MAX_DEPTH).  The caller must hold the RCU पढ़ो lock to
 * prevent keyrings from being destroyed or rearranged whilst they are being
 * searched.
 *
 * Keys are matched to the type provided and are then filtered by the match
 * function, which is given the description to use in any way it sees fit.  The
 * match function may use any attributes of a key that it wishes to
 * determine the match.  Normally the match function from the key type would be
 * used.
 *
 * RCU can be used to prevent the keyring key lists from disappearing without
 * the need to take lots of locks.
 *
 * Returns a poपूर्णांकer to the found key and increments the key usage count अगर
 * successful; -EAGAIN अगर no matching keys were found, or अगर expired or revoked
 * keys were found; -ENOKEY अगर only negative keys were found; -ENOTसूची अगर the
 * specअगरied keyring wasn't a keyring.
 *
 * In the हाल of a successful वापस, the possession attribute from
 * @keyring_ref is propagated to the वापसed key reference.
 */
key_ref_t keyring_search_rcu(key_ref_t keyring_ref,
			     काष्ठा keyring_search_context *ctx)
अणु
	काष्ठा key *keyring;
	दीर्घ err;

	ctx->iterator = keyring_search_iterator;
	ctx->possessed = is_key_possessed(keyring_ref);
	ctx->result = ERR_PTR(-EAGAIN);

	keyring = key_ref_to_ptr(keyring_ref);
	key_check(keyring);

	अगर (keyring->type != &key_type_keyring)
		वापस ERR_PTR(-ENOTसूची);

	अगर (!(ctx->flags & KEYRING_SEARCH_NO_CHECK_PERM)) अणु
		err = key_task_permission(keyring_ref, ctx->cred, KEY_NEED_SEARCH);
		अगर (err < 0)
			वापस ERR_PTR(err);
	पूर्ण

	ctx->now = kसमय_get_real_seconds();
	अगर (search_nested_keyrings(keyring, ctx))
		__key_get(key_ref_to_ptr(ctx->result));
	वापस ctx->result;
पूर्ण

/**
 * keyring_search - Search the supplied keyring tree क्रम a matching key
 * @keyring: The root of the keyring tree to be searched.
 * @type: The type of keyring we want to find.
 * @description: The name of the keyring we want to find.
 * @recurse: True to search the children of @keyring also
 *
 * As keyring_search_rcu() above, but using the current task's credentials and
 * type's शेष matching function and preferred search method.
 */
key_ref_t keyring_search(key_ref_t keyring,
			 काष्ठा key_type *type,
			 स्थिर अक्षर *description,
			 bool recurse)
अणु
	काष्ठा keyring_search_context ctx = अणु
		.index_key.type		= type,
		.index_key.description	= description,
		.index_key.desc_len	= म_माप(description),
		.cred			= current_cred(),
		.match_data.cmp		= key_शेष_cmp,
		.match_data.raw_data	= description,
		.match_data.lookup_type	= KEYRING_SEARCH_LOOKUP_सूचीECT,
		.flags			= KEYRING_SEARCH_DO_STATE_CHECK,
	पूर्ण;
	key_ref_t key;
	पूर्णांक ret;

	अगर (recurse)
		ctx.flags |= KEYRING_SEARCH_RECURSE;
	अगर (type->match_preparse) अणु
		ret = type->match_preparse(&ctx.match_data);
		अगर (ret < 0)
			वापस ERR_PTR(ret);
	पूर्ण

	rcu_पढ़ो_lock();
	key = keyring_search_rcu(keyring, &ctx);
	rcu_पढ़ो_unlock();

	अगर (type->match_मुक्त)
		type->match_मुक्त(&ctx.match_data);
	वापस key;
पूर्ण
EXPORT_SYMBOL(keyring_search);

अटल काष्ठा key_restriction *keyring_restriction_alloc(
	key_restrict_link_func_t check)
अणु
	काष्ठा key_restriction *keyres =
		kzalloc(माप(काष्ठा key_restriction), GFP_KERNEL);

	अगर (!keyres)
		वापस ERR_PTR(-ENOMEM);

	keyres->check = check;

	वापस keyres;
पूर्ण

/*
 * Semaphore to serialise restriction setup to prevent reference count
 * cycles through restriction key poपूर्णांकers.
 */
अटल DECLARE_RWSEM(keyring_serialise_restrict_sem);

/*
 * Check क्रम restriction cycles that would prevent keyring garbage collection.
 * keyring_serialise_restrict_sem must be held.
 */
अटल bool keyring_detect_restriction_cycle(स्थिर काष्ठा key *dest_keyring,
					     काष्ठा key_restriction *keyres)
अणु
	जबतक (keyres && keyres->key &&
	       keyres->key->type == &key_type_keyring) अणु
		अगर (keyres->key == dest_keyring)
			वापस true;

		keyres = keyres->key->restrict_link;
	पूर्ण

	वापस false;
पूर्ण

/**
 * keyring_restrict - Look up and apply a restriction to a keyring
 * @keyring_ref: The keyring to be restricted
 * @type: The key type that will provide the restriction checker.
 * @restriction: The restriction options to apply to the keyring
 *
 * Look up a keyring and apply a restriction to it.  The restriction is managed
 * by the specअगरic key type, but can be configured by the options specअगरied in
 * the restriction string.
 */
पूर्णांक keyring_restrict(key_ref_t keyring_ref, स्थिर अक्षर *type,
		     स्थिर अक्षर *restriction)
अणु
	काष्ठा key *keyring;
	काष्ठा key_type *restrict_type = शून्य;
	काष्ठा key_restriction *restrict_link;
	पूर्णांक ret = 0;

	keyring = key_ref_to_ptr(keyring_ref);
	key_check(keyring);

	अगर (keyring->type != &key_type_keyring)
		वापस -ENOTसूची;

	अगर (!type) अणु
		restrict_link = keyring_restriction_alloc(restrict_link_reject);
	पूर्ण अन्यथा अणु
		restrict_type = key_type_lookup(type);

		अगर (IS_ERR(restrict_type))
			वापस PTR_ERR(restrict_type);

		अगर (!restrict_type->lookup_restriction) अणु
			ret = -ENOENT;
			जाओ error;
		पूर्ण

		restrict_link = restrict_type->lookup_restriction(restriction);
	पूर्ण

	अगर (IS_ERR(restrict_link)) अणु
		ret = PTR_ERR(restrict_link);
		जाओ error;
	पूर्ण

	करोwn_ग_लिखो(&keyring->sem);
	करोwn_ग_लिखो(&keyring_serialise_restrict_sem);

	अगर (keyring->restrict_link) अणु
		ret = -EEXIST;
	पूर्ण अन्यथा अगर (keyring_detect_restriction_cycle(keyring, restrict_link)) अणु
		ret = -EDEADLK;
	पूर्ण अन्यथा अणु
		keyring->restrict_link = restrict_link;
		notअगरy_key(keyring, NOTIFY_KEY_SETATTR, 0);
	पूर्ण

	up_ग_लिखो(&keyring_serialise_restrict_sem);
	up_ग_लिखो(&keyring->sem);

	अगर (ret < 0) अणु
		key_put(restrict_link->key);
		kमुक्त(restrict_link);
	पूर्ण

error:
	अगर (restrict_type)
		key_type_put(restrict_type);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(keyring_restrict);

/*
 * Search the given keyring क्रम a key that might be updated.
 *
 * The caller must guarantee that the keyring is a keyring and that the
 * permission is granted to modअगरy the keyring as no check is made here.  The
 * caller must also hold a lock on the keyring semaphore.
 *
 * Returns a poपूर्णांकer to the found key with usage count incremented अगर
 * successful and वापसs शून्य अगर not found.  Revoked and invalidated keys are
 * skipped over.
 *
 * If successful, the possession indicator is propagated from the keyring ref
 * to the वापसed key reference.
 */
key_ref_t find_key_to_update(key_ref_t keyring_ref,
			     स्थिर काष्ठा keyring_index_key *index_key)
अणु
	काष्ठा key *keyring, *key;
	स्थिर व्योम *object;

	keyring = key_ref_to_ptr(keyring_ref);

	kenter("{%d},{%s,%s}",
	       keyring->serial, index_key->type->name, index_key->description);

	object = assoc_array_find(&keyring->keys, &keyring_assoc_array_ops,
				  index_key);

	अगर (object)
		जाओ found;

	kleave(" = NULL");
	वापस शून्य;

found:
	key = keyring_ptr_to_key(object);
	अगर (key->flags & ((1 << KEY_FLAG_INVALIDATED) |
			  (1 << KEY_FLAG_REVOKED))) अणु
		kleave(" = NULL [x]");
		वापस शून्य;
	पूर्ण
	__key_get(key);
	kleave(" = {%d}", key->serial);
	वापस make_key_ref(key, is_key_possessed(keyring_ref));
पूर्ण

/*
 * Find a keyring with the specअगरied name.
 *
 * Only keyrings that have nonzero refcount, are not revoked, and are owned by a
 * user in the current user namespace are considered.  If @uid_keyring is %true,
 * the keyring additionally must have been allocated as a user or user session
 * keyring; otherwise, it must grant Search permission directly to the caller.
 *
 * Returns a poपूर्णांकer to the keyring with the keyring's refcount having being
 * incremented on success.  -ENOKEY is वापसed अगर a key could not be found.
 */
काष्ठा key *find_keyring_by_name(स्थिर अक्षर *name, bool uid_keyring)
अणु
	काष्ठा user_namespace *ns = current_user_ns();
	काष्ठा key *keyring;

	अगर (!name)
		वापस ERR_PTR(-EINVAL);

	पढ़ो_lock(&keyring_name_lock);

	/* Search this hash bucket क्रम a keyring with a matching name that
	 * grants Search permission and that hasn't been revoked
	 */
	list_क्रम_each_entry(keyring, &ns->keyring_name_list, name_link) अणु
		अगर (!kuid_has_mapping(ns, keyring->user->uid))
			जारी;

		अगर (test_bit(KEY_FLAG_REVOKED, &keyring->flags))
			जारी;

		अगर (म_भेद(keyring->description, name) != 0)
			जारी;

		अगर (uid_keyring) अणु
			अगर (!test_bit(KEY_FLAG_UID_KEYRING,
				      &keyring->flags))
				जारी;
		पूर्ण अन्यथा अणु
			अगर (key_permission(make_key_ref(keyring, 0),
					   KEY_NEED_SEARCH) < 0)
				जारी;
		पूर्ण

		/* we've got a match but we might end up racing with
		 * key_cleanup() अगर the keyring is currently 'dead'
		 * (ie. it has a zero usage count) */
		अगर (!refcount_inc_not_zero(&keyring->usage))
			जारी;
		keyring->last_used_at = kसमय_get_real_seconds();
		जाओ out;
	पूर्ण

	keyring = ERR_PTR(-ENOKEY);
out:
	पढ़ो_unlock(&keyring_name_lock);
	वापस keyring;
पूर्ण

अटल पूर्णांक keyring_detect_cycle_iterator(स्थिर व्योम *object,
					 व्योम *iterator_data)
अणु
	काष्ठा keyring_search_context *ctx = iterator_data;
	स्थिर काष्ठा key *key = keyring_ptr_to_key(object);

	kenter("{%d}", key->serial);

	/* We might get a keyring with matching index-key that is nonetheless a
	 * dअगरferent keyring. */
	अगर (key != ctx->match_data.raw_data)
		वापस 0;

	ctx->result = ERR_PTR(-EDEADLK);
	वापस 1;
पूर्ण

/*
 * See अगर a cycle will be created by inserting acyclic tree B in acyclic
 * tree A at the topmost level (ie: as a direct child of A).
 *
 * Since we are adding B to A at the top level, checking क्रम cycles should just
 * be a matter of seeing अगर node A is somewhere in tree B.
 */
अटल पूर्णांक keyring_detect_cycle(काष्ठा key *A, काष्ठा key *B)
अणु
	काष्ठा keyring_search_context ctx = अणु
		.index_key		= A->index_key,
		.match_data.raw_data	= A,
		.match_data.lookup_type = KEYRING_SEARCH_LOOKUP_सूचीECT,
		.iterator		= keyring_detect_cycle_iterator,
		.flags			= (KEYRING_SEARCH_NO_STATE_CHECK |
					   KEYRING_SEARCH_NO_UPDATE_TIME |
					   KEYRING_SEARCH_NO_CHECK_PERM |
					   KEYRING_SEARCH_DETECT_TOO_DEEP |
					   KEYRING_SEARCH_RECURSE),
	पूर्ण;

	rcu_पढ़ो_lock();
	search_nested_keyrings(B, &ctx);
	rcu_पढ़ो_unlock();
	वापस PTR_ERR(ctx.result) == -EAGAIN ? 0 : PTR_ERR(ctx.result);
पूर्ण

/*
 * Lock keyring क्रम link.
 */
पूर्णांक __key_link_lock(काष्ठा key *keyring,
		    स्थिर काष्ठा keyring_index_key *index_key)
	__acquires(&keyring->sem)
	__acquires(&keyring_serialise_link_lock)
अणु
	अगर (keyring->type != &key_type_keyring)
		वापस -ENOTसूची;

	करोwn_ग_लिखो(&keyring->sem);

	/* Serialise link/link calls to prevent parallel calls causing a cycle
	 * when linking two keyring in opposite orders.
	 */
	अगर (index_key->type == &key_type_keyring)
		mutex_lock(&keyring_serialise_link_lock);

	वापस 0;
पूर्ण

/*
 * Lock keyrings क्रम move (link/unlink combination).
 */
पूर्णांक __key_move_lock(काष्ठा key *l_keyring, काष्ठा key *u_keyring,
		    स्थिर काष्ठा keyring_index_key *index_key)
	__acquires(&l_keyring->sem)
	__acquires(&u_keyring->sem)
	__acquires(&keyring_serialise_link_lock)
अणु
	अगर (l_keyring->type != &key_type_keyring ||
	    u_keyring->type != &key_type_keyring)
		वापस -ENOTसूची;

	/* We have to be very careful here to take the keyring locks in the
	 * right order, lest we खोलो ourselves to deadlocking against another
	 * move operation.
	 */
	अगर (l_keyring < u_keyring) अणु
		करोwn_ग_लिखो(&l_keyring->sem);
		करोwn_ग_लिखो_nested(&u_keyring->sem, 1);
	पूर्ण अन्यथा अणु
		करोwn_ग_लिखो(&u_keyring->sem);
		करोwn_ग_लिखो_nested(&l_keyring->sem, 1);
	पूर्ण

	/* Serialise link/link calls to prevent parallel calls causing a cycle
	 * when linking two keyring in opposite orders.
	 */
	अगर (index_key->type == &key_type_keyring)
		mutex_lock(&keyring_serialise_link_lock);

	वापस 0;
पूर्ण

/*
 * Pपुनः_स्मृतिate memory so that a key can be linked पूर्णांकo to a keyring.
 */
पूर्णांक __key_link_begin(काष्ठा key *keyring,
		     स्थिर काष्ठा keyring_index_key *index_key,
		     काष्ठा assoc_array_edit **_edit)
अणु
	काष्ठा assoc_array_edit *edit;
	पूर्णांक ret;

	kenter("%d,%s,%s,",
	       keyring->serial, index_key->type->name, index_key->description);

	BUG_ON(index_key->desc_len == 0);
	BUG_ON(*_edit != शून्य);

	*_edit = शून्य;

	ret = -EKEYREVOKED;
	अगर (test_bit(KEY_FLAG_REVOKED, &keyring->flags))
		जाओ error;

	/* Create an edit script that will insert/replace the key in the
	 * keyring tree.
	 */
	edit = assoc_array_insert(&keyring->keys,
				  &keyring_assoc_array_ops,
				  index_key,
				  शून्य);
	अगर (IS_ERR(edit)) अणु
		ret = PTR_ERR(edit);
		जाओ error;
	पूर्ण

	/* If we're not replacing a link in-place then we're going to need some
	 * extra quota.
	 */
	अगर (!edit->dead_leaf) अणु
		ret = key_payload_reserve(keyring,
					  keyring->datalen + KEYQUOTA_LINK_BYTES);
		अगर (ret < 0)
			जाओ error_cancel;
	पूर्ण

	*_edit = edit;
	kleave(" = 0");
	वापस 0;

error_cancel:
	assoc_array_cancel_edit(edit);
error:
	kleave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * Check alपढ़ोy instantiated keys aren't going to be a problem.
 *
 * The caller must have called __key_link_begin(). Don't need to call this क्रम
 * keys that were created since __key_link_begin() was called.
 */
पूर्णांक __key_link_check_live_key(काष्ठा key *keyring, काष्ठा key *key)
अणु
	अगर (key->type == &key_type_keyring)
		/* check that we aren't going to create a cycle by linking one
		 * keyring to another */
		वापस keyring_detect_cycle(keyring, key);
	वापस 0;
पूर्ण

/*
 * Link a key पूर्णांकo to a keyring.
 *
 * Must be called with __key_link_begin() having being called.  Discards any
 * alपढ़ोy extant link to matching key अगर there is one, so that each keyring
 * holds at most one link to any given key of a particular type+description
 * combination.
 */
व्योम __key_link(काष्ठा key *keyring, काष्ठा key *key,
		काष्ठा assoc_array_edit **_edit)
अणु
	__key_get(key);
	assoc_array_insert_set_object(*_edit, keyring_key_to_ptr(key));
	assoc_array_apply_edit(*_edit);
	*_edit = शून्य;
	notअगरy_key(keyring, NOTIFY_KEY_LINKED, key_serial(key));
पूर्ण

/*
 * Finish linking a key पूर्णांकo to a keyring.
 *
 * Must be called with __key_link_begin() having being called.
 */
व्योम __key_link_end(काष्ठा key *keyring,
		    स्थिर काष्ठा keyring_index_key *index_key,
		    काष्ठा assoc_array_edit *edit)
	__releases(&keyring->sem)
	__releases(&keyring_serialise_link_lock)
अणु
	BUG_ON(index_key->type == शून्य);
	kenter("%d,%s,", keyring->serial, index_key->type->name);

	अगर (edit) अणु
		अगर (!edit->dead_leaf) अणु
			key_payload_reserve(keyring,
				keyring->datalen - KEYQUOTA_LINK_BYTES);
		पूर्ण
		assoc_array_cancel_edit(edit);
	पूर्ण
	up_ग_लिखो(&keyring->sem);

	अगर (index_key->type == &key_type_keyring)
		mutex_unlock(&keyring_serialise_link_lock);
पूर्ण

/*
 * Check addition of keys to restricted keyrings.
 */
अटल पूर्णांक __key_link_check_restriction(काष्ठा key *keyring, काष्ठा key *key)
अणु
	अगर (!keyring->restrict_link || !keyring->restrict_link->check)
		वापस 0;
	वापस keyring->restrict_link->check(keyring, key->type, &key->payload,
					     keyring->restrict_link->key);
पूर्ण

/**
 * key_link - Link a key to a keyring
 * @keyring: The keyring to make the link in.
 * @key: The key to link to.
 *
 * Make a link in a keyring to a key, such that the keyring holds a reference
 * on that key and the key can potentially be found by searching that keyring.
 *
 * This function will ग_लिखो-lock the keyring's semaphore and will consume some
 * of the user's key data quota to hold the link.
 *
 * Returns 0 अगर successful, -ENOTसूची अगर the keyring isn't a keyring,
 * -EKEYREVOKED अगर the keyring has been revoked, -ENखाता अगर the keyring is
 * full, -EDQUOT अगर there is insufficient key data quota reमुख्यing to add
 * another link or -ENOMEM अगर there's insufficient memory.
 *
 * It is assumed that the caller has checked that it is permitted क्रम a link to
 * be made (the keyring should have Write permission and the key Link
 * permission).
 */
पूर्णांक key_link(काष्ठा key *keyring, काष्ठा key *key)
अणु
	काष्ठा assoc_array_edit *edit = शून्य;
	पूर्णांक ret;

	kenter("{%d,%d}", keyring->serial, refcount_पढ़ो(&keyring->usage));

	key_check(keyring);
	key_check(key);

	ret = __key_link_lock(keyring, &key->index_key);
	अगर (ret < 0)
		जाओ error;

	ret = __key_link_begin(keyring, &key->index_key, &edit);
	अगर (ret < 0)
		जाओ error_end;

	kdebug("begun {%d,%d}", keyring->serial, refcount_पढ़ो(&keyring->usage));
	ret = __key_link_check_restriction(keyring, key);
	अगर (ret == 0)
		ret = __key_link_check_live_key(keyring, key);
	अगर (ret == 0)
		__key_link(keyring, key, &edit);

error_end:
	__key_link_end(keyring, &key->index_key, edit);
error:
	kleave(" = %d {%d,%d}", ret, keyring->serial, refcount_पढ़ो(&keyring->usage));
	वापस ret;
पूर्ण
EXPORT_SYMBOL(key_link);

/*
 * Lock a keyring क्रम unlink.
 */
अटल पूर्णांक __key_unlink_lock(काष्ठा key *keyring)
	__acquires(&keyring->sem)
अणु
	अगर (keyring->type != &key_type_keyring)
		वापस -ENOTसूची;

	करोwn_ग_लिखो(&keyring->sem);
	वापस 0;
पूर्ण

/*
 * Begin the process of unlinking a key from a keyring.
 */
अटल पूर्णांक __key_unlink_begin(काष्ठा key *keyring, काष्ठा key *key,
			      काष्ठा assoc_array_edit **_edit)
अणु
	काष्ठा assoc_array_edit *edit;

	BUG_ON(*_edit != शून्य);

	edit = assoc_array_delete(&keyring->keys, &keyring_assoc_array_ops,
				  &key->index_key);
	अगर (IS_ERR(edit))
		वापस PTR_ERR(edit);

	अगर (!edit)
		वापस -ENOENT;

	*_edit = edit;
	वापस 0;
पूर्ण

/*
 * Apply an unlink change.
 */
अटल व्योम __key_unlink(काष्ठा key *keyring, काष्ठा key *key,
			 काष्ठा assoc_array_edit **_edit)
अणु
	assoc_array_apply_edit(*_edit);
	notअगरy_key(keyring, NOTIFY_KEY_UNLINKED, key_serial(key));
	*_edit = शून्य;
	key_payload_reserve(keyring, keyring->datalen - KEYQUOTA_LINK_BYTES);
पूर्ण

/*
 * Finish unlinking a key from to a keyring.
 */
अटल व्योम __key_unlink_end(काष्ठा key *keyring,
			     काष्ठा key *key,
			     काष्ठा assoc_array_edit *edit)
	__releases(&keyring->sem)
अणु
	अगर (edit)
		assoc_array_cancel_edit(edit);
	up_ग_लिखो(&keyring->sem);
पूर्ण

/**
 * key_unlink - Unlink the first link to a key from a keyring.
 * @keyring: The keyring to हटाओ the link from.
 * @key: The key the link is to.
 *
 * Remove a link from a keyring to a key.
 *
 * This function will ग_लिखो-lock the keyring's semaphore.
 *
 * Returns 0 अगर successful, -ENOTसूची अगर the keyring isn't a keyring, -ENOENT अगर
 * the key isn't linked to by the keyring or -ENOMEM if there's insufficient
 * memory.
 *
 * It is assumed that the caller has checked that it is permitted क्रम a link to
 * be हटाओd (the keyring should have Write permission; no permissions are
 * required on the key).
 */
पूर्णांक key_unlink(काष्ठा key *keyring, काष्ठा key *key)
अणु
	काष्ठा assoc_array_edit *edit = शून्य;
	पूर्णांक ret;

	key_check(keyring);
	key_check(key);

	ret = __key_unlink_lock(keyring);
	अगर (ret < 0)
		वापस ret;

	ret = __key_unlink_begin(keyring, key, &edit);
	अगर (ret == 0)
		__key_unlink(keyring, key, &edit);
	__key_unlink_end(keyring, key, edit);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(key_unlink);

/**
 * key_move - Move a key from one keyring to another
 * @key: The key to move
 * @from_keyring: The keyring to हटाओ the link from.
 * @to_keyring: The keyring to make the link in.
 * @flags: Qualअगरying flags, such as KEYCTL_MOVE_EXCL.
 *
 * Make a link in @to_keyring to a key, such that the keyring holds a reference
 * on that key and the key can potentially be found by searching that keyring
 * whilst simultaneously removing a link to the key from @from_keyring.
 *
 * This function will ग_लिखो-lock both keyring's semaphores and will consume
 * some of the user's key data quota to hold the link on @to_keyring.
 *
 * Returns 0 अगर successful, -ENOTसूची अगर either keyring isn't a keyring,
 * -EKEYREVOKED अगर either keyring has been revoked, -ENखाता अगर the second
 * keyring is full, -EDQUOT अगर there is insufficient key data quota reमुख्यing
 * to add another link or -ENOMEM अगर there's insufficient memory.  If
 * KEYCTL_MOVE_EXCL is set, then -EEXIST will be वापसed अगर there's alपढ़ोy a
 * matching key in @to_keyring.
 *
 * It is assumed that the caller has checked that it is permitted क्रम a link to
 * be made (the keyring should have Write permission and the key Link
 * permission).
 */
पूर्णांक key_move(काष्ठा key *key,
	     काष्ठा key *from_keyring,
	     काष्ठा key *to_keyring,
	     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा assoc_array_edit *from_edit = शून्य, *to_edit = शून्य;
	पूर्णांक ret;

	kenter("%d,%d,%d", key->serial, from_keyring->serial, to_keyring->serial);

	अगर (from_keyring == to_keyring)
		वापस 0;

	key_check(key);
	key_check(from_keyring);
	key_check(to_keyring);

	ret = __key_move_lock(from_keyring, to_keyring, &key->index_key);
	अगर (ret < 0)
		जाओ out;
	ret = __key_unlink_begin(from_keyring, key, &from_edit);
	अगर (ret < 0)
		जाओ error;
	ret = __key_link_begin(to_keyring, &key->index_key, &to_edit);
	अगर (ret < 0)
		जाओ error;

	ret = -EEXIST;
	अगर (to_edit->dead_leaf && (flags & KEYCTL_MOVE_EXCL))
		जाओ error;

	ret = __key_link_check_restriction(to_keyring, key);
	अगर (ret < 0)
		जाओ error;
	ret = __key_link_check_live_key(to_keyring, key);
	अगर (ret < 0)
		जाओ error;

	__key_unlink(from_keyring, key, &from_edit);
	__key_link(to_keyring, key, &to_edit);
error:
	__key_link_end(to_keyring, &key->index_key, to_edit);
	__key_unlink_end(from_keyring, key, from_edit);
out:
	kleave(" = %d", ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(key_move);

/**
 * keyring_clear - Clear a keyring
 * @keyring: The keyring to clear.
 *
 * Clear the contents of the specअगरied keyring.
 *
 * Returns 0 अगर successful or -ENOTसूची अगर the keyring isn't a keyring.
 */
पूर्णांक keyring_clear(काष्ठा key *keyring)
अणु
	काष्ठा assoc_array_edit *edit;
	पूर्णांक ret;

	अगर (keyring->type != &key_type_keyring)
		वापस -ENOTसूची;

	करोwn_ग_लिखो(&keyring->sem);

	edit = assoc_array_clear(&keyring->keys, &keyring_assoc_array_ops);
	अगर (IS_ERR(edit)) अणु
		ret = PTR_ERR(edit);
	पूर्ण अन्यथा अणु
		अगर (edit)
			assoc_array_apply_edit(edit);
		notअगरy_key(keyring, NOTIFY_KEY_CLEARED, 0);
		key_payload_reserve(keyring, 0);
		ret = 0;
	पूर्ण

	up_ग_लिखो(&keyring->sem);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(keyring_clear);

/*
 * Dispose of the links from a revoked keyring.
 *
 * This is called with the key sem ग_लिखो-locked.
 */
अटल व्योम keyring_revoke(काष्ठा key *keyring)
अणु
	काष्ठा assoc_array_edit *edit;

	edit = assoc_array_clear(&keyring->keys, &keyring_assoc_array_ops);
	अगर (!IS_ERR(edit)) अणु
		अगर (edit)
			assoc_array_apply_edit(edit);
		key_payload_reserve(keyring, 0);
	पूर्ण
पूर्ण

अटल bool keyring_gc_select_iterator(व्योम *object, व्योम *iterator_data)
अणु
	काष्ठा key *key = keyring_ptr_to_key(object);
	समय64_t *limit = iterator_data;

	अगर (key_is_dead(key, *limit))
		वापस false;
	key_get(key);
	वापस true;
पूर्ण

अटल पूर्णांक keyring_gc_check_iterator(स्थिर व्योम *object, व्योम *iterator_data)
अणु
	स्थिर काष्ठा key *key = keyring_ptr_to_key(object);
	समय64_t *limit = iterator_data;

	key_check(key);
	वापस key_is_dead(key, *limit);
पूर्ण

/*
 * Garbage collect poपूर्णांकers from a keyring.
 *
 * Not called with any locks held.  The keyring's key काष्ठा will not be
 * deallocated under us as only our caller may deallocate it.
 */
व्योम keyring_gc(काष्ठा key *keyring, समय64_t limit)
अणु
	पूर्णांक result;

	kenter("%x{%s}", keyring->serial, keyring->description ?: "");

	अगर (keyring->flags & ((1 << KEY_FLAG_INVALIDATED) |
			      (1 << KEY_FLAG_REVOKED)))
		जाओ करोnt_gc;

	/* scan the keyring looking क्रम dead keys */
	rcu_पढ़ो_lock();
	result = assoc_array_iterate(&keyring->keys,
				     keyring_gc_check_iterator, &limit);
	rcu_पढ़ो_unlock();
	अगर (result == true)
		जाओ करो_gc;

करोnt_gc:
	kleave(" [no gc]");
	वापस;

करो_gc:
	करोwn_ग_लिखो(&keyring->sem);
	assoc_array_gc(&keyring->keys, &keyring_assoc_array_ops,
		       keyring_gc_select_iterator, &limit);
	up_ग_लिखो(&keyring->sem);
	kleave(" [gc]");
पूर्ण

/*
 * Garbage collect restriction poपूर्णांकers from a keyring.
 *
 * Keyring restrictions are associated with a key type, and must be cleaned
 * up अगर the key type is unरेजिस्टरed. The restriction is altered to always
 * reject additional keys so a keyring cannot be खोलोed up by unरेजिस्टरing
 * a key type.
 *
 * Not called with any keyring locks held. The keyring's key काष्ठा will not
 * be deallocated under us as only our caller may deallocate it.
 *
 * The caller is required to hold key_types_sem and dead_type->sem. This is
 * fulfilled by key_gc_keytype() holding the locks on behalf of
 * key_garbage_collector(), which it invokes on a workqueue.
 */
व्योम keyring_restriction_gc(काष्ठा key *keyring, काष्ठा key_type *dead_type)
अणु
	काष्ठा key_restriction *keyres;

	kenter("%x{%s}", keyring->serial, keyring->description ?: "");

	/*
	 * keyring->restrict_link is only asचिन्हित at key allocation समय
	 * or with the key type locked, so the only values that could be
	 * concurrently asचिन्हित to keyring->restrict_link are क्रम key
	 * types other than dead_type. Given this, it's ok to check
	 * the key type beक्रमe acquiring keyring->sem.
	 */
	अगर (!dead_type || !keyring->restrict_link ||
	    keyring->restrict_link->keytype != dead_type) अणु
		kleave(" [no restriction gc]");
		वापस;
	पूर्ण

	/* Lock the keyring to ensure that a link is not in progress */
	करोwn_ग_लिखो(&keyring->sem);

	keyres = keyring->restrict_link;

	keyres->check = restrict_link_reject;

	key_put(keyres->key);
	keyres->key = शून्य;
	keyres->keytype = शून्य;

	up_ग_लिखो(&keyring->sem);

	kleave(" [restriction gc]");
पूर्ण
