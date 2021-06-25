<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __INCLUDE_ATMEL_SSC_H
#घोषणा __INCLUDE_ATMEL_SSC_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>

काष्ठा aपंचांगel_ssc_platक्रमm_data अणु
	पूर्णांक			use_dma;
	पूर्णांक			has_fslen_ext;
पूर्ण;

काष्ठा ssc_device अणु
	काष्ठा list_head	list;
	dma_addr_t		phybase;
	व्योम __iomem		*regs;
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा aपंचांगel_ssc_platक्रमm_data *pdata;
	काष्ठा clk		*clk;
	पूर्णांक			user;
	पूर्णांक			irq;
	bool			clk_from_rk_pin;
	bool			sound_dai;
पूर्ण;

काष्ठा ssc_device * __must_check ssc_request(अचिन्हित पूर्णांक ssc_num);
व्योम ssc_मुक्त(काष्ठा ssc_device *ssc);

/* SSC रेजिस्टर offsets */

/* SSC Control Register */
#घोषणा SSC_CR				0x00000000
#घोषणा SSC_CR_RXDIS_SIZE			 1
#घोषणा SSC_CR_RXDIS_OFFSET			 1
#घोषणा SSC_CR_RXEN_SIZE			 1
#घोषणा SSC_CR_RXEN_OFFSET			 0
#घोषणा SSC_CR_SWRST_SIZE			 1
#घोषणा SSC_CR_SWRST_OFFSET			15
#घोषणा SSC_CR_TXDIS_SIZE			 1
#घोषणा SSC_CR_TXDIS_OFFSET			 9
#घोषणा SSC_CR_TXEN_SIZE			 1
#घोषणा SSC_CR_TXEN_OFFSET			 8

/* SSC Clock Mode Register */
#घोषणा SSC_CMR				0x00000004
#घोषणा SSC_CMR_DIV_SIZE			12
#घोषणा SSC_CMR_DIV_OFFSET			 0

/* SSC Receive Clock Mode Register */
#घोषणा SSC_RCMR			0x00000010
#घोषणा SSC_RCMR_CKG_SIZE			 2
#घोषणा SSC_RCMR_CKG_OFFSET			 6
#घोषणा SSC_RCMR_CKI_SIZE			 1
#घोषणा SSC_RCMR_CKI_OFFSET			 5
#घोषणा SSC_RCMR_CKO_SIZE			 3
#घोषणा SSC_RCMR_CKO_OFFSET			 2
#घोषणा SSC_RCMR_CKS_SIZE			 2
#घोषणा SSC_RCMR_CKS_OFFSET			 0
#घोषणा SSC_RCMR_PERIOD_SIZE			 8
#घोषणा SSC_RCMR_PERIOD_OFFSET			24
#घोषणा SSC_RCMR_START_SIZE			 4
#घोषणा SSC_RCMR_START_OFFSET			 8
#घोषणा SSC_RCMR_STOP_SIZE			 1
#घोषणा SSC_RCMR_STOP_OFFSET			12
#घोषणा SSC_RCMR_STTDLY_SIZE			 8
#घोषणा SSC_RCMR_STTDLY_OFFSET			16

/* SSC Receive Frame Mode Register */
#घोषणा SSC_RFMR			0x00000014
#घोषणा SSC_RFMR_DATLEN_SIZE			 5
#घोषणा SSC_RFMR_DATLEN_OFFSET			 0
#घोषणा SSC_RFMR_DATNB_SIZE			 4
#घोषणा SSC_RFMR_DATNB_OFFSET			 8
#घोषणा SSC_RFMR_FSEDGE_SIZE			 1
#घोषणा SSC_RFMR_FSEDGE_OFFSET			24
/*
 * The FSLEN_EXT exist on at91sam9rl, at91sam9g10,
 * at91sam9g20, and at91sam9g45 and newer SoCs
 */
#घोषणा SSC_RFMR_FSLEN_EXT_SIZE			 4
#घोषणा SSC_RFMR_FSLEN_EXT_OFFSET		28
#घोषणा SSC_RFMR_FSLEN_SIZE			 4
#घोषणा SSC_RFMR_FSLEN_OFFSET			16
#घोषणा SSC_RFMR_FSOS_SIZE			 4
#घोषणा SSC_RFMR_FSOS_OFFSET			20
#घोषणा SSC_RFMR_LOOP_SIZE			 1
#घोषणा SSC_RFMR_LOOP_OFFSET			 5
#घोषणा SSC_RFMR_MSBF_SIZE			 1
#घोषणा SSC_RFMR_MSBF_OFFSET			 7

