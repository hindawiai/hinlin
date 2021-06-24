<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* floppy.h: Sparc specअगरic parts of the Floppy driver.
 *
 * Copyright (C) 1996, 2007, 2008 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 *
 * Ultra/PCI support added: Sep 1997  Eddie C. Dost  (ecd@skynet.be)
 */

#अगर_अघोषित __ASM_SPARC64_FLOPPY_H
#घोषणा __ASM_SPARC64_FLOPPY_H

#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/auxपन.स>

/*
 * Define this to enable exchanging drive 0 and 1 अगर only drive 1 is
 * probed on PCI machines.
 */
#अघोषित PCI_FDC_SWAP_DRIVES


/* References:
 * 1) Netbsd Sun floppy driver.
 * 2) NCR 82077 controller manual
 * 3) Intel 82077 controller manual
 */
काष्ठा sun_flpy_controller अणु
	अस्थिर अचिन्हित अक्षर status1_82077; /* Auxiliary Status reg. 1 */
	अस्थिर अचिन्हित अक्षर status2_82077; /* Auxiliary Status reg. 2 */
	अस्थिर अचिन्हित अक्षर करोr_82077;     /* Digital Output reg. */
	अस्थिर अचिन्हित अक्षर tapectl_82077; /* Tape Control reg */
	अस्थिर अचिन्हित अक्षर status_82077;  /* Main Status Register. */
#घोषणा drs_82077              status_82077   /* Digital Rate Select reg. */
	अस्थिर अचिन्हित अक्षर data_82077;    /* Data fअगरo. */
	अस्थिर अचिन्हित अक्षर ___unused;
	अस्थिर अचिन्हित अक्षर dir_82077;     /* Digital Input reg. */
#घोषणा dcr_82077              dir_82077      /* Config Control reg. */
पूर्ण;

/* You'll only ever find one controller on an Ultra anyways. */
अटल काष्ठा sun_flpy_controller *sun_fdc = (काष्ठा sun_flpy_controller *)-1;
अचिन्हित दीर्घ fdc_status;
अटल काष्ठा platक्रमm_device *floppy_op = शून्य;

काष्ठा sun_floppy_ops अणु
	अचिन्हित अक्षर	(*fd_inb) (अचिन्हित दीर्घ port, अचिन्हित पूर्णांक reg);
	व्योम		(*fd_outb) (अचिन्हित अक्षर value, अचिन्हित दीर्घ base,
				    अचिन्हित पूर्णांक reg);
	व्योम		(*fd_enable_dma) (व्योम);
	व्योम		(*fd_disable_dma) (व्योम);
	व्योम		(*fd_set_dma_mode) (पूर्णांक);
	व्योम		(*fd_set_dma_addr) (अक्षर *);
	व्योम		(*fd_set_dma_count) (पूर्णांक);
	अचिन्हित पूर्णांक	(*get_dma_residue) (व्योम);
	पूर्णांक		(*fd_request_irq) (व्योम);
	व्योम		(*fd_मुक्त_irq) (व्योम);
	पूर्णांक		(*fd_eject) (पूर्णांक);
पूर्ण;

अटल काष्ठा sun_floppy_ops sun_fकरोps;

#घोषणा fd_inb(base, reg)         sun_fकरोps.fd_inb(base, reg)
#घोषणा fd_outb(value, base, reg) sun_fकरोps.fd_outb(value, base, reg)
#घोषणा fd_enable_dma()           sun_fकरोps.fd_enable_dma()
#घोषणा fd_disable_dma()          sun_fकरोps.fd_disable_dma()
#घोषणा fd_request_dma()          (0) /* nothing... */
#घोषणा fd_मुक्त_dma()             /* nothing... */
#घोषणा fd_clear_dma_ff()         /* nothing... */
#घोषणा fd_set_dma_mode(mode)     sun_fकरोps.fd_set_dma_mode(mode)
#घोषणा fd_set_dma_addr(addr)     sun_fकरोps.fd_set_dma_addr(addr)
#घोषणा fd_set_dma_count(count)   sun_fकरोps.fd_set_dma_count(count)
#घोषणा get_dma_residue(x)        sun_fकरोps.get_dma_residue()
#घोषणा fd_request_irq()          sun_fकरोps.fd_request_irq()
#घोषणा fd_मुक्त_irq()             sun_fकरोps.fd_मुक्त_irq()
#घोषणा fd_eject(drive)           sun_fकरोps.fd_eject(drive)

