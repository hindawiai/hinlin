<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#अगर_अघोषित _QLCNIC_H_
#घोषणा _QLCNIC_H_

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश <linux/tcp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/firmware.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/समयr.h>
#समावेश <linux/irq.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/bitops.h>
#समावेश <linux/अगर_vlan.h>

#समावेश "qlcnic_hdr.h"
#समावेश "qlcnic_hw.h"
#समावेश "qlcnic_83xx_hw.h"
#समावेश "qlcnic_dcb.h"

#घोषणा _QLCNIC_LINUX_MAJOR 5
#घोषणा _QLCNIC_LINUX_MINOR 3
#घोषणा _QLCNIC_LINUX_SUBVERSION 66
#घोषणा QLCNIC_LINUX_VERSIONID  "5.3.66"
#घोषणा QLCNIC_DRV_IDC_VER  0x01
#घोषणा QLCNIC_DRIVER_VERSION  ((_QLCNIC_LINUX_MAJOR << 16) |\
		 (_QLCNIC_LINUX_MINOR << 8) | (_QLCNIC_LINUX_SUBVERSION))

#घोषणा QLCNIC_VERSION_CODE(a, b, c)	(((a) << 24) + ((b) << 16) + (c))
#घोषणा _major(v)	(((v) >> 24) & 0xff)
#घोषणा _minor(v)	(((v) >> 16) & 0xff)
#घोषणा _build(v)	((v) & 0xffff)

/* version in image has weird encoding:
 *  7:0  - major
 * 15:8  - minor
 * 31:16 - build (little endian)
 */
#घोषणा QLCNIC_DECODE_VERSION(v) \
	QLCNIC_VERSION_CODE(((v) & 0xff), (((v) >> 8) & 0xff), ((v) >> 16))

#घोषणा QLCNIC_MIN_FW_VERSION     QLCNIC_VERSION_CODE(4, 4, 2)
#घोषणा QLCNIC_NUM_FLASH_SECTORS (64)
#घोषणा QLCNIC_FLASH_SECTOR_SIZE (64 * 1024)
#घोषणा QLCNIC_FLASH_TOTAL_SIZE  (QLCNIC_NUM_FLASH_SECTORS \
					* QLCNIC_FLASH_SECTOR_SIZE)

#घोषणा RCV_DESC_RINGSIZE(rds_ring)	\
	(माप(काष्ठा rcv_desc) * (rds_ring)->num_desc)
#घोषणा RCV_BUFF_RINGSIZE(rds_ring)	\
	(माप(काष्ठा qlcnic_rx_buffer) * rds_ring->num_desc)
#घोषणा STATUS_DESC_RINGSIZE(sds_ring)	\
	(माप(काष्ठा status_desc) * (sds_ring)->num_desc)
#घोषणा TX_BUFF_RINGSIZE(tx_ring)	\
	(माप(काष्ठा qlcnic_cmd_buffer) * tx_ring->num_desc)
#घोषणा TX_DESC_RINGSIZE(tx_ring)	\
	(माप(काष्ठा cmd_desc_type0) * tx_ring->num_desc)

#घोषणा QLCNIC_P3P_A0		0x50
#घोषणा QLCNIC_P3P_C0		0x58

#घोषणा QLCNIC_IS_REVISION_P3P(REVISION)     (REVISION >= QLCNIC_P3P_A0)

#घोषणा FIRST_PAGE_GROUP_START	0
#घोषणा FIRST_PAGE_GROUP_END	0x100000

#घोषणा P3P_MAX_MTU                     (9600)
#घोषणा P3P_MIN_MTU                     (68)
#घोषणा QLCNIC_MAX_ETHERHDR                32 /* This contains some padding */

#घोषणा QLCNIC_P3P_RX_BUF_MAX_LEN         (QLCNIC_MAX_ETHERHDR + ETH_DATA_LEN)
#घोषणा QLCNIC_P3P_RX_JUMBO_BUF_MAX_LEN   (QLCNIC_MAX_ETHERHDR + P3P_MAX_MTU)
#घोषणा QLCNIC_CT_DEFAULT_RX_BUF_LEN	2048
#घोषणा QLCNIC_LRO_BUFFER_EXTRA		2048

/* Tx defines */
#घोषणा QLCNIC_MAX_FRAGS_PER_TX	14
#घोषणा MAX_TSO_HEADER_DESC	2
#घोषणा MGMT_CMD_DESC_RESV	4
#घोषणा TX_STOP_THRESH		((MAX_SKB_FRAGS >> 2) + MAX_TSO_HEADER_DESC \
							+ MGMT_CMD_DESC_RESV)
#घोषणा QLCNIC_MAX_TX_TIMEOUTS	2

/* Driver will use 1 Tx ring in INT-x/MSI/SRIOV mode. */
#घोषणा QLCNIC_SINGLE_RING		1
#घोषणा QLCNIC_DEF_SDS_RINGS		4
#घोषणा QLCNIC_DEF_TX_RINGS		4
#घोषणा QLCNIC_MAX_VNIC_TX_RINGS	4
#घोषणा QLCNIC_MAX_VNIC_SDS_RINGS	4
#घोषणा QLCNIC_83XX_MINIMUM_VECTOR	3
#घोषणा QLCNIC_82XX_MINIMUM_VECTOR	2

क्रमागत qlcnic_queue_type अणु
	QLCNIC_TX_QUEUE = 1,
	QLCNIC_RX_QUEUE,
पूर्ण;

/* Operational mode क्रम driver */
#घोषणा QLCNIC_VNIC_MODE	0xFF
#घोषणा QLCNIC_DEFAULT_MODE	0x0

/* Virtual NIC function count */
#घोषणा QLC_DEFAULT_VNIC_COUNT	8
#घोषणा QLC_84XX_VNIC_COUNT	16

/*
 * Following are the states of the Phantom. Phantom will set them and
 * Host will पढ़ो to check अगर the fields are correct.
 */
#घोषणा PHAN_INITIALIZE_FAILED		0xffff
#घोषणा PHAN_INITIALIZE_COMPLETE	0xff01

/* Host ग_लिखोs the following to notअगरy that it has करोne the init-handshake */
#घोषणा PHAN_INITIALIZE_ACK		0xf00f
#घोषणा PHAN_PEG_RCV_INITIALIZED	0xff01

#घोषणा NUM_RCV_DESC_RINGS	3

#घोषणा RCV_RING_NORMAL 0
#घोषणा RCV_RING_JUMBO	1

#घोषणा MIN_CMD_DESCRIPTORS		64
#घोषणा MIN_RCV_DESCRIPTORS		64
#घोषणा MIN_JUMBO_DESCRIPTORS		32

#घोषणा MAX_CMD_DESCRIPTORS		1024
#घोषणा MAX_RCV_DESCRIPTORS_1G		4096
#घोषणा MAX_RCV_DESCRIPTORS_10G 	8192
#घोषणा MAX_RCV_DESCRIPTORS_VF		2048
#घोषणा MAX_JUMBO_RCV_DESCRIPTORS_1G	512
#घोषणा MAX_JUMBO_RCV_DESCRIPTORS_10G	1024

#घोषणा DEFAULT_RCV_DESCRIPTORS_1G	2048
#घोषणा DEFAULT_RCV_DESCRIPTORS_10G	4096
#घोषणा DEFAULT_RCV_DESCRIPTORS_VF	1024
#घोषणा MAX_RDS_RINGS                   2

#घोषणा get_next_index(index, length)	\
	(((index) + 1) & ((length) - 1))

/*
 * Following data काष्ठाures describe the descriptors that will be used.
 * Added fileds of tcpHdrSize and ipHdrSize, The driver needs to करो it only when
 * we are करोing LSO (above the 1500 size packet) only.
 */
काष्ठा cmd_desc_type0 अणु
	u8 tcp_hdr_offset;	/* For LSO only */
	u8 ip_hdr_offset;	/* For LSO only */
	__le16 flags_opcode;	/* 15:13 unused, 12:7 opcode, 6:0 flags */
	__le32 nfrags__length;	/* 31:8 total len, 7:0 frag count */

	__le64 addr_buffer2;

	__le16 encap_descr;	/* 15:10 offset of outer L3 header,
				 * 9:6 number of 32bit words in outer L3 header,
				 * 5 offload outer L4 checksum,
				 * 4 offload outer L3 checksum,
				 * 3 Inner L4 type, TCP=0, UDP=1,
				 * 2 Inner L3 type, IPv4=0, IPv6=1,
				 * 1 Outer L3 type,IPv4=0, IPv6=1,
				 * 0 type of encapsulation, GRE=0, VXLAN=1
				 */
	__le16 mss;
	u8 port_ctxid;		/* 7:4 ctxid 3:0 port */
	u8 hdr_length;		/* LSO only : MAC+IP+TCP Hdr size */
	u8 outer_hdr_length;	/* Encapsulation only */
	u8 rsvd1;

	__le64 addr_buffer3;
	__le64 addr_buffer1;

	__le16 buffer_length[4];

	__le64 addr_buffer4;

	u8 eth_addr[ETH_ALEN];
	__le16 vlan_TCI;	/* In हाल of  encapsulation,
				 * this is क्रम outer VLAN
				 */

पूर्ण __attribute__ ((aligned(64)));

/* Note: माप(rcv_desc) should always be a mutliple of 2 */
काष्ठा rcv_desc अणु
	__le16 reference_handle;
	__le16 reserved;
	__le32 buffer_length;	/* allocated buffer length (usually 2K) */
	__le64 addr_buffer;
पूर्ण __packed;

काष्ठा status_desc अणु
	__le64 status_desc_data[2];
पूर्ण __attribute__ ((aligned(16)));

/* UNIFIED ROMIMAGE */
#घोषणा QLCNIC_UNI_FW_MIN_SIZE		0xc8000
#घोषणा QLCNIC_UNI_सूची_SECT_PRODUCT_TBL	0x0
#घोषणा QLCNIC_UNI_सूची_SECT_BOOTLD	0x6
#घोषणा QLCNIC_UNI_सूची_SECT_FW		0x7

/*Offsets */
#घोषणा QLCNIC_UNI_CHIP_REV_OFF		10
#घोषणा QLCNIC_UNI_FLAGS_OFF		11
#घोषणा QLCNIC_UNI_BIOS_VERSION_OFF 	12
#घोषणा QLCNIC_UNI_BOOTLD_IDX_OFF	27
#घोषणा QLCNIC_UNI_FIRMWARE_IDX_OFF 	29

काष्ठा uni_table_descअणु
	__le32	findex;
	__le32	num_entries;
	__le32	entry_size;
	__le32	reserved[5];
पूर्ण;

काष्ठा uni_data_descअणु
	__le32	findex;
	__le32	size;
	__le32	reserved[5];
पूर्ण;

/* Flash Defines and Structures */
#घोषणा QLCNIC_FLT_LOCATION	0x3F1000
#घोषणा QLCNIC_FDT_LOCATION     0x3F0000
#घोषणा QLCNIC_B0_FW_IMAGE_REGION 0x74
#घोषणा QLCNIC_C0_FW_IMAGE_REGION 0x97
#घोषणा QLCNIC_BOOTLD_REGION    0X72
काष्ठा qlcnic_flt_header अणु
	u16 version;
	u16 len;
	u16 checksum;
	u16 reserved;
पूर्ण;

काष्ठा qlcnic_flt_entry अणु
	u8 region;
	u8 reserved0;
	u8 attrib;
	u8 reserved1;
	u32 size;
	u32 start_addr;
	u32 end_addr;
पूर्ण;

/* Flash Descriptor Table */
काष्ठा qlcnic_fdt अणु
	u32	valid;
	u16	ver;
	u16	len;
	u16	cksum;
	u16	unused;
	u8	model[16];
	u8	mfg_id;
	u16	id;
	u8	flag;
	u8	erase_cmd;
	u8	alt_erase_cmd;
	u8	ग_लिखो_enable_cmd;
	u8	ग_लिखो_enable_bits;
	u8	ग_लिखो_statusreg_cmd;
	u8	unरक्षित_sec_cmd;
	u8	पढ़ो_manuf_cmd;
	u32	block_size;
	u32	alt_block_size;
	u32	flash_size;
	u32	ग_लिखो_enable_data;
	u8	पढ़ोid_addr_len;
	u8	ग_लिखो_disable_bits;
	u8	पढ़ो_dev_id_len;
	u8	chip_erase_cmd;
	u16	पढ़ो_समयo;
	u8	रक्षित_sec_cmd;
	u8	resvd[65];
पूर्ण;
/* Magic number to let user know flash is programmed */
#घोषणा	QLCNIC_BDINFO_MAGIC 0x12345678

#घोषणा QLCNIC_BRDTYPE_P3P_REF_QG	0x0021
#घोषणा QLCNIC_BRDTYPE_P3P_HMEZ		0x0022
#घोषणा QLCNIC_BRDTYPE_P3P_10G_CX4_LP	0x0023
#घोषणा QLCNIC_BRDTYPE_P3P_4_GB		0x0024
#घोषणा QLCNIC_BRDTYPE_P3P_IMEZ		0x0025
#घोषणा QLCNIC_BRDTYPE_P3P_10G_SFP_PLUS	0x0026
#घोषणा QLCNIC_BRDTYPE_P3P_10000_BASE_T	0x0027
#घोषणा QLCNIC_BRDTYPE_P3P_XG_LOM	0x0028
#घोषणा QLCNIC_BRDTYPE_P3P_4_GB_MM	0x0029
#घोषणा QLCNIC_BRDTYPE_P3P_10G_SFP_CT	0x002a
#घोषणा QLCNIC_BRDTYPE_P3P_10G_SFP_QT	0x002b
#घोषणा QLCNIC_BRDTYPE_P3P_10G_CX4	0x0031
#घोषणा QLCNIC_BRDTYPE_P3P_10G_XFP	0x0032
#घोषणा QLCNIC_BRDTYPE_P3P_10G_TP	0x0080

