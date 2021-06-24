<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file houses the मुख्य functions क्रम the iSCSI CHAP support
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <crypto/hash.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/err.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/scatterlist.h>
#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_nego.h"
#समावेश "iscsi_target_auth.h"

अटल अक्षर *chap_get_digest_name(स्थिर पूर्णांक digest_type)
अणु
	चयन (digest_type) अणु
	हाल CHAP_DIGEST_MD5:
		वापस "md5";
	हाल CHAP_DIGEST_SHA1:
		वापस "sha1";
	हाल CHAP_DIGEST_SHA256:
		वापस "sha256";
	हाल CHAP_DIGEST_SHA3_256:
		वापस "sha3-256";
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक chap_gen_challenge(
	काष्ठा iscsi_conn *conn,
	पूर्णांक caller,
	अक्षर *c_str,
	अचिन्हित पूर्णांक *c_len)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर *challenge_asciihex;
	काष्ठा iscsi_chap *chap = conn->auth_protocol;

	challenge_asciihex = kzalloc(chap->challenge_len * 2 + 1, GFP_KERNEL);
	अगर (!challenge_asciihex)
		वापस -ENOMEM;

	स_रखो(chap->challenge, 0, MAX_CHAP_CHALLENGE_LEN);

	ret = get_अक्रमom_bytes_रुको(chap->challenge, chap->challenge_len);
	अगर (unlikely(ret))
		जाओ out;

	bin2hex(challenge_asciihex, chap->challenge,
				chap->challenge_len);
	/*
	 * Set CHAP_C, and copy the generated challenge पूर्णांकo c_str.
	 */
	*c_len += प्र_लिखो(c_str + *c_len, "CHAP_C=0x%s", challenge_asciihex);
	*c_len += 1;

	pr_debug("[%s] Sending CHAP_C=0x%s\n\n", (caller) ? "server" : "client",
			challenge_asciihex);

out:
	kमुक्त(challenge_asciihex);
	वापस ret;
पूर्ण

अटल पूर्णांक chap_test_algorithm(स्थिर अक्षर *name)
अणु
	काष्ठा crypto_shash *tfm;

	tfm = crypto_alloc_shash(name, 0, 0);
	अगर (IS_ERR(tfm))
		वापस -1;

	crypto_मुक्त_shash(tfm);
	वापस 0;
पूर्ण

अटल पूर्णांक chap_check_algorithm(स्थिर अक्षर *a_str)
अणु
	अक्षर *पंचांगp, *orig, *token, *digest_name;
	दीर्घ digest_type;
	पूर्णांक r = CHAP_DIGEST_UNKNOWN;

	पंचांगp = kstrdup(a_str, GFP_KERNEL);
	अगर (!पंचांगp) अणु
		pr_err("Memory allocation failed for CHAP_A temporary buffer\n");
		वापस CHAP_DIGEST_UNKNOWN;
	पूर्ण
	orig = पंचांगp;

	token = strsep(&पंचांगp, "=");
	अगर (!token)
		जाओ out;

	अगर (म_भेद(token, "CHAP_A")) अणु
		pr_err("Unable to locate CHAP_A key\n");
		जाओ out;
	पूर्ण
	जबतक (token) अणु
		token = strsep(&पंचांगp, ",");
		अगर (!token)
			जाओ out;

		अगर (kम_से_दीर्घ(token, 10, &digest_type))
			जारी;

		digest_name = chap_get_digest_name(digest_type);
		अगर (!digest_name)
			जारी;

		pr_debug("Selected %s Algorithm\n", digest_name);
		अगर (chap_test_algorithm(digest_name) < 0) अणु
			pr_err("failed to allocate %s algo\n", digest_name);
		पूर्ण अन्यथा अणु
			r = digest_type;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	kमुक्त(orig);
	वापस r;
पूर्ण

