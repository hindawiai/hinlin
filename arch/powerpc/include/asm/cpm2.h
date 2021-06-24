<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Communication Processor Module v2.
 *
 * This file contains काष्ठाures and inक्रमmation क्रम the communication
 * processor channels found in the dual port RAM or parameter RAM.
 * All CPM control and status is available through the CPM2 पूर्णांकernal
 * memory map.  See immap_cpm2.h क्रम details.
 */
#अगर_घोषित __KERNEL__
#अगर_अघोषित __CPM2__
#घोषणा __CPM2__

#समावेश <यंत्र/immap_cpm2.h>
#समावेश <यंत्र/cpm.h>
#समावेश <sysdev/fsl_soc.h>

/* CPM Command रेजिस्टर.
*/
#घोषणा CPM_CR_RST	((uपूर्णांक)0x80000000)
#घोषणा CPM_CR_PAGE	((uपूर्णांक)0x7c000000)
#घोषणा CPM_CR_SBLOCK	((uपूर्णांक)0x03e00000)
#घोषणा CPM_CR_FLG	((uपूर्णांक)0x00010000)
#घोषणा CPM_CR_MCN	((uपूर्णांक)0x00003fc0)
#घोषणा CPM_CR_OPCODE	((uपूर्णांक)0x0000000f)

/* Device sub-block and page codes.
*/
#घोषणा CPM_CR_SCC1_SBLOCK	(0x04)
#घोषणा CPM_CR_SCC2_SBLOCK	(0x05)
#घोषणा CPM_CR_SCC3_SBLOCK	(0x06)
#घोषणा CPM_CR_SCC4_SBLOCK	(0x07)
#घोषणा CPM_CR_SMC1_SBLOCK	(0x08)
#घोषणा CPM_CR_SMC2_SBLOCK	(0x09)
#घोषणा CPM_CR_SPI_SBLOCK	(0x0a)
#घोषणा CPM_CR_I2C_SBLOCK	(0x0b)
#घोषणा CPM_CR_TIMER_SBLOCK	(0x0f)
#घोषणा CPM_CR_RAND_SBLOCK	(0x0e)
#घोषणा CPM_CR_FCC1_SBLOCK	(0x10)
#घोषणा CPM_CR_FCC2_SBLOCK	(0x11)
#घोषणा CPM_CR_FCC3_SBLOCK	(0x12)
#घोषणा CPM_CR_IDMA1_SBLOCK	(0x14)
#घोषणा CPM_CR_IDMA2_SBLOCK	(0x15)
#घोषणा CPM_CR_IDMA3_SBLOCK	(0x16)
#घोषणा CPM_CR_IDMA4_SBLOCK	(0x17)
#घोषणा CPM_CR_MCC1_SBLOCK	(0x1c)

#घोषणा CPM_CR_FCC_SBLOCK(x)	(x + 0x10)

#घोषणा CPM_CR_SCC1_PAGE	(0x00)
#घोषणा CPM_CR_SCC2_PAGE	(0x01)
#घोषणा CPM_CR_SCC3_PAGE	(0x02)
#घोषणा CPM_CR_SCC4_PAGE	(0x03)
#घोषणा CPM_CR_SMC1_PAGE	(0x07)
#घोषणा CPM_CR_SMC2_PAGE	(0x08)
#घोषणा CPM_CR_SPI_PAGE		(0x09)
#घोषणा CPM_CR_I2C_PAGE		(0x0a)
#घोषणा CPM_CR_TIMER_PAGE	(0x0a)
#घोषणा CPM_CR_RAND_PAGE	(0x0a)
#घोषणा CPM_CR_FCC1_PAGE	(0x04)
#घोषणा CPM_CR_FCC2_PAGE	(0x05)
#घोषणा CPM_CR_FCC3_PAGE	(0x06)
#घोषणा CPM_CR_IDMA1_PAGE	(0x07)
#घोषणा CPM_CR_IDMA2_PAGE	(0x08)
#घोषणा CPM_CR_IDMA3_PAGE	(0x09)
#घोषणा CPM_CR_IDMA4_PAGE	(0x0a)
#घोषणा CPM_CR_MCC1_PAGE	(0x07)
#घोषणा CPM_CR_MCC2_PAGE	(0x08)

#घोषणा CPM_CR_FCC_PAGE(x)	(x + 0x04)

/* CPM2-specअगरic opcodes (see cpm.h क्रम common opcodes)
*/
#घोषणा CPM_CR_START_IDMA	((uलघु)0x0009)

#घोषणा mk_cr_cmd(PG, SBC, MCN, OP) \
	((PG << 26) | (SBC << 21) | (MCN << 6) | OP)

/* The number of pages of host memory we allocate क्रम CPM.  This is
 * करोne early in kernel initialization to get physically contiguous
 * pages.
 */
#घोषणा NUM_CPM_HOST_PAGES	2

/* Export the base address of the communication processor रेजिस्टरs
 * and dual port ram.
 */
बाह्य cpm_cpm2_t __iomem *cpmp; /* Poपूर्णांकer to comm processor */

#घोषणा cpm_dpalloc cpm_muram_alloc
#घोषणा cpm_dpमुक्त cpm_muram_मुक्त
#घोषणा cpm_dpram_addr cpm_muram_addr

बाह्य व्योम cpm2_reset(व्योम);

/* Baud rate generators.
*/
#घोषणा CPM_BRG_RST		((uपूर्णांक)0x00020000)
#घोषणा CPM_BRG_EN		((uपूर्णांक)0x00010000)
#घोषणा CPM_BRG_EXTC_INT	((uपूर्णांक)0x00000000)
#घोषणा CPM_BRG_EXTC_CLK3_9	((uपूर्णांक)0x00004000)
#घोषणा CPM_BRG_EXTC_CLK5_15	((uपूर्णांक)0x00008000)
#घोषणा CPM_BRG_ATB		((uपूर्णांक)0x00002000)
#घोषणा CPM_BRG_CD_MASK		((uपूर्णांक)0x00001ffe)
#घोषणा CPM_BRG_DIV16		((uपूर्णांक)0x00000001)

#घोषणा CPM2_BRG_INT_CLK	(get_brgfreq())
#घोषणा CPM2_BRG_UART_CLK	(CPM2_BRG_INT_CLK/16)

बाह्य व्योम __cpm2_setbrg(uपूर्णांक brg, uपूर्णांक rate, uपूर्णांक clk, पूर्णांक भाग16, पूर्णांक src);

/* This function is used by UARTS, or anything अन्यथा that uses a 16x
 * oversampled घड़ी.
 */
अटल अंतरभूत व्योम cpm_setbrg(uपूर्णांक brg, uपूर्णांक rate)
अणु
	__cpm2_setbrg(brg, rate, CPM2_BRG_UART_CLK, 0, CPM_BRG_EXTC_INT);
पूर्ण

/* This function is used to set high speed synchronous baud rate
 * घड़ीs.
 */
अटल अंतरभूत व्योम cpm2_fastbrg(uपूर्णांक brg, uपूर्णांक rate, पूर्णांक भाग16)
अणु
	__cpm2_setbrg(brg, rate, CPM2_BRG_INT_CLK, भाग16, CPM_BRG_EXTC_INT);
पूर्ण

/* Parameter RAM offsets from the base.
*/
#घोषणा PROFF_SCC1		((uपूर्णांक)0x8000)
#घोषणा PROFF_SCC2		((uपूर्णांक)0x8100)
#घोषणा PROFF_SCC3		((uपूर्णांक)0x8200)
#घोषणा PROFF_SCC4		((uपूर्णांक)0x8300)
#घोषणा PROFF_FCC1		((uपूर्णांक)0x8400)
#घोषणा PROFF_FCC2		((uपूर्णांक)0x8500)
#घोषणा PROFF_FCC3		((uपूर्णांक)0x8600)
#घोषणा PROFF_MCC1		((uपूर्णांक)0x8700)
#घोषणा PROFF_SMC1_BASE		((uपूर्णांक)0x87fc)
#घोषणा PROFF_IDMA1_BASE	((uपूर्णांक)0x87fe)
#घोषणा PROFF_MCC2		((uपूर्णांक)0x8800)
#घोषणा PROFF_SMC2_BASE		((uपूर्णांक)0x88fc)
#घोषणा PROFF_IDMA2_BASE	((uपूर्णांक)0x88fe)
#घोषणा PROFF_SPI_BASE		((uपूर्णांक)0x89fc)
#घोषणा PROFF_IDMA3_BASE	((uपूर्णांक)0x89fe)
#घोषणा PROFF_TIMERS		((uपूर्णांक)0x8ae0)
#घोषणा PROFF_REVNUM		((uपूर्णांक)0x8af0)
#घोषणा PROFF_RAND		((uपूर्णांक)0x8af8)
#घोषणा PROFF_I2C_BASE		((uपूर्णांक)0x8afc)
#घोषणा PROFF_IDMA4_BASE	((uपूर्णांक)0x8afe)

