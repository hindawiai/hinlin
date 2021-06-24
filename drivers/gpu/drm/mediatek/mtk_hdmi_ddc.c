<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Jie Qiu <jie.qiu@mediatek.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/समय.स>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

#घोषणा SIF1_CLOK		(288)
#घोषणा DDC_DDCMCTL0		(0x0)
#घोषणा DDCM_ODRAIN			BIT(31)
#घोषणा DDCM_CLK_DIV_OFFSET		(16)
#घोषणा DDCM_CLK_DIV_MASK		(0xfff << 16)
#घोषणा DDCM_CS_STATUS			BIT(4)
#घोषणा DDCM_SCL_STATE			BIT(3)
#घोषणा DDCM_SDA_STATE			BIT(2)
#घोषणा DDCM_SM0EN			BIT(1)
#घोषणा DDCM_SCL_STRECH			BIT(0)
#घोषणा DDC_DDCMCTL1		(0x4)
#घोषणा DDCM_ACK_OFFSET			(16)
#घोषणा DDCM_ACK_MASK			(0xff << 16)
#घोषणा DDCM_PGLEN_OFFSET		(8)
#घोषणा DDCM_PGLEN_MASK			(0x7 << 8)
#घोषणा DDCM_SIF_MODE_OFFSET		(4)
#घोषणा DDCM_SIF_MODE_MASK		(0x7 << 4)
#घोषणा DDCM_START			(0x1)
#घोषणा DDCM_WRITE_DATA			(0x2)
#घोषणा DDCM_STOP			(0x3)
#घोषणा DDCM_READ_DATA_NO_ACK		(0x4)
#घोषणा DDCM_READ_DATA_ACK		(0x5)
#घोषणा DDCM_TRI			BIT(0)
#घोषणा DDC_DDCMD0		(0x8)
#घोषणा DDCM_DATA3			(0xff << 24)
#घोषणा DDCM_DATA2			(0xff << 16)
#घोषणा DDCM_DATA1			(0xff << 8)
#घोषणा DDCM_DATA0			(0xff << 0)
#घोषणा DDC_DDCMD1		(0xc)
#घोषणा DDCM_DATA7			(0xff << 24)
#घोषणा DDCM_DATA6			(0xff << 16)
#घोषणा DDCM_DATA5			(0xff << 8)
#घोषणा DDCM_DATA4			(0xff << 0)

काष्ठा mtk_hdmi_ddc अणु
	काष्ठा i2c_adapter adap;
	काष्ठा clk *clk;
	व्योम __iomem *regs;
पूर्ण;

