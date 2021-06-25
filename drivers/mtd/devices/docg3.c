<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Handles the M-Systems DiskOnChip G3 chip
 *
 * Copyright (C) 2011 Robert Jarzmik
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/bch.h>

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश "docg3.h"

/*
 * This driver handles the DiskOnChip G3 flash memory.
 *
 * As no specअगरication is available from M-Systems/Sandisk, this drivers lacks
 * several functions available on the chip, as :
 *  - IPL ग_लिखो
 *
 * The bus data width (8bits versus 16bits) is not handled (अगर_cfg flag), and
 * the driver assumes a 16bits data bus.
 *
 * DocG3 relies on 2 ECC algorithms, which are handled in hardware :
 *  - a 1 byte Hamming code stored in the OOB क्रम each page
 *  - a 7 bytes BCH code stored in the OOB क्रम each page
 * The BCH ECC is :
 *  - BCH is in GF(2^14)
 *  - BCH is over data of 520 bytes (512 page + 7 page_info bytes
 *                                   + 1 hamming byte)
 *  - BCH can correct up to 4 bits (t = 4)
 *  - BCH syndroms are calculated in hardware, and checked in hardware as well
 *
 */

अटल अचिन्हित पूर्णांक reliable_mode;
module_param(reliable_mode, uपूर्णांक, 0);
MODULE_PARM_DESC(reliable_mode, "Set the docg3 mode (0=normal MLC, 1=fast, "
		 "2=reliable) : MLC normal operations are in normal mode");

अटल पूर्णांक करोcg3_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
			       काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section)
		वापस -दुस्फल;

	/* byte 7 is Hamming ECC, byte 8-14 are BCH ECC */
	oobregion->offset = 7;
	oobregion->length = 8;

	वापस 0;
पूर्ण

अटल पूर्णांक करोcg3_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section > 1)
		वापस -दुस्फल;

	/* मुक्त bytes: byte 0 until byte 6, byte 15 */
	अगर (!section) अणु
		oobregion->offset = 0;
		oobregion->length = 7;
	पूर्ण अन्यथा अणु
		oobregion->offset = 15;
		oobregion->length = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops nand_ooblayout_करोcg3_ops = अणु
	.ecc = करोcg3_ooblayout_ecc,
	.मुक्त = करोcg3_ooblayout_मुक्त,
पूर्ण;

अटल अंतरभूत u8 करोc_पढ़ोb(काष्ठा करोcg3 *करोcg3, u16 reg)
अणु
	u8 val = पढ़ोb(करोcg3->cascade->base + reg);

	trace_करोcg3_io(0, 8, reg, (पूर्णांक)val);
	वापस val;
पूर्ण

अटल अंतरभूत u16 करोc_पढ़ोw(काष्ठा करोcg3 *करोcg3, u16 reg)
अणु
	u16 val = पढ़ोw(करोcg3->cascade->base + reg);

	trace_करोcg3_io(0, 16, reg, (पूर्णांक)val);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम करोc_ग_लिखोb(काष्ठा करोcg3 *करोcg3, u8 val, u16 reg)
अणु
	ग_लिखोb(val, करोcg3->cascade->base + reg);
	trace_करोcg3_io(1, 8, reg, val);
पूर्ण

अटल अंतरभूत व्योम करोc_ग_लिखोw(काष्ठा करोcg3 *करोcg3, u16 val, u16 reg)
अणु
	ग_लिखोw(val, करोcg3->cascade->base + reg);
	trace_करोcg3_io(1, 16, reg, val);
पूर्ण

अटल अंतरभूत व्योम करोc_flash_command(काष्ठा करोcg3 *करोcg3, u8 cmd)
अणु
	करोc_ग_लिखोb(करोcg3, cmd, DOC_FLASHCOMMAND);
पूर्ण

अटल अंतरभूत व्योम करोc_flash_sequence(काष्ठा करोcg3 *करोcg3, u8 seq)
अणु
	करोc_ग_लिखोb(करोcg3, seq, DOC_FLASHSEQUENCE);
पूर्ण

अटल अंतरभूत व्योम करोc_flash_address(काष्ठा करोcg3 *करोcg3, u8 addr)
अणु
	करोc_ग_लिखोb(करोcg3, addr, DOC_FLASHADDRESS);
पूर्ण

अटल अक्षर स्थिर * स्थिर part_probes[] = अणु "cmdlinepart", "saftlpart", शून्य पूर्ण;

अटल पूर्णांक करोc_रेजिस्टर_पढ़ोb(काष्ठा करोcg3 *करोcg3, पूर्णांक reg)
अणु
	u8 val;

	करोc_ग_लिखोw(करोcg3, reg, DOC_READADDRESS);
	val = करोc_पढ़ोb(करोcg3, reg);
	करोc_vdbg("Read register %04x : %02x\n", reg, val);
	वापस val;
पूर्ण

अटल पूर्णांक करोc_रेजिस्टर_पढ़ोw(काष्ठा करोcg3 *करोcg3, पूर्णांक reg)
अणु
	u16 val;

	करोc_ग_लिखोw(करोcg3, reg, DOC_READADDRESS);
	val = करोc_पढ़ोw(करोcg3, reg);
	करोc_vdbg("Read register %04x : %04x\n", reg, val);
	वापस val;
पूर्ण

/**
 * करोc_delay - delay करोcg3 operations
 * @करोcg3: the device
 * @nbNOPs: the number of NOPs to issue
 *
 * As no specअगरication is available, the right timings between chip commands are
 * unknown. The only available piece of inक्रमmation are the observed nops on a
 * working करोcg3 chip.
 * Thereक्रमe, करोc_delay relies on a busy loop of NOPs, instead of scheduler
 * मित्रlier msleep() functions or blocking mdelay().
 */
अटल व्योम करोc_delay(काष्ठा करोcg3 *करोcg3, पूर्णांक nbNOPs)
अणु
	पूर्णांक i;

	करोc_vdbg("NOP x %d\n", nbNOPs);
	क्रम (i = 0; i < nbNOPs; i++)
		करोc_ग_लिखोb(करोcg3, 0, DOC_NOP);
पूर्ण

अटल पूर्णांक is_prot_seq_error(काष्ठा करोcg3 *करोcg3)
अणु
	पूर्णांक ctrl;

	ctrl = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_FLASHCONTROL);
	वापस ctrl & (DOC_CTRL_PROTECTION_ERROR | DOC_CTRL_SEQUENCE_ERROR);
पूर्ण

अटल पूर्णांक करोc_is_पढ़ोy(काष्ठा करोcg3 *करोcg3)
अणु
	पूर्णांक ctrl;

	ctrl = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_FLASHCONTROL);
	वापस ctrl & DOC_CTRL_FLASHREADY;
पूर्ण

अटल पूर्णांक करोc_रुको_पढ़ोy(काष्ठा करोcg3 *करोcg3)
अणु
	पूर्णांक maxWaitCycles = 100;

	करो अणु
		करोc_delay(करोcg3, 4);
		cpu_relax();
	पूर्ण जबतक (!करोc_is_पढ़ोy(करोcg3) && maxWaitCycles--);
	करोc_delay(करोcg3, 2);
	अगर (maxWaitCycles > 0)
		वापस 0;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल पूर्णांक करोc_reset_seq(काष्ठा करोcg3 *करोcg3)
अणु
	पूर्णांक ret;

	करोc_ग_लिखोb(करोcg3, 0x10, DOC_FLASHCONTROL);
	करोc_flash_sequence(करोcg3, DOC_SEQ_RESET);
	करोc_flash_command(करोcg3, DOC_CMD_RESET);
	करोc_delay(करोcg3, 2);
	ret = करोc_रुको_पढ़ोy(करोcg3);

	करोc_dbg("doc_reset_seq() -> isReady=%s\n", ret ? "false" : "true");
	वापस ret;
पूर्ण

/**
 * करोc_पढ़ो_data_area - Read data from data area
 * @करोcg3: the device
 * @buf: the buffer to fill in (might be शून्य is dummy पढ़ोs)
 * @len: the length to पढ़ो
 * @first: first समय पढ़ो, DOC_READADDRESS should be set
 *
 * Reads bytes from flash data. Handles the single byte / even bytes पढ़ोs.
 */
अटल व्योम करोc_पढ़ो_data_area(काष्ठा करोcg3 *करोcg3, व्योम *buf, पूर्णांक len,
			       पूर्णांक first)
अणु
	पूर्णांक i, cdr, len4;
	u16 data16, *dst16;
	u8 data8, *dst8;

	करोc_dbg("doc_read_data_area(buf=%p, len=%d)\n", buf, len);
	cdr = len & 0x1;
	len4 = len - cdr;

	अगर (first)
		करोc_ग_लिखोw(करोcg3, DOC_IOSPACE_DATA, DOC_READADDRESS);
	dst16 = buf;
	क्रम (i = 0; i < len4; i += 2) अणु
		data16 = करोc_पढ़ोw(करोcg3, DOC_IOSPACE_DATA);
		अगर (dst16) अणु
			*dst16 = data16;
			dst16++;
		पूर्ण
	पूर्ण

	अगर (cdr) अणु
		करोc_ग_लिखोw(करोcg3, DOC_IOSPACE_DATA | DOC_READADDR_ONE_BYTE,
			   DOC_READADDRESS);
		करोc_delay(करोcg3, 1);
		dst8 = (u8 *)dst16;
		क्रम (i = 0; i < cdr; i++) अणु
			data8 = करोc_पढ़ोb(करोcg3, DOC_IOSPACE_DATA);
			अगर (dst8) अणु
				*dst8 = data8;
				dst8++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * करोc_ग_लिखो_data_area - Write data पूर्णांकo data area
 * @करोcg3: the device
 * @buf: the buffer to get input bytes from
 * @len: the length to ग_लिखो
 *
 * Writes bytes पूर्णांकo flash data. Handles the single byte / even bytes ग_लिखोs.
 */
