<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Cadence Design Systems Inc.
 *
 * Author: Boris Brezillon <boris.brezillon@bootlin.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i3c/master.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/of_device.h>

#घोषणा DEV_ID				0x0
#घोषणा DEV_ID_I3C_MASTER		0x5034

#घोषणा CONF_STATUS0			0x4
#घोषणा CONF_STATUS0_CMDR_DEPTH(x)	(4 << (((x) & GENMASK(31, 29)) >> 29))
#घोषणा CONF_STATUS0_ECC_CHK		BIT(28)
#घोषणा CONF_STATUS0_INTEG_CHK		BIT(27)
#घोषणा CONF_STATUS0_CSR_DAP_CHK	BIT(26)
#घोषणा CONF_STATUS0_TRANS_TOUT_CHK	BIT(25)
#घोषणा CONF_STATUS0_PROT_FAULTS_CHK	BIT(24)
#घोषणा CONF_STATUS0_GPO_NUM(x)		(((x) & GENMASK(23, 16)) >> 16)
#घोषणा CONF_STATUS0_GPI_NUM(x)		(((x) & GENMASK(15, 8)) >> 8)
#घोषणा CONF_STATUS0_IBIR_DEPTH(x)	(4 << (((x) & GENMASK(7, 6)) >> 7))
#घोषणा CONF_STATUS0_SUPPORTS_DDR	BIT(5)
#घोषणा CONF_STATUS0_SEC_MASTER		BIT(4)
#घोषणा CONF_STATUS0_DEVS_NUM(x)	((x) & GENMASK(3, 0))

#घोषणा CONF_STATUS1			0x8
#घोषणा CONF_STATUS1_IBI_HW_RES(x)	((((x) & GENMASK(31, 28)) >> 28) + 1)
#घोषणा CONF_STATUS1_CMD_DEPTH(x)	(4 << (((x) & GENMASK(27, 26)) >> 26))
#घोषणा CONF_STATUS1_SLVDDR_RX_DEPTH(x)	(8 << (((x) & GENMASK(25, 21)) >> 21))
#घोषणा CONF_STATUS1_SLVDDR_TX_DEPTH(x)	(8 << (((x) & GENMASK(20, 16)) >> 16))
#घोषणा CONF_STATUS1_IBI_DEPTH(x)	(2 << (((x) & GENMASK(12, 10)) >> 10))
#घोषणा CONF_STATUS1_RX_DEPTH(x)	(8 << (((x) & GENMASK(9, 5)) >> 5))
#घोषणा CONF_STATUS1_TX_DEPTH(x)	(8 << ((x) & GENMASK(4, 0)))

#घोषणा REV_ID				0xc
#घोषणा REV_ID_VID(id)			(((id) & GENMASK(31, 20)) >> 20)
#घोषणा REV_ID_PID(id)			(((id) & GENMASK(19, 8)) >> 8)
#घोषणा REV_ID_REV_MAJOR(id)		(((id) & GENMASK(7, 4)) >> 4)
#घोषणा REV_ID_REV_MINOR(id)		((id) & GENMASK(3, 0))

#घोषणा CTRL				0x10
#घोषणा CTRL_DEV_EN			BIT(31)
#घोषणा CTRL_HALT_EN			BIT(30)
#घोषणा CTRL_MCS			BIT(29)
#घोषणा CTRL_MCS_EN			BIT(28)
#घोषणा CTRL_THD_DELAY(x)		(((x) << 24) & GENMASK(25, 24))
#घोषणा CTRL_HJ_DISEC			BIT(8)
#घोषणा CTRL_MST_ACK			BIT(7)
#घोषणा CTRL_HJ_ACK			BIT(6)
#घोषणा CTRL_HJ_INIT			BIT(5)
#घोषणा CTRL_MST_INIT			BIT(4)
#घोषणा CTRL_AHDR_OPT			BIT(3)
#घोषणा CTRL_PURE_BUS_MODE		0
#घोषणा CTRL_MIXED_FAST_BUS_MODE	2
#घोषणा CTRL_MIXED_SLOW_BUS_MODE	3
#घोषणा CTRL_BUS_MODE_MASK		GENMASK(1, 0)
#घोषणा THD_DELAY_MAX			3

#घोषणा PRESCL_CTRL0			0x14
#घोषणा PRESCL_CTRL0_I2C(x)		((x) << 16)
#घोषणा PRESCL_CTRL0_I3C(x)		(x)
#घोषणा PRESCL_CTRL0_MAX		GENMASK(9, 0)

#घोषणा PRESCL_CTRL1			0x18
#घोषणा PRESCL_CTRL1_PP_LOW_MASK	GENMASK(15, 8)
#घोषणा PRESCL_CTRL1_PP_LOW(x)		((x) << 8)
#घोषणा PRESCL_CTRL1_OD_LOW_MASK	GENMASK(7, 0)
#घोषणा PRESCL_CTRL1_OD_LOW(x)		(x)

#घोषणा MST_IER				0x20
#घोषणा MST_IDR				0x24
#घोषणा MST_IMR				0x28
#घोषणा MST_ICR				0x2c
#घोषणा MST_ISR				0x30
#घोषणा MST_INT_HALTED			BIT(18)
#घोषणा MST_INT_MR_DONE			BIT(17)
#घोषणा MST_INT_IMM_COMP		BIT(16)
#घोषणा MST_INT_TX_THR			BIT(15)
#घोषणा MST_INT_TX_OVF			BIT(14)
#घोषणा MST_INT_IBID_THR		BIT(12)
#घोषणा MST_INT_IBID_UNF		BIT(11)
#घोषणा MST_INT_IBIR_THR		BIT(10)
#घोषणा MST_INT_IBIR_UNF		BIT(9)
#घोषणा MST_INT_IBIR_OVF		BIT(8)
#घोषणा MST_INT_RX_THR			BIT(7)
#घोषणा MST_INT_RX_UNF			BIT(6)
#घोषणा MST_INT_CMDD_EMP		BIT(5)
#घोषणा MST_INT_CMDD_THR		BIT(4)
#घोषणा MST_INT_CMDD_OVF		BIT(3)
#घोषणा MST_INT_CMDR_THR		BIT(2)
#घोषणा MST_INT_CMDR_UNF		BIT(1)
#घोषणा MST_INT_CMDR_OVF		BIT(0)

#घोषणा MST_STATUS0			0x34
#घोषणा MST_STATUS0_IDLE		BIT(18)
#घोषणा MST_STATUS0_HALTED		BIT(17)
#घोषणा MST_STATUS0_MASTER_MODE		BIT(16)
#घोषणा MST_STATUS0_TX_FULL		BIT(13)
#घोषणा MST_STATUS0_IBID_FULL		BIT(12)
#घोषणा MST_STATUS0_IBIR_FULL		BIT(11)
#घोषणा MST_STATUS0_RX_FULL		BIT(10)
#घोषणा MST_STATUS0_CMDD_FULL		BIT(9)
#घोषणा MST_STATUS0_CMDR_FULL		BIT(8)
#घोषणा MST_STATUS0_TX_EMP		BIT(5)
#घोषणा MST_STATUS0_IBID_EMP		BIT(4)
#घोषणा MST_STATUS0_IBIR_EMP		BIT(3)
#घोषणा MST_STATUS0_RX_EMP		BIT(2)
#घोषणा MST_STATUS0_CMDD_EMP		BIT(1)
#घोषणा MST_STATUS0_CMDR_EMP		BIT(0)

#घोषणा CMDR				0x38
#घोषणा CMDR_NO_ERROR			0
#घोषणा CMDR_DDR_PREAMBLE_ERROR		1
#घोषणा CMDR_DDR_PARITY_ERROR		2
#घोषणा CMDR_DDR_RX_FIFO_OVF		3
#घोषणा CMDR_DDR_TX_FIFO_UNF		4
#घोषणा CMDR_M0_ERROR			5
#घोषणा CMDR_M1_ERROR			6
#घोषणा CMDR_M2_ERROR			7
#घोषणा CMDR_MST_ABORT			8
#घोषणा CMDR_NACK_RESP			9
#घोषणा CMDR_INVALID_DA			10
#घोषणा CMDR_DDR_DROPPED		11
#घोषणा CMDR_ERROR(x)			(((x) & GENMASK(27, 24)) >> 24)
#घोषणा CMDR_XFER_BYTES(x)		(((x) & GENMASK(19, 8)) >> 8)
#घोषणा CMDR_CMDID_HJACK_DISEC		0xfe
#घोषणा CMDR_CMDID_HJACK_ENTDAA		0xff
#घोषणा CMDR_CMDID(x)			((x) & GENMASK(7, 0))

#घोषणा IBIR				0x3c
#घोषणा IBIR_ACKED			BIT(12)
#घोषणा IBIR_SLVID(x)			(((x) & GENMASK(11, 8)) >> 8)
#घोषणा IBIR_ERROR			BIT(7)
#घोषणा IBIR_XFER_BYTES(x)		(((x) & GENMASK(6, 2)) >> 2)
#घोषणा IBIR_TYPE_IBI			0
#घोषणा IBIR_TYPE_HJ			1
#घोषणा IBIR_TYPE_MR			2
#घोषणा IBIR_TYPE(x)			((x) & GENMASK(1, 0))

