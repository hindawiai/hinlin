<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * The driver क्रम Freescale MPC512x LocalPlus Bus FIFO
 * (called SCLPC in the Reference Manual).
 *
 * Copyright (C) 2013-2015 Alexander Popov <alex.popov@linux.com>.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <यंत्र/mpc5121.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-mapping.h>

#घोषणा DRV_NAME "mpc512x_lpbfifo"

काष्ठा cs_range अणु
	u32 csnum;
	u32 base; /* must be zero */
	u32 addr;
	u32 size;
पूर्ण;

अटल काष्ठा lpbfअगरo_data अणु
	spinlock_t lock; /* क्रम protecting lpbfअगरo_data */
	phys_addr_t regs_phys;
	resource_माप_प्रकार regs_size;
	काष्ठा mpc512x_lpbfअगरo __iomem *regs;
	पूर्णांक irq;
	काष्ठा cs_range *cs_ranges;
	माप_प्रकार cs_n;
	काष्ठा dma_chan *chan;
	काष्ठा mpc512x_lpbfअगरo_request *req;
	dma_addr_t ram_bus_addr;
	bool रुको_lpbfअगरo_irq;
	bool रुको_lpbfअगरo_callback;
पूर्ण lpbfअगरo;

/*
 * A data transfer from RAM to some device on LPB is finished
 * when both mpc512x_lpbfअगरo_irq() and mpc512x_lpbfअगरo_callback()
 * have been called. We execute the callback रेजिस्टरed in
 * mpc512x_lpbfअगरo_request just after that.
 * But क्रम a data transfer from some device on LPB to RAM we करोn't enable
 * LPBFIFO पूर्णांकerrupt because clearing MPC512X_SCLPC_SUCCESS पूर्णांकerrupt flag
 * स्वतःmatically disables LPBFIFO पढ़ोing request to the DMA controller
 * and the data transfer hangs. So the callback रेजिस्टरed in
 * mpc512x_lpbfअगरo_request is executed at the end of mpc512x_lpbfअगरo_callback().
 */

/*
 * mpc512x_lpbfअगरo_irq - IRQ handler क्रम LPB FIFO
 */