अटल व्योम करोc_ग_लिखो_data_area(काष्ठा करोcg3 *करोcg3, स्थिर व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक i, cdr, len4;
	u16 *src16;
	u8 *src8;

	करोc_dbg("doc_write_data_area(buf=%p, len=%d)\n", buf, len);
	cdr = len & 0x3;
	len4 = len - cdr;

	करोc_ग_लिखोw(करोcg3, DOC_IOSPACE_DATA, DOC_READADDRESS);
	src16 = (u16 *)buf;
	क्रम (i = 0; i < len4; i += 2) अणु
		करोc_ग_लिखोw(करोcg3, *src16, DOC_IOSPACE_DATA);
		src16++;
	पूर्ण

	src8 = (u8 *)src16;
	क्रम (i = 0; i < cdr; i++) अणु
		करोc_ग_लिखोw(करोcg3, DOC_IOSPACE_DATA | DOC_READADDR_ONE_BYTE,
			   DOC_READADDRESS);
		करोc_ग_लिखोb(करोcg3, *src8, DOC_IOSPACE_DATA);
		src8++;
	पूर्ण
पूर्ण

/**
 * करोc_set_data_mode - Sets the flash to normal or reliable data mode
 * @करोcg3: the device
 *
 * The reliable data mode is a bit slower than the fast mode, but less errors
 * occur.  Entering the reliable mode cannot be करोne without entering the fast
 * mode first.
 *
 * In reliable mode, pages 2*n and 2*n+1 are clones. Writing to page 0 of blocks
 * (4,5) make the hardware ग_लिखो also to page 1 of blocks blocks(4,5). Reading
 * from page 0 of blocks (4,5) or from page 1 of blocks (4,5) gives the same
 * result, which is a logical and between bytes from page 0 and page 1 (which is
 * consistent with the fact that writing to a page is _clearing_ bits of that
 * page).
 */
अटल व्योम करोc_set_reliable_mode(काष्ठा करोcg3 *करोcg3)
अणु
	अटल अक्षर *strmode[] = अणु "normal", "fast", "reliable", "invalid" पूर्ण;

	करोc_dbg("doc_set_reliable_mode(%s)\n", strmode[करोcg3->reliable]);
	चयन (करोcg3->reliable) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		करोc_flash_sequence(करोcg3, DOC_SEQ_SET_FASTMODE);
		करोc_flash_command(करोcg3, DOC_CMD_FAST_MODE);
		अवरोध;
	हाल 2:
		करोc_flash_sequence(करोcg3, DOC_SEQ_SET_RELIABLEMODE);
		करोc_flash_command(करोcg3, DOC_CMD_FAST_MODE);
		करोc_flash_command(करोcg3, DOC_CMD_RELIABLE_MODE);
		अवरोध;
	शेष:
		करोc_err("doc_set_reliable_mode(): invalid mode\n");
		अवरोध;
	पूर्ण
	करोc_delay(करोcg3, 2);
पूर्ण

/**
 * करोc_set_asic_mode - Set the ASIC mode
 * @करोcg3: the device
 * @mode: the mode
 *
 * The ASIC can work in 3 modes :
 *  - RESET: all रेजिस्टरs are zeroed
 *  - NORMAL: receives and handles commands
 *  - POWERDOWN: minimal घातeruse, flash parts shut off
 */
अटल व्योम करोc_set_asic_mode(काष्ठा करोcg3 *करोcg3, u8 mode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 12; i++)
		करोc_पढ़ोb(करोcg3, DOC_IOSPACE_IPL);

	mode |= DOC_ASICMODE_MDWREN;
	करोc_dbg("doc_set_asic_mode(%02x)\n", mode);
	करोc_ग_लिखोb(करोcg3, mode, DOC_ASICMODE);
	करोc_ग_लिखोb(करोcg3, ~mode, DOC_ASICMODECONFIRM);
	करोc_delay(करोcg3, 1);
पूर्ण

/**
 * करोc_set_device_id - Sets the devices id क्रम cascaded G3 chips
 * @करोcg3: the device
 * @id: the chip to select (amongst 0, 1, 2, 3)
 *
 * There can be 4 cascaded G3 chips. This function selects the one which will
 * should be the active one.
 */
अटल व्योम करोc_set_device_id(काष्ठा करोcg3 *करोcg3, पूर्णांक id)
अणु
	u8 ctrl;

	करोc_dbg("doc_set_device_id(%d)\n", id);
	करोc_ग_लिखोb(करोcg3, id, DOC_DEVICESELECT);
	ctrl = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_FLASHCONTROL);

	ctrl &= ~DOC_CTRL_VIOLATION;
	ctrl |= DOC_CTRL_CE;
	करोc_ग_लिखोb(करोcg3, ctrl, DOC_FLASHCONTROL);
पूर्ण

/**
 * करोc_set_extra_page_mode - Change flash page layout
 * @करोcg3: the device
 *
 * Normally, the flash page is split पूर्णांकo the data (512 bytes) and the out of
 * band data (16 bytes). For each, 4 more bytes can be accessed, where the wear
 * leveling counters are stored.  To access this last area of 4 bytes, a special
 * mode must be input to the flash ASIC.
 *
 * Returns 0 अगर no error occurred, -EIO अन्यथा.
 */
अटल पूर्णांक करोc_set_extra_page_mode(काष्ठा करोcg3 *करोcg3)
अणु
	पूर्णांक fctrl;

	करोc_dbg("doc_set_extra_page_mode()\n");
	करोc_flash_sequence(करोcg3, DOC_SEQ_PAGE_SIZE_532);
	करोc_flash_command(करोcg3, DOC_CMD_PAGE_SIZE_532);
	करोc_delay(करोcg3, 2);

	fctrl = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_FLASHCONTROL);
	अगर (fctrl & (DOC_CTRL_PROTECTION_ERROR | DOC_CTRL_SEQUENCE_ERROR))
		वापस -EIO;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * करोc_setup_addr_sector - Setup blocks/page/ofs address क्रम one plane
 * @करोcg3: the device
 * @sector: the sector
 */
अटल व्योम करोc_setup_addr_sector(काष्ठा करोcg3 *करोcg3, पूर्णांक sector)
अणु
	करोc_delay(करोcg3, 1);
	करोc_flash_address(करोcg3, sector & 0xff);
	करोc_flash_address(करोcg3, (sector >> 8) & 0xff);
	करोc_flash_address(करोcg3, (sector >> 16) & 0xff);
	करोc_delay(करोcg3, 1);
पूर्ण

/**
 * करोc_setup_ग_लिखोaddr_sector - Setup blocks/page/ofs address क्रम one plane
 * @करोcg3: the device
 * @sector: the sector
 * @ofs: the offset in the page, between 0 and (512 + 16 + 512)
 */
अटल व्योम करोc_setup_ग_लिखोaddr_sector(काष्ठा करोcg3 *करोcg3, पूर्णांक sector, पूर्णांक ofs)
अणु
	ofs = ofs >> 2;
	करोc_delay(करोcg3, 1);
	करोc_flash_address(करोcg3, ofs & 0xff);
	करोc_flash_address(करोcg3, sector & 0xff);
	करोc_flash_address(करोcg3, (sector >> 8) & 0xff);
	करोc_flash_address(करोcg3, (sector >> 16) & 0xff);
	करोc_delay(करोcg3, 1);
पूर्ण

/**
 * करोc_seek - Set both flash planes to the specअगरied block, page क्रम पढ़ोing
 * @करोcg3: the device
 * @block0: the first plane block index
 * @block1: the second plane block index
 * @page: the page index within the block
 * @wear: अगर true, पढ़ो will occur on the 4 extra bytes of the wear area
 * @ofs: offset in page to पढ़ो
 *
 * Programs the flash even and odd planes to the specअगरic block and page.
 * Alternatively, programs the flash to the wear area of the specअगरied page.
 */
अटल पूर्णांक करोc_पढ़ो_seek(काष्ठा करोcg3 *करोcg3, पूर्णांक block0, पूर्णांक block1, पूर्णांक page,
			 पूर्णांक wear, पूर्णांक ofs)
अणु
	पूर्णांक sector, ret = 0;

	करोc_dbg("doc_seek(blocks=(%d,%d), page=%d, ofs=%d, wear=%d)\n",
		block0, block1, page, ofs, wear);

	अगर (!wear && (ofs < 2 * DOC_LAYOUT_PAGE_SIZE)) अणु
		करोc_flash_sequence(करोcg3, DOC_SEQ_SET_PLANE1);
		करोc_flash_command(करोcg3, DOC_CMD_READ_PLANE1);
		करोc_delay(करोcg3, 2);
	पूर्ण अन्यथा अणु
		करोc_flash_sequence(करोcg3, DOC_SEQ_SET_PLANE2);
		करोc_flash_command(करोcg3, DOC_CMD_READ_PLANE2);
		करोc_delay(करोcg3, 2);
	पूर्ण

	करोc_set_reliable_mode(करोcg3);
	अगर (wear)
		ret = करोc_set_extra_page_mode(करोcg3);
	अगर (ret)
		जाओ out;

	करोc_flash_sequence(करोcg3, DOC_SEQ_READ);
	sector = (block0 << DOC_ADDR_BLOCK_SHIFT) + (page & DOC_ADDR_PAGE_MASK);
	करोc_flash_command(करोcg3, DOC_CMD_PROG_BLOCK_ADDR);
	करोc_setup_addr_sector(करोcg3, sector);

	sector = (block1 << DOC_ADDR_BLOCK_SHIFT) + (page & DOC_ADDR_PAGE_MASK);
	करोc_flash_command(करोcg3, DOC_CMD_PROG_BLOCK_ADDR);
	करोc_setup_addr_sector(करोcg3, sector);
	करोc_delay(करोcg3, 1);

out:
	वापस ret;
पूर्ण

/**
 * करोc_ग_लिखो_seek - Set both flash planes to the specअगरied block, page क्रम writing
 * @करोcg3: the device
 * @block0: the first plane block index
 * @block1: the second plane block index
 * @page: the page index within the block
 * @ofs: offset in page to ग_लिखो
 *
 * Programs the flash even and odd planes to the specअगरic block and page.
 * Alternatively, programs the flash to the wear area of the specअगरied page.
 */
अटल पूर्णांक करोc_ग_लिखो_seek(काष्ठा करोcg3 *करोcg3, पूर्णांक block0, पूर्णांक block1, पूर्णांक page,
			 पूर्णांक ofs)
अणु
	पूर्णांक ret = 0, sector;

	करोc_dbg("doc_write_seek(blocks=(%d,%d), page=%d, ofs=%d)\n",
		block0, block1, page, ofs);

	करोc_set_reliable_mode(करोcg3);

	अगर (ofs < 2 * DOC_LAYOUT_PAGE_SIZE) अणु
		करोc_flash_sequence(करोcg3, DOC_SEQ_SET_PLANE1);
		करोc_flash_command(करोcg3, DOC_CMD_READ_PLANE1);
		करोc_delay(करोcg3, 2);
	पूर्ण अन्यथा अणु
		करोc_flash_sequence(करोcg3, DOC_SEQ_SET_PLANE2);
		करोc_flash_command(करोcg3, DOC_CMD_READ_PLANE2);
		करोc_delay(करोcg3, 2);
	पूर्ण

	करोc_flash_sequence(करोcg3, DOC_SEQ_PAGE_SETUP);
	करोc_flash_command(करोcg3, DOC_CMD_PROG_CYCLE1);

	sector = (block0 << DOC_ADDR_BLOCK_SHIFT) + (page & DOC_ADDR_PAGE_MASK);
	करोc_setup_ग_लिखोaddr_sector(करोcg3, sector, ofs);

	करोc_flash_command(करोcg3, DOC_CMD_PROG_CYCLE3);
	करोc_delay(करोcg3, 2);
	ret = करोc_रुको_पढ़ोy(करोcg3);
	अगर (ret)
		जाओ out;

	करोc_flash_command(करोcg3, DOC_CMD_PROG_CYCLE1);
	sector = (block1 << DOC_ADDR_BLOCK_SHIFT) + (page & DOC_ADDR_PAGE_MASK);
	करोc_setup_ग_लिखोaddr_sector(करोcg3, sector, ofs);
	करोc_delay(करोcg3, 1);

out:
	वापस ret;
पूर्ण


/**
 * करोc_पढ़ो_page_ecc_init - Initialize hardware ECC engine
 * @करोcg3: the device
 * @len: the number of bytes covered by the ECC (BCH covered)
 *
 * The function करोes initialize the hardware ECC engine to compute the Hamming
 * ECC (on 1 byte) and the BCH hardware ECC (on 7 bytes).
 *
 * Return 0 अगर succeeded, -EIO on error
 */
