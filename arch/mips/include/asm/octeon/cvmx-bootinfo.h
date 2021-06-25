<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2008 Cavium Networks
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this file; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a dअगरferent license from Cavium.
 * Contact Cavium Networks क्रम more inक्रमmation
 ***********************license end**************************************/

/*
 * Header file containing the ABI with the bootloader.
 */

#अगर_अघोषित __CVMX_BOOTINFO_H__
#घोषणा __CVMX_BOOTINFO_H__

#समावेश "cvmx-coremask.h"

/*
 * Current major and minor versions of the CVMX bootinfo block that is
 * passed from the bootloader to the application.  This is versioned
 * so that applications can properly handle multiple bootloader
 * versions.
 */
#घोषणा CVMX_BOOTINFO_MAJ_VER 1
#घोषणा CVMX_BOOTINFO_MIN_VER 4

#अगर (CVMX_BOOTINFO_MAJ_VER == 1)
#घोषणा CVMX_BOOTINFO_OCTEON_SERIAL_LEN 20
/*
 * This काष्ठाure is populated by the bootloader.  For binary
 * compatibility the only changes that should be made are
 * adding members to the end of the काष्ठाure, and the minor
 * version should be incremented at that समय.
 * If an incompatible change is made, the major version
 * must be incremented, and the minor version should be reset
 * to 0.
 */
काष्ठा cvmx_bootinfo अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक32_t major_version;
	uपूर्णांक32_t minor_version;

	uपूर्णांक64_t stack_top;
	uपूर्णांक64_t heap_base;
	uपूर्णांक64_t heap_end;
	uपूर्णांक64_t desc_vaddr;

	uपूर्णांक32_t exception_base_addr;
	uपूर्णांक32_t stack_size;
	uपूर्णांक32_t flags;
	uपूर्णांक32_t core_mask;
	/* DRAM size in megabytes */
	uपूर्णांक32_t dram_size;
	/* physical address of मुक्त memory descriptor block*/
	uपूर्णांक32_t phy_mem_desc_addr;
	/* used to pass flags from app to debugger */
	uपूर्णांक32_t debugger_flags_base_addr;

	/* CPU घड़ी speed, in hz */
	uपूर्णांक32_t eघड़ी_hz;

	/* DRAM घड़ी speed, in hz */
	uपूर्णांक32_t dघड़ी_hz;

	uपूर्णांक32_t reserved0;
	uपूर्णांक16_t board_type;
	uपूर्णांक8_t board_rev_major;
	uपूर्णांक8_t board_rev_minor;
	uपूर्णांक16_t reserved1;
	uपूर्णांक8_t reserved2;
	uपूर्णांक8_t reserved3;
	अक्षर board_serial_number[CVMX_BOOTINFO_OCTEON_SERIAL_LEN];
	uपूर्णांक8_t mac_addr_base[6];
	uपूर्णांक8_t mac_addr_count;
#अगर (CVMX_BOOTINFO_MIN_VER >= 1)
	/*
	 * Several boards support compact flash on the Octeon boot
	 * bus.	 The CF memory spaces may be mapped to dअगरferent
	 * addresses on dअगरferent boards.  These are the physical
	 * addresses, so care must be taken to use the correct
	 * XKPHYS/KSEG0 addressing depending on the application's
	 * ABI.	 These values will be 0 अगर CF is not present.
	 */
	uपूर्णांक64_t compact_flash_common_base_addr;
	uपूर्णांक64_t compact_flash_attribute_base_addr;
	/*
	 * Base address of the LED display (as on EBT3000 board)
	 * This will be 0 अगर LED display not present.
	 */
	uपूर्णांक64_t led_display_base_addr;
#पूर्ण_अगर
#अगर (CVMX_BOOTINFO_MIN_VER >= 2)
	/* DFA reference घड़ी in hz (अगर applicable)*/
	uपूर्णांक32_t dfa_ref_घड़ी_hz;

	/*
	 * flags indicating various configuration options.  These
	 * flags supercede the 'flags' variable and should be used
	 * instead अगर available.
	 */
	uपूर्णांक32_t config_flags;
#पूर्ण_अगर
#अगर (CVMX_BOOTINFO_MIN_VER >= 3)
	/*
	 * Address of the OF Flattened Device Tree काष्ठाure
	 * describing the board.
	 */
	uपूर्णांक64_t fdt_addr;
#पूर्ण_अगर
#अगर (CVMX_BOOTINFO_MIN_VER >= 4)
	/*
	 * Coremask used क्रम processors with more than 32 cores
	 * or with OCI.  This replaces core_mask.
	 */
	काष्ठा cvmx_coremask ext_core_mask;
