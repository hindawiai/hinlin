<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ingenic JZ47xx न_अंकD driver
 *
 * Copyright (c) 2015 Imagination Technologies
 * Author: Alex Smith <alex.smith@imgtec.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <linux/jz4780-nemc.h>

#समावेश "ingenic_ecc.h"

#घोषणा DRV_NAME	"ingenic-nand"

काष्ठा jz_soc_info अणु
	अचिन्हित दीर्घ data_offset;
	अचिन्हित दीर्घ addr_offset;
	अचिन्हित दीर्घ cmd_offset;
	स्थिर काष्ठा mtd_ooblayout_ops *oob_layout;
पूर्ण;

काष्ठा ingenic_nand_cs अणु
	अचिन्हित पूर्णांक bank;
	व्योम __iomem *base;
पूर्ण;

काष्ठा ingenic_nfc अणु
	काष्ठा device *dev;
	काष्ठा ingenic_ecc *ecc;
	स्थिर काष्ठा jz_soc_info *soc_info;
	काष्ठा nand_controller controller;
	अचिन्हित पूर्णांक num_banks;
	काष्ठा list_head chips;
	काष्ठा ingenic_nand_cs cs[];
पूर्ण;

काष्ठा ingenic_nand अणु
	काष्ठा nand_chip chip;
	काष्ठा list_head chip_list;

	काष्ठा gpio_desc *busy_gpio;
	काष्ठा gpio_desc *wp_gpio;
	अचिन्हित पूर्णांक पढ़ोing: 1;
पूर्ण;

अटल अंतरभूत काष्ठा ingenic_nand *to_ingenic_nand(काष्ठा mtd_info *mtd)
अणु
	वापस container_of(mtd_to_nand(mtd), काष्ठा ingenic_nand, chip);
पूर्ण

अटल अंतरभूत काष्ठा ingenic_nfc *to_ingenic_nfc(काष्ठा nand_controller *ctrl)
अणु
	वापस container_of(ctrl, काष्ठा ingenic_nfc, controller);
पूर्ण

अटल पूर्णांक qi_lb60_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;

	अगर (section || !ecc->total)
		वापस -दुस्फल;

	oobregion->length = ecc->total;
	oobregion->offset = 12;

	वापस 0;
पूर्ण

अटल पूर्णांक qi_lb60_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;

	अगर (section)
		वापस -दुस्फल;

	oobregion->length = mtd->oobsize - ecc->total - 12;
	oobregion->offset = 12 + ecc->total;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops qi_lb60_ooblayout_ops = अणु
	.ecc = qi_lb60_ooblayout_ecc,
	.मुक्त = qi_lb60_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक jz4725b_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;

	अगर (section || !ecc->total)
		वापस -दुस्फल;

	oobregion->length = ecc->total;
	oobregion->offset = 3;

	वापस 0;
पूर्ण

अटल पूर्णांक jz4725b_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;

	अगर (section)
		वापस -दुस्फल;

	oobregion->length = mtd->oobsize - ecc->total - 3;
	oobregion->offset = 3 + ecc->total;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops jz4725b_ooblayout_ops = अणु
	.ecc = jz4725b_ooblayout_ecc,
	.मुक्त = jz4725b_ooblayout_मुक्त,
पूर्ण;

