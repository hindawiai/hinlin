<शैली गुरु>
/*
 * arch/m68k/atari/ataपूर्णांकs.c -- Atari Linux पूर्णांकerrupt handling code
 *
 * 5/2/94 Roman Hodek:
 *  Added support क्रम TT पूर्णांकerrupts; setup क्रम TT SCU (may someone has
 *  twiddled there and we won't get the right पूर्णांकerrupts :-()
 *
 *  Major change: The device-independent code in m68k/पूर्णांकs.c didn't know
 *  about non-स्वतःvec पूर्णांकs yet. It hardcoded the number of possible पूर्णांकs to
 *  7 (IRQ1...IRQ7). But the Atari has lots of non-स्वतःvec पूर्णांकs! I made the
 *  number of possible पूर्णांकs a स्थिरant defined in पूर्णांकerrupt.h, which is
 *  47 क्रम the Atari. So we can call request_irq() क्रम all Atari पूर्णांकerrupts
 *  just the normal way. Additionally, all vectors >= 48 are initialized to
 *  call trap() instead of पूर्णांकhandler(). This must be changed here, too.
 *
 * 1995-07-16 Lars Brinkhoff <f93labr@dd.chalmers.se>:
 *  Corrected a bug in atari_add_isr() which rejected all SCC
 *  पूर्णांकerrupt sources अगर there were no TT MFP!
 *
 * 12/13/95: New पूर्णांकerface functions atari_level_triggered_पूर्णांक() and
 *  atari_रेजिस्टर_vme_पूर्णांक() as support क्रम level triggered VME पूर्णांकerrupts.
 *
 * 02/12/96: (Roman)
 *  Total reग_लिखो of Atari पूर्णांकerrupt handling, क्रम new scheme see comments
 *  below.
 *
 * 1996-09-03 lars brinkhoff <f93labr@dd.chalmers.se>:
 *  Added new function atari_unरेजिस्टर_vme_पूर्णांक(), and
 *  modअगरied atari_रेजिस्टर_vme_पूर्णांक() as well as IS_VALID_INTNO()
 *  to work with it.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/module.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/traps.h>

#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/atariपूर्णांकs.h>
#समावेश <यंत्र/atari_stdma.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/entry.h>
#समावेश <यंत्र/पन.स>


/*
 * Atari पूर्णांकerrupt handling scheme:
 * --------------------------------
 *
 * All पूर्णांकerrupt source have an पूर्णांकernal number (defined in
 * <यंत्र/atariपूर्णांकs.h>): Autovector पूर्णांकerrupts are 1..7, then follow ST-MFP,
 * TT-MFP, SCC, and finally VME पूर्णांकerrupts. Vector numbers क्रम the latter can
 * be allocated by atari_रेजिस्टर_vme_पूर्णांक().
 */

/*
 * Biपंचांगap क्रम मुक्त पूर्णांकerrupt vector numbers
 * (new vectors starting from 0x70 can be allocated by
 * atari_रेजिस्टर_vme_पूर्णांक())
 */
अटल पूर्णांक मुक्त_vme_vec_biपंचांगap;

/* GK:
 * HBL IRQ handler क्रम Falcon. Nobody needs it :-)
 * ++andreas: उठाओ ipl to disable further HBLANK पूर्णांकerrupts.
 */
यंत्रlinkage व्योम falcon_hblhandler(व्योम);
यंत्र(".text\n"
__ALIGN_STR "\n\t"
"falcon_hblhandler:\n\t"
	"orw	#0x200,%sp@\n\t"	/* set saved ipl to 2 */
	"rte");

बाह्य व्योम atari_microwire_cmd(पूर्णांक cmd);

