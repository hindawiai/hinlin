<शैली गुरु>
/*
 * न_अंकD support क्रम Marvell Orion SoC platक्रमms
 *
 * Tzachi Perelstein <tzachi@marvell.com>
 *
 * This file is licensed under  the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/sizes.h>
#समावेश <linux/platक्रमm_data/mtd-orion_nand.h>

काष्ठा orion_nand_info अणु
	काष्ठा nand_controller controller;
	काष्ठा nand_chip chip;
	काष्ठा clk *clk;
पूर्ण;

अटल व्योम orion_nand_cmd_ctrl(काष्ठा nand_chip *nc, पूर्णांक cmd,
				अचिन्हित पूर्णांक ctrl)
अणु
	काष्ठा orion_nand_data *board = nand_get_controller_data(nc);
	u32 offs;

	अगर (cmd == न_अंकD_CMD_NONE)
		वापस;

	अगर (ctrl & न_अंकD_CLE)
		offs = (1 << board->cle);
	अन्यथा अगर (ctrl & न_अंकD_ALE)
		offs = (1 << board->ale);
	अन्यथा
		वापस;

	अगर (nc->options & न_अंकD_BUSWIDTH_16)
		offs <<= 1;

	ग_लिखोb(cmd, nc->legacy.IO_ADDR_W + offs);
पूर्ण

अटल व्योम orion_nand_पढ़ो_buf(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	व्योम __iomem *io_base = chip->legacy.IO_ADDR_R;
#अगर defined(__LINUX_ARM_ARCH__) && __LINUX_ARM_ARCH__ >= 5
	uपूर्णांक64_t *buf64;
#पूर्ण_अगर
	पूर्णांक i = 0;

	जबतक (len && (अचिन्हित दीर्घ)buf & 7) अणु
		*buf++ = पढ़ोb(io_base);
		len--;
	पूर्ण
#अगर defined(__LINUX_ARM_ARCH__) && __LINUX_ARM_ARCH__ >= 5
	buf64 = (uपूर्णांक64_t *)buf;
	जबतक (i < len/8) अणु
		/*
		 * Since GCC has no proper स्थिरraपूर्णांक (PR 43518)
		 * क्रमce x variable to r2/r3 रेजिस्टरs as ldrd inकाष्ठाion
		 * requires first रेजिस्टर to be even.
		 */
		रेजिस्टर uपूर्णांक64_t x यंत्र ("r2");

		यंत्र अस्थिर ("ldrd\t%0, [%1]" : "=&r" (x) : "r" (io_base));
		buf64[i++] = x;
	पूर्ण
	i *= 8;
#अन्यथा
	पढ़ोsl(io_base, buf, len/4);
	i = len / 4 * 4;
#पूर्ण_अगर
	जबतक (i < len)
		buf[i++] = पढ़ोb(io_base);
पूर्ण

अटल पूर्णांक orion_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;

	अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_UNKNOWN)
		chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops orion_nand_ops = अणु
	.attach_chip = orion_nand_attach_chip,
पूर्ण;

अटल पूर्णांक __init orion_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा orion_nand_info *info;
	काष्ठा mtd_info *mtd;
	काष्ठा nand_chip *nc;
	काष्ठा orion_nand_data *board;
	काष्ठा resource *res;
	व्योम __iomem *io_base;
	पूर्णांक ret = 0;
	u32 val = 0;

	info = devm_kzalloc(&pdev->dev,
			माप(काष्ठा orion_nand_info),
			GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	nc = &info->chip;
	mtd = nand_to_mtd(nc);

	nand_controller_init(&info->controller);
	info->controller.ops = &orion_nand_ops;
	nc->controller = &info->controller;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	io_base = devm_ioremap_resource(&pdev->dev, res);

	अगर (IS_ERR(io_base))
		वापस PTR_ERR(io_base);

	अगर (pdev->dev.of_node) अणु
		board = devm_kzalloc(&pdev->dev, माप(काष्ठा orion_nand_data),
					GFP_KERNEL);
		अगर (!board)
			वापस -ENOMEM;
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "cle", &val))
			board->cle = (u8)val;
		अन्यथा
			board->cle = 0;
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "ale", &val))
			board->ale = (u8)val;
		अन्यथा
			board->ale = 1;
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node,
						"bank-width", &val))
			board->width = (u8)val * 8;
		अन्यथा
			board->width = 8;
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node,
						"chip-delay", &val))
			board->chip_delay = (u8)val;
	पूर्ण अन्यथा अणु
		board = dev_get_platdata(&pdev->dev);
	पूर्ण

	mtd->dev.parent = &pdev->dev;

	nand_set_controller_data(nc, board);
	nand_set_flash_node(nc, pdev->dev.of_node);
	nc->legacy.IO_ADDR_R = nc->legacy.IO_ADDR_W = io_base;
	nc->legacy.cmd_ctrl = orion_nand_cmd_ctrl;
	nc->legacy.पढ़ो_buf = orion_nand_पढ़ो_buf;

	अगर (board->chip_delay)
		nc->legacy.chip_delay = board->chip_delay;

	WARN(board->width > 16,
		"%d bit bus width out of range",
		board->width);

	अगर (board->width == 16)
		nc->options |= न_अंकD_BUSWIDTH_16;

	platक्रमm_set_drvdata(pdev, info);

	/* Not all platक्रमms can gate the घड़ी, so it is not
	   an error अगर the घड़ी करोes not exists. */
	info->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(info->clk)) अणु
		ret = PTR_ERR(info->clk);
		अगर (ret == -ENOENT) अणु
			info->clk = शून्य;
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "failed to get clock!\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = clk_prepare_enable(info->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to prepare clock!\n");
		वापस ret;
	पूर्ण

	ret = nand_scan(nc, 1);
	अगर (ret)
		जाओ no_dev;

	mtd->name = "orion_nand";
	ret = mtd_device_रेजिस्टर(mtd, board->parts, board->nr_parts);
	अगर (ret) अणु
		nand_cleanup(nc);
		जाओ no_dev;
	पूर्ण

	वापस 0;

no_dev:
	clk_disable_unprepare(info->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक orion_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा orion_nand_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = &info->chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);

	nand_cleanup(chip);

	clk_disable_unprepare(info->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id orion_nand_of_match_table[] = अणु
	अणु .compatible = "marvell,orion-nand", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, orion_nand_of_match_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver orion_nand_driver = अणु
	.हटाओ		= orion_nand_हटाओ,
	.driver		= अणु
		.name	= "orion_nand",
		.of_match_table = of_match_ptr(orion_nand_of_match_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(orion_nand_driver, orion_nand_probe);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tzachi Perelstein");
MODULE_DESCRIPTION("NAND glue for Orion platforms");
MODULE_ALIAS("platform:orion_nand");
