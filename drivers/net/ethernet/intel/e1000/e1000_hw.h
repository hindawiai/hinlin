<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2006 Intel Corporation. */

/* e1000_hw.h
 * Structures, क्रमागतs, and macros क्रम the MAC
 */

#अगर_अघोषित _E1000_HW_H_
#घोषणा _E1000_HW_H_

#समावेश "e1000_osdep.h"


/* Forward declarations of काष्ठाures used by the shared code */
काष्ठा e1000_hw;
काष्ठा e1000_hw_stats;

/* Enumerated types specअगरic to the e1000 hardware */
/* Media Access Controllers */
प्रकार क्रमागत अणु
	e1000_undefined = 0,
	e1000_82542_rev2_0,
	e1000_82542_rev2_1,
	e1000_82543,
	e1000_82544,
	e1000_82540,
	e1000_82545,
	e1000_82545_rev_3,
	e1000_82546,
	e1000_ce4100,
	e1000_82546_rev_3,
	e1000_82541,
	e1000_82541_rev_2,
	e1000_82547,
	e1000_82547_rev_2,
	e1000_num_macs
पूर्ण e1000_mac_type;

प्रकार क्रमागत अणु
	e1000_eeprom_uninitialized = 0,
	e1000_eeprom_spi,
	e1000_eeprom_microwire,
	e1000_eeprom_flash,
	e1000_eeprom_none,	/* No NVM support */
	e1000_num_eeprom_types
पूर्ण e1000_eeprom_type;

/* Media Types */
प्रकार क्रमागत अणु
	e1000_media_type_copper = 0,
	e1000_media_type_fiber = 1,
	e1000_media_type_पूर्णांकernal_serdes = 2,
	e1000_num_media_types
पूर्ण e1000_media_type;

प्रकार क्रमागत अणु
	e1000_10_half = 0,
	e1000_10_full = 1,
	e1000_100_half = 2,
	e1000_100_full = 3
पूर्ण e1000_speed_duplex_type;

/* Flow Control Settings */
प्रकार क्रमागत अणु
	E1000_FC_NONE = 0,
	E1000_FC_RX_PAUSE = 1,
	E1000_FC_TX_PAUSE = 2,
	E1000_FC_FULL = 3,
	E1000_FC_DEFAULT = 0xFF
पूर्ण e1000_fc_type;

काष्ठा e1000_shaकरोw_ram अणु
	u16 eeprom_word;
	bool modअगरied;
पूर्ण;

/* PCI bus types */
प्रकार क्रमागत अणु
	e1000_bus_type_unknown = 0,
	e1000_bus_type_pci,
	e1000_bus_type_pcix,
	e1000_bus_type_reserved
पूर्ण e1000_bus_type;

/* PCI bus speeds */
प्रकार क्रमागत अणु
	e1000_bus_speed_unknown = 0,
	e1000_bus_speed_33,
	e1000_bus_speed_66,
	e1000_bus_speed_100,
	e1000_bus_speed_120,
	e1000_bus_speed_133,
	e1000_bus_speed_reserved
पूर्ण e1000_bus_speed;

/* PCI bus widths */
प्रकार क्रमागत अणु
	e1000_bus_width_unknown = 0,
	e1000_bus_width_32,
	e1000_bus_width_64,
	e1000_bus_width_reserved
पूर्ण e1000_bus_width;

/* PHY status info काष्ठाure and supporting क्रमागतs */
प्रकार क्रमागत अणु
	e1000_cable_length_50 = 0,
	e1000_cable_length_50_80,
	e1000_cable_length_80_110,
	e1000_cable_length_110_140,
	e1000_cable_length_140,
	e1000_cable_length_undefined = 0xFF
पूर्ण e1000_cable_length;

प्रकार क्रमागत अणु
	e1000_gg_cable_length_60 = 0,
	e1000_gg_cable_length_60_115 = 1,
	e1000_gg_cable_length_115_150 = 2,
	e1000_gg_cable_length_150 = 4
पूर्ण e1000_gg_cable_length;

प्रकार क्रमागत अणु
	e1000_igp_cable_length_10 = 10,
	e1000_igp_cable_length_20 = 20,
	e1000_igp_cable_length_30 = 30,
	e1000_igp_cable_length_40 = 40,
	e1000_igp_cable_length_50 = 50,
	e1000_igp_cable_length_60 = 60,
	e1000_igp_cable_length_70 = 70,
	e1000_igp_cable_length_80 = 80,
	e1000_igp_cable_length_90 = 90,
	e1000_igp_cable_length_100 = 100,
	e1000_igp_cable_length_110 = 110,
	e1000_igp_cable_length_115 = 115,
	e1000_igp_cable_length_120 = 120,
	e1000_igp_cable_length_130 = 130,
	e1000_igp_cable_length_140 = 140,
	e1000_igp_cable_length_150 = 150,
	e1000_igp_cable_length_160 = 160,
	e1000_igp_cable_length_170 = 170,
	e1000_igp_cable_length_180 = 180
पूर्ण e1000_igp_cable_length;

प्रकार क्रमागत अणु
	e1000_10bt_ext_dist_enable_normal = 0,
	e1000_10bt_ext_dist_enable_lower,
	e1000_10bt_ext_dist_enable_undefined = 0xFF
पूर्ण e1000_10bt_ext_dist_enable;

प्रकार क्रमागत अणु
	e1000_rev_polarity_normal = 0,
	e1000_rev_polarity_reversed,
	e1000_rev_polarity_undefined = 0xFF
पूर्ण e1000_rev_polarity;

प्रकार क्रमागत अणु
	e1000_करोwnshअगरt_normal = 0,
	e1000_करोwnshअगरt_activated,
	e1000_करोwnshअगरt_undefined = 0xFF
पूर्ण e1000_करोwnshअगरt;

प्रकार क्रमागत अणु
	e1000_smart_speed_शेष = 0,
	e1000_smart_speed_on,
	e1000_smart_speed_off
पूर्ण e1000_smart_speed;

प्रकार क्रमागत अणु
	e1000_polarity_reversal_enabled = 0,
	e1000_polarity_reversal_disabled,
	e1000_polarity_reversal_undefined = 0xFF
पूर्ण e1000_polarity_reversal;

प्रकार क्रमागत अणु
	e1000_स्वतः_x_mode_manual_mdi = 0,
	e1000_स्वतः_x_mode_manual_mdix,
	e1000_स्वतः_x_mode_स्वतः1,
	e1000_स्वतः_x_mode_स्वतः2,
	e1000_स्वतः_x_mode_undefined = 0xFF
पूर्ण e1000_स्वतः_x_mode;

प्रकार क्रमागत अणु
	e1000_1000t_rx_status_not_ok = 0,
	e1000_1000t_rx_status_ok,
	e1000_1000t_rx_status_undefined = 0xFF
पूर्ण e1000_1000t_rx_status;

प्रकार क्रमागत अणु
	e1000_phy_m88 = 0,
	e1000_phy_igp,
	e1000_phy_8211,
	e1000_phy_8201,
	e1000_phy_undefined = 0xFF
पूर्ण e1000_phy_type;

प्रकार क्रमागत अणु
	e1000_ms_hw_शेष = 0,
	e1000_ms_क्रमce_master,
	e1000_ms_क्रमce_slave,
	e1000_ms_स्वतः
पूर्ण e1000_ms_type;

प्रकार क्रमागत अणु
	e1000_ffe_config_enabled = 0,
	e1000_ffe_config_active,
	e1000_ffe_config_blocked
पूर्ण e1000_ffe_config;

प्रकार क्रमागत अणु
	e1000_dsp_config_disabled = 0,
	e1000_dsp_config_enabled,
	e1000_dsp_config_activated,
	e1000_dsp_config_undefined = 0xFF
पूर्ण e1000_dsp_config;

काष्ठा e1000_phy_info अणु
	e1000_cable_length cable_length;
	e1000_10bt_ext_dist_enable extended_10bt_distance;
	e1000_rev_polarity cable_polarity;
	e1000_करोwnshअगरt करोwnshअगरt;
	e1000_polarity_reversal polarity_correction;
	e1000_स्वतः_x_mode mdix_mode;
	e1000_1000t_rx_status local_rx;
	e1000_1000t_rx_status remote_rx;
पूर्ण;

काष्ठा e1000_phy_stats अणु
	u32 idle_errors;
	u32 receive_errors;
पूर्ण;

काष्ठा e1000_eeprom_info अणु
	e1000_eeprom_type type;
	u16 word_size;
	u16 opcode_bits;
	u16 address_bits;
	u16 delay_usec;
	u16 page_size;
पूर्ण;

/* Flex ASF Inक्रमmation */
#घोषणा E1000_HOST_IF_MAX_SIZE  2048

प्रकार क्रमागत अणु
	e1000_byte_align = 0,
	e1000_word_align = 1,
	e1000_dword_align = 2
पूर्ण e1000_align_type;

/* Error Codes */
#घोषणा E1000_SUCCESS      0
#घोषणा E1000_ERR_EEPROM   1
#घोषणा E1000_ERR_PHY      2
#घोषणा E1000_ERR_CONFIG   3
#घोषणा E1000_ERR_PARAM    4
#घोषणा E1000_ERR_MAC_TYPE 5
#घोषणा E1000_ERR_PHY_TYPE 6
#घोषणा E1000_ERR_RESET   9
#घोषणा E1000_ERR_MASTER_REQUESTS_PENDING 10
#घोषणा E1000_ERR_HOST_INTERFACE_COMMAND 11
#घोषणा E1000_BLK_PHY_RESET   12

#घोषणा E1000_BYTE_SWAP_WORD(_value) ((((_value) & 0x00ff) << 8) | \
                                     (((_value) & 0xff00) >> 8))

/* Function prototypes */
/* Initialization */
s32 e1000_reset_hw(काष्ठा e1000_hw *hw);
s32 e1000_init_hw(काष्ठा e1000_hw *hw);
s32 e1000_set_mac_type(काष्ठा e1000_hw *hw);
व्योम e1000_set_media_type(काष्ठा e1000_hw *hw);

/* Link Configuration */
s32 e1000_setup_link(काष्ठा e1000_hw *hw);
s32 e1000_phy_setup_स्वतःneg(काष्ठा e1000_hw *hw);
व्योम e1000_config_collision_dist(काष्ठा e1000_hw *hw);
s32 e1000_check_क्रम_link(काष्ठा e1000_hw *hw);
s32 e1000_get_speed_and_duplex(काष्ठा e1000_hw *hw, u16 * speed, u16 * duplex);
s32 e1000_क्रमce_mac_fc(काष्ठा e1000_hw *hw);

/* PHY */
s32 e1000_पढ़ो_phy_reg(काष्ठा e1000_hw *hw, u32 reg_addr, u16 * phy_data);
s32 e1000_ग_लिखो_phy_reg(काष्ठा e1000_hw *hw, u32 reg_addr, u16 data);
s32 e1000_phy_hw_reset(काष्ठा e1000_hw *hw);
s32 e1000_phy_reset(काष्ठा e1000_hw *hw);
s32 e1000_phy_get_info(काष्ठा e1000_hw *hw, काष्ठा e1000_phy_info *phy_info);
s32 e1000_validate_mdi_setting(काष्ठा e1000_hw *hw);

/* EEPROM Functions */
s32 e1000_init_eeprom_params(काष्ठा e1000_hw *hw);

/* MNG HOST IF functions */
u32 e1000_enable_mng_pass_thru(काष्ठा e1000_hw *hw);

#घोषणा E1000_MNG_DHCP_TX_PAYLOAD_CMD   64
#घोषणा E1000_HI_MAX_MNG_DATA_LENGTH    0x6F8	/* Host Interface data length */

#घोषणा E1000_MNG_DHCP_COMMAND_TIMEOUT  10	/* Time in ms to process MNG command */
#घोषणा E1000_MNG_DHCP_COOKIE_OFFSET    0x6F0	/* Cookie offset */
#घोषणा E1000_MNG_DHCP_COOKIE_LENGTH    0x10	/* Cookie length */
#घोषणा E1000_MNG_IAMT_MODE             0x3
#घोषणा E1000_MNG_ICH_IAMT_MODE         0x2
#घोषणा E1000_IAMT_SIGNATURE            0x544D4149	/* Intel(R) Active Management Technology signature */

#घोषणा E1000_MNG_DHCP_COOKIE_STATUS_PARSING_SUPPORT 0x1	/* DHCP parsing enabled */
#घोषणा E1000_MNG_DHCP_COOKIE_STATUS_VLAN_SUPPORT    0x2	/* DHCP parsing enabled */
#घोषणा E1000_VFTA_ENTRY_SHIFT                       0x5
#घोषणा E1000_VFTA_ENTRY_MASK                        0x7F
#घोषणा E1000_VFTA_ENTRY_BIT_SHIFT_MASK              0x1F

काष्ठा e1000_host_mng_command_header अणु
	u8 command_id;
	u8 checksum;
	u16 reserved1;
	u16 reserved2;
	u16 command_length;
पूर्ण;

काष्ठा e1000_host_mng_command_info अणु
	काष्ठा e1000_host_mng_command_header command_header;	/* Command Head/Command Result Head has 4 bytes */
	u8 command_data[E1000_HI_MAX_MNG_DATA_LENGTH];	/* Command data can length 0..0x658 */
पूर्ण;
#अगर_घोषित __BIG_ENDIAN
काष्ठा e1000_host_mng_dhcp_cookie अणु
	u32 signature;
	u16 vlan_id;
	u8 reserved0;
	u8 status;
	u32 reserved1;
	u8 checksum;
	u8 reserved3;
	u16 reserved2;
पूर्ण;
#अन्यथा
काष्ठा e1000_host_mng_dhcp_cookie अणु
	u32 signature;
	u8 status;
	u8 reserved0;
	u16 vlan_id;
	u32 reserved1;
	u16 reserved2;
	u8 reserved3;
	u8 checksum;
पूर्ण;
#पूर्ण_अगर

bool e1000_check_mng_mode(काष्ठा e1000_hw *hw);
s32 e1000_पढ़ो_eeprom(काष्ठा e1000_hw *hw, u16 reg, u16 words, u16 * data);
s32 e1000_validate_eeprom_checksum(काष्ठा e1000_hw *hw);
s32 e1000_update_eeprom_checksum(काष्ठा e1000_hw *hw);
s32 e1000_ग_लिखो_eeprom(काष्ठा e1000_hw *hw, u16 reg, u16 words, u16 * data);
s32 e1000_पढ़ो_mac_addr(काष्ठा e1000_hw *hw);

/* Filters (multicast, vlan, receive) */
u32 e1000_hash_mc_addr(काष्ठा e1000_hw *hw, u8 * mc_addr);
व्योम e1000_mta_set(काष्ठा e1000_hw *hw, u32 hash_value);
व्योम e1000_rar_set(काष्ठा e1000_hw *hw, u8 * mc_addr, u32 rar_index);
व्योम e1000_ग_लिखो_vfta(काष्ठा e1000_hw *hw, u32 offset, u32 value);

/* LED functions */
s32 e1000_setup_led(काष्ठा e1000_hw *hw);
s32 e1000_cleanup_led(काष्ठा e1000_hw *hw);
s32 e1000_led_on(काष्ठा e1000_hw *hw);
s32 e1000_led_off(काष्ठा e1000_hw *hw);
s32 e1000_blink_led_start(काष्ठा e1000_hw *hw);

/* Adaptive IFS Functions */

/* Everything अन्यथा */
व्योम e1000_reset_adaptive(काष्ठा e1000_hw *hw);
व्योम e1000_update_adaptive(काष्ठा e1000_hw *hw);
व्योम e1000_get_bus_info(काष्ठा e1000_hw *hw);
व्योम e1000_pci_set_mwi(काष्ठा e1000_hw *hw);
व्योम e1000_pci_clear_mwi(काष्ठा e1000_hw *hw);
व्योम e1000_pcix_set_mmrbc(काष्ठा e1000_hw *hw, पूर्णांक mmrbc);
पूर्णांक e1000_pcix_get_mmrbc(काष्ठा e1000_hw *hw);
/* Port I/O is only supported on 82544 and newer */
व्योम e1000_io_ग_लिखो(काष्ठा e1000_hw *hw, अचिन्हित दीर्घ port, u32 value);

#घोषणा E1000_READ_REG_IO(a, reg) \
    e1000_पढ़ो_reg_io((a), E1000_##reg)
#घोषणा E1000_WRITE_REG_IO(a, reg, val) \
    e1000_ग_लिखो_reg_io((a), E1000_##reg, val)

/* PCI Device IDs */
#घोषणा E1000_DEV_ID_82542               0x1000
#घोषणा E1000_DEV_ID_82543GC_FIBER       0x1001
#घोषणा E1000_DEV_ID_82543GC_COPPER      0x1004
#घोषणा E1000_DEV_ID_82544EI_COPPER      0x1008
#घोषणा E1000_DEV_ID_82544EI_FIBER       0x1009
#घोषणा E1000_DEV_ID_82544GC_COPPER      0x100C
#घोषणा E1000_DEV_ID_82544GC_LOM         0x100D
#घोषणा E1000_DEV_ID_82540EM             0x100E
#घोषणा E1000_DEV_ID_82540EM_LOM         0x1015
#घोषणा E1000_DEV_ID_82540EP_LOM         0x1016
#घोषणा E1000_DEV_ID_82540EP             0x1017
#घोषणा E1000_DEV_ID_82540EP_LP          0x101E
#घोषणा E1000_DEV_ID_82545EM_COPPER      0x100F
#घोषणा E1000_DEV_ID_82545EM_FIBER       0x1011
#घोषणा E1000_DEV_ID_82545GM_COPPER      0x1026
#घोषणा E1000_DEV_ID_82545GM_FIBER       0x1027
#घोषणा E1000_DEV_ID_82545GM_SERDES      0x1028
#घोषणा E1000_DEV_ID_82546EB_COPPER      0x1010
#घोषणा E1000_DEV_ID_82546EB_FIBER       0x1012
#घोषणा E1000_DEV_ID_82546EB_QUAD_COPPER 0x101D
#घोषणा E1000_DEV_ID_82541EI             0x1013
#घोषणा E1000_DEV_ID_82541EI_MOBILE      0x1018
#घोषणा E1000_DEV_ID_82541ER_LOM         0x1014
#घोषणा E1000_DEV_ID_82541ER             0x1078
#घोषणा E1000_DEV_ID_82547GI             0x1075
#घोषणा E1000_DEV_ID_82541GI             0x1076
#घोषणा E1000_DEV_ID_82541GI_MOBILE      0x1077
#घोषणा E1000_DEV_ID_82541GI_LF          0x107C
#घोषणा E1000_DEV_ID_82546GB_COPPER      0x1079
#घोषणा E1000_DEV_ID_82546GB_FIBER       0x107A
#घोषणा E1000_DEV_ID_82546GB_SERDES      0x107B
#घोषणा E1000_DEV_ID_82546GB_PCIE        0x108A
#घोषणा E1000_DEV_ID_82546GB_QUAD_COPPER 0x1099
#घोषणा E1000_DEV_ID_82547EI             0x1019
#घोषणा E1000_DEV_ID_82547EI_MOBILE      0x101A
#घोषणा E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3 0x10B5
#घोषणा E1000_DEV_ID_INTEL_CE4100_GBE    0x2E6E

#घोषणा NODE_ADDRESS_SIZE 6

/* MAC decode size is 128K - This is the size of BAR0 */
#घोषणा MAC_DECODE_SIZE (128 * 1024)

#घोषणा E1000_82542_2_0_REV_ID 2
#घोषणा E1000_82542_2_1_REV_ID 3
#घोषणा E1000_REVISION_0       0
#घोषणा E1000_REVISION_1       1
#घोषणा E1000_REVISION_2       2
#घोषणा E1000_REVISION_3       3

#घोषणा SPEED_10    10
#घोषणा SPEED_100   100
#घोषणा SPEED_1000  1000
#घोषणा HALF_DUPLEX 1
#घोषणा FULL_DUPLEX 2

/* The sizes (in bytes) of a ethernet packet */
#घोषणा ENET_HEADER_SIZE             14
#घोषणा MINIMUM_ETHERNET_FRAME_SIZE  64	/* With FCS */
#घोषणा ETHERNET_FCS_SIZE            4
#घोषणा MINIMUM_ETHERNET_PACKET_SIZE \
    (MINIMUM_ETHERNET_FRAME_SIZE - ETHERNET_FCS_SIZE)
#घोषणा CRC_LENGTH                   ETHERNET_FCS_SIZE
#घोषणा MAX_JUMBO_FRAME_SIZE         0x3F00

/* 802.1q VLAN Packet Sizes */
#घोषणा VLAN_TAG_SIZE  4	/* 802.3ac tag (not DMAed) */

/* Ethertype field values */
#घोषणा ETHERNET_IEEE_VLAN_TYPE 0x8100	/* 802.3ac packet */
#घोषणा ETHERNET_IP_TYPE        0x0800	/* IP packets */
#घोषणा ETHERNET_ARP_TYPE       0x0806	/* Address Resolution Protocol (ARP) */

/* Packet Header defines */
#घोषणा IP_PROTOCOL_TCP    6
#घोषणा IP_PROTOCOL_UDP    0x11

/* This defines the bits that are set in the Interrupt Mask
 * Set/Read Register.  Each bit is करोcumented below:
 *   o RXDMT0 = Receive Descriptor Minimum Threshold hit (ring 0)
 *   o RXSEQ  = Receive Sequence Error
 */
#घोषणा POLL_IMS_ENABLE_MASK ( \
    E1000_IMS_RXDMT0 |         \
    E1000_IMS_RXSEQ)

/* This defines the bits that are set in the Interrupt Mask
 * Set/Read Register.  Each bit is करोcumented below:
 *   o RXT0   = Receiver Timer Interrupt (ring 0)
 *   o TXDW   = Transmit Descriptor Written Back
 *   o RXDMT0 = Receive Descriptor Minimum Threshold hit (ring 0)
 *   o RXSEQ  = Receive Sequence Error
 *   o LSC    = Link Status Change
 */
#घोषणा IMS_ENABLE_MASK ( \
    E1000_IMS_RXT0   |    \
    E1000_IMS_TXDW   |    \
    E1000_IMS_RXDMT0 |    \
    E1000_IMS_RXSEQ  |    \
    E1000_IMS_LSC)

/* Number of high/low रेजिस्टर pairs in the RAR. The RAR (Receive Address
 * Registers) holds the directed and multicast addresses that we monitor. We
 * reserve one of these spots क्रम our directed address, allowing us room क्रम
 * E1000_RAR_ENTRIES - 1 multicast addresses.
 */
#घोषणा E1000_RAR_ENTRIES 15

#घोषणा MIN_NUMBER_OF_DESCRIPTORS  8
#घोषणा MAX_NUMBER_OF_DESCRIPTORS  0xFFF8

/* Receive Descriptor */
काष्ठा e1000_rx_desc अणु
	__le64 buffer_addr;	/* Address of the descriptor's data buffer */
	__le16 length;		/* Length of data DMAed पूर्णांकo data buffer */
	__le16 csum;		/* Packet checksum */
	u8 status;		/* Descriptor status */
	u8 errors;		/* Descriptor Errors */
	__le16 special;
पूर्ण;

/* Receive Descriptor - Extended */
जोड़ e1000_rx_desc_extended अणु
	काष्ठा अणु
		__le64 buffer_addr;
		__le64 reserved;
	पूर्ण पढ़ो;
	काष्ठा अणु
		काष्ठा अणु
			__le32 mrq;	/* Multiple Rx Queues */
			जोड़ अणु
				__le32 rss;	/* RSS Hash */
				काष्ठा अणु
					__le16 ip_id;	/* IP id */
					__le16 csum;	/* Packet Checksum */
				पूर्ण csum_ip;
			पूर्ण hi_dword;
		पूर्ण lower;
		काष्ठा अणु
			__le32 status_error;	/* ext status/error */
			__le16 length;
			__le16 vlan;	/* VLAN tag */
		पूर्ण upper;
	पूर्ण wb;			/* ग_लिखोback */
पूर्ण;

#घोषणा MAX_PS_BUFFERS 4
/* Receive Descriptor - Packet Split */
जोड़ e1000_rx_desc_packet_split अणु
	काष्ठा अणु
		/* one buffer क्रम protocol header(s), three data buffers */
		__le64 buffer_addr[MAX_PS_BUFFERS];
	पूर्ण पढ़ो;
	काष्ठा अणु
		काष्ठा अणु
			__le32 mrq;	/* Multiple Rx Queues */
			जोड़ अणु
				__le32 rss;	/* RSS Hash */
				काष्ठा अणु
					__le16 ip_id;	/* IP id */
					__le16 csum;	/* Packet Checksum */
				पूर्ण csum_ip;
			पूर्ण hi_dword;
		पूर्ण lower;
		काष्ठा अणु
			__le32 status_error;	/* ext status/error */
			__le16 length0;	/* length of buffer 0 */
			__le16 vlan;	/* VLAN tag */
		पूर्ण middle;
		काष्ठा अणु
			__le16 header_status;
			__le16 length[3];	/* length of buffers 1-3 */
		पूर्ण upper;
		__le64 reserved;
	पूर्ण wb;			/* ग_लिखोback */
पूर्ण;

