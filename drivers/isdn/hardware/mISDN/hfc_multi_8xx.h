<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * For License see notice in hfc_multi.c
 *
 * special IO and init functions क्रम the embedded XHFC board
 * from Speech Design
 *
 */

#समावेश <यंत्र/cpm1.h>

/* Change this to the value used by your board */
#अगर_अघोषित IMAP_ADDR
#घोषणा IMAP_ADDR	0xFFF00000
#पूर्ण_अगर

अटल व्योम
#अगर_घोषित HFC_REGISTER_DEBUG
HFC_outb_embsd(काष्ठा hfc_multi *hc, u_अक्षर reg, u_अक्षर val,
	       स्थिर अक्षर *function, पूर्णांक line)
#अन्यथा
	HFC_outb_embsd(काष्ठा hfc_multi *hc, u_अक्षर reg, u_अक्षर val)
#पूर्ण_अगर
अणु
	hc->immap->im_ioport.iop_padat |= PA_XHFC_A0;
	ग_लिखोb(reg, hc->xhfc_memaddr);
	hc->immap->im_ioport.iop_padat &= ~(PA_XHFC_A0);
	ग_लिखोb(val, hc->xhfc_memdata);
पूर्ण
अटल u_अक्षर
#अगर_घोषित HFC_REGISTER_DEBUG
HFC_inb_embsd(काष्ठा hfc_multi *hc, u_अक्षर reg, स्थिर अक्षर *function, पूर्णांक line)
#अन्यथा
	HFC_inb_embsd(काष्ठा hfc_multi *hc, u_अक्षर reg)
#पूर्ण_अगर
अणु
	hc->immap->im_ioport.iop_padat |= PA_XHFC_A0;
	ग_लिखोb(reg, hc->xhfc_memaddr);
	hc->immap->im_ioport.iop_padat &= ~(PA_XHFC_A0);
	वापस पढ़ोb(hc->xhfc_memdata);
पूर्ण
अटल u_लघु
#अगर_घोषित HFC_REGISTER_DEBUG
HFC_inw_embsd(काष्ठा hfc_multi *hc, u_अक्षर reg, स्थिर अक्षर *function, पूर्णांक line)
#अन्यथा
	HFC_inw_embsd(काष्ठा hfc_multi *hc, u_अक्षर reg)
#पूर्ण_अगर
अणु
	hc->immap->im_ioport.iop_padat |= PA_XHFC_A0;
	ग_लिखोb(reg, hc->xhfc_memaddr);
	hc->immap->im_ioport.iop_padat &= ~(PA_XHFC_A0);
	वापस पढ़ोb(hc->xhfc_memdata);
पूर्ण
अटल व्योम
#अगर_घोषित HFC_REGISTER_DEBUG
HFC_रुको_embsd(काष्ठा hfc_multi *hc, स्थिर अक्षर *function, पूर्णांक line)
#अन्यथा
	HFC_रुको_embsd(काष्ठा hfc_multi *hc)
#पूर्ण_अगर
अणु
	hc->immap->im_ioport.iop_padat |= PA_XHFC_A0;
	ग_लिखोb(R_STATUS, hc->xhfc_memaddr);
	hc->immap->im_ioport.iop_padat &= ~(PA_XHFC_A0);
	जबतक (पढ़ोb(hc->xhfc_memdata) & V_BUSY)
		cpu_relax();
पूर्ण

/* ग_लिखो fअगरo data (EMBSD) */
व्योम
ग_लिखो_fअगरo_embsd(काष्ठा hfc_multi *hc, u_अक्षर *data, पूर्णांक len)
अणु
	hc->immap->im_ioport.iop_padat |= PA_XHFC_A0;
	*hc->xhfc_memaddr = A_FIFO_DATA0;
	hc->immap->im_ioport.iop_padat &= ~(PA_XHFC_A0);
	जबतक (len) अणु
		*hc->xhfc_memdata = *data;
		data++;
		len--;
	पूर्ण
पूर्ण

