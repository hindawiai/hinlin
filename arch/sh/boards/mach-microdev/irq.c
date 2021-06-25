<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/superh/microdev/irq.c
 *
 * Copyright (C) 2003 Sean McGoogan (Sean.McGoogan@superh.com)
 *
 * SuperH SH4-202 MicroDev board support.
 */

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>
#समावेश <mach/microdev.h>

#घोषणा NUM_EXTERNAL_IRQS 16	/* IRL0 .. IRL15 */

अटल स्थिर काष्ठा अणु
	अचिन्हित अक्षर fpgaIrq;
	अचिन्हित अक्षर mapped;
	स्थिर अक्षर *name;
पूर्ण fpgaIrqTable[NUM_EXTERNAL_IRQS] = अणु
	अणु 0,				0,	"unused"   पूर्ण,		/* IRQ #0	IRL=15	0x200  */
	अणु MICRODEV_FPGA_IRQ_KEYBOARD,	1,	"keyboard" पूर्ण,		/* IRQ #1	IRL=14	0x220  */
	अणु MICRODEV_FPGA_IRQ_SERIAL1,	1,	"Serial #1"पूर्ण,		/* IRQ #2	IRL=13	0x240  */
	अणु MICRODEV_FPGA_IRQ_ETHERNET,	1,	"Ethernet" पूर्ण,		/* IRQ #3	IRL=12	0x260  */
	अणु MICRODEV_FPGA_IRQ_SERIAL2,	0,	"Serial #2"पूर्ण,		/* IRQ #4	IRL=11	0x280  */
	अणु 0,				0,	"unused"   पूर्ण,		/* IRQ #5	IRL=10	0x2a0  */
	अणु 0,				0,	"unused"   पूर्ण,		/* IRQ #6	IRL=9	0x2c0  */
	अणु MICRODEV_FPGA_IRQ_USB_HC,	1,	"USB"	   पूर्ण,		/* IRQ #7	IRL=8	0x2e0  */
	अणु MICRODEV_IRQ_PCI_INTA,	1,	"PCI INTA" पूर्ण,		/* IRQ #8	IRL=7	0x300  */
	अणु MICRODEV_IRQ_PCI_INTB,	1,	"PCI INTB" पूर्ण,		/* IRQ #9	IRL=6	0x320  */
	अणु MICRODEV_IRQ_PCI_INTC,	1,	"PCI INTC" पूर्ण,		/* IRQ #10	IRL=5	0x340  */
	अणु MICRODEV_IRQ_PCI_INTD,	1,	"PCI INTD" पूर्ण,		/* IRQ #11	IRL=4	0x360  */
	अणु MICRODEV_FPGA_IRQ_MOUSE,	1,	"mouse"    पूर्ण,		/* IRQ #12	IRL=3	0x380  */
	अणु MICRODEV_FPGA_IRQ_IDE2,	1,	"IDE #2"   पूर्ण,		/* IRQ #13	IRL=2	0x3a0  */
	अणु MICRODEV_FPGA_IRQ_IDE1,	1,	"IDE #1"   पूर्ण,		/* IRQ #14	IRL=1	0x3c0  */
	अणु 0,				0,	"unused"   पूर्ण,		/* IRQ #15	IRL=0	0x3e0  */
पूर्ण;

#अगर (MICRODEV_LINUX_IRQ_KEYBOARD != 1)
#  error Inconsistancy in defining the IRQ# क्रम Keyboard!
#पूर्ण_अगर

#अगर (MICRODEV_LINUX_IRQ_ETHERNET != 3)
#  error Inconsistancy in defining the IRQ# क्रम Ethernet!
#पूर्ण_अगर

#अगर (MICRODEV_LINUX_IRQ_USB_HC != 7)
#  error Inconsistancy in defining the IRQ# क्रम USB!
#पूर्ण_अगर

#अगर (MICRODEV_LINUX_IRQ_MOUSE != 12)
#  error Inconsistancy in defining the IRQ# क्रम PS/2 Mouse!
#पूर्ण_अगर

#अगर (MICRODEV_LINUX_IRQ_IDE2 != 13)
#  error Inconsistancy in defining the IRQ# क्रम secondary IDE!
#पूर्ण_अगर

#अगर (MICRODEV_LINUX_IRQ_IDE1 != 14)
#  error Inconsistancy in defining the IRQ# क्रम primary IDE!
#पूर्ण_अगर

अटल व्योम disable_microdev_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	अचिन्हित पूर्णांक fpgaIrq;

	अगर (irq >= NUM_EXTERNAL_IRQS)
		वापस;
	अगर (!fpgaIrqTable[irq].mapped)
		वापस;

	fpgaIrq = fpgaIrqTable[irq].fpgaIrq;

	/* disable पूर्णांकerrupts on the FPGA INTC रेजिस्टर */
	__raw_ग_लिखोl(MICRODEV_FPGA_INTC_MASK(fpgaIrq), MICRODEV_FPGA_INTDSB_REG);
