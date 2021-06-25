<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MPC8xx Communication Processor Module.
 * Copyright (c) 1997 Dan Malek (dmalek@jlc.net)
 *
 * This file contains काष्ठाures and inक्रमmation क्रम the communication
 * processor channels.  Some CPM control and status is available
 * through the MPC8xx पूर्णांकernal memory map.  See immap.h क्रम details.
 * This file only contains what I need क्रम the moment, not the total
 * CPM capabilities.  I (or someone अन्यथा) will add definitions as they
 * are needed.  -- Dan
 *
 * On the MBX board, EPPC-Bug loads CPM microcode पूर्णांकo the first 512
 * bytes of the DP RAM and relocates the I2C parameter area to the
 * IDMA1 space.  The reमुख्यing DP RAM is available क्रम buffer descriptors
 * or other use.
 */
#अगर_अघोषित __CPM1__
#घोषणा __CPM1__

#समावेश <linux/init.h>
#समावेश <यंत्र/8xx_immap.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/cpm.h>

/* CPM Command रेजिस्टर.
*/
#घोषणा CPM_CR_RST	((uलघु)0x8000)
#घोषणा CPM_CR_OPCODE	((uलघु)0x0f00)
#घोषणा CPM_CR_CHAN	((uलघु)0x00f0)
#घोषणा CPM_CR_FLG	((uलघु)0x0001)

/* Channel numbers.
*/
#घोषणा CPM_CR_CH_SCC1		((uलघु)0x0000)
#घोषणा CPM_CR_CH_I2C		((uलघु)0x0001)	/* I2C and IDMA1 */
#घोषणा CPM_CR_CH_SCC2		((uलघु)0x0004)
#घोषणा CPM_CR_CH_SPI		((uलघु)0x0005)	/* SPI / IDMA2 / Timers */
#घोषणा CPM_CR_CH_TIMER		CPM_CR_CH_SPI
#घोषणा CPM_CR_CH_SCC3		((uलघु)0x0008)
#घोषणा CPM_CR_CH_SMC1		((uलघु)0x0009)	/* SMC1 / DSP1 */
#घोषणा CPM_CR_CH_SCC4		((uलघु)0x000c)
#घोषणा CPM_CR_CH_SMC2		((uलघु)0x000d)	/* SMC2 / DSP2 */

#घोषणा mk_cr_cmd(CH, CMD)	((CMD << 8) | (CH << 4))

/* Export the base address of the communication processor रेजिस्टरs
 * and dual port ram.
 */
बाह्य cpm8xx_t __iomem *cpmp; /* Poपूर्णांकer to comm processor */

#घोषणा cpm_dpalloc cpm_muram_alloc
#घोषणा cpm_dpमुक्त cpm_muram_मुक्त
#घोषणा cpm_dpram_addr cpm_muram_addr
#घोषणा cpm_dpram_phys cpm_muram_dma

बाह्य व्योम cpm_setbrg(uपूर्णांक brg, uपूर्णांक rate);

बाह्य व्योम __init cpm_load_patch(cpm8xx_t *cp);

बाह्य व्योम cpm_reset(व्योम);

/* Parameter RAM offsets.
*/
#घोषणा PROFF_SCC1	((uपूर्णांक)0x0000)
#घोषणा PROFF_IIC	((uपूर्णांक)0x0080)
#घोषणा PROFF_SCC2	((uपूर्णांक)0x0100)
#घोषणा PROFF_SPI	((uपूर्णांक)0x0180)
#घोषणा PROFF_SCC3	((uपूर्णांक)0x0200)
#घोषणा PROFF_SMC1	((uपूर्णांक)0x0280)
#घोषणा PROFF_DSP1	((uपूर्णांक)0x02c0)
#घोषणा PROFF_SCC4	((uपूर्णांक)0x0300)
#घोषणा PROFF_SMC2	((uपूर्णांक)0x0380)

/* Define enough so I can at least use the serial port as a UART.
 * The MBX uses SMC1 as the host serial port.
 */
प्रकार काष्ठा smc_uart अणु
	uलघु	smc_rbase;	/* Rx Buffer descriptor base address */
	uलघु	smc_tbase;	/* Tx Buffer descriptor base address */
	u_अक्षर	smc_rfcr;	/* Rx function code */
	u_अक्षर	smc_tfcr;	/* Tx function code */
	uलघु	smc_mrblr;	/* Max receive buffer length */
	uपूर्णांक	smc_rstate;	/* Internal */
	uपूर्णांक	smc_idp;	/* Internal */
	uलघु	smc_rbptr;	/* Internal */
	uलघु	smc_ibc;	/* Internal */
	uपूर्णांक	smc_rxपंचांगp;	/* Internal */
	uपूर्णांक	smc_tstate;	/* Internal */
	uपूर्णांक	smc_tdp;	/* Internal */
	uलघु	smc_tbptr;	/* Internal */
	uलघु	smc_tbc;	/* Internal */
	uपूर्णांक	smc_txपंचांगp;	/* Internal */
	uलघु	smc_maxidl;	/* Maximum idle अक्षरacters */
	uलघु	smc_पंचांगpidl;	/* Temporary idle counter */
	uलघु	smc_brklen;	/* Last received अवरोध length */
	uलघु	smc_brkec;	/* rcv'd अवरोध condition counter */
	uलघु	smc_brkcr;	/* xmt अवरोध count रेजिस्टर */
	uलघु	smc_rmask;	/* Temporary bit mask */
	अक्षर	res1[8];	/* Reserved */
	uलघु	smc_rpbase;	/* Relocation poपूर्णांकer */
