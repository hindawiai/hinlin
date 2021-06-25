<शैली गुरु>
/*
 * Architecture specअगरic parts of the Floppy driver
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995 - 2000 Ralf Baechle
 */
#अगर_अघोषित _ASM_FLOPPY_H
#घोषणा _ASM_FLOPPY_H

#समावेश <यंत्र/पन.स>

अटल अंतरभूत व्योम fd_cacheflush(अक्षर * addr, दीर्घ size)
अणु
	dma_cache_wback_inv((अचिन्हित दीर्घ)addr, size);
पूर्ण

#घोषणा MAX_BUFFER_SECTORS 24


/*
 * And on Mips's the CMOS info fails also ...
 *
 * FIXME: This inक्रमmation should come from the ARC configuration tree
 *	  or wherever a particular machine has stored this ...
 */
#घोषणा FLOPPY0_TYPE		fd_drive_type(0)
#घोषणा FLOPPY1_TYPE		fd_drive_type(1)

#घोषणा FDC1			fd_getfdaddr1()

#घोषणा N_FDC 1			/* करो you *really* want a second controller? */
#घोषणा N_DRIVE 8

/*
 * The DMA channel used by the floppy controller cannot access data at
 * addresses >= 16MB
 *
 * Went back to the 1MB limit, as some people had problems with the floppy
 * driver otherwise. It करोesn't matter much क्रम perक्रमmance anyway, as most
 * floppy accesses go through the track buffer.
 *
 * On MIPSes using vdma, this actually means that *all* transfers go thru
 * the * track buffer since 0x1000000 is always smaller than KSEG0/1.
 * Actually this needs to be a bit more complicated since the so much dअगरferent
 * hardware available with MIPS CPUs ...
 */
#घोषणा CROSS_64KB(a, s) ((अचिन्हित दीर्घ)(a)/K_64 != ((अचिन्हित दीर्घ)(a) + (s) - 1) / K_64)

#घोषणा EXTRA_FLOPPY_PARAMS

#समावेश <floppy.h>

#पूर्ण_अगर /* _ASM_FLOPPY_H */
