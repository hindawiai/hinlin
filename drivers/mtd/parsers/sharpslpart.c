<शैली गुरु>
/*
 * sharpslpart.c - MTD partition parser क्रम न_अंकD flash using the SHARP FTL
 * क्रम logical addressing, as used on the PXA models of the SHARP SL Series.
 *
 * Copyright (C) 2017 Andrea Adami <andrea.adami@gmail.com>
 *
 * Based on SHARP GPL 2.4 sources:
 *   http://support.ezaurus.com/developer/source/source_dl.asp
 *     drivers/mtd/nand/sharp_sl_logical.c
 *     linux/include/यंत्र-arm/sharp_nand_logical.h
 *
 * Copyright (C) 2002 SHARP
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/sizes.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>

/* oob काष्ठाure */
#घोषणा न_अंकD_NOOB_LOGADDR_00		8
#घोषणा न_अंकD_NOOB_LOGADDR_01		9
#घोषणा न_अंकD_NOOB_LOGADDR_10		10
#घोषणा न_अंकD_NOOB_LOGADDR_11		11
#घोषणा न_अंकD_NOOB_LOGADDR_20		12
#घोषणा न_अंकD_NOOB_LOGADDR_21		13

#घोषणा BLOCK_IS_RESERVED		0xffff
#घोषणा BLOCK_UNMASK_COMPLEMENT		1

/* factory शेषs */
#घोषणा SHARPSL_न_अंकD_PARTS		3
#घोषणा SHARPSL_FTL_PART_SIZE		(7 * SZ_1M)
#घोषणा SHARPSL_PARTINFO1_LADDR		0x00060000
#घोषणा SHARPSL_PARTINFO2_LADDR		0x00064000

#घोषणा BOOT_MAGIC			0x424f4f54
#घोषणा FSRO_MAGIC			0x4653524f
#घोषणा FSRW_MAGIC			0x46535257

/**
 * काष्ठा sharpsl_ftl - Sharp FTL Logical Table
 * @logmax:		number of logical blocks
 * @log2phy:		the logical-to-physical table
 *
 * Structure containing the logical-to-physical translation table
 * used by the SHARP SL FTL.
 */
काष्ठा sharpsl_ftl अणु
	अचिन्हित पूर्णांक logmax;
	अचिन्हित पूर्णांक *log2phy;
पूर्ण;

/* verअगरy that the OOB bytes 8 to 15 are मुक्त and available क्रम the FTL */
अटल पूर्णांक sharpsl_nand_check_ooblayout(काष्ठा mtd_info *mtd)
अणु
	u8 मुक्तbytes = 0;
	पूर्णांक section = 0;

	जबतक (true) अणु
		काष्ठा mtd_oob_region oobमुक्त = अणु पूर्ण;
		पूर्णांक ret, i;

		ret = mtd_ooblayout_मुक्त(mtd, section++, &oobमुक्त);
		अगर (ret)
			अवरोध;

		अगर (!oobमुक्त.length || oobमुक्त.offset > 15 ||
		    (oobमुक्त.offset + oobमुक्त.length) < 8)
			जारी;

		i = oobमुक्त.offset >= 8 ? oobमुक्त.offset : 8;
		क्रम (; i < oobमुक्त.offset + oobमुक्त.length && i < 16; i++)
			मुक्तbytes |= BIT(i - 8);

		अगर (मुक्तbytes == 0xff)
			वापस 0;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक sharpsl_nand_पढ़ो_oob(काष्ठा mtd_info *mtd, loff_t offs, u8 *buf)
अणु
	काष्ठा mtd_oob_ops ops = अणु पूर्ण;
	पूर्णांक ret;

	ops.mode = MTD_OPS_PLACE_OOB;
	ops.ooblen = mtd->oobsize;
	ops.oobbuf = buf;

	ret = mtd_पढ़ो_oob(mtd, offs, &ops);
	अगर (ret != 0 || mtd->oobsize != ops.oobretlen)
		वापस -1;

	वापस 0;
पूर्ण

