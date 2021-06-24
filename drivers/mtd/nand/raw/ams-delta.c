<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2006 Jonathan McDowell <noodles@earth.li>
 *
 *  Derived from drivers/mtd/nand/toto.c (हटाओd in v2.6.28)
 *    Copyright (c) 2003 Texas Instruments
 *    Copyright (c) 2002 Thomas Gleixner <tgxl@linutronix.de>
 *
 *  Converted to platक्रमm driver by Janusz Krzysztofik <jkrzyszt@tis.icnet.pl>
 *  Partially stolen from plat_nand.c
 *
 *  Overview:
 *   This is a device driver क्रम the न_अंकD flash device found on the
 *   Amstrad E3 (Delta).
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nand-gpपन.स>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sizes.h>

/*
 * MTD काष्ठाure क्रम E3 (Delta)
 */
काष्ठा gpio_nand अणु
	काष्ठा nand_controller	base;
	काष्ठा nand_chip	nand_chip;
	काष्ठा gpio_desc	*gpiod_rdy;
	काष्ठा gpio_desc	*gpiod_nce;
	काष्ठा gpio_desc	*gpiod_nre;
	काष्ठा gpio_desc	*gpiod_nwp;
	काष्ठा gpio_desc	*gpiod_nwe;
	काष्ठा gpio_desc	*gpiod_ale;
	काष्ठा gpio_desc	*gpiod_cle;
	काष्ठा gpio_descs	*data_gpiods;
	bool			data_in;
	अचिन्हित पूर्णांक		tRP;
	अचिन्हित पूर्णांक		tWP;
	u8			(*io_पढ़ो)(काष्ठा gpio_nand *this);
	व्योम			(*io_ग_लिखो)(काष्ठा gpio_nand *this, u8 byte);
पूर्ण;

अटल व्योम gpio_nand_ग_लिखो_commit(काष्ठा gpio_nand *priv)
अणु
	gpiod_set_value(priv->gpiod_nwe, 1);
	ndelay(priv->tWP);
	gpiod_set_value(priv->gpiod_nwe, 0);
पूर्ण

अटल व्योम gpio_nand_io_ग_लिखो(काष्ठा gpio_nand *priv, u8 byte)
अणु
	काष्ठा gpio_descs *data_gpiods = priv->data_gpiods;
	DECLARE_BITMAP(values, BITS_PER_TYPE(byte)) = अणु byte, पूर्ण;

	gpiod_set_raw_array_value(data_gpiods->ndescs, data_gpiods->desc,
				  data_gpiods->info, values);

	gpio_nand_ग_लिखो_commit(priv);
पूर्ण

अटल व्योम gpio_nand_dir_output(काष्ठा gpio_nand *priv, u8 byte)
अणु
	काष्ठा gpio_descs *data_gpiods = priv->data_gpiods;
	DECLARE_BITMAP(values, BITS_PER_TYPE(byte)) = अणु byte, पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < data_gpiods->ndescs; i++)
		gpiod_direction_output_raw(data_gpiods->desc[i],
					   test_bit(i, values));

	gpio_nand_ग_लिखो_commit(priv);

	priv->data_in = false;
पूर्ण

अटल u8 gpio_nand_io_पढ़ो(काष्ठा gpio_nand *priv)
अणु
	u8 res;
	काष्ठा gpio_descs *data_gpiods = priv->data_gpiods;
	DECLARE_BITMAP(values, BITS_PER_TYPE(res)) = अणु 0, पूर्ण;

	gpiod_set_value(priv->gpiod_nre, 1);
	ndelay(priv->tRP);

	gpiod_get_raw_array_value(data_gpiods->ndescs, data_gpiods->desc,
				  data_gpiods->info, values);

	gpiod_set_value(priv->gpiod_nre, 0);

	res = values[0];
	वापस res;
पूर्ण