#घोषणा SLV_IER				0x40
#घोषणा SLV_IDR				0x44
#घोषणा SLV_IMR				0x48
#घोषणा SLV_ICR				0x4c
#घोषणा SLV_ISR				0x50
#घोषणा SLV_INT_TM			BIT(20)
#घोषणा SLV_INT_ERROR			BIT(19)
#घोषणा SLV_INT_EVENT_UP		BIT(18)
#घोषणा SLV_INT_HJ_DONE			BIT(17)
#घोषणा SLV_INT_MR_DONE			BIT(16)
#घोषणा SLV_INT_DA_UPD			BIT(15)
#घोषणा SLV_INT_SDR_FAIL		BIT(14)
#घोषणा SLV_INT_DDR_FAIL		BIT(13)
#घोषणा SLV_INT_M_RD_ABORT		BIT(12)
#घोषणा SLV_INT_DDR_RX_THR		BIT(11)
#घोषणा SLV_INT_DDR_TX_THR		BIT(10)
#घोषणा SLV_INT_SDR_RX_THR		BIT(9)
#घोषणा SLV_INT_SDR_TX_THR		BIT(8)
#घोषणा SLV_INT_DDR_RX_UNF		BIT(7)
#घोषणा SLV_INT_DDR_TX_OVF		BIT(6)
#घोषणा SLV_INT_SDR_RX_UNF		BIT(5)
#घोषणा SLV_INT_SDR_TX_OVF		BIT(4)
#घोषणा SLV_INT_DDR_RD_COMP		BIT(3)
#घोषणा SLV_INT_DDR_WR_COMP		BIT(2)
#घोषणा SLV_INT_SDR_RD_COMP		BIT(1)
#घोषणा SLV_INT_SDR_WR_COMP		BIT(0)

#घोषणा SLV_STATUS0			0x54
#घोषणा SLV_STATUS0_REG_ADDR(s)		(((s) & GENMASK(23, 16)) >> 16)
#घोषणा SLV_STATUS0_XFRD_BYTES(s)	((s) & GENMASK(15, 0))

#घोषणा SLV_STATUS1			0x58
#घोषणा SLV_STATUS1_AS(s)		(((s) & GENMASK(21, 20)) >> 20)
#घोषणा SLV_STATUS1_VEN_TM		BIT(19)
#घोषणा SLV_STATUS1_HJ_DIS		BIT(18)
#घोषणा SLV_STATUS1_MR_DIS		BIT(17)
#घोषणा SLV_STATUS1_PROT_ERR		BIT(16)
#घोषणा SLV_STATUS1_DA(x)		(((s) & GENMASK(15, 9)) >> 9)
#घोषणा SLV_STATUS1_HAS_DA		BIT(8)
#घोषणा SLV_STATUS1_DDR_RX_FULL		BIT(7)
#घोषणा SLV_STATUS1_DDR_TX_FULL		BIT(6)
#घोषणा SLV_STATUS1_DDR_RX_EMPTY	BIT(5)
#घोषणा SLV_STATUS1_DDR_TX_EMPTY	BIT(4)
#घोषणा SLV_STATUS1_SDR_RX_FULL		BIT(3)
#घोषणा SLV_STATUS1_SDR_TX_FULL		BIT(2)
#घोषणा SLV_STATUS1_SDR_RX_EMPTY	BIT(1)
#घोषणा SLV_STATUS1_SDR_TX_EMPTY	BIT(0)

#घोषणा CMD0_FIFO			0x60
#घोषणा CMD0_FIFO_IS_DDR		BIT(31)
#घोषणा CMD0_FIFO_IS_CCC		BIT(30)
#घोषणा CMD0_FIFO_BCH			BIT(29)
#घोषणा XMIT_BURST_STATIC_SUBADDR	0
#घोषणा XMIT_SINGLE_INC_SUBADDR		1
#घोषणा XMIT_SINGLE_STATIC_SUBADDR	2
#घोषणा XMIT_BURST_WITHOUT_SUBADDR	3
#घोषणा CMD0_FIFO_PRIV_XMIT_MODE(m)	((m) << 27)
#घोषणा CMD0_FIFO_SBCA			BIT(26)
#घोषणा CMD0_FIFO_RSBC			BIT(25)
#घोषणा CMD0_FIFO_IS_10B		BIT(24)
#घोषणा CMD0_FIFO_PL_LEN(l)		((l) << 12)
#घोषणा CMD0_FIFO_PL_LEN_MAX		4095
#घोषणा CMD0_FIFO_DEV_ADDR(a)		((a) << 1)
#घोषणा CMD0_FIFO_RNW			BIT(0)

#घोषणा CMD1_FIFO			0x64
#घोषणा CMD1_FIFO_CMDID(id)		((id) << 24)
#घोषणा CMD1_FIFO_CSRADDR(a)		(a)
#घोषणा CMD1_FIFO_CCC(id)		(id)

#घोषणा TX_FIFO				0x68

#घोषणा IMD_CMD0			0x70
#घोषणा IMD_CMD0_PL_LEN(l)		((l) << 12)
#घोषणा IMD_CMD0_DEV_ADDR(a)		((a) << 1)
#घोषणा IMD_CMD0_RNW			BIT(0)

#घोषणा IMD_CMD1			0x74
#घोषणा IMD_CMD1_CCC(id)		(id)

#घोषणा IMD_DATA			0x78
#घोषणा RX_FIFO				0x80
#घोषणा IBI_DATA_FIFO			0x84
#घोषणा SLV_DDR_TX_FIFO			0x88
#घोषणा SLV_DDR_RX_FIFO			0x8c

#घोषणा CMD_IBI_THR_CTRL		0x90
#घोषणा IBIR_THR(t)			((t) << 24)
#घोषणा CMDR_THR(t)			((t) << 16)
#घोषणा IBI_THR(t)			((t) << 8)
#घोषणा CMD_THR(t)			(t)

#घोषणा TX_RX_THR_CTRL			0x94
#घोषणा RX_THR(t)			((t) << 16)
#घोषणा TX_THR(t)			(t)

#घोषणा SLV_DDR_TX_RX_THR_CTRL		0x98
#घोषणा SLV_DDR_RX_THR(t)		((t) << 16)
#घोषणा SLV_DDR_TX_THR(t)		(t)

#घोषणा FLUSH_CTRL			0x9c
#घोषणा FLUSH_IBI_RESP			BIT(23)
#घोषणा FLUSH_CMD_RESP			BIT(22)
#घोषणा FLUSH_SLV_DDR_RX_FIFO		BIT(22)
#घोषणा FLUSH_SLV_DDR_TX_FIFO		BIT(21)
#घोषणा FLUSH_IMM_FIFO			BIT(20)
#घोषणा FLUSH_IBI_FIFO			BIT(19)
#घोषणा FLUSH_RX_FIFO			BIT(18)
#घोषणा FLUSH_TX_FIFO			BIT(17)
#घोषणा FLUSH_CMD_FIFO			BIT(16)

#घोषणा TTO_PRESCL_CTRL0		0xb0
#घोषणा TTO_PRESCL_CTRL0_DIVB(x)	((x) << 16)
#घोषणा TTO_PRESCL_CTRL0_DIVA(x)	(x)

#घोषणा TTO_PRESCL_CTRL1		0xb4
#घोषणा TTO_PRESCL_CTRL1_DIVB(x)	((x) << 16)
#घोषणा TTO_PRESCL_CTRL1_DIVA(x)	(x)

#घोषणा DEVS_CTRL			0xb8
#घोषणा DEVS_CTRL_DEV_CLR_SHIFT		16
#घोषणा DEVS_CTRL_DEV_CLR_ALL		GENMASK(31, 16)
#घोषणा DEVS_CTRL_DEV_CLR(dev)		BIT(16 + (dev))
#घोषणा DEVS_CTRL_DEV_ACTIVE(dev)	BIT(dev)
#घोषणा DEVS_CTRL_DEVS_ACTIVE_MASK	GENMASK(15, 0)
#घोषणा MAX_DEVS			16

#घोषणा DEV_ID_RR0(d)			(0xc0 + ((d) * 0x10))
#घोषणा DEV_ID_RR0_LVR_EXT_ADDR		BIT(11)
#घोषणा DEV_ID_RR0_HDR_CAP		BIT(10)
#घोषणा DEV_ID_RR0_IS_I3C		BIT(9)
#घोषणा DEV_ID_RR0_DEV_ADDR_MASK	(GENMASK(6, 0) | GENMASK(15, 13))
#घोषणा DEV_ID_RR0_SET_DEV_ADDR(a)	(((a) & GENMASK(6, 0)) |	\
					 (((a) & GENMASK(9, 7)) << 6))
#घोषणा DEV_ID_RR0_GET_DEV_ADDR(x)	((((x) >> 1) & GENMASK(6, 0)) |	\
					 (((x) >> 6) & GENMASK(9, 7)))

#घोषणा DEV_ID_RR1(d)			(0xc4 + ((d) * 0x10))
#घोषणा DEV_ID_RR1_PID_MSB(pid)		(pid)

#घोषणा DEV_ID_RR2(d)			(0xc8 + ((d) * 0x10))
#घोषणा DEV_ID_RR2_PID_LSB(pid)		((pid) << 16)
#घोषणा DEV_ID_RR2_BCR(bcr)		((bcr) << 8)
#घोषणा DEV_ID_RR2_DCR(dcr)		(dcr)
#घोषणा DEV_ID_RR2_LVR(lvr)		(lvr)

