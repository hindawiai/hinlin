<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MACH_SH2007_H
#घोषणा __MACH_SH2007_H

#घोषणा CS5BCR		0xff802050
#घोषणा CS5WCR		0xff802058
#घोषणा CS5PCR		0xff802070

#घोषणा BUS_SZ8		1
#घोषणा BUS_SZ16	2
#घोषणा BUS_SZ32	3

#घोषणा PCMCIA_IODYN	1
#घोषणा PCMCIA_ATA	0
#घोषणा PCMCIA_IO8	2
#घोषणा PCMCIA_IO16	3
#घोषणा PCMCIA_COMM8	4
#घोषणा PCMCIA_COMM16	5
#घोषणा PCMCIA_ATTR8	6
#घोषणा PCMCIA_ATTR16	7

#घोषणा TYPE_SRAM	0
#घोषणा TYPE_PCMCIA	4

/* ग_लिखो-पढ़ो/ग_लिखो-ग_लिखो delay (0-7:0,1,2,3,4,5,6,7) */
#घोषणा IWW5		0
#घोषणा IWW6		3
/* dअगरferent area, पढ़ो-ग_लिखो delay (0-7:0,1,2,3,4,5,6,7) */
#घोषणा IWRWD5		2
#घोषणा IWRWD6		2
/* same area, पढ़ो-ग_लिखो delay (0-7:0,1,2,3,4,5,6,7) */
#घोषणा IWRWS5		2
#घोषणा IWRWS6		2
/* dअगरferent area, पढ़ो-पढ़ो delay (0-7:0,1,2,3,4,5,6,7) */
#घोषणा IWRRD5		2
#घोषणा IWRRD6		2
/* same area, पढ़ो-पढ़ो delay (0-7:0,1,2,3,4,5,6,7) */
#घोषणा IWRRS5		0
#घोषणा IWRRS6		2
/* burst count (0-3:4,8,16,32) */
#घोषणा BST5		0
#घोषणा BST6		0
/* bus size */
#घोषणा SZ5		BUS_SZ16
#घोषणा SZ6		BUS_SZ16
/* RD hold क्रम SRAM (0-1:0,1) */
#घोषणा RDSPL5		0
#घोषणा RDSPL6		0
/* Burst pitch (0-7:0,1,2,3,4,5,6,7) */
#घोषणा BW5		0
#घोषणा BW6		0
/* Multiplex (0-1:0,1) */
#घोषणा MPX5		0
#घोषणा MPX6		0
/* device type */
#घोषणा TYPE5		TYPE_PCMCIA
#घोषणा TYPE6		TYPE_PCMCIA
/* address setup beक्रमe निश्चित CSn क्रम SRAM (0-7:0,1,2,3,4,5,6,7) */
#घोषणा ADS5		0
#घोषणा ADS6		0
/* address hold after negate CSn क्रम SRAM (0-7:0,1,2,3,4,5,6,7) */
#घोषणा ADH5		0
#घोषणा ADH6		0
/* CSn निश्चित to RD निश्चित delay क्रम SRAM (0-7:0,1,2,3,4,5,6,7) */
#घोषणा RDS5		0
#घोषणा RDS6		0
/* RD negate to CSn negate delay क्रम SRAM (0-7:0,1,2,3,4,5,6,7) */
#घोषणा RDH5		0
#घोषणा RDH6		0
/* CSn निश्चित to WE निश्चित delay क्रम SRAM (0-7:0,1,2,3,4,5,6,7) */
#घोषणा WTS5		0
#घोषणा WTS6		0
/* WE negate to CSn negate delay क्रम SRAM (0-7:0,1,2,3,4,5,6,7) */
#घोषणा WTH5		0
#घोषणा WTH6		0
/* BS hold (0-1:1,2) */
#घोषणा BSH5		0
#घोषणा BSH6		0
/* रुको cycle (0-15:0,1,2,3,4,5,6,7,8,9,11,13,15,17,21,25) */
#घोषणा IW5		6	/* 60ns PIO mode 4 */
#घोषणा IW6		15	/* 250ns */

#घोषणा SAA5		PCMCIA_IODYN	/* IDE area b4000000-b5ffffff */
#घोषणा SAB5		PCMCIA_IODYN	/* CF  area b6000000-b7ffffff */
#घोषणा PCWA5		0	/* additional रुको A (0-3:0,15,30,50) */
#घोषणा PCWB5		0	/* additional रुको B (0-3:0,15,30,50) */
/* रुको B (0-15:0,1,2,3,4,5,6,7,8,9,11,13,15,17,21,25) */
#घोषणा PCIW5		12
/* Address->OE/WE निश्चित delay A (0-7:0,1,2,3,6,9,12,15) */
#घोषणा TEDA5		2
/* Address->OE/WE निश्चित delay B (0-7:0,1,2,3,6,9,12,15) */
#घोषणा TEDB5		4
/* OE/WE negate->Address delay A (0-7:0,1,2,3,6,9,12,15) */
#घोषणा TEHA5		2
/* OE/WE negate->Address delay B (0-7:0,1,2,3,6,9,12,15) */
#घोषणा TEHB5		3

#घोषणा CS5BCR_D	((IWW5<<28)|(IWRWD5<<24)|(IWRWS5<<20)|		\
			(IWRRD5<<16)|(IWRRS5<<12)|(BST5<<10)|		\
			(SZ5<<8)|(RDSPL5<<7)|(BW5<<4)|(MPX5<<3)|TYPE5)
#घोषणा CS5WCR_D	((ADS5<<28)|(ADH5<<24)|(RDS5<<20)|	\
			(RDH5<<16)|(WTS5<<12)|(WTH5<<8)|(BSH5<<4)|IW5)
#घोषणा CS5PCR_D	((SAA5<<28)|(SAB5<<24)|(PCWA5<<22)|		\
			(PCWB5<<20)|(PCIW5<<16)|(TEDA5<<12)|		\
			(TEDB5<<8)|(TEHA5<<4)|TEHB5)

#घोषणा SMC0_BASE       0xb0800000      /* eth0 */
#घोषणा SMC1_BASE       0xb0900000      /* eth1 */
#घोषणा CF_BASE         0xb6100000      /* Compact Flash (I/O area) */
#घोषणा IDE_BASE        0xb4000000      /* IDE */
#घोषणा PC104_IO_BASE   0xb8000000
#घोषणा PC104_MEM_BASE  0xba000000
#घोषणा SMC_IO_SIZE     0x100

#घोषणा CF_OFFSET       0x1f0
#घोषणा IDE_OFFSET      0x170

#पूर्ण_अगर /* __MACH_SH2007_H */
