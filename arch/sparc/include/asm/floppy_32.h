<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* यंत्र/floppy.h: Sparc specअगरic parts of the Floppy driver.
 *
 * Copyright (C) 1995 David S. Miller (davem@davemloft.net)
 */

#अगर_अघोषित __ASM_SPARC_FLOPPY_H
#घोषणा __ASM_SPARC_FLOPPY_H

#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/auxपन.स>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/irq.h>

/* We करोn't need no stinkin' I/O port allocation crap. */
#अघोषित release_region
#अघोषित request_region
#घोषणा release_region(X, Y)	करो अणु पूर्ण जबतक(0)
#घोषणा request_region(X, Y, Z)	(1)

/* References:
 * 1) Netbsd Sun floppy driver.
 * 2) NCR 82077 controller manual
 * 3) Intel 82077 controller manual
 */
काष्ठा sun_flpy_controller अणु
	अस्थिर अचिन्हित अक्षर status_82072;  /* Main Status reg. */
#घोषणा dcr_82072              status_82072   /* Digital Control reg. */
#घोषणा status1_82077          status_82072   /* Auxiliary Status reg. 1 */

	अस्थिर अचिन्हित अक्षर data_82072;    /* Data fअगरo. */
#घोषणा status2_82077          data_82072     /* Auxiliary Status reg. 2 */

	अस्थिर अचिन्हित अक्षर करोr_82077;     /* Digital Output reg. */
	अस्थिर अचिन्हित अक्षर tapectl_82077; /* What the? Tape control reg? */

	अस्थिर अचिन्हित अक्षर status_82077;  /* Main Status Register. */
#घोषणा drs_82077              status_82077   /* Digital Rate Select reg. */

	अस्थिर अचिन्हित अक्षर data_82077;    /* Data fअगरo. */
	अस्थिर अचिन्हित अक्षर ___unused;
	अस्थिर अचिन्हित अक्षर dir_82077;     /* Digital Input reg. */
#घोषणा dcr_82077              dir_82077      /* Config Control reg. */
पूर्ण;

/* You'll only ever find one controller on a SparcStation anyways. */
अटल काष्ठा sun_flpy_controller *sun_fdc = शून्य;

काष्ठा sun_floppy_ops अणु
	अचिन्हित अक्षर (*fd_inb)(पूर्णांक port);
	व्योम (*fd_outb)(अचिन्हित अक्षर value, पूर्णांक port);
पूर्ण;

अटल काष्ठा sun_floppy_ops sun_fकरोps;

#घोषणा fd_inb(base, reg)         sun_fकरोps.fd_inb(reg)
#घोषणा fd_outb(value, base, reg) sun_fकरोps.fd_outb(value, reg)
#घोषणा fd_enable_dma()           sun_fd_enable_dma()
#घोषणा fd_disable_dma()          sun_fd_disable_dma()
#घोषणा fd_request_dma()          (0) /* nothing... */
#घोषणा fd_मुक्त_dma()             /* nothing... */
#घोषणा fd_clear_dma_ff()         /* nothing... */
#घोषणा fd_set_dma_mode(mode)     sun_fd_set_dma_mode(mode)
#घोषणा fd_set_dma_addr(addr)     sun_fd_set_dma_addr(addr)
#घोषणा fd_set_dma_count(count)   sun_fd_set_dma_count(count)
#घोषणा fd_enable_irq()           /* nothing... */
#घोषणा fd_disable_irq()          /* nothing... */
#घोषणा fd_request_irq()          sun_fd_request_irq()
#घोषणा fd_मुक्त_irq()             /* nothing... */
#अगर 0  /* P3: added by Alain, these cause a MMU corruption. 19960524 XXX */
#घोषणा fd_dma_mem_alloc(size)    ((अचिन्हित दीर्घ) vदो_स्मृति(size))
#घोषणा fd_dma_mem_मुक्त(addr,size) (vमुक्त((व्योम *)(addr)))
#पूर्ण_अगर

/* XXX This isn't really correct. XXX */
#घोषणा get_dma_residue(x)        (0)

#घोषणा FLOPPY0_TYPE  4
#घोषणा FLOPPY1_TYPE  0

/* Super paranoid... */
#अघोषित HAVE_DISABLE_HLT

/* Here is where we catch the floppy driver trying to initialize,
 * thereक्रमe this is where we call the PROM device tree probing
 * routine etc. on the Sparc.
 */
#घोषणा FDC1                      sun_floppy_init()

#घोषणा N_FDC    1
#घोषणा N_DRIVE  8

/* No 64k boundary crossing problems on the Sparc. */
#घोषणा CROSS_64KB(a,s) (0)

/* Routines unique to each controller type on a Sun. */
अटल व्योम sun_set_करोr(अचिन्हित अक्षर value, पूर्णांक fdc_82077)
अणु
	अगर (fdc_82077)
		sun_fdc->करोr_82077 = value;
पूर्ण

अटल अचिन्हित अक्षर sun_पढ़ो_dir(व्योम)
अणु
	वापस sun_fdc->dir_82077;