#घोषणा SIR_MAP(x)			(0x180 + ((x) * 4))
#घोषणा SIR_MAP_DEV_REG(d)		SIR_MAP((d) / 2)
#घोषणा SIR_MAP_DEV_SHIFT(d, fs)	((fs) + (((d) % 2) ? 16 : 0))
#घोषणा SIR_MAP_DEV_CONF_MASK(d)	(GENMASK(15, 0) << (((d) % 2) ? 16 : 0))
#घोषणा SIR_MAP_DEV_CONF(d, c)		((c) << (((d) % 2) ? 16 : 0))
#घोषणा DEV_ROLE_SLAVE			0
#घोषणा DEV_ROLE_MASTER			1
#घोषणा SIR_MAP_DEV_ROLE(role)		((role) << 14)
#घोषणा SIR_MAP_DEV_SLOW		BIT(13)
#घोषणा SIR_MAP_DEV_PL(l)		((l) << 8)
#घोषणा SIR_MAP_PL_MAX			GENMASK(4, 0)
#घोषणा SIR_MAP_DEV_DA(a)		((a) << 1)
#घोषणा SIR_MAP_DEV_ACK			BIT(0)

#घोषणा GPIR_WORD(x)			(0x200 + ((x) * 4))
#घोषणा GPI_REG(val, id)		\
	(((val) >> (((id) % 4) * 8)) & GENMASK(7, 0))

#घोषणा GPOR_WORD(x)			(0x220 + ((x) * 4))
#घोषणा GPO_REG(val, id)		\
	(((val) >> (((id) % 4) * 8)) & GENMASK(7, 0))

#घोषणा ASF_INT_STATUS			0x300
#घोषणा ASF_INT_RAW_STATUS		0x304
#घोषणा ASF_INT_MASK			0x308
#घोषणा ASF_INT_TEST			0x30c
#घोषणा ASF_INT_FATAL_SELECT		0x310
#घोषणा ASF_INTEGRITY_ERR		BIT(6)
#घोषणा ASF_PROTOCOL_ERR		BIT(5)
#घोषणा ASF_TRANS_TIMEOUT_ERR		BIT(4)
#घोषणा ASF_CSR_ERR			BIT(3)
#घोषणा ASF_DAP_ERR			BIT(2)
#घोषणा ASF_SRAM_UNCORR_ERR		BIT(1)
#घोषणा ASF_SRAM_CORR_ERR		BIT(0)

#घोषणा ASF_SRAM_CORR_FAULT_STATUS	0x320
#घोषणा ASF_SRAM_UNCORR_FAULT_STATUS	0x324
#घोषणा ASF_SRAM_CORR_FAULT_INSTANCE(x)	((x) >> 24)
#घोषणा ASF_SRAM_CORR_FAULT_ADDR(x)	((x) & GENMASK(23, 0))

#घोषणा ASF_SRAM_FAULT_STATS		0x328
#घोषणा ASF_SRAM_FAULT_UNCORR_STATS(x)	((x) >> 16)
#घोषणा ASF_SRAM_FAULT_CORR_STATS(x)	((x) & GENMASK(15, 0))

#घोषणा ASF_TRANS_TOUT_CTRL		0x330
#घोषणा ASF_TRANS_TOUT_EN		BIT(31)
#घोषणा ASF_TRANS_TOUT_VAL(x)	(x)

#घोषणा ASF_TRANS_TOUT_FAULT_MASK	0x334
#घोषणा ASF_TRANS_TOUT_FAULT_STATUS	0x338
#घोषणा ASF_TRANS_TOUT_FAULT_APB	BIT(3)
#घोषणा ASF_TRANS_TOUT_FAULT_SCL_LOW	BIT(2)
#घोषणा ASF_TRANS_TOUT_FAULT_SCL_HIGH	BIT(1)
#घोषणा ASF_TRANS_TOUT_FAULT_FSCL_HIGH	BIT(0)

#घोषणा ASF_PROTO_FAULT_MASK		0x340
#घोषणा ASF_PROTO_FAULT_STATUS		0x344
#घोषणा ASF_PROTO_FAULT_SLVSDR_RD_ABORT	BIT(31)
#घोषणा ASF_PROTO_FAULT_SLVDDR_FAIL	BIT(30)
#घोषणा ASF_PROTO_FAULT_S(x)		BIT(16 + (x))
#घोषणा ASF_PROTO_FAULT_MSTSDR_RD_ABORT	BIT(15)
#घोषणा ASF_PROTO_FAULT_MSTDDR_FAIL	BIT(14)
#घोषणा ASF_PROTO_FAULT_M(x)		BIT(x)

काष्ठा cdns_i3c_master_caps अणु
	u32 cmdfअगरodepth;
	u32 cmdrfअगरodepth;
	u32 txfअगरodepth;
	u32 rxfअगरodepth;
	u32 ibirfअगरodepth;
पूर्ण;

काष्ठा cdns_i3c_cmd अणु
	u32 cmd0;
	u32 cmd1;
	u32 tx_len;
	स्थिर व्योम *tx_buf;
	u32 rx_len;
	व्योम *rx_buf;
	u32 error;
पूर्ण;

काष्ठा cdns_i3c_xfer अणु
	काष्ठा list_head node;
	काष्ठा completion comp;
	पूर्णांक ret;
	अचिन्हित पूर्णांक ncmds;
	काष्ठा cdns_i3c_cmd cmds[];
पूर्ण;

काष्ठा cdns_i3c_data अणु
	u8 thd_delay_ns;
पूर्ण;

काष्ठा cdns_i3c_master अणु
	काष्ठा work_काष्ठा hj_work;
	काष्ठा i3c_master_controller base;
	u32 मुक्त_rr_slots;
	अचिन्हित पूर्णांक maxdevs;
	काष्ठा अणु
		अचिन्हित पूर्णांक num_slots;
		काष्ठा i3c_dev_desc **slots;
		spinlock_t lock;
	पूर्ण ibi;
	काष्ठा अणु
		काष्ठा list_head list;
		काष्ठा cdns_i3c_xfer *cur;
		spinlock_t lock;
	पूर्ण xferqueue;
	व्योम __iomem *regs;
	काष्ठा clk *sysclk;
	काष्ठा clk *pclk;
	काष्ठा cdns_i3c_master_caps caps;
	अचिन्हित दीर्घ i3c_scl_lim;
	स्थिर काष्ठा cdns_i3c_data *devdata;
पूर्ण;

अटल अंतरभूत काष्ठा cdns_i3c_master *
to_cdns_i3c_master(काष्ठा i3c_master_controller *master)
अणु
	वापस container_of(master, काष्ठा cdns_i3c_master, base);
पूर्ण

अटल व्योम cdns_i3c_master_wr_to_tx_fअगरo(काष्ठा cdns_i3c_master *master,
					  स्थिर u8 *bytes, पूर्णांक nbytes)
अणु
	ग_लिखोsl(master->regs + TX_FIFO, bytes, nbytes / 4);
	अगर (nbytes & 3) अणु
		u32 पंचांगp = 0;

		स_नकल(&पंचांगp, bytes + (nbytes & ~3), nbytes & 3);
		ग_लिखोsl(master->regs + TX_FIFO, &पंचांगp, 1);
	पूर्ण
पूर्ण

अटल व्योम cdns_i3c_master_rd_from_rx_fअगरo(काष्ठा cdns_i3c_master *master,
					    u8 *bytes, पूर्णांक nbytes)
अणु
	पढ़ोsl(master->regs + RX_FIFO, bytes, nbytes / 4);
	अगर (nbytes & 3) अणु
		u32 पंचांगp;

		पढ़ोsl(master->regs + RX_FIFO, &पंचांगp, 1);
		स_नकल(bytes + (nbytes & ~3), &पंचांगp, nbytes & 3);
	पूर्ण
पूर्ण

