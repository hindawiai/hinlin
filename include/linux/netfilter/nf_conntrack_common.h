<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_CONNTRACK_COMMON_H
#घोषणा _NF_CONNTRACK_COMMON_H

#समावेश <linux/atomic.h>
#समावेश <uapi/linux/netfilter/nf_conntrack_common.h>

काष्ठा ip_conntrack_stat अणु
	अचिन्हित पूर्णांक found;
	अचिन्हित पूर्णांक invalid;
	अचिन्हित पूर्णांक insert;
	अचिन्हित पूर्णांक insert_failed;
	अचिन्हित पूर्णांक clash_resolve;
	अचिन्हित पूर्णांक drop;
	अचिन्हित पूर्णांक early_drop;
	अचिन्हित पूर्णांक error;
	अचिन्हित पूर्णांक expect_new;
	अचिन्हित पूर्णांक expect_create;
	अचिन्हित पूर्णांक expect_delete;
	अचिन्हित पूर्णांक search_restart;
पूर्ण;

#घोषणा NFCT_INFOMASK	7UL
#घोषणा NFCT_PTRMASK	~(NFCT_INFOMASK)

काष्ठा nf_conntrack अणु
	atomic_t use;
पूर्ण;

व्योम nf_conntrack_destroy(काष्ठा nf_conntrack *nfct);
अटल अंतरभूत व्योम nf_conntrack_put(काष्ठा nf_conntrack *nfct)
अणु
	अगर (nfct && atomic_dec_and_test(&nfct->use))
		nf_conntrack_destroy(nfct);
पूर्ण
अटल अंतरभूत व्योम nf_conntrack_get(काष्ठा nf_conntrack *nfct)
अणु
	अगर (nfct)
		atomic_inc(&nfct->use);
पूर्ण

#पूर्ण_अगर /* _NF_CONNTRACK_COMMON_H */
