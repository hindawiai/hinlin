<शैली गुरु>
/*
 *   fs/cअगरs/smb2transport.c
 *
 *   Copyright (C) International Business Machines  Corp., 2002, 2011
 *                 Etersoft, 2012
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *              Jeremy Allison (jra@samba.org) 2006
 *              Pavel Shilovsky (pshilovsky@samba.org) 2012
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#समावेश <linux/fs.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/net.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/mempool.h>
#समावेश <linux/highस्मृति.स>
#समावेश <crypto/aead.h>
#समावेश "smb2pdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "smb2proto.h"
#समावेश "cifs_debug.h"
#समावेश "smb2status.h"
#समावेश "smb2glob.h"

अटल पूर्णांक
smb3_crypto_shash_allocate(काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा cअगरs_secmech *p = &server->secmech;
	पूर्णांक rc;

	rc = cअगरs_alloc_hash("hmac(sha256)",
			     &p->hmacsha256,
			     &p->sdeschmacsha256);
	अगर (rc)
		जाओ err;

	rc = cअगरs_alloc_hash("cmac(aes)", &p->cmacaes, &p->sdesccmacaes);
	अगर (rc)
		जाओ err;

	वापस 0;
err:
	cअगरs_मुक्त_hash(&p->hmacsha256, &p->sdeschmacsha256);
	वापस rc;
पूर्ण

पूर्णांक
smb311_crypto_shash_allocate(काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा cअगरs_secmech *p = &server->secmech;
	पूर्णांक rc = 0;

	rc = cअगरs_alloc_hash("hmac(sha256)",
			     &p->hmacsha256,
			     &p->sdeschmacsha256);
	अगर (rc)
		वापस rc;

	rc = cअगरs_alloc_hash("cmac(aes)", &p->cmacaes, &p->sdesccmacaes);
	अगर (rc)
		जाओ err;

	rc = cअगरs_alloc_hash("sha512", &p->sha512, &p->sdescsha512);
	अगर (rc)
		जाओ err;

	वापस 0;

err:
	cअगरs_मुक्त_hash(&p->cmacaes, &p->sdesccmacaes);
	cअगरs_मुक्त_hash(&p->hmacsha256, &p->sdeschmacsha256);
	वापस rc;
पूर्ण


अटल
पूर्णांक smb2_get_sign_key(__u64 ses_id, काष्ठा TCP_Server_Info *server, u8 *key)
अणु
	काष्ठा cअगरs_chan *chan;
	काष्ठा cअगरs_ses *ses = शून्य;
	काष्ठा TCP_Server_Info *it = शून्य;
	पूर्णांक i;
	पूर्णांक rc = 0;

	spin_lock(&cअगरs_tcp_ses_lock);

	list_क्रम_each_entry(it, &cअगरs_tcp_ses_list, tcp_ses_list) अणु
		list_क्रम_each_entry(ses, &it->smb_ses_list, smb_ses_list) अणु
			अगर (ses->Suid == ses_id)
				जाओ found;
		पूर्ण
	पूर्ण
	cअगरs_server_dbg(VFS, "%s: Could not find session 0x%llx\n",
			__func__, ses_id);
	rc = -ENOENT;
	जाओ out;

found:
	अगर (ses->binding) अणु
		/*
		 * If we are in the process of binding a new channel
		 * to an existing session, use the master connection
		 * session key
		 */
		स_नकल(key, ses->smb3signingkey, SMB3_SIGN_KEY_SIZE);
		जाओ out;
	पूर्ण

	/*
	 * Otherwise, use the channel key.
	 */

	क्रम (i = 0; i < ses->chan_count; i++) अणु
		chan = ses->chans + i;
		अगर (chan->server == server) अणु
			स_नकल(key, chan->signkey, SMB3_SIGN_KEY_SIZE);
			जाओ out;
		पूर्ण
	पूर्ण

	cअगरs_dbg(VFS,
		 "%s: Could not find channel signing key for session 0x%llx\n",
		 __func__, ses_id);
	rc = -ENOENT;

out:
	spin_unlock(&cअगरs_tcp_ses_lock);
	वापस rc;
पूर्ण

