<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale UPM न_अंकD driver.
 *
 * Copyright तऊ 2007-2008  MontaVista Software, Inc.
 *
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/fsl_lbc.h>

काष्ठा fsl_upm_nand अणु
	काष्ठा nand_controller base;
	काष्ठा device *dev;
	काष्ठा nand_chip chip;
	काष्ठा fsl_upm upm;
	uपूर्णांक8_t upm_addr_offset;
	uपूर्णांक8_t upm_cmd_offset;
	व्योम __iomem *io_base;
	काष्ठा gpio_desc *rnb_gpio[न_अंकD_MAX_CHIPS];
	uपूर्णांक32_t mchip_offsets[न_अंकD_MAX_CHIPS];
	uपूर्णांक32_t mchip_count;
	uपूर्णांक32_t mchip_number;
पूर्ण;

अटल अंतरभूत काष्ठा fsl_upm_nand *to_fsl_upm_nand(काष्ठा mtd_info *mtdinfo)
अणु
	वापस container_of(mtd_to_nand(mtdinfo), काष्ठा fsl_upm_nand,
			    chip);
पूर्ण

अटल पूर्णांक fun_chip_init(काष्ठा fsl_upm_nand *fun,
			 स्थिर काष्ठा device_node *upm_np,
			 स्थिर काष्ठा resource *io_res)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(&fun->chip);
	पूर्णांक ret;
	काष्ठा device_node *flash_np;

	fun->chip.ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;
	fun->chip.ecc.algo = न_अंकD_ECC_ALGO_HAMMING;
	fun->chip.controller = &fun->base;
	mtd->dev.parent = fun->dev;

	flash_np = of_get_next_child(upm_np, शून्य);
	अगर (!flash_np)
		वापस -ENODEV;

	nand_set_flash_node(&fun->chip, flash_np);
	mtd->name = devm_kaप्र_लिखो(fun->dev, GFP_KERNEL, "0x%llx.%pOFn",
				   (u64)io_res->start,
				   flash_np);
	अगर (!mtd->name) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = nand_scan(&fun->chip, fun->mchip_count);
	अगर (ret)
		जाओ err;

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
err:
	of_node_put(flash_np);
	वापस ret;
पूर्ण

अटल पूर्णांक func_exec_instr(काष्ठा nand_chip *chip,
			   स्थिर काष्ठा nand_op_instr *instr)
अणु
	काष्ठा fsl_upm_nand *fun = to_fsl_upm_nand(nand_to_mtd(chip));
	u32 mar, reg_offs = fun->mchip_offsets[fun->mchip_number];
	अचिन्हित पूर्णांक i;
	स्थिर u8 *out;
	u8 *in;

	चयन (instr->type) अणु
	हाल न_अंकD_OP_CMD_INSTR:
		fsl_upm_start_pattern(&fun->upm, fun->upm_cmd_offset);
		mar = (instr->ctx.cmd.opcode << (32 - fun->upm.width)) |
		      reg_offs;
		fsl_upm_run_pattern(&fun->upm, fun->io_base + reg_offs, mar);
		fsl_upm_end_pattern(&fun->upm);
		वापस 0;

	हाल न_अंकD_OP_ADDR_INSTR:
		fsl_upm_start_pattern(&fun->upm, fun->upm_addr_offset);
		क्रम (i = 0; i < instr->ctx.addr.naddrs; i++) अणु
			mar = (instr->ctx.addr.addrs[i] << (32 - fun->upm.width)) |
			      reg_offs;
			fsl_upm_run_pattern(&fun->upm, fun->io_base + reg_offs, mar);
		पूर्ण
		fsl_upm_end_pattern(&fun->upm);
		वापस 0;

	हाल न_अंकD_OP_DATA_IN_INSTR:
		in = instr->ctx.data.buf.in;
		क्रम (i = 0; i < instr->ctx.data.len; i++)
			in[i] = in_8(fun->io_base + reg_offs);
		वापस 0;

	हाल न_अंकD_OP_DATA_OUT_INSTR:
		out = instr->ctx.data.buf.out;
		क्रम (i = 0; i < instr->ctx.data.len; i++)
			out_8(fun->io_base + reg_offs, out[i]);
		वापस 0;

	हाल न_अंकD_OP_WAITRDY_INSTR:
		अगर (!fun->rnb_gpio[fun->mchip_number])
			वापस nand_soft_रुकोrdy(chip, instr->ctx.रुकोrdy.समयout_ms);

		वापस nand_gpio_रुकोrdy(chip, fun->rnb_gpio[fun->mchip_number],
					 instr->ctx.रुकोrdy.समयout_ms);

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fun_exec_op(काष्ठा nand_chip *chip, स्थिर काष्ठा nand_operation *op,
		       bool check_only)
