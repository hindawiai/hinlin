<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 Synopsys, Inc. and/or its affiliates.
 *
 * Author: Vitor Soares <vitor.soares@synopsys.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i3c/master.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#घोषणा DEVICE_CTRL			0x0
#घोषणा DEV_CTRL_ENABLE			BIT(31)
#घोषणा DEV_CTRL_RESUME			BIT(30)
#घोषणा DEV_CTRL_HOT_JOIN_NACK		BIT(8)
#घोषणा DEV_CTRL_I2C_SLAVE_PRESENT	BIT(7)

#घोषणा DEVICE_ADDR			0x4
#घोषणा DEV_ADDR_DYNAMIC_ADDR_VALID	BIT(31)
#घोषणा DEV_ADDR_DYNAMIC(x)		(((x) << 16) & GENMASK(22, 16))

#घोषणा HW_CAPABILITY			0x8
#घोषणा COMMAND_QUEUE_PORT		0xc
#घोषणा COMMAND_PORT_TOC		BIT(30)
#घोषणा COMMAND_PORT_READ_TRANSFER	BIT(28)
#घोषणा COMMAND_PORT_SDAP		BIT(27)
#घोषणा COMMAND_PORT_ROC		BIT(26)
#घोषणा COMMAND_PORT_SPEED(x)		(((x) << 21) & GENMASK(23, 21))
#घोषणा COMMAND_PORT_DEV_INDEX(x)	(((x) << 16) & GENMASK(20, 16))
#घोषणा COMMAND_PORT_CP			BIT(15)
#घोषणा COMMAND_PORT_CMD(x)		(((x) << 7) & GENMASK(14, 7))
#घोषणा COMMAND_PORT_TID(x)		(((x) << 3) & GENMASK(6, 3))

#घोषणा COMMAND_PORT_ARG_DATA_LEN(x)	(((x) << 16) & GENMASK(31, 16))
#घोषणा COMMAND_PORT_ARG_DATA_LEN_MAX	65536
#घोषणा COMMAND_PORT_TRANSFER_ARG	0x01

#घोषणा COMMAND_PORT_SDA_DATA_BYTE_3(x)	(((x) << 24) & GENMASK(31, 24))
#घोषणा COMMAND_PORT_SDA_DATA_BYTE_2(x)	(((x) << 16) & GENMASK(23, 16))
#घोषणा COMMAND_PORT_SDA_DATA_BYTE_1(x)	(((x) << 8) & GENMASK(15, 8))
#घोषणा COMMAND_PORT_SDA_BYTE_STRB_3	BIT(5)
#घोषणा COMMAND_PORT_SDA_BYTE_STRB_2	BIT(4)
#घोषणा COMMAND_PORT_SDA_BYTE_STRB_1	BIT(3)
#घोषणा COMMAND_PORT_SHORT_DATA_ARG	0x02

#घोषणा COMMAND_PORT_DEV_COUNT(x)	(((x) << 21) & GENMASK(25, 21))
#घोषणा COMMAND_PORT_ADDR_ASSGN_CMD	0x03

#घोषणा RESPONSE_QUEUE_PORT		0x10
#घोषणा RESPONSE_PORT_ERR_STATUS(x)	(((x) & GENMASK(31, 28)) >> 28)
#घोषणा RESPONSE_NO_ERROR		0
#घोषणा RESPONSE_ERROR_CRC		1
#घोषणा RESPONSE_ERROR_PARITY		2
#घोषणा RESPONSE_ERROR_FRAME		3
#घोषणा RESPONSE_ERROR_IBA_NACK		4
#घोषणा RESPONSE_ERROR_ADDRESS_NACK	5
#घोषणा RESPONSE_ERROR_OVER_UNDER_FLOW	6
#घोषणा RESPONSE_ERROR_TRANSF_ABORT	8
#घोषणा RESPONSE_ERROR_I2C_W_NACK_ERR	9
#घोषणा RESPONSE_PORT_TID(x)		(((x) & GENMASK(27, 24)) >> 24)
#घोषणा RESPONSE_PORT_DATA_LEN(x)	((x) & GENMASK(15, 0))

#घोषणा RX_TX_DATA_PORT			0x14
#घोषणा IBI_QUEUE_STATUS		0x18
#घोषणा QUEUE_THLD_CTRL			0x1c
#घोषणा QUEUE_THLD_CTRL_RESP_BUF_MASK	GENMASK(15, 8)
#घोषणा QUEUE_THLD_CTRL_RESP_BUF(x)	(((x) - 1) << 8)

#घोषणा DATA_BUFFER_THLD_CTRL		0x20
#घोषणा DATA_BUFFER_THLD_CTRL_RX_BUF	GENMASK(11, 8)

#घोषणा IBI_QUEUE_CTRL			0x24
#घोषणा IBI_MR_REQ_REJECT		0x2C
#घोषणा IBI_SIR_REQ_REJECT		0x30
#घोषणा IBI_REQ_REJECT_ALL		GENMASK(31, 0)

#घोषणा RESET_CTRL			0x34
#घोषणा RESET_CTRL_IBI_QUEUE		BIT(5)
#घोषणा RESET_CTRL_RX_FIFO		BIT(4)
#घोषणा RESET_CTRL_TX_FIFO		BIT(3)
#घोषणा RESET_CTRL_RESP_QUEUE		BIT(2)
#घोषणा RESET_CTRL_CMD_QUEUE		BIT(1)
#घोषणा RESET_CTRL_SOFT			BIT(0)

#घोषणा SLV_EVENT_CTRL			0x38
#घोषणा INTR_STATUS			0x3c
#घोषणा INTR_STATUS_EN			0x40
#घोषणा INTR_SIGNAL_EN			0x44
#घोषणा INTR_FORCE			0x48
#घोषणा INTR_BUSOWNER_UPDATE_STAT	BIT(13)
#घोषणा INTR_IBI_UPDATED_STAT		BIT(12)
#घोषणा INTR_READ_REQ_RECV_STAT		BIT(11)
#घोषणा INTR_DEFSLV_STAT		BIT(10)
#घोषणा INTR_TRANSFER_ERR_STAT		BIT(9)
#घोषणा INTR_DYN_ADDR_ASSGN_STAT	BIT(8)
#घोषणा INTR_CCC_UPDATED_STAT		BIT(6)
#घोषणा INTR_TRANSFER_ABORT_STAT	BIT(5)
#घोषणा INTR_RESP_READY_STAT		BIT(4)
#घोषणा INTR_CMD_QUEUE_READY_STAT	BIT(3)
#घोषणा INTR_IBI_THLD_STAT		BIT(2)
#घोषणा INTR_RX_THLD_STAT		BIT(1)
#घोषणा INTR_TX_THLD_STAT		BIT(0)
#घोषणा INTR_ALL			(INTR_BUSOWNER_UPDATE_STAT |	\
					INTR_IBI_UPDATED_STAT |		\
					INTR_READ_REQ_RECV_STAT |	\
					INTR_DEFSLV_STAT |		\
					INTR_TRANSFER_ERR_STAT |	\
					INTR_DYN_ADDR_ASSGN_STAT |	\
					INTR_CCC_UPDATED_STAT |		\
					INTR_TRANSFER_ABORT_STAT |	\
					INTR_RESP_READY_STAT |		\
					INTR_CMD_QUEUE_READY_STAT |	\
					INTR_IBI_THLD_STAT |		\
					INTR_TX_THLD_STAT |		\
					INTR_RX_THLD_STAT)

