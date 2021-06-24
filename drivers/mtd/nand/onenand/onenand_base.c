<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright तऊ 2005-2009 Samsung Electronics
 *  Copyright तऊ 2007 Nokia Corporation
 *
 *  Kyungmin Park <kyungmin.park@samsung.com>
 *
 *  Credits:
 *	Adrian Hunter <ext-adrian.hunter@nokia.com>:
 *	स्वतः-placement support, पढ़ो-जबतक load support, various fixes
 *
 *	Vishak G <vishak.g at samsung.com>, Rohit Hagargundgi <h.rohit at samsung.com>
 *	Flex-Oneन_अंकD support
 *	Amul Kumar Saha <amul.saha at samsung.com>
 *	OTP support
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/onenand.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <यंत्र/पन.स>

/*
 * Multiblock erase अगर number of blocks to erase is 2 or more.
 * Maximum number of blocks क्रम simultaneous erase is 64.
 */
#घोषणा MB_ERASE_MIN_BLK_COUNT 2
#घोषणा MB_ERASE_MAX_BLK_COUNT 64

/* Default Flex-Oneन_अंकD boundary and lock respectively */
अटल पूर्णांक flex_bdry[MAX_DIES * 2] = अणु -1, 0, -1, 0 पूर्ण;

module_param_array(flex_bdry, पूर्णांक, शून्य, 0400);
MODULE_PARM_DESC(flex_bdry,	"SLC Boundary information for Flex-OneNAND"
				"Syntax:flex_bdry=DIE_BDRY,LOCK,..."
				"DIE_BDRY: SLC boundary of the die"
				"LOCK: Locking information for SLC boundary"
				"    : 0->Set boundary in unlocked status"
				"    : 1->Set boundary in locked status");

/* Default Oneन_अंकD/Flex-Oneन_अंकD OTP options*/
अटल पूर्णांक otp;

module_param(otp, पूर्णांक, 0400);
MODULE_PARM_DESC(otp,	"Corresponding behaviour of OneNAND in OTP"
			"Syntax : otp=LOCK_TYPE"
			"LOCK_TYPE : Keys issued, for specific OTP Lock type"
			"	   : 0 -> Default (No Blocks Locked)"
			"	   : 1 -> OTP Block lock"
			"	   : 2 -> 1st Block lock"
			"	   : 3 -> BOTH OTP Block and 1st Block lock");

/*
 * flexonenand_oob_128 - oob info क्रम Flex-Onenand with 4KB page
 * For now, we expose only 64 out of 80 ecc bytes
 */
अटल पूर्णांक flexonenand_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				     काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section > 7)
		वापस -दुस्फल;

	oobregion->offset = (section * 16) + 6;
	oobregion->length = 10;

	वापस 0;
पूर्ण

अटल पूर्णांक flexonenand_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				      काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section > 7)
		वापस -दुस्फल;

	oobregion->offset = (section * 16) + 2;
	oobregion->length = 4;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops flexonenand_ooblayout_ops = अणु
	.ecc = flexonenand_ooblayout_ecc,
	.मुक्त = flexonenand_ooblayout_मुक्त,
पूर्ण;

/*
 * onenand_oob_128 - oob info क्रम Oneन_अंकD with 4KB page
 *
 * Based on specअगरication:
 * 4Gb M-die Oneन_अंकD Flash (KFM4G16Q4M, KFN8G16Q4M). Rev. 1.3, Apr. 2010
 *
 */
अटल पूर्णांक onenand_ooblayout_128_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				     काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section > 7)
		वापस -दुस्फल;

	oobregion->offset = (section * 16) + 7;
	oobregion->length = 9;

	वापस 0;
पूर्ण

अटल पूर्णांक onenand_ooblayout_128_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				      काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section >= 8)
		वापस -दुस्फल;

	/*
	 * मुक्त bytes are using the spare area fields marked as
	 * "Managed by internal ECC logic for Logical Sector Number area"
	 */
	oobregion->offset = (section * 16) + 2;
	oobregion->length = 3;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops onenand_oob_128_ooblayout_ops = अणु
	.ecc = onenand_ooblayout_128_ecc,
	.मुक्त = onenand_ooblayout_128_मुक्त,
पूर्ण;

/*
 * onenand_oob_32_64 - oob info क्रम large (2KB) page
 */
अटल पूर्णांक onenand_ooblayout_32_64_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				       काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section > 3)
		वापस -दुस्फल;

	oobregion->offset = (section * 16) + 8;
	oobregion->length = 5;

	वापस 0;
पूर्ण

अटल पूर्णांक onenand_ooblayout_32_64_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
					काष्ठा mtd_oob_region *oobregion)
अणु
	पूर्णांक sections = (mtd->oobsize / 32) * 2;

	अगर (section >= sections)
		वापस -दुस्फल;

	अगर (section & 1) अणु
		oobregion->offset = ((section - 1) * 16) + 14;
		oobregion->length = 2;
	पूर्ण अन्यथा  अणु
		oobregion->offset = (section * 16) + 2;
		oobregion->length = 3;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops onenand_oob_32_64_ooblayout_ops = अणु
	.ecc = onenand_ooblayout_32_64_ecc,
	.मुक्त = onenand_ooblayout_32_64_मुक्त,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर ffअक्षरs[] = अणु
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 16 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 32 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 48 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 64 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 80 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 96 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 112 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 128 */
पूर्ण;

/**
 * onenand_पढ़ोw - [Oneन_अंकD Interface] Read Oneन_अंकD रेजिस्टर
 * @addr:		address to पढ़ो
 *
 * Read Oneन_अंकD रेजिस्टर
 */
अटल अचिन्हित लघु onenand_पढ़ोw(व्योम __iomem *addr)
अणु
	वापस पढ़ोw(addr);
पूर्ण

/**
 * onenand_ग_लिखोw - [Oneन_अंकD Interface] Write Oneन_अंकD रेजिस्टर with value
 * @value:		value to ग_लिखो
 * @addr:		address to ग_लिखो
 *
 * Write Oneन_अंकD रेजिस्टर with value
 */
अटल व्योम onenand_ग_लिखोw(अचिन्हित लघु value, व्योम __iomem *addr)
अणु
	ग_लिखोw(value, addr);
पूर्ण

/**
 * onenand_block_address - [DEFAULT] Get block address
 * @this:		onenand chip data काष्ठाure
 * @block:		the block
 * @वापस		translated block address अगर DDP, otherwise same
 *
 * Setup Start Address 1 Register (F100h)
 */
अटल पूर्णांक onenand_block_address(काष्ठा onenand_chip *this, पूर्णांक block)
अणु
	/* Device Flash Core select, न_अंकD Flash Block Address */
	अगर (block & this->density_mask)
		वापस ONEन_अंकD_DDP_CHIP1 | (block ^ this->density_mask);

	वापस block;
पूर्ण

/**
 * onenand_bufferram_address - [DEFAULT] Get bufferram address
 * @this:		onenand chip data काष्ठाure
 * @block:		the block
 * @वापस		set DBS value अगर DDP, otherwise 0
 *
 * Setup Start Address 2 Register (F101h) क्रम DDP
 */
अटल पूर्णांक onenand_bufferram_address(काष्ठा onenand_chip *this, पूर्णांक block)
अणु
	/* Device BufferRAM Select */
	अगर (block & this->density_mask)
		वापस ONEन_अंकD_DDP_CHIP1;

	वापस ONEन_अंकD_DDP_CHIP0;
पूर्ण

/**
 * onenand_page_address - [DEFAULT] Get page address
 * @page:		the page address
 * @sector:	the sector address
 * @वापस		combined page and sector address
 *
 * Setup Start Address 8 Register (F107h)
 */
अटल पूर्णांक onenand_page_address(पूर्णांक page, पूर्णांक sector)
अणु
	/* Flash Page Address, Flash Sector Address */
	पूर्णांक fpa, fsa;

	fpa = page & ONEन_अंकD_FPA_MASK;
	fsa = sector & ONEन_अंकD_FSA_MASK;

	वापस ((fpa << ONEन_अंकD_FPA_SHIFT) | fsa);
पूर्ण

/**
 * onenand_buffer_address - [DEFAULT] Get buffer address
 * @dataram1:	DataRAM index
 * @sectors:	the sector address
 * @count:		the number of sectors
 * Return:		the start buffer value
 *
 * Setup Start Buffer Register (F200h)
 */
अटल पूर्णांक onenand_buffer_address(पूर्णांक dataram1, पूर्णांक sectors, पूर्णांक count)
अणु
	पूर्णांक bsa, bsc;

	/* BufferRAM Sector Address */
	bsa = sectors & ONEन_अंकD_BSA_MASK;

	अगर (dataram1)
		bsa |= ONEन_अंकD_BSA_DATARAM1;	/* DataRAM1 */
	अन्यथा
		bsa |= ONEन_अंकD_BSA_DATARAM0;	/* DataRAM0 */

	/* BufferRAM Sector Count */
	bsc = count & ONEन_अंकD_BSC_MASK;

	वापस ((bsa << ONEन_अंकD_BSA_SHIFT) | bsc);
पूर्ण

/**
 * flexonenand_block- For given address वापस block number
 * @this:         - Oneन_अंकD device काष्ठाure
 * @addr:		- Address क्रम which block number is needed
 */
अटल अचिन्हित flexonenand_block(काष्ठा onenand_chip *this, loff_t addr)
अणु
	अचिन्हित boundary, blk, die = 0;

	अगर (ONEन_अंकD_IS_DDP(this) && addr >= this->diesize[0]) अणु
		die = 1;
		addr -= this->diesize[0];
	पूर्ण

	boundary = this->boundary[die];

	blk = addr >> (this->erase_shअगरt - 1);
	अगर (blk > boundary)
		blk = (blk + boundary + 1) >> 1;

	blk += die ? this->density_mask : 0;
	वापस blk;
पूर्ण

अंतरभूत अचिन्हित onenand_block(काष्ठा onenand_chip *this, loff_t addr)
अणु
	अगर (!FLEXONEन_अंकD(this))
		वापस addr >> this->erase_shअगरt;
	वापस flexonenand_block(this, addr);
पूर्ण

/**
 * flexonenand_addr - Return address of the block
 * @this:		Oneन_अंकD device काष्ठाure
 * @block:		Block number on Flex-Oneन_अंकD
 *
 * Return address of the block
 */
अटल loff_t flexonenand_addr(काष्ठा onenand_chip *this, पूर्णांक block)
अणु
	loff_t ofs = 0;
	पूर्णांक die = 0, boundary;

	अगर (ONEन_अंकD_IS_DDP(this) && block >= this->density_mask) अणु
		block -= this->density_mask;
		die = 1;
		ofs = this->diesize[0];
	पूर्ण

	boundary = this->boundary[die];
	ofs += (loff_t)block << (this->erase_shअगरt - 1);
	अगर (block > (boundary + 1))
		ofs += (loff_t)(block - boundary - 1) << (this->erase_shअगरt - 1);
	वापस ofs;
पूर्ण

loff_t onenand_addr(काष्ठा onenand_chip *this, पूर्णांक block)
अणु
	अगर (!FLEXONEन_अंकD(this))
		वापस (loff_t)block << this->erase_shअगरt;
	वापस flexonenand_addr(this, block);
पूर्ण
EXPORT_SYMBOL(onenand_addr);

/**
 * onenand_get_density - [DEFAULT] Get Oneन_अंकD density
 * @dev_id:	Oneन_अंकD device ID
 *
 * Get Oneन_अंकD density from device ID
 */
अटल अंतरभूत पूर्णांक onenand_get_density(पूर्णांक dev_id)
अणु
	पूर्णांक density = dev_id >> ONEन_अंकD_DEVICE_DENSITY_SHIFT;
	वापस (density & ONEन_अंकD_DEVICE_DENSITY_MASK);
पूर्ण

/**
 * flexonenand_region - [Flex-Oneन_अंकD] Return erase region of addr
 * @mtd:		MTD device काष्ठाure
 * @addr:		address whose erase region needs to be identअगरied
 */
पूर्णांक flexonenand_region(काष्ठा mtd_info *mtd, loff_t addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mtd->numeraseregions; i++)
		अगर (addr < mtd->eraseregions[i].offset)
			अवरोध;
	वापस i - 1;
पूर्ण
EXPORT_SYMBOL(flexonenand_region);

/**
 * onenand_command - [DEFAULT] Send command to Oneन_अंकD device
 * @mtd:		MTD device काष्ठाure
 * @cmd:		the command to be sent
 * @addr:		offset to पढ़ो from or ग_लिखो to
 * @len:		number of bytes to पढ़ो or ग_लिखो
 *
 * Send command to Oneन_अंकD device. This function is used क्रम middle/large page
 * devices (1KB/2KB Bytes per page)
 */
अटल पूर्णांक onenand_command(काष्ठा mtd_info *mtd, पूर्णांक cmd, loff_t addr, माप_प्रकार len)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक value, block, page;

	/* Address translation */
	चयन (cmd) अणु
	हाल ONEन_अंकD_CMD_UNLOCK:
	हाल ONEन_अंकD_CMD_LOCK:
	हाल ONEन_अंकD_CMD_LOCK_TIGHT:
	हाल ONEन_अंकD_CMD_UNLOCK_ALL:
		block = -1;
		page = -1;
		अवरोध;

	हाल FLEXONEन_अंकD_CMD_PI_ACCESS:
		/* addr contains die index */
		block = addr * this->density_mask;
		page = -1;
		अवरोध;

	हाल ONEन_अंकD_CMD_ERASE:
	हाल ONEन_अंकD_CMD_MULTIBLOCK_ERASE:
	हाल ONEन_अंकD_CMD_ERASE_VERIFY:
	हाल ONEन_अंकD_CMD_BUFFERRAM:
	हाल ONEन_अंकD_CMD_OTP_ACCESS:
		block = onenand_block(this, addr);
		page = -1;
		अवरोध;

	हाल FLEXONEन_अंकD_CMD_READ_PI:
		cmd = ONEन_अंकD_CMD_READ;
		block = addr * this->density_mask;
		page = 0;
		अवरोध;

	शेष:
		block = onenand_block(this, addr);
		अगर (FLEXONEन_अंकD(this))
			page = (पूर्णांक) (addr - onenand_addr(this, block))>>\
				this->page_shअगरt;
		अन्यथा
			page = (पूर्णांक) (addr >> this->page_shअगरt);
		अगर (ONEन_अंकD_IS_2PLANE(this)) अणु
			/* Make the even block number */
			block &= ~1;
			/* Is it the odd plane? */
			अगर (addr & this->ग_लिखोsize)
				block++;
			page >>= 1;
		पूर्ण
		page &= this->page_mask;
		अवरोध;
	पूर्ण

	/* NOTE: The setting order of the रेजिस्टरs is very important! */
	अगर (cmd == ONEन_अंकD_CMD_BUFFERRAM) अणु
		/* Select DataRAM क्रम DDP */
		value = onenand_bufferram_address(this, block);
		this->ग_लिखो_word(value, this->base + ONEन_अंकD_REG_START_ADDRESS2);

		अगर (ONEन_अंकD_IS_2PLANE(this) || ONEन_अंकD_IS_4KB_PAGE(this))
			/* It is always BufferRAM0 */
			ONEन_अंकD_SET_BUFFERRAM0(this);
		अन्यथा
			/* Switch to the next data buffer */
			ONEन_अंकD_SET_NEXT_BUFFERRAM(this);

		वापस 0;
	पूर्ण

	अगर (block != -1) अणु
		/* Write 'DFS, FBA' of Flash */
		value = onenand_block_address(this, block);
		this->ग_लिखो_word(value, this->base + ONEन_अंकD_REG_START_ADDRESS1);

		/* Select DataRAM क्रम DDP */
		value = onenand_bufferram_address(this, block);
		this->ग_लिखो_word(value, this->base + ONEन_अंकD_REG_START_ADDRESS2);
	पूर्ण

	अगर (page != -1) अणु
		/* Now we use page size operation */
		पूर्णांक sectors = 0, count = 0;
		पूर्णांक dataram;

		चयन (cmd) अणु
		हाल FLEXONEन_अंकD_CMD_RECOVER_LSB:
		हाल ONEन_अंकD_CMD_READ:
		हाल ONEन_अंकD_CMD_READOOB:
			अगर (ONEन_अंकD_IS_4KB_PAGE(this))
				/* It is always BufferRAM0 */
				dataram = ONEन_अंकD_SET_BUFFERRAM0(this);
			अन्यथा
				dataram = ONEन_अंकD_SET_NEXT_BUFFERRAM(this);
			अवरोध;

		शेष:
			अगर (ONEन_अंकD_IS_2PLANE(this) && cmd == ONEन_अंकD_CMD_PROG)
				cmd = ONEन_अंकD_CMD_2X_PROG;
			dataram = ONEन_अंकD_CURRENT_BUFFERRAM(this);
			अवरोध;
		पूर्ण

		/* Write 'FPA, FSA' of Flash */
		value = onenand_page_address(page, sectors);
		this->ग_लिखो_word(value, this->base + ONEन_अंकD_REG_START_ADDRESS8);

		/* Write 'BSA, BSC' of DataRAM */
		value = onenand_buffer_address(dataram, sectors, count);
		this->ग_लिखो_word(value, this->base + ONEन_अंकD_REG_START_BUFFER);
	पूर्ण

	/* Interrupt clear */
	this->ग_लिखो_word(ONEन_अंकD_INT_CLEAR, this->base + ONEन_अंकD_REG_INTERRUPT);

	/* Write command */
	this->ग_लिखो_word(cmd, this->base + ONEन_अंकD_REG_COMMAND);

	वापस 0;
पूर्ण

/**
 * onenand_पढ़ो_ecc - वापस ecc status
 * @this:		onenand chip काष्ठाure
 */
अटल अंतरभूत पूर्णांक onenand_पढ़ो_ecc(काष्ठा onenand_chip *this)
अणु
	पूर्णांक ecc, i, result = 0;

	अगर (!FLEXONEन_अंकD(this) && !ONEन_अंकD_IS_4KB_PAGE(this))
		वापस this->पढ़ो_word(this->base + ONEन_अंकD_REG_ECC_STATUS);

	क्रम (i = 0; i < 4; i++) अणु
		ecc = this->पढ़ो_word(this->base + ONEन_अंकD_REG_ECC_STATUS + i*2);
		अगर (likely(!ecc))
			जारी;
		अगर (ecc & FLEXONEन_अंकD_UNCORRECTABLE_ERROR)
			वापस ONEन_अंकD_ECC_2BIT_ALL;
		अन्यथा
			result = ONEन_अंकD_ECC_1BIT_ALL;
	पूर्ण

	वापस result;
पूर्ण

/**
 * onenand_रुको - [DEFAULT] रुको until the command is करोne
 * @mtd:		MTD device काष्ठाure
 * @state:		state to select the max. समयout value
 *
 * Wait क्रम command करोne. This applies to all Oneन_अंकD command
 * Read can take up to 30us, erase up to 2ms and program up to 350us
 * according to general Oneन_अंकD specs
 */
