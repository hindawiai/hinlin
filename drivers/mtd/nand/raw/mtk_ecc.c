<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * MTK ECC controller driver.
 * Copyright (C) 2016  MediaTek Inc.
 * Authors:	Xiaolei Li		<xiaolei.li@mediatek.com>
 *		Jorge Ramirez-Ortiz	<jorge.ramirez-ortiz@linaro.org>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/mutex.h>

#समावेश "mtk_ecc.h"

#घोषणा ECC_IDLE_MASK		BIT(0)
#घोषणा ECC_IRQ_EN		BIT(0)
#घोषणा ECC_PG_IRQ_SEL		BIT(1)
#घोषणा ECC_OP_ENABLE		(1)
#घोषणा ECC_OP_DISABLE		(0)

#घोषणा ECC_ENCCON		(0x00)
#घोषणा ECC_ENCCNFG		(0x04)
#घोषणा		ECC_MS_SHIFT		(16)
#घोषणा ECC_ENCDIADDR		(0x08)
#घोषणा ECC_ENCIDLE		(0x0C)
#घोषणा ECC_DECCON		(0x100)
#घोषणा ECC_DECCNFG		(0x104)
#घोषणा		DEC_EMPTY_EN		BIT(31)
#घोषणा		DEC_CNFG_CORRECT	(0x3 << 12)
#घोषणा ECC_DECIDLE		(0x10C)
#घोषणा ECC_DECENUM0		(0x114)

#घोषणा ECC_TIMEOUT		(500000)

#घोषणा ECC_IDLE_REG(op)	((op) == ECC_ENCODE ? ECC_ENCIDLE : ECC_DECIDLE)
#घोषणा ECC_CTL_REG(op)		((op) == ECC_ENCODE ? ECC_ENCCON : ECC_DECCON)

काष्ठा mtk_ecc_caps अणु
	u32 err_mask;
	स्थिर u8 *ecc_strength;
	स्थिर u32 *ecc_regs;
	u8 num_ecc_strength;
	u8 ecc_mode_shअगरt;
	u32 parity_bits;
	पूर्णांक pg_irq_sel;
पूर्ण;

काष्ठा mtk_ecc अणु
	काष्ठा device *dev;
	स्थिर काष्ठा mtk_ecc_caps *caps;
	व्योम __iomem *regs;
	काष्ठा clk *clk;

	काष्ठा completion करोne;
	काष्ठा mutex lock;
	u32 sectors;

	u8 *eccdata;
पूर्ण;

/* ecc strength that each IP supports */
अटल स्थिर u8 ecc_strength_mt2701[] = अणु
	4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 28, 32, 36,
	40, 44, 48, 52, 56, 60
पूर्ण;

अटल स्थिर u8 ecc_strength_mt2712[] = अणु
	4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 28, 32, 36,
	40, 44, 48, 52, 56, 60, 68, 72, 80
पूर्ण;

अटल स्थिर u8 ecc_strength_mt7622[] = अणु
	4, 6, 8, 10, 12, 14, 16
पूर्ण;

क्रमागत mtk_ecc_regs अणु
	ECC_ENCPAR00,
	ECC_ENCIRQ_EN,
	ECC_ENCIRQ_STA,
	ECC_DECDONE,
	ECC_DECIRQ_EN,
	ECC_DECIRQ_STA,
पूर्ण;

अटल पूर्णांक mt2701_ecc_regs[] = अणु
	[ECC_ENCPAR00] =        0x10,
	[ECC_ENCIRQ_EN] =       0x80,
	[ECC_ENCIRQ_STA] =      0x84,
	[ECC_DECDONE] =         0x124,
	[ECC_DECIRQ_EN] =       0x200,
	[ECC_DECIRQ_STA] =      0x204,
पूर्ण;

अटल पूर्णांक mt2712_ecc_regs[] = अणु
	[ECC_ENCPAR00] =        0x300,
	[ECC_ENCIRQ_EN] =       0x80,
	[ECC_ENCIRQ_STA] =      0x84,
	[ECC_DECDONE] =         0x124,
	[ECC_DECIRQ_EN] =       0x200,
	[ECC_DECIRQ_STA] =      0x204,
पूर्ण;

