<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright तऊ 1999-2010 David Woodhouse <dwmw2@infradead.org>
 */

#अगर_अघोषित __MTD_NFTL_H__
#घोषणा __MTD_NFTL_H__

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/blktrans.h>

#समावेश <mtd/nftl-user.h>

/* these info are used in ReplUnitTable */
#घोषणा BLOCK_NIL          0xffff /* last block of a chain */
#घोषणा BLOCK_FREE         0xfffe /* मुक्त block */
#घोषणा BLOCK_NOTEXPLORED  0xfffd /* non explored block, only used during mounting */
#घोषणा BLOCK_RESERVED     0xfffc /* bios block or bad block */

काष्ठा NFTLrecord अणु
	काष्ठा mtd_blktrans_dev mbd;
	__u16 MediaUnit, SpareMediaUnit;
	__u32 EraseSize;
	काष्ठा NFTLMediaHeader MediaHdr;
	पूर्णांक usecount;
	अचिन्हित अक्षर heads;
	अचिन्हित अक्षर sectors;
	अचिन्हित लघु cylinders;
	__u16 numvunits;
	__u16 lastEUN;                  /* should be suppressed */
	__u16 numमुक्तEUNs;
	__u16 LastFreeEUN; 		/* To speed up finding a मुक्त EUN */
	पूर्णांक head,sect,cyl;
	__u16 *EUNtable; 		/* [numvunits]: First EUN क्रम each भव unit  */
	__u16 *ReplUnitTable; 		/* [numEUNs]: ReplUnitNumber क्रम each */
        अचिन्हित पूर्णांक nb_blocks;		/* number of physical blocks */
        अचिन्हित पूर्णांक nb_boot_blocks;	/* number of blocks used by the bios */
        काष्ठा erase_info instr;
पूर्ण;

पूर्णांक NFTL_mount(काष्ठा NFTLrecord *s);
पूर्णांक NFTL_क्रमmatblock(काष्ठा NFTLrecord *s, पूर्णांक block);

पूर्णांक nftl_पढ़ो_oob(काष्ठा mtd_info *mtd, loff_t offs, माप_प्रकार len,
		  माप_प्रकार *retlen, uपूर्णांक8_t *buf);
पूर्णांक nftl_ग_लिखो_oob(काष्ठा mtd_info *mtd, loff_t offs, माप_प्रकार len,
		   माप_प्रकार *retlen, uपूर्णांक8_t *buf);

#अगर_अघोषित NFTL_MAJOR
#घोषणा NFTL_MAJOR 93
#पूर्ण_अगर

#घोषणा MAX_NFTLS 16
#घोषणा MAX_SECTORS_PER_UNIT 64
#घोषणा NFTL_PARTN_BITS 4

#पूर्ण_अगर /* __MTD_NFTL_H__ */
