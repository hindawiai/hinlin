<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright 2007 Hewlett-Packard Development Company, L.P.
 *
 * This file is part of the SCTP kernel implementation
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *   Vlad Yasevich     <vladislav.yasevich@hp.com>
 */

#समावेश <crypto/hash.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/scatterlist.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/auth.h>

अटल काष्ठा sctp_hmac sctp_hmac_list[SCTP_AUTH_NUM_HMACS] = अणु
	अणु
		/* id 0 is reserved.  as all 0 */
		.hmac_id = SCTP_AUTH_HMAC_ID_RESERVED_0,
	पूर्ण,
	अणु
		.hmac_id = SCTP_AUTH_HMAC_ID_SHA1,
		.hmac_name = "hmac(sha1)",
		.hmac_len = SCTP_SHA1_SIG_SIZE,
	पूर्ण,
	अणु
		/* id 2 is reserved as well */
		.hmac_id = SCTP_AUTH_HMAC_ID_RESERVED_2,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_CRYPTO_SHA256)
	अणु
		.hmac_id = SCTP_AUTH_HMAC_ID_SHA256,
		.hmac_name = "hmac(sha256)",
		.hmac_len = SCTP_SHA256_SIG_SIZE,
	पूर्ण
#पूर्ण_अगर
पूर्ण;


व्योम sctp_auth_key_put(काष्ठा sctp_auth_bytes *key)
अणु
	अगर (!key)
		वापस;

	अगर (refcount_dec_and_test(&key->refcnt)) अणु
		kमुक्त_sensitive(key);
		SCTP_DBG_OBJCNT_DEC(keys);
	पूर्ण
पूर्ण

/* Create a new key काष्ठाure of a given length */
अटल काष्ठा sctp_auth_bytes *sctp_auth_create_key(__u32 key_len, gfp_t gfp)
अणु
	काष्ठा sctp_auth_bytes *key;

	/* Verअगरy that we are not going to overflow पूर्णांक_उच्च */
	अगर (key_len > (पूर्णांक_उच्च - माप(काष्ठा sctp_auth_bytes)))
		वापस शून्य;

	/* Allocate the shared key */
	key = kदो_स्मृति(माप(काष्ठा sctp_auth_bytes) + key_len, gfp);
	अगर (!key)
		वापस शून्य;

	key->len = key_len;
	refcount_set(&key->refcnt, 1);
	SCTP_DBG_OBJCNT_INC(keys);

	वापस key;
पूर्ण

/* Create a new shared key container with a give key id */
काष्ठा sctp_shared_key *sctp_auth_shkey_create(__u16 key_id, gfp_t gfp)
अणु
	काष्ठा sctp_shared_key *new;

	/* Allocate the shared key container */
	new = kzalloc(माप(काष्ठा sctp_shared_key), gfp);
	अगर (!new)
		वापस शून्य;

	INIT_LIST_HEAD(&new->key_list);
	refcount_set(&new->refcnt, 1);
	new->key_id = key_id;

	वापस new;
पूर्ण

/* Free the shared key काष्ठाure */
अटल व्योम sctp_auth_shkey_destroy(काष्ठा sctp_shared_key *sh_key)
अणु
	BUG_ON(!list_empty(&sh_key->key_list));
	sctp_auth_key_put(sh_key->key);
	sh_key->key = शून्य;
	kमुक्त(sh_key);
पूर्ण

व्योम sctp_auth_shkey_release(काष्ठा sctp_shared_key *sh_key)
अणु
	अगर (refcount_dec_and_test(&sh_key->refcnt))
		sctp_auth_shkey_destroy(sh_key);
पूर्ण

व्योम sctp_auth_shkey_hold(काष्ठा sctp_shared_key *sh_key)
अणु
	refcount_inc(&sh_key->refcnt);
पूर्ण

/* Destroy the entire key list.  This is करोne during the
 * associon and endpoपूर्णांक मुक्त process.
 */
व्योम sctp_auth_destroy_keys(काष्ठा list_head *keys)
अणु
	काष्ठा sctp_shared_key *ep_key;
	काष्ठा sctp_shared_key *पंचांगp;

	अगर (list_empty(keys))
		वापस;

	key_क्रम_each_safe(ep_key, पंचांगp, keys) अणु
		list_del_init(&ep_key->key_list);
		sctp_auth_shkey_release(ep_key);
	पूर्ण
पूर्ण

/* Compare two byte vectors as numbers.  Return values
 * are:
 * 	  0 - vectors are equal
 * 	< 0 - vector 1 is smaller than vector2
 * 	> 0 - vector 1 is greater than vector2
 *
 * Algorithm is:
 * 	This is perक्रमmed by selecting the numerically smaller key vector...
 *	If the key vectors are equal as numbers but dअगरfer in length ...
 *	the लघुer vector is considered smaller
 *
 * Examples (with small values):
 * 	000123456789 > 123456789 (first number is दीर्घer)
 * 	000123456789 < 234567891 (second number is larger numerically)
 * 	123456789 > 2345678 	 (first number is both larger & दीर्घer)
 */
