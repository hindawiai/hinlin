<शैली गुरु>
/*
 *   fs/cअगरs/sess.c
 *
 *   SMB/CIFS session setup handling routines
 *
 *   Copyright (c) International Business Machines  Corp., 2006, 2009
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

#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_unicode.h"
#समावेश "cifs_debug.h"
#समावेश "ntlmssp.h"
#समावेश "nterr.h"
#समावेश <linux/utsname.h>
#समावेश <linux/slab.h>
#समावेश "cifs_spnego.h"
#समावेश "smb2proto.h"
#समावेश "fs_context.h"

अटल पूर्णांक
cअगरs_ses_add_channel(काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा cअगरs_ses *ses,
		     काष्ठा cअगरs_server_अगरace *अगरace);

bool
is_server_using_अगरace(काष्ठा TCP_Server_Info *server,
		      काष्ठा cअगरs_server_अगरace *अगरace)
अणु
	काष्ठा sockaddr_in *i4 = (काष्ठा sockaddr_in *)&अगरace->sockaddr;
	काष्ठा sockaddr_in6 *i6 = (काष्ठा sockaddr_in6 *)&अगरace->sockaddr;
	काष्ठा sockaddr_in *s4 = (काष्ठा sockaddr_in *)&server->dstaddr;
	काष्ठा sockaddr_in6 *s6 = (काष्ठा sockaddr_in6 *)&server->dstaddr;

	अगर (server->dstaddr.ss_family != अगरace->sockaddr.ss_family)
		वापस false;
	अगर (server->dstaddr.ss_family == AF_INET) अणु
		अगर (s4->sin_addr.s_addr != i4->sin_addr.s_addr)
			वापस false;
	पूर्ण अन्यथा अगर (server->dstaddr.ss_family == AF_INET6) अणु
		अगर (स_भेद(&s6->sin6_addr, &i6->sin6_addr,
			   माप(i6->sin6_addr)) != 0)
			वापस false;
	पूर्ण अन्यथा अणु
		/* unknown family.. */
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

bool is_ses_using_अगरace(काष्ठा cअगरs_ses *ses, काष्ठा cअगरs_server_अगरace *अगरace)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ses->chan_count; i++) अणु
		अगर (is_server_using_अगरace(ses->chans[i].server, अगरace))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* वापसs number of channels added */
पूर्णांक cअगरs_try_adding_channels(काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा cअगरs_ses *ses)
अणु
	पूर्णांक old_chan_count = ses->chan_count;
	पूर्णांक left = ses->chan_max - ses->chan_count;
	पूर्णांक i = 0;
	पूर्णांक rc = 0;
	पूर्णांक tries = 0;
	काष्ठा cअगरs_server_अगरace *अगरaces = शून्य;
	माप_प्रकार अगरace_count;

	अगर (left <= 0) अणु
		cअगरs_dbg(FYI,
			 "ses already at max_channels (%zu), nothing to open\n",
			 ses->chan_max);
		वापस 0;
	पूर्ण

	अगर (ses->server->dialect < SMB30_PROT_ID) अणु
		cअगरs_dbg(VFS, "multichannel is not supported on this protocol version, use 3.0 or above\n");
		वापस 0;
	पूर्ण

	अगर (!(ses->server->capabilities & SMB2_GLOBAL_CAP_MULTI_CHANNEL)) अणु
		cअगरs_dbg(VFS, "server %s does not support multichannel\n", ses->server->hostname);
		ses->chan_max = 1;
		वापस 0;
	पूर्ण

	/*
	 * Make a copy of the अगरace list at the समय and use that
	 * instead so as to not hold the अगरace spinlock क्रम खोलोing
	 * channels
	 */
	spin_lock(&ses->अगरace_lock);
	अगरace_count = ses->अगरace_count;
	अगर (अगरace_count <= 0) अणु
		spin_unlock(&ses->अगरace_lock);
		cअगरs_dbg(VFS, "no iface list available to open channels\n");
		वापस 0;
	पूर्ण
	अगरaces = kmemdup(ses->अगरace_list, अगरace_count*माप(*अगरaces),
			 GFP_ATOMIC);
	अगर (!अगरaces) अणु
		spin_unlock(&ses->अगरace_lock);
		वापस 0;
	पूर्ण
	spin_unlock(&ses->अगरace_lock);

	/*
	 * Keep connecting to same, fastest, अगरace क्रम all channels as
	 * दीर्घ as its RSS. Try next fastest one अगर not RSS or channel
	 * creation fails.
	 */
	जबतक (left > 0) अणु
		काष्ठा cअगरs_server_अगरace *अगरace;

		tries++;
		अगर (tries > 3*ses->chan_max) अणु
			cअगरs_dbg(FYI, "too many channel open attempts (%d channels left to open)\n",
				 left);
			अवरोध;
		पूर्ण

		अगरace = &अगरaces[i];
		अगर (is_ses_using_अगरace(ses, अगरace) && !अगरace->rss_capable) अणु
			i = (i+1) % अगरace_count;
			जारी;
		पूर्ण

		rc = cअगरs_ses_add_channel(cअगरs_sb, ses, अगरace);
		अगर (rc) अणु
			cअगरs_dbg(FYI, "failed to open extra channel on iface#%d rc=%d\n",
				 i, rc);
			i = (i+1) % अगरace_count;
			जारी;
		पूर्ण

		cअगरs_dbg(FYI, "successfully opened new channel on iface#%d\n",
			 i);
		left--;
	पूर्ण

	kमुक्त(अगरaces);
	वापस ses->chan_count - old_chan_count;
पूर्ण

/*
 * If server is a channel of ses, वापस the corresponding enclosing
 * cअगरs_chan otherwise वापस शून्य.
 */
काष्ठा cअगरs_chan *
cअगरs_ses_find_chan(काष्ठा cअगरs_ses *ses, काष्ठा TCP_Server_Info *server)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ses->chan_count; i++) अणु
		अगर (ses->chans[i].server == server)
			वापस &ses->chans[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक
cअगरs_ses_add_channel(काष्ठा cअगरs_sb_info *cअगरs_sb, काष्ठा cअगरs_ses *ses,
		     काष्ठा cअगरs_server_अगरace *अगरace)
अणु
	काष्ठा cअगरs_chan *chan;
	काष्ठा smb3_fs_context ctx = अणुशून्यपूर्ण;
	अटल स्थिर अक्षर unc_fmt[] = "\\%s\\foo";
	अक्षर unc[माप(unc_fmt)+SERVER_NAME_LEN_WITH_शून्य] = अणु0पूर्ण;
	काष्ठा sockaddr_in *ipv4 = (काष्ठा sockaddr_in *)&अगरace->sockaddr;
	काष्ठा sockaddr_in6 *ipv6 = (काष्ठा sockaddr_in6 *)&अगरace->sockaddr;
	पूर्णांक rc;
	अचिन्हित पूर्णांक xid = get_xid();

	अगर (अगरace->sockaddr.ss_family == AF_INET)
		cअगरs_dbg(FYI, "adding channel to ses %p (speed:%zu bps rdma:%s ip:%pI4)\n",
			 ses, अगरace->speed, अगरace->rdma_capable ? "yes" : "no",
			 &ipv4->sin_addr);
	अन्यथा
		cअगरs_dbg(FYI, "adding channel to ses %p (speed:%zu bps rdma:%s ip:%pI4)\n",
			 ses, अगरace->speed, अगरace->rdma_capable ? "yes" : "no",
			 &ipv6->sin6_addr);

	/*
	 * Setup a ctx with mostly the same info as the existing
	 * session and overग_लिखो it with the requested अगरace data.
	 *
	 * We need to setup at least the fields used क्रम negprot and
	 * sesssetup.
	 *
	 * We only need the ctx here, so we can reuse memory from
	 * the session and server without caring about memory
	 * management.
	 */

	/* Always make new connection क्रम now (TODO?) */
	ctx.nosharesock = true;

	/* Auth */
	ctx.करोमुख्यस्वतः = ses->करोमुख्यAuto;
	ctx.करोमुख्यname = ses->करोमुख्यName;
	ctx.username = ses->user_name;
	ctx.password = ses->password;
	ctx.sectype = ses->sectype;
	ctx.sign = ses->sign;

	/* UNC and paths */
	/* XXX: Use ses->server->hostname? */
	प्र_लिखो(unc, unc_fmt, ses->ip_addr);
	ctx.UNC = unc;
	ctx.prepath = "";

	/* Reuse same version as master connection */
	ctx.vals = ses->server->vals;
	ctx.ops = ses->server->ops;

	ctx.noblocksnd = ses->server->noblocksnd;
	ctx.noस्वतःtune = ses->server->noस्वतःtune;
	ctx.sockopt_tcp_nodelay = ses->server->tcp_nodelay;
	ctx.echo_पूर्णांकerval = ses->server->echo_पूर्णांकerval / HZ;
	ctx.max_credits = ses->server->max_credits;

	/*
	 * This will be used क्रम encoding/decoding user/करोमुख्य/pw
	 * during sess setup auth.
	 */
	ctx.local_nls = cअगरs_sb->local_nls;

	/* Use RDMA अगर possible */
	ctx.rdma = अगरace->rdma_capable;
	स_नकल(&ctx.dstaddr, &अगरace->sockaddr, माप(काष्ठा sockaddr_storage));

	/* reuse master con client guid */
	स_नकल(&ctx.client_guid, ses->server->client_guid,
	       SMB2_CLIENT_GUID_SIZE);
	ctx.use_client_guid = true;

	mutex_lock(&ses->session_mutex);

	chan = ses->binding_chan = &ses->chans[ses->chan_count];
	chan->server = cअगरs_get_tcp_session(&ctx);
	अगर (IS_ERR(chan->server)) अणु
		rc = PTR_ERR(chan->server);
		chan->server = शून्य;
		जाओ out;
	पूर्ण
	spin_lock(&cअगरs_tcp_ses_lock);
	chan->server->is_channel = true;
	spin_unlock(&cअगरs_tcp_ses_lock);

	/*
	 * We need to allocate the server crypto now as we will need
	 * to sign packets beक्रमe we generate the channel signing key
	 * (we sign with the session key)
	 */
	rc = smb311_crypto_shash_allocate(chan->server);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "%s: crypto alloc failed\n", __func__);
		जाओ out;
	पूर्ण

	ses->binding = true;
	rc = cअगरs_negotiate_protocol(xid, ses);
	अगर (rc)
		जाओ out;

	rc = cअगरs_setup_session(xid, ses, cअगरs_sb->local_nls);
	अगर (rc)
		जाओ out;

	/* success, put it on the list
	 * XXX: sharing ses between 2 tcp servers is not possible, the
	 * way "internal" linked lists works in linux makes element
	 * only able to beदीर्घ to one list
	 *
	 * the binding session is alपढ़ोy established so the rest of
	 * the code should be able to look it up, no need to add the
	 * ses to the new server.
	 */

	ses->chan_count++;
	atomic_set(&ses->chan_seq, 0);
