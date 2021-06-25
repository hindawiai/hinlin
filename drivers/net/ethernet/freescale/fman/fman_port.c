<शैली गुरु>
/*
 * Copyright 2008 - 2015 Freescale Semiconductor Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/delay.h>
#समावेश <linux/libfdt_env.h>

#समावेश "fman.h"
#समावेश "fman_port.h"
#समावेश "fman_sp.h"
#समावेश "fman_keygen.h"

/* Queue ID */
#घोषणा DFLT_FQ_ID		0x00FFFFFF

/* General defines */
#घोषणा PORT_BMI_FIFO_UNITS		0x100

#घोषणा MAX_PORT_FIFO_SIZE(bmi_max_fअगरo_size)	\
	min((u32)bmi_max_fअगरo_size, (u32)1024 * FMAN_BMI_FIFO_UNITS)

#घोषणा PORT_CG_MAP_NUM			8
#घोषणा PORT_PRS_RESULT_WORDS_NUM	8
#घोषणा PORT_IC_OFFSET_UNITS		0x10

#घोषणा MIN_EXT_BUF_SIZE		64

#घोषणा BMI_PORT_REGS_OFFSET				0
#घोषणा QMI_PORT_REGS_OFFSET				0x400
#घोषणा HWP_PORT_REGS_OFFSET				0x800

/* Default values */
#घोषणा DFLT_PORT_BUFFER_PREFIX_CONTEXT_DATA_ALIGN		\
	DFLT_FM_SP_BUFFER_PREFIX_CONTEXT_DATA_ALIGN

#घोषणा DFLT_PORT_CUT_BYTES_FROM_END		4

#घोषणा DFLT_PORT_ERRORS_TO_DISCARD		FM_PORT_FRM_ERR_CLS_DISCARD
#घोषणा DFLT_PORT_MAX_FRAME_LENGTH		9600

#घोषणा DFLT_PORT_RX_FIFO_PRI_ELEVATION_LEV(bmi_max_fअगरo_size)	\
	MAX_PORT_FIFO_SIZE(bmi_max_fअगरo_size)

#घोषणा DFLT_PORT_RX_FIFO_THRESHOLD(major, bmi_max_fअगरo_size)	\
	(major == 6 ?						\
	MAX_PORT_FIFO_SIZE(bmi_max_fअगरo_size) :		\
	(MAX_PORT_FIFO_SIZE(bmi_max_fअगरo_size) * 3 / 4))	\

#घोषणा DFLT_PORT_EXTRA_NUM_OF_FIFO_BUFS		0

/* QMI defines */
#घोषणा QMI_DEQ_CFG_SUBPORTAL_MASK		0x1f

#घोषणा QMI_PORT_CFG_EN				0x80000000
#घोषणा QMI_PORT_STATUS_DEQ_FD_BSY		0x20000000

#घोषणा QMI_DEQ_CFG_PRI				0x80000000
#घोषणा QMI_DEQ_CFG_TYPE1			0x10000000
#घोषणा QMI_DEQ_CFG_TYPE2			0x20000000
#घोषणा QMI_DEQ_CFG_TYPE3			0x30000000
#घोषणा QMI_DEQ_CFG_PREFETCH_PARTIAL		0x01000000
#घोषणा QMI_DEQ_CFG_PREFETCH_FULL		0x03000000
#घोषणा QMI_DEQ_CFG_SP_MASK			0xf
#घोषणा QMI_DEQ_CFG_SP_SHIFT			20

#घोषणा QMI_BYTE_COUNT_LEVEL_CONTROL(_type)	\
	(_type == FMAN_PORT_TYPE_TX ? 0x1400 : 0x400)

/* BMI defins */
#घोषणा BMI_EBD_EN				0x80000000

#घोषणा BMI_PORT_CFG_EN				0x80000000

#घोषणा BMI_PORT_STATUS_BSY			0x80000000

#घोषणा BMI_DMA_ATTR_SWP_SHIFT			FMAN_SP_DMA_ATTR_SWP_SHIFT
#घोषणा BMI_DMA_ATTR_WRITE_OPTIMIZE		FMAN_SP_DMA_ATTR_WRITE_OPTIMIZE

#घोषणा BMI_RX_FIFO_PRI_ELEVATION_SHIFT	16
#घोषणा BMI_RX_FIFO_THRESHOLD_ETHE		0x80000000

#घोषणा BMI_FRAME_END_CS_IGNORE_SHIFT		24
#घोषणा BMI_FRAME_END_CS_IGNORE_MASK		0x0000001f

#घोषणा BMI_RX_FRAME_END_CUT_SHIFT		16
#घोषणा BMI_RX_FRAME_END_CUT_MASK		0x0000001f

#घोषणा BMI_IC_TO_EXT_SHIFT			FMAN_SP_IC_TO_EXT_SHIFT
#घोषणा BMI_IC_TO_EXT_MASK			0x0000001f
#घोषणा BMI_IC_FROM_INT_SHIFT			FMAN_SP_IC_FROM_INT_SHIFT
#घोषणा BMI_IC_FROM_INT_MASK			0x0000000f
#घोषणा BMI_IC_SIZE_MASK			0x0000001f

#घोषणा BMI_INT_BUF_MARG_SHIFT			28
#घोषणा BMI_INT_BUF_MARG_MASK			0x0000000f
#घोषणा BMI_EXT_BUF_MARG_START_SHIFT		FMAN_SP_EXT_BUF_MARG_START_SHIFT
#घोषणा BMI_EXT_BUF_MARG_START_MASK		0x000001ff
#घोषणा BMI_EXT_BUF_MARG_END_MASK		0x000001ff

#घोषणा BMI_CMD_MR_LEAC				0x00200000
#घोषणा BMI_CMD_MR_SLEAC			0x00100000
#घोषणा BMI_CMD_MR_MA				0x00080000
#घोषणा BMI_CMD_MR_DEAS				0x00040000
#घोषणा BMI_CMD_RX_MR_DEF			(BMI_CMD_MR_LEAC | \
						BMI_CMD_MR_SLEAC | \
						BMI_CMD_MR_MA | \
						BMI_CMD_MR_DEAS)
#घोषणा BMI_CMD_TX_MR_DEF			0

#घोषणा BMI_CMD_ATTR_ORDER			0x80000000
#घोषणा BMI_CMD_ATTR_SYNC			0x02000000
#घोषणा BMI_CMD_ATTR_COLOR_SHIFT		26

#घोषणा BMI_FIFO_PIPELINE_DEPTH_SHIFT		12
#घोषणा BMI_FIFO_PIPELINE_DEPTH_MASK		0x0000000f
#घोषणा BMI_NEXT_ENG_FD_BITS_SHIFT		24

#घोषणा BMI_EXT_BUF_POOL_VALID			FMAN_SP_EXT_BUF_POOL_VALID
#घोषणा BMI_EXT_BUF_POOL_EN_COUNTER		FMAN_SP_EXT_BUF_POOL_EN_COUNTER
#घोषणा BMI_EXT_BUF_POOL_BACKUP		FMAN_SP_EXT_BUF_POOL_BACKUP
#घोषणा BMI_EXT_BUF_POOL_ID_SHIFT		16
#घोषणा BMI_EXT_BUF_POOL_ID_MASK		0x003F0000
#घोषणा BMI_POOL_DEP_NUM_OF_POOLS_SHIFT	16

#घोषणा BMI_TX_FIFO_MIN_FILL_SHIFT		16

#घोषणा BMI_PRIORITY_ELEVATION_LEVEL ((0x3FF + 1) * PORT_BMI_FIFO_UNITS)
#घोषणा BMI_FIFO_THRESHOLD	      ((0x3FF + 1) * PORT_BMI_FIFO_UNITS)

#घोषणा BMI_DEQUEUE_PIPELINE_DEPTH(_type, _speed)		\
	((_type == FMAN_PORT_TYPE_TX && _speed == 10000) ? 4 : 1)

#घोषणा RX_ERRS_TO_ENQ				  \
	(FM_PORT_FRM_ERR_DMA			| \
	FM_PORT_FRM_ERR_PHYSICAL		| \
	FM_PORT_FRM_ERR_SIZE			| \
	FM_PORT_FRM_ERR_EXTRACTION		| \
	FM_PORT_FRM_ERR_NO_SCHEME		| \
	FM_PORT_FRM_ERR_PRS_TIMEOUT		| \
	FM_PORT_FRM_ERR_PRS_ILL_INSTRUCT	| \
	FM_PORT_FRM_ERR_BLOCK_LIMIT_EXCEEDED	| \
	FM_PORT_FRM_ERR_PRS_HDR_ERR		| \
	FM_PORT_FRM_ERR_KEYSIZE_OVERFLOW	| \
	FM_PORT_FRM_ERR_IPRE)

/* NIA defines */
#घोषणा NIA_ORDER_RESTOR				0x00800000
#घोषणा NIA_ENG_BMI					0x00500000
#घोषणा NIA_ENG_QMI_ENQ					0x00540000
#घोषणा NIA_ENG_QMI_DEQ					0x00580000
#घोषणा NIA_ENG_HWP					0x00440000
#घोषणा NIA_ENG_HWK					0x00480000
#घोषणा NIA_BMI_AC_ENQ_FRAME				0x00000002
#घोषणा NIA_BMI_AC_TX_RELEASE				0x000002C0
#घोषणा NIA_BMI_AC_RELEASE				0x000000C0
#घोषणा NIA_BMI_AC_TX					0x00000274
#घोषणा NIA_BMI_AC_FETCH_ALL_FRAME			0x0000020c

/* Port IDs */
#घोषणा TX_10G_PORT_BASE		0x30
#घोषणा RX_10G_PORT_BASE		0x10

