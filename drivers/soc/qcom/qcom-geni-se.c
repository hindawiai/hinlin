<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/qcom-geni-se.h>

/**
 * DOC: Overview
 *
 * Generic Interface (GENI) Serial Engine (SE) Wrapper driver is पूर्णांकroduced
 * to manage GENI firmware based Qualcomm Universal Peripheral (QUP) Wrapper
 * controller. QUP Wrapper is deचिन्हित to support various serial bus protocols
 * like UART, SPI, I2C, I3C, etc.
 */

/**
 * DOC: Hardware description
 *
 * GENI based QUP is a highly-flexible and programmable module क्रम supporting
 * a wide range of serial पूर्णांकerfaces like UART, SPI, I2C, I3C, etc. A single
 * QUP module can provide upto 8 serial पूर्णांकerfaces, using its पूर्णांकernal
 * serial engines. The actual configuration is determined by the target
 * platक्रमm configuration. The protocol supported by each पूर्णांकerface is
 * determined by the firmware loaded to the serial engine. Each SE consists
 * of a DMA Engine and GENI sub modules which enable serial engines to
 * support FIFO and DMA modes of operation.
 *
 *
 *                      +-----------------------------------------+
 *                      |QUP Wrapper                              |
 *                      |         +----------------------------+  |
 *   --QUP & SE Clocks-->         | Serial Engine N            |  +-IO------>
 *                      |         | ...                        |  | Interface
 *   <---Clock Perf.----+    +----+-----------------------+    |  |
 *     State Interface  |    | Serial Engine 1            |    |  |
 *                      |    |                            |    |  |
 *                      |    |                            |    |  |
 *   <--------AHB------->    |                            |    |  |
 *                      |    |                            +----+  |
 *                      |    |                            |       |
 *                      |    |                            |       |
 *   <------SE IRQ------+    +----------------------------+       |
 *                      |                                         |
 *                      +-----------------------------------------+
 *
 *                         Figure 1: GENI based QUP Wrapper
 *
 * The GENI submodules include primary and secondary sequencers which are
 * used to drive TX & RX operations. On serial पूर्णांकerfaces that operate using
 * master-slave model, primary sequencer drives both TX & RX operations. On
 * serial पूर्णांकerfaces that operate using peer-to-peer model, primary sequencer
 * drives TX operation and secondary sequencer drives RX operation.
 */

/**
 * DOC: Software description
 *
 * GENI SE Wrapper driver is काष्ठाured पूर्णांकo 2 parts:
 *
 * geni_wrapper represents QUP Wrapper controller. This part of the driver
 * manages QUP Wrapper inक्रमmation such as hardware version, घड़ी
 * perक्रमmance table that is common to all the पूर्णांकernal serial engines.
 *
 * geni_se represents serial engine. This part of the driver manages serial
 * engine inक्रमmation such as घड़ीs, containing QUP Wrapper, etc. This part
 * of driver also supports operations (eg. initialize the concerned serial
 * engine, select between FIFO and DMA mode of operation etc.) that are
 * common to all the serial engines and are independent of serial पूर्णांकerfaces.
 */

#घोषणा MAX_CLK_PERF_LEVEL 32
#घोषणा NUM_AHB_CLKS 2

/**
 * काष्ठा geni_wrapper - Data काष्ठाure to represent the QUP Wrapper Core
 * @dev:		Device poपूर्णांकer of the QUP wrapper core
 * @base:		Base address of this instance of QUP wrapper core
 * @ahb_clks:		Handle to the primary & secondary AHB घड़ीs
 * @to_core:		Core ICC path
 */
काष्ठा geni_wrapper अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा clk_bulk_data ahb_clks[NUM_AHB_CLKS];
पूर्ण;

अटल स्थिर अक्षर * स्थिर icc_path_names[] = अणु"qup-core", "qup-config",
						"qup-memory"पूर्ण;

#घोषणा QUP_HW_VER_REG			0x4

