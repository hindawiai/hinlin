<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * bdc_core.c - BRCM BDC USB3.0 device controller core operations
 *
 * Copyright (C) 2014 Broadcom Corporation
 *
 * Author: Ashwini Pahuja
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/clk.h>

#समावेश "bdc.h"
#समावेश "bdc_dbg.h"

/* Poll till controller status is not OIP */
अटल पूर्णांक poll_oip(काष्ठा bdc *bdc, u32 usec)
अणु
	u32 status;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout(bdc->regs + BDC_BDCSC, status,
				 (BDC_CSTS(status) != BDC_OIP), 10, usec);
	अगर (ret)
		dev_err(bdc->dev, "operation timedout BDCSC: 0x%08x\n", status);
	अन्यथा
		dev_dbg(bdc->dev, "%s complete status=%d", __func__, BDC_CSTS(status));

	वापस ret;
पूर्ण

/* Stop the BDC controller */
पूर्णांक bdc_stop(काष्ठा bdc *bdc)
अणु
	पूर्णांक ret;
	u32 temp;

	dev_dbg(bdc->dev, "%s ()\n\n", __func__);
	temp = bdc_पढ़ोl(bdc->regs, BDC_BDCSC);
	/* Check अगर BDC is alपढ़ोy halted */
	अगर (BDC_CSTS(temp) == BDC_HLT) अणु
		dev_vdbg(bdc->dev, "BDC already halted\n");
		वापस 0;
	पूर्ण
	temp &= ~BDC_COP_MASK;
	temp |= BDC_COS|BDC_COP_STP;
	bdc_ग_लिखोl(bdc->regs, BDC_BDCSC, temp);

	ret = poll_oip(bdc, BDC_COP_TIMEOUT);
	अगर (ret)
		dev_err(bdc->dev, "bdc stop operation failed");

	वापस ret;
पूर्ण

/* Issue a reset to BDC controller */
पूर्णांक bdc_reset(काष्ठा bdc *bdc)
अणु
	u32 temp;
	पूर्णांक ret;

	dev_dbg(bdc->dev, "%s ()\n", __func__);
	/* First halt the controller */
	ret = bdc_stop(bdc);
	अगर (ret)
		वापस ret;

	temp = bdc_पढ़ोl(bdc->regs, BDC_BDCSC);
	temp &= ~BDC_COP_MASK;
	temp |= BDC_COS|BDC_COP_RST;
	bdc_ग_लिखोl(bdc->regs, BDC_BDCSC, temp);
	ret = poll_oip(bdc, BDC_COP_TIMEOUT);
	अगर (ret)
		dev_err(bdc->dev, "bdc reset operation failed");

	वापस ret;
पूर्ण

/* Run the BDC controller */
पूर्णांक bdc_run(काष्ठा bdc *bdc)
अणु
	u32 temp;
	पूर्णांक ret;

	dev_dbg(bdc->dev, "%s ()\n", __func__);
	temp = bdc_पढ़ोl(bdc->regs, BDC_BDCSC);
	/* अगर BDC is alपढ़ोy in running state then करो not करो anything */
	अगर (BDC_CSTS(temp) == BDC_NOR) अणु
		dev_warn(bdc->dev, "bdc is already in running state\n");
		वापस 0;
	पूर्ण
	temp &= ~BDC_COP_MASK;
	temp |= BDC_COP_RUN;
	temp |= BDC_COS;
	bdc_ग_लिखोl(bdc->regs, BDC_BDCSC, temp);
	ret = poll_oip(bdc, BDC_COP_TIMEOUT);
	अगर (ret) अणु
		dev_err(bdc->dev, "bdc run operation failed:%d", ret);
		वापस ret;
	पूर्ण
	temp = bdc_पढ़ोl(bdc->regs, BDC_BDCSC);
	अगर (BDC_CSTS(temp) != BDC_NOR) अणु
		dev_err(bdc->dev, "bdc not in normal mode after RUN op :%d\n",
								BDC_CSTS(temp));
		वापस -ESHUTDOWN;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Present the termination to the host, typically called from upstream port
 * event with Vbus present =1
 */
