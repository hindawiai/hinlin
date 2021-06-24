<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is part of UBIFS.
 *
 * Copyright (C) 2018 Pengutronix, Sascha Hauer <s.hauer@pengutronix.de>
 */

/*
 * This file implements various helper functions क्रम UBIFS authentication support
 */

#समावेश <linux/crypto.h>
#समावेश <linux/verअगरication.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/algapi.h>
#समावेश <keys/user-type.h>
#समावेश <keys/asymmetric-type.h>

#समावेश "ubifs.h"

/**
 * ubअगरs_node_calc_hash - calculate the hash of a UBIFS node
 * @c: UBIFS file-प्रणाली description object
 * @node: the node to calculate a hash क्रम
 * @hash: the वापसed hash
 *
 * Returns 0 क्रम success or a negative error code otherwise.
 */
पूर्णांक __ubअगरs_node_calc_hash(स्थिर काष्ठा ubअगरs_info *c, स्थिर व्योम *node,
			    u8 *hash)
अणु
	स्थिर काष्ठा ubअगरs_ch *ch = node;

	वापस crypto_shash_tfm_digest(c->hash_tfm, node, le32_to_cpu(ch->len),
				       hash);
पूर्ण

/**
 * ubअगरs_hash_calc_hmac - calculate a HMAC from a hash
 * @c: UBIFS file-प्रणाली description object
 * @hash: the node to calculate a HMAC क्रम
 * @hmac: the वापसed HMAC
 *
 * Returns 0 क्रम success or a negative error code otherwise.
 */
अटल पूर्णांक ubअगरs_hash_calc_hmac(स्थिर काष्ठा ubअगरs_info *c, स्थिर u8 *hash,
				 u8 *hmac)
अणु
	वापस crypto_shash_tfm_digest(c->hmac_tfm, hash, c->hash_len, hmac);
पूर्ण

/**
 * ubअगरs_prepare_auth_node - Prepare an authentication node
 * @c: UBIFS file-प्रणाली description object
 * @node: the node to calculate a hash क्रम
 * @inhash: input hash of previous nodes
 *
 * This function prepares an authentication node क्रम writing onto flash.
 * It creates a HMAC from the given input hash and ग_लिखोs it to the node.
 *
 * Returns 0 क्रम success or a negative error code otherwise.
 */
पूर्णांक ubअगरs_prepare_auth_node(काष्ठा ubअगरs_info *c, व्योम *node,
			     काष्ठा shash_desc *inhash)
अणु
	काष्ठा ubअगरs_auth_node *auth = node;
	u8 hash[UBIFS_HASH_ARR_SZ];
	पूर्णांक err;

	अणु
		SHASH_DESC_ON_STACK(hash_desc, c->hash_tfm);

		hash_desc->tfm = c->hash_tfm;
		ubअगरs_shash_copy_state(c, inhash, hash_desc);

		err = crypto_shash_final(hash_desc, hash);
		अगर (err)
			वापस err;
	पूर्ण

	err = ubअगरs_hash_calc_hmac(c, hash, auth->hmac);
	अगर (err)
		वापस err;

	auth->ch.node_type = UBIFS_AUTH_NODE;
	ubअगरs_prepare_node(c, auth, ubअगरs_auth_node_sz(c), 0);
	वापस 0;
पूर्ण

अटल काष्ठा shash_desc *ubअगरs_get_desc(स्थिर काष्ठा ubअगरs_info *c,
					 काष्ठा crypto_shash *tfm)
अणु
	काष्ठा shash_desc *desc;
	पूर्णांक err;

	अगर (!ubअगरs_authenticated(c))
		वापस शून्य;

	desc = kदो_स्मृति(माप(*desc) + crypto_shash_descsize(tfm), GFP_KERNEL);
	अगर (!desc)
		वापस ERR_PTR(-ENOMEM);

	desc->tfm = tfm;

	err = crypto_shash_init(desc);
	अगर (err) अणु
		kमुक्त(desc);
		वापस ERR_PTR(err);
	पूर्ण

	वापस desc;
पूर्ण

