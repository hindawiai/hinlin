<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	6522 Versatile Interface Adapter (VIA)
 *
 *	There are two of these on the Mac II. Some IRQs are vectored
 *	via them as are assorted bits and bobs - eg RTC, ADB.
 *
 * CSA: Motorola seems to have हटाओd करोcumentation on the 6522 from
 * their web site; try
 *     http://nerini.drf.com/vectrex/other/text/chips/6522/
 *     http://www.zymurgy.net/classic/vic20/vicdet1.hपंचांग
 * and
 *     http://193.23.168.87/mikro_laborversuche/via_iobaustein/via6522_1.hपंचांगl
 * क्रम info.  A full-text web search on 6522 AND VIA will probably also
 * net some usefulness. <cananian@alumni.princeton.edu> 20apr1999
 *
 * Additional data is here (the SY6522 was used in the Mac II etc):
 *     http://www.6502.org/करोcuments/datasheets/synertek/synertek_sy6522.pdf
 *     http://www.6502.org/करोcuments/datasheets/synertek/synertek_sy6522_programming_reference.pdf
 *
 * PRAM/RTC access algorithms are from the NetBSD RTC toolkit version 1.08b
 * by Erik Vogan and adapted to Linux by Joshua M. Thompson (funaho@jurai.org)
 *
 */

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/macपूर्णांकs.h>
#समावेश <यंत्र/mac_via.h>
#समावेश <यंत्र/mac_psc.h>
#समावेश <यंत्र/mac_oss.h>

अस्थिर __u8 *via1, *via2;
पूर्णांक rbv_present;
पूर्णांक via_alt_mapping;
EXPORT_SYMBOL(via_alt_mapping);
अटल __u8 rbv_clear;

/*
 * Globals क्रम accessing the VIA chip रेजिस्टरs without having to
 * check अगर we're hitting a real VIA or an RBV. Normally you could
 * just hit the combined रेजिस्टर (ie, vIER|rIER) but that seems to
 * अवरोध on AV Macs...probably because they actually decode more than
 * eight address bits. Why can't Apple engineers at least be
 * _consistently_ lazy?                          - 1999-05-21 (jmt)
 */

अटल पूर्णांक gIER,gIFR,gBufA,gBufB;

/*
 * On Macs with a genuine VIA chip there is no way to mask an inभागidual slot
 * पूर्णांकerrupt. This limitation also seems to apply to VIA clone logic cores in
 * Quadra-like ASICs. (RBV and OSS machines करोn't have this limitation.)
 *
 * We used to fake it by configuring the relevant VIA pin as an output
 * (to mask the पूर्णांकerrupt) or input (to unmask). That scheme did not work on
 * (at least) the Quadra 700. A NuBus card's /NMRQ संकेत is an खोलो-collector
 * circuit (see Designing Cards and Drivers क्रम Macपूर्णांकosh II and Macपूर्णांकosh SE,
 * p. 10-11 etc) but VIA outमाला_दो are not (see datasheet).
 *
 * Driving these outमाला_दो high must cause the VIA to source current and the
 * card to sink current when it निश्चितs /NMRQ. Current will flow but the pin
 * voltage is uncertain and so the /NMRQ condition may still cause a transition
 * at the VIA2 CA1 input (which explains the lost पूर्णांकerrupts). A side effect
 * is that a disabled slot IRQ can never be tested as pending or not.
 *
 * Driving these outमाला_दो low करोesn't work either. All the slot /NMRQ lines are
 * (active low) OR'd together to generate the CA1 (aka "SLOTS") पूर्णांकerrupt (see
 * The Guide To Macपूर्णांकosh Family Hardware, 2nd edition p. 167). If we drive a
 * disabled /NMRQ line low, the falling edge immediately triggers a CA1
 * पूर्णांकerrupt and all slot पूर्णांकerrupts after that will generate no transition
 * and thereक्रमe no पूर्णांकerrupt, even after being re-enabled.
 *
 * So we make the VIA port A I/O lines inमाला_दो and use nubus_disabled to keep
 * track of their states. When any slot IRQ becomes disabled we mask the CA1
 * umbrella पूर्णांकerrupt. Only when all slot IRQs become enabled करो we unmask
 * the CA1 पूर्णांकerrupt. It must reमुख्य enabled even when cards have no पूर्णांकerrupt
 * handler रेजिस्टरed. Drivers must thereक्रमe disable a slot पूर्णांकerrupt at the
 * device beक्रमe they call मुक्त_irq (like shared and स्वतःvector पूर्णांकerrupts).
 *
 * There is also a related problem when MacOS is used to boot Linux. A network
 * card brought up by a MacOS driver may उठाओ an पूर्णांकerrupt जबतक Linux boots.
 * This can be fatal since it can't be handled until the right driver loads
 * (अगर such a driver exists at all). Apparently related to this hardware
 * limitation, "Designing Cards and Drivers", p. 9-8, says that a slot
 * पूर्णांकerrupt with no driver would crash MacOS (the book was written beक्रमe
 * the appearance of Macs with RBV or OSS).
 */

