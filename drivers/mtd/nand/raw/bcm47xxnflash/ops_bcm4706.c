<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * BCM47XX न_अंकD flash driver
 *
 * Copyright (C) 2012 Rafaध Miधecki <zajec5@gmail.com>
 */

#समावेश "bcm47xxnflash.h"

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/bcma/bcma.h>

/* Broadcom uses 1'000'000 but it seems to be too many. Tests on WNDR4500 has
 * shown ~1000 retries as maxiumum. */
#घोषणा NFLASH_READY_RETRIES		10000

#घोषणा NFLASH_SECTOR_SIZE		512

#घोषणा NCTL_CMD0			0x00010000
#घोषणा NCTL_COL			0x00020000	/* Update column with value from BCMA_CC_NFLASH_COL_ADDR */
#घोषणा NCTL_ROW			0x00040000	/* Update row (page) with value from BCMA_CC_NFLASH_ROW_ADDR */
#घोषणा NCTL_CMD1W			0x00080000
#घोषणा NCTL_READ			0x00100000
#घोषणा NCTL_WRITE			0x00200000
#घोषणा NCTL_SPECADDR			0x01000000
#घोषणा NCTL_READY			0x04000000
#घोषणा NCTL_ERR			0x08000000
#घोषणा NCTL_CSA			0x40000000
#घोषणा NCTL_START			0x80000000

/**************************************************
 * Various helpers
 **************************************************/

अटल अंतरभूत u8 bcm47xxnflash_ops_bcm4706_ns_to_cycle(u16 ns, u16 घड़ी)
अणु
	वापस ((ns * 1000 * घड़ी) / 1000000) + 1;
पूर्ण

अटल पूर्णांक bcm47xxnflash_ops_bcm4706_ctl_cmd(काष्ठा bcma_drv_cc *cc, u32 code)
अणु
	पूर्णांक i = 0;

	bcma_cc_ग_लिखो32(cc, BCMA_CC_NFLASH_CTL, NCTL_START | code);
	क्रम (i = 0; i < NFLASH_READY_RETRIES; i++) अणु
		अगर (!(bcma_cc_पढ़ो32(cc, BCMA_CC_NFLASH_CTL) & NCTL_START)) अणु
			i = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i) अणु
		pr_err("NFLASH control command not ready!\n");
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bcm47xxnflash_ops_bcm4706_poll(काष्ठा bcma_drv_cc *cc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NFLASH_READY_RETRIES; i++) अणु
		अगर (bcma_cc_पढ़ो32(cc, BCMA_CC_NFLASH_CTL) & NCTL_READY) अणु
			अगर (bcma_cc_पढ़ो32(cc, BCMA_CC_NFLASH_CTL) &
			    BCMA_CC_NFLASH_CTL_ERR) अणु
				pr_err("Error on polling\n");
				वापस -EBUSY;
			पूर्ण अन्यथा अणु
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	pr_err("Polling timeout!\n");
	वापस -EBUSY;
पूर्ण

/**************************************************
 * R/W
 **************************************************/

अटल व्योम bcm47xxnflash_ops_bcm4706_पढ़ो(काष्ठा mtd_info *mtd, uपूर्णांक8_t *buf,
					   पूर्णांक len)
