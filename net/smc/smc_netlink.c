<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  Generic netlink support functions to पूर्णांकeract with SMC module
 *
 *  Copyright IBM Corp. 2020
 *
 *  Author(s):	Guvenc Gulce <guvenc@linux.ibm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/mutex.h>
#समावेश <linux/अगर.h>
#समावेश <linux/smc.h>

#समावेश "smc_core.h"
#समावेश "smc_ism.h"
#समावेश "smc_ib.h"
#समावेश "smc_netlink.h"

#घोषणा SMC_CMD_MAX_ATTR 1

/* SMC_GENL generic netlink operation definition */
अटल स्थिर काष्ठा genl_ops smc_gen_nl_ops[] = अणु
	अणु
		.cmd = SMC_NETLINK_GET_SYS_INFO,
		/* can be retrieved by unprivileged users */
		.dumpit = smc_nl_get_sys_info,
	पूर्ण,
	अणु
		.cmd = SMC_NETLINK_GET_LGR_SMCR,
		/* can be retrieved by unprivileged users */
		.dumpit = smcr_nl_get_lgr,
	पूर्ण,
	अणु
		.cmd = SMC_NETLINK_GET_LINK_SMCR,
		/* can be retrieved by unprivileged users */
		.dumpit = smcr_nl_get_link,
	पूर्ण,
	अणु
		.cmd = SMC_NETLINK_GET_LGR_SMCD,
		/* can be retrieved by unprivileged users */
		.dumpit = smcd_nl_get_lgr,
	पूर्ण,
	अणु
		.cmd = SMC_NETLINK_GET_DEV_SMCD,
		/* can be retrieved by unprivileged users */
		.dumpit = smcd_nl_get_device,
	पूर्ण,
	अणु
		.cmd = SMC_NETLINK_GET_DEV_SMCR,
		/* can be retrieved by unprivileged users */
		.dumpit = smcr_nl_get_device,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy smc_gen_nl_policy[2] = अणु
	[SMC_CMD_MAX_ATTR]	= अणु .type = NLA_REJECT, पूर्ण,
पूर्ण;

/* SMC_GENL family definition */
काष्ठा genl_family smc_gen_nl_family __ro_after_init = अणु
	.hdrsize =	0,
	.name =		SMC_GENL_FAMILY_NAME,
	.version =	SMC_GENL_FAMILY_VERSION,
	.maxattr =	SMC_CMD_MAX_ATTR,
	.policy =	smc_gen_nl_policy,
	.netnsok =	true,
	.module =	THIS_MODULE,
	.ops =		smc_gen_nl_ops,
	.n_ops =	ARRAY_SIZE(smc_gen_nl_ops)
पूर्ण;

पूर्णांक __init smc_nl_init(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&smc_gen_nl_family);
पूर्ण

व्योम smc_nl_निकास(व्योम)
अणु
	genl_unरेजिस्टर_family(&smc_gen_nl_family);
पूर्ण
