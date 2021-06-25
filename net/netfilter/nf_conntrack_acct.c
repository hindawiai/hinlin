<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Accounting handling क्रम netfilter. */

/*
 * (C) 2008 Krzysztof Piotr Oledzki <ole@ans.pl>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/netfilter.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/export.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>
#समावेश <net/netfilter/nf_conntrack_acct.h>

अटल bool nf_ct_acct __पढ़ो_mostly;

module_param_named(acct, nf_ct_acct, bool, 0644);
MODULE_PARM_DESC(acct, "Enable connection tracking flow accounting.");

अटल स्थिर काष्ठा nf_ct_ext_type acct_extend = अणु
	.len	= माप(काष्ठा nf_conn_acct),
	.align	= __alignof__(काष्ठा nf_conn_acct),
	.id	= NF_CT_EXT_ACCT,
पूर्ण;

व्योम nf_conntrack_acct_pernet_init(काष्ठा net *net)
अणु
	net->ct.sysctl_acct = nf_ct_acct;
पूर्ण

पूर्णांक nf_conntrack_acct_init(व्योम)
अणु
	पूर्णांक ret = nf_ct_extend_रेजिस्टर(&acct_extend);
	अगर (ret < 0)
		pr_err("Unable to register extension\n");
	वापस ret;
पूर्ण

व्योम nf_conntrack_acct_fini(व्योम)
अणु
	nf_ct_extend_unरेजिस्टर(&acct_extend);
पूर्ण