/* Receive Descriptor bit definitions */
#घोषणा E1000_RXD_STAT_DD       0x01	/* Descriptor Done */
#घोषणा E1000_RXD_STAT_EOP      0x02	/* End of Packet */
#घोषणा E1000_RXD_STAT_IXSM     0x04	/* Ignore checksum */
#घोषणा E1000_RXD_STAT_VP       0x08	/* IEEE VLAN Packet */
#घोषणा E1000_RXD_STAT_UDPCS    0x10	/* UDP xsum calculated */
#घोषणा E1000_RXD_STAT_TCPCS    0x20	/* TCP xsum calculated */
#घोषणा E1000_RXD_STAT_IPCS     0x40	/* IP xsum calculated */
#घोषणा E1000_RXD_STAT_PIF      0x80	/* passed in-exact filter */
#घोषणा E1000_RXD_STAT_IPIDV    0x200	/* IP identअगरication valid */
#घोषणा E1000_RXD_STAT_UDPV     0x400	/* Valid UDP checksum */
#घोषणा E1000_RXD_STAT_ACK      0x8000	/* ACK Packet indication */
#घोषणा E1000_RXD_ERR_CE        0x01	/* CRC Error */
#घोषणा E1000_RXD_ERR_SE        0x02	/* Symbol Error */
#घोषणा E1000_RXD_ERR_SEQ       0x04	/* Sequence Error */
#घोषणा E1000_RXD_ERR_CXE       0x10	/* Carrier Extension Error */
#घोषणा E1000_RXD_ERR_TCPE      0x20	/* TCP/UDP Checksum Error */
#घोषणा E1000_RXD_ERR_IPE       0x40	/* IP Checksum Error */
#घोषणा E1000_RXD_ERR_RXE       0x80	/* Rx Data Error */
#घोषणा E1000_RXD_SPC_VLAN_MASK 0x0FFF	/* VLAN ID is in lower 12 bits */
#घोषणा E1000_RXD_SPC_PRI_MASK  0xE000	/* Priority is in upper 3 bits */
#घोषणा E1000_RXD_SPC_PRI_SHIFT 13
#घोषणा E1000_RXD_SPC_CFI_MASK  0x1000	/* CFI is bit 12 */
#घोषणा E1000_RXD_SPC_CFI_SHIFT 12

#घोषणा E1000_RXDEXT_STATERR_CE    0x01000000
#घोषणा E1000_RXDEXT_STATERR_SE    0x02000000
#घोषणा E1000_RXDEXT_STATERR_SEQ   0x04000000
#घोषणा E1000_RXDEXT_STATERR_CXE   0x10000000
#घोषणा E1000_RXDEXT_STATERR_TCPE  0x20000000
#घोषणा E1000_RXDEXT_STATERR_IPE   0x40000000
#घोषणा E1000_RXDEXT_STATERR_RXE   0x80000000

#घोषणा E1000_RXDPS_HDRSTAT_HDRSP        0x00008000
#घोषणा E1000_RXDPS_HDRSTAT_HDRLEN_MASK  0x000003FF

/* mask to determine अगर packets should be dropped due to frame errors */
#घोषणा E1000_RXD_ERR_FRAME_ERR_MASK ( \
    E1000_RXD_ERR_CE  |                \
    E1000_RXD_ERR_SE  |                \
    E1000_RXD_ERR_SEQ |                \
    E1000_RXD_ERR_CXE |                \
    E1000_RXD_ERR_RXE)

/* Same mask, but क्रम extended and packet split descriptors */
#घोषणा E1000_RXDEXT_ERR_FRAME_ERR_MASK ( \
    E1000_RXDEXT_STATERR_CE  |            \
    E1000_RXDEXT_STATERR_SE  |            \
    E1000_RXDEXT_STATERR_SEQ |            \
    E1000_RXDEXT_STATERR_CXE |            \
    E1000_RXDEXT_STATERR_RXE)

/* Transmit Descriptor */
काष्ठा e1000_tx_desc अणु
	__le64 buffer_addr;	/* Address of the descriptor's data buffer */
	जोड़ अणु
		__le32 data;
		काष्ठा अणु
			__le16 length;	/* Data buffer length */
			u8 cso;	/* Checksum offset */
			u8 cmd;	/* Descriptor control */
		पूर्ण flags;
	पूर्ण lower;
	जोड़ अणु
		__le32 data;
		काष्ठा अणु
			u8 status;	/* Descriptor status */
			u8 css;	/* Checksum start */
			__le16 special;
		पूर्ण fields;
	पूर्ण upper;
पूर्ण;

/* Transmit Descriptor bit definitions */
#घोषणा E1000_TXD_DTYP_D     0x00100000	/* Data Descriptor */
#घोषणा E1000_TXD_DTYP_C     0x00000000	/* Context Descriptor */
#घोषणा E1000_TXD_POPTS_IXSM 0x01	/* Insert IP checksum */
#घोषणा E1000_TXD_POPTS_TXSM 0x02	/* Insert TCP/UDP checksum */
#घोषणा E1000_TXD_CMD_EOP    0x01000000	/* End of Packet */
#घोषणा E1000_TXD_CMD_IFCS   0x02000000	/* Insert FCS (Ethernet CRC) */
#घोषणा E1000_TXD_CMD_IC     0x04000000	/* Insert Checksum */
#घोषणा E1000_TXD_CMD_RS     0x08000000	/* Report Status */
#घोषणा E1000_TXD_CMD_RPS    0x10000000	/* Report Packet Sent */
#घोषणा E1000_TXD_CMD_DEXT   0x20000000	/* Descriptor extension (0 = legacy) */
#घोषणा E1000_TXD_CMD_VLE    0x40000000	/* Add VLAN tag */
#घोषणा E1000_TXD_CMD_IDE    0x80000000	/* Enable Tidv रेजिस्टर */
#घोषणा E1000_TXD_STAT_DD    0x00000001	/* Descriptor Done */
#घोषणा E1000_TXD_STAT_EC    0x00000002	/* Excess Collisions */
#घोषणा E1000_TXD_STAT_LC    0x00000004	/* Late Collisions */
#घोषणा E1000_TXD_STAT_TU    0x00000008	/* Transmit underrun */
#घोषणा E1000_TXD_CMD_TCP    0x01000000	/* TCP packet */
#घोषणा E1000_TXD_CMD_IP     0x02000000	/* IP packet */
#घोषणा E1000_TXD_CMD_TSE    0x04000000	/* TCP Seg enable */
#घोषणा E1000_TXD_STAT_TC    0x00000004	/* Tx Underrun */

/* Offload Context Descriptor */
काष्ठा e1000_context_desc अणु
	जोड़ अणु
		__le32 ip_config;
		काष्ठा अणु
			u8 ipcss;	/* IP checksum start */
			u8 ipcso;	/* IP checksum offset */
			__le16 ipcse;	/* IP checksum end */
		पूर्ण ip_fields;
	पूर्ण lower_setup;
	जोड़ अणु
		__le32 tcp_config;
		काष्ठा अणु
			u8 tucss;	/* TCP checksum start */
			u8 tucso;	/* TCP checksum offset */
			__le16 tucse;	/* TCP checksum end */
		पूर्ण tcp_fields;
	पूर्ण upper_setup;
	__le32 cmd_and_length;	/* */
	जोड़ अणु
		__le32 data;
		काष्ठा अणु
			u8 status;	/* Descriptor status */
			u8 hdr_len;	/* Header length */
			__le16 mss;	/* Maximum segment size */
		पूर्ण fields;
	पूर्ण tcp_seg_setup;
पूर्ण;

/* Offload data descriptor */
काष्ठा e1000_data_desc अणु
	__le64 buffer_addr;	/* Address of the descriptor's buffer address */
	जोड़ अणु
		__le32 data;
		काष्ठा अणु
			__le16 length;	/* Data buffer length */
			u8 typ_len_ext;	/* */
			u8 cmd;	/* */
		पूर्ण flags;
	पूर्ण lower;
	जोड़ अणु
		__le32 data;
		काष्ठा अणु
			u8 status;	/* Descriptor status */
			u8 popts;	/* Packet Options */
			__le16 special;	/* */
		पूर्ण fields;
	पूर्ण upper;
पूर्ण;

/* Filters */
#घोषणा E1000_NUM_UNICAST          16	/* Unicast filter entries */
#घोषणा E1000_MC_TBL_SIZE          128	/* Multicast Filter Table (4096 bits) */
#घोषणा E1000_VLAN_FILTER_TBL_SIZE 128	/* VLAN Filter Table (4096 bits) */

/* Receive Address Register */
काष्ठा e1000_rar अणु
	अस्थिर __le32 low;	/* receive address low */
	अस्थिर __le32 high;	/* receive address high */
पूर्ण;

/* Number of entries in the Multicast Table Array (MTA). */
#घोषणा E1000_NUM_MTA_REGISTERS 128

/* IPv4 Address Table Entry */
काष्ठा e1000_ipv4_at_entry अणु
	अस्थिर u32 ipv4_addr;	/* IP Address (RW) */
	अस्थिर u32 reserved;
पूर्ण;

/* Four wakeup IP addresses are supported */
#घोषणा E1000_WAKEUP_IP_ADDRESS_COUNT_MAX 4
#घोषणा E1000_IP4AT_SIZE                  E1000_WAKEUP_IP_ADDRESS_COUNT_MAX
#घोषणा E1000_IP6AT_SIZE                  1

/* IPv6 Address Table Entry */
काष्ठा e1000_ipv6_at_entry अणु
	अस्थिर u8 ipv6_addr[16];
पूर्ण;

/* Flexible Filter Length Table Entry */
काष्ठा e1000_fflt_entry अणु
	अस्थिर u32 length;	/* Flexible Filter Length (RW) */
	अस्थिर u32 reserved;
पूर्ण;

/* Flexible Filter Mask Table Entry */
काष्ठा e1000_ffmt_entry अणु
	अस्थिर u32 mask;	/* Flexible Filter Mask (RW) */
	अस्थिर u32 reserved;
पूर्ण;

/* Flexible Filter Value Table Entry */
काष्ठा e1000_ffvt_entry अणु
	अस्थिर u32 value;	/* Flexible Filter Value (RW) */
	अस्थिर u32 reserved;
पूर्ण;

/* Four Flexible Filters are supported */
#घोषणा E1000_FLEXIBLE_FILTER_COUNT_MAX 4

/* Each Flexible Filter is at most 128 (0x80) bytes in length */
#घोषणा E1000_FLEXIBLE_FILTER_SIZE_MAX  128

#घोषणा E1000_FFLT_SIZE E1000_FLEXIBLE_FILTER_COUNT_MAX
#घोषणा E1000_FFMT_SIZE E1000_FLEXIBLE_FILTER_SIZE_MAX
#घोषणा E1000_FFVT_SIZE E1000_FLEXIBLE_FILTER_SIZE_MAX

#घोषणा E1000_DISABLE_SERDES_LOOPBACK   0x0400

/* Register Set. (82543, 82544)
 *
 * Registers are defined to be 32 bits and  should be accessed as 32 bit values.
 * These रेजिस्टरs are physically located on the NIC, but are mapped पूर्णांकo the
 * host memory address space.
 *
 * RW - रेजिस्टर is both पढ़ोable and writable
 * RO - रेजिस्टर is पढ़ो only
 * WO - रेजिस्टर is ग_लिखो only
 * R/clr - रेजिस्टर is पढ़ो only and is cleared when पढ़ो
 * A - रेजिस्टर array
 */
#घोषणा E1000_CTRL     0x00000	/* Device Control - RW */
#घोषणा E1000_CTRL_DUP 0x00004	/* Device Control Duplicate (Shaकरोw) - RW */
#घोषणा E1000_STATUS   0x00008	/* Device Status - RO */
#घोषणा E1000_EECD     0x00010	/* EEPROM/Flash Control - RW */
#घोषणा E1000_EERD     0x00014	/* EEPROM Read - RW */
#घोषणा E1000_CTRL_EXT 0x00018	/* Extended Device Control - RW */
#घोषणा E1000_FLA      0x0001C	/* Flash Access - RW */
#घोषणा E1000_MDIC     0x00020	/* MDI Control - RW */

#घोषणा INTEL_CE_GBE_MDIO_RCOMP_BASE    (hw->ce4100_gbe_mdio_base_virt)
#घोषणा E1000_MDIO_STS  (INTEL_CE_GBE_MDIO_RCOMP_BASE + 0)
#घोषणा E1000_MDIO_CMD  (INTEL_CE_GBE_MDIO_RCOMP_BASE + 4)
#घोषणा E1000_MDIO_DRV  (INTEL_CE_GBE_MDIO_RCOMP_BASE + 8)
#घोषणा E1000_MDC_CMD   (INTEL_CE_GBE_MDIO_RCOMP_BASE + 0xC)
#घोषणा E1000_RCOMP_CTL (INTEL_CE_GBE_MDIO_RCOMP_BASE + 0x20)
#घोषणा E1000_RCOMP_STS (INTEL_CE_GBE_MDIO_RCOMP_BASE + 0x24)

#घोषणा E1000_SCTL     0x00024	/* SerDes Control - RW */
#घोषणा E1000_FEXTNVM  0x00028	/* Future Extended NVM रेजिस्टर */
#घोषणा E1000_FCAL     0x00028	/* Flow Control Address Low - RW */
#घोषणा E1000_FCAH     0x0002C	/* Flow Control Address High -RW */
#घोषणा E1000_FCT      0x00030	/* Flow Control Type - RW */
#घोषणा E1000_VET      0x00038	/* VLAN Ether Type - RW */
#घोषणा E1000_ICR      0x000C0	/* Interrupt Cause Read - R/clr */
#घोषणा E1000_ITR      0x000C4	/* Interrupt Throttling Rate - RW */
#घोषणा E1000_ICS      0x000C8	/* Interrupt Cause Set - WO */
#घोषणा E1000_IMS      0x000D0	/* Interrupt Mask Set - RW */
#घोषणा E1000_IMC      0x000D8	/* Interrupt Mask Clear - WO */
#घोषणा E1000_IAM      0x000E0	/* Interrupt Acknowledge Auto Mask */

/* Auxiliary Control Register. This रेजिस्टर is CE4100 specअगरic,
 * RMII/RGMII function is चयनed by this रेजिस्टर - RW
 * Following are bits definitions of the Auxiliary Control Register
 */
#घोषणा E1000_CTL_AUX  0x000E0
#घोषणा E1000_CTL_AUX_END_SEL_SHIFT     10
#घोषणा E1000_CTL_AUX_ENDIANESS_SHIFT   8
#घोषणा E1000_CTL_AUX_RGMII_RMII_SHIFT  0

/* descriptor and packet transfer use CTL_AUX.ENDIANESS */
#घोषणा E1000_CTL_AUX_DES_PKT   (0x0 << E1000_CTL_AUX_END_SEL_SHIFT)
/* descriptor use CTL_AUX.ENDIANESS, packet use शेष */
#घोषणा E1000_CTL_AUX_DES       (0x1 << E1000_CTL_AUX_END_SEL_SHIFT)
/* descriptor use शेष, packet use CTL_AUX.ENDIANESS */
#घोषणा E1000_CTL_AUX_PKT       (0x2 << E1000_CTL_AUX_END_SEL_SHIFT)
/* all use CTL_AUX.ENDIANESS */
#घोषणा E1000_CTL_AUX_ALL       (0x3 << E1000_CTL_AUX_END_SEL_SHIFT)

#घोषणा E1000_CTL_AUX_RGMII     (0x0 << E1000_CTL_AUX_RGMII_RMII_SHIFT)
#घोषणा E1000_CTL_AUX_RMII      (0x1 << E1000_CTL_AUX_RGMII_RMII_SHIFT)

/* LW little endian, Byte big endian */
#घोषणा E1000_CTL_AUX_LWLE_BBE  (0x0 << E1000_CTL_AUX_ENDIANESS_SHIFT)
#घोषणा E1000_CTL_AUX_LWLE_BLE  (0x1 << E1000_CTL_AUX_ENDIANESS_SHIFT)
#घोषणा E1000_CTL_AUX_LWBE_BBE  (0x2 << E1000_CTL_AUX_ENDIANESS_SHIFT)
#घोषणा E1000_CTL_AUX_LWBE_BLE  (0x3 << E1000_CTL_AUX_ENDIANESS_SHIFT)

#घोषणा E1000_RCTL     0x00100	/* RX Control - RW */
#घोषणा E1000_RDTR1    0x02820	/* RX Delay Timer (1) - RW */
#घोषणा E1000_RDBAL1   0x02900	/* RX Descriptor Base Address Low (1) - RW */
#घोषणा E1000_RDBAH1   0x02904	/* RX Descriptor Base Address High (1) - RW */
#घोषणा E1000_RDLEN1   0x02908	/* RX Descriptor Length (1) - RW */
#घोषणा E1000_RDH1     0x02910	/* RX Descriptor Head (1) - RW */
#घोषणा E1000_RDT1     0x02918	/* RX Descriptor Tail (1) - RW */
#घोषणा E1000_FCTTV    0x00170	/* Flow Control Transmit Timer Value - RW */
#घोषणा E1000_TXCW     0x00178	/* TX Configuration Word - RW */
#घोषणा E1000_RXCW     0x00180	/* RX Configuration Word - RO */
#घोषणा E1000_TCTL     0x00400	/* TX Control - RW */
#घोषणा E1000_TCTL_EXT 0x00404	/* Extended TX Control - RW */
#घोषणा E1000_TIPG     0x00410	/* TX Inter-packet gap -RW */
#घोषणा E1000_TBT      0x00448	/* TX Burst Timer - RW */
#घोषणा E1000_AIT      0x00458	/* Adaptive Interframe Spacing Throttle - RW */
#घोषणा E1000_LEDCTL   0x00E00	/* LED Control - RW */
#घोषणा E1000_EXTCNF_CTRL  0x00F00	/* Extended Configuration Control */
#घोषणा E1000_EXTCNF_SIZE  0x00F08	/* Extended Configuration Size */
#घोषणा E1000_PHY_CTRL     0x00F10	/* PHY Control Register in CSR */
#घोषणा FEXTNVM_SW_CONFIG  0x0001
#घोषणा E1000_PBA      0x01000	/* Packet Buffer Allocation - RW */
#घोषणा E1000_PBS      0x01008	/* Packet Buffer Size */
#घोषणा E1000_EEMNGCTL 0x01010	/* MNG EEprom Control */
#घोषणा E1000_FLASH_UPDATES 1000
#घोषणा E1000_EEARBC   0x01024	/* EEPROM Auto Read Bus Control */
#घोषणा E1000_FLASHT   0x01028	/* FLASH Timer Register */
#घोषणा E1000_EEWR     0x0102C	/* EEPROM Write Register - RW */
#घोषणा E1000_FLSWCTL  0x01030	/* FLASH control रेजिस्टर */
#घोषणा E1000_FLSWDATA 0x01034	/* FLASH data रेजिस्टर */
#घोषणा E1000_FLSWCNT  0x01038	/* FLASH Access Counter */
#घोषणा E1000_FLOP     0x0103C	/* FLASH Opcode Register */
#घोषणा E1000_ERT      0x02008	/* Early Rx Threshold - RW */
#घोषणा E1000_FCRTL    0x02160	/* Flow Control Receive Threshold Low - RW */
#घोषणा E1000_FCRTH    0x02168	/* Flow Control Receive Threshold High - RW */
#घोषणा E1000_PSRCTL   0x02170	/* Packet Split Receive Control - RW */
#घोषणा E1000_RDFH     0x02410  /* RX Data FIFO Head - RW */
#घोषणा E1000_RDFT     0x02418  /* RX Data FIFO Tail - RW */
#घोषणा E1000_RDFHS    0x02420  /* RX Data FIFO Head Saved - RW */
#घोषणा E1000_RDFTS    0x02428  /* RX Data FIFO Tail Saved - RW */
#घोषणा E1000_RDFPC    0x02430  /* RX Data FIFO Packet Count - RW */
#घोषणा E1000_RDBAL    0x02800	/* RX Descriptor Base Address Low - RW */
#घोषणा E1000_RDBAH    0x02804	/* RX Descriptor Base Address High - RW */
#घोषणा E1000_RDLEN    0x02808	/* RX Descriptor Length - RW */
#घोषणा E1000_RDH      0x02810	/* RX Descriptor Head - RW */
#घोषणा E1000_RDT      0x02818	/* RX Descriptor Tail - RW */
#घोषणा E1000_RDTR     0x02820	/* RX Delay Timer - RW */
#घोषणा E1000_RDBAL0   E1000_RDBAL	/* RX Desc Base Address Low (0) - RW */
#घोषणा E1000_RDBAH0   E1000_RDBAH	/* RX Desc Base Address High (0) - RW */
#घोषणा E1000_RDLEN0   E1000_RDLEN	/* RX Desc Length (0) - RW */
#घोषणा E1000_RDH0     E1000_RDH	/* RX Desc Head (0) - RW */
#घोषणा E1000_RDT0     E1000_RDT	/* RX Desc Tail (0) - RW */
#घोषणा E1000_RDTR0    E1000_RDTR	/* RX Delay Timer (0) - RW */
#घोषणा E1000_RXDCTL   0x02828	/* RX Descriptor Control queue 0 - RW */
#घोषणा E1000_RXDCTL1  0x02928	/* RX Descriptor Control queue 1 - RW */
#घोषणा E1000_RADV     0x0282C	/* RX Interrupt Absolute Delay Timer - RW */
#घोषणा E1000_RSRPD    0x02C00	/* RX Small Packet Detect - RW */
#घोषणा E1000_RAID     0x02C08	/* Receive Ack Interrupt Delay - RW */
#घोषणा E1000_TXDMAC   0x03000	/* TX DMA Control - RW */
#घोषणा E1000_KABGTXD  0x03004	/* AFE Band Gap Transmit Ref Data */
#घोषणा E1000_TDFH     0x03410	/* TX Data FIFO Head - RW */
#घोषणा E1000_TDFT     0x03418	/* TX Data FIFO Tail - RW */
#घोषणा E1000_TDFHS    0x03420	/* TX Data FIFO Head Saved - RW */
#घोषणा E1000_TDFTS    0x03428	/* TX Data FIFO Tail Saved - RW */
#घोषणा E1000_TDFPC    0x03430	/* TX Data FIFO Packet Count - RW */
#घोषणा E1000_TDBAL    0x03800	/* TX Descriptor Base Address Low - RW */
#घोषणा E1000_TDBAH    0x03804	/* TX Descriptor Base Address High - RW */
#घोषणा E1000_TDLEN    0x03808	/* TX Descriptor Length - RW */
#घोषणा E1000_TDH      0x03810	/* TX Descriptor Head - RW */
#घोषणा E1000_TDT      0x03818	/* TX Descripotr Tail - RW */
#घोषणा E1000_TIDV     0x03820	/* TX Interrupt Delay Value - RW */
#घोषणा E1000_TXDCTL   0x03828	/* TX Descriptor Control - RW */
#घोषणा E1000_TADV     0x0382C	/* TX Interrupt Absolute Delay Val - RW */
#घोषणा E1000_TSPMT    0x03830	/* TCP Segmentation PAD & Min Threshold - RW */
#घोषणा E1000_TARC0    0x03840	/* TX Arbitration Count (0) */
#घोषणा E1000_TDBAL1   0x03900	/* TX Desc Base Address Low (1) - RW */
#घोषणा E1000_TDBAH1   0x03904	/* TX Desc Base Address High (1) - RW */
#घोषणा E1000_TDLEN1   0x03908	/* TX Desc Length (1) - RW */
#घोषणा E1000_TDH1     0x03910	/* TX Desc Head (1) - RW */
#घोषणा E1000_TDT1     0x03918	/* TX Desc Tail (1) - RW */
#घोषणा E1000_TXDCTL1  0x03928	/* TX Descriptor Control (1) - RW */
#घोषणा E1000_TARC1    0x03940	/* TX Arbitration Count (1) */
#घोषणा E1000_CRCERRS  0x04000	/* CRC Error Count - R/clr */
#घोषणा E1000_ALGNERRC 0x04004	/* Alignment Error Count - R/clr */
#घोषणा E1000_SYMERRS  0x04008	/* Symbol Error Count - R/clr */
#घोषणा E1000_RXERRC   0x0400C	/* Receive Error Count - R/clr */
#घोषणा E1000_MPC      0x04010	/* Missed Packet Count - R/clr */
#घोषणा E1000_SCC      0x04014	/* Single Collision Count - R/clr */
#घोषणा E1000_ECOL     0x04018	/* Excessive Collision Count - R/clr */
#घोषणा E1000_MCC      0x0401C	/* Multiple Collision Count - R/clr */
#घोषणा E1000_LATECOL  0x04020	/* Late Collision Count - R/clr */
#घोषणा E1000_COLC     0x04028	/* Collision Count - R/clr */
#घोषणा E1000_DC       0x04030	/* Defer Count - R/clr */
#घोषणा E1000_TNCRS    0x04034	/* TX-No CRS - R/clr */
#घोषणा E1000_SEC      0x04038	/* Sequence Error Count - R/clr */
#घोषणा E1000_CEXTERR  0x0403C	/* Carrier Extension Error Count - R/clr */
#घोषणा E1000_RLEC     0x04040	/* Receive Length Error Count - R/clr */
#घोषणा E1000_XONRXC   0x04048	/* XON RX Count - R/clr */
#घोषणा E1000_XONTXC   0x0404C	/* XON TX Count - R/clr */
#घोषणा E1000_XOFFRXC  0x04050	/* XOFF RX Count - R/clr */
#घोषणा E1000_XOFFTXC  0x04054	/* XOFF TX Count - R/clr */
#घोषणा E1000_FCRUC    0x04058	/* Flow Control RX Unsupported Count- R/clr */
#घोषणा E1000_PRC64    0x0405C	/* Packets RX (64 bytes) - R/clr */
#घोषणा E1000_PRC127   0x04060	/* Packets RX (65-127 bytes) - R/clr */
#घोषणा E1000_PRC255   0x04064	/* Packets RX (128-255 bytes) - R/clr */
#घोषणा E1000_PRC511   0x04068	/* Packets RX (255-511 bytes) - R/clr */
#घोषणा E1000_PRC1023  0x0406C	/* Packets RX (512-1023 bytes) - R/clr */
#घोषणा E1000_PRC1522  0x04070	/* Packets RX (1024-1522 bytes) - R/clr */
#घोषणा E1000_GPRC     0x04074	/* Good Packets RX Count - R/clr */
#घोषणा E1000_BPRC     0x04078	/* Broadcast Packets RX Count - R/clr */
#घोषणा E1000_MPRC     0x0407C	/* Multicast Packets RX Count - R/clr */
#घोषणा E1000_GPTC     0x04080	/* Good Packets TX Count - R/clr */
#घोषणा E1000_GORCL    0x04088	/* Good Octets RX Count Low - R/clr */
#घोषणा E1000_GORCH    0x0408C	/* Good Octets RX Count High - R/clr */
#घोषणा E1000_GOTCL    0x04090	/* Good Octets TX Count Low - R/clr */
#घोषणा E1000_GOTCH    0x04094	/* Good Octets TX Count High - R/clr */
#घोषणा E1000_RNBC     0x040A0	/* RX No Buffers Count - R/clr */
#घोषणा E1000_RUC      0x040A4	/* RX Undersize Count - R/clr */
#घोषणा E1000_RFC      0x040A8	/* RX Fragment Count - R/clr */
#घोषणा E1000_ROC      0x040AC	/* RX Oversize Count - R/clr */
#घोषणा E1000_RJC      0x040B0	/* RX Jabber Count - R/clr */
#घोषणा E1000_MGTPRC   0x040B4	/* Management Packets RX Count - R/clr */
#घोषणा E1000_MGTPDC   0x040B8	/* Management Packets Dropped Count - R/clr */
#घोषणा E1000_MGTPTC   0x040BC	/* Management Packets TX Count - R/clr */
#घोषणा E1000_TORL     0x040C0	/* Total Octets RX Low - R/clr */
#घोषणा E1000_TORH     0x040C4	/* Total Octets RX High - R/clr */
#घोषणा E1000_TOTL     0x040C8	/* Total Octets TX Low - R/clr */
#घोषणा E1000_TOTH     0x040CC	/* Total Octets TX High - R/clr */
#घोषणा E1000_TPR      0x040D0	/* Total Packets RX - R/clr */
#घोषणा E1000_TPT      0x040D4	/* Total Packets TX - R/clr */
#घोषणा E1000_PTC64    0x040D8	/* Packets TX (64 bytes) - R/clr */
#घोषणा E1000_PTC127   0x040DC	/* Packets TX (65-127 bytes) - R/clr */
#घोषणा E1000_PTC255   0x040E0	/* Packets TX (128-255 bytes) - R/clr */
#घोषणा E1000_PTC511   0x040E4	/* Packets TX (256-511 bytes) - R/clr */
#घोषणा E1000_PTC1023  0x040E8	/* Packets TX (512-1023 bytes) - R/clr */
#घोषणा E1000_PTC1522  0x040EC	/* Packets TX (1024-1522 Bytes) - R/clr */
#घोषणा E1000_MPTC     0x040F0	/* Multicast Packets TX Count - R/clr */
#घोषणा E1000_BPTC     0x040F4	/* Broadcast Packets TX Count - R/clr */
#घोषणा E1000_TSCTC    0x040F8	/* TCP Segmentation Context TX - R/clr */
#घोषणा E1000_TSCTFC   0x040FC	/* TCP Segmentation Context TX Fail - R/clr */
#घोषणा E1000_IAC      0x04100	/* Interrupt Assertion Count */
#घोषणा E1000_ICRXPTC  0x04104	/* Interrupt Cause Rx Packet Timer Expire Count */
#घोषणा E1000_ICRXATC  0x04108	/* Interrupt Cause Rx Absolute Timer Expire Count */
#घोषणा E1000_ICTXPTC  0x0410C	/* Interrupt Cause Tx Packet Timer Expire Count */
#घोषणा E1000_ICTXATC  0x04110	/* Interrupt Cause Tx Absolute Timer Expire Count */
#घोषणा E1000_ICTXQEC  0x04118	/* Interrupt Cause Tx Queue Empty Count */
#घोषणा E1000_ICTXQMTC 0x0411C	/* Interrupt Cause Tx Queue Minimum Threshold Count */
#घोषणा E1000_ICRXDMTC 0x04120	/* Interrupt Cause Rx Descriptor Minimum Threshold Count */
#घोषणा E1000_ICRXOC   0x04124	/* Interrupt Cause Receiver Overrun Count */
#घोषणा E1000_RXCSUM   0x05000	/* RX Checksum Control - RW */
#घोषणा E1000_RFCTL    0x05008	/* Receive Filter Control */
#घोषणा E1000_MTA      0x05200	/* Multicast Table Array - RW Array */
#घोषणा E1000_RA       0x05400	/* Receive Address - RW Array */
#घोषणा E1000_VFTA     0x05600	/* VLAN Filter Table Array - RW Array */
#घोषणा E1000_WUC      0x05800	/* Wakeup Control - RW */
#घोषणा E1000_WUFC     0x05808	/* Wakeup Filter Control - RW */
#घोषणा E1000_WUS      0x05810	/* Wakeup Status - RO */
#घोषणा E1000_MANC     0x05820	/* Management Control - RW */
#घोषणा E1000_IPAV     0x05838	/* IP Address Valid - RW */
#घोषणा E1000_IP4AT    0x05840	/* IPv4 Address Table - RW Array */
#घोषणा E1000_IP6AT    0x05880	/* IPv6 Address Table - RW Array */
#घोषणा E1000_WUPL     0x05900	/* Wakeup Packet Length - RW */
#घोषणा E1000_WUPM     0x05A00	/* Wakeup Packet Memory - RO A */
#घोषणा E1000_FFLT     0x05F00	/* Flexible Filter Length Table - RW Array */
#घोषणा E1000_HOST_IF  0x08800	/* Host Interface */
#घोषणा E1000_FFMT     0x09000	/* Flexible Filter Mask Table - RW Array */
#घोषणा E1000_FFVT     0x09800	/* Flexible Filter Value Table - RW Array */