अटल u8 nubus_disabled;

व्योम via_debug_dump(व्योम);
अटल व्योम via_nubus_init(व्योम);

/*
 * Initialize the VIAs
 *
 * First we figure out where they actually _are_ as well as what type of
 * VIA we have क्रम VIA2 (it could be a real VIA or an RBV or even an OSS.)
 * Then we pretty much clear them out and disable all IRQ sources.
 */

व्योम __init via_init(व्योम)
अणु
	via1 = (व्योम *)VIA1_BASE;
	pr_debug("VIA1 detected at %p\n", via1);

	अगर (oss_present) अणु
		via2 = शून्य;
		rbv_present = 0;
	पूर्ण अन्यथा अणु
		चयन (macपूर्णांकosh_config->via_type) अणु

		/* IIci, IIsi, IIvx, IIvi (P6xx), LC series */

		हाल MAC_VIA_IICI:
			via2 = (व्योम *)RBV_BASE;
			pr_debug("VIA2 (RBV) detected at %p\n", via2);
			rbv_present = 1;
			अगर (macपूर्णांकosh_config->ident == MAC_MODEL_LCIII) अणु
				rbv_clear = 0x00;
			पूर्ण अन्यथा अणु
				/* on most RBVs (& unlike the VIAs), you   */
				/* need to set bit 7 when you ग_लिखो to IFR */
				/* in order क्रम your clear to occur.       */
				rbv_clear = 0x80;
			पूर्ण
			gIER = rIER;
			gIFR = rIFR;
			gBufA = rSIFR;
			gBufB = rBufB;
			अवरोध;

		/* Quadra and early MacIIs agree on the VIA locations */

		हाल MAC_VIA_QUADRA:
		हाल MAC_VIA_II:
			via2 = (व्योम *) VIA2_BASE;
			pr_debug("VIA2 detected at %p\n", via2);
			rbv_present = 0;
			rbv_clear = 0x00;
			gIER = vIER;
			gIFR = vIFR;
			gBufA = vBufA;
			gBufB = vBufB;
			अवरोध;

		शेष:
			panic("UNKNOWN VIA TYPE");
		पूर्ण
	पूर्ण

#अगर_घोषित DEBUG_VIA
	via_debug_dump();