अटल पूर्णांक करोc_पढ़ो_page_ecc_init(काष्ठा करोcg3 *करोcg3, पूर्णांक len)
अणु
	करोc_ग_लिखोw(करोcg3, DOC_ECCCONF0_READ_MODE
		   | DOC_ECCCONF0_BCH_ENABLE | DOC_ECCCONF0_HAMMING_ENABLE
		   | (len & DOC_ECCCONF0_DATA_BYTES_MASK),
		   DOC_ECCCONF0);
	करोc_delay(करोcg3, 4);
	करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_FLASHCONTROL);
	वापस करोc_रुको_पढ़ोy(करोcg3);
पूर्ण

/**
 * करोc_ग_लिखो_page_ecc_init - Initialize hardware BCH ECC engine
 * @करोcg3: the device
 * @len: the number of bytes covered by the ECC (BCH covered)
 *
 * The function करोes initialize the hardware ECC engine to compute the Hamming
 * ECC (on 1 byte) and the BCH hardware ECC (on 7 bytes).
 *
 * Return 0 अगर succeeded, -EIO on error
 */
अटल पूर्णांक करोc_ग_लिखो_page_ecc_init(काष्ठा करोcg3 *करोcg3, पूर्णांक len)
अणु
	करोc_ग_लिखोw(करोcg3, DOC_ECCCONF0_WRITE_MODE
		   | DOC_ECCCONF0_BCH_ENABLE | DOC_ECCCONF0_HAMMING_ENABLE
		   | (len & DOC_ECCCONF0_DATA_BYTES_MASK),
		   DOC_ECCCONF0);
	करोc_delay(करोcg3, 4);
	करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_FLASHCONTROL);
	वापस करोc_रुको_पढ़ोy(करोcg3);
पूर्ण

/**
 * करोc_ecc_disable - Disable Hamming and BCH ECC hardware calculator
 * @करोcg3: the device
 *
 * Disables the hardware ECC generator and checker, क्रम unchecked पढ़ोs (as when
 * पढ़ोing OOB only or ग_लिखो status byte).
 */
अटल व्योम करोc_ecc_disable(काष्ठा करोcg3 *करोcg3)
अणु
	करोc_ग_लिखोw(करोcg3, DOC_ECCCONF0_READ_MODE, DOC_ECCCONF0);
	करोc_delay(करोcg3, 4);
पूर्ण

/**
 * करोc_hamming_ecc_init - Initialize hardware Hamming ECC engine
 * @करोcg3: the device
 * @nb_bytes: the number of bytes covered by the ECC (Hamming covered)
 *
 * This function programs the ECC hardware to compute the hamming code on the
 * last provided N bytes to the hardware generator.
 */
अटल व्योम करोc_hamming_ecc_init(काष्ठा करोcg3 *करोcg3, पूर्णांक nb_bytes)
अणु
	u8 ecc_conf1;

	ecc_conf1 = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_ECCCONF1);
	ecc_conf1 &= ~DOC_ECCCONF1_HAMMING_BITS_MASK;
	ecc_conf1 |= (nb_bytes & DOC_ECCCONF1_HAMMING_BITS_MASK);
	करोc_ग_लिखोb(करोcg3, ecc_conf1, DOC_ECCCONF1);
पूर्ण

/**
 * करोc_ecc_bch_fix_data - Fix अगर need be पढ़ो data from flash
 * @करोcg3: the device
 * @buf: the buffer of पढ़ो data (512 + 7 + 1 bytes)
 * @hwecc: the hardware calculated ECC.
 *         It's in fact recv_ecc ^ calc_ecc, where recv_ecc was पढ़ो from OOB
 *         area data, and calc_ecc the ECC calculated by the hardware generator.
 *
 * Checks अगर the received data matches the ECC, and अगर an error is detected,
 * tries to fix the bit flips (at most 4) in the buffer buf.  As the करोcg3
 * understands the (data, ecc, syndroms) in an inverted order in comparison to
 * the BCH library, the function reverses the order of bits (ie. bit7 and bit0,
 * bit6 and bit 1, ...) क्रम all ECC data.
 *
 * The hardware ecc unit produces oob_ecc ^ calc_ecc.  The kernel's bch
 * algorithm is used to decode this.  However the hw operates on page
 * data in a bit order that is the reverse of that of the bch alg,
 * requiring that the bits be reversed on the result.  Thanks to Ivan
 * Djelic क्रम his analysis.
 *
 * Returns number of fixed bits (0, 1, 2, 3, 4) or -EBADMSG अगर too many bit
 * errors were detected and cannot be fixed.
 */
अटल पूर्णांक करोc_ecc_bch_fix_data(काष्ठा करोcg3 *करोcg3, व्योम *buf, u8 *hwecc)
अणु
	u8 ecc[DOC_ECC_BCH_SIZE];
	पूर्णांक errorpos[DOC_ECC_BCH_T], i, numerrs;

	क्रम (i = 0; i < DOC_ECC_BCH_SIZE; i++)
		ecc[i] = bitrev8(hwecc[i]);
	numerrs = bch_decode(करोcg3->cascade->bch, शून्य,
			     DOC_ECC_BCH_COVERED_BYTES,
			     शून्य, ecc, शून्य, errorpos);
	BUG_ON(numerrs == -EINVAL);
	अगर (numerrs < 0)
		जाओ out;

	क्रम (i = 0; i < numerrs; i++)
		errorpos[i] = (errorpos[i] & ~7) | (7 - (errorpos[i] & 7));
	क्रम (i = 0; i < numerrs; i++)
		अगर (errorpos[i] < DOC_ECC_BCH_COVERED_BYTES*8)
			/* error is located in data, correct it */
			change_bit(errorpos[i], buf);
out:
	करोc_dbg("doc_ecc_bch_fix_data: flipped %d bits\n", numerrs);
	वापस numerrs;
पूर्ण


/**
 * करोc_पढ़ो_page_prepare - Prepares पढ़ोing data from a flash page
 * @करोcg3: the device
 * @block0: the first plane block index on flash memory
 * @block1: the second plane block index on flash memory
 * @page: the page index in the block
 * @offset: the offset in the page (must be a multiple of 4)
 *
 * Prepares the page to be पढ़ो in the flash memory :
 *   - tell ASIC to map the flash pages
 *   - tell ASIC to be in पढ़ो mode
 *
 * After a call to this method, a call to करोc_पढ़ो_page_finish is mandatory,
 * to end the पढ़ो cycle of the flash.
 *
 * Read data from a flash page. The length to be पढ़ो must be between 0 and
 * (page_size + oob_size + wear_size), ie. 532, and a multiple of 4 (because
 * the extra bytes पढ़ोing is not implemented).
 *
 * As pages are grouped by 2 (in 2 planes), पढ़ोing from a page must be करोne
 * in two steps:
 *  - one पढ़ो of 512 bytes at offset 0
 *  - one पढ़ो of 512 bytes at offset 512 + 16
 *
 * Returns 0 अगर successful, -EIO अगर a पढ़ो error occurred.
 */
अटल पूर्णांक करोc_पढ़ो_page_prepare(काष्ठा करोcg3 *करोcg3, पूर्णांक block0, पूर्णांक block1,
				 पूर्णांक page, पूर्णांक offset)
अणु
	पूर्णांक wear_area = 0, ret = 0;

	करोc_dbg("doc_read_page_prepare(blocks=(%d,%d), page=%d, ofsInPage=%d)\n",
		block0, block1, page, offset);
	अगर (offset >= DOC_LAYOUT_WEAR_OFFSET)
		wear_area = 1;
	अगर (!wear_area && offset > (DOC_LAYOUT_PAGE_OOB_SIZE * 2))
		वापस -EINVAL;

	करोc_set_device_id(करोcg3, करोcg3->device_id);
	ret = करोc_reset_seq(करोcg3);
	अगर (ret)
		जाओ err;

	/* Program the flash address block and page */
	ret = करोc_पढ़ो_seek(करोcg3, block0, block1, page, wear_area, offset);
	अगर (ret)
		जाओ err;

	करोc_flash_command(करोcg3, DOC_CMD_READ_ALL_PLANES);
	करोc_delay(करोcg3, 2);
	करोc_रुको_पढ़ोy(करोcg3);

	करोc_flash_command(करोcg3, DOC_CMD_SET_ADDR_READ);
	करोc_delay(करोcg3, 1);
	अगर (offset >= DOC_LAYOUT_PAGE_SIZE * 2)
		offset -= 2 * DOC_LAYOUT_PAGE_SIZE;
	करोc_flash_address(करोcg3, offset >> 2);
	करोc_delay(करोcg3, 1);
	करोc_रुको_पढ़ोy(करोcg3);

	करोc_flash_command(करोcg3, DOC_CMD_READ_FLASH);

	वापस 0;
err:
	करोc_ग_लिखोb(करोcg3, 0, DOC_DATAEND);
	करोc_delay(करोcg3, 2);
	वापस -EIO;
पूर्ण

/**
 * करोc_पढ़ो_page_getbytes - Reads bytes from a prepared page
 * @करोcg3: the device
 * @len: the number of bytes to be पढ़ो (must be a multiple of 4)
 * @buf: the buffer to be filled in (or शून्य is क्रमget bytes)
 * @first: 1 अगर first समय पढ़ो, DOC_READADDRESS should be set
 * @last_odd: 1 अगर last पढ़ो ended up on an odd byte
 *
 * Reads bytes from a prepared page. There is a trickery here : अगर the last पढ़ो
 * ended up on an odd offset in the 1024 bytes द्विगुन page, ie. between the 2
 * planes, the first byte must be पढ़ो apart. If a word (16bit) पढ़ो was used,
 * the पढ़ो would वापस the byte of plane 2 as low *and* high endian, which
 * will mess the पढ़ो.
 *
 */
अटल पूर्णांक करोc_पढ़ो_page_getbytes(काष्ठा करोcg3 *करोcg3, पूर्णांक len, u_अक्षर *buf,
				  पूर्णांक first, पूर्णांक last_odd)
अणु
	अगर (last_odd && len > 0) अणु
		करोc_पढ़ो_data_area(करोcg3, buf, 1, first);
		करोc_पढ़ो_data_area(करोcg3, buf ? buf + 1 : buf, len - 1, 0);
	पूर्ण अन्यथा अणु
		करोc_पढ़ो_data_area(करोcg3, buf, len, first);
	पूर्ण
	करोc_delay(करोcg3, 2);
	वापस len;
पूर्ण

/**
 * करोc_ग_लिखो_page_putbytes - Writes bytes पूर्णांकo a prepared page
 * @करोcg3: the device
 * @len: the number of bytes to be written
 * @buf: the buffer of input bytes
 *
 */
अटल व्योम करोc_ग_लिखो_page_putbytes(काष्ठा करोcg3 *करोcg3, पूर्णांक len,
				    स्थिर u_अक्षर *buf)
अणु
	करोc_ग_लिखो_data_area(करोcg3, buf, len);
	करोc_delay(करोcg3, 2);
पूर्ण

/**
 * करोc_get_bch_hw_ecc - Get hardware calculated BCH ECC
 * @करोcg3: the device
 * @hwecc:  the array of 7 पूर्णांकegers where the hardware ecc will be stored
 */
अटल व्योम करोc_get_bch_hw_ecc(काष्ठा करोcg3 *करोcg3, u8 *hwecc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DOC_ECC_BCH_SIZE; i++)
		hwecc[i] = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_BCH_HW_ECC(i));
