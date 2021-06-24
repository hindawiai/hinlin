<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Low-level parallel-port routines क्रम 8255-based PC-style hardware.
 *
 * Authors: Phil Blundell <philb@gnu.org>
 *          Tim Waugh <tim@cyberelk.demon.co.uk>
 *	    Jose Renau <renau@acm.org>
 *          David Campbell
 *          Andrea Arcangeli
 *
 * based on work by Grant Guenther <grant@torque.net> and Phil Blundell.
 *
 * Cleaned up include files - Russell King <linux@arm.uk.linux.org>
 * DMA support - Bert De Jonghe <bert@sophis.be>
 * Many ECP bugs fixed.  Fred Barnes & Jamie Lokier, 1999
 * More PCI support now conditional on CONFIG_PCI, 03/2001, Paul G.
 * Various hacks, Fred Barnes, 04/2001
 * Updated probing logic - Adam Belay <ambx1@neo.rr.com>
 */

/* This driver should work with any hardware that is broadly compatible
 * with that in the IBM PC.  This applies to the majority of पूर्णांकegrated
 * I/O chipsets that are commonly available.  The expected रेजिस्टर
 * layout is:
 *
 *	base+0		data
 *	base+1		status
 *	base+2		control
 *
 * In addition, there are some optional रेजिस्टरs:
 *
 *	base+3		EPP address
 *	base+4		EPP data
 *	base+0x400	ECP config A
 *	base+0x401	ECP config B
 *	base+0x402	ECP control
 *
 * All रेजिस्टरs are 8 bits wide and पढ़ो/ग_लिखो.  If your hardware dअगरfers
 * only in रेजिस्टर addresses (eg because your रेजिस्टरs are on 32-bit
 * word boundaries) then you can alter the स्थिरants in parport_pc.h to
 * accommodate this.
 *
 * Note that the ECP रेजिस्टरs may not start at offset 0x400 क्रम PCI cards,
 * but rather will start at port->base_hi.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>
#समावेश <linux/pnp.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/dma.h>

#समावेश <linux/parport.h>
#समावेश <linux/parport_pc.h>
#समावेश <linux/via.h>
#समावेश <यंत्र/parport.h>

#घोषणा PARPORT_PC_MAX_PORTS PARPORT_MAX

#अगर_घोषित CONFIG_ISA_DMA_API
#घोषणा HAS_DMA
#पूर्ण_अगर

/* ECR modes */
#घोषणा ECR_SPP 00
#घोषणा ECR_PS2 01
#घोषणा ECR_PPF 02
#घोषणा ECR_ECP 03
#घोषणा ECR_EPP 04
#घोषणा ECR_VND 05
#घोषणा ECR_TST 06
#घोषणा ECR_CNF 07
#घोषणा ECR_MODE_MASK 0xe0
#घोषणा ECR_WRITE(p, v) frob_econtrol((p), 0xff, (v))

#अघोषित DEBUG

#घोषणा NR_SUPERIOS 3
अटल काष्ठा superio_काष्ठा अणु	/* For Super-IO chips स्वतःdetection */
	पूर्णांक io;
	पूर्णांक irq;
	पूर्णांक dma;
पूर्ण superios[NR_SUPERIOS] = अणु अणु0,पूर्ण,पूर्ण;

अटल पूर्णांक user_specअगरied;
#अगर defined(CONFIG_PARPORT_PC_SUPERIO) || \
       (defined(CONFIG_PARPORT_1284) && defined(CONFIG_PARPORT_PC_FIFO))
अटल पूर्णांक verbose_probing;
#पूर्ण_अगर
अटल पूर्णांक pci_रेजिस्टरed_parport;
अटल पूर्णांक pnp_रेजिस्टरed_parport;

/* frob_control, but क्रम ECR */
अटल व्योम frob_econtrol(काष्ठा parport *pb, अचिन्हित अक्षर m,
			   अचिन्हित अक्षर v)
अणु
	अचिन्हित अक्षर ectr = 0;

	अगर (m != 0xff)
		ectr = inb(ECONTROL(pb));

	pr_debug("frob_econtrol(%02x,%02x): %02x -> %02x\n",
		 m, v, ectr, (ectr & ~m) ^ v);

	outb((ectr & ~m) ^ v, ECONTROL(pb));
पूर्ण

अटल अंतरभूत व्योम frob_set_mode(काष्ठा parport *p, पूर्णांक mode)
अणु
	frob_econtrol(p, ECR_MODE_MASK, mode << 5);
पूर्ण

#अगर_घोषित CONFIG_PARPORT_PC_FIFO
/* Safely change the mode bits in the ECR
   Returns:
	    0    : Success
	   -EBUSY: Could not drain FIFO in some finite amount of समय,
		   mode not changed!
 */
अटल पूर्णांक change_mode(काष्ठा parport *p, पूर्णांक m)
अणु
	स्थिर काष्ठा parport_pc_निजी *priv = p->physport->निजी_data;
	अचिन्हित अक्षर oecr;
	पूर्णांक mode;

	pr_debug("parport change_mode ECP-ISA to mode 0x%02x\n", m);

	अगर (!priv->ecr) अणु
		prपूर्णांकk(KERN_DEBUG "change_mode: but there's no ECR!\n");
		वापस 0;
	पूर्ण

	/* Bits <7:5> contain the mode. */
	oecr = inb(ECONTROL(p));
	mode = (oecr >> 5) & 0x7;
	अगर (mode == m)
		वापस 0;

	अगर (mode >= 2 && !(priv->ctr & 0x20)) अणु
		/* This mode resets the FIFO, so we may
		 * have to रुको क्रम it to drain first. */
		अचिन्हित दीर्घ expire = jअगरfies + p->physport->cad->समयout;
		पूर्णांक counter;
		चयन (mode) अणु
		हाल ECR_PPF: /* Parallel Port FIFO mode */
		हाल ECR_ECP: /* ECP Parallel Port mode */
			/* Busy रुको क्रम 200us */
			क्रम (counter = 0; counter < 40; counter++) अणु
				अगर (inb(ECONTROL(p)) & 0x01)
					अवरोध;
				अगर (संकेत_pending(current))
					अवरोध;
				udelay(5);
			पूर्ण

			/* Poll slowly. */
			जबतक (!(inb(ECONTROL(p)) & 0x01)) अणु
				अगर (समय_after_eq(jअगरfies, expire))
					/* The FIFO is stuck. */
					वापस -EBUSY;
				schedule_समयout_पूर्णांकerruptible(
							msecs_to_jअगरfies(10));
				अगर (संकेत_pending(current))
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (mode >= 2 && m >= 2) अणु
		/* We have to go through mode 001 */
		oecr &= ~(7 << 5);
		oecr |= ECR_PS2 << 5;
		ECR_WRITE(p, oecr);
	पूर्ण

	/* Set the mode. */
	oecr &= ~(7 << 5);
	oecr |= m << 5;
	ECR_WRITE(p, oecr);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* FIFO support */

/*
 * Clear TIMEOUT BIT in EPP MODE
 *
 * This is also used in SPP detection.
 */
अटल पूर्णांक clear_epp_समयout(काष्ठा parport *pb)
अणु
	अचिन्हित अक्षर r;

	अगर (!(parport_pc_पढ़ो_status(pb) & 0x01))
		वापस 1;

	/* To clear समयout some chips require द्विगुन पढ़ो */
	parport_pc_पढ़ो_status(pb);
	r = parport_pc_पढ़ो_status(pb);
	outb(r | 0x01, STATUS(pb)); /* Some reset by writing 1 */
	outb(r & 0xfe, STATUS(pb)); /* Others by writing 0 */
	r = parport_pc_पढ़ो_status(pb);

	वापस !(r & 0x01);
पूर्ण

/*
 * Access functions.
 *
 * Most of these aren't अटल because they may be used by the
 * parport_xxx_yyy macros.  बाह्य __अंतरभूत__ versions of several
 * of these are in parport_pc.h.
 */

अटल व्योम parport_pc_init_state(काष्ठा pardevice *dev,
						काष्ठा parport_state *s)
अणु
	s->u.pc.ctr = 0xc;
	अगर (dev->irq_func &&
	    dev->port->irq != PARPORT_IRQ_NONE)
		/* Set ackIntEn */
		s->u.pc.ctr |= 0x10;

	s->u.pc.ecr = 0x34; /* NetMos chip can cause problems 0x24;
			     * D.Gruszka VScom */
पूर्ण

अटल व्योम parport_pc_save_state(काष्ठा parport *p, काष्ठा parport_state *s)
अणु
	स्थिर काष्ठा parport_pc_निजी *priv = p->physport->निजी_data;
	s->u.pc.ctr = priv->ctr;
	अगर (priv->ecr)
		s->u.pc.ecr = inb(ECONTROL(p));
पूर्ण

अटल व्योम parport_pc_restore_state(काष्ठा parport *p,
						काष्ठा parport_state *s)
अणु
	काष्ठा parport_pc_निजी *priv = p->physport->निजी_data;
	रेजिस्टर अचिन्हित अक्षर c = s->u.pc.ctr & priv->ctr_writable;
	outb(c, CONTROL(p));
	priv->ctr = c;
	अगर (priv->ecr)
		ECR_WRITE(p, s->u.pc.ecr);
पूर्ण

#अगर_घोषित CONFIG_PARPORT_1284
अटल माप_प्रकार parport_pc_epp_पढ़ो_data(काष्ठा parport *port, व्योम *buf,
				       माप_प्रकार length, पूर्णांक flags)
अणु
	माप_प्रकार got = 0;

	अगर (flags & PARPORT_W91284PIC) अणु
		अचिन्हित अक्षर status;
		माप_प्रकार left = length;

		/* use knowledge about data lines..:
		 *  nFault is 0 अगर there is at least 1 byte in the Warp's FIFO
		 *  pError is 1 अगर there are 16 bytes in the Warp's FIFO
		 */
		status = inb(STATUS(port));

		जबतक (!(status & 0x08) && got < length) अणु
			अगर (left >= 16 && (status & 0x20) && !(status & 0x08)) अणु
				/* can grab 16 bytes from warp fअगरo */
				अगर (!((दीर्घ)buf & 0x03))
					insl(EPPDATA(port), buf, 4);
				अन्यथा
					insb(EPPDATA(port), buf, 16);
				buf += 16;
				got += 16;
				left -= 16;
			पूर्ण अन्यथा अणु
				/* grab single byte from the warp fअगरo */
				*((अक्षर *)buf) = inb(EPPDATA(port));
				buf++;
				got++;
				left--;
			पूर्ण
			status = inb(STATUS(port));
			अगर (status & 0x01) अणु
				/* EPP समयout should never occur... */
				prपूर्णांकk(KERN_DEBUG "%s: EPP timeout occurred while talking to w91284pic (should not have done)\n",
				       port->name);
				clear_epp_समयout(port);
			पूर्ण
		पूर्ण
		वापस got;
	पूर्ण
	अगर ((flags & PARPORT_EPP_FAST) && (length > 1)) अणु
		अगर (!(((दीर्घ)buf | length) & 0x03))
			insl(EPPDATA(port), buf, (length >> 2));
		अन्यथा
			insb(EPPDATA(port), buf, length);
		अगर (inb(STATUS(port)) & 0x01) अणु
			clear_epp_समयout(port);
			वापस -EIO;
		पूर्ण
		वापस length;
	पूर्ण
	क्रम (; got < length; got++) अणु
		*((अक्षर *)buf) = inb(EPPDATA(port));
		buf++;
		अगर (inb(STATUS(port)) & 0x01) अणु
			/* EPP समयout */
			clear_epp_समयout(port);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस got;
पूर्ण

अटल माप_प्रकार parport_pc_epp_ग_लिखो_data(काष्ठा parport *port, स्थिर व्योम *buf,
					माप_प्रकार length, पूर्णांक flags)
अणु
	माप_प्रकार written = 0;

	अगर ((flags & PARPORT_EPP_FAST) && (length > 1)) अणु
		अगर (!(((दीर्घ)buf | length) & 0x03))
			outsl(EPPDATA(port), buf, (length >> 2));
		अन्यथा
			outsb(EPPDATA(port), buf, length);
		अगर (inb(STATUS(port)) & 0x01) अणु
			clear_epp_समयout(port);
			वापस -EIO;
		पूर्ण
		वापस length;
	पूर्ण
	क्रम (; written < length; written++) अणु
		outb(*((अक्षर *)buf), EPPDATA(port));
		buf++;
		अगर (inb(STATUS(port)) & 0x01) अणु
			clear_epp_समयout(port);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस written;
पूर्ण

अटल माप_प्रकार parport_pc_epp_पढ़ो_addr(काष्ठा parport *port, व्योम *buf,
					माप_प्रकार length, पूर्णांक flags)
अणु
	माप_प्रकार got = 0;

	अगर ((flags & PARPORT_EPP_FAST) && (length > 1)) अणु
		insb(EPPADDR(port), buf, length);
		अगर (inb(STATUS(port)) & 0x01) अणु
			clear_epp_समयout(port);
			वापस -EIO;
		पूर्ण
		वापस length;
	पूर्ण
	क्रम (; got < length; got++) अणु
		*((अक्षर *)buf) = inb(EPPADDR(port));
		buf++;
		अगर (inb(STATUS(port)) & 0x01) अणु
			clear_epp_समयout(port);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस got;
पूर्ण

अटल माप_प्रकार parport_pc_epp_ग_लिखो_addr(काष्ठा parport *port,
					 स्थिर व्योम *buf, माप_प्रकार length,
					 पूर्णांक flags)
अणु
	माप_प्रकार written = 0;

	अगर ((flags & PARPORT_EPP_FAST) && (length > 1)) अणु
		outsb(EPPADDR(port), buf, length);
		अगर (inb(STATUS(port)) & 0x01) अणु
			clear_epp_समयout(port);
			वापस -EIO;
		पूर्ण
		वापस length;
	पूर्ण
	क्रम (; written < length; written++) अणु
		outb(*((अक्षर *)buf), EPPADDR(port));
		buf++;
		अगर (inb(STATUS(port)) & 0x01) अणु
			clear_epp_समयout(port);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस written;
पूर्ण

अटल माप_प्रकार parport_pc_ecpepp_पढ़ो_data(काष्ठा parport *port, व्योम *buf,
					  माप_प्रकार length, पूर्णांक flags)
अणु
	माप_प्रकार got;

	frob_set_mode(port, ECR_EPP);
	parport_pc_data_reverse(port);
	parport_pc_ग_लिखो_control(port, 0x4);
	got = parport_pc_epp_पढ़ो_data(port, buf, length, flags);
	frob_set_mode(port, ECR_PS2);

	वापस got;
पूर्ण

अटल माप_प्रकार parport_pc_ecpepp_ग_लिखो_data(काष्ठा parport *port,
					   स्थिर व्योम *buf, माप_प्रकार length,
					   पूर्णांक flags)
अणु
	माप_प्रकार written;

	frob_set_mode(port, ECR_EPP);
	parport_pc_ग_लिखो_control(port, 0x4);
	parport_pc_data_क्रमward(port);
	written = parport_pc_epp_ग_लिखो_data(port, buf, length, flags);
	frob_set_mode(port, ECR_PS2);

	वापस written;
पूर्ण

अटल माप_प्रकार parport_pc_ecpepp_पढ़ो_addr(काष्ठा parport *port, व्योम *buf,
					  माप_प्रकार length, पूर्णांक flags)
अणु
	माप_प्रकार got;

	frob_set_mode(port, ECR_EPP);
	parport_pc_data_reverse(port);
	parport_pc_ग_लिखो_control(port, 0x4);
	got = parport_pc_epp_पढ़ो_addr(port, buf, length, flags);
	frob_set_mode(port, ECR_PS2);

	वापस got;
पूर्ण

अटल माप_प्रकार parport_pc_ecpepp_ग_लिखो_addr(काष्ठा parport *port,
					    स्थिर व्योम *buf, माप_प्रकार length,
					    पूर्णांक flags)
अणु
	माप_प्रकार written;

	frob_set_mode(port, ECR_EPP);
	parport_pc_ग_लिखो_control(port, 0x4);
	parport_pc_data_क्रमward(port);
	written = parport_pc_epp_ग_लिखो_addr(port, buf, length, flags);
	frob_set_mode(port, ECR_PS2);

	वापस written;
पूर्ण
#पूर्ण_अगर /* IEEE 1284 support */

