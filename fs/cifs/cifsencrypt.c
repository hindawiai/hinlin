<शैली गुरु>
/*
 *   fs/cअगरs/cअगरsencrypt.c
 *
 *   Encryption and hashing operations relating to NTLM, NTLMv2.  See MS-NLMP
 *   क्रम more detailed inक्रमmation
 *
 *   Copyright (C) International Business Machines  Corp., 2005,2013
 *   Author(s): Steve French (sfrench@us.ibm.com)
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
#समावेश <linux/slab.h>
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_unicode.h"
#समावेश "cifsproto.h"
#समावेश "ntlmssp.h"
#समावेश <linux/प्रकार.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/fips.h>
#समावेश <crypto/arc4.h>
#समावेश <crypto/aead.h>

पूर्णांक __cअगरs_calc_signature(काष्ठा smb_rqst *rqst,
			काष्ठा TCP_Server_Info *server, अक्षर *signature,
			काष्ठा shash_desc *shash)
अणु
	पूर्णांक i;
	पूर्णांक rc;
	काष्ठा kvec *iov = rqst->rq_iov;
	पूर्णांक n_vec = rqst->rq_nvec;
	पूर्णांक is_smb2 = server->vals->header_preamble_size == 0;

	/* iov[0] is actual data and not the rfc1002 length क्रम SMB2+ */
	अगर (is_smb2) अणु
		अगर (iov[0].iov_len <= 4)
			वापस -EIO;
		i = 0;
	पूर्ण अन्यथा अणु
		अगर (n_vec < 2 || iov[0].iov_len != 4)
			वापस -EIO;
		i = 1; /* skip rfc1002 length */
	पूर्ण

	क्रम (; i < n_vec; i++) अणु
		अगर (iov[i].iov_len == 0)
			जारी;
		अगर (iov[i].iov_base == शून्य) अणु
			cअगरs_dbg(VFS, "null iovec entry\n");
			वापस -EIO;
		पूर्ण

		rc = crypto_shash_update(shash,
					 iov[i].iov_base, iov[i].iov_len);
		अगर (rc) अणु
			cअगरs_dbg(VFS, "%s: Could not update with payload\n",
				 __func__);
			वापस rc;
		पूर्ण
	पूर्ण

	/* now hash over the rq_pages array */
	क्रम (i = 0; i < rqst->rq_npages; i++) अणु
		व्योम *kaddr;
		अचिन्हित पूर्णांक len, offset;

		rqst_page_get_length(rqst, i, &len, &offset);

		kaddr = (अक्षर *) kmap(rqst->rq_pages[i]) + offset;

		rc = crypto_shash_update(shash, kaddr, len);
		अगर (rc) अणु
			cअगरs_dbg(VFS, "%s: Could not update with payload\n",
				 __func__);
			kunmap(rqst->rq_pages[i]);
			वापस rc;
		पूर्ण

		kunmap(rqst->rq_pages[i]);
	पूर्ण

	rc = crypto_shash_final(shash, signature);
	अगर (rc)
		cअगरs_dbg(VFS, "%s: Could not generate hash\n", __func__);

	वापस rc;
पूर्ण

/*
 * Calculate and वापस the CIFS signature based on the mac key and SMB PDU.
 * The 16 byte signature must be allocated by the caller. Note we only use the
 * 1st eight bytes and that the smb header signature field on input contains
 * the sequence number beक्रमe this function is called. Also, this function
 * should be called with the server->srv_mutex held.
 */
अटल पूर्णांक cअगरs_calc_signature(काष्ठा smb_rqst *rqst,
			काष्ठा TCP_Server_Info *server, अक्षर *signature)
अणु
	पूर्णांक rc;

	अगर (!rqst->rq_iov || !signature || !server)
		वापस -EINVAL;

	rc = cअगरs_alloc_hash("md5", &server->secmech.md5,
			     &server->secmech.sdescmd5);
	अगर (rc)
		वापस -1;

	rc = crypto_shash_init(&server->secmech.sdescmd5->shash);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not init md5\n", __func__);
		वापस rc;
	पूर्ण

	rc = crypto_shash_update(&server->secmech.sdescmd5->shash,
		server->session_key.response, server->session_key.len);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not update with response\n", __func__);
		वापस rc;
	पूर्ण

	वापस __cअगरs_calc_signature(rqst, server, signature,
				     &server->secmech.sdescmd5->shash);