पूर्ण

/**
 * करोc_page_finish - Ends पढ़ोing/writing of a flash page
 * @करोcg3: the device
 */
अटल व्योम करोc_page_finish(काष्ठा करोcg3 *करोcg3)
अणु
	करोc_ग_लिखोb(करोcg3, 0, DOC_DATAEND);
	करोc_delay(करोcg3, 2);
पूर्ण

/**
 * करोc_पढ़ो_page_finish - Ends पढ़ोing of a flash page
 * @करोcg3: the device
 *
 * As a side effect, resets the chip selector to 0. This ensures that after each
 * पढ़ो operation, the न्यूनमान 0 is selected. Thereक्रमe, अगर the प्रणालीs halts, the
 * reboot will boot on न्यूनमान 0, where the IPL is.
 */
अटल व्योम करोc_पढ़ो_page_finish(काष्ठा करोcg3 *करोcg3)
अणु
	करोc_page_finish(करोcg3);
	करोc_set_device_id(करोcg3, 0);
पूर्ण

/**
 * calc_block_sector - Calculate blocks, pages and ofs.
 *
 * @from: offset in flash
 * @block0: first plane block index calculated
 * @block1: second plane block index calculated
 * @page: page calculated
 * @ofs: offset in page
 * @reliable: 0 अगर करोcg3 in normal mode, 1 अगर करोcg3 in fast mode, 2 अगर करोcg3 in
 * reliable mode.
 *
 * The calculation is based on the reliable/normal mode. In normal mode, the 64
 * pages of a block are available. In reliable mode, as pages 2*n and 2*n+1 are
 * clones, only 32 pages per block are available.
 */
अटल व्योम calc_block_sector(loff_t from, पूर्णांक *block0, पूर्णांक *block1, पूर्णांक *page,
			      पूर्णांक *ofs, पूर्णांक reliable)
अणु
	uपूर्णांक sector, pages_biblock;

	pages_biblock = DOC_LAYOUT_PAGES_PER_BLOCK * DOC_LAYOUT_NBPLANES;
	अगर (reliable == 1 || reliable == 2)
		pages_biblock /= 2;

	sector = from / DOC_LAYOUT_PAGE_SIZE;
	*block0 = sector / pages_biblock * DOC_LAYOUT_NBPLANES;
	*block1 = *block0 + 1;
	*page = sector % pages_biblock;
	*page /= DOC_LAYOUT_NBPLANES;
	अगर (reliable == 1 || reliable == 2)
		*page *= 2;
	अगर (sector % 2)
		*ofs = DOC_LAYOUT_PAGE_OOB_SIZE;
	अन्यथा
		*ofs = 0;
पूर्ण

/**
 * करोc_पढ़ो_oob - Read out of band bytes from flash
 * @mtd: the device
 * @from: the offset from first block and first page, in bytes, aligned on page
 *        size
 * @ops: the mtd oob काष्ठाure
 *
 * Reads flash memory OOB area of pages.
 *
 * Returns 0 अगर पढ़ो successful, of -EIO, -EINVAL अगर an error occurred
 */
अटल पूर्णांक करोc_पढ़ो_oob(काष्ठा mtd_info *mtd, loff_t from,
			काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा करोcg3 *करोcg3 = mtd->priv;
	पूर्णांक block0, block1, page, ret, skip, ofs = 0;
	u8 *oobbuf = ops->oobbuf;
	u8 *buf = ops->datbuf;
	माप_प्रकार len, ooblen, nbdata, nboob;
	u8 hwecc[DOC_ECC_BCH_SIZE], eccconf1;
	पूर्णांक max_bitflips = 0;

	अगर (buf)
		len = ops->len;
	अन्यथा
		len = 0;
	अगर (oobbuf)
		ooblen = ops->ooblen;
	अन्यथा
		ooblen = 0;

	अगर (oobbuf && ops->mode == MTD_OPS_PLACE_OOB)
		oobbuf += ops->ooboffs;

	करोc_dbg("doc_read_oob(from=%lld, mode=%d, data=(%p:%zu), oob=(%p:%zu))\n",
		from, ops->mode, buf, len, oobbuf, ooblen);
	अगर (ooblen % DOC_LAYOUT_OOB_SIZE)
		वापस -EINVAL;

	ops->oobretlen = 0;
	ops->retlen = 0;
	ret = 0;
	skip = from % DOC_LAYOUT_PAGE_SIZE;
	mutex_lock(&करोcg3->cascade->lock);
	जबतक (ret >= 0 && (len > 0 || ooblen > 0)) अणु
		calc_block_sector(from - skip, &block0, &block1, &page, &ofs,
			करोcg3->reliable);
		nbdata = min_t(माप_प्रकार, len, DOC_LAYOUT_PAGE_SIZE - skip);
		nboob = min_t(माप_प्रकार, ooblen, (माप_प्रकार)DOC_LAYOUT_OOB_SIZE);
		ret = करोc_पढ़ो_page_prepare(करोcg3, block0, block1, page, ofs);
		अगर (ret < 0)
			जाओ out;
		ret = करोc_पढ़ो_page_ecc_init(करोcg3, DOC_ECC_BCH_TOTAL_BYTES);
		अगर (ret < 0)
			जाओ err_in_पढ़ो;
		ret = करोc_पढ़ो_page_getbytes(करोcg3, skip, शून्य, 1, 0);
		अगर (ret < skip)
			जाओ err_in_पढ़ो;
		ret = करोc_पढ़ो_page_getbytes(करोcg3, nbdata, buf, 0, skip % 2);
		अगर (ret < nbdata)
			जाओ err_in_पढ़ो;
		करोc_पढ़ो_page_getbytes(करोcg3,
				       DOC_LAYOUT_PAGE_SIZE - nbdata - skip,
				       शून्य, 0, (skip + nbdata) % 2);
		ret = करोc_पढ़ो_page_getbytes(करोcg3, nboob, oobbuf, 0, 0);
		अगर (ret < nboob)
			जाओ err_in_पढ़ो;
		करोc_पढ़ो_page_getbytes(करोcg3, DOC_LAYOUT_OOB_SIZE - nboob,
				       शून्य, 0, nboob % 2);

		करोc_get_bch_hw_ecc(करोcg3, hwecc);
		eccconf1 = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_ECCCONF1);

		अगर (nboob >= DOC_LAYOUT_OOB_SIZE) अणु
			करोc_dbg("OOB - INFO: %*phC\n", 7, oobbuf);
			करोc_dbg("OOB - HAMMING: %02x\n", oobbuf[7]);
			करोc_dbg("OOB - BCH_ECC: %*phC\n", 7, oobbuf + 8);
			करोc_dbg("OOB - UNUSED: %02x\n", oobbuf[15]);
		पूर्ण
		करोc_dbg("ECC checks: ECCConf1=%x\n", eccconf1);
		करोc_dbg("ECC HW_ECC: %*phC\n", 7, hwecc);

		ret = -EIO;
		अगर (is_prot_seq_error(करोcg3))
			जाओ err_in_पढ़ो;
		ret = 0;
		अगर ((block0 >= DOC_LAYOUT_BLOCK_FIRST_DATA) &&
		    (eccconf1 & DOC_ECCCONF1_BCH_SYNDROM_ERR) &&
		    (eccconf1 & DOC_ECCCONF1_PAGE_IS_WRITTEN) &&
		    (ops->mode != MTD_OPS_RAW) &&
		    (nbdata == DOC_LAYOUT_PAGE_SIZE)) अणु
			ret = करोc_ecc_bch_fix_data(करोcg3, buf, hwecc);
			अगर (ret < 0) अणु
				mtd->ecc_stats.failed++;
				ret = -EBADMSG;
			पूर्ण
			अगर (ret > 0) अणु
				mtd->ecc_stats.corrected += ret;
				max_bitflips = max(max_bitflips, ret);
				ret = max_bitflips;
			पूर्ण
		पूर्ण

		करोc_पढ़ो_page_finish(करोcg3);
		ops->retlen += nbdata;
		ops->oobretlen += nboob;
		buf += nbdata;
		oobbuf += nboob;
		len -= nbdata;
		ooblen -= nboob;
		from += DOC_LAYOUT_PAGE_SIZE;
		skip = 0;
	पूर्ण

out:
	mutex_unlock(&करोcg3->cascade->lock);
	वापस ret;
err_in_पढ़ो:
	करोc_पढ़ो_page_finish(करोcg3);
	जाओ out;
पूर्ण

अटल पूर्णांक करोc_reload_bbt(काष्ठा करोcg3 *करोcg3)
अणु
	पूर्णांक block = DOC_LAYOUT_BLOCK_BBT;
	पूर्णांक ret = 0, nbpages, page;
	u_अक्षर *buf = करोcg3->bbt;

	nbpages = DIV_ROUND_UP(करोcg3->max_block + 1, 8 * DOC_LAYOUT_PAGE_SIZE);
	क्रम (page = 0; !ret && (page < nbpages); page++) अणु
		ret = करोc_पढ़ो_page_prepare(करोcg3, block, block + 1,
					    page + DOC_LAYOUT_PAGE_BBT, 0);
		अगर (!ret)
			ret = करोc_पढ़ो_page_ecc_init(करोcg3,
						     DOC_LAYOUT_PAGE_SIZE);
		अगर (!ret)
			करोc_पढ़ो_page_getbytes(करोcg3, DOC_LAYOUT_PAGE_SIZE,
					       buf, 1, 0);
		buf += DOC_LAYOUT_PAGE_SIZE;
	पूर्ण
	करोc_पढ़ो_page_finish(करोcg3);
	वापस ret;
पूर्ण

/**
 * करोc_block_isbad - Checks whether a block is good or not
 * @mtd: the device
 * @from: the offset to find the correct block
 *
 * Returns 1 अगर block is bad, 0 अगर block is good
 */
अटल पूर्णांक करोc_block_isbad(काष्ठा mtd_info *mtd, loff_t from)
अणु
	काष्ठा करोcg3 *करोcg3 = mtd->priv;
	पूर्णांक block0, block1, page, ofs, is_good;

	calc_block_sector(from, &block0, &block1, &page, &ofs,
		करोcg3->reliable);
	करोc_dbg("doc_block_isbad(from=%lld) => block=(%d,%d), page=%d, ofs=%d\n",
		from, block0, block1, page, ofs);

	अगर (block0 < DOC_LAYOUT_BLOCK_FIRST_DATA)
		वापस 0;
	अगर (block1 > करोcg3->max_block)
		वापस -EINVAL;

	is_good = करोcg3->bbt[block0 >> 3] & (1 << (block0 & 0x7));
	वापस !is_good;
पूर्ण

#अगर 0
/**
 * करोc_get_erase_count - Get block erase count
 * @करोcg3: the device
 * @from: the offset in which the block is.
 *
 * Get the number of बार a block was erased. The number is the maximum of
 * erase बार between first and second plane (which should be equal normally).
 *
 * Returns The number of erases, or -EINVAL or -EIO on error.
 */