अटल काष्ठा cअगरs_ses *
smb2_find_smb_ses_unlocked(काष्ठा TCP_Server_Info *server, __u64 ses_id)
अणु
	काष्ठा cअगरs_ses *ses;

	list_क्रम_each_entry(ses, &server->smb_ses_list, smb_ses_list) अणु
		अगर (ses->Suid != ses_id)
			जारी;
		वापस ses;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा cअगरs_ses *
smb2_find_smb_ses(काष्ठा TCP_Server_Info *server, __u64 ses_id)
अणु
	काष्ठा cअगरs_ses *ses;

	spin_lock(&cअगरs_tcp_ses_lock);
	ses = smb2_find_smb_ses_unlocked(server, ses_id);
	spin_unlock(&cअगरs_tcp_ses_lock);

	वापस ses;
पूर्ण

अटल काष्ठा cअगरs_tcon *
smb2_find_smb_sess_tcon_unlocked(काष्ठा cअगरs_ses *ses, __u32  tid)
अणु
	काष्ठा cअगरs_tcon *tcon;

	list_क्रम_each_entry(tcon, &ses->tcon_list, tcon_list) अणु
		अगर (tcon->tid != tid)
			जारी;
		++tcon->tc_count;
		वापस tcon;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Obtain tcon corresponding to the tid in the given
 * cअगरs_ses
 */

काष्ठा cअगरs_tcon *
smb2_find_smb_tcon(काष्ठा TCP_Server_Info *server, __u64 ses_id, __u32  tid)
अणु
	काष्ठा cअगरs_ses *ses;
	काष्ठा cअगरs_tcon *tcon;

	spin_lock(&cअगरs_tcp_ses_lock);
	ses = smb2_find_smb_ses_unlocked(server, ses_id);
	अगर (!ses) अणु
		spin_unlock(&cअगरs_tcp_ses_lock);
		वापस शून्य;
	पूर्ण
	tcon = smb2_find_smb_sess_tcon_unlocked(ses, tid);
	spin_unlock(&cअगरs_tcp_ses_lock);

	वापस tcon;
पूर्ण

पूर्णांक
smb2_calc_signature(काष्ठा smb_rqst *rqst, काष्ठा TCP_Server_Info *server,
			bool allocate_crypto)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर smb2_signature[SMB2_HMACSHA256_SIZE];
	अचिन्हित अक्षर *sigptr = smb2_signature;
	काष्ठा kvec *iov = rqst->rq_iov;
	काष्ठा smb2_sync_hdr *shdr = (काष्ठा smb2_sync_hdr *)iov[0].iov_base;
	काष्ठा cअगरs_ses *ses;
	काष्ठा shash_desc *shash;
	काष्ठा crypto_shash *hash;
	काष्ठा sdesc *sdesc = शून्य;
	काष्ठा smb_rqst drqst;

	ses = smb2_find_smb_ses(server, shdr->SessionId);
	अगर (!ses) अणु
		cअगरs_server_dbg(VFS, "%s: Could not find session\n", __func__);
		वापस 0;
	पूर्ण

	स_रखो(smb2_signature, 0x0, SMB2_HMACSHA256_SIZE);
	स_रखो(shdr->Signature, 0x0, SMB2_SIGNATURE_SIZE);

	अगर (allocate_crypto) अणु
		rc = cअगरs_alloc_hash("hmac(sha256)", &hash, &sdesc);
		अगर (rc) अणु
			cअगरs_server_dbg(VFS,
					"%s: sha256 alloc failed\n", __func__);
			वापस rc;
		पूर्ण
		shash = &sdesc->shash;
	पूर्ण अन्यथा अणु
		hash = server->secmech.hmacsha256;
		shash = &server->secmech.sdeschmacsha256->shash;
	पूर्ण

	rc = crypto_shash_setkey(hash, ses->auth_key.response,
			SMB2_NTLMV2_SESSKEY_SIZE);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS,
				"%s: Could not update with response\n",
				__func__);
		जाओ out;
	पूर्ण

	rc = crypto_shash_init(shash);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: Could not init sha256", __func__);
		जाओ out;
	पूर्ण

	/*
	 * For SMB2+, __cअगरs_calc_signature() expects to sign only the actual
	 * data, that is, iov[0] should not contain a rfc1002 length.
	 *
	 * Sign the rfc1002 length prior to passing the data (iov[1-N]) करोwn to
	 * __cअगरs_calc_signature().
	 */
	drqst = *rqst;
	अगर (drqst.rq_nvec >= 2 && iov[0].iov_len == 4) अणु
		rc = crypto_shash_update(shash, iov[0].iov_base,
					 iov[0].iov_len);
		अगर (rc) अणु
			cअगरs_server_dbg(VFS,
					"%s: Could not update with payload\n",
					__func__);
			जाओ out;
		पूर्ण
		drqst.rq_iov++;
		drqst.rq_nvec--;
	पूर्ण

	rc = __cअगरs_calc_signature(&drqst, server, sigptr, shash);
	अगर (!rc)
		स_नकल(shdr->Signature, sigptr, SMB2_SIGNATURE_SIZE);

