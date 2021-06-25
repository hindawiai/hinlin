<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019, Linaro Limited

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/slimbus.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश "bus.h"

#घोषणा SWRM_COMP_HW_VERSION					0x00
#घोषणा SWRM_COMP_CFG_ADDR					0x04
#घोषणा SWRM_COMP_CFG_IRQ_LEVEL_OR_PULSE_MSK			BIT(1)
#घोषणा SWRM_COMP_CFG_ENABLE_MSK				BIT(0)
#घोषणा SWRM_COMP_PARAMS					0x100
#घोषणा SWRM_COMP_PARAMS_WR_FIFO_DEPTH				GENMASK(14, 10)
#घोषणा SWRM_COMP_PARAMS_RD_FIFO_DEPTH				GENMASK(19, 15)
#घोषणा SWRM_COMP_PARAMS_DOUT_PORTS_MASK			GENMASK(4, 0)
#घोषणा SWRM_COMP_PARAMS_DIN_PORTS_MASK				GENMASK(9, 5)
#घोषणा SWRM_INTERRUPT_STATUS					0x200
#घोषणा SWRM_INTERRUPT_STATUS_RMSK				GENMASK(16, 0)
#घोषणा SWRM_INTERRUPT_STATUS_SLAVE_PEND_IRQ			BIT(0)
#घोषणा SWRM_INTERRUPT_STATUS_NEW_SLAVE_ATTACHED		BIT(1)
#घोषणा SWRM_INTERRUPT_STATUS_CHANGE_ENUM_SLAVE_STATUS		BIT(2)
#घोषणा SWRM_INTERRUPT_STATUS_MASTER_CLASH_DET			BIT(3)
#घोषणा SWRM_INTERRUPT_STATUS_RD_FIFO_OVERFLOW			BIT(4)
#घोषणा SWRM_INTERRUPT_STATUS_RD_FIFO_UNDERFLOW			BIT(5)
#घोषणा SWRM_INTERRUPT_STATUS_WR_CMD_FIFO_OVERFLOW		BIT(6)
#घोषणा SWRM_INTERRUPT_STATUS_CMD_ERROR				BIT(7)
#घोषणा SWRM_INTERRUPT_STATUS_DOUT_PORT_COLLISION		BIT(8)
#घोषणा SWRM_INTERRUPT_STATUS_READ_EN_RD_VALID_MISMATCH		BIT(9)
#घोषणा SWRM_INTERRUPT_STATUS_SPECIAL_CMD_ID_FINISHED		BIT(10)
#घोषणा SWRM_INTERRUPT_STATUS_BUS_RESET_FINISHED_V2             BIT(13)
#घोषणा SWRM_INTERRUPT_STATUS_CLK_STOP_FINISHED_V2              BIT(14)
#घोषणा SWRM_INTERRUPT_STATUS_EXT_CLK_STOP_WAKEUP               BIT(16)
#घोषणा SWRM_INTERRUPT_MAX					17
#घोषणा SWRM_INTERRUPT_MASK_ADDR				0x204
#घोषणा SWRM_INTERRUPT_CLEAR					0x208
#घोषणा SWRM_INTERRUPT_CPU_EN					0x210
#घोषणा SWRM_CMD_FIFO_WR_CMD					0x300
#घोषणा SWRM_CMD_FIFO_RD_CMD					0x304
#घोषणा SWRM_CMD_FIFO_CMD					0x308
#घोषणा SWRM_CMD_FIFO_FLUSH					0x1
#घोषणा SWRM_CMD_FIFO_STATUS					0x30C
#घोषणा SWRM_RD_CMD_FIFO_CNT_MASK				GENMASK(20, 16)
#घोषणा SWRM_WR_CMD_FIFO_CNT_MASK				GENMASK(12, 8)
#घोषणा SWRM_CMD_FIFO_CFG_ADDR					0x314
#घोषणा SWRM_CONTINUE_EXEC_ON_CMD_IGNORE			BIT(31)
#घोषणा SWRM_RD_WR_CMD_RETRIES					0x7
#घोषणा SWRM_CMD_FIFO_RD_FIFO_ADDR				0x318
#घोषणा SWRM_RD_FIFO_CMD_ID_MASK				GENMASK(11, 8)
#घोषणा SWRM_ENUMERATOR_CFG_ADDR				0x500
#घोषणा SWRM_ENUMERATOR_SLAVE_DEV_ID_1(m)		(0x530 + 0x8 * (m))
#घोषणा SWRM_ENUMERATOR_SLAVE_DEV_ID_2(m)		(0x534 + 0x8 * (m))
#घोषणा SWRM_MCP_FRAME_CTRL_BANK_ADDR(m)		(0x101C + 0x40 * (m))
#घोषणा SWRM_MCP_FRAME_CTRL_BANK_COL_CTRL_BMSK			GENMASK(2, 0)
#घोषणा SWRM_MCP_FRAME_CTRL_BANK_ROW_CTRL_BMSK			GENMASK(7, 3)
#घोषणा SWRM_MCP_BUS_CTRL					0x1044
#घोषणा SWRM_MCP_BUS_CLK_START					BIT(1)
#घोषणा SWRM_MCP_CFG_ADDR					0x1048
#घोषणा SWRM_MCP_CFG_MAX_NUM_OF_CMD_NO_PINGS_BMSK		GENMASK(21, 17)
#घोषणा SWRM_DEF_CMD_NO_PINGS					0x1f
#घोषणा SWRM_MCP_STATUS						0x104C
#घोषणा SWRM_MCP_STATUS_BANK_NUM_MASK				BIT(0)
#घोषणा SWRM_MCP_SLV_STATUS					0x1090
#घोषणा SWRM_MCP_SLV_STATUS_MASK				GENMASK(1, 0)
#घोषणा SWRM_MCP_SLV_STATUS_SZ					2
#घोषणा SWRM_DP_PORT_CTRL_BANK(n, m)	(0x1124 + 0x100 * (n - 1) + 0x40 * m)
#घोषणा SWRM_DP_PORT_CTRL_2_BANK(n, m)	(0x1128 + 0x100 * (n - 1) + 0x40 * m)
#घोषणा SWRM_DP_BLOCK_CTRL_1(n)		(0x112C + 0x100 * (n - 1))
#घोषणा SWRM_DP_BLOCK_CTRL2_BANK(n, m)	(0x1130 + 0x100 * (n - 1) + 0x40 * m)
#घोषणा SWRM_DP_PORT_HCTRL_BANK(n, m)	(0x1134 + 0x100 * (n - 1) + 0x40 * m)
#घोषणा SWRM_DP_BLOCK_CTRL3_BANK(n, m)	(0x1138 + 0x100 * (n - 1) + 0x40 * m)
#घोषणा SWRM_DIN_DPn_PCM_PORT_CTRL(n)	(0x1054 + 0x100 * (n - 1))

#घोषणा SWRM_DP_PORT_CTRL_EN_CHAN_SHFT				0x18
#घोषणा SWRM_DP_PORT_CTRL_OFFSET2_SHFT				0x10
#घोषणा SWRM_DP_PORT_CTRL_OFFSET1_SHFT				0x08
#घोषणा SWRM_AHB_BRIDGE_WR_DATA_0				0xc85
#घोषणा SWRM_AHB_BRIDGE_WR_ADDR_0				0xc89
#घोषणा SWRM_AHB_BRIDGE_RD_ADDR_0				0xc8d
#घोषणा SWRM_AHB_BRIDGE_RD_DATA_0				0xc91

#घोषणा SWRM_REG_VAL_PACK(data, dev, id, reg)	\
			((reg) | ((id) << 16) | ((dev) << 20) | ((data) << 24))