/* पढ़ो fअगरo data (EMBSD) */
व्योम
पढ़ो_fअगरo_embsd(काष्ठा hfc_multi *hc, u_अक्षर *data, पूर्णांक len)
अणु
	hc->immap->im_ioport.iop_padat |= PA_XHFC_A0;
	*hc->xhfc_memaddr = A_FIFO_DATA0;
	hc->immap->im_ioport.iop_padat &= ~(PA_XHFC_A0);
	जबतक (len) अणु
		*data = (u_अक्षर)(*hc->xhfc_memdata);
		data++;
		len--;
	पूर्ण
पूर्ण

अटल पूर्णांक
setup_embedded(काष्ठा hfc_multi *hc, काष्ठा hm_map *m)
अणु
	prपूर्णांकk(KERN_INFO
	       "HFC-multi: card manufacturer: '%s' card name: '%s' clock: %s\n",
	       m->venकरोr_name, m->card_name, m->घड़ी2 ? "double" : "normal");

	hc->pci_dev = शून्य;
	अगर (m->घड़ी2)
		test_and_set_bit(HFC_CHIP_CLOCK2, &hc->chip);

	hc->leds = m->leds;
	hc->ledstate = 0xAFFEAFFE;
	hc->opticalsupport = m->opticalsupport;

	hc->pci_iobase = 0;
	hc->pci_membase = 0;
	hc->xhfc_membase = शून्य;
	hc->xhfc_memaddr = शून्य;
	hc->xhfc_memdata = शून्य;

	/* set memory access methods */
	अगर (m->io_mode) /* use mode from card config */
		hc->io_mode = m->io_mode;
	चयन (hc->io_mode) अणु
	हाल HFC_IO_MODE_EMBSD:
		test_and_set_bit(HFC_CHIP_EMBSD, &hc->chip);
		hc->slots = 128; /* required */
		hc->HFC_outb = HFC_outb_embsd;
		hc->HFC_inb = HFC_inb_embsd;
		hc->HFC_inw = HFC_inw_embsd;
		hc->HFC_रुको = HFC_रुको_embsd;
		hc->पढ़ो_fअगरo = पढ़ो_fअगरo_embsd;
		hc->ग_लिखो_fअगरo = ग_लिखो_fअगरo_embsd;
		hc->xhfc_origmembase = XHFC_MEMBASE + XHFC_OFFSET * hc->id;
		hc->xhfc_membase = (u_अक्षर *)ioremap(hc->xhfc_origmembase,
						     XHFC_MEMSIZE);
		अगर (!hc->xhfc_membase) अणु
			prपूर्णांकk(KERN_WARNING
			       "HFC-multi: failed to remap xhfc address space. "
			       "(internal error)\n");
			वापस -EIO;
		पूर्ण
		hc->xhfc_memaddr = (u_दीर्घ *)(hc->xhfc_membase + 4);
		hc->xhfc_memdata = (u_दीर्घ *)(hc->xhfc_membase);
		prपूर्णांकk(KERN_INFO
		       "HFC-multi: xhfc_membase:%#lx xhfc_origmembase:%#lx "
		       "xhfc_memaddr:%#lx xhfc_memdata:%#lx\n",
		       (u_दीर्घ)hc->xhfc_membase, hc->xhfc_origmembase,
		       (u_दीर्घ)hc->xhfc_memaddr, (u_दीर्घ)hc->xhfc_memdata);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "HFC-multi: Invalid IO mode.\n");
		वापस -EIO;
	पूर्ण

	/* Prepare the MPC8XX PortA 10 as output (address/data selector) */
	hc->immap = (काष्ठा immap *)(IMAP_ADDR);
	hc->immap->im_ioport.iop_papar &= ~(PA_XHFC_A0);
	hc->immap->im_ioport.iop_paodr &= ~(PA_XHFC_A0);
	hc->immap->im_ioport.iop_padir |=   PA_XHFC_A0;

	/* Prepare the MPC8xx PortB __X__ as input (ISDN__X__IRQ) */
	hc->pb_irqmsk = (PB_XHFC_IRQ1 << hc->id);
	hc->immap->im_cpm.cp_pbpar &= ~(hc->pb_irqmsk);
	hc->immap->im_cpm.cp_pbodr &= ~(hc->pb_irqmsk);
	hc->immap->im_cpm.cp_pbdir &= ~(hc->pb_irqmsk);

	/* At this poपूर्णांक the needed config is करोne */
	/* fअगरos are still not enabled */
	वापस 0;
पूर्ण
