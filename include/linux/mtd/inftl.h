<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	inftl.h -- defines to support the Inverse न_अंकD Flash Translation Layer
 *
 *	(C) Copyright 2002, Greg Ungerer (gerg@snapgear.com)
 */

#अगर_अघोषित __MTD_INFTL_H__
#घोषणा __MTD_INFTL_H__

#अगर_अघोषित __KERNEL__
#त्रुटि This is a kernel header. Perhaps include nftl-user.h instead?
#पूर्ण_अगर

#समावेश <linux/mtd/blktrans.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nftl.h>

#समावेश <mtd/inftl-user.h>

#अगर_अघोषित INFTL_MAJOR
#घोषणा INFTL_MAJOR 96
#पूर्ण_अगर
#घोषणा INFTL_PARTN_BITS 4

#अगर_घोषित __KERNEL__

काष्ठा INFTLrecord अणु
	काष्ठा mtd_blktrans_dev mbd;
	__u16 MediaUnit;
	__u32 EraseSize;
	काष्ठा INFTLMediaHeader MediaHdr;
	पूर्णांक usecount;
	अचिन्हित अक्षर heads;
	अचिन्हित अक्षर sectors;
	अचिन्हित लघु cylinders;
	__u16 numvunits;
	__u16 firstEUN;
	__u16 lastEUN;
	__u16 numमुक्तEUNs;
	__u16 LastFreeEUN;		/* To speed up finding a मुक्त EUN */
	पूर्णांक head,sect,cyl;
	__u16 *PUtable;			/* Physical Unit Table */
	__u16 *VUtable;			/* Virtual Unit Table */
	अचिन्हित पूर्णांक nb_blocks;		/* number of physical blocks */
	अचिन्हित पूर्णांक nb_boot_blocks;	/* number of blocks used by the bios */
	काष्ठा erase_info instr;
पूर्ण;

पूर्णांक INFTL_mount(काष्ठा INFTLrecord *s);
पूर्णांक INFTL_क्रमmatblock(काष्ठा INFTLrecord *s, पूर्णांक block);

व्योम INFTL_dumptables(काष्ठा INFTLrecord *s);
व्योम INFTL_dumpVUchains(काष्ठा INFTLrecord *s);

पूर्णांक inftl_पढ़ो_oob(काष्ठा mtd_info *mtd, loff_t offs, माप_प्रकार len,
		   माप_प्रकार *retlen, uपूर्णांक8_t *buf);
पूर्णांक inftl_ग_लिखो_oob(काष्ठा mtd_info *mtd, loff_t offs, माप_प्रकार len,
		    माप_प्रकार *retlen, uपूर्णांक8_t *buf);

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __MTD_INFTL_H__ */
