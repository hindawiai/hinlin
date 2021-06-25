<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#अगर_अघोषित __QLCNIC_83XX_HW_H
#घोषणा __QLCNIC_83XX_HW_H

#समावेश <linux/types.h>
#समावेश <linux/etherdevice.h>

#समावेश "qlcnic_hw.h"

#घोषणा QLCNIC_83XX_BAR0_LENGTH 0x4000

/* Directly mapped रेजिस्टरs */
#घोषणा QLC_83XX_CRB_WIN_BASE		0x3800
#घोषणा QLC_83XX_CRB_WIN_FUNC(f)	(QLC_83XX_CRB_WIN_BASE+((f)*4))
#घोषणा QLC_83XX_SEM_LOCK_BASE		0x3840
#घोषणा QLC_83XX_SEM_UNLOCK_BASE	0x3844
#घोषणा QLC_83XX_SEM_LOCK_FUNC(f)	(QLC_83XX_SEM_LOCK_BASE+((f)*8))
#घोषणा QLC_83XX_SEM_UNLOCK_FUNC(f)	(QLC_83XX_SEM_UNLOCK_BASE+((f)*8))
#घोषणा QLC_83XX_LINK_STATE(f)		(0x3698+((f) > 7 ? 4 : 0))
#घोषणा QLC_83XX_LINK_SPEED(f)		(0x36E0+(((f) >> 2) * 4))
#घोषणा QLC_83XX_LINK_SPEED_FACTOR	10
#घोषणा QLC_83xx_FUNC_VAL(v, f)	((v) & (1 << (f * 4)))
#घोषणा QLC_83XX_INTX_PTR		0x38C0
#घोषणा QLC_83XX_INTX_TRGR		0x38C4
#घोषणा QLC_83XX_INTX_MASK		0x38C8

#घोषणा QLC_83XX_DRV_LOCK_WAIT_COUNTER			100
#घोषणा QLC_83XX_DRV_LOCK_WAIT_DELAY			20
#घोषणा QLC_83XX_NEED_DRV_LOCK_RECOVERY		1
#घोषणा QLC_83XX_DRV_LOCK_RECOVERY_IN_PROGRESS		2
#घोषणा QLC_83XX_MAX_DRV_LOCK_RECOVERY_ATTEMPT		3
#घोषणा QLC_83XX_DRV_LOCK_RECOVERY_DELAY		200
#घोषणा QLC_83XX_DRV_LOCK_RECOVERY_STATUS_MASK		0x3
#घोषणा QLC_83XX_LB_WAIT_COUNT				250
#घोषणा QLC_83XX_LB_MSLEEP_COUNT			20
#घोषणा QLC_83XX_NO_NIC_RESOURCE	0x5
#घोषणा QLC_83XX_MAC_PRESENT		0xC
#घोषणा QLC_83XX_MAC_ABSENT		0xD


#घोषणा QLC_83XX_FLASH_SECTOR_SIZE		(64 * 1024)

/* PEG status definitions */
#घोषणा QLC_83XX_CMDPEG_COMPLETE		0xff01
#घोषणा QLC_83XX_VALID_INTX_BIT30(val)		((val) & BIT_30)
#घोषणा QLC_83XX_VALID_INTX_BIT31(val)		((val) & BIT_31)
#घोषणा QLC_83XX_INTX_FUNC(val)		((val) & 0xFF)
#घोषणा QLC_83XX_LEGACY_INTX_MAX_RETRY		100
#घोषणा QLC_83XX_LEGACY_INTX_DELAY		4
#घोषणा QLC_83XX_REG_DESC			1
#घोषणा QLC_83XX_LRO_DESC			2
#घोषणा QLC_83XX_CTRL_DESC			3
#घोषणा QLC_83XX_FW_CAPABILITY_TSO		BIT_6
#घोषणा QLC_83XX_FW_CAP_LRO_MSS		BIT_17
#घोषणा QLC_83XX_HOST_RDS_MODE_UNIQUE		0
#घोषणा QLC_83XX_HOST_SDS_MBX_IDX		8

#घोषणा QLCNIC_HOST_RDS_MBX_IDX			88

/* Pause control रेजिस्टरs */
#घोषणा QLC_83XX_SRE_SHIM_REG		0x0D200284
#घोषणा QLC_83XX_PORT0_THRESHOLD	0x0B2003A4
#घोषणा QLC_83XX_PORT1_THRESHOLD	0x0B2013A4
#घोषणा QLC_83XX_PORT0_TC_MC_REG	0x0B200388
#घोषणा QLC_83XX_PORT1_TC_MC_REG	0x0B201388
#घोषणा QLC_83XX_PORT0_TC_STATS		0x0B20039C
#घोषणा QLC_83XX_PORT1_TC_STATS		0x0B20139C
#घोषणा QLC_83XX_PORT2_IFB_THRESHOLD	0x0B200704
#घोषणा QLC_83XX_PORT3_IFB_THRESHOLD	0x0B201704

