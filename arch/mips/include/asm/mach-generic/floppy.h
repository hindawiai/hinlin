<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 1997, 1998, 2003 by Ralf Baechle
 */
#अगर_अघोषित __ASM_MACH_GENERIC_FLOPPY_H
#घोषणा __ASM_MACH_GENERIC_FLOPPY_H

#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/linkage.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cachectl.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/floppy.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

/*
 * How to access the FDC's रेजिस्टरs.
 */
अटल अंतरभूत अचिन्हित अक्षर fd_inb(अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक reg)
अणु
	वापस inb_p(base + reg);
पूर्ण

अटल अंतरभूत व्योम fd_outb(अचिन्हित अक्षर value, अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक reg)
अणु
	outb_p(value, base + reg);
पूर्ण

/*
 * How to access the floppy DMA functions.
 */
अटल अंतरभूत व्योम fd_enable_dma(व्योम)
अणु
	enable_dma(FLOPPY_DMA);
पूर्ण

अटल अंतरभूत व्योम fd_disable_dma(व्योम)
अणु
	disable_dma(FLOPPY_DMA);
पूर्ण

अटल अंतरभूत पूर्णांक fd_request_dma(व्योम)
अणु
	वापस request_dma(FLOPPY_DMA, "floppy");
पूर्ण

अटल अंतरभूत व्योम fd_मुक्त_dma(व्योम)
अणु
	मुक्त_dma(FLOPPY_DMA);
पूर्ण

अटल अंतरभूत व्योम fd_clear_dma_ff(व्योम)
अणु
	clear_dma_ff(FLOPPY_DMA);
पूर्ण

अटल अंतरभूत व्योम fd_set_dma_mode(अक्षर mode)
अणु
	set_dma_mode(FLOPPY_DMA, mode);
पूर्ण

अटल अंतरभूत व्योम fd_set_dma_addr(अक्षर *addr)
अणु
	set_dma_addr(FLOPPY_DMA, (अचिन्हित दीर्घ) addr);
पूर्ण

अटल अंतरभूत व्योम fd_set_dma_count(अचिन्हित पूर्णांक count)
अणु
	set_dma_count(FLOPPY_DMA, count);
पूर्ण

अटल अंतरभूत पूर्णांक fd_get_dma_residue(व्योम)
अणु
	वापस get_dma_residue(FLOPPY_DMA);
पूर्ण

अटल अंतरभूत व्योम fd_enable_irq(व्योम)
अणु
	enable_irq(FLOPPY_IRQ);
पूर्ण

अटल अंतरभूत व्योम fd_disable_irq(व्योम)
अणु
	disable_irq(FLOPPY_IRQ);
पूर्ण

अटल अंतरभूत पूर्णांक fd_request_irq(व्योम)
अणु
	वापस request_irq(FLOPPY_IRQ, floppy_पूर्णांकerrupt,
			   0, "floppy", शून्य);
पूर्ण

अटल अंतरभूत व्योम fd_मुक्त_irq(व्योम)
अणु
	मुक्त_irq(FLOPPY_IRQ, शून्य);
पूर्ण

#घोषणा fd_मुक्त_irq()		मुक्त_irq(FLOPPY_IRQ, शून्य);


अटल अंतरभूत अचिन्हित दीर्घ fd_getfdaddr1(व्योम)
अणु
	वापस 0x3f0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ fd_dma_mem_alloc(अचिन्हित दीर्घ size)
अणु
	वापस __get_dma_pages(GFP_KERNEL, get_order(size));
पूर्ण

अटल अंतरभूत व्योम fd_dma_mem_मुक्त(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	मुक्त_pages(addr, get_order(size));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ fd_drive_type(अचिन्हित दीर्घ n)
अणु
	अगर (n == 0)
		वापस 4;	/* 3,5", 1.44mb */

	वापस 0;
पूर्ण

#पूर्ण_अगर /* __ASM_MACH_GENERIC_FLOPPY_H */