/* Common SE रेजिस्टरs */
#घोषणा GENI_INIT_CFG_REVISION		0x0
#घोषणा GENI_S_INIT_CFG_REVISION	0x4
#घोषणा GENI_OUTPUT_CTRL		0x24
#घोषणा GENI_CGC_CTRL			0x28
#घोषणा GENI_CLK_CTRL_RO		0x60
#घोषणा GENI_IF_DISABLE_RO		0x64
#घोषणा GENI_FW_S_REVISION_RO		0x6c
#घोषणा SE_GENI_BYTE_GRAN		0x254
#घोषणा SE_GENI_TX_PACKING_CFG0		0x260
#घोषणा SE_GENI_TX_PACKING_CFG1		0x264
#घोषणा SE_GENI_RX_PACKING_CFG0		0x284
#घोषणा SE_GENI_RX_PACKING_CFG1		0x288
#घोषणा SE_GENI_M_GP_LENGTH		0x910
#घोषणा SE_GENI_S_GP_LENGTH		0x914
#घोषणा SE_DMA_TX_PTR_L			0xc30
#घोषणा SE_DMA_TX_PTR_H			0xc34
#घोषणा SE_DMA_TX_ATTR			0xc38
#घोषणा SE_DMA_TX_LEN			0xc3c
#घोषणा SE_DMA_TX_IRQ_EN		0xc48
#घोषणा SE_DMA_TX_IRQ_EN_SET		0xc4c
#घोषणा SE_DMA_TX_IRQ_EN_CLR		0xc50
#घोषणा SE_DMA_TX_LEN_IN		0xc54
#घोषणा SE_DMA_TX_MAX_BURST		0xc5c
#घोषणा SE_DMA_RX_PTR_L			0xd30
#घोषणा SE_DMA_RX_PTR_H			0xd34
#घोषणा SE_DMA_RX_ATTR			0xd38
#घोषणा SE_DMA_RX_LEN			0xd3c
#घोषणा SE_DMA_RX_IRQ_EN		0xd48
#घोषणा SE_DMA_RX_IRQ_EN_SET		0xd4c
#घोषणा SE_DMA_RX_IRQ_EN_CLR		0xd50
#घोषणा SE_DMA_RX_LEN_IN		0xd54
#घोषणा SE_DMA_RX_MAX_BURST		0xd5c
#घोषणा SE_DMA_RX_FLUSH			0xd60
#घोषणा SE_GSI_EVENT_EN			0xe18
#घोषणा SE_IRQ_EN			0xe1c
#घोषणा SE_DMA_GENERAL_CFG		0xe30

/* GENI_OUTPUT_CTRL fields */
#घोषणा DEFAULT_IO_OUTPUT_CTRL_MSK	GENMASK(6, 0)

/* GENI_CGC_CTRL fields */
#घोषणा CFG_AHB_CLK_CGC_ON		BIT(0)
#घोषणा CFG_AHB_WR_ACLK_CGC_ON		BIT(1)
#घोषणा DATA_AHB_CLK_CGC_ON		BIT(2)
#घोषणा SCLK_CGC_ON			BIT(3)
#घोषणा TX_CLK_CGC_ON			BIT(4)
#घोषणा RX_CLK_CGC_ON			BIT(5)
#घोषणा EXT_CLK_CGC_ON			BIT(6)
#घोषणा PROG_RAM_HCLK_OFF		BIT(8)
#घोषणा PROG_RAM_SCLK_OFF		BIT(9)
#घोषणा DEFAULT_CGC_EN			GENMASK(6, 0)

/* SE_GSI_EVENT_EN fields */
#घोषणा DMA_RX_EVENT_EN			BIT(0)
#घोषणा DMA_TX_EVENT_EN			BIT(1)
#घोषणा GENI_M_EVENT_EN			BIT(2)
#घोषणा GENI_S_EVENT_EN			BIT(3)

/* SE_IRQ_EN fields */
#घोषणा DMA_RX_IRQ_EN			BIT(0)
#घोषणा DMA_TX_IRQ_EN			BIT(1)
#घोषणा GENI_M_IRQ_EN			BIT(2)
#घोषणा GENI_S_IRQ_EN			BIT(3)

/* SE_DMA_GENERAL_CFG */
#घोषणा DMA_RX_CLK_CGC_ON		BIT(0)
#घोषणा DMA_TX_CLK_CGC_ON		BIT(1)
#घोषणा DMA_AHB_SLV_CFG_ON		BIT(2)
#घोषणा AHB_SEC_SLV_CLK_CGC_ON		BIT(3)
#घोषणा DUMMY_RX_NON_BUFFERABLE		BIT(4)
#घोषणा RX_DMA_ZERO_PADDING_EN		BIT(5)
#घोषणा RX_DMA_IRQ_DELAY_MSK		GENMASK(8, 6)
#घोषणा RX_DMA_IRQ_DELAY_SHFT		6

/**
 * geni_se_get_qup_hw_version() - Read the QUP wrapper Hardware version
 * @se:	Poपूर्णांकer to the corresponding serial engine.
 *
 * Return: Hardware Version of the wrapper.
 */
u32 geni_se_get_qup_hw_version(काष्ठा geni_se *se)
अणु
	काष्ठा geni_wrapper *wrapper = se->wrapper;

	वापस पढ़ोl_relaxed(wrapper->base + QUP_HW_VER_REG);
पूर्ण
EXPORT_SYMBOL(geni_se_get_qup_hw_version);

अटल व्योम geni_se_io_set_mode(व्योम __iomem *base)
अणु
	u32 val;

	val = पढ़ोl_relaxed(base + SE_IRQ_EN);
	val |= GENI_M_IRQ_EN | GENI_S_IRQ_EN;
	val |= DMA_TX_IRQ_EN | DMA_RX_IRQ_EN;
	ग_लिखोl_relaxed(val, base + SE_IRQ_EN);

	val = पढ़ोl_relaxed(base + SE_GENI_DMA_MODE_EN);
	val &= ~GENI_DMA_MODE_EN;
	ग_लिखोl_relaxed(val, base + SE_GENI_DMA_MODE_EN);

	ग_लिखोl_relaxed(0, base + SE_GSI_EVENT_EN);
