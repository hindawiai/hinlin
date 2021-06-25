<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OMAP3XXX L3 Interconnect Driver
 *
 * Copyright (C) 2011 Texas Corporation
 *	Felipe Balbi <balbi@ti.com>
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 *	Sriअक्षरan <r.sriअक्षरan@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश "omap_l3_smx.h"

अटल अंतरभूत u64 omap3_l3_पढ़ोll(व्योम __iomem *base, u16 reg)
अणु
	वापस __raw_पढ़ोll(base + reg);
पूर्ण

अटल अंतरभूत व्योम omap3_l3_ग_लिखोll(व्योम __iomem *base, u16 reg, u64 value)
अणु
	__raw_ग_लिखोll(value, base + reg);
पूर्ण

अटल अंतरभूत क्रमागत omap3_l3_code omap3_l3_decode_error_code(u64 error)
अणु
	वापस (error & 0x0f000000) >> L3_ERROR_LOG_CODE;
पूर्ण

अटल अंतरभूत u32 omap3_l3_decode_addr(u64 error_addr)
अणु
	वापस error_addr & 0xffffffff;
पूर्ण

अटल अंतरभूत अचिन्हित omap3_l3_decode_cmd(u64 error)
अणु
	वापस (error & 0x07) >> L3_ERROR_LOG_CMD;
पूर्ण

अटल अंतरभूत क्रमागत omap3_l3_initiator_id omap3_l3_decode_initid(u64 error)
अणु
	वापस (error & 0xff00) >> L3_ERROR_LOG_INITID;
पूर्ण

अटल अंतरभूत अचिन्हित omap3_l3_decode_req_info(u64 error)
अणु
	वापस (error >> 32) & 0xffff;
पूर्ण

अटल अक्षर *omap3_l3_code_string(u8 code)
अणु
	चयन (code) अणु
	हाल OMAP_L3_CODE_NOERROR:
		वापस "No Error";
	हाल OMAP_L3_CODE_UNSUP_CMD:
		वापस "Unsupported Command";
	हाल OMAP_L3_CODE_ADDR_HOLE:
		वापस "Address Hole";
	हाल OMAP_L3_CODE_PROTECT_VIOLATION:
		वापस "Protection Violation";
	हाल OMAP_L3_CODE_IN_BAND_ERR:
		वापस "In-band Error";
	हाल OMAP_L3_CODE_REQ_TOUT_NOT_ACCEPT:
		वापस "Request Timeout Not Accepted";
	हाल OMAP_L3_CODE_REQ_TOUT_NO_RESP:
		वापस "Request Timeout, no response";
	शेष:
		वापस "UNKNOWN error";
	पूर्ण
पूर्ण

अटल अक्षर *omap3_l3_initiator_string(u8 initid)
अणु
	चयन (initid) अणु
	हाल OMAP_L3_LCD:
		वापस "LCD";
	हाल OMAP_L3_SAD2D:
		वापस "SAD2D";
	हाल OMAP_L3_IA_MPU_SS_1:
	हाल OMAP_L3_IA_MPU_SS_2:
	हाल OMAP_L3_IA_MPU_SS_3:
	हाल OMAP_L3_IA_MPU_SS_4:
	हाल OMAP_L3_IA_MPU_SS_5:
		वापस "MPU";
	हाल OMAP_L3_IA_IVA_SS_1:
	हाल OMAP_L3_IA_IVA_SS_2:
	हाल OMAP_L3_IA_IVA_SS_3:
		वापस "IVA_SS";
	हाल OMAP_L3_IA_IVA_SS_DMA_1:
	हाल OMAP_L3_IA_IVA_SS_DMA_2:
	हाल OMAP_L3_IA_IVA_SS_DMA_3:
	हाल OMAP_L3_IA_IVA_SS_DMA_4:
	हाल OMAP_L3_IA_IVA_SS_DMA_5:
	हाल OMAP_L3_IA_IVA_SS_DMA_6:
		वापस "IVA_SS_DMA";
	हाल OMAP_L3_IA_SGX:
		वापस "SGX";
	हाल OMAP_L3_IA_CAM_1:
	हाल OMAP_L3_IA_CAM_2:
	हाल OMAP_L3_IA_CAM_3:
		वापस "CAM";
	हाल OMAP_L3_IA_DAP:
		वापस "DAP";
	हाल OMAP_L3_SDMA_WR_1:
	हाल OMAP_L3_SDMA_WR_2:
		वापस "SDMA_WR";
	हाल OMAP_L3_SDMA_RD_1:
	हाल OMAP_L3_SDMA_RD_2:
	हाल OMAP_L3_SDMA_RD_3:
	हाल OMAP_L3_SDMA_RD_4:
		वापस "SDMA_RD";
	हाल OMAP_L3_USBOTG:
		वापस "USB_OTG";
	हाल OMAP_L3_USBHOST:
		वापस "USB_HOST";
	शेष:
		वापस "UNKNOWN Initiator";
	पूर्ण
पूर्ण

/*
 * omap3_l3_block_irq - handles a रेजिस्टर block's irq
 * @l3: काष्ठा omap3_l3 *
 * @base: रेजिस्टर block base address
 * @error: L3_ERROR_LOG रेजिस्टर of our block
 *
 * Called in hard-irq context. Caller should take care of locking
 *
 * OMAP36xx TRM gives, on page 2001, Figure 9-10, the Typical Error
 * Analysis Sequence, we are following that sequence here, please
 * refer to that Figure क्रम more inक्रमmation on the subject.
 */