पूर्ण

/* must be called with server->srv_mutex held */
पूर्णांक cअगरs_sign_rqst(काष्ठा smb_rqst *rqst, काष्ठा TCP_Server_Info *server,
		   __u32 *pexpected_response_sequence_number)
अणु
	पूर्णांक rc = 0;
	अक्षर smb_signature[20];
	काष्ठा smb_hdr *cअगरs_pdu = (काष्ठा smb_hdr *)rqst->rq_iov[0].iov_base;

	अगर (rqst->rq_iov[0].iov_len != 4 ||
	    rqst->rq_iov[0].iov_base + 4 != rqst->rq_iov[1].iov_base)
		वापस -EIO;

	अगर ((cअगरs_pdu == शून्य) || (server == शून्य))
		वापस -EINVAL;

	अगर (!(cअगरs_pdu->Flags2 & SMBFLG2_SECURITY_SIGNATURE) ||
	    server->tcpStatus == CअगरsNeedNegotiate)
		वापस rc;

	अगर (!server->session_estab) अणु
		स_नकल(cअगरs_pdu->Signature.SecuritySignature, "BSRSPYL", 8);
		वापस rc;
	पूर्ण

	cअगरs_pdu->Signature.Sequence.SequenceNumber =
				cpu_to_le32(server->sequence_number);
	cअगरs_pdu->Signature.Sequence.Reserved = 0;

	*pexpected_response_sequence_number = ++server->sequence_number;
	++server->sequence_number;

	rc = cअगरs_calc_signature(rqst, server, smb_signature);
	अगर (rc)
		स_रखो(cअगरs_pdu->Signature.SecuritySignature, 0, 8);
	अन्यथा
		स_नकल(cअगरs_pdu->Signature.SecuritySignature, smb_signature, 8);

	वापस rc;
पूर्ण

पूर्णांक cअगरs_sign_smbv(काष्ठा kvec *iov, पूर्णांक n_vec, काष्ठा TCP_Server_Info *server,
		   __u32 *pexpected_response_sequence)
अणु
	काष्ठा smb_rqst rqst = अणु .rq_iov = iov,
				 .rq_nvec = n_vec पूर्ण;

	वापस cअगरs_sign_rqst(&rqst, server, pexpected_response_sequence);
पूर्ण

/* must be called with server->srv_mutex held */
पूर्णांक cअगरs_sign_smb(काष्ठा smb_hdr *cअगरs_pdu, काष्ठा TCP_Server_Info *server,
		  __u32 *pexpected_response_sequence_number)
अणु
	काष्ठा kvec iov[2];

	iov[0].iov_base = cअगरs_pdu;
	iov[0].iov_len = 4;
	iov[1].iov_base = (अक्षर *)cअगरs_pdu + 4;
	iov[1].iov_len = be32_to_cpu(cअगरs_pdu->smb_buf_length);

	वापस cअगरs_sign_smbv(iov, 2, server,
			      pexpected_response_sequence_number);
पूर्ण

पूर्णांक cअगरs_verअगरy_signature(काष्ठा smb_rqst *rqst,
			  काष्ठा TCP_Server_Info *server,
			  __u32 expected_sequence_number)
