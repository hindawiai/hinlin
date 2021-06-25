<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 Xilinx, Inc.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/माला.स>
#समावेश <linux/firmware/xlnx-zynqmp.h>

/* Constant Definitions */
#घोषणा IXR_FPGA_DONE_MASK	BIT(3)

/**
 * काष्ठा zynqmp_fpga_priv - Private data काष्ठाure
 * @dev:	Device data काष्ठाure
 * @flags:	flags which is used to identअगरy the bitfile type
 */
काष्ठा zynqmp_fpga_priv अणु
	काष्ठा device *dev;
	u32 flags;
पूर्ण;

अटल पूर्णांक zynqmp_fpga_ops_ग_लिखो_init(काष्ठा fpga_manager *mgr,
				      काष्ठा fpga_image_info *info,
				      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा zynqmp_fpga_priv *priv;

	priv = mgr->priv;
	priv->flags = info->flags;

	वापस 0;
पूर्ण

अटल पूर्णांक zynqmp_fpga_ops_ग_लिखो(काष्ठा fpga_manager *mgr,
				 स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा zynqmp_fpga_priv *priv;
	dma_addr_t dma_addr;
	u32 eemi_flags = 0;
	अक्षर *kbuf;
	पूर्णांक ret;

	priv = mgr->priv;

	kbuf = dma_alloc_coherent(priv->dev, size, &dma_addr, GFP_KERNEL);
	अगर (!kbuf)
		वापस -ENOMEM;

	स_नकल(kbuf, buf, size);

	wmb(); /* ensure all ग_लिखोs are करोne beक्रमe initiate FW call */

	अगर (priv->flags & FPGA_MGR_PARTIAL_RECONFIG)
		eemi_flags |= XILINX_ZYNQMP_PM_FPGA_PARTIAL;

	ret = zynqmp_pm_fpga_load(dma_addr, size, eemi_flags);

	dma_मुक्त_coherent(priv->dev, size, kbuf, dma_addr);

	वापस ret;
पूर्ण

अटल पूर्णांक zynqmp_fpga_ops_ग_लिखो_complete(काष्ठा fpga_manager *mgr,
					  काष्ठा fpga_image_info *info)
अणु
	वापस 0;
पूर्ण

अटल क्रमागत fpga_mgr_states zynqmp_fpga_ops_state(काष्ठा fpga_manager *mgr)
अणु
	u32 status = 0;

	zynqmp_pm_fpga_get_status(&status);
	अगर (status & IXR_FPGA_DONE_MASK)
		वापस FPGA_MGR_STATE_OPERATING;

	वापस FPGA_MGR_STATE_UNKNOWN;
पूर्ण

अटल स्थिर काष्ठा fpga_manager_ops zynqmp_fpga_ops = अणु
	.state = zynqmp_fpga_ops_state,
	.ग_लिखो_init = zynqmp_fpga_ops_ग_लिखो_init,
	.ग_लिखो = zynqmp_fpga_ops_ग_लिखो,
	.ग_लिखो_complete = zynqmp_fpga_ops_ग_लिखो_complete,
पूर्ण;

अटल पूर्णांक zynqmp_fpga_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा zynqmp_fpga_priv *priv;
	काष्ठा fpga_manager *mgr;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;

	mgr = devm_fpga_mgr_create(dev, "Xilinx ZynqMP FPGA Manager",
				   &zynqmp_fpga_ops, priv);
	अगर (!mgr)
		वापस -ENOMEM;

	वापस devm_fpga_mgr_रेजिस्टर(dev, mgr);
पूर्ण

अटल स्थिर काष्ठा of_device_id zynqmp_fpga_of_match[] = अणु
	अणु .compatible = "xlnx,zynqmp-pcap-fpga", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, zynqmp_fpga_of_match);

अटल काष्ठा platक्रमm_driver zynqmp_fpga_driver = अणु
	.probe = zynqmp_fpga_probe,
	.driver = अणु
		.name = "zynqmp_fpga_manager",
		.of_match_table = of_match_ptr(zynqmp_fpga_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(zynqmp_fpga_driver);

MODULE_AUTHOR("Nava kishore Manne <navam@xilinx.com>");
MODULE_DESCRIPTION("Xilinx ZynqMp FPGA Manager");
MODULE_LICENSE("GPL");
