<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ALIGN_H
#घोषणा _LINUX_ALIGN_H

#समावेश <linux/स्थिर.h>

/* @a is a घातer of 2 value */
#घोषणा ALIGN(x, a)		__ALIGN_KERNEL((x), (a))
#घोषणा ALIGN_DOWN(x, a)	__ALIGN_KERNEL((x) - ((a) - 1), (a))
#घोषणा __ALIGN_MASK(x, mask)	__ALIGN_KERNEL_MASK((x), (mask))
#घोषणा PTR_ALIGN(p, a)		((typeof(p))ALIGN((अचिन्हित दीर्घ)(p), (a)))
#घोषणा PTR_ALIGN_DOWN(p, a)	((typeof(p))ALIGN_DOWN((अचिन्हित दीर्घ)(p), (a)))
#घोषणा IS_ALIGNED(x, a)		(((x) & ((typeof(x))(a) - 1)) == 0)

#पूर्ण_अगर	/* _LINUX_ALIGN_H */
