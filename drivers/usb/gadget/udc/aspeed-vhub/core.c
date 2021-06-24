<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * aspeed-vhub -- Driver क्रम Aspeed SoC "vHub" USB gadget
 *
 * core.c - Top level support
 *
 * Copyright 2017 IBM Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/clk.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/dma-mapping.h>

#समावेश "vhub.h"

व्योम ast_vhub_करोne(काष्ठा ast_vhub_ep *ep, काष्ठा ast_vhub_req *req,
		   पूर्णांक status)
अणु
	bool पूर्णांकernal = req->पूर्णांकernal;
	काष्ठा ast_vhub *vhub = ep->vhub;

	EPVDBG(ep, "completing request @%p, status %d\n", req, status);

	list_del_init(&req->queue);

	अगर (req->req.status == -EINPROGRESS)
		req->req.status = status;

	अगर (req->req.dma) अणु
		अगर (!WARN_ON(!ep->dev))
			usb_gadget_unmap_request_by_dev(&vhub->pdev->dev,
						 &req->req, ep->epn.is_in);
		req->req.dma = 0;
	पूर्ण

	/*
	 * If this isn't an पूर्णांकernal EP0 request, call the core
	 * to call the gadget completion.
	 */
	अगर (!पूर्णांकernal) अणु
		spin_unlock(&ep->vhub->lock);
		usb_gadget_giveback_request(&ep->ep, &req->req);
		spin_lock(&ep->vhub->lock);
	पूर्ण
पूर्ण

व्योम ast_vhub_nuke(काष्ठा ast_vhub_ep *ep, पूर्णांक status)
अणु
	काष्ठा ast_vhub_req *req;
	पूर्णांक count = 0;

	/* Beware, lock will be dropped & req-acquired by करोne() */
	जबतक (!list_empty(&ep->queue)) अणु
		req = list_first_entry(&ep->queue, काष्ठा ast_vhub_req, queue);
		ast_vhub_करोne(ep, req, status);
		count++;
	पूर्ण
	अगर (count)
		EPDBG(ep, "Nuked %d request(s)\n", count);
पूर्ण

काष्ठा usb_request *ast_vhub_alloc_request(काष्ठा usb_ep *u_ep,
					   gfp_t gfp_flags)
अणु
	काष्ठा ast_vhub_req *req;

	req = kzalloc(माप(*req), gfp_flags);
	अगर (!req)
		वापस शून्य;
	वापस &req->req;
पूर्ण

व्योम ast_vhub_मुक्त_request(काष्ठा usb_ep *u_ep, काष्ठा usb_request *u_req)
अणु
	काष्ठा ast_vhub_req *req = to_ast_req(u_req);

	kमुक्त(req);
पूर्ण