अटल irqवापस_t mpc512x_lpbfअगरo_irq(पूर्णांक irq, व्योम *param)
अणु
	काष्ठा device *dev = (काष्ठा device *)param;
	काष्ठा mpc512x_lpbfअगरo_request *req = शून्य;
	अचिन्हित दीर्घ flags;
	u32 status;

	spin_lock_irqsave(&lpbfअगरo.lock, flags);

	अगर (!lpbfअगरo.regs)
		जाओ end;

	req = lpbfअगरo.req;
	अगर (!req || req->dir == MPC512X_LPBFIFO_REQ_सूची_READ) अणु
		dev_err(dev, "bogus LPBFIFO IRQ\n");
		जाओ end;
	पूर्ण

	status = in_be32(&lpbfअगरo.regs->status);
	अगर (status != MPC512X_SCLPC_SUCCESS) अणु
		dev_err(dev, "DMA transfer from RAM to peripheral failed\n");
		out_be32(&lpbfअगरo.regs->enable,
				MPC512X_SCLPC_RESET | MPC512X_SCLPC_FIFO_RESET);
		जाओ end;
	पूर्ण
	/* Clear the पूर्णांकerrupt flag */
	out_be32(&lpbfअगरo.regs->status, MPC512X_SCLPC_SUCCESS);

	lpbfअगरo.रुको_lpbfअगरo_irq = false;

	अगर (lpbfअगरo.रुको_lpbfअगरo_callback)
		जाओ end;

	/* Transfer is finished, set the FIFO as idle */
	lpbfअगरo.req = शून्य;

	spin_unlock_irqrestore(&lpbfअगरo.lock, flags);

	अगर (req->callback)
		req->callback(req);

	वापस IRQ_HANDLED;

 end:
	spin_unlock_irqrestore(&lpbfअगरo.lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * mpc512x_lpbfअगरo_callback is called by DMA driver when
 * DMA transaction is finished.
 */
अटल व्योम mpc512x_lpbfअगरo_callback(व्योम *param)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mpc512x_lpbfअगरo_request *req = शून्य;
	क्रमागत dma_data_direction dir;

	spin_lock_irqsave(&lpbfअगरo.lock, flags);

	अगर (!lpbfअगरo.regs) अणु
		spin_unlock_irqrestore(&lpbfअगरo.lock, flags);
		वापस;
	पूर्ण

	req = lpbfअगरo.req;
	अगर (!req) अणु
		pr_err("bogus LPBFIFO callback\n");
		spin_unlock_irqrestore(&lpbfअगरo.lock, flags);
		वापस;
	पूर्ण

	/* Release the mapping */
	अगर (req->dir == MPC512X_LPBFIFO_REQ_सूची_WRITE)
		dir = DMA_TO_DEVICE;
	अन्यथा
		dir = DMA_FROM_DEVICE;
	dma_unmap_single(lpbfअगरo.chan->device->dev,
			lpbfअगरo.ram_bus_addr, req->size, dir);

	lpbfअगरo.रुको_lpbfअगरo_callback = false;

	अगर (!lpbfअगरo.रुको_lpbfअगरo_irq) अणु
		/* Transfer is finished, set the FIFO as idle */
		lpbfअगरo.req = शून्य;

		spin_unlock_irqrestore(&lpbfअगरo.lock, flags);

		अगर (req->callback)
			req->callback(req);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&lpbfअगरo.lock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक mpc512x_lpbfअगरo_kick(व्योम)
अणु
	u32 bits;
	bool no_incr = false;
	u32 bpt = 32; /* max bytes per LPBFIFO transaction involving DMA */
	u32 cs = 0;
	माप_प्रकार i;
	काष्ठा dma_device *dma_dev = शून्य;
	काष्ठा scatterlist sg;
	क्रमागत dma_data_direction dir;
	काष्ठा dma_slave_config dma_conf = अणुपूर्ण;
	काष्ठा dma_async_tx_descriptor *dma_tx = शून्य;
	dma_cookie_t cookie;
	पूर्णांक ret;

	/*
	 * 1. Fit the requirements:
	 * - the packet size must be a multiple of 4 since FIFO Data Word
	 *    Register allows only full-word access according the Reference
	 *    Manual;
	 * - the physical address of the device on LPB and the packet size
	 *    must be aligned on BPT (bytes per transaction) or 8-bytes
	 *    boundary according the Reference Manual;
	 * - but we choose DMA maxburst equal (or very बंद to) BPT to prevent
	 *    DMA controller from overtaking FIFO and causing FIFO underflow
	 *    error. So we क्रमce the packet size to be aligned on BPT boundary
	 *    not to confuse DMA driver which requires the packet size to be
	 *    aligned on maxburst boundary;
	 * - BPT should be set to the LPB device port size क्रम operation with
	 *    disabled स्वतः-incrementing according Reference Manual.
	 */
	अगर (lpbfअगरo.req->size == 0 || !IS_ALIGNED(lpbfअगरo.req->size, 4))
		वापस -EINVAL;

	अगर (lpbfअगरo.req->portsize != LPB_DEV_PORTSIZE_UNDEFINED) अणु
		bpt = lpbfअगरo.req->portsize;
		no_incr = true;
	पूर्ण

	जबतक (bpt > 1) अणु
		अगर (IS_ALIGNED(lpbfअगरo.req->dev_phys_addr, min(bpt, 0x8u)) &&
					IS_ALIGNED(lpbfअगरo.req->size, bpt)) अणु
			अवरोध;
		पूर्ण

		अगर (no_incr)
			वापस -EINVAL;

		bpt >>= 1;
	पूर्ण
	dma_conf.dst_maxburst = max(bpt, 0x4u) / 4;
	dma_conf.src_maxburst = max(bpt, 0x4u) / 4;

	क्रम (i = 0; i < lpbfअगरo.cs_n; i++) अणु
		phys_addr_t cs_start = lpbfअगरo.cs_ranges[i].addr;
		phys_addr_t cs_end = cs_start + lpbfअगरo.cs_ranges[i].size;
		phys_addr_t access_start = lpbfअगरo.req->dev_phys_addr;
		phys_addr_t access_end = access_start + lpbfअगरo.req->size;

		अगर (access_start >= cs_start && access_end <= cs_end) अणु
			cs = lpbfअगरo.cs_ranges[i].csnum;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == lpbfअगरo.cs_n)
		वापस -EFAULT;

	/* 2. Prepare DMA */
	dma_dev = lpbfअगरo.chan->device;

	अगर (lpbfअगरo.req->dir == MPC512X_LPBFIFO_REQ_सूची_WRITE) अणु
		dir = DMA_TO_DEVICE;
		dma_conf.direction = DMA_MEM_TO_DEV;
		dma_conf.dst_addr = lpbfअगरo.regs_phys +
				दुरत्व(काष्ठा mpc512x_lpbfअगरo, data_word);
	पूर्ण अन्यथा अणु
		dir = DMA_FROM_DEVICE;
		dma_conf.direction = DMA_DEV_TO_MEM;
		dma_conf.src_addr = lpbfअगरo.regs_phys +
				दुरत्व(काष्ठा mpc512x_lpbfअगरo, data_word);
	पूर्ण
	dma_conf.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	dma_conf.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	/* Make DMA channel work with LPB FIFO data रेजिस्टर */
	अगर (dma_dev->device_config(lpbfअगरo.chan, &dma_conf)) अणु
		ret = -EINVAL;
		जाओ err_dma_prep;
	पूर्ण

	sg_init_table(&sg, 1);

	sg_dma_address(&sg) = dma_map_single(dma_dev->dev,
			lpbfअगरo.req->ram_virt_addr, lpbfअगरo.req->size, dir);
	अगर (dma_mapping_error(dma_dev->dev, sg_dma_address(&sg)))
		वापस -EFAULT;

	lpbfअगरo.ram_bus_addr = sg_dma_address(&sg); /* For मुक्तing later */

	sg_dma_len(&sg) = lpbfअगरo.req->size;

	dma_tx = dmaengine_prep_slave_sg(lpbfअगरo.chan, &sg,
						1, dma_conf.direction, 0);
	अगर (!dma_tx) अणु
		ret = -ENOSPC;
		जाओ err_dma_prep;
	पूर्ण
	dma_tx->callback = mpc512x_lpbfअगरo_callback;
	dma_tx->callback_param = शून्य;

	/* 3. Prepare FIFO */
	out_be32(&lpbfअगरo.regs->enable,
				MPC512X_SCLPC_RESET | MPC512X_SCLPC_FIFO_RESET);
	out_be32(&lpbfअगरo.regs->enable, 0x0);

	/*
	 * Configure the watermarks क्रम ग_लिखो operation (RAM->DMA->FIFO->dev):
	 * - high watermark 7 words according the Reference Manual,
	 * - low watermark 512 bytes (half of the FIFO).
	 * These watermarks करोn't work क्रम पढ़ो operation since the
	 * MPC512X_SCLPC_FLUSH bit is set (according the Reference Manual).
	 */
	out_be32(&lpbfअगरo.regs->fअगरo_ctrl, MPC512X_SCLPC_FIFO_CTRL(0x7));
	out_be32(&lpbfअगरo.regs->fअगरo_alarm, MPC512X_SCLPC_FIFO_ALARM(0x200));

	/*
	 * Start address is a physical address of the region which beदीर्घs
	 * to the device on the LocalPlus Bus
	 */
	out_be32(&lpbfअगरo.regs->start_addr, lpbfअगरo.req->dev_phys_addr);

	/*
	 * Configure chip select, transfer direction, address increment option
	 * and bytes per transaction option
	 */
	bits = MPC512X_SCLPC_CS(cs);
	अगर (lpbfअगरo.req->dir == MPC512X_LPBFIFO_REQ_सूची_READ)
		bits |= MPC512X_SCLPC_READ | MPC512X_SCLPC_FLUSH;
	अगर (no_incr)
		bits |= MPC512X_SCLPC_DAI;
	bits |= MPC512X_SCLPC_BPT(bpt);
	out_be32(&lpbfअगरo.regs->ctrl, bits);

	/* Unmask irqs */
	bits = MPC512X_SCLPC_ENABLE | MPC512X_SCLPC_ABORT_INT_ENABLE;
	अगर (lpbfअगरo.req->dir == MPC512X_LPBFIFO_REQ_सूची_WRITE)
		bits |= MPC512X_SCLPC_NORM_INT_ENABLE;
	अन्यथा
		lpbfअगरo.रुको_lpbfअगरo_irq = false;

	out_be32(&lpbfअगरo.regs->enable, bits);

	/* 4. Set packet size and kick FIFO off */
	bits = lpbfअगरo.req->size | MPC512X_SCLPC_START;
	out_be32(&lpbfअगरo.regs->pkt_size, bits);

	/* 5. Finally kick DMA off */
	cookie = dma_tx->tx_submit(dma_tx);
	अगर (dma_submit_error(cookie)) अणु
		ret = -ENOSPC;
		जाओ err_dma_submit;
	पूर्ण

	वापस 0;

 err_dma_submit:
	out_be32(&lpbfअगरo.regs->enable,
				MPC512X_SCLPC_RESET | MPC512X_SCLPC_FIFO_RESET);
 err_dma_prep:
	dma_unmap_single(dma_dev->dev, sg_dma_address(&sg),
						lpbfअगरo.req->size, dir);
	वापस ret;
