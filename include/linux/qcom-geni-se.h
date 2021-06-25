<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _LINUX_QCOM_GENI_SE
#घोषणा _LINUX_QCOM_GENI_SE

#समावेश <linux/पूर्णांकerconnect.h>

/* Transfer mode supported by GENI Serial Engines */
क्रमागत geni_se_xfer_mode अणु
	GENI_SE_INVALID,
	GENI_SE_FIFO,
	GENI_SE_DMA,
पूर्ण;

/* Protocols supported by GENI Serial Engines */
क्रमागत geni_se_protocol_type अणु
	GENI_SE_NONE,
	GENI_SE_SPI,
	GENI_SE_UART,
	GENI_SE_I2C,
	GENI_SE_I3C,
पूर्ण;

काष्ठा geni_wrapper;
काष्ठा clk;

क्रमागत geni_icc_path_index अणु
	GENI_TO_CORE,
	CPU_TO_GENI,
	GENI_TO_DDR
पूर्ण;

काष्ठा geni_icc_path अणु
	काष्ठा icc_path *path;
	अचिन्हित पूर्णांक avg_bw;
पूर्ण;

/**
 * काष्ठा geni_se - GENI Serial Engine
 * @base:		Base Address of the Serial Engine's रेजिस्टर block
 * @dev:		Poपूर्णांकer to the Serial Engine device
 * @wrapper:		Poपूर्णांकer to the parent QUP Wrapper core
 * @clk:		Handle to the core serial engine घड़ी
 * @num_clk_levels:	Number of valid घड़ी levels in clk_perf_tbl
 * @clk_perf_tbl:	Table of घड़ी frequency input to serial engine घड़ी
 * @icc_paths:		Array of ICC paths क्रम SE
 */
काष्ठा geni_se अणु
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा geni_wrapper *wrapper;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक num_clk_levels;
	अचिन्हित दीर्घ *clk_perf_tbl;
	काष्ठा geni_icc_path icc_paths[3];
पूर्ण;

/* Common SE रेजिस्टरs */
#घोषणा GENI_FORCE_DEFAULT_REG		0x20
#घोषणा SE_GENI_STATUS			0x40
#घोषणा GENI_SER_M_CLK_CFG		0x48
#घोषणा GENI_SER_S_CLK_CFG		0x4c
#घोषणा GENI_FW_REVISION_RO		0x68
#घोषणा SE_GENI_CLK_SEL			0x7c
#घोषणा SE_GENI_DMA_MODE_EN		0x258
#घोषणा SE_GENI_M_CMD0			0x600
#घोषणा SE_GENI_M_CMD_CTRL_REG		0x604
#घोषणा SE_GENI_M_IRQ_STATUS		0x610
#घोषणा SE_GENI_M_IRQ_EN		0x614
#घोषणा SE_GENI_M_IRQ_CLEAR		0x618
#घोषणा SE_GENI_S_CMD0			0x630
#घोषणा SE_GENI_S_CMD_CTRL_REG		0x634
#घोषणा SE_GENI_S_IRQ_STATUS		0x640
#घोषणा SE_GENI_S_IRQ_EN		0x644
#घोषणा SE_GENI_S_IRQ_CLEAR		0x648
#घोषणा SE_GENI_TX_FIFOn		0x700
#घोषणा SE_GENI_RX_FIFOn		0x780
#घोषणा SE_GENI_TX_FIFO_STATUS		0x800
#घोषणा SE_GENI_RX_FIFO_STATUS		0x804
#घोषणा SE_GENI_TX_WATERMARK_REG	0x80c
#घोषणा SE_GENI_RX_WATERMARK_REG	0x810
#घोषणा SE_GENI_RX_RFR_WATERMARK_REG	0x814
#घोषणा SE_GENI_IOS			0x908
#घोषणा SE_DMA_TX_IRQ_STAT		0xc40
#घोषणा SE_DMA_TX_IRQ_CLR		0xc44
#घोषणा SE_DMA_TX_FSM_RST		0xc58
#घोषणा SE_DMA_RX_IRQ_STAT		0xd40
#घोषणा SE_DMA_RX_IRQ_CLR		0xd44
#घोषणा SE_DMA_RX_FSM_RST		0xd58
#घोषणा SE_HW_PARAM_0			0xe24
#घोषणा SE_HW_PARAM_1			0xe28

