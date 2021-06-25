<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_RATEEST_TARGET_H
#घोषणा _XT_RATEEST_TARGET_H

#समावेश <linux/types.h>
#समावेश <linux/अगर.h>

काष्ठा xt_rateest_target_info अणु
	अक्षर			name[IFNAMSIZ];
	__s8			पूर्णांकerval;
	__u8		ewma_log;

	/* Used पूर्णांकernally by the kernel */
	काष्ठा xt_rateest	*est __attribute__((aligned(8)));
पूर्ण;

#पूर्ण_अगर /* _XT_RATEEST_TARGET_H */
