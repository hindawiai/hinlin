<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Preliminary support क्रम HW exception handing क्रम Microblaze
 *
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2005 John Williams <jwilliams@itee.uq.edu.au>
 */

#अगर_अघोषित _ASM_MICROBLAZE_EXCEPTIONS_H
#घोषणा _ASM_MICROBLAZE_EXCEPTIONS_H

#अगर_घोषित __KERNEL__
#अगर_अघोषित __ASSEMBLY__

/* Macros to enable and disable HW exceptions in the MSR */
/* Define MSR enable bit क्रम HW exceptions */
#घोषणा HWEX_MSR_BIT (1 << 8)

#अगर CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR
#घोषणा __enable_hw_exceptions()					\
	__यंत्र__ __अस्थिर__ ("	msrset	r0, %0;				\
				nop;"					\
				:					\
				: "i" (HWEX_MSR_BIT)			\
				: "memory")

#घोषणा __disable_hw_exceptions()					\
	__यंत्र__ __अस्थिर__ ("	msrclr r0, %0;				\
				nop;"					\
				:					\
				: "i" (HWEX_MSR_BIT)			\
				: "memory")
#अन्यथा /* !CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR */
#घोषणा __enable_hw_exceptions()					\
	__यंत्र__ __अस्थिर__ ("						\
				mfs	r12, rmsr;			\
				nop;					\
				ori	r12, r12, %0;			\
				mts	rmsr, r12;			\
				nop;"					\
				:					\
				: "i" (HWEX_MSR_BIT)			\
				: "memory", "r12")

#घोषणा __disable_hw_exceptions()					\
	__यंत्र__ __अस्थिर__ ("						\
				mfs	r12, rmsr;			\
				nop;					\
				andi	r12, r12, ~%0;			\
				mts	rmsr, r12;			\
				nop;"					\
				:					\
				: "i" (HWEX_MSR_BIT)			\
				: "memory", "r12")
#पूर्ण_अगर /* CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR */

यंत्रlinkage व्योम full_exception(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक type,
							पूर्णांक fsr, पूर्णांक addr);

यंत्रlinkage व्योम sw_exception(काष्ठा pt_regs *regs);
व्योम bad_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address, पूर्णांक sig);

व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *fp, दीर्घ err);
व्योम _exception(पूर्णांक signr, काष्ठा pt_regs *regs, पूर्णांक code, अचिन्हित दीर्घ addr);

#पूर्ण_अगर /*__ASSEMBLY__ */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_MICROBLAZE_EXCEPTIONS_H */
