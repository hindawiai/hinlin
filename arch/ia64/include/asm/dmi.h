<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_DMI_H
#घोषणा _ASM_DMI_H 1

#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>

/* Use normal IO mappings क्रम DMI */
#घोषणा dmi_early_remap		ioremap
#घोषणा dmi_early_unmap(x, l)	iounmap(x)
#घोषणा dmi_remap		ioremap
#घोषणा dmi_unmap		iounmap
#घोषणा dmi_alloc(l)		kzalloc(l, GFP_ATOMIC)

#पूर्ण_अगर