अटल पूर्णांक onenand_रुको(काष्ठा mtd_info *mtd, पूर्णांक state)
अणु
	काष्ठा onenand_chip * this = mtd->priv;
	अचिन्हित दीर्घ समयout;
	अचिन्हित पूर्णांक flags = ONEन_अंकD_INT_MASTER;
	अचिन्हित पूर्णांक पूर्णांकerrupt = 0;
	अचिन्हित पूर्णांक ctrl;

	/* The 20 msec is enough */
	समयout = jअगरfies + msecs_to_jअगरfies(20);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		पूर्णांकerrupt = this->पढ़ो_word(this->base + ONEन_अंकD_REG_INTERRUPT);

		अगर (पूर्णांकerrupt & flags)
			अवरोध;

		अगर (state != FL_READING && state != FL_PREPARING_ERASE)
			cond_resched();
	पूर्ण
	/* To get correct पूर्णांकerrupt status in समयout हाल */
	पूर्णांकerrupt = this->पढ़ो_word(this->base + ONEन_अंकD_REG_INTERRUPT);

	ctrl = this->पढ़ो_word(this->base + ONEन_अंकD_REG_CTRL_STATUS);

	/*
	 * In the Spec. it checks the controller status first
	 * However अगर you get the correct inक्रमmation in हाल of
	 * घातer off recovery (POR) test, it should पढ़ो ECC status first
	 */
	अगर (पूर्णांकerrupt & ONEन_अंकD_INT_READ) अणु
		पूर्णांक ecc = onenand_पढ़ो_ecc(this);
		अगर (ecc) अणु
			अगर (ecc & ONEन_अंकD_ECC_2BIT_ALL) अणु
				prपूर्णांकk(KERN_ERR "%s: ECC error = 0x%04x\n",
					__func__, ecc);
				mtd->ecc_stats.failed++;
				वापस -EBADMSG;
			पूर्ण अन्यथा अगर (ecc & ONEन_अंकD_ECC_1BIT_ALL) अणु
				prपूर्णांकk(KERN_DEBUG "%s: correctable ECC error = 0x%04x\n",
					__func__, ecc);
				mtd->ecc_stats.corrected++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (state == FL_READING) अणु
		prपूर्णांकk(KERN_ERR "%s: read timeout! ctrl=0x%04x intr=0x%04x\n",
			__func__, ctrl, पूर्णांकerrupt);
		वापस -EIO;
	पूर्ण

	अगर (state == FL_PREPARING_ERASE && !(पूर्णांकerrupt & ONEन_अंकD_INT_ERASE)) अणु
		prपूर्णांकk(KERN_ERR "%s: mb erase timeout! ctrl=0x%04x intr=0x%04x\n",
		       __func__, ctrl, पूर्णांकerrupt);
		वापस -EIO;
	पूर्ण

	अगर (!(पूर्णांकerrupt & ONEन_अंकD_INT_MASTER)) अणु
		prपूर्णांकk(KERN_ERR "%s: timeout! ctrl=0x%04x intr=0x%04x\n",
		       __func__, ctrl, पूर्णांकerrupt);
		वापस -EIO;
	पूर्ण

	/* If there's controller error, it's a real error */
	अगर (ctrl & ONEन_अंकD_CTRL_ERROR) अणु
		prपूर्णांकk(KERN_ERR "%s: controller error = 0x%04x\n",
			__func__, ctrl);
		अगर (ctrl & ONEन_अंकD_CTRL_LOCK)
			prपूर्णांकk(KERN_ERR "%s: it's locked error.\n", __func__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * onenand_पूर्णांकerrupt - [DEFAULT] onenand पूर्णांकerrupt handler
 * @irq:		onenand पूर्णांकerrupt number
 * @dev_id:	पूर्णांकerrupt data
 *
 * complete the work
 */
अटल irqवापस_t onenand_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा onenand_chip *this = data;

	/* To handle shared पूर्णांकerrupt */
	अगर (!this->complete.करोne)
		complete(&this->complete);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * onenand_पूर्णांकerrupt_रुको - [DEFAULT] रुको until the command is करोne
 * @mtd:		MTD device काष्ठाure
 * @state:		state to select the max. समयout value
 *
 * Wait क्रम command करोne.
 */
अटल पूर्णांक onenand_पूर्णांकerrupt_रुको(काष्ठा mtd_info *mtd, पूर्णांक state)
अणु
	काष्ठा onenand_chip *this = mtd->priv;

	रुको_क्रम_completion(&this->complete);

	वापस onenand_रुको(mtd, state);
पूर्ण

/*
 * onenand_try_पूर्णांकerrupt_रुको - [DEFAULT] try पूर्णांकerrupt रुको
 * @mtd:		MTD device काष्ठाure
 * @state:		state to select the max. समयout value
 *
 * Try पूर्णांकerrupt based रुको (It is used one-समय)
 */
अटल पूर्णांक onenand_try_पूर्णांकerrupt_रुको(काष्ठा mtd_info *mtd, पूर्णांक state)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	अचिन्हित दीर्घ reमुख्य, समयout;

	/* We use पूर्णांकerrupt रुको first */
	this->रुको = onenand_पूर्णांकerrupt_रुको;

	समयout = msecs_to_jअगरfies(100);
	reमुख्य = रुको_क्रम_completion_समयout(&this->complete, समयout);
	अगर (!reमुख्य) अणु
		prपूर्णांकk(KERN_INFO "OneNAND: There's no interrupt. "
				"We use the normal wait\n");

		/* Release the irq */
		मुक्त_irq(this->irq, this);

		this->रुको = onenand_रुको;
	पूर्ण

	वापस onenand_रुको(mtd, state);
पूर्ण

/*
 * onenand_setup_रुको - [Oneन_अंकD Interface] setup onenand रुको method
 * @mtd:		MTD device काष्ठाure
 *
 * There's two method to रुको onenand work
 * 1. polling - पढ़ो पूर्णांकerrupt status रेजिस्टर
 * 2. पूर्णांकerrupt - use the kernel पूर्णांकerrupt method
 */
अटल व्योम onenand_setup_रुको(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक syscfg;

	init_completion(&this->complete);

	अगर (this->irq <= 0) अणु
		this->रुको = onenand_रुको;
		वापस;
	पूर्ण

	अगर (request_irq(this->irq, &onenand_पूर्णांकerrupt,
				IRQF_SHARED, "onenand", this)) अणु
		/* If we can't get irq, use the normal रुको */
		this->रुको = onenand_रुको;
		वापस;
	पूर्ण

	/* Enable पूर्णांकerrupt */
	syscfg = this->पढ़ो_word(this->base + ONEन_अंकD_REG_SYS_CFG1);
	syscfg |= ONEन_अंकD_SYS_CFG1_IOBE;
	this->ग_लिखो_word(syscfg, this->base + ONEन_अंकD_REG_SYS_CFG1);

	this->रुको = onenand_try_पूर्णांकerrupt_रुको;
पूर्ण

/**
 * onenand_bufferram_offset - [DEFAULT] BufferRAM offset
 * @mtd:		MTD data काष्ठाure
 * @area:		BufferRAM area
 * @वापस		offset given area
 *
 * Return BufferRAM offset given area
 */
अटल अंतरभूत पूर्णांक onenand_bufferram_offset(काष्ठा mtd_info *mtd, पूर्णांक area)
अणु
	काष्ठा onenand_chip *this = mtd->priv;

	अगर (ONEन_अंकD_CURRENT_BUFFERRAM(this)) अणु
		/* Note: the 'this->writesize' is a real page size */
		अगर (area == ONEन_अंकD_DATARAM)
			वापस this->ग_लिखोsize;
		अगर (area == ONEन_अंकD_SPARERAM)
			वापस mtd->oobsize;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * onenand_पढ़ो_bufferram - [Oneन_अंकD Interface] Read the bufferram area
 * @mtd:		MTD data काष्ठाure
 * @area:		BufferRAM area
 * @buffer:	the databuffer to put/get data
 * @offset:	offset to पढ़ो from or ग_लिखो to
 * @count:		number of bytes to पढ़ो/ग_लिखो
 *
 * Read the BufferRAM area
 */
अटल पूर्णांक onenand_पढ़ो_bufferram(काष्ठा mtd_info *mtd, पूर्णांक area,
		अचिन्हित अक्षर *buffer, पूर्णांक offset, माप_प्रकार count)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	व्योम __iomem *bufferram;

	bufferram = this->base + area;

	bufferram += onenand_bufferram_offset(mtd, area);

	अगर (ONEन_अंकD_CHECK_BYTE_ACCESS(count)) अणु
		अचिन्हित लघु word;

		/* Align with word(16-bit) size */
		count--;

		/* Read word and save byte */
		word = this->पढ़ो_word(bufferram + offset + count);
		buffer[count] = (word & 0xff);
	पूर्ण

	स_नकल(buffer, bufferram + offset, count);

	वापस 0;
पूर्ण

/**
 * onenand_sync_पढ़ो_bufferram - [Oneन_अंकD Interface] Read the bufferram area with Sync. Burst mode
 * @mtd:		MTD data काष्ठाure
 * @area:		BufferRAM area
 * @buffer:	the databuffer to put/get data
 * @offset:	offset to पढ़ो from or ग_लिखो to
 * @count:		number of bytes to पढ़ो/ग_लिखो
 *
 * Read the BufferRAM area with Sync. Burst Mode
 */
अटल पूर्णांक onenand_sync_पढ़ो_bufferram(काष्ठा mtd_info *mtd, पूर्णांक area,
		अचिन्हित अक्षर *buffer, पूर्णांक offset, माप_प्रकार count)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	व्योम __iomem *bufferram;

	bufferram = this->base + area;

	bufferram += onenand_bufferram_offset(mtd, area);

	this->mmcontrol(mtd, ONEन_अंकD_SYS_CFG1_SYNC_READ);

	अगर (ONEन_अंकD_CHECK_BYTE_ACCESS(count)) अणु
		अचिन्हित लघु word;

		/* Align with word(16-bit) size */
		count--;

		/* Read word and save byte */
		word = this->पढ़ो_word(bufferram + offset + count);
		buffer[count] = (word & 0xff);
	पूर्ण

	स_नकल(buffer, bufferram + offset, count);

	this->mmcontrol(mtd, 0);

	वापस 0;
पूर्ण

/**
 * onenand_ग_लिखो_bufferram - [Oneन_अंकD Interface] Write the bufferram area
 * @mtd:		MTD data काष्ठाure
 * @area:		BufferRAM area
 * @buffer:	the databuffer to put/get data
 * @offset:	offset to पढ़ो from or ग_लिखो to
 * @count:		number of bytes to पढ़ो/ग_लिखो
 *
 * Write the BufferRAM area
 */
अटल पूर्णांक onenand_ग_लिखो_bufferram(काष्ठा mtd_info *mtd, पूर्णांक area,
		स्थिर अचिन्हित अक्षर *buffer, पूर्णांक offset, माप_प्रकार count)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	व्योम __iomem *bufferram;

	bufferram = this->base + area;

	bufferram += onenand_bufferram_offset(mtd, area);

	अगर (ONEन_अंकD_CHECK_BYTE_ACCESS(count)) अणु
		अचिन्हित लघु word;
		पूर्णांक byte_offset;

		/* Align with word(16-bit) size */
		count--;

		/* Calculate byte access offset */
		byte_offset = offset + count;

		/* Read word and save byte */
		word = this->पढ़ो_word(bufferram + byte_offset);
		word = (word & ~0xff) | buffer[count];
		this->ग_लिखो_word(word, bufferram + byte_offset);
	पूर्ण

	स_नकल(bufferram + offset, buffer, count);

	वापस 0;
पूर्ण

/**
 * onenand_get_2x_blockpage - [GENERIC] Get blockpage at 2x program mode
 * @mtd:		MTD data काष्ठाure
 * @addr:		address to check
 * @वापस		blockpage address
 *
 * Get blockpage address at 2x program mode
 */
अटल पूर्णांक onenand_get_2x_blockpage(काष्ठा mtd_info *mtd, loff_t addr)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक blockpage, block, page;

	/* Calculate the even block number */
	block = (पूर्णांक) (addr >> this->erase_shअगरt) & ~1;
	/* Is it the odd plane? */
	अगर (addr & this->ग_लिखोsize)
		block++;
	page = (पूर्णांक) (addr >> (this->page_shअगरt + 1)) & this->page_mask;
	blockpage = (block << 7) | page;

	वापस blockpage;
पूर्ण

/**
 * onenand_check_bufferram - [GENERIC] Check BufferRAM inक्रमmation
 * @mtd:		MTD data काष्ठाure
 * @addr:		address to check
 * @वापस		1 अगर there are valid data, otherwise 0
 *
 * Check bufferram अगर there is data we required
 */
अटल पूर्णांक onenand_check_bufferram(काष्ठा mtd_info *mtd, loff_t addr)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक blockpage, found = 0;
	अचिन्हित पूर्णांक i;

	अगर (ONEन_अंकD_IS_2PLANE(this))
		blockpage = onenand_get_2x_blockpage(mtd, addr);
	अन्यथा
		blockpage = (पूर्णांक) (addr >> this->page_shअगरt);

	/* Is there valid data? */
	i = ONEन_अंकD_CURRENT_BUFFERRAM(this);
	अगर (this->bufferram[i].blockpage == blockpage)
		found = 1;
	अन्यथा अणु
		/* Check another BufferRAM */
		i = ONEन_अंकD_NEXT_BUFFERRAM(this);
		अगर (this->bufferram[i].blockpage == blockpage) अणु
			ONEन_अंकD_SET_NEXT_BUFFERRAM(this);
			found = 1;
		पूर्ण
	पूर्ण

	अगर (found && ONEन_अंकD_IS_DDP(this)) अणु
		/* Select DataRAM क्रम DDP */
		पूर्णांक block = onenand_block(this, addr);
		पूर्णांक value = onenand_bufferram_address(this, block);
		this->ग_लिखो_word(value, this->base + ONEन_अंकD_REG_START_ADDRESS2);
	पूर्ण

	वापस found;
पूर्ण

/**
 * onenand_update_bufferram - [GENERIC] Update BufferRAM inक्रमmation
 * @mtd:		MTD data काष्ठाure
 * @addr:		address to update
 * @valid:		valid flag
 *
 * Update BufferRAM inक्रमmation
 */
अटल व्योम onenand_update_bufferram(काष्ठा mtd_info *mtd, loff_t addr,
		पूर्णांक valid)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक blockpage;
	अचिन्हित पूर्णांक i;

	अगर (ONEन_अंकD_IS_2PLANE(this))
		blockpage = onenand_get_2x_blockpage(mtd, addr);
	अन्यथा
		blockpage = (पूर्णांक) (addr >> this->page_shअगरt);

	/* Invalidate another BufferRAM */
	i = ONEन_अंकD_NEXT_BUFFERRAM(this);
	अगर (this->bufferram[i].blockpage == blockpage)
		this->bufferram[i].blockpage = -1;

	/* Update BufferRAM */
	i = ONEन_अंकD_CURRENT_BUFFERRAM(this);
	अगर (valid)
		this->bufferram[i].blockpage = blockpage;
	अन्यथा
		this->bufferram[i].blockpage = -1;
पूर्ण

/**
 * onenand_invalidate_bufferram - [GENERIC] Invalidate BufferRAM inक्रमmation
 * @mtd:		MTD data काष्ठाure
 * @addr:		start address to invalidate
 * @len:		length to invalidate
 *
 * Invalidate BufferRAM inक्रमmation
 */
अटल व्योम onenand_invalidate_bufferram(काष्ठा mtd_info *mtd, loff_t addr,
		अचिन्हित पूर्णांक len)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक i;
	loff_t end_addr = addr + len;

	/* Invalidate BufferRAM */
	क्रम (i = 0; i < MAX_BUFFERRAM; i++) अणु
		loff_t buf_addr = this->bufferram[i].blockpage << this->page_shअगरt;
		अगर (buf_addr >= addr && buf_addr < end_addr)
			this->bufferram[i].blockpage = -1;
	पूर्ण
पूर्ण

/**
 * onenand_get_device - [GENERIC] Get chip क्रम selected access
 * @mtd:		MTD device काष्ठाure
 * @new_state:	the state which is requested
 *
 * Get the device and lock it क्रम exclusive access
 */
अटल पूर्णांक onenand_get_device(काष्ठा mtd_info *mtd, पूर्णांक new_state)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	DECLARE_WAITQUEUE(रुको, current);

	/*
	 * Grab the lock and see अगर the device is available
	 */
	जबतक (1) अणु
		spin_lock(&this->chip_lock);
		अगर (this->state == FL_READY) अणु
			this->state = new_state;
			spin_unlock(&this->chip_lock);
			अगर (new_state != FL_PM_SUSPENDED && this->enable)
				this->enable(mtd);
			अवरोध;
		पूर्ण
		अगर (new_state == FL_PM_SUSPENDED) अणु
			spin_unlock(&this->chip_lock);
			वापस (this->state == FL_PM_SUSPENDED) ? 0 : -EAGAIN;
		पूर्ण
		set_current_state(TASK_UNINTERRUPTIBLE);
		add_रुको_queue(&this->wq, &रुको);
		spin_unlock(&this->chip_lock);
		schedule();
		हटाओ_रुको_queue(&this->wq, &रुको);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * onenand_release_device - [GENERIC] release chip
 * @mtd:		MTD device काष्ठाure
 *
 * Deselect, release chip lock and wake up anyone रुकोing on the device
 */
अटल व्योम onenand_release_device(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;

	अगर (this->state != FL_PM_SUSPENDED && this->disable)
		this->disable(mtd);
	/* Release the chip */
	spin_lock(&this->chip_lock);
	this->state = FL_READY;
	wake_up(&this->wq);
	spin_unlock(&this->chip_lock);
पूर्ण

/**
 * onenand_transfer_स्वतः_oob - [INTERN] oob स्वतः-placement transfer
 * @mtd:		MTD device काष्ठाure
 * @buf:		destination address
 * @column:	oob offset to पढ़ो from
 * @thislen:	oob length to पढ़ो
 */
अटल पूर्णांक onenand_transfer_स्वतः_oob(काष्ठा mtd_info *mtd, uपूर्णांक8_t *buf, पूर्णांक column,
				पूर्णांक thislen)
अणु
	काष्ठा onenand_chip *this = mtd->priv;

	this->पढ़ो_bufferram(mtd, ONEन_अंकD_SPARERAM, this->oob_buf, 0,
			     mtd->oobsize);
	वापस mtd_ooblayout_get_databytes(mtd, buf, this->oob_buf,
					   column, thislen);
पूर्ण

/**
 * onenand_recover_lsb - [Flex-Oneन_अंकD] Recover LSB page data
 * @mtd:		MTD device काष्ठाure
 * @addr:		address to recover
 * @status:	वापस value from onenand_रुको / onenand_bbt_रुको
 *
 * MLC न_अंकD Flash cell has paired pages - LSB page and MSB page. LSB page has
 * lower page address and MSB page has higher page address in paired pages.
 * If घातer off occurs during MSB page program, the paired LSB page data can
 * become corrupt. LSB page recovery पढ़ो is a way to पढ़ो LSB page though page
 * data are corrupted. When uncorrectable error occurs as a result of LSB page
 * पढ़ो after घातer up, issue LSB page recovery पढ़ो.
 */
अटल पूर्णांक onenand_recover_lsb(काष्ठा mtd_info *mtd, loff_t addr, पूर्णांक status)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक i;

	/* Recovery is only क्रम Flex-Oneन_अंकD */
	अगर (!FLEXONEन_अंकD(this))
		वापस status;

	/* check अगर we failed due to uncorrectable error */
	अगर (!mtd_is_eccerr(status) && status != ONEन_अंकD_BBT_READ_ECC_ERROR)
		वापस status;

	/* check अगर address lies in MLC region */
	i = flexonenand_region(mtd, addr);
	अगर (mtd->eraseregions[i].erasesize < (1 << this->erase_shअगरt))
		वापस status;

	/* We are attempting to reपढ़ो, so decrement stats.failed
	 * which was incremented by onenand_रुको due to पढ़ो failure
	 */
	prपूर्णांकk(KERN_INFO "%s: Attempting to recover from uncorrectable read\n",
		__func__);
	mtd->ecc_stats.failed--;

	/* Issue the LSB page recovery command */
	this->command(mtd, FLEXONEन_अंकD_CMD_RECOVER_LSB, addr, this->ग_लिखोsize);
	वापस this->रुको(mtd, FL_READING);
पूर्ण

/**
 * onenand_mlc_पढ़ो_ops_nolock - MLC Oneन_अंकD पढ़ो मुख्य and/or out-of-band
 * @mtd:		MTD device काष्ठाure
 * @from:		offset to पढ़ो from
 * @ops:		oob operation description काष्ठाure
 *
 * MLC Oneन_अंकD / Flex-Oneन_अंकD has 4KB page size and 4KB dataram.
 * So, पढ़ो-जबतक-load is not present.
 */
अटल पूर्णांक onenand_mlc_पढ़ो_ops_nolock(काष्ठा mtd_info *mtd, loff_t from,
				काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	काष्ठा mtd_ecc_stats stats;
	माप_प्रकार len = ops->len;
	माप_प्रकार ooblen = ops->ooblen;
	u_अक्षर *buf = ops->datbuf;
	u_अक्षर *oobbuf = ops->oobbuf;
	पूर्णांक पढ़ो = 0, column, thislen;
	पूर्णांक oobपढ़ो = 0, oobcolumn, thisooblen, oobsize;
	पूर्णांक ret = 0;
	पूर्णांक ग_लिखोsize = this->ग_लिखोsize;

	pr_debug("%s: from = 0x%08x, len = %i\n", __func__, (अचिन्हित पूर्णांक)from,
			(पूर्णांक)len);

	oobsize = mtd_oobavail(mtd, ops);
	oobcolumn = from & (mtd->oobsize - 1);

	/* Do not allow पढ़ोs past end of device */
	अगर (from + len > mtd->size) अणु
		prपूर्णांकk(KERN_ERR "%s: Attempt read beyond end of device\n",
			__func__);
		ops->retlen = 0;
		ops->oobretlen = 0;
		वापस -EINVAL;
	पूर्ण

	stats = mtd->ecc_stats;

	जबतक (पढ़ो < len) अणु
		cond_resched();

		thislen = min_t(पूर्णांक, ग_लिखोsize, len - पढ़ो);

		column = from & (ग_लिखोsize - 1);
		अगर (column + thislen > ग_लिखोsize)
			thislen = ग_लिखोsize - column;

		अगर (!onenand_check_bufferram(mtd, from)) अणु
			this->command(mtd, ONEन_अंकD_CMD_READ, from, ग_लिखोsize);

			ret = this->रुको(mtd, FL_READING);
			अगर (unlikely(ret))
				ret = onenand_recover_lsb(mtd, from, ret);
			onenand_update_bufferram(mtd, from, !ret);
			अगर (mtd_is_eccerr(ret))
				ret = 0;
			अगर (ret)
				अवरोध;
		पूर्ण

		this->पढ़ो_bufferram(mtd, ONEन_अंकD_DATARAM, buf, column, thislen);
		अगर (oobbuf) अणु
			thisooblen = oobsize - oobcolumn;
			thisooblen = min_t(पूर्णांक, thisooblen, ooblen - oobपढ़ो);

			अगर (ops->mode == MTD_OPS_AUTO_OOB)
				onenand_transfer_स्वतः_oob(mtd, oobbuf, oobcolumn, thisooblen);
			अन्यथा
				this->पढ़ो_bufferram(mtd, ONEन_अंकD_SPARERAM, oobbuf, oobcolumn, thisooblen);
			oobपढ़ो += thisooblen;
			oobbuf += thisooblen;
			oobcolumn = 0;
		पूर्ण

		पढ़ो += thislen;
		अगर (पढ़ो == len)
			अवरोध;

		from += thislen;
		buf += thislen;
	पूर्ण

	/*
	 * Return success, अगर no ECC failures, अन्यथा -EBADMSG
	 * fs driver will take care of that, because
	 * retlen == desired len and result == -EBADMSG
	 */
	ops->retlen = पढ़ो;
	ops->oobretlen = oobपढ़ो;

	अगर (ret)
		वापस ret;

	अगर (mtd->ecc_stats.failed - stats.failed)
		वापस -EBADMSG;

	/* वापस max bitflips per ecc step; ONEन_अंकDs correct 1 bit only */
	वापस mtd->ecc_stats.corrected != stats.corrected ? 1 : 0;
पूर्ण

/**
 * onenand_पढ़ो_ops_nolock - [Oneन_अंकD Interface] Oneन_अंकD पढ़ो मुख्य and/or out-of-band
 * @mtd:		MTD device काष्ठाure
 * @from:		offset to पढ़ो from
 * @ops:		oob operation description काष्ठाure
 *
 * Oneन_अंकD पढ़ो मुख्य and/or out-of-band data
 */
अटल पूर्णांक onenand_पढ़ो_ops_nolock(काष्ठा mtd_info *mtd, loff_t from,
				काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	काष्ठा mtd_ecc_stats stats;
	माप_प्रकार len = ops->len;
	माप_प्रकार ooblen = ops->ooblen;
	u_अक्षर *buf = ops->datbuf;
	u_अक्षर *oobbuf = ops->oobbuf;
	पूर्णांक पढ़ो = 0, column, thislen;
	पूर्णांक oobपढ़ो = 0, oobcolumn, thisooblen, oobsize;
	पूर्णांक ret = 0, boundary = 0;
	पूर्णांक ग_लिखोsize = this->ग_लिखोsize;

	pr_debug("%s: from = 0x%08x, len = %i\n", __func__, (अचिन्हित पूर्णांक)from,
			(पूर्णांक)len);

	oobsize = mtd_oobavail(mtd, ops);
	oobcolumn = from & (mtd->oobsize - 1);

	/* Do not allow पढ़ोs past end of device */
	अगर ((from + len) > mtd->size) अणु
		prपूर्णांकk(KERN_ERR "%s: Attempt read beyond end of device\n",
			__func__);
		ops->retlen = 0;
		ops->oobretlen = 0;
		वापस -EINVAL;
	पूर्ण

	stats = mtd->ecc_stats;

	/* Read-जबतक-load method */

	/* Do first load to bufferRAM */
	अगर (पढ़ो < len) अणु
		अगर (!onenand_check_bufferram(mtd, from)) अणु
			this->command(mtd, ONEन_अंकD_CMD_READ, from, ग_लिखोsize);
			ret = this->रुको(mtd, FL_READING);
			onenand_update_bufferram(mtd, from, !ret);
			अगर (mtd_is_eccerr(ret))
				ret = 0;
		पूर्ण
	पूर्ण

	thislen = min_t(पूर्णांक, ग_लिखोsize, len - पढ़ो);
	column = from & (ग_लिखोsize - 1);
	अगर (column + thislen > ग_लिखोsize)
		thislen = ग_लिखोsize - column;

	जबतक (!ret) अणु
		/* If there is more to load then start next load */
		from += thislen;
		अगर (पढ़ो + thislen < len) अणु
			this->command(mtd, ONEन_अंकD_CMD_READ, from, ग_लिखोsize);
			/*
			 * Chip boundary handling in DDP
			 * Now we issued chip 1 पढ़ो and poपूर्णांकed chip 1
			 * bufferram so we have to poपूर्णांक chip 0 bufferram.
			 */
			अगर (ONEन_अंकD_IS_DDP(this) &&
			    unlikely(from == (this->chipsize >> 1))) अणु
				this->ग_लिखो_word(ONEन_अंकD_DDP_CHIP0, this->base + ONEन_अंकD_REG_START_ADDRESS2);
				boundary = 1;
			पूर्ण अन्यथा
				boundary = 0;
			ONEन_अंकD_SET_PREV_BUFFERRAM(this);
		पूर्ण
		/* While load is going, पढ़ो from last bufferRAM */
		this->पढ़ो_bufferram(mtd, ONEन_अंकD_DATARAM, buf, column, thislen);

		/* Read oob area अगर needed */
		अगर (oobbuf) अणु
			thisooblen = oobsize - oobcolumn;
			thisooblen = min_t(पूर्णांक, thisooblen, ooblen - oobपढ़ो);

			अगर (ops->mode == MTD_OPS_AUTO_OOB)
				onenand_transfer_स्वतः_oob(mtd, oobbuf, oobcolumn, thisooblen);
			अन्यथा
				this->पढ़ो_bufferram(mtd, ONEन_अंकD_SPARERAM, oobbuf, oobcolumn, thisooblen);
			oobपढ़ो += thisooblen;
			oobbuf += thisooblen;
			oobcolumn = 0;
		पूर्ण

		/* See अगर we are करोne */
		पढ़ो += thislen;
		अगर (पढ़ो == len)
			अवरोध;
		/* Set up क्रम next पढ़ो from bufferRAM */
		अगर (unlikely(boundary))
			this->ग_लिखो_word(ONEन_अंकD_DDP_CHIP1, this->base + ONEन_अंकD_REG_START_ADDRESS2);
		ONEन_अंकD_SET_NEXT_BUFFERRAM(this);
		buf += thislen;
		thislen = min_t(पूर्णांक, ग_लिखोsize, len - पढ़ो);
		column = 0;
		cond_resched();
		/* Now रुको क्रम load */
		ret = this->रुको(mtd, FL_READING);
		onenand_update_bufferram(mtd, from, !ret);
		अगर (mtd_is_eccerr(ret))
			ret = 0;
	पूर्ण

	/*
	 * Return success, अगर no ECC failures, अन्यथा -EBADMSG
	 * fs driver will take care of that, because
	 * retlen == desired len and result == -EBADMSG
	 */
	ops->retlen = पढ़ो;
	ops->oobretlen = oobपढ़ो;

	अगर (ret)
		वापस ret;

	अगर (mtd->ecc_stats.failed - stats.failed)
		वापस -EBADMSG;

	/* वापस max bitflips per ecc step; ONEन_अंकDs correct 1 bit only */
	वापस mtd->ecc_stats.corrected != stats.corrected ? 1 : 0;
पूर्ण

/**
 * onenand_पढ़ो_oob_nolock - [MTD Interface] Oneन_अंकD पढ़ो out-of-band
 * @mtd:		MTD device काष्ठाure
 * @from:		offset to पढ़ो from
 * @ops:		oob operation description काष्ठाure
 *
 * Oneन_अंकD पढ़ो out-of-band data from the spare area
 */
अटल पूर्णांक onenand_पढ़ो_oob_nolock(काष्ठा mtd_info *mtd, loff_t from,
			काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	काष्ठा mtd_ecc_stats stats;
	पूर्णांक पढ़ो = 0, thislen, column, oobsize;
	माप_प्रकार len = ops->ooblen;
	अचिन्हित पूर्णांक mode = ops->mode;
	u_अक्षर *buf = ops->oobbuf;
	पूर्णांक ret = 0, पढ़ोcmd;

	from += ops->ooboffs;

	pr_debug("%s: from = 0x%08x, len = %i\n", __func__, (अचिन्हित पूर्णांक)from,
			(पूर्णांक)len);

	/* Initialize वापस length value */
	ops->oobretlen = 0;

	अगर (mode == MTD_OPS_AUTO_OOB)
		oobsize = mtd->oobavail;
	अन्यथा
		oobsize = mtd->oobsize;

	column = from & (mtd->oobsize - 1);

	अगर (unlikely(column >= oobsize)) अणु
		prपूर्णांकk(KERN_ERR "%s: Attempted to start read outside oob\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	stats = mtd->ecc_stats;

	पढ़ोcmd = ONEन_अंकD_IS_4KB_PAGE(this) ? ONEन_अंकD_CMD_READ : ONEन_अंकD_CMD_READOOB;

	जबतक (पढ़ो < len) अणु
		cond_resched();

		thislen = oobsize - column;
		thislen = min_t(पूर्णांक, thislen, len);

		this->command(mtd, पढ़ोcmd, from, mtd->oobsize);

		onenand_update_bufferram(mtd, from, 0);

		ret = this->रुको(mtd, FL_READING);
		अगर (unlikely(ret))
			ret = onenand_recover_lsb(mtd, from, ret);

		अगर (ret && !mtd_is_eccerr(ret)) अणु
			prपूर्णांकk(KERN_ERR "%s: read failed = 0x%x\n",
				__func__, ret);
			अवरोध;
		पूर्ण

		अगर (mode == MTD_OPS_AUTO_OOB)
			onenand_transfer_स्वतः_oob(mtd, buf, column, thislen);
		अन्यथा
			this->पढ़ो_bufferram(mtd, ONEन_अंकD_SPARERAM, buf, column, thislen);

		पढ़ो += thislen;

		अगर (पढ़ो == len)
			अवरोध;

		buf += thislen;

		/* Read more? */
		अगर (पढ़ो < len) अणु
			/* Page size */
			from += mtd->ग_लिखोsize;
			column = 0;
		पूर्ण
	पूर्ण

	ops->oobretlen = पढ़ो;

	अगर (ret)
		वापस ret;

	अगर (mtd->ecc_stats.failed - stats.failed)
		वापस -EBADMSG;

	वापस 0;
पूर्ण

/**
 * onenand_पढ़ो_oob - [MTD Interface] Read मुख्य and/or out-of-band
 * @mtd:		MTD device काष्ठाure
 * @from:		offset to पढ़ो from
 * @ops:		oob operation description काष्ठाure
 *
 * Read मुख्य and/or out-of-band
 */
अटल पूर्णांक onenand_पढ़ो_oob(काष्ठा mtd_info *mtd, loff_t from,
			    काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक ret;

	चयन (ops->mode) अणु
	हाल MTD_OPS_PLACE_OOB:
	हाल MTD_OPS_AUTO_OOB:
		अवरोध;
	हाल MTD_OPS_RAW:
		/* Not implemented yet */
	शेष:
		वापस -EINVAL;
	पूर्ण

	onenand_get_device(mtd, FL_READING);
	अगर (ops->datbuf)
		ret = ONEन_अंकD_IS_4KB_PAGE(this) ?
			onenand_mlc_पढ़ो_ops_nolock(mtd, from, ops) :
			onenand_पढ़ो_ops_nolock(mtd, from, ops);
	अन्यथा
		ret = onenand_पढ़ो_oob_nolock(mtd, from, ops);
	onenand_release_device(mtd);

	वापस ret;
पूर्ण

/**
 * onenand_bbt_रुको - [DEFAULT] रुको until the command is करोne
 * @mtd:		MTD device काष्ठाure
 * @state:		state to select the max. समयout value
 *
 * Wait क्रम command करोne.
 */
अटल पूर्णांक onenand_bbt_रुको(काष्ठा mtd_info *mtd, पूर्णांक state)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	अचिन्हित दीर्घ समयout;
	अचिन्हित पूर्णांक पूर्णांकerrupt, ctrl, ecc, addr1, addr8;

	/* The 20 msec is enough */
	समयout = jअगरfies + msecs_to_jअगरfies(20);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		पूर्णांकerrupt = this->पढ़ो_word(this->base + ONEन_अंकD_REG_INTERRUPT);
		अगर (पूर्णांकerrupt & ONEन_अंकD_INT_MASTER)
			अवरोध;
	पूर्ण
	/* To get correct पूर्णांकerrupt status in समयout हाल */
	पूर्णांकerrupt = this->पढ़ो_word(this->base + ONEन_अंकD_REG_INTERRUPT);
	ctrl = this->पढ़ो_word(this->base + ONEन_अंकD_REG_CTRL_STATUS);
	addr1 = this->पढ़ो_word(this->base + ONEन_अंकD_REG_START_ADDRESS1);
	addr8 = this->पढ़ो_word(this->base + ONEन_अंकD_REG_START_ADDRESS8);

	अगर (पूर्णांकerrupt & ONEन_अंकD_INT_READ) अणु
		ecc = onenand_पढ़ो_ecc(this);
		अगर (ecc & ONEन_अंकD_ECC_2BIT_ALL) अणु
			prपूर्णांकk(KERN_DEBUG "%s: ecc 0x%04x ctrl 0x%04x "
			       "intr 0x%04x addr1 %#x addr8 %#x\n",
			       __func__, ecc, ctrl, पूर्णांकerrupt, addr1, addr8);
			वापस ONEन_अंकD_BBT_READ_ECC_ERROR;
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "%s: read timeout! ctrl 0x%04x "
		       "intr 0x%04x addr1 %#x addr8 %#x\n",
		       __func__, ctrl, पूर्णांकerrupt, addr1, addr8);
		वापस ONEन_अंकD_BBT_READ_FATAL_ERROR;
	पूर्ण

	/* Initial bad block हाल: 0x2400 or 0x0400 */
	अगर (ctrl & ONEन_अंकD_CTRL_ERROR) अणु
		prपूर्णांकk(KERN_DEBUG "%s: ctrl 0x%04x intr 0x%04x addr1 %#x "
		       "addr8 %#x\n", __func__, ctrl, पूर्णांकerrupt, addr1, addr8);
		वापस ONEन_अंकD_BBT_READ_ERROR;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * onenand_bbt_पढ़ो_oob - [MTD Interface] Oneन_अंकD पढ़ो out-of-band क्रम bbt scan
 * @mtd:		MTD device काष्ठाure
 * @from:		offset to पढ़ो from
 * @ops:		oob operation description काष्ठाure
 *
 * Oneन_अंकD पढ़ो out-of-band data from the spare area क्रम bbt scan
 */
पूर्णांक onenand_bbt_पढ़ो_oob(काष्ठा mtd_info *mtd, loff_t from, 
			    काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक पढ़ो = 0, thislen, column;
	पूर्णांक ret = 0, पढ़ोcmd;
	माप_प्रकार len = ops->ooblen;
	u_अक्षर *buf = ops->oobbuf;

	pr_debug("%s: from = 0x%08x, len = %zi\n", __func__, (अचिन्हित पूर्णांक)from,
			len);

	/* Initialize वापस value */
	ops->oobretlen = 0;

	/* Do not allow पढ़ोs past end of device */
	अगर (unlikely((from + len) > mtd->size)) अणु
		prपूर्णांकk(KERN_ERR "%s: Attempt read beyond end of device\n",
			__func__);
		वापस ONEन_अंकD_BBT_READ_FATAL_ERROR;
	पूर्ण

	/* Grab the lock and see अगर the device is available */
	onenand_get_device(mtd, FL_READING);

	column = from & (mtd->oobsize - 1);

	पढ़ोcmd = ONEन_अंकD_IS_4KB_PAGE(this) ? ONEन_अंकD_CMD_READ : ONEन_अंकD_CMD_READOOB;

	जबतक (पढ़ो < len) अणु
		cond_resched();

		thislen = mtd->oobsize - column;
		thislen = min_t(पूर्णांक, thislen, len);

		this->command(mtd, पढ़ोcmd, from, mtd->oobsize);

		onenand_update_bufferram(mtd, from, 0);

		ret = this->bbt_रुको(mtd, FL_READING);
		अगर (unlikely(ret))
			ret = onenand_recover_lsb(mtd, from, ret);

		अगर (ret)
			अवरोध;

		this->पढ़ो_bufferram(mtd, ONEन_अंकD_SPARERAM, buf, column, thislen);
		पढ़ो += thislen;
		अगर (पढ़ो == len)
			अवरोध;

		buf += thislen;

		/* Read more? */
		अगर (पढ़ो < len) अणु
			/* Update Page size */
			from += this->ग_लिखोsize;
			column = 0;
		पूर्ण
	पूर्ण

	/* Deselect and wake up anyone रुकोing on the device */
	onenand_release_device(mtd);

	ops->oobretlen = पढ़ो;
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_MTD_ONEन_अंकD_VERIFY_WRITE
/**
 * onenand_verअगरy_oob - [GENERIC] verअगरy the oob contents after a ग_लिखो
 * @mtd:		MTD device काष्ठाure
 * @buf:		the databuffer to verअगरy
 * @to:		offset to पढ़ो from
 */
अटल पूर्णांक onenand_verअगरy_oob(काष्ठा mtd_info *mtd, स्थिर u_अक्षर *buf, loff_t to)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	u_अक्षर *oob_buf = this->oob_buf;
	पूर्णांक status, i, पढ़ोcmd;

	पढ़ोcmd = ONEन_अंकD_IS_4KB_PAGE(this) ? ONEन_अंकD_CMD_READ : ONEन_अंकD_CMD_READOOB;

	this->command(mtd, पढ़ोcmd, to, mtd->oobsize);
	onenand_update_bufferram(mtd, to, 0);
	status = this->रुको(mtd, FL_READING);
	अगर (status)
		वापस status;

	this->पढ़ो_bufferram(mtd, ONEन_अंकD_SPARERAM, oob_buf, 0, mtd->oobsize);
	क्रम (i = 0; i < mtd->oobsize; i++)
		अगर (buf[i] != 0xFF && buf[i] != oob_buf[i])
			वापस -EBADMSG;

	वापस 0;
पूर्ण

/**
 * onenand_verअगरy - [GENERIC] verअगरy the chip contents after a ग_लिखो
 * @mtd:          MTD device काष्ठाure
 * @buf:          the databuffer to verअगरy
 * @addr:         offset to पढ़ो from
 * @len:          number of bytes to पढ़ो and compare
 */
अटल पूर्णांक onenand_verअगरy(काष्ठा mtd_info *mtd, स्थिर u_अक्षर *buf, loff_t addr, माप_प्रकार len)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक ret = 0;
	पूर्णांक thislen, column;

	column = addr & (this->ग_लिखोsize - 1);

	जबतक (len != 0) अणु
		thislen = min_t(पूर्णांक, this->ग_लिखोsize - column, len);

		this->command(mtd, ONEन_अंकD_CMD_READ, addr, this->ग_लिखोsize);

		onenand_update_bufferram(mtd, addr, 0);

		ret = this->रुको(mtd, FL_READING);
		अगर (ret)
			वापस ret;

		onenand_update_bufferram(mtd, addr, 1);

		this->पढ़ो_bufferram(mtd, ONEन_अंकD_DATARAM, this->verअगरy_buf, 0, mtd->ग_लिखोsize);

		अगर (स_भेद(buf, this->verअगरy_buf + column, thislen))
			वापस -EBADMSG;

		len -= thislen;
		buf += thislen;
		addr += thislen;
		column = 0;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा onenand_verअगरy(...)		(0)
#घोषणा onenand_verअगरy_oob(...)		(0)
#पूर्ण_अगर

#घोषणा NOTALIGNED(x)	((x & (this->subpagesize - 1)) != 0)

अटल व्योम onenand_panic_रुको(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	अचिन्हित पूर्णांक पूर्णांकerrupt;
	पूर्णांक i;
	
	क्रम (i = 0; i < 2000; i++) अणु
		पूर्णांकerrupt = this->पढ़ो_word(this->base + ONEन_अंकD_REG_INTERRUPT);
		अगर (पूर्णांकerrupt & ONEन_अंकD_INT_MASTER)
			अवरोध;
		udelay(10);
	पूर्ण
पूर्ण

/**
 * onenand_panic_ग_लिखो - [MTD Interface] ग_लिखो buffer to FLASH in a panic context
 * @mtd:		MTD device काष्ठाure
 * @to:		offset to ग_लिखो to
 * @len:		number of bytes to ग_लिखो
 * @retlen:	poपूर्णांकer to variable to store the number of written bytes
 * @buf:		the data to ग_लिखो
 *
 * Write with ECC
 */
अटल पूर्णांक onenand_panic_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
			 माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक column, subpage;
	पूर्णांक written = 0;

	अगर (this->state == FL_PM_SUSPENDED)
		वापस -EBUSY;

	/* Wait क्रम any existing operation to clear */
	onenand_panic_रुको(mtd);

	pr_debug("%s: to = 0x%08x, len = %i\n", __func__, (अचिन्हित पूर्णांक)to,
			(पूर्णांक)len);

	/* Reject ग_लिखोs, which are not page aligned */
        अगर (unlikely(NOTALIGNED(to) || NOTALIGNED(len))) अणु
		prपूर्णांकk(KERN_ERR "%s: Attempt to write not page aligned data\n",
			__func__);
                वापस -EINVAL;
        पूर्ण

	column = to & (mtd->ग_लिखोsize - 1);

	/* Loop until all data ग_लिखो */
	जबतक (written < len) अणु
		पूर्णांक thislen = min_t(पूर्णांक, mtd->ग_लिखोsize - column, len - written);
		u_अक्षर *wbuf = (u_अक्षर *) buf;

		this->command(mtd, ONEन_अंकD_CMD_BUFFERRAM, to, thislen);

		/* Partial page ग_लिखो */
		subpage = thislen < mtd->ग_लिखोsize;
		अगर (subpage) अणु
			स_रखो(this->page_buf, 0xff, mtd->ग_लिखोsize);
			स_नकल(this->page_buf + column, buf, thislen);
			wbuf = this->page_buf;
		पूर्ण

		this->ग_लिखो_bufferram(mtd, ONEन_अंकD_DATARAM, wbuf, 0, mtd->ग_लिखोsize);
		this->ग_लिखो_bufferram(mtd, ONEन_अंकD_SPARERAM, ffअक्षरs, 0, mtd->oobsize);

		this->command(mtd, ONEन_अंकD_CMD_PROG, to, mtd->ग_लिखोsize);

		onenand_panic_रुको(mtd);

		/* In partial page ग_लिखो we करोn't update bufferram */
		onenand_update_bufferram(mtd, to, !subpage);
		अगर (ONEन_अंकD_IS_2PLANE(this)) अणु
			ONEन_अंकD_SET_BUFFERRAM1(this);
			onenand_update_bufferram(mtd, to + this->ग_लिखोsize, !subpage);
		पूर्ण

		written += thislen;

		अगर (written == len)
			अवरोध;

		column = 0;
		to += thislen;
		buf += thislen;
	पूर्ण

	*retlen = written;
	वापस 0;
पूर्ण

/**
 * onenand_fill_स्वतः_oob - [INTERN] oob स्वतः-placement transfer
 * @mtd:		MTD device काष्ठाure
 * @oob_buf:	oob buffer
 * @buf:		source address
 * @column:	oob offset to ग_लिखो to
 * @thislen:	oob length to ग_लिखो
 */
अटल पूर्णांक onenand_fill_स्वतः_oob(काष्ठा mtd_info *mtd, u_अक्षर *oob_buf,
				  स्थिर u_अक्षर *buf, पूर्णांक column, पूर्णांक thislen)
अणु
	वापस mtd_ooblayout_set_databytes(mtd, buf, oob_buf, column, thislen);
पूर्ण

/**
 * onenand_ग_लिखो_ops_nolock - [Oneन_अंकD Interface] ग_लिखो मुख्य and/or out-of-band
 * @mtd:		MTD device काष्ठाure
 * @to:		offset to ग_लिखो to
 * @ops:		oob operation description काष्ठाure
 *
 * Write मुख्य and/or oob with ECC
 */
अटल पूर्णांक onenand_ग_लिखो_ops_nolock(काष्ठा mtd_info *mtd, loff_t to,
				काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक written = 0, column, thislen = 0, subpage = 0;
	पूर्णांक prev = 0, prevlen = 0, prev_subpage = 0, first = 1;
	पूर्णांक oobwritten = 0, oobcolumn, thisooblen, oobsize;
	माप_प्रकार len = ops->len;
	माप_प्रकार ooblen = ops->ooblen;
	स्थिर u_अक्षर *buf = ops->datbuf;
	स्थिर u_अक्षर *oob = ops->oobbuf;
	u_अक्षर *oobbuf;
	पूर्णांक ret = 0, cmd;

	pr_debug("%s: to = 0x%08x, len = %i\n", __func__, (अचिन्हित पूर्णांक)to,
			(पूर्णांक)len);

	/* Initialize retlen, in हाल of early निकास */
	ops->retlen = 0;
	ops->oobretlen = 0;

	/* Reject ग_लिखोs, which are not page aligned */
        अगर (unlikely(NOTALIGNED(to) || NOTALIGNED(len))) अणु
		prपूर्णांकk(KERN_ERR "%s: Attempt to write not page aligned data\n",
			__func__);
                वापस -EINVAL;
        पूर्ण

	/* Check zero length */
	अगर (!len)
		वापस 0;
	oobsize = mtd_oobavail(mtd, ops);
	oobcolumn = to & (mtd->oobsize - 1);

	column = to & (mtd->ग_लिखोsize - 1);

	/* Loop until all data ग_लिखो */
	जबतक (1) अणु
		अगर (written < len) अणु
			u_अक्षर *wbuf = (u_अक्षर *) buf;

			thislen = min_t(पूर्णांक, mtd->ग_लिखोsize - column, len - written);
			thisooblen = min_t(पूर्णांक, oobsize - oobcolumn, ooblen - oobwritten);

			cond_resched();

			this->command(mtd, ONEन_अंकD_CMD_BUFFERRAM, to, thislen);

			/* Partial page ग_लिखो */
			subpage = thislen < mtd->ग_लिखोsize;
			अगर (subpage) अणु
				स_रखो(this->page_buf, 0xff, mtd->ग_लिखोsize);
				स_नकल(this->page_buf + column, buf, thislen);
				wbuf = this->page_buf;
			पूर्ण

			this->ग_लिखो_bufferram(mtd, ONEन_अंकD_DATARAM, wbuf, 0, mtd->ग_लिखोsize);

			अगर (oob) अणु
				oobbuf = this->oob_buf;

				/* We send data to spare ram with oobsize
				 * to prevent byte access */
				स_रखो(oobbuf, 0xff, mtd->oobsize);
				अगर (ops->mode == MTD_OPS_AUTO_OOB)
					onenand_fill_स्वतः_oob(mtd, oobbuf, oob, oobcolumn, thisooblen);
				अन्यथा
					स_नकल(oobbuf + oobcolumn, oob, thisooblen);

				oobwritten += thisooblen;
				oob += thisooblen;
				oobcolumn = 0;
			पूर्ण अन्यथा
				oobbuf = (u_अक्षर *) ffअक्षरs;

			this->ग_लिखो_bufferram(mtd, ONEन_अंकD_SPARERAM, oobbuf, 0, mtd->oobsize);
		पूर्ण अन्यथा
			ONEन_अंकD_SET_NEXT_BUFFERRAM(this);

		/*
		 * 2 PLANE, MLC, and Flex-Oneन_अंकD करो not support
		 * ग_लिखो-जबतक-program feature.
		 */
		अगर (!ONEन_अंकD_IS_2PLANE(this) && !ONEन_अंकD_IS_4KB_PAGE(this) && !first) अणु
			ONEन_अंकD_SET_PREV_BUFFERRAM(this);

			ret = this->रुको(mtd, FL_WRITING);

			/* In partial page ग_लिखो we करोn't update bufferram */
			onenand_update_bufferram(mtd, prev, !ret && !prev_subpage);
			अगर (ret) अणु
				written -= prevlen;
				prपूर्णांकk(KERN_ERR "%s: write failed %d\n",
					__func__, ret);
				अवरोध;
			पूर्ण

			अगर (written == len) अणु
				/* Only check verअगरy ग_लिखो turn on */
				ret = onenand_verअगरy(mtd, buf - len, to - len, len);
				अगर (ret)
					prपूर्णांकk(KERN_ERR "%s: verify failed %d\n",
						__func__, ret);
				अवरोध;
			पूर्ण

			ONEन_अंकD_SET_NEXT_BUFFERRAM(this);
		पूर्ण

		this->ongoing = 0;
		cmd = ONEन_अंकD_CMD_PROG;

		/* Exclude 1st OTP and OTP blocks क्रम cache program feature */
		अगर (ONEन_अंकD_IS_CACHE_PROGRAM(this) &&
		    likely(onenand_block(this, to) != 0) &&
		    ONEन_अंकD_IS_4KB_PAGE(this) &&
		    ((written + thislen) < len)) अणु
			cmd = ONEन_अंकD_CMD_2X_CACHE_PROG;
			this->ongoing = 1;
		पूर्ण

		this->command(mtd, cmd, to, mtd->ग_लिखोsize);

		/*
		 * 2 PLANE, MLC, and Flex-Oneन_अंकD रुको here
		 */
		अगर (ONEन_अंकD_IS_2PLANE(this) || ONEन_अंकD_IS_4KB_PAGE(this)) अणु
			ret = this->रुको(mtd, FL_WRITING);

			/* In partial page ग_लिखो we करोn't update bufferram */
			onenand_update_bufferram(mtd, to, !ret && !subpage);
			अगर (ret) अणु
				prपूर्णांकk(KERN_ERR "%s: write failed %d\n",
					__func__, ret);
				अवरोध;
			पूर्ण

			/* Only check verअगरy ग_लिखो turn on */
			ret = onenand_verअगरy(mtd, buf, to, thislen);
			अगर (ret) अणु
				prपूर्णांकk(KERN_ERR "%s: verify failed %d\n",
					__func__, ret);
				अवरोध;
			पूर्ण

			written += thislen;

			अगर (written == len)
				अवरोध;

		पूर्ण अन्यथा
			written += thislen;

		column = 0;
		prev_subpage = subpage;
		prev = to;
		prevlen = thislen;
		to += thislen;
		buf += thislen;
		first = 0;
	पूर्ण

	/* In error हाल, clear all bufferrams */
	अगर (written != len)
		onenand_invalidate_bufferram(mtd, 0, -1);

	ops->retlen = written;
	ops->oobretlen = oobwritten;

	वापस ret;
पूर्ण


/**
 * onenand_ग_लिखो_oob_nolock - [INTERN] Oneन_अंकD ग_लिखो out-of-band
 * @mtd:		MTD device काष्ठाure
 * @to:			offset to ग_लिखो to
 * @ops:                oob operation description काष्ठाure
 *
 * Oneन_अंकD ग_लिखो out-of-band
 */
अटल पूर्णांक onenand_ग_लिखो_oob_nolock(काष्ठा mtd_info *mtd, loff_t to,
				    काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक column, ret = 0, oobsize;
	पूर्णांक written = 0, oobcmd;
	u_अक्षर *oobbuf;
	माप_प्रकार len = ops->ooblen;
	स्थिर u_अक्षर *buf = ops->oobbuf;
	अचिन्हित पूर्णांक mode = ops->mode;

	to += ops->ooboffs;

	pr_debug("%s: to = 0x%08x, len = %i\n", __func__, (अचिन्हित पूर्णांक)to,
			(पूर्णांक)len);

	/* Initialize retlen, in हाल of early निकास */
	ops->oobretlen = 0;

	अगर (mode == MTD_OPS_AUTO_OOB)
		oobsize = mtd->oobavail;
	अन्यथा
		oobsize = mtd->oobsize;

	column = to & (mtd->oobsize - 1);

	अगर (unlikely(column >= oobsize)) अणु
		prपूर्णांकk(KERN_ERR "%s: Attempted to start write outside oob\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	/* For compatibility with न_अंकD: Do not allow ग_लिखो past end of page */
	अगर (unlikely(column + len > oobsize)) अणु
		prपूर्णांकk(KERN_ERR "%s: Attempt to write past end of page\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	oobbuf = this->oob_buf;

	oobcmd = ONEन_अंकD_IS_4KB_PAGE(this) ? ONEन_अंकD_CMD_PROG : ONEन_अंकD_CMD_PROGOOB;

	/* Loop until all data ग_लिखो */
	जबतक (written < len) अणु
		पूर्णांक thislen = min_t(पूर्णांक, oobsize, len - written);

		cond_resched();

		this->command(mtd, ONEन_अंकD_CMD_BUFFERRAM, to, mtd->oobsize);

		/* We send data to spare ram with oobsize
		 * to prevent byte access */
		स_रखो(oobbuf, 0xff, mtd->oobsize);
		अगर (mode == MTD_OPS_AUTO_OOB)
			onenand_fill_स्वतः_oob(mtd, oobbuf, buf, column, thislen);
		अन्यथा
			स_नकल(oobbuf + column, buf, thislen);
		this->ग_लिखो_bufferram(mtd, ONEन_अंकD_SPARERAM, oobbuf, 0, mtd->oobsize);

		अगर (ONEन_अंकD_IS_4KB_PAGE(this)) अणु
			/* Set मुख्य area of DataRAM to 0xff*/
			स_रखो(this->page_buf, 0xff, mtd->ग_लिखोsize);
			this->ग_लिखो_bufferram(mtd, ONEन_अंकD_DATARAM,
					 this->page_buf, 0, mtd->ग_लिखोsize);
		पूर्ण

		this->command(mtd, oobcmd, to, mtd->oobsize);

		onenand_update_bufferram(mtd, to, 0);
		अगर (ONEन_अंकD_IS_2PLANE(this)) अणु
			ONEन_अंकD_SET_BUFFERRAM1(this);
			onenand_update_bufferram(mtd, to + this->ग_लिखोsize, 0);
		पूर्ण

		ret = this->रुको(mtd, FL_WRITING);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s: write failed %d\n", __func__, ret);
			अवरोध;
		पूर्ण

		ret = onenand_verअगरy_oob(mtd, oobbuf, to);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s: verify failed %d\n",
				__func__, ret);
			अवरोध;
		पूर्ण

		written += thislen;
		अगर (written == len)
			अवरोध;

		to += mtd->ग_लिखोsize;
		buf += thislen;
		column = 0;
	पूर्ण

	ops->oobretlen = written;

	वापस ret;
पूर्ण

/**
 * onenand_ग_लिखो_oob - [MTD Interface] न_अंकD ग_लिखो data and/or out-of-band
 * @mtd:		MTD device काष्ठाure
 * @to:			offset to ग_लिखो
 * @ops:		oob operation description काष्ठाure
 */
अटल पूर्णांक onenand_ग_लिखो_oob(काष्ठा mtd_info *mtd, loff_t to,
			     काष्ठा mtd_oob_ops *ops)
अणु
	पूर्णांक ret;

	चयन (ops->mode) अणु
	हाल MTD_OPS_PLACE_OOB:
	हाल MTD_OPS_AUTO_OOB:
		अवरोध;
	हाल MTD_OPS_RAW:
		/* Not implemented yet */
	शेष:
		वापस -EINVAL;
	पूर्ण

	onenand_get_device(mtd, FL_WRITING);
	अगर (ops->datbuf)
		ret = onenand_ग_लिखो_ops_nolock(mtd, to, ops);
	अन्यथा
		ret = onenand_ग_लिखो_oob_nolock(mtd, to, ops);
	onenand_release_device(mtd);

	वापस ret;
पूर्ण

/**
 * onenand_block_isbad_nolock - [GENERIC] Check अगर a block is marked bad
 * @mtd:		MTD device काष्ठाure
 * @ofs:		offset from device start
 * @allowbbt:	1, अगर its allowed to access the bbt area
 *
 * Check, अगर the block is bad. Either by पढ़ोing the bad block table or
 * calling of the scan function.
 */
अटल पूर्णांक onenand_block_isbad_nolock(काष्ठा mtd_info *mtd, loff_t ofs, पूर्णांक allowbbt)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	काष्ठा bbm_info *bbm = this->bbm;

	/* Return info from the table */
	वापस bbm->isbad_bbt(mtd, ofs, allowbbt);
पूर्ण


अटल पूर्णांक onenand_multiblock_erase_verअगरy(काष्ठा mtd_info *mtd,
					   काष्ठा erase_info *instr)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	loff_t addr = instr->addr;
	पूर्णांक len = instr->len;
	अचिन्हित पूर्णांक block_size = (1 << this->erase_shअगरt);
	पूर्णांक ret = 0;

	जबतक (len) अणु
		this->command(mtd, ONEन_अंकD_CMD_ERASE_VERIFY, addr, block_size);
		ret = this->रुको(mtd, FL_VERIFYING_ERASE);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s: Failed verify, block %d\n",
			       __func__, onenand_block(this, addr));
			instr->fail_addr = addr;
			वापस -1;
		पूर्ण
		len -= block_size;
		addr += block_size;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * onenand_multiblock_erase - [INTERN] erase block(s) using multiblock erase
 * @mtd:		MTD device काष्ठाure
 * @instr:		erase inकाष्ठाion
 * @block_size:		block size
 *
 * Erase one or more blocks up to 64 block at a समय
 */
अटल पूर्णांक onenand_multiblock_erase(काष्ठा mtd_info *mtd,
				    काष्ठा erase_info *instr,
				    अचिन्हित पूर्णांक block_size)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	loff_t addr = instr->addr;
	पूर्णांक len = instr->len;
	पूर्णांक eb_count = 0;
	पूर्णांक ret = 0;
	पूर्णांक bdry_block = 0;

	अगर (ONEन_अंकD_IS_DDP(this)) अणु
		loff_t bdry_addr = this->chipsize >> 1;
		अगर (addr < bdry_addr && (addr + len) > bdry_addr)
			bdry_block = bdry_addr >> this->erase_shअगरt;
	पूर्ण

	/* Pre-check bbs */
	जबतक (len) अणु
		/* Check अगर we have a bad block, we करो not erase bad blocks */
		अगर (onenand_block_isbad_nolock(mtd, addr, 0)) अणु
			prपूर्णांकk(KERN_WARNING "%s: attempt to erase a bad block "
			       "at addr 0x%012llx\n",
			       __func__, (अचिन्हित दीर्घ दीर्घ) addr);
			वापस -EIO;
		पूर्ण
		len -= block_size;
		addr += block_size;
	पूर्ण

	len = instr->len;
	addr = instr->addr;

	/* loop over 64 eb batches */
	जबतक (len) अणु
		काष्ठा erase_info verअगरy_instr = *instr;
		पूर्णांक max_eb_count = MB_ERASE_MAX_BLK_COUNT;

		verअगरy_instr.addr = addr;
		verअगरy_instr.len = 0;

		/* करो not cross chip boundary */
		अगर (bdry_block) अणु
			पूर्णांक this_block = (addr >> this->erase_shअगरt);

			अगर (this_block < bdry_block) अणु
				max_eb_count = min(max_eb_count,
						   (bdry_block - this_block));
			पूर्ण
		पूर्ण

		eb_count = 0;

		जबतक (len > block_size && eb_count < (max_eb_count - 1)) अणु
			this->command(mtd, ONEन_अंकD_CMD_MULTIBLOCK_ERASE,
				      addr, block_size);
			onenand_invalidate_bufferram(mtd, addr, block_size);

			ret = this->रुको(mtd, FL_PREPARING_ERASE);
			अगर (ret) अणु
				prपूर्णांकk(KERN_ERR "%s: Failed multiblock erase, "
				       "block %d\n", __func__,
				       onenand_block(this, addr));
				instr->fail_addr = MTD_FAIL_ADDR_UNKNOWN;
				वापस -EIO;
			पूर्ण

			len -= block_size;
			addr += block_size;
			eb_count++;
		पूर्ण

		/* last block of 64-eb series */
		cond_resched();
		this->command(mtd, ONEन_अंकD_CMD_ERASE, addr, block_size);
		onenand_invalidate_bufferram(mtd, addr, block_size);

		ret = this->रुको(mtd, FL_ERASING);
		/* Check अगर it is ग_लिखो रक्षित */
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s: Failed erase, block %d\n",
			       __func__, onenand_block(this, addr));
			instr->fail_addr = MTD_FAIL_ADDR_UNKNOWN;
			वापस -EIO;
		पूर्ण

		len -= block_size;
		addr += block_size;
		eb_count++;

		/* verअगरy */
		verअगरy_instr.len = eb_count * block_size;
		अगर (onenand_multiblock_erase_verअगरy(mtd, &verअगरy_instr)) अणु
			instr->fail_addr = verअगरy_instr.fail_addr;
			वापस -EIO;
		पूर्ण

	पूर्ण
	वापस 0;
पूर्ण


/**
 * onenand_block_by_block_erase - [INTERN] erase block(s) using regular erase
 * @mtd:		MTD device काष्ठाure
 * @instr:		erase inकाष्ठाion
 * @region:	erase region
 * @block_size:	erase block size
 *
 * Erase one or more blocks one block at a समय
 */
अटल पूर्णांक onenand_block_by_block_erase(काष्ठा mtd_info *mtd,
					काष्ठा erase_info *instr,
					काष्ठा mtd_erase_region_info *region,
					अचिन्हित पूर्णांक block_size)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	loff_t addr = instr->addr;
	पूर्णांक len = instr->len;
	loff_t region_end = 0;
	पूर्णांक ret = 0;

	अगर (region) अणु
		/* region is set क्रम Flex-Oneन_अंकD */
		region_end = region->offset + region->erasesize * region->numblocks;
	पूर्ण

	/* Loop through the blocks */
	जबतक (len) अणु
		cond_resched();

		/* Check अगर we have a bad block, we करो not erase bad blocks */
		अगर (onenand_block_isbad_nolock(mtd, addr, 0)) अणु
			prपूर्णांकk(KERN_WARNING "%s: attempt to erase a bad block "
					"at addr 0x%012llx\n",
					__func__, (अचिन्हित दीर्घ दीर्घ) addr);
			वापस -EIO;
		पूर्ण

		this->command(mtd, ONEन_अंकD_CMD_ERASE, addr, block_size);

		onenand_invalidate_bufferram(mtd, addr, block_size);

		ret = this->रुको(mtd, FL_ERASING);
		/* Check, अगर it is ग_लिखो रक्षित */
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s: Failed erase, block %d\n",
				__func__, onenand_block(this, addr));
			instr->fail_addr = addr;
			वापस -EIO;
		पूर्ण

		len -= block_size;
		addr += block_size;

		अगर (region && addr == region_end) अणु
			अगर (!len)
				अवरोध;
			region++;

			block_size = region->erasesize;
			region_end = region->offset + region->erasesize * region->numblocks;

			अगर (len & (block_size - 1)) अणु
				/* FIXME: This should be handled at MTD partitioning level. */
				prपूर्णांकk(KERN_ERR "%s: Unaligned address\n",
					__func__);
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * onenand_erase - [MTD Interface] erase block(s)
 * @mtd:		MTD device काष्ठाure
 * @instr:		erase inकाष्ठाion
 *
 * Erase one or more blocks
 */
अटल पूर्णांक onenand_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	अचिन्हित पूर्णांक block_size;
	loff_t addr = instr->addr;
	loff_t len = instr->len;
	पूर्णांक ret = 0;
	काष्ठा mtd_erase_region_info *region = शून्य;
	loff_t region_offset = 0;

	pr_debug("%s: start=0x%012llx, len=%llu\n", __func__,
			(अचिन्हित दीर्घ दीर्घ)instr->addr,
			(अचिन्हित दीर्घ दीर्घ)instr->len);

	अगर (FLEXONEन_अंकD(this)) अणु
		/* Find the eraseregion of this address */
		पूर्णांक i = flexonenand_region(mtd, addr);

		region = &mtd->eraseregions[i];
		block_size = region->erasesize;

		/* Start address within region must align on block boundary.
		 * Erase region's start offset is always block start address.
		 */
		region_offset = region->offset;
	पूर्ण अन्यथा
		block_size = 1 << this->erase_shअगरt;

	/* Start address must align on block boundary */
	अगर (unlikely((addr - region_offset) & (block_size - 1))) अणु
		prपूर्णांकk(KERN_ERR "%s: Unaligned address\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Length must align on block boundary */
	अगर (unlikely(len & (block_size - 1))) अणु
		prपूर्णांकk(KERN_ERR "%s: Length not block aligned\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Grab the lock and see अगर the device is available */
	onenand_get_device(mtd, FL_ERASING);

	अगर (ONEन_अंकD_IS_4KB_PAGE(this) || region ||
	    instr->len < MB_ERASE_MIN_BLK_COUNT * block_size) अणु
		/* region is set क्रम Flex-Oneन_अंकD (no mb erase) */
		ret = onenand_block_by_block_erase(mtd, instr,
						   region, block_size);
	पूर्ण अन्यथा अणु
		ret = onenand_multiblock_erase(mtd, instr, block_size);
	पूर्ण

	/* Deselect and wake up anyone रुकोing on the device */
	onenand_release_device(mtd);

	वापस ret;
पूर्ण

/**
 * onenand_sync - [MTD Interface] sync
 * @mtd:		MTD device काष्ठाure
 *
 * Sync is actually a रुको क्रम chip पढ़ोy function
 */
अटल व्योम onenand_sync(काष्ठा mtd_info *mtd)
अणु
	pr_debug("%s: called\n", __func__);

	/* Grab the lock and see अगर the device is available */
	onenand_get_device(mtd, FL_SYNCING);

	/* Release it and go back */
	onenand_release_device(mtd);
पूर्ण

/**
 * onenand_block_isbad - [MTD Interface] Check whether the block at the given offset is bad
 * @mtd:		MTD device काष्ठाure
 * @ofs:		offset relative to mtd start
 *
 * Check whether the block is bad
 */
अटल पूर्णांक onenand_block_isbad(काष्ठा mtd_info *mtd, loff_t ofs)
अणु
	पूर्णांक ret;

	onenand_get_device(mtd, FL_READING);
	ret = onenand_block_isbad_nolock(mtd, ofs, 0);
	onenand_release_device(mtd);
	वापस ret;
पूर्ण

/**
 * onenand_शेष_block_markbad - [DEFAULT] mark a block bad
 * @mtd:		MTD device काष्ठाure
 * @ofs:		offset from device start
 *
 * This is the शेष implementation, which can be overridden by
 * a hardware specअगरic driver.
 */
अटल पूर्णांक onenand_शेष_block_markbad(काष्ठा mtd_info *mtd, loff_t ofs)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	काष्ठा bbm_info *bbm = this->bbm;
	u_अक्षर buf[2] = अणु0, 0पूर्ण;
	काष्ठा mtd_oob_ops ops = अणु
		.mode = MTD_OPS_PLACE_OOB,
		.ooblen = 2,
		.oobbuf = buf,
		.ooboffs = 0,
	पूर्ण;
	पूर्णांक block;

	/* Get block number */
	block = onenand_block(this, ofs);
        अगर (bbm->bbt)
                bbm->bbt[block >> 2] |= 0x01 << ((block & 0x03) << 1);

        /* We ग_लिखो two bytes, so we करोn't have to mess with 16-bit access */
        ofs += mtd->oobsize + (this->badblockpos & ~0x01);
	/* FIXME : What to करो when marking SLC block in partition
	 * 	   with MLC erasesize? For now, it is not advisable to
	 *	   create partitions containing both SLC and MLC regions.
	 */
	वापस onenand_ग_लिखो_oob_nolock(mtd, ofs, &ops);
पूर्ण

/**
 * onenand_block_markbad - [MTD Interface] Mark the block at the given offset as bad
 * @mtd:		MTD device काष्ठाure
 * @ofs:		offset relative to mtd start
 *
 * Mark the block as bad
 */
अटल पूर्णांक onenand_block_markbad(काष्ठा mtd_info *mtd, loff_t ofs)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक ret;

	ret = onenand_block_isbad(mtd, ofs);
	अगर (ret) अणु
		/* If it was bad alपढ़ोy, वापस success and करो nothing */
		अगर (ret > 0)
			वापस 0;
		वापस ret;
	पूर्ण

	onenand_get_device(mtd, FL_WRITING);
	ret = this->block_markbad(mtd, ofs);
	onenand_release_device(mtd);
	वापस ret;
पूर्ण

/**
 * onenand_करो_lock_cmd - [Oneन_अंकD Interface] Lock or unlock block(s)
 * @mtd:		MTD device काष्ठाure
 * @ofs:		offset relative to mtd start
 * @len:		number of bytes to lock or unlock
 * @cmd:		lock or unlock command
 *
 * Lock or unlock one or more blocks
 */
अटल पूर्णांक onenand_करो_lock_cmd(काष्ठा mtd_info *mtd, loff_t ofs, माप_प्रकार len, पूर्णांक cmd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक start, end, block, value, status;
	पूर्णांक wp_status_mask;

	start = onenand_block(this, ofs);
	end = onenand_block(this, ofs + len) - 1;

	अगर (cmd == ONEन_अंकD_CMD_LOCK)
		wp_status_mask = ONEन_अंकD_WP_LS;
	अन्यथा
		wp_status_mask = ONEन_अंकD_WP_US;

	/* Continuous lock scheme */
	अगर (this->options & ONEन_अंकD_HAS_CONT_LOCK) अणु
		/* Set start block address */
		this->ग_लिखो_word(start, this->base + ONEन_अंकD_REG_START_BLOCK_ADDRESS);
		/* Set end block address */
		this->ग_लिखो_word(end, this->base +  ONEन_अंकD_REG_END_BLOCK_ADDRESS);
		/* Write lock command */
		this->command(mtd, cmd, 0, 0);

		/* There's no वापस value */
		this->रुको(mtd, FL_LOCKING);

		/* Sanity check */
		जबतक (this->पढ़ो_word(this->base + ONEन_अंकD_REG_CTRL_STATUS)
		    & ONEन_अंकD_CTRL_ONGO)
			जारी;

		/* Check lock status */
		status = this->पढ़ो_word(this->base + ONEन_अंकD_REG_WP_STATUS);
		अगर (!(status & wp_status_mask))
			prपूर्णांकk(KERN_ERR "%s: wp status = 0x%x\n",
				__func__, status);

		वापस 0;
	पूर्ण

	/* Block lock scheme */
	क्रम (block = start; block < end + 1; block++) अणु
		/* Set block address */
		value = onenand_block_address(this, block);
		this->ग_लिखो_word(value, this->base + ONEन_अंकD_REG_START_ADDRESS1);
		/* Select DataRAM क्रम DDP */
		value = onenand_bufferram_address(this, block);
		this->ग_लिखो_word(value, this->base + ONEन_अंकD_REG_START_ADDRESS2);
		/* Set start block address */
		this->ग_लिखो_word(block, this->base + ONEन_अंकD_REG_START_BLOCK_ADDRESS);
		/* Write lock command */
		this->command(mtd, cmd, 0, 0);

		/* There's no वापस value */
		this->रुको(mtd, FL_LOCKING);

		/* Sanity check */
		जबतक (this->पढ़ो_word(this->base + ONEन_अंकD_REG_CTRL_STATUS)
		    & ONEन_अंकD_CTRL_ONGO)
			जारी;

		/* Check lock status */
		status = this->पढ़ो_word(this->base + ONEन_अंकD_REG_WP_STATUS);
		अगर (!(status & wp_status_mask))
			prपूर्णांकk(KERN_ERR "%s: block = %d, wp status = 0x%x\n",
				__func__, block, status);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * onenand_lock - [MTD Interface] Lock block(s)
 * @mtd:		MTD device काष्ठाure
 * @ofs:		offset relative to mtd start
 * @len:		number of bytes to unlock
 *
 * Lock one or more blocks
 */
अटल पूर्णांक onenand_lock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	पूर्णांक ret;

	onenand_get_device(mtd, FL_LOCKING);
	ret = onenand_करो_lock_cmd(mtd, ofs, len, ONEन_अंकD_CMD_LOCK);
	onenand_release_device(mtd);
	वापस ret;
पूर्ण

/**
 * onenand_unlock - [MTD Interface] Unlock block(s)
 * @mtd:		MTD device काष्ठाure
 * @ofs:		offset relative to mtd start
 * @len:		number of bytes to unlock
 *
 * Unlock one or more blocks
 */
अटल पूर्णांक onenand_unlock(काष्ठा mtd_info *mtd, loff_t ofs, uपूर्णांक64_t len)
अणु
	पूर्णांक ret;

	onenand_get_device(mtd, FL_LOCKING);
	ret = onenand_करो_lock_cmd(mtd, ofs, len, ONEन_अंकD_CMD_UNLOCK);
	onenand_release_device(mtd);
	वापस ret;
पूर्ण

/**
 * onenand_check_lock_status - [Oneन_अंकD Interface] Check lock status
 * @this:		onenand chip data काष्ठाure
 *
 * Check lock status
 */
अटल पूर्णांक onenand_check_lock_status(काष्ठा onenand_chip *this)
अणु
	अचिन्हित पूर्णांक value, block, status;
	अचिन्हित पूर्णांक end;

	end = this->chipsize >> this->erase_shअगरt;
	क्रम (block = 0; block < end; block++) अणु
		/* Set block address */
		value = onenand_block_address(this, block);
		this->ग_लिखो_word(value, this->base + ONEन_अंकD_REG_START_ADDRESS1);
		/* Select DataRAM क्रम DDP */
		value = onenand_bufferram_address(this, block);
		this->ग_लिखो_word(value, this->base + ONEन_अंकD_REG_START_ADDRESS2);
		/* Set start block address */
		this->ग_लिखो_word(block, this->base + ONEन_अंकD_REG_START_BLOCK_ADDRESS);

		/* Check lock status */
		status = this->पढ़ो_word(this->base + ONEन_अंकD_REG_WP_STATUS);
		अगर (!(status & ONEन_अंकD_WP_US)) अणु
			prपूर्णांकk(KERN_ERR "%s: block = %d, wp status = 0x%x\n",
				__func__, block, status);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

/**
 * onenand_unlock_all - [Oneन_अंकD Interface] unlock all blocks
 * @mtd:		MTD device काष्ठाure
 *
 * Unlock all blocks
 */
अटल व्योम onenand_unlock_all(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	loff_t ofs = 0;
	loff_t len = mtd->size;

	अगर (this->options & ONEन_अंकD_HAS_UNLOCK_ALL) अणु
		/* Set start block address */
		this->ग_लिखो_word(0, this->base + ONEन_अंकD_REG_START_BLOCK_ADDRESS);
		/* Write unlock command */
		this->command(mtd, ONEन_अंकD_CMD_UNLOCK_ALL, 0, 0);

		/* There's no वापस value */
		this->रुको(mtd, FL_LOCKING);

		/* Sanity check */
		जबतक (this->पढ़ो_word(this->base + ONEन_अंकD_REG_CTRL_STATUS)
		    & ONEन_अंकD_CTRL_ONGO)
			जारी;

		/* Don't check lock status */
		अगर (this->options & ONEन_अंकD_SKIP_UNLOCK_CHECK)
			वापस;

		/* Check lock status */
		अगर (onenand_check_lock_status(this))
			वापस;

		/* Workaround क्रम all block unlock in DDP */
		अगर (ONEन_अंकD_IS_DDP(this) && !FLEXONEन_अंकD(this)) अणु
			/* All blocks on another chip */
			ofs = this->chipsize >> 1;
			len = this->chipsize >> 1;
		पूर्ण
	पूर्ण

	onenand_करो_lock_cmd(mtd, ofs, len, ONEन_अंकD_CMD_UNLOCK);
पूर्ण

#अगर_घोषित CONFIG_MTD_ONEन_अंकD_OTP

/**
 * onenand_otp_command - Send OTP specअगरic command to Oneन_अंकD device
 * @mtd:	 MTD device काष्ठाure
 * @cmd:	 the command to be sent
 * @addr:	 offset to पढ़ो from or ग_लिखो to
 * @len:	 number of bytes to पढ़ो or ग_लिखो
 */
अटल पूर्णांक onenand_otp_command(काष्ठा mtd_info *mtd, पूर्णांक cmd, loff_t addr,
				माप_प्रकार len)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक value, block, page;

	/* Address translation */
	चयन (cmd) अणु
	हाल ONEन_अंकD_CMD_OTP_ACCESS:
		block = (पूर्णांक) (addr >> this->erase_shअगरt);
		page = -1;
		अवरोध;

	शेष:
		block = (पूर्णांक) (addr >> this->erase_shअगरt);
		page = (पूर्णांक) (addr >> this->page_shअगरt);

		अगर (ONEन_अंकD_IS_2PLANE(this)) अणु
			/* Make the even block number */
			block &= ~1;
			/* Is it the odd plane? */
			अगर (addr & this->ग_लिखोsize)
				block++;
			page >>= 1;
		पूर्ण
		page &= this->page_mask;
		अवरोध;
	पूर्ण

	अगर (block != -1) अणु
		/* Write 'DFS, FBA' of Flash */
		value = onenand_block_address(this, block);
		this->ग_लिखो_word(value, this->base +
				ONEन_अंकD_REG_START_ADDRESS1);
	पूर्ण

	अगर (page != -1) अणु
		/* Now we use page size operation */
		पूर्णांक sectors = 4, count = 4;
		पूर्णांक dataram;

		चयन (cmd) अणु
		शेष:
			अगर (ONEन_अंकD_IS_2PLANE(this) && cmd == ONEन_अंकD_CMD_PROG)
				cmd = ONEन_अंकD_CMD_2X_PROG;
			dataram = ONEन_अंकD_CURRENT_BUFFERRAM(this);
			अवरोध;
		पूर्ण

		/* Write 'FPA, FSA' of Flash */
		value = onenand_page_address(page, sectors);
		this->ग_लिखो_word(value, this->base +
				ONEन_अंकD_REG_START_ADDRESS8);

		/* Write 'BSA, BSC' of DataRAM */
		value = onenand_buffer_address(dataram, sectors, count);
		this->ग_लिखो_word(value, this->base + ONEन_अंकD_REG_START_BUFFER);
	पूर्ण

	/* Interrupt clear */
	this->ग_लिखो_word(ONEन_अंकD_INT_CLEAR, this->base + ONEन_अंकD_REG_INTERRUPT);

	/* Write command */
	this->ग_लिखो_word(cmd, this->base + ONEन_अंकD_REG_COMMAND);

	वापस 0;
पूर्ण

/**
 * onenand_otp_ग_लिखो_oob_nolock - [INTERN] Oneन_अंकD ग_लिखो out-of-band, specअगरic to OTP
 * @mtd:		MTD device काष्ठाure
 * @to:			offset to ग_लिखो to
 * @ops:                oob operation description काष्ठाure
 *
 * Oneन_अंकD ग_लिखो out-of-band only क्रम OTP
 */
अटल पूर्णांक onenand_otp_ग_लिखो_oob_nolock(काष्ठा mtd_info *mtd, loff_t to,
				    काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक column, ret = 0, oobsize;
	पूर्णांक written = 0;
	u_अक्षर *oobbuf;
	माप_प्रकार len = ops->ooblen;
	स्थिर u_अक्षर *buf = ops->oobbuf;
	पूर्णांक block, value, status;

	to += ops->ooboffs;

	/* Initialize retlen, in हाल of early निकास */
	ops->oobretlen = 0;

	oobsize = mtd->oobsize;

	column = to & (mtd->oobsize - 1);

	oobbuf = this->oob_buf;

	/* Loop until all data ग_लिखो */
	जबतक (written < len) अणु
		पूर्णांक thislen = min_t(पूर्णांक, oobsize, len - written);

		cond_resched();

		block = (पूर्णांक) (to >> this->erase_shअगरt);
		/*
		 * Write 'DFS, FBA' of Flash
		 * Add: F100h DQ=DFS, FBA
		 */

		value = onenand_block_address(this, block);
		this->ग_लिखो_word(value, this->base +
				ONEन_अंकD_REG_START_ADDRESS1);

		/*
		 * Select DataRAM क्रम DDP
		 * Add: F101h DQ=DBS
		 */

		value = onenand_bufferram_address(this, block);
		this->ग_लिखो_word(value, this->base +
				ONEन_अंकD_REG_START_ADDRESS2);
		ONEन_अंकD_SET_NEXT_BUFFERRAM(this);

		/*
		 * Enter OTP access mode
		 */
		this->command(mtd, ONEन_अंकD_CMD_OTP_ACCESS, 0, 0);
		this->रुको(mtd, FL_OTPING);

		/* We send data to spare ram with oobsize
		 * to prevent byte access */
		स_नकल(oobbuf + column, buf, thislen);

		/*
		 * Write Data पूर्णांकo DataRAM
		 * Add: 8th Word
		 * in sector0/spare/page0
		 * DQ=XXFCh
		 */
		this->ग_लिखो_bufferram(mtd, ONEन_अंकD_SPARERAM,
					oobbuf, 0, mtd->oobsize);

		onenand_otp_command(mtd, ONEन_अंकD_CMD_PROGOOB, to, mtd->oobsize);
		onenand_update_bufferram(mtd, to, 0);
		अगर (ONEन_अंकD_IS_2PLANE(this)) अणु
			ONEन_अंकD_SET_BUFFERRAM1(this);
			onenand_update_bufferram(mtd, to + this->ग_लिखोsize, 0);
		पूर्ण

		ret = this->रुको(mtd, FL_WRITING);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s: write failed %d\n", __func__, ret);
			अवरोध;
		पूर्ण

		/* Exit OTP access mode */
		this->command(mtd, ONEन_अंकD_CMD_RESET, 0, 0);
		this->रुको(mtd, FL_RESETTING);

		status = this->पढ़ो_word(this->base + ONEन_अंकD_REG_CTRL_STATUS);
		status &= 0x60;

		अगर (status == 0x60) अणु
			prपूर्णांकk(KERN_DEBUG "\nBLOCK\tSTATUS\n");
			prपूर्णांकk(KERN_DEBUG "1st Block\tLOCKED\n");
			prपूर्णांकk(KERN_DEBUG "OTP Block\tLOCKED\n");
		पूर्ण अन्यथा अगर (status == 0x20) अणु
			prपूर्णांकk(KERN_DEBUG "\nBLOCK\tSTATUS\n");
			prपूर्णांकk(KERN_DEBUG "1st Block\tLOCKED\n");
			prपूर्णांकk(KERN_DEBUG "OTP Block\tUN-LOCKED\n");
		पूर्ण अन्यथा अगर (status == 0x40) अणु
			prपूर्णांकk(KERN_DEBUG "\nBLOCK\tSTATUS\n");
			prपूर्णांकk(KERN_DEBUG "1st Block\tUN-LOCKED\n");
			prपूर्णांकk(KERN_DEBUG "OTP Block\tLOCKED\n");
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_DEBUG "Reboot to check\n");
		पूर्ण

		written += thislen;
		अगर (written == len)
			अवरोध;

		to += mtd->ग_लिखोsize;
		buf += thislen;
		column = 0;
	पूर्ण

	ops->oobretlen = written;

	वापस ret;
पूर्ण

/* Internal OTP operation */
प्रकार पूर्णांक (*otp_op_t)(काष्ठा mtd_info *mtd, loff_t क्रमm, माप_प्रकार len,
		माप_प्रकार *retlen, u_अक्षर *buf);

/**
 * करो_otp_पढ़ो - [DEFAULT] Read OTP block area
 * @mtd:		MTD device काष्ठाure
 * @from:		The offset to पढ़ो
 * @len:		number of bytes to पढ़ो
 * @retlen:	poपूर्णांकer to variable to store the number of पढ़ोbytes
 * @buf:		the databuffer to put/get data
 *
 * Read OTP block area.
 */
अटल पूर्णांक करो_otp_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	काष्ठा mtd_oob_ops ops = अणु
		.len	= len,
		.ooblen	= 0,
		.datbuf	= buf,
		.oobbuf	= शून्य,
	पूर्ण;
	पूर्णांक ret;

	/* Enter OTP access mode */
	this->command(mtd, ONEन_अंकD_CMD_OTP_ACCESS, 0, 0);
	this->रुको(mtd, FL_OTPING);

	ret = ONEन_अंकD_IS_4KB_PAGE(this) ?
		onenand_mlc_पढ़ो_ops_nolock(mtd, from, &ops) :
		onenand_पढ़ो_ops_nolock(mtd, from, &ops);

	/* Exit OTP access mode */
	this->command(mtd, ONEन_अंकD_CMD_RESET, 0, 0);
	this->रुको(mtd, FL_RESETTING);

	वापस ret;
पूर्ण

/**
 * करो_otp_ग_लिखो - [DEFAULT] Write OTP block area
 * @mtd:		MTD device काष्ठाure
 * @to:		The offset to ग_लिखो
 * @len:		number of bytes to ग_लिखो
 * @retlen:	poपूर्णांकer to variable to store the number of ग_लिखो bytes
 * @buf:		the databuffer to put/get data
 *
 * Write OTP block area.
 */
अटल पूर्णांक करो_otp_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
		माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	अचिन्हित अक्षर *pbuf = buf;
	पूर्णांक ret;
	काष्ठा mtd_oob_ops ops;

	/* Force buffer page aligned */
	अगर (len < mtd->ग_लिखोsize) अणु
		स_नकल(this->page_buf, buf, len);
		स_रखो(this->page_buf + len, 0xff, mtd->ग_लिखोsize - len);
		pbuf = this->page_buf;
		len = mtd->ग_लिखोsize;
	पूर्ण

	/* Enter OTP access mode */
	this->command(mtd, ONEन_अंकD_CMD_OTP_ACCESS, 0, 0);
	this->रुको(mtd, FL_OTPING);

	ops.len = len;
	ops.ooblen = 0;
	ops.datbuf = pbuf;
	ops.oobbuf = शून्य;
	ret = onenand_ग_लिखो_ops_nolock(mtd, to, &ops);
	*retlen = ops.retlen;

	/* Exit OTP access mode */
	this->command(mtd, ONEन_अंकD_CMD_RESET, 0, 0);
	this->रुको(mtd, FL_RESETTING);

	वापस ret;
पूर्ण

/**
 * करो_otp_lock - [DEFAULT] Lock OTP block area
 * @mtd:		MTD device काष्ठाure
 * @from:		The offset to lock
 * @len:		number of bytes to lock
 * @retlen:	poपूर्णांकer to variable to store the number of lock bytes
 * @buf:		the databuffer to put/get data
 *
 * Lock OTP block area.
 */
अटल पूर्णांक करो_otp_lock(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
		माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	काष्ठा mtd_oob_ops ops;
	पूर्णांक ret;

	अगर (FLEXONEन_अंकD(this)) अणु

		/* Enter OTP access mode */
		this->command(mtd, ONEन_अंकD_CMD_OTP_ACCESS, 0, 0);
		this->रुको(mtd, FL_OTPING);
		/*
		 * For Flex-Oneन_अंकD, we ग_लिखो lock mark to 1st word of sector 4 of
		 * मुख्य area of page 49.
		 */
		ops.len = mtd->ग_लिखोsize;
		ops.ooblen = 0;
		ops.datbuf = buf;
		ops.oobbuf = शून्य;
		ret = onenand_ग_लिखो_ops_nolock(mtd, mtd->ग_लिखोsize * 49, &ops);
		*retlen = ops.retlen;

		/* Exit OTP access mode */
		this->command(mtd, ONEन_अंकD_CMD_RESET, 0, 0);
		this->रुको(mtd, FL_RESETTING);
	पूर्ण अन्यथा अणु
		ops.mode = MTD_OPS_PLACE_OOB;
		ops.ooblen = len;
		ops.oobbuf = buf;
		ops.ooboffs = 0;
		ret = onenand_otp_ग_लिखो_oob_nolock(mtd, from, &ops);
		*retlen = ops.oobretlen;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * onenand_otp_walk - [DEFAULT] Handle OTP operation
 * @mtd:		MTD device काष्ठाure
 * @from:		The offset to पढ़ो/ग_लिखो
 * @len:		number of bytes to पढ़ो/ग_लिखो
 * @retlen:	poपूर्णांकer to variable to store the number of पढ़ो bytes
 * @buf:		the databuffer to put/get data
 * @action:	करो given action
 * @mode:		specअगरy user and factory
 *
 * Handle OTP operation.
 */
अटल पूर्णांक onenand_otp_walk(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			माप_प्रकार *retlen, u_अक्षर *buf,
			otp_op_t action, पूर्णांक mode)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक otp_pages;
	पूर्णांक density;
	पूर्णांक ret = 0;

	*retlen = 0;

	density = onenand_get_density(this->device_id);
	अगर (density < ONEन_अंकD_DEVICE_DENSITY_512Mb)
		otp_pages = 20;
	अन्यथा
		otp_pages = 50;

	अगर (mode == MTD_OTP_FACTORY) अणु
		from += mtd->ग_लिखोsize * otp_pages;
		otp_pages = ONEन_अंकD_PAGES_PER_BLOCK - otp_pages;
	पूर्ण

	/* Check User/Factory boundary */
	अगर (mode == MTD_OTP_USER) अणु
		अगर (mtd->ग_लिखोsize * otp_pages < from + len)
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (mtd->ग_लिखोsize * otp_pages <  len)
			वापस 0;
	पूर्ण

	onenand_get_device(mtd, FL_OTPING);
	जबतक (len > 0 && otp_pages > 0) अणु
		अगर (!action) अणु	/* OTP Info functions */
			काष्ठा otp_info *otpinfo;

			len -= माप(काष्ठा otp_info);
			अगर (len <= 0) अणु
				ret = -ENOSPC;
				अवरोध;
			पूर्ण

			otpinfo = (काष्ठा otp_info *) buf;
			otpinfo->start = from;
			otpinfo->length = mtd->ग_लिखोsize;
			otpinfo->locked = 0;

			from += mtd->ग_लिखोsize;
			buf += माप(काष्ठा otp_info);
			*retlen += माप(काष्ठा otp_info);
		पूर्ण अन्यथा अणु
			माप_प्रकार पंचांगp_retlen;

			ret = action(mtd, from, len, &पंचांगp_retlen, buf);
			अगर (ret)
				अवरोध;

			buf += पंचांगp_retlen;
			len -= पंचांगp_retlen;
			*retlen += पंचांगp_retlen;

		पूर्ण
		otp_pages--;
	पूर्ण
	onenand_release_device(mtd);

	वापस ret;
पूर्ण

/**
 * onenand_get_fact_prot_info - [MTD Interface] Read factory OTP info
 * @mtd:		MTD device काष्ठाure
 * @len:		number of bytes to पढ़ो
 * @retlen:	poपूर्णांकer to variable to store the number of पढ़ो bytes
 * @buf:		the databuffer to put/get data
 *
 * Read factory OTP info.
 */
अटल पूर्णांक onenand_get_fact_prot_info(काष्ठा mtd_info *mtd, माप_प्रकार len,
				      माप_प्रकार *retlen, काष्ठा otp_info *buf)
अणु
	वापस onenand_otp_walk(mtd, 0, len, retlen, (u_अक्षर *) buf, शून्य,
				MTD_OTP_FACTORY);
पूर्ण

/**
 * onenand_पढ़ो_fact_prot_reg - [MTD Interface] Read factory OTP area
 * @mtd:		MTD device काष्ठाure
 * @from:		The offset to पढ़ो
 * @len:		number of bytes to पढ़ो
 * @retlen:	poपूर्णांकer to variable to store the number of पढ़ो bytes
 * @buf:		the databuffer to put/get data
 *
 * Read factory OTP area.
 */
अटल पूर्णांक onenand_पढ़ो_fact_prot_reg(काष्ठा mtd_info *mtd, loff_t from,
			माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	वापस onenand_otp_walk(mtd, from, len, retlen, buf, करो_otp_पढ़ो, MTD_OTP_FACTORY);
पूर्ण

/**
 * onenand_get_user_prot_info - [MTD Interface] Read user OTP info
 * @mtd:		MTD device काष्ठाure
 * @retlen:	poपूर्णांकer to variable to store the number of पढ़ो bytes
 * @len:		number of bytes to पढ़ो
 * @buf:		the databuffer to put/get data
 *
 * Read user OTP info.
 */
अटल पूर्णांक onenand_get_user_prot_info(काष्ठा mtd_info *mtd, माप_प्रकार len,
				      माप_प्रकार *retlen, काष्ठा otp_info *buf)
अणु
	वापस onenand_otp_walk(mtd, 0, len, retlen, (u_अक्षर *) buf, शून्य,
				MTD_OTP_USER);
पूर्ण

/**
 * onenand_पढ़ो_user_prot_reg - [MTD Interface] Read user OTP area
 * @mtd:		MTD device काष्ठाure
 * @from:		The offset to पढ़ो
 * @len:		number of bytes to पढ़ो
 * @retlen:	poपूर्णांकer to variable to store the number of पढ़ो bytes
 * @buf:		the databuffer to put/get data
 *
 * Read user OTP area.
 */
अटल पूर्णांक onenand_पढ़ो_user_prot_reg(काष्ठा mtd_info *mtd, loff_t from,
			माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	वापस onenand_otp_walk(mtd, from, len, retlen, buf, करो_otp_पढ़ो, MTD_OTP_USER);
पूर्ण

/**
 * onenand_ग_लिखो_user_prot_reg - [MTD Interface] Write user OTP area
 * @mtd:		MTD device काष्ठाure
 * @from:		The offset to ग_लिखो
 * @len:		number of bytes to ग_लिखो
 * @retlen:	poपूर्णांकer to variable to store the number of ग_लिखो bytes
 * @buf:		the databuffer to put/get data
 *
 * Write user OTP area.
 */
अटल पूर्णांक onenand_ग_लिखो_user_prot_reg(काष्ठा mtd_info *mtd, loff_t from,
			माप_प्रकार len, माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	वापस onenand_otp_walk(mtd, from, len, retlen, (u_अक्षर *)buf,
				करो_otp_ग_लिखो, MTD_OTP_USER);
पूर्ण

/**
 * onenand_lock_user_prot_reg - [MTD Interface] Lock user OTP area
 * @mtd:		MTD device काष्ठाure
 * @from:		The offset to lock
 * @len:		number of bytes to unlock
 *
 * Write lock mark on spare area in page 0 in OTP block
 */
अटल पूर्णांक onenand_lock_user_prot_reg(काष्ठा mtd_info *mtd, loff_t from,
			माप_प्रकार len)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	u_अक्षर *buf = FLEXONEन_अंकD(this) ? this->page_buf : this->oob_buf;
	माप_प्रकार retlen;
	पूर्णांक ret;
	अचिन्हित पूर्णांक otp_lock_offset = ONEन_अंकD_OTP_LOCK_OFFSET;

	स_रखो(buf, 0xff, FLEXONEन_अंकD(this) ? this->ग_लिखोsize
						 : mtd->oobsize);
	/*
	 * Write lock mark to 8th word of sector0 of page0 of the spare0.
	 * We ग_लिखो 16 bytes spare area instead of 2 bytes.
	 * For Flex-Oneन_अंकD, we ग_लिखो lock mark to 1st word of sector 4 of
	 * मुख्य area of page 49.
	 */

	from = 0;
	len = FLEXONEन_अंकD(this) ? mtd->ग_लिखोsize : 16;

	/*
	 * Note: OTP lock operation
	 *       OTP block : 0xXXFC			XX 1111 1100
	 *       1st block : 0xXXF3 (If chip support)	XX 1111 0011
	 *       Both      : 0xXXF0 (If chip support)	XX 1111 0000
	 */
	अगर (FLEXONEन_अंकD(this))
		otp_lock_offset = FLEXONEन_अंकD_OTP_LOCK_OFFSET;

	/* ONEन_अंकD_OTP_AREA | ONEन_अंकD_OTP_BLOCK0 | ONEन_अंकD_OTP_AREA_BLOCK0 */
	अगर (otp == 1)
		buf[otp_lock_offset] = 0xFC;
	अन्यथा अगर (otp == 2)
		buf[otp_lock_offset] = 0xF3;
	अन्यथा अगर (otp == 3)
		buf[otp_lock_offset] = 0xF0;
	अन्यथा अगर (otp != 0)
		prपूर्णांकk(KERN_DEBUG "[OneNAND] Invalid option selected for OTP\n");

	ret = onenand_otp_walk(mtd, from, len, &retlen, buf, करो_otp_lock, MTD_OTP_USER);

	वापस ret ? : retlen;
पूर्ण

#पूर्ण_अगर	/* CONFIG_MTD_ONEन_अंकD_OTP */

/**
 * onenand_check_features - Check and set Oneन_अंकD features
 * @mtd:		MTD data काष्ठाure
 *
 * Check and set Oneन_अंकD features
 * - lock scheme
 * - two plane
 */
अटल व्योम onenand_check_features(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	अचिन्हित पूर्णांक density, process, numbufs;

	/* Lock scheme depends on density and process */
	density = onenand_get_density(this->device_id);
	process = this->version_id >> ONEन_अंकD_VERSION_PROCESS_SHIFT;
	numbufs = this->पढ़ो_word(this->base + ONEन_अंकD_REG_NUM_BUFFERS) >> 8;

	/* Lock scheme */
	चयन (density) अणु
	हाल ONEन_अंकD_DEVICE_DENSITY_8Gb:
		this->options |= ONEन_अंकD_HAS_NOP_1;
		fallthrough;
	हाल ONEन_अंकD_DEVICE_DENSITY_4Gb:
		अगर (ONEन_अंकD_IS_DDP(this))
			this->options |= ONEन_अंकD_HAS_2PLANE;
		अन्यथा अगर (numbufs == 1) अणु
			this->options |= ONEन_अंकD_HAS_4KB_PAGE;
			this->options |= ONEन_अंकD_HAS_CACHE_PROGRAM;
			/*
			 * There are two dअगरferent 4KiB pagesize chips
			 * and no way to detect it by H/W config values.
			 *
			 * To detect the correct NOP क्रम each chips,
			 * It should check the version ID as workaround.
			 *
			 * Now it has as following
			 * KFM4G16Q4M has NOP 4 with version ID 0x0131
			 * KFM4G16Q5M has NOP 1 with versoin ID 0x013e
			 */
			अगर ((this->version_id & 0xf) == 0xe)
				this->options |= ONEन_अंकD_HAS_NOP_1;
		पूर्ण
		this->options |= ONEन_अंकD_HAS_UNLOCK_ALL;
		अवरोध;

	हाल ONEन_अंकD_DEVICE_DENSITY_2Gb:
		/* 2Gb DDP करोes not have 2 plane */
		अगर (!ONEन_अंकD_IS_DDP(this))
			this->options |= ONEन_अंकD_HAS_2PLANE;
		this->options |= ONEन_अंकD_HAS_UNLOCK_ALL;
		अवरोध;

	हाल ONEन_अंकD_DEVICE_DENSITY_1Gb:
		/* A-Die has all block unlock */
		अगर (process)
			this->options |= ONEन_अंकD_HAS_UNLOCK_ALL;
		अवरोध;

	शेष:
		/* Some Oneन_अंकD has continuous lock scheme */
		अगर (!process)
			this->options |= ONEन_अंकD_HAS_CONT_LOCK;
		अवरोध;
	पूर्ण

	/* The MLC has 4KiB pagesize. */
	अगर (ONEन_अंकD_IS_MLC(this))
		this->options |= ONEन_अंकD_HAS_4KB_PAGE;

	अगर (ONEन_अंकD_IS_4KB_PAGE(this))
		this->options &= ~ONEन_अंकD_HAS_2PLANE;

	अगर (FLEXONEन_अंकD(this)) अणु
		this->options &= ~ONEन_अंकD_HAS_CONT_LOCK;
		this->options |= ONEन_अंकD_HAS_UNLOCK_ALL;
	पूर्ण

	अगर (this->options & ONEन_अंकD_HAS_CONT_LOCK)
		prपूर्णांकk(KERN_DEBUG "Lock scheme is Continuous Lock\n");
	अगर (this->options & ONEन_अंकD_HAS_UNLOCK_ALL)
		prपूर्णांकk(KERN_DEBUG "Chip support all block unlock\n");
	अगर (this->options & ONEन_अंकD_HAS_2PLANE)
		prपूर्णांकk(KERN_DEBUG "Chip has 2 plane\n");
	अगर (this->options & ONEन_अंकD_HAS_4KB_PAGE)
		prपूर्णांकk(KERN_DEBUG "Chip has 4KiB pagesize\n");
	अगर (this->options & ONEन_अंकD_HAS_CACHE_PROGRAM)
		prपूर्णांकk(KERN_DEBUG "Chip has cache program feature\n");
पूर्ण

/**
 * onenand_prपूर्णांक_device_info - Prपूर्णांक device & version ID
 * @device:        device ID
 * @version:	version ID
 *
 * Prपूर्णांक device & version ID
 */
अटल व्योम onenand_prपूर्णांक_device_info(पूर्णांक device, पूर्णांक version)
अणु
	पूर्णांक vcc, demuxed, ddp, density, flexonenand;

        vcc = device & ONEन_अंकD_DEVICE_VCC_MASK;
        demuxed = device & ONEन_अंकD_DEVICE_IS_DEMUX;
        ddp = device & ONEन_अंकD_DEVICE_IS_DDP;
        density = onenand_get_density(device);
	flexonenand = device & DEVICE_IS_FLEXONEन_अंकD;
	prपूर्णांकk(KERN_INFO "%s%sOneNAND%s %dMB %sV 16-bit (0x%02x)\n",
		demuxed ? "" : "Muxed ",
		flexonenand ? "Flex-" : "",
                ddp ? "(DDP)" : "",
                (16 << density),
                vcc ? "2.65/3.3" : "1.8",
                device);
	prपूर्णांकk(KERN_INFO "OneNAND version = 0x%04x\n", version);
पूर्ण

अटल स्थिर काष्ठा onenand_manufacturers onenand_manuf_ids[] = अणु
        अणुONEन_अंकD_MFR_SAMSUNG, "Samsung"पूर्ण,
	अणुONEन_अंकD_MFR_NUMONYX, "Numonyx"पूर्ण,
पूर्ण;

/**
 * onenand_check_maf - Check manufacturer ID
 * @manuf:         manufacturer ID
 *
 * Check manufacturer ID
 */
अटल पूर्णांक onenand_check_maf(पूर्णांक manuf)
अणु
	पूर्णांक size = ARRAY_SIZE(onenand_manuf_ids);
	अक्षर *name;
        पूर्णांक i;

	क्रम (i = 0; i < size; i++)
                अगर (manuf == onenand_manuf_ids[i].id)
                        अवरोध;

	अगर (i < size)
		name = onenand_manuf_ids[i].name;
	अन्यथा
		name = "Unknown";

	prपूर्णांकk(KERN_DEBUG "OneNAND Manufacturer: %s (0x%0x)\n", name, manuf);

	वापस (i == size);
पूर्ण

/**
 * flexonenand_get_boundary	- Reads the SLC boundary
 * @mtd:		MTD data काष्ठाure
 */
अटल पूर्णांक flexonenand_get_boundary(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	अचिन्हित die, bdry;
	पूर्णांक syscfg, locked;

	/* Disable ECC */
	syscfg = this->पढ़ो_word(this->base + ONEन_अंकD_REG_SYS_CFG1);
	this->ग_लिखो_word((syscfg | 0x0100), this->base + ONEन_अंकD_REG_SYS_CFG1);

	क्रम (die = 0; die < this->dies; die++) अणु
		this->command(mtd, FLEXONEन_अंकD_CMD_PI_ACCESS, die, 0);
		this->रुको(mtd, FL_SYNCING);

		this->command(mtd, FLEXONEन_अंकD_CMD_READ_PI, die, 0);
		this->रुको(mtd, FL_READING);

		bdry = this->पढ़ो_word(this->base + ONEन_अंकD_DATARAM);
		अगर ((bdry >> FLEXONEन_अंकD_PI_UNLOCK_SHIFT) == 3)
			locked = 0;
		अन्यथा
			locked = 1;
		this->boundary[die] = bdry & FLEXONEन_अंकD_PI_MASK;

		this->command(mtd, ONEन_अंकD_CMD_RESET, 0, 0);
		this->रुको(mtd, FL_RESETTING);

		prपूर्णांकk(KERN_INFO "Die %d boundary: %d%s\n", die,
		       this->boundary[die], locked ? "(Locked)" : "(Unlocked)");
	पूर्ण

	/* Enable ECC */
	this->ग_लिखो_word(syscfg, this->base + ONEन_अंकD_REG_SYS_CFG1);
	वापस 0;
पूर्ण

/**
 * flexonenand_get_size - Fill up fields in onenand_chip and mtd_info
 * 			  boundary[], diesize[], mtd->size, mtd->erasesize
 * @mtd:		- MTD device काष्ठाure
 */
अटल व्योम flexonenand_get_size(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक die, i, eraseshअगरt, density;
	पूर्णांक blksperdie, maxbdry;
	loff_t ofs;

	density = onenand_get_density(this->device_id);
	blksperdie = ((loff_t)(16 << density) << 20) >> (this->erase_shअगरt);
	blksperdie >>= ONEन_अंकD_IS_DDP(this) ? 1 : 0;
	maxbdry = blksperdie - 1;
	eraseshअगरt = this->erase_shअगरt - 1;

	mtd->numeraseregions = this->dies << 1;

	/* This fills up the device boundary */
	flexonenand_get_boundary(mtd);
	die = ofs = 0;
	i = -1;
	क्रम (; die < this->dies; die++) अणु
		अगर (!die || this->boundary[die-1] != maxbdry) अणु
			i++;
			mtd->eraseregions[i].offset = ofs;
			mtd->eraseregions[i].erasesize = 1 << eraseshअगरt;
			mtd->eraseregions[i].numblocks =
							this->boundary[die] + 1;
			ofs += mtd->eraseregions[i].numblocks << eraseshअगरt;
			eraseshअगरt++;
		पूर्ण अन्यथा अणु
			mtd->numeraseregions -= 1;
			mtd->eraseregions[i].numblocks +=
							this->boundary[die] + 1;
			ofs += (this->boundary[die] + 1) << (eraseshअगरt - 1);
		पूर्ण
		अगर (this->boundary[die] != maxbdry) अणु
			i++;
			mtd->eraseregions[i].offset = ofs;
			mtd->eraseregions[i].erasesize = 1 << eraseshअगरt;
			mtd->eraseregions[i].numblocks = maxbdry ^
							 this->boundary[die];
			ofs += mtd->eraseregions[i].numblocks << eraseshअगरt;
			eraseshअगरt--;
		पूर्ण अन्यथा
			mtd->numeraseregions -= 1;
	पूर्ण

	/* Expose MLC erase size except when all blocks are SLC */
	mtd->erasesize = 1 << this->erase_shअगरt;
	अगर (mtd->numeraseregions == 1)
		mtd->erasesize >>= 1;

	prपूर्णांकk(KERN_INFO "Device has %d eraseregions\n", mtd->numeraseregions);
	क्रम (i = 0; i < mtd->numeraseregions; i++)
		prपूर्णांकk(KERN_INFO "[offset: 0x%08x, erasesize: 0x%05x,"
			" numblocks: %04u]\n",
			(अचिन्हित पूर्णांक) mtd->eraseregions[i].offset,
			mtd->eraseregions[i].erasesize,
			mtd->eraseregions[i].numblocks);

	क्रम (die = 0, mtd->size = 0; die < this->dies; die++) अणु
		this->diesize[die] = (loff_t)blksperdie << this->erase_shअगरt;
		this->diesize[die] -= (loff_t)(this->boundary[die] + 1)
						 << (this->erase_shअगरt - 1);
		mtd->size += this->diesize[die];
	पूर्ण
पूर्ण

/**
 * flexonenand_check_blocks_erased - Check अगर blocks are erased
 * @mtd:	mtd info काष्ठाure
 * @start:	first erase block to check
 * @end:	last erase block to check
 *
 * Converting an unerased block from MLC to SLC
 * causes byte values to change. Since both data and its ECC
 * have changed, पढ़ोs on the block give uncorrectable error.
 * This might lead to the block being detected as bad.
 *
 * Aव्योम this by ensuring that the block to be converted is
 * erased.
 */
अटल पूर्णांक flexonenand_check_blocks_erased(काष्ठा mtd_info *mtd, पूर्णांक start, पूर्णांक end)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक i, ret;
	पूर्णांक block;
	काष्ठा mtd_oob_ops ops = अणु
		.mode = MTD_OPS_PLACE_OOB,
		.ooboffs = 0,
		.ooblen	= mtd->oobsize,
		.datbuf	= शून्य,
		.oobbuf	= this->oob_buf,
	पूर्ण;
	loff_t addr;

	prपूर्णांकk(KERN_DEBUG "Check blocks from %d to %d\n", start, end);

	क्रम (block = start; block <= end; block++) अणु
		addr = flexonenand_addr(this, block);
		अगर (onenand_block_isbad_nolock(mtd, addr, 0))
			जारी;

		/*
		 * Since मुख्य area ग_लिखो results in ECC ग_लिखो to spare,
		 * it is sufficient to check only ECC bytes क्रम change.
		 */
		ret = onenand_पढ़ो_oob_nolock(mtd, addr, &ops);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < mtd->oobsize; i++)
			अगर (this->oob_buf[i] != 0xff)
				अवरोध;

		अगर (i != mtd->oobsize) अणु
			prपूर्णांकk(KERN_WARNING "%s: Block %d not erased.\n",
				__func__, block);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * flexonenand_set_boundary	- Writes the SLC boundary
 */
अटल पूर्णांक flexonenand_set_boundary(काष्ठा mtd_info *mtd, पूर्णांक die,
				    पूर्णांक boundary, पूर्णांक lock)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक ret, density, blksperdie, old, new, thisboundary;
	loff_t addr;

	/* Change only once क्रम SDP Flex-Oneन_अंकD */
	अगर (die && (!ONEन_अंकD_IS_DDP(this)))
		वापस 0;

	/* boundary value of -1 indicates no required change */
	अगर (boundary < 0 || boundary == this->boundary[die])
		वापस 0;

	density = onenand_get_density(this->device_id);
	blksperdie = ((16 << density) << 20) >> this->erase_shअगरt;
	blksperdie >>= ONEन_अंकD_IS_DDP(this) ? 1 : 0;

	अगर (boundary >= blksperdie) अणु
		prपूर्णांकk(KERN_ERR "%s: Invalid boundary value. "
				"Boundary not changed.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Check अगर converting blocks are erased */
	old = this->boundary[die] + (die * this->density_mask);
	new = boundary + (die * this->density_mask);
	ret = flexonenand_check_blocks_erased(mtd, min(old, new) + 1, max(old, new));
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: Please erase blocks "
				"before boundary change\n", __func__);
		वापस ret;
	पूर्ण

	this->command(mtd, FLEXONEन_अंकD_CMD_PI_ACCESS, die, 0);
	this->रुको(mtd, FL_SYNCING);

	/* Check is boundary is locked */
	this->command(mtd, FLEXONEन_अंकD_CMD_READ_PI, die, 0);
	this->रुको(mtd, FL_READING);

	thisboundary = this->पढ़ो_word(this->base + ONEन_अंकD_DATARAM);
	अगर ((thisboundary >> FLEXONEन_अंकD_PI_UNLOCK_SHIFT) != 3) अणु
		prपूर्णांकk(KERN_ERR "%s: boundary locked\n", __func__);
		ret = 1;
		जाओ out;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Changing die %d boundary: %d%s\n",
			die, boundary, lock ? "(Locked)" : "(Unlocked)");

	addr = die ? this->diesize[0] : 0;

	boundary &= FLEXONEन_अंकD_PI_MASK;
	boundary |= lock ? 0 : (3 << FLEXONEन_अंकD_PI_UNLOCK_SHIFT);

	this->command(mtd, ONEन_अंकD_CMD_ERASE, addr, 0);
	ret = this->रुको(mtd, FL_ERASING);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed PI erase for Die %d\n",
		       __func__, die);
		जाओ out;
	पूर्ण

	this->ग_लिखो_word(boundary, this->base + ONEन_अंकD_DATARAM);
	this->command(mtd, ONEन_अंकD_CMD_PROG, addr, 0);
	ret = this->रुको(mtd, FL_WRITING);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed PI write for Die %d\n",
			__func__, die);
		जाओ out;
	पूर्ण

	this->command(mtd, FLEXONEन_अंकD_CMD_PI_UPDATE, die, 0);
	ret = this->रुको(mtd, FL_WRITING);
out:
	this->ग_लिखो_word(ONEन_अंकD_CMD_RESET, this->base + ONEन_अंकD_REG_COMMAND);
	this->रुको(mtd, FL_RESETTING);
	अगर (!ret)
		/* Recalculate device size on boundary change*/
		flexonenand_get_size(mtd);

	वापस ret;
पूर्ण

/**
 * onenand_chip_probe - [Oneन_अंकD Interface] The generic chip probe
 * @mtd:		MTD device काष्ठाure
 *
 * Oneन_अंकD detection method:
 *   Compare the values from command with ones from रेजिस्टर
 */
अटल पूर्णांक onenand_chip_probe(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक bram_maf_id, bram_dev_id, maf_id, dev_id;
	पूर्णांक syscfg;

	/* Save प्रणाली configuration 1 */
	syscfg = this->पढ़ो_word(this->base + ONEन_अंकD_REG_SYS_CFG1);
	/* Clear Sync. Burst Read mode to पढ़ो BootRAM */
	this->ग_लिखो_word((syscfg & ~ONEन_अंकD_SYS_CFG1_SYNC_READ & ~ONEन_अंकD_SYS_CFG1_SYNC_WRITE), this->base + ONEन_अंकD_REG_SYS_CFG1);

	/* Send the command क्रम पढ़ोing device ID from BootRAM */
	this->ग_लिखो_word(ONEन_अंकD_CMD_READID, this->base + ONEन_अंकD_BOOTRAM);

	/* Read manufacturer and device IDs from BootRAM */
	bram_maf_id = this->पढ़ो_word(this->base + ONEन_अंकD_BOOTRAM + 0x0);
	bram_dev_id = this->पढ़ो_word(this->base + ONEन_अंकD_BOOTRAM + 0x2);

	/* Reset Oneन_अंकD to पढ़ो शेष रेजिस्टर values */
	this->ग_लिखो_word(ONEन_अंकD_CMD_RESET, this->base + ONEन_अंकD_BOOTRAM);
	/* Wait reset */
	this->रुको(mtd, FL_RESETTING);

	/* Restore प्रणाली configuration 1 */
	this->ग_लिखो_word(syscfg, this->base + ONEन_अंकD_REG_SYS_CFG1);

	/* Check manufacturer ID */
	अगर (onenand_check_maf(bram_maf_id))
		वापस -ENXIO;

	/* Read manufacturer and device IDs from Register */
	maf_id = this->पढ़ो_word(this->base + ONEन_अंकD_REG_MANUFACTURER_ID);
	dev_id = this->पढ़ो_word(this->base + ONEन_अंकD_REG_DEVICE_ID);

	/* Check Oneन_अंकD device */
	अगर (maf_id != bram_maf_id || dev_id != bram_dev_id)
		वापस -ENXIO;

	वापस 0;
पूर्ण

/**
 * onenand_probe - [Oneन_अंकD Interface] Probe the Oneन_अंकD device
 * @mtd:		MTD device काष्ठाure
 */
अटल पूर्णांक onenand_probe(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;
	पूर्णांक dev_id, ver_id;
	पूर्णांक density;
	पूर्णांक ret;

	ret = this->chip_probe(mtd);
	अगर (ret)
		वापस ret;

	/* Device and version IDs from Register */
	dev_id = this->पढ़ो_word(this->base + ONEन_अंकD_REG_DEVICE_ID);
	ver_id = this->पढ़ो_word(this->base + ONEन_अंकD_REG_VERSION_ID);
	this->technology = this->पढ़ो_word(this->base + ONEन_अंकD_REG_TECHNOLOGY);

	/* Flash device inक्रमmation */
	onenand_prपूर्णांक_device_info(dev_id, ver_id);
	this->device_id = dev_id;
	this->version_id = ver_id;

	/* Check Oneन_अंकD features */
	onenand_check_features(mtd);

	density = onenand_get_density(dev_id);
	अगर (FLEXONEन_अंकD(this)) अणु
		this->dies = ONEन_अंकD_IS_DDP(this) ? 2 : 1;
		/* Maximum possible erase regions */
		mtd->numeraseregions = this->dies << 1;
		mtd->eraseregions =
			kसुस्मृति(this->dies << 1,
				माप(काष्ठा mtd_erase_region_info),
				GFP_KERNEL);
		अगर (!mtd->eraseregions)
			वापस -ENOMEM;
	पूर्ण

	/*
	 * For Flex-Oneन_अंकD, chipsize represents maximum possible device size.
	 * mtd->size represents the actual device size.
	 */
	this->chipsize = (16 << density) << 20;

	/* Oneन_अंकD page size & block size */
	/* The data buffer size is equal to page size */
	mtd->ग_लिखोsize = this->पढ़ो_word(this->base + ONEन_अंकD_REG_DATA_BUFFER_SIZE);
	/* We use the full BufferRAM */
	अगर (ONEन_अंकD_IS_4KB_PAGE(this))
		mtd->ग_लिखोsize <<= 1;

	mtd->oobsize = mtd->ग_लिखोsize >> 5;
	/* Pages per a block are always 64 in Oneन_अंकD */
	mtd->erasesize = mtd->ग_लिखोsize << 6;
	/*
	 * Flex-Oneन_अंकD SLC area has 64 pages per block.
	 * Flex-Oneन_अंकD MLC area has 128 pages per block.
	 * Expose MLC erase size to find erase_shअगरt and page_mask.
	 */
	अगर (FLEXONEन_अंकD(this))
		mtd->erasesize <<= 1;

	this->erase_shअगरt = ffs(mtd->erasesize) - 1;
	this->page_shअगरt = ffs(mtd->ग_लिखोsize) - 1;
	this->page_mask = (1 << (this->erase_shअगरt - this->page_shअगरt)) - 1;
	/* Set density mask. it is used क्रम DDP */
	अगर (ONEन_अंकD_IS_DDP(this))
		this->density_mask = this->chipsize >> (this->erase_shअगरt + 1);
	/* It's real page size */
	this->ग_लिखोsize = mtd->ग_लिखोsize;

	/* REVISIT: Multichip handling */

	अगर (FLEXONEन_अंकD(this))
		flexonenand_get_size(mtd);
	अन्यथा
		mtd->size = this->chipsize;

	/*
	 * We emulate the 4KiB page and 256KiB erase block size
	 * But oobsize is still 64 bytes.
	 * It is only valid अगर you turn on 2X program support,
	 * Otherwise it will be ignored by compiler.
	 */
	अगर (ONEन_अंकD_IS_2PLANE(this)) अणु
		mtd->ग_लिखोsize <<= 1;
		mtd->erasesize <<= 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * onenand_suspend - [MTD Interface] Suspend the Oneन_अंकD flash
 * @mtd:		MTD device काष्ठाure
 */
अटल पूर्णांक onenand_suspend(काष्ठा mtd_info *mtd)
अणु
	वापस onenand_get_device(mtd, FL_PM_SUSPENDED);
पूर्ण

/**
 * onenand_resume - [MTD Interface] Resume the Oneन_अंकD flash
 * @mtd:		MTD device काष्ठाure
 */
अटल व्योम onenand_resume(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;

	अगर (this->state == FL_PM_SUSPENDED)
		onenand_release_device(mtd);
	अन्यथा
		prपूर्णांकk(KERN_ERR "%s: resume() called for the chip which is not "
				"in suspended state\n", __func__);
पूर्ण

/**
 * onenand_scan - [Oneन_अंकD Interface] Scan क्रम the Oneन_अंकD device
 * @mtd:		MTD device काष्ठाure
 * @maxchips:	Number of chips to scan क्रम
 *
 * This fills out all the not initialized function poपूर्णांकers
 * with the शेषs.
 * The flash ID is पढ़ो and the mtd/chip काष्ठाures are
 * filled with the appropriate values.
 */
पूर्णांक onenand_scan(काष्ठा mtd_info *mtd, पूर्णांक maxchips)
अणु
	पूर्णांक i, ret;
	काष्ठा onenand_chip *this = mtd->priv;

	अगर (!this->पढ़ो_word)
		this->पढ़ो_word = onenand_पढ़ोw;
	अगर (!this->ग_लिखो_word)
		this->ग_लिखो_word = onenand_ग_लिखोw;

	अगर (!this->command)
		this->command = onenand_command;
	अगर (!this->रुको)
		onenand_setup_रुको(mtd);
	अगर (!this->bbt_रुको)
		this->bbt_रुको = onenand_bbt_रुको;
	अगर (!this->unlock_all)
		this->unlock_all = onenand_unlock_all;

	अगर (!this->chip_probe)
		this->chip_probe = onenand_chip_probe;

	अगर (!this->पढ़ो_bufferram)
		this->पढ़ो_bufferram = onenand_पढ़ो_bufferram;
	अगर (!this->ग_लिखो_bufferram)
		this->ग_लिखो_bufferram = onenand_ग_लिखो_bufferram;

	अगर (!this->block_markbad)
		this->block_markbad = onenand_शेष_block_markbad;
	अगर (!this->scan_bbt)
		this->scan_bbt = onenand_शेष_bbt;

	अगर (onenand_probe(mtd))
		वापस -ENXIO;

	/* Set Sync. Burst Read after probing */
	अगर (this->mmcontrol) अणु
		prपूर्णांकk(KERN_INFO "OneNAND Sync. Burst Read support\n");
		this->पढ़ो_bufferram = onenand_sync_पढ़ो_bufferram;
	पूर्ण

	/* Allocate buffers, अगर necessary */
	अगर (!this->page_buf) अणु
		this->page_buf = kzalloc(mtd->ग_लिखोsize, GFP_KERNEL);
		अगर (!this->page_buf)
			वापस -ENOMEM;
#अगर_घोषित CONFIG_MTD_ONEन_अंकD_VERIFY_WRITE
		this->verअगरy_buf = kzalloc(mtd->ग_लिखोsize, GFP_KERNEL);
		अगर (!this->verअगरy_buf) अणु
			kमुक्त(this->page_buf);
			वापस -ENOMEM;
		पूर्ण
#पूर्ण_अगर
		this->options |= ONEन_अंकD_PAGEBUF_ALLOC;
	पूर्ण
	अगर (!this->oob_buf) अणु
		this->oob_buf = kzalloc(mtd->oobsize, GFP_KERNEL);
		अगर (!this->oob_buf) अणु
			अगर (this->options & ONEन_अंकD_PAGEBUF_ALLOC) अणु
				this->options &= ~ONEन_अंकD_PAGEBUF_ALLOC;
#अगर_घोषित CONFIG_MTD_ONEन_अंकD_VERIFY_WRITE
				kमुक्त(this->verअगरy_buf);
#पूर्ण_अगर
				kमुक्त(this->page_buf);
			पूर्ण
			वापस -ENOMEM;
		पूर्ण
		this->options |= ONEन_अंकD_OOBBUF_ALLOC;
	पूर्ण

	this->state = FL_READY;
	init_रुकोqueue_head(&this->wq);
	spin_lock_init(&this->chip_lock);

	/*
	 * Allow subpage ग_लिखोs up to oobsize.
	 */
	चयन (mtd->oobsize) अणु
	हाल 128:
		अगर (FLEXONEन_अंकD(this)) अणु
			mtd_set_ooblayout(mtd, &flexonenand_ooblayout_ops);
			mtd->subpage_sft = 0;
		पूर्ण अन्यथा अणु
			mtd_set_ooblayout(mtd, &onenand_oob_128_ooblayout_ops);
			mtd->subpage_sft = 2;
		पूर्ण
		अगर (ONEन_अंकD_IS_NOP_1(this))
			mtd->subpage_sft = 0;
		अवरोध;
	हाल 64:
		mtd_set_ooblayout(mtd, &onenand_oob_32_64_ooblayout_ops);
		mtd->subpage_sft = 2;
		अवरोध;

	हाल 32:
		mtd_set_ooblayout(mtd, &onenand_oob_32_64_ooblayout_ops);
		mtd->subpage_sft = 1;
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_WARNING "%s: No OOB scheme defined for oobsize %d\n",
			__func__, mtd->oobsize);
		mtd->subpage_sft = 0;
		/* To prevent kernel oops */
		mtd_set_ooblayout(mtd, &onenand_oob_32_64_ooblayout_ops);
		अवरोध;
	पूर्ण

	this->subpagesize = mtd->ग_लिखोsize >> mtd->subpage_sft;

	/*
	 * The number of bytes available क्रम a client to place data पूर्णांकo
	 * the out of band area
	 */
	ret = mtd_ooblayout_count_मुक्तbytes(mtd);
	अगर (ret < 0)
		ret = 0;

	mtd->oobavail = ret;

	mtd->ecc_strength = 1;

	/* Fill in reमुख्यing MTD driver data */
	mtd->type = ONEन_अंकD_IS_MLC(this) ? MTD_MLCन_अंकDFLASH : MTD_न_अंकDFLASH;
	mtd->flags = MTD_CAP_न_अंकDFLASH;
	mtd->_erase = onenand_erase;
	mtd->_poपूर्णांक = शून्य;
	mtd->_unpoपूर्णांक = शून्य;
	mtd->_पढ़ो_oob = onenand_पढ़ो_oob;
	mtd->_ग_लिखो_oob = onenand_ग_लिखो_oob;
	mtd->_panic_ग_लिखो = onenand_panic_ग_लिखो;
#अगर_घोषित CONFIG_MTD_ONEन_अंकD_OTP
	mtd->_get_fact_prot_info = onenand_get_fact_prot_info;
	mtd->_पढ़ो_fact_prot_reg = onenand_पढ़ो_fact_prot_reg;
	mtd->_get_user_prot_info = onenand_get_user_prot_info;
	mtd->_पढ़ो_user_prot_reg = onenand_पढ़ो_user_prot_reg;
	mtd->_ग_लिखो_user_prot_reg = onenand_ग_लिखो_user_prot_reg;
	mtd->_lock_user_prot_reg = onenand_lock_user_prot_reg;
#पूर्ण_अगर
	mtd->_sync = onenand_sync;
	mtd->_lock = onenand_lock;
	mtd->_unlock = onenand_unlock;
	mtd->_suspend = onenand_suspend;
	mtd->_resume = onenand_resume;
	mtd->_block_isbad = onenand_block_isbad;
	mtd->_block_markbad = onenand_block_markbad;
	mtd->owner = THIS_MODULE;
	mtd->ग_लिखोbufsize = mtd->ग_लिखोsize;

	/* Unlock whole block */
	अगर (!(this->options & ONEन_अंकD_SKIP_INITIAL_UNLOCKING))
		this->unlock_all(mtd);

	/* Set the bad block marker position */
	this->badblockpos = ONEन_अंकD_BADBLOCK_POS;

	ret = this->scan_bbt(mtd);
	अगर ((!FLEXONEन_अंकD(this)) || ret)
		वापस ret;

	/* Change Flex-Oneन_अंकD boundaries अगर required */
	क्रम (i = 0; i < MAX_DIES; i++)
		flexonenand_set_boundary(mtd, i, flex_bdry[2 * i],
						 flex_bdry[(2 * i) + 1]);

	वापस 0;
पूर्ण

/**
 * onenand_release - [Oneन_अंकD Interface] Free resources held by the Oneन_अंकD device
 * @mtd:		MTD device काष्ठाure
 */
व्योम onenand_release(काष्ठा mtd_info *mtd)
अणु
	काष्ठा onenand_chip *this = mtd->priv;

	/* Deरेजिस्टर partitions */
	mtd_device_unरेजिस्टर(mtd);

	/* Free bad block table memory, अगर allocated */
	अगर (this->bbm) अणु
		काष्ठा bbm_info *bbm = this->bbm;
		kमुक्त(bbm->bbt);
		kमुक्त(this->bbm);
	पूर्ण
	/* Buffers allocated by onenand_scan */
	अगर (this->options & ONEन_अंकD_PAGEBUF_ALLOC) अणु
		kमुक्त(this->page_buf);
#अगर_घोषित CONFIG_MTD_ONEन_अंकD_VERIFY_WRITE
		kमुक्त(this->verअगरy_buf);
#पूर्ण_अगर
	पूर्ण
	अगर (this->options & ONEन_अंकD_OOBBUF_ALLOC)
		kमुक्त(this->oob_buf);
	kमुक्त(mtd->eraseregions);
पूर्ण

EXPORT_SYMBOL_GPL(onenand_scan);
EXPORT_SYMBOL_GPL(onenand_release);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kyungmin Park <kyungmin.park@samsung.com>");
MODULE_DESCRIPTION("Generic OneNAND flash driver code");