/* Super paranoid... */
#अघोषित HAVE_DISABLE_HLT

अटल पूर्णांक sun_floppy_types[2] = अणु 0, 0 पूर्ण;

/* Here is where we catch the floppy driver trying to initialize,
 * thereक्रमe this is where we call the PROM device tree probing
 * routine etc. on the Sparc.
 */
#घोषणा FLOPPY0_TYPE		sun_floppy_init()
#घोषणा FLOPPY1_TYPE		sun_floppy_types[1]

#घोषणा FDC1			((अचिन्हित दीर्घ)sun_fdc)

#घोषणा N_FDC    1
#घोषणा N_DRIVE  8

/* No 64k boundary crossing problems on the Sparc. */
#घोषणा CROSS_64KB(a,s) (0)

अटल अचिन्हित अक्षर sun_82077_fd_inb(अचिन्हित दीर्घ base, अचिन्हित पूर्णांक reg)
अणु
	udelay(5);
	चयन (reg) अणु
	शेष:
		prपूर्णांकk("floppy: Asked to read unknown port %x\n", reg);
		panic("floppy: Port bolixed.");
	हाल FD_STATUS:
		वापस sbus_पढ़ोb(&sun_fdc->status_82077) & ~STATUS_DMA;
	हाल FD_DATA:
		वापस sbus_पढ़ोb(&sun_fdc->data_82077);
	हाल FD_सूची:
		/* XXX: Is DCL on 0x80 in sun4m? */
		वापस sbus_पढ़ोb(&sun_fdc->dir_82077);
	पूर्ण
	panic("sun_82072_fd_inb: How did I get here?");
पूर्ण

अटल व्योम sun_82077_fd_outb(अचिन्हित अक्षर value, अचिन्हित दीर्घ base,
			      अचिन्हित पूर्णांक reg)
अणु
	udelay(5);
	चयन (reg) अणु
	शेष:
		prपूर्णांकk("floppy: Asked to write to unknown port %x\n", reg);
		panic("floppy: Port bolixed.");
	हाल FD_DOR:
		/* Happily, the 82077 has a real DOR रेजिस्टर. */
		sbus_ग_लिखोb(value, &sun_fdc->करोr_82077);
		अवरोध;
	हाल FD_DATA:
		sbus_ग_लिखोb(value, &sun_fdc->data_82077);
		अवरोध;
	हाल FD_DCR:
		sbus_ग_लिखोb(value, &sun_fdc->dcr_82077);
		अवरोध;
	हाल FD_DSR:
		sbus_ग_लिखोb(value, &sun_fdc->status_82077);
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
अचिन्हित अक्षर *pdma_vaddr;
अचिन्हित दीर्घ pdma_size;
अस्थिर पूर्णांक करोing_pdma = 0;

/* This is software state */
अक्षर *pdma_base = शून्य;
अचिन्हित दीर्घ pdma_areasize;

/* Common routines to all controller types on the Sparc. */
अटल व्योम sun_fd_disable_dma(व्योम)
अणु
	करोing_pdma = 0;
	pdma_base = शून्य;
पूर्ण

अटल व्योम sun_fd_set_dma_mode(पूर्णांक mode)
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

अटल व्योम sun_fd_set_dma_addr(अक्षर *buffer)
अणु
	pdma_vaddr = buffer;
पूर्ण

अटल व्योम sun_fd_set_dma_count(पूर्णांक length)
अणु
	pdma_size = length;
पूर्ण

अटल व्योम sun_fd_enable_dma(व्योम)
अणु
	pdma_base = pdma_vaddr;
	pdma_areasize = pdma_size;
पूर्ण

