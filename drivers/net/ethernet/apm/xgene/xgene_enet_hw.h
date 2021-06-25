<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Applied Micro X-Gene SoC Ethernet Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Authors: Iyappan Subramanian <isubramanian@apm.com>
 *	    Ravi Patel <rapatel@apm.com>
 *	    Keyur Chudgar <kchudgar@apm.com>
 */

#अगर_अघोषित __XGENE_ENET_HW_H__
#घोषणा __XGENE_ENET_HW_H__

#समावेश "xgene_enet_main.h"

काष्ठा xgene_enet_pdata;
काष्ठा xgene_enet_stats;
काष्ठा xgene_enet_desc_ring;

/* clears and then set bits */
अटल अंतरभूत व्योम xgene_set_bits(u32 *dst, u32 val, u32 start, u32 len)
अणु
	u32 end = start + len - 1;
	u32 mask = GENMASK(end, start);

	*dst &= ~mask;
	*dst |= (val << start) & mask;
पूर्ण

अटल अंतरभूत u32 xgene_get_bits(u32 val, u32 start, u32 end)
अणु
	वापस (val & GENMASK(end, start)) >> start;
पूर्ण

क्रमागत xgene_enet_rm अणु
	RM0,
	RM1,
	RM3 = 3
पूर्ण;

#घोषणा CSR_RING_ID		0x0008
#घोषणा OVERWRITE		BIT(31)
#घोषणा IS_BUFFER_POOL		BIT(20)
#घोषणा PREFETCH_BUF_EN		BIT(21)
#घोषणा CSR_RING_ID_BUF		0x000c
#घोषणा CSR_PBM_COAL		0x0014
#घोषणा CSR_PBM_CTICK0		0x0018
#घोषणा CSR_PBM_CTICK1		0x001c
#घोषणा CSR_PBM_CTICK2		0x0020
#घोषणा CSR_PBM_CTICK3		0x0024
#घोषणा CSR_THRESHOLD0_SET1	0x0030
#घोषणा CSR_THRESHOLD1_SET1	0x0034
#घोषणा CSR_RING_NE_INT_MODE	0x017c
#घोषणा CSR_RING_CONFIG		0x006c
#घोषणा CSR_RING_WR_BASE	0x0070
#घोषणा NUM_RING_CONFIG		5
#घोषणा BUFPOOL_MODE		3
#घोषणा INC_DEC_CMD_ADDR	0x002c
#घोषणा UDP_HDR_SIZE		2
#घोषणा BUF_LEN_CODE_2K		0x5000

#घोषणा CREATE_MASK(pos, len)		GENMASK((pos)+(len)-1, (pos))
#घोषणा CREATE_MASK_ULL(pos, len)	GENMASK_ULL((pos)+(len)-1, (pos))

/* Empty slot soft signature */
#घोषणा EMPTY_SLOT_INDEX	1
#घोषणा EMPTY_SLOT		~0ULL

#घोषणा WORK_DESC_SIZE		32
#घोषणा BUFPOOL_DESC_SIZE	16

#घोषणा RING_OWNER_MASK		GENMASK(9, 6)
#घोषणा RING_BUFNUM_MASK	GENMASK(5, 0)

#घोषणा SELTHRSH_POS		3
#घोषणा SELTHRSH_LEN		3
#घोषणा RINGADDRL_POS		5
#घोषणा RINGADDRL_LEN		27
#घोषणा RINGADDRH_POS		0
#घोषणा RINGADDRH_LEN		7
#घोषणा RINGSIZE_POS		23
#घोषणा RINGSIZE_LEN		3
#घोषणा RINGTYPE_POS		19
#घोषणा RINGTYPE_LEN		2
#घोषणा RINGMODE_POS		20
#घोषणा RINGMODE_LEN		3
#घोषणा RECOMTIMEOUTL_POS	28
#घोषणा RECOMTIMEOUTL_LEN	4
#घोषणा RECOMTIMEOUTH_POS	0
#घोषणा RECOMTIMEOUTH_LEN	3
#घोषणा NUMMSGSINQ_POS		1
#घोषणा NUMMSGSINQ_LEN		16
#घोषणा ACCEPTLERR		BIT(19)
#घोषणा QCOHERENT		BIT(4)
#घोषणा RECOMBBUF		BIT(27)

