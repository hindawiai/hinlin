<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2020 Google LLC.
 * Written by David Brazdil <dbrazdil@google.com>
 */

#अगर_अघोषित __ARM64_HYP_IMAGE_H__
#घोषणा __ARM64_HYP_IMAGE_H__

#घोषणा __HYP_CONCAT(a, b)	a ## b
#घोषणा HYP_CONCAT(a, b)	__HYP_CONCAT(a, b)

#अगर_अघोषित __KVM_NVHE_HYPERVISOR__
/*
 * KVM nVHE code has its own symbol namespace prefixed with __kvm_nvhe_,
 * to separate it from the kernel proper.
 */
#घोषणा kvm_nvhe_sym(sym)	__kvm_nvhe_##sym
#अन्यथा
#घोषणा kvm_nvhe_sym(sym)	sym
#पूर्ण_अगर

#अगर_घोषित LINKER_SCRIPT

/*
 * KVM nVHE ELF section names are prefixed with .hyp, to separate them
 * from the kernel proper.
 */
#घोषणा HYP_SECTION_NAME(NAME)	.hyp##NAME

/* Symbol defined at the beginning of each hyp section. */
#घोषणा HYP_SECTION_SYMBOL_NAME(NAME) \
	HYP_CONCAT(__hyp_section_, HYP_SECTION_NAME(NAME))

/*
 * Helper to generate linker script statements starting a hyp section.
 *
 * A symbol with a well-known name is defined at the first byte. This
 * is used as a base क्रम hyp relocations (see gen-hyprel.c). It must
 * be defined inside the section so the linker of `vmlinux` cannot
 * separate it from the section data.
 */
#घोषणा BEGIN_HYP_SECTION(NAME)				\
	HYP_SECTION_NAME(NAME) : अणु			\
		HYP_SECTION_SYMBOL_NAME(NAME) = .;

/* Helper to generate linker script statements ending a hyp section. */
#घोषणा END_HYP_SECTION					\
	पूर्ण

/* Defines an ELF hyp section from input section @NAME and its subsections. */
#घोषणा HYP_SECTION(NAME)			\
	BEGIN_HYP_SECTION(NAME)			\
		*(NAME NAME##.*)		\
	END_HYP_SECTION

/*
 * Defines a linker script alias of a kernel-proper symbol referenced by
 * KVM nVHE hyp code.
 */
#घोषणा KVM_NVHE_ALIAS(sym)	kvm_nvhe_sym(sym) = sym;

/* Defines a linker script alias क्रम KVM nVHE hyp symbols */
#घोषणा KVM_NVHE_ALIAS_HYP(first, sec)	kvm_nvhe_sym(first) = kvm_nvhe_sym(sec);

#पूर्ण_अगर /* LINKER_SCRIPT */

#पूर्ण_अगर /* __ARM64_HYP_IMAGE_H__ */
