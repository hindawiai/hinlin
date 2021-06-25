<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Aपंचांगel AT45xxx DataFlash MTD driver क्रम lightweight SPI framework
 *
 * Largely derived from at91_dataflash.c:
 *  Copyright (C) 2003-2005 SAN People (Pty) Ltd
*/
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/math64.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>

/*
 * DataFlash is a kind of SPI flash.  Most AT45 chips have two buffers in
 * each chip, which may be used क्रम द्विगुन buffered I/O; but this driver
 * करोesn't (yet) use these क्रम any kind of i/o overlap or prefetching.
 *
 * Someबार DataFlash is packaged in MMC-क्रमmat cards, although the
 * MMC stack can't (yet?) distinguish between MMC and DataFlash
 * protocols during क्रमागतeration.
 */

/* पढ़ोs can bypass the buffers */
#घोषणा OP_READ_CONTINUOUS	0xE8
#घोषणा OP_READ_PAGE		0xD2

/* group B requests can run even जबतक status reports "busy" */
#घोषणा OP_READ_STATUS		0xD7	/* group B */

/* move data between host and buffer */
#घोषणा OP_READ_BUFFER1		0xD4	/* group B */
#घोषणा OP_READ_BUFFER2		0xD6	/* group B */
#घोषणा OP_WRITE_BUFFER1	0x84	/* group B */
#घोषणा OP_WRITE_BUFFER2	0x87	/* group B */

/* erasing flash */
#घोषणा OP_ERASE_PAGE		0x81
#घोषणा OP_ERASE_BLOCK		0x50

/* move data between buffer and flash */
#घोषणा OP_TRANSFER_BUF1	0x53
#घोषणा OP_TRANSFER_BUF2	0x55
#घोषणा OP_MREAD_BUFFER1	0xD4
#घोषणा OP_MREAD_BUFFER2	0xD6
#घोषणा OP_MWERASE_BUFFER1	0x83
#घोषणा OP_MWERASE_BUFFER2	0x86
#घोषणा OP_MWRITE_BUFFER1	0x88	/* sector must be pre-erased */
#घोषणा OP_MWRITE_BUFFER2	0x89	/* sector must be pre-erased */

/* ग_लिखो to buffer, then ग_लिखो-erase to flash */
#घोषणा OP_PROGRAM_VIA_BUF1	0x82
#घोषणा OP_PROGRAM_VIA_BUF2	0x85

/* compare buffer to flash */
#घोषणा OP_COMPARE_BUF1		0x60
#घोषणा OP_COMPARE_BUF2		0x61

/* पढ़ो flash to buffer, then ग_लिखो-erase to flash */
#घोषणा OP_REWRITE_VIA_BUF1	0x58
#घोषणा OP_REWRITE_VIA_BUF2	0x59

/* newer chips report JEDEC manufacturer and device IDs; chip
 * serial number and OTP bits; and per-sector ग_लिखोprotect.
 */
#घोषणा OP_READ_ID		0x9F
#घोषणा OP_READ_SECURITY	0x77
#घोषणा OP_WRITE_SECURITY_REVC	0x9A
#घोषणा OP_WRITE_SECURITY	0x9B	/* revision D */

#घोषणा CFI_MFR_ATMEL		0x1F

#घोषणा DATAFLASH_SHIFT_EXTID	24
#घोषणा DATAFLASH_SHIFT_ID	40

काष्ठा dataflash अणु
	u8			command[4];
	अक्षर			name[24];

	अचिन्हित लघु		page_offset;	/* offset in flash address */
	अचिन्हित पूर्णांक		page_size;	/* of bytes per page */

	काष्ठा mutex		lock;
	काष्ठा spi_device	*spi;

	काष्ठा mtd_info		mtd;
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id dataflash_dt_ids[] = अणु
	अणु .compatible = "atmel,at45", पूर्ण,
	अणु .compatible = "atmel,dataflash", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dataflash_dt_ids);
#पूर्ण_अगर

/* ......................................................................... */

/*
 * Return the status of the DataFlash device.
 */
अटल अंतरभूत पूर्णांक dataflash_status(काष्ठा spi_device *spi)
अणु
	/* NOTE:  at45db321c over 25 MHz wants to ग_लिखो
	 * a dummy byte after the opcode...
	 */
	वापस spi_w8r8(spi, OP_READ_STATUS);
पूर्ण

/*
 * Poll the DataFlash device until it is READY.
 * This usually takes 5-20 msec or so; more क्रम sector erase.
 */