अटल पूर्णांक sctp_auth_compare_vectors(काष्ठा sctp_auth_bytes *vector1,
			      काष्ठा sctp_auth_bytes *vector2)
अणु
	पूर्णांक dअगरf;
	पूर्णांक i;
	स्थिर __u8 *दीर्घer;

	dअगरf = vector1->len - vector2->len;
	अगर (dअगरf) अणु
		दीर्घer = (dअगरf > 0) ? vector1->data : vector2->data;

		/* Check to see अगर the दीर्घer number is
		 * lead-zero padded.  If it is not, it
		 * is स्वतःmatically larger numerically.
		 */
		क्रम (i = 0; i < असल(dअगरf); i++) अणु
			अगर (दीर्घer[i] != 0)
				वापस dअगरf;
		पूर्ण
	पूर्ण

	/* lengths are the same, compare numbers */
	वापस स_भेद(vector1->data, vector2->data, vector1->len);
पूर्ण

/*
 * Create a key vector as described in SCTP-AUTH, Section 6.1
 *    The RANDOM parameter, the CHUNKS parameter and the HMAC-ALGO
 *    parameter sent by each endpoपूर्णांक are concatenated as byte vectors.
 *    These parameters include the parameter type, parameter length, and
 *    the parameter value, but padding is omitted; all padding MUST be
 *    हटाओd from this concatenation beक्रमe proceeding with further
 *    computation of keys.  Parameters which were not sent are simply
 *    omitted from the concatenation process.  The resulting two vectors
 *    are called the two key vectors.
 */
अटल काष्ठा sctp_auth_bytes *sctp_auth_make_key_vector(
			काष्ठा sctp_अक्रमom_param *अक्रमom,
			काष्ठा sctp_chunks_param *chunks,
			काष्ठा sctp_hmac_algo_param *hmacs,
			gfp_t gfp)
अणु
	काष्ठा sctp_auth_bytes *new;
	__u32	len;
	__u32	offset = 0;
	__u16	अक्रमom_len, hmacs_len, chunks_len = 0;

	अक्रमom_len = ntohs(अक्रमom->param_hdr.length);
	hmacs_len = ntohs(hmacs->param_hdr.length);
	अगर (chunks)
		chunks_len = ntohs(chunks->param_hdr.length);

	len = अक्रमom_len + hmacs_len + chunks_len;

	new = sctp_auth_create_key(len, gfp);
	अगर (!new)
		वापस शून्य;

	स_नकल(new->data, अक्रमom, अक्रमom_len);
	offset += अक्रमom_len;

	अगर (chunks) अणु
		स_नकल(new->data + offset, chunks, chunks_len);
		offset += chunks_len;
	पूर्ण

	स_नकल(new->data + offset, hmacs, hmacs_len);

	वापस new;
पूर्ण


/* Make a key vector based on our local parameters */
अटल काष्ठा sctp_auth_bytes *sctp_auth_make_local_vector(
				    स्थिर काष्ठा sctp_association *asoc,
				    gfp_t gfp)
अणु
	वापस sctp_auth_make_key_vector(
			(काष्ठा sctp_अक्रमom_param *)asoc->c.auth_अक्रमom,
			(काष्ठा sctp_chunks_param *)asoc->c.auth_chunks,
			(काष्ठा sctp_hmac_algo_param *)asoc->c.auth_hmacs, gfp);
पूर्ण

/* Make a key vector based on peer's parameters */
अटल काष्ठा sctp_auth_bytes *sctp_auth_make_peer_vector(
				    स्थिर काष्ठा sctp_association *asoc,
				    gfp_t gfp)
अणु
	वापस sctp_auth_make_key_vector(asoc->peer.peer_अक्रमom,
					 asoc->peer.peer_chunks,
					 asoc->peer.peer_hmacs,
					 gfp);
पूर्ण


/* Set the value of the association shared key base on the parameters
 * given.  The algorithm is:
 *    From the endpoपूर्णांक pair shared keys and the key vectors the
 *    association shared keys are computed.  This is perक्रमmed by selecting
 *    the numerically smaller key vector and concatenating it to the
 *    endpoपूर्णांक pair shared key, and then concatenating the numerically
 *    larger key vector to that.  The result of the concatenation is the
 *    association shared key.
 */
अटल काष्ठा sctp_auth_bytes *sctp_auth_asoc_set_secret(
			काष्ठा sctp_shared_key *ep_key,
			काष्ठा sctp_auth_bytes *first_vector,
			काष्ठा sctp_auth_bytes *last_vector,
			gfp_t gfp)