#घोषणा MAC_OFFSET			0x30
#घोषणा OFFSET_4			0x04
#घोषणा OFFSET_8			0x08

#घोषणा BLOCK_ETH_CSR_OFFSET		0x2000
#घोषणा BLOCK_ETH_CLE_CSR_OFFSET	0x6000
#घोषणा BLOCK_ETH_RING_IF_OFFSET	0x9000
#घोषणा BLOCK_ETH_CLKRST_CSR_OFFSET	0xc000
#घोषणा BLOCK_ETH_DIAG_CSR_OFFSET	0xD000
#घोषणा BLOCK_ETH_MAC_OFFSET		0x0000
#घोषणा BLOCK_ETH_STATS_OFFSET		0x0000
#घोषणा BLOCK_ETH_MAC_CSR_OFFSET	0x2800

#घोषणा CLKEN_ADDR			0xc208
#घोषणा SRST_ADDR			0xc200

#घोषणा MAC_ADDR_REG_OFFSET		0x00
#घोषणा MAC_COMMAND_REG_OFFSET		0x04
#घोषणा MAC_WRITE_REG_OFFSET		0x08
#घोषणा MAC_READ_REG_OFFSET		0x0c
#घोषणा MAC_COMMAND_DONE_REG_OFFSET	0x10

#घोषणा STAT_ADDR_REG_OFFSET            0x14
#घोषणा STAT_COMMAND_REG_OFFSET         0x18
#घोषणा STAT_WRITE_REG_OFFSET           0x1c
#घोषणा STAT_READ_REG_OFFSET            0x20
#घोषणा STAT_COMMAND_DONE_REG_OFFSET    0x24

#घोषणा PCS_ADDR_REG_OFFSET		0x00
#घोषणा PCS_COMMAND_REG_OFFSET		0x04
#घोषणा PCS_WRITE_REG_OFFSET		0x08
#घोषणा PCS_READ_REG_OFFSET		0x0c
#घोषणा PCS_COMMAND_DONE_REG_OFFSET	0x10

#घोषणा MII_MGMT_CONFIG_ADDR		0x20
#घोषणा MII_MGMT_COMMAND_ADDR		0x24
#घोषणा MII_MGMT_ADDRESS_ADDR		0x28
#घोषणा MII_MGMT_CONTROL_ADDR		0x2c
#घोषणा MII_MGMT_STATUS_ADDR		0x30
#घोषणा MII_MGMT_INDICATORS_ADDR	0x34

#घोषणा BUSY_MASK			BIT(0)
#घोषणा READ_CYCLE_MASK			BIT(0)
#घोषणा PHY_CONTROL_SET(dst, val)	xgene_set_bits(dst, val, 0, 16)

#घोषणा ENET_SPARE_CFG_REG_ADDR		0x0750
#घोषणा RSIF_CONFIG_REG_ADDR		0x0010
#घोषणा RSIF_RAM_DBG_REG0_ADDR		0x0048
#घोषणा RGMII_REG_0_ADDR		0x07e0
#घोषणा CFG_LINK_AGGR_RESUME_0_ADDR	0x07c8
#घोषणा DEBUG_REG_ADDR			0x0700
#घोषणा CFG_BYPASS_ADDR			0x0294
#घोषणा CLE_BYPASS_REG0_0_ADDR		0x0490
#घोषणा CLE_BYPASS_REG1_0_ADDR		0x0494
#घोषणा CFG_RSIF_FPBUFF_TIMEOUT_EN	BIT(31)
#घोषणा RESUME_TX			BIT(0)
#घोषणा CFG_SPEED_1250			BIT(24)
#घोषणा TX_PORT0			BIT(0)
#घोषणा CFG_BYPASS_UNISEC_TX		BIT(2)
#घोषणा CFG_BYPASS_UNISEC_RX		BIT(1)
#घोषणा CFG_CLE_BYPASS_EN0		BIT(31)
#घोषणा CFG_TXCLK_MUXSEL0_SET(dst, val)	xgene_set_bits(dst, val, 29, 3)
#घोषणा CFG_RXCLK_MUXSEL0_SET(dst, val)	xgene_set_bits(dst, val, 26, 3)