#घोषणा INTR_MASTER_MASK		(INTR_TRANSFER_ERR_STAT |	\
					 INTR_RESP_READY_STAT)

#घोषणा QUEUE_STATUS_LEVEL		0x4c
#घोषणा QUEUE_STATUS_IBI_STATUS_CNT(x)	(((x) & GENMASK(28, 24)) >> 24)
#घोषणा QUEUE_STATUS_IBI_BUF_BLR(x)	(((x) & GENMASK(23, 16)) >> 16)
#घोषणा QUEUE_STATUS_LEVEL_RESP(x)	(((x) & GENMASK(15, 8)) >> 8)
#घोषणा QUEUE_STATUS_LEVEL_CMD(x)	((x) & GENMASK(7, 0))

#घोषणा DATA_BUFFER_STATUS_LEVEL	0x50
#घोषणा DATA_BUFFER_STATUS_LEVEL_TX(x)	((x) & GENMASK(7, 0))

#घोषणा PRESENT_STATE			0x54
#घोषणा CCC_DEVICE_STATUS		0x58
#घोषणा DEVICE_ADDR_TABLE_POINTER	0x5c
#घोषणा DEVICE_ADDR_TABLE_DEPTH(x)	(((x) & GENMASK(31, 16)) >> 16)
#घोषणा DEVICE_ADDR_TABLE_ADDR(x)	((x) & GENMASK(7, 0))

#घोषणा DEV_CHAR_TABLE_POINTER		0x60
#घोषणा VENDOR_SPECIFIC_REG_POINTER	0x6c
#घोषणा SLV_PID_VALUE			0x74
#घोषणा SLV_CHAR_CTRL			0x78
#घोषणा SLV_MAX_LEN			0x7c
#घोषणा MAX_READ_TURNAROUND		0x80
#घोषणा MAX_DATA_SPEED			0x84
#घोषणा SLV_DEBUG_STATUS		0x88
#घोषणा SLV_INTR_REQ			0x8c
#घोषणा DEVICE_CTRL_EXTENDED		0xb0
#घोषणा SCL_I3C_OD_TIMING		0xb4
#घोषणा SCL_I3C_PP_TIMING		0xb8
#घोषणा SCL_I3C_TIMING_HCNT(x)		(((x) << 16) & GENMASK(23, 16))
#घोषणा SCL_I3C_TIMING_LCNT(x)		((x) & GENMASK(7, 0))
#घोषणा SCL_I3C_TIMING_CNT_MIN		5

#घोषणा SCL_I2C_FM_TIMING		0xbc
#घोषणा SCL_I2C_FM_TIMING_HCNT(x)	(((x) << 16) & GENMASK(31, 16))
#घोषणा SCL_I2C_FM_TIMING_LCNT(x)	((x) & GENMASK(15, 0))

#घोषणा SCL_I2C_FMP_TIMING		0xc0
#घोषणा SCL_I2C_FMP_TIMING_HCNT(x)	(((x) << 16) & GENMASK(23, 16))
#घोषणा SCL_I2C_FMP_TIMING_LCNT(x)	((x) & GENMASK(15, 0))

#घोषणा SCL_EXT_LCNT_TIMING		0xc8
#घोषणा SCL_EXT_LCNT_4(x)		(((x) << 24) & GENMASK(31, 24))
#घोषणा SCL_EXT_LCNT_3(x)		(((x) << 16) & GENMASK(23, 16))
#घोषणा SCL_EXT_LCNT_2(x)		(((x) << 8) & GENMASK(15, 8))
#घोषणा SCL_EXT_LCNT_1(x)		((x) & GENMASK(7, 0))

#घोषणा SCL_EXT_TERMN_LCNT_TIMING	0xcc
#घोषणा BUS_FREE_TIMING			0xd4
#घोषणा BUS_I3C_MST_FREE(x)		((x) & GENMASK(15, 0))

#घोषणा BUS_IDLE_TIMING			0xd8
#घोषणा I3C_VER_ID			0xe0
#घोषणा I3C_VER_TYPE			0xe4
#घोषणा EXTENDED_CAPABILITY		0xe8
#घोषणा SLAVE_CONFIG			0xec

#घोषणा DEV_ADDR_TABLE_LEGACY_I2C_DEV	BIT(31)
#घोषणा DEV_ADDR_TABLE_DYNAMIC_ADDR(x)	(((x) << 16) & GENMASK(23, 16))
#घोषणा DEV_ADDR_TABLE_STATIC_ADDR(x)	((x) & GENMASK(6, 0))
#घोषणा DEV_ADDR_TABLE_LOC(start, idx)	((start) + ((idx) << 2))

#घोषणा MAX_DEVS 32

#घोषणा I3C_BUS_SDR1_SCL_RATE		8000000
#घोषणा I3C_BUS_SDR2_SCL_RATE		6000000
#घोषणा I3C_BUS_SDR3_SCL_RATE		4000000
#घोषणा I3C_BUS_SDR4_SCL_RATE		2000000
#घोषणा I3C_BUS_I2C_FM_TLOW_MIN_NS	1300
#घोषणा I3C_BUS_I2C_FMP_TLOW_MIN_NS	500
#घोषणा I3C_BUS_THIGH_MAX_NS		41

#घोषणा XFER_TIMEOUT (msecs_to_jअगरfies(1000))

काष्ठा dw_i3c_master_caps अणु
	u8 cmdfअगरodepth;
	u8 datafअगरodepth;
पूर्ण;

काष्ठा dw_i3c_cmd अणु
	u32 cmd_lo;
	u32 cmd_hi;
	u16 tx_len;
	स्थिर व्योम *tx_buf;
	u16 rx_len;
	व्योम *rx_buf;
	u8 error;
पूर्ण;

काष्ठा dw_i3c_xfer अणु
	काष्ठा list_head node;
	काष्ठा completion comp;
	पूर्णांक ret;
	अचिन्हित पूर्णांक ncmds;
	काष्ठा dw_i3c_cmd cmds[];
पूर्ण;