/*
 * The logical block number asचिन्हित to a physical block is stored in the OOB
 * of the first page, in 3 16-bit copies with the following layout:
 *
 * 01234567 89abcdef
 * -------- --------
 * ECC BB   xyxyxy
 *
 * When पढ़ोing we check that the first two copies agree.
 * In हाल of error, matching is tried using the following pairs.
 * Reserved values 0xffff mean the block is kept क्रम wear leveling.
 *
 * 01234567 89abcdef
 * -------- --------
 * ECC BB   xyxy    oob[8]==oob[10] && oob[9]==oob[11]   -> byte0=8   byte1=9
 * ECC BB     xyxy  oob[10]==oob[12] && oob[11]==oob[13] -> byte0=10  byte1=11
 * ECC BB   xy  xy  oob[12]==oob[8] && oob[13]==oob[9]   -> byte0=12  byte1=13
 */
अटल पूर्णांक sharpsl_nand_get_logical_num(u8 *oob)
अणु
	u16 us;
	पूर्णांक good0, good1;

	अगर (oob[न_अंकD_NOOB_LOGADDR_00] == oob[न_अंकD_NOOB_LOGADDR_10] &&
	    oob[न_अंकD_NOOB_LOGADDR_01] == oob[न_अंकD_NOOB_LOGADDR_11]) अणु
		good0 = न_अंकD_NOOB_LOGADDR_00;
		good1 = न_अंकD_NOOB_LOGADDR_01;
	पूर्ण अन्यथा अगर (oob[न_अंकD_NOOB_LOGADDR_10] == oob[न_अंकD_NOOB_LOGADDR_20] &&
		   oob[न_अंकD_NOOB_LOGADDR_11] == oob[न_अंकD_NOOB_LOGADDR_21]) अणु
		good0 = न_अंकD_NOOB_LOGADDR_10;
		good1 = न_अंकD_NOOB_LOGADDR_11;
	पूर्ण अन्यथा अगर (oob[न_अंकD_NOOB_LOGADDR_20] == oob[न_अंकD_NOOB_LOGADDR_00] &&
		   oob[न_अंकD_NOOB_LOGADDR_21] == oob[न_अंकD_NOOB_LOGADDR_01]) अणु
		good0 = न_अंकD_NOOB_LOGADDR_20;
		good1 = न_अंकD_NOOB_LOGADDR_21;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	us = oob[good0] | oob[good1] << 8;

	/* parity check */
	अगर (hweight16(us) & BLOCK_UNMASK_COMPLEMENT)
		वापस -EINVAL;

	/* reserved */
	अगर (us == BLOCK_IS_RESERVED)
		वापस BLOCK_IS_RESERVED;

	वापस (us >> 1) & GENMASK(9, 0);
पूर्ण

अटल पूर्णांक sharpsl_nand_init_ftl(काष्ठा mtd_info *mtd, काष्ठा sharpsl_ftl *ftl)
अणु
	अचिन्हित पूर्णांक block_num, phymax;
	पूर्णांक i, ret, log_num;
	loff_t block_adr;
	u8 *oob;

	oob = kzalloc(mtd->oobsize, GFP_KERNEL);
	अगर (!oob)
		वापस -ENOMEM;

	phymax = mtd_भाग_by_eb(SHARPSL_FTL_PART_SIZE, mtd);

	/* FTL reserves 5% of the blocks + 1 spare  */
	ftl->logmax = ((phymax * 95) / 100) - 1;

	ftl->log2phy = kदो_स्मृति_array(ftl->logmax, माप(*ftl->log2phy),
				     GFP_KERNEL);
	अगर (!ftl->log2phy) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण

	/* initialize ftl->log2phy */
	क्रम (i = 0; i < ftl->logmax; i++)
		ftl->log2phy[i] = अच_पूर्णांक_उच्च;

	/* create physical-logical table */
	क्रम (block_num = 0; block_num < phymax; block_num++) अणु
		block_adr = (loff_t)block_num * mtd->erasesize;

		अगर (mtd_block_isbad(mtd, block_adr))
			जारी;

		अगर (sharpsl_nand_पढ़ो_oob(mtd, block_adr, oob))
			जारी;

		/* get logical block */
		log_num = sharpsl_nand_get_logical_num(oob);

		/* cut-off errors and skip the out-of-range values */
		अगर (log_num > 0 && log_num < ftl->logmax) अणु
			अगर (ftl->log2phy[log_num] == अच_पूर्णांक_उच्च)
				ftl->log2phy[log_num] = block_num;
		पूर्ण
	पूर्ण

	pr_info("Sharp SL FTL: %d blocks used (%d logical, %d reserved)\n",
		phymax, ftl->logmax, phymax - ftl->logmax);

	ret = 0;
