<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sst25l.c
 *
 * Driver क्रम SST25L SPI Flash chips
 *
 * Copyright तऊ 2009 Bluewater Systems Ltd
 * Author: Andre Renaud <andre@bluewatersys.com>
 * Author: Ryan Mallon
 *
 * Based on m25p80.c
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>

/* Erases can take up to 3 seconds! */
#घोषणा MAX_READY_WAIT_JIFFIES	msecs_to_jअगरfies(3000)

#घोषणा SST25L_CMD_WRSR		0x01	/* Write status रेजिस्टर */
#घोषणा SST25L_CMD_WRDI		0x04	/* Write disable */
#घोषणा SST25L_CMD_RDSR		0x05	/* Read status रेजिस्टर */
#घोषणा SST25L_CMD_WREN		0x06	/* Write enable */
#घोषणा SST25L_CMD_READ		0x03	/* High speed पढ़ो */

#घोषणा SST25L_CMD_EWSR		0x50	/* Enable ग_लिखो status रेजिस्टर */
#घोषणा SST25L_CMD_SECTOR_ERASE	0x20	/* Erase sector */
#घोषणा SST25L_CMD_READ_ID	0x90	/* Read device ID */
#घोषणा SST25L_CMD_AAI_PROGRAM	0xaf	/* Auto address increment */

#घोषणा SST25L_STATUS_BUSY	(1 << 0)	/* Chip is busy */
#घोषणा SST25L_STATUS_WREN	(1 << 1)	/* Write enabled */
#घोषणा SST25L_STATUS_BP0	(1 << 2)	/* Block protection 0 */
#घोषणा SST25L_STATUS_BP1	(1 << 3)	/* Block protection 1 */

काष्ठा sst25l_flash अणु
	काष्ठा spi_device	*spi;
	काष्ठा mutex		lock;
	काष्ठा mtd_info		mtd;
पूर्ण;

काष्ठा flash_info अणु
	स्थिर अक्षर		*name;
	uपूर्णांक16_t		device_id;
	अचिन्हित		page_size;
	अचिन्हित		nr_pages;
	अचिन्हित		erase_size;
पूर्ण;

#घोषणा to_sst25l_flash(x) container_of(x, काष्ठा sst25l_flash, mtd)

अटल काष्ठा flash_info sst25l_flash_info[] = अणु
	अणु"sst25lf020a", 0xbf43, 256, 1024, 4096पूर्ण,
	अणु"sst25lf040a",	0xbf44,	256, 2048, 4096पूर्ण,
पूर्ण;

अटल पूर्णांक sst25l_status(काष्ठा sst25l_flash *flash, पूर्णांक *status)
अणु
	काष्ठा spi_message m;
	काष्ठा spi_transfer t;
	अचिन्हित अक्षर cmd_resp[2];
	पूर्णांक err;

	spi_message_init(&m);
	स_रखो(&t, 0, माप(काष्ठा spi_transfer));

	cmd_resp[0] = SST25L_CMD_RDSR;
	cmd_resp[1] = 0xff;
	t.tx_buf = cmd_resp;
	t.rx_buf = cmd_resp;
	t.len = माप(cmd_resp);
	spi_message_add_tail(&t, &m);
	err = spi_sync(flash->spi, &m);
	अगर (err < 0)
		वापस err;

	*status = cmd_resp[1];
	वापस 0;
पूर्ण

अटल पूर्णांक sst25l_ग_लिखो_enable(काष्ठा sst25l_flash *flash, पूर्णांक enable)
अणु
	अचिन्हित अक्षर command[2];
	पूर्णांक status, err;

	command[0] = enable ? SST25L_CMD_WREN : SST25L_CMD_WRDI;
	err = spi_ग_लिखो(flash->spi, command, 1);
	अगर (err)
		वापस err;

	command[0] = SST25L_CMD_EWSR;
	err = spi_ग_लिखो(flash->spi, command, 1);
	अगर (err)
		वापस err;

	command[0] = SST25L_CMD_WRSR;
	command[1] = enable ? 0 : SST25L_STATUS_BP0 | SST25L_STATUS_BP1;
	err = spi_ग_लिखो(flash->spi, command, 2);
	अगर (err)
		वापस err;

	अगर (enable) अणु
		err = sst25l_status(flash, &status);
		अगर (err)
			वापस err;
		अगर (!(status & SST25L_STATUS_WREN))
			वापस -EROFS;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sst25l_रुको_till_पढ़ोy(काष्ठा sst25l_flash *flash)
अणु
	अचिन्हित दीर्घ deadline;
	पूर्णांक status, err;

	deadline = jअगरfies + MAX_READY_WAIT_JIFFIES;
	करो अणु
		err = sst25l_status(flash, &status);
		अगर (err)
			वापस err;
		अगर (!(status & SST25L_STATUS_BUSY))
			वापस 0;

		cond_resched();
	पूर्ण जबतक (!समय_after_eq(jअगरfies, deadline));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक sst25l_erase_sector(काष्ठा sst25l_flash *flash, uपूर्णांक32_t offset)