/**
 * __ubअगरs_hash_get_desc - get a descriptor suitable क्रम hashing a node
 * @c: UBIFS file-प्रणाली description object
 *
 * This function वापसs a descriptor suitable क्रम hashing a node. Free after use
 * with kमुक्त.
 */
काष्ठा shash_desc *__ubअगरs_hash_get_desc(स्थिर काष्ठा ubअगरs_info *c)
अणु
	वापस ubअगरs_get_desc(c, c->hash_tfm);
पूर्ण

/**
 * ubअगरs_bad_hash - Report hash mismatches
 * @c: UBIFS file-प्रणाली description object
 * @node: the node
 * @hash: the expected hash
 * @lnum: the LEB @node was पढ़ो from
 * @offs: offset in LEB @node was पढ़ो from
 *
 * This function reports a hash mismatch when a node has a dअगरferent hash than
 * expected.
 */
व्योम ubअगरs_bad_hash(स्थिर काष्ठा ubअगरs_info *c, स्थिर व्योम *node, स्थिर u8 *hash,
		    पूर्णांक lnum, पूर्णांक offs)
अणु
	पूर्णांक len = min(c->hash_len, 20);
	पूर्णांक cropped = len != c->hash_len;
	स्थिर अक्षर *cont = cropped ? "..." : "";

	u8 calc[UBIFS_HASH_ARR_SZ];

	__ubअगरs_node_calc_hash(c, node, calc);

	ubअगरs_err(c, "hash mismatch on node at LEB %d:%d", lnum, offs);
	ubअगरs_err(c, "hash expected:   %*ph%s", len, hash, cont);
	ubअगरs_err(c, "hash calculated: %*ph%s", len, calc, cont);
पूर्ण

/**
 * __ubअगरs_node_check_hash - check the hash of a node against given hash
 * @c: UBIFS file-प्रणाली description object
 * @node: the node
 * @expected: the expected hash
 *
 * This function calculates a hash over a node and compares it to the given hash.
 * Returns 0 अगर both hashes are equal or authentication is disabled, otherwise a
 * negative error code is वापसed.
 */
पूर्णांक __ubअगरs_node_check_hash(स्थिर काष्ठा ubअगरs_info *c, स्थिर व्योम *node,
			    स्थिर u8 *expected)
अणु
	u8 calc[UBIFS_HASH_ARR_SZ];
	पूर्णांक err;

	err = __ubअगरs_node_calc_hash(c, node, calc);
	अगर (err)
		वापस err;

	अगर (ubअगरs_check_hash(c, expected, calc))
		वापस -EPERM;

	वापस 0;
पूर्ण

/**
 * ubअगरs_sb_verअगरy_signature - verअगरy the signature of a superblock
 * @c: UBIFS file-प्रणाली description object
 * @sup: The superblock node
 *
 * To support offline चिन्हित images the superblock can be चिन्हित with a
 * PKCS#7 signature. The signature is placed directly behind the superblock
 * node in an ubअगरs_sig_node.
 *
 * Returns 0 when the signature can be successfully verअगरied or a negative
 * error code अगर not.
 */
पूर्णांक ubअगरs_sb_verअगरy_signature(काष्ठा ubअगरs_info *c,
			      स्थिर काष्ठा ubअगरs_sb_node *sup)