अणु
	काष्ठा fsl_upm_nand *fun = to_fsl_upm_nand(nand_to_mtd(chip));
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (op->cs > न_अंकD_MAX_CHIPS)
		वापस -EINVAL;

	अगर (check_only)
		वापस 0;

	fun->mchip_number = op->cs;

	क्रम (i = 0; i < op->ninstrs; i++) अणु
		ret = func_exec_instr(chip, &op->instrs[i]);
		अगर (ret)
			वापस ret;

		अगर (op->instrs[i].delay_ns)
			ndelay(op->instrs[i].delay_ns);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops fun_ops = अणु
	.exec_op = fun_exec_op,
पूर्ण;

अटल पूर्णांक fun_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा fsl_upm_nand *fun;
	काष्ठा resource *io_res;
	स्थिर __be32 *prop;
	पूर्णांक ret;
	पूर्णांक size;
	पूर्णांक i;

	fun = devm_kzalloc(&ofdev->dev, माप(*fun), GFP_KERNEL);
	अगर (!fun)
		वापस -ENOMEM;

	io_res = platक्रमm_get_resource(ofdev, IORESOURCE_MEM, 0);
	fun->io_base = devm_ioremap_resource(&ofdev->dev, io_res);
	अगर (IS_ERR(fun->io_base))
		वापस PTR_ERR(fun->io_base);

	ret = fsl_upm_find(io_res->start, &fun->upm);
	अगर (ret) अणु
		dev_err(&ofdev->dev, "can't find UPM\n");
		वापस ret;
	पूर्ण

	prop = of_get_property(ofdev->dev.of_node, "fsl,upm-addr-offset",
			       &size);
	अगर (!prop || size != माप(uपूर्णांक32_t)) अणु
		dev_err(&ofdev->dev, "can't get UPM address offset\n");
		वापस -EINVAL;
	पूर्ण
	fun->upm_addr_offset = *prop;

	prop = of_get_property(ofdev->dev.of_node, "fsl,upm-cmd-offset", &size);
	अगर (!prop || size != माप(uपूर्णांक32_t)) अणु
		dev_err(&ofdev->dev, "can't get UPM command offset\n");
		वापस -EINVAL;
	पूर्ण
	fun->upm_cmd_offset = *prop;

	prop = of_get_property(ofdev->dev.of_node,
			       "fsl,upm-addr-line-cs-offsets", &size);
	अगर (prop && (size / माप(uपूर्णांक32_t)) > 0) अणु
		fun->mchip_count = size / माप(uपूर्णांक32_t);
		अगर (fun->mchip_count >= न_अंकD_MAX_CHIPS) अणु
			dev_err(&ofdev->dev, "too much multiple chips\n");
			वापस -EINVAL;
		पूर्ण
		क्रम (i = 0; i < fun->mchip_count; i++)
			fun->mchip_offsets[i] = be32_to_cpu(prop[i]);
	पूर्ण अन्यथा अणु
		fun->mchip_count = 1;
	पूर्ण

	क्रम (i = 0; i < fun->mchip_count; i++) अणु
		fun->rnb_gpio[i] = devm_gpiod_get_index_optional(&ofdev->dev,
								 शून्य, i,
								 GPIOD_IN);
		अगर (IS_ERR(fun->rnb_gpio[i])) अणु
			dev_err(&ofdev->dev, "RNB gpio #%d is invalid\n", i);
			वापस PTR_ERR(fun->rnb_gpio[i]);
		पूर्ण
	पूर्ण

	nand_controller_init(&fun->base);
	fun->base.ops = &fun_ops;
	fun->dev = &ofdev->dev;

	ret = fun_chip_init(fun, ofdev->dev.of_node, io_res);
	अगर (ret)
		वापस ret;

	dev_set_drvdata(&ofdev->dev, fun);

	वापस 0;
पूर्ण

अटल पूर्णांक fun_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा fsl_upm_nand *fun = dev_get_drvdata(&ofdev->dev);
	काष्ठा nand_chip *chip = &fun->chip;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(mtd);
	WARN_ON(ret);
	nand_cleanup(chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_fun_match[] = अणु
	अणु .compatible = "fsl,upm-nand" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_fun_match);

अटल काष्ठा platक्रमm_driver of_fun_driver = अणु
	.driver = अणु
		.name = "fsl,upm-nand",
		.of_match_table = of_fun_match,
	पूर्ण,
	.probe		= fun_probe,
	.हटाओ		= fun_हटाओ,
पूर्ण;

module_platक्रमm_driver(of_fun_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anton Vorontsov <avorontsov@ru.mvista.com>");
MODULE_DESCRIPTION("Driver for NAND chips working through Freescale "
		   "LocalBus User-Programmable Machine");