#घोषणा SWRM_SPECIAL_CMD_ID	0xF
#घोषणा MAX_FREQ_NUM		1
#घोषणा TIMEOUT_MS		(2 * HZ)
#घोषणा QCOM_SWRM_MAX_RD_LEN	0x1
#घोषणा QCOM_SDW_MAX_PORTS	14
#घोषणा DEFAULT_CLK_FREQ	9600000
#घोषणा SWRM_MAX_DAIS		0xF
#घोषणा SWR_INVALID_PARAM 0xFF
#घोषणा SWR_HSTOP_MAX_VAL 0xF
#घोषणा SWR_HSTART_MIN_VAL 0x0
#घोषणा SWR_BROADCAST_CMD_ID    0x0F
#घोषणा SWR_MAX_CMD_ID	14
#घोषणा MAX_FIFO_RD_RETRY 3
#घोषणा SWR_OVERFLOW_RETRY_COUNT 30

काष्ठा qcom_swrm_port_config अणु
	u8 si;
	u8 off1;
	u8 off2;
	u8 bp_mode;
	u8 hstart;
	u8 hstop;
	u8 word_length;
	u8 blk_group_count;
	u8 lane_control;
पूर्ण;

काष्ठा qcom_swrm_ctrl अणु
	काष्ठा sdw_bus bus;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	व्योम __iomem *mmio;
	काष्ठा completion broadcast;
	काष्ठा completion क्रमागतeration;
	काष्ठा work_काष्ठा slave_work;
	/* Port alloc/मुक्त lock */
	काष्ठा mutex port_lock;
	काष्ठा clk *hclk;
	u8 wr_cmd_id;
	u8 rd_cmd_id;
	पूर्णांक irq;
	अचिन्हित पूर्णांक version;
	पूर्णांक num_din_ports;
	पूर्णांक num_करोut_ports;
	पूर्णांक cols_index;
	पूर्णांक rows_index;
	अचिन्हित दीर्घ करोut_port_mask;
	अचिन्हित दीर्घ din_port_mask;
	u32 पूर्णांकr_mask;
	u8 rcmd_id;
	u8 wcmd_id;
	काष्ठा qcom_swrm_port_config pconfig[QCOM_SDW_MAX_PORTS];
	काष्ठा sdw_stream_runसमय *srunसमय[SWRM_MAX_DAIS];
	क्रमागत sdw_slave_status status[SDW_MAX_DEVICES];
	पूर्णांक (*reg_पढ़ो)(काष्ठा qcom_swrm_ctrl *ctrl, पूर्णांक reg, u32 *val);
	पूर्णांक (*reg_ग_लिखो)(काष्ठा qcom_swrm_ctrl *ctrl, पूर्णांक reg, पूर्णांक val);
	u32 slave_status;
	u32 wr_fअगरo_depth;
	u32 rd_fअगरo_depth;
पूर्ण;

काष्ठा qcom_swrm_data अणु
	u32 शेष_cols;
	u32 शेष_rows;
पूर्ण;

अटल काष्ठा qcom_swrm_data swrm_v1_3_data = अणु
	.शेष_rows = 48,
	.शेष_cols = 16,
पूर्ण;

अटल काष्ठा qcom_swrm_data swrm_v1_5_data = अणु
	.शेष_rows = 50,
	.शेष_cols = 16,
पूर्ण;

#घोषणा to_qcom_sdw(b)	container_of(b, काष्ठा qcom_swrm_ctrl, bus)

अटल पूर्णांक qcom_swrm_ahb_reg_पढ़ो(काष्ठा qcom_swrm_ctrl *ctrl, पूर्णांक reg,
				  u32 *val)
अणु
	काष्ठा regmap *wcd_regmap = ctrl->regmap;
	पूर्णांक ret;

	/* pg रेजिस्टर + offset */
	ret = regmap_bulk_ग_लिखो(wcd_regmap, SWRM_AHB_BRIDGE_RD_ADDR_0,
			  (u8 *)&reg, 4);
	अगर (ret < 0)
		वापस SDW_CMD_FAIL;

	ret = regmap_bulk_पढ़ो(wcd_regmap, SWRM_AHB_BRIDGE_RD_DATA_0,
			       val, 4);
	अगर (ret < 0)
		वापस SDW_CMD_FAIL;

	वापस SDW_CMD_OK;
पूर्ण

