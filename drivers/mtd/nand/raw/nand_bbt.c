<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Overview:
 *   Bad block table support क्रम the न_अंकD driver
 *
 *  Copyright तऊ 2004 Thomas Gleixner (tglx@linutronix.de)
 *
 * Description:
 *
 * When nand_scan_bbt is called, then it tries to find the bad block table
 * depending on the options in the BBT descriptor(s). If no flash based BBT
 * (न_अंकD_BBT_USE_FLASH) is specअगरied then the device is scanned क्रम factory
 * marked good / bad blocks. This inक्रमmation is used to create a memory BBT.
 * Once a new bad block is discovered then the "factory" inक्रमmation is updated
 * on the device.
 * If a flash based BBT is specअगरied then the function first tries to find the
 * BBT on flash. If a BBT is found then the contents are पढ़ो and the memory
 * based BBT is created. If a mirrored BBT is selected then the mirror is
 * searched too and the versions are compared. If the mirror has a greater
 * version number, then the mirror BBT is used to build the memory based BBT.
 * If the tables are not versioned, then we "or" the bad block inक्रमmation.
 * If one of the BBTs is out of date or करोes not exist it is (re)created.
 * If no BBT exists at all then the device is scanned क्रम factory marked
 * good / bad blocks and the bad block tables are created.
 *
 * For manufacturer created BBTs like the one found on M-SYS DOC devices
 * the BBT is searched and पढ़ो but never created
 *
 * The स्वतः generated bad block table is located in the last good blocks
 * of the device. The table is mirrored, so it can be updated eventually.
 * The table is marked in the OOB area with an ident pattern and a version
 * number which indicates which of both tables is more up to date. If the न_अंकD
 * controller needs the complete OOB area क्रम the ECC inक्रमmation then the
 * option न_अंकD_BBT_NO_OOB should be used (aदीर्घ with न_अंकD_BBT_USE_FLASH, of
 * course): it moves the ident pattern and the version byte पूर्णांकo the data area
 * and the OOB area will reमुख्य untouched.
 *
 * The table uses 2 bits per block
 * 11b:		block is good
 * 00b:		block is factory marked bad
 * 01b, 10b:	block is marked bad due to wear
 *
 * The memory bad block table uses the following scheme:
 * 00b:		block is good
 * 01b:		block is marked bad due to wear
 * 10b:		block is reserved (to protect the bbt area)
 * 11b:		block is factory marked bad
 *
 * Multichip devices like DOC store the bad block info per न्यूनमान.
 *
 * Following assumptions are made:
 * - bbts start at a page boundary, अगर स्वतःlocated on a block boundary
 * - the space necessary क्रम a bbt in FLASH करोes not exceed a block boundary
 */

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/bbm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>
#समावेश <linux/माला.स>

#समावेश "internals.h"

#घोषणा BBT_BLOCK_GOOD		0x00
#घोषणा BBT_BLOCK_WORN		0x01
#घोषणा BBT_BLOCK_RESERVED	0x02
#घोषणा BBT_BLOCK_FACTORY_BAD	0x03

#घोषणा BBT_ENTRY_MASK		0x03
#घोषणा BBT_ENTRY_SHIFT		2

अटल अंतरभूत uपूर्णांक8_t bbt_get_entry(काष्ठा nand_chip *chip, पूर्णांक block)
अणु
	uपूर्णांक8_t entry = chip->bbt[block >> BBT_ENTRY_SHIFT];
	entry >>= (block & BBT_ENTRY_MASK) * 2;
	वापस entry & BBT_ENTRY_MASK;
पूर्ण

अटल अंतरभूत व्योम bbt_mark_entry(काष्ठा nand_chip *chip, पूर्णांक block,
		uपूर्णांक8_t mark)
अणु
	uपूर्णांक8_t msk = (mark & BBT_ENTRY_MASK) << ((block & BBT_ENTRY_MASK) * 2);
	chip->bbt[block >> BBT_ENTRY_SHIFT] |= msk;
पूर्ण

अटल पूर्णांक check_pattern_no_oob(uपूर्णांक8_t *buf, काष्ठा nand_bbt_descr *td)
अणु
	अगर (स_भेद(buf, td->pattern, td->len))
		वापस -1;
	वापस 0;
पूर्ण

/**
 * check_pattern - [GENERIC] check अगर a pattern is in the buffer
 * @buf: the buffer to search
 * @len: the length of buffer to search
 * @paglen: the pagelength
 * @td: search pattern descriptor
 *
 * Check क्रम a pattern at the given place. Used to search bad block tables and
 * good / bad block identअगरiers.
 */
अटल पूर्णांक check_pattern(uपूर्णांक8_t *buf, पूर्णांक len, पूर्णांक paglen, काष्ठा nand_bbt_descr *td)
अणु
	अगर (td->options & न_अंकD_BBT_NO_OOB)
		वापस check_pattern_no_oob(buf, td);

	/* Compare the pattern */
	अगर (स_भेद(buf + paglen + td->offs, td->pattern, td->len))
		वापस -1;

	वापस 0;
पूर्ण

/**
 * check_लघु_pattern - [GENERIC] check अगर a pattern is in the buffer
 * @buf: the buffer to search
 * @td:	search pattern descriptor
 *
 * Check क्रम a pattern at the given place. Used to search bad block tables and
 * good / bad block identअगरiers. Same as check_pattern, but no optional empty
 * check.
 */
अटल पूर्णांक check_लघु_pattern(uपूर्णांक8_t *buf, काष्ठा nand_bbt_descr *td)
अणु
	/* Compare the pattern */
	अगर (स_भेद(buf + td->offs, td->pattern, td->len))
		वापस -1;
	वापस 0;
पूर्ण

/**
 * add_marker_len - compute the length of the marker in data area
 * @td: BBT descriptor used क्रम computation
 *
 * The length will be 0 अगर the marker is located in OOB area.
 */
अटल u32 add_marker_len(काष्ठा nand_bbt_descr *td)
अणु
	u32 len;

	अगर (!(td->options & न_अंकD_BBT_NO_OOB))
		वापस 0;

	len = td->len;
	अगर (td->options & न_अंकD_BBT_VERSION)
		len++;
	वापस len;
पूर्ण

/**
 * पढ़ो_bbt - [GENERIC] Read the bad block table starting from page
 * @this: न_अंकD chip object
 * @buf: temporary buffer
 * @page: the starting page
 * @num: the number of bbt descriptors to पढ़ो
 * @td: the bbt describtion table
 * @offs: block number offset in the table
 *
 * Read the bad block table starting from page.
 */