/* Peg PC status रेजिस्टरs */
#घोषणा QLC_83XX_CRB_PEG_NET_0		0x3400003c
#घोषणा QLC_83XX_CRB_PEG_NET_1		0x3410003c
#घोषणा QLC_83XX_CRB_PEG_NET_2		0x3420003c
#घोषणा QLC_83XX_CRB_PEG_NET_3		0x3430003c
#घोषणा QLC_83XX_CRB_PEG_NET_4		0x34b0003c

/* Firmware image definitions */
#घोषणा QLC_83XX_BOOTLOADER_FLASH_ADDR	0x10000
#घोषणा QLC_83XX_FW_खाता_NAME		"83xx_fw.bin"
#घोषणा QLC_83XX_POST_FW_खाता_NAME	"83xx_post_fw.bin"
#घोषणा QLC_84XX_FW_खाता_NAME		"84xx_fw.bin"
#घोषणा QLC_83XX_BOOT_FROM_FLASH	0
#घोषणा QLC_83XX_BOOT_FROM_खाता		0x12345678

#घोषणा QLC_FW_खाता_NAME_LEN		20
#घोषणा QLC_83XX_MAX_RESET_SEQ_ENTRIES	16

#घोषणा QLC_83XX_MBX_POST_BC_OP		0x1
#घोषणा QLC_83XX_MBX_COMPLETION		0x0
#घोषणा QLC_83XX_MBX_REQUEST		0x1

#घोषणा QLC_83XX_MBX_TIMEOUT		(5 * HZ)
#घोषणा QLC_83XX_MBX_CMD_LOOP		5000000

/* status descriptor mailbox data
 * @phy_addr_अणुlow|highपूर्ण: physical address of buffer
 * @sds_ring_size: buffer size
 * @पूर्णांकrpt_id: पूर्णांकerrupt id
 * @पूर्णांकrpt_val: source of पूर्णांकerrupt
 */
काष्ठा qlcnic_sds_mbx अणु
	u32	phy_addr_low;
	u32	phy_addr_high;
	u32	rsvd1[4];
#अगर defined(__LITTLE_ENDIAN)
	u16	sds_ring_size;
	u16	rsvd2;
	u16	rsvd3[2];
	u16	पूर्णांकrpt_id;
	u8	पूर्णांकrpt_val;
	u8	rsvd4;
#या_अगर defined(__BIG_ENDIAN)
	u16	rsvd2;
	u16	sds_ring_size;
	u16	rsvd3[2];
	u8	rsvd4;
	u8	पूर्णांकrpt_val;
	u16	पूर्णांकrpt_id;
#पूर्ण_अगर
	u32	rsvd5;
पूर्ण __packed;

/* receive descriptor buffer data
 * phy_addr_reg_अणुlow|highपूर्ण: physical address of regular buffer
 * phy_addr_jmb_अणुlow|highपूर्ण: physical address of jumbo buffer
 * reg_ring_sz: size of regular buffer
 * reg_ring_len: no. of entries in regular buffer
 * jmb_ring_len: no. of entries in jumbo buffer
 * jmb_ring_sz: size of jumbo buffer
 */
काष्ठा qlcnic_rds_mbx अणु
	u32	phy_addr_reg_low;
	u32	phy_addr_reg_high;
	u32	phy_addr_jmb_low;
	u32	phy_addr_jmb_high;
#अगर defined(__LITTLE_ENDIAN)
	u16	reg_ring_sz;
	u16	reg_ring_len;
	u16	jmb_ring_sz;
	u16	jmb_ring_len;
#या_अगर defined(__BIG_ENDIAN)
	u16	reg_ring_len;
	u16	reg_ring_sz;
	u16	jmb_ring_len;
	u16	jmb_ring_sz;
#पूर्ण_अगर
पूर्ण __packed;

/* host producers क्रम regular and jumbo rings */
काष्ठा __host_producer_mbx अणु
	u32	reg_buf;
	u32	jmb_buf;
पूर्ण __packed;

/* Receive context mailbox data outbox रेजिस्टरs
 * @state: state of the context
 * @vport_id: भव port id
 * @context_id: receive context id
 * @num_pci_func: number of pci functions of the port
 * @phy_port: physical port id
 */
काष्ठा qlcnic_rcv_mbx_out अणु
#अगर defined(__LITTLE_ENDIAN)
	u8	rcv_num;
	u8	sts_num;
	u16	ctx_id;
	u8	state;
	u8	num_pci_func;
	u8	phy_port;
	u8	vport_id;
#या_अगर defined(__BIG_ENDIAN)
	u16	ctx_id;
	u8	sts_num;
	u8	rcv_num;
	u8	vport_id;
	u8	phy_port;
	u8	num_pci_func;
	u8	state;
#पूर्ण_अगर
	u32	host_csmr[QLCNIC_MAX_SDS_RINGS];
	काष्ठा __host_producer_mbx host_prod[QLCNIC_MAX_SDS_RINGS];
पूर्ण __packed;

काष्ठा qlcnic_add_rings_mbx_out अणु
#अगर defined(__LITTLE_ENDIAN)
	u8      rcv_num;
	u8      sts_num;
	u16	ctx_id;
