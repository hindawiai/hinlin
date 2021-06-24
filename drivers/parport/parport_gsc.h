<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Low-level parallel-support क्रम PC-style hardware पूर्णांकegrated in the
 *	LASI-Controller (on GSC-Bus) क्रम HP-PARISC Workstations
 *
 *	(C) 1999-2001 by Helge Deller <deller@gmx.de>
 *
 * based on parport_pc.c by
 * 	    Grant Guenther <grant@torque.net>
 * 	    Phil Blundell <Philip.Blundell@pobox.com>
 *          Tim Waugh <tim@cyberelk.demon.co.uk>
 *	    Jose Renau <renau@acm.org>
 *          David Campbell
 *          Andrea Arcangeli
 */

#अगर_अघोषित	__DRIVERS_PARPORT_PARPORT_GSC_H
#घोषणा	__DRIVERS_PARPORT_PARPORT_GSC_H

#समावेश <यंत्र/पन.स>
#समावेश <linux/delay.h>

#अघोषित	DEBUG_PARPORT	/* undefine क्रम production */
#घोषणा DELAY_TIME 	0

#अगर DELAY_TIME == 0
#घोषणा parport_पढ़ोb	gsc_पढ़ोb
#घोषणा parport_ग_लिखोb	gsc_ग_लिखोb
#अन्यथा
अटल __अंतरभूत__ अचिन्हित अक्षर parport_पढ़ोb( अचिन्हित दीर्घ port )
अणु
    udelay(DELAY_TIME);
    वापस gsc_पढ़ोb(port);
पूर्ण

अटल __अंतरभूत__ व्योम parport_ग_लिखोb( अचिन्हित अक्षर value, अचिन्हित दीर्घ port )
अणु
    gsc_ग_लिखोb(value,port);
    udelay(DELAY_TIME);
पूर्ण
#पूर्ण_अगर

/* --- रेजिस्टर definitions ------------------------------- */

#घोषणा EPPDATA(p)  ((p)->base    + 0x4)
#घोषणा EPPADDR(p)  ((p)->base    + 0x3)
#घोषणा CONTROL(p)  ((p)->base    + 0x2)
#घोषणा STATUS(p)   ((p)->base    + 0x1)
#घोषणा DATA(p)     ((p)->base    + 0x0)

काष्ठा parport_gsc_निजी अणु
	/* Contents of CTR. */
	अचिन्हित अक्षर ctr;

	/* Biपंचांगask of writable CTR bits. */
	अचिन्हित अक्षर ctr_writable;

	/* Number of bytes per portword. */
	पूर्णांक pword;

	/* Not used yet. */
	पूर्णांक पढ़ोIntrThreshold;
	पूर्णांक ग_लिखोIntrThreshold;

	/* buffer suitable क्रम DMA, अगर DMA enabled */
	अक्षर *dma_buf;
	dma_addr_t dma_handle;
	काष्ठा pci_dev *dev;
पूर्ण;

अटल अंतरभूत व्योम parport_gsc_ग_लिखो_data(काष्ठा parport *p, अचिन्हित अक्षर d)
अणु
#अगर_घोषित DEBUG_PARPORT
	prपूर्णांकk(KERN_DEBUG "%s(%p,0x%02x)\n", __func__, p, d);
#पूर्ण_अगर
	parport_ग_लिखोb(d, DATA(p));
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर parport_gsc_पढ़ो_data(काष्ठा parport *p)
अणु
	अचिन्हित अक्षर val = parport_पढ़ोb (DATA (p));
#अगर_घोषित DEBUG_PARPORT
	prपूर्णांकk(KERN_DEBUG "%s(%p) = 0x%02x\n", __func__, p, val);
#पूर्ण_अगर
	वापस val;
पूर्ण

/* __parport_gsc_frob_control dअगरfers from parport_gsc_frob_control in that
 * it करोesn't करो any extra masking. */
अटल अंतरभूत अचिन्हित अक्षर __parport_gsc_frob_control(काष्ठा parport *p,
							अचिन्हित अक्षर mask,
							अचिन्हित अक्षर val)
अणु
	काष्ठा parport_gsc_निजी *priv = p->physport->निजी_data;
	अचिन्हित अक्षर ctr = priv->ctr;
#अगर_घोषित DEBUG_PARPORT
	prपूर्णांकk(KERN_DEBUG "%s(%02x,%02x): %02x -> %02x\n",
	       __func__, mask, val,
	       ctr, ((ctr & ~mask) ^ val) & priv->ctr_writable);
