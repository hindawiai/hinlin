<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017-2020, The Linux Foundation. All rights reserved.
 * Copyright (c) 2020, Linaro Limited
 */

#समावेश <dt-bindings/dma/qcom-gpi.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/module.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma/qcom-gpi-dma.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश "../dmaengine.h"
#समावेश "../virt-dma.h"

#घोषणा TRE_TYPE_DMA		0x10
#घोषणा TRE_TYPE_GO		0x20
#घोषणा TRE_TYPE_CONFIG0	0x22

/* TRE flags */
#घोषणा TRE_FLAGS_CHAIN		BIT(0)
#घोषणा TRE_FLAGS_IEOB		BIT(8)
#घोषणा TRE_FLAGS_IEOT		BIT(9)
#घोषणा TRE_FLAGS_BEI		BIT(10)
#घोषणा TRE_FLAGS_LINK		BIT(11)
#घोषणा TRE_FLAGS_TYPE		GENMASK(23, 16)

/* SPI CONFIG0 WD0 */
#घोषणा TRE_SPI_C0_WORD_SZ	GENMASK(4, 0)
#घोषणा TRE_SPI_C0_LOOPBACK	BIT(8)
#घोषणा TRE_SPI_C0_CS		BIT(11)
#घोषणा TRE_SPI_C0_CPHA		BIT(12)
#घोषणा TRE_SPI_C0_CPOL		BIT(13)
#घोषणा TRE_SPI_C0_TX_PACK	BIT(24)
#घोषणा TRE_SPI_C0_RX_PACK	BIT(25)

/* CONFIG0 WD2 */
#घोषणा TRE_C0_CLK_DIV		GENMASK(11, 0)
#घोषणा TRE_C0_CLK_SRC		GENMASK(19, 16)

/* SPI GO WD0 */
#घोषणा TRE_SPI_GO_CMD		GENMASK(4, 0)
#घोषणा TRE_SPI_GO_CS		GENMASK(10, 8)
#घोषणा TRE_SPI_GO_FRAG		BIT(26)

/* GO WD2 */
#घोषणा TRE_RX_LEN		GENMASK(23, 0)

/* I2C Config0 WD0 */
#घोषणा TRE_I2C_C0_TLOW		GENMASK(7, 0)
#घोषणा TRE_I2C_C0_THIGH	GENMASK(15, 8)
#घोषणा TRE_I2C_C0_TCYL		GENMASK(23, 16)
#घोषणा TRE_I2C_C0_TX_PACK	BIT(24)
#घोषणा TRE_I2C_C0_RX_PACK      BIT(25)

/* I2C GO WD0 */
#घोषणा TRE_I2C_GO_CMD          GENMASK(4, 0)
#घोषणा TRE_I2C_GO_ADDR		GENMASK(14, 8)
#घोषणा TRE_I2C_GO_STRETCH	BIT(26)

/* DMA TRE */
#घोषणा TRE_DMA_LEN		GENMASK(23, 0)

/* Register offsets from gpi-top */
#घोषणा GPII_n_CH_k_CNTXT_0_OFFS(n, k)	(0x20000 + (0x4000 * (n)) + (0x80 * (k)))
#घोषणा GPII_n_CH_k_CNTXT_0_EL_SIZE	GENMASK(31, 24)
#घोषणा GPII_n_CH_k_CNTXT_0_CHSTATE	GENMASK(23, 20)
#घोषणा GPII_n_CH_k_CNTXT_0_ERIDX	GENMASK(18, 14)
#घोषणा GPII_n_CH_k_CNTXT_0_सूची		BIT(3)
#घोषणा GPII_n_CH_k_CNTXT_0_PROTO	GENMASK(2, 0)

#घोषणा GPII_n_CH_k_CNTXT_0(el_size, erindex, dir, chtype_proto)  \
	(FIELD_PREP(GPII_n_CH_k_CNTXT_0_EL_SIZE, el_size)	| \
	 FIELD_PREP(GPII_n_CH_k_CNTXT_0_ERIDX, erindex)		| \
	 FIELD_PREP(GPII_n_CH_k_CNTXT_0_सूची, dir)		| \
	 FIELD_PREP(GPII_n_CH_k_CNTXT_0_PROTO, chtype_proto))

#घोषणा GPI_CHTYPE_सूची_IN	(0)
#घोषणा GPI_CHTYPE_सूची_OUT	(1)

#घोषणा GPI_CHTYPE_PROTO_GPI	(0x2)

#घोषणा GPII_n_CH_k_DOORBELL_0_OFFS(n, k)	(0x22000 + (0x4000 * (n)) + (0x8 * (k)))
#घोषणा GPII_n_CH_CMD_OFFS(n)			(0x23008 + (0x4000 * (n)))
#घोषणा GPII_n_CH_CMD_OPCODE			GENMASK(31, 24)
#घोषणा GPII_n_CH_CMD_CHID			GENMASK(7, 0)
#घोषणा GPII_n_CH_CMD(opcode, chid)				 \
		     (FIELD_PREP(GPII_n_CH_CMD_OPCODE, opcode) | \
		      FIELD_PREP(GPII_n_CH_CMD_CHID, chid))

#घोषणा GPII_n_CH_CMD_ALLOCATE		(0)
#घोषणा GPII_n_CH_CMD_START		(1)
#घोषणा GPII_n_CH_CMD_STOP		(2)
#घोषणा GPII_n_CH_CMD_RESET		(9)
#घोषणा GPII_n_CH_CMD_DE_ALLOC		(10)
#घोषणा GPII_n_CH_CMD_UART_SW_STALE	(32)
#घोषणा GPII_n_CH_CMD_UART_RFR_READY	(33)
#घोषणा GPII_n_CH_CMD_UART_RFR_NOT_READY (34)

/* EV Context Array */
#घोषणा GPII_n_EV_CH_k_CNTXT_0_OFFS(n, k) (0x21000 + (0x4000 * (n)) + (0x80 * (k)))
#घोषणा GPII_n_EV_k_CNTXT_0_EL_SIZE	GENMASK(31, 24)
#घोषणा GPII_n_EV_k_CNTXT_0_CHSTATE	GENMASK(23, 20)
#घोषणा GPII_n_EV_k_CNTXT_0_INTYPE	BIT(16)
#घोषणा GPII_n_EV_k_CNTXT_0_CHTYPE	GENMASK(3, 0)

#घोषणा GPII_n_EV_k_CNTXT_0(el_size, पूर्णांकtype, chtype)		\
	(FIELD_PREP(GPII_n_EV_k_CNTXT_0_EL_SIZE, el_size) |	\
	 FIELD_PREP(GPII_n_EV_k_CNTXT_0_INTYPE, पूर्णांकtype)  |	\
	 FIELD_PREP(GPII_n_EV_k_CNTXT_0_CHTYPE, chtype))

#घोषणा GPI_INTTYPE_IRQ		(1)
#घोषणा GPI_CHTYPE_GPI_EV	(0x2)

क्रमागत CNTXT_OFFS अणु
	CNTXT_0_CONFIG = 0x0,
	CNTXT_1_R_LENGTH = 0x4,
	CNTXT_2_RING_BASE_LSB = 0x8,
	CNTXT_3_RING_BASE_MSB = 0xC,
	CNTXT_4_RING_RP_LSB = 0x10,
	CNTXT_5_RING_RP_MSB = 0x14,
	CNTXT_6_RING_WP_LSB = 0x18,
	CNTXT_7_RING_WP_MSB = 0x1C,
	CNTXT_8_RING_INT_MOD = 0x20,
	CNTXT_9_RING_INTVEC = 0x24,
	CNTXT_10_RING_MSI_LSB = 0x28,
	CNTXT_11_RING_MSI_MSB = 0x2C,
	CNTXT_12_RING_RP_UPDATE_LSB = 0x30,
	CNTXT_13_RING_RP_UPDATE_MSB = 0x34,
पूर्ण;

#घोषणा GPII_n_EV_CH_k_DOORBELL_0_OFFS(n, k)	(0x22100 + (0x4000 * (n)) + (0x8 * (k)))
#घोषणा GPII_n_EV_CH_CMD_OFFS(n)		(0x23010 + (0x4000 * (n)))
#घोषणा GPII_n_EV_CMD_OPCODE			GENMASK(31, 24)
#घोषणा GPII_n_EV_CMD_CHID			GENMASK(7, 0)
#घोषणा GPII_n_EV_CMD(opcode, chid)				 \
		     (FIELD_PREP(GPII_n_EV_CMD_OPCODE, opcode) | \
		      FIELD_PREP(GPII_n_EV_CMD_CHID, chid))

#घोषणा GPII_n_EV_CH_CMD_ALLOCATE		(0x00)
#घोषणा GPII_n_EV_CH_CMD_RESET			(0x09)
#घोषणा GPII_n_EV_CH_CMD_DE_ALLOC		(0x0A)

#घोषणा GPII_n_CNTXT_TYPE_IRQ_OFFS(n)		(0x23080 + (0x4000 * (n)))

/* mask type रेजिस्टर */
#घोषणा GPII_n_CNTXT_TYPE_IRQ_MSK_OFFS(n)	(0x23088 + (0x4000 * (n)))
#घोषणा GPII_n_CNTXT_TYPE_IRQ_MSK_BMSK		GENMASK(6, 0)
#घोषणा GPII_n_CNTXT_TYPE_IRQ_MSK_GENERAL	BIT(6)
#घोषणा GPII_n_CNTXT_TYPE_IRQ_MSK_IEOB		BIT(3)
#घोषणा GPII_n_CNTXT_TYPE_IRQ_MSK_GLOB		BIT(2)
#घोषणा GPII_n_CNTXT_TYPE_IRQ_MSK_EV_CTRL	BIT(1)
#घोषणा GPII_n_CNTXT_TYPE_IRQ_MSK_CH_CTRL	BIT(0)

#घोषणा GPII_n_CNTXT_SRC_GPII_CH_IRQ_OFFS(n)	(0x23090 + (0x4000 * (n)))
#घोषणा GPII_n_CNTXT_SRC_EV_CH_IRQ_OFFS(n)	(0x23094 + (0x4000 * (n)))

/* Mask channel control पूर्णांकerrupt रेजिस्टर */
#घोषणा GPII_n_CNTXT_SRC_CH_IRQ_MSK_OFFS(n)	(0x23098 + (0x4000 * (n)))
#घोषणा GPII_n_CNTXT_SRC_CH_IRQ_MSK_BMSK	GENMASK(1, 0)

/* Mask event control पूर्णांकerrupt रेजिस्टर */
#घोषणा GPII_n_CNTXT_SRC_EV_CH_IRQ_MSK_OFFS(n)	(0x2309C + (0x4000 * (n)))
#घोषणा GPII_n_CNTXT_SRC_EV_CH_IRQ_MSK_BMSK	BIT(0)

#घोषणा GPII_n_CNTXT_SRC_CH_IRQ_CLR_OFFS(n)	(0x230A0 + (0x4000 * (n)))
#घोषणा GPII_n_CNTXT_SRC_EV_CH_IRQ_CLR_OFFS(n)	(0x230A4 + (0x4000 * (n)))

/* Mask event पूर्णांकerrupt रेजिस्टर */
#घोषणा GPII_n_CNTXT_SRC_IEOB_IRQ_MSK_OFFS(n)	(0x230B8 + (0x4000 * (n)))
#घोषणा GPII_n_CNTXT_SRC_IEOB_IRQ_MSK_BMSK	BIT(0)

#घोषणा GPII_n_CNTXT_SRC_IEOB_IRQ_CLR_OFFS(n)	(0x230C0 + (0x4000 * (n)))
#घोषणा GPII_n_CNTXT_GLOB_IRQ_STTS_OFFS(n)	(0x23100 + (0x4000 * (n)))
#घोषणा GPI_GLOB_IRQ_ERROR_INT_MSK		BIT(0)

/* GPII specअगरic Global - Enable bit रेजिस्टर */
#घोषणा GPII_n_CNTXT_GLOB_IRQ_EN_OFFS(n)	(0x23108 + (0x4000 * (n)))
#घोषणा GPII_n_CNTXT_GLOB_IRQ_CLR_OFFS(n)	(0x23110 + (0x4000 * (n)))
#घोषणा GPII_n_CNTXT_GPII_IRQ_STTS_OFFS(n)	(0x23118 + (0x4000 * (n)))

/* GPII general पूर्णांकerrupt - Enable bit रेजिस्टर */
#घोषणा GPII_n_CNTXT_GPII_IRQ_EN_OFFS(n)	(0x23120 + (0x4000 * (n)))
#घोषणा GPII_n_CNTXT_GPII_IRQ_EN_BMSK		GENMASK(3, 0)

#घोषणा GPII_n_CNTXT_GPII_IRQ_CLR_OFFS(n)	(0x23128 + (0x4000 * (n)))

/* GPII Interrupt Type रेजिस्टर */
#घोषणा GPII_n_CNTXT_INTSET_OFFS(n)		(0x23180 + (0x4000 * (n)))
#घोषणा GPII_n_CNTXT_INTSET_BMSK		BIT(0)

#घोषणा GPII_n_CNTXT_MSI_BASE_LSB_OFFS(n)	(0x23188 + (0x4000 * (n)))
#घोषणा GPII_n_CNTXT_MSI_BASE_MSB_OFFS(n)	(0x2318C + (0x4000 * (n)))
#घोषणा GPII_n_CNTXT_SCRATCH_0_OFFS(n)		(0x23400 + (0x4000 * (n)))
#घोषणा GPII_n_CNTXT_SCRATCH_1_OFFS(n)		(0x23404 + (0x4000 * (n)))