पूर्ण smc_uart_t;

/* Function code bits.
*/
#घोषणा SMC_EB	((u_अक्षर)0x10)	/* Set big endian byte order */

/* SMC uart mode रेजिस्टर.
*/
#घोषणा	SMCMR_REN	((uलघु)0x0001)
#घोषणा SMCMR_TEN	((uलघु)0x0002)
#घोषणा SMCMR_DM	((uलघु)0x000c)
#घोषणा SMCMR_SM_GCI	((uलघु)0x0000)
#घोषणा SMCMR_SM_UART	((uलघु)0x0020)
#घोषणा SMCMR_SM_TRANS	((uलघु)0x0030)
#घोषणा SMCMR_SM_MASK	((uलघु)0x0030)
#घोषणा SMCMR_PM_EVEN	((uलघु)0x0100)	/* Even parity, अन्यथा odd */
#घोषणा SMCMR_REVD	SMCMR_PM_EVEN
#घोषणा SMCMR_PEN	((uलघु)0x0200)	/* Parity enable */
#घोषणा SMCMR_BS	SMCMR_PEN
#घोषणा SMCMR_SL	((uलघु)0x0400)	/* Two stops, अन्यथा one */
#घोषणा SMCR_CLEN_MASK	((uलघु)0x7800)	/* Character length */
#घोषणा smcr_mk_clen(C)	(((C) << 11) & SMCR_CLEN_MASK)

/* SMC2 as Centronics parallel prपूर्णांकer.  It is half duplex, in that
 * it can only receive or transmit.  The parameter ram values क्रम
 * each direction are either unique or properly overlap, so we can
 * include them in one काष्ठाure.
 */
प्रकार काष्ठा smc_centronics अणु
	uलघु	scent_rbase;
	uलघु	scent_tbase;
	u_अक्षर	scent_cfcr;
	u_अक्षर	scent_smask;
	uलघु	scent_mrblr;
	uपूर्णांक	scent_rstate;
	uपूर्णांक	scent_r_ptr;
	uलघु	scent_rbptr;
	uलघु	scent_r_cnt;
	uपूर्णांक	scent_rtemp;
	uपूर्णांक	scent_tstate;
	uपूर्णांक	scent_t_ptr;
	uलघु	scent_tbptr;
	uलघु	scent_t_cnt;
	uपूर्णांक	scent_ttemp;
	uलघु	scent_max_sl;
	uलघु	scent_sl_cnt;
	uलघु	scent_अक्षरacter1;
	uलघु	scent_अक्षरacter2;
	uलघु	scent_अक्षरacter3;
	uलघु	scent_अक्षरacter4;
	uलघु	scent_अक्षरacter5;
	uलघु	scent_अक्षरacter6;
	uलघु	scent_अक्षरacter7;
	uलघु	scent_अक्षरacter8;
	uलघु	scent_rccm;
	uलघु	scent_rccr;
पूर्ण smc_cent_t;

/* Centronics Status Mask Register.
*/
#घोषणा SMC_CENT_F	((u_अक्षर)0x08)
#घोषणा SMC_CENT_PE	((u_अक्षर)0x04)
#घोषणा SMC_CENT_S	((u_अक्षर)0x02)

/* SMC Event and Mask रेजिस्टर.
*/
#घोषणा	SMCM_BRKE	((अचिन्हित अक्षर)0x40)	/* When in UART Mode */
#घोषणा	SMCM_BRK	((अचिन्हित अक्षर)0x10)	/* When in UART Mode */
#घोषणा	SMCM_TXE	((अचिन्हित अक्षर)0x10)	/* When in Transparent Mode */
#घोषणा	SMCM_BSY	((अचिन्हित अक्षर)0x04)
#घोषणा	SMCM_TX		((अचिन्हित अक्षर)0x02)
#घोषणा	SMCM_RX		((अचिन्हित अक्षर)0x01)

/* Baud rate generators.
*/
#घोषणा CPM_BRG_RST		((uपूर्णांक)0x00020000)
#घोषणा CPM_BRG_EN		((uपूर्णांक)0x00010000)
#घोषणा CPM_BRG_EXTC_INT	((uपूर्णांक)0x00000000)
#घोषणा CPM_BRG_EXTC_CLK2	((uपूर्णांक)0x00004000)
#घोषणा CPM_BRG_EXTC_CLK6	((uपूर्णांक)0x00008000)
#घोषणा CPM_BRG_ATB		((uपूर्णांक)0x00002000)
#घोषणा CPM_BRG_CD_MASK		((uपूर्णांक)0x00001ffe)
#घोषणा CPM_BRG_DIV16		((uपूर्णांक)0x00000001)

