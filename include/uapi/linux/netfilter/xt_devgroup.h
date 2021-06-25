<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_DEVGROUP_H
#घोषणा _XT_DEVGROUP_H

#समावेश <linux/types.h>

क्रमागत xt_devgroup_flags अणु
	XT_DEVGROUP_MATCH_SRC	= 0x1,
	XT_DEVGROUP_INVERT_SRC	= 0x2,
	XT_DEVGROUP_MATCH_DST	= 0x4,
	XT_DEVGROUP_INVERT_DST	= 0x8,
पूर्ण;

काष्ठा xt_devgroup_info अणु
	__u32	flags;
	__u32	src_group;
	__u32	src_mask;
	__u32	dst_group;
	__u32	dst_mask;
पूर्ण;

#पूर्ण_अगर /* _XT_DEVGROUP_H */
