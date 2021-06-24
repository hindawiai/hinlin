<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/mmc/host/mmci.h - ARM PrimeCell MMCI PL180/1 driver
 *
 *  Copyright (C) 2003 Deep Blue Solutions, Ltd, All Rights Reserved.
 */
#घोषणा MMCIPOWER		0x000
#घोषणा MCI_PWR_OFF		0x00
#घोषणा MCI_PWR_UP		0x02
#घोषणा MCI_PWR_ON		0x03
#घोषणा MCI_OD			(1 << 6)
#घोषणा MCI_ROD			(1 << 7)
/*
 * The ST Micro version करोes not have ROD and reuse the voltage रेजिस्टरs क्रम
 * direction settings.
 */
#घोषणा MCI_ST_DATA2सूचीEN	(1 << 2)
#घोषणा MCI_ST_CMDसूचीEN		(1 << 3)
#घोषणा MCI_ST_DATA0सूचीEN	(1 << 4)
#घोषणा MCI_ST_DATA31सूचीEN	(1 << 5)
#घोषणा MCI_ST_FBCLKEN		(1 << 7)
#घोषणा MCI_ST_DATA74सूचीEN	(1 << 8)
/*
 * The STM32 sdmmc करोes not have PWR_UP/OD/ROD
 * and uses the घातer रेजिस्टर क्रम
 */
#घोषणा MCI_STM32_PWR_CYC	0x02
#घोषणा MCI_STM32_VSWITCH	BIT(2)
#घोषणा MCI_STM32_VSWITCHEN	BIT(3)
#घोषणा MCI_STM32_सूचीPOL	BIT(4)

#घोषणा MMCICLOCK		0x004
#घोषणा MCI_CLK_ENABLE		(1 << 8)
#घोषणा MCI_CLK_PWRSAVE		(1 << 9)
#घोषणा MCI_CLK_BYPASS		(1 << 10)
#घोषणा MCI_4BIT_BUS		(1 << 11)
/*
 * 8bit wide buses, hardware flow contronl, negative edges and घड़ी inversion
 * supported in ST Micro U300 and Ux500 versions
 */
#घोषणा MCI_ST_8BIT_BUS		(1 << 12)
#घोषणा MCI_ST_U300_HWFCEN	(1 << 13)
#घोषणा MCI_ST_UX500_NEG_EDGE	(1 << 13)
#घोषणा MCI_ST_UX500_HWFCEN	(1 << 14)
#घोषणा MCI_ST_UX500_CLK_INV	(1 << 15)
/* Modअगरied PL180 on Versatile Express platक्रमm */
#घोषणा MCI_ARM_HWFCEN		(1 << 12)

/* Modअगरied on Qualcomm Integrations */
#घोषणा MCI_QCOM_CLK_WIDEBUS_8	(BIT(10) | BIT(11))
#घोषणा MCI_QCOM_CLK_FLOWENA	BIT(12)
#घोषणा MCI_QCOM_CLK_INVERTOUT	BIT(13)

/* select in latch data and command in */
#घोषणा MCI_QCOM_CLK_SELECT_IN_FBCLK	BIT(15)
#घोषणा MCI_QCOM_CLK_SELECT_IN_DDR_MODE	(BIT(14) | BIT(15))

/* Modअगरied on STM32 sdmmc */
#घोषणा MCI_STM32_CLK_CLKDIV_MSK	GENMASK(9, 0)
#घोषणा MCI_STM32_CLK_WIDEBUS_4		BIT(14)
#घोषणा MCI_STM32_CLK_WIDEBUS_8		BIT(15)
#घोषणा MCI_STM32_CLK_NEGEDGE		BIT(16)
#घोषणा MCI_STM32_CLK_HWFCEN		BIT(17)
#घोषणा MCI_STM32_CLK_DDR		BIT(18)
#घोषणा MCI_STM32_CLK_BUSSPEED		BIT(19)
#घोषणा MCI_STM32_CLK_SEL_MSK		GENMASK(21, 20)
#घोषणा MCI_STM32_CLK_SELCK		(0 << 20)
#घोषणा MCI_STM32_CLK_SELCKIN		(1 << 20)
#घोषणा MCI_STM32_CLK_SELFBCK		(2 << 20)