irqवापस_t sparc_floppy_irq(पूर्णांक irq, व्योम *dev_cookie)
अणु
	अगर (likely(करोing_pdma)) अणु
		व्योम __iomem *stat = (व्योम __iomem *) fdc_status;
		अचिन्हित अक्षर *vaddr = pdma_vaddr;
		अचिन्हित दीर्घ size = pdma_size;
		u8 val;

		जबतक (size) अणु
			val = पढ़ोb(stat);
			अगर (unlikely(!(val & 0x80))) अणु
				pdma_vaddr = vaddr;
				pdma_size = size;
				वापस IRQ_HANDLED;
			पूर्ण
			अगर (unlikely(!(val & 0x20))) अणु
				pdma_vaddr = vaddr;
				pdma_size = size;
				करोing_pdma = 0;
				जाओ मुख्य_पूर्णांकerrupt;
			पूर्ण
			अगर (val & 0x40) अणु
				/* पढ़ो */
				*vaddr++ = पढ़ोb(stat + 1);
			पूर्ण अन्यथा अणु
				अचिन्हित अक्षर data = *vaddr++;

				/* ग_लिखो */
				ग_लिखोb(data, stat + 1);
			पूर्ण
			size--;
		पूर्ण

		pdma_vaddr = vaddr;
		pdma_size = size;

		/* Send Terminal Count pulse to floppy controller. */
		val = पढ़ोb(auxio_रेजिस्टर);
		val |= AUXIO_AUX1_FTCNT;
		ग_लिखोb(val, auxio_रेजिस्टर);
		val &= ~AUXIO_AUX1_FTCNT;
		ग_लिखोb(val, auxio_रेजिस्टर);

		करोing_pdma = 0;
	पूर्ण

मुख्य_पूर्णांकerrupt:
	वापस floppy_पूर्णांकerrupt(irq, dev_cookie);
पूर्ण

अटल पूर्णांक sun_fd_request_irq(व्योम)
अणु
	अटल पूर्णांक once = 0;
	पूर्णांक error;

	अगर(!once) अणु
		once = 1;

		error = request_irq(FLOPPY_IRQ, sparc_floppy_irq,
				    0, "floppy", शून्य);

		वापस ((error == 0) ? 0 : -1);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sun_fd_मुक्त_irq(व्योम)
अणु
पूर्ण

अटल अचिन्हित पूर्णांक sun_get_dma_residue(व्योम)
अणु
	/* XXX This isn't really correct. XXX */
	वापस 0;
पूर्ण

अटल पूर्णांक sun_fd_eject(पूर्णांक drive)
अणु
	set_करोr(0x00, 0xff, 0x90);
	udelay(500);
	set_करोr(0x00, 0x6f, 0x00);
	udelay(500);
	वापस 0;
पूर्ण

#समावेश <यंत्र/ebus_dma.h>
#समावेश <यंत्र/ns87303.h>

अटल काष्ठा ebus_dma_info sun_pci_fd_ebus_dma;
अटल काष्ठा device *sun_floppy_dev;
अटल पूर्णांक sun_pci_broken_drive = -1;

काष्ठा sun_pci_dma_op अणु
	अचिन्हित पूर्णांक 	addr;
	पूर्णांक		len;
	पूर्णांक		direction;
	अक्षर		*buf;
पूर्ण;
अटल काष्ठा sun_pci_dma_op sun_pci_dma_current = अणु -1U, 0, 0, शून्यपूर्ण;
अटल काष्ठा sun_pci_dma_op sun_pci_dma_pending = अणु -1U, 0, 0, शून्यपूर्ण;

irqवापस_t floppy_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

अटल अचिन्हित अक्षर sun_pci_fd_inb(अचिन्हित दीर्घ base, अचिन्हित पूर्णांक reg)
अणु
	udelay(5);
	वापस inb(base + reg);
पूर्ण

अटल व्योम sun_pci_fd_outb(अचिन्हित अक्षर val, अचिन्हित दीर्घ base,
			    अचिन्हित पूर्णांक reg)
अणु
	udelay(5);
	outb(val, base + reg);
पूर्ण

अटल व्योम sun_pci_fd_broken_outb(अचिन्हित अक्षर val, अचिन्हित दीर्घ base,
				   अचिन्हित पूर्णांक reg)
अणु
	udelay(5);
	/*
	 * XXX: Due to SUN's broken floppy connector on AX and AXi
	 *      we need to turn on MOTOR_0 also, अगर the floppy is
	 *      jumpered to DS1 (like most PC floppies are). I hope
	 *      this करोes not hurt correct hardware like the AXmp.
	 *      (Eddie, Sep 12 1998).
	 */
	अगर (reg == FD_DOR) अणु
		अगर (((val & 0x03) == sun_pci_broken_drive) && (val & 0x20)) अणु
			val |= 0x10;
		पूर्ण
	पूर्ण
	outb(val, base + reg);
पूर्ण