अटल पूर्णांक mt7622_ecc_regs[] = अणु
	[ECC_ENCPAR00] =        0x10,
	[ECC_ENCIRQ_EN] =       0x30,
	[ECC_ENCIRQ_STA] =      0x34,
	[ECC_DECDONE] =         0x11c,
	[ECC_DECIRQ_EN] =       0x140,
	[ECC_DECIRQ_STA] =      0x144,
पूर्ण;

अटल अंतरभूत व्योम mtk_ecc_रुको_idle(काष्ठा mtk_ecc *ecc,
				     क्रमागत mtk_ecc_operation op)
अणु
	काष्ठा device *dev = ecc->dev;
	u32 val;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout_atomic(ecc->regs + ECC_IDLE_REG(op), val,
					val & ECC_IDLE_MASK,
					10, ECC_TIMEOUT);
	अगर (ret)
		dev_warn(dev, "%s NOT idle\n",
			 op == ECC_ENCODE ? "encoder" : "decoder");
पूर्ण

अटल irqवापस_t mtk_ecc_irq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा mtk_ecc *ecc = id;
	u32 dec, enc;

	dec = पढ़ोw(ecc->regs + ecc->caps->ecc_regs[ECC_DECIRQ_STA])
		    & ECC_IRQ_EN;
	अगर (dec) अणु
		dec = पढ़ोw(ecc->regs + ecc->caps->ecc_regs[ECC_DECDONE]);
		अगर (dec & ecc->sectors) अणु
			/*
			 * Clear decode IRQ status once again to ensure that
			 * there will be no extra IRQ.
			 */
			पढ़ोw(ecc->regs + ecc->caps->ecc_regs[ECC_DECIRQ_STA]);
			ecc->sectors = 0;
			complete(&ecc->करोne);
		पूर्ण अन्यथा अणु
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण अन्यथा अणु
		enc = पढ़ोl(ecc->regs + ecc->caps->ecc_regs[ECC_ENCIRQ_STA])
		      & ECC_IRQ_EN;
		अगर (enc)
			complete(&ecc->करोne);
		अन्यथा
			वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mtk_ecc_config(काष्ठा mtk_ecc *ecc, काष्ठा mtk_ecc_config *config)
अणु
	u32 ecc_bit, dec_sz, enc_sz;
	u32 reg, i;

	क्रम (i = 0; i < ecc->caps->num_ecc_strength; i++) अणु
		अगर (ecc->caps->ecc_strength[i] == config->strength)
			अवरोध;
	पूर्ण

	अगर (i == ecc->caps->num_ecc_strength) अणु
		dev_err(ecc->dev, "invalid ecc strength %d\n",
			config->strength);
		वापस -EINVAL;
	पूर्ण

	ecc_bit = i;

	अगर (config->op == ECC_ENCODE) अणु
		/* configure ECC encoder (in bits) */
		enc_sz = config->len << 3;

		reg = ecc_bit | (config->mode << ecc->caps->ecc_mode_shअगरt);
		reg |= (enc_sz << ECC_MS_SHIFT);
		ग_लिखोl(reg, ecc->regs + ECC_ENCCNFG);

		अगर (config->mode != ECC_NFI_MODE)
			ग_लिखोl(lower_32_bits(config->addr),
			       ecc->regs + ECC_ENCDIADDR);

	पूर्ण अन्यथा अणु
		/* configure ECC decoder (in bits) */
		dec_sz = (config->len << 3) +
			 config->strength * ecc->caps->parity_bits;

		reg = ecc_bit | (config->mode << ecc->caps->ecc_mode_shअगरt);
		reg |= (dec_sz << ECC_MS_SHIFT) | DEC_CNFG_CORRECT;
		reg |= DEC_EMPTY_EN;
		ग_लिखोl(reg, ecc->regs + ECC_DECCNFG);

		अगर (config->sectors)
			ecc->sectors = 1 << (config->sectors - 1);
	पूर्ण

	वापस 0;
पूर्ण

व्योम mtk_ecc_get_stats(काष्ठा mtk_ecc *ecc, काष्ठा mtk_ecc_stats *stats,
		       पूर्णांक sectors)
अणु
	u32 offset, i, err;
	u32 bitflips = 0;

	stats->corrected = 0;
	stats->failed = 0;

	क्रम (i = 0; i < sectors; i++) अणु
		offset = (i >> 2) << 2;
		err = पढ़ोl(ecc->regs + ECC_DECENUM0 + offset);
		err = err >> ((i % 4) * 8);
		err &= ecc->caps->err_mask;
		अगर (err == ecc->caps->err_mask) अणु
			/* uncorrectable errors */
			stats->failed++;
			जारी;
		पूर्ण

		stats->corrected += err;
		bitflips = max_t(u32, bitflips, err);
	पूर्ण

	stats->bitflips = bitflips;