/* SI Clock Route Register
*/
#घोषणा SICR_RCLK_SCC1_BRG1	((uपूर्णांक)0x00000000)
#घोषणा SICR_TCLK_SCC1_BRG1	((uपूर्णांक)0x00000000)
#घोषणा SICR_RCLK_SCC2_BRG2	((uपूर्णांक)0x00000800)
#घोषणा SICR_TCLK_SCC2_BRG2	((uपूर्णांक)0x00000100)
#घोषणा SICR_RCLK_SCC3_BRG3	((uपूर्णांक)0x00100000)
#घोषणा SICR_TCLK_SCC3_BRG3	((uपूर्णांक)0x00020000)
#घोषणा SICR_RCLK_SCC4_BRG4	((uपूर्णांक)0x18000000)
#घोषणा SICR_TCLK_SCC4_BRG4	((uपूर्णांक)0x03000000)

/* SCCs.
*/
#घोषणा SCC_GSMRH_IRP		((uपूर्णांक)0x00040000)
#घोषणा SCC_GSMRH_GDE		((uपूर्णांक)0x00010000)
#घोषणा SCC_GSMRH_TCRC_CCITT	((uपूर्णांक)0x00008000)
#घोषणा SCC_GSMRH_TCRC_BISYNC	((uपूर्णांक)0x00004000)
#घोषणा SCC_GSMRH_TCRC_HDLC	((uपूर्णांक)0x00000000)
#घोषणा SCC_GSMRH_REVD		((uपूर्णांक)0x00002000)
#घोषणा SCC_GSMRH_TRX		((uपूर्णांक)0x00001000)
#घोषणा SCC_GSMRH_TTX		((uपूर्णांक)0x00000800)
#घोषणा SCC_GSMRH_CDP		((uपूर्णांक)0x00000400)
#घोषणा SCC_GSMRH_CTSP		((uपूर्णांक)0x00000200)
#घोषणा SCC_GSMRH_CDS		((uपूर्णांक)0x00000100)
#घोषणा SCC_GSMRH_CTSS		((uपूर्णांक)0x00000080)
#घोषणा SCC_GSMRH_TFL		((uपूर्णांक)0x00000040)
#घोषणा SCC_GSMRH_RFW		((uपूर्णांक)0x00000020)
#घोषणा SCC_GSMRH_TXSY		((uपूर्णांक)0x00000010)
#घोषणा SCC_GSMRH_SYNL16	((uपूर्णांक)0x0000000c)
#घोषणा SCC_GSMRH_SYNL8		((uपूर्णांक)0x00000008)
#घोषणा SCC_GSMRH_SYNL4		((uपूर्णांक)0x00000004)
#घोषणा SCC_GSMRH_RTSM		((uपूर्णांक)0x00000002)
#घोषणा SCC_GSMRH_RSYN		((uपूर्णांक)0x00000001)

