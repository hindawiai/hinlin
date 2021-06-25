<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2018
 * Author: Christophe Kerello <christophe.kerello@st.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

/* Bad block marker length */
#घोषणा FMC2_BBM_LEN			2

/* ECC step size */
#घोषणा FMC2_ECC_STEP_SIZE		512

/* BCHDSRx रेजिस्टरs length */
#घोषणा FMC2_BCHDSRS_LEN		20

/* HECCR length */
#घोषणा FMC2_HECCR_LEN			4

/* Max requests करोne क्रम a 8k nand page size */
#घोषणा FMC2_MAX_SG			16

/* Max chip enable */
#घोषणा FMC2_MAX_CE			2

/* Max ECC buffer length */
#घोषणा FMC2_MAX_ECC_BUF_LEN		(FMC2_BCHDSRS_LEN * FMC2_MAX_SG)

#घोषणा FMC2_TIMEOUT_MS			5000

/* Timings */
#घोषणा FMC2_THIZ			1
#घोषणा FMC2_TIO			8000
#घोषणा FMC2_TSYNC			3000
#घोषणा FMC2_PCR_TIMING_MASK		0xf
#घोषणा FMC2_PMEM_PATT_TIMING_MASK	0xff

/* FMC2 Controller Registers */
#घोषणा FMC2_BCR1			0x0
#घोषणा FMC2_PCR			0x80
#घोषणा FMC2_SR				0x84
#घोषणा FMC2_PMEM			0x88
#घोषणा FMC2_PATT			0x8c
#घोषणा FMC2_HECCR			0x94
#घोषणा FMC2_ISR			0x184
#घोषणा FMC2_ICR			0x188
#घोषणा FMC2_CSQCR			0x200
#घोषणा FMC2_CSQCFGR1			0x204
#घोषणा FMC2_CSQCFGR2			0x208
#घोषणा FMC2_CSQCFGR3			0x20c
#घोषणा FMC2_CSQAR1			0x210
#घोषणा FMC2_CSQAR2			0x214
#घोषणा FMC2_CSQIER			0x220
#घोषणा FMC2_CSQISR			0x224
#घोषणा FMC2_CSQICR			0x228
#घोषणा FMC2_CSQEMSR			0x230
#घोषणा FMC2_BCHIER			0x250
#घोषणा FMC2_BCHISR			0x254
#घोषणा FMC2_BCHICR			0x258
#घोषणा FMC2_BCHPBR1			0x260
#घोषणा FMC2_BCHPBR2			0x264
#घोषणा FMC2_BCHPBR3			0x268
#घोषणा FMC2_BCHPBR4			0x26c
#घोषणा FMC2_BCHDSR0			0x27c
#घोषणा FMC2_BCHDSR1			0x280
#घोषणा FMC2_BCHDSR2			0x284
#घोषणा FMC2_BCHDSR3			0x288
#घोषणा FMC2_BCHDSR4			0x28c

/* Register: FMC2_BCR1 */
#घोषणा FMC2_BCR1_FMC2EN		BIT(31)

/* Register: FMC2_PCR */
#घोषणा FMC2_PCR_PWAITEN		BIT(1)
#घोषणा FMC2_PCR_PBKEN			BIT(2)
#घोषणा FMC2_PCR_PWID			GENMASK(5, 4)
#घोषणा FMC2_PCR_PWID_BUSWIDTH_8	0
#घोषणा FMC2_PCR_PWID_BUSWIDTH_16	1
#घोषणा FMC2_PCR_ECCEN			BIT(6)
#घोषणा FMC2_PCR_ECCALG			BIT(8)
#घोषणा FMC2_PCR_TCLR			GENMASK(12, 9)
#घोषणा FMC2_PCR_TCLR_DEFAULT		0xf
#घोषणा FMC2_PCR_TAR			GENMASK(16, 13)
#घोषणा FMC2_PCR_TAR_DEFAULT		0xf
#घोषणा FMC2_PCR_ECCSS			GENMASK(19, 17)
#घोषणा FMC2_PCR_ECCSS_512		1
#घोषणा FMC2_PCR_ECCSS_2048		3
#घोषणा FMC2_PCR_BCHECC			BIT(24)
#घोषणा FMC2_PCR_WEN			BIT(25)

/* Register: FMC2_SR */
#घोषणा FMC2_SR_NWRF			BIT(6)

/* Register: FMC2_PMEM */
#घोषणा FMC2_PMEM_MEMSET		GENMASK(7, 0)
#घोषणा FMC2_PMEM_MEMWAIT		GENMASK(15, 8)
#घोषणा FMC2_PMEM_MEMHOLD		GENMASK(23, 16)
#घोषणा FMC2_PMEM_MEMHIZ		GENMASK(31, 24)
#घोषणा FMC2_PMEM_DEFAULT		0x0a0a0a0a

/* Register: FMC2_PATT */
#घोषणा FMC2_PATT_ATTSET		GENMASK(7, 0)
#घोषणा FMC2_PATT_ATTWAIT		GENMASK(15, 8)
#घोषणा FMC2_PATT_ATTHOLD		GENMASK(23, 16)
#घोषणा FMC2_PATT_ATTHIZ		GENMASK(31, 24)
#घोषणा FMC2_PATT_DEFAULT		0x0a0a0a0a

/* Register: FMC2_ISR */
#घोषणा FMC2_ISR_IHLF			BIT(1)

/* Register: FMC2_ICR */
#घोषणा FMC2_ICR_CIHLF			BIT(1)

/* Register: FMC2_CSQCR */
#घोषणा FMC2_CSQCR_CSQSTART		BIT(0)

/* Register: FMC2_CSQCFGR1 */
#घोषणा FMC2_CSQCFGR1_CMD2EN		BIT(1)
#घोषणा FMC2_CSQCFGR1_DMADEN		BIT(2)
#घोषणा FMC2_CSQCFGR1_ACYNBR		GENMASK(6, 4)
#घोषणा FMC2_CSQCFGR1_CMD1		GENMASK(15, 8)
#घोषणा FMC2_CSQCFGR1_CMD2		GENMASK(23, 16)
#घोषणा FMC2_CSQCFGR1_CMD1T		BIT(24)
#घोषणा FMC2_CSQCFGR1_CMD2T		BIT(25)

/* Register: FMC2_CSQCFGR2 */
#घोषणा FMC2_CSQCFGR2_SQSDTEN		BIT(0)
#घोषणा FMC2_CSQCFGR2_RCMD2EN		BIT(1)
#घोषणा FMC2_CSQCFGR2_DMASEN		BIT(2)
#घोषणा FMC2_CSQCFGR2_RCMD1		GENMASK(15, 8)
#घोषणा FMC2_CSQCFGR2_RCMD2		GENMASK(23, 16)
#घोषणा FMC2_CSQCFGR2_RCMD1T		BIT(24)
#घोषणा FMC2_CSQCFGR2_RCMD2T		BIT(25)

/* Register: FMC2_CSQCFGR3 */
#घोषणा FMC2_CSQCFGR3_SNBR		GENMASK(13, 8)
#घोषणा FMC2_CSQCFGR3_AC1T		BIT(16)
#घोषणा FMC2_CSQCFGR3_AC2T		BIT(17)
#घोषणा FMC2_CSQCFGR3_AC3T		BIT(18)
#घोषणा FMC2_CSQCFGR3_AC4T		BIT(19)
#घोषणा FMC2_CSQCFGR3_AC5T		BIT(20)
#घोषणा FMC2_CSQCFGR3_SDT		BIT(21)
#घोषणा FMC2_CSQCFGR3_RAC1T		BIT(22)
#घोषणा FMC2_CSQCFGR3_RAC2T		BIT(23)

/* Register: FMC2_CSQCAR1 */
#घोषणा FMC2_CSQCAR1_ADDC1		GENMASK(7, 0)
#घोषणा FMC2_CSQCAR1_ADDC2		GENMASK(15, 8)
#घोषणा FMC2_CSQCAR1_ADDC3		GENMASK(23, 16)
#घोषणा FMC2_CSQCAR1_ADDC4		GENMASK(31, 24)

/* Register: FMC2_CSQCAR2 */
#घोषणा FMC2_CSQCAR2_ADDC5		GENMASK(7, 0)
#घोषणा FMC2_CSQCAR2_न_अंकDCEN		GENMASK(11, 10)
#घोषणा FMC2_CSQCAR2_SAO		GENMASK(31, 16)

/* Register: FMC2_CSQIER */
#घोषणा FMC2_CSQIER_TCIE		BIT(0)

/* Register: FMC2_CSQICR */
#घोषणा FMC2_CSQICR_CLEAR_IRQ		GENMASK(4, 0)

/* Register: FMC2_CSQEMSR */
#घोषणा FMC2_CSQEMSR_SEM		GENMASK(15, 0)

/* Register: FMC2_BCHIER */
#घोषणा FMC2_BCHIER_DERIE		BIT(1)
#घोषणा FMC2_BCHIER_EPBRIE		BIT(4)

/* Register: FMC2_BCHICR */
#घोषणा FMC2_BCHICR_CLEAR_IRQ		GENMASK(4, 0)

/* Register: FMC2_BCHDSR0 */
#घोषणा FMC2_BCHDSR0_DUE		BIT(0)
#घोषणा FMC2_BCHDSR0_DEF		BIT(1)
#घोषणा FMC2_BCHDSR0_DEN		GENMASK(7, 4)

/* Register: FMC2_BCHDSR1 */
#घोषणा FMC2_BCHDSR1_EBP1		GENMASK(12, 0)
#घोषणा FMC2_BCHDSR1_EBP2		GENMASK(28, 16)

/* Register: FMC2_BCHDSR2 */
#घोषणा FMC2_BCHDSR2_EBP3		GENMASK(12, 0)
#घोषणा FMC2_BCHDSR2_EBP4		GENMASK(28, 16)

/* Register: FMC2_BCHDSR3 */
#घोषणा FMC2_BCHDSR3_EBP5		GENMASK(12, 0)
#घोषणा FMC2_BCHDSR3_EBP6		GENMASK(28, 16)

/* Register: FMC2_BCHDSR4 */
#घोषणा FMC2_BCHDSR4_EBP7		GENMASK(12, 0)
#घोषणा FMC2_BCHDSR4_EBP8		GENMASK(28, 16)

क्रमागत sपंचांग32_fmc2_ecc अणु
	FMC2_ECC_HAM = 1,
	FMC2_ECC_BCH4 = 4,
	FMC2_ECC_BCH8 = 8
पूर्ण;

क्रमागत sपंचांग32_fmc2_irq_state अणु
	FMC2_IRQ_UNKNOWN = 0,
	FMC2_IRQ_BCH,
	FMC2_IRQ_SEQ
पूर्ण;

