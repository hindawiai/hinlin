<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Linux driver क्रम Disk-On-Chip devices
 *
 * Copyright तऊ 1999 Machine Vision Holdings, Inc.
 * Copyright तऊ 1999-2010 David Woodhouse <dwmw2@infradead.org>
 * Copyright तऊ 2002-2003 Greg Ungerer <gerg@snapgear.com>
 * Copyright तऊ 2002-2003 SnapGear Inc
 */

#अगर_अघोषित __MTD_DOC2000_H__
#घोषणा __MTD_DOC2000_H__

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mutex.h>

#घोषणा DoC_Sig1 0
#घोषणा DoC_Sig2 1

#घोषणा DoC_ChipID		0x1000
#घोषणा DoC_DOCStatus		0x1001
#घोषणा DoC_DOCControl		0x1002
#घोषणा DoC_FloorSelect		0x1003
#घोषणा DoC_CDSNControl		0x1004
#घोषणा DoC_CDSNDeviceSelect 	0x1005
#घोषणा DoC_ECCConf 		0x1006
#घोषणा DoC_2k_ECCStatus	0x1007

#घोषणा DoC_CDSNSlowIO		0x100d
#घोषणा DoC_ECCSyndrome0	0x1010
#घोषणा DoC_ECCSyndrome1	0x1011
#घोषणा DoC_ECCSyndrome2	0x1012
#घोषणा DoC_ECCSyndrome3	0x1013
#घोषणा DoC_ECCSyndrome4	0x1014
#घोषणा DoC_ECCSyndrome5	0x1015
#घोषणा DoC_AliasResolution 	0x101b
#घोषणा DoC_ConfigInput		0x101c
#घोषणा DoC_ReadPipeInit 	0x101d
#घोषणा DoC_WritePipeTerm 	0x101e
#घोषणा DoC_LastDataRead 	0x101f
#घोषणा DoC_NOP 		0x1020

#घोषणा DoC_Mil_CDSN_IO 	0x0800
#घोषणा DoC_2k_CDSN_IO 		0x1800

#घोषणा DoC_Mplus_NOP			0x1002
#घोषणा DoC_Mplus_AliasResolution	0x1004
#घोषणा DoC_Mplus_DOCControl		0x1006
#घोषणा DoC_Mplus_AccessStatus		0x1008
#घोषणा DoC_Mplus_DeviceSelect		0x1008
#घोषणा DoC_Mplus_Configuration		0x100a
#घोषणा DoC_Mplus_OutputControl		0x100c
#घोषणा DoC_Mplus_FlashControl		0x1020
#घोषणा DoC_Mplus_FlashSelect 		0x1022
#घोषणा DoC_Mplus_FlashCmd		0x1024
#घोषणा DoC_Mplus_FlashAddress		0x1026
#घोषणा DoC_Mplus_FlashData0		0x1028
#घोषणा DoC_Mplus_FlashData1		0x1029
#घोषणा DoC_Mplus_ReadPipeInit		0x102a
#घोषणा DoC_Mplus_LastDataRead		0x102c
#घोषणा DoC_Mplus_LastDataRead1		0x102d
#घोषणा DoC_Mplus_WritePipeTerm 	0x102e
#घोषणा DoC_Mplus_ECCSyndrome0		0x1040
#घोषणा DoC_Mplus_ECCSyndrome1		0x1041
#घोषणा DoC_Mplus_ECCSyndrome2		0x1042
#घोषणा DoC_Mplus_ECCSyndrome3		0x1043
#घोषणा DoC_Mplus_ECCSyndrome4		0x1044
#घोषणा DoC_Mplus_ECCSyndrome5		0x1045
#घोषणा DoC_Mplus_ECCConf 		0x1046
#घोषणा DoC_Mplus_Toggle		0x1046
#घोषणा DoC_Mplus_DownloadStatus	0x1074
#घोषणा DoC_Mplus_CtrlConfirm		0x1076
#घोषणा DoC_Mplus_Power			0x1fff

/* How to access the device?
 * On ARM, it'll be mmap'd directly with 32-bit wide accesses.
 * On PPC, it's mmap'd and 16-bit wide.
 * Others use पढ़ोb/ग_लिखोb
 */
#अगर defined(__arm__)
अटल अंतरभूत u8 ReadDOC_(u32 __iomem *addr, अचिन्हित दीर्घ reg)
अणु
	वापस __raw_पढ़ोl(addr + reg);
पूर्ण
अटल अंतरभूत व्योम WriteDOC_(u8 data, u32 __iomem *addr, अचिन्हित दीर्घ reg)
अणु
	__raw_ग_लिखोl(data, addr + reg);
	wmb();
पूर्ण
#घोषणा DOC_IOREMAP_LEN 0x8000
#या_अगर defined(__ppc__)
अटल अंतरभूत u8 ReadDOC_(u16 __iomem *addr, अचिन्हित दीर्घ reg)
अणु
	वापस __raw_पढ़ोw(addr + reg);
पूर्ण
अटल अंतरभूत व्योम WriteDOC_(u8 data, u16 __iomem *addr, अचिन्हित दीर्घ reg)
अणु
	__raw_ग_लिखोw(data, addr + reg);
	wmb();
