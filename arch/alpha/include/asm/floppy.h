<शैली गुरु>
/*
 * Architecture specअगरic parts of the Floppy driver
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995
 */
#अगर_अघोषित __ASM_ALPHA_FLOPPY_H
#घोषणा __ASM_ALPHA_FLOPPY_H


#घोषणा fd_inb(base, reg)		inb_p((base) + (reg))
#घोषणा fd_outb(value, base, reg)	outb_p(value, (base) + (reg))

#घोषणा fd_enable_dma()         enable_dma(FLOPPY_DMA)
#घोषणा fd_disable_dma()        disable_dma(FLOPPY_DMA)
#घोषणा fd_request_dma()        request_dma(FLOPPY_DMA,"floppy")
#घोषणा fd_मुक्त_dma()           मुक्त_dma(FLOPPY_DMA)
#घोषणा fd_clear_dma_ff()       clear_dma_ff(FLOPPY_DMA)
#घोषणा fd_set_dma_mode(mode)   set_dma_mode(FLOPPY_DMA,mode)
#घोषणा fd_set_dma_addr(addr)   set_dma_addr(FLOPPY_DMA,virt_to_bus(addr))
#घोषणा fd_set_dma_count(count) set_dma_count(FLOPPY_DMA,count)
#घोषणा fd_enable_irq()         enable_irq(FLOPPY_IRQ)
#घोषणा fd_disable_irq()        disable_irq(FLOPPY_IRQ)
#घोषणा fd_request_irq()        request_irq(FLOPPY_IRQ, floppy_पूर्णांकerrupt,\
					    0, "floppy", शून्य)
#घोषणा fd_मुक्त_irq()           मुक्त_irq(FLOPPY_IRQ, शून्य)

#अगर_घोषित CONFIG_PCI

#समावेश <linux/pci.h>

#घोषणा fd_dma_setup(addr,size,mode,io) alpha_fd_dma_setup(addr,size,mode,io)

अटल __अंतरभूत__ पूर्णांक 
alpha_fd_dma_setup(अक्षर *addr, अचिन्हित दीर्घ size, पूर्णांक mode, पूर्णांक io)
अणु
	अटल अचिन्हित दीर्घ prev_size;
	अटल dma_addr_t bus_addr = 0;
	अटल अक्षर *prev_addr;
	अटल पूर्णांक prev_dir;
	पूर्णांक dir;

	dir = (mode != DMA_MODE_READ) ? PCI_DMA_FROMDEVICE : PCI_DMA_TODEVICE;

	अगर (bus_addr 
	    && (addr != prev_addr || size != prev_size || dir != prev_dir)) अणु
		/* dअगरferent from last समय -- unmap prev */
		pci_unmap_single(isa_bridge, bus_addr, prev_size, prev_dir);
		bus_addr = 0;
	पूर्ण

	अगर (!bus_addr)	/* need to map it */
		bus_addr = pci_map_single(isa_bridge, addr, size, dir);

	/* remember this one as prev */
	prev_addr = addr;
	prev_size = size;
	prev_dir = dir;

	fd_clear_dma_ff();
	fd_set_dma_mode(mode);
	set_dma_addr(FLOPPY_DMA, bus_addr);
	fd_set_dma_count(size);
	भव_dma_port = io;
	fd_enable_dma();

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PCI */

__अंतरभूत__ व्योम भव_dma_init(व्योम)
अणु
	/* Nothing to करो on an Alpha */
पूर्ण

अटल पूर्णांक FDC1 = 0x3f0;
अटल पूर्णांक FDC2 = -1;

/*
 * Again, the CMOS inक्रमmation करोesn't work on the alpha..
 */
#घोषणा FLOPPY0_TYPE 6
#घोषणा FLOPPY1_TYPE 0

#घोषणा N_FDC 2
#घोषणा N_DRIVE 8

/*
 * Most Alphas have no problems with floppy DMA crossing 64k borders,
 * except क्रम certain ones, like XL and RUFFIAN.
 *
 * However, the test is simple and fast, and this *is* floppy, after all,
 * so we करो it क्रम all platक्रमms, just to make sure.
 *
 * This is advantageous in other circumstances as well, as in moving
 * about the PCI DMA winकरोws and क्रमcing the floppy to start करोing
 * scatter-gather when it never had beक्रमe, and there *is* a problem
 * on that platक्रमm... ;-पूर्ण
 */

अटल अंतरभूत अचिन्हित दीर्घ CROSS_64KB(व्योम *a, अचिन्हित दीर्घ s)
अणु
	अचिन्हित दीर्घ p = (अचिन्हित दीर्घ)a;
	वापस ((p + s - 1) ^ p) & ~0xffffUL;
पूर्ण

#घोषणा EXTRA_FLOPPY_PARAMS

#पूर्ण_अगर /* __ASM_ALPHA_FLOPPY_H */
