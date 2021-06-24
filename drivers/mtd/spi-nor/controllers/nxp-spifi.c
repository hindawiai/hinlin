<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI NOR driver क्रम NXP SPI Flash Interface (SPIFI)
 *
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 *
 * Based on Freescale QuadSPI driver:
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/spi-nor.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>

/* NXP SPIFI रेजिस्टरs, bits and macros */
#घोषणा SPIFI_CTRL				0x000
#घोषणा  SPIFI_CTRL_TIMEOUT(समयout)		(समयout)
#घोषणा  SPIFI_CTRL_CSHIGH(cshigh)		((cshigh) << 16)
#घोषणा  SPIFI_CTRL_MODE3			BIT(23)
#घोषणा  SPIFI_CTRL_DUAL			BIT(28)
#घोषणा  SPIFI_CTRL_FBCLK			BIT(30)
#घोषणा SPIFI_CMD				0x004
#घोषणा  SPIFI_CMD_DATALEN(dlen)		((dlen) & 0x3fff)
#घोषणा  SPIFI_CMD_DOUT				BIT(15)
#घोषणा  SPIFI_CMD_INTLEN(ilen)			((ilen) << 16)
#घोषणा  SPIFI_CMD_FIELDFORM(field)		((field) << 19)
#घोषणा  SPIFI_CMD_FIELDFORM_ALL_SERIAL		SPIFI_CMD_FIELDFORM(0x0)
#घोषणा  SPIFI_CMD_FIELDFORM_QUAD_DUAL_DATA	SPIFI_CMD_FIELDFORM(0x1)
#घोषणा  SPIFI_CMD_FRAMEFORM(frame)		((frame) << 21)
#घोषणा  SPIFI_CMD_FRAMEFORM_OPCODE_ONLY	SPIFI_CMD_FRAMEFORM(0x1)
#घोषणा  SPIFI_CMD_OPCODE(op)			((op) << 24)
#घोषणा SPIFI_ADDR				0x008
#घोषणा SPIFI_IDATA				0x00c
#घोषणा SPIFI_CLIMIT				0x010
#घोषणा SPIFI_DATA				0x014
#घोषणा SPIFI_MCMD				0x018
#घोषणा SPIFI_STAT				0x01c
#घोषणा  SPIFI_STAT_MCINIT			BIT(0)
#घोषणा  SPIFI_STAT_CMD				BIT(1)
#घोषणा  SPIFI_STAT_RESET			BIT(4)

#घोषणा SPI_NOR_MAX_ID_LEN	6

काष्ठा nxp_spअगरi अणु
	काष्ठा device *dev;
	काष्ठा clk *clk_spअगरi;
	काष्ठा clk *clk_reg;
	व्योम __iomem *io_base;
	व्योम __iomem *flash_base;
	काष्ठा spi_nor nor;
	bool memory_mode;
	u32 mcmd;
पूर्ण;

अटल पूर्णांक nxp_spअगरi_रुको_क्रम_cmd(काष्ठा nxp_spअगरi *spअगरi)
अणु
	u8 stat;
	पूर्णांक ret;

	ret = पढ़ोb_poll_समयout(spअगरi->io_base + SPIFI_STAT, stat,
				 !(stat & SPIFI_STAT_CMD), 10, 30);
	अगर (ret)
		dev_warn(spअगरi->dev, "command timed out\n");

	वापस ret;
पूर्ण

अटल पूर्णांक nxp_spअगरi_reset(काष्ठा nxp_spअगरi *spअगरi)
अणु
	u8 stat;
	पूर्णांक ret;

	ग_लिखोl(SPIFI_STAT_RESET, spअगरi->io_base + SPIFI_STAT);
	ret = पढ़ोb_poll_समयout(spअगरi->io_base + SPIFI_STAT, stat,
				 !(stat & SPIFI_STAT_RESET), 10, 30);
	अगर (ret)
		dev_warn(spअगरi->dev, "state reset timed out\n");

	वापस ret;