अणु
	पूर्णांक err;
	काष्ठा ubअगरs_scan_leb *sleb;
	काष्ठा ubअगरs_scan_node *snod;
	स्थिर काष्ठा ubअगरs_sig_node *signode;

	sleb = ubअगरs_scan(c, UBIFS_SB_LNUM, UBIFS_SB_NODE_SZ, c->sbuf, 0);
	अगर (IS_ERR(sleb)) अणु
		err = PTR_ERR(sleb);
		वापस err;
	पूर्ण

	अगर (sleb->nodes_cnt == 0) अणु
		ubअगरs_err(c, "Unable to find signature node");
		err = -EINVAL;
		जाओ out_destroy;
	पूर्ण

	snod = list_first_entry(&sleb->nodes, काष्ठा ubअगरs_scan_node, list);

	अगर (snod->type != UBIFS_SIG_NODE) अणु
		ubअगरs_err(c, "Signature node is of wrong type");
		err = -EINVAL;
		जाओ out_destroy;
	पूर्ण

	signode = snod->node;

	अगर (le32_to_cpu(signode->len) > snod->len + माप(काष्ठा ubअगरs_sig_node)) अणु
		ubअगरs_err(c, "invalid signature len %d", le32_to_cpu(signode->len));
		err = -EINVAL;
		जाओ out_destroy;
	पूर्ण

	अगर (le32_to_cpu(signode->type) != UBIFS_SIGNATURE_TYPE_PKCS7) अणु
		ubअगरs_err(c, "Signature type %d is not supported\n",
			  le32_to_cpu(signode->type));
		err = -EINVAL;
		जाओ out_destroy;
	पूर्ण

	err = verअगरy_pkcs7_signature(sup, माप(काष्ठा ubअगरs_sb_node),
				     signode->sig, le32_to_cpu(signode->len),
				     शून्य, VERIFYING_UNSPECIFIED_SIGNATURE,
				     शून्य, शून्य);

	अगर (err)
		ubअगरs_err(c, "Failed to verify signature");
	अन्यथा
		ubअगरs_msg(c, "Successfully verified super block signature");

out_destroy:
	ubअगरs_scan_destroy(sleb);

	वापस err;
पूर्ण

/**
 * ubअगरs_init_authentication - initialize UBIFS authentication support
 * @c: UBIFS file-प्रणाली description object
 *
 * This function वापसs 0 क्रम success or a negative error code otherwise.
 */
पूर्णांक ubअगरs_init_authentication(काष्ठा ubअगरs_info *c)
अणु
	काष्ठा key *keyring_key;
	स्थिर काष्ठा user_key_payload *ukp;
	पूर्णांक err;
	अक्षर hmac_name[CRYPTO_MAX_ALG_NAME];

	अगर (!c->auth_hash_name) अणु
		ubअगरs_err(c, "authentication hash name needed with authentication");
		वापस -EINVAL;
	पूर्ण

	c->auth_hash_algo = match_string(hash_algo_name, HASH_ALGO__LAST,
					 c->auth_hash_name);
	अगर ((पूर्णांक)c->auth_hash_algo < 0) अणु
		ubअगरs_err(c, "Unknown hash algo %s specified",
			  c->auth_hash_name);
		वापस -EINVAL;
	पूर्ण

	snम_लिखो(hmac_name, CRYPTO_MAX_ALG_NAME, "hmac(%s)",
		 c->auth_hash_name);

	keyring_key = request_key(&key_type_logon, c->auth_key_name, शून्य);

	अगर (IS_ERR(keyring_key)) अणु
		ubअगरs_err(c, "Failed to request key: %ld",
			  PTR_ERR(keyring_key));
		वापस PTR_ERR(keyring_key);
	पूर्ण

	करोwn_पढ़ो(&keyring_key->sem);

	अगर (keyring_key->type != &key_type_logon) अणु
		ubअगरs_err(c, "key type must be logon");
		err = -ENOKEY;
		जाओ out;
	पूर्ण

	ukp = user_key_payload_locked(keyring_key);
	अगर (!ukp) अणु
		/* key was revoked beक्रमe we acquired its semaphore */
		err = -EKEYREVOKED;
		जाओ out;
	पूर्ण

	c->hash_tfm = crypto_alloc_shash(c->auth_hash_name, 0, 0);
	अगर (IS_ERR(c->hash_tfm)) अणु
		err = PTR_ERR(c->hash_tfm);
		ubअगरs_err(c, "Can not allocate %s: %d",
			  c->auth_hash_name, err);
		जाओ out;
	पूर्ण

	c->hash_len = crypto_shash_digestsize(c->hash_tfm);
	अगर (c->hash_len > UBIFS_HASH_ARR_SZ) अणु
		ubअगरs_err(c, "hash %s is bigger than maximum allowed hash size (%d > %d)",
			  c->auth_hash_name, c->hash_len, UBIFS_HASH_ARR_SZ);
		err = -EINVAL;
		जाओ out_मुक्त_hash;
	पूर्ण

	c->hmac_tfm = crypto_alloc_shash(hmac_name, 0, 0);
	अगर (IS_ERR(c->hmac_tfm)) अणु
		err = PTR_ERR(c->hmac_tfm);
		ubअगरs_err(c, "Can not allocate %s: %d", hmac_name, err);
		जाओ out_मुक्त_hash;
	पूर्ण

	c->hmac_desc_len = crypto_shash_digestsize(c->hmac_tfm);
	अगर (c->hmac_desc_len > UBIFS_HMAC_ARR_SZ) अणु
		ubअगरs_err(c, "hmac %s is bigger than maximum allowed hmac size (%d > %d)",
			  hmac_name, c->hmac_desc_len, UBIFS_HMAC_ARR_SZ);
		err = -EINVAL;
		जाओ out_मुक्त_hmac;
	पूर्ण

	err = crypto_shash_setkey(c->hmac_tfm, ukp->data, ukp->datalen);
	अगर (err)
		जाओ out_मुक्त_hmac;

	c->authenticated = true;

	c->log_hash = ubअगरs_hash_get_desc(c);
	अगर (IS_ERR(c->log_hash)) अणु
		err = PTR_ERR(c->log_hash);
		जाओ out_मुक्त_hmac;
	पूर्ण

	err = 0;