/* BMI Rx port रेजिस्टर map */
काष्ठा fman_port_rx_bmi_regs अणु
	u32 fmbm_rcfg;		/* Rx Configuration */
	u32 fmbm_rst;		/* Rx Status */
	u32 fmbm_rda;		/* Rx DMA attributes */
	u32 fmbm_rfp;		/* Rx FIFO Parameters */
	u32 fmbm_rfed;		/* Rx Frame End Data */
	u32 fmbm_ricp;		/* Rx Internal Context Parameters */
	u32 fmbm_rim;		/* Rx Internal Buffer Margins */
	u32 fmbm_rebm;		/* Rx External Buffer Margins */
	u32 fmbm_rfne;		/* Rx Frame Next Engine */
	u32 fmbm_rfca;		/* Rx Frame Command Attributes. */
	u32 fmbm_rfpne;		/* Rx Frame Parser Next Engine */
	u32 fmbm_rpso;		/* Rx Parse Start Offset */
	u32 fmbm_rpp;		/* Rx Policer Profile  */
	u32 fmbm_rccb;		/* Rx Coarse Classअगरication Base */
	u32 fmbm_reth;		/* Rx Excessive Threshold */
	u32 reserved003c[1];	/* (0x03C 0x03F) */
	u32 fmbm_rprai[PORT_PRS_RESULT_WORDS_NUM];
	/* Rx Parse Results Array Init */
	u32 fmbm_rfqid;		/* Rx Frame Queue ID */
	u32 fmbm_refqid;	/* Rx Error Frame Queue ID */
	u32 fmbm_rfsdm;		/* Rx Frame Status Discard Mask */
	u32 fmbm_rfsem;		/* Rx Frame Status Error Mask */
	u32 fmbm_rfene;		/* Rx Frame Enqueue Next Engine */
	u32 reserved0074[0x2];	/* (0x074-0x07C)  */
	u32 fmbm_rcmne;		/* Rx Frame Continuous Mode Next Engine */
	u32 reserved0080[0x20];	/* (0x080 0x0FF)  */
	u32 fmbm_ebmpi[FMAN_PORT_MAX_EXT_POOLS_NUM];
	/* Buffer Manager pool Inक्रमmation- */
	u32 fmbm_acnt[FMAN_PORT_MAX_EXT_POOLS_NUM];	/* Allocate Counter- */
	u32 reserved0130[8];	/* 0x130/0x140 - 0x15F reserved - */
	u32 fmbm_rcgm[PORT_CG_MAP_NUM];	/* Congestion Group Map */
	u32 fmbm_mpd;		/* BM Pool Depletion  */
	u32 reserved0184[0x1F];	/* (0x184 0x1FF) */
	u32 fmbm_rstc;		/* Rx Statistics Counters */
	u32 fmbm_rfrc;		/* Rx Frame Counter */
	u32 fmbm_rfbc;		/* Rx Bad Frames Counter */
	u32 fmbm_rlfc;		/* Rx Large Frames Counter */
	u32 fmbm_rffc;		/* Rx Filter Frames Counter */
	u32 fmbm_rfdc;		/* Rx Frame Discard Counter */
	u32 fmbm_rfldec;		/* Rx Frames List DMA Error Counter */
	u32 fmbm_rodc;		/* Rx Out of Buffers Discard nntr */
	u32 fmbm_rbdc;		/* Rx Buffers Deallocate Counter */
	u32 fmbm_rpec;		/* RX Prepare to enqueue Counte */
	u32 reserved0224[0x16];	/* (0x224 0x27F) */
	u32 fmbm_rpc;		/* Rx Perक्रमmance Counters */
	u32 fmbm_rpcp;		/* Rx Perक्रमmance Count Parameters */
	u32 fmbm_rccn;		/* Rx Cycle Counter */
	u32 fmbm_rtuc;		/* Rx Tasks Utilization Counter */
	u32 fmbm_rrquc;		/* Rx Receive Queue Utilization cntr */
	u32 fmbm_rduc;		/* Rx DMA Utilization Counter */
	u32 fmbm_rfuc;		/* Rx FIFO Utilization Counter */
	u32 fmbm_rpac;		/* Rx Pause Activation Counter */
	u32 reserved02a0[0x18];	/* (0x2A0 0x2FF) */
	u32 fmbm_rdcfg[0x3];	/* Rx Debug Configuration */
	u32 fmbm_rgpr;		/* Rx General Purpose Register */
	u32 reserved0310[0x3a];
पूर्ण;

/* BMI Tx port रेजिस्टर map */
काष्ठा fman_port_tx_bmi_regs अणु
	u32 fmbm_tcfg;		/* Tx Configuration */
	u32 fmbm_tst;		/* Tx Status */
	u32 fmbm_tda;		/* Tx DMA attributes */
	u32 fmbm_tfp;		/* Tx FIFO Parameters */
	u32 fmbm_tfed;		/* Tx Frame End Data */
	u32 fmbm_ticp;		/* Tx Internal Context Parameters */
	u32 fmbm_tfdne;		/* Tx Frame Dequeue Next Engine. */
	u32 fmbm_tfca;		/* Tx Frame Command attribute. */
	u32 fmbm_tcfqid;	/* Tx Confirmation Frame Queue ID. */
	u32 fmbm_tefqid;	/* Tx Frame Error Queue ID */
	u32 fmbm_tfene;		/* Tx Frame Enqueue Next Engine */
	u32 fmbm_trlmts;	/* Tx Rate Limiter Scale */
	u32 fmbm_trlmt;		/* Tx Rate Limiter */
	u32 reserved0034[0x0e];	/* (0x034-0x6c) */
	u32 fmbm_tccb;		/* Tx Coarse Classअगरication base */
	u32 fmbm_tfne;		/* Tx Frame Next Engine */
	u32 fmbm_tpfcm[0x02];
	/* Tx Priority based Flow Control (PFC) Mapping */
	u32 fmbm_tcmne;		/* Tx Frame Continuous Mode Next Engine */
	u32 reserved0080[0x60];	/* (0x080-0x200) */
	u32 fmbm_tstc;		/* Tx Statistics Counters */
	u32 fmbm_tfrc;		/* Tx Frame Counter */
	u32 fmbm_tfdc;		/* Tx Frames Discard Counter */
	u32 fmbm_tfledc;	/* Tx Frame len error discard cntr */
	u32 fmbm_tfufdc;	/* Tx Frame unsprt frmt discard cntr */
	u32 fmbm_tbdc;		/* Tx Buffers Deallocate Counter */
	u32 reserved0218[0x1A];	/* (0x218-0x280) */
	u32 fmbm_tpc;		/* Tx Perक्रमmance Counters */
	u32 fmbm_tpcp;		/* Tx Perक्रमmance Count Parameters */
	u32 fmbm_tccn;		/* Tx Cycle Counter */
	u32 fmbm_ttuc;		/* Tx Tasks Utilization Counter */
	u32 fmbm_ttcquc;	/* Tx Transmit conf Q util Counter */
	u32 fmbm_tduc;		/* Tx DMA Utilization Counter */
	u32 fmbm_tfuc;		/* Tx FIFO Utilization Counter */
	u32 reserved029c[16];	/* (0x29C-0x2FF) */
	u32 fmbm_tdcfg[0x3];	/* Tx Debug Configuration */
	u32 fmbm_tgpr;		/* Tx General Purpose Register */
	u32 reserved0310[0x3a]; /* (0x310-0x3FF) */
पूर्ण;

/* BMI port रेजिस्टर map */
जोड़ fman_port_bmi_regs अणु
	काष्ठा fman_port_rx_bmi_regs rx;
	काष्ठा fman_port_tx_bmi_regs tx;
पूर्ण;

/* QMI port रेजिस्टर map */
काष्ठा fman_port_qmi_regs अणु
	u32 fmqm_pnc;		/* PortID n Configuration Register */
	u32 fmqm_pns;		/* PortID n Status Register */
	u32 fmqm_pnts;		/* PortID n Task Status Register */
	u32 reserved00c[4];	/* 0xn00C - 0xn01B */
	u32 fmqm_pnen;		/* PortID n Enqueue NIA Register */
	u32 fmqm_pnetfc;		/* PortID n Enq Total Frame Counter */
	u32 reserved024[2];	/* 0xn024 - 0x02B */
	u32 fmqm_pndn;		/* PortID n Dequeue NIA Register */
	u32 fmqm_pndc;		/* PortID n Dequeue Config Register */
	u32 fmqm_pndtfc;		/* PortID n Dequeue tot Frame cntr */
	u32 fmqm_pndfdc;		/* PortID n Dequeue FQID Dflt Cntr */
	u32 fmqm_pndcc;		/* PortID n Dequeue Confirm Counter */
पूर्ण;

#घोषणा HWP_HXS_COUNT 16
#घोषणा HWP_HXS_PHE_REPORT 0x00000800
#घोषणा HWP_HXS_PCAC_PSTAT 0x00000100
#घोषणा HWP_HXS_PCAC_PSTOP 0x00000001
#घोषणा HWP_HXS_TCP_OFFSET 0xA
#घोषणा HWP_HXS_UDP_OFFSET 0xB
#घोषणा HWP_HXS_SH_PAD_REM 0x80000000

काष्ठा fman_port_hwp_regs अणु
	काष्ठा अणु
		u32 ssa; /* Soft Sequence Attachment */
		u32 lcv; /* Line-up Enable Confirmation Mask */
	पूर्ण pmda[HWP_HXS_COUNT]; /* Parse Memory Direct Access Registers */
	u32 reserved080[(0x3f8 - 0x080) / 4]; /* (0x080-0x3f7) */
	u32 fmpr_pcac; /* Configuration Access Control */
पूर्ण;

/* QMI dequeue prefetch modes */
क्रमागत fman_port_deq_prefetch अणु
	FMAN_PORT_DEQ_NO_PREFETCH, /* No prefetch mode */
	FMAN_PORT_DEQ_PART_PREFETCH, /* Partial prefetch mode */
	FMAN_PORT_DEQ_FULL_PREFETCH /* Full prefetch mode */
पूर्ण;

/* A काष्ठाure क्रम defining FM port resources */
काष्ठा fman_port_rsrc अणु
	u32 num; /* Committed required resource */
	u32 extra; /* Extra (not committed) required resource */
पूर्ण;

क्रमागत fman_port_dma_swap अणु
	FMAN_PORT_DMA_NO_SWAP,	/* No swap, transfer data as is */
	FMAN_PORT_DMA_SWAP_LE,
	/* The transferred data should be swapped in PPC Little Endian mode */
	FMAN_PORT_DMA_SWAP_BE
	/* The transferred data should be swapped in Big Endian mode */
पूर्ण;

/* Default port color */
क्रमागत fman_port_color अणु
	FMAN_PORT_COLOR_GREEN,	/* Default port color is green */
	FMAN_PORT_COLOR_YELLOW,	/* Default port color is yellow */
	FMAN_PORT_COLOR_RED,		/* Default port color is red */
	FMAN_PORT_COLOR_OVERRIDE	/* Ignore color */