पूर्ण

अटल व्योम geni_se_io_init(व्योम __iomem *base)
अणु
	u32 val;

	val = पढ़ोl_relaxed(base + GENI_CGC_CTRL);
	val |= DEFAULT_CGC_EN;
	ग_लिखोl_relaxed(val, base + GENI_CGC_CTRL);

	val = पढ़ोl_relaxed(base + SE_DMA_GENERAL_CFG);
	val |= AHB_SEC_SLV_CLK_CGC_ON | DMA_AHB_SLV_CFG_ON;
	val |= DMA_TX_CLK_CGC_ON | DMA_RX_CLK_CGC_ON;
	ग_लिखोl_relaxed(val, base + SE_DMA_GENERAL_CFG);

	ग_लिखोl_relaxed(DEFAULT_IO_OUTPUT_CTRL_MSK, base + GENI_OUTPUT_CTRL);
	ग_लिखोl_relaxed(FORCE_DEFAULT, base + GENI_FORCE_DEFAULT_REG);
पूर्ण

अटल व्योम geni_se_irq_clear(काष्ठा geni_se *se)
अणु
	ग_लिखोl_relaxed(0, se->base + SE_GSI_EVENT_EN);
	ग_लिखोl_relaxed(0xffffffff, se->base + SE_GENI_M_IRQ_CLEAR);
	ग_लिखोl_relaxed(0xffffffff, se->base + SE_GENI_S_IRQ_CLEAR);
	ग_लिखोl_relaxed(0xffffffff, se->base + SE_DMA_TX_IRQ_CLR);
	ग_लिखोl_relaxed(0xffffffff, se->base + SE_DMA_RX_IRQ_CLR);
	ग_लिखोl_relaxed(0xffffffff, se->base + SE_IRQ_EN);
पूर्ण

/**
 * geni_se_init() - Initialize the GENI serial engine
 * @se:		Poपूर्णांकer to the concerned serial engine.
 * @rx_wm:	Receive watermark, in units of FIFO words.
 * @rx_rfr:	Ready-क्रम-receive watermark, in units of FIFO words.
 *
 * This function is used to initialize the GENI serial engine, configure
 * receive watermark and पढ़ोy-क्रम-receive watermarks.
 */
व्योम geni_se_init(काष्ठा geni_se *se, u32 rx_wm, u32 rx_rfr)
अणु
	u32 val;

	geni_se_irq_clear(se);
	geni_se_io_init(se->base);
	geni_se_io_set_mode(se->base);

	ग_लिखोl_relaxed(rx_wm, se->base + SE_GENI_RX_WATERMARK_REG);
	ग_लिखोl_relaxed(rx_rfr, se->base + SE_GENI_RX_RFR_WATERMARK_REG);

	val = पढ़ोl_relaxed(se->base + SE_GENI_M_IRQ_EN);
	val |= M_COMMON_GENI_M_IRQ_EN;
	ग_लिखोl_relaxed(val, se->base + SE_GENI_M_IRQ_EN);

	val = पढ़ोl_relaxed(se->base + SE_GENI_S_IRQ_EN);
	val |= S_COMMON_GENI_S_IRQ_EN;
	ग_लिखोl_relaxed(val, se->base + SE_GENI_S_IRQ_EN);
पूर्ण
EXPORT_SYMBOL(geni_se_init);

अटल व्योम geni_se_select_fअगरo_mode(काष्ठा geni_se *se)
अणु
	u32 proto = geni_se_पढ़ो_proto(se);
	u32 val, val_old;

	geni_se_irq_clear(se);

	/*
	 * The RX path क्रम the UART is asynchronous and so needs more
	 * complex logic क्रम enabling / disabling its पूर्णांकerrupts.
	 *
	 * Specअगरic notes:
	 * - The करोne and TX-related पूर्णांकerrupts are managed manually.
	 * - We करोn't RX from the मुख्य sequencer (we use the secondary) so
	 *   we करोn't need the RX-related पूर्णांकerrupts enabled in the मुख्य
	 *   sequencer क्रम UART.
	 */
	अगर (proto != GENI_SE_UART) अणु
		val_old = val = पढ़ोl_relaxed(se->base + SE_GENI_M_IRQ_EN);
		val |= M_CMD_DONE_EN | M_TX_FIFO_WATERMARK_EN;
		val |= M_RX_FIFO_WATERMARK_EN | M_RX_FIFO_LAST_EN;
		अगर (val != val_old)
			ग_लिखोl_relaxed(val, se->base + SE_GENI_M_IRQ_EN);

		val_old = val = पढ़ोl_relaxed(se->base + SE_GENI_S_IRQ_EN);
		val |= S_CMD_DONE_EN;
		अगर (val != val_old)
			ग_लिखोl_relaxed(val, se->base + SE_GENI_S_IRQ_EN);
	पूर्ण

	val_old = val = पढ़ोl_relaxed(se->base + SE_GENI_DMA_MODE_EN);
	val &= ~GENI_DMA_MODE_EN;
	अगर (val != val_old)
		ग_लिखोl_relaxed(val, se->base + SE_GENI_DMA_MODE_EN);
