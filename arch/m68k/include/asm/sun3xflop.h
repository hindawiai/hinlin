<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* sun3xflop.h: Sun3/80 specअगरic parts of the floppy driver.
 *
 * Derived partially from यंत्र-sparc/floppy.h, which is:
 *     Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 *
 * Sun3x version 2/4/2000 Sam Creasey (sammy@sammy.net)
 */

#अगर_अघोषित __ASM_SUN3X_FLOPPY_H
#घोषणा __ASM_SUN3X_FLOPPY_H

#समावेश <linux/pgtable.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/sun3x.h>

/* शेष पूर्णांकerrupt vector */
#घोषणा SUN3X_FDC_IRQ 0x40

/* some स्थिरants */
#घोषणा FCR_TC 0x1
#घोषणा FCR_EJECT 0x2
#घोषणा FCR_MTRON 0x4
#घोषणा FCR_DSEL1 0x8
#घोषणा FCR_DSEL0 0x10

/* We करोn't need no stinkin' I/O port allocation crap. */
#अघोषित release_region
#अघोषित request_region
#घोषणा release_region(X, Y)	करो अणु पूर्ण जबतक(0)
#घोषणा request_region(X, Y, Z)	(1)

काष्ठा sun3xflop_निजी अणु
	अस्थिर अचिन्हित अक्षर *status_r;
	अस्थिर अचिन्हित अक्षर *data_r;
	अस्थिर अचिन्हित अक्षर *fcr_r;
	अस्थिर अचिन्हित अक्षर *fvr_r;
	अचिन्हित अक्षर fcr;
पूर्ण sun3x_fdc;

/* Super paranoid... */
#अघोषित HAVE_DISABLE_HLT

/* Routines unique to each controller type on a Sun. */
अटल अचिन्हित अक्षर sun3x_82072_fd_inb(पूर्णांक port)
अणु
	अटल पूर्णांक once = 0;
//	udelay(5);
	चयन(port & 7) अणु
	शेष:
		pr_crit("floppy: Asked to read unknown port %d\n", port);
		panic("floppy: Port bolixed.");
	हाल 4: /* FD_STATUS */
		वापस (*sun3x_fdc.status_r) & ~STATUS_DMA;
	हाल 5: /* FD_DATA */
		वापस (*sun3x_fdc.data_r);
	हाल 7: /* FD_सूची */
		/* ugly hack, I can't find a way to actually detect the disk */
		अगर(!once) अणु
			once = 1;
			वापस 0x80;
		पूर्ण
		वापस 0;
	पूर्ण;
	panic("sun_82072_fd_inb: How did I get here?");
पूर्ण

अटल व्योम sun3x_82072_fd_outb(अचिन्हित अक्षर value, पूर्णांक port)
अणु
//	udelay(5);
	चयन(port & 7) अणु
	शेष:
		pr_crit("floppy: Asked to write to unknown port %d\n", port);
		panic("floppy: Port bolixed.");
	हाल 2: /* FD_DOR */
		/* Oh geese, 82072 on the Sun has no DOR रेजिस्टर,
		 * so we make करो with taunting the FCR.
		 *
		 * ASSUMPTIONS:  There will only ever be one floppy
		 *               drive attached to a Sun controller
		 *               and it will be at drive zero.
		 */

	अणु
		अचिन्हित अक्षर fcr = sun3x_fdc.fcr;

		अगर(value & 0x10) अणु
			fcr |= (FCR_DSEL0 | FCR_MTRON);
		पूर्ण अन्यथा
			fcr &= ~(FCR_DSEL0 | FCR_MTRON);


		अगर(fcr != sun3x_fdc.fcr) अणु
			*(sun3x_fdc.fcr_r) = fcr;
			sun3x_fdc.fcr = fcr;
		पूर्ण
	पूर्ण
		अवरोध;
	हाल 5: /* FD_DATA */
		*(sun3x_fdc.data_r) = value;
		अवरोध;
	हाल 7: /* FD_DCR */
		*(sun3x_fdc.status_r) = value;
		अवरोध;
	हाल 4: /* FD_STATUS */
		*(sun3x_fdc.status_r) = value;
		अवरोध;
	पूर्ण
	वापस;
पूर्ण


यंत्रlinkage irqवापस_t sun3xflop_hardपूर्णांक(पूर्णांक irq, व्योम *dev_id)
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

//	pr_info("doing pdma\n");// st %x\न", sun_fdc->status_82072);

#अगर_घोषित TRACE_FLPY_INT
	अगर(!calls)
		bytes = भव_dma_count;
#पूर्ण_अगर

	अणु
		रेजिस्टर पूर्णांक lcount;
		रेजिस्टर अक्षर *lptr;

		क्रम(lcount=भव_dma_count, lptr=भव_dma_addr;
		    lcount; lcount--, lptr++) अणु