अटल पूर्णांक करोc_get_erase_count(काष्ठा करोcg3 *करोcg3, loff_t from)
अणु
	u8 buf[DOC_LAYOUT_WEAR_SIZE];
	पूर्णांक ret, plane1_erase_count, plane2_erase_count;
	पूर्णांक block0, block1, page, ofs;

	करोc_dbg("doc_get_erase_count(from=%lld, buf=%p)\n", from, buf);
	अगर (from % DOC_LAYOUT_PAGE_SIZE)
		वापस -EINVAL;
	calc_block_sector(from, &block0, &block1, &page, &ofs, करोcg3->reliable);
	अगर (block1 > करोcg3->max_block)
		वापस -EINVAL;

	ret = करोc_reset_seq(करोcg3);
	अगर (!ret)
		ret = करोc_पढ़ो_page_prepare(करोcg3, block0, block1, page,
					    ofs + DOC_LAYOUT_WEAR_OFFSET, 0);
	अगर (!ret)
		ret = करोc_पढ़ो_page_getbytes(करोcg3, DOC_LAYOUT_WEAR_SIZE,
					     buf, 1, 0);
	करोc_पढ़ो_page_finish(करोcg3);

	अगर (ret || (buf[0] != DOC_ERASE_MARK) || (buf[2] != DOC_ERASE_MARK))
		वापस -EIO;
	plane1_erase_count = (u8)(~buf[1]) | ((u8)(~buf[4]) << 8)
		| ((u8)(~buf[5]) << 16);
	plane2_erase_count = (u8)(~buf[3]) | ((u8)(~buf[6]) << 8)
		| ((u8)(~buf[7]) << 16);

	वापस max(plane1_erase_count, plane2_erase_count);
पूर्ण
#पूर्ण_अगर

/**
 * करोc_get_op_status - get erase/ग_लिखो operation status
 * @करोcg3: the device
 *
 * Queries the status from the chip, and वापसs it
 *
 * Returns the status (bits DOC_PLANES_STATUS_*)
 */
अटल पूर्णांक करोc_get_op_status(काष्ठा करोcg3 *करोcg3)
अणु
	u8 status;

	करोc_flash_sequence(करोcg3, DOC_SEQ_PLANES_STATUS);
	करोc_flash_command(करोcg3, DOC_CMD_PLANES_STATUS);
	करोc_delay(करोcg3, 5);

	करोc_ecc_disable(करोcg3);
	करोc_पढ़ो_data_area(करोcg3, &status, 1, 1);
	वापस status;
पूर्ण

/**
 * करोc_ग_लिखो_erase_रुको_status - रुको क्रम ग_लिखो or erase completion
 * @करोcg3: the device
 *
 * Wait क्रम the chip to be पढ़ोy again after erase or ग_लिखो operation, and check
 * erase/ग_लिखो status.
 *
 * Returns 0 अगर erase successful, -EIO अगर erase/ग_लिखो issue, -ETIMEOUT अगर
 * समयout
 */
अटल पूर्णांक करोc_ग_लिखो_erase_रुको_status(काष्ठा करोcg3 *करोcg3)
अणु
	पूर्णांक i, status, ret = 0;

	क्रम (i = 0; !करोc_is_पढ़ोy(करोcg3) && i < 5; i++)
		msleep(20);
	अगर (!करोc_is_पढ़ोy(करोcg3)) अणु
		करोc_dbg("Timeout reached and the chip is still not ready\n");
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	status = करोc_get_op_status(करोcg3);
	अगर (status & DOC_PLANES_STATUS_FAIL) अणु
		करोc_dbg("Erase/Write failed on (a) plane(s), status = %x\n",
			status);
		ret = -EIO;
	पूर्ण

out:
	करोc_page_finish(करोcg3);
	वापस ret;
पूर्ण

/**
 * करोc_erase_block - Erase a couple of blocks
 * @करोcg3: the device
 * @block0: the first block to erase (lefपंचांगost plane)
 * @block1: the second block to erase (righपंचांगost plane)
 *
 * Erase both blocks, and वापस operation status
 *
 * Returns 0 अगर erase successful, -EIO अगर erase issue, -ETIMEOUT अगर chip not
 * पढ़ोy क्रम too दीर्घ
 */
अटल पूर्णांक करोc_erase_block(काष्ठा करोcg3 *करोcg3, पूर्णांक block0, पूर्णांक block1)
अणु
	पूर्णांक ret, sector;

	करोc_dbg("doc_erase_block(blocks=(%d,%d))\n", block0, block1);
	ret = करोc_reset_seq(करोcg3);
	अगर (ret)
		वापस -EIO;

	करोc_set_reliable_mode(करोcg3);
	करोc_flash_sequence(करोcg3, DOC_SEQ_ERASE);

	sector = block0 << DOC_ADDR_BLOCK_SHIFT;
	करोc_flash_command(करोcg3, DOC_CMD_PROG_BLOCK_ADDR);
	करोc_setup_addr_sector(करोcg3, sector);
	sector = block1 << DOC_ADDR_BLOCK_SHIFT;
	करोc_flash_command(करोcg3, DOC_CMD_PROG_BLOCK_ADDR);
	करोc_setup_addr_sector(करोcg3, sector);
	करोc_delay(करोcg3, 1);

	करोc_flash_command(करोcg3, DOC_CMD_ERASECYCLE2);
	करोc_delay(करोcg3, 2);

	अगर (is_prot_seq_error(करोcg3)) अणु
		करोc_err("Erase blocks %d,%d error\n", block0, block1);
		वापस -EIO;
	पूर्ण

	वापस करोc_ग_लिखो_erase_रुको_status(करोcg3);
पूर्ण

/**
 * करोc_erase - Erase a portion of the chip
 * @mtd: the device
 * @info: the erase info
 *
 * Erase a bunch of contiguous blocks, by pairs, as a "mtd" page of 1024 is
 * split पूर्णांकo 2 pages of 512 bytes on 2 contiguous blocks.
 *
 * Returns 0 अगर erase successful, -EINVAL अगर addressing error, -EIO अगर erase
 * issue
 */
अटल पूर्णांक करोc_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *info)
अणु
	काष्ठा करोcg3 *करोcg3 = mtd->priv;
	uपूर्णांक64_t len;
	पूर्णांक block0, block1, page, ret = 0, ofs = 0;

	करोc_dbg("doc_erase(from=%lld, len=%lld\n", info->addr, info->len);

	calc_block_sector(info->addr + info->len, &block0, &block1, &page,
			  &ofs, करोcg3->reliable);
	अगर (info->addr + info->len > mtd->size || page || ofs)
		वापस -EINVAL;

	calc_block_sector(info->addr, &block0, &block1, &page, &ofs,
			  करोcg3->reliable);
	mutex_lock(&करोcg3->cascade->lock);
	करोc_set_device_id(करोcg3, करोcg3->device_id);
	करोc_set_reliable_mode(करोcg3);
	क्रम (len = info->len; !ret && len > 0; len -= mtd->erasesize) अणु
		ret = करोc_erase_block(करोcg3, block0, block1);
		block0 += 2;
		block1 += 2;
	पूर्ण
	mutex_unlock(&करोcg3->cascade->lock);

	वापस ret;
पूर्ण

/**
 * करोc_ग_लिखो_page - Write a single page to the chip
 * @करोcg3: the device
 * @to: the offset from first block and first page, in bytes, aligned on page
 *      size
 * @buf: buffer to get bytes from
 * @oob: buffer to get out of band bytes from (can be शून्य अगर no OOB should be
 *       written)
 * @स्वतःecc: अगर 0, all 16 bytes from OOB are taken, regardless of HW Hamming or
 *           BCH computations. If 1, only bytes 0-7 and byte 15 are taken,
 *           reमुख्यing ones are filled with hardware Hamming and BCH
 *           computations. Its value is not meaningfull is oob == शून्य.
 *
 * Write one full page (ie. 1 page split on two planes), of 512 bytes, with the
 * OOB data. The OOB ECC is स्वतःmatically computed by the hardware Hamming and
 * BCH generator अगर स्वतःecc is not null.
 *
 * Returns 0 अगर ग_लिखो successful, -EIO अगर ग_लिखो error, -EAGAIN अगर समयout
 */
अटल पूर्णांक करोc_ग_लिखो_page(काष्ठा करोcg3 *करोcg3, loff_t to, स्थिर u_अक्षर *buf,
			  स्थिर u_अक्षर *oob, पूर्णांक स्वतःecc)
अणु
	पूर्णांक block0, block1, page, ret, ofs = 0;
	u8 hwecc[DOC_ECC_BCH_SIZE], hamming;

	करोc_dbg("doc_write_page(to=%lld)\n", to);
	calc_block_sector(to, &block0, &block1, &page, &ofs, करोcg3->reliable);

	करोc_set_device_id(करोcg3, करोcg3->device_id);
	ret = करोc_reset_seq(करोcg3);
	अगर (ret)
		जाओ err;

	/* Program the flash address block and page */
	ret = करोc_ग_लिखो_seek(करोcg3, block0, block1, page, ofs);
	अगर (ret)
		जाओ err;

	करोc_ग_लिखो_page_ecc_init(करोcg3, DOC_ECC_BCH_TOTAL_BYTES);
	करोc_delay(करोcg3, 2);
	करोc_ग_लिखो_page_putbytes(करोcg3, DOC_LAYOUT_PAGE_SIZE, buf);

	अगर (oob && स्वतःecc) अणु
		करोc_ग_लिखो_page_putbytes(करोcg3, DOC_LAYOUT_OOB_PAGEINFO_SZ, oob);
		करोc_delay(करोcg3, 2);
		oob += DOC_LAYOUT_OOB_UNUSED_OFS;

		hamming = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_HAMMINGPARITY);
		करोc_delay(करोcg3, 2);
		करोc_ग_लिखो_page_putbytes(करोcg3, DOC_LAYOUT_OOB_HAMMING_SZ,
					&hamming);
		करोc_delay(करोcg3, 2);

		करोc_get_bch_hw_ecc(करोcg3, hwecc);
		करोc_ग_लिखो_page_putbytes(करोcg3, DOC_LAYOUT_OOB_BCH_SZ, hwecc);
		करोc_delay(करोcg3, 2);

		करोc_ग_लिखो_page_putbytes(करोcg3, DOC_LAYOUT_OOB_UNUSED_SZ, oob);
	पूर्ण
	अगर (oob && !स्वतःecc)
		करोc_ग_लिखो_page_putbytes(करोcg3, DOC_LAYOUT_OOB_SIZE, oob);

	करोc_delay(करोcg3, 2);
	करोc_page_finish(करोcg3);
	करोc_delay(करोcg3, 2);
	करोc_flash_command(करोcg3, DOC_CMD_PROG_CYCLE2);
	करोc_delay(करोcg3, 2);

	/*
	 * The रुको status will perक्रमm another करोc_page_finish() call, but that
	 * seems to please the करोcg3, so leave it.
	 */
	ret = करोc_ग_लिखो_erase_रुको_status(करोcg3);
	वापस ret;
err:
	करोc_पढ़ो_page_finish(करोcg3);
	वापस ret;
पूर्ण

/**
 * करोc_guess_स्वतःecc - Guess स्वतःecc mode from mbd_oob_ops
 * @ops: the oob operations
 *
 * Returns 0 or 1 अगर success, -EINVAL अगर invalid oob mode
 */
अटल पूर्णांक करोc_guess_स्वतःecc(काष्ठा mtd_oob_ops *ops)
अणु
	पूर्णांक स्वतःecc;

	चयन (ops->mode) अणु
	हाल MTD_OPS_PLACE_OOB:
	हाल MTD_OPS_AUTO_OOB:
		स्वतःecc = 1;
		अवरोध;
	हाल MTD_OPS_RAW:
		स्वतःecc = 0;
		अवरोध;
	शेष:
		स्वतःecc = -EINVAL;
	पूर्ण
	वापस स्वतःecc;