पूर्ण

अटल व्योम geni_se_select_dma_mode(काष्ठा geni_se *se)
अणु
	u32 proto = geni_se_पढ़ो_proto(se);
	u32 val, val_old;

	geni_se_irq_clear(se);

	अगर (proto != GENI_SE_UART) अणु
		val_old = val = पढ़ोl_relaxed(se->base + SE_GENI_M_IRQ_EN);
		val &= ~(M_CMD_DONE_EN | M_TX_FIFO_WATERMARK_EN);
		val &= ~(M_RX_FIFO_WATERMARK_EN | M_RX_FIFO_LAST_EN);
		अगर (val != val_old)
			ग_लिखोl_relaxed(val, se->base + SE_GENI_M_IRQ_EN);

		val_old = val = पढ़ोl_relaxed(se->base + SE_GENI_S_IRQ_EN);
		val &= ~S_CMD_DONE_EN;
		अगर (val != val_old)
			ग_लिखोl_relaxed(val, se->base + SE_GENI_S_IRQ_EN);
	पूर्ण

	val_old = val = पढ़ोl_relaxed(se->base + SE_GENI_DMA_MODE_EN);
	val |= GENI_DMA_MODE_EN;
	अगर (val != val_old)
		ग_लिखोl_relaxed(val, se->base + SE_GENI_DMA_MODE_EN);
पूर्ण

/**
 * geni_se_select_mode() - Select the serial engine transfer mode
 * @se:		Poपूर्णांकer to the concerned serial engine.
 * @mode:	Transfer mode to be selected.
 */
व्योम geni_se_select_mode(काष्ठा geni_se *se, क्रमागत geni_se_xfer_mode mode)
अणु
	WARN_ON(mode != GENI_SE_FIFO && mode != GENI_SE_DMA);

	चयन (mode) अणु
	हाल GENI_SE_FIFO:
		geni_se_select_fअगरo_mode(se);
		अवरोध;
	हाल GENI_SE_DMA:
		geni_se_select_dma_mode(se);
		अवरोध;
	हाल GENI_SE_INVALID:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(geni_se_select_mode);

/**
 * DOC: Overview
 *
 * GENI FIFO packing is highly configurable. TX/RX packing/unpacking consist
 * of up to 4 operations, each operation represented by 4 configuration vectors
 * of 10 bits programmed in GENI_TX_PACKING_CFG0 and GENI_TX_PACKING_CFG1 क्रम
 * TX FIFO and in GENI_RX_PACKING_CFG0 and GENI_RX_PACKING_CFG1 क्रम RX FIFO.
 * Refer to below examples क्रम detailed bit-field description.
 *
 * Example 1: word_size = 7, packing_mode = 4 x 8, msb_to_lsb = 1
 *
 *        +-----------+-------+-------+-------+-------+
 *        |           | vec_0 | vec_1 | vec_2 | vec_3 |
 *        +-----------+-------+-------+-------+-------+
 *        | start     | 0x6   | 0xe   | 0x16  | 0x1e  |
 *        | direction | 1     | 1     | 1     | 1     |
 *        | length    | 6     | 6     | 6     | 6     |
 *        | stop      | 0     | 0     | 0     | 1     |
 *        +-----------+-------+-------+-------+-------+
 *
 * Example 2: word_size = 15, packing_mode = 2 x 16, msb_to_lsb = 0
 *
 *        +-----------+-------+-------+-------+-------+
 *        |           | vec_0 | vec_1 | vec_2 | vec_3 |
 *        +-----------+-------+-------+-------+-------+
 *        | start     | 0x0   | 0x8   | 0x10  | 0x18  |
 *        | direction | 0     | 0     | 0     | 0     |
 *        | length    | 7     | 6     | 7     | 6     |
 *        | stop      | 0     | 0     | 0     | 1     |
 *        +-----------+-------+-------+-------+-------+
 *
 * Example 3: word_size = 23, packing_mode = 1 x 32, msb_to_lsb = 1
 *
 *        +-----------+-------+-------+-------+-------+
 *        |           | vec_0 | vec_1 | vec_2 | vec_3 |
 *        +-----------+-------+-------+-------+-------+
 *        | start     | 0x16  | 0xe   | 0x6   | 0x0   |
 *        | direction | 1     | 1     | 1     | 1     |
 *        | length    | 7     | 7     | 6     | 0     |
 *        | stop      | 0     | 0     | 1     | 0     |
 *        +-----------+-------+-------+-------+-------+
 *
 */