#पूर्ण_अगर

	/*
	 * Shut करोwn all IRQ sources, reset the समयrs, and
	 * समाप्त the समयr latch on VIA1.
	 */

	via1[vIER] = 0x7F;
	via1[vIFR] = 0x7F;
	via1[vT1CL] = 0;
	via1[vT1CH] = 0;
	via1[vT2CL] = 0;
	via1[vT2CH] = 0;
	via1[vACR] &= ~0xC0; /* setup T1 समयr with no PB7 output */
	via1[vACR] &= ~0x03; /* disable port A & B latches */

	/*
	 * SE/30: disable video IRQ
	 */

	अगर (macपूर्णांकosh_config->ident == MAC_MODEL_SE30) अणु
		via1[vDirB] |= 0x40;
		via1[vBufB] |= 0x40;
	पूर्ण

	चयन (macपूर्णांकosh_config->adb_type) अणु
	हाल MAC_ADB_IOP:
	हाल MAC_ADB_II:
	हाल MAC_ADB_PB1:
		/*
		 * Set the RTC bits to a known state: all lines to outमाला_दो and
		 * RTC disabled (yes that's 0 to enable and 1 to disable).
		 */
		via1[vDirB] |= VIA1B_vRTCEnb | VIA1B_vRTCClk | VIA1B_vRTCData;
		via1[vBufB] |= VIA1B_vRTCEnb | VIA1B_vRTCClk;
		अवरोध;
	पूर्ण

	/* Everything below this poपूर्णांक is VIA2/RBV only... */

	अगर (oss_present)
		वापस;

	अगर ((macपूर्णांकosh_config->via_type == MAC_VIA_QUADRA) &&
	    (macपूर्णांकosh_config->adb_type != MAC_ADB_PB1) &&
	    (macपूर्णांकosh_config->adb_type != MAC_ADB_PB2) &&
	    (macपूर्णांकosh_config->ident    != MAC_MODEL_C660) &&
	    (macपूर्णांकosh_config->ident    != MAC_MODEL_Q840)) अणु
		via_alt_mapping = 1;
		via1[vDirB] |= 0x40;
		via1[vBufB] &= ~0x40;
	पूर्ण अन्यथा अणु
		via_alt_mapping = 0;
	पूर्ण

	/*
	 * Now initialize VIA2. For RBV we just समाप्त all पूर्णांकerrupts;
	 * क्रम a regular VIA we also reset the समयrs and stuff.
	 */

	via2[gIER] = 0x7F;
	via2[gIFR] = 0x7F | rbv_clear;
	अगर (!rbv_present) अणु
		via2[vT1CL] = 0;
		via2[vT1CH] = 0;
		via2[vT2CL] = 0;
		via2[vT2CH] = 0;
		via2[vACR] &= ~0xC0; /* setup T1 समयr with no PB7 output */
		via2[vACR] &= ~0x03; /* disable port A & B latches */
	पूर्ण

	via_nubus_init();

	/* Everything below this poपूर्णांक is VIA2 only... */

	अगर (rbv_present)
		वापस;

	/*
	 * Set vPCR क्रम control line पूर्णांकerrupts.
	 *
	 * CA1 (SLOTS IRQ), CB1 (ASC IRQ): negative edge trigger.
	 *
	 * Macs with ESP SCSI have a negative edge triggered SCSI पूर्णांकerrupt.
	 * Testing reveals that PowerBooks करो too. However, the SE/30
	 * schematic diagram shows an active high NCR5380 IRQ line.
	 */

	pr_debug("VIA2 vPCR is 0x%02X\n", via2[vPCR]);
	अगर (macपूर्णांकosh_config->via_type == MAC_VIA_II) अणु
		/* CA2 (SCSI DRQ), CB2 (SCSI IRQ): indep. input, pos. edge */
		via2[vPCR] = 0x66;
	पूर्ण अन्यथा अणु
		/* CA2 (SCSI DRQ), CB2 (SCSI IRQ): indep. input, neg. edge */
		via2[vPCR] = 0x22;
	पूर्ण
पूर्ण

/*
 * Debugging dump, used in various places to see what's going on.
 */

व्योम via_debug_dump(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG "VIA1: DDRA = 0x%02X DDRB = 0x%02X ACR = 0x%02X\n",
		(uपूर्णांक) via1[vDirA], (uपूर्णांक) via1[vDirB], (uपूर्णांक) via1[vACR]);
	prपूर्णांकk(KERN_DEBUG "         PCR = 0x%02X  IFR = 0x%02X IER = 0x%02X\n",
		(uपूर्णांक) via1[vPCR], (uपूर्णांक) via1[vIFR], (uपूर्णांक) via1[vIER]);
	अगर (!via2)
		वापस;
	अगर (rbv_present) अणु
		prपूर्णांकk(KERN_DEBUG "VIA2:  IFR = 0x%02X  IER = 0x%02X\n",
			(uपूर्णांक) via2[rIFR], (uपूर्णांक) via2[rIER]);
		prपूर्णांकk(KERN_DEBUG "      SIFR = 0x%02X SIER = 0x%02X\n",
			(uपूर्णांक) via2[rSIFR], (uपूर्णांक) via2[rSIER]);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "VIA2: DDRA = 0x%02X DDRB = 0x%02X ACR = 0x%02X\n",
			(uपूर्णांक) via2[vDirA], (uपूर्णांक) via2[vDirB],
			(uपूर्णांक) via2[vACR]);
		prपूर्णांकk(KERN_DEBUG "         PCR = 0x%02X  IFR = 0x%02X IER = 0x%02X\n",
			(uपूर्णांक) via2[vPCR],
			(uपूर्णांक) via2[vIFR], (uपूर्णांक) via2[vIER]);
	पूर्ण