अटल पूर्णांक dataflash_रुकोपढ़ोy(काष्ठा spi_device *spi)
अणु
	पूर्णांक	status;

	क्रम (;;) अणु
		status = dataflash_status(spi);
		अगर (status < 0) अणु
			dev_dbg(&spi->dev, "status %d?\n", status);
			status = 0;
		पूर्ण

		अगर (status & (1 << 7))	/* RDY/nBSY */
			वापस status;

		usleep_range(3000, 4000);
	पूर्ण
पूर्ण

/* ......................................................................... */

/*
 * Erase pages of flash.
 */
अटल पूर्णांक dataflash_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	काष्ठा dataflash	*priv = mtd->priv;
	काष्ठा spi_device	*spi = priv->spi;
	काष्ठा spi_transfer	x = अणु पूर्ण;
	काष्ठा spi_message	msg;
	अचिन्हित		blocksize = priv->page_size << 3;
	u8			*command;
	u32			rem;

	dev_dbg(&spi->dev, "erase addr=0x%llx len 0x%llx\n",
		(दीर्घ दीर्घ)instr->addr, (दीर्घ दीर्घ)instr->len);

	भाग_u64_rem(instr->len, priv->page_size, &rem);
	अगर (rem)
		वापस -EINVAL;
	भाग_u64_rem(instr->addr, priv->page_size, &rem);
	अगर (rem)
		वापस -EINVAL;

	spi_message_init(&msg);

	x.tx_buf = command = priv->command;
	x.len = 4;
	spi_message_add_tail(&x, &msg);

	mutex_lock(&priv->lock);
	जबतक (instr->len > 0) अणु
		अचिन्हित पूर्णांक	pageaddr;
		पूर्णांक		status;
		पूर्णांक		करो_block;

		/* Calculate flash page address; use block erase (क्रम speed) अगर
		 * we're at a block boundary and need to erase the whole block.
		 */
		pageaddr = भाग_u64(instr->addr, priv->page_size);
		करो_block = (pageaddr & 0x7) == 0 && instr->len >= blocksize;
		pageaddr = pageaddr << priv->page_offset;

		command[0] = करो_block ? OP_ERASE_BLOCK : OP_ERASE_PAGE;
		command[1] = (u8)(pageaddr >> 16);
		command[2] = (u8)(pageaddr >> 8);
		command[3] = 0;

		dev_dbg(&spi->dev, "ERASE %s: (%x) %x %x %x [%i]\n",
			करो_block ? "block" : "page",
			command[0], command[1], command[2], command[3],
			pageaddr);

		status = spi_sync(spi, &msg);
		(व्योम) dataflash_रुकोपढ़ोy(spi);

		अगर (status < 0) अणु
			dev_err(&spi->dev, "erase %x, err %d\n",
				pageaddr, status);
			/* REVISIT:  can retry instr->retries बार; or
			 * giveup and instr->fail_addr = instr->addr;
			 */
			जारी;
		पूर्ण

		अगर (करो_block) अणु
			instr->addr += blocksize;
			instr->len -= blocksize;
		पूर्ण अन्यथा अणु
			instr->addr += priv->page_size;
			instr->len -= priv->page_size;
		पूर्ण
	पूर्ण
	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

/*
 * Read from the DataFlash device.
 *   from   : Start offset in flash device
 *   len    : Amount to पढ़ो
 *   retlen : About of data actually पढ़ो
 *   buf    : Buffer containing the data
 */