व्योम bdc_softconn(काष्ठा bdc *bdc)
अणु
	u32 uspc;

	uspc = bdc_पढ़ोl(bdc->regs, BDC_USPC);
	uspc &= ~BDC_PST_MASK;
	uspc |= BDC_LINK_STATE_RX_DET;
	uspc |= BDC_SWS;
	dev_dbg(bdc->dev, "%s () uspc=%08x\n", __func__, uspc);
	bdc_ग_लिखोl(bdc->regs, BDC_USPC, uspc);
पूर्ण

/* Remove the termination */
व्योम bdc_softdisconn(काष्ठा bdc *bdc)
अणु
	u32 uspc;

	uspc = bdc_पढ़ोl(bdc->regs, BDC_USPC);
	uspc |= BDC_SDC;
	uspc &= ~BDC_SCN;
	dev_dbg(bdc->dev, "%s () uspc=%x\n", __func__, uspc);
	bdc_ग_लिखोl(bdc->regs, BDC_USPC, uspc);
पूर्ण

/* Set up the scratchpad buffer array and scratchpad buffers, अगर needed. */
अटल पूर्णांक scratchpad_setup(काष्ठा bdc *bdc)
अणु
	पूर्णांक sp_buff_size;
	u32 low32;
	u32 upp32;

	sp_buff_size = BDC_SPB(bdc_पढ़ोl(bdc->regs, BDC_BDCCFG0));
	dev_dbg(bdc->dev, "%s() sp_buff_size=%d\n", __func__, sp_buff_size);
	अगर (!sp_buff_size) अणु
		dev_dbg(bdc->dev, "Scratchpad buffer not needed\n");
		वापस 0;
	पूर्ण
	/* Refer to BDC spec, Table 4 क्रम description of SPB */
	sp_buff_size = 1 << (sp_buff_size + 5);
	dev_dbg(bdc->dev, "Allocating %d bytes for scratchpad\n", sp_buff_size);
	bdc->scratchpad.buff  =  dma_alloc_coherent(bdc->dev, sp_buff_size,
						    &bdc->scratchpad.sp_dma,
						    GFP_KERNEL);

	अगर (!bdc->scratchpad.buff)
		जाओ fail;

	bdc->sp_buff_size = sp_buff_size;
	bdc->scratchpad.size = sp_buff_size;
	low32 = lower_32_bits(bdc->scratchpad.sp_dma);
	upp32 = upper_32_bits(bdc->scratchpad.sp_dma);
	cpu_to_le32s(&low32);
	cpu_to_le32s(&upp32);
	bdc_ग_लिखोl(bdc->regs, BDC_SPBBAL, low32);
	bdc_ग_लिखोl(bdc->regs, BDC_SPBBAH, upp32);
	वापस 0;

fail:
	bdc->scratchpad.buff = शून्य;

	वापस -ENOMEM;
पूर्ण

/* Allocate the status report ring */
अटल पूर्णांक setup_srr(काष्ठा bdc *bdc, पूर्णांक पूर्णांकerrupter)
अणु
	dev_dbg(bdc->dev, "%s() NUM_SR_ENTRIES:%d\n", __func__, NUM_SR_ENTRIES);
	/* Reset the SRR */
	bdc_ग_लिखोl(bdc->regs, BDC_SRRINT(0), BDC_SRR_RWS | BDC_SRR_RST);
	bdc->srr.dqp_index = 0;
	/* allocate the status report descriptors */
	bdc->srr.sr_bds = dma_alloc_coherent(bdc->dev,
					     NUM_SR_ENTRIES * माप(काष्ठा bdc_bd),
					     &bdc->srr.dma_addr, GFP_KERNEL);
	अगर (!bdc->srr.sr_bds)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/* Initialize the HW regs and पूर्णांकernal data काष्ठाures */