काष्ठा sपंचांग32_fmc2_timings अणु
	u8 tclr;
	u8 tar;
	u8 thiz;
	u8 tरुको;
	u8 thold_mem;
	u8 tset_mem;
	u8 thold_att;
	u8 tset_att;
पूर्ण;

काष्ठा sपंचांग32_fmc2_nand अणु
	काष्ठा nand_chip chip;
	काष्ठा sपंचांग32_fmc2_timings timings;
	पूर्णांक ncs;
	पूर्णांक cs_used[FMC2_MAX_CE];
पूर्ण;

अटल अंतरभूत काष्ठा sपंचांग32_fmc2_nand *to_fmc2_nand(काष्ठा nand_chip *chip)
अणु
	वापस container_of(chip, काष्ठा sपंचांग32_fmc2_nand, chip);
पूर्ण

काष्ठा sपंचांग32_fmc2_nfc अणु
	काष्ठा nand_controller base;
	काष्ठा sपंचांग32_fmc2_nand nand;
	काष्ठा device *dev;
	काष्ठा device *cdev;
	काष्ठा regmap *regmap;
	व्योम __iomem *data_base[FMC2_MAX_CE];
	व्योम __iomem *cmd_base[FMC2_MAX_CE];
	व्योम __iomem *addr_base[FMC2_MAX_CE];
	phys_addr_t io_phys_addr;
	phys_addr_t data_phys_addr[FMC2_MAX_CE];
	काष्ठा clk *clk;
	u8 irq_state;

	काष्ठा dma_chan *dma_tx_ch;
	काष्ठा dma_chan *dma_rx_ch;
	काष्ठा dma_chan *dma_ecc_ch;
	काष्ठा sg_table dma_data_sg;
	काष्ठा sg_table dma_ecc_sg;
	u8 *ecc_buf;
	पूर्णांक dma_ecc_len;

	काष्ठा completion complete;
	काष्ठा completion dma_data_complete;
	काष्ठा completion dma_ecc_complete;

	u8 cs_asचिन्हित;
	पूर्णांक cs_sel;
पूर्ण;

