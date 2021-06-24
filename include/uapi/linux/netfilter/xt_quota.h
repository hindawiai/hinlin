<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_QUOTA_H
#घोषणा _XT_QUOTA_H

#समावेश <linux/types.h>

क्रमागत xt_quota_flags अणु
	XT_QUOTA_INVERT		= 0x1,
पूर्ण;
#घोषणा XT_QUOTA_MASK		0x1

काष्ठा xt_quota_priv;

काष्ठा xt_quota_info अणु
	__u32 flags;
	__u32 pad;
	__aligned_u64 quota;

	/* Used पूर्णांकernally by the kernel */
	काष्ठा xt_quota_priv	*master;
पूर्ण;

#पूर्ण_अगर /* _XT_QUOTA_H */