out:
	अगर (allocate_crypto)
		cअगरs_मुक्त_hash(&hash, &sdesc);
	वापस rc;
पूर्ण

अटल पूर्णांक generate_key(काष्ठा cअगरs_ses *ses, काष्ठा kvec label,
			काष्ठा kvec context, __u8 *key, अचिन्हित पूर्णांक key_size)
अणु
	अचिन्हित अक्षर zero = 0x0;
	__u8 i[4] = अणु0, 0, 0, 1पूर्ण;
	__u8 L128[4] = अणु0, 0, 0, 128पूर्ण;
	__u8 L256[4] = अणु0, 0, 1, 0पूर्ण;
	पूर्णांक rc = 0;
	अचिन्हित अक्षर prfhash[SMB2_HMACSHA256_SIZE];
	अचिन्हित अक्षर *hashptr = prfhash;
	काष्ठा TCP_Server_Info *server = ses->server;

	स_रखो(prfhash, 0x0, SMB2_HMACSHA256_SIZE);
	स_रखो(key, 0x0, key_size);

	rc = smb3_crypto_shash_allocate(server);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: crypto alloc failed\n", __func__);
		जाओ smb3signkey_ret;
	पूर्ण

	rc = crypto_shash_setkey(server->secmech.hmacsha256,
		ses->auth_key.response, SMB2_NTLMV2_SESSKEY_SIZE);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: Could not set with session key\n", __func__);
		जाओ smb3signkey_ret;
	पूर्ण

	rc = crypto_shash_init(&server->secmech.sdeschmacsha256->shash);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: Could not init sign hmac\n", __func__);
		जाओ smb3signkey_ret;
	पूर्ण

	rc = crypto_shash_update(&server->secmech.sdeschmacsha256->shash,
				i, 4);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: Could not update with n\n", __func__);
		जाओ smb3signkey_ret;
	पूर्ण

	rc = crypto_shash_update(&server->secmech.sdeschmacsha256->shash,
				label.iov_base, label.iov_len);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: Could not update with label\n", __func__);
		जाओ smb3signkey_ret;
	पूर्ण

	rc = crypto_shash_update(&server->secmech.sdeschmacsha256->shash,
				&zero, 1);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: Could not update with zero\n", __func__);
		जाओ smb3signkey_ret;
	पूर्ण

	rc = crypto_shash_update(&server->secmech.sdeschmacsha256->shash,
				context.iov_base, context.iov_len);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: Could not update with context\n", __func__);
		जाओ smb3signkey_ret;
	पूर्ण

	अगर ((server->cipher_type == SMB2_ENCRYPTION_AES256_CCM) ||
		(server->cipher_type == SMB2_ENCRYPTION_AES256_GCM)) अणु
		rc = crypto_shash_update(&server->secmech.sdeschmacsha256->shash,
				L256, 4);
	पूर्ण अन्यथा अणु
		rc = crypto_shash_update(&server->secmech.sdeschmacsha256->shash,
				L128, 4);
	पूर्ण
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: Could not update with L\n", __func__);
		जाओ smb3signkey_ret;
	पूर्ण

	rc = crypto_shash_final(&server->secmech.sdeschmacsha256->shash,
				hashptr);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: Could not generate sha256 hash\n", __func__);
		जाओ smb3signkey_ret;
	पूर्ण

	स_नकल(key, hashptr, key_size);

