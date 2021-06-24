<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Bad Block Table support क्रम the Oneन_अंकD driver
 *
 *  Copyright(c) 2005 Samsung Electronics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 *
 *  Derived from nand_bbt.c
 *
 *  TODO:
 *    Split BBT core and chip specअगरic BBT.
 */

#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/onenand.h>
#समावेश <linux/export.h>

/**
 * check_लघु_pattern - [GENERIC] check अगर a pattern is in the buffer
 * @buf:		the buffer to search
 * @len:		the length of buffer to search
 * @paglen:	the pagelength
 * @td:		search pattern descriptor
 *
 * Check क्रम a pattern at the given place. Used to search bad block
 * tables and good / bad block identअगरiers. Same as check_pattern, but
 * no optional empty check and the pattern is expected to start
 * at offset 0.
 *
 */
अटल पूर्णांक check_लघु_pattern(uपूर्णांक8_t *buf, पूर्णांक len, पूर्णांक paglen, काष्ठा nand_bbt_descr *td)
अणु
	पूर्णांक i;
	uपूर्णांक8_t *p = buf;

	/* Compare the pattern */
	क्रम (i = 0; i < td->len; i++) अणु
		अगर (p[i] != td->pattern[i])
			वापस -1;
	पूर्ण
        वापस 0;
पूर्ण

/**
 * create_bbt - [GENERIC] Create a bad block table by scanning the device
 * @mtd:		MTD device काष्ठाure
 * @buf:		temporary buffer
 * @bd:		descriptor क्रम the good/bad block search pattern
 * @chip:		create the table क्रम a specअगरic chip, -1 पढ़ो all chips.
 *              Applies only अगर न_अंकD_BBT_PERCHIP option is set
 *
 * Create a bad block table by scanning the device
 * क्रम the given good/bad block identअगरy pattern
 */
अटल पूर्णांक create_bbt(काष्ठा mtd_info *mtd, uपूर्णांक8_t *buf, काष्ठा nand_bbt_descr *bd, पूर्णांक chip)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	काष्ठा bbm_info *bbm = this->bbm;
	पूर्णांक i, j, numblocks, len, scanlen;
	पूर्णांक startblock;
	loff_t from;
	माप_प्रकार पढ़ोlen, ooblen;
	काष्ठा mtd_oob_ops ops;
	पूर्णांक rgn;

	prपूर्णांकk(KERN_INFO "Scanning device for bad blocks\n");

	len = 2;

	/* We need only पढ़ो few bytes from the OOB area */
	scanlen = ooblen = 0;
	पढ़ोlen = bd->len;

	/* chip == -1 हाल only */
	/* Note that numblocks is 2 * (real numblocks) here;
	 * see i += 2 below as it makses shअगरting and masking less painful
	 */
	numblocks = this->chipsize >> (bbm->bbt_erase_shअगरt - 1);
	startblock = 0;
	from = 0;

	ops.mode = MTD_OPS_PLACE_OOB;
	ops.ooblen = पढ़ोlen;
	ops.oobbuf = buf;
	ops.len = ops.ooboffs = ops.retlen = ops.oobretlen = 0;

	क्रम (i = startblock; i < numblocks; ) अणु
		पूर्णांक ret;

		क्रम (j = 0; j < len; j++) अणु
			/* No need to पढ़ो pages fully,
			 * just पढ़ो required OOB bytes */
			ret = onenand_bbt_पढ़ो_oob(mtd,
				from + j * this->ग_लिखोsize + bd->offs, &ops);

			/* If it is a initial bad block, just ignore it */
			अगर (ret == ONEन_अंकD_BBT_READ_FATAL_ERROR)
				वापस -EIO;

			अगर (ret || check_लघु_pattern(&buf[j * scanlen],
					       scanlen, this->ग_लिखोsize, bd)) अणु
				bbm->bbt[i >> 3] |= 0x03 << (i & 0x6);
				prपूर्णांकk(KERN_INFO "OneNAND eraseblock %d is an "
					"initial bad block\n", i >> 1);
				mtd->ecc_stats.badblocks++;
				अवरोध;
			पूर्ण
		पूर्ण
		i += 2;

		अगर (FLEXONEन_अंकD(this)) अणु
			rgn = flexonenand_region(mtd, from);
			from += mtd->eraseregions[rgn].erasesize;
		पूर्ण अन्यथा
			from += (1 << bbm->bbt_erase_shअगरt);
	पूर्ण

	वापस 0;
पूर्ण