#घोषणा NUM_PACKING_VECTORS 4
#घोषणा PACKING_START_SHIFT 5
#घोषणा PACKING_सूची_SHIFT 4
#घोषणा PACKING_LEN_SHIFT 1
#घोषणा PACKING_STOP_BIT BIT(0)
#घोषणा PACKING_VECTOR_SHIFT 10
/**
 * geni_se_config_packing() - Packing configuration of the serial engine
 * @se:		Poपूर्णांकer to the concerned serial engine
 * @bpw:	Bits of data per transfer word.
 * @pack_words:	Number of words per fअगरo element.
 * @msb_to_lsb:	Transfer from MSB to LSB or vice-versa.
 * @tx_cfg:	Flag to configure the TX Packing.
 * @rx_cfg:	Flag to configure the RX Packing.
 *
 * This function is used to configure the packing rules क्रम the current
 * transfer.
 */
व्योम geni_se_config_packing(काष्ठा geni_se *se, पूर्णांक bpw, पूर्णांक pack_words,
			    bool msb_to_lsb, bool tx_cfg, bool rx_cfg)
अणु
	u32 cfg0, cfg1, cfg[NUM_PACKING_VECTORS] = अणु0पूर्ण;
	पूर्णांक len;
	पूर्णांक temp_bpw = bpw;
	पूर्णांक idx_start = msb_to_lsb ? bpw - 1 : 0;
	पूर्णांक idx = idx_start;
	पूर्णांक idx_delta = msb_to_lsb ? -BITS_PER_BYTE : BITS_PER_BYTE;
	पूर्णांक उच्चमान_bpw = ALIGN(bpw, BITS_PER_BYTE);
	पूर्णांक iter = (उच्चमान_bpw * pack_words) / BITS_PER_BYTE;
	पूर्णांक i;

	अगर (iter <= 0 || iter > NUM_PACKING_VECTORS)
		वापस;

	क्रम (i = 0; i < iter; i++) अणु
		len = min_t(पूर्णांक, temp_bpw, BITS_PER_BYTE) - 1;
		cfg[i] = idx << PACKING_START_SHIFT;
		cfg[i] |= msb_to_lsb << PACKING_सूची_SHIFT;
		cfg[i] |= len << PACKING_LEN_SHIFT;

		अगर (temp_bpw <= BITS_PER_BYTE) अणु
			idx = ((i + 1) * BITS_PER_BYTE) + idx_start;
			temp_bpw = bpw;
		पूर्ण अन्यथा अणु
			idx = idx + idx_delta;
			temp_bpw = temp_bpw - BITS_PER_BYTE;
		पूर्ण
	पूर्ण
	cfg[iter - 1] |= PACKING_STOP_BIT;
	cfg0 = cfg[0] | (cfg[1] << PACKING_VECTOR_SHIFT);
	cfg1 = cfg[2] | (cfg[3] << PACKING_VECTOR_SHIFT);

	अगर (tx_cfg) अणु
		ग_लिखोl_relaxed(cfg0, se->base + SE_GENI_TX_PACKING_CFG0);
		ग_लिखोl_relaxed(cfg1, se->base + SE_GENI_TX_PACKING_CFG1);
	पूर्ण
	अगर (rx_cfg) अणु
		ग_लिखोl_relaxed(cfg0, se->base + SE_GENI_RX_PACKING_CFG0);
		ग_लिखोl_relaxed(cfg1, se->base + SE_GENI_RX_PACKING_CFG1);
	पूर्ण

	/*
	 * Number of protocol words in each FIFO entry
	 * 0 - 4x8, four words in each entry, max word size of 8 bits
	 * 1 - 2x16, two words in each entry, max word size of 16 bits
	 * 2 - 1x32, one word in each entry, max word size of 32 bits
	 * 3 - undefined
	 */
	अगर (pack_words || bpw == 32)
		ग_लिखोl_relaxed(bpw / 16, se->base + SE_GENI_BYTE_GRAN);
पूर्ण
EXPORT_SYMBOL(geni_se_config_packing);

अटल व्योम geni_se_clks_off(काष्ठा geni_se *se)
अणु
	काष्ठा geni_wrapper *wrapper = se->wrapper;

	clk_disable_unprepare(se->clk);
	clk_bulk_disable_unprepare(ARRAY_SIZE(wrapper->ahb_clks),
						wrapper->ahb_clks);
पूर्ण

/**
 * geni_se_resources_off() - Turn off resources associated with the serial
 *                           engine
 * @se:	Poपूर्णांकer to the concerned serial engine.
 *
 * Return: 0 on success, standard Linux error codes on failure/error.
 */
पूर्णांक geni_se_resources_off(काष्ठा geni_se *se)
अणु
	पूर्णांक ret;

	अगर (has_acpi_companion(se->dev))
		वापस 0;

	ret = pinctrl_pm_select_sleep_state(se->dev);
	अगर (ret)
		वापस ret;

	geni_se_clks_off(se);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(geni_se_resources_off);