#अगर_घोषित CONFIG_PARPORT_PC_FIFO
अटल माप_प्रकार parport_pc_fअगरo_ग_लिखो_block_pio(काष्ठा parport *port,
					       स्थिर व्योम *buf, माप_प्रकार length)
अणु
	पूर्णांक ret = 0;
	स्थिर अचिन्हित अक्षर *bufp = buf;
	माप_प्रकार left = length;
	अचिन्हित दीर्घ expire = jअगरfies + port->physport->cad->समयout;
	स्थिर पूर्णांक fअगरo = FIFO(port);
	पूर्णांक poll_क्रम = 8; /* 80 usecs */
	स्थिर काष्ठा parport_pc_निजी *priv = port->physport->निजी_data;
	स्थिर पूर्णांक fअगरo_depth = priv->fअगरo_depth;

	port = port->physport;

	/* We करोn't want to be पूर्णांकerrupted every अक्षरacter. */
	parport_pc_disable_irq(port);
	/* set nErrIntrEn and serviceIntr */
	frob_econtrol(port, (1<<4) | (1<<2), (1<<4) | (1<<2));

	/* Forward mode. */
	parport_pc_data_क्रमward(port); /* Must be in PS2 mode */

	जबतक (left) अणु
		अचिन्हित अक्षर byte;
		अचिन्हित अक्षर ecrval = inb(ECONTROL(port));
		पूर्णांक i = 0;

		अगर (need_resched() && समय_beक्रमe(jअगरfies, expire))
			/* Can't yield the port. */
			schedule();

		/* Anyone अन्यथा रुकोing क्रम the port? */
		अगर (port->रुकोhead) अणु
			prपूर्णांकk(KERN_DEBUG "Somebody wants the port\n");
			अवरोध;
		पूर्ण

		अगर (ecrval & 0x02) अणु
			/* FIFO is full. Wait क्रम पूर्णांकerrupt. */

			/* Clear serviceIntr */
			ECR_WRITE(port, ecrval & ~(1<<2));
false_alarm:
			ret = parport_रुको_event(port, HZ);
			अगर (ret < 0)
				अवरोध;
			ret = 0;
			अगर (!समय_beक्रमe(jअगरfies, expire)) अणु
				/* Timed out. */
				prपूर्णांकk(KERN_DEBUG "FIFO write timed out\n");
				अवरोध;
			पूर्ण
			ecrval = inb(ECONTROL(port));
			अगर (!(ecrval & (1<<2))) अणु
				अगर (need_resched() &&
				    समय_beक्रमe(jअगरfies, expire))
					schedule();

				जाओ false_alarm;
			पूर्ण

			जारी;
		पूर्ण

		/* Can't fail now. */
		expire = jअगरfies + port->cad->समयout;

poll:
		अगर (संकेत_pending(current))
			अवरोध;

		अगर (ecrval & 0x01) अणु
			/* FIFO is empty. Blast it full. */
			स्थिर पूर्णांक n = left < fअगरo_depth ? left : fअगरo_depth;
			outsb(fअगरo, bufp, n);
			bufp += n;
			left -= n;

			/* Adjust the poll समय. */
			अगर (i < (poll_क्रम - 2))
				poll_क्रम--;
			जारी;
		पूर्ण अन्यथा अगर (i++ < poll_क्रम) अणु
			udelay(10);
			ecrval = inb(ECONTROL(port));
			जाओ poll;
		पूर्ण

		/* Half-full(call me an optimist) */
		byte = *bufp++;
		outb(byte, fअगरo);
		left--;
	पूर्ण
	dump_parport_state("leave fifo_write_block_pio", port);
	वापस length - left;
पूर्ण

#अगर_घोषित HAS_DMA
अटल माप_प्रकार parport_pc_fअगरo_ग_लिखो_block_dma(काष्ठा parport *port,
					       स्थिर व्योम *buf, माप_प्रकार length)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ dmaflag;
	माप_प्रकार left = length;
	स्थिर काष्ठा parport_pc_निजी *priv = port->physport->निजी_data;
	काष्ठा device *dev = port->physport->dev;
	dma_addr_t dma_addr, dma_handle;
	माप_प्रकार maxlen = 0x10000; /* max 64k per DMA transfer */
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ) buf;
	अचिन्हित दीर्घ end = (अचिन्हित दीर्घ) buf + length - 1;

	dump_parport_state("enter fifo_write_block_dma", port);
	अगर (end < MAX_DMA_ADDRESS) अणु
		/* If it would cross a 64k boundary, cap it at the end. */
		अगर ((start ^ end) & ~0xffffUL)
			maxlen = 0x10000 - (start & 0xffff);

		dma_addr = dma_handle = dma_map_single(dev, (व्योम *)buf, length,
						       DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		/* above 16 MB we use a bounce buffer as ISA-DMA
		   is not possible */
		maxlen   = PAGE_SIZE;          /* माप(priv->dma_buf) */
		dma_addr = priv->dma_handle;
		dma_handle = 0;
	पूर्ण

	port = port->physport;

	/* We करोn't want to be पूर्णांकerrupted every अक्षरacter. */
	parport_pc_disable_irq(port);
	/* set nErrIntrEn and serviceIntr */
	frob_econtrol(port, (1<<4) | (1<<2), (1<<4) | (1<<2));

	/* Forward mode. */
	parport_pc_data_क्रमward(port); /* Must be in PS2 mode */

	जबतक (left) अणु
		अचिन्हित दीर्घ expire = jअगरfies + port->physport->cad->समयout;

		माप_प्रकार count = left;

		अगर (count > maxlen)
			count = maxlen;

		अगर (!dma_handle)   /* bounce buffer ! */
			स_नकल(priv->dma_buf, buf, count);

		dmaflag = claim_dma_lock();
		disable_dma(port->dma);
		clear_dma_ff(port->dma);
		set_dma_mode(port->dma, DMA_MODE_WRITE);
		set_dma_addr(port->dma, dma_addr);
		set_dma_count(port->dma, count);

		/* Set DMA mode */
		frob_econtrol(port, 1<<3, 1<<3);

		/* Clear serviceIntr */
		frob_econtrol(port, 1<<2, 0);

		enable_dma(port->dma);
		release_dma_lock(dmaflag);

		/* assume DMA will be successful */
		left -= count;
		buf  += count;
		अगर (dma_handle)
			dma_addr += count;

		/* Wait क्रम पूर्णांकerrupt. */
false_alarm:
		ret = parport_रुको_event(port, HZ);
		अगर (ret < 0)
			अवरोध;
		ret = 0;
		अगर (!समय_beक्रमe(jअगरfies, expire)) अणु
			/* Timed out. */
			prपूर्णांकk(KERN_DEBUG "DMA write timed out\n");
			अवरोध;
		पूर्ण
		/* Is serviceIntr set? */
		अगर (!(inb(ECONTROL(port)) & (1<<2))) अणु
			cond_resched();

			जाओ false_alarm;
		पूर्ण

		dmaflag = claim_dma_lock();
		disable_dma(port->dma);
		clear_dma_ff(port->dma);
		count = get_dma_residue(port->dma);
		release_dma_lock(dmaflag);

		cond_resched(); /* Can't yield the port. */

		/* Anyone अन्यथा रुकोing क्रम the port? */
		अगर (port->रुकोhead) अणु
			prपूर्णांकk(KERN_DEBUG "Somebody wants the port\n");
			अवरोध;
		पूर्ण

		/* update क्रम possible DMA residue ! */
		buf  -= count;
		left += count;
		अगर (dma_handle)
			dma_addr -= count;
	पूर्ण

	/* Maybe got here through अवरोध, so adjust क्रम DMA residue! */
	dmaflag = claim_dma_lock();
	disable_dma(port->dma);
	clear_dma_ff(port->dma);
	left += get_dma_residue(port->dma);
	release_dma_lock(dmaflag);

	/* Turn off DMA mode */
	frob_econtrol(port, 1<<3, 0);

	अगर (dma_handle)
		dma_unmap_single(dev, dma_handle, length, DMA_TO_DEVICE);

	dump_parport_state("leave fifo_write_block_dma", port);
	वापस length - left;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत माप_प्रकार parport_pc_fअगरo_ग_लिखो_block(काष्ठा parport *port,
					       स्थिर व्योम *buf, माप_प्रकार length)
अणु
#अगर_घोषित HAS_DMA
	अगर (port->dma != PARPORT_DMA_NONE)
		वापस parport_pc_fअगरo_ग_लिखो_block_dma(port, buf, length);
#पूर्ण_अगर
	वापस parport_pc_fअगरo_ग_लिखो_block_pio(port, buf, length);
पूर्ण

/* Parallel Port FIFO mode (ECP chipsets) */
अटल माप_प्रकार parport_pc_compat_ग_लिखो_block_pio(काष्ठा parport *port,
						 स्थिर व्योम *buf, माप_प्रकार length,
						 पूर्णांक flags)
अणु
	माप_प्रकार written;
	पूर्णांक r;
	अचिन्हित दीर्घ expire;
	स्थिर काष्ठा parport_pc_निजी *priv = port->physport->निजी_data;

	/* Special हाल: a समयout of zero means we cannot call schedule().
	 * Also अगर O_NONBLOCK is set then use the शेष implementation. */
	अगर (port->physport->cad->समयout <= PARPORT_INACTIVITY_O_NONBLOCK)
		वापस parport_ieee1284_ग_लिखो_compat(port, buf,
						      length, flags);

	/* Set up parallel port FIFO mode.*/
	parport_pc_data_क्रमward(port); /* Must be in PS2 mode */
	parport_pc_frob_control(port, PARPORT_CONTROL_STROBE, 0);
	r = change_mode(port, ECR_PPF); /* Parallel port FIFO */
	अगर (r)
		prपूर्णांकk(KERN_DEBUG "%s: Warning change_mode ECR_PPF failed\n",
		       port->name);

	port->physport->ieee1284.phase = IEEE1284_PH_FWD_DATA;

	/* Write the data to the FIFO. */
	written = parport_pc_fअगरo_ग_लिखो_block(port, buf, length);

	/* Finish up. */
	/* For some hardware we करोn't want to touch the mode until
	 * the FIFO is empty, so allow 4 seconds क्रम each position
	 * in the fअगरo.
	 */
	expire = jअगरfies + (priv->fअगरo_depth * HZ * 4);
	करो अणु
		/* Wait क्रम the FIFO to empty */
		r = change_mode(port, ECR_PS2);
		अगर (r != -EBUSY)
			अवरोध;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, expire));
	अगर (r == -EBUSY) अणु

		prपूर्णांकk(KERN_DEBUG "%s: FIFO is stuck\n", port->name);

		/* Prevent further data transfer. */
		frob_set_mode(port, ECR_TST);

		/* Adjust क्रम the contents of the FIFO. */
		क्रम (written -= priv->fअगरo_depth; ; written++) अणु
			अगर (inb(ECONTROL(port)) & 0x2) अणु
				/* Full up. */
				अवरोध;
			पूर्ण
			outb(0, FIFO(port));
		पूर्ण

		/* Reset the FIFO and वापस to PS2 mode. */
		frob_set_mode(port, ECR_PS2);
	पूर्ण

	r = parport_रुको_peripheral(port,
				     PARPORT_STATUS_BUSY,
				     PARPORT_STATUS_BUSY);
	अगर (r)
		prपूर्णांकk(KERN_DEBUG "%s: BUSY timeout (%d) in compat_write_block_pio\n",
		       port->name, r);

	port->physport->ieee1284.phase = IEEE1284_PH_FWD_IDLE;

	वापस written;
पूर्ण

/* ECP */
#अगर_घोषित CONFIG_PARPORT_1284
अटल माप_प्रकार parport_pc_ecp_ग_लिखो_block_pio(काष्ठा parport *port,
					      स्थिर व्योम *buf, माप_प्रकार length,
					      पूर्णांक flags)
अणु
	माप_प्रकार written;
	पूर्णांक r;
	अचिन्हित दीर्घ expire;
	स्थिर काष्ठा parport_pc_निजी *priv = port->physport->निजी_data;

	/* Special हाल: a समयout of zero means we cannot call schedule().
	 * Also अगर O_NONBLOCK is set then use the शेष implementation. */
	अगर (port->physport->cad->समयout <= PARPORT_INACTIVITY_O_NONBLOCK)
		वापस parport_ieee1284_ecp_ग_लिखो_data(port, buf,
							length, flags);

	/* Switch to क्रमward mode अगर necessary. */
	अगर (port->physport->ieee1284.phase != IEEE1284_PH_FWD_IDLE) अणु
		/* Event 47: Set nInit high. */
		parport_frob_control(port,
				      PARPORT_CONTROL_INIT
				      | PARPORT_CONTROL_AUTOFD,
				      PARPORT_CONTROL_INIT
				      | PARPORT_CONTROL_AUTOFD);

		/* Event 49: PError goes high. */
		r = parport_रुको_peripheral(port,
					     PARPORT_STATUS_PAPEROUT,
					     PARPORT_STATUS_PAPEROUT);
		अगर (r) अणु
			prपूर्णांकk(KERN_DEBUG "%s: PError timeout (%d) in ecp_write_block_pio\n",
			       port->name, r);
		पूर्ण
	पूर्ण

	/* Set up ECP parallel port mode.*/
	parport_pc_data_क्रमward(port); /* Must be in PS2 mode */
	parport_pc_frob_control(port,
				 PARPORT_CONTROL_STROBE |
				 PARPORT_CONTROL_AUTOFD,
				 0);
	r = change_mode(port, ECR_ECP); /* ECP FIFO */
	अगर (r)
		prपूर्णांकk(KERN_DEBUG "%s: Warning change_mode ECR_ECP failed\n",
		       port->name);
	port->physport->ieee1284.phase = IEEE1284_PH_FWD_DATA;

	/* Write the data to the FIFO. */
	written = parport_pc_fअगरo_ग_लिखो_block(port, buf, length);

	/* Finish up. */
	/* For some hardware we करोn't want to touch the mode until
	 * the FIFO is empty, so allow 4 seconds क्रम each position
	 * in the fअगरo.
	 */
	expire = jअगरfies + (priv->fअगरo_depth * (HZ * 4));
	करो अणु
		/* Wait क्रम the FIFO to empty */
		r = change_mode(port, ECR_PS2);
		अगर (r != -EBUSY)
			अवरोध;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, expire));
	अगर (r == -EBUSY) अणु

		prपूर्णांकk(KERN_DEBUG "%s: FIFO is stuck\n", port->name);

		/* Prevent further data transfer. */
		frob_set_mode(port, ECR_TST);

		/* Adjust क्रम the contents of the FIFO. */
		क्रम (written -= priv->fअगरo_depth; ; written++) अणु
			अगर (inb(ECONTROL(port)) & 0x2) अणु
				/* Full up. */
				अवरोध;
			पूर्ण
			outb(0, FIFO(port));
		पूर्ण

		/* Reset the FIFO and वापस to PS2 mode. */
		frob_set_mode(port, ECR_PS2);

		/* Host transfer recovery. */
		parport_pc_data_reverse(port); /* Must be in PS2 mode */
		udelay(5);
		parport_frob_control(port, PARPORT_CONTROL_INIT, 0);
		r = parport_रुको_peripheral(port, PARPORT_STATUS_PAPEROUT, 0);
		अगर (r)
			prपूर्णांकk(KERN_DEBUG "%s: PE,1 timeout (%d) in ecp_write_block_pio\n",
			       port->name, r);

		parport_frob_control(port,
				      PARPORT_CONTROL_INIT,
				      PARPORT_CONTROL_INIT);
		r = parport_रुको_peripheral(port,
					     PARPORT_STATUS_PAPEROUT,
					     PARPORT_STATUS_PAPEROUT);
		अगर (r)
			prपूर्णांकk(KERN_DEBUG "%s: PE,2 timeout (%d) in ecp_write_block_pio\n",
			       port->name, r);
	पूर्ण

	r = parport_रुको_peripheral(port,
				     PARPORT_STATUS_BUSY,
				     PARPORT_STATUS_BUSY);
	अगर (r)
		prपूर्णांकk(KERN_DEBUG "%s: BUSY timeout (%d) in ecp_write_block_pio\n",
		       port->name, r);

	port->physport->ieee1284.phase = IEEE1284_PH_FWD_IDLE;

	वापस written;
पूर्ण
#पूर्ण_अगर /* IEEE 1284 support */
#पूर्ण_अगर /* Allowed to use FIFO/DMA */


/*
 *	******************************************
 *	INITIALISATION AND MODULE STUFF BELOW HERE
 *	******************************************
 */