/**
 * onenand_memory_bbt - [GENERIC] create a memory based bad block table
 * @mtd:		MTD device काष्ठाure
 * @bd:		descriptor क्रम the good/bad block search pattern
 *
 * The function creates a memory based bbt by scanning the device
 * क्रम manufacturer / software marked good / bad blocks
 */
अटल अंतरभूत पूर्णांक onenand_memory_bbt (काष्ठा mtd_info *mtd, काष्ठा nand_bbt_descr *bd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;

	वापस create_bbt(mtd, this->page_buf, bd, -1);
पूर्ण

/**
 * onenand_isbad_bbt - [Oneन_अंकD Interface] Check अगर a block is bad
 * @mtd:		MTD device काष्ठाure
 * @offs:		offset in the device
 * @allowbbt:	allow access to bad block table region
 */
अटल पूर्णांक onenand_isbad_bbt(काष्ठा mtd_info *mtd, loff_t offs, पूर्णांक allowbbt)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	काष्ठा bbm_info *bbm = this->bbm;
	पूर्णांक block;
	uपूर्णांक8_t res;

	/* Get block number * 2 */
	block = (पूर्णांक) (onenand_block(this, offs) << 1);
	res = (bbm->bbt[block >> 3] >> (block & 0x06)) & 0x03;

	pr_debug("onenand_isbad_bbt: bbt info for offs 0x%08x: (block %d) 0x%02x\n",
		(अचिन्हित पूर्णांक) offs, block >> 1, res);

	चयन ((पूर्णांक) res) अणु
	हाल 0x00:	वापस 0;
	हाल 0x01:	वापस 1;
	हाल 0x02:	वापस allowbbt ? 0 : 1;
	पूर्ण

	वापस 1;
पूर्ण

/**
 * onenand_scan_bbt - [Oneन_अंकD Interface] scan, find, पढ़ो and maybe create bad block table(s)
 * @mtd:		MTD device काष्ठाure
 * @bd:		descriptor क्रम the good/bad block search pattern
 *
 * The function checks, अगर a bad block table(s) is/are alपढ़ोy
 * available. If not it scans the device क्रम manufacturer
 * marked good / bad blocks and ग_लिखोs the bad block table(s) to
 * the selected place.
 *
 * The bad block table memory is allocated here. It is मुक्तd
 * by the onenand_release function.
 *
 */
अटल पूर्णांक onenand_scan_bbt(काष्ठा mtd_info *mtd, काष्ठा nand_bbt_descr *bd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	काष्ठा bbm_info *bbm = this->bbm;
	पूर्णांक len, ret = 0;

	len = this->chipsize >> (this->erase_shअगरt + 2);
	/* Allocate memory (2bit per block) and clear the memory bad block table */
	bbm->bbt = kzalloc(len, GFP_KERNEL);
	अगर (!bbm->bbt)
		वापस -ENOMEM;

	/* Set erase shअगरt */
	bbm->bbt_erase_shअगरt = this->erase_shअगरt;

	अगर (!bbm->isbad_bbt)
		bbm->isbad_bbt = onenand_isbad_bbt;

	/* Scan the device to build a memory based bad block table */
	अगर ((ret = onenand_memory_bbt(mtd, bd))) अणु
		prपूर्णांकk(KERN_ERR "onenand_scan_bbt: Can't scan flash and build the RAM-based BBT\n");
		kमुक्त(bbm->bbt);
		bbm->bbt = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Define some generic bad / good block scan pattern which are used
 * जबतक scanning a device क्रम factory marked good / bad blocks.
 */
अटल uपूर्णांक8_t scan_ff_pattern[] = अणु 0xff, 0xff पूर्ण;

अटल काष्ठा nand_bbt_descr largepage_memorybased = अणु
	.options = 0,
	.offs = 0,
	.len = 2,
	.pattern = scan_ff_pattern,
पूर्ण;

/**
 * onenand_शेष_bbt - [Oneन_अंकD Interface] Select a शेष bad block table क्रम the device
 * @mtd:		MTD device काष्ठाure
 *
 * This function selects the शेष bad block table
 * support क्रम the device and calls the onenand_scan_bbt function
 */
पूर्णांक onenand_शेष_bbt(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	काष्ठा bbm_info *bbm;

	this->bbm = kzalloc(माप(काष्ठा bbm_info), GFP_KERNEL);
	अगर (!this->bbm)
		वापस -ENOMEM;

	bbm = this->bbm;

	/* 1KB page has same configuration as 2KB page */
	अगर (!bbm->badblock_pattern)
		bbm->badblock_pattern = &largepage_memorybased;

	वापस onenand_scan_bbt(mtd, bbm->badblock_pattern);
पूर्ण
