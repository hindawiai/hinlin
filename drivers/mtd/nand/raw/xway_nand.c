<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright तऊ 2012 John Crispin <john@phrozen.org>
 *  Copyright तऊ 2016 Hauke Mehrtens <hauke@hauke-m.de>
 */

#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_platक्रमm.h>

#समावेश <lantiq_soc.h>

/* nand रेजिस्टरs */
#घोषणा EBU_ADDSEL1		0x24
#घोषणा EBU_न_अंकD_CON		0xB0
#घोषणा EBU_न_अंकD_WAIT		0xB4
#घोषणा  न_अंकD_WAIT_RD		BIT(0) /* न_अंकD flash status output */
#घोषणा  न_अंकD_WAIT_WR_C		BIT(3) /* न_अंकD Write/Read complete */
#घोषणा EBU_न_अंकD_ECC0		0xB8
#घोषणा EBU_न_अंकD_ECC_AC		0xBC

/*
 * nand commands
 * The pins of the न_अंकD chip are selected based on the address bits of the
 * "register" पढ़ो and ग_लिखो. There are no special रेजिस्टरs, but an
 * address range and the lower address bits are used to activate the
 * correct line. For example when the bit (1 << 2) is set in the address
 * the ALE pin will be activated.
 */
#घोषणा न_अंकD_CMD_ALE		BIT(2) /* address latch enable */
#घोषणा न_अंकD_CMD_CLE		BIT(3) /* command latch enable */
#घोषणा न_अंकD_CMD_CS		BIT(4) /* chip select */
#घोषणा न_अंकD_CMD_SE		BIT(5) /* spare area access latch */
#घोषणा न_अंकD_CMD_WP		BIT(6) /* ग_लिखो protect */
#घोषणा न_अंकD_WRITE_CMD		(न_अंकD_CMD_CS | न_अंकD_CMD_CLE)
#घोषणा न_अंकD_WRITE_ADDR		(न_अंकD_CMD_CS | न_अंकD_CMD_ALE)
#घोषणा न_अंकD_WRITE_DATA		(न_अंकD_CMD_CS)
#घोषणा न_अंकD_READ_DATA		(न_अंकD_CMD_CS)

/* we need to tel the ebu which addr we mapped the nand to */
#घोषणा ADDSEL1_MASK(x)		(x << 4)
#घोषणा ADDSEL1_REGEN		1

/* we need to tell the EBU that we have nand attached and set it up properly */
#घोषणा BUSCON1_SETUP		(1 << 22)
#घोषणा BUSCON1_BCGEN_RES	(0x3 << 12)
#घोषणा BUSCON1_WAITWRC2	(2 << 8)
#घोषणा BUSCON1_WAITRDC2	(2 << 6)
#घोषणा BUSCON1_HOLDC1		(1 << 4)
#घोषणा BUSCON1_RECOVC1		(1 << 2)
#घोषणा BUSCON1_CMULT4		1

#घोषणा न_अंकD_CON_CE		(1 << 20)
#घोषणा न_अंकD_CON_OUT_CS1	(1 << 10)
#घोषणा न_अंकD_CON_IN_CS1		(1 << 8)
#घोषणा न_अंकD_CON_PRE_P		(1 << 7)
#घोषणा न_अंकD_CON_WP_P		(1 << 6)
#घोषणा न_अंकD_CON_SE_P		(1 << 5)
#घोषणा न_अंकD_CON_CS_P		(1 << 4)
#घोषणा न_अंकD_CON_CSMUX		(1 << 1)
#घोषणा न_अंकD_CON_न_अंकDM		1

काष्ठा xway_nand_data अणु
	काष्ठा nand_controller	controller;
	काष्ठा nand_chip	chip;
	अचिन्हित दीर्घ		csflags;
	व्योम __iomem		*nandaddr;
पूर्ण;

अटल u8 xway_पढ़ोb(काष्ठा mtd_info *mtd, पूर्णांक op)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा xway_nand_data *data = nand_get_controller_data(chip);

	वापस पढ़ोb(data->nandaddr + op);
पूर्ण

अटल व्योम xway_ग_लिखोb(काष्ठा mtd_info *mtd, पूर्णांक op, u8 value)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा xway_nand_data *data = nand_get_controller_data(chip);

	ग_लिखोb(value, data->nandaddr + op);
पूर्ण

अटल व्योम xway_select_chip(काष्ठा nand_chip *chip, पूर्णांक select)
अणु
	काष्ठा xway_nand_data *data = nand_get_controller_data(chip);

	चयन (select) अणु
	हाल -1:
		ltq_ebu_w32_mask(न_अंकD_CON_CE, 0, EBU_न_अंकD_CON);
		ltq_ebu_w32_mask(न_अंकD_CON_न_अंकDM, 0, EBU_न_अंकD_CON);
		spin_unlock_irqrestore(&ebu_lock, data->csflags);
		अवरोध;
	हाल 0:
		spin_lock_irqsave(&ebu_lock, data->csflags);
		ltq_ebu_w32_mask(0, न_अंकD_CON_न_अंकDM, EBU_न_अंकD_CON);
		ltq_ebu_w32_mask(0, न_अंकD_CON_CE, EBU_न_अंकD_CON);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम xway_cmd_ctrl(काष्ठा nand_chip *chip, पूर्णांक cmd, अचिन्हित पूर्णांक ctrl)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	अगर (cmd == न_अंकD_CMD_NONE)
		वापस;

	अगर (ctrl & न_अंकD_CLE)
		xway_ग_लिखोb(mtd, न_अंकD_WRITE_CMD, cmd);
	अन्यथा अगर (ctrl & न_अंकD_ALE)
		xway_ग_लिखोb(mtd, न_अंकD_WRITE_ADDR, cmd);

	जबतक ((ltq_ebu_r32(EBU_न_अंकD_WAIT) & न_अंकD_WAIT_WR_C) == 0)
		;