#या_अगर defined(__BIG_ENDIAN)
	u16	ctx_id;
	u8	sts_num;
	u8	rcv_num;
#पूर्ण_अगर
	u32  host_csmr[QLCNIC_MAX_SDS_RINGS];
	काष्ठा __host_producer_mbx host_prod[QLCNIC_MAX_SDS_RINGS];
पूर्ण __packed;

/* Transmit context mailbox inbox रेजिस्टरs
 * @phys_addr_अणुlow|highपूर्ण: DMA address of the transmit buffer
 * @cnsmr_index_अणुlow|highपूर्ण: host consumer index
 * @size: legth of transmit buffer ring
 * @पूर्णांकr_id: पूर्णांकerrupt id
 * @src: src of पूर्णांकerrupt
 */
काष्ठा qlcnic_tx_mbx अणु
	u32	phys_addr_low;
	u32	phys_addr_high;
	u32	cnsmr_index_low;
	u32	cnsmr_index_high;
#अगर defined(__LITTLE_ENDIAN)
	u16	size;
	u16	पूर्णांकr_id;
	u8	src;
	u8	rsvd[3];
#या_अगर defined(__BIG_ENDIAN)
	u16	पूर्णांकr_id;
	u16	size;
	u8	rsvd[3];
	u8	src;
#पूर्ण_अगर
पूर्ण __packed;

/* Transmit context mailbox outbox रेजिस्टरs
 * @host_prod: host producer index
 * @ctx_id: transmit context id
 * @state: state of the transmit context
 */

काष्ठा qlcnic_tx_mbx_out अणु
	u32	host_prod;
#अगर defined(__LITTLE_ENDIAN)
	u16	ctx_id;
	u8	state;
	u8	rsvd;
#या_अगर defined(__BIG_ENDIAN)
	u8	rsvd;
	u8	state;
	u16	ctx_id;
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा qlcnic_पूर्णांकrpt_config अणु
	u8	type;
	u8	enabled;
	u16	id;
	u32	src;
पूर्ण;

काष्ठा qlcnic_macvlan_mbx अणु
#अगर defined(__LITTLE_ENDIAN)
	u8	mac_addr0;
	u8	mac_addr1;
	u8	mac_addr2;
	u8	mac_addr3;
	u8	mac_addr4;
	u8	mac_addr5;
	u16	vlan;
#या_अगर defined(__BIG_ENDIAN)
	u8	mac_addr3;
	u8	mac_addr2;
	u8	mac_addr1;
	u8	mac_addr0;
	u16	vlan;
	u8	mac_addr5;
	u8	mac_addr4;
#पूर्ण_अगर
पूर्ण;

काष्ठा qlc_83xx_fw_info अणु
	स्थिर काष्ठा firmware	*fw;
	अक्षर	fw_file_name[QLC_FW_खाता_NAME_LEN];
पूर्ण;

काष्ठा qlc_83xx_reset अणु
	काष्ठा qlc_83xx_reset_hdr *hdr;
	पूर्णांक	seq_index;
	पूर्णांक	seq_error;
	पूर्णांक	array_index;
	u32	array[QLC_83XX_MAX_RESET_SEQ_ENTRIES];
	u8	*buff;
	u8	*stop_offset;
	u8	*start_offset;
	u8	*init_offset;
	u8	seq_end;
	u8	ढाँचा_end;
पूर्ण;

#घोषणा QLC_83XX_IDC_DISABLE_FW_RESET_RECOVERY		0x1
#घोषणा QLC_83XX_IDC_GRACEFULL_RESET			0x2
#घोषणा QLC_83XX_IDC_DISABLE_FW_DUMP			0x4
#घोषणा QLC_83XX_IDC_TIMESTAMP				0
#घोषणा QLC_83XX_IDC_DURATION				1
#घोषणा QLC_83XX_IDC_INIT_TIMEOUT_SECS			30
#घोषणा QLC_83XX_IDC_RESET_ACK_TIMEOUT_SECS		10
#घोषणा QLC_83XX_IDC_RESET_TIMEOUT_SECS		10
#घोषणा QLC_83XX_IDC_QUIESCE_ACK_TIMEOUT_SECS		20
#घोषणा QLC_83XX_IDC_FW_POLL_DELAY			(1 * HZ)
#घोषणा QLC_83XX_IDC_FW_FAIL_THRESH			2
#घोषणा QLC_83XX_IDC_MAX_FUNC_PER_PARTITION_INFO	8
#घोषणा QLC_83XX_IDC_MAX_CNA_FUNCTIONS			16
#घोषणा QLC_83XX_IDC_MAJOR_VERSION			1
#घोषणा QLC_83XX_IDC_MINOR_VERSION			0
#घोषणा QLC_83XX_IDC_FLASH_PARAM_ADDR			0x3e8020

काष्ठा qlcnic_adapter;
काष्ठा qlcnic_fw_dump;