/* GCC is not inlining बाह्य अंतरभूत function later overwritten to non-अंतरभूत,
   so we use outlined_ variants here.  */
अटल स्थिर काष्ठा parport_operations parport_pc_ops = अणु
	.ग_लिखो_data	= parport_pc_ग_लिखो_data,
	.पढ़ो_data	= parport_pc_पढ़ो_data,

	.ग_लिखो_control	= parport_pc_ग_लिखो_control,
	.पढ़ो_control	= parport_pc_पढ़ो_control,
	.frob_control	= parport_pc_frob_control,

	.पढ़ो_status	= parport_pc_पढ़ो_status,

	.enable_irq	= parport_pc_enable_irq,
	.disable_irq	= parport_pc_disable_irq,

	.data_क्रमward	= parport_pc_data_क्रमward,
	.data_reverse	= parport_pc_data_reverse,

	.init_state	= parport_pc_init_state,
	.save_state	= parport_pc_save_state,
	.restore_state	= parport_pc_restore_state,

	.epp_ग_लिखो_data	= parport_ieee1284_epp_ग_लिखो_data,
	.epp_पढ़ो_data	= parport_ieee1284_epp_पढ़ो_data,
	.epp_ग_लिखो_addr	= parport_ieee1284_epp_ग_लिखो_addr,
	.epp_पढ़ो_addr	= parport_ieee1284_epp_पढ़ो_addr,

	.ecp_ग_लिखो_data	= parport_ieee1284_ecp_ग_लिखो_data,
	.ecp_पढ़ो_data	= parport_ieee1284_ecp_पढ़ो_data,
	.ecp_ग_लिखो_addr	= parport_ieee1284_ecp_ग_लिखो_addr,

	.compat_ग_लिखो_data	= parport_ieee1284_ग_लिखो_compat,
	.nibble_पढ़ो_data	= parport_ieee1284_पढ़ो_nibble,
	.byte_पढ़ो_data		= parport_ieee1284_पढ़ो_byte,

	.owner		= THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_PARPORT_PC_SUPERIO

अटल काष्ठा superio_काष्ठा *find_मुक्त_superio(व्योम)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < NR_SUPERIOS; i++)
		अगर (superios[i].io == 0)
			वापस &superios[i];
	वापस शून्य;
पूर्ण


/* Super-IO chipset detection, Winbond, SMSC */
अटल व्योम show_parconfig_smsc37c669(पूर्णांक io, पूर्णांक key)
अणु
	पूर्णांक cr1, cr4, cra, cr23, cr26, cr27;
	काष्ठा superio_काष्ठा *s;

	अटल स्थिर अक्षर *स्थिर modes[] = अणु
		"SPP and Bidirectional (PS/2)",
		"EPP and SPP",
		"ECP",
		"ECP and EPP" पूर्ण;

	outb(key, io);
	outb(key, io);
	outb(1, io);
	cr1 = inb(io + 1);
	outb(4, io);
	cr4 = inb(io + 1);
	outb(0x0a, io);
	cra = inb(io + 1);
	outb(0x23, io);
	cr23 = inb(io + 1);
	outb(0x26, io);
	cr26 = inb(io + 1);
	outb(0x27, io);
	cr27 = inb(io + 1);
	outb(0xaa, io);

	अगर (verbose_probing) अणु
		pr_info("SMSC 37c669 LPT Config: cr_1=0x%02x, 4=0x%02x, A=0x%2x, 23=0x%02x, 26=0x%02x, 27=0x%02x\n",
			cr1, cr4, cra, cr23, cr26, cr27);

		/* The करोcumentation calls DMA and IRQ-Lines by letters, so
		   the board maker can/will wire them
		   appropriately/अक्रमomly...  G=reserved H=IDE-irq, */
		pr_info("SMSC LPT Config: io=0x%04x, irq=%c, dma=%c, fifo threshold=%d\n",
			cr23 * 4,
			(cr27 & 0x0f) ? 'A' - 1 + (cr27 & 0x0f) : '-',
			(cr26 & 0x0f) ? 'A' - 1 + (cr26 & 0x0f) : '-',
			cra & 0x0f);
		pr_info("SMSC LPT Config: enabled=%s power=%s\n",
			(cr23 * 4 >= 0x100) ? "yes" : "no",
			(cr1 & 4) ? "yes" : "no");
		pr_info("SMSC LPT Config: Port mode=%s, EPP version =%s\n",
			(cr1 & 0x08) ? "Standard mode only (SPP)"
			: modes[cr4 & 0x03],
			(cr4 & 0x40) ? "1.7" : "1.9");
	पूर्ण

	/* Heuristics !  BIOS setup क्रम this मुख्यboard device limits
	   the choices to standard settings, i.e. io-address and IRQ
	   are related, however DMA can be 1 or 3, assume DMA_A=DMA1,
	   DMA_C=DMA3 (this is true e.g. क्रम TYAN 1564D Tomcat IV) */
	अगर (cr23 * 4 >= 0x100) अणु /* अगर active */
		s = find_मुक्त_superio();
		अगर (s == शून्य)
			pr_info("Super-IO: too many chips!\n");
		अन्यथा अणु
			पूर्णांक d;
			चयन (cr23 * 4) अणु
			हाल 0x3bc:
				s->io = 0x3bc;
				s->irq = 7;
				अवरोध;
			हाल 0x378:
				s->io = 0x378;
				s->irq = 7;
				अवरोध;
			हाल 0x278:
				s->io = 0x278;
				s->irq = 5;
			पूर्ण
			d = (cr26 & 0x0f);
			अगर (d == 1 || d == 3)
				s->dma = d;
			अन्यथा
				s->dma = PARPORT_DMA_NONE;
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम show_parconfig_winbond(पूर्णांक io, पूर्णांक key)
अणु
	पूर्णांक cr30, cr60, cr61, cr70, cr74, crf0;
	काष्ठा superio_काष्ठा *s;
	अटल स्थिर अक्षर *स्थिर modes[] = अणु
		"Standard (SPP) and Bidirectional(PS/2)", /* 0 */
		"EPP-1.9 and SPP",
		"ECP",
		"ECP and EPP-1.9",
		"Standard (SPP)",
		"EPP-1.7 and SPP",		/* 5 */
		"undefined!",
		"ECP and EPP-1.7" पूर्ण;
	अटल अक्षर *स्थिर irqtypes[] = अणु
		"pulsed low, high-Z",
		"follows nACK" पूर्ण;

	/* The रेजिस्टरs are called compatible-PnP because the
	   रेजिस्टर layout is modelled after ISA-PnP, the access
	   method is just another ... */
	outb(key, io);
	outb(key, io);
	outb(0x07, io);   /* Register 7: Select Logical Device */
	outb(0x01, io + 1); /* LD1 is Parallel Port */
	outb(0x30, io);
	cr30 = inb(io + 1);
	outb(0x60, io);
	cr60 = inb(io + 1);
	outb(0x61, io);
	cr61 = inb(io + 1);
	outb(0x70, io);
	cr70 = inb(io + 1);
	outb(0x74, io);
	cr74 = inb(io + 1);
	outb(0xf0, io);
	crf0 = inb(io + 1);
	outb(0xaa, io);

	अगर (verbose_probing) अणु
		pr_info("Winbond LPT Config: cr_30=%02x 60,61=%02x%02x 70=%02x 74=%02x, f0=%02x\n",
			cr30, cr60, cr61, cr70, cr74, crf0);
		pr_info("Winbond LPT Config: active=%s, io=0x%02x%02x irq=%d, ",
			(cr30 & 0x01) ? "yes" : "no", cr60, cr61, cr70 & 0x0f);
		अगर ((cr74 & 0x07) > 3)
			pr_cont("dma=none\n");
		अन्यथा
			pr_cont("dma=%d\n", cr74 & 0x07);
		pr_info("Winbond LPT Config: irqtype=%s, ECP fifo threshold=%d\n",
			irqtypes[crf0 >> 7], (crf0 >> 3) & 0x0f);
		pr_info("Winbond LPT Config: Port mode=%s\n",
			modes[crf0 & 0x07]);
	पूर्ण

	अगर (cr30 & 0x01) अणु /* the settings can be पूर्णांकerrogated later ... */
		s = find_मुक्त_superio();
		अगर (s == शून्य)
			pr_info("Super-IO: too many chips!\n");
		अन्यथा अणु
			s->io = (cr60 << 8) | cr61;
			s->irq = cr70 & 0x0f;
			s->dma = (((cr74 & 0x07) > 3) ?
					   PARPORT_DMA_NONE : (cr74 & 0x07));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम decode_winbond(पूर्णांक efer, पूर्णांक key, पूर्णांक devid, पूर्णांक devrev, पूर्णांक oldid)
अणु
	स्थिर अक्षर *type = "unknown";
	पूर्णांक id, progअगर = 2;

	अगर (devid == devrev)
		/* simple heuristics, we happened to पढ़ो some
		   non-winbond रेजिस्टर */
		वापस;

	id = (devid << 8) | devrev;

	/* Values are from खुला data sheets pdf files, I can just
	   confirm 83977TF is correct :-) */
	अगर (id == 0x9771)
		type = "83977F/AF";
	अन्यथा अगर (id == 0x9773)
		type = "83977TF / SMSC 97w33x/97w34x";
	अन्यथा अगर (id == 0x9774)
		type = "83977ATF";
	अन्यथा अगर ((id & ~0x0f) == 0x5270)
		type = "83977CTF / SMSC 97w36x";
	अन्यथा अगर ((id & ~0x0f) == 0x52f0)
		type = "83977EF / SMSC 97w35x";
	अन्यथा अगर ((id & ~0x0f) == 0x5210)
		type = "83627";
	अन्यथा अगर ((id & ~0x0f) == 0x6010)
		type = "83697HF";
	अन्यथा अगर ((oldid & 0x0f) == 0x0a) अणु
		type = "83877F";
		progअगर = 1;
	पूर्ण अन्यथा अगर ((oldid & 0x0f) == 0x0b) अणु
		type = "83877AF";
		progअगर = 1;
	पूर्ण अन्यथा अगर ((oldid & 0x0f) == 0x0c) अणु
		type = "83877TF";
		progअगर = 1;
	पूर्ण अन्यथा अगर ((oldid & 0x0f) == 0x0d) अणु
		type = "83877ATF";
		progअगर = 1;
	पूर्ण अन्यथा
		progअगर = 0;

	अगर (verbose_probing)
		pr_info("Winbond chip at EFER=0x%x key=0x%02x devid=%02x devrev=%02x oldid=%02x type=%s\n",
			efer, key, devid, devrev, oldid, type);

	अगर (progअगर == 2)
		show_parconfig_winbond(efer, key);
पूर्ण

अटल व्योम decode_smsc(पूर्णांक efer, पूर्णांक key, पूर्णांक devid, पूर्णांक devrev)
अणु
	स्थिर अक्षर *type = "unknown";
	व्योम (*func)(पूर्णांक io, पूर्णांक key);
	पूर्णांक id;

	अगर (devid == devrev)
		/* simple heuristics, we happened to पढ़ो some
		   non-smsc रेजिस्टर */
		वापस;

	func = शून्य;
	id = (devid << 8) | devrev;

	अगर (id == 0x0302) अणु
		type = "37c669";
		func = show_parconfig_smsc37c669;
	पूर्ण अन्यथा अगर (id == 0x6582)
		type = "37c665IR";
	अन्यथा अगर	(devid == 0x65)
		type = "37c665GT";
	अन्यथा अगर	(devid == 0x66)
		type = "37c666GT";

	अगर (verbose_probing)
		pr_info("SMSC chip at EFER=0x%x key=0x%02x devid=%02x devrev=%02x type=%s\n",
			efer, key, devid, devrev, type);

	अगर (func)
		func(efer, key);
पूर्ण


अटल व्योम winbond_check(पूर्णांक io, पूर्णांक key)
अणु
	पूर्णांक origval, devid, devrev, oldid, x_devid, x_devrev, x_oldid;

	अगर (!request_region(io, 3, __func__))
		वापस;

	origval = inb(io); /* Save original value */

	/* First probe without key */
	outb(0x20, io);
	x_devid = inb(io + 1);
	outb(0x21, io);
	x_devrev = inb(io + 1);
	outb(0x09, io);
	x_oldid = inb(io + 1);

	outb(key, io);
	outb(key, io);     /* Write Magic Sequence to EFER, extended
			      function enable रेजिस्टर */
	outb(0x20, io);    /* Write EFIR, extended function index रेजिस्टर */
	devid = inb(io + 1);  /* Read EFDR, extended function data रेजिस्टर */
	outb(0x21, io);
	devrev = inb(io + 1);
	outb(0x09, io);
	oldid = inb(io + 1);
	outb(0xaa, io);    /* Magic Seal */

	outb(origval, io); /* in हाल we poked some entirely dअगरferent hardware */

	अगर ((x_devid == devid) && (x_devrev == devrev) && (x_oldid == oldid))
		जाओ out; /* protection against false positives */

	decode_winbond(io, key, devid, devrev, oldid);
out:
	release_region(io, 3);
पूर्ण

अटल व्योम winbond_check2(पूर्णांक io, पूर्णांक key)
अणु
	पूर्णांक origval[3], devid, devrev, oldid, x_devid, x_devrev, x_oldid;

	अगर (!request_region(io, 3, __func__))
		वापस;

	origval[0] = inb(io); /* Save original values */
	origval[1] = inb(io + 1);
	origval[2] = inb(io + 2);

	/* First probe without the key */
	outb(0x20, io + 2);
	x_devid = inb(io + 2);
	outb(0x21, io + 1);
	x_devrev = inb(io + 2);
	outb(0x09, io + 1);
	x_oldid = inb(io + 2);

	outb(key, io);     /* Write Magic Byte to EFER, extended
			      function enable रेजिस्टर */
	outb(0x20, io + 2);  /* Write EFIR, extended function index रेजिस्टर */
	devid = inb(io + 2);  /* Read EFDR, extended function data रेजिस्टर */
	outb(0x21, io + 1);
	devrev = inb(io + 2);
	outb(0x09, io + 1);
	oldid = inb(io + 2);
	outb(0xaa, io);    /* Magic Seal */

	outb(origval[0], io); /* in हाल we poked some entirely dअगरferent hardware */
	outb(origval[1], io + 1);
	outb(origval[2], io + 2);

	अगर (x_devid == devid && x_devrev == devrev && x_oldid == oldid)
		जाओ out; /* protection against false positives */

	decode_winbond(io, key, devid, devrev, oldid);
out:
	release_region(io, 3);
पूर्ण

अटल व्योम smsc_check(पूर्णांक io, पूर्णांक key)
अणु
	पूर्णांक origval, id, rev, oldid, oldrev, x_id, x_rev, x_oldid, x_oldrev;

	अगर (!request_region(io, 3, __func__))
		वापस;

	origval = inb(io); /* Save original value */

	/* First probe without the key */
	outb(0x0d, io);
	x_oldid = inb(io + 1);
	outb(0x0e, io);
	x_oldrev = inb(io + 1);
	outb(0x20, io);
	x_id = inb(io + 1);
	outb(0x21, io);
	x_rev = inb(io + 1);

	outb(key, io);
	outb(key, io);     /* Write Magic Sequence to EFER, extended
			      function enable रेजिस्टर */
	outb(0x0d, io);    /* Write EFIR, extended function index रेजिस्टर */
	oldid = inb(io + 1);  /* Read EFDR, extended function data रेजिस्टर */
	outb(0x0e, io);
	oldrev = inb(io + 1);
	outb(0x20, io);
	id = inb(io + 1);
	outb(0x21, io);
	rev = inb(io + 1);
	outb(0xaa, io);    /* Magic Seal */

	outb(origval, io); /* in हाल we poked some entirely dअगरferent hardware */

	अगर (x_id == id && x_oldrev == oldrev &&
	    x_oldid == oldid && x_rev == rev)
		जाओ out; /* protection against false positives */

	decode_smsc(io, key, oldid, oldrev);
out:
	release_region(io, 3);
पूर्ण


अटल व्योम detect_and_report_winbond(व्योम)
अणु
	अगर (verbose_probing)
		prपूर्णांकk(KERN_DEBUG "Winbond Super-IO detection, now testing ports 3F0,370,250,4E,2E ...\n");
	winbond_check(0x3f0, 0x87);
	winbond_check(0x370, 0x87);
	winbond_check(0x2e , 0x87);
	winbond_check(0x4e , 0x87);
	winbond_check(0x3f0, 0x86);
	winbond_check2(0x250, 0x88);
	winbond_check2(0x250, 0x89);