अटल bool cdns_i3c_master_supports_ccc_cmd(काष्ठा i3c_master_controller *m,
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
	हाल I3C_CCC_DEFSLVS:
	हाल I3C_CCC_ENTHDR(0):
	हाल I3C_CCC_SETDASA:
	हाल I3C_CCC_SETNEWDA:
	हाल I3C_CCC_GETMWL:
	हाल I3C_CCC_GETMRL:
	हाल I3C_CCC_GETPID:
	हाल I3C_CCC_GETBCR:
	हाल I3C_CCC_GETDCR:
	हाल I3C_CCC_GETSTATUS:
	हाल I3C_CCC_GETACCMST:
	हाल I3C_CCC_GETMXDS:
	हाल I3C_CCC_GETHDRCAP:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक cdns_i3c_master_disable(काष्ठा cdns_i3c_master *master)
अणु
	u32 status;

	ग_लिखोl(पढ़ोl(master->regs + CTRL) & ~CTRL_DEV_EN, master->regs + CTRL);

	वापस पढ़ोl_poll_समयout(master->regs + MST_STATUS0, status,
				  status & MST_STATUS0_IDLE, 10, 1000000);
पूर्ण

अटल व्योम cdns_i3c_master_enable(काष्ठा cdns_i3c_master *master)
अणु
	ग_लिखोl(पढ़ोl(master->regs + CTRL) | CTRL_DEV_EN, master->regs + CTRL);
पूर्ण

अटल काष्ठा cdns_i3c_xfer *
cdns_i3c_master_alloc_xfer(काष्ठा cdns_i3c_master *master, अचिन्हित पूर्णांक ncmds)
अणु
	काष्ठा cdns_i3c_xfer *xfer;

	xfer = kzalloc(काष्ठा_size(xfer, cmds, ncmds), GFP_KERNEL);
	अगर (!xfer)
		वापस शून्य;

	INIT_LIST_HEAD(&xfer->node);
	xfer->ncmds = ncmds;
	xfer->ret = -ETIMEDOUT;

	वापस xfer;
पूर्ण

अटल व्योम cdns_i3c_master_मुक्त_xfer(काष्ठा cdns_i3c_xfer *xfer)
अणु
	kमुक्त(xfer);
पूर्ण

अटल व्योम cdns_i3c_master_start_xfer_locked(काष्ठा cdns_i3c_master *master)
अणु
	काष्ठा cdns_i3c_xfer *xfer = master->xferqueue.cur;
	अचिन्हित पूर्णांक i;

	अगर (!xfer)
		वापस;

	ग_लिखोl(MST_INT_CMDD_EMP, master->regs + MST_ICR);
	क्रम (i = 0; i < xfer->ncmds; i++) अणु
		काष्ठा cdns_i3c_cmd *cmd = &xfer->cmds[i];

		cdns_i3c_master_wr_to_tx_fअगरo(master, cmd->tx_buf,
					      cmd->tx_len);
	पूर्ण

	क्रम (i = 0; i < xfer->ncmds; i++) अणु
		काष्ठा cdns_i3c_cmd *cmd = &xfer->cmds[i];

		ग_लिखोl(cmd->cmd1 | CMD1_FIFO_CMDID(i),
		       master->regs + CMD1_FIFO);
		ग_लिखोl(cmd->cmd0, master->regs + CMD0_FIFO);
	पूर्ण

	ग_लिखोl(पढ़ोl(master->regs + CTRL) | CTRL_MCS,
	       master->regs + CTRL);
	ग_लिखोl(MST_INT_CMDD_EMP, master->regs + MST_IER);
पूर्ण

अटल व्योम cdns_i3c_master_end_xfer_locked(काष्ठा cdns_i3c_master *master,
					    u32 isr)
अणु
	काष्ठा cdns_i3c_xfer *xfer = master->xferqueue.cur;
	पूर्णांक i, ret = 0;
	u32 status0;

	अगर (!xfer)
		वापस;

	अगर (!(isr & MST_INT_CMDD_EMP))
		वापस;

	ग_लिखोl(MST_INT_CMDD_EMP, master->regs + MST_IDR);

	क्रम (status0 = पढ़ोl(master->regs + MST_STATUS0);
	     !(status0 & MST_STATUS0_CMDR_EMP);
	     status0 = पढ़ोl(master->regs + MST_STATUS0)) अणु
		काष्ठा cdns_i3c_cmd *cmd;
		u32 cmdr, rx_len, id;

		cmdr = पढ़ोl(master->regs + CMDR);
		id = CMDR_CMDID(cmdr);
		अगर (id == CMDR_CMDID_HJACK_DISEC ||
		    id == CMDR_CMDID_HJACK_ENTDAA ||
		    WARN_ON(id >= xfer->ncmds))
			जारी;

		cmd = &xfer->cmds[CMDR_CMDID(cmdr)];
		rx_len = min_t(u32, CMDR_XFER_BYTES(cmdr), cmd->rx_len);
		cdns_i3c_master_rd_from_rx_fअगरo(master, cmd->rx_buf, rx_len);
		cmd->error = CMDR_ERROR(cmdr);
	पूर्ण

	क्रम (i = 0; i < xfer->ncmds; i++) अणु
		चयन (xfer->cmds[i].error) अणु
		हाल CMDR_NO_ERROR:
			अवरोध;

		हाल CMDR_DDR_PREAMBLE_ERROR:
		हाल CMDR_DDR_PARITY_ERROR:
		हाल CMDR_M0_ERROR:
		हाल CMDR_M1_ERROR:
		हाल CMDR_M2_ERROR:
		हाल CMDR_MST_ABORT:
		हाल CMDR_NACK_RESP:
		हाल CMDR_DDR_DROPPED:
			ret = -EIO;
			अवरोध;

		हाल CMDR_DDR_RX_FIFO_OVF:
		हाल CMDR_DDR_TX_FIFO_UNF:
			ret = -ENOSPC;
			अवरोध;

		हाल CMDR_INVALID_DA:
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	xfer->ret = ret;
	complete(&xfer->comp);

	xfer = list_first_entry_or_null(&master->xferqueue.list,
					काष्ठा cdns_i3c_xfer, node);
	अगर (xfer)
		list_del_init(&xfer->node);

	master->xferqueue.cur = xfer;
	cdns_i3c_master_start_xfer_locked(master);
पूर्ण

अटल व्योम cdns_i3c_master_queue_xfer(काष्ठा cdns_i3c_master *master,
				       काष्ठा cdns_i3c_xfer *xfer)
अणु
	अचिन्हित दीर्घ flags;

	init_completion(&xfer->comp);
	spin_lock_irqsave(&master->xferqueue.lock, flags);
	अगर (master->xferqueue.cur) अणु
		list_add_tail(&xfer->node, &master->xferqueue.list);
	पूर्ण अन्यथा अणु
		master->xferqueue.cur = xfer;
		cdns_i3c_master_start_xfer_locked(master);
	पूर्ण
	spin_unlock_irqrestore(&master->xferqueue.lock, flags);
पूर्ण

अटल व्योम cdns_i3c_master_unqueue_xfer(काष्ठा cdns_i3c_master *master,
					 काष्ठा cdns_i3c_xfer *xfer)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&master->xferqueue.lock, flags);
	अगर (master->xferqueue.cur == xfer) अणु
		u32 status;

		ग_लिखोl(पढ़ोl(master->regs + CTRL) & ~CTRL_DEV_EN,
		       master->regs + CTRL);
		पढ़ोl_poll_समयout_atomic(master->regs + MST_STATUS0, status,
					  status & MST_STATUS0_IDLE, 10,
					  1000000);
		master->xferqueue.cur = शून्य;
		ग_लिखोl(FLUSH_RX_FIFO | FLUSH_TX_FIFO | FLUSH_CMD_FIFO |
		       FLUSH_CMD_RESP,
		       master->regs + FLUSH_CTRL);
		ग_लिखोl(MST_INT_CMDD_EMP, master->regs + MST_IDR);
		ग_लिखोl(पढ़ोl(master->regs + CTRL) | CTRL_DEV_EN,
		       master->regs + CTRL);
	पूर्ण अन्यथा अणु
		list_del_init(&xfer->node);
	पूर्ण
	spin_unlock_irqrestore(&master->xferqueue.lock, flags);
पूर्ण

अटल क्रमागत i3c_error_code cdns_i3c_cmd_get_err(काष्ठा cdns_i3c_cmd *cmd)
अणु
	चयन (cmd->error) अणु
	हाल CMDR_M0_ERROR:
		वापस I3C_ERROR_M0;

	हाल CMDR_M1_ERROR:
		वापस I3C_ERROR_M1;

	हाल CMDR_M2_ERROR:
	हाल CMDR_NACK_RESP:
		वापस I3C_ERROR_M2;

	शेष:
		अवरोध;
	पूर्ण

	वापस I3C_ERROR_UNKNOWN;
पूर्ण

अटल पूर्णांक cdns_i3c_master_send_ccc_cmd(काष्ठा i3c_master_controller *m,
					काष्ठा i3c_ccc_cmd *cmd)