smb3signkey_ret:
	वापस rc;
पूर्ण

काष्ठा derivation अणु
	काष्ठा kvec label;
	काष्ठा kvec context;
पूर्ण;

काष्ठा derivation_triplet अणु
	काष्ठा derivation signing;
	काष्ठा derivation encryption;
	काष्ठा derivation decryption;
पूर्ण;

अटल पूर्णांक
generate_smb3signingkey(काष्ठा cअगरs_ses *ses,
			स्थिर काष्ठा derivation_triplet *ptriplet)
अणु
	पूर्णांक rc;
#अगर_घोषित CONFIG_CIFS_DEBUG_DUMP_KEYS
	काष्ठा TCP_Server_Info *server = ses->server;
#पूर्ण_अगर

	/*
	 * All channels use the same encryption/decryption keys but
	 * they have their own signing key.
	 *
	 * When we generate the keys, check अगर it is क्रम a new channel
	 * (binding) in which हाल we only need to generate a signing
	 * key and store it in the channel as to not overग_लिखो the
	 * master connection signing key stored in the session
	 */

	अगर (ses->binding) अणु
		rc = generate_key(ses, ptriplet->signing.label,
				  ptriplet->signing.context,
				  cअगरs_ses_binding_channel(ses)->signkey,
				  SMB3_SIGN_KEY_SIZE);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		rc = generate_key(ses, ptriplet->signing.label,
				  ptriplet->signing.context,
				  ses->smb3signingkey,
				  SMB3_SIGN_KEY_SIZE);
		अगर (rc)
			वापस rc;

		स_नकल(ses->chans[0].signkey, ses->smb3signingkey,
		       SMB3_SIGN_KEY_SIZE);

		rc = generate_key(ses, ptriplet->encryption.label,
				  ptriplet->encryption.context,
				  ses->smb3encryptionkey,
				  SMB3_ENC_DEC_KEY_SIZE);
		rc = generate_key(ses, ptriplet->decryption.label,
				  ptriplet->decryption.context,
				  ses->smb3decryptionkey,
				  SMB3_ENC_DEC_KEY_SIZE);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (rc)
		वापस rc;

#अगर_घोषित CONFIG_CIFS_DEBUG_DUMP_KEYS
	cअगरs_dbg(VFS, "%s: dumping generated AES session keys\n", __func__);
	/*
	 * The session id is opaque in terms of endianness, so we can't
	 * prपूर्णांक it as a दीर्घ दीर्घ. we dump it as we got it on the wire
	 */
	cअगरs_dbg(VFS, "Session Id    %*ph\n", (पूर्णांक)माप(ses->Suid),
			&ses->Suid);
	cअगरs_dbg(VFS, "Cipher type   %d\n", server->cipher_type);
	cअगरs_dbg(VFS, "Session Key   %*ph\n",
		 SMB2_NTLMV2_SESSKEY_SIZE, ses->auth_key.response);
	cअगरs_dbg(VFS, "Signing Key   %*ph\n",
		 SMB3_SIGN_KEY_SIZE, ses->smb3signingkey);
	अगर ((server->cipher_type == SMB2_ENCRYPTION_AES256_CCM) ||
		(server->cipher_type == SMB2_ENCRYPTION_AES256_GCM)) अणु
		cअगरs_dbg(VFS, "ServerIn Key  %*ph\n",
				SMB3_GCM256_CRYPTKEY_SIZE, ses->smb3encryptionkey);
		cअगरs_dbg(VFS, "ServerOut Key %*ph\n",
				SMB3_GCM256_CRYPTKEY_SIZE, ses->smb3decryptionkey);
	पूर्ण अन्यथा अणु
		cअगरs_dbg(VFS, "ServerIn Key  %*ph\n",
				SMB3_GCM128_CRYPTKEY_SIZE, ses->smb3encryptionkey);
		cअगरs_dbg(VFS, "ServerOut Key %*ph\n",
				SMB3_GCM128_CRYPTKEY_SIZE, ses->smb3decryptionkey);
	पूर्ण
#पूर्ण_अगर
	वापस rc;
पूर्ण

पूर्णांक
generate_smb30signingkey(काष्ठा cअगरs_ses *ses)