#घोषणा QLCNIC_MSIX_TABLE_OFFSET	0x44

/* Flash memory map */
#घोषणा QLCNIC_BRDCFG_START	0x4000		/* board config */
#घोषणा QLCNIC_BOOTLD_START	0x10000		/* bootld */
#घोषणा QLCNIC_IMAGE_START	0x43000		/* compressed image */
#घोषणा QLCNIC_USER_START	0x3E8000	/* Firmware info */

#घोषणा QLCNIC_FW_VERSION_OFFSET	(QLCNIC_USER_START+0x408)
#घोषणा QLCNIC_FW_SIZE_OFFSET		(QLCNIC_USER_START+0x40c)
#घोषणा QLCNIC_FW_SERIAL_NUM_OFFSET	(QLCNIC_USER_START+0x81c)
#घोषणा QLCNIC_BIOS_VERSION_OFFSET	(QLCNIC_USER_START+0x83c)

#घोषणा QLCNIC_BRDTYPE_OFFSET		(QLCNIC_BRDCFG_START+0x8)
#घोषणा QLCNIC_FW_MAGIC_OFFSET		(QLCNIC_BRDCFG_START+0x128)

#घोषणा QLCNIC_FW_MIN_SIZE		(0x3fffff)
#घोषणा QLCNIC_UNIFIED_ROMIMAGE  	0
#घोषणा QLCNIC_FLASH_ROMIMAGE		1
#घोषणा QLCNIC_UNKNOWN_ROMIMAGE		0xff

#घोषणा QLCNIC_UNIFIED_ROMIMAGE_NAME	"phanfw.bin"
#घोषणा QLCNIC_FLASH_ROMIMAGE_NAME	"flash"

बाह्य अक्षर qlcnic_driver_name[];

बाह्य पूर्णांक qlcnic_use_msi;
बाह्य पूर्णांक qlcnic_use_msi_x;
बाह्य पूर्णांक qlcnic_स्वतः_fw_reset;
बाह्य पूर्णांक qlcnic_load_fw_file;

/* Number of status descriptors to handle per पूर्णांकerrupt */
#घोषणा MAX_STATUS_HANDLE	(64)

/*
 * qlcnic_skb_fragअणुपूर्ण is to contain mapping info क्रम each SG list. This
 * has to be मुक्तd when DMA is complete. This is part of qlcnic_tx_bufferअणुपूर्ण.
 */
काष्ठा qlcnic_skb_frag अणु
	u64 dma;
	u64 length;
पूर्ण;

/*    Following defines are क्रम the state of the buffers    */
#घोषणा	QLCNIC_BUFFER_FREE	0
#घोषणा	QLCNIC_BUFFER_BUSY	1

/*
 * There will be one qlcnic_buffer per skb packet.    These will be
 * used to save the dma info क्रम pci_unmap_page()
 */
काष्ठा qlcnic_cmd_buffer अणु
	काष्ठा sk_buff *skb;
	काष्ठा qlcnic_skb_frag frag_array[MAX_SKB_FRAGS + 1];
	u32 frag_count;
पूर्ण;

/* In rx_buffer, we करो not need multiple fragments as is a single buffer */
काष्ठा qlcnic_rx_buffer अणु
	u16 ref_handle;
	काष्ठा sk_buff *skb;
	काष्ठा list_head list;
	u64 dma;
पूर्ण;

/* Board types */
#घोषणा	QLCNIC_GBE	0x01
#घोषणा	QLCNIC_XGBE	0x02

/*
 * Interrupt coalescing शेषs. The शेषs are क्रम 1500 MTU. It is
 * adjusted based on configured MTU.
 */
#घोषणा QLCNIC_INTR_COAL_TYPE_RX		1
#घोषणा QLCNIC_INTR_COAL_TYPE_TX		2
#घोषणा QLCNIC_INTR_COAL_TYPE_RX_TX		3

#घोषणा QLCNIC_DEF_INTR_COALESCE_RX_TIME_US	3
#घोषणा QLCNIC_DEF_INTR_COALESCE_RX_PACKETS	256

#घोषणा QLCNIC_DEF_INTR_COALESCE_TX_TIME_US	64
#घोषणा QLCNIC_DEF_INTR_COALESCE_TX_PACKETS	64

#घोषणा QLCNIC_INTR_DEFAULT			0x04
#घोषणा QLCNIC_CONFIG_INTR_COALESCE		3
#घोषणा QLCNIC_DEV_INFO_SIZE			2

काष्ठा qlcnic_nic_पूर्णांकr_coalesce अणु
	u8	type;
	u8	sts_ring_mask;
	u16	rx_packets;
	u16	rx_समय_us;
	u16	tx_packets;
	u16	tx_समय_us;
	u16	flag;
	u32	समयr_out;
पूर्ण;

काष्ठा qlcnic_83xx_dump_ढाँचा_hdr अणु
	u32	type;
	u32	offset;
	u32	size;
	u32	cap_mask;
	u32	num_entries;
	u32	version;
	u32	बारtamp;
	u32	checksum;
	u32	drv_cap_mask;
	u32	sys_info[3];
	u32	saved_state[16];
	u32	cap_sizes[8];
	u32	ocm_wnd_reg[16];
	u32	rsvd[];
पूर्ण;

काष्ठा qlcnic_82xx_dump_ढाँचा_hdr अणु
	u32	type;
	u32	offset;
	u32	size;
	u32	cap_mask;
	u32	num_entries;
	u32	version;
	u32	बारtamp;
	u32	checksum;
	u32	drv_cap_mask;
	u32	sys_info[3];
	u32	saved_state[16];
	u32	cap_sizes[8];
	u32	rsvd[7];
	u32	capabilities;
	u32	rsvd1[];
पूर्ण;

#घोषणा QLC_PEX_DMA_READ_SIZE	(PAGE_SIZE * 16)

काष्ठा qlcnic_fw_dump अणु
	u8	clr;	/* flag to indicate अगर dump is cleared */
	bool	enable; /* enable/disable dump */
	u32	size;	/* total size of the dump */
	u32	cap_mask; /* Current capture mask */
	व्योम	*data;	/* dump data area */
	व्योम	*पंचांगpl_hdr;
	dma_addr_t phys_addr;
	व्योम	*dma_buffer;
	bool	use_pex_dma;
	/* Read only elements which are common between 82xx and 83xx
	 * ढाँचा header. Update these values immediately after we पढ़ो
	 * ढाँचा header from Firmware
	 */
	u32	पंचांगpl_hdr_size;
	u32	version;
	u32	num_entries;
	u32	offset;
पूर्ण;

/*
 * One hardware_contextअणुपूर्ण per adapter
 * contains पूर्णांकerrupt info as well shared hardware info.
 */
काष्ठा qlcnic_hardware_context अणु
	व्योम __iomem *pci_base0;
	व्योम __iomem *ocm_win_crb;

	अचिन्हित दीर्घ pci_len0;

	rwlock_t crb_lock;
	काष्ठा mutex mem_lock;

	u8 revision_id;
	u8 pci_func;
	u8 linkup;
	u8 loopback_state;
	u8 beacon_state;
	u8 has_link_events;
	u8 fw_type;
	u8 physical_port;
	u8 reset_context;
	u8 msix_supported;
	u8 max_mac_filters;
	u8 mc_enabled;
	u8 max_mc_count;
	u8 diag_test;
	u8 num_msix;
	u8 nic_mode;
	पूर्णांक diag_cnt;

	u16 max_uc_count;
	u16 port_type;
	u16 board_type;
	u16 supported_type;

	u32 link_speed;
	u16 link_duplex;
	u16 link_स्वतःneg;
	u16 module_type;

	u16 op_mode;
	u16 चयन_mode;
	u16 max_tx_ques;
	u16 max_rx_ques;
	u16 max_mtu;
	u32 msg_enable;
	u16 total_nic_func;
	u16 max_pci_func;
	u32 max_vnic_func;
	u32 total_pci_func;

	u32 capabilities;
	u32 extra_capability[3];
	u32 temp;
	u32 पूर्णांक_vec_bit;
	u32 fw_hal_version;
	u32 port_config;
	काष्ठा qlcnic_hardware_ops *hw_ops;
	काष्ठा qlcnic_nic_पूर्णांकr_coalesce coal;
	काष्ठा qlcnic_fw_dump fw_dump;
	काष्ठा qlcnic_fdt fdt;
	काष्ठा qlc_83xx_reset reset;
	काष्ठा qlc_83xx_idc idc;
	काष्ठा qlc_83xx_fw_info *fw_info;
	काष्ठा qlcnic_पूर्णांकrpt_config *पूर्णांकr_tbl;
	काष्ठा qlcnic_sriov *sriov;
	u32 *reg_tbl;
	u32 *ext_reg_tbl;
	u32 mbox_aen[QLC_83XX_MBX_AEN_CNT];
	u32 mbox_reg[4];
	काष्ठा qlcnic_mailbox *mailbox;
	u8 extend_lb_समय;
	u8 phys_port_id[ETH_ALEN];
	u8 lb_mode;
	काष्ठा device *hwmon_dev;
	u32 post_mode;
	bool run_post;
पूर्ण;

काष्ठा qlcnic_adapter_stats अणु
	u64  xmitcalled;
	u64  xmitfinished;
	u64  rxdropped;
	u64  txdropped;
	u64  csummed;
	u64  rx_pkts;
	u64  lro_pkts;
	u64  rxbytes;
	u64  txbytes;
	u64  lrobytes;
	u64  lso_frames;
	u64  encap_lso_frames;
	u64  encap_tx_csummed;
	u64  encap_rx_csummed;
	u64  xmit_on;
	u64  xmit_off;
	u64  skb_alloc_failure;
	u64  null_rxbuf;
	u64  rx_dma_map_error;
	u64  tx_dma_map_error;
	u64  spurious_पूर्णांकr;
	u64  mac_filter_limit_overrun;
	u64  mbx_spurious_पूर्णांकr;
पूर्ण;

/*
 * Rcv Descriptor Context. One such per Rcv Descriptor. There may
 * be one Rcv Descriptor क्रम normal packets, one क्रम jumbo and may be others.
 */
काष्ठा qlcnic_host_rds_ring अणु
	व्योम __iomem *crb_rcv_producer;
	काष्ठा rcv_desc *desc_head;
	काष्ठा qlcnic_rx_buffer *rx_buf_arr;
	u32 num_desc;
	u32 producer;
	u32 dma_size;
	u32 skb_size;
	u32 flags;
	काष्ठा list_head मुक्त_list;
	spinlock_t lock;
	dma_addr_t phys_addr;
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

काष्ठा qlcnic_host_sds_ring अणु
	u32 consumer;
	u32 num_desc;
	व्योम __iomem *crb_sts_consumer;

	काष्ठा qlcnic_host_tx_ring *tx_ring;
	काष्ठा status_desc *desc_head;
	काष्ठा qlcnic_adapter *adapter;
	काष्ठा napi_काष्ठा napi;
	काष्ठा list_head मुक्त_list[NUM_RCV_DESC_RINGS];

	व्योम __iomem *crb_पूर्णांकr_mask;
	पूर्णांक irq;

	dma_addr_t phys_addr;
	अक्षर name[IFNAMSIZ + 12];
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

काष्ठा qlcnic_tx_queue_stats अणु
	u64 xmit_on;
	u64 xmit_off;
	u64 xmit_called;
	u64 xmit_finished;
	u64 tx_bytes;
पूर्ण;

काष्ठा qlcnic_host_tx_ring अणु
	पूर्णांक irq;
	व्योम __iomem *crb_पूर्णांकr_mask;
	अक्षर name[IFNAMSIZ + 12];
	u16 ctx_id;

	u32 state;
	u32 producer;
	u32 sw_consumer;
	u32 num_desc;

	काष्ठा qlcnic_tx_queue_stats tx_stats;

	व्योम __iomem *crb_cmd_producer;
	काष्ठा cmd_desc_type0 *desc_head;
	काष्ठा qlcnic_adapter *adapter;
	काष्ठा napi_काष्ठा napi;
	काष्ठा qlcnic_cmd_buffer *cmd_buf_arr;
	__le32 *hw_consumer;

	dma_addr_t phys_addr;
	dma_addr_t hw_cons_phys_addr;
	काष्ठा netdev_queue *txq;
	/* Lock to protect Tx descriptors cleanup */
	spinlock_t tx_clean_lock;
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

/*
 * Receive context. There is one such काष्ठाure per instance of the
 * receive processing. Any state inक्रमmation that is relevant to
 * the receive, and is must be in this काष्ठाure. The global data may be
 * present अन्यथाwhere.
 */
काष्ठा qlcnic_recv_context अणु
	काष्ठा qlcnic_host_rds_ring *rds_rings;
	काष्ठा qlcnic_host_sds_ring *sds_rings;
	u32 state;
	u16 context_id;
	u16 virt_port;
पूर्ण;

/* HW context creation */

#घोषणा QLCNIC_OS_CRB_RETRY_COUNT	4000

#घोषणा QLCNIC_CDRP_CMD_BIT		0x80000000

/*
 * All responses must have the QLCNIC_CDRP_CMD_BIT cleared
 * in the crb QLCNIC_CDRP_CRB_OFFSET.
 */
#घोषणा QLCNIC_CDRP_FORM_RSP(rsp)	(rsp)
#घोषणा QLCNIC_CDRP_IS_RSP(rsp)	(((rsp) & QLCNIC_CDRP_CMD_BIT) == 0)

#घोषणा QLCNIC_CDRP_RSP_OK		0x00000001
#घोषणा QLCNIC_CDRP_RSP_FAIL		0x00000002
#घोषणा QLCNIC_CDRP_RSP_TIMEOUT 	0x00000003

/*
 * All commands must have the QLCNIC_CDRP_CMD_BIT set in
 * the crb QLCNIC_CDRP_CRB_OFFSET.
 */
#घोषणा QLCNIC_CDRP_FORM_CMD(cmd)	(QLCNIC_CDRP_CMD_BIT | (cmd))

