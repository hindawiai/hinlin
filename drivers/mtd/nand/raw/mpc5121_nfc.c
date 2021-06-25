<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2004-2008 Freescale Semiconductor, Inc.
 * Copyright 2009 Semihalf.
 *
 * Approved as OSADL project by a majority of OSADL members and funded
 * by OSADL membership fees in 2009;  क्रम details see www.osadl.org.
 *
 * Based on original driver from Freescale Semiconductor
 * written by John Rigby <jrigby@मुक्तscale.com> on basis of mxc_nand.c.
 * Reworked and extended by Piotr Ziecik <kosmo@semihalf.com>.
 */

#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/gfp.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/mpc5121.h>

/* Addresses क्रम NFC MAIN RAM BUFFER areas */
#घोषणा NFC_MAIN_AREA(n)	((n) *  0x200)

/* Addresses क्रम NFC SPARE BUFFER areas */
#घोषणा NFC_SPARE_BUFFERS	8
#घोषणा NFC_SPARE_LEN		0x40
#घोषणा NFC_SPARE_AREA(n)	(0x1000 + ((n) * NFC_SPARE_LEN))

/* MPC5121 NFC रेजिस्टरs */
#घोषणा NFC_BUF_ADDR		0x1E04
#घोषणा NFC_FLASH_ADDR		0x1E06
#घोषणा NFC_FLASH_CMD		0x1E08
#घोषणा NFC_CONFIG		0x1E0A
#घोषणा NFC_ECC_STATUS1		0x1E0C
#घोषणा NFC_ECC_STATUS2		0x1E0E
#घोषणा NFC_SPAS		0x1E10
#घोषणा NFC_WRPROT		0x1E12
#घोषणा NFC_NF_WRPRST		0x1E18
#घोषणा NFC_CONFIG1		0x1E1A
#घोषणा NFC_CONFIG2		0x1E1C
#घोषणा NFC_UNLOCKSTART_BLK0	0x1E20
#घोषणा NFC_UNLOCKEND_BLK0	0x1E22
#घोषणा NFC_UNLOCKSTART_BLK1	0x1E24
#घोषणा NFC_UNLOCKEND_BLK1	0x1E26
#घोषणा NFC_UNLOCKSTART_BLK2	0x1E28
#घोषणा NFC_UNLOCKEND_BLK2	0x1E2A
#घोषणा NFC_UNLOCKSTART_BLK3	0x1E2C
#घोषणा NFC_UNLOCKEND_BLK3	0x1E2E

/* Bit Definitions: NFC_BUF_ADDR */
#घोषणा NFC_RBA_MASK		(7 << 0)
#घोषणा NFC_ACTIVE_CS_SHIFT	5
#घोषणा NFC_ACTIVE_CS_MASK	(3 << NFC_ACTIVE_CS_SHIFT)

/* Bit Definitions: NFC_CONFIG */
#घोषणा NFC_BLS_UNLOCKED	(1 << 1)

/* Bit Definitions: NFC_CONFIG1 */
#घोषणा NFC_ECC_4BIT		(1 << 0)
#घोषणा NFC_FULL_PAGE_DMA	(1 << 1)
#घोषणा NFC_SPARE_ONLY		(1 << 2)
#घोषणा NFC_ECC_ENABLE		(1 << 3)
#घोषणा NFC_INT_MASK		(1 << 4)
#घोषणा NFC_BIG_ENDIAN		(1 << 5)
#घोषणा NFC_RESET		(1 << 6)
#घोषणा NFC_CE			(1 << 7)
#घोषणा NFC_ONE_CYCLE		(1 << 8)
#घोषणा NFC_PPB_32		(0 << 9)
#घोषणा NFC_PPB_64		(1 << 9)
#घोषणा NFC_PPB_128		(2 << 9)
#घोषणा NFC_PPB_256		(3 << 9)
#घोषणा NFC_PPB_MASK		(3 << 9)
#घोषणा NFC_FULL_PAGE_INT	(1 << 11)