पूर्ण

अटल पूर्णांक mpc512x_lpbfअगरo_submit_locked(काष्ठा mpc512x_lpbfअगरo_request *req)
अणु
	पूर्णांक ret = 0;

	अगर (!lpbfअगरo.regs)
		वापस -ENODEV;

	/* Check whether a transfer is in progress */
	अगर (lpbfअगरo.req)
		वापस -EBUSY;

	lpbfअगरo.रुको_lpbfअगरo_irq = true;
	lpbfअगरo.रुको_lpbfअगरo_callback = true;
	lpbfअगरo.req = req;

	ret = mpc512x_lpbfअगरo_kick();
	अगर (ret != 0)
		lpbfअगरo.req = शून्य; /* Set the FIFO as idle */

	वापस ret;
पूर्ण

पूर्णांक mpc512x_lpbfअगरo_submit(काष्ठा mpc512x_lpbfअगरo_request *req)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&lpbfअगरo.lock, flags);
	ret = mpc512x_lpbfअगरo_submit_locked(req);
	spin_unlock_irqrestore(&lpbfअगरo.lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mpc512x_lpbfअगरo_submit);

/*
 * LPBFIFO driver uses "ranges" property of "localbus" device tree node
 * क्रम being able to determine the chip select number of a client device
 * ordering a DMA transfer.
 */
