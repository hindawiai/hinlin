<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * SuperH FLCTL nand controller
 *
 * Copyright तऊ 2008 Renesas Solutions Corp.
 */

#अगर_अघोषित __SH_FLCTL_H__
#घोषणा __SH_FLCTL_H__

#समावेश <linux/completion.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/pm_qos.h>

/* FLCTL रेजिस्टरs */
#घोषणा FLCMNCR(f)		(f->reg + 0x0)
#घोषणा FLCMDCR(f)		(f->reg + 0x4)
#घोषणा FLCMCDR(f)		(f->reg + 0x8)
#घोषणा FLADR(f)		(f->reg + 0xC)
#घोषणा FLADR2(f)		(f->reg + 0x3C)
#घोषणा FLDATAR(f)		(f->reg + 0x10)
#घोषणा FLDTCNTR(f)		(f->reg + 0x14)
#घोषणा FLINTDMACR(f)		(f->reg + 0x18)
#घोषणा FLBSYTMR(f)		(f->reg + 0x1C)
#घोषणा FLBSYCNT(f)		(f->reg + 0x20)
#घोषणा FLDTFIFO(f)		(f->reg + 0x24)
#घोषणा FLECFIFO(f)		(f->reg + 0x28)
#घोषणा FLTRCR(f)		(f->reg + 0x2C)
#घोषणा FLHOLDCR(f)		(f->reg + 0x38)
#घोषणा	FL4ECCRESULT0(f)	(f->reg + 0x80)
#घोषणा	FL4ECCRESULT1(f)	(f->reg + 0x84)
#घोषणा	FL4ECCRESULT2(f)	(f->reg + 0x88)
#घोषणा	FL4ECCRESULT3(f)	(f->reg + 0x8C)
#घोषणा	FL4ECCCR(f)		(f->reg + 0x90)
#घोषणा	FL4ECCCNT(f)		(f->reg + 0x94)
#घोषणा	FLERRADR(f)		(f->reg + 0x98)

/* FLCMNCR control bits */
#घोषणा _4ECCCNTEN	(0x1 << 24)
#घोषणा _4ECCEN		(0x1 << 23)
#घोषणा _4ECCCORRECT	(0x1 << 22)
#घोषणा SHBUSSEL	(0x1 << 20)
#घोषणा SEL_16BIT	(0x1 << 19)
#घोषणा Sन_अंकD_E		(0x1 << 18)	/* Sन_अंकD (0=512 1=2048)*/
#घोषणा QTSEL_E		(0x1 << 17)
#घोषणा ENDIAN		(0x1 << 16)	/* 1 = little endian */
#घोषणा FCKSEL_E	(0x1 << 15)
#घोषणा ACM_SACCES_MODE	(0x01 << 10)
#घोषणा न_अंकWF_E		(0x1 << 9)
#घोषणा SE_D		(0x1 << 8)	/* Spare area disable */
#घोषणा	CE1_ENABLE	(0x1 << 4)	/* Chip Enable 1 */
#घोषणा	CE0_ENABLE	(0x1 << 3)	/* Chip Enable 0 */
#घोषणा	TYPESEL_SET	(0x1 << 0)

/*
 * Clock settings using the PULSEx रेजिस्टरs from FLCMNCR
 *
 * Some hardware uses bits called PULSEx instead of FCKSEL_E and QTSEL_E
 * to control the घड़ी भागider used between the High-Speed Peripheral Clock
 * and the FLCTL पूर्णांकernal घड़ी. If so, use CLK_8_BIT_xxx क्रम connecting 8 bit
 * and CLK_16_BIT_xxx क्रम connecting 16 bit bus bandwith न_अंकD chips. For the 16
 * bit version the भागider is seperate क्रम the pulse width of high and low
 * संकेतs.
 */
#घोषणा PULSE3	(0x1 << 27)
#घोषणा PULSE2	(0x1 << 17)
#घोषणा PULSE1	(0x1 << 15)
#घोषणा PULSE0	(0x1 << 9)
#घोषणा CLK_8B_0_5			PULSE1
#घोषणा CLK_8B_1			0x0
#घोषणा CLK_8B_1_5			(PULSE1 | PULSE2)
#घोषणा CLK_8B_2			PULSE0
#घोषणा CLK_8B_3			(PULSE0 | PULSE1 | PULSE2)
#घोषणा CLK_8B_4			(PULSE0 | PULSE2)
#घोषणा CLK_16B_6L_2H			PULSE0
#घोषणा CLK_16B_9L_3H			(PULSE0 | PULSE1 | PULSE2)
#घोषणा CLK_16B_12L_4H			(PULSE0 | PULSE2)

