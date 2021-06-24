<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Low-level parallel port routines क्रम the Multअगरace 3 card
 *
 * Author: Joerg Dorchain <joerg@करोrchain.net>
 *
 * (C) The elitist m68k Users(TM)
 *
 * based on the existing parport_amiga and lp_mfc
 *
 *
 * From the MFC3 करोcumentation:
 * 
 * Miscellaneous PIA Details
 * -------------------------
 * 
 * 	The two खोलो-drain पूर्णांकerrupt outमाला_दो /IRQA and /IRQB are routed to
 * /INT2 of the Z2 bus.
 * 
 * 	The CPU data bus of the PIA (D0-D7) is connected to D8-D15 on the Z2
 * bus. This means that any PIA रेजिस्टरs are accessed at even addresses.
 * 
 * Centronics Pin Connections क्रम the PIA
 * --------------------------------------
 * 
 * 	The following table shows the connections between the PIA and the
 * Centronics पूर्णांकerface connector. These connections implement a single, but
 * very complete, Centronics type पूर्णांकerface. The Pin column gives the pin
 * numbers of the PIA. The Centronics pin numbers can be found in the section
 * "Parallel Connectors".
 * 
 * 
 *    Pin | PIA | Dir | Centronics Names
 * -------+-----+-----+---------------------------------------------------------
 *     19 | CB2 | --> | /STROBE (aka /DRDY)
 *  10-17 | PBx | <-> | DATA0 - DATA7
 *     18 | CB1 | <-- | /ACK
 *     40 | CA1 | <-- | BUSY
 *      3 | PA1 | <-- | PAPER-OUT (aka POUT)
 *      4 | PA2 | <-- | SELECTED (aka SEL)
 *      9 | PA7 | --> | /INIT (aka /RESET or /INPUT-PRIME)
 *      6 | PA4 | <-- | /ERROR (aka /FAULT)
 *      7 | PA5 | --> | सूची (aka /SELECT-IN)
 *      8 | PA6 | --> | /AUTO-FEED-XT
 *     39 | CA2 | --> | खोलो
 *      5 | PA3 | <-- | /ACK (same as CB1!)
 *      2 | PA0 | <-- | BUSY (same as CA1!)
 * -------+-----+-----+---------------------------------------------------------
 * 
 * Should be enough to understand some of the driver.
 *
 * Per convention क्रम normal use the port रेजिस्टरs are visible.
 * If you need the data direction रेजिस्टरs, restore the value in the
 * control रेजिस्टर.
 */

#समावेश "multiface.h"
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/parport.h>
#समावेश <linux/delay.h>
#समावेश <linux/mc6821.h>
#समावेश <linux/zorro.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>

/* Maximum Number of Cards supported */
#घोषणा MAX_MFC 5

#अघोषित DEBUG

अटल काष्ठा parport *this_port[MAX_MFC] = अणुशून्य, पूर्ण;
अटल अस्थिर पूर्णांक dummy; /* क्रम trigger पढ़ोds */

#घोषणा pia(dev) ((काष्ठा pia *)(dev->base))
अटल काष्ठा parport_operations pp_mfc3_ops;

अटल व्योम mfc3_ग_लिखो_data(काष्ठा parport *p, अचिन्हित अक्षर data)
अणु
	pr_debug("write_data %c\n", data);

	dummy = pia(p)->pprb; /* clears irq bit */
	/* Triggers also /STROBE.*/
	pia(p)->pprb = data;
पूर्ण

अटल अचिन्हित अक्षर mfc3_पढ़ो_data(काष्ठा parport *p)
अणु
	/* clears पूर्णांकerrupt bit. Triggers also /STROBE. */
	वापस pia(p)->pprb;
पूर्ण

अटल अचिन्हित अक्षर control_pc_to_mfc3(अचिन्हित अक्षर control)
अणु
	अचिन्हित अक्षर ret = 32|64;

	अगर (control & PARPORT_CONTROL_SELECT) /* XXX: What is SELECP? */
		ret &= ~32; /* /SELECT_IN */
	अगर (control & PARPORT_CONTROL_INIT) /* INITP */
		ret |= 128;
	अगर (control & PARPORT_CONTROL_AUTOFD) /* AUTOLF */
		ret &= ~64;
	अगर (control & PARPORT_CONTROL_STROBE) /* Strobe */
		/* Handled directly by hardware */;
	वापस ret;
पूर्ण

अटल अचिन्हित अक्षर control_mfc3_to_pc(अचिन्हित अक्षर control)
अणु
	अचिन्हित अक्षर ret = PARPORT_CONTROL_STROBE 
			  | PARPORT_CONTROL_AUTOFD | PARPORT_CONTROL_SELECT;

	अगर (control & 128) /* /INITP */
		ret |= PARPORT_CONTROL_INIT;
	अगर (control & 64) /* /AUTOLF */
		ret &= ~PARPORT_CONTROL_AUTOFD;
	अगर (control & 32) /* /SELECT_IN */
		ret &= ~PARPORT_CONTROL_SELECT;
	वापस ret;
