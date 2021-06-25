<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2006 Intel Corporation. */

/*
 *	e100.c: Intel(R) PRO/100 ethernet driver
 *
 *	(Re)written 2003 by scott.feldman@पूर्णांकel.com.  Based loosely on
 *	original e100 driver, but better described as a munging of
 *	e100, e1000, eepro100, tg3, 8139cp, and other drivers.
 *
 *	References:
 *		Intel 8255x 10/100 Mbps Ethernet Controller Family,
 *		Open Source Software Developers Manual,
 *		http://sourceक्रमge.net/projects/e1000
 *
 *
 *	                      Theory of Operation
 *
 *	I.   General
 *
 *	The driver supports Intel(R) 10/100 Mbps PCI Fast Ethernet
 *	controller family, which includes the 82557, 82558, 82559, 82550,
 *	82551, and 82562 devices.  82558 and greater controllers
 *	पूर्णांकegrate the Intel 82555 PHY.  The controllers are used in
 *	server and client network पूर्णांकerface cards, as well as in
 *	LAN-On-Motherboard (LOM), CardBus, MiniPCI, and ICHx
 *	configurations.  8255x supports a 32-bit linear addressing
 *	mode and operates at 33Mhz PCI घड़ी rate.
 *
 *	II.  Driver Operation
 *
 *	Memory-mapped mode is used exclusively to access the device's
 *	shared-memory काष्ठाure, the Control/Status Registers (CSR). All
 *	setup, configuration, and control of the device, including queuing
 *	of Tx, Rx, and configuration commands is through the CSR.
 *	cmd_lock serializes accesses to the CSR command रेजिस्टर.  cb_lock
 *	protects the shared Command Block List (CBL).
 *
 *	8255x is highly MII-compliant and all access to the PHY go
 *	through the Management Data Interface (MDI).  Consequently, the
 *	driver leverages the mii.c library shared with other MII-compliant
 *	devices.
 *
 *	Big- and Little-Endian byte order as well as 32- and 64-bit
 *	archs are supported.  Weak-ordered memory and non-cache-coherent
 *	archs are supported.
 *
 *	III. Transmit
 *
 *	A Tx skb is mapped and hangs off of a TCB.  TCBs are linked
 *	together in a fixed-size ring (CBL) thus क्रमming the flexible mode
 *	memory काष्ठाure.  A TCB marked with the suspend-bit indicates
 *	the end of the ring.  The last TCB processed suspends the
 *	controller, and the controller can be restarted by issue a CU
 *	resume command to जारी from the suspend poपूर्णांक, or a CU start
 *	command to start at a given position in the ring.
 *
 *	Non-Tx commands (config, multicast setup, etc) are linked
 *	पूर्णांकo the CBL ring aदीर्घ with Tx commands.  The common काष्ठाure
 *	used क्रम both Tx and non-Tx commands is the Command Block (CB).
 *
 *	cb_to_use is the next CB to use क्रम queuing a command; cb_to_clean
 *	is the next CB to check क्रम completion; cb_to_send is the first
 *	CB to start on in हाल of a previous failure to resume.  CB clean
 *	up happens in पूर्णांकerrupt context in response to a CU पूर्णांकerrupt.
 *	cbs_avail keeps track of number of मुक्त CB resources available.
 *
 * 	Hardware padding of लघु packets to minimum packet size is
 * 	enabled.  82557 pads with 7Eh, जबतक the later controllers pad
 * 	with 00h.
 *
 *	IV.  Receive
 *
 *	The Receive Frame Area (RFA) comprises a ring of Receive Frame
 *	Descriptors (RFD) + data buffer, thus क्रमming the simplअगरied mode
 *	memory काष्ठाure.  Rx skbs are allocated to contain both the RFD
 *	and the data buffer, but the RFD is pulled off beक्रमe the skb is
 *	indicated.  The data buffer is aligned such that encapsulated
 *	protocol headers are u32-aligned.  Since the RFD is part of the
 *	mapped shared memory, and completion status is contained within
 *	the RFD, the RFD must be dma_sync'ed to मुख्यtain a consistent
 *	view from software and hardware.
 *
 *	In order to keep updates to the RFD link field from colliding with
 *	hardware ग_लिखोs to mark packets complete, we use the feature that
 *	hardware will not ग_लिखो to a size 0 descriptor and mark the previous
 *	packet as end-of-list (EL).   After updating the link, we हटाओ EL
 *	and only then restore the size such that hardware may use the
 *	previous-to-end RFD.
 *
 *	Under typical operation, the  receive unit (RU) is start once,
 *	and the controller happily fills RFDs as frames arrive.  If
 *	replacement RFDs cannot be allocated, or the RU goes non-active,
 *	the RU must be restarted.  Frame arrival generates an पूर्णांकerrupt,
 *	and Rx indication and re-allocation happen in the same context,
 *	thereक्रमe no locking is required.  A software-generated पूर्णांकerrupt
 *	is generated from the watchकरोg to recover from a failed allocation
 *	scenario where all Rx resources have been indicated and none re-
 *	placed.
 *
 *	V.   Miscellaneous
 *
 * 	VLAN offloading of tagging, stripping and filtering is not
 * 	supported, but driver will accommodate the extra 4-byte VLAN tag
 * 	क्रम processing by upper layers.  Tx/Rx Checksum offloading is not
 * 	supported.  Tx Scatter/Gather is not supported.  Jumbo Frames is
 * 	not supported (hardware limitation).
 *
 * 	MagicPacket(पंचांग) WoL support is enabled/disabled via ethtool.
 *
 * 	Thanks to JC (jchapman@katalix.com) क्रम helping with
 * 	testing/troubleshooting the development driver.
 *
 * 	TODO:
 * 	o several entry poपूर्णांकs race with dev->बंद
 * 	o check क्रम tx-no-resources/stop Q races with tx clean/wake Q
 *
 *	FIXES:
 * 2005/12/02 - Michael O'Donnell <Michael.ODonnell at stratus करोt com>
 *	- Stratus87247: protect MDI control रेजिस्टर manipulations
 * 2009/06/01 - Andreas Mohr <andi at lisas करोt de>
 *      - add clean lowlevel I/O emulation क्रम cards with MII-lacking PHYs
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/hardirq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mii.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/माला.स>
#समावेश <linux/firmware.h>
#समावेश <linux/rtnetlink.h>
#समावेश <यंत्र/unaligned.h>


#घोषणा DRV_NAME		"e100"
#घोषणा DRV_DESCRIPTION		"Intel(R) PRO/100 Network Driver"
#घोषणा DRV_COPYRIGHT		"Copyright(c) 1999-2006 Intel Corporation"

#घोषणा E100_WATCHDOG_PERIOD	(2 * HZ)
#घोषणा E100_NAPI_WEIGHT	16

#घोषणा FIRMWARE_D101M		"e100/d101m_ucode.bin"
#घोषणा FIRMWARE_D101S		"e100/d101s_ucode.bin"
#घोषणा FIRMWARE_D102E		"e100/d102e_ucode.bin"

MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_AUTHOR(DRV_COPYRIGHT);
MODULE_LICENSE("GPL v2");
MODULE_FIRMWARE(FIRMWARE_D101M);
MODULE_FIRMWARE(FIRMWARE_D101S);
MODULE_FIRMWARE(FIRMWARE_D102E);

अटल पूर्णांक debug = 3;
अटल पूर्णांक eeprom_bad_csum_allow = 0;
अटल पूर्णांक use_io = 0;
module_param(debug, पूर्णांक, 0);
module_param(eeprom_bad_csum_allow, पूर्णांक, 0);
module_param(use_io, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");
MODULE_PARM_DESC(eeprom_bad_csum_allow, "Allow bad eeprom checksums");
MODULE_PARM_DESC(use_io, "Force use of i/o access mode");

#घोषणा INTEL_8255X_ETHERNET_DEVICE(device_id, ich) अणु\
	PCI_VENDOR_ID_INTEL, device_id, PCI_ANY_ID, PCI_ANY_ID, \
	PCI_CLASS_NETWORK_ETHERNET << 8, 0xFFFF00, ich पूर्ण
अटल स्थिर काष्ठा pci_device_id e100_id_table[] = अणु
	INTEL_8255X_ETHERNET_DEVICE(0x1029, 0),
	INTEL_8255X_ETHERNET_DEVICE(0x1030, 0),
	INTEL_8255X_ETHERNET_DEVICE(0x1031, 3),
	INTEL_8255X_ETHERNET_DEVICE(0x1032, 3),
	INTEL_8255X_ETHERNET_DEVICE(0x1033, 3),
	INTEL_8255X_ETHERNET_DEVICE(0x1034, 3),
	INTEL_8255X_ETHERNET_DEVICE(0x1038, 3),
	INTEL_8255X_ETHERNET_DEVICE(0x1039, 4),
	INTEL_8255X_ETHERNET_DEVICE(0x103A, 4),
	INTEL_8255X_ETHERNET_DEVICE(0x103B, 4),
	INTEL_8255X_ETHERNET_DEVICE(0x103C, 4),
	INTEL_8255X_ETHERNET_DEVICE(0x103D, 4),
	INTEL_8255X_ETHERNET_DEVICE(0x103E, 4),
	INTEL_8255X_ETHERNET_DEVICE(0x1050, 5),
	INTEL_8255X_ETHERNET_DEVICE(0x1051, 5),
	INTEL_8255X_ETHERNET_DEVICE(0x1052, 5),
	INTEL_8255X_ETHERNET_DEVICE(0x1053, 5),
	INTEL_8255X_ETHERNET_DEVICE(0x1054, 5),
	INTEL_8255X_ETHERNET_DEVICE(0x1055, 5),
	INTEL_8255X_ETHERNET_DEVICE(0x1056, 5),
	INTEL_8255X_ETHERNET_DEVICE(0x1057, 5),
	INTEL_8255X_ETHERNET_DEVICE(0x1059, 0),
	INTEL_8255X_ETHERNET_DEVICE(0x1064, 6),
	INTEL_8255X_ETHERNET_DEVICE(0x1065, 6),
	INTEL_8255X_ETHERNET_DEVICE(0x1066, 6),
	INTEL_8255X_ETHERNET_DEVICE(0x1067, 6),
	INTEL_8255X_ETHERNET_DEVICE(0x1068, 6),
	INTEL_8255X_ETHERNET_DEVICE(0x1069, 6),
	INTEL_8255X_ETHERNET_DEVICE(0x106A, 6),
	INTEL_8255X_ETHERNET_DEVICE(0x106B, 6),
	INTEL_8255X_ETHERNET_DEVICE(0x1091, 7),
	INTEL_8255X_ETHERNET_DEVICE(0x1092, 7),
	INTEL_8255X_ETHERNET_DEVICE(0x1093, 7),
	INTEL_8255X_ETHERNET_DEVICE(0x1094, 7),
	INTEL_8255X_ETHERNET_DEVICE(0x1095, 7),
	INTEL_8255X_ETHERNET_DEVICE(0x10fe, 7),
	INTEL_8255X_ETHERNET_DEVICE(0x1209, 0),
	INTEL_8255X_ETHERNET_DEVICE(0x1229, 0),
	INTEL_8255X_ETHERNET_DEVICE(0x2449, 2),
	INTEL_8255X_ETHERNET_DEVICE(0x2459, 2),
	INTEL_8255X_ETHERNET_DEVICE(0x245D, 2),
	INTEL_8255X_ETHERNET_DEVICE(0x27DC, 7),
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, e100_id_table);

क्रमागत mac अणु
	mac_82557_D100_A  = 0,
	mac_82557_D100_B  = 1,
	mac_82557_D100_C  = 2,
	mac_82558_D101_A4 = 4,
	mac_82558_D101_B0 = 5,
	mac_82559_D101M   = 8,
	mac_82559_D101S   = 9,
	mac_82550_D102    = 12,
	mac_82550_D102_C  = 13,
	mac_82551_E       = 14,
	mac_82551_F       = 15,
	mac_82551_10      = 16,
	mac_unknown       = 0xFF,
पूर्ण;

क्रमागत phy अणु
	phy_100a     = 0x000003E0,
	phy_100c     = 0x035002A8,
	phy_82555_tx = 0x015002A8,
	phy_nsc_tx   = 0x5C002000,
	phy_82562_et = 0x033002A8,
	phy_82562_em = 0x032002A8,
	phy_82562_ek = 0x031002A8,
	phy_82562_eh = 0x017002A8,
	phy_82552_v  = 0xd061004d,
	phy_unknown  = 0xFFFFFFFF,
पूर्ण;

/* CSR (Control/Status Registers) */
काष्ठा csr अणु
	काष्ठा अणु
		u8 status;
		u8 stat_ack;
		u8 cmd_lo;
		u8 cmd_hi;
		u32 gen_ptr;
	पूर्ण scb;
	u32 port;
	u16 flash_ctrl;
	u8 eeprom_ctrl_lo;
	u8 eeprom_ctrl_hi;
	u32 mdi_ctrl;
	u32 rx_dma_count;
पूर्ण;

क्रमागत scb_status अणु
	rus_no_res       = 0x08,
	rus_पढ़ोy        = 0x10,
	rus_mask         = 0x3C,
पूर्ण;

क्रमागत ru_state  अणु
	RU_SUSPENDED = 0,
	RU_RUNNING	 = 1,
	RU_UNINITIALIZED = -1,
पूर्ण;

क्रमागत scb_stat_ack अणु
	stat_ack_not_ours    = 0x00,
	stat_ack_sw_gen      = 0x04,
	stat_ack_rnr         = 0x10,
	stat_ack_cu_idle     = 0x20,
	stat_ack_frame_rx    = 0x40,
	stat_ack_cu_cmd_करोne = 0x80,
	stat_ack_not_present = 0xFF,
	stat_ack_rx = (stat_ack_sw_gen | stat_ack_rnr | stat_ack_frame_rx),
	stat_ack_tx = (stat_ack_cu_idle | stat_ack_cu_cmd_करोne),
पूर्ण;

क्रमागत scb_cmd_hi अणु
	irq_mask_none = 0x00,
	irq_mask_all  = 0x01,
	irq_sw_gen    = 0x02,
पूर्ण;

क्रमागत scb_cmd_lo अणु
	cuc_nop        = 0x00,
	ruc_start      = 0x01,
	ruc_load_base  = 0x06,
	cuc_start      = 0x10,
	cuc_resume     = 0x20,
	cuc_dump_addr  = 0x40,
	cuc_dump_stats = 0x50,
	cuc_load_base  = 0x60,
	cuc_dump_reset = 0x70,
पूर्ण;

क्रमागत cuc_dump अणु
	cuc_dump_complete       = 0x0000A005,
	cuc_dump_reset_complete = 0x0000A007,
पूर्ण;

क्रमागत port अणु
	software_reset  = 0x0000,
	selftest        = 0x0001,
	selective_reset = 0x0002,
पूर्ण;

क्रमागत eeprom_ctrl_lo अणु
	eesk = 0x01,
	eecs = 0x02,
	eedi = 0x04,
	eeकरो = 0x08,
पूर्ण;

क्रमागत mdi_ctrl अणु
	mdi_ग_लिखो = 0x04000000,
	mdi_पढ़ो  = 0x08000000,
	mdi_पढ़ोy = 0x10000000,
पूर्ण;

क्रमागत eeprom_op अणु
	op_ग_लिखो = 0x05,
	op_पढ़ो  = 0x06,
	op_ewds  = 0x10,
	op_ewen  = 0x13,
पूर्ण;

क्रमागत eeprom_offsets अणु
	eeprom_cnfg_mdix  = 0x03,
	eeprom_phy_अगरace  = 0x06,
	eeprom_id         = 0x0A,
	eeprom_config_asf = 0x0D,
	eeprom_smbus_addr = 0x90,
पूर्ण;

क्रमागत eeprom_cnfg_mdix अणु
	eeprom_mdix_enabled = 0x0080,
पूर्ण;

क्रमागत eeprom_phy_अगरace अणु
	NoSuchPhy = 0,
	I82553AB,
	I82553C,
	I82503,
	DP83840,
	S80C240,
	S80C24,
	I82555,
	DP83840A = 10,
पूर्ण;

क्रमागत eeprom_id अणु
	eeprom_id_wol = 0x0020,