#घोषणा SCC_GSMRL_SIR		((uपूर्णांक)0x80000000)	/* SCC2 only */
#घोषणा SCC_GSMRL_EDGE_NONE	((uपूर्णांक)0x60000000)
#घोषणा SCC_GSMRL_EDGE_NEG	((uपूर्णांक)0x40000000)
#घोषणा SCC_GSMRL_EDGE_POS	((uपूर्णांक)0x20000000)
#घोषणा SCC_GSMRL_EDGE_BOTH	((uपूर्णांक)0x00000000)
#घोषणा SCC_GSMRL_TCI		((uपूर्णांक)0x10000000)
#घोषणा SCC_GSMRL_TSNC_3	((uपूर्णांक)0x0c000000)
#घोषणा SCC_GSMRL_TSNC_4	((uपूर्णांक)0x08000000)
#घोषणा SCC_GSMRL_TSNC_14	((uपूर्णांक)0x04000000)
#घोषणा SCC_GSMRL_TSNC_INF	((uपूर्णांक)0x00000000)
#घोषणा SCC_GSMRL_RINV		((uपूर्णांक)0x02000000)
#घोषणा SCC_GSMRL_TINV		((uपूर्णांक)0x01000000)
#घोषणा SCC_GSMRL_TPL_128	((uपूर्णांक)0x00c00000)
#घोषणा SCC_GSMRL_TPL_64	((uपूर्णांक)0x00a00000)
#घोषणा SCC_GSMRL_TPL_48	((uपूर्णांक)0x00800000)
#घोषणा SCC_GSMRL_TPL_32	((uपूर्णांक)0x00600000)
#घोषणा SCC_GSMRL_TPL_16	((uपूर्णांक)0x00400000)
#घोषणा SCC_GSMRL_TPL_8		((uपूर्णांक)0x00200000)
#घोषणा SCC_GSMRL_TPL_NONE	((uपूर्णांक)0x00000000)
#घोषणा SCC_GSMRL_TPP_ALL1	((uपूर्णांक)0x00180000)
#घोषणा SCC_GSMRL_TPP_01	((uपूर्णांक)0x00100000)
#घोषणा SCC_GSMRL_TPP_10	((uपूर्णांक)0x00080000)
#घोषणा SCC_GSMRL_TPP_ZEROS	((uपूर्णांक)0x00000000)
#घोषणा SCC_GSMRL_TEND		((uपूर्णांक)0x00040000)
#घोषणा SCC_GSMRL_TDCR_32	((uपूर्णांक)0x00030000)
#घोषणा SCC_GSMRL_TDCR_16	((uपूर्णांक)0x00020000)
#घोषणा SCC_GSMRL_TDCR_8	((uपूर्णांक)0x00010000)
#घोषणा SCC_GSMRL_TDCR_1	((uपूर्णांक)0x00000000)
#घोषणा SCC_GSMRL_RDCR_32	((uपूर्णांक)0x0000c000)
#घोषणा SCC_GSMRL_RDCR_16	((uपूर्णांक)0x00008000)
#घोषणा SCC_GSMRL_RDCR_8	((uपूर्णांक)0x00004000)
#घोषणा SCC_GSMRL_RDCR_1	((uपूर्णांक)0x00000000)
#घोषणा SCC_GSMRL_RENC_DFMAN	((uपूर्णांक)0x00003000)
#घोषणा SCC_GSMRL_RENC_MANCH	((uपूर्णांक)0x00002000)
#घोषणा SCC_GSMRL_RENC_FM0	((uपूर्णांक)0x00001000)
#घोषणा SCC_GSMRL_RENC_NRZI	((uपूर्णांक)0x00000800)
#घोषणा SCC_GSMRL_RENC_NRZ	((uपूर्णांक)0x00000000)
#घोषणा SCC_GSMRL_TENC_DFMAN	((uपूर्णांक)0x00000600)
#घोषणा SCC_GSMRL_TENC_MANCH	((uपूर्णांक)0x00000400)
#घोषणा SCC_GSMRL_TENC_FM0	((uपूर्णांक)0x00000200)
#घोषणा SCC_GSMRL_TENC_NRZI	((uपूर्णांक)0x00000100)
#घोषणा SCC_GSMRL_TENC_NRZ	((uपूर्णांक)0x00000000)
#घोषणा SCC_GSMRL_DIAG_LE	((uपूर्णांक)0x000000c0)	/* Loop and echo */
#घोषणा SCC_GSMRL_DIAG_ECHO	((uपूर्णांक)0x00000080)
#घोषणा SCC_GSMRL_DIAG_LOOP	((uपूर्णांक)0x00000040)
#घोषणा SCC_GSMRL_DIAG_NORM	((uपूर्णांक)0x00000000)
#घोषणा SCC_GSMRL_ENR		((uपूर्णांक)0x00000020)
#घोषणा SCC_GSMRL_ENT		((uपूर्णांक)0x00000010)
#घोषणा SCC_GSMRL_MODE_ENET	((uपूर्णांक)0x0000000c)
#घोषणा SCC_GSMRL_MODE_QMC	((uपूर्णांक)0x0000000a)
#घोषणा SCC_GSMRL_MODE_DDCMP	((uपूर्णांक)0x00000009)
#घोषणा SCC_GSMRL_MODE_BISYNC	((uपूर्णांक)0x00000008)
#घोषणा SCC_GSMRL_MODE_V14	((uपूर्णांक)0x00000007)
#घोषणा SCC_GSMRL_MODE_AHDLC	((uपूर्णांक)0x00000006)
#घोषणा SCC_GSMRL_MODE_PROFIBUS	((uपूर्णांक)0x00000005)
#घोषणा SCC_GSMRL_MODE_UART	((uपूर्णांक)0x00000004)
#घोषणा SCC_GSMRL_MODE_SS7	((uपूर्णांक)0x00000003)
#घोषणा SCC_GSMRL_MODE_ATALK	((uपूर्णांक)0x00000002)
#घोषणा SCC_GSMRL_MODE_HDLC	((uपूर्णांक)0x00000000)

#घोषणा SCC_TODR_TOD		((uलघु)0x8000)

/* SCC Event and Mask रेजिस्टर.
*/
#घोषणा	SCCM_TXE	((अचिन्हित अक्षर)0x10)
#घोषणा	SCCM_BSY	((अचिन्हित अक्षर)0x04)
#घोषणा	SCCM_TX		((अचिन्हित अक्षर)0x02)
#घोषणा	SCCM_RX		((अचिन्हित अक्षर)0x01)