अटल व्योम gpio_nand_dir_input(काष्ठा gpio_nand *priv)
अणु
	काष्ठा gpio_descs *data_gpiods = priv->data_gpiods;
	पूर्णांक i;

	क्रम (i = 0; i < data_gpiods->ndescs; i++)
		gpiod_direction_input(data_gpiods->desc[i]);

	priv->data_in = true;
पूर्ण

अटल व्योम gpio_nand_ग_लिखो_buf(काष्ठा gpio_nand *priv, स्थिर u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i = 0;

	अगर (len > 0 && priv->data_in)
		gpio_nand_dir_output(priv, buf[i++]);

	जबतक (i < len)
		priv->io_ग_लिखो(priv, buf[i++]);
पूर्ण

अटल व्योम gpio_nand_पढ़ो_buf(काष्ठा gpio_nand *priv, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	अगर (priv->data_gpiods && !priv->data_in)
		gpio_nand_dir_input(priv);

	क्रम (i = 0; i < len; i++)
		buf[i] = priv->io_पढ़ो(priv);
पूर्ण

अटल व्योम gpio_nand_ctrl_cs(काष्ठा gpio_nand *priv, bool निश्चित)
अणु
	gpiod_set_value(priv->gpiod_nce, निश्चित);
पूर्ण

अटल पूर्णांक gpio_nand_exec_op(काष्ठा nand_chip *this,
			     स्थिर काष्ठा nand_operation *op, bool check_only)
अणु
	काष्ठा gpio_nand *priv = nand_get_controller_data(this);
	स्थिर काष्ठा nand_op_instr *instr;
	पूर्णांक ret = 0;

	अगर (check_only)
		वापस 0;

	gpio_nand_ctrl_cs(priv, 1);

	क्रम (instr = op->instrs; instr < op->instrs + op->ninstrs; instr++) अणु
		चयन (instr->type) अणु
		हाल न_अंकD_OP_CMD_INSTR:
			gpiod_set_value(priv->gpiod_cle, 1);
			gpio_nand_ग_लिखो_buf(priv, &instr->ctx.cmd.opcode, 1);
			gpiod_set_value(priv->gpiod_cle, 0);
			अवरोध;

		हाल न_अंकD_OP_ADDR_INSTR:
			gpiod_set_value(priv->gpiod_ale, 1);
			gpio_nand_ग_लिखो_buf(priv, instr->ctx.addr.addrs,
					    instr->ctx.addr.naddrs);
			gpiod_set_value(priv->gpiod_ale, 0);
			अवरोध;

		हाल न_अंकD_OP_DATA_IN_INSTR:
			gpio_nand_पढ़ो_buf(priv, instr->ctx.data.buf.in,
					   instr->ctx.data.len);
			अवरोध;

		हाल न_अंकD_OP_DATA_OUT_INSTR:
			gpio_nand_ग_लिखो_buf(priv, instr->ctx.data.buf.out,
					    instr->ctx.data.len);
			अवरोध;

		हाल न_अंकD_OP_WAITRDY_INSTR:
			ret = priv->gpiod_rdy ?
			      nand_gpio_रुकोrdy(this, priv->gpiod_rdy,
						instr->ctx.रुकोrdy.समयout_ms) :
			      nand_soft_रुकोrdy(this,
						instr->ctx.रुकोrdy.समयout_ms);
			अवरोध;
		पूर्ण

		अगर (ret)
			अवरोध;
	पूर्ण

	gpio_nand_ctrl_cs(priv, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक gpio_nand_setup_पूर्णांकerface(काष्ठा nand_chip *this, पूर्णांक csline,
				     स्थिर काष्ठा nand_पूर्णांकerface_config *cf)
अणु
	काष्ठा gpio_nand *priv = nand_get_controller_data(this);
	स्थिर काष्ठा nand_sdr_timings *sdr = nand_get_sdr_timings(cf);
	काष्ठा device *dev = &nand_to_mtd(this)->dev;

	अगर (IS_ERR(sdr))
		वापस PTR_ERR(sdr);

	अगर (csline == न_अंकD_DATA_IFACE_CHECK_ONLY)
		वापस 0;

	अगर (priv->gpiod_nre) अणु
		priv->tRP = DIV_ROUND_UP(sdr->tRP_min, 1000);
		dev_dbg(dev, "using %u ns read pulse width\n", priv->tRP);
	पूर्ण

	priv->tWP = DIV_ROUND_UP(sdr->tWP_min, 1000);
	dev_dbg(dev, "using %u ns write pulse width\n", priv->tWP);

	वापस 0;
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
	.setup_पूर्णांकerface = gpio_nand_setup_पूर्णांकerface,
पूर्ण;

/*
 * Main initialization routine
 */
अटल पूर्णांक gpio_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_nand_platdata *pdata = dev_get_platdata(&pdev->dev);
	स्थिर काष्ठा mtd_partition *partitions = शून्य;
	पूर्णांक num_partitions = 0;
	काष्ठा gpio_nand *priv;
	काष्ठा nand_chip *this;
	काष्ठा mtd_info *mtd;
	पूर्णांक (*probe)(काष्ठा platक्रमm_device *pdev, काष्ठा gpio_nand *priv);
	पूर्णांक err = 0;

	अगर (pdata) अणु
		partitions = pdata->parts;
		num_partitions = pdata->num_parts;
	पूर्ण

	/* Allocate memory क्रम MTD device काष्ठाure and निजी data */
	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा gpio_nand),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	this = &priv->nand_chip;

	mtd = nand_to_mtd(this);
	mtd->dev.parent = &pdev->dev;

	nand_set_controller_data(this, priv);
	nand_set_flash_node(this, pdev->dev.of_node);

	priv->gpiod_rdy = devm_gpiod_get_optional(&pdev->dev, "rdy", GPIOD_IN);
	अगर (IS_ERR(priv->gpiod_rdy)) अणु
		err = PTR_ERR(priv->gpiod_rdy);
		dev_warn(&pdev->dev, "RDY GPIO request failed (%d)\n", err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	/* Set chip enabled but ग_लिखो रक्षित */
	priv->gpiod_nwp = devm_gpiod_get_optional(&pdev->dev, "nwp",
						  GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->gpiod_nwp)) अणु
		err = PTR_ERR(priv->gpiod_nwp);
		dev_err(&pdev->dev, "NWP GPIO request failed (%d)\n", err);
		वापस err;
	पूर्ण

	priv->gpiod_nce = devm_gpiod_get_optional(&pdev->dev, "nce",
						  GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->gpiod_nce)) अणु
		err = PTR_ERR(priv->gpiod_nce);
		dev_err(&pdev->dev, "NCE GPIO request failed (%d)\n", err);
		वापस err;
	पूर्ण

	priv->gpiod_nre = devm_gpiod_get_optional(&pdev->dev, "nre",
						  GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->gpiod_nre)) अणु
		err = PTR_ERR(priv->gpiod_nre);
		dev_err(&pdev->dev, "NRE GPIO request failed (%d)\n", err);
		वापस err;
	पूर्ण

	priv->gpiod_nwe = devm_gpiod_get_optional(&pdev->dev, "nwe",
						  GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->gpiod_nwe)) अणु
		err = PTR_ERR(priv->gpiod_nwe);
		dev_err(&pdev->dev, "NWE GPIO request failed (%d)\n", err);
		वापस err;
	पूर्ण

	priv->gpiod_ale = devm_gpiod_get(&pdev->dev, "ale", GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->gpiod_ale)) अणु
		err = PTR_ERR(priv->gpiod_ale);
		dev_err(&pdev->dev, "ALE GPIO request failed (%d)\n", err);
		वापस err;
	पूर्ण

	priv->gpiod_cle = devm_gpiod_get(&pdev->dev, "cle", GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->gpiod_cle)) अणु
		err = PTR_ERR(priv->gpiod_cle);
		dev_err(&pdev->dev, "CLE GPIO request failed (%d)\n", err);
		वापस err;
	पूर्ण

	/* Request array of data pins, initialize them as input */
	priv->data_gpiods = devm_gpiod_get_array_optional(&pdev->dev, "data",
							  GPIOD_IN);
	अगर (IS_ERR(priv->data_gpiods)) अणु
		err = PTR_ERR(priv->data_gpiods);
		dev_err(&pdev->dev, "data GPIO request failed: %d\n", err);
		वापस err;
	पूर्ण
	अगर (priv->data_gpiods) अणु
		अगर (!priv->gpiod_nwe) अणु
			dev_err(&pdev->dev,
				"mandatory NWE pin not provided by platform\n");
			वापस -ENODEV;
		पूर्ण

		priv->io_पढ़ो = gpio_nand_io_पढ़ो;
		priv->io_ग_लिखो = gpio_nand_io_ग_लिखो;
		priv->data_in = true;
	पूर्ण

	अगर (pdev->id_entry)
		probe = (व्योम *) pdev->id_entry->driver_data;
	अन्यथा
		probe = of_device_get_match_data(&pdev->dev);
	अगर (probe)
		err = probe(pdev, priv);
	अगर (err)
		वापस err;

	अगर (!priv->io_पढ़ो || !priv->io_ग_लिखो) अणु
		dev_err(&pdev->dev, "incomplete device configuration\n");
		वापस -ENODEV;
	पूर्ण

	/* Initialize the न_अंकD controller object embedded in gpio_nand. */
	priv->base.ops = &gpio_nand_ops;
	nand_controller_init(&priv->base);
	this->controller = &priv->base;

	/*
	 * FIXME: We should release ग_लिखो protection only after nand_scan() to
	 * be on the safe side but we can't करो that until we have a generic way
	 * to निश्चित/deनिश्चित WP from the core.  Even अगर the core shouldn't
	 * ग_लिखो things in the nand_scan() path, it should have control on this
	 * pin just in हाल we ever need to disable ग_लिखो protection during
	 * chip detection/initialization.
	 */
	/* Release ग_लिखो protection */
	gpiod_set_value(priv->gpiod_nwp, 0);

	/* Scan to find existence of the device */
	err = nand_scan(this, 1);
	अगर (err)
		वापस err;

	/* Register the partitions */
	err = mtd_device_रेजिस्टर(mtd, partitions, num_partitions);
	अगर (err)
		जाओ err_nand_cleanup;

	वापस 0;