अटल व्योम chap_बंद(काष्ठा iscsi_conn *conn)
अणु
	kमुक्त(conn->auth_protocol);
	conn->auth_protocol = शून्य;
पूर्ण

अटल काष्ठा iscsi_chap *chap_server_खोलो(
	काष्ठा iscsi_conn *conn,
	काष्ठा iscsi_node_auth *auth,
	स्थिर अक्षर *a_str,
	अक्षर *aic_str,
	अचिन्हित पूर्णांक *aic_len)
अणु
	पूर्णांक digest_type;
	काष्ठा iscsi_chap *chap;

	अगर (!(auth->naf_flags & NAF_USERID_SET) ||
	    !(auth->naf_flags & NAF_PASSWORD_SET)) अणु
		pr_err("CHAP user or password not set for"
				" Initiator ACL\n");
		वापस शून्य;
	पूर्ण

	conn->auth_protocol = kzalloc(माप(काष्ठा iscsi_chap), GFP_KERNEL);
	अगर (!conn->auth_protocol)
		वापस शून्य;

	chap = conn->auth_protocol;
	digest_type = chap_check_algorithm(a_str);
	चयन (digest_type) अणु
	हाल CHAP_DIGEST_MD5:
		chap->digest_size = MD5_SIGNATURE_SIZE;
		अवरोध;
	हाल CHAP_DIGEST_SHA1:
		chap->digest_size = SHA1_SIGNATURE_SIZE;
		अवरोध;
	हाल CHAP_DIGEST_SHA256:
		chap->digest_size = SHA256_SIGNATURE_SIZE;
		अवरोध;
	हाल CHAP_DIGEST_SHA3_256:
		chap->digest_size = SHA3_256_SIGNATURE_SIZE;
		अवरोध;
	हाल CHAP_DIGEST_UNKNOWN:
	शेष:
		pr_err("Unsupported CHAP_A value\n");
		chap_बंद(conn);
		वापस शून्य;
	पूर्ण

	chap->digest_name = chap_get_digest_name(digest_type);

	/* Tie the challenge length to the digest size */
	chap->challenge_len = chap->digest_size;

	pr_debug("[server] Got CHAP_A=%d\n", digest_type);
	*aic_len = प्र_लिखो(aic_str, "CHAP_A=%d", digest_type);
	*aic_len += 1;
	pr_debug("[server] Sending CHAP_A=%d\n", digest_type);

	/*
	 * Set Identअगरier.
	 */
	chap->id = conn->tpg->tpg_chap_id++;
	*aic_len += प्र_लिखो(aic_str + *aic_len, "CHAP_I=%d", chap->id);
	*aic_len += 1;
	pr_debug("[server] Sending CHAP_I=%d\n", chap->id);
	/*
	 * Generate Challenge.
	 */
	अगर (chap_gen_challenge(conn, 1, aic_str, aic_len) < 0) अणु
		chap_बंद(conn);
		वापस शून्य;
	पूर्ण

	वापस chap;
पूर्ण

अटल पूर्णांक chap_server_compute_hash(
	काष्ठा iscsi_conn *conn,
	काष्ठा iscsi_node_auth *auth,
	अक्षर *nr_in_ptr,
	अक्षर *nr_out_ptr,
	अचिन्हित पूर्णांक *nr_out_len)