/*			st=fd_inb(भव_dma_port+4) & 0x80 ;  */
			st = *(sun3x_fdc.status_r);
/*			अगर(st != 0xa0)                  */
/*				अवरोध;                  */

			अगर((st & 0x80) == 0) अणु
				भव_dma_count = lcount;
				भव_dma_addr = lptr;
				वापस IRQ_HANDLED;
			पूर्ण

			अगर((st & 0x20) == 0)
				अवरोध;

			अगर(भव_dma_mode)
/*				fd_outb(*lptr, भव_dma_port+5); */
				*(sun3x_fdc.data_r) = *lptr;
			अन्यथा
/*				*lptr = fd_inb(भव_dma_port+5); */
				*lptr = *(sun3x_fdc.data_r);
		पूर्ण

		भव_dma_count = lcount;
		भव_dma_addr = lptr;
/*		st = fd_inb(भव_dma_port+4);   */
		st = *(sun3x_fdc.status_r);
	पूर्ण

#अगर_घोषित TRACE_FLPY_INT
	calls++;
#पूर्ण_अगर
//	pr_info("st=%02x\n", st);
	अगर(st == 0x20)
		वापस IRQ_HANDLED;
	अगर(!(st & 0x20)) अणु
		भव_dma_residue += भव_dma_count;
		भव_dma_count=0;
		करोing_pdma = 0;

#अगर_घोषित TRACE_FLPY_INT
		pr_info("count=%x, residue=%x calls=%d bytes=%x dma_wait=%d\n",
			भव_dma_count, भव_dma_residue, calls, bytes,
			dma_रुको);
		calls = 0;
		dma_रुको=0;
#पूर्ण_अगर

		floppy_पूर्णांकerrupt(irq, dev_id);
		वापस IRQ_HANDLED;
	पूर्ण


#अगर_घोषित TRACE_FLPY_INT
	अगर(!भव_dma_count)
		dma_रुको++;
#पूर्ण_अगर
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sun3xflop_request_irq(व्योम)
अणु
	अटल पूर्णांक once = 0;
	पूर्णांक error;

	अगर(!once) अणु
		once = 1;
		error = request_irq(FLOPPY_IRQ, sun3xflop_hardपूर्णांक,
				    0, "floppy", शून्य);
		वापस ((error == 0) ? 0 : -1);
	पूर्ण अन्यथा वापस 0;
पूर्ण

अटल व्योम __init floppy_set_flags(पूर्णांक *पूर्णांकs,पूर्णांक param, पूर्णांक param2);

अटल पूर्णांक sun3xflop_init(व्योम)
अणु
	अगर(FLOPPY_IRQ < 0x40)
		FLOPPY_IRQ = SUN3X_FDC_IRQ;

	sun3x_fdc.status_r = (अस्थिर अचिन्हित अक्षर *)SUN3X_FDC;
	sun3x_fdc.data_r  = (अस्थिर अचिन्हित अक्षर *)(SUN3X_FDC+1);
	sun3x_fdc.fcr_r = (अस्थिर अचिन्हित अक्षर *)SUN3X_FDC_FCR;
	sun3x_fdc.fvr_r = (अस्थिर अचिन्हित अक्षर *)SUN3X_FDC_FVR;
	sun3x_fdc.fcr = 0;

	/* Last minute sanity check... */
	अगर(*sun3x_fdc.status_r == 0xff) अणु
		वापस -1;
	पूर्ण

	*sun3x_fdc.fvr_r = FLOPPY_IRQ;

	*sun3x_fdc.fcr_r = FCR_TC;
	udelay(10);
	*sun3x_fdc.fcr_r = 0;

	/* Success... */
	floppy_set_flags(शून्य, 1, FD_BROKEN_DCL); // I करोn't know how to detect this.
	allowed_drive_mask = 0x01;
	वापस (पूर्णांक) SUN3X_FDC;
पूर्ण

/* I'm not precisely sure this eject routine works */
अटल पूर्णांक sun3x_eject(व्योम)
अणु
	अगर(MACH_IS_SUN3X) अणु

		sun3x_fdc.fcr |= (FCR_DSEL0 | FCR_EJECT);
		*(sun3x_fdc.fcr_r) = sun3x_fdc.fcr;
		udelay(10);
		sun3x_fdc.fcr &= ~(FCR_DSEL0 | FCR_EJECT);
		*(sun3x_fdc.fcr_r) = sun3x_fdc.fcr;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा fd_eject(drive) sun3x_eject()

#पूर्ण_अगर /* !(__ASM_SUN3X_FLOPPY_H) */