#घोषणा CFG_CLE_IP_PROTOCOL0_SET(dst, val)	xgene_set_bits(dst, val, 16, 2)
#घोषणा CFG_CLE_IP_HDR_LEN_SET(dst, val)	xgene_set_bits(dst, val, 8, 5)
#घोषणा CFG_CLE_DSTQID0_SET(dst, val)		xgene_set_bits(dst, val, 0, 12)
#घोषणा CFG_CLE_FPSEL0_SET(dst, val)		xgene_set_bits(dst, val, 16, 4)
#घोषणा CFG_CLE_NXTFPSEL0_SET(dst, val)		xgene_set_bits(dst, val, 20, 4)
#घोषणा CFG_MACMODE_SET(dst, val)		xgene_set_bits(dst, val, 18, 2)
#घोषणा CFG_WAITASYNCRD_SET(dst, val)		xgene_set_bits(dst, val, 0, 16)
#घोषणा CFG_CLE_DSTQID0(val)		((val) & GENMASK(11, 0))
#घोषणा CFG_CLE_FPSEL0(val)		(((val) << 16) & GENMASK(19, 16))
#घोषणा CSR_ECM_CFG_0_ADDR		0x0220
#घोषणा CSR_ECM_CFG_1_ADDR		0x0224
#घोषणा CSR_MULTI_DPF0_ADDR		0x0230
#घोषणा RXBUF_PAUSE_THRESH		0x0534
#घोषणा RXBUF_PAUSE_OFF_THRESH		0x0540
#घोषणा DEF_PAUSE_THRES			0x7d
#घोषणा DEF_PAUSE_OFF_THRES		0x6d
#घोषणा DEF_QUANTA			0x8000
#घोषणा NORM_PAUSE_OPCODE		0x0001
#घोषणा PAUSE_XON_EN			BIT(30)
#घोषणा MULTI_DPF_AUTOCTRL		BIT(28)
#घोषणा CFG_CLE_NXTFPSEL0(val)		(((val) << 20) & GENMASK(23, 20))
#घोषणा ICM_CONFIG0_REG_0_ADDR		0x0400
#घोषणा ICM_CONFIG2_REG_0_ADDR		0x0410
#घोषणा ECM_CONFIG0_REG_0_ADDR		0x0500
#घोषणा ECM_CONFIG0_REG_1_ADDR		0x0504
#घोषणा ICM_ECM_DROP_COUNT_REG0_ADDR	0x0508
#घोषणा ICM_ECM_DROP_COUNT_REG1_ADDR	0x050c
#घोषणा RX_DV_GATE_REG_0_ADDR		0x05fc
#घोषणा TX_DV_GATE_EN0			BIT(2)
#घोषणा RX_DV_GATE_EN0			BIT(1)
#घोषणा RESUME_RX0			BIT(0)
#घोषणा ENET_CFGSSQMIFPRESET_ADDR		0x14
#घोषणा ENET_CFGSSQMIWQRESET_ADDR		0x1c
#घोषणा ENET_CFGSSQMIWQASSOC_ADDR		0xe0
#घोषणा ENET_CFGSSQMIFPQASSOC_ADDR		0xdc
#घोषणा ENET_CFGSSQMIQMLITEFPQASSOC_ADDR	0xf0
#घोषणा ENET_CFGSSQMIQMLITEWQASSOC_ADDR		0xf4
#घोषणा ENET_CFG_MEM_RAM_SHUTDOWN_ADDR		0x70
#घोषणा ENET_BLOCK_MEM_RDY_ADDR			0x74
#घोषणा MAC_CONFIG_1_ADDR			0x00
#घोषणा MAC_CONFIG_2_ADDR			0x04
#घोषणा MAX_FRAME_LEN_ADDR			0x10
#घोषणा INTERFACE_CONTROL_ADDR			0x38
#घोषणा STATION_ADDR0_ADDR			0x40
#घोषणा STATION_ADDR1_ADDR			0x44
#घोषणा PHY_ADDR_SET(dst, val)			xgene_set_bits(dst, val, 8, 5)
#घोषणा REG_ADDR_SET(dst, val)			xgene_set_bits(dst, val, 0, 5)
#घोषणा ENET_INTERFACE_MODE2_SET(dst, val)	xgene_set_bits(dst, val, 8, 2)
#घोषणा MGMT_CLOCK_SEL_SET(dst, val)		xgene_set_bits(dst, val, 0, 3)
#घोषणा SOFT_RESET1			BIT(31)
#घोषणा TX_EN				BIT(0)
#घोषणा RX_EN				BIT(2)
#घोषणा TX_FLOW_EN			BIT(4)
#घोषणा RX_FLOW_EN			BIT(5)
#घोषणा ENET_LHD_MODE			BIT(25)
#घोषणा ENET_GHD_MODE			BIT(26)
#घोषणा FULL_DUPLEX2			BIT(0)
#घोषणा PAD_CRC				BIT(2)
#घोषणा LENGTH_CHK			BIT(4)