#घोषणा PROFF_SCC_SIZE		((uपूर्णांक)0x100)
#घोषणा PROFF_FCC_SIZE		((uपूर्णांक)0x100)
#घोषणा PROFF_SMC_SIZE		((uपूर्णांक)64)

/* The SMCs are relocated to any of the first eight DPRAM pages.
 * We will fix these at the first locations of DPRAM, until we
 * get some microcode patches :-).
 * The parameter ram space क्रम the SMCs is fअगरty-some bytes, and
 * they are required to start on a 64 byte boundary.
 */
#घोषणा PROFF_SMC1	(0)
#घोषणा PROFF_SMC2	(64)


/* Define enough so I can at least use the serial port as a UART.
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
	uपूर्णांक	smc_sपंचांगp;	/* SDMA Temp */
पूर्ण smc_uart_t;

/* SMC uart mode रेजिस्टर (Internal memory map).
*/
#घोषणा SMCMR_REN	((uलघु)0x0001)
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

/* SMC Event and Mask रेजिस्टर.
*/
#घोषणा SMCM_BRKE       ((अचिन्हित अक्षर)0x40)   /* When in UART Mode */
#घोषणा SMCM_BRK        ((अचिन्हित अक्षर)0x10)   /* When in UART Mode */
#घोषणा SMCM_TXE	((अचिन्हित अक्षर)0x10)
#घोषणा SMCM_BSY	((अचिन्हित अक्षर)0x04)
#घोषणा SMCM_TX		((अचिन्हित अक्षर)0x02)
#घोषणा SMCM_RX		((अचिन्हित अक्षर)0x01)

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
#घोषणा SCCM_TXE	((अचिन्हित अक्षर)0x10)
#घोषणा SCCM_BSY	((अचिन्हित अक्षर)0x04)
#घोषणा SCCM_TX		((अचिन्हित अक्षर)0x02)
#घोषणा SCCM_RX		((अचिन्हित अक्षर)0x01)

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
#घोषणा SCC_EB	((u_अक्षर) 0x10)	/* Set big endian byte order */
#घोषणा SCC_GBL	((u_अक्षर) 0x20) /* Snooping enabled */

/* CPM Ethernet through SCC1.
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

/* SCC Mode Register (PSMR) as used by Ethernet.
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
	uपूर्णांक	scc_res1;	/* Reserved */
	uपूर्णांक	scc_res2;	/* Reserved */
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

/* The SCC PSMR when used as a UART.
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

/* How about some FCCs.....
*/
#घोषणा FCC_GFMR_DIAG_NORM	((uपूर्णांक)0x00000000)
#घोषणा FCC_GFMR_DIAG_LE	((uपूर्णांक)0x40000000)
#घोषणा FCC_GFMR_DIAG_AE	((uपूर्णांक)0x80000000)
#घोषणा FCC_GFMR_DIAG_ALE	((uपूर्णांक)0xc0000000)
#घोषणा FCC_GFMR_TCI		((uपूर्णांक)0x20000000)
#घोषणा FCC_GFMR_TRX		((uपूर्णांक)0x10000000)
#घोषणा FCC_GFMR_TTX		((uपूर्णांक)0x08000000)
#घोषणा FCC_GFMR_CDP		((uपूर्णांक)0x04000000)
#घोषणा FCC_GFMR_CTSP		((uपूर्णांक)0x02000000)
#घोषणा FCC_GFMR_CDS		((uपूर्णांक)0x01000000)
#घोषणा FCC_GFMR_CTSS		((uपूर्णांक)0x00800000)
#घोषणा FCC_GFMR_SYNL_NONE	((uपूर्णांक)0x00000000)
#घोषणा FCC_GFMR_SYNL_AUTO	((uपूर्णांक)0x00004000)
#घोषणा FCC_GFMR_SYNL_8		((uपूर्णांक)0x00008000)
#घोषणा FCC_GFMR_SYNL_16	((uपूर्णांक)0x0000c000)
#घोषणा FCC_GFMR_RTSM		((uपूर्णांक)0x00002000)
#घोषणा FCC_GFMR_RENC_NRZ	((uपूर्णांक)0x00000000)
#घोषणा FCC_GFMR_RENC_NRZI	((uपूर्णांक)0x00000800)
#घोषणा FCC_GFMR_REVD		((uपूर्णांक)0x00000400)
#घोषणा FCC_GFMR_TENC_NRZ	((uपूर्णांक)0x00000000)
#घोषणा FCC_GFMR_TENC_NRZI	((uपूर्णांक)0x00000100)
#घोषणा FCC_GFMR_TCRC_16	((uपूर्णांक)0x00000000)
#घोषणा FCC_GFMR_TCRC_32	((uपूर्णांक)0x00000080)
#घोषणा FCC_GFMR_ENR		((uपूर्णांक)0x00000020)
#घोषणा FCC_GFMR_ENT		((uपूर्णांक)0x00000010)
#घोषणा FCC_GFMR_MODE_ENET	((uपूर्णांक)0x0000000c)
#घोषणा FCC_GFMR_MODE_ATM	((uपूर्णांक)0x0000000a)
#घोषणा FCC_GFMR_MODE_HDLC	((uपूर्णांक)0x00000000)

/* Generic FCC parameter ram.
*/
प्रकार काष्ठा fcc_param अणु
	uलघु	fcc_riptr;	/* Rx Internal temp poपूर्णांकer */
	uलघु	fcc_tiptr;	/* Tx Internal temp poपूर्णांकer */
	uलघु	fcc_res1;
	uलघु	fcc_mrblr;	/* Max receive buffer length, mod 32 bytes */
	uपूर्णांक	fcc_rstate;	/* Upper byte is Func code, must be set */
	uपूर्णांक	fcc_rbase;	/* Receive BD base */
	uलघु	fcc_rbdstat;	/* RxBD status */
	uलघु	fcc_rbdlen;	/* RxBD करोwn counter */
	uपूर्णांक	fcc_rdptr;	/* RxBD पूर्णांकernal data poपूर्णांकer */
	uपूर्णांक	fcc_tstate;	/* Upper byte is Func code, must be set */
	uपूर्णांक	fcc_tbase;	/* Transmit BD base */
	uलघु	fcc_tbdstat;	/* TxBD status */
	uलघु	fcc_tbdlen;	/* TxBD करोwn counter */
	uपूर्णांक	fcc_tdptr;	/* TxBD पूर्णांकernal data poपूर्णांकer */
	uपूर्णांक	fcc_rbptr;	/* Rx BD Internal buf poपूर्णांकer */
	uपूर्णांक	fcc_tbptr;	/* Tx BD Internal buf poपूर्णांकer */
	uपूर्णांक	fcc_rcrc;	/* Rx temp CRC */
	uपूर्णांक	fcc_res2;
	uपूर्णांक	fcc_tcrc;	/* Tx temp CRC */
पूर्ण fccp_t;


