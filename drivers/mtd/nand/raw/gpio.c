<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Updated, and converted to generic GPIO based driver by Russell King.
 *
 * Written by Ben Dooks <ben@simtec.co.uk>
 *   Based on 2.4 version by Mark Whittaker
 *
 * तऊ 2004 Simtec Electronics
 *
 * Device driver क्रम न_अंकD flash that uses a memory mapped पूर्णांकerface to
 * पढ़ो/ग_लिखो the न_अंकD commands and data, and GPIO pins क्रम control संकेतs
 * (the DT binding refers to this as "GPIO assisted NAND flash")
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/nand-gpपन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/delay.h>

काष्ठा gpiomtd अणु
	काष्ठा nand_controller	base;
	व्योम __iomem		*io;
	व्योम __iomem		*io_sync;
	काष्ठा nand_chip	nand_chip;
	काष्ठा gpio_nand_platdata plat;
	काष्ठा gpio_desc *nce; /* Optional chip enable */
	काष्ठा gpio_desc *cle;
	काष्ठा gpio_desc *ale;
	काष्ठा gpio_desc *rdy;
	काष्ठा gpio_desc *nwp; /* Optional ग_लिखो protection */
पूर्ण;

अटल अंतरभूत काष्ठा gpiomtd *gpio_nand_getpriv(काष्ठा mtd_info *mtd)
अणु
	वापस container_of(mtd_to_nand(mtd), काष्ठा gpiomtd, nand_chip);
पूर्ण


#अगर_घोषित CONFIG_ARM
/* gpio_nand_करोsync()
 *
 * Make sure the GPIO state changes occur in-order with ग_लिखोs to न_अंकD
 * memory region.
 * Needed on PXA due to bus-reordering within the SoC itself (see section on
 * I/O ordering in PXA manual (section 2.3, p35)
 */
अटल व्योम gpio_nand_करोsync(काष्ठा gpiomtd *gpiomtd)
अणु
	अचिन्हित दीर्घ पंचांगp;

	अगर (gpiomtd->io_sync) अणु
		/*
		 * Linux memory barriers करोn't cater for what's required here.
		 * What's required is what's here - a पढ़ो from a separate
		 * region with a dependency on that पढ़ो.
		 */
		पंचांगp = पढ़ोl(gpiomtd->io_sync);
		यंत्र अस्थिर("mov %1, %0\n" : "=r" (पंचांगp) : "r" (पंचांगp));
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम gpio_nand_करोsync(काष्ठा gpiomtd *gpiomtd) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक gpio_nand_exec_instr(काष्ठा nand_chip *chip,
				स्थिर काष्ठा nand_op_instr *instr)
अणु
	काष्ठा gpiomtd *gpiomtd = gpio_nand_getpriv(nand_to_mtd(chip));
	अचिन्हित पूर्णांक i;

	चयन (instr->type) अणु
	हाल न_अंकD_OP_CMD_INSTR:
		gpio_nand_करोsync(gpiomtd);
		gpiod_set_value(gpiomtd->cle, 1);
		gpio_nand_करोsync(gpiomtd);
		ग_लिखोb(instr->ctx.cmd.opcode, gpiomtd->io);
		gpio_nand_करोsync(gpiomtd);
		gpiod_set_value(gpiomtd->cle, 0);
		वापस 0;

	हाल न_अंकD_OP_ADDR_INSTR:
		gpio_nand_करोsync(gpiomtd);
		gpiod_set_value(gpiomtd->ale, 1);
		gpio_nand_करोsync(gpiomtd);
		क्रम (i = 0; i < instr->ctx.addr.naddrs; i++)
			ग_लिखोb(instr->ctx.addr.addrs[i], gpiomtd->io);
		gpio_nand_करोsync(gpiomtd);
		gpiod_set_value(gpiomtd->ale, 0);
		वापस 0;

	हाल न_अंकD_OP_DATA_IN_INSTR:
		gpio_nand_करोsync(gpiomtd);
		अगर ((chip->options & न_अंकD_BUSWIDTH_16) &&
		    !instr->ctx.data.क्रमce_8bit)
			ioपढ़ो16_rep(gpiomtd->io, instr->ctx.data.buf.in,
				     instr->ctx.data.len / 2);
		अन्यथा
			ioपढ़ो8_rep(gpiomtd->io, instr->ctx.data.buf.in,
				    instr->ctx.data.len);
		वापस 0;

	हाल न_अंकD_OP_DATA_OUT_INSTR:
		gpio_nand_करोsync(gpiomtd);
		अगर ((chip->options & न_अंकD_BUSWIDTH_16) &&
		    !instr->ctx.data.क्रमce_8bit)
			ioग_लिखो16_rep(gpiomtd->io, instr->ctx.data.buf.out,
				      instr->ctx.data.len / 2);
		अन्यथा
			ioग_लिखो8_rep(gpiomtd->io, instr->ctx.data.buf.out,
				     instr->ctx.data.len);
		वापस 0;

	हाल न_अंकD_OP_WAITRDY_INSTR:
		अगर (!gpiomtd->rdy)
			वापस nand_soft_रुकोrdy(chip, instr->ctx.रुकोrdy.समयout_ms);

		वापस nand_gpio_रुकोrdy(chip, gpiomtd->rdy,
					 instr->ctx.रुकोrdy.समयout_ms);

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_nand_exec_op(काष्ठा nand_chip *chip,
			     स्थिर काष्ठा nand_operation *op,
			     bool check_only)