अणु
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);
	काष्ठा cdns_i3c_xfer *xfer;
	काष्ठा cdns_i3c_cmd *ccmd;
	पूर्णांक ret;

	xfer = cdns_i3c_master_alloc_xfer(master, 1);
	अगर (!xfer)
		वापस -ENOMEM;

	ccmd = xfer->cmds;
	ccmd->cmd1 = CMD1_FIFO_CCC(cmd->id);
	ccmd->cmd0 = CMD0_FIFO_IS_CCC |
		     CMD0_FIFO_PL_LEN(cmd->dests[0].payload.len);

	अगर (cmd->id & I3C_CCC_सूचीECT)
		ccmd->cmd0 |= CMD0_FIFO_DEV_ADDR(cmd->dests[0].addr);

	अगर (cmd->rnw) अणु
		ccmd->cmd0 |= CMD0_FIFO_RNW;
		ccmd->rx_buf = cmd->dests[0].payload.data;
		ccmd->rx_len = cmd->dests[0].payload.len;
	पूर्ण अन्यथा अणु
		ccmd->tx_buf = cmd->dests[0].payload.data;
		ccmd->tx_len = cmd->dests[0].payload.len;
	पूर्ण

	cdns_i3c_master_queue_xfer(master, xfer);
	अगर (!रुको_क्रम_completion_समयout(&xfer->comp, msecs_to_jअगरfies(1000)))
		cdns_i3c_master_unqueue_xfer(master, xfer);

	ret = xfer->ret;
	cmd->err = cdns_i3c_cmd_get_err(&xfer->cmds[0]);
	cdns_i3c_master_मुक्त_xfer(xfer);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_i3c_master_priv_xfers(काष्ठा i3c_dev_desc *dev,
				      काष्ठा i3c_priv_xfer *xfers,
				      पूर्णांक nxfers)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);
	पूर्णांक txslots = 0, rxslots = 0, i, ret;
	काष्ठा cdns_i3c_xfer *cdns_xfer;

	क्रम (i = 0; i < nxfers; i++) अणु
		अगर (xfers[i].len > CMD0_FIFO_PL_LEN_MAX)
			वापस -ENOTSUPP;
	पूर्ण

	अगर (!nxfers)
		वापस 0;

	अगर (nxfers > master->caps.cmdfअगरodepth ||
	    nxfers > master->caps.cmdrfअगरodepth)
		वापस -ENOTSUPP;

	/*
	 * First make sure that all transactions (block of transfers separated
	 * by a STOP marker) fit in the FIFOs.
	 */
	क्रम (i = 0; i < nxfers; i++) अणु
		अगर (xfers[i].rnw)
			rxslots += DIV_ROUND_UP(xfers[i].len, 4);
		अन्यथा
			txslots += DIV_ROUND_UP(xfers[i].len, 4);
	पूर्ण

	अगर (rxslots > master->caps.rxfअगरodepth ||
	    txslots > master->caps.txfअगरodepth)
		वापस -ENOTSUPP;

	cdns_xfer = cdns_i3c_master_alloc_xfer(master, nxfers);
	अगर (!cdns_xfer)
		वापस -ENOMEM;

	क्रम (i = 0; i < nxfers; i++) अणु
		काष्ठा cdns_i3c_cmd *ccmd = &cdns_xfer->cmds[i];
		u32 pl_len = xfers[i].len;

		ccmd->cmd0 = CMD0_FIFO_DEV_ADDR(dev->info.dyn_addr) |
			CMD0_FIFO_PRIV_XMIT_MODE(XMIT_BURST_WITHOUT_SUBADDR);

		अगर (xfers[i].rnw) अणु
			ccmd->cmd0 |= CMD0_FIFO_RNW;
			ccmd->rx_buf = xfers[i].data.in;
			ccmd->rx_len = xfers[i].len;
			pl_len++;
		पूर्ण अन्यथा अणु
			ccmd->tx_buf = xfers[i].data.out;
			ccmd->tx_len = xfers[i].len;
		पूर्ण

		ccmd->cmd0 |= CMD0_FIFO_PL_LEN(pl_len);

		अगर (i < nxfers - 1)
			ccmd->cmd0 |= CMD0_FIFO_RSBC;

		अगर (!i)
			ccmd->cmd0 |= CMD0_FIFO_BCH;
	पूर्ण

	cdns_i3c_master_queue_xfer(master, cdns_xfer);
	अगर (!रुको_क्रम_completion_समयout(&cdns_xfer->comp,
					 msecs_to_jअगरfies(1000)))
		cdns_i3c_master_unqueue_xfer(master, cdns_xfer);

	ret = cdns_xfer->ret;

	क्रम (i = 0; i < nxfers; i++)
		xfers[i].err = cdns_i3c_cmd_get_err(&cdns_xfer->cmds[i]);

	cdns_i3c_master_मुक्त_xfer(cdns_xfer);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_i3c_master_i2c_xfers(काष्ठा i2c_dev_desc *dev,
				     स्थिर काष्ठा i2c_msg *xfers, पूर्णांक nxfers)
अणु
	काष्ठा i3c_master_controller *m = i2c_dev_get_master(dev);
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);
	अचिन्हित पूर्णांक nrxwords = 0, ntxwords = 0;
	काष्ठा cdns_i3c_xfer *xfer;
	पूर्णांक i, ret = 0;

	अगर (nxfers > master->caps.cmdfअगरodepth)
		वापस -ENOTSUPP;

	क्रम (i = 0; i < nxfers; i++) अणु
		अगर (xfers[i].len > CMD0_FIFO_PL_LEN_MAX)
			वापस -ENOTSUPP;

		अगर (xfers[i].flags & I2C_M_RD)
			nrxwords += DIV_ROUND_UP(xfers[i].len, 4);
		अन्यथा
			ntxwords += DIV_ROUND_UP(xfers[i].len, 4);
	पूर्ण

	अगर (ntxwords > master->caps.txfअगरodepth ||
	    nrxwords > master->caps.rxfअगरodepth)
		वापस -ENOTSUPP;

	xfer = cdns_i3c_master_alloc_xfer(master, nxfers);
	अगर (!xfer)
		वापस -ENOMEM;

	क्रम (i = 0; i < nxfers; i++) अणु
		काष्ठा cdns_i3c_cmd *ccmd = &xfer->cmds[i];

		ccmd->cmd0 = CMD0_FIFO_DEV_ADDR(xfers[i].addr) |
			CMD0_FIFO_PL_LEN(xfers[i].len) |
			CMD0_FIFO_PRIV_XMIT_MODE(XMIT_BURST_WITHOUT_SUBADDR);

		अगर (xfers[i].flags & I2C_M_TEN)
			ccmd->cmd0 |= CMD0_FIFO_IS_10B;

		अगर (xfers[i].flags & I2C_M_RD) अणु
			ccmd->cmd0 |= CMD0_FIFO_RNW;
			ccmd->rx_buf = xfers[i].buf;
			ccmd->rx_len = xfers[i].len;
		पूर्ण अन्यथा अणु
			ccmd->tx_buf = xfers[i].buf;
			ccmd->tx_len = xfers[i].len;
		पूर्ण
	पूर्ण

	cdns_i3c_master_queue_xfer(master, xfer);
	अगर (!रुको_क्रम_completion_समयout(&xfer->comp, msecs_to_jअगरfies(1000)))
		cdns_i3c_master_unqueue_xfer(master, xfer);

	ret = xfer->ret;
	cdns_i3c_master_मुक्त_xfer(xfer);

	वापस ret;
पूर्ण

काष्ठा cdns_i3c_i2c_dev_data अणु
	u16 id;
	s16 ibi;
	काष्ठा i3c_generic_ibi_pool *ibi_pool;
पूर्ण;

अटल u32 prepare_rr0_dev_address(u32 addr)
अणु
	u32 ret = (addr << 1) & 0xff;

	/* RR0[7:1] = addr[6:0] */
	ret |= (addr & GENMASK(6, 0)) << 1;

	/* RR0[15:13] = addr[9:7] */
	ret |= (addr & GENMASK(9, 7)) << 6;

	/* RR0[0] = ~XOR(addr[6:0]) */
	अगर (!(hweight8(addr & 0x7f) & 1))
		ret |= 1;

	वापस ret;
पूर्ण

अटल व्योम cdns_i3c_master_upd_i3c_addr(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);
	काष्ठा cdns_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	u32 rr;

	rr = prepare_rr0_dev_address(dev->info.dyn_addr ?
				     dev->info.dyn_addr :
				     dev->info.अटल_addr);
	ग_लिखोl(DEV_ID_RR0_IS_I3C | rr, master->regs + DEV_ID_RR0(data->id));
पूर्ण

अटल पूर्णांक cdns_i3c_master_get_rr_slot(काष्ठा cdns_i3c_master *master,
				       u8 dyn_addr)
अणु
	अचिन्हित दीर्घ activedevs;
	u32 rr;
	पूर्णांक i;

	अगर (!dyn_addr) अणु
		अगर (!master->मुक्त_rr_slots)
			वापस -ENOSPC;

		वापस ffs(master->मुक्त_rr_slots) - 1;
	पूर्ण

	activedevs = पढ़ोl(master->regs + DEVS_CTRL) & DEVS_CTRL_DEVS_ACTIVE_MASK;
	activedevs &= ~BIT(0);

	क्रम_each_set_bit(i, &activedevs, master->maxdevs + 1) अणु
		rr = पढ़ोl(master->regs + DEV_ID_RR0(i));
		अगर (!(rr & DEV_ID_RR0_IS_I3C) ||
		    DEV_ID_RR0_GET_DEV_ADDR(rr) != dyn_addr)
			जारी;

		वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cdns_i3c_master_reattach_i3c_dev(काष्ठा i3c_dev_desc *dev,
					    u8 old_dyn_addr)
अणु
	cdns_i3c_master_upd_i3c_addr(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_i3c_master_attach_i3c_dev(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);
	काष्ठा cdns_i3c_i2c_dev_data *data;
	पूर्णांक slot;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	slot = cdns_i3c_master_get_rr_slot(master, dev->info.dyn_addr);
	अगर (slot < 0) अणु
		kमुक्त(data);
		वापस slot;
	पूर्ण

	data->ibi = -1;
	data->id = slot;
	i3c_dev_set_master_data(dev, data);
	master->मुक्त_rr_slots &= ~BIT(slot);

	अगर (!dev->info.dyn_addr) अणु
		cdns_i3c_master_upd_i3c_addr(dev);
		ग_लिखोl(पढ़ोl(master->regs + DEVS_CTRL) |
		       DEVS_CTRL_DEV_ACTIVE(data->id),
		       master->regs + DEVS_CTRL);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cdns_i3c_master_detach_i3c_dev(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);
	काष्ठा cdns_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);

	ग_लिखोl(पढ़ोl(master->regs + DEVS_CTRL) |
	       DEVS_CTRL_DEV_CLR(data->id),
	       master->regs + DEVS_CTRL);

	i3c_dev_set_master_data(dev, शून्य);
	master->मुक्त_rr_slots |= BIT(data->id);
	kमुक्त(data);