काष्ठा dw_i3c_master अणु
	काष्ठा i3c_master_controller base;
	u16 maxdevs;
	u16 datstartaddr;
	u32 मुक्त_pos;
	काष्ठा अणु
		काष्ठा list_head list;
		काष्ठा dw_i3c_xfer *cur;
		spinlock_t lock;
	पूर्ण xferqueue;
	काष्ठा dw_i3c_master_caps caps;
	व्योम __iomem *regs;
	काष्ठा reset_control *core_rst;
	काष्ठा clk *core_clk;
	अक्षर version[5];
	अक्षर type[5];
	u8 addrs[MAX_DEVS];
पूर्ण;

काष्ठा dw_i3c_i2c_dev_data अणु
	u8 index;
पूर्ण;

अटल u8 even_parity(u8 p)
अणु
	p ^= p >> 4;
	p &= 0xf;

	वापस (0x9669 >> p) & 1;
पूर्ण

अटल bool dw_i3c_master_supports_ccc_cmd(काष्ठा i3c_master_controller *m,
					   स्थिर काष्ठा i3c_ccc_cmd *cmd)
अणु
	अगर (cmd->ndests > 1)
		वापस false;

	चयन (cmd->id) अणु
	हाल I3C_CCC_ENEC(true):
	हाल I3C_CCC_ENEC(false):
	हाल I3C_CCC_DISEC(true):
	हाल I3C_CCC_DISEC(false):
	हाल I3C_CCC_ENTAS(0, true):
	हाल I3C_CCC_ENTAS(0, false):
	हाल I3C_CCC_RSTDAA(true):
	हाल I3C_CCC_RSTDAA(false):
	हाल I3C_CCC_ENTDAA:
	हाल I3C_CCC_SETMWL(true):
	हाल I3C_CCC_SETMWL(false):
	हाल I3C_CCC_SETMRL(true):
	हाल I3C_CCC_SETMRL(false):
	हाल I3C_CCC_ENTHDR(0):
	हाल I3C_CCC_SETDASA:
	हाल I3C_CCC_SETNEWDA:
	हाल I3C_CCC_GETMWL:
	हाल I3C_CCC_GETMRL:
	हाल I3C_CCC_GETPID:
	हाल I3C_CCC_GETBCR:
	हाल I3C_CCC_GETDCR:
	हाल I3C_CCC_GETSTATUS:
	हाल I3C_CCC_GETMXDS:
	हाल I3C_CCC_GETHDRCAP:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा dw_i3c_master *
to_dw_i3c_master(काष्ठा i3c_master_controller *master)
अणु
	वापस container_of(master, काष्ठा dw_i3c_master, base);
पूर्ण

अटल व्योम dw_i3c_master_disable(काष्ठा dw_i3c_master *master)
अणु
	ग_लिखोl(पढ़ोl(master->regs + DEVICE_CTRL) & ~DEV_CTRL_ENABLE,
	       master->regs + DEVICE_CTRL);
पूर्ण

अटल व्योम dw_i3c_master_enable(काष्ठा dw_i3c_master *master)
अणु
	ग_लिखोl(पढ़ोl(master->regs + DEVICE_CTRL) | DEV_CTRL_ENABLE,
	       master->regs + DEVICE_CTRL);
पूर्ण

अटल पूर्णांक dw_i3c_master_get_addr_pos(काष्ठा dw_i3c_master *master, u8 addr)
अणु
	पूर्णांक pos;

	क्रम (pos = 0; pos < master->maxdevs; pos++) अणु
		अगर (addr == master->addrs[pos])
			वापस pos;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dw_i3c_master_get_मुक्त_pos(काष्ठा dw_i3c_master *master)
अणु
	अगर (!(master->मुक्त_pos & GENMASK(master->maxdevs - 1, 0)))
		वापस -ENOSPC;

	वापस ffs(master->मुक्त_pos) - 1;
पूर्ण

अटल व्योम dw_i3c_master_wr_tx_fअगरo(काष्ठा dw_i3c_master *master,
				     स्थिर u8 *bytes, पूर्णांक nbytes)
अणु
	ग_लिखोsl(master->regs + RX_TX_DATA_PORT, bytes, nbytes / 4);
	अगर (nbytes & 3) अणु
		u32 पंचांगp = 0;

		स_नकल(&पंचांगp, bytes + (nbytes & ~3), nbytes & 3);
		ग_लिखोsl(master->regs + RX_TX_DATA_PORT, &पंचांगp, 1);
	पूर्ण
पूर्ण

अटल व्योम dw_i3c_master_पढ़ो_rx_fअगरo(काष्ठा dw_i3c_master *master,
				       u8 *bytes, पूर्णांक nbytes)
अणु
	पढ़ोsl(master->regs + RX_TX_DATA_PORT, bytes, nbytes / 4);
	अगर (nbytes & 3) अणु
		u32 पंचांगp;

		पढ़ोsl(master->regs + RX_TX_DATA_PORT, &पंचांगp, 1);
		स_नकल(bytes + (nbytes & ~3), &पंचांगp, nbytes & 3);
	पूर्ण
पूर्ण

अटल काष्ठा dw_i3c_xfer *
dw_i3c_master_alloc_xfer(काष्ठा dw_i3c_master *master, अचिन्हित पूर्णांक ncmds)
अणु
	काष्ठा dw_i3c_xfer *xfer;

	xfer = kzalloc(काष्ठा_size(xfer, cmds, ncmds), GFP_KERNEL);
	अगर (!xfer)
		वापस शून्य;

	INIT_LIST_HEAD(&xfer->node);
	xfer->ncmds = ncmds;
	xfer->ret = -ETIMEDOUT;

	वापस xfer;
पूर्ण

अटल व्योम dw_i3c_master_मुक्त_xfer(काष्ठा dw_i3c_xfer *xfer)
अणु
	kमुक्त(xfer);
पूर्ण

अटल व्योम dw_i3c_master_start_xfer_locked(काष्ठा dw_i3c_master *master)
अणु
	काष्ठा dw_i3c_xfer *xfer = master->xferqueue.cur;
	अचिन्हित पूर्णांक i;
	u32 thld_ctrl;

	अगर (!xfer)
		वापस;

	क्रम (i = 0; i < xfer->ncmds; i++) अणु
		काष्ठा dw_i3c_cmd *cmd = &xfer->cmds[i];

		dw_i3c_master_wr_tx_fअगरo(master, cmd->tx_buf, cmd->tx_len);
	पूर्ण

	thld_ctrl = पढ़ोl(master->regs + QUEUE_THLD_CTRL);
	thld_ctrl &= ~QUEUE_THLD_CTRL_RESP_BUF_MASK;
	thld_ctrl |= QUEUE_THLD_CTRL_RESP_BUF(xfer->ncmds);
	ग_लिखोl(thld_ctrl, master->regs + QUEUE_THLD_CTRL);

	क्रम (i = 0; i < xfer->ncmds; i++) अणु
		काष्ठा dw_i3c_cmd *cmd = &xfer->cmds[i];

		ग_लिखोl(cmd->cmd_hi, master->regs + COMMAND_QUEUE_PORT);
		ग_लिखोl(cmd->cmd_lo, master->regs + COMMAND_QUEUE_PORT);
	पूर्ण
