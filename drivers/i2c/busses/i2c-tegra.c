<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/i2c/busses/i2c-tegra.c
 *
 * Copyright (C) 2010 Google, Inc.
 * Author: Colin Cross <ccross@android.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#घोषणा BYTES_PER_FIFO_WORD 4

#घोषणा I2C_CNFG				0x000
#घोषणा I2C_CNFG_DEBOUNCE_CNT			GENMASK(14, 12)
#घोषणा I2C_CNFG_PACKET_MODE_EN			BIT(10)
#घोषणा I2C_CNFG_NEW_MASTER_FSM			BIT(11)
#घोषणा I2C_CNFG_MULTI_MASTER_MODE		BIT(17)
#घोषणा I2C_STATUS				0x01c
#घोषणा I2C_SL_CNFG				0x020
#घोषणा I2C_SL_CNFG_NACK			BIT(1)
#घोषणा I2C_SL_CNFG_NEWSL			BIT(2)
#घोषणा I2C_SL_ADDR1				0x02c
#घोषणा I2C_SL_ADDR2				0x030
#घोषणा I2C_TLOW_SEXT				0x034
#घोषणा I2C_TX_FIFO				0x050
#घोषणा I2C_RX_FIFO				0x054
#घोषणा I2C_PACKET_TRANSFER_STATUS		0x058
#घोषणा I2C_FIFO_CONTROL			0x05c
#घोषणा I2C_FIFO_CONTROL_TX_FLUSH		BIT(1)
#घोषणा I2C_FIFO_CONTROL_RX_FLUSH		BIT(0)
#घोषणा I2C_FIFO_CONTROL_TX_TRIG(x)		(((x) - 1) << 5)
#घोषणा I2C_FIFO_CONTROL_RX_TRIG(x)		(((x) - 1) << 2)
#घोषणा I2C_FIFO_STATUS				0x060
#घोषणा I2C_FIFO_STATUS_TX			GENMASK(7, 4)
#घोषणा I2C_FIFO_STATUS_RX			GENMASK(3, 0)
#घोषणा I2C_INT_MASK				0x064
#घोषणा I2C_INT_STATUS				0x068
#घोषणा I2C_INT_BUS_CLR_DONE			BIT(11)
#घोषणा I2C_INT_PACKET_XFER_COMPLETE		BIT(7)
#घोषणा I2C_INT_NO_ACK				BIT(3)
#घोषणा I2C_INT_ARBITRATION_LOST		BIT(2)
#घोषणा I2C_INT_TX_FIFO_DATA_REQ		BIT(1)
#घोषणा I2C_INT_RX_FIFO_DATA_REQ		BIT(0)
#घोषणा I2C_CLK_DIVISOR				0x06c
#घोषणा I2C_CLK_DIVISOR_STD_FAST_MODE		GENMASK(31, 16)
#घोषणा I2C_CLK_DIVISOR_HSMODE			GENMASK(15, 0)

#घोषणा DVC_CTRL_REG1				0x000
#घोषणा DVC_CTRL_REG1_INTR_EN			BIT(10)
#घोषणा DVC_CTRL_REG3				0x008
#घोषणा DVC_CTRL_REG3_SW_PROG			BIT(26)
#घोषणा DVC_CTRL_REG3_I2C_DONE_INTR_EN		BIT(30)
#घोषणा DVC_STATUS				0x00c
#घोषणा DVC_STATUS_I2C_DONE_INTR		BIT(30)

#घोषणा I2C_ERR_NONE				0x00
#घोषणा I2C_ERR_NO_ACK				BIT(0)
#घोषणा I2C_ERR_ARBITRATION_LOST		BIT(1)
#घोषणा I2C_ERR_UNKNOWN_INTERRUPT		BIT(2)
#घोषणा I2C_ERR_RX_BUFFER_OVERFLOW		BIT(3)

#घोषणा PACKET_HEADER0_HEADER_SIZE		GENMASK(29, 28)
#घोषणा PACKET_HEADER0_PACKET_ID		GENMASK(23, 16)
#घोषणा PACKET_HEADER0_CONT_ID			GENMASK(15, 12)
#घोषणा PACKET_HEADER0_PROTOCOL			GENMASK(7, 4)
#घोषणा PACKET_HEADER0_PROTOCOL_I2C		1

#घोषणा I2C_HEADER_CONT_ON_NAK			BIT(21)
#घोषणा I2C_HEADER_READ				BIT(19)
#घोषणा I2C_HEADER_10BIT_ADDR			BIT(18)
#घोषणा I2C_HEADER_IE_ENABLE			BIT(17)
#घोषणा I2C_HEADER_REPEAT_START			BIT(16)
#घोषणा I2C_HEADER_CONTINUE_XFER		BIT(15)
#घोषणा I2C_HEADER_SLAVE_ADDR_SHIFT		1

#घोषणा I2C_BUS_CLEAR_CNFG			0x084
#घोषणा I2C_BC_SCLK_THRESHOLD			GENMASK(23, 16)
#घोषणा I2C_BC_STOP_COND			BIT(2)
#घोषणा I2C_BC_TERMINATE			BIT(1)
#घोषणा I2C_BC_ENABLE				BIT(0)
#घोषणा I2C_BUS_CLEAR_STATUS			0x088
#घोषणा I2C_BC_STATUS				BIT(0)

#घोषणा I2C_CONFIG_LOAD				0x08c
#घोषणा I2C_MSTR_CONFIG_LOAD			BIT(0)

#घोषणा I2C_CLKEN_OVERRIDE			0x090
#घोषणा I2C_MST_CORE_CLKEN_OVR			BIT(0)

#घोषणा I2C_INTERFACE_TIMING_0			0x094
#घोषणा  I2C_INTERFACE_TIMING_THIGH		GENMASK(13, 8)
#घोषणा  I2C_INTERFACE_TIMING_TLOW		GENMASK(5, 0)
#घोषणा I2C_INTERFACE_TIMING_1			0x098
#घोषणा  I2C_INTERFACE_TIMING_TBUF		GENMASK(29, 24)
#घोषणा  I2C_INTERFACE_TIMING_TSU_STO		GENMASK(21, 16)
#घोषणा  I2C_INTERFACE_TIMING_THD_STA		GENMASK(13, 8)
#घोषणा  I2C_INTERFACE_TIMING_TSU_STA		GENMASK(5, 0)

#घोषणा I2C_HS_INTERFACE_TIMING_0		0x09c
#घोषणा  I2C_HS_INTERFACE_TIMING_THIGH		GENMASK(13, 8)
#घोषणा  I2C_HS_INTERFACE_TIMING_TLOW		GENMASK(5, 0)
#घोषणा I2C_HS_INTERFACE_TIMING_1		0x0a0
#घोषणा  I2C_HS_INTERFACE_TIMING_TSU_STO	GENMASK(21, 16)
#घोषणा  I2C_HS_INTERFACE_TIMING_THD_STA	GENMASK(13, 8)
#घोषणा  I2C_HS_INTERFACE_TIMING_TSU_STA	GENMASK(5, 0)

#घोषणा I2C_MST_FIFO_CONTROL			0x0b4
#घोषणा I2C_MST_FIFO_CONTROL_RX_FLUSH		BIT(0)
#घोषणा I2C_MST_FIFO_CONTROL_TX_FLUSH		BIT(1)
#घोषणा I2C_MST_FIFO_CONTROL_RX_TRIG(x)		(((x) - 1) <<  4)
#घोषणा I2C_MST_FIFO_CONTROL_TX_TRIG(x)		(((x) - 1) << 16)

#घोषणा I2C_MST_FIFO_STATUS			0x0b8
#घोषणा I2C_MST_FIFO_STATUS_TX			GENMASK(23, 16)
#घोषणा I2C_MST_FIFO_STATUS_RX			GENMASK(7, 0)

/* configuration load समयout in microseconds */
#घोषणा I2C_CONFIG_LOAD_TIMEOUT			1000000

/* packet header size in bytes */
#घोषणा I2C_PACKET_HEADER_SIZE			12

/*
 * I2C Controller will use PIO mode क्रम transfers up to 32 bytes in order to
 * aव्योम DMA overhead, otherwise बाह्यal APB DMA controller will be used.
 * Note that the actual MAX PIO length is 20 bytes because 32 bytes include
 * I2C_PACKET_HEADER_SIZE.
 */
#घोषणा I2C_PIO_MODE_PREFERRED_LEN		32

/*
 * msg_end_type: The bus control which needs to be sent at end of transfer.
 * @MSG_END_STOP: Send stop pulse.
 * @MSG_END_REPEAT_START: Send repeat-start.
 * @MSG_END_CONTINUE: Don't send stop or repeat-start.
 */
क्रमागत msg_end_type अणु
	MSG_END_STOP,
	MSG_END_REPEAT_START,
	MSG_END_CONTINUE,
पूर्ण;

/**
 * काष्ठा tegra_i2c_hw_feature : per hardware generation features
 * @has_जारी_xfer_support: जारी-transfer supported
 * @has_per_pkt_xfer_complete_irq: Has enable/disable capability क्रम transfer
 *		completion पूर्णांकerrupt on per packet basis.
 * @has_config_load_reg: Has the config load रेजिस्टर to load the new
 *		configuration.
 * @clk_भागisor_hs_mode: Clock भागisor in HS mode.
 * @clk_भागisor_std_mode: Clock भागisor in standard mode. It is
 *		applicable अगर there is no fast घड़ी source i.e. single घड़ी
 *		source.
 * @clk_भागisor_fast_mode: Clock भागisor in fast mode. It is
 *		applicable अगर there is no fast घड़ी source i.e. single घड़ी
 *		source.
 * @clk_भागisor_fast_plus_mode: Clock भागisor in fast mode plus. It is
 *		applicable अगर there is no fast घड़ी source (i.e. single
 *		घड़ी source).
 * @has_multi_master_mode: The I2C controller supports running in single-master
 *		or multi-master mode.
 * @has_slcg_override_reg: The I2C controller supports a रेजिस्टर that
 *		overrides the second level घड़ी gating.
 * @has_mst_fअगरo: The I2C controller contains the new MST FIFO पूर्णांकerface that
 *		provides additional features and allows क्रम दीर्घer messages to
 *		be transferred in one go.
 * @quirks: I2C adapter quirks क्रम limiting ग_लिखो/पढ़ो transfer size and not
 *		allowing 0 length transfers.
 * @supports_bus_clear: Bus Clear support to recover from bus hang during
 *		SDA stuck low from device क्रम some unknown reasons.
 * @has_apb_dma: Support of APBDMA on corresponding Tegra chip.
 * @tlow_std_mode: Low period of the घड़ी in standard mode.
 * @thigh_std_mode: High period of the घड़ी in standard mode.
 * @tlow_fast_fastplus_mode: Low period of the घड़ी in fast/fast-plus modes.
 * @thigh_fast_fastplus_mode: High period of the घड़ी in fast/fast-plus modes.
 * @setup_hold_समय_std_mode: Setup and hold समय क्रम start and stop conditions
 *		in standard mode.
 * @setup_hold_समय_fast_fast_plus_mode: Setup and hold समय क्रम start and stop
 *		conditions in fast/fast-plus modes.
 * @setup_hold_समय_hs_mode: Setup and hold समय क्रम start and stop conditions
 *		in HS mode.
 * @has_पूर्णांकerface_timing_reg: Has पूर्णांकerface timing रेजिस्टर to program the tuned
 *		timing settings.
 */