अटल व्योम bdc_mem_init(काष्ठा bdc *bdc, bool reinit)
अणु
	u8 size = 0;
	u32 usb2_pm;
	u32 low32;
	u32 upp32;
	u32 temp;

	dev_dbg(bdc->dev, "%s ()\n", __func__);
	bdc->ep0_state = WAIT_FOR_SETUP;
	bdc->dev_addr = 0;
	bdc->srr.eqp_index = 0;
	bdc->srr.dqp_index = 0;
	bdc->zlp_needed = false;
	bdc->delayed_status = false;

	bdc_ग_लिखोl(bdc->regs, BDC_SPBBAL, bdc->scratchpad.sp_dma);
	/* Init the SRR */
	temp = BDC_SRR_RWS | BDC_SRR_RST;
	/* Reset the SRR */
	bdc_ग_लिखोl(bdc->regs, BDC_SRRINT(0), temp);
	dev_dbg(bdc->dev, "bdc->srr.sr_bds =%p\n", bdc->srr.sr_bds);
	temp = lower_32_bits(bdc->srr.dma_addr);
	size = fls(NUM_SR_ENTRIES) - 2;
	temp |= size;
	dev_dbg(bdc->dev, "SRRBAL[0]=%08x NUM_SR_ENTRIES:%d size:%d\n",
						temp, NUM_SR_ENTRIES, size);

	low32 = lower_32_bits(temp);
	upp32 = upper_32_bits(bdc->srr.dma_addr);
	cpu_to_le32s(&low32);
	cpu_to_le32s(&upp32);

	/* Write the dma addresses पूर्णांकo regs*/
	bdc_ग_लिखोl(bdc->regs, BDC_SRRBAL(0), low32);
	bdc_ग_लिखोl(bdc->regs, BDC_SRRBAH(0), upp32);

	temp = bdc_पढ़ोl(bdc->regs, BDC_SRRINT(0));
	temp |= BDC_SRR_IE;
	temp &= ~(BDC_SRR_RST | BDC_SRR_RWS);
	bdc_ग_लिखोl(bdc->regs, BDC_SRRINT(0), temp);

	/* Set the Interrupt Coalescence ~500 usec */
	temp = bdc_पढ़ोl(bdc->regs, BDC_INTCTLS(0));
	temp &= ~0xffff;
	temp |= INT_CLS;
	bdc_ग_लिखोl(bdc->regs, BDC_INTCTLS(0), temp);

	usb2_pm = bdc_पढ़ोl(bdc->regs, BDC_USPPM2);
	dev_dbg(bdc->dev, "usb2_pm=%08x", usb2_pm);
	/* Enable hardware LPM Enable */
	usb2_pm |= BDC_HLE;
	bdc_ग_लिखोl(bdc->regs, BDC_USPPM2, usb2_pm);

	/* पढ़ोback क्रम debug */
	usb2_pm = bdc_पढ़ोl(bdc->regs, BDC_USPPM2);
	dev_dbg(bdc->dev, "usb2_pm=%08x\n", usb2_pm);

	/* Disable any unwanted SR's on SRR */
	temp = bdc_पढ़ोl(bdc->regs, BDC_BDCSC);
	/* We करोn't want Microframe counter wrap SR */
	temp |= BDC_MASK_MCW;
	bdc_ग_लिखोl(bdc->regs, BDC_BDCSC, temp);

	/*
	 * In some error हालs, driver has to reset the entire BDC controller
	 * in that हाल reinit is passed as 1
	 */
	अगर (reinit) अणु
		पूर्णांक i;
		/* Enable पूर्णांकerrupts */
		temp = bdc_पढ़ोl(bdc->regs, BDC_BDCSC);
		temp |= BDC_GIE;
		bdc_ग_लिखोl(bdc->regs, BDC_BDCSC, temp);
		/* Init scratchpad to 0 */
		स_रखो(bdc->scratchpad.buff, 0, bdc->sp_buff_size);
		/* Initialize SRR to 0 */
		स_रखो(bdc->srr.sr_bds, 0,
					NUM_SR_ENTRIES * माप(काष्ठा bdc_bd));
		/*
		 * clear ep flags to aव्योम post disconnect stops/deconfigs but
		 * not during S2 निकास
		 */
		अगर (!bdc->gadget.speed)
			क्रम (i = 1; i < bdc->num_eps; ++i)
				bdc->bdc_ep_array[i]->flags = 0;
	पूर्ण अन्यथा अणु
		/* One समय initiaization only */
		/* Enable status report function poपूर्णांकers */
		bdc->sr_handler[0] = bdc_sr_xsf;
		bdc->sr_handler[1] = bdc_sr_uspc;

		/* EP0 status report function poपूर्णांकers */
		bdc->sr_xsf_ep0[0] = bdc_xsf_ep0_setup_recv;
		bdc->sr_xsf_ep0[1] = bdc_xsf_ep0_data_start;
		bdc->sr_xsf_ep0[2] = bdc_xsf_ep0_status_start;
	पूर्ण
