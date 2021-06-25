<शैली गुरु>
/*
 * Basic EISA bus support क्रम the SGI Indigo-2.
 *
 * (C) 2002 Pascal Dameme <netinet@मुक्तsurf.fr>
 *	and Marc Zyngier <mzyngier@मुक्तsurf.fr>
 *
 * This code is released under both the GPL version 2 and BSD
 * licenses.  Either license may be used.
 *
 * This code offers a very basic support क्रम this EISA bus present in
 * the SGI Indigo-2. It currently only supports PIO (क्रमget about DMA
 * क्रम the समय being). This is enough क्रम a low-end ethernet card,
 * but क्रमget about your favorite SCSI card...
 *
 * TODO :
 * - Fix bugs...
 * - Add ISA support
 * - Add DMA (yeah, right...).
 * - Fix more bugs.
 */

#समावेश <linux/eisa.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sgi/ioc.h>
#समावेश <यंत्र/sgi/mc.h>
#समावेश <यंत्र/sgi/ip22.h>
#समावेश <यंत्र/i8259.h>

/* I2 has four EISA slots. */
#घोषणा IP22_EISA_MAX_SLOTS	  4
#घोषणा EISA_MAX_IRQ		 16

#घोषणा EIU_MODE_REG	 0x0001ffc0
#घोषणा EIU_STAT_REG	 0x0001ffc4
#घोषणा EIU_PREMPT_REG	 0x0001ffc8
#घोषणा EIU_QUIET_REG	 0x0001ffcc
#घोषणा EIU_INTRPT_ACK	 0x00010004

अटल अक्षर __init *decode_eisa_sig(अचिन्हित दीर्घ addr)
अणु
	अटल अक्षर sig_str[EISA_SIG_LEN] __initdata;
	u8 sig[4];
	u16 rev;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		sig[i] = inb(addr + i);

		अगर (!i && (sig[0] & 0x80))
			वापस शून्य;
	पूर्ण

	sig_str[0] = ((sig[0] >> 2) & 0x1f) + ('A' - 1);
	sig_str[1] = (((sig[0] & 3) << 3) | (sig[1] >> 5)) + ('A' - 1);
	sig_str[2] = (sig[1] & 0x1f) + ('A' - 1);
	rev = (sig[2] << 8) | sig[3];
	प्र_लिखो(sig_str + 3, "%04X", rev);

	वापस sig_str;
पूर्ण

अटल irqवापस_t ip22_eisa_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	u8 eisa_irq = inb(EIU_INTRPT_ACK);

	inb(EISA_DMA1_STATUS);
	inb(EISA_DMA2_STATUS);

	अगर (eisa_irq < EISA_MAX_IRQ) अणु
		करो_IRQ(eisa_irq);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Oops, Bad Stuff Happened... */
	prपूर्णांकk(KERN_ERR "eisa_irq %d out of bound\n", eisa_irq);

	outb(0x20, EISA_INT2_CTRL);
	outb(0x20, EISA_INT1_CTRL);

	वापस IRQ_NONE;
पूर्ण

पूर्णांक __init ip22_eisa_init(व्योम)
अणु
	पूर्णांक i, c;
	अक्षर *str;

	अगर (!(sgimc->प्रणालीid & SGIMC_SYSID_EPRESENT)) अणु
		prपूर्णांकk(KERN_INFO "EISA: bus not present.\n");
		वापस 1;
	पूर्ण

	prपूर्णांकk(KERN_INFO "EISA: Probing bus...\n");
	क्रम (c = 0, i = 1; i <= IP22_EISA_MAX_SLOTS; i++) अणु
		अगर ((str = decode_eisa_sig(0x1000 * i + EISA_VENDOR_ID_OFFSET))) अणु
			prपूर्णांकk(KERN_INFO "EISA: slot %d : %s detected.\n",
			       i, str);
			c++;
		पूर्ण
	पूर्ण
	prपूर्णांकk(KERN_INFO "EISA: Detected %d card%s.\n", c, c < 2 ? "" : "s");
#अगर_घोषित CONFIG_ISA
	prपूर्णांकk(KERN_INFO "ISA support compiled in.\n");
#पूर्ण_अगर

	/* Warning : BlackMagicAhead(पंचांग).
	   Please wave your favorite dead chicken over the busses */

	/* First say hello to the EIU */
	outl(0x0000FFFF, EIU_PREMPT_REG);
	outl(1, EIU_QUIET_REG);
	outl(0x40f3c07F, EIU_MODE_REG);

	/* Now be nice to the EISA chipset */
	outb(1, EISA_EXT_NMI_RESET_CTRL);
	udelay(50);	/* Wait दीर्घ enough क्रम the dust to settle */
	outb(0, EISA_EXT_NMI_RESET_CTRL);
	outb(0, EISA_DMA2_WRITE_SINGLE);

	init_i8259_irqs();

	अगर (request_irq(SGI_EISA_IRQ, ip22_eisa_पूर्णांकr, 0, "EISA", शून्य))
		pr_err("Failed to request irq %d (EISA)\n", SGI_EISA_IRQ);

	EISA_bus = 1;
	वापस 0;
पूर्ण