पूर्ण

अटल पूर्णांक xway_dev_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	वापस ltq_ebu_r32(EBU_न_अंकD_WAIT) & न_अंकD_WAIT_RD;
पूर्ण

अटल अचिन्हित अक्षर xway_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	वापस xway_पढ़ोb(nand_to_mtd(chip), न_अंकD_READ_DATA);
पूर्ण

अटल व्योम xway_पढ़ो_buf(काष्ठा nand_chip *chip, u_अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		buf[i] = xway_पढ़ोb(nand_to_mtd(chip), न_अंकD_WRITE_DATA);
पूर्ण

अटल व्योम xway_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर u_अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		xway_ग_लिखोb(nand_to_mtd(chip), न_अंकD_WRITE_DATA, buf[i]);
पूर्ण

अटल पूर्णांक xway_attach_chip(काष्ठा nand_chip *chip)
अणु
	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;

	अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_UNKNOWN)
		chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops xway_nand_ops = अणु
	.attach_chip = xway_attach_chip,
पूर्ण;

/*
 * Probe क्रम the न_अंकD device.
 */
अटल पूर्णांक xway_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xway_nand_data *data;
	काष्ठा mtd_info *mtd;
	काष्ठा resource *res;
	पूर्णांक err;
	u32 cs;
	u32 cs_flag = 0;

	/* Allocate memory क्रम the device काष्ठाure (and zero it) */
	data = devm_kzalloc(&pdev->dev, माप(काष्ठा xway_nand_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	data->nandaddr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(data->nandaddr))
		वापस PTR_ERR(data->nandaddr);

	nand_set_flash_node(&data->chip, pdev->dev.of_node);
	mtd = nand_to_mtd(&data->chip);
	mtd->dev.parent = &pdev->dev;

	data->chip.legacy.cmd_ctrl = xway_cmd_ctrl;
	data->chip.legacy.dev_पढ़ोy = xway_dev_पढ़ोy;
	data->chip.legacy.select_chip = xway_select_chip;
	data->chip.legacy.ग_लिखो_buf = xway_ग_लिखो_buf;
	data->chip.legacy.पढ़ो_buf = xway_पढ़ो_buf;
	data->chip.legacy.पढ़ो_byte = xway_पढ़ो_byte;
	data->chip.legacy.chip_delay = 30;

	nand_controller_init(&data->controller);
	data->controller.ops = &xway_nand_ops;
	data->chip.controller = &data->controller;

	platक्रमm_set_drvdata(pdev, data);
	nand_set_controller_data(&data->chip, data);

	/* load our CS from the DT. Either we find a valid 1 or शेष to 0 */
	err = of_property_पढ़ो_u32(pdev->dev.of_node, "lantiq,cs", &cs);
	अगर (!err && cs == 1)
		cs_flag = न_अंकD_CON_IN_CS1 | न_अंकD_CON_OUT_CS1;

	/* setup the EBU to run in न_अंकD mode on our base addr */
	ltq_ebu_w32(CPHYSADDR(data->nandaddr)
		    | ADDSEL1_MASK(3) | ADDSEL1_REGEN, EBU_ADDSEL1);

	ltq_ebu_w32(BUSCON1_SETUP | BUSCON1_BCGEN_RES | BUSCON1_WAITWRC2
		    | BUSCON1_WAITRDC2 | BUSCON1_HOLDC1 | BUSCON1_RECOVC1
		    | BUSCON1_CMULT4, LTQ_EBU_BUSCON1);

	ltq_ebu_w32(न_अंकD_CON_न_अंकDM | न_अंकD_CON_CSMUX | न_अंकD_CON_CS_P
		    | न_अंकD_CON_SE_P | न_अंकD_CON_WP_P | न_अंकD_CON_PRE_P
		    | cs_flag, EBU_न_अंकD_CON);

	/* Scan to find existence of the device */
	err = nand_scan(&data->chip, 1);
	अगर (err)
		वापस err;

	err = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (err)
		nand_cleanup(&data->chip);

	वापस err;
पूर्ण

/*
 * Remove a न_अंकD device.
 */
अटल पूर्णांक xway_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xway_nand_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = &data->chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xway_nand_match[] = अणु
	अणु .compatible = "lantiq,nand-xway" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver xway_nand_driver = अणु
	.probe	= xway_nand_probe,
	.हटाओ	= xway_nand_हटाओ,
	.driver	= अणु
		.name		= "lantiq,nand-xway",
		.of_match_table = xway_nand_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(xway_nand_driver);