out:
	ses->binding = false;
	ses->binding_chan = शून्य;
	mutex_unlock(&ses->session_mutex);

	अगर (rc && chan->server)
		cअगरs_put_tcp_session(chan->server, 0);

	वापस rc;
पूर्ण

अटल __u32 cअगरs_ssetup_hdr(काष्ठा cअगरs_ses *ses, SESSION_SETUP_ANDX *pSMB)
अणु
	__u32 capabilities = 0;

	/* init fields common to all four types of SessSetup */
	/* Note that offsets क्रम first seven fields in req काष्ठा are same  */
	/*	in CIFS Specs so करोes not matter which of 3 क्रमms of काष्ठा */
	/*	that we use in next few lines                               */
	/* Note that header is initialized to zero in header_assemble */
	pSMB->req.AndXCommand = 0xFF;
	pSMB->req.MaxBufferSize = cpu_to_le16(min_t(u32,
					CIFSMaxBufSize + MAX_CIFS_HDR_SIZE - 4,
					अच_लघु_उच्च));
	pSMB->req.MaxMpxCount = cpu_to_le16(ses->server->maxReq);
	pSMB->req.VcNumber = cpu_to_le16(1);

	/* Now no need to set SMBFLG_CASELESS or obsolete CANONICAL PATH */

	/* BB verअगरy whether signing required on neg or just on auth frame
	   (and NTLM हाल) */

	capabilities = CAP_LARGE_खाताS | CAP_NT_SMBS | CAP_LEVEL_II_OPLOCKS |
			CAP_LARGE_WRITE_X | CAP_LARGE_READ_X;

	अगर (ses->server->sign)
		pSMB->req.hdr.Flags2 |= SMBFLG2_SECURITY_SIGNATURE;

	अगर (ses->capabilities & CAP_UNICODE) अणु
		pSMB->req.hdr.Flags2 |= SMBFLG2_UNICODE;
		capabilities |= CAP_UNICODE;
	पूर्ण
	अगर (ses->capabilities & CAP_STATUS32) अणु
		pSMB->req.hdr.Flags2 |= SMBFLG2_ERR_STATUS;
		capabilities |= CAP_STATUS32;
	पूर्ण
	अगर (ses->capabilities & CAP_DFS) अणु
		pSMB->req.hdr.Flags2 |= SMBFLG2_DFS;
		capabilities |= CAP_DFS;
	पूर्ण
	अगर (ses->capabilities & CAP_UNIX)
		capabilities |= CAP_UNIX;

	वापस capabilities;
पूर्ण

अटल व्योम
unicode_oslm_strings(अक्षर **pbcc_area, स्थिर काष्ठा nls_table *nls_cp)
अणु
	अक्षर *bcc_ptr = *pbcc_area;
	पूर्णांक bytes_ret = 0;

	/* Copy OS version */
	bytes_ret = cअगरs_strtoUTF16((__le16 *)bcc_ptr, "Linux version ", 32,
				    nls_cp);
	bcc_ptr += 2 * bytes_ret;
	bytes_ret = cअगरs_strtoUTF16((__le16 *) bcc_ptr, init_utsname()->release,
				    32, nls_cp);
	bcc_ptr += 2 * bytes_ret;
	bcc_ptr += 2; /* trailing null */

	bytes_ret = cअगरs_strtoUTF16((__le16 *) bcc_ptr, CIFS_NETWORK_OPSYS,
				    32, nls_cp);
	bcc_ptr += 2 * bytes_ret;
	bcc_ptr += 2; /* trailing null */

	*pbcc_area = bcc_ptr;
पूर्ण

अटल व्योम unicode_करोमुख्य_string(अक्षर **pbcc_area, काष्ठा cअगरs_ses *ses,
				   स्थिर काष्ठा nls_table *nls_cp)
अणु
	अक्षर *bcc_ptr = *pbcc_area;
	पूर्णांक bytes_ret = 0;

	/* copy करोमुख्य */
	अगर (ses->करोमुख्यName == शून्य) अणु
		/* Sending null करोमुख्य better than using a bogus करोमुख्य name (as
		we did briefly in 2.6.18) since server will use its शेष */
		*bcc_ptr = 0;
		*(bcc_ptr+1) = 0;
		bytes_ret = 0;
	पूर्ण अन्यथा
		bytes_ret = cअगरs_strtoUTF16((__le16 *) bcc_ptr, ses->करोमुख्यName,
					    CIFS_MAX_DOMAINNAME_LEN, nls_cp);
	bcc_ptr += 2 * bytes_ret;
	bcc_ptr += 2;  /* account क्रम null terminator */

	*pbcc_area = bcc_ptr;
पूर्ण


अटल व्योम unicode_ssetup_strings(अक्षर **pbcc_area, काष्ठा cअगरs_ses *ses,
				   स्थिर काष्ठा nls_table *nls_cp)
अणु
	अक्षर *bcc_ptr = *pbcc_area;
	पूर्णांक bytes_ret = 0;

	/* BB FIXME add check that strings total less
	than 335 or will need to send them as arrays */

	/* unicode strings, must be word aligned beक्रमe the call */
/*	अगर ((दीर्घ) bcc_ptr % 2)	अणु
		*bcc_ptr = 0;
		bcc_ptr++;
	पूर्ण */
	/* copy user */
	अगर (ses->user_name == शून्य) अणु
		/* null user mount */
		*bcc_ptr = 0;
		*(bcc_ptr+1) = 0;
	पूर्ण अन्यथा अणु
		bytes_ret = cअगरs_strtoUTF16((__le16 *) bcc_ptr, ses->user_name,
					    CIFS_MAX_USERNAME_LEN, nls_cp);
	पूर्ण
	bcc_ptr += 2 * bytes_ret;
	bcc_ptr += 2; /* account क्रम null termination */

	unicode_करोमुख्य_string(&bcc_ptr, ses, nls_cp);
	unicode_oslm_strings(&bcc_ptr, nls_cp);

	*pbcc_area = bcc_ptr;
पूर्ण

अटल व्योम ascii_ssetup_strings(अक्षर **pbcc_area, काष्ठा cअगरs_ses *ses,
				 स्थिर काष्ठा nls_table *nls_cp)
अणु
	अक्षर *bcc_ptr = *pbcc_area;
	पूर्णांक len;

	/* copy user */
	/* BB what about null user mounts - check that we करो this BB */
	/* copy user */
	अगर (ses->user_name != शून्य) अणु
		len = strscpy(bcc_ptr, ses->user_name, CIFS_MAX_USERNAME_LEN);
		अगर (WARN_ON_ONCE(len < 0))
			len = CIFS_MAX_USERNAME_LEN - 1;
		bcc_ptr += len;
	पूर्ण
	/* अन्यथा null user mount */
	*bcc_ptr = 0;
	bcc_ptr++; /* account क्रम null termination */

	/* copy करोमुख्य */
	अगर (ses->करोमुख्यName != शून्य) अणु
		len = strscpy(bcc_ptr, ses->करोमुख्यName, CIFS_MAX_DOMAINNAME_LEN);
		अगर (WARN_ON_ONCE(len < 0))
			len = CIFS_MAX_DOMAINNAME_LEN - 1;
		bcc_ptr += len;
	पूर्ण /* अन्यथा we will send a null करोमुख्य name
	     so the server will शेष to its own करोमुख्य */
	*bcc_ptr = 0;
	bcc_ptr++;

	/* BB check क्रम overflow here */

	म_नकल(bcc_ptr, "Linux version ");
	bcc_ptr += म_माप("Linux version ");
	म_नकल(bcc_ptr, init_utsname()->release);
	bcc_ptr += म_माप(init_utsname()->release) + 1;

	म_नकल(bcc_ptr, CIFS_NETWORK_OPSYS);
	bcc_ptr += म_माप(CIFS_NETWORK_OPSYS) + 1;

	*pbcc_area = bcc_ptr;