पूर्ण

/**
 * करोc_fill_स्वतःoob - Fill a 16 bytes OOB from 8 non-ECC bytes
 * @dst: the target 16 bytes OOB buffer
 * @oobsrc: the source 8 bytes non-ECC OOB buffer
 *
 */
अटल व्योम करोc_fill_स्वतःoob(u8 *dst, u8 *oobsrc)
अणु
	स_नकल(dst, oobsrc, DOC_LAYOUT_OOB_PAGEINFO_SZ);
	dst[DOC_LAYOUT_OOB_UNUSED_OFS] = oobsrc[DOC_LAYOUT_OOB_PAGEINFO_SZ];
पूर्ण

/**
 * करोc_backup_oob - Backup OOB पूर्णांकo करोcg3 काष्ठाure
 * @करोcg3: the device
 * @to: the page offset in the chip
 * @ops: the OOB size and buffer
 *
 * As the करोcg3 should ग_लिखो a page with its OOB in one pass, and some userland
 * applications करो ग_लिखो_oob() to setup the OOB and then ग_लिखो(), store the OOB
 * पूर्णांकo a temporary storage. This is very dangerous, as 2 concurrent
 * applications could store an OOB, and then ग_लिखो their pages (which will
 * result पूर्णांकo one having its OOB corrupted).
 *
 * The only reliable way would be क्रम userland to call करोc_ग_लिखो_oob() with both
 * the page data _and_ the OOB area.
 *
 * Returns 0 अगर success, -EINVAL अगर ops content invalid
 */
अटल पूर्णांक करोc_backup_oob(काष्ठा करोcg3 *करोcg3, loff_t to,
			  काष्ठा mtd_oob_ops *ops)
अणु
	पूर्णांक ooblen = ops->ooblen, स्वतःecc;

	अगर (ooblen != DOC_LAYOUT_OOB_SIZE)
		वापस -EINVAL;
	स्वतःecc = करोc_guess_स्वतःecc(ops);
	अगर (स्वतःecc < 0)
		वापस स्वतःecc;

	करोcg3->oob_ग_लिखो_ofs = to;
	करोcg3->oob_स्वतःecc = स्वतःecc;
	अगर (ops->mode == MTD_OPS_AUTO_OOB) अणु
		करोc_fill_स्वतःoob(करोcg3->oob_ग_लिखो_buf, ops->oobbuf);
		ops->oobretlen = 8;
	पूर्ण अन्यथा अणु
		स_नकल(करोcg3->oob_ग_लिखो_buf, ops->oobbuf, DOC_LAYOUT_OOB_SIZE);
		ops->oobretlen = DOC_LAYOUT_OOB_SIZE;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * करोc_ग_लिखो_oob - Write out of band bytes to flash
 * @mtd: the device
 * @ofs: the offset from first block and first page, in bytes, aligned on page
 *       size
 * @ops: the mtd oob काष्ठाure
 *
 * Either ग_लिखो OOB data पूर्णांकo a temporary buffer, क्रम the subsequent ग_लिखो
 * page. The provided OOB should be 16 bytes दीर्घ. If a data buffer is provided
 * as well, issue the page ग_लिखो.
 * Or provide data without OOB, and then a all zeroed OOB will be used (ECC will
 * still be filled in अगर asked क्रम).
 *
 * Returns 0 is successful, EINVAL अगर length is not 14 bytes
 */