err_nand_cleanup:
	nand_cleanup(this);

	वापस err;
पूर्ण

/*
 * Clean up routine
 */
अटल पूर्णांक gpio_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_nand *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा mtd_info *mtd = nand_to_mtd(&priv->nand_chip);
	पूर्णांक ret;

	/* Apply ग_लिखो protection */
	gpiod_set_value(priv->gpiod_nwp, 1);

	/* Unरेजिस्टर device */
	ret = mtd_device_unरेजिस्टर(mtd);
	WARN_ON(ret);
	nand_cleanup(mtd_to_nand(mtd));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id gpio_nand_of_id_table[] = अणु
	अणु
		/* sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_nand_of_id_table);
#पूर्ण_अगर

अटल स्थिर काष्ठा platक्रमm_device_id gpio_nand_plat_id_table[] = अणु
	अणु
		.name	= "ams-delta-nand",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, gpio_nand_plat_id_table);

अटल काष्ठा platक्रमm_driver gpio_nand_driver = अणु
	.probe		= gpio_nand_probe,
	.हटाओ		= gpio_nand_हटाओ,
	.id_table	= gpio_nand_plat_id_table,
	.driver		= अणु
		.name	= "ams-delta-nand",
		.of_match_table = of_match_ptr(gpio_nand_of_id_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(gpio_nand_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jonathan McDowell <noodles@earth.li>");
MODULE_DESCRIPTION("Glue layer for NAND flash on Amstrad E3 (Delta)");