अटल पूर्णांक पढ़ो_bbt(काष्ठा nand_chip *this, uपूर्णांक8_t *buf, पूर्णांक page, पूर्णांक num,
		    काष्ठा nand_bbt_descr *td, पूर्णांक offs)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	पूर्णांक res, ret = 0, i, j, act = 0;
	माप_प्रकार retlen, len, totlen;
	loff_t from;
	पूर्णांक bits = td->options & न_अंकD_BBT_NRBITS_MSK;
	uपूर्णांक8_t msk = (uपूर्णांक8_t)((1 << bits) - 1);
	u32 marker_len;
	पूर्णांक reserved_block_code = td->reserved_block_code;

	totlen = (num * bits) >> 3;
	marker_len = add_marker_len(td);
	from = ((loff_t)page) << this->page_shअगरt;

	जबतक (totlen) अणु
		len = min(totlen, (माप_प्रकार)(1 << this->bbt_erase_shअगरt));
		अगर (marker_len) अणु
			/*
			 * In हाल the BBT marker is not in the OOB area it
			 * will be just in the first page.
			 */
			len -= marker_len;
			from += marker_len;
			marker_len = 0;
		पूर्ण
		res = mtd_पढ़ो(mtd, from, len, &retlen, buf);
		अगर (res < 0) अणु
			अगर (mtd_is_eccerr(res)) अणु
				pr_info("nand_bbt: ECC error in BBT at 0x%012llx\n",
					from & ~mtd->ग_लिखोsize);
				वापस res;
			पूर्ण अन्यथा अगर (mtd_is_bitflip(res)) अणु
				pr_info("nand_bbt: corrected error in BBT at 0x%012llx\n",
					from & ~mtd->ग_लिखोsize);
				ret = res;
			पूर्ण अन्यथा अणु
				pr_info("nand_bbt: error reading BBT\n");
				वापस res;
			पूर्ण
		पूर्ण

		/* Analyse data */
		क्रम (i = 0; i < len; i++) अणु
			uपूर्णांक8_t dat = buf[i];
			क्रम (j = 0; j < 8; j += bits, act++) अणु
				uपूर्णांक8_t पंचांगp = (dat >> j) & msk;
				अगर (पंचांगp == msk)
					जारी;
				अगर (reserved_block_code && (पंचांगp == reserved_block_code)) अणु
					pr_info("nand_read_bbt: reserved block at 0x%012llx\n",
						 (loff_t)(offs + act) <<
						 this->bbt_erase_shअगरt);
					bbt_mark_entry(this, offs + act,
							BBT_BLOCK_RESERVED);
					mtd->ecc_stats.bbtblocks++;
					जारी;
				पूर्ण
				/*
				 * Leave it क्रम now, अगर it's matured we can
				 * move this message to pr_debug.
				 */
				pr_info("nand_read_bbt: bad block at 0x%012llx\n",
					 (loff_t)(offs + act) <<
					 this->bbt_erase_shअगरt);
				/* Factory marked bad or worn out? */
				अगर (पंचांगp == 0)
					bbt_mark_entry(this, offs + act,
							BBT_BLOCK_FACTORY_BAD);
				अन्यथा
					bbt_mark_entry(this, offs + act,
							BBT_BLOCK_WORN);
				mtd->ecc_stats.badblocks++;
			पूर्ण
		पूर्ण
		totlen -= len;
		from += len;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * पढ़ो_असल_bbt - [GENERIC] Read the bad block table starting at a given page
 * @this: न_अंकD chip object
 * @buf: temporary buffer
 * @td: descriptor क्रम the bad block table
 * @chip: पढ़ो the table क्रम a specअगरic chip, -1 पढ़ो all chips; applies only अगर
 *        न_अंकD_BBT_PERCHIP option is set
 *
 * Read the bad block table क्रम all chips starting at a given page. We assume
 * that the bbt bits are in consecutive order.
 */