अणु
	अचिन्हित पूर्णांक rc;
	अक्षर server_response_sig[8];
	अक्षर what_we_think_sig_should_be[20];
	काष्ठा smb_hdr *cअगरs_pdu = (काष्ठा smb_hdr *)rqst->rq_iov[0].iov_base;

	अगर (rqst->rq_iov[0].iov_len != 4 ||
	    rqst->rq_iov[0].iov_base + 4 != rqst->rq_iov[1].iov_base)
		वापस -EIO;

	अगर (cअगरs_pdu == शून्य || server == शून्य)
		वापस -EINVAL;

	अगर (!server->session_estab)
		वापस 0;

	अगर (cअगरs_pdu->Command == SMB_COM_LOCKING_ANDX) अणु
		काष्ठा smb_com_lock_req *pSMB =
			(काष्ठा smb_com_lock_req *)cअगरs_pdu;
		अगर (pSMB->LockType & LOCKING_ANDX_OPLOCK_RELEASE)
			वापस 0;
	पूर्ण

	/* BB what अगर signatures are supposed to be on क्रम session but
	   server करोes not send one? BB */

	/* Do not need to verअगरy session setups with signature "BSRSPYL "  */
	अगर (स_भेद(cअगरs_pdu->Signature.SecuritySignature, "BSRSPYL ", 8) == 0)
		cअगरs_dbg(FYI, "dummy signature received for smb command 0x%x\n",
			 cअगरs_pdu->Command);

	/* save off the origiginal signature so we can modअगरy the smb and check
		its signature against what the server sent */
	स_नकल(server_response_sig, cअगरs_pdu->Signature.SecuritySignature, 8);

	cअगरs_pdu->Signature.Sequence.SequenceNumber =
					cpu_to_le32(expected_sequence_number);
	cअगरs_pdu->Signature.Sequence.Reserved = 0;

	mutex_lock(&server->srv_mutex);
	rc = cअगरs_calc_signature(rqst, server, what_we_think_sig_should_be);
	mutex_unlock(&server->srv_mutex);

	अगर (rc)
		वापस rc;

/*	cअगरs_dump_mem("what we think it should be: ",
		      what_we_think_sig_should_be, 16); */

	अगर (स_भेद(server_response_sig, what_we_think_sig_should_be, 8))
		वापस -EACCES;
	अन्यथा
		वापस 0;

पूर्ण

/* first calculate 24 bytes ntlm response and then 16 byte session key */
पूर्णांक setup_ntlm_response(काष्ठा cअगरs_ses *ses, स्थिर काष्ठा nls_table *nls_cp)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक temp_len = CIFS_SESS_KEY_SIZE + CIFS_AUTH_RESP_SIZE;
	अक्षर temp_key[CIFS_SESS_KEY_SIZE];

	अगर (!ses)
		वापस -EINVAL;

	ses->auth_key.response = kदो_स्मृति(temp_len, GFP_KERNEL);
	अगर (!ses->auth_key.response)
		वापस -ENOMEM;

	ses->auth_key.len = temp_len;

	rc = SMBNTencrypt(ses->password, ses->server->cryptkey,
			ses->auth_key.response + CIFS_SESS_KEY_SIZE, nls_cp);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "%s Can't generate NTLM response, error: %d\n",
			 __func__, rc);
		वापस rc;
	पूर्ण

	rc = E_md4hash(ses->password, temp_key, nls_cp);
	अगर (rc) अणु
		cअगरs_dbg(FYI, "%s Can't generate NT hash, error: %d\n",
			 __func__, rc);
		वापस rc;
	पूर्ण

	rc = mdfour(ses->auth_key.response, temp_key, CIFS_SESS_KEY_SIZE);
	अगर (rc)
		cअगरs_dbg(FYI, "%s Can't generate NTLM session key, error: %d\n",
			 __func__, rc);

	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
पूर्णांक calc_lanman_hash(स्थिर अक्षर *password, स्थिर अक्षर *cryptkey, bool encrypt,
			अक्षर *lnm_session_key)
अणु
	पूर्णांक i, len;
	पूर्णांक rc;
	अक्षर password_with_pad[CIFS_ENCPWD_SIZE] = अणु0पूर्ण;

	अगर (password) अणु
		क्रम (len = 0; len < CIFS_ENCPWD_SIZE; len++)
			अगर (!password[len])
				अवरोध;

		स_नकल(password_with_pad, password, len);
	पूर्ण

	अगर (!encrypt && global_secflags & CIFSSEC_MAY_PLNTXT) अणु
		स_नकल(lnm_session_key, password_with_pad,
			CIFS_ENCPWD_SIZE);
		वापस 0;
	पूर्ण

	/* calculate old style session key */
	/* calling बड़े is less broken than repeatedly
	calling nls_बड़े would be since that will never
	work क्रम UTF8, but neither handles multibyte code pages
	but the only alternative would be converting to UCS-16 (Unicode)
	(using a routine something like UniStrupr) then
	uppercasing and then converting back from Unicode - which
	would only worth करोing it अगर we knew it were utf8. Basically
	utf8 and other multibyte codepages each need their own strupper
	function since a byte at a समय will ont work. */

	क्रम (i = 0; i < CIFS_ENCPWD_SIZE; i++)
		password_with_pad[i] = बड़े(password_with_pad[i]);

	rc = SMBencrypt(password_with_pad, cryptkey, lnm_session_key);

	वापस rc;