/* Bit Definitions: NFC_CONFIG2 */
#घोषणा NFC_COMMAND		(1 << 0)
#घोषणा NFC_ADDRESS		(1 << 1)
#घोषणा NFC_INPUT		(1 << 2)
#घोषणा NFC_OUTPUT		(1 << 3)
#घोषणा NFC_ID			(1 << 4)
#घोषणा NFC_STATUS		(1 << 5)
#घोषणा NFC_CMD_FAIL		(1 << 15)
#घोषणा NFC_INT			(1 << 15)

/* Bit Definitions: NFC_WRPROT */
#घोषणा NFC_WPC_LOCK_TIGHT	(1 << 0)
#घोषणा NFC_WPC_LOCK		(1 << 1)
#घोषणा NFC_WPC_UNLOCK		(1 << 2)

#घोषणा	DRV_NAME		"mpc5121_nfc"

/* Timeouts */
#घोषणा NFC_RESET_TIMEOUT	1000		/* 1 ms */
#घोषणा NFC_TIMEOUT		(HZ / 10)	/* 1/10 s */

काष्ठा mpc5121_nfc_prv अणु
	काष्ठा nand_controller	controller;
	काष्ठा nand_chip	chip;
	पूर्णांक			irq;
	व्योम __iomem		*regs;
	काष्ठा clk		*clk;
	रुको_queue_head_t	irq_रुकोq;
	uपूर्णांक			column;
	पूर्णांक			spareonly;
	व्योम __iomem		*csreg;
	काष्ठा device		*dev;
पूर्ण;

अटल व्योम mpc5121_nfc_करोne(काष्ठा mtd_info *mtd);

/* Read NFC रेजिस्टर */
अटल अंतरभूत u16 nfc_पढ़ो(काष्ठा mtd_info *mtd, uपूर्णांक reg)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mpc5121_nfc_prv *prv = nand_get_controller_data(chip);

	वापस in_be16(prv->regs + reg);
पूर्ण

/* Write NFC रेजिस्टर */
अटल अंतरभूत व्योम nfc_ग_लिखो(काष्ठा mtd_info *mtd, uपूर्णांक reg, u16 val)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mpc5121_nfc_prv *prv = nand_get_controller_data(chip);

	out_be16(prv->regs + reg, val);
पूर्ण

/* Set bits in NFC रेजिस्टर */
अटल अंतरभूत व्योम nfc_set(काष्ठा mtd_info *mtd, uपूर्णांक reg, u16 bits)
अणु
	nfc_ग_लिखो(mtd, reg, nfc_पढ़ो(mtd, reg) | bits);
पूर्ण

/* Clear bits in NFC रेजिस्टर */
अटल अंतरभूत व्योम nfc_clear(काष्ठा mtd_info *mtd, uपूर्णांक reg, u16 bits)
अणु
	nfc_ग_लिखो(mtd, reg, nfc_पढ़ो(mtd, reg) & ~bits);
पूर्ण

/* Invoke address cycle */
अटल अंतरभूत व्योम mpc5121_nfc_send_addr(काष्ठा mtd_info *mtd, u16 addr)
अणु
	nfc_ग_लिखो(mtd, NFC_FLASH_ADDR, addr);
	nfc_ग_लिखो(mtd, NFC_CONFIG2, NFC_ADDRESS);
	mpc5121_nfc_करोne(mtd);
पूर्ण

/* Invoke command cycle */
अटल अंतरभूत व्योम mpc5121_nfc_send_cmd(काष्ठा mtd_info *mtd, u16 cmd)
अणु
	nfc_ग_लिखो(mtd, NFC_FLASH_CMD, cmd);
	nfc_ग_लिखो(mtd, NFC_CONFIG2, NFC_COMMAND);
	mpc5121_nfc_करोne(mtd);
पूर्ण

/* Send data from NFC buffers to न_अंकD flash */
अटल अंतरभूत व्योम mpc5121_nfc_send_prog_page(काष्ठा mtd_info *mtd)
अणु
	nfc_clear(mtd, NFC_BUF_ADDR, NFC_RBA_MASK);
	nfc_ग_लिखो(mtd, NFC_CONFIG2, NFC_INPUT);
	mpc5121_nfc_करोne(mtd);