पूर्ण

/*
 * Flush the L2 cache on Macs that have it by flipping
 * the प्रणाली पूर्णांकo 24-bit mode क्रम an instant.
 */

व्योम via_l2_flush(पूर्णांक ग_लिखोback)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	via2[gBufB] &= ~VIA2B_vMode32;
	via2[gBufB] |= VIA2B_vMode32;
	local_irq_restore(flags);
पूर्ण

/*
 * Initialize VIA2 क्रम Nubus access
 */

अटल व्योम __init via_nubus_init(व्योम)
अणु
	/* unlock nubus transactions */

	अगर ((macपूर्णांकosh_config->adb_type != MAC_ADB_PB1) &&
	    (macपूर्णांकosh_config->adb_type != MAC_ADB_PB2)) अणु
		/* set the line to be an output on non-RBV machines */
		अगर (!rbv_present)
			via2[vDirB] |= 0x02;

		/* this seems to be an ADB bit on PMU machines */
		/* according to MkLinux.  -- jmt               */
		via2[gBufB] |= 0x02;
	पूर्ण

	/*
	 * Disable the slot पूर्णांकerrupts. On some hardware that's not possible.
	 * On some hardware it's unclear what all of these I/O lines करो.
	 */

	चयन (macपूर्णांकosh_config->via_type) अणु
	हाल MAC_VIA_II:
	हाल MAC_VIA_QUADRA:
		pr_debug("VIA2 vDirA is 0x%02X\n", via2[vDirA]);
		अवरोध;
	हाल MAC_VIA_IICI:
		/* RBV. Disable all the slot पूर्णांकerrupts. SIER works like IER. */
		via2[rSIER] = 0x7F;
		अवरोध;
	पूर्ण
पूर्ण

व्योम via_nubus_irq_startup(पूर्णांक irq)
अणु
	पूर्णांक irq_idx = IRQ_IDX(irq);

	चयन (macपूर्णांकosh_config->via_type) अणु
	हाल MAC_VIA_II:
	हाल MAC_VIA_QUADRA:
		/* Make the port A line an input. Probably redundant. */
		अगर (macपूर्णांकosh_config->via_type == MAC_VIA_II) अणु
			/* The top two bits are RAM size outमाला_दो. */
			via2[vDirA] &= 0xC0 | ~(1 << irq_idx);
		पूर्ण अन्यथा अणु
			/* Allow NuBus slots 9 through F. */
			via2[vDirA] &= 0x80 | ~(1 << irq_idx);
		पूर्ण
		fallthrough;
	हाल MAC_VIA_IICI:
		via_irq_enable(irq);
		अवरोध;
	पूर्ण
पूर्ण

व्योम via_nubus_irq_shutकरोwn(पूर्णांक irq)
अणु
	चयन (macपूर्णांकosh_config->via_type) अणु
	हाल MAC_VIA_II:
	हाल MAC_VIA_QUADRA:
		/* Ensure that the umbrella CA1 पूर्णांकerrupt reमुख्यs enabled. */
		via_irq_enable(irq);
		अवरोध;
	हाल MAC_VIA_IICI:
		via_irq_disable(irq);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * The generic VIA पूर्णांकerrupt routines (shamelessly stolen from Alan Cox's
 * via6522.c :-), disable/pending masks added.
 */

#घोषणा VIA_TIMER_1_INT BIT(6)

व्योम via1_irq(काष्ठा irq_desc *desc)
अणु
	पूर्णांक irq_num;
	अचिन्हित अक्षर irq_bit, events;

	events = via1[vIFR] & via1[vIER] & 0x7F;
	अगर (!events)
		वापस;

	irq_num = IRQ_MAC_TIMER_1;
	irq_bit = VIA_TIMER_1_INT;
	अगर (events & irq_bit) अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		via1[vIFR] = irq_bit;
		generic_handle_irq(irq_num);
		local_irq_restore(flags);

		events &= ~irq_bit;
		अगर (!events)
			वापस;
	पूर्ण

	irq_num = VIA1_SOURCE_BASE;
	irq_bit = 1;
	करो अणु
		अगर (events & irq_bit) अणु
			via1[vIFR] = irq_bit;
			generic_handle_irq(irq_num);
		पूर्ण
		++irq_num;
		irq_bit <<= 1;
	पूर्ण जबतक (events >= irq_bit);
