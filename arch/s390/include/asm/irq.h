<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IRQ_H
#घोषणा _ASM_IRQ_H

#घोषणा EXT_INTERRUPT	0
#घोषणा IO_INTERRUPT	1
#घोषणा THIN_INTERRUPT	2

#घोषणा NR_IRQS_BASE	3

#घोषणा NR_IRQS	NR_IRQS_BASE
#घोषणा NR_IRQS_LEGACY NR_IRQS_BASE

/* External पूर्णांकerruption codes */
#घोषणा EXT_IRQ_INTERRUPT_KEY	0x0040
#घोषणा EXT_IRQ_CLK_COMP	0x1004
#घोषणा EXT_IRQ_CPU_TIMER	0x1005
#घोषणा EXT_IRQ_WARNING_TRACK	0x1007
#घोषणा EXT_IRQ_MALFUNC_ALERT	0x1200
#घोषणा EXT_IRQ_EMERGENCY_SIG	0x1201
#घोषणा EXT_IRQ_EXTERNAL_CALL	0x1202
#घोषणा EXT_IRQ_TIMING_ALERT	0x1406
#घोषणा EXT_IRQ_MEASURE_ALERT	0x1407
#घोषणा EXT_IRQ_SERVICE_SIG	0x2401
#घोषणा EXT_IRQ_CP_SERVICE	0x2603
#घोषणा EXT_IRQ_IUCV		0x4000

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/hardirq.h>
#समावेश <linux/percpu.h>
#समावेश <linux/cache.h>
#समावेश <linux/types.h>

क्रमागत पूर्णांकerruption_class अणु
	IRQEXT_CLK,
	IRQEXT_EXC,
	IRQEXT_EMS,
	IRQEXT_TMR,
	IRQEXT_TLA,
	IRQEXT_PFL,
	IRQEXT_DSD,
	IRQEXT_VRT,
	IRQEXT_SCP,
	IRQEXT_IUC,
	IRQEXT_CMS,
	IRQEXT_CMC,
	IRQEXT_FTP,
	IRQIO_CIO,
	IRQIO_DAS,
	IRQIO_C15,
	IRQIO_C70,
	IRQIO_TAP,
	IRQIO_VMR,
	IRQIO_LCS,
	IRQIO_CTC,
	IRQIO_ADM,
	IRQIO_CSC,
	IRQIO_VIR,
	IRQIO_QAI,
	IRQIO_APB,
	IRQIO_PCF,
	IRQIO_PCD,
	IRQIO_MSI,
	IRQIO_VAI,
	IRQIO_GAL,
	NMI_NMI,
	CPU_RST,
	NR_ARCH_IRQS
पूर्ण;

काष्ठा irq_stat अणु
	अचिन्हित पूर्णांक irqs[NR_ARCH_IRQS];
पूर्ण;

DECLARE_PER_CPU_SHARED_ALIGNED(काष्ठा irq_stat, irq_stat);

अटल __always_अंतरभूत व्योम inc_irq_stat(क्रमागत पूर्णांकerruption_class irq)
अणु
	__this_cpu_inc(irq_stat.irqs[irq]);
पूर्ण

काष्ठा ext_code अणु
	अचिन्हित लघु subcode;
	अचिन्हित लघु code;
पूर्ण;

प्रकार व्योम (*ext_पूर्णांक_handler_t)(काष्ठा ext_code, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);

पूर्णांक रेजिस्टर_बाह्यal_irq(u16 code, ext_पूर्णांक_handler_t handler);
पूर्णांक unरेजिस्टर_बाह्यal_irq(u16 code, ext_पूर्णांक_handler_t handler);

क्रमागत irq_subclass अणु
	IRQ_SUBCLASS_MEASUREMENT_ALERT = 5,
	IRQ_SUBCLASS_SERVICE_SIGNAL = 9,
पूर्ण;

#घोषणा CR0_IRQ_SUBCLASS_MASK					  \
	((1UL << (63 - 30))  /* Warning Track */		| \
	 (1UL << (63 - 48))  /* Malfunction Alert */		| \
	 (1UL << (63 - 49))  /* Emergency Signal */		| \
	 (1UL << (63 - 50))  /* External Call */		| \
	 (1UL << (63 - 52))  /* Clock Comparator */		| \
	 (1UL << (63 - 53))  /* CPU Timer */			| \
	 (1UL << (63 - 54))  /* Service Signal */		| \
	 (1UL << (63 - 57))  /* Interrupt Key */		| \
	 (1UL << (63 - 58))  /* Measurement Alert */		| \
	 (1UL << (63 - 59))  /* Timing Alert */			| \
	 (1UL << (63 - 62))) /* IUCV */

व्योम irq_subclass_रेजिस्टर(क्रमागत irq_subclass subclass);
व्योम irq_subclass_unरेजिस्टर(क्रमागत irq_subclass subclass);

#घोषणा irq_canonicalize(irq)  (irq)

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_IRQ_H */
