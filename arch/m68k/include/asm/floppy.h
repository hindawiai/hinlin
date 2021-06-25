<शैली गुरु>
/*
 * Implementation independent bits of the Floppy driver.
 *
 * much of this file is derived from what was originally the Q40 floppy driver.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1999, 2000, 2001
 *
 * Sun3x support added 2/4/2000 Sam Creasey (sammy@sammy.net)
 *
 */

#समावेश <यंत्र/पन.स>

#समावेश <linux/vदो_स्मृति.h>

यंत्रlinkage irqवापस_t floppy_hardपूर्णांक(पूर्णांक irq, व्योम *dev_id);

/* स्थिरants... */

#अघोषित MAX_DMA_ADDRESS
#घोषणा MAX_DMA_ADDRESS   0x00  /* nothing like that */


/*
 * Again, the CMOS inक्रमmation करोesn't work on m68k..
 */
#घोषणा FLOPPY0_TYPE (MACH_IS_Q40 ? 6 : 4)
#घोषणा FLOPPY1_TYPE 0

/* basically PC init + set use_भव_dma */
#घोषणा  FDC1 m68k_floppy_init()

#घोषणा N_FDC 1
#घोषणा N_DRIVE 8


/* vdma globals adapted from यंत्र-i386/floppy.h */

अटल पूर्णांक भव_dma_count=0;
अटल पूर्णांक भव_dma_residue=0;
अटल अक्षर *भव_dma_addr=शून्य;
अटल पूर्णांक भव_dma_mode=0;
अटल पूर्णांक करोing_pdma=0;

#समावेश <यंत्र/sun3xflop.h>

बाह्य spinlock_t  dma_spin_lock;

अटल __अंतरभूत__ अचिन्हित दीर्घ claim_dma_lock(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&dma_spin_lock, flags);
	वापस flags;
पूर्ण

अटल __अंतरभूत__ व्योम release_dma_lock(अचिन्हित दीर्घ flags)
अणु
	spin_unlock_irqrestore(&dma_spin_lock, flags);
पूर्ण


अटल __अंतरभूत__ अचिन्हित अक्षर fd_inb(पूर्णांक base, पूर्णांक reg)
अणु
	अगर(MACH_IS_Q40)
		वापस inb_p(base + reg);
	अन्यथा अगर(MACH_IS_SUN3X)
		वापस sun3x_82072_fd_inb(base + reg);
	वापस 0;
पूर्ण

अटल __अंतरभूत__ व्योम fd_outb(अचिन्हित अक्षर value, पूर्णांक base, पूर्णांक reg)
अणु
	अगर(MACH_IS_Q40)
		outb_p(value, base + reg);
	अन्यथा अगर(MACH_IS_SUN3X)
		sun3x_82072_fd_outb(value, base + reg);
पूर्ण


अटल पूर्णांक fd_request_irq(व्योम)
अणु
	अगर(MACH_IS_Q40)
		वापस request_irq(FLOPPY_IRQ, floppy_hardपूर्णांक,
				   0, "floppy", floppy_hardपूर्णांक);
	अन्यथा अगर(MACH_IS_SUN3X)
		वापस sun3xflop_request_irq();
	वापस -ENXIO;
पूर्ण

अटल व्योम fd_मुक्त_irq(व्योम)
अणु
	अगर(MACH_IS_Q40)
		मुक्त_irq(FLOPPY_IRQ, floppy_hardपूर्णांक);
पूर्ण

#घोषणा fd_request_dma()        vdma_request_dma(FLOPPY_DMA,"floppy")
#घोषणा fd_get_dma_residue()    vdma_get_dma_residue(FLOPPY_DMA)
#घोषणा fd_dma_mem_alloc(size)	vdma_mem_alloc(size)
#घोषणा fd_dma_setup(addr, size, mode, io) vdma_dma_setup(addr, size, mode, io)

#घोषणा fd_enable_irq()           /* nothing... */
#घोषणा fd_disable_irq()          /* nothing... */

#घोषणा fd_मुक्त_dma()             /* nothing */

/* No 64k boundary crossing problems on Q40 - no DMA at all */
#घोषणा CROSS_64KB(a,s) (0)

#घोषणा DMA_MODE_READ  0x44    /* i386 look-alike */
#घोषणा DMA_MODE_WRITE 0x48


अटल पूर्णांक m68k_floppy_init(व्योम)
अणु
  use_भव_dma =1;
  can_use_भव_dma = 1;


  अगर (MACH_IS_Q40)
	  वापस 0x3f0;
  अन्यथा अगर(MACH_IS_SUN3X)
	  वापस sun3xflop_init();
  अन्यथा
    वापस -1;