प्रकार काष्ठा scc_param अणु
	uलघु	scc_rbase;	/* Rx Buffer descriptor base address */
	uलघु	scc_tbase;	/* Tx Buffer descriptor base address */
	u_अक्षर	scc_rfcr;	/* Rx function code */
	u_अक्षर	scc_tfcr;	/* Tx function code */
	uलघु	scc_mrblr;	/* Max receive buffer length */
	uपूर्णांक	scc_rstate;	/* Internal */
	uपूर्णांक	scc_idp;	/* Internal */
	uलघु	scc_rbptr;	/* Internal */
	uलघु	scc_ibc;	/* Internal */
	uपूर्णांक	scc_rxपंचांगp;	/* Internal */
	uपूर्णांक	scc_tstate;	/* Internal */
	uपूर्णांक	scc_tdp;	/* Internal */
	uलघु	scc_tbptr;	/* Internal */
	uलघु	scc_tbc;	/* Internal */
	uपूर्णांक	scc_txपंचांगp;	/* Internal */
	uपूर्णांक	scc_rcrc;	/* Internal */
	uपूर्णांक	scc_tcrc;	/* Internal */
पूर्ण sccp_t;

/* Function code bits.
*/
#घोषणा SCC_EB	((u_अक्षर)0x10)	/* Set big endian byte order */

/* CPM Ethernet through SCCx.
 */
प्रकार काष्ठा scc_enet अणु
	sccp_t	sen_genscc;
	uपूर्णांक	sen_cpres;	/* Preset CRC */
	uपूर्णांक	sen_cmask;	/* Constant mask क्रम CRC */
	uपूर्णांक	sen_crcec;	/* CRC Error counter */
	uपूर्णांक	sen_alec;	/* alignment error counter */
	uपूर्णांक	sen_disfc;	/* discard frame counter */
	uलघु	sen_pads;	/* Tx लघु frame pad अक्षरacter */
	uलघु	sen_retlim;	/* Retry limit threshold */
	uलघु	sen_retcnt;	/* Retry limit counter */
	uलघु	sen_maxflr;	/* maximum frame length रेजिस्टर */
	uलघु	sen_minflr;	/* minimum frame length रेजिस्टर */
	uलघु	sen_maxd1;	/* maximum DMA1 length */
	uलघु	sen_maxd2;	/* maximum DMA2 length */
	uलघु	sen_maxd;	/* Rx max DMA */
	uलघु	sen_dmacnt;	/* Rx DMA counter */
	uलघु	sen_maxb;	/* Max BD byte count */
	uलघु	sen_gaddr1;	/* Group address filter */
	uलघु	sen_gaddr2;
	uलघु	sen_gaddr3;
	uलघु	sen_gaddr4;
	uपूर्णांक	sen_tbuf0data0;	/* Save area 0 - current frame */
	uपूर्णांक	sen_tbuf0data1;	/* Save area 1 - current frame */
	uपूर्णांक	sen_tbuf0rba;	/* Internal */
	uपूर्णांक	sen_tbuf0crc;	/* Internal */
	uलघु	sen_tbuf0bcnt;	/* Internal */
	uलघु	sen_paddrh;	/* physical address (MSB) */
	uलघु	sen_paddrm;
	uलघु	sen_paddrl;	/* physical address (LSB) */
	uलघु	sen_pper;	/* persistence */
	uलघु	sen_rfbdptr;	/* Rx first BD poपूर्णांकer */
	uलघु	sen_tfbdptr;	/* Tx first BD poपूर्णांकer */
	uलघु	sen_tlbdptr;	/* Tx last BD poपूर्णांकer */
	uपूर्णांक	sen_tbuf1data0;	/* Save area 0 - current frame */
	uपूर्णांक	sen_tbuf1data1;	/* Save area 1 - current frame */
	uपूर्णांक	sen_tbuf1rba;	/* Internal */
	uपूर्णांक	sen_tbuf1crc;	/* Internal */
	uलघु	sen_tbuf1bcnt;	/* Internal */
	uलघु	sen_txlen;	/* Tx Frame length counter */
	uलघु	sen_iaddr1;	/* Inभागidual address filter */
	uलघु	sen_iaddr2;
	uलघु	sen_iaddr3;
	uलघु	sen_iaddr4;
	uलघु	sen_boffcnt;	/* Backoff counter */

	/* NOTE: Some versions of the manual have the following items
	 * incorrectly करोcumented.  Below is the proper order.
	 */
	uलघु	sen_taddrh;	/* temp address (MSB) */
	uलघु	sen_taddrm;
	uलघु	sen_taddrl;	/* temp address (LSB) */
पूर्ण scc_enet_t;

/* SCC Event रेजिस्टर as used by Ethernet.
*/
#घोषणा SCCE_ENET_GRA	((uलघु)0x0080)	/* Graceful stop complete */
#घोषणा SCCE_ENET_TXE	((uलघु)0x0010)	/* Transmit Error */
#घोषणा SCCE_ENET_RXF	((uलघु)0x0008)	/* Full frame received */
#घोषणा SCCE_ENET_BSY	((uलघु)0x0004)	/* All incoming buffers full */
#घोषणा SCCE_ENET_TXB	((uलघु)0x0002)	/* A buffer was transmitted */
#घोषणा SCCE_ENET_RXB	((uलघु)0x0001)	/* A buffer was received */

