<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) 2010 Pablo Neira Ayuso <pablo@netfilter.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/netfilter.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>
#समावेश <net/netfilter/nf_conntrack_बारtamp.h>

अटल bool nf_ct_tstamp __पढ़ो_mostly;

module_param_named(tstamp, nf_ct_tstamp, bool, 0644);
MODULE_PARM_DESC(tstamp, "Enable connection tracking flow timestamping.");

अटल स्थिर काष्ठा nf_ct_ext_type tstamp_extend = अणु
	.len	= माप(काष्ठा nf_conn_tstamp),
	.align	= __alignof__(काष्ठा nf_conn_tstamp),
	.id	= NF_CT_EXT_TSTAMP,
पूर्ण;

व्योम nf_conntrack_tstamp_pernet_init(काष्ठा net *net)
अणु
	net->ct.sysctl_tstamp = nf_ct_tstamp;
पूर्ण

पूर्णांक nf_conntrack_tstamp_init(व्योम)
अणु
	पूर्णांक ret;
	ret = nf_ct_extend_रेजिस्टर(&tstamp_extend);
	अगर (ret < 0)
		pr_err("Unable to register extension\n");
	वापस ret;
पूर्ण

व्योम nf_conntrack_tstamp_fini(व्योम)
अणु
	nf_ct_extend_unरेजिस्टर(&tstamp_extend);
पूर्ण