/* GENI_FORCE_DEFAULT_REG fields */
#घोषणा FORCE_DEFAULT	BIT(0)

/* GENI_STATUS fields */
#घोषणा M_GENI_CMD_ACTIVE		BIT(0)
#घोषणा S_GENI_CMD_ACTIVE		BIT(12)

/* GENI_SER_M_CLK_CFG/GENI_SER_S_CLK_CFG */
#घोषणा SER_CLK_EN			BIT(0)
#घोषणा CLK_DIV_MSK			GENMASK(15, 4)
#घोषणा CLK_DIV_SHFT			4

/* GENI_FW_REVISION_RO fields */
#घोषणा FW_REV_PROTOCOL_MSK		GENMASK(15, 8)
#घोषणा FW_REV_PROTOCOL_SHFT		8

/* GENI_CLK_SEL fields */
#घोषणा CLK_SEL_MSK			GENMASK(2, 0)

/* SE_GENI_DMA_MODE_EN */
#घोषणा GENI_DMA_MODE_EN		BIT(0)

/* GENI_M_CMD0 fields */
#घोषणा M_OPCODE_MSK			GENMASK(31, 27)
#घोषणा M_OPCODE_SHFT			27
#घोषणा M_PARAMS_MSK			GENMASK(26, 0)

/* GENI_M_CMD_CTRL_REG */
#घोषणा M_GENI_CMD_CANCEL		BIT(2)
#घोषणा M_GENI_CMD_ABORT		BIT(1)
#घोषणा M_GENI_DISABLE			BIT(0)

/* GENI_S_CMD0 fields */
#घोषणा S_OPCODE_MSK			GENMASK(31, 27)
#घोषणा S_OPCODE_SHFT			27
#घोषणा S_PARAMS_MSK			GENMASK(26, 0)

/* GENI_S_CMD_CTRL_REG */
#घोषणा S_GENI_CMD_CANCEL		BIT(2)
#घोषणा S_GENI_CMD_ABORT		BIT(1)
#घोषणा S_GENI_DISABLE			BIT(0)

/* GENI_M_IRQ_EN fields */
#घोषणा M_CMD_DONE_EN			BIT(0)
#घोषणा M_CMD_OVERRUN_EN		BIT(1)
#घोषणा M_ILLEGAL_CMD_EN		BIT(2)
#घोषणा M_CMD_FAILURE_EN		BIT(3)
#घोषणा M_CMD_CANCEL_EN			BIT(4)
#घोषणा M_CMD_ABORT_EN			BIT(5)
#घोषणा M_TIMESTAMP_EN			BIT(6)
#घोषणा M_RX_IRQ_EN			BIT(7)
#घोषणा M_GP_SYNC_IRQ_0_EN		BIT(8)
#घोषणा M_GP_IRQ_0_EN			BIT(9)
#घोषणा M_GP_IRQ_1_EN			BIT(10)
#घोषणा M_GP_IRQ_2_EN			BIT(11)
#घोषणा M_GP_IRQ_3_EN			BIT(12)
#घोषणा M_GP_IRQ_4_EN			BIT(13)
#घोषणा M_GP_IRQ_5_EN			BIT(14)
#घोषणा M_IO_DATA_DEASSERT_EN		BIT(22)
#घोषणा M_IO_DATA_ASSERT_EN		BIT(23)
#घोषणा M_RX_FIFO_RD_ERR_EN		BIT(24)
#घोषणा M_RX_FIFO_WR_ERR_EN		BIT(25)
#घोषणा M_RX_FIFO_WATERMARK_EN		BIT(26)
#घोषणा M_RX_FIFO_LAST_EN		BIT(27)
#घोषणा M_TX_FIFO_RD_ERR_EN		BIT(28)
#घोषणा M_TX_FIFO_WR_ERR_EN		BIT(29)
#घोषणा M_TX_FIFO_WATERMARK_EN		BIT(30)
#घोषणा M_SEC_IRQ_EN			BIT(31)
#घोषणा M_COMMON_GENI_M_IRQ_EN	(GENMASK(6, 1) | \
				M_IO_DATA_DEASSERT_EN | \
				M_IO_DATA_ASSERT_EN | M_RX_FIFO_RD_ERR_EN | \
				M_RX_FIFO_WR_ERR_EN | M_TX_FIFO_RD_ERR_EN | \
				M_TX_FIFO_WR_ERR_EN)