पूर्ण

अटल पूर्णांक cdns_i3c_master_attach_i2c_dev(काष्ठा i2c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i2c_dev_get_master(dev);
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);
	काष्ठा cdns_i3c_i2c_dev_data *data;
	पूर्णांक slot;

	slot = cdns_i3c_master_get_rr_slot(master, 0);
	अगर (slot < 0)
		वापस slot;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->id = slot;
	master->मुक्त_rr_slots &= ~BIT(slot);
	i2c_dev_set_master_data(dev, data);

	ग_लिखोl(prepare_rr0_dev_address(dev->addr),
	       master->regs + DEV_ID_RR0(data->id));
	ग_लिखोl(dev->lvr, master->regs + DEV_ID_RR2(data->id));
	ग_लिखोl(पढ़ोl(master->regs + DEVS_CTRL) |
	       DEVS_CTRL_DEV_ACTIVE(data->id),
	       master->regs + DEVS_CTRL);

	वापस 0;
पूर्ण

अटल व्योम cdns_i3c_master_detach_i2c_dev(काष्ठा i2c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i2c_dev_get_master(dev);
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);
	काष्ठा cdns_i3c_i2c_dev_data *data = i2c_dev_get_master_data(dev);

	ग_लिखोl(पढ़ोl(master->regs + DEVS_CTRL) |
	       DEVS_CTRL_DEV_CLR(data->id),
	       master->regs + DEVS_CTRL);
	master->मुक्त_rr_slots |= BIT(data->id);

	i2c_dev_set_master_data(dev, शून्य);
	kमुक्त(data);
पूर्ण

अटल व्योम cdns_i3c_master_bus_cleanup(काष्ठा i3c_master_controller *m)
अणु
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);

	cdns_i3c_master_disable(master);
पूर्ण

अटल व्योम cdns_i3c_master_dev_rr_to_info(काष्ठा cdns_i3c_master *master,
					   अचिन्हित पूर्णांक slot,
					   काष्ठा i3c_device_info *info)
अणु
	u32 rr;

	स_रखो(info, 0, माप(*info));
	rr = पढ़ोl(master->regs + DEV_ID_RR0(slot));
	info->dyn_addr = DEV_ID_RR0_GET_DEV_ADDR(rr);
	rr = पढ़ोl(master->regs + DEV_ID_RR2(slot));
	info->dcr = rr;
	info->bcr = rr >> 8;
	info->pid = rr >> 16;
	info->pid |= (u64)पढ़ोl(master->regs + DEV_ID_RR1(slot)) << 16;
पूर्ण

अटल व्योम cdns_i3c_master_upd_i3c_scl_lim(काष्ठा cdns_i3c_master *master)
अणु
	काष्ठा i3c_master_controller *m = &master->base;
	अचिन्हित दीर्घ i3c_lim_period, pres_step, ncycles;
	काष्ठा i3c_bus *bus = i3c_master_get_bus(m);
	अचिन्हित दीर्घ new_i3c_scl_lim = 0;
	काष्ठा i3c_dev_desc *dev;
	u32 prescl1, ctrl;

	i3c_bus_क्रम_each_i3cdev(bus, dev) अणु
		अचिन्हित दीर्घ max_fscl;

		max_fscl = max(I3C_CCC_MAX_SDR_FSCL(dev->info.max_पढ़ो_ds),
			       I3C_CCC_MAX_SDR_FSCL(dev->info.max_ग_लिखो_ds));
		चयन (max_fscl) अणु
		हाल I3C_SDR1_FSCL_8MHZ:
			max_fscl = 8000000;
			अवरोध;
		हाल I3C_SDR2_FSCL_6MHZ:
			max_fscl = 6000000;
			अवरोध;
		हाल I3C_SDR3_FSCL_4MHZ:
			max_fscl = 4000000;
			अवरोध;
		हाल I3C_SDR4_FSCL_2MHZ:
			max_fscl = 2000000;
			अवरोध;
		हाल I3C_SDR0_FSCL_MAX:
		शेष:
			max_fscl = 0;
			अवरोध;
		पूर्ण

		अगर (max_fscl &&
		    (new_i3c_scl_lim > max_fscl || !new_i3c_scl_lim))
			new_i3c_scl_lim = max_fscl;
	पूर्ण

	/* Only update PRESCL_CTRL1 अगर the I3C SCL limitation has changed. */
	अगर (new_i3c_scl_lim == master->i3c_scl_lim)
		वापस;
	master->i3c_scl_lim = new_i3c_scl_lim;
	अगर (!new_i3c_scl_lim)
		वापस;
	pres_step = 1000000000UL / (bus->scl_rate.i3c * 4);

	/* Configure PP_LOW to meet I3C slave limitations. */
	prescl1 = पढ़ोl(master->regs + PRESCL_CTRL1) &
		  ~PRESCL_CTRL1_PP_LOW_MASK;
	ctrl = पढ़ोl(master->regs + CTRL);

	i3c_lim_period = DIV_ROUND_UP(1000000000, master->i3c_scl_lim);
	ncycles = DIV_ROUND_UP(i3c_lim_period, pres_step);
	अगर (ncycles < 4)
		ncycles = 0;
	अन्यथा
		ncycles -= 4;

	prescl1 |= PRESCL_CTRL1_PP_LOW(ncycles);

	/* Disable I3C master beक्रमe updating PRESCL_CTRL1. */
	अगर (ctrl & CTRL_DEV_EN)
		cdns_i3c_master_disable(master);

	ग_लिखोl(prescl1, master->regs + PRESCL_CTRL1);

	अगर (ctrl & CTRL_DEV_EN)
		cdns_i3c_master_enable(master);
पूर्ण

अटल पूर्णांक cdns_i3c_master_करो_daa(काष्ठा i3c_master_controller *m)
अणु
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);
	अचिन्हित दीर्घ olddevs, newdevs;
	पूर्णांक ret, slot;
	u8 addrs[MAX_DEVS] = अणु पूर्ण;
	u8 last_addr = 0;

	olddevs = पढ़ोl(master->regs + DEVS_CTRL) & DEVS_CTRL_DEVS_ACTIVE_MASK;
	olddevs |= BIT(0);

	/* Prepare RR slots beक्रमe launching DAA. */
	क्रम_each_clear_bit(slot, &olddevs, master->maxdevs + 1) अणु
		ret = i3c_master_get_मुक्त_addr(m, last_addr + 1);
		अगर (ret < 0)
			वापस -ENOSPC;

		last_addr = ret;
		addrs[slot] = last_addr;
		ग_लिखोl(prepare_rr0_dev_address(last_addr) | DEV_ID_RR0_IS_I3C,
		       master->regs + DEV_ID_RR0(slot));
		ग_लिखोl(0, master->regs + DEV_ID_RR1(slot));
		ग_लिखोl(0, master->regs + DEV_ID_RR2(slot));
	पूर्ण

	ret = i3c_master_entdaa_locked(&master->base);
	अगर (ret && ret != I3C_ERROR_M2)
		वापस ret;

	newdevs = पढ़ोl(master->regs + DEVS_CTRL) & DEVS_CTRL_DEVS_ACTIVE_MASK;
	newdevs &= ~olddevs;

	/*
	 * Clear all retaining रेजिस्टरs filled during DAA. We alपढ़ोy
	 * have the addressed asचिन्हित to them in the addrs array.
	 */
	क्रम_each_set_bit(slot, &newdevs, master->maxdevs + 1)
		i3c_master_add_i3c_dev_locked(m, addrs[slot]);

	/*
	 * Clear slots that ended up not being used. Can be caused by I3C
	 * device creation failure or when the I3C device was alपढ़ोy known
	 * by the प्रणाली but with a dअगरferent address (in this हाल the device
	 * alपढ़ोy has a slot and करोes not need a new one).
	 */
	ग_लिखोl(पढ़ोl(master->regs + DEVS_CTRL) |
	       master->मुक्त_rr_slots << DEVS_CTRL_DEV_CLR_SHIFT,
	       master->regs + DEVS_CTRL);

	i3c_master_defslvs_locked(&master->base);

	cdns_i3c_master_upd_i3c_scl_lim(master);

	/* Unmask Hot-Join and Mastership request पूर्णांकerrupts. */
	i3c_master_enec_locked(m, I3C_BROADCAST_ADDR,
			       I3C_CCC_EVENT_HJ | I3C_CCC_EVENT_MR);

	वापस 0;
पूर्ण

अटल u8 cdns_i3c_master_calculate_thd_delay(काष्ठा cdns_i3c_master *master)
अणु
	अचिन्हित दीर्घ sysclk_rate = clk_get_rate(master->sysclk);
	u8 thd_delay = DIV_ROUND_UP(master->devdata->thd_delay_ns,
				    (NSEC_PER_SEC / sysclk_rate));

	/* Every value greater than 3 is not valid. */
	अगर (thd_delay > THD_DELAY_MAX)
		thd_delay = THD_DELAY_MAX;

	/* CTLR_THD_DEL value is encoded. */
	वापस (THD_DELAY_MAX - thd_delay);
पूर्ण