#घोषणा QLCNIC_RCODE_SUCCESS		0
#घोषणा QLCNIC_RCODE_INVALID_ARGS	6
#घोषणा QLCNIC_RCODE_NOT_SUPPORTED	9
#घोषणा QLCNIC_RCODE_NOT_PERMITTED	10
#घोषणा QLCNIC_RCODE_NOT_IMPL		15
#घोषणा QLCNIC_RCODE_INVALID		16
#घोषणा QLCNIC_RCODE_TIMEOUT		17
#घोषणा QLCNIC_DESTROY_CTX_RESET	0

/*
 * Capabilities Announced
 */
#घोषणा QLCNIC_CAP0_LEGACY_CONTEXT	(1)
#घोषणा QLCNIC_CAP0_LEGACY_MN		(1 << 2)
#घोषणा QLCNIC_CAP0_LSO 		(1 << 6)
#घोषणा QLCNIC_CAP0_JUMBO_CONTIGUOUS	(1 << 7)
#घोषणा QLCNIC_CAP0_LRO_CONTIGUOUS	(1 << 8)
#घोषणा QLCNIC_CAP0_VALIDOFF		(1 << 11)
#घोषणा QLCNIC_CAP0_LRO_MSS		(1 << 21)
#घोषणा QLCNIC_CAP0_TX_MULTI		(1 << 22)

/*
 * Context state
 */
#घोषणा QLCNIC_HOST_CTX_STATE_FREED	0
#घोषणा QLCNIC_HOST_CTX_STATE_ACTIVE	2

/*
 * Rx context
 */

काष्ठा qlcnic_hostrq_sds_ring अणु
	__le64 host_phys_addr;	/* Ring base addr */
	__le32 ring_size;		/* Ring entries */
	__le16 msi_index;
	__le16 rsvd;		/* Padding */
पूर्ण __packed;

काष्ठा qlcnic_hostrq_rds_ring अणु
	__le64 host_phys_addr;	/* Ring base addr */
	__le64 buff_size;		/* Packet buffer size */
	__le32 ring_size;		/* Ring entries */
	__le32 ring_kind;		/* Class of ring */
पूर्ण __packed;

काष्ठा qlcnic_hostrq_rx_ctx अणु
	__le64 host_rsp_dma_addr;	/* Response dma'd here */
	__le32 capabilities[4];		/* Flag bit vector */
	__le32 host_पूर्णांक_crb_mode;	/* Interrupt crb usage */
	__le32 host_rds_crb_mode;	/* RDS crb usage */
	/* These ring offsets are relative to data[0] below */
	__le32 rds_ring_offset;	/* Offset to RDS config */
	__le32 sds_ring_offset;	/* Offset to SDS config */
	__le16 num_rds_rings;	/* Count of RDS rings */
	__le16 num_sds_rings;	/* Count of SDS rings */
	__le16 valid_field_offset;
	u8  txrx_sds_binding;
	u8  msix_handler;
	u8  reserved[128];      /* reserve space क्रम future expansion*/
	/* MUST BE 64-bit aligned.
	   The following is packed:
	   - N hostrq_rds_rings
	   - N hostrq_sds_rings */
	अक्षर data[];
पूर्ण __packed;

काष्ठा qlcnic_cardrsp_rds_ringअणु
	__le32 host_producer_crb;	/* Crb to use */
	__le32 rsvd1;		/* Padding */
पूर्ण __packed;

काष्ठा qlcnic_cardrsp_sds_ring अणु
	__le32 host_consumer_crb;	/* Crb to use */
	__le32 पूर्णांकerrupt_crb;	/* Crb to use */
पूर्ण __packed;

काष्ठा qlcnic_cardrsp_rx_ctx अणु
	/* These ring offsets are relative to data[0] below */
	__le32 rds_ring_offset;	/* Offset to RDS config */
	__le32 sds_ring_offset;	/* Offset to SDS config */
	__le32 host_ctx_state;	/* Starting State */
	__le32 num_fn_per_port;	/* How many PCI fn share the port */
	__le16 num_rds_rings;	/* Count of RDS rings */
	__le16 num_sds_rings;	/* Count of SDS rings */
	__le16 context_id;		/* Handle क्रम context */
	u8  phys_port;		/* Physical id of port */
	u8  virt_port;		/* Virtual/Logical id of port */
	u8  reserved[128];	/* save space क्रम future expansion */
	/*  MUST BE 64-bit aligned.
	   The following is packed:
	   - N cardrsp_rds_rings
	   - N cardrs_sds_rings */
	अक्षर data[];
पूर्ण __packed;

#घोषणा SIZखातापूर्ण_HOSTRQ_RX(HOSTRQ_RX, rds_rings, sds_rings)	\
	(माप(HOSTRQ_RX) + 					\
	(rds_rings)*(माप(काष्ठा qlcnic_hostrq_rds_ring)) +		\
	(sds_rings)*(माप(काष्ठा qlcnic_hostrq_sds_ring)))

#घोषणा SIZखातापूर्ण_CARDRSP_RX(CARDRSP_RX, rds_rings, sds_rings) 	\
	(माप(CARDRSP_RX) + 					\
	(rds_rings)*(माप(काष्ठा qlcnic_cardrsp_rds_ring)) + 		\
	(sds_rings)*(माप(काष्ठा qlcnic_cardrsp_sds_ring)))

/*
 * Tx context
 */

काष्ठा qlcnic_hostrq_cds_ring अणु
	__le64 host_phys_addr;	/* Ring base addr */
	__le32 ring_size;		/* Ring entries */
	__le32 rsvd;		/* Padding */
पूर्ण __packed;

काष्ठा qlcnic_hostrq_tx_ctx अणु
	__le64 host_rsp_dma_addr;	/* Response dma'd here */
	__le64 cmd_cons_dma_addr;	/*  */
	__le64 dummy_dma_addr;	/*  */
	__le32 capabilities[4];	/* Flag bit vector */
	__le32 host_पूर्णांक_crb_mode;	/* Interrupt crb usage */
	__le32 rsvd1;		/* Padding */
	__le16 rsvd2;		/* Padding */
	__le16 पूर्णांकerrupt_ctl;
	__le16 msi_index;
	__le16 rsvd3;		/* Padding */
	काष्ठा qlcnic_hostrq_cds_ring cds_ring;	/* Desc of cds ring */
	u8  reserved[128];	/* future expansion */
पूर्ण __packed;

काष्ठा qlcnic_cardrsp_cds_ring अणु
	__le32 host_producer_crb;	/* Crb to use */
	__le32 पूर्णांकerrupt_crb;	/* Crb to use */
पूर्ण __packed;

काष्ठा qlcnic_cardrsp_tx_ctx अणु
	__le32 host_ctx_state;	/* Starting state */
	__le16 context_id;		/* Handle क्रम context */
	u8  phys_port;		/* Physical id of port */
	u8  virt_port;		/* Virtual/Logical id of port */
	काष्ठा qlcnic_cardrsp_cds_ring cds_ring;	/* Card cds settings */
	u8  reserved[128];	/* future expansion */
पूर्ण __packed;

#घोषणा SIZखातापूर्ण_HOSTRQ_TX(HOSTRQ_TX)	(माप(HOSTRQ_TX))
#घोषणा SIZखातापूर्ण_CARDRSP_TX(CARDRSP_TX)	(माप(CARDRSP_TX))

/* CRB */

#घोषणा QLCNIC_HOST_RDS_CRB_MODE_UNIQUE	0
#घोषणा QLCNIC_HOST_RDS_CRB_MODE_SHARED	1
#घोषणा QLCNIC_HOST_RDS_CRB_MODE_CUSTOM	2
#घोषणा QLCNIC_HOST_RDS_CRB_MODE_MAX	3

#घोषणा QLCNIC_HOST_INT_CRB_MODE_UNIQUE	0
#घोषणा QLCNIC_HOST_INT_CRB_MODE_SHARED	1
#घोषणा QLCNIC_HOST_INT_CRB_MODE_NORX	2
#घोषणा QLCNIC_HOST_INT_CRB_MODE_NOTX	3
#घोषणा QLCNIC_HOST_INT_CRB_MODE_NORXTX	4


/* MAC */

#घोषणा MC_COUNT_P3P	38

#घोषणा QLCNIC_MAC_NOOP	0
#घोषणा QLCNIC_MAC_ADD	1
#घोषणा QLCNIC_MAC_DEL	2
#घोषणा QLCNIC_MAC_VLAN_ADD	3
#घोषणा QLCNIC_MAC_VLAN_DEL	4

क्रमागत qlcnic_mac_type अणु
	QLCNIC_UNICAST_MAC,
	QLCNIC_MULTICAST_MAC,
	QLCNIC_BROADCAST_MAC,
पूर्ण;

काष्ठा qlcnic_mac_vlan_list अणु
	काष्ठा list_head list;
	uपूर्णांक8_t mac_addr[ETH_ALEN+2];
	u16 vlan_id;
	क्रमागत qlcnic_mac_type mac_type;
पूर्ण;

/* MAC Learn */
#घोषणा NO_MAC_LEARN		0
#घोषणा DRV_MAC_LEARN		1
#घोषणा FDB_MAC_LEARN		2

#घोषणा QLCNIC_HOST_REQUEST	0x13
#घोषणा QLCNIC_REQUEST		0x14

#घोषणा QLCNIC_MAC_EVENT	0x1

#घोषणा QLCNIC_IP_UP		2
#घोषणा QLCNIC_IP_DOWN		3

#घोषणा QLCNIC_ILB_MODE		0x1
#घोषणा QLCNIC_ELB_MODE		0x2
#घोषणा QLCNIC_LB_MODE_MASK	0x3

#घोषणा QLCNIC_LINKEVENT	0x1
#घोषणा QLCNIC_LB_RESPONSE	0x2
#घोषणा QLCNIC_IS_LB_CONFIGURED(VAL)	\
		(VAL == (QLCNIC_LINKEVENT | QLCNIC_LB_RESPONSE))

/*
 * Driver --> Firmware
 */
#घोषणा QLCNIC_H2C_OPCODE_CONFIG_RSS			0x1
#घोषणा QLCNIC_H2C_OPCODE_CONFIG_INTR_COALESCE		0x3
#घोषणा QLCNIC_H2C_OPCODE_CONFIG_LED			0x4
#घोषणा QLCNIC_H2C_OPCODE_LRO_REQUEST			0x7
#घोषणा QLCNIC_H2C_OPCODE_SET_MAC_RECEIVE_MODE		0xc
#घोषणा QLCNIC_H2C_OPCODE_CONFIG_IPADDR		0x12

#घोषणा QLCNIC_H2C_OPCODE_GET_LINKEVENT		0x15
#घोषणा QLCNIC_H2C_OPCODE_CONFIG_BRIDGING		0x17
#घोषणा QLCNIC_H2C_OPCODE_CONFIG_HW_LRO		0x18
#घोषणा QLCNIC_H2C_OPCODE_CONFIG_LOOPBACK		0x13

/*
 * Firmware --> Driver
 */

#घोषणा QLCNIC_C2H_OPCODE_CONFIG_LOOPBACK		0x8f
#घोषणा QLCNIC_C2H_OPCODE_GET_LINKEVENT_RESPONSE	0x8D
#घोषणा QLCNIC_C2H_OPCODE_GET_DCB_AEN			0x90

#घोषणा VPORT_MISS_MODE_DROP		0 /* drop all unmatched */
#घोषणा VPORT_MISS_MODE_ACCEPT_ALL	1 /* accept all packets */
#घोषणा VPORT_MISS_MODE_ACCEPT_MULTI	2 /* accept unmatched multicast */

#घोषणा QLCNIC_LRO_REQUEST_CLEANUP	4

/* Capabilites received */
#घोषणा QLCNIC_FW_CAPABILITY_TSO		BIT_1
#घोषणा QLCNIC_FW_CAPABILITY_BDG		BIT_8
#घोषणा QLCNIC_FW_CAPABILITY_FVLANTX		BIT_9
#घोषणा QLCNIC_FW_CAPABILITY_HW_LRO		BIT_10
#घोषणा QLCNIC_FW_CAPABILITY_2_MULTI_TX		BIT_4
#घोषणा QLCNIC_FW_CAPABILITY_MULTI_LOOPBACK	BIT_27
#घोषणा QLCNIC_FW_CAPABILITY_MORE_CAPS		BIT_31

#घोषणा QLCNIC_FW_CAPABILITY_2_LRO_MAX_TCP_SEG	BIT_2
#घोषणा QLCNIC_FW_CAP2_HW_LRO_IPV6		BIT_3
#घोषणा QLCNIC_FW_CAPABILITY_SET_DRV_VER	BIT_5
#घोषणा QLCNIC_FW_CAPABILITY_2_BEACON		BIT_7
#घोषणा QLCNIC_FW_CAPABILITY_2_PER_PORT_ESWITCH_CFG	BIT_9
#घोषणा QLCNIC_FW_CAPABILITY_2_EXT_ISCSI_DUMP	BIT_13

#घोषणा QLCNIC_83XX_FW_CAPAB_ENCAP_RX_OFFLOAD	BIT_0
#घोषणा QLCNIC_83XX_FW_CAPAB_ENCAP_TX_OFFLOAD	BIT_1
#घोषणा QLCNIC_83XX_FW_CAPAB_ENCAP_CKO_OFFLOAD	BIT_4

/* module types */
#घोषणा LINKEVENT_MODULE_NOT_PRESENT			1
#घोषणा LINKEVENT_MODULE_OPTICAL_UNKNOWN		2
#घोषणा LINKEVENT_MODULE_OPTICAL_SRLR			3
#घोषणा LINKEVENT_MODULE_OPTICAL_LRM			4
#घोषणा LINKEVENT_MODULE_OPTICAL_SFP_1G 		5
#घोषणा LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLE	6
#घोषणा LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLELEN	7
#घोषणा LINKEVENT_MODULE_TWINAX 			8