पूर्ण
EXPORT_SYMBOL(mtk_ecc_get_stats);

व्योम mtk_ecc_release(काष्ठा mtk_ecc *ecc)
अणु
	clk_disable_unprepare(ecc->clk);
	put_device(ecc->dev);
पूर्ण
EXPORT_SYMBOL(mtk_ecc_release);

अटल व्योम mtk_ecc_hw_init(काष्ठा mtk_ecc *ecc)
अणु
	mtk_ecc_रुको_idle(ecc, ECC_ENCODE);
	ग_लिखोw(ECC_OP_DISABLE, ecc->regs + ECC_ENCCON);

	mtk_ecc_रुको_idle(ecc, ECC_DECODE);
	ग_लिखोl(ECC_OP_DISABLE, ecc->regs + ECC_DECCON);
पूर्ण

अटल काष्ठा mtk_ecc *mtk_ecc_get(काष्ठा device_node *np)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा mtk_ecc *ecc;

	pdev = of_find_device_by_node(np);
	अगर (!pdev)
		वापस ERR_PTR(-EPROBE_DEFER);

	ecc = platक्रमm_get_drvdata(pdev);
	अगर (!ecc) अणु
		put_device(&pdev->dev);
		वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	clk_prepare_enable(ecc->clk);
	mtk_ecc_hw_init(ecc);

	वापस ecc;
पूर्ण

काष्ठा mtk_ecc *of_mtk_ecc_get(काष्ठा device_node *of_node)
अणु
	काष्ठा mtk_ecc *ecc = शून्य;
	काष्ठा device_node *np;

	np = of_parse_phandle(of_node, "ecc-engine", 0);
	अगर (np) अणु
		ecc = mtk_ecc_get(np);
		of_node_put(np);
	पूर्ण

	वापस ecc;
पूर्ण
EXPORT_SYMBOL(of_mtk_ecc_get);

पूर्णांक mtk_ecc_enable(काष्ठा mtk_ecc *ecc, काष्ठा mtk_ecc_config *config)
अणु
	क्रमागत mtk_ecc_operation op = config->op;
	u16 reg_val;
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&ecc->lock);
	अगर (ret) अणु
		dev_err(ecc->dev, "interrupted when attempting to lock\n");
		वापस ret;
	पूर्ण

	mtk_ecc_रुको_idle(ecc, op);

	ret = mtk_ecc_config(ecc, config);
	अगर (ret) अणु
		mutex_unlock(&ecc->lock);
		वापस ret;
	पूर्ण

	अगर (config->mode != ECC_NFI_MODE || op != ECC_ENCODE) अणु
		init_completion(&ecc->करोne);
		reg_val = ECC_IRQ_EN;
		/*
		 * For ECC_NFI_MODE, अगर ecc->caps->pg_irq_sel is 1, then it
		 * means this chip can only generate one ecc irq during page
		 * पढ़ो / ग_लिखो. If is 0, generate one ecc irq each ecc step.
		 */
		अगर (ecc->caps->pg_irq_sel && config->mode == ECC_NFI_MODE)
			reg_val |= ECC_PG_IRQ_SEL;
		अगर (op == ECC_ENCODE)
			ग_लिखोw(reg_val, ecc->regs +
			       ecc->caps->ecc_regs[ECC_ENCIRQ_EN]);
		अन्यथा
			ग_लिखोw(reg_val, ecc->regs +
			       ecc->caps->ecc_regs[ECC_DECIRQ_EN]);
	पूर्ण

	ग_लिखोw(ECC_OP_ENABLE, ecc->regs + ECC_CTL_REG(op));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mtk_ecc_enable);

