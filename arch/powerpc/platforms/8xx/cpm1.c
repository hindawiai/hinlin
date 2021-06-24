<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * General Purpose functions क्रम the global management of the
 * Communication Processor Module.
 * Copyright (c) 1997 Dan error_act (dmalek@jlc.net)
 *
 * In addition to the inभागidual control of the communication
 * channels, there are a few functions that globally affect the
 * communication processor.
 *
 * Buffer descriptors must be allocated from the dual ported memory
 * space.  The allocator क्रम that is here.  When the communication
 * process is reset, we reclaim the memory available.  There is
 * currently no deallocator क्रम this memory.
 * The amount of space available is platक्रमm dependent.  On the
 * MBX, the EPPC software loads additional microcode पूर्णांकo the
 * communication processor, and uses some of the DP ram क्रम this
 * purpose.  Current, the first 512 bytes and the last 256 bytes of
 * memory are used.  Right now I am conservative and only use the
 * memory that can never be used क्रम microcode.  If there are
 * applications that require more DP ram, we can expand the boundaries
 * but then we have to be careful of any करोwnloaded microcode.
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/8xx_immap.h>
#समावेश <यंत्र/cpm1.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/rheap.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/cpm.h>

#समावेश <यंत्र/fs_pd.h>

#अगर_घोषित CONFIG_8xx_GPIO
#समावेश <linux/of_gpपन.स>
#पूर्ण_अगर

#घोषणा CPM_MAP_SIZE    (0x4000)

cpm8xx_t __iomem *cpmp;  /* Poपूर्णांकer to comm processor space */
immap_t __iomem *mpc8xx_immr = (व्योम __iomem *)VIRT_IMMR_BASE;
अटल cpic8xx_t __iomem *cpic_reg;

अटल काष्ठा irq_करोमुख्य *cpm_pic_host;

अटल व्योम cpm_mask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक cpm_vec = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);

	clrbits32(&cpic_reg->cpic_cimr, (1 << cpm_vec));
पूर्ण

अटल व्योम cpm_unmask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक cpm_vec = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);

	setbits32(&cpic_reg->cpic_cimr, (1 << cpm_vec));
पूर्ण

अटल व्योम cpm_end_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक cpm_vec = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);

	out_be32(&cpic_reg->cpic_cisr, (1 << cpm_vec));
पूर्ण

अटल काष्ठा irq_chip cpm_pic = अणु
	.name = "CPM PIC",
	.irq_mask = cpm_mask_irq,
	.irq_unmask = cpm_unmask_irq,
	.irq_eoi = cpm_end_irq,
पूर्ण;

पूर्णांक cpm_get_irq(व्योम)
अणु
	पूर्णांक cpm_vec;

	/*
	 * Get the vector by setting the ACK bit and then पढ़ोing
	 * the रेजिस्टर.
	 */
	out_be16(&cpic_reg->cpic_civr, 1);
	cpm_vec = in_be16(&cpic_reg->cpic_civr);
	cpm_vec >>= 11;

	वापस irq_linear_revmap(cpm_pic_host, cpm_vec);
पूर्ण

अटल पूर्णांक cpm_pic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			  irq_hw_number_t hw)
अणु
	pr_debug("cpm_pic_host_map(%d, 0x%lx)\n", virq, hw);

	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_chip_and_handler(virq, &cpm_pic, handle_fasteoi_irq);
	वापस 0;
पूर्ण

/*
 * The CPM can generate the error पूर्णांकerrupt when there is a race condition
 * between generating and masking पूर्णांकerrupts.  All we have to करो is ACK it
 * and वापस.  This is a no-op function so we करोn't need any special
 * tests in the पूर्णांकerrupt handler.
 */
अटल irqवापस_t cpm_error_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops cpm_pic_host_ops = अणु
	.map = cpm_pic_host_map,
पूर्ण;

