<शैली गुरु>
/*
 *   fs/cअगरs/cअगरs_spnego.c -- SPNEGO upcall management क्रम CIFS
 *
 *   Copyright (c) 2007 Red Hat, Inc.
 *   Author(s): Jeff Layton (jlayton@redhat.com)
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

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <keys/user-type.h>
#समावेश <linux/key-type.h>
#समावेश <linux/keyctl.h>
#समावेश <linux/inet.h>
#समावेश "cifsglob.h"
#समावेश "cifs_spnego.h"
#समावेश "cifs_debug.h"
#समावेश "cifsproto.h"
अटल स्थिर काष्ठा cred *spnego_cred;

/* create a new cअगरs key */
अटल पूर्णांक
cअगरs_spnego_key_instantiate(काष्ठा key *key, काष्ठा key_preparsed_payload *prep)
अणु
	अक्षर *payload;
	पूर्णांक ret;

	ret = -ENOMEM;
	payload = kmemdup(prep->data, prep->datalen, GFP_KERNEL);
	अगर (!payload)
		जाओ error;

	/* attach the data */
	key->payload.data[0] = payload;
	ret = 0;

error:
	वापस ret;
पूर्ण

अटल व्योम
cअगरs_spnego_key_destroy(काष्ठा key *key)
अणु
	kमुक्त(key->payload.data[0]);
पूर्ण


/*
 * keytype क्रम CIFS spnego keys
 */
काष्ठा key_type cअगरs_spnego_key_type = अणु
	.name		= "cifs.spnego",
	.instantiate	= cअगरs_spnego_key_instantiate,
	.destroy	= cअगरs_spnego_key_destroy,
	.describe	= user_describe,
पूर्ण;

/* length of दीर्घest version string e.g.  म_माप("ver=0xFF") */
#घोषणा MAX_VER_STR_LEN		8

/* length of दीर्घest security mechanism name, eg in future could have
 * म_माप(";sec=ntlmsspi") */
#घोषणा MAX_MECH_STR_LEN	13

/* म_माप of "host=" */
#घोषणा HOST_KEY_LEN		5

/* म_माप of ";ip4=" or ";ip6=" */
#घोषणा IP_KEY_LEN		5

/* म_माप of ";uid=0x" */
#घोषणा UID_KEY_LEN		7

/* म_माप of ";creduid=0x" */
#घोषणा CREDUID_KEY_LEN		11

/* म_माप of ";user=" */
#घोषणा USER_KEY_LEN		6

/* म_माप of ";pid=0x" */
#घोषणा PID_KEY_LEN		7

/* get a key काष्ठा with a SPNEGO security blob, suitable क्रम session setup */
काष्ठा key *
cअगरs_get_spnego_key(काष्ठा cअगरs_ses *sesInfo)
अणु
	काष्ठा TCP_Server_Info *server = cअगरs_ses_server(sesInfo);
	काष्ठा sockaddr_in *sa = (काष्ठा sockaddr_in *) &server->dstaddr;
	काष्ठा sockaddr_in6 *sa6 = (काष्ठा sockaddr_in6 *) &server->dstaddr;
	अक्षर *description, *dp;
	माप_प्रकार desc_len;
	काष्ठा key *spnego_key;
	स्थिर अक्षर *hostname = server->hostname;
	स्थिर काष्ठा cred *saved_cred;

	/* length of fields (with semicolons): ver=0xyz ip4=ipaddress
	   host=hostname sec=mechanism uid=0xFF user=username */
	desc_len = MAX_VER_STR_LEN +
		   HOST_KEY_LEN + म_माप(hostname) +
		   IP_KEY_LEN + INET6_ADDRSTRLEN +
		   MAX_MECH_STR_LEN +
		   UID_KEY_LEN + (माप(uid_t) * 2) +
		   CREDUID_KEY_LEN + (माप(uid_t) * 2) +
		   PID_KEY_LEN + (माप(pid_t) * 2) + 1;

	अगर (sesInfo->user_name)
		desc_len += USER_KEY_LEN + म_माप(sesInfo->user_name);

	spnego_key = ERR_PTR(-ENOMEM);
	description = kzalloc(desc_len, GFP_KERNEL);
	अगर (description == शून्य)
		जाओ out;

	dp = description;
	/* start with version and hostname portion of UNC string */
	spnego_key = ERR_PTR(-EINVAL);
	प्र_लिखो(dp, "ver=0x%x;host=%s;", CIFS_SPNEGO_UPCALL_VERSION,
		hostname);
	dp = description + म_माप(description);

	/* add the server address */
	अगर (server->dstaddr.ss_family == AF_INET)
		प्र_लिखो(dp, "ip4=%pI4", &sa->sin_addr);
	अन्यथा अगर (server->dstaddr.ss_family == AF_INET6)
		प्र_लिखो(dp, "ip6=%pI6", &sa6->sin6_addr);
	अन्यथा
		जाओ out;

	dp = description + म_माप(description);

	/* क्रम now, only sec=krb5 and sec=mskrb5 are valid */
	अगर (server->sec_kerberos)
		प्र_लिखो(dp, ";sec=krb5");
	अन्यथा अगर (server->sec_mskerberos)
		प्र_लिखो(dp, ";sec=mskrb5");
	अन्यथा अणु
		cअगरs_dbg(VFS, "unknown or missing server auth type, use krb5\n");
		प्र_लिखो(dp, ";sec=krb5");
	पूर्ण

	dp = description + म_माप(description);
	प्र_लिखो(dp, ";uid=0x%x",
		from_kuid_munged(&init_user_ns, sesInfo->linux_uid));

	dp = description + म_माप(description);
	प्र_लिखो(dp, ";creduid=0x%x",
		from_kuid_munged(&init_user_ns, sesInfo->cred_uid));

	अगर (sesInfo->user_name) अणु
		dp = description + म_माप(description);
		प्र_लिखो(dp, ";user=%s", sesInfo->user_name);
	पूर्ण

	dp = description + म_माप(description);
	प्र_लिखो(dp, ";pid=0x%x", current->pid);

	cअगरs_dbg(FYI, "key description = %s\n", description);
	saved_cred = override_creds(spnego_cred);
	spnego_key = request_key(&cअगरs_spnego_key_type, description, "");
	revert_creds(saved_cred);

