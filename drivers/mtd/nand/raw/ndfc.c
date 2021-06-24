<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Overview:
 *   Platक्रमm independent driver क्रम NDFC (NanD Flash Controller)
 *   पूर्णांकegrated पूर्णांकo EP440 cores
 *
 *   Ported to an OF platक्रमm driver by Sean MacLennan
 *
 *   The NDFC supports multiple chips, but this driver only supports a
 *   single chip since I करो not have access to any boards with
 *   multiple chips.
 *
 *  Author: Thomas Gleixner
 *
 *  Copyright 2006 IBM
 *  Copyright 2008 PIKA Technologies
 *    Sean MacLennan <smaclennan@pikatech.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/ndfc.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/पन.स>

#घोषणा NDFC_MAX_CS    4

काष्ठा ndfc_controller अणु
	काष्ठा platक्रमm_device *ofdev;
	व्योम __iomem *ndfcbase;
	काष्ठा nand_chip chip;
	पूर्णांक chip_select;
	काष्ठा nand_controller ndfc_control;
पूर्ण;

अटल काष्ठा ndfc_controller ndfc_ctrl[NDFC_MAX_CS];

अटल व्योम ndfc_select_chip(काष्ठा nand_chip *nchip, पूर्णांक chip)
अणु
	uपूर्णांक32_t ccr;
	काष्ठा ndfc_controller *ndfc = nand_get_controller_data(nchip);

	ccr = in_be32(ndfc->ndfcbase + NDFC_CCR);
	अगर (chip >= 0) अणु
		ccr &= ~NDFC_CCR_BS_MASK;
		ccr |= NDFC_CCR_BS(chip + ndfc->chip_select);
	पूर्ण अन्यथा
		ccr |= NDFC_CCR_RESET_CE;
	out_be32(ndfc->ndfcbase + NDFC_CCR, ccr);
पूर्ण

अटल व्योम ndfc_hwcontrol(काष्ठा nand_chip *chip, पूर्णांक cmd, अचिन्हित पूर्णांक ctrl)
अणु
	काष्ठा ndfc_controller *ndfc = nand_get_controller_data(chip);

	अगर (cmd == न_अंकD_CMD_NONE)
		वापस;

	अगर (ctrl & न_अंकD_CLE)
		ग_लिखोl(cmd & 0xFF, ndfc->ndfcbase + NDFC_CMD);
	अन्यथा
		ग_लिखोl(cmd & 0xFF, ndfc->ndfcbase + NDFC_ALE);
पूर्ण

अटल पूर्णांक ndfc_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	काष्ठा ndfc_controller *ndfc = nand_get_controller_data(chip);

	वापस in_be32(ndfc->ndfcbase + NDFC_STAT) & NDFC_STAT_IS_READY;
पूर्ण