अटल अंतरभूत काष्ठा sपंचांग32_fmc2_nfc *to_sपंचांग32_nfc(काष्ठा nand_controller *base)
अणु
	वापस container_of(base, काष्ठा sपंचांग32_fmc2_nfc, base);
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_timings_init(काष्ठा nand_chip *chip)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	काष्ठा sपंचांग32_fmc2_nand *nand = to_fmc2_nand(chip);
	काष्ठा sपंचांग32_fmc2_timings *timings = &nand->timings;
	u32 pmem, patt;

	/* Set tclr/tar timings */
	regmap_update_bits(nfc->regmap, FMC2_PCR,
			   FMC2_PCR_TCLR | FMC2_PCR_TAR,
			   FIELD_PREP(FMC2_PCR_TCLR, timings->tclr) |
			   FIELD_PREP(FMC2_PCR_TAR, timings->tar));

	/* Set tset/tरुको/thold/thiz timings in common bank */
	pmem = FIELD_PREP(FMC2_PMEM_MEMSET, timings->tset_mem);
	pmem |= FIELD_PREP(FMC2_PMEM_MEMWAIT, timings->tरुको);
	pmem |= FIELD_PREP(FMC2_PMEM_MEMHOLD, timings->thold_mem);
	pmem |= FIELD_PREP(FMC2_PMEM_MEMHIZ, timings->thiz);
	regmap_ग_लिखो(nfc->regmap, FMC2_PMEM, pmem);

	/* Set tset/tरुको/thold/thiz timings in attribut bank */
	patt = FIELD_PREP(FMC2_PATT_ATTSET, timings->tset_att);
	patt |= FIELD_PREP(FMC2_PATT_ATTWAIT, timings->tरुको);
	patt |= FIELD_PREP(FMC2_PATT_ATTHOLD, timings->thold_att);
	patt |= FIELD_PREP(FMC2_PATT_ATTHIZ, timings->thiz);
	regmap_ग_लिखो(nfc->regmap, FMC2_PATT, patt);
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_setup(काष्ठा nand_chip *chip)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	u32 pcr = 0, pcr_mask;

	/* Configure ECC algorithm (शेष configuration is Hamming) */
	pcr_mask = FMC2_PCR_ECCALG;
	pcr_mask |= FMC2_PCR_BCHECC;
	अगर (chip->ecc.strength == FMC2_ECC_BCH8) अणु
		pcr |= FMC2_PCR_ECCALG;
		pcr |= FMC2_PCR_BCHECC;
	पूर्ण अन्यथा अगर (chip->ecc.strength == FMC2_ECC_BCH4) अणु
		pcr |= FMC2_PCR_ECCALG;
	पूर्ण

	/* Set buswidth */
	pcr_mask |= FMC2_PCR_PWID;
	अगर (chip->options & न_अंकD_BUSWIDTH_16)
		pcr |= FIELD_PREP(FMC2_PCR_PWID, FMC2_PCR_PWID_BUSWIDTH_16);

	/* Set ECC sector size */
	pcr_mask |= FMC2_PCR_ECCSS;
	pcr |= FIELD_PREP(FMC2_PCR_ECCSS, FMC2_PCR_ECCSS_512);

	regmap_update_bits(nfc->regmap, FMC2_PCR, pcr_mask, pcr);
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_select_chip(काष्ठा nand_chip *chip, पूर्णांक chipnr)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	काष्ठा sपंचांग32_fmc2_nand *nand = to_fmc2_nand(chip);
	काष्ठा dma_slave_config dma_cfg;
	पूर्णांक ret;

	अगर (nand->cs_used[chipnr] == nfc->cs_sel)
		वापस 0;

	nfc->cs_sel = nand->cs_used[chipnr];
	sपंचांग32_fmc2_nfc_setup(chip);
	sपंचांग32_fmc2_nfc_timings_init(chip);

	अगर (nfc->dma_tx_ch && nfc->dma_rx_ch) अणु
		स_रखो(&dma_cfg, 0, माप(dma_cfg));
		dma_cfg.src_addr = nfc->data_phys_addr[nfc->cs_sel];
		dma_cfg.dst_addr = nfc->data_phys_addr[nfc->cs_sel];
		dma_cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		dma_cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		dma_cfg.src_maxburst = 32;
		dma_cfg.dst_maxburst = 32;

		ret = dmaengine_slave_config(nfc->dma_tx_ch, &dma_cfg);
		अगर (ret) अणु
			dev_err(nfc->dev, "tx DMA engine slave config failed\n");
			वापस ret;
		पूर्ण

		ret = dmaengine_slave_config(nfc->dma_rx_ch, &dma_cfg);
		अगर (ret) अणु
			dev_err(nfc->dev, "rx DMA engine slave config failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (nfc->dma_ecc_ch) अणु
		/*
		 * Hamming: we पढ़ो HECCR रेजिस्टर
		 * BCH4/BCH8: we पढ़ो BCHDSRSx रेजिस्टरs
		 */
		स_रखो(&dma_cfg, 0, माप(dma_cfg));
		dma_cfg.src_addr = nfc->io_phys_addr;
		dma_cfg.src_addr += chip->ecc.strength == FMC2_ECC_HAM ?
				    FMC2_HECCR : FMC2_BCHDSR0;
		dma_cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

		ret = dmaengine_slave_config(nfc->dma_ecc_ch, &dma_cfg);
		अगर (ret) अणु
			dev_err(nfc->dev, "ECC DMA engine slave config failed\n");
			वापस ret;
		पूर्ण

		/* Calculate ECC length needed क्रम one sector */
		nfc->dma_ecc_len = chip->ecc.strength == FMC2_ECC_HAM ?
				   FMC2_HECCR_LEN : FMC2_BCHDSRS_LEN;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_set_buswidth_16(काष्ठा sपंचांग32_fmc2_nfc *nfc, bool set)
अणु
	u32 pcr;

	pcr = set ? FIELD_PREP(FMC2_PCR_PWID, FMC2_PCR_PWID_BUSWIDTH_16) :
		    FIELD_PREP(FMC2_PCR_PWID, FMC2_PCR_PWID_BUSWIDTH_8);

	regmap_update_bits(nfc->regmap, FMC2_PCR, FMC2_PCR_PWID, pcr);
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_set_ecc(काष्ठा sपंचांग32_fmc2_nfc *nfc, bool enable)
अणु
	regmap_update_bits(nfc->regmap, FMC2_PCR, FMC2_PCR_ECCEN,
			   enable ? FMC2_PCR_ECCEN : 0);
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_enable_seq_irq(काष्ठा sपंचांग32_fmc2_nfc *nfc)
अणु
	nfc->irq_state = FMC2_IRQ_SEQ;

	regmap_update_bits(nfc->regmap, FMC2_CSQIER,
			   FMC2_CSQIER_TCIE, FMC2_CSQIER_TCIE);
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_disable_seq_irq(काष्ठा sपंचांग32_fmc2_nfc *nfc)
अणु
	regmap_update_bits(nfc->regmap, FMC2_CSQIER, FMC2_CSQIER_TCIE, 0);

	nfc->irq_state = FMC2_IRQ_UNKNOWN;
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_clear_seq_irq(काष्ठा sपंचांग32_fmc2_nfc *nfc)
अणु
	regmap_ग_लिखो(nfc->regmap, FMC2_CSQICR, FMC2_CSQICR_CLEAR_IRQ);
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_enable_bch_irq(काष्ठा sपंचांग32_fmc2_nfc *nfc, पूर्णांक mode)
अणु
	nfc->irq_state = FMC2_IRQ_BCH;

	अगर (mode == न_अंकD_ECC_WRITE)
		regmap_update_bits(nfc->regmap, FMC2_BCHIER,
				   FMC2_BCHIER_EPBRIE, FMC2_BCHIER_EPBRIE);
	अन्यथा
		regmap_update_bits(nfc->regmap, FMC2_BCHIER,
				   FMC2_BCHIER_DERIE, FMC2_BCHIER_DERIE);
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_disable_bch_irq(काष्ठा sपंचांग32_fmc2_nfc *nfc)
अणु
	regmap_update_bits(nfc->regmap, FMC2_BCHIER,
			   FMC2_BCHIER_DERIE | FMC2_BCHIER_EPBRIE, 0);

	nfc->irq_state = FMC2_IRQ_UNKNOWN;
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_clear_bch_irq(काष्ठा sपंचांग32_fmc2_nfc *nfc)
अणु
	regmap_ग_लिखो(nfc->regmap, FMC2_BCHICR, FMC2_BCHICR_CLEAR_IRQ);
पूर्ण

/*
 * Enable ECC logic and reset syndrome/parity bits previously calculated
 * Syndrome/parity bits is cleared by setting the ECCEN bit to 0
 */
अटल व्योम sपंचांग32_fmc2_nfc_hwctl(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);

	sपंचांग32_fmc2_nfc_set_ecc(nfc, false);

	अगर (chip->ecc.strength != FMC2_ECC_HAM) अणु
		regmap_update_bits(nfc->regmap, FMC2_PCR, FMC2_PCR_WEN,
				   mode == न_अंकD_ECC_WRITE ? FMC2_PCR_WEN : 0);

		reinit_completion(&nfc->complete);
		sपंचांग32_fmc2_nfc_clear_bch_irq(nfc);
		sपंचांग32_fmc2_nfc_enable_bch_irq(nfc, mode);
	पूर्ण

	sपंचांग32_fmc2_nfc_set_ecc(nfc, true);
पूर्ण

/*
 * ECC Hamming calculation
 * ECC is 3 bytes क्रम 512 bytes of data (supports error correction up to
 * max of 1-bit)
 */
अटल व्योम sपंचांग32_fmc2_nfc_ham_set_ecc(स्थिर u32 ecc_sta, u8 *ecc)
अणु
	ecc[0] = ecc_sta;
	ecc[1] = ecc_sta >> 8;
	ecc[2] = ecc_sta >> 16;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_ham_calculate(काष्ठा nand_chip *chip, स्थिर u8 *data,
					u8 *ecc)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	u32 sr, heccr;
	पूर्णांक ret;

	ret = regmap_पढ़ो_poll_समयout(nfc->regmap, FMC2_SR, sr,
				       sr & FMC2_SR_NWRF, 1,
				       1000 * FMC2_TIMEOUT_MS);
	अगर (ret) अणु
		dev_err(nfc->dev, "ham timeout\n");
		वापस ret;
	पूर्ण

	regmap_पढ़ो(nfc->regmap, FMC2_HECCR, &heccr);
	sपंचांग32_fmc2_nfc_ham_set_ecc(heccr, ecc);
	sपंचांग32_fmc2_nfc_set_ecc(nfc, false);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_ham_correct(काष्ठा nand_chip *chip, u8 *dat,
				      u8 *पढ़ो_ecc, u8 *calc_ecc)
अणु
	u8 bit_position = 0, b0, b1, b2;
	u32 byte_addr = 0, b;
	u32 i, shअगरting = 1;

	/* Indicate which bit and byte is faulty (अगर any) */
	b0 = पढ़ो_ecc[0] ^ calc_ecc[0];
	b1 = पढ़ो_ecc[1] ^ calc_ecc[1];
	b2 = पढ़ो_ecc[2] ^ calc_ecc[2];
	b = b0 | (b1 << 8) | (b2 << 16);

	/* No errors */
	अगर (likely(!b))
		वापस 0;

	/* Calculate bit position */
	क्रम (i = 0; i < 3; i++) अणु
		चयन (b % 4) अणु
		हाल 2:
			bit_position += shअगरting;
			अवरोध;
		हाल 1:
			अवरोध;
		शेष:
			वापस -EBADMSG;
		पूर्ण
		shअगरting <<= 1;
		b >>= 2;
	पूर्ण

	/* Calculate byte position */
	shअगरting = 1;
	क्रम (i = 0; i < 9; i++) अणु
		चयन (b % 4) अणु
		हाल 2:
			byte_addr += shअगरting;
			अवरोध;
		हाल 1:
			अवरोध;
		शेष:
			वापस -EBADMSG;
		पूर्ण
		shअगरting <<= 1;
		b >>= 2;
	पूर्ण

	/* Flip the bit */
	dat[byte_addr] ^= (1 << bit_position);

	वापस 1;
पूर्ण

/*
 * ECC BCH calculation and correction
 * ECC is 7/13 bytes क्रम 512 bytes of data (supports error correction up to
 * max of 4-bit/8-bit)
 */
अटल पूर्णांक sपंचांग32_fmc2_nfc_bch_calculate(काष्ठा nand_chip *chip, स्थिर u8 *data,
					u8 *ecc)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	u32 bchpbr;

	/* Wait until the BCH code is पढ़ोy */
	अगर (!रुको_क्रम_completion_समयout(&nfc->complete,
					 msecs_to_jअगरfies(FMC2_TIMEOUT_MS))) अणु
		dev_err(nfc->dev, "bch timeout\n");
		sपंचांग32_fmc2_nfc_disable_bch_irq(nfc);
		वापस -ETIMEDOUT;
	पूर्ण

	/* Read parity bits */
	regmap_पढ़ो(nfc->regmap, FMC2_BCHPBR1, &bchpbr);
	ecc[0] = bchpbr;
	ecc[1] = bchpbr >> 8;
	ecc[2] = bchpbr >> 16;
	ecc[3] = bchpbr >> 24;

	regmap_पढ़ो(nfc->regmap, FMC2_BCHPBR2, &bchpbr);
	ecc[4] = bchpbr;
	ecc[5] = bchpbr >> 8;
	ecc[6] = bchpbr >> 16;

	अगर (chip->ecc.strength == FMC2_ECC_BCH8) अणु
		ecc[7] = bchpbr >> 24;

		regmap_पढ़ो(nfc->regmap, FMC2_BCHPBR3, &bchpbr);
		ecc[8] = bchpbr;
		ecc[9] = bchpbr >> 8;
		ecc[10] = bchpbr >> 16;
		ecc[11] = bchpbr >> 24;

		regmap_पढ़ो(nfc->regmap, FMC2_BCHPBR4, &bchpbr);
		ecc[12] = bchpbr;
	पूर्ण

	sपंचांग32_fmc2_nfc_set_ecc(nfc, false);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_bch_decode(पूर्णांक eccsize, u8 *dat, u32 *ecc_sta)
अणु
	u32 bchdsr0 = ecc_sta[0];
	u32 bchdsr1 = ecc_sta[1];
	u32 bchdsr2 = ecc_sta[2];
	u32 bchdsr3 = ecc_sta[3];
	u32 bchdsr4 = ecc_sta[4];
	u16 pos[8];
	पूर्णांक i, den;
	अचिन्हित पूर्णांक nb_errs = 0;

	/* No errors found */
	अगर (likely(!(bchdsr0 & FMC2_BCHDSR0_DEF)))
		वापस 0;

	/* Too many errors detected */
	अगर (unlikely(bchdsr0 & FMC2_BCHDSR0_DUE))
		वापस -EBADMSG;

	pos[0] = FIELD_GET(FMC2_BCHDSR1_EBP1, bchdsr1);
	pos[1] = FIELD_GET(FMC2_BCHDSR1_EBP2, bchdsr1);
	pos[2] = FIELD_GET(FMC2_BCHDSR2_EBP3, bchdsr2);
	pos[3] = FIELD_GET(FMC2_BCHDSR2_EBP4, bchdsr2);
	pos[4] = FIELD_GET(FMC2_BCHDSR3_EBP5, bchdsr3);
	pos[5] = FIELD_GET(FMC2_BCHDSR3_EBP6, bchdsr3);
	pos[6] = FIELD_GET(FMC2_BCHDSR4_EBP7, bchdsr4);
	pos[7] = FIELD_GET(FMC2_BCHDSR4_EBP8, bchdsr4);

	den = FIELD_GET(FMC2_BCHDSR0_DEN, bchdsr0);
	क्रम (i = 0; i < den; i++) अणु
		अगर (pos[i] < eccsize * 8) अणु
			change_bit(pos[i], (अचिन्हित दीर्घ *)dat);
			nb_errs++;
		पूर्ण
	पूर्ण

	वापस nb_errs;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_bch_correct(काष्ठा nand_chip *chip, u8 *dat,
				      u8 *पढ़ो_ecc, u8 *calc_ecc)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	u32 ecc_sta[5];

	/* Wait until the decoding error is पढ़ोy */
	अगर (!रुको_क्रम_completion_समयout(&nfc->complete,
					 msecs_to_jअगरfies(FMC2_TIMEOUT_MS))) अणु
		dev_err(nfc->dev, "bch timeout\n");
		sपंचांग32_fmc2_nfc_disable_bch_irq(nfc);
		वापस -ETIMEDOUT;
	पूर्ण

	regmap_bulk_पढ़ो(nfc->regmap, FMC2_BCHDSR0, ecc_sta, 5);

	sपंचांग32_fmc2_nfc_set_ecc(nfc, false);

	वापस sपंचांग32_fmc2_nfc_bch_decode(chip->ecc.size, dat, ecc_sta);
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_पढ़ो_page(काष्ठा nand_chip *chip, u8 *buf,
				    पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret, i, s, stat, eccsize = chip->ecc.size;
	पूर्णांक eccbytes = chip->ecc.bytes;
	पूर्णांक eccsteps = chip->ecc.steps;
	पूर्णांक eccstrength = chip->ecc.strength;
	u8 *p = buf;
	u8 *ecc_calc = chip->ecc.calc_buf;
	u8 *ecc_code = chip->ecc.code_buf;
	अचिन्हित पूर्णांक max_bitflips = 0;

	ret = nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);
	अगर (ret)
		वापस ret;

	क्रम (i = mtd->ग_लिखोsize + FMC2_BBM_LEN, s = 0; s < eccsteps;
	     s++, i += eccbytes, p += eccsize) अणु
		chip->ecc.hwctl(chip, न_अंकD_ECC_READ);

		/* Read the nand page sector (512 bytes) */
		ret = nand_change_पढ़ो_column_op(chip, s * eccsize, p,
						 eccsize, false);
		अगर (ret)
			वापस ret;

		/* Read the corresponding ECC bytes */
		ret = nand_change_पढ़ो_column_op(chip, i, ecc_code,
						 eccbytes, false);
		अगर (ret)
			वापस ret;

		/* Correct the data */
		stat = chip->ecc.correct(chip, p, ecc_code, ecc_calc);
		अगर (stat == -EBADMSG)
			/* Check क्रम empty pages with bitflips */
			stat = nand_check_erased_ecc_chunk(p, eccsize,
							   ecc_code, eccbytes,
							   शून्य, 0,
							   eccstrength);

		अगर (stat < 0) अणु
			mtd->ecc_stats.failed++;
		पूर्ण अन्यथा अणु
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, stat);
		पूर्ण
	पूर्ण

	/* Read oob */
	अगर (oob_required) अणु
		ret = nand_change_पढ़ो_column_op(chip, mtd->ग_लिखोsize,
						 chip->oob_poi, mtd->oobsize,
						 false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस max_bitflips;
पूर्ण

/* Sequencer पढ़ो/ग_लिखो configuration */
अटल व्योम sपंचांग32_fmc2_nfc_rw_page_init(काष्ठा nand_chip *chip, पूर्णांक page,
					पूर्णांक raw, bool ग_लिखो_data)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	u32 ecc_offset = mtd->ग_लिखोsize + FMC2_BBM_LEN;
	/*
	 * cfg[0] => csqcfgr1, cfg[1] => csqcfgr2, cfg[2] => csqcfgr3
	 * cfg[3] => csqar1, cfg[4] => csqar2
	 */
	u32 cfg[5];

	regmap_update_bits(nfc->regmap, FMC2_PCR, FMC2_PCR_WEN,
			   ग_लिखो_data ? FMC2_PCR_WEN : 0);

	/*
	 * - Set Program Page/Page Read command
	 * - Enable DMA request data
	 * - Set timings
	 */
	cfg[0] = FMC2_CSQCFGR1_DMADEN | FMC2_CSQCFGR1_CMD1T;
	अगर (ग_लिखो_data)
		cfg[0] |= FIELD_PREP(FMC2_CSQCFGR1_CMD1, न_अंकD_CMD_SEQIN);
	अन्यथा
		cfg[0] |= FIELD_PREP(FMC2_CSQCFGR1_CMD1, न_अंकD_CMD_READ0) |
			  FMC2_CSQCFGR1_CMD2EN |
			  FIELD_PREP(FMC2_CSQCFGR1_CMD2, न_अंकD_CMD_READSTART) |
			  FMC2_CSQCFGR1_CMD2T;

	/*
	 * - Set Ranकरोm Data Input/Ranकरोm Data Read command
	 * - Enable the sequencer to access the Spare data area
	 * - Enable  DMA request status decoding क्रम पढ़ो
	 * - Set timings
	 */
	अगर (ग_लिखो_data)
		cfg[1] = FIELD_PREP(FMC2_CSQCFGR2_RCMD1, न_अंकD_CMD_RNDIN);
	अन्यथा
		cfg[1] = FIELD_PREP(FMC2_CSQCFGR2_RCMD1, न_अंकD_CMD_RNDOUT) |
			 FMC2_CSQCFGR2_RCMD2EN |
			 FIELD_PREP(FMC2_CSQCFGR2_RCMD2, न_अंकD_CMD_RNDOUTSTART) |
			 FMC2_CSQCFGR2_RCMD1T |
			 FMC2_CSQCFGR2_RCMD2T;
	अगर (!raw) अणु
		cfg[1] |= ग_लिखो_data ? 0 : FMC2_CSQCFGR2_DMASEN;
		cfg[1] |= FMC2_CSQCFGR2_SQSDTEN;
	पूर्ण

	/*
	 * - Set the number of sectors to be written
	 * - Set timings
	 */
	cfg[2] = FIELD_PREP(FMC2_CSQCFGR3_SNBR, chip->ecc.steps - 1);
	अगर (ग_लिखो_data) अणु
		cfg[2] |= FMC2_CSQCFGR3_RAC2T;
		अगर (chip->options & न_अंकD_ROW_ADDR_3)
			cfg[2] |= FMC2_CSQCFGR3_AC5T;
		अन्यथा
			cfg[2] |= FMC2_CSQCFGR3_AC4T;
	पूर्ण

	/*
	 * Set the fourth first address cycles
	 * Byte 1 and byte 2 => column, we start at 0x0
	 * Byte 3 and byte 4 => page
	 */
	cfg[3] = FIELD_PREP(FMC2_CSQCAR1_ADDC3, page);
	cfg[3] |= FIELD_PREP(FMC2_CSQCAR1_ADDC4, page >> 8);

	/*
	 * - Set chip enable number
	 * - Set ECC byte offset in the spare area
	 * - Calculate the number of address cycles to be issued
	 * - Set byte 5 of address cycle अगर needed
	 */
	cfg[4] = FIELD_PREP(FMC2_CSQCAR2_न_अंकDCEN, nfc->cs_sel);
	अगर (chip->options & न_अंकD_BUSWIDTH_16)
		cfg[4] |= FIELD_PREP(FMC2_CSQCAR2_SAO, ecc_offset >> 1);
	अन्यथा
		cfg[4] |= FIELD_PREP(FMC2_CSQCAR2_SAO, ecc_offset);
	अगर (chip->options & न_अंकD_ROW_ADDR_3) अणु
		cfg[0] |= FIELD_PREP(FMC2_CSQCFGR1_ACYNBR, 5);
		cfg[4] |= FIELD_PREP(FMC2_CSQCAR2_ADDC5, page >> 16);
	पूर्ण अन्यथा अणु
		cfg[0] |= FIELD_PREP(FMC2_CSQCFGR1_ACYNBR, 4);
	पूर्ण

	regmap_bulk_ग_लिखो(nfc->regmap, FMC2_CSQCFGR1, cfg, 5);
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_dma_callback(व्योम *arg)
अणु
	complete((काष्ठा completion *)arg);
पूर्ण

/* Read/ग_लिखो data from/to a page */
अटल पूर्णांक sपंचांग32_fmc2_nfc_xfer(काष्ठा nand_chip *chip, स्थिर u8 *buf,
			       पूर्णांक raw, bool ग_लिखो_data)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	काष्ठा dma_async_tx_descriptor *desc_data, *desc_ecc;
	काष्ठा scatterlist *sg;
	काष्ठा dma_chan *dma_ch = nfc->dma_rx_ch;
	क्रमागत dma_data_direction dma_data_dir = DMA_FROM_DEVICE;
	क्रमागत dma_transfer_direction dma_transfer_dir = DMA_DEV_TO_MEM;
	पूर्णांक eccsteps = chip->ecc.steps;
	पूर्णांक eccsize = chip->ecc.size;
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(FMC2_TIMEOUT_MS);
	स्थिर u8 *p = buf;
	पूर्णांक s, ret;

	/* Configure DMA data */
	अगर (ग_लिखो_data) अणु
		dma_data_dir = DMA_TO_DEVICE;
		dma_transfer_dir = DMA_MEM_TO_DEV;
		dma_ch = nfc->dma_tx_ch;
	पूर्ण

	क्रम_each_sg(nfc->dma_data_sg.sgl, sg, eccsteps, s) अणु
		sg_set_buf(sg, p, eccsize);
		p += eccsize;
	पूर्ण

	ret = dma_map_sg(nfc->dev, nfc->dma_data_sg.sgl,
			 eccsteps, dma_data_dir);
	अगर (ret < 0)
		वापस ret;

	desc_data = dmaengine_prep_slave_sg(dma_ch, nfc->dma_data_sg.sgl,
					    eccsteps, dma_transfer_dir,
					    DMA_PREP_INTERRUPT);
	अगर (!desc_data) अणु
		ret = -ENOMEM;
		जाओ err_unmap_data;
	पूर्ण

	reinit_completion(&nfc->dma_data_complete);
	reinit_completion(&nfc->complete);
	desc_data->callback = sपंचांग32_fmc2_nfc_dma_callback;
	desc_data->callback_param = &nfc->dma_data_complete;
	ret = dma_submit_error(dmaengine_submit(desc_data));
	अगर (ret)
		जाओ err_unmap_data;

	dma_async_issue_pending(dma_ch);

	अगर (!ग_लिखो_data && !raw) अणु
		/* Configure DMA ECC status */
		p = nfc->ecc_buf;
		क्रम_each_sg(nfc->dma_ecc_sg.sgl, sg, eccsteps, s) अणु
			sg_set_buf(sg, p, nfc->dma_ecc_len);
			p += nfc->dma_ecc_len;
		पूर्ण

		ret = dma_map_sg(nfc->dev, nfc->dma_ecc_sg.sgl,
				 eccsteps, dma_data_dir);
		अगर (ret < 0)
			जाओ err_unmap_data;

		desc_ecc = dmaengine_prep_slave_sg(nfc->dma_ecc_ch,
						   nfc->dma_ecc_sg.sgl,
						   eccsteps, dma_transfer_dir,
						   DMA_PREP_INTERRUPT);
		अगर (!desc_ecc) अणु
			ret = -ENOMEM;
			जाओ err_unmap_ecc;
		पूर्ण

		reinit_completion(&nfc->dma_ecc_complete);
		desc_ecc->callback = sपंचांग32_fmc2_nfc_dma_callback;
		desc_ecc->callback_param = &nfc->dma_ecc_complete;
		ret = dma_submit_error(dmaengine_submit(desc_ecc));
		अगर (ret)
			जाओ err_unmap_ecc;

		dma_async_issue_pending(nfc->dma_ecc_ch);
	पूर्ण

	sपंचांग32_fmc2_nfc_clear_seq_irq(nfc);
	sपंचांग32_fmc2_nfc_enable_seq_irq(nfc);

	/* Start the transfer */
	regmap_update_bits(nfc->regmap, FMC2_CSQCR,
			   FMC2_CSQCR_CSQSTART, FMC2_CSQCR_CSQSTART);

	/* Wait end of sequencer transfer */
	अगर (!रुको_क्रम_completion_समयout(&nfc->complete, समयout)) अणु
		dev_err(nfc->dev, "seq timeout\n");
		sपंचांग32_fmc2_nfc_disable_seq_irq(nfc);
		dmaengine_terminate_all(dma_ch);
		अगर (!ग_लिखो_data && !raw)
			dmaengine_terminate_all(nfc->dma_ecc_ch);
		ret = -ETIMEDOUT;
		जाओ err_unmap_ecc;
	पूर्ण

	/* Wait DMA data transfer completion */
	अगर (!रुको_क्रम_completion_समयout(&nfc->dma_data_complete, समयout)) अणु
		dev_err(nfc->dev, "data DMA timeout\n");
		dmaengine_terminate_all(dma_ch);
		ret = -ETIMEDOUT;
	पूर्ण

	/* Wait DMA ECC transfer completion */
	अगर (!ग_लिखो_data && !raw) अणु
		अगर (!रुको_क्रम_completion_समयout(&nfc->dma_ecc_complete,
						 समयout)) अणु
			dev_err(nfc->dev, "ECC DMA timeout\n");
			dmaengine_terminate_all(nfc->dma_ecc_ch);
			ret = -ETIMEDOUT;
		पूर्ण
	पूर्ण

err_unmap_ecc:
	अगर (!ग_लिखो_data && !raw)
		dma_unmap_sg(nfc->dev, nfc->dma_ecc_sg.sgl,
			     eccsteps, dma_data_dir);

err_unmap_data:
	dma_unmap_sg(nfc->dev, nfc->dma_data_sg.sgl, eccsteps, dma_data_dir);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_seq_ग_लिखो(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				    पूर्णांक oob_required, पूर्णांक page, पूर्णांक raw)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	/* Configure the sequencer */
	sपंचांग32_fmc2_nfc_rw_page_init(chip, page, raw, true);

	/* Write the page */
	ret = sपंचांग32_fmc2_nfc_xfer(chip, buf, raw, true);
	अगर (ret)
		वापस ret;

	/* Write oob */
	अगर (oob_required) अणु
		ret = nand_change_ग_लिखो_column_op(chip, mtd->ग_लिखोsize,
						  chip->oob_poi, mtd->oobsize,
						  false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_seq_ग_लिखो_page(काष्ठा nand_chip *chip, स्थिर u8 *buf,
					 पूर्णांक oob_required, पूर्णांक page)
अणु
	पूर्णांक ret;

	ret = sपंचांग32_fmc2_nfc_select_chip(chip, chip->cur_cs);
	अगर (ret)
		वापस ret;

	वापस sपंचांग32_fmc2_nfc_seq_ग_लिखो(chip, buf, oob_required, page, false);
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_seq_ग_लिखो_page_raw(काष्ठा nand_chip *chip,
					     स्थिर u8 *buf, पूर्णांक oob_required,
					     पूर्णांक page)
अणु
	पूर्णांक ret;

	ret = sपंचांग32_fmc2_nfc_select_chip(chip, chip->cur_cs);
	अगर (ret)
		वापस ret;

	वापस sपंचांग32_fmc2_nfc_seq_ग_लिखो(chip, buf, oob_required, page, true);
पूर्ण

/* Get a status indicating which sectors have errors */
अटल u16 sपंचांग32_fmc2_nfc_get_mapping_status(काष्ठा sपंचांग32_fmc2_nfc *nfc)
अणु
	u32 csqemsr;

	regmap_पढ़ो(nfc->regmap, FMC2_CSQEMSR, &csqemsr);

	वापस FIELD_GET(FMC2_CSQEMSR_SEM, csqemsr);
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_seq_correct(काष्ठा nand_chip *chip, u8 *dat,
				      u8 *पढ़ो_ecc, u8 *calc_ecc)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	पूर्णांक eccbytes = chip->ecc.bytes;
	पूर्णांक eccsteps = chip->ecc.steps;
	पूर्णांक eccstrength = chip->ecc.strength;
	पूर्णांक i, s, eccsize = chip->ecc.size;
	u32 *ecc_sta = (u32 *)nfc->ecc_buf;
	u16 sta_map = sपंचांग32_fmc2_nfc_get_mapping_status(nfc);
	अचिन्हित पूर्णांक max_bitflips = 0;

	क्रम (i = 0, s = 0; s < eccsteps; s++, i += eccbytes, dat += eccsize) अणु
		पूर्णांक stat = 0;

		अगर (eccstrength == FMC2_ECC_HAM) अणु
			/* Ecc_sta = FMC2_HECCR */
			अगर (sta_map & BIT(s)) अणु
				sपंचांग32_fmc2_nfc_ham_set_ecc(*ecc_sta,
							   &calc_ecc[i]);
				stat = sपंचांग32_fmc2_nfc_ham_correct(chip, dat,
								  &पढ़ो_ecc[i],
								  &calc_ecc[i]);
			पूर्ण
			ecc_sta++;
		पूर्ण अन्यथा अणु
			/*
			 * Ecc_sta[0] = FMC2_BCHDSR0
			 * Ecc_sta[1] = FMC2_BCHDSR1
			 * Ecc_sta[2] = FMC2_BCHDSR2
			 * Ecc_sta[3] = FMC2_BCHDSR3
			 * Ecc_sta[4] = FMC2_BCHDSR4
			 */
			अगर (sta_map & BIT(s))
				stat = sपंचांग32_fmc2_nfc_bch_decode(eccsize, dat,
								 ecc_sta);
			ecc_sta += 5;
		पूर्ण

		अगर (stat == -EBADMSG)
			/* Check क्रम empty pages with bitflips */
			stat = nand_check_erased_ecc_chunk(dat, eccsize,
							   &पढ़ो_ecc[i],
							   eccbytes,
							   शून्य, 0,
							   eccstrength);

		अगर (stat < 0) अणु
			mtd->ecc_stats.failed++;
		पूर्ण अन्यथा अणु
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, stat);
		पूर्ण
	पूर्ण

	वापस max_bitflips;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_seq_पढ़ो_page(काष्ठा nand_chip *chip, u8 *buf,
					पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	u8 *ecc_calc = chip->ecc.calc_buf;
	u8 *ecc_code = chip->ecc.code_buf;
	u16 sta_map;
	पूर्णांक ret;

	ret = sपंचांग32_fmc2_nfc_select_chip(chip, chip->cur_cs);
	अगर (ret)
		वापस ret;

	/* Configure the sequencer */
	sपंचांग32_fmc2_nfc_rw_page_init(chip, page, 0, false);

	/* Read the page */
	ret = sपंचांग32_fmc2_nfc_xfer(chip, buf, 0, false);
	अगर (ret)
		वापस ret;

	sta_map = sपंचांग32_fmc2_nfc_get_mapping_status(nfc);

	/* Check अगर errors happen */
	अगर (likely(!sta_map)) अणु
		अगर (oob_required)
			वापस nand_change_पढ़ो_column_op(chip, mtd->ग_लिखोsize,
							  chip->oob_poi,
							  mtd->oobsize, false);

		वापस 0;
	पूर्ण

	/* Read oob */
	ret = nand_change_पढ़ो_column_op(chip, mtd->ग_लिखोsize,
					 chip->oob_poi, mtd->oobsize, false);
	अगर (ret)
		वापस ret;

	ret = mtd_ooblayout_get_eccbytes(mtd, ecc_code, chip->oob_poi, 0,
					 chip->ecc.total);
	अगर (ret)
		वापस ret;

	/* Correct data */
	वापस chip->ecc.correct(chip, buf, ecc_code, ecc_calc);
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_seq_पढ़ो_page_raw(काष्ठा nand_chip *chip, u8 *buf,
					    पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	ret = sपंचांग32_fmc2_nfc_select_chip(chip, chip->cur_cs);
	अगर (ret)
		वापस ret;

	/* Configure the sequencer */
	sपंचांग32_fmc2_nfc_rw_page_init(chip, page, 1, false);

	/* Read the page */
	ret = sपंचांग32_fmc2_nfc_xfer(chip, buf, 1, false);
	अगर (ret)
		वापस ret;

	/* Read oob */
	अगर (oob_required)
		वापस nand_change_पढ़ो_column_op(chip, mtd->ग_लिखोsize,
						  chip->oob_poi, mtd->oobsize,
						  false);

	वापस 0;
पूर्ण

अटल irqवापस_t sपंचांग32_fmc2_nfc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = (काष्ठा sपंचांग32_fmc2_nfc *)dev_id;

	अगर (nfc->irq_state == FMC2_IRQ_SEQ)
		/* Sequencer is used */
		sपंचांग32_fmc2_nfc_disable_seq_irq(nfc);
	अन्यथा अगर (nfc->irq_state == FMC2_IRQ_BCH)
		/* BCH is used */
		sपंचांग32_fmc2_nfc_disable_bch_irq(nfc);

	complete(&nfc->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_पढ़ो_data(काष्ठा nand_chip *chip, व्योम *buf,
				     अचिन्हित पूर्णांक len, bool क्रमce_8bit)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	व्योम __iomem *io_addr_r = nfc->data_base[nfc->cs_sel];

	अगर (क्रमce_8bit && chip->options & न_अंकD_BUSWIDTH_16)
		/* Reconfigure bus width to 8-bit */
		sपंचांग32_fmc2_nfc_set_buswidth_16(nfc, false);

	अगर (!IS_ALIGNED((uपूर्णांकptr_t)buf, माप(u32))) अणु
		अगर (!IS_ALIGNED((uपूर्णांकptr_t)buf, माप(u16)) && len) अणु
			*(u8 *)buf = पढ़ोb_relaxed(io_addr_r);
			buf += माप(u8);
			len -= माप(u8);
		पूर्ण

		अगर (!IS_ALIGNED((uपूर्णांकptr_t)buf, माप(u32)) &&
		    len >= माप(u16)) अणु
			*(u16 *)buf = पढ़ोw_relaxed(io_addr_r);
			buf += माप(u16);
			len -= माप(u16);
		पूर्ण
	पूर्ण

	/* Buf is aligned */
	जबतक (len >= माप(u32)) अणु
		*(u32 *)buf = पढ़ोl_relaxed(io_addr_r);
		buf += माप(u32);
		len -= माप(u32);
	पूर्ण

	/* Read reमुख्यing bytes */
	अगर (len >= माप(u16)) अणु
		*(u16 *)buf = पढ़ोw_relaxed(io_addr_r);
		buf += माप(u16);
		len -= माप(u16);
	पूर्ण

	अगर (len)
		*(u8 *)buf = पढ़ोb_relaxed(io_addr_r);

	अगर (क्रमce_8bit && chip->options & न_अंकD_BUSWIDTH_16)
		/* Reconfigure bus width to 16-bit */
		sपंचांग32_fmc2_nfc_set_buswidth_16(nfc, true);
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_ग_लिखो_data(काष्ठा nand_chip *chip, स्थिर व्योम *buf,
				      अचिन्हित पूर्णांक len, bool क्रमce_8bit)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	व्योम __iomem *io_addr_w = nfc->data_base[nfc->cs_sel];

	अगर (क्रमce_8bit && chip->options & न_अंकD_BUSWIDTH_16)
		/* Reconfigure bus width to 8-bit */
		sपंचांग32_fmc2_nfc_set_buswidth_16(nfc, false);

	अगर (!IS_ALIGNED((uपूर्णांकptr_t)buf, माप(u32))) अणु
		अगर (!IS_ALIGNED((uपूर्णांकptr_t)buf, माप(u16)) && len) अणु
			ग_लिखोb_relaxed(*(u8 *)buf, io_addr_w);
			buf += माप(u8);
			len -= माप(u8);
		पूर्ण

		अगर (!IS_ALIGNED((uपूर्णांकptr_t)buf, माप(u32)) &&
		    len >= माप(u16)) अणु
			ग_लिखोw_relaxed(*(u16 *)buf, io_addr_w);
			buf += माप(u16);
			len -= माप(u16);
		पूर्ण
	पूर्ण

	/* Buf is aligned */
	जबतक (len >= माप(u32)) अणु
		ग_लिखोl_relaxed(*(u32 *)buf, io_addr_w);
		buf += माप(u32);
		len -= माप(u32);
	पूर्ण

	/* Write reमुख्यing bytes */
	अगर (len >= माप(u16)) अणु
		ग_लिखोw_relaxed(*(u16 *)buf, io_addr_w);
		buf += माप(u16);
		len -= माप(u16);
	पूर्ण

	अगर (len)
		ग_लिखोb_relaxed(*(u8 *)buf, io_addr_w);

	अगर (क्रमce_8bit && chip->options & न_अंकD_BUSWIDTH_16)
		/* Reconfigure bus width to 16-bit */
		sपंचांग32_fmc2_nfc_set_buswidth_16(nfc, true);
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_रुकोrdy(काष्ठा nand_chip *chip,
				  अचिन्हित दीर्घ समयout_ms)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	स्थिर काष्ठा nand_sdr_timings *timings;
	u32 isr, sr;

	/* Check अगर there is no pending requests to the न_अंकD flash */
	अगर (regmap_पढ़ो_poll_समयout(nfc->regmap, FMC2_SR, sr,
				     sr & FMC2_SR_NWRF, 1,
				     1000 * FMC2_TIMEOUT_MS))
		dev_warn(nfc->dev, "Waitrdy timeout\n");

	/* Wait tWB beक्रमe R/B# संकेत is low */
	timings = nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
	ndelay(PSEC_TO_NSEC(timings->tWB_max));

	/* R/B# संकेत is low, clear high level flag */
	regmap_ग_लिखो(nfc->regmap, FMC2_ICR, FMC2_ICR_CIHLF);

	/* Wait R/B# संकेत is high */
	वापस regmap_पढ़ो_poll_समयout(nfc->regmap, FMC2_ISR, isr,
					isr & FMC2_ISR_IHLF, 5,
					1000 * FMC2_TIMEOUT_MS);
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_exec_op(काष्ठा nand_chip *chip,
				  स्थिर काष्ठा nand_operation *op,
				  bool check_only)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	स्थिर काष्ठा nand_op_instr *instr = शून्य;
	अचिन्हित पूर्णांक op_id, i, समयout;
	पूर्णांक ret;

	अगर (check_only)
		वापस 0;

	ret = sपंचांग32_fmc2_nfc_select_chip(chip, op->cs);
	अगर (ret)
		वापस ret;

	क्रम (op_id = 0; op_id < op->ninstrs; op_id++) अणु
		instr = &op->instrs[op_id];

		चयन (instr->type) अणु
		हाल न_अंकD_OP_CMD_INSTR:
			ग_लिखोb_relaxed(instr->ctx.cmd.opcode,
				       nfc->cmd_base[nfc->cs_sel]);
			अवरोध;

		हाल न_अंकD_OP_ADDR_INSTR:
			क्रम (i = 0; i < instr->ctx.addr.naddrs; i++)
				ग_लिखोb_relaxed(instr->ctx.addr.addrs[i],
					       nfc->addr_base[nfc->cs_sel]);
			अवरोध;

		हाल न_अंकD_OP_DATA_IN_INSTR:
			sपंचांग32_fmc2_nfc_पढ़ो_data(chip, instr->ctx.data.buf.in,
						 instr->ctx.data.len,
						 instr->ctx.data.क्रमce_8bit);
			अवरोध;

		हाल न_अंकD_OP_DATA_OUT_INSTR:
			sपंचांग32_fmc2_nfc_ग_लिखो_data(chip, instr->ctx.data.buf.out,
						  instr->ctx.data.len,
						  instr->ctx.data.क्रमce_8bit);
			अवरोध;

		हाल न_अंकD_OP_WAITRDY_INSTR:
			समयout = instr->ctx.रुकोrdy.समयout_ms;
			ret = sपंचांग32_fmc2_nfc_रुकोrdy(chip, समयout);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_init(काष्ठा sपंचांग32_fmc2_nfc *nfc)
अणु
	u32 pcr;

	regmap_पढ़ो(nfc->regmap, FMC2_PCR, &pcr);

	/* Set CS used to undefined */
	nfc->cs_sel = -1;

	/* Enable रुको feature and nand flash memory bank */
	pcr |= FMC2_PCR_PWAITEN;
	pcr |= FMC2_PCR_PBKEN;

	/* Set buswidth to 8 bits mode क्रम identअगरication */
	pcr &= ~FMC2_PCR_PWID;

	/* ECC logic is disabled */
	pcr &= ~FMC2_PCR_ECCEN;

	/* Default mode */
	pcr &= ~FMC2_PCR_ECCALG;
	pcr &= ~FMC2_PCR_BCHECC;
	pcr &= ~FMC2_PCR_WEN;

	/* Set शेष ECC sector size */
	pcr &= ~FMC2_PCR_ECCSS;
	pcr |= FIELD_PREP(FMC2_PCR_ECCSS, FMC2_PCR_ECCSS_2048);

	/* Set शेष tclr/tar timings */
	pcr &= ~FMC2_PCR_TCLR;
	pcr |= FIELD_PREP(FMC2_PCR_TCLR, FMC2_PCR_TCLR_DEFAULT);
	pcr &= ~FMC2_PCR_TAR;
	pcr |= FIELD_PREP(FMC2_PCR_TAR, FMC2_PCR_TAR_DEFAULT);

	/* Enable FMC2 controller */
	अगर (nfc->dev == nfc->cdev)
		regmap_update_bits(nfc->regmap, FMC2_BCR1,
				   FMC2_BCR1_FMC2EN, FMC2_BCR1_FMC2EN);

	regmap_ग_लिखो(nfc->regmap, FMC2_PCR, pcr);
	regmap_ग_लिखो(nfc->regmap, FMC2_PMEM, FMC2_PMEM_DEFAULT);
	regmap_ग_लिखो(nfc->regmap, FMC2_PATT, FMC2_PATT_DEFAULT);
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_calc_timings(काष्ठा nand_chip *chip,
					स्थिर काष्ठा nand_sdr_timings *sdrt)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	काष्ठा sपंचांग32_fmc2_nand *nand = to_fmc2_nand(chip);
	काष्ठा sपंचांग32_fmc2_timings *tims = &nand->timings;
	अचिन्हित दीर्घ hclk = clk_get_rate(nfc->clk);
	अचिन्हित दीर्घ hclkp = NSEC_PER_SEC / (hclk / 1000);
	अचिन्हित दीर्घ timing, tar, tclr, thiz, tरुको;
	अचिन्हित दीर्घ tset_mem, tset_att, thold_mem, thold_att;

	tar = max_t(अचिन्हित दीर्घ, hclkp, sdrt->tAR_min);
	timing = DIV_ROUND_UP(tar, hclkp) - 1;
	tims->tar = min_t(अचिन्हित दीर्घ, timing, FMC2_PCR_TIMING_MASK);

	tclr = max_t(अचिन्हित दीर्घ, hclkp, sdrt->tCLR_min);
	timing = DIV_ROUND_UP(tclr, hclkp) - 1;
	tims->tclr = min_t(अचिन्हित दीर्घ, timing, FMC2_PCR_TIMING_MASK);

	tims->thiz = FMC2_THIZ;
	thiz = (tims->thiz + 1) * hclkp;

	/*
	 * tWAIT > tRP
	 * tWAIT > tWP
	 * tWAIT > tREA + tIO
	 */
	tरुको = max_t(अचिन्हित दीर्घ, hclkp, sdrt->tRP_min);
	tरुको = max_t(अचिन्हित दीर्घ, tरुको, sdrt->tWP_min);
	tरुको = max_t(अचिन्हित दीर्घ, tरुको, sdrt->tREA_max + FMC2_TIO);
	timing = DIV_ROUND_UP(tरुको, hclkp);
	tims->tरुको = clamp_val(timing, 1, FMC2_PMEM_PATT_TIMING_MASK);

	/*
	 * tSETUP_MEM > tCS - tWAIT
	 * tSETUP_MEM > tALS - tWAIT
	 * tSETUP_MEM > tDS - (tWAIT - tHIZ)
	 */
	tset_mem = hclkp;
	अगर (sdrt->tCS_min > tरुको && (tset_mem < sdrt->tCS_min - tरुको))
		tset_mem = sdrt->tCS_min - tरुको;
	अगर (sdrt->tALS_min > tरुको && (tset_mem < sdrt->tALS_min - tरुको))
		tset_mem = sdrt->tALS_min - tरुको;
	अगर (tरुको > thiz && (sdrt->tDS_min > tरुको - thiz) &&
	    (tset_mem < sdrt->tDS_min - (tरुको - thiz)))
		tset_mem = sdrt->tDS_min - (tरुको - thiz);
	timing = DIV_ROUND_UP(tset_mem, hclkp);
	tims->tset_mem = clamp_val(timing, 1, FMC2_PMEM_PATT_TIMING_MASK);

	/*
	 * tHOLD_MEM > tCH
	 * tHOLD_MEM > tREH - tSETUP_MEM
	 * tHOLD_MEM > max(tRC, tWC) - (tSETUP_MEM + tWAIT)
	 */
	thold_mem = max_t(अचिन्हित दीर्घ, hclkp, sdrt->tCH_min);
	अगर (sdrt->tREH_min > tset_mem &&
	    (thold_mem < sdrt->tREH_min - tset_mem))
		thold_mem = sdrt->tREH_min - tset_mem;
	अगर ((sdrt->tRC_min > tset_mem + tरुको) &&
	    (thold_mem < sdrt->tRC_min - (tset_mem + tरुको)))
		thold_mem = sdrt->tRC_min - (tset_mem + tरुको);
	अगर ((sdrt->tWC_min > tset_mem + tरुको) &&
	    (thold_mem < sdrt->tWC_min - (tset_mem + tरुको)))
		thold_mem = sdrt->tWC_min - (tset_mem + tरुको);
	timing = DIV_ROUND_UP(thold_mem, hclkp);
	tims->thold_mem = clamp_val(timing, 1, FMC2_PMEM_PATT_TIMING_MASK);

	/*
	 * tSETUP_ATT > tCS - tWAIT
	 * tSETUP_ATT > tCLS - tWAIT
	 * tSETUP_ATT > tALS - tWAIT
	 * tSETUP_ATT > tRHW - tHOLD_MEM
	 * tSETUP_ATT > tDS - (tWAIT - tHIZ)
	 */
	tset_att = hclkp;
	अगर (sdrt->tCS_min > tरुको && (tset_att < sdrt->tCS_min - tरुको))
		tset_att = sdrt->tCS_min - tरुको;
	अगर (sdrt->tCLS_min > tरुको && (tset_att < sdrt->tCLS_min - tरुको))
		tset_att = sdrt->tCLS_min - tरुको;
	अगर (sdrt->tALS_min > tरुको && (tset_att < sdrt->tALS_min - tरुको))
		tset_att = sdrt->tALS_min - tरुको;
	अगर (sdrt->tRHW_min > thold_mem &&
	    (tset_att < sdrt->tRHW_min - thold_mem))
		tset_att = sdrt->tRHW_min - thold_mem;
	अगर (tरुको > thiz && (sdrt->tDS_min > tरुको - thiz) &&
	    (tset_att < sdrt->tDS_min - (tरुको - thiz)))
		tset_att = sdrt->tDS_min - (tरुको - thiz);
	timing = DIV_ROUND_UP(tset_att, hclkp);
	tims->tset_att = clamp_val(timing, 1, FMC2_PMEM_PATT_TIMING_MASK);

	/*
	 * tHOLD_ATT > tALH
	 * tHOLD_ATT > tCH
	 * tHOLD_ATT > tCLH
	 * tHOLD_ATT > tCOH
	 * tHOLD_ATT > tDH
	 * tHOLD_ATT > tWB + tIO + tSYNC - tSETUP_MEM
	 * tHOLD_ATT > tADL - tSETUP_MEM
	 * tHOLD_ATT > tWH - tSETUP_MEM
	 * tHOLD_ATT > tWHR - tSETUP_MEM
	 * tHOLD_ATT > tRC - (tSETUP_ATT + tWAIT)
	 * tHOLD_ATT > tWC - (tSETUP_ATT + tWAIT)
	 */
	thold_att = max_t(अचिन्हित दीर्घ, hclkp, sdrt->tALH_min);
	thold_att = max_t(अचिन्हित दीर्घ, thold_att, sdrt->tCH_min);
	thold_att = max_t(अचिन्हित दीर्घ, thold_att, sdrt->tCLH_min);
	thold_att = max_t(अचिन्हित दीर्घ, thold_att, sdrt->tCOH_min);
	thold_att = max_t(अचिन्हित दीर्घ, thold_att, sdrt->tDH_min);
	अगर ((sdrt->tWB_max + FMC2_TIO + FMC2_TSYNC > tset_mem) &&
	    (thold_att < sdrt->tWB_max + FMC2_TIO + FMC2_TSYNC - tset_mem))
		thold_att = sdrt->tWB_max + FMC2_TIO + FMC2_TSYNC - tset_mem;
	अगर (sdrt->tADL_min > tset_mem &&
	    (thold_att < sdrt->tADL_min - tset_mem))
		thold_att = sdrt->tADL_min - tset_mem;
	अगर (sdrt->tWH_min > tset_mem &&
	    (thold_att < sdrt->tWH_min - tset_mem))
		thold_att = sdrt->tWH_min - tset_mem;
	अगर (sdrt->tWHR_min > tset_mem &&
	    (thold_att < sdrt->tWHR_min - tset_mem))
		thold_att = sdrt->tWHR_min - tset_mem;
	अगर ((sdrt->tRC_min > tset_att + tरुको) &&
	    (thold_att < sdrt->tRC_min - (tset_att + tरुको)))
		thold_att = sdrt->tRC_min - (tset_att + tरुको);
	अगर ((sdrt->tWC_min > tset_att + tरुको) &&
	    (thold_att < sdrt->tWC_min - (tset_att + tरुको)))
		thold_att = sdrt->tWC_min - (tset_att + tरुको);
	timing = DIV_ROUND_UP(thold_att, hclkp);
	tims->thold_att = clamp_val(timing, 1, FMC2_PMEM_PATT_TIMING_MASK);
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक chipnr,
					  स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	स्थिर काष्ठा nand_sdr_timings *sdrt;

	sdrt = nand_get_sdr_timings(conf);
	अगर (IS_ERR(sdrt))
		वापस PTR_ERR(sdrt);

	अगर (chipnr == न_अंकD_DATA_IFACE_CHECK_ONLY)
		वापस 0;

	sपंचांग32_fmc2_nfc_calc_timings(chip, sdrt);
	sपंचांग32_fmc2_nfc_timings_init(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_dma_setup(काष्ठा sपंचांग32_fmc2_nfc *nfc)
अणु
	पूर्णांक ret = 0;

	nfc->dma_tx_ch = dma_request_chan(nfc->dev, "tx");
	अगर (IS_ERR(nfc->dma_tx_ch)) अणु
		ret = PTR_ERR(nfc->dma_tx_ch);
		अगर (ret != -ENODEV && ret != -EPROBE_DEFER)
			dev_err(nfc->dev,
				"failed to request tx DMA channel: %d\n", ret);
		nfc->dma_tx_ch = शून्य;
		जाओ err_dma;
	पूर्ण

	nfc->dma_rx_ch = dma_request_chan(nfc->dev, "rx");
	अगर (IS_ERR(nfc->dma_rx_ch)) अणु
		ret = PTR_ERR(nfc->dma_rx_ch);
		अगर (ret != -ENODEV && ret != -EPROBE_DEFER)
			dev_err(nfc->dev,
				"failed to request rx DMA channel: %d\n", ret);
		nfc->dma_rx_ch = शून्य;
		जाओ err_dma;
	पूर्ण

	nfc->dma_ecc_ch = dma_request_chan(nfc->dev, "ecc");
	अगर (IS_ERR(nfc->dma_ecc_ch)) अणु
		ret = PTR_ERR(nfc->dma_ecc_ch);
		अगर (ret != -ENODEV && ret != -EPROBE_DEFER)
			dev_err(nfc->dev,
				"failed to request ecc DMA channel: %d\n", ret);
		nfc->dma_ecc_ch = शून्य;
		जाओ err_dma;
	पूर्ण

	ret = sg_alloc_table(&nfc->dma_ecc_sg, FMC2_MAX_SG, GFP_KERNEL);
	अगर (ret)
		वापस ret;

	/* Allocate a buffer to store ECC status रेजिस्टरs */
	nfc->ecc_buf = devm_kzalloc(nfc->dev, FMC2_MAX_ECC_BUF_LEN, GFP_KERNEL);
	अगर (!nfc->ecc_buf)
		वापस -ENOMEM;

	ret = sg_alloc_table(&nfc->dma_data_sg, FMC2_MAX_SG, GFP_KERNEL);
	अगर (ret)
		वापस ret;

	init_completion(&nfc->dma_data_complete);
	init_completion(&nfc->dma_ecc_complete);

	वापस 0;

err_dma:
	अगर (ret == -ENODEV) अणु
		dev_warn(nfc->dev,
			 "DMAs not defined in the DT, polling mode is used\n");
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_fmc2_nfc_nand_callbacks_setup(काष्ठा nand_chip *chip)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);

	/*
	 * Specअगरic callbacks to पढ़ो/ग_लिखो a page depending on
	 * the mode (polling/sequencer) and the algo used (Hamming, BCH).
	 */
	अगर (nfc->dma_tx_ch && nfc->dma_rx_ch && nfc->dma_ecc_ch) अणु
		/* DMA => use sequencer mode callbacks */
		chip->ecc.correct = sपंचांग32_fmc2_nfc_seq_correct;
		chip->ecc.ग_लिखो_page = sपंचांग32_fmc2_nfc_seq_ग_लिखो_page;
		chip->ecc.पढ़ो_page = sपंचांग32_fmc2_nfc_seq_पढ़ो_page;
		chip->ecc.ग_लिखो_page_raw = sपंचांग32_fmc2_nfc_seq_ग_लिखो_page_raw;
		chip->ecc.पढ़ो_page_raw = sपंचांग32_fmc2_nfc_seq_पढ़ो_page_raw;
	पूर्ण अन्यथा अणु
		/* No DMA => use polling mode callbacks */
		chip->ecc.hwctl = sपंचांग32_fmc2_nfc_hwctl;
		अगर (chip->ecc.strength == FMC2_ECC_HAM) अणु
			/* Hamming is used */
			chip->ecc.calculate = sपंचांग32_fmc2_nfc_ham_calculate;
			chip->ecc.correct = sपंचांग32_fmc2_nfc_ham_correct;
			chip->ecc.options |= न_अंकD_ECC_GENERIC_ERASED_CHECK;
		पूर्ण अन्यथा अणु
			/* BCH is used */
			chip->ecc.calculate = sपंचांग32_fmc2_nfc_bch_calculate;
			chip->ecc.correct = sपंचांग32_fmc2_nfc_bch_correct;
			chip->ecc.पढ़ो_page = sपंचांग32_fmc2_nfc_पढ़ो_page;
		पूर्ण
	पूर्ण

	/* Specअगरic configurations depending on the algo used */
	अगर (chip->ecc.strength == FMC2_ECC_HAM)
		chip->ecc.bytes = chip->options & न_अंकD_BUSWIDTH_16 ? 4 : 3;
	अन्यथा अगर (chip->ecc.strength == FMC2_ECC_BCH8)
		chip->ecc.bytes = chip->options & न_अंकD_BUSWIDTH_16 ? 14 : 13;
	अन्यथा
		chip->ecc.bytes = chip->options & न_अंकD_BUSWIDTH_16 ? 8 : 7;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
					काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;

	अगर (section)
		वापस -दुस्फल;

	oobregion->length = ecc->total;
	oobregion->offset = FMC2_BBM_LEN;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
					 काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;

	अगर (section)
		वापस -दुस्फल;

	oobregion->length = mtd->oobsize - ecc->total - FMC2_BBM_LEN;
	oobregion->offset = ecc->total + FMC2_BBM_LEN;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops sपंचांग32_fmc2_nfc_ooblayout_ops = अणु
	.ecc = sपंचांग32_fmc2_nfc_ooblayout_ecc,
	.मुक्त = sपंचांग32_fmc2_nfc_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक sपंचांग32_fmc2_nfc_calc_ecc_bytes(पूर्णांक step_size, पूर्णांक strength)
अणु
	/* Hamming */
	अगर (strength == FMC2_ECC_HAM)
		वापस 4;

	/* BCH8 */
	अगर (strength == FMC2_ECC_BCH8)
		वापस 14;

	/* BCH4 */
	वापस 8;
पूर्ण

न_अंकD_ECC_CAPS_SINGLE(sपंचांग32_fmc2_nfc_ecc_caps, sपंचांग32_fmc2_nfc_calc_ecc_bytes,
		     FMC2_ECC_STEP_SIZE,
		     FMC2_ECC_HAM, FMC2_ECC_BCH4, FMC2_ECC_BCH8);

अटल पूर्णांक sपंचांग32_fmc2_nfc_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = to_sपंचांग32_nfc(chip->controller);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	/*
	 * Only न_अंकD_ECC_ENGINE_TYPE_ON_HOST mode is actually supported
	 * Hamming => ecc.strength = 1
	 * BCH4 => ecc.strength = 4
	 * BCH8 => ecc.strength = 8
	 * ECC sector size = 512
	 */
	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST) अणु
		dev_err(nfc->dev,
			"nand_ecc_engine_type is not well defined in the DT\n");
		वापस -EINVAL;
	पूर्ण

	/* Default ECC settings in हाल they are not set in the device tree */
	अगर (!chip->ecc.size)
		chip->ecc.size = FMC2_ECC_STEP_SIZE;

	अगर (!chip->ecc.strength)
		chip->ecc.strength = FMC2_ECC_BCH8;

	ret = nand_ecc_choose_conf(chip, &sपंचांग32_fmc2_nfc_ecc_caps,
				   mtd->oobsize - FMC2_BBM_LEN);
	अगर (ret) अणु
		dev_err(nfc->dev, "no valid ECC settings set\n");
		वापस ret;
	पूर्ण

	अगर (mtd->ग_लिखोsize / chip->ecc.size > FMC2_MAX_SG) अणु
		dev_err(nfc->dev, "nand page size is not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (chip->bbt_options & न_अंकD_BBT_USE_FLASH)
		chip->bbt_options |= न_अंकD_BBT_NO_OOB;

	sपंचांग32_fmc2_nfc_nand_callbacks_setup(chip);

	mtd_set_ooblayout(mtd, &sपंचांग32_fmc2_nfc_ooblayout_ops);

	sपंचांग32_fmc2_nfc_setup(chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops sपंचांग32_fmc2_nfc_controller_ops = अणु
	.attach_chip = sपंचांग32_fmc2_nfc_attach_chip,
	.exec_op = sपंचांग32_fmc2_nfc_exec_op,
	.setup_पूर्णांकerface = sपंचांग32_fmc2_nfc_setup_पूर्णांकerface,
पूर्ण;

अटल पूर्णांक sपंचांग32_fmc2_nfc_parse_child(काष्ठा sपंचांग32_fmc2_nfc *nfc,
				      काष्ठा device_node *dn)
अणु
	काष्ठा sपंचांग32_fmc2_nand *nand = &nfc->nand;
	u32 cs;
	पूर्णांक ret, i;

	अगर (!of_get_property(dn, "reg", &nand->ncs))
		वापस -EINVAL;

	nand->ncs /= माप(u32);
	अगर (!nand->ncs) अणु
		dev_err(nfc->dev, "invalid reg property size\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < nand->ncs; i++) अणु
		ret = of_property_पढ़ो_u32_index(dn, "reg", i, &cs);
		अगर (ret) अणु
			dev_err(nfc->dev, "could not retrieve reg property: %d\n",
				ret);
			वापस ret;
		पूर्ण

		अगर (cs >= FMC2_MAX_CE) अणु
			dev_err(nfc->dev, "invalid reg value: %d\n", cs);
			वापस -EINVAL;
		पूर्ण

		अगर (nfc->cs_asचिन्हित & BIT(cs)) अणु
			dev_err(nfc->dev, "cs already assigned: %d\n", cs);
			वापस -EINVAL;
		पूर्ण

		nfc->cs_asचिन्हित |= BIT(cs);
		nand->cs_used[i] = cs;
	पूर्ण

	nand_set_flash_node(&nand->chip, dn);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_parse_dt(काष्ठा sपंचांग32_fmc2_nfc *nfc)
अणु
	काष्ठा device_node *dn = nfc->dev->of_node;
	काष्ठा device_node *child;
	पूर्णांक nchips = of_get_child_count(dn);
	पूर्णांक ret = 0;

	अगर (!nchips) अणु
		dev_err(nfc->dev, "NAND chip not defined\n");
		वापस -EINVAL;
	पूर्ण

	अगर (nchips > 1) अणु
		dev_err(nfc->dev, "too many NAND chips defined\n");
		वापस -EINVAL;
	पूर्ण

	क्रम_each_child_of_node(dn, child) अणु
		ret = sपंचांग32_fmc2_nfc_parse_child(nfc, child);
		अगर (ret < 0) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_set_cdev(काष्ठा sपंचांग32_fmc2_nfc *nfc)
अणु
	काष्ठा device *dev = nfc->dev;
	bool ebi_found = false;

	अगर (dev->parent && of_device_is_compatible(dev->parent->of_node,
						   "st,stm32mp1-fmc2-ebi"))
		ebi_found = true;

	अगर (of_device_is_compatible(dev->of_node, "st,stm32mp1-fmc2-nfc")) अणु
		अगर (ebi_found) अणु
			nfc->cdev = dev->parent;

			वापस 0;
		पूर्ण

		वापस -EINVAL;
	पूर्ण

	अगर (ebi_found)
		वापस -EINVAL;

	nfc->cdev = dev;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा reset_control *rstc;
	काष्ठा sपंचांग32_fmc2_nfc *nfc;
	काष्ठा sपंचांग32_fmc2_nand *nand;
	काष्ठा resource *res;
	काष्ठा mtd_info *mtd;
	काष्ठा nand_chip *chip;
	काष्ठा resource cres;
	पूर्णांक chip_cs, mem_region, ret, irq;
	पूर्णांक start_region = 0;

	nfc = devm_kzalloc(dev, माप(*nfc), GFP_KERNEL);
	अगर (!nfc)
		वापस -ENOMEM;

	nfc->dev = dev;
	nand_controller_init(&nfc->base);
	nfc->base.ops = &sपंचांग32_fmc2_nfc_controller_ops;

	ret = sपंचांग32_fmc2_nfc_set_cdev(nfc);
	अगर (ret)
		वापस ret;

	ret = sपंचांग32_fmc2_nfc_parse_dt(nfc);
	अगर (ret)
		वापस ret;

	ret = of_address_to_resource(nfc->cdev->of_node, 0, &cres);
	अगर (ret)
		वापस ret;

	nfc->io_phys_addr = cres.start;

	nfc->regmap = device_node_to_regmap(nfc->cdev->of_node);
	अगर (IS_ERR(nfc->regmap))
		वापस PTR_ERR(nfc->regmap);

	अगर (nfc->dev == nfc->cdev)
		start_region = 1;

	क्रम (chip_cs = 0, mem_region = start_region; chip_cs < FMC2_MAX_CE;
	     chip_cs++, mem_region += 3) अणु
		अगर (!(nfc->cs_asचिन्हित & BIT(chip_cs)))
			जारी;

		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, mem_region);
		nfc->data_base[chip_cs] = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(nfc->data_base[chip_cs]))
			वापस PTR_ERR(nfc->data_base[chip_cs]);

		nfc->data_phys_addr[chip_cs] = res->start;

		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
					    mem_region + 1);
		nfc->cmd_base[chip_cs] = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(nfc->cmd_base[chip_cs]))
			वापस PTR_ERR(nfc->cmd_base[chip_cs]);

		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
					    mem_region + 2);
		nfc->addr_base[chip_cs] = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(nfc->addr_base[chip_cs]))
			वापस PTR_ERR(nfc->addr_base[chip_cs]);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(dev, irq, sपंचांग32_fmc2_nfc_irq, 0,
			       dev_name(dev), nfc);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq\n");
		वापस ret;
	पूर्ण

	init_completion(&nfc->complete);

	nfc->clk = devm_clk_get(nfc->cdev, शून्य);
	अगर (IS_ERR(nfc->clk))
		वापस PTR_ERR(nfc->clk);

	ret = clk_prepare_enable(nfc->clk);
	अगर (ret) अणु
		dev_err(dev, "can not enable the clock\n");
		वापस ret;
	पूर्ण

	rstc = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(rstc)) अणु
		ret = PTR_ERR(rstc);
		अगर (ret == -EPROBE_DEFER)
			जाओ err_clk_disable;
	पूर्ण अन्यथा अणु
		reset_control_निश्चित(rstc);
		reset_control_deनिश्चित(rstc);
	पूर्ण

	ret = sपंचांग32_fmc2_nfc_dma_setup(nfc);
	अगर (ret)
		जाओ err_release_dma;

	sपंचांग32_fmc2_nfc_init(nfc);

	nand = &nfc->nand;
	chip = &nand->chip;
	mtd = nand_to_mtd(chip);
	mtd->dev.parent = dev;

	chip->controller = &nfc->base;
	chip->options |= न_अंकD_BUSWIDTH_AUTO | न_अंकD_NO_SUBPAGE_WRITE |
			 न_अंकD_USES_DMA;

	/* Scan to find existence of the device */
	ret = nand_scan(chip, nand->ncs);
	अगर (ret)
		जाओ err_release_dma;

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret)
		जाओ err_nand_cleanup;

	platक्रमm_set_drvdata(pdev, nfc);

	वापस 0;