अणु
	अचिन्हित दीर्घ id;
	अचिन्हित अक्षर id_as_uअक्षर;
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर identअगरier[10], *initiatorchg = शून्य;
	अचिन्हित अक्षर *initiatorchg_binhex = शून्य;
	अचिन्हित अक्षर *digest = शून्य;
	अचिन्हित अक्षर *response = शून्य;
	अचिन्हित अक्षर *client_digest = शून्य;
	अचिन्हित अक्षर *server_digest = शून्य;
	अचिन्हित अक्षर chap_n[MAX_CHAP_N_SIZE], chap_r[MAX_RESPONSE_LENGTH];
	माप_प्रकार compare_len;
	काष्ठा iscsi_chap *chap = conn->auth_protocol;
	काष्ठा crypto_shash *tfm = शून्य;
	काष्ठा shash_desc *desc = शून्य;
	पूर्णांक auth_ret = -1, ret, initiatorchg_len;

	digest = kzalloc(chap->digest_size, GFP_KERNEL);
	अगर (!digest) अणु
		pr_err("Unable to allocate the digest buffer\n");
		जाओ out;
	पूर्ण

	response = kzalloc(chap->digest_size * 2 + 2, GFP_KERNEL);
	अगर (!response) अणु
		pr_err("Unable to allocate the response buffer\n");
		जाओ out;
	पूर्ण

	client_digest = kzalloc(chap->digest_size, GFP_KERNEL);
	अगर (!client_digest) अणु
		pr_err("Unable to allocate the client_digest buffer\n");
		जाओ out;
	पूर्ण

	server_digest = kzalloc(chap->digest_size, GFP_KERNEL);
	अगर (!server_digest) अणु
		pr_err("Unable to allocate the server_digest buffer\n");
		जाओ out;
	पूर्ण

	स_रखो(identअगरier, 0, 10);
	स_रखो(chap_n, 0, MAX_CHAP_N_SIZE);
	स_रखो(chap_r, 0, MAX_RESPONSE_LENGTH);

	initiatorchg = kzalloc(CHAP_CHALLENGE_STR_LEN, GFP_KERNEL);
	अगर (!initiatorchg) अणु
		pr_err("Unable to allocate challenge buffer\n");
		जाओ out;
	पूर्ण

	initiatorchg_binhex = kzalloc(CHAP_CHALLENGE_STR_LEN, GFP_KERNEL);
	अगर (!initiatorchg_binhex) अणु
		pr_err("Unable to allocate initiatorchg_binhex buffer\n");
		जाओ out;
	पूर्ण
	/*
	 * Extract CHAP_N.
	 */
	अगर (extract_param(nr_in_ptr, "CHAP_N", MAX_CHAP_N_SIZE, chap_n,
				&type) < 0) अणु
		pr_err("Could not find CHAP_N.\n");
		जाओ out;
	पूर्ण
	अगर (type == HEX) अणु
		pr_err("Could not find CHAP_N.\n");
		जाओ out;
	पूर्ण

	/* Include the terminating शून्य in the compare */
	compare_len = म_माप(auth->userid) + 1;
	अगर (म_भेदन(chap_n, auth->userid, compare_len) != 0) अणु
		pr_err("CHAP_N values do not match!\n");
		जाओ out;
	पूर्ण
	pr_debug("[server] Got CHAP_N=%s\n", chap_n);
	/*
	 * Extract CHAP_R.
	 */
	अगर (extract_param(nr_in_ptr, "CHAP_R", MAX_RESPONSE_LENGTH, chap_r,
				&type) < 0) अणु
		pr_err("Could not find CHAP_R.\n");
		जाओ out;
	पूर्ण
	अगर (type != HEX) अणु
		pr_err("Could not find CHAP_R.\n");
		जाओ out;
	पूर्ण
	अगर (म_माप(chap_r) != chap->digest_size * 2) अणु
		pr_err("Malformed CHAP_R\n");
		जाओ out;
	पूर्ण
	अगर (hex2bin(client_digest, chap_r, chap->digest_size) < 0) अणु
		pr_err("Malformed CHAP_R\n");
		जाओ out;
	पूर्ण

	pr_debug("[server] Got CHAP_R=%s\n", chap_r);

	tfm = crypto_alloc_shash(chap->digest_name, 0, 0);
	अगर (IS_ERR(tfm)) अणु
		tfm = शून्य;
		pr_err("Unable to allocate struct crypto_shash\n");
		जाओ out;
	पूर्ण

	desc = kदो_स्मृति(माप(*desc) + crypto_shash_descsize(tfm), GFP_KERNEL);
	अगर (!desc) अणु
		pr_err("Unable to allocate struct shash_desc\n");
		जाओ out;
	पूर्ण

	desc->tfm = tfm;

	ret = crypto_shash_init(desc);
	अगर (ret < 0) अणु
		pr_err("crypto_shash_init() failed\n");
		जाओ out;
	पूर्ण

	ret = crypto_shash_update(desc, &chap->id, 1);
	अगर (ret < 0) अणु
		pr_err("crypto_shash_update() failed for id\n");
		जाओ out;
	पूर्ण

	ret = crypto_shash_update(desc, (अक्षर *)&auth->password,
				  म_माप(auth->password));
	अगर (ret < 0) अणु
		pr_err("crypto_shash_update() failed for password\n");
		जाओ out;
	पूर्ण

	ret = crypto_shash_finup(desc, chap->challenge,
				 chap->challenge_len, server_digest);
	अगर (ret < 0) अणु
		pr_err("crypto_shash_finup() failed for challenge\n");
		जाओ out;
	पूर्ण

	bin2hex(response, server_digest, chap->digest_size);
	pr_debug("[server] %s Server Digest: %s\n",
		chap->digest_name, response);

	अगर (स_भेद(server_digest, client_digest, chap->digest_size) != 0) अणु
		pr_debug("[server] %s Digests do not match!\n\n",
			chap->digest_name);
		जाओ out;
	पूर्ण अन्यथा
		pr_debug("[server] %s Digests match, CHAP connection"
				" successful.\n\n", chap->digest_name);
	/*
	 * One way authentication has succeeded, वापस now अगर mutual
	 * authentication is not enabled.
	 */
	अगर (!auth->authenticate_target) अणु
		auth_ret = 0;
		जाओ out;
	पूर्ण
	/*
	 * Get CHAP_I.
	 */
	अगर (extract_param(nr_in_ptr, "CHAP_I", 10, identअगरier, &type) < 0) अणु
		pr_err("Could not find CHAP_I.\n");
		जाओ out;
	पूर्ण

	अगर (type == HEX)
		ret = kम_से_अदीर्घ(&identअगरier[2], 0, &id);
	अन्यथा
		ret = kम_से_अदीर्घ(identअगरier, 0, &id);

	अगर (ret < 0) अणु
		pr_err("kstrtoul() failed for CHAP identifier: %d\n", ret);
		जाओ out;
	पूर्ण
	अगर (id > 255) अणु
		pr_err("chap identifier: %lu greater than 255\n", id);
		जाओ out;
	पूर्ण
	/*
	 * RFC 1994 says Identअगरier is no more than octet (8 bits).
	 */
	pr_debug("[server] Got CHAP_I=%lu\n", id);
	/*
	 * Get CHAP_C.
	 */
	अगर (extract_param(nr_in_ptr, "CHAP_C", CHAP_CHALLENGE_STR_LEN,
			initiatorchg, &type) < 0) अणु
		pr_err("Could not find CHAP_C.\n");
		जाओ out;
	पूर्ण

	अगर (type != HEX) अणु
		pr_err("Could not find CHAP_C.\n");
		जाओ out;
	पूर्ण
	initiatorchg_len = DIV_ROUND_UP(म_माप(initiatorchg), 2);
	अगर (!initiatorchg_len) अणु
		pr_err("Unable to convert incoming challenge\n");
		जाओ out;
	पूर्ण
	अगर (initiatorchg_len > 1024) अणु
		pr_err("CHAP_C exceeds maximum binary size of 1024 bytes\n");
		जाओ out;
	पूर्ण
	अगर (hex2bin(initiatorchg_binhex, initiatorchg, initiatorchg_len) < 0) अणु
		pr_err("Malformed CHAP_C\n");
		जाओ out;
	पूर्ण
	pr_debug("[server] Got CHAP_C=%s\n", initiatorchg);
	/*
	 * During mutual authentication, the CHAP_C generated by the
	 * initiator must not match the original CHAP_C generated by
	 * the target.
	 */
	अगर (initiatorchg_len == chap->challenge_len &&
				!स_भेद(initiatorchg_binhex, chap->challenge,
				initiatorchg_len)) अणु
		pr_err("initiator CHAP_C matches target CHAP_C, failing"
		       " login attempt\n");
		जाओ out;
	पूर्ण
	/*
	 * Generate CHAP_N and CHAP_R क्रम mutual authentication.
	 */
	ret = crypto_shash_init(desc);
	अगर (ret < 0) अणु
		pr_err("crypto_shash_init() failed\n");
		जाओ out;
	पूर्ण

	/* To handle both endiannesses */
	id_as_uअक्षर = id;
	ret = crypto_shash_update(desc, &id_as_uअक्षर, 1);
	अगर (ret < 0) अणु
		pr_err("crypto_shash_update() failed for id\n");
		जाओ out;
	पूर्ण

	ret = crypto_shash_update(desc, auth->password_mutual,
				  म_माप(auth->password_mutual));
	अगर (ret < 0) अणु
		pr_err("crypto_shash_update() failed for"
				" password_mutual\n");
		जाओ out;
	पूर्ण
	/*
	 * Convert received challenge to binary hex.
	 */
	ret = crypto_shash_finup(desc, initiatorchg_binhex, initiatorchg_len,
				 digest);
	अगर (ret < 0) अणु
		pr_err("crypto_shash_finup() failed for ma challenge\n");
		जाओ out;
	पूर्ण

	/*
	 * Generate CHAP_N and CHAP_R.
	 */
	*nr_out_len = प्र_लिखो(nr_out_ptr, "CHAP_N=%s", auth->userid_mutual);
	*nr_out_len += 1;
	pr_debug("[server] Sending CHAP_N=%s\n", auth->userid_mutual);
	/*
	 * Convert response from binary hex to ascii hext.
	 */
	bin2hex(response, digest, chap->digest_size);
	*nr_out_len += प्र_लिखो(nr_out_ptr + *nr_out_len, "CHAP_R=0x%s",
			response);
	*nr_out_len += 1;
	pr_debug("[server] Sending CHAP_R=0x%s\n", response);
	auth_ret = 0;