पूर्ण;

/* QMI dequeue from the SP channel - types */
क्रमागत fman_port_deq_type अणु
	FMAN_PORT_DEQ_BY_PRI,
	/* Priority precedence and Intra-Class scheduling */
	FMAN_PORT_DEQ_ACTIVE_FQ,
	/* Active FQ precedence and Intra-Class scheduling */
	FMAN_PORT_DEQ_ACTIVE_FQ_NO_ICS
	/* Active FQ precedence and override Intra-Class scheduling */
पूर्ण;

/* External buffer pools configuration */
काष्ठा fman_port_bpools अणु
	u8 count;			/* Num of pools to set up */
	bool counters_enable;		/* Enable allocate counters */
	u8 grp_bp_depleted_num;
	/* Number of depleted pools - अगर reached the BMI indicates
	 * the MAC to send a छोड़ो frame
	 */
	काष्ठा अणु
		u8 bpid;		/* BM pool ID */
		u16 size;
		/* Pool's size - must be in ascending order */
		bool is_backup;
		/* If this is a backup pool */
		bool grp_bp_depleted;
		/* Consider this buffer in multiple pools depletion criteria */
		bool single_bp_depleted;
		/* Consider this buffer in single pool depletion criteria */
	पूर्ण bpool[FMAN_PORT_MAX_EXT_POOLS_NUM];
पूर्ण;

काष्ठा fman_port_cfg अणु
	u32 dflt_fqid;
	u32 err_fqid;
	u32 pcd_base_fqid;
	u32 pcd_fqs_count;
	u8 deq_sp;
	bool deq_high_priority;
	क्रमागत fman_port_deq_type deq_type;
	क्रमागत fman_port_deq_prefetch deq_prefetch_option;
	u16 deq_byte_cnt;
	u8 cheksum_last_bytes_ignore;
	u8 rx_cut_end_bytes;
	काष्ठा fman_buf_pool_depletion buf_pool_depletion;
	काष्ठा fman_ext_pools ext_buf_pools;
	u32 tx_fअगरo_min_level;
	u32 tx_fअगरo_low_comf_level;
	u32 rx_pri_elevation;
	u32 rx_fअगरo_thr;
	काष्ठा fman_sp_buf_margins buf_margins;
	u32 पूर्णांक_buf_start_margin;
	काष्ठा fman_sp_पूर्णांक_context_data_copy पूर्णांक_context;
	u32 discard_mask;
	u32 err_mask;
	काष्ठा fman_buffer_prefix_content buffer_prefix_content;
	bool करोnt_release_buf;

	u8 rx_fd_bits;
	u32 tx_fअगरo_deq_pipeline_depth;
	bool errata_A006320;
	bool excessive_threshold_रेजिस्टर;
	bool fmbm_tfne_has_features;

	क्रमागत fman_port_dma_swap dma_swap_data;
	क्रमागत fman_port_color color;
पूर्ण;

काष्ठा fman_port_rx_pools_params अणु
	u8 num_of_pools;
	u16 largest_buf_size;
पूर्ण;

काष्ठा fman_port_dts_params अणु
	व्योम __iomem *base_addr;	/* FMan port भव memory */
	क्रमागत fman_port_type type;	/* Port type */
	u16 speed;			/* Port speed */
	u8 id;				/* HW Port Id */
	u32 qman_channel_id;		/* QMan channel id (non RX only) */
	काष्ठा fman *fman;		/* FMan Handle */
पूर्ण;

काष्ठा fman_port अणु
	व्योम *fm;
	काष्ठा device *dev;
	काष्ठा fman_rev_info rev_info;
	u8 port_id;
	क्रमागत fman_port_type port_type;
	u16 port_speed;

	जोड़ fman_port_bmi_regs __iomem *bmi_regs;
	काष्ठा fman_port_qmi_regs __iomem *qmi_regs;
	काष्ठा fman_port_hwp_regs __iomem *hwp_regs;

	काष्ठा fman_sp_buffer_offsets buffer_offsets;

	u8 पूर्णांकernal_buf_offset;
	काष्ठा fman_ext_pools ext_buf_pools;

	u16 max_frame_length;
	काष्ठा fman_port_rsrc खोलो_dmas;
	काष्ठा fman_port_rsrc tasks;
	काष्ठा fman_port_rsrc fअगरo_bufs;
	काष्ठा fman_port_rx_pools_params rx_pools_params;

	काष्ठा fman_port_cfg *cfg;
	काष्ठा fman_port_dts_params dts_params;

	u8 ext_pools_num;
	u32 max_port_fअगरo_size;
	u32 max_num_of_ext_pools;
	u32 max_num_of_sub_portals;
	u32 bm_max_num_of_pools;
पूर्ण;

अटल पूर्णांक init_bmi_rx(काष्ठा fman_port *port)
अणु
	काष्ठा fman_port_rx_bmi_regs __iomem *regs = &port->bmi_regs->rx;
	काष्ठा fman_port_cfg *cfg = port->cfg;
	u32 पंचांगp;

	/* DMA attributes */
	पंचांगp = (u32)cfg->dma_swap_data << BMI_DMA_ATTR_SWP_SHIFT;
	/* Enable ग_लिखो optimization */
	पंचांगp |= BMI_DMA_ATTR_WRITE_OPTIMIZE;
	ioग_लिखो32be(पंचांगp, &regs->fmbm_rda);

	/* Rx FIFO parameters */
	पंचांगp = (cfg->rx_pri_elevation / PORT_BMI_FIFO_UNITS - 1) <<
		BMI_RX_FIFO_PRI_ELEVATION_SHIFT;
	पंचांगp |= cfg->rx_fअगरo_thr / PORT_BMI_FIFO_UNITS - 1;
	ioग_लिखो32be(पंचांगp, &regs->fmbm_rfp);

	अगर (cfg->excessive_threshold_रेजिस्टर)
		/* always allow access to the extra resources */
		ioग_लिखो32be(BMI_RX_FIFO_THRESHOLD_ETHE, &regs->fmbm_reth);

	/* Frame end data */
	पंचांगp = (cfg->cheksum_last_bytes_ignore & BMI_FRAME_END_CS_IGNORE_MASK) <<
		BMI_FRAME_END_CS_IGNORE_SHIFT;
	पंचांगp |= (cfg->rx_cut_end_bytes & BMI_RX_FRAME_END_CUT_MASK) <<
		BMI_RX_FRAME_END_CUT_SHIFT;
	अगर (cfg->errata_A006320)
		पंचांगp &= 0xffe0ffff;
	ioग_लिखो32be(पंचांगp, &regs->fmbm_rfed);

	/* Internal context parameters */
	पंचांगp = ((cfg->पूर्णांक_context.ext_buf_offset / PORT_IC_OFFSET_UNITS) &
		BMI_IC_TO_EXT_MASK) << BMI_IC_TO_EXT_SHIFT;
	पंचांगp |= ((cfg->पूर्णांक_context.पूर्णांक_context_offset / PORT_IC_OFFSET_UNITS) &
		BMI_IC_FROM_INT_MASK) << BMI_IC_FROM_INT_SHIFT;
	पंचांगp |= (cfg->पूर्णांक_context.size / PORT_IC_OFFSET_UNITS) &
		BMI_IC_SIZE_MASK;
	ioग_लिखो32be(पंचांगp, &regs->fmbm_ricp);

	/* Internal buffer offset */
	पंचांगp = ((cfg->पूर्णांक_buf_start_margin / PORT_IC_OFFSET_UNITS) &
		BMI_INT_BUF_MARG_MASK) << BMI_INT_BUF_MARG_SHIFT;
	ioग_लिखो32be(पंचांगp, &regs->fmbm_rim);

	/* External buffer margins */
	पंचांगp = (cfg->buf_margins.start_margins & BMI_EXT_BUF_MARG_START_MASK) <<
		BMI_EXT_BUF_MARG_START_SHIFT;
	पंचांगp |= cfg->buf_margins.end_margins & BMI_EXT_BUF_MARG_END_MASK;
	ioग_लिखो32be(पंचांगp, &regs->fmbm_rebm);

	/* Frame attributes */
	पंचांगp = BMI_CMD_RX_MR_DEF;
	पंचांगp |= BMI_CMD_ATTR_ORDER;
	पंचांगp |= (u32)cfg->color << BMI_CMD_ATTR_COLOR_SHIFT;
	/* Synchronization request */
	पंचांगp |= BMI_CMD_ATTR_SYNC;

	ioग_लिखो32be(पंचांगp, &regs->fmbm_rfca);

	/* NIA */
	पंचांगp = (u32)cfg->rx_fd_bits << BMI_NEXT_ENG_FD_BITS_SHIFT;

	पंचांगp |= NIA_ENG_HWP;
	ioग_लिखो32be(पंचांगp, &regs->fmbm_rfne);

	/* Parser Next Engine NIA */
	ioग_लिखो32be(NIA_ENG_BMI | NIA_BMI_AC_ENQ_FRAME, &regs->fmbm_rfpne);

	/* Enqueue NIA */
	ioग_लिखो32be(NIA_ENG_QMI_ENQ | NIA_ORDER_RESTOR, &regs->fmbm_rfene);

	/* Default/error queues */
	ioग_लिखो32be((cfg->dflt_fqid & DFLT_FQ_ID), &regs->fmbm_rfqid);
	ioग_लिखो32be((cfg->err_fqid & DFLT_FQ_ID), &regs->fmbm_refqid);

	/* Discard/error masks */
	ioग_लिखो32be(cfg->discard_mask, &regs->fmbm_rfsdm);
	ioग_लिखो32be(cfg->err_mask, &regs->fmbm_rfsem);

	वापस 0;
पूर्ण

