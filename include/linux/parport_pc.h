<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_PARPORT_PC_H
#घोषणा __LINUX_PARPORT_PC_H

#समावेश <यंत्र/पन.स>

/* --- रेजिस्टर definitions ------------------------------- */

#घोषणा ECONTROL(p) ((p)->base_hi + 0x2)
#घोषणा CONFIGB(p)  ((p)->base_hi + 0x1)
#घोषणा CONFIGA(p)  ((p)->base_hi + 0x0)
#घोषणा FIFO(p)     ((p)->base_hi + 0x0)
#घोषणा EPPDATA(p)  ((p)->base    + 0x4)
#घोषणा EPPADDR(p)  ((p)->base    + 0x3)
#घोषणा CONTROL(p)  ((p)->base    + 0x2)
#घोषणा STATUS(p)   ((p)->base    + 0x1)
#घोषणा DATA(p)     ((p)->base    + 0x0)

काष्ठा parport_pc_निजी अणु
	/* Contents of CTR. */
	अचिन्हित अक्षर ctr;

	/* Biपंचांगask of writable CTR bits. */
	अचिन्हित अक्षर ctr_writable;

	/* Whether or not there's an ECR. */
	पूर्णांक ecr;

	/* Number of PWords that FIFO will hold. */
	पूर्णांक fअगरo_depth;

	/* Number of bytes per portword. */
	पूर्णांक pword;

	/* Not used yet. */
	पूर्णांक पढ़ोIntrThreshold;
	पूर्णांक ग_लिखोIntrThreshold;

	/* buffer suitable क्रम DMA, अगर DMA enabled */
	अक्षर *dma_buf;
	dma_addr_t dma_handle;
	काष्ठा list_head list;
	काष्ठा parport *port;
पूर्ण;

काष्ठा parport_pc_via_data
अणु
	/* ISA PnP IRQ routing रेजिस्टर 1 */
	u8 via_pci_parport_irq_reg;
	/* ISA PnP DMA request routing रेजिस्टर */
	u8 via_pci_parport_dma_reg;
	/* Register and value to enable SuperIO configuration access */
	u8 via_pci_superio_config_reg;
	u8 via_pci_superio_config_data;
	/* SuperIO function रेजिस्टर number */
	u8 viacfg_function;
	/* parallel port control रेजिस्टर number */
	u8 viacfg_parport_control;
	/* Parallel port base address रेजिस्टर */
	u8 viacfg_parport_base;
पूर्ण;

अटल __अंतरभूत__ व्योम parport_pc_ग_लिखो_data(काष्ठा parport *p, अचिन्हित अक्षर d)
अणु
#अगर_घोषित DEBUG_PARPORT
	prपूर्णांकk (KERN_DEBUG "parport_pc_write_data(%p,0x%02x)\n", p, d);
#पूर्ण_अगर
	outb(d, DATA(p));
पूर्ण

अटल __अंतरभूत__ अचिन्हित अक्षर parport_pc_पढ़ो_data(काष्ठा parport *p)
अणु
	अचिन्हित अक्षर val = inb (DATA (p));
#अगर_घोषित DEBUG_PARPORT
	prपूर्णांकk (KERN_DEBUG "parport_pc_read_data(%p) = 0x%02x\n",
		p, val);
#पूर्ण_अगर
	वापस val;
पूर्ण

#अगर_घोषित DEBUG_PARPORT
अटल अंतरभूत व्योम dump_parport_state (अक्षर *str, काष्ठा parport *p)
अणु
	/* here's hoping that reading these ports won't side-effect anything underneath */
	अचिन्हित अक्षर ecr = inb (ECONTROL (p));
	अचिन्हित अक्षर dcr = inb (CONTROL (p));
	अचिन्हित अक्षर dsr = inb (STATUS (p));
	अटल स्थिर अक्षर *स्थिर ecr_modes[] = अणु"SPP", "PS2", "PPFIFO", "ECP", "xXx", "yYy", "TST", "CFG"पूर्ण;
	स्थिर काष्ठा parport_pc_निजी *priv = p->physport->निजी_data;
	पूर्णांक i;

	prपूर्णांकk (KERN_DEBUG "*** parport state (%s): ecr=[%s", str, ecr_modes[(ecr & 0xe0) >> 5]);
	अगर (ecr & 0x10) prपूर्णांकk (",nErrIntrEn");
	अगर (ecr & 0x08) prपूर्णांकk (",dmaEn");
	अगर (ecr & 0x04) prपूर्णांकk (",serviceIntr");
	अगर (ecr & 0x02) prपूर्णांकk (",f_full");
	अगर (ecr & 0x01) prपूर्णांकk (",f_empty");
	क्रम (i=0; i<2; i++) अणु
		prपूर्णांकk ("]  dcr(%s)=[", i ? "soft" : "hard");
		dcr = i ? priv->ctr : inb (CONTROL (p));
	
		अगर (dcr & 0x20) अणु
			prपूर्णांकk ("rev");
		पूर्ण अन्यथा अणु
			prपूर्णांकk ("fwd");
		पूर्ण
		अगर (dcr & 0x10) prपूर्णांकk (",ackIntEn");
		अगर (!(dcr & 0x08)) prपूर्णांकk (",N-SELECT-IN");
		अगर (dcr & 0x04) prपूर्णांकk (",N-INIT");
		अगर (!(dcr & 0x02)) prपूर्णांकk (",N-AUTOFD");
		अगर (!(dcr & 0x01)) prपूर्णांकk (",N-STROBE");
	पूर्ण
	prपूर्णांकk ("]  dsr=[");
	अगर (!(dsr & 0x80)) prपूर्णांकk ("BUSY");
	अगर (dsr & 0x40) prपूर्णांकk (",N-ACK");
	अगर (dsr & 0x20) prपूर्णांकk (",PERROR");
	अगर (dsr & 0x10) prपूर्णांकk (",SELECT");
	अगर (dsr & 0x08) prपूर्णांकk (",N-FAULT");
	prपूर्णांकk ("]\n");
	वापस;
