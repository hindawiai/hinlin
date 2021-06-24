<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_SECMARK_H_target
#घोषणा _XT_SECMARK_H_target

#समावेश <linux/types.h>

/*
 * This is पूर्णांकended क्रम use by various security subप्रणालीs (but not
 * at the same समय).
 *
 * 'mode' refers to the specअगरic security subप्रणाली which the
 * packets are being marked क्रम.
 */
#घोषणा SECMARK_MODE_SEL	0x01		/* SELinux */
#घोषणा SECMARK_SECCTX_MAX	256

काष्ठा xt_secmark_target_info अणु
	__u8 mode;
	__u32 secid;
	अक्षर secctx[SECMARK_SECCTX_MAX];
पूर्ण;

काष्ठा xt_secmark_target_info_v1 अणु
	__u8 mode;
	अक्षर secctx[SECMARK_SECCTX_MAX];
	__u32 secid;
पूर्ण;

#पूर्ण_अगर /*_XT_SECMARK_H_target */