अणु
	काष्ठा sctp_auth_bytes *secret;
	__u32 offset = 0;
	__u32 auth_len;

	auth_len = first_vector->len + last_vector->len;
	अगर (ep_key->key)
		auth_len += ep_key->key->len;

	secret = sctp_auth_create_key(auth_len, gfp);
	अगर (!secret)
		वापस शून्य;

	अगर (ep_key->key) अणु
		स_नकल(secret->data, ep_key->key->data, ep_key->key->len);
		offset += ep_key->key->len;
	पूर्ण

	स_नकल(secret->data + offset, first_vector->data, first_vector->len);
	offset += first_vector->len;

	स_नकल(secret->data + offset, last_vector->data, last_vector->len);

	वापस secret;
पूर्ण

/* Create an association shared key.  Follow the algorithm
 * described in SCTP-AUTH, Section 6.1
 */
अटल काष्ठा sctp_auth_bytes *sctp_auth_asoc_create_secret(
				 स्थिर काष्ठा sctp_association *asoc,
				 काष्ठा sctp_shared_key *ep_key,
				 gfp_t gfp)
अणु
	काष्ठा sctp_auth_bytes *local_key_vector;
	काष्ठा sctp_auth_bytes *peer_key_vector;
	काष्ठा sctp_auth_bytes	*first_vector,
				*last_vector;
	काष्ठा sctp_auth_bytes	*secret = शून्य;
	पूर्णांक	cmp;


	/* Now we need to build the key vectors
	 * SCTP-AUTH , Section 6.1
	 *    The RANDOM parameter, the CHUNKS parameter and the HMAC-ALGO
	 *    parameter sent by each endpoपूर्णांक are concatenated as byte vectors.
	 *    These parameters include the parameter type, parameter length, and
	 *    the parameter value, but padding is omitted; all padding MUST be
	 *    हटाओd from this concatenation beक्रमe proceeding with further
	 *    computation of keys.  Parameters which were not sent are simply
	 *    omitted from the concatenation process.  The resulting two vectors
	 *    are called the two key vectors.
	 */

	local_key_vector = sctp_auth_make_local_vector(asoc, gfp);
	peer_key_vector = sctp_auth_make_peer_vector(asoc, gfp);

	अगर (!peer_key_vector || !local_key_vector)
		जाओ out;

	/* Figure out the order in which the key_vectors will be
	 * added to the endpoपूर्णांक shared key.
	 * SCTP-AUTH, Section 6.1:
	 *   This is perक्रमmed by selecting the numerically smaller key
	 *   vector and concatenating it to the endpoपूर्णांक pair shared
	 *   key, and then concatenating the numerically larger key
	 *   vector to that.  If the key vectors are equal as numbers
	 *   but dअगरfer in length, then the concatenation order is the
	 *   endpoपूर्णांक shared key, followed by the लघुer key vector,
	 *   followed by the दीर्घer key vector.  Otherwise, the key
	 *   vectors are identical, and may be concatenated to the
	 *   endpoपूर्णांक pair key in any order.
	 */
	cmp = sctp_auth_compare_vectors(local_key_vector,
					peer_key_vector);
	अगर (cmp < 0) अणु
		first_vector = local_key_vector;
		last_vector = peer_key_vector;
	पूर्ण अन्यथा अणु
		first_vector = peer_key_vector;
		last_vector = local_key_vector;
	पूर्ण

	secret = sctp_auth_asoc_set_secret(ep_key, first_vector, last_vector,
					    gfp);
out:
	sctp_auth_key_put(local_key_vector);
	sctp_auth_key_put(peer_key_vector);

	वापस secret;
पूर्ण

/*
 * Populate the association overlay list with the list
 * from the endpoपूर्णांक.
 */
पूर्णांक sctp_auth_asoc_copy_shkeys(स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				काष्ठा sctp_association *asoc,
				gfp_t gfp)
अणु
	काष्ठा sctp_shared_key *sh_key;
	काष्ठा sctp_shared_key *new;

	BUG_ON(!list_empty(&asoc->endpoपूर्णांक_shared_keys));

	key_क्रम_each(sh_key, &ep->endpoपूर्णांक_shared_keys) अणु
		new = sctp_auth_shkey_create(sh_key->key_id, gfp);
		अगर (!new)
			जाओ nomem;

		new->key = sh_key->key;
		sctp_auth_key_hold(new->key);
		list_add(&new->key_list, &asoc->endpoपूर्णांक_shared_keys);
	पूर्ण

	वापस 0;

nomem:
	sctp_auth_destroy_keys(&asoc->endpoपूर्णांक_shared_keys);
	वापस -ENOMEM;
पूर्ण


/* Public पूर्णांकerface to create the association shared key.
 * See code above क्रम the algorithm.
 */