#घोषणा E1000_KUMCTRLSTA 0x00034	/* MAC-PHY पूर्णांकerface - RW */
#घोषणा E1000_MDPHYA     0x0003C	/* PHY address - RW */
#घोषणा E1000_MANC2H     0x05860	/* Management Control To Host - RW */
#घोषणा E1000_SW_FW_SYNC 0x05B5C	/* Software-Firmware Synchronization - RW */

#घोषणा E1000_GCR       0x05B00	/* PCI-Ex Control */
#घोषणा E1000_GSCL_1    0x05B10	/* PCI-Ex Statistic Control #1 */
#घोषणा E1000_GSCL_2    0x05B14	/* PCI-Ex Statistic Control #2 */
#घोषणा E1000_GSCL_3    0x05B18	/* PCI-Ex Statistic Control #3 */
#घोषणा E1000_GSCL_4    0x05B1C	/* PCI-Ex Statistic Control #4 */
#घोषणा E1000_FACTPS    0x05B30	/* Function Active and Power State to MNG */
#घोषणा E1000_SWSM      0x05B50	/* SW Semaphore */
#घोषणा E1000_FWSM      0x05B54	/* FW Semaphore */
#घोषणा E1000_FFLT_DBG  0x05F04	/* Debug Register */
#घोषणा E1000_HICR      0x08F00	/* Host Interface Control */

/* RSS रेजिस्टरs */
#घोषणा E1000_CPUVEC    0x02C10	/* CPU Vector Register - RW */
#घोषणा E1000_MRQC      0x05818	/* Multiple Receive Control - RW */
#घोषणा E1000_RETA      0x05C00	/* Redirection Table - RW Array */
#घोषणा E1000_RSSRK     0x05C80	/* RSS Ranकरोm Key - RW Array */
#घोषणा E1000_RSSIM     0x05864	/* RSS Interrupt Mask */
#घोषणा E1000_RSSIR     0x05868	/* RSS Interrupt Request */
/* Register Set (82542)
 *
 * Some of the 82542 रेजिस्टरs are located at dअगरferent offsets than they are
 * in more current versions of the 8254x. Despite the dअगरference in location,
 * the रेजिस्टरs function in the same manner.
 */
#घोषणा E1000_82542_CTL_AUX  E1000_CTL_AUX
#घोषणा E1000_82542_CTRL     E1000_CTRL
#घोषणा E1000_82542_CTRL_DUP E1000_CTRL_DUP
#घोषणा E1000_82542_STATUS   E1000_STATUS
#घोषणा E1000_82542_EECD     E1000_EECD
#घोषणा E1000_82542_EERD     E1000_EERD
#घोषणा E1000_82542_CTRL_EXT E1000_CTRL_EXT
#घोषणा E1000_82542_FLA      E1000_FLA
#घोषणा E1000_82542_MDIC     E1000_MDIC
#घोषणा E1000_82542_SCTL     E1000_SCTL
#घोषणा E1000_82542_FEXTNVM  E1000_FEXTNVM
#घोषणा E1000_82542_FCAL     E1000_FCAL
#घोषणा E1000_82542_FCAH     E1000_FCAH
#घोषणा E1000_82542_FCT      E1000_FCT
#घोषणा E1000_82542_VET      E1000_VET
#घोषणा E1000_82542_RA       0x00040
#घोषणा E1000_82542_ICR      E1000_ICR
#घोषणा E1000_82542_ITR      E1000_ITR
#घोषणा E1000_82542_ICS      E1000_ICS
#घोषणा E1000_82542_IMS      E1000_IMS
#घोषणा E1000_82542_IMC      E1000_IMC
#घोषणा E1000_82542_RCTL     E1000_RCTL
#घोषणा E1000_82542_RDTR     0x00108
#घोषणा E1000_82542_RDFH     E1000_RDFH
#घोषणा E1000_82542_RDFT     E1000_RDFT
#घोषणा E1000_82542_RDFHS    E1000_RDFHS
#घोषणा E1000_82542_RDFTS    E1000_RDFTS
#घोषणा E1000_82542_RDFPC    E1000_RDFPC
#घोषणा E1000_82542_RDBAL    0x00110
#घोषणा E1000_82542_RDBAH    0x00114
#घोषणा E1000_82542_RDLEN    0x00118
#घोषणा E1000_82542_RDH      0x00120
#घोषणा E1000_82542_RDT      0x00128
#घोषणा E1000_82542_RDTR0    E1000_82542_RDTR
#घोषणा E1000_82542_RDBAL0   E1000_82542_RDBAL
#घोषणा E1000_82542_RDBAH0   E1000_82542_RDBAH
#घोषणा E1000_82542_RDLEN0   E1000_82542_RDLEN
#घोषणा E1000_82542_RDH0     E1000_82542_RDH
#घोषणा E1000_82542_RDT0     E1000_82542_RDT
#घोषणा E1000_82542_SRRCTL(_n) (0x280C + ((_n) << 8))	/* Split and Replication
							 * RX Control - RW */
#घोषणा E1000_82542_DCA_RXCTRL(_n) (0x02814 + ((_n) << 8))
#घोषणा E1000_82542_RDBAH3   0x02B04	/* RX Desc Base High Queue 3 - RW */
#घोषणा E1000_82542_RDBAL3   0x02B00	/* RX Desc Low Queue 3 - RW */
#घोषणा E1000_82542_RDLEN3   0x02B08	/* RX Desc Length Queue 3 - RW */
#घोषणा E1000_82542_RDH3     0x02B10	/* RX Desc Head Queue 3 - RW */
#घोषणा E1000_82542_RDT3     0x02B18	/* RX Desc Tail Queue 3 - RW */
#घोषणा E1000_82542_RDBAL2   0x02A00	/* RX Desc Base Low Queue 2 - RW */
#घोषणा E1000_82542_RDBAH2   0x02A04	/* RX Desc Base High Queue 2 - RW */
#घोषणा E1000_82542_RDLEN2   0x02A08	/* RX Desc Length Queue 2 - RW */
#घोषणा E1000_82542_RDH2     0x02A10	/* RX Desc Head Queue 2 - RW */
#घोषणा E1000_82542_RDT2     0x02A18	/* RX Desc Tail Queue 2 - RW */
#घोषणा E1000_82542_RDTR1    0x00130
#घोषणा E1000_82542_RDBAL1   0x00138
#घोषणा E1000_82542_RDBAH1   0x0013C
#घोषणा E1000_82542_RDLEN1   0x00140
#घोषणा E1000_82542_RDH1     0x00148
#घोषणा E1000_82542_RDT1     0x00150
#घोषणा E1000_82542_FCRTH    0x00160
#घोषणा E1000_82542_FCRTL    0x00168
#घोषणा E1000_82542_FCTTV    E1000_FCTTV
#घोषणा E1000_82542_TXCW     E1000_TXCW
#घोषणा E1000_82542_RXCW     E1000_RXCW
#घोषणा E1000_82542_MTA      0x00200
#घोषणा E1000_82542_TCTL     E1000_TCTL
#घोषणा E1000_82542_TCTL_EXT E1000_TCTL_EXT
#घोषणा E1000_82542_TIPG     E1000_TIPG
#घोषणा E1000_82542_TDBAL    0x00420
#घोषणा E1000_82542_TDBAH    0x00424
#घोषणा E1000_82542_TDLEN    0x00428
#घोषणा E1000_82542_TDH      0x00430
#घोषणा E1000_82542_TDT      0x00438
#घोषणा E1000_82542_TIDV     0x00440
#घोषणा E1000_82542_TBT      E1000_TBT
#घोषणा E1000_82542_AIT      E1000_AIT
#घोषणा E1000_82542_VFTA     0x00600
#घोषणा E1000_82542_LEDCTL   E1000_LEDCTL
#घोषणा E1000_82542_PBA      E1000_PBA
#घोषणा E1000_82542_PBS      E1000_PBS
#घोषणा E1000_82542_EEMNGCTL E1000_EEMNGCTL
#घोषणा E1000_82542_EEARBC   E1000_EEARBC
#घोषणा E1000_82542_FLASHT   E1000_FLASHT
#घोषणा E1000_82542_EEWR     E1000_EEWR
#घोषणा E1000_82542_FLSWCTL  E1000_FLSWCTL
#घोषणा E1000_82542_FLSWDATA E1000_FLSWDATA
#घोषणा E1000_82542_FLSWCNT  E1000_FLSWCNT
#घोषणा E1000_82542_FLOP     E1000_FLOP
#घोषणा E1000_82542_EXTCNF_CTRL  E1000_EXTCNF_CTRL
#घोषणा E1000_82542_EXTCNF_SIZE  E1000_EXTCNF_SIZE
#घोषणा E1000_82542_PHY_CTRL E1000_PHY_CTRL
#घोषणा E1000_82542_ERT      E1000_ERT
#घोषणा E1000_82542_RXDCTL   E1000_RXDCTL
#घोषणा E1000_82542_RXDCTL1  E1000_RXDCTL1
#घोषणा E1000_82542_RADV     E1000_RADV
#घोषणा E1000_82542_RSRPD    E1000_RSRPD
#घोषणा E1000_82542_TXDMAC   E1000_TXDMAC
#घोषणा E1000_82542_KABGTXD  E1000_KABGTXD
#घोषणा E1000_82542_TDFHS    E1000_TDFHS
#घोषणा E1000_82542_TDFTS    E1000_TDFTS
#घोषणा E1000_82542_TDFPC    E1000_TDFPC
#घोषणा E1000_82542_TXDCTL   E1000_TXDCTL
#घोषणा E1000_82542_TADV     E1000_TADV
#घोषणा E1000_82542_TSPMT    E1000_TSPMT
#घोषणा E1000_82542_CRCERRS  E1000_CRCERRS
#घोषणा E1000_82542_ALGNERRC E1000_ALGNERRC
#घोषणा E1000_82542_SYMERRS  E1000_SYMERRS
#घोषणा E1000_82542_RXERRC   E1000_RXERRC
#घोषणा E1000_82542_MPC      E1000_MPC
#घोषणा E1000_82542_SCC      E1000_SCC
#घोषणा E1000_82542_ECOL     E1000_ECOL
#घोषणा E1000_82542_MCC      E1000_MCC
#घोषणा E1000_82542_LATECOL  E1000_LATECOL
#घोषणा E1000_82542_COLC     E1000_COLC
#घोषणा E1000_82542_DC       E1000_DC
#घोषणा E1000_82542_TNCRS    E1000_TNCRS
#घोषणा E1000_82542_SEC      E1000_SEC
#घोषणा E1000_82542_CEXTERR  E1000_CEXTERR
#घोषणा E1000_82542_RLEC     E1000_RLEC
#घोषणा E1000_82542_XONRXC   E1000_XONRXC
#घोषणा E1000_82542_XONTXC   E1000_XONTXC
#घोषणा E1000_82542_XOFFRXC  E1000_XOFFRXC
#घोषणा E1000_82542_XOFFTXC  E1000_XOFFTXC
#घोषणा E1000_82542_FCRUC    E1000_FCRUC
#घोषणा E1000_82542_PRC64    E1000_PRC64
#घोषणा E1000_82542_PRC127   E1000_PRC127
#घोषणा E1000_82542_PRC255   E1000_PRC255
#घोषणा E1000_82542_PRC511   E1000_PRC511
#घोषणा E1000_82542_PRC1023  E1000_PRC1023
#घोषणा E1000_82542_PRC1522  E1000_PRC1522
#घोषणा E1000_82542_GPRC     E1000_GPRC
#घोषणा E1000_82542_BPRC     E1000_BPRC
#घोषणा E1000_82542_MPRC     E1000_MPRC
#घोषणा E1000_82542_GPTC     E1000_GPTC
#घोषणा E1000_82542_GORCL    E1000_GORCL
#घोषणा E1000_82542_GORCH    E1000_GORCH
#घोषणा E1000_82542_GOTCL    E1000_GOTCL
#घोषणा E1000_82542_GOTCH    E1000_GOTCH
#घोषणा E1000_82542_RNBC     E1000_RNBC
#घोषणा E1000_82542_RUC      E1000_RUC
#घोषणा E1000_82542_RFC      E1000_RFC
#घोषणा E1000_82542_ROC      E1000_ROC
#घोषणा E1000_82542_RJC      E1000_RJC
#घोषणा E1000_82542_MGTPRC   E1000_MGTPRC
#घोषणा E1000_82542_MGTPDC   E1000_MGTPDC
#घोषणा E1000_82542_MGTPTC   E1000_MGTPTC
#घोषणा E1000_82542_TORL     E1000_TORL
#घोषणा E1000_82542_TORH     E1000_TORH
#घोषणा E1000_82542_TOTL     E1000_TOTL
#घोषणा E1000_82542_TOTH     E1000_TOTH
#घोषणा E1000_82542_TPR      E1000_TPR
#घोषणा E1000_82542_TPT      E1000_TPT
#घोषणा E1000_82542_PTC64    E1000_PTC64
#घोषणा E1000_82542_PTC127   E1000_PTC127
#घोषणा E1000_82542_PTC255   E1000_PTC255
#घोषणा E1000_82542_PTC511   E1000_PTC511
#घोषणा E1000_82542_PTC1023  E1000_PTC1023
#घोषणा E1000_82542_PTC1522  E1000_PTC1522
#घोषणा E1000_82542_MPTC     E1000_MPTC
#घोषणा E1000_82542_BPTC     E1000_BPTC
#घोषणा E1000_82542_TSCTC    E1000_TSCTC
#घोषणा E1000_82542_TSCTFC   E1000_TSCTFC
#घोषणा E1000_82542_RXCSUM   E1000_RXCSUM
#घोषणा E1000_82542_WUC      E1000_WUC
#घोषणा E1000_82542_WUFC     E1000_WUFC
#घोषणा E1000_82542_WUS      E1000_WUS
#घोषणा E1000_82542_MANC     E1000_MANC
#घोषणा E1000_82542_IPAV     E1000_IPAV
#घोषणा E1000_82542_IP4AT    E1000_IP4AT
#घोषणा E1000_82542_IP6AT    E1000_IP6AT
#घोषणा E1000_82542_WUPL     E1000_WUPL
#घोषणा E1000_82542_WUPM     E1000_WUPM
#घोषणा E1000_82542_FFLT     E1000_FFLT
#घोषणा E1000_82542_TDFH     0x08010
#घोषणा E1000_82542_TDFT     0x08018
#घोषणा E1000_82542_FFMT     E1000_FFMT
#घोषणा E1000_82542_FFVT     E1000_FFVT
#घोषणा E1000_82542_HOST_IF  E1000_HOST_IF
#घोषणा E1000_82542_IAM         E1000_IAM
#घोषणा E1000_82542_EEMNGCTL    E1000_EEMNGCTL
#घोषणा E1000_82542_PSRCTL      E1000_PSRCTL
#घोषणा E1000_82542_RAID        E1000_RAID
#घोषणा E1000_82542_TARC0       E1000_TARC0
#घोषणा E1000_82542_TDBAL1      E1000_TDBAL1
#घोषणा E1000_82542_TDBAH1      E1000_TDBAH1
#घोषणा E1000_82542_TDLEN1      E1000_TDLEN1
#घोषणा E1000_82542_TDH1        E1000_TDH1
#घोषणा E1000_82542_TDT1        E1000_TDT1
#घोषणा E1000_82542_TXDCTL1     E1000_TXDCTL1
#घोषणा E1000_82542_TARC1       E1000_TARC1
#घोषणा E1000_82542_RFCTL       E1000_RFCTL
#घोषणा E1000_82542_GCR         E1000_GCR
#घोषणा E1000_82542_GSCL_1      E1000_GSCL_1
#घोषणा E1000_82542_GSCL_2      E1000_GSCL_2
#घोषणा E1000_82542_GSCL_3      E1000_GSCL_3
#घोषणा E1000_82542_GSCL_4      E1000_GSCL_4
#घोषणा E1000_82542_FACTPS      E1000_FACTPS
#घोषणा E1000_82542_SWSM        E1000_SWSM
#घोषणा E1000_82542_FWSM        E1000_FWSM
#घोषणा E1000_82542_FFLT_DBG    E1000_FFLT_DBG
#घोषणा E1000_82542_IAC         E1000_IAC
#घोषणा E1000_82542_ICRXPTC     E1000_ICRXPTC
#घोषणा E1000_82542_ICRXATC     E1000_ICRXATC
#घोषणा E1000_82542_ICTXPTC     E1000_ICTXPTC
#घोषणा E1000_82542_ICTXATC     E1000_ICTXATC
#घोषणा E1000_82542_ICTXQEC     E1000_ICTXQEC
#घोषणा E1000_82542_ICTXQMTC    E1000_ICTXQMTC
#घोषणा E1000_82542_ICRXDMTC    E1000_ICRXDMTC
#घोषणा E1000_82542_ICRXOC      E1000_ICRXOC
#घोषणा E1000_82542_HICR        E1000_HICR

#घोषणा E1000_82542_CPUVEC      E1000_CPUVEC
#घोषणा E1000_82542_MRQC        E1000_MRQC
#घोषणा E1000_82542_RETA        E1000_RETA
#घोषणा E1000_82542_RSSRK       E1000_RSSRK
#घोषणा E1000_82542_RSSIM       E1000_RSSIM
#घोषणा E1000_82542_RSSIR       E1000_RSSIR
#घोषणा E1000_82542_KUMCTRLSTA E1000_KUMCTRLSTA
#घोषणा E1000_82542_SW_FW_SYNC E1000_SW_FW_SYNC

/* Statistics counters collected by the MAC */
काष्ठा e1000_hw_stats अणु
	u64 crcerrs;
	u64 algnerrc;
	u64 symerrs;
	u64 rxerrc;
	u64 txerrc;
	u64 mpc;
	u64 scc;
	u64 ecol;
	u64 mcc;
	u64 latecol;
	u64 colc;
	u64 dc;
	u64 tncrs;
	u64 sec;
	u64 cexterr;
	u64 rlec;
	u64 xonrxc;
	u64 xontxc;
	u64 xoffrxc;
	u64 xofftxc;
	u64 fcruc;
	u64 prc64;
	u64 prc127;
	u64 prc255;
	u64 prc511;
	u64 prc1023;
	u64 prc1522;
	u64 gprc;
	u64 bprc;
	u64 mprc;
	u64 gptc;
	u64 gorcl;
	u64 gorch;
	u64 gotcl;
	u64 gotch;
	u64 rnbc;
	u64 ruc;
	u64 rfc;
	u64 roc;
	u64 rlerrc;
	u64 rjc;
	u64 mgprc;
	u64 mgpdc;
	u64 mgptc;
	u64 torl;
	u64 torh;
	u64 totl;
	u64 toth;
	u64 tpr;
	u64 tpt;
	u64 ptc64;
	u64 ptc127;
	u64 ptc255;
	u64 ptc511;
	u64 ptc1023;
	u64 ptc1522;
	u64 mptc;
	u64 bptc;
	u64 tsctc;
	u64 tsctfc;
	u64 iac;
	u64 icrxptc;
	u64 icrxatc;
	u64 ictxptc;
	u64 ictxatc;
	u64 ictxqec;
	u64 ictxqmtc;
	u64 icrxdmtc;
	u64 icrxoc;
पूर्ण;

/* Structure containing variables used by the shared code (e1000_hw.c) */
काष्ठा e1000_hw अणु
	u8 __iomem *hw_addr;
	u8 __iomem *flash_address;
	व्योम __iomem *ce4100_gbe_mdio_base_virt;
	e1000_mac_type mac_type;
	e1000_phy_type phy_type;
	u32 phy_init_script;
	e1000_media_type media_type;
	व्योम *back;
	काष्ठा e1000_shaकरोw_ram *eeprom_shaकरोw_ram;
	u32 flash_bank_size;
	u32 flash_base_addr;
	e1000_fc_type fc;
	e1000_bus_speed bus_speed;
	e1000_bus_width bus_width;
	e1000_bus_type bus_type;
	काष्ठा e1000_eeprom_info eeprom;
	e1000_ms_type master_slave;
	e1000_ms_type original_master_slave;
	e1000_ffe_config ffe_config_state;
	u32 asf_firmware_present;
	u32 eeprom_semaphore_present;
	अचिन्हित दीर्घ io_base;
	u32 phy_id;
	u32 phy_revision;
	u32 phy_addr;
	u32 original_fc;
	u32 txcw;
	u32 स्वतःneg_failed;
	u32 max_frame_size;
	u32 min_frame_size;
	u32 mc_filter_type;
	u32 num_mc_addrs;
	u32 collision_delta;
	u32 tx_packet_delta;
	u32 ledctl_शेष;
	u32 ledctl_mode1;
	u32 ledctl_mode2;
	bool tx_pkt_filtering;
	काष्ठा e1000_host_mng_dhcp_cookie mng_cookie;
	u16 phy_spd_शेष;
	u16 स्वतःneg_advertised;
	u16 pci_cmd_word;
	u16 fc_high_water;
	u16 fc_low_water;
	u16 fc_छोड़ो_समय;
	u16 current_अगरs_val;
	u16 अगरs_min_val;
	u16 अगरs_max_val;
	u16 अगरs_step_size;
	u16 अगरs_ratio;
	u16 device_id;
	u16 venकरोr_id;
	u16 subप्रणाली_id;
	u16 subप्रणाली_venकरोr_id;
	u8 revision_id;
	u8 स्वतःneg;
	u8 mdix;
	u8 क्रमced_speed_duplex;
	u8 रुको_स्वतःneg_complete;
	u8 dma_fairness;
	u8 mac_addr[NODE_ADDRESS_SIZE];
	u8 perm_mac_addr[NODE_ADDRESS_SIZE];
	bool disable_polarity_correction;
	bool speed_करोwngraded;
	e1000_smart_speed smart_speed;
	e1000_dsp_config dsp_config_state;
	bool get_link_status;
	bool serdes_has_link;
	bool tbi_compatibility_en;
	bool tbi_compatibility_on;
	bool laa_is_present;
	bool phy_reset_disable;
	bool initialize_hw_bits_disable;
	bool fc_send_xon;
	bool fc_strict_ieee;
	bool report_tx_early;
	bool adaptive_अगरs;
	bool अगरs_params_क्रमced;
	bool in_अगरs_mode;
	bool mng_reg_access_disabled;
	bool leave_av_bit_off;
	bool bad_tx_carr_stats_fd;
	bool has_smbus;