अचिन्हित पूर्णांक __init cpm_pic_init(व्योम)
अणु
	काष्ठा device_node *np = शून्य;
	काष्ठा resource res;
	अचिन्हित पूर्णांक sirq = 0, hwirq, eirq;
	पूर्णांक ret;

	pr_debug("cpm_pic_init\n");

	np = of_find_compatible_node(शून्य, शून्य, "fsl,cpm1-pic");
	अगर (np == शून्य)
		np = of_find_compatible_node(शून्य, "cpm-pic", "CPM");
	अगर (np == शून्य) अणु
		prपूर्णांकk(KERN_ERR "CPM PIC init: can not find cpm-pic node\n");
		वापस sirq;
	पूर्ण

	ret = of_address_to_resource(np, 0, &res);
	अगर (ret)
		जाओ end;

	cpic_reg = ioremap(res.start, resource_size(&res));
	अगर (cpic_reg == शून्य)
		जाओ end;

	sirq = irq_of_parse_and_map(np, 0);
	अगर (!sirq)
		जाओ end;

	/* Initialize the CPM पूर्णांकerrupt controller. */
	hwirq = (अचिन्हित पूर्णांक)virq_to_hw(sirq);
	out_be32(&cpic_reg->cpic_cicr,
	    (CICR_SCD_SCC4 | CICR_SCC_SCC3 | CICR_SCB_SCC2 | CICR_SCA_SCC1) |
		((hwirq/2) << 13) | CICR_HP_MASK);

	out_be32(&cpic_reg->cpic_cimr, 0);

	cpm_pic_host = irq_करोमुख्य_add_linear(np, 64, &cpm_pic_host_ops, शून्य);
	अगर (cpm_pic_host == शून्य) अणु
		prपूर्णांकk(KERN_ERR "CPM2 PIC: failed to allocate irq host!\n");
		sirq = 0;
		जाओ end;
	पूर्ण

	/* Install our own error handler. */
	np = of_find_compatible_node(शून्य, शून्य, "fsl,cpm1");
	अगर (np == शून्य)
		np = of_find_node_by_type(शून्य, "cpm");
	अगर (np == शून्य) अणु
		prपूर्णांकk(KERN_ERR "CPM PIC init: can not find cpm node\n");
		जाओ end;
	पूर्ण

	eirq = irq_of_parse_and_map(np, 0);
	अगर (!eirq)
		जाओ end;

	अगर (request_irq(eirq, cpm_error_पूर्णांकerrupt, IRQF_NO_THREAD, "error",
			शून्य))
		prपूर्णांकk(KERN_ERR "Could not allocate CPM error IRQ!");

	setbits32(&cpic_reg->cpic_cicr, CICR_IEN);

end:
	of_node_put(np);
	वापस sirq;
पूर्ण

व्योम __init cpm_reset(व्योम)
अणु
	sysconf8xx_t __iomem *siu_conf;

	cpmp = &mpc8xx_immr->im_cpm;

#अगर_अघोषित CONFIG_PPC_EARLY_DEBUG_CPM
	/* Perक्रमm a reset. */
	out_be16(&cpmp->cp_cpcr, CPM_CR_RST | CPM_CR_FLG);

	/* Wait क्रम it. */
	जबतक (in_be16(&cpmp->cp_cpcr) & CPM_CR_FLG);
#पूर्ण_अगर

#अगर_घोषित CONFIG_UCODE_PATCH
	cpm_load_patch(cpmp);
#पूर्ण_अगर

	/*
	 * Set SDMA Bus Request priority 5.
	 * On 860T, this also enables FEC priority 6.  I am not sure
	 * this is what we really want क्रम some applications, but the
	 * manual recommends it.
	 * Bit 25, FAM can also be set to use FEC aggressive mode (860T).
	 */
	siu_conf = immr_map(im_siu_conf);
	अगर ((mfspr(SPRN_IMMR) & 0xffff) == 0x0900) /* MPC885 */
		out_be32(&siu_conf->sc_sdcr, 0x40);
	अन्यथा
		out_be32(&siu_conf->sc_sdcr, 1);
	immr_unmap(siu_conf);
पूर्ण

अटल DEFINE_SPINLOCK(cmd_lock);

#घोषणा MAX_CR_CMD_LOOPS        10000

पूर्णांक cpm_command(u32 command, u8 opcode)
अणु
	पूर्णांक i, ret;
	अचिन्हित दीर्घ flags;

	अगर (command & 0xffffff0f)
		वापस -EINVAL;

	spin_lock_irqsave(&cmd_lock, flags);

	ret = 0;
	out_be16(&cpmp->cp_cpcr, command | CPM_CR_FLG | (opcode << 8));
	क्रम (i = 0; i < MAX_CR_CMD_LOOPS; i++)
		अगर ((in_be16(&cpmp->cp_cpcr) & CPM_CR_FLG) == 0)
			जाओ out;

	prपूर्णांकk(KERN_ERR "%s(): Not able to issue CPM command\n", __func__);
	ret = -EIO;
