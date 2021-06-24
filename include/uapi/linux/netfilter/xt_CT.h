<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_CT_H
#घोषणा _XT_CT_H

#समावेश <linux/types.h>

क्रमागत अणु
	XT_CT_NOTRACK		= 1 << 0,
	XT_CT_NOTRACK_ALIAS	= 1 << 1,
	XT_CT_ZONE_सूची_ORIG	= 1 << 2,
	XT_CT_ZONE_सूची_REPL	= 1 << 3,
	XT_CT_ZONE_MARK		= 1 << 4,

	XT_CT_MASK		= XT_CT_NOTRACK | XT_CT_NOTRACK_ALIAS |
				  XT_CT_ZONE_सूची_ORIG | XT_CT_ZONE_सूची_REPL |
				  XT_CT_ZONE_MARK,
पूर्ण;

काष्ठा xt_ct_target_info अणु
	__u16 flags;
	__u16 zone;
	__u32 ct_events;
	__u32 exp_events;
	अक्षर helper[16];

	/* Used पूर्णांकernally by the kernel */
	काष्ठा nf_conn	*ct __attribute__((aligned(8)));
पूर्ण;

काष्ठा xt_ct_target_info_v1 अणु
	__u16 flags;
	__u16 zone;
	__u32 ct_events;
	__u32 exp_events;
	अक्षर helper[16];
	अक्षर समयout[32];

	/* Used पूर्णांकernally by the kernel */
	काष्ठा nf_conn	*ct __attribute__((aligned(8)));
पूर्ण;

#पूर्ण_अगर /* _XT_CT_H */
