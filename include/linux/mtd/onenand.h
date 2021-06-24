<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/include/linux/mtd/onenand.h
 *
 *  Copyright तऊ 2005-2009 Samsung Electronics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 */

#अगर_अघोषित __LINUX_MTD_ONEन_अंकD_H
#घोषणा __LINUX_MTD_ONEन_अंकD_H

#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/mtd/flashchip.h>
#समावेश <linux/mtd/onenand_regs.h>
#समावेश <linux/mtd/bbm.h>

#घोषणा MAX_DIES		2
#घोषणा MAX_BUFFERRAM		2

/* Scan and identअगरy a Oneन_अंकD device */
बाह्य पूर्णांक onenand_scan(काष्ठा mtd_info *mtd, पूर्णांक max_chips);
/* Free resources held by the Oneन_अंकD device */
बाह्य व्योम onenand_release(काष्ठा mtd_info *mtd);

/**
 * काष्ठा onenand_bufferram - Oneन_अंकD BufferRAM Data
 * @blockpage:		block & page address in BufferRAM
 */
काष्ठा onenand_bufferram अणु
	पूर्णांक	blockpage;
पूर्ण;

/**
 * काष्ठा onenand_chip - Oneन_अंकD Private Flash Chip Data
 * @base:		[BOARDSPECIFIC] address to access Oneन_अंकD
 * @dies:		[INTERN][FLEX-ONEन_अंकD] number of dies on chip
 * @boundary:		[INTERN][FLEX-ONEन_अंकD] Boundary of the dies
 * @diesize:		[INTERN][FLEX-ONEन_अंकD] Size of the dies
 * @chipsize:		[INTERN] the size of one chip क्रम multichip arrays
 *			FIXME For Flex-Oneन_अंकD, chipsize holds maximum possible
 *			device size ie when all blocks are considered MLC
 * @device_id:		[INTERN] device ID
 * @density_mask:	chip density, used क्रम DDP devices
 * @verstion_id:	[INTERN] version ID
 * @options:		[BOARDSPECIFIC] various chip options. They can
 *			partly be set to inक्रमm onenand_scan about
 * @erase_shअगरt:	[INTERN] number of address bits in a block
 * @page_shअगरt:		[INTERN] number of address bits in a page
 * @page_mask:		[INTERN] a page per block mask
 * @ग_लिखोsize:		[INTERN] a real page size
 * @bufferram_index:	[INTERN] BufferRAM index
 * @bufferram:		[INTERN] BufferRAM info
 * @पढ़ोw:		[REPLACEABLE] hardware specअगरic function क्रम पढ़ो लघु
 * @ग_लिखोw:		[REPLACEABLE] hardware specअगरic function क्रम ग_लिखो लघु
 * @command:		[REPLACEABLE] hardware specअगरic function क्रम writing
 *			commands to the chip
 * @रुको:		[REPLACEABLE] hardware specअगरic function क्रम रुको on पढ़ोy
 * @bbt_रुको:		[REPLACEABLE] hardware specअगरic function क्रम bbt रुको on पढ़ोy
 * @unlock_all:		[REPLACEABLE] hardware specअगरic function क्रम unlock all
 * @पढ़ो_bufferram:	[REPLACEABLE] hardware specअगरic function क्रम BufferRAM Area
 * @ग_लिखो_bufferram:	[REPLACEABLE] hardware specअगरic function क्रम BufferRAM Area
 * @पढ़ो_word:		[REPLACEABLE] hardware specअगरic function क्रम पढ़ो
 *			रेजिस्टर of Oneन_अंकD
 * @ग_लिखो_word:		[REPLACEABLE] hardware specअगरic function क्रम ग_लिखो
 *			रेजिस्टर of Oneन_अंकD
 * @mmcontrol:		sync burst पढ़ो function
 * @chip_probe:		[REPLACEABLE] hardware specअगरic function क्रम chip probe
 * @block_markbad:	function to mark a block as bad
 * @scan_bbt:		[REPLACEALBE] hardware specअगरic function क्रम scanning
 *			Bad block Table
 * @chip_lock:		[INTERN] spinlock used to protect access to this
 *			काष्ठाure and the chip
 * @wq:			[INTERN] रुको queue to sleep on अगर a Oneन_अंकD
 *			operation is in progress
 * @state:		[INTERN] the current state of the Oneन_अंकD device
 * @page_buf:		[INTERN] page मुख्य data buffer
 * @oob_buf:		[INTERN] page oob data buffer
 * @subpagesize:	[INTERN] holds the subpagesize
 * @bbm:		[REPLACEABLE] poपूर्णांकer to Bad Block Management
 * @priv:		[OPTIONAL] poपूर्णांकer to निजी chip date
 */
