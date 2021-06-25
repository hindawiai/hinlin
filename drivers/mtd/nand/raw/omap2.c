<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2004 Texas Instruments, Jian Zhang <jzhang@ti.com>
 * Copyright तऊ 2004 Micron Technology Inc.
 * Copyright तऊ 2004 David Brownell
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/sched.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nand-ecc-sw-bch.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/omap-dma.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <linux/platक्रमm_data/elm.h>

#समावेश <linux/omap-gpmc.h>
#समावेश <linux/platक्रमm_data/mtd-nand-omap2.h>

#घोषणा	DRIVER_NAME	"omap2-nand"
#घोषणा	OMAP_न_अंकD_TIMEOUT_MS	5000

#घोषणा न_अंकD_Ecc_P1e		(1 << 0)
#घोषणा न_अंकD_Ecc_P2e		(1 << 1)
#घोषणा न_अंकD_Ecc_P4e		(1 << 2)
#घोषणा न_अंकD_Ecc_P8e		(1 << 3)
#घोषणा न_अंकD_Ecc_P16e		(1 << 4)
#घोषणा न_अंकD_Ecc_P32e		(1 << 5)
#घोषणा न_अंकD_Ecc_P64e		(1 << 6)
#घोषणा न_अंकD_Ecc_P128e		(1 << 7)
#घोषणा न_अंकD_Ecc_P256e		(1 << 8)
#घोषणा न_अंकD_Ecc_P512e		(1 << 9)
#घोषणा न_अंकD_Ecc_P1024e		(1 << 10)
#घोषणा न_अंकD_Ecc_P2048e		(1 << 11)

#घोषणा न_अंकD_Ecc_P1o		(1 << 16)
#घोषणा न_अंकD_Ecc_P2o		(1 << 17)
#घोषणा न_अंकD_Ecc_P4o		(1 << 18)
#घोषणा न_अंकD_Ecc_P8o		(1 << 19)
#घोषणा न_अंकD_Ecc_P16o		(1 << 20)
#घोषणा न_अंकD_Ecc_P32o		(1 << 21)
#घोषणा न_अंकD_Ecc_P64o		(1 << 22)
#घोषणा न_अंकD_Ecc_P128o		(1 << 23)
#घोषणा न_अंकD_Ecc_P256o		(1 << 24)
#घोषणा न_अंकD_Ecc_P512o		(1 << 25)
#घोषणा न_अंकD_Ecc_P1024o		(1 << 26)
#घोषणा न_अंकD_Ecc_P2048o		(1 << 27)

#घोषणा TF(value)	(value ? 1 : 0)

#घोषणा P2048e(a)	(TF(a & न_अंकD_Ecc_P2048e)	<< 0)
#घोषणा P2048o(a)	(TF(a & न_अंकD_Ecc_P2048o)	<< 1)
#घोषणा P1e(a)		(TF(a & न_अंकD_Ecc_P1e)		<< 2)
#घोषणा P1o(a)		(TF(a & न_अंकD_Ecc_P1o)		<< 3)
#घोषणा P2e(a)		(TF(a & न_अंकD_Ecc_P2e)		<< 4)
#घोषणा P2o(a)		(TF(a & न_अंकD_Ecc_P2o)		<< 5)
#घोषणा P4e(a)		(TF(a & न_अंकD_Ecc_P4e)		<< 6)
#घोषणा P4o(a)		(TF(a & न_अंकD_Ecc_P4o)		<< 7)

#घोषणा P8e(a)		(TF(a & न_अंकD_Ecc_P8e)		<< 0)
#घोषणा P8o(a)		(TF(a & न_अंकD_Ecc_P8o)		<< 1)
#घोषणा P16e(a)		(TF(a & न_अंकD_Ecc_P16e)		<< 2)
#घोषणा P16o(a)		(TF(a & न_अंकD_Ecc_P16o)		<< 3)
#घोषणा P32e(a)		(TF(a & न_अंकD_Ecc_P32e)		<< 4)
#घोषणा P32o(a)		(TF(a & न_अंकD_Ecc_P32o)		<< 5)
#घोषणा P64e(a)		(TF(a & न_अंकD_Ecc_P64e)		<< 6)
#घोषणा P64o(a)		(TF(a & न_अंकD_Ecc_P64o)		<< 7)

#घोषणा P128e(a)	(TF(a & न_अंकD_Ecc_P128e)		<< 0)
#घोषणा P128o(a)	(TF(a & न_अंकD_Ecc_P128o)		<< 1)
#घोषणा P256e(a)	(TF(a & न_अंकD_Ecc_P256e)		<< 2)
#घोषणा P256o(a)	(TF(a & न_अंकD_Ecc_P256o)		<< 3)
#घोषणा P512e(a)	(TF(a & न_अंकD_Ecc_P512e)		<< 4)
#घोषणा P512o(a)	(TF(a & न_अंकD_Ecc_P512o)		<< 5)
#घोषणा P1024e(a)	(TF(a & न_अंकD_Ecc_P1024e)	<< 6)
#घोषणा P1024o(a)	(TF(a & न_अंकD_Ecc_P1024o)	<< 7)

#घोषणा P8e_s(a)	(TF(a & न_अंकD_Ecc_P8e)		<< 0)
#घोषणा P8o_s(a)	(TF(a & न_अंकD_Ecc_P8o)		<< 1)
#घोषणा P16e_s(a)	(TF(a & न_अंकD_Ecc_P16e)		<< 2)
#घोषणा P16o_s(a)	(TF(a & न_अंकD_Ecc_P16o)		<< 3)
#घोषणा P1e_s(a)	(TF(a & न_अंकD_Ecc_P1e)		<< 4)
#घोषणा P1o_s(a)	(TF(a & न_अंकD_Ecc_P1o)		<< 5)
#घोषणा P2e_s(a)	(TF(a & न_अंकD_Ecc_P2e)		<< 6)
#घोषणा P2o_s(a)	(TF(a & न_अंकD_Ecc_P2o)		<< 7)

#घोषणा P4e_s(a)	(TF(a & न_अंकD_Ecc_P4e)		<< 0)
#घोषणा P4o_s(a)	(TF(a & न_अंकD_Ecc_P4o)		<< 1)

#घोषणा	PREFETCH_CONFIG1_CS_SHIFT	24
#घोषणा	ECC_CONFIG_CS_SHIFT		1
#घोषणा	CS_MASK				0x7
#घोषणा	ENABLE_PREFETCH			(0x1 << 7)
#घोषणा	DMA_MPU_MODE_SHIFT		2
#घोषणा	ECCSIZE0_SHIFT			12
#घोषणा	ECCSIZE1_SHIFT			22
#घोषणा	ECC1RESULTSIZE			0x1
#घोषणा	ECCCLEAR			0x100
#घोषणा	ECC1				0x1
#घोषणा	PREFETCH_FIFOTHRESHOLD_MAX	0x40
#घोषणा	PREFETCH_FIFOTHRESHOLD(val)	((val) << 8)
#घोषणा	PREFETCH_STATUS_COUNT(val)	(val & 0x00003fff)
#घोषणा	PREFETCH_STATUS_FIFO_CNT(val)	((val >> 24) & 0x7F)
#घोषणा	STATUS_BUFF_EMPTY		0x00000001

#घोषणा SECTOR_BYTES		512
/* 4 bit padding to make byte aligned, 56 = 52 + 4 */
#घोषणा BCH4_BIT_PAD		4

/* GPMC ecc engine settings क्रम पढ़ो */
#घोषणा BCH_WRAPMODE_1		1	/* BCH wrap mode 1 */
#घोषणा BCH8R_ECC_SIZE0		0x1a	/* ecc_size0 = 26 */
#घोषणा BCH8R_ECC_SIZE1		0x2	/* ecc_size1 = 2 */
#घोषणा BCH4R_ECC_SIZE0		0xd	/* ecc_size0 = 13 */
#घोषणा BCH4R_ECC_SIZE1		0x3	/* ecc_size1 = 3 */

/* GPMC ecc engine settings क्रम ग_लिखो */
#घोषणा BCH_WRAPMODE_6		6	/* BCH wrap mode 6 */
#घोषणा BCH_ECC_SIZE0		0x0	/* ecc_size0 = 0, no oob protection */
#घोषणा BCH_ECC_SIZE1		0x20	/* ecc_size1 = 32 */

#घोषणा BADBLOCK_MARKER_LENGTH		2

अटल u_अक्षर bch16_vector[] = अणु0xf5, 0x24, 0x1c, 0xd0, 0x61, 0xb3, 0xf1, 0x55,
				0x2e, 0x2c, 0x86, 0xa3, 0xed, 0x36, 0x1b, 0x78,
				0x48, 0x76, 0xa9, 0x3b, 0x97, 0xd1, 0x7a, 0x93,
				0x07, 0x0eपूर्ण;
अटल u_अक्षर bch8_vector[] = अणु0xf3, 0xdb, 0x14, 0x16, 0x8b, 0xd2, 0xbe, 0xcc,
	0xac, 0x6b, 0xff, 0x99, 0x7bपूर्ण;
अटल u_अक्षर bch4_vector[] = अणु0x00, 0x6b, 0x31, 0xdd, 0x41, 0xbc, 0x10पूर्ण;

काष्ठा omap_nand_info अणु
	काष्ठा nand_chip		nand;
	काष्ठा platक्रमm_device		*pdev;

	पूर्णांक				gpmc_cs;
	bool				dev_पढ़ोy;
	क्रमागत nand_io			xfer_type;
	पूर्णांक				devsize;
	क्रमागत omap_ecc			ecc_opt;
	काष्ठा device_node		*elm_of_node;

	अचिन्हित दीर्घ			phys_base;
	काष्ठा completion		comp;
	काष्ठा dma_chan			*dma;
	पूर्णांक				gpmc_irq_fअगरo;
	पूर्णांक				gpmc_irq_count;
	क्रमागत अणु
		OMAP_न_अंकD_IO_READ = 0,	/* पढ़ो */
		OMAP_न_अंकD_IO_WRITE,	/* ग_लिखो */
	पूर्ण iomode;
	u_अक्षर				*buf;
	पूर्णांक					buf_len;
	/* Interface to GPMC */
	काष्ठा gpmc_nand_regs		reg;
	काष्ठा gpmc_nand_ops		*ops;
	bool				flash_bbt;
	/* fields specअगरic क्रम BCHx_HW ECC scheme */
	काष्ठा device			*elm_dev;
	/* न_अंकD पढ़ोy gpio */
	काष्ठा gpio_desc		*पढ़ोy_gpiod;
पूर्ण;

अटल अंतरभूत काष्ठा omap_nand_info *mtd_to_omap(काष्ठा mtd_info *mtd)
अणु
	वापस container_of(mtd_to_nand(mtd), काष्ठा omap_nand_info, nand);
पूर्ण

/**
 * omap_prefetch_enable - configures and starts prefetch transfer
 * @cs: cs (chip select) number
 * @fअगरo_th: fअगरo threshold to be used क्रम पढ़ो/ ग_लिखो
 * @dma_mode: dma mode enable (1) or disable (0)
 * @u32_count: number of bytes to be transferred
 * @is_ग_लिखो: prefetch पढ़ो(0) or ग_लिखो post(1) mode
 * @info: न_अंकD device काष्ठाure containing platक्रमm data
 */
अटल पूर्णांक omap_prefetch_enable(पूर्णांक cs, पूर्णांक fअगरo_th, पूर्णांक dma_mode,
	अचिन्हित पूर्णांक u32_count, पूर्णांक is_ग_लिखो, काष्ठा omap_nand_info *info)
अणु
	u32 val;

	अगर (fअगरo_th > PREFETCH_FIFOTHRESHOLD_MAX)
		वापस -1;

	अगर (पढ़ोl(info->reg.gpmc_prefetch_control))
		वापस -EBUSY;

	/* Set the amount of bytes to be prefetched */
	ग_लिखोl(u32_count, info->reg.gpmc_prefetch_config2);

	/* Set dma/mpu mode, the prefetch पढ़ो / post ग_लिखो and
	 * enable the engine. Set which cs is has requested क्रम.
	 */
	val = ((cs << PREFETCH_CONFIG1_CS_SHIFT) |
		PREFETCH_FIFOTHRESHOLD(fअगरo_th) | ENABLE_PREFETCH |
		(dma_mode << DMA_MPU_MODE_SHIFT) | (is_ग_लिखो & 0x1));
	ग_लिखोl(val, info->reg.gpmc_prefetch_config1);

	/*  Start the prefetch engine */
	ग_लिखोl(0x1, info->reg.gpmc_prefetch_control);

	वापस 0;
