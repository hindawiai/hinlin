<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_DMI_H
#घोषणा _ASM_DMI_H

#समावेश <linux/पन.स>
#समावेश <linux/memblock.h>

#घोषणा dmi_early_remap(x, l)		ioremap_cache(x, l)
#घोषणा dmi_early_unmap(x, l)		iounmap(x)
#घोषणा dmi_remap(x, l)			ioremap_cache(x, l)
#घोषणा dmi_unmap(x)			iounmap(x)

/* MIPS initialize DMI scan beक्रमe SLAB is पढ़ोy, so we use memblock here */
#घोषणा dmi_alloc(l)			memblock_alloc_low(l, PAGE_SIZE)

#अगर defined(CONFIG_MACH_LOONGSON64)
#घोषणा SMBIOS_ENTRY_POINT_SCAN_START	0xFFFE000
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_DMI_H */