/* Ethernet controller through FCC.
*/
प्रकार काष्ठा fcc_enet अणु
	fccp_t	fen_genfcc;
	uपूर्णांक	fen_statbuf;	/* Internal status buffer */
	uपूर्णांक	fen_camptr;	/* CAM address */
	uपूर्णांक	fen_cmask;	/* Constant mask क्रम CRC */
	uपूर्णांक	fen_cpres;	/* Preset CRC */
	uपूर्णांक	fen_crcec;	/* CRC Error counter */
	uपूर्णांक	fen_alec;	/* alignment error counter */
	uपूर्णांक	fen_disfc;	/* discard frame counter */
	uलघु	fen_retlim;	/* Retry limit */
	uलघु	fen_retcnt;	/* Retry counter */
	uलघु	fen_pper;	/* Persistence */
	uलघु	fen_boffcnt;	/* backoff counter */
	uपूर्णांक	fen_gaddrh;	/* Group address filter, high 32-bits */
	uपूर्णांक	fen_gaddrl;	/* Group address filter, low 32-bits */
	uलघु	fen_tfcstat;	/* out of sequence TxBD */
	uलघु	fen_tfclen;
	uपूर्णांक	fen_tfcptr;
	uलघु	fen_mflr;	/* Maximum frame length (1518) */
	uलघु	fen_paddrh;	/* MAC address */
	uलघु	fen_paddrm;
	uलघु	fen_paddrl;
	uलघु	fen_ibdcount;	/* Internal BD counter */
	uलघु	fen_ibdstart;	/* Internal BD start poपूर्णांकer */
	uलघु	fen_ibdend;	/* Internal BD end poपूर्णांकer */
	uलघु	fen_txlen;	/* Internal Tx frame length counter */
	uपूर्णांक	fen_ibdbase[8]; /* Internal use */
	uपूर्णांक	fen_iaddrh;	/* Inभागidual address filter */
	uपूर्णांक	fen_iaddrl;
	uलघु	fen_minflr;	/* Minimum frame length (64) */
	uलघु	fen_taddrh;	/* Filter transfer MAC address */
	uलघु	fen_taddrm;
	uलघु	fen_taddrl;
	uलघु	fen_padptr;	/* Poपूर्णांकer to pad byte buffer */
	uलघु	fen_cftype;	/* control frame type */
	uलघु	fen_cfrange;	/* control frame range */
	uलघु	fen_maxb;	/* maximum BD count */
	uलघु	fen_maxd1;	/* Max DMA1 length (1520) */
	uलघु	fen_maxd2;	/* Max DMA2 length (1520) */
	uलघु	fen_maxd;	/* पूर्णांकernal max DMA count */
	uलघु	fen_dmacnt;	/* पूर्णांकernal DMA counter */
	uपूर्णांक	fen_octc;	/* Total octect counter */
	uपूर्णांक	fen_colc;	/* Total collision counter */
	uपूर्णांक	fen_broc;	/* Total broadcast packet counter */
	uपूर्णांक	fen_mulc;	/* Total multicast packet count */
	uपूर्णांक	fen_uspc;	/* Total packets < 64 bytes */
	uपूर्णांक	fen_frgc;	/* Total packets < 64 bytes with errors */
	uपूर्णांक	fen_ospc;	/* Total packets > 1518 */
	uपूर्णांक	fen_jbrc;	/* Total packets > 1518 with errors */
	uपूर्णांक	fen_p64c;	/* Total packets == 64 bytes */
	uपूर्णांक	fen_p65c;	/* Total packets 64 < bytes <= 127 */
	uपूर्णांक	fen_p128c;	/* Total packets 127 < bytes <= 255 */
	uपूर्णांक	fen_p256c;	/* Total packets 256 < bytes <= 511 */
	uपूर्णांक	fen_p512c;	/* Total packets 512 < bytes <= 1023 */
	uपूर्णांक	fen_p1024c;	/* Total packets 1024 < bytes <= 1518 */
	uपूर्णांक	fen_cambuf;	/* Internal CAM buffer poपूर्णांकer */
	uलघु	fen_rfthr;	/* Received frames threshold */
	uलघु	fen_rfcnt;	/* Received frames count */
पूर्ण fcc_enet_t;

/* FCC Event/Mask रेजिस्टर as used by Ethernet.
*/
#घोषणा FCC_ENET_GRA	((uलघु)0x0080)	/* Graceful stop complete */
#घोषणा FCC_ENET_RXC	((uलघु)0x0040)	/* Control Frame Received */
#घोषणा FCC_ENET_TXC	((uलघु)0x0020)	/* Out of seq. Tx sent */
#घोषणा FCC_ENET_TXE	((uलघु)0x0010)	/* Transmit Error */
#घोषणा FCC_ENET_RXF	((uलघु)0x0008)	/* Full frame received */
#घोषणा FCC_ENET_BSY	((uलघु)0x0004)	/* Busy.  Rx Frame dropped */
#घोषणा FCC_ENET_TXB	((uलघु)0x0002)	/* A buffer was transmitted */
#घोषणा FCC_ENET_RXB	((uलघु)0x0001)	/* A buffer was received */

/* FCC Mode Register (FPSMR) as used by Ethernet.
*/
#घोषणा FCC_PSMR_HBC	((uपूर्णांक)0x80000000)	/* Enable heartbeat */
#घोषणा FCC_PSMR_FC	((uपूर्णांक)0x40000000)	/* Force Collision */
#घोषणा FCC_PSMR_SBT	((uपूर्णांक)0x20000000)	/* Stop backoff समयr */
#घोषणा FCC_PSMR_LPB	((uपूर्णांक)0x10000000)	/* Local protect. 1 = FDX */
#घोषणा FCC_PSMR_LCW	((uपूर्णांक)0x08000000)	/* Late collision select */
#घोषणा FCC_PSMR_FDE	((uपूर्णांक)0x04000000)	/* Full Duplex Enable */
#घोषणा FCC_PSMR_MON	((uपूर्णांक)0x02000000)	/* RMON Enable */
#घोषणा FCC_PSMR_PRO	((uपूर्णांक)0x00400000)	/* Promiscuous Enable */
#घोषणा FCC_PSMR_FCE	((uपूर्णांक)0x00200000)	/* Flow Control Enable */
#घोषणा FCC_PSMR_RSH	((uपूर्णांक)0x00100000)	/* Receive Short Frames */
#घोषणा FCC_PSMR_CAM	((uपूर्णांक)0x00000400)	/* CAM enable */
#घोषणा FCC_PSMR_BRO	((uपूर्णांक)0x00000200)	/* Broadcast pkt discard */
#घोषणा FCC_PSMR_ENCRC	((uपूर्णांक)0x00000080)	/* Use 32-bit CRC */

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
पूर्ण iic_t;

/* IDMA parameter RAM
*/
प्रकार काष्ठा idma अणु
	uलघु ibase;		/* IDMA buffer descriptor table base address */
	uलघु dcm;		/* DMA channel mode */
	uलघु ibdptr;		/* IDMA current buffer descriptor poपूर्णांकer */
	uलघु dpr_buf;		/* IDMA transfer buffer base address */
	uलघु buf_inv;		/* पूर्णांकernal buffer inventory */
	uलघु ss_max;		/* steady-state maximum transfer size */
	uलघु dpr_in_ptr;	/* ग_लिखो poपूर्णांकer inside the पूर्णांकernal buffer */
	uलघु sts;		/* source transfer size */
	uलघु dpr_out_ptr;	/* पढ़ो poपूर्णांकer inside the पूर्णांकernal buffer */
	uलघु seob;		/* source end of burst */
	uलघु deob;		/* destination end of burst */
	uलघु dts;		/* destination transfer size */
	uलघु ret_add;		/* वापस address when working in ERM=1 mode */
	uलघु res0;		/* reserved */
	uपूर्णांक   bd_cnt;		/* पूर्णांकernal byte count */
	uपूर्णांक   s_ptr;		/* source पूर्णांकernal data poपूर्णांकer */
	uपूर्णांक   d_ptr;		/* destination पूर्णांकernal data poपूर्णांकer */
	uपूर्णांक   istate;		/* पूर्णांकernal state */
	u_अक्षर res1[20];	/* pad to 64-byte length */
पूर्ण idma_t;