अणु
	काष्ठा derivation_triplet triplet;
	काष्ठा derivation *d;

	d = &triplet.signing;
	d->label.iov_base = "SMB2AESCMAC";
	d->label.iov_len = 12;
	d->context.iov_base = "SmbSign";
	d->context.iov_len = 8;

	d = &triplet.encryption;
	d->label.iov_base = "SMB2AESCCM";
	d->label.iov_len = 11;
	d->context.iov_base = "ServerIn ";
	d->context.iov_len = 10;

	d = &triplet.decryption;
	d->label.iov_base = "SMB2AESCCM";
	d->label.iov_len = 11;
	d->context.iov_base = "ServerOut";
	d->context.iov_len = 10;

	वापस generate_smb3signingkey(ses, &triplet);
पूर्ण

पूर्णांक
generate_smb311signingkey(काष्ठा cअगरs_ses *ses)

अणु
	काष्ठा derivation_triplet triplet;
	काष्ठा derivation *d;

	d = &triplet.signing;
	d->label.iov_base = "SMBSigningKey";
	d->label.iov_len = 14;
	d->context.iov_base = ses->preauth_sha_hash;
	d->context.iov_len = 64;

	d = &triplet.encryption;
	d->label.iov_base = "SMBC2SCipherKey";
	d->label.iov_len = 16;
	d->context.iov_base = ses->preauth_sha_hash;
	d->context.iov_len = 64;

	d = &triplet.decryption;
	d->label.iov_base = "SMBS2CCipherKey";
	d->label.iov_len = 16;
	d->context.iov_base = ses->preauth_sha_hash;
	d->context.iov_len = 64;

	वापस generate_smb3signingkey(ses, &triplet);
पूर्ण

पूर्णांक
smb3_calc_signature(काष्ठा smb_rqst *rqst, काष्ठा TCP_Server_Info *server,
			bool allocate_crypto)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर smb3_signature[SMB2_CMACAES_SIZE];
	अचिन्हित अक्षर *sigptr = smb3_signature;
	काष्ठा kvec *iov = rqst->rq_iov;
	काष्ठा smb2_sync_hdr *shdr = (काष्ठा smb2_sync_hdr *)iov[0].iov_base;
	काष्ठा shash_desc *shash;
	काष्ठा crypto_shash *hash;
	काष्ठा sdesc *sdesc = शून्य;
	काष्ठा smb_rqst drqst;
	u8 key[SMB3_SIGN_KEY_SIZE];

	rc = smb2_get_sign_key(shdr->SessionId, server, key);
	अगर (rc)
		वापस 0;

	अगर (allocate_crypto) अणु
		rc = cअगरs_alloc_hash("cmac(aes)", &hash, &sdesc);
		अगर (rc)
			वापस rc;

		shash = &sdesc->shash;
	पूर्ण अन्यथा अणु
		hash = server->secmech.cmacaes;
		shash = &server->secmech.sdesccmacaes->shash;
	पूर्ण

	स_रखो(smb3_signature, 0x0, SMB2_CMACAES_SIZE);
	स_रखो(shdr->Signature, 0x0, SMB2_SIGNATURE_SIZE);

	rc = crypto_shash_setkey(hash, key, SMB2_CMACAES_SIZE);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: Could not set key for cmac aes\n", __func__);
		जाओ out;
	पूर्ण

	/*
	 * we alपढ़ोy allocate sdesccmacaes when we init smb3 signing key,
	 * so unlike smb2 हाल we करो not have to check here अगर secmech are
	 * initialized
	 */
	rc = crypto_shash_init(shash);
	अगर (rc) अणु
		cअगरs_server_dbg(VFS, "%s: Could not init cmac aes\n", __func__);
		जाओ out;
	पूर्ण

	/*
	 * For SMB2+, __cअगरs_calc_signature() expects to sign only the actual
	 * data, that is, iov[0] should not contain a rfc1002 length.
	 *
	 * Sign the rfc1002 length prior to passing the data (iov[1-N]) करोwn to
	 * __cअगरs_calc_signature().
	 */
	drqst = *rqst;
	अगर (drqst.rq_nvec >= 2 && iov[0].iov_len == 4) अणु
		rc = crypto_shash_update(shash, iov[0].iov_base,
					 iov[0].iov_len);
		अगर (rc) अणु
			cअगरs_server_dbg(VFS, "%s: Could not update with payload\n",
				 __func__);
			जाओ out;
		पूर्ण
		drqst.rq_iov++;
		drqst.rq_nvec--;
	पूर्ण

	rc = __cअगरs_calc_signature(&drqst, server, sigptr, shash);
	अगर (!rc)
		स_नकल(shdr->Signature, sigptr, SMB2_SIGNATURE_SIZE);