काष्ठा qlc_83xx_idc अणु
	पूर्णांक (*state_entry) (काष्ठा qlcnic_adapter *);
	u64		sec_counter;
	u64		delay;
	अचिन्हित दीर्घ	status;
	पूर्णांक		err_code;
	पूर्णांक		collect_dump;
	u8		curr_state;
	u8		prev_state;
	u8		vnic_state;
	u8		vnic_रुको_limit;
	u8		quiesce_req;
	u8		delay_reset;
	अक्षर		**name;
पूर्ण;

क्रमागत qlcnic_vlan_operations अणु
	QLC_VLAN_ADD = 0,
	QLC_VLAN_DELETE
पूर्ण;

/* Device States */
क्रमागत qlcnic_83xx_states अणु
	QLC_83XX_IDC_DEV_UNKNOWN,
	QLC_83XX_IDC_DEV_COLD,
	QLC_83XX_IDC_DEV_INIT,
	QLC_83XX_IDC_DEV_READY,
	QLC_83XX_IDC_DEV_NEED_RESET,
	QLC_83XX_IDC_DEV_NEED_QUISCENT,
	QLC_83XX_IDC_DEV_FAILED,
	QLC_83XX_IDC_DEV_QUISCENT
पूर्ण;

#घोषणा QLCNIC_MBX_RSP(reg)		LSW(reg)
#घोषणा QLCNIC_MBX_NUM_REGS(reg)	(MSW(reg) & 0x1FF)
#घोषणा QLCNIC_MBX_STATUS(reg)		(((reg) >> 25) & 0x7F)
#घोषणा QLCNIC_MBX_HOST(ahw, i)	((ahw)->pci_base0 + ((i) * 4))
#घोषणा QLCNIC_MBX_FW(ahw, i)		((ahw)->pci_base0 + 0x800 + ((i) * 4))

/* Mailbox process AEN count */
#घोषणा QLC_83XX_IDC_COMP_AEN			3
#घोषणा QLC_83XX_MBX_AEN_CNT			5
#घोषणा QLC_83XX_MODULE_LOADED			1
#घोषणा QLC_83XX_MBX_READY			2
#घोषणा QLC_83XX_MBX_AEN_ACK			3
#घोषणा QLC_83XX_SFP_PRESENT(data)		((data) & 3)
#घोषणा QLC_83XX_SFP_ERR(data)			(((data) >> 2) & 3)
#घोषणा QLC_83XX_SFP_MODULE_TYPE(data)		(((data) >> 4) & 0x1F)
#घोषणा QLC_83XX_SFP_CU_LENGTH(data)		(LSB((data) >> 16))
#घोषणा QLC_83XX_SFP_TX_FAULT(data)		((data) & BIT_10)
#घोषणा QLC_83XX_LINK_STATS(data)		((data) & BIT_0)
#घोषणा QLC_83XX_CURRENT_LINK_SPEED(data)	(((data) >> 3) & 7)
#घोषणा QLC_83XX_LINK_PAUSE(data)		(((data) >> 6) & 3)
#घोषणा QLC_83XX_LINK_LB(data)			(((data) >> 8) & 7)
#घोषणा QLC_83XX_LINK_FEC(data)		((data) & BIT_12)
#घोषणा QLC_83XX_LINK_EEE(data)		((data) & BIT_13)
#घोषणा QLC_83XX_DCBX(data)			(((data) >> 28) & 7)
#घोषणा QLC_83XX_AUTONEG(data)			((data) & BIT_15)
#घोषणा QLC_83XX_TX_PAUSE			0x10
#घोषणा QLC_83XX_RX_PAUSE			0x20
#घोषणा QLC_83XX_TX_RX_PAUSE			0x30
#घोषणा QLC_83XX_CFG_STD_PAUSE			(1 << 5)
#घोषणा QLC_83XX_CFG_STD_TX_PAUSE		(1 << 20)
#घोषणा QLC_83XX_CFG_STD_RX_PAUSE		(2 << 20)
#घोषणा QLC_83XX_CFG_STD_TX_RX_PAUSE		(3 << 20)
#घोषणा QLC_83XX_ENABLE_AUTONEG		(1 << 15)
#घोषणा QLC_83XX_CFG_LOOPBACK_HSS		(2 << 1)
#घोषणा QLC_83XX_CFG_LOOPBACK_PHY		(3 << 1)
#घोषणा QLC_83XX_CFG_LOOPBACK_EXT		(4 << 1)

/* LED configuration settings */
#घोषणा QLC_83XX_ENABLE_BEACON		0xe
#घोषणा QLC_83XX_BEACON_ON		1
#घोषणा QLC_83XX_BEACON_OFF		0
#घोषणा QLC_83XX_LED_RATE		0xff
#घोषणा QLC_83XX_LED_ACT		(1 << 10)
#घोषणा QLC_83XX_LED_MOD		(0 << 13)
#घोषणा QLC_83XX_LED_CONFIG	(QLC_83XX_LED_RATE | QLC_83XX_LED_ACT |	\
				 QLC_83XX_LED_MOD)