#घोषणा MMCIARGUMENT		0x008

/* The command रेजिस्टर controls the Command Path State Machine (CPSM) */
#घोषणा MMCICOMMAND		0x00c
#घोषणा MCI_CPSM_RESPONSE	BIT(6)
#घोषणा MCI_CPSM_LONGRSP	BIT(7)
#घोषणा MCI_CPSM_INTERRUPT	BIT(8)
#घोषणा MCI_CPSM_PENDING	BIT(9)
#घोषणा MCI_CPSM_ENABLE		BIT(10)
/* Command रेजिस्टर flag extenstions in the ST Micro versions */
#घोषणा MCI_CPSM_ST_SDIO_SUSP		BIT(11)
#घोषणा MCI_CPSM_ST_ENCMD_COMPL		BIT(12)
#घोषणा MCI_CPSM_ST_NIEN		BIT(13)
#घोषणा MCI_CPSM_ST_CE_ATACMD		BIT(14)
/* Command रेजिस्टर flag extensions in the Qualcomm versions */
#घोषणा MCI_CPSM_QCOM_PROGENA		BIT(11)
#घोषणा MCI_CPSM_QCOM_DATCMD		BIT(12)
#घोषणा MCI_CPSM_QCOM_MCIABORT		BIT(13)
#घोषणा MCI_CPSM_QCOM_CCSENABLE		BIT(14)
#घोषणा MCI_CPSM_QCOM_CCSDISABLE	BIT(15)
#घोषणा MCI_CPSM_QCOM_AUTO_CMD19	BIT(16)
#घोषणा MCI_CPSM_QCOM_AUTO_CMD21	BIT(21)
/* Command रेजिस्टर in STM32 sdmmc versions */
#घोषणा MCI_CPSM_STM32_CMDTRANS		BIT(6)
#घोषणा MCI_CPSM_STM32_CMDSTOP		BIT(7)
#घोषणा MCI_CPSM_STM32_WAITRESP_MASK	GENMASK(9, 8)
#घोषणा MCI_CPSM_STM32_NORSP		(0 << 8)
#घोषणा MCI_CPSM_STM32_SRSP_CRC		(1 << 8)
#घोषणा MCI_CPSM_STM32_SRSP		(2 << 8)
#घोषणा MCI_CPSM_STM32_LRSP_CRC		(3 << 8)
#घोषणा MCI_CPSM_STM32_ENABLE		BIT(12)

#घोषणा MMCIRESPCMD		0x010
#घोषणा MMCIRESPONSE0		0x014
#घोषणा MMCIRESPONSE1		0x018
#घोषणा MMCIRESPONSE2		0x01c
#घोषणा MMCIRESPONSE3		0x020
#घोषणा MMCIDATATIMER		0x024
#घोषणा MMCIDATALENGTH		0x028

/* The data control रेजिस्टर controls the Data Path State Machine (DPSM) */
#घोषणा MMCIDATACTRL		0x02c
#घोषणा MCI_DPSM_ENABLE		BIT(0)
#घोषणा MCI_DPSM_सूचीECTION	BIT(1)
#घोषणा MCI_DPSM_MODE		BIT(2)
#घोषणा MCI_DPSM_DMAENABLE	BIT(3)
#घोषणा MCI_DPSM_BLOCKSIZE	BIT(4)
/* Control रेजिस्टर extensions in the ST Micro U300 and Ux500 versions */
#घोषणा MCI_DPSM_ST_RWSTART	BIT(8)
#घोषणा MCI_DPSM_ST_RWSTOP	BIT(9)
#घोषणा MCI_DPSM_ST_RWMOD	BIT(10)
#घोषणा MCI_DPSM_ST_SDIOEN	BIT(11)
/* Control रेजिस्टर extensions in the ST Micro Ux500 versions */
#घोषणा MCI_DPSM_ST_DMAREQCTL	BIT(12)
#घोषणा MCI_DPSM_ST_DBOOTMODEEN	BIT(13)
#घोषणा MCI_DPSM_ST_BUSYMODE	BIT(14)
#घोषणा MCI_DPSM_ST_DDRMODE	BIT(15)
/* Control रेजिस्टर extensions in the Qualcomm versions */
#घोषणा MCI_DPSM_QCOM_DATA_PEND	BIT(17)
#घोषणा MCI_DPSM_QCOM_RX_DATA_PEND BIT(20)
/* Control रेजिस्टर extensions in STM32 versions */
#घोषणा MCI_DPSM_STM32_MODE_BLOCK	(0 << 2)
#घोषणा MCI_DPSM_STM32_MODE_SDIO	(1 << 2)
#घोषणा MCI_DPSM_STM32_MODE_STREAM	(2 << 2)
#घोषणा MCI_DPSM_STM32_MODE_BLOCK_STOP	(3 << 2)