/* SSC Transmit Clock Mode Register */
#घोषणा SSC_TCMR			0x00000018
#घोषणा SSC_TCMR_CKG_SIZE			 2
#घोषणा SSC_TCMR_CKG_OFFSET			 6
#घोषणा SSC_TCMR_CKI_SIZE			 1
#घोषणा SSC_TCMR_CKI_OFFSET			 5
#घोषणा SSC_TCMR_CKO_SIZE			 3
#घोषणा SSC_TCMR_CKO_OFFSET			 2
#घोषणा SSC_TCMR_CKS_SIZE			 2
#घोषणा SSC_TCMR_CKS_OFFSET			 0
#घोषणा SSC_TCMR_PERIOD_SIZE			 8
#घोषणा SSC_TCMR_PERIOD_OFFSET			24
#घोषणा SSC_TCMR_START_SIZE			 4
#घोषणा SSC_TCMR_START_OFFSET			 8
#घोषणा SSC_TCMR_STTDLY_SIZE			 8
#घोषणा SSC_TCMR_STTDLY_OFFSET			16

/* SSC Transmit Frame Mode Register */
#घोषणा SSC_TFMR			0x0000001c
#घोषणा SSC_TFMR_DATDEF_SIZE			 1
#घोषणा SSC_TFMR_DATDEF_OFFSET			 5
#घोषणा SSC_TFMR_DATLEN_SIZE			 5
#घोषणा SSC_TFMR_DATLEN_OFFSET			 0
#घोषणा SSC_TFMR_DATNB_SIZE			 4
#घोषणा SSC_TFMR_DATNB_OFFSET			 8
#घोषणा SSC_TFMR_FSDEN_SIZE			 1
#घोषणा SSC_TFMR_FSDEN_OFFSET			23
#घोषणा SSC_TFMR_FSEDGE_SIZE			 1
#घोषणा SSC_TFMR_FSEDGE_OFFSET			24
/*
 * The FSLEN_EXT exist on at91sam9rl, at91sam9g10,
 * at91sam9g20, and at91sam9g45 and newer SoCs
 */
#घोषणा SSC_TFMR_FSLEN_EXT_SIZE			 4
#घोषणा SSC_TFMR_FSLEN_EXT_OFFSET		28
#घोषणा SSC_TFMR_FSLEN_SIZE			 4
#घोषणा SSC_TFMR_FSLEN_OFFSET			16
#घोषणा SSC_TFMR_FSOS_SIZE			 3
#घोषणा SSC_TFMR_FSOS_OFFSET			20
#घोषणा SSC_TFMR_MSBF_SIZE			 1
#घोषणा SSC_TFMR_MSBF_OFFSET			 7

/* SSC Receive Hold Register */
#घोषणा SSC_RHR				0x00000020
#घोषणा SSC_RHR_RDAT_SIZE			32
#घोषणा SSC_RHR_RDAT_OFFSET			 0

/* SSC Transmit Hold Register */
#घोषणा SSC_THR				0x00000024
#घोषणा SSC_THR_TDAT_SIZE			32
#घोषणा SSC_THR_TDAT_OFFSET			 0

/* SSC Receive Sync. Holding Register */
#घोषणा SSC_RSHR			0x00000030
#घोषणा SSC_RSHR_RSDAT_SIZE			16
#घोषणा SSC_RSHR_RSDAT_OFFSET			 0

/* SSC Transmit Sync. Holding Register */
#घोषणा SSC_TSHR			0x00000034
#घोषणा SSC_TSHR_TSDAT_SIZE			16
#घोषणा SSC_TSHR_RSDAT_OFFSET			 0

/* SSC Receive Compare 0 Register */
#घोषणा SSC_RC0R			0x00000038
#घोषणा SSC_RC0R_CP0_SIZE			16
#घोषणा SSC_RC0R_CP0_OFFSET			 0

/* SSC Receive Compare 1 Register */
#घोषणा SSC_RC1R			0x0000003c
#घोषणा SSC_RC1R_CP1_SIZE			16
#घोषणा SSC_RC1R_CP1_OFFSET			 0

