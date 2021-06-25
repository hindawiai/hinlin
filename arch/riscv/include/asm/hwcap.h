<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copied from arch/arm64/include/यंत्र/hwcap.h
 *
 * Copyright (C) 2012 ARM Ltd.
 * Copyright (C) 2017 SiFive
 */
#अगर_अघोषित _ASM_RISCV_HWCAP_H
#घोषणा _ASM_RISCV_HWCAP_H

#समावेश <linux/bits.h>
#समावेश <uapi/यंत्र/hwcap.h>

#अगर_अघोषित __ASSEMBLY__
/*
 * This yields a mask that user programs can use to figure out what
 * inकाष्ठाion set this cpu supports.
 */
#घोषणा ELF_HWCAP		(elf_hwcap)

क्रमागत अणु
	CAP_HWCAP = 1,
पूर्ण;

बाह्य अचिन्हित दीर्घ elf_hwcap;

#घोषणा RISCV_ISA_EXT_a		('a' - 'a')
#घोषणा RISCV_ISA_EXT_c		('c' - 'a')
#घोषणा RISCV_ISA_EXT_d		('d' - 'a')
#घोषणा RISCV_ISA_EXT_f		('f' - 'a')
#घोषणा RISCV_ISA_EXT_h		('h' - 'a')
#घोषणा RISCV_ISA_EXT_i		('i' - 'a')
#घोषणा RISCV_ISA_EXT_m		('m' - 'a')
#घोषणा RISCV_ISA_EXT_s		('s' - 'a')
#घोषणा RISCV_ISA_EXT_u		('u' - 'a')

#घोषणा RISCV_ISA_EXT_MAX	64

अचिन्हित दीर्घ riscv_isa_extension_base(स्थिर अचिन्हित दीर्घ *isa_biपंचांगap);

#घोषणा riscv_isa_extension_mask(ext) BIT_MASK(RISCV_ISA_EXT_##ext)

bool __riscv_isa_extension_available(स्थिर अचिन्हित दीर्घ *isa_biपंचांगap, पूर्णांक bit);
#घोषणा riscv_isa_extension_available(isa_biपंचांगap, ext)	\
	__riscv_isa_extension_available(isa_biपंचांगap, RISCV_ISA_EXT_##ext)

#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_RISCV_HWCAP_H */
