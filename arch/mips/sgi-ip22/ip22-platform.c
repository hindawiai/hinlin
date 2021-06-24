<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/paccess.h>
#समावेश <यंत्र/sgi/ip22.h>
#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/mc.h>
#समावेश <यंत्र/sgi/seeq.h>
#समावेश <यंत्र/sgi/wd.h>

अटल काष्ठा resource sgiwd93_0_resources[] = अणु
	अणु
		.name	= "eth0 irq",
		.start	= SGI_WD93_0_IRQ,
		.end	= SGI_WD93_0_IRQ,
		.flags	= IORESOURCE_IRQ
	पूर्ण
पूर्ण;

अटल काष्ठा sgiwd93_platक्रमm_data sgiwd93_0_pd = अणु
	.unit	= 0,
	.irq	= SGI_WD93_0_IRQ,
पूर्ण;

अटल u64 sgiwd93_0_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device sgiwd93_0_device = अणु
	.name		= "sgiwd93",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(sgiwd93_0_resources),
	.resource	= sgiwd93_0_resources,
	.dev = अणु
		.platक्रमm_data = &sgiwd93_0_pd,
		.dma_mask = &sgiwd93_0_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा resource sgiwd93_1_resources[] = अणु
	अणु
		.name	= "eth0 irq",
		.start	= SGI_WD93_1_IRQ,
		.end	= SGI_WD93_1_IRQ,
		.flags	= IORESOURCE_IRQ
	पूर्ण
पूर्ण;

अटल काष्ठा sgiwd93_platक्रमm_data sgiwd93_1_pd = अणु
	.unit	= 1,
	.irq	= SGI_WD93_1_IRQ,
पूर्ण;

अटल u64 sgiwd93_1_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device sgiwd93_1_device = अणु
	.name		= "sgiwd93",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(sgiwd93_1_resources),
	.resource	= sgiwd93_1_resources,
	.dev = अणु
		.platक्रमm_data = &sgiwd93_1_pd,
		.dma_mask = &sgiwd93_1_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

/*
 * Create a platक्रमm device क्रम the GPI port that receives the
 * image data from the embedded camera.
 */
अटल पूर्णांक __init sgiwd93_devinit(व्योम)
अणु
	पूर्णांक res;

	sgiwd93_0_pd.hregs	= &hpc3c0->scsi_chan0;
	sgiwd93_0_pd.wdregs	= (अचिन्हित अक्षर *) hpc3c0->scsi0_ext;

	res = platक्रमm_device_रेजिस्टर(&sgiwd93_0_device);
	अगर (res)
		वापस res;

	अगर (!ip22_is_fullhouse())
		वापस 0;

	sgiwd93_1_pd.hregs	= &hpc3c0->scsi_chan1;
	sgiwd93_1_pd.wdregs	= (अचिन्हित अक्षर *) hpc3c0->scsi1_ext;

	वापस platक्रमm_device_रेजिस्टर(&sgiwd93_1_device);
पूर्ण

device_initcall(sgiwd93_devinit);

अटल काष्ठा resource sgiseeq_0_resources[] = अणु
	अणु
		.name	= "eth0 irq",
		.start	= SGI_ENET_IRQ,
		.end	= SGI_ENET_IRQ,
		.flags	= IORESOURCE_IRQ
	पूर्ण
पूर्ण;

अटल काष्ठा sgiseeq_platक्रमm_data eth0_pd;

अटल u64 sgiseeq_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device eth0_device = अणु
	.name		= "sgiseeq",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(sgiseeq_0_resources),
	.resource	= sgiseeq_0_resources,
	.dev = अणु
		.platक्रमm_data = &eth0_pd,
		.dma_mask = &sgiseeq_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा resource sgiseeq_1_resources[] = अणु
	अणु
		.name	= "eth1 irq",
		.start	= SGI_GIO_0_IRQ,
		.end	= SGI_GIO_0_IRQ,
		.flags	= IORESOURCE_IRQ
	पूर्ण