#पूर्ण_अगर
#अन्यथा				/* __BIG_ENDIAN */
	/*
	 * Little-Endian: When the CPU mode is चयनed to
	 * little-endian, the view of the काष्ठाure has some of the
	 * fields swapped.
	 */
	uपूर्णांक32_t minor_version;
	uपूर्णांक32_t major_version;

	uपूर्णांक64_t stack_top;
	uपूर्णांक64_t heap_base;
	uपूर्णांक64_t heap_end;
	uपूर्णांक64_t desc_vaddr;

	uपूर्णांक32_t stack_size;
	uपूर्णांक32_t exception_base_addr;

	uपूर्णांक32_t core_mask;
	uपूर्णांक32_t flags;

	uपूर्णांक32_t phy_mem_desc_addr;
	uपूर्णांक32_t dram_size;

	uपूर्णांक32_t eघड़ी_hz;
	uपूर्णांक32_t debugger_flags_base_addr;

	uपूर्णांक32_t reserved0;
	uपूर्णांक32_t dघड़ी_hz;

	uपूर्णांक8_t reserved3;
	uपूर्णांक8_t reserved2;
	uपूर्णांक16_t reserved1;
	uपूर्णांक8_t board_rev_minor;
	uपूर्णांक8_t board_rev_major;
	uपूर्णांक16_t board_type;

	अक्षर board_serial_number[CVMX_BOOTINFO_OCTEON_SERIAL_LEN];
	uपूर्णांक8_t mac_addr_base[6];
	uपूर्णांक8_t mac_addr_count;
	uपूर्णांक8_t pad[5];

#अगर (CVMX_BOOTINFO_MIN_VER >= 1)
	uपूर्णांक64_t compact_flash_common_base_addr;
	uपूर्णांक64_t compact_flash_attribute_base_addr;
	uपूर्णांक64_t led_display_base_addr;
#पूर्ण_अगर
#अगर (CVMX_BOOTINFO_MIN_VER >= 2)
	uपूर्णांक32_t config_flags;
	uपूर्णांक32_t dfa_ref_घड़ी_hz;
#पूर्ण_अगर
#अगर (CVMX_BOOTINFO_MIN_VER >= 3)
	uपूर्णांक64_t fdt_addr;
#पूर्ण_अगर
#अगर (CVMX_BOOTINFO_MIN_VER >= 4)
	काष्ठा cvmx_coremask ext_core_mask;
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण;

#घोषणा CVMX_BOOTINFO_CFG_FLAG_PCI_HOST			(1ull << 0)
#घोषणा CVMX_BOOTINFO_CFG_FLAG_PCI_TARGET		(1ull << 1)
#घोषणा CVMX_BOOTINFO_CFG_FLAG_DEBUG			(1ull << 2)
#घोषणा CVMX_BOOTINFO_CFG_FLAG_NO_MAGIC			(1ull << 3)
/* This flag is set अगर the TLB mappings are not contained in the
 * 0x10000000 - 0x20000000 boot bus region. */
#घोषणा CVMX_BOOTINFO_CFG_FLAG_OVERSIZE_TLB_MAPPING	(1ull << 4)
#घोषणा CVMX_BOOTINFO_CFG_FLAG_BREAK			(1ull << 5)

#पूर्ण_अगर /*   (CVMX_BOOTINFO_MAJ_VER == 1) */