पूर्ण

अटल व्योम mfc3_ग_लिखो_control(काष्ठा parport *p, अचिन्हित अक्षर control)
अणु
	pr_debug("write_control %02x\n", control);
	pia(p)->ppra = (pia(p)->ppra & 0x1f) | control_pc_to_mfc3(control);
पूर्ण
	
अटल अचिन्हित अक्षर mfc3_पढ़ो_control( काष्ठा parport *p)
अणु
	pr_debug("read_control\n");
	वापस control_mfc3_to_pc(pia(p)->ppra & 0xe0);
पूर्ण

अटल अचिन्हित अक्षर mfc3_frob_control( काष्ठा parport *p, अचिन्हित अक्षर mask, अचिन्हित अक्षर val)
अणु
	अचिन्हित अक्षर old;

	pr_debug("frob_control mask %02x, value %02x\n", mask, val);
	old = mfc3_पढ़ो_control(p);
	mfc3_ग_लिखो_control(p, (old & ~mask) ^ val);
	वापस old;
पूर्ण

अटल अचिन्हित अक्षर status_mfc3_to_pc(अचिन्हित अक्षर status)
अणु
	अचिन्हित अक्षर ret = PARPORT_STATUS_BUSY;

	अगर (status & 1) /* Busy */
		ret &= ~PARPORT_STATUS_BUSY;
	अगर (status & 2) /* PaperOut */
		ret |= PARPORT_STATUS_PAPEROUT;
	अगर (status & 4) /* Selected */
		ret |= PARPORT_STATUS_SELECT;
	अगर (status & 8) /* Ack */
		ret |= PARPORT_STATUS_ACK;
	अगर (status & 16) /* /ERROR */
		ret |= PARPORT_STATUS_ERROR;

	वापस ret;
पूर्ण