/* DMA channel mode bit fields
*/
#घोषणा IDMA_DCM_FB		((uलघु)0x8000) /* fly-by mode */
#घोषणा IDMA_DCM_LP		((uलघु)0x4000) /* low priority */
#घोषणा IDMA_DCM_TC2		((uलघु)0x0400) /* value driven on TC[2] */
#घोषणा IDMA_DCM_DMA_WRAP_MASK	((uलघु)0x01c0) /* mask क्रम DMA wrap */
#घोषणा IDMA_DCM_DMA_WRAP_64	((uलघु)0x0000) /* 64-byte DMA xfer buffer */
#घोषणा IDMA_DCM_DMA_WRAP_128	((uलघु)0x0040) /* 128-byte DMA xfer buffer */
#घोषणा IDMA_DCM_DMA_WRAP_256	((uलघु)0x0080) /* 256-byte DMA xfer buffer */
#घोषणा IDMA_DCM_DMA_WRAP_512	((uलघु)0x00c0) /* 512-byte DMA xfer buffer */
#घोषणा IDMA_DCM_DMA_WRAP_1024	((uलघु)0x0100) /* 1024-byte DMA xfer buffer */
#घोषणा IDMA_DCM_DMA_WRAP_2048	((uलघु)0x0140) /* 2048-byte DMA xfer buffer */
#घोषणा IDMA_DCM_SINC		((uलघु)0x0020) /* source inc addr */
#घोषणा IDMA_DCM_DINC		((uलघु)0x0010) /* destination inc addr */
#घोषणा IDMA_DCM_ERM		((uलघु)0x0008) /* बाह्यal request mode */
#घोषणा IDMA_DCM_DT		((uलघु)0x0004) /* DONE treaपंचांगent */
#घोषणा IDMA_DCM_SD_MASK	((uलघु)0x0003) /* mask क्रम SD bit field */
#घोषणा IDMA_DCM_SD_MEM2MEM	((uलघु)0x0000) /* memory-to-memory xfer */
#घोषणा IDMA_DCM_SD_PER2MEM	((uलघु)0x0002) /* peripheral-to-memory xfer */
#घोषणा IDMA_DCM_SD_MEM2PER	((uलघु)0x0001) /* memory-to-peripheral xfer */

/* IDMA Buffer Descriptors
*/
प्रकार काष्ठा idma_bd अणु
	uपूर्णांक flags;
	uपूर्णांक len;	/* data length */
	uपूर्णांक src;	/* source data buffer poपूर्णांकer */
	uपूर्णांक dst;	/* destination data buffer poपूर्णांकer */
पूर्ण idma_bd_t;

/* IDMA buffer descriptor flag bit fields
*/
#घोषणा IDMA_BD_V	((uपूर्णांक)0x80000000)	/* valid */
#घोषणा IDMA_BD_W	((uपूर्णांक)0x20000000)	/* wrap */
#घोषणा IDMA_BD_I	((uपूर्णांक)0x10000000)	/* पूर्णांकerrupt */
#घोषणा IDMA_BD_L	((uपूर्णांक)0x08000000)	/* last */
#घोषणा IDMA_BD_CM	((uपूर्णांक)0x02000000)	/* continuous mode */
#घोषणा IDMA_BD_SDN	((uपूर्णांक)0x00400000)	/* source करोne */
#घोषणा IDMA_BD_DDN	((uपूर्णांक)0x00200000)	/* destination करोne */
#घोषणा IDMA_BD_DGBL	((uपूर्णांक)0x00100000)	/* destination global */
#घोषणा IDMA_BD_DBO_LE	((uपूर्णांक)0x00040000)	/* little-end dest byte order */
#घोषणा IDMA_BD_DBO_BE	((uपूर्णांक)0x00080000)	/* big-end dest byte order */
#घोषणा IDMA_BD_DDTB	((uपूर्णांक)0x00010000)	/* destination data bus */
#घोषणा IDMA_BD_SGBL	((uपूर्णांक)0x00002000)	/* source global */
#घोषणा IDMA_BD_SBO_LE	((uपूर्णांक)0x00000800)	/* little-end src byte order */
#घोषणा IDMA_BD_SBO_BE	((uपूर्णांक)0x00001000)	/* big-end src byte order */
#घोषणा IDMA_BD_SDTB	((uपूर्णांक)0x00000200)	/* source data bus */

/* per-channel IDMA रेजिस्टरs
*/
प्रकार काष्ठा im_idma अणु
	u_अक्षर idsr;			/* IDMAn event status रेजिस्टर */
	u_अक्षर res0[3];
	u_अक्षर idmr;			/* IDMAn event mask रेजिस्टर */
	u_अक्षर res1[3];
पूर्ण im_idma_t;

/* IDMA event रेजिस्टर bit fields
*/
#घोषणा IDMA_EVENT_SC	((अचिन्हित अक्षर)0x08)	/* stop completed */
#घोषणा IDMA_EVENT_OB	((अचिन्हित अक्षर)0x04)	/* out of buffers */
#घोषणा IDMA_EVENT_EDN	((अचिन्हित अक्षर)0x02)	/* बाह्यal DONE निश्चितed */
#घोषणा IDMA_EVENT_BC	((अचिन्हित अक्षर)0x01)	/* buffer descriptor complete */

/* RISC Controller Configuration Register (RCCR) bit fields
*/
#घोषणा RCCR_TIME	((uपूर्णांक)0x80000000) /* समयr enable */
#घोषणा RCCR_TIMEP_MASK	((uपूर्णांक)0x3f000000) /* mask क्रम समयr period bit field */
#घोषणा RCCR_DR0M	((uपूर्णांक)0x00800000) /* IDMA0 request mode */
#घोषणा RCCR_DR1M	((uपूर्णांक)0x00400000) /* IDMA1 request mode */
#घोषणा RCCR_DR2M	((uपूर्णांक)0x00000080) /* IDMA2 request mode */
#घोषणा RCCR_DR3M	((uपूर्णांक)0x00000040) /* IDMA3 request mode */
#घोषणा RCCR_DR0QP_MASK	((uपूर्णांक)0x00300000) /* mask क्रम IDMA0 req priority */
#घोषणा RCCR_DR0QP_HIGH ((uपूर्णांक)0x00000000) /* IDMA0 has high req priority */
#घोषणा RCCR_DR0QP_MED	((uपूर्णांक)0x00100000) /* IDMA0 has medium req priority */
#घोषणा RCCR_DR0QP_LOW	((uपूर्णांक)0x00200000) /* IDMA0 has low req priority */
#घोषणा RCCR_DR1QP_MASK	((uपूर्णांक)0x00030000) /* mask क्रम IDMA1 req priority */
#घोषणा RCCR_DR1QP_HIGH ((uपूर्णांक)0x00000000) /* IDMA1 has high req priority */
#घोषणा RCCR_DR1QP_MED	((uपूर्णांक)0x00010000) /* IDMA1 has medium req priority */
#घोषणा RCCR_DR1QP_LOW	((uपूर्णांक)0x00020000) /* IDMA1 has low req priority */
#घोषणा RCCR_DR2QP_MASK	((uपूर्णांक)0x00000030) /* mask क्रम IDMA2 req priority */
#घोषणा RCCR_DR2QP_HIGH ((uपूर्णांक)0x00000000) /* IDMA2 has high req priority */
#घोषणा RCCR_DR2QP_MED	((uपूर्णांक)0x00000010) /* IDMA2 has medium req priority */
#घोषणा RCCR_DR2QP_LOW	((uपूर्णांक)0x00000020) /* IDMA2 has low req priority */
#घोषणा RCCR_DR3QP_MASK	((uपूर्णांक)0x00000003) /* mask क्रम IDMA3 req priority */
#घोषणा RCCR_DR3QP_HIGH ((uपूर्णांक)0x00000000) /* IDMA3 has high req priority */
#घोषणा RCCR_DR3QP_MED	((uपूर्णांक)0x00000001) /* IDMA3 has medium req priority */
#घोषणा RCCR_DR3QP_LOW	((uपूर्णांक)0x00000002) /* IDMA3 has low req priority */
#घोषणा RCCR_EIE	((uपूर्णांक)0x00080000) /* बाह्यal पूर्णांकerrupt enable */
#घोषणा RCCR_SCD	((uपूर्णांक)0x00040000) /* scheduler configuration */
#घोषणा RCCR_ERAM_MASK	((uपूर्णांक)0x0000e000) /* mask क्रम enable RAM microcode */
#घोषणा RCCR_ERAM_0KB	((uपूर्णांक)0x00000000) /* use 0KB of dpram क्रम microcode */
#घोषणा RCCR_ERAM_2KB	((uपूर्णांक)0x00002000) /* use 2KB of dpram क्रम microcode */
#घोषणा RCCR_ERAM_4KB	((uपूर्णांक)0x00004000) /* use 4KB of dpram क्रम microcode */
#घोषणा RCCR_ERAM_6KB	((uपूर्णांक)0x00006000) /* use 6KB of dpram क्रम microcode */
#घोषणा RCCR_ERAM_8KB	((uपूर्णांक)0x00008000) /* use 8KB of dpram क्रम microcode */
#घोषणा RCCR_ERAM_10KB	((uपूर्णांक)0x0000a000) /* use 10KB of dpram क्रम microcode */
#घोषणा RCCR_ERAM_12KB	((uपूर्णांक)0x0000c000) /* use 12KB of dpram क्रम microcode */
#घोषणा RCCR_EDM0	((uपूर्णांक)0x00000800) /* DREQ0 edge detect mode */
#घोषणा RCCR_EDM1	((uपूर्णांक)0x00000400) /* DREQ1 edge detect mode */
#घोषणा RCCR_EDM2	((uपूर्णांक)0x00000200) /* DREQ2 edge detect mode */
#घोषणा RCCR_EDM3	((uपूर्णांक)0x00000100) /* DREQ3 edge detect mode */
#घोषणा RCCR_DEM01	((uपूर्णांक)0x00000008) /* DONE0/DONE1 edge detect mode */
#घोषणा RCCR_DEM23	((uपूर्णांक)0x00000004) /* DONE2/DONE3 edge detect mode */