पूर्ण;

अटल काष्ठा sgiseeq_platक्रमm_data eth1_pd;

अटल काष्ठा platक्रमm_device eth1_device = अणु
	.name		= "sgiseeq",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(sgiseeq_1_resources),
	.resource	= sgiseeq_1_resources,
	.dev = अणु
		.platक्रमm_data = &eth1_pd,
	पूर्ण,
पूर्ण;

/*
 * Create a platक्रमm device क्रम the GPI port that receives the
 * image data from the embedded camera.
 */
अटल पूर्णांक __init sgiseeq_devinit(व्योम)
अणु
	अचिन्हित पूर्णांक pbdma __maybe_unused;
	पूर्णांक res, i;

	eth0_pd.hpc = hpc3c0;
	eth0_pd.irq = SGI_ENET_IRQ;
#घोषणा EADDR_NVOFS	250
	क्रम (i = 0; i < 3; i++) अणु
		अचिन्हित लघु पंचांगp = ip22_nvram_पढ़ो(EADDR_NVOFS / 2 + i);

		eth0_pd.mac[2 * i]     = पंचांगp >> 8;
		eth0_pd.mac[2 * i + 1] = पंचांगp & 0xff;
	पूर्ण

	res = platक्रमm_device_रेजिस्टर(&eth0_device);
	अगर (res)
		वापस res;

	/* Second HPC is missing? */
	अगर (ip22_is_fullhouse() ||
	    get_dbe(pbdma, (अचिन्हित पूर्णांक *)&hpc3c1->pbdma[1]))
		वापस 0;

	sgimc->giopar |= SGIMC_GIOPAR_MASTEREXP1 | SGIMC_GIOPAR_EXP164 |
			 SGIMC_GIOPAR_HPC264;
	hpc3c1->pbus_piocfg[0][0] = 0x3ffff;
	/* पूर्णांकerrupt/config रेजिस्टर on Challenge S Mezz board */
	hpc3c1->pbus_extregs[0][0] = 0x30;

	eth1_pd.hpc = hpc3c1;
	eth1_pd.irq = SGI_GIO_0_IRQ;
#घोषणा EADDR_NVOFS	250
	क्रम (i = 0; i < 3; i++) अणु
		अचिन्हित लघु पंचांगp = ip22_eeprom_पढ़ो(&hpc3c1->eeprom,
						      EADDR_NVOFS / 2 + i);

		eth1_pd.mac[2 * i]     = पंचांगp >> 8;
		eth1_pd.mac[2 * i + 1] = पंचांगp & 0xff;
	पूर्ण

	वापस platक्रमm_device_रेजिस्टर(&eth1_device);
पूर्ण

device_initcall(sgiseeq_devinit);

अटल पूर्णांक __init sgi_hal2_devinit(व्योम)
अणु
	वापस IS_ERR(platक्रमm_device_रेजिस्टर_simple("sgihal2", 0, शून्य, 0));
पूर्ण

device_initcall(sgi_hal2_devinit);

अटल पूर्णांक __init sgi_button_devinit(व्योम)
अणु
	अगर (ip22_is_fullhouse())
		वापस 0; /* full house has no volume buttons */

	वापस IS_ERR(platक्रमm_device_रेजिस्टर_simple("sgibtns", -1, शून्य, 0));
पूर्ण

device_initcall(sgi_button_devinit);

अटल पूर्णांक __init sgi_ds1286_devinit(व्योम)
अणु
	काष्ठा resource res;

	स_रखो(&res, 0, माप(res));
	res.start = HPC3_CHIP0_BASE + दुरत्व(काष्ठा hpc3_regs, rtcregs);
	res.end = res.start + माप(hpc3c0->rtcregs) - 1;
	res.flags = IORESOURCE_MEM;

	वापस IS_ERR(platक्रमm_device_रेजिस्टर_simple("rtc-ds1286", -1,
						      &res, 1));
पूर्ण

device_initcall(sgi_ds1286_devinit);