पूर्ण


अटल पूर्णांक vdma_request_dma(अचिन्हित पूर्णांक dmanr, स्थिर अक्षर * device_id)
अणु
	वापस 0;
पूर्ण


अटल पूर्णांक vdma_get_dma_residue(अचिन्हित पूर्णांक dummy)
अणु
	वापस भव_dma_count + भव_dma_residue;
पूर्ण


अटल अचिन्हित दीर्घ vdma_mem_alloc(अचिन्हित दीर्घ size)
अणु
	वापस (अचिन्हित दीर्घ) vदो_स्मृति(size);

पूर्ण

अटल व्योम _fd_dma_mem_मुक्त(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
        vमुक्त((व्योम *)addr);
पूर्ण
#घोषणा fd_dma_mem_मुक्त(addr,size) _fd_dma_mem_मुक्त(addr, size)


/* choose_dma_mode ???*/

अटल पूर्णांक vdma_dma_setup(अक्षर *addr, अचिन्हित दीर्घ size, पूर्णांक mode, पूर्णांक io)
अणु
	करोing_pdma = 1;
	भव_dma_port = (MACH_IS_Q40 ? io : 0);
	भव_dma_mode = (mode  == DMA_MODE_WRITE);
	भव_dma_addr = addr;
	भव_dma_count = size;
	भव_dma_residue = 0;
	वापस 0;
पूर्ण



अटल व्योम fd_disable_dma(व्योम)
अणु
	करोing_pdma = 0;
	भव_dma_residue += भव_dma_count;
	भव_dma_count=0;
पूर्ण



/* this is the only truly Q40 specअगरic function */

यंत्रlinkage irqवापस_t floppy_hardपूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	रेजिस्टर अचिन्हित अक्षर st;

#अघोषित TRACE_FLPY_INT
#घोषणा NO_FLOPPY_ASSEMBLER

#अगर_घोषित TRACE_FLPY_INT
	अटल पूर्णांक calls=0;
	अटल पूर्णांक bytes=0;
	अटल पूर्णांक dma_रुको=0;
#पूर्ण_अगर
	अगर(!करोing_pdma) अणु
		floppy_पूर्णांकerrupt(irq, dev_id);
		वापस IRQ_HANDLED;
	पूर्ण

#अगर_घोषित TRACE_FLPY_INT
	अगर(!calls)
		bytes = भव_dma_count;
#पूर्ण_अगर

	अणु
		रेजिस्टर पूर्णांक lcount;
		रेजिस्टर अक्षर *lptr;

		/* serve 1st byte fast: */

		st=1;
		क्रम(lcount=भव_dma_count, lptr=भव_dma_addr;
		    lcount; lcount--, lptr++) अणु
			st = inb(भव_dma_port + FD_STATUS);
			st &= STATUS_DMA | STATUS_READY;
			अगर (st != (STATUS_DMA | STATUS_READY))
				अवरोध;
			अगर(भव_dma_mode)
				outb_p(*lptr, भव_dma_port + FD_DATA);
			अन्यथा
				*lptr = inb_p(भव_dma_port + FD_DATA);
		पूर्ण

		भव_dma_count = lcount;
		भव_dma_addr = lptr;
		st = inb(भव_dma_port + FD_STATUS);
	पूर्ण

#अगर_घोषित TRACE_FLPY_INT
	calls++;
#पूर्ण_अगर
	अगर (st == STATUS_DMA)
		वापस IRQ_HANDLED;
	अगर (!(st & STATUS_DMA)) अणु
		भव_dma_residue += भव_dma_count;
		भव_dma_count=0;
#अगर_घोषित TRACE_FLPY_INT
		pr_info("count=%x, residue=%x calls=%d bytes=%d dma_wait=%d\n",
			भव_dma_count, भव_dma_residue, calls, bytes,
			dma_रुको);
		calls = 0;
		dma_रुको=0;
#पूर्ण_अगर
		करोing_pdma = 0;
		floppy_पूर्णांकerrupt(irq, dev_id);
		वापस IRQ_HANDLED;
	पूर्ण
#अगर_घोषित TRACE_FLPY_INT
	अगर(!भव_dma_count)
		dma_रुको++;
#पूर्ण_अगर
	वापस IRQ_HANDLED;
पूर्ण

#घोषणा EXTRA_FLOPPY_PARAMS
