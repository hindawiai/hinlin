<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  न_अंकD family Bad Block Management (BBM) header file
 *    - Bad Block Table (BBT) implementation
 *
 *  Copyright तऊ 2005 Samsung Electronics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 *
 *  Copyright तऊ 2000-2005
 *  Thomas Gleixner <tglx@linuxtronix.de>
 */
#अगर_अघोषित __LINUX_MTD_BBM_H
#घोषणा __LINUX_MTD_BBM_H

/* The maximum number of न_अंकD chips in an array */
#घोषणा न_अंकD_MAX_CHIPS		8

/**
 * काष्ठा nand_bbt_descr - bad block table descriptor
 * @options:	options क्रम this descriptor
 * @pages:	the page(s) where we find the bbt, used with option BBT_ABSPAGE
 *		when bbt is searched, then we store the found bbts pages here.
 *		Its an array and supports up to 8 chips now
 * @offs:	offset of the pattern in the oob area of the page
 * @veroffs:	offset of the bbt version counter in the oob are of the page
 * @version:	version पढ़ो from the bbt page during scan
 * @len:	length of the pattern, अगर 0 no pattern check is perक्रमmed
 * @maxblocks:	maximum number of blocks to search क्रम a bbt. This number of
 *		blocks is reserved at the end of the device where the tables are
 *		written.
 * @reserved_block_code: अगर non-0, this pattern denotes a reserved (rather than
 *              bad) block in the stored bbt
 * @pattern:	pattern to identअगरy bad block table or factory marked good /
 *		bad blocks, can be शून्य, अगर len = 0
 *
 * Descriptor क्रम the bad block table marker and the descriptor क्रम the
 * pattern which identअगरies good and bad blocks. The assumption is made
 * that the pattern and the version count are always located in the oob area
 * of the first block.
 */
काष्ठा nand_bbt_descr अणु
	पूर्णांक options;
	पूर्णांक pages[न_अंकD_MAX_CHIPS];
	पूर्णांक offs;
	पूर्णांक veroffs;
	uपूर्णांक8_t version[न_अंकD_MAX_CHIPS];
	पूर्णांक len;
	पूर्णांक maxblocks;
	पूर्णांक reserved_block_code;
	uपूर्णांक8_t *pattern;
पूर्ण;

/* Options क्रम the bad block table descriptors */

/* The number of bits used per block in the bbt on the device */
#घोषणा न_अंकD_BBT_NRBITS_MSK	0x0000000F
#घोषणा न_अंकD_BBT_1BIT		0x00000001
#घोषणा न_अंकD_BBT_2BIT		0x00000002
#घोषणा न_अंकD_BBT_4BIT		0x00000004
#घोषणा न_अंकD_BBT_8BIT		0x00000008
/* The bad block table is in the last good block of the device */
#घोषणा न_अंकD_BBT_LASTBLOCK	0x00000010
/* The bbt is at the given page, अन्यथा we must scan क्रम the bbt */
#घोषणा न_अंकD_BBT_ABSPAGE	0x00000020
/* bbt is stored per chip on multichip devices */
#घोषणा न_अंकD_BBT_PERCHIP	0x00000080
/* bbt has a version counter at offset veroffs */
#घोषणा न_अंकD_BBT_VERSION	0x00000100
/* Create a bbt अगर none exists */
#घोषणा न_अंकD_BBT_CREATE		0x00000200
/*
 * Create an empty BBT with no venकरोr inक्रमmation. Venकरोr's inक्रमmation may be
 * unavailable, क्रम example, अगर the न_अंकD controller has a dअगरferent data and OOB
 * layout or अगर this inक्रमmation is alपढ़ोy purged. Must be used in conjunction
 * with न_अंकD_BBT_CREATE.
 */
#घोषणा न_अंकD_BBT_CREATE_EMPTY	0x00000400
/* Write bbt अगर neccecary */
#घोषणा न_अंकD_BBT_WRITE		0x00002000
/* Read and ग_लिखो back block contents when writing bbt */
#घोषणा न_अंकD_BBT_SAVECONTENT	0x00004000

/*
 * Use a flash based bad block table. By शेष, OOB identअगरier is saved in
 * OOB area. This option is passed to the शेष bad block table function.
 */
#घोषणा न_अंकD_BBT_USE_FLASH	0x00020000
/*
 * Do not store flash based bad block table marker in the OOB area; store it
 * in-band.
 */
#घोषणा न_अंकD_BBT_NO_OOB		0x00040000
/*
 * Do not ग_लिखो new bad block markers to OOB; useful, e.g., when ECC covers
 * entire spare area. Must be used with न_अंकD_BBT_USE_FLASH.
 */
#घोषणा न_अंकD_BBT_NO_OOB_BBM	0x00080000

/*
 * Flag set by nand_create_शेष_bbt_descr(), marking that the nand_bbt_descr
 * was allocated dynamicaly and must be मुक्तd in nand_cleanup(). Has no meaning
 * in nand_chip.bbt_options.
 */
#घोषणा न_अंकD_BBT_DYNAMICSTRUCT	0x80000000

/* The maximum number of blocks to scan क्रम a bbt */
#घोषणा न_अंकD_BBT_SCAN_MAXBLOCKS	4

/*
 * Bad block scanning errors
 */
#घोषणा ONEन_अंकD_BBT_READ_ERROR		1
#घोषणा ONEन_अंकD_BBT_READ_ECC_ERROR	2
#घोषणा ONEन_अंकD_BBT_READ_FATAL_ERROR	4

/**
 * काष्ठा bbm_info - [GENERIC] Bad Block Table data काष्ठाure
 * @bbt_erase_shअगरt:	[INTERN] number of address bits in a bbt entry
 * @options:		options क्रम this descriptor
 * @bbt:		[INTERN] bad block table poपूर्णांकer
 * @isbad_bbt:		function to determine अगर a block is bad
 * @badblock_pattern:	[REPLACEABLE] bad block scan pattern used क्रम
 *			initial bad block scan
 * @priv:		[OPTIONAL] poपूर्णांकer to निजी bbm date
 */
काष्ठा bbm_info अणु
	पूर्णांक bbt_erase_shअगरt;
	पूर्णांक options;

	uपूर्णांक8_t *bbt;

	पूर्णांक (*isbad_bbt)(काष्ठा mtd_info *mtd, loff_t ofs, पूर्णांक allowbbt);

	/* TODO Add more न_अंकD specअगरic fileds */
	काष्ठा nand_bbt_descr *badblock_pattern;

	व्योम *priv;
पूर्ण;

/* Oneन_अंकD BBT पूर्णांकerface */
बाह्य पूर्णांक onenand_शेष_bbt(काष्ठा mtd_info *mtd);

#पूर्ण_अगर	/* __LINUX_MTD_BBM_H */