पूर्ण

अटल व्योम via2_irq(काष्ठा irq_desc *desc)
अणु
	पूर्णांक irq_num;
	अचिन्हित अक्षर irq_bit, events;

	events = via2[gIFR] & via2[gIER] & 0x7F;
	अगर (!events)
		वापस;

	irq_num = VIA2_SOURCE_BASE;
	irq_bit = 1;
	करो अणु
		अगर (events & irq_bit) अणु
			via2[gIFR] = irq_bit | rbv_clear;
			generic_handle_irq(irq_num);
		पूर्ण
		++irq_num;
		irq_bit <<= 1;
	पूर्ण जबतक (events >= irq_bit);
पूर्ण

/*
 * Dispatch Nubus पूर्णांकerrupts. We are called as a secondary dispatch by the
 * VIA2 dispatcher as a fast पूर्णांकerrupt handler.
 */

अटल व्योम via_nubus_irq(काष्ठा irq_desc *desc)
अणु
	पूर्णांक slot_irq;
	अचिन्हित अक्षर slot_bit, events;

	events = ~via2[gBufA] & 0x7F;
	अगर (rbv_present)
		events &= via2[rSIER];
	अन्यथा
		events &= ~via2[vDirA];
	अगर (!events)
		वापस;

	करो अणु
		slot_irq = IRQ_NUBUS_F;
		slot_bit = 0x40;
		करो अणु
			अगर (events & slot_bit) अणु
				events &= ~slot_bit;
				generic_handle_irq(slot_irq);
			पूर्ण
			--slot_irq;
			slot_bit >>= 1;
		पूर्ण जबतक (events);

 		/* clear the CA1 पूर्णांकerrupt and make certain there's no more. */
		via2[gIFR] = 0x02 | rbv_clear;
		events = ~via2[gBufA] & 0x7F;
		अगर (rbv_present)
			events &= via2[rSIER];
		अन्यथा
			events &= ~via2[vDirA];
	पूर्ण जबतक (events);
पूर्ण

/*
 * Register the पूर्णांकerrupt dispatchers क्रम VIA or RBV machines only.
 */

व्योम __init via_रेजिस्टर_पूर्णांकerrupts(व्योम)
अणु
	अगर (via_alt_mapping) अणु
		/* software पूर्णांकerrupt */
		irq_set_chained_handler(IRQ_AUTO_1, via1_irq);
		/* via1 पूर्णांकerrupt */
		irq_set_chained_handler(IRQ_AUTO_6, via1_irq);
	पूर्ण अन्यथा अणु
		irq_set_chained_handler(IRQ_AUTO_1, via1_irq);
	पूर्ण
	irq_set_chained_handler(IRQ_AUTO_2, via2_irq);
	irq_set_chained_handler(IRQ_MAC_NUBUS, via_nubus_irq);
पूर्ण

व्योम via_irq_enable(पूर्णांक irq) अणु
	पूर्णांक irq_src	= IRQ_SRC(irq);
	पूर्णांक irq_idx	= IRQ_IDX(irq);

	अगर (irq_src == 1) अणु
		via1[vIER] = IER_SET_BIT(irq_idx);
	पूर्ण अन्यथा अगर (irq_src == 2) अणु
		अगर (irq != IRQ_MAC_NUBUS || nubus_disabled == 0)
			via2[gIER] = IER_SET_BIT(irq_idx);
	पूर्ण अन्यथा अगर (irq_src == 7) अणु
		चयन (macपूर्णांकosh_config->via_type) अणु
		हाल MAC_VIA_II:
		हाल MAC_VIA_QUADRA:
			nubus_disabled &= ~(1 << irq_idx);
			/* Enable the CA1 पूर्णांकerrupt when no slot is disabled. */
			अगर (!nubus_disabled)
				via2[gIER] = IER_SET_BIT(1);
			अवरोध;
		हाल MAC_VIA_IICI:
			/* On RBV, enable the slot पूर्णांकerrupt.
			 * SIER works like IER.
			 */
			via2[rSIER] = IER_SET_BIT(irq_idx);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम via_irq_disable(पूर्णांक irq) अणु
	पूर्णांक irq_src	= IRQ_SRC(irq);
	पूर्णांक irq_idx	= IRQ_IDX(irq);

	अगर (irq_src == 1) अणु
		via1[vIER] = IER_CLR_BIT(irq_idx);
	पूर्ण अन्यथा अगर (irq_src == 2) अणु
		via2[gIER] = IER_CLR_BIT(irq_idx);
	पूर्ण अन्यथा अगर (irq_src == 7) अणु
		चयन (macपूर्णांकosh_config->via_type) अणु
		हाल MAC_VIA_II:
		हाल MAC_VIA_QUADRA:
			nubus_disabled |= 1 << irq_idx;
			अगर (nubus_disabled)
				via2[gIER] = IER_CLR_BIT(1);
			अवरोध;
		हाल MAC_VIA_IICI:
			via2[rSIER] = IER_CLR_BIT(irq_idx);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम via1_set_head(पूर्णांक head)