/* FLCMDCR control bits */
#घोषणा ADRCNT2_E	(0x1 << 31)	/* 5byte address enable */
#घोषणा ADRMD_E		(0x1 << 26)	/* Sector address access */
#घोषणा CDSRC_E		(0x1 << 25)	/* Data buffer selection */
#घोषणा DOSR_E		(0x1 << 24)	/* Status पढ़ो check */
#घोषणा SELRW		(0x1 << 21)	/*  0:पढ़ो 1:ग_लिखो */
#घोषणा DOADR_E		(0x1 << 20)	/* Address stage execute */
#घोषणा ADRCNT_1	(0x00 << 18)	/* Address data bytes: 1byte */
#घोषणा ADRCNT_2	(0x01 << 18)	/* Address data bytes: 2byte */
#घोषणा ADRCNT_3	(0x02 << 18)	/* Address data bytes: 3byte */
#घोषणा ADRCNT_4	(0x03 << 18)	/* Address data bytes: 4byte */
#घोषणा DOCMD2_E	(0x1 << 17)	/* 2nd cmd stage execute */
#घोषणा DOCMD1_E	(0x1 << 16)	/* 1st cmd stage execute */

/* FLINTDMACR control bits */
#घोषणा ESTERINTE	(0x1 << 24)	/* ECC error पूर्णांकerrupt enable */
#घोषणा AC1CLR		(0x1 << 19)	/* ECC FIFO clear */
#घोषणा AC0CLR		(0x1 << 18)	/* Data FIFO clear */
#घोषणा DREQ0EN		(0x1 << 16)	/* FLDTFIFODMA Request Enable */
#घोषणा ECERB		(0x1 << 9)	/* ECC error */
#घोषणा STERB		(0x1 << 8)	/* Status error */
#घोषणा STERINTE	(0x1 << 4)	/* Status error enable */

/* FLTRCR control bits */
#घोषणा TRSTRT		(0x1 << 0)	/* translation start */
#घोषणा TREND		(0x1 << 1)	/* translation end */

/*
 * FLHOLDCR control bits
 *
 * HOLDEN: Bus Occupancy Enable (inverted)
 * Enable this bit when the बाह्यal bus might be used in between transfers.
 * If not set and the bus माला_लो used by other modules, a deadlock occurs.
 */
#घोषणा HOLDEN		(0x1 << 0)

/* FL4ECCCR control bits */
#घोषणा	_4ECCFA		(0x1 << 2)	/* 4 symbols correct fault */
#घोषणा	_4ECCEND	(0x1 << 1)	/* 4 symbols end */
#घोषणा	_4ECCEXST	(0x1 << 0)	/* 4 symbols exist */

#घोषणा LOOP_TIMEOUT_MAX	0x00010000

क्रमागत flctl_ecc_res_t अणु
	FL_SUCCESS,
	FL_REPAIRABLE,
	FL_ERROR,
	FL_TIMEOUT
पूर्ण;

काष्ठा dma_chan;

काष्ठा sh_flctl अणु
	काष्ठा nand_chip	chip;
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा dev_pm_qos_request pm_qos;
	व्योम __iomem		*reg;
	resource_माप_प्रकार		fअगरo;

	uपूर्णांक8_t	करोne_buff[2048 + 64];	/* max size 2048 + 64 */
	पूर्णांक	पढ़ो_bytes;
	अचिन्हित पूर्णांक index;
	पूर्णांक	seqin_column;		/* column in SEQIN cmd */
	पूर्णांक	seqin_page_addr;	/* page_addr in SEQIN cmd */
	uपूर्णांक32_t seqin_पढ़ो_cmd;		/* पढ़ो cmd in SEQIN cmd */
	पूर्णांक	erase1_page_addr;	/* page_addr in ERASE1 cmd */
	uपूर्णांक32_t erase_ADRCNT;		/* bits of FLCMDCR in ERASE1 cmd */
	uपूर्णांक32_t rw_ADRCNT;	/* bits of FLCMDCR in READ WRITE cmd */
	uपूर्णांक32_t flcmncr_base;	/* base value of FLCMNCR */
	uपूर्णांक32_t flपूर्णांकdmacr_base;	/* irq enable bits */

	अचिन्हित page_size:1;	/* न_अंकD page size (0 = 512, 1 = 2048) */
	अचिन्हित hwecc:1;	/* Hardware ECC (0 = disabled, 1 = enabled) */
	अचिन्हित holden:1;	/* Hardware has FLHOLDCR and HOLDEN is set */
	अचिन्हित qos_request:1;	/* QoS request to prevent deep घातer shutकरोwn */

	/* DMA related objects */
	काष्ठा dma_chan		*chan_fअगरo0_rx;
	काष्ठा dma_chan		*chan_fअगरo0_tx;
	काष्ठा completion	dma_complete;
पूर्ण;

काष्ठा sh_flctl_platक्रमm_data अणु
	काष्ठा mtd_partition	*parts;
	पूर्णांक			nr_parts;
	अचिन्हित दीर्घ		flcmncr_val;

	अचिन्हित has_hwecc:1;
	अचिन्हित use_holden:1;

	अचिन्हित पूर्णांक            slave_id_fअगरo0_tx;
	अचिन्हित पूर्णांक            slave_id_fअगरo0_rx;
पूर्ण;

अटल अंतरभूत काष्ठा sh_flctl *mtd_to_flctl(काष्ठा mtd_info *mtdinfo)
अणु
	वापस container_of(mtd_to_nand(mtdinfo), काष्ठा sh_flctl, chip);
पूर्ण

#पूर्ण_अगर	/* __SH_FLCTL_H__ */