अटल irqवापस_t ast_vhub_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ast_vhub *vhub = data;
	irqवापस_t iret = IRQ_NONE;
	u32 i, istat;

	/* Stale पूर्णांकerrupt जबतक tearing करोwn */
	अगर (!vhub->ep0_bufs)
		वापस IRQ_NONE;

	spin_lock(&vhub->lock);

	/* Read and ACK पूर्णांकerrupts */
	istat = पढ़ोl(vhub->regs + AST_VHUB_ISR);
	अगर (!istat)
		जाओ bail;
	ग_लिखोl(istat, vhub->regs + AST_VHUB_ISR);
	iret = IRQ_HANDLED;

	UDCVDBG(vhub, "irq status=%08x, ep_acks=%08x ep_nacks=%08x\n",
	       istat,
	       पढ़ोl(vhub->regs + AST_VHUB_EP_ACK_ISR),
	       पढ़ोl(vhub->regs + AST_VHUB_EP_NACK_ISR));

	/* Handle generic EPs first */
	अगर (istat & VHUB_IRQ_EP_POOL_ACK_STALL) अणु
		u32 ep_acks = पढ़ोl(vhub->regs + AST_VHUB_EP_ACK_ISR);
		ग_लिखोl(ep_acks, vhub->regs + AST_VHUB_EP_ACK_ISR);

		क्रम (i = 0; ep_acks && i < vhub->max_epns; i++) अणु
			u32 mask = VHUB_EP_IRQ(i);
			अगर (ep_acks & mask) अणु
				ast_vhub_epn_ack_irq(&vhub->epns[i]);
				ep_acks &= ~mask;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Handle device पूर्णांकerrupts */
	अगर (istat & vhub->port_irq_mask) अणु
		क्रम (i = 0; i < vhub->max_ports; i++) अणु
			अगर (istat & VHUB_DEV_IRQ(i))
				ast_vhub_dev_irq(&vhub->ports[i].dev);
		पूर्ण
	पूर्ण

	/* Handle top-level vHub EP0 पूर्णांकerrupts */
	अगर (istat & (VHUB_IRQ_HUB_EP0_OUT_ACK_STALL |
		     VHUB_IRQ_HUB_EP0_IN_ACK_STALL |
		     VHUB_IRQ_HUB_EP0_SETUP)) अणु
		अगर (istat & VHUB_IRQ_HUB_EP0_IN_ACK_STALL)
			ast_vhub_ep0_handle_ack(&vhub->ep0, true);
		अगर (istat & VHUB_IRQ_HUB_EP0_OUT_ACK_STALL)
			ast_vhub_ep0_handle_ack(&vhub->ep0, false);
		अगर (istat & VHUB_IRQ_HUB_EP0_SETUP)
			ast_vhub_ep0_handle_setup(&vhub->ep0);
	पूर्ण

	/* Various top level bus events */
	अगर (istat & (VHUB_IRQ_BUS_RESUME |
		     VHUB_IRQ_BUS_SUSPEND |
		     VHUB_IRQ_BUS_RESET)) अणु
		अगर (istat & VHUB_IRQ_BUS_RESUME)
			ast_vhub_hub_resume(vhub);
		अगर (istat & VHUB_IRQ_BUS_SUSPEND)
			ast_vhub_hub_suspend(vhub);
		अगर (istat & VHUB_IRQ_BUS_RESET)
			ast_vhub_hub_reset(vhub);
	पूर्ण

 bail:
	spin_unlock(&vhub->lock);
	वापस iret;
पूर्ण

व्योम ast_vhub_init_hw(काष्ठा ast_vhub *vhub)
अणु
	u32 ctrl, port_mask, epn_mask;

	UDCDBG(vhub,"(Re)Starting HW ...\n");

	/* Enable PHY */
	ctrl = VHUB_CTRL_PHY_CLK |
		VHUB_CTRL_PHY_RESET_DIS;

       /*
	* We करो *NOT* set the VHUB_CTRL_CLK_STOP_SUSPEND bit
	* to stop the logic घड़ी during suspend because
	* it causes the रेजिस्टरs to become inaccessible and
	* we haven't yet figured out a good wayt to bring the
	* controller back पूर्णांकo lअगरe to issue a wakeup.
	*/

	/*
	 * Set some ISO & split control bits according to Aspeed
	 * recommendation
	 *
	 * VHUB_CTRL_ISO_RSP_CTRL: When set tells the HW to respond
	 * with 0 bytes data packet to ISO IN endpoपूर्णांकs when no data
	 * is available.
	 *
	 * VHUB_CTRL_SPLIT_IN: This makes a SOF complete a split IN
	 * transaction.
	 */
	ctrl |= VHUB_CTRL_ISO_RSP_CTRL | VHUB_CTRL_SPLIT_IN;
	ग_लिखोl(ctrl, vhub->regs + AST_VHUB_CTRL);
	udelay(1);

	/* Set descriptor ring size */
	अगर (AST_VHUB_DESCS_COUNT == 256) अणु
		ctrl |= VHUB_CTRL_LONG_DESC;
		ग_लिखोl(ctrl, vhub->regs + AST_VHUB_CTRL);
	पूर्ण अन्यथा अणु
		BUILD_BUG_ON(AST_VHUB_DESCS_COUNT != 32);
	पूर्ण

	/* Reset all devices */
	port_mask = GENMASK(vhub->max_ports, 1);
	ग_लिखोl(VHUB_SW_RESET_ROOT_HUB |
	       VHUB_SW_RESET_DMA_CONTROLLER |
	       VHUB_SW_RESET_EP_POOL |
	       port_mask, vhub->regs + AST_VHUB_SW_RESET);
	udelay(1);
	ग_लिखोl(0, vhub->regs + AST_VHUB_SW_RESET);

	/* Disable and cleanup EP ACK/NACK पूर्णांकerrupts */
	epn_mask = GENMASK(vhub->max_epns - 1, 0);
	ग_लिखोl(0, vhub->regs + AST_VHUB_EP_ACK_IER);
	ग_लिखोl(0, vhub->regs + AST_VHUB_EP_NACK_IER);
	ग_लिखोl(epn_mask, vhub->regs + AST_VHUB_EP_ACK_ISR);
	ग_लिखोl(epn_mask, vhub->regs + AST_VHUB_EP_NACK_ISR);

	/* Default settings क्रम EP0, enable HW hub EP1 */
	ग_लिखोl(0, vhub->regs + AST_VHUB_EP0_CTRL);
	ग_लिखोl(VHUB_EP1_CTRL_RESET_TOGGLE |
	       VHUB_EP1_CTRL_ENABLE,
	       vhub->regs + AST_VHUB_EP1_CTRL);
	ग_लिखोl(0, vhub->regs + AST_VHUB_EP1_STS_CHG);

	/* Configure EP0 DMA buffer */
	ग_लिखोl(vhub->ep0.buf_dma, vhub->regs + AST_VHUB_EP0_DATA);

	/* Clear address */
	ग_लिखोl(0, vhub->regs + AST_VHUB_CONF);

	/* Pullup hub (activate on host) */
	अगर (vhub->क्रमce_usb1)
		ctrl |= VHUB_CTRL_FULL_SPEED_ONLY;

	ctrl |= VHUB_CTRL_UPSTREAM_CONNECT;
	ग_लिखोl(ctrl, vhub->regs + AST_VHUB_CTRL);

	/* Enable some पूर्णांकerrupts */
	ग_लिखोl(VHUB_IRQ_HUB_EP0_IN_ACK_STALL |
	       VHUB_IRQ_HUB_EP0_OUT_ACK_STALL |
	       VHUB_IRQ_HUB_EP0_SETUP |
	       VHUB_IRQ_EP_POOL_ACK_STALL |
	       VHUB_IRQ_BUS_RESUME |
	       VHUB_IRQ_BUS_SUSPEND |
	       VHUB_IRQ_BUS_RESET,
	       vhub->regs + AST_VHUB_IER);
