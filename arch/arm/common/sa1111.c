<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/common/sa1111.c
 *
 * SA1111 support
 *
 * Original code by John Dorsey
 *
 * This file contains all generic SA1111 support.
 *
 * All initialization functions provided here are पूर्णांकended to be called
 * from machine specअगरic code with proper arguments when required.
 */
#समावेश <linux/module.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/hardware/sa1111.h>

/* SA1111 IRQs */
#घोषणा IRQ_GPAIN0		(0)
#घोषणा IRQ_GPAIN1		(1)
#घोषणा IRQ_GPAIN2		(2)
#घोषणा IRQ_GPAIN3		(3)
#घोषणा IRQ_GPBIN0		(4)
#घोषणा IRQ_GPBIN1		(5)
#घोषणा IRQ_GPBIN2		(6)
#घोषणा IRQ_GPBIN3		(7)
#घोषणा IRQ_GPBIN4		(8)
#घोषणा IRQ_GPBIN5		(9)
#घोषणा IRQ_GPCIN0		(10)
#घोषणा IRQ_GPCIN1		(11)
#घोषणा IRQ_GPCIN2		(12)
#घोषणा IRQ_GPCIN3		(13)
#घोषणा IRQ_GPCIN4		(14)
#घोषणा IRQ_GPCIN5		(15)
#घोषणा IRQ_GPCIN6		(16)
#घोषणा IRQ_GPCIN7		(17)
#घोषणा IRQ_MSTXINT		(18)
#घोषणा IRQ_MSRXINT		(19)
#घोषणा IRQ_MSSTOPERRINT	(20)
#घोषणा IRQ_TPTXINT		(21)
#घोषणा IRQ_TPRXINT		(22)
#घोषणा IRQ_TPSTOPERRINT	(23)
#घोषणा SSPXMTINT		(24)
#घोषणा SSPRCVINT		(25)
#घोषणा SSPROR			(26)
#घोषणा AUDXMTDMADONEA		(32)
#घोषणा AUDRCVDMADONEA		(33)
#घोषणा AUDXMTDMADONEB		(34)
#घोषणा AUDRCVDMADONEB		(35)
#घोषणा AUDTFSR			(36)
#घोषणा AUDRFSR			(37)
#घोषणा AUDTUR			(38)
#घोषणा AUDROR			(39)
#घोषणा AUDDTS			(40)
#घोषणा AUDRDD			(41)
#घोषणा AUDSTO			(42)
#घोषणा IRQ_USBPWR		(43)
#घोषणा IRQ_HCIM		(44)
#घोषणा IRQ_HCIBUFFACC		(45)
#घोषणा IRQ_HCIRMTWKP		(46)
#घोषणा IRQ_NHCIMFCIR		(47)
#घोषणा IRQ_USB_PORT_RESUME	(48)
#घोषणा IRQ_S0_READY_NINT	(49)
#घोषणा IRQ_S1_READY_NINT	(50)
#घोषणा IRQ_S0_CD_VALID		(51)
#घोषणा IRQ_S1_CD_VALID		(52)
#घोषणा IRQ_S0_BVD1_STSCHG	(53)
#घोषणा IRQ_S1_BVD1_STSCHG	(54)
#घोषणा SA1111_IRQ_NR		(55)

बाह्य व्योम sa1110_mb_enable(व्योम);
बाह्य व्योम sa1110_mb_disable(व्योम);

/*
 * We keep the following data क्रम the overall SA1111.  Note that the
 * काष्ठा device and काष्ठा resource are "fake"; they should be supplied
 * by the bus above us.  However, in the पूर्णांकerests of getting all SA1111
 * drivers converted over to the device model, we provide this as an
 * anchor poपूर्णांक क्रम all the other drivers.
 */
काष्ठा sa1111 अणु
	काष्ठा device	*dev;
	काष्ठा clk	*clk;
	अचिन्हित दीर्घ	phys;
	पूर्णांक		irq;
	पूर्णांक		irq_base;	/* base क्रम cascaded on-chip IRQs */
	spinlock_t	lock;
	व्योम __iomem	*base;
	काष्ठा sa1111_platक्रमm_data *pdata;
	काष्ठा irq_करोमुख्य *irqकरोमुख्य;
	काष्ठा gpio_chip gc;
#अगर_घोषित CONFIG_PM
	व्योम		*saved_state;
#पूर्ण_अगर
पूर्ण;

/*
 * We _really_ need to eliminate this.  Its only users
 * are the PWM and DMA checking code.
 */
अटल काष्ठा sa1111 *g_sa1111;

काष्ठा sa1111_dev_info अणु
	अचिन्हित दीर्घ	offset;
	अचिन्हित दीर्घ	skpcr_mask;
	bool		dma;
	अचिन्हित पूर्णांक	devid;
	अचिन्हित पूर्णांक	hwirq[6];
पूर्ण;

अटल काष्ठा sa1111_dev_info sa1111_devices[] = अणु
	अणु
		.offset		= SA1111_USB,
		.skpcr_mask	= SKPCR_UCLKEN,
		.dma		= true,
		.devid		= SA1111_DEVID_USB,
		.hwirq = अणु
			IRQ_USBPWR,
			IRQ_HCIM,
			IRQ_HCIBUFFACC,
			IRQ_HCIRMTWKP,
			IRQ_NHCIMFCIR,
			IRQ_USB_PORT_RESUME
		पूर्ण,
	पूर्ण,
	अणु
		.offset		= 0x0600,
		.skpcr_mask	= SKPCR_I2SCLKEN | SKPCR_L3CLKEN,
		.dma		= true,
		.devid		= SA1111_DEVID_SAC,
		.hwirq = अणु
			AUDXMTDMADONEA,
			AUDXMTDMADONEB,
			AUDRCVDMADONEA,
			AUDRCVDMADONEB
		पूर्ण,
	पूर्ण,
	अणु
		.offset		= 0x0800,
		.skpcr_mask	= SKPCR_SCLKEN,
		.devid		= SA1111_DEVID_SSP,
	पूर्ण,
	अणु
		.offset		= SA1111_KBD,
		.skpcr_mask	= SKPCR_PTCLKEN,
		.devid		= SA1111_DEVID_PS2_KBD,
		.hwirq = अणु
			IRQ_TPRXINT,
			IRQ_TPTXINT
		पूर्ण,
	पूर्ण,
	अणु
		.offset		= SA1111_MSE,
		.skpcr_mask	= SKPCR_PMCLKEN,
		.devid		= SA1111_DEVID_PS2_MSE,
		.hwirq = अणु
			IRQ_MSRXINT,
			IRQ_MSTXINT
		पूर्ण,
	पूर्ण,
	अणु
		.offset		= 0x1800,
		.skpcr_mask	= 0,
		.devid		= SA1111_DEVID_PCMCIA,
		.hwirq = अणु
			IRQ_S0_READY_NINT,
			IRQ_S0_CD_VALID,
			IRQ_S0_BVD1_STSCHG,
			IRQ_S1_READY_NINT,
			IRQ_S1_CD_VALID,
			IRQ_S1_BVD1_STSCHG,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sa1111_map_irq(काष्ठा sa1111 *sachip, irq_hw_number_t hwirq)
अणु
	वापस irq_create_mapping(sachip->irqकरोमुख्य, hwirq);
पूर्ण