अटल व्योम ingenic_nand_ecc_hwctl(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	काष्ठा ingenic_nand *nand = to_ingenic_nand(nand_to_mtd(chip));

	nand->पढ़ोing = (mode == न_अंकD_ECC_READ);
पूर्ण

अटल पूर्णांक ingenic_nand_ecc_calculate(काष्ठा nand_chip *chip, स्थिर u8 *dat,
				      u8 *ecc_code)
अणु
	काष्ठा ingenic_nand *nand = to_ingenic_nand(nand_to_mtd(chip));
	काष्ठा ingenic_nfc *nfc = to_ingenic_nfc(nand->chip.controller);
	काष्ठा ingenic_ecc_params params;

	/*
	 * Don't need to generate the ECC when पढ़ोing, the ECC engine करोes it
	 * क्रम us as part of decoding/correction.
	 */
	अगर (nand->पढ़ोing)
		वापस 0;

	params.size = nand->chip.ecc.size;
	params.bytes = nand->chip.ecc.bytes;
	params.strength = nand->chip.ecc.strength;

	वापस ingenic_ecc_calculate(nfc->ecc, &params, dat, ecc_code);
पूर्ण

अटल पूर्णांक ingenic_nand_ecc_correct(काष्ठा nand_chip *chip, u8 *dat,
				    u8 *पढ़ो_ecc, u8 *calc_ecc)
अणु
	काष्ठा ingenic_nand *nand = to_ingenic_nand(nand_to_mtd(chip));
	काष्ठा ingenic_nfc *nfc = to_ingenic_nfc(nand->chip.controller);
	काष्ठा ingenic_ecc_params params;

	params.size = nand->chip.ecc.size;
	params.bytes = nand->chip.ecc.bytes;
	params.strength = nand->chip.ecc.strength;

	वापस ingenic_ecc_correct(nfc->ecc, &params, dat, पढ़ो_ecc);
पूर्ण

अटल पूर्णांक ingenic_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा ingenic_nfc *nfc = to_ingenic_nfc(chip->controller);
	पूर्णांक eccbytes;

	अगर (chip->ecc.strength == 4) अणु
		/* JZ4740 uses 9 bytes of ECC to correct maximum 4 errors */
		chip->ecc.bytes = 9;
	पूर्ण अन्यथा अणु
		chip->ecc.bytes = fls((1 + 8) * chip->ecc.size)	*
				  (chip->ecc.strength / 8);
	पूर्ण

	चयन (chip->ecc.engine_type) अणु
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_HOST:
		अगर (!nfc->ecc) अणु
			dev_err(nfc->dev, "HW ECC selected, but ECC controller not found\n");
			वापस -ENODEV;
		पूर्ण

		chip->ecc.hwctl = ingenic_nand_ecc_hwctl;
		chip->ecc.calculate = ingenic_nand_ecc_calculate;
		chip->ecc.correct = ingenic_nand_ecc_correct;
		fallthrough;
	हाल न_अंकD_ECC_ENGINE_TYPE_SOFT:
		dev_info(nfc->dev, "using %s (strength %d, size %d, bytes %d)\n",
			 (nfc->ecc) ? "hardware ECC" : "software ECC",
			 chip->ecc.strength, chip->ecc.size, chip->ecc.bytes);
		अवरोध;
	हाल न_अंकD_ECC_ENGINE_TYPE_NONE:
		dev_info(nfc->dev, "not using ECC\n");
		अवरोध;
	शेष:
		dev_err(nfc->dev, "ECC mode %d not supported\n",
			chip->ecc.engine_type);
		वापस -EINVAL;
	पूर्ण

	/* The न_अंकD core will generate the ECC layout क्रम SW ECC */
	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस 0;

	/* Generate ECC layout. ECC codes are right aligned in the OOB area. */
	eccbytes = mtd->ग_लिखोsize / chip->ecc.size * chip->ecc.bytes;

	अगर (eccbytes > mtd->oobsize - 2) अणु
		dev_err(nfc->dev,
			"invalid ECC config: required %d ECC bytes, but only %d are available",
			eccbytes, mtd->oobsize - 2);
		वापस -EINVAL;
	पूर्ण

	/*
	 * The generic layout क्रम BBT markers will most likely overlap with our
	 * ECC bytes in the OOB, so move the BBT markers outside the OOB area.
	 */
	अगर (chip->bbt_options & न_अंकD_BBT_USE_FLASH)
		chip->bbt_options |= न_अंकD_BBT_NO_OOB;

	/* For legacy reasons we use a dअगरferent layout on the qi,lb60 board. */
	अगर (of_machine_is_compatible("qi,lb60"))
		mtd_set_ooblayout(mtd, &qi_lb60_ooblayout_ops);
	अन्यथा अगर (nfc->soc_info->oob_layout)
		mtd_set_ooblayout(mtd, nfc->soc_info->oob_layout);
	अन्यथा
		mtd_set_ooblayout(mtd, nand_get_large_page_ooblayout());

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_nand_exec_instr(काष्ठा nand_chip *chip,
				   काष्ठा ingenic_nand_cs *cs,
				   स्थिर काष्ठा nand_op_instr *instr)
अणु
	काष्ठा ingenic_nand *nand = to_ingenic_nand(nand_to_mtd(chip));
	काष्ठा ingenic_nfc *nfc = to_ingenic_nfc(chip->controller);
	अचिन्हित पूर्णांक i;

	चयन (instr->type) अणु
	हाल न_अंकD_OP_CMD_INSTR:
		ग_लिखोb(instr->ctx.cmd.opcode,
		       cs->base + nfc->soc_info->cmd_offset);
		वापस 0;
	हाल न_अंकD_OP_ADDR_INSTR:
		क्रम (i = 0; i < instr->ctx.addr.naddrs; i++)
			ग_लिखोb(instr->ctx.addr.addrs[i],
			       cs->base + nfc->soc_info->addr_offset);
		वापस 0;
	हाल न_अंकD_OP_DATA_IN_INSTR:
		अगर (instr->ctx.data.क्रमce_8bit ||
		    !(chip->options & न_अंकD_BUSWIDTH_16))
			ioपढ़ो8_rep(cs->base + nfc->soc_info->data_offset,
				    instr->ctx.data.buf.in,
				    instr->ctx.data.len);
		अन्यथा
			ioपढ़ो16_rep(cs->base + nfc->soc_info->data_offset,
				     instr->ctx.data.buf.in,
				     instr->ctx.data.len);
		वापस 0;
	हाल न_अंकD_OP_DATA_OUT_INSTR:
		अगर (instr->ctx.data.क्रमce_8bit ||
		    !(chip->options & न_अंकD_BUSWIDTH_16))
			ioग_लिखो8_rep(cs->base + nfc->soc_info->data_offset,
				     instr->ctx.data.buf.out,
				     instr->ctx.data.len);
		अन्यथा
			ioग_लिखो16_rep(cs->base + nfc->soc_info->data_offset,
				      instr->ctx.data.buf.out,
				      instr->ctx.data.len);
		वापस 0;
	हाल न_अंकD_OP_WAITRDY_INSTR:
		अगर (!nand->busy_gpio)
			वापस nand_soft_रुकोrdy(chip,
						 instr->ctx.रुकोrdy.समयout_ms);

		वापस nand_gpio_रुकोrdy(chip, nand->busy_gpio,
					 instr->ctx.रुकोrdy.समयout_ms);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ingenic_nand_exec_op(काष्ठा nand_chip *chip,
				स्थिर काष्ठा nand_operation *op,
				bool check_only)
अणु
	काष्ठा ingenic_nand *nand = to_ingenic_nand(nand_to_mtd(chip));
	काष्ठा ingenic_nfc *nfc = to_ingenic_nfc(nand->chip.controller);
	काष्ठा ingenic_nand_cs *cs;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (check_only)
		वापस 0;

	cs = &nfc->cs[op->cs];
	jz4780_nemc_निश्चित(nfc->dev, cs->bank, true);
	क्रम (i = 0; i < op->ninstrs; i++) अणु
		ret = ingenic_nand_exec_instr(chip, cs, &op->instrs[i]);
		अगर (ret)
			अवरोध;

		अगर (op->instrs[i].delay_ns)
			ndelay(op->instrs[i].delay_ns);
	पूर्ण
	jz4780_nemc_निश्चित(nfc->dev, cs->bank, false);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops ingenic_nand_controller_ops = अणु
	.attach_chip = ingenic_nand_attach_chip,
	.exec_op = ingenic_nand_exec_op,
पूर्ण;

अटल पूर्णांक ingenic_nand_init_chip(काष्ठा platक्रमm_device *pdev,
				  काष्ठा ingenic_nfc *nfc,
				  काष्ठा device_node *np,
				  अचिन्हित पूर्णांक chipnr)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ingenic_nand *nand;
	काष्ठा ingenic_nand_cs *cs;
	काष्ठा nand_chip *chip;
	काष्ठा mtd_info *mtd;
	स्थिर __be32 *reg;
	पूर्णांक ret = 0;

	cs = &nfc->cs[chipnr];

	reg = of_get_property(np, "reg", शून्य);
	अगर (!reg)
		वापस -EINVAL;

	cs->bank = be32_to_cpu(*reg);

	jz4780_nemc_set_type(nfc->dev, cs->bank, JZ4780_NEMC_BANK_न_अंकD);

	cs->base = devm_platक्रमm_ioremap_resource(pdev, chipnr);
	अगर (IS_ERR(cs->base))
		वापस PTR_ERR(cs->base);

	nand = devm_kzalloc(dev, माप(*nand), GFP_KERNEL);
	अगर (!nand)
		वापस -ENOMEM;

	nand->busy_gpio = devm_gpiod_get_optional(dev, "rb", GPIOD_IN);

	अगर (IS_ERR(nand->busy_gpio)) अणु
		ret = PTR_ERR(nand->busy_gpio);
		dev_err(dev, "failed to request busy GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * The rb-gpios semantics was unकरोcumented and qi,lb60 (aदीर्घ with
	 * the ingenic driver) got it wrong. The active state encodes the
	 * न_अंकD पढ़ोy state, which is high level. Since there's no संकेत
	 * inverter on this board, it should be active-high. Let's fix that
	 * here क्रम older DTs so we can re-use the generic nand_gpio_रुकोrdy()
	 * helper, and be consistent with what other drivers करो.
	 */
	अगर (of_machine_is_compatible("qi,lb60") &&
	    gpiod_is_active_low(nand->busy_gpio))
		gpiod_toggle_active_low(nand->busy_gpio);

	nand->wp_gpio = devm_gpiod_get_optional(dev, "wp", GPIOD_OUT_LOW);

	अगर (IS_ERR(nand->wp_gpio)) अणु
		ret = PTR_ERR(nand->wp_gpio);
		dev_err(dev, "failed to request WP GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	chip = &nand->chip;
	mtd = nand_to_mtd(chip);
	mtd->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s.%d", dev_name(dev),
				   cs->bank);
	अगर (!mtd->name)
		वापस -ENOMEM;
	mtd->dev.parent = dev;

	chip->options = न_अंकD_NO_SUBPAGE_WRITE;
	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
	chip->controller = &nfc->controller;
	nand_set_flash_node(chip, np);

	chip->controller->ops = &ingenic_nand_controller_ops;
	ret = nand_scan(chip, 1);
	अगर (ret)
		वापस ret;

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret) अणु
		nand_cleanup(chip);
		वापस ret;
	पूर्ण

	list_add_tail(&nand->chip_list, &nfc->chips);

	वापस 0;