#घोषणा GPII_n_ERROR_LOG_OFFS(n)		(0x23200 + (0x4000 * (n)))

/* QOS Registers */
#घोषणा GPII_n_CH_k_QOS_OFFS(n, k)		(0x2005C + (0x4000 * (n)) + (0x80 * (k)))

/* Scratch रेजिस्टरs */
#घोषणा GPII_n_CH_k_SCRATCH_0_OFFS(n, k)	(0x20060 + (0x4000 * (n)) + (0x80 * (k)))
#घोषणा GPII_n_CH_k_SCRATCH_0_SEID		GENMASK(2, 0)
#घोषणा GPII_n_CH_k_SCRATCH_0_PROTO		GENMASK(7, 4)
#घोषणा GPII_n_CH_k_SCRATCH_0_PAIR		GENMASK(20, 16)
#घोषणा GPII_n_CH_k_SCRATCH_0(pair, proto, seid)		\
			     (FIELD_PREP(GPII_n_CH_k_SCRATCH_0_PAIR, pair)	| \
			      FIELD_PREP(GPII_n_CH_k_SCRATCH_0_PROTO, proto)	| \
			      FIELD_PREP(GPII_n_CH_k_SCRATCH_0_SEID, seid))
#घोषणा GPII_n_CH_k_SCRATCH_1_OFFS(n, k)	(0x20064 + (0x4000 * (n)) + (0x80 * (k)))
#घोषणा GPII_n_CH_k_SCRATCH_2_OFFS(n, k)	(0x20068 + (0x4000 * (n)) + (0x80 * (k)))
#घोषणा GPII_n_CH_k_SCRATCH_3_OFFS(n, k)	(0x2006C + (0x4000 * (n)) + (0x80 * (k)))

काष्ठा __packed gpi_tre अणु
	u32 dword[4];
पूर्ण;

क्रमागत msm_gpi_tce_code अणु
	MSM_GPI_TCE_SUCCESS = 1,
	MSM_GPI_TCE_EOT = 2,
	MSM_GPI_TCE_EOB = 4,
	MSM_GPI_TCE_UNEXP_ERR = 16,
पूर्ण;

#घोषणा CMD_TIMEOUT_MS		(250)

#घोषणा MAX_CHANNELS_PER_GPII	(2)
#घोषणा GPI_TX_CHAN		(0)
#घोषणा GPI_RX_CHAN		(1)
#घोषणा STATE_IGNORE		(U32_MAX)
#घोषणा EV_FACTOR		(2)
#घोषणा REQ_OF_DMA_ARGS		(5) /* # of arguments required from client */
#घोषणा CHAN_TRES		64

काष्ठा __packed xfer_compl_event अणु
	u64 ptr;
	u32 length:24;
	u8 code;
	u16 status;
	u8 type;
	u8 chid;
पूर्ण;

काष्ठा __packed immediate_data_event अणु
	u8 data_bytes[8];
	u8 length:4;
	u8 resvd:4;
	u16 tre_index;
	u8 code;
	u16 status;
	u8 type;
	u8 chid;
पूर्ण;

काष्ठा __packed qup_notअगर_event अणु
	u32 status;
	u32 समय;
	u32 count:24;
	u8 resvd;
	u16 resvd1;
	u8 type;
	u8 chid;
पूर्ण;

काष्ठा __packed gpi_ere अणु
	u32 dword[4];
पूर्ण;

क्रमागत GPI_EV_TYPE अणु
	XFER_COMPLETE_EV_TYPE = 0x22,
	IMMEDIATE_DATA_EV_TYPE = 0x30,
	QUP_NOTIF_EV_TYPE = 0x31,
	STALE_EV_TYPE = 0xFF,
पूर्ण;

जोड़ __packed gpi_event अणु
	काष्ठा __packed xfer_compl_event xfer_compl_event;
	काष्ठा __packed immediate_data_event immediate_data_event;
	काष्ठा __packed qup_notअगर_event qup_notअगर_event;
	काष्ठा __packed gpi_ere gpi_ere;
पूर्ण;

क्रमागत gpii_irq_settings अणु
	DEFAULT_IRQ_SETTINGS,
	MASK_IEOB_SETTINGS,
पूर्ण;

क्रमागत gpi_ev_state अणु
	DEFAULT_EV_CH_STATE = 0,
	EV_STATE_NOT_ALLOCATED = DEFAULT_EV_CH_STATE,
	EV_STATE_ALLOCATED,
	MAX_EV_STATES
पूर्ण;

अटल स्थिर अक्षर *स्थिर gpi_ev_state_str[MAX_EV_STATES] = अणु
	[EV_STATE_NOT_ALLOCATED] = "NOT ALLOCATED",
	[EV_STATE_ALLOCATED] = "ALLOCATED",
पूर्ण;

#घोषणा TO_GPI_EV_STATE_STR(_state) (((_state) >= MAX_EV_STATES) ? \
				    "INVALID" : gpi_ev_state_str[(_state)])

क्रमागत gpi_ch_state अणु
	DEFAULT_CH_STATE = 0x0,
	CH_STATE_NOT_ALLOCATED = DEFAULT_CH_STATE,
	CH_STATE_ALLOCATED = 0x1,
	CH_STATE_STARTED = 0x2,
	CH_STATE_STOPPED = 0x3,
	CH_STATE_STOP_IN_PROC = 0x4,
	CH_STATE_ERROR = 0xf,
	MAX_CH_STATES
पूर्ण;

क्रमागत gpi_cmd अणु
	GPI_CH_CMD_BEGIN,
	GPI_CH_CMD_ALLOCATE = GPI_CH_CMD_BEGIN,
	GPI_CH_CMD_START,
	GPI_CH_CMD_STOP,
	GPI_CH_CMD_RESET,
	GPI_CH_CMD_DE_ALLOC,
	GPI_CH_CMD_UART_SW_STALE,
	GPI_CH_CMD_UART_RFR_READY,
	GPI_CH_CMD_UART_RFR_NOT_READY,
	GPI_CH_CMD_END = GPI_CH_CMD_UART_RFR_NOT_READY,
	GPI_EV_CMD_BEGIN,
	GPI_EV_CMD_ALLOCATE = GPI_EV_CMD_BEGIN,
	GPI_EV_CMD_RESET,
	GPI_EV_CMD_DEALLOC,
	GPI_EV_CMD_END = GPI_EV_CMD_DEALLOC,
	GPI_MAX_CMD,
पूर्ण;

#घोषणा IS_CHAN_CMD(_cmd) ((_cmd) <= GPI_CH_CMD_END)

अटल स्थिर अक्षर *स्थिर gpi_cmd_str[GPI_MAX_CMD] = अणु
	[GPI_CH_CMD_ALLOCATE] = "CH ALLOCATE",
	[GPI_CH_CMD_START] = "CH START",
	[GPI_CH_CMD_STOP] = "CH STOP",
	[GPI_CH_CMD_RESET] = "CH_RESET",
	[GPI_CH_CMD_DE_ALLOC] = "DE ALLOC",
	[GPI_CH_CMD_UART_SW_STALE] = "UART SW STALE",
	[GPI_CH_CMD_UART_RFR_READY] = "UART RFR READY",
	[GPI_CH_CMD_UART_RFR_NOT_READY] = "UART RFR NOT READY",
	[GPI_EV_CMD_ALLOCATE] = "EV ALLOCATE",
	[GPI_EV_CMD_RESET] = "EV RESET",
	[GPI_EV_CMD_DEALLOC] = "EV DEALLOC",
पूर्ण;

#घोषणा TO_GPI_CMD_STR(_cmd) (((_cmd) >= GPI_MAX_CMD) ? "INVALID" : \
				  gpi_cmd_str[(_cmd)])

/*
 * @DISABLE_STATE: no रेजिस्टर access allowed
 * @CONFIG_STATE:  client has configured the channel
 * @PREP_HARDWARE: रेजिस्टर access is allowed
 *		   however, no processing EVENTS
 * @ACTIVE_STATE: channels are fully operational
 * @PREPARE_TERMINATE: graceful termination of channels
 *		       रेजिस्टर access is allowed
 * @PAUSE_STATE: channels are active, but not processing any events
 */
क्रमागत gpi_pm_state अणु
	DISABLE_STATE,
	CONFIG_STATE,
	PREPARE_HARDWARE,
	ACTIVE_STATE,
	PREPARE_TERMINATE,
	PAUSE_STATE,
	MAX_PM_STATE
पूर्ण;

#घोषणा REG_ACCESS_VALID(_pm_state) ((_pm_state) >= PREPARE_HARDWARE)

अटल स्थिर अक्षर *स्थिर gpi_pm_state_str[MAX_PM_STATE] = अणु
	[DISABLE_STATE] = "DISABLE",
	[CONFIG_STATE] = "CONFIG",
	[PREPARE_HARDWARE] = "PREPARE HARDWARE",
	[ACTIVE_STATE] = "ACTIVE",
	[PREPARE_TERMINATE] = "PREPARE TERMINATE",
	[PAUSE_STATE] = "PAUSE",
पूर्ण;

#घोषणा TO_GPI_PM_STR(_state) (((_state) >= MAX_PM_STATE) ? \
			      "INVALID" : gpi_pm_state_str[(_state)])

अटल स्थिर काष्ठा अणु
	क्रमागत gpi_cmd gpi_cmd;
	u32 opcode;
	u32 state;
पूर्ण gpi_cmd_info[GPI_MAX_CMD] = अणु
	अणु
		GPI_CH_CMD_ALLOCATE,
		GPII_n_CH_CMD_ALLOCATE,
		CH_STATE_ALLOCATED,
	पूर्ण,
	अणु
		GPI_CH_CMD_START,
		GPII_n_CH_CMD_START,
		CH_STATE_STARTED,
	पूर्ण,
	अणु
		GPI_CH_CMD_STOP,
		GPII_n_CH_CMD_STOP,
		CH_STATE_STOPPED,
	पूर्ण,
	अणु
		GPI_CH_CMD_RESET,
		GPII_n_CH_CMD_RESET,
		CH_STATE_ALLOCATED,
	पूर्ण,
	अणु
		GPI_CH_CMD_DE_ALLOC,
		GPII_n_CH_CMD_DE_ALLOC,
		CH_STATE_NOT_ALLOCATED,
	पूर्ण,
	अणु
		GPI_CH_CMD_UART_SW_STALE,
		GPII_n_CH_CMD_UART_SW_STALE,
		STATE_IGNORE,
	पूर्ण,
	अणु
		GPI_CH_CMD_UART_RFR_READY,
		GPII_n_CH_CMD_UART_RFR_READY,
		STATE_IGNORE,
	पूर्ण,
	अणु
		GPI_CH_CMD_UART_RFR_NOT_READY,
		GPII_n_CH_CMD_UART_RFR_NOT_READY,
		STATE_IGNORE,
	पूर्ण,
	अणु
		GPI_EV_CMD_ALLOCATE,
		GPII_n_EV_CH_CMD_ALLOCATE,
		EV_STATE_ALLOCATED,
	पूर्ण,
	अणु
		GPI_EV_CMD_RESET,
		GPII_n_EV_CH_CMD_RESET,
		EV_STATE_ALLOCATED,
	पूर्ण,
	अणु
		GPI_EV_CMD_DEALLOC,
		GPII_n_EV_CH_CMD_DE_ALLOC,
		EV_STATE_NOT_ALLOCATED,
	पूर्ण,
पूर्ण;

काष्ठा gpi_ring अणु
	व्योम *pre_aligned;
	माप_प्रकार alloc_size;
	phys_addr_t phys_addr;
	dma_addr_t dma_handle;
	व्योम *base;
	व्योम *wp;
	व्योम *rp;
	u32 len;
	u32 el_size;
	u32 elements;
	bool configured;
पूर्ण;

काष्ठा gpi_dev अणु
	काष्ठा dma_device dma_device;
	काष्ठा device *dev;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	व्योम __iomem *ee_base; /*ee रेजिस्टर base address*/
	u32 max_gpii; /* maximum # of gpii instances available per gpi block */
	u32 gpii_mask; /* gpii instances available क्रम apps */
	u32 ev_factor; /* ev ring length factor */
	काष्ठा gpii *gpiis;
पूर्ण;

काष्ठा reg_info अणु
	अक्षर *name;
	u32 offset;
	u32 val;
पूर्ण;

काष्ठा gchan अणु
	काष्ठा virt_dma_chan vc;
	u32 chid;
	u32 seid;
	u32 protocol;
	काष्ठा gpii *gpii;
	क्रमागत gpi_ch_state ch_state;
	क्रमागत gpi_pm_state pm_state;
	व्योम __iomem *ch_cntxt_base_reg;
	व्योम __iomem *ch_cntxt_db_reg;
	व्योम __iomem *ch_cmd_reg;
	u32 dir;
	काष्ठा gpi_ring ch_ring;
	व्योम *config;
पूर्ण;