अटल पूर्णांक करोc_ग_लिखो_oob(काष्ठा mtd_info *mtd, loff_t ofs,
			 काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा करोcg3 *करोcg3 = mtd->priv;
	पूर्णांक ret, स्वतःecc, oobdelta;
	u8 *oobbuf = ops->oobbuf;
	u8 *buf = ops->datbuf;
	माप_प्रकार len, ooblen;
	u8 oob[DOC_LAYOUT_OOB_SIZE];

	अगर (buf)
		len = ops->len;
	अन्यथा
		len = 0;
	अगर (oobbuf)
		ooblen = ops->ooblen;
	अन्यथा
		ooblen = 0;

	अगर (oobbuf && ops->mode == MTD_OPS_PLACE_OOB)
		oobbuf += ops->ooboffs;

	करोc_dbg("doc_write_oob(from=%lld, mode=%d, data=(%p:%zu), oob=(%p:%zu))\n",
		ofs, ops->mode, buf, len, oobbuf, ooblen);
	चयन (ops->mode) अणु
	हाल MTD_OPS_PLACE_OOB:
	हाल MTD_OPS_RAW:
		oobdelta = mtd->oobsize;
		अवरोध;
	हाल MTD_OPS_AUTO_OOB:
		oobdelta = mtd->oobavail;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर ((len % DOC_LAYOUT_PAGE_SIZE) || (ooblen % oobdelta) ||
	    (ofs % DOC_LAYOUT_PAGE_SIZE))
		वापस -EINVAL;
	अगर (len && ooblen &&
	    (len / DOC_LAYOUT_PAGE_SIZE) != (ooblen / oobdelta))
		वापस -EINVAL;

	ops->oobretlen = 0;
	ops->retlen = 0;
	ret = 0;
	अगर (len == 0 && ooblen == 0)
		वापस -EINVAL;
	अगर (len == 0 && ooblen > 0)
		वापस करोc_backup_oob(करोcg3, ofs, ops);

	स्वतःecc = करोc_guess_स्वतःecc(ops);
	अगर (स्वतःecc < 0)
		वापस स्वतःecc;

	mutex_lock(&करोcg3->cascade->lock);
	जबतक (!ret && len > 0) अणु
		स_रखो(oob, 0, माप(oob));
		अगर (ofs == करोcg3->oob_ग_लिखो_ofs)
			स_नकल(oob, करोcg3->oob_ग_लिखो_buf, DOC_LAYOUT_OOB_SIZE);
		अन्यथा अगर (ooblen > 0 && ops->mode == MTD_OPS_AUTO_OOB)
			करोc_fill_स्वतःoob(oob, oobbuf);
		अन्यथा अगर (ooblen > 0)
			स_नकल(oob, oobbuf, DOC_LAYOUT_OOB_SIZE);
		ret = करोc_ग_लिखो_page(करोcg3, ofs, buf, oob, स्वतःecc);

		ofs += DOC_LAYOUT_PAGE_SIZE;
		len -= DOC_LAYOUT_PAGE_SIZE;
		buf += DOC_LAYOUT_PAGE_SIZE;
		अगर (ooblen) अणु
			oobbuf += oobdelta;
			ooblen -= oobdelta;
			ops->oobretlen += oobdelta;
		पूर्ण
		ops->retlen += DOC_LAYOUT_PAGE_SIZE;
	पूर्ण

	करोc_set_device_id(करोcg3, 0);
	mutex_unlock(&करोcg3->cascade->lock);
	वापस ret;
पूर्ण

अटल काष्ठा करोcg3 *sysfs_dev2करोcg3(काष्ठा device *dev,
				     काष्ठा device_attribute *attr)
अणु
	पूर्णांक न्यूनमान;
	काष्ठा mtd_info **करोcg3_न्यूनमानs = dev_get_drvdata(dev);

	न्यूनमान = attr->attr.name[1] - '0';
	अगर (न्यूनमान < 0 || न्यूनमान >= DOC_MAX_NBFLOORS)
		वापस शून्य;
	अन्यथा
		वापस करोcg3_न्यूनमानs[न्यूनमान]->priv;
पूर्ण

अटल sमाप_प्रकार dps0_is_key_locked(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा करोcg3 *करोcg3 = sysfs_dev2करोcg3(dev, attr);
	पूर्णांक dps0;

	mutex_lock(&करोcg3->cascade->lock);
	करोc_set_device_id(करोcg3, करोcg3->device_id);
	dps0 = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_DPS0_STATUS);
	करोc_set_device_id(करोcg3, 0);
	mutex_unlock(&करोcg3->cascade->lock);

	वापस प्र_लिखो(buf, "%d\n", !(dps0 & DOC_DPS_KEY_OK));
पूर्ण

अटल sमाप_प्रकार dps1_is_key_locked(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा करोcg3 *करोcg3 = sysfs_dev2करोcg3(dev, attr);
	पूर्णांक dps1;

	mutex_lock(&करोcg3->cascade->lock);
	करोc_set_device_id(करोcg3, करोcg3->device_id);
	dps1 = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_DPS1_STATUS);
	करोc_set_device_id(करोcg3, 0);
	mutex_unlock(&करोcg3->cascade->lock);

	वापस प्र_लिखो(buf, "%d\n", !(dps1 & DOC_DPS_KEY_OK));
पूर्ण

अटल sमाप_प्रकार dps0_insert_key(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा करोcg3 *करोcg3 = sysfs_dev2करोcg3(dev, attr);
	पूर्णांक i;

	अगर (count != DOC_LAYOUT_DPS_KEY_LENGTH)
		वापस -EINVAL;

	mutex_lock(&करोcg3->cascade->lock);
	करोc_set_device_id(करोcg3, करोcg3->device_id);
	क्रम (i = 0; i < DOC_LAYOUT_DPS_KEY_LENGTH; i++)
		करोc_ग_लिखोb(करोcg3, buf[i], DOC_DPS0_KEY);
	करोc_set_device_id(करोcg3, 0);
	mutex_unlock(&करोcg3->cascade->lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार dps1_insert_key(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा करोcg3 *करोcg3 = sysfs_dev2करोcg3(dev, attr);
	पूर्णांक i;

	अगर (count != DOC_LAYOUT_DPS_KEY_LENGTH)
		वापस -EINVAL;

	mutex_lock(&करोcg3->cascade->lock);
	करोc_set_device_id(करोcg3, करोcg3->device_id);
	क्रम (i = 0; i < DOC_LAYOUT_DPS_KEY_LENGTH; i++)
		करोc_ग_लिखोb(करोcg3, buf[i], DOC_DPS1_KEY);
	करोc_set_device_id(करोcg3, 0);
	mutex_unlock(&करोcg3->cascade->lock);
	वापस count;
पूर्ण

#घोषणा FLOOR_SYSFS(id) अणु \
	__ATTR(f##id##_dps0_is_keylocked, S_IRUGO, dps0_is_key_locked, शून्य), \
	__ATTR(f##id##_dps1_is_keylocked, S_IRUGO, dps1_is_key_locked, शून्य), \
	__ATTR(f##id##_dps0_protection_key, S_IWUSR|S_IWGRP, शून्य, dps0_insert_key), \
	__ATTR(f##id##_dps1_protection_key, S_IWUSR|S_IWGRP, शून्य, dps1_insert_key), \
पूर्ण

अटल काष्ठा device_attribute करोc_sys_attrs[DOC_MAX_NBFLOORS][4] = अणु
	FLOOR_SYSFS(0), FLOOR_SYSFS(1), FLOOR_SYSFS(2), FLOOR_SYSFS(3)
पूर्ण;

अटल पूर्णांक करोc_रेजिस्टर_sysfs(काष्ठा platक्रमm_device *pdev,
			      काष्ठा करोcg3_cascade *cascade)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक न्यूनमान;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (न्यूनमान = 0;
	     न्यूनमान < DOC_MAX_NBFLOORS && cascade->न्यूनमानs[न्यूनमान];
	     न्यूनमान++) अणु
		क्रम (i = 0; i < 4; i++) अणु
			ret = device_create_file(dev, &करोc_sys_attrs[न्यूनमान][i]);
			अगर (ret)
				जाओ हटाओ_files;
		पूर्ण
	पूर्ण

	वापस 0;

हटाओ_files:
	करो अणु
		जबतक (--i >= 0)
			device_हटाओ_file(dev, &करोc_sys_attrs[न्यूनमान][i]);
		i = 4;
	पूर्ण जबतक (--न्यूनमान >= 0);

	वापस ret;
पूर्ण

अटल व्योम करोc_unरेजिस्टर_sysfs(काष्ठा platक्रमm_device *pdev,
				 काष्ठा करोcg3_cascade *cascade)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक न्यूनमान, i;

	क्रम (न्यूनमान = 0; न्यूनमान < DOC_MAX_NBFLOORS && cascade->न्यूनमानs[न्यूनमान];
	     न्यूनमान++)
		क्रम (i = 0; i < 4; i++)
			device_हटाओ_file(dev, &करोc_sys_attrs[न्यूनमान][i]);
पूर्ण

/*
 * Debug sysfs entries
 */
अटल पूर्णांक flashcontrol_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा करोcg3 *करोcg3 = (काष्ठा करोcg3 *)s->निजी;

	u8 fctrl;

	mutex_lock(&करोcg3->cascade->lock);
	fctrl = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_FLASHCONTROL);
	mutex_unlock(&करोcg3->cascade->lock);

	seq_म_लिखो(s, "FlashControl : 0x%02x (%s,CE# %s,%s,%s,flash %s)\n",
		   fctrl,
		   fctrl & DOC_CTRL_VIOLATION ? "protocol violation" : "-",
		   fctrl & DOC_CTRL_CE ? "active" : "inactive",
		   fctrl & DOC_CTRL_PROTECTION_ERROR ? "protection error" : "-",
		   fctrl & DOC_CTRL_SEQUENCE_ERROR ? "sequence error" : "-",
		   fctrl & DOC_CTRL_FLASHREADY ? "ready" : "not ready");

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(flashcontrol);

अटल पूर्णांक asic_mode_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा करोcg3 *करोcg3 = (काष्ठा करोcg3 *)s->निजी;

	पूर्णांक pctrl, mode;

	mutex_lock(&करोcg3->cascade->lock);
	pctrl = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_ASICMODE);
	mode = pctrl & 0x03;
	mutex_unlock(&करोcg3->cascade->lock);

	seq_म_लिखो(s,
		   "%04x : RAM_WE=%d,RSTIN_RESET=%d,BDETCT_RESET=%d,WRITE_ENABLE=%d,POWERDOWN=%d,MODE=%d%d (",
		   pctrl,
		   pctrl & DOC_ASICMODE_RAM_WE ? 1 : 0,
		   pctrl & DOC_ASICMODE_RSTIN_RESET ? 1 : 0,
		   pctrl & DOC_ASICMODE_BDETCT_RESET ? 1 : 0,
		   pctrl & DOC_ASICMODE_MDWREN ? 1 : 0,
		   pctrl & DOC_ASICMODE_POWERDOWN ? 1 : 0,
		   mode >> 1, mode & 0x1);

	चयन (mode) अणु
	हाल DOC_ASICMODE_RESET:
		seq_माला_दो(s, "reset");
		अवरोध;
	हाल DOC_ASICMODE_NORMAL:
		seq_माला_दो(s, "normal");
		अवरोध;
	हाल DOC_ASICMODE_POWERDOWN:
		seq_माला_दो(s, "powerdown");
		अवरोध;
	पूर्ण
	seq_माला_दो(s, ")\n");
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(asic_mode);

अटल पूर्णांक device_id_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा करोcg3 *करोcg3 = (काष्ठा करोcg3 *)s->निजी;
	पूर्णांक id;

	mutex_lock(&करोcg3->cascade->lock);
	id = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_DEVICESELECT);
	mutex_unlock(&करोcg3->cascade->lock);

	seq_म_लिखो(s, "DeviceId = %d\n", id);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(device_id);

अटल पूर्णांक protection_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा करोcg3 *करोcg3 = (काष्ठा करोcg3 *)s->निजी;
	पूर्णांक protect, dps0, dps0_low, dps0_high, dps1, dps1_low, dps1_high;

	mutex_lock(&करोcg3->cascade->lock);
	protect = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_PROTECTION);
	dps0 = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_DPS0_STATUS);
	dps0_low = करोc_रेजिस्टर_पढ़ोw(करोcg3, DOC_DPS0_ADDRLOW);
	dps0_high = करोc_रेजिस्टर_पढ़ोw(करोcg3, DOC_DPS0_ADDRHIGH);
	dps1 = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_DPS1_STATUS);
	dps1_low = करोc_रेजिस्टर_पढ़ोw(करोcg3, DOC_DPS1_ADDRLOW);
	dps1_high = करोc_रेजिस्टर_पढ़ोw(करोcg3, DOC_DPS1_ADDRHIGH);
	mutex_unlock(&करोcg3->cascade->lock);

	seq_म_लिखो(s, "Protection = 0x%02x (", protect);
	अगर (protect & DOC_PROTECT_FOUNDRY_OTP_LOCK)
		seq_माला_दो(s, "FOUNDRY_OTP_LOCK,");
	अगर (protect & DOC_PROTECT_CUSTOMER_OTP_LOCK)
		seq_माला_दो(s, "CUSTOMER_OTP_LOCK,");
	अगर (protect & DOC_PROTECT_LOCK_INPUT)
		seq_माला_दो(s, "LOCK_INPUT,");
	अगर (protect & DOC_PROTECT_STICKY_LOCK)
		seq_माला_दो(s, "STICKY_LOCK,");
	अगर (protect & DOC_PROTECT_PROTECTION_ENABLED)
		seq_माला_दो(s, "PROTECTION ON,");
	अगर (protect & DOC_PROTECT_IPL_DOWNLOAD_LOCK)
		seq_माला_दो(s, "IPL_DOWNLOAD_LOCK,");
	अगर (protect & DOC_PROTECT_PROTECTION_ERROR)
		seq_माला_दो(s, "PROTECT_ERR,");
	अन्यथा
		seq_माला_दो(s, "NO_PROTECT_ERR");
	seq_माला_दो(s, ")\n");

	seq_म_लिखो(s, "DPS0 = 0x%02x : Protected area [0x%x - 0x%x] : OTP=%d, READ=%d, WRITE=%d, HW_LOCK=%d, KEY_OK=%d\n",
		   dps0, dps0_low, dps0_high,
		   !!(dps0 & DOC_DPS_OTP_PROTECTED),
		   !!(dps0 & DOC_DPS_READ_PROTECTED),
		   !!(dps0 & DOC_DPS_WRITE_PROTECTED),
		   !!(dps0 & DOC_DPS_HW_LOCK_ENABLED),
		   !!(dps0 & DOC_DPS_KEY_OK));
	seq_म_लिखो(s, "DPS1 = 0x%02x : Protected area [0x%x - 0x%x] : OTP=%d, READ=%d, WRITE=%d, HW_LOCK=%d, KEY_OK=%d\n",
		   dps1, dps1_low, dps1_high,
		   !!(dps1 & DOC_DPS_OTP_PROTECTED),
		   !!(dps1 & DOC_DPS_READ_PROTECTED),
		   !!(dps1 & DOC_DPS_WRITE_PROTECTED),
		   !!(dps1 & DOC_DPS_HW_LOCK_ENABLED),
		   !!(dps1 & DOC_DPS_KEY_OK));
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(protection);

अटल व्योम __init करोc_dbg_रेजिस्टर(काष्ठा mtd_info *न्यूनमान)
अणु
	काष्ठा dentry *root = न्यूनमान->dbg.dfs_dir;
	काष्ठा करोcg3 *करोcg3 = न्यूनमान->priv;

	अगर (IS_ERR_OR_शून्य(root)) अणु
		अगर (IS_ENABLED(CONFIG_DEBUG_FS) &&
		    !IS_ENABLED(CONFIG_MTD_PARTITIONED_MASTER))
			dev_warn(न्यूनमान->dev.parent,
				 "CONFIG_MTD_PARTITIONED_MASTER must be enabled to expose debugfs stuff\n");
		वापस;
	पूर्ण

	debugfs_create_file("docg3_flashcontrol", S_IRUSR, root, करोcg3,
			    &flashcontrol_fops);
	debugfs_create_file("docg3_asic_mode", S_IRUSR, root, करोcg3,
			    &asic_mode_fops);
	debugfs_create_file("docg3_device_id", S_IRUSR, root, करोcg3,
			    &device_id_fops);
	debugfs_create_file("docg3_protection", S_IRUSR, root, करोcg3,
			    &protection_fops);
पूर्ण

/**
 * करोc_set_driver_info - Fill the mtd_info काष्ठाure and करोcg3 काष्ठाure
 * @chip_id: The chip ID of the supported chip
 * @mtd: The काष्ठाure to fill
 */
अटल पूर्णांक __init करोc_set_driver_info(पूर्णांक chip_id, काष्ठा mtd_info *mtd)
अणु
	काष्ठा करोcg3 *करोcg3 = mtd->priv;
	पूर्णांक cfg;

	cfg = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_CONFIGURATION);
	करोcg3->अगर_cfg = (cfg & DOC_CONF_IF_CFG ? 1 : 0);
	करोcg3->reliable = reliable_mode;

	चयन (chip_id) अणु
	हाल DOC_CHIPID_G3:
		mtd->name = devm_kaप्र_लिखो(करोcg3->dev, GFP_KERNEL, "docg3.%d",
					   करोcg3->device_id);
		अगर (!mtd->name)
			वापस -ENOMEM;
		करोcg3->max_block = 2047;
		अवरोध;
	पूर्ण
	mtd->type = MTD_न_अंकDFLASH;
	mtd->flags = MTD_CAP_न_अंकDFLASH;
	mtd->size = (करोcg3->max_block + 1) * DOC_LAYOUT_BLOCK_SIZE;
	अगर (करोcg3->reliable == 2)
		mtd->size /= 2;
	mtd->erasesize = DOC_LAYOUT_BLOCK_SIZE * DOC_LAYOUT_NBPLANES;
	अगर (करोcg3->reliable == 2)
		mtd->erasesize /= 2;
	mtd->ग_लिखोbufsize = mtd->ग_लिखोsize = DOC_LAYOUT_PAGE_SIZE;
	mtd->oobsize = DOC_LAYOUT_OOB_SIZE;
	mtd->_erase = करोc_erase;
	mtd->_पढ़ो_oob = करोc_पढ़ो_oob;
	mtd->_ग_लिखो_oob = करोc_ग_लिखो_oob;
	mtd->_block_isbad = करोc_block_isbad;
	mtd_set_ooblayout(mtd, &nand_ooblayout_करोcg3_ops);
	mtd->oobavail = 8;
	mtd->ecc_strength = DOC_ECC_BCH_T;

	वापस 0;
पूर्ण

/**
 * करोc_probe_device - Check अगर a device is available
 * @cascade: the cascade of chips this devices will beदीर्घ to
 * @न्यूनमान: the न्यूनमान of the probed device
 * @dev: the device
 *
 * Checks whether a device at the specअगरied IO range, and न्यूनमान is available.
 *
 * Returns a mtd_info काष्ठा अगर there is a device, ENODEV अगर none found, ENOMEM
 * अगर a memory allocation failed. If न्यूनमान 0 is checked, a reset of the ASIC is
 * launched.
 */
अटल काष्ठा mtd_info * __init
करोc_probe_device(काष्ठा करोcg3_cascade *cascade, पूर्णांक न्यूनमान, काष्ठा device *dev)
अणु
	पूर्णांक ret, bbt_nbpages;
	u16 chip_id, chip_id_inv;
	काष्ठा करोcg3 *करोcg3;
	काष्ठा mtd_info *mtd;

	ret = -ENOMEM;
	करोcg3 = kzalloc(माप(काष्ठा करोcg3), GFP_KERNEL);
	अगर (!करोcg3)
		जाओ nomem1;
	mtd = kzalloc(माप(काष्ठा mtd_info), GFP_KERNEL);
	अगर (!mtd)
		जाओ nomem2;
	mtd->priv = करोcg3;
	mtd->dev.parent = dev;
	bbt_nbpages = DIV_ROUND_UP(करोcg3->max_block + 1,
				   8 * DOC_LAYOUT_PAGE_SIZE);
	करोcg3->bbt = kसुस्मृति(DOC_LAYOUT_PAGE_SIZE, bbt_nbpages, GFP_KERNEL);
	अगर (!करोcg3->bbt)
		जाओ nomem3;

	करोcg3->dev = dev;
	करोcg3->device_id = न्यूनमान;
	करोcg3->cascade = cascade;
	करोc_set_device_id(करोcg3, करोcg3->device_id);
	अगर (!न्यूनमान)
		करोc_set_asic_mode(करोcg3, DOC_ASICMODE_RESET);
	करोc_set_asic_mode(करोcg3, DOC_ASICMODE_NORMAL);

	chip_id = करोc_रेजिस्टर_पढ़ोw(करोcg3, DOC_CHIPID);
	chip_id_inv = करोc_रेजिस्टर_पढ़ोw(करोcg3, DOC_CHIPID_INV);

	ret = 0;
	अगर (chip_id != (u16)(~chip_id_inv)) अणु
		जाओ nomem4;
	पूर्ण

	चयन (chip_id) अणु
	हाल DOC_CHIPID_G3:
		करोc_info("Found a G3 DiskOnChip at addr %p, floor %d\n",
			 करोcg3->cascade->base, न्यूनमान);
		अवरोध;
	शेष:
		करोc_err("Chip id %04x is not a DiskOnChip G3 chip\n", chip_id);
		जाओ nomem4;
	पूर्ण

	ret = करोc_set_driver_info(chip_id, mtd);
	अगर (ret)
		जाओ nomem4;

	करोc_hamming_ecc_init(करोcg3, DOC_LAYOUT_OOB_PAGEINFO_SZ);
	करोc_reload_bbt(करोcg3);
	वापस mtd;

nomem4:
	kमुक्त(करोcg3->bbt);
nomem3:
	kमुक्त(mtd);
nomem2:
	kमुक्त(करोcg3);
nomem1:
	वापस ret ? ERR_PTR(ret) : शून्य;
पूर्ण

/**
 * करोc_release_device - Release a करोcg3 न्यूनमान
 * @mtd: the device
 */
अटल व्योम करोc_release_device(काष्ठा mtd_info *mtd)
अणु
	काष्ठा करोcg3 *करोcg3 = mtd->priv;

	mtd_device_unरेजिस्टर(mtd);
	kमुक्त(करोcg3->bbt);
	kमुक्त(करोcg3);
	kमुक्त(mtd);
पूर्ण

/**
 * करोcg3_resume - Awakens करोcg3 न्यूनमान
 * @pdev: platfrom device
 *
 * Returns 0 (always successful)
 */
अटल पूर्णांक करोcg3_resume(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा करोcg3_cascade *cascade;
	काष्ठा mtd_info **करोcg3_न्यूनमानs, *mtd;
	काष्ठा करोcg3 *करोcg3;

	cascade = platक्रमm_get_drvdata(pdev);
	करोcg3_न्यूनमानs = cascade->न्यूनमानs;
	mtd = करोcg3_न्यूनमानs[0];
	करोcg3 = mtd->priv;

	करोc_dbg("docg3_resume()\n");
	क्रम (i = 0; i < 12; i++)
		करोc_पढ़ोb(करोcg3, DOC_IOSPACE_IPL);
	वापस 0;
पूर्ण

/**
 * करोcg3_suspend - Put in low घातer mode the करोcg3 न्यूनमान
 * @pdev: platक्रमm device
 * @state: घातer state
 *
 * Shuts off most of करोcg3 circuitery to lower घातer consumption.
 *
 * Returns 0 अगर suspend succeeded, -EIO अगर chip refused suspend
 */
अटल पूर्णांक करोcg3_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	पूर्णांक न्यूनमान, i;
	काष्ठा करोcg3_cascade *cascade;
	काष्ठा mtd_info **करोcg3_न्यूनमानs, *mtd;
	काष्ठा करोcg3 *करोcg3;
	u8 ctrl, pwr_करोwn;

	cascade = platक्रमm_get_drvdata(pdev);
	करोcg3_न्यूनमानs = cascade->न्यूनमानs;
	क्रम (न्यूनमान = 0; न्यूनमान < DOC_MAX_NBFLOORS; न्यूनमान++) अणु
		mtd = करोcg3_न्यूनमानs[न्यूनमान];
		अगर (!mtd)
			जारी;
		करोcg3 = mtd->priv;

		करोc_ग_लिखोb(करोcg3, न्यूनमान, DOC_DEVICESELECT);
		ctrl = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_FLASHCONTROL);
		ctrl &= ~DOC_CTRL_VIOLATION & ~DOC_CTRL_CE;
		करोc_ग_लिखोb(करोcg3, ctrl, DOC_FLASHCONTROL);

		क्रम (i = 0; i < 10; i++) अणु
			usleep_range(3000, 4000);
			pwr_करोwn = करोc_रेजिस्टर_पढ़ोb(करोcg3, DOC_POWERMODE);
			अगर (pwr_करोwn & DOC_POWERDOWN_READY)
				अवरोध;
		पूर्ण
		अगर (pwr_करोwn & DOC_POWERDOWN_READY) अणु
			करोc_dbg("docg3_suspend(): floor %d powerdown ok\n",
				न्यूनमान);
		पूर्ण अन्यथा अणु
			करोc_err("docg3_suspend(): floor %d powerdown failed\n",
				न्यूनमान);
			वापस -EIO;
		पूर्ण
	पूर्ण

	mtd = करोcg3_न्यूनमानs[0];
	करोcg3 = mtd->priv;
	करोc_set_asic_mode(करोcg3, DOC_ASICMODE_POWERDOWN);
	वापस 0;
पूर्ण

/**
 * करोc_probe - Probe the IO space क्रम a DiskOnChip G3 chip
 * @pdev: platक्रमm device
 *
 * Probes क्रम a G3 chip at the specअगरied IO space in the platक्रमm data
 * ressources. The न्यूनमान 0 must be available.
 *
 * Returns 0 on success, -ENOMEM, -ENXIO on error
 */
अटल पूर्णांक __init करोcg3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtd_info *mtd;
	काष्ठा resource *ress;
	व्योम __iomem *base;
	पूर्णांक ret, न्यूनमान;
	काष्ठा करोcg3_cascade *cascade;

	ret = -ENXIO;
	ress = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!ress) अणु
		dev_err(dev, "No I/O memory resource defined\n");
		वापस ret;
	पूर्ण
	base = devm_ioremap(dev, ress->start, DOC_IOSPACE_SIZE);

	ret = -ENOMEM;
	cascade = devm_kसुस्मृति(dev, DOC_MAX_NBFLOORS, माप(*cascade),
			       GFP_KERNEL);
	अगर (!cascade)
		वापस ret;
	cascade->base = base;
	mutex_init(&cascade->lock);
	cascade->bch = bch_init(DOC_ECC_BCH_M, DOC_ECC_BCH_T,
				DOC_ECC_BCH_PRIMPOLY, false);
	अगर (!cascade->bch)
		वापस ret;

	क्रम (न्यूनमान = 0; न्यूनमान < DOC_MAX_NBFLOORS; न्यूनमान++) अणु
		mtd = करोc_probe_device(cascade, न्यूनमान, dev);
		अगर (IS_ERR(mtd)) अणु
			ret = PTR_ERR(mtd);
			जाओ err_probe;
		पूर्ण
		अगर (!mtd) अणु
			अगर (न्यूनमान == 0)
				जाओ notfound;
			अन्यथा
				जारी;
		पूर्ण
		cascade->न्यूनमानs[न्यूनमान] = mtd;
		ret = mtd_device_parse_रेजिस्टर(mtd, part_probes, शून्य, शून्य,
						0);
		अगर (ret)
			जाओ err_probe;

		करोc_dbg_रेजिस्टर(cascade->न्यूनमानs[न्यूनमान]);
	पूर्ण

	ret = करोc_रेजिस्टर_sysfs(pdev, cascade);
	अगर (ret)
		जाओ err_probe;

	platक्रमm_set_drvdata(pdev, cascade);
	वापस 0;