अटल पूर्णांक init_bmi_tx(काष्ठा fman_port *port)
अणु
	काष्ठा fman_port_tx_bmi_regs __iomem *regs = &port->bmi_regs->tx;
	काष्ठा fman_port_cfg *cfg = port->cfg;
	u32 पंचांगp;

	/* Tx Configuration रेजिस्टर */
	पंचांगp = 0;
	ioग_लिखो32be(पंचांगp, &regs->fmbm_tcfg);

	/* DMA attributes */
	पंचांगp = (u32)cfg->dma_swap_data << BMI_DMA_ATTR_SWP_SHIFT;
	ioग_लिखो32be(पंचांगp, &regs->fmbm_tda);

	/* Tx FIFO parameters */
	पंचांगp = (cfg->tx_fअगरo_min_level / PORT_BMI_FIFO_UNITS) <<
		BMI_TX_FIFO_MIN_FILL_SHIFT;
	पंचांगp |= ((cfg->tx_fअगरo_deq_pipeline_depth - 1) &
		BMI_FIFO_PIPELINE_DEPTH_MASK) << BMI_FIFO_PIPELINE_DEPTH_SHIFT;
	पंचांगp |= (cfg->tx_fअगरo_low_comf_level / PORT_BMI_FIFO_UNITS) - 1;
	ioग_लिखो32be(पंचांगp, &regs->fmbm_tfp);

	/* Frame end data */
	पंचांगp = (cfg->cheksum_last_bytes_ignore & BMI_FRAME_END_CS_IGNORE_MASK) <<
		BMI_FRAME_END_CS_IGNORE_SHIFT;
	ioग_लिखो32be(पंचांगp, &regs->fmbm_tfed);

	/* Internal context parameters */
	पंचांगp = ((cfg->पूर्णांक_context.ext_buf_offset / PORT_IC_OFFSET_UNITS) &
		BMI_IC_TO_EXT_MASK) << BMI_IC_TO_EXT_SHIFT;
	पंचांगp |= ((cfg->पूर्णांक_context.पूर्णांक_context_offset / PORT_IC_OFFSET_UNITS) &
		BMI_IC_FROM_INT_MASK) << BMI_IC_FROM_INT_SHIFT;
	पंचांगp |= (cfg->पूर्णांक_context.size / PORT_IC_OFFSET_UNITS) &
		BMI_IC_SIZE_MASK;
	ioग_लिखो32be(पंचांगp, &regs->fmbm_ticp);

	/* Frame attributes */
	पंचांगp = BMI_CMD_TX_MR_DEF;
	पंचांगp |= BMI_CMD_ATTR_ORDER;
	पंचांगp |= (u32)cfg->color << BMI_CMD_ATTR_COLOR_SHIFT;
	ioग_लिखो32be(पंचांगp, &regs->fmbm_tfca);

	/* Dequeue NIA + enqueue NIA */
	ioग_लिखो32be(NIA_ENG_QMI_DEQ, &regs->fmbm_tfdne);
	ioग_लिखो32be(NIA_ENG_QMI_ENQ | NIA_ORDER_RESTOR, &regs->fmbm_tfene);
	अगर (cfg->fmbm_tfne_has_features)
		ioग_लिखो32be(!cfg->dflt_fqid ?
			    BMI_EBD_EN | NIA_BMI_AC_FETCH_ALL_FRAME :
			    NIA_BMI_AC_FETCH_ALL_FRAME, &regs->fmbm_tfne);
	अगर (!cfg->dflt_fqid && cfg->करोnt_release_buf) अणु
		ioग_लिखो32be(DFLT_FQ_ID, &regs->fmbm_tcfqid);
		ioग_लिखो32be(NIA_ENG_BMI | NIA_BMI_AC_TX_RELEASE,
			    &regs->fmbm_tfene);
		अगर (cfg->fmbm_tfne_has_features)
			ioग_लिखो32be(ioपढ़ो32be(&regs->fmbm_tfne) & ~BMI_EBD_EN,
				    &regs->fmbm_tfne);
	पूर्ण

	/* Confirmation/error queues */
	अगर (cfg->dflt_fqid || !cfg->करोnt_release_buf)
		ioग_लिखो32be(cfg->dflt_fqid & DFLT_FQ_ID, &regs->fmbm_tcfqid);
	ioग_लिखो32be((cfg->err_fqid & DFLT_FQ_ID), &regs->fmbm_tefqid);

	वापस 0;
पूर्ण

अटल पूर्णांक init_qmi(काष्ठा fman_port *port)
अणु
	काष्ठा fman_port_qmi_regs __iomem *regs = port->qmi_regs;
	काष्ठा fman_port_cfg *cfg = port->cfg;
	u32 पंचांगp;

	/* Rx port configuration */
	अगर (port->port_type == FMAN_PORT_TYPE_RX) अणु
		/* Enqueue NIA */
		ioग_लिखो32be(NIA_ENG_BMI | NIA_BMI_AC_RELEASE, &regs->fmqm_pnen);
		वापस 0;
	पूर्ण

	/* Continue with Tx port configuration */
	अगर (port->port_type == FMAN_PORT_TYPE_TX) अणु
		/* Enqueue NIA */
		ioग_लिखो32be(NIA_ENG_BMI | NIA_BMI_AC_TX_RELEASE,
			    &regs->fmqm_pnen);
		/* Dequeue NIA */
		ioग_लिखो32be(NIA_ENG_BMI | NIA_BMI_AC_TX, &regs->fmqm_pndn);
	पूर्ण

	/* Dequeue Configuration रेजिस्टर */
	पंचांगp = 0;
	अगर (cfg->deq_high_priority)
		पंचांगp |= QMI_DEQ_CFG_PRI;

	चयन (cfg->deq_type) अणु
	हाल FMAN_PORT_DEQ_BY_PRI:
		पंचांगp |= QMI_DEQ_CFG_TYPE1;
		अवरोध;
	हाल FMAN_PORT_DEQ_ACTIVE_FQ:
		पंचांगp |= QMI_DEQ_CFG_TYPE2;
		अवरोध;
	हाल FMAN_PORT_DEQ_ACTIVE_FQ_NO_ICS:
		पंचांगp |= QMI_DEQ_CFG_TYPE3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (cfg->deq_prefetch_option) अणु
	हाल FMAN_PORT_DEQ_NO_PREFETCH:
		अवरोध;
	हाल FMAN_PORT_DEQ_PART_PREFETCH:
		पंचांगp |= QMI_DEQ_CFG_PREFETCH_PARTIAL;
		अवरोध;
	हाल FMAN_PORT_DEQ_FULL_PREFETCH:
		पंचांगp |= QMI_DEQ_CFG_PREFETCH_FULL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	पंचांगp |= (cfg->deq_sp & QMI_DEQ_CFG_SP_MASK) << QMI_DEQ_CFG_SP_SHIFT;
	पंचांगp |= cfg->deq_byte_cnt;
	ioग_लिखो32be(पंचांगp, &regs->fmqm_pndc);

	वापस 0;
पूर्ण

अटल व्योम stop_port_hwp(काष्ठा fman_port *port)
अणु
	काष्ठा fman_port_hwp_regs __iomem *regs = port->hwp_regs;
	पूर्णांक cnt = 100;

	ioग_लिखो32be(HWP_HXS_PCAC_PSTOP, &regs->fmpr_pcac);

	जबतक (cnt-- > 0 &&
	       (ioपढ़ो32be(&regs->fmpr_pcac) & HWP_HXS_PCAC_PSTAT))
		udelay(10);
	अगर (!cnt)
		pr_err("Timeout stopping HW Parser\n");
पूर्ण

अटल व्योम start_port_hwp(काष्ठा fman_port *port)
अणु
	काष्ठा fman_port_hwp_regs __iomem *regs = port->hwp_regs;
	पूर्णांक cnt = 100;

	ioग_लिखो32be(0, &regs->fmpr_pcac);

	जबतक (cnt-- > 0 &&
	       !(ioपढ़ो32be(&regs->fmpr_pcac) & HWP_HXS_PCAC_PSTAT))
		udelay(10);
	अगर (!cnt)
		pr_err("Timeout starting HW Parser\n");
पूर्ण

अटल व्योम init_hwp(काष्ठा fman_port *port)
अणु
	काष्ठा fman_port_hwp_regs __iomem *regs = port->hwp_regs;
	पूर्णांक i;

	stop_port_hwp(port);

	क्रम (i = 0; i < HWP_HXS_COUNT; i++) अणु
		/* enable HXS error reporting पूर्णांकo FD[STATUS] PHE */
		ioग_लिखो32be(0x00000000, &regs->pmda[i].ssa);
		ioग_लिखो32be(0xffffffff, &regs->pmda[i].lcv);
	पूर्ण

	/* Short packet padding removal from checksum calculation */
	ioग_लिखो32be(HWP_HXS_SH_PAD_REM, &regs->pmda[HWP_HXS_TCP_OFFSET].ssa);
	ioग_लिखो32be(HWP_HXS_SH_PAD_REM, &regs->pmda[HWP_HXS_UDP_OFFSET].ssa);

	start_port_hwp(port);
पूर्ण

अटल पूर्णांक init(काष्ठा fman_port *port)
अणु
	पूर्णांक err;

	/* Init BMI रेजिस्टरs */
	चयन (port->port_type) अणु
	हाल FMAN_PORT_TYPE_RX:
		err = init_bmi_rx(port);
		अगर (!err)
			init_hwp(port);
		अवरोध;
	हाल FMAN_PORT_TYPE_TX:
		err = init_bmi_tx(port);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (err)
		वापस err;

	/* Init QMI रेजिस्टरs */
	err = init_qmi(port);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक set_bpools(स्थिर काष्ठा fman_port *port,
		      स्थिर काष्ठा fman_port_bpools *bp)