निकास:
	kमुक्त(oob);
	वापस ret;
पूर्ण

अटल व्योम sharpsl_nand_cleanup_ftl(काष्ठा sharpsl_ftl *ftl)
अणु
	kमुक्त(ftl->log2phy);
पूर्ण

अटल पूर्णांक sharpsl_nand_पढ़ो_laddr(काष्ठा mtd_info *mtd,
				   loff_t from,
				   माप_प्रकार len,
				   व्योम *buf,
				   काष्ठा sharpsl_ftl *ftl)
अणु
	अचिन्हित पूर्णांक log_num, final_log_num;
	अचिन्हित पूर्णांक block_num;
	loff_t block_adr;
	loff_t block_ofs;
	माप_प्रकार retlen;
	पूर्णांक err;

	log_num = mtd_भाग_by_eb((u32)from, mtd);
	final_log_num = mtd_भाग_by_eb(((u32)from + len - 1), mtd);

	अगर (len <= 0 || log_num >= ftl->logmax || final_log_num > log_num)
		वापस -EINVAL;

	block_num = ftl->log2phy[log_num];
	block_adr = (loff_t)block_num * mtd->erasesize;
	block_ofs = mtd_mod_by_eb((u32)from, mtd);

	err = mtd_पढ़ो(mtd, block_adr + block_ofs, len, &retlen, buf);
	/* Ignore corrected ECC errors */
	अगर (mtd_is_bitflip(err))
		err = 0;

	अगर (!err && retlen != len)
		err = -EIO;

	अगर (err)
		pr_err("sharpslpart: error, read failed at %#llx\n",
		       block_adr + block_ofs);

	वापस err;
पूर्ण

/*
 * MTD Partition Parser
 *
 * Sample values पढ़ो from SL-C860
 *
 * # cat /proc/mtd
 * dev:    size   erasesize  name
 * mtd0: 006d0000 00020000 "Filesystem"
 * mtd1: 00700000 00004000 "smf"
 * mtd2: 03500000 00004000 "root"
 * mtd3: 04400000 00004000 "home"
 *
 * PARTITIONINFO1
 * 0x00060000: 00 00 00 00 00 00 70 00 42 4f 4f 54 00 00 00 00  ......p.BOOT....
 * 0x00060010: 00 00 70 00 00 00 c0 03 46 53 52 4f 00 00 00 00  ..p.....FSRO....
 * 0x00060020: 00 00 c0 03 00 00 00 04 46 53 52 57 00 00 00 00  ........FSRW....
 */
काष्ठा sharpsl_nand_partinfo अणु
	__le32 start;
	__le32 end;
	__be32 magic;
	u32 reserved;
पूर्ण;

अटल पूर्णांक sharpsl_nand_पढ़ो_partinfo(काष्ठा mtd_info *master,
				      loff_t from,
				      माप_प्रकार len,
				      काष्ठा sharpsl_nand_partinfo *buf,
				      काष्ठा sharpsl_ftl *ftl)