पूर्ण

अटल व्योम
decode_unicode_ssetup(अक्षर **pbcc_area, पूर्णांक bleft, काष्ठा cअगरs_ses *ses,
		      स्थिर काष्ठा nls_table *nls_cp)
अणु
	पूर्णांक len;
	अक्षर *data = *pbcc_area;

	cअगरs_dbg(FYI, "bleft %d\n", bleft);

	kमुक्त(ses->serverOS);
	ses->serverOS = cअगरs_strndup_from_utf16(data, bleft, true, nls_cp);
	cअगरs_dbg(FYI, "serverOS=%s\n", ses->serverOS);
	len = (UniStrnlen((ब_अक्षर_प्रकार *) data, bleft / 2) * 2) + 2;
	data += len;
	bleft -= len;
	अगर (bleft <= 0)
		वापस;

	kमुक्त(ses->serverNOS);
	ses->serverNOS = cअगरs_strndup_from_utf16(data, bleft, true, nls_cp);
	cअगरs_dbg(FYI, "serverNOS=%s\n", ses->serverNOS);
	len = (UniStrnlen((ब_अक्षर_प्रकार *) data, bleft / 2) * 2) + 2;
	data += len;
	bleft -= len;
	अगर (bleft <= 0)
		वापस;

	kमुक्त(ses->serverDoमुख्य);
	ses->serverDoमुख्य = cअगरs_strndup_from_utf16(data, bleft, true, nls_cp);
	cअगरs_dbg(FYI, "serverDomain=%s\n", ses->serverDoमुख्य);

	वापस;
पूर्ण

अटल व्योम decode_ascii_ssetup(अक्षर **pbcc_area, __u16 bleft,
				काष्ठा cअगरs_ses *ses,
				स्थिर काष्ठा nls_table *nls_cp)
अणु
	पूर्णांक len;
	अक्षर *bcc_ptr = *pbcc_area;

	cअगरs_dbg(FYI, "decode sessetup ascii. bleft %d\n", bleft);

	len = strnlen(bcc_ptr, bleft);
	अगर (len >= bleft)
		वापस;

	kमुक्त(ses->serverOS);

	ses->serverOS = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (ses->serverOS) अणु
		स_नकल(ses->serverOS, bcc_ptr, len);
		ses->serverOS[len] = 0;
		अगर (म_भेदन(ses->serverOS, "OS/2", 4) == 0)
			cअगरs_dbg(FYI, "OS/2 server\n");
	पूर्ण

	bcc_ptr += len + 1;
	bleft -= len + 1;

	len = strnlen(bcc_ptr, bleft);
	अगर (len >= bleft)
		वापस;

	kमुक्त(ses->serverNOS);

	ses->serverNOS = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (ses->serverNOS) अणु
		स_नकल(ses->serverNOS, bcc_ptr, len);
		ses->serverNOS[len] = 0;
	पूर्ण

	bcc_ptr += len + 1;
	bleft -= len + 1;

	len = strnlen(bcc_ptr, bleft);
	अगर (len > bleft)
		वापस;

	/* No करोमुख्य field in LANMAN हाल. Doमुख्य is
	   वापसed by old servers in the SMB negprot response */
	/* BB For newer servers which करो not support Unicode,
	   but thus करो वापस करोमुख्य here we could add parsing
	   क्रम it later, but it is not very important */
	cअगरs_dbg(FYI, "ascii: bytes left %d\n", bleft);
पूर्ण

पूर्णांक decode_ntlmssp_challenge(अक्षर *bcc_ptr, पूर्णांक blob_len,
				    काष्ठा cअगरs_ses *ses)
अणु
	अचिन्हित पूर्णांक tioffset; /* challenge message target info area */
	अचिन्हित पूर्णांक tilen; /* challenge message target info area length  */

	CHALLENGE_MESSAGE *pblob = (CHALLENGE_MESSAGE *)bcc_ptr;

	अगर (blob_len < माप(CHALLENGE_MESSAGE)) अणु
		cअगरs_dbg(VFS, "challenge blob len %d too small\n", blob_len);
		वापस -EINVAL;
	पूर्ण

	अगर (स_भेद(pblob->Signature, "NTLMSSP", 8)) अणु
		cअगरs_dbg(VFS, "blob signature incorrect %s\n",
			 pblob->Signature);
		वापस -EINVAL;
	पूर्ण
	अगर (pblob->MessageType != NtLmChallenge) अणु
		cअगरs_dbg(VFS, "Incorrect message type %d\n",
			 pblob->MessageType);
		वापस -EINVAL;
	पूर्ण

	स_नकल(ses->ntlmssp->cryptkey, pblob->Challenge, CIFS_CRYPTO_KEY_SIZE);
	/* BB we could decode pblob->NegotiateFlags; some may be useful */
	/* In particular we can examine sign flags */
	/* BB spec says that अगर AvId field of MsvAvTimestamp is populated then
		we must set the MIC field of the AUTHENTICATE_MESSAGE */
	ses->ntlmssp->server_flags = le32_to_cpu(pblob->NegotiateFlags);
	tioffset = le32_to_cpu(pblob->TargetInfoArray.BufferOffset);
	tilen = le16_to_cpu(pblob->TargetInfoArray.Length);
	अगर (tioffset > blob_len || tioffset + tilen > blob_len) अणु
		cअगरs_dbg(VFS, "tioffset + tilen too high %u + %u\n",
			 tioffset, tilen);
		वापस -EINVAL;
	पूर्ण
	अगर (tilen) अणु
		ses->auth_key.response = kmemdup(bcc_ptr + tioffset, tilen,
						 GFP_KERNEL);
		अगर (!ses->auth_key.response) अणु
			cअगरs_dbg(VFS, "Challenge target info alloc failure\n");
			वापस -ENOMEM;
		पूर्ण
		ses->auth_key.len = tilen;
	पूर्ण

	वापस 0;
पूर्ण

/* BB Move to ntlmssp.c eventually */

/* We करो not दो_स्मृति the blob, it is passed in pbuffer, because
   it is fixed size, and small, making this approach cleaner */
व्योम build_ntlmssp_negotiate_blob(अचिन्हित अक्षर *pbuffer,
					 काष्ठा cअगरs_ses *ses)
अणु
	काष्ठा TCP_Server_Info *server = cअगरs_ses_server(ses);
	NEGOTIATE_MESSAGE *sec_blob = (NEGOTIATE_MESSAGE *)pbuffer;
	__u32 flags;

	स_रखो(pbuffer, 0, माप(NEGOTIATE_MESSAGE));
	स_नकल(sec_blob->Signature, NTLMSSP_SIGNATURE, 8);
	sec_blob->MessageType = NtLmNegotiate;

	/* BB is NTLMV2 session security क्रमmat easier to use here? */
	flags = NTLMSSP_NEGOTIATE_56 |	NTLMSSP_REQUEST_TARGET |
		NTLMSSP_NEGOTIATE_128 | NTLMSSP_NEGOTIATE_UNICODE |
		NTLMSSP_NEGOTIATE_NTLM | NTLMSSP_NEGOTIATE_EXTENDED_SEC |
		NTLMSSP_NEGOTIATE_SEAL;
	अगर (server->sign)
		flags |= NTLMSSP_NEGOTIATE_SIGN;
	अगर (!server->session_estab || ses->ntlmssp->sesskey_per_smbsess)
		flags |= NTLMSSP_NEGOTIATE_KEY_XCH;

	sec_blob->NegotiateFlags = cpu_to_le32(flags);

	sec_blob->WorkstationName.BufferOffset = 0;
	sec_blob->WorkstationName.Length = 0;
	sec_blob->WorkstationName.MaximumLength = 0;

	/* Doमुख्य name is sent on the Challenge not Negotiate NTLMSSP request */
	sec_blob->Doमुख्यName.BufferOffset = 0;
	sec_blob->Doमुख्यName.Length = 0;
	sec_blob->Doमुख्यName.MaximumLength = 0;
पूर्ण

अटल पूर्णांक size_of_ntlmssp_blob(काष्ठा cअगरs_ses *ses)
अणु
	पूर्णांक sz = माप(AUTHENTICATE_MESSAGE) + ses->auth_key.len
		- CIFS_SESS_KEY_SIZE + CIFS_CPHTXT_SIZE + 2;

	अगर (ses->करोमुख्यName)
		sz += 2 * strnlen(ses->करोमुख्यName, CIFS_MAX_DOMAINNAME_LEN);
	अन्यथा
		sz += 2;

	अगर (ses->user_name)
		sz += 2 * strnlen(ses->user_name, CIFS_MAX_USERNAME_LEN);
	अन्यथा
		sz += 2;

	वापस sz;