पूर्ण

/* Free the dynamic memory */
अटल व्योम bdc_mem_मुक्त(काष्ठा bdc *bdc)
अणु
	dev_dbg(bdc->dev, "%s\n", __func__);
	/* Free SRR */
	अगर (bdc->srr.sr_bds)
		dma_मुक्त_coherent(bdc->dev,
					NUM_SR_ENTRIES * माप(काष्ठा bdc_bd),
					bdc->srr.sr_bds, bdc->srr.dma_addr);

	/* Free scratchpad */
	अगर (bdc->scratchpad.buff)
		dma_मुक्त_coherent(bdc->dev, bdc->sp_buff_size,
				bdc->scratchpad.buff, bdc->scratchpad.sp_dma);

	/* Destroy the dma pools */
	dma_pool_destroy(bdc->bd_table_pool);

	/* Free the bdc_ep array */
	kमुक्त(bdc->bdc_ep_array);

	bdc->srr.sr_bds = शून्य;
	bdc->scratchpad.buff = शून्य;
	bdc->bd_table_pool = शून्य;
	bdc->bdc_ep_array = शून्य;
पूर्ण

/*
 * bdc reinit gives a controller reset and reinitialize the रेजिस्टरs,
 * called from disconnect/bus reset scenario's, to ensure proper HW cleanup
 */
पूर्णांक bdc_reinit(काष्ठा bdc *bdc)
अणु
	पूर्णांक ret;

	dev_dbg(bdc->dev, "%s\n", __func__);
	ret = bdc_stop(bdc);
	अगर (ret)
		जाओ out;

	ret = bdc_reset(bdc);
	अगर (ret)
		जाओ out;

	/* the reinit flag is 1 */
	bdc_mem_init(bdc, true);
	ret = bdc_run(bdc);
out:
	bdc->reinit = false;

	वापस ret;
पूर्ण

/* Allocate all the dyanmic memory */
अटल पूर्णांक bdc_mem_alloc(काष्ठा bdc *bdc)
अणु
	u32 page_size;
	अचिन्हित पूर्णांक num_ieps, num_oeps;

	dev_dbg(bdc->dev,
		"%s() NUM_BDS_PER_TABLE:%d\n", __func__,
		NUM_BDS_PER_TABLE);
	page_size = BDC_PGS(bdc_पढ़ोl(bdc->regs, BDC_BDCCFG0));
	/* page size is 2^pgs KB */
	page_size = 1 << page_size;
	/* KB */
	page_size <<= 10;
	dev_dbg(bdc->dev, "page_size=%d\n", page_size);

	/* Create a pool of bd tables */
	bdc->bd_table_pool =
	    dma_pool_create("BDC BD tables", bdc->dev, NUM_BDS_PER_TABLE * 16,
								16, page_size);

	अगर (!bdc->bd_table_pool)
		जाओ fail;

	अगर (scratchpad_setup(bdc))
		जाओ fail;

	/* पढ़ो from regs */
	num_ieps = NUM_NCS(bdc_पढ़ोl(bdc->regs, BDC_FSCNIC));
	num_oeps = NUM_NCS(bdc_पढ़ोl(bdc->regs, BDC_FSCNOC));
	/* +2: 1 क्रम ep0 and the other is rsvd i.e. bdc_ep[0] is rsvd */
	bdc->num_eps = num_ieps + num_oeps + 2;
	dev_dbg(bdc->dev,
		"ieps:%d eops:%d num_eps:%d\n",
		num_ieps, num_oeps, bdc->num_eps);
	/* allocate array of ep poपूर्णांकers */
	bdc->bdc_ep_array = kसुस्मृति(bdc->num_eps, माप(काष्ठा bdc_ep *),
								GFP_KERNEL);
	अगर (!bdc->bdc_ep_array)
		जाओ fail;

	dev_dbg(bdc->dev, "Allocating sr report0\n");
	अगर (setup_srr(bdc, 0))
		जाओ fail;

	वापस 0;