अटल पूर्णांक dataflash_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			       माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा dataflash	*priv = mtd->priv;
	काष्ठा spi_transfer	x[2] = अणु पूर्ण;
	काष्ठा spi_message	msg;
	अचिन्हित पूर्णांक		addr;
	u8			*command;
	पूर्णांक			status;

	dev_dbg(&priv->spi->dev, "read 0x%x..0x%x\n",
		  (अचिन्हित पूर्णांक)from, (अचिन्हित पूर्णांक)(from + len));

	/* Calculate flash page/byte address */
	addr = (((अचिन्हित)from / priv->page_size) << priv->page_offset)
		+ ((अचिन्हित)from % priv->page_size);

	command = priv->command;

	dev_dbg(&priv->spi->dev, "READ: (%x) %x %x %x\n",
		command[0], command[1], command[2], command[3]);

	spi_message_init(&msg);

	x[0].tx_buf = command;
	x[0].len = 8;
	spi_message_add_tail(&x[0], &msg);

	x[1].rx_buf = buf;
	x[1].len = len;
	spi_message_add_tail(&x[1], &msg);

	mutex_lock(&priv->lock);

	/* Continuous पढ़ो, max घड़ी = f(car) which may be less than
	 * the peak rate available.  Some chips support commands with
	 * fewer "don't care" bytes.  Both buffers stay unchanged.
	 */
	command[0] = OP_READ_CONTINUOUS;
	command[1] = (u8)(addr >> 16);
	command[2] = (u8)(addr >> 8);
	command[3] = (u8)(addr >> 0);
	/* plus 4 "don't care" bytes */

	status = spi_sync(priv->spi, &msg);
	mutex_unlock(&priv->lock);

	अगर (status >= 0) अणु
		*retlen = msg.actual_length - 8;
		status = 0;
	पूर्ण अन्यथा
		dev_dbg(&priv->spi->dev, "read %x..%x --> %d\n",
			(अचिन्हित)from, (अचिन्हित)(from + len),
			status);
	वापस status;
पूर्ण

/*
 * Write to the DataFlash device.
 *   to     : Start offset in flash device
 *   len    : Amount to ग_लिखो
 *   retlen : Amount of data actually written
 *   buf    : Buffer containing the data
 */
अटल पूर्णांक dataflash_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
				माप_प्रकार * retlen, स्थिर u_अक्षर * buf)
अणु
	काष्ठा dataflash	*priv = mtd->priv;
	काष्ठा spi_device	*spi = priv->spi;
	काष्ठा spi_transfer	x[2] = अणु पूर्ण;
	काष्ठा spi_message	msg;
	अचिन्हित पूर्णांक		pageaddr, addr, offset, ग_लिखोlen;
	माप_प्रकार			reमुख्यing = len;
	u_अक्षर			*ग_लिखोbuf = (u_अक्षर *) buf;
	पूर्णांक			status = -EINVAL;
	u8			*command;

	dev_dbg(&spi->dev, "write 0x%x..0x%x\n",
		(अचिन्हित पूर्णांक)to, (अचिन्हित पूर्णांक)(to + len));

	spi_message_init(&msg);

	x[0].tx_buf = command = priv->command;
	x[0].len = 4;
	spi_message_add_tail(&x[0], &msg);

	pageaddr = ((अचिन्हित)to / priv->page_size);
	offset = ((अचिन्हित)to % priv->page_size);
	अगर (offset + len > priv->page_size)
		ग_लिखोlen = priv->page_size - offset;
	अन्यथा
		ग_लिखोlen = len;

	mutex_lock(&priv->lock);
	जबतक (reमुख्यing > 0) अणु
		dev_dbg(&spi->dev, "write @ %i:%i len=%i\n",
			pageaddr, offset, ग_लिखोlen);

		/* REVISIT:
		 * (a) each page in a sector must be rewritten at least
		 *     once every 10K sibling erase/program operations.
		 * (b) क्रम pages that are alपढ़ोy erased, we could
		 *     use WRITE+MWRITE not PROGRAM क्रम ~30% speedup.
		 * (c) WRITE to buffer could be करोne जबतक रुकोing क्रम
		 *     a previous MWRITE/MWERASE to complete ...
		 * (d) error handling here seems to be mostly missing.
		 *
		 * Two persistent bits per page, plus a per-sector counter,
		 * could support (a) and (b) ... we might consider using
		 * the second half of sector zero, which is just one block,
		 * to track that state.  (On AT91, that sector should also
		 * support boot-from-DataFlash.)
		 */

		addr = pageaddr << priv->page_offset;

		/* (1) Maybe transfer partial page to Buffer1 */
		अगर (ग_लिखोlen != priv->page_size) अणु
			command[0] = OP_TRANSFER_BUF1;
			command[1] = (addr & 0x00FF0000) >> 16;
			command[2] = (addr & 0x0000FF00) >> 8;
			command[3] = 0;

			dev_dbg(&spi->dev, "TRANSFER: (%x) %x %x %x\n",
				command[0], command[1], command[2], command[3]);

			status = spi_sync(spi, &msg);
			अगर (status < 0)
				dev_dbg(&spi->dev, "xfer %u -> %d\n",
					addr, status);

			(व्योम) dataflash_रुकोपढ़ोy(priv->spi);
		पूर्ण

		/* (2) Program full page via Buffer1 */
		addr += offset;
		command[0] = OP_PROGRAM_VIA_BUF1;
		command[1] = (addr & 0x00FF0000) >> 16;
		command[2] = (addr & 0x0000FF00) >> 8;
		command[3] = (addr & 0x000000FF);

		dev_dbg(&spi->dev, "PROGRAM: (%x) %x %x %x\n",
			command[0], command[1], command[2], command[3]);

		x[1].tx_buf = ग_लिखोbuf;
		x[1].len = ग_लिखोlen;
		spi_message_add_tail(x + 1, &msg);
		status = spi_sync(spi, &msg);
		spi_transfer_del(x + 1);
		अगर (status < 0)
			dev_dbg(&spi->dev, "pgm %u/%u -> %d\n",
				addr, ग_लिखोlen, status);

		(व्योम) dataflash_रुकोपढ़ोy(priv->spi);


