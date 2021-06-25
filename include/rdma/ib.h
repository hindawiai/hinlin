<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2010 Intel Corporation.  All rights reserved.
 */

#अगर_अघोषित _RDMA_IB_H
#घोषणा _RDMA_IB_H

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fs.h>

काष्ठा ib_addr अणु
	जोड़ अणु
		__u8		uib_addr8[16];
		__be16		uib_addr16[8];
		__be32		uib_addr32[4];
		__be64		uib_addr64[2];
	पूर्ण ib_u;
#घोषणा sib_addr8		ib_u.uib_addr8
#घोषणा sib_addr16		ib_u.uib_addr16
#घोषणा sib_addr32		ib_u.uib_addr32
#घोषणा sib_addr64		ib_u.uib_addr64
#घोषणा sib_raw			ib_u.uib_addr8
#घोषणा sib_subnet_prefix	ib_u.uib_addr64[0]
#घोषणा sib_पूर्णांकerface_id	ib_u.uib_addr64[1]
पूर्ण;

अटल अंतरभूत bool ib_addr_any(स्थिर काष्ठा ib_addr *a)
अणु
	वापस ((a->sib_addr64[0] | a->sib_addr64[1]) == 0);
पूर्ण

अटल अंतरभूत bool ib_addr_loopback(स्थिर काष्ठा ib_addr *a)
अणु
	वापस ((a->sib_addr32[0] | a->sib_addr32[1] |
		 a->sib_addr32[2] | (a->sib_addr32[3] ^ htonl(1))) == 0);
पूर्ण

अटल अंतरभूत व्योम ib_addr_set(काष्ठा ib_addr *addr,
			       __be32 w1, __be32 w2, __be32 w3, __be32 w4)
अणु
	addr->sib_addr32[0] = w1;
	addr->sib_addr32[1] = w2;
	addr->sib_addr32[2] = w3;
	addr->sib_addr32[3] = w4;
पूर्ण

अटल अंतरभूत पूर्णांक ib_addr_cmp(स्थिर काष्ठा ib_addr *a1, स्थिर काष्ठा ib_addr *a2)
अणु
	वापस स_भेद(a1, a2, माप(काष्ठा ib_addr));
पूर्ण

काष्ठा sockaddr_ib अणु
	अचिन्हित लघु पूर्णांक	sib_family;	/* AF_IB */
	__be16			sib_pkey;
	__be32			sib_flowinfo;
	काष्ठा ib_addr		sib_addr;
	__be64			sib_sid;
	__be64			sib_sid_mask;
	__u64			sib_scope_id;
पूर्ण;

/*
 * The IB पूर्णांकerfaces that use ग_लिखो() as bi-directional ioctl() are
 * fundamentally unsafe, since there are lots of ways to trigger "write()"
 * calls from various contexts with elevated privileges. That includes the
 * traditional suid executable error message ग_लिखोs, but also various kernel
 * पूर्णांकerfaces that can ग_लिखो to file descriptors.
 *
 * This function provides protection क्रम the legacy API by restricting the
 * calling context.
 */
अटल अंतरभूत bool ib_safe_file_access(काष्ठा file *filp)
अणु
	वापस filp->f_cred == current_cred() && !uaccess_kernel();
पूर्ण

#पूर्ण_अगर /* _RDMA_IB_H */
