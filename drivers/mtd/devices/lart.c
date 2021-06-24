<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * MTD driver क्रम the 28F160F3 Flash Memory (non-CFI) on LART.
 *
 * Author: Abraham vd Merwe <abraham@2d3d.co.za>
 *
 * Copyright (c) 2001, 2d3D, Inc.
 *
 * References:
 *
 *    [1] 3 Volt Fast Boot Block Flash Memory" Intel Datasheet
 *           - Order Number: 290644-005
 *           - January 2000
 *
 *    [2] MTD पूर्णांकernal API करोcumentation
 *           - http://www.linux-mtd.infradead.org/ 
 *
 * Limitations:
 *
 *    Even though this driver is written क्रम 3 Volt Fast Boot
 *    Block Flash Memory, it is rather specअगरic to LART. With
 *    Minor modअगरications, notably the without data/address line
 *    mangling and dअगरferent bus settings, etc. it should be
 *    trivial to adapt to other platक्रमms.
 *
 *    If somebody would sponsor me a dअगरferent board, I'll
 *    adapt the driver (:
 */

/* debugging */
//#घोषणा LART_DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>

#अगर_अघोषित CONFIG_SA1100_LART
#त्रुटि This is क्रम LART architecture only
#पूर्ण_अगर

अटल अक्षर module_name[] = "lart";

/*
 * These values is specअगरic to 28Fxxxx3 flash memory.
 * See section 2.3.1 in "3 Volt Fast Boot Block Flash Memory" Intel Datasheet
 */
#घोषणा FLASH_BLOCKSIZE_PARAM		(4096 * BUSWIDTH)
#घोषणा FLASH_NUMBLOCKS_16m_PARAM	8
#घोषणा FLASH_NUMBLOCKS_8m_PARAM	8

/*
 * These values is specअगरic to 28Fxxxx3 flash memory.
 * See section 2.3.2 in "3 Volt Fast Boot Block Flash Memory" Intel Datasheet
 */
#घोषणा FLASH_BLOCKSIZE_MAIN		(32768 * BUSWIDTH)
#घोषणा FLASH_NUMBLOCKS_16m_MAIN	31
#घोषणा FLASH_NUMBLOCKS_8m_MAIN		15

/*
 * These values are specअगरic to LART
 */

/* general */
#घोषणा BUSWIDTH			4				/* करोn't change this - a lot of the code _will_ अवरोध अगर you change this */
#घोषणा FLASH_OFFSET		0xe8000000		/* see linux/arch/arm/mach-sa1100/lart.c */

/* blob */
#घोषणा NUM_BLOB_BLOCKS		FLASH_NUMBLOCKS_16m_PARAM
#घोषणा PART_BLOB_START		0x00000000
#घोषणा PART_BLOB_LEN		(NUM_BLOB_BLOCKS * FLASH_BLOCKSIZE_PARAM)

/* kernel */
#घोषणा NUM_KERNEL_BLOCKS	7
#घोषणा PART_KERNEL_START	(PART_BLOB_START + PART_BLOB_LEN)
#घोषणा PART_KERNEL_LEN		(NUM_KERNEL_BLOCKS * FLASH_BLOCKSIZE_MAIN)

/* initial ramdisk */
#घोषणा NUM_INITRD_BLOCKS	24
#घोषणा PART_INITRD_START	(PART_KERNEL_START + PART_KERNEL_LEN)
#घोषणा PART_INITRD_LEN		(NUM_INITRD_BLOCKS * FLASH_BLOCKSIZE_MAIN)

/*
 * See section 4.0 in "3 Volt Fast Boot Block Flash Memory" Intel Datasheet
 */
#घोषणा READ_ARRAY			0x00FF00FF		/* Read Array/Reset */
#घोषणा READ_ID_CODES		0x00900090		/* Read Identअगरier Codes */
#घोषणा ERASE_SETUP			0x00200020		/* Block Erase */
#घोषणा ERASE_CONFIRM		0x00D000D0		/* Block Erase and Program Resume */
#घोषणा PGM_SETUP			0x00400040		/* Program */
#घोषणा STATUS_READ			0x00700070		/* Read Status Register */
#घोषणा STATUS_CLEAR		0x00500050		/* Clear Status Register */
#घोषणा STATUS_BUSY			0x00800080		/* Write State Machine Status (WSMS) */
#घोषणा STATUS_ERASE_ERR	0x00200020		/* Erase Status (ES) */
#घोषणा STATUS_PGM_ERR		0x00100010		/* Program Status (PS) */

/*
 * See section 4.2 in "3 Volt Fast Boot Block Flash Memory" Intel Datasheet
 */
#घोषणा FLASH_MANUFACTURER			0x00890089
#घोषणा FLASH_DEVICE_8mbit_TOP		0x88f188f1
#घोषणा FLASH_DEVICE_8mbit_BOTTOM	0x88f288f2
#घोषणा FLASH_DEVICE_16mbit_TOP		0x88f388f3
#घोषणा FLASH_DEVICE_16mbit_BOTTOM	0x88f488f4

/***************************************************************************************************/

/*
 * The data line mapping on LART is as follows:
 *
 *   	 U2  CPU |   U3  CPU
 *   	 -------------------
 *   	  0  20  |   0   12
 *   	  1  22  |   1   14
 *   	  2  19  |   2   11
 *   	  3  17  |   3   9
 *   	  4  24  |   4   0
 *   	  5  26  |   5   2
 *   	  6  31  |   6   7
 *   	  7  29  |   7   5
 *   	  8  21  |   8   13
 *   	  9  23  |   9   15
 *   	  10 18  |   10  10
 *   	  11 16  |   11  8
 *   	  12 25  |   12  1
 *   	  13 27  |   13  3
 *   	  14 30  |   14  6
 *   	  15 28  |   15  4
 */

/* Mangle data (x) */
#घोषणा DATA_TO_FLASH(x)				\
	(									\
		(((x) & 0x08009000) >> 11)	+	\
		(((x) & 0x00002000) >> 10)	+	\
		(((x) & 0x04004000) >> 8)	+	\
		(((x) & 0x00000010) >> 4)	+	\
		(((x) & 0x91000820) >> 3)	+	\
		(((x) & 0x22080080) >> 2)	+	\
		((x) & 0x40000400)			+	\
		(((x) & 0x00040040) << 1)	+	\
		(((x) & 0x00110000) << 4)	+	\
		(((x) & 0x00220100) << 5)	+	\
		(((x) & 0x00800208) << 6)	+	\
		(((x) & 0x00400004) << 9)	+	\
		(((x) & 0x00000001) << 12)	+	\
		(((x) & 0x00000002) << 13)		\
	)

/* Unmangle data (x) */
#घोषणा FLASH_TO_DATA(x)				\
	(									\
		(((x) & 0x00010012) << 11)	+	\
		(((x) & 0x00000008) << 10)	+	\
		(((x) & 0x00040040) << 8)	+	\
		(((x) & 0x00000001) << 4)	+	\
		(((x) & 0x12200104) << 3)	+	\
		(((x) & 0x08820020) << 2)	+	\
		((x) & 0x40000400)			+	\
		(((x) & 0x00080080) >> 1)	+	\
		(((x) & 0x01100000) >> 4)	+	\
		(((x) & 0x04402000) >> 5)	+	\
		(((x) & 0x20008200) >> 6)	+	\
		(((x) & 0x80000800) >> 9)	+	\
		(((x) & 0x00001000) >> 12)	+	\
		(((x) & 0x00004000) >> 13)		\
	)

/*
 * The address line mapping on LART is as follows:
 *
 *   	 U3  CPU |   U2  CPU
 *   	 -------------------
 *   	  0  2   |   0   2
 *   	  1  3   |   1   3
 *   	  2  9   |   2   9
 *   	  3  13  |   3   8
 *   	  4  8   |   4   7
 *   	  5  12  |   5   6
 *   	  6  11  |   6   5
 *   	  7  10  |   7   4
 *   	  8  4   |   8   10
 *   	  9  5   |   9   11
 *   	 10  6   |   10  12
 *   	 11  7   |   11  13
 *
 *   	 BOOT BLOCK BOUNDARY
 *
 *   	 12  15  |   12  15
 *   	 13  14  |   13  14
 *   	 14  16  |   14  16
 *
 *   	 MAIN BLOCK BOUNDARY
 *
 *   	 15  17  |   15  18
 *   	 16  18  |   16  17
 *   	 17  20  |   17  20
 *   	 18  19  |   18  19
 *   	 19  21  |   19  21
 *
 * As we can see from above, the addresses aren't mangled across
 * block boundaries, so we करोn't need to worry about address
 * translations except क्रम sending/पढ़ोing commands during
 * initialization
 */

/* Mangle address (x) on chip U2 */
#घोषणा ADDR_TO_FLASH_U2(x)				\
	(									\
		(((x) & 0x00000f00) >> 4)	+	\
		(((x) & 0x00042000) << 1)	+	\
		(((x) & 0x0009c003) << 2)	+	\
		(((x) & 0x00021080) << 3)	+	\
		(((x) & 0x00000010) << 4)	+	\
		(((x) & 0x00000040) << 5)	+	\
		(((x) & 0x00000024) << 7)	+	\
		(((x) & 0x00000008) << 10)		\
	)

/* Unmangle address (x) on chip U2 */
#घोषणा FLASH_U2_TO_ADDR(x)				\
	(									\
		(((x) << 4) & 0x00000f00)	+	\
		(((x) >> 1) & 0x00042000)	+	\
		(((x) >> 2) & 0x0009c003)	+	\
		(((x) >> 3) & 0x00021080)	+	\
		(((x) >> 4) & 0x00000010)	+	\
		(((x) >> 5) & 0x00000040)	+	\
		(((x) >> 7) & 0x00000024)	+	\
		(((x) >> 10) & 0x00000008)		\
	)

/* Mangle address (x) on chip U3 */
#घोषणा ADDR_TO_FLASH_U3(x)				\
	(									\
		(((x) & 0x00000080) >> 3)	+	\
		(((x) & 0x00000040) >> 1)	+	\
		(((x) & 0x00052020) << 1)	+	\
		(((x) & 0x00084f03) << 2)	+	\
		(((x) & 0x00029010) << 3)	+	\
		(((x) & 0x00000008) << 5)	+	\
		(((x) & 0x00000004) << 7)		\
	)

/* Unmangle address (x) on chip U3 */
#घोषणा FLASH_U3_TO_ADDR(x)				\
	(									\
		(((x) << 3) & 0x00000080)	+	\
		(((x) << 1) & 0x00000040)	+	\
		(((x) >> 1) & 0x00052020)	+	\
		(((x) >> 2) & 0x00084f03)	+	\
		(((x) >> 3) & 0x00029010)	+	\
		(((x) >> 5) & 0x00000008)	+	\
		(((x) >> 7) & 0x00000004)		\
	)

/***************************************************************************************************/

अटल __u8 पढ़ो8 (__u32 offset)
अणु
   अस्थिर __u8 *data = (__u8 *) (FLASH_OFFSET + offset);
#अगर_घोषित LART_DEBUG
   prपूर्णांकk (KERN_DEBUG "%s(): 0x%.8x -> 0x%.2x\n", __func__, offset, *data);
#पूर्ण_अगर
   वापस (*data);
पूर्ण

अटल __u32 पढ़ो32 (__u32 offset)
अणु
   अस्थिर __u32 *data = (__u32 *) (FLASH_OFFSET + offset);
#अगर_घोषित LART_DEBUG
   prपूर्णांकk (KERN_DEBUG "%s(): 0x%.8x -> 0x%.8x\n", __func__, offset, *data);
#पूर्ण_अगर
   वापस (*data);
पूर्ण

अटल व्योम ग_लिखो32 (__u32 x,__u32 offset)
अणु
   अस्थिर __u32 *data = (__u32 *) (FLASH_OFFSET + offset);
   *data = x;
#अगर_घोषित LART_DEBUG
   prपूर्णांकk (KERN_DEBUG "%s(): 0x%.8x <- 0x%.8x\n", __func__, offset, *data);
#पूर्ण_अगर
पूर्ण

/***************************************************************************************************/

/*
 * Probe क्रम 16mbit flash memory on a LART board without करोing
 * too much damage. Since we need to ग_लिखो 1 dword to memory,
 * we're f**cked if this happens to be DRAM since we can't
 * restore the memory (otherwise we might निकास Read Array mode).
 *
 * Returns 1 अगर we found 16mbit flash memory on LART, 0 otherwise.
 */
अटल पूर्णांक flash_probe (व्योम)
अणु
   __u32 manufacturer,devtype;

   /* setup "Read Identifier Codes" mode */
   ग_लिखो32 (DATA_TO_FLASH (READ_ID_CODES),0x00000000);

   /* probe U2. U2/U3 वापसs the same data since the first 3
	* address lines is mangled in the same way */
   manufacturer = FLASH_TO_DATA (पढ़ो32 (ADDR_TO_FLASH_U2 (0x00000000)));
   devtype = FLASH_TO_DATA (पढ़ो32 (ADDR_TO_FLASH_U2 (0x00000001)));

   /* put the flash back पूर्णांकo command mode */
   ग_लिखो32 (DATA_TO_FLASH (READ_ARRAY),0x00000000);

   वापस (manufacturer == FLASH_MANUFACTURER && (devtype == FLASH_DEVICE_16mbit_TOP || devtype == FLASH_DEVICE_16mbit_BOTTOM));
पूर्ण

/*
 * Erase one block of flash memory at offset ``offset'' which is any
 * address within the block which should be erased.
 *
 * Returns 1 अगर successful, 0 otherwise.
 */
अटल अंतरभूत पूर्णांक erase_block (__u32 offset)
अणु
   __u32 status;

#अगर_घोषित LART_DEBUG
   prपूर्णांकk (KERN_DEBUG "%s(): 0x%.8x\n", __func__, offset);
#पूर्ण_अगर

   /* erase and confirm */
   ग_लिखो32 (DATA_TO_FLASH (ERASE_SETUP),offset);
   ग_लिखो32 (DATA_TO_FLASH (ERASE_CONFIRM),offset);

   /* रुको क्रम block erase to finish */
   करो
	 अणु
		ग_लिखो32 (DATA_TO_FLASH (STATUS_READ),offset);
		status = FLASH_TO_DATA (पढ़ो32 (offset));
	 पूर्ण
   जबतक ((~status & STATUS_BUSY) != 0);

   /* put the flash back पूर्णांकo command mode */
   ग_लिखो32 (DATA_TO_FLASH (READ_ARRAY),offset);

   /* was the erase successful? */
   अगर ((status & STATUS_ERASE_ERR))
	 अणु
		prपूर्णांकk (KERN_WARNING "%s: erase error at address 0x%.8x.\n",module_name,offset);
		वापस (0);
	 पूर्ण

   वापस (1);
पूर्ण

अटल पूर्णांक flash_erase (काष्ठा mtd_info *mtd,काष्ठा erase_info *instr)
अणु
   __u32 addr,len;
   पूर्णांक i,first;

#अगर_घोषित LART_DEBUG
   prपूर्णांकk (KERN_DEBUG "%s(addr = 0x%.8x, len = %d)\n", __func__, instr->addr, instr->len);
#पूर्ण_अगर

   /*
	* check that both start and end of the requested erase are
	* aligned with the erasesize at the appropriate addresses.
	*
	* skip all erase regions which are ended beक्रमe the start of
	* the requested erase. Actually, to save on the calculations,
	* we skip to the first erase region which starts after the
	* start of the requested erase, and then go back one.
	*/
   क्रम (i = 0; i < mtd->numeraseregions && instr->addr >= mtd->eraseregions[i].offset; i++) ;
   i--;

   /*
	* ok, now i is poपूर्णांकing at the erase region in which this
	* erase request starts. Check the start of the requested
	* erase range is aligned with the erase size which is in
	* effect here.
	*/
   अगर (i < 0 || (instr->addr & (mtd->eraseregions[i].erasesize - 1)))
      वापस -EINVAL;

   /* Remember the erase region we start on */
   first = i;

   /*
	* next, check that the end of the requested erase is aligned
	* with the erase region at that address.
	*
	* as beक्रमe, drop back one to poपूर्णांक at the region in which
	* the address actually falls
	*/
   क्रम (; i < mtd->numeraseregions && instr->addr + instr->len >= mtd->eraseregions[i].offset; i++) ;
   i--;

   /* is the end aligned on a block boundary? */
   अगर (i < 0 || ((instr->addr + instr->len) & (mtd->eraseregions[i].erasesize - 1)))
      वापस -EINVAL;

   addr = instr->addr;
   len = instr->len;

   i = first;

   /* now erase those blocks */
   जबतक (len)
	 अणु
		अगर (!erase_block (addr))
			 वापस (-EIO);

		addr += mtd->eraseregions[i].erasesize;
		len -= mtd->eraseregions[i].erasesize;

		अगर (addr == mtd->eraseregions[i].offset + (mtd->eraseregions[i].erasesize * mtd->eraseregions[i].numblocks)) i++;
	 पूर्ण

   वापस (0);
पूर्ण

अटल पूर्णांक flash_पढ़ो (काष्ठा mtd_info *mtd,loff_t from,माप_प्रकार len,माप_प्रकार *retlen,u_अक्षर *buf)
अणु
#अगर_घोषित LART_DEBUG
   prपूर्णांकk (KERN_DEBUG "%s(from = 0x%.8x, len = %d)\n", __func__, (__u32)from, len);
#पूर्ण_अगर

   /* we always पढ़ो len bytes */
   *retlen = len;

   /* first, we पढ़ो bytes until we reach a dword boundary */
   अगर (from & (BUSWIDTH - 1))
	 अणु
		पूर्णांक gap = BUSWIDTH - (from & (BUSWIDTH - 1));

		जबतक (len && gap--) अणु
			*buf++ = पढ़ो8 (from++);
			len--;
		पूर्ण
	 पूर्ण

   /* now we पढ़ो dwords until we reach a non-dword boundary */
   जबतक (len >= BUSWIDTH)
	 अणु
		*((__u32 *) buf) = पढ़ो32 (from);

		buf += BUSWIDTH;
		from += BUSWIDTH;
		len -= BUSWIDTH;
	 पूर्ण

   /* top up the last unaligned bytes */
   अगर (len & (BUSWIDTH - 1))
	 जबतक (len--) *buf++ = पढ़ो8 (from++);

   वापस (0);
पूर्ण

/*
 * Write one dword ``x'' to flash memory at offset ``offset''. ``offset''
 * must be 32 bits, i.e. it must be on a dword boundary.
 *
 * Returns 1 अगर successful, 0 otherwise.
 */
अटल अंतरभूत पूर्णांक ग_लिखो_dword (__u32 offset,__u32 x)
अणु
   __u32 status;

#अगर_घोषित LART_DEBUG
   prपूर्णांकk (KERN_DEBUG "%s(): 0x%.8x <- 0x%.8x\n", __func__, offset, x);
#पूर्ण_अगर

   /* setup writing */
   ग_लिखो32 (DATA_TO_FLASH (PGM_SETUP),offset);

   /* ग_लिखो the data */
   ग_लिखो32 (x,offset);

   /* रुको क्रम the ग_लिखो to finish */
   करो
	 अणु
		ग_लिखो32 (DATA_TO_FLASH (STATUS_READ),offset);
		status = FLASH_TO_DATA (पढ़ो32 (offset));
	 पूर्ण
   जबतक ((~status & STATUS_BUSY) != 0);

   /* put the flash back पूर्णांकo command mode */
   ग_लिखो32 (DATA_TO_FLASH (READ_ARRAY),offset);

   /* was the ग_लिखो successful? */
   अगर ((status & STATUS_PGM_ERR) || पढ़ो32 (offset) != x)
	 अणु
		prपूर्णांकk (KERN_WARNING "%s: write error at address 0x%.8x.\n",module_name,offset);
		वापस (0);
	 पूर्ण

   वापस (1);
पूर्ण

अटल पूर्णांक flash_ग_लिखो (काष्ठा mtd_info *mtd,loff_t to,माप_प्रकार len,माप_प्रकार *retlen,स्थिर u_अक्षर *buf)
अणु
   __u8 पंचांगp[4];
   पूर्णांक i,n;

#अगर_घोषित LART_DEBUG
   prपूर्णांकk (KERN_DEBUG "%s(to = 0x%.8x, len = %d)\n", __func__, (__u32)to, len);
#पूर्ण_अगर

   /* sanity checks */
   अगर (!len) वापस (0);

   /* first, we ग_लिखो a 0xFF.... padded byte until we reach a dword boundary */
   अगर (to & (BUSWIDTH - 1))
	 अणु
		__u32 aligned = to & ~(BUSWIDTH - 1);
		पूर्णांक gap = to - aligned;

		i = n = 0;

		जबतक (gap--) पंचांगp[i++] = 0xFF;
		जबतक (len && i < BUSWIDTH) अणु
			पंचांगp[i++] = buf[n++];
			len--;
		पूर्ण
		जबतक (i < BUSWIDTH) पंचांगp[i++] = 0xFF;

		अगर (!ग_लिखो_dword (aligned,*((__u32 *) पंचांगp))) वापस (-EIO);

		to += n;
		buf += n;
		*retlen += n;
	 पूर्ण

   /* now we ग_लिखो dwords until we reach a non-dword boundary */
   जबतक (len >= BUSWIDTH)
	 अणु
		अगर (!ग_लिखो_dword (to,*((__u32 *) buf))) वापस (-EIO);

		to += BUSWIDTH;
		buf += BUSWIDTH;
		*retlen += BUSWIDTH;
		len -= BUSWIDTH;
	 पूर्ण

   /* top up the last unaligned bytes, padded with 0xFF.... */
   अगर (len & (BUSWIDTH - 1))
	 अणु
		i = n = 0;

		जबतक (len--) पंचांगp[i++] = buf[n++];
		जबतक (i < BUSWIDTH) पंचांगp[i++] = 0xFF;

		अगर (!ग_लिखो_dword (to,*((__u32 *) पंचांगp))) वापस (-EIO);

		*retlen += n;
	 पूर्ण

   वापस (0);
पूर्ण

/***************************************************************************************************/

अटल काष्ठा mtd_info mtd;

अटल काष्ठा mtd_erase_region_info erase_regions[] = अणु
	/* parameter blocks */
	अणु
		.offset		= 0x00000000,
		.erasesize	= FLASH_BLOCKSIZE_PARAM,
		.numblocks	= FLASH_NUMBLOCKS_16m_PARAM,
	पूर्ण,
	/* मुख्य blocks */
	अणु
		.offset	 = FLASH_BLOCKSIZE_PARAM * FLASH_NUMBLOCKS_16m_PARAM,
		.erasesize	= FLASH_BLOCKSIZE_MAIN,
		.numblocks	= FLASH_NUMBLOCKS_16m_MAIN,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा mtd_partition lart_partitions[] = अणु
	/* blob */
	अणु
		.name	= "blob",
		.offset	= PART_BLOB_START,
		.size	= PART_BLOB_LEN,
	पूर्ण,
	/* kernel */
	अणु
		.name	= "kernel",
		.offset	= PART_KERNEL_START,	/* MTDPART_OFS_APPEND */
		.size	= PART_KERNEL_LEN,
	पूर्ण,
	/* initial ramdisk / file प्रणाली */
	अणु
		.name	= "file system",
		.offset	= PART_INITRD_START,	/* MTDPART_OFS_APPEND */
		.size	= PART_INITRD_LEN,	/* MTDPART_SIZ_FULL */
	पूर्ण
पूर्ण;
#घोषणा NUM_PARTITIONS ARRAY_SIZE(lart_partitions)

अटल पूर्णांक __init lart_flash_init (व्योम)
अणु
   पूर्णांक result;
   स_रखो (&mtd,0,माप (mtd));
   prपूर्णांकk ("MTD driver for LART. Written by Abraham vd Merwe <abraham@2d3d.co.za>\n");
   prपूर्णांकk ("%s: Probing for 28F160x3 flash on LART...\n",module_name);
   अगर (!flash_probe ())
	 अणु
		prपूर्णांकk (KERN_WARNING "%s: Found no LART compatible flash device\n",module_name);
		वापस (-ENXIO);
	 पूर्ण
   prपूर्णांकk ("%s: This looks like a LART board to me.\n",module_name);
   mtd.name = module_name;
   mtd.type = MTD_NORFLASH;
   mtd.ग_लिखोsize = 1;
   mtd.ग_लिखोbufsize = 4;
   mtd.flags = MTD_CAP_NORFLASH;
   mtd.size = FLASH_BLOCKSIZE_PARAM * FLASH_NUMBLOCKS_16m_PARAM + FLASH_BLOCKSIZE_MAIN * FLASH_NUMBLOCKS_16m_MAIN;
   mtd.erasesize = FLASH_BLOCKSIZE_MAIN;
   mtd.numeraseregions = ARRAY_SIZE(erase_regions);
   mtd.eraseregions = erase_regions;
   mtd._erase = flash_erase;
   mtd._पढ़ो = flash_पढ़ो;
   mtd._ग_लिखो = flash_ग_लिखो;
   mtd.owner = THIS_MODULE;

#अगर_घोषित LART_DEBUG
   prपूर्णांकk (KERN_DEBUG
		   "mtd.name = %s\n"
		   "mtd.size = 0x%.8x (%uM)\n"
		   "mtd.erasesize = 0x%.8x (%uK)\n"
		   "mtd.numeraseregions = %d\n",
		   mtd.name,
		   mtd.size,mtd.size / (1024*1024),
		   mtd.erasesize,mtd.erasesize / 1024,
		   mtd.numeraseregions);

   अगर (mtd.numeraseregions)
	 क्रम (result = 0; result < mtd.numeraseregions; result++)
	   prपूर्णांकk (KERN_DEBUG
			   "\n\n"
			   "mtd.eraseregions[%d].offset = 0x%.8x\n"
			   "mtd.eraseregions[%d].erasesize = 0x%.8x (%uK)\n"
			   "mtd.eraseregions[%d].numblocks = %d\n",
			   result,mtd.eraseregions[result].offset,
			   result,mtd.eraseregions[result].erasesize,mtd.eraseregions[result].erasesize / 1024,
			   result,mtd.eraseregions[result].numblocks);

   prपूर्णांकk ("\npartitions = %d\n", ARRAY_SIZE(lart_partitions));

   क्रम (result = 0; result < ARRAY_SIZE(lart_partitions); result++)
	 prपूर्णांकk (KERN_DEBUG
			 "\n\n"
			 "lart_partitions[%d].name = %s\n"
			 "lart_partitions[%d].offset = 0x%.8x\n"
			 "lart_partitions[%d].size = 0x%.8x (%uK)\n",
			 result,lart_partitions[result].name,
			 result,lart_partitions[result].offset,
			 result,lart_partitions[result].size,lart_partitions[result].size / 1024);
#पूर्ण_अगर

   result = mtd_device_रेजिस्टर(&mtd, lart_partitions,
                                ARRAY_SIZE(lart_partitions));

   वापस (result);
पूर्ण

अटल व्योम __निकास lart_flash_निकास (व्योम)
अणु
   mtd_device_unरेजिस्टर(&mtd);
पूर्ण

module_init (lart_flash_init);
module_निकास (lart_flash_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abraham vd Merwe <abraham@2d3d.co.za>");
MODULE_DESCRIPTION("MTD driver for Intel 28F160F3 on LART board");
