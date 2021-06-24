<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_RATEEST_MATCH_H
#घोषणा _XT_RATEEST_MATCH_H

#समावेश <linux/types.h>
#समावेश <linux/अगर.h>

क्रमागत xt_rateest_match_flags अणु
	XT_RATEEST_MATCH_INVERT	= 1<<0,
	XT_RATEEST_MATCH_ABS	= 1<<1,
	XT_RATEEST_MATCH_REL	= 1<<2,
	XT_RATEEST_MATCH_DELTA	= 1<<3,
	XT_RATEEST_MATCH_BPS	= 1<<4,
	XT_RATEEST_MATCH_PPS	= 1<<5,
पूर्ण;

क्रमागत xt_rateest_match_mode अणु
	XT_RATEEST_MATCH_NONE,
	XT_RATEEST_MATCH_EQ,
	XT_RATEEST_MATCH_LT,
	XT_RATEEST_MATCH_GT,
पूर्ण;

काष्ठा xt_rateest_match_info अणु
	अक्षर			name1[IFNAMSIZ];
	अक्षर			name2[IFNAMSIZ];
	__u16		flags;
	__u16		mode;
	__u32		bps1;
	__u32		pps1;
	__u32		bps2;
	__u32		pps2;

	/* Used पूर्णांकernally by the kernel */
	काष्ठा xt_rateest	*est1 __attribute__((aligned(8)));
	काष्ठा xt_rateest	*est2 __attribute__((aligned(8)));
पूर्ण;

#पूर्ण_अगर /* _XT_RATEEST_MATCH_H */