पूर्ण

अटल पूर्णांक nxp_spअगरi_set_memory_mode_off(काष्ठा nxp_spअगरi *spअगरi)
अणु
	पूर्णांक ret;

	अगर (!spअगरi->memory_mode)
		वापस 0;

	ret = nxp_spअगरi_reset(spअगरi);
	अगर (ret)
		dev_err(spअगरi->dev, "unable to enter command mode\n");
	अन्यथा
		spअगरi->memory_mode = false;

	वापस ret;
पूर्ण

अटल पूर्णांक nxp_spअगरi_set_memory_mode_on(काष्ठा nxp_spअगरi *spअगरi)
अणु
	u8 stat;
	पूर्णांक ret;

	अगर (spअगरi->memory_mode)
		वापस 0;

	ग_लिखोl(spअगरi->mcmd, spअगरi->io_base + SPIFI_MCMD);
	ret = पढ़ोb_poll_समयout(spअगरi->io_base + SPIFI_STAT, stat,
				 stat & SPIFI_STAT_MCINIT, 10, 30);
	अगर (ret)
		dev_err(spअगरi->dev, "unable to enter memory mode\n");
	अन्यथा
		spअगरi->memory_mode = true;

	वापस ret;
पूर्ण

अटल पूर्णांक nxp_spअगरi_पढ़ो_reg(काष्ठा spi_nor *nor, u8 opcode, u8 *buf,
			      माप_प्रकार len)
अणु
	काष्ठा nxp_spअगरi *spअगरi = nor->priv;
	u32 cmd;
	पूर्णांक ret;

	ret = nxp_spअगरi_set_memory_mode_off(spअगरi);
	अगर (ret)
		वापस ret;

	cmd = SPIFI_CMD_DATALEN(len) |
	      SPIFI_CMD_OPCODE(opcode) |
	      SPIFI_CMD_FIELDFORM_ALL_SERIAL |
	      SPIFI_CMD_FRAMEFORM_OPCODE_ONLY;
	ग_लिखोl(cmd, spअगरi->io_base + SPIFI_CMD);

	जबतक (len--)
		*buf++ = पढ़ोb(spअगरi->io_base + SPIFI_DATA);

	वापस nxp_spअगरi_रुको_क्रम_cmd(spअगरi);
पूर्ण

अटल पूर्णांक nxp_spअगरi_ग_लिखो_reg(काष्ठा spi_nor *nor, u8 opcode, स्थिर u8 *buf,
			       माप_प्रकार len)
अणु
	काष्ठा nxp_spअगरi *spअगरi = nor->priv;
	u32 cmd;
	पूर्णांक ret;

	ret = nxp_spअगरi_set_memory_mode_off(spअगरi);
	अगर (ret)
		वापस ret;

	cmd = SPIFI_CMD_DOUT |
	      SPIFI_CMD_DATALEN(len) |
	      SPIFI_CMD_OPCODE(opcode) |
	      SPIFI_CMD_FIELDFORM_ALL_SERIAL |
	      SPIFI_CMD_FRAMEFORM_OPCODE_ONLY;
	ग_लिखोl(cmd, spअगरi->io_base + SPIFI_CMD);

	जबतक (len--)
		ग_लिखोb(*buf++, spअगरi->io_base + SPIFI_DATA);

	वापस nxp_spअगरi_रुको_क्रम_cmd(spअगरi);
पूर्ण

अटल sमाप_प्रकार nxp_spअगरi_पढ़ो(काष्ठा spi_nor *nor, loff_t from, माप_प्रकार len,
			      u_अक्षर *buf)
अणु
	काष्ठा nxp_spअगरi *spअगरi = nor->priv;
	पूर्णांक ret;

	ret = nxp_spअगरi_set_memory_mode_on(spअगरi);
	अगर (ret)
		वापस ret;

	स_नकल_fromio(buf, spअगरi->flash_base + from, len);

	वापस len;
