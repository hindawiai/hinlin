<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HiSilicon FMC SPI NOR flash controller driver
 *
 * Copyright (c) 2015-2016 HiSilicon Technologies Co., Ltd.
 */
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/spi-nor.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/* Hardware रेजिस्टर offsets and field definitions */
#घोषणा FMC_CFG				0x00
#घोषणा FMC_CFG_OP_MODE_MASK		BIT_MASK(0)
#घोषणा FMC_CFG_OP_MODE_BOOT		0
#घोषणा FMC_CFG_OP_MODE_NORMAL		1
#घोषणा FMC_CFG_FLASH_SEL(type)		(((type) & 0x3) << 1)
#घोषणा FMC_CFG_FLASH_SEL_MASK		0x6
#घोषणा FMC_ECC_TYPE(type)		(((type) & 0x7) << 5)
#घोषणा FMC_ECC_TYPE_MASK		GENMASK(7, 5)
#घोषणा SPI_NOR_ADDR_MODE_MASK		BIT_MASK(10)
#घोषणा SPI_NOR_ADDR_MODE_3BYTES	(0x0 << 10)
#घोषणा SPI_NOR_ADDR_MODE_4BYTES	(0x1 << 10)
#घोषणा FMC_GLOBAL_CFG			0x04
#घोषणा FMC_GLOBAL_CFG_WP_ENABLE	BIT(6)
#घोषणा FMC_SPI_TIMING_CFG		0x08
#घोषणा TIMING_CFG_TCSH(nr)		(((nr) & 0xf) << 8)
#घोषणा TIMING_CFG_TCSS(nr)		(((nr) & 0xf) << 4)
#घोषणा TIMING_CFG_TSHSL(nr)		((nr) & 0xf)
#घोषणा CS_HOLD_TIME			0x6
#घोषणा CS_SETUP_TIME			0x6
#घोषणा CS_DESELECT_TIME		0xf
#घोषणा FMC_INT				0x18
#घोषणा FMC_INT_OP_DONE			BIT(0)
#घोषणा FMC_INT_CLR			0x20
#घोषणा FMC_CMD				0x24
#घोषणा FMC_CMD_CMD1(cmd)		((cmd) & 0xff)
#घोषणा FMC_ADDRL			0x2c
#घोषणा FMC_OP_CFG			0x30
#घोषणा OP_CFG_FM_CS(cs)		((cs) << 11)
#घोषणा OP_CFG_MEM_IF_TYPE(type)	(((type) & 0x7) << 7)
#घोषणा OP_CFG_ADDR_NUM(addr)		(((addr) & 0x7) << 4)
#घोषणा OP_CFG_DUMMY_NUM(dummy)		((dummy) & 0xf)
#घोषणा FMC_DATA_NUM			0x38
#घोषणा FMC_DATA_NUM_CNT(cnt)		((cnt) & GENMASK(13, 0))
#घोषणा FMC_OP				0x3c
#घोषणा FMC_OP_DUMMY_EN			BIT(8)
#घोषणा FMC_OP_CMD1_EN			BIT(7)
#घोषणा FMC_OP_ADDR_EN			BIT(6)
#घोषणा FMC_OP_WRITE_DATA_EN		BIT(5)
#घोषणा FMC_OP_READ_DATA_EN		BIT(2)
#घोषणा FMC_OP_READ_STATUS_EN		BIT(1)
#घोषणा FMC_OP_REG_OP_START		BIT(0)
#घोषणा FMC_DMA_LEN			0x40
#घोषणा FMC_DMA_LEN_SET(len)		((len) & GENMASK(27, 0))
#घोषणा FMC_DMA_SADDR_D0		0x4c
#घोषणा HIFMC_DMA_MAX_LEN		(4096)
#घोषणा HIFMC_DMA_MASK			(HIFMC_DMA_MAX_LEN - 1)
#घोषणा FMC_OP_DMA			0x68
#घोषणा OP_CTRL_RD_OPCODE(code)		(((code) & 0xff) << 16)
#घोषणा OP_CTRL_WR_OPCODE(code)		(((code) & 0xff) << 8)
#घोषणा OP_CTRL_RW_OP(op)		((op) << 1)
#घोषणा OP_CTRL_DMA_OP_READY		BIT(0)
#घोषणा FMC_OP_READ			0x0
#घोषणा FMC_OP_WRITE			0x1
#घोषणा FMC_WAIT_TIMEOUT		1000000