अणु
	काष्ठा gpiomtd *gpiomtd = gpio_nand_getpriv(nand_to_mtd(chip));
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (check_only)
		वापस 0;

	gpio_nand_करोsync(gpiomtd);
	gpiod_set_value(gpiomtd->nce, 0);
	क्रम (i = 0; i < op->ninstrs; i++) अणु
		ret = gpio_nand_exec_instr(chip, &op->instrs[i]);
		अगर (ret)
			अवरोध;

		अगर (op->instrs[i].delay_ns)
			ndelay(op->instrs[i].delay_ns);
	पूर्ण
	gpio_nand_करोsync(gpiomtd);
	gpiod_set_value(gpiomtd->nce, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक gpio_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;

	अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_UNKNOWN)
		chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops gpio_nand_ops = अणु
	.exec_op = gpio_nand_exec_op,
	.attach_chip = gpio_nand_attach_chip,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id gpio_nand_id_table[] = अणु
	अणु .compatible = "gpio-control-nand" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_nand_id_table);

अटल पूर्णांक gpio_nand_get_config_of(स्थिर काष्ठा device *dev,
				   काष्ठा gpio_nand_platdata *plat)
अणु
	u32 val;

	अगर (!dev->of_node)
		वापस -ENODEV;

	अगर (!of_property_पढ़ो_u32(dev->of_node, "bank-width", &val)) अणु
		अगर (val == 2) अणु
			plat->options |= न_अंकD_BUSWIDTH_16;
		पूर्ण अन्यथा अगर (val != 1) अणु
			dev_err(dev, "invalid bank-width %u\n", val);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!of_property_पढ़ो_u32(dev->of_node, "chip-delay", &val))
		plat->chip_delay = val;

	वापस 0;
पूर्ण

