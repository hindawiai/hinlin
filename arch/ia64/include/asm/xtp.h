<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_XTP_H
#घोषणा _ASM_IA64_XTP_H

#समावेश <यंत्र/पन.स>

#अगर_घोषित CONFIG_SMP

#घोषणा XTP_OFFSET		0x1e0008

#घोषणा SMP_IRQ_REसूचीECTION	(1 << 0)
#घोषणा SMP_IPI_REसूचीECTION	(1 << 1)

बाह्य अचिन्हित अक्षर smp_पूर्णांक_redirect;

/*
 * XTP control functions:
 *	min_xtp   : route all पूर्णांकerrupts to this CPU
 *	normal_xtp: nominal XTP value
 *	max_xtp   : never deliver पूर्णांकerrupts to this CPU.
 */

अटल अंतरभूत व्योम
min_xtp (व्योम)
अणु
	अगर (smp_पूर्णांक_redirect & SMP_IRQ_REसूचीECTION)
		ग_लिखोb(0x00, ipi_base_addr + XTP_OFFSET); /* XTP to min */
पूर्ण

अटल अंतरभूत व्योम
normal_xtp (व्योम)
अणु
	अगर (smp_पूर्णांक_redirect & SMP_IRQ_REसूचीECTION)
		ग_लिखोb(0x08, ipi_base_addr + XTP_OFFSET); /* XTP normal */
पूर्ण

अटल अंतरभूत व्योम
max_xtp (व्योम)
अणु
	अगर (smp_पूर्णांक_redirect & SMP_IRQ_REसूचीECTION)
		ग_लिखोb(0x0f, ipi_base_addr + XTP_OFFSET); /* Set XTP to max */
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

#पूर्ण_अगर /* _ASM_IA64_XTP_Hy */
