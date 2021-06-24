<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPGA Freeze Bridge Controller
 *
 *  Copyright (C) 2016 Altera Corporation. All rights reserved.
 */
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <linux/fpga/fpga-bridge.h>

#घोषणा FREEZE_CSR_STATUS_OFFSET		0
#घोषणा FREEZE_CSR_CTRL_OFFSET			4
#घोषणा FREEZE_CSR_ILLEGAL_REQ_OFFSET		8
#घोषणा FREEZE_CSR_REG_VERSION			12

#घोषणा FREEZE_CSR_SUPPORTED_VERSION		2
#घोषणा FREEZE_CSR_OFFICIAL_VERSION		0xad000003

#घोषणा FREEZE_CSR_STATUS_FREEZE_REQ_DONE	BIT(0)
#घोषणा FREEZE_CSR_STATUS_UNFREEZE_REQ_DONE	BIT(1)

#घोषणा FREEZE_CSR_CTRL_FREEZE_REQ		BIT(0)
#घोषणा FREEZE_CSR_CTRL_RESET_REQ		BIT(1)
#घोषणा FREEZE_CSR_CTRL_UNFREEZE_REQ		BIT(2)

#घोषणा FREEZE_BRIDGE_NAME			"freeze"

काष्ठा altera_मुक्तze_br_data अणु
	काष्ठा device *dev;
	व्योम __iomem *base_addr;
	bool enable;
पूर्ण;

/*
 * Poll status until status bit is set or we have a समयout.
 */
अटल पूर्णांक altera_मुक्तze_br_req_ack(काष्ठा altera_मुक्तze_br_data *priv,
				    u32 समयout, u32 req_ack)
अणु
	काष्ठा device *dev = priv->dev;
	व्योम __iomem *csr_illegal_req_addr = priv->base_addr +
					     FREEZE_CSR_ILLEGAL_REQ_OFFSET;
	u32 status, illegal, ctrl;
	पूर्णांक ret = -ETIMEDOUT;

	करो अणु
		illegal = पढ़ोl(csr_illegal_req_addr);
		अगर (illegal) अणु
			dev_err(dev, "illegal request detected 0x%x", illegal);

			ग_लिखोl(1, csr_illegal_req_addr);

			illegal = पढ़ोl(csr_illegal_req_addr);
			अगर (illegal)
				dev_err(dev, "illegal request not cleared 0x%x",
					illegal);

			ret = -EINVAL;
			अवरोध;
		पूर्ण

		status = पढ़ोl(priv->base_addr + FREEZE_CSR_STATUS_OFFSET);
		dev_dbg(dev, "%s %x %x\n", __func__, status, req_ack);
		status &= req_ack;
		अगर (status) अणु
			ctrl = पढ़ोl(priv->base_addr + FREEZE_CSR_CTRL_OFFSET);
			dev_dbg(dev, "%s request %x acknowledged %x %x\n",
				__func__, req_ack, status, ctrl);
			ret = 0;
			अवरोध;
		पूर्ण

		udelay(1);
	पूर्ण जबतक (समयout--);

	अगर (ret == -ETIMEDOUT)
		dev_err(dev, "%s timeout waiting for 0x%x\n",
			__func__, req_ack);

	वापस ret;
पूर्ण

अटल पूर्णांक altera_मुक्तze_br_करो_मुक्तze(काष्ठा altera_मुक्तze_br_data *priv,
				      u32 समयout)
अणु
	काष्ठा device *dev = priv->dev;
	व्योम __iomem *csr_ctrl_addr = priv->base_addr +
				      FREEZE_CSR_CTRL_OFFSET;
	u32 status;
	पूर्णांक ret;

	status = पढ़ोl(priv->base_addr + FREEZE_CSR_STATUS_OFFSET);

	dev_dbg(dev, "%s %d %d\n", __func__, status, पढ़ोl(csr_ctrl_addr));

	अगर (status & FREEZE_CSR_STATUS_FREEZE_REQ_DONE) अणु
		dev_dbg(dev, "%s bridge already disabled %d\n",
			__func__, status);
		वापस 0;
	पूर्ण अन्यथा अगर (!(status & FREEZE_CSR_STATUS_UNFREEZE_REQ_DONE)) अणु
		dev_err(dev, "%s bridge not enabled %d\n", __func__, status);
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(FREEZE_CSR_CTRL_FREEZE_REQ, csr_ctrl_addr);

	ret = altera_मुक्तze_br_req_ack(priv, समयout,
				       FREEZE_CSR_STATUS_FREEZE_REQ_DONE);

	अगर (ret)
		ग_लिखोl(0, csr_ctrl_addr);
	अन्यथा
		ग_लिखोl(FREEZE_CSR_CTRL_RESET_REQ, csr_ctrl_addr);

	वापस ret;
पूर्ण

अटल पूर्णांक altera_मुक्तze_br_करो_unमुक्तze(काष्ठा altera_मुक्तze_br_data *priv,
					u32 समयout)
