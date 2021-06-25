<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mchp23k256.c
 *
 * Driver क्रम Microchip 23k256 SPI RAM chips
 *
 * Copyright तऊ 2016 Andrew Lunn <andrew@lunn.ch>
 */
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/sizes.h>
#समावेश <linux/spi/flash.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/of_device.h>

#घोषणा MAX_CMD_SIZE		4

काष्ठा mchp23_caps अणु
	u8 addr_width;
	अचिन्हित पूर्णांक size;
पूर्ण;

काष्ठा mchp23k256_flash अणु
	काष्ठा spi_device	*spi;
	काष्ठा mutex		lock;
	काष्ठा mtd_info		mtd;
	स्थिर काष्ठा mchp23_caps	*caps;
पूर्ण;

#घोषणा MCHP23K256_CMD_WRITE_STATUS	0x01
#घोषणा MCHP23K256_CMD_WRITE		0x02
#घोषणा MCHP23K256_CMD_READ		0x03
#घोषणा MCHP23K256_MODE_SEQ		BIT(6)

#घोषणा to_mchp23k256_flash(x) container_of(x, काष्ठा mchp23k256_flash, mtd)

अटल व्योम mchp23k256_addr2cmd(काष्ठा mchp23k256_flash *flash,
				अचिन्हित पूर्णांक addr, u8 *cmd)
अणु
	पूर्णांक i;

	/*
	 * Address is sent in big endian (MSB first) and we skip
	 * the first entry of the cmd array which contains the cmd
	 * opcode.
	 */
	क्रम (i = flash->caps->addr_width; i > 0; i--, addr >>= 8)
		cmd[i] = addr;
पूर्ण

अटल पूर्णांक mchp23k256_cmdsz(काष्ठा mchp23k256_flash *flash)
अणु
	वापस 1 + flash->caps->addr_width;
पूर्ण

अटल पूर्णांक mchp23k256_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
			    माप_प्रकार *retlen, स्थिर अचिन्हित अक्षर *buf)
अणु
	काष्ठा mchp23k256_flash *flash = to_mchp23k256_flash(mtd);
	काष्ठा spi_transfer transfer[2] = अणुपूर्ण;
	काष्ठा spi_message message;
	अचिन्हित अक्षर command[MAX_CMD_SIZE];
	पूर्णांक ret, cmd_len;

	spi_message_init(&message);

	cmd_len = mchp23k256_cmdsz(flash);

	command[0] = MCHP23K256_CMD_WRITE;
	mchp23k256_addr2cmd(flash, to, command);

	transfer[0].tx_buf = command;
	transfer[0].len = cmd_len;
	spi_message_add_tail(&transfer[0], &message);

	transfer[1].tx_buf = buf;
	transfer[1].len = len;
	spi_message_add_tail(&transfer[1], &message);

	mutex_lock(&flash->lock);

	ret = spi_sync(flash->spi, &message);

	mutex_unlock(&flash->lock);

	अगर (ret)
		वापस ret;

	अगर (retlen && message.actual_length > cmd_len)
		*retlen += message.actual_length - cmd_len;

	वापस 0;
पूर्ण

अटल पूर्णांक mchp23k256_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			   माप_प्रकार *retlen, अचिन्हित अक्षर *buf)
अणु
	काष्ठा mchp23k256_flash *flash = to_mchp23k256_flash(mtd);
	काष्ठा spi_transfer transfer[2] = अणुपूर्ण;
	काष्ठा spi_message message;
	अचिन्हित अक्षर command[MAX_CMD_SIZE];
	पूर्णांक ret, cmd_len;

	spi_message_init(&message);

	cmd_len = mchp23k256_cmdsz(flash);

	स_रखो(&transfer, 0, माप(transfer));
	command[0] = MCHP23K256_CMD_READ;
	mchp23k256_addr2cmd(flash, from, command);

	transfer[0].tx_buf = command;
	transfer[0].len = cmd_len;
	spi_message_add_tail(&transfer[0], &message);

	transfer[1].rx_buf = buf;
	transfer[1].len = len;
	spi_message_add_tail(&transfer[1], &message);

	mutex_lock(&flash->lock);

	ret = spi_sync(flash->spi, &message);

	mutex_unlock(&flash->lock);

	अगर (ret)
		वापस ret;

	अगर (retlen && message.actual_length > cmd_len)
		*retlen += message.actual_length - cmd_len;

	वापस 0;
