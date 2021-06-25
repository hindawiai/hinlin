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
#अगर_अघोषित __ASM_POWERPC_FLOPPY_H
#घोषणा __ASM_POWERPC_FLOPPY_H
#अगर_घोषित __KERNEL__

#समावेश <यंत्र/machdep.h>

#घोषणा fd_inb(base, reg)		inb_p((base) + (reg))
#घोषणा fd_outb(value, base, reg)	outb_p(value, (base) + (reg))

#घोषणा fd_enable_dma()         enable_dma(FLOPPY_DMA)
#घोषणा fd_disable_dma()	 fd_ops->_disable_dma(FLOPPY_DMA)
#घोषणा fd_मुक्त_dma()           fd_ops->_मुक्त_dma(FLOPPY_DMA)
#घोषणा fd_clear_dma_ff()       clear_dma_ff(FLOPPY_DMA)
#घोषणा fd_set_dma_mode(mode)   set_dma_mode(FLOPPY_DMA, mode)
#घोषणा fd_set_dma_count(count) set_dma_count(FLOPPY_DMA, count)
#घोषणा fd_get_dma_residue()    fd_ops->_get_dma_residue(FLOPPY_DMA)
#घोषणा fd_enable_irq()         enable_irq(FLOPPY_IRQ)
#घोषणा fd_disable_irq()        disable_irq(FLOPPY_IRQ)
#घोषणा fd_मुक्त_irq()           मुक्त_irq(FLOPPY_IRQ, शून्य);

#समावेश <linux/pci.h>
#समावेश <यंत्र/ppc-pci.h>	/* क्रम isa_bridge_pcidev */

#घोषणा fd_dma_setup(addr,size,mode,io) fd_ops->_dma_setup(addr,size,mode,io)

अटल पूर्णांक fd_request_dma(व्योम);

काष्ठा fd_dma_ops अणु
	व्योम (*_disable_dma)(अचिन्हित पूर्णांक dmanr);
	व्योम (*_मुक्त_dma)(अचिन्हित पूर्णांक dmanr);
	पूर्णांक (*_get_dma_residue)(अचिन्हित पूर्णांक dummy);
	पूर्णांक (*_dma_setup)(अक्षर *addr, अचिन्हित दीर्घ size, पूर्णांक mode, पूर्णांक io);
पूर्ण;

अटल पूर्णांक भव_dma_count;
अटल पूर्णांक भव_dma_residue;
अटल अक्षर *भव_dma_addr;
अटल पूर्णांक भव_dma_mode;
अटल पूर्णांक करोing_vdma;
अटल काष्ठा fd_dma_ops *fd_ops;

अटल irqवापस_t floppy_hardपूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित अक्षर st;
	पूर्णांक lcount;
	अक्षर *lptr;

	अगर (!करोing_vdma)
		वापस floppy_पूर्णांकerrupt(irq, dev_id);


	st = 1;
	क्रम (lcount=भव_dma_count, lptr=भव_dma_addr;
	     lcount; lcount--, lptr++) अणु
		st = inb(भव_dma_port + FD_STATUS);
		st &= STATUS_DMA | STATUS_READY;
		अगर (st != (STATUS_DMA | STATUS_READY))
			अवरोध;
		अगर (भव_dma_mode)
			outb_p(*lptr, भव_dma_port + FD_DATA);
		अन्यथा
			*lptr = inb_p(भव_dma_port + FD_DATA);
	पूर्ण
	भव_dma_count = lcount;
	भव_dma_addr = lptr;
	st = inb(भव_dma_port + FD_STATUS);

	अगर (st == STATUS_DMA)
		वापस IRQ_HANDLED;
	अगर (!(st & STATUS_DMA)) अणु
		भव_dma_residue += भव_dma_count;
		भव_dma_count=0;
		करोing_vdma = 0;
		floppy_पूर्णांकerrupt(irq, dev_id);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम vdma_disable_dma(अचिन्हित पूर्णांक dummy)
