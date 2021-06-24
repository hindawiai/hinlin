<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ARM समयr implementation, found in Integrator, Versatile and Realview
 * platक्रमms.  Not all platक्रमms support all रेजिस्टरs and bits in these
 * रेजिस्टरs, so we mark them with A क्रम Integrator AP, C क्रम Integrator
 * CP, V क्रम Versatile and R क्रम Realview.
 *
 * Integrator AP has 16-bit समयrs, Integrator CP, Versatile and Realview
 * can have 16-bit or 32-bit selectable via a bit in the control रेजिस्टर.
 *
 * Every SP804 contains two identical समयrs.
 */
#घोषणा NR_TIMERS	2
#घोषणा TIMER_1_BASE	0x00
#घोषणा TIMER_2_BASE	0x20

#घोषणा TIMER_LOAD	0x00			/* ACVR rw */
#घोषणा TIMER_VALUE	0x04			/* ACVR ro */
#घोषणा TIMER_CTRL	0x08			/* ACVR rw */
#घोषणा TIMER_CTRL_ONESHOT	(1 << 0)	/*  CVR */
#घोषणा TIMER_CTRL_32BIT	(1 << 1)	/*  CVR */
#घोषणा TIMER_CTRL_DIV1		(0 << 2)	/* ACVR */
#घोषणा TIMER_CTRL_DIV16	(1 << 2)	/* ACVR */
#घोषणा TIMER_CTRL_DIV256	(2 << 2)	/* ACVR */
#घोषणा TIMER_CTRL_IE		(1 << 5)	/*   VR */
#घोषणा TIMER_CTRL_PERIODIC	(1 << 6)	/* ACVR */
#घोषणा TIMER_CTRL_ENABLE	(1 << 7)	/* ACVR */

#घोषणा TIMER_INTCLR	0x0c			/* ACVR wo */
#घोषणा TIMER_RIS	0x10			/*  CVR ro */
#घोषणा TIMER_MIS	0x14			/*  CVR ro */
#घोषणा TIMER_BGLOAD	0x18			/*  CVR rw */

काष्ठा sp804_समयr अणु
	पूर्णांक load;
	पूर्णांक load_h;
	पूर्णांक value;
	पूर्णांक value_h;
	पूर्णांक ctrl;
	पूर्णांक पूर्णांकclr;
	पूर्णांक ris;
	पूर्णांक mis;
	पूर्णांक bgload;
	पूर्णांक bgload_h;
	पूर्णांक समयr_base[NR_TIMERS];
	पूर्णांक width;
पूर्ण;

काष्ठा sp804_clkevt अणु
	व्योम __iomem *base;
	व्योम __iomem *load;
	व्योम __iomem *load_h;
	व्योम __iomem *value;
	व्योम __iomem *value_h;
	व्योम __iomem *ctrl;
	व्योम __iomem *पूर्णांकclr;
	व्योम __iomem *ris;
	व्योम __iomem *mis;
	व्योम __iomem *bgload;
	व्योम __iomem *bgload_h;
	अचिन्हित दीर्घ reload;
	पूर्णांक width;
पूर्ण;