क्रमागत hअगरmc_अगरtype अणु
	IF_TYPE_STD,
	IF_TYPE_DUAL,
	IF_TYPE_DIO,
	IF_TYPE_QUAD,
	IF_TYPE_QIO,
पूर्ण;

काष्ठा hअगरmc_priv अणु
	u32 chipselect;
	u32 clkrate;
	काष्ठा hअगरmc_host *host;
पूर्ण;

#घोषणा HIFMC_MAX_CHIP_NUM		2
काष्ठा hअगरmc_host अणु
	काष्ठा device *dev;
	काष्ठा mutex lock;

	व्योम __iomem *regbase;
	व्योम __iomem *iobase;
	काष्ठा clk *clk;
	व्योम *buffer;
	dma_addr_t dma_buffer;

	काष्ठा spi_nor	*nor[HIFMC_MAX_CHIP_NUM];
	u32 num_chip;
पूर्ण;

अटल अंतरभूत पूर्णांक hisi_spi_nor_रुको_op_finish(काष्ठा hअगरmc_host *host)
अणु
	u32 reg;

	वापस पढ़ोl_poll_समयout(host->regbase + FMC_INT, reg,
		(reg & FMC_INT_OP_DONE), 0, FMC_WAIT_TIMEOUT);
पूर्ण

अटल पूर्णांक hisi_spi_nor_get_अगर_type(क्रमागत spi_nor_protocol proto)
अणु
	क्रमागत hअगरmc_अगरtype अगर_type;

	चयन (proto) अणु
	हाल SNOR_PROTO_1_1_2:
		अगर_type = IF_TYPE_DUAL;
		अवरोध;
	हाल SNOR_PROTO_1_2_2:
		अगर_type = IF_TYPE_DIO;
		अवरोध;
	हाल SNOR_PROTO_1_1_4:
		अगर_type = IF_TYPE_QUAD;
		अवरोध;
	हाल SNOR_PROTO_1_4_4:
		अगर_type = IF_TYPE_QIO;
		अवरोध;
	हाल SNOR_PROTO_1_1_1:
	शेष:
		अगर_type = IF_TYPE_STD;
		अवरोध;
	पूर्ण

	वापस अगर_type;
पूर्ण

अटल व्योम hisi_spi_nor_init(काष्ठा hअगरmc_host *host)
अणु
	u32 reg;

	reg = TIMING_CFG_TCSH(CS_HOLD_TIME)
		| TIMING_CFG_TCSS(CS_SETUP_TIME)
		| TIMING_CFG_TSHSL(CS_DESELECT_TIME);
	ग_लिखोl(reg, host->regbase + FMC_SPI_TIMING_CFG);
पूर्ण

अटल पूर्णांक hisi_spi_nor_prep(काष्ठा spi_nor *nor)
अणु
	काष्ठा hअगरmc_priv *priv = nor->priv;
	काष्ठा hअगरmc_host *host = priv->host;
	पूर्णांक ret;

	mutex_lock(&host->lock);

	ret = clk_set_rate(host->clk, priv->clkrate);
	अगर (ret)
		जाओ out;

	ret = clk_prepare_enable(host->clk);
	अगर (ret)
		जाओ out;

	वापस 0;

out:
	mutex_unlock(&host->lock);
	वापस ret;
पूर्ण

अटल व्योम hisi_spi_nor_unprep(काष्ठा spi_nor *nor)
अणु
	काष्ठा hअगरmc_priv *priv = nor->priv;
	काष्ठा hअगरmc_host *host = priv->host;

	clk_disable_unprepare(host->clk);
	mutex_unlock(&host->lock);
