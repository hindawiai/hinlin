<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_COMPILER_H
#घोषणा __ASM_COMPILER_H

#अगर_घोषित ARM64_ASM_ARCH
#घोषणा ARM64_ASM_PREAMBLE ".arch " ARM64_ASM_ARCH "\n"
#अन्यथा
#घोषणा ARM64_ASM_PREAMBLE
#पूर्ण_अगर

/*
 * The EL0/EL1 poपूर्णांकer bits used by a poपूर्णांकer authentication code.
 * This is dependent on TBI0/TBI1 being enabled, or bits 63:56 would also apply.
 */
#घोषणा ptrauth_user_pac_mask()		GENMASK_ULL(54, vabits_actual)
#घोषणा ptrauth_kernel_pac_mask()	GENMASK_ULL(63, vabits_actual)

/* Valid क्रम EL0 TTBR0 and EL1 TTBR1 inकाष्ठाion poपूर्णांकers */
#घोषणा ptrauth_clear_pac(ptr)						\
	((ptr & BIT_ULL(55)) ? (ptr | ptrauth_kernel_pac_mask()) :	\
			       (ptr & ~ptrauth_user_pac_mask()))

#घोषणा __builtin_वापस_address(val)					\
	(व्योम *)(ptrauth_clear_pac((अचिन्हित दीर्घ)__builtin_वापस_address(val)))

#पूर्ण_अगर /* __ASM_COMPILER_H */