पूर्ण

/* Receive data from न_अंकD flash */
अटल अंतरभूत व्योम mpc5121_nfc_send_पढ़ो_page(काष्ठा mtd_info *mtd)
अणु
	nfc_clear(mtd, NFC_BUF_ADDR, NFC_RBA_MASK);
	nfc_ग_लिखो(mtd, NFC_CONFIG2, NFC_OUTPUT);
	mpc5121_nfc_करोne(mtd);
पूर्ण

/* Receive ID from न_अंकD flash */
अटल अंतरभूत व्योम mpc5121_nfc_send_पढ़ो_id(काष्ठा mtd_info *mtd)
अणु
	nfc_clear(mtd, NFC_BUF_ADDR, NFC_RBA_MASK);
	nfc_ग_लिखो(mtd, NFC_CONFIG2, NFC_ID);
	mpc5121_nfc_करोne(mtd);
पूर्ण

/* Receive status from न_अंकD flash */
अटल अंतरभूत व्योम mpc5121_nfc_send_पढ़ो_status(काष्ठा mtd_info *mtd)
अणु
	nfc_clear(mtd, NFC_BUF_ADDR, NFC_RBA_MASK);
	nfc_ग_लिखो(mtd, NFC_CONFIG2, NFC_STATUS);
	mpc5121_nfc_करोne(mtd);
पूर्ण

/* NFC पूर्णांकerrupt handler */
अटल irqवापस_t mpc5121_nfc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mtd_info *mtd = data;
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mpc5121_nfc_prv *prv = nand_get_controller_data(chip);

	nfc_set(mtd, NFC_CONFIG1, NFC_INT_MASK);
	wake_up(&prv->irq_रुकोq);

	वापस IRQ_HANDLED;
पूर्ण

