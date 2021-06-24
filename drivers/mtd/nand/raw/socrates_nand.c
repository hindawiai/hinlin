<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright तऊ 2008 Ilya Yanok, Emcraft Systems
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>

#घोषणा FPGA_न_अंकD_CMD_MASK		(0x7 << 28)
#घोषणा FPGA_न_अंकD_CMD_COMMAND		(0x0 << 28)
#घोषणा FPGA_न_अंकD_CMD_ADDR		(0x1 << 28)
#घोषणा FPGA_न_अंकD_CMD_READ		(0x2 << 28)
#घोषणा FPGA_न_अंकD_CMD_WRITE		(0x3 << 28)
#घोषणा FPGA_न_अंकD_BUSY			(0x1 << 15)
#घोषणा FPGA_न_अंकD_ENABLE		(0x1 << 31)
#घोषणा FPGA_न_अंकD_DATA_SHIFT		16

काष्ठा socrates_nand_host अणु
	काष्ठा nand_controller	controller;
	काष्ठा nand_chip	nand_chip;
	व्योम __iomem		*io_base;
	काष्ठा device		*dev;
पूर्ण;

/**
 * socrates_nand_ग_लिखो_buf -  ग_लिखो buffer to chip
 * @this:	न_अंकD chip object
 * @buf:	data buffer
 * @len:	number of bytes to ग_लिखो
 */
अटल व्योम socrates_nand_ग_लिखो_buf(काष्ठा nand_chip *this, स्थिर uपूर्णांक8_t *buf,
				    पूर्णांक len)
अणु
	पूर्णांक i;
	काष्ठा socrates_nand_host *host = nand_get_controller_data(this);

	क्रम (i = 0; i < len; i++) अणु
		out_be32(host->io_base, FPGA_न_अंकD_ENABLE |
				FPGA_न_अंकD_CMD_WRITE |
				(buf[i] << FPGA_न_अंकD_DATA_SHIFT));
	पूर्ण
पूर्ण

/**
 * socrates_nand_पढ़ो_buf -  पढ़ो chip data पूर्णांकo buffer
 * @this:	न_अंकD chip object
 * @buf:	buffer to store date
 * @len:	number of bytes to पढ़ो
 */
अटल व्योम socrates_nand_पढ़ो_buf(काष्ठा nand_chip *this, uपूर्णांक8_t *buf,
				   पूर्णांक len)
अणु
	पूर्णांक i;
	काष्ठा socrates_nand_host *host = nand_get_controller_data(this);
	uपूर्णांक32_t val;

	val = FPGA_न_अंकD_ENABLE | FPGA_न_अंकD_CMD_READ;

	out_be32(host->io_base, val);
	क्रम (i = 0; i < len; i++) अणु
		buf[i] = (in_be32(host->io_base) >>
				FPGA_न_अंकD_DATA_SHIFT) & 0xff;
	पूर्ण
पूर्ण

/**
 * socrates_nand_पढ़ो_byte -  पढ़ो one byte from the chip
 * @mtd:	MTD device काष्ठाure
 */
अटल uपूर्णांक8_t socrates_nand_पढ़ो_byte(काष्ठा nand_chip *this)
अणु
	uपूर्णांक8_t byte;
	socrates_nand_पढ़ो_buf(this, &byte, माप(byte));
	वापस byte;
पूर्ण

/*
 * Hardware specअगरic access to control-lines
 */
अटल व्योम socrates_nand_cmd_ctrl(काष्ठा nand_chip *nand_chip, पूर्णांक cmd,
				   अचिन्हित पूर्णांक ctrl)
अणु
	काष्ठा socrates_nand_host *host = nand_get_controller_data(nand_chip);
	uपूर्णांक32_t val;

	अगर (cmd == न_अंकD_CMD_NONE)
		वापस;

	अगर (ctrl & न_अंकD_CLE)
		val = FPGA_न_अंकD_CMD_COMMAND;
	अन्यथा
		val = FPGA_न_अंकD_CMD_ADDR;

	अगर (ctrl & न_अंकD_NCE)
		val |= FPGA_न_अंकD_ENABLE;

	val |= (cmd & 0xff) << FPGA_न_अंकD_DATA_SHIFT;

	out_be32(host->io_base, val);