err_nand_cleanup:
	nand_cleanup(chip);

err_release_dma:
	अगर (nfc->dma_ecc_ch)
		dma_release_channel(nfc->dma_ecc_ch);
	अगर (nfc->dma_tx_ch)
		dma_release_channel(nfc->dma_tx_ch);
	अगर (nfc->dma_rx_ch)
		dma_release_channel(nfc->dma_rx_ch);

	sg_मुक्त_table(&nfc->dma_data_sg);
	sg_मुक्त_table(&nfc->dma_ecc_sg);

err_clk_disable:
	clk_disable_unprepare(nfc->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_nfc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांग32_fmc2_nand *nand = &nfc->nand;
	काष्ठा nand_chip *chip = &nand->chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);

	अगर (nfc->dma_ecc_ch)
		dma_release_channel(nfc->dma_ecc_ch);
	अगर (nfc->dma_tx_ch)
		dma_release_channel(nfc->dma_tx_ch);
	अगर (nfc->dma_rx_ch)
		dma_release_channel(nfc->dma_rx_ch);

	sg_मुक्त_table(&nfc->dma_data_sg);
	sg_मुक्त_table(&nfc->dma_ecc_sg);

	clk_disable_unprepare(nfc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_fmc2_nfc_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = dev_get_drvdata(dev);

	clk_disable_unprepare(nfc->clk);

	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_fmc2_nfc_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_fmc2_nfc *nfc = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_fmc2_nand *nand = &nfc->nand;
	पूर्णांक chip_cs, ret;

	pinctrl_pm_select_शेष_state(dev);

	ret = clk_prepare_enable(nfc->clk);
	अगर (ret) अणु
		dev_err(dev, "can not enable the clock\n");
		वापस ret;
	पूर्ण

	sपंचांग32_fmc2_nfc_init(nfc);

	क्रम (chip_cs = 0; chip_cs < FMC2_MAX_CE; chip_cs++) अणु
		अगर (!(nfc->cs_asचिन्हित & BIT(chip_cs)))
			जारी;

		nand_reset(&nand->chip, chip_cs);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sपंचांग32_fmc2_nfc_pm_ops, sपंचांग32_fmc2_nfc_suspend,
			 sपंचांग32_fmc2_nfc_resume);

अटल स्थिर काष्ठा of_device_id sपंचांग32_fmc2_nfc_match[] = अणु
	अणु.compatible = "st,stm32mp15-fmc2"पूर्ण,
	अणु.compatible = "st,stm32mp1-fmc2-nfc"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_fmc2_nfc_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_fmc2_nfc_driver = अणु
	.probe	= sपंचांग32_fmc2_nfc_probe,
	.हटाओ	= sपंचांग32_fmc2_nfc_हटाओ,
	.driver	= अणु
		.name = "stm32_fmc2_nfc",
		.of_match_table = sपंचांग32_fmc2_nfc_match,
		.pm = &sपंचांग32_fmc2_nfc_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_fmc2_nfc_driver);

MODULE_ALIAS("platform:stm32_fmc2_nfc");
MODULE_AUTHOR("Christophe Kerello <christophe.kerello@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 FMC2 NFC driver");
MODULE_LICENSE("GPL v2");