अटल अंतरभूत व्योम sअगर_set_bit(काष्ठा mtk_hdmi_ddc *ddc, अचिन्हित पूर्णांक offset,
			       अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl(पढ़ोl(ddc->regs + offset) | val, ddc->regs + offset);
पूर्ण

अटल अंतरभूत व्योम sअगर_clr_bit(काष्ठा mtk_hdmi_ddc *ddc, अचिन्हित पूर्णांक offset,
			       अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl(पढ़ोl(ddc->regs + offset) & ~val, ddc->regs + offset);
पूर्ण

अटल अंतरभूत bool sअगर_bit_is_set(काष्ठा mtk_hdmi_ddc *ddc, अचिन्हित पूर्णांक offset,
				  अचिन्हित पूर्णांक val)
अणु
	वापस (पढ़ोl(ddc->regs + offset) & val) == val;
पूर्ण

अटल अंतरभूत व्योम sअगर_ग_लिखो_mask(काष्ठा mtk_hdmi_ddc *ddc, अचिन्हित पूर्णांक offset,
				  अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक shअगरt,
				  अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = पढ़ोl(ddc->regs + offset);
	पंचांगp &= ~mask;
	पंचांगp |= (val << shअगरt) & mask;
	ग_लिखोl(पंचांगp, ddc->regs + offset);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक sअगर_पढ़ो_mask(काष्ठा mtk_hdmi_ddc *ddc,
					 अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक mask,
					 अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (पढ़ोl(ddc->regs + offset) & mask) >> shअगरt;
पूर्ण

अटल व्योम ddcm_trigger_mode(काष्ठा mtk_hdmi_ddc *ddc, पूर्णांक mode)
अणु
	u32 val;

	sअगर_ग_लिखो_mask(ddc, DDC_DDCMCTL1, DDCM_SIF_MODE_MASK,
		       DDCM_SIF_MODE_OFFSET, mode);
	sअगर_set_bit(ddc, DDC_DDCMCTL1, DDCM_TRI);
	पढ़ोl_poll_समयout(ddc->regs + DDC_DDCMCTL1, val,
			   (val & DDCM_TRI) != DDCM_TRI, 4, 20000);
पूर्ण

अटल पूर्णांक mtk_hdmi_ddc_पढ़ो_msg(काष्ठा mtk_hdmi_ddc *ddc, काष्ठा i2c_msg *msg)
अणु
	काष्ठा device *dev = ddc->adap.dev.parent;
	u32 reमुख्य_count, ack_count, ack_final, पढ़ो_count, temp_count;
	u32 index = 0;
	u32 ack;
	पूर्णांक i;

	ddcm_trigger_mode(ddc, DDCM_START);
	sअगर_ग_लिखो_mask(ddc, DDC_DDCMD0, 0xff, 0, (msg->addr << 1) | 0x01);
	sअगर_ग_लिखो_mask(ddc, DDC_DDCMCTL1, DDCM_PGLEN_MASK, DDCM_PGLEN_OFFSET,
		       0x00);
	ddcm_trigger_mode(ddc, DDCM_WRITE_DATA);
	ack = sअगर_पढ़ो_mask(ddc, DDC_DDCMCTL1, DDCM_ACK_MASK, DDCM_ACK_OFFSET);
	dev_dbg(dev, "ack = 0x%x\n", ack);
	अगर (ack != 0x01) अणु
		dev_err(dev, "i2c ack err!\n");
		वापस -ENXIO;
	पूर्ण

	reमुख्य_count = msg->len;
	ack_count = (msg->len - 1) / 8;
	ack_final = 0;

	जबतक (reमुख्य_count > 0) अणु
		अगर (ack_count > 0) अणु
			पढ़ो_count = 8;
			ack_final = 0;
			ack_count--;
		पूर्ण अन्यथा अणु
			पढ़ो_count = reमुख्य_count;
			ack_final = 1;
		पूर्ण

		sअगर_ग_लिखो_mask(ddc, DDC_DDCMCTL1, DDCM_PGLEN_MASK,
			       DDCM_PGLEN_OFFSET, पढ़ो_count - 1);
		ddcm_trigger_mode(ddc, (ack_final == 1) ?
				  DDCM_READ_DATA_NO_ACK :
				  DDCM_READ_DATA_ACK);

		ack = sअगर_पढ़ो_mask(ddc, DDC_DDCMCTL1, DDCM_ACK_MASK,
				    DDCM_ACK_OFFSET);
		temp_count = 0;
		जबतक (((ack & (1 << temp_count)) != 0) && (temp_count < 8))
			temp_count++;
		अगर (((ack_final == 1) && (temp_count != (पढ़ो_count - 1))) ||
		    ((ack_final == 0) && (temp_count != पढ़ो_count))) अणु
			dev_err(dev, "Address NACK! ACK(0x%x)\n", ack);
			अवरोध;
		पूर्ण

		क्रम (i = पढ़ो_count; i >= 1; i--) अणु
			पूर्णांक shअगरt;
			पूर्णांक offset;

			अगर (i > 4) अणु
				offset = DDC_DDCMD1;
				shअगरt = (i - 5) * 8;
			पूर्ण अन्यथा अणु
				offset = DDC_DDCMD0;
				shअगरt = (i - 1) * 8;
			पूर्ण

			msg->buf[index + i - 1] = sअगर_पढ़ो_mask(ddc, offset,
								0xff << shअगरt,
								shअगरt);
		पूर्ण

		reमुख्य_count -= पढ़ो_count;
		index += पढ़ो_count;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hdmi_ddc_ग_लिखो_msg(काष्ठा mtk_hdmi_ddc *ddc, काष्ठा i2c_msg *msg)
अणु
	काष्ठा device *dev = ddc->adap.dev.parent;
	u32 ack;

	ddcm_trigger_mode(ddc, DDCM_START);
	sअगर_ग_लिखो_mask(ddc, DDC_DDCMD0, DDCM_DATA0, 0, msg->addr << 1);
	sअगर_ग_लिखो_mask(ddc, DDC_DDCMD0, DDCM_DATA1, 8, msg->buf[0]);
	sअगर_ग_लिखो_mask(ddc, DDC_DDCMCTL1, DDCM_PGLEN_MASK, DDCM_PGLEN_OFFSET,
		       0x1);
	ddcm_trigger_mode(ddc, DDCM_WRITE_DATA);

	ack = sअगर_पढ़ो_mask(ddc, DDC_DDCMCTL1, DDCM_ACK_MASK, DDCM_ACK_OFFSET);
	dev_dbg(dev, "ack = %d\n", ack);

	अगर (ack != 0x03) अणु
		dev_err(dev, "i2c ack err!\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hdmi_ddc_xfer(काष्ठा i2c_adapter *adapter,
			     काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा mtk_hdmi_ddc *ddc = adapter->algo_data;
	काष्ठा device *dev = adapter->dev.parent;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!ddc) अणु
		dev_err(dev, "invalid arguments\n");
		वापस -EINVAL;
	पूर्ण

	sअगर_set_bit(ddc, DDC_DDCMCTL0, DDCM_SCL_STRECH);
	sअगर_set_bit(ddc, DDC_DDCMCTL0, DDCM_SM0EN);
	sअगर_clr_bit(ddc, DDC_DDCMCTL0, DDCM_ODRAIN);

	अगर (sअगर_bit_is_set(ddc, DDC_DDCMCTL1, DDCM_TRI)) अणु
		dev_err(dev, "ddc line is busy!\n");
		वापस -EBUSY;
	पूर्ण

	sअगर_ग_लिखो_mask(ddc, DDC_DDCMCTL0, DDCM_CLK_DIV_MASK,
		       DDCM_CLK_DIV_OFFSET, SIF1_CLOK);

	क्रम (i = 0; i < num; i++) अणु
		काष्ठा i2c_msg *msg = &msgs[i];

		dev_dbg(dev, "i2c msg, adr:0x%x, flags:%d, len :0x%x\n",
			msg->addr, msg->flags, msg->len);

		अगर (msg->flags & I2C_M_RD)
			ret = mtk_hdmi_ddc_पढ़ो_msg(ddc, msg);
		अन्यथा
			ret = mtk_hdmi_ddc_ग_लिखो_msg(ddc, msg);
		अगर (ret < 0)
			जाओ xfer_end;
	पूर्ण

	ddcm_trigger_mode(ddc, DDCM_STOP);

	वापस i;

xfer_end:
	ddcm_trigger_mode(ddc, DDCM_STOP);
	dev_err(dev, "ddc failed!\n");
	वापस ret;
पूर्ण

अटल u32 mtk_hdmi_ddc_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm mtk_hdmi_ddc_algorithm = अणु
	.master_xfer = mtk_hdmi_ddc_xfer,
	.functionality = mtk_hdmi_ddc_func,
पूर्ण;

अटल पूर्णांक mtk_hdmi_ddc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_hdmi_ddc *ddc;
	काष्ठा resource *mem;
	पूर्णांक ret;

	ddc = devm_kzalloc(dev, माप(काष्ठा mtk_hdmi_ddc), GFP_KERNEL);
	अगर (!ddc)
		वापस -ENOMEM;

	ddc->clk = devm_clk_get(dev, "ddc-i2c");
	अगर (IS_ERR(ddc->clk)) अणु
		dev_err(dev, "get ddc_clk failed: %p ,\n", ddc->clk);
		वापस PTR_ERR(ddc->clk);
	पूर्ण

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ddc->regs = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(ddc->regs))
		वापस PTR_ERR(ddc->regs);

	ret = clk_prepare_enable(ddc->clk);
	अगर (ret) अणु
		dev_err(dev, "enable ddc clk failed!\n");
		वापस ret;
	पूर्ण

	strlcpy(ddc->adap.name, "mediatek-hdmi-ddc", माप(ddc->adap.name));
	ddc->adap.owner = THIS_MODULE;
	ddc->adap.class = I2C_CLASS_DDC;
	ddc->adap.algo = &mtk_hdmi_ddc_algorithm;
	ddc->adap.retries = 3;
	ddc->adap.dev.of_node = dev->of_node;
	ddc->adap.algo_data = ddc;
	ddc->adap.dev.parent = &pdev->dev;

	ret = i2c_add_adapter(&ddc->adap);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to add bus to i2c core\n");
		जाओ err_clk_disable;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ddc);

	dev_dbg(dev, "ddc->adap: %p\n", &ddc->adap);
	dev_dbg(dev, "ddc->clk: %p\n", ddc->clk);
	dev_dbg(dev, "physical adr: %pa, end: %pa\n", &mem->start,
		&mem->end);

	वापस 0;

err_clk_disable:
	clk_disable_unprepare(ddc->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_hdmi_ddc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_hdmi_ddc *ddc = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&ddc->adap);
	clk_disable_unprepare(ddc->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mtk_hdmi_ddc_match[] = अणु
	अणु .compatible = "mediatek,mt8173-hdmi-ddc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_hdmi_ddc_match);

काष्ठा platक्रमm_driver mtk_hdmi_ddc_driver = अणु
	.probe = mtk_hdmi_ddc_probe,
	.हटाओ = mtk_hdmi_ddc_हटाओ,
	.driver = अणु
		.name = "mediatek-hdmi-ddc",
		.of_match_table = mtk_hdmi_ddc_match,
	पूर्ण,
पूर्ण;

MODULE_AUTHOR("Jie Qiu <jie.qiu@mediatek.com>");
MODULE_DESCRIPTION("MediaTek HDMI DDC Driver");
MODULE_LICENSE("GPL v2");