fail:
	dev_warn(bdc->dev, "Couldn't initialize memory\n");
	bdc_mem_मुक्त(bdc);

	वापस -ENOMEM;
पूर्ण

/* opposite to bdc_hw_init */
अटल व्योम bdc_hw_निकास(काष्ठा bdc *bdc)
अणु
	dev_dbg(bdc->dev, "%s ()\n", __func__);
	bdc_mem_मुक्त(bdc);
पूर्ण

/* Initialize the bdc HW and memory */
अटल पूर्णांक bdc_hw_init(काष्ठा bdc *bdc)
अणु
	पूर्णांक ret;

	dev_dbg(bdc->dev, "%s ()\n", __func__);
	ret = bdc_reset(bdc);
	अगर (ret) अणु
		dev_err(bdc->dev, "err resetting bdc abort bdc init%d\n", ret);
		वापस ret;
	पूर्ण
	ret = bdc_mem_alloc(bdc);
	अगर (ret) अणु
		dev_err(bdc->dev, "Mem alloc failed, aborting\n");
		वापस -ENOMEM;
	पूर्ण
	bdc_mem_init(bdc, 0);
	bdc_dbg_regs(bdc);
	dev_dbg(bdc->dev, "HW Init done\n");

	वापस 0;
पूर्ण

अटल पूर्णांक bdc_phy_init(काष्ठा bdc *bdc)
अणु
	पूर्णांक phy_num;
	पूर्णांक ret;

	क्रम (phy_num = 0; phy_num < bdc->num_phys; phy_num++) अणु
		ret = phy_init(bdc->phys[phy_num]);
		अगर (ret)
			जाओ err_निकास_phy;
		ret = phy_घातer_on(bdc->phys[phy_num]);
		अगर (ret) अणु
			phy_निकास(bdc->phys[phy_num]);
			जाओ err_निकास_phy;
		पूर्ण
	पूर्ण

	वापस 0;

err_निकास_phy:
	जबतक (--phy_num >= 0) अणु
		phy_घातer_off(bdc->phys[phy_num]);
		phy_निकास(bdc->phys[phy_num]);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम bdc_phy_निकास(काष्ठा bdc *bdc)
अणु
	पूर्णांक phy_num;

	क्रम (phy_num = 0; phy_num < bdc->num_phys; phy_num++) अणु
		phy_घातer_off(bdc->phys[phy_num]);
		phy_निकास(bdc->phys[phy_num]);
	पूर्ण
पूर्ण

