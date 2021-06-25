<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Jie Qiu <jie.qiu@mediatek.com>
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "mtk_cec.h"

#घोषणा TR_CONFIG		0x00
#घोषणा CLEAR_CEC_IRQ			BIT(15)

#घोषणा CEC_CKGEN		0x04
#घोषणा CEC_32K_PDN			BIT(19)
#घोषणा PDN				BIT(16)

#घोषणा RX_EVENT		0x54
#घोषणा HDMI_PORD			BIT(25)
#घोषणा HDMI_HTPLG			BIT(24)
#घोषणा HDMI_PORD_INT_EN		BIT(9)
#घोषणा HDMI_HTPLG_INT_EN		BIT(8)

#घोषणा RX_GEN_WD		0x58
#घोषणा HDMI_PORD_INT_32K_STATUS	BIT(26)
#घोषणा RX_RISC_INT_32K_STATUS		BIT(25)
#घोषणा HDMI_HTPLG_INT_32K_STATUS	BIT(24)
#घोषणा HDMI_PORD_INT_32K_CLR		BIT(18)
#घोषणा RX_INT_32K_CLR			BIT(17)
#घोषणा HDMI_HTPLG_INT_32K_CLR		BIT(16)
#घोषणा HDMI_PORD_INT_32K_STA_MASK	BIT(10)
#घोषणा RX_RISC_INT_32K_STA_MASK	BIT(9)
#घोषणा HDMI_HTPLG_INT_32K_STA_MASK	BIT(8)
#घोषणा HDMI_PORD_INT_32K_EN		BIT(2)
#घोषणा RX_INT_32K_EN			BIT(1)
#घोषणा HDMI_HTPLG_INT_32K_EN		BIT(0)

#घोषणा NORMAL_INT_CTRL		0x5C
#घोषणा HDMI_HTPLG_INT_STA		BIT(0)
#घोषणा HDMI_PORD_INT_STA		BIT(1)
#घोषणा HDMI_HTPLG_INT_CLR		BIT(16)
#घोषणा HDMI_PORD_INT_CLR		BIT(17)
#घोषणा HDMI_FULL_INT_CLR		BIT(20)

काष्ठा mtk_cec अणु
	व्योम __iomem *regs;
	काष्ठा clk *clk;
	पूर्णांक irq;
	bool hpd;
	व्योम (*hpd_event)(bool hpd, काष्ठा device *dev);
	काष्ठा device *hdmi_dev;
	spinlock_t lock;
पूर्ण;

अटल व्योम mtk_cec_clear_bits(काष्ठा mtk_cec *cec, अचिन्हित पूर्णांक offset,
			       अचिन्हित पूर्णांक bits)
अणु
	व्योम __iomem *reg = cec->regs + offset;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(reg);
	पंचांगp &= ~bits;
	ग_लिखोl(पंचांगp, reg);
पूर्ण

अटल व्योम mtk_cec_set_bits(काष्ठा mtk_cec *cec, अचिन्हित पूर्णांक offset,
			     अचिन्हित पूर्णांक bits)
अणु
	व्योम __iomem *reg = cec->regs + offset;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(reg);
	पंचांगp |= bits;
	ग_लिखोl(पंचांगp, reg);
पूर्ण

अटल व्योम mtk_cec_mask(काष्ठा mtk_cec *cec, अचिन्हित पूर्णांक offset,
			 अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक mask)
अणु
	u32 पंचांगp = पढ़ोl(cec->regs + offset) & ~mask;

	पंचांगp |= val & mask;
	ग_लिखोl(val, cec->regs + offset);
पूर्ण

व्योम mtk_cec_set_hpd_event(काष्ठा device *dev,
			   व्योम (*hpd_event)(bool hpd, काष्ठा device *dev),
			   काष्ठा device *hdmi_dev)
अणु
	काष्ठा mtk_cec *cec = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cec->lock, flags);
	cec->hdmi_dev = hdmi_dev;
	cec->hpd_event = hpd_event;
	spin_unlock_irqrestore(&cec->lock, flags);
पूर्ण

bool mtk_cec_hpd_high(काष्ठा device *dev)
अणु
	काष्ठा mtk_cec *cec = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक status;

	status = पढ़ोl(cec->regs + RX_EVENT);

	वापस (status & (HDMI_PORD | HDMI_HTPLG)) == (HDMI_PORD | HDMI_HTPLG);
पूर्ण

अटल व्योम mtk_cec_htplg_irq_init(काष्ठा mtk_cec *cec)
अणु
	mtk_cec_mask(cec, CEC_CKGEN, 0 | CEC_32K_PDN, PDN | CEC_32K_PDN);
	mtk_cec_set_bits(cec, RX_GEN_WD, HDMI_PORD_INT_32K_CLR |
			 RX_INT_32K_CLR | HDMI_HTPLG_INT_32K_CLR);
	mtk_cec_mask(cec, RX_GEN_WD, 0, HDMI_PORD_INT_32K_CLR | RX_INT_32K_CLR |
		     HDMI_HTPLG_INT_32K_CLR | HDMI_PORD_INT_32K_EN |
		     RX_INT_32K_EN | HDMI_HTPLG_INT_32K_EN);
