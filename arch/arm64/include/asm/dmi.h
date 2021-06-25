<शैली गुरु>
/*
 * arch/arm64/include/यंत्र/dmi.h
 *
 * Copyright (C) 2013 Linaro Limited.
 * Written by: Yi Li (yi.li@linaro.org)
 *
 * based on arch/ia64/include/यंत्र/dmi.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित __ASM_DMI_H
#घोषणा __ASM_DMI_H

#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

/*
 * According to section 2.3.6 of the UEFI spec, the firmware should not
 * request a भव mapping क्रम configuration tables such as SMBIOS.
 * This means we have to map them beक्रमe use.
 */
#घोषणा dmi_early_remap(x, l)		ioremap_cache(x, l)
#घोषणा dmi_early_unmap(x, l)		iounmap(x)
#घोषणा dmi_remap(x, l)			ioremap_cache(x, l)
#घोषणा dmi_unmap(x)			iounmap(x)
#घोषणा dmi_alloc(l)			kzalloc(l, GFP_KERNEL)

#पूर्ण_अगर