पूर्ण;

#घोषणा E1000_EEPROM_SWDPIN0   0x0001	/* SWDPIN 0 EEPROM Value */
#घोषणा E1000_EEPROM_LED_LOGIC 0x0020	/* Led Logic Word */
#घोषणा E1000_EEPROM_RW_REG_DATA   16	/* Offset to data in EEPROM पढ़ो/ग_लिखो रेजिस्टरs */
#घोषणा E1000_EEPROM_RW_REG_DONE   2	/* Offset to READ/WRITE करोne bit */
#घोषणा E1000_EEPROM_RW_REG_START  1	/* First bit क्रम telling part to start operation */
#घोषणा E1000_EEPROM_RW_ADDR_SHIFT 2	/* Shअगरt to the address bits */
#घोषणा E1000_EEPROM_POLL_WRITE    1	/* Flag क्रम polling क्रम ग_लिखो complete */
#घोषणा E1000_EEPROM_POLL_READ     0	/* Flag क्रम polling क्रम पढ़ो complete */
/* Register Bit Masks */
/* Device Control */
#घोषणा E1000_CTRL_FD       0x00000001	/* Full duplex.0=half; 1=full */
#घोषणा E1000_CTRL_BEM      0x00000002	/* Endian Mode.0=little,1=big */
#घोषणा E1000_CTRL_PRIOR    0x00000004	/* Priority on PCI. 0=rx,1=fair */
#घोषणा E1000_CTRL_GIO_MASTER_DISABLE 0x00000004	/*Blocks new Master requests */
#घोषणा E1000_CTRL_LRST     0x00000008	/* Link reset. 0=normal,1=reset */
#घोषणा E1000_CTRL_TME      0x00000010	/* Test mode. 0=normal,1=test */
#घोषणा E1000_CTRL_SLE      0x00000020	/* Serial Link on 0=dis,1=en */
#घोषणा E1000_CTRL_ASDE     0x00000020	/* Auto-speed detect enable */
#घोषणा E1000_CTRL_SLU      0x00000040	/* Set link up (Force Link) */
#घोषणा E1000_CTRL_ILOS     0x00000080	/* Invert Loss-Of Signal */
#घोषणा E1000_CTRL_SPD_SEL  0x00000300	/* Speed Select Mask */
#घोषणा E1000_CTRL_SPD_10   0x00000000	/* Force 10Mb */
#घोषणा E1000_CTRL_SPD_100  0x00000100	/* Force 100Mb */
#घोषणा E1000_CTRL_SPD_1000 0x00000200	/* Force 1Gb */
#घोषणा E1000_CTRL_BEM32    0x00000400	/* Big Endian 32 mode */
#घोषणा E1000_CTRL_FRCSPD   0x00000800	/* Force Speed */
#घोषणा E1000_CTRL_FRCDPX   0x00001000	/* Force Duplex */
#घोषणा E1000_CTRL_D_UD_EN  0x00002000	/* Dock/Unकरोck enable */
#घोषणा E1000_CTRL_D_UD_POLARITY 0x00004000	/* Defined polarity of Dock/Unकरोck indication in SDP[0] */
#घोषणा E1000_CTRL_FORCE_PHY_RESET 0x00008000	/* Reset both PHY ports, through PHYRST_N pin */
#घोषणा E1000_CTRL_EXT_LINK_EN 0x00010000	/* enable link status from बाह्यal LINK_0 and LINK_1 pins */
#घोषणा E1000_CTRL_SWDPIN0  0x00040000	/* SWDPIN 0 value */
#घोषणा E1000_CTRL_SWDPIN1  0x00080000	/* SWDPIN 1 value */
#घोषणा E1000_CTRL_SWDPIN2  0x00100000	/* SWDPIN 2 value */
#घोषणा E1000_CTRL_SWDPIN3  0x00200000	/* SWDPIN 3 value */
#घोषणा E1000_CTRL_SWDPIO0  0x00400000	/* SWDPIN 0 Input or output */
#घोषणा E1000_CTRL_SWDPIO1  0x00800000	/* SWDPIN 1 input or output */
#घोषणा E1000_CTRL_SWDPIO2  0x01000000	/* SWDPIN 2 input or output */
#घोषणा E1000_CTRL_SWDPIO3  0x02000000	/* SWDPIN 3 input or output */
#घोषणा E1000_CTRL_RST      0x04000000	/* Global reset */
#घोषणा E1000_CTRL_RFCE     0x08000000	/* Receive Flow Control enable */
#घोषणा E1000_CTRL_TFCE     0x10000000	/* Transmit flow control enable */
#घोषणा E1000_CTRL_RTE      0x20000000	/* Routing tag enable */
#घोषणा E1000_CTRL_VME      0x40000000	/* IEEE VLAN mode enable */
#घोषणा E1000_CTRL_PHY_RST  0x80000000	/* PHY Reset */
#घोषणा E1000_CTRL_SW2FW_INT 0x02000000	/* Initiate an पूर्णांकerrupt to manageability engine */

/* Device Status */
#घोषणा E1000_STATUS_FD         0x00000001	/* Full duplex.0=half,1=full */
#घोषणा E1000_STATUS_LU         0x00000002	/* Link up.0=no,1=link */
#घोषणा E1000_STATUS_FUNC_MASK  0x0000000C	/* PCI Function Mask */
#घोषणा E1000_STATUS_FUNC_SHIFT 2
#घोषणा E1000_STATUS_FUNC_0     0x00000000	/* Function 0 */
#घोषणा E1000_STATUS_FUNC_1     0x00000004	/* Function 1 */
#घोषणा E1000_STATUS_TXOFF      0x00000010	/* transmission छोड़ोd */
#घोषणा E1000_STATUS_TBIMODE    0x00000020	/* TBI mode */
#घोषणा E1000_STATUS_SPEED_MASK 0x000000C0
#घोषणा E1000_STATUS_SPEED_10   0x00000000	/* Speed 10Mb/s */
#घोषणा E1000_STATUS_SPEED_100  0x00000040	/* Speed 100Mb/s */
#घोषणा E1000_STATUS_SPEED_1000 0x00000080	/* Speed 1000Mb/s */
#घोषणा E1000_STATUS_LAN_INIT_DONE 0x00000200	/* Lan Init Completion
						   by EEPROM/Flash */
#घोषणा E1000_STATUS_ASDV       0x00000300	/* Auto speed detect value */
#घोषणा E1000_STATUS_DOCK_CI    0x00000800	/* Change in Dock/Unकरोck state. Clear on ग_लिखो '0'. */
#घोषणा E1000_STATUS_GIO_MASTER_ENABLE 0x00080000	/* Status of Master requests. */
#घोषणा E1000_STATUS_MTXCKOK    0x00000400	/* MTX घड़ी running OK */
#घोषणा E1000_STATUS_PCI66      0x00000800	/* In 66Mhz slot */
#घोषणा E1000_STATUS_BUS64      0x00001000	/* In 64 bit slot */
#घोषणा E1000_STATUS_PCIX_MODE  0x00002000	/* PCI-X mode */
#घोषणा E1000_STATUS_PCIX_SPEED 0x0000C000	/* PCI-X bus speed */
#घोषणा E1000_STATUS_BMC_SKU_0  0x00100000	/* BMC USB redirect disabled */
#घोषणा E1000_STATUS_BMC_SKU_1  0x00200000	/* BMC SRAM disabled */
#घोषणा E1000_STATUS_BMC_SKU_2  0x00400000	/* BMC SDRAM disabled */
#घोषणा E1000_STATUS_BMC_CRYPTO 0x00800000	/* BMC crypto disabled */
#घोषणा E1000_STATUS_BMC_LITE   0x01000000	/* BMC बाह्यal code execution disabled */
#घोषणा E1000_STATUS_RGMII_ENABLE 0x02000000	/* RGMII disabled */
#घोषणा E1000_STATUS_FUSE_8       0x04000000
#घोषणा E1000_STATUS_FUSE_9       0x08000000
#घोषणा E1000_STATUS_SERDES0_DIS  0x10000000	/* SERDES disabled on port 0 */
#घोषणा E1000_STATUS_SERDES1_DIS  0x20000000	/* SERDES disabled on port 1 */

/* Constants used to पूर्णांकerpret the masked PCI-X bus speed. */
#घोषणा E1000_STATUS_PCIX_SPEED_66  0x00000000	/* PCI-X bus speed  50-66 MHz */
#घोषणा E1000_STATUS_PCIX_SPEED_100 0x00004000	/* PCI-X bus speed  66-100 MHz */
#घोषणा E1000_STATUS_PCIX_SPEED_133 0x00008000	/* PCI-X bus speed 100-133 MHz */

/* EEPROM/Flash Control */
#घोषणा E1000_EECD_SK        0x00000001	/* EEPROM Clock */
#घोषणा E1000_EECD_CS        0x00000002	/* EEPROM Chip Select */
#घोषणा E1000_EECD_DI        0x00000004	/* EEPROM Data In */
#घोषणा E1000_EECD_DO        0x00000008	/* EEPROM Data Out */
#घोषणा E1000_EECD_FWE_MASK  0x00000030
#घोषणा E1000_EECD_FWE_DIS   0x00000010	/* Disable FLASH ग_लिखोs */
#घोषणा E1000_EECD_FWE_EN    0x00000020	/* Enable FLASH ग_लिखोs */
#घोषणा E1000_EECD_FWE_SHIFT 4
#घोषणा E1000_EECD_REQ       0x00000040	/* EEPROM Access Request */
#घोषणा E1000_EECD_GNT       0x00000080	/* EEPROM Access Grant */
#घोषणा E1000_EECD_PRES      0x00000100	/* EEPROM Present */
#घोषणा E1000_EECD_SIZE      0x00000200	/* EEPROM Size (0=64 word 1=256 word) */
#घोषणा E1000_EECD_ADDR_BITS 0x00000400	/* EEPROM Addressing bits based on type
					 * (0-small, 1-large) */
#घोषणा E1000_EECD_TYPE      0x00002000	/* EEPROM Type (1-SPI, 0-Microwire) */
#अगर_अघोषित E1000_EEPROM_GRANT_ATTEMPTS
#घोषणा E1000_EEPROM_GRANT_ATTEMPTS 1000	/* EEPROM # attempts to gain grant */
#पूर्ण_अगर
#घोषणा E1000_EECD_AUTO_RD          0x00000200	/* EEPROM Auto Read करोne */
#घोषणा E1000_EECD_SIZE_EX_MASK     0x00007800	/* EEprom Size */
#घोषणा E1000_EECD_SIZE_EX_SHIFT    11
#घोषणा E1000_EECD_NVADDS    0x00018000	/* NVM Address Size */
#घोषणा E1000_EECD_SELSHAD   0x00020000	/* Select Shaकरोw RAM */
#घोषणा E1000_EECD_INITSRAM  0x00040000	/* Initialize Shaकरोw RAM */
#घोषणा E1000_EECD_FLUPD     0x00080000	/* Update FLASH */
#घोषणा E1000_EECD_AUPDEN    0x00100000	/* Enable Autonomous FLASH update */
#घोषणा E1000_EECD_SHADV     0x00200000	/* Shaकरोw RAM Data Valid */
#घोषणा E1000_EECD_SEC1VAL   0x00400000	/* Sector One Valid */
#घोषणा E1000_EECD_SECVAL_SHIFT      22
#घोषणा E1000_STM_OPCODE     0xDB00
#घोषणा E1000_HICR_FW_RESET  0xC0

#घोषणा E1000_SHADOW_RAM_WORDS     2048
#घोषणा E1000_ICH_NVM_SIG_WORD     0x13
#घोषणा E1000_ICH_NVM_SIG_MASK     0xC0

/* EEPROM Read */
#घोषणा E1000_EERD_START      0x00000001	/* Start Read */
#घोषणा E1000_EERD_DONE       0x00000010	/* Read Done */
#घोषणा E1000_EERD_ADDR_SHIFT 8
#घोषणा E1000_EERD_ADDR_MASK  0x0000FF00	/* Read Address */
#घोषणा E1000_EERD_DATA_SHIFT 16
#घोषणा E1000_EERD_DATA_MASK  0xFFFF0000	/* Read Data */

/* SPI EEPROM Status Register */
#घोषणा EEPROM_STATUS_RDY_SPI  0x01
#घोषणा EEPROM_STATUS_WEN_SPI  0x02
#घोषणा EEPROM_STATUS_BP0_SPI  0x04
#घोषणा EEPROM_STATUS_BP1_SPI  0x08
#घोषणा EEPROM_STATUS_WPEN_SPI 0x80

/* Extended Device Control */
#घोषणा E1000_CTRL_EXT_GPI0_EN   0x00000001	/* Maps SDP4 to GPI0 */
#घोषणा E1000_CTRL_EXT_GPI1_EN   0x00000002	/* Maps SDP5 to GPI1 */
#घोषणा E1000_CTRL_EXT_PHYINT_EN E1000_CTRL_EXT_GPI1_EN
#घोषणा E1000_CTRL_EXT_GPI2_EN   0x00000004	/* Maps SDP6 to GPI2 */
#घोषणा E1000_CTRL_EXT_GPI3_EN   0x00000008	/* Maps SDP7 to GPI3 */
#घोषणा E1000_CTRL_EXT_SDP4_DATA 0x00000010	/* Value of SW Defineable Pin 4 */
#घोषणा E1000_CTRL_EXT_SDP5_DATA 0x00000020	/* Value of SW Defineable Pin 5 */
#घोषणा E1000_CTRL_EXT_PHY_INT   E1000_CTRL_EXT_SDP5_DATA
#घोषणा E1000_CTRL_EXT_SDP6_DATA 0x00000040	/* Value of SW Defineable Pin 6 */
#घोषणा E1000_CTRL_EXT_SDP7_DATA 0x00000080	/* Value of SW Defineable Pin 7 */
#घोषणा E1000_CTRL_EXT_SDP4_सूची  0x00000100	/* Direction of SDP4 0=in 1=out */
#घोषणा E1000_CTRL_EXT_SDP5_सूची  0x00000200	/* Direction of SDP5 0=in 1=out */
#घोषणा E1000_CTRL_EXT_SDP6_सूची  0x00000400	/* Direction of SDP6 0=in 1=out */
#घोषणा E1000_CTRL_EXT_SDP7_सूची  0x00000800	/* Direction of SDP7 0=in 1=out */
#घोषणा E1000_CTRL_EXT_ASDCHK    0x00001000	/* Initiate an ASD sequence */
#घोषणा E1000_CTRL_EXT_EE_RST    0x00002000	/* Reinitialize from EEPROM */
#घोषणा E1000_CTRL_EXT_IPS       0x00004000	/* Invert Power State */
#घोषणा E1000_CTRL_EXT_SPD_BYPS  0x00008000	/* Speed Select Bypass */
#घोषणा E1000_CTRL_EXT_RO_DIS    0x00020000	/* Relaxed Ordering disable */
#घोषणा E1000_CTRL_EXT_LINK_MODE_MASK 0x00C00000
#घोषणा E1000_CTRL_EXT_LINK_MODE_GMII 0x00000000
#घोषणा E1000_CTRL_EXT_LINK_MODE_TBI  0x00C00000
#घोषणा E1000_CTRL_EXT_LINK_MODE_KMRN 0x00000000
#घोषणा E1000_CTRL_EXT_LINK_MODE_SERDES  0x00C00000
#घोषणा E1000_CTRL_EXT_LINK_MODE_SGMII   0x00800000
#घोषणा E1000_CTRL_EXT_WR_WMARK_MASK  0x03000000
#घोषणा E1000_CTRL_EXT_WR_WMARK_256   0x00000000
#घोषणा E1000_CTRL_EXT_WR_WMARK_320   0x01000000
#घोषणा E1000_CTRL_EXT_WR_WMARK_384   0x02000000
#घोषणा E1000_CTRL_EXT_WR_WMARK_448   0x03000000
#घोषणा E1000_CTRL_EXT_DRV_LOAD       0x10000000	/* Driver loaded bit क्रम FW */
#घोषणा E1000_CTRL_EXT_IAME           0x08000000	/* Interrupt acknowledge Auto-mask */
#घोषणा E1000_CTRL_EXT_INT_TIMER_CLR  0x20000000	/* Clear Interrupt समयrs after IMS clear */
#घोषणा E1000_CRTL_EXT_PB_PAREN       0x01000000	/* packet buffer parity error detection enabled */
#घोषणा E1000_CTRL_EXT_DF_PAREN       0x02000000	/* descriptor FIFO parity error detection enable */
#घोषणा E1000_CTRL_EXT_GHOST_PAREN    0x40000000

/* MDI Control */
#घोषणा E1000_MDIC_DATA_MASK 0x0000FFFF
#घोषणा E1000_MDIC_REG_MASK  0x001F0000
#घोषणा E1000_MDIC_REG_SHIFT 16
#घोषणा E1000_MDIC_PHY_MASK  0x03E00000
#घोषणा E1000_MDIC_PHY_SHIFT 21
#घोषणा E1000_MDIC_OP_WRITE  0x04000000
#घोषणा E1000_MDIC_OP_READ   0x08000000
#घोषणा E1000_MDIC_READY     0x10000000
#घोषणा E1000_MDIC_INT_EN    0x20000000
#घोषणा E1000_MDIC_ERROR     0x40000000

#घोषणा INTEL_CE_GBE_MDIC_OP_WRITE      0x04000000
#घोषणा INTEL_CE_GBE_MDIC_OP_READ       0x00000000
#घोषणा INTEL_CE_GBE_MDIC_GO            0x80000000
#घोषणा INTEL_CE_GBE_MDIC_READ_ERROR    0x80000000

#घोषणा E1000_KUMCTRLSTA_MASK           0x0000FFFF
#घोषणा E1000_KUMCTRLSTA_OFFSET         0x001F0000
#घोषणा E1000_KUMCTRLSTA_OFFSET_SHIFT   16
#घोषणा E1000_KUMCTRLSTA_REN            0x00200000

#घोषणा E1000_KUMCTRLSTA_OFFSET_FIFO_CTRL      0x00000000
#घोषणा E1000_KUMCTRLSTA_OFFSET_CTRL           0x00000001
#घोषणा E1000_KUMCTRLSTA_OFFSET_INB_CTRL       0x00000002
#घोषणा E1000_KUMCTRLSTA_OFFSET_DIAG           0x00000003
#घोषणा E1000_KUMCTRLSTA_OFFSET_TIMEOUTS       0x00000004
#घोषणा E1000_KUMCTRLSTA_OFFSET_INB_PARAM      0x00000009
#घोषणा E1000_KUMCTRLSTA_OFFSET_HD_CTRL        0x00000010
#घोषणा E1000_KUMCTRLSTA_OFFSET_M2P_SERDES     0x0000001E
#घोषणा E1000_KUMCTRLSTA_OFFSET_M2P_MODES      0x0000001F

/* FIFO Control */
#घोषणा E1000_KUMCTRLSTA_FIFO_CTRL_RX_BYPASS   0x00000008
#घोषणा E1000_KUMCTRLSTA_FIFO_CTRL_TX_BYPASS   0x00000800

/* In-Band Control */
#घोषणा E1000_KUMCTRLSTA_INB_CTRL_LINK_STATUS_TX_TIMEOUT_DEFAULT    0x00000500
#घोषणा E1000_KUMCTRLSTA_INB_CTRL_DIS_PADDING  0x00000010

/* Half-Duplex Control */
#घोषणा E1000_KUMCTRLSTA_HD_CTRL_10_100_DEFAULT 0x00000004
#घोषणा E1000_KUMCTRLSTA_HD_CTRL_1000_DEFAULT  0x00000000

#घोषणा E1000_KUMCTRLSTA_OFFSET_K0S_CTRL       0x0000001E

#घोषणा E1000_KUMCTRLSTA_DIAG_FELPBK           0x2000
#घोषणा E1000_KUMCTRLSTA_DIAG_NELPBK           0x1000

#घोषणा E1000_KUMCTRLSTA_K0S_100_EN            0x2000
#घोषणा E1000_KUMCTRLSTA_K0S_GBE_EN            0x1000
#घोषणा E1000_KUMCTRLSTA_K0S_ENTRY_LATENCY_MASK   0x0003

#घोषणा E1000_KABGTXD_BGSQLBIAS                0x00050000

#घोषणा E1000_PHY_CTRL_SPD_EN                  0x00000001
#घोषणा E1000_PHY_CTRL_D0A_LPLU                0x00000002
#घोषणा E1000_PHY_CTRL_NOND0A_LPLU             0x00000004
#घोषणा E1000_PHY_CTRL_NOND0A_GBE_DISABLE      0x00000008
#घोषणा E1000_PHY_CTRL_GBE_DISABLE             0x00000040
#घोषणा E1000_PHY_CTRL_B2B_EN                  0x00000080

/* LED Control */
#घोषणा E1000_LEDCTL_LED0_MODE_MASK       0x0000000F
#घोषणा E1000_LEDCTL_LED0_MODE_SHIFT      0
#घोषणा E1000_LEDCTL_LED0_BLINK_RATE      0x0000020
#घोषणा E1000_LEDCTL_LED0_IVRT            0x00000040
#घोषणा E1000_LEDCTL_LED0_BLINK           0x00000080
#घोषणा E1000_LEDCTL_LED1_MODE_MASK       0x00000F00
#घोषणा E1000_LEDCTL_LED1_MODE_SHIFT      8
#घोषणा E1000_LEDCTL_LED1_BLINK_RATE      0x0002000
#घोषणा E1000_LEDCTL_LED1_IVRT            0x00004000
#घोषणा E1000_LEDCTL_LED1_BLINK           0x00008000
#घोषणा E1000_LEDCTL_LED2_MODE_MASK       0x000F0000
#घोषणा E1000_LEDCTL_LED2_MODE_SHIFT      16
#घोषणा E1000_LEDCTL_LED2_BLINK_RATE      0x00200000
#घोषणा E1000_LEDCTL_LED2_IVRT            0x00400000
#घोषणा E1000_LEDCTL_LED2_BLINK           0x00800000
#घोषणा E1000_LEDCTL_LED3_MODE_MASK       0x0F000000
#घोषणा E1000_LEDCTL_LED3_MODE_SHIFT      24
#घोषणा E1000_LEDCTL_LED3_BLINK_RATE      0x20000000
#घोषणा E1000_LEDCTL_LED3_IVRT            0x40000000
#घोषणा E1000_LEDCTL_LED3_BLINK           0x80000000

#घोषणा E1000_LEDCTL_MODE_LINK_10_1000  0x0
#घोषणा E1000_LEDCTL_MODE_LINK_100_1000 0x1
#घोषणा E1000_LEDCTL_MODE_LINK_UP       0x2
#घोषणा E1000_LEDCTL_MODE_ACTIVITY      0x3
#घोषणा E1000_LEDCTL_MODE_LINK_ACTIVITY 0x4
#घोषणा E1000_LEDCTL_MODE_LINK_10       0x5
#घोषणा E1000_LEDCTL_MODE_LINK_100      0x6
#घोषणा E1000_LEDCTL_MODE_LINK_1000     0x7
#घोषणा E1000_LEDCTL_MODE_PCIX_MODE     0x8
#घोषणा E1000_LEDCTL_MODE_FULL_DUPLEX   0x9
#घोषणा E1000_LEDCTL_MODE_COLLISION     0xA
#घोषणा E1000_LEDCTL_MODE_BUS_SPEED     0xB
#घोषणा E1000_LEDCTL_MODE_BUS_SIZE      0xC
#घोषणा E1000_LEDCTL_MODE_PAUSED        0xD
#घोषणा E1000_LEDCTL_MODE_LED_ON        0xE
#घोषणा E1000_LEDCTL_MODE_LED_OFF       0xF

/* Receive Address */
#घोषणा E1000_RAH_AV  0x80000000	/* Receive descriptor valid */

/* Interrupt Cause Read */
#घोषणा E1000_ICR_TXDW          0x00000001	/* Transmit desc written back */
#घोषणा E1000_ICR_TXQE          0x00000002	/* Transmit Queue empty */
#घोषणा E1000_ICR_LSC           0x00000004	/* Link Status Change */
#घोषणा E1000_ICR_RXSEQ         0x00000008	/* rx sequence error */
#घोषणा E1000_ICR_RXDMT0        0x00000010	/* rx desc min. threshold (0) */
#घोषणा E1000_ICR_RXO           0x00000040	/* rx overrun */
#घोषणा E1000_ICR_RXT0          0x00000080	/* rx समयr पूर्णांकr (ring 0) */
#घोषणा E1000_ICR_MDAC          0x00000200	/* MDIO access complete */
#घोषणा E1000_ICR_RXCFG         0x00000400	/* RX /c/ ordered set */
#घोषणा E1000_ICR_GPI_EN0       0x00000800	/* GP Int 0 */
#घोषणा E1000_ICR_GPI_EN1       0x00001000	/* GP Int 1 */
#घोषणा E1000_ICR_GPI_EN2       0x00002000	/* GP Int 2 */
#घोषणा E1000_ICR_GPI_EN3       0x00004000	/* GP Int 3 */
#घोषणा E1000_ICR_TXD_LOW       0x00008000
#घोषणा E1000_ICR_SRPD          0x00010000
#घोषणा E1000_ICR_ACK           0x00020000	/* Receive Ack frame */
#घोषणा E1000_ICR_MNG           0x00040000	/* Manageability event */
#घोषणा E1000_ICR_DOCK          0x00080000	/* Dock/Unकरोck */
#घोषणा E1000_ICR_INT_ASSERTED  0x80000000	/* If this bit निश्चितed, the driver should claim the पूर्णांकerrupt */
#घोषणा E1000_ICR_RXD_FIFO_PAR0 0x00100000	/* queue 0 Rx descriptor FIFO parity error */
#घोषणा E1000_ICR_TXD_FIFO_PAR0 0x00200000	/* queue 0 Tx descriptor FIFO parity error */
#घोषणा E1000_ICR_HOST_ARB_PAR  0x00400000	/* host arb पढ़ो buffer parity error */
#घोषणा E1000_ICR_PB_PAR        0x00800000	/* packet buffer parity error */
#घोषणा E1000_ICR_RXD_FIFO_PAR1 0x01000000	/* queue 1 Rx descriptor FIFO parity error */
#घोषणा E1000_ICR_TXD_FIFO_PAR1 0x02000000	/* queue 1 Tx descriptor FIFO parity error */
#घोषणा E1000_ICR_ALL_PARITY    0x03F00000	/* all parity error bits */
#घोषणा E1000_ICR_DSW           0x00000020	/* FW changed the status of DISSW bit in the FWSM */
#घोषणा E1000_ICR_PHYINT        0x00001000	/* LAN connected device generates an पूर्णांकerrupt */
#घोषणा E1000_ICR_EPRST         0x00100000	/* ME hardware reset occurs */