अटल पूर्णांक qcom_swrm_ahb_reg_ग_लिखो(काष्ठा qcom_swrm_ctrl *ctrl,
				   पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा regmap *wcd_regmap = ctrl->regmap;
	पूर्णांक ret;
	/* pg रेजिस्टर + offset */
	ret = regmap_bulk_ग_लिखो(wcd_regmap, SWRM_AHB_BRIDGE_WR_DATA_0,
			  (u8 *)&val, 4);
	अगर (ret)
		वापस SDW_CMD_FAIL;

	/* ग_लिखो address रेजिस्टर */
	ret = regmap_bulk_ग_लिखो(wcd_regmap, SWRM_AHB_BRIDGE_WR_ADDR_0,
			  (u8 *)&reg, 4);
	अगर (ret)
		वापस SDW_CMD_FAIL;

	वापस SDW_CMD_OK;
पूर्ण

अटल पूर्णांक qcom_swrm_cpu_reg_पढ़ो(काष्ठा qcom_swrm_ctrl *ctrl, पूर्णांक reg,
				  u32 *val)
अणु
	*val = पढ़ोl(ctrl->mmio + reg);
	वापस SDW_CMD_OK;
पूर्ण

अटल पूर्णांक qcom_swrm_cpu_reg_ग_लिखो(काष्ठा qcom_swrm_ctrl *ctrl, पूर्णांक reg,
				   पूर्णांक val)
अणु
	ग_लिखोl(val, ctrl->mmio + reg);
	वापस SDW_CMD_OK;
पूर्ण

अटल u32 swrm_get_packed_reg_val(u8 *cmd_id, u8 cmd_data,
				   u8 dev_addr, u16 reg_addr)
अणु
	u32 val;
	u8 id = *cmd_id;

	अगर (id != SWR_BROADCAST_CMD_ID) अणु
		अगर (id < SWR_MAX_CMD_ID)
			id += 1;
		अन्यथा
			id = 0;
		*cmd_id = id;
	पूर्ण
	val = SWRM_REG_VAL_PACK(cmd_data, dev_addr, id, reg_addr);

	वापस val;
पूर्ण

अटल पूर्णांक swrm_रुको_क्रम_rd_fअगरo_avail(काष्ठा qcom_swrm_ctrl *swrm)
अणु
	u32 fअगरo_outstanding_data, value;
	पूर्णांक fअगरo_retry_count = SWR_OVERFLOW_RETRY_COUNT;

	करो अणु
		/* Check क्रम fअगरo underflow during पढ़ो */
		swrm->reg_पढ़ो(swrm, SWRM_CMD_FIFO_STATUS, &value);
		fअगरo_outstanding_data = FIELD_GET(SWRM_RD_CMD_FIFO_CNT_MASK, value);

		/* Check अगर पढ़ो data is available in पढ़ो fअगरo */
		अगर (fअगरo_outstanding_data > 0)
			वापस 0;

		usleep_range(500, 510);
	पूर्ण जबतक (fअगरo_retry_count--);

	अगर (fअगरo_outstanding_data == 0) अणु
		dev_err_ratelimited(swrm->dev, "%s err read underflow\n", __func__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक swrm_रुको_क्रम_wr_fअगरo_avail(काष्ठा qcom_swrm_ctrl *swrm)
अणु
	u32 fअगरo_outstanding_cmds, value;
	पूर्णांक fअगरo_retry_count = SWR_OVERFLOW_RETRY_COUNT;

	करो अणु
		/* Check क्रम fअगरo overflow during ग_लिखो */
		swrm->reg_पढ़ो(swrm, SWRM_CMD_FIFO_STATUS, &value);
		fअगरo_outstanding_cmds = FIELD_GET(SWRM_WR_CMD_FIFO_CNT_MASK, value);

		/* Check क्रम space in ग_लिखो fअगरo beक्रमe writing */
		अगर (fअगरo_outstanding_cmds < swrm->wr_fअगरo_depth)
			वापस 0;

		usleep_range(500, 510);
	पूर्ण जबतक (fअगरo_retry_count--);

	अगर (fअगरo_outstanding_cmds == swrm->wr_fअगरo_depth) अणु
		dev_err_ratelimited(swrm->dev, "%s err write overflow\n", __func__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_swrm_cmd_fअगरo_wr_cmd(काष्ठा qcom_swrm_ctrl *swrm, u8 cmd_data,
				     u8 dev_addr, u16 reg_addr)
अणु

	u32 val;
	पूर्णांक ret = 0;
	u8 cmd_id = 0x0;

	अगर (dev_addr == SDW_BROADCAST_DEV_NUM) अणु
		cmd_id = SWR_BROADCAST_CMD_ID;
		val = swrm_get_packed_reg_val(&cmd_id, cmd_data,
					      dev_addr, reg_addr);
	पूर्ण अन्यथा अणु
		val = swrm_get_packed_reg_val(&swrm->wcmd_id, cmd_data,
					      dev_addr, reg_addr);
	पूर्ण

	अगर (swrm_रुको_क्रम_wr_fअगरo_avail(swrm))
		वापस SDW_CMD_FAIL_OTHER;

	/* Its assumed that ग_लिखो is okay as we करो not get any status back */
	swrm->reg_ग_लिखो(swrm, SWRM_CMD_FIFO_WR_CMD, val);

	/* version 1.3 or less */
	अगर (swrm->version <= 0x01030000)
		usleep_range(150, 155);

	अगर (cmd_id == SWR_BROADCAST_CMD_ID) अणु
		/*
		 * sleep क्रम 10ms क्रम MSM soundwire variant to allow broadcast
		 * command to complete.
		 */
		ret = रुको_क्रम_completion_समयout(&swrm->broadcast,
						  msecs_to_jअगरfies(TIMEOUT_MS));
		अगर (!ret)
			ret = SDW_CMD_IGNORED;
		अन्यथा
			ret = SDW_CMD_OK;

	पूर्ण अन्यथा अणु
		ret = SDW_CMD_OK;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_swrm_cmd_fअगरo_rd_cmd(काष्ठा qcom_swrm_ctrl *swrm,
				     u8 dev_addr, u16 reg_addr,
				     u32 len, u8 *rval)
अणु
	u32 cmd_data, cmd_id, val, retry_attempt = 0;

	val = swrm_get_packed_reg_val(&swrm->rcmd_id, len, dev_addr, reg_addr);

	/* रुको क्रम FIFO RD to complete to aव्योम overflow */
	usleep_range(100, 105);
	swrm->reg_ग_लिखो(swrm, SWRM_CMD_FIFO_RD_CMD, val);
	/* रुको क्रम FIFO RD CMD complete to aव्योम overflow */
	usleep_range(250, 255);

	अगर (swrm_रुको_क्रम_rd_fअगरo_avail(swrm))
		वापस SDW_CMD_FAIL_OTHER;

	करो अणु
		swrm->reg_पढ़ो(swrm, SWRM_CMD_FIFO_RD_FIFO_ADDR, &cmd_data);
		rval[0] = cmd_data & 0xFF;
		cmd_id = FIELD_GET(SWRM_RD_FIFO_CMD_ID_MASK, cmd_data);

		अगर (cmd_id != swrm->rcmd_id) अणु
			अगर (retry_attempt < (MAX_FIFO_RD_RETRY - 1)) अणु
				/* रुको 500 us beक्रमe retry on fअगरo पढ़ो failure */
				usleep_range(500, 505);
				swrm->reg_ग_लिखो(swrm, SWRM_CMD_FIFO_CMD,
						SWRM_CMD_FIFO_FLUSH);
				swrm->reg_ग_लिखो(swrm, SWRM_CMD_FIFO_RD_CMD, val);
			पूर्ण
			retry_attempt++;
		पूर्ण अन्यथा अणु
			वापस SDW_CMD_OK;
		पूर्ण

	पूर्ण जबतक (retry_attempt < MAX_FIFO_RD_RETRY);

	dev_err(swrm->dev, "failed to पढ़ो fअगरo: reg: 0x%x, rcmd_id: 0x%x,\
		dev_num: 0x%x, cmd_data: 0x%x\न",
		reg_addr, swrm->rcmd_id, dev_addr, cmd_data);

	वापस SDW_CMD_IGNORED;
पूर्ण

अटल पूर्णांक qcom_swrm_get_alert_slave_dev_num(काष्ठा qcom_swrm_ctrl *ctrl)
अणु
	u32 val, status;
	पूर्णांक dev_num;

	ctrl->reg_पढ़ो(ctrl, SWRM_MCP_SLV_STATUS, &val);

	क्रम (dev_num = 0; dev_num < SDW_MAX_DEVICES; dev_num++) अणु
		status = (val >> (dev_num * SWRM_MCP_SLV_STATUS_SZ));

		अगर ((status & SWRM_MCP_SLV_STATUS_MASK) == SDW_SLAVE_ALERT) अणु
			ctrl->status[dev_num] = status;
			वापस dev_num;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम qcom_swrm_get_device_status(काष्ठा qcom_swrm_ctrl *ctrl)
अणु
	u32 val;
	पूर्णांक i;

	ctrl->reg_पढ़ो(ctrl, SWRM_MCP_SLV_STATUS, &val);
	ctrl->slave_status = val;

	क्रम (i = 0; i < SDW_MAX_DEVICES; i++) अणु
		u32 s;

		s = (val >> (i * 2));
		s &= SWRM_MCP_SLV_STATUS_MASK;
		ctrl->status[i] = s;
	पूर्ण
पूर्ण

अटल व्योम qcom_swrm_set_slave_dev_num(काष्ठा sdw_bus *bus,
					काष्ठा sdw_slave *slave, पूर्णांक devnum)
अणु
	काष्ठा qcom_swrm_ctrl *ctrl = to_qcom_sdw(bus);
	u32 status;

	ctrl->reg_पढ़ो(ctrl, SWRM_MCP_SLV_STATUS, &status);
	status = (status >> (devnum * SWRM_MCP_SLV_STATUS_SZ));
	status &= SWRM_MCP_SLV_STATUS_MASK;

	अगर (status == SDW_SLAVE_ATTACHED) अणु
		अगर (slave)
			slave->dev_num = devnum;
		mutex_lock(&bus->bus_lock);
		set_bit(devnum, bus->asचिन्हित);
		mutex_unlock(&bus->bus_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक qcom_swrm_क्रमागतerate(काष्ठा sdw_bus *bus)
अणु
	काष्ठा qcom_swrm_ctrl *ctrl = to_qcom_sdw(bus);
	काष्ठा sdw_slave *slave, *_s;
	काष्ठा sdw_slave_id id;
	u32 val1, val2;
	bool found;
	u64 addr;
	पूर्णांक i;
	अक्षर *buf1 = (अक्षर *)&val1, *buf2 = (अक्षर *)&val2;

	क्रम (i = 1; i <= SDW_MAX_DEVICES; i++) अणु
		/*SCP_Devid5 - Devid 4*/
		ctrl->reg_पढ़ो(ctrl, SWRM_ENUMERATOR_SLAVE_DEV_ID_1(i), &val1);

		/*SCP_Devid3 - DevId 2 Devid 1 Devid 0*/
		ctrl->reg_पढ़ो(ctrl, SWRM_ENUMERATOR_SLAVE_DEV_ID_2(i), &val2);

		अगर (!val1 && !val2)
			अवरोध;

		addr = buf2[1] | (buf2[0] << 8) | (buf1[3] << 16) |
			((u64)buf1[2] << 24) | ((u64)buf1[1] << 32) |
			((u64)buf1[0] << 40);

		sdw_extract_slave_id(bus, addr, &id);
		found = false;
		/* Now compare with entries */
		list_क्रम_each_entry_safe(slave, _s, &bus->slaves, node) अणु
			अगर (sdw_compare_devid(slave, id) == 0) अणु
				qcom_swrm_set_slave_dev_num(bus, slave, i);
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			qcom_swrm_set_slave_dev_num(bus, शून्य, i);
			sdw_slave_add(bus, &id, शून्य);
		पूर्ण
	पूर्ण

	complete(&ctrl->क्रमागतeration);
	वापस 0;
पूर्ण

अटल irqवापस_t qcom_swrm_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा qcom_swrm_ctrl *swrm = dev_id;
	u32 value, पूर्णांकr_sts, पूर्णांकr_sts_masked, slave_status;
	u32 i;
	पूर्णांक devnum;
	पूर्णांक ret = IRQ_HANDLED;

	swrm->reg_पढ़ो(swrm, SWRM_INTERRUPT_STATUS, &पूर्णांकr_sts);
	पूर्णांकr_sts_masked = पूर्णांकr_sts & swrm->पूर्णांकr_mask;

	करो अणु
		क्रम (i = 0; i < SWRM_INTERRUPT_MAX; i++) अणु
			value = पूर्णांकr_sts_masked & BIT(i);
			अगर (!value)
				जारी;

			चयन (value) अणु
			हाल SWRM_INTERRUPT_STATUS_SLAVE_PEND_IRQ:
				devnum = qcom_swrm_get_alert_slave_dev_num(swrm);
				अगर (devnum < 0) अणु
					dev_err_ratelimited(swrm->dev,
					    "no slave alert found.spurious interrupt\n");
				पूर्ण अन्यथा अणु
					sdw_handle_slave_status(&swrm->bus, swrm->status);
				पूर्ण

				अवरोध;
			हाल SWRM_INTERRUPT_STATUS_NEW_SLAVE_ATTACHED:
			हाल SWRM_INTERRUPT_STATUS_CHANGE_ENUM_SLAVE_STATUS:
				dev_err_ratelimited(swrm->dev, "%s: SWR new slave attached\n",
					__func__);
				swrm->reg_पढ़ो(swrm, SWRM_MCP_SLV_STATUS, &slave_status);
				अगर (swrm->slave_status == slave_status) अणु
					dev_err(swrm->dev, "Slave status not changed %x\n",
						slave_status);
				पूर्ण अन्यथा अणु
					qcom_swrm_get_device_status(swrm);
					qcom_swrm_क्रमागतerate(&swrm->bus);
					sdw_handle_slave_status(&swrm->bus, swrm->status);
				पूर्ण
				अवरोध;
			हाल SWRM_INTERRUPT_STATUS_MASTER_CLASH_DET:
				dev_err_ratelimited(swrm->dev,
						"%s: SWR bus clsh detected\n",
						__func__);
				swrm->पूर्णांकr_mask &= ~SWRM_INTERRUPT_STATUS_MASTER_CLASH_DET;
				swrm->reg_ग_लिखो(swrm, SWRM_INTERRUPT_CPU_EN, swrm->पूर्णांकr_mask);
				अवरोध;
			हाल SWRM_INTERRUPT_STATUS_RD_FIFO_OVERFLOW:
				swrm->reg_पढ़ो(swrm, SWRM_CMD_FIFO_STATUS, &value);
				dev_err_ratelimited(swrm->dev,
					"%s: SWR read FIFO overflow fifo status 0x%x\n",
					__func__, value);
				अवरोध;
			हाल SWRM_INTERRUPT_STATUS_RD_FIFO_UNDERFLOW:
				swrm->reg_पढ़ो(swrm, SWRM_CMD_FIFO_STATUS, &value);
				dev_err_ratelimited(swrm->dev,
					"%s: SWR read FIFO underflow fifo status 0x%x\n",
					__func__, value);
				अवरोध;
			हाल SWRM_INTERRUPT_STATUS_WR_CMD_FIFO_OVERFLOW:
				swrm->reg_पढ़ो(swrm, SWRM_CMD_FIFO_STATUS, &value);
				dev_err(swrm->dev,
					"%s: SWR write FIFO overflow fifo status %x\n",
					__func__, value);
				swrm->reg_ग_लिखो(swrm, SWRM_CMD_FIFO_CMD, 0x1);
				अवरोध;
			हाल SWRM_INTERRUPT_STATUS_CMD_ERROR:
				swrm->reg_पढ़ो(swrm, SWRM_CMD_FIFO_STATUS, &value);
				dev_err_ratelimited(swrm->dev,
					"%s: SWR CMD error, fifo status 0x%x, flushing fifo\n",
					__func__, value);
				swrm->reg_ग_लिखो(swrm, SWRM_CMD_FIFO_CMD, 0x1);
				अवरोध;
			हाल SWRM_INTERRUPT_STATUS_DOUT_PORT_COLLISION:
				dev_err_ratelimited(swrm->dev,
						"%s: SWR Port collision detected\n",
						__func__);
				swrm->पूर्णांकr_mask &= ~SWRM_INTERRUPT_STATUS_DOUT_PORT_COLLISION;
				swrm->reg_ग_लिखो(swrm,
					SWRM_INTERRUPT_CPU_EN, swrm->पूर्णांकr_mask);
				अवरोध;
			हाल SWRM_INTERRUPT_STATUS_READ_EN_RD_VALID_MISMATCH:
				dev_err_ratelimited(swrm->dev,
					"%s: SWR read enable valid mismatch\n",
					__func__);
				swrm->पूर्णांकr_mask &=
					~SWRM_INTERRUPT_STATUS_READ_EN_RD_VALID_MISMATCH;
				swrm->reg_ग_लिखो(swrm,
					SWRM_INTERRUPT_CPU_EN, swrm->पूर्णांकr_mask);
				अवरोध;
			हाल SWRM_INTERRUPT_STATUS_SPECIAL_CMD_ID_FINISHED:
				complete(&swrm->broadcast);
				अवरोध;
			हाल SWRM_INTERRUPT_STATUS_BUS_RESET_FINISHED_V2:
				अवरोध;
			हाल SWRM_INTERRUPT_STATUS_CLK_STOP_FINISHED_V2:
				अवरोध;
			हाल SWRM_INTERRUPT_STATUS_EXT_CLK_STOP_WAKEUP:
				अवरोध;
			शेष:
				dev_err_ratelimited(swrm->dev,
						"%s: SWR unknown interrupt value: %d\n",
						__func__, value);
				ret = IRQ_NONE;
				अवरोध;
			पूर्ण
		पूर्ण
		swrm->reg_ग_लिखो(swrm, SWRM_INTERRUPT_CLEAR, पूर्णांकr_sts);
		swrm->reg_पढ़ो(swrm, SWRM_INTERRUPT_STATUS, &पूर्णांकr_sts);
		पूर्णांकr_sts_masked = पूर्णांकr_sts & swrm->पूर्णांकr_mask;
	पूर्ण जबतक (पूर्णांकr_sts_masked);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_swrm_init(काष्ठा qcom_swrm_ctrl *ctrl)
अणु
	u32 val;

	/* Clear Rows and Cols */
	val = FIELD_PREP(SWRM_MCP_FRAME_CTRL_BANK_ROW_CTRL_BMSK, ctrl->rows_index);
	val |= FIELD_PREP(SWRM_MCP_FRAME_CTRL_BANK_COL_CTRL_BMSK, ctrl->cols_index);

	ctrl->reg_ग_लिखो(ctrl, SWRM_MCP_FRAME_CTRL_BANK_ADDR(0), val);

	/* Enable Auto क्रमागतeration */
	ctrl->reg_ग_लिखो(ctrl, SWRM_ENUMERATOR_CFG_ADDR, 1);

	ctrl->पूर्णांकr_mask = SWRM_INTERRUPT_STATUS_RMSK;
	/* Mask soundwire पूर्णांकerrupts */
	ctrl->reg_ग_लिखो(ctrl, SWRM_INTERRUPT_MASK_ADDR,
			SWRM_INTERRUPT_STATUS_RMSK);

	/* Configure No pings */
	ctrl->reg_पढ़ो(ctrl, SWRM_MCP_CFG_ADDR, &val);
	u32p_replace_bits(&val, SWRM_DEF_CMD_NO_PINGS, SWRM_MCP_CFG_MAX_NUM_OF_CMD_NO_PINGS_BMSK);
	ctrl->reg_ग_लिखो(ctrl, SWRM_MCP_CFG_ADDR, val);

	ctrl->reg_ग_लिखो(ctrl, SWRM_MCP_BUS_CTRL, SWRM_MCP_BUS_CLK_START);
	/* Configure number of retries of a पढ़ो/ग_लिखो cmd */
	अगर (ctrl->version > 0x01050001) अणु
		/* Only क्रम versions >= 1.5.1 */
		ctrl->reg_ग_लिखो(ctrl, SWRM_CMD_FIFO_CFG_ADDR,
				SWRM_RD_WR_CMD_RETRIES |
				SWRM_CONTINUE_EXEC_ON_CMD_IGNORE);
	पूर्ण अन्यथा अणु
		ctrl->reg_ग_लिखो(ctrl, SWRM_CMD_FIFO_CFG_ADDR,
				SWRM_RD_WR_CMD_RETRIES);
	पूर्ण

	/* Set IRQ to PULSE */
	ctrl->reg_ग_लिखो(ctrl, SWRM_COMP_CFG_ADDR,
			SWRM_COMP_CFG_IRQ_LEVEL_OR_PULSE_MSK |
			SWRM_COMP_CFG_ENABLE_MSK);

	/* enable CPU IRQs */
	अगर (ctrl->mmio) अणु
		ctrl->reg_ग_लिखो(ctrl, SWRM_INTERRUPT_CPU_EN,
				SWRM_INTERRUPT_STATUS_RMSK);
	पूर्ण
	ctrl->slave_status = 0;
	ctrl->reg_पढ़ो(ctrl, SWRM_COMP_PARAMS, &val);
	ctrl->rd_fअगरo_depth = FIELD_GET(SWRM_COMP_PARAMS_RD_FIFO_DEPTH, val);
	ctrl->wr_fअगरo_depth = FIELD_GET(SWRM_COMP_PARAMS_WR_FIFO_DEPTH, val);

	वापस 0;
पूर्ण

अटल क्रमागत sdw_command_response qcom_swrm_xfer_msg(काष्ठा sdw_bus *bus,
						    काष्ठा sdw_msg *msg)
अणु
	काष्ठा qcom_swrm_ctrl *ctrl = to_qcom_sdw(bus);
	पूर्णांक ret, i, len;

	अगर (msg->flags == SDW_MSG_FLAG_READ) अणु
		क्रम (i = 0; i < msg->len;) अणु
			अगर ((msg->len - i) < QCOM_SWRM_MAX_RD_LEN)
				len = msg->len - i;
			अन्यथा
				len = QCOM_SWRM_MAX_RD_LEN;

			ret = qcom_swrm_cmd_fअगरo_rd_cmd(ctrl, msg->dev_num,
							msg->addr + i, len,
						       &msg->buf[i]);
			अगर (ret)
				वापस ret;

			i = i + len;
		पूर्ण
	पूर्ण अन्यथा अगर (msg->flags == SDW_MSG_FLAG_WRITE) अणु
		क्रम (i = 0; i < msg->len; i++) अणु
			ret = qcom_swrm_cmd_fअगरo_wr_cmd(ctrl, msg->buf[i],
							msg->dev_num,
						       msg->addr + i);
			अगर (ret)
				वापस SDW_CMD_IGNORED;
		पूर्ण
	पूर्ण

	वापस SDW_CMD_OK;
पूर्ण

अटल पूर्णांक qcom_swrm_pre_bank_चयन(काष्ठा sdw_bus *bus)
अणु
	u32 reg = SWRM_MCP_FRAME_CTRL_BANK_ADDR(bus->params.next_bank);
	काष्ठा qcom_swrm_ctrl *ctrl = to_qcom_sdw(bus);
	u32 val;

	ctrl->reg_पढ़ो(ctrl, reg, &val);

	u32p_replace_bits(&val, ctrl->cols_index, SWRM_MCP_FRAME_CTRL_BANK_COL_CTRL_BMSK);
	u32p_replace_bits(&val, ctrl->rows_index, SWRM_MCP_FRAME_CTRL_BANK_ROW_CTRL_BMSK);

	वापस ctrl->reg_ग_लिखो(ctrl, reg, val);
पूर्ण

अटल पूर्णांक qcom_swrm_port_params(काष्ठा sdw_bus *bus,
				 काष्ठा sdw_port_params *p_params,
				 अचिन्हित पूर्णांक bank)
अणु
	काष्ठा qcom_swrm_ctrl *ctrl = to_qcom_sdw(bus);

	वापस ctrl->reg_ग_लिखो(ctrl, SWRM_DP_BLOCK_CTRL_1(p_params->num),
			       p_params->bps - 1);

पूर्ण

अटल पूर्णांक qcom_swrm_transport_params(काष्ठा sdw_bus *bus,
				      काष्ठा sdw_transport_params *params,
				      क्रमागत sdw_reg_bank bank)
अणु
	काष्ठा qcom_swrm_ctrl *ctrl = to_qcom_sdw(bus);
	काष्ठा qcom_swrm_port_config *pcfg;
	u32 value;
	पूर्णांक reg = SWRM_DP_PORT_CTRL_BANK((params->port_num), bank);
	पूर्णांक ret;

	pcfg = &ctrl->pconfig[params->port_num];

	value = pcfg->off1 << SWRM_DP_PORT_CTRL_OFFSET1_SHFT;
	value |= pcfg->off2 << SWRM_DP_PORT_CTRL_OFFSET2_SHFT;
	value |= pcfg->si;

	ret = ctrl->reg_ग_लिखो(ctrl, reg, value);
	अगर (ret)
		जाओ err;

	अगर (pcfg->lane_control != SWR_INVALID_PARAM) अणु
		reg = SWRM_DP_PORT_CTRL_2_BANK(params->port_num, bank);
		value = pcfg->lane_control;
		ret = ctrl->reg_ग_लिखो(ctrl, reg, value);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (pcfg->blk_group_count != SWR_INVALID_PARAM) अणु
		reg = SWRM_DP_BLOCK_CTRL2_BANK(params->port_num, bank);
		value = pcfg->blk_group_count;
		ret = ctrl->reg_ग_लिखो(ctrl, reg, value);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (pcfg->hstart != SWR_INVALID_PARAM
			&& pcfg->hstop != SWR_INVALID_PARAM) अणु
		reg = SWRM_DP_PORT_HCTRL_BANK(params->port_num, bank);
		value = (pcfg->hstop << 4) | pcfg->hstart;
		ret = ctrl->reg_ग_लिखो(ctrl, reg, value);
	पूर्ण अन्यथा अणु
		reg = SWRM_DP_PORT_HCTRL_BANK(params->port_num, bank);
		value = (SWR_HSTOP_MAX_VAL << 4) | SWR_HSTART_MIN_VAL;
		ret = ctrl->reg_ग_लिखो(ctrl, reg, value);
	पूर्ण

	अगर (ret)
		जाओ err;

	अगर (pcfg->bp_mode != SWR_INVALID_PARAM) अणु
		reg = SWRM_DP_BLOCK_CTRL3_BANK(params->port_num, bank);
		ret = ctrl->reg_ग_लिखो(ctrl, reg, pcfg->bp_mode);
	पूर्ण

err:
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_swrm_port_enable(काष्ठा sdw_bus *bus,
				 काष्ठा sdw_enable_ch *enable_ch,
				 अचिन्हित पूर्णांक bank)
अणु
	u32 reg = SWRM_DP_PORT_CTRL_BANK(enable_ch->port_num, bank);
	काष्ठा qcom_swrm_ctrl *ctrl = to_qcom_sdw(bus);
	u32 val;

	ctrl->reg_पढ़ो(ctrl, reg, &val);

	अगर (enable_ch->enable)
		val |= (enable_ch->ch_mask << SWRM_DP_PORT_CTRL_EN_CHAN_SHFT);
	अन्यथा
		val &= ~(0xff << SWRM_DP_PORT_CTRL_EN_CHAN_SHFT);

	वापस ctrl->reg_ग_लिखो(ctrl, reg, val);
पूर्ण

अटल स्थिर काष्ठा sdw_master_port_ops qcom_swrm_port_ops = अणु
	.dpn_set_port_params = qcom_swrm_port_params,
	.dpn_set_port_transport_params = qcom_swrm_transport_params,
	.dpn_port_enable_ch = qcom_swrm_port_enable,
पूर्ण;

अटल स्थिर काष्ठा sdw_master_ops qcom_swrm_ops = अणु
	.xfer_msg = qcom_swrm_xfer_msg,
	.pre_bank_चयन = qcom_swrm_pre_bank_चयन,
पूर्ण;

अटल पूर्णांक qcom_swrm_compute_params(काष्ठा sdw_bus *bus)
अणु
	काष्ठा qcom_swrm_ctrl *ctrl = to_qcom_sdw(bus);
	काष्ठा sdw_master_runसमय *m_rt;
	काष्ठा sdw_slave_runसमय *s_rt;
	काष्ठा sdw_port_runसमय *p_rt;
	काष्ठा qcom_swrm_port_config *pcfg;
	काष्ठा sdw_slave *slave;
	अचिन्हित पूर्णांक m_port;
	पूर्णांक i = 1;

	list_क्रम_each_entry(m_rt, &bus->m_rt_list, bus_node) अणु
		list_क्रम_each_entry(p_rt, &m_rt->port_list, port_node) अणु
			pcfg = &ctrl->pconfig[p_rt->num];
			p_rt->transport_params.port_num = p_rt->num;
			अगर (pcfg->word_length != SWR_INVALID_PARAM) अणु
				sdw_fill_port_params(&p_rt->port_params,
					     p_rt->num,  pcfg->word_length + 1,
					     SDW_PORT_FLOW_MODE_ISOCH,
					     SDW_PORT_DATA_MODE_NORMAL);
			पूर्ण

		पूर्ण

		list_क्रम_each_entry(s_rt, &m_rt->slave_rt_list, m_rt_node) अणु
			slave = s_rt->slave;
			list_क्रम_each_entry(p_rt, &s_rt->port_list, port_node) अणु
				m_port = slave->m_port_map[p_rt->num];
				/* port config starts at offset 0 so -1 from actual port number */
				अगर (m_port)
					pcfg = &ctrl->pconfig[m_port];
				अन्यथा
					pcfg = &ctrl->pconfig[i];
				p_rt->transport_params.port_num = p_rt->num;
				p_rt->transport_params.sample_पूर्णांकerval =
					pcfg->si + 1;
				p_rt->transport_params.offset1 = pcfg->off1;
				p_rt->transport_params.offset2 = pcfg->off2;
				p_rt->transport_params.blk_pkg_mode = pcfg->bp_mode;
				p_rt->transport_params.blk_grp_ctrl = pcfg->blk_group_count;

				p_rt->transport_params.hstart = pcfg->hstart;
				p_rt->transport_params.hstop = pcfg->hstop;
				p_rt->transport_params.lane_ctrl = pcfg->lane_control;
				अगर (pcfg->word_length != SWR_INVALID_PARAM) अणु
					sdw_fill_port_params(&p_rt->port_params,
						     p_rt->num,
						     pcfg->word_length + 1,
						     SDW_PORT_FLOW_MODE_ISOCH,
						     SDW_PORT_DATA_MODE_NORMAL);
				पूर्ण
				i++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 qcom_swrm_freq_tbl[MAX_FREQ_NUM] = अणु
	DEFAULT_CLK_FREQ,
पूर्ण;

अटल व्योम qcom_swrm_stream_मुक्त_ports(काष्ठा qcom_swrm_ctrl *ctrl,
					काष्ठा sdw_stream_runसमय *stream)
अणु
	काष्ठा sdw_master_runसमय *m_rt;
	काष्ठा sdw_port_runसमय *p_rt;
	अचिन्हित दीर्घ *port_mask;

	mutex_lock(&ctrl->port_lock);

	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		अगर (m_rt->direction == SDW_DATA_सूची_RX)
			port_mask = &ctrl->करोut_port_mask;
		अन्यथा
			port_mask = &ctrl->din_port_mask;

		list_क्रम_each_entry(p_rt, &m_rt->port_list, port_node)
			clear_bit(p_rt->num, port_mask);
	पूर्ण

	mutex_unlock(&ctrl->port_lock);
पूर्ण

अटल पूर्णांक qcom_swrm_stream_alloc_ports(काष्ठा qcom_swrm_ctrl *ctrl,
					काष्ठा sdw_stream_runसमय *stream,
				       काष्ठा snd_pcm_hw_params *params,
				       पूर्णांक direction)
अणु
	काष्ठा sdw_port_config pconfig[QCOM_SDW_MAX_PORTS];
	काष्ठा sdw_stream_config sconfig;
	काष्ठा sdw_master_runसमय *m_rt;
	काष्ठा sdw_slave_runसमय *s_rt;
	काष्ठा sdw_port_runसमय *p_rt;
	काष्ठा sdw_slave *slave;
	अचिन्हित दीर्घ *port_mask;
	पूर्णांक i, maxport, pn, nports = 0, ret = 0;
	अचिन्हित पूर्णांक m_port;

	mutex_lock(&ctrl->port_lock);
	list_क्रम_each_entry(m_rt, &stream->master_list, stream_node) अणु
		अगर (m_rt->direction == SDW_DATA_सूची_RX) अणु
			maxport = ctrl->num_करोut_ports;
			port_mask = &ctrl->करोut_port_mask;
		पूर्ण अन्यथा अणु
			maxport = ctrl->num_din_ports;
			port_mask = &ctrl->din_port_mask;
		पूर्ण

		list_क्रम_each_entry(s_rt, &m_rt->slave_rt_list, m_rt_node) अणु
			slave = s_rt->slave;
			list_क्रम_each_entry(p_rt, &s_rt->port_list, port_node) अणु
				m_port = slave->m_port_map[p_rt->num];
				/* Port numbers start from 1 - 14*/
				अगर (m_port)
					pn = m_port;
				अन्यथा
					pn = find_first_zero_bit(port_mask, maxport);

				अगर (pn > maxport) अणु
					dev_err(ctrl->dev, "All ports busy\n");
					ret = -EBUSY;
					जाओ err;
				पूर्ण
				set_bit(pn, port_mask);
				pconfig[nports].num = pn;
				pconfig[nports].ch_mask = p_rt->ch_mask;
				nports++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (direction == SNDRV_PCM_STREAM_CAPTURE)
		sconfig.direction = SDW_DATA_सूची_TX;
	अन्यथा
		sconfig.direction = SDW_DATA_सूची_RX;

	/* hw parameters wil be ignored as we only support PDM */
	sconfig.ch_count = 1;
	sconfig.frame_rate = params_rate(params);
	sconfig.type = stream->type;
	sconfig.bps = 1;
	sdw_stream_add_master(&ctrl->bus, &sconfig, pconfig,
			      nports, stream);
err:
	अगर (ret) अणु
		क्रम (i = 0; i < nports; i++)
			clear_bit(pconfig[i].num, port_mask);
	पूर्ण

	mutex_unlock(&ctrl->port_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_swrm_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा qcom_swrm_ctrl *ctrl = dev_get_drvdata(dai->dev);
	काष्ठा sdw_stream_runसमय *srunसमय = ctrl->srunसमय[dai->id];
	पूर्णांक ret;

	ret = qcom_swrm_stream_alloc_ports(ctrl, srunसमय, params,
					   substream->stream);
	अगर (ret)
		qcom_swrm_stream_मुक्त_ports(ctrl, srunसमय);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_swrm_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा qcom_swrm_ctrl *ctrl = dev_get_drvdata(dai->dev);
	काष्ठा sdw_stream_runसमय *srunसमय = ctrl->srunसमय[dai->id];

	qcom_swrm_stream_मुक्त_ports(ctrl, srunसमय);
	sdw_stream_हटाओ_master(&ctrl->bus, srunसमय);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_swrm_set_sdw_stream(काष्ठा snd_soc_dai *dai,
				    व्योम *stream, पूर्णांक direction)
अणु
	काष्ठा qcom_swrm_ctrl *ctrl = dev_get_drvdata(dai->dev);

	ctrl->srunसमय[dai->id] = stream;

	वापस 0;
पूर्ण

अटल व्योम *qcom_swrm_get_sdw_stream(काष्ठा snd_soc_dai *dai, पूर्णांक direction)
अणु
	काष्ठा qcom_swrm_ctrl *ctrl = dev_get_drvdata(dai->dev);

	वापस ctrl->srunसमय[dai->id];
पूर्ण

अटल पूर्णांक qcom_swrm_startup(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा qcom_swrm_ctrl *ctrl = dev_get_drvdata(dai->dev);
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा sdw_stream_runसमय *srunसमय;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक ret, i;

	srunसमय = sdw_alloc_stream(dai->name);
	अगर (!srunसमय)
		वापस -ENOMEM;

	ctrl->srunसमय[dai->id] = srunसमय;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		ret = snd_soc_dai_set_sdw_stream(codec_dai, srunसमय,
						 substream->stream);
		अगर (ret < 0 && ret != -ENOTSUPP) अणु
			dev_err(dai->dev, "Failed to set sdw stream on %s\n",
				codec_dai->name);
			sdw_release_stream(srunसमय);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qcom_swrm_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा qcom_swrm_ctrl *ctrl = dev_get_drvdata(dai->dev);

	sdw_release_stream(ctrl->srunसमय[dai->id]);
	ctrl->srunसमय[dai->id] = शून्य;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops qcom_swrm_pdm_dai_ops = अणु
	.hw_params = qcom_swrm_hw_params,
	.hw_मुक्त = qcom_swrm_hw_मुक्त,
	.startup = qcom_swrm_startup,
	.shutकरोwn = qcom_swrm_shutकरोwn,
	.set_sdw_stream = qcom_swrm_set_sdw_stream,
	.get_sdw_stream = qcom_swrm_get_sdw_stream,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver qcom_swrm_dai_component = अणु
	.name = "soundwire",
पूर्ण;

अटल पूर्णांक qcom_swrm_रेजिस्टर_dais(काष्ठा qcom_swrm_ctrl *ctrl)
अणु
	पूर्णांक num_dais = ctrl->num_करोut_ports + ctrl->num_din_ports;
	काष्ठा snd_soc_dai_driver *dais;
	काष्ठा snd_soc_pcm_stream *stream;
	काष्ठा device *dev = ctrl->dev;
	पूर्णांक i;

	/* PDM dais are only tested क्रम now */
	dais = devm_kसुस्मृति(dev, num_dais, माप(*dais), GFP_KERNEL);
	अगर (!dais)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_dais; i++) अणु
		dais[i].name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "SDW Pin%d", i);
		अगर (!dais[i].name)
			वापस -ENOMEM;

		अगर (i < ctrl->num_करोut_ports)
			stream = &dais[i].playback;
		अन्यथा
			stream = &dais[i].capture;

		stream->channels_min = 1;
		stream->channels_max = 1;
		stream->rates = SNDRV_PCM_RATE_48000;
		stream->क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;

		dais[i].ops = &qcom_swrm_pdm_dai_ops;
		dais[i].id = i;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(ctrl->dev,
						&qcom_swrm_dai_component,
						dais, num_dais);
पूर्ण

अटल पूर्णांक qcom_swrm_get_port_config(काष्ठा qcom_swrm_ctrl *ctrl)
अणु
	काष्ठा device_node *np = ctrl->dev->of_node;
	u8 off1[QCOM_SDW_MAX_PORTS];
	u8 off2[QCOM_SDW_MAX_PORTS];
	u8 si[QCOM_SDW_MAX_PORTS];
	u8 bp_mode[QCOM_SDW_MAX_PORTS] = अणु 0, पूर्ण;
	u8 hstart[QCOM_SDW_MAX_PORTS];
	u8 hstop[QCOM_SDW_MAX_PORTS];
	u8 word_length[QCOM_SDW_MAX_PORTS];
	u8 blk_group_count[QCOM_SDW_MAX_PORTS];
	u8 lane_control[QCOM_SDW_MAX_PORTS];
	पूर्णांक i, ret, nports, val;

	ctrl->reg_पढ़ो(ctrl, SWRM_COMP_PARAMS, &val);

	ctrl->num_करोut_ports = FIELD_GET(SWRM_COMP_PARAMS_DOUT_PORTS_MASK, val);
	ctrl->num_din_ports = FIELD_GET(SWRM_COMP_PARAMS_DIN_PORTS_MASK, val);

	ret = of_property_पढ़ो_u32(np, "qcom,din-ports", &val);
	अगर (ret)
		वापस ret;

	अगर (val > ctrl->num_din_ports)
		वापस -EINVAL;

	ctrl->num_din_ports = val;

	ret = of_property_पढ़ो_u32(np, "qcom,dout-ports", &val);
	अगर (ret)
		वापस ret;

	अगर (val > ctrl->num_करोut_ports)
		वापस -EINVAL;

	ctrl->num_करोut_ports = val;

	nports = ctrl->num_करोut_ports + ctrl->num_din_ports;
	/* Valid port numbers are from 1-14, so mask out port 0 explicitly */
	set_bit(0, &ctrl->करोut_port_mask);
	set_bit(0, &ctrl->din_port_mask);

	ret = of_property_पढ़ो_u8_array(np, "qcom,ports-offset1",
					off1, nports);
	अगर (ret)
		वापस ret;

	ret = of_property_पढ़ो_u8_array(np, "qcom,ports-offset2",
					off2, nports);
	अगर (ret)
		वापस ret;

	ret = of_property_पढ़ो_u8_array(np, "qcom,ports-sinterval-low",
					si, nports);
	अगर (ret)
		वापस ret;

	ret = of_property_पढ़ो_u8_array(np, "qcom,ports-block-pack-mode",
					bp_mode, nports);
	अगर (ret) अणु
		u32 version;

		ctrl->reg_पढ़ो(ctrl, SWRM_COMP_HW_VERSION, &version);

		अगर (version <= 0x01030000)
			स_रखो(bp_mode, SWR_INVALID_PARAM, QCOM_SDW_MAX_PORTS);
		अन्यथा
			वापस ret;
	पूर्ण

	स_रखो(hstart, SWR_INVALID_PARAM, QCOM_SDW_MAX_PORTS);
	of_property_पढ़ो_u8_array(np, "qcom,ports-hstart", hstart, nports);

	स_रखो(hstop, SWR_INVALID_PARAM, QCOM_SDW_MAX_PORTS);
	of_property_पढ़ो_u8_array(np, "qcom,ports-hstop", hstop, nports);

	स_रखो(word_length, SWR_INVALID_PARAM, QCOM_SDW_MAX_PORTS);
	of_property_पढ़ो_u8_array(np, "qcom,ports-word-length", word_length, nports);

	स_रखो(blk_group_count, SWR_INVALID_PARAM, QCOM_SDW_MAX_PORTS);
	of_property_पढ़ो_u8_array(np, "qcom,ports-block-group-count", blk_group_count, nports);

	स_रखो(lane_control, SWR_INVALID_PARAM, QCOM_SDW_MAX_PORTS);
	of_property_पढ़ो_u8_array(np, "qcom,ports-lane-control", lane_control, nports);

	क्रम (i = 0; i < nports; i++) अणु
		/* Valid port number range is from 1-14 */
		ctrl->pconfig[i + 1].si = si[i];
		ctrl->pconfig[i + 1].off1 = off1[i];
		ctrl->pconfig[i + 1].off2 = off2[i];
		ctrl->pconfig[i + 1].bp_mode = bp_mode[i];
		ctrl->pconfig[i + 1].hstart = hstart[i];
		ctrl->pconfig[i + 1].hstop = hstop[i];
		ctrl->pconfig[i + 1].word_length = word_length[i];
		ctrl->pconfig[i + 1].blk_group_count = blk_group_count[i];
		ctrl->pconfig[i + 1].lane_control = lane_control[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_swrm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdw_master_prop *prop;
	काष्ठा sdw_bus_params *params;
	काष्ठा qcom_swrm_ctrl *ctrl;
	स्थिर काष्ठा qcom_swrm_data *data;
	पूर्णांक ret;
	u32 val;

	ctrl = devm_kzalloc(dev, माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस -ENOMEM;

	data = of_device_get_match_data(dev);
	ctrl->rows_index = sdw_find_row_index(data->शेष_rows);
	ctrl->cols_index = sdw_find_col_index(data->शेष_cols);
#अगर IS_REACHABLE(CONFIG_SLIMBUS)
	अगर (dev->parent->bus == &slimbus_bus) अणु
#अन्यथा
	अगर (false) अणु
#पूर्ण_अगर
		ctrl->reg_पढ़ो = qcom_swrm_ahb_reg_पढ़ो;
		ctrl->reg_ग_लिखो = qcom_swrm_ahb_reg_ग_लिखो;
		ctrl->regmap = dev_get_regmap(dev->parent, शून्य);
		अगर (!ctrl->regmap)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		ctrl->reg_पढ़ो = qcom_swrm_cpu_reg_पढ़ो;
		ctrl->reg_ग_लिखो = qcom_swrm_cpu_reg_ग_लिखो;
		ctrl->mmio = devm_platक्रमm_ioremap_resource(pdev, 0);
		अगर (IS_ERR(ctrl->mmio))
			वापस PTR_ERR(ctrl->mmio);
	पूर्ण

	ctrl->irq = of_irq_get(dev->of_node, 0);
	अगर (ctrl->irq < 0) अणु
		ret = ctrl->irq;
		जाओ err_init;
	पूर्ण

	ctrl->hclk = devm_clk_get(dev, "iface");
	अगर (IS_ERR(ctrl->hclk)) अणु
		ret = PTR_ERR(ctrl->hclk);
		जाओ err_init;
	पूर्ण

	clk_prepare_enable(ctrl->hclk);

	ctrl->dev = dev;
	dev_set_drvdata(&pdev->dev, ctrl);
	mutex_init(&ctrl->port_lock);
	init_completion(&ctrl->broadcast);
	init_completion(&ctrl->क्रमागतeration);

	ctrl->bus.ops = &qcom_swrm_ops;
	ctrl->bus.port_ops = &qcom_swrm_port_ops;
	ctrl->bus.compute_params = &qcom_swrm_compute_params;

	ret = qcom_swrm_get_port_config(ctrl);
	अगर (ret)
		जाओ err_clk;

	params = &ctrl->bus.params;
	params->max_dr_freq = DEFAULT_CLK_FREQ;
	params->curr_dr_freq = DEFAULT_CLK_FREQ;
	params->col = data->शेष_cols;
	params->row = data->शेष_rows;
	ctrl->reg_पढ़ो(ctrl, SWRM_MCP_STATUS, &val);
	params->curr_bank = val & SWRM_MCP_STATUS_BANK_NUM_MASK;
	params->next_bank = !params->curr_bank;

	prop = &ctrl->bus.prop;
	prop->max_clk_freq = DEFAULT_CLK_FREQ;
	prop->num_clk_gears = 0;
	prop->num_clk_freq = MAX_FREQ_NUM;
	prop->clk_freq = &qcom_swrm_freq_tbl[0];
	prop->शेष_col = data->शेष_cols;
	prop->शेष_row = data->शेष_rows;

	ctrl->reg_पढ़ो(ctrl, SWRM_COMP_HW_VERSION, &ctrl->version);

	ret = devm_request_thपढ़ोed_irq(dev, ctrl->irq, शून्य,
					qcom_swrm_irq_handler,
					IRQF_TRIGGER_RISING |
					IRQF_ONESHOT,
					"soundwire", ctrl);
	अगर (ret) अणु
		dev_err(dev, "Failed to request soundwire irq\n");
		जाओ err_clk;
	पूर्ण

	ret = sdw_bus_master_add(&ctrl->bus, dev, dev->fwnode);
	अगर (ret) अणु
		dev_err(dev, "Failed to register Soundwire controller (%d)\n",
			ret);
		जाओ err_clk;
	पूर्ण

	qcom_swrm_init(ctrl);
	रुको_क्रम_completion_समयout(&ctrl->क्रमागतeration,
				    msecs_to_jअगरfies(TIMEOUT_MS));
	ret = qcom_swrm_रेजिस्टर_dais(ctrl);
	अगर (ret)
		जाओ err_master_add;

	dev_info(dev, "Qualcomm Soundwire controller v%x.%x.%x Registered\n",
		 (ctrl->version >> 24) & 0xff, (ctrl->version >> 16) & 0xff,
		 ctrl->version & 0xffff);

	वापस 0;

err_master_add:
	sdw_bus_master_delete(&ctrl->bus);
err_clk:
	clk_disable_unprepare(ctrl->hclk);
err_init:
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_swrm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_swrm_ctrl *ctrl = dev_get_drvdata(&pdev->dev);

	sdw_bus_master_delete(&ctrl->bus);
	clk_disable_unprepare(ctrl->hclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_swrm_of_match[] = अणु
	अणु .compatible = "qcom,soundwire-v1.3.0", .data = &swrm_v1_3_data पूर्ण,
	अणु .compatible = "qcom,soundwire-v1.5.1", .data = &swrm_v1_5_data पूर्ण,
	अणु/* sentinel */पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, qcom_swrm_of_match);

अटल काष्ठा platक्रमm_driver qcom_swrm_driver = अणु
	.probe	= &qcom_swrm_probe,
	.हटाओ = &qcom_swrm_हटाओ,
	.driver = अणु
		.name	= "qcom-soundwire",
		.of_match_table = qcom_swrm_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(qcom_swrm_driver);

MODULE_DESCRIPTION("Qualcomm soundwire driver");
MODULE_LICENSE("GPL v2");