काष्ठा onenand_chip अणु
	व्योम __iomem		*base;
	अचिन्हित		dies;
	अचिन्हित		boundary[MAX_DIES];
	loff_t			diesize[MAX_DIES];
	अचिन्हित पूर्णांक		chipsize;
	अचिन्हित पूर्णांक		device_id;
	अचिन्हित पूर्णांक		version_id;
	अचिन्हित पूर्णांक		technology;
	अचिन्हित पूर्णांक		density_mask;
	अचिन्हित पूर्णांक		options;
	अचिन्हित पूर्णांक		badblockpos;

	अचिन्हित पूर्णांक		erase_shअगरt;
	अचिन्हित पूर्णांक		page_shअगरt;
	अचिन्हित पूर्णांक		page_mask;
	अचिन्हित पूर्णांक		ग_लिखोsize;

	अचिन्हित पूर्णांक		bufferram_index;
	काष्ठा onenand_bufferram	bufferram[MAX_BUFFERRAM];

	पूर्णांक (*command)(काष्ठा mtd_info *mtd, पूर्णांक cmd, loff_t address, माप_प्रकार len);
	पूर्णांक (*रुको)(काष्ठा mtd_info *mtd, पूर्णांक state);
	पूर्णांक (*bbt_रुको)(काष्ठा mtd_info *mtd, पूर्णांक state);
	व्योम (*unlock_all)(काष्ठा mtd_info *mtd);
	पूर्णांक (*पढ़ो_bufferram)(काष्ठा mtd_info *mtd, पूर्णांक area,
			अचिन्हित अक्षर *buffer, पूर्णांक offset, माप_प्रकार count);
	पूर्णांक (*ग_लिखो_bufferram)(काष्ठा mtd_info *mtd, पूर्णांक area,
			स्थिर अचिन्हित अक्षर *buffer, पूर्णांक offset, माप_प्रकार count);
	अचिन्हित लघु (*पढ़ो_word)(व्योम __iomem *addr);
	व्योम (*ग_लिखो_word)(अचिन्हित लघु value, व्योम __iomem *addr);
	व्योम (*mmcontrol)(काष्ठा mtd_info *mtd, पूर्णांक sync_पढ़ो);
	पूर्णांक (*chip_probe)(काष्ठा mtd_info *mtd);
	पूर्णांक (*block_markbad)(काष्ठा mtd_info *mtd, loff_t ofs);
	पूर्णांक (*scan_bbt)(काष्ठा mtd_info *mtd);
	पूर्णांक (*enable)(काष्ठा mtd_info *mtd);
	पूर्णांक (*disable)(काष्ठा mtd_info *mtd);

	काष्ठा completion	complete;
	पूर्णांक			irq;

	spinlock_t		chip_lock;
	रुको_queue_head_t	wq;
	flstate_t		state;
	अचिन्हित अक्षर		*page_buf;
	अचिन्हित अक्षर		*oob_buf;
#अगर_घोषित CONFIG_MTD_ONEन_अंकD_VERIFY_WRITE
	अचिन्हित अक्षर		*verअगरy_buf;
#पूर्ण_अगर

	पूर्णांक			subpagesize;

	व्योम			*bbm;

	व्योम			*priv;

	/*
	 * Shows that the current operation is composed
	 * of sequence of commands. For example, cache program.
	 * Such command status OnGo bit is checked at the end of
	 * sequence.
	 */
	अचिन्हित पूर्णांक		ongoing;
पूर्ण;

/*
 * Helper macros
 */
#घोषणा ONEन_अंकD_PAGES_PER_BLOCK        (1<<6)

#घोषणा ONEन_अंकD_CURRENT_BUFFERRAM(this)		(this->bufferram_index)
#घोषणा ONEन_अंकD_NEXT_BUFFERRAM(this)		(this->bufferram_index ^ 1)
#घोषणा ONEन_अंकD_SET_NEXT_BUFFERRAM(this)	(this->bufferram_index ^= 1)
#घोषणा ONEन_अंकD_SET_PREV_BUFFERRAM(this)	(this->bufferram_index ^= 1)
#घोषणा ONEन_अंकD_SET_BUFFERRAM0(this)		(this->bufferram_index = 0)
#घोषणा ONEन_अंकD_SET_BUFFERRAM1(this)		(this->bufferram_index = 1)

