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

#अगर_अघोषित __CVMX_SRXX_DEFS_H__
#घोषणा __CVMX_SRXX_DEFS_H__

#घोषणा CVMX_SRXX_COM_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180090000200ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SRXX_IGN_RX_FULL(block_id) (CVMX_ADD_IO_SEG(0x0001180090000218ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SRXX_SPI4_CALX(offset, block_id) (CVMX_ADD_IO_SEG(0x0001180090000000ull) + (((offset) & 31) + ((block_id) & 1) * 0x1000000ull) * 8)
#घोषणा CVMX_SRXX_SPI4_STAT(block_id) (CVMX_ADD_IO_SEG(0x0001180090000208ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SRXX_SW_TICK_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180090000220ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SRXX_SW_TICK_DAT(block_id) (CVMX_ADD_IO_SEG(0x0001180090000228ull) + ((block_id) & 1) * 0x8000000ull)

जोड़ cvmx_srxx_com_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_srxx_com_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t prts:4;
		uपूर्णांक64_t st_en:1;
		uपूर्णांक64_t reserved_1_2:2;
		uपूर्णांक64_t inf_en:1;
#अन्यथा
		uपूर्णांक64_t inf_en:1;
		uपूर्णांक64_t reserved_1_2:2;
		uपूर्णांक64_t st_en:1;
		uपूर्णांक64_t prts:4;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_srxx_ign_rx_full अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_srxx_ign_rx_full_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t ignore:16;
#अन्यथा
		uपूर्णांक64_t ignore:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_srxx_spi4_calx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_srxx_spi4_calx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t oddpar:1;
		uपूर्णांक64_t prt3:4;
		uपूर्णांक64_t prt2:4;
		uपूर्णांक64_t prt1:4;
		uपूर्णांक64_t prt0:4;
#अन्यथा
		uपूर्णांक64_t prt0:4;
		uपूर्णांक64_t prt1:4;
		uपूर्णांक64_t prt2:4;
		uपूर्णांक64_t prt3:4;
		uपूर्णांक64_t oddpar:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_srxx_spi4_stat अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_srxx_spi4_stat_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t m:8;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t len:7;
#अन्यथा
		uपूर्णांक64_t len:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t m:8;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_srxx_sw_tick_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_srxx_sw_tick_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t eop:1;
		uपूर्णांक64_t sop:1;
		uपूर्णांक64_t mod:4;
		uपूर्णांक64_t opc:4;
		uपूर्णांक64_t adr:4;
#अन्यथा
		uपूर्णांक64_t adr:4;
		uपूर्णांक64_t opc:4;
		uपूर्णांक64_t mod:4;
		uपूर्णांक64_t sop:1;
		uपूर्णांक64_t eop:1;
		uपूर्णांक64_t reserved_14_63:50;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_srxx_sw_tick_dat अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_srxx_sw_tick_dat_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t dat:64;
#अन्यथा
		uपूर्णांक64_t dat:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