/* GENI_S_IRQ_EN fields */
#घोषणा S_CMD_DONE_EN			BIT(0)
#घोषणा S_CMD_OVERRUN_EN		BIT(1)
#घोषणा S_ILLEGAL_CMD_EN		BIT(2)
#घोषणा S_CMD_FAILURE_EN		BIT(3)
#घोषणा S_CMD_CANCEL_EN			BIT(4)
#घोषणा S_CMD_ABORT_EN			BIT(5)
#घोषणा S_GP_SYNC_IRQ_0_EN		BIT(8)
#घोषणा S_GP_IRQ_0_EN			BIT(9)
#घोषणा S_GP_IRQ_1_EN			BIT(10)
#घोषणा S_GP_IRQ_2_EN			BIT(11)
#घोषणा S_GP_IRQ_3_EN			BIT(12)
#घोषणा S_GP_IRQ_4_EN			BIT(13)
#घोषणा S_GP_IRQ_5_EN			BIT(14)
#घोषणा S_IO_DATA_DEASSERT_EN		BIT(22)
#घोषणा S_IO_DATA_ASSERT_EN		BIT(23)
#घोषणा S_RX_FIFO_RD_ERR_EN		BIT(24)
#घोषणा S_RX_FIFO_WR_ERR_EN		BIT(25)
#घोषणा S_RX_FIFO_WATERMARK_EN		BIT(26)
#घोषणा S_RX_FIFO_LAST_EN		BIT(27)
#घोषणा S_COMMON_GENI_S_IRQ_EN	(GENMASK(5, 1) | GENMASK(13, 9) | \
				 S_RX_FIFO_RD_ERR_EN | S_RX_FIFO_WR_ERR_EN)

/*  GENI_/TX/RX/RX_RFR/_WATERMARK_REG fields */
#घोषणा WATERMARK_MSK			GENMASK(5, 0)

/* GENI_TX_FIFO_STATUS fields */
#घोषणा TX_FIFO_WC			GENMASK(27, 0)

/*  GENI_RX_FIFO_STATUS fields */
#घोषणा RX_LAST				BIT(31)
#घोषणा RX_LAST_BYTE_VALID_MSK		GENMASK(30, 28)
#घोषणा RX_LAST_BYTE_VALID_SHFT		28
#घोषणा RX_FIFO_WC_MSK			GENMASK(24, 0)

/* SE_GENI_IOS fields */
#घोषणा IO2_DATA_IN			BIT(1)
#घोषणा RX_DATA_IN			BIT(0)

/* SE_DMA_TX_IRQ_STAT Register fields */
#घोषणा TX_DMA_DONE			BIT(0)
#घोषणा TX_EOT				BIT(1)
#घोषणा TX_SBE				BIT(2)
#घोषणा TX_RESET_DONE			BIT(3)