काष्ठा gpii अणु
	u32 gpii_id;
	काष्ठा gchan gchan[MAX_CHANNELS_PER_GPII];
	काष्ठा gpi_dev *gpi_dev;
	पूर्णांक irq;
	व्योम __iomem *regs; /* poपूर्णांकs to gpi top */
	व्योम __iomem *ev_cntxt_base_reg;
	व्योम __iomem *ev_cntxt_db_reg;
	व्योम __iomem *ev_ring_rp_lsb_reg;
	व्योम __iomem *ev_cmd_reg;
	व्योम __iomem *ieob_clr_reg;
	काष्ठा mutex ctrl_lock;
	क्रमागत gpi_ev_state ev_state;
	bool configured_irq;
	क्रमागत gpi_pm_state pm_state;
	rwlock_t pm_lock;
	काष्ठा gpi_ring ev_ring;
	काष्ठा tasklet_काष्ठा ev_task; /* event processing tasklet */
	काष्ठा completion cmd_completion;
	क्रमागत gpi_cmd gpi_cmd;
	u32 cntxt_type_irq_msk;
	bool ieob_set;
पूर्ण;

#घोषणा MAX_TRE 3

काष्ठा gpi_desc अणु
	काष्ठा virt_dma_desc vd;
	माप_प्रकार len;
	व्योम *db; /* DB रेजिस्टर to program */
	काष्ठा gchan *gchan;
	काष्ठा gpi_tre tre[MAX_TRE];
	u32 num_tre;
पूर्ण;

अटल स्थिर u32 GPII_CHAN_सूची[MAX_CHANNELS_PER_GPII] = अणु
	GPI_CHTYPE_सूची_OUT, GPI_CHTYPE_सूची_IN
पूर्ण;

अटल irqवापस_t gpi_handle_irq(पूर्णांक irq, व्योम *data);
अटल व्योम gpi_ring_recycle_ev_element(काष्ठा gpi_ring *ring);
अटल पूर्णांक gpi_ring_add_element(काष्ठा gpi_ring *ring, व्योम **wp);
अटल व्योम gpi_process_events(काष्ठा gpii *gpii);

अटल अंतरभूत काष्ठा gchan *to_gchan(काष्ठा dma_chan *dma_chan)
अणु
	वापस container_of(dma_chan, काष्ठा gchan, vc.chan);
पूर्ण

अटल अंतरभूत काष्ठा gpi_desc *to_gpi_desc(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा gpi_desc, vd);
पूर्ण

अटल अंतरभूत phys_addr_t to_physical(स्थिर काष्ठा gpi_ring *स्थिर ring,
				      व्योम *addr)
अणु
	वापस ring->phys_addr + (addr - ring->base);
पूर्ण

अटल अंतरभूत व्योम *to_भव(स्थिर काष्ठा gpi_ring *स्थिर ring, phys_addr_t addr)
अणु
	वापस ring->base + (addr - ring->phys_addr);
पूर्ण

अटल अंतरभूत u32 gpi_पढ़ो_reg(काष्ठा gpii *gpii, व्योम __iomem *addr)
अणु
	वापस पढ़ोl_relaxed(addr);
पूर्ण

अटल अंतरभूत व्योम gpi_ग_लिखो_reg(काष्ठा gpii *gpii, व्योम __iomem *addr, u32 val)
अणु
	ग_लिखोl_relaxed(val, addr);
पूर्ण

/* gpi_ग_लिखो_reg_field - ग_लिखो to specअगरic bit field */
अटल अंतरभूत व्योम gpi_ग_लिखो_reg_field(काष्ठा gpii *gpii, व्योम __iomem *addr,
				       u32 mask, u32 shअगरt, u32 val)
अणु
	u32 पंचांगp = gpi_पढ़ो_reg(gpii, addr);

	पंचांगp &= ~mask;
	val = पंचांगp | ((val << shअगरt) & mask);
	gpi_ग_लिखो_reg(gpii, addr, val);
पूर्ण

अटल __always_अंतरभूत व्योम
gpi_update_reg(काष्ठा gpii *gpii, u32 offset, u32 mask, u32 val)
अणु
	व्योम __iomem *addr = gpii->regs + offset;
	u32 पंचांगp = gpi_पढ़ो_reg(gpii, addr);

	पंचांगp &= ~mask;
	पंचांगp |= u32_encode_bits(val, mask);

	gpi_ग_लिखो_reg(gpii, addr, पंचांगp);
पूर्ण

अटल व्योम gpi_disable_पूर्णांकerrupts(काष्ठा gpii *gpii)
अणु
	gpi_update_reg(gpii, GPII_n_CNTXT_TYPE_IRQ_MSK_OFFS(gpii->gpii_id),
		       GPII_n_CNTXT_TYPE_IRQ_MSK_BMSK, 0);
	gpi_update_reg(gpii, GPII_n_CNTXT_SRC_IEOB_IRQ_MSK_OFFS(gpii->gpii_id),
		       GPII_n_CNTXT_SRC_IEOB_IRQ_MSK_BMSK, 0);
	gpi_update_reg(gpii, GPII_n_CNTXT_SRC_CH_IRQ_MSK_OFFS(gpii->gpii_id),
		       GPII_n_CNTXT_SRC_CH_IRQ_MSK_BMSK, 0);
	gpi_update_reg(gpii, GPII_n_CNTXT_SRC_EV_CH_IRQ_MSK_OFFS(gpii->gpii_id),
		       GPII_n_CNTXT_SRC_EV_CH_IRQ_MSK_BMSK, 0);
	gpi_update_reg(gpii, GPII_n_CNTXT_GLOB_IRQ_EN_OFFS(gpii->gpii_id),
		       GPII_n_CNTXT_GPII_IRQ_EN_BMSK, 0);
	gpi_update_reg(gpii, GPII_n_CNTXT_GPII_IRQ_EN_OFFS(gpii->gpii_id),
		       GPII_n_CNTXT_GPII_IRQ_EN_BMSK, 0);
	gpi_update_reg(gpii, GPII_n_CNTXT_INTSET_OFFS(gpii->gpii_id),
		       GPII_n_CNTXT_INTSET_BMSK, 0);

	gpii->cntxt_type_irq_msk = 0;
	devm_मुक्त_irq(gpii->gpi_dev->dev, gpii->irq, gpii);
	gpii->configured_irq = false;
पूर्ण