अटल पूर्णांक geni_se_clks_on(काष्ठा geni_se *se)
अणु
	पूर्णांक ret;
	काष्ठा geni_wrapper *wrapper = se->wrapper;

	ret = clk_bulk_prepare_enable(ARRAY_SIZE(wrapper->ahb_clks),
						wrapper->ahb_clks);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(se->clk);
	अगर (ret)
		clk_bulk_disable_unprepare(ARRAY_SIZE(wrapper->ahb_clks),
							wrapper->ahb_clks);
	वापस ret;
पूर्ण

/**
 * geni_se_resources_on() - Turn on resources associated with the serial
 *                          engine
 * @se:	Poपूर्णांकer to the concerned serial engine.
 *
 * Return: 0 on success, standard Linux error codes on failure/error.
 */
पूर्णांक geni_se_resources_on(काष्ठा geni_se *se)
अणु
	पूर्णांक ret;

	अगर (has_acpi_companion(se->dev))
		वापस 0;

	ret = geni_se_clks_on(se);
	अगर (ret)
		वापस ret;

	ret = pinctrl_pm_select_शेष_state(se->dev);
	अगर (ret)
		geni_se_clks_off(se);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(geni_se_resources_on);

/**
 * geni_se_clk_tbl_get() - Get the घड़ी table to program DFS
 * @se:		Poपूर्णांकer to the concerned serial engine.
 * @tbl:	Table in which the output is वापसed.
 *
 * This function is called by the protocol drivers to determine the dअगरferent
 * घड़ी frequencies supported by serial engine core घड़ी. The protocol
 * drivers use the output to determine the घड़ी frequency index to be
 * programmed पूर्णांकo DFS.
 *
 * Return: number of valid perक्रमmance levels in the table on success,
 *	   standard Linux error codes on failure.
 */
पूर्णांक geni_se_clk_tbl_get(काष्ठा geni_se *se, अचिन्हित दीर्घ **tbl)
अणु
	दीर्घ freq = 0;
	पूर्णांक i;

	अगर (se->clk_perf_tbl) अणु
		*tbl = se->clk_perf_tbl;
		वापस se->num_clk_levels;
	पूर्ण

	se->clk_perf_tbl = devm_kसुस्मृति(se->dev, MAX_CLK_PERF_LEVEL,
					माप(*se->clk_perf_tbl),
					GFP_KERNEL);
	अगर (!se->clk_perf_tbl)
		वापस -ENOMEM;

	क्रम (i = 0; i < MAX_CLK_PERF_LEVEL; i++) अणु
		freq = clk_round_rate(se->clk, freq + 1);
		अगर (freq <= 0 || freq == se->clk_perf_tbl[i - 1])
			अवरोध;
		se->clk_perf_tbl[i] = freq;
	पूर्ण
	se->num_clk_levels = i;
	*tbl = se->clk_perf_tbl;
	वापस se->num_clk_levels;
पूर्ण
EXPORT_SYMBOL(geni_se_clk_tbl_get);

/**
 * geni_se_clk_freq_match() - Get the matching or बंदst SE घड़ी frequency
 * @se:		Poपूर्णांकer to the concerned serial engine.
 * @req_freq:	Requested घड़ी frequency.
 * @index:	Index of the resultant frequency in the table.
 * @res_freq:	Resultant frequency of the source घड़ी.
 * @exact:	Flag to indicate exact multiple requirement of the requested
 *		frequency.
 *
 * This function is called by the protocol drivers to determine the best match
 * of the requested frequency as provided by the serial engine घड़ी in order
 * to meet the perक्रमmance requirements.
 *
 * If we वापस success:
 * - अगर @exact is true  then @res_freq / <an_पूर्णांकeger> == @req_freq
 * - अगर @exact is false then @res_freq / <an_पूर्णांकeger> <= @req_freq
 *
 * Return: 0 on success, standard Linux error codes on failure.
 */
पूर्णांक geni_se_clk_freq_match(काष्ठा geni_se *se, अचिन्हित दीर्घ req_freq,
			   अचिन्हित पूर्णांक *index, अचिन्हित दीर्घ *res_freq,
			   bool exact)
अणु
	अचिन्हित दीर्घ *tbl;
	पूर्णांक num_clk_levels;
	पूर्णांक i;
	अचिन्हित दीर्घ best_delta;
	अचिन्हित दीर्घ new_delta;
	अचिन्हित पूर्णांक भागider;

	num_clk_levels = geni_se_clk_tbl_get(se, &tbl);
	अगर (num_clk_levels < 0)
		वापस num_clk_levels;

	अगर (num_clk_levels == 0)
		वापस -EINVAL;

	best_delta = अच_दीर्घ_उच्च;
	क्रम (i = 0; i < num_clk_levels; i++) अणु
		भागider = DIV_ROUND_UP(tbl[i], req_freq);
		new_delta = req_freq - tbl[i] / भागider;
		अगर (new_delta < best_delta) अणु
			/* We have a new best! */
			*index = i;
			*res_freq = tbl[i];

			/* If the new best is exact then we're करोne */
			अगर (new_delta == 0)
				वापस 0;

			/* Record how बंद we got */
			best_delta = new_delta;
		पूर्ण
	पूर्ण

	अगर (exact)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(geni_se_clk_freq_match);

