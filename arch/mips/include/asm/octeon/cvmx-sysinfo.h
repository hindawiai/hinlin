<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
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
 * This module provides प्रणाली/board inक्रमmation obtained by the bootloader.
 */

#अगर_अघोषित __CVMX_SYSINFO_H__
#घोषणा __CVMX_SYSINFO_H__

#समावेश "cvmx-coremask.h"

#घोषणा OCTEON_SERIAL_LEN 20
/**
 * Structure describing application specअगरic inक्रमmation.
 * __cvmx_app_init() populates this from the cvmx boot descriptor.
 * This काष्ठाure is निजी to simple executive applications, so
 * no versioning is required.
 *
 * This काष्ठाure must be provided with some fields set in order to
 * use simple executive functions in other applications (Linux kernel,
 * u-boot, etc.)  The cvmx_sysinfo_minimal_initialize() function is
 * provided to set the required values in these हालs.
 */
काष्ठा cvmx_sysinfo अणु
	/* System wide variables */
	/* installed DRAM in प्रणाली, in bytes */
	uपूर्णांक64_t प्रणाली_dram_size;

	/* ptr to memory descriptor block */
	uपूर्णांक64_t phy_mem_desc_addr;

	/* Application image specअगरic variables */
	/* stack top address (भव) */
	uपूर्णांक64_t stack_top;
	/* heap base address (भव) */
	uपूर्णांक64_t heap_base;
	/* stack size in bytes */
	uपूर्णांक32_t stack_size;
	/* heap size in bytes */
	uपूर्णांक32_t heap_size;
	/* coremask defining cores running application */
	काष्ठा cvmx_coremask core_mask;
	/* Deprecated, use cvmx_coremask_first_core() to select init core */
	uपूर्णांक32_t init_core;

	/* exception base address, as set by bootloader */
	uपूर्णांक64_t exception_base_addr;

	/* cpu घड़ी speed in hz */
	uपूर्णांक32_t cpu_घड़ी_hz;

	/* dram data rate in hz (data rate = 2 * घड़ी rate */
	uपूर्णांक32_t dram_data_rate_hz;


	uपूर्णांक16_t board_type;
	uपूर्णांक8_t board_rev_major;
	uपूर्णांक8_t board_rev_minor;
	uपूर्णांक8_t mac_addr_base[6];
	uपूर्णांक8_t mac_addr_count;
	अक्षर board_serial_number[OCTEON_SERIAL_LEN];
	/*
	 * Several boards support compact flash on the Octeon boot
	 * bus.	 The CF memory spaces may be mapped to dअगरferent
	 * addresses on dअगरferent boards.  These values will be 0 अगर
	 * CF is not present.  Note that these addresses are physical
	 * addresses, and it is up to the application to use the
	 * proper addressing mode (XKPHYS, KSEG0, etc.)
	 */
	uपूर्णांक64_t compact_flash_common_base_addr;
	uपूर्णांक64_t compact_flash_attribute_base_addr;
	/*
	 * Base address of the LED display (as on EBT3000 board) This
	 * will be 0 अगर LED display not present.  Note that this
	 * address is a physical address, and it is up to the
	 * application to use the proper addressing mode (XKPHYS,
	 * KSEG0, etc.)
	 */
	uपूर्णांक64_t led_display_base_addr;
	/* DFA reference घड़ी in hz (अगर applicable)*/
	uपूर्णांक32_t dfa_ref_घड़ी_hz;
	/* configuration flags from bootloader */
	uपूर्णांक32_t bootloader_config_flags;

	/* Uart number used क्रम console */
	uपूर्णांक8_t console_uart_num;
पूर्ण;

/**
 * This function वापसs the प्रणाली/board inक्रमmation as obtained
 * by the bootloader.
 *
 *
 * Returns  Poपूर्णांकer to the boot inक्रमmation काष्ठाure
 *
 */

बाह्य काष्ठा cvmx_sysinfo *cvmx_sysinfo_get(व्योम);

#पूर्ण_अगर /* __CVMX_SYSINFO_H__ */