/* SCC Mode Register (PMSR) as used by Ethernet.
*/
#घोषणा SCC_PSMR_HBC	((uलघु)0x8000)	/* Enable heartbeat */
#घोषणा SCC_PSMR_FC	((uलघु)0x4000)	/* Force collision */
#घोषणा SCC_PSMR_RSH	((uलघु)0x2000)	/* Receive लघु frames */
#घोषणा SCC_PSMR_IAM	((uलघु)0x1000)	/* Check inभागidual hash */
#घोषणा SCC_PSMR_ENCRC	((uलघु)0x0800)	/* Ethernet CRC mode */
#घोषणा SCC_PSMR_PRO	((uलघु)0x0200)	/* Promiscuous mode */
#घोषणा SCC_PSMR_BRO	((uलघु)0x0100)	/* Catch broadcast pkts */
#घोषणा SCC_PSMR_SBT	((uलघु)0x0080)	/* Special backoff समयr */
#घोषणा SCC_PSMR_LPB	((uलघु)0x0040)	/* Set Loopback mode */
#घोषणा SCC_PSMR_SIP	((uलघु)0x0020)	/* Sample Input Pins */
#घोषणा SCC_PSMR_LCW	((uलघु)0x0010)	/* Late collision winकरोw */
#घोषणा SCC_PSMR_NIB22	((uलघु)0x000a)	/* Start frame search */
#घोषणा SCC_PSMR_FDE	((uलघु)0x0001)	/* Full duplex enable */

/* SCC as UART
*/
प्रकार काष्ठा scc_uart अणु
	sccp_t	scc_genscc;
	अक्षर	res1[8];	/* Reserved */
	uलघु	scc_maxidl;	/* Maximum idle अक्षरs */
	uलघु	scc_idlc;	/* temp idle counter */
	uलघु	scc_brkcr;	/* Break count रेजिस्टर */
	uलघु	scc_parec;	/* receive parity error counter */
	uलघु	scc_frmec;	/* receive framing error counter */
	uलघु	scc_nosec;	/* receive noise counter */
	uलघु	scc_brkec;	/* receive अवरोध condition counter */
	uलघु	scc_brkln;	/* last received अवरोध length */
	uलघु	scc_uaddr1;	/* UART address अक्षरacter 1 */
	uलघु	scc_uaddr2;	/* UART address अक्षरacter 2 */
	uलघु	scc_rtemp;	/* Temp storage */
	uलघु	scc_toseq;	/* Transmit out of sequence अक्षर */
	uलघु	scc_अक्षर1;	/* control अक्षरacter 1 */
	uलघु	scc_अक्षर2;	/* control अक्षरacter 2 */
	uलघु	scc_अक्षर3;	/* control अक्षरacter 3 */
	uलघु	scc_अक्षर4;	/* control अक्षरacter 4 */
	uलघु	scc_अक्षर5;	/* control अक्षरacter 5 */
	uलघु	scc_अक्षर6;	/* control अक्षरacter 6 */
	uलघु	scc_अक्षर7;	/* control अक्षरacter 7 */
	uलघु	scc_अक्षर8;	/* control अक्षरacter 8 */
	uलघु	scc_rccm;	/* receive control अक्षरacter mask */
	uलघु	scc_rccr;	/* receive control अक्षरacter रेजिस्टर */
	uलघु	scc_rlbc;	/* receive last अवरोध अक्षरacter */
पूर्ण scc_uart_t;

/* SCC Event and Mask रेजिस्टरs when it is used as a UART.
*/
#घोषणा UART_SCCM_GLR		((uलघु)0x1000)
#घोषणा UART_SCCM_GLT		((uलघु)0x0800)
#घोषणा UART_SCCM_AB		((uलघु)0x0200)
#घोषणा UART_SCCM_IDL		((uलघु)0x0100)
#घोषणा UART_SCCM_GRA		((uलघु)0x0080)
#घोषणा UART_SCCM_BRKE		((uलघु)0x0040)
#घोषणा UART_SCCM_BRKS		((uलघु)0x0020)
#घोषणा UART_SCCM_CCR		((uलघु)0x0008)
#घोषणा UART_SCCM_BSY		((uलघु)0x0004)
#घोषणा UART_SCCM_TX		((uलघु)0x0002)
#घोषणा UART_SCCM_RX		((uलघु)0x0001)

/* The SCC PMSR when used as a UART.
*/
#घोषणा SCU_PSMR_FLC		((uलघु)0x8000)
#घोषणा SCU_PSMR_SL		((uलघु)0x4000)
#घोषणा SCU_PSMR_CL		((uलघु)0x3000)
#घोषणा SCU_PSMR_UM		((uलघु)0x0c00)
#घोषणा SCU_PSMR_FRZ		((uलघु)0x0200)
#घोषणा SCU_PSMR_RZS		((uलघु)0x0100)
#घोषणा SCU_PSMR_SYN		((uलघु)0x0080)
#घोषणा SCU_PSMR_DRT		((uलघु)0x0040)
#घोषणा SCU_PSMR_PEN		((uलघु)0x0010)
#घोषणा SCU_PSMR_RPM		((uलघु)0x000c)
#घोषणा SCU_PSMR_REVP		((uलघु)0x0008)
#घोषणा SCU_PSMR_TPM		((uलघु)0x0003)
#घोषणा SCU_PSMR_TEVP		((uलघु)0x0002)