अटल पूर्णांक cdns_i3c_master_bus_init(काष्ठा i3c_master_controller *m)
अणु
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);
	अचिन्हित दीर्घ pres_step, sysclk_rate, max_i2cfreq;
	काष्ठा i3c_bus *bus = i3c_master_get_bus(m);
	u32 ctrl, prescl0, prescl1, pres, low;
	काष्ठा i3c_device_info info = अणु पूर्ण;
	पूर्णांक ret, ncycles;

	चयन (bus->mode) अणु
	हाल I3C_BUS_MODE_PURE:
		ctrl = CTRL_PURE_BUS_MODE;
		अवरोध;

	हाल I3C_BUS_MODE_MIXED_FAST:
		ctrl = CTRL_MIXED_FAST_BUS_MODE;
		अवरोध;

	हाल I3C_BUS_MODE_MIXED_SLOW:
		ctrl = CTRL_MIXED_SLOW_BUS_MODE;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	sysclk_rate = clk_get_rate(master->sysclk);
	अगर (!sysclk_rate)
		वापस -EINVAL;

	pres = DIV_ROUND_UP(sysclk_rate, (bus->scl_rate.i3c * 4)) - 1;
	अगर (pres > PRESCL_CTRL0_MAX)
		वापस -दुस्फल;

	bus->scl_rate.i3c = sysclk_rate / ((pres + 1) * 4);

	prescl0 = PRESCL_CTRL0_I3C(pres);

	low = ((I3C_BUS_TLOW_OD_MIN_NS * sysclk_rate) / (pres + 1)) - 2;
	prescl1 = PRESCL_CTRL1_OD_LOW(low);

	max_i2cfreq = bus->scl_rate.i2c;

	pres = (sysclk_rate / (max_i2cfreq * 5)) - 1;
	अगर (pres > PRESCL_CTRL0_MAX)
		वापस -दुस्फल;

	bus->scl_rate.i2c = sysclk_rate / ((pres + 1) * 5);

	prescl0 |= PRESCL_CTRL0_I2C(pres);
	ग_लिखोl(prescl0, master->regs + PRESCL_CTRL0);

	/* Calculate OD and PP low. */
	pres_step = 1000000000 / (bus->scl_rate.i3c * 4);
	ncycles = DIV_ROUND_UP(I3C_BUS_TLOW_OD_MIN_NS, pres_step) - 2;
	अगर (ncycles < 0)
		ncycles = 0;
	prescl1 = PRESCL_CTRL1_OD_LOW(ncycles);
	ग_लिखोl(prescl1, master->regs + PRESCL_CTRL1);

	/* Get an address क्रम the master. */
	ret = i3c_master_get_मुक्त_addr(m, 0);
	अगर (ret < 0)
		वापस ret;

	ग_लिखोl(prepare_rr0_dev_address(ret) | DEV_ID_RR0_IS_I3C,
	       master->regs + DEV_ID_RR0(0));

	cdns_i3c_master_dev_rr_to_info(master, 0, &info);
	अगर (info.bcr & I3C_BCR_HDR_CAP)
		info.hdr_cap = I3C_CCC_HDR_MODE(I3C_HDR_DDR);

	ret = i3c_master_set_info(&master->base, &info);
	अगर (ret)
		वापस ret;

	/*
	 * Enable Hot-Join, and, when a Hot-Join request happens, disable all
	 * events coming from this device.
	 *
	 * We will issue ENTDAA afterwards from the thपढ़ोed IRQ handler.
	 */
	ctrl |= CTRL_HJ_ACK | CTRL_HJ_DISEC | CTRL_HALT_EN | CTRL_MCS_EN;

	/*
	 * Configure data hold delay based on device-specअगरic data.
	 *
	 * MIPI I3C Specअगरication 1.0 defines non-zero minimal tHD_PP timing on
	 * master output. This setting allows to meet this timing on master's
	 * SoC outमाला_दो, regardless of PCB balancing.
	 */
	ctrl |= CTRL_THD_DELAY(cdns_i3c_master_calculate_thd_delay(master));
	ग_लिखोl(ctrl, master->regs + CTRL);

	cdns_i3c_master_enable(master);

	वापस 0;
पूर्ण

अटल व्योम cdns_i3c_master_handle_ibi(काष्ठा cdns_i3c_master *master,
				       u32 ibir)
अणु
	काष्ठा cdns_i3c_i2c_dev_data *data;
	bool data_consumed = false;
	काष्ठा i3c_ibi_slot *slot;
	u32 id = IBIR_SLVID(ibir);
	काष्ठा i3c_dev_desc *dev;
	माप_प्रकार nbytes;
	u8 *buf;

	/*
	 * FIXME: maybe we should report the FIFO OVF errors to the upper
	 * layer.
	 */
	अगर (id >= master->ibi.num_slots || (ibir & IBIR_ERROR))
		जाओ out;

	dev = master->ibi.slots[id];
	spin_lock(&master->ibi.lock);

	data = i3c_dev_get_master_data(dev);
	slot = i3c_generic_ibi_get_मुक्त_slot(data->ibi_pool);
	अगर (!slot)
		जाओ out_unlock;

	buf = slot->data;

	nbytes = IBIR_XFER_BYTES(ibir);
	पढ़ोsl(master->regs + IBI_DATA_FIFO, buf, nbytes / 4);
	अगर (nbytes % 3) अणु
		u32 पंचांगp = __raw_पढ़ोl(master->regs + IBI_DATA_FIFO);

		स_नकल(buf + (nbytes & ~3), &पंचांगp, nbytes & 3);
	पूर्ण

	slot->len = min_t(अचिन्हित पूर्णांक, IBIR_XFER_BYTES(ibir),
			  dev->ibi->max_payload_len);
	i3c_master_queue_ibi(dev, slot);
	data_consumed = true;

out_unlock:
	spin_unlock(&master->ibi.lock);

out:
	/* Consume data from the FIFO अगर it's not been करोne alपढ़ोy. */
	अगर (!data_consumed) अणु
		पूर्णांक i;

		क्रम (i = 0; i < IBIR_XFER_BYTES(ibir); i += 4)
			पढ़ोl(master->regs + IBI_DATA_FIFO);
	पूर्ण
पूर्ण

अटल व्योम cnds_i3c_master_demux_ibis(काष्ठा cdns_i3c_master *master)
अणु
	u32 status0;

	ग_लिखोl(MST_INT_IBIR_THR, master->regs + MST_ICR);

	क्रम (status0 = पढ़ोl(master->regs + MST_STATUS0);
	     !(status0 & MST_STATUS0_IBIR_EMP);
	     status0 = पढ़ोl(master->regs + MST_STATUS0)) अणु
		u32 ibir = पढ़ोl(master->regs + IBIR);

		चयन (IBIR_TYPE(ibir)) अणु
		हाल IBIR_TYPE_IBI:
			cdns_i3c_master_handle_ibi(master, ibir);
			अवरोध;

		हाल IBIR_TYPE_HJ:
			WARN_ON(IBIR_XFER_BYTES(ibir) || (ibir & IBIR_ERROR));
			queue_work(master->base.wq, &master->hj_work);
			अवरोध;

		हाल IBIR_TYPE_MR:
			WARN_ON(IBIR_XFER_BYTES(ibir) || (ibir & IBIR_ERROR));
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t cdns_i3c_master_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cdns_i3c_master *master = data;
	u32 status;

	status = पढ़ोl(master->regs + MST_ISR);
	अगर (!(status & पढ़ोl(master->regs + MST_IMR)))
		वापस IRQ_NONE;

	spin_lock(&master->xferqueue.lock);
	cdns_i3c_master_end_xfer_locked(master, status);
	spin_unlock(&master->xferqueue.lock);

	अगर (status & MST_INT_IBIR_THR)
		cnds_i3c_master_demux_ibis(master);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cdns_i3c_master_disable_ibi(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);
	काष्ठा cdns_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	अचिन्हित दीर्घ flags;
	u32 sirmap;
	पूर्णांक ret;

	ret = i3c_master_disec_locked(m, dev->info.dyn_addr,
				      I3C_CCC_EVENT_SIR);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&master->ibi.lock, flags);
	sirmap = पढ़ोl(master->regs + SIR_MAP_DEV_REG(data->ibi));
	sirmap &= ~SIR_MAP_DEV_CONF_MASK(data->ibi);
	sirmap |= SIR_MAP_DEV_CONF(data->ibi,
				   SIR_MAP_DEV_DA(I3C_BROADCAST_ADDR));
	ग_लिखोl(sirmap, master->regs + SIR_MAP_DEV_REG(data->ibi));
	spin_unlock_irqrestore(&master->ibi.lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_i3c_master_enable_ibi(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);
	काष्ठा cdns_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	अचिन्हित दीर्घ flags;
	u32 sircfg, sirmap;
	पूर्णांक ret;

	spin_lock_irqsave(&master->ibi.lock, flags);
	sirmap = पढ़ोl(master->regs + SIR_MAP_DEV_REG(data->ibi));
	sirmap &= ~SIR_MAP_DEV_CONF_MASK(data->ibi);
	sircfg = SIR_MAP_DEV_ROLE(dev->info.bcr >> 6) |
		 SIR_MAP_DEV_DA(dev->info.dyn_addr) |
		 SIR_MAP_DEV_PL(dev->info.max_ibi_len) |
		 SIR_MAP_DEV_ACK;

	अगर (dev->info.bcr & I3C_BCR_MAX_DATA_SPEED_LIM)
		sircfg |= SIR_MAP_DEV_SLOW;

	sirmap |= SIR_MAP_DEV_CONF(data->ibi, sircfg);
	ग_लिखोl(sirmap, master->regs + SIR_MAP_DEV_REG(data->ibi));
	spin_unlock_irqrestore(&master->ibi.lock, flags);

	ret = i3c_master_enec_locked(m, dev->info.dyn_addr,
				     I3C_CCC_EVENT_SIR);
	अगर (ret) अणु
		spin_lock_irqsave(&master->ibi.lock, flags);
		sirmap = पढ़ोl(master->regs + SIR_MAP_DEV_REG(data->ibi));
		sirmap &= ~SIR_MAP_DEV_CONF_MASK(data->ibi);
		sirmap |= SIR_MAP_DEV_CONF(data->ibi,
					   SIR_MAP_DEV_DA(I3C_BROADCAST_ADDR));
		ग_लिखोl(sirmap, master->regs + SIR_MAP_DEV_REG(data->ibi));
		spin_unlock_irqrestore(&master->ibi.lock, flags);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_i3c_master_request_ibi(काष्ठा i3c_dev_desc *dev,
				       स्थिर काष्ठा i3c_ibi_setup *req)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);
	काष्ठा cdns_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	data->ibi_pool = i3c_generic_ibi_alloc_pool(dev, req);
	अगर (IS_ERR(data->ibi_pool))
		वापस PTR_ERR(data->ibi_pool);

	spin_lock_irqsave(&master->ibi.lock, flags);
	क्रम (i = 0; i < master->ibi.num_slots; i++) अणु
		अगर (!master->ibi.slots[i]) अणु
			data->ibi = i;
			master->ibi.slots[i] = dev;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&master->ibi.lock, flags);

	अगर (i < master->ibi.num_slots)
		वापस 0;

	i3c_generic_ibi_मुक्त_pool(data->ibi_pool);
	data->ibi_pool = शून्य;

	वापस -ENOSPC;