#घोषणा GENI_SE_DMA_DONE_EN BIT(0)
#घोषणा GENI_SE_DMA_EOT_EN BIT(1)
#घोषणा GENI_SE_DMA_AHB_ERR_EN BIT(2)
#घोषणा GENI_SE_DMA_EOT_BUF BIT(0)
/**
 * geni_se_tx_dma_prep() - Prepare the serial engine क्रम TX DMA transfer
 * @se:			Poपूर्णांकer to the concerned serial engine.
 * @buf:		Poपूर्णांकer to the TX buffer.
 * @len:		Length of the TX buffer.
 * @iova:		Poपूर्णांकer to store the mapped DMA address.
 *
 * This function is used to prepare the buffers क्रम DMA TX.
 *
 * Return: 0 on success, standard Linux error codes on failure.
 */
पूर्णांक geni_se_tx_dma_prep(काष्ठा geni_se *se, व्योम *buf, माप_प्रकार len,
			dma_addr_t *iova)
अणु
	काष्ठा geni_wrapper *wrapper = se->wrapper;
	u32 val;

	अगर (!wrapper)
		वापस -EINVAL;

	*iova = dma_map_single(wrapper->dev, buf, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(wrapper->dev, *iova))
		वापस -EIO;

	val = GENI_SE_DMA_DONE_EN;
	val |= GENI_SE_DMA_EOT_EN;
	val |= GENI_SE_DMA_AHB_ERR_EN;
	ग_लिखोl_relaxed(val, se->base + SE_DMA_TX_IRQ_EN_SET);
	ग_लिखोl_relaxed(lower_32_bits(*iova), se->base + SE_DMA_TX_PTR_L);
	ग_लिखोl_relaxed(upper_32_bits(*iova), se->base + SE_DMA_TX_PTR_H);
	ग_लिखोl_relaxed(GENI_SE_DMA_EOT_BUF, se->base + SE_DMA_TX_ATTR);
	ग_लिखोl(len, se->base + SE_DMA_TX_LEN);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(geni_se_tx_dma_prep);

/**
 * geni_se_rx_dma_prep() - Prepare the serial engine क्रम RX DMA transfer
 * @se:			Poपूर्णांकer to the concerned serial engine.
 * @buf:		Poपूर्णांकer to the RX buffer.
 * @len:		Length of the RX buffer.
 * @iova:		Poपूर्णांकer to store the mapped DMA address.
 *
 * This function is used to prepare the buffers क्रम DMA RX.
 *
 * Return: 0 on success, standard Linux error codes on failure.
 */
पूर्णांक geni_se_rx_dma_prep(काष्ठा geni_se *se, व्योम *buf, माप_प्रकार len,
			dma_addr_t *iova)
अणु
	काष्ठा geni_wrapper *wrapper = se->wrapper;
	u32 val;

	अगर (!wrapper)
		वापस -EINVAL;

	*iova = dma_map_single(wrapper->dev, buf, len, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(wrapper->dev, *iova))
		वापस -EIO;

	val = GENI_SE_DMA_DONE_EN;
	val |= GENI_SE_DMA_EOT_EN;
	val |= GENI_SE_DMA_AHB_ERR_EN;
	ग_लिखोl_relaxed(val, se->base + SE_DMA_RX_IRQ_EN_SET);
	ग_लिखोl_relaxed(lower_32_bits(*iova), se->base + SE_DMA_RX_PTR_L);
	ग_लिखोl_relaxed(upper_32_bits(*iova), se->base + SE_DMA_RX_PTR_H);
	/* RX करोes not have EOT buffer type bit. So just reset RX_ATTR */
	ग_लिखोl_relaxed(0, se->base + SE_DMA_RX_ATTR);
	ग_लिखोl(len, se->base + SE_DMA_RX_LEN);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(geni_se_rx_dma_prep);

/**
 * geni_se_tx_dma_unprep() - Unprepare the serial engine after TX DMA transfer
 * @se:			Poपूर्णांकer to the concerned serial engine.
 * @iova:		DMA address of the TX buffer.
 * @len:		Length of the TX buffer.
 *
 * This function is used to unprepare the DMA buffers after DMA TX.
 */
व्योम geni_se_tx_dma_unprep(काष्ठा geni_se *se, dma_addr_t iova, माप_प्रकार len)
अणु
	काष्ठा geni_wrapper *wrapper = se->wrapper;

	अगर (!dma_mapping_error(wrapper->dev, iova))
		dma_unmap_single(wrapper->dev, iova, len, DMA_TO_DEVICE);