#घोषणा QLC_83XX_10M_LINK	1
#घोषणा QLC_83XX_100M_LINK	2
#घोषणा QLC_83XX_1G_LINK	3
#घोषणा QLC_83XX_10G_LINK	4
#घोषणा QLC_83XX_STAT_TX	3
#घोषणा QLC_83XX_STAT_RX	2
#घोषणा QLC_83XX_STAT_MAC	1
#घोषणा QLC_83XX_TX_STAT_REGS	14
#घोषणा QLC_83XX_RX_STAT_REGS	40
#घोषणा QLC_83XX_MAC_STAT_REGS	94

#घोषणा QLC_83XX_GET_FUNC_PRIVILEGE(VAL, FN)	(0x3 & ((VAL) >> (FN * 2)))
#घोषणा QLC_83XX_SET_FUNC_OPMODE(VAL, FN)	((VAL) << (FN * 2))
#घोषणा QLC_83XX_DEFAULT_OPMODE			0x55555555
#घोषणा QLC_83XX_PRIVLEGED_FUNC			0x1
#घोषणा QLC_83XX_VIRTUAL_FUNC				0x2

#घोषणा QLC_83XX_LB_MAX_FILTERS			2048
#घोषणा QLC_83XX_LB_BUCKET_SIZE			256
#घोषणा QLC_83XX_MINIMUM_VECTOR			3
#घोषणा QLC_83XX_MAX_MC_COUNT			38
#घोषणा QLC_83XX_MAX_UC_COUNT			4096

#घोषणा QLC_83XX_PVID_STRIP_CAPABILITY		BIT_22
#घोषणा QLC_83XX_GET_FUNC_MODE_FROM_NPAR_INFO(val)	(val & 0x80000000)
#घोषणा QLC_83XX_GET_LRO_CAPABILITY(val)		(val & 0x20)
#घोषणा QLC_83XX_GET_LSO_CAPABILITY(val)		(val & 0x40)
#घोषणा QLC_83XX_GET_HW_LRO_CAPABILITY(val)		(val & 0x400)
#घोषणा QLC_83XX_GET_VLAN_ALIGN_CAPABILITY(val)	(val & 0x4000)
#घोषणा QLC_83XX_GET_FW_LRO_MSS_CAPABILITY(val)	(val & 0x20000)
#घोषणा QLC_83XX_ESWITCH_CAPABILITY			BIT_23
#घोषणा QLC_83XX_SRIOV_MODE				0x1
#घोषणा QLCNIC_BRDTYPE_83XX_10G			0x0083

#घोषणा QLC_83XX_FLASH_SPI_STATUS		0x2808E010
#घोषणा QLC_83XX_FLASH_SPI_CONTROL		0x2808E014
#घोषणा QLC_83XX_FLASH_STATUS			0x42100004
#घोषणा QLC_83XX_FLASH_CONTROL			0x42110004
#घोषणा QLC_83XX_FLASH_ADDR			0x42110008
#घोषणा QLC_83XX_FLASH_WRDATA			0x4211000C
#घोषणा QLC_83XX_FLASH_RDDATA			0x42110018
#घोषणा QLC_83XX_FLASH_सूचीECT_WINDOW		0x42110030
#घोषणा QLC_83XX_FLASH_सूचीECT_DATA(DATA)	(0x42150000 | (0x0000FFFF&DATA))
#घोषणा QLC_83XX_FLASH_SECTOR_ERASE_CMD	0xdeadbeef
#घोषणा QLC_83XX_FLASH_WRITE_CMD		0xdacdacda
#घोषणा QLC_83XX_FLASH_BULK_WRITE_CMD		0xcadcadca
#घोषणा QLC_83XX_FLASH_READ_RETRY_COUNT	5000
#घोषणा QLC_83XX_FLASH_STATUS_READY		0x6
#घोषणा QLC_83XX_FLASH_WRITE_MIN		2
#घोषणा QLC_83XX_FLASH_WRITE_MAX		64
#घोषणा QLC_83XX_FLASH_STATUS_REG_POLL_DELAY	1
#घोषणा QLC_83XX_ERASE_MODE			1
#घोषणा QLC_83XX_WRITE_MODE			2
#घोषणा QLC_83XX_BULK_WRITE_MODE		3
#घोषणा QLC_83XX_FLASH_FDT_WRITE_DEF_SIG	0xFD0100
#घोषणा QLC_83XX_FLASH_FDT_ERASE_DEF_SIG	0xFD0300
#घोषणा QLC_83XX_FLASH_FDT_READ_MFG_ID_VAL	0xFD009F
#घोषणा QLC_83XX_FLASH_OEM_ERASE_SIG		0xFD03D8
#घोषणा QLC_83XX_FLASH_OEM_WRITE_SIG		0xFD0101
#घोषणा QLC_83XX_FLASH_OEM_READ_SIG		0xFD0005
#घोषणा QLC_83XX_FLASH_ADDR_TEMP_VAL		0x00800000
#घोषणा QLC_83XX_FLASH_ADDR_SECOND_TEMP_VAL	0x00800001
#घोषणा QLC_83XX_FLASH_WRDATA_DEF		0x0
#घोषणा QLC_83XX_FLASH_READ_CTRL		0x3F
#घोषणा QLC_83XX_FLASH_SPI_CTRL		0x4
#घोषणा QLC_83XX_FLASH_FIRST_ERASE_MS_VAL	0x2
#घोषणा QLC_83XX_FLASH_SECOND_ERASE_MS_VAL	0x5
#घोषणा QLC_83XX_FLASH_LAST_ERASE_MS_VAL	0x3D
#घोषणा QLC_83XX_FLASH_FIRST_MS_PATTERN	0x43
#घोषणा QLC_83XX_FLASH_SECOND_MS_PATTERN	0x7F
#घोषणा QLC_83XX_FLASH_LAST_MS_PATTERN		0x7D
#घोषणा QLC_83xx_FLASH_MAX_WAIT_USEC		100
#घोषणा QLC_83XX_FLASH_LOCK_TIMEOUT		10000