अटल पूर्णांक get_cs_ranges(काष्ठा device *dev)
अणु
	पूर्णांक ret = -ENODEV;
	काष्ठा device_node *lb_node;
	स्थिर u32 *addr_cells_p;
	स्थिर u32 *size_cells_p;
	पूर्णांक proplen;
	माप_प्रकार i;

	lb_node = of_find_compatible_node(शून्य, शून्य, "fsl,mpc5121-localbus");
	अगर (!lb_node)
		वापस ret;

	/*
	 * The node defined as compatible with 'fsl,mpc5121-localbus'
	 * should have two address cells and one size cell.
	 * Every item of its ranges property should consist of:
	 * - the first address cell which is the chipselect number;
	 * - the second address cell which is the offset in the chipselect,
	 *    must be zero.
	 * - CPU address of the beginning of an access winकरोw;
	 * - the only size cell which is the size of an access winकरोw.
	 */
	addr_cells_p = of_get_property(lb_node, "#address-cells", शून्य);
	size_cells_p = of_get_property(lb_node, "#size-cells", शून्य);
	अगर (addr_cells_p == शून्य || *addr_cells_p != 2 ||
				size_cells_p == शून्य ||	*size_cells_p != 1) अणु
		जाओ end;
	पूर्ण

	proplen = of_property_count_u32_elems(lb_node, "ranges");
	अगर (proplen <= 0 || proplen % 4 != 0)
		जाओ end;

	lpbfअगरo.cs_n = proplen / 4;
	lpbfअगरo.cs_ranges = devm_kसुस्मृति(dev, lpbfअगरo.cs_n,
					माप(काष्ठा cs_range), GFP_KERNEL);
	अगर (!lpbfअगरo.cs_ranges)
		जाओ end;

	अगर (of_property_पढ़ो_u32_array(lb_node, "ranges",
				(u32 *)lpbfअगरo.cs_ranges, proplen) != 0) अणु
		जाओ end;
	पूर्ण

	क्रम (i = 0; i < lpbfअगरo.cs_n; i++) अणु
		अगर (lpbfअगरo.cs_ranges[i].base != 0)
			जाओ end;
	पूर्ण

	ret = 0;

 end:
	of_node_put(lb_node);
	वापस ret;