पूर्ण

अटल व्योम detect_and_report_smsc(व्योम)
अणु
	अगर (verbose_probing)
		prपूर्णांकk(KERN_DEBUG "SMSC Super-IO detection, now testing Ports 2F0, 370 ...\n");
	smsc_check(0x3f0, 0x55);
	smsc_check(0x370, 0x55);
	smsc_check(0x3f0, 0x44);
	smsc_check(0x370, 0x44);
पूर्ण

अटल व्योम detect_and_report_it87(व्योम)
अणु
	u16 dev;
	u8 origval, r;
	अगर (verbose_probing)
		prपूर्णांकk(KERN_DEBUG "IT8705 Super-IO detection, now testing port 2E ...\n");
	अगर (!request_muxed_region(0x2e, 2, __func__))
		वापस;
	origval = inb(0x2e);		/* Save original value */
	outb(0x87, 0x2e);
	outb(0x01, 0x2e);
	outb(0x55, 0x2e);
	outb(0x55, 0x2e);
	outb(0x20, 0x2e);
	dev = inb(0x2f) << 8;
	outb(0x21, 0x2e);
	dev |= inb(0x2f);
	अगर (dev == 0x8712 || dev == 0x8705 || dev == 0x8715 ||
	    dev == 0x8716 || dev == 0x8718 || dev == 0x8726) अणु
		pr_info("IT%04X SuperIO detected\n", dev);
		outb(0x07, 0x2E);	/* Parallel Port */
		outb(0x03, 0x2F);
		outb(0xF0, 0x2E);	/* BOOT 0x80 off */
		r = inb(0x2f);
		outb(0xF0, 0x2E);
		outb(r | 8, 0x2F);
		outb(0x02, 0x2E);	/* Lock */
		outb(0x02, 0x2F);
	पूर्ण अन्यथा अणु
		outb(origval, 0x2e);	/* Oops, sorry to disturb */
	पूर्ण
	release_region(0x2e, 2);
पूर्ण
#पूर्ण_अगर /* CONFIG_PARPORT_PC_SUPERIO */

अटल काष्ठा superio_काष्ठा *find_superio(काष्ठा parport *p)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < NR_SUPERIOS; i++)
		अगर (superios[i].io == p->base)
			वापस &superios[i];
	वापस शून्य;
पूर्ण

अटल पूर्णांक get_superio_dma(काष्ठा parport *p)
अणु
	काष्ठा superio_काष्ठा *s = find_superio(p);
	अगर (s)
		वापस s->dma;
	वापस PARPORT_DMA_NONE;
पूर्ण

अटल पूर्णांक get_superio_irq(काष्ठा parport *p)
अणु
	काष्ठा superio_काष्ठा *s = find_superio(p);
	अगर (s)
		वापस s->irq;
	वापस PARPORT_IRQ_NONE;
पूर्ण


/* --- Mode detection ------------------------------------- */

/*
 * Checks क्रम port existence, all ports support SPP MODE
 * Returns:
 *         0           :  No parallel port at this address
 *  PARPORT_MODE_PCSPP :  SPP port detected
 *                        (अगर the user specअगरied an ioport himself,
 *                         this shall always be the हाल!)
 *
 */
अटल पूर्णांक parport_SPP_supported(काष्ठा parport *pb)
अणु
	अचिन्हित अक्षर r, w;

	/*
	 * first clear an eventually pending EPP समयout
	 * I (sailer@अगरe.ee.ethz.ch) have an SMSC chipset
	 * that करोes not even respond to SPP cycles अगर an EPP
	 * समयout is pending
	 */
	clear_epp_समयout(pb);

	/* Do a simple पढ़ो-ग_लिखो test to make sure the port exists. */
	w = 0xc;
	outb(w, CONTROL(pb));

	/* Is there a control रेजिस्टर that we can पढ़ो from?  Some
	 * ports करोn't allow पढ़ोs, so पढ़ो_control just वापसs a
	 * software copy. Some ports _करो_ allow पढ़ोs, so bypass the
	 * software copy here.  In addition, some bits aren't
	 * writable. */
	r = inb(CONTROL(pb));
	अगर ((r & 0xf) == w) अणु
		w = 0xe;
		outb(w, CONTROL(pb));
		r = inb(CONTROL(pb));
		outb(0xc, CONTROL(pb));
		अगर ((r & 0xf) == w)
			वापस PARPORT_MODE_PCSPP;
	पूर्ण

	अगर (user_specअगरied)
		/* That didn't work, but the user thinks there's a
		 * port here. */
		pr_info("parport 0x%lx (WARNING): CTR: wrote 0x%02x, read 0x%02x\n",
			pb->base, w, r);

	/* Try the data रेजिस्टर.  The data lines aren't tri-stated at
	 * this stage, so we expect back what we wrote. */
	w = 0xaa;
	parport_pc_ग_लिखो_data(pb, w);
	r = parport_pc_पढ़ो_data(pb);
	अगर (r == w) अणु
		w = 0x55;
		parport_pc_ग_लिखो_data(pb, w);
		r = parport_pc_पढ़ो_data(pb);
		अगर (r == w)
			वापस PARPORT_MODE_PCSPP;
	पूर्ण

	अगर (user_specअगरied) अणु
		/* Didn't work, but the user is convinced this is the
		 * place. */
		pr_info("parport 0x%lx (WARNING): DATA: wrote 0x%02x, read 0x%02x\n",
			pb->base, w, r);
		pr_info("parport 0x%lx: You gave this address, but there is probably no parallel port there!\n",
			pb->base);
	पूर्ण

	/* It's possible that we can't पढ़ो the control रेजिस्टर or
	 * the data रेजिस्टर.  In that हाल just believe the user. */
	अगर (user_specअगरied)
		वापस PARPORT_MODE_PCSPP;

	वापस 0;
पूर्ण

/* Check क्रम ECR
 *
 * Old style XT ports alias io ports every 0x400, hence accessing ECR
 * on these cards actually accesses the CTR.
 *
 * Modern cards करोn't करो this but पढ़ोing from ECR will वापस 0xff
 * regardless of what is written here अगर the card करोes NOT support
 * ECP.
 *
 * We first check to see अगर ECR is the same as CTR.  If not, the low
 * two bits of ECR aren't writable, so we check by writing ECR and
 * पढ़ोing it back to see अगर it's what we expect.
 */
अटल पूर्णांक parport_ECR_present(काष्ठा parport *pb)
अणु
	काष्ठा parport_pc_निजी *priv = pb->निजी_data;
	अचिन्हित अक्षर r = 0xc;

	outb(r, CONTROL(pb));
	अगर ((inb(ECONTROL(pb)) & 0x3) == (r & 0x3)) अणु
		outb(r ^ 0x2, CONTROL(pb)); /* Toggle bit 1 */

		r = inb(CONTROL(pb));
		अगर ((inb(ECONTROL(pb)) & 0x2) == (r & 0x2))
			जाओ no_reg; /* Sure that no ECR रेजिस्टर exists */
	पूर्ण

	अगर ((inb(ECONTROL(pb)) & 0x3) != 0x1)
		जाओ no_reg;

	ECR_WRITE(pb, 0x34);
	अगर (inb(ECONTROL(pb)) != 0x35)
		जाओ no_reg;

	priv->ecr = 1;
	outb(0xc, CONTROL(pb));

	/* Go to mode 000 */
	frob_set_mode(pb, ECR_SPP);

	वापस 1;

 no_reg:
	outb(0xc, CONTROL(pb));
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PARPORT_1284
/* Detect PS/2 support.
 *
 * Bit 5 (0x20) sets the PS/2 data direction; setting this high
 * allows us to पढ़ो data from the data lines.  In theory we would get back
 * 0xff but any peripheral attached to the port may drag some or all of the
 * lines करोwn to zero.  So अगर we get back anything that isn't the contents
 * of the data रेजिस्टर we deem PS/2 support to be present.
 *
 * Some SPP ports have "half PS/2" ability - you can't turn off the line
 * drivers, but an बाह्यal peripheral with sufficiently beefy drivers of
 * its own can overघातer them and निश्चित its own levels onto the bus, from
 * where they can then be पढ़ो back as normal.  Ports with this property
 * and the right type of device attached are likely to fail the SPP test,
 * (as they will appear to have stuck bits) and so the fact that they might
 * be misdetected here is rather academic.
 */

अटल पूर्णांक parport_PS2_supported(काष्ठा parport *pb)
अणु
	पूर्णांक ok = 0;

	clear_epp_समयout(pb);

	/* try to tri-state the buffer */
	parport_pc_data_reverse(pb);

	parport_pc_ग_लिखो_data(pb, 0x55);
	अगर (parport_pc_पढ़ो_data(pb) != 0x55)
		ok++;

	parport_pc_ग_लिखो_data(pb, 0xaa);
	अगर (parport_pc_पढ़ो_data(pb) != 0xaa)
		ok++;

	/* cancel input mode */
	parport_pc_data_क्रमward(pb);

	अगर (ok) अणु
		pb->modes |= PARPORT_MODE_TRISTATE;
	पूर्ण अन्यथा अणु
		काष्ठा parport_pc_निजी *priv = pb->निजी_data;
		priv->ctr_writable &= ~0x20;
	पूर्ण

	वापस ok;
पूर्ण

#अगर_घोषित CONFIG_PARPORT_PC_FIFO
अटल पूर्णांक parport_ECP_supported(काष्ठा parport *pb)
अणु
	पूर्णांक i;
	पूर्णांक config, configb;
	पूर्णांक pword;
	काष्ठा parport_pc_निजी *priv = pb->निजी_data;
	/* Translate ECP पूर्णांकrLine to ISA irq value */
	अटल स्थिर पूर्णांक पूर्णांकrline[] = अणु 0, 7, 9, 10, 11, 14, 15, 5 पूर्ण;

	/* If there is no ECR, we have no hope of supporting ECP. */
	अगर (!priv->ecr)
		वापस 0;

	/* Find out FIFO depth */
	ECR_WRITE(pb, ECR_SPP << 5); /* Reset FIFO */
	ECR_WRITE(pb, ECR_TST << 5); /* TEST FIFO */
	क्रम (i = 0; i < 1024 && !(inb(ECONTROL(pb)) & 0x02); i++)
		outb(0xaa, FIFO(pb));

	/*
	 * Using LGS chipset it uses ECR रेजिस्टर, but
	 * it करोesn't support ECP or FIFO MODE
	 */
	अगर (i == 1024) अणु
		ECR_WRITE(pb, ECR_SPP << 5);
		वापस 0;
	पूर्ण

	priv->fअगरo_depth = i;
	अगर (verbose_probing)
		prपूर्णांकk(KERN_DEBUG "0x%lx: FIFO is %d bytes\n", pb->base, i);

	/* Find out ग_लिखोIntrThreshold */
	frob_econtrol(pb, 1<<2, 1<<2);
	frob_econtrol(pb, 1<<2, 0);
	क्रम (i = 1; i <= priv->fअगरo_depth; i++) अणु
		inb(FIFO(pb));
		udelay(50);
		अगर (inb(ECONTROL(pb)) & (1<<2))
			अवरोध;
	पूर्ण

	अगर (i <= priv->fअगरo_depth) अणु
		अगर (verbose_probing)
			prपूर्णांकk(KERN_DEBUG "0x%lx: writeIntrThreshold is %d\n",
			       pb->base, i);
	पूर्ण अन्यथा
		/* Number of bytes we know we can ग_लिखो अगर we get an
		   पूर्णांकerrupt. */
		i = 0;

	priv->ग_लिखोIntrThreshold = i;

	/* Find out पढ़ोIntrThreshold */
	frob_set_mode(pb, ECR_PS2); /* Reset FIFO and enable PS2 */
	parport_pc_data_reverse(pb); /* Must be in PS2 mode */
	frob_set_mode(pb, ECR_TST); /* Test FIFO */
	frob_econtrol(pb, 1<<2, 1<<2);
	frob_econtrol(pb, 1<<2, 0);
	क्रम (i = 1; i <= priv->fअगरo_depth; i++) अणु
		outb(0xaa, FIFO(pb));
		अगर (inb(ECONTROL(pb)) & (1<<2))
			अवरोध;
	पूर्ण

	अगर (i <= priv->fअगरo_depth) अणु
		अगर (verbose_probing)
			pr_info("0x%lx: readIntrThreshold is %d\n",
				pb->base, i);
	पूर्ण अन्यथा
		/* Number of bytes we can पढ़ो अगर we get an पूर्णांकerrupt. */
		i = 0;

	priv->पढ़ोIntrThreshold = i;

	ECR_WRITE(pb, ECR_SPP << 5); /* Reset FIFO */
	ECR_WRITE(pb, 0xf4); /* Configuration mode */
	config = inb(CONFIGA(pb));
	pword = (config >> 4) & 0x7;
	चयन (pword) अणु
	हाल 0:
		pword = 2;
		pr_warn("0x%lx: Unsupported pword size!\n", pb->base);
		अवरोध;
	हाल 2:
		pword = 4;
		pr_warn("0x%lx: Unsupported pword size!\n", pb->base);
		अवरोध;
	शेष:
		pr_warn("0x%lx: Unknown implementation ID\n", pb->base);
		fallthrough;	/* Assume 1 */
	हाल 1:
		pword = 1;
	पूर्ण
	priv->pword = pword;

	अगर (verbose_probing) अणु
		prपूर्णांकk(KERN_DEBUG "0x%lx: PWord is %d bits\n",
		       pb->base, 8 * pword);

		prपूर्णांकk(KERN_DEBUG "0x%lx: Interrupts are ISA-%s\n",
		       pb->base, config & 0x80 ? "Level" : "Pulses");

		configb = inb(CONFIGB(pb));
		prपूर्णांकk(KERN_DEBUG "0x%lx: ECP port cfgA=0x%02x cfgB=0x%02x\n",
		       pb->base, config, configb);
		prपूर्णांकk(KERN_DEBUG "0x%lx: ECP settings irq=", pb->base);
		अगर ((configb >> 3) & 0x07)
			pr_cont("%d", पूर्णांकrline[(configb >> 3) & 0x07]);
		अन्यथा
			pr_cont("<none or set by other means>");
		pr_cont(" dma=");
		अगर ((configb & 0x03) == 0x00)
			pr_cont("<none or set by other means>\n");
		अन्यथा
			pr_cont("%d\n", configb & 0x07);
	पूर्ण

	/* Go back to mode 000 */
	frob_set_mode(pb, ECR_SPP);

	वापस 1;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_32
अटल पूर्णांक पूर्णांकel_bug_present_check_epp(काष्ठा parport *pb)
अणु
	स्थिर काष्ठा parport_pc_निजी *priv = pb->निजी_data;
	पूर्णांक bug_present = 0;

	अगर (priv->ecr) अणु
		/* store value of ECR */
		अचिन्हित अक्षर ecr = inb(ECONTROL(pb));
		अचिन्हित अक्षर i;
		क्रम (i = 0x00; i < 0x80; i += 0x20) अणु
			ECR_WRITE(pb, i);
			अगर (clear_epp_समयout(pb)) अणु
				/* Phony EPP in ECP. */
				bug_present = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		/* वापस ECR पूर्णांकo the inital state */
		ECR_WRITE(pb, ecr);
	पूर्ण

	वापस bug_present;
पूर्ण
अटल पूर्णांक पूर्णांकel_bug_present(काष्ठा parport *pb)
अणु
/* Check whether the device is legacy, not PCI or PCMCIA. Only legacy is known to be affected. */
	अगर (pb->dev != शून्य) अणु
		वापस 0;
	पूर्ण

	वापस पूर्णांकel_bug_present_check_epp(pb);
पूर्ण
#अन्यथा
अटल पूर्णांक पूर्णांकel_bug_present(काष्ठा parport *pb)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_32 */

अटल पूर्णांक parport_ECPPS2_supported(काष्ठा parport *pb)
अणु
	स्थिर काष्ठा parport_pc_निजी *priv = pb->निजी_data;
	पूर्णांक result;
	अचिन्हित अक्षर oecr;

	अगर (!priv->ecr)
		वापस 0;

	oecr = inb(ECONTROL(pb));
	ECR_WRITE(pb, ECR_PS2 << 5);
	result = parport_PS2_supported(pb);
	ECR_WRITE(pb, oecr);
	वापस result;
पूर्ण

/* EPP mode detection  */