पूर्ण

अटल व्योम dw_i3c_master_enqueue_xfer(काष्ठा dw_i3c_master *master,
				       काष्ठा dw_i3c_xfer *xfer)
अणु
	अचिन्हित दीर्घ flags;

	init_completion(&xfer->comp);
	spin_lock_irqsave(&master->xferqueue.lock, flags);
	अगर (master->xferqueue.cur) अणु
		list_add_tail(&xfer->node, &master->xferqueue.list);
	पूर्ण अन्यथा अणु
		master->xferqueue.cur = xfer;
		dw_i3c_master_start_xfer_locked(master);
	पूर्ण
	spin_unlock_irqrestore(&master->xferqueue.lock, flags);
पूर्ण

अटल व्योम dw_i3c_master_dequeue_xfer_locked(काष्ठा dw_i3c_master *master,
					      काष्ठा dw_i3c_xfer *xfer)
अणु
	अगर (master->xferqueue.cur == xfer) अणु
		u32 status;

		master->xferqueue.cur = शून्य;

		ग_लिखोl(RESET_CTRL_RX_FIFO | RESET_CTRL_TX_FIFO |
		       RESET_CTRL_RESP_QUEUE | RESET_CTRL_CMD_QUEUE,
		       master->regs + RESET_CTRL);

		पढ़ोl_poll_समयout_atomic(master->regs + RESET_CTRL, status,
					  !status, 10, 1000000);
	पूर्ण अन्यथा अणु
		list_del_init(&xfer->node);
	पूर्ण
पूर्ण

अटल व्योम dw_i3c_master_dequeue_xfer(काष्ठा dw_i3c_master *master,
				       काष्ठा dw_i3c_xfer *xfer)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&master->xferqueue.lock, flags);
	dw_i3c_master_dequeue_xfer_locked(master, xfer);
	spin_unlock_irqrestore(&master->xferqueue.lock, flags);
पूर्ण

अटल व्योम dw_i3c_master_end_xfer_locked(काष्ठा dw_i3c_master *master, u32 isr)
अणु
	काष्ठा dw_i3c_xfer *xfer = master->xferqueue.cur;
	पूर्णांक i, ret = 0;
	u32 nresp;

	अगर (!xfer)
		वापस;

	nresp = पढ़ोl(master->regs + QUEUE_STATUS_LEVEL);
	nresp = QUEUE_STATUS_LEVEL_RESP(nresp);

	क्रम (i = 0; i < nresp; i++) अणु
		काष्ठा dw_i3c_cmd *cmd;
		u32 resp;

		resp = पढ़ोl(master->regs + RESPONSE_QUEUE_PORT);

		cmd = &xfer->cmds[RESPONSE_PORT_TID(resp)];
		cmd->rx_len = RESPONSE_PORT_DATA_LEN(resp);
		cmd->error = RESPONSE_PORT_ERR_STATUS(resp);
		अगर (cmd->rx_len && !cmd->error)
			dw_i3c_master_पढ़ो_rx_fअगरo(master, cmd->rx_buf,
						   cmd->rx_len);
	पूर्ण

	क्रम (i = 0; i < nresp; i++) अणु
		चयन (xfer->cmds[i].error) अणु
		हाल RESPONSE_NO_ERROR:
			अवरोध;
		हाल RESPONSE_ERROR_PARITY:
		हाल RESPONSE_ERROR_IBA_NACK:
		हाल RESPONSE_ERROR_TRANSF_ABORT:
		हाल RESPONSE_ERROR_CRC:
		हाल RESPONSE_ERROR_FRAME:
			ret = -EIO;
			अवरोध;
		हाल RESPONSE_ERROR_OVER_UNDER_FLOW:
			ret = -ENOSPC;
			अवरोध;
		हाल RESPONSE_ERROR_I2C_W_NACK_ERR:
		हाल RESPONSE_ERROR_ADDRESS_NACK:
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	xfer->ret = ret;
	complete(&xfer->comp);

	अगर (ret < 0) अणु
		dw_i3c_master_dequeue_xfer_locked(master, xfer);
		ग_लिखोl(पढ़ोl(master->regs + DEVICE_CTRL) | DEV_CTRL_RESUME,
		       master->regs + DEVICE_CTRL);
	पूर्ण

	xfer = list_first_entry_or_null(&master->xferqueue.list,
					काष्ठा dw_i3c_xfer,
					node);
	अगर (xfer)
		list_del_init(&xfer->node);

	master->xferqueue.cur = xfer;
	dw_i3c_master_start_xfer_locked(master);
पूर्ण

अटल पूर्णांक dw_i3c_clk_cfg(काष्ठा dw_i3c_master *master)
अणु
	अचिन्हित दीर्घ core_rate, core_period;
	u32 scl_timing;
	u8 hcnt, lcnt;

	core_rate = clk_get_rate(master->core_clk);
	अगर (!core_rate)
		वापस -EINVAL;

	core_period = DIV_ROUND_UP(1000000000, core_rate);

	hcnt = DIV_ROUND_UP(I3C_BUS_THIGH_MAX_NS, core_period) - 1;
	अगर (hcnt < SCL_I3C_TIMING_CNT_MIN)
		hcnt = SCL_I3C_TIMING_CNT_MIN;

	lcnt = DIV_ROUND_UP(core_rate, I3C_BUS_TYP_I3C_SCL_RATE) - hcnt;
	अगर (lcnt < SCL_I3C_TIMING_CNT_MIN)
		lcnt = SCL_I3C_TIMING_CNT_MIN;

	scl_timing = SCL_I3C_TIMING_HCNT(hcnt) | SCL_I3C_TIMING_LCNT(lcnt);
	ग_लिखोl(scl_timing, master->regs + SCL_I3C_PP_TIMING);

	अगर (!(पढ़ोl(master->regs + DEVICE_CTRL) & DEV_CTRL_I2C_SLAVE_PRESENT))
		ग_लिखोl(BUS_I3C_MST_FREE(lcnt), master->regs + BUS_FREE_TIMING);

	lcnt = DIV_ROUND_UP(I3C_BUS_TLOW_OD_MIN_NS, core_period);
	scl_timing = SCL_I3C_TIMING_HCNT(hcnt) | SCL_I3C_TIMING_LCNT(lcnt);
	ग_लिखोl(scl_timing, master->regs + SCL_I3C_OD_TIMING);

	lcnt = DIV_ROUND_UP(core_rate, I3C_BUS_SDR1_SCL_RATE) - hcnt;
	scl_timing = SCL_EXT_LCNT_1(lcnt);
	lcnt = DIV_ROUND_UP(core_rate, I3C_BUS_SDR2_SCL_RATE) - hcnt;
	scl_timing |= SCL_EXT_LCNT_2(lcnt);
	lcnt = DIV_ROUND_UP(core_rate, I3C_BUS_SDR3_SCL_RATE) - hcnt;
	scl_timing |= SCL_EXT_LCNT_3(lcnt);
	lcnt = DIV_ROUND_UP(core_rate, I3C_BUS_SDR4_SCL_RATE) - hcnt;
	scl_timing |= SCL_EXT_LCNT_4(lcnt);
	ग_लिखोl(scl_timing, master->regs + SCL_EXT_LCNT_TIMING);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_i2c_clk_cfg(काष्ठा dw_i3c_master *master)
