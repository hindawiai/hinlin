<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_NFACCT_MATCH_H
#घोषणा _XT_NFACCT_MATCH_H

#समावेश <linux/netfilter/nfnetlink_acct.h>

काष्ठा nf_acct;

काष्ठा xt_nfacct_match_info अणु
	अक्षर		name[NFACCT_NAME_MAX];
	काष्ठा nf_acct	*nfacct;
पूर्ण;

काष्ठा xt_nfacct_match_info_v1 अणु
	अक्षर		name[NFACCT_NAME_MAX];
	काष्ठा nf_acct	*nfacct __attribute__((aligned(8)));
पूर्ण;

#पूर्ण_अगर /* _XT_NFACCT_MATCH_H */
