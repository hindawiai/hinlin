<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/pcmcia/sa1111_generic.c
 *
 * We implement the generic parts of a SA1111 PCMCIA driver.  This
 * basically means we handle everything except controlling the
 * घातer.  Power is machine specअगरic...
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश <pcmcia/ss.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/hardware/sa1111.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/irq.h>

#समावेश "sa1111_generic.h"

/*
 * These are offsets from the above base.
 */
#घोषणा PCCR	0x0000
#घोषणा PCSSR	0x0004
#घोषणा PCSR	0x0008

#घोषणा PCSR_S0_READY	(1<<0)
#घोषणा PCSR_S1_READY	(1<<1)
#घोषणा PCSR_S0_DETECT	(1<<2)
#घोषणा PCSR_S1_DETECT	(1<<3)
#घोषणा PCSR_S0_VS1	(1<<4)
#घोषणा PCSR_S0_VS2	(1<<5)
#घोषणा PCSR_S1_VS1	(1<<6)
#घोषणा PCSR_S1_VS2	(1<<7)
#घोषणा PCSR_S0_WP	(1<<8)
#घोषणा PCSR_S1_WP	(1<<9)
#घोषणा PCSR_S0_BVD1	(1<<10)
#घोषणा PCSR_S0_BVD2	(1<<11)
#घोषणा PCSR_S1_BVD1	(1<<12)
#घोषणा PCSR_S1_BVD2	(1<<13)

#घोषणा PCCR_S0_RST	(1<<0)
#घोषणा PCCR_S1_RST	(1<<1)
#घोषणा PCCR_S0_FLT	(1<<2)
#घोषणा PCCR_S1_FLT	(1<<3)
#घोषणा PCCR_S0_PWAITEN	(1<<4)
#घोषणा PCCR_S1_PWAITEN	(1<<5)
#घोषणा PCCR_S0_PSE	(1<<6)
#घोषणा PCCR_S1_PSE	(1<<7)

#घोषणा PCSSR_S0_SLEEP	(1<<0)
#घोषणा PCSSR_S1_SLEEP	(1<<1)

#घोषणा IDX_IRQ_S0_READY_NINT	(0)
#घोषणा IDX_IRQ_S0_CD_VALID	(1)
#घोषणा IDX_IRQ_S0_BVD1_STSCHG	(2)
#घोषणा IDX_IRQ_S1_READY_NINT	(3)
#घोषणा IDX_IRQ_S1_CD_VALID	(4)
#घोषणा IDX_IRQ_S1_BVD1_STSCHG	(5)
#घोषणा NUM_IRQS		(6)

व्योम sa1111_pcmcia_socket_state(काष्ठा soc_pcmcia_socket *skt, काष्ठा pcmcia_state *state)
अणु
	काष्ठा sa1111_pcmcia_socket *s = to_skt(skt);
	u32 status = पढ़ोl_relaxed(s->dev->mapbase + PCSR);

	चयन (skt->nr) अणु
	हाल 0:
		state->detect = status & PCSR_S0_DETECT ? 0 : 1;
		state->पढ़ोy  = status & PCSR_S0_READY  ? 1 : 0;
		state->bvd1   = status & PCSR_S0_BVD1   ? 1 : 0;
		state->bvd2   = status & PCSR_S0_BVD2   ? 1 : 0;
		state->wrprot = status & PCSR_S0_WP     ? 1 : 0;
		state->vs_3v  = status & PCSR_S0_VS1    ? 0 : 1;
		state->vs_Xv  = status & PCSR_S0_VS2    ? 0 : 1;
		अवरोध;

	हाल 1:
		state->detect = status & PCSR_S1_DETECT ? 0 : 1;
		state->पढ़ोy  = status & PCSR_S1_READY  ? 1 : 0;
		state->bvd1   = status & PCSR_S1_BVD1   ? 1 : 0;
		state->bvd2   = status & PCSR_S1_BVD2   ? 1 : 0;
		state->wrprot = status & PCSR_S1_WP     ? 1 : 0;
		state->vs_3v  = status & PCSR_S1_VS1    ? 0 : 1;
		state->vs_Xv  = status & PCSR_S1_VS2    ? 0 : 1;
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक sa1111_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt, स्थिर socket_state_t *state)
अणु
	काष्ठा sa1111_pcmcia_socket *s = to_skt(skt);
	u32 pccr_skt_mask, pccr_set_mask, val;
	अचिन्हित दीर्घ flags;

	चयन (skt->nr) अणु
	हाल 0:
		pccr_skt_mask = PCCR_S0_RST|PCCR_S0_FLT|PCCR_S0_PWAITEN|PCCR_S0_PSE;
		अवरोध;

	हाल 1:
		pccr_skt_mask = PCCR_S1_RST|PCCR_S1_FLT|PCCR_S1_PWAITEN|PCCR_S1_PSE;
		अवरोध;

	शेष:
		वापस -1;
	पूर्ण

	pccr_set_mask = 0;

	अगर (state->Vcc != 0)
		pccr_set_mask |= PCCR_S0_PWAITEN|PCCR_S1_PWAITEN;
	अगर (state->Vcc == 50)
		pccr_set_mask |= PCCR_S0_PSE|PCCR_S1_PSE;
	अगर (state->flags & SS_RESET)
		pccr_set_mask |= PCCR_S0_RST|PCCR_S1_RST;
	अगर (state->flags & SS_OUTPUT_ENA)
		pccr_set_mask |= PCCR_S0_FLT|PCCR_S1_FLT;

	local_irq_save(flags);
	val = पढ़ोl_relaxed(s->dev->mapbase + PCCR);
	val &= ~pccr_skt_mask;
	val |= pccr_set_mask & pccr_skt_mask;
	ग_लिखोl_relaxed(val, s->dev->mapbase + PCCR);
	local_irq_restore(flags);

	वापस 0;