अटल व्योम sa1111_handle_irqकरोमुख्य(काष्ठा irq_करोमुख्य *irqकरोमुख्य, पूर्णांक irq)
अणु
	काष्ठा irq_desc *d = irq_to_desc(irq_linear_revmap(irqकरोमुख्य, irq));

	अगर (d)
		generic_handle_irq_desc(d);
पूर्ण

/*
 * SA1111 पूर्णांकerrupt support.  Since clearing an IRQ जबतक there are
 * active IRQs causes the पूर्णांकerrupt output to pulse, the upper levels
 * will call us again अगर there are more पूर्णांकerrupts to process.
 */
अटल व्योम sa1111_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक stat0, stat1, i;
	काष्ठा sa1111 *sachip = irq_desc_get_handler_data(desc);
	काष्ठा irq_करोमुख्य *irqकरोमुख्य;
	व्योम __iomem *mapbase = sachip->base + SA1111_INTC;

	stat0 = पढ़ोl_relaxed(mapbase + SA1111_INTSTATCLR0);
	stat1 = पढ़ोl_relaxed(mapbase + SA1111_INTSTATCLR1);

	ग_लिखोl_relaxed(stat0, mapbase + SA1111_INTSTATCLR0);

	desc->irq_data.chip->irq_ack(&desc->irq_data);

	ग_लिखोl_relaxed(stat1, mapbase + SA1111_INTSTATCLR1);

	अगर (stat0 == 0 && stat1 == 0) अणु
		करो_bad_IRQ(desc);
		वापस;
	पूर्ण

	irqकरोमुख्य = sachip->irqकरोमुख्य;

	क्रम (i = 0; stat0; i++, stat0 >>= 1)
		अगर (stat0 & 1)
			sa1111_handle_irqकरोमुख्य(irqकरोमुख्य, i);

	क्रम (i = 32; stat1; i++, stat1 >>= 1)
		अगर (stat1 & 1)
			sa1111_handle_irqकरोमुख्य(irqकरोमुख्य, i);

	/* For level-based पूर्णांकerrupts */
	desc->irq_data.chip->irq_unmask(&desc->irq_data);
पूर्ण

अटल u32 sa1111_irqmask(काष्ठा irq_data *d)
अणु
	वापस BIT(irqd_to_hwirq(d) & 31);
पूर्ण

अटल पूर्णांक sa1111_irqbank(काष्ठा irq_data *d)
अणु
	वापस (irqd_to_hwirq(d) / 32) * 4;
पूर्ण

अटल व्योम sa1111_ack_irq(काष्ठा irq_data *d)
अणु
पूर्ण

अटल व्योम sa1111_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा sa1111 *sachip = irq_data_get_irq_chip_data(d);
	व्योम __iomem *mapbase = sachip->base + SA1111_INTC + sa1111_irqbank(d);
	u32 ie;

	ie = पढ़ोl_relaxed(mapbase + SA1111_INTEN0);
	ie &= ~sa1111_irqmask(d);
	ग_लिखोl(ie, mapbase + SA1111_INTEN0);
पूर्ण

अटल व्योम sa1111_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा sa1111 *sachip = irq_data_get_irq_chip_data(d);
	व्योम __iomem *mapbase = sachip->base + SA1111_INTC + sa1111_irqbank(d);
	u32 ie;

	ie = पढ़ोl_relaxed(mapbase + SA1111_INTEN0);
	ie |= sa1111_irqmask(d);
	ग_लिखोl_relaxed(ie, mapbase + SA1111_INTEN0);
पूर्ण

/*
 * Attempt to re-trigger the पूर्णांकerrupt.  The SA1111 contains a रेजिस्टर
 * (INTSET) which claims to करो this.  However, in practice no amount of
 * manipulation of INTEN and INTSET guarantees that the पूर्णांकerrupt will
 * be triggered.  In fact, its very dअगरficult, अगर not impossible to get
 * INTSET to re-trigger the पूर्णांकerrupt.
 */