out_मुक्त_hmac:
	अगर (err)
		crypto_मुक्त_shash(c->hmac_tfm);
out_मुक्त_hash:
	अगर (err)
		crypto_मुक्त_shash(c->hash_tfm);
out:
	up_पढ़ो(&keyring_key->sem);
	key_put(keyring_key);

	वापस err;
पूर्ण

/**
 * __ubअगरs_निकास_authentication - release resource
 * @c: UBIFS file-प्रणाली description object
 *
 * This function releases the authentication related resources.
 */
व्योम __ubअगरs_निकास_authentication(काष्ठा ubअगरs_info *c)
अणु
	अगर (!ubअगरs_authenticated(c))
		वापस;

	crypto_मुक्त_shash(c->hmac_tfm);
	crypto_मुक्त_shash(c->hash_tfm);
	kमुक्त(c->log_hash);
पूर्ण

/**
 * ubअगरs_node_calc_hmac - calculate the HMAC of a UBIFS node
 * @c: UBIFS file-प्रणाली description object
 * @node: the node to insert a HMAC पूर्णांकo.
 * @len: the length of the node
 * @ofs_hmac: the offset in the node where the HMAC is inserted
 * @hmac: वापसed HMAC
 *
 * This function calculates a HMAC of a UBIFS node. The HMAC is expected to be
 * embedded पूर्णांकo the node, so this area is not covered by the HMAC. Also not
 * covered is the UBIFS_NODE_MAGIC and the CRC of the node.
 */
अटल पूर्णांक ubअगरs_node_calc_hmac(स्थिर काष्ठा ubअगरs_info *c, स्थिर व्योम *node,
				पूर्णांक len, पूर्णांक ofs_hmac, व्योम *hmac)
अणु
	SHASH_DESC_ON_STACK(shash, c->hmac_tfm);
	पूर्णांक hmac_len = c->hmac_desc_len;
	पूर्णांक err;

	ubअगरs_निश्चित(c, ofs_hmac > 8);
	ubअगरs_निश्चित(c, ofs_hmac + hmac_len < len);

	shash->tfm = c->hmac_tfm;

	err = crypto_shash_init(shash);
	अगर (err)
		वापस err;

	/* behind common node header CRC up to HMAC begin */
	err = crypto_shash_update(shash, node + 8, ofs_hmac - 8);
	अगर (err < 0)
		वापस err;

	/* behind HMAC, अगर any */
	अगर (len - ofs_hmac - hmac_len > 0) अणु
		err = crypto_shash_update(shash, node + ofs_hmac + hmac_len,
			    len - ofs_hmac - hmac_len);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस crypto_shash_final(shash, hmac);
पूर्ण

/**
 * __ubअगरs_node_insert_hmac - insert a HMAC पूर्णांकo a UBIFS node
 * @c: UBIFS file-प्रणाली description object
 * @node: the node to insert a HMAC पूर्णांकo.
 * @len: the length of the node
 * @ofs_hmac: the offset in the node where the HMAC is inserted
 *
 * This function inserts a HMAC at offset @ofs_hmac पूर्णांकo the node given in
 * @node.
 *
 * This function वापसs 0 क्रम success or a negative error code otherwise.
 */