पूर्ण

/*
 * omap_prefetch_reset - disables and stops the prefetch engine
 */
अटल पूर्णांक omap_prefetch_reset(पूर्णांक cs, काष्ठा omap_nand_info *info)
अणु
	u32 config1;

	/* check अगर the same module/cs is trying to reset */
	config1 = पढ़ोl(info->reg.gpmc_prefetch_config1);
	अगर (((config1 >> PREFETCH_CONFIG1_CS_SHIFT) & CS_MASK) != cs)
		वापस -EINVAL;

	/* Stop the PFPW engine */
	ग_लिखोl(0x0, info->reg.gpmc_prefetch_control);

	/* Reset/disable the PFPW engine */
	ग_लिखोl(0x0, info->reg.gpmc_prefetch_config1);

	वापस 0;
पूर्ण

/**
 * omap_hwcontrol - hardware specअगरic access to control-lines
 * @chip: न_अंकD chip object
 * @cmd: command to device
 * @ctrl:
 * न_अंकD_NCE: bit 0 -> करोn't care
 * न_अंकD_CLE: bit 1 -> Command Latch
 * न_अंकD_ALE: bit 2 -> Address Latch
 *
 * NOTE: boards may use dअगरferent bits क्रम these!!
 */
अटल व्योम omap_hwcontrol(काष्ठा nand_chip *chip, पूर्णांक cmd, अचिन्हित पूर्णांक ctrl)
अणु
	काष्ठा omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));

	अगर (cmd != न_अंकD_CMD_NONE) अणु
		अगर (ctrl & न_अंकD_CLE)
			ग_लिखोb(cmd, info->reg.gpmc_nand_command);

		अन्यथा अगर (ctrl & न_अंकD_ALE)
			ग_लिखोb(cmd, info->reg.gpmc_nand_address);

		अन्यथा /* न_अंकD_NCE */
			ग_लिखोb(cmd, info->reg.gpmc_nand_data);
	पूर्ण
पूर्ण

/**
 * omap_पढ़ो_buf8 - पढ़ो data from न_अंकD controller पूर्णांकo buffer
 * @mtd: MTD device काष्ठाure
 * @buf: buffer to store date
 * @len: number of bytes to पढ़ो
 */