/*-----------------------------------------------------------------------
 * CMXFCR - CMX FCC Clock Route Register
 */
#घोषणा CMXFCR_FC1         0x40000000   /* FCC1 connection              */
#घोषणा CMXFCR_RF1CS_MSK   0x38000000   /* Receive FCC1 Clock Source Mask */
#घोषणा CMXFCR_TF1CS_MSK   0x07000000   /* Transmit FCC1 Clock Source Mask */
#घोषणा CMXFCR_FC2         0x00400000   /* FCC2 connection              */
#घोषणा CMXFCR_RF2CS_MSK   0x00380000   /* Receive FCC2 Clock Source Mask */
#घोषणा CMXFCR_TF2CS_MSK   0x00070000   /* Transmit FCC2 Clock Source Mask */
#घोषणा CMXFCR_FC3         0x00004000   /* FCC3 connection              */
#घोषणा CMXFCR_RF3CS_MSK   0x00003800   /* Receive FCC3 Clock Source Mask */
#घोषणा CMXFCR_TF3CS_MSK   0x00000700   /* Transmit FCC3 Clock Source Mask */

#घोषणा CMXFCR_RF1CS_BRG5  0x00000000   /* Receive FCC1 Clock Source is BRG5 */
#घोषणा CMXFCR_RF1CS_BRG6  0x08000000   /* Receive FCC1 Clock Source is BRG6 */
#घोषणा CMXFCR_RF1CS_BRG7  0x10000000   /* Receive FCC1 Clock Source is BRG7 */
#घोषणा CMXFCR_RF1CS_BRG8  0x18000000   /* Receive FCC1 Clock Source is BRG8 */
#घोषणा CMXFCR_RF1CS_CLK9  0x20000000   /* Receive FCC1 Clock Source is CLK9 */
#घोषणा CMXFCR_RF1CS_CLK10 0x28000000   /* Receive FCC1 Clock Source is CLK10 */
#घोषणा CMXFCR_RF1CS_CLK11 0x30000000   /* Receive FCC1 Clock Source is CLK11 */
#घोषणा CMXFCR_RF1CS_CLK12 0x38000000   /* Receive FCC1 Clock Source is CLK12 */

#घोषणा CMXFCR_TF1CS_BRG5  0x00000000   /* Transmit FCC1 Clock Source is BRG5 */
#घोषणा CMXFCR_TF1CS_BRG6  0x01000000   /* Transmit FCC1 Clock Source is BRG6 */
#घोषणा CMXFCR_TF1CS_BRG7  0x02000000   /* Transmit FCC1 Clock Source is BRG7 */
#घोषणा CMXFCR_TF1CS_BRG8  0x03000000   /* Transmit FCC1 Clock Source is BRG8 */
#घोषणा CMXFCR_TF1CS_CLK9  0x04000000   /* Transmit FCC1 Clock Source is CLK9 */
#घोषणा CMXFCR_TF1CS_CLK10 0x05000000   /* Transmit FCC1 Clock Source is CLK10 */
#घोषणा CMXFCR_TF1CS_CLK11 0x06000000   /* Transmit FCC1 Clock Source is CLK11 */
#घोषणा CMXFCR_TF1CS_CLK12 0x07000000   /* Transmit FCC1 Clock Source is CLK12 */

#घोषणा CMXFCR_RF2CS_BRG5  0x00000000   /* Receive FCC2 Clock Source is BRG5 */
#घोषणा CMXFCR_RF2CS_BRG6  0x00080000   /* Receive FCC2 Clock Source is BRG6 */
#घोषणा CMXFCR_RF2CS_BRG7  0x00100000   /* Receive FCC2 Clock Source is BRG7 */
#घोषणा CMXFCR_RF2CS_BRG8  0x00180000   /* Receive FCC2 Clock Source is BRG8 */
#घोषणा CMXFCR_RF2CS_CLK13 0x00200000   /* Receive FCC2 Clock Source is CLK13 */
#घोषणा CMXFCR_RF2CS_CLK14 0x00280000   /* Receive FCC2 Clock Source is CLK14 */
#घोषणा CMXFCR_RF2CS_CLK15 0x00300000   /* Receive FCC2 Clock Source is CLK15 */
#घोषणा CMXFCR_RF2CS_CLK16 0x00380000   /* Receive FCC2 Clock Source is CLK16 */

#घोषणा CMXFCR_TF2CS_BRG5  0x00000000   /* Transmit FCC2 Clock Source is BRG5 */
#घोषणा CMXFCR_TF2CS_BRG6  0x00010000   /* Transmit FCC2 Clock Source is BRG6 */
#घोषणा CMXFCR_TF2CS_BRG7  0x00020000   /* Transmit FCC2 Clock Source is BRG7 */
#घोषणा CMXFCR_TF2CS_BRG8  0x00030000   /* Transmit FCC2 Clock Source is BRG8 */
#घोषणा CMXFCR_TF2CS_CLK13 0x00040000   /* Transmit FCC2 Clock Source is CLK13 */
#घोषणा CMXFCR_TF2CS_CLK14 0x00050000   /* Transmit FCC2 Clock Source is CLK14 */
#घोषणा CMXFCR_TF2CS_CLK15 0x00060000   /* Transmit FCC2 Clock Source is CLK15 */
#घोषणा CMXFCR_TF2CS_CLK16 0x00070000   /* Transmit FCC2 Clock Source is CLK16 */

#घोषणा CMXFCR_RF3CS_BRG5  0x00000000   /* Receive FCC3 Clock Source is BRG5 */
#घोषणा CMXFCR_RF3CS_BRG6  0x00000800   /* Receive FCC3 Clock Source is BRG6 */
#घोषणा CMXFCR_RF3CS_BRG7  0x00001000   /* Receive FCC3 Clock Source is BRG7 */
#घोषणा CMXFCR_RF3CS_BRG8  0x00001800   /* Receive FCC3 Clock Source is BRG8 */
#घोषणा CMXFCR_RF3CS_CLK13 0x00002000   /* Receive FCC3 Clock Source is CLK13 */
#घोषणा CMXFCR_RF3CS_CLK14 0x00002800   /* Receive FCC3 Clock Source is CLK14 */
#घोषणा CMXFCR_RF3CS_CLK15 0x00003000   /* Receive FCC3 Clock Source is CLK15 */
#घोषणा CMXFCR_RF3CS_CLK16 0x00003800   /* Receive FCC3 Clock Source is CLK16 */