#अगर_घोषित PCI_FDC_SWAP_DRIVES
अटल व्योम sun_pci_fd_lde_broken_outb(अचिन्हित अक्षर val, अचिन्हित दीर्घ base,
				       अचिन्हित पूर्णांक reg)
अणु
	udelay(5);
	/*
	 * XXX: Due to SUN's broken floppy connector on AX and AXi
	 *      we need to turn on MOTOR_0 also, अगर the floppy is
	 *      jumpered to DS1 (like most PC floppies are). I hope
	 *      this करोes not hurt correct hardware like the AXmp.
	 *      (Eddie, Sep 12 1998).
	 */
	अगर (reg == FD_DOR) अणु
		अगर (((val & 0x03) == sun_pci_broken_drive) && (val & 0x10)) अणु
			val &= ~(0x03);
			val |= 0x21;
		पूर्ण
	पूर्ण
	outb(val, base + reg);
पूर्ण
#पूर्ण_अगर /* PCI_FDC_SWAP_DRIVES */

अटल व्योम sun_pci_fd_enable_dma(व्योम)
अणु
	BUG_ON((शून्य == sun_pci_dma_pending.buf) 	||
	    (0	  == sun_pci_dma_pending.len) 	||
	    (0	  == sun_pci_dma_pending.direction));

	sun_pci_dma_current.buf = sun_pci_dma_pending.buf;
	sun_pci_dma_current.len = sun_pci_dma_pending.len;
	sun_pci_dma_current.direction = sun_pci_dma_pending.direction;

	sun_pci_dma_pending.buf  = शून्य;
	sun_pci_dma_pending.len  = 0;
	sun_pci_dma_pending.direction = 0;
	sun_pci_dma_pending.addr = -1U;

	sun_pci_dma_current.addr =
		dma_map_single(sun_floppy_dev,
			       sun_pci_dma_current.buf,
			       sun_pci_dma_current.len,
			       sun_pci_dma_current.direction);

	ebus_dma_enable(&sun_pci_fd_ebus_dma, 1);

	अगर (ebus_dma_request(&sun_pci_fd_ebus_dma,
			     sun_pci_dma_current.addr,
			     sun_pci_dma_current.len))
		BUG();
पूर्ण

अटल व्योम sun_pci_fd_disable_dma(व्योम)
अणु
	ebus_dma_enable(&sun_pci_fd_ebus_dma, 0);
	अगर (sun_pci_dma_current.addr != -1U)
		dma_unmap_single(sun_floppy_dev,
				 sun_pci_dma_current.addr,
				 sun_pci_dma_current.len,
				 sun_pci_dma_current.direction);
	sun_pci_dma_current.addr = -1U;
पूर्ण

अटल व्योम sun_pci_fd_set_dma_mode(पूर्णांक mode)
अणु
	अगर (mode == DMA_MODE_WRITE)
		sun_pci_dma_pending.direction = DMA_TO_DEVICE;
	अन्यथा
		sun_pci_dma_pending.direction = DMA_FROM_DEVICE;

	ebus_dma_prepare(&sun_pci_fd_ebus_dma, mode != DMA_MODE_WRITE);
पूर्ण

अटल व्योम sun_pci_fd_set_dma_count(पूर्णांक length)
अणु
	sun_pci_dma_pending.len = length;
पूर्ण

अटल व्योम sun_pci_fd_set_dma_addr(अक्षर *buffer)
अणु
	sun_pci_dma_pending.buf = buffer;
पूर्ण

अटल अचिन्हित पूर्णांक sun_pci_get_dma_residue(व्योम)
अणु
	वापस ebus_dma_residue(&sun_pci_fd_ebus_dma);
पूर्ण

अटल पूर्णांक sun_pci_fd_request_irq(व्योम)
अणु
	वापस ebus_dma_irq_enable(&sun_pci_fd_ebus_dma, 1);
पूर्ण

अटल व्योम sun_pci_fd_मुक्त_irq(व्योम)
अणु
	ebus_dma_irq_enable(&sun_pci_fd_ebus_dma, 0);
पूर्ण

अटल पूर्णांक sun_pci_fd_eject(पूर्णांक drive)
अणु
	वापस -EINVAL;
पूर्ण

व्योम sun_pci_fd_dma_callback(काष्ठा ebus_dma_info *p, पूर्णांक event, व्योम *cookie)
अणु
	floppy_पूर्णांकerrupt(0, शून्य);
पूर्ण