/* Type defines क्रम board and chip types */
क्रमागत cvmx_board_types_क्रमागत अणु
	CVMX_BOARD_TYPE_शून्य = 0,
	CVMX_BOARD_TYPE_SIM = 1,
	CVMX_BOARD_TYPE_EBT3000 = 2,
	CVMX_BOARD_TYPE_KODAMA = 3,
	CVMX_BOARD_TYPE_NIAGARA = 4,
	CVMX_BOARD_TYPE_NAC38 = 5,	/* क्रमmerly NAO38 */
	CVMX_BOARD_TYPE_THUNDER = 6,
	CVMX_BOARD_TYPE_TRANTOR = 7,
	CVMX_BOARD_TYPE_EBH3000 = 8,
	CVMX_BOARD_TYPE_EBH3100 = 9,
	CVMX_BOARD_TYPE_HIKARI = 10,
	CVMX_BOARD_TYPE_CN3010_EVB_HS5 = 11,
	CVMX_BOARD_TYPE_CN3005_EVB_HS5 = 12,
	CVMX_BOARD_TYPE_KBP = 13,
	/* Deprecated, CVMX_BOARD_TYPE_CN3010_EVB_HS5 supports the CN3020 */
	CVMX_BOARD_TYPE_CN3020_EVB_HS5 = 14,
	CVMX_BOARD_TYPE_EBT5800 = 15,
	CVMX_BOARD_TYPE_NICPRO2 = 16,
	CVMX_BOARD_TYPE_EBH5600 = 17,
	CVMX_BOARD_TYPE_EBH5601 = 18,
	CVMX_BOARD_TYPE_EBH5200 = 19,
	CVMX_BOARD_TYPE_BBGW_REF = 20,
	CVMX_BOARD_TYPE_NIC_XLE_4G = 21,
	CVMX_BOARD_TYPE_EBT5600 = 22,
	CVMX_BOARD_TYPE_EBH5201 = 23,
	CVMX_BOARD_TYPE_EBT5200 = 24,
	CVMX_BOARD_TYPE_CB5600	= 25,
	CVMX_BOARD_TYPE_CB5601	= 26,
	CVMX_BOARD_TYPE_CB5200	= 27,
	/* Special 'generic' board type, supports many boards */
	CVMX_BOARD_TYPE_GENERIC = 28,
	CVMX_BOARD_TYPE_EBH5610 = 29,
	CVMX_BOARD_TYPE_LANAI2_A = 30,
	CVMX_BOARD_TYPE_LANAI2_U = 31,
	CVMX_BOARD_TYPE_EBB5600 = 32,
	CVMX_BOARD_TYPE_EBB6300 = 33,
	CVMX_BOARD_TYPE_NIC_XLE_10G = 34,
	CVMX_BOARD_TYPE_LANAI2_G = 35,
	CVMX_BOARD_TYPE_EBT5810 = 36,
	CVMX_BOARD_TYPE_NIC10E = 37,
	CVMX_BOARD_TYPE_EP6300C = 38,
	CVMX_BOARD_TYPE_EBB6800 = 39,
	CVMX_BOARD_TYPE_NIC4E = 40,
	CVMX_BOARD_TYPE_NIC2E = 41,
	CVMX_BOARD_TYPE_EBB6600 = 42,
	CVMX_BOARD_TYPE_REDWING = 43,
	CVMX_BOARD_TYPE_NIC68_4 = 44,
	CVMX_BOARD_TYPE_NIC10E_66 = 45,
	CVMX_BOARD_TYPE_MAX,

	/*
	 * The range from CVMX_BOARD_TYPE_MAX to
	 * CVMX_BOARD_TYPE_CUST_DEFINED_MIN is reserved क्रम future
	 * SDK use.
	 */

	/*
	 * Set aside a range क्रम customer boards.  These numbers are managed
	 * by Cavium.
	 */
	CVMX_BOARD_TYPE_CUST_DEFINED_MIN = 10000,
	CVMX_BOARD_TYPE_CUST_WSX16 = 10001,
	CVMX_BOARD_TYPE_CUST_NS0216 = 10002,
	CVMX_BOARD_TYPE_CUST_NB5 = 10003,
	CVMX_BOARD_TYPE_CUST_WMR500 = 10004,
	CVMX_BOARD_TYPE_CUST_ITB101 = 10005,
	CVMX_BOARD_TYPE_CUST_NTE102 = 10006,
	CVMX_BOARD_TYPE_CUST_AGS103 = 10007,
	CVMX_BOARD_TYPE_CUST_GST104 = 10008,
	CVMX_BOARD_TYPE_CUST_GCT105 = 10009,
	CVMX_BOARD_TYPE_CUST_AGS106 = 10010,
	CVMX_BOARD_TYPE_CUST_SGM107 = 10011,
	CVMX_BOARD_TYPE_CUST_GCT108 = 10012,
	CVMX_BOARD_TYPE_CUST_AGS109 = 10013,
	CVMX_BOARD_TYPE_CUST_GCT110 = 10014,
	CVMX_BOARD_TYPE_CUST_L2_AIR_SENDER = 10015,
	CVMX_BOARD_TYPE_CUST_L2_AIR_RECEIVER = 10016,
	CVMX_BOARD_TYPE_CUST_L2_ACCTON2_TX = 10017,
	CVMX_BOARD_TYPE_CUST_L2_ACCTON2_RX = 10018,
	CVMX_BOARD_TYPE_CUST_L2_WSTRNSNIC_TX = 10019,
	CVMX_BOARD_TYPE_CUST_L2_WSTRNSNIC_RX = 10020,
	CVMX_BOARD_TYPE_CUST_L2_ZINWELL = 10021,
	CVMX_BOARD_TYPE_CUST_DEFINED_MAX = 20000,

	/*
	 * Set aside a range क्रम customer निजी use.	The SDK won't
	 * use any numbers in this range.
	 */
	CVMX_BOARD_TYPE_CUST_PRIVATE_MIN = 20001,
	CVMX_BOARD_TYPE_UBNT_E100 = 20002,
	CVMX_BOARD_TYPE_UBNT_E200 = 20003,
	CVMX_BOARD_TYPE_UBNT_E220 = 20005,
	CVMX_BOARD_TYPE_CUST_DSR1000N = 20006,
	CVMX_BOARD_TYPE_UBNT_E300 = 20300,
	CVMX_BOARD_TYPE_KONTRON_S1901 = 21901,
	CVMX_BOARD_TYPE_CUST_PRIVATE_MAX = 30000,

	/* The reमुख्यing range is reserved क्रम future use. */