out:
	spin_unlock_irqrestore(&cmd_lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(cpm_command);

/*
 * Set a baud rate generator.  This needs lots of work.  There are
 * four BRGs, any of which can be wired to any channel.
 * The पूर्णांकernal baud rate घड़ी is the प्रणाली घड़ी भागided by 16.
 * This assumes the baudrate is 16x oversampled by the uart.
 */
#घोषणा BRG_INT_CLK		(get_brgfreq())
#घोषणा BRG_UART_CLK		(BRG_INT_CLK/16)
#घोषणा BRG_UART_CLK_DIV16	(BRG_UART_CLK/16)

व्योम
cpm_setbrg(uपूर्णांक brg, uपूर्णांक rate)
अणु
	u32 __iomem *bp;

	/* This is good enough to get SMCs running..... */
	bp = &cpmp->cp_brgc1;
	bp += brg;
	/*
	 * The BRG has a 12-bit counter.  For really slow baud rates (or
	 * really fast processors), we may have to further भागide by 16.
	 */
	अगर (((BRG_UART_CLK / rate) - 1) < 4096)
		out_be32(bp, (((BRG_UART_CLK / rate) - 1) << 1) | CPM_BRG_EN);
	अन्यथा
		out_be32(bp, (((BRG_UART_CLK_DIV16 / rate) - 1) << 1) |
			      CPM_BRG_EN | CPM_BRG_DIV16);
पूर्ण

काष्ठा cpm_ioport16 अणु
	__be16 dir, par, odr_sor, dat, पूर्णांकr;
	__be16 res[3];
पूर्ण;

काष्ठा cpm_ioport32b अणु
	__be32 dir, par, odr, dat;
पूर्ण;

काष्ठा cpm_ioport32e अणु
	__be32 dir, par, sor, odr, dat;
पूर्ण;

अटल व्योम __init cpm1_set_pin32(पूर्णांक port, पूर्णांक pin, पूर्णांक flags)
अणु
	काष्ठा cpm_ioport32e __iomem *iop;
	pin = 1 << (31 - pin);

	अगर (port == CPM_PORTB)
		iop = (काष्ठा cpm_ioport32e __iomem *)
		      &mpc8xx_immr->im_cpm.cp_pbdir;
	अन्यथा
		iop = (काष्ठा cpm_ioport32e __iomem *)
		      &mpc8xx_immr->im_cpm.cp_pedir;

	अगर (flags & CPM_PIN_OUTPUT)
		setbits32(&iop->dir, pin);
	अन्यथा
		clrbits32(&iop->dir, pin);

	अगर (!(flags & CPM_PIN_GPIO))
		setbits32(&iop->par, pin);
	अन्यथा
		clrbits32(&iop->par, pin);

	अगर (port == CPM_PORTB) अणु
		अगर (flags & CPM_PIN_OPENDRAIN)
			setbits16(&mpc8xx_immr->im_cpm.cp_pbodr, pin);
		अन्यथा
			clrbits16(&mpc8xx_immr->im_cpm.cp_pbodr, pin);
	पूर्ण

	अगर (port == CPM_PORTE) अणु
		अगर (flags & CPM_PIN_SECONDARY)
			setbits32(&iop->sor, pin);
		अन्यथा
			clrbits32(&iop->sor, pin);

		अगर (flags & CPM_PIN_OPENDRAIN)
			setbits32(&mpc8xx_immr->im_cpm.cp_peodr, pin);
		अन्यथा
			clrbits32(&mpc8xx_immr->im_cpm.cp_peodr, pin);
	पूर्ण
पूर्ण

अटल व्योम __init cpm1_set_pin16(पूर्णांक port, पूर्णांक pin, पूर्णांक flags)
अणु
	काष्ठा cpm_ioport16 __iomem *iop =
		(काष्ठा cpm_ioport16 __iomem *)&mpc8xx_immr->im_ioport;

	pin = 1 << (15 - pin);

	अगर (port != 0)
		iop += port - 1;

	अगर (flags & CPM_PIN_OUTPUT)
		setbits16(&iop->dir, pin);
	अन्यथा
		clrbits16(&iop->dir, pin);

	अगर (!(flags & CPM_PIN_GPIO))
		setbits16(&iop->par, pin);
	अन्यथा
		clrbits16(&iop->par, pin);

	अगर (port == CPM_PORTA) अणु
		अगर (flags & CPM_PIN_OPENDRAIN)
			setbits16(&iop->odr_sor, pin);
		अन्यथा
			clrbits16(&iop->odr_sor, pin);
	पूर्ण
	अगर (port == CPM_PORTC) अणु
		अगर (flags & CPM_PIN_SECONDARY)
			setbits16(&iop->odr_sor, pin);
		अन्यथा
			clrbits16(&iop->odr_sor, pin);
		अगर (flags & CPM_PIN_FALLEDGE)
			setbits16(&iop->पूर्णांकr, pin);
		अन्यथा
			clrbits16(&iop->पूर्णांकr, pin);
	पूर्ण
पूर्ण

व्योम __init cpm1_set_pin(क्रमागत cpm_port port, पूर्णांक pin, पूर्णांक flags)
अणु
	अगर (port == CPM_PORTB || port == CPM_PORTE)
		cpm1_set_pin32(port, pin, flags);
	अन्यथा
		cpm1_set_pin16(port, pin, flags);
पूर्ण

पूर्णांक __init cpm1_clk_setup(क्रमागत cpm_clk_target target, पूर्णांक घड़ी, पूर्णांक mode)
अणु
	पूर्णांक shअगरt;
	पूर्णांक i, bits = 0;
	u32 __iomem *reg;
	u32 mask = 7;

	u8 clk_map[][3] = अणु
		अणुCPM_CLK_SCC1, CPM_BRG1, 0पूर्ण,
		अणुCPM_CLK_SCC1, CPM_BRG2, 1पूर्ण,
		अणुCPM_CLK_SCC1, CPM_BRG3, 2पूर्ण,
		अणुCPM_CLK_SCC1, CPM_BRG4, 3पूर्ण,
		अणुCPM_CLK_SCC1, CPM_CLK1, 4पूर्ण,
		अणुCPM_CLK_SCC1, CPM_CLK2, 5पूर्ण,
		अणुCPM_CLK_SCC1, CPM_CLK3, 6पूर्ण,
		अणुCPM_CLK_SCC1, CPM_CLK4, 7पूर्ण,

		अणुCPM_CLK_SCC2, CPM_BRG1, 0पूर्ण,
		अणुCPM_CLK_SCC2, CPM_BRG2, 1पूर्ण,
		अणुCPM_CLK_SCC2, CPM_BRG3, 2पूर्ण,
		अणुCPM_CLK_SCC2, CPM_BRG4, 3पूर्ण,
		अणुCPM_CLK_SCC2, CPM_CLK1, 4पूर्ण,
		अणुCPM_CLK_SCC2, CPM_CLK2, 5पूर्ण,
		अणुCPM_CLK_SCC2, CPM_CLK3, 6पूर्ण,
		अणुCPM_CLK_SCC2, CPM_CLK4, 7पूर्ण,

		अणुCPM_CLK_SCC3, CPM_BRG1, 0पूर्ण,
		अणुCPM_CLK_SCC3, CPM_BRG2, 1पूर्ण,
		अणुCPM_CLK_SCC3, CPM_BRG3, 2पूर्ण,
		अणुCPM_CLK_SCC3, CPM_BRG4, 3पूर्ण,
		अणुCPM_CLK_SCC3, CPM_CLK5, 4पूर्ण,
		अणुCPM_CLK_SCC3, CPM_CLK6, 5पूर्ण,
		अणुCPM_CLK_SCC3, CPM_CLK7, 6पूर्ण,
		अणुCPM_CLK_SCC3, CPM_CLK8, 7पूर्ण,

		अणुCPM_CLK_SCC4, CPM_BRG1, 0पूर्ण,
		अणुCPM_CLK_SCC4, CPM_BRG2, 1पूर्ण,
		अणुCPM_CLK_SCC4, CPM_BRG3, 2पूर्ण,
		अणुCPM_CLK_SCC4, CPM_BRG4, 3पूर्ण,
		अणुCPM_CLK_SCC4, CPM_CLK5, 4पूर्ण,
		अणुCPM_CLK_SCC4, CPM_CLK6, 5पूर्ण,
		अणुCPM_CLK_SCC4, CPM_CLK7, 6पूर्ण,
		अणुCPM_CLK_SCC4, CPM_CLK8, 7पूर्ण,

		अणुCPM_CLK_SMC1, CPM_BRG1, 0पूर्ण,
		अणुCPM_CLK_SMC1, CPM_BRG2, 1पूर्ण,
		अणुCPM_CLK_SMC1, CPM_BRG3, 2पूर्ण,
		अणुCPM_CLK_SMC1, CPM_BRG4, 3पूर्ण,
		अणुCPM_CLK_SMC1, CPM_CLK1, 4पूर्ण,
		अणुCPM_CLK_SMC1, CPM_CLK2, 5पूर्ण,
		अणुCPM_CLK_SMC1, CPM_CLK3, 6पूर्ण,
		अणुCPM_CLK_SMC1, CPM_CLK4, 7पूर्ण,

		अणुCPM_CLK_SMC2, CPM_BRG1, 0पूर्ण,
		अणुCPM_CLK_SMC2, CPM_BRG2, 1पूर्ण,
		अणुCPM_CLK_SMC2, CPM_BRG3, 2पूर्ण,
		अणुCPM_CLK_SMC2, CPM_BRG4, 3पूर्ण,
		अणुCPM_CLK_SMC2, CPM_CLK5, 4पूर्ण,
		अणुCPM_CLK_SMC2, CPM_CLK6, 5पूर्ण,
		अणुCPM_CLK_SMC2, CPM_CLK7, 6पूर्ण,
		अणुCPM_CLK_SMC2, CPM_CLK8, 7पूर्ण,
	पूर्ण;

	चयन (target) अणु
	हाल CPM_CLK_SCC1:
		reg = &mpc8xx_immr->im_cpm.cp_sicr;
		shअगरt = 0;
		अवरोध;

	हाल CPM_CLK_SCC2:
		reg = &mpc8xx_immr->im_cpm.cp_sicr;
		shअगरt = 8;
		अवरोध;

	हाल CPM_CLK_SCC3:
		reg = &mpc8xx_immr->im_cpm.cp_sicr;
		shअगरt = 16;
		अवरोध;

	हाल CPM_CLK_SCC4:
		reg = &mpc8xx_immr->im_cpm.cp_sicr;
		shअगरt = 24;
		अवरोध;

	हाल CPM_CLK_SMC1:
		reg = &mpc8xx_immr->im_cpm.cp_simode;
		shअगरt = 12;
		अवरोध;

	हाल CPM_CLK_SMC2:
		reg = &mpc8xx_immr->im_cpm.cp_simode;
		shअगरt = 28;
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "cpm1_clock_setup: invalid clock target\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(clk_map); i++) अणु
		अगर (clk_map[i][0] == target && clk_map[i][1] == घड़ी) अणु
			bits = clk_map[i][2];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(clk_map)) अणु
		prपूर्णांकk(KERN_ERR "cpm1_clock_setup: invalid clock combination\n");
		वापस -EINVAL;
	पूर्ण

	bits <<= shअगरt;
	mask <<= shअगरt;

	अगर (reg == &mpc8xx_immr->im_cpm.cp_sicr) अणु
		अगर (mode == CPM_CLK_RTX) अणु
			bits |= bits << 3;
			mask |= mask << 3;
		पूर्ण अन्यथा अगर (mode == CPM_CLK_RX) अणु
			bits <<= 3;
			mask <<= 3;
		पूर्ण
	पूर्ण

	out_be32(reg, (in_be32(reg) & ~mask) | bits);

	वापस 0;
