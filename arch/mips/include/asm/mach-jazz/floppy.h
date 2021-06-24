<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1998, 2003 by Ralf Baechle
 */
#अगर_अघोषित __ASM_MACH_JAZZ_FLOPPY_H
#घोषणा __ASM_MACH_JAZZ_FLOPPY_H

#समावेश <linux/delay.h>
#समावेश <linux/linkage.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/jazz.h>
#समावेश <यंत्र/jazzdma.h>

अटल अंतरभूत अचिन्हित अक्षर fd_inb(अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित अक्षर c;

	c = *(अस्थिर अचिन्हित अक्षर *) (base + reg);
	udelay(1);

	वापस c;
पूर्ण

अटल अंतरभूत व्योम fd_outb(अचिन्हित अक्षर value, अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक reg)
अणु
	*(अस्थिर अचिन्हित अक्षर *) (base + reg) = value;
पूर्ण

/*
 * How to access the floppy DMA functions.
 */
अटल अंतरभूत व्योम fd_enable_dma(व्योम)
अणु
	vdma_enable(JAZZ_FLOPPY_DMA);
पूर्ण

अटल अंतरभूत व्योम fd_disable_dma(व्योम)
अणु
	vdma_disable(JAZZ_FLOPPY_DMA);
पूर्ण

अटल अंतरभूत पूर्णांक fd_request_dma(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम fd_मुक्त_dma(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम fd_clear_dma_ff(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम fd_set_dma_mode(अक्षर mode)
अणु
	vdma_set_mode(JAZZ_FLOPPY_DMA, mode);
पूर्ण

अटल अंतरभूत व्योम fd_set_dma_addr(अक्षर *a)
अणु
	vdma_set_addr(JAZZ_FLOPPY_DMA, vdma_phys2log(CPHYSADDR((अचिन्हित दीर्घ)a)));
पूर्ण

अटल अंतरभूत व्योम fd_set_dma_count(अचिन्हित पूर्णांक count)
अणु
	vdma_set_count(JAZZ_FLOPPY_DMA, count);
पूर्ण

अटल अंतरभूत पूर्णांक fd_get_dma_residue(व्योम)
अणु
	वापस vdma_get_residue(JAZZ_FLOPPY_DMA);
पूर्ण

अटल अंतरभूत व्योम fd_enable_irq(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम fd_disable_irq(व्योम)
अणु
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

अटल अंतरभूत अचिन्हित दीर्घ fd_getfdaddr1(व्योम)
अणु
	वापस JAZZ_FDC_BASE;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ fd_dma_mem_alloc(अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ mem;

	mem = __get_dma_pages(GFP_KERNEL, get_order(size));
	अगर(!mem)
		वापस 0;
	vdma_alloc(CPHYSADDR(mem), size);	/* XXX error checking */

	वापस mem;
पूर्ण

अटल अंतरभूत व्योम fd_dma_mem_मुक्त(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	vdma_मुक्त(vdma_phys2log(CPHYSADDR(addr)));
	मुक्त_pages(addr, get_order(size));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ fd_drive_type(अचिन्हित दीर्घ n)
अणु
	/* XXX This is wrong क्रम machines with ED 2.88mb disk drives like the
	   Olivetti M700.  Anyway, we should suck this from the ARC
	   firmware.  */
	अगर (n == 0)
		वापस 4;	/* 3,5", 1.44mb */

	वापस 0;
पूर्ण

#पूर्ण_अगर /* __ASM_MACH_JAZZ_FLOPPY_H */
