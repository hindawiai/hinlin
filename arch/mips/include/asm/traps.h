<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Trap handling definitions.
 *
 *	Copyright (C) 2002, 2003  Maciej W. Rozycki
 */
#अगर_अघोषित _ASM_TRAPS_H
#घोषणा _ASM_TRAPS_H

/*
 * Possible status responses क्रम a board_be_handler backend.
 */
#घोषणा MIPS_BE_DISCARD 0		/* वापस with no action */
#घोषणा MIPS_BE_FIXUP	1		/* वापस to the fixup code */
#घोषणा MIPS_BE_FATAL	2		/* treat as an unrecoverable error */

बाह्य व्योम (*board_be_init)(व्योम);
बाह्य पूर्णांक (*board_be_handler)(काष्ठा pt_regs *regs, पूर्णांक is_fixup);

बाह्य व्योम (*board_nmi_handler_setup)(व्योम);
बाह्य व्योम (*board_ejtag_handler_setup)(व्योम);
बाह्य व्योम (*board_bind_eic_पूर्णांकerrupt)(पूर्णांक irq, पूर्णांक regset);
बाह्य व्योम (*board_ebase_setup)(व्योम);
बाह्य व्योम (*board_cache_error_setup)(व्योम);

बाह्य पूर्णांक रेजिस्टर_nmi_notअगरier(काष्ठा notअगरier_block *nb);
बाह्य व्योम reserve_exception_space(phys_addr_t addr, अचिन्हित दीर्घ size);
बाह्य अक्षर except_vec_nmi[];

#घोषणा VECTORSPACING 0x100	/* क्रम EI/VI mode */

#घोषणा nmi_notअगरier(fn, pri)						\
(अणु									\
	अटल काष्ठा notअगरier_block fn##_nb = अणु			\
		.notअगरier_call = fn,					\
		.priority = pri						\
	पूर्ण;								\
									\
	रेजिस्टर_nmi_notअगरier(&fn##_nb);				\
पूर्ण)

#पूर्ण_अगर /* _ASM_TRAPS_H */
