<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <net/genetlink.h>
#समावेश <net/ila.h>
#समावेश <net/netns/generic.h>
#समावेश <uapi/linux/genetlink.h>
#समावेश "ila.h"

अटल स्थिर काष्ठा nla_policy ila_nl_policy[ILA_ATTR_MAX + 1] = अणु
	[ILA_ATTR_LOCATOR] = अणु .type = NLA_U64, पूर्ण,
	[ILA_ATTR_LOCATOR_MATCH] = अणु .type = NLA_U64, पूर्ण,
	[ILA_ATTR_IFINDEX] = अणु .type = NLA_U32, पूर्ण,
	[ILA_ATTR_CSUM_MODE] = अणु .type = NLA_U8, पूर्ण,
	[ILA_ATTR_IDENT_TYPE] = अणु .type = NLA_U8, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_ops ila_nl_ops[] = अणु
	अणु
		.cmd = ILA_CMD_ADD,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = ila_xlat_nl_cmd_add_mapping,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = ILA_CMD_DEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = ila_xlat_nl_cmd_del_mapping,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = ILA_CMD_FLUSH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = ila_xlat_nl_cmd_flush,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = ILA_CMD_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = ila_xlat_nl_cmd_get_mapping,
		.start = ila_xlat_nl_dump_start,
		.dumpit = ila_xlat_nl_dump,
		.करोne = ila_xlat_nl_dump_करोne,
	पूर्ण,
पूर्ण;

अचिन्हित पूर्णांक ila_net_id;

काष्ठा genl_family ila_nl_family __ro_after_init = अणु
	.hdrsize	= 0,
	.name		= ILA_GENL_NAME,
	.version	= ILA_GENL_VERSION,
	.maxattr	= ILA_ATTR_MAX,
	.policy = ila_nl_policy,
	.netnsok	= true,
	.parallel_ops	= true,
	.module		= THIS_MODULE,
	.ops		= ila_nl_ops,
	.n_ops		= ARRAY_SIZE(ila_nl_ops),
पूर्ण;

अटल __net_init पूर्णांक ila_init_net(काष्ठा net *net)
अणु
	पूर्णांक err;

	err = ila_xlat_init_net(net);
	अगर (err)
		जाओ ila_xlat_init_fail;

	वापस 0;

ila_xlat_init_fail:
	वापस err;
पूर्ण

अटल __net_निकास व्योम ila_निकास_net(काष्ठा net *net)
अणु
	ila_xlat_निकास_net(net);
पूर्ण

अटल काष्ठा pernet_operations ila_net_ops = अणु
	.init = ila_init_net,
	.निकास = ila_निकास_net,
	.id   = &ila_net_id,
	.size = माप(काष्ठा ila_net),
पूर्ण;

अटल पूर्णांक __init ila_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_pernet_device(&ila_net_ops);
	अगर (ret)
		जाओ रेजिस्टर_device_fail;

	ret = genl_रेजिस्टर_family(&ila_nl_family);
	अगर (ret)
		जाओ रेजिस्टर_family_fail;

	ret = ila_lwt_init();
	अगर (ret)
		जाओ fail_lwt;

	वापस 0;

fail_lwt:
	genl_unरेजिस्टर_family(&ila_nl_family);
रेजिस्टर_family_fail:
	unरेजिस्टर_pernet_device(&ila_net_ops);
रेजिस्टर_device_fail:
	वापस ret;
पूर्ण

अटल व्योम __निकास ila_fini(व्योम)
अणु
	ila_lwt_fini();
	genl_unरेजिस्टर_family(&ila_nl_family);
	unरेजिस्टर_pernet_device(&ila_net_ops);
पूर्ण

module_init(ila_init);
module_निकास(ila_fini);
MODULE_AUTHOR("Tom Herbert <tom@herbertland.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IPv6: Identifier Locator Addressing (ILA)");