/* Interrupt Cause Set */
#घोषणा E1000_ICS_TXDW      E1000_ICR_TXDW	/* Transmit desc written back */
#घोषणा E1000_ICS_TXQE      E1000_ICR_TXQE	/* Transmit Queue empty */
#घोषणा E1000_ICS_LSC       E1000_ICR_LSC	/* Link Status Change */
#घोषणा E1000_ICS_RXSEQ     E1000_ICR_RXSEQ	/* rx sequence error */
#घोषणा E1000_ICS_RXDMT0    E1000_ICR_RXDMT0	/* rx desc min. threshold */
#घोषणा E1000_ICS_RXO       E1000_ICR_RXO	/* rx overrun */
#घोषणा E1000_ICS_RXT0      E1000_ICR_RXT0	/* rx समयr पूर्णांकr */
#घोषणा E1000_ICS_MDAC      E1000_ICR_MDAC	/* MDIO access complete */
#घोषणा E1000_ICS_RXCFG     E1000_ICR_RXCFG	/* RX /c/ ordered set */
#घोषणा E1000_ICS_GPI_EN0   E1000_ICR_GPI_EN0	/* GP Int 0 */
#घोषणा E1000_ICS_GPI_EN1   E1000_ICR_GPI_EN1	/* GP Int 1 */
#घोषणा E1000_ICS_GPI_EN2   E1000_ICR_GPI_EN2	/* GP Int 2 */
#घोषणा E1000_ICS_GPI_EN3   E1000_ICR_GPI_EN3	/* GP Int 3 */
#घोषणा E1000_ICS_TXD_LOW   E1000_ICR_TXD_LOW
#घोषणा E1000_ICS_SRPD      E1000_ICR_SRPD
#घोषणा E1000_ICS_ACK       E1000_ICR_ACK	/* Receive Ack frame */
#घोषणा E1000_ICS_MNG       E1000_ICR_MNG	/* Manageability event */
#घोषणा E1000_ICS_DOCK      E1000_ICR_DOCK	/* Dock/Unकरोck */
#घोषणा E1000_ICS_RXD_FIFO_PAR0 E1000_ICR_RXD_FIFO_PAR0	/* queue 0 Rx descriptor FIFO parity error */
#घोषणा E1000_ICS_TXD_FIFO_PAR0 E1000_ICR_TXD_FIFO_PAR0	/* queue 0 Tx descriptor FIFO parity error */
#घोषणा E1000_ICS_HOST_ARB_PAR  E1000_ICR_HOST_ARB_PAR	/* host arb पढ़ो buffer parity error */
#घोषणा E1000_ICS_PB_PAR        E1000_ICR_PB_PAR	/* packet buffer parity error */
#घोषणा E1000_ICS_RXD_FIFO_PAR1 E1000_ICR_RXD_FIFO_PAR1	/* queue 1 Rx descriptor FIFO parity error */
#घोषणा E1000_ICS_TXD_FIFO_PAR1 E1000_ICR_TXD_FIFO_PAR1	/* queue 1 Tx descriptor FIFO parity error */
#घोषणा E1000_ICS_DSW       E1000_ICR_DSW
#घोषणा E1000_ICS_PHYINT    E1000_ICR_PHYINT
#घोषणा E1000_ICS_EPRST     E1000_ICR_EPRST

/* Interrupt Mask Set */
#घोषणा E1000_IMS_TXDW      E1000_ICR_TXDW	/* Transmit desc written back */
#घोषणा E1000_IMS_TXQE      E1000_ICR_TXQE	/* Transmit Queue empty */
#घोषणा E1000_IMS_LSC       E1000_ICR_LSC	/* Link Status Change */
#घोषणा E1000_IMS_RXSEQ     E1000_ICR_RXSEQ	/* rx sequence error */
#घोषणा E1000_IMS_RXDMT0    E1000_ICR_RXDMT0	/* rx desc min. threshold */
#घोषणा E1000_IMS_RXO       E1000_ICR_RXO	/* rx overrun */
#घोषणा E1000_IMS_RXT0      E1000_ICR_RXT0	/* rx समयr पूर्णांकr */
#घोषणा E1000_IMS_MDAC      E1000_ICR_MDAC	/* MDIO access complete */
#घोषणा E1000_IMS_RXCFG     E1000_ICR_RXCFG	/* RX /c/ ordered set */
#घोषणा E1000_IMS_GPI_EN0   E1000_ICR_GPI_EN0	/* GP Int 0 */
#घोषणा E1000_IMS_GPI_EN1   E1000_ICR_GPI_EN1	/* GP Int 1 */
#घोषणा E1000_IMS_GPI_EN2   E1000_ICR_GPI_EN2	/* GP Int 2 */
#घोषणा E1000_IMS_GPI_EN3   E1000_ICR_GPI_EN3	/* GP Int 3 */
#घोषणा E1000_IMS_TXD_LOW   E1000_ICR_TXD_LOW
#घोषणा E1000_IMS_SRPD      E1000_ICR_SRPD
#घोषणा E1000_IMS_ACK       E1000_ICR_ACK	/* Receive Ack frame */
#घोषणा E1000_IMS_MNG       E1000_ICR_MNG	/* Manageability event */
#घोषणा E1000_IMS_DOCK      E1000_ICR_DOCK	/* Dock/Unकरोck */
#घोषणा E1000_IMS_RXD_FIFO_PAR0 E1000_ICR_RXD_FIFO_PAR0	/* queue 0 Rx descriptor FIFO parity error */
#घोषणा E1000_IMS_TXD_FIFO_PAR0 E1000_ICR_TXD_FIFO_PAR0	/* queue 0 Tx descriptor FIFO parity error */
#घोषणा E1000_IMS_HOST_ARB_PAR  E1000_ICR_HOST_ARB_PAR	/* host arb पढ़ो buffer parity error */
#घोषणा E1000_IMS_PB_PAR        E1000_ICR_PB_PAR	/* packet buffer parity error */
#घोषणा E1000_IMS_RXD_FIFO_PAR1 E1000_ICR_RXD_FIFO_PAR1	/* queue 1 Rx descriptor FIFO parity error */
#घोषणा E1000_IMS_TXD_FIFO_PAR1 E1000_ICR_TXD_FIFO_PAR1	/* queue 1 Tx descriptor FIFO parity error */
#घोषणा E1000_IMS_DSW       E1000_ICR_DSW
#घोषणा E1000_IMS_PHYINT    E1000_ICR_PHYINT
#घोषणा E1000_IMS_EPRST     E1000_ICR_EPRST

/* Interrupt Mask Clear */
#घोषणा E1000_IMC_TXDW      E1000_ICR_TXDW	/* Transmit desc written back */
#घोषणा E1000_IMC_TXQE      E1000_ICR_TXQE	/* Transmit Queue empty */
#घोषणा E1000_IMC_LSC       E1000_ICR_LSC	/* Link Status Change */
#घोषणा E1000_IMC_RXSEQ     E1000_ICR_RXSEQ	/* rx sequence error */
#घोषणा E1000_IMC_RXDMT0    E1000_ICR_RXDMT0	/* rx desc min. threshold */
#घोषणा E1000_IMC_RXO       E1000_ICR_RXO	/* rx overrun */
#घोषणा E1000_IMC_RXT0      E1000_ICR_RXT0	/* rx समयr पूर्णांकr */
#घोषणा E1000_IMC_MDAC      E1000_ICR_MDAC	/* MDIO access complete */
#घोषणा E1000_IMC_RXCFG     E1000_ICR_RXCFG	/* RX /c/ ordered set */
#घोषणा E1000_IMC_GPI_EN0   E1000_ICR_GPI_EN0	/* GP Int 0 */
#घोषणा E1000_IMC_GPI_EN1   E1000_ICR_GPI_EN1	/* GP Int 1 */
#घोषणा E1000_IMC_GPI_EN2   E1000_ICR_GPI_EN2	/* GP Int 2 */
#घोषणा E1000_IMC_GPI_EN3   E1000_ICR_GPI_EN3	/* GP Int 3 */
#घोषणा E1000_IMC_TXD_LOW   E1000_ICR_TXD_LOW
#घोषणा E1000_IMC_SRPD      E1000_ICR_SRPD
#घोषणा E1000_IMC_ACK       E1000_ICR_ACK	/* Receive Ack frame */
#घोषणा E1000_IMC_MNG       E1000_ICR_MNG	/* Manageability event */
#घोषणा E1000_IMC_DOCK      E1000_ICR_DOCK	/* Dock/Unकरोck */
#घोषणा E1000_IMC_RXD_FIFO_PAR0 E1000_ICR_RXD_FIFO_PAR0	/* queue 0 Rx descriptor FIFO parity error */
#घोषणा E1000_IMC_TXD_FIFO_PAR0 E1000_ICR_TXD_FIFO_PAR0	/* queue 0 Tx descriptor FIFO parity error */
#घोषणा E1000_IMC_HOST_ARB_PAR  E1000_ICR_HOST_ARB_PAR	/* host arb पढ़ो buffer parity error */
#घोषणा E1000_IMC_PB_PAR        E1000_ICR_PB_PAR	/* packet buffer parity error */
#घोषणा E1000_IMC_RXD_FIFO_PAR1 E1000_ICR_RXD_FIFO_PAR1	/* queue 1 Rx descriptor FIFO parity error */
#घोषणा E1000_IMC_TXD_FIFO_PAR1 E1000_ICR_TXD_FIFO_PAR1	/* queue 1 Tx descriptor FIFO parity error */
#घोषणा E1000_IMC_DSW       E1000_ICR_DSW
#घोषणा E1000_IMC_PHYINT    E1000_ICR_PHYINT
#घोषणा E1000_IMC_EPRST     E1000_ICR_EPRST

/* Receive Control */
#घोषणा E1000_RCTL_RST            0x00000001	/* Software reset */
#घोषणा E1000_RCTL_EN             0x00000002	/* enable */
#घोषणा E1000_RCTL_SBP            0x00000004	/* store bad packet */
#घोषणा E1000_RCTL_UPE            0x00000008	/* unicast promiscuous enable */
#घोषणा E1000_RCTL_MPE            0x00000010	/* multicast promiscuous enab */
#घोषणा E1000_RCTL_LPE            0x00000020	/* दीर्घ packet enable */
#घोषणा E1000_RCTL_LBM_NO         0x00000000	/* no loopback mode */
#घोषणा E1000_RCTL_LBM_MAC        0x00000040	/* MAC loopback mode */
#घोषणा E1000_RCTL_LBM_SLP        0x00000080	/* serial link loopback mode */
#घोषणा E1000_RCTL_LBM_TCVR       0x000000C0	/* tcvr loopback mode */
#घोषणा E1000_RCTL_DTYP_MASK      0x00000C00	/* Descriptor type mask */
#घोषणा E1000_RCTL_DTYP_PS        0x00000400	/* Packet Split descriptor */
#घोषणा E1000_RCTL_RDMTS_HALF     0x00000000	/* rx desc min threshold size */
#घोषणा E1000_RCTL_RDMTS_QUAT     0x00000100	/* rx desc min threshold size */
#घोषणा E1000_RCTL_RDMTS_EIGTH    0x00000200	/* rx desc min threshold size */
#घोषणा E1000_RCTL_MO_SHIFT       12	/* multicast offset shअगरt */
#घोषणा E1000_RCTL_MO_0           0x00000000	/* multicast offset 11:0 */
#घोषणा E1000_RCTL_MO_1           0x00001000	/* multicast offset 12:1 */
#घोषणा E1000_RCTL_MO_2           0x00002000	/* multicast offset 13:2 */
#घोषणा E1000_RCTL_MO_3           0x00003000	/* multicast offset 15:4 */
#घोषणा E1000_RCTL_MDR            0x00004000	/* multicast desc ring 0 */
#घोषणा E1000_RCTL_BAM            0x00008000	/* broadcast enable */
/* these buffer sizes are valid अगर E1000_RCTL_BSEX is 0 */
#घोषणा E1000_RCTL_SZ_2048        0x00000000	/* rx buffer size 2048 */
#घोषणा E1000_RCTL_SZ_1024        0x00010000	/* rx buffer size 1024 */
#घोषणा E1000_RCTL_SZ_512         0x00020000	/* rx buffer size 512 */
#घोषणा E1000_RCTL_SZ_256         0x00030000	/* rx buffer size 256 */
/* these buffer sizes are valid अगर E1000_RCTL_BSEX is 1 */
#घोषणा E1000_RCTL_SZ_16384       0x00010000	/* rx buffer size 16384 */
#घोषणा E1000_RCTL_SZ_8192        0x00020000	/* rx buffer size 8192 */
#घोषणा E1000_RCTL_SZ_4096        0x00030000	/* rx buffer size 4096 */
#घोषणा E1000_RCTL_VFE            0x00040000	/* vlan filter enable */
#घोषणा E1000_RCTL_CFIEN          0x00080000	/* canonical क्रमm enable */
#घोषणा E1000_RCTL_CFI            0x00100000	/* canonical क्रमm indicator */
#घोषणा E1000_RCTL_DPF            0x00400000	/* discard छोड़ो frames */
#घोषणा E1000_RCTL_PMCF           0x00800000	/* pass MAC control frames */
#घोषणा E1000_RCTL_BSEX           0x02000000	/* Buffer size extension */
#घोषणा E1000_RCTL_SECRC          0x04000000	/* Strip Ethernet CRC */
#घोषणा E1000_RCTL_FLXBUF_MASK    0x78000000	/* Flexible buffer size */
#घोषणा E1000_RCTL_FLXBUF_SHIFT   27	/* Flexible buffer shअगरt */

/* Use byte values क्रम the following shअगरt parameters
 * Usage:
 *     psrctl |= (((ROUNDUP(value0, 128) >> E1000_PSRCTL_BSIZE0_SHIFT) &
 *                  E1000_PSRCTL_BSIZE0_MASK) |
 *                ((ROUNDUP(value1, 1024) >> E1000_PSRCTL_BSIZE1_SHIFT) &
 *                  E1000_PSRCTL_BSIZE1_MASK) |
 *                ((ROUNDUP(value2, 1024) << E1000_PSRCTL_BSIZE2_SHIFT) &
 *                  E1000_PSRCTL_BSIZE2_MASK) |
 *                ((ROUNDUP(value3, 1024) << E1000_PSRCTL_BSIZE3_SHIFT) |;
 *                  E1000_PSRCTL_BSIZE3_MASK))
 * where value0 = [128..16256],  शेष=256
 *       value1 = [1024..64512], शेष=4096
 *       value2 = [0..64512],    शेष=4096
 *       value3 = [0..64512],    शेष=0
 */

#घोषणा E1000_PSRCTL_BSIZE0_MASK   0x0000007F
#घोषणा E1000_PSRCTL_BSIZE1_MASK   0x00003F00
#घोषणा E1000_PSRCTL_BSIZE2_MASK   0x003F0000
#घोषणा E1000_PSRCTL_BSIZE3_MASK   0x3F000000

#घोषणा E1000_PSRCTL_BSIZE0_SHIFT  7	/* Shअगरt _right_ 7 */
#घोषणा E1000_PSRCTL_BSIZE1_SHIFT  2	/* Shअगरt _right_ 2 */
#घोषणा E1000_PSRCTL_BSIZE2_SHIFT  6	/* Shअगरt _left_ 6 */
#घोषणा E1000_PSRCTL_BSIZE3_SHIFT 14	/* Shअगरt _left_ 14 */

/* SW_W_SYNC definitions */
#घोषणा E1000_SWFW_EEP_SM     0x0001
#घोषणा E1000_SWFW_PHY0_SM    0x0002
#घोषणा E1000_SWFW_PHY1_SM    0x0004
#घोषणा E1000_SWFW_MAC_CSR_SM 0x0008

/* Receive Descriptor */
#घोषणा E1000_RDT_DELAY 0x0000ffff	/* Delay समयr (1=1024us) */
#घोषणा E1000_RDT_FPDB  0x80000000	/* Flush descriptor block */
#घोषणा E1000_RDLEN_LEN 0x0007ff80	/* descriptor length */
#घोषणा E1000_RDH_RDH   0x0000ffff	/* receive descriptor head */
#घोषणा E1000_RDT_RDT   0x0000ffff	/* receive descriptor tail */

/* Flow Control */
#घोषणा E1000_FCRTH_RTH  0x0000FFF8	/* Mask Bits[15:3] क्रम RTH */
#घोषणा E1000_FCRTH_XFCE 0x80000000	/* External Flow Control Enable */
#घोषणा E1000_FCRTL_RTL  0x0000FFF8	/* Mask Bits[15:3] क्रम RTL */
#घोषणा E1000_FCRTL_XONE 0x80000000	/* Enable XON frame transmission */

/* Header split receive */
#घोषणा E1000_RFCTL_ISCSI_DIS           0x00000001
#घोषणा E1000_RFCTL_ISCSI_DWC_MASK      0x0000003E
#घोषणा E1000_RFCTL_ISCSI_DWC_SHIFT     1
#घोषणा E1000_RFCTL_NFSW_DIS            0x00000040
#घोषणा E1000_RFCTL_NFSR_DIS            0x00000080
#घोषणा E1000_RFCTL_NFS_VER_MASK        0x00000300
#घोषणा E1000_RFCTL_NFS_VER_SHIFT       8
#घोषणा E1000_RFCTL_IPV6_DIS            0x00000400
#घोषणा E1000_RFCTL_IPV6_XSUM_DIS       0x00000800
#घोषणा E1000_RFCTL_ACK_DIS             0x00001000
#घोषणा E1000_RFCTL_ACKD_DIS            0x00002000
#घोषणा E1000_RFCTL_IPFRSP_DIS          0x00004000
#घोषणा E1000_RFCTL_EXTEN               0x00008000
#घोषणा E1000_RFCTL_IPV6_EX_DIS         0x00010000
#घोषणा E1000_RFCTL_NEW_IPV6_EXT_DIS    0x00020000

/* Receive Descriptor Control */
#घोषणा E1000_RXDCTL_PTHRESH 0x0000003F	/* RXDCTL Prefetch Threshold */
#घोषणा E1000_RXDCTL_HTHRESH 0x00003F00	/* RXDCTL Host Threshold */
#घोषणा E1000_RXDCTL_WTHRESH 0x003F0000	/* RXDCTL Writeback Threshold */
#घोषणा E1000_RXDCTL_GRAN    0x01000000	/* RXDCTL Granularity */

/* Transmit Descriptor Control */
#घोषणा E1000_TXDCTL_PTHRESH 0x0000003F	/* TXDCTL Prefetch Threshold */
#घोषणा E1000_TXDCTL_HTHRESH 0x00003F00	/* TXDCTL Host Threshold */
#घोषणा E1000_TXDCTL_WTHRESH 0x003F0000	/* TXDCTL Writeback Threshold */
#घोषणा E1000_TXDCTL_GRAN    0x01000000	/* TXDCTL Granularity */
#घोषणा E1000_TXDCTL_LWTHRESH 0xFE000000	/* TXDCTL Low Threshold */
#घोषणा E1000_TXDCTL_FULL_TX_DESC_WB 0x01010000	/* GRAN=1, WTHRESH=1 */
#घोषणा E1000_TXDCTL_COUNT_DESC 0x00400000	/* Enable the counting of desc.
						   still to be processed. */
/* Transmit Configuration Word */
#घोषणा E1000_TXCW_FD         0x00000020	/* TXCW full duplex */
#घोषणा E1000_TXCW_HD         0x00000040	/* TXCW half duplex */
#घोषणा E1000_TXCW_PAUSE      0x00000080	/* TXCW sym छोड़ो request */
#घोषणा E1000_TXCW_ASM_सूची    0x00000100	/* TXCW asपंचांग छोड़ो direction */
#घोषणा E1000_TXCW_PAUSE_MASK 0x00000180	/* TXCW छोड़ो request mask */
#घोषणा E1000_TXCW_RF         0x00003000	/* TXCW remote fault */
#घोषणा E1000_TXCW_NP         0x00008000	/* TXCW next page */
#घोषणा E1000_TXCW_CW         0x0000ffff	/* TxConfigWord mask */
#घोषणा E1000_TXCW_TXC        0x40000000	/* Transmit Config control */
#घोषणा E1000_TXCW_ANE        0x80000000	/* Auto-neg enable */

/* Receive Configuration Word */
#घोषणा E1000_RXCW_CW    0x0000ffff	/* RxConfigWord mask */
#घोषणा E1000_RXCW_NC    0x04000000	/* Receive config no carrier */
#घोषणा E1000_RXCW_IV    0x08000000	/* Receive config invalid */
#घोषणा E1000_RXCW_CC    0x10000000	/* Receive config change */
#घोषणा E1000_RXCW_C     0x20000000	/* Receive config */
#घोषणा E1000_RXCW_SYNCH 0x40000000	/* Receive config synch */
#घोषणा E1000_RXCW_ANC   0x80000000	/* Auto-neg complete */

/* Transmit Control */
#घोषणा E1000_TCTL_RST    0x00000001	/* software reset */
#घोषणा E1000_TCTL_EN     0x00000002	/* enable tx */
#घोषणा E1000_TCTL_BCE    0x00000004	/* busy check enable */
#घोषणा E1000_TCTL_PSP    0x00000008	/* pad लघु packets */
#घोषणा E1000_TCTL_CT     0x00000ff0	/* collision threshold */
#घोषणा E1000_TCTL_COLD   0x003ff000	/* collision distance */
#घोषणा E1000_TCTL_SWXOFF 0x00400000	/* SW Xoff transmission */
#घोषणा E1000_TCTL_PBE    0x00800000	/* Packet Burst Enable */
#घोषणा E1000_TCTL_RTLC   0x01000000	/* Re-transmit on late collision */
#घोषणा E1000_TCTL_NRTU   0x02000000	/* No Re-transmit on underrun */
#घोषणा E1000_TCTL_MULR   0x10000000	/* Multiple request support */
/* Extended Transmit Control */
#घोषणा E1000_TCTL_EXT_BST_MASK  0x000003FF	/* Backoff Slot Time */
#घोषणा E1000_TCTL_EXT_GCEX_MASK 0x000FFC00	/* Gigabit Carry Extend Padding */

/* Receive Checksum Control */
#घोषणा E1000_RXCSUM_PCSS_MASK 0x000000FF	/* Packet Checksum Start */
#घोषणा E1000_RXCSUM_IPOFL     0x00000100	/* IPv4 checksum offload */
#घोषणा E1000_RXCSUM_TUOFL     0x00000200	/* TCP / UDP checksum offload */
#घोषणा E1000_RXCSUM_IPV6OFL   0x00000400	/* IPv6 checksum offload */
#घोषणा E1000_RXCSUM_IPPCSE    0x00001000	/* IP payload checksum enable */
#घोषणा E1000_RXCSUM_PCSD      0x00002000	/* packet checksum disabled */

/* Multiple Receive Queue Control */
#घोषणा E1000_MRQC_ENABLE_MASK              0x00000003
#घोषणा E1000_MRQC_ENABLE_RSS_2Q            0x00000001
#घोषणा E1000_MRQC_ENABLE_RSS_INT           0x00000004
#घोषणा E1000_MRQC_RSS_FIELD_MASK           0xFFFF0000
#घोषणा E1000_MRQC_RSS_FIELD_IPV4_TCP       0x00010000
#घोषणा E1000_MRQC_RSS_FIELD_IPV4           0x00020000
#घोषणा E1000_MRQC_RSS_FIELD_IPV6_TCP_EX    0x00040000
#घोषणा E1000_MRQC_RSS_FIELD_IPV6_EX        0x00080000
#घोषणा E1000_MRQC_RSS_FIELD_IPV6           0x00100000
#घोषणा E1000_MRQC_RSS_FIELD_IPV6_TCP       0x00200000

/* Definitions क्रम घातer management and wakeup रेजिस्टरs */
/* Wake Up Control */
#घोषणा E1000_WUC_APME       0x00000001	/* APM Enable */
#घोषणा E1000_WUC_PME_EN     0x00000002	/* PME Enable */
#घोषणा E1000_WUC_PME_STATUS 0x00000004	/* PME Status */
#घोषणा E1000_WUC_APMPME     0x00000008	/* Assert PME on APM Wakeup */
#घोषणा E1000_WUC_SPM        0x80000000	/* Enable SPM */