out:
	kमुक्त_sensitive(desc);
	अगर (tfm)
		crypto_मुक्त_shash(tfm);
	kमुक्त(initiatorchg);
	kमुक्त(initiatorchg_binhex);
	kमुक्त(digest);
	kमुक्त(response);
	kमुक्त(server_digest);
	kमुक्त(client_digest);
	वापस auth_ret;
पूर्ण

u32 chap_मुख्य_loop(
	काष्ठा iscsi_conn *conn,
	काष्ठा iscsi_node_auth *auth,
	अक्षर *in_text,
	अक्षर *out_text,
	पूर्णांक *in_len,
	पूर्णांक *out_len)
अणु
	काष्ठा iscsi_chap *chap = conn->auth_protocol;

	अगर (!chap) अणु
		chap = chap_server_खोलो(conn, auth, in_text, out_text, out_len);
		अगर (!chap)
			वापस 2;
		chap->chap_state = CHAP_STAGE_SERVER_AIC;
		वापस 0;
	पूर्ण अन्यथा अगर (chap->chap_state == CHAP_STAGE_SERVER_AIC) अणु
		convert_null_to_semi(in_text, *in_len);
		अगर (chap_server_compute_hash(conn, auth, in_text, out_text,
				out_len) < 0) अणु
			chap_बंद(conn);
			वापस 2;
		पूर्ण
		अगर (auth->authenticate_target)
			chap->chap_state = CHAP_STAGE_SERVER_NR;
		अन्यथा
			*out_len = 0;
		chap_बंद(conn);
		वापस 1;
	पूर्ण

	वापस 2;
पूर्ण