अणु
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);
	काष्ठा bcm47xxnflash *b47n = nand_get_controller_data(nand_chip);

	u32 ctlcode;
	u32 *dest = (u32 *)buf;
	पूर्णांक i;
	पूर्णांक toपढ़ो;

	BUG_ON(b47n->curr_page_addr & ~nand_chip->pagemask);
	/* Don't validate column using nand_chip->page_shअगरt, it may be bigger
	 * when accessing OOB */

	जबतक (len) अणु
		/* We can पढ़ो maximum of 0x200 bytes at once */
		toपढ़ो = min(len, 0x200);

		/* Set page and column */
		bcma_cc_ग_लिखो32(b47n->cc, BCMA_CC_NFLASH_COL_ADDR,
				b47n->curr_column);
		bcma_cc_ग_लिखो32(b47n->cc, BCMA_CC_NFLASH_ROW_ADDR,
				b47n->curr_page_addr);

		/* Prepare to पढ़ो */
		ctlcode = NCTL_CSA | NCTL_CMD1W | NCTL_ROW | NCTL_COL |
			  NCTL_CMD0;
		ctlcode |= न_अंकD_CMD_READSTART << 8;
		अगर (bcm47xxnflash_ops_bcm4706_ctl_cmd(b47n->cc, ctlcode))
			वापस;
		अगर (bcm47xxnflash_ops_bcm4706_poll(b47n->cc))
			वापस;

		/* Eventually पढ़ो some data :) */
		क्रम (i = 0; i < toपढ़ो; i += 4, dest++) अणु
			ctlcode = NCTL_CSA | 0x30000000 | NCTL_READ;
			अगर (i == toपढ़ो - 4) /* Last पढ़ो goes without that */
				ctlcode &= ~NCTL_CSA;
			अगर (bcm47xxnflash_ops_bcm4706_ctl_cmd(b47n->cc,
							      ctlcode))
				वापस;
			*dest = bcma_cc_पढ़ो32(b47n->cc, BCMA_CC_NFLASH_DATA);
		पूर्ण

		b47n->curr_column += toपढ़ो;
		len -= toपढ़ो;
	पूर्ण
पूर्ण

अटल व्योम bcm47xxnflash_ops_bcm4706_ग_लिखो(काष्ठा mtd_info *mtd,
					    स्थिर uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);
	काष्ठा bcm47xxnflash *b47n = nand_get_controller_data(nand_chip);
	काष्ठा bcma_drv_cc *cc = b47n->cc;

	u32 ctlcode;
	स्थिर u32 *data = (u32 *)buf;
	पूर्णांक i;

	BUG_ON(b47n->curr_page_addr & ~nand_chip->pagemask);
	/* Don't validate column using nand_chip->page_shअगरt, it may be bigger
	 * when accessing OOB */

	क्रम (i = 0; i < len; i += 4, data++) अणु
		bcma_cc_ग_लिखो32(cc, BCMA_CC_NFLASH_DATA, *data);

		ctlcode = NCTL_CSA | 0x30000000 | NCTL_WRITE;
		अगर (i == len - 4) /* Last पढ़ो goes without that */
			ctlcode &= ~NCTL_CSA;
		अगर (bcm47xxnflash_ops_bcm4706_ctl_cmd(cc, ctlcode)) अणु
			pr_err("%s ctl_cmd didn't work!\n", __func__);
			वापस;
		पूर्ण
	पूर्ण

	b47n->curr_column += len;
पूर्ण

/**************************************************
 * न_अंकD chip ops
 **************************************************/

अटल व्योम bcm47xxnflash_ops_bcm4706_cmd_ctrl(काष्ठा nand_chip *nand_chip,
					       पूर्णांक cmd, अचिन्हित पूर्णांक ctrl)
अणु
	काष्ठा bcm47xxnflash *b47n = nand_get_controller_data(nand_chip);
	u32 code = 0;

	अगर (cmd == न_अंकD_CMD_NONE)
		वापस;

	अगर (cmd & न_अंकD_CTRL_CLE)
		code = cmd | NCTL_CMD0;

	/* nCS is not needed क्रम reset command */
	अगर (cmd != न_अंकD_CMD_RESET)
		code |= NCTL_CSA;

	bcm47xxnflash_ops_bcm4706_ctl_cmd(b47n->cc, code);
पूर्ण

/* Default nand_select_chip calls cmd_ctrl, which is not used in BCM4706 */
अटल व्योम bcm47xxnflash_ops_bcm4706_select_chip(काष्ठा nand_chip *chip,
						  पूर्णांक cs)
अणु
	वापस;
पूर्ण

अटल पूर्णांक bcm47xxnflash_ops_bcm4706_dev_पढ़ोy(काष्ठा nand_chip *nand_chip)
अणु
	काष्ठा bcm47xxnflash *b47n = nand_get_controller_data(nand_chip);

	वापस !!(bcma_cc_पढ़ो32(b47n->cc, BCMA_CC_NFLASH_CTL) & NCTL_READY);
पूर्ण