अणु
	u32 __iomem *bp_reg, *bp_depl_reg;
	u32 पंचांगp;
	u8 i, max_bp_num;
	bool grp_depl_used = false, rx_port;

	चयन (port->port_type) अणु
	हाल FMAN_PORT_TYPE_RX:
		max_bp_num = port->ext_pools_num;
		rx_port = true;
		bp_reg = port->bmi_regs->rx.fmbm_ebmpi;
		bp_depl_reg = &port->bmi_regs->rx.fmbm_mpd;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (rx_port) अणु
		/* Check buffers are provided in ascending order */
		क्रम (i = 0; (i < (bp->count - 1) &&
			     (i < FMAN_PORT_MAX_EXT_POOLS_NUM - 1)); i++) अणु
			अगर (bp->bpool[i].size > bp->bpool[i + 1].size)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Set up बाह्यal buffers pools */
	क्रम (i = 0; i < bp->count; i++) अणु
		पंचांगp = BMI_EXT_BUF_POOL_VALID;
		पंचांगp |= ((u32)bp->bpool[i].bpid <<
			BMI_EXT_BUF_POOL_ID_SHIFT) & BMI_EXT_BUF_POOL_ID_MASK;

		अगर (rx_port) अणु
			अगर (bp->counters_enable)
				पंचांगp |= BMI_EXT_BUF_POOL_EN_COUNTER;

			अगर (bp->bpool[i].is_backup)
				पंचांगp |= BMI_EXT_BUF_POOL_BACKUP;

			पंचांगp |= (u32)bp->bpool[i].size;
		पूर्ण

		ioग_लिखो32be(पंचांगp, &bp_reg[i]);
	पूर्ण

	/* Clear unused pools */
	क्रम (i = bp->count; i < max_bp_num; i++)
		ioग_लिखो32be(0, &bp_reg[i]);

	/* Pools depletion */
	पंचांगp = 0;
	क्रम (i = 0; i < FMAN_PORT_MAX_EXT_POOLS_NUM; i++) अणु
		अगर (bp->bpool[i].grp_bp_depleted) अणु
			grp_depl_used = true;
			पंचांगp |= 0x80000000 >> i;
		पूर्ण

		अगर (bp->bpool[i].single_bp_depleted)
			पंचांगp |= 0x80 >> i;
	पूर्ण

	अगर (grp_depl_used)
		पंचांगp |= ((u32)bp->grp_bp_depleted_num - 1) <<
		    BMI_POOL_DEP_NUM_OF_POOLS_SHIFT;

	ioग_लिखो32be(पंचांगp, bp_depl_reg);
	वापस 0;
पूर्ण

अटल bool is_init_करोne(काष्ठा fman_port_cfg *cfg)
अणु
	/* Checks अगर FMan port driver parameters were initialized */
	अगर (!cfg)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक verअगरy_size_of_fअगरo(काष्ठा fman_port *port)
अणु
	u32 min_fअगरo_size_required = 0, opt_fअगरo_size_क्रम_b2b = 0;

	/* TX Ports */
	अगर (port->port_type == FMAN_PORT_TYPE_TX) अणु
		min_fअगरo_size_required = (u32)
		    (roundup(port->max_frame_length,
			     FMAN_BMI_FIFO_UNITS) + (3 * FMAN_BMI_FIFO_UNITS));

		min_fअगरo_size_required +=
		    port->cfg->tx_fअगरo_deq_pipeline_depth *
		    FMAN_BMI_FIFO_UNITS;

		opt_fअगरo_size_क्रम_b2b = min_fअगरo_size_required;

		/* Add some margin क्रम back-to-back capability to improve
		 * perक्रमmance, allows the hardware to pipeline new frame dma
		 * जबतक the previous frame not yet transmitted.
		 */
		अगर (port->port_speed == 10000)
			opt_fअगरo_size_क्रम_b2b += 3 * FMAN_BMI_FIFO_UNITS;
		अन्यथा
			opt_fअगरo_size_क्रम_b2b += 2 * FMAN_BMI_FIFO_UNITS;
	पूर्ण

	/* RX Ports */
	अन्यथा अगर (port->port_type == FMAN_PORT_TYPE_RX) अणु
		अगर (port->rev_info.major >= 6)
			min_fअगरo_size_required = (u32)
			(roundup(port->max_frame_length,
				 FMAN_BMI_FIFO_UNITS) +
				 (5 * FMAN_BMI_FIFO_UNITS));
			/* 4 according to spec + 1 क्रम FOF>0 */
		अन्यथा
			min_fअगरo_size_required = (u32)
			(roundup(min(port->max_frame_length,
				     port->rx_pools_params.largest_buf_size),
				     FMAN_BMI_FIFO_UNITS) +
				     (7 * FMAN_BMI_FIFO_UNITS));

		opt_fअगरo_size_क्रम_b2b = min_fअगरo_size_required;

		/* Add some margin क्रम back-to-back capability to improve
		 * perक्रमmance,allows the hardware to pipeline new frame dma
		 * जबतक the previous frame not yet transmitted.
		 */
		अगर (port->port_speed == 10000)
			opt_fअगरo_size_क्रम_b2b += 8 * FMAN_BMI_FIFO_UNITS;
		अन्यथा
			opt_fअगरo_size_क्रम_b2b += 3 * FMAN_BMI_FIFO_UNITS;
	पूर्ण

	WARN_ON(min_fअगरo_size_required <= 0);
	WARN_ON(opt_fअगरo_size_क्रम_b2b < min_fअगरo_size_required);

	/* Verअगरy the size  */
	अगर (port->fअगरo_bufs.num < min_fअगरo_size_required)
		dev_dbg(port->dev, "%s: FIFO size should be enlarged to %d bytes\n",
			__func__, min_fअगरo_size_required);
	अन्यथा अगर (port->fअगरo_bufs.num < opt_fअगरo_size_क्रम_b2b)
		dev_dbg(port->dev, "%s: For b2b processing,FIFO may be enlarged to %d bytes\n",
			__func__, opt_fअगरo_size_क्रम_b2b);

	वापस 0;
पूर्ण