पूर्ण

अटल पूर्णांक hisi_spi_nor_op_reg(काष्ठा spi_nor *nor,
				u8 opcode, माप_प्रकार len, u8 optype)
अणु
	काष्ठा hअगरmc_priv *priv = nor->priv;
	काष्ठा hअगरmc_host *host = priv->host;
	u32 reg;

	reg = FMC_CMD_CMD1(opcode);
	ग_लिखोl(reg, host->regbase + FMC_CMD);

	reg = FMC_DATA_NUM_CNT(len);
	ग_लिखोl(reg, host->regbase + FMC_DATA_NUM);

	reg = OP_CFG_FM_CS(priv->chipselect);
	ग_लिखोl(reg, host->regbase + FMC_OP_CFG);

	ग_लिखोl(0xff, host->regbase + FMC_INT_CLR);
	reg = FMC_OP_CMD1_EN | FMC_OP_REG_OP_START | optype;
	ग_लिखोl(reg, host->regbase + FMC_OP);

	वापस hisi_spi_nor_रुको_op_finish(host);
पूर्ण

अटल पूर्णांक hisi_spi_nor_पढ़ो_reg(काष्ठा spi_nor *nor, u8 opcode, u8 *buf,
				 माप_प्रकार len)
अणु
	काष्ठा hअगरmc_priv *priv = nor->priv;
	काष्ठा hअगरmc_host *host = priv->host;
	पूर्णांक ret;

	ret = hisi_spi_nor_op_reg(nor, opcode, len, FMC_OP_READ_DATA_EN);
	अगर (ret)
		वापस ret;

	स_नकल_fromio(buf, host->iobase, len);
	वापस 0;
पूर्ण