पूर्ण;

क्रमागत eeprom_config_asf अणु
	eeprom_asf = 0x8000,
	eeprom_gcl = 0x4000,
पूर्ण;

क्रमागत cb_status अणु
	cb_complete = 0x8000,
	cb_ok       = 0x2000,
पूर्ण;

/*
 * cb_command - Command Block flags
 * @cb_tx_nc:  0: controller करोes CRC (normal),  1: CRC from skb memory
 */
क्रमागत cb_command अणु
	cb_nop    = 0x0000,
	cb_iaaddr = 0x0001,
	cb_config = 0x0002,
	cb_multi  = 0x0003,
	cb_tx     = 0x0004,
	cb_ucode  = 0x0005,
	cb_dump   = 0x0006,
	cb_tx_sf  = 0x0008,
	cb_tx_nc  = 0x0010,
	cb_cid    = 0x1f00,
	cb_i      = 0x2000,
	cb_s      = 0x4000,
	cb_el     = 0x8000,
पूर्ण;

काष्ठा rfd अणु
	__le16 status;
	__le16 command;
	__le32 link;
	__le32 rbd;
	__le16 actual_size;
	__le16 size;
पूर्ण;

काष्ठा rx अणु
	काष्ठा rx *next, *prev;
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;
पूर्ण;

#अगर defined(__BIG_ENDIAN_BITFIELD)
#घोषणा X(a,b)	b,a
#अन्यथा
#घोषणा X(a,b)	a,b
#पूर्ण_अगर
काष्ठा config अणु
/*0*/	u8 X(byte_count:6, pad0:2);
/*1*/	u8 X(X(rx_fअगरo_limit:4, tx_fअगरo_limit:3), pad1:1);
/*2*/	u8 adaptive_अगरs;
/*3*/	u8 X(X(X(X(mwi_enable:1, type_enable:1), पढ़ो_align_enable:1),
	   term_ग_लिखो_cache_line:1), pad3:4);
/*4*/	u8 X(rx_dma_max_count:7, pad4:1);
/*5*/	u8 X(tx_dma_max_count:7, dma_max_count_enable:1);
/*6*/	u8 X(X(X(X(X(X(X(late_scb_update:1, direct_rx_dma:1),
	   tno_पूर्णांकr:1), cna_पूर्णांकr:1), standard_tcb:1), standard_stat_counter:1),
	   rx_save_overruns : 1), rx_save_bad_frames : 1);
/*7*/	u8 X(X(X(X(X(rx_discard_लघु_frames:1, tx_underrun_retry:2),
	   pad7:2), rx_extended_rfd:1), tx_two_frames_in_fअगरo:1),
	   tx_dynamic_tbd:1);
/*8*/	u8 X(X(mii_mode:1, pad8:6), csma_disabled:1);
/*9*/	u8 X(X(X(X(X(rx_tcpudp_checksum:1, pad9:3), vlan_arp_tco:1),
	   link_status_wake:1), arp_wake:1), mcmatch_wake:1);
/*10*/	u8 X(X(X(pad10:3, no_source_addr_insertion:1), preamble_length:2),
	   loopback:2);
/*11*/	u8 X(linear_priority:3, pad11:5);
/*12*/	u8 X(X(linear_priority_mode:1, pad12:3), अगरs:4);
/*13*/	u8 ip_addr_lo;
/*14*/	u8 ip_addr_hi;
/*15*/	u8 X(X(X(X(X(X(X(promiscuous_mode:1, broadcast_disabled:1),
	   रुको_after_win:1), pad15_1:1), ignore_ul_bit:1), crc_16_bit:1),
	   pad15_2:1), crs_or_cdt:1);
/*16*/	u8 fc_delay_lo;
/*17*/	u8 fc_delay_hi;
/*18*/	u8 X(X(X(X(X(rx_stripping:1, tx_padding:1), rx_crc_transfer:1),
	   rx_दीर्घ_ok:1), fc_priority_threshold:3), pad18:1);
/*19*/	u8 X(X(X(X(X(X(X(addr_wake:1, magic_packet_disable:1),
	   fc_disable:1), fc_restop:1), fc_restart:1), fc_reject:1),
	   full_duplex_क्रमce:1), full_duplex_pin:1);
/*20*/	u8 X(X(X(pad20_1:5, fc_priority_location:1), multi_ia:1), pad20_2:1);
/*21*/	u8 X(X(pad21_1:3, multicast_all:1), pad21_2:4);
/*22*/	u8 X(X(rx_d102_mode:1, rx_vlan_drop:1), pad22:6);
	u8 pad_d102[9];
पूर्ण;

#घोषणा E100_MAX_MULTICAST_ADDRS	64
काष्ठा multi अणु
	__le16 count;
	u8 addr[E100_MAX_MULTICAST_ADDRS * ETH_ALEN + 2/*pad*/];
पूर्ण;

/* Important: keep total काष्ठा u32-aligned */
#घोषणा UCODE_SIZE			134
काष्ठा cb अणु
	__le16 status;
	__le16 command;
	__le32 link;
	जोड़ अणु
		u8 iaaddr[ETH_ALEN];
		__le32 ucode[UCODE_SIZE];
		काष्ठा config config;
		काष्ठा multi multi;
		काष्ठा अणु
			u32 tbd_array;
			u16 tcb_byte_count;
			u8 threshold;
			u8 tbd_count;
			काष्ठा अणु
				__le32 buf_addr;
				__le16 size;
				u16 eol;
			पूर्ण tbd;
		पूर्ण tcb;
		__le32 dump_buffer_addr;
	पूर्ण u;
	काष्ठा cb *next, *prev;
	dma_addr_t dma_addr;
	काष्ठा sk_buff *skb;
पूर्ण;

क्रमागत loopback अणु
	lb_none = 0, lb_mac = 1, lb_phy = 3,
पूर्ण;

काष्ठा stats अणु
	__le32 tx_good_frames, tx_max_collisions, tx_late_collisions,
		tx_underruns, tx_lost_crs, tx_deferred, tx_single_collisions,
		tx_multiple_collisions, tx_total_collisions;
	__le32 rx_good_frames, rx_crc_errors, rx_alignment_errors,
		rx_resource_errors, rx_overrun_errors, rx_cdt_errors,
		rx_लघु_frame_errors;
	__le32 fc_xmt_छोड़ो, fc_rcv_छोड़ो, fc_rcv_unsupported;
	__le16 xmt_tco_frames, rcv_tco_frames;
	__le32 complete;
पूर्ण;

काष्ठा mem अणु
	काष्ठा अणु
		u32 signature;
		u32 result;
	पूर्ण selftest;
	काष्ठा stats stats;
	u8 dump_buf[596];
पूर्ण;

काष्ठा param_range अणु
	u32 min;
	u32 max;
	u32 count;
पूर्ण;

काष्ठा params अणु
	काष्ठा param_range rfds;
	काष्ठा param_range cbs;
पूर्ण;

काष्ठा nic अणु
	/* Begin: frequently used values: keep adjacent क्रम cache effect */
	u32 msg_enable				____cacheline_aligned;
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pdev;
	u16 (*mdio_ctrl)(काष्ठा nic *nic, u32 addr, u32 dir, u32 reg, u16 data);

	काष्ठा rx *rxs				____cacheline_aligned;
	काष्ठा rx *rx_to_use;
	काष्ठा rx *rx_to_clean;
	काष्ठा rfd blank_rfd;
	क्रमागत ru_state ru_running;

	spinlock_t cb_lock			____cacheline_aligned;
	spinlock_t cmd_lock;
	काष्ठा csr __iomem *csr;
	क्रमागत scb_cmd_lo cuc_cmd;
	अचिन्हित पूर्णांक cbs_avail;
	काष्ठा napi_काष्ठा napi;
	काष्ठा cb *cbs;
	काष्ठा cb *cb_to_use;
	काष्ठा cb *cb_to_send;
	काष्ठा cb *cb_to_clean;
	__le16 tx_command;
	/* End: frequently used values: keep adjacent क्रम cache effect */

	क्रमागत अणु
		ich                = (1 << 0),
		promiscuous        = (1 << 1),
		multicast_all      = (1 << 2),
		wol_magic          = (1 << 3),
		ich_10h_workaround = (1 << 4),
	पूर्ण flags					____cacheline_aligned;

	क्रमागत mac mac;
	क्रमागत phy phy;
	काष्ठा params params;
	काष्ठा समयr_list watchकरोg;
	काष्ठा mii_अगर_info mii;
	काष्ठा work_काष्ठा tx_समयout_task;
	क्रमागत loopback loopback;

	काष्ठा mem *mem;
	dma_addr_t dma_addr;

	काष्ठा dma_pool *cbs_pool;
	dma_addr_t cbs_dma_addr;
	u8 adaptive_अगरs;
	u8 tx_threshold;
	u32 tx_frames;
	u32 tx_collisions;
	u32 tx_deferred;
	u32 tx_single_collisions;
	u32 tx_multiple_collisions;
	u32 tx_fc_छोड़ो;
	u32 tx_tco_frames;

	u32 rx_fc_छोड़ो;
	u32 rx_fc_unsupported;
	u32 rx_tco_frames;
	u32 rx_लघु_frame_errors;
	u32 rx_over_length_errors;

	u16 eeprom_wc;
	__le16 eeprom[256];
	spinlock_t mdio_lock;
	स्थिर काष्ठा firmware *fw;
पूर्ण;

अटल अंतरभूत व्योम e100_ग_लिखो_flush(काष्ठा nic *nic)
अणु
	/* Flush previous PCI ग_लिखोs through पूर्णांकermediate bridges
	 * by करोing a benign पढ़ो */
	(व्योम)ioपढ़ो8(&nic->csr->scb.status);
पूर्ण

अटल व्योम e100_enable_irq(काष्ठा nic *nic)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&nic->cmd_lock, flags);
	ioग_लिखो8(irq_mask_none, &nic->csr->scb.cmd_hi);
	e100_ग_लिखो_flush(nic);
	spin_unlock_irqrestore(&nic->cmd_lock, flags);
पूर्ण

अटल व्योम e100_disable_irq(काष्ठा nic *nic)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&nic->cmd_lock, flags);
	ioग_लिखो8(irq_mask_all, &nic->csr->scb.cmd_hi);
	e100_ग_लिखो_flush(nic);
	spin_unlock_irqrestore(&nic->cmd_lock, flags);
पूर्ण

अटल व्योम e100_hw_reset(काष्ठा nic *nic)
अणु
	/* Put CU and RU पूर्णांकo idle with a selective reset to get
	 * device off of PCI bus */
	ioग_लिखो32(selective_reset, &nic->csr->port);
	e100_ग_लिखो_flush(nic); udelay(20);

	/* Now fully reset device */
	ioग_लिखो32(software_reset, &nic->csr->port);
	e100_ग_लिखो_flush(nic); udelay(20);

	/* Mask off our पूर्णांकerrupt line - it's unmasked after reset */
	e100_disable_irq(nic);
पूर्ण

अटल पूर्णांक e100_self_test(काष्ठा nic *nic)
अणु
	u32 dma_addr = nic->dma_addr + दुरत्व(काष्ठा mem, selftest);

	/* Passing the self-test is a pretty good indication
	 * that the device can DMA to/from host memory */

	nic->mem->selftest.signature = 0;
	nic->mem->selftest.result = 0xFFFFFFFF;

	ioग_लिखो32(selftest | dma_addr, &nic->csr->port);
	e100_ग_लिखो_flush(nic);
	/* Wait 10 msec क्रम self-test to complete */
	msleep(10);

	/* Interrupts are enabled after self-test */
	e100_disable_irq(nic);

	/* Check results of self-test */
	अगर (nic->mem->selftest.result != 0) अणु
		netअगर_err(nic, hw, nic->netdev,
			  "Self-test failed: result=0x%08X\n",
			  nic->mem->selftest.result);
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (nic->mem->selftest.signature == 0) अणु
		netअगर_err(nic, hw, nic->netdev, "Self-test failed: timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम e100_eeprom_ग_लिखो(काष्ठा nic *nic, u16 addr_len, u16 addr, __le16 data)
अणु
	u32 cmd_addr_data[3];
	u8 ctrl;
	पूर्णांक i, j;

	/* Three cmds: ग_लिखो/erase enable, ग_लिखो data, ग_लिखो/erase disable */
	cmd_addr_data[0] = op_ewen << (addr_len - 2);
	cmd_addr_data[1] = (((op_ग_लिखो << addr_len) | addr) << 16) |
		le16_to_cpu(data);
	cmd_addr_data[2] = op_ewds << (addr_len - 2);

	/* Bit-bang cmds to ग_लिखो word to eeprom */
	क्रम (j = 0; j < 3; j++) अणु

		/* Chip select */
		ioग_लिखो8(eecs | eesk, &nic->csr->eeprom_ctrl_lo);
		e100_ग_लिखो_flush(nic); udelay(4);

		क्रम (i = 31; i >= 0; i--) अणु
			ctrl = (cmd_addr_data[j] & (1 << i)) ?
				eecs | eedi : eecs;
			ioग_लिखो8(ctrl, &nic->csr->eeprom_ctrl_lo);
			e100_ग_लिखो_flush(nic); udelay(4);

			ioग_लिखो8(ctrl | eesk, &nic->csr->eeprom_ctrl_lo);
			e100_ग_लिखो_flush(nic); udelay(4);
		पूर्ण
		/* Wait 10 msec क्रम cmd to complete */
		msleep(10);

		/* Chip deselect */
		ioग_लिखो8(0, &nic->csr->eeprom_ctrl_lo);
		e100_ग_लिखो_flush(nic); udelay(4);
	पूर्ण
पूर्ण;

/* General technique stolen from the eepro100 driver - very clever */
अटल __le16 e100_eeprom_पढ़ो(काष्ठा nic *nic, u16 *addr_len, u16 addr)
अणु
	u32 cmd_addr_data;
	u16 data = 0;
	u8 ctrl;
	पूर्णांक i;

	cmd_addr_data = ((op_पढ़ो << *addr_len) | addr) << 16;

	/* Chip select */
	ioग_लिखो8(eecs | eesk, &nic->csr->eeprom_ctrl_lo);
	e100_ग_लिखो_flush(nic); udelay(4);

	/* Bit-bang to पढ़ो word from eeprom */
	क्रम (i = 31; i >= 0; i--) अणु
		ctrl = (cmd_addr_data & (1 << i)) ? eecs | eedi : eecs;
		ioग_लिखो8(ctrl, &nic->csr->eeprom_ctrl_lo);
		e100_ग_लिखो_flush(nic); udelay(4);

		ioग_लिखो8(ctrl | eesk, &nic->csr->eeprom_ctrl_lo);
		e100_ग_लिखो_flush(nic); udelay(4);

		/* Eeprom drives a dummy zero to EEDO after receiving
		 * complete address.  Use this to adjust addr_len. */
		ctrl = ioपढ़ो8(&nic->csr->eeprom_ctrl_lo);
		अगर (!(ctrl & eeकरो) && i > 16) अणु
			*addr_len -= (i - 16);
			i = 17;
		पूर्ण

		data = (data << 1) | (ctrl & eeकरो ? 1 : 0);
	पूर्ण

	/* Chip deselect */
	ioग_लिखो8(0, &nic->csr->eeprom_ctrl_lo);
	e100_ग_लिखो_flush(nic); udelay(4);

	वापस cpu_to_le16(data);
पूर्ण;

/* Load entire EEPROM image पूर्णांकo driver cache and validate checksum */
अटल पूर्णांक e100_eeprom_load(काष्ठा nic *nic)
अणु
	u16 addr, addr_len = 8, checksum = 0;

	/* Try पढ़ोing with an 8-bit addr len to discover actual addr len */
	e100_eeprom_पढ़ो(nic, &addr_len, 0);
	nic->eeprom_wc = 1 << addr_len;

	क्रम (addr = 0; addr < nic->eeprom_wc; addr++) अणु
		nic->eeprom[addr] = e100_eeprom_पढ़ो(nic, &addr_len, addr);
		अगर (addr < nic->eeprom_wc - 1)
			checksum += le16_to_cpu(nic->eeprom[addr]);
	पूर्ण

	/* The checksum, stored in the last word, is calculated such that
	 * the sum of words should be 0xBABA */
	अगर (cpu_to_le16(0xBABA - checksum) != nic->eeprom[nic->eeprom_wc - 1]) अणु
		netअगर_err(nic, probe, nic->netdev, "EEPROM corrupted\n");
		अगर (!eeprom_bad_csum_allow)
			वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

/* Save (portion of) driver EEPROM cache to device and update checksum */
अटल पूर्णांक e100_eeprom_save(काष्ठा nic *nic, u16 start, u16 count)
अणु
	u16 addr, addr_len = 8, checksum = 0;

	/* Try पढ़ोing with an 8-bit addr len to discover actual addr len */
	e100_eeprom_पढ़ो(nic, &addr_len, 0);
	nic->eeprom_wc = 1 << addr_len;

	अगर (start + count >= nic->eeprom_wc)
		वापस -EINVAL;

	क्रम (addr = start; addr < start + count; addr++)
		e100_eeprom_ग_लिखो(nic, addr_len, addr, nic->eeprom[addr]);

	/* The checksum, stored in the last word, is calculated such that
	 * the sum of words should be 0xBABA */
	क्रम (addr = 0; addr < nic->eeprom_wc - 1; addr++)
		checksum += le16_to_cpu(nic->eeprom[addr]);
	nic->eeprom[nic->eeprom_wc - 1] = cpu_to_le16(0xBABA - checksum);
	e100_eeprom_ग_लिखो(nic, addr_len, nic->eeprom_wc - 1,
		nic->eeprom[nic->eeprom_wc - 1]);

	वापस 0;
पूर्ण

#घोषणा E100_WAIT_SCB_TIMEOUT 20000 /* we might have to रुको 100ms!!! */
#घोषणा E100_WAIT_SCB_FAST 20       /* delay like the old code */
अटल पूर्णांक e100_exec_cmd(काष्ठा nic *nic, u8 cmd, dma_addr_t dma_addr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	spin_lock_irqsave(&nic->cmd_lock, flags);

	/* Previous command is accepted when SCB clears */
	क्रम (i = 0; i < E100_WAIT_SCB_TIMEOUT; i++) अणु
		अगर (likely(!ioपढ़ो8(&nic->csr->scb.cmd_lo)))
			अवरोध;
		cpu_relax();
		अगर (unlikely(i > E100_WAIT_SCB_FAST))
			udelay(5);
	पूर्ण
	अगर (unlikely(i == E100_WAIT_SCB_TIMEOUT)) अणु
		err = -EAGAIN;
		जाओ err_unlock;
	पूर्ण

	अगर (unlikely(cmd != cuc_resume))
		ioग_लिखो32(dma_addr, &nic->csr->scb.gen_ptr);
	ioग_लिखो8(cmd, &nic->csr->scb.cmd_lo);

err_unlock:
	spin_unlock_irqrestore(&nic->cmd_lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक e100_exec_cb(काष्ठा nic *nic, काष्ठा sk_buff *skb,
	पूर्णांक (*cb_prepare)(काष्ठा nic *, काष्ठा cb *, काष्ठा sk_buff *))
अणु
	काष्ठा cb *cb;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&nic->cb_lock, flags);

	अगर (unlikely(!nic->cbs_avail)) अणु
		err = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	cb = nic->cb_to_use;
	nic->cb_to_use = cb->next;
	nic->cbs_avail--;
	cb->skb = skb;

	err = cb_prepare(nic, cb, skb);
	अगर (err)
		जाओ err_unlock;

	अगर (unlikely(!nic->cbs_avail))
		err = -ENOSPC;


	/* Order is important otherwise we'll be in a race with h/w:
	 * set S-bit in current first, then clear S-bit in previous. */
	cb->command |= cpu_to_le16(cb_s);
	dma_wmb();
	cb->prev->command &= cpu_to_le16(~cb_s);

	जबतक (nic->cb_to_send != nic->cb_to_use) अणु
		अगर (unlikely(e100_exec_cmd(nic, nic->cuc_cmd,
			nic->cb_to_send->dma_addr))) अणु
			/* Ok, here's where things get sticky.  It's
			 * possible that we can't schedule the command
			 * because the controller is too busy, so
			 * let's just queue the command and try again
			 * when another command is scheduled. */
			अगर (err == -ENOSPC) अणु
				//request a reset
				schedule_work(&nic->tx_समयout_task);
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अणु
			nic->cuc_cmd = cuc_resume;
			nic->cb_to_send = nic->cb_to_send->next;
		पूर्ण
	पूर्ण

err_unlock:
	spin_unlock_irqrestore(&nic->cb_lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक addr, पूर्णांक reg)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	वापस nic->mdio_ctrl(nic, addr, mdi_पढ़ो, reg, 0);
पूर्ण

अटल व्योम mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक addr, पूर्णांक reg, पूर्णांक data)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);

	nic->mdio_ctrl(nic, addr, mdi_ग_लिखो, reg, data);