पूर्ण

अटल पूर्णांक ast_vhub_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ast_vhub *vhub = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (!vhub || !vhub->regs)
		वापस 0;

	/* Remove devices */
	क्रम (i = 0; i < vhub->max_ports; i++)
		ast_vhub_del_dev(&vhub->ports[i].dev);

	spin_lock_irqsave(&vhub->lock, flags);

	/* Mask & ack all पूर्णांकerrupts  */
	ग_लिखोl(0, vhub->regs + AST_VHUB_IER);
	ग_लिखोl(VHUB_IRQ_ACK_ALL, vhub->regs + AST_VHUB_ISR);

	/* Pull device, leave PHY enabled */
	ग_लिखोl(VHUB_CTRL_PHY_CLK |
	       VHUB_CTRL_PHY_RESET_DIS,
	       vhub->regs + AST_VHUB_CTRL);

	अगर (vhub->clk)
		clk_disable_unprepare(vhub->clk);

	spin_unlock_irqrestore(&vhub->lock, flags);

	अगर (vhub->ep0_bufs)
		dma_मुक्त_coherent(&pdev->dev,
				  AST_VHUB_EP0_MAX_PACKET *
				  (vhub->max_ports + 1),
				  vhub->ep0_bufs,
				  vhub->ep0_bufs_dma);
	vhub->ep0_bufs = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक ast_vhub_probe(काष्ठा platक्रमm_device *pdev)