अणु
	अचिन्हित अक्षर command[4];
	पूर्णांक err;

	err = sst25l_ग_लिखो_enable(flash, 1);
	अगर (err)
		वापस err;

	command[0] = SST25L_CMD_SECTOR_ERASE;
	command[1] = offset >> 16;
	command[2] = offset >> 8;
	command[3] = offset;
	err = spi_ग_लिखो(flash->spi, command, 4);
	अगर (err)
		वापस err;

	err = sst25l_रुको_till_पढ़ोy(flash);
	अगर (err)
		वापस err;

	वापस sst25l_ग_लिखो_enable(flash, 0);
पूर्ण

अटल पूर्णांक sst25l_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	काष्ठा sst25l_flash *flash = to_sst25l_flash(mtd);
	uपूर्णांक32_t addr, end;
	पूर्णांक err;

	/* Sanity checks */
	अगर ((uपूर्णांक32_t)instr->len % mtd->erasesize)
		वापस -EINVAL;

	अगर ((uपूर्णांक32_t)instr->addr % mtd->erasesize)
		वापस -EINVAL;

	addr = instr->addr;
	end = addr + instr->len;

	mutex_lock(&flash->lock);

	err = sst25l_रुको_till_पढ़ोy(flash);
	अगर (err) अणु
		mutex_unlock(&flash->lock);
		वापस err;
	पूर्ण

	जबतक (addr < end) अणु
		err = sst25l_erase_sector(flash, addr);
		अगर (err) अणु
			mutex_unlock(&flash->lock);
			dev_err(&flash->spi->dev, "Erase failed\n");
			वापस err;
		पूर्ण

		addr += mtd->erasesize;
	पूर्ण

	mutex_unlock(&flash->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक sst25l_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		       माप_प्रकार *retlen, अचिन्हित अक्षर *buf)
अणु
	काष्ठा sst25l_flash *flash = to_sst25l_flash(mtd);
	काष्ठा spi_transfer transfer[2];
	काष्ठा spi_message message;
	अचिन्हित अक्षर command[4];
	पूर्णांक ret;

	spi_message_init(&message);
	स_रखो(&transfer, 0, माप(transfer));

	command[0] = SST25L_CMD_READ;
	command[1] = from >> 16;
	command[2] = from >> 8;
	command[3] = from;

	transfer[0].tx_buf = command;
	transfer[0].len = माप(command);
	spi_message_add_tail(&transfer[0], &message);

	transfer[1].rx_buf = buf;
	transfer[1].len = len;
	spi_message_add_tail(&transfer[1], &message);

	mutex_lock(&flash->lock);

	/* Wait क्रम previous ग_लिखो/erase to complete */
	ret = sst25l_रुको_till_पढ़ोy(flash);
	अगर (ret) अणु
		mutex_unlock(&flash->lock);
		वापस ret;
	पूर्ण

	spi_sync(flash->spi, &message);

	अगर (retlen && message.actual_length > माप(command))
		*retlen += message.actual_length - माप(command);

	mutex_unlock(&flash->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक sst25l_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
			माप_प्रकार *retlen, स्थिर अचिन्हित अक्षर *buf)
अणु
	काष्ठा sst25l_flash *flash = to_sst25l_flash(mtd);
	पूर्णांक i, j, ret, bytes, copied = 0;
	अचिन्हित अक्षर command[5];

	अगर ((uपूर्णांक32_t)to % mtd->ग_लिखोsize)
		वापस -EINVAL;

	mutex_lock(&flash->lock);

	ret = sst25l_ग_लिखो_enable(flash, 1);
	अगर (ret)
		जाओ out;

	क्रम (i = 0; i < len; i += mtd->ग_लिखोsize) अणु
		ret = sst25l_रुको_till_पढ़ोy(flash);
		अगर (ret)
			जाओ out;

		/* Write the first byte of the page */
		command[0] = SST25L_CMD_AAI_PROGRAM;
		command[1] = (to + i) >> 16;
		command[2] = (to + i) >> 8;
		command[3] = (to + i);
		command[4] = buf[i];
		ret = spi_ग_लिखो(flash->spi, command, 5);
		अगर (ret < 0)
			जाओ out;
		copied++;

		/*
		 * Write the reमुख्यing bytes using स्वतः address
		 * increment mode
		 */
		bytes = min_t(uपूर्णांक32_t, mtd->ग_लिखोsize, len - i);
		क्रम (j = 1; j < bytes; j++, copied++) अणु
			ret = sst25l_रुको_till_पढ़ोy(flash);
			अगर (ret)
				जाओ out;

			command[1] = buf[i + j];
			ret = spi_ग_लिखो(flash->spi, command, 2);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	ret = sst25l_ग_लिखो_enable(flash, 0);

	अगर (retlen)
		*retlen = copied;

	mutex_unlock(&flash->lock);
	वापस ret;
