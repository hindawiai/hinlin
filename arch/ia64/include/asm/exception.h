<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __ASM_EXCEPTION_H
#घोषणा __ASM_EXCEPTION_H

काष्ठा pt_regs;
काष्ठा exception_table_entry;

बाह्य व्योम ia64_handle_exception(काष्ठा pt_regs *regs,
				  स्थिर काष्ठा exception_table_entry *e);

#घोषणा ia64_करोne_with_exception(regs)					  \
(अणु									  \
	पूर्णांक __ex_ret = 0;						  \
	स्थिर काष्ठा exception_table_entry *e;				  \
	e = search_exception_tables((regs)->cr_iip + ia64_psr(regs)->ri); \
	अगर (e) अणु							  \
		ia64_handle_exception(regs, e);				  \
		__ex_ret = 1;						  \
	पूर्ण								  \
	__ex_ret;							  \
पूर्ण)

#पूर्ण_अगर	/* __ASM_EXCEPTION_H */
