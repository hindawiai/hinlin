<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_TRAPS_32_H
#घोषणा __ASM_SH_TRAPS_32_H

#समावेश <linux/types.h>
#समावेश <यंत्र/mmu.h>

#अगर_घोषित CONFIG_CPU_HAS_SR_RB
#घोषणा lookup_exception_vector()	\
(अणु					\
	अचिन्हित दीर्घ _vec;		\
					\
	__यंत्र__ __अस्थिर__ (		\
		"stc r2_bank, %0\n\t"	\
		: "=r" (_vec)		\
	);				\
					\
	_vec;				\
पूर्ण)
#अन्यथा
#घोषणा lookup_exception_vector()	\
(अणु					\
	अचिन्हित दीर्घ _vec;		\
	__यंत्र__ __अस्थिर__ (		\
		"mov r4, %0\n\t"	\
		: "=r" (_vec)		\
	);				\
					\
	_vec;				\
पूर्ण)
#पूर्ण_अगर

अटल अंतरभूत व्योम trigger_address_error(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		"ldc %0, sr\n\t"
		"mov.l @%1, %0"
		:
		: "r" (0x10000000), "r" (0x80000001)
	);
पूर्ण

यंत्रlinkage व्योम करो_address_error(काष्ठा pt_regs *regs,
				 अचिन्हित दीर्घ ग_लिखोaccess,
				 अचिन्हित दीर्घ address);
यंत्रlinkage व्योम करो_भागide_error(अचिन्हित दीर्घ r4);
यंत्रlinkage व्योम करो_reserved_inst(व्योम);
यंत्रlinkage व्योम करो_illegal_slot_inst(व्योम);
यंत्रlinkage व्योम करो_exception_error(व्योम);

#घोषणा BUILD_TRAP_HANDLER(name)					\
यंत्रlinkage व्योम name##_trap_handler(अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,	\
				    अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7,	\
				    काष्ठा pt_regs __regs)

#घोषणा TRAP_HANDLER_DECL				\
	काष्ठा pt_regs *regs = RELOC_HIDE(&__regs, 0);	\
	अचिन्हित पूर्णांक vec = regs->tra;			\
	(व्योम)vec;

#पूर्ण_अगर /* __ASM_SH_TRAPS_32_H */