#घोषणा LINKSPEED_10GBPS	10000
#घोषणा LINKSPEED_1GBPS 	1000
#घोषणा LINKSPEED_100MBPS	100
#घोषणा LINKSPEED_10MBPS	10

#घोषणा LINKSPEED_ENCODED_10MBPS	0
#घोषणा LINKSPEED_ENCODED_100MBPS	1
#घोषणा LINKSPEED_ENCODED_1GBPS 	2

#घोषणा LINKEVENT_AUTONEG_DISABLED	0
#घोषणा LINKEVENT_AUTONEG_ENABLED	1

#घोषणा LINKEVENT_HALF_DUPLEX		0
#घोषणा LINKEVENT_FULL_DUPLEX		1

#घोषणा LINKEVENT_LINKSPEED_MBPS	0
#घोषणा LINKEVENT_LINKSPEED_ENCODED	1

/* firmware response header:
 *	63:58 - message type
 *	57:56 - owner
 *	55:53 - desc count
 *	52:48 - reserved
 *	47:40 - completion id
 *	39:32 - opcode
 *	31:16 - error code
 *	15:00 - reserved
 */
#घोषणा qlcnic_get_nic_msg_opcode(msg_hdr)	\
	((msg_hdr >> 32) & 0xFF)

काष्ठा qlcnic_fw_msg अणु
	जोड़ अणु
		काष्ठा अणु
			u64 hdr;
			u64 body[7];
		पूर्ण;
		u64 words[8];
	पूर्ण;
पूर्ण;

काष्ठा qlcnic_nic_req अणु
	__le64 qhdr;
	__le64 req_hdr;
	__le64 words[6];
पूर्ण __packed;

काष्ठा qlcnic_mac_req अणु
	u8 op;
	u8 tag;
	u8 mac_addr[6];
पूर्ण;

काष्ठा qlcnic_vlan_req अणु
	__le16 vlan_id;
	__le16 rsvd[3];
पूर्ण __packed;

काष्ठा qlcnic_ipaddr अणु
	__be32 ipv4;
	__be32 ipv6[4];
पूर्ण;

#घोषणा QLCNIC_MSI_ENABLED		0x02
#घोषणा QLCNIC_MSIX_ENABLED		0x04
#घोषणा QLCNIC_LRO_ENABLED		0x01
#घोषणा QLCNIC_LRO_DISABLED		0x00
#घोषणा QLCNIC_BRIDGE_ENABLED       	0X10
#घोषणा QLCNIC_DIAG_ENABLED		0x20
#घोषणा QLCNIC_ESWITCH_ENABLED		0x40
#घोषणा QLCNIC_ADAPTER_INITIALIZED	0x80
#घोषणा QLCNIC_TAGGING_ENABLED		0x100
#घोषणा QLCNIC_MACSPOOF			0x200
#घोषणा QLCNIC_MAC_OVERRIDE_DISABLED	0x400
#घोषणा QLCNIC_PROMISC_DISABLED		0x800
#घोषणा QLCNIC_NEED_FLR			0x1000
#घोषणा QLCNIC_FW_RESET_OWNER		0x2000
#घोषणा QLCNIC_FW_HANG			0x4000
#घोषणा QLCNIC_FW_LRO_MSS_CAP		0x8000
#घोषणा QLCNIC_TX_INTR_SHARED		0x10000
#घोषणा QLCNIC_APP_CHANGED_FLAGS	0x20000
#घोषणा QLCNIC_HAS_PHYS_PORT_ID		0x40000
#घोषणा QLCNIC_TSS_RSS			0x80000

#घोषणा QLCNIC_VLAN_FILTERING		0x800000

#घोषणा QLCNIC_IS_MSI_FAMILY(adapter) \
	((adapter)->flags & (QLCNIC_MSI_ENABLED | QLCNIC_MSIX_ENABLED))
#घोषणा QLCNIC_IS_TSO_CAPABLE(adapter)  \
	((adapter)->ahw->capabilities & QLCNIC_FW_CAPABILITY_TSO)

#घोषणा QLCNIC_BEACON_EANBLE		0xC
#घोषणा QLCNIC_BEACON_DISABLE		0xD

#घोषणा QLCNIC_BEACON_ON		2
#घोषणा QLCNIC_BEACON_OFF		0

#घोषणा QLCNIC_MSIX_TBL_SPACE		8192
#घोषणा QLCNIC_PCI_REG_MSIX_TBL 	0x44
#घोषणा QLCNIC_MSIX_TBL_PGSIZE		4096

#घोषणा QLCNIC_ADAPTER_UP_MAGIC 777

#घोषणा __QLCNIC_FW_ATTACHED		0
#घोषणा __QLCNIC_DEV_UP 		1
#घोषणा __QLCNIC_RESETTING		2
#घोषणा __QLCNIC_START_FW 		4
#घोषणा __QLCNIC_AER			5
#घोषणा __QLCNIC_DIAG_RES_ALLOC		6
#घोषणा __QLCNIC_LED_ENABLE		7
#घोषणा __QLCNIC_ELB_INPROGRESS		8
#घोषणा __QLCNIC_MULTI_TX_UNIQUE	9
#घोषणा __QLCNIC_SRIOV_ENABLE		10
#घोषणा __QLCNIC_SRIOV_CAPABLE		11
#घोषणा __QLCNIC_MBX_POLL_ENABLE	12
#घोषणा __QLCNIC_DIAG_MODE		13
#घोषणा __QLCNIC_MAINTEन_अंकCE_MODE	16

#घोषणा QLCNIC_INTERRUPT_TEST		1
#घोषणा QLCNIC_LOOPBACK_TEST		2
#घोषणा QLCNIC_LED_TEST		3

#घोषणा QLCNIC_FILTER_AGE	80
#घोषणा QLCNIC_READD_AGE	20
#घोषणा QLCNIC_LB_MAX_FILTERS	64
#घोषणा QLCNIC_LB_BUCKET_SIZE	32
#घोषणा QLCNIC_ILB_MAX_RCV_LOOP	10

काष्ठा qlcnic_filter अणु
	काष्ठा hlist_node fnode;
	u8 faddr[ETH_ALEN];
	u16 vlan_id;
	अचिन्हित दीर्घ fसमय;
पूर्ण;

काष्ठा qlcnic_filter_hash अणु
	काष्ठा hlist_head *fhead;
	u8 fnum;
	u16 fmax;
	u16 fbucket_size;
पूर्ण;

/* Mailbox specअगरic data काष्ठाures */
काष्ठा qlcnic_mailbox अणु
	काष्ठा workqueue_काष्ठा	*work_q;
	काष्ठा qlcnic_adapter	*adapter;
	स्थिर काष्ठा qlcnic_mbx_ops *ops;
	काष्ठा work_काष्ठा	work;
	काष्ठा completion	completion;
	काष्ठा list_head	cmd_q;
	अचिन्हित दीर्घ		status;
	spinlock_t		queue_lock;	/* Mailbox queue lock */
	spinlock_t		aen_lock;	/* Mailbox response/AEN lock */
	u32			rsp_status;
	u32			num_cmds;
पूर्ण;

काष्ठा qlcnic_adapter अणु
	काष्ठा qlcnic_hardware_context *ahw;
	काष्ठा qlcnic_recv_context *recv_ctx;
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pdev;

	अचिन्हित दीर्घ state;
	u32 flags;

	u16 num_txd;
	u16 num_rxd;
	u16 num_jumbo_rxd;
	u16 max_rxd;
	u16 max_jumbo_rxd;

	u8 max_rds_rings;

	u8 max_sds_rings; /* max sds rings supported by adapter */
	u8 max_tx_rings;  /* max tx rings supported by adapter */

	u8 drv_tx_rings;  /* max tx rings supported by driver */
	u8 drv_sds_rings; /* max sds rings supported by driver */

	u8 drv_tss_rings; /* tss ring input */
	u8 drv_rss_rings; /* rss ring input */

	u8 rx_csum;
	u8 portnum;

	u8 fw_रुको_cnt;
	u8 fw_fail_cnt;
	u8 tx_समयo_cnt;
	u8 need_fw_reset;
	u8 reset_ctx_cnt;

	u16 is_up;
	u16 rx_pvid;
	u16 tx_pvid;

	u32 irq;
	u32 heartbeat;

	u8 dev_state;
	u8 reset_ack_समयo;
	u8 dev_init_समयo;

	u8 mac_addr[ETH_ALEN];

	u64 dev_rst_समय;
	bool drv_mac_learn;
	bool fdb_mac_learn;
	bool rx_mac_learn;
	अचिन्हित दीर्घ vlans[BITS_TO_LONGS(VLAN_N_VID)];
	u8 flash_mfg_id;
	काष्ठा qlcnic_npar_info *npars;
	काष्ठा qlcnic_eचयन *eचयन;
	काष्ठा qlcnic_nic_ढाँचा *nic_ops;

	काष्ठा qlcnic_adapter_stats stats;
	काष्ठा list_head mac_list;

	व्योम __iomem	*tgt_mask_reg;
	व्योम __iomem	*tgt_status_reg;
	व्योम __iomem	*crb_पूर्णांक_state_reg;
	व्योम __iomem	*isr_पूर्णांक_vec;

	काष्ठा msix_entry *msix_entries;
	काष्ठा workqueue_काष्ठा *qlcnic_wq;
	काष्ठा delayed_work fw_work;
	काष्ठा delayed_work idc_aen_work;
	काष्ठा delayed_work mbx_poll_work;
	काष्ठा qlcnic_dcb *dcb;

	काष्ठा qlcnic_filter_hash fhash;
	काष्ठा qlcnic_filter_hash rx_fhash;
	काष्ठा list_head vf_mc_list;

	spinlock_t mac_learn_lock;
	/* spinlock क्रम catching rcv filters क्रम eचयन traffic */
	spinlock_t rx_mac_learn_lock;
	u32 file_prd_off;	/*File fw product offset*/
	u32 fw_version;
	u32 offload_flags;
	स्थिर काष्ठा firmware *fw;
पूर्ण;

काष्ठा qlcnic_info_le अणु
	__le16	pci_func;
	__le16	op_mode;	/* 1 = Priv, 2 = NP, 3 = NP passthru */
	__le16	phys_port;
	__le16	चयन_mode;	/* 0 = disabled, 1 = पूर्णांक, 2 = ext */

	__le32	capabilities;
	u8	max_mac_filters;
	u8	reserved1;
	__le16	max_mtu;

	__le16	max_tx_ques;
	__le16	max_rx_ques;
	__le16	min_tx_bw;
	__le16	max_tx_bw;
	__le32  op_type;
	__le16  max_bw_reg_offset;
	__le16  max_linkspeed_reg_offset;
	__le32  capability1;
	__le32  capability2;
	__le32  capability3;
	__le16  max_tx_mac_filters;
	__le16  max_rx_mcast_mac_filters;
	__le16  max_rx_ucast_mac_filters;
	__le16  max_rx_ip_addr;
	__le16  max_rx_lro_flow;
	__le16  max_rx_status_rings;
	__le16  max_rx_buf_rings;
	__le16  max_tx_vlan_keys;
	u8      total_pf;
	u8      total_rss_engines;
	__le16  max_vports;
	__le16	linkstate_reg_offset;
	__le16	bit_offsets;
	__le16  max_local_ipv6_addrs;
	__le16  max_remote_ipv6_addrs;
	u8	reserved2[56];
पूर्ण __packed;

काष्ठा qlcnic_info अणु
	u16	pci_func;
	u16	op_mode;
	u16	phys_port;
	u16	चयन_mode;
	u32	capabilities;
	u8	max_mac_filters;
	u16	max_mtu;
	u16	max_tx_ques;
	u16	max_rx_ques;
	u16	min_tx_bw;
	u16	max_tx_bw;
	u32	op_type;
	u16	max_bw_reg_offset;
	u16	max_linkspeed_reg_offset;
	u32	capability1;
	u32	capability2;
	u32	capability3;
	u16	max_tx_mac_filters;
	u16	max_rx_mcast_mac_filters;
	u16	max_rx_ucast_mac_filters;
	u16	max_rx_ip_addr;
	u16	max_rx_lro_flow;
	u16	max_rx_status_rings;
	u16	max_rx_buf_rings;
	u16	max_tx_vlan_keys;
	u8      total_pf;
	u8      total_rss_engines;
	u16	max_vports;
	u16	linkstate_reg_offset;
	u16	bit_offsets;
	u16	max_local_ipv6_addrs;
	u16	max_remote_ipv6_addrs;
पूर्ण;

काष्ठा qlcnic_pci_info_le अणु
	__le16	id;		/* pci function id */
	__le16	active;		/* 1 = Enabled */
	__le16	type;		/* 1 = NIC, 2 = FCoE, 3 = iSCSI */
	__le16	शेष_port;	/* शेष port number */

	__le16	tx_min_bw;	/* Multiple of 100mbpc */
	__le16	tx_max_bw;
	__le16	reserved1[2];

	u8	mac[ETH_ALEN];
	__le16  func_count;
	u8      reserved2[104];

पूर्ण __packed;

काष्ठा qlcnic_pci_info अणु
	u16	id;
	u16	active;
	u16	type;
	u16	शेष_port;
	u16	tx_min_bw;
	u16	tx_max_bw;
	u8	mac[ETH_ALEN];
	u16  func_count;
पूर्ण;

काष्ठा qlcnic_npar_info अणु
	bool	eचयन_status;
	u16	pvid;
	u16	min_bw;
	u16	max_bw;
	u8	phy_port;
	u8	type;
	u8	active;
	u8	enable_pm;
	u8	dest_npar;
	u8	discard_tagged;
	u8	mac_override;
	u8	mac_anti_spoof;
	u8	promisc_mode;
	u8	offload_flags;
	u8      pci_func;
	u8      mac[ETH_ALEN];
पूर्ण;