/* Wait क्रम operation complete */
अटल व्योम mpc5121_nfc_करोne(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mpc5121_nfc_prv *prv = nand_get_controller_data(chip);
	पूर्णांक rv;

	अगर ((nfc_पढ़ो(mtd, NFC_CONFIG2) & NFC_INT) == 0) अणु
		nfc_clear(mtd, NFC_CONFIG1, NFC_INT_MASK);
		rv = रुको_event_समयout(prv->irq_रुकोq,
			(nfc_पढ़ो(mtd, NFC_CONFIG2) & NFC_INT), NFC_TIMEOUT);

		अगर (!rv)
			dev_warn(prv->dev,
				"Timeout while waiting for interrupt.\n");
	पूर्ण

	nfc_clear(mtd, NFC_CONFIG2, NFC_INT);
पूर्ण

/* Do address cycle(s) */
अटल व्योम mpc5121_nfc_addr_cycle(काष्ठा mtd_info *mtd, पूर्णांक column, पूर्णांक page)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	u32 pagemask = chip->pagemask;

	अगर (column != -1) अणु
		mpc5121_nfc_send_addr(mtd, column);
		अगर (mtd->ग_लिखोsize > 512)
			mpc5121_nfc_send_addr(mtd, column >> 8);
	पूर्ण

	अगर (page != -1) अणु
		करो अणु
			mpc5121_nfc_send_addr(mtd, page & 0xFF);
			page >>= 8;
			pagemask >>= 8;
		पूर्ण जबतक (pagemask);
	पूर्ण
पूर्ण

/* Control chip select संकेतs */
अटल व्योम mpc5121_nfc_select_chip(काष्ठा nand_chip *nand, पूर्णांक chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);

	अगर (chip < 0) अणु
		nfc_clear(mtd, NFC_CONFIG1, NFC_CE);
		वापस;
	पूर्ण

	nfc_clear(mtd, NFC_BUF_ADDR, NFC_ACTIVE_CS_MASK);
	nfc_set(mtd, NFC_BUF_ADDR, (chip << NFC_ACTIVE_CS_SHIFT) &
							NFC_ACTIVE_CS_MASK);
	nfc_set(mtd, NFC_CONFIG1, NFC_CE);
पूर्ण

/* Init बाह्यal chip select logic on ADS5121 board */
अटल पूर्णांक ads5121_chipselect_init(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mpc5121_nfc_prv *prv = nand_get_controller_data(chip);
	काष्ठा device_node *dn;

	dn = of_find_compatible_node(शून्य, शून्य, "fsl,mpc5121ads-cpld");
	अगर (dn) अणु
		prv->csreg = of_iomap(dn, 0);
		of_node_put(dn);
		अगर (!prv->csreg)
			वापस -ENOMEM;

		/* CPLD Register 9 controls न_अंकD /CE Lines */
		prv->csreg += 9;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* Control chips select संकेत on ADS5121 board */
अटल व्योम ads5121_select_chip(काष्ठा nand_chip *nand, पूर्णांक chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand);
	काष्ठा mpc5121_nfc_prv *prv = nand_get_controller_data(nand);
	u8 v;

	v = in_8(prv->csreg);
	v |= 0x0F;

	अगर (chip >= 0) अणु
		mpc5121_nfc_select_chip(nand, 0);
		v &= ~(1 << chip);
	पूर्ण अन्यथा
		mpc5121_nfc_select_chip(nand, -1);

	out_8(prv->csreg, v);
पूर्ण

/* Read न_अंकD Ready/Busy संकेत */
अटल पूर्णांक mpc5121_nfc_dev_पढ़ोy(काष्ठा nand_chip *nand)
अणु
	/*
	 * NFC handles पढ़ोy/busy संकेत पूर्णांकernally. Thereक्रमe, this function
	 * always वापसs status as पढ़ोy.
	 */
	वापस 1;
पूर्ण

/* Write command to न_अंकD flash */
अटल व्योम mpc5121_nfc_command(काष्ठा nand_chip *chip, अचिन्हित command,
				पूर्णांक column, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा mpc5121_nfc_prv *prv = nand_get_controller_data(chip);

	prv->column = (column >= 0) ? column : 0;
	prv->spareonly = 0;

	चयन (command) अणु
	हाल न_अंकD_CMD_PAGEPROG:
		mpc5121_nfc_send_prog_page(mtd);
		अवरोध;
	/*
	 * NFC करोes not support sub-page पढ़ोs and ग_लिखोs,
	 * so emulate them using full page transfers.
	 */
	हाल न_अंकD_CMD_READ0:
		column = 0;
		अवरोध;

	हाल न_अंकD_CMD_READ1:
		prv->column += 256;
		command = न_अंकD_CMD_READ0;
		column = 0;
		अवरोध;

	हाल न_अंकD_CMD_READOOB:
		prv->spareonly = 1;
		command = न_अंकD_CMD_READ0;
		column = 0;
		अवरोध;

	हाल न_अंकD_CMD_SEQIN:
		mpc5121_nfc_command(chip, न_अंकD_CMD_READ0, column, page);
		column = 0;
		अवरोध;

	हाल न_अंकD_CMD_ERASE1:
	हाल न_अंकD_CMD_ERASE2:
	हाल न_अंकD_CMD_READID:
	हाल न_अंकD_CMD_STATUS:
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	mpc5121_nfc_send_cmd(mtd, command);
	mpc5121_nfc_addr_cycle(mtd, column, page);

	चयन (command) अणु
	हाल न_अंकD_CMD_READ0:
		अगर (mtd->ग_लिखोsize > 512)
			mpc5121_nfc_send_cmd(mtd, न_अंकD_CMD_READSTART);
		mpc5121_nfc_send_पढ़ो_page(mtd);
		अवरोध;

	हाल न_अंकD_CMD_READID:
		mpc5121_nfc_send_पढ़ो_id(mtd);
		अवरोध;

	हाल न_अंकD_CMD_STATUS:
		mpc5121_nfc_send_पढ़ो_status(mtd);
		अगर (chip->options & न_अंकD_BUSWIDTH_16)
			prv->column = 1;
		अन्यथा
			prv->column = 0;
		अवरोध;
	पूर्ण
पूर्ण

/* Copy data from/to NFC spare buffers. */
अटल व्योम mpc5121_nfc_copy_spare(काष्ठा mtd_info *mtd, uपूर्णांक offset,
						u8 *buffer, uपूर्णांक size, पूर्णांक wr)
अणु
	काष्ठा nand_chip *nand = mtd_to_nand(mtd);
	काष्ठा mpc5121_nfc_prv *prv = nand_get_controller_data(nand);
	uपूर्णांक o, s, sbsize, blksize;

	/*
	 * न_अंकD spare area is available through NFC spare buffers.
	 * The NFC भागides spare area पूर्णांकo (page_size / 512) chunks.
	 * Each chunk is placed पूर्णांकo separate spare memory area, using
	 * first (spare_size / num_of_chunks) bytes of the buffer.
	 *
	 * For न_अंकD device in which the spare area is not भागided fully
	 * by the number of chunks, number of used bytes in each spare
	 * buffer is rounded करोwn to the nearest even number of bytes,
	 * and all reमुख्यing bytes are added to the last used spare area.
	 *
	 * For more inक्रमmation पढ़ो section 26.6.10 of MPC5121e
	 * Microcontroller Reference Manual, Rev. 3.
	 */

	/* Calculate number of valid bytes in each spare buffer */
	sbsize = (mtd->oobsize / (mtd->ग_लिखोsize / 512)) & ~1;

	जबतक (size) अणु
		/* Calculate spare buffer number */
		s = offset / sbsize;
		अगर (s > NFC_SPARE_BUFFERS - 1)
			s = NFC_SPARE_BUFFERS - 1;

		/*
		 * Calculate offset to requested data block in selected spare
		 * buffer and its size.
		 */
		o = offset - (s * sbsize);
		blksize = min(sbsize - o, size);

		अगर (wr)
			स_नकल_toio(prv->regs + NFC_SPARE_AREA(s) + o,
							buffer, blksize);
		अन्यथा
			स_नकल_fromio(buffer,
				prv->regs + NFC_SPARE_AREA(s) + o, blksize);

		buffer += blksize;
		offset += blksize;
		size -= blksize;
	पूर्ण
पूर्ण

/* Copy data from/to NFC मुख्य and spare buffers */
अटल व्योम mpc5121_nfc_buf_copy(काष्ठा mtd_info *mtd, u_अक्षर *buf, पूर्णांक len,
									पूर्णांक wr)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mpc5121_nfc_prv *prv = nand_get_controller_data(chip);
	uपूर्णांक c = prv->column;
	uपूर्णांक l;

	/* Handle spare area access */
	अगर (prv->spareonly || c >= mtd->ग_लिखोsize) अणु
		/* Calculate offset from beginning of spare area */
		अगर (c >= mtd->ग_लिखोsize)
			c -= mtd->ग_लिखोsize;

		prv->column += len;
		mpc5121_nfc_copy_spare(mtd, c, buf, len, wr);
		वापस;
	पूर्ण

	/*
	 * Handle मुख्य area access - limit copy length to prevent
	 * crossing मुख्य/spare boundary.
	 */
	l = min((uपूर्णांक)len, mtd->ग_लिखोsize - c);
	prv->column += l;

	अगर (wr)
		स_नकल_toio(prv->regs + NFC_MAIN_AREA(0) + c, buf, l);
	अन्यथा
		स_नकल_fromio(buf, prv->regs + NFC_MAIN_AREA(0) + c, l);

	/* Handle crossing मुख्य/spare boundary */
	अगर (l != len) अणु
		buf += l;
		len -= l;
		mpc5121_nfc_buf_copy(mtd, buf, len, wr);
	पूर्ण
पूर्ण

/* Read data from NFC buffers */
अटल व्योम mpc5121_nfc_पढ़ो_buf(काष्ठा nand_chip *chip, u_अक्षर *buf, पूर्णांक len)
अणु
	mpc5121_nfc_buf_copy(nand_to_mtd(chip), buf, len, 0);
पूर्ण

/* Write data to NFC buffers */
अटल व्योम mpc5121_nfc_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर u_अक्षर *buf,
				  पूर्णांक len)
अणु
	mpc5121_nfc_buf_copy(nand_to_mtd(chip), (u_अक्षर *)buf, len, 1);
पूर्ण

/* Read byte from NFC buffers */
अटल u8 mpc5121_nfc_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	u8 पंचांगp;

	mpc5121_nfc_पढ़ो_buf(chip, &पंचांगp, माप(पंचांगp));

	वापस पंचांगp;
पूर्ण

/*
 * Read NFC configuration from Reset Config Word
 *
 * NFC is configured during reset in basis of inक्रमmation stored
 * in Reset Config Word. There is no other way to set न_अंकD block
 * size, spare size and bus width.
 */
अटल पूर्णांक mpc5121_nfc_पढ़ो_hw_config(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mpc5121_nfc_prv *prv = nand_get_controller_data(chip);
	काष्ठा mpc512x_reset_module *rm;
	काष्ठा device_node *rmnode;
	uपूर्णांक rcw_pagesize = 0;
	uपूर्णांक rcw_sparesize = 0;
	uपूर्णांक rcw_width;
	uपूर्णांक rcwh;
	uपूर्णांक romloc, ps;
	पूर्णांक ret = 0;

	rmnode = of_find_compatible_node(शून्य, शून्य, "fsl,mpc5121-reset");
	अगर (!rmnode) अणु
		dev_err(prv->dev, "Missing 'fsl,mpc5121-reset' "
					"node in device tree!\n");
		वापस -ENODEV;
	पूर्ण

	rm = of_iomap(rmnode, 0);
	अगर (!rm) अणु
		dev_err(prv->dev, "Error mapping reset module node!\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	rcwh = in_be32(&rm->rcwhr);

	/* Bit 6: NFC bus width */
	rcw_width = ((rcwh >> 6) & 0x1) ? 2 : 1;

	/* Bit 7: NFC Page/Spare size */
	ps = (rcwh >> 7) & 0x1;

	/* Bits [22:21]: ROM Location */
	romloc = (rcwh >> 21) & 0x3;

	/* Decode RCW bits */
	चयन ((ps << 2) | romloc) अणु
	हाल 0x00:
	हाल 0x01:
		rcw_pagesize = 512;
		rcw_sparesize = 16;
		अवरोध;
	हाल 0x02:
	हाल 0x03:
		rcw_pagesize = 4096;
		rcw_sparesize = 128;
		अवरोध;
	हाल 0x04:
	हाल 0x05:
		rcw_pagesize = 2048;
		rcw_sparesize = 64;
		अवरोध;
	हाल 0x06:
	हाल 0x07:
		rcw_pagesize = 4096;
		rcw_sparesize = 218;
		अवरोध;
	पूर्ण

	mtd->ग_लिखोsize = rcw_pagesize;
	mtd->oobsize = rcw_sparesize;
	अगर (rcw_width == 2)
		chip->options |= न_अंकD_BUSWIDTH_16;

	dev_notice(prv->dev, "Configured for "
				"%u-bit NAND, page size %u "
				"with %u spare.\n",
				rcw_width * 8, rcw_pagesize,
				rcw_sparesize);
	iounmap(rm);
out:
	of_node_put(rmnode);
	वापस ret;
पूर्ण

/* Free driver resources */
अटल व्योम mpc5121_nfc_मुक्त(काष्ठा device *dev, काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा mpc5121_nfc_prv *prv = nand_get_controller_data(chip);

	अगर (prv->clk)
		clk_disable_unprepare(prv->clk);

	अगर (prv->csreg)
		iounmap(prv->csreg);
पूर्ण

अटल पूर्णांक mpc5121_nfc_attach_chip(काष्ठा nand_chip *chip)
अणु
	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;

	अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_UNKNOWN)
		chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops mpc5121_nfc_ops = अणु
	.attach_chip = mpc5121_nfc_attach_chip,
पूर्ण;

अटल पूर्णांक mpc5121_nfc_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dn = op->dev.of_node;
	काष्ठा clk *clk;
	काष्ठा device *dev = &op->dev;
	काष्ठा mpc5121_nfc_prv *prv;
	काष्ठा resource res;
	काष्ठा mtd_info *mtd;
	काष्ठा nand_chip *chip;
	अचिन्हित दीर्घ regs_paddr, regs_size;
	स्थिर __be32 *chips_no;
	पूर्णांक reसमय_रखो = 0;
	पूर्णांक retval = 0;
	पूर्णांक rev, len;

	/*
	 * Check SoC revision. This driver supports only NFC
	 * in MPC5121 revision 2 and MPC5123 revision 3.
	 */
	rev = (mfspr(SPRN_SVR) >> 4) & 0xF;
	अगर ((rev != 2) && (rev != 3)) अणु
		dev_err(dev, "SoC revision %u is not supported!\n", rev);
		वापस -ENXIO;
	पूर्ण

	prv = devm_kzalloc(dev, माप(*prv), GFP_KERNEL);
	अगर (!prv)
		वापस -ENOMEM;

	chip = &prv->chip;
	mtd = nand_to_mtd(chip);

	nand_controller_init(&prv->controller);
	prv->controller.ops = &mpc5121_nfc_ops;
	chip->controller = &prv->controller;

	mtd->dev.parent = dev;
	nand_set_controller_data(chip, prv);
	nand_set_flash_node(chip, dn);
	prv->dev = dev;

	/* Read NFC configuration from Reset Config Word */
	retval = mpc5121_nfc_पढ़ो_hw_config(mtd);
	अगर (retval) अणु
		dev_err(dev, "Unable to read NFC config!\n");
		वापस retval;
	पूर्ण

	prv->irq = irq_of_parse_and_map(dn, 0);
	अगर (prv->irq == NO_IRQ) अणु
		dev_err(dev, "Error mapping IRQ!\n");
		वापस -EINVAL;
	पूर्ण

	retval = of_address_to_resource(dn, 0, &res);
	अगर (retval) अणु
		dev_err(dev, "Error parsing memory region!\n");
		वापस retval;
	पूर्ण

	chips_no = of_get_property(dn, "chips", &len);
	अगर (!chips_no || len != माप(*chips_no)) अणु
		dev_err(dev, "Invalid/missing 'chips' property!\n");
		वापस -EINVAL;
	पूर्ण

	regs_paddr = res.start;
	regs_size = resource_size(&res);

	अगर (!devm_request_mem_region(dev, regs_paddr, regs_size, DRV_NAME)) अणु
		dev_err(dev, "Error requesting memory region!\n");
		वापस -EBUSY;
	पूर्ण

	prv->regs = devm_ioremap(dev, regs_paddr, regs_size);
	अगर (!prv->regs) अणु
		dev_err(dev, "Error mapping memory region!\n");
		वापस -ENOMEM;
	पूर्ण

	mtd->name = "MPC5121 NAND";
	chip->legacy.dev_पढ़ोy = mpc5121_nfc_dev_पढ़ोy;
	chip->legacy.cmdfunc = mpc5121_nfc_command;
	chip->legacy.पढ़ो_byte = mpc5121_nfc_पढ़ो_byte;
	chip->legacy.पढ़ो_buf = mpc5121_nfc_पढ़ो_buf;
	chip->legacy.ग_लिखो_buf = mpc5121_nfc_ग_लिखो_buf;
	chip->legacy.select_chip = mpc5121_nfc_select_chip;
	chip->legacy.set_features = nand_get_set_features_notsupp;
	chip->legacy.get_features = nand_get_set_features_notsupp;
	chip->bbt_options = न_अंकD_BBT_USE_FLASH;

	/* Support बाह्यal chip-select logic on ADS5121 board */
	अगर (of_machine_is_compatible("fsl,mpc5121ads")) अणु
		retval = ads5121_chipselect_init(mtd);
		अगर (retval) अणु
			dev_err(dev, "Chipselect init error!\n");
			वापस retval;
		पूर्ण

		chip->legacy.select_chip = ads5121_select_chip;
	पूर्ण

	/* Enable NFC घड़ी */
	clk = devm_clk_get(dev, "ipg");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "Unable to acquire NFC clock!\n");
		retval = PTR_ERR(clk);
		जाओ error;
	पूर्ण
	retval = clk_prepare_enable(clk);
	अगर (retval) अणु
		dev_err(dev, "Unable to enable NFC clock!\n");
		जाओ error;
	पूर्ण
	prv->clk = clk;

	/* Reset न_अंकD Flash controller */
	nfc_set(mtd, NFC_CONFIG1, NFC_RESET);
	जबतक (nfc_पढ़ो(mtd, NFC_CONFIG1) & NFC_RESET) अणु
		अगर (reसमय_रखो++ >= NFC_RESET_TIMEOUT) अणु
			dev_err(dev, "Timeout while resetting NFC!\n");
			retval = -EINVAL;
			जाओ error;
		पूर्ण

		udelay(1);
	पूर्ण

	/* Enable ग_लिखो to NFC memory */
	nfc_ग_लिखो(mtd, NFC_CONFIG, NFC_BLS_UNLOCKED);

	/* Enable ग_लिखो to all न_अंकD pages */
	nfc_ग_लिखो(mtd, NFC_UNLOCKSTART_BLK0, 0x0000);
	nfc_ग_लिखो(mtd, NFC_UNLOCKEND_BLK0, 0xFFFF);
	nfc_ग_लिखो(mtd, NFC_WRPROT, NFC_WPC_UNLOCK);

	/*
	 * Setup NFC:
	 *	- Big Endian transfers,
	 *	- Interrupt after full page पढ़ो/ग_लिखो.
	 */
	nfc_ग_लिखो(mtd, NFC_CONFIG1, NFC_BIG_ENDIAN | NFC_INT_MASK |
							NFC_FULL_PAGE_INT);

	/* Set spare area size */
	nfc_ग_लिखो(mtd, NFC_SPAS, mtd->oobsize >> 1);

	init_रुकोqueue_head(&prv->irq_रुकोq);
	retval = devm_request_irq(dev, prv->irq, &mpc5121_nfc_irq, 0, DRV_NAME,
									mtd);
	अगर (retval) अणु
		dev_err(dev, "Error requesting IRQ!\n");
		जाओ error;
	पूर्ण

	/* Detect न_अंकD chips */
	retval = nand_scan(chip, be32_to_cpup(chips_no));
	अगर (retval) अणु
		dev_err(dev, "NAND Flash not found !\n");
		जाओ error;
	पूर्ण

	/* Set erase block size */
	चयन (mtd->erasesize / mtd->ग_लिखोsize) अणु
	हाल 32:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_32);
		अवरोध;

	हाल 64:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_64);
		अवरोध;

	हाल 128:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_128);
		अवरोध;

	हाल 256:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_256);
		अवरोध;

	शेष:
		dev_err(dev, "Unsupported NAND flash!\n");
		retval = -ENXIO;
		जाओ error;
	पूर्ण

	dev_set_drvdata(dev, mtd);

	/* Register device in MTD */
	retval = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (retval) अणु
		dev_err(dev, "Error adding MTD device!\n");
		जाओ error;
	पूर्ण

	वापस 0;
error:
	mpc5121_nfc_मुक्त(dev, mtd);
	वापस retval;
पूर्ण

अटल पूर्णांक mpc5121_nfc_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device *dev = &op->dev;
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(mtd);
	WARN_ON(ret);
	nand_cleanup(mtd_to_nand(mtd));
	mpc5121_nfc_मुक्त(dev, mtd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc5121_nfc_match[] = अणु
	अणु .compatible = "fsl,mpc5121-nfc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mpc5121_nfc_match);

अटल काष्ठा platक्रमm_driver mpc5121_nfc_driver = अणु
	.probe		= mpc5121_nfc_probe,
	.हटाओ		= mpc5121_nfc_हटाओ,
	.driver		= अणु
		.name = DRV_NAME,
		.of_match_table = mpc5121_nfc_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mpc5121_nfc_driver);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("MPC5121 NAND MTD driver");
MODULE_LICENSE("GPL");