पूर्णांक sctp_auth_asoc_init_active_key(काष्ठा sctp_association *asoc, gfp_t gfp)
अणु
	काष्ठा sctp_auth_bytes	*secret;
	काष्ठा sctp_shared_key *ep_key;
	काष्ठा sctp_chunk *chunk;

	/* If we करोn't support AUTH, or peer is not capable
	 * we करोn't need to करो anything.
	 */
	अगर (!asoc->peer.auth_capable)
		वापस 0;

	/* If the key_id is non-zero and we couldn't find an
	 * endpoपूर्णांक pair shared key, we can't compute the
	 * secret.
	 * For key_id 0, endpoपूर्णांक pair shared key is a शून्य key.
	 */
	ep_key = sctp_auth_get_shkey(asoc, asoc->active_key_id);
	BUG_ON(!ep_key);

	secret = sctp_auth_asoc_create_secret(asoc, ep_key, gfp);
	अगर (!secret)
		वापस -ENOMEM;

	sctp_auth_key_put(asoc->asoc_shared_key);
	asoc->asoc_shared_key = secret;
	asoc->shkey = ep_key;

	/* Update send queue in हाल any chunk alपढ़ोy in there now
	 * needs authenticating
	 */
	list_क्रम_each_entry(chunk, &asoc->outqueue.out_chunk_list, list) अणु
		अगर (sctp_auth_send_cid(chunk->chunk_hdr->type, asoc)) अणु
			chunk->auth = 1;
			अगर (!chunk->shkey) अणु
				chunk->shkey = asoc->shkey;
				sctp_auth_shkey_hold(chunk->shkey);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


/* Find the endpoपूर्णांक pair shared key based on the key_id */
काष्ठा sctp_shared_key *sctp_auth_get_shkey(
				स्थिर काष्ठा sctp_association *asoc,
				__u16 key_id)
अणु
	काष्ठा sctp_shared_key *key;

	/* First search associations set of endpoपूर्णांक pair shared keys */
	key_क्रम_each(key, &asoc->endpoपूर्णांक_shared_keys) अणु
		अगर (key->key_id == key_id) अणु
			अगर (!key->deactivated)
				वापस key;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Initialize all the possible digest transक्रमms that we can use.  Right
 * now, the supported digests are SHA1 and SHA256.  We करो this here once
 * because of the restrictiong that transक्रमms may only be allocated in
 * user context.  This क्रमces us to pre-allocated all possible transक्रमms
 * at the endpoपूर्णांक init समय.
 */
पूर्णांक sctp_auth_init_hmacs(काष्ठा sctp_endpoपूर्णांक *ep, gfp_t gfp)
अणु
	काष्ठा crypto_shash *tfm = शून्य;
	__u16   id;

	/* If the transक्रमms are alपढ़ोy allocated, we are करोne */
	अगर (ep->auth_hmacs)
		वापस 0;

	/* Allocated the array of poपूर्णांकers to transorms */
	ep->auth_hmacs = kसुस्मृति(SCTP_AUTH_NUM_HMACS,
				 माप(काष्ठा crypto_shash *),
				 gfp);
	अगर (!ep->auth_hmacs)
		वापस -ENOMEM;

	क्रम (id = 0; id < SCTP_AUTH_NUM_HMACS; id++) अणु

		/* See is we support the id.  Supported IDs have name and
		 * length fields set, so that we can allocated and use
		 * them.  We can safely just check क्रम name, क्रम without the
		 * name, we can't allocate the TFM.
		 */
		अगर (!sctp_hmac_list[id].hmac_name)
			जारी;

		/* If this TFM has been allocated, we are all set */
		अगर (ep->auth_hmacs[id])
			जारी;

		/* Allocate the ID */
		tfm = crypto_alloc_shash(sctp_hmac_list[id].hmac_name, 0, 0);
		अगर (IS_ERR(tfm))
			जाओ out_err;

		ep->auth_hmacs[id] = tfm;
	पूर्ण

	वापस 0;

out_err:
	/* Clean up any successful allocations */
	sctp_auth_destroy_hmacs(ep->auth_hmacs);
	ep->auth_hmacs = शून्य;
	वापस -ENOMEM;
पूर्ण

/* Destroy the hmac tfm array */
व्योम sctp_auth_destroy_hmacs(काष्ठा crypto_shash *auth_hmacs[])
अणु
	पूर्णांक i;

	अगर (!auth_hmacs)
		वापस;

	क्रम (i = 0; i < SCTP_AUTH_NUM_HMACS; i++) अणु
		crypto_मुक्त_shash(auth_hmacs[i]);
	पूर्ण
	kमुक्त(auth_hmacs);
पूर्ण


काष्ठा sctp_hmac *sctp_auth_get_hmac(__u16 hmac_id)
अणु
	वापस &sctp_hmac_list[hmac_id];
पूर्ण

/* Get an hmac description inक्रमmation that we can use to build
 * the AUTH chunk
 */