/* SE_DMA_RX_IRQ_STAT Register fields */
#घोषणा RX_DMA_DONE			BIT(0)
#घोषणा RX_EOT				BIT(1)
#घोषणा RX_SBE				BIT(2)
#घोषणा RX_RESET_DONE			BIT(3)
#घोषणा RX_FLUSH_DONE			BIT(4)
#घोषणा RX_GENI_GP_IRQ			GENMASK(10, 5)
#घोषणा RX_GENI_CANCEL_IRQ		BIT(11)
#घोषणा RX_GENI_GP_IRQ_EXT		GENMASK(13, 12)

/* SE_HW_PARAM_0 fields */
#घोषणा TX_FIFO_WIDTH_MSK		GENMASK(29, 24)
#घोषणा TX_FIFO_WIDTH_SHFT		24
#घोषणा TX_FIFO_DEPTH_MSK		GENMASK(21, 16)
#घोषणा TX_FIFO_DEPTH_SHFT		16

/* SE_HW_PARAM_1 fields */
#घोषणा RX_FIFO_WIDTH_MSK		GENMASK(29, 24)
#घोषणा RX_FIFO_WIDTH_SHFT		24
#घोषणा RX_FIFO_DEPTH_MSK		GENMASK(21, 16)
#घोषणा RX_FIFO_DEPTH_SHFT		16

#घोषणा HW_VER_MAJOR_MASK		GENMASK(31, 28)
#घोषणा HW_VER_MAJOR_SHFT		28
#घोषणा HW_VER_MINOR_MASK		GENMASK(27, 16)
#घोषणा HW_VER_MINOR_SHFT		16
#घोषणा HW_VER_STEP_MASK		GENMASK(15, 0)

#घोषणा GENI_SE_VERSION_MAJOR(ver) ((ver & HW_VER_MAJOR_MASK) >> HW_VER_MAJOR_SHFT)
#घोषणा GENI_SE_VERSION_MINOR(ver) ((ver & HW_VER_MINOR_MASK) >> HW_VER_MINOR_SHFT)
#घोषणा GENI_SE_VERSION_STEP(ver) (ver & HW_VER_STEP_MASK)

/* QUP SE VERSION value क्रम major number 2 and minor number 5 */
#घोषणा QUP_SE_VERSION_2_5                  0x20050000

/*
 * Define bandwidth thresholds that cause the underlying Core 2X पूर्णांकerconnect
 * घड़ी to run at the named frequency. These baseline values are recommended
 * by the hardware team, and are not dynamically scaled with GENI bandwidth
 * beyond basic on/off.
 */
#घोषणा CORE_2X_19_2_MHZ		960
#घोषणा CORE_2X_50_MHZ			2500
#घोषणा CORE_2X_100_MHZ			5000
#घोषणा CORE_2X_150_MHZ			7500
#घोषणा CORE_2X_200_MHZ			10000
#घोषणा CORE_2X_236_MHZ			16383

#घोषणा GENI_DEFAULT_BW			Bps_to_icc(1000)

#अगर IS_ENABLED(CONFIG_QCOM_GENI_SE)

u32 geni_se_get_qup_hw_version(काष्ठा geni_se *se);

/**
 * geni_se_पढ़ो_proto() - Read the protocol configured क्रम a serial engine
 * @se:		Poपूर्णांकer to the concerned serial engine.
 *
 * Return: Protocol value as configured in the serial engine.
 */
अटल अंतरभूत u32 geni_se_पढ़ो_proto(काष्ठा geni_se *se)
अणु
	u32 val;

	val = पढ़ोl_relaxed(se->base + GENI_FW_REVISION_RO);

	वापस (val & FW_REV_PROTOCOL_MSK) >> FW_REV_PROTOCOL_SHFT;
पूर्ण

/**
 * geni_se_setup_m_cmd() - Setup the primary sequencer
 * @se:		Poपूर्णांकer to the concerned serial engine.
 * @cmd:	Command/Operation to setup in the primary sequencer.
 * @params:	Parameter क्रम the sequencer command.
 *
 * This function is used to configure the primary sequencer with the
 * command and its associated parameters.
 */