पूर्ण

/* the standard mdio_ctrl() function क्रम usual MII-compliant hardware */
अटल u16 mdio_ctrl_hw(काष्ठा nic *nic, u32 addr, u32 dir, u32 reg, u16 data)
अणु
	u32 data_out = 0;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;


	/*
	 * Stratus87247: we shouldn't be writing the MDI control
	 * रेजिस्टर until the Ready bit shows True.  Also, since
	 * manipulation of the MDI control रेजिस्टरs is a multi-step
	 * procedure it should be करोne under lock.
	 */
	spin_lock_irqsave(&nic->mdio_lock, flags);
	क्रम (i = 100; i; --i) अणु
		अगर (ioपढ़ो32(&nic->csr->mdi_ctrl) & mdi_पढ़ोy)
			अवरोध;
		udelay(20);
	पूर्ण
	अगर (unlikely(!i)) अणु
		netdev_err(nic->netdev, "e100.mdio_ctrl won't go Ready\n");
		spin_unlock_irqrestore(&nic->mdio_lock, flags);
		वापस 0;		/* No way to indicate समयout error */
	पूर्ण
	ioग_लिखो32((reg << 16) | (addr << 21) | dir | data, &nic->csr->mdi_ctrl);

	क्रम (i = 0; i < 100; i++) अणु
		udelay(20);
		अगर ((data_out = ioपढ़ो32(&nic->csr->mdi_ctrl)) & mdi_पढ़ोy)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&nic->mdio_lock, flags);
	netअगर_prपूर्णांकk(nic, hw, KERN_DEBUG, nic->netdev,
		     "%s:addr=%d, reg=%d, data_in=0x%04X, data_out=0x%04X\n",
		     dir == mdi_पढ़ो ? "READ" : "WRITE",
		     addr, reg, data, data_out);
	वापस (u16)data_out;
पूर्ण

/* slightly tweaked mdio_ctrl() function क्रम phy_82552_v specअगरics */
अटल u16 mdio_ctrl_phy_82552_v(काष्ठा nic *nic,
				 u32 addr,
				 u32 dir,
				 u32 reg,
				 u16 data)
अणु
	अगर ((reg == MII_BMCR) && (dir == mdi_ग_लिखो)) अणु
		अगर (data & (BMCR_ANRESTART | BMCR_ANENABLE)) अणु
			u16 advert = mdio_पढ़ो(nic->netdev, nic->mii.phy_id,
							MII_ADVERTISE);

			/*
			 * Workaround Si issue where someबार the part will not
			 * स्वतःneg to 100Mbps even when advertised.
			 */
			अगर (advert & ADVERTISE_100FULL)
				data |= BMCR_SPEED100 | BMCR_FULLDPLX;
			अन्यथा अगर (advert & ADVERTISE_100HALF)
				data |= BMCR_SPEED100;
		पूर्ण
	पूर्ण
	वापस mdio_ctrl_hw(nic, addr, dir, reg, data);
पूर्ण

/* Fully software-emulated mdio_ctrl() function क्रम cards without
 * MII-compliant PHYs.
 * For now, this is मुख्यly geared towards 80c24 support; in हाल of further
 * requirements क्रम other types (i82503, ...?) either extend this mechanism
 * or split it, whichever is cleaner.
 */
अटल u16 mdio_ctrl_phy_mii_emulated(काष्ठा nic *nic,
				      u32 addr,
				      u32 dir,
				      u32 reg,
				      u16 data)
अणु
	/* might need to allocate a netdev_priv'ed रेजिस्टर array eventually
	 * to be able to record state changes, but क्रम now
	 * some fully hardcoded रेजिस्टर handling ought to be ok I guess. */

	अगर (dir == mdi_पढ़ो) अणु
		चयन (reg) अणु
		हाल MII_BMCR:
			/* Auto-negotiation, right? */
			वापस  BMCR_ANENABLE |
				BMCR_FULLDPLX;
		हाल MII_BMSR:
			वापस	BMSR_LSTATUS /* क्रम mii_link_ok() */ |
				BMSR_ANEGCAPABLE |
				BMSR_10FULL;
		हाल MII_ADVERTISE:
			/* 80c24 is a "combo card" PHY, right? */
			वापस	ADVERTISE_10HALF |
				ADVERTISE_10FULL;
		शेष:
			netअगर_prपूर्णांकk(nic, hw, KERN_DEBUG, nic->netdev,
				     "%s:addr=%d, reg=%d, data=0x%04X: unimplemented emulation!\n",
				     dir == mdi_पढ़ो ? "READ" : "WRITE",
				     addr, reg, data);
			वापस 0xFFFF;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (reg) अणु
		शेष:
			netअगर_prपूर्णांकk(nic, hw, KERN_DEBUG, nic->netdev,
				     "%s:addr=%d, reg=%d, data=0x%04X: unimplemented emulation!\n",
				     dir == mdi_पढ़ो ? "READ" : "WRITE",
				     addr, reg, data);
			वापस 0xFFFF;
		पूर्ण
	पूर्ण
पूर्ण
अटल अंतरभूत पूर्णांक e100_phy_supports_mii(काष्ठा nic *nic)
अणु
	/* क्रम now, just check it by comparing whether we
	   are using MII software emulation.
	*/
	वापस (nic->mdio_ctrl != mdio_ctrl_phy_mii_emulated);
पूर्ण

अटल व्योम e100_get_शेषs(काष्ठा nic *nic)
अणु
	काष्ठा param_range rfds = अणु .min = 16, .max = 256, .count = 256 पूर्ण;
	काष्ठा param_range cbs  = अणु .min = 64, .max = 256, .count = 128 पूर्ण;

	/* MAC type is encoded as rev ID; exception: ICH is treated as 82559 */
	nic->mac = (nic->flags & ich) ? mac_82559_D101M : nic->pdev->revision;
	अगर (nic->mac == mac_unknown)
		nic->mac = mac_82557_D100_A;

	nic->params.rfds = rfds;
	nic->params.cbs = cbs;

	/* Quadwords to DMA पूर्णांकo FIFO beक्रमe starting frame transmit */
	nic->tx_threshold = 0xE0;

	/* no पूर्णांकerrupt क्रम every tx completion, delay = 256us अगर not 557 */
	nic->tx_command = cpu_to_le16(cb_tx | cb_tx_sf |
		((nic->mac >= mac_82558_D101_A4) ? cb_cid : cb_i));

	/* Template क्रम a freshly allocated RFD */
	nic->blank_rfd.command = 0;
	nic->blank_rfd.rbd = cpu_to_le32(0xFFFFFFFF);
	nic->blank_rfd.size = cpu_to_le16(VLAN_ETH_FRAME_LEN + ETH_FCS_LEN);

	/* MII setup */
	nic->mii.phy_id_mask = 0x1F;
	nic->mii.reg_num_mask = 0x1F;
	nic->mii.dev = nic->netdev;
	nic->mii.mdio_पढ़ो = mdio_पढ़ो;
	nic->mii.mdio_ग_लिखो = mdio_ग_लिखो;
पूर्ण

अटल पूर्णांक e100_configure(काष्ठा nic *nic, काष्ठा cb *cb, काष्ठा sk_buff *skb)
अणु
	काष्ठा config *config = &cb->u.config;
	u8 *c = (u8 *)config;
	काष्ठा net_device *netdev = nic->netdev;

	cb->command = cpu_to_le16(cb_config);

	स_रखो(config, 0, माप(काष्ठा config));

	config->byte_count = 0x16;		/* bytes in this काष्ठा */
	config->rx_fअगरo_limit = 0x8;		/* bytes in FIFO beक्रमe DMA */
	config->direct_rx_dma = 0x1;		/* reserved */
	config->standard_tcb = 0x1;		/* 1=standard, 0=extended */
	config->standard_stat_counter = 0x1;	/* 1=standard, 0=extended */
	config->rx_discard_लघु_frames = 0x1;	/* 1=discard, 0=pass */
	config->tx_underrun_retry = 0x3;	/* # of underrun retries */
	अगर (e100_phy_supports_mii(nic))
		config->mii_mode = 1;           /* 1=MII mode, 0=i82503 mode */
	config->pad10 = 0x6;
	config->no_source_addr_insertion = 0x1;	/* 1=no, 0=yes */
	config->preamble_length = 0x2;		/* 0=1, 1=3, 2=7, 3=15 bytes */
	config->अगरs = 0x6;			/* x16 = पूर्णांकer frame spacing */
	config->ip_addr_hi = 0xF2;		/* ARP IP filter - not used */
	config->pad15_1 = 0x1;
	config->pad15_2 = 0x1;
	config->crs_or_cdt = 0x0;		/* 0=CRS only, 1=CRS or CDT */
	config->fc_delay_hi = 0x40;		/* समय delay क्रम fc frame */
	config->tx_padding = 0x1;		/* 1=pad लघु frames */
	config->fc_priority_threshold = 0x7;	/* 7=priority fc disabled */
	config->pad18 = 0x1;
	config->full_duplex_pin = 0x1;		/* 1=examine FDX# pin */
	config->pad20_1 = 0x1F;
	config->fc_priority_location = 0x1;	/* 1=byte#31, 0=byte#19 */
	config->pad21_1 = 0x5;

	config->adaptive_अगरs = nic->adaptive_अगरs;
	config->loopback = nic->loopback;

	अगर (nic->mii.क्रमce_media && nic->mii.full_duplex)
		config->full_duplex_क्रमce = 0x1;	/* 1=क्रमce, 0=स्वतः */

	अगर (nic->flags & promiscuous || nic->loopback) अणु
		config->rx_save_bad_frames = 0x1;	/* 1=save, 0=discard */
		config->rx_discard_लघु_frames = 0x0;	/* 1=discard, 0=save */
		config->promiscuous_mode = 0x1;		/* 1=on, 0=off */
	पूर्ण

	अगर (unlikely(netdev->features & NETIF_F_RXFCS))
		config->rx_crc_transfer = 0x1;	/* 1=save, 0=discard */

	अगर (nic->flags & multicast_all)
		config->multicast_all = 0x1;		/* 1=accept, 0=no */

	/* disable WoL when up */
	अगर (netअगर_running(nic->netdev) || !(nic->flags & wol_magic))
		config->magic_packet_disable = 0x1;	/* 1=off, 0=on */

	अगर (nic->mac >= mac_82558_D101_A4) अणु
		config->fc_disable = 0x1;	/* 1=Tx fc off, 0=Tx fc on */
		config->mwi_enable = 0x1;	/* 1=enable, 0=disable */
		config->standard_tcb = 0x0;	/* 1=standard, 0=extended */
		config->rx_दीर्घ_ok = 0x1;	/* 1=VLANs ok, 0=standard */
		अगर (nic->mac >= mac_82559_D101M) अणु
			config->tno_पूर्णांकr = 0x1;		/* TCO stats enable */
			/* Enable TCO in extended config */
			अगर (nic->mac >= mac_82551_10) अणु
				config->byte_count = 0x20; /* extended bytes */
				config->rx_d102_mode = 0x1; /* GMRC क्रम TCO */
			पूर्ण
		पूर्ण अन्यथा अणु
			config->standard_stat_counter = 0x0;
		पूर्ण
	पूर्ण

	अगर (netdev->features & NETIF_F_RXALL) अणु
		config->rx_save_overruns = 0x1; /* 1=save, 0=discard */
		config->rx_save_bad_frames = 0x1;       /* 1=save, 0=discard */
		config->rx_discard_लघु_frames = 0x0;  /* 1=discard, 0=save */
	पूर्ण

	netअगर_prपूर्णांकk(nic, hw, KERN_DEBUG, nic->netdev, "[00-07]=%8ph\n",
		     c + 0);
	netअगर_prपूर्णांकk(nic, hw, KERN_DEBUG, nic->netdev, "[08-15]=%8ph\n",
		     c + 8);
	netअगर_prपूर्णांकk(nic, hw, KERN_DEBUG, nic->netdev, "[16-23]=%8ph\n",
		     c + 16);
	वापस 0;