/* SSC Status Register */
#घोषणा SSC_SR				0x00000040
#घोषणा SSC_SR_CP0_SIZE				 1
#घोषणा SSC_SR_CP0_OFFSET			 8
#घोषणा SSC_SR_CP1_SIZE				 1
#घोषणा SSC_SR_CP1_OFFSET			 9
#घोषणा SSC_SR_ENDRX_SIZE			 1
#घोषणा SSC_SR_ENDRX_OFFSET			 6
#घोषणा SSC_SR_ENDTX_SIZE			 1
#घोषणा SSC_SR_ENDTX_OFFSET			 2
#घोषणा SSC_SR_OVRUN_SIZE			 1
#घोषणा SSC_SR_OVRUN_OFFSET			 5
#घोषणा SSC_SR_RXBUFF_SIZE			 1
#घोषणा SSC_SR_RXBUFF_OFFSET			 7
#घोषणा SSC_SR_RXEN_SIZE			 1
#घोषणा SSC_SR_RXEN_OFFSET			17
#घोषणा SSC_SR_RXRDY_SIZE			 1
#घोषणा SSC_SR_RXRDY_OFFSET			 4
#घोषणा SSC_SR_RXSYN_SIZE			 1
#घोषणा SSC_SR_RXSYN_OFFSET			11
#घोषणा SSC_SR_TXBUFE_SIZE			 1
#घोषणा SSC_SR_TXBUFE_OFFSET			 3
#घोषणा SSC_SR_TXEMPTY_SIZE			 1
#घोषणा SSC_SR_TXEMPTY_OFFSET			 1
#घोषणा SSC_SR_TXEN_SIZE			 1
#घोषणा SSC_SR_TXEN_OFFSET			16
#घोषणा SSC_SR_TXRDY_SIZE			 1
#घोषणा SSC_SR_TXRDY_OFFSET			 0
#घोषणा SSC_SR_TXSYN_SIZE			 1
#घोषणा SSC_SR_TXSYN_OFFSET			10

/* SSC Interrupt Enable Register */
#घोषणा SSC_IER				0x00000044
#घोषणा SSC_IER_CP0_SIZE			 1
#घोषणा SSC_IER_CP0_OFFSET			 8
#घोषणा SSC_IER_CP1_SIZE			 1
#घोषणा SSC_IER_CP1_OFFSET			 9
#घोषणा SSC_IER_ENDRX_SIZE			 1
#घोषणा SSC_IER_ENDRX_OFFSET			 6
#घोषणा SSC_IER_ENDTX_SIZE			 1
#घोषणा SSC_IER_ENDTX_OFFSET			 2
#घोषणा SSC_IER_OVRUN_SIZE			 1
#घोषणा SSC_IER_OVRUN_OFFSET			 5
#घोषणा SSC_IER_RXBUFF_SIZE			 1
#घोषणा SSC_IER_RXBUFF_OFFSET			 7
#घोषणा SSC_IER_RXRDY_SIZE			 1
#घोषणा SSC_IER_RXRDY_OFFSET			 4
#घोषणा SSC_IER_RXSYN_SIZE			 1
#घोषणा SSC_IER_RXSYN_OFFSET			11
#घोषणा SSC_IER_TXBUFE_SIZE			 1
#घोषणा SSC_IER_TXBUFE_OFFSET			 3
#घोषणा SSC_IER_TXEMPTY_SIZE			 1
#घोषणा SSC_IER_TXEMPTY_OFFSET			 1
#घोषणा SSC_IER_TXRDY_SIZE			 1
#घोषणा SSC_IER_TXRDY_OFFSET			 0
#घोषणा SSC_IER_TXSYN_SIZE			 1
#घोषणा SSC_IER_TXSYN_OFFSET			10

/* SSC Interrupt Disable Register */
#घोषणा SSC_IDR				0x00000048
#घोषणा SSC_IDR_CP0_SIZE			 1
#घोषणा SSC_IDR_CP0_OFFSET			 8
#घोषणा SSC_IDR_CP1_SIZE			 1
#घोषणा SSC_IDR_CP1_OFFSET			 9
#घोषणा SSC_IDR_ENDRX_SIZE			 1
#घोषणा SSC_IDR_ENDRX_OFFSET			 6
#घोषणा SSC_IDR_ENDTX_SIZE			 1
#घोषणा SSC_IDR_ENDTX_OFFSET			 2
#घोषणा SSC_IDR_OVRUN_SIZE			 1
#घोषणा SSC_IDR_OVRUN_OFFSET			 5
#घोषणा SSC_IDR_RXBUFF_SIZE			 1
#घोषणा SSC_IDR_RXBUFF_OFFSET			 7
#घोषणा SSC_IDR_RXRDY_SIZE			 1
#घोषणा SSC_IDR_RXRDY_OFFSET			 4
#घोषणा SSC_IDR_RXSYN_SIZE			 1
#घोषणा SSC_IDR_RXSYN_OFFSET			11
#घोषणा SSC_IDR_TXBUFE_SIZE			 1
#घोषणा SSC_IDR_TXBUFE_OFFSET			 3
#घोषणा SSC_IDR_TXEMPTY_SIZE			 1
#घोषणा SSC_IDR_TXEMPTY_OFFSET			 1
#घोषणा SSC_IDR_TXRDY_SIZE			 1
#घोषणा SSC_IDR_TXRDY_OFFSET			 0
#घोषणा SSC_IDR_TXSYN_SIZE			 1
#घोषणा SSC_IDR_TXSYN_OFFSET			10