पूर्ण

अटल व्योम ingenic_nand_cleanup_chips(काष्ठा ingenic_nfc *nfc)
अणु
	काष्ठा ingenic_nand *ingenic_chip;
	काष्ठा nand_chip *chip;
	पूर्णांक ret;

	जबतक (!list_empty(&nfc->chips)) अणु
		ingenic_chip = list_first_entry(&nfc->chips,
						काष्ठा ingenic_nand, chip_list);
		chip = &ingenic_chip->chip;
		ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
		WARN_ON(ret);
		nand_cleanup(chip);
		list_del(&ingenic_chip->chip_list);
	पूर्ण
पूर्ण

अटल पूर्णांक ingenic_nand_init_chips(काष्ठा ingenic_nfc *nfc,
				   काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np;
	पूर्णांक i = 0;
	पूर्णांक ret;
	पूर्णांक num_chips = of_get_child_count(dev->of_node);

	अगर (num_chips > nfc->num_banks) अणु
		dev_err(dev, "found %d chips but only %d banks\n",
			num_chips, nfc->num_banks);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_child_of_node(dev->of_node, np) अणु
		ret = ingenic_nand_init_chip(pdev, nfc, np, i);
		अगर (ret) अणु
			ingenic_nand_cleanup_chips(nfc);
			of_node_put(np);
			वापस ret;
		पूर्ण

		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	अचिन्हित पूर्णांक num_banks;
	काष्ठा ingenic_nfc *nfc;
	पूर्णांक ret;

	num_banks = jz4780_nemc_num_banks(dev);
	अगर (num_banks == 0) अणु
		dev_err(dev, "no banks found\n");
		वापस -ENODEV;
	पूर्ण

	nfc = devm_kzalloc(dev, काष्ठा_size(nfc, cs, num_banks), GFP_KERNEL);
	अगर (!nfc)
		वापस -ENOMEM;

	nfc->soc_info = device_get_match_data(dev);
	अगर (!nfc->soc_info)
		वापस -EINVAL;

	/*
	 * Check क्रम ECC HW beक्रमe we call nand_scan_ident, to prevent us from
	 * having to call it again अगर the ECC driver वापसs -EPROBE_DEFER.
	 */
	nfc->ecc = of_ingenic_ecc_get(dev->of_node);
	अगर (IS_ERR(nfc->ecc))
		वापस PTR_ERR(nfc->ecc);

	nfc->dev = dev;
	nfc->num_banks = num_banks;

	nand_controller_init(&nfc->controller);
	INIT_LIST_HEAD(&nfc->chips);

	ret = ingenic_nand_init_chips(nfc, pdev);
	अगर (ret) अणु
		अगर (nfc->ecc)
			ingenic_ecc_release(nfc->ecc);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, nfc);
	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ingenic_nfc *nfc = platक्रमm_get_drvdata(pdev);

	अगर (nfc->ecc)
		ingenic_ecc_release(nfc->ecc);

	ingenic_nand_cleanup_chips(nfc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा jz_soc_info jz4740_soc_info = अणु
	.data_offset = 0x00000000,
	.cmd_offset = 0x00008000,
	.addr_offset = 0x00010000,
पूर्ण;

अटल स्थिर काष्ठा jz_soc_info jz4725b_soc_info = अणु
	.data_offset = 0x00000000,
	.cmd_offset = 0x00008000,
	.addr_offset = 0x00010000,
	.oob_layout = &jz4725b_ooblayout_ops,
पूर्ण;

अटल स्थिर काष्ठा jz_soc_info jz4780_soc_info = अणु
	.data_offset = 0x00000000,
	.cmd_offset = 0x00400000,
	.addr_offset = 0x00800000,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ingenic_nand_dt_match[] = अणु
	अणु .compatible = "ingenic,jz4740-nand", .data = &jz4740_soc_info पूर्ण,
	अणु .compatible = "ingenic,jz4725b-nand", .data = &jz4725b_soc_info पूर्ण,
	अणु .compatible = "ingenic,jz4780-nand", .data = &jz4780_soc_info पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ingenic_nand_dt_match);

अटल काष्ठा platक्रमm_driver ingenic_nand_driver = अणु
	.probe		= ingenic_nand_probe,
	.हटाओ		= ingenic_nand_हटाओ,
	.driver	= अणु
		.name	= DRV_NAME,
		.of_match_table = of_match_ptr(ingenic_nand_dt_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ingenic_nand_driver);

MODULE_AUTHOR("Alex Smith <alex@alex-smith.me.uk>");
MODULE_AUTHOR("Harvey Hunt <harveyhuntnexus@gmail.com>");
MODULE_DESCRIPTION("Ingenic JZ47xx NAND driver");
MODULE_LICENSE("GPL v2");