पूर्ण

अटल व्योम enable_microdev_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	अचिन्हित दीर्घ priorityReg, priorities, pri;
	अचिन्हित पूर्णांक fpgaIrq;

	अगर (unlikely(irq >= NUM_EXTERNAL_IRQS))
		वापस;
	अगर (unlikely(!fpgaIrqTable[irq].mapped))
		वापस;

	pri = 15 - irq;

	fpgaIrq = fpgaIrqTable[irq].fpgaIrq;
	priorityReg = MICRODEV_FPGA_INTPRI_REG(fpgaIrq);

	/* set priority क्रम the पूर्णांकerrupt */
	priorities = __raw_पढ़ोl(priorityReg);
	priorities &= ~MICRODEV_FPGA_INTPRI_MASK(fpgaIrq);
	priorities |= MICRODEV_FPGA_INTPRI_LEVEL(fpgaIrq, pri);
	__raw_ग_लिखोl(priorities, priorityReg);

	/* enable पूर्णांकerrupts on the FPGA INTC रेजिस्टर */
	__raw_ग_लिखोl(MICRODEV_FPGA_INTC_MASK(fpgaIrq), MICRODEV_FPGA_INTENB_REG);
पूर्ण

अटल काष्ठा irq_chip microdev_irq_type = अणु
	.name = "MicroDev-IRQ",
	.irq_unmask = enable_microdev_irq,
	.irq_mask = disable_microdev_irq,
पूर्ण;

/* This function sets the desired irq handler to be a MicroDev type */
अटल व्योम __init make_microdev_irq(अचिन्हित पूर्णांक irq)
अणु
	disable_irq_nosync(irq);
	irq_set_chip_and_handler(irq, &microdev_irq_type, handle_level_irq);
	disable_microdev_irq(irq_get_irq_data(irq));
पूर्ण

बाह्य व्योम __init init_microdev_irq(व्योम)
अणु
	पूर्णांक i;

	/* disable पूर्णांकerrupts on the FPGA INTC रेजिस्टर */
	__raw_ग_लिखोl(~0ul, MICRODEV_FPGA_INTDSB_REG);

	क्रम (i = 0; i < NUM_EXTERNAL_IRQS; i++)
		make_microdev_irq(i);
पूर्ण

बाह्य व्योम microdev_prपूर्णांक_fpga_पूर्णांकc_status(व्योम)
अणु
	अस्थिर अचिन्हित पूर्णांक * स्थिर पूर्णांकenb = (अचिन्हित पूर्णांक*)MICRODEV_FPGA_INTENB_REG;
	अस्थिर अचिन्हित पूर्णांक * स्थिर पूर्णांकdsb = (अचिन्हित पूर्णांक*)MICRODEV_FPGA_INTDSB_REG;
	अस्थिर अचिन्हित पूर्णांक * स्थिर पूर्णांकpria = (अचिन्हित पूर्णांक*)MICRODEV_FPGA_INTPRI_REG(0);
	अस्थिर अचिन्हित पूर्णांक * स्थिर पूर्णांकprib = (अचिन्हित पूर्णांक*)MICRODEV_FPGA_INTPRI_REG(8);
	अस्थिर अचिन्हित पूर्णांक * स्थिर पूर्णांकpric = (अचिन्हित पूर्णांक*)MICRODEV_FPGA_INTPRI_REG(16);
	अस्थिर अचिन्हित पूर्णांक * स्थिर पूर्णांकprid = (अचिन्हित पूर्णांक*)MICRODEV_FPGA_INTPRI_REG(24);
	अस्थिर अचिन्हित पूर्णांक * स्थिर पूर्णांकsrc = (अचिन्हित पूर्णांक*)MICRODEV_FPGA_INTSRC_REG;
	अस्थिर अचिन्हित पूर्णांक * स्थिर पूर्णांकreq = (अचिन्हित पूर्णांक*)MICRODEV_FPGA_INTREQ_REG;

	prपूर्णांकk("-------------------------- microdev_print_fpga_intc_status() ------------------\n");
	prपूर्णांकk("FPGA_INTENB = 0x%08x\n", *पूर्णांकenb);
	prपूर्णांकk("FPGA_INTDSB = 0x%08x\n", *पूर्णांकdsb);
	prपूर्णांकk("FPGA_INTSRC = 0x%08x\n", *पूर्णांकsrc);
	prपूर्णांकk("FPGA_INTREQ = 0x%08x\n", *पूर्णांकreq);
	prपूर्णांकk("FPGA_INTPRI[3..0] = %08x:%08x:%08x:%08x\n", *पूर्णांकprid, *पूर्णांकpric, *पूर्णांकprib, *पूर्णांकpria);
	prपूर्णांकk("-------------------------------------------------------------------------------\n");
पूर्ण
