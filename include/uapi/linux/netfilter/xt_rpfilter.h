<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_RPATH_H
#घोषणा _XT_RPATH_H

#समावेश <linux/types.h>

क्रमागत अणु
	XT_RPFILTER_LOOSE = 1 << 0,
	XT_RPFILTER_VALID_MARK = 1 << 1,
	XT_RPFILTER_ACCEPT_LOCAL = 1 << 2,
	XT_RPFILTER_INVERT = 1 << 3,
#अगर_घोषित __KERNEL__
	XT_RPFILTER_OPTION_MASK = XT_RPFILTER_LOOSE |
				  XT_RPFILTER_VALID_MARK |
				  XT_RPFILTER_ACCEPT_LOCAL |
				  XT_RPFILTER_INVERT,
#पूर्ण_अगर
पूर्ण;

काष्ठा xt_rpfilter_info अणु
	__u8 flags;
पूर्ण;

#पूर्ण_अगर