#अगर_घोषित CONFIG_MTD_DATAFLASH_WRITE_VERIFY

		/* (3) Compare to Buffer1 */
		addr = pageaddr << priv->page_offset;
		command[0] = OP_COMPARE_BUF1;
		command[1] = (addr & 0x00FF0000) >> 16;
		command[2] = (addr & 0x0000FF00) >> 8;
		command[3] = 0;

		dev_dbg(&spi->dev, "COMPARE: (%x) %x %x %x\n",
			command[0], command[1], command[2], command[3]);

		status = spi_sync(spi, &msg);
		अगर (status < 0)
			dev_dbg(&spi->dev, "compare %u -> %d\n",
				addr, status);

		status = dataflash_रुकोपढ़ोy(priv->spi);

		/* Check result of the compare operation */
		अगर (status & (1 << 6)) अणु
			dev_err(&spi->dev, "compare page %u, err %d\n",
				pageaddr, status);
			reमुख्यing = 0;
			status = -EIO;
			अवरोध;
		पूर्ण अन्यथा
			status = 0;

#पूर्ण_अगर	/* CONFIG_MTD_DATAFLASH_WRITE_VERIFY */

		reमुख्यing = reमुख्यing - ग_लिखोlen;
		pageaddr++;
		offset = 0;
		ग_लिखोbuf += ग_लिखोlen;
		*retlen += ग_लिखोlen;

		अगर (reमुख्यing > priv->page_size)
			ग_लिखोlen = priv->page_size;
		अन्यथा
			ग_लिखोlen = reमुख्यing;
	पूर्ण
	mutex_unlock(&priv->lock);

	वापस status;
पूर्ण

/* ......................................................................... */

#अगर_घोषित CONFIG_MTD_DATAFLASH_OTP

अटल पूर्णांक dataflash_get_otp_info(काष्ठा mtd_info *mtd, माप_प्रकार len,
				  माप_प्रकार *retlen, काष्ठा otp_info *info)
अणु
	/* Report both blocks as identical:  bytes 0..64, locked.
	 * Unless the user block changed from all-ones, we can't
	 * tell whether it's still writable; so we assume it isn't.
	 */
	info->start = 0;
	info->length = 64;
	info->locked = 1;
	*retlen = माप(*info);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार otp_पढ़ो(काष्ठा spi_device *spi, अचिन्हित base,
		u8 *buf, loff_t off, माप_प्रकार len)
अणु
	काष्ठा spi_message	m;
	माप_प्रकार			l;
	u8			*scratch;
	काष्ठा spi_transfer	t;
	पूर्णांक			status;

	अगर (off > 64)
		वापस -EINVAL;

	अगर ((off + len) > 64)
		len = 64 - off;

	spi_message_init(&m);

	l = 4 + base + off + len;
	scratch = kzalloc(l, GFP_KERNEL);
	अगर (!scratch)
		वापस -ENOMEM;

	/* OUT: OP_READ_SECURITY, 3 करोn't-care bytes, zeroes
	 * IN:  ignore 4 bytes, data bytes 0..N (max 127)
	 */
	scratch[0] = OP_READ_SECURITY;

	स_रखो(&t, 0, माप t);
	t.tx_buf = scratch;
	t.rx_buf = scratch;
	t.len = l;
	spi_message_add_tail(&t, &m);

	dataflash_रुकोपढ़ोy(spi);

	status = spi_sync(spi, &m);
	अगर (status >= 0) अणु
		स_नकल(buf, scratch + 4 + base + off, len);
		status = len;
	पूर्ण

	kमुक्त(scratch);
	वापस status;
पूर्ण