#घोषणा CMXFCR_TF3CS_BRG5  0x00000000   /* Transmit FCC3 Clock Source is BRG5 */
#घोषणा CMXFCR_TF3CS_BRG6  0x00000100   /* Transmit FCC3 Clock Source is BRG6 */
#घोषणा CMXFCR_TF3CS_BRG7  0x00000200   /* Transmit FCC3 Clock Source is BRG7 */
#घोषणा CMXFCR_TF3CS_BRG8  0x00000300   /* Transmit FCC3 Clock Source is BRG8 */
#घोषणा CMXFCR_TF3CS_CLK13 0x00000400   /* Transmit FCC3 Clock Source is CLK13 */
#घोषणा CMXFCR_TF3CS_CLK14 0x00000500   /* Transmit FCC3 Clock Source is CLK14 */
#घोषणा CMXFCR_TF3CS_CLK15 0x00000600   /* Transmit FCC3 Clock Source is CLK15 */
#घोषणा CMXFCR_TF3CS_CLK16 0x00000700   /* Transmit FCC3 Clock Source is CLK16 */

/*-----------------------------------------------------------------------
 * CMXSCR - CMX SCC Clock Route Register
 */
#घोषणा CMXSCR_GR1         0x80000000   /* Grant Support of SCC1        */
#घोषणा CMXSCR_SC1         0x40000000   /* SCC1 connection              */
#घोषणा CMXSCR_RS1CS_MSK   0x38000000   /* Receive SCC1 Clock Source Mask */
#घोषणा CMXSCR_TS1CS_MSK   0x07000000   /* Transmit SCC1 Clock Source Mask */
#घोषणा CMXSCR_GR2         0x00800000   /* Grant Support of SCC2        */
#घोषणा CMXSCR_SC2         0x00400000   /* SCC2 connection              */
#घोषणा CMXSCR_RS2CS_MSK   0x00380000   /* Receive SCC2 Clock Source Mask */
#घोषणा CMXSCR_TS2CS_MSK   0x00070000   /* Transmit SCC2 Clock Source Mask */
#घोषणा CMXSCR_GR3         0x00008000   /* Grant Support of SCC3        */
#घोषणा CMXSCR_SC3         0x00004000   /* SCC3 connection              */
#घोषणा CMXSCR_RS3CS_MSK   0x00003800   /* Receive SCC3 Clock Source Mask */
#घोषणा CMXSCR_TS3CS_MSK   0x00000700   /* Transmit SCC3 Clock Source Mask */
#घोषणा CMXSCR_GR4         0x00000080   /* Grant Support of SCC4        */
#घोषणा CMXSCR_SC4         0x00000040   /* SCC4 connection              */
#घोषणा CMXSCR_RS4CS_MSK   0x00000038   /* Receive SCC4 Clock Source Mask */
#घोषणा CMXSCR_TS4CS_MSK   0x00000007   /* Transmit SCC4 Clock Source Mask */

#घोषणा CMXSCR_RS1CS_BRG1  0x00000000   /* SCC1 Rx Clock Source is BRG1 */
#घोषणा CMXSCR_RS1CS_BRG2  0x08000000   /* SCC1 Rx Clock Source is BRG2 */
#घोषणा CMXSCR_RS1CS_BRG3  0x10000000   /* SCC1 Rx Clock Source is BRG3 */
#घोषणा CMXSCR_RS1CS_BRG4  0x18000000   /* SCC1 Rx Clock Source is BRG4 */
#घोषणा CMXSCR_RS1CS_CLK11 0x20000000   /* SCC1 Rx Clock Source is CLK11 */
#घोषणा CMXSCR_RS1CS_CLK12 0x28000000   /* SCC1 Rx Clock Source is CLK12 */
#घोषणा CMXSCR_RS1CS_CLK3  0x30000000   /* SCC1 Rx Clock Source is CLK3 */
#घोषणा CMXSCR_RS1CS_CLK4  0x38000000   /* SCC1 Rx Clock Source is CLK4 */

#घोषणा CMXSCR_TS1CS_BRG1  0x00000000   /* SCC1 Tx Clock Source is BRG1 */
#घोषणा CMXSCR_TS1CS_BRG2  0x01000000   /* SCC1 Tx Clock Source is BRG2 */
#घोषणा CMXSCR_TS1CS_BRG3  0x02000000   /* SCC1 Tx Clock Source is BRG3 */
#घोषणा CMXSCR_TS1CS_BRG4  0x03000000   /* SCC1 Tx Clock Source is BRG4 */
#घोषणा CMXSCR_TS1CS_CLK11 0x04000000   /* SCC1 Tx Clock Source is CLK11 */
#घोषणा CMXSCR_TS1CS_CLK12 0x05000000   /* SCC1 Tx Clock Source is CLK12 */
#घोषणा CMXSCR_TS1CS_CLK3  0x06000000   /* SCC1 Tx Clock Source is CLK3 */
#घोषणा CMXSCR_TS1CS_CLK4  0x07000000   /* SCC1 Tx Clock Source is CLK4 */

#घोषणा CMXSCR_RS2CS_BRG1  0x00000000   /* SCC2 Rx Clock Source is BRG1 */
#घोषणा CMXSCR_RS2CS_BRG2  0x00080000   /* SCC2 Rx Clock Source is BRG2 */
#घोषणा CMXSCR_RS2CS_BRG3  0x00100000   /* SCC2 Rx Clock Source is BRG3 */
#घोषणा CMXSCR_RS2CS_BRG4  0x00180000   /* SCC2 Rx Clock Source is BRG4 */
#घोषणा CMXSCR_RS2CS_CLK11 0x00200000   /* SCC2 Rx Clock Source is CLK11 */
#घोषणा CMXSCR_RS2CS_CLK12 0x00280000   /* SCC2 Rx Clock Source is CLK12 */
#घोषणा CMXSCR_RS2CS_CLK3  0x00300000   /* SCC2 Rx Clock Source is CLK3 */
#घोषणा CMXSCR_RS2CS_CLK4  0x00380000   /* SCC2 Rx Clock Source is CLK4 */

#घोषणा CMXSCR_TS2CS_BRG1  0x00000000   /* SCC2 Tx Clock Source is BRG1 */
#घोषणा CMXSCR_TS2CS_BRG2  0x00010000   /* SCC2 Tx Clock Source is BRG2 */
#घोषणा CMXSCR_TS2CS_BRG3  0x00020000   /* SCC2 Tx Clock Source is BRG3 */
#घोषणा CMXSCR_TS2CS_BRG4  0x00030000   /* SCC2 Tx Clock Source is BRG4 */
#घोषणा CMXSCR_TS2CS_CLK11 0x00040000   /* SCC2 Tx Clock Source is CLK11 */
#घोषणा CMXSCR_TS2CS_CLK12 0x00050000   /* SCC2 Tx Clock Source is CLK12 */
#घोषणा CMXSCR_TS2CS_CLK3  0x00060000   /* SCC2 Tx Clock Source is CLK3 */
#घोषणा CMXSCR_TS2CS_CLK4  0x00070000   /* SCC2 Tx Clock Source is CLK4 */

#घोषणा CMXSCR_RS3CS_BRG1  0x00000000   /* SCC3 Rx Clock Source is BRG1 */
#घोषणा CMXSCR_RS3CS_BRG2  0x00000800   /* SCC3 Rx Clock Source is BRG2 */
#घोषणा CMXSCR_RS3CS_BRG3  0x00001000   /* SCC3 Rx Clock Source is BRG3 */
#घोषणा CMXSCR_RS3CS_BRG4  0x00001800   /* SCC3 Rx Clock Source is BRG4 */
#घोषणा CMXSCR_RS3CS_CLK5  0x00002000   /* SCC3 Rx Clock Source is CLK5 */
#घोषणा CMXSCR_RS3CS_CLK6  0x00002800   /* SCC3 Rx Clock Source is CLK6 */
#घोषणा CMXSCR_RS3CS_CLK7  0x00003000   /* SCC3 Rx Clock Source is CLK7 */
#घोषणा CMXSCR_RS3CS_CLK8  0x00003800   /* SCC3 Rx Clock Source is CLK8 */