पूर्ण

अटल व्योम mtk_cec_htplg_irq_enable(काष्ठा mtk_cec *cec)
अणु
	mtk_cec_set_bits(cec, RX_EVENT, HDMI_PORD_INT_EN | HDMI_HTPLG_INT_EN);
पूर्ण

अटल व्योम mtk_cec_htplg_irq_disable(काष्ठा mtk_cec *cec)
अणु
	mtk_cec_clear_bits(cec, RX_EVENT, HDMI_PORD_INT_EN | HDMI_HTPLG_INT_EN);
पूर्ण

अटल व्योम mtk_cec_clear_htplg_irq(काष्ठा mtk_cec *cec)
अणु
	mtk_cec_set_bits(cec, TR_CONFIG, CLEAR_CEC_IRQ);
	mtk_cec_set_bits(cec, NORMAL_INT_CTRL, HDMI_HTPLG_INT_CLR |
			 HDMI_PORD_INT_CLR | HDMI_FULL_INT_CLR);
	mtk_cec_set_bits(cec, RX_GEN_WD, HDMI_PORD_INT_32K_CLR |
			 RX_INT_32K_CLR | HDMI_HTPLG_INT_32K_CLR);
	usleep_range(5, 10);
	mtk_cec_clear_bits(cec, NORMAL_INT_CTRL, HDMI_HTPLG_INT_CLR |
			   HDMI_PORD_INT_CLR | HDMI_FULL_INT_CLR);
	mtk_cec_clear_bits(cec, TR_CONFIG, CLEAR_CEC_IRQ);
	mtk_cec_clear_bits(cec, RX_GEN_WD, HDMI_PORD_INT_32K_CLR |
			   RX_INT_32K_CLR | HDMI_HTPLG_INT_32K_CLR);
पूर्ण

अटल व्योम mtk_cec_hpd_event(काष्ठा mtk_cec *cec, bool hpd)
अणु
	व्योम (*hpd_event)(bool hpd, काष्ठा device *dev);
	काष्ठा device *hdmi_dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cec->lock, flags);
	hpd_event = cec->hpd_event;
	hdmi_dev = cec->hdmi_dev;
	spin_unlock_irqrestore(&cec->lock, flags);

	अगर (hpd_event)
		hpd_event(hpd, hdmi_dev);
पूर्ण

अटल irqवापस_t mtk_cec_htplg_isr_thपढ़ो(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा device *dev = arg;
	काष्ठा mtk_cec *cec = dev_get_drvdata(dev);
	bool hpd;

	mtk_cec_clear_htplg_irq(cec);
	hpd = mtk_cec_hpd_high(dev);

	अगर (cec->hpd != hpd) अणु
		dev_dbg(dev, "hotplug event! cur hpd = %d, hpd = %d\n",
			cec->hpd, hpd);
		cec->hpd = hpd;
		mtk_cec_hpd_event(cec, hpd);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mtk_cec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_cec *cec;
	काष्ठा resource *res;
	पूर्णांक ret;

	cec = devm_kzalloc(dev, माप(*cec), GFP_KERNEL);
	अगर (!cec)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, cec);
	spin_lock_init(&cec->lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	cec->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(cec->regs)) अणु
		ret = PTR_ERR(cec->regs);
		dev_err(dev, "Failed to ioremap cec: %d\n", ret);
		वापस ret;
	पूर्ण

	cec->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(cec->clk)) अणु
		ret = PTR_ERR(cec->clk);
		dev_err(dev, "Failed to get cec clock: %d\n", ret);
		वापस ret;
	पूर्ण

	cec->irq = platक्रमm_get_irq(pdev, 0);
	अगर (cec->irq < 0)
		वापस cec->irq;

	ret = devm_request_thपढ़ोed_irq(dev, cec->irq, शून्य,
					mtk_cec_htplg_isr_thपढ़ो,
					IRQF_SHARED | IRQF_TRIGGER_LOW |
					IRQF_ONESHOT, "hdmi hpd", dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register cec irq: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(cec->clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable cec clock: %d\n", ret);
		वापस ret;
	पूर्ण

	mtk_cec_htplg_irq_init(cec);
	mtk_cec_htplg_irq_enable(cec);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_cec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_cec *cec = platक्रमm_get_drvdata(pdev);

	mtk_cec_htplg_irq_disable(cec);
	clk_disable_unprepare(cec->clk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mtk_cec_of_ids[] = अणु
	अणु .compatible = "mediatek,mt8173-cec", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_cec_of_ids);

काष्ठा platक्रमm_driver mtk_cec_driver = अणु
	.probe = mtk_cec_probe,
	.हटाओ = mtk_cec_हटाओ,
	.driver = अणु
		.name = "mediatek-cec",
		.of_match_table = mtk_cec_of_ids,
	पूर्ण,
पूर्ण;