/* SSC Interrupt Mask Register */
#घोषणा SSC_IMR				0x0000004c
#घोषणा SSC_IMR_CP0_SIZE			 1
#घोषणा SSC_IMR_CP0_OFFSET			 8
#घोषणा SSC_IMR_CP1_SIZE			 1
#घोषणा SSC_IMR_CP1_OFFSET			 9
#घोषणा SSC_IMR_ENDRX_SIZE			 1
#घोषणा SSC_IMR_ENDRX_OFFSET			 6
#घोषणा SSC_IMR_ENDTX_SIZE			 1
#घोषणा SSC_IMR_ENDTX_OFFSET			 2
#घोषणा SSC_IMR_OVRUN_SIZE			 1
#घोषणा SSC_IMR_OVRUN_OFFSET			 5
#घोषणा SSC_IMR_RXBUFF_SIZE			 1
#घोषणा SSC_IMR_RXBUFF_OFFSET			 7
#घोषणा SSC_IMR_RXRDY_SIZE			 1
#घोषणा SSC_IMR_RXRDY_OFFSET			 4
#घोषणा SSC_IMR_RXSYN_SIZE			 1
#घोषणा SSC_IMR_RXSYN_OFFSET			11
#घोषणा SSC_IMR_TXBUFE_SIZE			 1
#घोषणा SSC_IMR_TXBUFE_OFFSET			 3
#घोषणा SSC_IMR_TXEMPTY_SIZE			 1
#घोषणा SSC_IMR_TXEMPTY_OFFSET			 1
#घोषणा SSC_IMR_TXRDY_SIZE			 1
#घोषणा SSC_IMR_TXRDY_OFFSET			 0
#घोषणा SSC_IMR_TXSYN_SIZE			 1
#घोषणा SSC_IMR_TXSYN_OFFSET			10

/* SSC PDC Receive Poपूर्णांकer Register */
#घोषणा SSC_PDC_RPR			0x00000100

/* SSC PDC Receive Counter Register */
#घोषणा SSC_PDC_RCR			0x00000104

/* SSC PDC Transmit Poपूर्णांकer Register */
#घोषणा SSC_PDC_TPR			0x00000108

/* SSC PDC Receive Next Poपूर्णांकer Register */
#घोषणा SSC_PDC_RNPR			0x00000110

/* SSC PDC Receive Next Counter Register */
#घोषणा SSC_PDC_RNCR			0x00000114

/* SSC PDC Transmit Counter Register */
#घोषणा SSC_PDC_TCR			0x0000010c

/* SSC PDC Transmit Next Poपूर्णांकer Register */
#घोषणा SSC_PDC_TNPR			0x00000118

/* SSC PDC Transmit Next Counter Register */
#घोषणा SSC_PDC_TNCR			0x0000011c

/* SSC PDC Transfer Control Register */
#घोषणा SSC_PDC_PTCR			0x00000120
#घोषणा SSC_PDC_PTCR_RXTDIS_SIZE		 1
#घोषणा SSC_PDC_PTCR_RXTDIS_OFFSET		 1
#घोषणा SSC_PDC_PTCR_RXTEN_SIZE			 1
#घोषणा SSC_PDC_PTCR_RXTEN_OFFSET		 0
#घोषणा SSC_PDC_PTCR_TXTDIS_SIZE		 1
#घोषणा SSC_PDC_PTCR_TXTDIS_OFFSET		 9
#घोषणा SSC_PDC_PTCR_TXTEN_SIZE			 1
#घोषणा SSC_PDC_PTCR_TXTEN_OFFSET		 8

/* SSC PDC Transfer Status Register */
#घोषणा SSC_PDC_PTSR			0x00000124
#घोषणा SSC_PDC_PTSR_RXTEN_SIZE			 1
#घोषणा SSC_PDC_PTSR_RXTEN_OFFSET		 0
#घोषणा SSC_PDC_PTSR_TXTEN_SIZE			 1
#घोषणा SSC_PDC_PTSR_TXTEN_OFFSET		 8

/* Bit manipulation macros */
#घोषणा SSC_BIT(name)					\
	(1 << SSC_##name##_OFFSET)
#घोषणा SSC_BF(name, value)				\
	(((value) & ((1 << SSC_##name##_SIZE) - 1))	\
	 << SSC_##name##_OFFSET)
#घोषणा SSC_BFEXT(name, value)				\
	(((value) >> SSC_##name##_OFFSET)		\
	 & ((1 << SSC_##name##_SIZE) - 1))
#घोषणा SSC_BFINS(name, value, old)			\
	(((old) & ~(((1 << SSC_##name##_SIZE) - 1)	\
	<< SSC_##name##_OFFSET)) | SSC_BF(name, value))

/* Register access macros */
#घोषणा ssc_पढ़ोl(base, reg)		__raw_पढ़ोl(base + SSC_##reg)
#घोषणा ssc_ग_लिखोl(base, reg, value)	__raw_ग_लिखोl((value), base + SSC_##reg)

#पूर्ण_अगर /* __INCLUDE_ATMEL_SSC_H */