पूर्ण

अटल पूर्णांक mpc512x_lpbfअगरo_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource r;
	पूर्णांक ret = 0;

	स_रखो(&lpbfअगरo, 0, माप(काष्ठा lpbfअगरo_data));
	spin_lock_init(&lpbfअगरo.lock);

	lpbfअगरo.chan = dma_request_chan(&pdev->dev, "rx-tx");
	अगर (IS_ERR(lpbfअगरo.chan))
		वापस PTR_ERR(lpbfअगरo.chan);

	अगर (of_address_to_resource(pdev->dev.of_node, 0, &r) != 0) अणु
		dev_err(&pdev->dev, "bad 'reg' in 'sclpc' device tree node\n");
		ret = -ENODEV;
		जाओ err0;
	पूर्ण

	lpbfअगरo.regs_phys = r.start;
	lpbfअगरo.regs_size = resource_size(&r);

	अगर (!devm_request_mem_region(&pdev->dev, lpbfअगरo.regs_phys,
					lpbfअगरo.regs_size, DRV_NAME)) अणु
		dev_err(&pdev->dev, "unable to request region\n");
		ret = -EBUSY;
		जाओ err0;
	पूर्ण

	lpbfअगरo.regs = devm_ioremap(&pdev->dev,
					lpbfअगरo.regs_phys, lpbfअगरo.regs_size);
	अगर (!lpbfअगरo.regs) अणु
		dev_err(&pdev->dev, "mapping registers failed\n");
		ret = -ENOMEM;
		जाओ err0;
	पूर्ण

	out_be32(&lpbfअगरo.regs->enable,
				MPC512X_SCLPC_RESET | MPC512X_SCLPC_FIFO_RESET);

	अगर (get_cs_ranges(&pdev->dev) != 0) अणु
		dev_err(&pdev->dev, "bad '/localbus' device tree node\n");
		ret = -ENODEV;
		जाओ err0;
	पूर्ण

	lpbfअगरo.irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	अगर (!lpbfअगरo.irq) अणु
		dev_err(&pdev->dev, "mapping irq failed\n");
		ret = -ENODEV;
		जाओ err0;
	पूर्ण

	अगर (request_irq(lpbfअगरo.irq, mpc512x_lpbfअगरo_irq, 0,
						DRV_NAME, &pdev->dev) != 0) अणु
		dev_err(&pdev->dev, "requesting irq failed\n");
		ret = -ENODEV;
		जाओ err1;
	पूर्ण

	dev_info(&pdev->dev, "probe succeeded\n");
	वापस 0;

 err1:
	irq_dispose_mapping(lpbfअगरo.irq);
 err0:
	dma_release_channel(lpbfअगरo.chan);
	वापस ret;
पूर्ण

अटल पूर्णांक mpc512x_lpbfअगरo_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dma_device *dma_dev = lpbfअगरo.chan->device;
	काष्ठा mpc512x_lpbfअगरo __iomem *regs = शून्य;

	spin_lock_irqsave(&lpbfअगरo.lock, flags);
	regs = lpbfअगरo.regs;
	lpbfअगरo.regs = शून्य;
	spin_unlock_irqrestore(&lpbfअगरo.lock, flags);

	dma_dev->device_terminate_all(lpbfअगरo.chan);
	out_be32(&regs->enable, MPC512X_SCLPC_RESET | MPC512X_SCLPC_FIFO_RESET);

	मुक्त_irq(lpbfअगरo.irq, &pdev->dev);
	irq_dispose_mapping(lpbfअगरo.irq);
	dma_release_channel(lpbfअगरo.chan);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc512x_lpbfअगरo_match[] = अणु
	अणु .compatible = "fsl,mpc512x-lpbfifo", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mpc512x_lpbfअगरo_match);

अटल काष्ठा platक्रमm_driver mpc512x_lpbfअगरo_driver = अणु
	.probe = mpc512x_lpbfअगरo_probe,
	.हटाओ = mpc512x_lpbfअगरo_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = mpc512x_lpbfअगरo_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mpc512x_lpbfअगरo_driver);

MODULE_AUTHOR("Alexander Popov <alex.popov@linux.com>");
MODULE_DESCRIPTION("MPC512x LocalPlus Bus FIFO device driver");
MODULE_LICENSE("GPL v2");