पूर्ण

अटल sमाप_प्रकार nxp_spअगरi_ग_लिखो(काष्ठा spi_nor *nor, loff_t to, माप_प्रकार len,
			       स्थिर u_अक्षर *buf)
अणु
	काष्ठा nxp_spअगरi *spअगरi = nor->priv;
	u32 cmd;
	पूर्णांक ret;
	माप_प्रकार i;

	ret = nxp_spअगरi_set_memory_mode_off(spअगरi);
	अगर (ret)
		वापस ret;

	ग_लिखोl(to, spअगरi->io_base + SPIFI_ADDR);

	cmd = SPIFI_CMD_DOUT |
	      SPIFI_CMD_DATALEN(len) |
	      SPIFI_CMD_FIELDFORM_ALL_SERIAL |
	      SPIFI_CMD_OPCODE(nor->program_opcode) |
	      SPIFI_CMD_FRAMEFORM(spअगरi->nor.addr_width + 1);
	ग_लिखोl(cmd, spअगरi->io_base + SPIFI_CMD);

	क्रम (i = 0; i < len; i++)
		ग_लिखोb(buf[i], spअगरi->io_base + SPIFI_DATA);

	ret = nxp_spअगरi_रुको_क्रम_cmd(spअगरi);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल पूर्णांक nxp_spअगरi_erase(काष्ठा spi_nor *nor, loff_t offs)
अणु
	काष्ठा nxp_spअगरi *spअगरi = nor->priv;
	u32 cmd;
	पूर्णांक ret;

	ret = nxp_spअगरi_set_memory_mode_off(spअगरi);
	अगर (ret)
		वापस ret;

	ग_लिखोl(offs, spअगरi->io_base + SPIFI_ADDR);

	cmd = SPIFI_CMD_FIELDFORM_ALL_SERIAL |
	      SPIFI_CMD_OPCODE(nor->erase_opcode) |
	      SPIFI_CMD_FRAMEFORM(spअगरi->nor.addr_width + 1);
	ग_लिखोl(cmd, spअगरi->io_base + SPIFI_CMD);

	वापस nxp_spअगरi_रुको_क्रम_cmd(spअगरi);
पूर्ण

अटल पूर्णांक nxp_spअगरi_setup_memory_cmd(काष्ठा nxp_spअगरi *spअगरi)
अणु
	चयन (spअगरi->nor.पढ़ो_proto) अणु
	हाल SNOR_PROTO_1_1_1:
		spअगरi->mcmd = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
		अवरोध;
	हाल SNOR_PROTO_1_1_2:
	हाल SNOR_PROTO_1_1_4:
		spअगरi->mcmd = SPIFI_CMD_FIELDFORM_QUAD_DUAL_DATA;
		अवरोध;
	शेष:
		dev_err(spअगरi->dev, "unsupported SPI read mode\n");
		वापस -EINVAL;
	पूर्ण

	/* Memory mode supports address length between 1 and 4 */
	अगर (spअगरi->nor.addr_width < 1 || spअगरi->nor.addr_width > 4)
		वापस -EINVAL;

	spअगरi->mcmd |= SPIFI_CMD_OPCODE(spअगरi->nor.पढ़ो_opcode) |
		       SPIFI_CMD_INTLEN(spअगरi->nor.पढ़ो_dummy / 8) |
		       SPIFI_CMD_FRAMEFORM(spअगरi->nor.addr_width + 1);

	वापस 0;
पूर्ण

अटल व्योम nxp_spअगरi_dummy_id_पढ़ो(काष्ठा spi_nor *nor)
अणु
	u8 id[SPI_NOR_MAX_ID_LEN];
	nor->controller_ops->पढ़ो_reg(nor, SPINOR_OP_RDID, id,
				      SPI_NOR_MAX_ID_LEN);
पूर्ण