व्योम mtk_ecc_disable(काष्ठा mtk_ecc *ecc)
अणु
	क्रमागत mtk_ecc_operation op = ECC_ENCODE;

	/* find out the running operation */
	अगर (पढ़ोw(ecc->regs + ECC_CTL_REG(op)) != ECC_OP_ENABLE)
		op = ECC_DECODE;

	/* disable it */
	mtk_ecc_रुको_idle(ecc, op);
	अगर (op == ECC_DECODE) अणु
		/*
		 * Clear decode IRQ status in हाल there is a समयout to रुको
		 * decode IRQ.
		 */
		पढ़ोw(ecc->regs + ecc->caps->ecc_regs[ECC_DECDONE]);
		ग_लिखोw(0, ecc->regs + ecc->caps->ecc_regs[ECC_DECIRQ_EN]);
	पूर्ण अन्यथा अणु
		ग_लिखोw(0, ecc->regs + ecc->caps->ecc_regs[ECC_ENCIRQ_EN]);
	पूर्ण

	ग_लिखोw(ECC_OP_DISABLE, ecc->regs + ECC_CTL_REG(op));

	mutex_unlock(&ecc->lock);
पूर्ण
EXPORT_SYMBOL(mtk_ecc_disable);

पूर्णांक mtk_ecc_रुको_करोne(काष्ठा mtk_ecc *ecc, क्रमागत mtk_ecc_operation op)
अणु
	पूर्णांक ret;

	ret = रुको_क्रम_completion_समयout(&ecc->करोne, msecs_to_jअगरfies(500));
	अगर (!ret) अणु
		dev_err(ecc->dev, "%s timeout - interrupt did not arrive)\n",
			(op == ECC_ENCODE) ? "encoder" : "decoder");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mtk_ecc_रुको_करोne);

पूर्णांक mtk_ecc_encode(काष्ठा mtk_ecc *ecc, काष्ठा mtk_ecc_config *config,
		   u8 *data, u32 bytes)
अणु
	dma_addr_t addr;
	u32 len;
	पूर्णांक ret;

	addr = dma_map_single(ecc->dev, data, bytes, DMA_TO_DEVICE);
	ret = dma_mapping_error(ecc->dev, addr);
	अगर (ret) अणु
		dev_err(ecc->dev, "dma mapping error\n");
		वापस -EINVAL;
	पूर्ण

	config->op = ECC_ENCODE;
	config->addr = addr;
	ret = mtk_ecc_enable(ecc, config);
	अगर (ret) अणु
		dma_unmap_single(ecc->dev, addr, bytes, DMA_TO_DEVICE);
		वापस ret;
	पूर्ण

	ret = mtk_ecc_रुको_करोne(ecc, ECC_ENCODE);
	अगर (ret)
		जाओ समयout;

	mtk_ecc_रुको_idle(ecc, ECC_ENCODE);

	/* Program ECC bytes to OOB: per sector oob = FDM + ECC + SPARE */
	len = (config->strength * ecc->caps->parity_bits + 7) >> 3;

	/* ग_लिखो the parity bytes generated by the ECC back to temp buffer */
	__ioपढ़ो32_copy(ecc->eccdata,
			ecc->regs + ecc->caps->ecc_regs[ECC_ENCPAR00],
			round_up(len, 4));

	/* copy पूर्णांकo possibly unaligned OOB region with actual length */
	स_नकल(data + bytes, ecc->eccdata, len);
समयout:

	dma_unmap_single(ecc->dev, addr, bytes, DMA_TO_DEVICE);
	mtk_ecc_disable(ecc);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mtk_ecc_encode);

व्योम mtk_ecc_adjust_strength(काष्ठा mtk_ecc *ecc, u32 *p)
अणु
	स्थिर u8 *ecc_strength = ecc->caps->ecc_strength;
	पूर्णांक i;

	क्रम (i = 0; i < ecc->caps->num_ecc_strength; i++) अणु
		अगर (*p <= ecc_strength[i]) अणु
			अगर (!i)
				*p = ecc_strength[i];
			अन्यथा अगर (*p != ecc_strength[i])
				*p = ecc_strength[i - 1];
			वापस;
		पूर्ण
	पूर्ण

	*p = ecc_strength[ecc->caps->num_ecc_strength - 1];
पूर्ण
EXPORT_SYMBOL(mtk_ecc_adjust_strength);

अचिन्हित पूर्णांक mtk_ecc_get_parity_bits(काष्ठा mtk_ecc *ecc)
अणु
	वापस ecc->caps->parity_bits;
पूर्ण
EXPORT_SYMBOL(mtk_ecc_get_parity_bits);