#अगर_घोषित CONFIG_CIFS_DEBUG2
	अगर (cअगरsFYI && !IS_ERR(spnego_key)) अणु
		काष्ठा cअगरs_spnego_msg *msg = spnego_key->payload.data[0];
		cअगरs_dump_mem("SPNEGO reply blob:", msg->data, min(1024U,
				msg->secblob_len + msg->sesskey_len));
	पूर्ण
#पूर्ण_अगर /* CONFIG_CIFS_DEBUG2 */

out:
	kमुक्त(description);
	वापस spnego_key;
पूर्ण

पूर्णांक
init_cअगरs_spnego(व्योम)
अणु
	काष्ठा cred *cred;
	काष्ठा key *keyring;
	पूर्णांक ret;

	cअगरs_dbg(FYI, "Registering the %s key type\n",
		 cअगरs_spnego_key_type.name);

	/*
	 * Create an override credential set with special thपढ़ो keyring क्रम
	 * spnego upcalls.
	 */

	cred = prepare_kernel_cred(शून्य);
	अगर (!cred)
		वापस -ENOMEM;

	keyring = keyring_alloc(".cifs_spnego",
				GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, cred,
				(KEY_POS_ALL & ~KEY_POS_SETATTR) |
				KEY_USR_VIEW | KEY_USR_READ,
				KEY_ALLOC_NOT_IN_QUOTA, शून्य, शून्य);
	अगर (IS_ERR(keyring)) अणु
		ret = PTR_ERR(keyring);
		जाओ failed_put_cred;
	पूर्ण

	ret = रेजिस्टर_key_type(&cअगरs_spnego_key_type);
	अगर (ret < 0)
		जाओ failed_put_key;

	/*
	 * inकाष्ठा request_key() to use this special keyring as a cache क्रम
	 * the results it looks up
	 */
	set_bit(KEY_FLAG_ROOT_CAN_CLEAR, &keyring->flags);
	cred->thपढ़ो_keyring = keyring;
	cred->jit_keyring = KEY_REQKEY_DEFL_THREAD_KEYRING;
	spnego_cred = cred;

	cअगरs_dbg(FYI, "cifs spnego keyring: %d\n", key_serial(keyring));
	वापस 0;

failed_put_key:
	key_put(keyring);
failed_put_cred:
	put_cred(cred);
	वापस ret;
पूर्ण

व्योम
निकास_cअगरs_spnego(व्योम)
अणु
	key_revoke(spnego_cred->thपढ़ो_keyring);
	unरेजिस्टर_key_type(&cअगरs_spnego_key_type);
	put_cred(spnego_cred);
	cअगरs_dbg(FYI, "Unregistered %s key type\n", cअगरs_spnego_key_type.name);
पूर्ण