/* CPM Transparent mode SCC.
 */
प्रकार काष्ठा scc_trans अणु
	sccp_t	st_genscc;
	uपूर्णांक	st_cpres;	/* Preset CRC */
	uपूर्णांक	st_cmask;	/* Constant mask क्रम CRC */
पूर्ण scc_trans_t;

/* IIC parameter RAM.
*/
प्रकार काष्ठा iic अणु
	uलघु	iic_rbase;	/* Rx Buffer descriptor base address */
	uलघु	iic_tbase;	/* Tx Buffer descriptor base address */
	u_अक्षर	iic_rfcr;	/* Rx function code */
	u_अक्षर	iic_tfcr;	/* Tx function code */
	uलघु	iic_mrblr;	/* Max receive buffer length */
	uपूर्णांक	iic_rstate;	/* Internal */
	uपूर्णांक	iic_rdp;	/* Internal */
	uलघु	iic_rbptr;	/* Internal */
	uलघु	iic_rbc;	/* Internal */
	uपूर्णांक	iic_rxपंचांगp;	/* Internal */
	uपूर्णांक	iic_tstate;	/* Internal */
	uपूर्णांक	iic_tdp;	/* Internal */
	uलघु	iic_tbptr;	/* Internal */
	uलघु	iic_tbc;	/* Internal */
	uपूर्णांक	iic_txपंचांगp;	/* Internal */
	अक्षर	res1[4];	/* Reserved */
	uलघु	iic_rpbase;	/* Relocation poपूर्णांकer */
	अक्षर	res2[2];	/* Reserved */
पूर्ण iic_t;

/*
 * RISC Controller Configuration Register definitons
 */
#घोषणा RCCR_TIME	0x8000			/* RISC Timer Enable */
#घोषणा RCCR_TIMEP(t)	(((t) & 0x3F)<<8)	/* RISC Timer Period */
#घोषणा RCCR_TIME_MASK	0x00FF			/* not RISC Timer related bits */

/* RISC Timer Parameter RAM offset */
#घोषणा PROFF_RTMR	((uपूर्णांक)0x01B0)

प्रकार काष्ठा risc_समयr_pram अणु
	अचिन्हित लघु	पंचांग_base;	/* RISC Timer Table Base Address */
	अचिन्हित लघु	पंचांग_ptr;		/* RISC Timer Table Poपूर्णांकer (पूर्णांकernal) */
	अचिन्हित लघु	r_पंचांगr;		/* RISC Timer Mode Register */
	अचिन्हित लघु	r_पंचांगv;		/* RISC Timer Valid Register */
	अचिन्हित दीर्घ	पंचांग_cmd;		/* RISC Timer Command Register */
	अचिन्हित दीर्घ	पंचांग_cnt;		/* RISC Timer Internal Count */
पूर्ण rt_pram_t;

/* Bits in RISC Timer Command Register */
#घोषणा TM_CMD_VALID	0x80000000	/* Valid - Enables the समयr */
#घोषणा TM_CMD_RESTART	0x40000000	/* Restart - क्रम स्वतःmatic restart */
#घोषणा TM_CMD_PWM	0x20000000	/* Run in Pulse Width Modulation Mode */
#घोषणा TM_CMD_NUM(n)	(((n)&0xF)<<16)	/* Timer Number */
#घोषणा TM_CMD_PERIOD(p) ((p)&0xFFFF)	/* Timer Period */

/* CPM पूर्णांकerrupts.  There are nearly 32 पूर्णांकerrupts generated by CPM
 * channels or devices.  All of these are presented to the PPC core
 * as a single पूर्णांकerrupt.  The CPM पूर्णांकerrupt handler dispatches its
 * own handlers, in a similar fashion to the PPC core handler.  We
 * use the table as defined in the manuals (i.e. no special high
 * priority and SCC1 == SCCa, etc...).
 */
