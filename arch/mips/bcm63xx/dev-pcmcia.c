<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <bcm63xx_cs.h>
#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_dev_pcmcia.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_regs.h>

अटल काष्ठा resource pcmcia_resources[] = अणु
	/* pcmcia रेजिस्टरs */
	अणु
		/* start & end filled at runसमय */
		.flags		= IORESOURCE_MEM,
	पूर्ण,

	/* pcmcia memory zone resources */
	अणु
		.start		= BCM_PCMCIA_COMMON_BASE_PA,
		.end		= BCM_PCMCIA_COMMON_END_PA,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= BCM_PCMCIA_ATTR_BASE_PA,
		.end		= BCM_PCMCIA_ATTR_END_PA,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= BCM_PCMCIA_IO_BASE_PA,
		.end		= BCM_PCMCIA_IO_END_PA,
		.flags		= IORESOURCE_MEM,
	पूर्ण,

	/* PCMCIA irq */
	अणु
		/* start filled at runसमय */
		.flags		= IORESOURCE_IRQ,
	पूर्ण,

	/* declare PCMCIA IO resource also */
	अणु
		.start		= BCM_PCMCIA_IO_BASE_PA,
		.end		= BCM_PCMCIA_IO_END_PA,
		.flags		= IORESOURCE_IO,
	पूर्ण,
पूर्ण;

अटल काष्ठा bcm63xx_pcmcia_platक्रमm_data pd;

अटल काष्ठा platक्रमm_device bcm63xx_pcmcia_device = अणु
	.name		= "bcm63xx_pcmcia",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(pcmcia_resources),
	.resource	= pcmcia_resources,
	.dev		= अणु
		.platक्रमm_data = &pd,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init config_pcmcia_cs(अचिन्हित पूर्णांक cs,
				   u32 base, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक ret;

	ret = bcm63xx_set_cs_status(cs, 0);
	अगर (!ret)
		ret = bcm63xx_set_cs_base(cs, base, size);
	अगर (!ret)
		ret = bcm63xx_set_cs_status(cs, 1);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा अणु
	अचिन्हित पूर्णांक	cs;
	अचिन्हित पूर्णांक	base;
	अचिन्हित पूर्णांक	size;
पूर्ण pcmcia_cs[3] __initस्थिर = अणु
	अणु
		.cs	= MPI_CS_PCMCIA_COMMON,
		.base	= BCM_PCMCIA_COMMON_BASE_PA,
		.size	= BCM_PCMCIA_COMMON_SIZE
	पूर्ण,
	अणु
		.cs	= MPI_CS_PCMCIA_ATTR,
		.base	= BCM_PCMCIA_ATTR_BASE_PA,
		.size	= BCM_PCMCIA_ATTR_SIZE
	पूर्ण,
	अणु
		.cs	= MPI_CS_PCMCIA_IO,
		.base	= BCM_PCMCIA_IO_BASE_PA,
		.size	= BCM_PCMCIA_IO_SIZE
	पूर्ण,
पूर्ण;

पूर्णांक __init bcm63xx_pcmcia_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret, i;

	अगर (!BCMCPU_IS_6348() && !BCMCPU_IS_6358())
		वापस 0;

	/* use correct pcmcia पढ़ोy gpio depending on processor */
	चयन (bcm63xx_get_cpu_id()) अणु
	हाल BCM6348_CPU_ID:
		pd.पढ़ोy_gpio = 22;
		अवरोध;

	हाल BCM6358_CPU_ID:
		pd.पढ़ोy_gpio = 18;
		अवरोध;

	शेष:
		वापस -ENODEV;
	पूर्ण

	pcmcia_resources[0].start = bcm63xx_regset_address(RSET_PCMCIA);
	pcmcia_resources[0].end = pcmcia_resources[0].start +
		RSET_PCMCIA_SIZE - 1;
	pcmcia_resources[4].start = bcm63xx_get_irq_number(IRQ_PCMCIA);

	/* configure pcmcia chip selects */
	क्रम (i = 0; i < 3; i++) अणु
		ret = config_pcmcia_cs(pcmcia_cs[i].cs,
				       pcmcia_cs[i].base,
				       pcmcia_cs[i].size);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	वापस platक्रमm_device_रेजिस्टर(&bcm63xx_pcmcia_device);

out_err:
	pr_err("unable to set pcmcia chip select\n");
	वापस ret;
पूर्ण