अटल व्योम ndfc_enable_hwecc(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	uपूर्णांक32_t ccr;
	काष्ठा ndfc_controller *ndfc = nand_get_controller_data(chip);

	ccr = in_be32(ndfc->ndfcbase + NDFC_CCR);
	ccr |= NDFC_CCR_RESET_ECC;
	out_be32(ndfc->ndfcbase + NDFC_CCR, ccr);
	wmb();
पूर्ण

अटल पूर्णांक ndfc_calculate_ecc(काष्ठा nand_chip *chip,
			      स्थिर u_अक्षर *dat, u_अक्षर *ecc_code)
अणु
	काष्ठा ndfc_controller *ndfc = nand_get_controller_data(chip);
	uपूर्णांक32_t ecc;
	uपूर्णांक8_t *p = (uपूर्णांक8_t *)&ecc;

	wmb();
	ecc = in_be32(ndfc->ndfcbase + NDFC_ECC);
	/* The NDFC uses Smart Media (SMC) bytes order */
	ecc_code[0] = p[1];
	ecc_code[1] = p[2];
	ecc_code[2] = p[3];

	वापस 0;
पूर्ण

अटल पूर्णांक ndfc_correct_ecc(काष्ठा nand_chip *chip,
			    अचिन्हित अक्षर *buf,
			    अचिन्हित अक्षर *पढ़ो_ecc,
			    अचिन्हित अक्षर *calc_ecc)
अणु
	वापस ecc_sw_hamming_correct(buf, पढ़ो_ecc, calc_ecc,
				      chip->ecc.size, false);
पूर्ण

/*
 * Speedups क्रम buffer पढ़ो/ग_लिखो/verअगरy
 *
 * NDFC allows 32bit पढ़ो/ग_लिखो of data. So we can speed up the buffer
 * functions. No further checking, as nand_base will always पढ़ो/ग_लिखो
 * page aligned.
 */
अटल व्योम ndfc_पढ़ो_buf(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	काष्ठा ndfc_controller *ndfc = nand_get_controller_data(chip);
	uपूर्णांक32_t *p = (uपूर्णांक32_t *) buf;

	क्रम(;len > 0; len -= 4)
		*p++ = in_be32(ndfc->ndfcbase + NDFC_DATA);
पूर्ण

अटल व्योम ndfc_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	काष्ठा ndfc_controller *ndfc = nand_get_controller_data(chip);
	uपूर्णांक32_t *p = (uपूर्णांक32_t *) buf;

	क्रम(;len > 0; len -= 4)
		out_be32(ndfc->ndfcbase + NDFC_DATA, *p++);
पूर्ण

/*
 * Initialize chip काष्ठाure
 */
अटल पूर्णांक ndfc_chip_init(काष्ठा ndfc_controller *ndfc,
			  काष्ठा device_node *node)
अणु
	काष्ठा device_node *flash_np;
	काष्ठा nand_chip *chip = &ndfc->chip;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	chip->legacy.IO_ADDR_R = ndfc->ndfcbase + NDFC_DATA;
	chip->legacy.IO_ADDR_W = ndfc->ndfcbase + NDFC_DATA;
	chip->legacy.cmd_ctrl = ndfc_hwcontrol;
	chip->legacy.dev_पढ़ोy = ndfc_पढ़ोy;
	chip->legacy.select_chip = ndfc_select_chip;
	chip->legacy.chip_delay = 50;
	chip->controller = &ndfc->ndfc_control;
	chip->legacy.पढ़ो_buf = ndfc_पढ़ो_buf;
	chip->legacy.ग_लिखो_buf = ndfc_ग_लिखो_buf;
	chip->ecc.correct = ndfc_correct_ecc;
	chip->ecc.hwctl = ndfc_enable_hwecc;
	chip->ecc.calculate = ndfc_calculate_ecc;
	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
	chip->ecc.size = 256;
	chip->ecc.bytes = 3;
	chip->ecc.strength = 1;
	nand_set_controller_data(chip, ndfc);

	mtd->dev.parent = &ndfc->ofdev->dev;

	flash_np = of_get_next_child(node, शून्य);
	अगर (!flash_np)
		वापस -ENODEV;
	nand_set_flash_node(chip, flash_np);

	mtd->name = kaप्र_लिखो(GFP_KERNEL, "%s.%pOFn", dev_name(&ndfc->ofdev->dev),
			      flash_np);
	अगर (!mtd->name) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = nand_scan(chip, 1);
	अगर (ret)
		जाओ err;

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);

err:
	of_node_put(flash_np);
	अगर (ret)
		kमुक्त(mtd->name);
	वापस ret;
पूर्ण

अटल पूर्णांक ndfc_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा ndfc_controller *ndfc;
	स्थिर __be32 *reg;
	u32 ccr;
	u32 cs;
	पूर्णांक err, len;

	/* Read the reg property to get the chip select */
	reg = of_get_property(ofdev->dev.of_node, "reg", &len);
	अगर (reg == शून्य || len != 12) अणु
		dev_err(&ofdev->dev, "unable read reg property (%d)\n", len);
		वापस -ENOENT;
	पूर्ण

	cs = be32_to_cpu(reg[0]);
	अगर (cs >= NDFC_MAX_CS) अणु
		dev_err(&ofdev->dev, "invalid CS number (%d)\n", cs);
		वापस -EINVAL;
	पूर्ण

	ndfc = &ndfc_ctrl[cs];
	ndfc->chip_select = cs;

	nand_controller_init(&ndfc->ndfc_control);
	ndfc->ofdev = ofdev;
	dev_set_drvdata(&ofdev->dev, ndfc);

	ndfc->ndfcbase = of_iomap(ofdev->dev.of_node, 0);
	अगर (!ndfc->ndfcbase) अणु
		dev_err(&ofdev->dev, "failed to get memory\n");
		वापस -EIO;
	पूर्ण

	ccr = NDFC_CCR_BS(ndfc->chip_select);

	/* It is ok अगर ccr करोes not exist - just शेष to 0 */
	reg = of_get_property(ofdev->dev.of_node, "ccr", शून्य);
	अगर (reg)
		ccr |= be32_to_cpup(reg);

	out_be32(ndfc->ndfcbase + NDFC_CCR, ccr);

	/* Set the bank settings अगर given */
	reg = of_get_property(ofdev->dev.of_node, "bank-settings", शून्य);
	अगर (reg) अणु
		पूर्णांक offset = NDFC_BCFG0 + (ndfc->chip_select << 2);
		out_be32(ndfc->ndfcbase + offset, be32_to_cpup(reg));
	पूर्ण

	err = ndfc_chip_init(ndfc, ofdev->dev.of_node);
	अगर (err) अणु
		iounmap(ndfc->ndfcbase);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ndfc_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा ndfc_controller *ndfc = dev_get_drvdata(&ofdev->dev);
	काष्ठा nand_chip *chip = &ndfc->chip;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(mtd);
	WARN_ON(ret);
	nand_cleanup(chip);
	kमुक्त(mtd->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ndfc_match[] = अणु
	अणु .compatible = "ibm,ndfc", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ndfc_match);

अटल काष्ठा platक्रमm_driver ndfc_driver = अणु
	.driver = अणु
		.name = "ndfc",
		.of_match_table = ndfc_match,
	पूर्ण,
	.probe = ndfc_probe,
	.हटाओ = ndfc_हटाओ,
पूर्ण;

module_platक्रमm_driver(ndfc_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Thomas Gleixner <tglx@linutronix.de>");
MODULE_DESCRIPTION("OF Platform driver for NDFC");