पूर्ण
#पूर्ण_अगर /* CIFS_WEAK_PW_HASH */

/* Build a proper attribute value/target info pairs blob.
 * Fill in netbios and dns करोमुख्य name and workstation name
 * and client समय (total five av pairs and + one end of fields indicator.
 * Allocate करोमुख्य name which माला_लो मुक्तd when session काष्ठा is deallocated.
 */
अटल पूर्णांक
build_avpair_blob(काष्ठा cअगरs_ses *ses, स्थिर काष्ठा nls_table *nls_cp)
अणु
	अचिन्हित पूर्णांक dlen;
	अचिन्हित पूर्णांक size = 2 * माप(काष्ठा ntlmssp2_name);
	अक्षर *defdmname = "WORKGROUP";
	अचिन्हित अक्षर *blobptr;
	काष्ठा ntlmssp2_name *attrptr;

	अगर (!ses->करोमुख्यName) अणु
		ses->करोमुख्यName = kstrdup(defdmname, GFP_KERNEL);
		अगर (!ses->करोमुख्यName)
			वापस -ENOMEM;
	पूर्ण

	dlen = म_माप(ses->करोमुख्यName);

	/*
	 * The length of this blob is two बार the size of a
	 * काष्ठाure (av pair) which holds name/size
	 * ( क्रम NTLMSSP_AV_NB_DOMAIN_NAME followed by NTLMSSP_AV_EOL ) +
	 * unicode length of a netbios करोमुख्य name
	 */
	ses->auth_key.len = size + 2 * dlen;
	ses->auth_key.response = kzalloc(ses->auth_key.len, GFP_KERNEL);
	अगर (!ses->auth_key.response) अणु
		ses->auth_key.len = 0;
		वापस -ENOMEM;
	पूर्ण

	blobptr = ses->auth_key.response;
	attrptr = (काष्ठा ntlmssp2_name *) blobptr;

	/*
	 * As defined in MS-NTLM 3.3.2, just this av pair field
	 * is sufficient as part of the temp
	 */
	attrptr->type = cpu_to_le16(NTLMSSP_AV_NB_DOMAIN_NAME);
	attrptr->length = cpu_to_le16(2 * dlen);
	blobptr = (अचिन्हित अक्षर *)attrptr + माप(काष्ठा ntlmssp2_name);
	cअगरs_strtoUTF16((__le16 *)blobptr, ses->करोमुख्यName, dlen, nls_cp);

	वापस 0;
पूर्ण

/* Server has provided av pairs/target info in the type 2 challenge
 * packet and we have plucked it and stored within smb session.
 * We parse that blob here to find netbios करोमुख्य name to be used
 * as part of ntlmv2 authentication (in Target String), अगर not alपढ़ोy
 * specअगरied on the command line.
 * If this function वापसs without any error but without fetching
 * करोमुख्य name, authentication may fail against some server but
 * may not fail against other (those who are not very particular
 * about target string i.e. क्रम some, just user name might suffice.
 */
अटल पूर्णांक
find_करोमुख्य_name(काष्ठा cअगरs_ses *ses, स्थिर काष्ठा nls_table *nls_cp)
अणु
	अचिन्हित पूर्णांक attrsize;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक onesize = माप(काष्ठा ntlmssp2_name);
	अचिन्हित अक्षर *blobptr;
	अचिन्हित अक्षर *blobend;
	काष्ठा ntlmssp2_name *attrptr;

	अगर (!ses->auth_key.len || !ses->auth_key.response)
		वापस 0;

	blobptr = ses->auth_key.response;
	blobend = blobptr + ses->auth_key.len;

	जबतक (blobptr + onesize < blobend) अणु
		attrptr = (काष्ठा ntlmssp2_name *) blobptr;
		type = le16_to_cpu(attrptr->type);
		अगर (type == NTLMSSP_AV_EOL)
			अवरोध;
		blobptr += 2; /* advance attr type */
		attrsize = le16_to_cpu(attrptr->length);
		blobptr += 2; /* advance attr size */
		अगर (blobptr + attrsize > blobend)
			अवरोध;
		अगर (type == NTLMSSP_AV_NB_DOMAIN_NAME) अणु
			अगर (!attrsize || attrsize >= CIFS_MAX_DOMAINNAME_LEN)
				अवरोध;
			अगर (!ses->करोमुख्यName) अणु
				ses->करोमुख्यName =
					kदो_स्मृति(attrsize + 1, GFP_KERNEL);
				अगर (!ses->करोमुख्यName)
						वापस -ENOMEM;
				cअगरs_from_utf16(ses->करोमुख्यName,
					(__le16 *)blobptr, attrsize, attrsize,
					nls_cp, NO_MAP_UNI_RSVD);
				अवरोध;
			पूर्ण
		पूर्ण
		blobptr += attrsize; /* advance attr  value */
	पूर्ण

	वापस 0;