अटल पूर्णांक पढ़ो_असल_bbt(काष्ठा nand_chip *this, uपूर्णांक8_t *buf,
			काष्ठा nand_bbt_descr *td, पूर्णांक chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	u64 tarमाला_लोize = nanddev_target_size(&this->base);
	पूर्णांक res = 0, i;

	अगर (td->options & न_अंकD_BBT_PERCHIP) अणु
		पूर्णांक offs = 0;
		क्रम (i = 0; i < nanddev_ntarमाला_लो(&this->base); i++) अणु
			अगर (chip == -1 || chip == i)
				res = पढ़ो_bbt(this, buf, td->pages[i],
					tarमाला_लोize >> this->bbt_erase_shअगरt,
					td, offs);
			अगर (res)
				वापस res;
			offs += tarमाला_लोize >> this->bbt_erase_shअगरt;
		पूर्ण
	पूर्ण अन्यथा अणु
		res = पढ़ो_bbt(this, buf, td->pages[0],
				mtd->size >> this->bbt_erase_shअगरt, td, 0);
		अगर (res)
			वापस res;
	पूर्ण
	वापस 0;
पूर्ण

/* BBT marker is in the first page, no OOB */
अटल पूर्णांक scan_पढ़ो_data(काष्ठा nand_chip *this, uपूर्णांक8_t *buf, loff_t offs,
			  काष्ठा nand_bbt_descr *td)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	माप_प्रकार retlen;
	माप_प्रकार len;

	len = td->len;
	अगर (td->options & न_अंकD_BBT_VERSION)
		len++;

	वापस mtd_पढ़ो(mtd, offs, len, &retlen, buf);
पूर्ण

/**
 * scan_पढ़ो_oob - [GENERIC] Scan data+OOB region to buffer
 * @this: न_अंकD chip object
 * @buf: temporary buffer
 * @offs: offset at which to scan
 * @len: length of data region to पढ़ो
 *
 * Scan पढ़ो data from data+OOB. May traverse multiple pages, पूर्णांकerleaving
 * page,OOB,page,OOB,... in buf. Completes transfer and वापसs the "strongest"
 * ECC condition (error or bitflip). May quit on the first (non-ECC) error.
 */
अटल पूर्णांक scan_पढ़ो_oob(काष्ठा nand_chip *this, uपूर्णांक8_t *buf, loff_t offs,
			 माप_प्रकार len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	काष्ठा mtd_oob_ops ops;
	पूर्णांक res, ret = 0;

	ops.mode = MTD_OPS_PLACE_OOB;
	ops.ooboffs = 0;
	ops.ooblen = mtd->oobsize;

	जबतक (len > 0) अणु
		ops.datbuf = buf;
		ops.len = min(len, (माप_प्रकार)mtd->ग_लिखोsize);
		ops.oobbuf = buf + ops.len;

		res = mtd_पढ़ो_oob(mtd, offs, &ops);
		अगर (res) अणु
			अगर (!mtd_is_bitflip_or_eccerr(res))
				वापस res;
			अन्यथा अगर (mtd_is_eccerr(res) || !ret)
				ret = res;
		पूर्ण

		buf += mtd->oobsize + mtd->ग_लिखोsize;
		len -= mtd->ग_लिखोsize;
		offs += mtd->ग_लिखोsize;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक scan_पढ़ो(काष्ठा nand_chip *this, uपूर्णांक8_t *buf, loff_t offs,
		     माप_प्रकार len, काष्ठा nand_bbt_descr *td)
अणु
	अगर (td->options & न_अंकD_BBT_NO_OOB)
		वापस scan_पढ़ो_data(this, buf, offs, td);
	अन्यथा
		वापस scan_पढ़ो_oob(this, buf, offs, len);
पूर्ण

/* Scan ग_लिखो data with oob to flash */
अटल पूर्णांक scan_ग_लिखो_bbt(काष्ठा nand_chip *this, loff_t offs, माप_प्रकार len,
			  uपूर्णांक8_t *buf, uपूर्णांक8_t *oob)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	काष्ठा mtd_oob_ops ops;

	ops.mode = MTD_OPS_PLACE_OOB;
	ops.ooboffs = 0;
	ops.ooblen = mtd->oobsize;
	ops.datbuf = buf;
	ops.oobbuf = oob;
	ops.len = len;

	वापस mtd_ग_लिखो_oob(mtd, offs, &ops);
पूर्ण

अटल u32 bbt_get_ver_offs(काष्ठा nand_chip *this, काष्ठा nand_bbt_descr *td)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	u32 ver_offs = td->veroffs;

	अगर (!(td->options & न_अंकD_BBT_NO_OOB))
		ver_offs += mtd->ग_लिखोsize;
	वापस ver_offs;
पूर्ण

/**
 * पढ़ो_असल_bbts - [GENERIC] Read the bad block table(s) क्रम all chips starting at a given page
 * @this: न_अंकD chip object
 * @buf: temporary buffer
 * @td: descriptor क्रम the bad block table
 * @md:	descriptor क्रम the bad block table mirror
 *
 * Read the bad block table(s) क्रम all chips starting at a given page. We
 * assume that the bbt bits are in consecutive order.
 */
अटल व्योम पढ़ो_असल_bbts(काष्ठा nand_chip *this, uपूर्णांक8_t *buf,
			  काष्ठा nand_bbt_descr *td, काष्ठा nand_bbt_descr *md)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(this);

	/* Read the primary version, अगर available */
	अगर (td->options & न_अंकD_BBT_VERSION) अणु
		scan_पढ़ो(this, buf, (loff_t)td->pages[0] << this->page_shअगरt,
			  mtd->ग_लिखोsize, td);
		td->version[0] = buf[bbt_get_ver_offs(this, td)];
		pr_info("Bad block table at page %d, version 0x%02X\n",
			 td->pages[0], td->version[0]);
	पूर्ण

	/* Read the mirror version, अगर available */
	अगर (md && (md->options & न_अंकD_BBT_VERSION)) अणु
		scan_पढ़ो(this, buf, (loff_t)md->pages[0] << this->page_shअगरt,
			  mtd->ग_लिखोsize, md);
		md->version[0] = buf[bbt_get_ver_offs(this, md)];
		pr_info("Bad block table at page %d, version 0x%02X\n",
			 md->pages[0], md->version[0]);
	पूर्ण
पूर्ण

/* Scan a given block partially */
अटल पूर्णांक scan_block_fast(काष्ठा nand_chip *this, काष्ठा nand_bbt_descr *bd,
			   loff_t offs, uपूर्णांक8_t *buf)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(this);

	काष्ठा mtd_oob_ops ops;
	पूर्णांक ret, page_offset;

	ops.ooblen = mtd->oobsize;
	ops.oobbuf = buf;
	ops.ooboffs = 0;
	ops.datbuf = शून्य;
	ops.mode = MTD_OPS_PLACE_OOB;

	page_offset = nand_bbm_get_next_page(this, 0);

	जबतक (page_offset >= 0) अणु
		/*
		 * Read the full oob until पढ़ो_oob is fixed to handle single
		 * byte पढ़ोs क्रम 16 bit buswidth.
		 */
		ret = mtd_पढ़ो_oob(mtd, offs + (page_offset * mtd->ग_लिखोsize),
				   &ops);
		/* Ignore ECC errors when checking क्रम BBM */
		अगर (ret && !mtd_is_bitflip_or_eccerr(ret))
			वापस ret;

		अगर (check_लघु_pattern(buf, bd))
			वापस 1;

		page_offset = nand_bbm_get_next_page(this, page_offset + 1);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * create_bbt - [GENERIC] Create a bad block table by scanning the device
 * @this: न_अंकD chip object
 * @buf: temporary buffer
 * @bd: descriptor क्रम the good/bad block search pattern
 * @chip: create the table क्रम a specअगरic chip, -1 पढ़ो all chips; applies only
 *        अगर न_अंकD_BBT_PERCHIP option is set
 *
 * Create a bad block table by scanning the device क्रम the given good/bad block
 * identअगरy pattern.
 */
अटल पूर्णांक create_bbt(काष्ठा nand_chip *this, uपूर्णांक8_t *buf,
		      काष्ठा nand_bbt_descr *bd, पूर्णांक chip)
अणु
	u64 tarमाला_लोize = nanddev_target_size(&this->base);
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	पूर्णांक i, numblocks, startblock;
	loff_t from;

	pr_info("Scanning device for bad blocks\n");

	अगर (chip == -1) अणु
		numblocks = mtd->size >> this->bbt_erase_shअगरt;
		startblock = 0;
		from = 0;
	पूर्ण अन्यथा अणु
		अगर (chip >= nanddev_ntarमाला_लो(&this->base)) अणु
			pr_warn("create_bbt(): chipnr (%d) > available chips (%d)\n",
			        chip + 1, nanddev_ntarमाला_लो(&this->base));
			वापस -EINVAL;
		पूर्ण
		numblocks = tarमाला_लोize >> this->bbt_erase_shअगरt;
		startblock = chip * numblocks;
		numblocks += startblock;
		from = (loff_t)startblock << this->bbt_erase_shअगरt;
	पूर्ण

	क्रम (i = startblock; i < numblocks; i++) अणु
		पूर्णांक ret;

		BUG_ON(bd->options & न_अंकD_BBT_NO_OOB);

		ret = scan_block_fast(this, bd, from, buf);
		अगर (ret < 0)
			वापस ret;

		अगर (ret) अणु
			bbt_mark_entry(this, i, BBT_BLOCK_FACTORY_BAD);
			pr_warn("Bad eraseblock %d at 0x%012llx\n",
				i, (अचिन्हित दीर्घ दीर्घ)from);
			mtd->ecc_stats.badblocks++;
		पूर्ण

		from += (1 << this->bbt_erase_shअगरt);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * search_bbt - [GENERIC] scan the device क्रम a specअगरic bad block table
 * @this: न_अंकD chip object
 * @buf: temporary buffer
 * @td: descriptor क्रम the bad block table
 *
 * Read the bad block table by searching क्रम a given ident pattern. Search is
 * preक्रमmed either from the beginning up or from the end of the device
 * करोwnwards. The search starts always at the start of a block. If the option
 * न_अंकD_BBT_PERCHIP is given, each chip is searched क्रम a bbt, which contains
 * the bad block inक्रमmation of this chip. This is necessary to provide support
 * क्रम certain DOC devices.
 *
 * The bbt ident pattern resides in the oob area of the first page in a block.
 */
अटल पूर्णांक search_bbt(काष्ठा nand_chip *this, uपूर्णांक8_t *buf,
		      काष्ठा nand_bbt_descr *td)
अणु
	u64 tarमाला_लोize = nanddev_target_size(&this->base);
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	पूर्णांक i, chips;
	पूर्णांक startblock, block, dir;
	पूर्णांक scanlen = mtd->ग_लिखोsize + mtd->oobsize;
	पूर्णांक bbtblocks;
	पूर्णांक blocktopage = this->bbt_erase_shअगरt - this->page_shअगरt;

	/* Search direction top -> करोwn? */
	अगर (td->options & न_अंकD_BBT_LASTBLOCK) अणु
		startblock = (mtd->size >> this->bbt_erase_shअगरt) - 1;
		dir = -1;
	पूर्ण अन्यथा अणु
		startblock = 0;
		dir = 1;
	पूर्ण

	/* Do we have a bbt per chip? */
	अगर (td->options & न_अंकD_BBT_PERCHIP) अणु
		chips = nanddev_ntarमाला_लो(&this->base);
		bbtblocks = tarमाला_लोize >> this->bbt_erase_shअगरt;
		startblock &= bbtblocks - 1;
	पूर्ण अन्यथा अणु
		chips = 1;
		bbtblocks = mtd->size >> this->bbt_erase_shअगरt;
	पूर्ण

	क्रम (i = 0; i < chips; i++) अणु
		/* Reset version inक्रमmation */
		td->version[i] = 0;
		td->pages[i] = -1;
		/* Scan the maximum number of blocks */
		क्रम (block = 0; block < td->maxblocks; block++) अणु

			पूर्णांक actblock = startblock + dir * block;
			loff_t offs = (loff_t)actblock << this->bbt_erase_shअगरt;

			/* Read first page */
			scan_पढ़ो(this, buf, offs, mtd->ग_लिखोsize, td);
			अगर (!check_pattern(buf, scanlen, mtd->ग_लिखोsize, td)) अणु
				td->pages[i] = actblock << blocktopage;
				अगर (td->options & न_अंकD_BBT_VERSION) अणु
					offs = bbt_get_ver_offs(this, td);
					td->version[i] = buf[offs];
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		startblock += tarमाला_लोize >> this->bbt_erase_shअगरt;
	पूर्ण
	/* Check, अगर we found a bbt क्रम each requested chip */
	क्रम (i = 0; i < chips; i++) अणु
		अगर (td->pages[i] == -1)
			pr_warn("Bad block table not found for chip %d\n", i);
		अन्यथा
			pr_info("Bad block table found at page %d, version 0x%02X\n",
				td->pages[i], td->version[i]);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * search_पढ़ो_bbts - [GENERIC] scan the device क्रम bad block table(s)
 * @this: न_अंकD chip object
 * @buf: temporary buffer
 * @td: descriptor क्रम the bad block table
 * @md: descriptor क्रम the bad block table mirror
 *
 * Search and पढ़ो the bad block table(s).
 */
अटल व्योम search_पढ़ो_bbts(काष्ठा nand_chip *this, uपूर्णांक8_t *buf,
			     काष्ठा nand_bbt_descr *td,
			     काष्ठा nand_bbt_descr *md)
अणु
	/* Search the primary table */
	search_bbt(this, buf, td);

	/* Search the mirror table */
	अगर (md)
		search_bbt(this, buf, md);
पूर्ण

/**
 * get_bbt_block - Get the first valid eraseblock suitable to store a BBT
 * @this: the न_अंकD device
 * @td: the BBT description
 * @md: the mirror BBT descriptor
 * @chip: the CHIP selector
 *
 * This functions वापसs a positive block number poपूर्णांकing a valid eraseblock
 * suitable to store a BBT (i.e. in the range reserved क्रम BBT), or -ENOSPC अगर
 * all blocks are alपढ़ोy used of marked bad. If td->pages[chip] was alपढ़ोy
 * poपूर्णांकing to a valid block we re-use it, otherwise we search क्रम the next
 * valid one.
 */
अटल पूर्णांक get_bbt_block(काष्ठा nand_chip *this, काष्ठा nand_bbt_descr *td,
			 काष्ठा nand_bbt_descr *md, पूर्णांक chip)
अणु
	u64 tarमाला_लोize = nanddev_target_size(&this->base);
	पूर्णांक startblock, dir, page, numblocks, i;

	/*
	 * There was alपढ़ोy a version of the table, reuse the page. This
	 * applies क्रम असलolute placement too, as we have the page number in
	 * td->pages.
	 */
	अगर (td->pages[chip] != -1)
		वापस td->pages[chip] >>
				(this->bbt_erase_shअगरt - this->page_shअगरt);

	numblocks = (पूर्णांक)(tarमाला_लोize >> this->bbt_erase_shअगरt);
	अगर (!(td->options & न_अंकD_BBT_PERCHIP))
		numblocks *= nanddev_ntarमाला_लो(&this->base);

	/*
	 * Automatic placement of the bad block table. Search direction
	 * top -> करोwn?
	 */
	अगर (td->options & न_अंकD_BBT_LASTBLOCK) अणु
		startblock = numblocks * (chip + 1) - 1;
		dir = -1;
	पूर्ण अन्यथा अणु
		startblock = chip * numblocks;
		dir = 1;
	पूर्ण

	क्रम (i = 0; i < td->maxblocks; i++) अणु
		पूर्णांक block = startblock + dir * i;

		/* Check, अगर the block is bad */
		चयन (bbt_get_entry(this, block)) अणु
		हाल BBT_BLOCK_WORN:
		हाल BBT_BLOCK_FACTORY_BAD:
			जारी;
		पूर्ण

		page = block << (this->bbt_erase_shअगरt - this->page_shअगरt);

		/* Check, अगर the block is used by the mirror table */
		अगर (!md || md->pages[chip] != page)
			वापस block;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

/**
 * mark_bbt_block_bad - Mark one of the block reserved क्रम BBT bad
 * @this: the न_अंकD device
 * @td: the BBT description
 * @chip: the CHIP selector
 * @block: the BBT block to mark
 *
 * Blocks reserved क्रम BBT can become bad. This functions is an helper to mark
 * such blocks as bad. It takes care of updating the in-memory BBT, marking the
 * block as bad using a bad block marker and invalidating the associated
 * td->pages[] entry.
 */
अटल व्योम mark_bbt_block_bad(काष्ठा nand_chip *this,
			       काष्ठा nand_bbt_descr *td,
			       पूर्णांक chip, पूर्णांक block)
अणु
	loff_t to;
	पूर्णांक res;

	bbt_mark_entry(this, block, BBT_BLOCK_WORN);

	to = (loff_t)block << this->bbt_erase_shअगरt;
	res = nand_markbad_bbm(this, to);
	अगर (res)
		pr_warn("nand_bbt: error %d while marking block %d bad\n",
			res, block);

	td->pages[chip] = -1;
पूर्ण

/**
 * ग_लिखो_bbt - [GENERIC] (Re)ग_लिखो the bad block table
 * @this: न_अंकD chip object
 * @buf: temporary buffer
 * @td: descriptor क्रम the bad block table
 * @md: descriptor क्रम the bad block table mirror
 * @chipsel: selector क्रम a specअगरic chip, -1 क्रम all
 *
 * (Re)ग_लिखो the bad block table.
 */
अटल पूर्णांक ग_लिखो_bbt(काष्ठा nand_chip *this, uपूर्णांक8_t *buf,
		     काष्ठा nand_bbt_descr *td, काष्ठा nand_bbt_descr *md,
		     पूर्णांक chipsel)
अणु
	u64 tarमाला_लोize = nanddev_target_size(&this->base);
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	काष्ठा erase_info einfo;
	पूर्णांक i, res, chip = 0;
	पूर्णांक bits, page, offs, numblocks, sft, sfपंचांगsk;
	पूर्णांक nrchips, pageoffs, ooboffs;
	uपूर्णांक8_t msk[4];
	uपूर्णांक8_t rcode = td->reserved_block_code;
	माप_प्रकार retlen, len = 0;
	loff_t to;
	काष्ठा mtd_oob_ops ops;

	ops.ooblen = mtd->oobsize;
	ops.ooboffs = 0;
	ops.datbuf = शून्य;
	ops.mode = MTD_OPS_PLACE_OOB;

	अगर (!rcode)
		rcode = 0xff;
	/* Write bad block table per chip rather than per device? */
	अगर (td->options & न_अंकD_BBT_PERCHIP) अणु
		numblocks = (पूर्णांक)(tarमाला_लोize >> this->bbt_erase_shअगरt);
		/* Full device ग_लिखो or specअगरic chip? */
		अगर (chipsel == -1) अणु
			nrchips = nanddev_ntarमाला_लो(&this->base);
		पूर्ण अन्यथा अणु
			nrchips = chipsel + 1;
			chip = chipsel;
		पूर्ण
	पूर्ण अन्यथा अणु
		numblocks = (पूर्णांक)(mtd->size >> this->bbt_erase_shअगरt);
		nrchips = 1;
	पूर्ण

	/* Loop through the chips */
	जबतक (chip < nrchips) अणु
		पूर्णांक block;

		block = get_bbt_block(this, td, md, chip);
		अगर (block < 0) अणु
			pr_err("No space left to write bad block table\n");
			res = block;
			जाओ outerr;
		पूर्ण

		/*
		 * get_bbt_block() वापसs a block number, shअगरt the value to
		 * get a page number.
		 */
		page = block << (this->bbt_erase_shअगरt - this->page_shअगरt);

		/* Set up shअगरt count and masks क्रम the flash table */
		bits = td->options & न_अंकD_BBT_NRBITS_MSK;
		msk[2] = ~rcode;
		चयन (bits) अणु
		हाल 1: sft = 3; sfपंचांगsk = 0x07; msk[0] = 0x00; msk[1] = 0x01;
			msk[3] = 0x01;
			अवरोध;
		हाल 2: sft = 2; sfपंचांगsk = 0x06; msk[0] = 0x00; msk[1] = 0x01;
			msk[3] = 0x03;
			अवरोध;
		हाल 4: sft = 1; sfपंचांगsk = 0x04; msk[0] = 0x00; msk[1] = 0x0C;
			msk[3] = 0x0f;
			अवरोध;
		हाल 8: sft = 0; sfपंचांगsk = 0x00; msk[0] = 0x00; msk[1] = 0x0F;
			msk[3] = 0xff;
			अवरोध;
		शेष: वापस -EINVAL;
		पूर्ण

		to = ((loff_t)page) << this->page_shअगरt;

		/* Must we save the block contents? */
		अगर (td->options & न_अंकD_BBT_SAVECONTENT) अणु
			/* Make it block aligned */
			to &= ~(((loff_t)1 << this->bbt_erase_shअगरt) - 1);
			len = 1 << this->bbt_erase_shअगरt;
			res = mtd_पढ़ो(mtd, to, len, &retlen, buf);
			अगर (res < 0) अणु
				अगर (retlen != len) अणु
					pr_info("nand_bbt: error reading block for writing the bad block table\n");
					वापस res;
				पूर्ण
				pr_warn("nand_bbt: ECC error while reading block for writing bad block table\n");
			पूर्ण
			/* Read oob data */
			ops.ooblen = (len >> this->page_shअगरt) * mtd->oobsize;
			ops.oobbuf = &buf[len];
			res = mtd_पढ़ो_oob(mtd, to + mtd->ग_लिखोsize, &ops);
			अगर (res < 0 || ops.oobretlen != ops.ooblen)
				जाओ outerr;

			/* Calc the byte offset in the buffer */
			pageoffs = page - (पूर्णांक)(to >> this->page_shअगरt);
			offs = pageoffs << this->page_shअगरt;
			/* Preset the bbt area with 0xff */
			स_रखो(&buf[offs], 0xff, (माप_प्रकार)(numblocks >> sft));
			ooboffs = len + (pageoffs * mtd->oobsize);

		पूर्ण अन्यथा अगर (td->options & न_अंकD_BBT_NO_OOB) अणु
			ooboffs = 0;
			offs = td->len;
			/* The version byte */
			अगर (td->options & न_अंकD_BBT_VERSION)
				offs++;
			/* Calc length */
			len = (माप_प्रकार)(numblocks >> sft);
			len += offs;
			/* Make it page aligned! */
			len = ALIGN(len, mtd->ग_लिखोsize);
			/* Preset the buffer with 0xff */
			स_रखो(buf, 0xff, len);
			/* Pattern is located at the begin of first page */
			स_नकल(buf, td->pattern, td->len);
		पूर्ण अन्यथा अणु
			/* Calc length */
			len = (माप_प्रकार)(numblocks >> sft);
			/* Make it page aligned! */
			len = ALIGN(len, mtd->ग_लिखोsize);
			/* Preset the buffer with 0xff */
			स_रखो(buf, 0xff, len +
			       (len >> this->page_shअगरt)* mtd->oobsize);
			offs = 0;
			ooboffs = len;
			/* Pattern is located in oob area of first page */
			स_नकल(&buf[ooboffs + td->offs], td->pattern, td->len);
		पूर्ण

		अगर (td->options & न_अंकD_BBT_VERSION)
			buf[ooboffs + td->veroffs] = td->version[chip];

		/* Walk through the memory table */
		क्रम (i = 0; i < numblocks; i++) अणु
			uपूर्णांक8_t dat;
			पूर्णांक sftcnt = (i << (3 - sft)) & sfपंचांगsk;
			dat = bbt_get_entry(this, chip * numblocks + i);
			/* Do not store the reserved bbt blocks! */
			buf[offs + (i >> sft)] &= ~(msk[dat] << sftcnt);
		पूर्ण

		स_रखो(&einfo, 0, माप(einfo));
		einfo.addr = to;
		einfo.len = 1 << this->bbt_erase_shअगरt;
		res = nand_erase_nand(this, &einfo, 1);
		अगर (res < 0) अणु
			pr_warn("nand_bbt: error while erasing BBT block %d\n",
				res);
			mark_bbt_block_bad(this, td, chip, block);
			जारी;
		पूर्ण

		res = scan_ग_लिखो_bbt(this, to, len, buf,
				     td->options & न_अंकD_BBT_NO_OOB ?
				     शून्य : &buf[len]);
		अगर (res < 0) अणु
			pr_warn("nand_bbt: error while writing BBT block %d\n",
				res);
			mark_bbt_block_bad(this, td, chip, block);
			जारी;
		पूर्ण

		pr_info("Bad block table written to 0x%012llx, version 0x%02X\n",
			 (अचिन्हित दीर्घ दीर्घ)to, td->version[chip]);

		/* Mark it as used */
		td->pages[chip++] = page;
	पूर्ण
	वापस 0;

 outerr:
	pr_warn("nand_bbt: error while writing bad block table %d\n", res);
	वापस res;
पूर्ण

/**
 * nand_memory_bbt - [GENERIC] create a memory based bad block table
 * @this: न_अंकD chip object
 * @bd: descriptor क्रम the good/bad block search pattern
 *
 * The function creates a memory based bbt by scanning the device क्रम
 * manufacturer / software marked good / bad blocks.
 */
अटल अंतरभूत पूर्णांक nand_memory_bbt(काष्ठा nand_chip *this,
				  काष्ठा nand_bbt_descr *bd)
अणु
	u8 *pagebuf = nand_get_data_buf(this);

	वापस create_bbt(this, pagebuf, bd, -1);
पूर्ण

/**
 * check_create - [GENERIC] create and ग_लिखो bbt(s) अगर necessary
 * @this: the न_अंकD device
 * @buf: temporary buffer
 * @bd: descriptor क्रम the good/bad block search pattern
 *
 * The function checks the results of the previous call to पढ़ो_bbt and creates
 * / updates the bbt(s) अगर necessary. Creation is necessary अगर no bbt was found
 * क्रम the chip/device. Update is necessary अगर one of the tables is missing or
 * the version nr. of one table is less than the other.
 */
अटल पूर्णांक check_create(काष्ठा nand_chip *this, uपूर्णांक8_t *buf,
			काष्ठा nand_bbt_descr *bd)
अणु
	पूर्णांक i, chips, ग_लिखोops, create, chipsel, res, res2;
	काष्ठा nand_bbt_descr *td = this->bbt_td;
	काष्ठा nand_bbt_descr *md = this->bbt_md;
	काष्ठा nand_bbt_descr *rd, *rd2;

	/* Do we have a bbt per chip? */
	अगर (td->options & न_अंकD_BBT_PERCHIP)
		chips = nanddev_ntarमाला_लो(&this->base);
	अन्यथा
		chips = 1;

	क्रम (i = 0; i < chips; i++) अणु
		ग_लिखोops = 0;
		create = 0;
		rd = शून्य;
		rd2 = शून्य;
		res = res2 = 0;
		/* Per chip or per device? */
		chipsel = (td->options & न_अंकD_BBT_PERCHIP) ? i : -1;
		/* Mirrored table available? */
		अगर (md) अणु
			अगर (td->pages[i] == -1 && md->pages[i] == -1) अणु
				create = 1;
				ग_लिखोops = 0x03;
			पूर्ण अन्यथा अगर (td->pages[i] == -1) अणु
				rd = md;
				ग_लिखोops = 0x01;
			पूर्ण अन्यथा अगर (md->pages[i] == -1) अणु
				rd = td;
				ग_लिखोops = 0x02;
			पूर्ण अन्यथा अगर (td->version[i] == md->version[i]) अणु
				rd = td;
				अगर (!(td->options & न_अंकD_BBT_VERSION))
					rd2 = md;
			पूर्ण अन्यथा अगर (((पूर्णांक8_t)(td->version[i] - md->version[i])) > 0) अणु
				rd = td;
				ग_लिखोops = 0x02;
			पूर्ण अन्यथा अणु
				rd = md;
				ग_लिखोops = 0x01;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (td->pages[i] == -1) अणु
				create = 1;
				ग_लिखोops = 0x01;
			पूर्ण अन्यथा अणु
				rd = td;
			पूर्ण
		पूर्ण

		अगर (create) अणु
			/* Create the bad block table by scanning the device? */
			अगर (!(td->options & न_अंकD_BBT_CREATE))
				जारी;

			/* Create the table in memory by scanning the chip(s) */
			अगर (!(this->bbt_options & न_अंकD_BBT_CREATE_EMPTY))
				create_bbt(this, buf, bd, chipsel);

			td->version[i] = 1;
			अगर (md)
				md->version[i] = 1;
		पूर्ण

		/* Read back first? */
		अगर (rd) अणु
			res = पढ़ो_असल_bbt(this, buf, rd, chipsel);
			अगर (mtd_is_eccerr(res)) अणु
				/* Mark table as invalid */
				rd->pages[i] = -1;
				rd->version[i] = 0;
				i--;
				जारी;
			पूर्ण
		पूर्ण
		/* If they weren't versioned, पढ़ो both */
		अगर (rd2) अणु
			res2 = पढ़ो_असल_bbt(this, buf, rd2, chipsel);
			अगर (mtd_is_eccerr(res2)) अणु
				/* Mark table as invalid */
				rd2->pages[i] = -1;
				rd2->version[i] = 0;
				i--;
				जारी;
			पूर्ण
		पूर्ण

		/* Scrub the flash table(s)? */
		अगर (mtd_is_bitflip(res) || mtd_is_bitflip(res2))
			ग_लिखोops = 0x03;

		/* Update version numbers beक्रमe writing */
		अगर (md) अणु
			td->version[i] = max(td->version[i], md->version[i]);
			md->version[i] = td->version[i];
		पूर्ण

		/* Write the bad block table to the device? */
		अगर ((ग_लिखोops & 0x01) && (td->options & न_अंकD_BBT_WRITE)) अणु
			res = ग_लिखो_bbt(this, buf, td, md, chipsel);
			अगर (res < 0)
				वापस res;
		पूर्ण

		/* Write the mirror bad block table to the device? */
		अगर ((ग_लिखोops & 0x02) && md && (md->options & न_अंकD_BBT_WRITE)) अणु
			res = ग_लिखो_bbt(this, buf, md, td, chipsel);
			अगर (res < 0)
				वापस res;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * nand_update_bbt - update bad block table(s)
 * @this: the न_अंकD device
 * @offs: the offset of the newly marked block
 *
 * The function updates the bad block table(s).
 */
अटल पूर्णांक nand_update_bbt(काष्ठा nand_chip *this, loff_t offs)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	पूर्णांक len, res = 0;
	पूर्णांक chip, chipsel;
	uपूर्णांक8_t *buf;
	काष्ठा nand_bbt_descr *td = this->bbt_td;
	काष्ठा nand_bbt_descr *md = this->bbt_md;

	अगर (!this->bbt || !td)
		वापस -EINVAL;

	/* Allocate a temporary buffer क्रम one eraseblock incl. oob */
	len = (1 << this->bbt_erase_shअगरt);
	len += (len >> this->page_shअगरt) * mtd->oobsize;
	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* Do we have a bbt per chip? */
	अगर (td->options & न_अंकD_BBT_PERCHIP) अणु
		chip = (पूर्णांक)(offs >> this->chip_shअगरt);
		chipsel = chip;
	पूर्ण अन्यथा अणु
		chip = 0;
		chipsel = -1;
	पूर्ण

	td->version[chip]++;
	अगर (md)
		md->version[chip]++;

	/* Write the bad block table to the device? */
	अगर (td->options & न_अंकD_BBT_WRITE) अणु
		res = ग_लिखो_bbt(this, buf, td, md, chipsel);
		अगर (res < 0)
			जाओ out;
	पूर्ण
	/* Write the mirror bad block table to the device? */
	अगर (md && (md->options & न_अंकD_BBT_WRITE)) अणु
		res = ग_लिखो_bbt(this, buf, md, td, chipsel);
	पूर्ण

 out:
	kमुक्त(buf);
	वापस res;
पूर्ण

/**
 * mark_bbt_region - [GENERIC] mark the bad block table regions
 * @this: the न_अंकD device
 * @td: bad block table descriptor
 *
 * The bad block table regions are marked as "bad" to prevent accidental
 * erasures / ग_लिखोs. The regions are identअगरied by the mark 0x02.
 */
अटल व्योम mark_bbt_region(काष्ठा nand_chip *this, काष्ठा nand_bbt_descr *td)
अणु
	u64 tarमाला_लोize = nanddev_target_size(&this->base);
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	पूर्णांक i, j, chips, block, nrblocks, update;
	uपूर्णांक8_t oldval;

	/* Do we have a bbt per chip? */
	अगर (td->options & न_अंकD_BBT_PERCHIP) अणु
		chips = nanddev_ntarमाला_लो(&this->base);
		nrblocks = (पूर्णांक)(tarमाला_लोize >> this->bbt_erase_shअगरt);
	पूर्ण अन्यथा अणु
		chips = 1;
		nrblocks = (पूर्णांक)(mtd->size >> this->bbt_erase_shअगरt);
	पूर्ण

	क्रम (i = 0; i < chips; i++) अणु
		अगर ((td->options & न_अंकD_BBT_ABSPAGE) ||
		    !(td->options & न_अंकD_BBT_WRITE)) अणु
			अगर (td->pages[i] == -1)
				जारी;
			block = td->pages[i] >> (this->bbt_erase_shअगरt - this->page_shअगरt);
			oldval = bbt_get_entry(this, block);
			bbt_mark_entry(this, block, BBT_BLOCK_RESERVED);
			अगर ((oldval != BBT_BLOCK_RESERVED) &&
					td->reserved_block_code)
				nand_update_bbt(this, (loff_t)block <<
						this->bbt_erase_shअगरt);
			जारी;
		पूर्ण
		update = 0;
		अगर (td->options & न_अंकD_BBT_LASTBLOCK)
			block = ((i + 1) * nrblocks) - td->maxblocks;
		अन्यथा
			block = i * nrblocks;
		क्रम (j = 0; j < td->maxblocks; j++) अणु
			oldval = bbt_get_entry(this, block);
			bbt_mark_entry(this, block, BBT_BLOCK_RESERVED);
			अगर (oldval != BBT_BLOCK_RESERVED)
				update = 1;
			block++;
		पूर्ण
		/*
		 * If we want reserved blocks to be recorded to flash, and some
		 * new ones have been marked, then we need to update the stored
		 * bbts.  This should only happen once.
		 */
		अगर (update && td->reserved_block_code)
			nand_update_bbt(this, (loff_t)(block - 1) <<
					this->bbt_erase_shअगरt);
	पूर्ण
पूर्ण

/**
 * verअगरy_bbt_descr - verअगरy the bad block description
 * @this: the न_अंकD device
 * @bd: the table to verअगरy
 *
 * This functions perक्रमms a few sanity checks on the bad block description
 * table.
 */
अटल व्योम verअगरy_bbt_descr(काष्ठा nand_chip *this, काष्ठा nand_bbt_descr *bd)
अणु
	u64 tarमाला_लोize = nanddev_target_size(&this->base);
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	u32 pattern_len;
	u32 bits;
	u32 table_size;

	अगर (!bd)
		वापस;

	pattern_len = bd->len;
	bits = bd->options & न_अंकD_BBT_NRBITS_MSK;

	BUG_ON((this->bbt_options & न_अंकD_BBT_NO_OOB) &&
			!(this->bbt_options & न_अंकD_BBT_USE_FLASH));
	BUG_ON(!bits);

	अगर (bd->options & न_अंकD_BBT_VERSION)
		pattern_len++;

	अगर (bd->options & न_अंकD_BBT_NO_OOB) अणु
		BUG_ON(!(this->bbt_options & न_अंकD_BBT_USE_FLASH));
		BUG_ON(!(this->bbt_options & न_अंकD_BBT_NO_OOB));
		BUG_ON(bd->offs);
		अगर (bd->options & न_अंकD_BBT_VERSION)
			BUG_ON(bd->veroffs != bd->len);
		BUG_ON(bd->options & न_अंकD_BBT_SAVECONTENT);
	पूर्ण

	अगर (bd->options & न_अंकD_BBT_PERCHIP)
		table_size = tarमाला_लोize >> this->bbt_erase_shअगरt;
	अन्यथा
		table_size = mtd->size >> this->bbt_erase_shअगरt;
	table_size >>= 3;
	table_size *= bits;
	अगर (bd->options & न_अंकD_BBT_NO_OOB)
		table_size += pattern_len;
	BUG_ON(table_size > (1 << this->bbt_erase_shअगरt));
पूर्ण

/**
 * nand_scan_bbt - [न_अंकD Interface] scan, find, पढ़ो and maybe create bad block table(s)
 * @this: the न_अंकD device
 * @bd: descriptor क्रम the good/bad block search pattern
 *
 * The function checks, अगर a bad block table(s) is/are alपढ़ोy available. If
 * not it scans the device क्रम manufacturer marked good / bad blocks and ग_लिखोs
 * the bad block table(s) to the selected place.
 *
 * The bad block table memory is allocated here. It must be मुक्तd by calling
 * the nand_मुक्त_bbt function.
 */
अटल पूर्णांक nand_scan_bbt(काष्ठा nand_chip *this, काष्ठा nand_bbt_descr *bd)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	पूर्णांक len, res;
	uपूर्णांक8_t *buf;
	काष्ठा nand_bbt_descr *td = this->bbt_td;
	काष्ठा nand_bbt_descr *md = this->bbt_md;

	len = (mtd->size >> (this->bbt_erase_shअगरt + 2)) ? : 1;
	/*
	 * Allocate memory (2bit per block) and clear the memory bad block
	 * table.
	 */
	this->bbt = kzalloc(len, GFP_KERNEL);
	अगर (!this->bbt)
		वापस -ENOMEM;

	/*
	 * If no primary table descriptor is given, scan the device to build a
	 * memory based bad block table.
	 */
	अगर (!td) अणु
		अगर ((res = nand_memory_bbt(this, bd))) अणु
			pr_err("nand_bbt: can't scan flash and build the RAM-based BBT\n");
			जाओ err_मुक्त_bbt;
		पूर्ण
		वापस 0;
	पूर्ण
	verअगरy_bbt_descr(this, td);
	verअगरy_bbt_descr(this, md);

	/* Allocate a temporary buffer क्रम one eraseblock incl. oob */
	len = (1 << this->bbt_erase_shअगरt);
	len += (len >> this->page_shअगरt) * mtd->oobsize;
	buf = vदो_स्मृति(len);
	अगर (!buf) अणु
		res = -ENOMEM;
		जाओ err_मुक्त_bbt;
	पूर्ण

	/* Is the bbt at a given page? */
	अगर (td->options & न_अंकD_BBT_ABSPAGE) अणु
		पढ़ो_असल_bbts(this, buf, td, md);
	पूर्ण अन्यथा अणु
		/* Search the bad block table using a pattern in oob */
		search_पढ़ो_bbts(this, buf, td, md);
	पूर्ण

	res = check_create(this, buf, bd);
	अगर (res)
		जाओ err_मुक्त_buf;

	/* Prevent the bbt regions from erasing / writing */
	mark_bbt_region(this, td);
	अगर (md)
		mark_bbt_region(this, md);

	vमुक्त(buf);
	वापस 0;

err_मुक्त_buf:
	vमुक्त(buf);
err_मुक्त_bbt:
	kमुक्त(this->bbt);
	this->bbt = शून्य;
	वापस res;
पूर्ण

/*
 * Define some generic bad / good block scan pattern which are used
 * जबतक scanning a device क्रम factory marked good / bad blocks.
 */
अटल uपूर्णांक8_t scan_ff_pattern[] = अणु 0xff, 0xff पूर्ण;

/* Generic flash bbt descriptors */
अटल uपूर्णांक8_t bbt_pattern[] = अणु'B', 'b', 't', '0' पूर्ण;
अटल uपूर्णांक8_t mirror_pattern[] = अणु'1', 't', 'b', 'B' पूर्ण;

अटल काष्ठा nand_bbt_descr bbt_मुख्य_descr = अणु
	.options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE | न_अंकD_BBT_WRITE
		| न_अंकD_BBT_2BIT | न_अंकD_BBT_VERSION | न_अंकD_BBT_PERCHIP,
	.offs =	8,
	.len = 4,
	.veroffs = 12,
	.maxblocks = न_अंकD_BBT_SCAN_MAXBLOCKS,
	.pattern = bbt_pattern
पूर्ण;

अटल काष्ठा nand_bbt_descr bbt_mirror_descr = अणु
	.options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE | न_अंकD_BBT_WRITE
		| न_अंकD_BBT_2BIT | न_अंकD_BBT_VERSION | न_अंकD_BBT_PERCHIP,
	.offs =	8,
	.len = 4,
	.veroffs = 12,
	.maxblocks = न_अंकD_BBT_SCAN_MAXBLOCKS,
	.pattern = mirror_pattern
पूर्ण;

अटल काष्ठा nand_bbt_descr bbt_मुख्य_no_oob_descr = अणु
	.options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE | न_अंकD_BBT_WRITE
		| न_अंकD_BBT_2BIT | न_अंकD_BBT_VERSION | न_अंकD_BBT_PERCHIP
		| न_अंकD_BBT_NO_OOB,
	.len = 4,
	.veroffs = 4,
	.maxblocks = न_अंकD_BBT_SCAN_MAXBLOCKS,
	.pattern = bbt_pattern
पूर्ण;

अटल काष्ठा nand_bbt_descr bbt_mirror_no_oob_descr = अणु
	.options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE | न_अंकD_BBT_WRITE
		| न_अंकD_BBT_2BIT | न_अंकD_BBT_VERSION | न_अंकD_BBT_PERCHIP
		| न_अंकD_BBT_NO_OOB,
	.len = 4,
	.veroffs = 4,
	.maxblocks = न_अंकD_BBT_SCAN_MAXBLOCKS,
	.pattern = mirror_pattern
पूर्ण;

#घोषणा BADBLOCK_SCAN_MASK (~न_अंकD_BBT_NO_OOB)
/**
 * nand_create_badblock_pattern - [INTERN] Creates a BBT descriptor काष्ठाure
 * @this: न_अंकD chip to create descriptor क्रम
 *
 * This function allocates and initializes a nand_bbt_descr क्रम BBM detection
 * based on the properties of @this. The new descriptor is stored in
 * this->badblock_pattern. Thus, this->badblock_pattern should be शून्य when
 * passed to this function.
 */
अटल पूर्णांक nand_create_badblock_pattern(काष्ठा nand_chip *this)
अणु
	काष्ठा nand_bbt_descr *bd;
	अगर (this->badblock_pattern) अणु
		pr_warn("Bad block pattern already allocated; not replacing\n");
		वापस -EINVAL;
	पूर्ण
	bd = kzalloc(माप(*bd), GFP_KERNEL);
	अगर (!bd)
		वापस -ENOMEM;
	bd->options = this->bbt_options & BADBLOCK_SCAN_MASK;
	bd->offs = this->badblockpos;
	bd->len = (this->options & न_अंकD_BUSWIDTH_16) ? 2 : 1;
	bd->pattern = scan_ff_pattern;
	bd->options |= न_अंकD_BBT_DYNAMICSTRUCT;
	this->badblock_pattern = bd;
	वापस 0;
पूर्ण

/**
 * nand_create_bbt - [न_अंकD Interface] Select a शेष bad block table क्रम the device
 * @this: न_अंकD chip object
 *
 * This function selects the शेष bad block table support क्रम the device and
 * calls the nand_scan_bbt function.
 */
पूर्णांक nand_create_bbt(काष्ठा nand_chip *this)
अणु
	पूर्णांक ret;

	/* Is a flash based bad block table requested? */
	अगर (this->bbt_options & न_अंकD_BBT_USE_FLASH) अणु
		/* Use the शेष pattern descriptors */
		अगर (!this->bbt_td) अणु
			अगर (this->bbt_options & न_अंकD_BBT_NO_OOB) अणु
				this->bbt_td = &bbt_मुख्य_no_oob_descr;
				this->bbt_md = &bbt_mirror_no_oob_descr;
			पूर्ण अन्यथा अणु
				this->bbt_td = &bbt_मुख्य_descr;
				this->bbt_md = &bbt_mirror_descr;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		this->bbt_td = शून्य;
		this->bbt_md = शून्य;
	पूर्ण

	अगर (!this->badblock_pattern) अणु
		ret = nand_create_badblock_pattern(this);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस nand_scan_bbt(this, this->badblock_pattern);
पूर्ण
EXPORT_SYMBOL(nand_create_bbt);

/**
 * nand_isreserved_bbt - [न_अंकD Interface] Check अगर a block is reserved
 * @this: न_अंकD chip object
 * @offs: offset in the device
 */
पूर्णांक nand_isreserved_bbt(काष्ठा nand_chip *this, loff_t offs)
अणु
	पूर्णांक block;

	block = (पूर्णांक)(offs >> this->bbt_erase_shअगरt);
	वापस bbt_get_entry(this, block) == BBT_BLOCK_RESERVED;
पूर्ण

/**
 * nand_isbad_bbt - [न_अंकD Interface] Check अगर a block is bad
 * @this: न_अंकD chip object
 * @offs: offset in the device
 * @allowbbt: allow access to bad block table region
 */
पूर्णांक nand_isbad_bbt(काष्ठा nand_chip *this, loff_t offs, पूर्णांक allowbbt)
अणु
	पूर्णांक block, res;

	block = (पूर्णांक)(offs >> this->bbt_erase_shअगरt);
	res = bbt_get_entry(this, block);

	pr_debug("nand_isbad_bbt(): bbt info for offs 0x%08x: (block %d) 0x%02x\n",
		 (अचिन्हित पूर्णांक)offs, block, res);

	चयन (res) अणु
	हाल BBT_BLOCK_GOOD:
		वापस 0;
	हाल BBT_BLOCK_WORN:
		वापस 1;
	हाल BBT_BLOCK_RESERVED:
		वापस allowbbt ? 0 : 1;
	पूर्ण
	वापस 1;
पूर्ण

/**
 * nand_markbad_bbt - [न_अंकD Interface] Mark a block bad in the BBT
 * @this: न_अंकD chip object
 * @offs: offset of the bad block
 */
पूर्णांक nand_markbad_bbt(काष्ठा nand_chip *this, loff_t offs)
अणु
	पूर्णांक block, ret = 0;

	block = (पूर्णांक)(offs >> this->bbt_erase_shअगरt);

	/* Mark bad block in memory */
	bbt_mark_entry(this, block, BBT_BLOCK_WORN);

	/* Update flash-based bad block table */
	अगर (this->bbt_options & न_अंकD_BBT_USE_FLASH)
		ret = nand_update_bbt(this, offs);

	वापस ret;
पूर्ण