अटल अचिन्हित पूर्णांक atari_irq_startup(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;

	m68k_irq_startup(data);
	atari_turnon_irq(irq);
	atari_enable_irq(irq);
	वापस 0;
पूर्ण

अटल व्योम atari_irq_shutकरोwn(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;

	atari_disable_irq(irq);
	atari_turnoff_irq(irq);
	m68k_irq_shutकरोwn(data);

	अगर (irq == IRQ_AUTO_4)
	    vectors[VEC_INT4] = falcon_hblhandler;
पूर्ण

अटल व्योम atari_irq_enable(काष्ठा irq_data *data)
अणु
	atari_enable_irq(data->irq);
पूर्ण

अटल व्योम atari_irq_disable(काष्ठा irq_data *data)
अणु
	atari_disable_irq(data->irq);
पूर्ण

अटल काष्ठा irq_chip atari_irq_chip = अणु
	.name		= "atari",
	.irq_startup	= atari_irq_startup,
	.irq_shutकरोwn	= atari_irq_shutकरोwn,
	.irq_enable	= atari_irq_enable,
	.irq_disable	= atari_irq_disable,
पूर्ण;

/*
 * ST-MFP समयr D chained पूर्णांकerrupts - each driver माला_लो its own समयr
 * पूर्णांकerrupt instance.
 */

काष्ठा mfpसमयrbase अणु
	अस्थिर काष्ठा MFP *mfp;
	अचिन्हित अक्षर mfp_mask, mfp_data;
	अचिन्हित लघु पूर्णांक_mask;
	पूर्णांक handler_irq, mfpसमयr_irq, server_irq;
	अक्षर *name;
पूर्ण sपंचांगfp_base = अणु
	.mfp		= &st_mfp,
	.पूर्णांक_mask	= 0x0,
	.handler_irq	= IRQ_MFP_TIMD,
	.mfpसमयr_irq	= IRQ_MFP_TIMER1,
	.name		= "MFP Timer D"
पूर्ण;

अटल irqवापस_t mfp_समयr_d_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mfpसमयrbase *base = dev_id;
	पूर्णांक mach_irq;
	अचिन्हित अक्षर पूर्णांकs;

	mach_irq = base->mfpसमयr_irq;
	पूर्णांकs = base->पूर्णांक_mask;
	क्रम (; पूर्णांकs; mach_irq++, पूर्णांकs >>= 1) अणु
		अगर (पूर्णांकs & 1)
			generic_handle_irq(mach_irq);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण


अटल व्योम atari_mfpसमयr_enable(काष्ठा irq_data *data)
अणु
	पूर्णांक mfp_num = data->irq - IRQ_MFP_TIMER1;
	sपंचांगfp_base.पूर्णांक_mask |= 1 << mfp_num;
	atari_enable_irq(IRQ_MFP_TIMD);
पूर्ण

अटल व्योम atari_mfpसमयr_disable(काष्ठा irq_data *data)
अणु
	पूर्णांक mfp_num = data->irq - IRQ_MFP_TIMER1;
	sपंचांगfp_base.पूर्णांक_mask &= ~(1 << mfp_num);
	अगर (!sपंचांगfp_base.पूर्णांक_mask)
		atari_disable_irq(IRQ_MFP_TIMD);
पूर्ण

अटल काष्ठा irq_chip atari_mfpसमयr_chip = अणु
	.name		= "timer_d",
	.irq_enable	= atari_mfpसमयr_enable,
	.irq_disable	= atari_mfpसमयr_disable,
पूर्ण;


/*
 * EtherNAT CPLD पूर्णांकerrupt handling
 * CPLD पूर्णांकerrupt रेजिस्टर is at phys. 0x80000023
 * Need this mapped in at पूर्णांकerrupt startup समय
 * Possibly need this mapped on demand anyway -
 * EtherNAT USB driver needs to disable IRQ beक्रमe
 * startup!
 */

अटल अचिन्हित अक्षर *enat_cpld;

अटल अचिन्हित पूर्णांक atari_ethernat_startup(काष्ठा irq_data *data)
अणु
	पूर्णांक enat_num = 140 - data->irq + 1;

	m68k_irq_startup(data);
	/*
	* map CPLD पूर्णांकerrupt रेजिस्टर
	*/
	अगर (!enat_cpld)
		enat_cpld = (अचिन्हित अक्षर *)ioremap((ATARI_ETHERNAT_PHYS_ADDR+0x23), 0x2);
	/*
	 * करो _not_ enable the USB chip पूर्णांकerrupt here - causes पूर्णांकerrupt storm
	 * and triggers dead पूर्णांकerrupt watchकरोg
	 * Need to reset the USB chip to a sane state in early startup beक्रमe
	 * removing this hack
	 */
	अगर (enat_num == 1)
		*enat_cpld |= 1 << enat_num;

	वापस 0;
पूर्ण

अटल व्योम atari_ethernat_enable(काष्ठा irq_data *data)
अणु
	पूर्णांक enat_num = 140 - data->irq + 1;
	/*
	* map CPLD पूर्णांकerrupt रेजिस्टर
	*/
	अगर (!enat_cpld)
		enat_cpld = (अचिन्हित अक्षर *)ioremap((ATARI_ETHERNAT_PHYS_ADDR+0x23), 0x2);
	*enat_cpld |= 1 << enat_num;
पूर्ण

अटल व्योम atari_ethernat_disable(काष्ठा irq_data *data)
अणु
	पूर्णांक enat_num = 140 - data->irq + 1;
	/*
	* map CPLD पूर्णांकerrupt रेजिस्टर
	*/
	अगर (!enat_cpld)
		enat_cpld = (अचिन्हित अक्षर *)ioremap((ATARI_ETHERNAT_PHYS_ADDR+0x23), 0x2);
	*enat_cpld &= ~(1 << enat_num);
पूर्ण

अटल व्योम atari_ethernat_shutकरोwn(काष्ठा irq_data *data)
अणु
	पूर्णांक enat_num = 140 - data->irq + 1;
	अगर (enat_cpld) अणु
		*enat_cpld &= ~(1 << enat_num);
		iounmap(enat_cpld);
		enat_cpld = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip atari_ethernat_chip = अणु
	.name		= "ethernat",
	.irq_startup	= atari_ethernat_startup,
	.irq_shutकरोwn	= atari_ethernat_shutकरोwn,
	.irq_enable	= atari_ethernat_enable,
	.irq_disable	= atari_ethernat_disable,
पूर्ण;

/*
 * व्योम atari_init_IRQ (व्योम)
 *
 * Parameters:	None
 *
 * Returns:	Nothing
 *
 * This function should be called during kernel startup to initialize
 * the atari IRQ handling routines.
 */

व्योम __init atari_init_IRQ(व्योम)
अणु
	m68k_setup_user_पूर्णांकerrupt(VEC_USER, NUM_ATARI_SOURCES - IRQ_USER);
	m68k_setup_irq_controller(&atari_irq_chip, handle_simple_irq, 1,
				  NUM_ATARI_SOURCES - 1);

	/* Initialize the MFP(s) */

#अगर_घोषित ATARI_USE_SOFTWARE_EOI
	st_mfp.vec_adr  = 0x48;	/* Software EOI-Mode */
#अन्यथा
	st_mfp.vec_adr  = 0x40;	/* Automatic EOI-Mode */
#पूर्ण_अगर
	st_mfp.पूर्णांक_en_a = 0x00;	/* turn off MFP-Ints */
	st_mfp.पूर्णांक_en_b = 0x00;
	st_mfp.पूर्णांक_mk_a = 0xff;	/* no Masking */
	st_mfp.पूर्णांक_mk_b = 0xff;

	अगर (ATARIHW_PRESENT(TT_MFP)) अणु
#अगर_घोषित ATARI_USE_SOFTWARE_EOI
		tt_mfp.vec_adr  = 0x58;		/* Software EOI-Mode */
#अन्यथा
		tt_mfp.vec_adr  = 0x50;		/* Automatic EOI-Mode */
#पूर्ण_अगर
		tt_mfp.पूर्णांक_en_a = 0x00;		/* turn off MFP-Ints */
		tt_mfp.पूर्णांक_en_b = 0x00;
		tt_mfp.पूर्णांक_mk_a = 0xff;		/* no Masking */
		tt_mfp.पूर्णांक_mk_b = 0xff;
	पूर्ण

	अगर (ATARIHW_PRESENT(SCC) && !atari_SCC_reset_करोne) अणु
		atari_scc.cha_a_ctrl = 9;
		MFPDELAY();
		atari_scc.cha_a_ctrl = (अक्षर) 0xc0; /* hardware reset */
	पूर्ण

	अगर (ATARIHW_PRESENT(SCU)) अणु
		/* init the SCU अगर present */
		tt_scu.sys_mask = 0x10;		/* enable VBL (क्रम the cursor) and
									 * disable HSYNC पूर्णांकerrupts (who
									 * needs them?)  MFP and SCC are
									 * enabled in VME mask
									 */
		tt_scu.vme_mask = 0x60;		/* enable MFP and SCC पूर्णांकs */
	पूर्ण अन्यथा अणु
		/* If no SCU and no Hades, the HSYNC पूर्णांकerrupt needs to be
		 * disabled this way. (Else _पूर्णांकhandler in kernel/sys_call.S
		 * माला_लो overruns)
		 */

		vectors[VEC_INT2] = falcon_hblhandler;
		vectors[VEC_INT4] = falcon_hblhandler;
	पूर्ण

	अगर (ATARIHW_PRESENT(PCM_8BIT) && ATARIHW_PRESENT(MICROWIRE)) अणु
		/* Initialize the LM1992 Sound Controller to enable
		   the PSG sound.  This is misplaced here, it should
		   be in an atasound_init(), that करोesn't exist yet. */
		atari_microwire_cmd(MW_LM1992_PSG_HIGH);
	पूर्ण

	stdma_init();

	/* Initialize the PSG: all sounds off, both ports output */
	sound_ym.rd_data_reg_sel = 7;
	sound_ym.wd_data = 0xff;

	m68k_setup_irq_controller(&atari_mfpसमयr_chip, handle_simple_irq,
				  IRQ_MFP_TIMER1, 8);

	irq_set_status_flags(IRQ_MFP_TIMER1, IRQ_IS_POLLED);
	irq_set_status_flags(IRQ_MFP_TIMER2, IRQ_IS_POLLED);

	/* prepare समयr D data क्रम use as poll पूर्णांकerrupt */
	/* set Timer D data Register - needs to be > 0 */
	st_mfp.tim_dt_d = 254;	/* < 100 Hz */
	/* start समयr D, भाग = 1:100 */
	st_mfp.tim_ct_cd = (st_mfp.tim_ct_cd & 0xf0) | 0x6;

	/* request समयr D dispatch handler */
	अगर (request_irq(IRQ_MFP_TIMD, mfp_समयr_d_handler, IRQF_SHARED,
			sपंचांगfp_base.name, &sपंचांगfp_base))
		pr_err("Couldn't register %s interrupt\n", sपंचांगfp_base.name);

	/*
	 * EtherNAT ethernet / USB पूर्णांकerrupt handlers
	 */

	m68k_setup_irq_controller(&atari_ethernat_chip, handle_simple_irq,
				  139, 2);
पूर्ण


/*
 * atari_रेजिस्टर_vme_पूर्णांक() वापसs the number of a मुक्त पूर्णांकerrupt vector क्रम
 * hardware with a programmable पूर्णांक vector (probably a VME board).
 */

अचिन्हित पूर्णांक atari_रेजिस्टर_vme_पूर्णांक(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 32; i++)
		अगर ((मुक्त_vme_vec_biपंचांगap & (1 << i)) == 0)
			अवरोध;

	अगर (i == 16)
		वापस 0;

	मुक्त_vme_vec_biपंचांगap |= 1 << i;
	वापस VME_SOURCE_BASE + i;
पूर्ण
EXPORT_SYMBOL(atari_रेजिस्टर_vme_पूर्णांक);


व्योम atari_unरेजिस्टर_vme_पूर्णांक(अचिन्हित पूर्णांक irq)
अणु
	अगर (irq >= VME_SOURCE_BASE && irq < VME_SOURCE_BASE + VME_MAX_SOURCES) अणु
		irq -= VME_SOURCE_BASE;
		मुक्त_vme_vec_biपंचांगap &= ~(1 << irq);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(atari_unरेजिस्टर_vme_पूर्णांक);


