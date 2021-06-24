<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_XT_PHYSDEV_H
#घोषणा _UAPI_XT_PHYSDEV_H

#समावेश <linux/types.h>
#समावेश <linux/अगर.h>

#घोषणा XT_PHYSDEV_OP_IN		0x01
#घोषणा XT_PHYSDEV_OP_OUT		0x02
#घोषणा XT_PHYSDEV_OP_BRIDGED		0x04
#घोषणा XT_PHYSDEV_OP_ISIN		0x08
#घोषणा XT_PHYSDEV_OP_ISOUT		0x10
#घोषणा XT_PHYSDEV_OP_MASK		(0x20 - 1)

काष्ठा xt_physdev_info अणु
	अक्षर physindev[IFNAMSIZ];
	अक्षर in_mask[IFNAMSIZ];
	अक्षर physoutdev[IFNAMSIZ];
	अक्षर out_mask[IFNAMSIZ];
	__u8 invert;
	__u8 biपंचांगask;
पूर्ण;

#पूर्ण_अगर /* _UAPI_XT_PHYSDEV_H */