पूर्ण

/* Server has provided av pairs/target info in the type 2 challenge
 * packet and we have plucked it and stored within smb session.
 * We parse that blob here to find the server given बारtamp
 * as part of ntlmv2 authentication (or local current समय as
 * शेष in हाल of failure)
 */
अटल __le64
find_बारtamp(काष्ठा cअगरs_ses *ses)
अणु
	अचिन्हित पूर्णांक attrsize;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक onesize = माप(काष्ठा ntlmssp2_name);
	अचिन्हित अक्षर *blobptr;
	अचिन्हित अक्षर *blobend;
	काष्ठा ntlmssp2_name *attrptr;
	काष्ठा बारpec64 ts;

	अगर (!ses->auth_key.len || !ses->auth_key.response)
		वापस 0;

	blobptr = ses->auth_key.response;
	blobend = blobptr + ses->auth_key.len;

	जबतक (blobptr + onesize < blobend) अणु
		attrptr = (काष्ठा ntlmssp2_name *) blobptr;
		type = le16_to_cpu(attrptr->type);
		अगर (type == NTLMSSP_AV_EOL)
			अवरोध;
		blobptr += 2; /* advance attr type */
		attrsize = le16_to_cpu(attrptr->length);
		blobptr += 2; /* advance attr size */
		अगर (blobptr + attrsize > blobend)
			अवरोध;
		अगर (type == NTLMSSP_AV_TIMESTAMP) अणु
			अगर (attrsize == माप(u64))
				वापस *((__le64 *)blobptr);
		पूर्ण
		blobptr += attrsize; /* advance attr value */
	पूर्ण

	kसमय_get_real_ts64(&ts);
	वापस cpu_to_le64(cअगरs_UnixTimeToNT(ts));
पूर्ण

अटल पूर्णांक calc_ntlmv2_hash(काष्ठा cअगरs_ses *ses, अक्षर *ntlmv2_hash,
			    स्थिर काष्ठा nls_table *nls_cp)
