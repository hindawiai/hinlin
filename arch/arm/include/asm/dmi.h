<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित __ASM_DMI_H
#घोषणा __ASM_DMI_H

#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#घोषणा dmi_early_remap(x, l)		memremap(x, l, MEMREMAP_WB)
#घोषणा dmi_early_unmap(x, l)		memunmap(x)
#घोषणा dmi_remap(x, l)			memremap(x, l, MEMREMAP_WB)
#घोषणा dmi_unmap(x)			memunmap(x)
#घोषणा dmi_alloc(l)			kzalloc(l, GFP_KERNEL)

#पूर्ण_अगर
