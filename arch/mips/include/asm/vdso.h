<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Imagination Technologies
 * Author: Alex Smith <alex.smith@imgtec.com>
 */

#अगर_अघोषित __ASM_VDSO_H
#घोषणा __ASM_VDSO_H

#समावेश <linux/mm_types.h>
#समावेश <vdso/datapage.h>

#समावेश <यंत्र/barrier.h>

/**
 * काष्ठा mips_vdso_image - Details of a VDSO image.
 * @data: Poपूर्णांकer to VDSO image data (page-aligned).
 * @size: Size of the VDSO image data (page-aligned).
 * @off_sigवापस: Offset of the sigवापस() trampoline.
 * @off_rt_sigवापस: Offset of the rt_sigवापस() trampoline.
 * @mapping: Special mapping काष्ठाure.
 *
 * This काष्ठाure contains details of a VDSO image, including the image data
 * and offsets of certain symbols required by the kernel. It is generated as
 * part of the VDSO build process, aside from the mapping page array, which is
 * populated at runसमय.
 */
काष्ठा mips_vdso_image अणु
	व्योम *data;
	अचिन्हित दीर्घ size;

	अचिन्हित दीर्घ off_sigवापस;
	अचिन्हित दीर्घ off_rt_sigवापस;

	काष्ठा vm_special_mapping mapping;
पूर्ण;

/*
 * The following काष्ठाures are स्वतः-generated as part of the build क्रम each
 * ABI by genvdso, see arch/mips/vdso/Makefile.
 */

बाह्य काष्ठा mips_vdso_image vdso_image;

#अगर_घोषित CONFIG_MIPS32_O32
बाह्य काष्ठा mips_vdso_image vdso_image_o32;
#पूर्ण_अगर

#अगर_घोषित CONFIG_MIPS32_N32
बाह्य काष्ठा mips_vdso_image vdso_image_n32;
#पूर्ण_अगर

जोड़ mips_vdso_data अणु
	काष्ठा vdso_data data[CS_BASES];
	u8 page[PAGE_SIZE];
पूर्ण;

#पूर्ण_अगर /* __ASM_VDSO_H */