पूर्ण

/*
 * GPIO LIB API implementation
 */
#अगर_घोषित CONFIG_8xx_GPIO

काष्ठा cpm1_gpio16_chip अणु
	काष्ठा of_mm_gpio_chip mm_gc;
	spinlock_t lock;

	/* shaकरोwed data रेजिस्टर to clear/set bits safely */
	u16 cpdata;

	/* IRQ associated with Pins when relevant */
	पूर्णांक irq[16];
पूर्ण;

अटल व्योम cpm1_gpio16_save_regs(काष्ठा of_mm_gpio_chip *mm_gc)
अणु
	काष्ठा cpm1_gpio16_chip *cpm1_gc =
		container_of(mm_gc, काष्ठा cpm1_gpio16_chip, mm_gc);
	काष्ठा cpm_ioport16 __iomem *iop = mm_gc->regs;

	cpm1_gc->cpdata = in_be16(&iop->dat);
पूर्ण

अटल पूर्णांक cpm1_gpio16_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा cpm_ioport16 __iomem *iop = mm_gc->regs;
	u16 pin_mask;

	pin_mask = 1 << (15 - gpio);

	वापस !!(in_be16(&iop->dat) & pin_mask);
पूर्ण

अटल व्योम __cpm1_gpio16_set(काष्ठा of_mm_gpio_chip *mm_gc, u16 pin_mask,
	पूर्णांक value)