अणु
	काष्ठा device *dev = priv->dev;
	व्योम __iomem *csr_ctrl_addr = priv->base_addr +
				      FREEZE_CSR_CTRL_OFFSET;
	u32 status;
	पूर्णांक ret;

	ग_लिखोl(0, csr_ctrl_addr);

	status = पढ़ोl(priv->base_addr + FREEZE_CSR_STATUS_OFFSET);

	dev_dbg(dev, "%s %d %d\n", __func__, status, पढ़ोl(csr_ctrl_addr));

	अगर (status & FREEZE_CSR_STATUS_UNFREEZE_REQ_DONE) अणु
		dev_dbg(dev, "%s bridge already enabled %d\n",
			__func__, status);
		वापस 0;
	पूर्ण अन्यथा अगर (!(status & FREEZE_CSR_STATUS_FREEZE_REQ_DONE)) अणु
		dev_err(dev, "%s bridge not frozen %d\n", __func__, status);
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(FREEZE_CSR_CTRL_UNFREEZE_REQ, csr_ctrl_addr);

	ret = altera_मुक्तze_br_req_ack(priv, समयout,
				       FREEZE_CSR_STATUS_UNFREEZE_REQ_DONE);

	status = पढ़ोl(priv->base_addr + FREEZE_CSR_STATUS_OFFSET);

	dev_dbg(dev, "%s %d %d\n", __func__, status, पढ़ोl(csr_ctrl_addr));

	ग_लिखोl(0, csr_ctrl_addr);

	वापस ret;
पूर्ण

/*
 * enable = 1 : allow traffic through the bridge
 * enable = 0 : disable traffic through the bridge
 */
अटल पूर्णांक altera_मुक्तze_br_enable_set(काष्ठा fpga_bridge *bridge,
				       bool enable)
अणु
	काष्ठा altera_मुक्तze_br_data *priv = bridge->priv;
	काष्ठा fpga_image_info *info = bridge->info;
	u32 समयout = 0;
	पूर्णांक ret;

	अगर (enable) अणु
		अगर (info)
			समयout = info->enable_समयout_us;

		ret = altera_मुक्तze_br_करो_unमुक्तze(bridge->priv, समयout);
	पूर्ण अन्यथा अणु
		अगर (info)
			समयout = info->disable_समयout_us;

		ret = altera_मुक्तze_br_करो_मुक्तze(bridge->priv, समयout);
	पूर्ण

	अगर (!ret)
		priv->enable = enable;

	वापस ret;
पूर्ण

अटल पूर्णांक altera_मुक्तze_br_enable_show(काष्ठा fpga_bridge *bridge)
अणु
	काष्ठा altera_मुक्तze_br_data *priv = bridge->priv;

	वापस priv->enable;
पूर्ण

अटल स्थिर काष्ठा fpga_bridge_ops altera_मुक्तze_br_br_ops = अणु
	.enable_set = altera_मुक्तze_br_enable_set,
	.enable_show = altera_मुक्तze_br_enable_show,
पूर्ण;

अटल स्थिर काष्ठा of_device_id altera_मुक्तze_br_of_match[] = अणु
	अणु .compatible = "altr,freeze-bridge-controller", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altera_मुक्तze_br_of_match);

अटल पूर्णांक altera_मुक्तze_br_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = pdev->dev.of_node;
	व्योम __iomem *base_addr;
	काष्ठा altera_मुक्तze_br_data *priv;
	काष्ठा fpga_bridge *br;
	काष्ठा resource *res;
	u32 status, revision;

	अगर (!np)
		वापस -ENODEV;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base_addr = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base_addr))
		वापस PTR_ERR(base_addr);

	revision = पढ़ोl(base_addr + FREEZE_CSR_REG_VERSION);
	अगर ((revision != FREEZE_CSR_SUPPORTED_VERSION) &&
	    (revision != FREEZE_CSR_OFFICIAL_VERSION)) अणु
		dev_err(dev,
			"%s unexpected revision 0x%x != 0x%x != 0x%x\n",
			__func__, revision, FREEZE_CSR_SUPPORTED_VERSION,
			FREEZE_CSR_OFFICIAL_VERSION);
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;

	status = पढ़ोl(base_addr + FREEZE_CSR_STATUS_OFFSET);
	अगर (status & FREEZE_CSR_STATUS_UNFREEZE_REQ_DONE)
		priv->enable = 1;

	priv->base_addr = base_addr;

	br = devm_fpga_bridge_create(dev, FREEZE_BRIDGE_NAME,
				     &altera_मुक्तze_br_br_ops, priv);
	अगर (!br)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, br);

	वापस fpga_bridge_रेजिस्टर(br);
पूर्ण

अटल पूर्णांक altera_मुक्तze_br_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fpga_bridge *br = platक्रमm_get_drvdata(pdev);

	fpga_bridge_unरेजिस्टर(br);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver altera_मुक्तze_br_driver = अणु
	.probe = altera_मुक्तze_br_probe,
	.हटाओ = altera_मुक्तze_br_हटाओ,
	.driver = अणु
		.name	= "altera_freeze_br",
		.of_match_table = of_match_ptr(altera_मुक्तze_br_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(altera_मुक्तze_br_driver);

MODULE_DESCRIPTION("Altera Freeze Bridge");
MODULE_AUTHOR("Alan Tull <atull@opensource.altera.com>");
MODULE_LICENSE("GPL v2");