अटल पूर्णांक hisi_spi_nor_ग_लिखो_reg(काष्ठा spi_nor *nor, u8 opcode,
				  स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा hअगरmc_priv *priv = nor->priv;
	काष्ठा hअगरmc_host *host = priv->host;

	अगर (len)
		स_नकल_toio(host->iobase, buf, len);

	वापस hisi_spi_nor_op_reg(nor, opcode, len, FMC_OP_WRITE_DATA_EN);
पूर्ण

अटल पूर्णांक hisi_spi_nor_dma_transfer(काष्ठा spi_nor *nor, loff_t start_off,
		dma_addr_t dma_buf, माप_प्रकार len, u8 op_type)
अणु
	काष्ठा hअगरmc_priv *priv = nor->priv;
	काष्ठा hअगरmc_host *host = priv->host;
	u8 अगर_type = 0;
	u32 reg;

	reg = पढ़ोl(host->regbase + FMC_CFG);
	reg &= ~(FMC_CFG_OP_MODE_MASK | SPI_NOR_ADDR_MODE_MASK);
	reg |= FMC_CFG_OP_MODE_NORMAL;
	reg |= (nor->addr_width == 4) ? SPI_NOR_ADDR_MODE_4BYTES
		: SPI_NOR_ADDR_MODE_3BYTES;
	ग_लिखोl(reg, host->regbase + FMC_CFG);

	ग_लिखोl(start_off, host->regbase + FMC_ADDRL);
	ग_लिखोl(dma_buf, host->regbase + FMC_DMA_SADDR_D0);
	ग_लिखोl(FMC_DMA_LEN_SET(len), host->regbase + FMC_DMA_LEN);

	reg = OP_CFG_FM_CS(priv->chipselect);
	अगर (op_type == FMC_OP_READ)
		अगर_type = hisi_spi_nor_get_अगर_type(nor->पढ़ो_proto);
	अन्यथा
		अगर_type = hisi_spi_nor_get_अगर_type(nor->ग_लिखो_proto);
	reg |= OP_CFG_MEM_IF_TYPE(अगर_type);
	अगर (op_type == FMC_OP_READ)
		reg |= OP_CFG_DUMMY_NUM(nor->पढ़ो_dummy >> 3);
	ग_लिखोl(reg, host->regbase + FMC_OP_CFG);

	ग_लिखोl(0xff, host->regbase + FMC_INT_CLR);
	reg = OP_CTRL_RW_OP(op_type) | OP_CTRL_DMA_OP_READY;
	reg |= (op_type == FMC_OP_READ)
		? OP_CTRL_RD_OPCODE(nor->पढ़ो_opcode)
		: OP_CTRL_WR_OPCODE(nor->program_opcode);
	ग_लिखोl(reg, host->regbase + FMC_OP_DMA);

	वापस hisi_spi_nor_रुको_op_finish(host);
पूर्ण

अटल sमाप_प्रकार hisi_spi_nor_पढ़ो(काष्ठा spi_nor *nor, loff_t from, माप_प्रकार len,
		u_अक्षर *पढ़ो_buf)
अणु
	काष्ठा hअगरmc_priv *priv = nor->priv;
	काष्ठा hअगरmc_host *host = priv->host;
	माप_प्रकार offset;
	पूर्णांक ret;

	क्रम (offset = 0; offset < len; offset += HIFMC_DMA_MAX_LEN) अणु
		माप_प्रकार trans = min_t(माप_प्रकार, HIFMC_DMA_MAX_LEN, len - offset);

		ret = hisi_spi_nor_dma_transfer(nor,
			from + offset, host->dma_buffer, trans, FMC_OP_READ);
		अगर (ret) अणु
			dev_warn(nor->dev, "DMA read timeout\n");
			वापस ret;
		पूर्ण
		स_नकल(पढ़ो_buf + offset, host->buffer, trans);
	पूर्ण

	वापस len;
पूर्ण

अटल sमाप_प्रकार hisi_spi_nor_ग_लिखो(काष्ठा spi_nor *nor, loff_t to,
			माप_प्रकार len, स्थिर u_अक्षर *ग_लिखो_buf)
अणु
	काष्ठा hअगरmc_priv *priv = nor->priv;
	काष्ठा hअगरmc_host *host = priv->host;
	माप_प्रकार offset;
	पूर्णांक ret;

	क्रम (offset = 0; offset < len; offset += HIFMC_DMA_MAX_LEN) अणु
		माप_प्रकार trans = min_t(माप_प्रकार, HIFMC_DMA_MAX_LEN, len - offset);

		स_नकल(host->buffer, ग_लिखो_buf + offset, trans);
		ret = hisi_spi_nor_dma_transfer(nor,
			to + offset, host->dma_buffer, trans, FMC_OP_WRITE);
		अगर (ret) अणु
			dev_warn(nor->dev, "DMA write timeout\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण

अटल स्थिर काष्ठा spi_nor_controller_ops hisi_controller_ops = अणु
	.prepare = hisi_spi_nor_prep,
	.unprepare = hisi_spi_nor_unprep,
	.पढ़ो_reg = hisi_spi_nor_पढ़ो_reg,
	.ग_लिखो_reg = hisi_spi_nor_ग_लिखो_reg,
	.पढ़ो = hisi_spi_nor_पढ़ो,
	.ग_लिखो = hisi_spi_nor_ग_लिखो,
पूर्ण;

/*
 * Get spi flash device inक्रमmation and रेजिस्टर it as a mtd device.
 */
अटल पूर्णांक hisi_spi_nor_रेजिस्टर(काष्ठा device_node *np,
				काष्ठा hअगरmc_host *host)
अणु
	स्थिर काष्ठा spi_nor_hwcaps hwcaps = अणु
		.mask = SNOR_HWCAPS_READ |
			SNOR_HWCAPS_READ_FAST |
			SNOR_HWCAPS_READ_1_1_2 |
			SNOR_HWCAPS_READ_1_1_4 |
			SNOR_HWCAPS_PP,
	पूर्ण;
	काष्ठा device *dev = host->dev;
	काष्ठा spi_nor *nor;
	काष्ठा hअगरmc_priv *priv;
	काष्ठा mtd_info *mtd;
	पूर्णांक ret;

	nor = devm_kzalloc(dev, माप(*nor), GFP_KERNEL);
	अगर (!nor)
		वापस -ENOMEM;

	nor->dev = dev;
	spi_nor_set_flash_node(nor, np);

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32(np, "reg", &priv->chipselect);
	अगर (ret) अणु
		dev_err(dev, "There's no reg property for %pOF\n",
			np);
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "spi-max-frequency",
			&priv->clkrate);
	अगर (ret) अणु
		dev_err(dev, "There's no spi-max-frequency property for %pOF\n",
			np);
		वापस ret;
	पूर्ण
	priv->host = host;
	nor->priv = priv;
	nor->controller_ops = &hisi_controller_ops;

	ret = spi_nor_scan(nor, शून्य, &hwcaps);
	अगर (ret)
		वापस ret;

	mtd = &nor->mtd;
	mtd->name = np->name;
	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret)
		वापस ret;

	host->nor[host->num_chip] = nor;
	host->num_chip++;
	वापस 0;