/*
 * Floppy probing, we'd like to use /dev/fd0 क्रम a single Floppy on PCI,
 * even अगर this is configured using DS1, thus looks like /dev/fd1 with
 * the cabling used in Ultras.
 */
#घोषणा DOR	(port + 2)
#घोषणा MSR	(port + 4)
#घोषणा FIFO	(port + 5)

अटल व्योम sun_pci_fd_out_byte(अचिन्हित दीर्घ port, अचिन्हित अक्षर val,
			        अचिन्हित दीर्घ reg)
अणु
	अचिन्हित अक्षर status;
	पूर्णांक समयout = 1000;

	जबतक (!((status = inb(MSR)) & 0x80) && --समयout)
		udelay(100);
	outb(val, reg);
पूर्ण

अटल अचिन्हित अक्षर sun_pci_fd_sensei(अचिन्हित दीर्घ port)
अणु
	अचिन्हित अक्षर result[2] = अणु 0x70, 0x00 पूर्ण;
	अचिन्हित अक्षर status;
	पूर्णांक i = 0;

	sun_pci_fd_out_byte(port, 0x08, FIFO);
	करो अणु
		पूर्णांक समयout = 1000;

		जबतक (!((status = inb(MSR)) & 0x80) && --समयout)
			udelay(100);

		अगर (!समयout)
			अवरोध;

		अगर ((status & 0xf0) == 0xd0)
			result[i++] = inb(FIFO);
		अन्यथा
			अवरोध;
	पूर्ण जबतक (i < 2);

	वापस result[0];
पूर्ण

अटल व्योम sun_pci_fd_reset(अचिन्हित दीर्घ port)
अणु
	अचिन्हित अक्षर mask = 0x00;
	अचिन्हित अक्षर status;
	पूर्णांक समयout = 10000;

	outb(0x80, MSR);
	करो अणु
		status = sun_pci_fd_sensei(port);
		अगर ((status & 0xc0) == 0xc0)
			mask |= 1 << (status & 0x03);
		अन्यथा
			udelay(100);
	पूर्ण जबतक ((mask != 0x0f) && --समयout);
पूर्ण

अटल पूर्णांक sun_pci_fd_test_drive(अचिन्हित दीर्घ port, पूर्णांक drive)
अणु
	अचिन्हित अक्षर status, data;
	पूर्णांक समयout = 1000;
	पूर्णांक पढ़ोy;

	sun_pci_fd_reset(port);

	data = (0x10 << drive) | 0x0c | drive;
	sun_pci_fd_out_byte(port, data, DOR);

	sun_pci_fd_out_byte(port, 0x07, FIFO);
	sun_pci_fd_out_byte(port, drive & 0x03, FIFO);

	करो अणु
		udelay(100);
		status = sun_pci_fd_sensei(port);
	पूर्ण जबतक (((status & 0xc0) == 0x80) && --समयout);

	अगर (!समयout)
		पढ़ोy = 0;
	अन्यथा
		पढ़ोy = (status & 0x10) ? 0 : 1;

	sun_pci_fd_reset(port);
	वापस पढ़ोy;
पूर्ण
#अघोषित FIFO
#अघोषित MSR
#अघोषित DOR

अटल पूर्णांक __init ebus_fdthree_p(काष्ठा device_node *dp)
अणु
	अगर (of_node_name_eq(dp, "fdthree"))
		वापस 1;
	अगर (of_node_name_eq(dp, "floppy")) अणु
		स्थिर अक्षर *compat;

		compat = of_get_property(dp, "compatible", शून्य);
		अगर (compat && !म_भेद(compat, "fdthree"))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ __init sun_floppy_init(व्योम)