#घोषणा MMCIDATACNT		0x030
#घोषणा MMCISTATUS		0x034
#घोषणा MCI_CMDCRCFAIL		(1 << 0)
#घोषणा MCI_DATACRCFAIL		(1 << 1)
#घोषणा MCI_CMDTIMEOUT		(1 << 2)
#घोषणा MCI_DATATIMEOUT		(1 << 3)
#घोषणा MCI_TXUNDERRUN		(1 << 4)
#घोषणा MCI_RXOVERRUN		(1 << 5)
#घोषणा MCI_CMDRESPEND		(1 << 6)
#घोषणा MCI_CMDSENT		(1 << 7)
#घोषणा MCI_DATAEND		(1 << 8)
#घोषणा MCI_STARTBITERR		(1 << 9)
#घोषणा MCI_DATABLOCKEND	(1 << 10)
#घोषणा MCI_CMDACTIVE		(1 << 11)
#घोषणा MCI_TXACTIVE		(1 << 12)
#घोषणा MCI_RXACTIVE		(1 << 13)
#घोषणा MCI_TXFIFOHALFEMPTY	(1 << 14)
#घोषणा MCI_RXFIFOHALFFULL	(1 << 15)
#घोषणा MCI_TXFIFOFULL		(1 << 16)
#घोषणा MCI_RXFIFOFULL		(1 << 17)
#घोषणा MCI_TXFIFOEMPTY		(1 << 18)
#घोषणा MCI_RXFIFOEMPTY		(1 << 19)
#घोषणा MCI_TXDATAAVLBL		(1 << 20)
#घोषणा MCI_RXDATAAVLBL		(1 << 21)
/* Extended status bits क्रम the ST Micro variants */
#घोषणा MCI_ST_SDIOIT		(1 << 22)
#घोषणा MCI_ST_CEATAEND		(1 << 23)
#घोषणा MCI_ST_CARDBUSY		(1 << 24)
/* Extended status bits क्रम the STM32 variants */
#घोषणा MCI_STM32_BUSYD0	BIT(20)
#घोषणा MCI_STM32_BUSYD0END	BIT(21)
#घोषणा MCI_STM32_VSWEND	BIT(25)

#घोषणा MMCICLEAR		0x038
#घोषणा MCI_CMDCRCFAILCLR	(1 << 0)
#घोषणा MCI_DATACRCFAILCLR	(1 << 1)
#घोषणा MCI_CMDTIMEOUTCLR	(1 << 2)
#घोषणा MCI_DATATIMEOUTCLR	(1 << 3)
#घोषणा MCI_TXUNDERRUNCLR	(1 << 4)
#घोषणा MCI_RXOVERRUNCLR	(1 << 5)
#घोषणा MCI_CMDRESPENDCLR	(1 << 6)
#घोषणा MCI_CMDSENTCLR		(1 << 7)
#घोषणा MCI_DATAENDCLR		(1 << 8)
#घोषणा MCI_STARTBITERRCLR	(1 << 9)
#घोषणा MCI_DATABLOCKENDCLR	(1 << 10)
/* Extended status bits क्रम the ST Micro variants */
#घोषणा MCI_ST_SDIOITC		(1 << 22)
#घोषणा MCI_ST_CEATAENDC	(1 << 23)
#घोषणा MCI_ST_BUSYENDC		(1 << 24)
/* Extended clear bits क्रम the STM32 variants */
#घोषणा MCI_STM32_VSWENDC	BIT(25)
#घोषणा MCI_STM32_CKSTOPC	BIT(26)

