<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright तऊ 2009 - Maxim Levitsky
 * Common routines & support क्रम SmartMedia/xD क्रमmat
 */
#समावेश <linux/bitops.h>
#समावेश <linux/mtd/mtd.h>

/* Full oob काष्ठाure as written on the flash */
काष्ठा sm_oob अणु
	uपूर्णांक32_t reserved;
	uपूर्णांक8_t data_status;
	uपूर्णांक8_t block_status;
	uपूर्णांक8_t lba_copy1[2];
	uपूर्णांक8_t ecc2[3];
	uपूर्णांक8_t lba_copy2[2];
	uपूर्णांक8_t ecc1[3];
पूर्ण __packed;


/* one sector is always 512 bytes, but it can consist of two nand pages */
#घोषणा SM_SECTOR_SIZE		512

/* oob area is also 16 bytes, but might be from two pages */
#घोषणा SM_OOB_SIZE		16

/* This is maximum zone size, and all devices that have more that one zone
   have this size */
#घोषणा SM_MAX_ZONE_SIZE 	1024

/* support क्रम small page nand */
#घोषणा SM_SMALL_PAGE 		256
#घोषणा SM_SMALL_OOB_SIZE	8


पूर्णांक sm_रेजिस्टर_device(काष्ठा mtd_info *mtd, पूर्णांक smarपंचांगedia);


अटल अंतरभूत पूर्णांक sm_sector_valid(काष्ठा sm_oob *oob)
अणु
	वापस hweight16(oob->data_status) >= 5;
पूर्ण

अटल अंतरभूत पूर्णांक sm_block_valid(काष्ठा sm_oob *oob)
अणु
	वापस hweight16(oob->block_status) >= 7;
पूर्ण

अटल अंतरभूत पूर्णांक sm_block_erased(काष्ठा sm_oob *oob)
अणु
	अटल स्थिर uपूर्णांक32_t erased_pattern[4] = अणु
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण;

	/* First test क्रम erased block */
	अगर (!स_भेद(oob, erased_pattern, माप(*oob)))
		वापस 1;
	वापस 0;
पूर्ण