पूर्ण
EXPORT_SYMBOL(geni_se_tx_dma_unprep);

/**
 * geni_se_rx_dma_unprep() - Unprepare the serial engine after RX DMA transfer
 * @se:			Poपूर्णांकer to the concerned serial engine.
 * @iova:		DMA address of the RX buffer.
 * @len:		Length of the RX buffer.
 *
 * This function is used to unprepare the DMA buffers after DMA RX.
 */
व्योम geni_se_rx_dma_unprep(काष्ठा geni_se *se, dma_addr_t iova, माप_प्रकार len)
अणु
	काष्ठा geni_wrapper *wrapper = se->wrapper;

	अगर (!dma_mapping_error(wrapper->dev, iova))
		dma_unmap_single(wrapper->dev, iova, len, DMA_FROM_DEVICE);
पूर्ण
EXPORT_SYMBOL(geni_se_rx_dma_unprep);

पूर्णांक geni_icc_get(काष्ठा geni_se *se, स्थिर अक्षर *icc_ddr)
अणु
	पूर्णांक i, err;
	स्थिर अक्षर *icc_names[] = अणु"qup-core", "qup-config", icc_ddrपूर्ण;

	अगर (has_acpi_companion(se->dev))
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(se->icc_paths); i++) अणु
		अगर (!icc_names[i])
			जारी;

		se->icc_paths[i].path = devm_of_icc_get(se->dev, icc_names[i]);
		अगर (IS_ERR(se->icc_paths[i].path))
			जाओ err;
	पूर्ण

	वापस 0;

err:
	err = PTR_ERR(se->icc_paths[i].path);
	अगर (err != -EPROBE_DEFER)
		dev_err_ratelimited(se->dev, "Failed to get ICC path '%s': %d\n",
					icc_names[i], err);
	वापस err;

पूर्ण
EXPORT_SYMBOL(geni_icc_get);

पूर्णांक geni_icc_set_bw(काष्ठा geni_se *se)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(se->icc_paths); i++) अणु
		ret = icc_set_bw(se->icc_paths[i].path,
			se->icc_paths[i].avg_bw, se->icc_paths[i].avg_bw);
		अगर (ret) अणु
			dev_err_ratelimited(se->dev, "ICC BW voting failed on path '%s': %d\n",
					icc_path_names[i], ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(geni_icc_set_bw);

व्योम geni_icc_set_tag(काष्ठा geni_se *se, u32 tag)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(se->icc_paths); i++)
		icc_set_tag(se->icc_paths[i].path, tag);
पूर्ण
EXPORT_SYMBOL(geni_icc_set_tag);

/* To करो: Replace this by icc_bulk_enable once it's implemented in ICC core */
पूर्णांक geni_icc_enable(काष्ठा geni_se *se)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(se->icc_paths); i++) अणु
		ret = icc_enable(se->icc_paths[i].path);
		अगर (ret) अणु
			dev_err_ratelimited(se->dev, "ICC enable failed on path '%s': %d\n",
					icc_path_names[i], ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(geni_icc_enable);

पूर्णांक geni_icc_disable(काष्ठा geni_se *se)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(se->icc_paths); i++) अणु
		ret = icc_disable(se->icc_paths[i].path);
		अगर (ret) अणु
			dev_err_ratelimited(se->dev, "ICC disable failed on path '%s': %d\n",
					icc_path_names[i], ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(geni_icc_disable);

अटल पूर्णांक geni_se_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा geni_wrapper *wrapper;
	पूर्णांक ret;

	wrapper = devm_kzalloc(dev, माप(*wrapper), GFP_KERNEL);
	अगर (!wrapper)
		वापस -ENOMEM;

	wrapper->dev = dev;
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	wrapper->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(wrapper->base))
		वापस PTR_ERR(wrapper->base);

	अगर (!has_acpi_companion(&pdev->dev)) अणु
		wrapper->ahb_clks[0].id = "m-ahb";
		wrapper->ahb_clks[1].id = "s-ahb";
		ret = devm_clk_bulk_get(dev, NUM_AHB_CLKS, wrapper->ahb_clks);
		अगर (ret) अणु
			dev_err(dev, "Err getting AHB clks %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	dev_set_drvdata(dev, wrapper);
	dev_dbg(dev, "GENI SE Driver probed\n");
	वापस devm_of_platक्रमm_populate(dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id geni_se_dt_match[] = अणु
	अणु .compatible = "qcom,geni-se-qup", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, geni_se_dt_match);

अटल काष्ठा platक्रमm_driver geni_se_driver = अणु
	.driver = अणु
		.name = "geni_se_qup",
		.of_match_table = geni_se_dt_match,
	पूर्ण,
	.probe = geni_se_probe,
पूर्ण;
module_platक्रमm_driver(geni_se_driver);

MODULE_DESCRIPTION("GENI Serial Engine Driver");
MODULE_LICENSE("GPL v2");
