<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (C) 2003-2018 Cavium, Inc.
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

#अगर_अघोषित __CVMX_STXX_DEFS_H__
#घोषणा __CVMX_STXX_DEFS_H__

#घोषणा CVMX_STXX_ARB_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180090000608ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_STXX_BCKPRS_CNT(block_id) (CVMX_ADD_IO_SEG(0x0001180090000688ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_STXX_COM_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180090000600ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_STXX_DIP_CNT(block_id) (CVMX_ADD_IO_SEG(0x0001180090000690ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_STXX_IGN_CAL(block_id) (CVMX_ADD_IO_SEG(0x0001180090000610ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_STXX_INT_MSK(block_id) (CVMX_ADD_IO_SEG(0x00011800900006A0ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_STXX_INT_REG(block_id) (CVMX_ADD_IO_SEG(0x0001180090000698ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_STXX_INT_SYNC(block_id) (CVMX_ADD_IO_SEG(0x00011800900006A8ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_STXX_MIN_BST(block_id) (CVMX_ADD_IO_SEG(0x0001180090000618ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_STXX_SPI4_CALX(offset, block_id) (CVMX_ADD_IO_SEG(0x0001180090000400ull) + (((offset) & 31) + ((block_id) & 1) * 0x1000000ull) * 8)
#घोषणा CVMX_STXX_SPI4_DAT(block_id) (CVMX_ADD_IO_SEG(0x0001180090000628ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_STXX_SPI4_STAT(block_id) (CVMX_ADD_IO_SEG(0x0001180090000630ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_STXX_STAT_BYTES_HI(block_id) (CVMX_ADD_IO_SEG(0x0001180090000648ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_STXX_STAT_BYTES_LO(block_id) (CVMX_ADD_IO_SEG(0x0001180090000680ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_STXX_STAT_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180090000638ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_STXX_STAT_PKT_XMT(block_id) (CVMX_ADD_IO_SEG(0x0001180090000640ull) + ((block_id) & 1) * 0x8000000ull)

व्योम __cvmx_पूर्णांकerrupt_stxx_पूर्णांक_msk_enable(पूर्णांक index);

जोड़ cvmx_stxx_arb_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_arb_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t mपूर्णांकrn:1;
		uपूर्णांक64_t reserved_4_4:1;
		uपूर्णांक64_t igntpa:1;
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t igntpa:1;
		uपूर्णांक64_t reserved_4_4:1;
		uपूर्णांक64_t mपूर्णांकrn:1;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_bckprs_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_bckprs_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_com_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_com_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t st_en:1;
		uपूर्णांक64_t reserved_1_2:2;
		uपूर्णांक64_t inf_en:1;
#अन्यथा
		uपूर्णांक64_t inf_en:1;
		uपूर्णांक64_t reserved_1_2:2;
		uपूर्णांक64_t st_en:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_dip_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_dip_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t frmmax:4;
		uपूर्णांक64_t dipmax:4;
#अन्यथा
		uपूर्णांक64_t dipmax:4;
		uपूर्णांक64_t frmmax:4;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_ign_cal अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_ign_cal_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t igntpa:16;
#अन्यथा
		uपूर्णांक64_t igntpa:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_पूर्णांक_msk अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_पूर्णांक_msk_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t frmerr:1;
		uपूर्णांक64_t unxfrm:1;
		uपूर्णांक64_t nosync:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t datovr:1;
		uपूर्णांक64_t ovrbst:1;
		uपूर्णांक64_t calpar1:1;
		uपूर्णांक64_t calpar0:1;
#अन्यथा
		uपूर्णांक64_t calpar0:1;
		uपूर्णांक64_t calpar1:1;
		uपूर्णांक64_t ovrbst:1;
		uपूर्णांक64_t datovr:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t nosync:1;
		uपूर्णांक64_t unxfrm:1;
		uपूर्णांक64_t frmerr:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_पूर्णांक_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t syncerr:1;
		uपूर्णांक64_t frmerr:1;
		uपूर्णांक64_t unxfrm:1;
		uपूर्णांक64_t nosync:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t datovr:1;
		uपूर्णांक64_t ovrbst:1;
		uपूर्णांक64_t calpar1:1;
		uपूर्णांक64_t calpar0:1;
#अन्यथा
		uपूर्णांक64_t calpar0:1;
		uपूर्णांक64_t calpar1:1;
		uपूर्णांक64_t ovrbst:1;
		uपूर्णांक64_t datovr:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t nosync:1;
		uपूर्णांक64_t unxfrm:1;
		uपूर्णांक64_t frmerr:1;
		uपूर्णांक64_t syncerr:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_पूर्णांक_sync अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_पूर्णांक_sync_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t frmerr:1;
		uपूर्णांक64_t unxfrm:1;
		uपूर्णांक64_t nosync:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t datovr:1;
		uपूर्णांक64_t ovrbst:1;
		uपूर्णांक64_t calpar1:1;
		uपूर्णांक64_t calpar0:1;
#अन्यथा
		uपूर्णांक64_t calpar0:1;
		uपूर्णांक64_t calpar1:1;
		uपूर्णांक64_t ovrbst:1;
		uपूर्णांक64_t datovr:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t nosync:1;
		uपूर्णांक64_t unxfrm:1;
		uपूर्णांक64_t frmerr:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_min_bst अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_min_bst_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t minb:9;
#अन्यथा
		uपूर्णांक64_t minb:9;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_spi4_calx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_spi4_calx_s अणु
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

जोड़ cvmx_stxx_spi4_dat अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_spi4_dat_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t alpha:16;
		uपूर्णांक64_t max_t:16;
#अन्यथा
		uपूर्णांक64_t max_t:16;
		uपूर्णांक64_t alpha:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_spi4_stat अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_spi4_stat_s अणु
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

जोड़ cvmx_stxx_stat_bytes_hi अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_stat_bytes_hi_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_stat_bytes_lo अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_stat_bytes_lo_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_stat_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_stat_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t clr:1;
		uपूर्णांक64_t bckprs:4;
#अन्यथा
		uपूर्णांक64_t bckprs:4;
		uपूर्णांक64_t clr:1;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_stxx_stat_pkt_xmt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_stxx_stat_pkt_xmt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
