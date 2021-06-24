<शैली गुरु>
/***********************license start***************
 * Author: Cavium Inc.
 *
 * Contact: support@cavium.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2012 Cavium Inc.
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

#अगर_अघोषित __CVMX_LMCX_DEFS_H__
#घोषणा __CVMX_LMCX_DEFS_H__

#घोषणा CVMX_LMCX_BIST_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800880000F0ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_BIST_RESULT(block_id) (CVMX_ADD_IO_SEG(0x00011800880000F8ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_CHAR_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000220ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_CHAR_MASK0(block_id) (CVMX_ADD_IO_SEG(0x0001180088000228ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_CHAR_MASK1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000230ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_CHAR_MASK2(block_id) (CVMX_ADD_IO_SEG(0x0001180088000238ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_CHAR_MASK3(block_id) (CVMX_ADD_IO_SEG(0x0001180088000240ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_CHAR_MASK4(block_id) (CVMX_ADD_IO_SEG(0x0001180088000318ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_COMP_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000028ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_COMP_CTL2(block_id) (CVMX_ADD_IO_SEG(0x00011800880001B8ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_CONFIG(block_id) (CVMX_ADD_IO_SEG(0x0001180088000188ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_CONTROL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000190ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000010ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_CTL1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000090ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_DCLK_CNT(block_id) (CVMX_ADD_IO_SEG(0x00011800880001E0ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_DCLK_CNT_HI(block_id) (CVMX_ADD_IO_SEG(0x0001180088000070ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_DCLK_CNT_LO(block_id) (CVMX_ADD_IO_SEG(0x0001180088000068ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_DCLK_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800880000B8ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_DDR2_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000018ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_DDR_PLL_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000258ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_DELAY_CFG(block_id) (CVMX_ADD_IO_SEG(0x0001180088000088ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_DIMMX_PARAMS(offset, block_id) (CVMX_ADD_IO_SEG(0x0001180088000270ull) + (((offset) & 1) + ((block_id) & 3) * 0x200000ull) * 8)
#घोषणा CVMX_LMCX_DIMM_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000310ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_DLL_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800880000C0ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_DLL_CTL2(block_id) (CVMX_ADD_IO_SEG(0x00011800880001C8ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_DLL_CTL3(block_id) (CVMX_ADD_IO_SEG(0x0001180088000218ull) + ((block_id) & 3) * 0x1000000ull)
अटल अंतरभूत uपूर्णांक64_t CVMX_LMCX_DUAL_MEMCFG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN50XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN58XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180088000098ull) + (block_id) * 0x60000000ull;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180088000098ull) + (block_id) * 0x60000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180088000098ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180088000098ull) + (block_id) * 0x60000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_LMCX_ECC_SYND(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN30XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN50XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN38XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN58XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180088000038ull) + (block_id) * 0x60000000ull;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180088000038ull) + (block_id) * 0x60000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180088000038ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180088000038ull) + (block_id) * 0x60000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_LMCX_FADR(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN30XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN50XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN38XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN58XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180088000020ull) + (block_id) * 0x60000000ull;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180088000020ull) + (block_id) * 0x60000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180088000020ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180088000020ull) + (block_id) * 0x60000000ull;
पूर्ण

#घोषणा CVMX_LMCX_IFB_CNT(block_id) (CVMX_ADD_IO_SEG(0x00011800880001D0ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_IFB_CNT_HI(block_id) (CVMX_ADD_IO_SEG(0x0001180088000050ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_IFB_CNT_LO(block_id) (CVMX_ADD_IO_SEG(0x0001180088000048ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_INT(block_id) (CVMX_ADD_IO_SEG(0x00011800880001F0ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_INT_EN(block_id) (CVMX_ADD_IO_SEG(0x00011800880001E8ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_MEM_CFG0(block_id) (CVMX_ADD_IO_SEG(0x0001180088000000ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_MEM_CFG1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000008ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_MODEREG_PARAMS0(block_id) (CVMX_ADD_IO_SEG(0x00011800880001A8ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_MODEREG_PARAMS1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000260ull) + ((block_id) & 3) * 0x1000000ull)
अटल अंतरभूत uपूर्णांक64_t CVMX_LMCX_NXM(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN58XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800880000C8ull) + (block_id) * 0x60000000ull;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800880000C8ull) + (block_id) * 0x60000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800880000C8ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800880000C8ull) + (block_id) * 0x60000000ull;
पूर्ण

#घोषणा CVMX_LMCX_OPS_CNT(block_id) (CVMX_ADD_IO_SEG(0x00011800880001D8ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_OPS_CNT_HI(block_id) (CVMX_ADD_IO_SEG(0x0001180088000060ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_OPS_CNT_LO(block_id) (CVMX_ADD_IO_SEG(0x0001180088000058ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_PHY_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000210ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_PLL_BWCTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000040ull))
#घोषणा CVMX_LMCX_PLL_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800880000A8ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_PLL_STATUS(block_id) (CVMX_ADD_IO_SEG(0x00011800880000B0ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_READ_LEVEL_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000140ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_READ_LEVEL_DBG(block_id) (CVMX_ADD_IO_SEG(0x0001180088000148ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_READ_LEVEL_RANKX(offset, block_id) (CVMX_ADD_IO_SEG(0x0001180088000100ull) + (((offset) & 3) + ((block_id) & 1) * 0xC000000ull) * 8)
#घोषणा CVMX_LMCX_RESET_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000180ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_RLEVEL_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800880002A0ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_RLEVEL_DBG(block_id) (CVMX_ADD_IO_SEG(0x00011800880002A8ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_RLEVEL_RANKX(offset, block_id) (CVMX_ADD_IO_SEG(0x0001180088000280ull) + (((offset) & 3) + ((block_id) & 3) * 0x200000ull) * 8)
#घोषणा CVMX_LMCX_RODT_COMP_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800880000A0ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_RODT_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000078ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_RODT_MASK(block_id) (CVMX_ADD_IO_SEG(0x0001180088000268ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_SCRAMBLED_FADR(block_id) (CVMX_ADD_IO_SEG(0x0001180088000330ull))
#घोषणा CVMX_LMCX_SCRAMBLE_CFG0(block_id) (CVMX_ADD_IO_SEG(0x0001180088000320ull))
#घोषणा CVMX_LMCX_SCRAMBLE_CFG1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000328ull))
#घोषणा CVMX_LMCX_SLOT_CTL0(block_id) (CVMX_ADD_IO_SEG(0x00011800880001F8ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_SLOT_CTL1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000200ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_SLOT_CTL2(block_id) (CVMX_ADD_IO_SEG(0x0001180088000208ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_TIMING_PARAMS0(block_id) (CVMX_ADD_IO_SEG(0x0001180088000198ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_TIMING_PARAMS1(block_id) (CVMX_ADD_IO_SEG(0x00011800880001A0ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_TRO_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000248ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_TRO_STAT(block_id) (CVMX_ADD_IO_SEG(0x0001180088000250ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_WLEVEL_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000300ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_WLEVEL_DBG(block_id) (CVMX_ADD_IO_SEG(0x0001180088000308ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_LMCX_WLEVEL_RANKX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800880002B0ull) + (((offset) & 3) + ((block_id) & 3) * 0x200000ull) * 8)
#घोषणा CVMX_LMCX_WODT_CTL0(block_id) (CVMX_ADD_IO_SEG(0x0001180088000030ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_WODT_CTL1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000080ull) + ((block_id) & 1) * 0x60000000ull)
#घोषणा CVMX_LMCX_WODT_MASK(block_id) (CVMX_ADD_IO_SEG(0x00011800880001B0ull) + ((block_id) & 3) * 0x1000000ull)

जोड़ cvmx_lmcx_bist_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_bist_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t start:1;
#अन्यथा
		uपूर्णांक64_t start:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_bist_result अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_bist_result_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t csrd2e:1;
		uपूर्णांक64_t csre2d:1;
		uपूर्णांक64_t mwf:1;
		uपूर्णांक64_t mwd:3;
		uपूर्णांक64_t mwc:1;
		uपूर्णांक64_t mrf:1;
		uपूर्णांक64_t mrd:3;
#अन्यथा
		uपूर्णांक64_t mrd:3;
		uपूर्णांक64_t mrf:1;
		uपूर्णांक64_t mwc:1;
		uपूर्णांक64_t mwd:3;
		uपूर्णांक64_t mwf:1;
		uपूर्णांक64_t csre2d:1;
		uपूर्णांक64_t csrd2e:1;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_bist_result_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t mwf:1;
		uपूर्णांक64_t mwd:3;
		uपूर्णांक64_t mwc:1;
		uपूर्णांक64_t mrf:1;
		uपूर्णांक64_t mrd:3;
#अन्यथा
		uपूर्णांक64_t mrd:3;
		uपूर्णांक64_t mrf:1;
		uपूर्णांक64_t mwc:1;
		uपूर्णांक64_t mwd:3;
		uपूर्णांक64_t mwf:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_lmcx_अक्षर_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_अक्षर_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t dr:1;
		uपूर्णांक64_t skew_on:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t sel:1;
		uपूर्णांक64_t prog:8;
		uपूर्णांक64_t prbs:32;
#अन्यथा
		uपूर्णांक64_t prbs:32;
		uपूर्णांक64_t prog:8;
		uपूर्णांक64_t sel:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t skew_on:1;
		uपूर्णांक64_t dr:1;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_अक्षर_ctl_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_42_63:22;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t sel:1;
		uपूर्णांक64_t prog:8;
		uपूर्णांक64_t prbs:32;
#अन्यथा
		uपूर्णांक64_t prbs:32;
		uपूर्णांक64_t prog:8;
		uपूर्णांक64_t sel:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_42_63:22;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_lmcx_अक्षर_mask0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_अक्षर_mask0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t mask:64;
#अन्यथा
		uपूर्णांक64_t mask:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_अक्षर_mask1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_अक्षर_mask1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t mask:8;
#अन्यथा
		uपूर्णांक64_t mask:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_अक्षर_mask2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_अक्षर_mask2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t mask:64;
#अन्यथा
		uपूर्णांक64_t mask:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_अक्षर_mask3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_अक्षर_mask3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t mask:8;
#अन्यथा
		uपूर्णांक64_t mask:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_अक्षर_mask4 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_अक्षर_mask4_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_33_63:31;
		uपूर्णांक64_t reset_n_mask:1;
		uपूर्णांक64_t a_mask:16;
		uपूर्णांक64_t ba_mask:3;
		uपूर्णांक64_t we_n_mask:1;
		uपूर्णांक64_t cas_n_mask:1;
		uपूर्णांक64_t ras_n_mask:1;
		uपूर्णांक64_t odt1_mask:2;
		uपूर्णांक64_t odt0_mask:2;
		uपूर्णांक64_t cs1_n_mask:2;
		uपूर्णांक64_t cs0_n_mask:2;
		uपूर्णांक64_t cke_mask:2;
#अन्यथा
		uपूर्णांक64_t cke_mask:2;
		uपूर्णांक64_t cs0_n_mask:2;
		uपूर्णांक64_t cs1_n_mask:2;
		uपूर्णांक64_t odt0_mask:2;
		uपूर्णांक64_t odt1_mask:2;
		uपूर्णांक64_t ras_n_mask:1;
		uपूर्णांक64_t cas_n_mask:1;
		uपूर्णांक64_t we_n_mask:1;
		uपूर्णांक64_t ba_mask:3;
		uपूर्णांक64_t a_mask:16;
		uपूर्णांक64_t reset_n_mask:1;
		uपूर्णांक64_t reserved_33_63:31;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_comp_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_comp_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t nctl_csr:4;
		uपूर्णांक64_t nctl_clk:4;
		uपूर्णांक64_t nctl_cmd:4;
		uपूर्णांक64_t nctl_dat:4;
		uपूर्णांक64_t pctl_csr:4;
		uपूर्णांक64_t pctl_clk:4;
		uपूर्णांक64_t reserved_0_7:8;
#अन्यथा
		uपूर्णांक64_t reserved_0_7:8;
		uपूर्णांक64_t pctl_clk:4;
		uपूर्णांक64_t pctl_csr:4;
		uपूर्णांक64_t nctl_dat:4;
		uपूर्णांक64_t nctl_cmd:4;
		uपूर्णांक64_t nctl_clk:4;
		uपूर्णांक64_t nctl_csr:4;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_comp_ctl_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t nctl_csr:4;
		uपूर्णांक64_t nctl_clk:4;
		uपूर्णांक64_t nctl_cmd:4;
		uपूर्णांक64_t nctl_dat:4;
		uपूर्णांक64_t pctl_csr:4;
		uपूर्णांक64_t pctl_clk:4;
		uपूर्णांक64_t pctl_cmd:4;
		uपूर्णांक64_t pctl_dat:4;
#अन्यथा
		uपूर्णांक64_t pctl_dat:4;
		uपूर्णांक64_t pctl_cmd:4;
		uपूर्णांक64_t pctl_clk:4;
		uपूर्णांक64_t pctl_csr:4;
		uपूर्णांक64_t nctl_dat:4;
		uपूर्णांक64_t nctl_cmd:4;
		uपूर्णांक64_t nctl_clk:4;
		uपूर्णांक64_t nctl_csr:4;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_lmcx_comp_ctl_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t nctl_csr:4;
		uपूर्णांक64_t reserved_20_27:8;
		uपूर्णांक64_t nctl_dat:4;
		uपूर्णांक64_t pctl_csr:4;
		uपूर्णांक64_t reserved_5_11:7;
		uपूर्णांक64_t pctl_dat:5;
#अन्यथा
		uपूर्णांक64_t pctl_dat:5;
		uपूर्णांक64_t reserved_5_11:7;
		uपूर्णांक64_t pctl_csr:4;
		uपूर्णांक64_t nctl_dat:4;
		uपूर्णांक64_t reserved_20_27:8;
		uपूर्णांक64_t nctl_csr:4;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_lmcx_comp_ctl_cn58xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t nctl_csr:4;
		uपूर्णांक64_t reserved_20_27:8;
		uपूर्णांक64_t nctl_dat:4;
		uपूर्णांक64_t pctl_csr:4;
		uपूर्णांक64_t reserved_4_11:8;
		uपूर्णांक64_t pctl_dat:4;
#अन्यथा
		uपूर्णांक64_t pctl_dat:4;
		uपूर्णांक64_t reserved_4_11:8;
		uपूर्णांक64_t pctl_csr:4;
		uपूर्णांक64_t nctl_dat:4;
		uपूर्णांक64_t reserved_20_27:8;
		uपूर्णांक64_t nctl_csr:4;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn58xxp1;
पूर्ण;

जोड़ cvmx_lmcx_comp_ctl2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_comp_ctl2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t ddr__ptune:4;
		uपूर्णांक64_t ddr__ntune:4;
		uपूर्णांक64_t m180:1;
		uपूर्णांक64_t byp:1;
		uपूर्णांक64_t ptune:4;
		uपूर्णांक64_t ntune:4;
		uपूर्णांक64_t rodt_ctl:4;
		uपूर्णांक64_t cmd_ctl:4;
		uपूर्णांक64_t ck_ctl:4;
		uपूर्णांक64_t dqx_ctl:4;
#अन्यथा
		uपूर्णांक64_t dqx_ctl:4;
		uपूर्णांक64_t ck_ctl:4;
		uपूर्णांक64_t cmd_ctl:4;
		uपूर्णांक64_t rodt_ctl:4;
		uपूर्णांक64_t ntune:4;
		uपूर्णांक64_t ptune:4;
		uपूर्णांक64_t byp:1;
		uपूर्णांक64_t m180:1;
		uपूर्णांक64_t ddr__ntune:4;
		uपूर्णांक64_t ddr__ptune:4;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_config अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_config_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_61_63:3;
		uपूर्णांक64_t mode32b:1;
		uपूर्णांक64_t scrz:1;
		uपूर्णांक64_t early_unload_d1_r1:1;
		uपूर्णांक64_t early_unload_d1_r0:1;
		uपूर्णांक64_t early_unload_d0_r1:1;
		uपूर्णांक64_t early_unload_d0_r0:1;
		uपूर्णांक64_t init_status:4;
		uपूर्णांक64_t mirrmask:4;
		uपूर्णांक64_t rankmask:4;
		uपूर्णांक64_t rank_ena:1;
		uपूर्णांक64_t sref_with_dll:1;
		uपूर्णांक64_t early_dqx:1;
		uपूर्णांक64_t sequence:3;
		uपूर्णांक64_t ref_zqcs_पूर्णांक:19;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t ecc_adr:1;
		uपूर्णांक64_t क्रमceग_लिखो:4;
		uपूर्णांक64_t idleघातer:3;
		uपूर्णांक64_t pbank_lsb:4;
		uपूर्णांक64_t row_lsb:3;
		uपूर्णांक64_t ecc_ena:1;
		uपूर्णांक64_t init_start:1;
#अन्यथा
		uपूर्णांक64_t init_start:1;
		uपूर्णांक64_t ecc_ena:1;
		uपूर्णांक64_t row_lsb:3;
		uपूर्णांक64_t pbank_lsb:4;
		uपूर्णांक64_t idleघातer:3;
		uपूर्णांक64_t क्रमceग_लिखो:4;
		uपूर्णांक64_t ecc_adr:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t ref_zqcs_पूर्णांक:19;
		uपूर्णांक64_t sequence:3;
		uपूर्णांक64_t early_dqx:1;
		uपूर्णांक64_t sref_with_dll:1;
		uपूर्णांक64_t rank_ena:1;
		uपूर्णांक64_t rankmask:4;
		uपूर्णांक64_t mirrmask:4;
		uपूर्णांक64_t init_status:4;
		uपूर्णांक64_t early_unload_d0_r0:1;
		uपूर्णांक64_t early_unload_d0_r1:1;
		uपूर्णांक64_t early_unload_d1_r0:1;
		uपूर्णांक64_t early_unload_d1_r1:1;
		uपूर्णांक64_t scrz:1;
		uपूर्णांक64_t mode32b:1;
		uपूर्णांक64_t reserved_61_63:3;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_config_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_59_63:5;
		uपूर्णांक64_t early_unload_d1_r1:1;
		uपूर्णांक64_t early_unload_d1_r0:1;
		uपूर्णांक64_t early_unload_d0_r1:1;
		uपूर्णांक64_t early_unload_d0_r0:1;
		uपूर्णांक64_t init_status:4;
		uपूर्णांक64_t mirrmask:4;
		uपूर्णांक64_t rankmask:4;
		uपूर्णांक64_t rank_ena:1;
		uपूर्णांक64_t sref_with_dll:1;
		uपूर्णांक64_t early_dqx:1;
		uपूर्णांक64_t sequence:3;
		uपूर्णांक64_t ref_zqcs_पूर्णांक:19;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t ecc_adr:1;
		uपूर्णांक64_t क्रमceग_लिखो:4;
		uपूर्णांक64_t idleघातer:3;
		uपूर्णांक64_t pbank_lsb:4;
		uपूर्णांक64_t row_lsb:3;
		uपूर्णांक64_t ecc_ena:1;
		uपूर्णांक64_t init_start:1;
#अन्यथा
		uपूर्णांक64_t init_start:1;
		uपूर्णांक64_t ecc_ena:1;
		uपूर्णांक64_t row_lsb:3;
		uपूर्णांक64_t pbank_lsb:4;
		uपूर्णांक64_t idleघातer:3;
		uपूर्णांक64_t क्रमceग_लिखो:4;
		uपूर्णांक64_t ecc_adr:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t ref_zqcs_पूर्णांक:19;
		uपूर्णांक64_t sequence:3;
		uपूर्णांक64_t early_dqx:1;
		uपूर्णांक64_t sref_with_dll:1;
		uपूर्णांक64_t rank_ena:1;
		uपूर्णांक64_t rankmask:4;
		uपूर्णांक64_t mirrmask:4;
		uपूर्णांक64_t init_status:4;
		uपूर्णांक64_t early_unload_d0_r0:1;
		uपूर्णांक64_t early_unload_d0_r1:1;
		uपूर्णांक64_t early_unload_d1_r0:1;
		uपूर्णांक64_t early_unload_d1_r1:1;
		uपूर्णांक64_t reserved_59_63:5;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_lmcx_config_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_55_63:9;
		uपूर्णांक64_t init_status:4;
		uपूर्णांक64_t mirrmask:4;
		uपूर्णांक64_t rankmask:4;
		uपूर्णांक64_t rank_ena:1;
		uपूर्णांक64_t sref_with_dll:1;
		uपूर्णांक64_t early_dqx:1;
		uपूर्णांक64_t sequence:3;
		uपूर्णांक64_t ref_zqcs_पूर्णांक:19;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t ecc_adr:1;
		uपूर्णांक64_t क्रमceग_लिखो:4;
		uपूर्णांक64_t idleघातer:3;
		uपूर्णांक64_t pbank_lsb:4;
		uपूर्णांक64_t row_lsb:3;
		uपूर्णांक64_t ecc_ena:1;
		uपूर्णांक64_t init_start:1;
#अन्यथा
		uपूर्णांक64_t init_start:1;
		uपूर्णांक64_t ecc_ena:1;
		uपूर्णांक64_t row_lsb:3;
		uपूर्णांक64_t pbank_lsb:4;
		uपूर्णांक64_t idleघातer:3;
		uपूर्णांक64_t क्रमceग_लिखो:4;
		uपूर्णांक64_t ecc_adr:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t ref_zqcs_पूर्णांक:19;
		uपूर्णांक64_t sequence:3;
		uपूर्णांक64_t early_dqx:1;
		uपूर्णांक64_t sref_with_dll:1;
		uपूर्णांक64_t rank_ena:1;
		uपूर्णांक64_t rankmask:4;
		uपूर्णांक64_t mirrmask:4;
		uपूर्णांक64_t init_status:4;
		uपूर्णांक64_t reserved_55_63:9;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
	काष्ठा cvmx_lmcx_config_cn66xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_60_63:4;
		uपूर्णांक64_t scrz:1;
		uपूर्णांक64_t early_unload_d1_r1:1;
		uपूर्णांक64_t early_unload_d1_r0:1;
		uपूर्णांक64_t early_unload_d0_r1:1;
		uपूर्णांक64_t early_unload_d0_r0:1;
		uपूर्णांक64_t init_status:4;
		uपूर्णांक64_t mirrmask:4;
		uपूर्णांक64_t rankmask:4;
		uपूर्णांक64_t rank_ena:1;
		uपूर्णांक64_t sref_with_dll:1;
		uपूर्णांक64_t early_dqx:1;
		uपूर्णांक64_t sequence:3;
		uपूर्णांक64_t ref_zqcs_पूर्णांक:19;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t ecc_adr:1;
		uपूर्णांक64_t क्रमceग_लिखो:4;
		uपूर्णांक64_t idleघातer:3;
		uपूर्णांक64_t pbank_lsb:4;
		uपूर्णांक64_t row_lsb:3;
		uपूर्णांक64_t ecc_ena:1;
		uपूर्णांक64_t init_start:1;
#अन्यथा
		uपूर्णांक64_t init_start:1;
		uपूर्णांक64_t ecc_ena:1;
		uपूर्णांक64_t row_lsb:3;
		uपूर्णांक64_t pbank_lsb:4;
		uपूर्णांक64_t idleघातer:3;
		uपूर्णांक64_t क्रमceग_लिखो:4;
		uपूर्णांक64_t ecc_adr:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t ref_zqcs_पूर्णांक:19;
		uपूर्णांक64_t sequence:3;
		uपूर्णांक64_t early_dqx:1;
		uपूर्णांक64_t sref_with_dll:1;
		uपूर्णांक64_t rank_ena:1;
		uपूर्णांक64_t rankmask:4;
		uपूर्णांक64_t mirrmask:4;
		uपूर्णांक64_t init_status:4;
		uपूर्णांक64_t early_unload_d0_r0:1;
		uपूर्णांक64_t early_unload_d0_r1:1;
		uपूर्णांक64_t early_unload_d1_r0:1;
		uपूर्णांक64_t early_unload_d1_r1:1;
		uपूर्णांक64_t scrz:1;
		uपूर्णांक64_t reserved_60_63:4;
#पूर्ण_अगर
	पूर्ण cn66xx;
पूर्ण;

जोड़ cvmx_lmcx_control अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_control_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t scramble_ena:1;
		uपूर्णांक64_t thrcnt:12;
		uपूर्णांक64_t persub:8;
		uपूर्णांक64_t thrmax:4;
		uपूर्णांक64_t crm_cnt:5;
		uपूर्णांक64_t crm_thr:5;
		uपूर्णांक64_t crm_max:5;
		uपूर्णांक64_t rodt_bprch:1;
		uपूर्णांक64_t wodt_bprch:1;
		uपूर्णांक64_t bprch:2;
		uपूर्णांक64_t ext_zqcs_dis:1;
		uपूर्णांक64_t पूर्णांक_zqcs_dis:1;
		uपूर्णांक64_t स्वतः_dclkdis:1;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t nxm_ग_लिखो_en:1;
		uपूर्णांक64_t elev_prio_dis:1;
		uपूर्णांक64_t inorder_wr:1;
		uपूर्णांक64_t inorder_rd:1;
		uपूर्णांक64_t throttle_wr:1;
		uपूर्णांक64_t throttle_rd:1;
		uपूर्णांक64_t fprch2:2;
		uपूर्णांक64_t pocas:1;
		uपूर्णांक64_t ddr2t:1;
		uपूर्णांक64_t bwcnt:1;
		uपूर्णांक64_t rdimm_ena:1;
#अन्यथा
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t bwcnt:1;
		uपूर्णांक64_t ddr2t:1;
		uपूर्णांक64_t pocas:1;
		uपूर्णांक64_t fprch2:2;
		uपूर्णांक64_t throttle_rd:1;
		uपूर्णांक64_t throttle_wr:1;
		uपूर्णांक64_t inorder_rd:1;
		uपूर्णांक64_t inorder_wr:1;
		uपूर्णांक64_t elev_prio_dis:1;
		uपूर्णांक64_t nxm_ग_लिखो_en:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t स्वतः_dclkdis:1;
		uपूर्णांक64_t पूर्णांक_zqcs_dis:1;
		uपूर्णांक64_t ext_zqcs_dis:1;
		uपूर्णांक64_t bprch:2;
		uपूर्णांक64_t wodt_bprch:1;
		uपूर्णांक64_t rodt_bprch:1;
		uपूर्णांक64_t crm_max:5;
		uपूर्णांक64_t crm_thr:5;
		uपूर्णांक64_t crm_cnt:5;
		uपूर्णांक64_t thrmax:4;
		uपूर्णांक64_t persub:8;
		uपूर्णांक64_t thrcnt:12;
		uपूर्णांक64_t scramble_ena:1;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_control_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t rodt_bprch:1;
		uपूर्णांक64_t wodt_bprch:1;
		uपूर्णांक64_t bprch:2;
		uपूर्णांक64_t ext_zqcs_dis:1;
		uपूर्णांक64_t पूर्णांक_zqcs_dis:1;
		uपूर्णांक64_t स्वतः_dclkdis:1;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t nxm_ग_लिखो_en:1;
		uपूर्णांक64_t elev_prio_dis:1;
		uपूर्णांक64_t inorder_wr:1;
		uपूर्णांक64_t inorder_rd:1;
		uपूर्णांक64_t throttle_wr:1;
		uपूर्णांक64_t throttle_rd:1;
		uपूर्णांक64_t fprch2:2;
		uपूर्णांक64_t pocas:1;
		uपूर्णांक64_t ddr2t:1;
		uपूर्णांक64_t bwcnt:1;
		uपूर्णांक64_t rdimm_ena:1;
#अन्यथा
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t bwcnt:1;
		uपूर्णांक64_t ddr2t:1;
		uपूर्णांक64_t pocas:1;
		uपूर्णांक64_t fprch2:2;
		uपूर्णांक64_t throttle_rd:1;
		uपूर्णांक64_t throttle_wr:1;
		uपूर्णांक64_t inorder_rd:1;
		uपूर्णांक64_t inorder_wr:1;
		uपूर्णांक64_t elev_prio_dis:1;
		uपूर्णांक64_t nxm_ग_लिखो_en:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t स्वतः_dclkdis:1;
		uपूर्णांक64_t पूर्णांक_zqcs_dis:1;
		uपूर्णांक64_t ext_zqcs_dis:1;
		uपूर्णांक64_t bprch:2;
		uपूर्णांक64_t wodt_bprch:1;
		uपूर्णांक64_t rodt_bprch:1;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_lmcx_control_cn66xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t scramble_ena:1;
		uपूर्णांक64_t reserved_24_62:39;
		uपूर्णांक64_t rodt_bprch:1;
		uपूर्णांक64_t wodt_bprch:1;
		uपूर्णांक64_t bprch:2;
		uपूर्णांक64_t ext_zqcs_dis:1;
		uपूर्णांक64_t पूर्णांक_zqcs_dis:1;
		uपूर्णांक64_t स्वतः_dclkdis:1;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t nxm_ग_लिखो_en:1;
		uपूर्णांक64_t elev_prio_dis:1;
		uपूर्णांक64_t inorder_wr:1;
		uपूर्णांक64_t inorder_rd:1;
		uपूर्णांक64_t throttle_wr:1;
		uपूर्णांक64_t throttle_rd:1;
		uपूर्णांक64_t fprch2:2;
		uपूर्णांक64_t pocas:1;
		uपूर्णांक64_t ddr2t:1;
		uपूर्णांक64_t bwcnt:1;
		uपूर्णांक64_t rdimm_ena:1;
#अन्यथा
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t bwcnt:1;
		uपूर्णांक64_t ddr2t:1;
		uपूर्णांक64_t pocas:1;
		uपूर्णांक64_t fprch2:2;
		uपूर्णांक64_t throttle_rd:1;
		uपूर्णांक64_t throttle_wr:1;
		uपूर्णांक64_t inorder_rd:1;
		uपूर्णांक64_t inorder_wr:1;
		uपूर्णांक64_t elev_prio_dis:1;
		uपूर्णांक64_t nxm_ग_लिखो_en:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t स्वतः_dclkdis:1;
		uपूर्णांक64_t पूर्णांक_zqcs_dis:1;
		uपूर्णांक64_t ext_zqcs_dis:1;
		uपूर्णांक64_t bprch:2;
		uपूर्णांक64_t wodt_bprch:1;
		uपूर्णांक64_t rodt_bprch:1;
		uपूर्णांक64_t reserved_24_62:39;
		uपूर्णांक64_t scramble_ena:1;
#पूर्ण_अगर
	पूर्ण cn66xx;
	काष्ठा cvmx_lmcx_control_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_63_63:1;
		uपूर्णांक64_t thrcnt:12;
		uपूर्णांक64_t persub:8;
		uपूर्णांक64_t thrmax:4;
		uपूर्णांक64_t crm_cnt:5;
		uपूर्णांक64_t crm_thr:5;
		uपूर्णांक64_t crm_max:5;
		uपूर्णांक64_t rodt_bprch:1;
		uपूर्णांक64_t wodt_bprch:1;
		uपूर्णांक64_t bprch:2;
		uपूर्णांक64_t ext_zqcs_dis:1;
		uपूर्णांक64_t पूर्णांक_zqcs_dis:1;
		uपूर्णांक64_t स्वतः_dclkdis:1;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t nxm_ग_लिखो_en:1;
		uपूर्णांक64_t elev_prio_dis:1;
		uपूर्णांक64_t inorder_wr:1;
		uपूर्णांक64_t inorder_rd:1;
		uपूर्णांक64_t throttle_wr:1;
		uपूर्णांक64_t throttle_rd:1;
		uपूर्णांक64_t fprch2:2;
		uपूर्णांक64_t pocas:1;
		uपूर्णांक64_t ddr2t:1;
		uपूर्णांक64_t bwcnt:1;
		uपूर्णांक64_t rdimm_ena:1;
#अन्यथा
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t bwcnt:1;
		uपूर्णांक64_t ddr2t:1;
		uपूर्णांक64_t pocas:1;
		uपूर्णांक64_t fprch2:2;
		uपूर्णांक64_t throttle_rd:1;
		uपूर्णांक64_t throttle_wr:1;
		uपूर्णांक64_t inorder_rd:1;
		uपूर्णांक64_t inorder_wr:1;
		uपूर्णांक64_t elev_prio_dis:1;
		uपूर्णांक64_t nxm_ग_लिखो_en:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t स्वतः_dclkdis:1;
		uपूर्णांक64_t पूर्णांक_zqcs_dis:1;
		uपूर्णांक64_t ext_zqcs_dis:1;
		uपूर्णांक64_t bprch:2;
		uपूर्णांक64_t wodt_bprch:1;
		uपूर्णांक64_t rodt_bprch:1;
		uपूर्णांक64_t crm_max:5;
		uपूर्णांक64_t crm_thr:5;
		uपूर्णांक64_t crm_cnt:5;
		uपूर्णांक64_t thrmax:4;
		uपूर्णांक64_t persub:8;
		uपूर्णांक64_t thrcnt:12;
		uपूर्णांक64_t reserved_63_63:1;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_lmcx_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t ddr__nctl:4;
		uपूर्णांक64_t ddr__pctl:4;
		uपूर्णांक64_t slow_scf:1;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t pll_भाग2:1;
		uपूर्णांक64_t pll_bypass:1;
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t r2r_slot:1;
		uपूर्णांक64_t inorder_mwf:1;
		uपूर्णांक64_t inorder_mrf:1;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t fprch2:1;
		uपूर्णांक64_t bprch:1;
		uपूर्णांक64_t sil_lat:2;
		uपूर्णांक64_t tskw:2;
		uपूर्णांक64_t qs_dic:2;
		uपूर्णांक64_t dic:2;
#अन्यथा
		uपूर्णांक64_t dic:2;
		uपूर्णांक64_t qs_dic:2;
		uपूर्णांक64_t tskw:2;
		uपूर्णांक64_t sil_lat:2;
		uपूर्णांक64_t bprch:1;
		uपूर्णांक64_t fprch2:1;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t inorder_mrf:1;
		uपूर्णांक64_t inorder_mwf:1;
		uपूर्णांक64_t r2r_slot:1;
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t pll_bypass:1;
		uपूर्णांक64_t pll_भाग2:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t slow_scf:1;
		uपूर्णांक64_t ddr__pctl:4;
		uपूर्णांक64_t ddr__nctl:4;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_ctl_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t ddr__nctl:4;
		uपूर्णांक64_t ddr__pctl:4;
		uपूर्णांक64_t slow_scf:1;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t pll_भाग2:1;
		uपूर्णांक64_t pll_bypass:1;
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t r2r_slot:1;
		uपूर्णांक64_t inorder_mwf:1;
		uपूर्णांक64_t inorder_mrf:1;
		uपूर्णांक64_t dreset:1;
		uपूर्णांक64_t mode32b:1;
		uपूर्णांक64_t fprch2:1;
		uपूर्णांक64_t bprch:1;
		uपूर्णांक64_t sil_lat:2;
		uपूर्णांक64_t tskw:2;
		uपूर्णांक64_t qs_dic:2;
		uपूर्णांक64_t dic:2;
#अन्यथा
		uपूर्णांक64_t dic:2;
		uपूर्णांक64_t qs_dic:2;
		uपूर्णांक64_t tskw:2;
		uपूर्णांक64_t sil_lat:2;
		uपूर्णांक64_t bprch:1;
		uपूर्णांक64_t fprch2:1;
		uपूर्णांक64_t mode32b:1;
		uपूर्णांक64_t dreset:1;
		uपूर्णांक64_t inorder_mrf:1;
		uपूर्णांक64_t inorder_mwf:1;
		uपूर्णांक64_t r2r_slot:1;
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t pll_bypass:1;
		uपूर्णांक64_t pll_भाग2:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t slow_scf:1;
		uपूर्णांक64_t ddr__pctl:4;
		uपूर्णांक64_t ddr__nctl:4;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_lmcx_ctl_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t ddr__nctl:4;
		uपूर्णांक64_t ddr__pctl:4;
		uपूर्णांक64_t slow_scf:1;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t reserved_16_17:2;
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t r2r_slot:1;
		uपूर्णांक64_t inorder_mwf:1;
		uपूर्णांक64_t inorder_mrf:1;
		uपूर्णांक64_t set_zero:1;
		uपूर्णांक64_t mode128b:1;
		uपूर्णांक64_t fprch2:1;
		uपूर्णांक64_t bprch:1;
		uपूर्णांक64_t sil_lat:2;
		uपूर्णांक64_t tskw:2;
		uपूर्णांक64_t qs_dic:2;
		uपूर्णांक64_t dic:2;
#अन्यथा
		uपूर्णांक64_t dic:2;
		uपूर्णांक64_t qs_dic:2;
		uपूर्णांक64_t tskw:2;
		uपूर्णांक64_t sil_lat:2;
		uपूर्णांक64_t bprch:1;
		uपूर्णांक64_t fprch2:1;
		uपूर्णांक64_t mode128b:1;
		uपूर्णांक64_t set_zero:1;
		uपूर्णांक64_t inorder_mrf:1;
		uपूर्णांक64_t inorder_mwf:1;
		uपूर्णांक64_t r2r_slot:1;
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t reserved_16_17:2;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t slow_scf:1;
		uपूर्णांक64_t ddr__pctl:4;
		uपूर्णांक64_t ddr__nctl:4;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_lmcx_ctl_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t ddr__nctl:4;
		uपूर्णांक64_t ddr__pctl:4;
		uपूर्णांक64_t slow_scf:1;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t reserved_17_17:1;
		uपूर्णांक64_t pll_bypass:1;
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t r2r_slot:1;
		uपूर्णांक64_t inorder_mwf:1;
		uपूर्णांक64_t inorder_mrf:1;
		uपूर्णांक64_t dreset:1;
		uपूर्णांक64_t mode32b:1;
		uपूर्णांक64_t fprch2:1;
		uपूर्णांक64_t bprch:1;
		uपूर्णांक64_t sil_lat:2;
		uपूर्णांक64_t tskw:2;
		uपूर्णांक64_t qs_dic:2;
		uपूर्णांक64_t dic:2;
#अन्यथा
		uपूर्णांक64_t dic:2;
		uपूर्णांक64_t qs_dic:2;
		uपूर्णांक64_t tskw:2;
		uपूर्णांक64_t sil_lat:2;
		uपूर्णांक64_t bprch:1;
		uपूर्णांक64_t fprch2:1;
		uपूर्णांक64_t mode32b:1;
		uपूर्णांक64_t dreset:1;
		uपूर्णांक64_t inorder_mrf:1;
		uपूर्णांक64_t inorder_mwf:1;
		uपूर्णांक64_t r2r_slot:1;
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t pll_bypass:1;
		uपूर्णांक64_t reserved_17_17:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t slow_scf:1;
		uपूर्णांक64_t ddr__pctl:4;
		uपूर्णांक64_t ddr__nctl:4;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_lmcx_ctl_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t ddr__nctl:4;
		uपूर्णांक64_t ddr__pctl:4;
		uपूर्णांक64_t slow_scf:1;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t reserved_16_17:2;
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t r2r_slot:1;
		uपूर्णांक64_t inorder_mwf:1;
		uपूर्णांक64_t inorder_mrf:1;
		uपूर्णांक64_t dreset:1;
		uपूर्णांक64_t mode32b:1;
		uपूर्णांक64_t fprch2:1;
		uपूर्णांक64_t bprch:1;
		uपूर्णांक64_t sil_lat:2;
		uपूर्णांक64_t tskw:2;
		uपूर्णांक64_t qs_dic:2;
		uपूर्णांक64_t dic:2;
#अन्यथा
		uपूर्णांक64_t dic:2;
		uपूर्णांक64_t qs_dic:2;
		uपूर्णांक64_t tskw:2;
		uपूर्णांक64_t sil_lat:2;
		uपूर्णांक64_t bprch:1;
		uपूर्णांक64_t fprch2:1;
		uपूर्णांक64_t mode32b:1;
		uपूर्णांक64_t dreset:1;
		uपूर्णांक64_t inorder_mrf:1;
		uपूर्णांक64_t inorder_mwf:1;
		uपूर्णांक64_t r2r_slot:1;
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t reserved_16_17:2;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t slow_scf:1;
		uपूर्णांक64_t ddr__pctl:4;
		uपूर्णांक64_t ddr__nctl:4;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_lmcx_ctl_cn58xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t ddr__nctl:4;
		uपूर्णांक64_t ddr__pctl:4;
		uपूर्णांक64_t slow_scf:1;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t reserved_16_17:2;
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t r2r_slot:1;
		uपूर्णांक64_t inorder_mwf:1;
		uपूर्णांक64_t inorder_mrf:1;
		uपूर्णांक64_t dreset:1;
		uपूर्णांक64_t mode128b:1;
		uपूर्णांक64_t fprch2:1;
		uपूर्णांक64_t bprch:1;
		uपूर्णांक64_t sil_lat:2;
		uपूर्णांक64_t tskw:2;
		uपूर्णांक64_t qs_dic:2;
		uपूर्णांक64_t dic:2;
#अन्यथा
		uपूर्णांक64_t dic:2;
		uपूर्णांक64_t qs_dic:2;
		uपूर्णांक64_t tskw:2;
		uपूर्णांक64_t sil_lat:2;
		uपूर्णांक64_t bprch:1;
		uपूर्णांक64_t fprch2:1;
		uपूर्णांक64_t mode128b:1;
		uपूर्णांक64_t dreset:1;
		uपूर्णांक64_t inorder_mrf:1;
		uपूर्णांक64_t inorder_mwf:1;
		uपूर्णांक64_t r2r_slot:1;
		uपूर्णांक64_t rdimm_ena:1;
		uपूर्णांक64_t reserved_16_17:2;
		uपूर्णांक64_t max_ग_लिखो_batch:4;
		uपूर्णांक64_t xor_bank:1;
		uपूर्णांक64_t slow_scf:1;
		uपूर्णांक64_t ddr__pctl:4;
		uपूर्णांक64_t ddr__nctl:4;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn58xx;
पूर्ण;

जोड़ cvmx_lmcx_ctl1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_ctl1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_21_63:43;
		uपूर्णांक64_t ecc_adr:1;
		uपूर्णांक64_t क्रमceग_लिखो:4;
		uपूर्णांक64_t idleघातer:3;
		uपूर्णांक64_t sequence:3;
		uपूर्णांक64_t sil_mode:1;
		uपूर्णांक64_t dcc_enable:1;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t data_layout:2;
#अन्यथा
		uपूर्णांक64_t data_layout:2;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t dcc_enable:1;
		uपूर्णांक64_t sil_mode:1;
		uपूर्णांक64_t sequence:3;
		uपूर्णांक64_t idleघातer:3;
		uपूर्णांक64_t क्रमceग_लिखो:4;
		uपूर्णांक64_t ecc_adr:1;
		uपूर्णांक64_t reserved_21_63:43;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_ctl1_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t data_layout:2;
#अन्यथा
		uपूर्णांक64_t data_layout:2;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_lmcx_ctl1_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t sil_mode:1;
		uपूर्णांक64_t dcc_enable:1;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t data_layout:2;
#अन्यथा
		uपूर्णांक64_t data_layout:2;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t dcc_enable:1;
		uपूर्णांक64_t sil_mode:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_lmcx_ctl1_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_21_63:43;
		uपूर्णांक64_t ecc_adr:1;
		uपूर्णांक64_t क्रमceग_लिखो:4;
		uपूर्णांक64_t idleघातer:3;
		uपूर्णांक64_t sequence:3;
		uपूर्णांक64_t sil_mode:1;
		uपूर्णांक64_t dcc_enable:1;
		uपूर्णांक64_t reserved_0_7:8;
#अन्यथा
		uपूर्णांक64_t reserved_0_7:8;
		uपूर्णांक64_t dcc_enable:1;
		uपूर्णांक64_t sil_mode:1;
		uपूर्णांक64_t sequence:3;
		uपूर्णांक64_t idleघातer:3;
		uपूर्णांक64_t क्रमceग_लिखो:4;
		uपूर्णांक64_t ecc_adr:1;
		uपूर्णांक64_t reserved_21_63:43;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_lmcx_ctl1_cn58xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t sil_mode:1;
		uपूर्णांक64_t dcc_enable:1;
		uपूर्णांक64_t reserved_0_7:8;
#अन्यथा
		uपूर्णांक64_t reserved_0_7:8;
		uपूर्णांक64_t dcc_enable:1;
		uपूर्णांक64_t sil_mode:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn58xx;
पूर्ण;

जोड़ cvmx_lmcx_dclk_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_dclk_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t dclkcnt:64;
#अन्यथा
		uपूर्णांक64_t dclkcnt:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_dclk_cnt_hi अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_dclk_cnt_hi_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t dclkcnt_hi:32;
#अन्यथा
		uपूर्णांक64_t dclkcnt_hi:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_dclk_cnt_lo अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_dclk_cnt_lo_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t dclkcnt_lo:32;
#अन्यथा
		uपूर्णांक64_t dclkcnt_lo:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_dclk_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_dclk_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t off90_ena:1;
		uपूर्णांक64_t dclk90_byp:1;
		uपूर्णांक64_t dclk90_ld:1;
		uपूर्णांक64_t dclk90_vlu:5;
#अन्यथा
		uपूर्णांक64_t dclk90_vlu:5;
		uपूर्णांक64_t dclk90_ld:1;
		uपूर्णांक64_t dclk90_byp:1;
		uपूर्णांक64_t off90_ena:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_ddr2_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_ddr2_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t bank8:1;
		uपूर्णांक64_t burst8:1;
		uपूर्णांक64_t addlat:3;
		uपूर्णांक64_t pocas:1;
		uपूर्णांक64_t bwcnt:1;
		uपूर्णांक64_t twr:3;
		uपूर्णांक64_t silo_hc:1;
		uपूर्णांक64_t ddr_eof:4;
		uपूर्णांक64_t tfaw:5;
		uपूर्णांक64_t crip_mode:1;
		uपूर्णांक64_t ddr2t:1;
		uपूर्णांक64_t odt_ena:1;
		uपूर्णांक64_t qdll_ena:1;
		uपूर्णांक64_t dll90_vlu:5;
		uपूर्णांक64_t dll90_byp:1;
		uपूर्णांक64_t rdqs:1;
		uपूर्णांक64_t ddr2:1;
#अन्यथा
		uपूर्णांक64_t ddr2:1;
		uपूर्णांक64_t rdqs:1;
		uपूर्णांक64_t dll90_byp:1;
		uपूर्णांक64_t dll90_vlu:5;
		uपूर्णांक64_t qdll_ena:1;
		uपूर्णांक64_t odt_ena:1;
		uपूर्णांक64_t ddr2t:1;
		uपूर्णांक64_t crip_mode:1;
		uपूर्णांक64_t tfaw:5;
		uपूर्णांक64_t ddr_eof:4;
		uपूर्णांक64_t silo_hc:1;
		uपूर्णांक64_t twr:3;
		uपूर्णांक64_t bwcnt:1;
		uपूर्णांक64_t pocas:1;
		uपूर्णांक64_t addlat:3;
		uपूर्णांक64_t burst8:1;
		uपूर्णांक64_t bank8:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_ddr2_ctl_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t bank8:1;
		uपूर्णांक64_t burst8:1;
		uपूर्णांक64_t addlat:3;
		uपूर्णांक64_t pocas:1;
		uपूर्णांक64_t bwcnt:1;
		uपूर्णांक64_t twr:3;
		uपूर्णांक64_t silo_hc:1;
		uपूर्णांक64_t ddr_eof:4;
		uपूर्णांक64_t tfaw:5;
		uपूर्णांक64_t crip_mode:1;
		uपूर्णांक64_t ddr2t:1;
		uपूर्णांक64_t odt_ena:1;
		uपूर्णांक64_t qdll_ena:1;
		uपूर्णांक64_t dll90_vlu:5;
		uपूर्णांक64_t dll90_byp:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t ddr2:1;
#अन्यथा
		uपूर्णांक64_t ddr2:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t dll90_byp:1;
		uपूर्णांक64_t dll90_vlu:5;
		uपूर्णांक64_t qdll_ena:1;
		uपूर्णांक64_t odt_ena:1;
		uपूर्णांक64_t ddr2t:1;
		uपूर्णांक64_t crip_mode:1;
		uपूर्णांक64_t tfaw:5;
		uपूर्णांक64_t ddr_eof:4;
		uपूर्णांक64_t silo_hc:1;
		uपूर्णांक64_t twr:3;
		uपूर्णांक64_t bwcnt:1;
		uपूर्णांक64_t pocas:1;
		uपूर्णांक64_t addlat:3;
		uपूर्णांक64_t burst8:1;
		uपूर्णांक64_t bank8:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_lmcx_ddr_pll_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_ddr_pll_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_27_63:37;
		uपूर्णांक64_t jtg_test_mode:1;
		uपूर्णांक64_t dfm_भाग_reset:1;
		uपूर्णांक64_t dfm_ps_en:3;
		uपूर्णांक64_t ddr_भाग_reset:1;
		uपूर्णांक64_t ddr_ps_en:3;
		uपूर्णांक64_t dअगरfamp:4;
		uपूर्णांक64_t cps:3;
		uपूर्णांक64_t cpb:3;
		uपूर्णांक64_t reset_n:1;
		uपूर्णांक64_t clkf:7;
#अन्यथा
		uपूर्णांक64_t clkf:7;
		uपूर्णांक64_t reset_n:1;
		uपूर्णांक64_t cpb:3;
		uपूर्णांक64_t cps:3;
		uपूर्णांक64_t dअगरfamp:4;
		uपूर्णांक64_t ddr_ps_en:3;
		uपूर्णांक64_t ddr_भाग_reset:1;
		uपूर्णांक64_t dfm_ps_en:3;
		uपूर्णांक64_t dfm_भाग_reset:1;
		uपूर्णांक64_t jtg_test_mode:1;
		uपूर्णांक64_t reserved_27_63:37;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_delay_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_delay_cfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_15_63:49;
		uपूर्णांक64_t dq:5;
		uपूर्णांक64_t cmd:5;
		uपूर्णांक64_t clk:5;
#अन्यथा
		uपूर्णांक64_t clk:5;
		uपूर्णांक64_t cmd:5;
		uपूर्णांक64_t dq:5;
		uपूर्णांक64_t reserved_15_63:49;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_delay_cfg_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t dq:4;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t cmd:4;
		uपूर्णांक64_t reserved_4_4:1;
		uपूर्णांक64_t clk:4;
#अन्यथा
		uपूर्णांक64_t clk:4;
		uपूर्णांक64_t reserved_4_4:1;
		uपूर्णांक64_t cmd:4;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t dq:4;
		uपूर्णांक64_t reserved_14_63:50;
#पूर्ण_अगर
	पूर्ण cn38xx;
पूर्ण;

जोड़ cvmx_lmcx_dimmx_params अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_dimmx_params_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t rc15:4;
		uपूर्णांक64_t rc14:4;
		uपूर्णांक64_t rc13:4;
		uपूर्णांक64_t rc12:4;
		uपूर्णांक64_t rc11:4;
		uपूर्णांक64_t rc10:4;
		uपूर्णांक64_t rc9:4;
		uपूर्णांक64_t rc8:4;
		uपूर्णांक64_t rc7:4;
		uपूर्णांक64_t rc6:4;
		uपूर्णांक64_t rc5:4;
		uपूर्णांक64_t rc4:4;
		uपूर्णांक64_t rc3:4;
		uपूर्णांक64_t rc2:4;
		uपूर्णांक64_t rc1:4;
		uपूर्णांक64_t rc0:4;
#अन्यथा
		uपूर्णांक64_t rc0:4;
		uपूर्णांक64_t rc1:4;
		uपूर्णांक64_t rc2:4;
		uपूर्णांक64_t rc3:4;
		uपूर्णांक64_t rc4:4;
		uपूर्णांक64_t rc5:4;
		uपूर्णांक64_t rc6:4;
		uपूर्णांक64_t rc7:4;
		uपूर्णांक64_t rc8:4;
		uपूर्णांक64_t rc9:4;
		uपूर्णांक64_t rc10:4;
		uपूर्णांक64_t rc11:4;
		uपूर्णांक64_t rc12:4;
		uपूर्णांक64_t rc13:4;
		uपूर्णांक64_t rc14:4;
		uपूर्णांक64_t rc15:4;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_dimm_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_dimm_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_46_63:18;
		uपूर्णांक64_t parity:1;
		uपूर्णांक64_t tcws:13;
		uपूर्णांक64_t dimm1_wmask:16;
		uपूर्णांक64_t dimm0_wmask:16;
#अन्यथा
		uपूर्णांक64_t dimm0_wmask:16;
		uपूर्णांक64_t dimm1_wmask:16;
		uपूर्णांक64_t tcws:13;
		uपूर्णांक64_t parity:1;
		uपूर्णांक64_t reserved_46_63:18;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_dll_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_dll_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t dreset:1;
		uपूर्णांक64_t dll90_byp:1;
		uपूर्णांक64_t dll90_ena:1;
		uपूर्णांक64_t dll90_vlu:5;
#अन्यथा
		uपूर्णांक64_t dll90_vlu:5;
		uपूर्णांक64_t dll90_ena:1;
		uपूर्णांक64_t dll90_byp:1;
		uपूर्णांक64_t dreset:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_dll_ctl2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_dll_ctl2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t पूर्णांकf_en:1;
		uपूर्णांक64_t dll_bringup:1;
		uपूर्णांक64_t dreset:1;
		uपूर्णांक64_t quad_dll_ena:1;
		uपूर्णांक64_t byp_sel:4;
		uपूर्णांक64_t byp_setting:8;
#अन्यथा
		uपूर्णांक64_t byp_setting:8;
		uपूर्णांक64_t byp_sel:4;
		uपूर्णांक64_t quad_dll_ena:1;
		uपूर्णांक64_t dreset:1;
		uपूर्णांक64_t dll_bringup:1;
		uपूर्णांक64_t पूर्णांकf_en:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_dll_ctl2_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_15_63:49;
		uपूर्णांक64_t dll_bringup:1;
		uपूर्णांक64_t dreset:1;
		uपूर्णांक64_t quad_dll_ena:1;
		uपूर्णांक64_t byp_sel:4;
		uपूर्णांक64_t byp_setting:8;
#अन्यथा
		uपूर्णांक64_t byp_setting:8;
		uपूर्णांक64_t byp_sel:4;
		uपूर्णांक64_t quad_dll_ena:1;
		uपूर्णांक64_t dreset:1;
		uपूर्णांक64_t dll_bringup:1;
		uपूर्णांक64_t reserved_15_63:49;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_lmcx_dll_ctl3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_dll_ctl3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_41_63:23;
		uपूर्णांक64_t dclk90_fwd:1;
		uपूर्णांक64_t ddr_90_dly_byp:1;
		uपूर्णांक64_t dclk90_recal_dis:1;
		uपूर्णांक64_t dclk90_byp_sel:1;
		uपूर्णांक64_t dclk90_byp_setting:8;
		uपूर्णांक64_t dll_fast:1;
		uपूर्णांक64_t dll90_setting:8;
		uपूर्णांक64_t fine_tune_mode:1;
		uपूर्णांक64_t dll_mode:1;
		uपूर्णांक64_t dll90_byte_sel:4;
		uपूर्णांक64_t offset_ena:1;
		uपूर्णांक64_t load_offset:1;
		uपूर्णांक64_t mode_sel:2;
		uपूर्णांक64_t byte_sel:4;
		uपूर्णांक64_t offset:6;
#अन्यथा
		uपूर्णांक64_t offset:6;
		uपूर्णांक64_t byte_sel:4;
		uपूर्णांक64_t mode_sel:2;
		uपूर्णांक64_t load_offset:1;
		uपूर्णांक64_t offset_ena:1;
		uपूर्णांक64_t dll90_byte_sel:4;
		uपूर्णांक64_t dll_mode:1;
		uपूर्णांक64_t fine_tune_mode:1;
		uपूर्णांक64_t dll90_setting:8;
		uपूर्णांक64_t dll_fast:1;
		uपूर्णांक64_t dclk90_byp_setting:8;
		uपूर्णांक64_t dclk90_byp_sel:1;
		uपूर्णांक64_t dclk90_recal_dis:1;
		uपूर्णांक64_t ddr_90_dly_byp:1;
		uपूर्णांक64_t dclk90_fwd:1;
		uपूर्णांक64_t reserved_41_63:23;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_dll_ctl3_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t dll_fast:1;
		uपूर्णांक64_t dll90_setting:8;
		uपूर्णांक64_t fine_tune_mode:1;
		uपूर्णांक64_t dll_mode:1;
		uपूर्णांक64_t dll90_byte_sel:4;
		uपूर्णांक64_t offset_ena:1;
		uपूर्णांक64_t load_offset:1;
		uपूर्णांक64_t mode_sel:2;
		uपूर्णांक64_t byte_sel:4;
		uपूर्णांक64_t offset:6;
#अन्यथा
		uपूर्णांक64_t offset:6;
		uपूर्णांक64_t byte_sel:4;
		uपूर्णांक64_t mode_sel:2;
		uपूर्णांक64_t load_offset:1;
		uपूर्णांक64_t offset_ena:1;
		uपूर्णांक64_t dll90_byte_sel:4;
		uपूर्णांक64_t dll_mode:1;
		uपूर्णांक64_t fine_tune_mode:1;
		uपूर्णांक64_t dll90_setting:8;
		uपूर्णांक64_t dll_fast:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_lmcx_dual_memcfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_dual_memcfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t bank8:1;
		uपूर्णांक64_t row_lsb:3;
		uपूर्णांक64_t reserved_8_15:8;
		uपूर्णांक64_t cs_mask:8;
#अन्यथा
		uपूर्णांक64_t cs_mask:8;
		uपूर्णांक64_t reserved_8_15:8;
		uपूर्णांक64_t row_lsb:3;
		uपूर्णांक64_t bank8:1;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_dual_memcfg_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_19_63:45;
		uपूर्णांक64_t row_lsb:3;
		uपूर्णांक64_t reserved_8_15:8;
		uपूर्णांक64_t cs_mask:8;
#अन्यथा
		uपूर्णांक64_t cs_mask:8;
		uपूर्णांक64_t reserved_8_15:8;
		uपूर्णांक64_t row_lsb:3;
		uपूर्णांक64_t reserved_19_63:45;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_lmcx_ecc_synd अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_ecc_synd_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t mrdsyn3:8;
		uपूर्णांक64_t mrdsyn2:8;
		uपूर्णांक64_t mrdsyn1:8;
		uपूर्णांक64_t mrdsyn0:8;
#अन्यथा
		uपूर्णांक64_t mrdsyn0:8;
		uपूर्णांक64_t mrdsyn1:8;
		uपूर्णांक64_t mrdsyn2:8;
		uपूर्णांक64_t mrdsyn3:8;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_fadr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_fadr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_fadr_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t fdimm:2;
		uपूर्णांक64_t fbunk:1;
		uपूर्णांक64_t fbank:3;
		uपूर्णांक64_t frow:14;
		uपूर्णांक64_t fcol:12;
#अन्यथा
		uपूर्णांक64_t fcol:12;
		uपूर्णांक64_t frow:14;
		uपूर्णांक64_t fbank:3;
		uपूर्णांक64_t fbunk:1;
		uपूर्णांक64_t fdimm:2;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_lmcx_fadr_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_36_63:28;
		uपूर्णांक64_t fdimm:2;
		uपूर्णांक64_t fbunk:1;
		uपूर्णांक64_t fbank:3;
		uपूर्णांक64_t frow:16;
		uपूर्णांक64_t fcol:14;
#अन्यथा
		uपूर्णांक64_t fcol:14;
		uपूर्णांक64_t frow:16;
		uपूर्णांक64_t fbank:3;
		uपूर्णांक64_t fbunk:1;
		uपूर्णांक64_t fdimm:2;
		uपूर्णांक64_t reserved_36_63:28;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_lmcx_अगरb_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_अगरb_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t अगरbcnt:64;
#अन्यथा
		uपूर्णांक64_t अगरbcnt:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_अगरb_cnt_hi अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_अगरb_cnt_hi_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t अगरbcnt_hi:32;
#अन्यथा
		uपूर्णांक64_t अगरbcnt_hi:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_अगरb_cnt_lo अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_अगरb_cnt_lo_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t अगरbcnt_lo:32;
#अन्यथा
		uपूर्णांक64_t अगरbcnt_lo:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_पूर्णांक_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t ded_err:4;
		uपूर्णांक64_t sec_err:4;
		uपूर्णांक64_t nxm_wr_err:1;
#अन्यथा
		uपूर्णांक64_t nxm_wr_err:1;
		uपूर्णांक64_t sec_err:4;
		uपूर्णांक64_t ded_err:4;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_पूर्णांक_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_पूर्णांक_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t पूर्णांकr_ded_ena:1;
		uपूर्णांक64_t पूर्णांकr_sec_ena:1;
		uपूर्णांक64_t पूर्णांकr_nxm_wr_ena:1;
#अन्यथा
		uपूर्णांक64_t पूर्णांकr_nxm_wr_ena:1;
		uपूर्णांक64_t पूर्णांकr_sec_ena:1;
		uपूर्णांक64_t पूर्णांकr_ded_ena:1;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_mem_cfg0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_mem_cfg0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t silo_qc:1;
		uपूर्णांक64_t bunk_ena:1;
		uपूर्णांक64_t ded_err:4;
		uपूर्णांक64_t sec_err:4;
		uपूर्णांक64_t पूर्णांकr_ded_ena:1;
		uपूर्णांक64_t पूर्णांकr_sec_ena:1;
		uपूर्णांक64_t tcl:4;
		uपूर्णांक64_t ref_पूर्णांक:6;
		uपूर्णांक64_t pbank_lsb:4;
		uपूर्णांक64_t row_lsb:3;
		uपूर्णांक64_t ecc_ena:1;
		uपूर्णांक64_t init_start:1;
#अन्यथा
		uपूर्णांक64_t init_start:1;
		uपूर्णांक64_t ecc_ena:1;
		uपूर्णांक64_t row_lsb:3;
		uपूर्णांक64_t pbank_lsb:4;
		uपूर्णांक64_t ref_पूर्णांक:6;
		uपूर्णांक64_t tcl:4;
		uपूर्णांक64_t पूर्णांकr_sec_ena:1;
		uपूर्णांक64_t पूर्णांकr_ded_ena:1;
		uपूर्णांक64_t sec_err:4;
		uपूर्णांक64_t ded_err:4;
		uपूर्णांक64_t bunk_ena:1;
		uपूर्णांक64_t silo_qc:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_mem_cfg1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_mem_cfg1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t comp_bypass:1;
		uपूर्णांक64_t trrd:3;
		uपूर्णांक64_t caslat:3;
		uपूर्णांक64_t पंचांगrd:3;
		uपूर्णांक64_t trfc:5;
		uपूर्णांक64_t trp:4;
		uपूर्णांक64_t twtr:4;
		uपूर्णांक64_t trcd:4;
		uपूर्णांक64_t tras:5;
#अन्यथा
		uपूर्णांक64_t tras:5;
		uपूर्णांक64_t trcd:4;
		uपूर्णांक64_t twtr:4;
		uपूर्णांक64_t trp:4;
		uपूर्णांक64_t trfc:5;
		uपूर्णांक64_t पंचांगrd:3;
		uपूर्णांक64_t caslat:3;
		uपूर्णांक64_t trrd:3;
		uपूर्णांक64_t comp_bypass:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_mem_cfg1_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_31_63:33;
		uपूर्णांक64_t trrd:3;
		uपूर्णांक64_t caslat:3;
		uपूर्णांक64_t पंचांगrd:3;
		uपूर्णांक64_t trfc:5;
		uपूर्णांक64_t trp:4;
		uपूर्णांक64_t twtr:4;
		uपूर्णांक64_t trcd:4;
		uपूर्णांक64_t tras:5;
#अन्यथा
		uपूर्णांक64_t tras:5;
		uपूर्णांक64_t trcd:4;
		uपूर्णांक64_t twtr:4;
		uपूर्णांक64_t trp:4;
		uपूर्णांक64_t trfc:5;
		uपूर्णांक64_t पंचांगrd:3;
		uपूर्णांक64_t caslat:3;
		uपूर्णांक64_t trrd:3;
		uपूर्णांक64_t reserved_31_63:33;
#पूर्ण_अगर
	पूर्ण cn38xx;
पूर्ण;

जोड़ cvmx_lmcx_modereg_params0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_modereg_params0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t ppd:1;
		uपूर्णांक64_t wrp:3;
		uपूर्णांक64_t dllr:1;
		uपूर्णांक64_t पंचांग:1;
		uपूर्णांक64_t rbt:1;
		uपूर्णांक64_t cl:4;
		uपूर्णांक64_t bl:2;
		uपूर्णांक64_t qoff:1;
		uपूर्णांक64_t tdqs:1;
		uपूर्णांक64_t wlev:1;
		uपूर्णांक64_t al:2;
		uपूर्णांक64_t dll:1;
		uपूर्णांक64_t mpr:1;
		uपूर्णांक64_t mprloc:2;
		uपूर्णांक64_t cwl:3;
#अन्यथा
		uपूर्णांक64_t cwl:3;
		uपूर्णांक64_t mprloc:2;
		uपूर्णांक64_t mpr:1;
		uपूर्णांक64_t dll:1;
		uपूर्णांक64_t al:2;
		uपूर्णांक64_t wlev:1;
		uपूर्णांक64_t tdqs:1;
		uपूर्णांक64_t qoff:1;
		uपूर्णांक64_t bl:2;
		uपूर्णांक64_t cl:4;
		uपूर्णांक64_t rbt:1;
		uपूर्णांक64_t पंचांग:1;
		uपूर्णांक64_t dllr:1;
		uपूर्णांक64_t wrp:3;
		uपूर्णांक64_t ppd:1;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_modereg_params1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_modereg_params1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t rtt_nom_11:3;
		uपूर्णांक64_t dic_11:2;
		uपूर्णांक64_t rtt_wr_11:2;
		uपूर्णांक64_t srt_11:1;
		uपूर्णांक64_t asr_11:1;
		uपूर्णांक64_t pasr_11:3;
		uपूर्णांक64_t rtt_nom_10:3;
		uपूर्णांक64_t dic_10:2;
		uपूर्णांक64_t rtt_wr_10:2;
		uपूर्णांक64_t srt_10:1;
		uपूर्णांक64_t asr_10:1;
		uपूर्णांक64_t pasr_10:3;
		uपूर्णांक64_t rtt_nom_01:3;
		uपूर्णांक64_t dic_01:2;
		uपूर्णांक64_t rtt_wr_01:2;
		uपूर्णांक64_t srt_01:1;
		uपूर्णांक64_t asr_01:1;
		uपूर्णांक64_t pasr_01:3;
		uपूर्णांक64_t rtt_nom_00:3;
		uपूर्णांक64_t dic_00:2;
		uपूर्णांक64_t rtt_wr_00:2;
		uपूर्णांक64_t srt_00:1;
		uपूर्णांक64_t asr_00:1;
		uपूर्णांक64_t pasr_00:3;
#अन्यथा
		uपूर्णांक64_t pasr_00:3;
		uपूर्णांक64_t asr_00:1;
		uपूर्णांक64_t srt_00:1;
		uपूर्णांक64_t rtt_wr_00:2;
		uपूर्णांक64_t dic_00:2;
		uपूर्णांक64_t rtt_nom_00:3;
		uपूर्णांक64_t pasr_01:3;
		uपूर्णांक64_t asr_01:1;
		uपूर्णांक64_t srt_01:1;
		uपूर्णांक64_t rtt_wr_01:2;
		uपूर्णांक64_t dic_01:2;
		uपूर्णांक64_t rtt_nom_01:3;
		uपूर्णांक64_t pasr_10:3;
		uपूर्णांक64_t asr_10:1;
		uपूर्णांक64_t srt_10:1;
		uपूर्णांक64_t rtt_wr_10:2;
		uपूर्णांक64_t dic_10:2;
		uपूर्णांक64_t rtt_nom_10:3;
		uपूर्णांक64_t pasr_11:3;
		uपूर्णांक64_t asr_11:1;
		uपूर्णांक64_t srt_11:1;
		uपूर्णांक64_t rtt_wr_11:2;
		uपूर्णांक64_t dic_11:2;
		uपूर्णांक64_t rtt_nom_11:3;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_nxm अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_nxm_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t mem_msb_d3_r1:4;
		uपूर्णांक64_t mem_msb_d3_r0:4;
		uपूर्णांक64_t mem_msb_d2_r1:4;
		uपूर्णांक64_t mem_msb_d2_r0:4;
		uपूर्णांक64_t mem_msb_d1_r1:4;
		uपूर्णांक64_t mem_msb_d1_r0:4;
		uपूर्णांक64_t mem_msb_d0_r1:4;
		uपूर्णांक64_t mem_msb_d0_r0:4;
		uपूर्णांक64_t cs_mask:8;
#अन्यथा
		uपूर्णांक64_t cs_mask:8;
		uपूर्णांक64_t mem_msb_d0_r0:4;
		uपूर्णांक64_t mem_msb_d0_r1:4;
		uपूर्णांक64_t mem_msb_d1_r0:4;
		uपूर्णांक64_t mem_msb_d1_r1:4;
		uपूर्णांक64_t mem_msb_d2_r0:4;
		uपूर्णांक64_t mem_msb_d2_r1:4;
		uपूर्णांक64_t mem_msb_d3_r0:4;
		uपूर्णांक64_t mem_msb_d3_r1:4;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_nxm_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t cs_mask:8;
#अन्यथा
		uपूर्णांक64_t cs_mask:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_lmcx_ops_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_ops_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t opscnt:64;
#अन्यथा
		uपूर्णांक64_t opscnt:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_ops_cnt_hi अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_ops_cnt_hi_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t opscnt_hi:32;
#अन्यथा
		uपूर्णांक64_t opscnt_hi:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_ops_cnt_lo अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_ops_cnt_lo_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t opscnt_lo:32;
#अन्यथा
		uपूर्णांक64_t opscnt_lo:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_phy_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_phy_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_15_63:49;
		uपूर्णांक64_t rx_always_on:1;
		uपूर्णांक64_t lv_mode:1;
		uपूर्णांक64_t ck_tune1:1;
		uपूर्णांक64_t ck_dlyout1:4;
		uपूर्णांक64_t ck_tune0:1;
		uपूर्णांक64_t ck_dlyout0:4;
		uपूर्णांक64_t loopback:1;
		uपूर्णांक64_t loopback_pos:1;
		uपूर्णांक64_t ts_stagger:1;
#अन्यथा
		uपूर्णांक64_t ts_stagger:1;
		uपूर्णांक64_t loopback_pos:1;
		uपूर्णांक64_t loopback:1;
		uपूर्णांक64_t ck_dlyout0:4;
		uपूर्णांक64_t ck_tune0:1;
		uपूर्णांक64_t ck_dlyout1:4;
		uपूर्णांक64_t ck_tune1:1;
		uपूर्णांक64_t lv_mode:1;
		uपूर्णांक64_t rx_always_on:1;
		uपूर्णांक64_t reserved_15_63:49;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_phy_ctl_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t lv_mode:1;
		uपूर्णांक64_t ck_tune1:1;
		uपूर्णांक64_t ck_dlyout1:4;
		uपूर्णांक64_t ck_tune0:1;
		uपूर्णांक64_t ck_dlyout0:4;
		uपूर्णांक64_t loopback:1;
		uपूर्णांक64_t loopback_pos:1;
		uपूर्णांक64_t ts_stagger:1;
#अन्यथा
		uपूर्णांक64_t ts_stagger:1;
		uपूर्णांक64_t loopback_pos:1;
		uपूर्णांक64_t loopback:1;
		uपूर्णांक64_t ck_dlyout0:4;
		uपूर्णांक64_t ck_tune0:1;
		uपूर्णांक64_t ck_dlyout1:4;
		uपूर्णांक64_t ck_tune1:1;
		uपूर्णांक64_t lv_mode:1;
		uपूर्णांक64_t reserved_14_63:50;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_lmcx_pll_bwctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_pll_bwctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t bwupd:1;
		uपूर्णांक64_t bwctl:4;
#अन्यथा
		uपूर्णांक64_t bwctl:4;
		uपूर्णांक64_t bwupd:1;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_pll_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_pll_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_30_63:34;
		uपूर्णांक64_t bypass:1;
		uपूर्णांक64_t fasten_n:1;
		uपूर्णांक64_t भाग_reset:1;
		uपूर्णांक64_t reset_n:1;
		uपूर्णांक64_t clkf:12;
		uपूर्णांक64_t clkr:6;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t en16:1;
		uपूर्णांक64_t en12:1;
		uपूर्णांक64_t en8:1;
		uपूर्णांक64_t en6:1;
		uपूर्णांक64_t en4:1;
		uपूर्णांक64_t en2:1;
#अन्यथा
		uपूर्णांक64_t en2:1;
		uपूर्णांक64_t en4:1;
		uपूर्णांक64_t en6:1;
		uपूर्णांक64_t en8:1;
		uपूर्णांक64_t en12:1;
		uपूर्णांक64_t en16:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t clkr:6;
		uपूर्णांक64_t clkf:12;
		uपूर्णांक64_t reset_n:1;
		uपूर्णांक64_t भाग_reset:1;
		uपूर्णांक64_t fasten_n:1;
		uपूर्णांक64_t bypass:1;
		uपूर्णांक64_t reserved_30_63:34;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_pll_ctl_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t fasten_n:1;
		uपूर्णांक64_t भाग_reset:1;
		uपूर्णांक64_t reset_n:1;
		uपूर्णांक64_t clkf:12;
		uपूर्णांक64_t clkr:6;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t en16:1;
		uपूर्णांक64_t en12:1;
		uपूर्णांक64_t en8:1;
		uपूर्णांक64_t en6:1;
		uपूर्णांक64_t en4:1;
		uपूर्णांक64_t en2:1;
#अन्यथा
		uपूर्णांक64_t en2:1;
		uपूर्णांक64_t en4:1;
		uपूर्णांक64_t en6:1;
		uपूर्णांक64_t en8:1;
		uपूर्णांक64_t en12:1;
		uपूर्णांक64_t en16:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t clkr:6;
		uपूर्णांक64_t clkf:12;
		uपूर्णांक64_t reset_n:1;
		uपूर्णांक64_t भाग_reset:1;
		uपूर्णांक64_t fasten_n:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_lmcx_pll_ctl_cn56xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t भाग_reset:1;
		uपूर्णांक64_t reset_n:1;
		uपूर्णांक64_t clkf:12;
		uपूर्णांक64_t clkr:6;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t en16:1;
		uपूर्णांक64_t en12:1;
		uपूर्णांक64_t en8:1;
		uपूर्णांक64_t en6:1;
		uपूर्णांक64_t en4:1;
		uपूर्णांक64_t en2:1;
#अन्यथा
		uपूर्णांक64_t en2:1;
		uपूर्णांक64_t en4:1;
		uपूर्णांक64_t en6:1;
		uपूर्णांक64_t en8:1;
		uपूर्णांक64_t en12:1;
		uपूर्णांक64_t en16:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t clkr:6;
		uपूर्णांक64_t clkf:12;
		uपूर्णांक64_t reset_n:1;
		uपूर्णांक64_t भाग_reset:1;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण cn56xxp1;
पूर्ण;

जोड़ cvmx_lmcx_pll_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_pll_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t ddr__nctl:5;
		uपूर्णांक64_t ddr__pctl:5;
		uपूर्णांक64_t reserved_2_21:20;
		uपूर्णांक64_t rfslip:1;
		uपूर्णांक64_t fbslip:1;
#अन्यथा
		uपूर्णांक64_t fbslip:1;
		uपूर्णांक64_t rfslip:1;
		uपूर्णांक64_t reserved_2_21:20;
		uपूर्णांक64_t ddr__pctl:5;
		uपूर्णांक64_t ddr__nctl:5;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_pll_status_cn58xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t rfslip:1;
		uपूर्णांक64_t fbslip:1;
#अन्यथा
		uपूर्णांक64_t fbslip:1;
		uपूर्णांक64_t rfslip:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण cn58xxp1;
पूर्ण;

जोड़ cvmx_lmcx_पढ़ो_level_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_पढ़ो_level_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t rankmask:4;
		uपूर्णांक64_t pattern:8;
		uपूर्णांक64_t row:16;
		uपूर्णांक64_t col:12;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t bnk:3;
#अन्यथा
		uपूर्णांक64_t bnk:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t col:12;
		uपूर्णांक64_t row:16;
		uपूर्णांक64_t pattern:8;
		uपूर्णांक64_t rankmask:4;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_पढ़ो_level_dbg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_पढ़ो_level_dbg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t biपंचांगask:16;
		uपूर्णांक64_t reserved_4_15:12;
		uपूर्णांक64_t byte:4;
#अन्यथा
		uपूर्णांक64_t byte:4;
		uपूर्णांक64_t reserved_4_15:12;
		uपूर्णांक64_t biपंचांगask:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_पढ़ो_level_rankx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_पढ़ो_level_rankx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_38_63:26;
		uपूर्णांक64_t status:2;
		uपूर्णांक64_t byte8:4;
		uपूर्णांक64_t byte7:4;
		uपूर्णांक64_t byte6:4;
		uपूर्णांक64_t byte5:4;
		uपूर्णांक64_t byte4:4;
		uपूर्णांक64_t byte3:4;
		uपूर्णांक64_t byte2:4;
		uपूर्णांक64_t byte1:4;
		uपूर्णांक64_t byte0:4;
#अन्यथा
		uपूर्णांक64_t byte0:4;
		uपूर्णांक64_t byte1:4;
		uपूर्णांक64_t byte2:4;
		uपूर्णांक64_t byte3:4;
		uपूर्णांक64_t byte4:4;
		uपूर्णांक64_t byte5:4;
		uपूर्णांक64_t byte6:4;
		uपूर्णांक64_t byte7:4;
		uपूर्णांक64_t byte8:4;
		uपूर्णांक64_t status:2;
		uपूर्णांक64_t reserved_38_63:26;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_reset_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_reset_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t ddr3psv:1;
		uपूर्णांक64_t ddr3psoft:1;
		uपूर्णांक64_t ddr3pwarm:1;
		uपूर्णांक64_t ddr3rst:1;
#अन्यथा
		uपूर्णांक64_t ddr3rst:1;
		uपूर्णांक64_t ddr3pwarm:1;
		uपूर्णांक64_t ddr3psoft:1;
		uपूर्णांक64_t ddr3psv:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_rlevel_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_rlevel_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_22_63:42;
		uपूर्णांक64_t delay_unload_3:1;
		uपूर्णांक64_t delay_unload_2:1;
		uपूर्णांक64_t delay_unload_1:1;
		uपूर्णांक64_t delay_unload_0:1;
		uपूर्णांक64_t biपंचांगask:8;
		uपूर्णांक64_t or_dis:1;
		uपूर्णांक64_t offset_en:1;
		uपूर्णांक64_t offset:4;
		uपूर्णांक64_t byte:4;
#अन्यथा
		uपूर्णांक64_t byte:4;
		uपूर्णांक64_t offset:4;
		uपूर्णांक64_t offset_en:1;
		uपूर्णांक64_t or_dis:1;
		uपूर्णांक64_t biपंचांगask:8;
		uपूर्णांक64_t delay_unload_0:1;
		uपूर्णांक64_t delay_unload_1:1;
		uपूर्णांक64_t delay_unload_2:1;
		uपूर्णांक64_t delay_unload_3:1;
		uपूर्णांक64_t reserved_22_63:42;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_rlevel_ctl_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t offset_en:1;
		uपूर्णांक64_t offset:4;
		uपूर्णांक64_t byte:4;
#अन्यथा
		uपूर्णांक64_t byte:4;
		uपूर्णांक64_t offset:4;
		uपूर्णांक64_t offset_en:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_lmcx_rlevel_dbg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_rlevel_dbg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t biपंचांगask:64;
#अन्यथा
		uपूर्णांक64_t biपंचांगask:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_rlevel_rankx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_rlevel_rankx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_56_63:8;
		uपूर्णांक64_t status:2;
		uपूर्णांक64_t byte8:6;
		uपूर्णांक64_t byte7:6;
		uपूर्णांक64_t byte6:6;
		uपूर्णांक64_t byte5:6;
		uपूर्णांक64_t byte4:6;
		uपूर्णांक64_t byte3:6;
		uपूर्णांक64_t byte2:6;
		uपूर्णांक64_t byte1:6;
		uपूर्णांक64_t byte0:6;
#अन्यथा
		uपूर्णांक64_t byte0:6;
		uपूर्णांक64_t byte1:6;
		uपूर्णांक64_t byte2:6;
		uपूर्णांक64_t byte3:6;
		uपूर्णांक64_t byte4:6;
		uपूर्णांक64_t byte5:6;
		uपूर्णांक64_t byte6:6;
		uपूर्णांक64_t byte7:6;
		uपूर्णांक64_t byte8:6;
		uपूर्णांक64_t status:2;
		uपूर्णांक64_t reserved_56_63:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_rodt_comp_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_rodt_comp_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t enable:1;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t nctl:4;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t pctl:5;
#अन्यथा
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t nctl:4;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t enable:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_rodt_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_rodt_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t rodt_hi3:4;
		uपूर्णांक64_t rodt_hi2:4;
		uपूर्णांक64_t rodt_hi1:4;
		uपूर्णांक64_t rodt_hi0:4;
		uपूर्णांक64_t rodt_lo3:4;
		uपूर्णांक64_t rodt_lo2:4;
		uपूर्णांक64_t rodt_lo1:4;
		uपूर्णांक64_t rodt_lo0:4;
#अन्यथा
		uपूर्णांक64_t rodt_lo0:4;
		uपूर्णांक64_t rodt_lo1:4;
		uपूर्णांक64_t rodt_lo2:4;
		uपूर्णांक64_t rodt_lo3:4;
		uपूर्णांक64_t rodt_hi0:4;
		uपूर्णांक64_t rodt_hi1:4;
		uपूर्णांक64_t rodt_hi2:4;
		uपूर्णांक64_t rodt_hi3:4;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_rodt_mask अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_rodt_mask_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t rodt_d3_r1:8;
		uपूर्णांक64_t rodt_d3_r0:8;
		uपूर्णांक64_t rodt_d2_r1:8;
		uपूर्णांक64_t rodt_d2_r0:8;
		uपूर्णांक64_t rodt_d1_r1:8;
		uपूर्णांक64_t rodt_d1_r0:8;
		uपूर्णांक64_t rodt_d0_r1:8;
		uपूर्णांक64_t rodt_d0_r0:8;
#अन्यथा
		uपूर्णांक64_t rodt_d0_r0:8;
		uपूर्णांक64_t rodt_d0_r1:8;
		uपूर्णांक64_t rodt_d1_r0:8;
		uपूर्णांक64_t rodt_d1_r1:8;
		uपूर्णांक64_t rodt_d2_r0:8;
		uपूर्णांक64_t rodt_d2_r1:8;
		uपूर्णांक64_t rodt_d3_r0:8;
		uपूर्णांक64_t rodt_d3_r1:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_scramble_cfg0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_scramble_cfg0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t key:64;
#अन्यथा
		uपूर्णांक64_t key:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_scramble_cfg1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_scramble_cfg1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t key:64;
#अन्यथा
		uपूर्णांक64_t key:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_scrambled_fadr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_scrambled_fadr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_36_63:28;
		uपूर्णांक64_t fdimm:2;
		uपूर्णांक64_t fbunk:1;
		uपूर्णांक64_t fbank:3;
		uपूर्णांक64_t frow:16;
		uपूर्णांक64_t fcol:14;
#अन्यथा
		uपूर्णांक64_t fcol:14;
		uपूर्णांक64_t frow:16;
		uपूर्णांक64_t fbank:3;
		uपूर्णांक64_t fbunk:1;
		uपूर्णांक64_t fdimm:2;
		uपूर्णांक64_t reserved_36_63:28;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_slot_ctl0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_slot_ctl0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t w2w_init:6;
		uपूर्णांक64_t w2r_init:6;
		uपूर्णांक64_t r2w_init:6;
		uपूर्णांक64_t r2r_init:6;
#अन्यथा
		uपूर्णांक64_t r2r_init:6;
		uपूर्णांक64_t r2w_init:6;
		uपूर्णांक64_t w2r_init:6;
		uपूर्णांक64_t w2w_init:6;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_slot_ctl1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_slot_ctl1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t w2w_xrank_init:6;
		uपूर्णांक64_t w2r_xrank_init:6;
		uपूर्णांक64_t r2w_xrank_init:6;
		uपूर्णांक64_t r2r_xrank_init:6;
#अन्यथा
		uपूर्णांक64_t r2r_xrank_init:6;
		uपूर्णांक64_t r2w_xrank_init:6;
		uपूर्णांक64_t w2r_xrank_init:6;
		uपूर्णांक64_t w2w_xrank_init:6;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_slot_ctl2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_slot_ctl2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t w2w_xdimm_init:6;
		uपूर्णांक64_t w2r_xdimm_init:6;
		uपूर्णांक64_t r2w_xdimm_init:6;
		uपूर्णांक64_t r2r_xdimm_init:6;
#अन्यथा
		uपूर्णांक64_t r2r_xdimm_init:6;
		uपूर्णांक64_t r2w_xdimm_init:6;
		uपूर्णांक64_t w2r_xdimm_init:6;
		uपूर्णांक64_t w2w_xdimm_init:6;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_timing_params0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_timing_params0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_47_63:17;
		uपूर्णांक64_t trp_ext:1;
		uपूर्णांक64_t tcksre:4;
		uपूर्णांक64_t trp:4;
		uपूर्णांक64_t tzqinit:4;
		uपूर्णांक64_t tdllk:4;
		uपूर्णांक64_t पंचांगod:4;
		uपूर्णांक64_t पंचांगrd:4;
		uपूर्णांक64_t txpr:4;
		uपूर्णांक64_t tcke:4;
		uपूर्णांक64_t tzqcs:4;
		uपूर्णांक64_t tckeon:10;
#अन्यथा
		uपूर्णांक64_t tckeon:10;
		uपूर्णांक64_t tzqcs:4;
		uपूर्णांक64_t tcke:4;
		uपूर्णांक64_t txpr:4;
		uपूर्णांक64_t पंचांगrd:4;
		uपूर्णांक64_t पंचांगod:4;
		uपूर्णांक64_t tdllk:4;
		uपूर्णांक64_t tzqinit:4;
		uपूर्णांक64_t trp:4;
		uपूर्णांक64_t tcksre:4;
		uपूर्णांक64_t trp_ext:1;
		uपूर्णांक64_t reserved_47_63:17;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_timing_params0_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_47_63:17;
		uपूर्णांक64_t trp_ext:1;
		uपूर्णांक64_t tcksre:4;
		uपूर्णांक64_t trp:4;
		uपूर्णांक64_t tzqinit:4;
		uपूर्णांक64_t tdllk:4;
		uपूर्णांक64_t पंचांगod:4;
		uपूर्णांक64_t पंचांगrd:4;
		uपूर्णांक64_t txpr:4;
		uपूर्णांक64_t tcke:4;
		uपूर्णांक64_t tzqcs:4;
		uपूर्णांक64_t reserved_0_9:10;
#अन्यथा
		uपूर्णांक64_t reserved_0_9:10;
		uपूर्णांक64_t tzqcs:4;
		uपूर्णांक64_t tcke:4;
		uपूर्णांक64_t txpr:4;
		uपूर्णांक64_t पंचांगrd:4;
		uपूर्णांक64_t पंचांगod:4;
		uपूर्णांक64_t tdllk:4;
		uपूर्णांक64_t tzqinit:4;
		uपूर्णांक64_t trp:4;
		uपूर्णांक64_t tcksre:4;
		uपूर्णांक64_t trp_ext:1;
		uपूर्णांक64_t reserved_47_63:17;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_lmcx_timing_params0_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_46_63:18;
		uपूर्णांक64_t tcksre:4;
		uपूर्णांक64_t trp:4;
		uपूर्णांक64_t tzqinit:4;
		uपूर्णांक64_t tdllk:4;
		uपूर्णांक64_t पंचांगod:4;
		uपूर्णांक64_t पंचांगrd:4;
		uपूर्णांक64_t txpr:4;
		uपूर्णांक64_t tcke:4;
		uपूर्णांक64_t tzqcs:4;
		uपूर्णांक64_t tckeon:10;
#अन्यथा
		uपूर्णांक64_t tckeon:10;
		uपूर्णांक64_t tzqcs:4;
		uपूर्णांक64_t tcke:4;
		uपूर्णांक64_t txpr:4;
		uपूर्णांक64_t पंचांगrd:4;
		uपूर्णांक64_t पंचांगod:4;
		uपूर्णांक64_t tdllk:4;
		uपूर्णांक64_t tzqinit:4;
		uपूर्णांक64_t trp:4;
		uपूर्णांक64_t tcksre:4;
		uपूर्णांक64_t reserved_46_63:18;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_lmcx_timing_params1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_timing_params1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_47_63:17;
		uपूर्णांक64_t tras_ext:1;
		uपूर्णांक64_t txpdll:5;
		uपूर्णांक64_t tfaw:5;
		uपूर्णांक64_t twldqsen:4;
		uपूर्णांक64_t twlmrd:4;
		uपूर्णांक64_t txp:3;
		uपूर्णांक64_t trrd:3;
		uपूर्णांक64_t trfc:5;
		uपूर्णांक64_t twtr:4;
		uपूर्णांक64_t trcd:4;
		uपूर्णांक64_t tras:5;
		uपूर्णांक64_t पंचांगprr:4;
#अन्यथा
		uपूर्णांक64_t पंचांगprr:4;
		uपूर्णांक64_t tras:5;
		uपूर्णांक64_t trcd:4;
		uपूर्णांक64_t twtr:4;
		uपूर्णांक64_t trfc:5;
		uपूर्णांक64_t trrd:3;
		uपूर्णांक64_t txp:3;
		uपूर्णांक64_t twlmrd:4;
		uपूर्णांक64_t twldqsen:4;
		uपूर्णांक64_t tfaw:5;
		uपूर्णांक64_t txpdll:5;
		uपूर्णांक64_t tras_ext:1;
		uपूर्णांक64_t reserved_47_63:17;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_timing_params1_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_46_63:18;
		uपूर्णांक64_t txpdll:5;
		uपूर्णांक64_t tfaw:5;
		uपूर्णांक64_t twldqsen:4;
		uपूर्णांक64_t twlmrd:4;
		uपूर्णांक64_t txp:3;
		uपूर्णांक64_t trrd:3;
		uपूर्णांक64_t trfc:5;
		uपूर्णांक64_t twtr:4;
		uपूर्णांक64_t trcd:4;
		uपूर्णांक64_t tras:5;
		uपूर्णांक64_t पंचांगprr:4;
#अन्यथा
		uपूर्णांक64_t पंचांगprr:4;
		uपूर्णांक64_t tras:5;
		uपूर्णांक64_t trcd:4;
		uपूर्णांक64_t twtr:4;
		uपूर्णांक64_t trfc:5;
		uपूर्णांक64_t trrd:3;
		uपूर्णांक64_t txp:3;
		uपूर्णांक64_t twlmrd:4;
		uपूर्णांक64_t twldqsen:4;
		uपूर्णांक64_t tfaw:5;
		uपूर्णांक64_t txpdll:5;
		uपूर्णांक64_t reserved_46_63:18;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_lmcx_tro_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_tro_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_33_63:31;
		uपूर्णांक64_t rclk_cnt:32;
		uपूर्णांक64_t treset:1;
#अन्यथा
		uपूर्णांक64_t treset:1;
		uपूर्णांक64_t rclk_cnt:32;
		uपूर्णांक64_t reserved_33_63:31;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_tro_stat अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_tro_stat_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t ring_cnt:32;
#अन्यथा
		uपूर्णांक64_t ring_cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_wlevel_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_wlevel_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_22_63:42;
		uपूर्णांक64_t rtt_nom:3;
		uपूर्णांक64_t biपंचांगask:8;
		uपूर्णांक64_t or_dis:1;
		uपूर्णांक64_t sset:1;
		uपूर्णांक64_t lanemask:9;
#अन्यथा
		uपूर्णांक64_t lanemask:9;
		uपूर्णांक64_t sset:1;
		uपूर्णांक64_t or_dis:1;
		uपूर्णांक64_t biपंचांगask:8;
		uपूर्णांक64_t rtt_nom:3;
		uपूर्णांक64_t reserved_22_63:42;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_wlevel_ctl_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t sset:1;
		uपूर्णांक64_t lanemask:9;
#अन्यथा
		uपूर्णांक64_t lanemask:9;
		uपूर्णांक64_t sset:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_lmcx_wlevel_dbg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_wlevel_dbg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t biपंचांगask:8;
		uपूर्णांक64_t byte:4;
#अन्यथा
		uपूर्णांक64_t byte:4;
		uपूर्णांक64_t biपंचांगask:8;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_wlevel_rankx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_wlevel_rankx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_47_63:17;
		uपूर्णांक64_t status:2;
		uपूर्णांक64_t byte8:5;
		uपूर्णांक64_t byte7:5;
		uपूर्णांक64_t byte6:5;
		uपूर्णांक64_t byte5:5;
		uपूर्णांक64_t byte4:5;
		uपूर्णांक64_t byte3:5;
		uपूर्णांक64_t byte2:5;
		uपूर्णांक64_t byte1:5;
		uपूर्णांक64_t byte0:5;
#अन्यथा
		uपूर्णांक64_t byte0:5;
		uपूर्णांक64_t byte1:5;
		uपूर्णांक64_t byte2:5;
		uपूर्णांक64_t byte3:5;
		uपूर्णांक64_t byte4:5;
		uपूर्णांक64_t byte5:5;
		uपूर्णांक64_t byte6:5;
		uपूर्णांक64_t byte7:5;
		uपूर्णांक64_t byte8:5;
		uपूर्णांक64_t status:2;
		uपूर्णांक64_t reserved_47_63:17;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_wodt_ctl0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_wodt_ctl0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_lmcx_wodt_ctl0_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t wodt_d1_r1:8;
		uपूर्णांक64_t wodt_d1_r0:8;
		uपूर्णांक64_t wodt_d0_r1:8;
		uपूर्णांक64_t wodt_d0_r0:8;
#अन्यथा
		uपूर्णांक64_t wodt_d0_r0:8;
		uपूर्णांक64_t wodt_d0_r1:8;
		uपूर्णांक64_t wodt_d1_r0:8;
		uपूर्णांक64_t wodt_d1_r1:8;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_lmcx_wodt_ctl0_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t wodt_hi3:4;
		uपूर्णांक64_t wodt_hi2:4;
		uपूर्णांक64_t wodt_hi1:4;
		uपूर्णांक64_t wodt_hi0:4;
		uपूर्णांक64_t wodt_lo3:4;
		uपूर्णांक64_t wodt_lo2:4;
		uपूर्णांक64_t wodt_lo1:4;
		uपूर्णांक64_t wodt_lo0:4;
#अन्यथा
		uपूर्णांक64_t wodt_lo0:4;
		uपूर्णांक64_t wodt_lo1:4;
		uपूर्णांक64_t wodt_lo2:4;
		uपूर्णांक64_t wodt_lo3:4;
		uपूर्णांक64_t wodt_hi0:4;
		uपूर्णांक64_t wodt_hi1:4;
		uपूर्णांक64_t wodt_hi2:4;
		uपूर्णांक64_t wodt_hi3:4;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn38xx;
पूर्ण;

जोड़ cvmx_lmcx_wodt_ctl1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_wodt_ctl1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t wodt_d3_r1:8;
		uपूर्णांक64_t wodt_d3_r0:8;
		uपूर्णांक64_t wodt_d2_r1:8;
		uपूर्णांक64_t wodt_d2_r0:8;
#अन्यथा
		uपूर्णांक64_t wodt_d2_r0:8;
		uपूर्णांक64_t wodt_d2_r1:8;
		uपूर्णांक64_t wodt_d3_r0:8;
		uपूर्णांक64_t wodt_d3_r1:8;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_lmcx_wodt_mask अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_lmcx_wodt_mask_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t wodt_d3_r1:8;
		uपूर्णांक64_t wodt_d3_r0:8;
		uपूर्णांक64_t wodt_d2_r1:8;
		uपूर्णांक64_t wodt_d2_r0:8;
		uपूर्णांक64_t wodt_d1_r1:8;
		uपूर्णांक64_t wodt_d1_r0:8;
		uपूर्णांक64_t wodt_d0_r1:8;
		uपूर्णांक64_t wodt_d0_r0:8;
#अन्यथा
		uपूर्णांक64_t wodt_d0_r0:8;
		uपूर्णांक64_t wodt_d0_r1:8;
		uपूर्णांक64_t wodt_d1_r0:8;
		uपूर्णांक64_t wodt_d1_r1:8;
		uपूर्णांक64_t wodt_d2_r0:8;
		uपूर्णांक64_t wodt_d2_r1:8;
		uपूर्णांक64_t wodt_d3_r0:8;
		uपूर्णांक64_t wodt_d3_r1:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