काष्ठा qlcnic_eचयन अणु
	u8	port;
	u8	active_vports;
	u8	active_vlans;
	u8	active_ucast_filters;
	u8	max_ucast_filters;
	u8	max_active_vlans;

	u32	flags;
#घोषणा QLCNIC_SWITCH_ENABLE		BIT_1
#घोषणा QLCNIC_SWITCH_VLAN_FILTERING	BIT_2
#घोषणा QLCNIC_SWITCH_PROMISC_MODE	BIT_3
#घोषणा QLCNIC_SWITCH_PORT_MIRRORING	BIT_4
पूर्ण;


#घोषणा MAX_BW			100	/* % of link speed */
#घोषणा MIN_BW			1	/* % of link speed */
#घोषणा MAX_VLAN_ID		4095
#घोषणा MIN_VLAN_ID		2
#घोषणा DEFAULT_MAC_LEARN	1

#घोषणा IS_VALID_VLAN(vlan)	(vlan >= MIN_VLAN_ID && vlan < MAX_VLAN_ID)
#घोषणा IS_VALID_BW(bw)		(bw <= MAX_BW)

काष्ठा qlcnic_pci_func_cfg अणु
	u16	func_type;
	u16	min_bw;
	u16	max_bw;
	u16	port_num;
	u8	pci_func;
	u8	func_state;
	u8	def_mac_addr[ETH_ALEN];
पूर्ण;

काष्ठा qlcnic_npar_func_cfg अणु
	u32	fw_capab;
	u16	port_num;
	u16	min_bw;
	u16	max_bw;
	u16	max_tx_queues;
	u16	max_rx_queues;
	u8	pci_func;
	u8	op_mode;
पूर्ण;

काष्ठा qlcnic_pm_func_cfg अणु
	u8	pci_func;
	u8	action;
	u8	dest_npar;
	u8	reserved[5];
पूर्ण;

काष्ठा qlcnic_esw_func_cfg अणु
	u16	vlan_id;
	u8	op_mode;
	u8	op_type;
	u8	pci_func;
	u8	host_vlan_tag;
	u8	promisc_mode;
	u8	discard_tagged;
	u8	mac_override;
	u8	mac_anti_spoof;
	u8	offload_flags;
	u8	reserved[5];
पूर्ण;

#घोषणा QLCNIC_STATS_VERSION		1
#घोषणा QLCNIC_STATS_PORT		1
#घोषणा QLCNIC_STATS_ESWITCH		2
#घोषणा QLCNIC_QUERY_RX_COUNTER		0
#घोषणा QLCNIC_QUERY_TX_COUNTER		1
#घोषणा QLCNIC_STATS_NOT_AVAIL	0xffffffffffffffffULL
#घोषणा QLCNIC_FILL_STATS(VAL1) \
	(((VAL1) == QLCNIC_STATS_NOT_AVAIL) ? 0 : VAL1)
#घोषणा QLCNIC_MAC_STATS 1
#घोषणा QLCNIC_ESW_STATS 2

#घोषणा QLCNIC_ADD_ESW_STATS(VAL1, VAL2)\
करो अणु	\
	अगर (((VAL1) == QLCNIC_STATS_NOT_AVAIL) && \
	    ((VAL2) != QLCNIC_STATS_NOT_AVAIL)) \
		(VAL1) = (VAL2); \
	अन्यथा अगर (((VAL1) != QLCNIC_STATS_NOT_AVAIL) && \
		 ((VAL2) != QLCNIC_STATS_NOT_AVAIL)) \
			(VAL1) += (VAL2); \
पूर्ण जबतक (0)

काष्ठा qlcnic_mac_statistics_le अणु
	__le64	mac_tx_frames;
	__le64	mac_tx_bytes;
	__le64	mac_tx_mcast_pkts;
	__le64	mac_tx_bcast_pkts;
	__le64	mac_tx_छोड़ो_cnt;
	__le64	mac_tx_ctrl_pkt;
	__le64	mac_tx_lt_64b_pkts;
	__le64	mac_tx_lt_127b_pkts;
	__le64	mac_tx_lt_255b_pkts;
	__le64	mac_tx_lt_511b_pkts;
	__le64	mac_tx_lt_1023b_pkts;
	__le64	mac_tx_lt_1518b_pkts;
	__le64	mac_tx_gt_1518b_pkts;
	__le64	rsvd1[3];

	__le64	mac_rx_frames;
	__le64	mac_rx_bytes;
	__le64	mac_rx_mcast_pkts;
	__le64	mac_rx_bcast_pkts;
	__le64	mac_rx_छोड़ो_cnt;
	__le64	mac_rx_ctrl_pkt;
	__le64	mac_rx_lt_64b_pkts;
	__le64	mac_rx_lt_127b_pkts;
	__le64	mac_rx_lt_255b_pkts;
	__le64	mac_rx_lt_511b_pkts;
	__le64	mac_rx_lt_1023b_pkts;
	__le64	mac_rx_lt_1518b_pkts;
	__le64	mac_rx_gt_1518b_pkts;
	__le64	rsvd2[3];

	__le64	mac_rx_length_error;
	__le64	mac_rx_length_small;
	__le64	mac_rx_length_large;
	__le64	mac_rx_jabber;
	__le64	mac_rx_dropped;
	__le64	mac_rx_crc_error;
	__le64	mac_align_error;
पूर्ण __packed;

काष्ठा qlcnic_mac_statistics अणु
	u64	mac_tx_frames;
	u64	mac_tx_bytes;
	u64	mac_tx_mcast_pkts;
	u64	mac_tx_bcast_pkts;
	u64	mac_tx_छोड़ो_cnt;
	u64	mac_tx_ctrl_pkt;
	u64	mac_tx_lt_64b_pkts;
	u64	mac_tx_lt_127b_pkts;
	u64	mac_tx_lt_255b_pkts;
	u64	mac_tx_lt_511b_pkts;
	u64	mac_tx_lt_1023b_pkts;
	u64	mac_tx_lt_1518b_pkts;
	u64	mac_tx_gt_1518b_pkts;
	u64	rsvd1[3];
	u64	mac_rx_frames;
	u64	mac_rx_bytes;
	u64	mac_rx_mcast_pkts;
	u64	mac_rx_bcast_pkts;
	u64	mac_rx_छोड़ो_cnt;
	u64	mac_rx_ctrl_pkt;
	u64	mac_rx_lt_64b_pkts;
	u64	mac_rx_lt_127b_pkts;
	u64	mac_rx_lt_255b_pkts;
	u64	mac_rx_lt_511b_pkts;
	u64	mac_rx_lt_1023b_pkts;
	u64	mac_rx_lt_1518b_pkts;
	u64	mac_rx_gt_1518b_pkts;
	u64	rsvd2[3];
	u64	mac_rx_length_error;
	u64	mac_rx_length_small;
	u64	mac_rx_length_large;
	u64	mac_rx_jabber;
	u64	mac_rx_dropped;
	u64	mac_rx_crc_error;
	u64	mac_align_error;
पूर्ण;

काष्ठा qlcnic_esw_stats_le अणु
	__le16 context_id;
	__le16 version;
	__le16 size;
	__le16 unused;
	__le64 unicast_frames;
	__le64 multicast_frames;
	__le64 broadcast_frames;
	__le64 dropped_frames;
	__le64 errors;
	__le64 local_frames;
	__le64 numbytes;
	__le64 rsvd[3];
पूर्ण __packed;

काष्ठा __qlcnic_esw_statistics अणु
	u16	context_id;
	u16	version;
	u16	size;
	u16	unused;
	u64	unicast_frames;
	u64	multicast_frames;
	u64	broadcast_frames;
	u64	dropped_frames;
	u64	errors;
	u64	local_frames;
	u64	numbytes;
	u64	rsvd[3];
पूर्ण;

काष्ठा qlcnic_esw_statistics अणु
	काष्ठा __qlcnic_esw_statistics rx;
	काष्ठा __qlcnic_esw_statistics tx;
पूर्ण;

#घोषणा QLCNIC_FORCE_FW_DUMP_KEY	0xdeadfeed
#घोषणा QLCNIC_ENABLE_FW_DUMP		0xaddfeed
#घोषणा QLCNIC_DISABLE_FW_DUMP		0xbadfeed
#घोषणा QLCNIC_FORCE_FW_RESET		0xdeaddead
#घोषणा QLCNIC_SET_QUIESCENT		0xadd00010
#घोषणा QLCNIC_RESET_QUIESCENT		0xadd00020

काष्ठा _cdrp_cmd अणु
	u32 num;
	u32 *arg;
पूर्ण;

काष्ठा qlcnic_cmd_args अणु
	काष्ठा completion	completion;
	काष्ठा list_head	list;
	काष्ठा _cdrp_cmd	req;
	काष्ठा _cdrp_cmd	rsp;
	atomic_t		rsp_status;
	पूर्णांक			pay_size;
	u32			rsp_opcode;
	u32			total_cmds;
	u32			op_type;
	u32			type;
	u32			cmd_op;
	u32			*hdr;	/* Back channel message header */
	u32			*pay;	/* Back channel message payload */
	u8			func_num;
पूर्ण;

पूर्णांक qlcnic_fw_cmd_get_minidump_temp(काष्ठा qlcnic_adapter *adapter);
पूर्णांक qlcnic_fw_cmd_set_port(काष्ठा qlcnic_adapter *adapter, u32 config);
पूर्णांक qlcnic_pci_mem_ग_लिखो_2M(काष्ठा qlcnic_adapter *, u64 off, u64 data);
पूर्णांक qlcnic_pci_mem_पढ़ो_2M(काष्ठा qlcnic_adapter *, u64 off, u64 *data);

#घोषणा ADDR_IN_RANGE(addr, low, high)	\
	(((addr) < (high)) && ((addr) >= (low)))

#घोषणा QLCRD32(adapter, off, err) \
	(adapter->ahw->hw_ops->पढ़ो_reg)(adapter, off, err)

#घोषणा QLCWR32(adapter, off, val) \
	adapter->ahw->hw_ops->ग_लिखो_reg(adapter, off, val)

पूर्णांक qlcnic_pcie_sem_lock(काष्ठा qlcnic_adapter *, पूर्णांक, u32);
व्योम qlcnic_pcie_sem_unlock(काष्ठा qlcnic_adapter *, पूर्णांक);

#घोषणा qlcnic_rom_lock(a)	\
	qlcnic_pcie_sem_lock((a), 2, QLCNIC_ROM_LOCK_ID)
#घोषणा qlcnic_rom_unlock(a)	\
	qlcnic_pcie_sem_unlock((a), 2)
#घोषणा qlcnic_phy_lock(a)	\
	qlcnic_pcie_sem_lock((a), 3, QLCNIC_PHY_LOCK_ID)
#घोषणा qlcnic_phy_unlock(a)	\
	qlcnic_pcie_sem_unlock((a), 3)
#घोषणा qlcnic_sw_lock(a)	\
	qlcnic_pcie_sem_lock((a), 6, 0)
#घोषणा qlcnic_sw_unlock(a)	\
	qlcnic_pcie_sem_unlock((a), 6)
#घोषणा crb_win_lock(a)	\
	qlcnic_pcie_sem_lock((a), 7, QLCNIC_CRB_WIN_LOCK_ID)
#घोषणा crb_win_unlock(a)	\
	qlcnic_pcie_sem_unlock((a), 7)

#घोषणा __QLCNIC_MAX_LED_RATE	0xf
#घोषणा __QLCNIC_MAX_LED_STATE	0x2

#घोषणा MAX_CTL_CHECK 1000

