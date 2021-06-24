<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Witness Service client क्रम CIFS
 *
 * Copyright (c) 2020 Samuel Cabrero <scabrero@suse.de>
 */

#समावेश <linux/kref.h>
#समावेश <net/genetlink.h>
#समावेश <uapi/linux/cअगरs/cअगरs_netlink.h>

#समावेश "cifs_swn.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "fscache.h"
#समावेश "cifs_debug.h"
#समावेश "netlink.h"

अटल DEFINE_IDR(cअगरs_swnreg_idr);
अटल DEFINE_MUTEX(cअगरs_swnreg_idr_mutex);

काष्ठा cअगरs_swn_reg अणु
	पूर्णांक id;
	काष्ठा kref ref_count;

	स्थिर अक्षर *net_name;
	स्थिर अक्षर *share_name;
	bool net_name_notअगरy;
	bool share_name_notअगरy;
	bool ip_notअगरy;

	काष्ठा cअगरs_tcon *tcon;
पूर्ण;

अटल पूर्णांक cअगरs_swn_auth_info_krb(काष्ठा cअगरs_tcon *tcon, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	ret = nla_put_flag(skb, CIFS_GENL_ATTR_SWN_KRB_AUTH);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक cअगरs_swn_auth_info_ntlm(काष्ठा cअगरs_tcon *tcon, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	अगर (tcon->ses->user_name != शून्य) अणु
		ret = nla_put_string(skb, CIFS_GENL_ATTR_SWN_USER_NAME, tcon->ses->user_name);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (tcon->ses->password != शून्य) अणु
		ret = nla_put_string(skb, CIFS_GENL_ATTR_SWN_PASSWORD, tcon->ses->password);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (tcon->ses->करोमुख्यName != शून्य) अणु
		ret = nla_put_string(skb, CIFS_GENL_ATTR_SWN_DOMAIN_NAME, tcon->ses->करोमुख्यName);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Sends a रेजिस्टर message to the userspace daemon based on the registration.
 * The authentication inक्रमmation to connect to the witness service is bundled
 * पूर्णांकo the message.
 */
अटल पूर्णांक cअगरs_swn_send_रेजिस्टर_message(काष्ठा cअगरs_swn_reg *swnreg)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा genlmsghdr *hdr;
	क्रमागत securityEnum authtype;
	काष्ठा sockaddr_storage *addr;
	पूर्णांक ret;

	skb = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (skb == शून्य) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	hdr = genlmsg_put(skb, 0, 0, &cअगरs_genl_family, 0, CIFS_GENL_CMD_SWN_REGISTER);
	अगर (hdr == शून्य) अणु
		ret = -ENOMEM;
		जाओ nlmsg_fail;
	पूर्ण

	ret = nla_put_u32(skb, CIFS_GENL_ATTR_SWN_REGISTRATION_ID, swnreg->id);
	अगर (ret < 0)
		जाओ nlmsg_fail;

	ret = nla_put_string(skb, CIFS_GENL_ATTR_SWN_NET_NAME, swnreg->net_name);
	अगर (ret < 0)
		जाओ nlmsg_fail;

	ret = nla_put_string(skb, CIFS_GENL_ATTR_SWN_SHARE_NAME, swnreg->share_name);
	अगर (ret < 0)
		जाओ nlmsg_fail;

	/*
	 * If there is an address stored use it instead of the server address, because we are
	 * in the process of reconnecting to it after a share has been moved or we have been
	 * told to चयन to it (client move message). In these हालs we unरेजिस्टर from the
	 * server address and रेजिस्टर to the new address when we receive the notअगरication.
	 */
	अगर (swnreg->tcon->ses->server->use_swn_dstaddr)
		addr = &swnreg->tcon->ses->server->swn_dstaddr;
	अन्यथा
		addr = &swnreg->tcon->ses->server->dstaddr;

	ret = nla_put(skb, CIFS_GENL_ATTR_SWN_IP, माप(काष्ठा sockaddr_storage), addr);
	अगर (ret < 0)
		जाओ nlmsg_fail;

	अगर (swnreg->net_name_notअगरy) अणु
		ret = nla_put_flag(skb, CIFS_GENL_ATTR_SWN_NET_NAME_NOTIFY);
		अगर (ret < 0)
			जाओ nlmsg_fail;
	पूर्ण

	अगर (swnreg->share_name_notअगरy) अणु
		ret = nla_put_flag(skb, CIFS_GENL_ATTR_SWN_SHARE_NAME_NOTIFY);
		अगर (ret < 0)
			जाओ nlmsg_fail;
	पूर्ण

	अगर (swnreg->ip_notअगरy) अणु
		ret = nla_put_flag(skb, CIFS_GENL_ATTR_SWN_IP_NOTIFY);
		अगर (ret < 0)
			जाओ nlmsg_fail;
	पूर्ण

	authtype = cअगरs_select_sectype(swnreg->tcon->ses->server, swnreg->tcon->ses->sectype);
	चयन (authtype) अणु
	हाल Kerberos:
		ret = cअगरs_swn_auth_info_krb(swnreg->tcon, skb);
		अगर (ret < 0) अणु
			cअगरs_dbg(VFS, "%s: Failed to get kerberos auth info: %d\n", __func__, ret);
			जाओ nlmsg_fail;
		पूर्ण
		अवरोध;
	हाल LANMAN:
	हाल NTLM:
	हाल NTLMv2:
	हाल RawNTLMSSP:
		ret = cअगरs_swn_auth_info_ntlm(swnreg->tcon, skb);
		अगर (ret < 0) अणु
			cअगरs_dbg(VFS, "%s: Failed to get NTLM auth info: %d\n", __func__, ret);
			जाओ nlmsg_fail;
		पूर्ण
		अवरोध;
	शेष:
		cअगरs_dbg(VFS, "%s: secType %d not supported!\n", __func__, authtype);
		ret = -EINVAL;
		जाओ nlmsg_fail;
	पूर्ण

	genlmsg_end(skb, hdr);
	genlmsg_multicast(&cअगरs_genl_family, skb, 0, CIFS_GENL_MCGRP_SWN, GFP_ATOMIC);

	cअगरs_dbg(FYI, "%s: Message to register for network name %s with id %d sent\n", __func__,
			swnreg->net_name, swnreg->id);

	वापस 0;

nlmsg_fail:
	genlmsg_cancel(skb, hdr);
	nlmsg_मुक्त(skb);
fail:
	वापस ret;
पूर्ण

/*
 * Sends an uरेजिस्टर message to the userspace daemon based on the registration
 */
अटल पूर्णांक cअगरs_swn_send_unरेजिस्टर_message(काष्ठा cअगरs_swn_reg *swnreg)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा genlmsghdr *hdr;
	पूर्णांक ret;

	skb = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	hdr = genlmsg_put(skb, 0, 0, &cअगरs_genl_family, 0, CIFS_GENL_CMD_SWN_UNREGISTER);
	अगर (hdr == शून्य) अणु
		ret = -ENOMEM;
		जाओ nlmsg_fail;
	पूर्ण

	ret = nla_put_u32(skb, CIFS_GENL_ATTR_SWN_REGISTRATION_ID, swnreg->id);
	अगर (ret < 0)
		जाओ nlmsg_fail;

	ret = nla_put_string(skb, CIFS_GENL_ATTR_SWN_NET_NAME, swnreg->net_name);
	अगर (ret < 0)
		जाओ nlmsg_fail;

	ret = nla_put_string(skb, CIFS_GENL_ATTR_SWN_SHARE_NAME, swnreg->share_name);
	अगर (ret < 0)
		जाओ nlmsg_fail;

	ret = nla_put(skb, CIFS_GENL_ATTR_SWN_IP, माप(काष्ठा sockaddr_storage),
			&swnreg->tcon->ses->server->dstaddr);
	अगर (ret < 0)
		जाओ nlmsg_fail;

	अगर (swnreg->net_name_notअगरy) अणु
		ret = nla_put_flag(skb, CIFS_GENL_ATTR_SWN_NET_NAME_NOTIFY);
		अगर (ret < 0)
			जाओ nlmsg_fail;
	पूर्ण

	अगर (swnreg->share_name_notअगरy) अणु
		ret = nla_put_flag(skb, CIFS_GENL_ATTR_SWN_SHARE_NAME_NOTIFY);
		अगर (ret < 0)
			जाओ nlmsg_fail;
	पूर्ण

	अगर (swnreg->ip_notअगरy) अणु
		ret = nla_put_flag(skb, CIFS_GENL_ATTR_SWN_IP_NOTIFY);
		अगर (ret < 0)
			जाओ nlmsg_fail;
	पूर्ण

	genlmsg_end(skb, hdr);
	genlmsg_multicast(&cअगरs_genl_family, skb, 0, CIFS_GENL_MCGRP_SWN, GFP_ATOMIC);

	cअगरs_dbg(FYI, "%s: Message to unregister for network name %s with id %d sent\n", __func__,
			swnreg->net_name, swnreg->id);

	वापस 0;

nlmsg_fail:
	genlmsg_cancel(skb, hdr);
	nlmsg_मुक्त(skb);
	वापस ret;
पूर्ण

/*
 * Try to find a matching registration क्रम the tcon's server name and share name.
 * Calls to this function must be रक्षित by cअगरs_swnreg_idr_mutex.
 * TODO Try to aव्योम memory allocations
 */
अटल काष्ठा cअगरs_swn_reg *cअगरs_find_swn_reg(काष्ठा cअगरs_tcon *tcon)
अणु
	काष्ठा cअगरs_swn_reg *swnreg;
	पूर्णांक id;
	स्थिर अक्षर *share_name;
	स्थिर अक्षर *net_name;

	net_name = extract_hostname(tcon->treeName);
	अगर (IS_ERR(net_name)) अणु
		पूर्णांक ret;

		ret = PTR_ERR(net_name);
		cअगरs_dbg(VFS, "%s: failed to extract host name from target '%s': %d\n",
				__func__, tcon->treeName, ret);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	share_name = extract_shaनाम(tcon->treeName);
	अगर (IS_ERR(share_name)) अणु
		पूर्णांक ret;

		ret = PTR_ERR(share_name);
		cअगरs_dbg(VFS, "%s: failed to extract share name from target '%s': %d\n",
				__func__, tcon->treeName, ret);
		kमुक्त(net_name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	idr_क्रम_each_entry(&cअगरs_swnreg_idr, swnreg, id) अणु
		अगर (strहालcmp(swnreg->net_name, net_name) != 0
		    || strहालcmp(swnreg->share_name, share_name) != 0) अणु
			जारी;
		पूर्ण

		cअगरs_dbg(FYI, "Existing swn registration for %s:%s found\n", swnreg->net_name,
				swnreg->share_name);

		kमुक्त(net_name);
		kमुक्त(share_name);

		वापस swnreg;
	पूर्ण

	kमुक्त(net_name);
	kमुक्त(share_name);

	वापस ERR_PTR(-EEXIST);
पूर्ण

/*
 * Get a registration क्रम the tcon's server and share name, allocating a new one अगर it करोes not
 * exists
 */
अटल काष्ठा cअगरs_swn_reg *cअगरs_get_swn_reg(काष्ठा cअगरs_tcon *tcon)
अणु
	काष्ठा cअगरs_swn_reg *reg = शून्य;
	पूर्णांक ret;

	mutex_lock(&cअगरs_swnreg_idr_mutex);

	/* Check अगर we are alपढ़ोy रेजिस्टरed क्रम this network and share names */
	reg = cअगरs_find_swn_reg(tcon);
	अगर (!IS_ERR(reg)) अणु
		kref_get(&reg->ref_count);
		mutex_unlock(&cअगरs_swnreg_idr_mutex);
		वापस reg;
	पूर्ण अन्यथा अगर (PTR_ERR(reg) != -EEXIST) अणु
		mutex_unlock(&cअगरs_swnreg_idr_mutex);
		वापस reg;
	पूर्ण

	reg = kदो_स्मृति(माप(काष्ठा cअगरs_swn_reg), GFP_ATOMIC);
	अगर (reg == शून्य) अणु
		mutex_unlock(&cअगरs_swnreg_idr_mutex);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	kref_init(&reg->ref_count);

	reg->id = idr_alloc(&cअगरs_swnreg_idr, reg, 1, 0, GFP_ATOMIC);
	अगर (reg->id < 0) अणु
		cअगरs_dbg(FYI, "%s: failed to allocate registration id\n", __func__);
		ret = reg->id;
		जाओ fail;
	पूर्ण

	reg->net_name = extract_hostname(tcon->treeName);
	अगर (IS_ERR(reg->net_name)) अणु
		ret = PTR_ERR(reg->net_name);
		cअगरs_dbg(VFS, "%s: failed to extract host name from target: %d\n", __func__, ret);
		जाओ fail_idr;
	पूर्ण

	reg->share_name = extract_shaनाम(tcon->treeName);
	अगर (IS_ERR(reg->share_name)) अणु
		ret = PTR_ERR(reg->share_name);
		cअगरs_dbg(VFS, "%s: failed to extract share name from target: %d\n", __func__, ret);
		जाओ fail_net_name;
	पूर्ण

	reg->net_name_notअगरy = true;
	reg->share_name_notअगरy = true;
	reg->ip_notअगरy = (tcon->capabilities & SMB2_SHARE_CAP_SCALEOUT);

	reg->tcon = tcon;

	mutex_unlock(&cअगरs_swnreg_idr_mutex);

	वापस reg;

fail_net_name:
	kमुक्त(reg->net_name);
fail_idr:
	idr_हटाओ(&cअगरs_swnreg_idr, reg->id);
fail:
	kमुक्त(reg);
	mutex_unlock(&cअगरs_swnreg_idr_mutex);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम cअगरs_swn_reg_release(काष्ठा kref *ref)
अणु
	काष्ठा cअगरs_swn_reg *swnreg = container_of(ref, काष्ठा cअगरs_swn_reg, ref_count);
	पूर्णांक ret;

	ret = cअगरs_swn_send_unरेजिस्टर_message(swnreg);
	अगर (ret < 0)
		cअगरs_dbg(VFS, "%s: Failed to send unregister message: %d\n", __func__, ret);

	idr_हटाओ(&cअगरs_swnreg_idr, swnreg->id);
	kमुक्त(swnreg->net_name);
	kमुक्त(swnreg->share_name);
	kमुक्त(swnreg);
पूर्ण

अटल व्योम cअगरs_put_swn_reg(काष्ठा cअगरs_swn_reg *swnreg)
अणु
	mutex_lock(&cअगरs_swnreg_idr_mutex);
	kref_put(&swnreg->ref_count, cअगरs_swn_reg_release);
	mutex_unlock(&cअगरs_swnreg_idr_mutex);
पूर्ण

अटल पूर्णांक cअगरs_swn_resource_state_changed(काष्ठा cअगरs_swn_reg *swnreg, स्थिर अक्षर *name, पूर्णांक state)
अणु
	पूर्णांक i;

	चयन (state) अणु
	हाल CIFS_SWN_RESOURCE_STATE_UNAVAILABLE:
		cअगरs_dbg(FYI, "%s: resource name '%s' become unavailable\n", __func__, name);
		क्रम (i = 0; i < swnreg->tcon->ses->chan_count; i++) अणु
			spin_lock(&GlobalMid_Lock);
			अगर (swnreg->tcon->ses->chans[i].server->tcpStatus != CअगरsExiting)
				swnreg->tcon->ses->chans[i].server->tcpStatus = CअगरsNeedReconnect;
			spin_unlock(&GlobalMid_Lock);
		पूर्ण
		अवरोध;
	हाल CIFS_SWN_RESOURCE_STATE_AVAILABLE:
		cअगरs_dbg(FYI, "%s: resource name '%s' become available\n", __func__, name);
		क्रम (i = 0; i < swnreg->tcon->ses->chan_count; i++) अणु
			spin_lock(&GlobalMid_Lock);
			अगर (swnreg->tcon->ses->chans[i].server->tcpStatus != CअगरsExiting)
				swnreg->tcon->ses->chans[i].server->tcpStatus = CअगरsNeedReconnect;
			spin_unlock(&GlobalMid_Lock);
		पूर्ण
		अवरोध;
	हाल CIFS_SWN_RESOURCE_STATE_UNKNOWN:
		cअगरs_dbg(FYI, "%s: resource name '%s' changed to unknown state\n", __func__, name);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool cअगरs_sockaddr_equal(काष्ठा sockaddr_storage *addr1, काष्ठा sockaddr_storage *addr2)
अणु
	अगर (addr1->ss_family != addr2->ss_family)
		वापस false;

	अगर (addr1->ss_family == AF_INET) अणु
		वापस (स_भेद(&((स्थिर काष्ठा sockaddr_in *)addr1)->sin_addr,
				&((स्थिर काष्ठा sockaddr_in *)addr2)->sin_addr,
				माप(काष्ठा in_addr)) == 0);
	पूर्ण

	अगर (addr1->ss_family == AF_INET6) अणु
		वापस (स_भेद(&((स्थिर काष्ठा sockaddr_in6 *)addr1)->sin6_addr,
				&((स्थिर काष्ठा sockaddr_in6 *)addr2)->sin6_addr,
				माप(काष्ठा in6_addr)) == 0);
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक cअगरs_swn_store_swn_addr(स्थिर काष्ठा sockaddr_storage *new,
				   स्थिर काष्ठा sockaddr_storage *old,
				   काष्ठा sockaddr_storage *dst)
अणु
	__be16 port;

	अगर (old->ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *ipv4 = (काष्ठा sockaddr_in *)old;

		port = ipv4->sin_port;
	पूर्ण

	अगर (old->ss_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *ipv6 = (काष्ठा sockaddr_in6 *)old;

		port = ipv6->sin6_port;
	पूर्ण

	अगर (new->ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *ipv4 = (काष्ठा sockaddr_in *)new;

		ipv4->sin_port = port;
	पूर्ण

	अगर (new->ss_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *ipv6 = (काष्ठा sockaddr_in6 *)new;

		ipv6->sin6_port = port;
	पूर्ण

	*dst = *new;

	वापस 0;
पूर्ण

अटल पूर्णांक cअगरs_swn_reconnect(काष्ठा cअगरs_tcon *tcon, काष्ठा sockaddr_storage *addr)
अणु
	पूर्णांक ret = 0;

	/* Store the reconnect address */
	mutex_lock(&tcon->ses->server->srv_mutex);
	अगर (cअगरs_sockaddr_equal(&tcon->ses->server->dstaddr, addr))
		जाओ unlock;

	ret = cअगरs_swn_store_swn_addr(addr, &tcon->ses->server->dstaddr,
				      &tcon->ses->server->swn_dstaddr);
	अगर (ret < 0) अणु
		cअगरs_dbg(VFS, "%s: failed to store address: %d\n", __func__, ret);
		जाओ unlock;
	पूर्ण
	tcon->ses->server->use_swn_dstaddr = true;

	/*
	 * Unरेजिस्टर to stop receiving notअगरications क्रम the old IP address.
	 */
	ret = cअगरs_swn_unरेजिस्टर(tcon);
	अगर (ret < 0) अणु
		cअगरs_dbg(VFS, "%s: Failed to unregister for witness notifications: %d\n",
			 __func__, ret);
		जाओ unlock;
	पूर्ण

	/*
	 * And रेजिस्टर to receive notअगरications क्रम the new IP address now that we have
	 * stored the new address.
	 */
	ret = cअगरs_swn_रेजिस्टर(tcon);
	अगर (ret < 0) अणु
		cअगरs_dbg(VFS, "%s: Failed to register for witness notifications: %d\n",
			 __func__, ret);
		जाओ unlock;
	पूर्ण

	spin_lock(&GlobalMid_Lock);
	अगर (tcon->ses->server->tcpStatus != CअगरsExiting)
		tcon->ses->server->tcpStatus = CअगरsNeedReconnect;
	spin_unlock(&GlobalMid_Lock);

unlock:
	mutex_unlock(&tcon->ses->server->srv_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक cअगरs_swn_client_move(काष्ठा cअगरs_swn_reg *swnreg, काष्ठा sockaddr_storage *addr)
अणु
	काष्ठा sockaddr_in *ipv4 = (काष्ठा sockaddr_in *)addr;
	काष्ठा sockaddr_in6 *ipv6 = (काष्ठा sockaddr_in6 *)addr;

	अगर (addr->ss_family == AF_INET)
		cअगरs_dbg(FYI, "%s: move to %pI4\n", __func__, &ipv4->sin_addr);
	अन्यथा अगर (addr->ss_family == AF_INET6)
		cअगरs_dbg(FYI, "%s: move to %pI6\n", __func__, &ipv6->sin6_addr);

	वापस cअगरs_swn_reconnect(swnreg->tcon, addr);
पूर्ण

पूर्णांक cअगरs_swn_notअगरy(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cअगरs_swn_reg *swnreg;
	अक्षर name[256];
	पूर्णांक type;

	अगर (info->attrs[CIFS_GENL_ATTR_SWN_REGISTRATION_ID]) अणु
		पूर्णांक swnreg_id;

		swnreg_id = nla_get_u32(info->attrs[CIFS_GENL_ATTR_SWN_REGISTRATION_ID]);
		mutex_lock(&cअगरs_swnreg_idr_mutex);
		swnreg = idr_find(&cअगरs_swnreg_idr, swnreg_id);
		mutex_unlock(&cअगरs_swnreg_idr_mutex);
		अगर (swnreg == शून्य) अणु
			cअगरs_dbg(FYI, "%s: registration id %d not found\n", __func__, swnreg_id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		cअगरs_dbg(FYI, "%s: missing registration id attribute\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[CIFS_GENL_ATTR_SWN_NOTIFICATION_TYPE]) अणु
		type = nla_get_u32(info->attrs[CIFS_GENL_ATTR_SWN_NOTIFICATION_TYPE]);
	पूर्ण अन्यथा अणु
		cअगरs_dbg(FYI, "%s: missing notification type attribute\n", __func__);
		वापस -EINVAL;
	पूर्ण

	चयन (type) अणु
	हाल CIFS_SWN_NOTIFICATION_RESOURCE_CHANGE: अणु
		पूर्णांक state;

		अगर (info->attrs[CIFS_GENL_ATTR_SWN_RESOURCE_NAME]) अणु
			nla_strscpy(name, info->attrs[CIFS_GENL_ATTR_SWN_RESOURCE_NAME],
					माप(name));
		पूर्ण अन्यथा अणु
			cअगरs_dbg(FYI, "%s: missing resource name attribute\n", __func__);
			वापस -EINVAL;
		पूर्ण
		अगर (info->attrs[CIFS_GENL_ATTR_SWN_RESOURCE_STATE]) अणु
			state = nla_get_u32(info->attrs[CIFS_GENL_ATTR_SWN_RESOURCE_STATE]);
		पूर्ण अन्यथा अणु
			cअगरs_dbg(FYI, "%s: missing resource state attribute\n", __func__);
			वापस -EINVAL;
		पूर्ण
		वापस cअगरs_swn_resource_state_changed(swnreg, name, state);
	पूर्ण
	हाल CIFS_SWN_NOTIFICATION_CLIENT_MOVE: अणु
		काष्ठा sockaddr_storage addr;

		अगर (info->attrs[CIFS_GENL_ATTR_SWN_IP]) अणु
			nla_स_नकल(&addr, info->attrs[CIFS_GENL_ATTR_SWN_IP], माप(addr));
		पूर्ण अन्यथा अणु
			cअगरs_dbg(FYI, "%s: missing IP address attribute\n", __func__);
			वापस -EINVAL;
		पूर्ण
		वापस cअगरs_swn_client_move(swnreg, &addr);
	पूर्ण
	शेष:
		cअगरs_dbg(FYI, "%s: unknown notification type %d\n", __func__, type);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cअगरs_swn_रेजिस्टर(काष्ठा cअगरs_tcon *tcon)
अणु
	काष्ठा cअगरs_swn_reg *swnreg;
	पूर्णांक ret;

	swnreg = cअगरs_get_swn_reg(tcon);
	अगर (IS_ERR(swnreg))
		वापस PTR_ERR(swnreg);

	ret = cअगरs_swn_send_रेजिस्टर_message(swnreg);
	अगर (ret < 0) अणु
		cअगरs_dbg(VFS, "%s: Failed to send swn register message: %d\n", __func__, ret);
		/* Do not put the swnreg or वापस error, the echo task will retry */
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cअगरs_swn_unरेजिस्टर(काष्ठा cअगरs_tcon *tcon)
अणु
	काष्ठा cअगरs_swn_reg *swnreg;

	mutex_lock(&cअगरs_swnreg_idr_mutex);

	swnreg = cअगरs_find_swn_reg(tcon);
	अगर (IS_ERR(swnreg)) अणु
		mutex_unlock(&cअगरs_swnreg_idr_mutex);
		वापस PTR_ERR(swnreg);
	पूर्ण

	mutex_unlock(&cअगरs_swnreg_idr_mutex);

	cअगरs_put_swn_reg(swnreg);

	वापस 0;
पूर्ण

व्योम cअगरs_swn_dump(काष्ठा seq_file *m)
अणु
	काष्ठा cअगरs_swn_reg *swnreg;
	काष्ठा sockaddr_in *sa;
	काष्ठा sockaddr_in6 *sa6;
	पूर्णांक id;

	seq_माला_दो(m, "Witness registrations:");

	mutex_lock(&cअगरs_swnreg_idr_mutex);
	idr_क्रम_each_entry(&cअगरs_swnreg_idr, swnreg, id) अणु
		seq_म_लिखो(m, "\nId: %u Refs: %u Network name: '%s'%s Share name: '%s'%s Ip address: ",
				id, kref_पढ़ो(&swnreg->ref_count),
				swnreg->net_name, swnreg->net_name_notअगरy ? "(y)" : "(n)",
				swnreg->share_name, swnreg->share_name_notअगरy ? "(y)" : "(n)");
		चयन (swnreg->tcon->ses->server->dstaddr.ss_family) अणु
		हाल AF_INET:
			sa = (काष्ठा sockaddr_in *) &swnreg->tcon->ses->server->dstaddr;
			seq_म_लिखो(m, "%pI4", &sa->sin_addr.s_addr);
			अवरोध;
		हाल AF_INET6:
			sa6 = (काष्ठा sockaddr_in6 *) &swnreg->tcon->ses->server->dstaddr;
			seq_म_लिखो(m, "%pI6", &sa6->sin6_addr.s6_addr);
			अगर (sa6->sin6_scope_id)
				seq_म_लिखो(m, "%%%u", sa6->sin6_scope_id);
			अवरोध;
		शेष:
			seq_माला_दो(m, "(unknown)");
		पूर्ण
		seq_म_लिखो(m, "%s", swnreg->ip_notअगरy ? "(y)" : "(n)");
	पूर्ण
	mutex_unlock(&cअगरs_swnreg_idr_mutex);
	seq_माला_दो(m, "\n");
पूर्ण

व्योम cअगरs_swn_check(व्योम)
अणु
	काष्ठा cअगरs_swn_reg *swnreg;
	पूर्णांक id;
	पूर्णांक ret;

	mutex_lock(&cअगरs_swnreg_idr_mutex);
	idr_क्रम_each_entry(&cअगरs_swnreg_idr, swnreg, id) अणु
		ret = cअगरs_swn_send_रेजिस्टर_message(swnreg);
		अगर (ret < 0)
			cअगरs_dbg(FYI, "%s: Failed to send register message: %d\n", __func__, ret);
	पूर्ण
	mutex_unlock(&cअगरs_swnreg_idr_mutex);
पूर्ण