अटल अंतरभूत व्योम geni_se_setup_m_cmd(काष्ठा geni_se *se, u32 cmd, u32 params)
अणु
	u32 m_cmd;

	m_cmd = (cmd << M_OPCODE_SHFT) | (params & M_PARAMS_MSK);
	ग_लिखोl(m_cmd, se->base + SE_GENI_M_CMD0);
पूर्ण

/**
 * geni_se_setup_s_cmd() - Setup the secondary sequencer
 * @se:		Poपूर्णांकer to the concerned serial engine.
 * @cmd:	Command/Operation to setup in the secondary sequencer.
 * @params:	Parameter क्रम the sequencer command.
 *
 * This function is used to configure the secondary sequencer with the
 * command and its associated parameters.
 */
अटल अंतरभूत व्योम geni_se_setup_s_cmd(काष्ठा geni_se *se, u32 cmd, u32 params)
अणु
	u32 s_cmd;

	s_cmd = पढ़ोl_relaxed(se->base + SE_GENI_S_CMD0);
	s_cmd &= ~(S_OPCODE_MSK | S_PARAMS_MSK);
	s_cmd |= (cmd << S_OPCODE_SHFT);
	s_cmd |= (params & S_PARAMS_MSK);
	ग_लिखोl(s_cmd, se->base + SE_GENI_S_CMD0);
पूर्ण

/**
 * geni_se_cancel_m_cmd() - Cancel the command configured in the primary
 *                          sequencer
 * @se:	Poपूर्णांकer to the concerned serial engine.
 *
 * This function is used to cancel the currently configured command in the
 * primary sequencer.
 */
अटल अंतरभूत व्योम geni_se_cancel_m_cmd(काष्ठा geni_se *se)
अणु
	ग_लिखोl_relaxed(M_GENI_CMD_CANCEL, se->base + SE_GENI_M_CMD_CTRL_REG);
पूर्ण

/**
 * geni_se_cancel_s_cmd() - Cancel the command configured in the secondary
 *                          sequencer
 * @se:	Poपूर्णांकer to the concerned serial engine.
 *
 * This function is used to cancel the currently configured command in the
 * secondary sequencer.
 */
अटल अंतरभूत व्योम geni_se_cancel_s_cmd(काष्ठा geni_se *se)
अणु
	ग_लिखोl_relaxed(S_GENI_CMD_CANCEL, se->base + SE_GENI_S_CMD_CTRL_REG);
पूर्ण

/**
 * geni_se_पात_m_cmd() - Abort the command configured in the primary sequencer
 * @se:	Poपूर्णांकer to the concerned serial engine.
 *
 * This function is used to क्रमce पात the currently configured command in the
 * primary sequencer.
 */
अटल अंतरभूत व्योम geni_se_पात_m_cmd(काष्ठा geni_se *se)
अणु
	ग_लिखोl_relaxed(M_GENI_CMD_ABORT, se->base + SE_GENI_M_CMD_CTRL_REG);
पूर्ण

/**
 * geni_se_पात_s_cmd() - Abort the command configured in the secondary
 *                         sequencer
 * @se:	Poपूर्णांकer to the concerned serial engine.
 *
 * This function is used to क्रमce पात the currently configured command in the
 * secondary sequencer.
 */
अटल अंतरभूत व्योम geni_se_पात_s_cmd(काष्ठा geni_se *se)
अणु
	ग_लिखोl_relaxed(S_GENI_CMD_ABORT, se->base + SE_GENI_S_CMD_CTRL_REG);
पूर्ण

/**
 * geni_se_get_tx_fअगरo_depth() - Get the TX fअगरo depth of the serial engine
 * @se:	Poपूर्णांकer to the concerned serial engine.
 *
 * This function is used to get the depth i.e. number of elements in the
 * TX fअगरo of the serial engine.
 *
 * Return: TX fअगरo depth in units of FIFO words.
 */