पूर्ण

अटल व्योम hisi_spi_nor_unरेजिस्टर_all(काष्ठा hअगरmc_host *host)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < host->num_chip; i++)
		mtd_device_unरेजिस्टर(&host->nor[i]->mtd);
पूर्ण

अटल पूर्णांक hisi_spi_nor_रेजिस्टर_all(काष्ठा hअगरmc_host *host)
अणु
	काष्ठा device *dev = host->dev;
	काष्ठा device_node *np;
	पूर्णांक ret;

	क्रम_each_available_child_of_node(dev->of_node, np) अणु
		ret = hisi_spi_nor_रेजिस्टर(np, host);
		अगर (ret) अणु
			of_node_put(np);
			जाओ fail;
		पूर्ण

		अगर (host->num_chip == HIFMC_MAX_CHIP_NUM) अणु
			dev_warn(dev, "Flash device number exceeds the maximum chipselect number\n");
			of_node_put(np);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;

fail:
	hisi_spi_nor_unरेजिस्टर_all(host);
	वापस ret;
पूर्ण

अटल पूर्णांक hisi_spi_nor_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा hअगरmc_host *host;
	पूर्णांक ret;

	host = devm_kzalloc(dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, host);
	host->dev = dev;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "control");
	host->regbase = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(host->regbase))
		वापस PTR_ERR(host->regbase);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "memory");
	host->iobase = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(host->iobase))
		वापस PTR_ERR(host->iobase);

	host->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(host->clk))
		वापस PTR_ERR(host->clk);

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_warn(dev, "Unable to set dma mask\n");
		वापस ret;
	पूर्ण

	host->buffer = dmam_alloc_coherent(dev, HIFMC_DMA_MAX_LEN,
			&host->dma_buffer, GFP_KERNEL);
	अगर (!host->buffer)
		वापस -ENOMEM;

	ret = clk_prepare_enable(host->clk);
	अगर (ret)
		वापस ret;

	mutex_init(&host->lock);
	hisi_spi_nor_init(host);
	ret = hisi_spi_nor_रेजिस्टर_all(host);
	अगर (ret)
		mutex_destroy(&host->lock);

	clk_disable_unprepare(host->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक hisi_spi_nor_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hअगरmc_host *host = platक्रमm_get_drvdata(pdev);

	hisi_spi_nor_unरेजिस्टर_all(host);
	mutex_destroy(&host->lock);
	clk_disable_unprepare(host->clk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hisi_spi_nor_dt_ids[] = अणु
	अणु .compatible = "hisilicon,fmc-spi-nor"पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hisi_spi_nor_dt_ids);

अटल काष्ठा platक्रमm_driver hisi_spi_nor_driver = अणु
	.driver = अणु
		.name	= "hisi-sfc",
		.of_match_table = hisi_spi_nor_dt_ids,
	पूर्ण,
	.probe	= hisi_spi_nor_probe,
	.हटाओ	= hisi_spi_nor_हटाओ,
पूर्ण;
module_platक्रमm_driver(hisi_spi_nor_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("HiSilicon SPI Nor Flash Controller Driver");