अणु
	काष्ठा cpm1_gpio16_chip *cpm1_gc = gpiochip_get_data(&mm_gc->gc);
	काष्ठा cpm_ioport16 __iomem *iop = mm_gc->regs;

	अगर (value)
		cpm1_gc->cpdata |= pin_mask;
	अन्यथा
		cpm1_gc->cpdata &= ~pin_mask;

	out_be16(&iop->dat, cpm1_gc->cpdata);
पूर्ण

अटल व्योम cpm1_gpio16_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक value)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा cpm1_gpio16_chip *cpm1_gc = gpiochip_get_data(&mm_gc->gc);
	अचिन्हित दीर्घ flags;
	u16 pin_mask = 1 << (15 - gpio);

	spin_lock_irqsave(&cpm1_gc->lock, flags);

	__cpm1_gpio16_set(mm_gc, pin_mask, value);

	spin_unlock_irqrestore(&cpm1_gc->lock, flags);
पूर्ण

अटल पूर्णांक cpm1_gpio16_to_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा cpm1_gpio16_chip *cpm1_gc = gpiochip_get_data(&mm_gc->gc);

	वापस cpm1_gc->irq[gpio] ? : -ENXIO;
पूर्ण

अटल पूर्णांक cpm1_gpio16_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा cpm1_gpio16_chip *cpm1_gc = gpiochip_get_data(&mm_gc->gc);
	काष्ठा cpm_ioport16 __iomem *iop = mm_gc->regs;
	अचिन्हित दीर्घ flags;
	u16 pin_mask = 1 << (15 - gpio);

	spin_lock_irqsave(&cpm1_gc->lock, flags);

	setbits16(&iop->dir, pin_mask);
	__cpm1_gpio16_set(mm_gc, pin_mask, val);

	spin_unlock_irqrestore(&cpm1_gc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक cpm1_gpio16_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा cpm1_gpio16_chip *cpm1_gc = gpiochip_get_data(&mm_gc->gc);
	काष्ठा cpm_ioport16 __iomem *iop = mm_gc->regs;
	अचिन्हित दीर्घ flags;
	u16 pin_mask = 1 << (15 - gpio);

	spin_lock_irqsave(&cpm1_gc->lock, flags);

	clrbits16(&iop->dir, pin_mask);

	spin_unlock_irqrestore(&cpm1_gc->lock, flags);

	वापस 0;
पूर्ण

पूर्णांक cpm1_gpiochip_add16(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा cpm1_gpio16_chip *cpm1_gc;
	काष्ठा of_mm_gpio_chip *mm_gc;
	काष्ठा gpio_chip *gc;
	u16 mask;

	cpm1_gc = kzalloc(माप(*cpm1_gc), GFP_KERNEL);
	अगर (!cpm1_gc)
		वापस -ENOMEM;

	spin_lock_init(&cpm1_gc->lock);

	अगर (!of_property_पढ़ो_u16(np, "fsl,cpm1-gpio-irq-mask", &mask)) अणु
		पूर्णांक i, j;

		क्रम (i = 0, j = 0; i < 16; i++)
			अगर (mask & (1 << (15 - i)))
				cpm1_gc->irq[i] = irq_of_parse_and_map(np, j++);
	पूर्ण

	mm_gc = &cpm1_gc->mm_gc;
	gc = &mm_gc->gc;

	mm_gc->save_regs = cpm1_gpio16_save_regs;
	gc->ngpio = 16;
	gc->direction_input = cpm1_gpio16_dir_in;
	gc->direction_output = cpm1_gpio16_dir_out;
	gc->get = cpm1_gpio16_get;
	gc->set = cpm1_gpio16_set;
	gc->to_irq = cpm1_gpio16_to_irq;
	gc->parent = dev;
	gc->owner = THIS_MODULE;

	वापस of_mm_gpiochip_add_data(np, mm_gc, cpm1_gc);
पूर्ण

काष्ठा cpm1_gpio32_chip अणु
	काष्ठा of_mm_gpio_chip mm_gc;
	spinlock_t lock;

	/* shaकरोwed data रेजिस्टर to clear/set bits safely */
	u32 cpdata;
पूर्ण;

अटल व्योम cpm1_gpio32_save_regs(काष्ठा of_mm_gpio_chip *mm_gc)
अणु
	काष्ठा cpm1_gpio32_chip *cpm1_gc =
		container_of(mm_gc, काष्ठा cpm1_gpio32_chip, mm_gc);
	काष्ठा cpm_ioport32b __iomem *iop = mm_gc->regs;

	cpm1_gc->cpdata = in_be32(&iop->dat);
पूर्ण

अटल पूर्णांक cpm1_gpio32_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा cpm_ioport32b __iomem *iop = mm_gc->regs;
	u32 pin_mask;

	pin_mask = 1 << (31 - gpio);

	वापस !!(in_be32(&iop->dat) & pin_mask);
पूर्ण

अटल व्योम __cpm1_gpio32_set(काष्ठा of_mm_gpio_chip *mm_gc, u32 pin_mask,
	पूर्णांक value)
अणु
	काष्ठा cpm1_gpio32_chip *cpm1_gc = gpiochip_get_data(&mm_gc->gc);
	काष्ठा cpm_ioport32b __iomem *iop = mm_gc->regs;

	अगर (value)
		cpm1_gc->cpdata |= pin_mask;
	अन्यथा
		cpm1_gc->cpdata &= ~pin_mask;

	out_be32(&iop->dat, cpm1_gc->cpdata);
पूर्ण

अटल व्योम cpm1_gpio32_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक value)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा cpm1_gpio32_chip *cpm1_gc = gpiochip_get_data(&mm_gc->gc);
	अचिन्हित दीर्घ flags;
	u32 pin_mask = 1 << (31 - gpio);

	spin_lock_irqsave(&cpm1_gc->lock, flags);

	__cpm1_gpio32_set(mm_gc, pin_mask, value);

	spin_unlock_irqrestore(&cpm1_gc->lock, flags);
पूर्ण

अटल पूर्णांक cpm1_gpio32_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा cpm1_gpio32_chip *cpm1_gc = gpiochip_get_data(&mm_gc->gc);
	काष्ठा cpm_ioport32b __iomem *iop = mm_gc->regs;
	अचिन्हित दीर्घ flags;
	u32 pin_mask = 1 << (31 - gpio);

	spin_lock_irqsave(&cpm1_gc->lock, flags);

	setbits32(&iop->dir, pin_mask);
	__cpm1_gpio32_set(mm_gc, pin_mask, val);

	spin_unlock_irqrestore(&cpm1_gc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक cpm1_gpio32_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा cpm1_gpio32_chip *cpm1_gc = gpiochip_get_data(&mm_gc->gc);
	काष्ठा cpm_ioport32b __iomem *iop = mm_gc->regs;
	अचिन्हित दीर्घ flags;
	u32 pin_mask = 1 << (31 - gpio);

	spin_lock_irqsave(&cpm1_gc->lock, flags);

	clrbits32(&iop->dir, pin_mask);

	spin_unlock_irqrestore(&cpm1_gc->lock, flags);

	वापस 0;
पूर्ण

पूर्णांक cpm1_gpiochip_add32(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा cpm1_gpio32_chip *cpm1_gc;
	काष्ठा of_mm_gpio_chip *mm_gc;
	काष्ठा gpio_chip *gc;

	cpm1_gc = kzalloc(माप(*cpm1_gc), GFP_KERNEL);
	अगर (!cpm1_gc)
		वापस -ENOMEM;

	spin_lock_init(&cpm1_gc->lock);

	mm_gc = &cpm1_gc->mm_gc;
	gc = &mm_gc->gc;

	mm_gc->save_regs = cpm1_gpio32_save_regs;
	gc->ngpio = 32;
	gc->direction_input = cpm1_gpio32_dir_in;
	gc->direction_output = cpm1_gpio32_dir_out;
	gc->get = cpm1_gpio32_get;
	gc->set = cpm1_gpio32_set;
	gc->parent = dev;
	gc->owner = THIS_MODULE;

	वापस of_mm_gpiochip_add_data(np, mm_gc, cpm1_gc);
पूर्ण

#पूर्ण_अगर /* CONFIG_8xx_GPIO */