काष्ठा sctp_hmac *sctp_auth_asoc_get_hmac(स्थिर काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_hmac_algo_param *hmacs;
	__u16 n_elt;
	__u16 id = 0;
	पूर्णांक i;

	/* If we have a शेष entry, use it */
	अगर (asoc->शेष_hmac_id)
		वापस &sctp_hmac_list[asoc->शेष_hmac_id];

	/* Since we करो not have a शेष entry, find the first entry
	 * we support and वापस that.  Do not cache that id.
	 */
	hmacs = asoc->peer.peer_hmacs;
	अगर (!hmacs)
		वापस शून्य;

	n_elt = (ntohs(hmacs->param_hdr.length) -
		 माप(काष्ठा sctp_paramhdr)) >> 1;
	क्रम (i = 0; i < n_elt; i++) अणु
		id = ntohs(hmacs->hmac_ids[i]);

		/* Check the id is in the supported range. And
		 * see अगर we support the id.  Supported IDs have name and
		 * length fields set, so that we can allocate and use
		 * them.  We can safely just check क्रम name, क्रम without the
		 * name, we can't allocate the TFM.
		 */
		अगर (id > SCTP_AUTH_HMAC_ID_MAX ||
		    !sctp_hmac_list[id].hmac_name) अणु
			id = 0;
			जारी;
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (id == 0)
		वापस शून्य;

	वापस &sctp_hmac_list[id];
पूर्ण

अटल पूर्णांक __sctp_auth_find_hmacid(__be16 *hmacs, पूर्णांक n_elts, __be16 hmac_id)
अणु
	पूर्णांक  found = 0;
	पूर्णांक  i;

	क्रम (i = 0; i < n_elts; i++) अणु
		अगर (hmac_id == hmacs[i]) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

/* See अगर the HMAC_ID is one that we claim as supported */
पूर्णांक sctp_auth_asoc_verअगरy_hmac_id(स्थिर काष्ठा sctp_association *asoc,
				    __be16 hmac_id)
अणु
	काष्ठा sctp_hmac_algo_param *hmacs;
	__u16 n_elt;

	अगर (!asoc)
		वापस 0;

	hmacs = (काष्ठा sctp_hmac_algo_param *)asoc->c.auth_hmacs;
	n_elt = (ntohs(hmacs->param_hdr.length) -
		 माप(काष्ठा sctp_paramhdr)) >> 1;

	वापस __sctp_auth_find_hmacid(hmacs->hmac_ids, n_elt, hmac_id);
पूर्ण


/* Cache the शेष HMAC id.  This to follow this text from SCTP-AUTH:
 * Section 6.1:
 *   The receiver of a HMAC-ALGO parameter SHOULD use the first listed
 *   algorithm it supports.
 */
व्योम sctp_auth_asoc_set_शेष_hmac(काष्ठा sctp_association *asoc,
				     काष्ठा sctp_hmac_algo_param *hmacs)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep;
	__u16   id;
	पूर्णांक	i;
	पूर्णांक	n_params;

	/* अगर the शेष id is alपढ़ोy set, use it */
	अगर (asoc->शेष_hmac_id)
		वापस;

	n_params = (ntohs(hmacs->param_hdr.length) -
		    माप(काष्ठा sctp_paramhdr)) >> 1;
	ep = asoc->ep;
	क्रम (i = 0; i < n_params; i++) अणु
		id = ntohs(hmacs->hmac_ids[i]);

		/* Check the id is in the supported range */
		अगर (id > SCTP_AUTH_HMAC_ID_MAX)
			जारी;

		/* If this TFM has been allocated, use this id */
		अगर (ep->auth_hmacs[id]) अणु
			asoc->शेष_hmac_id = id;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण


/* Check to see अगर the given chunk is supposed to be authenticated */
अटल पूर्णांक __sctp_auth_cid(क्रमागत sctp_cid chunk, काष्ठा sctp_chunks_param *param)
अणु
	अचिन्हित लघु len;
	पूर्णांक found = 0;
	पूर्णांक i;

	अगर (!param || param->param_hdr.length == 0)
		वापस 0;

	len = ntohs(param->param_hdr.length) - माप(काष्ठा sctp_paramhdr);

	/* SCTP-AUTH, Section 3.2
	 *    The chunk types क्रम INIT, INIT-ACK, SHUTDOWN-COMPLETE and AUTH
	 *    chunks MUST NOT be listed in the CHUNKS parameter.  However, अगर
	 *    a CHUNKS parameter is received then the types क्रम INIT, INIT-ACK,
	 *    SHUTDOWN-COMPLETE and AUTH chunks MUST be ignored.
	 */
	क्रम (i = 0; !found && i < len; i++) अणु
		चयन (param->chunks[i]) अणु
		हाल SCTP_CID_INIT:
		हाल SCTP_CID_INIT_ACK:
		हाल SCTP_CID_SHUTDOWN_COMPLETE:
		हाल SCTP_CID_AUTH:
			अवरोध;

		शेष:
			अगर (param->chunks[i] == chunk)
				found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

/* Check अगर peer requested that this chunk is authenticated */
पूर्णांक sctp_auth_send_cid(क्रमागत sctp_cid chunk, स्थिर काष्ठा sctp_association *asoc)
अणु
	अगर (!asoc)
		वापस 0;

	अगर (!asoc->peer.auth_capable)
		वापस 0;

	वापस __sctp_auth_cid(chunk, asoc->peer.peer_chunks);
पूर्ण

/* Check अगर we requested that peer authenticate this chunk. */
पूर्णांक sctp_auth_recv_cid(क्रमागत sctp_cid chunk, स्थिर काष्ठा sctp_association *asoc)
अणु
	अगर (!asoc)
		वापस 0;

	अगर (!asoc->peer.auth_capable)
		वापस 0;

	वापस __sctp_auth_cid(chunk,
			      (काष्ठा sctp_chunks_param *)asoc->c.auth_chunks);
पूर्ण

/* SCTP-AUTH: Section 6.2:
 *    The sender MUST calculate the MAC as described in RFC2104 [2] using
 *    the hash function H as described by the MAC Identअगरier and the shared
 *    association key K based on the endpoपूर्णांक pair shared key described by
 *    the shared key identअगरier.  The 'data' used क्रम the computation of
 *    the AUTH-chunk is given by the AUTH chunk with its HMAC field set to
 *    zero (as shown in Figure 6) followed by all chunks that are placed
 *    after the AUTH chunk in the SCTP packet.
 */
व्योम sctp_auth_calculate_hmac(स्थिर काष्ठा sctp_association *asoc,
			      काष्ठा sk_buff *skb, काष्ठा sctp_auth_chunk *auth,
			      काष्ठा sctp_shared_key *ep_key, gfp_t gfp)
अणु
	काष्ठा sctp_auth_bytes *asoc_key;
	काष्ठा crypto_shash *tfm;
	__u16 key_id, hmac_id;
	अचिन्हित अक्षर *end;
	पूर्णांक मुक्त_key = 0;
	__u8 *digest;

	/* Extract the info we need:
	 * - hmac id
	 * - key id
	 */
	key_id = ntohs(auth->auth_hdr.shkey_id);
	hmac_id = ntohs(auth->auth_hdr.hmac_id);

	अगर (key_id == asoc->active_key_id)
		asoc_key = asoc->asoc_shared_key;
	अन्यथा अणु
		/* ep_key can't be शून्य here */
		asoc_key = sctp_auth_asoc_create_secret(asoc, ep_key, gfp);
		अगर (!asoc_key)
			वापस;

		मुक्त_key = 1;
	पूर्ण

	/* set up scatter list */
	end = skb_tail_poपूर्णांकer(skb);

	tfm = asoc->ep->auth_hmacs[hmac_id];

	digest = auth->auth_hdr.hmac;
	अगर (crypto_shash_setkey(tfm, &asoc_key->data[0], asoc_key->len))
		जाओ मुक्त;

	crypto_shash_tfm_digest(tfm, (u8 *)auth, end - (अचिन्हित अक्षर *)auth,
				digest);

मुक्त:
	अगर (मुक्त_key)
		sctp_auth_key_put(asoc_key);
पूर्ण

/* API Helpers */

/* Add a chunk to the endpoपूर्णांक authenticated chunk list */
पूर्णांक sctp_auth_ep_add_chunkid(काष्ठा sctp_endpoपूर्णांक *ep, __u8 chunk_id)
अणु
	काष्ठा sctp_chunks_param *p = ep->auth_chunk_list;
	__u16 nchunks;
	__u16 param_len;

	/* If this chunk is alपढ़ोy specअगरied, we are करोne */
	अगर (__sctp_auth_cid(chunk_id, p))
		वापस 0;

	/* Check अगर we can add this chunk to the array */
	param_len = ntohs(p->param_hdr.length);
	nchunks = param_len - माप(काष्ठा sctp_paramhdr);
	अगर (nchunks == SCTP_NUM_CHUNK_TYPES)
		वापस -EINVAL;

	p->chunks[nchunks] = chunk_id;
	p->param_hdr.length = htons(param_len + 1);
	वापस 0;
पूर्ण

/* Add hmac identअगरires to the endpoपूर्णांक list of supported hmac ids */
पूर्णांक sctp_auth_ep_set_hmacs(काष्ठा sctp_endpoपूर्णांक *ep,
			   काष्ठा sctp_hmacalgo *hmacs)
अणु
	पूर्णांक has_sha1 = 0;
	__u16 id;
	पूर्णांक i;

	/* Scan the list looking क्रम unsupported id.  Also make sure that
	 * SHA1 is specअगरied.
	 */
	क्रम (i = 0; i < hmacs->shmac_num_idents; i++) अणु
		id = hmacs->shmac_idents[i];

		अगर (id > SCTP_AUTH_HMAC_ID_MAX)
			वापस -EOPNOTSUPP;

		अगर (SCTP_AUTH_HMAC_ID_SHA1 == id)
			has_sha1 = 1;

		अगर (!sctp_hmac_list[id].hmac_name)
			वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!has_sha1)
		वापस -EINVAL;

	क्रम (i = 0; i < hmacs->shmac_num_idents; i++)
		ep->auth_hmacs_list->hmac_ids[i] =
				htons(hmacs->shmac_idents[i]);
	ep->auth_hmacs_list->param_hdr.length =
			htons(माप(काष्ठा sctp_paramhdr) +
			hmacs->shmac_num_idents * माप(__u16));
	वापस 0;