#घोषणा CMXSCR_TS3CS_BRG1  0x00000000   /* SCC3 Tx Clock Source is BRG1 */
#घोषणा CMXSCR_TS3CS_BRG2  0x00000100   /* SCC3 Tx Clock Source is BRG2 */
#घोषणा CMXSCR_TS3CS_BRG3  0x00000200   /* SCC3 Tx Clock Source is BRG3 */
#घोषणा CMXSCR_TS3CS_BRG4  0x00000300   /* SCC3 Tx Clock Source is BRG4 */
#घोषणा CMXSCR_TS3CS_CLK5  0x00000400   /* SCC3 Tx Clock Source is CLK5 */
#घोषणा CMXSCR_TS3CS_CLK6  0x00000500   /* SCC3 Tx Clock Source is CLK6 */
#घोषणा CMXSCR_TS3CS_CLK7  0x00000600   /* SCC3 Tx Clock Source is CLK7 */
#घोषणा CMXSCR_TS3CS_CLK8  0x00000700   /* SCC3 Tx Clock Source is CLK8 */

#घोषणा CMXSCR_RS4CS_BRG1  0x00000000   /* SCC4 Rx Clock Source is BRG1 */
#घोषणा CMXSCR_RS4CS_BRG2  0x00000008   /* SCC4 Rx Clock Source is BRG2 */
#घोषणा CMXSCR_RS4CS_BRG3  0x00000010   /* SCC4 Rx Clock Source is BRG3 */
#घोषणा CMXSCR_RS4CS_BRG4  0x00000018   /* SCC4 Rx Clock Source is BRG4 */
#घोषणा CMXSCR_RS4CS_CLK5  0x00000020   /* SCC4 Rx Clock Source is CLK5 */
#घोषणा CMXSCR_RS4CS_CLK6  0x00000028   /* SCC4 Rx Clock Source is CLK6 */
#घोषणा CMXSCR_RS4CS_CLK7  0x00000030   /* SCC4 Rx Clock Source is CLK7 */
#घोषणा CMXSCR_RS4CS_CLK8  0x00000038   /* SCC4 Rx Clock Source is CLK8 */

#घोषणा CMXSCR_TS4CS_BRG1  0x00000000   /* SCC4 Tx Clock Source is BRG1 */
#घोषणा CMXSCR_TS4CS_BRG2  0x00000001   /* SCC4 Tx Clock Source is BRG2 */
#घोषणा CMXSCR_TS4CS_BRG3  0x00000002   /* SCC4 Tx Clock Source is BRG3 */
#घोषणा CMXSCR_TS4CS_BRG4  0x00000003   /* SCC4 Tx Clock Source is BRG4 */
#घोषणा CMXSCR_TS4CS_CLK5  0x00000004   /* SCC4 Tx Clock Source is CLK5 */
#घोषणा CMXSCR_TS4CS_CLK6  0x00000005   /* SCC4 Tx Clock Source is CLK6 */
#घोषणा CMXSCR_TS4CS_CLK7  0x00000006   /* SCC4 Tx Clock Source is CLK7 */
#घोषणा CMXSCR_TS4CS_CLK8  0x00000007   /* SCC4 Tx Clock Source is CLK8 */

/*-----------------------------------------------------------------------
 * SIUMCR - SIU Module Configuration Register				 4-31
 */
#घोषणा SIUMCR_BBD	0x80000000	/* Bus Busy Disable		*/
#घोषणा SIUMCR_ESE	0x40000000	/* External Snoop Enable	*/
#घोषणा SIUMCR_PBSE	0x20000000	/* Parity Byte Select Enable	*/
#घोषणा SIUMCR_CDIS	0x10000000	/* Core Disable			*/
#घोषणा SIUMCR_DPPC00	0x00000000	/* Data Parity Pins Configuration*/
#घोषणा SIUMCR_DPPC01	0x04000000	/* - " -			*/
#घोषणा SIUMCR_DPPC10	0x08000000	/* - " -			*/
#घोषणा SIUMCR_DPPC11	0x0c000000	/* - " -			*/
#घोषणा SIUMCR_L2CPC00	0x00000000	/* L2 Cache Pins Configuration	*/
#घोषणा SIUMCR_L2CPC01	0x01000000	/* - " -			*/
#घोषणा SIUMCR_L2CPC10	0x02000000	/* - " -			*/
#घोषणा SIUMCR_L2CPC11	0x03000000	/* - " -			*/
#घोषणा SIUMCR_LBPC00	0x00000000	/* Local Bus Pins Configuration	*/
#घोषणा SIUMCR_LBPC01	0x00400000	/* - " -			*/
#घोषणा SIUMCR_LBPC10	0x00800000	/* - " -			*/
#घोषणा SIUMCR_LBPC11	0x00c00000	/* - " -			*/
#घोषणा SIUMCR_APPC00	0x00000000	/* Address Parity Pins Configuration*/
#घोषणा SIUMCR_APPC01	0x00100000	/* - " -			*/
#घोषणा SIUMCR_APPC10	0x00200000	/* - " -			*/
#घोषणा SIUMCR_APPC11	0x00300000	/* - " -			*/
#घोषणा SIUMCR_CS10PC00	0x00000000	/* CS10 Pin Configuration	*/
#घोषणा SIUMCR_CS10PC01	0x00040000	/* - " -			*/
#घोषणा SIUMCR_CS10PC10	0x00080000	/* - " -			*/
#घोषणा SIUMCR_CS10PC11	0x000c0000	/* - " -			*/
#घोषणा SIUMCR_BCTLC00	0x00000000	/* Buffer Control Configuration	*/
#घोषणा SIUMCR_BCTLC01	0x00010000	/* - " -			*/
#घोषणा SIUMCR_BCTLC10	0x00020000	/* - " -			*/
#घोषणा SIUMCR_BCTLC11	0x00030000	/* - " -			*/
#घोषणा SIUMCR_MMR00	0x00000000	/* Mask Masters Requests	*/
#घोषणा SIUMCR_MMR01	0x00004000	/* - " -			*/
#घोषणा SIUMCR_MMR10	0x00008000	/* - " -			*/
#घोषणा SIUMCR_MMR11	0x0000c000	/* - " -			*/
#घोषणा SIUMCR_LPBSE	0x00002000	/* LocalBus Parity Byte Select Enable*/

/*-----------------------------------------------------------------------
 * SCCR - System Clock Control Register					 9-8
*/
#घोषणा SCCR_PCI_MODE	0x00000100	/* PCI Mode	*/
#घोषणा SCCR_PCI_MODCK	0x00000080	/* Value of PCI_MODCK pin	*/
#घोषणा SCCR_PCIDF_MSK	0x00000078	/* PCI भागision factor	*/
#घोषणा SCCR_PCIDF_SHIFT 3

#अगर_अघोषित CPM_IMMR_OFFSET
#घोषणा CPM_IMMR_OFFSET	0x101a8
#पूर्ण_अगर

#घोषणा FCC_PSMR_RMII	((uपूर्णांक)0x00020000)	/* Use RMII पूर्णांकerface */

/* FCC iop & घड़ी configuration. BSP code is responsible to define Fx_RXCLK & Fx_TXCLK
 * in order to use घड़ी-computing stuff below क्रम the FCC x
 */

/* Automatically generates रेजिस्टर configurations */
#घोषणा PC_CLK(x)	((uपूर्णांक)(1<<(x-1)))	/* FCC CLK I/O ports */

#घोषणा CMXFCR_RF1CS(x)	((uपूर्णांक)((x-5)<<27))	/* FCC1 Receive Clock Source */
#घोषणा CMXFCR_TF1CS(x)	((uपूर्णांक)((x-5)<<24))	/* FCC1 Transmit Clock Source */
#घोषणा CMXFCR_RF2CS(x)	((uपूर्णांक)((x-9)<<19))	/* FCC2 Receive Clock Source */
#घोषणा CMXFCR_TF2CS(x) ((uपूर्णांक)((x-9)<<16))	/* FCC2 Transmit Clock Source */
#घोषणा CMXFCR_RF3CS(x)	((uपूर्णांक)((x-9)<<11))	/* FCC3 Receive Clock Source */
#घोषणा CMXFCR_TF3CS(x) ((uपूर्णांक)((x-9)<<8))	/* FCC3 Transmit Clock Source */

