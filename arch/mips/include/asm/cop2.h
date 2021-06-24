<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2009 Wind River Systems,
 *   written by Ralf Baechle <ralf@linux-mips.org>
 */
#अगर_अघोषित __ASM_COP2_H
#घोषणा __ASM_COP2_H

#समावेश <linux/notअगरier.h>

#अगर defined(CONFIG_CPU_CAVIUM_OCTEON)

बाह्य व्योम octeon_cop2_save(काष्ठा octeon_cop2_state *);
बाह्य व्योम octeon_cop2_restore(काष्ठा octeon_cop2_state *);

#घोषणा cop2_save(r)		octeon_cop2_save(&(r)->thपढ़ो.cp2)
#घोषणा cop2_restore(r)		octeon_cop2_restore(&(r)->thपढ़ो.cp2)

#घोषणा cop2_present		1
#घोषणा cop2_lazy_restore	1

#या_अगर defined(CONFIG_CPU_XLP)

बाह्य व्योम nlm_cop2_save(काष्ठा nlm_cop2_state *);
बाह्य व्योम nlm_cop2_restore(काष्ठा nlm_cop2_state *);

#घोषणा cop2_save(r)		nlm_cop2_save(&(r)->thपढ़ो.cp2)
#घोषणा cop2_restore(r)		nlm_cop2_restore(&(r)->thपढ़ो.cp2)

#घोषणा cop2_present		1
#घोषणा cop2_lazy_restore	0

#या_अगर defined(CONFIG_CPU_LOONGSON64)

#घोषणा cop2_present		1
#घोषणा cop2_lazy_restore	1
#घोषणा cop2_save(r)		करो अणु (व्योम)(r); पूर्ण जबतक (0)
#घोषणा cop2_restore(r)		करो अणु (व्योम)(r); पूर्ण जबतक (0)

#अन्यथा

#घोषणा cop2_present		0
#घोषणा cop2_lazy_restore	0
#घोषणा cop2_save(r)		करो अणु (व्योम)(r); पूर्ण जबतक (0)
#घोषणा cop2_restore(r)		करो अणु (व्योम)(r); पूर्ण जबतक (0)
#पूर्ण_अगर

क्रमागत cu2_ops अणु
	CU2_EXCEPTION,
	CU2_LWC2_OP,
	CU2_LDC2_OP,
	CU2_SWC2_OP,
	CU2_SDC2_OP,
पूर्ण;

बाह्य पूर्णांक रेजिस्टर_cu2_notअगरier(काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक cu2_notअगरier_call_chain(अचिन्हित दीर्घ val, व्योम *v);

#घोषणा cu2_notअगरier(fn, pri)						\
(अणु									\
	अटल काष्ठा notअगरier_block fn##_nb = अणु			\
		.notअगरier_call = fn,					\
		.priority = pri						\
	पूर्ण;								\
									\
	रेजिस्टर_cu2_notअगरier(&fn##_nb);				\
पूर्ण)

#पूर्ण_अगर /* __ASM_COP2_H */