अटल अचिन्हित अक्षर mfc3_पढ़ो_status(काष्ठा parport *p)
अणु
	अचिन्हित अक्षर status;

	status = status_mfc3_to_pc(pia(p)->ppra & 0x1f);
	pr_debug("read_status %02x\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक use_cnt;

अटल irqवापस_t mfc3_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक i;

	क्रम( i = 0; i < MAX_MFC; i++)
		अगर (this_port[i] != शून्य)
			अगर (pia(this_port[i])->crb & 128) अणु /* Board caused पूर्णांकerrupt */
				dummy = pia(this_port[i])->pprb; /* clear irq bit */
				parport_generic_irq(this_port[i]);
			पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mfc3_enable_irq(काष्ठा parport *p)
अणु
	pia(p)->crb |= PIA_C1_ENABLE_IRQ;
पूर्ण

अटल व्योम mfc3_disable_irq(काष्ठा parport *p)
अणु
	pia(p)->crb &= ~PIA_C1_ENABLE_IRQ;
पूर्ण

अटल व्योम mfc3_data_क्रमward(काष्ठा parport *p)
अणु
	pr_debug("forward\n");
	pia(p)->crb &= ~PIA_DDR; /* make data direction रेजिस्टर visible */
	pia(p)->pddrb = 255; /* all pins output */
	pia(p)->crb |= PIA_DDR; /* make data रेजिस्टर visible - शेष */
पूर्ण

अटल व्योम mfc3_data_reverse(काष्ठा parport *p)
अणु
	pr_debug("reverse\n");
	pia(p)->crb &= ~PIA_DDR; /* make data direction रेजिस्टर visible */
	pia(p)->pddrb = 0; /* all pins input */
	pia(p)->crb |= PIA_DDR; /* make data रेजिस्टर visible - शेष */
पूर्ण

अटल व्योम mfc3_init_state(काष्ठा pardevice *dev, काष्ठा parport_state *s)
अणु
	s->u.amiga.data = 0;
	s->u.amiga.datadir = 255;
	s->u.amiga.status = 0;
	s->u.amiga.statusdir = 0xe0;
पूर्ण

अटल व्योम mfc3_save_state(काष्ठा parport *p, काष्ठा parport_state *s)
अणु
	s->u.amiga.data = pia(p)->pprb;
	pia(p)->crb &= ~PIA_DDR;
	s->u.amiga.datadir = pia(p)->pddrb;
	pia(p)->crb |= PIA_DDR;
	s->u.amiga.status = pia(p)->ppra;
	pia(p)->cra &= ~PIA_DDR;
	s->u.amiga.statusdir = pia(p)->pddrb;
	pia(p)->cra |= PIA_DDR;
पूर्ण

अटल व्योम mfc3_restore_state(काष्ठा parport *p, काष्ठा parport_state *s)
अणु
	pia(p)->pprb = s->u.amiga.data;
	pia(p)->crb &= ~PIA_DDR;
	pia(p)->pddrb = s->u.amiga.datadir;
	pia(p)->crb |= PIA_DDR;
	pia(p)->ppra = s->u.amiga.status;
	pia(p)->cra &= ~PIA_DDR;
	pia(p)->pddrb = s->u.amiga.statusdir;
	pia(p)->cra |= PIA_DDR;
पूर्ण

अटल काष्ठा parport_operations pp_mfc3_ops = अणु
	.ग_लिखो_data	= mfc3_ग_लिखो_data,
	.पढ़ो_data	= mfc3_पढ़ो_data,

	.ग_लिखो_control	= mfc3_ग_लिखो_control,
	.पढ़ो_control	= mfc3_पढ़ो_control,
	.frob_control	= mfc3_frob_control,

	.पढ़ो_status	= mfc3_पढ़ो_status,

	.enable_irq	= mfc3_enable_irq,
	.disable_irq	= mfc3_disable_irq,

	.data_क्रमward	= mfc3_data_क्रमward, 
	.data_reverse	= mfc3_data_reverse, 

	.init_state	= mfc3_init_state,
	.save_state	= mfc3_save_state,
	.restore_state	= mfc3_restore_state,

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

/* ----------- Initialisation code --------------------------------- */

अटल पूर्णांक __init parport_mfc3_init(व्योम)
अणु
	काष्ठा parport *p;
	पूर्णांक pias = 0;
	काष्ठा pia *pp;
	काष्ठा zorro_dev *z = शून्य;

	अगर (!MACH_IS_AMIGA)
		वापस -ENODEV;

	जबतक ((z = zorro_find_device(ZORRO_PROD_BSC_MULTIFACE_III, z))) अणु
		अचिन्हित दीर्घ piabase = z->resource.start+PIABASE;
		अगर (!request_mem_region(piabase, माप(काष्ठा pia), "PIA"))
			जारी;

		pp = ZTWO_VADDR(piabase);
		pp->crb = 0;
		pp->pddrb = 255; /* all data pins output */
		pp->crb = PIA_DDR|32|8;
		dummy = pp->pddrb; /* पढ़ोing clears पूर्णांकerrupt */
		pp->cra = 0;
		pp->pddra = 0xe0; /* /RESET,  /सूची ,/AUTO-FEED output */
		pp->cra = PIA_DDR;
		pp->ppra = 0; /* reset prपूर्णांकer */
		udelay(10);
		pp->ppra = 128;
		p = parport_रेजिस्टर_port((अचिन्हित दीर्घ)pp, IRQ_AMIGA_PORTS,
					  PARPORT_DMA_NONE, &pp_mfc3_ops);
		अगर (!p)
			जाओ out_port;

		अगर (p->irq != PARPORT_IRQ_NONE) अणु
			अगर (use_cnt++ == 0)
				अगर (request_irq(IRQ_AMIGA_PORTS, mfc3_पूर्णांकerrupt, IRQF_SHARED, p->name, &pp_mfc3_ops))
					जाओ out_irq;
		पूर्ण
		p->dev = &z->dev;

		this_port[pias++] = p;
		pr_info("%s: Multiface III port using irq\n", p->name);
		/* XXX: set operating mode */

		p->निजी_data = (व्योम *)piabase;
		parport_announce_port (p);

		अगर (pias >= MAX_MFC)
			अवरोध;
		जारी;

	out_irq:
		parport_put_port(p);
	out_port:
		release_mem_region(piabase, माप(काष्ठा pia));
	पूर्ण

	वापस pias ? 0 : -ENODEV;
पूर्ण

अटल व्योम __निकास parport_mfc3_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_MFC; i++) अणु
		अगर (!this_port[i])
			जारी;
		parport_हटाओ_port(this_port[i]);
		अगर (this_port[i]->irq != PARPORT_IRQ_NONE) अणु
			अगर (--use_cnt == 0) 
				मुक्त_irq(IRQ_AMIGA_PORTS, &pp_mfc3_ops);
		पूर्ण
		release_mem_region(ZTWO_PADDR(this_port[i]->निजी_data), माप(काष्ठा pia));
		parport_put_port(this_port[i]);
	पूर्ण
पूर्ण


MODULE_AUTHOR("Joerg Dorchain <joerg@dorchain.net>");
MODULE_DESCRIPTION("Parport Driver for Multiface 3 expansion cards Parallel Port");
MODULE_LICENSE("GPL");

module_init(parport_mfc3_init)
module_निकास(parport_mfc3_निकास)