#घोषणा PC_F1RXCLK	PC_CLK(F1_RXCLK)
#घोषणा PC_F1TXCLK	PC_CLK(F1_TXCLK)
#घोषणा CMX1_CLK_ROUTE	(CMXFCR_RF1CS(F1_RXCLK) | CMXFCR_TF1CS(F1_TXCLK))
#घोषणा CMX1_CLK_MASK	((uपूर्णांक)0xff000000)

#घोषणा PC_F2RXCLK	PC_CLK(F2_RXCLK)
#घोषणा PC_F2TXCLK	PC_CLK(F2_TXCLK)
#घोषणा CMX2_CLK_ROUTE	(CMXFCR_RF2CS(F2_RXCLK) | CMXFCR_TF2CS(F2_TXCLK))
#घोषणा CMX2_CLK_MASK	((uपूर्णांक)0x00ff0000)

#घोषणा PC_F3RXCLK	PC_CLK(F3_RXCLK)
#घोषणा PC_F3TXCLK	PC_CLK(F3_TXCLK)
#घोषणा CMX3_CLK_ROUTE	(CMXFCR_RF3CS(F3_RXCLK) | CMXFCR_TF3CS(F3_TXCLK))
#घोषणा CMX3_CLK_MASK	((uपूर्णांक)0x0000ff00)

#घोषणा CPMUX_CLK_MASK (CMX3_CLK_MASK | CMX2_CLK_MASK)
#घोषणा CPMUX_CLK_ROUTE (CMX3_CLK_ROUTE | CMX2_CLK_ROUTE)

#घोषणा CLK_TRX (PC_F3TXCLK | PC_F3RXCLK | PC_F2TXCLK | PC_F2RXCLK)

/* I/O Pin assignment क्रम FCC1.  I करोn't yet know the best way to करो this,
 * but there is little variation among the choices.
 */
#घोषणा PA1_COL		0x00000001U
#घोषणा PA1_CRS		0x00000002U
#घोषणा PA1_TXER	0x00000004U
#घोषणा PA1_TXEN	0x00000008U
#घोषणा PA1_RXDV	0x00000010U
#घोषणा PA1_RXER	0x00000020U
#घोषणा PA1_TXDAT	0x00003c00U
#घोषणा PA1_RXDAT	0x0003c000U
#घोषणा PA1_PSORA0	(PA1_RXDAT | PA1_TXDAT)
#घोषणा PA1_PSORA1	(PA1_COL | PA1_CRS | PA1_TXER | PA1_TXEN | \
		PA1_RXDV | PA1_RXER)
#घोषणा PA1_सूचीA0	(PA1_RXDAT | PA1_CRS | PA1_COL | PA1_RXER | PA1_RXDV)
#घोषणा PA1_सूचीA1	(PA1_TXDAT | PA1_TXEN | PA1_TXER)


/* I/O Pin assignment क्रम FCC2.  I करोn't yet know the best way to करो this,
 * but there is little variation among the choices.
 */
#घोषणा PB2_TXER	0x00000001U
#घोषणा PB2_RXDV	0x00000002U
#घोषणा PB2_TXEN	0x00000004U
#घोषणा PB2_RXER	0x00000008U
#घोषणा PB2_COL		0x00000010U
#घोषणा PB2_CRS		0x00000020U
#घोषणा PB2_TXDAT	0x000003c0U
#घोषणा PB2_RXDAT	0x00003c00U
#घोषणा PB2_PSORB0	(PB2_RXDAT | PB2_TXDAT | PB2_CRS | PB2_COL | \
		PB2_RXER | PB2_RXDV | PB2_TXER)
#घोषणा PB2_PSORB1	(PB2_TXEN)
#घोषणा PB2_सूचीB0	(PB2_RXDAT | PB2_CRS | PB2_COL | PB2_RXER | PB2_RXDV)
#घोषणा PB2_सूचीB1	(PB2_TXDAT | PB2_TXEN | PB2_TXER)


/* I/O Pin assignment क्रम FCC3.  I करोn't yet know the best way to करो this,
 * but there is little variation among the choices.
 */
#घोषणा PB3_RXDV	0x00004000U
#घोषणा PB3_RXER	0x00008000U
#घोषणा PB3_TXER	0x00010000U
#घोषणा PB3_TXEN	0x00020000U
#घोषणा PB3_COL		0x00040000U
#घोषणा PB3_CRS		0x00080000U
#घोषणा PB3_TXDAT	0x0f000000U
#घोषणा PC3_TXDAT	0x00000010U
#घोषणा PB3_RXDAT	0x00f00000U
#घोषणा PB3_PSORB0	(PB3_RXDAT | PB3_TXDAT | PB3_CRS | PB3_COL | \
		PB3_RXER | PB3_RXDV | PB3_TXER | PB3_TXEN)
#घोषणा PB3_PSORB1	0
#घोषणा PB3_सूचीB0	(PB3_RXDAT | PB3_CRS | PB3_COL | PB3_RXER | PB3_RXDV)
#घोषणा PB3_सूचीB1	(PB3_TXDAT | PB3_TXEN | PB3_TXER)
#घोषणा PC3_सूचीC1	(PC3_TXDAT)

/* Handy macro to specअगरy mem क्रम FCCs*/
#घोषणा FCC_MEM_OFFSET(x) (CPM_FCC_SPECIAL_BASE + (x*128))
#घोषणा FCC1_MEM_OFFSET FCC_MEM_OFFSET(0)
#घोषणा FCC2_MEM_OFFSET FCC_MEM_OFFSET(1)
#घोषणा FCC3_MEM_OFFSET FCC_MEM_OFFSET(2)

/* Clocks and GRG's */

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
	CPM_CLK_FCC1,
	CPM_CLK_FCC2,
	CPM_CLK_FCC3,
	CPM_CLK_SMC1,
	CPM_CLK_SMC2,
पूर्ण;

क्रमागत cpm_clk अणु
	CPM_CLK_NONE = 0,
	CPM_BRG1,	/* Baud Rate Generator  1 */
	CPM_BRG2,	/* Baud Rate Generator  2 */
	CPM_BRG3,	/* Baud Rate Generator  3 */
	CPM_BRG4,	/* Baud Rate Generator  4 */
	CPM_BRG5,	/* Baud Rate Generator  5 */
	CPM_BRG6,	/* Baud Rate Generator  6 */
	CPM_BRG7,	/* Baud Rate Generator  7 */
	CPM_BRG8,	/* Baud Rate Generator  8 */
	CPM_CLK1,	/* Clock  1 */
	CPM_CLK2,	/* Clock  2 */
	CPM_CLK3,	/* Clock  3 */
	CPM_CLK4,	/* Clock  4 */
	CPM_CLK5,	/* Clock  5 */
	CPM_CLK6,	/* Clock  6 */
	CPM_CLK7,	/* Clock  7 */
	CPM_CLK8,	/* Clock  8 */
	CPM_CLK9,	/* Clock  9 */
	CPM_CLK10,	/* Clock 10 */
	CPM_CLK11,	/* Clock 11 */
	CPM_CLK12,	/* Clock 12 */
	CPM_CLK13,	/* Clock 13 */
	CPM_CLK14,	/* Clock 14 */
	CPM_CLK15,	/* Clock 15 */
	CPM_CLK16,	/* Clock 16 */
	CPM_CLK17,	/* Clock 17 */
	CPM_CLK18,	/* Clock 18 */
	CPM_CLK19,	/* Clock 19 */
	CPM_CLK20,	/* Clock 20 */
	CPM_CLK_DUMMY
पूर्ण;

बाह्य पूर्णांक cpm2_clk_setup(क्रमागत cpm_clk_target target, पूर्णांक घड़ी, पूर्णांक mode);
बाह्य पूर्णांक cpm2_smc_clk_setup(क्रमागत cpm_clk_target target, पूर्णांक घड़ी);

#घोषणा CPM_PIN_INPUT     0
#घोषणा CPM_PIN_OUTPUT    1
#घोषणा CPM_PIN_PRIMARY   0
#घोषणा CPM_PIN_SECONDARY 2
#घोषणा CPM_PIN_GPIO      4
#घोषणा CPM_PIN_OPENDRAIN 8

व्योम cpm2_set_pin(पूर्णांक port, पूर्णांक pin, पूर्णांक flags);

#पूर्ण_अगर /* __CPM2__ */
#पूर्ण_अगर /* __KERNEL__ */