पूर्ण

अटल काष्ठा flash_info *sst25l_match_device(काष्ठा spi_device *spi)
अणु
	काष्ठा flash_info *flash_info = शून्य;
	काष्ठा spi_message m;
	काष्ठा spi_transfer t;
	अचिन्हित अक्षर cmd_resp[6];
	पूर्णांक i, err;
	uपूर्णांक16_t id;

	spi_message_init(&m);
	स_रखो(&t, 0, माप(काष्ठा spi_transfer));

	cmd_resp[0] = SST25L_CMD_READ_ID;
	cmd_resp[1] = 0;
	cmd_resp[2] = 0;
	cmd_resp[3] = 0;
	cmd_resp[4] = 0xff;
	cmd_resp[5] = 0xff;
	t.tx_buf = cmd_resp;
	t.rx_buf = cmd_resp;
	t.len = माप(cmd_resp);
	spi_message_add_tail(&t, &m);
	err = spi_sync(spi, &m);
	अगर (err < 0) अणु
		dev_err(&spi->dev, "error reading device id\n");
		वापस शून्य;
	पूर्ण

	id = (cmd_resp[4] << 8) | cmd_resp[5];

	क्रम (i = 0; i < ARRAY_SIZE(sst25l_flash_info); i++)
		अगर (sst25l_flash_info[i].device_id == id)
			flash_info = &sst25l_flash_info[i];

	अगर (!flash_info)
		dev_err(&spi->dev, "unknown id %.4x\n", id);

	वापस flash_info;
पूर्ण

अटल पूर्णांक sst25l_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा flash_info *flash_info;
	काष्ठा sst25l_flash *flash;
	काष्ठा flash_platक्रमm_data *data;
	पूर्णांक ret;

	flash_info = sst25l_match_device(spi);
	अगर (!flash_info)
		वापस -ENODEV;

	flash = devm_kzalloc(&spi->dev, माप(*flash), GFP_KERNEL);
	अगर (!flash)
		वापस -ENOMEM;

	flash->spi = spi;
	mutex_init(&flash->lock);
	spi_set_drvdata(spi, flash);

	data = dev_get_platdata(&spi->dev);
	अगर (data && data->name)
		flash->mtd.name = data->name;

	flash->mtd.dev.parent   = &spi->dev;
	flash->mtd.type		= MTD_NORFLASH;
	flash->mtd.flags	= MTD_CAP_NORFLASH;
	flash->mtd.erasesize	= flash_info->erase_size;
	flash->mtd.ग_लिखोsize	= flash_info->page_size;
	flash->mtd.ग_लिखोbufsize	= flash_info->page_size;
	flash->mtd.size		= flash_info->page_size * flash_info->nr_pages;
	flash->mtd._erase	= sst25l_erase;
	flash->mtd._पढ़ो		= sst25l_पढ़ो;
	flash->mtd._ग_लिखो 	= sst25l_ग_लिखो;

	dev_info(&spi->dev, "%s (%lld KiB)\n", flash_info->name,
		 (दीर्घ दीर्घ)flash->mtd.size >> 10);

	pr_debug("mtd .name = %s, .size = 0x%llx (%lldMiB) "
	      ".erasesize = 0x%.8x (%uKiB) .numeraseregions = %d\n",
	      flash->mtd.name,
	      (दीर्घ दीर्घ)flash->mtd.size, (दीर्घ दीर्घ)(flash->mtd.size >> 20),
	      flash->mtd.erasesize, flash->mtd.erasesize / 1024,
	      flash->mtd.numeraseregions);


	ret = mtd_device_रेजिस्टर(&flash->mtd, data ? data->parts : शून्य,
				  data ? data->nr_parts : 0);
	अगर (ret)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक sst25l_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा sst25l_flash *flash = spi_get_drvdata(spi);

	वापस mtd_device_unरेजिस्टर(&flash->mtd);
पूर्ण

अटल काष्ठा spi_driver sst25l_driver = अणु
	.driver = अणु
		.name	= "sst25l",
	पूर्ण,
	.probe		= sst25l_probe,
	.हटाओ		= sst25l_हटाओ,
पूर्ण;

module_spi_driver(sst25l_driver);

MODULE_DESCRIPTION("MTD SPI driver for SST25L Flash chips");
MODULE_AUTHOR("Andre Renaud <andre@bluewatersys.com>, "
	      "Ryan Mallon");
MODULE_LICENSE("GPL");