/*
 * Default nand_command and nand_command_lp करोn't match BCM4706 hardware layout.
 * For example, पढ़ोing chip id is perक्रमmed in a non-standard way.
 * Setting column and page is also handled dअगरferently, we use a special
 * रेजिस्टरs of ChipCommon core. Hacking cmd_ctrl to understand and convert
 * standard commands would be much more complicated.
 */
अटल व्योम bcm47xxnflash_ops_bcm4706_cmdfunc(काष्ठा nand_chip *nand_chip,
					      अचिन्हित command, पूर्णांक column,
					      पूर्णांक page_addr)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand_chip);
	काष्ठा bcm47xxnflash *b47n = nand_get_controller_data(nand_chip);
	काष्ठा bcma_drv_cc *cc = b47n->cc;
	u32 ctlcode;
	पूर्णांक i;

	अगर (column != -1)
		b47n->curr_column = column;
	अगर (page_addr != -1)
		b47n->curr_page_addr = page_addr;

	चयन (command) अणु
	हाल न_अंकD_CMD_RESET:
		nand_chip->legacy.cmd_ctrl(nand_chip, command, न_अंकD_CTRL_CLE);

		ndelay(100);
		nand_रुको_पढ़ोy(nand_chip);
		अवरोध;
	हाल न_अंकD_CMD_READID:
		ctlcode = NCTL_CSA | 0x01000000 | NCTL_CMD1W | NCTL_CMD0;
		ctlcode |= न_अंकD_CMD_READID;
		अगर (bcm47xxnflash_ops_bcm4706_ctl_cmd(b47n->cc, ctlcode)) अणु
			pr_err("READID error\n");
			अवरोध;
		पूर्ण

		/*
		 * Reading is specअगरic, last one has to go without NCTL_CSA
		 * bit. We करोn't know how many पढ़ोs न_अंकD subप्रणाली is going
		 * to perक्रमm, so cache everything.
		 */
		क्रम (i = 0; i < ARRAY_SIZE(b47n->id_data); i++) अणु
			ctlcode = NCTL_CSA | NCTL_READ;
			अगर (i == ARRAY_SIZE(b47n->id_data) - 1)
				ctlcode &= ~NCTL_CSA;
			अगर (bcm47xxnflash_ops_bcm4706_ctl_cmd(b47n->cc,
							      ctlcode)) अणु
				pr_err("READID error\n");
				अवरोध;
			पूर्ण
			b47n->id_data[i] =
				bcma_cc_पढ़ो32(b47n->cc, BCMA_CC_NFLASH_DATA)
				& 0xFF;
		पूर्ण

		अवरोध;
	हाल न_अंकD_CMD_STATUS:
		ctlcode = NCTL_CSA | NCTL_CMD0 | न_अंकD_CMD_STATUS;
		अगर (bcm47xxnflash_ops_bcm4706_ctl_cmd(cc, ctlcode))
			pr_err("STATUS command error\n");
		अवरोध;
	हाल न_अंकD_CMD_READ0:
		अवरोध;
	हाल न_अंकD_CMD_READOOB:
		अगर (page_addr != -1)
			b47n->curr_column += mtd->ग_लिखोsize;
		अवरोध;
	हाल न_अंकD_CMD_ERASE1:
		bcma_cc_ग_लिखो32(cc, BCMA_CC_NFLASH_ROW_ADDR,
				b47n->curr_page_addr);
		ctlcode = NCTL_ROW | NCTL_CMD1W | NCTL_CMD0 |
			  न_अंकD_CMD_ERASE1 | (न_अंकD_CMD_ERASE2 << 8);
		अगर (bcm47xxnflash_ops_bcm4706_ctl_cmd(cc, ctlcode))
			pr_err("ERASE1 failed\n");
		अवरोध;
	हाल न_अंकD_CMD_ERASE2:
		अवरोध;
	हाल न_अंकD_CMD_SEQIN:
		/* Set page and column */
		bcma_cc_ग_लिखो32(cc, BCMA_CC_NFLASH_COL_ADDR,
				b47n->curr_column);
		bcma_cc_ग_लिखो32(cc, BCMA_CC_NFLASH_ROW_ADDR,
				b47n->curr_page_addr);

		/* Prepare to ग_लिखो */
		ctlcode = 0x40000000 | NCTL_ROW | NCTL_COL | NCTL_CMD0;
		ctlcode |= न_अंकD_CMD_SEQIN;
		अगर (bcm47xxnflash_ops_bcm4706_ctl_cmd(cc, ctlcode))
			pr_err("SEQIN failed\n");
		अवरोध;
	हाल न_अंकD_CMD_PAGEPROG:
		अगर (bcm47xxnflash_ops_bcm4706_ctl_cmd(cc, NCTL_CMD0 |
							  न_अंकD_CMD_PAGEPROG))
			pr_err("PAGEPROG failed\n");
		अगर (bcm47xxnflash_ops_bcm4706_poll(cc))
			pr_err("PAGEPROG not ready\n");
		अवरोध;
	शेष:
		pr_err("Command 0x%X unsupported\n", command);
		अवरोध;
	पूर्ण
	b47n->curr_command = command;