/* Wake Up Filter Control */
#घोषणा E1000_WUFC_LNKC 0x00000001	/* Link Status Change Wakeup Enable */
#घोषणा E1000_WUFC_MAG  0x00000002	/* Magic Packet Wakeup Enable */
#घोषणा E1000_WUFC_EX   0x00000004	/* Directed Exact Wakeup Enable */
#घोषणा E1000_WUFC_MC   0x00000008	/* Directed Multicast Wakeup Enable */
#घोषणा E1000_WUFC_BC   0x00000010	/* Broadcast Wakeup Enable */
#घोषणा E1000_WUFC_ARP  0x00000020	/* ARP Request Packet Wakeup Enable */
#घोषणा E1000_WUFC_IPV4 0x00000040	/* Directed IPv4 Packet Wakeup Enable */
#घोषणा E1000_WUFC_IPV6 0x00000080	/* Directed IPv6 Packet Wakeup Enable */
#घोषणा E1000_WUFC_IGNORE_TCO      0x00008000	/* Ignore WakeOn TCO packets */
#घोषणा E1000_WUFC_FLX0 0x00010000	/* Flexible Filter 0 Enable */
#घोषणा E1000_WUFC_FLX1 0x00020000	/* Flexible Filter 1 Enable */
#घोषणा E1000_WUFC_FLX2 0x00040000	/* Flexible Filter 2 Enable */
#घोषणा E1000_WUFC_FLX3 0x00080000	/* Flexible Filter 3 Enable */
#घोषणा E1000_WUFC_ALL_FILTERS 0x000F00FF	/* Mask क्रम all wakeup filters */
#घोषणा E1000_WUFC_FLX_OFFSET 16	/* Offset to the Flexible Filters bits */
#घोषणा E1000_WUFC_FLX_FILTERS 0x000F0000	/* Mask क्रम the 4 flexible filters */

/* Wake Up Status */
#घोषणा E1000_WUS_LNKC 0x00000001	/* Link Status Changed */
#घोषणा E1000_WUS_MAG  0x00000002	/* Magic Packet Received */
#घोषणा E1000_WUS_EX   0x00000004	/* Directed Exact Received */
#घोषणा E1000_WUS_MC   0x00000008	/* Directed Multicast Received */
#घोषणा E1000_WUS_BC   0x00000010	/* Broadcast Received */
#घोषणा E1000_WUS_ARP  0x00000020	/* ARP Request Packet Received */
#घोषणा E1000_WUS_IPV4 0x00000040	/* Directed IPv4 Packet Wakeup Received */
#घोषणा E1000_WUS_IPV6 0x00000080	/* Directed IPv6 Packet Wakeup Received */
#घोषणा E1000_WUS_FLX0 0x00010000	/* Flexible Filter 0 Match */
#घोषणा E1000_WUS_FLX1 0x00020000	/* Flexible Filter 1 Match */
#घोषणा E1000_WUS_FLX2 0x00040000	/* Flexible Filter 2 Match */
#घोषणा E1000_WUS_FLX3 0x00080000	/* Flexible Filter 3 Match */
#घोषणा E1000_WUS_FLX_FILTERS 0x000F0000	/* Mask क्रम the 4 flexible filters */

/* Management Control */
#घोषणा E1000_MANC_SMBUS_EN      0x00000001	/* SMBus Enabled - RO */
#घोषणा E1000_MANC_ASF_EN        0x00000002	/* ASF Enabled - RO */
#घोषणा E1000_MANC_R_ON_FORCE    0x00000004	/* Reset on Force TCO - RO */
#घोषणा E1000_MANC_RMCP_EN       0x00000100	/* Enable RCMP 026Fh Filtering */
#घोषणा E1000_MANC_0298_EN       0x00000200	/* Enable RCMP 0298h Filtering */
#घोषणा E1000_MANC_IPV4_EN       0x00000400	/* Enable IPv4 */
#घोषणा E1000_MANC_IPV6_EN       0x00000800	/* Enable IPv6 */
#घोषणा E1000_MANC_SNAP_EN       0x00001000	/* Accept LLC/SNAP */
#घोषणा E1000_MANC_ARP_EN        0x00002000	/* Enable ARP Request Filtering */
#घोषणा E1000_MANC_NEIGHBOR_EN   0x00004000	/* Enable Neighbor Discovery
						 * Filtering */
#घोषणा E1000_MANC_ARP_RES_EN    0x00008000	/* Enable ARP response Filtering */
#घोषणा E1000_MANC_TCO_RESET     0x00010000	/* TCO Reset Occurred */
#घोषणा E1000_MANC_RCV_TCO_EN    0x00020000	/* Receive TCO Packets Enabled */
#घोषणा E1000_MANC_REPORT_STATUS 0x00040000	/* Status Reporting Enabled */
#घोषणा E1000_MANC_RCV_ALL       0x00080000	/* Receive All Enabled */
#घोषणा E1000_MANC_BLK_PHY_RST_ON_IDE   0x00040000	/* Block phy resets */
#घोषणा E1000_MANC_EN_MAC_ADDR_FILTER   0x00100000	/* Enable MAC address
							 * filtering */
#घोषणा E1000_MANC_EN_MNG2HOST   0x00200000	/* Enable MNG packets to host
						 * memory */
#घोषणा E1000_MANC_EN_IP_ADDR_FILTER    0x00400000	/* Enable IP address
							 * filtering */
#घोषणा E1000_MANC_EN_XSUM_FILTER   0x00800000	/* Enable checksum filtering */
#घोषणा E1000_MANC_BR_EN         0x01000000	/* Enable broadcast filtering */
#घोषणा E1000_MANC_SMB_REQ       0x01000000	/* SMBus Request */
#घोषणा E1000_MANC_SMB_GNT       0x02000000	/* SMBus Grant */
#घोषणा E1000_MANC_SMB_CLK_IN    0x04000000	/* SMBus Clock In */
#घोषणा E1000_MANC_SMB_DATA_IN   0x08000000	/* SMBus Data In */
#घोषणा E1000_MANC_SMB_DATA_OUT  0x10000000	/* SMBus Data Out */
#घोषणा E1000_MANC_SMB_CLK_OUT   0x20000000	/* SMBus Clock Out */

#घोषणा E1000_MANC_SMB_DATA_OUT_SHIFT  28	/* SMBus Data Out Shअगरt */
#घोषणा E1000_MANC_SMB_CLK_OUT_SHIFT   29	/* SMBus Clock Out Shअगरt */

/* SW Semaphore Register */
#घोषणा E1000_SWSM_SMBI         0x00000001	/* Driver Semaphore bit */
#घोषणा E1000_SWSM_SWESMBI      0x00000002	/* FW Semaphore bit */
#घोषणा E1000_SWSM_WMNG         0x00000004	/* Wake MNG Clock */
#घोषणा E1000_SWSM_DRV_LOAD     0x00000008	/* Driver Loaded Bit */

/* FW Semaphore Register */
#घोषणा E1000_FWSM_MODE_MASK    0x0000000E	/* FW mode */
#घोषणा E1000_FWSM_MODE_SHIFT            1
#घोषणा E1000_FWSM_FW_VALID     0x00008000	/* FW established a valid mode */

#घोषणा E1000_FWSM_RSPCIPHY        0x00000040	/* Reset PHY on PCI reset */
#घोषणा E1000_FWSM_DISSW           0x10000000	/* FW disable SW Write Access */
#घोषणा E1000_FWSM_SKUSEL_MASK     0x60000000	/* LAN SKU select */
#घोषणा E1000_FWSM_SKUEL_SHIFT     29
#घोषणा E1000_FWSM_SKUSEL_EMB      0x0	/* Embedded SKU */
#घोषणा E1000_FWSM_SKUSEL_CONS     0x1	/* Consumer SKU */
#घोषणा E1000_FWSM_SKUSEL_PERF_100 0x2	/* Perf & Corp 10/100 SKU */
#घोषणा E1000_FWSM_SKUSEL_PERF_GBE 0x3	/* Perf & Copr GbE SKU */

/* FFLT Debug Register */
#घोषणा E1000_FFLT_DBG_INVC     0x00100000	/* Invalid /C/ code handling */

प्रकार क्रमागत अणु
	e1000_mng_mode_none = 0,
	e1000_mng_mode_asf,
	e1000_mng_mode_pt,
	e1000_mng_mode_ipmi,
	e1000_mng_mode_host_पूर्णांकerface_only
पूर्ण e1000_mng_mode;

/* Host Interface Control Register */
#घोषणा E1000_HICR_EN           0x00000001	/* Enable Bit - RO */
#घोषणा E1000_HICR_C            0x00000002	/* Driver sets this bit when करोne
						 * to put command in RAM */
#घोषणा E1000_HICR_SV           0x00000004	/* Status Validity */
#घोषणा E1000_HICR_FWR          0x00000080	/* FW reset. Set by the Host */

/* Host Interface Command Interface - Address range 0x8800-0x8EFF */
#घोषणा E1000_HI_MAX_DATA_LENGTH         252	/* Host Interface data length */
#घोषणा E1000_HI_MAX_BLOCK_BYTE_LENGTH  1792	/* Number of bytes in range */
#घोषणा E1000_HI_MAX_BLOCK_DWORD_LENGTH  448	/* Number of dwords in range */
#घोषणा E1000_HI_COMMAND_TIMEOUT         500	/* Time in ms to process HI command */

काष्ठा e1000_host_command_header अणु
	u8 command_id;
	u8 command_length;
	u8 command_options;	/* I/F bits क्रम command, status क्रम वापस */
	u8 checksum;
पूर्ण;
काष्ठा e1000_host_command_info अणु
	काष्ठा e1000_host_command_header command_header;	/* Command Head/Command Result Head has 4 bytes */
	u8 command_data[E1000_HI_MAX_DATA_LENGTH];	/* Command data can length 0..252 */
पूर्ण;

/* Host SMB रेजिस्टर #0 */
#घोषणा E1000_HSMC0R_CLKIN      0x00000001	/* SMB Clock in */
#घोषणा E1000_HSMC0R_DATAIN     0x00000002	/* SMB Data in */
#घोषणा E1000_HSMC0R_DATAOUT    0x00000004	/* SMB Data out */
#घोषणा E1000_HSMC0R_CLKOUT     0x00000008	/* SMB Clock out */

/* Host SMB रेजिस्टर #1 */
#घोषणा E1000_HSMC1R_CLKIN      E1000_HSMC0R_CLKIN
#घोषणा E1000_HSMC1R_DATAIN     E1000_HSMC0R_DATAIN
#घोषणा E1000_HSMC1R_DATAOUT    E1000_HSMC0R_DATAOUT
#घोषणा E1000_HSMC1R_CLKOUT     E1000_HSMC0R_CLKOUT

/* FW Status Register */
#घोषणा E1000_FWSTS_FWS_MASK    0x000000FF	/* FW Status */

/* Wake Up Packet Length */
#घोषणा E1000_WUPL_LENGTH_MASK 0x0FFF	/* Only the lower 12 bits are valid */

#घोषणा E1000_MDALIGN          4096

/* PCI-Ex रेजिस्टरs*/

/* PCI-Ex Control Register */
#घोषणा E1000_GCR_RXD_NO_SNOOP          0x00000001
#घोषणा E1000_GCR_RXDSCW_NO_SNOOP       0x00000002
#घोषणा E1000_GCR_RXDSCR_NO_SNOOP       0x00000004
#घोषणा E1000_GCR_TXD_NO_SNOOP          0x00000008
#घोषणा E1000_GCR_TXDSCW_NO_SNOOP       0x00000010
#घोषणा E1000_GCR_TXDSCR_NO_SNOOP       0x00000020

#घोषणा PCI_EX_NO_SNOOP_ALL (E1000_GCR_RXD_NO_SNOOP         | \
                             E1000_GCR_RXDSCW_NO_SNOOP      | \
                             E1000_GCR_RXDSCR_NO_SNOOP      | \
                             E1000_GCR_TXD_NO_SNOOP         | \
                             E1000_GCR_TXDSCW_NO_SNOOP      | \
                             E1000_GCR_TXDSCR_NO_SNOOP)

#घोषणा PCI_EX_82566_SNOOP_ALL PCI_EX_NO_SNOOP_ALL

#घोषणा E1000_GCR_L1_ACT_WITHOUT_L0S_RX 0x08000000
/* Function Active and Power State to MNG */
#घोषणा E1000_FACTPS_FUNC0_POWER_STATE_MASK         0x00000003
#घोषणा E1000_FACTPS_LAN0_VALID                     0x00000004
#घोषणा E1000_FACTPS_FUNC0_AUX_EN                   0x00000008
#घोषणा E1000_FACTPS_FUNC1_POWER_STATE_MASK         0x000000C0
#घोषणा E1000_FACTPS_FUNC1_POWER_STATE_SHIFT        6
#घोषणा E1000_FACTPS_LAN1_VALID                     0x00000100
#घोषणा E1000_FACTPS_FUNC1_AUX_EN                   0x00000200
#घोषणा E1000_FACTPS_FUNC2_POWER_STATE_MASK         0x00003000
#घोषणा E1000_FACTPS_FUNC2_POWER_STATE_SHIFT        12
#घोषणा E1000_FACTPS_IDE_ENABLE                     0x00004000
#घोषणा E1000_FACTPS_FUNC2_AUX_EN                   0x00008000
#घोषणा E1000_FACTPS_FUNC3_POWER_STATE_MASK         0x000C0000
#घोषणा E1000_FACTPS_FUNC3_POWER_STATE_SHIFT        18
#घोषणा E1000_FACTPS_SP_ENABLE                      0x00100000
#घोषणा E1000_FACTPS_FUNC3_AUX_EN                   0x00200000
#घोषणा E1000_FACTPS_FUNC4_POWER_STATE_MASK         0x03000000
#घोषणा E1000_FACTPS_FUNC4_POWER_STATE_SHIFT        24
#घोषणा E1000_FACTPS_IPMI_ENABLE                    0x04000000
#घोषणा E1000_FACTPS_FUNC4_AUX_EN                   0x08000000
#घोषणा E1000_FACTPS_MNGCG                          0x20000000
#घोषणा E1000_FACTPS_LAN_FUNC_SEL                   0x40000000
#घोषणा E1000_FACTPS_PM_STATE_CHANGED               0x80000000

/* PCI-Ex Config Space */
#घोषणा PCI_EX_LINK_STATUS           0x12
#घोषणा PCI_EX_LINK_WIDTH_MASK       0x3F0
#घोषणा PCI_EX_LINK_WIDTH_SHIFT      4

/* EEPROM Commands - Microwire */
#घोषणा EEPROM_READ_OPCODE_MICROWIRE  0x6	/* EEPROM पढ़ो opcode */
#घोषणा EEPROM_WRITE_OPCODE_MICROWIRE 0x5	/* EEPROM ग_लिखो opcode */
#घोषणा EEPROM_ERASE_OPCODE_MICROWIRE 0x7	/* EEPROM erase opcode */
#घोषणा EEPROM_EWEN_OPCODE_MICROWIRE  0x13	/* EEPROM erase/ग_लिखो enable */
#घोषणा EEPROM_EWDS_OPCODE_MICROWIRE  0x10	/* EEPROM erase/ग_लिखो disable */

/* EEPROM Commands - SPI */
#घोषणा EEPROM_MAX_RETRY_SPI        5000	/* Max रुको of 5ms, क्रम RDY संकेत */
#घोषणा EEPROM_READ_OPCODE_SPI      0x03	/* EEPROM पढ़ो opcode */
#घोषणा EEPROM_WRITE_OPCODE_SPI     0x02	/* EEPROM ग_लिखो opcode */
#घोषणा EEPROM_A8_OPCODE_SPI        0x08	/* opcode bit-3 = address bit-8 */
#घोषणा EEPROM_WREN_OPCODE_SPI      0x06	/* EEPROM set Write Enable latch */
#घोषणा EEPROM_WRDI_OPCODE_SPI      0x04	/* EEPROM reset Write Enable latch */
#घोषणा EEPROM_RDSR_OPCODE_SPI      0x05	/* EEPROM पढ़ो Status रेजिस्टर */
#घोषणा EEPROM_WRSR_OPCODE_SPI      0x01	/* EEPROM ग_लिखो Status रेजिस्टर */
#घोषणा EEPROM_ERASE4K_OPCODE_SPI   0x20	/* EEPROM ERASE 4KB */
#घोषणा EEPROM_ERASE64K_OPCODE_SPI  0xD8	/* EEPROM ERASE 64KB */
#घोषणा EEPROM_ERASE256_OPCODE_SPI  0xDB	/* EEPROM ERASE 256B */

/* EEPROM Size definitions */
#घोषणा EEPROM_WORD_SIZE_SHIFT  6
#घोषणा EEPROM_SIZE_SHIFT       10
#घोषणा EEPROM_SIZE_MASK        0x1C00

/* EEPROM Word Offsets */
#घोषणा EEPROM_COMPAT                 0x0003
#घोषणा EEPROM_ID_LED_SETTINGS        0x0004
#घोषणा EEPROM_VERSION                0x0005
#घोषणा EEPROM_SERDES_AMPLITUDE       0x0006	/* For SERDES output amplitude adjusपंचांगent. */
#घोषणा EEPROM_PHY_CLASS_WORD         0x0007
#घोषणा EEPROM_INIT_CONTROL1_REG      0x000A
#घोषणा EEPROM_INIT_CONTROL2_REG      0x000F
#घोषणा EEPROM_SWDEF_PINS_CTRL_PORT_1 0x0010
#घोषणा EEPROM_INIT_CONTROL3_PORT_B   0x0014
#घोषणा EEPROM_INIT_3GIO_3            0x001A
#घोषणा EEPROM_SWDEF_PINS_CTRL_PORT_0 0x0020
#घोषणा EEPROM_INIT_CONTROL3_PORT_A   0x0024
#घोषणा EEPROM_CFG                    0x0012
#घोषणा EEPROM_FLASH_VERSION          0x0032
#घोषणा EEPROM_CHECKSUM_REG           0x003F

#घोषणा E1000_EEPROM_CFG_DONE         0x00040000	/* MNG config cycle करोne */
#घोषणा E1000_EEPROM_CFG_DONE_PORT_1  0x00080000	/* ...क्रम second port */

/* Word definitions क्रम ID LED Settings */
#घोषणा ID_LED_RESERVED_0000 0x0000
#घोषणा ID_LED_RESERVED_FFFF 0xFFFF
#घोषणा ID_LED_DEFAULT       ((ID_LED_OFF1_ON2 << 12) | \
                              (ID_LED_OFF1_OFF2 << 8) | \
                              (ID_LED_DEF1_DEF2 << 4) | \
                              (ID_LED_DEF1_DEF2))
#घोषणा ID_LED_DEF1_DEF2     0x1
#घोषणा ID_LED_DEF1_ON2      0x2
#घोषणा ID_LED_DEF1_OFF2     0x3
#घोषणा ID_LED_ON1_DEF2      0x4
#घोषणा ID_LED_ON1_ON2       0x5
#घोषणा ID_LED_ON1_OFF2      0x6
#घोषणा ID_LED_OFF1_DEF2     0x7
#घोषणा ID_LED_OFF1_ON2      0x8
#घोषणा ID_LED_OFF1_OFF2     0x9

#घोषणा IGP_ACTIVITY_LED_MASK   0xFFFFF0FF
#घोषणा IGP_ACTIVITY_LED_ENABLE 0x0300
#घोषणा IGP_LED3_MODE           0x07000000

/* Mask bits क्रम SERDES amplitude adjusपंचांगent in Word 6 of the EEPROM */
#घोषणा EEPROM_SERDES_AMPLITUDE_MASK  0x000F

/* Mask bit क्रम PHY class in Word 7 of the EEPROM */
#घोषणा EEPROM_PHY_CLASS_A   0x8000

/* Mask bits क्रम fields in Word 0x0a of the EEPROM */
#घोषणा EEPROM_WORD0A_ILOS   0x0010
#घोषणा EEPROM_WORD0A_SWDPIO 0x01E0
#घोषणा EEPROM_WORD0A_LRST   0x0200
#घोषणा EEPROM_WORD0A_FD     0x0400
#घोषणा EEPROM_WORD0A_66MHZ  0x0800

/* Mask bits क्रम fields in Word 0x0f of the EEPROM */
#घोषणा EEPROM_WORD0F_PAUSE_MASK 0x3000
#घोषणा EEPROM_WORD0F_PAUSE      0x1000
#घोषणा EEPROM_WORD0F_ASM_सूची    0x2000
#घोषणा EEPROM_WORD0F_ANE        0x0800
#घोषणा EEPROM_WORD0F_SWPDIO_EXT 0x00F0
#घोषणा EEPROM_WORD0F_LPLU       0x0001

/* Mask bits क्रम fields in Word 0x10/0x20 of the EEPROM */
#घोषणा EEPROM_WORD1020_GIGA_DISABLE         0x0010
#घोषणा EEPROM_WORD1020_GIGA_DISABLE_NON_D0A 0x0008

/* Mask bits क्रम fields in Word 0x1a of the EEPROM */
#घोषणा EEPROM_WORD1A_ASPM_MASK  0x000C

/* For checksumming, the sum of all words in the EEPROM should equal 0xBABA. */
#घोषणा EEPROM_SUM 0xBABA

/* EEPROM Map defines (WORD OFFSETS)*/
#घोषणा EEPROM_NODE_ADDRESS_BYTE_0 0
#घोषणा EEPROM_PBA_BYTE_1          8

#घोषणा EEPROM_RESERVED_WORD          0xFFFF

/* EEPROM Map Sizes (Byte Counts) */
#घोषणा PBA_SIZE 4

/* Collision related configuration parameters */
#घोषणा E1000_COLLISION_THRESHOLD       15
#घोषणा E1000_CT_SHIFT                  4
/* Collision distance is a 0-based value that applies to
 * half-duplex-capable hardware only. */
#घोषणा E1000_COLLISION_DISTANCE        63
#घोषणा E1000_COLLISION_DISTANCE_82542  64
#घोषणा E1000_FDX_COLLISION_DISTANCE    E1000_COLLISION_DISTANCE
#घोषणा E1000_HDX_COLLISION_DISTANCE    E1000_COLLISION_DISTANCE
#घोषणा E1000_COLD_SHIFT                12

/* Number of Transmit and Receive Descriptors must be a multiple of 8 */
#घोषणा REQ_TX_DESCRIPTOR_MULTIPLE  8
#घोषणा REQ_RX_DESCRIPTOR_MULTIPLE  8

/* Default values क्रम the transmit IPG रेजिस्टर */
#घोषणा DEFAULT_82542_TIPG_IPGT        10
#घोषणा DEFAULT_82543_TIPG_IPGT_FIBER  9
#घोषणा DEFAULT_82543_TIPG_IPGT_COPPER 8

#घोषणा E1000_TIPG_IPGT_MASK  0x000003FF
#घोषणा E1000_TIPG_IPGR1_MASK 0x000FFC00
#घोषणा E1000_TIPG_IPGR2_MASK 0x3FF00000

#घोषणा DEFAULT_82542_TIPG_IPGR1 2
#घोषणा DEFAULT_82543_TIPG_IPGR1 8
#घोषणा E1000_TIPG_IPGR1_SHIFT  10

#घोषणा DEFAULT_82542_TIPG_IPGR2 10
#घोषणा DEFAULT_82543_TIPG_IPGR2 6
#घोषणा E1000_TIPG_IPGR2_SHIFT  20

#घोषणा E1000_TXDMAC_DPP 0x00000001

/* Adaptive IFS defines */
#घोषणा TX_THRESHOLD_START     8
#घोषणा TX_THRESHOLD_INCREMENT 10
#घोषणा TX_THRESHOLD_DECREMENT 1
#घोषणा TX_THRESHOLD_STOP      190
#घोषणा TX_THRESHOLD_DISABLE   0
#घोषणा TX_THRESHOLD_TIMER_MS  10000
#घोषणा MIN_NUM_XMITS          1000
#घोषणा IFS_MAX                80
#घोषणा IFS_STEP               10
#घोषणा IFS_MIN                40
#घोषणा IFS_RATIO              4

/* Extended Configuration Control and Size */
#घोषणा E1000_EXTCNF_CTRL_PCIE_WRITE_ENABLE 0x00000001
#घोषणा E1000_EXTCNF_CTRL_PHY_WRITE_ENABLE  0x00000002
#घोषणा E1000_EXTCNF_CTRL_D_UD_ENABLE       0x00000004
#घोषणा E1000_EXTCNF_CTRL_D_UD_LATENCY      0x00000008
#घोषणा E1000_EXTCNF_CTRL_D_UD_OWNER        0x00000010
#घोषणा E1000_EXTCNF_CTRL_MDIO_SW_OWNERSHIP 0x00000020
#घोषणा E1000_EXTCNF_CTRL_MDIO_HW_OWNERSHIP 0x00000040
#घोषणा E1000_EXTCNF_CTRL_EXT_CNF_POINTER   0x0FFF0000

#घोषणा E1000_EXTCNF_SIZE_EXT_PHY_LENGTH    0x000000FF
#घोषणा E1000_EXTCNF_SIZE_EXT_DOCK_LENGTH   0x0000FF00
#घोषणा E1000_EXTCNF_SIZE_EXT_PCIE_LENGTH   0x00FF0000
#घोषणा E1000_EXTCNF_CTRL_LCD_WRITE_ENABLE  0x00000001
#घोषणा E1000_EXTCNF_CTRL_SWFLAG            0x00000020

/* PBA स्थिरants */
#घोषणा E1000_PBA_8K 0x0008	/* 8KB, शेष Rx allocation */
#घोषणा E1000_PBA_12K 0x000C	/* 12KB, शेष Rx allocation */
#घोषणा E1000_PBA_16K 0x0010	/* 16KB, शेष TX allocation */
#घोषणा E1000_PBA_20K 0x0014
#घोषणा E1000_PBA_22K 0x0016
#घोषणा E1000_PBA_24K 0x0018
#घोषणा E1000_PBA_30K 0x001E
#घोषणा E1000_PBA_32K 0x0020
#घोषणा E1000_PBA_34K 0x0022
#घोषणा E1000_PBA_38K 0x0026
#घोषणा E1000_PBA_40K 0x0028
#घोषणा E1000_PBA_48K 0x0030	/* 48KB, शेष RX allocation */

#घोषणा E1000_PBS_16K E1000_PBA_16K

/* Flow Control Constants */
#घोषणा FLOW_CONTROL_ADDRESS_LOW  0x00C28001
#घोषणा FLOW_CONTROL_ADDRESS_HIGH 0x00000100
#घोषणा FLOW_CONTROL_TYPE         0x8808

/* The historical शेषs क्रम the flow control values are given below. */
#घोषणा FC_DEFAULT_HI_THRESH        (0x8000)	/* 32KB */
#घोषणा FC_DEFAULT_LO_THRESH        (0x4000)	/* 16KB */
#घोषणा FC_DEFAULT_TX_TIMER         (0x100)	/* ~130 us */