अटल पूर्णांक parport_EPP_supported(काष्ठा parport *pb)
अणु
	/*
	 * Theory:
	 *	Bit 0 of STR is the EPP समयout bit, this bit is 0
	 *	when EPP is possible and is set high when an EPP समयout
	 *	occurs (EPP uses the HALT line to stop the CPU जबतक it करोes
	 *	the byte transfer, an EPP समयout occurs अगर the attached
	 *	device fails to respond after 10 micro seconds).
	 *
	 *	This bit is cleared by either पढ़ोing it (National Semi)
	 *	or writing a 1 to the bit (SMC, UMC, WinBond), others ???
	 *	This bit is always high in non EPP modes.
	 */

	/* If EPP समयout bit clear then EPP available */
	अगर (!clear_epp_समयout(pb))
		वापस 0;  /* No way to clear समयout */

	/* Check क्रम Intel bug. */
	अगर (पूर्णांकel_bug_present(pb))
		वापस 0;

	pb->modes |= PARPORT_MODE_EPP;

	/* Set up access functions to use EPP hardware. */
	pb->ops->epp_पढ़ो_data = parport_pc_epp_पढ़ो_data;
	pb->ops->epp_ग_लिखो_data = parport_pc_epp_ग_लिखो_data;
	pb->ops->epp_पढ़ो_addr = parport_pc_epp_पढ़ो_addr;
	pb->ops->epp_ग_लिखो_addr = parport_pc_epp_ग_लिखो_addr;

	वापस 1;
पूर्ण

अटल पूर्णांक parport_ECPEPP_supported(काष्ठा parport *pb)
अणु
	काष्ठा parport_pc_निजी *priv = pb->निजी_data;
	पूर्णांक result;
	अचिन्हित अक्षर oecr;

	अगर (!priv->ecr)
		वापस 0;

	oecr = inb(ECONTROL(pb));
	/* Search क्रम SMC style EPP+ECP mode */
	ECR_WRITE(pb, 0x80);
	outb(0x04, CONTROL(pb));
	result = parport_EPP_supported(pb);

	ECR_WRITE(pb, oecr);

	अगर (result) अणु
		/* Set up access functions to use ECP+EPP hardware. */
		pb->ops->epp_पढ़ो_data = parport_pc_ecpepp_पढ़ो_data;
		pb->ops->epp_ग_लिखो_data = parport_pc_ecpepp_ग_लिखो_data;
		pb->ops->epp_पढ़ो_addr = parport_pc_ecpepp_पढ़ो_addr;
		pb->ops->epp_ग_लिखो_addr = parport_pc_ecpepp_ग_लिखो_addr;
	पूर्ण

	वापस result;
पूर्ण

#अन्यथा /* No IEEE 1284 support */

/* Don't bother probing for modes we know we won't use. */
अटल पूर्णांक parport_PS2_supported(काष्ठा parport *pb) अणु वापस 0; पूर्ण
#अगर_घोषित CONFIG_PARPORT_PC_FIFO
अटल पूर्णांक parport_ECP_supported(काष्ठा parport *pb)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल पूर्णांक parport_EPP_supported(काष्ठा parport *pb)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक parport_ECPEPP_supported(काष्ठा parport *pb)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक parport_ECPPS2_supported(काष्ठा parport *pb)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* No IEEE 1284 support */

/* --- IRQ detection -------------------------------------- */

/* Only अगर supports ECP mode */
अटल पूर्णांक programmable_irq_support(काष्ठा parport *pb)
अणु
	पूर्णांक irq, पूर्णांकrLine;
	अचिन्हित अक्षर oecr = inb(ECONTROL(pb));
	अटल स्थिर पूर्णांक lookup[8] = अणु
		PARPORT_IRQ_NONE, 7, 9, 10, 11, 14, 15, 5
	पूर्ण;

	ECR_WRITE(pb, ECR_CNF << 5); /* Configuration MODE */

	पूर्णांकrLine = (inb(CONFIGB(pb)) >> 3) & 0x07;
	irq = lookup[पूर्णांकrLine];

	ECR_WRITE(pb, oecr);
	वापस irq;
पूर्ण

अटल पूर्णांक irq_probe_ECP(काष्ठा parport *pb)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ irqs;

	irqs = probe_irq_on();

	ECR_WRITE(pb, ECR_SPP << 5); /* Reset FIFO */
	ECR_WRITE(pb, (ECR_TST << 5) | 0x04);
	ECR_WRITE(pb, ECR_TST << 5);

	/* If Full FIFO sure that ग_लिखोIntrThreshold is generated */
	क्रम (i = 0; i < 1024 && !(inb(ECONTROL(pb)) & 0x02) ; i++)
		outb(0xaa, FIFO(pb));

	pb->irq = probe_irq_off(irqs);
	ECR_WRITE(pb, ECR_SPP << 5);

	अगर (pb->irq <= 0)
		pb->irq = PARPORT_IRQ_NONE;

	वापस pb->irq;
पूर्ण

/*
 * This detection seems that only works in National Semiconductors
 * This करोesn't work in SMC, LGS, and Winbond
 */
अटल पूर्णांक irq_probe_EPP(काष्ठा parport *pb)
अणु
#अगर_अघोषित ADVANCED_DETECT
	वापस PARPORT_IRQ_NONE;
#अन्यथा
	पूर्णांक irqs;
	अचिन्हित अक्षर oecr;

	अगर (pb->modes & PARPORT_MODE_PCECR)
		oecr = inb(ECONTROL(pb));

	irqs = probe_irq_on();

	अगर (pb->modes & PARPORT_MODE_PCECR)
		frob_econtrol(pb, 0x10, 0x10);

	clear_epp_समयout(pb);
	parport_pc_frob_control(pb, 0x20, 0x20);
	parport_pc_frob_control(pb, 0x10, 0x10);
	clear_epp_समयout(pb);

	/* Device isn't expecting an EPP पढ़ो
	 * and generates an IRQ.
	 */
	parport_pc_पढ़ो_epp(pb);
	udelay(20);

	pb->irq = probe_irq_off(irqs);
	अगर (pb->modes & PARPORT_MODE_PCECR)
		ECR_WRITE(pb, oecr);
	parport_pc_ग_लिखो_control(pb, 0xc);

	अगर (pb->irq <= 0)
		pb->irq = PARPORT_IRQ_NONE;

	वापस pb->irq;
#पूर्ण_अगर /* Advanced detection */
पूर्ण

अटल पूर्णांक irq_probe_SPP(काष्ठा parport *pb)
अणु
	/* Don't even try to करो this. */
	वापस PARPORT_IRQ_NONE;
पूर्ण

/* We will attempt to share पूर्णांकerrupt requests since other devices
 * such as sound cards and network cards seem to like using the
 * prपूर्णांकer IRQs.
 *
 * When ECP is available we can स्वतःprobe क्रम IRQs.
 * NOTE: If we can स्वतःprobe it, we can रेजिस्टर the IRQ.
 */
अटल पूर्णांक parport_irq_probe(काष्ठा parport *pb)
अणु
	काष्ठा parport_pc_निजी *priv = pb->निजी_data;

	अगर (priv->ecr) अणु
		pb->irq = programmable_irq_support(pb);

		अगर (pb->irq == PARPORT_IRQ_NONE)
			pb->irq = irq_probe_ECP(pb);
	पूर्ण

	अगर ((pb->irq == PARPORT_IRQ_NONE) && priv->ecr &&
	    (pb->modes & PARPORT_MODE_EPP))
		pb->irq = irq_probe_EPP(pb);

	clear_epp_समयout(pb);

	अगर (pb->irq == PARPORT_IRQ_NONE && (pb->modes & PARPORT_MODE_EPP))
		pb->irq = irq_probe_EPP(pb);

	clear_epp_समयout(pb);

	अगर (pb->irq == PARPORT_IRQ_NONE)
		pb->irq = irq_probe_SPP(pb);

	अगर (pb->irq == PARPORT_IRQ_NONE)
		pb->irq = get_superio_irq(pb);

	वापस pb->irq;
पूर्ण

/* --- DMA detection -------------------------------------- */

/* Only अगर chipset conक्रमms to ECP ISA Interface Standard */
अटल पूर्णांक programmable_dma_support(काष्ठा parport *p)
अणु
	अचिन्हित अक्षर oecr = inb(ECONTROL(p));
	पूर्णांक dma;

	frob_set_mode(p, ECR_CNF);

	dma = inb(CONFIGB(p)) & 0x07;
	/* 000: Indicates jumpered 8-bit DMA अगर पढ़ो-only.
	   100: Indicates jumpered 16-bit DMA अगर पढ़ो-only. */
	अगर ((dma & 0x03) == 0)
		dma = PARPORT_DMA_NONE;

	ECR_WRITE(p, oecr);
	वापस dma;
पूर्ण

अटल पूर्णांक parport_dma_probe(काष्ठा parport *p)
अणु
	स्थिर काष्ठा parport_pc_निजी *priv = p->निजी_data;
	अगर (priv->ecr)		/* ask ECP chipset first */
		p->dma = programmable_dma_support(p);
	अगर (p->dma == PARPORT_DMA_NONE) अणु
		/* ask known Super-IO chips proper, although these
		   claim ECP compatible, some करोn't report their DMA
		   conक्रमming to ECP standards */
		p->dma = get_superio_dma(p);
	पूर्ण

	वापस p->dma;
पूर्ण

/* --- Initialisation code -------------------------------- */

अटल LIST_HEAD(ports_list);
अटल DEFINE_SPINLOCK(ports_lock);

काष्ठा parport *parport_pc_probe_port(अचिन्हित दीर्घ पूर्णांक base,
				      अचिन्हित दीर्घ पूर्णांक base_hi,
				      पूर्णांक irq, पूर्णांक dma,
				      काष्ठा device *dev,
				      पूर्णांक irqflags)
अणु
	काष्ठा parport_pc_निजी *priv;
	काष्ठा parport_operations *ops;
	काष्ठा parport *p;
	पूर्णांक probedirq = PARPORT_IRQ_NONE;
	काष्ठा resource *base_res;
	काष्ठा resource	*ECR_res = शून्य;
	काष्ठा resource	*EPP_res = शून्य;
	काष्ठा platक्रमm_device *pdev = शून्य;
	पूर्णांक ret;

	अगर (!dev) अणु
		/* We need a physical device to attach to, but none was
		 * provided. Create our own. */
		pdev = platक्रमm_device_रेजिस्टर_simple("parport_pc",
						       base, शून्य, 0);
		अगर (IS_ERR(pdev))
			वापस शून्य;
		dev = &pdev->dev;

		ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(24));
		अगर (ret) अणु
			dev_err(dev, "Unable to set coherent dma mask: disabling DMA\n");
			dma = PARPORT_DMA_NONE;
		पूर्ण
	पूर्ण

	ops = kदो_स्मृति(माप(काष्ठा parport_operations), GFP_KERNEL);
	अगर (!ops)
		जाओ out1;

	priv = kदो_स्मृति(माप(काष्ठा parport_pc_निजी), GFP_KERNEL);
	अगर (!priv)
		जाओ out2;

	/* a misnomer, actually - it's allocate and reserve parport number */
	p = parport_रेजिस्टर_port(base, irq, dma, ops);
	अगर (!p)
		जाओ out3;

	base_res = request_region(base, 3, p->name);
	अगर (!base_res)
		जाओ out4;

	स_नकल(ops, &parport_pc_ops, माप(काष्ठा parport_operations));
	priv->ctr = 0xc;
	priv->ctr_writable = ~0x10;
	priv->ecr = 0;
	priv->fअगरo_depth = 0;
	priv->dma_buf = शून्य;
	priv->dma_handle = 0;
	INIT_LIST_HEAD(&priv->list);
	priv->port = p;

	p->dev = dev;
	p->base_hi = base_hi;
	p->modes = PARPORT_MODE_PCSPP | PARPORT_MODE_SAFEININT;
	p->निजी_data = priv;

	अगर (base_hi) अणु
		ECR_res = request_region(base_hi, 3, p->name);
		अगर (ECR_res)
			parport_ECR_present(p);
	पूर्ण

	अगर (base != 0x3bc) अणु
		EPP_res = request_region(base+0x3, 5, p->name);
		अगर (EPP_res)
			अगर (!parport_EPP_supported(p))
				parport_ECPEPP_supported(p);
	पूर्ण
	अगर (!parport_SPP_supported(p))
		/* No port. */
		जाओ out5;
	अगर (priv->ecr)
		parport_ECPPS2_supported(p);
	अन्यथा
		parport_PS2_supported(p);

	p->size = (p->modes & PARPORT_MODE_EPP) ? 8 : 3;

	pr_info("%s: PC-style at 0x%lx", p->name, p->base);
	अगर (p->base_hi && priv->ecr)
		pr_cont(" (0x%lx)", p->base_hi);
	अगर (p->irq == PARPORT_IRQ_AUTO) अणु
		p->irq = PARPORT_IRQ_NONE;
		parport_irq_probe(p);
	पूर्ण अन्यथा अगर (p->irq == PARPORT_IRQ_PROBEONLY) अणु
		p->irq = PARPORT_IRQ_NONE;
		parport_irq_probe(p);
		probedirq = p->irq;
		p->irq = PARPORT_IRQ_NONE;
	पूर्ण
	अगर (p->irq != PARPORT_IRQ_NONE) अणु
		pr_cont(", irq %d", p->irq);
		priv->ctr_writable |= 0x10;

		अगर (p->dma == PARPORT_DMA_AUTO) अणु
			p->dma = PARPORT_DMA_NONE;
			parport_dma_probe(p);
		पूर्ण
	पूर्ण
	अगर (p->dma == PARPORT_DMA_AUTO) /* To use DMA, giving the irq
					   is mandatory (see above) */
		p->dma = PARPORT_DMA_NONE;

#अगर_घोषित CONFIG_PARPORT_PC_FIFO
	अगर (parport_ECP_supported(p) &&
	    p->dma != PARPORT_DMA_NOFIFO &&
	    priv->fअगरo_depth > 0 && p->irq != PARPORT_IRQ_NONE) अणु
		p->modes |= PARPORT_MODE_ECP | PARPORT_MODE_COMPAT;
		p->ops->compat_ग_लिखो_data = parport_pc_compat_ग_लिखो_block_pio;
#अगर_घोषित CONFIG_PARPORT_1284
		p->ops->ecp_ग_लिखो_data = parport_pc_ecp_ग_लिखो_block_pio;
		/* currently broken, but working on it.. (FB) */
		/* p->ops->ecp_पढ़ो_data = parport_pc_ecp_पढ़ो_block_pio; */
#पूर्ण_अगर /* IEEE 1284 support */
		अगर (p->dma != PARPORT_DMA_NONE) अणु
			pr_cont(", dma %d", p->dma);
			p->modes |= PARPORT_MODE_DMA;
		पूर्ण अन्यथा
			pr_cont(", using FIFO");
	पूर्ण अन्यथा
		/* We can't use the DMA channel after all. */
		p->dma = PARPORT_DMA_NONE;
#पूर्ण_अगर /* Allowed to use FIFO/DMA */

	pr_cont(" [");