अटल पूर्णांक sa1111_retrigger_irq(काष्ठा irq_data *d)
अणु
	काष्ठा sa1111 *sachip = irq_data_get_irq_chip_data(d);
	व्योम __iomem *mapbase = sachip->base + SA1111_INTC + sa1111_irqbank(d);
	u32 ip, mask = sa1111_irqmask(d);
	पूर्णांक i;

	ip = पढ़ोl_relaxed(mapbase + SA1111_INTPOL0);
	क्रम (i = 0; i < 8; i++) अणु
		ग_लिखोl_relaxed(ip ^ mask, mapbase + SA1111_INTPOL0);
		ग_लिखोl_relaxed(ip, mapbase + SA1111_INTPOL0);
		अगर (पढ़ोl_relaxed(mapbase + SA1111_INTSTATCLR0) & mask)
			अवरोध;
	पूर्ण

	अगर (i == 8) अणु
		pr_err("Danger Will Robinson: failed to re-trigger IRQ%d\n",
		       d->irq);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक sa1111_type_irq(काष्ठा irq_data *d, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sa1111 *sachip = irq_data_get_irq_chip_data(d);
	व्योम __iomem *mapbase = sachip->base + SA1111_INTC + sa1111_irqbank(d);
	u32 ip, mask = sa1111_irqmask(d);

	अगर (flags == IRQ_TYPE_PROBE)
		वापस 0;

	अगर ((!(flags & IRQ_TYPE_EDGE_RISING) ^ !(flags & IRQ_TYPE_EDGE_FALLING)) == 0)
		वापस -EINVAL;

	ip = पढ़ोl_relaxed(mapbase + SA1111_INTPOL0);
	अगर (flags & IRQ_TYPE_EDGE_RISING)
		ip &= ~mask;
	अन्यथा
		ip |= mask;
	ग_लिखोl_relaxed(ip, mapbase + SA1111_INTPOL0);
	ग_लिखोl_relaxed(ip, mapbase + SA1111_WAKEPOL0);

	वापस 0;
पूर्ण

अटल पूर्णांक sa1111_wake_irq(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा sa1111 *sachip = irq_data_get_irq_chip_data(d);
	व्योम __iomem *mapbase = sachip->base + SA1111_INTC + sa1111_irqbank(d);
	u32 we, mask = sa1111_irqmask(d);

	we = पढ़ोl_relaxed(mapbase + SA1111_WAKEEN0);
	अगर (on)
		we |= mask;
	अन्यथा
		we &= ~mask;
	ग_लिखोl_relaxed(we, mapbase + SA1111_WAKEEN0);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip sa1111_irq_chip = अणु
	.name		= "SA1111",
	.irq_ack	= sa1111_ack_irq,
	.irq_mask	= sa1111_mask_irq,
	.irq_unmask	= sa1111_unmask_irq,
	.irq_retrigger	= sa1111_retrigger_irq,
	.irq_set_type	= sa1111_type_irq,
	.irq_set_wake	= sa1111_wake_irq,
पूर्ण;

अटल पूर्णांक sa1111_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
	irq_hw_number_t hwirq)
अणु
	काष्ठा sa1111 *sachip = d->host_data;

	/* Disallow unavailable पूर्णांकerrupts */
	अगर (hwirq > SSPROR && hwirq < AUDXMTDMADONEA)
		वापस -EINVAL;

	irq_set_chip_data(irq, sachip);
	irq_set_chip_and_handler(irq, &sa1111_irq_chip, handle_edge_irq);
	irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops sa1111_irqकरोमुख्य_ops = अणु
	.map = sa1111_irqकरोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल पूर्णांक sa1111_setup_irq(काष्ठा sa1111 *sachip, अचिन्हित irq_base)
अणु
	व्योम __iomem *irqbase = sachip->base + SA1111_INTC;
	पूर्णांक ret;

	/*
	 * We're guaranteed that this region hasn't been taken.
	 */
	request_mem_region(sachip->phys + SA1111_INTC, 512, "irq");

	ret = irq_alloc_descs(-1, irq_base, SA1111_IRQ_NR, -1);
	अगर (ret <= 0) अणु
		dev_err(sachip->dev, "unable to allocate %u irqs: %d\n",
			SA1111_IRQ_NR, ret);
		अगर (ret == 0)
			ret = -EINVAL;
		वापस ret;
	पूर्ण

	sachip->irq_base = ret;

	/* disable all IRQs */
	ग_लिखोl_relaxed(0, irqbase + SA1111_INTEN0);
	ग_लिखोl_relaxed(0, irqbase + SA1111_INTEN1);
	ग_लिखोl_relaxed(0, irqbase + SA1111_WAKEEN0);
	ग_लिखोl_relaxed(0, irqbase + SA1111_WAKEEN1);

	/*
	 * detect on rising edge.  Note: Feb 2001 Errata क्रम SA1111
	 * specअगरies that S0ReadyInt and S1ReadyInt should be '1'.
	 */
	ग_लिखोl_relaxed(0, irqbase + SA1111_INTPOL0);
	ग_लिखोl_relaxed(BIT(IRQ_S0_READY_NINT & 31) |
		       BIT(IRQ_S1_READY_NINT & 31),
		       irqbase + SA1111_INTPOL1);

	/* clear all IRQs */
	ग_लिखोl_relaxed(~0, irqbase + SA1111_INTSTATCLR0);
	ग_लिखोl_relaxed(~0, irqbase + SA1111_INTSTATCLR1);

	sachip->irqकरोमुख्य = irq_करोमुख्य_add_linear(शून्य, SA1111_IRQ_NR,
						  &sa1111_irqकरोमुख्य_ops,
						  sachip);
	अगर (!sachip->irqकरोमुख्य) अणु
		irq_मुक्त_descs(sachip->irq_base, SA1111_IRQ_NR);
		वापस -ENOMEM;
	पूर्ण

	irq_करोमुख्य_associate_many(sachip->irqकरोमुख्य,
				  sachip->irq_base + IRQ_GPAIN0,
				  IRQ_GPAIN0, SSPROR + 1 - IRQ_GPAIN0);
	irq_करोमुख्य_associate_many(sachip->irqकरोमुख्य,
				  sachip->irq_base + AUDXMTDMADONEA,
				  AUDXMTDMADONEA,
				  IRQ_S1_BVD1_STSCHG + 1 - AUDXMTDMADONEA);

	/*
	 * Register SA1111 पूर्णांकerrupt
	 */
	irq_set_irq_type(sachip->irq, IRQ_TYPE_EDGE_RISING);
	irq_set_chained_handler_and_data(sachip->irq, sa1111_irq_handler,
					 sachip);

	dev_info(sachip->dev, "Providing IRQ%u-%u\n",
		sachip->irq_base, sachip->irq_base + SA1111_IRQ_NR - 1);

	वापस 0;
पूर्ण

अटल व्योम sa1111_हटाओ_irq(काष्ठा sa1111 *sachip)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = sachip->irqकरोमुख्य;
	व्योम __iomem *irqbase = sachip->base + SA1111_INTC;
	पूर्णांक i;

	/* disable all IRQs */
	ग_लिखोl_relaxed(0, irqbase + SA1111_INTEN0);
	ग_लिखोl_relaxed(0, irqbase + SA1111_INTEN1);
	ग_लिखोl_relaxed(0, irqbase + SA1111_WAKEEN0);
	ग_लिखोl_relaxed(0, irqbase + SA1111_WAKEEN1);

	irq_set_chained_handler_and_data(sachip->irq, शून्य, शून्य);
	क्रम (i = 0; i < SA1111_IRQ_NR; i++)
		irq_dispose_mapping(irq_find_mapping(करोमुख्य, i));
	irq_करोमुख्य_हटाओ(करोमुख्य);

	release_mem_region(sachip->phys + SA1111_INTC, 512);
पूर्ण

क्रमागत अणु
	SA1111_GPIO_PXDDR = (SA1111_GPIO_PADDR - SA1111_GPIO_PADDR),
	SA1111_GPIO_PXDRR = (SA1111_GPIO_PADRR - SA1111_GPIO_PADDR),
	SA1111_GPIO_PXDWR = (SA1111_GPIO_PADWR - SA1111_GPIO_PADDR),
	SA1111_GPIO_PXSDR = (SA1111_GPIO_PASDR - SA1111_GPIO_PADDR),
	SA1111_GPIO_PXSSR = (SA1111_GPIO_PASSR - SA1111_GPIO_PADDR),
पूर्ण;

अटल काष्ठा sa1111 *gc_to_sa1111(काष्ठा gpio_chip *gc)
अणु
	वापस container_of(gc, काष्ठा sa1111, gc);
पूर्ण

अटल व्योम __iomem *sa1111_gpio_map_reg(काष्ठा sa1111 *sachip, अचिन्हित offset)
अणु
	व्योम __iomem *reg = sachip->base + SA1111_GPIO;

	अगर (offset < 4)
		वापस reg + SA1111_GPIO_PADDR;
	अगर (offset < 10)
		वापस reg + SA1111_GPIO_PBDDR;
	अगर (offset < 18)
		वापस reg + SA1111_GPIO_PCDDR;
	वापस शून्य;
पूर्ण

अटल u32 sa1111_gpio_map_bit(अचिन्हित offset)
अणु
	अगर (offset < 4)
		वापस BIT(offset);
	अगर (offset < 10)
		वापस BIT(offset - 4);
	अगर (offset < 18)
		वापस BIT(offset - 10);
	वापस 0;
पूर्ण

अटल व्योम sa1111_gpio_modअगरy(व्योम __iomem *reg, u32 mask, u32 set)
अणु
	u32 val;

	val = पढ़ोl_relaxed(reg);
	val &= ~mask;
	val |= mask & set;
	ग_लिखोl_relaxed(val, reg);
पूर्ण

अटल पूर्णांक sa1111_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा sa1111 *sachip = gc_to_sa1111(gc);
	व्योम __iomem *reg = sa1111_gpio_map_reg(sachip, offset);
	u32 mask = sa1111_gpio_map_bit(offset);

	वापस !!(पढ़ोl_relaxed(reg + SA1111_GPIO_PXDDR) & mask);
पूर्ण

अटल पूर्णांक sa1111_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा sa1111 *sachip = gc_to_sa1111(gc);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *reg = sa1111_gpio_map_reg(sachip, offset);
	u32 mask = sa1111_gpio_map_bit(offset);

	spin_lock_irqsave(&sachip->lock, flags);
	sa1111_gpio_modअगरy(reg + SA1111_GPIO_PXDDR, mask, mask);
	sa1111_gpio_modअगरy(reg + SA1111_GPIO_PXSDR, mask, mask);
	spin_unlock_irqrestore(&sachip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sa1111_gpio_direction_output(काष्ठा gpio_chip *gc, अचिन्हित offset,
	पूर्णांक value)
अणु
	काष्ठा sa1111 *sachip = gc_to_sa1111(gc);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *reg = sa1111_gpio_map_reg(sachip, offset);
	u32 mask = sa1111_gpio_map_bit(offset);

	spin_lock_irqsave(&sachip->lock, flags);
	sa1111_gpio_modअगरy(reg + SA1111_GPIO_PXDWR, mask, value ? mask : 0);
	sa1111_gpio_modअगरy(reg + SA1111_GPIO_PXSSR, mask, value ? mask : 0);
	sa1111_gpio_modअगरy(reg + SA1111_GPIO_PXDDR, mask, 0);
	sa1111_gpio_modअगरy(reg + SA1111_GPIO_PXSDR, mask, 0);
	spin_unlock_irqrestore(&sachip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sa1111_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा sa1111 *sachip = gc_to_sa1111(gc);
	व्योम __iomem *reg = sa1111_gpio_map_reg(sachip, offset);
	u32 mask = sa1111_gpio_map_bit(offset);

	वापस !!(पढ़ोl_relaxed(reg + SA1111_GPIO_PXDRR) & mask);
पूर्ण

अटल व्योम sa1111_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा sa1111 *sachip = gc_to_sa1111(gc);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *reg = sa1111_gpio_map_reg(sachip, offset);
	u32 mask = sa1111_gpio_map_bit(offset);

	spin_lock_irqsave(&sachip->lock, flags);
	sa1111_gpio_modअगरy(reg + SA1111_GPIO_PXDWR, mask, value ? mask : 0);
	sa1111_gpio_modअगरy(reg + SA1111_GPIO_PXSSR, mask, value ? mask : 0);
	spin_unlock_irqrestore(&sachip->lock, flags);
पूर्ण

अटल व्योम sa1111_gpio_set_multiple(काष्ठा gpio_chip *gc, अचिन्हित दीर्घ *mask,
	अचिन्हित दीर्घ *bits)
अणु
	काष्ठा sa1111 *sachip = gc_to_sa1111(gc);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *reg = sachip->base + SA1111_GPIO;
	u32 msk, val;

	msk = *mask;
	val = *bits;

	spin_lock_irqsave(&sachip->lock, flags);
	sa1111_gpio_modअगरy(reg + SA1111_GPIO_PADWR, msk & 15, val);
	sa1111_gpio_modअगरy(reg + SA1111_GPIO_PASSR, msk & 15, val);
	sa1111_gpio_modअगरy(reg + SA1111_GPIO_PBDWR, (msk >> 4) & 255, val >> 4);
	sa1111_gpio_modअगरy(reg + SA1111_GPIO_PBSSR, (msk >> 4) & 255, val >> 4);
	sa1111_gpio_modअगरy(reg + SA1111_GPIO_PCDWR, (msk >> 12) & 255, val >> 12);
	sa1111_gpio_modअगरy(reg + SA1111_GPIO_PCSSR, (msk >> 12) & 255, val >> 12);
	spin_unlock_irqrestore(&sachip->lock, flags);
पूर्ण

अटल पूर्णांक sa1111_gpio_to_irq(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा sa1111 *sachip = gc_to_sa1111(gc);

	वापस sa1111_map_irq(sachip, offset);
पूर्ण

अटल पूर्णांक sa1111_setup_gpios(काष्ठा sa1111 *sachip)
अणु
	sachip->gc.label = "sa1111";
	sachip->gc.parent = sachip->dev;
	sachip->gc.owner = THIS_MODULE;
	sachip->gc.get_direction = sa1111_gpio_get_direction;
	sachip->gc.direction_input = sa1111_gpio_direction_input;
	sachip->gc.direction_output = sa1111_gpio_direction_output;
	sachip->gc.get = sa1111_gpio_get;
	sachip->gc.set = sa1111_gpio_set;
	sachip->gc.set_multiple = sa1111_gpio_set_multiple;
	sachip->gc.to_irq = sa1111_gpio_to_irq;
	sachip->gc.base = -1;
	sachip->gc.ngpio = 18;

	वापस devm_gpiochip_add_data(sachip->dev, &sachip->gc, sachip);
पूर्ण

/*
 * Bring the SA1111 out of reset.  This requires a set procedure:
 *  1. nRESET निश्चितed (by hardware)
 *  2. CLK turned on from SA1110
 *  3. nRESET deनिश्चितed
 *  4. VCO turned on, PLL_BYPASS turned off
 *  5. Wait lock समय, then निश्चित RCLKEn
 *  7. PCR set to allow घड़ीing of inभागidual functions
 *
 * Until we've करोne this, the only रेजिस्टरs we can access are:
 *   SBI_SKCR
 *   SBI_SMCR
 *   SBI_SKID
 */
अटल व्योम sa1111_wake(काष्ठा sa1111 *sachip)
अणु
	अचिन्हित दीर्घ flags, r;

	spin_lock_irqsave(&sachip->lock, flags);

	clk_enable(sachip->clk);

	/*
	 * Turn VCO on, and disable PLL Bypass.
	 */
	r = पढ़ोl_relaxed(sachip->base + SA1111_SKCR);
	r &= ~SKCR_VCO_OFF;
	ग_लिखोl_relaxed(r, sachip->base + SA1111_SKCR);
	r |= SKCR_PLL_BYPASS | SKCR_OE_EN;
	ग_लिखोl_relaxed(r, sachip->base + SA1111_SKCR);

	/*
	 * Wait lock समय.  SA1111 manual _करोesn't_
	 * specअगरy a figure क्रम this!  We choose 100us.
	 */
	udelay(100);

	/*
	 * Enable RCLK.  We also ensure that RDYEN is set.
	 */
	r |= SKCR_RCLKEN | SKCR_RDYEN;
	ग_लिखोl_relaxed(r, sachip->base + SA1111_SKCR);

	/*
	 * Wait 14 RCLK cycles क्रम the chip to finish coming out
	 * of reset. (RCLK=24MHz).  This is 590ns.
	 */
	udelay(1);

	/*
	 * Ensure all घड़ीs are initially off.
	 */
	ग_लिखोl_relaxed(0, sachip->base + SA1111_SKPCR);

	spin_unlock_irqrestore(&sachip->lock, flags);
पूर्ण

#अगर_घोषित CONFIG_ARCH_SA1100

अटल u32 sa1111_dma_mask[] = अणु
	~0,
	~(1 << 20),
	~(1 << 23),
	~(1 << 24),
	~(1 << 25),
	~(1 << 20),
	~(1 << 20),
	0,
पूर्ण;

/*
 * Configure the SA1111 shared memory controller.
 */
व्योम
sa1111_configure_smc(काष्ठा sa1111 *sachip, पूर्णांक sdram, अचिन्हित पूर्णांक drac,
		     अचिन्हित पूर्णांक cas_latency)
अणु
	अचिन्हित पूर्णांक smcr = SMCR_DTIM | SMCR_MBGE | FInsrt(drac, SMCR_DRAC);

	अगर (cas_latency == 3)
		smcr |= SMCR_CLAT;

	ग_लिखोl_relaxed(smcr, sachip->base + SA1111_SMCR);

	/*
	 * Now clear the bits in the DMA mask to work around the SA1111
	 * DMA erratum (Intel StrongARM SA-1111 Microprocessor Companion
	 * Chip Specअगरication Update, June 2000, Erratum #7).
	 */
	अगर (sachip->dev->dma_mask)
		*sachip->dev->dma_mask &= sa1111_dma_mask[drac >> 2];

	sachip->dev->coherent_dma_mask &= sa1111_dma_mask[drac >> 2];
पूर्ण
#पूर्ण_अगर

अटल व्योम sa1111_dev_release(काष्ठा device *_dev)
अणु
	काष्ठा sa1111_dev *dev = to_sa1111_device(_dev);

	kमुक्त(dev);
पूर्ण

अटल पूर्णांक
sa1111_init_one_child(काष्ठा sa1111 *sachip, काष्ठा resource *parent,
		      काष्ठा sa1111_dev_info *info)
अणु
	काष्ठा sa1111_dev *dev;
	अचिन्हित i;
	पूर्णांक ret;

	dev = kzalloc(माप(काष्ठा sa1111_dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	device_initialize(&dev->dev);
	dev_set_name(&dev->dev, "%4.4lx", info->offset);
	dev->devid	 = info->devid;
	dev->dev.parent  = sachip->dev;
	dev->dev.bus     = &sa1111_bus_type;
	dev->dev.release = sa1111_dev_release;
	dev->res.start   = sachip->phys + info->offset;
	dev->res.end     = dev->res.start + 511;
	dev->res.name    = dev_name(&dev->dev);
	dev->res.flags   = IORESOURCE_MEM;
	dev->mapbase     = sachip->base + info->offset;
	dev->skpcr_mask  = info->skpcr_mask;

	क्रम (i = 0; i < ARRAY_SIZE(info->hwirq); i++)
		dev->hwirq[i] = info->hwirq[i];

	/*
	 * If the parent device has a DMA mask associated with it, and
	 * this child supports DMA, propagate it करोwn to the children.
	 */
	अगर (info->dma && sachip->dev->dma_mask) अणु
		dev->dma_mask = *sachip->dev->dma_mask;
		dev->dev.dma_mask = &dev->dma_mask;
		dev->dev.coherent_dma_mask = sachip->dev->coherent_dma_mask;
	पूर्ण

	ret = request_resource(parent, &dev->res);
	अगर (ret) अणु
		dev_err(sachip->dev, "failed to allocate resource for %s\n",
			dev->res.name);
		जाओ err_resource;
	पूर्ण

	ret = device_add(&dev->dev);
	अगर (ret)
		जाओ err_add;
	वापस 0;

 err_add:
	release_resource(&dev->res);
 err_resource:
	put_device(&dev->dev);
 err_alloc:
	वापस ret;
पूर्ण

/**
 *	sa1111_probe - probe क्रम a single SA1111 chip.
 *	@phys_addr: physical address of device.
 *
 *	Probe क्रम a SA1111 chip.  This must be called
 *	beक्रमe any other SA1111-specअगरic code.
 *
 *	Returns:
 *	%-ENODEV	device not found.
 *	%-EBUSY		physical address alपढ़ोy marked in-use.
 *	%-EINVAL	no platक्रमm data passed
 *	%0		successful.
 */
अटल पूर्णांक __sa1111_probe(काष्ठा device *me, काष्ठा resource *mem, पूर्णांक irq)
अणु
	काष्ठा sa1111_platक्रमm_data *pd = me->platक्रमm_data;
	काष्ठा sa1111 *sachip;
	अचिन्हित दीर्घ id;
	अचिन्हित पूर्णांक has_devs;
	पूर्णांक i, ret = -ENODEV;

	अगर (!pd)
		वापस -EINVAL;

	sachip = devm_kzalloc(me, माप(काष्ठा sa1111), GFP_KERNEL);
	अगर (!sachip)
		वापस -ENOMEM;

	sachip->clk = devm_clk_get(me, "SA1111_CLK");
	अगर (IS_ERR(sachip->clk))
		वापस PTR_ERR(sachip->clk);

	ret = clk_prepare(sachip->clk);
	अगर (ret)
		वापस ret;

	spin_lock_init(&sachip->lock);

	sachip->dev = me;
	dev_set_drvdata(sachip->dev, sachip);

	sachip->pdata = pd;
	sachip->phys = mem->start;
	sachip->irq = irq;

	/*
	 * Map the whole region.  This also maps the
	 * रेजिस्टरs क्रम our children.
	 */
	sachip->base = ioremap(mem->start, PAGE_SIZE * 2);
	अगर (!sachip->base) अणु
		ret = -ENOMEM;
		जाओ err_clk_unprep;
	पूर्ण

	/*
	 * Probe क्रम the chip.  Only touch the SBI रेजिस्टरs.
	 */
	id = पढ़ोl_relaxed(sachip->base + SA1111_SKID);
	अगर ((id & SKID_ID_MASK) != SKID_SA1111_ID) अणु
		prपूर्णांकk(KERN_DEBUG "SA1111 not detected: ID = %08lx\n", id);
		ret = -ENODEV;
		जाओ err_unmap;
	पूर्ण

	pr_info("SA1111 Microprocessor Companion Chip: silicon revision %lx, metal revision %lx\n",
		(id & SKID_SIREV_MASK) >> 4, id & SKID_MTREV_MASK);

	/*
	 * We found it.  Wake the chip up, and initialise.
	 */
	sa1111_wake(sachip);

	/*
	 * The पूर्णांकerrupt controller must be initialised beक्रमe any
	 * other device to ensure that the पूर्णांकerrupts are available.
	 */
	ret = sa1111_setup_irq(sachip, pd->irq_base);
	अगर (ret)
		जाओ err_clk;

	/* Setup the GPIOs - should really be करोne after the IRQ setup */
	ret = sa1111_setup_gpios(sachip);
	अगर (ret)
		जाओ err_irq;

#अगर_घोषित CONFIG_ARCH_SA1100
	अणु
	अचिन्हित पूर्णांक val;

	/*
	 * The SDRAM configuration of the SA1110 and the SA1111 must
	 * match.  This is very important to ensure that SA1111 accesses
	 * करोn't corrupt the SDRAM.  Note that this ungates the SA1111's
	 * MBGNT संकेत, so we must have called sa1110_mb_disable()
	 * beक्रमehand.
	 */
	sa1111_configure_smc(sachip, 1,
			     FExtr(MDCNFG, MDCNFG_SA1110_DRAC0),
			     FExtr(MDCNFG, MDCNFG_SA1110_TDL0));

	/*
	 * We only need to turn on DCLK whenever we want to use the
	 * DMA.  It can otherwise be held firmly in the off position.
	 * (currently, we always enable it.)
	 */
	val = पढ़ोl_relaxed(sachip->base + SA1111_SKPCR);
	ग_लिखोl_relaxed(val | SKPCR_DCLKEN, sachip->base + SA1111_SKPCR);

	/*
	 * Enable the SA1110 memory bus request and grant संकेतs.
	 */
	sa1110_mb_enable();
	पूर्ण
#पूर्ण_अगर

	g_sa1111 = sachip;

	has_devs = ~0;
	अगर (pd)
		has_devs &= ~pd->disable_devs;

	क्रम (i = 0; i < ARRAY_SIZE(sa1111_devices); i++)
		अगर (sa1111_devices[i].devid & has_devs)
			sa1111_init_one_child(sachip, mem, &sa1111_devices[i]);

	वापस 0;

 err_irq:
	sa1111_हटाओ_irq(sachip);
 err_clk:
	clk_disable(sachip->clk);
 err_unmap:
	iounmap(sachip->base);
 err_clk_unprep:
	clk_unprepare(sachip->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक sa1111_हटाओ_one(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा sa1111_dev *sadev = to_sa1111_device(dev);
	अगर (dev->bus != &sa1111_bus_type)
		वापस 0;
	device_del(&sadev->dev);
	release_resource(&sadev->res);
	put_device(&sadev->dev);
	वापस 0;
पूर्ण

अटल व्योम __sa1111_हटाओ(काष्ठा sa1111 *sachip)
अणु
	device_क्रम_each_child(sachip->dev, शून्य, sa1111_हटाओ_one);

	sa1111_हटाओ_irq(sachip);

	clk_disable(sachip->clk);
	clk_unprepare(sachip->clk);

	iounmap(sachip->base);
पूर्ण

काष्ठा sa1111_save_data अणु
	अचिन्हित पूर्णांक	skcr;
	अचिन्हित पूर्णांक	skpcr;
	अचिन्हित पूर्णांक	skcdr;
	अचिन्हित अक्षर	skaud;
	अचिन्हित अक्षर	skpwm0;
	अचिन्हित अक्षर	skpwm1;

	/*
	 * Interrupt controller
	 */
	अचिन्हित पूर्णांक	पूर्णांकpol0;
	अचिन्हित पूर्णांक	पूर्णांकpol1;
	अचिन्हित पूर्णांक	पूर्णांकen0;
	अचिन्हित पूर्णांक	पूर्णांकen1;
	अचिन्हित पूर्णांक	wakepol0;
	अचिन्हित पूर्णांक	wakepol1;
	अचिन्हित पूर्णांक	wakeen0;
	अचिन्हित पूर्णांक	wakeen1;
पूर्ण;

#अगर_घोषित CONFIG_PM

अटल पूर्णांक sa1111_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा sa1111 *sachip = dev_get_drvdata(dev);
	काष्ठा sa1111_save_data *save;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;
	व्योम __iomem *base;

	save = kदो_स्मृति(माप(काष्ठा sa1111_save_data), GFP_KERNEL);
	अगर (!save)
		वापस -ENOMEM;
	sachip->saved_state = save;

	spin_lock_irqsave(&sachip->lock, flags);

	/*
	 * Save state.
	 */
	base = sachip->base;
	save->skcr     = पढ़ोl_relaxed(base + SA1111_SKCR);
	save->skpcr    = पढ़ोl_relaxed(base + SA1111_SKPCR);
	save->skcdr    = पढ़ोl_relaxed(base + SA1111_SKCDR);
	save->skaud    = पढ़ोl_relaxed(base + SA1111_SKAUD);
	save->skpwm0   = पढ़ोl_relaxed(base + SA1111_SKPWM0);
	save->skpwm1   = पढ़ोl_relaxed(base + SA1111_SKPWM1);

	ग_लिखोl_relaxed(0, sachip->base + SA1111_SKPWM0);
	ग_लिखोl_relaxed(0, sachip->base + SA1111_SKPWM1);

	base = sachip->base + SA1111_INTC;
	save->पूर्णांकpol0  = पढ़ोl_relaxed(base + SA1111_INTPOL0);
	save->पूर्णांकpol1  = पढ़ोl_relaxed(base + SA1111_INTPOL1);
	save->पूर्णांकen0   = पढ़ोl_relaxed(base + SA1111_INTEN0);
	save->पूर्णांकen1   = पढ़ोl_relaxed(base + SA1111_INTEN1);
	save->wakepol0 = पढ़ोl_relaxed(base + SA1111_WAKEPOL0);
	save->wakepol1 = पढ़ोl_relaxed(base + SA1111_WAKEPOL1);
	save->wakeen0  = पढ़ोl_relaxed(base + SA1111_WAKEEN0);
	save->wakeen1  = पढ़ोl_relaxed(base + SA1111_WAKEEN1);

	/*
	 * Disable.
	 */
	val = पढ़ोl_relaxed(sachip->base + SA1111_SKCR);
	ग_लिखोl_relaxed(val | SKCR_SLEEP, sachip->base + SA1111_SKCR);

	clk_disable(sachip->clk);

	spin_unlock_irqrestore(&sachip->lock, flags);

#अगर_घोषित CONFIG_ARCH_SA1100
	sa1110_mb_disable();
#पूर्ण_अगर

	वापस 0;
पूर्ण

/*
 *	sa1111_resume - Restore the SA1111 device state.
 *	@dev: device to restore
 *
 *	Restore the general state of the SA1111; घड़ी control and
 *	पूर्णांकerrupt controller.  Other parts of the SA1111 must be
 *	restored by their respective drivers, and must be called
 *	via LDM after this function.
 */
अटल पूर्णांक sa1111_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा sa1111 *sachip = dev_get_drvdata(dev);
	काष्ठा sa1111_save_data *save;
	अचिन्हित दीर्घ flags, id;
	व्योम __iomem *base;

	save = sachip->saved_state;
	अगर (!save)
		वापस 0;

	/*
	 * Ensure that the SA1111 is still here.
	 * FIXME: shouldn't करो this here.
	 */
	id = पढ़ोl_relaxed(sachip->base + SA1111_SKID);
	अगर ((id & SKID_ID_MASK) != SKID_SA1111_ID) अणु
		__sa1111_हटाओ(sachip);
		dev_set_drvdata(dev, शून्य);
		kमुक्त(save);
		वापस 0;
	पूर्ण

	/*
	 * First of all, wake up the chip.
	 */
	sa1111_wake(sachip);

#अगर_घोषित CONFIG_ARCH_SA1100
	/* Enable the memory bus request/grant संकेतs */
	sa1110_mb_enable();
#पूर्ण_अगर

	/*
	 * Only lock क्रम ग_लिखो ops. Also, sa1111_wake must be called with
	 * released spinlock!
	 */
	spin_lock_irqsave(&sachip->lock, flags);

	ग_लिखोl_relaxed(0, sachip->base + SA1111_INTC + SA1111_INTEN0);
	ग_लिखोl_relaxed(0, sachip->base + SA1111_INTC + SA1111_INTEN1);

	base = sachip->base;
	ग_लिखोl_relaxed(save->skcr,     base + SA1111_SKCR);
	ग_लिखोl_relaxed(save->skpcr,    base + SA1111_SKPCR);
	ग_लिखोl_relaxed(save->skcdr,    base + SA1111_SKCDR);
	ग_लिखोl_relaxed(save->skaud,    base + SA1111_SKAUD);
	ग_लिखोl_relaxed(save->skpwm0,   base + SA1111_SKPWM0);
	ग_लिखोl_relaxed(save->skpwm1,   base + SA1111_SKPWM1);

	base = sachip->base + SA1111_INTC;
	ग_लिखोl_relaxed(save->पूर्णांकpol0,  base + SA1111_INTPOL0);
	ग_लिखोl_relaxed(save->पूर्णांकpol1,  base + SA1111_INTPOL1);
	ग_लिखोl_relaxed(save->पूर्णांकen0,   base + SA1111_INTEN0);
	ग_लिखोl_relaxed(save->पूर्णांकen1,   base + SA1111_INTEN1);
	ग_लिखोl_relaxed(save->wakepol0, base + SA1111_WAKEPOL0);
	ग_लिखोl_relaxed(save->wakepol1, base + SA1111_WAKEPOL1);
	ग_लिखोl_relaxed(save->wakeen0,  base + SA1111_WAKEEN0);
	ग_लिखोl_relaxed(save->wakeen1,  base + SA1111_WAKEEN1);

	spin_unlock_irqrestore(&sachip->lock, flags);

	sachip->saved_state = शून्य;
	kमुक्त(save);

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा sa1111_suspend_noirq शून्य
#घोषणा sa1111_resume_noirq  शून्य
#पूर्ण_अगर

अटल पूर्णांक sa1111_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *mem;
	पूर्णांक irq;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mem)
		वापस -EINVAL;
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	वापस __sa1111_probe(&pdev->dev, mem, irq);
पूर्ण

अटल पूर्णांक sa1111_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sa1111 *sachip = platक्रमm_get_drvdata(pdev);

	अगर (sachip) अणु
#अगर_घोषित CONFIG_PM
		kमुक्त(sachip->saved_state);
		sachip->saved_state = शून्य;
#पूर्ण_अगर
		__sa1111_हटाओ(sachip);
		platक्रमm_set_drvdata(pdev, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dev_pm_ops sa1111_pm_ops = अणु
	.suspend_noirq = sa1111_suspend_noirq,
	.resume_noirq = sa1111_resume_noirq,
पूर्ण;

/*
 *	Not sure अगर this should be on the प्रणाली bus or not yet.
 *	We really want some way to रेजिस्टर a प्रणाली device at
 *	the per-machine level, and then have this driver pick
 *	up the रेजिस्टरed devices.
 *
 *	We also need to handle the SDRAM configuration क्रम
 *	PXA250/SA1110 machine classes.
 */
अटल काष्ठा platक्रमm_driver sa1111_device_driver = अणु
	.probe		= sa1111_probe,
	.हटाओ		= sa1111_हटाओ,
	.driver		= अणु
		.name	= "sa1111",
		.pm	= &sa1111_pm_ops,
	पूर्ण,
पूर्ण;

/*
 *	Get the parent device driver (us) काष्ठाure
 *	from a child function device
 */
अटल अंतरभूत काष्ठा sa1111 *sa1111_chip_driver(काष्ठा sa1111_dev *sadev)
अणु
	वापस (काष्ठा sa1111 *)dev_get_drvdata(sadev->dev.parent);
पूर्ण

/*
 * The bits in the opभाग field are non-linear.
 */
अटल अचिन्हित अक्षर opभाग_प्रकारable[] = अणु 1, 4, 2, 8 पूर्ण;

अटल अचिन्हित पूर्णांक __sa1111_pll_घड़ी(काष्ठा sa1111 *sachip)
अणु
	अचिन्हित पूर्णांक skcdr, fbभाग, ipभाग, opभाग;

	skcdr = पढ़ोl_relaxed(sachip->base + SA1111_SKCDR);

	fbभाग = (skcdr & 0x007f) + 2;
	ipभाग = ((skcdr & 0x0f80) >> 7) + 2;
	opभाग = opभाग_प्रकारable[(skcdr & 0x3000) >> 12];

	वापस 3686400 * fbभाग / (ipभाग * opभाग);
पूर्ण

/**
 *	sa1111_pll_घड़ी - वापस the current PLL घड़ी frequency.
 *	@sadev: SA1111 function block
 *
 *	BUG: we should look at SKCR.  We also blindly believe that
 *	the chip is being fed with the 3.6864MHz घड़ी.
 *
 *	Returns the PLL घड़ी in Hz.
 */
अचिन्हित पूर्णांक sa1111_pll_घड़ी(काष्ठा sa1111_dev *sadev)
अणु
	काष्ठा sa1111 *sachip = sa1111_chip_driver(sadev);

	वापस __sa1111_pll_घड़ी(sachip);
पूर्ण
EXPORT_SYMBOL(sa1111_pll_घड़ी);

/**
 *	sa1111_select_audio_mode - select I2S or AC link mode
 *	@sadev: SA1111 function block
 *	@mode: One of %SA1111_AUDIO_ACLINK or %SA1111_AUDIO_I2S
 *
 *	Frob the SKCR to select AC Link mode or I2S mode क्रम
 *	the audio block.
 */
व्योम sa1111_select_audio_mode(काष्ठा sa1111_dev *sadev, पूर्णांक mode)
अणु
	काष्ठा sa1111 *sachip = sa1111_chip_driver(sadev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&sachip->lock, flags);

	val = पढ़ोl_relaxed(sachip->base + SA1111_SKCR);
	अगर (mode == SA1111_AUDIO_I2S) अणु
		val &= ~SKCR_SELAC;
	पूर्ण अन्यथा अणु
		val |= SKCR_SELAC;
	पूर्ण
	ग_लिखोl_relaxed(val, sachip->base + SA1111_SKCR);

	spin_unlock_irqrestore(&sachip->lock, flags);
पूर्ण
EXPORT_SYMBOL(sa1111_select_audio_mode);

/**
 *	sa1111_set_audio_rate - set the audio sample rate
 *	@sadev: SA1111 SAC function block
 *	@rate: sample rate to select
 */
पूर्णांक sa1111_set_audio_rate(काष्ठा sa1111_dev *sadev, पूर्णांक rate)
अणु
	काष्ठा sa1111 *sachip = sa1111_chip_driver(sadev);
	अचिन्हित पूर्णांक भाग;

	अगर (sadev->devid != SA1111_DEVID_SAC)
		वापस -EINVAL;

	भाग = (__sa1111_pll_घड़ी(sachip) / 256 + rate / 2) / rate;
	अगर (भाग == 0)
		भाग = 1;
	अगर (भाग > 128)
		भाग = 128;

	ग_लिखोl_relaxed(भाग - 1, sachip->base + SA1111_SKAUD);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sa1111_set_audio_rate);

/**
 *	sa1111_get_audio_rate - get the audio sample rate
 *	@sadev: SA1111 SAC function block device
 */
पूर्णांक sa1111_get_audio_rate(काष्ठा sa1111_dev *sadev)
अणु
	काष्ठा sa1111 *sachip = sa1111_chip_driver(sadev);
	अचिन्हित दीर्घ भाग;

	अगर (sadev->devid != SA1111_DEVID_SAC)
		वापस -EINVAL;

	भाग = पढ़ोl_relaxed(sachip->base + SA1111_SKAUD) + 1;

	वापस __sa1111_pll_घड़ी(sachip) / (256 * भाग);
पूर्ण
EXPORT_SYMBOL(sa1111_get_audio_rate);

/*
 * Inभागidual device operations.
 */

/**
 *	sa1111_enable_device - enable an on-chip SA1111 function block
 *	@sadev: SA1111 function block device to enable
 */
पूर्णांक sa1111_enable_device(काष्ठा sa1111_dev *sadev)
अणु
	काष्ठा sa1111 *sachip = sa1111_chip_driver(sadev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = 0;

	अगर (sachip->pdata && sachip->pdata->enable)
		ret = sachip->pdata->enable(sachip->pdata->data, sadev->devid);

	अगर (ret == 0) अणु
		spin_lock_irqsave(&sachip->lock, flags);
		val = पढ़ोl_relaxed(sachip->base + SA1111_SKPCR);
		ग_लिखोl_relaxed(val | sadev->skpcr_mask, sachip->base + SA1111_SKPCR);
		spin_unlock_irqrestore(&sachip->lock, flags);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sa1111_enable_device);

/**
 *	sa1111_disable_device - disable an on-chip SA1111 function block
 *	@sadev: SA1111 function block device to disable
 */
व्योम sa1111_disable_device(काष्ठा sa1111_dev *sadev)
अणु
	काष्ठा sa1111 *sachip = sa1111_chip_driver(sadev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&sachip->lock, flags);
	val = पढ़ोl_relaxed(sachip->base + SA1111_SKPCR);
	ग_लिखोl_relaxed(val & ~sadev->skpcr_mask, sachip->base + SA1111_SKPCR);
	spin_unlock_irqrestore(&sachip->lock, flags);

	अगर (sachip->pdata && sachip->pdata->disable)
		sachip->pdata->disable(sachip->pdata->data, sadev->devid);
पूर्ण
EXPORT_SYMBOL(sa1111_disable_device);

पूर्णांक sa1111_get_irq(काष्ठा sa1111_dev *sadev, अचिन्हित num)
अणु
	काष्ठा sa1111 *sachip = sa1111_chip_driver(sadev);
	अगर (num >= ARRAY_SIZE(sadev->hwirq))
		वापस -EINVAL;
	वापस sa1111_map_irq(sachip, sadev->hwirq[num]);
पूर्ण
EXPORT_SYMBOL_GPL(sa1111_get_irq);

/*
 *	SA1111 "Register Access Bus."
 *
 *	We model this as a regular bus type, and hang devices directly
 *	off this.
 */
अटल पूर्णांक sa1111_match(काष्ठा device *_dev, काष्ठा device_driver *_drv)
अणु
	काष्ठा sa1111_dev *dev = to_sa1111_device(_dev);
	काष्ठा sa1111_driver *drv = SA1111_DRV(_drv);

	वापस !!(dev->devid & drv->devid);
पूर्ण

अटल पूर्णांक sa1111_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा sa1111_dev *sadev = to_sa1111_device(dev);
	काष्ठा sa1111_driver *drv = SA1111_DRV(dev->driver);
	पूर्णांक ret = -ENODEV;

	अगर (drv->probe)
		ret = drv->probe(sadev);
	वापस ret;
पूर्ण

अटल पूर्णांक sa1111_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा sa1111_dev *sadev = to_sa1111_device(dev);
	काष्ठा sa1111_driver *drv = SA1111_DRV(dev->driver);

	अगर (drv->हटाओ)
		drv->हटाओ(sadev);

	वापस 0;
पूर्ण

काष्ठा bus_type sa1111_bus_type = अणु
	.name		= "sa1111-rab",
	.match		= sa1111_match,
	.probe		= sa1111_bus_probe,
	.हटाओ		= sa1111_bus_हटाओ,
पूर्ण;
EXPORT_SYMBOL(sa1111_bus_type);

पूर्णांक sa1111_driver_रेजिस्टर(काष्ठा sa1111_driver *driver)
अणु
	driver->drv.bus = &sa1111_bus_type;
	वापस driver_रेजिस्टर(&driver->drv);
पूर्ण
EXPORT_SYMBOL(sa1111_driver_रेजिस्टर);

व्योम sa1111_driver_unरेजिस्टर(काष्ठा sa1111_driver *driver)
अणु
	driver_unरेजिस्टर(&driver->drv);
पूर्ण
EXPORT_SYMBOL(sa1111_driver_unरेजिस्टर);

#अगर_घोषित CONFIG_DMABOUNCE
/*
 * According to the "Intel StrongARM SA-1111 Microprocessor Companion
 * Chip Specअगरication Update" (June 2000), erratum #7, there is a
 * signअगरicant bug in the SA1111 SDRAM shared memory controller.  If
 * an access to a region of memory above 1MB relative to the bank base,
 * it is important that address bit 10 _NOT_ be निश्चितed. Depending
 * on the configuration of the RAM, bit 10 may correspond to one
 * of several dअगरferent (processor-relative) address bits.
 *
 * This routine only identअगरies whether or not a given DMA address
 * is susceptible to the bug.
 *
 * This should only get called क्रम sa1111_device types due to the
 * way we configure our device dma_masks.
 */
अटल पूर्णांक sa1111_needs_bounce(काष्ठा device *dev, dma_addr_t addr, माप_प्रकार size)
अणु
	/*
	 * Section 4.6 of the "Intel StrongARM SA-1111 Development Module
	 * User's Guide" mentions that jumpers R51 and R52 control the
	 * target of SA-1111 DMA (either SDRAM bank 0 on Assabet, or
	 * SDRAM bank 1 on Neponset). The शेष configuration selects
	 * Assabet, so any address in bank 1 is necessarily invalid.
	 */
	वापस (machine_is_assabet() || machine_is_pfs168()) &&
		(addr >= 0xc8000000 || (addr + size) >= 0xc8000000);
पूर्ण

अटल पूर्णांक sa1111_notअगरier_call(काष्ठा notअगरier_block *n, अचिन्हित दीर्घ action,
	व्योम *data)
अणु
	काष्ठा sa1111_dev *dev = to_sa1111_device(data);

	चयन (action) अणु
	हाल BUS_NOTIFY_ADD_DEVICE:
		अगर (dev->dev.dma_mask && dev->dma_mask < 0xffffffffUL) अणु
			पूर्णांक ret = dmabounce_रेजिस्टर_dev(&dev->dev, 1024, 4096,
					sa1111_needs_bounce);
			अगर (ret)
				dev_err(&dev->dev, "failed to register with dmabounce: %d\n", ret);
		पूर्ण
		अवरोध;

	हाल BUS_NOTIFY_DEL_DEVICE:
		अगर (dev->dev.dma_mask && dev->dma_mask < 0xffffffffUL)
			dmabounce_unरेजिस्टर_dev(&dev->dev);
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block sa1111_bus_notअगरier = अणु
	.notअगरier_call = sa1111_notअगरier_call,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init sa1111_init(व्योम)
अणु
	पूर्णांक ret = bus_रेजिस्टर(&sa1111_bus_type);
#अगर_घोषित CONFIG_DMABOUNCE
	अगर (ret == 0)
		bus_रेजिस्टर_notअगरier(&sa1111_bus_type, &sa1111_bus_notअगरier);
#पूर्ण_अगर
	अगर (ret == 0)
		platक्रमm_driver_रेजिस्टर(&sa1111_device_driver);
	वापस ret;
पूर्ण

अटल व्योम __निकास sa1111_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sa1111_device_driver);
#अगर_घोषित CONFIG_DMABOUNCE
	bus_unरेजिस्टर_notअगरier(&sa1111_bus_type, &sa1111_bus_notअगरier);
#पूर्ण_अगर
	bus_unरेजिस्टर(&sa1111_bus_type);
पूर्ण

subsys_initcall(sa1111_init);
module_निकास(sa1111_निकास);

MODULE_DESCRIPTION("Intel Corporation SA1111 core driver");
MODULE_LICENSE("GPL");