अणु
	पूर्णांक rc = 0;
	पूर्णांक len;
	अक्षर nt_hash[CIFS_NTHASH_SIZE];
	__le16 *user;
	ब_अक्षर_प्रकार *करोमुख्य;
	ब_अक्षर_प्रकार *server;

	अगर (!ses->server->secmech.sdeschmacmd5) अणु
		cअगरs_dbg(VFS, "%s: can't generate ntlmv2 hash\n", __func__);
		वापस -1;
	पूर्ण

	/* calculate md4 hash of password */
	E_md4hash(ses->password, nt_hash, nls_cp);

	rc = crypto_shash_setkey(ses->server->secmech.hmacmd5, nt_hash,
				CIFS_NTHASH_SIZE);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not set NT Hash as a key\n", __func__);
		वापस rc;
	पूर्ण

	rc = crypto_shash_init(&ses->server->secmech.sdeschmacmd5->shash);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not init hmacmd5\n", __func__);
		वापस rc;
	पूर्ण

	/* convert ses->user_name to unicode */
	len = ses->user_name ? म_माप(ses->user_name) : 0;
	user = kदो_स्मृति(2 + (len * 2), GFP_KERNEL);
	अगर (user == शून्य) अणु
		rc = -ENOMEM;
		वापस rc;
	पूर्ण

	अगर (len) अणु
		len = cअगरs_strtoUTF16(user, ses->user_name, len, nls_cp);
		UniStrupr(user);
	पूर्ण अन्यथा अणु
		स_रखो(user, '\0', 2);
	पूर्ण

	rc = crypto_shash_update(&ses->server->secmech.sdeschmacmd5->shash,
				(अक्षर *)user, 2 * len);
	kमुक्त(user);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not update with user\n", __func__);
		वापस rc;
	पूर्ण

	/* convert ses->करोमुख्यName to unicode and upperहाल */
	अगर (ses->करोमुख्यName) अणु
		len = म_माप(ses->करोमुख्यName);

		करोमुख्य = kदो_स्मृति(2 + (len * 2), GFP_KERNEL);
		अगर (करोमुख्य == शून्य) अणु
			rc = -ENOMEM;
			वापस rc;
		पूर्ण
		len = cअगरs_strtoUTF16((__le16 *)करोमुख्य, ses->करोमुख्यName, len,
				      nls_cp);
		rc =
		crypto_shash_update(&ses->server->secmech.sdeschmacmd5->shash,
					(अक्षर *)करोमुख्य, 2 * len);
		kमुक्त(करोमुख्य);
		अगर (rc) अणु
			cअगरs_dbg(VFS, "%s: Could not update with domain\n",
				 __func__);
			वापस rc;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* We use ses->ip_addr अगर no करोमुख्य name available */
		len = म_माप(ses->ip_addr);

		server = kदो_स्मृति(2 + (len * 2), GFP_KERNEL);
		अगर (server == शून्य) अणु
			rc = -ENOMEM;
			वापस rc;
		पूर्ण
		len = cअगरs_strtoUTF16((__le16 *)server, ses->ip_addr, len,
					nls_cp);
		rc =
		crypto_shash_update(&ses->server->secmech.sdeschmacmd5->shash,
					(अक्षर *)server, 2 * len);
		kमुक्त(server);
		अगर (rc) अणु
			cअगरs_dbg(VFS, "%s: Could not update with server\n",
				 __func__);
			वापस rc;
		पूर्ण
	पूर्ण

	rc = crypto_shash_final(&ses->server->secmech.sdeschmacmd5->shash,
					ntlmv2_hash);
	अगर (rc)
		cअगरs_dbg(VFS, "%s: Could not generate md5 hash\n", __func__);

	वापस rc;
पूर्ण

अटल पूर्णांक
CalcNTLMv2_response(स्थिर काष्ठा cअगरs_ses *ses, अक्षर *ntlmv2_hash)
अणु
	पूर्णांक rc;
	काष्ठा ntlmv2_resp *ntlmv2 = (काष्ठा ntlmv2_resp *)
	    (ses->auth_key.response + CIFS_SESS_KEY_SIZE);
	अचिन्हित पूर्णांक hash_len;

	/* The MD5 hash starts at challenge_key.key */
	hash_len = ses->auth_key.len - (CIFS_SESS_KEY_SIZE +
		दुरत्व(काष्ठा ntlmv2_resp, challenge.key[0]));

	अगर (!ses->server->secmech.sdeschmacmd5) अणु
		cअगरs_dbg(VFS, "%s: can't generate ntlmv2 hash\n", __func__);
		वापस -1;
	पूर्ण

	rc = crypto_shash_setkey(ses->server->secmech.hmacmd5,
				 ntlmv2_hash, CIFS_HMAC_MD5_HASH_SIZE);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not set NTLMV2 Hash as a key\n",
			 __func__);
		वापस rc;
	पूर्ण

	rc = crypto_shash_init(&ses->server->secmech.sdeschmacmd5->shash);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not init hmacmd5\n", __func__);
		वापस rc;
	पूर्ण

	अगर (ses->server->negflavor == CIFS_NEGFLAVOR_EXTENDED)
		स_नकल(ntlmv2->challenge.key,
		       ses->ntlmssp->cryptkey, CIFS_SERVER_CHALLENGE_SIZE);
	अन्यथा
		स_नकल(ntlmv2->challenge.key,
		       ses->server->cryptkey, CIFS_SERVER_CHALLENGE_SIZE);
	rc = crypto_shash_update(&ses->server->secmech.sdeschmacmd5->shash,
				 ntlmv2->challenge.key, hash_len);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not update with response\n", __func__);
		वापस rc;
	पूर्ण

	/* Note that the MD5 digest over ग_लिखोs anon.challenge_key.key */
	rc = crypto_shash_final(&ses->server->secmech.sdeschmacmd5->shash,
				ntlmv2->ntlmv2_hash);
	अगर (rc)
		cअगरs_dbg(VFS, "%s: Could not generate md5 hash\n", __func__);

	वापस rc;