अटल पूर्णांक dataflash_पढ़ो_fact_otp(काष्ठा mtd_info *mtd,
		loff_t from, माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा dataflash	*priv = mtd->priv;
	पूर्णांक			status;

	/* 64 bytes, from 0..63 ... start at 64 on-chip */
	mutex_lock(&priv->lock);
	status = otp_पढ़ो(priv->spi, 64, buf, from, len);
	mutex_unlock(&priv->lock);

	अगर (status < 0)
		वापस status;
	*retlen = status;
	वापस 0;
पूर्ण

अटल पूर्णांक dataflash_पढ़ो_user_otp(काष्ठा mtd_info *mtd,
		loff_t from, माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा dataflash	*priv = mtd->priv;
	पूर्णांक			status;

	/* 64 bytes, from 0..63 ... start at 0 on-chip */
	mutex_lock(&priv->lock);
	status = otp_पढ़ो(priv->spi, 0, buf, from, len);
	mutex_unlock(&priv->lock);

	अगर (status < 0)
		वापस status;
	*retlen = status;
	वापस 0;
पूर्ण

अटल पूर्णांक dataflash_ग_लिखो_user_otp(काष्ठा mtd_info *mtd,
		loff_t from, माप_प्रकार len, माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा spi_message	m;
	स्थिर माप_प्रकार		l = 4 + 64;
	u8			*scratch;
	काष्ठा spi_transfer	t;
	काष्ठा dataflash	*priv = mtd->priv;
	पूर्णांक			status;

	अगर (from >= 64) अणु
		/*
		 * Attempting to ग_लिखो beyond the end of OTP memory,
		 * no data can be written.
		 */
		*retlen = 0;
		वापस 0;
	पूर्ण

	/* Truncate the ग_लिखो to fit पूर्णांकo OTP memory. */
	अगर ((from + len) > 64)
		len = 64 - from;

	/* OUT: OP_WRITE_SECURITY, 3 zeroes, 64 data-or-zero bytes
	 * IN:  ignore all
	 */
	scratch = kzalloc(l, GFP_KERNEL);
	अगर (!scratch)
		वापस -ENOMEM;
	scratch[0] = OP_WRITE_SECURITY;
	स_नकल(scratch + 4 + from, buf, len);

	spi_message_init(&m);

	स_रखो(&t, 0, माप t);
	t.tx_buf = scratch;
	t.len = l;
	spi_message_add_tail(&t, &m);

	/* Write the OTP bits, अगर they've not yet been written.
	 * This modअगरies SRAM buffer1.
	 */
	mutex_lock(&priv->lock);
	dataflash_रुकोपढ़ोy(priv->spi);
	status = spi_sync(priv->spi, &m);
	mutex_unlock(&priv->lock);

	kमुक्त(scratch);

	अगर (status >= 0) अणु
		status = 0;
		*retlen = len;
	पूर्ण
	वापस status;
पूर्ण

अटल अक्षर *otp_setup(काष्ठा mtd_info *device, अक्षर revision)
अणु
	device->_get_fact_prot_info = dataflash_get_otp_info;
	device->_पढ़ो_fact_prot_reg = dataflash_पढ़ो_fact_otp;
	device->_get_user_prot_info = dataflash_get_otp_info;
	device->_पढ़ो_user_prot_reg = dataflash_पढ़ो_user_otp;

	/* rev c parts (at45db321c and at45db1281 only!) use a
	 * dअगरferent ग_लिखो procedure; not (yet?) implemented.
	 */
	अगर (revision > 'c')
		device->_ग_लिखो_user_prot_reg = dataflash_ग_लिखो_user_otp;

	वापस ", OTP";
पूर्ण

#अन्यथा

अटल अक्षर *otp_setup(काष्ठा mtd_info *device, अक्षर revision)
अणु
	वापस " (OTP)";
पूर्ण

#पूर्ण_अगर

/* ......................................................................... */

/*
 * Register DataFlash device with MTD subप्रणाली.
 */
अटल पूर्णांक add_dataflash_otp(काष्ठा spi_device *spi, अक्षर *name, पूर्णांक nr_pages,
			     पूर्णांक pagesize, पूर्णांक pageoffset, अक्षर revision)
अणु
	काष्ठा dataflash		*priv;
	काष्ठा mtd_info			*device;
	काष्ठा flash_platक्रमm_data	*pdata = dev_get_platdata(&spi->dev);
	अक्षर				*otp_tag = "";
	पूर्णांक				err = 0;

	priv = kzalloc(माप *priv, GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_init(&priv->lock);
	priv->spi = spi;
	priv->page_size = pagesize;
	priv->page_offset = pageoffset;

	/* name must be usable with cmdlinepart */
	प्र_लिखो(priv->name, "spi%d.%d-%s",
			spi->master->bus_num, spi->chip_select,
			name);

	device = &priv->mtd;
	device->name = (pdata && pdata->name) ? pdata->name : priv->name;
	device->size = nr_pages * pagesize;
	device->erasesize = pagesize;
	device->ग_लिखोsize = pagesize;
	device->type = MTD_DATAFLASH;
	device->flags = MTD_WRITEABLE;
	device->_erase = dataflash_erase;
	device->_पढ़ो = dataflash_पढ़ो;
	device->_ग_लिखो = dataflash_ग_लिखो;
	device->priv = priv;

	device->dev.parent = &spi->dev;
	mtd_set_of_node(device, spi->dev.of_node);

	अगर (revision >= 'c')
		otp_tag = otp_setup(device, revision);

	dev_info(&spi->dev, "%s (%lld KBytes) pagesize %d bytes%s\n",
			name, (दीर्घ दीर्घ)((device->size + 1023) >> 10),
			pagesize, otp_tag);
	spi_set_drvdata(spi, priv);

	err = mtd_device_रेजिस्टर(device,
			pdata ? pdata->parts : शून्य,
			pdata ? pdata->nr_parts : 0);

	अगर (!err)
		वापस 0;

	kमुक्त(priv);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक add_dataflash(काष्ठा spi_device *spi, अक्षर *name,
				पूर्णांक nr_pages, पूर्णांक pagesize, पूर्णांक pageoffset)
अणु
	वापस add_dataflash_otp(spi, name, nr_pages, pagesize,
			pageoffset, 0);
पूर्ण

काष्ठा flash_info अणु
	अक्षर		*name;

	/* JEDEC id has a high byte of zero plus three data bytes:
	 * the manufacturer id, then a two byte device id.
	 */
	u64		jedec_id;

	/* The size listed here is what works with OP_ERASE_PAGE. */
	अचिन्हित	nr_pages;
	u16		pagesize;
	u16		pageoffset;

	u16		flags;
#घोषणा SUP_EXTID	0x0004		/* supports extended ID data */
#घोषणा SUP_POW2PS	0x0002		/* supports 2^N byte pages */
#घोषणा IS_POW2PS	0x0001		/* uses 2^N byte pages */
पूर्ण;

अटल काष्ठा flash_info dataflash_data[] = अणु

	/*
	 * NOTE:  chips with SUP_POW2PS (rev D and up) need two entries,
	 * one with IS_POW2PS and the other without.  The entry with the
	 * non-2^N byte page size can't name exact chip revisions without
	 * losing backwards compatibility क्रम cmdlinepart.
	 *
	 * These newer chips also support 128-byte security रेजिस्टरs (with
	 * 64 bytes one-समय-programmable) and software ग_लिखो-protection.
	 */
	अणु "AT45DB011B",  0x1f2200, 512, 264, 9, SUP_POW2PSपूर्ण,
	अणु "at45db011d",  0x1f2200, 512, 256, 8, SUP_POW2PS | IS_POW2PSपूर्ण,

	अणु "AT45DB021B",  0x1f2300, 1024, 264, 9, SUP_POW2PSपूर्ण,
	अणु "at45db021d",  0x1f2300, 1024, 256, 8, SUP_POW2PS | IS_POW2PSपूर्ण,

	अणु "AT45DB041x",  0x1f2400, 2048, 264, 9, SUP_POW2PSपूर्ण,
	अणु "at45db041d",  0x1f2400, 2048, 256, 8, SUP_POW2PS | IS_POW2PSपूर्ण,

	अणु "AT45DB081B",  0x1f2500, 4096, 264, 9, SUP_POW2PSपूर्ण,
	अणु "at45db081d",  0x1f2500, 4096, 256, 8, SUP_POW2PS | IS_POW2PSपूर्ण,

	अणु "AT45DB161x",  0x1f2600, 4096, 528, 10, SUP_POW2PSपूर्ण,
	अणु "at45db161d",  0x1f2600, 4096, 512, 9, SUP_POW2PS | IS_POW2PSपूर्ण,

	अणु "AT45DB321x",  0x1f2700, 8192, 528, 10, 0पूर्ण,		/* rev C */

	अणु "AT45DB321x",  0x1f2701, 8192, 528, 10, SUP_POW2PSपूर्ण,
	अणु "at45db321d",  0x1f2701, 8192, 512, 9, SUP_POW2PS | IS_POW2PSपूर्ण,

	अणु "AT45DB642x",  0x1f2800, 8192, 1056, 11, SUP_POW2PSपूर्ण,
	अणु "at45db642d",  0x1f2800, 8192, 1024, 10, SUP_POW2PS | IS_POW2PSपूर्ण,

	अणु "AT45DB641E",  0x1f28000100ULL, 32768, 264, 9, SUP_EXTID | SUP_POW2PSपूर्ण,
	अणु "at45db641e",  0x1f28000100ULL, 32768, 256, 8, SUP_EXTID | SUP_POW2PS | IS_POW2PSपूर्ण,
पूर्ण;

अटल काष्ठा flash_info *jedec_lookup(काष्ठा spi_device *spi,
				       u64 jedec, bool use_extid)
अणु
	काष्ठा flash_info *info;
	पूर्णांक status;

	क्रम (info = dataflash_data;
	     info < dataflash_data + ARRAY_SIZE(dataflash_data);
	     info++) अणु
		अगर (use_extid && !(info->flags & SUP_EXTID))
			जारी;

		अगर (info->jedec_id == jedec) अणु
			dev_dbg(&spi->dev, "OTP, sector protect%s\n",
				(info->flags & SUP_POW2PS) ?
				", binary pagesize" : "");
			अगर (info->flags & SUP_POW2PS) अणु
				status = dataflash_status(spi);
				अगर (status < 0) अणु
					dev_dbg(&spi->dev, "status error %d\n",
						status);
					वापस ERR_PTR(status);
				पूर्ण
				अगर (status & 0x1) अणु
					अगर (info->flags & IS_POW2PS)
						वापस info;
				पूर्ण अन्यथा अणु
					अगर (!(info->flags & IS_POW2PS))
						वापस info;
				पूर्ण
			पूर्ण अन्यथा
				वापस info;
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल काष्ठा flash_info *jedec_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	u8 code = OP_READ_ID;
	u64 jedec;
	u8 id[माप(jedec)] = अणु0पूर्ण;
	स्थिर अचिन्हित पूर्णांक id_size = 5;
	काष्ठा flash_info *info;

	/*
	 * JEDEC also defines an optional "extended device information"
	 * string क्रम after venकरोr-specअगरic data, after the three bytes
	 * we use here.  Supporting some chips might require using it.
	 *
	 * If the venकरोr ID isn't Atmel's (0x1f), assume this call failed.
	 * That's not an error; only rev C and newer chips handle it, and
	 * only Aपंचांगel sells these chips.
	 */
	ret = spi_ग_लिखो_then_पढ़ो(spi, &code, 1, id, id_size);
	अगर (ret < 0) अणु
		dev_dbg(&spi->dev, "error %d reading JEDEC ID\n", ret);
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (id[0] != CFI_MFR_ATMEL)
		वापस शून्य;

	jedec = be64_to_cpup((__be64 *)id);

	/*
	 * First, try to match device using extended device
	 * inक्रमmation
	 */
	info = jedec_lookup(spi, jedec >> DATAFLASH_SHIFT_EXTID, true);
	अगर (!IS_ERR(info))
		वापस info;
	/*
	 * If that fails, make another pass using regular ID
	 * inक्रमmation
	 */
	info = jedec_lookup(spi, jedec >> DATAFLASH_SHIFT_ID, false);
	अगर (!IS_ERR(info))
		वापस info;
	/*
	 * Treat other chips as errors ... we won't know the right page
	 * size (it might be binary) even when we can tell which density
	 * class is involved (legacy chip id scheme).
	 */
	dev_warn(&spi->dev, "JEDEC id %016llx not handled\n", jedec);
	वापस ERR_PTR(-ENODEV);
पूर्ण

/*
 * Detect and initialize DataFlash device, using JEDEC IDs on newer chips
 * or अन्यथा the ID code embedded in the status bits:
 *
 *   Device      Density         ID code          #Pages PageSize  Offset
 *   AT45DB011B  1Mbit   (128K)  xx0011xx (0x0c)    512    264      9
 *   AT45DB021B  2Mbit   (256K)  xx0101xx (0x14)   1024    264      9
 *   AT45DB041B  4Mbit   (512K)  xx0111xx (0x1c)   2048    264      9
 *   AT45DB081B  8Mbit   (1M)    xx1001xx (0x24)   4096    264      9
 *   AT45DB0161B 16Mbit  (2M)    xx1011xx (0x2c)   4096    528     10
 *   AT45DB0321B 32Mbit  (4M)    xx1101xx (0x34)   8192    528     10
 *   AT45DB0642  64Mbit  (8M)    xx111xxx (0x3c)   8192   1056     11
 *   AT45DB1282  128Mbit (16M)   xx0100xx (0x10)  16384   1056     11
 */
अटल पूर्णांक dataflash_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक status;
	काष्ठा flash_info	*info;

	/*
	 * Try to detect dataflash by JEDEC ID.
	 * If it succeeds we know we have either a C or D part.
	 * D will support घातer of 2 pagesize option.
	 * Both support the security रेजिस्टर, though with dअगरferent
	 * ग_लिखो procedures.
	 */
	info = jedec_probe(spi);
	अगर (IS_ERR(info))
		वापस PTR_ERR(info);
	अगर (info != शून्य)
		वापस add_dataflash_otp(spi, info->name, info->nr_pages,
				info->pagesize, info->pageoffset,
				(info->flags & SUP_POW2PS) ? 'd' : 'c');

	/*
	 * Older chips support only legacy commands, identअगरing
	 * capacity using bits in the status byte.
	 */
	status = dataflash_status(spi);
	अगर (status <= 0 || status == 0xff) अणु
		dev_dbg(&spi->dev, "status error %d\n", status);
		अगर (status == 0 || status == 0xff)
			status = -ENODEV;
		वापस status;
	पूर्ण

	/* अगर there's a device there, assume it's dataflash.
	 * board setup should have set spi->max_speed_max to
	 * match f(car) क्रम continuous पढ़ोs, mode 0 or 3.
	 */
	चयन (status & 0x3c) अणु
	हाल 0x0c:	/* 0 0 1 1 x x */
		status = add_dataflash(spi, "AT45DB011B", 512, 264, 9);
		अवरोध;
	हाल 0x14:	/* 0 1 0 1 x x */
		status = add_dataflash(spi, "AT45DB021B", 1024, 264, 9);
		अवरोध;
	हाल 0x1c:	/* 0 1 1 1 x x */
		status = add_dataflash(spi, "AT45DB041x", 2048, 264, 9);
		अवरोध;
	हाल 0x24:	/* 1 0 0 1 x x */
		status = add_dataflash(spi, "AT45DB081B", 4096, 264, 9);
		अवरोध;
	हाल 0x2c:	/* 1 0 1 1 x x */
		status = add_dataflash(spi, "AT45DB161x", 4096, 528, 10);
		अवरोध;
	हाल 0x34:	/* 1 1 0 1 x x */
		status = add_dataflash(spi, "AT45DB321x", 8192, 528, 10);
		अवरोध;
	हाल 0x38:	/* 1 1 1 x x x */
	हाल 0x3c:
		status = add_dataflash(spi, "AT45DB642x", 8192, 1056, 11);
		अवरोध;
	/* obsolete AT45DB1282 not (yet?) supported */
	शेष:
		dev_info(&spi->dev, "unsupported device (%x)\n",
				status & 0x3c);
		status = -ENODEV;
	पूर्ण

	अगर (status < 0)
		dev_dbg(&spi->dev, "add_dataflash --> %d\n", status);

	वापस status;
पूर्ण

अटल पूर्णांक dataflash_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा dataflash	*flash = spi_get_drvdata(spi);
	पूर्णांक			status;

	dev_dbg(&spi->dev, "remove\n");

	status = mtd_device_unरेजिस्टर(&flash->mtd);
	अगर (status == 0)
		kमुक्त(flash);
	वापस status;
पूर्ण

अटल काष्ठा spi_driver dataflash_driver = अणु
	.driver = अणु
		.name		= "mtd_dataflash",
		.of_match_table = of_match_ptr(dataflash_dt_ids),
	पूर्ण,

	.probe		= dataflash_probe,
	.हटाओ		= dataflash_हटाओ,

	/* FIXME:  investigate suspend and resume... */
पूर्ण;

module_spi_driver(dataflash_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrew Victor, David Brownell");
MODULE_DESCRIPTION("MTD DataFlash driver");
MODULE_ALIAS("spi:mtd_dataflash");