अणु
	अचिन्हित दीर्घ core_rate, core_period;
	u16 hcnt, lcnt;
	u32 scl_timing;

	core_rate = clk_get_rate(master->core_clk);
	अगर (!core_rate)
		वापस -EINVAL;

	core_period = DIV_ROUND_UP(1000000000, core_rate);

	lcnt = DIV_ROUND_UP(I3C_BUS_I2C_FMP_TLOW_MIN_NS, core_period);
	hcnt = DIV_ROUND_UP(core_rate, I3C_BUS_I2C_FM_PLUS_SCL_RATE) - lcnt;
	scl_timing = SCL_I2C_FMP_TIMING_HCNT(hcnt) |
		     SCL_I2C_FMP_TIMING_LCNT(lcnt);
	ग_लिखोl(scl_timing, master->regs + SCL_I2C_FMP_TIMING);

	lcnt = DIV_ROUND_UP(I3C_BUS_I2C_FM_TLOW_MIN_NS, core_period);
	hcnt = DIV_ROUND_UP(core_rate, I3C_BUS_I2C_FM_SCL_RATE) - lcnt;
	scl_timing = SCL_I2C_FM_TIMING_HCNT(hcnt) |
		     SCL_I2C_FM_TIMING_LCNT(lcnt);
	ग_लिखोl(scl_timing, master->regs + SCL_I2C_FM_TIMING);

	ग_लिखोl(BUS_I3C_MST_FREE(lcnt), master->regs + BUS_FREE_TIMING);
	ग_लिखोl(पढ़ोl(master->regs + DEVICE_CTRL) | DEV_CTRL_I2C_SLAVE_PRESENT,
	       master->regs + DEVICE_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_i3c_master_bus_init(काष्ठा i3c_master_controller *m)
अणु
	काष्ठा dw_i3c_master *master = to_dw_i3c_master(m);
	काष्ठा i3c_bus *bus = i3c_master_get_bus(m);
	काष्ठा i3c_device_info info = अणु पूर्ण;
	u32 thld_ctrl;
	पूर्णांक ret;

	चयन (bus->mode) अणु
	हाल I3C_BUS_MODE_MIXED_FAST:
	हाल I3C_BUS_MODE_MIXED_LIMITED:
		ret = dw_i2c_clk_cfg(master);
		अगर (ret)
			वापस ret;
		fallthrough;
	हाल I3C_BUS_MODE_PURE:
		ret = dw_i3c_clk_cfg(master);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	thld_ctrl = पढ़ोl(master->regs + QUEUE_THLD_CTRL);
	thld_ctrl &= ~QUEUE_THLD_CTRL_RESP_BUF_MASK;
	ग_लिखोl(thld_ctrl, master->regs + QUEUE_THLD_CTRL);

	thld_ctrl = पढ़ोl(master->regs + DATA_BUFFER_THLD_CTRL);
	thld_ctrl &= ~DATA_BUFFER_THLD_CTRL_RX_BUF;
	ग_लिखोl(thld_ctrl, master->regs + DATA_BUFFER_THLD_CTRL);

	ग_लिखोl(INTR_ALL, master->regs + INTR_STATUS);
	ग_लिखोl(INTR_MASTER_MASK, master->regs + INTR_STATUS_EN);
	ग_लिखोl(INTR_MASTER_MASK, master->regs + INTR_SIGNAL_EN);

	ret = i3c_master_get_मुक्त_addr(m, 0);
	अगर (ret < 0)
		वापस ret;

	ग_लिखोl(DEV_ADDR_DYNAMIC_ADDR_VALID | DEV_ADDR_DYNAMIC(ret),
	       master->regs + DEVICE_ADDR);

	स_रखो(&info, 0, माप(info));
	info.dyn_addr = ret;

	ret = i3c_master_set_info(&master->base, &info);
	अगर (ret)
		वापस ret;

	ग_लिखोl(IBI_REQ_REJECT_ALL, master->regs + IBI_SIR_REQ_REJECT);
	ग_लिखोl(IBI_REQ_REJECT_ALL, master->regs + IBI_MR_REQ_REJECT);

	/* For now करोn't support Hot-Join */
	ग_लिखोl(पढ़ोl(master->regs + DEVICE_CTRL) | DEV_CTRL_HOT_JOIN_NACK,
	       master->regs + DEVICE_CTRL);

	dw_i3c_master_enable(master);

	वापस 0;
पूर्ण

अटल व्योम dw_i3c_master_bus_cleanup(काष्ठा i3c_master_controller *m)
अणु
	काष्ठा dw_i3c_master *master = to_dw_i3c_master(m);

	dw_i3c_master_disable(master);
पूर्ण

अटल पूर्णांक dw_i3c_ccc_set(काष्ठा dw_i3c_master *master,
			  काष्ठा i3c_ccc_cmd *ccc)
अणु
	काष्ठा dw_i3c_xfer *xfer;
	काष्ठा dw_i3c_cmd *cmd;
	पूर्णांक ret, pos = 0;

	अगर (ccc->id & I3C_CCC_सूचीECT) अणु
		pos = dw_i3c_master_get_addr_pos(master, ccc->dests[0].addr);
		अगर (pos < 0)
			वापस pos;
	पूर्ण

	xfer = dw_i3c_master_alloc_xfer(master, 1);
	अगर (!xfer)
		वापस -ENOMEM;

	cmd = xfer->cmds;
	cmd->tx_buf = ccc->dests[0].payload.data;
	cmd->tx_len = ccc->dests[0].payload.len;

	cmd->cmd_hi = COMMAND_PORT_ARG_DATA_LEN(ccc->dests[0].payload.len) |
		      COMMAND_PORT_TRANSFER_ARG;

	cmd->cmd_lo = COMMAND_PORT_CP |
		      COMMAND_PORT_DEV_INDEX(pos) |
		      COMMAND_PORT_CMD(ccc->id) |
		      COMMAND_PORT_TOC |
		      COMMAND_PORT_ROC;

	dw_i3c_master_enqueue_xfer(master, xfer);
	अगर (!रुको_क्रम_completion_समयout(&xfer->comp, XFER_TIMEOUT))
		dw_i3c_master_dequeue_xfer(master, xfer);

	ret = xfer->ret;
	अगर (xfer->cmds[0].error == RESPONSE_ERROR_IBA_NACK)
		ccc->err = I3C_ERROR_M2;

	dw_i3c_master_मुक्त_xfer(xfer);

	वापस ret;
पूर्ण

अटल पूर्णांक dw_i3c_ccc_get(काष्ठा dw_i3c_master *master, काष्ठा i3c_ccc_cmd *ccc)
अणु
	काष्ठा dw_i3c_xfer *xfer;
	काष्ठा dw_i3c_cmd *cmd;
	पूर्णांक ret, pos;

	pos = dw_i3c_master_get_addr_pos(master, ccc->dests[0].addr);
	अगर (pos < 0)
		वापस pos;

	xfer = dw_i3c_master_alloc_xfer(master, 1);
	अगर (!xfer)
		वापस -ENOMEM;

	cmd = xfer->cmds;
	cmd->rx_buf = ccc->dests[0].payload.data;
	cmd->rx_len = ccc->dests[0].payload.len;

	cmd->cmd_hi = COMMAND_PORT_ARG_DATA_LEN(ccc->dests[0].payload.len) |
		      COMMAND_PORT_TRANSFER_ARG;

	cmd->cmd_lo = COMMAND_PORT_READ_TRANSFER |
		      COMMAND_PORT_CP |
		      COMMAND_PORT_DEV_INDEX(pos) |
		      COMMAND_PORT_CMD(ccc->id) |
		      COMMAND_PORT_TOC |
		      COMMAND_PORT_ROC;

	dw_i3c_master_enqueue_xfer(master, xfer);
	अगर (!रुको_क्रम_completion_समयout(&xfer->comp, XFER_TIMEOUT))
		dw_i3c_master_dequeue_xfer(master, xfer);

	ret = xfer->ret;
	अगर (xfer->cmds[0].error == RESPONSE_ERROR_IBA_NACK)
		ccc->err = I3C_ERROR_M2;
	dw_i3c_master_मुक्त_xfer(xfer);

	वापस ret;
पूर्ण

अटल पूर्णांक dw_i3c_master_send_ccc_cmd(काष्ठा i3c_master_controller *m,
				      काष्ठा i3c_ccc_cmd *ccc)
अणु
	काष्ठा dw_i3c_master *master = to_dw_i3c_master(m);
	पूर्णांक ret = 0;

	अगर (ccc->id == I3C_CCC_ENTDAA)
		वापस -EINVAL;

	अगर (ccc->rnw)
		ret = dw_i3c_ccc_get(master, ccc);
	अन्यथा
		ret = dw_i3c_ccc_set(master, ccc);

	वापस ret;
पूर्ण

अटल पूर्णांक dw_i3c_master_daa(काष्ठा i3c_master_controller *m)
अणु
	काष्ठा dw_i3c_master *master = to_dw_i3c_master(m);
	काष्ठा dw_i3c_xfer *xfer;
	काष्ठा dw_i3c_cmd *cmd;
	u32 olddevs, newdevs;
	u8 p, last_addr = 0;
	पूर्णांक ret, pos;

	olddevs = ~(master->मुक्त_pos);

	/* Prepare DAT beक्रमe launching DAA. */
	क्रम (pos = 0; pos < master->maxdevs; pos++) अणु
		अगर (olddevs & BIT(pos))
			जारी;

		ret = i3c_master_get_मुक्त_addr(m, last_addr + 1);
		अगर (ret < 0)
			वापस -ENOSPC;

		master->addrs[pos] = ret;
		p = even_parity(ret);
		last_addr = ret;
		ret |= (p << 7);

		ग_लिखोl(DEV_ADDR_TABLE_DYNAMIC_ADDR(ret),
		       master->regs +
		       DEV_ADDR_TABLE_LOC(master->datstartaddr, pos));
	पूर्ण

	xfer = dw_i3c_master_alloc_xfer(master, 1);
	अगर (!xfer)
		वापस -ENOMEM;

	pos = dw_i3c_master_get_मुक्त_pos(master);
	cmd = &xfer->cmds[0];
	cmd->cmd_hi = 0x1;
	cmd->cmd_lo = COMMAND_PORT_DEV_COUNT(master->maxdevs - pos) |
		      COMMAND_PORT_DEV_INDEX(pos) |
		      COMMAND_PORT_CMD(I3C_CCC_ENTDAA) |
		      COMMAND_PORT_ADDR_ASSGN_CMD |
		      COMMAND_PORT_TOC |
		      COMMAND_PORT_ROC;

	dw_i3c_master_enqueue_xfer(master, xfer);
	अगर (!रुको_क्रम_completion_समयout(&xfer->comp, XFER_TIMEOUT))
		dw_i3c_master_dequeue_xfer(master, xfer);

	newdevs = GENMASK(master->maxdevs - cmd->rx_len - 1, 0);
	newdevs &= ~olddevs;

	क्रम (pos = 0; pos < master->maxdevs; pos++) अणु
		अगर (newdevs & BIT(pos))
			i3c_master_add_i3c_dev_locked(m, master->addrs[pos]);
	पूर्ण

	dw_i3c_master_मुक्त_xfer(xfer);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_i3c_master_priv_xfers(काष्ठा i3c_dev_desc *dev,
				    काष्ठा i3c_priv_xfer *i3c_xfers,
				    पूर्णांक i3c_nxfers)
अणु
	काष्ठा dw_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा dw_i3c_master *master = to_dw_i3c_master(m);
	अचिन्हित पूर्णांक nrxwords = 0, ntxwords = 0;
	काष्ठा dw_i3c_xfer *xfer;
	पूर्णांक i, ret = 0;

	अगर (!i3c_nxfers)
		वापस 0;

	अगर (i3c_nxfers > master->caps.cmdfअगरodepth)
		वापस -ENOTSUPP;

	क्रम (i = 0; i < i3c_nxfers; i++) अणु
		अगर (i3c_xfers[i].rnw)
			nrxwords += DIV_ROUND_UP(i3c_xfers[i].len, 4);
		अन्यथा
			ntxwords += DIV_ROUND_UP(i3c_xfers[i].len, 4);
	पूर्ण

	अगर (ntxwords > master->caps.datafअगरodepth ||
	    nrxwords > master->caps.datafअगरodepth)
		वापस -ENOTSUPP;

	xfer = dw_i3c_master_alloc_xfer(master, i3c_nxfers);
	अगर (!xfer)
		वापस -ENOMEM;

	क्रम (i = 0; i < i3c_nxfers; i++) अणु
		काष्ठा dw_i3c_cmd *cmd = &xfer->cmds[i];

		cmd->cmd_hi = COMMAND_PORT_ARG_DATA_LEN(i3c_xfers[i].len) |
			COMMAND_PORT_TRANSFER_ARG;

		अगर (i3c_xfers[i].rnw) अणु
			cmd->rx_buf = i3c_xfers[i].data.in;
			cmd->rx_len = i3c_xfers[i].len;
			cmd->cmd_lo = COMMAND_PORT_READ_TRANSFER |
				      COMMAND_PORT_SPEED(dev->info.max_पढ़ो_ds);

		पूर्ण अन्यथा अणु
			cmd->tx_buf = i3c_xfers[i].data.out;
			cmd->tx_len = i3c_xfers[i].len;
			cmd->cmd_lo =
				COMMAND_PORT_SPEED(dev->info.max_ग_लिखो_ds);
		पूर्ण

		cmd->cmd_lo |= COMMAND_PORT_TID(i) |
			       COMMAND_PORT_DEV_INDEX(data->index) |
			       COMMAND_PORT_ROC;

		अगर (i == (i3c_nxfers - 1))
			cmd->cmd_lo |= COMMAND_PORT_TOC;
	पूर्ण

	dw_i3c_master_enqueue_xfer(master, xfer);
	अगर (!रुको_क्रम_completion_समयout(&xfer->comp, XFER_TIMEOUT))
		dw_i3c_master_dequeue_xfer(master, xfer);

	ret = xfer->ret;
	dw_i3c_master_मुक्त_xfer(xfer);

	वापस ret;
पूर्ण

अटल पूर्णांक dw_i3c_master_reattach_i3c_dev(काष्ठा i3c_dev_desc *dev,
					  u8 old_dyn_addr)
अणु
	काष्ठा dw_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा dw_i3c_master *master = to_dw_i3c_master(m);
	पूर्णांक pos;

	pos = dw_i3c_master_get_मुक्त_pos(master);

	अगर (data->index > pos && pos > 0) अणु
		ग_लिखोl(0,
		       master->regs +
		       DEV_ADDR_TABLE_LOC(master->datstartaddr, data->index));

		master->addrs[data->index] = 0;
		master->मुक्त_pos |= BIT(data->index);

		data->index = pos;
		master->addrs[pos] = dev->info.dyn_addr;
		master->मुक्त_pos &= ~BIT(pos);
	पूर्ण

	ग_लिखोl(DEV_ADDR_TABLE_DYNAMIC_ADDR(dev->info.dyn_addr),
	       master->regs +
	       DEV_ADDR_TABLE_LOC(master->datstartaddr, data->index));

	master->addrs[data->index] = dev->info.dyn_addr;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_i3c_master_attach_i3c_dev(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा dw_i3c_master *master = to_dw_i3c_master(m);
	काष्ठा dw_i3c_i2c_dev_data *data;
	पूर्णांक pos;

	pos = dw_i3c_master_get_मुक्त_pos(master);
	अगर (pos < 0)
		वापस pos;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->index = pos;
	master->addrs[pos] = dev->info.dyn_addr ? : dev->info.अटल_addr;
	master->मुक्त_pos &= ~BIT(pos);
	i3c_dev_set_master_data(dev, data);

	ग_लिखोl(DEV_ADDR_TABLE_DYNAMIC_ADDR(master->addrs[pos]),
	       master->regs +
	       DEV_ADDR_TABLE_LOC(master->datstartaddr, data->index));

	वापस 0;
पूर्ण

अटल व्योम dw_i3c_master_detach_i3c_dev(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा dw_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा dw_i3c_master *master = to_dw_i3c_master(m);

	ग_लिखोl(0,
	       master->regs +
	       DEV_ADDR_TABLE_LOC(master->datstartaddr, data->index));

	i3c_dev_set_master_data(dev, शून्य);
	master->addrs[data->index] = 0;
	master->मुक्त_pos |= BIT(data->index);
	kमुक्त(data);
पूर्ण

अटल पूर्णांक dw_i3c_master_i2c_xfers(काष्ठा i2c_dev_desc *dev,
				   स्थिर काष्ठा i2c_msg *i2c_xfers,
				   पूर्णांक i2c_nxfers)
अणु
	काष्ठा dw_i3c_i2c_dev_data *data = i2c_dev_get_master_data(dev);
	काष्ठा i3c_master_controller *m = i2c_dev_get_master(dev);
	काष्ठा dw_i3c_master *master = to_dw_i3c_master(m);
	अचिन्हित पूर्णांक nrxwords = 0, ntxwords = 0;
	काष्ठा dw_i3c_xfer *xfer;
	पूर्णांक i, ret = 0;

	अगर (!i2c_nxfers)
		वापस 0;

	अगर (i2c_nxfers > master->caps.cmdfअगरodepth)
		वापस -ENOTSUPP;

	क्रम (i = 0; i < i2c_nxfers; i++) अणु
		अगर (i2c_xfers[i].flags & I2C_M_RD)
			nrxwords += DIV_ROUND_UP(i2c_xfers[i].len, 4);
		अन्यथा
			ntxwords += DIV_ROUND_UP(i2c_xfers[i].len, 4);
	पूर्ण

	अगर (ntxwords > master->caps.datafअगरodepth ||
	    nrxwords > master->caps.datafअगरodepth)
		वापस -ENOTSUPP;

	xfer = dw_i3c_master_alloc_xfer(master, i2c_nxfers);
	अगर (!xfer)
		वापस -ENOMEM;

	क्रम (i = 0; i < i2c_nxfers; i++) अणु
		काष्ठा dw_i3c_cmd *cmd = &xfer->cmds[i];

		cmd->cmd_hi = COMMAND_PORT_ARG_DATA_LEN(i2c_xfers[i].len) |
			COMMAND_PORT_TRANSFER_ARG;

		cmd->cmd_lo = COMMAND_PORT_TID(i) |
			      COMMAND_PORT_DEV_INDEX(data->index) |
			      COMMAND_PORT_ROC;

		अगर (i2c_xfers[i].flags & I2C_M_RD) अणु
			cmd->cmd_lo |= COMMAND_PORT_READ_TRANSFER;
			cmd->rx_buf = i2c_xfers[i].buf;
			cmd->rx_len = i2c_xfers[i].len;
		पूर्ण अन्यथा अणु
			cmd->tx_buf = i2c_xfers[i].buf;
			cmd->tx_len = i2c_xfers[i].len;
		पूर्ण

		अगर (i == (i2c_nxfers - 1))
			cmd->cmd_lo |= COMMAND_PORT_TOC;
	पूर्ण

	dw_i3c_master_enqueue_xfer(master, xfer);
	अगर (!रुको_क्रम_completion_समयout(&xfer->comp, XFER_TIMEOUT))
		dw_i3c_master_dequeue_xfer(master, xfer);

	ret = xfer->ret;
	dw_i3c_master_मुक्त_xfer(xfer);

	वापस ret;
पूर्ण

अटल पूर्णांक dw_i3c_master_attach_i2c_dev(काष्ठा i2c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i2c_dev_get_master(dev);
	काष्ठा dw_i3c_master *master = to_dw_i3c_master(m);
	काष्ठा dw_i3c_i2c_dev_data *data;
	पूर्णांक pos;

	pos = dw_i3c_master_get_मुक्त_pos(master);
	अगर (pos < 0)
		वापस pos;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->index = pos;
	master->addrs[pos] = dev->addr;
	master->मुक्त_pos &= ~BIT(pos);
	i2c_dev_set_master_data(dev, data);

	ग_लिखोl(DEV_ADDR_TABLE_LEGACY_I2C_DEV |
	       DEV_ADDR_TABLE_STATIC_ADDR(dev->addr),
	       master->regs +
	       DEV_ADDR_TABLE_LOC(master->datstartaddr, data->index));

	वापस 0;
पूर्ण

अटल व्योम dw_i3c_master_detach_i2c_dev(काष्ठा i2c_dev_desc *dev)
अणु
	काष्ठा dw_i3c_i2c_dev_data *data = i2c_dev_get_master_data(dev);
	काष्ठा i3c_master_controller *m = i2c_dev_get_master(dev);
	काष्ठा dw_i3c_master *master = to_dw_i3c_master(m);

	ग_लिखोl(0,
	       master->regs +
	       DEV_ADDR_TABLE_LOC(master->datstartaddr, data->index));

	i2c_dev_set_master_data(dev, शून्य);
	master->addrs[data->index] = 0;
	master->मुक्त_pos |= BIT(data->index);
	kमुक्त(data);
पूर्ण

अटल irqवापस_t dw_i3c_master_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dw_i3c_master *master = dev_id;
	u32 status;

	status = पढ़ोl(master->regs + INTR_STATUS);

	अगर (!(status & पढ़ोl(master->regs + INTR_STATUS_EN))) अणु
		ग_लिखोl(INTR_ALL, master->regs + INTR_STATUS);
		वापस IRQ_NONE;
	पूर्ण

	spin_lock(&master->xferqueue.lock);
	dw_i3c_master_end_xfer_locked(master, status);
	अगर (status & INTR_TRANSFER_ERR_STAT)
		ग_लिखोl(INTR_TRANSFER_ERR_STAT, master->regs + INTR_STATUS);
	spin_unlock(&master->xferqueue.lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा i3c_master_controller_ops dw_mipi_i3c_ops = अणु
	.bus_init = dw_i3c_master_bus_init,
	.bus_cleanup = dw_i3c_master_bus_cleanup,
	.attach_i3c_dev = dw_i3c_master_attach_i3c_dev,
	.reattach_i3c_dev = dw_i3c_master_reattach_i3c_dev,
	.detach_i3c_dev = dw_i3c_master_detach_i3c_dev,
	.करो_daa = dw_i3c_master_daa,
	.supports_ccc_cmd = dw_i3c_master_supports_ccc_cmd,
	.send_ccc_cmd = dw_i3c_master_send_ccc_cmd,
	.priv_xfers = dw_i3c_master_priv_xfers,
	.attach_i2c_dev = dw_i3c_master_attach_i2c_dev,
	.detach_i2c_dev = dw_i3c_master_detach_i2c_dev,
	.i2c_xfers = dw_i3c_master_i2c_xfers,
पूर्ण;

अटल पूर्णांक dw_i3c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_i3c_master *master;
	पूर्णांक ret, irq;

	master = devm_kzalloc(&pdev->dev, माप(*master), GFP_KERNEL);
	अगर (!master)
		वापस -ENOMEM;

	master->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(master->regs))
		वापस PTR_ERR(master->regs);

	master->core_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(master->core_clk))
		वापस PTR_ERR(master->core_clk);

	master->core_rst = devm_reset_control_get_optional_exclusive(&pdev->dev,
								    "core_rst");
	अगर (IS_ERR(master->core_rst))
		वापस PTR_ERR(master->core_rst);

	ret = clk_prepare_enable(master->core_clk);
	अगर (ret)
		जाओ err_disable_core_clk;

	reset_control_deनिश्चित(master->core_rst);

	spin_lock_init(&master->xferqueue.lock);
	INIT_LIST_HEAD(&master->xferqueue.list);

	ग_लिखोl(INTR_ALL, master->regs + INTR_STATUS);
	irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_irq(&pdev->dev, irq,
			       dw_i3c_master_irq_handler, 0,
			       dev_name(&pdev->dev), master);
	अगर (ret)
		जाओ err_निश्चित_rst;

	platक्रमm_set_drvdata(pdev, master);

	/* Inक्रमmation regarding the FIFOs/QUEUEs depth */
	ret = पढ़ोl(master->regs + QUEUE_STATUS_LEVEL);
	master->caps.cmdfअगरodepth = QUEUE_STATUS_LEVEL_CMD(ret);

	ret = पढ़ोl(master->regs + DATA_BUFFER_STATUS_LEVEL);
	master->caps.datafअगरodepth = DATA_BUFFER_STATUS_LEVEL_TX(ret);

	ret = पढ़ोl(master->regs + DEVICE_ADDR_TABLE_POINTER);
	master->datstartaddr = ret;
	master->maxdevs = ret >> 16;
	master->मुक्त_pos = GENMASK(master->maxdevs - 1, 0);

	ret = i3c_master_रेजिस्टर(&master->base, &pdev->dev,
				  &dw_mipi_i3c_ops, false);
	अगर (ret)
		जाओ err_निश्चित_rst;

	वापस 0;

err_निश्चित_rst:
	reset_control_निश्चित(master->core_rst);

err_disable_core_clk:
	clk_disable_unprepare(master->core_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक dw_i3c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_i3c_master *master = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = i3c_master_unरेजिस्टर(&master->base);
	अगर (ret)
		वापस ret;

	reset_control_निश्चित(master->core_rst);

	clk_disable_unprepare(master->core_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dw_i3c_master_of_match[] = अणु
	अणु .compatible = "snps,dw-i3c-master-1.00a", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_i3c_master_of_match);

अटल काष्ठा platक्रमm_driver dw_i3c_driver = अणु
	.probe = dw_i3c_probe,
	.हटाओ = dw_i3c_हटाओ,
	.driver = अणु
		.name = "dw-i3c-master",
		.of_match_table = of_match_ptr(dw_i3c_master_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(dw_i3c_driver);

MODULE_AUTHOR("Vitor Soares <vitor.soares@synopsys.com>");
MODULE_DESCRIPTION("DesignWare MIPI I3C driver");
MODULE_LICENSE("GPL v2");