#घोषणा MMCIMASK0		0x03c
#घोषणा MCI_CMDCRCFAILMASK	(1 << 0)
#घोषणा MCI_DATACRCFAILMASK	(1 << 1)
#घोषणा MCI_CMDTIMEOUTMASK	(1 << 2)
#घोषणा MCI_DATATIMEOUTMASK	(1 << 3)
#घोषणा MCI_TXUNDERRUNMASK	(1 << 4)
#घोषणा MCI_RXOVERRUNMASK	(1 << 5)
#घोषणा MCI_CMDRESPENDMASK	(1 << 6)
#घोषणा MCI_CMDSENTMASK		(1 << 7)
#घोषणा MCI_DATAENDMASK		(1 << 8)
#घोषणा MCI_STARTBITERRMASK	(1 << 9)
#घोषणा MCI_DATABLOCKENDMASK	(1 << 10)
#घोषणा MCI_CMDACTIVEMASK	(1 << 11)
#घोषणा MCI_TXACTIVEMASK	(1 << 12)
#घोषणा MCI_RXACTIVEMASK	(1 << 13)
#घोषणा MCI_TXFIFOHALFEMPTYMASK	(1 << 14)
#घोषणा MCI_RXFIFOHALFFULLMASK	(1 << 15)
#घोषणा MCI_TXFIFOFULLMASK	(1 << 16)
#घोषणा MCI_RXFIFOFULLMASK	(1 << 17)
#घोषणा MCI_TXFIFOEMPTYMASK	(1 << 18)
#घोषणा MCI_RXFIFOEMPTYMASK	(1 << 19)
#घोषणा MCI_TXDATAAVLBLMASK	(1 << 20)
#घोषणा MCI_RXDATAAVLBLMASK	(1 << 21)
/* Extended status bits क्रम the ST Micro variants */
#घोषणा MCI_ST_SDIOITMASK	(1 << 22)
#घोषणा MCI_ST_CEATAENDMASK	(1 << 23)
#घोषणा MCI_ST_BUSYENDMASK	(1 << 24)
/* Extended status bits क्रम the STM32 variants */
#घोषणा MCI_STM32_BUSYD0ENDMASK	BIT(21)

#घोषणा MMCIMASK1		0x040
#घोषणा MMCIFIFOCNT		0x048
#घोषणा MMCIFIFO		0x080 /* to 0x0bc */

/* STM32 sdmmc रेजिस्टरs क्रम IDMA (Internal DMA) */
#घोषणा MMCI_STM32_IDMACTRLR	0x050
#घोषणा MMCI_STM32_IDMAEN	BIT(0)
#घोषणा MMCI_STM32_IDMALLIEN	BIT(1)

#घोषणा MMCI_STM32_IDMABSIZER		0x054
#घोषणा MMCI_STM32_IDMABNDT_SHIFT	5
#घोषणा MMCI_STM32_IDMABNDT_MASK	GENMASK(12, 5)

#घोषणा MMCI_STM32_IDMABASE0R	0x058

#घोषणा MMCI_STM32_IDMALAR	0x64
#घोषणा MMCI_STM32_IDMALA_MASK	GENMASK(13, 0)
#घोषणा MMCI_STM32_ABR		BIT(29)
#घोषणा MMCI_STM32_ULS		BIT(30)
#घोषणा MMCI_STM32_ULA		BIT(31)

#घोषणा MMCI_STM32_IDMABAR	0x68

#घोषणा MCI_IRQENABLE	\
	(MCI_CMDCRCFAILMASK | MCI_DATACRCFAILMASK | MCI_CMDTIMEOUTMASK | \
	MCI_DATATIMEOUTMASK | MCI_TXUNDERRUNMASK | MCI_RXOVERRUNMASK |	\
	MCI_CMDRESPENDMASK | MCI_CMDSENTMASK)

/* These पूर्णांकerrupts are directed to IRQ1 when two IRQ lines are available */
#घोषणा MCI_IRQ_PIO_MASK \
	(MCI_RXFIFOHALFFULLMASK | MCI_RXDATAAVLBLMASK | \
	 MCI_TXFIFOHALFEMPTYMASK)

