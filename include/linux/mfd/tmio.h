<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित MFD_TMIO_H
#घोषणा MFD_TMIO_H

#समावेश <linux/device.h>
#समावेश <linux/fb.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा पंचांगio_ioपढ़ो8(addr) पढ़ोb(addr)
#घोषणा पंचांगio_ioपढ़ो16(addr) पढ़ोw(addr)
#घोषणा पंचांगio_ioपढ़ो16_rep(r, b, l) पढ़ोsw(r, b, l)
#घोषणा पंचांगio_ioपढ़ो32(addr) \
	(((u32)पढ़ोw((addr))) | (((u32)पढ़ोw((addr) + 2)) << 16))

#घोषणा पंचांगio_ioग_लिखो8(val, addr) ग_लिखोb((val), (addr))
#घोषणा पंचांगio_ioग_लिखो16(val, addr) ग_लिखोw((val), (addr))
#घोषणा पंचांगio_ioग_लिखो16_rep(r, b, l) ग_लिखोsw(r, b, l)
#घोषणा पंचांगio_ioग_लिखो32(val, addr) \
	करो अणु \
		ग_लिखोw((val),       (addr)); \
		ग_लिखोw((val) >> 16, (addr) + 2); \
	पूर्ण जबतक (0)

#घोषणा sd_config_ग_लिखो8(base, shअगरt, reg, val) \
	पंचांगio_ioग_लिखो8((val), (base) + ((reg) << (shअगरt)))
#घोषणा sd_config_ग_लिखो16(base, shअगरt, reg, val) \
	पंचांगio_ioग_लिखो16((val), (base) + ((reg) << (shअगरt)))
#घोषणा sd_config_ग_लिखो32(base, shअगरt, reg, val) \
	करो अणु \
		पंचांगio_ioग_लिखो16((val), (base) + ((reg) << (shअगरt)));   \
		पंचांगio_ioग_लिखो16((val) >> 16, (base) + ((reg + 2) << (shअगरt))); \
	पूर्ण जबतक (0)

/* पंचांगio MMC platक्रमm flags */
/*
 * Some controllers can support a 2-byte block size when the bus width
 * is configured in 4-bit mode.
 */
#घोषणा TMIO_MMC_BLKSZ_2BYTES		BIT(1)
/*
 * Some controllers can support SDIO IRQ संकेतling.
 */
#घोषणा TMIO_MMC_SDIO_IRQ		BIT(2)

/* Some features are only available or tested on R-Car Gen2 or later */
#घोषणा TMIO_MMC_MIN_RCAR2		BIT(3)

/*
 * Some controllers require रुकोing क्रम the SD bus to become
 * idle beक्रमe writing to some रेजिस्टरs.
 */
#घोषणा TMIO_MMC_HAS_IDLE_WAIT		BIT(4)

/*
 * Use the busy समयout feature. Probably all TMIO versions support it. Yet,
 * we करोn't have करोcumentation क्रम old variants, so we enable only known good
 * variants with this flag. Can be हटाओd once all variants are known good.
 */
#घोषणा TMIO_MMC_USE_BUSY_TIMEOUT	BIT(5)

/*
 * Some controllers have CMD12 स्वतःmatically
 * issue/non-issue रेजिस्टर
 */
#घोषणा TMIO_MMC_HAVE_CMD12_CTRL	BIT(7)

/* Controller has some SDIO status bits which must be 1 */
#घोषणा TMIO_MMC_SDIO_STATUS_SETBITS	BIT(8)

/*
 * Some controllers have a 32-bit wide data port रेजिस्टर
 */
#घोषणा TMIO_MMC_32BIT_DATA_PORT	BIT(9)

/*
 * Some controllers allows to set SDx actual घड़ी
 */
#घोषणा TMIO_MMC_CLK_ACTUAL		BIT(10)

/* Some controllers have a CBSY bit */
#घोषणा TMIO_MMC_HAVE_CBSY		BIT(11)

पूर्णांक पंचांगio_core_mmc_enable(व्योम __iomem *cnf, पूर्णांक shअगरt, अचिन्हित दीर्घ base);
पूर्णांक पंचांगio_core_mmc_resume(व्योम __iomem *cnf, पूर्णांक shअगरt, अचिन्हित दीर्घ base);
व्योम पंचांगio_core_mmc_pwr(व्योम __iomem *cnf, पूर्णांक shअगरt, पूर्णांक state);
व्योम पंचांगio_core_mmc_clk_भाग(व्योम __iomem *cnf, पूर्णांक shअगरt, पूर्णांक state);

काष्ठा dma_chan;

/*
 * data क्रम the MMC controller
 */
काष्ठा पंचांगio_mmc_data अणु
	व्योम				*chan_priv_tx;
	व्योम				*chan_priv_rx;
	अचिन्हित पूर्णांक			hclk;
	अचिन्हित दीर्घ			capabilities;
	अचिन्हित दीर्घ			capabilities2;
	अचिन्हित दीर्घ			flags;
	u32				ocr_mask;	/* available voltages */
	पूर्णांक				alignment_shअगरt;
	dma_addr_t			dma_rx_offset;
	अचिन्हित पूर्णांक			max_blk_count;
	अचिन्हित लघु			max_segs;
	व्योम (*set_pwr)(काष्ठा platक्रमm_device *host, पूर्णांक state);
	व्योम (*set_clk_भाग)(काष्ठा platक्रमm_device *host, पूर्णांक state);
पूर्ण;

/*
 * data क्रम the न_अंकD controller
 */
काष्ठा पंचांगio_nand_data अणु
	काष्ठा nand_bbt_descr	*badblock_pattern;
	काष्ठा mtd_partition	*partition;
	अचिन्हित पूर्णांक		num_partitions;
	स्थिर अक्षर *स्थिर	*part_parsers;
पूर्ण;

#घोषणा FBIO_TMIO_ACC_WRITE	0x7C639300
#घोषणा FBIO_TMIO_ACC_SYNC	0x7C639301

काष्ठा पंचांगio_fb_data अणु
	पूर्णांक			(*lcd_set_घातer)(काष्ठा platक्रमm_device *fb_dev,
						 bool on);
	पूर्णांक			(*lcd_mode)(काष्ठा platक्रमm_device *fb_dev,
					    स्थिर काष्ठा fb_videomode *mode);
	पूर्णांक			num_modes;
	काष्ठा fb_videomode	*modes;

	/* in mm: size of screen */
	पूर्णांक			height;
	पूर्णांक			width;
पूर्ण;

#पूर्ण_अगर