क्रमागत qlc_83xx_mbx_cmd_type अणु
	QLC_83XX_MBX_CMD_WAIT = 0,
	QLC_83XX_MBX_CMD_NO_WAIT,
	QLC_83XX_MBX_CMD_BUSY_WAIT,
पूर्ण;

क्रमागत qlc_83xx_mbx_response_states अणु
	QLC_83XX_MBX_RESPONSE_WAIT = 0,
	QLC_83XX_MBX_RESPONSE_ARRIVED,
पूर्ण;

#घोषणा QLC_83XX_MBX_RESPONSE_FAILED	0x2
#घोषणा QLC_83XX_MBX_RESPONSE_UNKNOWN	0x3

/* Additional रेजिस्टरs in 83xx */
क्रमागत qlc_83xx_ext_regs अणु
	QLCNIC_GLOBAL_RESET = 0,
	QLCNIC_WILDCARD,
	QLCNIC_INFORMANT,
	QLCNIC_HOST_MBX_CTRL,
	QLCNIC_FW_MBX_CTRL,
	QLCNIC_BOOTLOADER_ADDR,
	QLCNIC_BOOTLOADER_SIZE,
	QLCNIC_FW_IMAGE_ADDR,
	QLCNIC_MBX_INTR_ENBL,
	QLCNIC_DEF_INT_MASK,
	QLCNIC_DEF_INT_ID,
	QLC_83XX_IDC_MAJ_VERSION,
	QLC_83XX_IDC_DEV_STATE,
	QLC_83XX_IDC_DRV_PRESENCE,
	QLC_83XX_IDC_DRV_ACK,
	QLC_83XX_IDC_CTRL,
	QLC_83XX_IDC_DRV_AUDIT,
	QLC_83XX_IDC_MIN_VERSION,
	QLC_83XX_RECOVER_DRV_LOCK,
	QLC_83XX_IDC_PF_0,
	QLC_83XX_IDC_PF_1,
	QLC_83XX_IDC_PF_2,
	QLC_83XX_IDC_PF_3,
	QLC_83XX_IDC_PF_4,
	QLC_83XX_IDC_PF_5,
	QLC_83XX_IDC_PF_6,
	QLC_83XX_IDC_PF_7,
	QLC_83XX_IDC_PF_8,
	QLC_83XX_IDC_PF_9,
	QLC_83XX_IDC_PF_10,
	QLC_83XX_IDC_PF_11,
	QLC_83XX_IDC_PF_12,
	QLC_83XX_IDC_PF_13,
	QLC_83XX_IDC_PF_14,
	QLC_83XX_IDC_PF_15,
	QLC_83XX_IDC_DEV_PARTITION_INFO_1,
	QLC_83XX_IDC_DEV_PARTITION_INFO_2,
	QLC_83XX_DRV_OP_MODE,
	QLC_83XX_VNIC_STATE,
	QLC_83XX_DRV_LOCK,
	QLC_83XX_DRV_UNLOCK,
	QLC_83XX_DRV_LOCK_ID,
	QLC_83XX_ASIC_TEMP,
पूर्ण;

/* Initialize/Stop NIC command bit definitions */
#घोषणा QLC_REGISTER_LB_IDC		BIT_0
#घोषणा QLC_REGISTER_DCB_AEN		BIT_1
#घोषणा QLC_83XX_MULTI_TEन_अंकCY_INFO	BIT_29
#घोषणा QLC_INIT_FW_RESOURCES		BIT_31

