<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linker script macros to generate Image header fields.
 *
 * Copyright (C) 2014 ARM Ltd.
 */
#अगर_अघोषित __ARM64_KERNEL_IMAGE_H
#घोषणा __ARM64_KERNEL_IMAGE_H

#अगर_अघोषित LINKER_SCRIPT
#त्रुटि This file should only be included in vmlinux.lds.S
#पूर्ण_अगर

#समावेश <यंत्र/image.h>

/*
 * There aren't any ELF relocations we can use to endian-swap values known only
 * at link समय (e.g. the subtraction of two symbol addresses), so we must get
 * the linker to endian-swap certain values beक्रमe emitting them.
 *
 * Note that, in order क्रम this to work when building the ELF64 PIE executable
 * (क्रम KASLR), these values should not be referenced via R_AARCH64_ABS64
 * relocations, since these are fixed up at runसमय rather than at build समय
 * when PIE is in effect. So we need to split them up in 32-bit high and low
 * words.
 */
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#घोषणा DATA_LE32(data)				\
	((((data) & 0x000000ff) << 24) |	\
	 (((data) & 0x0000ff00) << 8)  |	\
	 (((data) & 0x00ff0000) >> 8)  |	\
	 (((data) & 0xff000000) >> 24))
#अन्यथा
#घोषणा DATA_LE32(data) ((data) & 0xffffffff)
#पूर्ण_अगर

#घोषणा DEFINE_IMAGE_LE64(sym, data)				\
	sym##_lo32 = DATA_LE32((data) & 0xffffffff);		\
	sym##_hi32 = DATA_LE32((data) >> 32)

#घोषणा __HEAD_FLAG(field)	(__HEAD_FLAG_##field << \
					ARM64_IMAGE_FLAG_##field##_SHIFT)

#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#घोषणा __HEAD_FLAG_BE		ARM64_IMAGE_FLAG_BE
#अन्यथा
#घोषणा __HEAD_FLAG_BE		ARM64_IMAGE_FLAG_LE
#पूर्ण_अगर

#घोषणा __HEAD_FLAG_PAGE_SIZE	((PAGE_SHIFT - 10) / 2)

#घोषणा __HEAD_FLAG_PHYS_BASE	1

#घोषणा __HEAD_FLAGS		(__HEAD_FLAG(BE)	| \
				 __HEAD_FLAG(PAGE_SIZE) | \
				 __HEAD_FLAG(PHYS_BASE))

/*
 * These will output as part of the Image header, which should be little-endian
 * regardless of the endianness of the kernel. While स्थिरant values could be
 * endian swapped in head.S, all are करोne here क्रम consistency.
 */
#घोषणा HEAD_SYMBOLS						\
	DEFINE_IMAGE_LE64(_kernel_size_le, _end - _text);	\
	DEFINE_IMAGE_LE64(_kernel_flags_le, __HEAD_FLAGS);

#पूर्ण_अगर /* __ARM64_KERNEL_IMAGE_H */