अटल पूर्णांक set_ext_buffer_pools(काष्ठा fman_port *port)
अणु
	काष्ठा fman_ext_pools *ext_buf_pools = &port->cfg->ext_buf_pools;
	काष्ठा fman_buf_pool_depletion *buf_pool_depletion =
	&port->cfg->buf_pool_depletion;
	u8 ordered_array[FMAN_PORT_MAX_EXT_POOLS_NUM];
	u16 sizes_array[BM_MAX_NUM_OF_POOLS];
	पूर्णांक i = 0, j = 0, err;
	काष्ठा fman_port_bpools bpools;

	स_रखो(&ordered_array, 0, माप(u8) * FMAN_PORT_MAX_EXT_POOLS_NUM);
	स_रखो(&sizes_array, 0, माप(u16) * BM_MAX_NUM_OF_POOLS);
	स_नकल(&port->ext_buf_pools, ext_buf_pools,
	       माप(काष्ठा fman_ext_pools));

	fman_sp_set_buf_pools_in_asc_order_of_buf_sizes(ext_buf_pools,
							ordered_array,
							sizes_array);

	स_रखो(&bpools, 0, माप(काष्ठा fman_port_bpools));
	bpools.count = ext_buf_pools->num_of_pools_used;
	bpools.counters_enable = true;
	क्रम (i = 0; i < ext_buf_pools->num_of_pools_used; i++) अणु
		bpools.bpool[i].bpid = ordered_array[i];
		bpools.bpool[i].size = sizes_array[ordered_array[i]];
	पूर्ण

	/* save pools parameters क्रम later use */
	port->rx_pools_params.num_of_pools = ext_buf_pools->num_of_pools_used;
	port->rx_pools_params.largest_buf_size =
	    sizes_array[ordered_array[ext_buf_pools->num_of_pools_used - 1]];

	/* FMBM_RMPD reg. - pool depletion */
	अगर (buf_pool_depletion->pools_grp_mode_enable) अणु
		bpools.grp_bp_depleted_num = buf_pool_depletion->num_of_pools;
		क्रम (i = 0; i < port->bm_max_num_of_pools; i++) अणु
			अगर (buf_pool_depletion->pools_to_consider[i]) अणु
				क्रम (j = 0; j < ext_buf_pools->
				     num_of_pools_used; j++) अणु
					अगर (i == ordered_array[j]) अणु
						bpools.bpool[j].
						    grp_bp_depleted = true;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (buf_pool_depletion->single_pool_mode_enable) अणु
		क्रम (i = 0; i < port->bm_max_num_of_pools; i++) अणु
			अगर (buf_pool_depletion->
			    pools_to_consider_क्रम_single_mode[i]) अणु
				क्रम (j = 0; j < ext_buf_pools->
				     num_of_pools_used; j++) अणु
					अगर (i == ordered_array[j]) अणु
						bpools.bpool[j].
						    single_bp_depleted = true;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	err = set_bpools(port, &bpools);
	अगर (err != 0) अणु
		dev_err(port->dev, "%s: set_bpools() failed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_low_level_driver(काष्ठा fman_port *port)
अणु
	काष्ठा fman_port_cfg *cfg = port->cfg;
	u32 पंचांगp_val;

	चयन (port->port_type) अणु
	हाल FMAN_PORT_TYPE_RX:
		cfg->err_mask = (RX_ERRS_TO_ENQ & ~cfg->discard_mask);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	पंचांगp_val = (u32)((port->पूर्णांकernal_buf_offset % OFFSET_UNITS) ?
		(port->पूर्णांकernal_buf_offset / OFFSET_UNITS + 1) :
		(port->पूर्णांकernal_buf_offset / OFFSET_UNITS));
	port->पूर्णांकernal_buf_offset = (u8)(पंचांगp_val * OFFSET_UNITS);
	port->cfg->पूर्णांक_buf_start_margin = port->पूर्णांकernal_buf_offset;

	अगर (init(port) != 0) अणु
		dev_err(port->dev, "%s: fman port initialization failed\n",
			__func__);
		वापस -ENODEV;
	पूर्ण

	/* The code bellow is a trick so the FM will not release the buffer
	 * to BM nor will try to enqueue the frame to QM
	 */
	अगर (port->port_type == FMAN_PORT_TYPE_TX) अणु
		अगर (!cfg->dflt_fqid && cfg->करोnt_release_buf) अणु
			/* override fmbm_tcfqid 0 with a false non-0 value.
			 * This will क्रमce FM to act according to tfene.
			 * Otherwise, अगर fmbm_tcfqid is 0 the FM will release
			 * buffers to BM regardless of fmbm_tfene
			 */
			ioग_लिखो32be(0xFFFFFF, &port->bmi_regs->tx.fmbm_tcfqid);
			ioग_लिखो32be(NIA_ENG_BMI | NIA_BMI_AC_TX_RELEASE,
				    &port->bmi_regs->tx.fmbm_tfene);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fill_soc_specअगरic_params(काष्ठा fman_port *port)
अणु
	u32 bmi_max_fअगरo_size;

	bmi_max_fअगरo_size = fman_get_bmi_max_fअगरo_size(port->fm);
	port->max_port_fअगरo_size = MAX_PORT_FIFO_SIZE(bmi_max_fअगरo_size);
	port->bm_max_num_of_pools = 64;

	/* P4080 - Major 2
	 * P2041/P3041/P5020/P5040 - Major 3
	 * Tx/Bx - Major 6
	 */
	चयन (port->rev_info.major) अणु
	हाल 2:
	हाल 3:
		port->max_num_of_ext_pools		= 4;
		port->max_num_of_sub_portals		= 12;
		अवरोध;

	हाल 6:
		port->max_num_of_ext_pools		= 8;
		port->max_num_of_sub_portals		= 16;
		अवरोध;

	शेष:
		dev_err(port->dev, "%s: Unsupported FMan version\n", __func__);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_dflt_fअगरo_deq_pipeline_depth(u8 major, क्रमागत fman_port_type type,
					    u16 speed)
अणु
	चयन (type) अणु
	हाल FMAN_PORT_TYPE_RX:
	हाल FMAN_PORT_TYPE_TX:
		चयन (speed) अणु
		हाल 10000:
			वापस 4;
		हाल 1000:
			अगर (major >= 6)
				वापस 2;
			अन्यथा
				वापस 1;
		शेष:
			वापस 0;
		पूर्ण
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक get_dflt_num_of_tasks(u8 major, क्रमागत fman_port_type type,
				 u16 speed)
अणु
	चयन (type) अणु
	हाल FMAN_PORT_TYPE_RX:
	हाल FMAN_PORT_TYPE_TX:
		चयन (speed) अणु
		हाल 10000:
			वापस 16;
		हाल 1000:
			अगर (major >= 6)
				वापस 4;
			अन्यथा
				वापस 3;
		शेष:
			वापस 0;
		पूर्ण
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक get_dflt_extra_num_of_tasks(u8 major, क्रमागत fman_port_type type,
				       u16 speed)
अणु
	चयन (type) अणु
	हाल FMAN_PORT_TYPE_RX:
		/* FMan V3 */
		अगर (major >= 6)
			वापस 0;

		/* FMan V2 */
		अगर (speed == 10000)
			वापस 8;
		अन्यथा
			वापस 2;
	हाल FMAN_PORT_TYPE_TX:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक get_dflt_num_of_खोलो_dmas(u8 major, क्रमागत fman_port_type type,
				     u16 speed)
अणु
	पूर्णांक val;

	अगर (major >= 6) अणु
		चयन (type) अणु
		हाल FMAN_PORT_TYPE_TX:
			अगर (speed == 10000)
				val = 12;
			अन्यथा
				val = 3;
			अवरोध;
		हाल FMAN_PORT_TYPE_RX:
			अगर (speed == 10000)
				val = 8;
			अन्यथा
				val = 2;
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (type) अणु
		हाल FMAN_PORT_TYPE_TX:
		हाल FMAN_PORT_TYPE_RX:
			अगर (speed == 10000)
				val = 8;
			अन्यथा
				val = 1;
			अवरोध;
		शेष:
			val = 0;
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक get_dflt_extra_num_of_खोलो_dmas(u8 major, क्रमागत fman_port_type type,
					   u16 speed)
अणु
	/* FMan V3 */
	अगर (major >= 6)
		वापस 0;

	/* FMan V2 */
	चयन (type) अणु
	हाल FMAN_PORT_TYPE_RX:
	हाल FMAN_PORT_TYPE_TX:
		अगर (speed == 10000)
			वापस 8;
		अन्यथा
			वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक get_dflt_num_of_fअगरo_bufs(u8 major, क्रमागत fman_port_type type,
				     u16 speed)
अणु
	पूर्णांक val;

	अगर (major >= 6) अणु
		चयन (type) अणु
		हाल FMAN_PORT_TYPE_TX:
			अगर (speed == 10000)
				val = 64;
			अन्यथा
				val = 50;
			अवरोध;
		हाल FMAN_PORT_TYPE_RX:
			अगर (speed == 10000)
				val = 96;
			अन्यथा
				val = 50;
			अवरोध;
		शेष:
			val = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (type) अणु
		हाल FMAN_PORT_TYPE_TX:
			अगर (speed == 10000)
				val = 48;
			अन्यथा
				val = 44;
			अवरोध;
		हाल FMAN_PORT_TYPE_RX:
			अगर (speed == 10000)
				val = 48;
			अन्यथा
				val = 45;
			अवरोध;
		शेष:
			val = 0;
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम set_dflt_cfg(काष्ठा fman_port *port,
			 काष्ठा fman_port_params *port_params)
अणु
	काष्ठा fman_port_cfg *cfg = port->cfg;

	cfg->dma_swap_data = FMAN_PORT_DMA_NO_SWAP;
	cfg->color = FMAN_PORT_COLOR_GREEN;
	cfg->rx_cut_end_bytes = DFLT_PORT_CUT_BYTES_FROM_END;
	cfg->rx_pri_elevation = BMI_PRIORITY_ELEVATION_LEVEL;
	cfg->rx_fअगरo_thr = BMI_FIFO_THRESHOLD;
	cfg->tx_fअगरo_low_comf_level = (5 * 1024);
	cfg->deq_type = FMAN_PORT_DEQ_BY_PRI;
	cfg->deq_prefetch_option = FMAN_PORT_DEQ_FULL_PREFETCH;
	cfg->tx_fअगरo_deq_pipeline_depth =
		BMI_DEQUEUE_PIPELINE_DEPTH(port->port_type, port->port_speed);
	cfg->deq_byte_cnt = QMI_BYTE_COUNT_LEVEL_CONTROL(port->port_type);

	cfg->rx_pri_elevation =
		DFLT_PORT_RX_FIFO_PRI_ELEVATION_LEV(port->max_port_fअगरo_size);
	port->cfg->rx_fअगरo_thr =
		DFLT_PORT_RX_FIFO_THRESHOLD(port->rev_info.major,
					    port->max_port_fअगरo_size);

	अगर ((port->rev_info.major == 6) &&
	    ((port->rev_info.minor == 0) || (port->rev_info.minor == 3)))
		cfg->errata_A006320 = true;

	/* Excessive Threshold रेजिस्टर - exists क्रम pre-FMv3 chips only */
	अगर (port->rev_info.major < 6)
		cfg->excessive_threshold_रेजिस्टर = true;
	अन्यथा
		cfg->fmbm_tfne_has_features = true;

	cfg->buffer_prefix_content.data_align =
		DFLT_PORT_BUFFER_PREFIX_CONTEXT_DATA_ALIGN;
पूर्ण

अटल व्योम set_rx_dflt_cfg(काष्ठा fman_port *port,
			    काष्ठा fman_port_params *port_params)
अणु
	port->cfg->discard_mask = DFLT_PORT_ERRORS_TO_DISCARD;

	स_नकल(&port->cfg->ext_buf_pools,
	       &port_params->specअगरic_params.rx_params.ext_buf_pools,
	       माप(काष्ठा fman_ext_pools));
	port->cfg->err_fqid =
		port_params->specअगरic_params.rx_params.err_fqid;
	port->cfg->dflt_fqid =
		port_params->specअगरic_params.rx_params.dflt_fqid;
	port->cfg->pcd_base_fqid =
		port_params->specअगरic_params.rx_params.pcd_base_fqid;
	port->cfg->pcd_fqs_count =
		port_params->specअगरic_params.rx_params.pcd_fqs_count;
पूर्ण

अटल व्योम set_tx_dflt_cfg(काष्ठा fman_port *port,
			    काष्ठा fman_port_params *port_params,
			    काष्ठा fman_port_dts_params *dts_params)
अणु
	port->cfg->tx_fअगरo_deq_pipeline_depth =
		get_dflt_fअगरo_deq_pipeline_depth(port->rev_info.major,
						 port->port_type,
						 port->port_speed);
	port->cfg->err_fqid =
		port_params->specअगरic_params.non_rx_params.err_fqid;
	port->cfg->deq_sp =
		(u8)(dts_params->qman_channel_id & QMI_DEQ_CFG_SUBPORTAL_MASK);
	port->cfg->dflt_fqid =
		port_params->specअगरic_params.non_rx_params.dflt_fqid;
	port->cfg->deq_high_priority = true;
पूर्ण

/**
 * fman_port_config
 * @port:	Poपूर्णांकer to the port काष्ठाure
 * @params:	Poपूर्णांकer to data काष्ठाure of parameters
 *
 * Creates a descriptor क्रम the FM PORT module.
 * The routine वापसs a poपूर्णांकer to the FM PORT object.
 * This descriptor must be passed as first parameter to all other FM PORT
 * function calls.
 * No actual initialization or configuration of FM hardware is करोne by this
 * routine.
 *
 * Return: 0 on success; Error code otherwise.
 */
पूर्णांक fman_port_config(काष्ठा fman_port *port, काष्ठा fman_port_params *params)
अणु
	व्योम __iomem *base_addr = port->dts_params.base_addr;
	पूर्णांक err;

	/* Allocate the FM driver's parameters काष्ठाure */
	port->cfg = kzalloc(माप(*port->cfg), GFP_KERNEL);
	अगर (!port->cfg)
		वापस -EINVAL;

	/* Initialize FM port parameters which will be kept by the driver */
	port->port_type = port->dts_params.type;
	port->port_speed = port->dts_params.speed;
	port->port_id = port->dts_params.id;
	port->fm = port->dts_params.fman;
	port->ext_pools_num = (u8)8;

	/* get FM revision */
	fman_get_revision(port->fm, &port->rev_info);

	err = fill_soc_specअगरic_params(port);
	अगर (err)
		जाओ err_port_cfg;

	चयन (port->port_type) अणु
	हाल FMAN_PORT_TYPE_RX:
		set_rx_dflt_cfg(port, params);
		fallthrough;
	हाल FMAN_PORT_TYPE_TX:
		set_tx_dflt_cfg(port, params, &port->dts_params);
		fallthrough;
	शेष:
		set_dflt_cfg(port, params);
	पूर्ण

	/* Continue with other parameters */
	/* set memory map poपूर्णांकers */
	port->bmi_regs = base_addr + BMI_PORT_REGS_OFFSET;
	port->qmi_regs = base_addr + QMI_PORT_REGS_OFFSET;
	port->hwp_regs = base_addr + HWP_PORT_REGS_OFFSET;

	port->max_frame_length = DFLT_PORT_MAX_FRAME_LENGTH;
	/* resource distribution. */

	port->fअगरo_bufs.num =
	get_dflt_num_of_fअगरo_bufs(port->rev_info.major, port->port_type,
				  port->port_speed) * FMAN_BMI_FIFO_UNITS;
	port->fअगरo_bufs.extra =
	DFLT_PORT_EXTRA_NUM_OF_FIFO_BUFS * FMAN_BMI_FIFO_UNITS;

	port->खोलो_dmas.num =
	get_dflt_num_of_खोलो_dmas(port->rev_info.major,
				  port->port_type, port->port_speed);
	port->खोलो_dmas.extra =
	get_dflt_extra_num_of_खोलो_dmas(port->rev_info.major,
					port->port_type, port->port_speed);
	port->tasks.num =
	get_dflt_num_of_tasks(port->rev_info.major,
			      port->port_type, port->port_speed);
	port->tasks.extra =
	get_dflt_extra_num_of_tasks(port->rev_info.major,
				    port->port_type, port->port_speed);

	/* FM_HEAVY_TRAFFIC_SEQUENCER_HANG_ERRATA_FMAN_A006981 errata
	 * workaround
	 */
	अगर ((port->rev_info.major == 6) && (port->rev_info.minor == 0) &&
	    (((port->port_type == FMAN_PORT_TYPE_TX) &&
	    (port->port_speed == 1000)))) अणु
		port->खोलो_dmas.num = 16;
		port->खोलो_dmas.extra = 0;
	पूर्ण

	अगर (port->rev_info.major >= 6 &&
	    port->port_type == FMAN_PORT_TYPE_TX &&
	    port->port_speed == 1000) अणु
		/* FM_WRONG_RESET_VALUES_ERRATA_FMAN_A005127 Errata
		 * workaround
		 */
		u32 reg;

		reg = 0x00001013;
		ioग_लिखो32be(reg, &port->bmi_regs->tx.fmbm_tfp);
	पूर्ण

	वापस 0;

err_port_cfg:
	kमुक्त(port->cfg);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(fman_port_config);

/*
 * fman_port_use_kg_hash
 * @port: A poपूर्णांकer to a FM Port module.
 * @enable: enable or disable
 *
 * Sets the HW KeyGen or the BMI as HW Parser next engine, enabling
 * or bypassing the KeyGen hashing of Rx traffic
 */
व्योम fman_port_use_kg_hash(काष्ठा fman_port *port, bool enable)
अणु
	अगर (enable)
		/* After the Parser frames go to KeyGen */
		ioग_लिखो32be(NIA_ENG_HWK, &port->bmi_regs->rx.fmbm_rfpne);
	अन्यथा
		/* After the Parser frames go to BMI */
		ioग_लिखो32be(NIA_ENG_BMI | NIA_BMI_AC_ENQ_FRAME,
			    &port->bmi_regs->rx.fmbm_rfpne);
पूर्ण
EXPORT_SYMBOL(fman_port_use_kg_hash);

/**
 * fman_port_init
 * @port:	A poपूर्णांकer to a FM Port module.
 *
 * Initializes the FM PORT module by defining the software काष्ठाure and
 * configuring the hardware रेजिस्टरs.
 *
 * Return: 0 on success; Error code otherwise.
 */
पूर्णांक fman_port_init(काष्ठा fman_port *port)
अणु
	काष्ठा fman_port_init_params params;
	काष्ठा fman_keygen *keygen;
	काष्ठा fman_port_cfg *cfg;
	पूर्णांक err;

	अगर (is_init_करोne(port->cfg))
		वापस -EINVAL;

	err = fman_sp_build_buffer_काष्ठा(&port->cfg->पूर्णांक_context,
					  &port->cfg->buffer_prefix_content,
					  &port->cfg->buf_margins,
					  &port->buffer_offsets,
					  &port->पूर्णांकernal_buf_offset);
	अगर (err)
		वापस err;

	cfg = port->cfg;

	अगर (port->port_type == FMAN_PORT_TYPE_RX) अणु
		/* Call the बाह्यal Buffer routine which also checks fअगरo
		 * size and updates it अगर necessary
		 */
		/* define बाह्यal buffer pools and pool depletion */
		err = set_ext_buffer_pools(port);
		अगर (err)
			वापस err;
		/* check अगर the largest बाह्यal buffer pool is large enough */
		अगर (cfg->buf_margins.start_margins + MIN_EXT_BUF_SIZE +
		    cfg->buf_margins.end_margins >
		    port->rx_pools_params.largest_buf_size) अणु
			dev_err(port->dev, "%s: buf_margins.start_margins (%d) + minimum buf size (64) + buf_margins.end_margins (%d) is larger than maximum external buffer size (%d)\n",
				__func__, cfg->buf_margins.start_margins,
				cfg->buf_margins.end_margins,
				port->rx_pools_params.largest_buf_size);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Call FM module routine क्रम communicating parameters */
	स_रखो(&params, 0, माप(params));
	params.port_id = port->port_id;
	params.port_type = port->port_type;
	params.port_speed = port->port_speed;
	params.num_of_tasks = (u8)port->tasks.num;
	params.num_of_extra_tasks = (u8)port->tasks.extra;
	params.num_of_खोलो_dmas = (u8)port->खोलो_dmas.num;
	params.num_of_extra_खोलो_dmas = (u8)port->खोलो_dmas.extra;

	अगर (port->fअगरo_bufs.num) अणु
		err = verअगरy_size_of_fअगरo(port);
		अगर (err)
			वापस err;
	पूर्ण
	params.size_of_fअगरo = port->fअगरo_bufs.num;
	params.extra_size_of_fअगरo = port->fअगरo_bufs.extra;
	params.deq_pipeline_depth = port->cfg->tx_fअगरo_deq_pipeline_depth;
	params.max_frame_length = port->max_frame_length;

	err = fman_set_port_params(port->fm, &params);
	अगर (err)
		वापस err;

	err = init_low_level_driver(port);
	अगर (err)
		वापस err;

	अगर (port->cfg->pcd_fqs_count) अणु
		keygen = port->dts_params.fman->keygen;
		err = keygen_port_hashing_init(keygen, port->port_id,
					       port->cfg->pcd_base_fqid,
					       port->cfg->pcd_fqs_count);
		अगर (err)
			वापस err;

		fman_port_use_kg_hash(port, true);
	पूर्ण

	kमुक्त(port->cfg);
	port->cfg = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fman_port_init);