अटल irqवापस_t omap3_l3_block_irq(काष्ठा omap3_l3 *l3,
					u64 error, पूर्णांक error_addr)
अणु
	u8 code = omap3_l3_decode_error_code(error);
	u8 initid = omap3_l3_decode_initid(error);
	u8 multi = error & L3_ERROR_LOG_MULTI;
	u32 address = omap3_l3_decode_addr(error_addr);

	pr_err("%s seen by %s %s at address %x\n",
			omap3_l3_code_string(code),
			omap3_l3_initiator_string(initid),
			multi ? "Multiple Errors" : "", address);
	WARN_ON(1);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t omap3_l3_app_irq(पूर्णांक irq, व्योम *_l3)
अणु
	काष्ठा omap3_l3 *l3 = _l3;
	u64 status, clear;
	u64 error;
	u64 error_addr;
	u64 err_source = 0;
	व्योम __iomem *base;
	पूर्णांक पूर्णांक_type;
	irqवापस_t ret = IRQ_NONE;

	पूर्णांक_type = irq == l3->app_irq ? L3_APPLICATION_ERROR : L3_DEBUG_ERROR;
	अगर (!पूर्णांक_type) अणु
		status = omap3_l3_पढ़ोll(l3->rt, L3_SI_FLAG_STATUS_0);
		/*
		 * अगर we have a समयout error, there's nothing we can
		 * करो besides rebooting the board. So let's BUG on any
		 * of such errors and handle the others. समयout error
		 * is severe and not expected to occur.
		 */
		BUG_ON(status & L3_STATUS_0_TIMEOUT_MASK);
	पूर्ण अन्यथा अणु
		status = omap3_l3_पढ़ोll(l3->rt, L3_SI_FLAG_STATUS_1);
		/* No समयout error क्रम debug sources */
	पूर्ण

	/* identअगरy the error source */
	err_source = __ffs(status);

	base = l3->rt + omap3_l3_bases[पूर्णांक_type][err_source];
	error = omap3_l3_पढ़ोll(base, L3_ERROR_LOG);
	अगर (error) अणु
		error_addr = omap3_l3_पढ़ोll(base, L3_ERROR_LOG_ADDR);
		ret |= omap3_l3_block_irq(l3, error, error_addr);
	पूर्ण

	/* Clear the status रेजिस्टर */
	clear = (L3_AGENT_STATUS_CLEAR_IA << पूर्णांक_type) |
		L3_AGENT_STATUS_CLEAR_TA;
	omap3_l3_ग_लिखोll(base, L3_AGENT_STATUS, clear);

	/* clear the error log रेजिस्टर */
	omap3_l3_ग_लिखोll(base, L3_ERROR_LOG, error);

	वापस ret;
पूर्ण

#अगर IS_BUILTIN(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id omap3_l3_match[] = अणु
	अणु
		.compatible = "ti,omap3-l3-smx",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap3_l3_match);
#पूर्ण_अगर

अटल पूर्णांक omap3_l3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap3_l3 *l3;
	काष्ठा resource *res;
	पूर्णांक ret;

	l3 = kzalloc(माप(*l3), GFP_KERNEL);
	अगर (!l3)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, l3);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "couldn't find resource\n");
		ret = -ENODEV;
		जाओ err0;
	पूर्ण
	l3->rt = ioremap(res->start, resource_size(res));
	अगर (!l3->rt) अणु
		dev_err(&pdev->dev, "ioremap failed\n");
		ret = -ENOMEM;
		जाओ err0;
	पूर्ण

	l3->debug_irq = platक्रमm_get_irq(pdev, 0);
	ret = request_irq(l3->debug_irq, omap3_l3_app_irq, IRQF_TRIGGER_RISING,
			  "l3-debug-irq", l3);
	अगर (ret) अणु
		dev_err(&pdev->dev, "couldn't request debug irq\n");
		जाओ err1;
	पूर्ण

	l3->app_irq = platक्रमm_get_irq(pdev, 1);
	ret = request_irq(l3->app_irq, omap3_l3_app_irq, IRQF_TRIGGER_RISING,
			  "l3-app-irq", l3);
	अगर (ret) अणु
		dev_err(&pdev->dev, "couldn't request app irq\n");
		जाओ err2;
	पूर्ण

	वापस 0;

err2:
	मुक्त_irq(l3->debug_irq, l3);
err1:
	iounmap(l3->rt);
err0:
	kमुक्त(l3);
	वापस ret;
पूर्ण

अटल पूर्णांक omap3_l3_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap3_l3         *l3 = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(l3->app_irq, l3);
	मुक्त_irq(l3->debug_irq, l3);
	iounmap(l3->rt);
	kमुक्त(l3);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver omap3_l3_driver = अणु
	.probe		= omap3_l3_probe,
	.हटाओ         = omap3_l3_हटाओ,
	.driver         = अणु
		.name   = "omap_l3_smx",
		.of_match_table = of_match_ptr(omap3_l3_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init omap3_l3_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&omap3_l3_driver);
पूर्ण
postcore_initcall_sync(omap3_l3_init);

अटल व्योम __निकास omap3_l3_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap3_l3_driver);
पूर्ण
module_निकास(omap3_l3_निकास);

MODULE_AUTHOR("Felipe Balbi");
MODULE_AUTHOR("Santosh Shilimkar");
MODULE_AUTHOR("Sricharan R");
MODULE_DESCRIPTION("OMAP3XXX L3 Interconnect Driver");
MODULE_LICENSE("GPL");