notfound:
	ret = -ENODEV;
	dev_info(dev, "No supported DiskOnChip found\n");
err_probe:
	bch_मुक्त(cascade->bch);
	क्रम (न्यूनमान = 0; न्यूनमान < DOC_MAX_NBFLOORS; न्यूनमान++)
		अगर (cascade->न्यूनमानs[न्यूनमान])
			करोc_release_device(cascade->न्यूनमानs[न्यूनमान]);
	वापस ret;
पूर्ण

/**
 * करोcg3_release - Release the driver
 * @pdev: the platक्रमm device
 *
 * Returns 0
 */
अटल पूर्णांक करोcg3_release(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा करोcg3_cascade *cascade = platक्रमm_get_drvdata(pdev);
	काष्ठा करोcg3 *करोcg3 = cascade->न्यूनमानs[0]->priv;
	पूर्णांक न्यूनमान;

	करोc_unरेजिस्टर_sysfs(pdev, cascade);
	क्रम (न्यूनमान = 0; न्यूनमान < DOC_MAX_NBFLOORS; न्यूनमान++)
		अगर (cascade->न्यूनमानs[न्यूनमान])
			करोc_release_device(cascade->न्यूनमानs[न्यूनमान]);

	bch_मुक्त(करोcg3->cascade->bch);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id करोcg3_dt_ids[] = अणु
	अणु .compatible = "m-systems,diskonchip-g3" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, करोcg3_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver g3_driver = अणु
	.driver		= अणु
		.name	= "docg3",
		.of_match_table = of_match_ptr(करोcg3_dt_ids),
	पूर्ण,
	.suspend	= करोcg3_suspend,
	.resume		= करोcg3_resume,
	.हटाओ		= करोcg3_release,
पूर्ण;

module_platक्रमm_driver_probe(g3_driver, करोcg3_probe);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Robert Jarzmik <robert.jarzmik@free.fr>");
MODULE_DESCRIPTION("MTD driver for DiskOnChip G3");