#घोषणा TR64_ADDR	0x20
#घोषणा TR127_ADDR	0x21
#घोषणा TR255_ADDR	0x22
#घोषणा TR511_ADDR	0x23
#घोषणा TR1K_ADDR	0x24
#घोषणा TRMAX_ADDR	0x25
#घोषणा TRMGV_ADDR	0x26

#घोषणा RFCS_ADDR	0x29
#घोषणा RMCA_ADDR	0x2a
#घोषणा RBCA_ADDR	0x2b
#घोषणा RXCF_ADDR	0x2c
#घोषणा RXPF_ADDR	0x2d
#घोषणा RXUO_ADDR	0x2e
#घोषणा RALN_ADDR	0x2f
#घोषणा RFLR_ADDR	0x30
#घोषणा RCDE_ADDR	0x31
#घोषणा RCSE_ADDR	0x32
#घोषणा RUND_ADDR	0x33
#घोषणा ROVR_ADDR	0x34
#घोषणा RFRG_ADDR	0x35
#घोषणा RJBR_ADDR	0x36
#घोषणा RDRP_ADDR	0x37

#घोषणा TMCA_ADDR	0x3a
#घोषणा TBCA_ADDR	0x3b
#घोषणा TXPF_ADDR	0x3c
#घोषणा TDFR_ADDR	0x3d
#घोषणा TEDF_ADDR	0x3e
#घोषणा TSCL_ADDR	0x3f
#घोषणा TMCL_ADDR	0x40
#घोषणा TLCL_ADDR	0x41
#घोषणा TXCL_ADDR	0x42
#घोषणा TNCL_ADDR	0x43
#घोषणा TPFH_ADDR	0x44
#घोषणा TDRP_ADDR	0x45
#घोषणा TJBR_ADDR	0x46
#घोषणा TFCS_ADDR	0x47
#घोषणा TXCF_ADDR	0x48
#घोषणा TOVR_ADDR	0x49
#घोषणा TUND_ADDR	0x4a
#घोषणा TFRG_ADDR	0x4b
#घोषणा DUMP_ADDR	0x27

