<शैली गुरु>
/*
 * Amiga Linux पूर्णांकerrupt handling code
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/irq.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/amipcmcia.h>


/*
 * Enable/disable a particular machine specअगरic पूर्णांकerrupt source.
 * Note that this may affect other पूर्णांकerrupts in हाल of a shared पूर्णांकerrupt.
 * This function should only be called क्रम a _very_ लघु समय to change some
 * पूर्णांकernal data, that may not be changed by the पूर्णांकerrupt at the same समय.
 */

अटल व्योम amiga_irq_enable(काष्ठा irq_data *data)
अणु
	amiga_custom.पूर्णांकena = IF_SETCLR | (1 << (data->irq - IRQ_USER));
पूर्ण

अटल व्योम amiga_irq_disable(काष्ठा irq_data *data)
अणु
	amiga_custom.पूर्णांकena = 1 << (data->irq - IRQ_USER);
पूर्ण

अटल काष्ठा irq_chip amiga_irq_chip = अणु
	.name		= "amiga",
	.irq_enable	= amiga_irq_enable,
	.irq_disable	= amiga_irq_disable,
पूर्ण;


/*
 * The builtin Amiga hardware पूर्णांकerrupt handlers.
 */

अटल व्योम ami_पूर्णांक1(काष्ठा irq_desc *desc)
अणु
	अचिन्हित लघु पूर्णांकs = amiga_custom.पूर्णांकreqr & amiga_custom.पूर्णांकenar;

	/* अगर serial transmit buffer empty, पूर्णांकerrupt */
	अगर (पूर्णांकs & IF_TBE) अणु
		amiga_custom.पूर्णांकreq = IF_TBE;
		generic_handle_irq(IRQ_AMIGA_TBE);
	पूर्ण

	/* अगर floppy disk transfer complete, पूर्णांकerrupt */
	अगर (पूर्णांकs & IF_DSKBLK) अणु
		amiga_custom.पूर्णांकreq = IF_DSKBLK;
		generic_handle_irq(IRQ_AMIGA_DSKBLK);
	पूर्ण

	/* अगर software पूर्णांकerrupt set, पूर्णांकerrupt */
	अगर (पूर्णांकs & IF_SOFT) अणु
		amiga_custom.पूर्णांकreq = IF_SOFT;
		generic_handle_irq(IRQ_AMIGA_SOFT);
	पूर्ण
पूर्ण

अटल व्योम ami_पूर्णांक3(काष्ठा irq_desc *desc)
अणु
	अचिन्हित लघु पूर्णांकs = amiga_custom.पूर्णांकreqr & amiga_custom.पूर्णांकenar;

	/* अगर a blitter पूर्णांकerrupt */
	अगर (पूर्णांकs & IF_BLIT) अणु
		amiga_custom.पूर्णांकreq = IF_BLIT;
		generic_handle_irq(IRQ_AMIGA_BLIT);
	पूर्ण

	/* अगर a copper पूर्णांकerrupt */
	अगर (पूर्णांकs & IF_COPER) अणु
		amiga_custom.पूर्णांकreq = IF_COPER;
		generic_handle_irq(IRQ_AMIGA_COPPER);
	पूर्ण

	/* अगर a vertical blank पूर्णांकerrupt */
	अगर (पूर्णांकs & IF_VERTB) अणु
		amiga_custom.पूर्णांकreq = IF_VERTB;
		generic_handle_irq(IRQ_AMIGA_VERTB);
	पूर्ण
पूर्ण

अटल व्योम ami_पूर्णांक4(काष्ठा irq_desc *desc)
अणु
	अचिन्हित लघु पूर्णांकs = amiga_custom.पूर्णांकreqr & amiga_custom.पूर्णांकenar;

	/* अगर audio 0 पूर्णांकerrupt */
	अगर (पूर्णांकs & IF_AUD0) अणु
		amiga_custom.पूर्णांकreq = IF_AUD0;
		generic_handle_irq(IRQ_AMIGA_AUD0);
	पूर्ण

	/* अगर audio 1 पूर्णांकerrupt */
	अगर (पूर्णांकs & IF_AUD1) अणु
		amiga_custom.पूर्णांकreq = IF_AUD1;
		generic_handle_irq(IRQ_AMIGA_AUD1);
	पूर्ण

	/* अगर audio 2 पूर्णांकerrupt */
	अगर (पूर्णांकs & IF_AUD2) अणु
		amiga_custom.पूर्णांकreq = IF_AUD2;
		generic_handle_irq(IRQ_AMIGA_AUD2);
	पूर्ण

	/* अगर audio 3 पूर्णांकerrupt */
	अगर (पूर्णांकs & IF_AUD3) अणु
		amiga_custom.पूर्णांकreq = IF_AUD3;
		generic_handle_irq(IRQ_AMIGA_AUD3);
	पूर्ण
पूर्ण

अटल व्योम ami_पूर्णांक5(काष्ठा irq_desc *desc)
अणु
	अचिन्हित लघु पूर्णांकs = amiga_custom.पूर्णांकreqr & amiga_custom.पूर्णांकenar;

	/* अगर serial receive buffer full पूर्णांकerrupt */
	अगर (पूर्णांकs & IF_RBF) अणु
		/* acknowledge of IF_RBF must be करोne by the serial पूर्णांकerrupt */
		generic_handle_irq(IRQ_AMIGA_RBF);
	पूर्ण

	/* अगर a disk sync पूर्णांकerrupt */
	अगर (पूर्णांकs & IF_DSKSYN) अणु
		amiga_custom.पूर्णांकreq = IF_DSKSYN;
		generic_handle_irq(IRQ_AMIGA_DSKSYN);
	पूर्ण
पूर्ण


/*
 * व्योम amiga_init_IRQ(व्योम)
 *
 * Parameters:	None
 *
 * Returns:	Nothing
 *
 * This function should be called during kernel startup to initialize
 * the amiga IRQ handling routines.
 */

व्योम __init amiga_init_IRQ(व्योम)
अणु
	m68k_setup_irq_controller(&amiga_irq_chip, handle_simple_irq, IRQ_USER,
				  AMI_STD_IRQS);

	irq_set_chained_handler(IRQ_AUTO_1, ami_पूर्णांक1);
	irq_set_chained_handler(IRQ_AUTO_3, ami_पूर्णांक3);
	irq_set_chained_handler(IRQ_AUTO_4, ami_पूर्णांक4);
	irq_set_chained_handler(IRQ_AUTO_5, ami_पूर्णांक5);

	/* turn off PCMCIA पूर्णांकerrupts */
	अगर (AMIGAHW_PRESENT(PCMCIA))
		gayle.पूर्णांकen = GAYLE_IRQ_IDE;

	/* turn off all पूर्णांकerrupts and enable the master पूर्णांकerrupt bit */
	amiga_custom.पूर्णांकena = 0x7fff;
	amiga_custom.पूर्णांकreq = 0x7fff;
	amiga_custom.पूर्णांकena = IF_SETCLR | IF_INTEN;

	cia_init_IRQ(&ciaa_base);
	cia_init_IRQ(&ciab_base);
पूर्ण