पूर्ण

पूर्णांक build_ntlmssp_auth_blob(अचिन्हित अक्षर **pbuffer,
					u16 *buflen,
				   काष्ठा cअगरs_ses *ses,
				   स्थिर काष्ठा nls_table *nls_cp)
अणु
	पूर्णांक rc;
	AUTHENTICATE_MESSAGE *sec_blob;
	__u32 flags;
	अचिन्हित अक्षर *पंचांगp;

	rc = setup_ntlmv2_rsp(ses, nls_cp);
	अगर (rc) अणु
		cअगरs_dbg(VFS, "Error %d during NTLMSSP authentication\n", rc);
		*buflen = 0;
		जाओ setup_ntlmv2_ret;
	पूर्ण
	*pbuffer = kदो_स्मृति(size_of_ntlmssp_blob(ses), GFP_KERNEL);
	अगर (!*pbuffer) अणु
		rc = -ENOMEM;
		cअगरs_dbg(VFS, "Error %d during NTLMSSP allocation\n", rc);
		*buflen = 0;
		जाओ setup_ntlmv2_ret;
	पूर्ण
	sec_blob = (AUTHENTICATE_MESSAGE *)*pbuffer;

	स_नकल(sec_blob->Signature, NTLMSSP_SIGNATURE, 8);
	sec_blob->MessageType = NtLmAuthenticate;

	flags = NTLMSSP_NEGOTIATE_56 |
		NTLMSSP_REQUEST_TARGET | NTLMSSP_NEGOTIATE_TARGET_INFO |
		NTLMSSP_NEGOTIATE_128 | NTLMSSP_NEGOTIATE_UNICODE |
		NTLMSSP_NEGOTIATE_NTLM | NTLMSSP_NEGOTIATE_EXTENDED_SEC |
		NTLMSSP_NEGOTIATE_SEAL;
	अगर (ses->server->sign)
		flags |= NTLMSSP_NEGOTIATE_SIGN;
	अगर (!ses->server->session_estab || ses->ntlmssp->sesskey_per_smbsess)
		flags |= NTLMSSP_NEGOTIATE_KEY_XCH;

	पंचांगp = *pbuffer + माप(AUTHENTICATE_MESSAGE);
	sec_blob->NegotiateFlags = cpu_to_le32(flags);

	sec_blob->LmChallengeResponse.BufferOffset =
				cpu_to_le32(माप(AUTHENTICATE_MESSAGE));
	sec_blob->LmChallengeResponse.Length = 0;
	sec_blob->LmChallengeResponse.MaximumLength = 0;

	sec_blob->NtChallengeResponse.BufferOffset =
				cpu_to_le32(पंचांगp - *pbuffer);
	अगर (ses->user_name != शून्य) अणु
		स_नकल(पंचांगp, ses->auth_key.response + CIFS_SESS_KEY_SIZE,
				ses->auth_key.len - CIFS_SESS_KEY_SIZE);
		पंचांगp += ses->auth_key.len - CIFS_SESS_KEY_SIZE;

		sec_blob->NtChallengeResponse.Length =
				cpu_to_le16(ses->auth_key.len - CIFS_SESS_KEY_SIZE);
		sec_blob->NtChallengeResponse.MaximumLength =
				cpu_to_le16(ses->auth_key.len - CIFS_SESS_KEY_SIZE);
	पूर्ण अन्यथा अणु
		/*
		 * करोn't send an NT Response क्रम anonymous access
		 */
		sec_blob->NtChallengeResponse.Length = 0;
		sec_blob->NtChallengeResponse.MaximumLength = 0;
	पूर्ण

	अगर (ses->करोमुख्यName == शून्य) अणु
		sec_blob->Doमुख्यName.BufferOffset = cpu_to_le32(पंचांगp - *pbuffer);
		sec_blob->Doमुख्यName.Length = 0;
		sec_blob->Doमुख्यName.MaximumLength = 0;
		पंचांगp += 2;
	पूर्ण अन्यथा अणु
		पूर्णांक len;
		len = cअगरs_strtoUTF16((__le16 *)पंचांगp, ses->करोमुख्यName,
				      CIFS_MAX_DOMAINNAME_LEN, nls_cp);
		len *= 2; /* unicode is 2 bytes each */
		sec_blob->Doमुख्यName.BufferOffset = cpu_to_le32(पंचांगp - *pbuffer);
		sec_blob->Doमुख्यName.Length = cpu_to_le16(len);
		sec_blob->Doमुख्यName.MaximumLength = cpu_to_le16(len);
		पंचांगp += len;
	पूर्ण

	अगर (ses->user_name == शून्य) अणु
		sec_blob->UserName.BufferOffset = cpu_to_le32(पंचांगp - *pbuffer);
		sec_blob->UserName.Length = 0;
		sec_blob->UserName.MaximumLength = 0;
		पंचांगp += 2;
	पूर्ण अन्यथा अणु
		पूर्णांक len;
		len = cअगरs_strtoUTF16((__le16 *)पंचांगp, ses->user_name,
				      CIFS_MAX_USERNAME_LEN, nls_cp);
		len *= 2; /* unicode is 2 bytes each */
		sec_blob->UserName.BufferOffset = cpu_to_le32(पंचांगp - *pbuffer);
		sec_blob->UserName.Length = cpu_to_le16(len);
		sec_blob->UserName.MaximumLength = cpu_to_le16(len);
		पंचांगp += len;
	पूर्ण

	sec_blob->WorkstationName.BufferOffset = cpu_to_le32(पंचांगp - *pbuffer);
	sec_blob->WorkstationName.Length = 0;
	sec_blob->WorkstationName.MaximumLength = 0;
	पंचांगp += 2;

	अगर (((ses->ntlmssp->server_flags & NTLMSSP_NEGOTIATE_KEY_XCH) ||
		(ses->ntlmssp->server_flags & NTLMSSP_NEGOTIATE_EXTENDED_SEC))
			&& !calc_seckey(ses)) अणु
		स_नकल(पंचांगp, ses->ntlmssp->ciphertext, CIFS_CPHTXT_SIZE);
		sec_blob->SessionKey.BufferOffset = cpu_to_le32(पंचांगp - *pbuffer);
		sec_blob->SessionKey.Length = cpu_to_le16(CIFS_CPHTXT_SIZE);
		sec_blob->SessionKey.MaximumLength =
				cpu_to_le16(CIFS_CPHTXT_SIZE);
		पंचांगp += CIFS_CPHTXT_SIZE;
	पूर्ण अन्यथा अणु
		sec_blob->SessionKey.BufferOffset = cpu_to_le32(पंचांगp - *pbuffer);
		sec_blob->SessionKey.Length = 0;
		sec_blob->SessionKey.MaximumLength = 0;
	पूर्ण

	*buflen = पंचांगp - *pbuffer;
setup_ntlmv2_ret:
	वापस rc;
पूर्ण

क्रमागत securityEnum
cअगरs_select_sectype(काष्ठा TCP_Server_Info *server, क्रमागत securityEnum requested)
अणु
	चयन (server->negflavor) अणु
	हाल CIFS_NEGFLAVOR_EXTENDED:
		चयन (requested) अणु
		हाल Kerberos:
		हाल RawNTLMSSP:
			वापस requested;
		हाल Unspecअगरied:
			अगर (server->sec_ntlmssp &&
			    (global_secflags & CIFSSEC_MAY_NTLMSSP))
				वापस RawNTLMSSP;
			अगर ((server->sec_kerberos || server->sec_mskerberos) &&
			    (global_secflags & CIFSSEC_MAY_KRB5))
				वापस Kerberos;
			fallthrough;
		शेष:
			वापस Unspecअगरied;
		पूर्ण
	हाल CIFS_NEGFLAVOR_UNENCAP:
		चयन (requested) अणु
		हाल NTLM:
		हाल NTLMv2:
			वापस requested;
		हाल Unspecअगरied:
			अगर (global_secflags & CIFSSEC_MAY_NTLMV2)
				वापस NTLMv2;
			अगर (global_secflags & CIFSSEC_MAY_NTLM)
				वापस NTLM;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		fallthrough;	/* to attempt LANMAN authentication next */
	हाल CIFS_NEGFLAVOR_LANMAN:
		चयन (requested) अणु
		हाल LANMAN:
			वापस requested;
		हाल Unspecअगरied:
			अगर (global_secflags & CIFSSEC_MAY_LANMAN)
				वापस LANMAN;
			fallthrough;
		शेष:
			वापस Unspecअगरied;
		पूर्ण
	शेष:
		वापस Unspecअगरied;
	पूर्ण
पूर्ण

काष्ठा sess_data अणु
	अचिन्हित पूर्णांक xid;
	काष्ठा cअगरs_ses *ses;
	काष्ठा nls_table *nls_cp;
	व्योम (*func)(काष्ठा sess_data *);
	पूर्णांक result;

	/* we will send the SMB in three pieces:
	 * a fixed length beginning part, an optional
	 * SPNEGO blob (which can be zero length), and a
	 * last part which will include the strings
	 * and rest of bcc area. This allows us to aव्योम
	 * a large buffer 17K allocation
	 */
	पूर्णांक buf0_type;
	काष्ठा kvec iov[3];