out:
	अगर (allocate_crypto)
		cअगरs_मुक्त_hash(&hash, &sdesc);
	वापस rc;
पूर्ण

/* must be called with server->srv_mutex held */
अटल पूर्णांक
smb2_sign_rqst(काष्ठा smb_rqst *rqst, काष्ठा TCP_Server_Info *server)
अणु
	पूर्णांक rc = 0;
	काष्ठा smb2_sync_hdr *shdr;
	काष्ठा smb2_sess_setup_req *ssr;
	bool is_binding;
	bool is_चिन्हित;

	shdr = (काष्ठा smb2_sync_hdr *)rqst->rq_iov[0].iov_base;
	ssr = (काष्ठा smb2_sess_setup_req *)shdr;

	is_binding = shdr->Command == SMB2_SESSION_SETUP &&
		(ssr->Flags & SMB2_SESSION_REQ_FLAG_BINDING);
	is_चिन्हित = shdr->Flags & SMB2_FLAGS_SIGNED;

	अगर (!is_चिन्हित)
		वापस 0;
	अगर (server->tcpStatus == CअगरsNeedNegotiate)
		वापस 0;
	अगर (!is_binding && !server->session_estab) अणु
		म_नकलन(shdr->Signature, "BSRSPYL", 8);
		वापस 0;
	पूर्ण

	rc = server->ops->calc_signature(rqst, server, false);

	वापस rc;
पूर्ण

पूर्णांक
smb2_verअगरy_signature(काष्ठा smb_rqst *rqst, काष्ठा TCP_Server_Info *server)
अणु
	अचिन्हित पूर्णांक rc;
	अक्षर server_response_sig[SMB2_SIGNATURE_SIZE];
	काष्ठा smb2_sync_hdr *shdr =
			(काष्ठा smb2_sync_hdr *)rqst->rq_iov[0].iov_base;

	अगर ((shdr->Command == SMB2_NEGOTIATE) ||
	    (shdr->Command == SMB2_SESSION_SETUP) ||
	    (shdr->Command == SMB2_OPLOCK_BREAK) ||
	    server->ignore_signature ||
	    (!server->session_estab))
		वापस 0;

	/*
	 * BB what अगर signatures are supposed to be on क्रम session but
	 * server करोes not send one? BB
	 */

	/* Do not need to verअगरy session setups with signature "BSRSPYL " */
	अगर (स_भेद(shdr->Signature, "BSRSPYL ", 8) == 0)
		cअगरs_dbg(FYI, "dummy signature received for smb command 0x%x\n",
			 shdr->Command);

	/*
	 * Save off the origiginal signature so we can modअगरy the smb and check
	 * our calculated signature against what the server sent.
	 */
	स_नकल(server_response_sig, shdr->Signature, SMB2_SIGNATURE_SIZE);

	स_रखो(shdr->Signature, 0, SMB2_SIGNATURE_SIZE);

	rc = server->ops->calc_signature(rqst, server, true);

	अगर (rc)
		वापस rc;

	अगर (स_भेद(server_response_sig, shdr->Signature, SMB2_SIGNATURE_SIZE)) अणु
		cअगरs_dbg(VFS, "sign fail cmd 0x%x message id 0x%llx\n",
			shdr->Command, shdr->MessageId);
		वापस -EACCES;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

/*
 * Set message id क्रम the request. Should be called after रुको_क्रम_मुक्त_request
 * and when srv_mutex is held.
 */
अटल अंतरभूत व्योम
smb2_seq_num_पूर्णांकo_buf(काष्ठा TCP_Server_Info *server,
		      काष्ठा smb2_sync_hdr *shdr)