#घोषणा MCI_IRQ_PIO_STM32_MASK \
	(MCI_RXFIFOHALFFULLMASK | MCI_TXFIFOHALFEMPTYMASK)

#घोषणा NR_SG		128

#घोषणा MMCI_PINCTRL_STATE_OPENDRAIN "opendrain"

काष्ठा clk;
काष्ठा dma_chan;
काष्ठा mmci_host;

/**
 * काष्ठा variant_data - MMCI variant-specअगरic quirks
 * @clkreg: शेष value क्रम MCICLOCK रेजिस्टर
 * @clkreg_enable: enable value क्रम MMCICLOCK रेजिस्टर
 * @clkreg_8bit_bus_enable: enable value क्रम 8 bit bus
 * @clkreg_neg_edge_enable: enable value क्रम inverted data/cmd output
 * @cmdreg_cpsm_enable: enable value क्रम CPSM
 * @cmdreg_lrsp_crc: enable value क्रम दीर्घ response with crc
 * @cmdreg_srsp_crc: enable value क्रम लघु response with crc
 * @cmdreg_srsp: enable value क्रम लघु response without crc
 * @cmdreg_stop: enable value क्रम stop and पात transmission
 * @datalength_bits: number of bits in the MMCIDATALENGTH रेजिस्टर
 * @fअगरosize: number of bytes that can be written when MMCI_TXFIFOEMPTY
 *	      is निश्चितed (likewise क्रम RX)
 * @fअगरohalfsize: number of bytes that can be written when MCI_TXFIFOHALFEMPTY
 *		  is निश्चितed (likewise क्रम RX)
 * @data_cmd_enable: enable value क्रम data commands.
 * @st_sdio: enable ST specअगरic SDIO logic
 * @st_clkभाग: true अगर using a ST-specअगरic घड़ी भागider algorithm
 * @sपंचांग32_clkभाग: true अगर using a STM32-specअगरic घड़ी भागider algorithm
 * @datactrl_mask_ddrmode: ddr mode mask in datactrl रेजिस्टर.
 * @datactrl_mask_sdio: SDIO enable mask in datactrl रेजिस्टर
 * @datactrl_blocksz: block size in घातer of two
 * @datactrl_any_blocksz: true अगर block any block sizes are accepted by
 *		  hardware, such as with some SDIO traffic that send
 *		  odd packets.
 * @dma_घातer_of_2: DMA only works with blocks that are a घातer of 2.
 * @datactrl_first: true अगर data must be setup beक्रमe send command
 * @datacnt_useless: true अगर you could not use datacnt रेजिस्टर to पढ़ो
 *		     reमुख्यing data
 * @pwrreg_घातerup: घातer up value क्रम MMCIPOWER रेजिस्टर
 * @f_max: maximum clk frequency supported by the controller.
 * @संकेत_direction: input/out direction of bus संकेतs can be indicated
 * @pwrreg_clkgate: MMCIPOWER रेजिस्टर must be used to gate the घड़ी
 * @busy_detect: true अगर the variant supports busy detection on DAT0.
 * @busy_समयout: true अगर the variant starts data समयr when the DPSM
 *		  enter in Wait_R or Busy state.
 * @busy_dpsm_flag: biपंचांगask enabling busy detection in the DPSM
 * @busy_detect_flag: biपंचांगask identअगरying the bit in the MMCISTATUS रेजिस्टर
 *		      indicating that the card is busy
 * @busy_detect_mask: biपंचांगask identअगरying the bit in the MMCIMASK0 to mask क्रम
 *		      getting busy end detection पूर्णांकerrupts
 * @pwrreg_noघातer: bits in MMCIPOWER करोn't controls ext. घातer supply
 * @explicit_mclk_control: enable explicit mclk control in driver.
 * @qcom_fअगरo: enables qcom specअगरic fअगरo pio पढ़ो logic.
 * @qcom_dml: enables qcom specअगरic dma glue क्रम dma transfers.
 * @reversed_irq_handling: handle data irq beक्रमe cmd irq.
 * @mmcimask1: true अगर variant have a MMCIMASK1 रेजिस्टर.
 * @irq_pio_mask: biपंचांगask used to manage पूर्णांकerrupt pio transfert in mmcimask
 *		  रेजिस्टर
 * @start_err: biपंचांगask identअगरying the STARTBITERR bit inside MMCISTATUS
 *	       रेजिस्टर.
 * @खोलोdrain: biपंचांगask identअगरying the OPENDRAIN bit inside MMCIPOWER रेजिस्टर
 * @dma_lli: true अगर variant has dma link list feature.
 * @sपंचांग32_idmअसलize_mask: sपंचांग32 sdmmc idma buffer size.
 */