पूर्ण

अटल अचिन्हित अक्षर sun_82072_fd_inb(पूर्णांक port)
अणु
	udelay(5);
	चयन (port) अणु
	शेष:
		prपूर्णांकk("floppy: Asked to read unknown port %d\n", port);
		panic("floppy: Port bolixed.");
	हाल FD_STATUS:
		वापस sun_fdc->status_82072 & ~STATUS_DMA;
	हाल FD_DATA:
		वापस sun_fdc->data_82072;
	हाल FD_सूची:
		वापस sun_पढ़ो_dir();
	पूर्ण
	panic("sun_82072_fd_inb: How did I get here?");
पूर्ण

अटल व्योम sun_82072_fd_outb(अचिन्हित अक्षर value, पूर्णांक port)
अणु
	udelay(5);
	चयन (port) अणु
	शेष:
		prपूर्णांकk("floppy: Asked to write to unknown port %d\n", port);
		panic("floppy: Port bolixed.");
	हाल FD_DOR:
		sun_set_करोr(value, 0);
		अवरोध;
	हाल FD_DATA:
		sun_fdc->data_82072 = value;
		अवरोध;
	हाल FD_DCR:
		sun_fdc->dcr_82072 = value;
		अवरोध;
	हाल FD_DSR:
		sun_fdc->status_82072 = value;
		अवरोध;
	पूर्ण
	वापस;
पूर्ण

अटल अचिन्हित अक्षर sun_82077_fd_inb(पूर्णांक port)
अणु
	udelay(5);
	चयन (port) अणु
	शेष:
		prपूर्णांकk("floppy: Asked to read unknown port %d\n", port);
		panic("floppy: Port bolixed.");
	हाल FD_SRA:
		वापस sun_fdc->status1_82077;
	हाल FD_SRB:
		वापस sun_fdc->status2_82077;
	हाल FD_DOR:
		वापस sun_fdc->करोr_82077;
	हाल FD_TDR:
		वापस sun_fdc->tapectl_82077;
	हाल FD_STATUS:
		वापस sun_fdc->status_82077 & ~STATUS_DMA;
	हाल FD_DATA:
		वापस sun_fdc->data_82077;
	हाल FD_सूची:
		वापस sun_पढ़ो_dir();
	पूर्ण
	panic("sun_82077_fd_inb: How did I get here?");
पूर्ण

अटल व्योम sun_82077_fd_outb(अचिन्हित अक्षर value, पूर्णांक port)
अणु
	udelay(5);
	चयन (port) अणु
	शेष:
		prपूर्णांकk("floppy: Asked to write to unknown port %d\n", port);
		panic("floppy: Port bolixed.");
	हाल FD_DOR:
		sun_set_करोr(value, 1);
		अवरोध;
	हाल FD_DATA:
		sun_fdc->data_82077 = value;
		अवरोध;
	हाल FD_DCR:
		sun_fdc->dcr_82077 = value;
		अवरोध;
	हाल FD_DSR:
		sun_fdc->status_82077 = value;
		अवरोध;
	हाल FD_TDR:
		sun_fdc->tapectl_82077 = value;
		अवरोध;
	पूर्ण
	वापस;
पूर्ण

/* For pseuकरो-dma (Sun floppy drives have no real DMA available to
 * them so we must eat the data fअगरo bytes directly ourselves) we have
 * three state variables.  करोing_pdma tells our अंतरभूत low-level
 * assembly floppy पूर्णांकerrupt entry poपूर्णांक whether it should sit and eat
 * bytes from the fअगरo or just transfer control up to the higher level
 * floppy पूर्णांकerrupt c-code.  I tried very hard but I could not get the
 * pseuकरो-dma to work in c-code without getting many overruns and
 * underruns.  If non-zero, करोing_pdma encodes the direction of
 * the transfer क्रम debugging.  1=पढ़ो 2=ग_लिखो
 */

/* Common routines to all controller types on the Sparc. */
अटल अंतरभूत व्योम भव_dma_init(व्योम)
अणु
	/* nothing... */
पूर्ण

अटल अंतरभूत व्योम sun_fd_disable_dma(व्योम)
अणु
	करोing_pdma = 0;
	pdma_base = शून्य;
पूर्ण

अटल अंतरभूत व्योम sun_fd_set_dma_mode(पूर्णांक mode)
अणु
	चयन(mode) अणु
	हाल DMA_MODE_READ:
		करोing_pdma = 1;
		अवरोध;
	हाल DMA_MODE_WRITE:
		करोing_pdma = 2;
		अवरोध;
	शेष:
		prपूर्णांकk("Unknown dma mode %d\n", mode);
		panic("floppy: Giving up...");
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sun_fd_set_dma_addr(अक्षर *buffer)
अणु
	pdma_vaddr = buffer;
पूर्ण

अटल अंतरभूत व्योम sun_fd_set_dma_count(पूर्णांक length)
अणु
	pdma_size = length;
पूर्ण