#पूर्ण_अगर
	ctr = (ctr & ~mask) ^ val;
	ctr &= priv->ctr_writable; /* only ग_लिखो writable bits. */
	parport_ग_लिखोb (ctr, CONTROL (p));
	priv->ctr = ctr;	/* Update soft copy */
	वापस ctr;
पूर्ण

अटल अंतरभूत व्योम parport_gsc_data_reverse(काष्ठा parport *p)
अणु
	__parport_gsc_frob_control (p, 0x20, 0x20);
पूर्ण

अटल अंतरभूत व्योम parport_gsc_data_क्रमward(काष्ठा parport *p)
अणु
	__parport_gsc_frob_control (p, 0x20, 0x00);
पूर्ण

अटल अंतरभूत व्योम parport_gsc_ग_लिखो_control(काष्ठा parport *p,
						 अचिन्हित अक्षर d)
अणु
	स्थिर अचिन्हित अक्षर wm = (PARPORT_CONTROL_STROBE |
				  PARPORT_CONTROL_AUTOFD |
				  PARPORT_CONTROL_INIT |
				  PARPORT_CONTROL_SELECT);

	/* Take this out when drivers have adapted to newer पूर्णांकerface. */
	अगर (d & 0x20) अणु
		prपूर्णांकk(KERN_DEBUG "%s (%s): use data_reverse for this!\n",
		       p->name, p->cad->name);
		parport_gsc_data_reverse (p);
	पूर्ण

	__parport_gsc_frob_control (p, wm, d & wm);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर parport_gsc_पढ़ो_control(काष्ठा parport *p)
अणु
	स्थिर अचिन्हित अक्षर rm = (PARPORT_CONTROL_STROBE |
				  PARPORT_CONTROL_AUTOFD |
				  PARPORT_CONTROL_INIT |
				  PARPORT_CONTROL_SELECT);
	स्थिर काष्ठा parport_gsc_निजी *priv = p->physport->निजी_data;
	वापस priv->ctr & rm; /* Use soft copy */
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर parport_gsc_frob_control(काष्ठा parport *p,
							अचिन्हित अक्षर mask,
							अचिन्हित अक्षर val)
अणु
	स्थिर अचिन्हित अक्षर wm = (PARPORT_CONTROL_STROBE |
				  PARPORT_CONTROL_AUTOFD |
				  PARPORT_CONTROL_INIT |
				  PARPORT_CONTROL_SELECT);

	/* Take this out when drivers have adapted to newer पूर्णांकerface. */
	अगर (mask & 0x20) अणु
		prपूर्णांकk(KERN_DEBUG "%s (%s): use data_%s for this!\n",
		       p->name, p->cad->name,
		       (val & 0x20) ? "reverse" : "forward");
		अगर (val & 0x20)
			parport_gsc_data_reverse (p);
		अन्यथा
			parport_gsc_data_क्रमward (p);
	पूर्ण

	/* Restrict mask and val to control lines. */
	mask &= wm;
	val &= wm;

	वापस __parport_gsc_frob_control (p, mask, val);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर parport_gsc_पढ़ो_status(काष्ठा parport *p)
अणु
	वापस parport_पढ़ोb (STATUS(p));
पूर्ण

अटल अंतरभूत व्योम parport_gsc_disable_irq(काष्ठा parport *p)
अणु
	__parport_gsc_frob_control (p, 0x10, 0x00);
पूर्ण

अटल अंतरभूत व्योम parport_gsc_enable_irq(काष्ठा parport *p)
अणु
	__parport_gsc_frob_control (p, 0x10, 0x10);
पूर्ण

बाह्य व्योम parport_gsc_release_resources(काष्ठा parport *p);

बाह्य पूर्णांक parport_gsc_claim_resources(काष्ठा parport *p);

बाह्य व्योम parport_gsc_init_state(काष्ठा pardevice *, काष्ठा parport_state *s);

बाह्य व्योम parport_gsc_save_state(काष्ठा parport *p, काष्ठा parport_state *s);

बाह्य व्योम parport_gsc_restore_state(काष्ठा parport *p, काष्ठा parport_state *s);

बाह्य व्योम parport_gsc_inc_use_count(व्योम);

बाह्य व्योम parport_gsc_dec_use_count(व्योम);

बाह्य काष्ठा parport *parport_gsc_probe_port(अचिन्हित दीर्घ base,
						अचिन्हित दीर्घ base_hi,
						पूर्णांक irq, पूर्णांक dma,
						काष्ठा parisc_device *padev);

#पूर्ण_अगर	/* __DRIVERS_PARPORT_PARPORT_GSC_H */