पूर्णांक __ubअगरs_node_insert_hmac(स्थिर काष्ठा ubअगरs_info *c, व्योम *node, पूर्णांक len,
			    पूर्णांक ofs_hmac)
अणु
	वापस ubअगरs_node_calc_hmac(c, node, len, ofs_hmac, node + ofs_hmac);
पूर्ण

/**
 * __ubअगरs_node_verअगरy_hmac - verअगरy the HMAC of UBIFS node
 * @c: UBIFS file-प्रणाली description object
 * @node: the node to insert a HMAC पूर्णांकo.
 * @len: the length of the node
 * @ofs_hmac: the offset in the node where the HMAC is inserted
 *
 * This function verअगरies the HMAC at offset @ofs_hmac of the node given in
 * @node. Returns 0 अगर successful or a negative error code otherwise.
 */
पूर्णांक __ubअगरs_node_verअगरy_hmac(स्थिर काष्ठा ubअगरs_info *c, स्थिर व्योम *node,
			     पूर्णांक len, पूर्णांक ofs_hmac)
अणु
	पूर्णांक hmac_len = c->hmac_desc_len;
	u8 *hmac;
	पूर्णांक err;

	hmac = kदो_स्मृति(hmac_len, GFP_NOFS);
	अगर (!hmac)
		वापस -ENOMEM;

	err = ubअगरs_node_calc_hmac(c, node, len, ofs_hmac, hmac);
	अगर (err) अणु
		kमुक्त(hmac);
		वापस err;
	पूर्ण

	err = crypto_memneq(hmac, node + ofs_hmac, hmac_len);

	kमुक्त(hmac);

	अगर (!err)
		वापस 0;

	वापस -EPERM;
पूर्ण

पूर्णांक __ubअगरs_shash_copy_state(स्थिर काष्ठा ubअगरs_info *c, काष्ठा shash_desc *src,
			     काष्ठा shash_desc *target)
अणु
	u8 *state;
	पूर्णांक err;

	state = kदो_स्मृति(crypto_shash_descsize(src->tfm), GFP_NOFS);
	अगर (!state)
		वापस -ENOMEM;

	err = crypto_shash_export(src, state);
	अगर (err)
		जाओ out;

	err = crypto_shash_import(target, state);

out:
	kमुक्त(state);

	वापस err;
पूर्ण

/**
 * ubअगरs_hmac_wkm - Create a HMAC of the well known message
 * @c: UBIFS file-प्रणाली description object
 * @hmac: The HMAC of the well known message
 *
 * This function creates a HMAC of a well known message. This is used
 * to check अगर the provided key is suitable to authenticate a UBIFS
 * image. This is only a convenience to the user to provide a better
 * error message when the wrong key is provided.
 *
 * This function वापसs 0 क्रम success or a negative error code otherwise.
 */
पूर्णांक ubअगरs_hmac_wkm(काष्ठा ubअगरs_info *c, u8 *hmac)
अणु
	SHASH_DESC_ON_STACK(shash, c->hmac_tfm);
	पूर्णांक err;
	स्थिर अक्षर well_known_message[] = "UBIFS";

	अगर (!ubअगरs_authenticated(c))
		वापस 0;

	shash->tfm = c->hmac_tfm;

	err = crypto_shash_init(shash);
	अगर (err)
		वापस err;

	err = crypto_shash_update(shash, well_known_message,
				  माप(well_known_message) - 1);
	अगर (err < 0)
		वापस err;

	err = crypto_shash_final(shash, hmac);
	अगर (err)
		वापस err;
	वापस 0;
पूर्ण

/*
 * ubअगरs_hmac_zero - test अगर a HMAC is zero
 * @c: UBIFS file-प्रणाली description object
 * @hmac: the HMAC to test
 *
 * This function tests अगर a HMAC is zero and वापसs true अगर it is
 * and false otherwise.
 */
bool ubअगरs_hmac_zero(काष्ठा ubअगरs_info *c, स्थिर u8 *hmac)
अणु
	वापस !स_प्रथम_inv(hmac, 0, c->hmac_desc_len);
पूर्ण