पूर्ण
#अन्यथा	/* !DEBUG_PARPORT */
#घोषणा dump_parport_state(args...)
#पूर्ण_अगर	/* !DEBUG_PARPORT */

/* __parport_pc_frob_control dअगरfers from parport_pc_frob_control in that
 * it करोesn't करो any extra masking. */
अटल __अंतरभूत__ अचिन्हित अक्षर __parport_pc_frob_control (काष्ठा parport *p,
							   अचिन्हित अक्षर mask,
							   अचिन्हित अक्षर val)
अणु
	काष्ठा parport_pc_निजी *priv = p->physport->निजी_data;
	अचिन्हित अक्षर ctr = priv->ctr;
#अगर_घोषित DEBUG_PARPORT
	prपूर्णांकk (KERN_DEBUG
		"__parport_pc_frob_control(%02x,%02x): %02x -> %02x\n",
		mask, val, ctr, ((ctr & ~mask) ^ val) & priv->ctr_writable);
#पूर्ण_अगर
	ctr = (ctr & ~mask) ^ val;
	ctr &= priv->ctr_writable; /* only ग_लिखो writable bits. */
	outb (ctr, CONTROL (p));
	priv->ctr = ctr;	/* Update soft copy */
	वापस ctr;
पूर्ण

अटल __अंतरभूत__ व्योम parport_pc_data_reverse (काष्ठा parport *p)
अणु
	__parport_pc_frob_control (p, 0x20, 0x20);
पूर्ण

अटल __अंतरभूत__ व्योम parport_pc_data_क्रमward (काष्ठा parport *p)
अणु
	__parport_pc_frob_control (p, 0x20, 0x00);
पूर्ण

अटल __अंतरभूत__ व्योम parport_pc_ग_लिखो_control (काष्ठा parport *p,
						 अचिन्हित अक्षर d)
अणु
	स्थिर अचिन्हित अक्षर wm = (PARPORT_CONTROL_STROBE |
				  PARPORT_CONTROL_AUTOFD |
				  PARPORT_CONTROL_INIT |
				  PARPORT_CONTROL_SELECT);

	/* Take this out when drivers have adapted to newer पूर्णांकerface. */
	अगर (d & 0x20) अणु
		prपूर्णांकk (KERN_DEBUG "%s (%s): use data_reverse for this!\n",
			p->name, p->cad->name);
		parport_pc_data_reverse (p);
	पूर्ण

	__parport_pc_frob_control (p, wm, d & wm);
पूर्ण

अटल __अंतरभूत__ अचिन्हित अक्षर parport_pc_पढ़ो_control(काष्ठा parport *p)
अणु
	स्थिर अचिन्हित अक्षर rm = (PARPORT_CONTROL_STROBE |
				  PARPORT_CONTROL_AUTOFD |
				  PARPORT_CONTROL_INIT |
				  PARPORT_CONTROL_SELECT);
	स्थिर काष्ठा parport_pc_निजी *priv = p->physport->निजी_data;
	वापस priv->ctr & rm; /* Use soft copy */
पूर्ण

अटल __अंतरभूत__ अचिन्हित अक्षर parport_pc_frob_control (काष्ठा parport *p,
							 अचिन्हित अक्षर mask,
							 अचिन्हित अक्षर val)
अणु
	स्थिर अचिन्हित अक्षर wm = (PARPORT_CONTROL_STROBE |
				  PARPORT_CONTROL_AUTOFD |
				  PARPORT_CONTROL_INIT |
				  PARPORT_CONTROL_SELECT);

	/* Take this out when drivers have adapted to newer पूर्णांकerface. */
	अगर (mask & 0x20) अणु
		prपूर्णांकk (KERN_DEBUG "%s (%s): use data_%s for this!\n",
			p->name, p->cad->name,
			(val & 0x20) ? "reverse" : "forward");
		अगर (val & 0x20)
			parport_pc_data_reverse (p);
		अन्यथा
			parport_pc_data_क्रमward (p);
	पूर्ण

	/* Restrict mask and val to control lines. */
	mask &= wm;
	val &= wm;

	वापस __parport_pc_frob_control (p, mask, val);
पूर्ण

अटल __अंतरभूत__ अचिन्हित अक्षर parport_pc_पढ़ो_status(काष्ठा parport *p)
अणु
	वापस inb(STATUS(p));
पूर्ण


अटल __अंतरभूत__ व्योम parport_pc_disable_irq(काष्ठा parport *p)
अणु
	__parport_pc_frob_control (p, 0x10, 0x00);
पूर्ण

अटल __अंतरभूत__ व्योम parport_pc_enable_irq(काष्ठा parport *p)
अणु
	__parport_pc_frob_control (p, 0x10, 0x10);
पूर्ण

बाह्य व्योम parport_pc_release_resources(काष्ठा parport *p);

बाह्य पूर्णांक parport_pc_claim_resources(काष्ठा parport *p);

/* PCMCIA code will want to get us to look at a port.  Provide a mechanism. */
बाह्य काष्ठा parport *parport_pc_probe_port(अचिन्हित दीर्घ base,
					     अचिन्हित दीर्घ base_hi,
					     पूर्णांक irq, पूर्णांक dma,
					     काष्ठा device *dev,
					     पूर्णांक irqflags);
बाह्य व्योम parport_pc_unरेजिस्टर_port(काष्ठा parport *p);

#पूर्ण_अगर