अटल अंतरभूत u32 geni_se_get_tx_fअगरo_depth(काष्ठा geni_se *se)
अणु
	u32 val;

	val = पढ़ोl_relaxed(se->base + SE_HW_PARAM_0);

	वापस (val & TX_FIFO_DEPTH_MSK) >> TX_FIFO_DEPTH_SHFT;
पूर्ण

/**
 * geni_se_get_tx_fअगरo_width() - Get the TX fअगरo width of the serial engine
 * @se:	Poपूर्णांकer to the concerned serial engine.
 *
 * This function is used to get the width i.e. word size per element in the
 * TX fअगरo of the serial engine.
 *
 * Return: TX fअगरo width in bits
 */
अटल अंतरभूत u32 geni_se_get_tx_fअगरo_width(काष्ठा geni_se *se)
अणु
	u32 val;

	val = पढ़ोl_relaxed(se->base + SE_HW_PARAM_0);

	वापस (val & TX_FIFO_WIDTH_MSK) >> TX_FIFO_WIDTH_SHFT;
पूर्ण

/**
 * geni_se_get_rx_fअगरo_depth() - Get the RX fअगरo depth of the serial engine
 * @se:	Poपूर्णांकer to the concerned serial engine.
 *
 * This function is used to get the depth i.e. number of elements in the
 * RX fअगरo of the serial engine.
 *
 * Return: RX fअगरo depth in units of FIFO words
 */
अटल अंतरभूत u32 geni_se_get_rx_fअगरo_depth(काष्ठा geni_se *se)
अणु
	u32 val;

	val = पढ़ोl_relaxed(se->base + SE_HW_PARAM_1);

	वापस (val & RX_FIFO_DEPTH_MSK) >> RX_FIFO_DEPTH_SHFT;
पूर्ण

व्योम geni_se_init(काष्ठा geni_se *se, u32 rx_wm, u32 rx_rfr);

व्योम geni_se_select_mode(काष्ठा geni_se *se, क्रमागत geni_se_xfer_mode mode);

व्योम geni_se_config_packing(काष्ठा geni_se *se, पूर्णांक bpw, पूर्णांक pack_words,
			    bool msb_to_lsb, bool tx_cfg, bool rx_cfg);

पूर्णांक geni_se_resources_off(काष्ठा geni_se *se);

पूर्णांक geni_se_resources_on(काष्ठा geni_se *se);

पूर्णांक geni_se_clk_tbl_get(काष्ठा geni_se *se, अचिन्हित दीर्घ **tbl);

पूर्णांक geni_se_clk_freq_match(काष्ठा geni_se *se, अचिन्हित दीर्घ req_freq,
			   अचिन्हित पूर्णांक *index, अचिन्हित दीर्घ *res_freq,
			   bool exact);

पूर्णांक geni_se_tx_dma_prep(काष्ठा geni_se *se, व्योम *buf, माप_प्रकार len,
			dma_addr_t *iova);

पूर्णांक geni_se_rx_dma_prep(काष्ठा geni_se *se, व्योम *buf, माप_प्रकार len,
			dma_addr_t *iova);

व्योम geni_se_tx_dma_unprep(काष्ठा geni_se *se, dma_addr_t iova, माप_प्रकार len);

व्योम geni_se_rx_dma_unprep(काष्ठा geni_se *se, dma_addr_t iova, माप_प्रकार len);

पूर्णांक geni_icc_get(काष्ठा geni_se *se, स्थिर अक्षर *icc_ddr);

पूर्णांक geni_icc_set_bw(काष्ठा geni_se *se);
व्योम geni_icc_set_tag(काष्ठा geni_se *se, u32 tag);

पूर्णांक geni_icc_enable(काष्ठा geni_se *se);

पूर्णांक geni_icc_disable(काष्ठा geni_se *se);
#पूर्ण_अगर
#पूर्ण_अगर