पूर्ण

अटल व्योम cdns_i3c_master_मुक्त_ibi(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *m = i3c_dev_get_master(dev);
	काष्ठा cdns_i3c_master *master = to_cdns_i3c_master(m);
	काष्ठा cdns_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&master->ibi.lock, flags);
	master->ibi.slots[data->ibi] = शून्य;
	data->ibi = -1;
	spin_unlock_irqrestore(&master->ibi.lock, flags);

	i3c_generic_ibi_मुक्त_pool(data->ibi_pool);
पूर्ण

अटल व्योम cdns_i3c_master_recycle_ibi_slot(काष्ठा i3c_dev_desc *dev,
					     काष्ठा i3c_ibi_slot *slot)
अणु
	काष्ठा cdns_i3c_i2c_dev_data *data = i3c_dev_get_master_data(dev);

	i3c_generic_ibi_recycle_slot(data->ibi_pool, slot);
पूर्ण

अटल स्थिर काष्ठा i3c_master_controller_ops cdns_i3c_master_ops = अणु
	.bus_init = cdns_i3c_master_bus_init,
	.bus_cleanup = cdns_i3c_master_bus_cleanup,
	.करो_daa = cdns_i3c_master_करो_daa,
	.attach_i3c_dev = cdns_i3c_master_attach_i3c_dev,
	.reattach_i3c_dev = cdns_i3c_master_reattach_i3c_dev,
	.detach_i3c_dev = cdns_i3c_master_detach_i3c_dev,
	.attach_i2c_dev = cdns_i3c_master_attach_i2c_dev,
	.detach_i2c_dev = cdns_i3c_master_detach_i2c_dev,
	.supports_ccc_cmd = cdns_i3c_master_supports_ccc_cmd,
	.send_ccc_cmd = cdns_i3c_master_send_ccc_cmd,
	.priv_xfers = cdns_i3c_master_priv_xfers,
	.i2c_xfers = cdns_i3c_master_i2c_xfers,
	.enable_ibi = cdns_i3c_master_enable_ibi,
	.disable_ibi = cdns_i3c_master_disable_ibi,
	.request_ibi = cdns_i3c_master_request_ibi,
	.मुक्त_ibi = cdns_i3c_master_मुक्त_ibi,
	.recycle_ibi_slot = cdns_i3c_master_recycle_ibi_slot,
पूर्ण;

अटल व्योम cdns_i3c_master_hj(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cdns_i3c_master *master = container_of(work,
						      काष्ठा cdns_i3c_master,
						      hj_work);

	i3c_master_करो_daa(&master->base);
पूर्ण

अटल काष्ठा cdns_i3c_data cdns_i3c_devdata = अणु
	.thd_delay_ns = 10,
पूर्ण;

अटल स्थिर काष्ठा of_device_id cdns_i3c_master_of_ids[] = अणु
	अणु .compatible = "cdns,i3c-master", .data = &cdns_i3c_devdata पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक cdns_i3c_master_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_i3c_master *master;
	पूर्णांक ret, irq;
	u32 val;

	master = devm_kzalloc(&pdev->dev, माप(*master), GFP_KERNEL);
	अगर (!master)
		वापस -ENOMEM;

	master->devdata = of_device_get_match_data(&pdev->dev);
	अगर (!master->devdata)
		वापस -EINVAL;

	master->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(master->regs))
		वापस PTR_ERR(master->regs);

	master->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(master->pclk))
		वापस PTR_ERR(master->pclk);

	master->sysclk = devm_clk_get(&pdev->dev, "sysclk");
	अगर (IS_ERR(master->sysclk))
		वापस PTR_ERR(master->sysclk);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = clk_prepare_enable(master->pclk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(master->sysclk);
	अगर (ret)
		जाओ err_disable_pclk;

	अगर (पढ़ोl(master->regs + DEV_ID) != DEV_ID_I3C_MASTER) अणु
		ret = -EINVAL;
		जाओ err_disable_sysclk;
	पूर्ण

	spin_lock_init(&master->xferqueue.lock);
	INIT_LIST_HEAD(&master->xferqueue.list);

	INIT_WORK(&master->hj_work, cdns_i3c_master_hj);
	ग_लिखोl(0xffffffff, master->regs + MST_IDR);
	ग_लिखोl(0xffffffff, master->regs + SLV_IDR);
	ret = devm_request_irq(&pdev->dev, irq, cdns_i3c_master_पूर्णांकerrupt, 0,
			       dev_name(&pdev->dev), master);
	अगर (ret)
		जाओ err_disable_sysclk;

	platक्रमm_set_drvdata(pdev, master);

	val = पढ़ोl(master->regs + CONF_STATUS0);

	/* Device ID0 is reserved to describe this master. */
	master->maxdevs = CONF_STATUS0_DEVS_NUM(val);
	master->मुक्त_rr_slots = GENMASK(master->maxdevs, 1);

	val = पढ़ोl(master->regs + CONF_STATUS1);
	master->caps.cmdfअगरodepth = CONF_STATUS1_CMD_DEPTH(val);
	master->caps.rxfअगरodepth = CONF_STATUS1_RX_DEPTH(val);
	master->caps.txfअगरodepth = CONF_STATUS1_TX_DEPTH(val);
	master->caps.ibirfअगरodepth = CONF_STATUS0_IBIR_DEPTH(val);
	master->caps.cmdrfअगरodepth = CONF_STATUS0_CMDR_DEPTH(val);

	spin_lock_init(&master->ibi.lock);
	master->ibi.num_slots = CONF_STATUS1_IBI_HW_RES(val);
	master->ibi.slots = devm_kसुस्मृति(&pdev->dev, master->ibi.num_slots,
					 माप(*master->ibi.slots),
					 GFP_KERNEL);
	अगर (!master->ibi.slots) अणु
		ret = -ENOMEM;
		जाओ err_disable_sysclk;
	पूर्ण

	ग_लिखोl(IBIR_THR(1), master->regs + CMD_IBI_THR_CTRL);
	ग_लिखोl(MST_INT_IBIR_THR, master->regs + MST_IER);
	ग_लिखोl(DEVS_CTRL_DEV_CLR_ALL, master->regs + DEVS_CTRL);

	ret = i3c_master_रेजिस्टर(&master->base, &pdev->dev,
				  &cdns_i3c_master_ops, false);
	अगर (ret)
		जाओ err_disable_sysclk;

	वापस 0;

err_disable_sysclk:
	clk_disable_unprepare(master->sysclk);

err_disable_pclk:
	clk_disable_unprepare(master->pclk);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_i3c_master_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_i3c_master *master = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = i3c_master_unरेजिस्टर(&master->base);
	अगर (ret)
		वापस ret;

	clk_disable_unprepare(master->sysclk);
	clk_disable_unprepare(master->pclk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cdns_i3c_master = अणु
	.probe = cdns_i3c_master_probe,
	.हटाओ = cdns_i3c_master_हटाओ,
	.driver = अणु
		.name = "cdns-i3c-master",
		.of_match_table = cdns_i3c_master_of_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cdns_i3c_master);

MODULE_AUTHOR("Boris Brezillon <boris.brezillon@bootlin.com>");
MODULE_DESCRIPTION("Cadence I3C master driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:cdns-i3c-master");