पूर्ण;

अटल पूर्णांक
sess_alloc_buffer(काष्ठा sess_data *sess_data, पूर्णांक wct)
अणु
	पूर्णांक rc;
	काष्ठा cअगरs_ses *ses = sess_data->ses;
	काष्ठा smb_hdr *smb_buf;

	rc = small_smb_init_no_tc(SMB_COM_SESSION_SETUP_ANDX, wct, ses,
				  (व्योम **)&smb_buf);

	अगर (rc)
		वापस rc;

	sess_data->iov[0].iov_base = (अक्षर *)smb_buf;
	sess_data->iov[0].iov_len = be32_to_cpu(smb_buf->smb_buf_length) + 4;
	/*
	 * This variable will be used to clear the buffer
	 * allocated above in हाल of any error in the calling function.
	 */
	sess_data->buf0_type = CIFS_SMALL_BUFFER;

	/* 2000 big enough to fit max user, करोमुख्य, NOS name etc. */
	sess_data->iov[2].iov_base = kदो_स्मृति(2000, GFP_KERNEL);
	अगर (!sess_data->iov[2].iov_base) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त_smb_buf;
	पूर्ण

	वापस 0;

out_मुक्त_smb_buf:
	kमुक्त(smb_buf);
	sess_data->iov[0].iov_base = शून्य;
	sess_data->iov[0].iov_len = 0;
	sess_data->buf0_type = CIFS_NO_BUFFER;
	वापस rc;
पूर्ण

अटल व्योम
sess_मुक्त_buffer(काष्ठा sess_data *sess_data)
अणु

	मुक्त_rsp_buf(sess_data->buf0_type, sess_data->iov[0].iov_base);
	sess_data->buf0_type = CIFS_NO_BUFFER;
	kमुक्त(sess_data->iov[2].iov_base);
पूर्ण