/**
 * fman_port_cfg_buf_prefix_content
 * @port:			A poपूर्णांकer to a FM Port module.
 * @buffer_prefix_content:	A काष्ठाure of parameters describing
 *				the काष्ठाure of the buffer.
 *				Out parameter:
 *				Start margin - offset of data from
 *				start of बाह्यal buffer.
 * Defines the काष्ठाure, size and content of the application buffer.
 * The prefix, in Tx ports, अगर 'pass_prs_result', the application should set
 * a value to their offsets in the prefix of the FM will save the first
 * 'priv_data_size', than, depending on 'pass_prs_result' and
 * 'pass_time_stamp', copy parse result and समयStamp, and the packet itself
 * (in this order), to the application buffer, and to offset.
 * Calling this routine changes the buffer margins definitions in the पूर्णांकernal
 * driver data base from its शेष configuration:
 * Data size:  [DEFAULT_PORT_BUFFER_PREFIX_CONTENT_PRIV_DATA_SIZE]
 * Pass Parser result: [DEFAULT_PORT_BUFFER_PREFIX_CONTENT_PASS_PRS_RESULT].
 * Pass बारtamp: [DEFAULT_PORT_BUFFER_PREFIX_CONTENT_PASS_TIME_STAMP].
 * May be used क्रम all ports
 *
 * Allowed only following fman_port_config() and beक्रमe fman_port_init().
 *
 * Return: 0 on success; Error code otherwise.
 */
पूर्णांक fman_port_cfg_buf_prefix_content(काष्ठा fman_port *port,
				     काष्ठा fman_buffer_prefix_content *
				     buffer_prefix_content)
अणु
	अगर (is_init_करोne(port->cfg))
		वापस -EINVAL;

	स_नकल(&port->cfg->buffer_prefix_content,
	       buffer_prefix_content,
	       माप(काष्ठा fman_buffer_prefix_content));
	/* अगर data_align was not initialized by user,
	 * we वापस to driver's शेष
	 */
	अगर (!port->cfg->buffer_prefix_content.data_align)
		port->cfg->buffer_prefix_content.data_align =
		DFLT_PORT_BUFFER_PREFIX_CONTEXT_DATA_ALIGN;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fman_port_cfg_buf_prefix_content);

/**
 * fman_port_disable
 * @port:	A poपूर्णांकer to a FM Port module.
 *
 * Gracefully disable an FM port. The port will not start new	tasks after all
 * tasks associated with the port are terminated.
 *
 * This is a blocking routine, it वापसs after port is gracefully stopped,
 * i.e. the port will not except new frames, but it will finish all frames
 * or tasks which were alपढ़ोy began.
 * Allowed only following fman_port_init().
 *
 * Return: 0 on success; Error code otherwise.
 */
पूर्णांक fman_port_disable(काष्ठा fman_port *port)
अणु
	u32 __iomem *bmi_cfg_reg, *bmi_status_reg;
	u32 पंचांगp;
	bool rx_port, failure = false;
	पूर्णांक count;

	अगर (!is_init_करोne(port->cfg))
		वापस -EINVAL;

	चयन (port->port_type) अणु
	हाल FMAN_PORT_TYPE_RX:
		bmi_cfg_reg = &port->bmi_regs->rx.fmbm_rcfg;
		bmi_status_reg = &port->bmi_regs->rx.fmbm_rst;
		rx_port = true;
		अवरोध;
	हाल FMAN_PORT_TYPE_TX:
		bmi_cfg_reg = &port->bmi_regs->tx.fmbm_tcfg;
		bmi_status_reg = &port->bmi_regs->tx.fmbm_tst;
		rx_port = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Disable QMI */
	अगर (!rx_port) अणु
		पंचांगp = ioपढ़ो32be(&port->qmi_regs->fmqm_pnc) & ~QMI_PORT_CFG_EN;
		ioग_लिखो32be(पंचांगp, &port->qmi_regs->fmqm_pnc);

		/* Wait क्रम QMI to finish FD handling */
		count = 100;
		करो अणु
			udelay(10);
			पंचांगp = ioपढ़ो32be(&port->qmi_regs->fmqm_pns);
		पूर्ण जबतक ((पंचांगp & QMI_PORT_STATUS_DEQ_FD_BSY) && --count);

		अगर (count == 0) अणु
			/* Timeout */
			failure = true;
		पूर्ण
	पूर्ण

	/* Disable BMI */
	पंचांगp = ioपढ़ो32be(bmi_cfg_reg) & ~BMI_PORT_CFG_EN;
	ioग_लिखो32be(पंचांगp, bmi_cfg_reg);

	/* Wait क्रम graceful stop end */
	count = 500;
	करो अणु
		udelay(10);
		पंचांगp = ioपढ़ो32be(bmi_status_reg);
	पूर्ण जबतक ((पंचांगp & BMI_PORT_STATUS_BSY) && --count);

	अगर (count == 0) अणु
		/* Timeout */
		failure = true;
	पूर्ण

	अगर (failure)
		dev_dbg(port->dev, "%s: FMan Port[%d]: BMI or QMI is Busy. Port forced down\n",
			__func__,  port->port_id);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fman_port_disable);

