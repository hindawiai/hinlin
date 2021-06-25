<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2012 Cavium Networks
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

#अगर_अघोषित __CVMX_LED_DEFS_H__
#घोषणा __CVMX_LED_DEFS_H__

#घोषणा CVMX_LED_BLINK (CVMX_ADD_IO_SEG(0x0001180000001A48ull))
#घोषणा CVMX_LED_CLK_PHASE (CVMX_ADD_IO_SEG(0x0001180000001A08ull))
#घोषणा CVMX_LED_CYLON (CVMX_ADD_IO_SEG(0x0001180000001AF8ull))
#घोषणा CVMX_LED_DBG (CVMX_ADD_IO_SEG(0x0001180000001A18ull))
#घोषणा CVMX_LED_EN (CVMX_ADD_IO_SEG(0x0001180000001A00ull))
#घोषणा CVMX_LED_POLARITY (CVMX_ADD_IO_SEG(0x0001180000001A50ull))
#घोषणा CVMX_LED_PRT (CVMX_ADD_IO_SEG(0x0001180000001A10ull))
#घोषणा CVMX_LED_PRT_FMT (CVMX_ADD_IO_SEG(0x0001180000001A30ull))
#घोषणा CVMX_LED_PRT_STATUSX(offset) (CVMX_ADD_IO_SEG(0x0001180000001A80ull) + ((offset) & 7) * 8)
#घोषणा CVMX_LED_UDD_CNTX(offset) (CVMX_ADD_IO_SEG(0x0001180000001A20ull) + ((offset) & 1) * 8)
#घोषणा CVMX_LED_UDD_DATX(offset) (CVMX_ADD_IO_SEG(0x0001180000001A38ull) + ((offset) & 1) * 8)
#घोषणा CVMX_LED_UDD_DAT_CLRX(offset) (CVMX_ADD_IO_SEG(0x0001180000001AC8ull) + ((offset) & 1) * 16)
#घोषणा CVMX_LED_UDD_DAT_SETX(offset) (CVMX_ADD_IO_SEG(0x0001180000001AC0ull) + ((offset) & 1) * 16)

जोड़ cvmx_led_blink अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_led_blink_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t rate:8;
#अन्यथा
		uपूर्णांक64_t rate:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_led_clk_phase अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_led_clk_phase_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t phase:7;
#अन्यथा
		uपूर्णांक64_t phase:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_led_cylon अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_led_cylon_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t rate:16;
#अन्यथा
		uपूर्णांक64_t rate:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_led_dbg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_led_dbg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t dbg_en:1;
#अन्यथा
		uपूर्णांक64_t dbg_en:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_led_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_led_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t en:1;
#अन्यथा
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_led_polarity अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_led_polarity_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t polarity:1;
#अन्यथा
		uपूर्णांक64_t polarity:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_led_prt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_led_prt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t prt_en:8;
#अन्यथा
		uपूर्णांक64_t prt_en:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_led_prt_fmt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_led_prt_fmt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t क्रमmat:4;
#अन्यथा
		uपूर्णांक64_t क्रमmat:4;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_led_prt_statusx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_led_prt_statusx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t status:6;
#अन्यथा
		uपूर्णांक64_t status:6;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_led_udd_cntx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_led_udd_cntx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t cnt:6;
#अन्यथा
		uपूर्णांक64_t cnt:6;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_led_udd_datx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_led_udd_datx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t dat:32;
#अन्यथा
		uपूर्णांक64_t dat:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_led_udd_dat_clrx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_led_udd_dat_clrx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t clr:32;
#अन्यथा
		uपूर्णांक64_t clr:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_led_udd_dat_setx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_led_udd_dat_setx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t set:32;
#अन्यथा
		uपूर्णांक64_t set:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