#घोषणा FLEXONEन_अंकD(this)						\
	(this->device_id & DEVICE_IS_FLEXONEन_अंकD)
#घोषणा ONEन_अंकD_GET_SYS_CFG1(this)					\
	(this->पढ़ो_word(this->base + ONEन_अंकD_REG_SYS_CFG1))
#घोषणा ONEन_अंकD_SET_SYS_CFG1(v, this)					\
	(this->ग_लिखो_word(v, this->base + ONEन_अंकD_REG_SYS_CFG1))

#घोषणा ONEन_अंकD_IS_DDP(this)						\
	(this->device_id & ONEन_अंकD_DEVICE_IS_DDP)

#घोषणा ONEन_अंकD_IS_MLC(this)						\
	(this->technology & ONEन_अंकD_TECHNOLOGY_IS_MLC)

#अगर_घोषित CONFIG_MTD_ONEन_अंकD_2X_PROGRAM
#घोषणा ONEन_अंकD_IS_2PLANE(this)						\
	(this->options & ONEन_अंकD_HAS_2PLANE)
#अन्यथा
#घोषणा ONEन_अंकD_IS_2PLANE(this)			(0)
#पूर्ण_अगर

#घोषणा ONEन_अंकD_IS_CACHE_PROGRAM(this)					\
	(this->options & ONEन_अंकD_HAS_CACHE_PROGRAM)

#घोषणा ONEन_अंकD_IS_NOP_1(this)						\
	(this->options & ONEन_अंकD_HAS_NOP_1)

/* Check byte access in Oneन_अंकD */
#घोषणा ONEन_अंकD_CHECK_BYTE_ACCESS(addr)		(addr & 0x1)

#घोषणा ONEन_अंकD_BADBLOCK_POS		0

/*
 * Options bits
 */
#घोषणा ONEन_अंकD_HAS_CONT_LOCK		(0x0001)
#घोषणा ONEन_अंकD_HAS_UNLOCK_ALL		(0x0002)
#घोषणा ONEन_अंकD_HAS_2PLANE		(0x0004)
#घोषणा ONEन_अंकD_HAS_4KB_PAGE		(0x0008)
#घोषणा ONEन_अंकD_HAS_CACHE_PROGRAM	(0x0010)
#घोषणा ONEन_अंकD_HAS_NOP_1		(0x0020)
#घोषणा ONEन_अंकD_SKIP_UNLOCK_CHECK	(0x0100)
#घोषणा ONEन_अंकD_PAGEBUF_ALLOC		(0x1000)
#घोषणा ONEन_अंकD_OOBBUF_ALLOC		(0x2000)
#घोषणा ONEन_अंकD_SKIP_INITIAL_UNLOCKING	(0x4000)

#घोषणा ONEन_अंकD_IS_4KB_PAGE(this)					\
	(this->options & ONEन_अंकD_HAS_4KB_PAGE)

/*
 * Oneन_अंकD Flash Manufacturer ID Codes
 */
#घोषणा ONEन_अंकD_MFR_SAMSUNG	0xec
#घोषणा ONEन_अंकD_MFR_NUMONYX	0x20

/**
 * काष्ठा onenand_manufacturers - न_अंकD Flash Manufacturer ID Structure
 * @name:	Manufacturer name
 * @id:		manufacturer ID code of device.
*/
काष्ठा onenand_manufacturers अणु
        पूर्णांक id;
        अक्षर *name;
पूर्ण;

पूर्णांक onenand_bbt_पढ़ो_oob(काष्ठा mtd_info *mtd, loff_t from,
			 काष्ठा mtd_oob_ops *ops);
अचिन्हित onenand_block(काष्ठा onenand_chip *this, loff_t addr);
loff_t onenand_addr(काष्ठा onenand_chip *this, पूर्णांक block);
पूर्णांक flexonenand_region(काष्ठा mtd_info *mtd, loff_t addr);

काष्ठा mtd_partition;

काष्ठा onenand_platक्रमm_data अणु
	व्योम		(*mmcontrol)(काष्ठा mtd_info *mtd, पूर्णांक sync_पढ़ो);
	पूर्णांक		(*पढ़ो_bufferram)(काष्ठा mtd_info *mtd, पूर्णांक area,
			अचिन्हित अक्षर *buffer, पूर्णांक offset, माप_प्रकार count);
	काष्ठा mtd_partition *parts;
	अचिन्हित पूर्णांक	nr_parts;
पूर्ण;

#पूर्ण_अगर	/* __LINUX_MTD_ONEन_अंकD_H */