पूर्ण

/* Set a new shared key on either endpoपूर्णांक or association.  If the
 * key with a same ID alपढ़ोy exists, replace the key (हटाओ the
 * old key and add a new one).
 */
पूर्णांक sctp_auth_set_key(काष्ठा sctp_endpoपूर्णांक *ep,
		      काष्ठा sctp_association *asoc,
		      काष्ठा sctp_authkey *auth_key)
अणु
	काष्ठा sctp_shared_key *cur_key, *shkey;
	काष्ठा sctp_auth_bytes *key;
	काष्ठा list_head *sh_keys;
	पूर्णांक replace = 0;

	/* Try to find the given key id to see अगर
	 * we are करोing a replace, or adding a new key
	 */
	अगर (asoc) अणु
		अगर (!asoc->peer.auth_capable)
			वापस -EACCES;
		sh_keys = &asoc->endpoपूर्णांक_shared_keys;
	पूर्ण अन्यथा अणु
		अगर (!ep->auth_enable)
			वापस -EACCES;
		sh_keys = &ep->endpoपूर्णांक_shared_keys;
	पूर्ण

	key_क्रम_each(shkey, sh_keys) अणु
		अगर (shkey->key_id == auth_key->sca_keynumber) अणु
			replace = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	cur_key = sctp_auth_shkey_create(auth_key->sca_keynumber, GFP_KERNEL);
	अगर (!cur_key)
		वापस -ENOMEM;

	/* Create a new key data based on the info passed in */
	key = sctp_auth_create_key(auth_key->sca_keylength, GFP_KERNEL);
	अगर (!key) अणु
		kमुक्त(cur_key);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(key->data, &auth_key->sca_key[0], auth_key->sca_keylength);
	cur_key->key = key;

	अगर (replace) अणु
		list_del_init(&shkey->key_list);
		sctp_auth_shkey_release(shkey);
	पूर्ण
	list_add(&cur_key->key_list, sh_keys);

	वापस 0;