काष्ठा variant_data अणु
	अचिन्हित पूर्णांक		clkreg;
	अचिन्हित पूर्णांक		clkreg_enable;
	अचिन्हित पूर्णांक		clkreg_8bit_bus_enable;
	अचिन्हित पूर्णांक		clkreg_neg_edge_enable;
	अचिन्हित पूर्णांक		cmdreg_cpsm_enable;
	अचिन्हित पूर्णांक		cmdreg_lrsp_crc;
	अचिन्हित पूर्णांक		cmdreg_srsp_crc;
	अचिन्हित पूर्णांक		cmdreg_srsp;
	अचिन्हित पूर्णांक		cmdreg_stop;
	अचिन्हित पूर्णांक		datalength_bits;
	अचिन्हित पूर्णांक		fअगरosize;
	अचिन्हित पूर्णांक		fअगरohalfsize;
	अचिन्हित पूर्णांक		data_cmd_enable;
	अचिन्हित पूर्णांक		datactrl_mask_ddrmode;
	अचिन्हित पूर्णांक		datactrl_mask_sdio;
	अचिन्हित पूर्णांक		datactrl_blocksz;
	u8			datactrl_any_blocksz:1;
	u8			dma_घातer_of_2:1;
	u8			datactrl_first:1;
	u8			datacnt_useless:1;
	u8			st_sdio:1;
	u8			st_clkभाग:1;
	u8			sपंचांग32_clkभाग:1;
	u32			pwrreg_घातerup;
	u32			f_max;
	u8			संकेत_direction:1;
	u8			pwrreg_clkgate:1;
	u8			busy_detect:1;
	u8			busy_समयout:1;
	u32			busy_dpsm_flag;
	u32			busy_detect_flag;
	u32			busy_detect_mask;
	u8			pwrreg_noघातer:1;
	u8			explicit_mclk_control:1;
	u8			qcom_fअगरo:1;
	u8			qcom_dml:1;
	u8			reversed_irq_handling:1;
	u8			mmcimask1:1;
	अचिन्हित पूर्णांक		irq_pio_mask;
	u32			start_err;
	u32			खोलोdrain;
	u8			dma_lli:1;
	u32			sपंचांग32_idmअसलize_mask;
	व्योम (*init)(काष्ठा mmci_host *host);
पूर्ण;

/* mmci variant callbacks */
काष्ठा mmci_host_ops अणु
	पूर्णांक (*validate_data)(काष्ठा mmci_host *host, काष्ठा mmc_data *data);
	पूर्णांक (*prep_data)(काष्ठा mmci_host *host, काष्ठा mmc_data *data,
			 bool next);
	व्योम (*unprep_data)(काष्ठा mmci_host *host, काष्ठा mmc_data *data,
			    पूर्णांक err);
	u32 (*get_datactrl_cfg)(काष्ठा mmci_host *host);
	व्योम (*get_next_data)(काष्ठा mmci_host *host, काष्ठा mmc_data *data);
	पूर्णांक (*dma_setup)(काष्ठा mmci_host *host);
	व्योम (*dma_release)(काष्ठा mmci_host *host);
	पूर्णांक (*dma_start)(काष्ठा mmci_host *host, अचिन्हित पूर्णांक *datactrl);
	व्योम (*dma_finalize)(काष्ठा mmci_host *host, काष्ठा mmc_data *data);
	व्योम (*dma_error)(काष्ठा mmci_host *host);
	व्योम (*set_clkreg)(काष्ठा mmci_host *host, अचिन्हित पूर्णांक desired);
	व्योम (*set_pwrreg)(काष्ठा mmci_host *host, अचिन्हित पूर्णांक pwr);
	bool (*busy_complete)(काष्ठा mmci_host *host, u32 status, u32 err_msk);
	व्योम (*pre_sig_volt_चयन)(काष्ठा mmci_host *host);
	पूर्णांक (*post_sig_volt_चयन)(काष्ठा mmci_host *host, काष्ठा mmc_ios *ios);