पूर्ण

/*
 * Read the Device Ready pin.
 */
अटल पूर्णांक socrates_nand_device_पढ़ोy(काष्ठा nand_chip *nand_chip)
अणु
	काष्ठा socrates_nand_host *host = nand_get_controller_data(nand_chip);

	अगर (in_be32(host->io_base) & FPGA_न_अंकD_BUSY)
		वापस 0; /* busy */
	वापस 1;
पूर्ण

अटल पूर्णांक socrates_attach_chip(काष्ठा nand_chip *chip)
अणु
	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;

	अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_UNKNOWN)
		chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops socrates_ops = अणु
	.attach_chip = socrates_attach_chip,
पूर्ण;

/*
 * Probe क्रम the न_अंकD device.
 */
अटल पूर्णांक socrates_nand_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा socrates_nand_host *host;
	काष्ठा mtd_info *mtd;
	काष्ठा nand_chip *nand_chip;
	पूर्णांक res;

	/* Allocate memory क्रम the device काष्ठाure (and zero it) */
	host = devm_kzalloc(&ofdev->dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	host->io_base = of_iomap(ofdev->dev.of_node, 0);
	अगर (host->io_base == शून्य) अणु
		dev_err(&ofdev->dev, "ioremap failed\n");
		वापस -EIO;
	पूर्ण

	nand_chip = &host->nand_chip;
	mtd = nand_to_mtd(nand_chip);
	host->dev = &ofdev->dev;

	nand_controller_init(&host->controller);
	host->controller.ops = &socrates_ops;
	nand_chip->controller = &host->controller;

	/* link the निजी data काष्ठाures */
	nand_set_controller_data(nand_chip, host);
	nand_set_flash_node(nand_chip, ofdev->dev.of_node);
	mtd->name = "socrates_nand";
	mtd->dev.parent = &ofdev->dev;

	nand_chip->legacy.cmd_ctrl = socrates_nand_cmd_ctrl;
	nand_chip->legacy.पढ़ो_byte = socrates_nand_पढ़ो_byte;
	nand_chip->legacy.ग_लिखो_buf = socrates_nand_ग_लिखो_buf;
	nand_chip->legacy.पढ़ो_buf = socrates_nand_पढ़ो_buf;
	nand_chip->legacy.dev_पढ़ोy = socrates_nand_device_पढ़ोy;

	/* TODO: I have no idea what real delay is. */
	nand_chip->legacy.chip_delay = 20;	/* 20us command delay समय */

	dev_set_drvdata(&ofdev->dev, host);

	res = nand_scan(nand_chip, 1);
	अगर (res)
		जाओ out;

	res = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (!res)
		वापस res;

	nand_cleanup(nand_chip);

out:
	iounmap(host->io_base);
	वापस res;
पूर्ण

/*
 * Remove a न_अंकD device.
 */
अटल पूर्णांक socrates_nand_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा socrates_nand_host *host = dev_get_drvdata(&ofdev->dev);
	काष्ठा nand_chip *chip = &host->nand_chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);

	iounmap(host->io_base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id socrates_nand_match[] =
अणु
	अणु
		.compatible   = "abb,socrates-nand",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, socrates_nand_match);

अटल काष्ठा platक्रमm_driver socrates_nand_driver = अणु
	.driver = अणु
		.name = "socrates_nand",
		.of_match_table = socrates_nand_match,
	पूर्ण,
	.probe		= socrates_nand_probe,
	.हटाओ		= socrates_nand_हटाओ,
पूर्ण;

module_platक्रमm_driver(socrates_nand_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ilya Yanok");
MODULE_DESCRIPTION("NAND driver for Socrates board");