पूर्ण
#घोषणा DOC_IOREMAP_LEN 0x4000
#अन्यथा
#घोषणा ReadDOC_(adr, reg)      पढ़ोb((व्योम __iomem *)(adr) + (reg))
#घोषणा WriteDOC_(d, adr, reg)  ग_लिखोb(d, (व्योम __iomem *)(adr) + (reg))
#घोषणा DOC_IOREMAP_LEN 0x2000

#पूर्ण_अगर

#अगर defined(__i386__) || defined(__x86_64__)
#घोषणा USE_MEMCPY
#पूर्ण_अगर

/* These are provided to directly use the DoC_xxx defines */
#घोषणा ReadDOC(adr, reg)      ReadDOC_(adr,DoC_##reg)
#घोषणा WriteDOC(d, adr, reg)  WriteDOC_(d,adr,DoC_##reg)

#घोषणा DOC_MODE_RESET 		0
#घोषणा DOC_MODE_NORMAL 	1
#घोषणा DOC_MODE_RESERVED1 	2
#घोषणा DOC_MODE_RESERVED2 	3

#घोषणा DOC_MODE_CLR_ERR 	0x80
#घोषणा	DOC_MODE_RST_LAT	0x10
#घोषणा	DOC_MODE_BDECT		0x08
#घोषणा DOC_MODE_MDWREN 	0x04

#घोषणा DOC_ChipID_Doc2k 	0x20
#घोषणा DOC_ChipID_Doc2kTSOP 	0x21	/* पूर्णांकernal number क्रम MTD */
#घोषणा DOC_ChipID_DocMil 	0x30
#घोषणा DOC_ChipID_DocMilPlus32	0x40
#घोषणा DOC_ChipID_DocMilPlus16	0x41

#घोषणा CDSN_CTRL_FR_B 		0x80
#घोषणा CDSN_CTRL_FR_B0		0x40
#घोषणा CDSN_CTRL_FR_B1		0x80

#घोषणा CDSN_CTRL_ECC_IO 	0x20
#घोषणा CDSN_CTRL_FLASH_IO 	0x10
#घोषणा CDSN_CTRL_WP 		0x08
#घोषणा CDSN_CTRL_ALE 		0x04
#घोषणा CDSN_CTRL_CLE 		0x02
#घोषणा CDSN_CTRL_CE 		0x01

#घोषणा DOC_ECC_RESET 		0
#घोषणा DOC_ECC_ERROR 		0x80
#घोषणा DOC_ECC_RW 		0x20
#घोषणा DOC_ECC__EN 		0x08
#घोषणा DOC_TOGGLE_BIT 		0x04
#घोषणा DOC_ECC_RESV 		0x02
#घोषणा DOC_ECC_IGNORE		0x01

#घोषणा DOC_FLASH_CE		0x80
#घोषणा DOC_FLASH_WP		0x40
#घोषणा DOC_FLASH_BANK		0x02

/* We have to also set the reserved bit 1 क्रम enable */
#घोषणा DOC_ECC_EN (DOC_ECC__EN | DOC_ECC_RESV)
#घोषणा DOC_ECC_DIS (DOC_ECC_RESV)

काष्ठा Nand अणु
	अक्षर न्यूनमान, chip;
	अचिन्हित दीर्घ curadr;
	अचिन्हित अक्षर curmode;
	/* Also some erase/ग_लिखो/pipeline info when we get that far */
पूर्ण;

#घोषणा MAX_FLOORS 4
#घोषणा MAX_CHIPS 4

#घोषणा MAX_FLOORS_MIL 1
#घोषणा MAX_CHIPS_MIL 1

#घोषणा MAX_FLOORS_MPLUS 2
#घोषणा MAX_CHIPS_MPLUS 1

#घोषणा ADDR_COLUMN 1
#घोषणा ADDR_PAGE 2
#घोषणा ADDR_COLUMN_PAGE 3

काष्ठा DiskOnChip अणु
	अचिन्हित दीर्घ physadr;
	व्योम __iomem *virtadr;
	अचिन्हित दीर्घ totlen;
	अचिन्हित अक्षर ChipID; /* Type of DiskOnChip */
	पूर्णांक ioreg;

	अचिन्हित दीर्घ mfr; /* Flash IDs - only one type of flash per device */
	अचिन्हित दीर्घ id;
	पूर्णांक chipshअगरt;
	अक्षर page256;
	अक्षर pageadrlen;
	अक्षर पूर्णांकerleave; /* Internal पूर्णांकerleaving - Millennium Plus style */
	अचिन्हित दीर्घ erasesize;

	पूर्णांक curन्यूनमान;
	पूर्णांक curchip;

	पूर्णांक numchips;
	काष्ठा Nand *chips;
	काष्ठा mtd_info *nextकरोc;
	काष्ठा mutex lock;
पूर्ण;

पूर्णांक करोc_decode_ecc(अचिन्हित अक्षर sector[512], अचिन्हित अक्षर ecc1[6]);

#पूर्ण_अगर /* __MTD_DOC2000_H__ */