पूर्ण

पूर्णांक
setup_ntlmv2_rsp(काष्ठा cअगरs_ses *ses, स्थिर काष्ठा nls_table *nls_cp)
अणु
	पूर्णांक rc;
	पूर्णांक baselen;
	अचिन्हित पूर्णांक tilen;
	काष्ठा ntlmv2_resp *ntlmv2;
	अक्षर ntlmv2_hash[16];
	अचिन्हित अक्षर *tiblob = शून्य; /* target info blob */
	__le64 rsp_बारtamp;

	अगर (nls_cp == शून्य) अणु
		cअगरs_dbg(VFS, "%s called with nls_cp==NULL\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (ses->server->negflavor == CIFS_NEGFLAVOR_EXTENDED) अणु
		अगर (!ses->करोमुख्यName) अणु
			अगर (ses->करोमुख्यAuto) अणु
				rc = find_करोमुख्य_name(ses, nls_cp);
				अगर (rc) अणु
					cअगरs_dbg(VFS, "error %d finding domain name\n",
						 rc);
					जाओ setup_ntlmv2_rsp_ret;
				पूर्ण
			पूर्ण अन्यथा अणु
				ses->करोमुख्यName = kstrdup("", GFP_KERNEL);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = build_avpair_blob(ses, nls_cp);
		अगर (rc) अणु
			cअगरs_dbg(VFS, "error %d building av pair blob\n", rc);
			जाओ setup_ntlmv2_rsp_ret;
		पूर्ण
	पूर्ण

	/* Must be within 5 minutes of the server (or in range +/-2h
	 * in हाल of Mac OS X), so simply carry over server बारtamp
	 * (as Winकरोws 7 करोes)
	 */
	rsp_बारtamp = find_बारtamp(ses);

	baselen = CIFS_SESS_KEY_SIZE + माप(काष्ठा ntlmv2_resp);
	tilen = ses->auth_key.len;
	tiblob = ses->auth_key.response;

	ses->auth_key.response = kदो_स्मृति(baselen + tilen, GFP_KERNEL);
	अगर (!ses->auth_key.response) अणु
		rc = -ENOMEM;
		ses->auth_key.len = 0;
		जाओ setup_ntlmv2_rsp_ret;
	पूर्ण
	ses->auth_key.len += baselen;

	ntlmv2 = (काष्ठा ntlmv2_resp *)
			(ses->auth_key.response + CIFS_SESS_KEY_SIZE);
	ntlmv2->blob_signature = cpu_to_le32(0x00000101);
	ntlmv2->reserved = 0;
	ntlmv2->समय = rsp_बारtamp;

	get_अक्रमom_bytes(&ntlmv2->client_chal, माप(ntlmv2->client_chal));
	ntlmv2->reserved2 = 0;

	स_नकल(ses->auth_key.response + baselen, tiblob, tilen);

	mutex_lock(&ses->server->srv_mutex);

	rc = cअगरs_alloc_hash("hmac(md5)",
			     &ses->server->secmech.hmacmd5,
			     &ses->server->secmech.sdeschmacmd5);
	अगर (rc) अणु
		जाओ unlock;
	पूर्ण

	/* calculate ntlmv2_hash */
	rc = calc_ntlmv2_hash(ses, ntlmv2_hash, nls_cp);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "Could not get v2 hash rc %d\n", rc);
		जाओ unlock;
	पूर्ण

	/* calculate first part of the client response (CR1) */
	rc = CalcNTLMv2_response(ses, ntlmv2_hash);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "Could not calculate CR1 rc: %d\n", rc);
		जाओ unlock;
	पूर्ण

	/* now calculate the session key क्रम NTLMv2 */
	rc = crypto_shash_setkey(ses->server->secmech.hmacmd5,
		ntlmv2_hash, CIFS_HMAC_MD5_HASH_SIZE);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not set NTLMV2 Hash as a key\n",
			 __func__);
		जाओ unlock;
	पूर्ण

	rc = crypto_shash_init(&ses->server->secmech.sdeschmacmd5->shash);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not init hmacmd5\n", __func__);
		जाओ unlock;
	पूर्ण

	rc = crypto_shash_update(&ses->server->secmech.sdeschmacmd5->shash,
		ntlmv2->ntlmv2_hash,
		CIFS_HMAC_MD5_HASH_SIZE);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: Could not update with response\n", __func__);
		जाओ unlock;
	पूर्ण

	rc = crypto_shash_final(&ses->server->secmech.sdeschmacmd5->shash,
		ses->auth_key.response);
	अगर (rc)
		cअगरs_dbg(VFS, "%s: Could not generate md5 hash\n", __func__);