#घोषणा prपूर्णांकmode(x)							\
करो अणु									\
	अगर (p->modes & PARPORT_MODE_##x)				\
		pr_cont("%s%s", f++ ? "," : "", #x);			\
पूर्ण जबतक (0)

	अणु
		पूर्णांक f = 0;
		prपूर्णांकmode(PCSPP);
		prपूर्णांकmode(TRISTATE);
		prपूर्णांकmode(COMPAT);
		prपूर्णांकmode(EPP);
		prपूर्णांकmode(ECP);
		prपूर्णांकmode(DMA);
	पूर्ण
#अघोषित prपूर्णांकmode
#अगर_अघोषित CONFIG_PARPORT_1284
	pr_cont("(,...)");
#पूर्ण_अगर /* CONFIG_PARPORT_1284 */
	pr_cont("]\n");
	अगर (probedirq != PARPORT_IRQ_NONE)
		pr_info("%s: irq %d detected\n", p->name, probedirq);

	/* If No ECP release the ports grabbed above. */
	अगर (ECR_res && (p->modes & PARPORT_MODE_ECP) == 0) अणु
		release_region(base_hi, 3);
		ECR_res = शून्य;
	पूर्ण
	/* Likewise क्रम EEP ports */
	अगर (EPP_res && (p->modes & PARPORT_MODE_EPP) == 0) अणु
		release_region(base+3, 5);
		EPP_res = शून्य;
	पूर्ण
	अगर (p->irq != PARPORT_IRQ_NONE) अणु
		अगर (request_irq(p->irq, parport_irq_handler,
				 irqflags, p->name, p)) अणु
			pr_warn("%s: irq %d in use, resorting to polled operation\n",
				p->name, p->irq);
			p->irq = PARPORT_IRQ_NONE;
			p->dma = PARPORT_DMA_NONE;
		पूर्ण

#अगर_घोषित CONFIG_PARPORT_PC_FIFO
#अगर_घोषित HAS_DMA
		अगर (p->dma != PARPORT_DMA_NONE) अणु
			अगर (request_dma(p->dma, p->name)) अणु
				pr_warn("%s: dma %d in use, resorting to PIO operation\n",
					p->name, p->dma);
				p->dma = PARPORT_DMA_NONE;
			पूर्ण अन्यथा अणु
				priv->dma_buf =
				  dma_alloc_coherent(dev,
						       PAGE_SIZE,
						       &priv->dma_handle,
						       GFP_KERNEL);
				अगर (!priv->dma_buf) अणु
					pr_warn("%s: cannot get buffer for DMA, resorting to PIO operation\n",
						p->name);
					मुक्त_dma(p->dma);
					p->dma = PARPORT_DMA_NONE;
				पूर्ण
			पूर्ण
		पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
	पूर्ण

	/* Done probing.  Now put the port पूर्णांकo a sensible start-up state. */
	अगर (priv->ecr)
		/*
		 * Put the ECP detected port in PS2 mode.
		 * Do this also क्रम ports that have ECR but करोn't करो ECP.
		 */
		ECR_WRITE(p, 0x34);

	parport_pc_ग_लिखो_data(p, 0);
	parport_pc_data_क्रमward(p);

	/* Now that we've told the sharing engine about the port, and
	   found out its अक्षरacteristics, let the high-level drivers
	   know about it. */
	spin_lock(&ports_lock);
	list_add(&priv->list, &ports_list);
	spin_unlock(&ports_lock);
	parport_announce_port(p);

	वापस p;

out5:
	अगर (ECR_res)
		release_region(base_hi, 3);
	अगर (EPP_res)
		release_region(base+0x3, 5);
	release_region(base, 3);
out4:
	parport_del_port(p);
out3:
	kमुक्त(priv);
out2:
	kमुक्त(ops);
out1:
	अगर (pdev)
		platक्रमm_device_unरेजिस्टर(pdev);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(parport_pc_probe_port);

व्योम parport_pc_unरेजिस्टर_port(काष्ठा parport *p)
अणु
	काष्ठा parport_pc_निजी *priv = p->निजी_data;
	काष्ठा parport_operations *ops = p->ops;

	parport_हटाओ_port(p);
	spin_lock(&ports_lock);
	list_del_init(&priv->list);
	spin_unlock(&ports_lock);
#अगर defined(CONFIG_PARPORT_PC_FIFO) && defined(HAS_DMA)
	अगर (p->dma != PARPORT_DMA_NONE)
		मुक्त_dma(p->dma);
#पूर्ण_अगर
	अगर (p->irq != PARPORT_IRQ_NONE)
		मुक्त_irq(p->irq, p);
	release_region(p->base, 3);
	अगर (p->size > 3)
		release_region(p->base + 3, p->size - 3);
	अगर (p->modes & PARPORT_MODE_ECP)
		release_region(p->base_hi, 3);
#अगर defined(CONFIG_PARPORT_PC_FIFO) && defined(HAS_DMA)
	अगर (priv->dma_buf)
		dma_मुक्त_coherent(p->physport->dev, PAGE_SIZE,
				    priv->dma_buf,
				    priv->dma_handle);
#पूर्ण_अगर
	kमुक्त(p->निजी_data);
	parport_del_port(p);
	kमुक्त(ops); /* hope no-one cached it */
पूर्ण
EXPORT_SYMBOL(parport_pc_unरेजिस्टर_port);

#अगर_घोषित CONFIG_PCI

/* ITE support मुख्यtained by Rich Liu <richliu@poorman.org> */
अटल पूर्णांक sio_ite_8872_probe(काष्ठा pci_dev *pdev, पूर्णांक स्वतःirq, पूर्णांक स्वतःdma,
			      स्थिर काष्ठा parport_pc_via_data *via)
अणु
	लघु पूर्णांकa_addr[6] = अणु 0x2A0, 0x2C0, 0x220, 0x240, 0x1E0 पूर्ण;
	u32 ite8872set;
	u32 ite8872_lpt, ite8872_lpthi;
	u8 ite8872_irq, type;
	पूर्णांक irq;
	पूर्णांक i;

	pr_debug("sio_ite_8872_probe()\n");

	/* make sure which one chip */
	क्रम (i = 0; i < 5; i++) अणु
		अगर (request_region(पूर्णांकa_addr[i], 32, "it887x")) अणु
			पूर्णांक test;
			pci_ग_लिखो_config_dword(pdev, 0x60,
						0xe5000000 | पूर्णांकa_addr[i]);
			pci_ग_लिखो_config_dword(pdev, 0x78,
						0x00000000 | पूर्णांकa_addr[i]);
			test = inb(पूर्णांकa_addr[i]);
			अगर (test != 0xff)
				अवरोध;
			release_region(पूर्णांकa_addr[i], 32);
		पूर्ण
	पूर्ण
	अगर (i >= 5) अणु
		pr_info("parport_pc: cannot find ITE8872 INTA\n");
		वापस 0;
	पूर्ण

	type = inb(पूर्णांकa_addr[i] + 0x18);
	type &= 0x0f;

	चयन (type) अणु
	हाल 0x2:
		pr_info("parport_pc: ITE8871 found (1P)\n");
		ite8872set = 0x64200000;
		अवरोध;
	हाल 0xa:
		pr_info("parport_pc: ITE8875 found (1P)\n");
		ite8872set = 0x64200000;
		अवरोध;
	हाल 0xe:
		pr_info("parport_pc: ITE8872 found (2S1P)\n");
		ite8872set = 0x64e00000;
		अवरोध;
	हाल 0x6:
		pr_info("parport_pc: ITE8873 found (1S)\n");
		release_region(पूर्णांकa_addr[i], 32);
		वापस 0;
	हाल 0x8:
		pr_info("parport_pc: ITE8874 found (2S)\n");
		release_region(पूर्णांकa_addr[i], 32);
		वापस 0;
	शेष:
		pr_info("parport_pc: unknown ITE887x\n");
		pr_info("parport_pc: please mail 'lspci -nvv' output to Rich.Liu@ite.com.tw\n");
		release_region(पूर्णांकa_addr[i], 32);
		वापस 0;
	पूर्ण

	pci_पढ़ो_config_byte(pdev, 0x3c, &ite8872_irq);
	pci_पढ़ो_config_dword(pdev, 0x1c, &ite8872_lpt);
	ite8872_lpt &= 0x0000ff00;
	pci_पढ़ो_config_dword(pdev, 0x20, &ite8872_lpthi);
	ite8872_lpthi &= 0x0000ff00;
	pci_ग_लिखो_config_dword(pdev, 0x6c, 0xe3000000 | ite8872_lpt);
	pci_ग_लिखो_config_dword(pdev, 0x70, 0xe3000000 | ite8872_lpthi);
	pci_ग_लिखो_config_dword(pdev, 0x80, (ite8872_lpthi<<16) | ite8872_lpt);
	/* SET SPP&EPP , Parallel Port NO DMA , Enable All Function */
	/* SET Parallel IRQ */
	pci_ग_लिखो_config_dword(pdev, 0x9c,
				ite8872set | (ite8872_irq * 0x11111));

	pr_debug("ITE887x: The IRQ is %d\n", ite8872_irq);
	pr_debug("ITE887x: The PARALLEL I/O port is 0x%x\n", ite8872_lpt);
	pr_debug("ITE887x: The PARALLEL I/O porthi is 0x%x\n", ite8872_lpthi);

	/* Let the user (or शेषs) steer us away from पूर्णांकerrupts */
	irq = ite8872_irq;
	अगर (स्वतःirq != PARPORT_IRQ_AUTO)
		irq = PARPORT_IRQ_NONE;

	/*
	 * Release the resource so that parport_pc_probe_port can get it.
	 */
	release_region(पूर्णांकa_addr[i], 32);
	अगर (parport_pc_probe_port(ite8872_lpt, ite8872_lpthi,
				   irq, PARPORT_DMA_NONE, &pdev->dev, 0)) अणु
		pr_info("parport_pc: ITE 8872 parallel port: io=0x%X",
			ite8872_lpt);
		अगर (irq != PARPORT_IRQ_NONE)
			pr_cont(", irq=%d", irq);
		pr_cont("\n");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* VIA 8231 support by Pavel Fedin <sonic_amiga@rambler.ru>
   based on VIA 686a support code by Jeff Garzik <jgarzik@pobox.com> */
अटल पूर्णांक parport_init_mode;

/* Data क्रम two known VIA chips */
अटल काष्ठा parport_pc_via_data via_686a_data = अणु
	0x51,
	0x50,
	0x85,
	0x02,
	0xE2,
	0xF0,
	0xE6
पूर्ण;
अटल काष्ठा parport_pc_via_data via_8231_data = अणु
	0x45,
	0x44,
	0x50,
	0x04,
	0xF2,
	0xFA,
	0xF6
पूर्ण;

अटल पूर्णांक sio_via_probe(काष्ठा pci_dev *pdev, पूर्णांक स्वतःirq, पूर्णांक स्वतःdma,
			 स्थिर काष्ठा parport_pc_via_data *via)
अणु
	u8 पंचांगp, पंचांगp2, siofunc;
	u8 ppcontrol = 0;
	पूर्णांक dma, irq;
	अचिन्हित port1, port2;
	अचिन्हित have_epp = 0;

	prपूर्णांकk(KERN_DEBUG "parport_pc: VIA 686A/8231 detected\n");

	चयन (parport_init_mode) अणु
	हाल 1:
		prपूर्णांकk(KERN_DEBUG "parport_pc: setting SPP mode\n");
		siofunc = VIA_FUNCTION_PARPORT_SPP;
		अवरोध;
	हाल 2:
		prपूर्णांकk(KERN_DEBUG "parport_pc: setting PS/2 mode\n");
		siofunc = VIA_FUNCTION_PARPORT_SPP;
		ppcontrol = VIA_PARPORT_BIसूची;
		अवरोध;
	हाल 3:
		prपूर्णांकk(KERN_DEBUG "parport_pc: setting EPP mode\n");
		siofunc = VIA_FUNCTION_PARPORT_EPP;
		ppcontrol = VIA_PARPORT_BIसूची;
		have_epp = 1;
		अवरोध;
	हाल 4:
		prपूर्णांकk(KERN_DEBUG "parport_pc: setting ECP mode\n");
		siofunc = VIA_FUNCTION_PARPORT_ECP;
		ppcontrol = VIA_PARPORT_BIसूची;
		अवरोध;
	हाल 5:
		prपूर्णांकk(KERN_DEBUG "parport_pc: setting EPP+ECP mode\n");
		siofunc = VIA_FUNCTION_PARPORT_ECP;
		ppcontrol = VIA_PARPORT_BIसूची|VIA_PARPORT_ECPEPP;
		have_epp = 1;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_DEBUG "parport_pc: probing current configuration\n");
		siofunc = VIA_FUNCTION_PROBE;
		अवरोध;
	पूर्ण
	/*
	 * unlock super i/o configuration
	 */
	pci_पढ़ो_config_byte(pdev, via->via_pci_superio_config_reg, &पंचांगp);
	पंचांगp |= via->via_pci_superio_config_data;
	pci_ग_लिखो_config_byte(pdev, via->via_pci_superio_config_reg, पंचांगp);

	/* Bits 1-0: Parallel Port Mode / Enable */
	outb(via->viacfg_function, VIA_CONFIG_INDEX);
	पंचांगp = inb(VIA_CONFIG_DATA);
	/* Bit 5: EPP+ECP enable; bit 7: PS/2 bidirectional port enable */
	outb(via->viacfg_parport_control, VIA_CONFIG_INDEX);
	पंचांगp2 = inb(VIA_CONFIG_DATA);
	अगर (siofunc == VIA_FUNCTION_PROBE) अणु
		siofunc = पंचांगp & VIA_FUNCTION_PARPORT_DISABLE;
		ppcontrol = पंचांगp2;
	पूर्ण अन्यथा अणु
		पंचांगp &= ~VIA_FUNCTION_PARPORT_DISABLE;
		पंचांगp |= siofunc;
		outb(via->viacfg_function, VIA_CONFIG_INDEX);
		outb(पंचांगp, VIA_CONFIG_DATA);
		पंचांगp2 &= ~(VIA_PARPORT_BIसूची|VIA_PARPORT_ECPEPP);
		पंचांगp2 |= ppcontrol;
		outb(via->viacfg_parport_control, VIA_CONFIG_INDEX);
		outb(पंचांगp2, VIA_CONFIG_DATA);
	पूर्ण

	/* Parallel Port I/O Base Address, bits 9-2 */
	outb(via->viacfg_parport_base, VIA_CONFIG_INDEX);
	port1 = inb(VIA_CONFIG_DATA) << 2;

	prपूर्णांकk(KERN_DEBUG "parport_pc: Current parallel port base: 0x%X\n",
	       port1);
	अगर (port1 == 0x3BC && have_epp) अणु
		outb(via->viacfg_parport_base, VIA_CONFIG_INDEX);
		outb((0x378 >> 2), VIA_CONFIG_DATA);
		prपूर्णांकk(KERN_DEBUG "parport_pc: Parallel port base changed to 0x378\n");
		port1 = 0x378;
	पूर्ण

	/*
	 * lock super i/o configuration
	 */
	pci_पढ़ो_config_byte(pdev, via->via_pci_superio_config_reg, &पंचांगp);
	पंचांगp &= ~via->via_pci_superio_config_data;
	pci_ग_लिखो_config_byte(pdev, via->via_pci_superio_config_reg, पंचांगp);

	अगर (siofunc == VIA_FUNCTION_PARPORT_DISABLE) अणु
		pr_info("parport_pc: VIA parallel port disabled in BIOS\n");
		वापस 0;
	पूर्ण

	/* Bits 7-4: PnP Routing क्रम Parallel Port IRQ */
	pci_पढ़ो_config_byte(pdev, via->via_pci_parport_irq_reg, &पंचांगp);
	irq = ((पंचांगp & VIA_IRQCONTROL_PARALLEL) >> 4);

	अगर (siofunc == VIA_FUNCTION_PARPORT_ECP) अणु
		/* Bits 3-2: PnP Routing क्रम Parallel Port DMA */
		pci_पढ़ो_config_byte(pdev, via->via_pci_parport_dma_reg, &पंचांगp);
		dma = ((पंचांगp & VIA_DMACONTROL_PARALLEL) >> 2);
	पूर्ण अन्यथा
		/* अगर ECP not enabled, DMA is not enabled, assumed
		   bogus 'dma' value */
		dma = PARPORT_DMA_NONE;

	/* Let the user (or शेषs) steer us away from पूर्णांकerrupts and DMA */
	अगर (स्वतःirq == PARPORT_IRQ_NONE) अणु
		irq = PARPORT_IRQ_NONE;
		dma = PARPORT_DMA_NONE;
	पूर्ण
	अगर (स्वतःdma == PARPORT_DMA_NONE)
		dma = PARPORT_DMA_NONE;

	चयन (port1) अणु
	हाल 0x3bc:
		port2 = 0x7bc; अवरोध;
	हाल 0x378:
		port2 = 0x778; अवरोध;
	हाल 0x278:
		port2 = 0x678; अवरोध;
	शेष:
		pr_info("parport_pc: Weird VIA parport base 0x%X, ignoring\n",
			port1);
		वापस 0;
	पूर्ण

	/* filter bogus IRQs */
	चयन (irq) अणु
	हाल 0:
	हाल 2:
	हाल 8:
	हाल 13:
		irq = PARPORT_IRQ_NONE;
		अवरोध;

	शेष: /* करो nothing */
		अवरोध;
	पूर्ण

	/* finally, करो the probe with values obtained */
	अगर (parport_pc_probe_port(port1, port2, irq, dma, &pdev->dev, 0)) अणु
		pr_info("parport_pc: VIA parallel port: io=0x%X", port1);
		अगर (irq != PARPORT_IRQ_NONE)
			pr_cont(", irq=%d", irq);
		अगर (dma != PARPORT_DMA_NONE)
			pr_cont(", dma=%d", dma);
		pr_cont("\n");
		वापस 1;
	पूर्ण

	pr_warn("parport_pc: Strange, can't probe VIA parallel port: io=0x%X, irq=%d, dma=%d\n",
		port1, irq, dma);
	वापस 0;
पूर्ण


क्रमागत parport_pc_sio_types अणु
	sio_via_686a = 0,   /* Via VT82C686A motherboard Super I/O */
	sio_via_8231,	    /* Via VT8231 south bridge पूर्णांकegrated Super IO */
	sio_ite_8872,
	last_sio
पूर्ण;

/* each element directly indexed from क्रमागत list, above */
अटल काष्ठा parport_pc_superio अणु
	पूर्णांक (*probe) (काष्ठा pci_dev *pdev, पूर्णांक स्वतःirq, पूर्णांक स्वतःdma,
		      स्थिर काष्ठा parport_pc_via_data *via);
	स्थिर काष्ठा parport_pc_via_data *via;
पूर्ण parport_pc_superio_info[] = अणु
	अणु sio_via_probe, &via_686a_data, पूर्ण,
	अणु sio_via_probe, &via_8231_data, पूर्ण,
	अणु sio_ite_8872_probe, शून्य, पूर्ण,
पूर्ण;

क्रमागत parport_pc_pci_cards अणु
	siig_1p_10x = last_sio,
	siig_2p_10x,
	siig_1p_20x,
	siig_2p_20x,
	lava_parallel,
	lava_parallel_dual_a,
	lava_parallel_dual_b,
	boca_ioppar,
	plx_9050,
	समयdia_4006a,
	समयdia_4014,
	समयdia_4008a,
	समयdia_4018,
	समयdia_9018a,
	syba_2p_epp,
	syba_1p_ecp,
	titan_010l,
	avlab_1p,
	avlab_2p,
	oxsemi_952,
	oxsemi_954,
	oxsemi_840,
	oxsemi_pcie_pport,
	aks_0100,
	mobility_pp,
	neपंचांगos_9705,
	neपंचांगos_9715,
	neपंचांगos_9755,
	neपंचांगos_9805,
	neपंचांगos_9815,
	neपंचांगos_9901,
	neपंचांगos_9865,
	quatech_sppxp100,
	wch_ch382l,
पूर्ण;


/* each element directly indexed from क्रमागत list, above
 * (but offset by last_sio) */
अटल काष्ठा parport_pc_pci अणु
	पूर्णांक numports;
	काष्ठा अणु /* BAR (base address रेजिस्टरs) numbers in the config
		    space header */
		पूर्णांक lo;
		पूर्णांक hi;
		/* -1 अगर not there, >6 क्रम offset-method (max BAR is 6) */
	पूर्ण addr[4];

	/* If set, this is called immediately after pci_enable_device.
	 * If it वापसs non-zero, no probing will take place and the
	 * ports will not be used. */
	पूर्णांक (*preinit_hook) (काष्ठा pci_dev *pdev, पूर्णांक स्वतःirq, पूर्णांक स्वतःdma);

	/* If set, this is called after probing क्रम ports.  If 'failed'
	 * is non-zero we couldn't use any of the ports. */
	व्योम (*postinit_hook) (काष्ठा pci_dev *pdev, पूर्णांक failed);
पूर्ण cards[] = अणु
	/* siig_1p_10x */		अणु 1, अणु अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* siig_2p_10x */		अणु 2, अणु अणु 2, 3 पूर्ण, अणु 4, 5 पूर्ण, पूर्ण पूर्ण,
	/* siig_1p_20x */		अणु 1, अणु अणु 0, 1 पूर्ण, पूर्ण पूर्ण,
	/* siig_2p_20x */		अणु 2, अणु अणु 0, 1 पूर्ण, अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* lava_parallel */		अणु 1, अणु अणु 0, -1 पूर्ण, पूर्ण पूर्ण,
	/* lava_parallel_dual_a */	अणु 1, अणु अणु 0, -1 पूर्ण, पूर्ण पूर्ण,
	/* lava_parallel_dual_b */	अणु 1, अणु अणु 0, -1 पूर्ण, पूर्ण पूर्ण,
	/* boca_ioppar */		अणु 1, अणु अणु 0, -1 पूर्ण, पूर्ण पूर्ण,
	/* plx_9050 */			अणु 2, अणु अणु 4, -1 पूर्ण, अणु 5, -1 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4006a */             अणु 1, अणु अणु 0, -1 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4014  */             अणु 2, अणु अणु 0, -1 पूर्ण, अणु 2, -1 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4008a */             अणु 1, अणु अणु 0, 1 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4018  */             अणु 2, अणु अणु 0, 1 पूर्ण, अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_9018a */             अणु 2, अणु अणु 0, 1 पूर्ण, अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
					/* SYBA uses fixed offsets in
					   a 1K io winकरोw */
	/* syba_2p_epp AP138B */	अणु 2, अणु अणु 0, 0x078 पूर्ण, अणु 0, 0x178 पूर्ण, पूर्ण पूर्ण,
	/* syba_1p_ecp W83787 */	अणु 1, अणु अणु 0, 0x078 पूर्ण, पूर्ण पूर्ण,
	/* titan_010l */		अणु 1, अणु अणु 3, -1 पूर्ण, पूर्ण पूर्ण,
	/* avlab_1p		*/	अणु 1, अणु अणु 0, 1पूर्ण, पूर्ण पूर्ण,
	/* avlab_2p		*/	अणु 2, अणु अणु 0, 1पूर्ण, अणु 2, 3 पूर्ण,पूर्ण पूर्ण,
	/* The Oxक्रमd Semi cards are unusual: 954 करोesn't support ECP,
	 * and 840 locks up अगर you ग_लिखो 1 to bit 2! */
	/* oxsemi_952 */		अणु 1, अणु अणु 0, 1 पूर्ण, पूर्ण पूर्ण,
	/* oxsemi_954 */		अणु 1, अणु अणु 0, -1 पूर्ण, पूर्ण पूर्ण,
	/* oxsemi_840 */		अणु 1, अणु अणु 0, 1 पूर्ण, पूर्ण पूर्ण,
	/* oxsemi_pcie_pport */		अणु 1, अणु अणु 0, 1 पूर्ण, पूर्ण पूर्ण,
	/* aks_0100 */                  अणु 1, अणु अणु 0, -1 पूर्ण, पूर्ण पूर्ण,
	/* mobility_pp */		अणु 1, अणु अणु 0, 1 पूर्ण, पूर्ण पूर्ण,

	/* The neपंचांगos entries below are untested */
	/* neपंचांगos_9705 */               अणु 1, अणु अणु 0, -1 पूर्ण, पूर्ण पूर्ण,
	/* neपंचांगos_9715 */               अणु 2, अणु अणु 0, 1 पूर्ण, अणु 2, 3 पूर्ण,पूर्ण पूर्ण,
	/* neपंचांगos_9755 */               अणु 2, अणु अणु 0, 1 पूर्ण, अणु 2, 3 पूर्ण,पूर्ण पूर्ण,
	/* neपंचांगos_9805 */		अणु 1, अणु अणु 0, 1 पूर्ण, पूर्ण पूर्ण,
	/* neपंचांगos_9815 */		अणु 2, अणु अणु 0, 1 पूर्ण, अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* neपंचांगos_9901 */               अणु 1, अणु अणु 0, -1 पूर्ण, पूर्ण पूर्ण,
	/* neपंचांगos_9865 */               अणु 1, अणु अणु 0, -1 पूर्ण, पूर्ण पूर्ण,
	/* quatech_sppxp100 */		अणु 1, अणु अणु 0, 1 पूर्ण, पूर्ण पूर्ण,
	/* wch_ch382l */		अणु 1, अणु अणु 2, -1 पूर्ण, पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id parport_pc_pci_tbl[] = अणु
	/* Super-IO onboard chips */
	अणु 0x1106, 0x0686, PCI_ANY_ID, PCI_ANY_ID, 0, 0, sio_via_686a पूर्ण,
	अणु 0x1106, 0x8231, PCI_ANY_ID, PCI_ANY_ID, 0, 0, sio_via_8231 पूर्ण,
	अणु PCI_VENDOR_ID_ITE, PCI_DEVICE_ID_ITE_8872,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, sio_ite_8872 पूर्ण,

	/* PCI cards */
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_1P_10x,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_1p_10x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2P_10x,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2p_10x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_1P_20x,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_1p_20x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2P_20x,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2p_20x पूर्ण,
	अणु PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_PARALLEL,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, lava_parallel पूर्ण,
	अणु PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_DUAL_PAR_A,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, lava_parallel_dual_a पूर्ण,
	अणु PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_DUAL_PAR_B,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, lava_parallel_dual_b पूर्ण,
	अणु PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_BOCA_IOPPAR,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, boca_ioppar पूर्ण,
	अणु PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
	  PCI_SUBVENDOR_ID_EXSYS, PCI_SUBDEVICE_ID_EXSYS_4014, 0, 0, plx_9050 पूर्ण,
	/* PCI_VENDOR_ID_TIMEDIA/SUNIX has many dअगरfering cards ...*/
	अणु 0x1409, 0x7268, 0x1409, 0x0101, 0, 0, समयdia_4006a पूर्ण,
	अणु 0x1409, 0x7268, 0x1409, 0x0102, 0, 0, समयdia_4014 पूर्ण,
	अणु 0x1409, 0x7268, 0x1409, 0x0103, 0, 0, समयdia_4008a पूर्ण,
	अणु 0x1409, 0x7268, 0x1409, 0x0104, 0, 0, समयdia_4018 पूर्ण,
	अणु 0x1409, 0x7268, 0x1409, 0x9018, 0, 0, समयdia_9018a पूर्ण,
	अणु PCI_VENDOR_ID_SYBA, PCI_DEVICE_ID_SYBA_2P_EPP,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, syba_2p_epp पूर्ण,
	अणु PCI_VENDOR_ID_SYBA, PCI_DEVICE_ID_SYBA_1P_ECP,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, syba_1p_ecp पूर्ण,
	अणु PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_010L,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, titan_010l पूर्ण,
	/* PCI_VENDOR_ID_AVLAB/Intek21 has another bunch of cards ...*/
	/* AFAVLAB_TK9902 */
	अणु 0x14db, 0x2120, PCI_ANY_ID, PCI_ANY_ID, 0, 0, avlab_1pपूर्ण,
	अणु 0x14db, 0x2121, PCI_ANY_ID, PCI_ANY_ID, 0, 0, avlab_2pपूर्ण,
	अणु PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_16PCI952PP,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_952 पूर्ण,
	अणु PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_16PCI954PP,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_954 पूर्ण,
	अणु PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_12PCI840,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_840 पूर्ण,
	अणु PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe840,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_pport पूर्ण,
	अणु PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe840_G,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_pport पूर्ण,
	अणु PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe952_0,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_pport पूर्ण,
	अणु PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe952_0_G,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_pport पूर्ण,
	अणु PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe952_1,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_pport पूर्ण,
	अणु PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe952_1_G,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_pport पूर्ण,
	अणु PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe952_1_U,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_pport पूर्ण,
	अणु PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe952_1_GU,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_pport पूर्ण,
	अणु PCI_VENDOR_ID_AKS, PCI_DEVICE_ID_AKS_ALADDINCARD,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, aks_0100 पूर्ण,
	अणु 0x14f2, 0x0121, PCI_ANY_ID, PCI_ANY_ID, 0, 0, mobility_pp पूर्ण,
	/* NetMos communication controllers */
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9705,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, neपंचांगos_9705 पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9715,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, neपंचांगos_9715 पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9755,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, neपंचांगos_9755 पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9805,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, neपंचांगos_9805 पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9815,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, neपंचांगos_9815 पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9901,
	  0xA000, 0x2000, 0, 0, neपंचांगos_9901 पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9865,
	  0xA000, 0x1000, 0, 0, neपंचांगos_9865 पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9865,
	  0xA000, 0x2000, 0, 0, neपंचांगos_9865 पूर्ण,
	/* Quatech SPPXP-100 Parallel port PCI ExpressCard */
	अणु PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_SPPXP_100,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, quatech_sppxp100 पूर्ण,
	/* WCH CH382L PCI-E single parallel port card */
	अणु 0x1c00, 0x3050, 0x1c00, 0x3050, 0, 0, wch_ch382l पूर्ण,
	अणु 0, पूर्ण /* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, parport_pc_pci_tbl);

काष्ठा pci_parport_data अणु
	पूर्णांक num;
	काष्ठा parport *ports[2];
पूर्ण;

अटल पूर्णांक parport_pc_pci_probe(काष्ठा pci_dev *dev,
					   स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err, count, n, i = id->driver_data;
	काष्ठा pci_parport_data *data;

	अगर (i < last_sio)
		/* This is an onboard Super-IO and has alपढ़ोy been probed */
		वापस 0;

	/* This is a PCI card */
	i -= last_sio;
	count = 0;
	err = pci_enable_device(dev);
	अगर (err)
		वापस err;

	data = kदो_स्मृति(माप(काष्ठा pci_parport_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (cards[i].preinit_hook &&
	    cards[i].preinit_hook(dev, PARPORT_IRQ_NONE, PARPORT_DMA_NONE)) अणु
		kमुक्त(data);
		वापस -ENODEV;
	पूर्ण

	क्रम (n = 0; n < cards[i].numports; n++) अणु
		पूर्णांक lo = cards[i].addr[n].lo;
		पूर्णांक hi = cards[i].addr[n].hi;
		पूर्णांक irq;
		अचिन्हित दीर्घ io_lo, io_hi;
		io_lo = pci_resource_start(dev, lo);
		io_hi = 0;
		अगर ((hi >= 0) && (hi <= 6))
			io_hi = pci_resource_start(dev, hi);
		अन्यथा अगर (hi > 6)
			io_lo += hi; /* Reपूर्णांकerpret the meaning of
					"hi" as an offset (see SYBA
					def.) */
		/* TODO: test अगर sharing पूर्णांकerrupts works */
		irq = dev->irq;
		अगर (irq == IRQ_NONE) अणु
			prपूर्णांकk(KERN_DEBUG "PCI parallel port detected: %04x:%04x, I/O at %#lx(%#lx)\n",
			       id->venकरोr, id->device, io_lo, io_hi);
			irq = PARPORT_IRQ_NONE;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_DEBUG "PCI parallel port detected: %04x:%04x, I/O at %#lx(%#lx), IRQ %d\n",
			       id->venकरोr, id->device, io_lo, io_hi, irq);
		पूर्ण
		data->ports[count] =
			parport_pc_probe_port(io_lo, io_hi, irq,
					       PARPORT_DMA_NONE, &dev->dev,
					       IRQF_SHARED);
		अगर (data->ports[count])
			count++;
	पूर्ण

	data->num = count;

	अगर (cards[i].postinit_hook)
		cards[i].postinit_hook(dev, count == 0);

	अगर (count) अणु
		pci_set_drvdata(dev, data);
		वापस 0;
	पूर्ण

	kमुक्त(data);

	वापस -ENODEV;
पूर्ण

अटल व्योम parport_pc_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_parport_data *data = pci_get_drvdata(dev);
	पूर्णांक i;

	अगर (data) अणु
		क्रम (i = data->num - 1; i >= 0; i--)
			parport_pc_unरेजिस्टर_port(data->ports[i]);

		kमुक्त(data);
	पूर्ण
पूर्ण

अटल काष्ठा pci_driver parport_pc_pci_driver = अणु
	.name		= "parport_pc",
	.id_table	= parport_pc_pci_tbl,
	.probe		= parport_pc_pci_probe,
	.हटाओ		= parport_pc_pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init parport_pc_init_superio(पूर्णांक स्वतःirq, पूर्णांक स्वतःdma)
अणु
	स्थिर काष्ठा pci_device_id *id;
	काष्ठा pci_dev *pdev = शून्य;
	पूर्णांक ret = 0;

	क्रम_each_pci_dev(pdev) अणु
		id = pci_match_id(parport_pc_pci_tbl, pdev);
		अगर (id == शून्य || id->driver_data >= last_sio)
			जारी;

		अगर (parport_pc_superio_info[id->driver_data].probe(
			pdev, स्वतःirq, स्वतःdma,
			parport_pc_superio_info[id->driver_data].via)) अणु
			ret++;
		पूर्ण
	पूर्ण

	वापस ret; /* number of devices found */
पूर्ण
#अन्यथा
अटल काष्ठा pci_driver parport_pc_pci_driver;
अटल पूर्णांक __init parport_pc_init_superio(पूर्णांक स्वतःirq, पूर्णांक स्वतःdma)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

#अगर_घोषित CONFIG_PNP

अटल स्थिर काष्ठा pnp_device_id parport_pc_pnp_tbl[] = अणु
	/* Standard LPT Prपूर्णांकer Port */
	अणु.id = "PNP0400", .driver_data = 0पूर्ण,
	/* ECP Prपूर्णांकer Port */
	अणु.id = "PNP0401", .driver_data = 0पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp, parport_pc_pnp_tbl);

अटल पूर्णांक parport_pc_pnp_probe(काष्ठा pnp_dev *dev,
						स्थिर काष्ठा pnp_device_id *id)
अणु
	काष्ठा parport *pdata;
	अचिन्हित दीर्घ io_lo, io_hi;
	पूर्णांक dma, irq;

	अगर (pnp_port_valid(dev, 0) &&
		!(pnp_port_flags(dev, 0) & IORESOURCE_DISABLED)) अणु
		io_lo = pnp_port_start(dev, 0);
	पूर्ण अन्यथा
		वापस -EINVAL;

	अगर (pnp_port_valid(dev, 1) &&
		!(pnp_port_flags(dev, 1) & IORESOURCE_DISABLED)) अणु
		io_hi = pnp_port_start(dev, 1);
	पूर्ण अन्यथा
		io_hi = 0;

	अगर (pnp_irq_valid(dev, 0) &&
		!(pnp_irq_flags(dev, 0) & IORESOURCE_DISABLED)) अणु
		irq = pnp_irq(dev, 0);
	पूर्ण अन्यथा
		irq = PARPORT_IRQ_NONE;

	अगर (pnp_dma_valid(dev, 0) &&
		!(pnp_dma_flags(dev, 0) & IORESOURCE_DISABLED)) अणु
		dma = pnp_dma(dev, 0);
	पूर्ण अन्यथा
		dma = PARPORT_DMA_NONE;

	dev_info(&dev->dev, "reported by %s\n", dev->protocol->name);
	pdata = parport_pc_probe_port(io_lo, io_hi, irq, dma, &dev->dev, 0);
	अगर (pdata == शून्य)
		वापस -ENODEV;

	pnp_set_drvdata(dev, pdata);
	वापस 0;
पूर्ण

अटल व्योम parport_pc_pnp_हटाओ(काष्ठा pnp_dev *dev)
अणु
	काष्ठा parport *pdata = (काष्ठा parport *)pnp_get_drvdata(dev);
	अगर (!pdata)
		वापस;

	parport_pc_unरेजिस्टर_port(pdata);
पूर्ण

/* we only need the pnp layer to activate the device, at least क्रम now */
अटल काष्ठा pnp_driver parport_pc_pnp_driver = अणु
	.name		= "parport_pc",
	.id_table	= parport_pc_pnp_tbl,
	.probe		= parport_pc_pnp_probe,
	.हटाओ		= parport_pc_pnp_हटाओ,
पूर्ण;

#अन्यथा
अटल काष्ठा pnp_driver parport_pc_pnp_driver;
#पूर्ण_अगर /* CONFIG_PNP */

अटल पूर्णांक parport_pc_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	/* Always succeed, the actual probing is करोne in
	 * parport_pc_probe_port(). */
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver parport_pc_platक्रमm_driver = अणु
	.driver = अणु
		.name	= "parport_pc",
	पूर्ण,
	.probe		= parport_pc_platक्रमm_probe,
पूर्ण;

/* This is called by parport_pc_find_nonpci_ports (in यंत्र/parport.h) */
अटल पूर्णांक __attribute__((unused))
parport_pc_find_isa_ports(पूर्णांक स्वतःirq, पूर्णांक स्वतःdma)
अणु
	पूर्णांक count = 0;

	अगर (parport_pc_probe_port(0x3bc, 0x7bc, स्वतःirq, स्वतःdma, शून्य, 0))
		count++;
	अगर (parport_pc_probe_port(0x378, 0x778, स्वतःirq, स्वतःdma, शून्य, 0))
		count++;
	अगर (parport_pc_probe_port(0x278, 0x678, स्वतःirq, स्वतःdma, शून्य, 0))
		count++;

	वापस count;
पूर्ण

/* This function is called by parport_pc_init अगर the user didn't
 * specअगरy any ports to probe.  Its job is to find some ports.  Order
 * is important here -- we want ISA ports to be रेजिस्टरed first,
 * followed by PCI cards (क्रम least surprise), but beक्रमe that we want
 * to करो chipset-specअगरic tests क्रम some onboard ports that we know
 * about.
 *
 * स्वतःirq is PARPORT_IRQ_NONE, PARPORT_IRQ_AUTO, or PARPORT_IRQ_PROBEONLY
 * स्वतःdma is PARPORT_DMA_NONE or PARPORT_DMA_AUTO
 */
अटल व्योम __init parport_pc_find_ports(पूर्णांक स्वतःirq, पूर्णांक स्वतःdma)
अणु
	पूर्णांक count = 0, err;

#अगर_घोषित CONFIG_PARPORT_PC_SUPERIO
	detect_and_report_it87();
	detect_and_report_winbond();
	detect_and_report_smsc();
#पूर्ण_अगर

	/* Onboard SuperIO chipsets that show themselves on the PCI bus. */
	count += parport_pc_init_superio(स्वतःirq, स्वतःdma);

	/* PnP ports, skip detection अगर SuperIO alपढ़ोy found them */
	अगर (!count) अणु
		err = pnp_रेजिस्टर_driver(&parport_pc_pnp_driver);
		अगर (!err)
			pnp_रेजिस्टरed_parport = 1;
	पूर्ण

	/* ISA ports and whatever (see यंत्र/parport.h). */
	parport_pc_find_nonpci_ports(स्वतःirq, स्वतःdma);

	err = pci_रेजिस्टर_driver(&parport_pc_pci_driver);
	अगर (!err)
		pci_रेजिस्टरed_parport = 1;
पूर्ण

/*
 *	Piles of crap below pretend to be a parser क्रम module and kernel
 *	parameters.  Say "thank you" to whoever had come up with that
 *	syntax and keep in mind that code below is a cleaned up version.
 */

अटल पूर्णांक __initdata io[PARPORT_PC_MAX_PORTS+1] = अणु
	[0 ... PARPORT_PC_MAX_PORTS] = 0
पूर्ण;
अटल पूर्णांक __initdata io_hi[PARPORT_PC_MAX_PORTS+1] = अणु
	[0 ... PARPORT_PC_MAX_PORTS] = PARPORT_IOHI_AUTO
पूर्ण;
अटल पूर्णांक __initdata dmaval[PARPORT_PC_MAX_PORTS] = अणु
	[0 ... PARPORT_PC_MAX_PORTS-1] = PARPORT_DMA_NONE
पूर्ण;
अटल पूर्णांक __initdata irqval[PARPORT_PC_MAX_PORTS] = अणु
	[0 ... PARPORT_PC_MAX_PORTS-1] = PARPORT_IRQ_PROBEONLY
पूर्ण;

अटल पूर्णांक __init parport_parse_param(स्थिर अक्षर *s, पूर्णांक *val,
				पूर्णांक स्वतःmatic, पूर्णांक none, पूर्णांक nofअगरo)
अणु
	अगर (!s)
		वापस 0;
	अगर (!म_भेदन(s, "auto", 4))
		*val = स्वतःmatic;
	अन्यथा अगर (!म_भेदन(s, "none", 4))
		*val = none;
	अन्यथा अगर (nofअगरo && !म_भेदन(s, "nofifo", 6))
		*val = nofअगरo;
	अन्यथा अणु
		अक्षर *ep;
		अचिन्हित दीर्घ r = simple_म_से_अदीर्घ(s, &ep, 0);
		अगर (ep != s)
			*val = r;
		अन्यथा अणु
			pr_err("parport: bad specifier `%s'\n", s);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init parport_parse_irq(स्थिर अक्षर *irqstr, पूर्णांक *val)
अणु
	वापस parport_parse_param(irqstr, val, PARPORT_IRQ_AUTO,
				     PARPORT_IRQ_NONE, 0);
पूर्ण

अटल पूर्णांक __init parport_parse_dma(स्थिर अक्षर *dmastr, पूर्णांक *val)
अणु
	वापस parport_parse_param(dmastr, val, PARPORT_DMA_AUTO,
				     PARPORT_DMA_NONE, PARPORT_DMA_NOFIFO);
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक __init parport_init_mode_setup(अक्षर *str)
अणु
	prपूर्णांकk(KERN_DEBUG "parport_pc.c: Specified parameter parport_init_mode=%s\n",
	       str);

	अगर (!म_भेद(str, "spp"))
		parport_init_mode = 1;
	अगर (!म_भेद(str, "ps2"))
		parport_init_mode = 2;
	अगर (!म_भेद(str, "epp"))
		parport_init_mode = 3;
	अगर (!म_भेद(str, "ecp"))
		parport_init_mode = 4;
	अगर (!म_भेद(str, "ecpepp"))
		parport_init_mode = 5;
	वापस 1;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित MODULE
अटल अक्षर *irq[PARPORT_PC_MAX_PORTS];
अटल अक्षर *dma[PARPORT_PC_MAX_PORTS];

MODULE_PARM_DESC(io, "Base I/O address (SPP regs)");
module_param_hw_array(io, पूर्णांक, ioport, शून्य, 0);
MODULE_PARM_DESC(io_hi, "Base I/O address (ECR)");
module_param_hw_array(io_hi, पूर्णांक, ioport, शून्य, 0);
MODULE_PARM_DESC(irq, "IRQ line");
module_param_hw_array(irq, अक्षरp, irq, शून्य, 0);
MODULE_PARM_DESC(dma, "DMA channel");
module_param_hw_array(dma, अक्षरp, dma, शून्य, 0);
#अगर defined(CONFIG_PARPORT_PC_SUPERIO) || \
       (defined(CONFIG_PARPORT_1284) && defined(CONFIG_PARPORT_PC_FIFO))
MODULE_PARM_DESC(verbose_probing, "Log chit-chat during initialisation");
module_param(verbose_probing, पूर्णांक, 0644);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI
अटल अक्षर *init_mode;
MODULE_PARM_DESC(init_mode,
	"Initialise mode for VIA VT8231 port (spp, ps2, epp, ecp or ecpepp)");
module_param(init_mode, अक्षरp, 0);
#पूर्ण_अगर

अटल पूर्णांक __init parse_parport_params(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक val;

#अगर_घोषित CONFIG_PCI
	अगर (init_mode)
		parport_init_mode_setup(init_mode);
#पूर्ण_अगर

	क्रम (i = 0; i < PARPORT_PC_MAX_PORTS && io[i]; i++) अणु
		अगर (parport_parse_irq(irq[i], &val))
			वापस 1;
		irqval[i] = val;
		अगर (parport_parse_dma(dma[i], &val))
			वापस 1;
		dmaval[i] = val;
	पूर्ण
	अगर (!io[0]) अणु
		/* The user can make us use any IRQs or DMAs we find. */
		अगर (irq[0] && !parport_parse_irq(irq[0], &val))
			चयन (val) अणु
			हाल PARPORT_IRQ_NONE:
			हाल PARPORT_IRQ_AUTO:
				irqval[0] = val;
				अवरोध;
			शेष:
				pr_warn("parport_pc: irq specified without base address.  Use 'io=' to specify one\n");
			पूर्ण

		अगर (dma[0] && !parport_parse_dma(dma[0], &val))
			चयन (val) अणु
			हाल PARPORT_DMA_NONE:
			हाल PARPORT_DMA_AUTO:
				dmaval[0] = val;
				अवरोध;
			शेष:
				pr_warn("parport_pc: dma specified without base address.  Use 'io=' to specify one\n");
			पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#अन्यथा

अटल पूर्णांक parport_setup_ptr __initdata;

/*
 * Acceptable parameters:
 *
 * parport=0
 * parport=स्वतः
 * parport=0xBASE[,IRQ[,DMA]]
 *
 * IRQ/DMA may be numeric or 'auto' or 'none'
 */
अटल पूर्णांक __init parport_setup(अक्षर *str)
अणु
	अक्षर *endptr;
	अक्षर *sep;
	पूर्णांक val;

	अगर (!str || !*str || (*str == '0' && !*(str+1))) अणु
		/* Disable parport अगर "parport=0" in cmdline */
		io[0] = PARPORT_DISABLE;
		वापस 1;
	पूर्ण

	अगर (!म_भेदन(str, "auto", 4)) अणु
		irqval[0] = PARPORT_IRQ_AUTO;
		dmaval[0] = PARPORT_DMA_AUTO;
		वापस 1;
	पूर्ण

	val = simple_म_से_अदीर्घ(str, &endptr, 0);
	अगर (endptr == str) अणु
		pr_warn("parport=%s not understood\n", str);
		वापस 1;
	पूर्ण

	अगर (parport_setup_ptr == PARPORT_PC_MAX_PORTS) अणु
		pr_err("parport=%s ignored, too many ports\n", str);
		वापस 1;
	पूर्ण

	io[parport_setup_ptr] = val;
	irqval[parport_setup_ptr] = PARPORT_IRQ_NONE;
	dmaval[parport_setup_ptr] = PARPORT_DMA_NONE;

	sep = म_अक्षर(str, ',');
	अगर (sep++) अणु
		अगर (parport_parse_irq(sep, &val))
			वापस 1;
		irqval[parport_setup_ptr] = val;
		sep = म_अक्षर(sep, ',');
		अगर (sep++) अणु
			अगर (parport_parse_dma(sep, &val))
				वापस 1;
			dmaval[parport_setup_ptr] = val;
		पूर्ण
	पूर्ण
	parport_setup_ptr++;
	वापस 1;
पूर्ण

अटल पूर्णांक __init parse_parport_params(व्योम)
अणु
	वापस io[0] == PARPORT_DISABLE;
पूर्ण

__setup("parport=", parport_setup);

/*
 * Acceptable parameters:
 *
 * parport_init_mode=[spp|ps2|epp|ecp|ecpepp]
 */
#अगर_घोषित CONFIG_PCI
__setup("parport_init_mode=", parport_init_mode_setup);
#पूर्ण_अगर
#पूर्ण_अगर

/* "Parser" ends here */

अटल पूर्णांक __init parport_pc_init(व्योम)
अणु
	पूर्णांक err;

	अगर (parse_parport_params())
		वापस -EINVAL;

	err = platक्रमm_driver_रेजिस्टर(&parport_pc_platक्रमm_driver);
	अगर (err)
		वापस err;

	अगर (io[0]) अणु
		पूर्णांक i;
		/* Only probe the ports we were given. */
		user_specअगरied = 1;
		क्रम (i = 0; i < PARPORT_PC_MAX_PORTS; i++) अणु
			अगर (!io[i])
				अवरोध;
			अगर (io_hi[i] == PARPORT_IOHI_AUTO)
				io_hi[i] = 0x400 + io[i];
			parport_pc_probe_port(io[i], io_hi[i],
					irqval[i], dmaval[i], शून्य, 0);
		पूर्ण
	पूर्ण अन्यथा
		parport_pc_find_ports(irqval[0], dmaval[0]);

	वापस 0;
पूर्ण

अटल व्योम __निकास parport_pc_निकास(व्योम)
अणु
	अगर (pci_रेजिस्टरed_parport)
		pci_unरेजिस्टर_driver(&parport_pc_pci_driver);
	अगर (pnp_रेजिस्टरed_parport)
		pnp_unरेजिस्टर_driver(&parport_pc_pnp_driver);
	platक्रमm_driver_unरेजिस्टर(&parport_pc_platक्रमm_driver);

	जबतक (!list_empty(&ports_list)) अणु
		काष्ठा parport_pc_निजी *priv;
		काष्ठा parport *port;
		काष्ठा device *dev;
		priv = list_entry(ports_list.next,
				  काष्ठा parport_pc_निजी, list);
		port = priv->port;
		dev = port->dev;
		parport_pc_unरेजिस्टर_port(port);
		अगर (dev && dev->bus == &platक्रमm_bus_type)
			platक्रमm_device_unरेजिस्टर(to_platक्रमm_device(dev));
	पूर्ण
पूर्ण

MODULE_AUTHOR("Phil Blundell, Tim Waugh, others");
MODULE_DESCRIPTION("PC-style parallel port driver");
MODULE_LICENSE("GPL");
module_init(parport_pc_init)
module_निकास(parport_pc_निकास)