#घोषणा ECM_DROP_COUNT(src)	xgene_get_bits(src, 0, 15)
#घोषणा ICM_DROP_COUNT(src)	xgene_get_bits(src, 16, 31)

#घोषणा TSO_IPPROTO_TCP			1

#घोषणा USERINFO_POS			0
#घोषणा USERINFO_LEN			32
#घोषणा FPQNUM_POS			32
#घोषणा FPQNUM_LEN			12
#घोषणा ELERR_POS                       46
#घोषणा ELERR_LEN                       2
#घोषणा NV_POS				50
#घोषणा NV_LEN				1
#घोषणा LL_POS				51
#घोषणा LL_LEN				1
#घोषणा LERR_POS			60
#घोषणा LERR_LEN			3
#घोषणा STASH_POS			52
#घोषणा STASH_LEN			2
#घोषणा BUFDATALEN_POS			48
#घोषणा BUFDATALEN_LEN			15
#घोषणा DATAADDR_POS			0
#घोषणा DATAADDR_LEN			42
#घोषणा COHERENT_POS			63
#घोषणा HENQNUM_POS			48
#घोषणा HENQNUM_LEN			12
#घोषणा TYPESEL_POS			44
#घोषणा TYPESEL_LEN			4
#घोषणा ETHHDR_POS			12
#घोषणा ETHHDR_LEN			8
#घोषणा IC_POS				35	/* Insert CRC */
#घोषणा TCPHDR_POS			0
#घोषणा TCPHDR_LEN			6
#घोषणा IPHDR_POS			6
#घोषणा IPHDR_LEN			6
#घोषणा MSS_POS				20
#घोषणा MSS_LEN				2
#घोषणा EC_POS				22	/* Enable checksum */
#घोषणा EC_LEN				1
#घोषणा ET_POS				23	/* Enable TSO */
#घोषणा IS_POS				24	/* IP protocol select */
#घोषणा IS_LEN				1
#घोषणा TYPE_ETH_WORK_MESSAGE_POS	44
#घोषणा LL_BYTES_MSB_POS		56
#घोषणा LL_BYTES_MSB_LEN		8
#घोषणा LL_BYTES_LSB_POS		48
#घोषणा LL_BYTES_LSB_LEN		12
#घोषणा LL_LEN_POS			48
#घोषणा LL_LEN_LEN			8
#घोषणा DATALEN_MASK			GENMASK(11, 0)

#घोषणा LAST_BUFFER			(0x7800ULL << BUFDATALEN_POS)

#घोषणा TSO_MSS0_POS			0
#घोषणा TSO_MSS0_LEN			14
#घोषणा TSO_MSS1_POS			16
#घोषणा TSO_MSS1_LEN			14

काष्ठा xgene_enet_raw_desc अणु
	__le64 m0;
	__le64 m1;
	__le64 m2;
	__le64 m3;
पूर्ण;

काष्ठा xgene_enet_raw_desc16 अणु
	__le64 m0;
	__le64 m1;
पूर्ण;

अटल अंतरभूत व्योम xgene_enet_mark_desc_slot_empty(व्योम *desc_slot_ptr)
अणु
	__le64 *desc_slot = desc_slot_ptr;

	desc_slot[EMPTY_SLOT_INDEX] = cpu_to_le64(EMPTY_SLOT);
पूर्ण

अटल अंतरभूत bool xgene_enet_is_desc_slot_empty(व्योम *desc_slot_ptr)
अणु
	__le64 *desc_slot = desc_slot_ptr;

	वापस (desc_slot[EMPTY_SLOT_INDEX] == cpu_to_le64(EMPTY_SLOT));
पूर्ण

क्रमागत xgene_enet_ring_cfgsize अणु
	RING_CFGSIZE_512B,
	RING_CFGSIZE_2KB,
	RING_CFGSIZE_16KB,
	RING_CFGSIZE_64KB,
	RING_CFGSIZE_512KB,
	RING_CFGSIZE_INVALID