पूर्ण;

क्रमागत cvmx_chip_types_क्रमागत अणु
	CVMX_CHIP_TYPE_शून्य = 0,
	CVMX_CHIP_SIM_TYPE_DEPRECATED = 1,
	CVMX_CHIP_TYPE_OCTEON_SAMPLE = 2,
	CVMX_CHIP_TYPE_MAX,
पूर्ण;

/* Compatibility alias क्रम NAC38 name change, planned to be हटाओd
 * from SDK 1.7 */
#घोषणा CVMX_BOARD_TYPE_NAO38	CVMX_BOARD_TYPE_NAC38

/* Functions to वापस string based on type */
#घोषणा ENUM_BRD_TYPE_CASE(x) \
	हाल x: वापस(#x + 16);	/* Skip CVMX_BOARD_TYPE_ */
अटल अंतरभूत स्थिर अक्षर *cvmx_board_type_to_string(क्रमागत
						    cvmx_board_types_क्रमागत type)
अणु
	चयन (type) अणु
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_शून्य)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_SIM)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBT3000)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_KODAMA)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIAGARA)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NAC38)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_THUNDER)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_TRANTOR)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBH3000)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBH3100)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_HIKARI)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CN3010_EVB_HS5)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CN3005_EVB_HS5)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_KBP)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CN3020_EVB_HS5)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBT5800)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NICPRO2)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBH5600)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBH5601)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBH5200)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_BBGW_REF)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIC_XLE_4G)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBT5600)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBH5201)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBT5200)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CB5600)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CB5601)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CB5200)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_GENERIC)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBH5610)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_LANAI2_A)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_LANAI2_U)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBB5600)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBB6300)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIC_XLE_10G)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_LANAI2_G)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBT5810)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIC10E)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EP6300C)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBB6800)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIC4E)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIC2E)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_EBB6600)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_REDWING)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIC68_4)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_NIC10E_66)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_MAX)

			/* Customer boards listed here */
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_DEFINED_MIN)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_WSX16)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_NS0216)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_NB5)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_WMR500)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_ITB101)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_NTE102)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_AGS103)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_GST104)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_GCT105)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_AGS106)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_SGM107)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_GCT108)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_AGS109)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_GCT110)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_L2_AIR_SENDER)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_L2_AIR_RECEIVER)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_L2_ACCTON2_TX)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_L2_ACCTON2_RX)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_L2_WSTRNSNIC_TX)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_L2_WSTRNSNIC_RX)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_L2_ZINWELL)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_DEFINED_MAX)

		    /* Customer निजी range */
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_PRIVATE_MIN)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_UBNT_E100)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_UBNT_E200)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_UBNT_E220)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_DSR1000N)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_UBNT_E300)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_KONTRON_S1901)
		ENUM_BRD_TYPE_CASE(CVMX_BOARD_TYPE_CUST_PRIVATE_MAX)
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा ENUM_CHIP_TYPE_CASE(x) \
	हाल x: वापस(#x + 15);	/* Skip CVMX_CHIP_TYPE */
अटल अंतरभूत स्थिर अक्षर *cvmx_chip_type_to_string(क्रमागत
						   cvmx_chip_types_क्रमागत type)
अणु
	चयन (type) अणु
		ENUM_CHIP_TYPE_CASE(CVMX_CHIP_TYPE_शून्य)
		ENUM_CHIP_TYPE_CASE(CVMX_CHIP_SIM_TYPE_DEPRECATED)
		ENUM_CHIP_TYPE_CASE(CVMX_CHIP_TYPE_OCTEON_SAMPLE)
		ENUM_CHIP_TYPE_CASE(CVMX_CHIP_TYPE_MAX)
	पूर्ण
	वापस "Unsupported Chip";
पूर्ण

#पूर्ण_अगर /* __CVMX_BOOTINFO_H__ */
