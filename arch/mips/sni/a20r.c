<शैली गुरु>
/*
 * A20R specअगरic code
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2006 Thomas Bogenकरोerfer (tsbogend@alpha.franken.de)
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_8250.h>

#समावेश <यंत्र/sni.h>
#समावेश <यंत्र/समय.स>

#घोषणा PORT(_base,_irq)				\
	अणु						\
		.iobase		= _base,		\
		.irq		= _irq,			\
		.uartclk	= 1843200,		\
		.iotype		= UPIO_PORT,		\
		.flags		= UPF_BOOT_AUTOCONF,	\
	पूर्ण

अटल काष्ठा plat_serial8250_port a20r_data[] = अणु
	PORT(0x3f8, 4),
	PORT(0x2f8, 3),
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device a20r_serial8250_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= a20r_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource a20r_ds1216_rsrc[] = अणु
	अणु
		.start = 0x1c081ffc,
		.end   = 0x1c081fff,
		.flags = IORESOURCE_MEM
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device a20r_ds1216_device = अणु
	.name		= "rtc-ds1216",
	.num_resources	= ARRAY_SIZE(a20r_ds1216_rsrc),
	.resource	= a20r_ds1216_rsrc
पूर्ण;

अटल काष्ठा resource snirm_82596_rsrc[] = अणु
	अणु
		.start = 0x18000000,
		.end   = 0x18000004,
		.flags = IORESOURCE_MEM
	पूर्ण,
	अणु
		.start = 0x18010000,
		.end   = 0x18010004,
		.flags = IORESOURCE_MEM
	पूर्ण,
	अणु
		.start = 0x1ff00000,
		.end   = 0x1ff00020,
		.flags = IORESOURCE_MEM
	पूर्ण,
	अणु
		.start = 22,
		.end   = 22,
		.flags = IORESOURCE_IRQ
	पूर्ण,
	अणु
		.flags = 0x01		     /* 16bit mpu port access */
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device snirm_82596_pdev = अणु
	.name		= "snirm_82596",
	.num_resources	= ARRAY_SIZE(snirm_82596_rsrc),
	.resource	= snirm_82596_rsrc
पूर्ण;

अटल काष्ठा resource snirm_53c710_rsrc[] = अणु
	अणु
		.start = 0x19000000,
		.end   = 0x190fffff,
		.flags = IORESOURCE_MEM
	पूर्ण,
	अणु
		.start = 19,
		.end   = 19,
		.flags = IORESOURCE_IRQ
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device snirm_53c710_pdev = अणु
	.name		= "snirm_53c710",
	.num_resources	= ARRAY_SIZE(snirm_53c710_rsrc),
	.resource	= snirm_53c710_rsrc
पूर्ण;

अटल काष्ठा resource sc26xx_rsrc[] = अणु
	अणु
		.start = 0x1c070000,
		.end   = 0x1c0700ff,
		.flags = IORESOURCE_MEM
	पूर्ण,
	अणु
		.start = 20,
		.end   = 20,
		.flags = IORESOURCE_IRQ
	पूर्ण
पूर्ण;

#समावेश <linux/platक्रमm_data/serial-sccnxp.h>

अटल काष्ठा sccnxp_pdata sccnxp_data = अणु
	.reg_shअगरt	= 2,
	.mctrl_cfg[0]	= MCTRL_SIG(DTR_OP, LINE_OP7) |
			  MCTRL_SIG(RTS_OP, LINE_OP3) |
			  MCTRL_SIG(DSR_IP, LINE_IP5) |
			  MCTRL_SIG(DCD_IP, LINE_IP6),
	.mctrl_cfg[1]	= MCTRL_SIG(DTR_OP, LINE_OP2) |
			  MCTRL_SIG(RTS_OP, LINE_OP1) |
			  MCTRL_SIG(DSR_IP, LINE_IP0) |
			  MCTRL_SIG(CTS_IP, LINE_IP1) |
			  MCTRL_SIG(DCD_IP, LINE_IP2) |
			  MCTRL_SIG(RNG_IP, LINE_IP3),
पूर्ण;

अटल काष्ठा platक्रमm_device sc26xx_pdev = अणु
	.name		= "sc2681",
	.resource	= sc26xx_rsrc,
	.num_resources	= ARRAY_SIZE(sc26xx_rsrc),
	.dev	= अणु
		.platक्रमm_data	= &sccnxp_data,
	पूर्ण,