#घोषणा CPMVEC_NR		32
#घोषणा	CPMVEC_PIO_PC15		((uलघु)0x1f)
#घोषणा	CPMVEC_SCC1		((uलघु)0x1e)
#घोषणा	CPMVEC_SCC2		((uलघु)0x1d)
#घोषणा	CPMVEC_SCC3		((uलघु)0x1c)
#घोषणा	CPMVEC_SCC4		((uलघु)0x1b)
#घोषणा	CPMVEC_PIO_PC14		((uलघु)0x1a)
#घोषणा	CPMVEC_TIMER1		((uलघु)0x19)
#घोषणा	CPMVEC_PIO_PC13		((uलघु)0x18)
#घोषणा	CPMVEC_PIO_PC12		((uलघु)0x17)
#घोषणा	CPMVEC_SDMA_CB_ERR	((uलघु)0x16)
#घोषणा CPMVEC_IDMA1		((uलघु)0x15)
#घोषणा CPMVEC_IDMA2		((uलघु)0x14)
#घोषणा CPMVEC_TIMER2		((uलघु)0x12)
#घोषणा CPMVEC_RISCTIMER	((uलघु)0x11)
#घोषणा CPMVEC_I2C		((uलघु)0x10)
#घोषणा	CPMVEC_PIO_PC11		((uलघु)0x0f)
#घोषणा	CPMVEC_PIO_PC10		((uलघु)0x0e)
#घोषणा CPMVEC_TIMER3		((uलघु)0x0c)
#घोषणा	CPMVEC_PIO_PC9		((uलघु)0x0b)
#घोषणा	CPMVEC_PIO_PC8		((uलघु)0x0a)
#घोषणा	CPMVEC_PIO_PC7		((uलघु)0x09)
#घोषणा CPMVEC_TIMER4		((uलघु)0x07)
#घोषणा	CPMVEC_PIO_PC6		((uलघु)0x06)
#घोषणा	CPMVEC_SPI		((uलघु)0x05)
#घोषणा	CPMVEC_SMC1		((uलघु)0x04)
#घोषणा	CPMVEC_SMC2		((uलघु)0x03)
#घोषणा	CPMVEC_PIO_PC5		((uलघु)0x02)
#घोषणा	CPMVEC_PIO_PC4		((uलघु)0x01)
#घोषणा	CPMVEC_ERROR		((uलघु)0x00)

/* CPM पूर्णांकerrupt configuration vector.
*/
#घोषणा	CICR_SCD_SCC4		((uपूर्णांक)0x00c00000)	/* SCC4 @ SCCd */
#घोषणा	CICR_SCC_SCC3		((uपूर्णांक)0x00200000)	/* SCC3 @ SCCc */
#घोषणा	CICR_SCB_SCC2		((uपूर्णांक)0x00040000)	/* SCC2 @ SCCb */
#घोषणा	CICR_SCA_SCC1		((uपूर्णांक)0x00000000)	/* SCC1 @ SCCa */
#घोषणा CICR_IRL_MASK		((uपूर्णांक)0x0000e000)	/* Core पूर्णांकerrupt */
#घोषणा CICR_HP_MASK		((uपूर्णांक)0x00001f00)	/* Hi-pri पूर्णांक. */
#घोषणा CICR_IEN		((uपूर्णांक)0x00000080)	/* Int. enable */
#घोषणा CICR_SPS		((uपूर्णांक)0x00000001)	/* SCC Spपढ़ो */

#घोषणा CPM_PIN_INPUT     0
#घोषणा CPM_PIN_OUTPUT    1
#घोषणा CPM_PIN_PRIMARY   0
#घोषणा CPM_PIN_SECONDARY 2
#घोषणा CPM_PIN_GPIO      4
#घोषणा CPM_PIN_OPENDRAIN 8
#घोषणा CPM_PIN_FALLEDGE  16
#घोषणा CPM_PIN_ANYEDGE   0

क्रमागत cpm_port अणु
	CPM_PORTA,
	CPM_PORTB,
	CPM_PORTC,
	CPM_PORTD,
	CPM_PORTE,
पूर्ण;

व्योम cpm1_set_pin(क्रमागत cpm_port port, पूर्णांक pin, पूर्णांक flags);

क्रमागत cpm_clk_dir अणु
	CPM_CLK_RX,
	CPM_CLK_TX,
	CPM_CLK_RTX
पूर्ण;

क्रमागत cpm_clk_target अणु
	CPM_CLK_SCC1,
	CPM_CLK_SCC2,
	CPM_CLK_SCC3,
	CPM_CLK_SCC4,
	CPM_CLK_SMC1,
	CPM_CLK_SMC2,
पूर्ण;

क्रमागत cpm_clk अणु
	CPM_BRG1,	/* Baud Rate Generator  1 */
	CPM_BRG2,	/* Baud Rate Generator  2 */
	CPM_BRG3,	/* Baud Rate Generator  3 */
	CPM_BRG4,	/* Baud Rate Generator  4 */
	CPM_CLK1,	/* Clock  1 */
	CPM_CLK2,	/* Clock  2 */
	CPM_CLK3,	/* Clock  3 */
	CPM_CLK4,	/* Clock  4 */
	CPM_CLK5,	/* Clock  5 */
	CPM_CLK6,	/* Clock  6 */
	CPM_CLK7,	/* Clock  7 */
	CPM_CLK8,	/* Clock  8 */
पूर्ण;

पूर्णांक cpm1_clk_setup(क्रमागत cpm_clk_target target, पूर्णांक घड़ी, पूर्णांक mode);
पूर्णांक cpm1_gpiochip_add16(काष्ठा device *dev);
पूर्णांक cpm1_gpiochip_add32(काष्ठा device *dev);

#पूर्ण_अगर /* __CPM1__ */