unlock:
	mutex_unlock(&ses->server->srv_mutex);
setup_ntlmv2_rsp_ret:
	kमुक्त(tiblob);

	वापस rc;
पूर्ण

पूर्णांक
calc_seckey(काष्ठा cअगरs_ses *ses)
अणु
	अचिन्हित अक्षर sec_key[CIFS_SESS_KEY_SIZE]; /* a nonce */
	काष्ठा arc4_ctx *ctx_arc4;

	अगर (fips_enabled)
		वापस -ENODEV;

	get_अक्रमom_bytes(sec_key, CIFS_SESS_KEY_SIZE);

	ctx_arc4 = kदो_स्मृति(माप(*ctx_arc4), GFP_KERNEL);
	अगर (!ctx_arc4) अणु
		cअगरs_dbg(VFS, "Could not allocate arc4 context\n");
		वापस -ENOMEM;
	पूर्ण

	arc4_setkey(ctx_arc4, ses->auth_key.response, CIFS_SESS_KEY_SIZE);
	arc4_crypt(ctx_arc4, ses->ntlmssp->ciphertext, sec_key,
		   CIFS_CPHTXT_SIZE);

	/* make secondary_key/nonce as session key */
	स_नकल(ses->auth_key.response, sec_key, CIFS_SESS_KEY_SIZE);
	/* and make len as that of session key only */
	ses->auth_key.len = CIFS_SESS_KEY_SIZE;

	memzero_explicit(sec_key, CIFS_SESS_KEY_SIZE);
	kमुक्त_sensitive(ctx_arc4);
	वापस 0;
पूर्ण

व्योम
cअगरs_crypto_secmech_release(काष्ठा TCP_Server_Info *server)
अणु
	अगर (server->secmech.cmacaes) अणु
		crypto_मुक्त_shash(server->secmech.cmacaes);
		server->secmech.cmacaes = शून्य;
	पूर्ण

	अगर (server->secmech.hmacsha256) अणु
		crypto_मुक्त_shash(server->secmech.hmacsha256);
		server->secmech.hmacsha256 = शून्य;
	पूर्ण

	अगर (server->secmech.md5) अणु
		crypto_मुक्त_shash(server->secmech.md5);
		server->secmech.md5 = शून्य;
	पूर्ण

	अगर (server->secmech.sha512) अणु
		crypto_मुक्त_shash(server->secmech.sha512);
		server->secmech.sha512 = शून्य;
	पूर्ण

	अगर (server->secmech.hmacmd5) अणु
		crypto_मुक्त_shash(server->secmech.hmacmd5);
		server->secmech.hmacmd5 = शून्य;
	पूर्ण

	अगर (server->secmech.ccmaesencrypt) अणु
		crypto_मुक्त_aead(server->secmech.ccmaesencrypt);
		server->secmech.ccmaesencrypt = शून्य;
	पूर्ण

	अगर (server->secmech.ccmaesdecrypt) अणु
		crypto_मुक्त_aead(server->secmech.ccmaesdecrypt);
		server->secmech.ccmaesdecrypt = शून्य;
	पूर्ण

	kमुक्त(server->secmech.sdesccmacaes);
	server->secmech.sdesccmacaes = शून्य;
	kमुक्त(server->secmech.sdeschmacsha256);
	server->secmech.sdeschmacsha256 = शून्य;
	kमुक्त(server->secmech.sdeschmacmd5);
	server->secmech.sdeschmacmd5 = शून्य;
	kमुक्त(server->secmech.sdescmd5);
	server->secmech.sdescmd5 = शून्य;
	kमुक्त(server->secmech.sdescsha512);
	server->secmech.sdescsha512 = शून्य;
पूर्ण