पूर्ण

पूर्णांक sa1111_pcmcia_add(काष्ठा sa1111_dev *dev, काष्ठा pcmcia_low_level *ops,
	पूर्णांक (*add)(काष्ठा soc_pcmcia_socket *))
अणु
	काष्ठा sa1111_pcmcia_socket *s;
	काष्ठा clk *clk;
	पूर्णांक i, ret = 0, irqs[NUM_IRQS];

	clk = devm_clk_get(&dev->dev, शून्य);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	क्रम (i = 0; i < NUM_IRQS; i++) अणु
		irqs[i] = sa1111_get_irq(dev, i);
		अगर (irqs[i] <= 0)
			वापस irqs[i] ? : -ENXIO;
	पूर्ण

	ops->socket_state = sa1111_pcmcia_socket_state;

	क्रम (i = 0; i < ops->nr; i++) अणु
		s = kzalloc(माप(*s), GFP_KERNEL);
		अगर (!s)
			वापस -ENOMEM;

		s->soc.nr = ops->first + i;
		s->soc.clk = clk;

		soc_pcmcia_init_one(&s->soc, ops, &dev->dev);
		s->dev = dev;
		अगर (s->soc.nr) अणु
			s->soc.socket.pci_irq = irqs[IDX_IRQ_S1_READY_NINT];
			s->soc.stat[SOC_STAT_CD].irq = irqs[IDX_IRQ_S1_CD_VALID];
			s->soc.stat[SOC_STAT_CD].name = "SA1111 CF card detect";
			s->soc.stat[SOC_STAT_BVD1].irq = irqs[IDX_IRQ_S1_BVD1_STSCHG];
			s->soc.stat[SOC_STAT_BVD1].name = "SA1111 CF BVD1";
		पूर्ण अन्यथा अणु
			s->soc.socket.pci_irq = irqs[IDX_IRQ_S0_READY_NINT];
			s->soc.stat[SOC_STAT_CD].irq = irqs[IDX_IRQ_S0_CD_VALID];
			s->soc.stat[SOC_STAT_CD].name = "SA1111 PCMCIA card detect";
			s->soc.stat[SOC_STAT_BVD1].irq = irqs[IDX_IRQ_S0_BVD1_STSCHG];
			s->soc.stat[SOC_STAT_BVD1].name = "SA1111 PCMCIA BVD1";
		पूर्ण

		ret = add(&s->soc);
		अगर (ret == 0) अणु
			s->next = dev_get_drvdata(&dev->dev);
			dev_set_drvdata(&dev->dev, s);
		पूर्ण अन्यथा
			kमुक्त(s);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pcmcia_probe(काष्ठा sa1111_dev *dev)
अणु
	व्योम __iomem *base;
	पूर्णांक ret;

	ret = sa1111_enable_device(dev);
	अगर (ret)
		वापस ret;

	dev_set_drvdata(&dev->dev, शून्य);

	अगर (!request_mem_region(dev->res.start, 512, SA1111_DRIVER_NAME(dev))) अणु
		sa1111_disable_device(dev);
		वापस -EBUSY;
	पूर्ण

	base = dev->mapbase;

	/*
	 * Initialise the suspend state.
	 */
	ग_लिखोl_relaxed(PCSSR_S0_SLEEP | PCSSR_S1_SLEEP, base + PCSSR);
	ग_लिखोl_relaxed(PCCR_S0_FLT | PCCR_S1_FLT, base + PCCR);

	ret = -ENODEV;
#अगर_घोषित CONFIG_SA1100_BADGE4
	अगर (machine_is_badge4())
		ret = pcmcia_badge4_init(dev);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SA1100_JORNADA720
	अगर (machine_is_jornada720())
		ret = pcmcia_jornada720_init(dev);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_LUBBOCK
	अगर (machine_is_lubbock())
		ret = pcmcia_lubbock_init(dev);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ASSABET_NEPONSET
	अगर (machine_is_assabet())
		ret = pcmcia_neponset_init(dev);
#पूर्ण_अगर

	अगर (ret) अणु
		release_mem_region(dev->res.start, 512);
		sa1111_disable_device(dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम pcmcia_हटाओ(काष्ठा sa1111_dev *dev)
अणु
	काष्ठा sa1111_pcmcia_socket *next, *s = dev_get_drvdata(&dev->dev);

	dev_set_drvdata(&dev->dev, शून्य);

	क्रम (; s; s = next) अणु
		next = s->next;
		soc_pcmcia_हटाओ_one(&s->soc);
		kमुक्त(s);
	पूर्ण

	release_mem_region(dev->res.start, 512);
	sa1111_disable_device(dev);
पूर्ण

अटल काष्ठा sa1111_driver pcmcia_driver = अणु
	.drv = अणु
		.name	= "sa1111-pcmcia",
	पूर्ण,
	.devid		= SA1111_DEVID_PCMCIA,
	.probe		= pcmcia_probe,
	.हटाओ		= pcmcia_हटाओ,
पूर्ण;

अटल पूर्णांक __init sa1111_drv_pcmcia_init(व्योम)
अणु
	वापस sa1111_driver_रेजिस्टर(&pcmcia_driver);
पूर्ण

अटल व्योम __निकास sa1111_drv_pcmcia_निकास(व्योम)
अणु
	sa1111_driver_unरेजिस्टर(&pcmcia_driver);
पूर्ण

fs_initcall(sa1111_drv_pcmcia_init);
module_निकास(sa1111_drv_pcmcia_निकास);

MODULE_DESCRIPTION("SA1111 PCMCIA card socket driver");
MODULE_LICENSE("GPL");