पूर्ण;

क्रमागत xgene_enet_ring_type अणु
	RING_DISABLED,
	RING_REGULAR,
	RING_BUFPOOL
पूर्ण;

क्रमागत xgene_ring_owner अणु
	RING_OWNER_ETH0,
	RING_OWNER_ETH1,
	RING_OWNER_CPU = 15,
	RING_OWNER_INVALID
पूर्ण;

क्रमागत xgene_enet_ring_bufnum अणु
	RING_BUFNUM_REGULAR = 0x0,
	RING_BUFNUM_BUFPOOL = 0x20,
	RING_BUFNUM_INVALID
पूर्ण;

क्रमागत xgene_enet_err_code अणु
	HBF_READ_DATA = 3,
	HBF_LL_READ = 4,
	BAD_WORK_MSG = 6,
	BUFPOOL_TIMEOUT = 15,
	INGRESS_CRC = 16,
	INGRESS_CHECKSUM = 17,
	INGRESS_TRUNC_FRAME = 18,
	INGRESS_PKT_LEN = 19,
	INGRESS_PKT_UNDER = 20,
	INGRESS_FIFO_OVERRUN = 21,
	INGRESS_CHECKSUM_COMPUTE = 26,
	ERR_CODE_INVALID
पूर्ण;

अटल अंतरभूत क्रमागत xgene_ring_owner xgene_enet_ring_owner(u16 id)
अणु
	वापस (id & RING_OWNER_MASK) >> 6;
पूर्ण

अटल अंतरभूत u8 xgene_enet_ring_bufnum(u16 id)
अणु
	वापस id & RING_BUFNUM_MASK;
पूर्ण

अटल अंतरभूत bool xgene_enet_is_bufpool(u16 id)
अणु
	वापस ((id & RING_BUFNUM_MASK) >= 0x20) ? true : false;
पूर्ण

अटल अंतरभूत u8 xgene_enet_get_fpsel(u16 id)
अणु
	अगर (xgene_enet_is_bufpool(id))
		वापस xgene_enet_ring_bufnum(id) - RING_BUFNUM_BUFPOOL;

	वापस 0;
पूर्ण

अटल अंतरभूत u16 xgene_enet_get_numslots(u16 id, u32 size)
अणु
	bool is_bufpool = xgene_enet_is_bufpool(id);

	वापस (is_bufpool) ? size / BUFPOOL_DESC_SIZE :
		      size / WORK_DESC_SIZE;
पूर्ण

व्योम xgene_enet_parse_error(काष्ठा xgene_enet_desc_ring *ring,
			    क्रमागत xgene_enet_err_code status);
पूर्णांक xgene_enet_mdio_config(काष्ठा xgene_enet_pdata *pdata);
व्योम xgene_enet_mdio_हटाओ(काष्ठा xgene_enet_pdata *pdata);
bool xgene_ring_mgr_init(काष्ठा xgene_enet_pdata *p);
पूर्णांक xgene_enet_phy_connect(काष्ठा net_device *ndev);
व्योम xgene_enet_phy_disconnect(काष्ठा xgene_enet_pdata *pdata);
u32 xgene_enet_rd_mac(काष्ठा xgene_enet_pdata *pdata, u32 rd_addr);
व्योम xgene_enet_wr_mac(काष्ठा xgene_enet_pdata *pdata, u32 wr_addr,
		       u32 wr_data);
u32 xgene_enet_rd_stat(काष्ठा xgene_enet_pdata *pdata, u32 rd_addr);

बाह्य स्थिर काष्ठा xgene_mac_ops xgene_gmac_ops;
बाह्य स्थिर काष्ठा xgene_port_ops xgene_gport_ops;
बाह्य काष्ठा xgene_ring_ops xgene_ring1_ops;

#पूर्ण_अगर /* __XGENE_ENET_HW_H__ */