पूर्ण

/*************************************************************************
*  CPUSaver parameters
*
*  All CPUSaver parameters are 16-bit literals that are part of a
*  "move immediate value" inकाष्ठाion.  By changing the value of
*  the literal in the inकाष्ठाion beक्रमe the code is loaded, the
*  driver can change the algorithm.
*
*  INTDELAY - This loads the dead-man समयr with its initial value.
*    When this समयr expires the पूर्णांकerrupt is निश्चितed, and the
*    समयr is reset each समय a new packet is received.  (see
*    BUNDLEMAX below to set the limit on number of chained packets)
*    The current शेष is 0x600 or 1536.  Experiments show that
*    the value should probably stay within the 0x200 - 0x1000.
*
*  BUNDLEMAX -
*    This sets the maximum number of frames that will be bundled.  In
*    some situations, such as the TCP winकरोwing algorithm, it may be
*    better to limit the growth of the bundle size than let it go as
*    high as it can, because that could cause too much added latency.
*    The शेष is six, because this is the number of packets in the
*    शेष TCP winकरोw size.  A value of 1 would make CPUSaver indicate
*    an पूर्णांकerrupt क्रम every frame received.  If you करो not want to put
*    a limit on the bundle size, set this value to xFFFF.
*
*  BUNDLESMALL -
*    This contains a bit-mask describing the minimum size frame that
*    will be bundled.  The शेष masks the lower 7 bits, which means
*    that any frame less than 128 bytes in length will not be bundled,
*    but will instead immediately generate an पूर्णांकerrupt.  This करोes
*    not affect the current bundle in any way.  Any frame that is 128
*    bytes or large will be bundled normally.  This feature is meant
*    to provide immediate indication of ACK frames in a TCP environment.
*    Customers were seeing poor perक्रमmance when a machine with CPUSaver
*    enabled was sending but not receiving.  The delay पूर्णांकroduced when
*    the ACKs were received was enough to reduce total throughput, because
*    the sender would sit idle until the ACK was finally seen.
*
*    The current शेष is 0xFF80, which masks out the lower 7 bits.
*    This means that any frame which is x7F (127) bytes or smaller
*    will cause an immediate पूर्णांकerrupt.  Because this value must be a
*    bit mask, there are only a few valid values that can be used.  To
*    turn this feature off, the driver can ग_लिखो the value xFFFF to the
*    lower word of this inकाष्ठाion (in the same way that the other
*    parameters are used).  Likewise, a value of 0xF800 (2047) would
*    cause an पूर्णांकerrupt to be generated क्रम every frame, because all
*    standard Ethernet frames are <= 2047 bytes in length.
*************************************************************************/

/* अगर you wish to disable the ucode functionality, जबतक मुख्यtaining the
 * workarounds it provides, set the following defines to:
 * BUNDLESMALL 0
 * BUNDLEMAX 1
 * INTDELAY 1
 */
#घोषणा BUNDLESMALL 1
#घोषणा BUNDLEMAX (u16)6
#घोषणा INTDELAY (u16)1536 /* 0x600 */

/* Initialize firmware */
अटल स्थिर काष्ठा firmware *e100_request_firmware(काष्ठा nic *nic)
अणु
	स्थिर अक्षर *fw_name;
	स्थिर काष्ठा firmware *fw = nic->fw;
	u8 समयr, bundle, min_size;
	पूर्णांक err = 0;
	bool required = false;

	/* करो not load u-code क्रम ICH devices */
	अगर (nic->flags & ich)
		वापस शून्य;

	/* Search क्रम ucode match against h/w revision
	 *
	 * Based on comments in the source code क्रम the FreeBSD fxp
	 * driver, the FIRMWARE_D102E ucode includes both CPUSaver and
	 *
	 *    "fixes क्रम bugs in the B-step hardware (specअगरically, bugs
	 *     with Inline Receive)."
	 *
	 * So we must fail अगर it cannot be loaded.
	 *
	 * The other microcode files are only required क्रम the optional
	 * CPUSaver feature.  Nice to have, but no reason to fail.
	 */
	अगर (nic->mac == mac_82559_D101M) अणु
		fw_name = FIRMWARE_D101M;
	पूर्ण अन्यथा अगर (nic->mac == mac_82559_D101S) अणु
		fw_name = FIRMWARE_D101S;
	पूर्ण अन्यथा अगर (nic->mac == mac_82551_F || nic->mac == mac_82551_10) अणु
		fw_name = FIRMWARE_D102E;
		required = true;
	पूर्ण अन्यथा अणु /* No ucode on other devices */
		वापस शून्य;
	पूर्ण

	/* If the firmware has not previously been loaded, request a poपूर्णांकer
	 * to it. If it was previously loaded, we are reinitializing the
	 * adapter, possibly in a resume from hibernate, in which हाल
	 * request_firmware() cannot be used.
	 */
	अगर (!fw)
		err = request_firmware(&fw, fw_name, &nic->pdev->dev);

	अगर (err) अणु
		अगर (required) अणु
			netअगर_err(nic, probe, nic->netdev,
				  "Failed to load firmware \"%s\": %d\n",
				  fw_name, err);
			वापस ERR_PTR(err);
		पूर्ण अन्यथा अणु
			netअगर_info(nic, probe, nic->netdev,
				   "CPUSaver disabled. Needs \"%s\": %d\n",
				   fw_name, err);
			वापस शून्य;
		पूर्ण
	पूर्ण

	/* Firmware should be precisely UCODE_SIZE (words) plus three bytes
	   indicating the offsets क्रम BUNDLESMALL, BUNDLEMAX, INTDELAY */
	अगर (fw->size != UCODE_SIZE * 4 + 3) अणु
		netअगर_err(nic, probe, nic->netdev,
			  "Firmware \"%s\" has wrong size %zu\n",
			  fw_name, fw->size);
		release_firmware(fw);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* Read समयr, bundle and min_size from end of firmware blob */
	समयr = fw->data[UCODE_SIZE * 4];
	bundle = fw->data[UCODE_SIZE * 4 + 1];
	min_size = fw->data[UCODE_SIZE * 4 + 2];

	अगर (समयr >= UCODE_SIZE || bundle >= UCODE_SIZE ||
	    min_size >= UCODE_SIZE) अणु
		netअगर_err(nic, probe, nic->netdev,
			  "\"%s\" has bogus offset values (0x%x,0x%x,0x%x)\n",
			  fw_name, समयr, bundle, min_size);
		release_firmware(fw);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* OK, firmware is validated and पढ़ोy to use. Save a poपूर्णांकer
	 * to it in the nic */
	nic->fw = fw;
	वापस fw;
पूर्ण