अणु
	अचिन्हित पूर्णांक i, num = le16_to_cpu(shdr->CreditCharge);

	shdr->MessageId = get_next_mid64(server);
	/* skip message numbers according to CreditCharge field */
	क्रम (i = 1; i < num; i++)
		get_next_mid(server);
पूर्ण

अटल काष्ठा mid_q_entry *
smb2_mid_entry_alloc(स्थिर काष्ठा smb2_sync_hdr *shdr,
		     काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा mid_q_entry *temp;
	अचिन्हित पूर्णांक credits = le16_to_cpu(shdr->CreditCharge);

	अगर (server == शून्य) अणु
		cअगरs_dbg(VFS, "Null TCP session in smb2_mid_entry_alloc\n");
		वापस शून्य;
	पूर्ण

	temp = mempool_alloc(cअगरs_mid_poolp, GFP_NOFS);
	स_रखो(temp, 0, माप(काष्ठा mid_q_entry));
	kref_init(&temp->refcount);
	temp->mid = le64_to_cpu(shdr->MessageId);
	temp->credits = credits > 0 ? credits : 1;
	temp->pid = current->pid;
	temp->command = shdr->Command; /* Always LE */
	temp->when_alloc = jअगरfies;
	temp->server = server;

	/*
	 * The शेष is क्रम the mid to be synchronous, so the
	 * शेष callback just wakes up the current task.
	 */
	get_task_काष्ठा(current);
	temp->creator = current;
	temp->callback = cअगरs_wake_up_task;
	temp->callback_data = current;

	atomic_inc(&midCount);
	temp->mid_state = MID_REQUEST_ALLOCATED;
	trace_smb3_cmd_enter(shdr->TreeId, shdr->SessionId,
		le16_to_cpu(shdr->Command), temp->mid);
	वापस temp;
पूर्ण

अटल पूर्णांक
smb2_get_mid_entry(काष्ठा cअगरs_ses *ses, काष्ठा TCP_Server_Info *server,
		   काष्ठा smb2_sync_hdr *shdr, काष्ठा mid_q_entry **mid)
अणु
	अगर (server->tcpStatus == CअगरsExiting)
		वापस -ENOENT;

	अगर (server->tcpStatus == CअगरsNeedReconnect) अणु
		cअगरs_dbg(FYI, "tcp session dead - return to caller to retry\n");
		वापस -EAGAIN;
	पूर्ण

	अगर (server->tcpStatus == CअगरsNeedNegotiate &&
	   shdr->Command != SMB2_NEGOTIATE)
		वापस -EAGAIN;

	अगर (ses->status == CअगरsNew) अणु
		अगर ((shdr->Command != SMB2_SESSION_SETUP) &&
		    (shdr->Command != SMB2_NEGOTIATE))
			वापस -EAGAIN;
		/* अन्यथा ok - we are setting up session */
	पूर्ण

	अगर (ses->status == CअगरsExiting) अणु
		अगर (shdr->Command != SMB2_LOGOFF)
			वापस -EAGAIN;
		/* अन्यथा ok - we are shutting करोwn the session */
	पूर्ण

	*mid = smb2_mid_entry_alloc(shdr, server);
	अगर (*mid == शून्य)
		वापस -ENOMEM;
	spin_lock(&GlobalMid_Lock);
	list_add_tail(&(*mid)->qhead, &server->pending_mid_q);
	spin_unlock(&GlobalMid_Lock);

	वापस 0;
पूर्ण

पूर्णांक
smb2_check_receive(काष्ठा mid_q_entry *mid, काष्ठा TCP_Server_Info *server,
		   bool log_error)
अणु
	अचिन्हित पूर्णांक len = mid->resp_buf_size;
	काष्ठा kvec iov[1];
	काष्ठा smb_rqst rqst = अणु .rq_iov = iov,
				 .rq_nvec = 1 पूर्ण;

	iov[0].iov_base = (अक्षर *)mid->resp_buf;
	iov[0].iov_len = len;

	dump_smb(mid->resp_buf, min_t(u32, 80, len));
	/* convert the length पूर्णांकo a more usable क्रमm */
	अगर (len > 24 && server->sign && !mid->decrypted) अणु
		पूर्णांक rc;

		rc = smb2_verअगरy_signature(&rqst, server);
		अगर (rc)
			cअगरs_server_dbg(VFS, "SMB signature verification returned error = %d\n",
				 rc);
	पूर्ण

	वापस map_smb2_to_linux_error(mid->resp_buf, log_error);
पूर्ण

काष्ठा mid_q_entry *
smb2_setup_request(काष्ठा cअगरs_ses *ses, काष्ठा TCP_Server_Info *server,
		   काष्ठा smb_rqst *rqst)
अणु
	पूर्णांक rc;
	काष्ठा smb2_sync_hdr *shdr =
			(काष्ठा smb2_sync_hdr *)rqst->rq_iov[0].iov_base;
	काष्ठा mid_q_entry *mid;

	smb2_seq_num_पूर्णांकo_buf(server, shdr);

	rc = smb2_get_mid_entry(ses, server, shdr, &mid);
	अगर (rc) अणु
		revert_current_mid_from_hdr(server, shdr);
		वापस ERR_PTR(rc);
	पूर्ण

	rc = smb2_sign_rqst(rqst, server);
	अगर (rc) अणु
		revert_current_mid_from_hdr(server, shdr);
		cअगरs_delete_mid(mid);
		वापस ERR_PTR(rc);
	पूर्ण

	वापस mid;
पूर्ण

काष्ठा mid_q_entry *
smb2_setup_async_request(काष्ठा TCP_Server_Info *server, काष्ठा smb_rqst *rqst)
अणु
	पूर्णांक rc;
	काष्ठा smb2_sync_hdr *shdr =
			(काष्ठा smb2_sync_hdr *)rqst->rq_iov[0].iov_base;
	काष्ठा mid_q_entry *mid;

	अगर (server->tcpStatus == CअगरsNeedNegotiate &&
	   shdr->Command != SMB2_NEGOTIATE)
		वापस ERR_PTR(-EAGAIN);

	smb2_seq_num_पूर्णांकo_buf(server, shdr);

	mid = smb2_mid_entry_alloc(shdr, server);
	अगर (mid == शून्य) अणु
		revert_current_mid_from_hdr(server, shdr);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	rc = smb2_sign_rqst(rqst, server);
	अगर (rc) अणु
		revert_current_mid_from_hdr(server, shdr);
		DeleteMidQEntry(mid);
		वापस ERR_PTR(rc);
	पूर्ण

	वापस mid;
पूर्ण

पूर्णांक
smb3_crypto_aead_allocate(काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा crypto_aead *tfm;

	अगर (!server->secmech.ccmaesencrypt) अणु
		अगर ((server->cipher_type == SMB2_ENCRYPTION_AES128_GCM) ||
		    (server->cipher_type == SMB2_ENCRYPTION_AES256_GCM))
			tfm = crypto_alloc_aead("gcm(aes)", 0, 0);
		अन्यथा
			tfm = crypto_alloc_aead("ccm(aes)", 0, 0);
		अगर (IS_ERR(tfm)) अणु
			cअगरs_server_dbg(VFS, "%s: Failed alloc encrypt aead\n",
				 __func__);
			वापस PTR_ERR(tfm);
		पूर्ण
		server->secmech.ccmaesencrypt = tfm;
	पूर्ण

	अगर (!server->secmech.ccmaesdecrypt) अणु
		अगर ((server->cipher_type == SMB2_ENCRYPTION_AES128_GCM) ||
		    (server->cipher_type == SMB2_ENCRYPTION_AES256_GCM))
			tfm = crypto_alloc_aead("gcm(aes)", 0, 0);
		अन्यथा
			tfm = crypto_alloc_aead("ccm(aes)", 0, 0);
		अगर (IS_ERR(tfm)) अणु
			crypto_मुक्त_aead(server->secmech.ccmaesencrypt);
			server->secmech.ccmaesencrypt = शून्य;
			cअगरs_server_dbg(VFS, "%s: Failed to alloc decrypt aead\n",
				 __func__);
			वापस PTR_ERR(tfm);
		पूर्ण
		server->secmech.ccmaesdecrypt = tfm;
	पूर्ण

	वापस 0;
पूर्ण