अटल पूर्णांक bdc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bdc *bdc;
	पूर्णांक ret;
	पूर्णांक irq;
	u32 temp;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk *clk;
	पूर्णांक phy_num;

	dev_dbg(dev, "%s()\n", __func__);

	clk = devm_clk_get_optional(dev, "sw_usbd");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(dev, "could not enable clock\n");
		वापस ret;
	पूर्ण

	bdc = devm_kzalloc(dev, माप(*bdc), GFP_KERNEL);
	अगर (!bdc)
		वापस -ENOMEM;

	bdc->clk = clk;

	bdc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(bdc->regs))
		वापस PTR_ERR(bdc->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	spin_lock_init(&bdc->lock);
	platक्रमm_set_drvdata(pdev, bdc);
	bdc->irq = irq;
	bdc->dev = dev;
	dev_dbg(dev, "bdc->regs: %p irq=%d\n", bdc->regs, bdc->irq);

	bdc->num_phys = of_count_phandle_with_args(dev->of_node,
						"phys", "#phy-cells");
	अगर (bdc->num_phys > 0) अणु
		bdc->phys = devm_kसुस्मृति(dev, bdc->num_phys,
					माप(काष्ठा phy *), GFP_KERNEL);
		अगर (!bdc->phys)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		bdc->num_phys = 0;
	पूर्ण
	dev_info(dev, "Using %d phy(s)\n", bdc->num_phys);

	क्रम (phy_num = 0; phy_num < bdc->num_phys; phy_num++) अणु
		bdc->phys[phy_num] = devm_of_phy_get_by_index(
			dev, dev->of_node, phy_num);
		अगर (IS_ERR(bdc->phys[phy_num])) अणु
			ret = PTR_ERR(bdc->phys[phy_num]);
			dev_err(bdc->dev,
				"BDC phy specified but not found:%d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = bdc_phy_init(bdc);
	अगर (ret) अणु
		dev_err(bdc->dev, "BDC phy init failure:%d\n", ret);
		वापस ret;
	पूर्ण

	temp = bdc_पढ़ोl(bdc->regs, BDC_BDCCAP1);
	अगर ((temp & BDC_P64) &&
			!dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64))) अणु
		dev_dbg(dev, "Using 64-bit address\n");
	पूर्ण अन्यथा अणु
		ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
		अगर (ret) अणु
			dev_err(dev,
				"No suitable DMA config available, abort\n");
			वापस -ENOTSUPP;
		पूर्ण
		dev_dbg(dev, "Using 32-bit address\n");
	पूर्ण
	ret = bdc_hw_init(bdc);
	अगर (ret) अणु
		dev_err(dev, "BDC init failure:%d\n", ret);
		जाओ phycleanup;
	पूर्ण
	ret = bdc_udc_init(bdc);
	अगर (ret) अणु
		dev_err(dev, "BDC Gadget init failure:%d\n", ret);
		जाओ cleanup;
	पूर्ण
	वापस 0;

cleanup:
	bdc_hw_निकास(bdc);
phycleanup:
	bdc_phy_निकास(bdc);
	वापस ret;
पूर्ण

अटल पूर्णांक bdc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bdc *bdc;

	bdc  = platक्रमm_get_drvdata(pdev);
	dev_dbg(bdc->dev, "%s ()\n", __func__);
	bdc_udc_निकास(bdc);
	bdc_hw_निकास(bdc);
	bdc_phy_निकास(bdc);
	clk_disable_unprepare(bdc->clk);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bdc_suspend(काष्ठा device *dev)
अणु
	काष्ठा bdc *bdc = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* Halt the controller */
	ret = bdc_stop(bdc);
	अगर (!ret)
		clk_disable_unprepare(bdc->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक bdc_resume(काष्ठा device *dev)
अणु
	काष्ठा bdc *bdc = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(bdc->clk);
	अगर (ret) अणु
		dev_err(bdc->dev, "err enabling the clock\n");
		वापस ret;
	पूर्ण
	ret = bdc_reinit(bdc);
	अगर (ret) अणु
		dev_err(bdc->dev, "err in bdc reinit\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(bdc_pm_ops, bdc_suspend,
		bdc_resume);

अटल स्थिर काष्ठा of_device_id bdc_of_match[] = अणु
	अणु .compatible = "brcm,bdc-udc-v2" पूर्ण,
	अणु .compatible = "brcm,bdc" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver bdc_driver = अणु
	.driver		= अणु
		.name	= BRCM_BDC_NAME,
		.pm = &bdc_pm_ops,
		.of_match_table	= bdc_of_match,
	पूर्ण,
	.probe		= bdc_probe,
	.हटाओ		= bdc_हटाओ,
पूर्ण;

module_platक्रमm_driver(bdc_driver);
MODULE_AUTHOR("Ashwini Pahuja <ashwini.linux@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(BRCM_BDC_DESC);
