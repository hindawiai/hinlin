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
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/export.h>
#समावेश <bcm63xx_dev_enet.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_regs.h>

अटल स्थिर अचिन्हित दीर्घ bcm6348_regs_enetdmac[] = अणु
	[ENETDMAC_CHANCFG]	= ENETDMAC_CHANCFG_REG,
	[ENETDMAC_IR]		= ENETDMAC_IR_REG,
	[ENETDMAC_IRMASK]	= ENETDMAC_IRMASK_REG,
	[ENETDMAC_MAXBURST]	= ENETDMAC_MAXBURST_REG,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ bcm6345_regs_enetdmac[] = अणु
	[ENETDMAC_CHANCFG]	= ENETDMA_6345_CHANCFG_REG,
	[ENETDMAC_IR]		= ENETDMA_6345_IR_REG,
	[ENETDMAC_IRMASK]	= ENETDMA_6345_IRMASK_REG,
	[ENETDMAC_MAXBURST]	= ENETDMA_6345_MAXBURST_REG,
	[ENETDMAC_BUFALLOC]	= ENETDMA_6345_BUFALLOC_REG,
	[ENETDMAC_RSTART]	= ENETDMA_6345_RSTART_REG,
	[ENETDMAC_FC]		= ENETDMA_6345_FC_REG,
	[ENETDMAC_LEN]		= ENETDMA_6345_LEN_REG,
पूर्ण;

स्थिर अचिन्हित दीर्घ *bcm63xx_regs_enetdmac;
EXPORT_SYMBOL(bcm63xx_regs_enetdmac);

अटल __init व्योम bcm63xx_enetdmac_regs_init(व्योम)
अणु
	अगर (BCMCPU_IS_6345())
		bcm63xx_regs_enetdmac = bcm6345_regs_enetdmac;
	अन्यथा
		bcm63xx_regs_enetdmac = bcm6348_regs_enetdmac;
पूर्ण

अटल काष्ठा resource shared_res[] = अणु
	अणु
		.start		= -1, /* filled at runसमय */
		.end		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= -1, /* filled at runसमय */
		.end		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= -1, /* filled at runसमय */
		.end		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device bcm63xx_enet_shared_device = अणु
	.name		= "bcm63xx_enet_shared",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(shared_res),
	.resource	= shared_res,
पूर्ण;

अटल पूर्णांक shared_device_रेजिस्टरed;

अटल u64 enet_dmamask = DMA_BIT_MASK(32);

अटल काष्ठा resource enet0_res[] = अणु
	अणु
		.start		= -1, /* filled at runसमय */
		.end		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा bcm63xx_enet_platक्रमm_data enet0_pd;

अटल काष्ठा platक्रमm_device bcm63xx_enet0_device = अणु
	.name		= "bcm63xx_enet",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(enet0_res),
	.resource	= enet0_res,
	.dev		= अणु
		.platक्रमm_data = &enet0_pd,
		.dma_mask = &enet_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा resource enet1_res[] = अणु
	अणु
		.start		= -1, /* filled at runसमय */
		.end		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा bcm63xx_enet_platक्रमm_data enet1_pd;

अटल काष्ठा platक्रमm_device bcm63xx_enet1_device = अणु
	.name		= "bcm63xx_enet",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(enet1_res),
	.resource	= enet1_res,
	.dev		= अणु
		.platक्रमm_data = &enet1_pd,
		.dma_mask = &enet_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा resource enetsw_res[] = अणु
	अणु
		/* start & end filled at runसमय */
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		/* start filled at runसमय */
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		/* start filled at runसमय */
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा bcm63xx_enetsw_platक्रमm_data enetsw_pd;

अटल काष्ठा platक्रमm_device bcm63xx_enetsw_device = अणु
	.name		= "bcm63xx_enetsw",
	.num_resources	= ARRAY_SIZE(enetsw_res),
	.resource	= enetsw_res,
	.dev		= अणु
		.platक्रमm_data = &enetsw_pd,
		.dma_mask = &enet_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_shared(व्योम)
अणु
	पूर्णांक ret, chan_count;

	अगर (shared_device_रेजिस्टरed)
		वापस 0;

	bcm63xx_enetdmac_regs_init();

	shared_res[0].start = bcm63xx_regset_address(RSET_ENETDMA);
	shared_res[0].end = shared_res[0].start;
	अगर (BCMCPU_IS_6345())
		shared_res[0].end += (RSET_6345_ENETDMA_SIZE) - 1;
	अन्यथा
		shared_res[0].end += (RSET_ENETDMA_SIZE)  - 1;

	अगर (BCMCPU_IS_6328() || BCMCPU_IS_6362() || BCMCPU_IS_6368())
		chan_count = 32;
	अन्यथा अगर (BCMCPU_IS_6345())
		chan_count = 8;
	अन्यथा
		chan_count = 16;

	shared_res[1].start = bcm63xx_regset_address(RSET_ENETDMAC);
	shared_res[1].end = shared_res[1].start;
	shared_res[1].end += RSET_ENETDMAC_SIZE(chan_count)  - 1;

	shared_res[2].start = bcm63xx_regset_address(RSET_ENETDMAS);
	shared_res[2].end = shared_res[2].start;
	shared_res[2].end += RSET_ENETDMAS_SIZE(chan_count)  - 1;

	ret = platक्रमm_device_रेजिस्टर(&bcm63xx_enet_shared_device);
	अगर (ret)
		वापस ret;
	shared_device_रेजिस्टरed = 1;

	वापस 0;
पूर्ण