काष्ठा tegra_i2c_hw_feature अणु
	bool has_जारी_xfer_support;
	bool has_per_pkt_xfer_complete_irq;
	bool has_config_load_reg;
	u32 clk_भागisor_hs_mode;
	u32 clk_भागisor_std_mode;
	u32 clk_भागisor_fast_mode;
	u32 clk_भागisor_fast_plus_mode;
	bool has_multi_master_mode;
	bool has_slcg_override_reg;
	bool has_mst_fअगरo;
	स्थिर काष्ठा i2c_adapter_quirks *quirks;
	bool supports_bus_clear;
	bool has_apb_dma;
	u32 tlow_std_mode;
	u32 thigh_std_mode;
	u32 tlow_fast_fastplus_mode;
	u32 thigh_fast_fastplus_mode;
	u32 setup_hold_समय_std_mode;
	u32 setup_hold_समय_fast_fast_plus_mode;
	u32 setup_hold_समय_hs_mode;
	bool has_पूर्णांकerface_timing_reg;
पूर्ण;

/**
 * काष्ठा tegra_i2c_dev - per device I2C context
 * @dev: device reference क्रम घातer management
 * @hw: Tegra I2C HW feature
 * @adapter: core I2C layer adapter inक्रमmation
 * @भाग_clk: घड़ी reference क्रम भाग घड़ी of I2C controller
 * @घड़ीs: array of I2C controller घड़ीs
 * @nघड़ीs: number of घड़ीs in the array
 * @rst: reset control क्रम the I2C controller
 * @base: ioremapped रेजिस्टरs cookie
 * @base_phys: physical base address of the I2C controller
 * @cont_id: I2C controller ID, used क्रम packet header
 * @irq: IRQ number of transfer complete पूर्णांकerrupt
 * @is_dvc: identअगरies the DVC I2C controller, has a dअगरferent रेजिस्टर layout
 * @is_vi: identअगरies the VI I2C controller, has a dअगरferent रेजिस्टर layout
 * @msg_complete: transfer completion notअगरier
 * @msg_err: error code क्रम completed message
 * @msg_buf: poपूर्णांकer to current message data
 * @msg_buf_reमुख्यing: size of unsent data in the message buffer
 * @msg_पढ़ो: indicates that the transfer is a पढ़ो access
 * @bus_clk_rate: current I2C bus घड़ी rate
 * @multimaster_mode: indicates that I2C controller is in multi-master mode
 * @tx_dma_chan: DMA transmit channel
 * @rx_dma_chan: DMA receive channel
 * @dma_phys: handle to DMA resources
 * @dma_buf: poपूर्णांकer to allocated DMA buffer
 * @dma_buf_size: DMA buffer size
 * @dma_mode: indicates active DMA transfer
 * @dma_complete: DMA completion notअगरier
 * @atomic_mode: indicates active atomic transfer
 */
काष्ठा tegra_i2c_dev अणु
	काष्ठा device *dev;
	काष्ठा i2c_adapter adapter;

	स्थिर काष्ठा tegra_i2c_hw_feature *hw;
	काष्ठा reset_control *rst;
	अचिन्हित पूर्णांक cont_id;
	अचिन्हित पूर्णांक irq;

	phys_addr_t base_phys;
	व्योम __iomem *base;

	काष्ठा clk_bulk_data घड़ीs[2];
	अचिन्हित पूर्णांक nघड़ीs;

	काष्ठा clk *भाग_clk;
	u32 bus_clk_rate;

	काष्ठा completion msg_complete;
	माप_प्रकार msg_buf_reमुख्यing;
	पूर्णांक msg_err;
	u8 *msg_buf;

	काष्ठा completion dma_complete;
	काष्ठा dma_chan *tx_dma_chan;
	काष्ठा dma_chan *rx_dma_chan;
	अचिन्हित पूर्णांक dma_buf_size;
	dma_addr_t dma_phys;
	व्योम *dma_buf;

	bool multimaster_mode;
	bool atomic_mode;
	bool dma_mode;
	bool msg_पढ़ो;
	bool is_dvc;
	bool is_vi;
पूर्ण;

अटल व्योम dvc_ग_लिखोl(काष्ठा tegra_i2c_dev *i2c_dev, u32 val,
		       अचिन्हित पूर्णांक reg)
अणु
	ग_लिखोl_relaxed(val, i2c_dev->base + reg);
पूर्ण