अणु
	क्रमागत usb_device_speed max_speed;
	काष्ठा ast_vhub *vhub;
	काष्ठा resource *res;
	पूर्णांक i, rc = 0;
	स्थिर काष्ठा device_node *np = pdev->dev.of_node;

	vhub = devm_kzalloc(&pdev->dev, माप(*vhub), GFP_KERNEL);
	अगर (!vhub)
		वापस -ENOMEM;

	rc = of_property_पढ़ो_u32(np, "aspeed,vhub-downstream-ports",
				  &vhub->max_ports);
	अगर (rc < 0)
		vhub->max_ports = AST_VHUB_NUM_PORTS;

	vhub->ports = devm_kसुस्मृति(&pdev->dev, vhub->max_ports,
				   माप(*vhub->ports), GFP_KERNEL);
	अगर (!vhub->ports)
		वापस -ENOMEM;

	rc = of_property_पढ़ो_u32(np, "aspeed,vhub-generic-endpoints",
				  &vhub->max_epns);
	अगर (rc < 0)
		vhub->max_epns = AST_VHUB_NUM_GEN_EPs;

	vhub->epns = devm_kसुस्मृति(&pdev->dev, vhub->max_epns,
				  माप(*vhub->epns), GFP_KERNEL);
	अगर (!vhub->epns)
		वापस -ENOMEM;

	spin_lock_init(&vhub->lock);
	vhub->pdev = pdev;
	vhub->port_irq_mask = GENMASK(VHUB_IRQ_DEV1_BIT + vhub->max_ports - 1,
				      VHUB_IRQ_DEV1_BIT);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	vhub->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(vhub->regs)) अणु
		dev_err(&pdev->dev, "Failed to map resources\n");
		वापस PTR_ERR(vhub->regs);
	पूर्ण
	UDCDBG(vhub, "vHub@%pR mapped @%p\n", res, vhub->regs);

	platक्रमm_set_drvdata(pdev, vhub);

	vhub->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(vhub->clk)) अणु
		rc = PTR_ERR(vhub->clk);
		जाओ err;
	पूर्ण
	rc = clk_prepare_enable(vhub->clk);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Error couldn't enable clock (%d)\n", rc);
		जाओ err;
	पूर्ण

	/* Check अगर we need to limit the HW to USB1 */
	max_speed = usb_get_maximum_speed(&pdev->dev);
	अगर (max_speed != USB_SPEED_UNKNOWN && max_speed < USB_SPEED_HIGH)
		vhub->क्रमce_usb1 = true;

	/* Mask & ack all पूर्णांकerrupts beक्रमe installing the handler */
	ग_लिखोl(0, vhub->regs + AST_VHUB_IER);
	ग_लिखोl(VHUB_IRQ_ACK_ALL, vhub->regs + AST_VHUB_ISR);

	/* Find पूर्णांकerrupt and install handler */
	vhub->irq = platक्रमm_get_irq(pdev, 0);
	अगर (vhub->irq < 0) अणु
		rc = vhub->irq;
		जाओ err;
	पूर्ण
	rc = devm_request_irq(&pdev->dev, vhub->irq, ast_vhub_irq, 0,
			      KBUILD_MODNAME, vhub);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Failed to request interrupt\n");
		जाओ err;
	पूर्ण

	/*
	 * Allocate DMA buffers क्रम all EP0s in one chunk,
	 * one per port and one क्रम the vHub itself
	 */
	vhub->ep0_bufs = dma_alloc_coherent(&pdev->dev,
					    AST_VHUB_EP0_MAX_PACKET *
					    (vhub->max_ports + 1),
					    &vhub->ep0_bufs_dma, GFP_KERNEL);
	अगर (!vhub->ep0_bufs) अणु
		dev_err(&pdev->dev, "Failed to allocate EP0 DMA buffers\n");
		rc = -ENOMEM;
		जाओ err;
	पूर्ण
	UDCVDBG(vhub, "EP0 DMA buffers @%p (DMA 0x%08x)\n",
		vhub->ep0_bufs, (u32)vhub->ep0_bufs_dma);

	/* Init vHub EP0 */
	ast_vhub_init_ep0(vhub, &vhub->ep0, शून्य);

	/* Init devices */
	क्रम (i = 0; i < vhub->max_ports && rc == 0; i++)
		rc = ast_vhub_init_dev(vhub, i);
	अगर (rc)
		जाओ err;

	/* Init hub emulation */
	rc = ast_vhub_init_hub(vhub);
	अगर (rc)
		जाओ err;

	/* Initialize HW */
	ast_vhub_init_hw(vhub);

	dev_info(&pdev->dev, "Initialized virtual hub in USB%d mode\n",
		 vhub->क्रमce_usb1 ? 1 : 2);

	वापस 0;
 err:
	ast_vhub_हटाओ(pdev);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा of_device_id ast_vhub_dt_ids[] = अणु
	अणु
		.compatible = "aspeed,ast2400-usb-vhub",
	पूर्ण,
	अणु
		.compatible = "aspeed,ast2500-usb-vhub",
	पूर्ण,
	अणु
		.compatible = "aspeed,ast2600-usb-vhub",
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ast_vhub_dt_ids);

अटल काष्ठा platक्रमm_driver ast_vhub_driver = अणु
	.probe		= ast_vhub_probe,
	.हटाओ		= ast_vhub_हटाओ,
	.driver		= अणु
		.name	= KBUILD_MODNAME,
		.of_match_table	= ast_vhub_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ast_vhub_driver);

MODULE_DESCRIPTION("Aspeed vHub udc driver");
MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_LICENSE("GPL");
