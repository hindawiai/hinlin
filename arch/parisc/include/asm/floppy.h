<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*    Architecture specअगरic parts of the Floppy driver
 *
 *    Linux/PA-RISC Project (http://www.parisc-linux.org/)
 *    Copyright (C) 2000 Matthew Wilcox (willy a debian . org)
 *    Copyright (C) 2000 Dave Kennedy
 */
#अगर_अघोषित __ASM_PARISC_FLOPPY_H
#घोषणा __ASM_PARISC_FLOPPY_H

#समावेश <linux/vदो_स्मृति.h>


/*
 * The DMA channel used by the floppy controller cannot access data at
 * addresses >= 16MB
 *
 * Went back to the 1MB limit, as some people had problems with the floppy
 * driver otherwise. It करोesn't matter much क्रम perक्रमmance anyway, as most
 * floppy accesses go through the track buffer.
 */
#घोषणा _CROSS_64KB(a,s,vdma) \
(!(vdma) && ((अचिन्हित दीर्घ)(a)/K_64 != ((अचिन्हित दीर्घ)(a) + (s) - 1) / K_64))

#घोषणा CROSS_64KB(a,s) _CROSS_64KB(a,s,use_भव_dma & 1)


#घोषणा SW fd_routine[use_भव_dma&1]
#घोषणा CSW fd_routine[can_use_भव_dma & 1]


#घोषणा fd_inb(base, reg)		पढ़ोb((base) + (reg))
#घोषणा fd_outb(value, base, reg)	ग_लिखोb(value, (base) + (reg))

#घोषणा fd_request_dma()        CSW._request_dma(FLOPPY_DMA,"floppy")
#घोषणा fd_मुक्त_dma()           CSW._मुक्त_dma(FLOPPY_DMA)
#घोषणा fd_enable_irq()         enable_irq(FLOPPY_IRQ)
#घोषणा fd_disable_irq()        disable_irq(FLOPPY_IRQ)
#घोषणा fd_मुक्त_irq()		मुक्त_irq(FLOPPY_IRQ, शून्य)
#घोषणा fd_get_dma_residue()    SW._get_dma_residue(FLOPPY_DMA)
#घोषणा fd_dma_mem_alloc(size)	SW._dma_mem_alloc(size)
#घोषणा fd_dma_setup(addr, size, mode, io) SW._dma_setup(addr, size, mode, io)

#घोषणा FLOPPY_CAN_FALLBACK_ON_NODMA

अटल पूर्णांक भव_dma_count=0;
अटल पूर्णांक भव_dma_residue=0;
अटल अक्षर *भव_dma_addr=0;
अटल पूर्णांक भव_dma_mode=0;
अटल पूर्णांक करोing_pdma=0;

अटल व्योम floppy_hardपूर्णांक(पूर्णांक irq, व्योम *dev_id, काष्ठा pt_regs * regs)
अणु
	रेजिस्टर अचिन्हित अक्षर st;

#अघोषित TRACE_FLPY_INT

#अगर_घोषित TRACE_FLPY_INT
	अटल पूर्णांक calls=0;
	अटल पूर्णांक bytes=0;
	अटल पूर्णांक dma_रुको=0;
#पूर्ण_अगर
	अगर (!करोing_pdma) अणु
		floppy_पूर्णांकerrupt(irq, dev_id, regs);
		वापस;
	पूर्ण

#अगर_घोषित TRACE_FLPY_INT
	अगर(!calls)
		bytes = भव_dma_count;
#पूर्ण_अगर

	अणु
		रेजिस्टर पूर्णांक lcount;
		रेजिस्टर अक्षर *lptr = भव_dma_addr;

		क्रम (lcount = भव_dma_count; lcount; lcount--) अणु
			st = fd_inb(भव_dma_port, FD_STATUS);
			st &= STATUS_DMA | STATUS_READY;
			अगर (st != (STATUS_DMA | STATUS_READY))
				अवरोध;
			अगर (भव_dma_mode) अणु
				fd_outb(*lptr, भव_dma_port, FD_DATA);
			पूर्ण अन्यथा अणु
				*lptr = fd_inb(भव_dma_port, FD_DATA);
			पूर्ण
			lptr++;
		पूर्ण
		भव_dma_count = lcount;
		भव_dma_addr = lptr;
		st = fd_inb(भव_dma_port, FD_STATUS);
	पूर्ण

#अगर_घोषित TRACE_FLPY_INT
	calls++;
#पूर्ण_अगर
	अगर (st == STATUS_DMA)
		वापस;
	अगर (!(st & STATUS_DMA)) अणु
		भव_dma_residue += भव_dma_count;
		भव_dma_count = 0;
#अगर_घोषित TRACE_FLPY_INT
		prपूर्णांकk("count=%x, residue=%x calls=%d bytes=%d dma_wait=%d\n", 
		       भव_dma_count, भव_dma_residue, calls, bytes,
		       dma_रुको);
		calls = 0;
		dma_रुको=0;
#पूर्ण_अगर
		करोing_pdma = 0;
		floppy_पूर्णांकerrupt(irq, dev_id, regs);
		वापस;
	पूर्ण
#अगर_घोषित TRACE_FLPY_INT
	अगर (!भव_dma_count)
		dma_रुको++;
#पूर्ण_अगर
पूर्ण

अटल व्योम fd_disable_dma(व्योम)
अणु
	अगर(! (can_use_भव_dma & 1))
		disable_dma(FLOPPY_DMA);
	करोing_pdma = 0;
	भव_dma_residue += भव_dma_count;
	भव_dma_count=0;
पूर्ण

अटल पूर्णांक vdma_request_dma(अचिन्हित पूर्णांक dmanr, स्थिर अक्षर * device_id)
अणु
	वापस 0;
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
	अगर(can_use_भव_dma)
		वापस request_irq(FLOPPY_IRQ, floppy_hardपूर्णांक,
				   0, "floppy", शून्य);
	अन्यथा
		वापस request_irq(FLOPPY_IRQ, floppy_पूर्णांकerrupt,
				   0, "floppy", शून्य);
पूर्ण

अटल अचिन्हित दीर्घ dma_mem_alloc(अचिन्हित दीर्घ size)
अणु
	वापस __get_dma_pages(GFP_KERNEL, get_order(size));
पूर्ण


अटल अचिन्हित दीर्घ vdma_mem_alloc(अचिन्हित दीर्घ size)
अणु
	वापस (अचिन्हित दीर्घ) vदो_स्मृति(size);

पूर्ण

#घोषणा nodma_mem_alloc(size) vdma_mem_alloc(size)

अटल व्योम _fd_dma_mem_मुक्त(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	अगर((अचिन्हित पूर्णांक) addr >= (अचिन्हित पूर्णांक) high_memory)
		वापस vमुक्त((व्योम *)addr);
	अन्यथा
		मुक्त_pages(addr, get_order(size));		
पूर्ण

#घोषणा fd_dma_mem_मुक्त(addr, size)  _fd_dma_mem_मुक्त(addr, size) 

अटल व्योम _fd_chose_dma_mode(अक्षर *addr, अचिन्हित दीर्घ size)
अणु
	अगर(can_use_भव_dma == 2) अणु
		अगर((अचिन्हित पूर्णांक) addr >= (अचिन्हित पूर्णांक) high_memory ||
		   virt_to_bus(addr) >= 0x1000000 ||
		   _CROSS_64KB(addr, size, 0))
			use_भव_dma = 1;
		अन्यथा
			use_भव_dma = 0;
	पूर्ण अन्यथा अणु
		use_भव_dma = can_use_भव_dma & 1;
	पूर्ण
पूर्ण

#घोषणा fd_chose_dma_mode(addr, size) _fd_chose_dma_mode(addr, size)


अटल पूर्णांक vdma_dma_setup(अक्षर *addr, अचिन्हित दीर्घ size, पूर्णांक mode, पूर्णांक io)
अणु
	करोing_pdma = 1;
	भव_dma_port = io;
	भव_dma_mode = (mode  == DMA_MODE_WRITE);
	भव_dma_addr = addr;
	भव_dma_count = size;
	भव_dma_residue = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक hard_dma_setup(अक्षर *addr, अचिन्हित दीर्घ size, पूर्णांक mode, पूर्णांक io)
अणु
#अगर_घोषित FLOPPY_SANITY_CHECK
	अगर (CROSS_64KB(addr, size)) अणु
		prपूर्णांकk("DMA crossing 64-K boundary %p-%p\n", addr, addr+size);
		वापस -1;
	पूर्ण
#पूर्ण_अगर
	/* actual, physical DMA */
	करोing_pdma = 0;
	clear_dma_ff(FLOPPY_DMA);
	set_dma_mode(FLOPPY_DMA,mode);
	set_dma_addr(FLOPPY_DMA,virt_to_bus(addr));
	set_dma_count(FLOPPY_DMA,size);
	enable_dma(FLOPPY_DMA);
	वापस 0;
पूर्ण

अटल काष्ठा fd_routine_l अणु
	पूर्णांक (*_request_dma)(अचिन्हित पूर्णांक dmanr, स्थिर अक्षर * device_id);
	व्योम (*_मुक्त_dma)(अचिन्हित पूर्णांक dmanr);
	पूर्णांक (*_get_dma_residue)(अचिन्हित पूर्णांक dummy);
	अचिन्हित दीर्घ (*_dma_mem_alloc) (अचिन्हित दीर्घ size);
	पूर्णांक (*_dma_setup)(अक्षर *addr, अचिन्हित दीर्घ size, पूर्णांक mode, पूर्णांक io);
पूर्ण fd_routine[] = अणु
	अणु
		request_dma,
		मुक्त_dma,
		get_dma_residue,
		dma_mem_alloc,
		hard_dma_setup
	पूर्ण,
	अणु
		vdma_request_dma,
		vdma_nop,
		vdma_get_dma_residue,
		vdma_mem_alloc,
		vdma_dma_setup
	पूर्ण
पूर्ण;


अटल पूर्णांक FDC1 = 0x3f0; /* Lies.  Floppy controller is memory mapped, not io mapped */
अटल पूर्णांक FDC2 = -1;

#घोषणा FLOPPY0_TYPE	0
#घोषणा FLOPPY1_TYPE	0

#घोषणा N_FDC 1
#घोषणा N_DRIVE 8

#घोषणा EXTRA_FLOPPY_PARAMS

#पूर्ण_अगर /* __ASM_PARISC_FLOPPY_H */
