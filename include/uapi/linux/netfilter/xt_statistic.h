<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_STATISTIC_H
#घोषणा _XT_STATISTIC_H

#समावेश <linux/types.h>

क्रमागत xt_statistic_mode अणु
	XT_STATISTIC_MODE_RANDOM,
	XT_STATISTIC_MODE_NTH,
	__XT_STATISTIC_MODE_MAX
पूर्ण;
#घोषणा XT_STATISTIC_MODE_MAX (__XT_STATISTIC_MODE_MAX - 1)

क्रमागत xt_statistic_flags अणु
	XT_STATISTIC_INVERT		= 0x1,
पूर्ण;
#घोषणा XT_STATISTIC_MASK		0x1

काष्ठा xt_statistic_priv;

काष्ठा xt_statistic_info अणु
	__u16			mode;
	__u16			flags;
	जोड़ अणु
		काष्ठा अणु
			__u32	probability;
		पूर्ण अक्रमom;
		काष्ठा अणु
			__u32	every;
			__u32	packet;
			__u32	count; /* unused */
		पूर्ण nth;
	पूर्ण u;
	काष्ठा xt_statistic_priv *master __attribute__((aligned(8)));
पूर्ण;

#पूर्ण_अगर /* _XT_STATISTIC_H */