अटल u32 dvc_पढ़ोl(काष्ठा tegra_i2c_dev *i2c_dev, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl_relaxed(i2c_dev->base + reg);
पूर्ण

/*
 * If necessary, i2c_ग_लिखोl() and i2c_पढ़ोl() will offset the रेजिस्टर
 * in order to talk to the I2C block inside the DVC block.
 */
अटल u32 tegra_i2c_reg_addr(काष्ठा tegra_i2c_dev *i2c_dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (i2c_dev->is_dvc)
		reg += (reg >= I2C_TX_FIFO) ? 0x10 : 0x40;
	अन्यथा अगर (i2c_dev->is_vi)
		reg = 0xc00 + (reg << 2);

	वापस reg;
पूर्ण

अटल व्योम i2c_ग_लिखोl(काष्ठा tegra_i2c_dev *i2c_dev, u32 val, अचिन्हित पूर्णांक reg)
अणु
	ग_लिखोl_relaxed(val, i2c_dev->base + tegra_i2c_reg_addr(i2c_dev, reg));

	/* पढ़ो back रेजिस्टर to make sure that रेजिस्टर ग_लिखोs completed */
	अगर (reg != I2C_TX_FIFO)
		पढ़ोl_relaxed(i2c_dev->base + tegra_i2c_reg_addr(i2c_dev, reg));
	अन्यथा अगर (i2c_dev->is_vi)
		पढ़ोl_relaxed(i2c_dev->base + tegra_i2c_reg_addr(i2c_dev, I2C_INT_STATUS));
पूर्ण

अटल u32 i2c_पढ़ोl(काष्ठा tegra_i2c_dev *i2c_dev, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl_relaxed(i2c_dev->base + tegra_i2c_reg_addr(i2c_dev, reg));
पूर्ण

अटल व्योम i2c_ग_लिखोsl(काष्ठा tegra_i2c_dev *i2c_dev, व्योम *data,
			अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक len)
अणु
	ग_लिखोsl(i2c_dev->base + tegra_i2c_reg_addr(i2c_dev, reg), data, len);
पूर्ण

अटल व्योम i2c_ग_लिखोsl_vi(काष्ठा tegra_i2c_dev *i2c_dev, व्योम *data,
			   अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक len)
अणु
	u32 *data32 = data;

	/*
	 * VI I2C controller has known hardware bug where ग_लिखोs get stuck
	 * when immediate multiple ग_लिखोs happen to TX_FIFO रेजिस्टर.
	 * Recommended software work around is to पढ़ो I2C रेजिस्टर after
	 * each ग_लिखो to TX_FIFO रेजिस्टर to flush out the data.
	 */
	जबतक (len--)
		i2c_ग_लिखोl(i2c_dev, *data32++, reg);
पूर्ण

अटल व्योम i2c_पढ़ोsl(काष्ठा tegra_i2c_dev *i2c_dev, व्योम *data,
		       अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक len)
अणु
	पढ़ोsl(i2c_dev->base + tegra_i2c_reg_addr(i2c_dev, reg), data, len);
पूर्ण

अटल व्योम tegra_i2c_mask_irq(काष्ठा tegra_i2c_dev *i2c_dev, u32 mask)
अणु
	u32 पूर्णांक_mask;

	पूर्णांक_mask = i2c_पढ़ोl(i2c_dev, I2C_INT_MASK) & ~mask;
	i2c_ग_लिखोl(i2c_dev, पूर्णांक_mask, I2C_INT_MASK);
पूर्ण

अटल व्योम tegra_i2c_unmask_irq(काष्ठा tegra_i2c_dev *i2c_dev, u32 mask)
अणु
	u32 पूर्णांक_mask;

	पूर्णांक_mask = i2c_पढ़ोl(i2c_dev, I2C_INT_MASK) | mask;
	i2c_ग_लिखोl(i2c_dev, पूर्णांक_mask, I2C_INT_MASK);
पूर्ण

अटल व्योम tegra_i2c_dma_complete(व्योम *args)
अणु
	काष्ठा tegra_i2c_dev *i2c_dev = args;

	complete(&i2c_dev->dma_complete);
पूर्ण

अटल पूर्णांक tegra_i2c_dma_submit(काष्ठा tegra_i2c_dev *i2c_dev, माप_प्रकार len)
अणु
	काष्ठा dma_async_tx_descriptor *dma_desc;
	क्रमागत dma_transfer_direction dir;
	काष्ठा dma_chan *chan;

	dev_dbg(i2c_dev->dev, "starting DMA for length: %zu\n", len);

	reinit_completion(&i2c_dev->dma_complete);

	dir = i2c_dev->msg_पढ़ो ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV;
	chan = i2c_dev->msg_पढ़ो ? i2c_dev->rx_dma_chan : i2c_dev->tx_dma_chan;

	dma_desc = dmaengine_prep_slave_single(chan, i2c_dev->dma_phys,
					       len, dir, DMA_PREP_INTERRUPT |
					       DMA_CTRL_ACK);
	अगर (!dma_desc) अणु
		dev_err(i2c_dev->dev, "failed to get %s DMA descriptor\n",
			i2c_dev->msg_पढ़ो ? "RX" : "TX");
		वापस -EINVAL;
	पूर्ण

	dma_desc->callback = tegra_i2c_dma_complete;
	dma_desc->callback_param = i2c_dev;

	dmaengine_submit(dma_desc);
	dma_async_issue_pending(chan);

	वापस 0;
पूर्ण

अटल व्योम tegra_i2c_release_dma(काष्ठा tegra_i2c_dev *i2c_dev)
अणु
	अगर (i2c_dev->dma_buf) अणु
		dma_मुक्त_coherent(i2c_dev->dev, i2c_dev->dma_buf_size,
				  i2c_dev->dma_buf, i2c_dev->dma_phys);
		i2c_dev->dma_buf = शून्य;
	पूर्ण

	अगर (i2c_dev->tx_dma_chan) अणु
		dma_release_channel(i2c_dev->tx_dma_chan);
		i2c_dev->tx_dma_chan = शून्य;
	पूर्ण

	अगर (i2c_dev->rx_dma_chan) अणु
		dma_release_channel(i2c_dev->rx_dma_chan);
		i2c_dev->rx_dma_chan = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_i2c_init_dma(काष्ठा tegra_i2c_dev *i2c_dev)
अणु
	काष्ठा dma_chan *chan;
	dma_addr_t dma_phys;
	u32 *dma_buf;
	पूर्णांक err;

	अगर (!i2c_dev->hw->has_apb_dma || i2c_dev->is_vi)
		वापस 0;

	अगर (!IS_ENABLED(CONFIG_TEGRA20_APB_DMA)) अणु
		dev_dbg(i2c_dev->dev, "DMA support not enabled\n");
		वापस 0;
	पूर्ण

	chan = dma_request_chan(i2c_dev->dev, "rx");
	अगर (IS_ERR(chan)) अणु
		err = PTR_ERR(chan);
		जाओ err_out;
	पूर्ण

	i2c_dev->rx_dma_chan = chan;

	chan = dma_request_chan(i2c_dev->dev, "tx");
	अगर (IS_ERR(chan)) अणु
		err = PTR_ERR(chan);
		जाओ err_out;
	पूर्ण

	i2c_dev->tx_dma_chan = chan;

	i2c_dev->dma_buf_size = i2c_dev->hw->quirks->max_ग_लिखो_len +
				I2C_PACKET_HEADER_SIZE;

	dma_buf = dma_alloc_coherent(i2c_dev->dev, i2c_dev->dma_buf_size,
				     &dma_phys, GFP_KERNEL | __GFP_NOWARN);
	अगर (!dma_buf) अणु
		dev_err(i2c_dev->dev, "failed to allocate DMA buffer\n");
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	i2c_dev->dma_buf = dma_buf;
	i2c_dev->dma_phys = dma_phys;

	वापस 0;

err_out:
	tegra_i2c_release_dma(i2c_dev);
	अगर (err != -EPROBE_DEFER) अणु
		dev_err(i2c_dev->dev, "cannot use DMA: %d\n", err);
		dev_err(i2c_dev->dev, "falling back to PIO\n");
		वापस 0;
	पूर्ण

	वापस err;
पूर्ण

/*
 * One of the Tegra I2C blocks is inside the DVC (Digital Voltage Controller)
 * block.  This block is identical to the rest of the I2C blocks, except that
 * it only supports master mode, it has रेजिस्टरs moved around, and it needs
 * some extra init to get it पूर्णांकo I2C mode.  The रेजिस्टर moves are handled
 * by i2c_पढ़ोl() and i2c_ग_लिखोl().
 */
अटल व्योम tegra_dvc_init(काष्ठा tegra_i2c_dev *i2c_dev)
अणु
	u32 val;

	val = dvc_पढ़ोl(i2c_dev, DVC_CTRL_REG3);
	val |= DVC_CTRL_REG3_SW_PROG;
	val |= DVC_CTRL_REG3_I2C_DONE_INTR_EN;
	dvc_ग_लिखोl(i2c_dev, val, DVC_CTRL_REG3);

	val = dvc_पढ़ोl(i2c_dev, DVC_CTRL_REG1);
	val |= DVC_CTRL_REG1_INTR_EN;
	dvc_ग_लिखोl(i2c_dev, val, DVC_CTRL_REG1);
पूर्ण

अटल व्योम tegra_i2c_vi_init(काष्ठा tegra_i2c_dev *i2c_dev)
अणु
	u32 value;

	value = FIELD_PREP(I2C_INTERFACE_TIMING_THIGH, 2) |
		FIELD_PREP(I2C_INTERFACE_TIMING_TLOW, 4);
	i2c_ग_लिखोl(i2c_dev, value, I2C_INTERFACE_TIMING_0);

	value = FIELD_PREP(I2C_INTERFACE_TIMING_TBUF, 4) |
		FIELD_PREP(I2C_INTERFACE_TIMING_TSU_STO, 7) |
		FIELD_PREP(I2C_INTERFACE_TIMING_THD_STA, 4) |
		FIELD_PREP(I2C_INTERFACE_TIMING_TSU_STA, 4);
	i2c_ग_लिखोl(i2c_dev, value, I2C_INTERFACE_TIMING_1);

	value = FIELD_PREP(I2C_HS_INTERFACE_TIMING_THIGH, 3) |
		FIELD_PREP(I2C_HS_INTERFACE_TIMING_TLOW, 8);
	i2c_ग_लिखोl(i2c_dev, value, I2C_HS_INTERFACE_TIMING_0);

	value = FIELD_PREP(I2C_HS_INTERFACE_TIMING_TSU_STO, 11) |
		FIELD_PREP(I2C_HS_INTERFACE_TIMING_THD_STA, 11) |
		FIELD_PREP(I2C_HS_INTERFACE_TIMING_TSU_STA, 11);
	i2c_ग_लिखोl(i2c_dev, value, I2C_HS_INTERFACE_TIMING_1);

	value = FIELD_PREP(I2C_BC_SCLK_THRESHOLD, 9) | I2C_BC_STOP_COND;
	i2c_ग_लिखोl(i2c_dev, value, I2C_BUS_CLEAR_CNFG);

	i2c_ग_लिखोl(i2c_dev, 0x0, I2C_TLOW_SEXT);
पूर्ण

अटल पूर्णांक tegra_i2c_poll_रेजिस्टर(काष्ठा tegra_i2c_dev *i2c_dev,
				   u32 reg, u32 mask, u32 delay_us,
				   u32 समयout_us)
अणु
	व्योम __iomem *addr = i2c_dev->base + tegra_i2c_reg_addr(i2c_dev, reg);
	u32 val;

	अगर (!i2c_dev->atomic_mode)
		वापस पढ़ोl_relaxed_poll_समयout(addr, val, !(val & mask),
						  delay_us, समयout_us);

	वापस पढ़ोl_relaxed_poll_समयout_atomic(addr, val, !(val & mask),
						 delay_us, समयout_us);
पूर्ण

अटल पूर्णांक tegra_i2c_flush_fअगरos(काष्ठा tegra_i2c_dev *i2c_dev)
अणु
	u32 mask, val, offset;
	पूर्णांक err;

	अगर (i2c_dev->hw->has_mst_fअगरo) अणु
		mask = I2C_MST_FIFO_CONTROL_TX_FLUSH |
		       I2C_MST_FIFO_CONTROL_RX_FLUSH;
		offset = I2C_MST_FIFO_CONTROL;
	पूर्ण अन्यथा अणु
		mask = I2C_FIFO_CONTROL_TX_FLUSH |
		       I2C_FIFO_CONTROL_RX_FLUSH;
		offset = I2C_FIFO_CONTROL;
	पूर्ण

	val = i2c_पढ़ोl(i2c_dev, offset);
	val |= mask;
	i2c_ग_लिखोl(i2c_dev, val, offset);

	err = tegra_i2c_poll_रेजिस्टर(i2c_dev, offset, mask, 1000, 1000000);
	अगर (err) अणु
		dev_err(i2c_dev->dev, "failed to flush FIFO\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_i2c_रुको_क्रम_config_load(काष्ठा tegra_i2c_dev *i2c_dev)
अणु
	पूर्णांक err;

	अगर (!i2c_dev->hw->has_config_load_reg)
		वापस 0;

	i2c_ग_लिखोl(i2c_dev, I2C_MSTR_CONFIG_LOAD, I2C_CONFIG_LOAD);

	err = tegra_i2c_poll_रेजिस्टर(i2c_dev, I2C_CONFIG_LOAD, 0xffffffff,
				      1000, I2C_CONFIG_LOAD_TIMEOUT);
	अगर (err) अणु
		dev_err(i2c_dev->dev, "failed to load config\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_i2c_init(काष्ठा tegra_i2c_dev *i2c_dev)
अणु
	u32 val, clk_भागisor, clk_multiplier, tsu_thd, tlow, thigh, non_hs_mode;
	पूर्णांक err;

	/*
	 * The reset shouldn't ever fail in practice. The failure will be a
	 * sign of a severe problem that needs to be resolved. Still we करोn't
	 * want to fail the initialization completely because this may अवरोध
	 * kernel boot up since voltage regulators use I2C. Hence, we will
	 * emit a noisy warning on error, which won't stay unnoticed and
	 * won't hose machine entirely.
	 */
	err = reset_control_reset(i2c_dev->rst);
	WARN_ON_ONCE(err);

	अगर (i2c_dev->is_dvc)
		tegra_dvc_init(i2c_dev);

	val = I2C_CNFG_NEW_MASTER_FSM | I2C_CNFG_PACKET_MODE_EN |
	      FIELD_PREP(I2C_CNFG_DEBOUNCE_CNT, 2);

	अगर (i2c_dev->hw->has_multi_master_mode)
		val |= I2C_CNFG_MULTI_MASTER_MODE;

	i2c_ग_लिखोl(i2c_dev, val, I2C_CNFG);
	i2c_ग_लिखोl(i2c_dev, 0, I2C_INT_MASK);

	अगर (i2c_dev->is_vi)
		tegra_i2c_vi_init(i2c_dev);

	चयन (i2c_dev->bus_clk_rate) अणु
	हाल I2C_MAX_STANDARD_MODE_FREQ + 1 ... I2C_MAX_FAST_MODE_PLUS_FREQ:
	शेष:
		tlow = i2c_dev->hw->tlow_fast_fastplus_mode;
		thigh = i2c_dev->hw->thigh_fast_fastplus_mode;
		tsu_thd = i2c_dev->hw->setup_hold_समय_fast_fast_plus_mode;

		अगर (i2c_dev->bus_clk_rate > I2C_MAX_FAST_MODE_FREQ)
			non_hs_mode = i2c_dev->hw->clk_भागisor_fast_plus_mode;
		अन्यथा
			non_hs_mode = i2c_dev->hw->clk_भागisor_fast_mode;
		अवरोध;

	हाल 0 ... I2C_MAX_STANDARD_MODE_FREQ:
		tlow = i2c_dev->hw->tlow_std_mode;
		thigh = i2c_dev->hw->thigh_std_mode;
		tsu_thd = i2c_dev->hw->setup_hold_समय_std_mode;
		non_hs_mode = i2c_dev->hw->clk_भागisor_std_mode;
		अवरोध;
	पूर्ण

	/* make sure घड़ी भागisor programmed correctly */
	clk_भागisor = FIELD_PREP(I2C_CLK_DIVISOR_HSMODE,
				 i2c_dev->hw->clk_भागisor_hs_mode) |
		      FIELD_PREP(I2C_CLK_DIVISOR_STD_FAST_MODE, non_hs_mode);
	i2c_ग_लिखोl(i2c_dev, clk_भागisor, I2C_CLK_DIVISOR);

	अगर (i2c_dev->hw->has_पूर्णांकerface_timing_reg) अणु
		val = FIELD_PREP(I2C_INTERFACE_TIMING_THIGH, thigh) |
		      FIELD_PREP(I2C_INTERFACE_TIMING_TLOW, tlow);
		i2c_ग_लिखोl(i2c_dev, val, I2C_INTERFACE_TIMING_0);
	पूर्ण

	/*
	 * Configure setup and hold बार only when tsu_thd is non-zero.
	 * Otherwise, preserve the chip शेष values.
	 */
	अगर (i2c_dev->hw->has_पूर्णांकerface_timing_reg && tsu_thd)
		i2c_ग_लिखोl(i2c_dev, tsu_thd, I2C_INTERFACE_TIMING_1);

	clk_multiplier = (tlow + thigh + 2) * (non_hs_mode + 1);

	err = clk_set_rate(i2c_dev->भाग_clk,
			   i2c_dev->bus_clk_rate * clk_multiplier);
	अगर (err) अणु
		dev_err(i2c_dev->dev, "failed to set div-clk rate: %d\n", err);
		वापस err;
	पूर्ण

	अगर (!i2c_dev->is_dvc && !i2c_dev->is_vi) अणु
		u32 sl_cfg = i2c_पढ़ोl(i2c_dev, I2C_SL_CNFG);

		sl_cfg |= I2C_SL_CNFG_NACK | I2C_SL_CNFG_NEWSL;
		i2c_ग_लिखोl(i2c_dev, sl_cfg, I2C_SL_CNFG);
		i2c_ग_लिखोl(i2c_dev, 0xfc, I2C_SL_ADDR1);
		i2c_ग_लिखोl(i2c_dev, 0x00, I2C_SL_ADDR2);
	पूर्ण

	err = tegra_i2c_flush_fअगरos(i2c_dev);
	अगर (err)
		वापस err;

	अगर (i2c_dev->multimaster_mode && i2c_dev->hw->has_slcg_override_reg)
		i2c_ग_लिखोl(i2c_dev, I2C_MST_CORE_CLKEN_OVR, I2C_CLKEN_OVERRIDE);

	err = tegra_i2c_रुको_क्रम_config_load(i2c_dev);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_i2c_disable_packet_mode(काष्ठा tegra_i2c_dev *i2c_dev)
अणु
	u32 cnfg;

	/*
	 * NACK पूर्णांकerrupt is generated beक्रमe the I2C controller generates
	 * the STOP condition on the bus.  So, रुको क्रम 2 घड़ी periods
	 * beक्रमe disabling the controller so that the STOP condition has
	 * been delivered properly.
	 */
	udelay(DIV_ROUND_UP(2 * 1000000, i2c_dev->bus_clk_rate));

	cnfg = i2c_पढ़ोl(i2c_dev, I2C_CNFG);
	अगर (cnfg & I2C_CNFG_PACKET_MODE_EN)
		i2c_ग_लिखोl(i2c_dev, cnfg & ~I2C_CNFG_PACKET_MODE_EN, I2C_CNFG);

	वापस tegra_i2c_रुको_क्रम_config_load(i2c_dev);
पूर्ण

अटल पूर्णांक tegra_i2c_empty_rx_fअगरo(काष्ठा tegra_i2c_dev *i2c_dev)
अणु
	माप_प्रकार buf_reमुख्यing = i2c_dev->msg_buf_reमुख्यing;
	अचिन्हित पूर्णांक words_to_transfer, rx_fअगरo_avail;
	u8 *buf = i2c_dev->msg_buf;
	u32 val;

	/*
	 * Catch overflow due to message fully sent beक्रमe the check क्रम
	 * RX FIFO availability.
	 */
	अगर (WARN_ON_ONCE(!(i2c_dev->msg_buf_reमुख्यing)))
		वापस -EINVAL;

	अगर (i2c_dev->hw->has_mst_fअगरo) अणु
		val = i2c_पढ़ोl(i2c_dev, I2C_MST_FIFO_STATUS);
		rx_fअगरo_avail = FIELD_GET(I2C_MST_FIFO_STATUS_RX, val);
	पूर्ण अन्यथा अणु
		val = i2c_पढ़ोl(i2c_dev, I2C_FIFO_STATUS);
		rx_fअगरo_avail = FIELD_GET(I2C_FIFO_STATUS_RX, val);
	पूर्ण

	/* round करोwn to exclude partial word at the end of buffer */
	words_to_transfer = buf_reमुख्यing / BYTES_PER_FIFO_WORD;
	अगर (words_to_transfer > rx_fअगरo_avail)
		words_to_transfer = rx_fअगरo_avail;

	i2c_पढ़ोsl(i2c_dev, buf, I2C_RX_FIFO, words_to_transfer);

	buf += words_to_transfer * BYTES_PER_FIFO_WORD;
	buf_reमुख्यing -= words_to_transfer * BYTES_PER_FIFO_WORD;
	rx_fअगरo_avail -= words_to_transfer;

	/*
	 * If there is a partial word at the end of buffer, handle it
	 * manually to prevent overwriting past the end of buffer.
	 */
	अगर (rx_fअगरo_avail > 0 && buf_reमुख्यing > 0) अणु
		/*
		 * buf_reमुख्यing > 3 check not needed as rx_fअगरo_avail == 0
		 * when (words_to_transfer was > rx_fअगरo_avail) earlier
		 * in this function.
		 */
		val = i2c_पढ़ोl(i2c_dev, I2C_RX_FIFO);
		val = cpu_to_le32(val);
		स_नकल(buf, &val, buf_reमुख्यing);
		buf_reमुख्यing = 0;
		rx_fअगरo_avail--;
	पूर्ण

	/* RX FIFO must be drained, otherwise it's an Overflow हाल. */
	अगर (WARN_ON_ONCE(rx_fअगरo_avail))
		वापस -EINVAL;

	i2c_dev->msg_buf_reमुख्यing = buf_reमुख्यing;
	i2c_dev->msg_buf = buf;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_i2c_fill_tx_fअगरo(काष्ठा tegra_i2c_dev *i2c_dev)
अणु
	माप_प्रकार buf_reमुख्यing = i2c_dev->msg_buf_reमुख्यing;
	अचिन्हित पूर्णांक words_to_transfer, tx_fअगरo_avail;
	u8 *buf = i2c_dev->msg_buf;
	u32 val;

	अगर (i2c_dev->hw->has_mst_fअगरo) अणु
		val = i2c_पढ़ोl(i2c_dev, I2C_MST_FIFO_STATUS);
		tx_fअगरo_avail = FIELD_GET(I2C_MST_FIFO_STATUS_TX, val);
	पूर्ण अन्यथा अणु
		val = i2c_पढ़ोl(i2c_dev, I2C_FIFO_STATUS);
		tx_fअगरo_avail = FIELD_GET(I2C_FIFO_STATUS_TX, val);
	पूर्ण

	/* round करोwn to exclude partial word at the end of buffer */
	words_to_transfer = buf_reमुख्यing / BYTES_PER_FIFO_WORD;

	/*
	 * This hunk pushes 4 bytes at a समय पूर्णांकo the TX FIFO.
	 *
	 * It's very common to have < 4 bytes, hence there is no word
	 * to push अगर we have less than 4 bytes to transfer.
	 */
	अगर (words_to_transfer) अणु
		अगर (words_to_transfer > tx_fअगरo_avail)
			words_to_transfer = tx_fअगरo_avail;

		/*
		 * Update state beक्रमe writing to FIFO.  Note that this may
		 * cause us to finish writing all bytes (AKA buf_reमुख्यing
		 * goes to 0), hence we have a potential क्रम an पूर्णांकerrupt
		 * (PACKET_XFER_COMPLETE is not maskable), but GIC पूर्णांकerrupt
		 * is disabled at this poपूर्णांक.
		 */
		buf_reमुख्यing -= words_to_transfer * BYTES_PER_FIFO_WORD;
		tx_fअगरo_avail -= words_to_transfer;

		i2c_dev->msg_buf_reमुख्यing = buf_reमुख्यing;
		i2c_dev->msg_buf = buf + words_to_transfer * BYTES_PER_FIFO_WORD;

		अगर (i2c_dev->is_vi)
			i2c_ग_लिखोsl_vi(i2c_dev, buf, I2C_TX_FIFO, words_to_transfer);
		अन्यथा
			i2c_ग_लिखोsl(i2c_dev, buf, I2C_TX_FIFO, words_to_transfer);

		buf += words_to_transfer * BYTES_PER_FIFO_WORD;
	पूर्ण

	/*
	 * If there is a partial word at the end of buffer, handle it manually
	 * to prevent पढ़ोing past the end of buffer, which could cross a page
	 * boundary and fault.
	 */
	अगर (tx_fअगरo_avail > 0 && buf_reमुख्यing > 0) अणु
		/*
		 * buf_reमुख्यing > 3 check not needed as tx_fअगरo_avail == 0
		 * when (words_to_transfer was > tx_fअगरo_avail) earlier
		 * in this function क्रम non-zero words_to_transfer.
		 */
		स_नकल(&val, buf, buf_reमुख्यing);
		val = le32_to_cpu(val);

		i2c_dev->msg_buf_reमुख्यing = 0;
		i2c_dev->msg_buf = शून्य;

		i2c_ग_लिखोl(i2c_dev, val, I2C_TX_FIFO);
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t tegra_i2c_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	स्थिर u32 status_err = I2C_INT_NO_ACK | I2C_INT_ARBITRATION_LOST;
	काष्ठा tegra_i2c_dev *i2c_dev = dev_id;
	u32 status;

	status = i2c_पढ़ोl(i2c_dev, I2C_INT_STATUS);

	अगर (status == 0) अणु
		dev_warn(i2c_dev->dev, "IRQ status 0 %08x %08x %08x\n",
			 i2c_पढ़ोl(i2c_dev, I2C_PACKET_TRANSFER_STATUS),
			 i2c_पढ़ोl(i2c_dev, I2C_STATUS),
			 i2c_पढ़ोl(i2c_dev, I2C_CNFG));
		i2c_dev->msg_err |= I2C_ERR_UNKNOWN_INTERRUPT;
		जाओ err;
	पूर्ण

	अगर (status & status_err) अणु
		tegra_i2c_disable_packet_mode(i2c_dev);
		अगर (status & I2C_INT_NO_ACK)
			i2c_dev->msg_err |= I2C_ERR_NO_ACK;
		अगर (status & I2C_INT_ARBITRATION_LOST)
			i2c_dev->msg_err |= I2C_ERR_ARBITRATION_LOST;
		जाओ err;
	पूर्ण

	/*
	 * I2C transfer is terminated during the bus clear, so skip
	 * processing the other पूर्णांकerrupts.
	 */
	अगर (i2c_dev->hw->supports_bus_clear && (status & I2C_INT_BUS_CLR_DONE))
		जाओ err;

	अगर (!i2c_dev->dma_mode) अणु
		अगर (i2c_dev->msg_पढ़ो && (status & I2C_INT_RX_FIFO_DATA_REQ)) अणु
			अगर (tegra_i2c_empty_rx_fअगरo(i2c_dev)) अणु
				/*
				 * Overflow error condition: message fully sent,
				 * with no XFER_COMPLETE पूर्णांकerrupt but hardware
				 * asks to transfer more.
				 */
				i2c_dev->msg_err |= I2C_ERR_RX_BUFFER_OVERFLOW;
				जाओ err;
			पूर्ण
		पूर्ण

		अगर (!i2c_dev->msg_पढ़ो && (status & I2C_INT_TX_FIFO_DATA_REQ)) अणु
			अगर (i2c_dev->msg_buf_reमुख्यing)
				tegra_i2c_fill_tx_fअगरo(i2c_dev);
			अन्यथा
				tegra_i2c_mask_irq(i2c_dev,
						   I2C_INT_TX_FIFO_DATA_REQ);
		पूर्ण
	पूर्ण

	i2c_ग_लिखोl(i2c_dev, status, I2C_INT_STATUS);
	अगर (i2c_dev->is_dvc)
		dvc_ग_लिखोl(i2c_dev, DVC_STATUS_I2C_DONE_INTR, DVC_STATUS);

	/*
	 * During message पढ़ो XFER_COMPLETE पूर्णांकerrupt is triggered prior to
	 * DMA completion and during message ग_लिखो XFER_COMPLETE पूर्णांकerrupt is
	 * triggered after DMA completion.
	 *
	 * PACKETS_XFER_COMPLETE indicates completion of all bytes of transfer,
	 * so क्रमcing msg_buf_reमुख्यing to 0 in DMA mode.
	 */
	अगर (status & I2C_INT_PACKET_XFER_COMPLETE) अणु
		अगर (i2c_dev->dma_mode)
			i2c_dev->msg_buf_reमुख्यing = 0;
		/*
		 * Underflow error condition: XFER_COMPLETE beक्रमe message
		 * fully sent.
		 */
		अगर (WARN_ON_ONCE(i2c_dev->msg_buf_reमुख्यing)) अणु
			i2c_dev->msg_err |= I2C_ERR_UNKNOWN_INTERRUPT;
			जाओ err;
		पूर्ण
		complete(&i2c_dev->msg_complete);
	पूर्ण
	जाओ करोne;
err:
	/* mask all पूर्णांकerrupts on error */
	tegra_i2c_mask_irq(i2c_dev,
			   I2C_INT_NO_ACK |
			   I2C_INT_ARBITRATION_LOST |
			   I2C_INT_PACKET_XFER_COMPLETE |
			   I2C_INT_TX_FIFO_DATA_REQ |
			   I2C_INT_RX_FIFO_DATA_REQ);

	अगर (i2c_dev->hw->supports_bus_clear)
		tegra_i2c_mask_irq(i2c_dev, I2C_INT_BUS_CLR_DONE);

	i2c_ग_लिखोl(i2c_dev, status, I2C_INT_STATUS);

	अगर (i2c_dev->is_dvc)
		dvc_ग_लिखोl(i2c_dev, DVC_STATUS_I2C_DONE_INTR, DVC_STATUS);

	अगर (i2c_dev->dma_mode) अणु
		अगर (i2c_dev->msg_पढ़ो)
			dmaengine_terminate_async(i2c_dev->rx_dma_chan);
		अन्यथा
			dmaengine_terminate_async(i2c_dev->tx_dma_chan);

		complete(&i2c_dev->dma_complete);
	पूर्ण

	complete(&i2c_dev->msg_complete);
करोne:
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tegra_i2c_config_fअगरo_trig(काष्ठा tegra_i2c_dev *i2c_dev,
				       माप_प्रकार len)
अणु
	काष्ठा dma_slave_config slv_config = अणु0पूर्ण;
	u32 val, reg, dma_burst, reg_offset;
	काष्ठा dma_chan *chan;
	पूर्णांक err;

	अगर (i2c_dev->hw->has_mst_fअगरo)
		reg = I2C_MST_FIFO_CONTROL;
	अन्यथा
		reg = I2C_FIFO_CONTROL;

	अगर (i2c_dev->dma_mode) अणु
		अगर (len & 0xF)
			dma_burst = 1;
		अन्यथा अगर (len & 0x10)
			dma_burst = 4;
		अन्यथा
			dma_burst = 8;

		अगर (i2c_dev->msg_पढ़ो) अणु
			chan = i2c_dev->rx_dma_chan;
			reg_offset = tegra_i2c_reg_addr(i2c_dev, I2C_RX_FIFO);

			slv_config.src_addr = i2c_dev->base_phys + reg_offset;
			slv_config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
			slv_config.src_maxburst = dma_burst;

			अगर (i2c_dev->hw->has_mst_fअगरo)
				val = I2C_MST_FIFO_CONTROL_RX_TRIG(dma_burst);
			अन्यथा
				val = I2C_FIFO_CONTROL_RX_TRIG(dma_burst);
		पूर्ण अन्यथा अणु
			chan = i2c_dev->tx_dma_chan;
			reg_offset = tegra_i2c_reg_addr(i2c_dev, I2C_TX_FIFO);

			slv_config.dst_addr = i2c_dev->base_phys + reg_offset;
			slv_config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
			slv_config.dst_maxburst = dma_burst;

			अगर (i2c_dev->hw->has_mst_fअगरo)
				val = I2C_MST_FIFO_CONTROL_TX_TRIG(dma_burst);
			अन्यथा
				val = I2C_FIFO_CONTROL_TX_TRIG(dma_burst);
		पूर्ण

		slv_config.device_fc = true;
		err = dmaengine_slave_config(chan, &slv_config);
		अगर (err) अणु
			dev_err(i2c_dev->dev, "DMA config failed: %d\n", err);
			dev_err(i2c_dev->dev, "falling back to PIO\n");

			tegra_i2c_release_dma(i2c_dev);
			i2c_dev->dma_mode = false;
		पूर्ण अन्यथा अणु
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (i2c_dev->hw->has_mst_fअगरo)
		val = I2C_MST_FIFO_CONTROL_TX_TRIG(8) |
		      I2C_MST_FIFO_CONTROL_RX_TRIG(1);
	अन्यथा
		val = I2C_FIFO_CONTROL_TX_TRIG(8) |
		      I2C_FIFO_CONTROL_RX_TRIG(1);
out:
	i2c_ग_लिखोl(i2c_dev, val, reg);
पूर्ण

अटल अचिन्हित दीर्घ tegra_i2c_poll_completion(काष्ठा tegra_i2c_dev *i2c_dev,
					       काष्ठा completion *complete,
					       अचिन्हित पूर्णांक समयout_ms)
अणु
	kसमय_प्रकार kसमय = kसमय_get();
	kसमय_प्रकार kसमयout = kसमय_add_ms(kसमय, समयout_ms);

	करो अणु
		u32 status = i2c_पढ़ोl(i2c_dev, I2C_INT_STATUS);

		अगर (status)
			tegra_i2c_isr(i2c_dev->irq, i2c_dev);

		अगर (completion_करोne(complete)) अणु
			s64 delta = kसमय_ms_delta(kसमयout, kसमय);

			वापस msecs_to_jअगरfies(delta) ?: 1;
		पूर्ण

		kसमय = kसमय_get();

	पूर्ण जबतक (kसमय_beक्रमe(kसमय, kसमयout));

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ tegra_i2c_रुको_completion(काष्ठा tegra_i2c_dev *i2c_dev,
					       काष्ठा completion *complete,
					       अचिन्हित पूर्णांक समयout_ms)
अणु
	अचिन्हित दीर्घ ret;

	अगर (i2c_dev->atomic_mode) अणु
		ret = tegra_i2c_poll_completion(i2c_dev, complete, समयout_ms);
	पूर्ण अन्यथा अणु
		enable_irq(i2c_dev->irq);
		ret = रुको_क्रम_completion_समयout(complete,
						  msecs_to_jअगरfies(समयout_ms));
		disable_irq(i2c_dev->irq);

		/*
		 * Under some rare circumstances (like running KASAN +
		 * NFS root) CPU, which handles पूर्णांकerrupt, may stuck in
		 * unपूर्णांकerruptible state क्रम a signअगरicant समय.  In this
		 * हाल we will get समयout अगर I2C transfer is running on
		 * a sibling CPU, despite of IRQ being उठाओd.
		 *
		 * In order to handle this rare condition, the IRQ status
		 * needs to be checked after समयout.
		 */
		अगर (ret == 0)
			ret = tegra_i2c_poll_completion(i2c_dev, complete, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_i2c_issue_bus_clear(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा tegra_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	u32 val, समय_left;
	पूर्णांक err;

	reinit_completion(&i2c_dev->msg_complete);

	val = FIELD_PREP(I2C_BC_SCLK_THRESHOLD, 9) | I2C_BC_STOP_COND |
	      I2C_BC_TERMINATE;
	i2c_ग_लिखोl(i2c_dev, val, I2C_BUS_CLEAR_CNFG);

	err = tegra_i2c_रुको_क्रम_config_load(i2c_dev);
	अगर (err)
		वापस err;

	val |= I2C_BC_ENABLE;
	i2c_ग_लिखोl(i2c_dev, val, I2C_BUS_CLEAR_CNFG);
	tegra_i2c_unmask_irq(i2c_dev, I2C_INT_BUS_CLR_DONE);

	समय_left = tegra_i2c_रुको_completion(i2c_dev, &i2c_dev->msg_complete, 50);
	tegra_i2c_mask_irq(i2c_dev, I2C_INT_BUS_CLR_DONE);

	अगर (समय_left == 0) अणु
		dev_err(i2c_dev->dev, "failed to clear bus\n");
		वापस -ETIMEDOUT;
	पूर्ण

	val = i2c_पढ़ोl(i2c_dev, I2C_BUS_CLEAR_STATUS);
	अगर (!(val & I2C_BC_STATUS)) अणु
		dev_err(i2c_dev->dev, "un-recovered arbitration lost\n");
		वापस -EIO;
	पूर्ण

	वापस -EAGAIN;
पूर्ण

अटल व्योम tegra_i2c_push_packet_header(काष्ठा tegra_i2c_dev *i2c_dev,
					 काष्ठा i2c_msg *msg,
					 क्रमागत msg_end_type end_state)
अणु
	u32 *dma_buf = i2c_dev->dma_buf;
	u32 packet_header;

	packet_header = FIELD_PREP(PACKET_HEADER0_HEADER_SIZE, 0) |
			FIELD_PREP(PACKET_HEADER0_PROTOCOL,
				   PACKET_HEADER0_PROTOCOL_I2C) |
			FIELD_PREP(PACKET_HEADER0_CONT_ID, i2c_dev->cont_id) |
			FIELD_PREP(PACKET_HEADER0_PACKET_ID, 1);

	अगर (i2c_dev->dma_mode && !i2c_dev->msg_पढ़ो)
		*dma_buf++ = packet_header;
	अन्यथा
		i2c_ग_लिखोl(i2c_dev, packet_header, I2C_TX_FIFO);

	packet_header = msg->len - 1;

	अगर (i2c_dev->dma_mode && !i2c_dev->msg_पढ़ो)
		*dma_buf++ = packet_header;
	अन्यथा
		i2c_ग_लिखोl(i2c_dev, packet_header, I2C_TX_FIFO);

	packet_header = I2C_HEADER_IE_ENABLE;

	अगर (end_state == MSG_END_CONTINUE)
		packet_header |= I2C_HEADER_CONTINUE_XFER;
	अन्यथा अगर (end_state == MSG_END_REPEAT_START)
		packet_header |= I2C_HEADER_REPEAT_START;

	अगर (msg->flags & I2C_M_TEN) अणु
		packet_header |= msg->addr;
		packet_header |= I2C_HEADER_10BIT_ADDR;
	पूर्ण अन्यथा अणु
		packet_header |= msg->addr << I2C_HEADER_SLAVE_ADDR_SHIFT;
	पूर्ण

	अगर (msg->flags & I2C_M_IGNORE_NAK)
		packet_header |= I2C_HEADER_CONT_ON_NAK;

	अगर (msg->flags & I2C_M_RD)
		packet_header |= I2C_HEADER_READ;

	अगर (i2c_dev->dma_mode && !i2c_dev->msg_पढ़ो)
		*dma_buf++ = packet_header;
	अन्यथा
		i2c_ग_लिखोl(i2c_dev, packet_header, I2C_TX_FIFO);
पूर्ण

अटल पूर्णांक tegra_i2c_error_recover(काष्ठा tegra_i2c_dev *i2c_dev,
				   काष्ठा i2c_msg *msg)
अणु
	अगर (i2c_dev->msg_err == I2C_ERR_NONE)
		वापस 0;

	tegra_i2c_init(i2c_dev);

	/* start recovery upon arbitration loss in single master mode */
	अगर (i2c_dev->msg_err == I2C_ERR_ARBITRATION_LOST) अणु
		अगर (!i2c_dev->multimaster_mode)
			वापस i2c_recover_bus(&i2c_dev->adapter);

		वापस -EAGAIN;
	पूर्ण

	अगर (i2c_dev->msg_err == I2C_ERR_NO_ACK) अणु
		अगर (msg->flags & I2C_M_IGNORE_NAK)
			वापस 0;

		वापस -EREMOTEIO;
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक tegra_i2c_xfer_msg(काष्ठा tegra_i2c_dev *i2c_dev,
			      काष्ठा i2c_msg *msg,
			      क्रमागत msg_end_type end_state)
अणु
	अचिन्हित दीर्घ समय_left, xfer_समय = 100;
	माप_प्रकार xfer_size;
	u32 पूर्णांक_mask;
	पूर्णांक err;

	err = tegra_i2c_flush_fअगरos(i2c_dev);
	अगर (err)
		वापस err;

	i2c_dev->msg_buf = msg->buf;
	i2c_dev->msg_buf_reमुख्यing = msg->len;
	i2c_dev->msg_err = I2C_ERR_NONE;
	i2c_dev->msg_पढ़ो = !!(msg->flags & I2C_M_RD);
	reinit_completion(&i2c_dev->msg_complete);

	अगर (i2c_dev->msg_पढ़ो)
		xfer_size = msg->len;
	अन्यथा
		xfer_size = msg->len + I2C_PACKET_HEADER_SIZE;

	xfer_size = ALIGN(xfer_size, BYTES_PER_FIFO_WORD);

	i2c_dev->dma_mode = xfer_size > I2C_PIO_MODE_PREFERRED_LEN &&
			    i2c_dev->dma_buf && !i2c_dev->atomic_mode;

	tegra_i2c_config_fअगरo_trig(i2c_dev, xfer_size);

	/*
	 * Transfer समय in mSec = Total bits / transfer rate
	 * Total bits = 9 bits per byte (including ACK bit) + Start & stop bits
	 */
	xfer_समय += DIV_ROUND_CLOSEST(((xfer_size * 9) + 2) * MSEC_PER_SEC,
				       i2c_dev->bus_clk_rate);

	पूर्णांक_mask = I2C_INT_NO_ACK | I2C_INT_ARBITRATION_LOST;
	tegra_i2c_unmask_irq(i2c_dev, पूर्णांक_mask);

	अगर (i2c_dev->dma_mode) अणु
		अगर (i2c_dev->msg_पढ़ो) अणु
			dma_sync_single_क्रम_device(i2c_dev->dev,
						   i2c_dev->dma_phys,
						   xfer_size, DMA_FROM_DEVICE);

			err = tegra_i2c_dma_submit(i2c_dev, xfer_size);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			dma_sync_single_क्रम_cpu(i2c_dev->dev,
						i2c_dev->dma_phys,
						xfer_size, DMA_TO_DEVICE);
		पूर्ण
	पूर्ण

	tegra_i2c_push_packet_header(i2c_dev, msg, end_state);

	अगर (!i2c_dev->msg_पढ़ो) अणु
		अगर (i2c_dev->dma_mode) अणु
			स_नकल(i2c_dev->dma_buf + I2C_PACKET_HEADER_SIZE,
			       msg->buf, msg->len);

			dma_sync_single_क्रम_device(i2c_dev->dev,
						   i2c_dev->dma_phys,
						   xfer_size, DMA_TO_DEVICE);

			err = tegra_i2c_dma_submit(i2c_dev, xfer_size);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			tegra_i2c_fill_tx_fअगरo(i2c_dev);
		पूर्ण
	पूर्ण

	अगर (i2c_dev->hw->has_per_pkt_xfer_complete_irq)
		पूर्णांक_mask |= I2C_INT_PACKET_XFER_COMPLETE;

	अगर (!i2c_dev->dma_mode) अणु
		अगर (msg->flags & I2C_M_RD)
			पूर्णांक_mask |= I2C_INT_RX_FIFO_DATA_REQ;
		अन्यथा अगर (i2c_dev->msg_buf_reमुख्यing)
			पूर्णांक_mask |= I2C_INT_TX_FIFO_DATA_REQ;
	पूर्ण

	tegra_i2c_unmask_irq(i2c_dev, पूर्णांक_mask);
	dev_dbg(i2c_dev->dev, "unmasked IRQ: %02x\n",
		i2c_पढ़ोl(i2c_dev, I2C_INT_MASK));

	अगर (i2c_dev->dma_mode) अणु
		समय_left = tegra_i2c_रुको_completion(i2c_dev,
						      &i2c_dev->dma_complete,
						      xfer_समय);

		/*
		 * Synchronize DMA first, since dmaengine_terminate_sync()
		 * perक्रमms synchronization after the transfer's termination
		 * and we want to get a completion अगर transfer succeeded.
		 */
		dmaengine_synchronize(i2c_dev->msg_पढ़ो ?
				      i2c_dev->rx_dma_chan :
				      i2c_dev->tx_dma_chan);

		dmaengine_terminate_sync(i2c_dev->msg_पढ़ो ?
					 i2c_dev->rx_dma_chan :
					 i2c_dev->tx_dma_chan);

		अगर (!समय_left && !completion_करोne(&i2c_dev->dma_complete)) अणु
			dev_err(i2c_dev->dev, "DMA transfer timed out\n");
			tegra_i2c_init(i2c_dev);
			वापस -ETIMEDOUT;
		पूर्ण

		अगर (i2c_dev->msg_पढ़ो && i2c_dev->msg_err == I2C_ERR_NONE) अणु
			dma_sync_single_क्रम_cpu(i2c_dev->dev,
						i2c_dev->dma_phys,
						xfer_size, DMA_FROM_DEVICE);

			स_नकल(i2c_dev->msg_buf, i2c_dev->dma_buf, msg->len);
		पूर्ण
	पूर्ण

	समय_left = tegra_i2c_रुको_completion(i2c_dev, &i2c_dev->msg_complete,
					      xfer_समय);

	tegra_i2c_mask_irq(i2c_dev, पूर्णांक_mask);

	अगर (समय_left == 0) अणु
		dev_err(i2c_dev->dev, "I2C transfer timed out\n");
		tegra_i2c_init(i2c_dev);
		वापस -ETIMEDOUT;
	पूर्ण

	dev_dbg(i2c_dev->dev, "transfer complete: %lu %d %d\n",
		समय_left, completion_करोne(&i2c_dev->msg_complete),
		i2c_dev->msg_err);

	i2c_dev->dma_mode = false;

	err = tegra_i2c_error_recover(i2c_dev, msg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msgs[],
			  पूर्णांक num)
अणु
	काष्ठा tegra_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	पूर्णांक i, ret;

	ret = pm_runसमय_get_sync(i2c_dev->dev);
	अगर (ret < 0) अणु
		dev_err(i2c_dev->dev, "runtime resume failed %d\n", ret);
		pm_runसमय_put_noidle(i2c_dev->dev);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		क्रमागत msg_end_type end_type = MSG_END_STOP;

		अगर (i < (num - 1)) अणु
			/* check whether follow up message is coming */
			अगर (msgs[i + 1].flags & I2C_M_NOSTART)
				end_type = MSG_END_CONTINUE;
			अन्यथा
				end_type = MSG_END_REPEAT_START;
		पूर्ण
		ret = tegra_i2c_xfer_msg(i2c_dev, &msgs[i], end_type);
		अगर (ret)
			अवरोध;
	पूर्ण

	pm_runसमय_put(i2c_dev->dev);

	वापस ret ?: i;
पूर्ण

अटल पूर्णांक tegra_i2c_xfer_atomic(काष्ठा i2c_adapter *adap,
				 काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा tegra_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	पूर्णांक ret;

	i2c_dev->atomic_mode = true;
	ret = tegra_i2c_xfer(adap, msgs, num);
	i2c_dev->atomic_mode = false;

	वापस ret;
पूर्ण

अटल u32 tegra_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा tegra_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	u32 ret = I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK) |
		  I2C_FUNC_10BIT_ADDR |	I2C_FUNC_PROTOCOL_MANGLING;

	अगर (i2c_dev->hw->has_जारी_xfer_support)
		ret |= I2C_FUNC_NOSTART;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm tegra_i2c_algo = अणु
	.master_xfer		= tegra_i2c_xfer,
	.master_xfer_atomic	= tegra_i2c_xfer_atomic,
	.functionality		= tegra_i2c_func,
पूर्ण;

/* payload size is only 12 bit */
अटल स्थिर काष्ठा i2c_adapter_quirks tegra_i2c_quirks = अणु
	.flags = I2C_AQ_NO_ZERO_LEN,
	.max_पढ़ो_len = SZ_4K,
	.max_ग_लिखो_len = SZ_4K - I2C_PACKET_HEADER_SIZE,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks tegra194_i2c_quirks = अणु
	.flags = I2C_AQ_NO_ZERO_LEN,
	.max_ग_लिखो_len = SZ_64K - I2C_PACKET_HEADER_SIZE,
पूर्ण;

अटल काष्ठा i2c_bus_recovery_info tegra_i2c_recovery_info = अणु
	.recover_bus = tegra_i2c_issue_bus_clear,
पूर्ण;

अटल स्थिर काष्ठा tegra_i2c_hw_feature tegra20_i2c_hw = अणु
	.has_जारी_xfer_support = false,
	.has_per_pkt_xfer_complete_irq = false,
	.clk_भागisor_hs_mode = 3,
	.clk_भागisor_std_mode = 0,
	.clk_भागisor_fast_mode = 0,
	.clk_भागisor_fast_plus_mode = 0,
	.has_config_load_reg = false,
	.has_multi_master_mode = false,
	.has_slcg_override_reg = false,
	.has_mst_fअगरo = false,
	.quirks = &tegra_i2c_quirks,
	.supports_bus_clear = false,
	.has_apb_dma = true,
	.tlow_std_mode = 0x4,
	.thigh_std_mode = 0x2,
	.tlow_fast_fastplus_mode = 0x4,
	.thigh_fast_fastplus_mode = 0x2,
	.setup_hold_समय_std_mode = 0x0,
	.setup_hold_समय_fast_fast_plus_mode = 0x0,
	.setup_hold_समय_hs_mode = 0x0,
	.has_पूर्णांकerface_timing_reg = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_i2c_hw_feature tegra30_i2c_hw = अणु
	.has_जारी_xfer_support = true,
	.has_per_pkt_xfer_complete_irq = false,
	.clk_भागisor_hs_mode = 3,
	.clk_भागisor_std_mode = 0,
	.clk_भागisor_fast_mode = 0,
	.clk_भागisor_fast_plus_mode = 0,
	.has_config_load_reg = false,
	.has_multi_master_mode = false,
	.has_slcg_override_reg = false,
	.has_mst_fअगरo = false,
	.quirks = &tegra_i2c_quirks,
	.supports_bus_clear = false,
	.has_apb_dma = true,
	.tlow_std_mode = 0x4,
	.thigh_std_mode = 0x2,
	.tlow_fast_fastplus_mode = 0x4,
	.thigh_fast_fastplus_mode = 0x2,
	.setup_hold_समय_std_mode = 0x0,
	.setup_hold_समय_fast_fast_plus_mode = 0x0,
	.setup_hold_समय_hs_mode = 0x0,
	.has_पूर्णांकerface_timing_reg = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_i2c_hw_feature tegra114_i2c_hw = अणु
	.has_जारी_xfer_support = true,
	.has_per_pkt_xfer_complete_irq = true,
	.clk_भागisor_hs_mode = 1,
	.clk_भागisor_std_mode = 0x19,
	.clk_भागisor_fast_mode = 0x19,
	.clk_भागisor_fast_plus_mode = 0x10,
	.has_config_load_reg = false,
	.has_multi_master_mode = false,
	.has_slcg_override_reg = false,
	.has_mst_fअगरo = false,
	.quirks = &tegra_i2c_quirks,
	.supports_bus_clear = true,
	.has_apb_dma = true,
	.tlow_std_mode = 0x4,
	.thigh_std_mode = 0x2,
	.tlow_fast_fastplus_mode = 0x4,
	.thigh_fast_fastplus_mode = 0x2,
	.setup_hold_समय_std_mode = 0x0,
	.setup_hold_समय_fast_fast_plus_mode = 0x0,
	.setup_hold_समय_hs_mode = 0x0,
	.has_पूर्णांकerface_timing_reg = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_i2c_hw_feature tegra124_i2c_hw = अणु
	.has_जारी_xfer_support = true,
	.has_per_pkt_xfer_complete_irq = true,
	.clk_भागisor_hs_mode = 1,
	.clk_भागisor_std_mode = 0x19,
	.clk_भागisor_fast_mode = 0x19,
	.clk_भागisor_fast_plus_mode = 0x10,
	.has_config_load_reg = true,
	.has_multi_master_mode = false,
	.has_slcg_override_reg = true,
	.has_mst_fअगरo = false,
	.quirks = &tegra_i2c_quirks,
	.supports_bus_clear = true,
	.has_apb_dma = true,
	.tlow_std_mode = 0x4,
	.thigh_std_mode = 0x2,
	.tlow_fast_fastplus_mode = 0x4,
	.thigh_fast_fastplus_mode = 0x2,
	.setup_hold_समय_std_mode = 0x0,
	.setup_hold_समय_fast_fast_plus_mode = 0x0,
	.setup_hold_समय_hs_mode = 0x0,
	.has_पूर्णांकerface_timing_reg = true,
पूर्ण;

अटल स्थिर काष्ठा tegra_i2c_hw_feature tegra210_i2c_hw = अणु
	.has_जारी_xfer_support = true,
	.has_per_pkt_xfer_complete_irq = true,
	.clk_भागisor_hs_mode = 1,
	.clk_भागisor_std_mode = 0x19,
	.clk_भागisor_fast_mode = 0x19,
	.clk_भागisor_fast_plus_mode = 0x10,
	.has_config_load_reg = true,
	.has_multi_master_mode = false,
	.has_slcg_override_reg = true,
	.has_mst_fअगरo = false,
	.quirks = &tegra_i2c_quirks,
	.supports_bus_clear = true,
	.has_apb_dma = true,
	.tlow_std_mode = 0x4,
	.thigh_std_mode = 0x2,
	.tlow_fast_fastplus_mode = 0x4,
	.thigh_fast_fastplus_mode = 0x2,
	.setup_hold_समय_std_mode = 0,
	.setup_hold_समय_fast_fast_plus_mode = 0,
	.setup_hold_समय_hs_mode = 0,
	.has_पूर्णांकerface_timing_reg = true,
पूर्ण;

अटल स्थिर काष्ठा tegra_i2c_hw_feature tegra186_i2c_hw = अणु
	.has_जारी_xfer_support = true,
	.has_per_pkt_xfer_complete_irq = true,
	.clk_भागisor_hs_mode = 1,
	.clk_भागisor_std_mode = 0x16,
	.clk_भागisor_fast_mode = 0x19,
	.clk_भागisor_fast_plus_mode = 0x10,
	.has_config_load_reg = true,
	.has_multi_master_mode = false,
	.has_slcg_override_reg = true,
	.has_mst_fअगरo = false,
	.quirks = &tegra_i2c_quirks,
	.supports_bus_clear = true,
	.has_apb_dma = false,
	.tlow_std_mode = 0x4,
	.thigh_std_mode = 0x3,
	.tlow_fast_fastplus_mode = 0x4,
	.thigh_fast_fastplus_mode = 0x2,
	.setup_hold_समय_std_mode = 0,
	.setup_hold_समय_fast_fast_plus_mode = 0,
	.setup_hold_समय_hs_mode = 0,
	.has_पूर्णांकerface_timing_reg = true,
पूर्ण;

अटल स्थिर काष्ठा tegra_i2c_hw_feature tegra194_i2c_hw = अणु
	.has_जारी_xfer_support = true,
	.has_per_pkt_xfer_complete_irq = true,
	.clk_भागisor_hs_mode = 1,
	.clk_भागisor_std_mode = 0x4f,
	.clk_भागisor_fast_mode = 0x3c,
	.clk_भागisor_fast_plus_mode = 0x16,
	.has_config_load_reg = true,
	.has_multi_master_mode = true,
	.has_slcg_override_reg = true,
	.has_mst_fअगरo = true,
	.quirks = &tegra194_i2c_quirks,
	.supports_bus_clear = true,
	.has_apb_dma = false,
	.tlow_std_mode = 0x8,
	.thigh_std_mode = 0x7,
	.tlow_fast_fastplus_mode = 0x2,
	.thigh_fast_fastplus_mode = 0x2,
	.setup_hold_समय_std_mode = 0x08080808,
	.setup_hold_समय_fast_fast_plus_mode = 0x02020202,
	.setup_hold_समय_hs_mode = 0x090909,
	.has_पूर्णांकerface_timing_reg = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_i2c_of_match[] = अणु
	अणु .compatible = "nvidia,tegra194-i2c", .data = &tegra194_i2c_hw, पूर्ण,
	अणु .compatible = "nvidia,tegra186-i2c", .data = &tegra186_i2c_hw, पूर्ण,
	अणु .compatible = "nvidia,tegra210-i2c-vi", .data = &tegra210_i2c_hw, पूर्ण,
	अणु .compatible = "nvidia,tegra210-i2c", .data = &tegra210_i2c_hw, पूर्ण,
	अणु .compatible = "nvidia,tegra124-i2c", .data = &tegra124_i2c_hw, पूर्ण,
	अणु .compatible = "nvidia,tegra114-i2c", .data = &tegra114_i2c_hw, पूर्ण,
	अणु .compatible = "nvidia,tegra30-i2c", .data = &tegra30_i2c_hw, पूर्ण,
	अणु .compatible = "nvidia,tegra20-i2c", .data = &tegra20_i2c_hw, पूर्ण,
	अणु .compatible = "nvidia,tegra20-i2c-dvc", .data = &tegra20_i2c_hw, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_i2c_of_match);

अटल व्योम tegra_i2c_parse_dt(काष्ठा tegra_i2c_dev *i2c_dev)
अणु
	काष्ठा device_node *np = i2c_dev->dev->of_node;
	bool multi_mode;
	पूर्णांक err;

	err = of_property_पढ़ो_u32(np, "clock-frequency",
				   &i2c_dev->bus_clk_rate);
	अगर (err)
		i2c_dev->bus_clk_rate = I2C_MAX_STANDARD_MODE_FREQ;

	multi_mode = of_property_पढ़ो_bool(np, "multi-master");
	i2c_dev->multimaster_mode = multi_mode;

	अगर (of_device_is_compatible(np, "nvidia,tegra20-i2c-dvc"))
		i2c_dev->is_dvc = true;

	अगर (of_device_is_compatible(np, "nvidia,tegra210-i2c-vi"))
		i2c_dev->is_vi = true;
पूर्ण

अटल पूर्णांक tegra_i2c_init_घड़ीs(काष्ठा tegra_i2c_dev *i2c_dev)
अणु
	पूर्णांक err;

	i2c_dev->घड़ीs[i2c_dev->nघड़ीs++].id = "div-clk";

	अगर (i2c_dev->hw == &tegra20_i2c_hw || i2c_dev->hw == &tegra30_i2c_hw)
		i2c_dev->घड़ीs[i2c_dev->nघड़ीs++].id = "fast-clk";

	अगर (i2c_dev->is_vi)
		i2c_dev->घड़ीs[i2c_dev->nघड़ीs++].id = "slow";

	err = devm_clk_bulk_get(i2c_dev->dev, i2c_dev->nघड़ीs,
				i2c_dev->घड़ीs);
	अगर (err)
		वापस err;

	err = clk_bulk_prepare(i2c_dev->nघड़ीs, i2c_dev->घड़ीs);
	अगर (err)
		वापस err;

	i2c_dev->भाग_clk = i2c_dev->घड़ीs[0].clk;

	अगर (!i2c_dev->multimaster_mode)
		वापस 0;

	err = clk_enable(i2c_dev->भाग_clk);
	अगर (err) अणु
		dev_err(i2c_dev->dev, "failed to enable div-clk: %d\n", err);
		जाओ unprepare_घड़ीs;
	पूर्ण

	वापस 0;

unprepare_घड़ीs:
	clk_bulk_unprepare(i2c_dev->nघड़ीs, i2c_dev->घड़ीs);

	वापस err;
पूर्ण

अटल व्योम tegra_i2c_release_घड़ीs(काष्ठा tegra_i2c_dev *i2c_dev)
अणु
	अगर (i2c_dev->multimaster_mode)
		clk_disable(i2c_dev->भाग_clk);

	clk_bulk_unprepare(i2c_dev->nघड़ीs, i2c_dev->घड़ीs);
पूर्ण

अटल पूर्णांक tegra_i2c_init_hardware(काष्ठा tegra_i2c_dev *i2c_dev)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(i2c_dev->dev);
	अगर (ret < 0)
		dev_err(i2c_dev->dev, "runtime resume failed: %d\n", ret);
	अन्यथा
		ret = tegra_i2c_init(i2c_dev);

	pm_runसमय_put(i2c_dev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_i2c_dev *i2c_dev;
	काष्ठा resource *res;
	पूर्णांक err;

	i2c_dev = devm_kzalloc(&pdev->dev, माप(*i2c_dev), GFP_KERNEL);
	अगर (!i2c_dev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, i2c_dev);

	init_completion(&i2c_dev->msg_complete);
	init_completion(&i2c_dev->dma_complete);

	i2c_dev->hw = of_device_get_match_data(&pdev->dev);
	i2c_dev->cont_id = pdev->id;
	i2c_dev->dev = &pdev->dev;

	i2c_dev->base = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &res);
	अगर (IS_ERR(i2c_dev->base))
		वापस PTR_ERR(i2c_dev->base);

	i2c_dev->base_phys = res->start;

	err = platक्रमm_get_irq(pdev, 0);
	अगर (err < 0)
		वापस err;

	i2c_dev->irq = err;

	/* पूर्णांकerrupt will be enabled during of transfer समय */
	irq_set_status_flags(i2c_dev->irq, IRQ_NOAUTOEN);

	err = devm_request_thपढ़ोed_irq(i2c_dev->dev, i2c_dev->irq,
					शून्य, tegra_i2c_isr,
					IRQF_NO_SUSPEND | IRQF_ONESHOT,
					dev_name(i2c_dev->dev), i2c_dev);
	अगर (err)
		वापस err;

	i2c_dev->rst = devm_reset_control_get_exclusive(i2c_dev->dev, "i2c");
	अगर (IS_ERR(i2c_dev->rst)) अणु
		dev_err_probe(i2c_dev->dev, PTR_ERR(i2c_dev->rst),
			      "failed to get reset control\n");
		वापस PTR_ERR(i2c_dev->rst);
	पूर्ण

	tegra_i2c_parse_dt(i2c_dev);

	err = tegra_i2c_init_घड़ीs(i2c_dev);
	अगर (err)
		वापस err;

	err = tegra_i2c_init_dma(i2c_dev);
	अगर (err)
		जाओ release_घड़ीs;

	/*
	 * VI I2C is in VE घातer करोमुख्य which is not always ON and not
	 * IRQ-safe.  Thus, IRQ-safe device shouldn't be attached to a
	 * non IRQ-safe करोमुख्य because this prevents घातering off the घातer
	 * करोमुख्य.
	 *
	 * VI I2C device shouldn't be marked as IRQ-safe because VI I2C won't
	 * be used क्रम atomic transfers.
	 */
	अगर (!i2c_dev->is_vi)
		pm_runसमय_irq_safe(i2c_dev->dev);

	pm_runसमय_enable(i2c_dev->dev);

	err = tegra_i2c_init_hardware(i2c_dev);
	अगर (err)
		जाओ release_rpm;

	i2c_set_adapdata(&i2c_dev->adapter, i2c_dev);
	i2c_dev->adapter.dev.of_node = i2c_dev->dev->of_node;
	i2c_dev->adapter.dev.parent = i2c_dev->dev;
	i2c_dev->adapter.retries = 1;
	i2c_dev->adapter.समयout = 6 * HZ;
	i2c_dev->adapter.quirks = i2c_dev->hw->quirks;
	i2c_dev->adapter.owner = THIS_MODULE;
	i2c_dev->adapter.class = I2C_CLASS_DEPRECATED;
	i2c_dev->adapter.algo = &tegra_i2c_algo;
	i2c_dev->adapter.nr = pdev->id;

	अगर (i2c_dev->hw->supports_bus_clear)
		i2c_dev->adapter.bus_recovery_info = &tegra_i2c_recovery_info;

	strlcpy(i2c_dev->adapter.name, dev_name(i2c_dev->dev),
		माप(i2c_dev->adapter.name));

	err = i2c_add_numbered_adapter(&i2c_dev->adapter);
	अगर (err)
		जाओ release_rpm;

	वापस 0;

release_rpm:
	pm_runसमय_disable(i2c_dev->dev);

	tegra_i2c_release_dma(i2c_dev);
release_घड़ीs:
	tegra_i2c_release_घड़ीs(i2c_dev);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_i2c_dev *i2c_dev = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&i2c_dev->adapter);
	pm_runसमय_disable(i2c_dev->dev);

	tegra_i2c_release_dma(i2c_dev);
	tegra_i2c_release_घड़ीs(i2c_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_i2c_dev *i2c_dev = dev_get_drvdata(dev);
	पूर्णांक err;

	err = pinctrl_pm_select_शेष_state(dev);
	अगर (err)
		वापस err;

	err = clk_bulk_enable(i2c_dev->nघड़ीs, i2c_dev->घड़ीs);
	अगर (err)
		वापस err;

	/*
	 * VI I2C device is attached to VE घातer करोमुख्य which goes through
	 * घातer ON/OFF during runसमय PM resume/suspend, meaning that
	 * controller needs to be re-initialized after घातer ON.
	 */
	अगर (i2c_dev->is_vi) अणु
		err = tegra_i2c_init(i2c_dev);
		अगर (err)
			जाओ disable_घड़ीs;
	पूर्ण

	वापस 0;

disable_घड़ीs:
	clk_bulk_disable(i2c_dev->nघड़ीs, i2c_dev->घड़ीs);

	वापस err;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_i2c_dev *i2c_dev = dev_get_drvdata(dev);

	clk_bulk_disable(i2c_dev->nघड़ीs, i2c_dev->घड़ीs);

	वापस pinctrl_pm_select_idle_state(dev);
पूर्ण

अटल पूर्णांक __maybe_unused tegra_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_i2c_dev *i2c_dev = dev_get_drvdata(dev);
	पूर्णांक err;

	i2c_mark_adapter_suspended(&i2c_dev->adapter);

	अगर (!pm_runसमय_status_suspended(dev)) अणु
		err = tegra_i2c_runसमय_suspend(dev);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_i2c_dev *i2c_dev = dev_get_drvdata(dev);
	पूर्णांक err;

	/*
	 * We need to ensure that घड़ीs are enabled so that रेजिस्टरs can be
	 * restored in tegra_i2c_init().
	 */
	err = tegra_i2c_runसमय_resume(dev);
	अगर (err)
		वापस err;

	err = tegra_i2c_init(i2c_dev);
	अगर (err)
		वापस err;

	/*
	 * In हाल we are runसमय suspended, disable घड़ीs again so that we
	 * करोn't unbalance the घड़ी reference counts during the next runसमय
	 * resume transition.
	 */
	अगर (pm_runसमय_status_suspended(dev)) अणु
		err = tegra_i2c_runसमय_suspend(dev);
		अगर (err)
			वापस err;
	पूर्ण

	i2c_mark_adapter_resumed(&i2c_dev->adapter);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_i2c_pm = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(tegra_i2c_suspend, tegra_i2c_resume)
	SET_RUNTIME_PM_OPS(tegra_i2c_runसमय_suspend, tegra_i2c_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_i2c_driver = अणु
	.probe = tegra_i2c_probe,
	.हटाओ = tegra_i2c_हटाओ,
	.driver = अणु
		.name = "tegra-i2c",
		.of_match_table = tegra_i2c_of_match,
		.pm = &tegra_i2c_pm,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_i2c_driver);

MODULE_DESCRIPTION("NVIDIA Tegra I2C Bus Controller driver");
MODULE_AUTHOR("Colin Cross");
MODULE_LICENSE("GPL v2");
