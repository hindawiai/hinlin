<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * तऊ Copyright 2016 ATMEL
 * तऊ Copyright 2016 Free Electrons
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 *
 * Derived from the aपंचांगel_nand.c driver which contained the following
 * copyrights:
 *
 *    Copyright तऊ 2003 Rick Bronson
 *
 *    Derived from drivers/mtd/nand/autcpu12.c (हटाओd in v3.8)
 *        Copyright तऊ 2001 Thomas Gleixner (gleixner@autronix.de)
 *
 *    Derived from drivers/mtd/spia.c (हटाओd in v3.8)
 *        Copyright तऊ 2000 Steven J. Hill (sjhill@cotw.com)
 *
 *
 *    Add Hardware ECC support क्रम AT91SAM9260 / AT91SAM9263
 *        Riअक्षरd Genoud (riअक्षरd.genoud@gmail.com), Adeneo Copyright तऊ 2007
 *
 *        Derived from Das U-Boot source code
 *              (u-boot-1.1.5/board/aपंचांगel/at91sam9263ek/nand.c)
 *        तऊ Copyright 2006 ATMEL Rousset, Lacressonniere Nicolas
 *
 *    Add Programmable Multibit ECC support क्रम various AT91 SoC
 *        तऊ Copyright 2012 ATMEL, Hong Xu
 *
 *    Add Nand Flash Controller support क्रम SAMA5 SoC
 *        तऊ Copyright 2013 ATMEL, Josh Wu (josh.wu@aपंचांगel.com)
 */

#अगर_अघोषित ATMEL_PMECC_H
#घोषणा ATMEL_PMECC_H

#घोषणा ATMEL_PMECC_MAXIMIZE_ECC_STRENGTH	0
#घोषणा ATMEL_PMECC_SECTOR_SIZE_AUTO		0
#घोषणा ATMEL_PMECC_OOBOFFSET_AUTO		-1

काष्ठा aपंचांगel_pmecc_user_req अणु
	पूर्णांक pagesize;
	पूर्णांक oobsize;
	काष्ठा अणु
		पूर्णांक strength;
		पूर्णांक bytes;
		पूर्णांक sectorsize;
		पूर्णांक nsectors;
		पूर्णांक ooboffset;
	पूर्ण ecc;
पूर्ण;

काष्ठा aपंचांगel_pmecc *devm_aपंचांगel_pmecc_get(काष्ठा device *dev);

काष्ठा aपंचांगel_pmecc_user *
aपंचांगel_pmecc_create_user(काष्ठा aपंचांगel_pmecc *pmecc,
			काष्ठा aपंचांगel_pmecc_user_req *req);
व्योम aपंचांगel_pmecc_destroy_user(काष्ठा aपंचांगel_pmecc_user *user);

व्योम aपंचांगel_pmecc_reset(काष्ठा aपंचांगel_pmecc *pmecc);
पूर्णांक aपंचांगel_pmecc_enable(काष्ठा aपंचांगel_pmecc_user *user, पूर्णांक op);
व्योम aपंचांगel_pmecc_disable(काष्ठा aपंचांगel_pmecc_user *user);
पूर्णांक aपंचांगel_pmecc_रुको_rdy(काष्ठा aपंचांगel_pmecc_user *user);
पूर्णांक aपंचांगel_pmecc_correct_sector(काष्ठा aपंचांगel_pmecc_user *user, पूर्णांक sector,
			       व्योम *data, व्योम *ecc);
bool aपंचांगel_pmecc_correct_erased_chunks(काष्ठा aपंचांगel_pmecc_user *user);
व्योम aपंचांगel_pmecc_get_generated_eccbytes(काष्ठा aपंचांगel_pmecc_user *user,
					पूर्णांक sector, व्योम *ecc);

#पूर्ण_अगर /* ATMEL_PMECC_H */