अटल अंतरभूत व्योम sun_fd_enable_dma(व्योम)
अणु
	pdma_base = pdma_vaddr;
	pdma_areasize = pdma_size;
पूर्ण

पूर्णांक sparc_floppy_request_irq(अचिन्हित पूर्णांक irq, irq_handler_t irq_handler);

अटल पूर्णांक sun_fd_request_irq(व्योम)
अणु
	अटल पूर्णांक once = 0;

	अगर (!once) अणु
		once = 1;
		वापस sparc_floppy_request_irq(FLOPPY_IRQ, floppy_पूर्णांकerrupt);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल काष्ठा linux_prom_रेजिस्टरs fd_regs[2];

अटल पूर्णांक sun_floppy_init(व्योम)
अणु
	काष्ठा platक्रमm_device *op;
	काष्ठा device_node *dp;
	काष्ठा resource r;
	अक्षर state[128];
	phandle fd_node;
	phandle tnode;
	पूर्णांक num_regs;

	use_भव_dma = 1;

	/* Forget it अगर we aren't on a machine that could possibly
	 * ever have a floppy drive.
	 */
	अगर (sparc_cpu_model != sun4m) अणु
		/* We certainly करोn't have a floppy controller. */
		जाओ no_sun_fdc;
	पूर्ण
	/* Well, try to find one. */
	tnode = prom_अ_लोhild(prom_root_node);
	fd_node = prom_searchsiblings(tnode, "obio");
	अगर (fd_node != 0) अणु
		tnode = prom_अ_लोhild(fd_node);
		fd_node = prom_searchsiblings(tnode, "SUNW,fdtwo");
	पूर्ण अन्यथा अणु
		fd_node = prom_searchsiblings(tnode, "fd");
	पूर्ण
	अगर (fd_node == 0) अणु
		जाओ no_sun_fdc;
	पूर्ण

	/* The sun4m lets us know अगर the controller is actually usable. */
	अगर (prom_getproperty(fd_node, "status", state, माप(state)) != -1) अणु
		अगर(!म_भेद(state, "disabled")) अणु
			जाओ no_sun_fdc;
		पूर्ण
	पूर्ण
	num_regs = prom_getproperty(fd_node, "reg", (अक्षर *) fd_regs, माप(fd_regs));
	num_regs = (num_regs / माप(fd_regs[0]));
	prom_apply_obio_ranges(fd_regs, num_regs);
	स_रखो(&r, 0, माप(r));
	r.flags = fd_regs[0].which_io;
	r.start = fd_regs[0].phys_addr;
	sun_fdc = of_ioremap(&r, 0, fd_regs[0].reg_size, "floppy");

	/* Look up irq in platक्रमm_device.
	 * We try "SUNW,fdtwo" and "fd"
	 */
	op = शून्य;
	क्रम_each_node_by_name(dp, "SUNW,fdtwo") अणु
		op = of_find_device_by_node(dp);
		अगर (op)
			अवरोध;
	पूर्ण
	अगर (!op) अणु
		क्रम_each_node_by_name(dp, "fd") अणु
			op = of_find_device_by_node(dp);
			अगर (op)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (!op)
		जाओ no_sun_fdc;

	FLOPPY_IRQ = op->archdata.irqs[0];

	/* Last minute sanity check... */
	अगर (sun_fdc->status_82072 == 0xff) अणु
		sun_fdc = शून्य;
		जाओ no_sun_fdc;
	पूर्ण

	sun_fकरोps.fd_inb = sun_82077_fd_inb;
	sun_fकरोps.fd_outb = sun_82077_fd_outb;
	fdc_status = &sun_fdc->status_82077;

	अगर (sun_fdc->करोr_82077 == 0x80) अणु
		sun_fdc->करोr_82077 = 0x02;
		अगर (sun_fdc->करोr_82077 == 0x80) अणु
			sun_fकरोps.fd_inb = sun_82072_fd_inb;
			sun_fकरोps.fd_outb = sun_82072_fd_outb;
			fdc_status = &sun_fdc->status_82072;
		पूर्ण
	पूर्ण

	/* Success... */
	allowed_drive_mask = 0x01;
	वापस (पूर्णांक) sun_fdc;

no_sun_fdc:
	वापस -1;
पूर्ण

अटल पूर्णांक sparc_eject(व्योम)
अणु
	set_करोr(0x00, 0xff, 0x90);
	udelay(500);
	set_करोr(0x00, 0x6f, 0x00);
	udelay(500);
	वापस 0;
पूर्ण

#घोषणा fd_eject(drive) sparc_eject()

#घोषणा EXTRA_FLOPPY_PARAMS

अटल DEFINE_SPINLOCK(dma_spin_lock);

#घोषणा claim_dma_lock() \
(अणु	अचिन्हित दीर्घ flags; \
	spin_lock_irqsave(&dma_spin_lock, flags); \
	flags; \
पूर्ण)

#घोषणा release_dma_lock(__flags) \
	spin_unlock_irqrestore(&dma_spin_lock, __flags);

#पूर्ण_अगर /* !(__ASM_SPARC_FLOPPY_H) */