अटल पूर्णांक e100_setup_ucode(काष्ठा nic *nic, काष्ठा cb *cb,
			     काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा firmware *fw = (व्योम *)skb;
	u8 समयr, bundle, min_size;

	/* It's not a real skb; we just abused the fact that e100_exec_cb
	   will pass it through to here... */
	cb->skb = शून्य;

	/* firmware is stored as little endian alपढ़ोy */
	स_नकल(cb->u.ucode, fw->data, UCODE_SIZE * 4);

	/* Read समयr, bundle and min_size from end of firmware blob */
	समयr = fw->data[UCODE_SIZE * 4];
	bundle = fw->data[UCODE_SIZE * 4 + 1];
	min_size = fw->data[UCODE_SIZE * 4 + 2];

	/* Insert user-tunable settings in cb->u.ucode */
	cb->u.ucode[समयr] &= cpu_to_le32(0xFFFF0000);
	cb->u.ucode[समयr] |= cpu_to_le32(INTDELAY);
	cb->u.ucode[bundle] &= cpu_to_le32(0xFFFF0000);
	cb->u.ucode[bundle] |= cpu_to_le32(BUNDLEMAX);
	cb->u.ucode[min_size] &= cpu_to_le32(0xFFFF0000);
	cb->u.ucode[min_size] |= cpu_to_le32((BUNDLESMALL) ? 0xFFFF : 0xFF80);

	cb->command = cpu_to_le16(cb_ucode | cb_el);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक e100_load_ucode_रुको(काष्ठा nic *nic)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक err = 0, counter = 50;
	काष्ठा cb *cb = nic->cb_to_clean;

	fw = e100_request_firmware(nic);
	/* If it's शून्य, then no ucode is required */
	अगर (IS_ERR_OR_शून्य(fw))
		वापस PTR_ERR_OR_ZERO(fw);

	अगर ((err = e100_exec_cb(nic, (व्योम *)fw, e100_setup_ucode)))
		netअगर_err(nic, probe, nic->netdev,
			  "ucode cmd failed with error %d\n", err);

	/* must restart cuc */
	nic->cuc_cmd = cuc_start;

	/* रुको क्रम completion */
	e100_ग_लिखो_flush(nic);
	udelay(10);

	/* रुको क्रम possibly (ouch) 500ms */
	जबतक (!(cb->status & cpu_to_le16(cb_complete))) अणु
		msleep(10);
		अगर (!--counter) अवरोध;
	पूर्ण

	/* ack any पूर्णांकerrupts, something could have been set */
	ioग_लिखो8(~0, &nic->csr->scb.stat_ack);

	/* अगर the command failed, or is not OK, notअगरy and वापस */
	अगर (!counter || !(cb->status & cpu_to_le16(cb_ok))) अणु
		netअगर_err(nic, probe, nic->netdev, "ucode load failed\n");
		err = -EPERM;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक e100_setup_iaaddr(काष्ठा nic *nic, काष्ठा cb *cb,
	काष्ठा sk_buff *skb)
अणु
	cb->command = cpu_to_le16(cb_iaaddr);
	स_नकल(cb->u.iaaddr, nic->netdev->dev_addr, ETH_ALEN);
	वापस 0;
पूर्ण

अटल पूर्णांक e100_dump(काष्ठा nic *nic, काष्ठा cb *cb, काष्ठा sk_buff *skb)
अणु
	cb->command = cpu_to_le16(cb_dump);
	cb->u.dump_buffer_addr = cpu_to_le32(nic->dma_addr +
		दुरत्व(काष्ठा mem, dump_buf));
	वापस 0;
पूर्ण

अटल पूर्णांक e100_phy_check_without_mii(काष्ठा nic *nic)
अणु
	u8 phy_type;
	पूर्णांक without_mii;

	phy_type = (nic->eeprom[eeprom_phy_अगरace] >> 8) & 0x0f;

	चयन (phy_type) अणु
	हाल NoSuchPhy: /* Non-MII PHY; UNTESTED! */
	हाल I82503: /* Non-MII PHY; UNTESTED! */
	हाल S80C24: /* Non-MII PHY; tested and working */
		/* paragraph from the FreeBSD driver, "FXP_PHY_80C24":
		 * The Seeq 80c24 AutoDUPLEX(पंचांग) Ethernet Interface Adapter
		 * करोesn't have a programming पूर्णांकerface of any sort.  The
		 * media is sensed स्वतःmatically based on how the link partner
		 * is configured.  This is, in essence, manual configuration.
		 */
		netअगर_info(nic, probe, nic->netdev,
			   "found MII-less i82503 or 80c24 or other PHY\n");

		nic->mdio_ctrl = mdio_ctrl_phy_mii_emulated;
		nic->mii.phy_id = 0; /* is this ok क्रम an MII-less PHY? */

		/* these might be needed क्रम certain MII-less cards...
		 * nic->flags |= ich;
		 * nic->flags |= ich_10h_workaround; */

		without_mii = 1;
		अवरोध;
	शेष:
		without_mii = 0;
		अवरोध;
	पूर्ण
	वापस without_mii;
पूर्ण

#घोषणा NCONFIG_AUTO_SWITCH	0x0080
#घोषणा MII_NSC_CONG		MII_RESV1
#घोषणा NSC_CONG_ENABLE		0x0100
#घोषणा NSC_CONG_TXREADY	0x0400
#घोषणा ADVERTISE_FC_SUPPORTED	0x0400
अटल पूर्णांक e100_phy_init(काष्ठा nic *nic)
अणु
	काष्ठा net_device *netdev = nic->netdev;
	u32 addr;
	u16 bmcr, stat, id_lo, id_hi, cong;

	/* Discover phy addr by searching addrs in order अणु1,0,2,..., 31पूर्ण */
	क्रम (addr = 0; addr < 32; addr++) अणु
		nic->mii.phy_id = (addr == 0) ? 1 : (addr == 1) ? 0 : addr;
		bmcr = mdio_पढ़ो(netdev, nic->mii.phy_id, MII_BMCR);
		stat = mdio_पढ़ो(netdev, nic->mii.phy_id, MII_BMSR);
		stat = mdio_पढ़ो(netdev, nic->mii.phy_id, MII_BMSR);
		अगर (!((bmcr == 0xFFFF) || ((stat == 0) && (bmcr == 0))))
			अवरोध;
	पूर्ण
	अगर (addr == 32) अणु
		/* uhoh, no PHY detected: check whether we seem to be some
		 * weird, rare variant which is *known* to not have any MII.
		 * But करो this AFTER MII checking only, since this करोes
		 * lookup of EEPROM values which may easily be unreliable. */
		अगर (e100_phy_check_without_mii(nic))
			वापस 0; /* simply वापस and hope क्रम the best */
		अन्यथा अणु
			/* क्रम unknown हालs log a fatal error */
			netअगर_err(nic, hw, nic->netdev,
				  "Failed to locate any known PHY, aborting\n");
			वापस -EAGAIN;
		पूर्ण
	पूर्ण अन्यथा
		netअगर_prपूर्णांकk(nic, hw, KERN_DEBUG, nic->netdev,
			     "phy_addr = %d\n", nic->mii.phy_id);

	/* Get phy ID */
	id_lo = mdio_पढ़ो(netdev, nic->mii.phy_id, MII_PHYSID1);
	id_hi = mdio_पढ़ो(netdev, nic->mii.phy_id, MII_PHYSID2);
	nic->phy = (u32)id_hi << 16 | (u32)id_lo;
	netअगर_prपूर्णांकk(nic, hw, KERN_DEBUG, nic->netdev,
		     "phy ID = 0x%08X\n", nic->phy);

	/* Select the phy and isolate the rest */
	क्रम (addr = 0; addr < 32; addr++) अणु
		अगर (addr != nic->mii.phy_id) अणु
			mdio_ग_लिखो(netdev, addr, MII_BMCR, BMCR_ISOLATE);
		पूर्ण अन्यथा अगर (nic->phy != phy_82552_v) अणु
			bmcr = mdio_पढ़ो(netdev, addr, MII_BMCR);
			mdio_ग_लिखो(netdev, addr, MII_BMCR,
				bmcr & ~BMCR_ISOLATE);
		पूर्ण
	पूर्ण
	/*
	 * Workaround क्रम 82552:
	 * Clear the ISOLATE bit on selected phy_id last (mirrored on all
	 * other phy_id's) using bmcr value from addr discovery loop above.
	 */
	अगर (nic->phy == phy_82552_v)
		mdio_ग_लिखो(netdev, nic->mii.phy_id, MII_BMCR,
			bmcr & ~BMCR_ISOLATE);

	/* Handle National tx phys */
#घोषणा NCS_PHY_MODEL_MASK	0xFFF0FFFF
	अगर ((nic->phy & NCS_PHY_MODEL_MASK) == phy_nsc_tx) अणु
		/* Disable congestion control */
		cong = mdio_पढ़ो(netdev, nic->mii.phy_id, MII_NSC_CONG);
		cong |= NSC_CONG_TXREADY;
		cong &= ~NSC_CONG_ENABLE;
		mdio_ग_लिखो(netdev, nic->mii.phy_id, MII_NSC_CONG, cong);
	पूर्ण

	अगर (nic->phy == phy_82552_v) अणु
		u16 advert = mdio_पढ़ो(netdev, nic->mii.phy_id, MII_ADVERTISE);

		/* assign special tweaked mdio_ctrl() function */
		nic->mdio_ctrl = mdio_ctrl_phy_82552_v;

		/* Workaround Si not advertising flow-control during स्वतःneg */
		advert |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
		mdio_ग_लिखो(netdev, nic->mii.phy_id, MII_ADVERTISE, advert);

		/* Reset क्रम the above changes to take effect */
		bmcr = mdio_पढ़ो(netdev, nic->mii.phy_id, MII_BMCR);
		bmcr |= BMCR_RESET;
		mdio_ग_लिखो(netdev, nic->mii.phy_id, MII_BMCR, bmcr);
	पूर्ण अन्यथा अगर ((nic->mac >= mac_82550_D102) || ((nic->flags & ich) &&
	   (mdio_पढ़ो(netdev, nic->mii.phy_id, MII_TPISTATUS) & 0x8000) &&
		(nic->eeprom[eeprom_cnfg_mdix] & eeprom_mdix_enabled))) अणु
		/* enable/disable MDI/MDI-X स्वतः-चयनing. */
		mdio_ग_लिखो(netdev, nic->mii.phy_id, MII_NCONFIG,
				nic->mii.क्रमce_media ? 0 : NCONFIG_AUTO_SWITCH);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक e100_hw_init(काष्ठा nic *nic)
अणु
	पूर्णांक err = 0;

	e100_hw_reset(nic);

	netअगर_err(nic, hw, nic->netdev, "e100_hw_init\n");
	अगर ((err = e100_self_test(nic)))
		वापस err;

	अगर ((err = e100_phy_init(nic)))
		वापस err;
	अगर ((err = e100_exec_cmd(nic, cuc_load_base, 0)))
		वापस err;
	अगर ((err = e100_exec_cmd(nic, ruc_load_base, 0)))
		वापस err;
	अगर ((err = e100_load_ucode_रुको(nic)))
		वापस err;
	अगर ((err = e100_exec_cb(nic, शून्य, e100_configure)))
		वापस err;
	अगर ((err = e100_exec_cb(nic, शून्य, e100_setup_iaaddr)))
		वापस err;
	अगर ((err = e100_exec_cmd(nic, cuc_dump_addr,
		nic->dma_addr + दुरत्व(काष्ठा mem, stats))))
		वापस err;
	अगर ((err = e100_exec_cmd(nic, cuc_dump_reset, 0)))
		वापस err;

	e100_disable_irq(nic);

	वापस 0;
पूर्ण

अटल पूर्णांक e100_multi(काष्ठा nic *nic, काष्ठा cb *cb, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *netdev = nic->netdev;
	काष्ठा netdev_hw_addr *ha;
	u16 i, count = min(netdev_mc_count(netdev), E100_MAX_MULTICAST_ADDRS);

	cb->command = cpu_to_le16(cb_multi);
	cb->u.multi.count = cpu_to_le16(count * ETH_ALEN);
	i = 0;
	netdev_क्रम_each_mc_addr(ha, netdev) अणु
		अगर (i == count)
			अवरोध;
		स_नकल(&cb->u.multi.addr[i++ * ETH_ALEN], &ha->addr,
			ETH_ALEN);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम e100_set_multicast_list(काष्ठा net_device *netdev)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);

	netअगर_prपूर्णांकk(nic, hw, KERN_DEBUG, nic->netdev,
		     "mc_count=%d, flags=0x%04X\n",
		     netdev_mc_count(netdev), netdev->flags);

	अगर (netdev->flags & IFF_PROMISC)
		nic->flags |= promiscuous;
	अन्यथा
		nic->flags &= ~promiscuous;

	अगर (netdev->flags & IFF_ALLMULTI ||
		netdev_mc_count(netdev) > E100_MAX_MULTICAST_ADDRS)
		nic->flags |= multicast_all;
	अन्यथा
		nic->flags &= ~multicast_all;

	e100_exec_cb(nic, शून्य, e100_configure);
	e100_exec_cb(nic, शून्य, e100_multi);
पूर्ण

अटल व्योम e100_update_stats(काष्ठा nic *nic)
अणु
	काष्ठा net_device *dev = nic->netdev;
	काष्ठा net_device_stats *ns = &dev->stats;
	काष्ठा stats *s = &nic->mem->stats;
	__le32 *complete = (nic->mac < mac_82558_D101_A4) ? &s->fc_xmt_छोड़ो :
		(nic->mac < mac_82559_D101M) ? (__le32 *)&s->xmt_tco_frames :
		&s->complete;

	/* Device's stats reporting may take several microseconds to
	 * complete, so we're always रुकोing क्रम results of the
	 * previous command. */

	अगर (*complete == cpu_to_le32(cuc_dump_reset_complete)) अणु
		*complete = 0;
		nic->tx_frames = le32_to_cpu(s->tx_good_frames);
		nic->tx_collisions = le32_to_cpu(s->tx_total_collisions);
		ns->tx_पातed_errors += le32_to_cpu(s->tx_max_collisions);
		ns->tx_winकरोw_errors += le32_to_cpu(s->tx_late_collisions);
		ns->tx_carrier_errors += le32_to_cpu(s->tx_lost_crs);
		ns->tx_fअगरo_errors += le32_to_cpu(s->tx_underruns);
		ns->collisions += nic->tx_collisions;
		ns->tx_errors += le32_to_cpu(s->tx_max_collisions) +
			le32_to_cpu(s->tx_lost_crs);
		nic->rx_लघु_frame_errors +=
			le32_to_cpu(s->rx_लघु_frame_errors);
		ns->rx_length_errors = nic->rx_लघु_frame_errors +
			nic->rx_over_length_errors;
		ns->rx_crc_errors += le32_to_cpu(s->rx_crc_errors);
		ns->rx_frame_errors += le32_to_cpu(s->rx_alignment_errors);
		ns->rx_over_errors += le32_to_cpu(s->rx_overrun_errors);
		ns->rx_fअगरo_errors += le32_to_cpu(s->rx_overrun_errors);
		ns->rx_missed_errors += le32_to_cpu(s->rx_resource_errors);
		ns->rx_errors += le32_to_cpu(s->rx_crc_errors) +
			le32_to_cpu(s->rx_alignment_errors) +
			le32_to_cpu(s->rx_लघु_frame_errors) +
			le32_to_cpu(s->rx_cdt_errors);
		nic->tx_deferred += le32_to_cpu(s->tx_deferred);
		nic->tx_single_collisions +=
			le32_to_cpu(s->tx_single_collisions);
		nic->tx_multiple_collisions +=
			le32_to_cpu(s->tx_multiple_collisions);
		अगर (nic->mac >= mac_82558_D101_A4) अणु
			nic->tx_fc_छोड़ो += le32_to_cpu(s->fc_xmt_छोड़ो);
			nic->rx_fc_छोड़ो += le32_to_cpu(s->fc_rcv_छोड़ो);
			nic->rx_fc_unsupported +=
				le32_to_cpu(s->fc_rcv_unsupported);
			अगर (nic->mac >= mac_82559_D101M) अणु
				nic->tx_tco_frames +=
					le16_to_cpu(s->xmt_tco_frames);
				nic->rx_tco_frames +=
					le16_to_cpu(s->rcv_tco_frames);
			पूर्ण
		पूर्ण
	पूर्ण


	अगर (e100_exec_cmd(nic, cuc_dump_reset, 0))
		netअगर_prपूर्णांकk(nic, tx_err, KERN_DEBUG, nic->netdev,
			     "exec cuc_dump_reset failed\n");
पूर्ण

अटल व्योम e100_adjust_adaptive_अगरs(काष्ठा nic *nic, पूर्णांक speed, पूर्णांक duplex)
अणु
	/* Adjust पूर्णांकer-frame-spacing (IFS) between two transmits अगर
	 * we're getting collisions on a half-duplex connection. */

	अगर (duplex == DUPLEX_HALF) अणु
		u32 prev = nic->adaptive_अगरs;
		u32 min_frames = (speed == SPEED_100) ? 1000 : 100;

		अगर ((nic->tx_frames / 32 < nic->tx_collisions) &&
		   (nic->tx_frames > min_frames)) अणु
			अगर (nic->adaptive_अगरs < 60)
				nic->adaptive_अगरs += 5;
		पूर्ण अन्यथा अगर (nic->tx_frames < min_frames) अणु
			अगर (nic->adaptive_अगरs >= 5)
				nic->adaptive_अगरs -= 5;
		पूर्ण
		अगर (nic->adaptive_अगरs != prev)
			e100_exec_cb(nic, शून्य, e100_configure);
	पूर्ण
पूर्ण

अटल व्योम e100_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा nic *nic = from_समयr(nic, t, watchकरोg);
	काष्ठा ethtool_cmd cmd = अणु .cmd = ETHTOOL_GSET पूर्ण;
	u32 speed;

	netअगर_prपूर्णांकk(nic, समयr, KERN_DEBUG, nic->netdev,
		     "right now = %ld\n", jअगरfies);

	/* mii library handles link मुख्यtenance tasks */

	mii_ethtool_gset(&nic->mii, &cmd);
	speed = ethtool_cmd_speed(&cmd);

	अगर (mii_link_ok(&nic->mii) && !netअगर_carrier_ok(nic->netdev)) अणु
		netdev_info(nic->netdev, "NIC Link is Up %u Mbps %s Duplex\n",
			    speed == SPEED_100 ? 100 : 10,
			    cmd.duplex == DUPLEX_FULL ? "Full" : "Half");
	पूर्ण अन्यथा अगर (!mii_link_ok(&nic->mii) && netअगर_carrier_ok(nic->netdev)) अणु
		netdev_info(nic->netdev, "NIC Link is Down\n");
	पूर्ण

	mii_check_link(&nic->mii);

	/* Software generated पूर्णांकerrupt to recover from (rare) Rx
	 * allocation failure.
	 * Unक्रमtunately have to use a spinlock to not re-enable पूर्णांकerrupts
	 * accidentally, due to hardware that shares a रेजिस्टर between the
	 * पूर्णांकerrupt mask bit and the SW Interrupt generation bit */
	spin_lock_irq(&nic->cmd_lock);
	ioग_लिखो8(ioपढ़ो8(&nic->csr->scb.cmd_hi) | irq_sw_gen,&nic->csr->scb.cmd_hi);
	e100_ग_लिखो_flush(nic);
	spin_unlock_irq(&nic->cmd_lock);

	e100_update_stats(nic);
	e100_adjust_adaptive_अगरs(nic, speed, cmd.duplex);

	अगर (nic->mac <= mac_82557_D100_C)
		/* Issue a multicast command to workaround a 557 lock up */
		e100_set_multicast_list(nic->netdev);

	अगर (nic->flags & ich && speed == SPEED_10 && cmd.duplex == DUPLEX_HALF)
		/* Need SW workaround क्रम ICH[x] 10Mbps/half duplex Tx hang. */
		nic->flags |= ich_10h_workaround;
	अन्यथा
		nic->flags &= ~ich_10h_workaround;

	mod_समयr(&nic->watchकरोg,
		  round_jअगरfies(jअगरfies + E100_WATCHDOG_PERIOD));
पूर्ण

अटल पूर्णांक e100_xmit_prepare(काष्ठा nic *nic, काष्ठा cb *cb,
	काष्ठा sk_buff *skb)
अणु
	dma_addr_t dma_addr;
	cb->command = nic->tx_command;

	dma_addr = dma_map_single(&nic->pdev->dev, skb->data, skb->len,
				  DMA_TO_DEVICE);
	/* If we can't map the skb, have the upper layer try later */
	अगर (dma_mapping_error(&nic->pdev->dev, dma_addr)) अणु
		dev_kमुक्त_skb_any(skb);
		skb = शून्य;
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Use the last 4 bytes of the SKB payload packet as the CRC, used क्रम
	 * testing, ie sending frames with bad CRC.
	 */
	अगर (unlikely(skb->no_fcs))
		cb->command |= cpu_to_le16(cb_tx_nc);
	अन्यथा
		cb->command &= ~cpu_to_le16(cb_tx_nc);

	/* पूर्णांकerrupt every 16 packets regardless of delay */
	अगर ((nic->cbs_avail & ~15) == nic->cbs_avail)
		cb->command |= cpu_to_le16(cb_i);
	cb->u.tcb.tbd_array = cb->dma_addr + दुरत्व(काष्ठा cb, u.tcb.tbd);
	cb->u.tcb.tcb_byte_count = 0;
	cb->u.tcb.threshold = nic->tx_threshold;
	cb->u.tcb.tbd_count = 1;
	cb->u.tcb.tbd.buf_addr = cpu_to_le32(dma_addr);
	cb->u.tcb.tbd.size = cpu_to_le16(skb->len);
	skb_tx_बारtamp(skb);
	वापस 0;
पूर्ण

अटल netdev_tx_t e100_xmit_frame(काष्ठा sk_buff *skb,
				   काष्ठा net_device *netdev)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	पूर्णांक err;

	अगर (nic->flags & ich_10h_workaround) अणु
		/* SW workaround क्रम ICH[x] 10Mbps/half duplex Tx hang.
		   Issue a NOP command followed by a 1us delay beक्रमe
		   issuing the Tx command. */
		अगर (e100_exec_cmd(nic, cuc_nop, 0))
			netअगर_prपूर्णांकk(nic, tx_err, KERN_DEBUG, nic->netdev,
				     "exec cuc_nop failed\n");
		udelay(1);
	पूर्ण

	err = e100_exec_cb(nic, skb, e100_xmit_prepare);

	चयन (err) अणु
	हाल -ENOSPC:
		/* We queued the skb, but now we're out of space. */
		netअगर_prपूर्णांकk(nic, tx_err, KERN_DEBUG, nic->netdev,
			     "No space for CB\n");
		netअगर_stop_queue(netdev);
		अवरोध;
	हाल -ENOMEM:
		/* This is a hard error - log it. */
		netअगर_prपूर्णांकk(nic, tx_err, KERN_DEBUG, nic->netdev,
			     "Out of Tx resources, returning skb\n");
		netअगर_stop_queue(netdev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक e100_tx_clean(काष्ठा nic *nic)
अणु
	काष्ठा net_device *dev = nic->netdev;
	काष्ठा cb *cb;
	पूर्णांक tx_cleaned = 0;

	spin_lock(&nic->cb_lock);

	/* Clean CBs marked complete */
	क्रम (cb = nic->cb_to_clean;
	    cb->status & cpu_to_le16(cb_complete);
	    cb = nic->cb_to_clean = cb->next) अणु
		dma_rmb(); /* पढ़ो skb after status */
		netअगर_prपूर्णांकk(nic, tx_करोne, KERN_DEBUG, nic->netdev,
			     "cb[%d]->status = 0x%04X\n",
			     (पूर्णांक)(((व्योम*)cb - (व्योम*)nic->cbs)/माप(काष्ठा cb)),
			     cb->status);

		अगर (likely(cb->skb != शून्य)) अणु
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += cb->skb->len;

			dma_unmap_single(&nic->pdev->dev,
					 le32_to_cpu(cb->u.tcb.tbd.buf_addr),
					 le16_to_cpu(cb->u.tcb.tbd.size),
					 DMA_TO_DEVICE);
			dev_kमुक्त_skb_any(cb->skb);
			cb->skb = शून्य;
			tx_cleaned = 1;
		पूर्ण
		cb->status = 0;
		nic->cbs_avail++;
	पूर्ण

	spin_unlock(&nic->cb_lock);

	/* Recover from running out of Tx resources in xmit_frame */
	अगर (unlikely(tx_cleaned && netअगर_queue_stopped(nic->netdev)))
		netअगर_wake_queue(nic->netdev);

	वापस tx_cleaned;
पूर्ण

अटल व्योम e100_clean_cbs(काष्ठा nic *nic)
अणु
	अगर (nic->cbs) अणु
		जबतक (nic->cbs_avail != nic->params.cbs.count) अणु
			काष्ठा cb *cb = nic->cb_to_clean;
			अगर (cb->skb) अणु
				dma_unmap_single(&nic->pdev->dev,
						 le32_to_cpu(cb->u.tcb.tbd.buf_addr),
						 le16_to_cpu(cb->u.tcb.tbd.size),
						 DMA_TO_DEVICE);
				dev_kमुक्त_skb(cb->skb);
			पूर्ण
			nic->cb_to_clean = nic->cb_to_clean->next;
			nic->cbs_avail++;
		पूर्ण
		dma_pool_मुक्त(nic->cbs_pool, nic->cbs, nic->cbs_dma_addr);
		nic->cbs = शून्य;
		nic->cbs_avail = 0;
	पूर्ण
	nic->cuc_cmd = cuc_start;
	nic->cb_to_use = nic->cb_to_send = nic->cb_to_clean =
		nic->cbs;
पूर्ण

अटल पूर्णांक e100_alloc_cbs(काष्ठा nic *nic)
अणु
	काष्ठा cb *cb;
	अचिन्हित पूर्णांक i, count = nic->params.cbs.count;

	nic->cuc_cmd = cuc_start;
	nic->cb_to_use = nic->cb_to_send = nic->cb_to_clean = शून्य;
	nic->cbs_avail = 0;

	nic->cbs = dma_pool_zalloc(nic->cbs_pool, GFP_KERNEL,
				   &nic->cbs_dma_addr);
	अगर (!nic->cbs)
		वापस -ENOMEM;

	क्रम (cb = nic->cbs, i = 0; i < count; cb++, i++) अणु
		cb->next = (i + 1 < count) ? cb + 1 : nic->cbs;
		cb->prev = (i == 0) ? nic->cbs + count - 1 : cb - 1;

		cb->dma_addr = nic->cbs_dma_addr + i * माप(काष्ठा cb);
		cb->link = cpu_to_le32(nic->cbs_dma_addr +
			((i+1) % count) * माप(काष्ठा cb));
	पूर्ण

	nic->cb_to_use = nic->cb_to_send = nic->cb_to_clean = nic->cbs;
	nic->cbs_avail = count;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम e100_start_receiver(काष्ठा nic *nic, काष्ठा rx *rx)
अणु
	अगर (!nic->rxs) वापस;
	अगर (RU_SUSPENDED != nic->ru_running) वापस;

	/* handle init समय starts */
	अगर (!rx) rx = nic->rxs;

	/* (Re)start RU अगर suspended or idle and RFA is non-शून्य */
	अगर (rx->skb) अणु
		e100_exec_cmd(nic, ruc_start, rx->dma_addr);
		nic->ru_running = RU_RUNNING;
	पूर्ण
पूर्ण

#घोषणा RFD_BUF_LEN (माप(काष्ठा rfd) + VLAN_ETH_FRAME_LEN + ETH_FCS_LEN)
अटल पूर्णांक e100_rx_alloc_skb(काष्ठा nic *nic, काष्ठा rx *rx)
अणु
	अगर (!(rx->skb = netdev_alloc_skb_ip_align(nic->netdev, RFD_BUF_LEN)))
		वापस -ENOMEM;

	/* Init, and map the RFD. */
	skb_copy_to_linear_data(rx->skb, &nic->blank_rfd, माप(काष्ठा rfd));
	rx->dma_addr = dma_map_single(&nic->pdev->dev, rx->skb->data,
				      RFD_BUF_LEN, DMA_BIसूचीECTIONAL);

	अगर (dma_mapping_error(&nic->pdev->dev, rx->dma_addr)) अणु
		dev_kमुक्त_skb_any(rx->skb);
		rx->skb = शून्य;
		rx->dma_addr = 0;
		वापस -ENOMEM;
	पूर्ण

	/* Link the RFD to end of RFA by linking previous RFD to
	 * this one.  We are safe to touch the previous RFD because
	 * it is रक्षित by the beक्रमe last buffer's el bit being set */
	अगर (rx->prev->skb) अणु
		काष्ठा rfd *prev_rfd = (काष्ठा rfd *)rx->prev->skb->data;
		put_unaligned_le32(rx->dma_addr, &prev_rfd->link);
		dma_sync_single_क्रम_device(&nic->pdev->dev,
					   rx->prev->dma_addr,
					   माप(काष्ठा rfd),
					   DMA_BIसूचीECTIONAL);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक e100_rx_indicate(काष्ठा nic *nic, काष्ठा rx *rx,
	अचिन्हित पूर्णांक *work_करोne, अचिन्हित पूर्णांक work_to_करो)
अणु
	काष्ठा net_device *dev = nic->netdev;
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा rfd *rfd = (काष्ठा rfd *)skb->data;
	u16 rfd_status, actual_size;
	u16 fcs_pad = 0;

	अगर (unlikely(work_करोne && *work_करोne >= work_to_करो))
		वापस -EAGAIN;

	/* Need to sync beक्रमe taking a peek at cb_complete bit */
	dma_sync_single_क्रम_cpu(&nic->pdev->dev, rx->dma_addr,
				माप(काष्ठा rfd), DMA_BIसूचीECTIONAL);
	rfd_status = le16_to_cpu(rfd->status);

	netअगर_prपूर्णांकk(nic, rx_status, KERN_DEBUG, nic->netdev,
		     "status=0x%04X\n", rfd_status);
	dma_rmb(); /* पढ़ो size after status bit */

	/* If data isn't पढ़ोy, nothing to indicate */
	अगर (unlikely(!(rfd_status & cb_complete))) अणु
		/* If the next buffer has the el bit, but we think the receiver
		 * is still running, check to see अगर it really stopped जबतक
		 * we had पूर्णांकerrupts off.
		 * This allows क्रम a fast restart without re-enabling
		 * पूर्णांकerrupts */
		अगर ((le16_to_cpu(rfd->command) & cb_el) &&
		    (RU_RUNNING == nic->ru_running))

			अगर (ioपढ़ो8(&nic->csr->scb.status) & rus_no_res)
				nic->ru_running = RU_SUSPENDED;
		dma_sync_single_क्रम_device(&nic->pdev->dev, rx->dma_addr,
					   माप(काष्ठा rfd),
					   DMA_FROM_DEVICE);
		वापस -ENODATA;
	पूर्ण

	/* Get actual data size */
	अगर (unlikely(dev->features & NETIF_F_RXFCS))
		fcs_pad = 4;
	actual_size = le16_to_cpu(rfd->actual_size) & 0x3FFF;
	अगर (unlikely(actual_size > RFD_BUF_LEN - माप(काष्ठा rfd)))
		actual_size = RFD_BUF_LEN - माप(काष्ठा rfd);

	/* Get data */
	dma_unmap_single(&nic->pdev->dev, rx->dma_addr, RFD_BUF_LEN,
			 DMA_BIसूचीECTIONAL);

	/* If this buffer has the el bit, but we think the receiver
	 * is still running, check to see अगर it really stopped जबतक
	 * we had पूर्णांकerrupts off.
	 * This allows क्रम a fast restart without re-enabling पूर्णांकerrupts.
	 * This can happen when the RU sees the size change but also sees
	 * the el bit set. */
	अगर ((le16_to_cpu(rfd->command) & cb_el) &&
	    (RU_RUNNING == nic->ru_running)) अणु

	    अगर (ioपढ़ो8(&nic->csr->scb.status) & rus_no_res)
		nic->ru_running = RU_SUSPENDED;
	पूर्ण

	/* Pull off the RFD and put the actual data (minus eth hdr) */
	skb_reserve(skb, माप(काष्ठा rfd));
	skb_put(skb, actual_size);
	skb->protocol = eth_type_trans(skb, nic->netdev);

	/* If we are receiving all frames, then करोn't bother
	 * checking क्रम errors.
	 */
	अगर (unlikely(dev->features & NETIF_F_RXALL)) अणु
		अगर (actual_size > ETH_DATA_LEN + VLAN_ETH_HLEN + fcs_pad)
			/* Received oversized frame, but keep it. */
			nic->rx_over_length_errors++;
		जाओ process_skb;
	पूर्ण

	अगर (unlikely(!(rfd_status & cb_ok))) अणु
		/* Don't indicate अगर hardware indicates errors */
		dev_kमुक्त_skb_any(skb);
	पूर्ण अन्यथा अगर (actual_size > ETH_DATA_LEN + VLAN_ETH_HLEN + fcs_pad) अणु
		/* Don't indicate oversized frames */
		nic->rx_over_length_errors++;
		dev_kमुक्त_skb_any(skb);
	पूर्ण अन्यथा अणु
process_skb:
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += (actual_size - fcs_pad);
		netअगर_receive_skb(skb);
		अगर (work_करोne)
			(*work_करोne)++;
	पूर्ण

	rx->skb = शून्य;

	वापस 0;
पूर्ण

अटल व्योम e100_rx_clean(काष्ठा nic *nic, अचिन्हित पूर्णांक *work_करोne,
	अचिन्हित पूर्णांक work_to_करो)
अणु
	काष्ठा rx *rx;
	पूर्णांक restart_required = 0, err = 0;
	काष्ठा rx *old_beक्रमe_last_rx, *new_beक्रमe_last_rx;
	काष्ठा rfd *old_beक्रमe_last_rfd, *new_beक्रमe_last_rfd;

	/* Indicate newly arrived packets */
	क्रम (rx = nic->rx_to_clean; rx->skb; rx = nic->rx_to_clean = rx->next) अणु
		err = e100_rx_indicate(nic, rx, work_करोne, work_to_करो);
		/* Hit quota or no more to clean */
		अगर (-EAGAIN == err || -ENODATA == err)
			अवरोध;
	पूर्ण


	/* On EAGAIN, hit quota so have more work to करो, restart once
	 * cleanup is complete.
	 * Else, are we alपढ़ोy rnr? then pay attention!!! this ensures that
	 * the state machine progression never allows a start with a
	 * partially cleaned list, aव्योमing a race between hardware
	 * and rx_to_clean when in NAPI mode */
	अगर (-EAGAIN != err && RU_SUSPENDED == nic->ru_running)
		restart_required = 1;

	old_beक्रमe_last_rx = nic->rx_to_use->prev->prev;
	old_beक्रमe_last_rfd = (काष्ठा rfd *)old_beक्रमe_last_rx->skb->data;

	/* Alloc new skbs to refill list */
	क्रम (rx = nic->rx_to_use; !rx->skb; rx = nic->rx_to_use = rx->next) अणु
		अगर (unlikely(e100_rx_alloc_skb(nic, rx)))
			अवरोध; /* Better luck next समय (see watchकरोg) */
	पूर्ण

	new_beक्रमe_last_rx = nic->rx_to_use->prev->prev;
	अगर (new_beक्रमe_last_rx != old_beक्रमe_last_rx) अणु
		/* Set the el-bit on the buffer that is beक्रमe the last buffer.
		 * This lets us update the next poपूर्णांकer on the last buffer
		 * without worrying about hardware touching it.
		 * We set the size to 0 to prevent hardware from touching this
		 * buffer.
		 * When the hardware hits the beक्रमe last buffer with el-bit
		 * and size of 0, it will RNR पूर्णांकerrupt, the RUS will go पूर्णांकo
		 * the No Resources state.  It will not complete nor ग_लिखो to
		 * this buffer. */
		new_beक्रमe_last_rfd =
			(काष्ठा rfd *)new_beक्रमe_last_rx->skb->data;
		new_beक्रमe_last_rfd->size = 0;
		new_beक्रमe_last_rfd->command |= cpu_to_le16(cb_el);
		dma_sync_single_क्रम_device(&nic->pdev->dev,
					   new_beक्रमe_last_rx->dma_addr,
					   माप(काष्ठा rfd),
					   DMA_BIसूचीECTIONAL);

		/* Now that we have a new stopping poपूर्णांक, we can clear the old
		 * stopping poपूर्णांक.  We must sync twice to get the proper
		 * ordering on the hardware side of things. */
		old_beक्रमe_last_rfd->command &= ~cpu_to_le16(cb_el);
		dma_sync_single_क्रम_device(&nic->pdev->dev,
					   old_beक्रमe_last_rx->dma_addr,
					   माप(काष्ठा rfd),
					   DMA_BIसूचीECTIONAL);
		old_beक्रमe_last_rfd->size = cpu_to_le16(VLAN_ETH_FRAME_LEN
							+ ETH_FCS_LEN);
		dma_sync_single_क्रम_device(&nic->pdev->dev,
					   old_beक्रमe_last_rx->dma_addr,
					   माप(काष्ठा rfd),
					   DMA_BIसूचीECTIONAL);
	पूर्ण

	अगर (restart_required) अणु
		// ack the rnr?
		ioग_लिखो8(stat_ack_rnr, &nic->csr->scb.stat_ack);
		e100_start_receiver(nic, nic->rx_to_clean);
		अगर (work_करोne)
			(*work_करोne)++;
	पूर्ण
पूर्ण

अटल व्योम e100_rx_clean_list(काष्ठा nic *nic)
अणु
	काष्ठा rx *rx;
	अचिन्हित पूर्णांक i, count = nic->params.rfds.count;

	nic->ru_running = RU_UNINITIALIZED;

	अगर (nic->rxs) अणु
		क्रम (rx = nic->rxs, i = 0; i < count; rx++, i++) अणु
			अगर (rx->skb) अणु
				dma_unmap_single(&nic->pdev->dev,
						 rx->dma_addr, RFD_BUF_LEN,
						 DMA_BIसूचीECTIONAL);
				dev_kमुक्त_skb(rx->skb);
			पूर्ण
		पूर्ण
		kमुक्त(nic->rxs);
		nic->rxs = शून्य;
	पूर्ण

	nic->rx_to_use = nic->rx_to_clean = शून्य;
पूर्ण

अटल पूर्णांक e100_rx_alloc_list(काष्ठा nic *nic)
अणु
	काष्ठा rx *rx;
	अचिन्हित पूर्णांक i, count = nic->params.rfds.count;
	काष्ठा rfd *beक्रमe_last;

	nic->rx_to_use = nic->rx_to_clean = शून्य;
	nic->ru_running = RU_UNINITIALIZED;

	अगर (!(nic->rxs = kसुस्मृति(count, माप(काष्ठा rx), GFP_KERNEL)))
		वापस -ENOMEM;

	क्रम (rx = nic->rxs, i = 0; i < count; rx++, i++) अणु
		rx->next = (i + 1 < count) ? rx + 1 : nic->rxs;
		rx->prev = (i == 0) ? nic->rxs + count - 1 : rx - 1;
		अगर (e100_rx_alloc_skb(nic, rx)) अणु
			e100_rx_clean_list(nic);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	/* Set the el-bit on the buffer that is beक्रमe the last buffer.
	 * This lets us update the next poपूर्णांकer on the last buffer without
	 * worrying about hardware touching it.
	 * We set the size to 0 to prevent hardware from touching this buffer.
	 * When the hardware hits the beक्रमe last buffer with el-bit and size
	 * of 0, it will RNR पूर्णांकerrupt, the RU will go पूर्णांकo the No Resources
	 * state.  It will not complete nor ग_लिखो to this buffer. */
	rx = nic->rxs->prev->prev;
	beक्रमe_last = (काष्ठा rfd *)rx->skb->data;
	beक्रमe_last->command |= cpu_to_le16(cb_el);
	beक्रमe_last->size = 0;
	dma_sync_single_क्रम_device(&nic->pdev->dev, rx->dma_addr,
				   माप(काष्ठा rfd), DMA_BIसूचीECTIONAL);

	nic->rx_to_use = nic->rx_to_clean = nic->rxs;
	nic->ru_running = RU_SUSPENDED;

	वापस 0;
पूर्ण

अटल irqवापस_t e100_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *netdev = dev_id;
	काष्ठा nic *nic = netdev_priv(netdev);
	u8 stat_ack = ioपढ़ो8(&nic->csr->scb.stat_ack);

	netअगर_prपूर्णांकk(nic, पूर्णांकr, KERN_DEBUG, nic->netdev,
		     "stat_ack = 0x%02X\n", stat_ack);

	अगर (stat_ack == stat_ack_not_ours ||	/* Not our पूर्णांकerrupt */
	   stat_ack == stat_ack_not_present)	/* Hardware is ejected */
		वापस IRQ_NONE;

	/* Ack पूर्णांकerrupt(s) */
	ioग_लिखो8(stat_ack, &nic->csr->scb.stat_ack);

	/* We hit Receive No Resource (RNR); restart RU after cleaning */
	अगर (stat_ack & stat_ack_rnr)
		nic->ru_running = RU_SUSPENDED;

	अगर (likely(napi_schedule_prep(&nic->napi))) अणु
		e100_disable_irq(nic);
		__napi_schedule(&nic->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक e100_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा nic *nic = container_of(napi, काष्ठा nic, napi);
	अचिन्हित पूर्णांक work_करोne = 0;

	e100_rx_clean(nic, &work_करोne, budget);
	e100_tx_clean(nic);

	/* If budget fully consumed, जारी polling */
	अगर (work_करोne == budget)
		वापस budget;

	/* only re-enable पूर्णांकerrupt अगर stack agrees polling is really करोne */
	अगर (likely(napi_complete_करोne(napi, work_करोne)))
		e100_enable_irq(nic);

	वापस work_करोne;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम e100_netpoll(काष्ठा net_device *netdev)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);

	e100_disable_irq(nic);
	e100_पूर्णांकr(nic->pdev->irq, netdev);
	e100_tx_clean(nic);
	e100_enable_irq(nic);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक e100_set_mac_address(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	e100_exec_cb(nic, शून्य, e100_setup_iaaddr);

	वापस 0;
पूर्ण

अटल पूर्णांक e100_asf(काष्ठा nic *nic)
अणु
	/* ASF can be enabled from eeprom */
	वापस (nic->pdev->device >= 0x1050) && (nic->pdev->device <= 0x1057) &&
	   (nic->eeprom[eeprom_config_asf] & eeprom_asf) &&
	   !(nic->eeprom[eeprom_config_asf] & eeprom_gcl) &&
	   ((nic->eeprom[eeprom_smbus_addr] & 0xFF) != 0xFE);
पूर्ण

अटल पूर्णांक e100_up(काष्ठा nic *nic)
अणु
	पूर्णांक err;

	अगर ((err = e100_rx_alloc_list(nic)))
		वापस err;
	अगर ((err = e100_alloc_cbs(nic)))
		जाओ err_rx_clean_list;
	अगर ((err = e100_hw_init(nic)))
		जाओ err_clean_cbs;
	e100_set_multicast_list(nic->netdev);
	e100_start_receiver(nic, शून्य);
	mod_समयr(&nic->watchकरोg, jअगरfies);
	अगर ((err = request_irq(nic->pdev->irq, e100_पूर्णांकr, IRQF_SHARED,
		nic->netdev->name, nic->netdev)))
		जाओ err_no_irq;
	netअगर_wake_queue(nic->netdev);
	napi_enable(&nic->napi);
	/* enable पूर्णांकs _after_ enabling poll, preventing a race between
	 * disable पूर्णांकs+schedule */
	e100_enable_irq(nic);
	वापस 0;

err_no_irq:
	del_समयr_sync(&nic->watchकरोg);
err_clean_cbs:
	e100_clean_cbs(nic);
err_rx_clean_list:
	e100_rx_clean_list(nic);
	वापस err;
पूर्ण

अटल व्योम e100_करोwn(काष्ठा nic *nic)
अणु
	/* रुको here क्रम poll to complete */
	napi_disable(&nic->napi);
	netअगर_stop_queue(nic->netdev);
	e100_hw_reset(nic);
	मुक्त_irq(nic->pdev->irq, nic->netdev);
	del_समयr_sync(&nic->watchकरोg);
	netअगर_carrier_off(nic->netdev);
	e100_clean_cbs(nic);
	e100_rx_clean_list(nic);
पूर्ण

अटल व्योम e100_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);

	/* Reset outside of पूर्णांकerrupt context, to aव्योम request_irq
	 * in पूर्णांकerrupt context */
	schedule_work(&nic->tx_समयout_task);
पूर्ण

अटल व्योम e100_tx_समयout_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nic *nic = container_of(work, काष्ठा nic, tx_समयout_task);
	काष्ठा net_device *netdev = nic->netdev;

	netअगर_prपूर्णांकk(nic, tx_err, KERN_DEBUG, nic->netdev,
		     "scb.status=0x%02X\n", ioपढ़ो8(&nic->csr->scb.status));

	rtnl_lock();
	अगर (netअगर_running(netdev)) अणु
		e100_करोwn(netdev_priv(netdev));
		e100_up(netdev_priv(netdev));
	पूर्ण
	rtnl_unlock();
पूर्ण

अटल पूर्णांक e100_loopback_test(काष्ठा nic *nic, क्रमागत loopback loopback_mode)
अणु
	पूर्णांक err;
	काष्ठा sk_buff *skb;

	/* Use driver resources to perक्रमm पूर्णांकernal MAC or PHY
	 * loopback test.  A single packet is prepared and transmitted
	 * in loopback mode, and the test passes अगर the received
	 * packet compares byte-क्रम-byte to the transmitted packet. */

	अगर ((err = e100_rx_alloc_list(nic)))
		वापस err;
	अगर ((err = e100_alloc_cbs(nic)))
		जाओ err_clean_rx;

	/* ICH PHY loopback is broken so करो MAC loopback instead */
	अगर (nic->flags & ich && loopback_mode == lb_phy)
		loopback_mode = lb_mac;

	nic->loopback = loopback_mode;
	अगर ((err = e100_hw_init(nic)))
		जाओ err_loopback_none;

	अगर (loopback_mode == lb_phy)
		mdio_ग_लिखो(nic->netdev, nic->mii.phy_id, MII_BMCR,
			BMCR_LOOPBACK);

	e100_start_receiver(nic, शून्य);

	अगर (!(skb = netdev_alloc_skb(nic->netdev, ETH_DATA_LEN))) अणु
		err = -ENOMEM;
		जाओ err_loopback_none;
	पूर्ण
	skb_put(skb, ETH_DATA_LEN);
	स_रखो(skb->data, 0xFF, ETH_DATA_LEN);
	e100_xmit_frame(skb, nic->netdev);

	msleep(10);

	dma_sync_single_क्रम_cpu(&nic->pdev->dev, nic->rx_to_clean->dma_addr,
				RFD_BUF_LEN, DMA_BIसूचीECTIONAL);

	अगर (स_भेद(nic->rx_to_clean->skb->data + माप(काष्ठा rfd),
	   skb->data, ETH_DATA_LEN))
		err = -EAGAIN;

err_loopback_none:
	mdio_ग_लिखो(nic->netdev, nic->mii.phy_id, MII_BMCR, 0);
	nic->loopback = lb_none;
	e100_clean_cbs(nic);
	e100_hw_reset(nic);
err_clean_rx:
	e100_rx_clean_list(nic);
	वापस err;
पूर्ण

#घोषणा MII_LED_CONTROL	0x1B
#घोषणा E100_82552_LED_OVERRIDE 0x19
#घोषणा E100_82552_LED_ON       0x000F /* LEDTX and LED_RX both on */
#घोषणा E100_82552_LED_OFF      0x000A /* LEDTX and LED_RX both off */

अटल पूर्णांक e100_get_link_ksettings(काष्ठा net_device *netdev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);

	mii_ethtool_get_link_ksettings(&nic->mii, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक e100_set_link_ksettings(काष्ठा net_device *netdev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	पूर्णांक err;

	mdio_ग_लिखो(netdev, nic->mii.phy_id, MII_BMCR, BMCR_RESET);
	err = mii_ethtool_set_link_ksettings(&nic->mii, cmd);
	e100_exec_cb(nic, शून्य, e100_configure);

	वापस err;
पूर्ण

अटल व्योम e100_get_drvinfo(काष्ठा net_device *netdev,
	काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(nic->pdev),
		माप(info->bus_info));
पूर्ण

#घोषणा E100_PHY_REGS 0x1C
अटल पूर्णांक e100_get_regs_len(काष्ठा net_device *netdev)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	वापस 1 + E100_PHY_REGS + माप(nic->mem->dump_buf);
पूर्ण

अटल व्योम e100_get_regs(काष्ठा net_device *netdev,
	काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	u32 *buff = p;
	पूर्णांक i;

	regs->version = (1 << 24) | nic->pdev->revision;
	buff[0] = ioपढ़ो8(&nic->csr->scb.cmd_hi) << 24 |
		ioपढ़ो8(&nic->csr->scb.cmd_lo) << 16 |
		ioपढ़ो16(&nic->csr->scb.status);
	क्रम (i = E100_PHY_REGS; i >= 0; i--)
		buff[1 + E100_PHY_REGS - i] =
			mdio_पढ़ो(netdev, nic->mii.phy_id, i);
	स_रखो(nic->mem->dump_buf, 0, माप(nic->mem->dump_buf));
	e100_exec_cb(nic, शून्य, e100_dump);
	msleep(10);
	स_नकल(&buff[2 + E100_PHY_REGS], nic->mem->dump_buf,
		माप(nic->mem->dump_buf));
पूर्ण

अटल व्योम e100_get_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	wol->supported = (nic->mac >= mac_82558_D101_A4) ?  WAKE_MAGIC : 0;
	wol->wolopts = (nic->flags & wol_magic) ? WAKE_MAGIC : 0;
पूर्ण

अटल पूर्णांक e100_set_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);

	अगर ((wol->wolopts && wol->wolopts != WAKE_MAGIC) ||
	    !device_can_wakeup(&nic->pdev->dev))
		वापस -EOPNOTSUPP;

	अगर (wol->wolopts)
		nic->flags |= wol_magic;
	अन्यथा
		nic->flags &= ~wol_magic;

	device_set_wakeup_enable(&nic->pdev->dev, wol->wolopts);

	e100_exec_cb(nic, शून्य, e100_configure);

	वापस 0;
पूर्ण

अटल u32 e100_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	वापस nic->msg_enable;
पूर्ण

अटल व्योम e100_set_msglevel(काष्ठा net_device *netdev, u32 value)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	nic->msg_enable = value;
पूर्ण

अटल पूर्णांक e100_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	वापस mii_nway_restart(&nic->mii);
पूर्ण

अटल u32 e100_get_link(काष्ठा net_device *netdev)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	वापस mii_link_ok(&nic->mii);
पूर्ण

अटल पूर्णांक e100_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	वापस nic->eeprom_wc << 1;
पूर्ण

#घोषणा E100_EEPROM_MAGIC	0x1234
अटल पूर्णांक e100_get_eeprom(काष्ठा net_device *netdev,
	काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);

	eeprom->magic = E100_EEPROM_MAGIC;
	स_नकल(bytes, &((u8 *)nic->eeprom)[eeprom->offset], eeprom->len);

	वापस 0;
पूर्ण

अटल पूर्णांक e100_set_eeprom(काष्ठा net_device *netdev,
	काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);

	अगर (eeprom->magic != E100_EEPROM_MAGIC)
		वापस -EINVAL;

	स_नकल(&((u8 *)nic->eeprom)[eeprom->offset], bytes, eeprom->len);

	वापस e100_eeprom_save(nic, eeprom->offset >> 1,
		(eeprom->len >> 1) + 1);
पूर्ण

अटल व्योम e100_get_ringparam(काष्ठा net_device *netdev,
	काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	काष्ठा param_range *rfds = &nic->params.rfds;
	काष्ठा param_range *cbs = &nic->params.cbs;

	ring->rx_max_pending = rfds->max;
	ring->tx_max_pending = cbs->max;
	ring->rx_pending = rfds->count;
	ring->tx_pending = cbs->count;
पूर्ण

अटल पूर्णांक e100_set_ringparam(काष्ठा net_device *netdev,
	काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	काष्ठा param_range *rfds = &nic->params.rfds;
	काष्ठा param_range *cbs = &nic->params.cbs;

	अगर ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		वापस -EINVAL;

	अगर (netअगर_running(netdev))
		e100_करोwn(nic);
	rfds->count = max(ring->rx_pending, rfds->min);
	rfds->count = min(rfds->count, rfds->max);
	cbs->count = max(ring->tx_pending, cbs->min);
	cbs->count = min(cbs->count, cbs->max);
	netअगर_info(nic, drv, nic->netdev, "Ring Param settings: rx: %d, tx %d\n",
		   rfds->count, cbs->count);
	अगर (netअगर_running(netdev))
		e100_up(nic);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर e100_gstrings_test[][ETH_GSTRING_LEN] = अणु
	"Link test     (on/offline)",
	"Eeprom test   (on/offline)",
	"Self test        (offline)",
	"Mac loopback     (offline)",
	"Phy loopback     (offline)",
पूर्ण;
#घोषणा E100_TEST_LEN	ARRAY_SIZE(e100_gstrings_test)

अटल व्योम e100_diag_test(काष्ठा net_device *netdev,
	काष्ठा ethtool_test *test, u64 *data)
अणु
	काष्ठा ethtool_cmd cmd;
	काष्ठा nic *nic = netdev_priv(netdev);
	पूर्णांक i;

	स_रखो(data, 0, E100_TEST_LEN * माप(u64));
	data[0] = !mii_link_ok(&nic->mii);
	data[1] = e100_eeprom_load(nic);
	अगर (test->flags & ETH_TEST_FL_OFFLINE) अणु

		/* save speed, duplex & स्वतःneg settings */
		mii_ethtool_gset(&nic->mii, &cmd);

		अगर (netअगर_running(netdev))
			e100_करोwn(nic);
		data[2] = e100_self_test(nic);
		data[3] = e100_loopback_test(nic, lb_mac);
		data[4] = e100_loopback_test(nic, lb_phy);

		/* restore speed, duplex & स्वतःneg settings */
		mii_ethtool_sset(&nic->mii, &cmd);

		अगर (netअगर_running(netdev))
			e100_up(nic);
	पूर्ण
	क्रम (i = 0; i < E100_TEST_LEN; i++)
		test->flags |= data[i] ? ETH_TEST_FL_FAILED : 0;

	msleep_पूर्णांकerruptible(4 * 1000);
पूर्ण

अटल पूर्णांक e100_set_phys_id(काष्ठा net_device *netdev,
			    क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	क्रमागत led_state अणु
		led_on     = 0x01,
		led_off    = 0x04,
		led_on_559 = 0x05,
		led_on_557 = 0x07,
	पूर्ण;
	u16 led_reg = (nic->phy == phy_82552_v) ? E100_82552_LED_OVERRIDE :
		MII_LED_CONTROL;
	u16 leds = 0;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		वापस 2;

	हाल ETHTOOL_ID_ON:
		leds = (nic->phy == phy_82552_v) ? E100_82552_LED_ON :
		       (nic->mac < mac_82559_D101M) ? led_on_557 : led_on_559;
		अवरोध;

	हाल ETHTOOL_ID_OFF:
		leds = (nic->phy == phy_82552_v) ? E100_82552_LED_OFF : led_off;
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		अवरोध;
	पूर्ण

	mdio_ग_लिखो(netdev, nic->mii.phy_id, led_reg, leds);
	वापस 0;
पूर्ण

अटल स्थिर अक्षर e100_gstrings_stats[][ETH_GSTRING_LEN] = अणु
	"rx_packets", "tx_packets", "rx_bytes", "tx_bytes", "rx_errors",
	"tx_errors", "rx_dropped", "tx_dropped", "multicast", "collisions",
	"rx_length_errors", "rx_over_errors", "rx_crc_errors",
	"rx_frame_errors", "rx_fifo_errors", "rx_missed_errors",
	"tx_aborted_errors", "tx_carrier_errors", "tx_fifo_errors",
	"tx_heartbeat_errors", "tx_window_errors",
	/* device-specअगरic stats */
	"tx_deferred", "tx_single_collisions", "tx_multi_collisions",
	"tx_flow_control_pause", "rx_flow_control_pause",
	"rx_flow_control_unsupported", "tx_tco_packets", "rx_tco_packets",
	"rx_short_frame_errors", "rx_over_length_errors",
पूर्ण;
#घोषणा E100_NET_STATS_LEN	21
#घोषणा E100_STATS_LEN	ARRAY_SIZE(e100_gstrings_stats)

अटल पूर्णांक e100_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस E100_TEST_LEN;
	हाल ETH_SS_STATS:
		वापस E100_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम e100_get_ethtool_stats(काष्ठा net_device *netdev,
	काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	पूर्णांक i;

	क्रम (i = 0; i < E100_NET_STATS_LEN; i++)
		data[i] = ((अचिन्हित दीर्घ *)&netdev->stats)[i];

	data[i++] = nic->tx_deferred;
	data[i++] = nic->tx_single_collisions;
	data[i++] = nic->tx_multiple_collisions;
	data[i++] = nic->tx_fc_छोड़ो;
	data[i++] = nic->rx_fc_छोड़ो;
	data[i++] = nic->rx_fc_unsupported;
	data[i++] = nic->tx_tco_frames;
	data[i++] = nic->rx_tco_frames;
	data[i++] = nic->rx_लघु_frame_errors;
	data[i++] = nic->rx_over_length_errors;
पूर्ण

अटल व्योम e100_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *data)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		स_नकल(data, *e100_gstrings_test, माप(e100_gstrings_test));
		अवरोध;
	हाल ETH_SS_STATS:
		स_नकल(data, *e100_gstrings_stats, माप(e100_gstrings_stats));
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ethtool_ops e100_ethtool_ops = अणु
	.get_drvinfo		= e100_get_drvinfo,
	.get_regs_len		= e100_get_regs_len,
	.get_regs		= e100_get_regs,
	.get_wol		= e100_get_wol,
	.set_wol		= e100_set_wol,
	.get_msglevel		= e100_get_msglevel,
	.set_msglevel		= e100_set_msglevel,
	.nway_reset		= e100_nway_reset,
	.get_link		= e100_get_link,
	.get_eeprom_len		= e100_get_eeprom_len,
	.get_eeprom		= e100_get_eeprom,
	.set_eeprom		= e100_set_eeprom,
	.get_ringparam		= e100_get_ringparam,
	.set_ringparam		= e100_set_ringparam,
	.self_test		= e100_diag_test,
	.get_strings		= e100_get_strings,
	.set_phys_id		= e100_set_phys_id,
	.get_ethtool_stats	= e100_get_ethtool_stats,
	.get_sset_count		= e100_get_sset_count,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_link_ksettings	= e100_get_link_ksettings,
	.set_link_ksettings	= e100_set_link_ksettings,
पूर्ण;

अटल पूर्णांक e100_करो_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);

	वापस generic_mii_ioctl(&nic->mii, अगर_mii(अगरr), cmd, शून्य);
पूर्ण

अटल पूर्णांक e100_alloc(काष्ठा nic *nic)
अणु
	nic->mem = dma_alloc_coherent(&nic->pdev->dev, माप(काष्ठा mem),
				      &nic->dma_addr, GFP_KERNEL);
	वापस nic->mem ? 0 : -ENOMEM;
पूर्ण

अटल व्योम e100_मुक्त(काष्ठा nic *nic)
अणु
	अगर (nic->mem) अणु
		dma_मुक्त_coherent(&nic->pdev->dev, माप(काष्ठा mem),
				  nic->mem, nic->dma_addr);
		nic->mem = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक e100_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	पूर्णांक err = 0;

	netअगर_carrier_off(netdev);
	अगर ((err = e100_up(nic)))
		netअगर_err(nic, अगरup, nic->netdev, "Cannot open interface, aborting\n");
	वापस err;
पूर्ण

अटल पूर्णांक e100_बंद(काष्ठा net_device *netdev)
अणु
	e100_करोwn(netdev_priv(netdev));
	वापस 0;
पूर्ण

अटल पूर्णांक e100_set_features(काष्ठा net_device *netdev,
			     netdev_features_t features)
अणु
	काष्ठा nic *nic = netdev_priv(netdev);
	netdev_features_t changed = features ^ netdev->features;

	अगर (!(changed & (NETIF_F_RXFCS | NETIF_F_RXALL)))
		वापस 0;

	netdev->features = features;
	e100_exec_cb(nic, शून्य, e100_configure);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा net_device_ops e100_netdev_ops = अणु
	.nकरो_खोलो		= e100_खोलो,
	.nकरो_stop		= e100_बंद,
	.nकरो_start_xmit		= e100_xmit_frame,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_rx_mode	= e100_set_multicast_list,
	.nकरो_set_mac_address	= e100_set_mac_address,
	.nकरो_करो_ioctl		= e100_करो_ioctl,
	.nकरो_tx_समयout		= e100_tx_समयout,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= e100_netpoll,
#पूर्ण_अगर
	.nकरो_set_features	= e100_set_features,
पूर्ण;

अटल पूर्णांक e100_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा nic *nic;
	पूर्णांक err;

	अगर (!(netdev = alloc_etherdev(माप(काष्ठा nic))))
		वापस -ENOMEM;

	netdev->hw_features |= NETIF_F_RXFCS;
	netdev->priv_flags |= IFF_SUPP_NOFCS;
	netdev->hw_features |= NETIF_F_RXALL;

	netdev->netdev_ops = &e100_netdev_ops;
	netdev->ethtool_ops = &e100_ethtool_ops;
	netdev->watchकरोg_समयo = E100_WATCHDOG_PERIOD;
	म_नकलन(netdev->name, pci_name(pdev), माप(netdev->name) - 1);

	nic = netdev_priv(netdev);
	netअगर_napi_add(netdev, &nic->napi, e100_poll, E100_NAPI_WEIGHT);
	nic->netdev = netdev;
	nic->pdev = pdev;
	nic->msg_enable = (1 << debug) - 1;
	nic->mdio_ctrl = mdio_ctrl_hw;
	pci_set_drvdata(pdev, netdev);

	अगर ((err = pci_enable_device(pdev))) अणु
		netअगर_err(nic, probe, nic->netdev, "Cannot enable PCI device, aborting\n");
		जाओ err_out_मुक्त_dev;
	पूर्ण

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		netअगर_err(nic, probe, nic->netdev, "Cannot find proper PCI device base address, aborting\n");
		err = -ENODEV;
		जाओ err_out_disable_pdev;
	पूर्ण

	अगर ((err = pci_request_regions(pdev, DRV_NAME))) अणु
		netअगर_err(nic, probe, nic->netdev, "Cannot obtain PCI resources, aborting\n");
		जाओ err_out_disable_pdev;
	पूर्ण

	अगर ((err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32)))) अणु
		netअगर_err(nic, probe, nic->netdev, "No usable DMA configuration, aborting\n");
		जाओ err_out_मुक्त_res;
	पूर्ण

	SET_NETDEV_DEV(netdev, &pdev->dev);

	अगर (use_io)
		netअगर_info(nic, probe, nic->netdev, "using i/o access mode\n");

	nic->csr = pci_iomap(pdev, (use_io ? 1 : 0), माप(काष्ठा csr));
	अगर (!nic->csr) अणु
		netअगर_err(nic, probe, nic->netdev, "Cannot map device registers, aborting\n");
		err = -ENOMEM;
		जाओ err_out_मुक्त_res;
	पूर्ण

	अगर (ent->driver_data)
		nic->flags |= ich;
	अन्यथा
		nic->flags &= ~ich;

	e100_get_शेषs(nic);

	/* D100 MAC करोesn't allow rx of vlan packets with normal MTU */
	अगर (nic->mac < mac_82558_D101_A4)
		netdev->features |= NETIF_F_VLAN_CHALLENGED;

	/* locks must be initialized beक्रमe calling hw_reset */
	spin_lock_init(&nic->cb_lock);
	spin_lock_init(&nic->cmd_lock);
	spin_lock_init(&nic->mdio_lock);

	/* Reset the device beक्रमe pci_set_master() in हाल device is in some
	 * funky state and has an पूर्णांकerrupt pending - hपूर्णांक: we करोn't have the
	 * पूर्णांकerrupt handler रेजिस्टरed yet. */
	e100_hw_reset(nic);

	pci_set_master(pdev);

	समयr_setup(&nic->watchकरोg, e100_watchकरोg, 0);

	INIT_WORK(&nic->tx_समयout_task, e100_tx_समयout_task);

	अगर ((err = e100_alloc(nic))) अणु
		netअगर_err(nic, probe, nic->netdev, "Cannot alloc driver memory, aborting\n");
		जाओ err_out_iounmap;
	पूर्ण

	अगर ((err = e100_eeprom_load(nic)))
		जाओ err_out_मुक्त;

	e100_phy_init(nic);

	स_नकल(netdev->dev_addr, nic->eeprom, ETH_ALEN);
	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		अगर (!eeprom_bad_csum_allow) अणु
			netअगर_err(nic, probe, nic->netdev, "Invalid MAC address from EEPROM, aborting\n");
			err = -EAGAIN;
			जाओ err_out_मुक्त;
		पूर्ण अन्यथा अणु
			netअगर_err(nic, probe, nic->netdev, "Invalid MAC address from EEPROM, you MUST configure one.\n");
		पूर्ण
	पूर्ण

	/* Wol magic packet can be enabled from eeprom */
	अगर ((nic->mac >= mac_82558_D101_A4) &&
	   (nic->eeprom[eeprom_id] & eeprom_id_wol)) अणु
		nic->flags |= wol_magic;
		device_set_wakeup_enable(&pdev->dev, true);
	पूर्ण

	/* ack any pending wake events, disable PME */
	pci_pme_active(pdev, false);

	म_नकल(netdev->name, "eth%d");
	अगर ((err = रेजिस्टर_netdev(netdev))) अणु
		netअगर_err(nic, probe, nic->netdev, "Cannot register net device, aborting\n");
		जाओ err_out_मुक्त;
	पूर्ण
	nic->cbs_pool = dma_pool_create(netdev->name,
			   &nic->pdev->dev,
			   nic->params.cbs.max * माप(काष्ठा cb),
			   माप(u32),
			   0);
	अगर (!nic->cbs_pool) अणु
		netअगर_err(nic, probe, nic->netdev, "Cannot create DMA pool, aborting\n");
		err = -ENOMEM;
		जाओ err_out_pool;
	पूर्ण
	netअगर_info(nic, probe, nic->netdev,
		   "addr 0x%llx, irq %d, MAC addr %pM\n",
		   (अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, use_io ? 1 : 0),
		   pdev->irq, netdev->dev_addr);

	वापस 0;

err_out_pool:
	unरेजिस्टर_netdev(netdev);
err_out_मुक्त:
	e100_मुक्त(nic);
err_out_iounmap:
	pci_iounmap(pdev, nic->csr);
err_out_मुक्त_res:
	pci_release_regions(pdev);
err_out_disable_pdev:
	pci_disable_device(pdev);
err_out_मुक्त_dev:
	मुक्त_netdev(netdev);
	वापस err;
पूर्ण

अटल व्योम e100_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);

	अगर (netdev) अणु
		काष्ठा nic *nic = netdev_priv(netdev);
		unरेजिस्टर_netdev(netdev);
		e100_मुक्त(nic);
		pci_iounmap(pdev, nic->csr);
		dma_pool_destroy(nic->cbs_pool);
		मुक्त_netdev(netdev);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
	पूर्ण
पूर्ण

#घोषणा E100_82552_SMARTSPEED   0x14   /* SmartSpeed Ctrl रेजिस्टर */
#घोषणा E100_82552_REV_ANEG     0x0200 /* Reverse स्वतः-negotiation */
#घोषणा E100_82552_ANEG_NOW     0x0400 /* Auto-negotiate now */
अटल व्योम __e100_shutकरोwn(काष्ठा pci_dev *pdev, bool *enable_wake)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा nic *nic = netdev_priv(netdev);

	अगर (netअगर_running(netdev))
		e100_करोwn(nic);
	netअगर_device_detach(netdev);

	अगर ((nic->flags & wol_magic) | e100_asf(nic)) अणु
		/* enable reverse स्वतः-negotiation */
		अगर (nic->phy == phy_82552_v) अणु
			u16 smartspeed = mdio_पढ़ो(netdev, nic->mii.phy_id,
			                           E100_82552_SMARTSPEED);

			mdio_ग_लिखो(netdev, nic->mii.phy_id,
			           E100_82552_SMARTSPEED, smartspeed |
			           E100_82552_REV_ANEG | E100_82552_ANEG_NOW);
		पूर्ण
		*enable_wake = true;
	पूर्ण अन्यथा अणु
		*enable_wake = false;
	पूर्ण

	pci_clear_master(pdev);
पूर्ण

अटल पूर्णांक __e100_घातer_off(काष्ठा pci_dev *pdev, bool wake)
अणु
	अगर (wake)
		वापस pci_prepare_to_sleep(pdev);

	pci_wake_from_d3(pdev, false);
	pci_set_घातer_state(pdev, PCI_D3hot);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused e100_suspend(काष्ठा device *dev_d)
अणु
	bool wake;

	__e100_shutकरोwn(to_pci_dev(dev_d), &wake);

	device_wakeup_disable(dev_d);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused e100_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev_d);
	काष्ठा nic *nic = netdev_priv(netdev);

	/* disable reverse स्वतः-negotiation */
	अगर (nic->phy == phy_82552_v) अणु
		u16 smartspeed = mdio_पढ़ो(netdev, nic->mii.phy_id,
		                           E100_82552_SMARTSPEED);

		mdio_ग_लिखो(netdev, nic->mii.phy_id,
		           E100_82552_SMARTSPEED,
		           smartspeed & ~(E100_82552_REV_ANEG));
	पूर्ण

	netअगर_device_attach(netdev);
	अगर (netअगर_running(netdev))
		e100_up(nic);

	वापस 0;
पूर्ण

अटल व्योम e100_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	bool wake;
	__e100_shutकरोwn(pdev, &wake);
	अगर (प्रणाली_state == SYSTEM_POWER_OFF)
		__e100_घातer_off(pdev, wake);
पूर्ण

/* ------------------ PCI Error Recovery infraकाष्ठाure  -------------- */
/**
 * e100_io_error_detected - called when PCI error is detected.
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 */
अटल pci_ers_result_t e100_io_error_detected(काष्ठा pci_dev *pdev, pci_channel_state_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा nic *nic = netdev_priv(netdev);

	netअगर_device_detach(netdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (netअगर_running(netdev))
		e100_करोwn(nic);
	pci_disable_device(pdev);

	/* Request a slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * e100_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch.
 */
अटल pci_ers_result_t e100_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा nic *nic = netdev_priv(netdev);

	अगर (pci_enable_device(pdev)) अणु
		pr_err("Cannot re-enable PCI device after reset\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
	pci_set_master(pdev);

	/* Only one device per card can करो a reset */
	अगर (0 != PCI_FUNC(pdev->devfn))
		वापस PCI_ERS_RESULT_RECOVERED;
	e100_hw_reset(nic);
	e100_phy_init(nic);

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * e100_io_resume - resume normal operations
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Resume normal operations after an error recovery
 * sequence has been completed.
 */
अटल व्योम e100_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा nic *nic = netdev_priv(netdev);

	/* ack any pending wake events, disable PME */
	pci_enable_wake(pdev, PCI_D0, 0);

	netअगर_device_attach(netdev);
	अगर (netअगर_running(netdev)) अणु
		e100_खोलो(netdev);
		mod_समयr(&nic->watchकरोg, jअगरfies);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers e100_err_handler = अणु
	.error_detected = e100_io_error_detected,
	.slot_reset = e100_io_slot_reset,
	.resume = e100_io_resume,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(e100_pm_ops, e100_suspend, e100_resume);

अटल काष्ठा pci_driver e100_driver = अणु
	.name =         DRV_NAME,
	.id_table =     e100_id_table,
	.probe =        e100_probe,
	.हटाओ =       e100_हटाओ,

	/* Power Management hooks */
	.driver.pm =	&e100_pm_ops,

	.shutकरोwn =     e100_shutकरोwn,
	.err_handler = &e100_err_handler,
पूर्ण;

अटल पूर्णांक __init e100_init_module(व्योम)
अणु
	अगर (((1 << debug) - 1) & NETIF_MSG_DRV) अणु
		pr_info("%s\n", DRV_DESCRIPTION);
		pr_info("%s\n", DRV_COPYRIGHT);
	पूर्ण
	वापस pci_रेजिस्टर_driver(&e100_driver);
पूर्ण

अटल व्योम __निकास e100_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&e100_driver);
पूर्ण

module_init(e100_init_module);
module_निकास(e100_cleanup_module);