अणु
	अटल पूर्णांक initialized = 0;
	काष्ठा device_node *dp;
	काष्ठा platक्रमm_device *op;
	स्थिर अक्षर *prop;
	अक्षर state[128];

	अगर (initialized)
		वापस sun_floppy_types[0];
	initialized = 1;

	op = शून्य;

	क्रम_each_node_by_name(dp, "SUNW,fdtwo") अणु
		अगर (!of_node_name_eq(dp->parent, "sbus"))
			जारी;
		op = of_find_device_by_node(dp);
		अगर (op)
			अवरोध;
	पूर्ण
	अगर (op) अणु
		floppy_op = op;
		FLOPPY_IRQ = op->archdata.irqs[0];
	पूर्ण अन्यथा अणु
		काष्ठा device_node *ebus_dp;
		व्योम __iomem *auxio_reg;
		स्थिर अक्षर *state_prop;
		अचिन्हित दीर्घ config;

		dp = शून्य;
		क्रम_each_node_by_name(ebus_dp, "ebus") अणु
			क्रम (dp = ebus_dp->child; dp; dp = dp->sibling) अणु
				अगर (ebus_fdthree_p(dp))
					जाओ found_fdthree;
			पूर्ण
		पूर्ण
	found_fdthree:
		अगर (!dp)
			वापस 0;

		op = of_find_device_by_node(dp);
		अगर (!op)
			वापस 0;

		state_prop = of_get_property(op->dev.of_node, "status", शून्य);
		अगर (state_prop && !म_भेदन(state_prop, "disabled", 8))
			वापस 0;

		FLOPPY_IRQ = op->archdata.irqs[0];

		/* Make sure the high density bit is set, some प्रणालीs
		 * (most notably Ultra5/Ultra10) come up with it clear.
		 */
		auxio_reg = (व्योम __iomem *) op->resource[2].start;
		ग_लिखोl(पढ़ोl(auxio_reg)|0x2, auxio_reg);

		sun_floppy_dev = &op->dev;

		spin_lock_init(&sun_pci_fd_ebus_dma.lock);

		/* XXX ioremap */
		sun_pci_fd_ebus_dma.regs = (व्योम __iomem *)
			op->resource[1].start;
		अगर (!sun_pci_fd_ebus_dma.regs)
			वापस 0;

		sun_pci_fd_ebus_dma.flags = (EBUS_DMA_FLAG_USE_EBDMA_HANDLER |
					     EBUS_DMA_FLAG_TCI_DISABLE);
		sun_pci_fd_ebus_dma.callback = sun_pci_fd_dma_callback;
		sun_pci_fd_ebus_dma.client_cookie = शून्य;
		sun_pci_fd_ebus_dma.irq = FLOPPY_IRQ;
		म_नकल(sun_pci_fd_ebus_dma.name, "floppy");
		अगर (ebus_dma_रेजिस्टर(&sun_pci_fd_ebus_dma))
			वापस 0;

		/* XXX ioremap */
		sun_fdc = (काष्ठा sun_flpy_controller *) op->resource[0].start;

		sun_fकरोps.fd_inb = sun_pci_fd_inb;
		sun_fकरोps.fd_outb = sun_pci_fd_outb;

		can_use_भव_dma = use_भव_dma = 0;
		sun_fकरोps.fd_enable_dma = sun_pci_fd_enable_dma;
		sun_fकरोps.fd_disable_dma = sun_pci_fd_disable_dma;
		sun_fकरोps.fd_set_dma_mode = sun_pci_fd_set_dma_mode;
		sun_fकरोps.fd_set_dma_addr = sun_pci_fd_set_dma_addr;
		sun_fकरोps.fd_set_dma_count = sun_pci_fd_set_dma_count;
		sun_fकरोps.get_dma_residue = sun_pci_get_dma_residue;

		sun_fकरोps.fd_request_irq = sun_pci_fd_request_irq;
		sun_fकरोps.fd_मुक्त_irq = sun_pci_fd_मुक्त_irq;

		sun_fकरोps.fd_eject = sun_pci_fd_eject;

		fdc_status = (अचिन्हित दीर्घ) &sun_fdc->status_82077;

		/*
		 * XXX: Find out on which machines this is really needed.
		 */
		अगर (1) अणु
			sun_pci_broken_drive = 1;
			sun_fकरोps.fd_outb = sun_pci_fd_broken_outb;
		पूर्ण

		allowed_drive_mask = 0;
		अगर (sun_pci_fd_test_drive((अचिन्हित दीर्घ)sun_fdc, 0))
			sun_floppy_types[0] = 4;
		अगर (sun_pci_fd_test_drive((अचिन्हित दीर्घ)sun_fdc, 1))
			sun_floppy_types[1] = 4;

		/*
		 * Find NS87303 SuperIO config रेजिस्टरs (through ecpp).
		 */
		config = 0;
		क्रम (dp = ebus_dp->child; dp; dp = dp->sibling) अणु
			अगर (of_node_name_eq(dp, "ecpp")) अणु
				काष्ठा platक्रमm_device *ecpp_op;

				ecpp_op = of_find_device_by_node(dp);
				अगर (ecpp_op)
					config = ecpp_op->resource[1].start;
				जाओ config_करोne;
			पूर्ण
		पूर्ण
	config_करोne:

		/*
		 * Sanity check, is this really the NS87303?
		 */
		चयन (config & 0x3ff) अणु
		हाल 0x02e:
		हाल 0x15c:
		हाल 0x26e:
		हाल 0x398:
			अवरोध;
		शेष:
			config = 0;
		पूर्ण

		अगर (!config)
			वापस sun_floppy_types[0];

		/* Enable PC-AT mode. */
		ns87303_modअगरy(config, ASC, 0, 0xc0);