अणु
	अगर (head == 0)
		via1[vBufA] &= ~VIA1A_vHeadSel;
	अन्यथा
		via1[vBufA] |= VIA1A_vHeadSel;
पूर्ण
EXPORT_SYMBOL(via1_set_head);

पूर्णांक via2_scsi_drq_pending(व्योम)
अणु
	वापस via2[gIFR] & (1 << IRQ_IDX(IRQ_MAC_SCSIDRQ));
पूर्ण
EXPORT_SYMBOL(via2_scsi_drq_pending);

/* समयr and घड़ी source */

#घोषणा VIA_CLOCK_FREQ     783360                /* VIA "phase 2" घड़ी in Hz */
#घोषणा VIA_TIMER_CYCLES   (VIA_CLOCK_FREQ / HZ) /* घड़ी cycles per jअगरfy */

#घोषणा VIA_TC             (VIA_TIMER_CYCLES - 2) /* including 0 and -1 */
#घोषणा VIA_TC_LOW         (VIA_TC & 0xFF)
#घोषणा VIA_TC_HIGH        (VIA_TC >> 8)

अटल u64 mac_पढ़ो_clk(काष्ठा घड़ीsource *cs);

अटल काष्ठा घड़ीsource mac_clk = अणु
	.name   = "via1",
	.rating = 250,
	.पढ़ो   = mac_पढ़ो_clk,
	.mask   = CLOCKSOURCE_MASK(32),
	.flags  = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल u32 clk_total, clk_offset;

अटल irqवापस_t via_समयr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	clk_total += VIA_TIMER_CYCLES;
	clk_offset = 0;
	legacy_समयr_tick(1);

	वापस IRQ_HANDLED;
पूर्ण

व्योम __init via_init_घड़ी(व्योम)
अणु
	अगर (request_irq(IRQ_MAC_TIMER_1, via_समयr_handler, IRQF_TIMER, "timer",
			शून्य)) अणु
		pr_err("Couldn't register %s interrupt\n", "timer");
		वापस;
	पूर्ण

	via1[vT1CL] = VIA_TC_LOW;
	via1[vT1CH] = VIA_TC_HIGH;
	via1[vACR] |= 0x40;

	घड़ीsource_रेजिस्टर_hz(&mac_clk, VIA_CLOCK_FREQ);
पूर्ण

अटल u64 mac_पढ़ो_clk(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;
	u8 count_high;
	u16 count;
	u32 ticks;

	/*
	 * Timer counter wrap-around is detected with the समयr पूर्णांकerrupt flag
	 * but पढ़ोing the counter low byte (vT1CL) would reset the flag.
	 * Also, accessing both counter रेजिस्टरs is essentially a data race.
	 * These problems are aव्योमed by ignoring the low byte. Clock accuracy
	 * is 256 बार worse (error can reach 0.327 ms) but CPU overhead is
	 * reduced by aव्योमing slow VIA रेजिस्टर accesses.
	 */

	local_irq_save(flags);
	count_high = via1[vT1CH];
	अगर (count_high == 0xFF)
		count_high = 0;
	अगर (count_high > 0 && (via1[vIFR] & VIA_TIMER_1_INT))
		clk_offset = VIA_TIMER_CYCLES;
	count = count_high << 8;
	ticks = VIA_TIMER_CYCLES - count;
	ticks += clk_offset + clk_total;
	local_irq_restore(flags);

	वापस ticks;
पूर्ण
