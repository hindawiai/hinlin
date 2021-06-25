<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Netlink routines क्रम CIFS
 *
 * Copyright (c) 2020 Samuel Cabrero <scabrero@suse.de>
 */

#समावेश <net/genetlink.h>
#समावेश <uapi/linux/cअगरs/cअगरs_netlink.h>

#समावेश "netlink.h"
#समावेश "cifsglob.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_swn.h"

अटल स्थिर काष्ठा nla_policy cअगरs_genl_policy[CIFS_GENL_ATTR_MAX + 1] = अणु
	[CIFS_GENL_ATTR_SWN_REGISTRATION_ID]	= अणु .type = NLA_U32 पूर्ण,
	[CIFS_GENL_ATTR_SWN_NET_NAME]		= अणु .type = NLA_STRING पूर्ण,
	[CIFS_GENL_ATTR_SWN_SHARE_NAME]		= अणु .type = NLA_STRING पूर्ण,
	[CIFS_GENL_ATTR_SWN_IP]			= अणु .len = माप(काष्ठा sockaddr_storage) पूर्ण,
	[CIFS_GENL_ATTR_SWN_NET_NAME_NOTIFY]	= अणु .type = NLA_FLAG पूर्ण,
	[CIFS_GENL_ATTR_SWN_SHARE_NAME_NOTIFY]	= अणु .type = NLA_FLAG पूर्ण,
	[CIFS_GENL_ATTR_SWN_IP_NOTIFY]		= अणु .type = NLA_FLAG पूर्ण,
	[CIFS_GENL_ATTR_SWN_KRB_AUTH]		= अणु .type = NLA_FLAG पूर्ण,
	[CIFS_GENL_ATTR_SWN_USER_NAME]		= अणु .type = NLA_STRING पूर्ण,
	[CIFS_GENL_ATTR_SWN_PASSWORD]		= अणु .type = NLA_STRING पूर्ण,
	[CIFS_GENL_ATTR_SWN_DOMAIN_NAME]	= अणु .type = NLA_STRING पूर्ण,
	[CIFS_GENL_ATTR_SWN_NOTIFICATION_TYPE]	= अणु .type = NLA_U32 पूर्ण,
	[CIFS_GENL_ATTR_SWN_RESOURCE_STATE]	= अणु .type = NLA_U32 पूर्ण,
	[CIFS_GENL_ATTR_SWN_RESOURCE_NAME]	= अणु .type = NLA_STRINGपूर्ण,
पूर्ण;

अटल काष्ठा genl_ops cअगरs_genl_ops[] = अणु
	अणु
		.cmd = CIFS_GENL_CMD_SWN_NOTIFY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = cअगरs_swn_notअगरy,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group cअगरs_genl_mcgrps[] = अणु
	[CIFS_GENL_MCGRP_SWN] = अणु .name = CIFS_GENL_MCGRP_SWN_NAME पूर्ण,
पूर्ण;

काष्ठा genl_family cअगरs_genl_family = अणु
	.name		= CIFS_GENL_NAME,
	.version	= CIFS_GENL_VERSION,
	.hdrsize	= 0,
	.maxattr	= CIFS_GENL_ATTR_MAX,
	.module		= THIS_MODULE,
	.policy		= cअगरs_genl_policy,
	.ops		= cअगरs_genl_ops,
	.n_ops		= ARRAY_SIZE(cअगरs_genl_ops),
	.mcgrps		= cअगरs_genl_mcgrps,
	.n_mcgrps	= ARRAY_SIZE(cअगरs_genl_mcgrps),
पूर्ण;

/**
 * cअगरs_genl_init - Register generic netlink family
 *
 * Return zero अगर initialized successfully, otherwise non-zero.
 */
पूर्णांक cअगरs_genl_init(व्योम)
अणु
	पूर्णांक ret;

	ret = genl_रेजिस्टर_family(&cअगरs_genl_family);
	अगर (ret < 0) अणु
		cअगरs_dbg(VFS, "%s: failed to register netlink family\n",
				__func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cअगरs_genl_निकास - Unरेजिस्टर generic netlink family
 */
व्योम cअगरs_genl_निकास(व्योम)
अणु
	पूर्णांक ret;

	ret = genl_unरेजिस्टर_family(&cअगरs_genl_family);
	अगर (ret < 0) अणु
		cअगरs_dbg(VFS, "%s: failed to unregister netlink family\n",
				__func__);
	पूर्ण
पूर्ण