पूर्णांक __init bcm63xx_enet_रेजिस्टर(पूर्णांक unit,
				 स्थिर काष्ठा bcm63xx_enet_platक्रमm_data *pd)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा bcm63xx_enet_platक्रमm_data *dpd;
	पूर्णांक ret;

	अगर (unit > 1)
		वापस -ENODEV;

	अगर (unit == 1 && (BCMCPU_IS_6338() || BCMCPU_IS_6345()))
		वापस -ENODEV;

	ret = रेजिस्टर_shared();
	अगर (ret)
		वापस ret;

	अगर (unit == 0) अणु
		enet0_res[0].start = bcm63xx_regset_address(RSET_ENET0);
		enet0_res[0].end = enet0_res[0].start;
		enet0_res[0].end += RSET_ENET_SIZE - 1;
		enet0_res[1].start = bcm63xx_get_irq_number(IRQ_ENET0);
		enet0_res[2].start = bcm63xx_get_irq_number(IRQ_ENET0_RXDMA);
		enet0_res[3].start = bcm63xx_get_irq_number(IRQ_ENET0_TXDMA);
		pdev = &bcm63xx_enet0_device;
	पूर्ण अन्यथा अणु
		enet1_res[0].start = bcm63xx_regset_address(RSET_ENET1);
		enet1_res[0].end = enet1_res[0].start;
		enet1_res[0].end += RSET_ENET_SIZE - 1;
		enet1_res[1].start = bcm63xx_get_irq_number(IRQ_ENET1);
		enet1_res[2].start = bcm63xx_get_irq_number(IRQ_ENET1_RXDMA);
		enet1_res[3].start = bcm63xx_get_irq_number(IRQ_ENET1_TXDMA);
		pdev = &bcm63xx_enet1_device;
	पूर्ण

	/* copy given platक्रमm data */
	dpd = pdev->dev.platक्रमm_data;
	स_नकल(dpd, pd, माप(*pd));

	/* adjust them in हाल पूर्णांकernal phy is used */
	अगर (dpd->use_पूर्णांकernal_phy) अणु

		/* पूर्णांकernal phy only exists क्रम enet0 */
		अगर (unit == 1)
			वापस -ENODEV;

		dpd->phy_id = 1;
		dpd->has_phy_पूर्णांकerrupt = 1;
		dpd->phy_पूर्णांकerrupt = bcm63xx_get_irq_number(IRQ_ENET_PHY);
	पूर्ण

	dpd->dma_chan_en_mask = ENETDMAC_CHANCFG_EN_MASK;
	dpd->dma_chan_पूर्णांक_mask = ENETDMAC_IR_PKTDONE_MASK;
	अगर (BCMCPU_IS_6345()) अणु
		dpd->dma_chan_en_mask |= ENETDMAC_CHANCFG_CHAINING_MASK;
		dpd->dma_chan_en_mask |= ENETDMAC_CHANCFG_WRAP_EN_MASK;
		dpd->dma_chan_en_mask |= ENETDMAC_CHANCFG_FLOWC_EN_MASK;
		dpd->dma_chan_पूर्णांक_mask |= ENETDMA_IR_BUFDONE_MASK;
		dpd->dma_chan_पूर्णांक_mask |= ENETDMA_IR_NOTOWNER_MASK;
		dpd->dma_chan_width = ENETDMA_6345_CHAN_WIDTH;
		dpd->dma_desc_shअगरt = ENETDMA_6345_DESC_SHIFT;
	पूर्ण अन्यथा अणु
		dpd->dma_has_sram = true;
		dpd->dma_chan_width = ENETDMA_CHAN_WIDTH;
	पूर्ण

	अगर (unit == 0) अणु
		dpd->rx_chan = 0;
		dpd->tx_chan = 1;
	पूर्ण अन्यथा अणु
		dpd->rx_chan = 2;
		dpd->tx_chan = 3;
	पूर्ण

	ret = platक्रमm_device_रेजिस्टर(pdev);
	अगर (ret)
		वापस ret;
	वापस 0;
पूर्ण

पूर्णांक __init
bcm63xx_enetsw_रेजिस्टर(स्थिर काष्ठा bcm63xx_enetsw_platक्रमm_data *pd)
अणु
	पूर्णांक ret;

	अगर (!BCMCPU_IS_6328() && !BCMCPU_IS_6362() && !BCMCPU_IS_6368())
		वापस -ENODEV;

	ret = रेजिस्टर_shared();
	अगर (ret)
		वापस ret;

	enetsw_res[0].start = bcm63xx_regset_address(RSET_ENETSW);
	enetsw_res[0].end = enetsw_res[0].start;
	enetsw_res[0].end += RSET_ENETSW_SIZE - 1;
	enetsw_res[1].start = bcm63xx_get_irq_number(IRQ_ENETSW_RXDMA0);
	enetsw_res[2].start = bcm63xx_get_irq_number(IRQ_ENETSW_TXDMA0);
	अगर (!enetsw_res[2].start)
		enetsw_res[2].start = -1;

	स_नकल(bcm63xx_enetsw_device.dev.platक्रमm_data, pd, माप(*pd));

	अगर (BCMCPU_IS_6328())
		enetsw_pd.num_ports = ENETSW_PORTS_6328;
	अन्यथा अगर (BCMCPU_IS_6362() || BCMCPU_IS_6368())
		enetsw_pd.num_ports = ENETSW_PORTS_6368;

	enetsw_pd.dma_has_sram = true;
	enetsw_pd.dma_chan_width = ENETDMA_CHAN_WIDTH;
	enetsw_pd.dma_chan_en_mask = ENETDMAC_CHANCFG_EN_MASK;
	enetsw_pd.dma_chan_पूर्णांक_mask = ENETDMAC_IR_PKTDONE_MASK;

	ret = platक्रमm_device_रेजिस्टर(&bcm63xx_enetsw_device);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