अटल व्योम omap_पढ़ो_buf8(काष्ठा mtd_info *mtd, u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा nand_chip *nand = mtd_to_nand(mtd);

	ioपढ़ो8_rep(nand->legacy.IO_ADDR_R, buf, len);
पूर्ण

/**
 * omap_ग_लिखो_buf8 - ग_लिखो buffer to न_अंकD controller
 * @mtd: MTD device काष्ठाure
 * @buf: data buffer
 * @len: number of bytes to ग_लिखो
 */
अटल व्योम omap_ग_लिखो_buf8(काष्ठा mtd_info *mtd, स्थिर u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा omap_nand_info *info = mtd_to_omap(mtd);
	u_अक्षर *p = (u_अक्षर *)buf;
	bool status;

	जबतक (len--) अणु
		ioग_लिखो8(*p++, info->nand.legacy.IO_ADDR_W);
		/* रुको until buffer is available क्रम ग_लिखो */
		करो अणु
			status = info->ops->nand_ग_लिखोbuffer_empty();
		पूर्ण जबतक (!status);
	पूर्ण
पूर्ण

/**
 * omap_पढ़ो_buf16 - पढ़ो data from न_अंकD controller पूर्णांकo buffer
 * @mtd: MTD device काष्ठाure
 * @buf: buffer to store date
 * @len: number of bytes to पढ़ो
 */
अटल व्योम omap_पढ़ो_buf16(काष्ठा mtd_info *mtd, u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा nand_chip *nand = mtd_to_nand(mtd);

	ioपढ़ो16_rep(nand->legacy.IO_ADDR_R, buf, len / 2);
पूर्ण

/**
 * omap_ग_लिखो_buf16 - ग_लिखो buffer to न_अंकD controller
 * @mtd: MTD device काष्ठाure
 * @buf: data buffer
 * @len: number of bytes to ग_लिखो
 */
अटल व्योम omap_ग_लिखो_buf16(काष्ठा mtd_info *mtd, स्थिर u_अक्षर * buf, पूर्णांक len)
अणु
	काष्ठा omap_nand_info *info = mtd_to_omap(mtd);
	u16 *p = (u16 *) buf;
	bool status;
	/* FIXME try bursts of ग_लिखोsw() or DMA ... */
	len >>= 1;

	जबतक (len--) अणु
		ioग_लिखो16(*p++, info->nand.legacy.IO_ADDR_W);
		/* रुको until buffer is available क्रम ग_लिखो */
		करो अणु
			status = info->ops->nand_ग_लिखोbuffer_empty();
		पूर्ण जबतक (!status);
	पूर्ण
पूर्ण

/**
 * omap_पढ़ो_buf_pref - पढ़ो data from न_अंकD controller पूर्णांकo buffer
 * @chip: न_अंकD chip object
 * @buf: buffer to store date
 * @len: number of bytes to पढ़ो
 */
अटल व्योम omap_पढ़ो_buf_pref(काष्ठा nand_chip *chip, u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा omap_nand_info *info = mtd_to_omap(mtd);
	uपूर्णांक32_t r_count = 0;
	पूर्णांक ret = 0;
	u32 *p = (u32 *)buf;

	/* take care of subpage पढ़ोs */
	अगर (len % 4) अणु
		अगर (info->nand.options & न_अंकD_BUSWIDTH_16)
			omap_पढ़ो_buf16(mtd, buf, len % 4);
		अन्यथा
			omap_पढ़ो_buf8(mtd, buf, len % 4);
		p = (u32 *) (buf + len % 4);
		len -= len % 4;
	पूर्ण

	/* configure and start prefetch transfer */
	ret = omap_prefetch_enable(info->gpmc_cs,
			PREFETCH_FIFOTHRESHOLD_MAX, 0x0, len, 0x0, info);
	अगर (ret) अणु
		/* PFPW engine is busy, use cpu copy method */
		अगर (info->nand.options & न_अंकD_BUSWIDTH_16)
			omap_पढ़ो_buf16(mtd, (u_अक्षर *)p, len);
		अन्यथा
			omap_पढ़ो_buf8(mtd, (u_अक्षर *)p, len);
	पूर्ण अन्यथा अणु
		करो अणु
			r_count = पढ़ोl(info->reg.gpmc_prefetch_status);
			r_count = PREFETCH_STATUS_FIFO_CNT(r_count);
			r_count = r_count >> 2;
			ioपढ़ो32_rep(info->nand.legacy.IO_ADDR_R, p, r_count);
			p += r_count;
			len -= r_count << 2;
		पूर्ण जबतक (len);
		/* disable and stop the PFPW engine */
		omap_prefetch_reset(info->gpmc_cs, info);
	पूर्ण
पूर्ण

/**
 * omap_ग_लिखो_buf_pref - ग_लिखो buffer to न_अंकD controller
 * @chip: न_अंकD chip object
 * @buf: data buffer
 * @len: number of bytes to ग_लिखो
 */
अटल व्योम omap_ग_लिखो_buf_pref(काष्ठा nand_chip *chip, स्थिर u_अक्षर *buf,
				पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा omap_nand_info *info = mtd_to_omap(mtd);
	uपूर्णांक32_t w_count = 0;
	पूर्णांक i = 0, ret = 0;
	u16 *p = (u16 *)buf;
	अचिन्हित दीर्घ tim, limit;
	u32 val;

	/* take care of subpage ग_लिखोs */
	अगर (len % 2 != 0) अणु
		ग_लिखोb(*buf, info->nand.legacy.IO_ADDR_W);
		p = (u16 *)(buf + 1);
		len--;
	पूर्ण

	/*  configure and start prefetch transfer */
	ret = omap_prefetch_enable(info->gpmc_cs,
			PREFETCH_FIFOTHRESHOLD_MAX, 0x0, len, 0x1, info);
	अगर (ret) अणु
		/* PFPW engine is busy, use cpu copy method */
		अगर (info->nand.options & न_अंकD_BUSWIDTH_16)
			omap_ग_लिखो_buf16(mtd, (u_अक्षर *)p, len);
		अन्यथा
			omap_ग_लिखो_buf8(mtd, (u_अक्षर *)p, len);
	पूर्ण अन्यथा अणु
		जबतक (len) अणु
			w_count = पढ़ोl(info->reg.gpmc_prefetch_status);
			w_count = PREFETCH_STATUS_FIFO_CNT(w_count);
			w_count = w_count >> 1;
			क्रम (i = 0; (i < w_count) && len; i++, len -= 2)
				ioग_लिखो16(*p++, info->nand.legacy.IO_ADDR_W);
		पूर्ण
		/* रुको क्रम data to flushed-out beक्रमe reset the prefetch */
		tim = 0;
		limit = (loops_per_jअगरfy *
					msecs_to_jअगरfies(OMAP_न_अंकD_TIMEOUT_MS));
		करो अणु
			cpu_relax();
			val = पढ़ोl(info->reg.gpmc_prefetch_status);
			val = PREFETCH_STATUS_COUNT(val);
		पूर्ण जबतक (val && (tim++ < limit));

		/* disable and stop the PFPW engine */
		omap_prefetch_reset(info->gpmc_cs, info);
	पूर्ण
पूर्ण

/*
 * omap_nand_dma_callback: callback on the completion of dma transfer
 * @data: poपूर्णांकer to completion data काष्ठाure
 */
अटल व्योम omap_nand_dma_callback(व्योम *data)
अणु
	complete((काष्ठा completion *) data);
पूर्ण

/*
 * omap_nand_dma_transfer: configure and start dma transfer
 * @mtd: MTD device काष्ठाure
 * @addr: भव address in RAM of source/destination
 * @len: number of data bytes to be transferred
 * @is_ग_लिखो: flag क्रम पढ़ो/ग_लिखो operation
 */
अटल अंतरभूत पूर्णांक omap_nand_dma_transfer(काष्ठा mtd_info *mtd, व्योम *addr,
					अचिन्हित पूर्णांक len, पूर्णांक is_ग_लिखो)
अणु
	काष्ठा omap_nand_info *info = mtd_to_omap(mtd);
	काष्ठा dma_async_tx_descriptor *tx;
	क्रमागत dma_data_direction dir = is_ग_लिखो ? DMA_TO_DEVICE :
							DMA_FROM_DEVICE;
	काष्ठा scatterlist sg;
	अचिन्हित दीर्घ tim, limit;
	अचिन्हित n;
	पूर्णांक ret;
	u32 val;

	अगर (!virt_addr_valid(addr))
		जाओ out_copy;

	sg_init_one(&sg, addr, len);
	n = dma_map_sg(info->dma->device->dev, &sg, 1, dir);
	अगर (n == 0) अणु
		dev_err(&info->pdev->dev,
			"Couldn't DMA map a %d byte buffer\n", len);
		जाओ out_copy;
	पूर्ण

	tx = dmaengine_prep_slave_sg(info->dma, &sg, n,
		is_ग_लिखो ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM,
		DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!tx)
		जाओ out_copy_unmap;

	tx->callback = omap_nand_dma_callback;
	tx->callback_param = &info->comp;
	dmaengine_submit(tx);

	init_completion(&info->comp);

	/* setup and start DMA using dma_addr */
	dma_async_issue_pending(info->dma);

	/*  configure and start prefetch transfer */
	ret = omap_prefetch_enable(info->gpmc_cs,
		PREFETCH_FIFOTHRESHOLD_MAX, 0x1, len, is_ग_लिखो, info);
	अगर (ret)
		/* PFPW engine is busy, use cpu copy method */
		जाओ out_copy_unmap;

	रुको_क्रम_completion(&info->comp);
	tim = 0;
	limit = (loops_per_jअगरfy * msecs_to_jअगरfies(OMAP_न_अंकD_TIMEOUT_MS));

	करो अणु
		cpu_relax();
		val = पढ़ोl(info->reg.gpmc_prefetch_status);
		val = PREFETCH_STATUS_COUNT(val);
	पूर्ण जबतक (val && (tim++ < limit));

	/* disable and stop the PFPW engine */
	omap_prefetch_reset(info->gpmc_cs, info);

	dma_unmap_sg(info->dma->device->dev, &sg, 1, dir);
	वापस 0;

out_copy_unmap:
	dma_unmap_sg(info->dma->device->dev, &sg, 1, dir);
out_copy:
	अगर (info->nand.options & न_अंकD_BUSWIDTH_16)
		is_ग_लिखो == 0 ? omap_पढ़ो_buf16(mtd, (u_अक्षर *) addr, len)
			: omap_ग_लिखो_buf16(mtd, (u_अक्षर *) addr, len);
	अन्यथा
		is_ग_लिखो == 0 ? omap_पढ़ो_buf8(mtd, (u_अक्षर *) addr, len)
			: omap_ग_लिखो_buf8(mtd, (u_अक्षर *) addr, len);
	वापस 0;
पूर्ण

/**
 * omap_पढ़ो_buf_dma_pref - पढ़ो data from न_अंकD controller पूर्णांकo buffer
 * @chip: न_अंकD chip object
 * @buf: buffer to store date
 * @len: number of bytes to पढ़ो
 */
अटल व्योम omap_पढ़ो_buf_dma_pref(काष्ठा nand_chip *chip, u_अक्षर *buf,
				   पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	अगर (len <= mtd->oobsize)
		omap_पढ़ो_buf_pref(chip, buf, len);
	अन्यथा
		/* start transfer in DMA mode */
		omap_nand_dma_transfer(mtd, buf, len, 0x0);
पूर्ण

/**
 * omap_ग_लिखो_buf_dma_pref - ग_लिखो buffer to न_अंकD controller
 * @chip: न_अंकD chip object
 * @buf: data buffer
 * @len: number of bytes to ग_लिखो
 */
अटल व्योम omap_ग_लिखो_buf_dma_pref(काष्ठा nand_chip *chip, स्थिर u_अक्षर *buf,
				    पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	अगर (len <= mtd->oobsize)
		omap_ग_लिखो_buf_pref(chip, buf, len);
	अन्यथा
		/* start transfer in DMA mode */
		omap_nand_dma_transfer(mtd, (u_अक्षर *)buf, len, 0x1);
पूर्ण

/*
 * omap_nand_irq - GPMC irq handler
 * @this_irq: gpmc irq number
 * @dev: omap_nand_info काष्ठाure poपूर्णांकer is passed here
 */
अटल irqवापस_t omap_nand_irq(पूर्णांक this_irq, व्योम *dev)
अणु
	काष्ठा omap_nand_info *info = (काष्ठा omap_nand_info *) dev;
	u32 bytes;

	bytes = पढ़ोl(info->reg.gpmc_prefetch_status);
	bytes = PREFETCH_STATUS_FIFO_CNT(bytes);
	bytes = bytes  & 0xFFFC; /* io in multiple of 4 bytes */
	अगर (info->iomode == OMAP_न_अंकD_IO_WRITE) अणु /* checks क्रम ग_लिखो io */
		अगर (this_irq == info->gpmc_irq_count)
			जाओ करोne;

		अगर (info->buf_len && (info->buf_len < bytes))
			bytes = info->buf_len;
		अन्यथा अगर (!info->buf_len)
			bytes = 0;
		ioग_लिखो32_rep(info->nand.legacy.IO_ADDR_W, (u32 *)info->buf,
			      bytes >> 2);
		info->buf = info->buf + bytes;
		info->buf_len -= bytes;

	पूर्ण अन्यथा अणु
		ioपढ़ो32_rep(info->nand.legacy.IO_ADDR_R, (u32 *)info->buf,
			     bytes >> 2);
		info->buf = info->buf + bytes;

		अगर (this_irq == info->gpmc_irq_count)
			जाओ करोne;
	पूर्ण

	वापस IRQ_HANDLED;

करोne:
	complete(&info->comp);

	disable_irq_nosync(info->gpmc_irq_fअगरo);
	disable_irq_nosync(info->gpmc_irq_count);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * omap_पढ़ो_buf_irq_pref - पढ़ो data from न_अंकD controller पूर्णांकo buffer
 * @chip: न_अंकD chip object
 * @buf: buffer to store date
 * @len: number of bytes to पढ़ो
 */
अटल व्योम omap_पढ़ो_buf_irq_pref(काष्ठा nand_chip *chip, u_अक्षर *buf,
				   पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा omap_nand_info *info = mtd_to_omap(mtd);
	पूर्णांक ret = 0;

	अगर (len <= mtd->oobsize) अणु
		omap_पढ़ो_buf_pref(chip, buf, len);
		वापस;
	पूर्ण

	info->iomode = OMAP_न_अंकD_IO_READ;
	info->buf = buf;
	init_completion(&info->comp);

	/*  configure and start prefetch transfer */
	ret = omap_prefetch_enable(info->gpmc_cs,
			PREFETCH_FIFOTHRESHOLD_MAX/2, 0x0, len, 0x0, info);
	अगर (ret)
		/* PFPW engine is busy, use cpu copy method */
		जाओ out_copy;

	info->buf_len = len;

	enable_irq(info->gpmc_irq_count);
	enable_irq(info->gpmc_irq_fअगरo);

	/* रुकोing क्रम पढ़ो to complete */
	रुको_क्रम_completion(&info->comp);

	/* disable and stop the PFPW engine */
	omap_prefetch_reset(info->gpmc_cs, info);
	वापस;

out_copy:
	अगर (info->nand.options & न_अंकD_BUSWIDTH_16)
		omap_पढ़ो_buf16(mtd, buf, len);
	अन्यथा
		omap_पढ़ो_buf8(mtd, buf, len);
पूर्ण

/*
 * omap_ग_लिखो_buf_irq_pref - ग_लिखो buffer to न_अंकD controller
 * @chip: न_अंकD chip object
 * @buf: data buffer
 * @len: number of bytes to ग_लिखो
 */
अटल व्योम omap_ग_लिखो_buf_irq_pref(काष्ठा nand_chip *chip, स्थिर u_अक्षर *buf,
				    पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा omap_nand_info *info = mtd_to_omap(mtd);
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ tim, limit;
	u32 val;

	अगर (len <= mtd->oobsize) अणु
		omap_ग_लिखो_buf_pref(chip, buf, len);
		वापस;
	पूर्ण

	info->iomode = OMAP_न_अंकD_IO_WRITE;
	info->buf = (u_अक्षर *) buf;
	init_completion(&info->comp);

	/* configure and start prefetch transfer : size=24 */
	ret = omap_prefetch_enable(info->gpmc_cs,
		(PREFETCH_FIFOTHRESHOLD_MAX * 3) / 8, 0x0, len, 0x1, info);
	अगर (ret)
		/* PFPW engine is busy, use cpu copy method */
		जाओ out_copy;

	info->buf_len = len;

	enable_irq(info->gpmc_irq_count);
	enable_irq(info->gpmc_irq_fअगरo);

	/* रुकोing क्रम ग_लिखो to complete */
	रुको_क्रम_completion(&info->comp);

	/* रुको क्रम data to flushed-out beक्रमe reset the prefetch */
	tim = 0;
	limit = (loops_per_jअगरfy *  msecs_to_jअगरfies(OMAP_न_अंकD_TIMEOUT_MS));
	करो अणु
		val = पढ़ोl(info->reg.gpmc_prefetch_status);
		val = PREFETCH_STATUS_COUNT(val);
		cpu_relax();
	पूर्ण जबतक (val && (tim++ < limit));

	/* disable and stop the PFPW engine */
	omap_prefetch_reset(info->gpmc_cs, info);
	वापस;

out_copy:
	अगर (info->nand.options & न_अंकD_BUSWIDTH_16)
		omap_ग_लिखो_buf16(mtd, buf, len);
	अन्यथा
		omap_ग_लिखो_buf8(mtd, buf, len);
पूर्ण

/**
 * gen_true_ecc - This function will generate true ECC value
 * @ecc_buf: buffer to store ecc code
 *
 * This generated true ECC value can be used when correcting
 * data पढ़ो from न_अंकD flash memory core
 */
अटल व्योम gen_true_ecc(u8 *ecc_buf)
अणु
	u32 पंचांगp = ecc_buf[0] | (ecc_buf[1] << 16) |
		((ecc_buf[2] & 0xF0) << 20) | ((ecc_buf[2] & 0x0F) << 8);

	ecc_buf[0] = ~(P64o(पंचांगp) | P64e(पंचांगp) | P32o(पंचांगp) | P32e(पंचांगp) |
			P16o(पंचांगp) | P16e(पंचांगp) | P8o(पंचांगp) | P8e(पंचांगp));
	ecc_buf[1] = ~(P1024o(पंचांगp) | P1024e(पंचांगp) | P512o(पंचांगp) | P512e(पंचांगp) |
			P256o(पंचांगp) | P256e(पंचांगp) | P128o(पंचांगp) | P128e(पंचांगp));
	ecc_buf[2] = ~(P4o(पंचांगp) | P4e(पंचांगp) | P2o(पंचांगp) | P2e(पंचांगp) | P1o(पंचांगp) |
			P1e(पंचांगp) | P2048o(पंचांगp) | P2048e(पंचांगp));
पूर्ण

/**
 * omap_compare_ecc - Detect (2 bits) and correct (1 bit) error in data
 * @ecc_data1:  ecc code from nand spare area
 * @ecc_data2:  ecc code from hardware रेजिस्टर obtained from hardware ecc
 * @page_data:  page data
 *
 * This function compares two ECC's and indicates अगर there is an error.
 * If the error can be corrected it will be corrected to the buffer.
 * If there is no error, %0 is वापसed. If there is an error but it
 * was corrected, %1 is वापसed. Otherwise, %-1 is वापसed.
 */
अटल पूर्णांक omap_compare_ecc(u8 *ecc_data1,	/* पढ़ो from न_अंकD memory */
			    u8 *ecc_data2,	/* पढ़ो from रेजिस्टर */
			    u8 *page_data)
अणु
	uपूर्णांक	i;
	u8	पंचांगp0_bit[8], पंचांगp1_bit[8], पंचांगp2_bit[8];
	u8	comp0_bit[8], comp1_bit[8], comp2_bit[8];
	u8	ecc_bit[24];
	u8	ecc_sum = 0;
	u8	find_bit = 0;
	uपूर्णांक	find_byte = 0;
	पूर्णांक	isEccFF;

	isEccFF = ((*(u32 *)ecc_data1 & 0xFFFFFF) == 0xFFFFFF);

	gen_true_ecc(ecc_data1);
	gen_true_ecc(ecc_data2);

	क्रम (i = 0; i <= 2; i++) अणु
		*(ecc_data1 + i) = ~(*(ecc_data1 + i));
		*(ecc_data2 + i) = ~(*(ecc_data2 + i));
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		पंचांगp0_bit[i]     = *ecc_data1 % 2;
		*ecc_data1	= *ecc_data1 / 2;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		पंचांगp1_bit[i]	 = *(ecc_data1 + 1) % 2;
		*(ecc_data1 + 1) = *(ecc_data1 + 1) / 2;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		पंचांगp2_bit[i]	 = *(ecc_data1 + 2) % 2;
		*(ecc_data1 + 2) = *(ecc_data1 + 2) / 2;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		comp0_bit[i]     = *ecc_data2 % 2;
		*ecc_data2       = *ecc_data2 / 2;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		comp1_bit[i]     = *(ecc_data2 + 1) % 2;
		*(ecc_data2 + 1) = *(ecc_data2 + 1) / 2;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		comp2_bit[i]     = *(ecc_data2 + 2) % 2;
		*(ecc_data2 + 2) = *(ecc_data2 + 2) / 2;
	पूर्ण

	क्रम (i = 0; i < 6; i++)
		ecc_bit[i] = पंचांगp2_bit[i + 2] ^ comp2_bit[i + 2];

	क्रम (i = 0; i < 8; i++)
		ecc_bit[i + 6] = पंचांगp0_bit[i] ^ comp0_bit[i];

	क्रम (i = 0; i < 8; i++)
		ecc_bit[i + 14] = पंचांगp1_bit[i] ^ comp1_bit[i];

	ecc_bit[22] = पंचांगp2_bit[0] ^ comp2_bit[0];
	ecc_bit[23] = पंचांगp2_bit[1] ^ comp2_bit[1];

	क्रम (i = 0; i < 24; i++)
		ecc_sum += ecc_bit[i];

	चयन (ecc_sum) अणु
	हाल 0:
		/* Not reached because this function is not called अगर
		 *  ECC values are equal
		 */
		वापस 0;

	हाल 1:
		/* Uncorrectable error */
		pr_debug("ECC UNCORRECTED_ERROR 1\n");
		वापस -EBADMSG;

	हाल 11:
		/* UN-Correctable error */
		pr_debug("ECC UNCORRECTED_ERROR B\n");
		वापस -EBADMSG;

	हाल 12:
		/* Correctable error */
		find_byte = (ecc_bit[23] << 8) +
			    (ecc_bit[21] << 7) +
			    (ecc_bit[19] << 6) +
			    (ecc_bit[17] << 5) +
			    (ecc_bit[15] << 4) +
			    (ecc_bit[13] << 3) +
			    (ecc_bit[11] << 2) +
			    (ecc_bit[9]  << 1) +
			    ecc_bit[7];

		find_bit = (ecc_bit[5] << 2) + (ecc_bit[3] << 1) + ecc_bit[1];

		pr_debug("Correcting single bit ECC error at offset: "
				"%d, bit: %d\n", find_byte, find_bit);

		page_data[find_byte] ^= (1 << find_bit);

		वापस 1;
	शेष:
		अगर (isEccFF) अणु
			अगर (ecc_data2[0] == 0 &&
			    ecc_data2[1] == 0 &&
			    ecc_data2[2] == 0)
				वापस 0;
		पूर्ण
		pr_debug("UNCORRECTED_ERROR default\n");
		वापस -EBADMSG;
	पूर्ण
पूर्ण

/**
 * omap_correct_data - Compares the ECC पढ़ो with HW generated ECC
 * @chip: न_अंकD chip object
 * @dat: page data
 * @पढ़ो_ecc: ecc पढ़ो from nand flash
 * @calc_ecc: ecc पढ़ो from HW ECC रेजिस्टरs
 *
 * Compares the ecc पढ़ो from nand spare area with ECC रेजिस्टरs values
 * and अगर ECC's mismatched, it will call 'omap_compare_ecc' क्रम error
 * detection and correction. If there are no errors, %0 is वापसed. If
 * there were errors and all of the errors were corrected, the number of
 * corrected errors is वापसed. If uncorrectable errors exist, %-1 is
 * वापसed.
 */
अटल पूर्णांक omap_correct_data(काष्ठा nand_chip *chip, u_अक्षर *dat,
			     u_अक्षर *पढ़ो_ecc, u_अक्षर *calc_ecc)
अणु
	काष्ठा omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	पूर्णांक blockCnt = 0, i = 0, ret = 0;
	पूर्णांक stat = 0;

	/* Ex न_अंकD_ECC_HW12_2048 */
	अगर (info->nand.ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_HOST &&
	    info->nand.ecc.size == 2048)
		blockCnt = 4;
	अन्यथा
		blockCnt = 1;

	क्रम (i = 0; i < blockCnt; i++) अणु
		अगर (स_भेद(पढ़ो_ecc, calc_ecc, 3) != 0) अणु
			ret = omap_compare_ecc(पढ़ो_ecc, calc_ecc, dat);
			अगर (ret < 0)
				वापस ret;
			/* keep track of the number of corrected errors */
			stat += ret;
		पूर्ण
		पढ़ो_ecc += 3;
		calc_ecc += 3;
		dat      += 512;
	पूर्ण
	वापस stat;
पूर्ण

/**
 * omap_calcuate_ecc - Generate non-inverted ECC bytes.
 * @chip: न_अंकD chip object
 * @dat: The poपूर्णांकer to data on which ecc is computed
 * @ecc_code: The ecc_code buffer
 *
 * Using noninverted ECC can be considered ugly since writing a blank
 * page ie. padding will clear the ECC bytes. This is no problem as दीर्घ
 * nobody is trying to ग_लिखो data on the seemingly unused page. Reading
 * an erased page will produce an ECC mismatch between generated and पढ़ो
 * ECC bytes that has to be dealt with separately.
 */
अटल पूर्णांक omap_calculate_ecc(काष्ठा nand_chip *chip, स्थिर u_अक्षर *dat,
			      u_अक्षर *ecc_code)
अणु
	काष्ठा omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	u32 val;

	val = पढ़ोl(info->reg.gpmc_ecc_config);
	अगर (((val >> ECC_CONFIG_CS_SHIFT) & CS_MASK) != info->gpmc_cs)
		वापस -EINVAL;

	/* पढ़ो ecc result */
	val = पढ़ोl(info->reg.gpmc_ecc1_result);
	*ecc_code++ = val;          /* P128e, ..., P1e */
	*ecc_code++ = val >> 16;    /* P128o, ..., P1o */
	/* P2048o, P1024o, P512o, P256o, P2048e, P1024e, P512e, P256e */
	*ecc_code++ = ((val >> 8) & 0x0f) | ((val >> 20) & 0xf0);

	वापस 0;
पूर्ण

/**
 * omap_enable_hwecc - This function enables the hardware ecc functionality
 * @chip: न_अंकD chip object
 * @mode: Read/Write mode
 */
अटल व्योम omap_enable_hwecc(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	काष्ठा omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	अचिन्हित पूर्णांक dev_width = (chip->options & न_अंकD_BUSWIDTH_16) ? 1 : 0;
	u32 val;

	/* clear ecc and enable bits */
	val = ECCCLEAR | ECC1;
	ग_लिखोl(val, info->reg.gpmc_ecc_control);

	/* program ecc and result sizes */
	val = ((((info->nand.ecc.size >> 1) - 1) << ECCSIZE1_SHIFT) |
			 ECC1RESULTSIZE);
	ग_लिखोl(val, info->reg.gpmc_ecc_size_config);

	चयन (mode) अणु
	हाल न_अंकD_ECC_READ:
	हाल न_अंकD_ECC_WRITE:
		ग_लिखोl(ECCCLEAR | ECC1, info->reg.gpmc_ecc_control);
		अवरोध;
	हाल न_अंकD_ECC_READSYN:
		ग_लिखोl(ECCCLEAR, info->reg.gpmc_ecc_control);
		अवरोध;
	शेष:
		dev_info(&info->pdev->dev,
			"error: unrecognized Mode[%d]!\n", mode);
		अवरोध;
	पूर्ण

	/* (ECC 16 or 8 bit col) | ( CS  )  | ECC Enable */
	val = (dev_width << 7) | (info->gpmc_cs << 1) | (0x1);
	ग_लिखोl(val, info->reg.gpmc_ecc_config);
पूर्ण

/**
 * omap_रुको - रुको until the command is करोne
 * @this: न_अंकD Chip काष्ठाure
 *
 * Wait function is called during Program and erase operations and
 * the way it is called from MTD layer, we should रुको till the न_अंकD
 * chip is पढ़ोy after the programming/erase operation has completed.
 *
 * Erase can take up to 400ms and program up to 20ms according to
 * general न_अंकD and SmartMedia specs
 */
अटल पूर्णांक omap_रुको(काष्ठा nand_chip *this)
अणु
	काष्ठा omap_nand_info *info = mtd_to_omap(nand_to_mtd(this));
	अचिन्हित दीर्घ समयo = jअगरfies;
	पूर्णांक status;

	समयo += msecs_to_jअगरfies(400);

	ग_लिखोb(न_अंकD_CMD_STATUS & 0xFF, info->reg.gpmc_nand_command);
	जबतक (समय_beक्रमe(jअगरfies, समयo)) अणु
		status = पढ़ोb(info->reg.gpmc_nand_data);
		अगर (status & न_अंकD_STATUS_READY)
			अवरोध;
		cond_resched();
	पूर्ण

	status = पढ़ोb(info->reg.gpmc_nand_data);
	वापस status;
पूर्ण

/**
 * omap_dev_पढ़ोy - checks the न_अंकD Ready GPIO line
 * @chip: न_अंकD chip object
 *
 * Returns true अगर पढ़ोy and false अगर busy.
 */
अटल पूर्णांक omap_dev_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	काष्ठा omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));

	वापस gpiod_get_value(info->पढ़ोy_gpiod);
पूर्ण

/**
 * omap_enable_hwecc_bch - Program GPMC to perक्रमm BCH ECC calculation
 * @chip: न_अंकD chip object
 * @mode: Read/Write mode
 *
 * When using BCH with SW correction (i.e. no ELM), sector size is set
 * to 512 bytes and we use BCH_WRAPMODE_6 wrapping mode
 * क्रम both पढ़ोing and writing with:
 * eccsize0 = 0  (no additional रक्षित byte in spare area)
 * eccsize1 = 32 (skip 32 nibbles = 16 bytes per sector in spare area)
 */
अटल व्योम __maybe_unused omap_enable_hwecc_bch(काष्ठा nand_chip *chip,
						 पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक bch_type;
	अचिन्हित पूर्णांक dev_width, nsectors;
	काष्ठा omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	क्रमागत omap_ecc ecc_opt = info->ecc_opt;
	u32 val, wr_mode;
	अचिन्हित पूर्णांक ecc_size1, ecc_size0;

	/* GPMC configurations क्रम calculating ECC */
	चयन (ecc_opt) अणु
	हाल OMAP_ECC_BCH4_CODE_HW_DETECTION_SW:
		bch_type = 0;
		nsectors = 1;
		wr_mode	  = BCH_WRAPMODE_6;
		ecc_size0 = BCH_ECC_SIZE0;
		ecc_size1 = BCH_ECC_SIZE1;
		अवरोध;
	हाल OMAP_ECC_BCH4_CODE_HW:
		bch_type = 0;
		nsectors = chip->ecc.steps;
		अगर (mode == न_अंकD_ECC_READ) अणु
			wr_mode	  = BCH_WRAPMODE_1;
			ecc_size0 = BCH4R_ECC_SIZE0;
			ecc_size1 = BCH4R_ECC_SIZE1;
		पूर्ण अन्यथा अणु
			wr_mode   = BCH_WRAPMODE_6;
			ecc_size0 = BCH_ECC_SIZE0;
			ecc_size1 = BCH_ECC_SIZE1;
		पूर्ण
		अवरोध;
	हाल OMAP_ECC_BCH8_CODE_HW_DETECTION_SW:
		bch_type = 1;
		nsectors = 1;
		wr_mode	  = BCH_WRAPMODE_6;
		ecc_size0 = BCH_ECC_SIZE0;
		ecc_size1 = BCH_ECC_SIZE1;
		अवरोध;
	हाल OMAP_ECC_BCH8_CODE_HW:
		bch_type = 1;
		nsectors = chip->ecc.steps;
		अगर (mode == न_अंकD_ECC_READ) अणु
			wr_mode	  = BCH_WRAPMODE_1;
			ecc_size0 = BCH8R_ECC_SIZE0;
			ecc_size1 = BCH8R_ECC_SIZE1;
		पूर्ण अन्यथा अणु
			wr_mode   = BCH_WRAPMODE_6;
			ecc_size0 = BCH_ECC_SIZE0;
			ecc_size1 = BCH_ECC_SIZE1;
		पूर्ण
		अवरोध;
	हाल OMAP_ECC_BCH16_CODE_HW:
		bch_type = 0x2;
		nsectors = chip->ecc.steps;
		अगर (mode == न_अंकD_ECC_READ) अणु
			wr_mode	  = 0x01;
			ecc_size0 = 52; /* ECC bits in nibbles per sector */
			ecc_size1 = 0;  /* non-ECC bits in nibbles per sector */
		पूर्ण अन्यथा अणु
			wr_mode	  = 0x01;
			ecc_size0 = 0;  /* extra bits in nibbles per sector */
			ecc_size1 = 52; /* OOB bits in nibbles per sector */
		पूर्ण
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	ग_लिखोl(ECC1, info->reg.gpmc_ecc_control);

	/* Configure ecc size क्रम BCH */
	val = (ecc_size1 << ECCSIZE1_SHIFT) | (ecc_size0 << ECCSIZE0_SHIFT);
	ग_लिखोl(val, info->reg.gpmc_ecc_size_config);

	dev_width = (chip->options & न_अंकD_BUSWIDTH_16) ? 1 : 0;

	/* BCH configuration */
	val = ((1                        << 16) | /* enable BCH */
	       (bch_type		 << 12) | /* BCH4/BCH8/BCH16 */
	       (wr_mode                  <<  8) | /* wrap mode */
	       (dev_width                <<  7) | /* bus width */
	       (((nsectors-1) & 0x7)     <<  4) | /* number of sectors */
	       (info->gpmc_cs            <<  1) | /* ECC CS */
	       (0x1));                            /* enable ECC */

	ग_लिखोl(val, info->reg.gpmc_ecc_config);

	/* Clear ecc and enable bits */
	ग_लिखोl(ECCCLEAR | ECC1, info->reg.gpmc_ecc_control);
पूर्ण

अटल u8  bch4_polynomial[] = अणु0x28, 0x13, 0xcc, 0x39, 0x96, 0xac, 0x7fपूर्ण;
अटल u8  bch8_polynomial[] = अणु0xef, 0x51, 0x2e, 0x09, 0xed, 0x93, 0x9a, 0xc2,
				0x97, 0x79, 0xe5, 0x24, 0xb5पूर्ण;

/**
 * _omap_calculate_ecc_bch - Generate ECC bytes क्रम one sector
 * @mtd:	MTD device काष्ठाure
 * @dat:	The poपूर्णांकer to data on which ecc is computed
 * @ecc_calc:	The ecc_code buffer
 * @i:		The sector number (क्रम a multi sector page)
 *
 * Support calculating of BCH4/8/16 ECC vectors क्रम one sector
 * within a page. Sector number is in @i.
 */
अटल पूर्णांक _omap_calculate_ecc_bch(काष्ठा mtd_info *mtd,
				   स्थिर u_अक्षर *dat, u_अक्षर *ecc_calc, पूर्णांक i)
अणु
	काष्ठा omap_nand_info *info = mtd_to_omap(mtd);
	पूर्णांक eccbytes	= info->nand.ecc.bytes;
	काष्ठा gpmc_nand_regs	*gpmc_regs = &info->reg;
	u8 *ecc_code;
	अचिन्हित दीर्घ bch_val1, bch_val2, bch_val3, bch_val4;
	u32 val;
	पूर्णांक j;

	ecc_code = ecc_calc;
	चयन (info->ecc_opt) अणु
	हाल OMAP_ECC_BCH8_CODE_HW_DETECTION_SW:
	हाल OMAP_ECC_BCH8_CODE_HW:
		bch_val1 = पढ़ोl(gpmc_regs->gpmc_bch_result0[i]);
		bch_val2 = पढ़ोl(gpmc_regs->gpmc_bch_result1[i]);
		bch_val3 = पढ़ोl(gpmc_regs->gpmc_bch_result2[i]);
		bch_val4 = पढ़ोl(gpmc_regs->gpmc_bch_result3[i]);
		*ecc_code++ = (bch_val4 & 0xFF);
		*ecc_code++ = ((bch_val3 >> 24) & 0xFF);
		*ecc_code++ = ((bch_val3 >> 16) & 0xFF);
		*ecc_code++ = ((bch_val3 >> 8) & 0xFF);
		*ecc_code++ = (bch_val3 & 0xFF);
		*ecc_code++ = ((bch_val2 >> 24) & 0xFF);
		*ecc_code++ = ((bch_val2 >> 16) & 0xFF);
		*ecc_code++ = ((bch_val2 >> 8) & 0xFF);
		*ecc_code++ = (bch_val2 & 0xFF);
		*ecc_code++ = ((bch_val1 >> 24) & 0xFF);
		*ecc_code++ = ((bch_val1 >> 16) & 0xFF);
		*ecc_code++ = ((bch_val1 >> 8) & 0xFF);
		*ecc_code++ = (bch_val1 & 0xFF);
		अवरोध;
	हाल OMAP_ECC_BCH4_CODE_HW_DETECTION_SW:
	हाल OMAP_ECC_BCH4_CODE_HW:
		bch_val1 = पढ़ोl(gpmc_regs->gpmc_bch_result0[i]);
		bch_val2 = पढ़ोl(gpmc_regs->gpmc_bch_result1[i]);
		*ecc_code++ = ((bch_val2 >> 12) & 0xFF);
		*ecc_code++ = ((bch_val2 >> 4) & 0xFF);
		*ecc_code++ = ((bch_val2 & 0xF) << 4) |
			((bch_val1 >> 28) & 0xF);
		*ecc_code++ = ((bch_val1 >> 20) & 0xFF);
		*ecc_code++ = ((bch_val1 >> 12) & 0xFF);
		*ecc_code++ = ((bch_val1 >> 4) & 0xFF);
		*ecc_code++ = ((bch_val1 & 0xF) << 4);
		अवरोध;
	हाल OMAP_ECC_BCH16_CODE_HW:
		val = पढ़ोl(gpmc_regs->gpmc_bch_result6[i]);
		ecc_code[0]  = ((val >>  8) & 0xFF);
		ecc_code[1]  = ((val >>  0) & 0xFF);
		val = पढ़ोl(gpmc_regs->gpmc_bch_result5[i]);
		ecc_code[2]  = ((val >> 24) & 0xFF);
		ecc_code[3]  = ((val >> 16) & 0xFF);
		ecc_code[4]  = ((val >>  8) & 0xFF);
		ecc_code[5]  = ((val >>  0) & 0xFF);
		val = पढ़ोl(gpmc_regs->gpmc_bch_result4[i]);
		ecc_code[6]  = ((val >> 24) & 0xFF);
		ecc_code[7]  = ((val >> 16) & 0xFF);
		ecc_code[8]  = ((val >>  8) & 0xFF);
		ecc_code[9]  = ((val >>  0) & 0xFF);
		val = पढ़ोl(gpmc_regs->gpmc_bch_result3[i]);
		ecc_code[10] = ((val >> 24) & 0xFF);
		ecc_code[11] = ((val >> 16) & 0xFF);
		ecc_code[12] = ((val >>  8) & 0xFF);
		ecc_code[13] = ((val >>  0) & 0xFF);
		val = पढ़ोl(gpmc_regs->gpmc_bch_result2[i]);
		ecc_code[14] = ((val >> 24) & 0xFF);
		ecc_code[15] = ((val >> 16) & 0xFF);
		ecc_code[16] = ((val >>  8) & 0xFF);
		ecc_code[17] = ((val >>  0) & 0xFF);
		val = पढ़ोl(gpmc_regs->gpmc_bch_result1[i]);
		ecc_code[18] = ((val >> 24) & 0xFF);
		ecc_code[19] = ((val >> 16) & 0xFF);
		ecc_code[20] = ((val >>  8) & 0xFF);
		ecc_code[21] = ((val >>  0) & 0xFF);
		val = पढ़ोl(gpmc_regs->gpmc_bch_result0[i]);
		ecc_code[22] = ((val >> 24) & 0xFF);
		ecc_code[23] = ((val >> 16) & 0xFF);
		ecc_code[24] = ((val >>  8) & 0xFF);
		ecc_code[25] = ((val >>  0) & 0xFF);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* ECC scheme specअगरic syndrome customizations */
	चयन (info->ecc_opt) अणु
	हाल OMAP_ECC_BCH4_CODE_HW_DETECTION_SW:
		/* Add स्थिरant polynomial to reमुख्यder, so that
		 * ECC of blank pages results in 0x0 on पढ़ोing back
		 */
		क्रम (j = 0; j < eccbytes; j++)
			ecc_calc[j] ^= bch4_polynomial[j];
		अवरोध;
	हाल OMAP_ECC_BCH4_CODE_HW:
		/* Set  8th ECC byte as 0x0 क्रम ROM compatibility */
		ecc_calc[eccbytes - 1] = 0x0;
		अवरोध;
	हाल OMAP_ECC_BCH8_CODE_HW_DETECTION_SW:
		/* Add स्थिरant polynomial to reमुख्यder, so that
		 * ECC of blank pages results in 0x0 on पढ़ोing back
		 */
		क्रम (j = 0; j < eccbytes; j++)
			ecc_calc[j] ^= bch8_polynomial[j];
		अवरोध;
	हाल OMAP_ECC_BCH8_CODE_HW:
		/* Set 14th ECC byte as 0x0 क्रम ROM compatibility */
		ecc_calc[eccbytes - 1] = 0x0;
		अवरोध;
	हाल OMAP_ECC_BCH16_CODE_HW:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * omap_calculate_ecc_bch_sw - ECC generator क्रम sector क्रम SW based correction
 * @chip:	न_अंकD chip object
 * @dat:	The poपूर्णांकer to data on which ecc is computed
 * @ecc_calc:	Buffer storing the calculated ECC bytes
 *
 * Support calculating of BCH4/8/16 ECC vectors क्रम one sector. This is used
 * when SW based correction is required as ECC is required क्रम one sector
 * at a समय.
 */
अटल पूर्णांक omap_calculate_ecc_bch_sw(काष्ठा nand_chip *chip,
				     स्थिर u_अक्षर *dat, u_अक्षर *ecc_calc)
अणु
	वापस _omap_calculate_ecc_bch(nand_to_mtd(chip), dat, ecc_calc, 0);
पूर्ण

/**
 * omap_calculate_ecc_bch_multi - Generate ECC क्रम multiple sectors
 * @mtd:	MTD device काष्ठाure
 * @dat:	The poपूर्णांकer to data on which ecc is computed
 * @ecc_calc:	Buffer storing the calculated ECC bytes
 *
 * Support calculating of BCH4/8/16 ecc vectors क्रम the entire page in one go.
 */
अटल पूर्णांक omap_calculate_ecc_bch_multi(काष्ठा mtd_info *mtd,
					स्थिर u_अक्षर *dat, u_अक्षर *ecc_calc)
अणु
	काष्ठा omap_nand_info *info = mtd_to_omap(mtd);
	पूर्णांक eccbytes = info->nand.ecc.bytes;
	अचिन्हित दीर्घ nsectors;
	पूर्णांक i, ret;

	nsectors = ((पढ़ोl(info->reg.gpmc_ecc_config) >> 4) & 0x7) + 1;
	क्रम (i = 0; i < nsectors; i++) अणु
		ret = _omap_calculate_ecc_bch(mtd, dat, ecc_calc, i);
		अगर (ret)
			वापस ret;

		ecc_calc += eccbytes;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * erased_sector_bitflips - count bit flips
 * @data:	data sector buffer
 * @oob:	oob buffer
 * @info:	omap_nand_info
 *
 * Check the bit flips in erased page falls below correctable level.
 * If falls below, report the page as erased with correctable bit
 * flip, अन्यथा report as uncorrectable page.
 */
अटल पूर्णांक erased_sector_bitflips(u_अक्षर *data, u_अक्षर *oob,
		काष्ठा omap_nand_info *info)
अणु
	पूर्णांक flip_bits = 0, i;

	क्रम (i = 0; i < info->nand.ecc.size; i++) अणु
		flip_bits += hweight8(~data[i]);
		अगर (flip_bits > info->nand.ecc.strength)
			वापस 0;
	पूर्ण

	क्रम (i = 0; i < info->nand.ecc.bytes - 1; i++) अणु
		flip_bits += hweight8(~oob[i]);
		अगर (flip_bits > info->nand.ecc.strength)
			वापस 0;
	पूर्ण

	/*
	 * Bit flips falls in correctable level.
	 * Fill data area with 0xFF
	 */
	अगर (flip_bits) अणु
		स_रखो(data, 0xFF, info->nand.ecc.size);
		स_रखो(oob, 0xFF, info->nand.ecc.bytes);
	पूर्ण

	वापस flip_bits;
पूर्ण

/**
 * omap_elm_correct_data - corrects page data area in हाल error reported
 * @chip:	न_अंकD chip object
 * @data:	page data
 * @पढ़ो_ecc:	ecc पढ़ो from nand flash
 * @calc_ecc:	ecc पढ़ो from HW ECC रेजिस्टरs
 *
 * Calculated ecc vector reported as zero in हाल of non-error pages.
 * In हाल of non-zero ecc vector, first filter out erased-pages, and
 * then process data via ELM to detect bit-flips.
 */
अटल पूर्णांक omap_elm_correct_data(काष्ठा nand_chip *chip, u_अक्षर *data,
				 u_अक्षर *पढ़ो_ecc, u_अक्षर *calc_ecc)
अणु
	काष्ठा omap_nand_info *info = mtd_to_omap(nand_to_mtd(chip));
	काष्ठा nand_ecc_ctrl *ecc = &info->nand.ecc;
	पूर्णांक eccsteps = info->nand.ecc.steps;
	पूर्णांक i , j, stat = 0;
	पूर्णांक eccflag, actual_eccbytes;
	काष्ठा elm_errorvec err_vec[ERROR_VECTOR_MAX];
	u_अक्षर *ecc_vec = calc_ecc;
	u_अक्षर *spare_ecc = पढ़ो_ecc;
	u_अक्षर *erased_ecc_vec;
	u_अक्षर *buf;
	पूर्णांक bitflip_count;
	bool is_error_reported = false;
	u32 bit_pos, byte_pos, error_max, pos;
	पूर्णांक err;

	चयन (info->ecc_opt) अणु
	हाल OMAP_ECC_BCH4_CODE_HW:
		/* omit  7th ECC byte reserved क्रम ROM code compatibility */
		actual_eccbytes = ecc->bytes - 1;
		erased_ecc_vec = bch4_vector;
		अवरोध;
	हाल OMAP_ECC_BCH8_CODE_HW:
		/* omit 14th ECC byte reserved क्रम ROM code compatibility */
		actual_eccbytes = ecc->bytes - 1;
		erased_ecc_vec = bch8_vector;
		अवरोध;
	हाल OMAP_ECC_BCH16_CODE_HW:
		actual_eccbytes = ecc->bytes;
		erased_ecc_vec = bch16_vector;
		अवरोध;
	शेष:
		dev_err(&info->pdev->dev, "invalid driver configuration\n");
		वापस -EINVAL;
	पूर्ण

	/* Initialize elm error vector to zero */
	स_रखो(err_vec, 0, माप(err_vec));

	क्रम (i = 0; i < eccsteps ; i++) अणु
		eccflag = 0;	/* initialize eccflag */

		/*
		 * Check any error reported,
		 * In हाल of error, non zero ecc reported.
		 */
		क्रम (j = 0; j < actual_eccbytes; j++) अणु
			अगर (calc_ecc[j] != 0) अणु
				eccflag = 1; /* non zero ecc, error present */
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (eccflag == 1) अणु
			अगर (स_भेद(calc_ecc, erased_ecc_vec,
						actual_eccbytes) == 0) अणु
				/*
				 * calc_ecc[] matches pattern क्रम ECC(all 0xff)
				 * so this is definitely an erased-page
				 */
			पूर्ण अन्यथा अणु
				buf = &data[info->nand.ecc.size * i];
				/*
				 * count number of 0-bits in पढ़ो_buf.
				 * This check can be हटाओd once a similar
				 * check is पूर्णांकroduced in generic न_अंकD driver
				 */
				bitflip_count = erased_sector_bitflips(
						buf, पढ़ो_ecc, info);
				अगर (bitflip_count) अणु
					/*
					 * number of 0-bits within ECC limits
					 * So this may be an erased-page
					 */
					stat += bitflip_count;
				पूर्ण अन्यथा अणु
					/*
					 * Too many 0-bits. It may be a
					 * - programmed-page, OR
					 * - erased-page with many bit-flips
					 * So this page requires check by ELM
					 */
					err_vec[i].error_reported = true;
					is_error_reported = true;
				पूर्ण
			पूर्ण
		पूर्ण

		/* Update the ecc vector */
		calc_ecc += ecc->bytes;
		पढ़ो_ecc += ecc->bytes;
	पूर्ण

	/* Check अगर any error reported */
	अगर (!is_error_reported)
		वापस stat;

	/* Decode BCH error using ELM module */
	elm_decode_bch_error_page(info->elm_dev, ecc_vec, err_vec);

	err = 0;
	क्रम (i = 0; i < eccsteps; i++) अणु
		अगर (err_vec[i].error_uncorrectable) अणु
			dev_err(&info->pdev->dev,
				"uncorrectable bit-flips found\n");
			err = -EBADMSG;
		पूर्ण अन्यथा अगर (err_vec[i].error_reported) अणु
			क्रम (j = 0; j < err_vec[i].error_count; j++) अणु
				चयन (info->ecc_opt) अणु
				हाल OMAP_ECC_BCH4_CODE_HW:
					/* Add 4 bits to take care of padding */
					pos = err_vec[i].error_loc[j] +
						BCH4_BIT_PAD;
					अवरोध;
				हाल OMAP_ECC_BCH8_CODE_HW:
				हाल OMAP_ECC_BCH16_CODE_HW:
					pos = err_vec[i].error_loc[j];
					अवरोध;
				शेष:
					वापस -EINVAL;
				पूर्ण
				error_max = (ecc->size + actual_eccbytes) * 8;
				/* Calculate bit position of error */
				bit_pos = pos % 8;

				/* Calculate byte position of error */
				byte_pos = (error_max - pos - 1) / 8;

				अगर (pos < error_max) अणु
					अगर (byte_pos < 512) अणु
						pr_debug("bitflip@dat[%d]=%x\n",
						     byte_pos, data[byte_pos]);
						data[byte_pos] ^= 1 << bit_pos;
					पूर्ण अन्यथा अणु
						pr_debug("bitflip@oob[%d]=%x\n",
							(byte_pos - 512),
						     spare_ecc[byte_pos - 512]);
						spare_ecc[byte_pos - 512] ^=
							1 << bit_pos;
					पूर्ण
				पूर्ण अन्यथा अणु
					dev_err(&info->pdev->dev,
						"invalid bit-flip @ %d:%d\n",
						byte_pos, bit_pos);
					err = -EBADMSG;
				पूर्ण
			पूर्ण
		पूर्ण

		/* Update number of correctable errors */
		stat = max_t(अचिन्हित पूर्णांक, stat, err_vec[i].error_count);

		/* Update page data with sector size */
		data += ecc->size;
		spare_ecc += ecc->bytes;
	पूर्ण

	वापस (err) ? err : stat;
पूर्ण

/**
 * omap_ग_लिखो_page_bch - BCH ecc based ग_लिखो page function क्रम entire page
 * @chip:		nand chip info काष्ठाure
 * @buf:		data buffer
 * @oob_required:	must ग_लिखो chip->oob_poi to OOB
 * @page:		page
 *
 * Custom ग_लिखो page method evolved to support multi sector writing in one shot
 */
अटल पूर्णांक omap_ग_लिखो_page_bch(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
			       पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;
	uपूर्णांक8_t *ecc_calc = chip->ecc.calc_buf;

	nand_prog_page_begin_op(chip, page, 0, शून्य, 0);

	/* Enable GPMC ecc engine */
	chip->ecc.hwctl(chip, न_अंकD_ECC_WRITE);

	/* Write data */
	chip->legacy.ग_लिखो_buf(chip, buf, mtd->ग_लिखोsize);

	/* Update ecc vector from GPMC result रेजिस्टरs */
	omap_calculate_ecc_bch_multi(mtd, buf, &ecc_calc[0]);

	ret = mtd_ooblayout_set_eccbytes(mtd, ecc_calc, chip->oob_poi, 0,
					 chip->ecc.total);
	अगर (ret)
		वापस ret;

	/* Write ecc vector to OOB area */
	chip->legacy.ग_लिखो_buf(chip, chip->oob_poi, mtd->oobsize);

	वापस nand_prog_page_end_op(chip);
पूर्ण

/**
 * omap_ग_लिखो_subpage_bch - BCH hardware ECC based subpage ग_लिखो
 * @chip:	nand chip info काष्ठाure
 * @offset:	column address of subpage within the page
 * @data_len:	data length
 * @buf:	data buffer
 * @oob_required: must ग_लिखो chip->oob_poi to OOB
 * @page: page number to ग_लिखो
 *
 * OMAP optimized subpage ग_लिखो method.
 */
अटल पूर्णांक omap_ग_लिखो_subpage_bch(काष्ठा nand_chip *chip, u32 offset,
				  u32 data_len, स्थिर u8 *buf,
				  पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	u8 *ecc_calc = chip->ecc.calc_buf;
	पूर्णांक ecc_size      = chip->ecc.size;
	पूर्णांक ecc_bytes     = chip->ecc.bytes;
	पूर्णांक ecc_steps     = chip->ecc.steps;
	u32 start_step = offset / ecc_size;
	u32 end_step   = (offset + data_len - 1) / ecc_size;
	पूर्णांक step, ret = 0;

	/*
	 * Write entire page at one go as it would be optimal
	 * as ECC is calculated by hardware.
	 * ECC is calculated क्रम all subpages but we choose
	 * only what we want.
	 */
	nand_prog_page_begin_op(chip, page, 0, शून्य, 0);

	/* Enable GPMC ECC engine */
	chip->ecc.hwctl(chip, न_अंकD_ECC_WRITE);

	/* Write data */
	chip->legacy.ग_लिखो_buf(chip, buf, mtd->ग_लिखोsize);

	क्रम (step = 0; step < ecc_steps; step++) अणु
		/* mask ECC of un-touched subpages by padding 0xFF */
		अगर (step < start_step || step > end_step)
			स_रखो(ecc_calc, 0xff, ecc_bytes);
		अन्यथा
			ret = _omap_calculate_ecc_bch(mtd, buf, ecc_calc, step);

		अगर (ret)
			वापस ret;

		buf += ecc_size;
		ecc_calc += ecc_bytes;
	पूर्ण

	/* copy calculated ECC क्रम whole page to chip->buffer->oob */
	/* this include masked-value(0xFF) क्रम unwritten subpages */
	ecc_calc = chip->ecc.calc_buf;
	ret = mtd_ooblayout_set_eccbytes(mtd, ecc_calc, chip->oob_poi, 0,
					 chip->ecc.total);
	अगर (ret)
		वापस ret;

	/* ग_लिखो OOB buffer to न_अंकD device */
	chip->legacy.ग_लिखो_buf(chip, chip->oob_poi, mtd->oobsize);

	वापस nand_prog_page_end_op(chip);
पूर्ण

/**
 * omap_पढ़ो_page_bch - BCH ecc based page पढ़ो function क्रम entire page
 * @chip:		nand chip info काष्ठाure
 * @buf:		buffer to store पढ़ो data
 * @oob_required:	caller requires OOB data पढ़ो to chip->oob_poi
 * @page:		page number to पढ़ो
 *
 * For BCH ecc scheme, GPMC used क्रम syndrome calculation and ELM module
 * used क्रम error correction.
 * Custom method evolved to support ELM error correction & multi sector
 * पढ़ोing. On पढ़ोing page data area is पढ़ो aदीर्घ with OOB data with
 * ecc engine enabled. ecc vector updated after पढ़ो of OOB data.
 * For non error pages ecc vector reported as zero.
 */
अटल पूर्णांक omap_पढ़ो_page_bch(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
			      पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	uपूर्णांक8_t *ecc_calc = chip->ecc.calc_buf;
	uपूर्णांक8_t *ecc_code = chip->ecc.code_buf;
	पूर्णांक stat, ret;
	अचिन्हित पूर्णांक max_bitflips = 0;

	nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);

	/* Enable GPMC ecc engine */
	chip->ecc.hwctl(chip, न_अंकD_ECC_READ);

	/* Read data */
	chip->legacy.पढ़ो_buf(chip, buf, mtd->ग_लिखोsize);

	/* Read oob bytes */
	nand_change_पढ़ो_column_op(chip,
				   mtd->ग_लिखोsize + BADBLOCK_MARKER_LENGTH,
				   chip->oob_poi + BADBLOCK_MARKER_LENGTH,
				   chip->ecc.total, false);

	/* Calculate ecc bytes */
	omap_calculate_ecc_bch_multi(mtd, buf, ecc_calc);

	ret = mtd_ooblayout_get_eccbytes(mtd, ecc_code, chip->oob_poi, 0,
					 chip->ecc.total);
	अगर (ret)
		वापस ret;

	stat = chip->ecc.correct(chip, buf, ecc_code, ecc_calc);

	अगर (stat < 0) अणु
		mtd->ecc_stats.failed++;
	पूर्ण अन्यथा अणु
		mtd->ecc_stats.corrected += stat;
		max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, stat);
	पूर्ण

	वापस max_bitflips;
पूर्ण

/**
 * is_elm_present - checks क्रम presence of ELM module by scanning DT nodes
 * @info: न_अंकD device काष्ठाure containing platक्रमm data
 * @elm_node: ELM's DT node
 */
अटल bool is_elm_present(काष्ठा omap_nand_info *info,
			   काष्ठा device_node *elm_node)
अणु
	काष्ठा platक्रमm_device *pdev;

	/* check whether elm-id is passed via DT */
	अगर (!elm_node) अणु
		dev_err(&info->pdev->dev, "ELM devicetree node not found\n");
		वापस false;
	पूर्ण
	pdev = of_find_device_by_node(elm_node);
	/* check whether ELM device is रेजिस्टरed */
	अगर (!pdev) अणु
		dev_err(&info->pdev->dev, "ELM device not found\n");
		वापस false;
	पूर्ण
	/* ELM module available, now configure it */
	info->elm_dev = &pdev->dev;
	वापस true;
पूर्ण

अटल bool omap2_nand_ecc_check(काष्ठा omap_nand_info *info)
अणु
	bool ecc_needs_bch, ecc_needs_omap_bch, ecc_needs_elm;

	चयन (info->ecc_opt) अणु
	हाल OMAP_ECC_BCH4_CODE_HW_DETECTION_SW:
	हाल OMAP_ECC_BCH8_CODE_HW_DETECTION_SW:
		ecc_needs_omap_bch = false;
		ecc_needs_bch = true;
		ecc_needs_elm = false;
		अवरोध;
	हाल OMAP_ECC_BCH4_CODE_HW:
	हाल OMAP_ECC_BCH8_CODE_HW:
	हाल OMAP_ECC_BCH16_CODE_HW:
		ecc_needs_omap_bch = true;
		ecc_needs_bch = false;
		ecc_needs_elm = true;
		अवरोध;
	शेष:
		ecc_needs_omap_bch = false;
		ecc_needs_bch = false;
		ecc_needs_elm = false;
		अवरोध;
	पूर्ण

	अगर (ecc_needs_bch && !IS_ENABLED(CONFIG_MTD_न_अंकD_ECC_SW_BCH)) अणु
		dev_err(&info->pdev->dev,
			"CONFIG_MTD_NAND_ECC_SW_BCH not enabled\n");
		वापस false;
	पूर्ण
	अगर (ecc_needs_omap_bch && !IS_ENABLED(CONFIG_MTD_न_अंकD_OMAP_BCH)) अणु
		dev_err(&info->pdev->dev,
			"CONFIG_MTD_NAND_OMAP_BCH not enabled\n");
		वापस false;
	पूर्ण
	अगर (ecc_needs_elm && !is_elm_present(info, info->elm_of_node)) अणु
		dev_err(&info->pdev->dev, "ELM not available\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल स्थिर अक्षर * स्थिर nand_xfer_types[] = अणु
	[न_अंकD_OMAP_PREFETCH_POLLED] = "prefetch-polled",
	[न_अंकD_OMAP_POLLED] = "polled",
	[न_अंकD_OMAP_PREFETCH_DMA] = "prefetch-dma",
	[न_अंकD_OMAP_PREFETCH_IRQ] = "prefetch-irq",
पूर्ण;

अटल पूर्णांक omap_get_dt_info(काष्ठा device *dev, काष्ठा omap_nand_info *info)
अणु
	काष्ठा device_node *child = dev->of_node;
	पूर्णांक i;
	स्थिर अक्षर *s;
	u32 cs;

	अगर (of_property_पढ़ो_u32(child, "reg", &cs) < 0) अणु
		dev_err(dev, "reg not found in DT\n");
		वापस -EINVAL;
	पूर्ण

	info->gpmc_cs = cs;

	/* detect availability of ELM module. Won't be present pre-OMAP4 */
	info->elm_of_node = of_parse_phandle(child, "ti,elm-id", 0);
	अगर (!info->elm_of_node) अणु
		info->elm_of_node = of_parse_phandle(child, "elm_id", 0);
		अगर (!info->elm_of_node)
			dev_dbg(dev, "ti,elm-id not in DT\n");
	पूर्ण

	/* select ecc-scheme क्रम न_अंकD */
	अगर (of_property_पढ़ो_string(child, "ti,nand-ecc-opt", &s)) अणु
		dev_err(dev, "ti,nand-ecc-opt not found\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!म_भेद(s, "sw")) अणु
		info->ecc_opt = OMAP_ECC_HAM1_CODE_SW;
	पूर्ण अन्यथा अगर (!म_भेद(s, "ham1") ||
		   !म_भेद(s, "hw") || !म_भेद(s, "hw-romcode")) अणु
		info->ecc_opt =	OMAP_ECC_HAM1_CODE_HW;
	पूर्ण अन्यथा अगर (!म_भेद(s, "bch4")) अणु
		अगर (info->elm_of_node)
			info->ecc_opt = OMAP_ECC_BCH4_CODE_HW;
		अन्यथा
			info->ecc_opt = OMAP_ECC_BCH4_CODE_HW_DETECTION_SW;
	पूर्ण अन्यथा अगर (!म_भेद(s, "bch8")) अणु
		अगर (info->elm_of_node)
			info->ecc_opt = OMAP_ECC_BCH8_CODE_HW;
		अन्यथा
			info->ecc_opt = OMAP_ECC_BCH8_CODE_HW_DETECTION_SW;
	पूर्ण अन्यथा अगर (!म_भेद(s, "bch16")) अणु
		info->ecc_opt =	OMAP_ECC_BCH16_CODE_HW;
	पूर्ण अन्यथा अणु
		dev_err(dev, "unrecognized value for ti,nand-ecc-opt\n");
		वापस -EINVAL;
	पूर्ण

	/* select data transfer mode */
	अगर (!of_property_पढ़ो_string(child, "ti,nand-xfer-type", &s)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(nand_xfer_types); i++) अणु
			अगर (!strहालcmp(s, nand_xfer_types[i])) अणु
				info->xfer_type = i;
				वापस 0;
			पूर्ण
		पूर्ण

		dev_err(dev, "unrecognized value for ti,nand-xfer-type\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
			      काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा omap_nand_info *info = mtd_to_omap(mtd);
	काष्ठा nand_chip *chip = &info->nand;
	पूर्णांक off = BADBLOCK_MARKER_LENGTH;

	अगर (info->ecc_opt == OMAP_ECC_HAM1_CODE_HW &&
	    !(chip->options & न_अंकD_BUSWIDTH_16))
		off = 1;

	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = off;
	oobregion->length = chip->ecc.total;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
			       काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा omap_nand_info *info = mtd_to_omap(mtd);
	काष्ठा nand_chip *chip = &info->nand;
	पूर्णांक off = BADBLOCK_MARKER_LENGTH;

	अगर (info->ecc_opt == OMAP_ECC_HAM1_CODE_HW &&
	    !(chip->options & न_अंकD_BUSWIDTH_16))
		off = 1;

	अगर (section)
		वापस -दुस्फल;

	off += chip->ecc.total;
	अगर (off >= mtd->oobsize)
		वापस -दुस्फल;

	oobregion->offset = off;
	oobregion->length = mtd->oobsize - off;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops omap_ooblayout_ops = अणु
	.ecc = omap_ooblayout_ecc,
	.मुक्त = omap_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक omap_sw_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	अचिन्हित पूर्णांक nsteps = nanddev_get_ecc_nsteps(nand);
	अचिन्हित पूर्णांक ecc_bytes = nanddev_get_ecc_bytes_per_step(nand);
	पूर्णांक off = BADBLOCK_MARKER_LENGTH;

	अगर (section >= nsteps)
		वापस -दुस्फल;

	/*
	 * When SW correction is employed, one OMAP specअगरic marker byte is
	 * reserved after each ECC step.
	 */
	oobregion->offset = off + (section * (ecc_bytes + 1));
	oobregion->length = ecc_bytes;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_sw_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	अचिन्हित पूर्णांक nsteps = nanddev_get_ecc_nsteps(nand);
	अचिन्हित पूर्णांक ecc_bytes = nanddev_get_ecc_bytes_per_step(nand);
	पूर्णांक off = BADBLOCK_MARKER_LENGTH;

	अगर (section)
		वापस -दुस्फल;

	/*
	 * When SW correction is employed, one OMAP specअगरic marker byte is
	 * reserved after each ECC step.
	 */
	off += ((ecc_bytes + 1) * nsteps);
	अगर (off >= mtd->oobsize)
		वापस -दुस्फल;

	oobregion->offset = off;
	oobregion->length = mtd->oobsize - off;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops omap_sw_ooblayout_ops = अणु
	.ecc = omap_sw_ooblayout_ecc,
	.मुक्त = omap_sw_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक omap_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा omap_nand_info *info = mtd_to_omap(mtd);
	काष्ठा device *dev = &info->pdev->dev;
	पूर्णांक min_oobbytes = BADBLOCK_MARKER_LENGTH;
	पूर्णांक oobbytes_per_step;
	dma_cap_mask_t mask;
	पूर्णांक err;

	अगर (chip->bbt_options & न_अंकD_BBT_USE_FLASH)
		chip->bbt_options |= न_अंकD_BBT_NO_OOB;
	अन्यथा
		chip->options |= न_अंकD_SKIP_BBTSCAN;

	/* Re-populate low-level callbacks based on xfer modes */
	चयन (info->xfer_type) अणु
	हाल न_अंकD_OMAP_PREFETCH_POLLED:
		chip->legacy.पढ़ो_buf = omap_पढ़ो_buf_pref;
		chip->legacy.ग_लिखो_buf = omap_ग_लिखो_buf_pref;
		अवरोध;

	हाल न_अंकD_OMAP_POLLED:
		/* Use nand_base शेषs क्रम अणुपढ़ो,ग_लिखोपूर्ण_buf */
		अवरोध;

	हाल न_अंकD_OMAP_PREFETCH_DMA:
		dma_cap_zero(mask);
		dma_cap_set(DMA_SLAVE, mask);
		info->dma = dma_request_chan(dev->parent, "rxtx");

		अगर (IS_ERR(info->dma)) अणु
			dev_err(dev, "DMA engine request failed\n");
			वापस PTR_ERR(info->dma);
		पूर्ण अन्यथा अणु
			काष्ठा dma_slave_config cfg;

			स_रखो(&cfg, 0, माप(cfg));
			cfg.src_addr = info->phys_base;
			cfg.dst_addr = info->phys_base;
			cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
			cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
			cfg.src_maxburst = 16;
			cfg.dst_maxburst = 16;
			err = dmaengine_slave_config(info->dma, &cfg);
			अगर (err) अणु
				dev_err(dev,
					"DMA engine slave config failed: %d\n",
					err);
				वापस err;
			पूर्ण
			chip->legacy.पढ़ो_buf = omap_पढ़ो_buf_dma_pref;
			chip->legacy.ग_लिखो_buf = omap_ग_लिखो_buf_dma_pref;
		पूर्ण
		अवरोध;

	हाल न_अंकD_OMAP_PREFETCH_IRQ:
		info->gpmc_irq_fअगरo = platक्रमm_get_irq(info->pdev, 0);
		अगर (info->gpmc_irq_fअगरo <= 0)
			वापस -ENODEV;
		err = devm_request_irq(dev, info->gpmc_irq_fअगरo,
				       omap_nand_irq, IRQF_SHARED,
				       "gpmc-nand-fifo", info);
		अगर (err) अणु
			dev_err(dev, "Requesting IRQ %d, error %d\n",
				info->gpmc_irq_fअगरo, err);
			info->gpmc_irq_fअगरo = 0;
			वापस err;
		पूर्ण

		info->gpmc_irq_count = platक्रमm_get_irq(info->pdev, 1);
		अगर (info->gpmc_irq_count <= 0)
			वापस -ENODEV;
		err = devm_request_irq(dev, info->gpmc_irq_count,
				       omap_nand_irq, IRQF_SHARED,
				       "gpmc-nand-count", info);
		अगर (err) अणु
			dev_err(dev, "Requesting IRQ %d, error %d\n",
				info->gpmc_irq_count, err);
			info->gpmc_irq_count = 0;
			वापस err;
		पूर्ण

		chip->legacy.पढ़ो_buf = omap_पढ़ो_buf_irq_pref;
		chip->legacy.ग_लिखो_buf = omap_ग_लिखो_buf_irq_pref;

		अवरोध;

	शेष:
		dev_err(dev, "xfer_type %d not supported!\n", info->xfer_type);
		वापस -EINVAL;
	पूर्ण

	अगर (!omap2_nand_ecc_check(info))
		वापस -EINVAL;

	/*
	 * Bail out earlier to let न_अंकD_ECC_ENGINE_TYPE_SOFT code create its own
	 * ooblayout instead of using ours.
	 */
	अगर (info->ecc_opt == OMAP_ECC_HAM1_CODE_SW) अणु
		chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;
		chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;
		वापस 0;
	पूर्ण

	/* Populate MTD पूर्णांकerface based on ECC scheme */
	चयन (info->ecc_opt) अणु
	हाल OMAP_ECC_HAM1_CODE_HW:
		dev_info(dev, "nand: using OMAP_ECC_HAM1_CODE_HW\n");
		chip->ecc.engine_type	= न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
		chip->ecc.bytes		= 3;
		chip->ecc.size		= 512;
		chip->ecc.strength	= 1;
		chip->ecc.calculate	= omap_calculate_ecc;
		chip->ecc.hwctl		= omap_enable_hwecc;
		chip->ecc.correct	= omap_correct_data;
		mtd_set_ooblayout(mtd, &omap_ooblayout_ops);
		oobbytes_per_step	= chip->ecc.bytes;

		अगर (!(chip->options & न_अंकD_BUSWIDTH_16))
			min_oobbytes	= 1;

		अवरोध;

	हाल OMAP_ECC_BCH4_CODE_HW_DETECTION_SW:
		pr_info("nand: using OMAP_ECC_BCH4_CODE_HW_DETECTION_SW\n");
		chip->ecc.engine_type	= न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
		chip->ecc.size		= 512;
		chip->ecc.bytes		= 7;
		chip->ecc.strength	= 4;
		chip->ecc.hwctl		= omap_enable_hwecc_bch;
		chip->ecc.correct	= rawnand_sw_bch_correct;
		chip->ecc.calculate	= omap_calculate_ecc_bch_sw;
		mtd_set_ooblayout(mtd, &omap_sw_ooblayout_ops);
		/* Reserve one byte क्रम the OMAP marker */
		oobbytes_per_step	= chip->ecc.bytes + 1;
		/* Software BCH library is used क्रम locating errors */
		err = rawnand_sw_bch_init(chip);
		अगर (err) अणु
			dev_err(dev, "Unable to use BCH library\n");
			वापस err;
		पूर्ण
		अवरोध;

	हाल OMAP_ECC_BCH4_CODE_HW:
		pr_info("nand: using OMAP_ECC_BCH4_CODE_HW ECC scheme\n");
		chip->ecc.engine_type	= न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
		chip->ecc.size		= 512;
		/* 14th bit is kept reserved क्रम ROM-code compatibility */
		chip->ecc.bytes		= 7 + 1;
		chip->ecc.strength	= 4;
		chip->ecc.hwctl		= omap_enable_hwecc_bch;
		chip->ecc.correct	= omap_elm_correct_data;
		chip->ecc.पढ़ो_page	= omap_पढ़ो_page_bch;
		chip->ecc.ग_लिखो_page	= omap_ग_लिखो_page_bch;
		chip->ecc.ग_लिखो_subpage	= omap_ग_लिखो_subpage_bch;
		mtd_set_ooblayout(mtd, &omap_ooblayout_ops);
		oobbytes_per_step	= chip->ecc.bytes;

		err = elm_config(info->elm_dev, BCH4_ECC,
				 mtd->ग_लिखोsize / chip->ecc.size,
				 chip->ecc.size, chip->ecc.bytes);
		अगर (err < 0)
			वापस err;
		अवरोध;

	हाल OMAP_ECC_BCH8_CODE_HW_DETECTION_SW:
		pr_info("nand: using OMAP_ECC_BCH8_CODE_HW_DETECTION_SW\n");
		chip->ecc.engine_type	= न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
		chip->ecc.size		= 512;
		chip->ecc.bytes		= 13;
		chip->ecc.strength	= 8;
		chip->ecc.hwctl		= omap_enable_hwecc_bch;
		chip->ecc.correct	= rawnand_sw_bch_correct;
		chip->ecc.calculate	= omap_calculate_ecc_bch_sw;
		mtd_set_ooblayout(mtd, &omap_sw_ooblayout_ops);
		/* Reserve one byte क्रम the OMAP marker */
		oobbytes_per_step	= chip->ecc.bytes + 1;
		/* Software BCH library is used क्रम locating errors */
		err = rawnand_sw_bch_init(chip);
		अगर (err) अणु
			dev_err(dev, "unable to use BCH library\n");
			वापस err;
		पूर्ण
		अवरोध;

	हाल OMAP_ECC_BCH8_CODE_HW:
		pr_info("nand: using OMAP_ECC_BCH8_CODE_HW ECC scheme\n");
		chip->ecc.engine_type	= न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
		chip->ecc.size		= 512;
		/* 14th bit is kept reserved क्रम ROM-code compatibility */
		chip->ecc.bytes		= 13 + 1;
		chip->ecc.strength	= 8;
		chip->ecc.hwctl		= omap_enable_hwecc_bch;
		chip->ecc.correct	= omap_elm_correct_data;
		chip->ecc.पढ़ो_page	= omap_पढ़ो_page_bch;
		chip->ecc.ग_लिखो_page	= omap_ग_लिखो_page_bch;
		chip->ecc.ग_लिखो_subpage	= omap_ग_लिखो_subpage_bch;
		mtd_set_ooblayout(mtd, &omap_ooblayout_ops);
		oobbytes_per_step	= chip->ecc.bytes;

		err = elm_config(info->elm_dev, BCH8_ECC,
				 mtd->ग_लिखोsize / chip->ecc.size,
				 chip->ecc.size, chip->ecc.bytes);
		अगर (err < 0)
			वापस err;

		अवरोध;

	हाल OMAP_ECC_BCH16_CODE_HW:
		pr_info("Using OMAP_ECC_BCH16_CODE_HW ECC scheme\n");
		chip->ecc.engine_type	= न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
		chip->ecc.size		= 512;
		chip->ecc.bytes		= 26;
		chip->ecc.strength	= 16;
		chip->ecc.hwctl		= omap_enable_hwecc_bch;
		chip->ecc.correct	= omap_elm_correct_data;
		chip->ecc.पढ़ो_page	= omap_पढ़ो_page_bch;
		chip->ecc.ग_लिखो_page	= omap_ग_लिखो_page_bch;
		chip->ecc.ग_लिखो_subpage	= omap_ग_लिखो_subpage_bch;
		mtd_set_ooblayout(mtd, &omap_ooblayout_ops);
		oobbytes_per_step	= chip->ecc.bytes;

		err = elm_config(info->elm_dev, BCH16_ECC,
				 mtd->ग_लिखोsize / chip->ecc.size,
				 chip->ecc.size, chip->ecc.bytes);
		अगर (err < 0)
			वापस err;

		अवरोध;
	शेष:
		dev_err(dev, "Invalid or unsupported ECC scheme\n");
		वापस -EINVAL;
	पूर्ण

	/* Check अगर न_अंकD device's OOB is enough to store ECC signatures */
	min_oobbytes += (oobbytes_per_step *
			 (mtd->ग_लिखोsize / chip->ecc.size));
	अगर (mtd->oobsize < min_oobbytes) अणु
		dev_err(dev,
			"Not enough OOB bytes: required = %d, available=%d\n",
			min_oobbytes, mtd->oobsize);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops omap_nand_controller_ops = अणु
	.attach_chip = omap_nand_attach_chip,
पूर्ण;

/* Shared among all न_अंकD instances to synchronize access to the ECC Engine */
अटल काष्ठा nand_controller omap_gpmc_controller;
अटल bool omap_gpmc_controller_initialized;

अटल पूर्णांक omap_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_nand_info		*info;
	काष्ठा mtd_info			*mtd;
	काष्ठा nand_chip		*nand_chip;
	पूर्णांक				err;
	काष्ठा resource			*res;
	काष्ठा device			*dev = &pdev->dev;

	info = devm_kzalloc(&pdev->dev, माप(काष्ठा omap_nand_info),
				GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->pdev = pdev;

	err = omap_get_dt_info(dev, info);
	अगर (err)
		वापस err;

	info->ops = gpmc_omap_get_nand_ops(&info->reg, info->gpmc_cs);
	अगर (!info->ops) अणु
		dev_err(&pdev->dev, "Failed to get GPMC->NAND interface\n");
		वापस -ENODEV;
	पूर्ण

	nand_chip		= &info->nand;
	mtd			= nand_to_mtd(nand_chip);
	mtd->dev.parent		= &pdev->dev;
	nand_set_flash_node(nand_chip, dev->of_node);

	अगर (!mtd->name) अणु
		mtd->name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
					   "omap2-nand.%d", info->gpmc_cs);
		अगर (!mtd->name) अणु
			dev_err(&pdev->dev, "Failed to set MTD name\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	nand_chip->legacy.IO_ADDR_R = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(nand_chip->legacy.IO_ADDR_R))
		वापस PTR_ERR(nand_chip->legacy.IO_ADDR_R);

	info->phys_base = res->start;

	अगर (!omap_gpmc_controller_initialized) अणु
		omap_gpmc_controller.ops = &omap_nand_controller_ops;
		nand_controller_init(&omap_gpmc_controller);
		omap_gpmc_controller_initialized = true;
	पूर्ण

	nand_chip->controller = &omap_gpmc_controller;

	nand_chip->legacy.IO_ADDR_W = nand_chip->legacy.IO_ADDR_R;
	nand_chip->legacy.cmd_ctrl  = omap_hwcontrol;

	info->पढ़ोy_gpiod = devm_gpiod_get_optional(&pdev->dev, "rb",
						    GPIOD_IN);
	अगर (IS_ERR(info->पढ़ोy_gpiod)) अणु
		dev_err(dev, "failed to get ready gpio\n");
		वापस PTR_ERR(info->पढ़ोy_gpiod);
	पूर्ण

	/*
	 * If RDY/BSY line is connected to OMAP then use the omap पढ़ोy
	 * function and the generic nand_रुको function which पढ़ोs the status
	 * रेजिस्टर after monitoring the RDY/BSY line. Otherwise use a standard
	 * chip delay which is slightly more than tR (AC Timing) of the न_अंकD
	 * device and पढ़ो status रेजिस्टर until you get a failure or success
	 */
	अगर (info->पढ़ोy_gpiod) अणु
		nand_chip->legacy.dev_पढ़ोy = omap_dev_पढ़ोy;
		nand_chip->legacy.chip_delay = 0;
	पूर्ण अन्यथा अणु
		nand_chip->legacy.रुकोfunc = omap_रुको;
		nand_chip->legacy.chip_delay = 50;
	पूर्ण

	अगर (info->flash_bbt)
		nand_chip->bbt_options |= न_अंकD_BBT_USE_FLASH;

	/* scan न_अंकD device connected to chip controller */
	nand_chip->options |= info->devsize & न_अंकD_BUSWIDTH_16;

	err = nand_scan(nand_chip, 1);
	अगर (err)
		जाओ वापस_error;

	err = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (err)
		जाओ cleanup_nand;

	platक्रमm_set_drvdata(pdev, mtd);

	वापस 0;

cleanup_nand:
	nand_cleanup(nand_chip);

वापस_error:
	अगर (!IS_ERR_OR_शून्य(info->dma))
		dma_release_channel(info->dma);

	rawnand_sw_bch_cleanup(nand_chip);

	वापस err;
पूर्ण

अटल पूर्णांक omap_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtd_info *mtd = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *nand_chip = mtd_to_nand(mtd);
	काष्ठा omap_nand_info *info = mtd_to_omap(mtd);
	पूर्णांक ret;

	rawnand_sw_bch_cleanup(nand_chip);

	अगर (info->dma)
		dma_release_channel(info->dma);
	ret = mtd_device_unरेजिस्टर(mtd);
	WARN_ON(ret);
	nand_cleanup(nand_chip);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id omap_nand_ids[] = अणु
	अणु .compatible = "ti,omap2-nand", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_nand_ids);

अटल काष्ठा platक्रमm_driver omap_nand_driver = अणु
	.probe		= omap_nand_probe,
	.हटाओ		= omap_nand_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.of_match_table = of_match_ptr(omap_nand_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(omap_nand_driver);

MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Glue layer for NAND flash on TI OMAP boards");
