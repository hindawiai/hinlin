<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_DMI_H
#घोषणा _ASM_X86_DMI_H

#समावेश <linux/compiler.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/setup.h>

अटल __always_अंतरभूत __init व्योम *dmi_alloc(अचिन्हित len)
अणु
	वापस extend_brk(len, माप(पूर्णांक));
पूर्ण

/* Use early IO mappings क्रम DMI because it's initialized early */
#घोषणा dmi_early_remap		early_memremap
#घोषणा dmi_early_unmap		early_memunmap
#घोषणा dmi_remap(_x, _l)	memremap(_x, _l, MEMREMAP_WB)
#घोषणा dmi_unmap(_x)		memunmap(_x)

#पूर्ण_अगर /* _ASM_X86_DMI_H */