/* PCIX Config space */
#घोषणा PCIX_COMMAND_REGISTER    0xE6
#घोषणा PCIX_STATUS_REGISTER_LO  0xE8
#घोषणा PCIX_STATUS_REGISTER_HI  0xEA

#घोषणा PCIX_COMMAND_MMRBC_MASK      0x000C
#घोषणा PCIX_COMMAND_MMRBC_SHIFT     0x2
#घोषणा PCIX_STATUS_HI_MMRBC_MASK    0x0060
#घोषणा PCIX_STATUS_HI_MMRBC_SHIFT   0x5
#घोषणा PCIX_STATUS_HI_MMRBC_4K      0x3
#घोषणा PCIX_STATUS_HI_MMRBC_2K      0x2

/* Number of bits required to shअगरt right the "pause" bits from the
 * EEPROM (bits 13:12) to the "pause" (bits 8:7) field in the TXCW रेजिस्टर.
 */
#घोषणा PAUSE_SHIFT 5

/* Number of bits required to shअगरt left the "SWDPIO" bits from the
 * EEPROM (bits 8:5) to the "SWDPIO" (bits 25:22) field in the CTRL रेजिस्टर.
 */
#घोषणा SWDPIO_SHIFT 17

/* Number of bits required to shअगरt left the "SWDPIO_EXT" bits from the
 * EEPROM word F (bits 7:4) to the bits 11:8 of The Extended CTRL रेजिस्टर.
 */
#घोषणा SWDPIO__EXT_SHIFT 4

/* Number of bits required to shअगरt left the "ILOS" bit from the EEPROM
 * (bit 4) to the "ILOS" (bit 7) field in the CTRL रेजिस्टर.
 */
#घोषणा ILOS_SHIFT  3

#घोषणा RECEIVE_BUFFER_ALIGN_SIZE  (256)

/* Number of milliseconds we रुको क्रम स्वतः-negotiation to complete */
#घोषणा LINK_UP_TIMEOUT             500

/* Number of milliseconds we रुको क्रम Eeprom स्वतः पढ़ो bit करोne after MAC reset */
#घोषणा AUTO_READ_DONE_TIMEOUT      10
/* Number of milliseconds we रुको क्रम PHY configuration करोne after MAC reset */
#घोषणा PHY_CFG_TIMEOUT             100

#घोषणा E1000_TX_BUFFER_SIZE ((u32)1514)

/* The carrier extension symbol, as received by the NIC. */
#घोषणा CARRIER_EXTENSION   0x0F

/* TBI_ACCEPT macro definition:
 *
 * This macro requires:
 *      adapter = a poपूर्णांकer to काष्ठा e1000_hw
 *      status = the 8 bit status field of the RX descriptor with EOP set
 *      error = the 8 bit error field of the RX descriptor with EOP set
 *      length = the sum of all the length fields of the RX descriptors that
 *               make up the current frame
 *      last_byte = the last byte of the frame DMAed by the hardware
 *      max_frame_length = the maximum frame length we want to accept.
 *      min_frame_length = the minimum frame length we want to accept.
 *
 * This macro is a conditional that should be used in the पूर्णांकerrupt
 * handler's Rx processing routine when RxErrors have been detected.
 *
 * Typical use:
 *  ...
 *  अगर (TBI_ACCEPT) अणु
 *      accept_frame = true;
 *      e1000_tbi_adjust_stats(adapter, MacAddress);
 *      frame_length--;
 *  पूर्ण अन्यथा अणु
 *      accept_frame = false;
 *  पूर्ण
 *  ...
 */

#घोषणा TBI_ACCEPT(adapter, status, errors, length, last_byte) \
    ((adapter)->tbi_compatibility_on && \
     (((errors) & E1000_RXD_ERR_FRAME_ERR_MASK) == E1000_RXD_ERR_CE) && \
     ((last_byte) == CARRIER_EXTENSION) && \
     (((status) & E1000_RXD_STAT_VP) ? \
          (((length) > ((adapter)->min_frame_size - VLAN_TAG_SIZE)) && \
           ((length) <= ((adapter)->max_frame_size + 1))) : \
          (((length) > (adapter)->min_frame_size) && \
           ((length) <= ((adapter)->max_frame_size + VLAN_TAG_SIZE + 1)))))

/* Structures, क्रमागतs, and macros क्रम the PHY */

/* Bit definitions क्रम the Management Data IO (MDIO) and Management Data
 * Clock (MDC) pins in the Device Control Register.
 */
#घोषणा E1000_CTRL_PHY_RESET_सूची  E1000_CTRL_SWDPIO0
#घोषणा E1000_CTRL_PHY_RESET      E1000_CTRL_SWDPIN0
#घोषणा E1000_CTRL_MDIO_सूची       E1000_CTRL_SWDPIO2
#घोषणा E1000_CTRL_MDIO           E1000_CTRL_SWDPIN2
#घोषणा E1000_CTRL_MDC_सूची        E1000_CTRL_SWDPIO3
#घोषणा E1000_CTRL_MDC            E1000_CTRL_SWDPIN3
#घोषणा E1000_CTRL_PHY_RESET_सूची4 E1000_CTRL_EXT_SDP4_सूची
#घोषणा E1000_CTRL_PHY_RESET4     E1000_CTRL_EXT_SDP4_DATA

/* PHY 1000 MII Register/Bit Definitions */
/* PHY Registers defined by IEEE */
#घोषणा PHY_CTRL         0x00	/* Control Register */
#घोषणा PHY_STATUS       0x01	/* Status Register */
#घोषणा PHY_ID1          0x02	/* Phy Id Reg (word 1) */
#घोषणा PHY_ID2          0x03	/* Phy Id Reg (word 2) */
#घोषणा PHY_AUTONEG_ADV  0x04	/* Autoneg Advertisement */
#घोषणा PHY_LP_ABILITY   0x05	/* Link Partner Ability (Base Page) */
#घोषणा PHY_AUTONEG_EXP  0x06	/* Autoneg Expansion Reg */
#घोषणा PHY_NEXT_PAGE_TX 0x07	/* Next Page TX */
#घोषणा PHY_LP_NEXT_PAGE 0x08	/* Link Partner Next Page */
#घोषणा PHY_1000T_CTRL   0x09	/* 1000Base-T Control Reg */
#घोषणा PHY_1000T_STATUS 0x0A	/* 1000Base-T Status Reg */
#घोषणा PHY_EXT_STATUS   0x0F	/* Extended Status Reg */

#घोषणा MAX_PHY_REG_ADDRESS        0x1F	/* 5 bit address bus (0-0x1F) */
#घोषणा MAX_PHY_MULTI_PAGE_REG     0xF	/* Registers equal on all pages */

/* M88E1000 Specअगरic Registers */
#घोषणा M88E1000_PHY_SPEC_CTRL     0x10	/* PHY Specअगरic Control Register */
#घोषणा M88E1000_PHY_SPEC_STATUS   0x11	/* PHY Specअगरic Status Register */
#घोषणा M88E1000_INT_ENABLE        0x12	/* Interrupt Enable Register */
#घोषणा M88E1000_INT_STATUS        0x13	/* Interrupt Status Register */
#घोषणा M88E1000_EXT_PHY_SPEC_CTRL 0x14	/* Extended PHY Specअगरic Control */
#घोषणा M88E1000_RX_ERR_CNTR       0x15	/* Receive Error Counter */

#घोषणा M88E1000_PHY_EXT_CTRL      0x1A	/* PHY extend control रेजिस्टर */
#घोषणा M88E1000_PHY_PAGE_SELECT   0x1D	/* Reg 29 क्रम page number setting */
#घोषणा M88E1000_PHY_GEN_CONTROL   0x1E	/* Its meaning depends on reg 29 */
#घोषणा M88E1000_PHY_VCO_REG_BIT8  0x100	/* Bits 8 & 11 are adjusted क्रम */
#घोषणा M88E1000_PHY_VCO_REG_BIT11 0x800	/* improved BER perक्रमmance */

#घोषणा IGP01E1000_IEEE_REGS_PAGE  0x0000
#घोषणा IGP01E1000_IEEE_RESTART_AUTONEG 0x3300
#घोषणा IGP01E1000_IEEE_FORCE_GIGA      0x0140

/* IGP01E1000 Specअगरic Registers */
#घोषणा IGP01E1000_PHY_PORT_CONFIG 0x10	/* PHY Specअगरic Port Config Register */
#घोषणा IGP01E1000_PHY_PORT_STATUS 0x11	/* PHY Specअगरic Status Register */
#घोषणा IGP01E1000_PHY_PORT_CTRL   0x12	/* PHY Specअगरic Control Register */
#घोषणा IGP01E1000_PHY_LINK_HEALTH 0x13	/* PHY Link Health Register */
#घोषणा IGP01E1000_GMII_FIFO       0x14	/* GMII FIFO Register */
#घोषणा IGP01E1000_PHY_CHANNEL_QUALITY 0x15	/* PHY Channel Quality Register */
#घोषणा IGP02E1000_PHY_POWER_MGMT      0x19
#घोषणा IGP01E1000_PHY_PAGE_SELECT     0x1F	/* PHY Page Select Core Register */

/* IGP01E1000 AGC Registers - stores the cable length values*/
#घोषणा IGP01E1000_PHY_AGC_A        0x1172
#घोषणा IGP01E1000_PHY_AGC_B        0x1272
#घोषणा IGP01E1000_PHY_AGC_C        0x1472
#घोषणा IGP01E1000_PHY_AGC_D        0x1872

/* IGP02E1000 AGC Registers क्रम cable length values */
#घोषणा IGP02E1000_PHY_AGC_A        0x11B1
#घोषणा IGP02E1000_PHY_AGC_B        0x12B1
#घोषणा IGP02E1000_PHY_AGC_C        0x14B1
#घोषणा IGP02E1000_PHY_AGC_D        0x18B1

/* IGP01E1000 DSP Reset Register */
#घोषणा IGP01E1000_PHY_DSP_RESET   0x1F33
#घोषणा IGP01E1000_PHY_DSP_SET     0x1F71
#घोषणा IGP01E1000_PHY_DSP_FFE     0x1F35

#घोषणा IGP01E1000_PHY_CHANNEL_NUM    4
#घोषणा IGP02E1000_PHY_CHANNEL_NUM    4

#घोषणा IGP01E1000_PHY_AGC_PARAM_A    0x1171
#घोषणा IGP01E1000_PHY_AGC_PARAM_B    0x1271
#घोषणा IGP01E1000_PHY_AGC_PARAM_C    0x1471
#घोषणा IGP01E1000_PHY_AGC_PARAM_D    0x1871

#घोषणा IGP01E1000_PHY_EDAC_MU_INDEX        0xC000
#घोषणा IGP01E1000_PHY_EDAC_SIGN_EXT_9_BITS 0x8000

#घोषणा IGP01E1000_PHY_ANALOG_TX_STATE      0x2890
#घोषणा IGP01E1000_PHY_ANALOG_CLASS_A       0x2000
#घोषणा IGP01E1000_PHY_FORCE_ANALOG_ENABLE  0x0004
#घोषणा IGP01E1000_PHY_DSP_FFE_CM_CP        0x0069

#घोषणा IGP01E1000_PHY_DSP_FFE_DEFAULT      0x002A
/* IGP01E1000 PCS Initialization रेजिस्टर - stores the polarity status when
 * speed = 1000 Mbps. */
#घोषणा IGP01E1000_PHY_PCS_INIT_REG  0x00B4
#घोषणा IGP01E1000_PHY_PCS_CTRL_REG  0x00B5

#घोषणा IGP01E1000_ANALOG_REGS_PAGE  0x20C0

/* PHY Control Register */
#घोषणा MII_CR_SPEED_SELECT_MSB 0x0040	/* bits 6,13: 10=1000, 01=100, 00=10 */
#घोषणा MII_CR_COLL_TEST_ENABLE 0x0080	/* Collision test enable */
#घोषणा MII_CR_FULL_DUPLEX      0x0100	/* FDX =1, half duplex =0 */
#घोषणा MII_CR_RESTART_AUTO_NEG 0x0200	/* Restart स्वतः negotiation */
#घोषणा MII_CR_ISOLATE          0x0400	/* Isolate PHY from MII */
#घोषणा MII_CR_POWER_DOWN       0x0800	/* Power करोwn */
#घोषणा MII_CR_AUTO_NEG_EN      0x1000	/* Auto Neg Enable */
#घोषणा MII_CR_SPEED_SELECT_LSB 0x2000	/* bits 6,13: 10=1000, 01=100, 00=10 */
#घोषणा MII_CR_LOOPBACK         0x4000	/* 0 = normal, 1 = loopback */
#घोषणा MII_CR_RESET            0x8000	/* 0 = normal, 1 = PHY reset */

/* PHY Status Register */
#घोषणा MII_SR_EXTENDED_CAPS     0x0001	/* Extended रेजिस्टर capabilities */
#घोषणा MII_SR_JABBER_DETECT     0x0002	/* Jabber Detected */
#घोषणा MII_SR_LINK_STATUS       0x0004	/* Link Status 1 = link */
#घोषणा MII_SR_AUTONEG_CAPS      0x0008	/* Auto Neg Capable */
#घोषणा MII_SR_REMOTE_FAULT      0x0010	/* Remote Fault Detect */
#घोषणा MII_SR_AUTONEG_COMPLETE  0x0020	/* Auto Neg Complete */
#घोषणा MII_SR_PREAMBLE_SUPPRESS 0x0040	/* Preamble may be suppressed */
#घोषणा MII_SR_EXTENDED_STATUS   0x0100	/* Ext. status info in Reg 0x0F */
#घोषणा MII_SR_100T2_HD_CAPS     0x0200	/* 100T2 Half Duplex Capable */
#घोषणा MII_SR_100T2_FD_CAPS     0x0400	/* 100T2 Full Duplex Capable */
#घोषणा MII_SR_10T_HD_CAPS       0x0800	/* 10T   Half Duplex Capable */
#घोषणा MII_SR_10T_FD_CAPS       0x1000	/* 10T   Full Duplex Capable */
#घोषणा MII_SR_100X_HD_CAPS      0x2000	/* 100X  Half Duplex Capable */
#घोषणा MII_SR_100X_FD_CAPS      0x4000	/* 100X  Full Duplex Capable */
#घोषणा MII_SR_100T4_CAPS        0x8000	/* 100T4 Capable */

/* Autoneg Advertisement Register */
#घोषणा NWAY_AR_SELECTOR_FIELD 0x0001	/* indicates IEEE 802.3 CSMA/CD */
#घोषणा NWAY_AR_10T_HD_CAPS    0x0020	/* 10T   Half Duplex Capable */
#घोषणा NWAY_AR_10T_FD_CAPS    0x0040	/* 10T   Full Duplex Capable */
#घोषणा NWAY_AR_100TX_HD_CAPS  0x0080	/* 100TX Half Duplex Capable */
#घोषणा NWAY_AR_100TX_FD_CAPS  0x0100	/* 100TX Full Duplex Capable */
#घोषणा NWAY_AR_100T4_CAPS     0x0200	/* 100T4 Capable */
#घोषणा NWAY_AR_PAUSE          0x0400	/* Pause operation desired */
#घोषणा NWAY_AR_ASM_सूची        0x0800	/* Asymmetric Pause Direction bit */
#घोषणा NWAY_AR_REMOTE_FAULT   0x2000	/* Remote Fault detected */
#घोषणा NWAY_AR_NEXT_PAGE      0x8000	/* Next Page ability supported */

/* Link Partner Ability Register (Base Page) */
#घोषणा NWAY_LPAR_SELECTOR_FIELD 0x0000	/* LP protocol selector field */
#घोषणा NWAY_LPAR_10T_HD_CAPS    0x0020	/* LP is 10T   Half Duplex Capable */
#घोषणा NWAY_LPAR_10T_FD_CAPS    0x0040	/* LP is 10T   Full Duplex Capable */
#घोषणा NWAY_LPAR_100TX_HD_CAPS  0x0080	/* LP is 100TX Half Duplex Capable */
#घोषणा NWAY_LPAR_100TX_FD_CAPS  0x0100	/* LP is 100TX Full Duplex Capable */
#घोषणा NWAY_LPAR_100T4_CAPS     0x0200	/* LP is 100T4 Capable */
#घोषणा NWAY_LPAR_PAUSE          0x0400	/* LP Pause operation desired */
#घोषणा NWAY_LPAR_ASM_सूची        0x0800	/* LP Asymmetric Pause Direction bit */
#घोषणा NWAY_LPAR_REMOTE_FAULT   0x2000	/* LP has detected Remote Fault */
#घोषणा NWAY_LPAR_ACKNOWLEDGE    0x4000	/* LP has rx'd link code word */
#घोषणा NWAY_LPAR_NEXT_PAGE      0x8000	/* Next Page ability supported */

/* Autoneg Expansion Register */
#घोषणा NWAY_ER_LP_NWAY_CAPS      0x0001	/* LP has Auto Neg Capability */
#घोषणा NWAY_ER_PAGE_RXD          0x0002	/* LP is 10T   Half Duplex Capable */
#घोषणा NWAY_ER_NEXT_PAGE_CAPS    0x0004	/* LP is 10T   Full Duplex Capable */
#घोषणा NWAY_ER_LP_NEXT_PAGE_CAPS 0x0008	/* LP is 100TX Half Duplex Capable */
#घोषणा NWAY_ER_PAR_DETECT_FAULT  0x0010	/* LP is 100TX Full Duplex Capable */

/* Next Page TX Register */
#घोषणा NPTX_MSG_CODE_FIELD 0x0001	/* NP msg code or unक्रमmatted data */
#घोषणा NPTX_TOGGLE         0x0800	/* Toggles between exchanges
					 * of dअगरferent NP
					 */
#घोषणा NPTX_ACKNOWLDGE2    0x1000	/* 1 = will comply with msg
					 * 0 = cannot comply with msg
					 */
#घोषणा NPTX_MSG_PAGE       0x2000	/* क्रमmatted(1)/unक्रमmatted(0) pg */
#घोषणा NPTX_NEXT_PAGE      0x8000	/* 1 = addition NP will follow
					 * 0 = sending last NP
					 */

/* Link Partner Next Page Register */
#घोषणा LP_RNPR_MSG_CODE_FIELD 0x0001	/* NP msg code or unक्रमmatted data */
#घोषणा LP_RNPR_TOGGLE         0x0800	/* Toggles between exchanges
					 * of dअगरferent NP
					 */
#घोषणा LP_RNPR_ACKNOWLDGE2    0x1000	/* 1 = will comply with msg
					 * 0 = cannot comply with msg
					 */
#घोषणा LP_RNPR_MSG_PAGE       0x2000	/* क्रमmatted(1)/unक्रमmatted(0) pg */
#घोषणा LP_RNPR_ACKNOWLDGE     0x4000	/* 1 = ACK / 0 = NO ACK */
#घोषणा LP_RNPR_NEXT_PAGE      0x8000	/* 1 = addition NP will follow
					 * 0 = sending last NP
					 */

/* 1000BASE-T Control Register */
#घोषणा CR_1000T_ASYM_PAUSE      0x0080	/* Advertise asymmetric छोड़ो bit */
#घोषणा CR_1000T_HD_CAPS         0x0100	/* Advertise 1000T HD capability */
#घोषणा CR_1000T_FD_CAPS         0x0200	/* Advertise 1000T FD capability  */
#घोषणा CR_1000T_REPEATER_DTE    0x0400	/* 1=Repeater/चयन device port */
					/* 0=DTE device */
#घोषणा CR_1000T_MS_VALUE        0x0800	/* 1=Configure PHY as Master */
					/* 0=Configure PHY as Slave */
#घोषणा CR_1000T_MS_ENABLE       0x1000	/* 1=Master/Slave manual config value */
					/* 0=Automatic Master/Slave config */
#घोषणा CR_1000T_TEST_MODE_NORMAL 0x0000	/* Normal Operation */
#घोषणा CR_1000T_TEST_MODE_1     0x2000	/* Transmit Waveक्रमm test */
#घोषणा CR_1000T_TEST_MODE_2     0x4000	/* Master Transmit Jitter test */
#घोषणा CR_1000T_TEST_MODE_3     0x6000	/* Slave Transmit Jitter test */
#घोषणा CR_1000T_TEST_MODE_4     0x8000	/* Transmitter Distortion test */

/* 1000BASE-T Status Register */
#घोषणा SR_1000T_IDLE_ERROR_CNT   0x00FF	/* Num idle errors since last पढ़ो */
#घोषणा SR_1000T_ASYM_PAUSE_सूची   0x0100	/* LP asymmetric छोड़ो direction bit */
#घोषणा SR_1000T_LP_HD_CAPS       0x0400	/* LP is 1000T HD capable */
#घोषणा SR_1000T_LP_FD_CAPS       0x0800	/* LP is 1000T FD capable */
#घोषणा SR_1000T_REMOTE_RX_STATUS 0x1000	/* Remote receiver OK */
#घोषणा SR_1000T_LOCAL_RX_STATUS  0x2000	/* Local receiver OK */
#घोषणा SR_1000T_MS_CONFIG_RES    0x4000	/* 1=Local TX is Master, 0=Slave */
#घोषणा SR_1000T_MS_CONFIG_FAULT  0x8000	/* Master/Slave config fault */
#घोषणा SR_1000T_REMOTE_RX_STATUS_SHIFT          12
#घोषणा SR_1000T_LOCAL_RX_STATUS_SHIFT           13
#घोषणा SR_1000T_PHY_EXCESSIVE_IDLE_ERR_COUNT    5
#घोषणा FFE_IDLE_ERR_COUNT_TIMEOUT_20            20
#घोषणा FFE_IDLE_ERR_COUNT_TIMEOUT_100           100

/* Extended Status Register */
#घोषणा IEEE_ESR_1000T_HD_CAPS 0x1000	/* 1000T HD capable */
#घोषणा IEEE_ESR_1000T_FD_CAPS 0x2000	/* 1000T FD capable */
#घोषणा IEEE_ESR_1000X_HD_CAPS 0x4000	/* 1000X HD capable */
#घोषणा IEEE_ESR_1000X_FD_CAPS 0x8000	/* 1000X FD capable */

#घोषणा PHY_TX_POLARITY_MASK   0x0100	/* रेजिस्टर 10h bit 8 (polarity bit) */
#घोषणा PHY_TX_NORMAL_POLARITY 0	/* रेजिस्टर 10h bit 8 (normal polarity) */

#घोषणा AUTO_POLARITY_DISABLE  0x0010	/* रेजिस्टर 11h bit 4 */
				      /* (0=enable, 1=disable) */

/* M88E1000 PHY Specअगरic Control Register */
#घोषणा M88E1000_PSCR_JABBER_DISABLE    0x0001	/* 1=Jabber Function disabled */
#घोषणा M88E1000_PSCR_POLARITY_REVERSAL 0x0002	/* 1=Polarity Reversal enabled */
#घोषणा M88E1000_PSCR_SQE_TEST          0x0004	/* 1=SQE Test enabled */
#घोषणा M88E1000_PSCR_CLK125_DISABLE    0x0010	/* 1=CLK125 low,
						 * 0=CLK125 toggling
						 */
#घोषणा M88E1000_PSCR_MDI_MANUAL_MODE  0x0000	/* MDI Crossover Mode bits 6:5 */
					       /* Manual MDI configuration */
#घोषणा M88E1000_PSCR_MDIX_MANUAL_MODE 0x0020	/* Manual MDIX configuration */
#घोषणा M88E1000_PSCR_AUTO_X_1000T     0x0040	/* 1000BASE-T: Auto crossover,
						 *  100BASE-TX/10BASE-T:
						 *  MDI Mode
						 */
#घोषणा M88E1000_PSCR_AUTO_X_MODE      0x0060	/* Auto crossover enabled
						 * all speeds.
						 */
#घोषणा M88E1000_PSCR_10BT_EXT_DIST_ENABLE 0x0080
					/* 1=Enable Extended 10BASE-T distance
					 * (Lower 10BASE-T RX Threshold)
					 * 0=Normal 10BASE-T RX Threshold */
#घोषणा M88E1000_PSCR_MII_5BIT_ENABLE      0x0100
					/* 1=5-Bit पूर्णांकerface in 100BASE-TX
					 * 0=MII पूर्णांकerface in 100BASE-TX */
#घोषणा M88E1000_PSCR_SCRAMBLER_DISABLE    0x0200	/* 1=Scrambler disable */
#घोषणा M88E1000_PSCR_FORCE_LINK_GOOD      0x0400	/* 1=Force link good */
#घोषणा M88E1000_PSCR_ASSERT_CRS_ON_TX     0x0800	/* 1=Assert CRS on Transmit */

#घोषणा M88E1000_PSCR_POLARITY_REVERSAL_SHIFT    1
#घोषणा M88E1000_PSCR_AUTO_X_MODE_SHIFT          5
#घोषणा M88E1000_PSCR_10BT_EXT_DIST_ENABLE_SHIFT 7

/* M88E1000 PHY Specअगरic Status Register */
#घोषणा M88E1000_PSSR_JABBER             0x0001	/* 1=Jabber */
#घोषणा M88E1000_PSSR_REV_POLARITY       0x0002	/* 1=Polarity reversed */
#घोषणा M88E1000_PSSR_DOWNSHIFT          0x0020	/* 1=Downshअगरted */
#घोषणा M88E1000_PSSR_MDIX               0x0040	/* 1=MDIX; 0=MDI */
#घोषणा M88E1000_PSSR_CABLE_LENGTH       0x0380	/* 0=<50M;1=50-80M;2=80-110M;
						 * 3=110-140M;4=>140M */
#घोषणा M88E1000_PSSR_LINK               0x0400	/* 1=Link up, 0=Link करोwn */
#घोषणा M88E1000_PSSR_SPD_DPLX_RESOLVED  0x0800	/* 1=Speed & Duplex resolved */
#घोषणा M88E1000_PSSR_PAGE_RCVD          0x1000	/* 1=Page received */
#घोषणा M88E1000_PSSR_DPLX               0x2000	/* 1=Duplex 0=Half Duplex */
#घोषणा M88E1000_PSSR_SPEED              0xC000	/* Speed, bits 14:15 */
#घोषणा M88E1000_PSSR_10MBS              0x0000	/* 00=10Mbs */
#घोषणा M88E1000_PSSR_100MBS             0x4000	/* 01=100Mbs */
#घोषणा M88E1000_PSSR_1000MBS            0x8000	/* 10=1000Mbs */