/**
 * fman_port_enable
 * @port:	A poपूर्णांकer to a FM Port module.
 *
 * A runसमय routine provided to allow disable/enable of port.
 *
 * Allowed only following fman_port_init().
 *
 * Return: 0 on success; Error code otherwise.
 */
पूर्णांक fman_port_enable(काष्ठा fman_port *port)
अणु
	u32 __iomem *bmi_cfg_reg;
	u32 पंचांगp;
	bool rx_port;

	अगर (!is_init_करोne(port->cfg))
		वापस -EINVAL;

	चयन (port->port_type) अणु
	हाल FMAN_PORT_TYPE_RX:
		bmi_cfg_reg = &port->bmi_regs->rx.fmbm_rcfg;
		rx_port = true;
		अवरोध;
	हाल FMAN_PORT_TYPE_TX:
		bmi_cfg_reg = &port->bmi_regs->tx.fmbm_tcfg;
		rx_port = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Enable QMI */
	अगर (!rx_port) अणु
		पंचांगp = ioपढ़ो32be(&port->qmi_regs->fmqm_pnc) | QMI_PORT_CFG_EN;
		ioग_लिखो32be(पंचांगp, &port->qmi_regs->fmqm_pnc);
	पूर्ण

	/* Enable BMI */
	पंचांगp = ioपढ़ो32be(bmi_cfg_reg) | BMI_PORT_CFG_EN;
	ioग_लिखो32be(पंचांगp, bmi_cfg_reg);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fman_port_enable);

/**
 * fman_port_bind
 * @dev:		FMan Port OF device poपूर्णांकer
 *
 * Bind to a specअगरic FMan Port.
 *
 * Allowed only after the port was created.
 *
 * Return: A poपूर्णांकer to the FMan port device.
 */
काष्ठा fman_port *fman_port_bind(काष्ठा device *dev)
अणु
	वापस (काष्ठा fman_port *)(dev_get_drvdata(get_device(dev)));
पूर्ण
EXPORT_SYMBOL(fman_port_bind);

/**
 * fman_port_get_qman_channel_id
 * @port:	Poपूर्णांकer to the FMan port devuce
 *
 * Get the QMan channel ID क्रम the specअगरic port
 *
 * Return: QMan channel ID
 */
u32 fman_port_get_qman_channel_id(काष्ठा fman_port *port)
अणु
	वापस port->dts_params.qman_channel_id;
पूर्ण
EXPORT_SYMBOL(fman_port_get_qman_channel_id);

/**
 * fman_port_get_device
 * @port:	Poपूर्णांकer to the FMan port device
 *
 * Get the 'struct device' associated to the specअगरied FMan port device
 *
 * Return: poपूर्णांकer to associated 'struct device'
 */
काष्ठा device *fman_port_get_device(काष्ठा fman_port *port)
अणु
	वापस port->dev;
पूर्ण
EXPORT_SYMBOL(fman_port_get_device);

पूर्णांक fman_port_get_hash_result_offset(काष्ठा fman_port *port, u32 *offset)
अणु
	अगर (port->buffer_offsets.hash_result_offset == ILLEGAL_BASE)
		वापस -EINVAL;

	*offset = port->buffer_offsets.hash_result_offset;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fman_port_get_hash_result_offset);

पूर्णांक fman_port_get_tstamp(काष्ठा fman_port *port, स्थिर व्योम *data, u64 *tstamp)
अणु
	अगर (port->buffer_offsets.समय_stamp_offset == ILLEGAL_BASE)
		वापस -EINVAL;

	*tstamp = be64_to_cpu(*(__be64 *)(data +
			port->buffer_offsets.समय_stamp_offset));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fman_port_get_tstamp);

अटल पूर्णांक fman_port_probe(काष्ठा platक्रमm_device *of_dev)
अणु
	काष्ठा fman_port *port;
	काष्ठा fman *fman;
	काष्ठा device_node *fm_node, *port_node;
	काष्ठा platक्रमm_device *fm_pdev;
	काष्ठा resource res;
	काष्ठा resource *dev_res;
	u32 val;
	पूर्णांक err = 0, lenp;
	क्रमागत fman_port_type port_type;
	u16 port_speed;
	u8 port_id;

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	port->dev = &of_dev->dev;

	port_node = of_node_get(of_dev->dev.of_node);

	/* Get the FM node */
	fm_node = of_get_parent(port_node);
	अगर (!fm_node) अणु
		dev_err(port->dev, "%s: of_get_parent() failed\n", __func__);
		err = -ENODEV;
		जाओ वापस_err;
	पूर्ण

	fm_pdev = of_find_device_by_node(fm_node);
	of_node_put(fm_node);
	अगर (!fm_pdev) अणु
		err = -EINVAL;
		जाओ वापस_err;
	पूर्ण

	fman = dev_get_drvdata(&fm_pdev->dev);
	अगर (!fman) अणु
		err = -EINVAL;
		जाओ वापस_err;
	पूर्ण

	err = of_property_पढ़ो_u32(port_node, "cell-index", &val);
	अगर (err) अणु
		dev_err(port->dev, "%s: reading cell-index for %pOF failed\n",
			__func__, port_node);
		err = -EINVAL;
		जाओ वापस_err;
	पूर्ण
	port_id = (u8)val;
	port->dts_params.id = port_id;

	अगर (of_device_is_compatible(port_node, "fsl,fman-v3-port-tx")) अणु
		port_type = FMAN_PORT_TYPE_TX;
		port_speed = 1000;
		अगर (of_find_property(port_node, "fsl,fman-10g-port", &lenp))
			port_speed = 10000;

	पूर्ण अन्यथा अगर (of_device_is_compatible(port_node, "fsl,fman-v2-port-tx")) अणु
		अगर (port_id >= TX_10G_PORT_BASE)
			port_speed = 10000;
		अन्यथा
			port_speed = 1000;
		port_type = FMAN_PORT_TYPE_TX;

	पूर्ण अन्यथा अगर (of_device_is_compatible(port_node, "fsl,fman-v3-port-rx")) अणु
		port_type = FMAN_PORT_TYPE_RX;
		port_speed = 1000;
		अगर (of_find_property(port_node, "fsl,fman-10g-port", &lenp))
			port_speed = 10000;

	पूर्ण अन्यथा अगर (of_device_is_compatible(port_node, "fsl,fman-v2-port-rx")) अणु
		अगर (port_id >= RX_10G_PORT_BASE)
			port_speed = 10000;
		अन्यथा
			port_speed = 1000;
		port_type = FMAN_PORT_TYPE_RX;

	पूर्ण  अन्यथा अणु
		dev_err(port->dev, "%s: Illegal port type\n", __func__);
		err = -EINVAL;
		जाओ वापस_err;
	पूर्ण

	port->dts_params.type = port_type;
	port->dts_params.speed = port_speed;

	अगर (port_type == FMAN_PORT_TYPE_TX) अणु
		u32 qman_channel_id;

		qman_channel_id = fman_get_qman_channel_id(fman, port_id);
		अगर (qman_channel_id == 0) अणु
			dev_err(port->dev, "%s: incorrect qman-channel-id\n",
				__func__);
			err = -EINVAL;
			जाओ वापस_err;
		पूर्ण
		port->dts_params.qman_channel_id = qman_channel_id;
	पूर्ण

	err = of_address_to_resource(port_node, 0, &res);
	अगर (err < 0) अणु
		dev_err(port->dev, "%s: of_address_to_resource() failed\n",
			__func__);
		err = -ENOMEM;
		जाओ वापस_err;
	पूर्ण

	port->dts_params.fman = fman;

	of_node_put(port_node);

	dev_res = __devm_request_region(port->dev, &res, res.start,
					resource_size(&res), "fman-port");
	अगर (!dev_res) अणु
		dev_err(port->dev, "%s: __devm_request_region() failed\n",
			__func__);
		err = -EINVAL;
		जाओ मुक्त_port;
	पूर्ण

	port->dts_params.base_addr = devm_ioremap(port->dev, res.start,
						  resource_size(&res));
	अगर (!port->dts_params.base_addr)
		dev_err(port->dev, "%s: devm_ioremap() failed\n", __func__);

	dev_set_drvdata(&of_dev->dev, port);

	वापस 0;

वापस_err:
	of_node_put(port_node);
मुक्त_port:
	kमुक्त(port);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id fman_port_match[] = अणु
	अणु.compatible = "fsl,fman-v3-port-rx"पूर्ण,
	अणु.compatible = "fsl,fman-v2-port-rx"पूर्ण,
	अणु.compatible = "fsl,fman-v3-port-tx"पूर्ण,
	अणु.compatible = "fsl,fman-v2-port-tx"पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, fman_port_match);

अटल काष्ठा platक्रमm_driver fman_port_driver = अणु
	.driver = अणु
		.name = "fsl-fman-port",
		.of_match_table = fman_port_match,
	पूर्ण,
	.probe = fman_port_probe,
पूर्ण;

अटल पूर्णांक __init fman_port_load(व्योम)
अणु
	पूर्णांक err;

	pr_debug("FSL DPAA FMan driver\n");

	err = platक्रमm_driver_रेजिस्टर(&fman_port_driver);
	अगर (err < 0)
		pr_err("Error, platform_driver_register() = %d\n", err);

	वापस err;
पूर्ण
module_init(fman_port_load);

अटल व्योम __निकास fman_port_unload(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&fman_port_driver);
पूर्ण
module_निकास(fman_port_unload);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Freescale DPAA Frame Manager Port driver");