/* 83xx funcitons */
पूर्णांक qlcnic_83xx_get_fw_version(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_issue_cmd(काष्ठा qlcnic_adapter *, काष्ठा qlcnic_cmd_args *);
पूर्णांक qlcnic_83xx_setup_पूर्णांकr(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_get_func_no(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_cam_lock(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_cam_unlock(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_send_ctrl_op(काष्ठा qlcnic_adapter *, काष्ठा qlcnic_cmd_args *, u32);
व्योम qlcnic_83xx_add_sysfs(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_हटाओ_sysfs(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_ग_लिखो_crb(काष्ठा qlcnic_adapter *, अक्षर *, loff_t, माप_प्रकार);
व्योम qlcnic_83xx_पढ़ो_crb(काष्ठा qlcnic_adapter *, अक्षर *, loff_t, माप_प्रकार);
पूर्णांक qlcnic_83xx_rd_reg_indirect(काष्ठा qlcnic_adapter *, uदीर्घ, पूर्णांक *);
पूर्णांक qlcnic_83xx_wrt_reg_indirect(काष्ठा qlcnic_adapter *, uदीर्घ, u32);
पूर्णांक qlcnic_83xx_nic_set_promisc(काष्ठा qlcnic_adapter *, u32);
पूर्णांक qlcnic_83xx_config_hw_lro(काष्ठा qlcnic_adapter *, पूर्णांक);
पूर्णांक qlcnic_83xx_config_rss(काष्ठा qlcnic_adapter *, पूर्णांक);
व्योम qlcnic_83xx_change_l2_filter(काष्ठा qlcnic_adapter *adapter, u64 *addr,
				  u16 vlan, काष्ठा qlcnic_host_tx_ring *ring);
पूर्णांक qlcnic_83xx_get_pci_info(काष्ठा qlcnic_adapter *, काष्ठा qlcnic_pci_info *);
पूर्णांक qlcnic_83xx_set_nic_info(काष्ठा qlcnic_adapter *, काष्ठा qlcnic_info *);
व्योम qlcnic_83xx_initialize_nic(काष्ठा qlcnic_adapter *, पूर्णांक);

पूर्णांक qlcnic_83xx_napi_add(काष्ठा qlcnic_adapter *, काष्ठा net_device *);
व्योम qlcnic_83xx_napi_del(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_napi_enable(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_napi_disable(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_config_led(काष्ठा qlcnic_adapter *, u32, u32);
पूर्णांक qlcnic_ind_wr(काष्ठा qlcnic_adapter *, u32, u32);
पूर्णांक qlcnic_ind_rd(काष्ठा qlcnic_adapter *, u32);
पूर्णांक qlcnic_83xx_create_rx_ctx(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_create_tx_ctx(काष्ठा qlcnic_adapter *,
			      काष्ठा qlcnic_host_tx_ring *, पूर्णांक);
व्योम qlcnic_83xx_del_rx_ctx(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_del_tx_ctx(काष्ठा qlcnic_adapter *,
			    काष्ठा qlcnic_host_tx_ring *);
पूर्णांक qlcnic_83xx_get_nic_info(काष्ठा qlcnic_adapter *, काष्ठा qlcnic_info *, u8);
पूर्णांक qlcnic_83xx_setup_link_event(काष्ठा qlcnic_adapter *, पूर्णांक);
व्योम qlcnic_83xx_process_rcv_ring_diag(काष्ठा qlcnic_host_sds_ring *);
पूर्णांक qlcnic_83xx_config_पूर्णांकrpt(काष्ठा qlcnic_adapter *, bool);
पूर्णांक qlcnic_83xx_sre_macaddr_change(काष्ठा qlcnic_adapter *, u8 *, u16, u8);
पूर्णांक qlcnic_83xx_get_mac_address(काष्ठा qlcnic_adapter *, u8 *, u8);
पूर्णांक qlcnic_83xx_alloc_mbx_args(काष्ठा qlcnic_cmd_args *,
			       काष्ठा qlcnic_adapter *, u32);
व्योम qlcnic_मुक्त_mbx_args(काष्ठा qlcnic_cmd_args *);
व्योम qlcnic_set_npar_data(काष्ठा qlcnic_adapter *, स्थिर काष्ठा qlcnic_info *,
			  काष्ठा qlcnic_info *);
पूर्णांक qlcnic_83xx_config_पूर्णांकr_coal(काष्ठा qlcnic_adapter *,
				 काष्ठा ethtool_coalesce *);
पूर्णांक qlcnic_83xx_set_rx_tx_पूर्णांकr_coal(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_get_port_info(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_enable_mbx_पूर्णांकerrupt(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_disable_mbx_पूर्णांकr(काष्ठा qlcnic_adapter *);
irqवापस_t qlcnic_83xx_clear_legacy_पूर्णांकr(काष्ठा qlcnic_adapter *);
irqवापस_t qlcnic_83xx_पूर्णांकr(पूर्णांक, व्योम *);
irqवापस_t qlcnic_83xx_पंचांगp_पूर्णांकr(पूर्णांक, व्योम *);
व्योम qlcnic_83xx_check_vf(काष्ठा qlcnic_adapter *,
			  स्थिर काष्ठा pci_device_id *);
पूर्णांक qlcnic_83xx_config_शेष_opmode(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_setup_mbx_पूर्णांकr(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_मुक्त_mbx_पूर्णांकr(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_रेजिस्टर_map(काष्ठा qlcnic_hardware_context *);
व्योम qlcnic_83xx_idc_aen_work(काष्ठा work_काष्ठा *);
व्योम qlcnic_83xx_config_ipaddr(काष्ठा qlcnic_adapter *, __be32, पूर्णांक);

पूर्णांक qlcnic_83xx_erase_flash_sector(काष्ठा qlcnic_adapter *, u32);
पूर्णांक qlcnic_83xx_flash_bulk_ग_लिखो(काष्ठा qlcnic_adapter *, u32, u32 *, पूर्णांक);
पूर्णांक qlcnic_83xx_flash_ग_लिखो32(काष्ठा qlcnic_adapter *, u32, u32 *);
पूर्णांक qlcnic_83xx_lock_flash(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_unlock_flash(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_save_flash_status(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_restore_flash_status(काष्ठा qlcnic_adapter *, पूर्णांक);
पूर्णांक qlcnic_83xx_पढ़ो_flash_mfg_id(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_पढ़ो_flash_descriptor_table(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_flash_पढ़ो32(काष्ठा qlcnic_adapter *, u32, u8 *, पूर्णांक);
पूर्णांक qlcnic_83xx_lockless_flash_पढ़ो32(काष्ठा qlcnic_adapter *,
				      u32, u8 *, पूर्णांक);
पूर्णांक qlcnic_83xx_init(काष्ठा qlcnic_adapter *, पूर्णांक);
पूर्णांक qlcnic_83xx_idc_पढ़ोy_state_entry(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_idc_poll_dev_state(काष्ठा work_काष्ठा *);
व्योम qlcnic_83xx_idc_निकास(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_idc_request_reset(काष्ठा qlcnic_adapter *, u32);
पूर्णांक qlcnic_83xx_lock_driver(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_unlock_driver(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_set_शेष_offload_settings(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_idc_vnic_pf_entry(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_disable_vnic_mode(काष्ठा qlcnic_adapter *, पूर्णांक);
पूर्णांक qlcnic_83xx_config_vnic_opmode(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_get_vnic_vport_info(काष्ठा qlcnic_adapter *,
				    काष्ठा qlcnic_info *, u8);
पूर्णांक qlcnic_83xx_get_vnic_pf_info(काष्ठा qlcnic_adapter *, काष्ठा qlcnic_info *);
पूर्णांक qlcnic_83xx_set_port_eचयन_status(काष्ठा qlcnic_adapter *, पूर्णांक, पूर्णांक *);

व्योम qlcnic_83xx_get_minidump_ढाँचा(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_get_stats(काष्ठा qlcnic_adapter *adapter, u64 *data);
पूर्णांक qlcnic_83xx_extend_md_capab(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_get_link_ksettings(काष्ठा qlcnic_adapter *adapter,
				   काष्ठा ethtool_link_ksettings *ecmd);
पूर्णांक qlcnic_83xx_set_link_ksettings(काष्ठा qlcnic_adapter *adapter,
				   स्थिर काष्ठा ethtool_link_ksettings *ecmd);
व्योम qlcnic_83xx_get_छोड़ोparam(काष्ठा qlcnic_adapter *,
				काष्ठा ethtool_छोड़ोparam *);
पूर्णांक qlcnic_83xx_set_छोड़ोparam(काष्ठा qlcnic_adapter *,
			       काष्ठा ethtool_छोड़ोparam *);
पूर्णांक qlcnic_83xx_test_link(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_get_port_type(काष्ठा qlcnic_adapter *adapter);
पूर्णांक qlcnic_83xx_reg_test(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_get_regs_len(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_get_रेजिस्टरs(काष्ठा qlcnic_adapter *, u32 *);
पूर्णांक qlcnic_83xx_loopback_test(काष्ठा net_device *, u8);
पूर्णांक qlcnic_83xx_पूर्णांकerrupt_test(काष्ठा net_device *);
पूर्णांक qlcnic_83xx_set_led(काष्ठा net_device *, क्रमागत ethtool_phys_id_state);
पूर्णांक qlcnic_83xx_flash_test(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_enable_flash_ग_लिखो(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_disable_flash_ग_लिखो(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_enable_mbx_poll(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_disable_mbx_poll(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_idc_init(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_idc_reattach_driver(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_set_vnic_opmode(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_check_vnic_state(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_aer_stop_poll_work(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_83xx_aer_reset(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_aer_start_poll_work(काष्ठा qlcnic_adapter *);
u32 qlcnic_83xx_get_saved_state(व्योम *, u32);
व्योम qlcnic_83xx_set_saved_state(व्योम *, u32, u32);
व्योम qlcnic_83xx_cache_पंचांगpl_hdr_values(काष्ठा qlcnic_fw_dump *);
u32 qlcnic_83xx_get_cap_size(व्योम *, पूर्णांक);
व्योम qlcnic_83xx_set_sys_info(व्योम *, पूर्णांक, u32);
व्योम qlcnic_83xx_store_cap_mask(व्योम *, u32);
पूर्णांक qlcnic_ms_mem_ग_लिखो128(काष्ठा qlcnic_adapter *, u64, u32 *, u32);
#पूर्ण_अगर