अणु
	पूर्णांक ret;

	ret = sharpsl_nand_पढ़ो_laddr(master, from, len, buf, ftl);
	अगर (ret)
		वापस ret;

	/* check क्रम magics */
	अगर (be32_to_cpu(buf[0].magic) != BOOT_MAGIC ||
	    be32_to_cpu(buf[1].magic) != FSRO_MAGIC ||
	    be32_to_cpu(buf[2].magic) != FSRW_MAGIC) अणु
		pr_err("sharpslpart: magic values mismatch\n");
		वापस -EINVAL;
	पूर्ण

	/* fixup क्रम hardcoded value 64 MiB (क्रम older models) */
	buf[2].end = cpu_to_le32(master->size);

	/* extra sanity check */
	अगर (le32_to_cpu(buf[0].end) <= le32_to_cpu(buf[0].start) ||
	    le32_to_cpu(buf[1].start) < le32_to_cpu(buf[0].end) ||
	    le32_to_cpu(buf[1].end) <= le32_to_cpu(buf[1].start) ||
	    le32_to_cpu(buf[2].start) < le32_to_cpu(buf[1].end) ||
	    le32_to_cpu(buf[2].end) <= le32_to_cpu(buf[2].start)) अणु
		pr_err("sharpslpart: partition sizes mismatch\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sharpsl_parse_mtd_partitions(काष्ठा mtd_info *master,
					स्थिर काष्ठा mtd_partition **pparts,
					काष्ठा mtd_part_parser_data *data)
अणु
	काष्ठा sharpsl_ftl ftl;
	काष्ठा sharpsl_nand_partinfo buf[SHARPSL_न_अंकD_PARTS];
	काष्ठा mtd_partition *sharpsl_nand_parts;
	पूर्णांक err;

	/* check that OOB bytes 8 to 15 used by the FTL are actually मुक्त */
	err = sharpsl_nand_check_ooblayout(master);
	अगर (err)
		वापस err;

	/* init logical mgmt (FTL) */
	err = sharpsl_nand_init_ftl(master, &ftl);
	अगर (err)
		वापस err;

	/* पढ़ो and validate first partition table */
	pr_info("sharpslpart: try reading first partition table\n");
	err = sharpsl_nand_पढ़ो_partinfo(master,
					 SHARPSL_PARTINFO1_LADDR,
					 माप(buf), buf, &ftl);
	अगर (err) अणु
		/* fallback: पढ़ो second partition table */
		pr_warn("sharpslpart: first partition table is invalid, retry using the second\n");
		err = sharpsl_nand_पढ़ो_partinfo(master,
						 SHARPSL_PARTINFO2_LADDR,
						 माप(buf), buf, &ftl);
	पूर्ण

	/* cleanup logical mgmt (FTL) */
	sharpsl_nand_cleanup_ftl(&ftl);

	अगर (err) अणु
		pr_err("sharpslpart: both partition tables are invalid\n");
		वापस err;
	पूर्ण

	sharpsl_nand_parts = kसुस्मृति(SHARPSL_न_अंकD_PARTS,
				     माप(*sharpsl_nand_parts),
				     GFP_KERNEL);
	अगर (!sharpsl_nand_parts)
		वापस -ENOMEM;

	/* original names */
	sharpsl_nand_parts[0].name = "smf";
	sharpsl_nand_parts[0].offset = le32_to_cpu(buf[0].start);
	sharpsl_nand_parts[0].size = le32_to_cpu(buf[0].end) -
				     le32_to_cpu(buf[0].start);

	sharpsl_nand_parts[1].name = "root";
	sharpsl_nand_parts[1].offset = le32_to_cpu(buf[1].start);
	sharpsl_nand_parts[1].size = le32_to_cpu(buf[1].end) -
				     le32_to_cpu(buf[1].start);

	sharpsl_nand_parts[2].name = "home";
	sharpsl_nand_parts[2].offset = le32_to_cpu(buf[2].start);
	sharpsl_nand_parts[2].size = le32_to_cpu(buf[2].end) -
				     le32_to_cpu(buf[2].start);

	*pparts = sharpsl_nand_parts;
	वापस SHARPSL_न_अंकD_PARTS;
पूर्ण

अटल काष्ठा mtd_part_parser sharpsl_mtd_parser = अणु
	.parse_fn = sharpsl_parse_mtd_partitions,
	.name = "sharpslpart",
पूर्ण;
module_mtd_part_parser(sharpsl_mtd_parser);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrea Adami <andrea.adami@gmail.com>");
MODULE_DESCRIPTION("MTD partitioning for NAND flash on Sharp SL Series");