पूर्ण;

काष्ठा mmci_host अणु
	phys_addr_t		phybase;
	व्योम __iomem		*base;
	काष्ठा mmc_request	*mrq;
	काष्ठा mmc_command	*cmd;
	काष्ठा mmc_command	stop_पात;
	काष्ठा mmc_data		*data;
	काष्ठा mmc_host		*mmc;
	काष्ठा clk		*clk;
	u8			singleirq:1;

	काष्ठा reset_control	*rst;

	spinlock_t		lock;

	अचिन्हित पूर्णांक		mclk;
	/* cached value of requested clk in set_ios */
	अचिन्हित पूर्णांक		घड़ी_cache;
	अचिन्हित पूर्णांक		cclk;
	u32			pwr_reg;
	u32			pwr_reg_add;
	u32			clk_reg;
	u32			clk_reg_add;
	u32			datactrl_reg;
	u32			busy_status;
	u32			mask1_reg;
	u8			vqmmc_enabled:1;
	काष्ठा mmci_platक्रमm_data *plat;
	काष्ठा mmc_host_ops	*mmc_ops;
	काष्ठा mmci_host_ops	*ops;
	काष्ठा variant_data	*variant;
	व्योम			*variant_priv;
	काष्ठा pinctrl		*pinctrl;
	काष्ठा pinctrl_state	*pins_खोलोdrain;

	u8			hw_designer;
	u8			hw_revision:4;

	काष्ठा समयr_list	समयr;
	अचिन्हित पूर्णांक		oldstat;
	u32			irq_action;

	/* pio stuff */
	काष्ठा sg_mapping_iter	sg_miter;
	अचिन्हित पूर्णांक		size;
	पूर्णांक (*get_rx_fअगरocnt)(काष्ठा mmci_host *h, u32 status, पूर्णांक reमुख्य);

	u8			use_dma:1;
	u8			dma_in_progress:1;
	व्योम			*dma_priv;

	s32			next_cookie;
पूर्ण;

#घोषणा dma_inprogress(host)	((host)->dma_in_progress)

व्योम mmci_ग_लिखो_clkreg(काष्ठा mmci_host *host, u32 clk);
व्योम mmci_ग_लिखो_pwrreg(काष्ठा mmci_host *host, u32 pwr);

अटल अंतरभूत u32 mmci_dctrl_blksz(काष्ठा mmci_host *host)
अणु
	वापस (ffs(host->data->blksz) - 1) << 4;
पूर्ण

#अगर_घोषित CONFIG_DMA_ENGINE
पूर्णांक mmci_dmae_prep_data(काष्ठा mmci_host *host, काष्ठा mmc_data *data,
			bool next);
व्योम mmci_dmae_unprep_data(काष्ठा mmci_host *host, काष्ठा mmc_data *data,
			   पूर्णांक err);
व्योम mmci_dmae_get_next_data(काष्ठा mmci_host *host, काष्ठा mmc_data *data);
पूर्णांक mmci_dmae_setup(काष्ठा mmci_host *host);
व्योम mmci_dmae_release(काष्ठा mmci_host *host);
पूर्णांक mmci_dmae_start(काष्ठा mmci_host *host, अचिन्हित पूर्णांक *datactrl);
व्योम mmci_dmae_finalize(काष्ठा mmci_host *host, काष्ठा mmc_data *data);
व्योम mmci_dmae_error(काष्ठा mmci_host *host);
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMC_QCOM_DML
व्योम qcom_variant_init(काष्ठा mmci_host *host);
#अन्यथा
अटल अंतरभूत व्योम qcom_variant_init(काष्ठा mmci_host *host) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMC_STM32_SDMMC
व्योम sdmmc_variant_init(काष्ठा mmci_host *host);
#अन्यथा
अटल अंतरभूत व्योम sdmmc_variant_init(काष्ठा mmci_host *host) अणुपूर्ण
#पूर्ण_अगर