पूर्ण

पूर्णांक sctp_auth_set_active_key(काष्ठा sctp_endpoपूर्णांक *ep,
			     काष्ठा sctp_association *asoc,
			     __u16  key_id)
अणु
	काष्ठा sctp_shared_key *key;
	काष्ठा list_head *sh_keys;
	पूर्णांक found = 0;

	/* The key identअगरier MUST correst to an existing key */
	अगर (asoc) अणु
		अगर (!asoc->peer.auth_capable)
			वापस -EACCES;
		sh_keys = &asoc->endpoपूर्णांक_shared_keys;
	पूर्ण अन्यथा अणु
		अगर (!ep->auth_enable)
			वापस -EACCES;
		sh_keys = &ep->endpoपूर्णांक_shared_keys;
	पूर्ण

	key_क्रम_each(key, sh_keys) अणु
		अगर (key->key_id == key_id) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found || key->deactivated)
		वापस -EINVAL;

	अगर (asoc) अणु
		asoc->active_key_id = key_id;
		sctp_auth_asoc_init_active_key(asoc, GFP_KERNEL);
	पूर्ण अन्यथा
		ep->active_key_id = key_id;

	वापस 0;
पूर्ण

पूर्णांक sctp_auth_del_key_id(काष्ठा sctp_endpoपूर्णांक *ep,
			 काष्ठा sctp_association *asoc,
			 __u16  key_id)
अणु
	काष्ठा sctp_shared_key *key;
	काष्ठा list_head *sh_keys;
	पूर्णांक found = 0;

	/* The key identअगरier MUST NOT be the current active key
	 * The key identअगरier MUST correst to an existing key
	 */
	अगर (asoc) अणु
		अगर (!asoc->peer.auth_capable)
			वापस -EACCES;
		अगर (asoc->active_key_id == key_id)
			वापस -EINVAL;

		sh_keys = &asoc->endpoपूर्णांक_shared_keys;
	पूर्ण अन्यथा अणु
		अगर (!ep->auth_enable)
			वापस -EACCES;
		अगर (ep->active_key_id == key_id)
			वापस -EINVAL;

		sh_keys = &ep->endpoपूर्णांक_shared_keys;
	पूर्ण

	key_क्रम_each(key, sh_keys) अणु
		अगर (key->key_id == key_id) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस -EINVAL;

	/* Delete the shared key */
	list_del_init(&key->key_list);
	sctp_auth_shkey_release(key);

	वापस 0;