पूर्ण

अटल u8 bcm47xxnflash_ops_bcm4706_पढ़ो_byte(काष्ठा nand_chip *nand_chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(nand_chip);
	काष्ठा bcm47xxnflash *b47n = nand_get_controller_data(nand_chip);
	काष्ठा bcma_drv_cc *cc = b47n->cc;
	u32 पंचांगp = 0;

	चयन (b47n->curr_command) अणु
	हाल न_अंकD_CMD_READID:
		अगर (b47n->curr_column >= ARRAY_SIZE(b47n->id_data)) अणु
			pr_err("Requested invalid id_data: %d\n",
			       b47n->curr_column);
			वापस 0;
		पूर्ण
		वापस b47n->id_data[b47n->curr_column++];
	हाल न_अंकD_CMD_STATUS:
		अगर (bcm47xxnflash_ops_bcm4706_ctl_cmd(cc, NCTL_READ))
			वापस 0;
		वापस bcma_cc_पढ़ो32(cc, BCMA_CC_NFLASH_DATA) & 0xff;
	हाल न_अंकD_CMD_READOOB:
		bcm47xxnflash_ops_bcm4706_पढ़ो(mtd, (u8 *)&पंचांगp, 4);
		वापस पंचांगp & 0xFF;
	पूर्ण

	pr_err("Invalid command for byte read: 0x%X\n", b47n->curr_command);
	वापस 0;
पूर्ण

अटल व्योम bcm47xxnflash_ops_bcm4706_पढ़ो_buf(काष्ठा nand_chip *nand_chip,
					       uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	काष्ठा bcm47xxnflash *b47n = nand_get_controller_data(nand_chip);

	चयन (b47n->curr_command) अणु
	हाल न_अंकD_CMD_READ0:
	हाल न_अंकD_CMD_READOOB:
		bcm47xxnflash_ops_bcm4706_पढ़ो(nand_to_mtd(nand_chip), buf,
					       len);
		वापस;
	पूर्ण

	pr_err("Invalid command for buf read: 0x%X\n", b47n->curr_command);
पूर्ण

अटल व्योम bcm47xxnflash_ops_bcm4706_ग_लिखो_buf(काष्ठा nand_chip *nand_chip,
						स्थिर uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	काष्ठा bcm47xxnflash *b47n = nand_get_controller_data(nand_chip);

	चयन (b47n->curr_command) अणु
	हाल न_अंकD_CMD_SEQIN:
		bcm47xxnflash_ops_bcm4706_ग_लिखो(nand_to_mtd(nand_chip), buf,
						len);
		वापस;
	पूर्ण

	pr_err("Invalid command for buf write: 0x%X\n", b47n->curr_command);
पूर्ण

/**************************************************
 * Init
 **************************************************/

पूर्णांक bcm47xxnflash_ops_bcm4706_init(काष्ठा bcm47xxnflash *b47n)
अणु
	काष्ठा nand_chip *nand_chip = (काष्ठा nand_chip *)&b47n->nand_chip;
	पूर्णांक err;
	u32 freq;
	u16 घड़ी;
	u8 w0, w1, w2, w3, w4;

	अचिन्हित दीर्घ chipsize; /* MiB */
	u8 tbits, col_bits, col_size, row_bits, row_bsize;
	u32 val;

	nand_chip->legacy.select_chip = bcm47xxnflash_ops_bcm4706_select_chip;
	nand_chip->legacy.cmd_ctrl = bcm47xxnflash_ops_bcm4706_cmd_ctrl;
	nand_chip->legacy.dev_पढ़ोy = bcm47xxnflash_ops_bcm4706_dev_पढ़ोy;
	b47n->nand_chip.legacy.cmdfunc = bcm47xxnflash_ops_bcm4706_cmdfunc;
	b47n->nand_chip.legacy.पढ़ो_byte = bcm47xxnflash_ops_bcm4706_पढ़ो_byte;
	b47n->nand_chip.legacy.पढ़ो_buf = bcm47xxnflash_ops_bcm4706_पढ़ो_buf;
	b47n->nand_chip.legacy.ग_लिखो_buf = bcm47xxnflash_ops_bcm4706_ग_लिखो_buf;
	b47n->nand_chip.legacy.set_features = nand_get_set_features_notsupp;
	b47n->nand_chip.legacy.get_features = nand_get_set_features_notsupp;

	nand_chip->legacy.chip_delay = 50;
	b47n->nand_chip.bbt_options = न_अंकD_BBT_USE_FLASH;
	/* TODO: implement ECC */
	b47n->nand_chip.ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_NONE;

	/* Enable न_अंकD flash access */
	bcma_cc_set32(b47n->cc, BCMA_CC_4706_FLASHSCFG,
		      BCMA_CC_4706_FLASHSCFG_NF1);

	/* Configure रुको counters */
	अगर (b47n->cc->status & BCMA_CC_CHIPST_4706_PKG_OPTION) अणु
		/* 400 MHz */
		freq = 400000000 / 4;
	पूर्ण अन्यथा अणु
		freq = bcma_chipco_pll_पढ़ो(b47n->cc, 4);
		freq = (freq & 0xFFF) >> 3;
		/* Fixed reference घड़ी 25 MHz and m = 2 */
		freq = (freq * 25000000 / 2) / 4;
	पूर्ण
	घड़ी = freq / 1000000;
	w0 = bcm47xxnflash_ops_bcm4706_ns_to_cycle(15, घड़ी);
	w1 = bcm47xxnflash_ops_bcm4706_ns_to_cycle(20, घड़ी);
	w2 = bcm47xxnflash_ops_bcm4706_ns_to_cycle(10, घड़ी);
	w3 = bcm47xxnflash_ops_bcm4706_ns_to_cycle(10, घड़ी);
	w4 = bcm47xxnflash_ops_bcm4706_ns_to_cycle(100, घड़ी);
	bcma_cc_ग_लिखो32(b47n->cc, BCMA_CC_NFLASH_WAITCNT0,
			(w4 << 24 | w3 << 18 | w2 << 12 | w1 << 6 | w0));

	/* Scan न_अंकD */
	err = nand_scan(&b47n->nand_chip, 1);
	अगर (err) अणु
		pr_err("Could not scan NAND flash: %d\n", err);
		जाओ निकास;
	पूर्ण

	/* Configure FLASH */
	chipsize = nanddev_target_size(&b47n->nand_chip.base) >> 20;
	tbits = ffs(chipsize); /* find first bit set */
	अगर (!tbits || tbits != fls(chipsize)) अणु
		pr_err("Invalid flash size: 0x%lX\n", chipsize);
		err = -ENOTSUPP;
		जाओ निकास;
	पूर्ण
	tbits += 19; /* Broadcom increases *index* by 20, we increase *pos* */

	col_bits = b47n->nand_chip.page_shअगरt + 1;
	col_size = (col_bits + 7) / 8;

	row_bits = tbits - col_bits + 1;
	row_bsize = (row_bits + 7) / 8;

	val = ((row_bsize - 1) << 6) | ((col_size - 1) << 4) | 2;
	bcma_cc_ग_लिखो32(b47n->cc, BCMA_CC_NFLASH_CONF, val);

निकास:
	अगर (err)
		bcma_cc_mask32(b47n->cc, BCMA_CC_4706_FLASHSCFG,
			       ~BCMA_CC_4706_FLASHSCFG_NF1);
	वापस err;
पूर्ण