अटल स्थिर काष्ठा spi_nor_controller_ops nxp_spअगरi_controller_ops = अणु
	.पढ़ो_reg  = nxp_spअगरi_पढ़ो_reg,
	.ग_लिखो_reg = nxp_spअगरi_ग_लिखो_reg,
	.पढ़ो  = nxp_spअगरi_पढ़ो,
	.ग_लिखो = nxp_spअगरi_ग_लिखो,
	.erase = nxp_spअगरi_erase,
पूर्ण;

अटल पूर्णांक nxp_spअगरi_setup_flash(काष्ठा nxp_spअगरi *spअगरi,
				 काष्ठा device_node *np)
अणु
	काष्ठा spi_nor_hwcaps hwcaps = अणु
		.mask = SNOR_HWCAPS_READ |
			SNOR_HWCAPS_READ_FAST |
			SNOR_HWCAPS_PP,
	पूर्ण;
	u32 ctrl, property;
	u16 mode = 0;
	पूर्णांक ret;

	अगर (!of_property_पढ़ो_u32(np, "spi-rx-bus-width", &property)) अणु
		चयन (property) अणु
		हाल 1:
			अवरोध;
		हाल 2:
			mode |= SPI_RX_DUAL;
			अवरोध;
		हाल 4:
			mode |= SPI_RX_QUAD;
			अवरोध;
		शेष:
			dev_err(spअगरi->dev, "unsupported rx-bus-width\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (of_find_property(np, "spi-cpha", शून्य))
		mode |= SPI_CPHA;

	अगर (of_find_property(np, "spi-cpol", शून्य))
		mode |= SPI_CPOL;

	/* Setup control रेजिस्टर शेषs */
	ctrl = SPIFI_CTRL_TIMEOUT(1000) |
	       SPIFI_CTRL_CSHIGH(15) |
	       SPIFI_CTRL_FBCLK;

	अगर (mode & SPI_RX_DUAL) अणु
		ctrl |= SPIFI_CTRL_DUAL;
		hwcaps.mask |= SNOR_HWCAPS_READ_1_1_2;
	पूर्ण अन्यथा अगर (mode & SPI_RX_QUAD) अणु
		ctrl &= ~SPIFI_CTRL_DUAL;
		hwcaps.mask |= SNOR_HWCAPS_READ_1_1_4;
	पूर्ण अन्यथा अणु
		ctrl |= SPIFI_CTRL_DUAL;
	पूर्ण

	चयन (mode & (SPI_CPHA | SPI_CPOL)) अणु
	हाल SPI_MODE_0:
		ctrl &= ~SPIFI_CTRL_MODE3;
		अवरोध;
	हाल SPI_MODE_3:
		ctrl |= SPIFI_CTRL_MODE3;
		अवरोध;
	शेष:
		dev_err(spअगरi->dev, "only mode 0 and 3 supported\n");
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(ctrl, spअगरi->io_base + SPIFI_CTRL);

	spअगरi->nor.dev   = spअगरi->dev;
	spi_nor_set_flash_node(&spअगरi->nor, np);
	spअगरi->nor.priv  = spअगरi;
	spअगरi->nor.controller_ops = &nxp_spअगरi_controller_ops;

	/*
	 * The first पढ़ो on a hard reset isn't reliable so करो a
	 * dummy पढ़ो of the id beक्रमe calling spi_nor_scan().
	 * The reason क्रम this problem is unknown.
	 *
	 * The official NXP spअगरilib uses more or less the same
	 * workaround that is applied here by पढ़ोing the device
	 * id multiple बार.
	 */
	nxp_spअगरi_dummy_id_पढ़ो(&spअगरi->nor);

	ret = spi_nor_scan(&spअगरi->nor, शून्य, &hwcaps);
	अगर (ret) अणु
		dev_err(spअगरi->dev, "device scan failed\n");
		वापस ret;
	पूर्ण

	ret = nxp_spअगरi_setup_memory_cmd(spअगरi);
	अगर (ret) अणु
		dev_err(spअगरi->dev, "memory command setup failed\n");
		वापस ret;
	पूर्ण

	ret = mtd_device_रेजिस्टर(&spअगरi->nor.mtd, शून्य, 0);
	अगर (ret) अणु
		dev_err(spअगरi->dev, "mtd device parse failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nxp_spअगरi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *flash_np;
	काष्ठा nxp_spअगरi *spअगरi;
	काष्ठा resource *res;
	पूर्णांक ret;

	spअगरi = devm_kzalloc(&pdev->dev, माप(*spअगरi), GFP_KERNEL);
	अगर (!spअगरi)
		वापस -ENOMEM;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "spifi");
	spअगरi->io_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(spअगरi->io_base))
		वापस PTR_ERR(spअगरi->io_base);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "flash");
	spअगरi->flash_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(spअगरi->flash_base))
		वापस PTR_ERR(spअगरi->flash_base);

	spअगरi->clk_spअगरi = devm_clk_get(&pdev->dev, "spifi");
	अगर (IS_ERR(spअगरi->clk_spअगरi)) अणु
		dev_err(&pdev->dev, "spifi clock not found\n");
		वापस PTR_ERR(spअगरi->clk_spअगरi);
	पूर्ण

	spअगरi->clk_reg = devm_clk_get(&pdev->dev, "reg");
	अगर (IS_ERR(spअगरi->clk_reg)) अणु
		dev_err(&pdev->dev, "reg clock not found\n");
		वापस PTR_ERR(spअगरi->clk_reg);
	पूर्ण

	ret = clk_prepare_enable(spअगरi->clk_reg);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable reg clock\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(spअगरi->clk_spअगरi);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable spifi clock\n");
		जाओ dis_clk_reg;
	पूर्ण

	spअगरi->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, spअगरi);

	/* Initialize and reset device */
	nxp_spअगरi_reset(spअगरi);
	ग_लिखोl(0, spअगरi->io_base + SPIFI_IDATA);
	ग_लिखोl(0, spअगरi->io_base + SPIFI_MCMD);
	nxp_spअगरi_reset(spअगरi);

	flash_np = of_get_next_available_child(pdev->dev.of_node, शून्य);
	अगर (!flash_np) अणु
		dev_err(&pdev->dev, "no SPI flash device to configure\n");
		ret = -ENODEV;
		जाओ dis_clks;
	पूर्ण

	ret = nxp_spअगरi_setup_flash(spअगरi, flash_np);
	of_node_put(flash_np);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to setup flash chip\n");
		जाओ dis_clks;
	पूर्ण

	वापस 0;

dis_clks:
	clk_disable_unprepare(spअगरi->clk_spअगरi);
dis_clk_reg:
	clk_disable_unprepare(spअगरi->clk_reg);
	वापस ret;
पूर्ण

अटल पूर्णांक nxp_spअगरi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nxp_spअगरi *spअगरi = platक्रमm_get_drvdata(pdev);

	mtd_device_unरेजिस्टर(&spअगरi->nor.mtd);
	clk_disable_unprepare(spअगरi->clk_spअगरi);
	clk_disable_unprepare(spअगरi->clk_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id nxp_spअगरi_match[] = अणु
	अणु.compatible = "nxp,lpc1773-spifi"पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nxp_spअगरi_match);

अटल काष्ठा platक्रमm_driver nxp_spअगरi_driver = अणु
	.probe	= nxp_spअगरi_probe,
	.हटाओ	= nxp_spअगरi_हटाओ,
	.driver	= अणु
		.name = "nxp-spifi",
		.of_match_table = nxp_spअगरi_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(nxp_spअगरi_driver);

MODULE_DESCRIPTION("NXP SPI Flash Interface driver");
MODULE_AUTHOR("Joachim Eastwood <manabian@gmail.com>");
MODULE_LICENSE("GPL v2");