#घोषणा M88E1000_PSSR_REV_POLARITY_SHIFT 1
#घोषणा M88E1000_PSSR_DOWNSHIFT_SHIFT    5
#घोषणा M88E1000_PSSR_MDIX_SHIFT         6
#घोषणा M88E1000_PSSR_CABLE_LENGTH_SHIFT 7

/* M88E1000 Extended PHY Specअगरic Control Register */
#घोषणा M88E1000_EPSCR_FIBER_LOOPBACK 0x4000	/* 1=Fiber loopback */
#घोषणा M88E1000_EPSCR_DOWN_NO_IDLE   0x8000	/* 1=Lost lock detect enabled.
						 * Will निश्चित lost lock and bring
						 * link करोwn अगर idle not seen
						 * within 1ms in 1000BASE-T
						 */
/* Number of बार we will attempt to स्वतःnegotiate beक्रमe करोwnshअगरting अगर we
 * are the master */
#घोषणा M88E1000_EPSCR_MASTER_DOWNSHIFT_MASK 0x0C00
#घोषणा M88E1000_EPSCR_MASTER_DOWNSHIFT_1X   0x0000
#घोषणा M88E1000_EPSCR_MASTER_DOWNSHIFT_2X   0x0400
#घोषणा M88E1000_EPSCR_MASTER_DOWNSHIFT_3X   0x0800
#घोषणा M88E1000_EPSCR_MASTER_DOWNSHIFT_4X   0x0C00
/* Number of बार we will attempt to स्वतःnegotiate beक्रमe करोwnshअगरting अगर we
 * are the slave */
#घोषणा M88E1000_EPSCR_SLAVE_DOWNSHIFT_MASK  0x0300
#घोषणा M88E1000_EPSCR_SLAVE_DOWNSHIFT_DIS   0x0000
#घोषणा M88E1000_EPSCR_SLAVE_DOWNSHIFT_1X    0x0100
#घोषणा M88E1000_EPSCR_SLAVE_DOWNSHIFT_2X    0x0200
#घोषणा M88E1000_EPSCR_SLAVE_DOWNSHIFT_3X    0x0300
#घोषणा M88E1000_EPSCR_TX_CLK_2_5     0x0060	/* 2.5 MHz TX_CLK */
#घोषणा M88E1000_EPSCR_TX_CLK_25      0x0070	/* 25  MHz TX_CLK */
#घोषणा M88E1000_EPSCR_TX_CLK_0       0x0000	/* NO  TX_CLK */

/* M88EC018 Rev 2 specअगरic DownShअगरt settings */
#घोषणा M88EC018_EPSCR_DOWNSHIFT_COUNTER_MASK  0x0E00
#घोषणा M88EC018_EPSCR_DOWNSHIFT_COUNTER_1X    0x0000
#घोषणा M88EC018_EPSCR_DOWNSHIFT_COUNTER_2X    0x0200
#घोषणा M88EC018_EPSCR_DOWNSHIFT_COUNTER_3X    0x0400
#घोषणा M88EC018_EPSCR_DOWNSHIFT_COUNTER_4X    0x0600
#घोषणा M88EC018_EPSCR_DOWNSHIFT_COUNTER_5X    0x0800
#घोषणा M88EC018_EPSCR_DOWNSHIFT_COUNTER_6X    0x0A00
#घोषणा M88EC018_EPSCR_DOWNSHIFT_COUNTER_7X    0x0C00
#घोषणा M88EC018_EPSCR_DOWNSHIFT_COUNTER_8X    0x0E00

/* IGP01E1000 Specअगरic Port Config Register - R/W */
#घोषणा IGP01E1000_PSCFR_AUTO_MDIX_PAR_DETECT  0x0010
#घोषणा IGP01E1000_PSCFR_PRE_EN                0x0020
#घोषणा IGP01E1000_PSCFR_SMART_SPEED           0x0080
#घोषणा IGP01E1000_PSCFR_DISABLE_TPLOOPBACK    0x0100
#घोषणा IGP01E1000_PSCFR_DISABLE_JABBER        0x0400
#घोषणा IGP01E1000_PSCFR_DISABLE_TRANSMIT      0x2000

/* IGP01E1000 Specअगरic Port Status Register - R/O */
#घोषणा IGP01E1000_PSSR_AUTONEG_FAILED         0x0001	/* RO LH SC */
#घोषणा IGP01E1000_PSSR_POLARITY_REVERSED      0x0002
#घोषणा IGP01E1000_PSSR_CABLE_LENGTH           0x007C
#घोषणा IGP01E1000_PSSR_FULL_DUPLEX            0x0200
#घोषणा IGP01E1000_PSSR_LINK_UP                0x0400
#घोषणा IGP01E1000_PSSR_MDIX                   0x0800
#घोषणा IGP01E1000_PSSR_SPEED_MASK             0xC000	/* speed bits mask */
#घोषणा IGP01E1000_PSSR_SPEED_10MBPS           0x4000
#घोषणा IGP01E1000_PSSR_SPEED_100MBPS          0x8000
#घोषणा IGP01E1000_PSSR_SPEED_1000MBPS         0xC000
#घोषणा IGP01E1000_PSSR_CABLE_LENGTH_SHIFT     0x0002	/* shअगरt right 2 */
#घोषणा IGP01E1000_PSSR_MDIX_SHIFT             0x000B	/* shअगरt right 11 */

/* IGP01E1000 Specअगरic Port Control Register - R/W */
#घोषणा IGP01E1000_PSCR_TP_LOOPBACK            0x0010
#घोषणा IGP01E1000_PSCR_CORRECT_NC_SCMBLR      0x0200
#घोषणा IGP01E1000_PSCR_TEN_CRS_SELECT         0x0400
#घोषणा IGP01E1000_PSCR_FLIP_CHIP              0x0800
#घोषणा IGP01E1000_PSCR_AUTO_MDIX              0x1000
#घोषणा IGP01E1000_PSCR_FORCE_MDI_MDIX         0x2000	/* 0-MDI, 1-MDIX */

/* IGP01E1000 Specअगरic Port Link Health Register */
#घोषणा IGP01E1000_PLHR_SS_DOWNGRADE           0x8000
#घोषणा IGP01E1000_PLHR_GIG_SCRAMBLER_ERROR    0x4000
#घोषणा IGP01E1000_PLHR_MASTER_FAULT           0x2000
#घोषणा IGP01E1000_PLHR_MASTER_RESOLUTION      0x1000
#घोषणा IGP01E1000_PLHR_GIG_REM_RCVR_NOK       0x0800	/* LH */
#घोषणा IGP01E1000_PLHR_IDLE_ERROR_CNT_OFLOW   0x0400	/* LH */
#घोषणा IGP01E1000_PLHR_DATA_ERR_1             0x0200	/* LH */
#घोषणा IGP01E1000_PLHR_DATA_ERR_0             0x0100
#घोषणा IGP01E1000_PLHR_AUTONEG_FAULT          0x0040
#घोषणा IGP01E1000_PLHR_AUTONEG_ACTIVE         0x0010
#घोषणा IGP01E1000_PLHR_VALID_CHANNEL_D        0x0008
#घोषणा IGP01E1000_PLHR_VALID_CHANNEL_C        0x0004
#घोषणा IGP01E1000_PLHR_VALID_CHANNEL_B        0x0002
#घोषणा IGP01E1000_PLHR_VALID_CHANNEL_A        0x0001

/* IGP01E1000 Channel Quality Register */
#घोषणा IGP01E1000_MSE_CHANNEL_D        0x000F
#घोषणा IGP01E1000_MSE_CHANNEL_C        0x00F0
#घोषणा IGP01E1000_MSE_CHANNEL_B        0x0F00
#घोषणा IGP01E1000_MSE_CHANNEL_A        0xF000

#घोषणा IGP02E1000_PM_SPD                         0x0001	/* Smart Power Down */
#घोषणा IGP02E1000_PM_D3_LPLU                     0x0004	/* Enable LPLU in non-D0a modes */
#घोषणा IGP02E1000_PM_D0_LPLU                     0x0002	/* Enable LPLU in D0a mode */

/* IGP01E1000 DSP reset macros */
#घोषणा DSP_RESET_ENABLE     0x0
#घोषणा DSP_RESET_DISABLE    0x2
#घोषणा E1000_MAX_DSP_RESETS 10

/* IGP01E1000 & IGP02E1000 AGC Registers */

#घोषणा IGP01E1000_AGC_LENGTH_SHIFT 7	/* Coarse - 13:11, Fine - 10:7 */
#घोषणा IGP02E1000_AGC_LENGTH_SHIFT 9	/* Coarse - 15:13, Fine - 12:9 */

/* IGP02E1000 AGC Register Length 9-bit mask */
#घोषणा IGP02E1000_AGC_LENGTH_MASK  0x7F

/* 7 bits (3 Coarse + 4 Fine) --> 128 optional values */
#घोषणा IGP01E1000_AGC_LENGTH_TABLE_SIZE 128
#घोषणा IGP02E1000_AGC_LENGTH_TABLE_SIZE 113

/* The precision error of the cable length is +/- 10 meters */
#घोषणा IGP01E1000_AGC_RANGE    10
#घोषणा IGP02E1000_AGC_RANGE    15

/* IGP01E1000 PCS Initialization रेजिस्टर */
/* bits 3:6 in the PCS रेजिस्टरs stores the channels polarity */
#घोषणा IGP01E1000_PHY_POLARITY_MASK    0x0078

/* IGP01E1000 GMII FIFO Register */
#घोषणा IGP01E1000_GMII_FLEX_SPD               0x10	/* Enable flexible speed
							 * on Link-Up */
#घोषणा IGP01E1000_GMII_SPD                    0x20	/* Enable SPD */

/* IGP01E1000 Analog Register */
#घोषणा IGP01E1000_ANALOG_SPARE_FUSE_STATUS       0x20D1
#घोषणा IGP01E1000_ANALOG_FUSE_STATUS             0x20D0
#घोषणा IGP01E1000_ANALOG_FUSE_CONTROL            0x20DC
#घोषणा IGP01E1000_ANALOG_FUSE_BYPASS             0x20DE

#घोषणा IGP01E1000_ANALOG_FUSE_POLY_MASK            0xF000
#घोषणा IGP01E1000_ANALOG_FUSE_FINE_MASK            0x0F80
#घोषणा IGP01E1000_ANALOG_FUSE_COARSE_MASK          0x0070
#घोषणा IGP01E1000_ANALOG_SPARE_FUSE_ENABLED        0x0100
#घोषणा IGP01E1000_ANALOG_FUSE_ENABLE_SW_CONTROL    0x0002

#घोषणा IGP01E1000_ANALOG_FUSE_COARSE_THRESH        0x0040
#घोषणा IGP01E1000_ANALOG_FUSE_COARSE_10            0x0010
#घोषणा IGP01E1000_ANALOG_FUSE_FINE_1               0x0080
#घोषणा IGP01E1000_ANALOG_FUSE_FINE_10              0x0500

/* Bit definitions क्रम valid PHY IDs. */
/* I = Integrated
 * E = External
 */
#घोषणा M88_VENDOR         0x0141
#घोषणा M88E1000_E_PHY_ID  0x01410C50
#घोषणा M88E1000_I_PHY_ID  0x01410C30
#घोषणा M88E1011_I_PHY_ID  0x01410C20
#घोषणा IGP01E1000_I_PHY_ID  0x02A80380
#घोषणा M88E1000_12_PHY_ID M88E1000_E_PHY_ID
#घोषणा M88E1000_14_PHY_ID M88E1000_E_PHY_ID
#घोषणा M88E1011_I_REV_4   0x04
#घोषणा M88E1111_I_PHY_ID  0x01410CC0
#घोषणा M88E1118_E_PHY_ID  0x01410E40
#घोषणा L1LXT971A_PHY_ID   0x001378E0

#घोषणा RTL8211B_PHY_ID    0x001CC910
#घोषणा RTL8201N_PHY_ID    0x8200
#घोषणा RTL_PHY_CTRL_FD    0x0100 /* Full duplex.0=half; 1=full */
#घोषणा RTL_PHY_CTRL_SPD_100    0x200000 /* Force 100Mb */

/* Bits...
 * 15-5: page
 * 4-0: रेजिस्टर offset
 */
#घोषणा PHY_PAGE_SHIFT        5
#घोषणा PHY_REG(page, reg)    \
        (((page) << PHY_PAGE_SHIFT) | ((reg) & MAX_PHY_REG_ADDRESS))

#घोषणा IGP3_PHY_PORT_CTRL           \
        PHY_REG(769, 17)	/* Port General Configuration */
#घोषणा IGP3_PHY_RATE_ADAPT_CTRL \
        PHY_REG(769, 25)	/* Rate Adapter Control Register */

#घोषणा IGP3_KMRN_FIFO_CTRL_STATS \
        PHY_REG(770, 16)	/* KMRN FIFO's control/status रेजिस्टर */
#घोषणा IGP3_KMRN_POWER_MNG_CTRL \
        PHY_REG(770, 17)	/* KMRN Power Management Control Register */
#घोषणा IGP3_KMRN_INBAND_CTRL \
        PHY_REG(770, 18)	/* KMRN Inband Control Register */
#घोषणा IGP3_KMRN_DIAG \
        PHY_REG(770, 19)	/* KMRN Diagnostic रेजिस्टर */
#घोषणा IGP3_KMRN_DIAG_PCS_LOCK_LOSS 0x0002	/* RX PCS is not synced */
#घोषणा IGP3_KMRN_ACK_TIMEOUT \
        PHY_REG(770, 20)	/* KMRN Acknowledge Timeouts रेजिस्टर */

#घोषणा IGP3_VR_CTRL \
        PHY_REG(776, 18)	/* Voltage regulator control रेजिस्टर */
#घोषणा IGP3_VR_CTRL_MODE_SHUT       0x0200	/* Enter घातerकरोwn, shutकरोwn VRs */
#घोषणा IGP3_VR_CTRL_MODE_MASK       0x0300	/* Shutकरोwn VR Mask */

#घोषणा IGP3_CAPABILITY \
        PHY_REG(776, 19)	/* IGP3 Capability Register */

/* Capabilities क्रम SKU Control  */
#घोषणा IGP3_CAP_INITIATE_TEAM       0x0001	/* Able to initiate a team */
#घोषणा IGP3_CAP_WFM                 0x0002	/* Support WoL and PXE */
#घोषणा IGP3_CAP_ASF                 0x0004	/* Support ASF */
#घोषणा IGP3_CAP_LPLU                0x0008	/* Support Low Power Link Up */
#घोषणा IGP3_CAP_DC_AUTO_SPEED       0x0010	/* Support AC/DC Auto Link Speed */
#घोषणा IGP3_CAP_SPD                 0x0020	/* Support Smart Power Down */
#घोषणा IGP3_CAP_MULT_QUEUE          0x0040	/* Support 2 tx & 2 rx queues */
#घोषणा IGP3_CAP_RSS                 0x0080	/* Support RSS */
#घोषणा IGP3_CAP_8021PQ              0x0100	/* Support 802.1Q & 802.1p */
#घोषणा IGP3_CAP_AMT_CB              0x0200	/* Support active manageability and circuit अवरोधer */

#घोषणा IGP3_PPC_JORDAN_EN           0x0001
#घोषणा IGP3_PPC_JORDAN_GIGA_SPEED   0x0002

#घोषणा IGP3_KMRN_PMC_EE_IDLE_LINK_DIS         0x0001
#घोषणा IGP3_KMRN_PMC_K0S_ENTRY_LATENCY_MASK   0x001E
#घोषणा IGP3_KMRN_PMC_K0S_MODE1_EN_GIGA        0x0020
#घोषणा IGP3_KMRN_PMC_K0S_MODE1_EN_100         0x0040

#घोषणा IGP3E1000_PHY_MISC_CTRL                0x1B	/* Misc. Ctrl रेजिस्टर */
#घोषणा IGP3_PHY_MISC_DUPLEX_MANUAL_SET        0x1000	/* Duplex Manual Set */

#घोषणा IGP3_KMRN_EXT_CTRL  PHY_REG(770, 18)
#घोषणा IGP3_KMRN_EC_DIS_INBAND    0x0080

#घोषणा IGP03E1000_E_PHY_ID  0x02A80390
#घोषणा IFE_E_PHY_ID         0x02A80330	/* 10/100 PHY */
#घोषणा IFE_PLUS_E_PHY_ID    0x02A80320
#घोषणा IFE_C_E_PHY_ID       0x02A80310

#घोषणा IFE_PHY_EXTENDED_STATUS_CONTROL   0x10	/* 100BaseTx Extended Status, Control and Address */
#घोषणा IFE_PHY_SPECIAL_CONTROL           0x11	/* 100BaseTx PHY special control रेजिस्टर */
#घोषणा IFE_PHY_RCV_FALSE_CARRIER         0x13	/* 100BaseTx Receive False Carrier Counter */
#घोषणा IFE_PHY_RCV_DISCONNECT            0x14	/* 100BaseTx Receive Disconnect Counter */
#घोषणा IFE_PHY_RCV_ERROT_FRAME           0x15	/* 100BaseTx Receive Error Frame Counter */
#घोषणा IFE_PHY_RCV_SYMBOL_ERR            0x16	/* Receive Symbol Error Counter */
#घोषणा IFE_PHY_PREM_खातापूर्ण_ERR              0x17	/* 100BaseTx Receive Premature End Of Frame Error Counter */
#घोषणा IFE_PHY_RCV_खातापूर्ण_ERR               0x18	/* 10BaseT Receive End Of Frame Error Counter */
#घोषणा IFE_PHY_TX_JABBER_DETECT          0x19	/* 10BaseT Transmit Jabber Detect Counter */
#घोषणा IFE_PHY_EQUALIZER                 0x1A	/* PHY Equalizer Control and Status */
#घोषणा IFE_PHY_SPECIAL_CONTROL_LED       0x1B	/* PHY special control and LED configuration */
#घोषणा IFE_PHY_MDIX_CONTROL              0x1C	/* MDI/MDI-X Control रेजिस्टर */
#घोषणा IFE_PHY_HWI_CONTROL               0x1D	/* Hardware Integrity Control (HWI) */

#घोषणा IFE_PESC_REDUCED_POWER_DOWN_DISABLE  0x2000	/* Default 1 = Disable स्वतः reduced घातer करोwn */
#घोषणा IFE_PESC_100BTX_POWER_DOWN           0x0400	/* Indicates the घातer state of 100BASE-TX */
#घोषणा IFE_PESC_10BTX_POWER_DOWN            0x0200	/* Indicates the घातer state of 10BASE-T */
#घोषणा IFE_PESC_POLARITY_REVERSED           0x0100	/* Indicates 10BASE-T polarity */
#घोषणा IFE_PESC_PHY_ADDR_MASK               0x007C	/* Bit 6:2 क्रम sampled PHY address */
#घोषणा IFE_PESC_SPEED                       0x0002	/* Auto-negotiation speed result 1=100Mbs, 0=10Mbs */
#घोषणा IFE_PESC_DUPLEX                      0x0001	/* Auto-negotiation duplex result 1=Full, 0=Half */
#घोषणा IFE_PESC_POLARITY_REVERSED_SHIFT     8

#घोषणा IFE_PSC_DISABLE_DYNAMIC_POWER_DOWN   0x0100	/* 1 = Dynamic Power Down disabled */
#घोषणा IFE_PSC_FORCE_POLARITY               0x0020	/* 1=Reversed Polarity, 0=Normal */
#घोषणा IFE_PSC_AUTO_POLARITY_DISABLE        0x0010	/* 1=Auto Polarity Disabled, 0=Enabled */
#घोषणा IFE_PSC_JABBER_FUNC_DISABLE          0x0001	/* 1=Jabber Disabled, 0=Normal Jabber Operation */
#घोषणा IFE_PSC_FORCE_POLARITY_SHIFT         5
#घोषणा IFE_PSC_AUTO_POLARITY_DISABLE_SHIFT  4

#घोषणा IFE_PMC_AUTO_MDIX                    0x0080	/* 1=enable MDI/MDI-X feature, शेष 0=disabled */
#घोषणा IFE_PMC_FORCE_MDIX                   0x0040	/* 1=क्रमce MDIX-X, 0=क्रमce MDI */
#घोषणा IFE_PMC_MDIX_STATUS                  0x0020	/* 1=MDI-X, 0=MDI */
#घोषणा IFE_PMC_AUTO_MDIX_COMPLETE           0x0010	/* Resolution algorithm is completed */
#घोषणा IFE_PMC_MDIX_MODE_SHIFT              6
#घोषणा IFE_PHC_MDIX_RESET_ALL_MASK          0x0000	/* Disable स्वतः MDI-X */

#घोषणा IFE_PHC_HWI_ENABLE                   0x8000	/* Enable the HWI feature */
#घोषणा IFE_PHC_ABILITY_CHECK                0x4000	/* 1= Test Passed, 0=failed */
#घोषणा IFE_PHC_TEST_EXEC                    0x2000	/* PHY launch test pulses on the wire */
#घोषणा IFE_PHC_HIGHZ                        0x0200	/* 1 = Open Circuit */
#घोषणा IFE_PHC_LOWZ                         0x0400	/* 1 = Short Circuit */
#घोषणा IFE_PHC_LOW_HIGH_Z_MASK              0x0600	/* Mask क्रम indication type of problem on the line */
#घोषणा IFE_PHC_DISTANCE_MASK                0x01FF	/* Mask क्रम distance to the cable problem, in 80cm granularity */
#घोषणा IFE_PHC_RESET_ALL_MASK               0x0000	/* Disable HWI */
#घोषणा IFE_PSCL_PROBE_MODE                  0x0020	/* LED Probe mode */
#घोषणा IFE_PSCL_PROBE_LEDS_OFF              0x0006	/* Force LEDs 0 and 2 off */
#घोषणा IFE_PSCL_PROBE_LEDS_ON               0x0007	/* Force LEDs 0 and 2 on */

#घोषणा ICH_FLASH_COMMAND_TIMEOUT            5000	/* 5000 uSecs - adjusted */
#घोषणा ICH_FLASH_ERASE_TIMEOUT              3000000	/* Up to 3 seconds - worst हाल */
#घोषणा ICH_FLASH_CYCLE_REPEAT_COUNT         10	/* 10 cycles */
#घोषणा ICH_FLASH_SEG_SIZE_256               256
#घोषणा ICH_FLASH_SEG_SIZE_4K                4096
#घोषणा ICH_FLASH_SEG_SIZE_64K               65536

#घोषणा ICH_CYCLE_READ                       0x0
#घोषणा ICH_CYCLE_RESERVED                   0x1
#घोषणा ICH_CYCLE_WRITE                      0x2
#घोषणा ICH_CYCLE_ERASE                      0x3

#घोषणा ICH_FLASH_GFPREG   0x0000
#घोषणा ICH_FLASH_HSFSTS   0x0004
#घोषणा ICH_FLASH_HSFCTL   0x0006
#घोषणा ICH_FLASH_FADDR    0x0008
#घोषणा ICH_FLASH_FDATA0   0x0010
#घोषणा ICH_FLASH_FRACC    0x0050
#घोषणा ICH_FLASH_FREG0    0x0054
#घोषणा ICH_FLASH_FREG1    0x0058
#घोषणा ICH_FLASH_FREG2    0x005C
#घोषणा ICH_FLASH_FREG3    0x0060
#घोषणा ICH_FLASH_FPR0     0x0074
#घोषणा ICH_FLASH_FPR1     0x0078
#घोषणा ICH_FLASH_SSFSTS   0x0090
#घोषणा ICH_FLASH_SSFCTL   0x0092
#घोषणा ICH_FLASH_PREOP    0x0094
#घोषणा ICH_FLASH_OPTYPE   0x0096
#घोषणा ICH_FLASH_OPMENU   0x0098

#घोषणा ICH_FLASH_REG_MAPSIZE      0x00A0
#घोषणा ICH_FLASH_SECTOR_SIZE      4096
#घोषणा ICH_GFPREG_BASE_MASK       0x1FFF
#घोषणा ICH_FLASH_LINEAR_ADDR_MASK 0x00FFFFFF

/* Miscellaneous PHY bit definitions. */
#घोषणा PHY_PREAMBLE        0xFFFFFFFF
#घोषणा PHY_SOF             0x01
#घोषणा PHY_OP_READ         0x02
#घोषणा PHY_OP_WRITE        0x01
#घोषणा PHY_TURNAROUND      0x02
#घोषणा PHY_PREAMBLE_SIZE   32
#घोषणा MII_CR_SPEED_1000   0x0040
#घोषणा MII_CR_SPEED_100    0x2000
#घोषणा MII_CR_SPEED_10     0x0000
#घोषणा E1000_PHY_ADDRESS   0x01
#घोषणा PHY_AUTO_NEG_TIME   45	/* 4.5 Seconds */
#घोषणा PHY_FORCE_TIME      20	/* 2.0 Seconds */
#घोषणा PHY_REVISION_MASK   0xFFFFFFF0
#घोषणा DEVICE_SPEED_MASK   0x00000300	/* Device Ctrl Reg Speed Mask */
#घोषणा REG4_SPEED_MASK     0x01E0
#घोषणा REG9_SPEED_MASK     0x0300
#घोषणा ADVERTISE_10_HALF   0x0001
#घोषणा ADVERTISE_10_FULL   0x0002
#घोषणा ADVERTISE_100_HALF  0x0004
#घोषणा ADVERTISE_100_FULL  0x0008
#घोषणा ADVERTISE_1000_HALF 0x0010
#घोषणा ADVERTISE_1000_FULL 0x0020
#घोषणा AUTONEG_ADVERTISE_SPEED_DEFAULT 0x002F	/* Everything but 1000-Half */
#घोषणा AUTONEG_ADVERTISE_10_100_ALL    0x000F	/* All 10/100 speeds */
#घोषणा AUTONEG_ADVERTISE_10_ALL        0x0003	/* 10Mbps Full & Half speeds */

#पूर्ण_अगर /* _E1000_HW_H_ */