अणु
	करोing_vdma = 0;
	भव_dma_residue += भव_dma_count;
	भव_dma_count=0;
पूर्ण

अटल व्योम vdma_nop(अचिन्हित पूर्णांक dummy)
अणु
पूर्ण


अटल पूर्णांक vdma_get_dma_residue(अचिन्हित पूर्णांक dummy)
अणु
	वापस भव_dma_count + भव_dma_residue;
पूर्ण


अटल पूर्णांक fd_request_irq(व्योम)
अणु
	अगर (can_use_भव_dma)
		वापस request_irq(FLOPPY_IRQ, floppy_hardपूर्णांक,
				   0, "floppy", शून्य);
	अन्यथा
		वापस request_irq(FLOPPY_IRQ, floppy_पूर्णांकerrupt,
				   0, "floppy", शून्य);
पूर्ण

अटल पूर्णांक vdma_dma_setup(अक्षर *addr, अचिन्हित दीर्घ size, पूर्णांक mode, पूर्णांक io)
अणु
	करोing_vdma = 1;
	भव_dma_port = io;
	भव_dma_mode = (mode  == DMA_MODE_WRITE);
	भव_dma_addr = addr;
	भव_dma_count = size;
	भव_dma_residue = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक hard_dma_setup(अक्षर *addr, अचिन्हित दीर्घ size, पूर्णांक mode, पूर्णांक io)
अणु
	अटल अचिन्हित दीर्घ prev_size;
	अटल dma_addr_t bus_addr = 0;
	अटल अक्षर *prev_addr;
	अटल पूर्णांक prev_dir;
	पूर्णांक dir;

	करोing_vdma = 0;
	dir = (mode == DMA_MODE_READ) ? PCI_DMA_FROMDEVICE : PCI_DMA_TODEVICE;

	अगर (bus_addr 
	    && (addr != prev_addr || size != prev_size || dir != prev_dir)) अणु
		/* dअगरferent from last समय -- unmap prev */
		pci_unmap_single(isa_bridge_pcidev, bus_addr, prev_size, prev_dir);
		bus_addr = 0;
	पूर्ण

	अगर (!bus_addr)	/* need to map it */
		bus_addr = pci_map_single(isa_bridge_pcidev, addr, size, dir);

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

अटल काष्ठा fd_dma_ops real_dma_ops =
अणु
	._disable_dma = disable_dma,
	._मुक्त_dma = मुक्त_dma,
	._get_dma_residue = get_dma_residue,
	._dma_setup = hard_dma_setup
पूर्ण;

अटल काष्ठा fd_dma_ops virt_dma_ops =
अणु
	._disable_dma = vdma_disable_dma,
	._मुक्त_dma = vdma_nop,
	._get_dma_residue = vdma_get_dma_residue,
	._dma_setup = vdma_dma_setup
पूर्ण;

अटल पूर्णांक fd_request_dma(व्योम)
अणु
	अगर (can_use_भव_dma & 1) अणु
		fd_ops = &virt_dma_ops;
		वापस 0;
	पूर्ण
	अन्यथा अणु
		fd_ops = &real_dma_ops;
		वापस request_dma(FLOPPY_DMA, "floppy");
	पूर्ण
पूर्ण

अटल पूर्णांक FDC1 = 0x3f0;
अटल पूर्णांक FDC2 = -1;

/*
 * Again, the CMOS inक्रमmation not available
 */
#घोषणा FLOPPY0_TYPE 6
#घोषणा FLOPPY1_TYPE 0

#घोषणा N_FDC 2			/* Don't change this! */
#घोषणा N_DRIVE 8

/*
 * The PowerPC has no problems with floppy DMA crossing 64k borders.
 */
#घोषणा CROSS_64KB(a,s)	(0)

#घोषणा EXTRA_FLOPPY_PARAMS

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __ASM_POWERPC_FLOPPY_H */