व्योम qlcnic_prune_lb_filters(काष्ठा qlcnic_adapter *adapter);
व्योम qlcnic_delete_lb_filters(काष्ठा qlcnic_adapter *adapter);
पूर्णांक qlcnic_dump_fw(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_enable_fw_dump_state(काष्ठा qlcnic_adapter *);
bool qlcnic_check_fw_dump_state(काष्ठा qlcnic_adapter *);

/* Functions from qlcnic_init.c */
व्योम qlcnic_schedule_work(काष्ठा qlcnic_adapter *, work_func_t, पूर्णांक);
पूर्णांक qlcnic_load_firmware(काष्ठा qlcnic_adapter *adapter);
पूर्णांक qlcnic_need_fw_reset(काष्ठा qlcnic_adapter *adapter);
व्योम qlcnic_request_firmware(काष्ठा qlcnic_adapter *adapter);
व्योम qlcnic_release_firmware(काष्ठा qlcnic_adapter *adapter);
पूर्णांक qlcnic_pinit_from_rom(काष्ठा qlcnic_adapter *adapter);
पूर्णांक qlcnic_setup_idc_param(काष्ठा qlcnic_adapter *adapter);
पूर्णांक qlcnic_check_flash_fw_ver(काष्ठा qlcnic_adapter *adapter);

पूर्णांक qlcnic_rom_fast_पढ़ो(काष्ठा qlcnic_adapter *adapter, u32 addr, u32 *valp);
पूर्णांक qlcnic_rom_fast_पढ़ो_words(काष्ठा qlcnic_adapter *adapter, पूर्णांक addr,
				u8 *bytes, माप_प्रकार size);
पूर्णांक qlcnic_alloc_sw_resources(काष्ठा qlcnic_adapter *adapter);
व्योम qlcnic_मुक्त_sw_resources(काष्ठा qlcnic_adapter *adapter);

व्योम __iomem *qlcnic_get_ioaddr(काष्ठा qlcnic_hardware_context *, u32);

पूर्णांक qlcnic_alloc_hw_resources(काष्ठा qlcnic_adapter *adapter);
व्योम qlcnic_मुक्त_hw_resources(काष्ठा qlcnic_adapter *adapter);

पूर्णांक qlcnic_fw_create_ctx(काष्ठा qlcnic_adapter *adapter);
व्योम qlcnic_fw_destroy_ctx(काष्ठा qlcnic_adapter *adapter);

व्योम qlcnic_reset_rx_buffers_list(काष्ठा qlcnic_adapter *adapter);
व्योम qlcnic_release_rx_buffers(काष्ठा qlcnic_adapter *adapter);
व्योम qlcnic_release_tx_buffers(काष्ठा qlcnic_adapter *,
			       काष्ठा qlcnic_host_tx_ring *);

पूर्णांक qlcnic_check_fw_status(काष्ठा qlcnic_adapter *adapter);
व्योम qlcnic_watchकरोg_task(काष्ठा work_काष्ठा *work);
व्योम qlcnic_post_rx_buffers(काष्ठा qlcnic_adapter *adapter,
		काष्ठा qlcnic_host_rds_ring *rds_ring, u8 ring_id);
व्योम qlcnic_set_multi(काष्ठा net_device *netdev);
व्योम qlcnic_flush_mcast_mac(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_nic_add_mac(काष्ठा qlcnic_adapter *, स्थिर u8 *, u16,
		       क्रमागत qlcnic_mac_type);
पूर्णांक qlcnic_nic_del_mac(काष्ठा qlcnic_adapter *, स्थिर u8 *);
व्योम qlcnic_82xx_मुक्त_mac_list(काष्ठा qlcnic_adapter *adapter);
पूर्णांक qlcnic_82xx_पढ़ो_phys_port_id(काष्ठा qlcnic_adapter *);

पूर्णांक qlcnic_fw_cmd_set_mtu(काष्ठा qlcnic_adapter *adapter, पूर्णांक mtu);
पूर्णांक qlcnic_fw_cmd_set_drv_version(काष्ठा qlcnic_adapter *, u32);
पूर्णांक qlcnic_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu);
netdev_features_t qlcnic_fix_features(काष्ठा net_device *netdev,
	netdev_features_t features);
पूर्णांक qlcnic_set_features(काष्ठा net_device *netdev, netdev_features_t features);
पूर्णांक qlcnic_config_bridged_mode(काष्ठा qlcnic_adapter *adapter, u32 enable);
व्योम qlcnic_update_cmd_producer(काष्ठा qlcnic_host_tx_ring *);

/* Functions from qlcnic_ethtool.c */
पूर्णांक qlcnic_check_loopback_buff(अचिन्हित अक्षर *, u8 []);
पूर्णांक qlcnic_करो_lb_test(काष्ठा qlcnic_adapter *, u8);

/* Functions from qlcnic_मुख्य.c */
पूर्णांक qlcnic_reset_context(काष्ठा qlcnic_adapter *);
व्योम qlcnic_diag_मुक्त_res(काष्ठा net_device *netdev, पूर्णांक);
पूर्णांक qlcnic_diag_alloc_res(काष्ठा net_device *netdev, पूर्णांक);
netdev_tx_t qlcnic_xmit_frame(काष्ठा sk_buff *, काष्ठा net_device *);
व्योम qlcnic_set_tx_ring_count(काष्ठा qlcnic_adapter *, u8);
व्योम qlcnic_set_sds_ring_count(काष्ठा qlcnic_adapter *, u8);
पूर्णांक qlcnic_setup_rings(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_validate_rings(काष्ठा qlcnic_adapter *, __u32, पूर्णांक);
व्योम qlcnic_alloc_lb_filters_mem(काष्ठा qlcnic_adapter *adapter);
पूर्णांक qlcnic_enable_msix(काष्ठा qlcnic_adapter *, u32);
व्योम qlcnic_set_drv_version(काष्ठा qlcnic_adapter *);

/*  eSwitch management functions */
पूर्णांक qlcnic_config_चयन_port(काष्ठा qlcnic_adapter *,
				काष्ठा qlcnic_esw_func_cfg *);

पूर्णांक qlcnic_get_eचयन_port_config(काष्ठा qlcnic_adapter *,
				काष्ठा qlcnic_esw_func_cfg *);
पूर्णांक qlcnic_config_port_mirroring(काष्ठा qlcnic_adapter *, u8, u8, u8);
पूर्णांक qlcnic_get_port_stats(काष्ठा qlcnic_adapter *, स्थिर u8, स्थिर u8,
					काष्ठा __qlcnic_esw_statistics *);
पूर्णांक qlcnic_get_eचयन_stats(काष्ठा qlcnic_adapter *, स्थिर u8, u8,
					काष्ठा __qlcnic_esw_statistics *);
पूर्णांक qlcnic_clear_esw_stats(काष्ठा qlcnic_adapter *adapter, u8, u8, u8);
पूर्णांक qlcnic_get_mac_stats(काष्ठा qlcnic_adapter *, काष्ठा qlcnic_mac_statistics *);

व्योम qlcnic_मुक्त_mbx_args(काष्ठा qlcnic_cmd_args *cmd);

पूर्णांक qlcnic_alloc_sds_rings(काष्ठा qlcnic_recv_context *, पूर्णांक);
व्योम qlcnic_मुक्त_sds_rings(काष्ठा qlcnic_recv_context *);
व्योम qlcnic_advert_link_change(काष्ठा qlcnic_adapter *, पूर्णांक);
व्योम qlcnic_मुक्त_tx_rings(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_alloc_tx_rings(काष्ठा qlcnic_adapter *, काष्ठा net_device *);
व्योम qlcnic_dump_mbx(काष्ठा qlcnic_adapter *, काष्ठा qlcnic_cmd_args *);

व्योम qlcnic_create_sysfs_entries(काष्ठा qlcnic_adapter *adapter);
व्योम qlcnic_हटाओ_sysfs_entries(काष्ठा qlcnic_adapter *adapter);
व्योम qlcnic_82xx_add_sysfs(काष्ठा qlcnic_adapter *adapter);
व्योम qlcnic_82xx_हटाओ_sysfs(काष्ठा qlcnic_adapter *adapter);

पूर्णांक qlcnicvf_config_bridged_mode(काष्ठा qlcnic_adapter *, u32);
पूर्णांक qlcnicvf_config_led(काष्ठा qlcnic_adapter *, u32, u32);
व्योम qlcnic_set_vlan_config(काष्ठा qlcnic_adapter *,
			    काष्ठा qlcnic_esw_func_cfg *);
व्योम qlcnic_set_eचयन_port_features(काष्ठा qlcnic_adapter *,
				      काष्ठा qlcnic_esw_func_cfg *);
पूर्णांक qlcnic_setup_tss_rss_पूर्णांकr(काष्ठा qlcnic_adapter  *);
व्योम qlcnic_करोwn(काष्ठा qlcnic_adapter *, काष्ठा net_device *);
पूर्णांक qlcnic_up(काष्ठा qlcnic_adapter *, काष्ठा net_device *);
व्योम __qlcnic_करोwn(काष्ठा qlcnic_adapter *, काष्ठा net_device *);
व्योम qlcnic_detach(काष्ठा qlcnic_adapter *);
व्योम qlcnic_tearकरोwn_पूर्णांकr(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_attach(काष्ठा qlcnic_adapter *);
पूर्णांक __qlcnic_up(काष्ठा qlcnic_adapter *, काष्ठा net_device *);
व्योम qlcnic_restore_indev_addr(काष्ठा net_device *, अचिन्हित दीर्घ);

पूर्णांक qlcnic_check_temp(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_init_pci_info(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_set_शेष_offload_settings(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_reset_npar_config(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_set_eचयन_port_config(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_set_vxlan_port(काष्ठा qlcnic_adapter *adapter, u16 port);
पूर्णांक qlcnic_set_vxlan_parsing(काष्ठा qlcnic_adapter *adapter, u16 port);
पूर्णांक qlcnic_83xx_configure_opmode(काष्ठा qlcnic_adapter *adapter);
पूर्णांक qlcnic_पढ़ो_mac_addr(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_setup_netdev(काष्ठा qlcnic_adapter *, काष्ठा net_device *, पूर्णांक);
व्योम qlcnic_set_netdev_features(काष्ठा qlcnic_adapter *,
				काष्ठा qlcnic_esw_func_cfg *);
व्योम qlcnic_sriov_vf_set_multi(काष्ठा net_device *);
पूर्णांक qlcnic_is_valid_nic_func(काष्ठा qlcnic_adapter *, u8);
पूर्णांक qlcnic_get_pci_func_type(काष्ठा qlcnic_adapter *, u16, u16 *, u16 *,
			     u16 *);

/*
 * QLOGIC Board inक्रमmation
 */

#घोषणा QLCNIC_MAX_BOARD_NAME_LEN 100
काष्ठा qlcnic_board_info अणु
	अचिन्हित लघु  venकरोr;
	अचिन्हित लघु  device;
	अचिन्हित लघु  sub_venकरोr;
	अचिन्हित लघु  sub_device;
	अक्षर लघु_name[QLCNIC_MAX_BOARD_NAME_LEN];
पूर्ण;

अटल अंतरभूत u32 qlcnic_tx_avail(काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	अगर (likely(tx_ring->producer < tx_ring->sw_consumer))
		वापस tx_ring->sw_consumer - tx_ring->producer;
	अन्यथा
		वापस tx_ring->sw_consumer + tx_ring->num_desc -
				tx_ring->producer;
पूर्ण

काष्ठा qlcnic_nic_ढाँचा अणु
	पूर्णांक (*config_bridged_mode) (काष्ठा qlcnic_adapter *, u32);
	पूर्णांक (*config_led) (काष्ठा qlcnic_adapter *, u32, u32);
	पूर्णांक (*start_firmware) (काष्ठा qlcnic_adapter *);
	पूर्णांक (*init_driver) (काष्ठा qlcnic_adapter *);
	व्योम (*request_reset) (काष्ठा qlcnic_adapter *, u32);
	व्योम (*cancel_idc_work) (काष्ठा qlcnic_adapter *);
	पूर्णांक (*napi_add)(काष्ठा qlcnic_adapter *, काष्ठा net_device *);
	व्योम (*napi_del)(काष्ठा qlcnic_adapter *);
	व्योम (*config_ipaddr)(काष्ठा qlcnic_adapter *, __be32, पूर्णांक);
	irqवापस_t (*clear_legacy_पूर्णांकr)(काष्ठा qlcnic_adapter *);
	पूर्णांक (*shutकरोwn)(काष्ठा pci_dev *);
	पूर्णांक (*resume)(काष्ठा qlcnic_adapter *);
पूर्ण;

काष्ठा qlcnic_mbx_ops अणु
	पूर्णांक (*enqueue_cmd) (काष्ठा qlcnic_adapter *,
			    काष्ठा qlcnic_cmd_args *, अचिन्हित दीर्घ *);
	व्योम (*dequeue_cmd) (काष्ठा qlcnic_adapter *, काष्ठा qlcnic_cmd_args *);
	व्योम (*decode_resp) (काष्ठा qlcnic_adapter *, काष्ठा qlcnic_cmd_args *);
	व्योम (*encode_cmd) (काष्ठा qlcnic_adapter *, काष्ठा qlcnic_cmd_args *);
	व्योम (*nofity_fw) (काष्ठा qlcnic_adapter *, u8);
पूर्ण;

पूर्णांक qlcnic_83xx_init_mailbox_work(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_detach_mailbox_work(काष्ठा qlcnic_adapter *);
व्योम qlcnic_83xx_reinit_mbx_work(काष्ठा qlcnic_mailbox *mbx);
व्योम qlcnic_83xx_मुक्त_mailbox(काष्ठा qlcnic_mailbox *mbx);
व्योम qlcnic_update_stats(काष्ठा qlcnic_adapter *);

/* Adapter hardware असलtraction */
काष्ठा qlcnic_hardware_ops अणु
	व्योम (*पढ़ो_crb) (काष्ठा qlcnic_adapter *, अक्षर *, loff_t, माप_प्रकार);
	व्योम (*ग_लिखो_crb) (काष्ठा qlcnic_adapter *, अक्षर *, loff_t, माप_प्रकार);
	पूर्णांक (*पढ़ो_reg) (काष्ठा qlcnic_adapter *, uदीर्घ, पूर्णांक *);
	पूर्णांक (*ग_लिखो_reg) (काष्ठा qlcnic_adapter *, uदीर्घ, u32);
	व्योम (*get_ocm_win) (काष्ठा qlcnic_hardware_context *);
	पूर्णांक (*get_mac_address) (काष्ठा qlcnic_adapter *, u8 *, u8);
	पूर्णांक (*setup_पूर्णांकr) (काष्ठा qlcnic_adapter *);
	पूर्णांक (*alloc_mbx_args)(काष्ठा qlcnic_cmd_args *,
			      काष्ठा qlcnic_adapter *, u32);
	पूर्णांक (*mbx_cmd) (काष्ठा qlcnic_adapter *, काष्ठा qlcnic_cmd_args *);
	व्योम (*get_func_no) (काष्ठा qlcnic_adapter *);
	पूर्णांक (*api_lock) (काष्ठा qlcnic_adapter *);
	व्योम (*api_unlock) (काष्ठा qlcnic_adapter *);
	व्योम (*add_sysfs) (काष्ठा qlcnic_adapter *);
	व्योम (*हटाओ_sysfs) (काष्ठा qlcnic_adapter *);
	व्योम (*process_lb_rcv_ring_diag) (काष्ठा qlcnic_host_sds_ring *);
	पूर्णांक (*create_rx_ctx) (काष्ठा qlcnic_adapter *);
	पूर्णांक (*create_tx_ctx) (काष्ठा qlcnic_adapter *,
	काष्ठा qlcnic_host_tx_ring *, पूर्णांक);
	व्योम (*del_rx_ctx) (काष्ठा qlcnic_adapter *);
	व्योम (*del_tx_ctx) (काष्ठा qlcnic_adapter *,
			    काष्ठा qlcnic_host_tx_ring *);
	पूर्णांक (*setup_link_event) (काष्ठा qlcnic_adapter *, पूर्णांक);
	पूर्णांक (*get_nic_info) (काष्ठा qlcnic_adapter *, काष्ठा qlcnic_info *, u8);
	पूर्णांक (*get_pci_info) (काष्ठा qlcnic_adapter *, काष्ठा qlcnic_pci_info *);
	पूर्णांक (*set_nic_info) (काष्ठा qlcnic_adapter *, काष्ठा qlcnic_info *);
	पूर्णांक (*change_macvlan) (काष्ठा qlcnic_adapter *, u8*, u16, u8);
	व्योम (*napi_enable) (काष्ठा qlcnic_adapter *);
	व्योम (*napi_disable) (काष्ठा qlcnic_adapter *);
	पूर्णांक (*config_पूर्णांकr_coal) (काष्ठा qlcnic_adapter *,
				 काष्ठा ethtool_coalesce *);
	पूर्णांक (*config_rss) (काष्ठा qlcnic_adapter *, पूर्णांक);
	पूर्णांक (*config_hw_lro) (काष्ठा qlcnic_adapter *, पूर्णांक);
	पूर्णांक (*config_loopback) (काष्ठा qlcnic_adapter *, u8);
	पूर्णांक (*clear_loopback) (काष्ठा qlcnic_adapter *, u8);
	पूर्णांक (*config_promisc_mode) (काष्ठा qlcnic_adapter *, u32);
	व्योम (*change_l2_filter)(काष्ठा qlcnic_adapter *adapter, u64 *addr,
				 u16 vlan, काष्ठा qlcnic_host_tx_ring *tx_ring);
	पूर्णांक (*get_board_info) (काष्ठा qlcnic_adapter *);
	व्योम (*set_mac_filter_count) (काष्ठा qlcnic_adapter *);
	व्योम (*मुक्त_mac_list) (काष्ठा qlcnic_adapter *);
	पूर्णांक (*पढ़ो_phys_port_id) (काष्ठा qlcnic_adapter *);
	pci_ers_result_t (*io_error_detected) (काष्ठा pci_dev *,
					       pci_channel_state_t);
	pci_ers_result_t (*io_slot_reset) (काष्ठा pci_dev *);
	व्योम (*io_resume) (काष्ठा pci_dev *);
	व्योम (*get_beacon_state)(काष्ठा qlcnic_adapter *);
	व्योम (*enable_sds_पूर्णांकr) (काष्ठा qlcnic_adapter *,
				 काष्ठा qlcnic_host_sds_ring *);
	व्योम (*disable_sds_पूर्णांकr) (काष्ठा qlcnic_adapter *,
				  काष्ठा qlcnic_host_sds_ring *);
	व्योम (*enable_tx_पूर्णांकr) (काष्ठा qlcnic_adapter *,
				काष्ठा qlcnic_host_tx_ring *);
	व्योम (*disable_tx_पूर्णांकr) (काष्ठा qlcnic_adapter *,
				 काष्ठा qlcnic_host_tx_ring *);
	u32 (*get_saved_state)(व्योम *, u32);
	व्योम (*set_saved_state)(व्योम *, u32, u32);
	व्योम (*cache_पंचांगpl_hdr_values)(काष्ठा qlcnic_fw_dump *);
	u32 (*get_cap_size)(व्योम *, पूर्णांक);
	व्योम (*set_sys_info)(व्योम *, पूर्णांक, u32);
	व्योम (*store_cap_mask)(व्योम *, u32);
	bool (*encap_rx_offload) (काष्ठा qlcnic_adapter *adapter);
	bool (*encap_tx_offload) (काष्ठा qlcnic_adapter *adapter);
पूर्ण;

बाह्य काष्ठा qlcnic_nic_ढाँचा qlcnic_vf_ops;

अटल अंतरभूत bool qlcnic_83xx_encap_tx_offload(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस adapter->ahw->extra_capability[0] &
	       QLCNIC_83XX_FW_CAPAB_ENCAP_TX_OFFLOAD;
पूर्ण

अटल अंतरभूत bool qlcnic_83xx_encap_rx_offload(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस adapter->ahw->extra_capability[0] &
	       QLCNIC_83XX_FW_CAPAB_ENCAP_RX_OFFLOAD;
पूर्ण

अटल अंतरभूत bool qlcnic_82xx_encap_tx_offload(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool qlcnic_82xx_encap_rx_offload(काष्ठा qlcnic_adapter *adapter)
अणु
        वापस false;
पूर्ण

अटल अंतरभूत bool qlcnic_encap_rx_offload(काष्ठा qlcnic_adapter *adapter)
अणु
        वापस adapter->ahw->hw_ops->encap_rx_offload(adapter);
पूर्ण

अटल अंतरभूत bool qlcnic_encap_tx_offload(काष्ठा qlcnic_adapter *adapter)
अणु
        वापस adapter->ahw->hw_ops->encap_tx_offload(adapter);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_start_firmware(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस adapter->nic_ops->start_firmware(adapter);
पूर्ण

अटल अंतरभूत व्योम qlcnic_पढ़ो_crb(काष्ठा qlcnic_adapter *adapter, अक्षर *buf,
				   loff_t offset, माप_प्रकार size)
अणु
	adapter->ahw->hw_ops->पढ़ो_crb(adapter, buf, offset, size);
पूर्ण

अटल अंतरभूत व्योम qlcnic_ग_लिखो_crb(काष्ठा qlcnic_adapter *adapter, अक्षर *buf,
				    loff_t offset, माप_प्रकार size)
अणु
	adapter->ahw->hw_ops->ग_लिखो_crb(adapter, buf, offset, size);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_get_mac_address(काष्ठा qlcnic_adapter *adapter,
					 u8 *mac, u8 function)
अणु
	वापस adapter->ahw->hw_ops->get_mac_address(adapter, mac, function);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_setup_पूर्णांकr(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस adapter->ahw->hw_ops->setup_पूर्णांकr(adapter);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_alloc_mbx_args(काष्ठा qlcnic_cmd_args *mbx,
					काष्ठा qlcnic_adapter *adapter, u32 arg)
अणु
	वापस adapter->ahw->hw_ops->alloc_mbx_args(mbx, adapter, arg);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_issue_cmd(काष्ठा qlcnic_adapter *adapter,
				   काष्ठा qlcnic_cmd_args *cmd)
अणु
	अगर (adapter->ahw->hw_ops->mbx_cmd)
		वापस adapter->ahw->hw_ops->mbx_cmd(adapter, cmd);

	वापस -EIO;
पूर्ण

अटल अंतरभूत व्योम qlcnic_get_func_no(काष्ठा qlcnic_adapter *adapter)
अणु
	adapter->ahw->hw_ops->get_func_no(adapter);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_api_lock(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस adapter->ahw->hw_ops->api_lock(adapter);
पूर्ण

अटल अंतरभूत व्योम qlcnic_api_unlock(काष्ठा qlcnic_adapter *adapter)
अणु
	adapter->ahw->hw_ops->api_unlock(adapter);
पूर्ण

अटल अंतरभूत व्योम qlcnic_add_sysfs(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (adapter->ahw->hw_ops->add_sysfs)
		adapter->ahw->hw_ops->add_sysfs(adapter);
पूर्ण

अटल अंतरभूत व्योम qlcnic_हटाओ_sysfs(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (adapter->ahw->hw_ops->हटाओ_sysfs)
		adapter->ahw->hw_ops->हटाओ_sysfs(adapter);
पूर्ण

अटल अंतरभूत व्योम
qlcnic_process_rcv_ring_diag(काष्ठा qlcnic_host_sds_ring *sds_ring)
अणु
	sds_ring->adapter->ahw->hw_ops->process_lb_rcv_ring_diag(sds_ring);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_fw_cmd_create_rx_ctx(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस adapter->ahw->hw_ops->create_rx_ctx(adapter);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_fw_cmd_create_tx_ctx(काष्ठा qlcnic_adapter *adapter,
					      काष्ठा qlcnic_host_tx_ring *ptr,
					      पूर्णांक ring)
अणु
	वापस adapter->ahw->hw_ops->create_tx_ctx(adapter, ptr, ring);
पूर्ण

अटल अंतरभूत व्योम qlcnic_fw_cmd_del_rx_ctx(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस adapter->ahw->hw_ops->del_rx_ctx(adapter);
पूर्ण

अटल अंतरभूत व्योम qlcnic_fw_cmd_del_tx_ctx(काष्ठा qlcnic_adapter *adapter,
					    काष्ठा qlcnic_host_tx_ring *ptr)
अणु
	वापस adapter->ahw->hw_ops->del_tx_ctx(adapter, ptr);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_linkevent_request(काष्ठा qlcnic_adapter *adapter,
					   पूर्णांक enable)
अणु
	वापस adapter->ahw->hw_ops->setup_link_event(adapter, enable);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_get_nic_info(काष्ठा qlcnic_adapter *adapter,
				      काष्ठा qlcnic_info *info, u8 id)
अणु
	वापस adapter->ahw->hw_ops->get_nic_info(adapter, info, id);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_get_pci_info(काष्ठा qlcnic_adapter *adapter,
				      काष्ठा qlcnic_pci_info *info)
अणु
	वापस adapter->ahw->hw_ops->get_pci_info(adapter, info);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_set_nic_info(काष्ठा qlcnic_adapter *adapter,
				      काष्ठा qlcnic_info *info)
अणु
	वापस adapter->ahw->hw_ops->set_nic_info(adapter, info);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_sre_macaddr_change(काष्ठा qlcnic_adapter *adapter,
					    u8 *addr, u16 id, u8 cmd)
अणु
	वापस adapter->ahw->hw_ops->change_macvlan(adapter, addr, id, cmd);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_napi_add(काष्ठा qlcnic_adapter *adapter,
				  काष्ठा net_device *netdev)
अणु
	वापस adapter->nic_ops->napi_add(adapter, netdev);
पूर्ण

अटल अंतरभूत व्योम qlcnic_napi_del(काष्ठा qlcnic_adapter *adapter)
अणु
	adapter->nic_ops->napi_del(adapter);
पूर्ण

अटल अंतरभूत व्योम qlcnic_napi_enable(काष्ठा qlcnic_adapter *adapter)
अणु
	adapter->ahw->hw_ops->napi_enable(adapter);
पूर्ण

अटल अंतरभूत पूर्णांक __qlcnic_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qlcnic_adapter *adapter = pci_get_drvdata(pdev);

	वापस adapter->nic_ops->shutकरोwn(pdev);
पूर्ण

अटल अंतरभूत पूर्णांक __qlcnic_resume(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस adapter->nic_ops->resume(adapter);
पूर्ण

अटल अंतरभूत व्योम qlcnic_napi_disable(काष्ठा qlcnic_adapter *adapter)
अणु
	adapter->ahw->hw_ops->napi_disable(adapter);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_config_पूर्णांकr_coalesce(काष्ठा qlcnic_adapter *adapter,
					      काष्ठा ethtool_coalesce *ethcoal)
अणु
	वापस adapter->ahw->hw_ops->config_पूर्णांकr_coal(adapter, ethcoal);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_config_rss(काष्ठा qlcnic_adapter *adapter, पूर्णांक enable)
अणु
	वापस adapter->ahw->hw_ops->config_rss(adapter, enable);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_config_hw_lro(काष्ठा qlcnic_adapter *adapter,
				       पूर्णांक enable)
अणु
	वापस adapter->ahw->hw_ops->config_hw_lro(adapter, enable);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_set_lb_mode(काष्ठा qlcnic_adapter *adapter, u8 mode)
अणु
	वापस adapter->ahw->hw_ops->config_loopback(adapter, mode);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_clear_lb_mode(काष्ठा qlcnic_adapter *adapter, u8 mode)
अणु
	वापस adapter->ahw->hw_ops->clear_loopback(adapter, mode);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_nic_set_promisc(काष्ठा qlcnic_adapter *adapter,
					 u32 mode)
अणु
	वापस adapter->ahw->hw_ops->config_promisc_mode(adapter, mode);
पूर्ण

अटल अंतरभूत व्योम qlcnic_change_filter(काष्ठा qlcnic_adapter *adapter,
					u64 *addr, u16 vlan,
					काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	adapter->ahw->hw_ops->change_l2_filter(adapter, addr, vlan, tx_ring);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_get_board_info(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस adapter->ahw->hw_ops->get_board_info(adapter);
पूर्ण

अटल अंतरभूत व्योम qlcnic_मुक्त_mac_list(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस adapter->ahw->hw_ops->मुक्त_mac_list(adapter);
पूर्ण

अटल अंतरभूत व्योम qlcnic_set_mac_filter_count(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (adapter->ahw->hw_ops->set_mac_filter_count)
		adapter->ahw->hw_ops->set_mac_filter_count(adapter);
पूर्ण

अटल अंतरभूत व्योम qlcnic_get_beacon_state(काष्ठा qlcnic_adapter *adapter)
अणु
	adapter->ahw->hw_ops->get_beacon_state(adapter);
पूर्ण

अटल अंतरभूत व्योम qlcnic_पढ़ो_phys_port_id(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (adapter->ahw->hw_ops->पढ़ो_phys_port_id)
		adapter->ahw->hw_ops->पढ़ो_phys_port_id(adapter);
पूर्ण

अटल अंतरभूत u32 qlcnic_get_saved_state(काष्ठा qlcnic_adapter *adapter,
					 व्योम *t_hdr, u32 index)
अणु
	वापस adapter->ahw->hw_ops->get_saved_state(t_hdr, index);
पूर्ण

अटल अंतरभूत व्योम qlcnic_set_saved_state(काष्ठा qlcnic_adapter *adapter,
					  व्योम *t_hdr, u32 index, u32 value)
अणु
	adapter->ahw->hw_ops->set_saved_state(t_hdr, index, value);
पूर्ण

अटल अंतरभूत व्योम qlcnic_cache_पंचांगpl_hdr_values(काष्ठा qlcnic_adapter *adapter,
						काष्ठा qlcnic_fw_dump *fw_dump)
अणु
	adapter->ahw->hw_ops->cache_पंचांगpl_hdr_values(fw_dump);
पूर्ण

अटल अंतरभूत u32 qlcnic_get_cap_size(काष्ठा qlcnic_adapter *adapter,
				      व्योम *पंचांगpl_hdr, पूर्णांक index)
अणु
	वापस adapter->ahw->hw_ops->get_cap_size(पंचांगpl_hdr, index);
पूर्ण

अटल अंतरभूत व्योम qlcnic_set_sys_info(काष्ठा qlcnic_adapter *adapter,
				       व्योम *पंचांगpl_hdr, पूर्णांक idx, u32 value)
अणु
	adapter->ahw->hw_ops->set_sys_info(पंचांगpl_hdr, idx, value);
पूर्ण

अटल अंतरभूत व्योम qlcnic_store_cap_mask(काष्ठा qlcnic_adapter *adapter,
					 व्योम *पंचांगpl_hdr, u32 mask)
अणु
	adapter->ahw->hw_ops->store_cap_mask(पंचांगpl_hdr, mask);
पूर्ण

अटल अंतरभूत व्योम qlcnic_dev_request_reset(काष्ठा qlcnic_adapter *adapter,
					    u32 key)
अणु
	अगर (adapter->nic_ops->request_reset)
		adapter->nic_ops->request_reset(adapter, key);
पूर्ण

अटल अंतरभूत व्योम qlcnic_cancel_idc_work(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (adapter->nic_ops->cancel_idc_work)
		adapter->nic_ops->cancel_idc_work(adapter);
पूर्ण

अटल अंतरभूत irqवापस_t
qlcnic_clear_legacy_पूर्णांकr(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस adapter->nic_ops->clear_legacy_पूर्णांकr(adapter);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_config_led(काष्ठा qlcnic_adapter *adapter, u32 state,
				    u32 rate)
अणु
	वापस adapter->nic_ops->config_led(adapter, state, rate);
पूर्ण

अटल अंतरभूत व्योम qlcnic_config_ipaddr(काष्ठा qlcnic_adapter *adapter,
					__be32 ip, पूर्णांक cmd)
अणु
	adapter->nic_ops->config_ipaddr(adapter, ip, cmd);
पूर्ण

अटल अंतरभूत bool qlcnic_check_multi_tx(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस test_bit(__QLCNIC_MULTI_TX_UNIQUE, &adapter->state);
पूर्ण

अटल अंतरभूत व्योम
qlcnic_82xx_enable_tx_पूर्णांकr(काष्ठा qlcnic_adapter *adapter,
			   काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	अगर (qlcnic_check_multi_tx(adapter) &&
	    !adapter->ahw->diag_test)
		ग_लिखोl(0x0, tx_ring->crb_पूर्णांकr_mask);
पूर्ण

अटल अंतरभूत व्योम
qlcnic_82xx_disable_tx_पूर्णांकr(काष्ठा qlcnic_adapter *adapter,
			    काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	अगर (qlcnic_check_multi_tx(adapter) &&
	    !adapter->ahw->diag_test)
		ग_लिखोl(1, tx_ring->crb_पूर्णांकr_mask);
पूर्ण

अटल अंतरभूत व्योम
qlcnic_83xx_enable_tx_पूर्णांकr(काष्ठा qlcnic_adapter *adapter,
			   काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	ग_लिखोl(0, tx_ring->crb_पूर्णांकr_mask);
पूर्ण

अटल अंतरभूत व्योम
qlcnic_83xx_disable_tx_पूर्णांकr(काष्ठा qlcnic_adapter *adapter,
			    काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	ग_लिखोl(1, tx_ring->crb_पूर्णांकr_mask);
पूर्ण

/* Enable MSI-x and INT-x पूर्णांकerrupts */
अटल अंतरभूत व्योम
qlcnic_83xx_enable_sds_पूर्णांकr(काष्ठा qlcnic_adapter *adapter,
			    काष्ठा qlcnic_host_sds_ring *sds_ring)
अणु
	ग_लिखोl(0, sds_ring->crb_पूर्णांकr_mask);
पूर्ण

/* Disable MSI-x and INT-x पूर्णांकerrupts */
अटल अंतरभूत व्योम
qlcnic_83xx_disable_sds_पूर्णांकr(काष्ठा qlcnic_adapter *adapter,
			     काष्ठा qlcnic_host_sds_ring *sds_ring)
अणु
	ग_लिखोl(1, sds_ring->crb_पूर्णांकr_mask);
पूर्ण

अटल अंतरभूत व्योम qlcnic_disable_multi_tx(काष्ठा qlcnic_adapter *adapter)
अणु
	test_and_clear_bit(__QLCNIC_MULTI_TX_UNIQUE, &adapter->state);
	adapter->drv_tx_rings = QLCNIC_SINGLE_RING;
पूर्ण

/* When operating in a muti tx mode, driver needs to ग_लिखो 0x1
 * to src रेजिस्टर, instead of 0x0 to disable receiving पूर्णांकerrupt.
 */
अटल अंतरभूत व्योम
qlcnic_82xx_disable_sds_पूर्णांकr(काष्ठा qlcnic_adapter *adapter,
			     काष्ठा qlcnic_host_sds_ring *sds_ring)
अणु
	अगर (qlcnic_check_multi_tx(adapter) &&
	    !adapter->ahw->diag_test &&
	    (adapter->flags & QLCNIC_MSIX_ENABLED))
		ग_लिखोl(0x1, sds_ring->crb_पूर्णांकr_mask);
	अन्यथा
		ग_लिखोl(0, sds_ring->crb_पूर्णांकr_mask);
पूर्ण

अटल अंतरभूत व्योम qlcnic_enable_sds_पूर्णांकr(काष्ठा qlcnic_adapter *adapter,
					  काष्ठा qlcnic_host_sds_ring *sds_ring)
अणु
	अगर (adapter->ahw->hw_ops->enable_sds_पूर्णांकr)
		adapter->ahw->hw_ops->enable_sds_पूर्णांकr(adapter, sds_ring);
पूर्ण

अटल अंतरभूत व्योम
qlcnic_disable_sds_पूर्णांकr(काष्ठा qlcnic_adapter *adapter,
			काष्ठा qlcnic_host_sds_ring *sds_ring)
अणु
	अगर (adapter->ahw->hw_ops->disable_sds_पूर्णांकr)
		adapter->ahw->hw_ops->disable_sds_पूर्णांकr(adapter, sds_ring);
पूर्ण

अटल अंतरभूत व्योम qlcnic_enable_tx_पूर्णांकr(काष्ठा qlcnic_adapter *adapter,
					 काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	अगर (adapter->ahw->hw_ops->enable_tx_पूर्णांकr)
		adapter->ahw->hw_ops->enable_tx_पूर्णांकr(adapter, tx_ring);
पूर्ण

अटल अंतरभूत व्योम qlcnic_disable_tx_पूर्णांकr(काष्ठा qlcnic_adapter *adapter,
					  काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	अगर (adapter->ahw->hw_ops->disable_tx_पूर्णांकr)
		adapter->ahw->hw_ops->disable_tx_पूर्णांकr(adapter, tx_ring);
पूर्ण

/* When operating in a muti tx mode, driver needs to ग_लिखो 0x0
 * to src रेजिस्टर, instead of 0x1 to enable receiving पूर्णांकerrupts.
 */
अटल अंतरभूत व्योम
qlcnic_82xx_enable_sds_पूर्णांकr(काष्ठा qlcnic_adapter *adapter,
			    काष्ठा qlcnic_host_sds_ring *sds_ring)
अणु
	अगर (qlcnic_check_multi_tx(adapter) &&
	    !adapter->ahw->diag_test &&
	    (adapter->flags & QLCNIC_MSIX_ENABLED))
		ग_लिखोl(0, sds_ring->crb_पूर्णांकr_mask);
	अन्यथा
		ग_लिखोl(0x1, sds_ring->crb_पूर्णांकr_mask);

	अगर (!QLCNIC_IS_MSI_FAMILY(adapter))
		ग_लिखोl(0xfbff, adapter->tgt_mask_reg);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_get_diag_lock(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस test_and_set_bit(__QLCNIC_DIAG_MODE, &adapter->state);
पूर्ण

अटल अंतरभूत व्योम qlcnic_release_diag_lock(काष्ठा qlcnic_adapter *adapter)
अणु
	clear_bit(__QLCNIC_DIAG_MODE, &adapter->state);
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_check_diag_status(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस test_bit(__QLCNIC_DIAG_MODE, &adapter->state);
पूर्ण

बाह्य स्थिर काष्ठा ethtool_ops qlcnic_sriov_vf_ethtool_ops;
बाह्य स्थिर काष्ठा ethtool_ops qlcnic_ethtool_ops;
बाह्य स्थिर काष्ठा ethtool_ops qlcnic_ethtool_failed_ops;

#घोषणा QLCDB(adapter, lvl, _fmt, _args...) करो अणु	\
	अगर (NETIF_MSG_##lvl & adapter->ahw->msg_enable)	\
		prपूर्णांकk(KERN_INFO "%s: %s: " _fmt,	\
			 dev_name(&adapter->pdev->dev),	\
			__func__, ##_args);		\
	पूर्ण जबतक (0)

#घोषणा PCI_DEVICE_ID_QLOGIC_QLE824X		0x8020
#घोषणा PCI_DEVICE_ID_QLOGIC_QLE834X		0x8030
#घोषणा PCI_DEVICE_ID_QLOGIC_VF_QLE834X	0x8430
#घोषणा PCI_DEVICE_ID_QLOGIC_QLE8830		0x8830
#घोषणा PCI_DEVICE_ID_QLOGIC_VF_QLE8C30		0x8C30
#घोषणा PCI_DEVICE_ID_QLOGIC_QLE844X		0x8040
#घोषणा PCI_DEVICE_ID_QLOGIC_VF_QLE844X	0x8440

अटल अंतरभूत bool qlcnic_82xx_check(काष्ठा qlcnic_adapter *adapter)
अणु
	अचिन्हित लघु device = adapter->pdev->device;
	वापस (device == PCI_DEVICE_ID_QLOGIC_QLE824X) ? true : false;
पूर्ण

अटल अंतरभूत bool qlcnic_84xx_check(काष्ठा qlcnic_adapter *adapter)
अणु
	अचिन्हित लघु device = adapter->pdev->device;

	वापस ((device == PCI_DEVICE_ID_QLOGIC_QLE844X) ||
		(device == PCI_DEVICE_ID_QLOGIC_VF_QLE844X)) ? true : false;
पूर्ण

अटल अंतरभूत bool qlcnic_83xx_check(काष्ठा qlcnic_adapter *adapter)
अणु
	अचिन्हित लघु device = adapter->pdev->device;
	bool status;

	status = ((device == PCI_DEVICE_ID_QLOGIC_QLE834X) ||
		  (device == PCI_DEVICE_ID_QLOGIC_QLE8830) ||
		  (device == PCI_DEVICE_ID_QLOGIC_QLE844X) ||
		  (device == PCI_DEVICE_ID_QLOGIC_VF_QLE844X) ||
		  (device == PCI_DEVICE_ID_QLOGIC_VF_QLE834X) ||
		  (device == PCI_DEVICE_ID_QLOGIC_VF_QLE8C30)) ? true : false;

	वापस status;
पूर्ण

अटल अंतरभूत bool qlcnic_sriov_pf_check(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस (adapter->ahw->op_mode == QLCNIC_SRIOV_PF_FUNC) ? true : false;
पूर्ण

अटल अंतरभूत bool qlcnic_sriov_vf_check(काष्ठा qlcnic_adapter *adapter)
अणु
	अचिन्हित लघु device = adapter->pdev->device;
	bool status;

	status = ((device == PCI_DEVICE_ID_QLOGIC_VF_QLE834X) ||
		  (device == PCI_DEVICE_ID_QLOGIC_VF_QLE844X) ||
		  (device == PCI_DEVICE_ID_QLOGIC_VF_QLE8C30)) ? true : false;

	वापस status;
पूर्ण

अटल अंतरभूत bool qlcnic_83xx_pf_check(काष्ठा qlcnic_adapter *adapter)
अणु
	अचिन्हित लघु device = adapter->pdev->device;

	वापस (device == PCI_DEVICE_ID_QLOGIC_QLE834X) ? true : false;
पूर्ण

अटल अंतरभूत bool qlcnic_83xx_vf_check(काष्ठा qlcnic_adapter *adapter)
अणु
	अचिन्हित लघु device = adapter->pdev->device;

	वापस ((device == PCI_DEVICE_ID_QLOGIC_VF_QLE834X) ||
		(device == PCI_DEVICE_ID_QLOGIC_VF_QLE8C30)) ? true : false;
पूर्ण

अटल अंतरभूत bool qlcnic_sriov_check(काष्ठा qlcnic_adapter *adapter)
अणु
	bool status;

	status = (qlcnic_sriov_pf_check(adapter) ||
		  qlcnic_sriov_vf_check(adapter)) ? true : false;

	वापस status;
पूर्ण

अटल अंतरभूत u32 qlcnic_get_vnic_func_count(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (qlcnic_84xx_check(adapter))
		वापस QLC_84XX_VNIC_COUNT;
	अन्यथा
		वापस QLC_DEFAULT_VNIC_COUNT;
पूर्ण

अटल अंतरभूत व्योम qlcnic_swap32_buffer(u32 *buffer, पूर्णांक count)
अणु
#अगर defined(__BIG_ENDIAN)
	u32 *पंचांगp = buffer;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		*पंचांगp = swab32(*पंचांगp);
		पंचांगp++;
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_QLCNIC_HWMON
व्योम qlcnic_रेजिस्टर_hwmon_dev(काष्ठा qlcnic_adapter *);
व्योम qlcnic_unरेजिस्टर_hwmon_dev(काष्ठा qlcnic_adapter *);
#अन्यथा
अटल अंतरभूत व्योम qlcnic_रेजिस्टर_hwmon_dev(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस;
पूर्ण
अटल अंतरभूत व्योम qlcnic_unरेजिस्टर_hwmon_dev(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर				/* __QLCNIC_H_ */