अटल पूर्णांक
sess_establish_session(काष्ठा sess_data *sess_data)
अणु
	काष्ठा cअगरs_ses *ses = sess_data->ses;

	mutex_lock(&ses->server->srv_mutex);
	अगर (!ses->server->session_estab) अणु
		अगर (ses->server->sign) अणु
			ses->server->session_key.response =
				kmemdup(ses->auth_key.response,
				ses->auth_key.len, GFP_KERNEL);
			अगर (!ses->server->session_key.response) अणु
				mutex_unlock(&ses->server->srv_mutex);
				वापस -ENOMEM;
			पूर्ण
			ses->server->session_key.len =
						ses->auth_key.len;
		पूर्ण
		ses->server->sequence_number = 0x2;
		ses->server->session_estab = true;
	पूर्ण
	mutex_unlock(&ses->server->srv_mutex);

	cअगरs_dbg(FYI, "CIFS session established successfully\n");
	spin_lock(&GlobalMid_Lock);
	ses->status = CअगरsGood;
	ses->need_reconnect = false;
	spin_unlock(&GlobalMid_Lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
sess_sendreceive(काष्ठा sess_data *sess_data)
अणु
	पूर्णांक rc;
	काष्ठा smb_hdr *smb_buf = (काष्ठा smb_hdr *) sess_data->iov[0].iov_base;
	__u16 count;
	काष्ठा kvec rsp_iov = अणु शून्य, 0 पूर्ण;

	count = sess_data->iov[1].iov_len + sess_data->iov[2].iov_len;
	be32_add_cpu(&smb_buf->smb_buf_length, count);
	put_bcc(count, smb_buf);

	rc = SendReceive2(sess_data->xid, sess_data->ses,
			  sess_data->iov, 3 /* num_iovecs */,
			  &sess_data->buf0_type,
			  CIFS_LOG_ERROR, &rsp_iov);
	cअगरs_small_buf_release(sess_data->iov[0].iov_base);
	स_नकल(&sess_data->iov[0], &rsp_iov, माप(काष्ठा kvec));

	वापस rc;
पूर्ण

/*
 * LANMAN and plaपूर्णांकext are less secure and off by शेष.
 * So we make this explicitly be turned on in kconfig (in the
 * build) and turned on at runसमय (changed from the शेष)
 * in proc/fs/cअगरs or via mount parm.  Unक्रमtunately this is
 * needed क्रम old Win (e.g. Win95), some obscure NAS and OS/2
 */
#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
अटल व्योम
sess_auth_lanman(काष्ठा sess_data *sess_data)
अणु
	पूर्णांक rc = 0;
	काष्ठा smb_hdr *smb_buf;
	SESSION_SETUP_ANDX *pSMB;
	अक्षर *bcc_ptr;
	काष्ठा cअगरs_ses *ses = sess_data->ses;
	अक्षर lnm_session_key[CIFS_AUTH_RESP_SIZE];
	__u16 bytes_reमुख्यing;

	/* lanman 2 style sessionsetup */
	/* wct = 10 */
	rc = sess_alloc_buffer(sess_data, 10);
	अगर (rc)
		जाओ out;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	bcc_ptr = sess_data->iov[2].iov_base;
	(व्योम)cअगरs_ssetup_hdr(ses, pSMB);

	pSMB->req.hdr.Flags2 &= ~SMBFLG2_UNICODE;

	अगर (ses->user_name != शून्य) अणु
		/* no capabilities flags in old lanman negotiation */
		pSMB->old_req.PasswordLength = cpu_to_le16(CIFS_AUTH_RESP_SIZE);

		/* Calculate hash with password and copy पूर्णांकo bcc_ptr.
		 * Encryption Key (stored as in cryptkey) माला_लो used अगर the
		 * security mode bit in Negotiate Protocol response states
		 * to use challenge/response method (i.e. Password bit is 1).
		 */
		rc = calc_lanman_hash(ses->password, ses->server->cryptkey,
				      ses->server->sec_mode & SECMODE_PW_ENCRYPT ?
				      true : false, lnm_session_key);
		अगर (rc)
			जाओ out;

		स_नकल(bcc_ptr, (अक्षर *)lnm_session_key, CIFS_AUTH_RESP_SIZE);
		bcc_ptr += CIFS_AUTH_RESP_SIZE;
	पूर्ण अन्यथा अणु
		pSMB->old_req.PasswordLength = 0;
	पूर्ण

	/*
	 * can not sign अगर LANMAN negotiated so no need
	 * to calculate signing key? but what अगर server
	 * changed to करो higher than lanman dialect and
	 * we reconnected would we ever calc signing_key?
	 */

	cअगरs_dbg(FYI, "Negotiating LANMAN setting up strings\n");
	/* Unicode not allowed क्रम LANMAN dialects */
	ascii_ssetup_strings(&bcc_ptr, ses, sess_data->nls_cp);

	sess_data->iov[2].iov_len = (दीर्घ) bcc_ptr -
			(दीर्घ) sess_data->iov[2].iov_base;

	rc = sess_sendreceive(sess_data);
	अगर (rc)
		जाओ out;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	smb_buf = (काष्ठा smb_hdr *)sess_data->iov[0].iov_base;

	/* lanman response has a word count of 3 */
	अगर (smb_buf->WordCount != 3) अणु
		rc = -EIO;
		cअगरs_dbg(VFS, "bad word count %d\n", smb_buf->WordCount);
		जाओ out;
	पूर्ण

	अगर (le16_to_cpu(pSMB->resp.Action) & GUEST_LOGIN)
		cअगरs_dbg(FYI, "Guest login\n"); /* BB mark SesInfo काष्ठा? */

	ses->Suid = smb_buf->Uid;   /* UID left in wire क्रमmat (le) */
	cअगरs_dbg(FYI, "UID = %llu\n", ses->Suid);

	bytes_reमुख्यing = get_bcc(smb_buf);
	bcc_ptr = pByteArea(smb_buf);

	/* BB check अगर Unicode and decode strings */
	अगर (bytes_reमुख्यing == 0) अणु
		/* no string area to decode, करो nothing */
	पूर्ण अन्यथा अगर (smb_buf->Flags2 & SMBFLG2_UNICODE) अणु
		/* unicode string area must be word-aligned */
		अगर (((अचिन्हित दीर्घ) bcc_ptr - (अचिन्हित दीर्घ) smb_buf) % 2) अणु
			++bcc_ptr;
			--bytes_reमुख्यing;
		पूर्ण
		decode_unicode_ssetup(&bcc_ptr, bytes_reमुख्यing, ses,
				      sess_data->nls_cp);
	पूर्ण अन्यथा अणु
		decode_ascii_ssetup(&bcc_ptr, bytes_reमुख्यing, ses,
				    sess_data->nls_cp);
	पूर्ण

	rc = sess_establish_session(sess_data);
out:
	sess_data->result = rc;
	sess_data->func = शून्य;
	sess_मुक्त_buffer(sess_data);
पूर्ण

#पूर्ण_अगर

अटल व्योम
sess_auth_ntlm(काष्ठा sess_data *sess_data)
अणु
	पूर्णांक rc = 0;
	काष्ठा smb_hdr *smb_buf;
	SESSION_SETUP_ANDX *pSMB;
	अक्षर *bcc_ptr;
	काष्ठा cअगरs_ses *ses = sess_data->ses;
	__u32 capabilities;
	__u16 bytes_reमुख्यing;

	/* old style NTLM sessionsetup */
	/* wct = 13 */
	rc = sess_alloc_buffer(sess_data, 13);
	अगर (rc)
		जाओ out;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	bcc_ptr = sess_data->iov[2].iov_base;
	capabilities = cअगरs_ssetup_hdr(ses, pSMB);

	pSMB->req_no_secext.Capabilities = cpu_to_le32(capabilities);
	अगर (ses->user_name != शून्य) अणु
		pSMB->req_no_secext.CaseInsensitivePasswordLength =
				cpu_to_le16(CIFS_AUTH_RESP_SIZE);
		pSMB->req_no_secext.CaseSensitivePasswordLength =
				cpu_to_le16(CIFS_AUTH_RESP_SIZE);

		/* calculate ntlm response and session key */
		rc = setup_ntlm_response(ses, sess_data->nls_cp);
		अगर (rc) अणु
			cअगरs_dbg(VFS, "Error %d during NTLM authentication\n",
					 rc);
			जाओ out;
		पूर्ण

		/* copy ntlm response */
		स_नकल(bcc_ptr, ses->auth_key.response + CIFS_SESS_KEY_SIZE,
				CIFS_AUTH_RESP_SIZE);
		bcc_ptr += CIFS_AUTH_RESP_SIZE;
		स_नकल(bcc_ptr, ses->auth_key.response + CIFS_SESS_KEY_SIZE,
				CIFS_AUTH_RESP_SIZE);
		bcc_ptr += CIFS_AUTH_RESP_SIZE;
	पूर्ण अन्यथा अणु
		pSMB->req_no_secext.CaseInsensitivePasswordLength = 0;
		pSMB->req_no_secext.CaseSensitivePasswordLength = 0;
	पूर्ण

	अगर (ses->capabilities & CAP_UNICODE) अणु
		/* unicode strings must be word aligned */
		अगर (sess_data->iov[0].iov_len % 2) अणु
			*bcc_ptr = 0;
			bcc_ptr++;
		पूर्ण
		unicode_ssetup_strings(&bcc_ptr, ses, sess_data->nls_cp);
	पूर्ण अन्यथा अणु
		ascii_ssetup_strings(&bcc_ptr, ses, sess_data->nls_cp);
	पूर्ण


	sess_data->iov[2].iov_len = (दीर्घ) bcc_ptr -
			(दीर्घ) sess_data->iov[2].iov_base;

	rc = sess_sendreceive(sess_data);
	अगर (rc)
		जाओ out;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	smb_buf = (काष्ठा smb_hdr *)sess_data->iov[0].iov_base;

	अगर (smb_buf->WordCount != 3) अणु
		rc = -EIO;
		cअगरs_dbg(VFS, "bad word count %d\n", smb_buf->WordCount);
		जाओ out;
	पूर्ण

	अगर (le16_to_cpu(pSMB->resp.Action) & GUEST_LOGIN)
		cअगरs_dbg(FYI, "Guest login\n"); /* BB mark SesInfo काष्ठा? */

	ses->Suid = smb_buf->Uid;   /* UID left in wire क्रमmat (le) */
	cअगरs_dbg(FYI, "UID = %llu\n", ses->Suid);

	bytes_reमुख्यing = get_bcc(smb_buf);
	bcc_ptr = pByteArea(smb_buf);

	/* BB check अगर Unicode and decode strings */
	अगर (bytes_reमुख्यing == 0) अणु
		/* no string area to decode, करो nothing */
	पूर्ण अन्यथा अगर (smb_buf->Flags2 & SMBFLG2_UNICODE) अणु
		/* unicode string area must be word-aligned */
		अगर (((अचिन्हित दीर्घ) bcc_ptr - (अचिन्हित दीर्घ) smb_buf) % 2) अणु
			++bcc_ptr;
			--bytes_reमुख्यing;
		पूर्ण
		decode_unicode_ssetup(&bcc_ptr, bytes_reमुख्यing, ses,
				      sess_data->nls_cp);
	पूर्ण अन्यथा अणु
		decode_ascii_ssetup(&bcc_ptr, bytes_reमुख्यing, ses,
				    sess_data->nls_cp);
	पूर्ण

	rc = sess_establish_session(sess_data);
out:
	sess_data->result = rc;
	sess_data->func = शून्य;
	sess_मुक्त_buffer(sess_data);
	kमुक्त(ses->auth_key.response);
	ses->auth_key.response = शून्य;
पूर्ण

अटल व्योम
sess_auth_ntlmv2(काष्ठा sess_data *sess_data)
अणु
	पूर्णांक rc = 0;
	काष्ठा smb_hdr *smb_buf;
	SESSION_SETUP_ANDX *pSMB;
	अक्षर *bcc_ptr;
	काष्ठा cअगरs_ses *ses = sess_data->ses;
	__u32 capabilities;
	__u16 bytes_reमुख्यing;

	/* old style NTLM sessionsetup */
	/* wct = 13 */
	rc = sess_alloc_buffer(sess_data, 13);
	अगर (rc)
		जाओ out;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	bcc_ptr = sess_data->iov[2].iov_base;
	capabilities = cअगरs_ssetup_hdr(ses, pSMB);

	pSMB->req_no_secext.Capabilities = cpu_to_le32(capabilities);

	/* LM2 password would be here अगर we supported it */
	pSMB->req_no_secext.CaseInsensitivePasswordLength = 0;

	अगर (ses->user_name != शून्य) अणु
		/* calculate nlmv2 response and session key */
		rc = setup_ntlmv2_rsp(ses, sess_data->nls_cp);
		अगर (rc) अणु
			cअगरs_dbg(VFS, "Error %d during NTLMv2 authentication\n", rc);
			जाओ out;
		पूर्ण

		स_नकल(bcc_ptr, ses->auth_key.response + CIFS_SESS_KEY_SIZE,
				ses->auth_key.len - CIFS_SESS_KEY_SIZE);
		bcc_ptr += ses->auth_key.len - CIFS_SESS_KEY_SIZE;

		/* set हाल sensitive password length after tilen may get
		 * asचिन्हित, tilen is 0 otherwise.
		 */
		pSMB->req_no_secext.CaseSensitivePasswordLength =
			cpu_to_le16(ses->auth_key.len - CIFS_SESS_KEY_SIZE);
	पूर्ण अन्यथा अणु
		pSMB->req_no_secext.CaseSensitivePasswordLength = 0;
	पूर्ण

	अगर (ses->capabilities & CAP_UNICODE) अणु
		अगर (sess_data->iov[0].iov_len % 2) अणु
			*bcc_ptr = 0;
			bcc_ptr++;
		पूर्ण
		unicode_ssetup_strings(&bcc_ptr, ses, sess_data->nls_cp);
	पूर्ण अन्यथा अणु
		ascii_ssetup_strings(&bcc_ptr, ses, sess_data->nls_cp);
	पूर्ण


	sess_data->iov[2].iov_len = (दीर्घ) bcc_ptr -
			(दीर्घ) sess_data->iov[2].iov_base;

	rc = sess_sendreceive(sess_data);
	अगर (rc)
		जाओ out;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	smb_buf = (काष्ठा smb_hdr *)sess_data->iov[0].iov_base;

	अगर (smb_buf->WordCount != 3) अणु
		rc = -EIO;
		cअगरs_dbg(VFS, "bad word count %d\n", smb_buf->WordCount);
		जाओ out;
	पूर्ण

	अगर (le16_to_cpu(pSMB->resp.Action) & GUEST_LOGIN)
		cअगरs_dbg(FYI, "Guest login\n"); /* BB mark SesInfo काष्ठा? */

	ses->Suid = smb_buf->Uid;   /* UID left in wire क्रमmat (le) */
	cअगरs_dbg(FYI, "UID = %llu\n", ses->Suid);

	bytes_reमुख्यing = get_bcc(smb_buf);
	bcc_ptr = pByteArea(smb_buf);

	/* BB check अगर Unicode and decode strings */
	अगर (bytes_reमुख्यing == 0) अणु
		/* no string area to decode, करो nothing */
	पूर्ण अन्यथा अगर (smb_buf->Flags2 & SMBFLG2_UNICODE) अणु
		/* unicode string area must be word-aligned */
		अगर (((अचिन्हित दीर्घ) bcc_ptr - (अचिन्हित दीर्घ) smb_buf) % 2) अणु
			++bcc_ptr;
			--bytes_reमुख्यing;
		पूर्ण
		decode_unicode_ssetup(&bcc_ptr, bytes_reमुख्यing, ses,
				      sess_data->nls_cp);
	पूर्ण अन्यथा अणु
		decode_ascii_ssetup(&bcc_ptr, bytes_reमुख्यing, ses,
				    sess_data->nls_cp);
	पूर्ण

	rc = sess_establish_session(sess_data);
out:
	sess_data->result = rc;
	sess_data->func = शून्य;
	sess_मुक्त_buffer(sess_data);
	kमुक्त(ses->auth_key.response);
	ses->auth_key.response = शून्य;
पूर्ण

#अगर_घोषित CONFIG_CIFS_UPCALL
अटल व्योम
sess_auth_kerberos(काष्ठा sess_data *sess_data)
अणु
	पूर्णांक rc = 0;
	काष्ठा smb_hdr *smb_buf;
	SESSION_SETUP_ANDX *pSMB;
	अक्षर *bcc_ptr;
	काष्ठा cअगरs_ses *ses = sess_data->ses;
	__u32 capabilities;
	__u16 bytes_reमुख्यing;
	काष्ठा key *spnego_key = शून्य;
	काष्ठा cअगरs_spnego_msg *msg;
	u16 blob_len;

	/* extended security */
	/* wct = 12 */
	rc = sess_alloc_buffer(sess_data, 12);
	अगर (rc)
		जाओ out;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	bcc_ptr = sess_data->iov[2].iov_base;
	capabilities = cअगरs_ssetup_hdr(ses, pSMB);

	spnego_key = cअगरs_get_spnego_key(ses);
	अगर (IS_ERR(spnego_key)) अणु
		rc = PTR_ERR(spnego_key);
		spnego_key = शून्य;
		जाओ out;
	पूर्ण

	msg = spnego_key->payload.data[0];
	/*
	 * check version field to make sure that cअगरs.upcall is
	 * sending us a response in an expected क्रमm
	 */
	अगर (msg->version != CIFS_SPNEGO_UPCALL_VERSION) अणु
		cअगरs_dbg(VFS, "incorrect version of cifs.upcall (expected %d but got %d)\n",
			 CIFS_SPNEGO_UPCALL_VERSION, msg->version);
		rc = -EKEYREJECTED;
		जाओ out_put_spnego_key;
	पूर्ण

	ses->auth_key.response = kmemdup(msg->data, msg->sesskey_len,
					 GFP_KERNEL);
	अगर (!ses->auth_key.response) अणु
		cअगरs_dbg(VFS, "Kerberos can't allocate (%u bytes) memory\n",
			 msg->sesskey_len);
		rc = -ENOMEM;
		जाओ out_put_spnego_key;
	पूर्ण
	ses->auth_key.len = msg->sesskey_len;

	pSMB->req.hdr.Flags2 |= SMBFLG2_EXT_SEC;
	capabilities |= CAP_EXTENDED_SECURITY;
	pSMB->req.Capabilities = cpu_to_le32(capabilities);
	sess_data->iov[1].iov_base = msg->data + msg->sesskey_len;
	sess_data->iov[1].iov_len = msg->secblob_len;
	pSMB->req.SecurityBlobLength = cpu_to_le16(sess_data->iov[1].iov_len);

	अगर (ses->capabilities & CAP_UNICODE) अणु
		/* unicode strings must be word aligned */
		अगर ((sess_data->iov[0].iov_len
			+ sess_data->iov[1].iov_len) % 2) अणु
			*bcc_ptr = 0;
			bcc_ptr++;
		पूर्ण
		unicode_oslm_strings(&bcc_ptr, sess_data->nls_cp);
		unicode_करोमुख्य_string(&bcc_ptr, ses, sess_data->nls_cp);
	पूर्ण अन्यथा अणु
		/* BB: is this right? */
		ascii_ssetup_strings(&bcc_ptr, ses, sess_data->nls_cp);
	पूर्ण

	sess_data->iov[2].iov_len = (दीर्घ) bcc_ptr -
			(दीर्घ) sess_data->iov[2].iov_base;

	rc = sess_sendreceive(sess_data);
	अगर (rc)
		जाओ out_put_spnego_key;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	smb_buf = (काष्ठा smb_hdr *)sess_data->iov[0].iov_base;

	अगर (smb_buf->WordCount != 4) अणु
		rc = -EIO;
		cअगरs_dbg(VFS, "bad word count %d\n", smb_buf->WordCount);
		जाओ out_put_spnego_key;
	पूर्ण

	अगर (le16_to_cpu(pSMB->resp.Action) & GUEST_LOGIN)
		cअगरs_dbg(FYI, "Guest login\n"); /* BB mark SesInfo काष्ठा? */

	ses->Suid = smb_buf->Uid;   /* UID left in wire क्रमmat (le) */
	cअगरs_dbg(FYI, "UID = %llu\n", ses->Suid);

	bytes_reमुख्यing = get_bcc(smb_buf);
	bcc_ptr = pByteArea(smb_buf);

	blob_len = le16_to_cpu(pSMB->resp.SecurityBlobLength);
	अगर (blob_len > bytes_reमुख्यing) अणु
		cअगरs_dbg(VFS, "bad security blob length %d\n",
				blob_len);
		rc = -EINVAL;
		जाओ out_put_spnego_key;
	पूर्ण
	bcc_ptr += blob_len;
	bytes_reमुख्यing -= blob_len;

	/* BB check अगर Unicode and decode strings */
	अगर (bytes_reमुख्यing == 0) अणु
		/* no string area to decode, करो nothing */
	पूर्ण अन्यथा अगर (smb_buf->Flags2 & SMBFLG2_UNICODE) अणु
		/* unicode string area must be word-aligned */
		अगर (((अचिन्हित दीर्घ) bcc_ptr - (अचिन्हित दीर्घ) smb_buf) % 2) अणु
			++bcc_ptr;
			--bytes_reमुख्यing;
		पूर्ण
		decode_unicode_ssetup(&bcc_ptr, bytes_reमुख्यing, ses,
				      sess_data->nls_cp);
	पूर्ण अन्यथा अणु
		decode_ascii_ssetup(&bcc_ptr, bytes_reमुख्यing, ses,
				    sess_data->nls_cp);
	पूर्ण

	rc = sess_establish_session(sess_data);
out_put_spnego_key:
	key_invalidate(spnego_key);
	key_put(spnego_key);
out:
	sess_data->result = rc;
	sess_data->func = शून्य;
	sess_मुक्त_buffer(sess_data);
	kमुक्त(ses->auth_key.response);
	ses->auth_key.response = शून्य;
पूर्ण

#पूर्ण_अगर /* ! CONFIG_CIFS_UPCALL */

/*
 * The required kvec buffers have to be allocated beक्रमe calling this
 * function.
 */
अटल पूर्णांक
_sess_auth_rawntlmssp_assemble_req(काष्ठा sess_data *sess_data)
अणु
	SESSION_SETUP_ANDX *pSMB;
	काष्ठा cअगरs_ses *ses = sess_data->ses;
	__u32 capabilities;
	अक्षर *bcc_ptr;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;

	capabilities = cअगरs_ssetup_hdr(ses, pSMB);
	अगर ((pSMB->req.hdr.Flags2 & SMBFLG2_UNICODE) == 0) अणु
		cअगरs_dbg(VFS, "NTLMSSP requires Unicode support\n");
		वापस -ENOSYS;
	पूर्ण

	pSMB->req.hdr.Flags2 |= SMBFLG2_EXT_SEC;
	capabilities |= CAP_EXTENDED_SECURITY;
	pSMB->req.Capabilities |= cpu_to_le32(capabilities);

	bcc_ptr = sess_data->iov[2].iov_base;
	/* unicode strings must be word aligned */
	अगर ((sess_data->iov[0].iov_len + sess_data->iov[1].iov_len) % 2) अणु
		*bcc_ptr = 0;
		bcc_ptr++;
	पूर्ण
	unicode_oslm_strings(&bcc_ptr, sess_data->nls_cp);

	sess_data->iov[2].iov_len = (दीर्घ) bcc_ptr -
					(दीर्घ) sess_data->iov[2].iov_base;

	वापस 0;
पूर्ण

अटल व्योम
sess_auth_rawntlmssp_authenticate(काष्ठा sess_data *sess_data);

अटल व्योम
sess_auth_rawntlmssp_negotiate(काष्ठा sess_data *sess_data)
अणु
	पूर्णांक rc;
	काष्ठा smb_hdr *smb_buf;
	SESSION_SETUP_ANDX *pSMB;
	काष्ठा cअगरs_ses *ses = sess_data->ses;
	__u16 bytes_reमुख्यing;
	अक्षर *bcc_ptr;
	u16 blob_len;

	cअगरs_dbg(FYI, "rawntlmssp session setup negotiate phase\n");

	/*
	 * अगर memory allocation is successful, caller of this function
	 * मुक्तs it.
	 */
	ses->ntlmssp = kदो_स्मृति(माप(काष्ठा ntlmssp_auth), GFP_KERNEL);
	अगर (!ses->ntlmssp) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	ses->ntlmssp->sesskey_per_smbsess = false;

	/* wct = 12 */
	rc = sess_alloc_buffer(sess_data, 12);
	अगर (rc)
		जाओ out;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;

	/* Build security blob beक्रमe we assemble the request */
	build_ntlmssp_negotiate_blob(pSMB->req.SecurityBlob, ses);
	sess_data->iov[1].iov_len = माप(NEGOTIATE_MESSAGE);
	sess_data->iov[1].iov_base = pSMB->req.SecurityBlob;
	pSMB->req.SecurityBlobLength = cpu_to_le16(माप(NEGOTIATE_MESSAGE));

	rc = _sess_auth_rawntlmssp_assemble_req(sess_data);
	अगर (rc)
		जाओ out;

	rc = sess_sendreceive(sess_data);

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	smb_buf = (काष्ठा smb_hdr *)sess_data->iov[0].iov_base;

	/* If true, rc here is expected and not an error */
	अगर (sess_data->buf0_type != CIFS_NO_BUFFER &&
	    smb_buf->Status.CअगरsError ==
			cpu_to_le32(NT_STATUS_MORE_PROCESSING_REQUIRED))
		rc = 0;

	अगर (rc)
		जाओ out;

	cअगरs_dbg(FYI, "rawntlmssp session setup challenge phase\n");

	अगर (smb_buf->WordCount != 4) अणु
		rc = -EIO;
		cअगरs_dbg(VFS, "bad word count %d\n", smb_buf->WordCount);
		जाओ out;
	पूर्ण

	ses->Suid = smb_buf->Uid;   /* UID left in wire क्रमmat (le) */
	cअगरs_dbg(FYI, "UID = %llu\n", ses->Suid);

	bytes_reमुख्यing = get_bcc(smb_buf);
	bcc_ptr = pByteArea(smb_buf);

	blob_len = le16_to_cpu(pSMB->resp.SecurityBlobLength);
	अगर (blob_len > bytes_reमुख्यing) अणु
		cअगरs_dbg(VFS, "bad security blob length %d\n",
				blob_len);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	rc = decode_ntlmssp_challenge(bcc_ptr, blob_len, ses);
out:
	sess_मुक्त_buffer(sess_data);

	अगर (!rc) अणु
		sess_data->func = sess_auth_rawntlmssp_authenticate;
		वापस;
	पूर्ण

	/* Else error. Cleanup */
	kमुक्त(ses->auth_key.response);
	ses->auth_key.response = शून्य;
	kमुक्त(ses->ntlmssp);
	ses->ntlmssp = शून्य;

	sess_data->func = शून्य;
	sess_data->result = rc;
पूर्ण

अटल व्योम
sess_auth_rawntlmssp_authenticate(काष्ठा sess_data *sess_data)
अणु
	पूर्णांक rc;
	काष्ठा smb_hdr *smb_buf;
	SESSION_SETUP_ANDX *pSMB;
	काष्ठा cअगरs_ses *ses = sess_data->ses;
	__u16 bytes_reमुख्यing;
	अक्षर *bcc_ptr;
	अचिन्हित अक्षर *ntlmsspblob = शून्य;
	u16 blob_len;

	cअगरs_dbg(FYI, "rawntlmssp session setup authenticate phase\n");

	/* wct = 12 */
	rc = sess_alloc_buffer(sess_data, 12);
	अगर (rc)
		जाओ out;

	/* Build security blob beक्रमe we assemble the request */
	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	smb_buf = (काष्ठा smb_hdr *)pSMB;
	rc = build_ntlmssp_auth_blob(&ntlmsspblob,
					&blob_len, ses, sess_data->nls_cp);
	अगर (rc)
		जाओ out_मुक्त_ntlmsspblob;
	sess_data->iov[1].iov_len = blob_len;
	sess_data->iov[1].iov_base = ntlmsspblob;
	pSMB->req.SecurityBlobLength = cpu_to_le16(blob_len);
	/*
	 * Make sure that we tell the server that we are using
	 * the uid that it just gave us back on the response
	 * (challenge)
	 */
	smb_buf->Uid = ses->Suid;

	rc = _sess_auth_rawntlmssp_assemble_req(sess_data);
	अगर (rc)
		जाओ out_मुक्त_ntlmsspblob;

	rc = sess_sendreceive(sess_data);
	अगर (rc)
		जाओ out_मुक्त_ntlmsspblob;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	smb_buf = (काष्ठा smb_hdr *)sess_data->iov[0].iov_base;
	अगर (smb_buf->WordCount != 4) अणु
		rc = -EIO;
		cअगरs_dbg(VFS, "bad word count %d\n", smb_buf->WordCount);
		जाओ out_मुक्त_ntlmsspblob;
	पूर्ण

	अगर (le16_to_cpu(pSMB->resp.Action) & GUEST_LOGIN)
		cअगरs_dbg(FYI, "Guest login\n"); /* BB mark SesInfo काष्ठा? */

	अगर (ses->Suid != smb_buf->Uid) अणु
		ses->Suid = smb_buf->Uid;
		cअगरs_dbg(FYI, "UID changed! new UID = %llu\n", ses->Suid);
	पूर्ण

	bytes_reमुख्यing = get_bcc(smb_buf);
	bcc_ptr = pByteArea(smb_buf);
	blob_len = le16_to_cpu(pSMB->resp.SecurityBlobLength);
	अगर (blob_len > bytes_reमुख्यing) अणु
		cअगरs_dbg(VFS, "bad security blob length %d\n",
				blob_len);
		rc = -EINVAL;
		जाओ out_मुक्त_ntlmsspblob;
	पूर्ण
	bcc_ptr += blob_len;
	bytes_reमुख्यing -= blob_len;


	/* BB check अगर Unicode and decode strings */
	अगर (bytes_reमुख्यing == 0) अणु
		/* no string area to decode, करो nothing */
	पूर्ण अन्यथा अगर (smb_buf->Flags2 & SMBFLG2_UNICODE) अणु
		/* unicode string area must be word-aligned */
		अगर (((अचिन्हित दीर्घ) bcc_ptr - (अचिन्हित दीर्घ) smb_buf) % 2) अणु
			++bcc_ptr;
			--bytes_reमुख्यing;
		पूर्ण
		decode_unicode_ssetup(&bcc_ptr, bytes_reमुख्यing, ses,
				      sess_data->nls_cp);
	पूर्ण अन्यथा अणु
		decode_ascii_ssetup(&bcc_ptr, bytes_reमुख्यing, ses,
				    sess_data->nls_cp);
	पूर्ण

out_मुक्त_ntlmsspblob:
	kमुक्त(ntlmsspblob);
out:
	sess_मुक्त_buffer(sess_data);

	 अगर (!rc)
		rc = sess_establish_session(sess_data);

	/* Cleanup */
	kमुक्त(ses->auth_key.response);
	ses->auth_key.response = शून्य;
	kमुक्त(ses->ntlmssp);
	ses->ntlmssp = शून्य;

	sess_data->func = शून्य;
	sess_data->result = rc;
पूर्ण

अटल पूर्णांक select_sec(काष्ठा cअगरs_ses *ses, काष्ठा sess_data *sess_data)
अणु
	पूर्णांक type;

	type = cअगरs_select_sectype(ses->server, ses->sectype);
	cअगरs_dbg(FYI, "sess setup type %d\n", type);
	अगर (type == Unspecअगरied) अणु
		cअगरs_dbg(VFS, "Unable to select appropriate authentication method!\n");
		वापस -EINVAL;
	पूर्ण

	चयन (type) अणु
	हाल LANMAN:
		/* LANMAN and plaपूर्णांकext are less secure and off by शेष.
		 * So we make this explicitly be turned on in kconfig (in the
		 * build) and turned on at runसमय (changed from the शेष)
		 * in proc/fs/cअगरs or via mount parm.  Unक्रमtunately this is
		 * needed क्रम old Win (e.g. Win95), some obscure NAS and OS/2 */
#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
		sess_data->func = sess_auth_lanman;
		अवरोध;
#अन्यथा
		वापस -EOPNOTSUPP;
#पूर्ण_अगर
	हाल NTLM:
		sess_data->func = sess_auth_ntlm;
		अवरोध;
	हाल NTLMv2:
		sess_data->func = sess_auth_ntlmv2;
		अवरोध;
	हाल Kerberos:
#अगर_घोषित CONFIG_CIFS_UPCALL
		sess_data->func = sess_auth_kerberos;
		अवरोध;
#अन्यथा
		cअगरs_dbg(VFS, "Kerberos negotiated but upcall support disabled!\n");
		वापस -ENOSYS;
#पूर्ण_अगर /* CONFIG_CIFS_UPCALL */
	हाल RawNTLMSSP:
		sess_data->func = sess_auth_rawntlmssp_negotiate;
		अवरोध;
	शेष:
		cअगरs_dbg(VFS, "secType %d not supported!\n", type);
		वापस -ENOSYS;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक CIFS_SessSetup(स्थिर अचिन्हित पूर्णांक xid, काष्ठा cअगरs_ses *ses,
		    स्थिर काष्ठा nls_table *nls_cp)
अणु
	पूर्णांक rc = 0;
	काष्ठा sess_data *sess_data;

	अगर (ses == शून्य) अणु
		WARN(1, "%s: ses == NULL!", __func__);
		वापस -EINVAL;
	पूर्ण

	sess_data = kzalloc(माप(काष्ठा sess_data), GFP_KERNEL);
	अगर (!sess_data)
		वापस -ENOMEM;

	rc = select_sec(ses, sess_data);
	अगर (rc)
		जाओ out;

	sess_data->xid = xid;
	sess_data->ses = ses;
	sess_data->buf0_type = CIFS_NO_BUFFER;
	sess_data->nls_cp = (काष्ठा nls_table *) nls_cp;

	जबतक (sess_data->func)
		sess_data->func(sess_data);

	/* Store result beक्रमe we मुक्त sess_data */
	rc = sess_data->result;

out:
	kमुक्त(sess_data);
	वापस rc;
पूर्ण