पूर्ण;

/*
 * Trigger chipset to update CPU's CAUSE IP field
 */
अटल u32 a20r_update_cause_ip(व्योम)
अणु
	u32 status = पढ़ो_c0_status();

	ग_लिखो_c0_status(status | 0x00010000);
	यंत्र अस्थिर(
	"	.set	push			\n"
	"	.set	noat			\n"
	"	.set	noreorder		\n"
	"	lw	$1, 0(%0)		\n"
	"	sb	$0, 0(%1)		\n"
	"	sync				\n"
	"	lb	%1, 0(%1)		\n"
	"	b	1f			\n"
	"	ori	%1, $1, 2		\n"
	"	.align	8			\n"
	"1:					\n"
	"	nop				\n"
	"	sw	%1, 0(%0)		\n"
	"	sync				\n"
	"	li	%1, 0x20		\n"
	"2:					\n"
	"	nop				\n"
	"	bnez	%1,2b			\n"
	"	addiu	%1, -1			\n"
	"	sw	$1, 0(%0)		\n"
	"	sync				\n"
		".set	pop			\n"
	:
	: "Jr" (PCIMT_UCONF), "Jr" (0xbc000000));
	ग_लिखो_c0_status(status);

	वापस status;
पूर्ण

अटल अंतरभूत व्योम unmask_a20r_irq(काष्ठा irq_data *d)
अणु
	set_c0_status(0x100 << (d->irq - SNI_A20R_IRQ_BASE));
	irq_enable_hazard();
पूर्ण

अटल अंतरभूत व्योम mask_a20r_irq(काष्ठा irq_data *d)
अणु
	clear_c0_status(0x100 << (d->irq - SNI_A20R_IRQ_BASE));
	irq_disable_hazard();
पूर्ण

अटल काष्ठा irq_chip a20r_irq_type = अणु
	.name		= "A20R",
	.irq_mask	= mask_a20r_irq,
	.irq_unmask	= unmask_a20r_irq,
पूर्ण;

/*
 * hwपूर्णांक 0 receive all पूर्णांकerrupts
 */
अटल व्योम a20r_hwपूर्णांक(व्योम)
अणु
	u32 cause, status;
	पूर्णांक irq;

	clear_c0_status(IE_IRQ0);
	status = a20r_update_cause_ip();
	cause = पढ़ो_c0_cause();

	irq = ffs(((cause & status) >> 8) & 0xf8);
	अगर (likely(irq > 0))
		करो_IRQ(SNI_A20R_IRQ_BASE + irq - 1);

	a20r_update_cause_ip();
	set_c0_status(IE_IRQ0);
पूर्ण

व्योम __init sni_a20r_irq_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = SNI_A20R_IRQ_BASE + 2 ; i < SNI_A20R_IRQ_BASE + 8; i++)
		irq_set_chip_and_handler(i, &a20r_irq_type, handle_level_irq);
	sni_hwपूर्णांक = a20r_hwपूर्णांक;
	change_c0_status(ST0_IM, IE_IRQ0);
	अगर (request_irq(SNI_A20R_IRQ_BASE + 3, sni_isa_irq_handler,
			IRQF_SHARED, "ISA", sni_isa_irq_handler))
		pr_err("Failed to register ISA interrupt\n");
पूर्ण

व्योम sni_a20r_init(व्योम)
अणु
	/* FIXME, हटाओ अगर not needed */
पूर्ण

अटल पूर्णांक __init snirm_a20r_setup_devinit(व्योम)
अणु
	चयन (sni_brd_type) अणु
	हाल SNI_BRD_TOWER_OASIC:
	हाल SNI_BRD_MINITOWER:
		platक्रमm_device_रेजिस्टर(&snirm_82596_pdev);
		platक्रमm_device_रेजिस्टर(&snirm_53c710_pdev);
		platक्रमm_device_रेजिस्टर(&sc26xx_pdev);
		platक्रमm_device_रेजिस्टर(&a20r_serial8250_device);
		platक्रमm_device_रेजिस्टर(&a20r_ds1216_device);
		sni_eisa_root_init();
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

device_initcall(snirm_a20r_setup_devinit);