/* configure and enable पूर्णांकerrupts */
अटल पूर्णांक gpi_config_पूर्णांकerrupts(काष्ठा gpii *gpii, क्रमागत gpii_irq_settings settings, bool mask)
अणु
	स्थिर u32 enable = (GPII_n_CNTXT_TYPE_IRQ_MSK_GENERAL |
			      GPII_n_CNTXT_TYPE_IRQ_MSK_IEOB |
			      GPII_n_CNTXT_TYPE_IRQ_MSK_GLOB |
			      GPII_n_CNTXT_TYPE_IRQ_MSK_EV_CTRL |
			      GPII_n_CNTXT_TYPE_IRQ_MSK_CH_CTRL);
	पूर्णांक ret;

	अगर (!gpii->configured_irq) अणु
		ret = devm_request_irq(gpii->gpi_dev->dev, gpii->irq,
				       gpi_handle_irq, IRQF_TRIGGER_HIGH,
				       "gpi-dma", gpii);
		अगर (ret < 0) अणु
			dev_err(gpii->gpi_dev->dev, "error request irq:%d ret:%d\n",
				gpii->irq, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (settings == MASK_IEOB_SETTINGS) अणु
		/*
		 * GPII only uses one EV ring per gpii so we can globally
		 * enable/disable IEOB पूर्णांकerrupt
		 */
		अगर (mask)
			gpii->cntxt_type_irq_msk |= GPII_n_CNTXT_TYPE_IRQ_MSK_IEOB;
		अन्यथा
			gpii->cntxt_type_irq_msk &= ~(GPII_n_CNTXT_TYPE_IRQ_MSK_IEOB);
		gpi_update_reg(gpii, GPII_n_CNTXT_TYPE_IRQ_MSK_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_TYPE_IRQ_MSK_BMSK, gpii->cntxt_type_irq_msk);
	पूर्ण अन्यथा अणु
		gpi_update_reg(gpii, GPII_n_CNTXT_TYPE_IRQ_MSK_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_TYPE_IRQ_MSK_BMSK, enable);
		gpi_update_reg(gpii, GPII_n_CNTXT_SRC_IEOB_IRQ_MSK_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_SRC_IEOB_IRQ_MSK_BMSK,
			       GPII_n_CNTXT_SRC_IEOB_IRQ_MSK_BMSK);
		gpi_update_reg(gpii, GPII_n_CNTXT_SRC_CH_IRQ_MSK_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_SRC_CH_IRQ_MSK_BMSK,
			       GPII_n_CNTXT_SRC_CH_IRQ_MSK_BMSK);
		gpi_update_reg(gpii, GPII_n_CNTXT_SRC_EV_CH_IRQ_MSK_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_SRC_EV_CH_IRQ_MSK_BMSK,
			       GPII_n_CNTXT_SRC_EV_CH_IRQ_MSK_BMSK);
		gpi_update_reg(gpii, GPII_n_CNTXT_GLOB_IRQ_EN_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_GPII_IRQ_EN_BMSK,
			       GPII_n_CNTXT_GPII_IRQ_EN_BMSK);
		gpi_update_reg(gpii, GPII_n_CNTXT_GPII_IRQ_EN_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_GPII_IRQ_EN_BMSK, GPII_n_CNTXT_GPII_IRQ_EN_BMSK);
		gpi_update_reg(gpii, GPII_n_CNTXT_MSI_BASE_LSB_OFFS(gpii->gpii_id), U32_MAX, 0);
		gpi_update_reg(gpii, GPII_n_CNTXT_MSI_BASE_MSB_OFFS(gpii->gpii_id), U32_MAX, 0);
		gpi_update_reg(gpii, GPII_n_CNTXT_SCRATCH_0_OFFS(gpii->gpii_id), U32_MAX, 0);
		gpi_update_reg(gpii, GPII_n_CNTXT_SCRATCH_1_OFFS(gpii->gpii_id), U32_MAX, 0);
		gpi_update_reg(gpii, GPII_n_CNTXT_INTSET_OFFS(gpii->gpii_id),
			       GPII_n_CNTXT_INTSET_BMSK, 1);
		gpi_update_reg(gpii, GPII_n_ERROR_LOG_OFFS(gpii->gpii_id), U32_MAX, 0);

		gpii->cntxt_type_irq_msk = enable;
	पूर्ण

	gpii->configured_irq = true;
	वापस 0;
पूर्ण

/* Sends gpii event or channel command */
अटल पूर्णांक gpi_send_cmd(काष्ठा gpii *gpii, काष्ठा gchan *gchan,
			क्रमागत gpi_cmd gpi_cmd)
अणु
	u32 chid = MAX_CHANNELS_PER_GPII;
	अचिन्हित दीर्घ समयout;
	व्योम __iomem *cmd_reg;
	u32 cmd;

	अगर (gpi_cmd >= GPI_MAX_CMD)
		वापस -EINVAL;
	अगर (IS_CHAN_CMD(gpi_cmd))
		chid = gchan->chid;

	dev_dbg(gpii->gpi_dev->dev,
		"sending cmd: %s:%u\n", TO_GPI_CMD_STR(gpi_cmd), chid);

	/* send opcode and रुको क्रम completion */
	reinit_completion(&gpii->cmd_completion);
	gpii->gpi_cmd = gpi_cmd;

	cmd_reg = IS_CHAN_CMD(gpi_cmd) ? gchan->ch_cmd_reg : gpii->ev_cmd_reg;
	cmd = IS_CHAN_CMD(gpi_cmd) ? GPII_n_CH_CMD(gpi_cmd_info[gpi_cmd].opcode, chid) :
				     GPII_n_EV_CMD(gpi_cmd_info[gpi_cmd].opcode, 0);
	gpi_ग_लिखो_reg(gpii, cmd_reg, cmd);
	समयout = रुको_क्रम_completion_समयout(&gpii->cmd_completion,
					      msecs_to_jअगरfies(CMD_TIMEOUT_MS));
	अगर (!समयout) अणु
		dev_err(gpii->gpi_dev->dev, "cmd: %s completion timeout:%u\n",
			TO_GPI_CMD_STR(gpi_cmd), chid);
		वापस -EIO;
	पूर्ण

	/* confirm new ch state is correct , अगर the cmd is a state change cmd */
	अगर (gpi_cmd_info[gpi_cmd].state == STATE_IGNORE)
		वापस 0;

	अगर (IS_CHAN_CMD(gpi_cmd) && gchan->ch_state == gpi_cmd_info[gpi_cmd].state)
		वापस 0;

	अगर (!IS_CHAN_CMD(gpi_cmd) && gpii->ev_state == gpi_cmd_info[gpi_cmd].state)
		वापस 0;

	वापस -EIO;
पूर्ण

/* program transfer ring DB रेजिस्टर */
अटल अंतरभूत व्योम gpi_ग_लिखो_ch_db(काष्ठा gchan *gchan,
				   काष्ठा gpi_ring *ring, व्योम *wp)
अणु
	काष्ठा gpii *gpii = gchan->gpii;
	phys_addr_t p_wp;

	p_wp = to_physical(ring, wp);
	gpi_ग_लिखो_reg(gpii, gchan->ch_cntxt_db_reg, p_wp);
पूर्ण

/* program event ring DB रेजिस्टर */
अटल अंतरभूत व्योम gpi_ग_लिखो_ev_db(काष्ठा gpii *gpii,
				   काष्ठा gpi_ring *ring, व्योम *wp)
अणु
	phys_addr_t p_wp;

	p_wp = ring->phys_addr + (wp - ring->base);
	gpi_ग_लिखो_reg(gpii, gpii->ev_cntxt_db_reg, p_wp);
पूर्ण

/* process transfer completion पूर्णांकerrupt */
अटल व्योम gpi_process_ieob(काष्ठा gpii *gpii)
अणु
	gpi_ग_लिखो_reg(gpii, gpii->ieob_clr_reg, BIT(0));

	gpi_config_पूर्णांकerrupts(gpii, MASK_IEOB_SETTINGS, 0);
	tasklet_hi_schedule(&gpii->ev_task);
पूर्ण

/* process channel control पूर्णांकerrupt */
अटल व्योम gpi_process_ch_ctrl_irq(काष्ठा gpii *gpii)
अणु
	u32 gpii_id = gpii->gpii_id;
	u32 offset = GPII_n_CNTXT_SRC_GPII_CH_IRQ_OFFS(gpii_id);
	u32 ch_irq = gpi_पढ़ो_reg(gpii, gpii->regs + offset);
	काष्ठा gchan *gchan;
	u32 chid, state;

	/* clear the status */
	offset = GPII_n_CNTXT_SRC_CH_IRQ_CLR_OFFS(gpii_id);
	gpi_ग_लिखो_reg(gpii, gpii->regs + offset, (u32)ch_irq);

	क्रम (chid = 0; chid < MAX_CHANNELS_PER_GPII; chid++) अणु
		अगर (!(BIT(chid) & ch_irq))
			जारी;

		gchan = &gpii->gchan[chid];
		state = gpi_पढ़ो_reg(gpii, gchan->ch_cntxt_base_reg +
				     CNTXT_0_CONFIG);
		state = FIELD_GET(GPII_n_CH_k_CNTXT_0_CHSTATE, state);

		/*
		 * CH_CMD_DEALLOC cmd always successful. However cmd करोes
		 * not change hardware status. So overwriting software state
		 * to शेष state.
		 */
		अगर (gpii->gpi_cmd == GPI_CH_CMD_DE_ALLOC)
			state = DEFAULT_CH_STATE;
		gchan->ch_state = state;

		/*
		 * Triggering complete all अगर ch_state is not a stop in process.
		 * Stop in process is a transition state and we will रुको क्रम
		 * stop पूर्णांकerrupt beक्रमe notअगरying.
		 */
		अगर (gchan->ch_state != CH_STATE_STOP_IN_PROC)
			complete_all(&gpii->cmd_completion);
	पूर्ण
पूर्ण

/* processing gpi general error पूर्णांकerrupts */
अटल व्योम gpi_process_gen_err_irq(काष्ठा gpii *gpii)
अणु
	u32 gpii_id = gpii->gpii_id;
	u32 offset = GPII_n_CNTXT_GPII_IRQ_STTS_OFFS(gpii_id);
	u32 irq_stts = gpi_पढ़ो_reg(gpii, gpii->regs + offset);

	/* clear the status */
	dev_dbg(gpii->gpi_dev->dev, "irq_stts:0x%x\n", irq_stts);

	/* Clear the रेजिस्टर */
	offset = GPII_n_CNTXT_GPII_IRQ_CLR_OFFS(gpii_id);
	gpi_ग_लिखो_reg(gpii, gpii->regs + offset, irq_stts);
पूर्ण

/* processing gpi level error पूर्णांकerrupts */
अटल व्योम gpi_process_glob_err_irq(काष्ठा gpii *gpii)
अणु
	u32 gpii_id = gpii->gpii_id;
	u32 offset = GPII_n_CNTXT_GLOB_IRQ_STTS_OFFS(gpii_id);
	u32 irq_stts = gpi_पढ़ो_reg(gpii, gpii->regs + offset);

	offset = GPII_n_CNTXT_GLOB_IRQ_CLR_OFFS(gpii_id);
	gpi_ग_लिखो_reg(gpii, gpii->regs + offset, irq_stts);

	/* only error पूर्णांकerrupt should be set */
	अगर (irq_stts & ~GPI_GLOB_IRQ_ERROR_INT_MSK) अणु
		dev_err(gpii->gpi_dev->dev, "invalid error status:0x%x\n", irq_stts);
		वापस;
	पूर्ण

	offset = GPII_n_ERROR_LOG_OFFS(gpii_id);
	gpi_ग_लिखो_reg(gpii, gpii->regs + offset, 0);
पूर्ण

/* gpii पूर्णांकerrupt handler */
अटल irqवापस_t gpi_handle_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा gpii *gpii = data;
	u32 gpii_id = gpii->gpii_id;
	u32 type, offset;
	अचिन्हित दीर्घ flags;

	पढ़ो_lock_irqsave(&gpii->pm_lock, flags);

	/*
	 * States are out of sync to receive पूर्णांकerrupt
	 * जबतक software state is in DISABLE state, bailing out.
	 */
	अगर (!REG_ACCESS_VALID(gpii->pm_state)) अणु
		dev_err(gpii->gpi_dev->dev, "receive interrupt while in %s state\n",
			TO_GPI_PM_STR(gpii->pm_state));
		जाओ निकास_irq;
	पूर्ण

	offset = GPII_n_CNTXT_TYPE_IRQ_OFFS(gpii->gpii_id);
	type = gpi_पढ़ो_reg(gpii, gpii->regs + offset);

	करो अणु
		/* global gpii error */
		अगर (type & GPII_n_CNTXT_TYPE_IRQ_MSK_GLOB) अणु
			gpi_process_glob_err_irq(gpii);
			type &= ~(GPII_n_CNTXT_TYPE_IRQ_MSK_GLOB);
		पूर्ण

		/* transfer complete पूर्णांकerrupt */
		अगर (type & GPII_n_CNTXT_TYPE_IRQ_MSK_IEOB) अणु
			gpi_process_ieob(gpii);
			type &= ~GPII_n_CNTXT_TYPE_IRQ_MSK_IEOB;
		पूर्ण

		/* event control irq */
		अगर (type & GPII_n_CNTXT_TYPE_IRQ_MSK_EV_CTRL) अणु
			u32 ev_state;
			u32 ev_ch_irq;

			dev_dbg(gpii->gpi_dev->dev,
				"processing EV CTRL interrupt\n");
			offset = GPII_n_CNTXT_SRC_EV_CH_IRQ_OFFS(gpii_id);
			ev_ch_irq = gpi_पढ़ो_reg(gpii, gpii->regs + offset);

			offset = GPII_n_CNTXT_SRC_EV_CH_IRQ_CLR_OFFS
				(gpii_id);
			gpi_ग_लिखो_reg(gpii, gpii->regs + offset, ev_ch_irq);
			ev_state = gpi_पढ़ो_reg(gpii, gpii->ev_cntxt_base_reg +
						CNTXT_0_CONFIG);
			ev_state = FIELD_GET(GPII_n_EV_k_CNTXT_0_CHSTATE, ev_state);

			/*
			 * CMD EV_CMD_DEALLOC is always successful. However
			 * cmd करोes not change hardware status. So overwriting
			 * software state to शेष state.
			 */
			अगर (gpii->gpi_cmd == GPI_EV_CMD_DEALLOC)
				ev_state = DEFAULT_EV_CH_STATE;

			gpii->ev_state = ev_state;
			dev_dbg(gpii->gpi_dev->dev, "setting EV state to %s\n",
				TO_GPI_EV_STATE_STR(gpii->ev_state));
			complete_all(&gpii->cmd_completion);
			type &= ~(GPII_n_CNTXT_TYPE_IRQ_MSK_EV_CTRL);
		पूर्ण

		/* channel control irq */
		अगर (type & GPII_n_CNTXT_TYPE_IRQ_MSK_CH_CTRL) अणु
			dev_dbg(gpii->gpi_dev->dev, "process CH CTRL interrupts\n");
			gpi_process_ch_ctrl_irq(gpii);
			type &= ~(GPII_n_CNTXT_TYPE_IRQ_MSK_CH_CTRL);
		पूर्ण

		अगर (type) अणु
			dev_err(gpii->gpi_dev->dev, "Unhandled interrupt status:0x%x\n", type);
			gpi_process_gen_err_irq(gpii);
			जाओ निकास_irq;
		पूर्ण

		offset = GPII_n_CNTXT_TYPE_IRQ_OFFS(gpii->gpii_id);
		type = gpi_पढ़ो_reg(gpii, gpii->regs + offset);
	पूर्ण जबतक (type);

निकास_irq:
	पढ़ो_unlock_irqrestore(&gpii->pm_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

/* process DMA Immediate completion data events */
अटल व्योम gpi_process_imed_data_event(काष्ठा gchan *gchan,
					काष्ठा immediate_data_event *imed_event)
अणु
	काष्ठा gpii *gpii = gchan->gpii;
	काष्ठा gpi_ring *ch_ring = &gchan->ch_ring;
	व्योम *tre = ch_ring->base + (ch_ring->el_size * imed_event->tre_index);
	काष्ठा dmaengine_result result;
	काष्ठा gpi_desc *gpi_desc;
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;
	u32 chid;

	/*
	 * If channel not active करोn't process event
	 */
	अगर (gchan->pm_state != ACTIVE_STATE) अणु
		dev_err(gpii->gpi_dev->dev, "skipping processing event because ch @ %s state\n",
			TO_GPI_PM_STR(gchan->pm_state));
		वापस;
	पूर्ण

	spin_lock_irqsave(&gchan->vc.lock, flags);
	vd = vchan_next_desc(&gchan->vc);
	अगर (!vd) अणु
		काष्ठा gpi_ere *gpi_ere;
		काष्ठा gpi_tre *gpi_tre;

		spin_unlock_irqrestore(&gchan->vc.lock, flags);
		dev_dbg(gpii->gpi_dev->dev, "event without a pending descriptor!\n");
		gpi_ere = (काष्ठा gpi_ere *)imed_event;
		dev_dbg(gpii->gpi_dev->dev,
			"Event: %08x %08x %08x %08x\n",
			gpi_ere->dword[0], gpi_ere->dword[1],
			gpi_ere->dword[2], gpi_ere->dword[3]);
		gpi_tre = tre;
		dev_dbg(gpii->gpi_dev->dev,
			"Pending TRE: %08x %08x %08x %08x\n",
			gpi_tre->dword[0], gpi_tre->dword[1],
			gpi_tre->dword[2], gpi_tre->dword[3]);
		वापस;
	पूर्ण
	gpi_desc = to_gpi_desc(vd);
	spin_unlock_irqrestore(&gchan->vc.lock, flags);

	/*
	 * RP poपूर्णांकed by Event is to last TRE processed,
	 * we need to update ring rp to tre + 1
	 */
	tre += ch_ring->el_size;
	अगर (tre >= (ch_ring->base + ch_ring->len))
		tre = ch_ring->base;
	ch_ring->rp = tre;

	/* make sure rp updates are immediately visible to all cores */
	smp_wmb();

	chid = imed_event->chid;
	अगर (imed_event->code == MSM_GPI_TCE_EOT && gpii->ieob_set) अणु
		अगर (chid == GPI_RX_CHAN)
			जाओ gpi_मुक्त_desc;
		अन्यथा
			वापस;
	पूर्ण

	अगर (imed_event->code == MSM_GPI_TCE_UNEXP_ERR)
		result.result = DMA_TRANS_ABORTED;
	अन्यथा
		result.result = DMA_TRANS_NOERROR;
	result.residue = gpi_desc->len - imed_event->length;

	dma_cookie_complete(&vd->tx);
	dmaengine_desc_get_callback_invoke(&vd->tx, &result);

gpi_मुक्त_desc:
	spin_lock_irqsave(&gchan->vc.lock, flags);
	list_del(&vd->node);
	spin_unlock_irqrestore(&gchan->vc.lock, flags);
	kमुक्त(gpi_desc);
	gpi_desc = शून्य;
पूर्ण

/* processing transfer completion events */
अटल व्योम gpi_process_xfer_compl_event(काष्ठा gchan *gchan,
					 काष्ठा xfer_compl_event *compl_event)
अणु
	काष्ठा gpii *gpii = gchan->gpii;
	काष्ठा gpi_ring *ch_ring = &gchan->ch_ring;
	व्योम *ev_rp = to_भव(ch_ring, compl_event->ptr);
	काष्ठा virt_dma_desc *vd;
	काष्ठा gpi_desc *gpi_desc;
	काष्ठा dmaengine_result result;
	अचिन्हित दीर्घ flags;
	u32 chid;

	/* only process events on active channel */
	अगर (unlikely(gchan->pm_state != ACTIVE_STATE)) अणु
		dev_err(gpii->gpi_dev->dev, "skipping processing event because ch @ %s state\n",
			TO_GPI_PM_STR(gchan->pm_state));
		वापस;
	पूर्ण

	spin_lock_irqsave(&gchan->vc.lock, flags);
	vd = vchan_next_desc(&gchan->vc);
	अगर (!vd) अणु
		काष्ठा gpi_ere *gpi_ere;

		spin_unlock_irqrestore(&gchan->vc.lock, flags);
		dev_err(gpii->gpi_dev->dev, "Event without a pending descriptor!\n");
		gpi_ere = (काष्ठा gpi_ere *)compl_event;
		dev_err(gpii->gpi_dev->dev,
			"Event: %08x %08x %08x %08x\n",
			gpi_ere->dword[0], gpi_ere->dword[1],
			gpi_ere->dword[2], gpi_ere->dword[3]);
		वापस;
	पूर्ण

	gpi_desc = to_gpi_desc(vd);
	spin_unlock_irqrestore(&gchan->vc.lock, flags);

	/*
	 * RP poपूर्णांकed by Event is to last TRE processed,
	 * we need to update ring rp to ev_rp + 1
	 */
	ev_rp += ch_ring->el_size;
	अगर (ev_rp >= (ch_ring->base + ch_ring->len))
		ev_rp = ch_ring->base;
	ch_ring->rp = ev_rp;

	/* update must be visible to other cores */
	smp_wmb();

	chid = compl_event->chid;
	अगर (compl_event->code == MSM_GPI_TCE_EOT && gpii->ieob_set) अणु
		अगर (chid == GPI_RX_CHAN)
			जाओ gpi_मुक्त_desc;
		अन्यथा
			वापस;
	पूर्ण

	अगर (compl_event->code == MSM_GPI_TCE_UNEXP_ERR) अणु
		dev_err(gpii->gpi_dev->dev, "Error in Transaction\n");
		result.result = DMA_TRANS_ABORTED;
	पूर्ण अन्यथा अणु
		dev_dbg(gpii->gpi_dev->dev, "Transaction Success\n");
		result.result = DMA_TRANS_NOERROR;
	पूर्ण
	result.residue = gpi_desc->len - compl_event->length;
	dev_dbg(gpii->gpi_dev->dev, "Residue %d\n", result.residue);

	dma_cookie_complete(&vd->tx);
	dmaengine_desc_get_callback_invoke(&vd->tx, &result);

gpi_मुक्त_desc:
	spin_lock_irqsave(&gchan->vc.lock, flags);
	list_del(&vd->node);
	spin_unlock_irqrestore(&gchan->vc.lock, flags);
	kमुक्त(gpi_desc);
	gpi_desc = शून्य;
पूर्ण

/* process all events */
अटल व्योम gpi_process_events(काष्ठा gpii *gpii)
अणु
	काष्ठा gpi_ring *ev_ring = &gpii->ev_ring;
	phys_addr_t cntxt_rp;
	व्योम *rp;
	जोड़ gpi_event *gpi_event;
	काष्ठा gchan *gchan;
	u32 chid, type;

	cntxt_rp = gpi_पढ़ो_reg(gpii, gpii->ev_ring_rp_lsb_reg);
	rp = to_भव(ev_ring, cntxt_rp);

	करो अणु
		जबतक (rp != ev_ring->rp) अणु
			gpi_event = ev_ring->rp;
			chid = gpi_event->xfer_compl_event.chid;
			type = gpi_event->xfer_compl_event.type;

			dev_dbg(gpii->gpi_dev->dev,
				"Event: CHID:%u, type:%x %08x %08x %08x %08x\n",
				chid, type, gpi_event->gpi_ere.dword[0],
				gpi_event->gpi_ere.dword[1], gpi_event->gpi_ere.dword[2],
				gpi_event->gpi_ere.dword[3]);

			चयन (type) अणु
			हाल XFER_COMPLETE_EV_TYPE:
				gchan = &gpii->gchan[chid];
				gpi_process_xfer_compl_event(gchan,
							     &gpi_event->xfer_compl_event);
				अवरोध;
			हाल STALE_EV_TYPE:
				dev_dbg(gpii->gpi_dev->dev, "stale event, not processing\n");
				अवरोध;
			हाल IMMEDIATE_DATA_EV_TYPE:
				gchan = &gpii->gchan[chid];
				gpi_process_imed_data_event(gchan,
							    &gpi_event->immediate_data_event);
				अवरोध;
			हाल QUP_NOTIF_EV_TYPE:
				dev_dbg(gpii->gpi_dev->dev, "QUP_NOTIF_EV_TYPE\n");
				अवरोध;
			शेष:
				dev_dbg(gpii->gpi_dev->dev,
					"not supported event type:0x%x\n", type);
			पूर्ण
			gpi_ring_recycle_ev_element(ev_ring);
		पूर्ण
		gpi_ग_लिखो_ev_db(gpii, ev_ring, ev_ring->wp);

		/* clear pending IEOB events */
		gpi_ग_लिखो_reg(gpii, gpii->ieob_clr_reg, BIT(0));

		cntxt_rp = gpi_पढ़ो_reg(gpii, gpii->ev_ring_rp_lsb_reg);
		rp = to_भव(ev_ring, cntxt_rp);

	पूर्ण जबतक (rp != ev_ring->rp);
पूर्ण

/* processing events using tasklet */
अटल व्योम gpi_ev_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा gpii *gpii = (काष्ठा gpii *)data;

	पढ़ो_lock_bh(&gpii->pm_lock);
	अगर (!REG_ACCESS_VALID(gpii->pm_state)) अणु
		पढ़ो_unlock_bh(&gpii->pm_lock);
		dev_err(gpii->gpi_dev->dev, "not processing any events, pm_state:%s\n",
			TO_GPI_PM_STR(gpii->pm_state));
		वापस;
	पूर्ण

	/* process the events */
	gpi_process_events(gpii);

	/* enable IEOB, चयनing back to पूर्णांकerrupts */
	gpi_config_पूर्णांकerrupts(gpii, MASK_IEOB_SETTINGS, 1);
	पढ़ो_unlock_bh(&gpii->pm_lock);
पूर्ण

/* marks all pending events क्रम the channel as stale */
अटल व्योम gpi_mark_stale_events(काष्ठा gchan *gchan)
अणु
	काष्ठा gpii *gpii = gchan->gpii;
	काष्ठा gpi_ring *ev_ring = &gpii->ev_ring;
	u32 cntxt_rp, local_rp;
	व्योम *ev_rp;

	cntxt_rp = gpi_पढ़ो_reg(gpii, gpii->ev_ring_rp_lsb_reg);

	ev_rp = ev_ring->rp;
	local_rp = (u32)to_physical(ev_ring, ev_rp);
	जबतक (local_rp != cntxt_rp) अणु
		जोड़ gpi_event *gpi_event = ev_rp;
		u32 chid = gpi_event->xfer_compl_event.chid;

		अगर (chid == gchan->chid)
			gpi_event->xfer_compl_event.type = STALE_EV_TYPE;
		ev_rp += ev_ring->el_size;
		अगर (ev_rp >= (ev_ring->base + ev_ring->len))
			ev_rp = ev_ring->base;
		cntxt_rp = gpi_पढ़ो_reg(gpii, gpii->ev_ring_rp_lsb_reg);
		local_rp = (u32)to_physical(ev_ring, ev_rp);
	पूर्ण
पूर्ण

/* reset sw state and issue channel reset or de-alloc */
अटल पूर्णांक gpi_reset_chan(काष्ठा gchan *gchan, क्रमागत gpi_cmd gpi_cmd)
अणु
	काष्ठा gpii *gpii = gchan->gpii;
	काष्ठा gpi_ring *ch_ring = &gchan->ch_ring;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(list);
	पूर्णांक ret;

	ret = gpi_send_cmd(gpii, gchan, gpi_cmd);
	अगर (ret) अणु
		dev_err(gpii->gpi_dev->dev, "Error with cmd:%s ret:%d\n",
			TO_GPI_CMD_STR(gpi_cmd), ret);
		वापस ret;
	पूर्ण

	/* initialize the local ring ptrs */
	ch_ring->rp = ch_ring->base;
	ch_ring->wp = ch_ring->base;

	/* visible to other cores */
	smp_wmb();

	/* check event ring क्रम any stale events */
	ग_लिखो_lock_irq(&gpii->pm_lock);
	gpi_mark_stale_events(gchan);

	/* हटाओ all async descriptors */
	spin_lock_irqsave(&gchan->vc.lock, flags);
	vchan_get_all_descriptors(&gchan->vc, &list);
	spin_unlock_irqrestore(&gchan->vc.lock, flags);
	ग_लिखो_unlock_irq(&gpii->pm_lock);
	vchan_dma_desc_मुक्त_list(&gchan->vc, &list);

	वापस 0;
पूर्ण

अटल पूर्णांक gpi_start_chan(काष्ठा gchan *gchan)
अणु
	काष्ठा gpii *gpii = gchan->gpii;
	पूर्णांक ret;

	ret = gpi_send_cmd(gpii, gchan, GPI_CH_CMD_START);
	अगर (ret) अणु
		dev_err(gpii->gpi_dev->dev, "Error with cmd:%s ret:%d\n",
			TO_GPI_CMD_STR(GPI_CH_CMD_START), ret);
		वापस ret;
	पूर्ण

	/* gpii CH is active now */
	ग_लिखो_lock_irq(&gpii->pm_lock);
	gchan->pm_state = ACTIVE_STATE;
	ग_लिखो_unlock_irq(&gpii->pm_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक gpi_stop_chan(काष्ठा gchan *gchan)
अणु
	काष्ठा gpii *gpii = gchan->gpii;
	पूर्णांक ret;

	ret = gpi_send_cmd(gpii, gchan, GPI_CH_CMD_STOP);
	अगर (ret) अणु
		dev_err(gpii->gpi_dev->dev, "Error with cmd:%s ret:%d\n",
			TO_GPI_CMD_STR(GPI_CH_CMD_STOP), ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* allocate and configure the transfer channel */
अटल पूर्णांक gpi_alloc_chan(काष्ठा gchan *chan, bool send_alloc_cmd)
अणु
	काष्ठा gpii *gpii = chan->gpii;
	काष्ठा gpi_ring *ring = &chan->ch_ring;
	पूर्णांक ret;
	u32 id = gpii->gpii_id;
	u32 chid = chan->chid;
	u32 pair_chid = !chid;

	अगर (send_alloc_cmd) अणु
		ret = gpi_send_cmd(gpii, chan, GPI_CH_CMD_ALLOCATE);
		अगर (ret) अणु
			dev_err(gpii->gpi_dev->dev, "Error with cmd:%s ret:%d\n",
				TO_GPI_CMD_STR(GPI_CH_CMD_ALLOCATE), ret);
			वापस ret;
		पूर्ण
	पूर्ण

	gpi_ग_लिखो_reg(gpii, chan->ch_cntxt_base_reg + CNTXT_0_CONFIG,
		      GPII_n_CH_k_CNTXT_0(ring->el_size, 0, chan->dir, GPI_CHTYPE_PROTO_GPI));
	gpi_ग_लिखो_reg(gpii, chan->ch_cntxt_base_reg + CNTXT_1_R_LENGTH, ring->len);
	gpi_ग_लिखो_reg(gpii, chan->ch_cntxt_base_reg + CNTXT_2_RING_BASE_LSB, ring->phys_addr);
	gpi_ग_लिखो_reg(gpii, chan->ch_cntxt_base_reg + CNTXT_3_RING_BASE_MSB,
		      upper_32_bits(ring->phys_addr));
	gpi_ग_लिखो_reg(gpii, chan->ch_cntxt_db_reg + CNTXT_5_RING_RP_MSB - CNTXT_4_RING_RP_LSB,
		      upper_32_bits(ring->phys_addr));
	gpi_ग_लिखो_reg(gpii, gpii->regs + GPII_n_CH_k_SCRATCH_0_OFFS(id, chid),
		      GPII_n_CH_k_SCRATCH_0(pair_chid, chan->protocol, chan->seid));
	gpi_ग_लिखो_reg(gpii, gpii->regs + GPII_n_CH_k_SCRATCH_1_OFFS(id, chid), 0);
	gpi_ग_लिखो_reg(gpii, gpii->regs + GPII_n_CH_k_SCRATCH_2_OFFS(id, chid), 0);
	gpi_ग_लिखो_reg(gpii, gpii->regs + GPII_n_CH_k_SCRATCH_3_OFFS(id, chid), 0);
	gpi_ग_लिखो_reg(gpii, gpii->regs + GPII_n_CH_k_QOS_OFFS(id, chid), 1);

	/* flush all the ग_लिखोs */
	wmb();
	वापस 0;
पूर्ण

/* allocate and configure event ring */
अटल पूर्णांक gpi_alloc_ev_chan(काष्ठा gpii *gpii)
अणु
	काष्ठा gpi_ring *ring = &gpii->ev_ring;
	व्योम __iomem *base = gpii->ev_cntxt_base_reg;
	पूर्णांक ret;

	ret = gpi_send_cmd(gpii, शून्य, GPI_EV_CMD_ALLOCATE);
	अगर (ret) अणु
		dev_err(gpii->gpi_dev->dev, "error with cmd:%s ret:%d\n",
			TO_GPI_CMD_STR(GPI_EV_CMD_ALLOCATE), ret);
		वापस ret;
	पूर्ण

	/* program event context */
	gpi_ग_लिखो_reg(gpii, base + CNTXT_0_CONFIG,
		      GPII_n_EV_k_CNTXT_0(ring->el_size, GPI_INTTYPE_IRQ, GPI_CHTYPE_GPI_EV));
	gpi_ग_लिखो_reg(gpii, base + CNTXT_1_R_LENGTH, ring->len);
	gpi_ग_लिखो_reg(gpii, base + CNTXT_2_RING_BASE_LSB, lower_32_bits(ring->phys_addr));
	gpi_ग_लिखो_reg(gpii, base + CNTXT_3_RING_BASE_MSB, upper_32_bits(ring->phys_addr));
	gpi_ग_लिखो_reg(gpii, gpii->ev_cntxt_db_reg + CNTXT_5_RING_RP_MSB - CNTXT_4_RING_RP_LSB,
		      upper_32_bits(ring->phys_addr));
	gpi_ग_लिखो_reg(gpii, base + CNTXT_8_RING_INT_MOD, 0);
	gpi_ग_लिखो_reg(gpii, base + CNTXT_10_RING_MSI_LSB, 0);
	gpi_ग_लिखो_reg(gpii, base + CNTXT_11_RING_MSI_MSB, 0);
	gpi_ग_लिखो_reg(gpii, base + CNTXT_8_RING_INT_MOD, 0);
	gpi_ग_लिखो_reg(gpii, base + CNTXT_12_RING_RP_UPDATE_LSB, 0);
	gpi_ग_लिखो_reg(gpii, base + CNTXT_13_RING_RP_UPDATE_MSB, 0);

	/* add events to ring */
	ring->wp = (ring->base + ring->len - ring->el_size);

	/* flush all the ग_लिखोs */
	wmb();

	/* gpii is active now */
	ग_लिखो_lock_irq(&gpii->pm_lock);
	gpii->pm_state = ACTIVE_STATE;
	ग_लिखो_unlock_irq(&gpii->pm_lock);
	gpi_ग_लिखो_ev_db(gpii, ring, ring->wp);

	वापस 0;
पूर्ण

/* calculate # of ERE/TRE available to queue */
अटल पूर्णांक gpi_ring_num_elements_avail(स्थिर काष्ठा gpi_ring * स्थिर ring)
अणु
	पूर्णांक elements = 0;

	अगर (ring->wp < ring->rp) अणु
		elements = ((ring->rp - ring->wp) / ring->el_size) - 1;
	पूर्ण अन्यथा अणु
		elements = (ring->rp - ring->base) / ring->el_size;
		elements += ((ring->base + ring->len - ring->wp) / ring->el_size) - 1;
	पूर्ण

	वापस elements;
पूर्ण

अटल पूर्णांक gpi_ring_add_element(काष्ठा gpi_ring *ring, व्योम **wp)
अणु
	अगर (gpi_ring_num_elements_avail(ring) <= 0)
		वापस -ENOMEM;

	*wp = ring->wp;
	ring->wp += ring->el_size;
	अगर (ring->wp  >= (ring->base + ring->len))
		ring->wp = ring->base;

	/* visible to other cores */
	smp_wmb();

	वापस 0;
पूर्ण

अटल व्योम gpi_ring_recycle_ev_element(काष्ठा gpi_ring *ring)
अणु
	/* Update the WP */
	ring->wp += ring->el_size;
	अगर (ring->wp  >= (ring->base + ring->len))
		ring->wp = ring->base;

	/* Update the RP */
	ring->rp += ring->el_size;
	अगर (ring->rp  >= (ring->base + ring->len))
		ring->rp = ring->base;

	/* visible to other cores */
	smp_wmb();
पूर्ण

अटल व्योम gpi_मुक्त_ring(काष्ठा gpi_ring *ring,
			  काष्ठा gpii *gpii)
अणु
	dma_मुक्त_coherent(gpii->gpi_dev->dev, ring->alloc_size,
			  ring->pre_aligned, ring->dma_handle);
	स_रखो(ring, 0, माप(*ring));
पूर्ण

/* allocate memory क्रम transfer and event rings */
अटल पूर्णांक gpi_alloc_ring(काष्ठा gpi_ring *ring, u32 elements,
			  u32 el_size, काष्ठा gpii *gpii)
अणु
	u64 len = elements * el_size;
	पूर्णांक bit;

	/* ring len must be घातer of 2 */
	bit = find_last_bit((अचिन्हित दीर्घ *)&len, 32);
	अगर (((1 << bit) - 1) & len)
		bit++;
	len = 1 << bit;
	ring->alloc_size = (len + (len - 1));
	dev_dbg(gpii->gpi_dev->dev,
		"#el:%u el_size:%u len:%u actual_len:%llu alloc_size:%zu\n",
		  elements, el_size, (elements * el_size), len,
		  ring->alloc_size);

	ring->pre_aligned = dma_alloc_coherent(gpii->gpi_dev->dev,
					       ring->alloc_size,
					       &ring->dma_handle, GFP_KERNEL);
	अगर (!ring->pre_aligned) अणु
		dev_err(gpii->gpi_dev->dev, "could not alloc size:%zu mem for ring\n",
			ring->alloc_size);
		वापस -ENOMEM;
	पूर्ण

	/* align the physical mem */
	ring->phys_addr = (ring->dma_handle + (len - 1)) & ~(len - 1);
	ring->base = ring->pre_aligned + (ring->phys_addr - ring->dma_handle);
	ring->rp = ring->base;
	ring->wp = ring->base;
	ring->len = len;
	ring->el_size = el_size;
	ring->elements = ring->len / ring->el_size;
	स_रखो(ring->base, 0, ring->len);
	ring->configured = true;

	/* update to other cores */
	smp_wmb();

	dev_dbg(gpii->gpi_dev->dev,
		"phy_pre:%pad phy_alig:%pa len:%u el_size:%u elements:%u\n",
		&ring->dma_handle, &ring->phys_addr, ring->len,
		ring->el_size, ring->elements);

	वापस 0;
पूर्ण

/* copy tre पूर्णांकo transfer ring */
अटल व्योम gpi_queue_xfer(काष्ठा gpii *gpii, काष्ठा gchan *gchan,
			   काष्ठा gpi_tre *gpi_tre, व्योम **wp)
अणु
	काष्ठा gpi_tre *ch_tre;
	पूर्णांक ret;

	/* get next tre location we can copy */
	ret = gpi_ring_add_element(&gchan->ch_ring, (व्योम **)&ch_tre);
	अगर (unlikely(ret)) अणु
		dev_err(gpii->gpi_dev->dev, "Error adding ring element to xfer ring\n");
		वापस;
	पूर्ण

	/* copy the tre info */
	स_नकल(ch_tre, gpi_tre, माप(*ch_tre));
	*wp = ch_tre;
पूर्ण

/* reset and restart transfer channel */
अटल पूर्णांक gpi_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा gchan *gchan = to_gchan(chan);
	काष्ठा gpii *gpii = gchan->gpii;
	पूर्णांक schid, echid, i;
	पूर्णांक ret = 0;

	mutex_lock(&gpii->ctrl_lock);

	/*
	 * treat both channels as a group अगर its protocol is not UART
	 * STOP, RESET, or START needs to be in lockstep
	 */
	schid = (gchan->protocol == QCOM_GPI_UART) ? gchan->chid : 0;
	echid = (gchan->protocol == QCOM_GPI_UART) ? schid + 1 : MAX_CHANNELS_PER_GPII;

	/* stop the channel */
	क्रम (i = schid; i < echid; i++) अणु
		gchan = &gpii->gchan[i];

		/* disable ch state so no more TRE processing */
		ग_लिखो_lock_irq(&gpii->pm_lock);
		gchan->pm_state = PREPARE_TERMINATE;
		ग_लिखो_unlock_irq(&gpii->pm_lock);

		/* send command to Stop the channel */
		ret = gpi_stop_chan(gchan);
	पूर्ण

	/* reset the channels (clears any pending tre) */
	क्रम (i = schid; i < echid; i++) अणु
		gchan = &gpii->gchan[i];

		ret = gpi_reset_chan(gchan, GPI_CH_CMD_RESET);
		अगर (ret) अणु
			dev_err(gpii->gpi_dev->dev, "Error resetting channel ret:%d\n", ret);
			जाओ terminate_निकास;
		पूर्ण

		/* reprogram channel CNTXT */
		ret = gpi_alloc_chan(gchan, false);
		अगर (ret) अणु
			dev_err(gpii->gpi_dev->dev, "Error alloc_channel ret:%d\n", ret);
			जाओ terminate_निकास;
		पूर्ण
	पूर्ण

	/* restart the channels */
	क्रम (i = schid; i < echid; i++) अणु
		gchan = &gpii->gchan[i];

		ret = gpi_start_chan(gchan);
		अगर (ret) अणु
			dev_err(gpii->gpi_dev->dev, "Error Starting Channel ret:%d\n", ret);
			जाओ terminate_निकास;
		पूर्ण
	पूर्ण

terminate_निकास:
	mutex_unlock(&gpii->ctrl_lock);
	वापस ret;
पूर्ण

/* छोड़ो dma transfer क्रम all channels */
अटल पूर्णांक gpi_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा gchan *gchan = to_gchan(chan);
	काष्ठा gpii *gpii = gchan->gpii;
	पूर्णांक i, ret;

	mutex_lock(&gpii->ctrl_lock);

	/*
	 * छोड़ो/resume are per gpii not per channel, so
	 * client needs to call छोड़ो only once
	 */
	अगर (gpii->pm_state == PAUSE_STATE) अणु
		dev_dbg(gpii->gpi_dev->dev, "channel is already paused\n");
		mutex_unlock(&gpii->ctrl_lock);
		वापस 0;
	पूर्ण

	/* send stop command to stop the channels */
	क्रम (i = 0; i < MAX_CHANNELS_PER_GPII; i++) अणु
		ret = gpi_stop_chan(&gpii->gchan[i]);
		अगर (ret) अणु
			mutex_unlock(&gpii->ctrl_lock);
			वापस ret;
		पूर्ण
	पूर्ण

	disable_irq(gpii->irq);

	/* Wait क्रम thपढ़ोs to complete out */
	tasklet_समाप्त(&gpii->ev_task);

	ग_लिखो_lock_irq(&gpii->pm_lock);
	gpii->pm_state = PAUSE_STATE;
	ग_लिखो_unlock_irq(&gpii->pm_lock);
	mutex_unlock(&gpii->ctrl_lock);

	वापस 0;
पूर्ण

/* resume dma transfer */
अटल पूर्णांक gpi_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा gchan *gchan = to_gchan(chan);
	काष्ठा gpii *gpii = gchan->gpii;
	पूर्णांक i, ret;

	mutex_lock(&gpii->ctrl_lock);
	अगर (gpii->pm_state == ACTIVE_STATE) अणु
		dev_dbg(gpii->gpi_dev->dev, "channel is already active\n");
		mutex_unlock(&gpii->ctrl_lock);
		वापस 0;
	पूर्ण

	enable_irq(gpii->irq);

	/* send start command to start the channels */
	क्रम (i = 0; i < MAX_CHANNELS_PER_GPII; i++) अणु
		ret = gpi_send_cmd(gpii, &gpii->gchan[i], GPI_CH_CMD_START);
		अगर (ret) अणु
			dev_err(gpii->gpi_dev->dev, "Error starting chan, ret:%d\n", ret);
			mutex_unlock(&gpii->ctrl_lock);
			वापस ret;
		पूर्ण
	पूर्ण

	ग_लिखो_lock_irq(&gpii->pm_lock);
	gpii->pm_state = ACTIVE_STATE;
	ग_लिखो_unlock_irq(&gpii->pm_lock);
	mutex_unlock(&gpii->ctrl_lock);

	वापस 0;
पूर्ण

अटल व्योम gpi_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा gpi_desc *gpi_desc = to_gpi_desc(vd);

	kमुक्त(gpi_desc);
	gpi_desc = शून्य;
पूर्ण

अटल पूर्णांक
gpi_peripheral_config(काष्ठा dma_chan *chan, काष्ठा dma_slave_config *config)
अणु
	काष्ठा gchan *gchan = to_gchan(chan);

	अगर (!config->peripheral_config)
		वापस -EINVAL;

	gchan->config = kपुनः_स्मृति(gchan->config, config->peripheral_size, GFP_NOWAIT);
	अगर (!gchan->config)
		वापस -ENOMEM;

	स_नकल(gchan->config, config->peripheral_config, config->peripheral_size);

	वापस 0;
पूर्ण

अटल पूर्णांक gpi_create_i2c_tre(काष्ठा gchan *chan, काष्ठा gpi_desc *desc,
			      काष्ठा scatterlist *sgl, क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा gpi_i2c_config *i2c = chan->config;
	काष्ठा device *dev = chan->gpii->gpi_dev->dev;
	अचिन्हित पूर्णांक tre_idx = 0;
	dma_addr_t address;
	काष्ठा gpi_tre *tre;
	अचिन्हित पूर्णांक i;

	/* first create config tre अगर applicable */
	अगर (i2c->set_config) अणु
		tre = &desc->tre[tre_idx];
		tre_idx++;

		tre->dword[0] = u32_encode_bits(i2c->low_count, TRE_I2C_C0_TLOW);
		tre->dword[0] |= u32_encode_bits(i2c->high_count, TRE_I2C_C0_THIGH);
		tre->dword[0] |= u32_encode_bits(i2c->cycle_count, TRE_I2C_C0_TCYL);
		tre->dword[0] |= u32_encode_bits(i2c->pack_enable, TRE_I2C_C0_TX_PACK);
		tre->dword[0] |= u32_encode_bits(i2c->pack_enable, TRE_I2C_C0_RX_PACK);

		tre->dword[1] = 0;

		tre->dword[2] = u32_encode_bits(i2c->clk_भाग, TRE_C0_CLK_DIV);

		tre->dword[3] = u32_encode_bits(TRE_TYPE_CONFIG0, TRE_FLAGS_TYPE);
		tre->dword[3] |= u32_encode_bits(1, TRE_FLAGS_CHAIN);
	पूर्ण

	/* create the GO tre क्रम Tx */
	अगर (i2c->op == I2C_WRITE) अणु
		tre = &desc->tre[tre_idx];
		tre_idx++;

		अगर (i2c->multi_msg)
			tre->dword[0] = u32_encode_bits(I2C_READ, TRE_I2C_GO_CMD);
		अन्यथा
			tre->dword[0] = u32_encode_bits(i2c->op, TRE_I2C_GO_CMD);

		tre->dword[0] |= u32_encode_bits(i2c->addr, TRE_I2C_GO_ADDR);
		tre->dword[0] |= u32_encode_bits(i2c->stretch, TRE_I2C_GO_STRETCH);

		tre->dword[1] = 0;
		tre->dword[2] = u32_encode_bits(i2c->rx_len, TRE_RX_LEN);

		tre->dword[3] = u32_encode_bits(TRE_TYPE_GO, TRE_FLAGS_TYPE);

		अगर (i2c->multi_msg)
			tre->dword[3] |= u32_encode_bits(1, TRE_FLAGS_LINK);
		अन्यथा
			tre->dword[3] |= u32_encode_bits(1, TRE_FLAGS_CHAIN);
	पूर्ण

	अगर (i2c->op == I2C_READ || i2c->multi_msg == false) अणु
		/* create the DMA TRE */
		tre = &desc->tre[tre_idx];
		tre_idx++;

		address = sg_dma_address(sgl);
		tre->dword[0] = lower_32_bits(address);
		tre->dword[1] = upper_32_bits(address);

		tre->dword[2] = u32_encode_bits(sg_dma_len(sgl), TRE_DMA_LEN);

		tre->dword[3] = u32_encode_bits(TRE_TYPE_DMA, TRE_FLAGS_TYPE);
		tre->dword[3] |= u32_encode_bits(1, TRE_FLAGS_IEOT);
	पूर्ण

	क्रम (i = 0; i < tre_idx; i++)
		dev_dbg(dev, "TRE:%d %x:%x:%x:%x\n", i, desc->tre[i].dword[0],
			desc->tre[i].dword[1], desc->tre[i].dword[2], desc->tre[i].dword[3]);

	वापस tre_idx;
पूर्ण

अटल पूर्णांक gpi_create_spi_tre(काष्ठा gchan *chan, काष्ठा gpi_desc *desc,
			      काष्ठा scatterlist *sgl, क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा gpi_spi_config *spi = chan->config;
	काष्ठा device *dev = chan->gpii->gpi_dev->dev;
	अचिन्हित पूर्णांक tre_idx = 0;
	dma_addr_t address;
	काष्ठा gpi_tre *tre;
	अचिन्हित पूर्णांक i;

	/* first create config tre अगर applicable */
	अगर (direction == DMA_MEM_TO_DEV && spi->set_config) अणु
		tre = &desc->tre[tre_idx];
		tre_idx++;

		tre->dword[0] = u32_encode_bits(spi->word_len, TRE_SPI_C0_WORD_SZ);
		tre->dword[0] |= u32_encode_bits(spi->loopback_en, TRE_SPI_C0_LOOPBACK);
		tre->dword[0] |= u32_encode_bits(spi->घड़ी_pol_high, TRE_SPI_C0_CPOL);
		tre->dword[0] |= u32_encode_bits(spi->data_pol_high, TRE_SPI_C0_CPHA);
		tre->dword[0] |= u32_encode_bits(spi->pack_en, TRE_SPI_C0_TX_PACK);
		tre->dword[0] |= u32_encode_bits(spi->pack_en, TRE_SPI_C0_RX_PACK);

		tre->dword[1] = 0;

		tre->dword[2] = u32_encode_bits(spi->clk_भाग, TRE_C0_CLK_DIV);
		tre->dword[2] |= u32_encode_bits(spi->clk_src, TRE_C0_CLK_SRC);

		tre->dword[3] = u32_encode_bits(TRE_TYPE_CONFIG0, TRE_FLAGS_TYPE);
		tre->dword[3] |= u32_encode_bits(1, TRE_FLAGS_CHAIN);
	पूर्ण

	/* create the GO tre क्रम Tx */
	अगर (direction == DMA_MEM_TO_DEV) अणु
		tre = &desc->tre[tre_idx];
		tre_idx++;

		tre->dword[0] = u32_encode_bits(spi->fragmentation, TRE_SPI_GO_FRAG);
		tre->dword[0] |= u32_encode_bits(spi->cs, TRE_SPI_GO_CS);
		tre->dword[0] |= u32_encode_bits(spi->cmd, TRE_SPI_GO_CMD);

		tre->dword[1] = 0;

		tre->dword[2] = u32_encode_bits(spi->rx_len, TRE_RX_LEN);

		tre->dword[3] = u32_encode_bits(TRE_TYPE_GO, TRE_FLAGS_TYPE);
		अगर (spi->cmd == SPI_RX)
			tre->dword[3] |= u32_encode_bits(1, TRE_FLAGS_IEOB);
		अन्यथा
			tre->dword[3] |= u32_encode_bits(1, TRE_FLAGS_CHAIN);
	पूर्ण

	/* create the dma tre */
	tre = &desc->tre[tre_idx];
	tre_idx++;

	address = sg_dma_address(sgl);
	tre->dword[0] = lower_32_bits(address);
	tre->dword[1] = upper_32_bits(address);

	tre->dword[2] = u32_encode_bits(sg_dma_len(sgl), TRE_DMA_LEN);

	tre->dword[3] = u32_encode_bits(TRE_TYPE_DMA, TRE_FLAGS_TYPE);
	अगर (direction == DMA_MEM_TO_DEV)
		tre->dword[3] |= u32_encode_bits(1, TRE_FLAGS_IEOT);

	क्रम (i = 0; i < tre_idx; i++)
		dev_dbg(dev, "TRE:%d %x:%x:%x:%x\n", i, desc->tre[i].dword[0],
			desc->tre[i].dword[1], desc->tre[i].dword[2], desc->tre[i].dword[3]);

	वापस tre_idx;
पूर्ण

/* copy tre पूर्णांकo transfer ring */
अटल काष्ठा dma_async_tx_descriptor *
gpi_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		  अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		  अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा gchan *gchan = to_gchan(chan);
	काष्ठा gpii *gpii = gchan->gpii;
	काष्ठा device *dev = gpii->gpi_dev->dev;
	काष्ठा gpi_ring *ch_ring = &gchan->ch_ring;
	काष्ठा gpi_desc *gpi_desc;
	u32 nr, nr_tre = 0;
	u8 set_config;
	पूर्णांक i;

	gpii->ieob_set = false;
	अगर (!is_slave_direction(direction)) अणु
		dev_err(gpii->gpi_dev->dev, "invalid dma direction: %d\n", direction);
		वापस शून्य;
	पूर्ण

	अगर (sg_len > 1) अणु
		dev_err(dev, "Multi sg sent, we support only one atm: %d\n", sg_len);
		वापस शून्य;
	पूर्ण

	nr_tre = 3;
	set_config = *(u32 *)gchan->config;
	अगर (!set_config)
		nr_tre = 2;
	अगर (direction == DMA_DEV_TO_MEM) /* rx */
		nr_tre = 1;

	/* calculate # of elements required & available */
	nr = gpi_ring_num_elements_avail(ch_ring);
	अगर (nr < nr_tre) अणु
		dev_err(dev, "not enough space in ring, avail:%u required:%u\n", nr, nr_tre);
		वापस शून्य;
	पूर्ण

	gpi_desc = kzalloc(माप(*gpi_desc), GFP_NOWAIT);
	अगर (!gpi_desc)
		वापस शून्य;

	/* create TREs क्रम xfer */
	अगर (gchan->protocol == QCOM_GPI_SPI) अणु
		i = gpi_create_spi_tre(gchan, gpi_desc, sgl, direction);
	पूर्ण अन्यथा अगर (gchan->protocol == QCOM_GPI_I2C) अणु
		i = gpi_create_i2c_tre(gchan, gpi_desc, sgl, direction);
	पूर्ण अन्यथा अणु
		dev_err(dev, "invalid peripheral: %d\n", gchan->protocol);
		kमुक्त(gpi_desc);
		वापस शून्य;
	पूर्ण

	/* set up the descriptor */
	gpi_desc->gchan = gchan;
	gpi_desc->len = sg_dma_len(sgl);
	gpi_desc->num_tre  = i;

	वापस vchan_tx_prep(&gchan->vc, &gpi_desc->vd, flags);
पूर्ण

/* rings transfer ring db to being transfer */
अटल व्योम gpi_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा gchan *gchan = to_gchan(chan);
	काष्ठा gpii *gpii = gchan->gpii;
	अचिन्हित दीर्घ flags, pm_lock_flags;
	काष्ठा virt_dma_desc *vd = शून्य;
	काष्ठा gpi_desc *gpi_desc;
	काष्ठा gpi_ring *ch_ring = &gchan->ch_ring;
	व्योम *tre, *wp = शून्य;
	पूर्णांक i;

	पढ़ो_lock_irqsave(&gpii->pm_lock, pm_lock_flags);

	/* move all submitted discriptors to issued list */
	spin_lock_irqsave(&gchan->vc.lock, flags);
	अगर (vchan_issue_pending(&gchan->vc))
		vd = list_last_entry(&gchan->vc.desc_issued,
				     काष्ठा virt_dma_desc, node);
	spin_unlock_irqrestore(&gchan->vc.lock, flags);

	/* nothing to करो list is empty */
	अगर (!vd) अणु
		पढ़ो_unlock_irqrestore(&gpii->pm_lock, pm_lock_flags);
		वापस;
	पूर्ण

	gpi_desc = to_gpi_desc(vd);
	क्रम (i = 0; i < gpi_desc->num_tre; i++) अणु
		tre = &gpi_desc->tre[i];
		gpi_queue_xfer(gpii, gchan, tre, &wp);
	पूर्ण

	gpi_desc->db = ch_ring->wp;
	gpi_ग_लिखो_ch_db(gchan, &gchan->ch_ring, gpi_desc->db);
	पढ़ो_unlock_irqrestore(&gpii->pm_lock, pm_lock_flags);
पूर्ण

अटल पूर्णांक gpi_ch_init(काष्ठा gchan *gchan)
अणु
	काष्ठा gpii *gpii = gchan->gpii;
	स्थिर पूर्णांक ev_factor = gpii->gpi_dev->ev_factor;
	u32 elements;
	पूर्णांक i = 0, ret = 0;

	gchan->pm_state = CONFIG_STATE;

	/* check अगर both channels are configured beक्रमe जारी */
	क्रम (i = 0; i < MAX_CHANNELS_PER_GPII; i++)
		अगर (gpii->gchan[i].pm_state != CONFIG_STATE)
			जाओ निकास_gpi_init;

	/* protocol must be same क्रम both channels */
	अगर (gpii->gchan[0].protocol != gpii->gchan[1].protocol) अणु
		dev_err(gpii->gpi_dev->dev, "protocol did not match protocol %u != %u\n",
			gpii->gchan[0].protocol, gpii->gchan[1].protocol);
		ret = -EINVAL;
		जाओ निकास_gpi_init;
	पूर्ण

	/* allocate memory क्रम event ring */
	elements = CHAN_TRES << ev_factor;
	ret = gpi_alloc_ring(&gpii->ev_ring, elements,
			     माप(जोड़ gpi_event), gpii);
	अगर (ret)
		जाओ निकास_gpi_init;

	/* configure पूर्णांकerrupts */
	ग_लिखो_lock_irq(&gpii->pm_lock);
	gpii->pm_state = PREPARE_HARDWARE;
	ग_लिखो_unlock_irq(&gpii->pm_lock);
	ret = gpi_config_पूर्णांकerrupts(gpii, DEFAULT_IRQ_SETTINGS, 0);
	अगर (ret) अणु
		dev_err(gpii->gpi_dev->dev, "error config. interrupts, ret:%d\n", ret);
		जाओ error_config_पूर्णांक;
	पूर्ण

	/* allocate event rings */
	ret = gpi_alloc_ev_chan(gpii);
	अगर (ret) अणु
		dev_err(gpii->gpi_dev->dev, "error alloc_ev_chan:%d\n", ret);
		जाओ error_alloc_ev_ring;
	पूर्ण

	/* Allocate all channels */
	क्रम (i = 0; i < MAX_CHANNELS_PER_GPII; i++) अणु
		ret = gpi_alloc_chan(&gpii->gchan[i], true);
		अगर (ret) अणु
			dev_err(gpii->gpi_dev->dev, "Error allocating chan:%d\n", ret);
			जाओ error_alloc_chan;
		पूर्ण
	पूर्ण

	/* start channels  */
	क्रम (i = 0; i < MAX_CHANNELS_PER_GPII; i++) अणु
		ret = gpi_start_chan(&gpii->gchan[i]);
		अगर (ret) अणु
			dev_err(gpii->gpi_dev->dev, "Error start chan:%d\n", ret);
			जाओ error_start_chan;
		पूर्ण
	पूर्ण
	वापस ret;

error_start_chan:
	क्रम (i = i - 1; i >= 0; i--) अणु
		gpi_stop_chan(&gpii->gchan[i]);
		gpi_send_cmd(gpii, gchan, GPI_CH_CMD_RESET);
	पूर्ण
	i = 2;
error_alloc_chan:
	क्रम (i = i - 1; i >= 0; i--)
		gpi_reset_chan(gchan, GPI_CH_CMD_DE_ALLOC);
error_alloc_ev_ring:
	gpi_disable_पूर्णांकerrupts(gpii);
error_config_पूर्णांक:
	gpi_मुक्त_ring(&gpii->ev_ring, gpii);
निकास_gpi_init:
	mutex_unlock(&gpii->ctrl_lock);
	वापस ret;
पूर्ण

/* release all channel resources */
अटल व्योम gpi_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा gchan *gchan = to_gchan(chan);
	काष्ठा gpii *gpii = gchan->gpii;
	क्रमागत gpi_pm_state cur_state;
	पूर्णांक ret, i;

	mutex_lock(&gpii->ctrl_lock);

	cur_state = gchan->pm_state;

	/* disable ch state so no more TRE processing क्रम this channel */
	ग_लिखो_lock_irq(&gpii->pm_lock);
	gchan->pm_state = PREPARE_TERMINATE;
	ग_लिखो_unlock_irq(&gpii->pm_lock);

	/* attempt to करो graceful hardware shutकरोwn */
	अगर (cur_state == ACTIVE_STATE) अणु
		gpi_stop_chan(gchan);

		ret = gpi_send_cmd(gpii, gchan, GPI_CH_CMD_RESET);
		अगर (ret)
			dev_err(gpii->gpi_dev->dev, "error resetting channel:%d\n", ret);

		gpi_reset_chan(gchan, GPI_CH_CMD_DE_ALLOC);
	पूर्ण

	/* मुक्त all allocated memory */
	gpi_मुक्त_ring(&gchan->ch_ring, gpii);
	vchan_मुक्त_chan_resources(&gchan->vc);
	kमुक्त(gchan->config);

	ग_लिखो_lock_irq(&gpii->pm_lock);
	gchan->pm_state = DISABLE_STATE;
	ग_लिखो_unlock_irq(&gpii->pm_lock);

	/* अगर other rings are still active निकास */
	क्रम (i = 0; i < MAX_CHANNELS_PER_GPII; i++)
		अगर (gpii->gchan[i].ch_ring.configured)
			जाओ निकास_मुक्त;

	/* deallocate EV Ring */
	cur_state = gpii->pm_state;
	ग_लिखो_lock_irq(&gpii->pm_lock);
	gpii->pm_state = PREPARE_TERMINATE;
	ग_लिखो_unlock_irq(&gpii->pm_lock);

	/* रुको क्रम thपढ़ोs to complete out */
	tasklet_समाप्त(&gpii->ev_task);

	/* send command to de allocate event ring */
	अगर (cur_state == ACTIVE_STATE)
		gpi_send_cmd(gpii, शून्य, GPI_EV_CMD_DEALLOC);

	gpi_मुक्त_ring(&gpii->ev_ring, gpii);

	/* disable पूर्णांकerrupts */
	अगर (cur_state == ACTIVE_STATE)
		gpi_disable_पूर्णांकerrupts(gpii);

	/* set final state to disable */
	ग_लिखो_lock_irq(&gpii->pm_lock);
	gpii->pm_state = DISABLE_STATE;
	ग_लिखो_unlock_irq(&gpii->pm_lock);

निकास_मुक्त:
	mutex_unlock(&gpii->ctrl_lock);
पूर्ण

/* allocate channel resources */
अटल पूर्णांक gpi_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा gchan *gchan = to_gchan(chan);
	काष्ठा gpii *gpii = gchan->gpii;
	पूर्णांक ret;

	mutex_lock(&gpii->ctrl_lock);

	/* allocate memory क्रम transfer ring */
	ret = gpi_alloc_ring(&gchan->ch_ring, CHAN_TRES,
			     माप(काष्ठा gpi_tre), gpii);
	अगर (ret)
		जाओ xfer_alloc_err;

	ret = gpi_ch_init(gchan);

	mutex_unlock(&gpii->ctrl_lock);

	वापस ret;
xfer_alloc_err:
	mutex_unlock(&gpii->ctrl_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक gpi_find_avail_gpii(काष्ठा gpi_dev *gpi_dev, u32 seid)
अणु
	काष्ठा gchan *tx_chan, *rx_chan;
	अचिन्हित पूर्णांक gpii;

	/* check अगर same seid is alपढ़ोy configured क्रम another chid */
	क्रम (gpii = 0; gpii < gpi_dev->max_gpii; gpii++) अणु
		अगर (!((1 << gpii) & gpi_dev->gpii_mask))
			जारी;

		tx_chan = &gpi_dev->gpiis[gpii].gchan[GPI_TX_CHAN];
		rx_chan = &gpi_dev->gpiis[gpii].gchan[GPI_RX_CHAN];

		अगर (rx_chan->vc.chan.client_count && rx_chan->seid == seid)
			वापस gpii;
		अगर (tx_chan->vc.chan.client_count && tx_chan->seid == seid)
			वापस gpii;
	पूर्ण

	/* no channels configured with same seid, वापस next avail gpii */
	क्रम (gpii = 0; gpii < gpi_dev->max_gpii; gpii++) अणु
		अगर (!((1 << gpii) & gpi_dev->gpii_mask))
			जारी;

		tx_chan = &gpi_dev->gpiis[gpii].gchan[GPI_TX_CHAN];
		rx_chan = &gpi_dev->gpiis[gpii].gchan[GPI_RX_CHAN];

		/* check अगर gpii is configured */
		अगर (tx_chan->vc.chan.client_count ||
		    rx_chan->vc.chan.client_count)
			जारी;

		/* found a मुक्त gpii */
		वापस gpii;
	पूर्ण

	/* no gpii instance available to use */
	वापस -EIO;
पूर्ण

/* gpi_of_dma_xlate: खोलो client requested channel */
अटल काष्ठा dma_chan *gpi_of_dma_xlate(काष्ठा of_phandle_args *args,
					 काष्ठा of_dma *of_dma)
अणु
	काष्ठा gpi_dev *gpi_dev = (काष्ठा gpi_dev *)of_dma->of_dma_data;
	u32 seid, chid;
	पूर्णांक gpii;
	काष्ठा gchan *gchan;

	अगर (args->args_count < 3) अणु
		dev_err(gpi_dev->dev, "gpii require minimum 2 args, client passed:%d args\n",
			args->args_count);
		वापस शून्य;
	पूर्ण

	chid = args->args[0];
	अगर (chid >= MAX_CHANNELS_PER_GPII) अणु
		dev_err(gpi_dev->dev, "gpii channel:%d not valid\n", chid);
		वापस शून्य;
	पूर्ण

	seid = args->args[1];

	/* find next available gpii to use */
	gpii = gpi_find_avail_gpii(gpi_dev, seid);
	अगर (gpii < 0) अणु
		dev_err(gpi_dev->dev, "no available gpii instances\n");
		वापस शून्य;
	पूर्ण

	gchan = &gpi_dev->gpiis[gpii].gchan[chid];
	अगर (gchan->vc.chan.client_count) अणु
		dev_err(gpi_dev->dev, "gpii:%d chid:%d seid:%d already configured\n",
			gpii, chid, gchan->seid);
		वापस शून्य;
	पूर्ण

	gchan->seid = seid;
	gchan->protocol = args->args[2];

	वापस dma_get_slave_channel(&gchan->vc.chan);
पूर्ण

अटल पूर्णांक gpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpi_dev *gpi_dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	gpi_dev = devm_kzalloc(&pdev->dev, माप(*gpi_dev), GFP_KERNEL);
	अगर (!gpi_dev)
		वापस -ENOMEM;

	gpi_dev->dev = &pdev->dev;
	gpi_dev->res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	gpi_dev->regs = devm_ioremap_resource(gpi_dev->dev, gpi_dev->res);
	अगर (IS_ERR(gpi_dev->regs))
		वापस PTR_ERR(gpi_dev->regs);
	gpi_dev->ee_base = gpi_dev->regs;

	ret = of_property_पढ़ो_u32(gpi_dev->dev->of_node, "dma-channels",
				   &gpi_dev->max_gpii);
	अगर (ret) अणु
		dev_err(gpi_dev->dev, "missing 'max-no-gpii' DT node\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(gpi_dev->dev->of_node, "dma-channel-mask",
				   &gpi_dev->gpii_mask);
	अगर (ret) अणु
		dev_err(gpi_dev->dev, "missing 'gpii-mask' DT node\n");
		वापस ret;
	पूर्ण

	gpi_dev->ev_factor = EV_FACTOR;

	ret = dma_set_mask(gpi_dev->dev, DMA_BIT_MASK(64));
	अगर (ret) अणु
		dev_err(gpi_dev->dev, "Error setting dma_mask to 64, ret:%d\n", ret);
		वापस ret;
	पूर्ण

	gpi_dev->gpiis = devm_kzalloc(gpi_dev->dev, माप(*gpi_dev->gpiis) *
				      gpi_dev->max_gpii, GFP_KERNEL);
	अगर (!gpi_dev->gpiis)
		वापस -ENOMEM;

	/* setup all the supported gpii */
	INIT_LIST_HEAD(&gpi_dev->dma_device.channels);
	क्रम (i = 0; i < gpi_dev->max_gpii; i++) अणु
		काष्ठा gpii *gpii = &gpi_dev->gpiis[i];
		पूर्णांक chan;

		अगर (!((1 << i) & gpi_dev->gpii_mask))
			जारी;

		/* set up ev cntxt रेजिस्टर map */
		gpii->ev_cntxt_base_reg = gpi_dev->ee_base + GPII_n_EV_CH_k_CNTXT_0_OFFS(i, 0);
		gpii->ev_cntxt_db_reg = gpi_dev->ee_base + GPII_n_EV_CH_k_DOORBELL_0_OFFS(i, 0);
		gpii->ev_ring_rp_lsb_reg = gpii->ev_cntxt_base_reg + CNTXT_4_RING_RP_LSB;
		gpii->ev_cmd_reg = gpi_dev->ee_base + GPII_n_EV_CH_CMD_OFFS(i);
		gpii->ieob_clr_reg = gpi_dev->ee_base + GPII_n_CNTXT_SRC_IEOB_IRQ_CLR_OFFS(i);

		/* set up irq */
		ret = platक्रमm_get_irq(pdev, i);
		अगर (ret < 0) अणु
			dev_err(gpi_dev->dev, "platform_get_irq failed for %d:%d\n", i, ret);
			वापस ret;
		पूर्ण
		gpii->irq = ret;

		/* set up channel specअगरic रेजिस्टर info */
		क्रम (chan = 0; chan < MAX_CHANNELS_PER_GPII; chan++) अणु
			काष्ठा gchan *gchan = &gpii->gchan[chan];

			/* set up ch cntxt रेजिस्टर map */
			gchan->ch_cntxt_base_reg = gpi_dev->ee_base +
				GPII_n_CH_k_CNTXT_0_OFFS(i, chan);
			gchan->ch_cntxt_db_reg = gpi_dev->ee_base +
				GPII_n_CH_k_DOORBELL_0_OFFS(i, chan);
			gchan->ch_cmd_reg = gpi_dev->ee_base + GPII_n_CH_CMD_OFFS(i);

			/* vchan setup */
			vchan_init(&gchan->vc, &gpi_dev->dma_device);
			gchan->vc.desc_मुक्त = gpi_desc_मुक्त;
			gchan->chid = chan;
			gchan->gpii = gpii;
			gchan->dir = GPII_CHAN_सूची[chan];
		पूर्ण
		mutex_init(&gpii->ctrl_lock);
		rwlock_init(&gpii->pm_lock);
		tasklet_init(&gpii->ev_task, gpi_ev_tasklet,
			     (अचिन्हित दीर्घ)gpii);
		init_completion(&gpii->cmd_completion);
		gpii->gpii_id = i;
		gpii->regs = gpi_dev->ee_base;
		gpii->gpi_dev = gpi_dev;
	पूर्ण

	platक्रमm_set_drvdata(pdev, gpi_dev);

	/* clear and Set capabilities */
	dma_cap_zero(gpi_dev->dma_device.cap_mask);
	dma_cap_set(DMA_SLAVE, gpi_dev->dma_device.cap_mask);

	/* configure dmaengine apis */
	gpi_dev->dma_device.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	gpi_dev->dma_device.residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;
	gpi_dev->dma_device.src_addr_widths = DMA_SLAVE_BUSWIDTH_8_BYTES;
	gpi_dev->dma_device.dst_addr_widths = DMA_SLAVE_BUSWIDTH_8_BYTES;
	gpi_dev->dma_device.device_alloc_chan_resources = gpi_alloc_chan_resources;
	gpi_dev->dma_device.device_मुक्त_chan_resources = gpi_मुक्त_chan_resources;
	gpi_dev->dma_device.device_tx_status = dma_cookie_status;
	gpi_dev->dma_device.device_issue_pending = gpi_issue_pending;
	gpi_dev->dma_device.device_prep_slave_sg = gpi_prep_slave_sg;
	gpi_dev->dma_device.device_config = gpi_peripheral_config;
	gpi_dev->dma_device.device_terminate_all = gpi_terminate_all;
	gpi_dev->dma_device.dev = gpi_dev->dev;
	gpi_dev->dma_device.device_छोड़ो = gpi_छोड़ो;
	gpi_dev->dma_device.device_resume = gpi_resume;

	/* रेजिस्टर with dmaengine framework */
	ret = dma_async_device_रेजिस्टर(&gpi_dev->dma_device);
	अगर (ret) अणु
		dev_err(gpi_dev->dev, "async_device_register failed ret:%d", ret);
		वापस ret;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(gpi_dev->dev->of_node,
					 gpi_of_dma_xlate, gpi_dev);
	अगर (ret) अणु
		dev_err(gpi_dev->dev, "of_dma_controller_reg failed ret:%d", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id gpi_of_match[] = अणु
	अणु .compatible = "qcom,sdm845-gpi-dma" पूर्ण,
	अणु .compatible = "qcom,sm8150-gpi-dma" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gpi_of_match);

अटल काष्ठा platक्रमm_driver gpi_driver = अणु
	.probe = gpi_probe,
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = gpi_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gpi_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gpi_driver);
पूर्ण
subsys_initcall(gpi_init)

MODULE_DESCRIPTION("QCOM GPI DMA engine driver");
MODULE_LICENSE("GPL v2");