#अगर_घोषित PCI_FDC_SWAP_DRIVES
		/*
		 * If only Floppy 1 is present, swap drives.
		 */
		अगर (!sun_floppy_types[0] && sun_floppy_types[1]) अणु
			/*
			 * Set the drive exchange bit in FCR on NS87303,
			 * make sure other bits are sane beक्रमe करोing so.
			 */
			ns87303_modअगरy(config, FER, FER_EDM, 0);
			ns87303_modअगरy(config, ASC, ASC_DRV2_SEL, 0);
			ns87303_modअगरy(config, FCR, 0, FCR_LDE);

			config = sun_floppy_types[0];
			sun_floppy_types[0] = sun_floppy_types[1];
			sun_floppy_types[1] = config;

			अगर (sun_pci_broken_drive != -1) अणु
				sun_pci_broken_drive = 1 - sun_pci_broken_drive;
				sun_fकरोps.fd_outb = sun_pci_fd_lde_broken_outb;
			पूर्ण
		पूर्ण
#पूर्ण_अगर /* PCI_FDC_SWAP_DRIVES */

		वापस sun_floppy_types[0];
	पूर्ण
	prop = of_get_property(op->dev.of_node, "status", शून्य);
	अगर (prop && !म_भेदन(state, "disabled", 8))
		वापस 0;

	/*
	 * We cannot करो of_ioremap here: it करोes request_region,
	 * which the generic floppy driver tries to करो once again.
	 * But we must use the sdev resource values as they have
	 * had parent ranges applied.
	 */
	sun_fdc = (काष्ठा sun_flpy_controller *)
		(op->resource[0].start +
		 ((op->resource[0].flags & 0x1ffUL) << 32UL));

	/* Last minute sanity check... */
	अगर (sbus_पढ़ोb(&sun_fdc->status1_82077) == 0xff) अणु
		sun_fdc = (काष्ठा sun_flpy_controller *)-1;
		वापस 0;
	पूर्ण

        sun_fकरोps.fd_inb = sun_82077_fd_inb;
        sun_fकरोps.fd_outb = sun_82077_fd_outb;

	can_use_भव_dma = use_भव_dma = 1;
	sun_fकरोps.fd_enable_dma = sun_fd_enable_dma;
	sun_fकरोps.fd_disable_dma = sun_fd_disable_dma;
	sun_fकरोps.fd_set_dma_mode = sun_fd_set_dma_mode;
	sun_fकरोps.fd_set_dma_addr = sun_fd_set_dma_addr;
	sun_fकरोps.fd_set_dma_count = sun_fd_set_dma_count;
	sun_fकरोps.get_dma_residue = sun_get_dma_residue;

	sun_fकरोps.fd_request_irq = sun_fd_request_irq;
	sun_fकरोps.fd_मुक्त_irq = sun_fd_मुक्त_irq;

	sun_fकरोps.fd_eject = sun_fd_eject;

        fdc_status = (अचिन्हित दीर्घ) &sun_fdc->status_82077;

	/* Success... */
	allowed_drive_mask = 0x01;
	sun_floppy_types[0] = 4;
	sun_floppy_types[1] = 0;

	वापस sun_floppy_types[0];
पूर्ण

#घोषणा EXTRA_FLOPPY_PARAMS

अटल DEFINE_SPINLOCK(dma_spin_lock);

#घोषणा claim_dma_lock() \
(अणु	अचिन्हित दीर्घ flags; \
	spin_lock_irqsave(&dma_spin_lock, flags); \
	flags; \
पूर्ण)

#घोषणा release_dma_lock(__flags) \
	spin_unlock_irqrestore(&dma_spin_lock, __flags);

#पूर्ण_अगर /* !(__ASM_SPARC64_FLOPPY_H) */