पूर्ण

पूर्णांक sctp_auth_deact_key_id(काष्ठा sctp_endpoपूर्णांक *ep,
			   काष्ठा sctp_association *asoc, __u16  key_id)
अणु
	काष्ठा sctp_shared_key *key;
	काष्ठा list_head *sh_keys;
	पूर्णांक found = 0;

	/* The key identअगरier MUST NOT be the current active key
	 * The key identअगरier MUST correst to an existing key
	 */
	अगर (asoc) अणु
		अगर (!asoc->peer.auth_capable)
			वापस -EACCES;
		अगर (asoc->active_key_id == key_id)
			वापस -EINVAL;

		sh_keys = &asoc->endpoपूर्णांक_shared_keys;
	पूर्ण अन्यथा अणु
		अगर (!ep->auth_enable)
			वापस -EACCES;
		अगर (ep->active_key_id == key_id)
			वापस -EINVAL;

		sh_keys = &ep->endpoपूर्णांक_shared_keys;
	पूर्ण

	key_क्रम_each(key, sh_keys) अणु
		अगर (key->key_id == key_id) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस -EINVAL;

	/* refcnt == 1 and !list_empty mean it's not being used anywhere
	 * and deactivated will be set, so it's समय to notअगरy userland
	 * that this shkey can be मुक्तd.
	 */
	अगर (asoc && !list_empty(&key->key_list) &&
	    refcount_पढ़ो(&key->refcnt) == 1) अणु
		काष्ठा sctp_ulpevent *ev;

		ev = sctp_ulpevent_make_authkey(asoc, key->key_id,
						SCTP_AUTH_FREE_KEY, GFP_KERNEL);
		अगर (ev)
			asoc->stream.si->enqueue_event(&asoc->ulpq, ev);
	पूर्ण

	key->deactivated = 1;

	वापस 0;
पूर्ण

पूर्णांक sctp_auth_init(काष्ठा sctp_endpoपूर्णांक *ep, gfp_t gfp)
अणु
	पूर्णांक err = -ENOMEM;

	/* Allocate space क्रम HMACS and CHUNKS authentication
	 * variables.  There are arrays that we encode directly
	 * पूर्णांकo parameters to make the rest of the operations easier.
	 */
	अगर (!ep->auth_hmacs_list) अणु
		काष्ठा sctp_hmac_algo_param *auth_hmacs;

		auth_hmacs = kzalloc(काष्ठा_size(auth_hmacs, hmac_ids,
						 SCTP_AUTH_NUM_HMACS), gfp);
		अगर (!auth_hmacs)
			जाओ nomem;
		/* Initialize the HMACS parameter.
		 * SCTP-AUTH: Section 3.3
		 *    Every endpoपूर्णांक supporting SCTP chunk authentication MUST
		 *    support the HMAC based on the SHA-1 algorithm.
		 */
		auth_hmacs->param_hdr.type = SCTP_PARAM_HMAC_ALGO;
		auth_hmacs->param_hdr.length =
				htons(माप(काष्ठा sctp_paramhdr) + 2);
		auth_hmacs->hmac_ids[0] = htons(SCTP_AUTH_HMAC_ID_SHA1);
		ep->auth_hmacs_list = auth_hmacs;
	पूर्ण

	अगर (!ep->auth_chunk_list) अणु
		काष्ठा sctp_chunks_param *auth_chunks;

		auth_chunks = kzalloc(माप(*auth_chunks) +
				      SCTP_NUM_CHUNK_TYPES, gfp);
		अगर (!auth_chunks)
			जाओ nomem;
		/* Initialize the CHUNKS parameter */
		auth_chunks->param_hdr.type = SCTP_PARAM_CHUNKS;
		auth_chunks->param_hdr.length =
				htons(माप(काष्ठा sctp_paramhdr));
		ep->auth_chunk_list = auth_chunks;
	पूर्ण

	/* Allocate and initialize transorms arrays क्रम supported
	 * HMACs.
	 */
	err = sctp_auth_init_hmacs(ep, gfp);
	अगर (err)
		जाओ nomem;

	वापस 0;

nomem:
	/* Free all allocations */
	kमुक्त(ep->auth_hmacs_list);
	kमुक्त(ep->auth_chunk_list);
	ep->auth_hmacs_list = शून्य;
	ep->auth_chunk_list = शून्य;
	वापस err;
पूर्ण

व्योम sctp_auth_मुक्त(काष्ठा sctp_endpoपूर्णांक *ep)
अणु
	kमुक्त(ep->auth_hmacs_list);
	kमुक्त(ep->auth_chunk_list);
	ep->auth_hmacs_list = शून्य;
	ep->auth_chunk_list = शून्य;
	sctp_auth_destroy_hmacs(ep->auth_hmacs);
	ep->auth_hmacs = शून्य;
पूर्ण