पूर्ण

/*
 * Set the device पूर्णांकo sequential mode. This allows पढ़ो/ग_लिखोs to the
 * entire SRAM in a single operation
 */
अटल पूर्णांक mchp23k256_set_mode(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_transfer transfer = अणुपूर्ण;
	काष्ठा spi_message message;
	अचिन्हित अक्षर command[2];

	spi_message_init(&message);

	command[0] = MCHP23K256_CMD_WRITE_STATUS;
	command[1] = MCHP23K256_MODE_SEQ;

	transfer.tx_buf = command;
	transfer.len = माप(command);
	spi_message_add_tail(&transfer, &message);

	वापस spi_sync(spi, &message);
पूर्ण

अटल स्थिर काष्ठा mchp23_caps mchp23k256_caps = अणु
	.size = SZ_32K,
	.addr_width = 2,
पूर्ण;

अटल स्थिर काष्ठा mchp23_caps mchp23lcv1024_caps = अणु
	.size = SZ_128K,
	.addr_width = 3,
पूर्ण;

अटल पूर्णांक mchp23k256_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा mchp23k256_flash *flash;
	काष्ठा flash_platक्रमm_data *data;
	पूर्णांक err;

	flash = devm_kzalloc(&spi->dev, माप(*flash), GFP_KERNEL);
	अगर (!flash)
		वापस -ENOMEM;

	flash->spi = spi;
	mutex_init(&flash->lock);
	spi_set_drvdata(spi, flash);

	err = mchp23k256_set_mode(spi);
	अगर (err)
		वापस err;

	data = dev_get_platdata(&spi->dev);

	flash->caps = of_device_get_match_data(&spi->dev);
	अगर (!flash->caps)
		flash->caps = &mchp23k256_caps;

	mtd_set_of_node(&flash->mtd, spi->dev.of_node);
	flash->mtd.dev.parent	= &spi->dev;
	flash->mtd.type		= MTD_RAM;
	flash->mtd.flags	= MTD_CAP_RAM;
	flash->mtd.ग_लिखोsize	= 1;
	flash->mtd.size		= flash->caps->size;
	flash->mtd._पढ़ो	= mchp23k256_पढ़ो;
	flash->mtd._ग_लिखो	= mchp23k256_ग_लिखो;

	err = mtd_device_रेजिस्टर(&flash->mtd, data ? data->parts : शून्य,
				  data ? data->nr_parts : 0);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक mchp23k256_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा mchp23k256_flash *flash = spi_get_drvdata(spi);

	वापस mtd_device_unरेजिस्टर(&flash->mtd);
पूर्ण

अटल स्थिर काष्ठा of_device_id mchp23k256_of_table[] = अणु
	अणु
		.compatible = "microchip,mchp23k256",
		.data = &mchp23k256_caps,
	पूर्ण,
	अणु
		.compatible = "microchip,mchp23lcv1024",
		.data = &mchp23lcv1024_caps,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mchp23k256_of_table);

अटल काष्ठा spi_driver mchp23k256_driver = अणु
	.driver = अणु
		.name	= "mchp23k256",
		.of_match_table = of_match_ptr(mchp23k256_of_table),
	पूर्ण,
	.probe		= mchp23k256_probe,
	.हटाओ		= mchp23k256_हटाओ,
पूर्ण;

module_spi_driver(mchp23k256_driver);

MODULE_DESCRIPTION("MTD SPI driver for MCHP23K256 RAM chips");
MODULE_AUTHOR("Andrew Lunn <andre@lunn.ch>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:mchp23k256");
