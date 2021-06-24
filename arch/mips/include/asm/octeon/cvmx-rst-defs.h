<शैली गुरु>
/***********************license start***************
 * Author: Cavium Inc.
 *
 * Contact: support@cavium.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2014 Cavium Inc.
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
 * Contact Cavium Inc. क्रम more inक्रमmation
 ***********************license end**************************************/

#अगर_अघोषित __CVMX_RST_DEFS_H__
#घोषणा __CVMX_RST_DEFS_H__

#घोषणा CVMX_RST_BOOT (CVMX_ADD_IO_SEG(0x0001180006001600ull))
#घोषणा CVMX_RST_CFG (CVMX_ADD_IO_SEG(0x0001180006001610ull))
#घोषणा CVMX_RST_CKILL (CVMX_ADD_IO_SEG(0x0001180006001638ull))
#घोषणा CVMX_RST_CTLX(offset) (CVMX_ADD_IO_SEG(0x0001180006001640ull) + ((offset) & 3) * 8)
#घोषणा CVMX_RST_DELAY (CVMX_ADD_IO_SEG(0x0001180006001608ull))
#घोषणा CVMX_RST_ECO (CVMX_ADD_IO_SEG(0x00011800060017B8ull))
#घोषणा CVMX_RST_INT (CVMX_ADD_IO_SEG(0x0001180006001628ull))
#घोषणा CVMX_RST_OCX (CVMX_ADD_IO_SEG(0x0001180006001618ull))
#घोषणा CVMX_RST_POWER_DBG (CVMX_ADD_IO_SEG(0x0001180006001708ull))
#घोषणा CVMX_RST_PP_POWER (CVMX_ADD_IO_SEG(0x0001180006001700ull))
#घोषणा CVMX_RST_SOFT_PRSTX(offset) (CVMX_ADD_IO_SEG(0x00011800060016C0ull) + ((offset) & 3) * 8)
#घोषणा CVMX_RST_SOFT_RST (CVMX_ADD_IO_SEG(0x0001180006001680ull))

जोड़ cvmx_rst_boot अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rst_boot_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t chipसमाप्त:1;
		uपूर्णांक64_t jtcsrdis:1;
		uपूर्णांक64_t ejtagdis:1;
		uपूर्णांक64_t romen:1;
		uपूर्णांक64_t cसमाप्त_ppdis:1;
		uपूर्णांक64_t jt_tsपंचांगode:1;
		uपूर्णांक64_t vrm_err:1;
		uपूर्णांक64_t reserved_37_56:20;
		uपूर्णांक64_t c_mul:7;
		uपूर्णांक64_t pnr_mul:6;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t lboot_oci:3;
		uपूर्णांक64_t lboot_ext:6;
		uपूर्णांक64_t lboot:10;
		uपूर्णांक64_t rboot:1;
		uपूर्णांक64_t rboot_pin:1;
#अन्यथा
		uपूर्णांक64_t rboot_pin:1;
		uपूर्णांक64_t rboot:1;
		uपूर्णांक64_t lboot:10;
		uपूर्णांक64_t lboot_ext:6;
		uपूर्णांक64_t lboot_oci:3;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t pnr_mul:6;
		uपूर्णांक64_t c_mul:7;
		uपूर्णांक64_t reserved_37_56:20;
		uपूर्णांक64_t vrm_err:1;
		uपूर्णांक64_t jt_tsपंचांगode:1;
		uपूर्णांक64_t cसमाप्त_ppdis:1;
		uपूर्णांक64_t romen:1;
		uपूर्णांक64_t ejtagdis:1;
		uपूर्णांक64_t jtcsrdis:1;
		uपूर्णांक64_t chipसमाप्त:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_rst_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rst_cfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bist_delay:58;
		uपूर्णांक64_t reserved_3_5:3;
		uपूर्णांक64_t cntl_clr_bist:1;
		uपूर्णांक64_t warm_clr_bist:1;
		uपूर्णांक64_t soft_clr_bist:1;
#अन्यथा
		uपूर्णांक64_t soft_clr_bist:1;
		uपूर्णांक64_t warm_clr_bist:1;
		uपूर्णांक64_t cntl_clr_bist:1;
		uपूर्णांक64_t reserved_3_5:3;
		uपूर्णांक64_t bist_delay:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_rst_cसमाप्त अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rst_cसमाप्त_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_47_63:17;
		uपूर्णांक64_t समयr:47;
#अन्यथा
		uपूर्णांक64_t समयr:47;
		uपूर्णांक64_t reserved_47_63:17;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_rst_ctlx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rst_ctlx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t prst_link:1;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t rst_link:1;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t reserved_4_5:2;
		uपूर्णांक64_t rst_drv:1;
		uपूर्णांक64_t rst_rcv:1;
		uपूर्णांक64_t rst_chip:1;
		uपूर्णांक64_t rst_val:1;
#अन्यथा
		uपूर्णांक64_t rst_val:1;
		uपूर्णांक64_t rst_chip:1;
		uपूर्णांक64_t rst_rcv:1;
		uपूर्णांक64_t rst_drv:1;
		uपूर्णांक64_t reserved_4_5:2;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t rst_link:1;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t prst_link:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_rst_delay अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rst_delay_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t warm_rst_dly:16;
		uपूर्णांक64_t soft_rst_dly:16;
#अन्यथा
		uपूर्णांक64_t soft_rst_dly:16;
		uपूर्णांक64_t warm_rst_dly:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_rst_eco अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rst_eco_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t eco_rw:32;
#अन्यथा
		uपूर्णांक64_t eco_rw:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_rst_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rst_पूर्णांक_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t perst:4;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t rst_link:4;
#अन्यथा
		uपूर्णांक64_t rst_link:4;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t perst:4;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_rst_पूर्णांक_cn70xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t perst:3;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t rst_link:3;
#अन्यथा
		uपूर्णांक64_t rst_link:3;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t perst:3;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण cn70xx;
पूर्ण;

जोड़ cvmx_rst_ocx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rst_ocx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t rst_link:3;
#अन्यथा
		uपूर्णांक64_t rst_link:3;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_rst_घातer_dbg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rst_घातer_dbg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t str:3;
#अन्यथा
		uपूर्णांक64_t str:3;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_rst_pp_घातer अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rst_pp_घातer_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t gate:48;
#अन्यथा
		uपूर्णांक64_t gate:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_rst_pp_घातer_cn70xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t gate:4;
#अन्यथा
		uपूर्णांक64_t gate:4;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण cn70xx;
पूर्ण;

जोड़ cvmx_rst_soft_prstx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rst_soft_prstx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t soft_prst:1;
#अन्यथा
		uपूर्णांक64_t soft_prst:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_rst_soft_rst अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rst_soft_rst_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t soft_rst:1;
#अन्यथा
		uपूर्णांक64_t soft_rst:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