अटल स्थिर काष्ठा mtk_ecc_caps mtk_ecc_caps_mt2701 = अणु
	.err_mask = 0x3f,
	.ecc_strength = ecc_strength_mt2701,
	.ecc_regs = mt2701_ecc_regs,
	.num_ecc_strength = 20,
	.ecc_mode_shअगरt = 5,
	.parity_bits = 14,
	.pg_irq_sel = 0,
पूर्ण;

अटल स्थिर काष्ठा mtk_ecc_caps mtk_ecc_caps_mt2712 = अणु
	.err_mask = 0x7f,
	.ecc_strength = ecc_strength_mt2712,
	.ecc_regs = mt2712_ecc_regs,
	.num_ecc_strength = 23,
	.ecc_mode_shअगरt = 5,
	.parity_bits = 14,
	.pg_irq_sel = 1,
पूर्ण;

अटल स्थिर काष्ठा mtk_ecc_caps mtk_ecc_caps_mt7622 = अणु
	.err_mask = 0x3f,
	.ecc_strength = ecc_strength_mt7622,
	.ecc_regs = mt7622_ecc_regs,
	.num_ecc_strength = 7,
	.ecc_mode_shअगरt = 4,
	.parity_bits = 13,
	.pg_irq_sel = 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_ecc_dt_match[] = अणु
	अणु
		.compatible = "mediatek,mt2701-ecc",
		.data = &mtk_ecc_caps_mt2701,
	पूर्ण, अणु
		.compatible = "mediatek,mt2712-ecc",
		.data = &mtk_ecc_caps_mt2712,
	पूर्ण, अणु
		.compatible = "mediatek,mt7622-ecc",
		.data = &mtk_ecc_caps_mt7622,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक mtk_ecc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_ecc *ecc;
	काष्ठा resource *res;
	u32 max_eccdata_size;
	पूर्णांक irq, ret;

	ecc = devm_kzalloc(dev, माप(*ecc), GFP_KERNEL);
	अगर (!ecc)
		वापस -ENOMEM;

	ecc->caps = of_device_get_match_data(dev);

	max_eccdata_size = ecc->caps->num_ecc_strength - 1;
	max_eccdata_size = ecc->caps->ecc_strength[max_eccdata_size];
	max_eccdata_size = (max_eccdata_size * ecc->caps->parity_bits + 7) >> 3;
	max_eccdata_size = round_up(max_eccdata_size, 4);
	ecc->eccdata = devm_kzalloc(dev, max_eccdata_size, GFP_KERNEL);
	अगर (!ecc->eccdata)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ecc->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ecc->regs)) अणु
		dev_err(dev, "failed to map regs: %ld\n", PTR_ERR(ecc->regs));
		वापस PTR_ERR(ecc->regs);
	पूर्ण

	ecc->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(ecc->clk)) अणु
		dev_err(dev, "failed to get clock: %ld\n", PTR_ERR(ecc->clk));
		वापस PTR_ERR(ecc->clk);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = dma_set_mask(dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(dev, "failed to set DMA mask\n");
		वापस ret;
	पूर्ण

	ret = devm_request_irq(dev, irq, mtk_ecc_irq, 0x0, "mtk-ecc", ecc);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq\n");
		वापस -EINVAL;
	पूर्ण

	ecc->dev = dev;
	mutex_init(&ecc->lock);
	platक्रमm_set_drvdata(pdev, ecc);
	dev_info(dev, "probed\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mtk_ecc_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_ecc *ecc = dev_get_drvdata(dev);

	clk_disable_unprepare(ecc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_ecc_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_ecc *ecc = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(ecc->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clk\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mtk_ecc_pm_ops, mtk_ecc_suspend, mtk_ecc_resume);
#पूर्ण_अगर

MODULE_DEVICE_TABLE(of, mtk_ecc_dt_match);

अटल काष्ठा platक्रमm_driver mtk_ecc_driver = अणु
	.probe  = mtk_ecc_probe,
	.driver = अणु
		.name  = "mtk-ecc",
		.of_match_table = of_match_ptr(mtk_ecc_dt_match),
#अगर_घोषित CONFIG_PM_SLEEP
		.pm = &mtk_ecc_pm_ops,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_ecc_driver);

MODULE_AUTHOR("Xiaolei Li <xiaolei.li@mediatek.com>");
MODULE_DESCRIPTION("MTK Nand ECC Driver");
MODULE_LICENSE("Dual MIT/GPL");
