<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/floppy.h
 *
 *  Copyright (C) 1996-2000 Russell King
 *
 *  Note that we करोn't touch FLOPPY_DMA nor FLOPPY_IRQ here
 */
#अगर_अघोषित __ASM_ARM_FLOPPY_H
#घोषणा __ASM_ARM_FLOPPY_H

#घोषणा fd_outb(val, base, reg)						\
	करो अणु								\
		पूर्णांक new_val = (val);					\
		अगर ((reg) == FD_DOR) अणु					\
			अगर (new_val & 0xf0)				\
				new_val = (new_val & 0x0c) |		\
					  floppy_selects[new_val & 3];	\
			अन्यथा						\
				new_val &= 0x0c;			\
		पूर्ण							\
		outb(new_val, (base) + (reg));				\
	पूर्ण जबतक(0)

#घोषणा fd_inb(base, reg)	inb((base) + (reg))
#घोषणा fd_request_irq()	request_irq(IRQ_FLOPPYDISK,floppy_पूर्णांकerrupt,\
					    0,"floppy",शून्य)
#घोषणा fd_मुक्त_irq()		मुक्त_irq(IRQ_FLOPPYDISK,शून्य)
#घोषणा fd_disable_irq()	disable_irq(IRQ_FLOPPYDISK)
#घोषणा fd_enable_irq()		enable_irq(IRQ_FLOPPYDISK)

अटल अंतरभूत पूर्णांक fd_dma_setup(व्योम *data, अचिन्हित पूर्णांक length,
			       अचिन्हित पूर्णांक mode, अचिन्हित दीर्घ addr)
अणु
	set_dma_mode(DMA_FLOPPY, mode);
	__set_dma_addr(DMA_FLOPPY, data);
	set_dma_count(DMA_FLOPPY, length);
	भव_dma_port = addr;
	enable_dma(DMA_FLOPPY);
	वापस 0;
पूर्ण
#घोषणा fd_dma_setup		fd_dma_setup

#घोषणा fd_request_dma()	request_dma(DMA_FLOPPY,"floppy")
#घोषणा fd_मुक्त_dma()		मुक्त_dma(DMA_FLOPPY)
#घोषणा fd_disable_dma()	disable_dma(DMA_FLOPPY)

/* need to clean up dma.h */
#घोषणा DMA_FLOPPYDISK		DMA_FLOPPY

/* Floppy_selects is the list of DOR's to select drive fd
 *
 * On initialisation, the floppy list is scanned, and the drives allocated
 * in the order that they are found.  This is करोne by seeking the drive
 * to a non-zero track, and then restoring it to track 0.  If an error occurs,
 * then there is no floppy drive present.       [to be put back in again]
 */
अटल अचिन्हित अक्षर floppy_selects[4] = अणु 0x10, 0x21, 0x23, 0x33 पूर्ण;

#घोषणा FDC1 (0x3f0)

#घोषणा FLOPPY0_TYPE 4
#घोषणा FLOPPY1_TYPE 4

#घोषणा N_FDC 1
#घोषणा N_DRIVE 4

#घोषणा CROSS_64KB(a,s) (0)

/*
 * This allows people to reverse the order of
 * fd0 and fd1, in हाल their hardware is
 * strangely connected (as some RiscPCs
 * and A5000s seem to be).
 */
अटल व्योम driveswap(पूर्णांक *पूर्णांकs, पूर्णांक dummy, पूर्णांक dummy2)
अणु
	swap(floppy_selects[0], floppy_selects[1]);
पूर्ण

#घोषणा EXTRA_FLOPPY_PARAMS ,अणु "driveswap", &driveswap, शून्य, 0, 0 पूर्ण
	
#पूर्ण_अगर