अटल काष्ठा resource *gpio_nand_get_io_sync_of(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *r;
	u64 addr;

	अगर (of_property_पढ़ो_u64(pdev->dev.of_node,
				       "gpio-control-nand,io-sync-reg", &addr))
		वापस शून्य;

	r = devm_kzalloc(&pdev->dev, माप(*r), GFP_KERNEL);
	अगर (!r)
		वापस शून्य;

	r->start = addr;
	r->end = r->start + 0x3;
	r->flags = IORESOURCE_MEM;

	वापस r;
पूर्ण
#अन्यथा /* CONFIG_OF */
अटल अंतरभूत पूर्णांक gpio_nand_get_config_of(स्थिर काष्ठा device *dev,
					  काष्ठा gpio_nand_platdata *plat)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत काष्ठा resource *
gpio_nand_get_io_sync_of(काष्ठा platक्रमm_device *pdev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल अंतरभूत पूर्णांक gpio_nand_get_config(स्थिर काष्ठा device *dev,
				       काष्ठा gpio_nand_platdata *plat)
अणु
	पूर्णांक ret = gpio_nand_get_config_of(dev, plat);

	अगर (!ret)
		वापस ret;

	अगर (dev_get_platdata(dev)) अणु
		स_नकल(plat, dev_get_platdata(dev), माप(*plat));
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत काष्ठा resource *
gpio_nand_get_io_sync(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *r = gpio_nand_get_io_sync_of(pdev);

	अगर (r)
		वापस r;

	वापस platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
पूर्ण

अटल पूर्णांक gpio_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpiomtd *gpiomtd = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = &gpiomtd->nand_chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);

	/* Enable ग_लिखो protection and disable the chip */
	अगर (gpiomtd->nwp && !IS_ERR(gpiomtd->nwp))
		gpiod_set_value(gpiomtd->nwp, 0);
	अगर (gpiomtd->nce && !IS_ERR(gpiomtd->nce))
		gpiod_set_value(gpiomtd->nce, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpiomtd *gpiomtd;
	काष्ठा nand_chip *chip;
	काष्ठा mtd_info *mtd;
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret = 0;

	अगर (!dev->of_node && !dev_get_platdata(dev))
		वापस -EINVAL;

	gpiomtd = devm_kzalloc(dev, माप(*gpiomtd), GFP_KERNEL);
	अगर (!gpiomtd)
		वापस -ENOMEM;

	chip = &gpiomtd->nand_chip;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	gpiomtd->io = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(gpiomtd->io))
		वापस PTR_ERR(gpiomtd->io);

	res = gpio_nand_get_io_sync(pdev);
	अगर (res) अणु
		gpiomtd->io_sync = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(gpiomtd->io_sync))
			वापस PTR_ERR(gpiomtd->io_sync);
	पूर्ण

	ret = gpio_nand_get_config(dev, &gpiomtd->plat);
	अगर (ret)
		वापस ret;

	/* Just enable the chip */
	gpiomtd->nce = devm_gpiod_get_optional(dev, "nce", GPIOD_OUT_HIGH);
	अगर (IS_ERR(gpiomtd->nce))
		वापस PTR_ERR(gpiomtd->nce);

	/* We disable ग_लिखो protection once we know probe() will succeed */
	gpiomtd->nwp = devm_gpiod_get_optional(dev, "nwp", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpiomtd->nwp)) अणु
		ret = PTR_ERR(gpiomtd->nwp);
		जाओ out_ce;
	पूर्ण

	gpiomtd->ale = devm_gpiod_get(dev, "ale", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpiomtd->ale)) अणु
		ret = PTR_ERR(gpiomtd->ale);
		जाओ out_ce;
	पूर्ण

	gpiomtd->cle = devm_gpiod_get(dev, "cle", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpiomtd->cle)) अणु
		ret = PTR_ERR(gpiomtd->cle);
		जाओ out_ce;
	पूर्ण

	gpiomtd->rdy = devm_gpiod_get_optional(dev, "rdy", GPIOD_IN);
	अगर (IS_ERR(gpiomtd->rdy)) अणु
		ret = PTR_ERR(gpiomtd->rdy);
		जाओ out_ce;
	पूर्ण

	nand_controller_init(&gpiomtd->base);
	gpiomtd->base.ops = &gpio_nand_ops;

	nand_set_flash_node(chip, pdev->dev.of_node);
	chip->options		= gpiomtd->plat.options;
	chip->controller	= &gpiomtd->base;

	mtd			= nand_to_mtd(chip);
	mtd->dev.parent		= dev;

	platक्रमm_set_drvdata(pdev, gpiomtd);

	/* Disable ग_लिखो protection, अगर wired up */
	अगर (gpiomtd->nwp && !IS_ERR(gpiomtd->nwp))
		gpiod_direction_output(gpiomtd->nwp, 1);

	ret = nand_scan(chip, 1);
	अगर (ret)
		जाओ err_wp;

	अगर (gpiomtd->plat.adjust_parts)
		gpiomtd->plat.adjust_parts(&gpiomtd->plat, mtd->size);

	ret = mtd_device_रेजिस्टर(mtd, gpiomtd->plat.parts,
				  gpiomtd->plat.num_parts);
	अगर (!ret)
		वापस 0;

err_wp:
	अगर (gpiomtd->nwp && !IS_ERR(gpiomtd->nwp))
		gpiod_set_value(gpiomtd->nwp, 0);
out_ce:
	अगर (gpiomtd->nce && !IS_ERR(gpiomtd->nce))
		gpiod_set_value(gpiomtd->nce, 0);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver gpio_nand_driver = अणु
	.probe		= gpio_nand_probe,
	.हटाओ		= gpio_nand_हटाओ,
	.driver		= अणु
		.name	= "gpio-nand",
		.of_match_table = of_match_ptr(gpio_nand_id_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(gpio_nand_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_DESCRIPTION("GPIO NAND Driver");
