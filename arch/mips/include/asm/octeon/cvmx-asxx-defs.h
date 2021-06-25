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

#अगर_अघोषित __CVMX_ASXX_DEFS_H__
#घोषणा __CVMX_ASXX_DEFS_H__

#घोषणा CVMX_ASXX_GMII_RX_CLK_SET(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000180ull))
#घोषणा CVMX_ASXX_GMII_RX_DAT_SET(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000188ull))
#घोषणा CVMX_ASXX_INT_EN(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000018ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_INT_REG(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000010ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_MII_RX_DAT_SET(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000190ull))
#घोषणा CVMX_ASXX_PRT_LOOP(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000040ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RLD_BYPASS(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000248ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RLD_BYPASS_SETTING(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000250ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RLD_COMP(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000220ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RLD_DATA_DRV(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000218ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RLD_FCRAM_MODE(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000210ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RLD_NCTL_STRONG(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000230ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RLD_NCTL_WEAK(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000240ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RLD_PCTL_STRONG(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000228ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RLD_PCTL_WEAK(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000238ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RLD_SETTING(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000258ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RX_CLK_SETX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800B0000020ull) + (((offset) & 3) + ((block_id) & 1) * 0x1000000ull) * 8)
#घोषणा CVMX_ASXX_RX_PRT_EN(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000000ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RX_WOL(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000100ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RX_WOL_MSK(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000108ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RX_WOL_POWOK(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000118ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_RX_WOL_SIG(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000110ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_TX_CLK_SETX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800B0000048ull) + (((offset) & 3) + ((block_id) & 1) * 0x1000000ull) * 8)
#घोषणा CVMX_ASXX_TX_COMP_BYP(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000068ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_ASXX_TX_HI_WATERX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800B0000080ull) + (((offset) & 3) + ((block_id) & 1) * 0x1000000ull) * 8)
#घोषणा CVMX_ASXX_TX_PRT_EN(block_id) (CVMX_ADD_IO_SEG(0x00011800B0000008ull) + ((block_id) & 1) * 0x8000000ull)

व्योम __cvmx_पूर्णांकerrupt_asxx_enable(पूर्णांक block);

जोड़ cvmx_asxx_gmii_rx_clk_set अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_gmii_rx_clk_set_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t setting:5;
#अन्यथा
		uपूर्णांक64_t setting:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_gmii_rx_dat_set अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_gmii_rx_dat_set_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t setting:5;
#अन्यथा
		uपूर्णांक64_t setting:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_पूर्णांक_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_पूर्णांक_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t txpsh:4;
		uपूर्णांक64_t txpop:4;
		uपूर्णांक64_t ovrflw:4;
#अन्यथा
		uपूर्णांक64_t ovrflw:4;
		uपूर्णांक64_t txpop:4;
		uपूर्णांक64_t txpsh:4;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_asxx_पूर्णांक_en_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t txpsh:3;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t txpop:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t ovrflw:3;
#अन्यथा
		uपूर्णांक64_t ovrflw:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t txpop:3;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t txpsh:3;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_asxx_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_पूर्णांक_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t txpsh:4;
		uपूर्णांक64_t txpop:4;
		uपूर्णांक64_t ovrflw:4;
#अन्यथा
		uपूर्णांक64_t ovrflw:4;
		uपूर्णांक64_t txpop:4;
		uपूर्णांक64_t txpsh:4;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_asxx_पूर्णांक_reg_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t txpsh:3;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t txpop:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t ovrflw:3;
#अन्यथा
		uपूर्णांक64_t ovrflw:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t txpop:3;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t txpsh:3;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_asxx_mii_rx_dat_set अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_mii_rx_dat_set_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t setting:5;
#अन्यथा
		uपूर्णांक64_t setting:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_prt_loop अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_prt_loop_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t ext_loop:4;
		uपूर्णांक64_t पूर्णांक_loop:4;
#अन्यथा
		uपूर्णांक64_t पूर्णांक_loop:4;
		uपूर्णांक64_t ext_loop:4;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_asxx_prt_loop_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t ext_loop:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t पूर्णांक_loop:3;
#अन्यथा
		uपूर्णांक64_t पूर्णांक_loop:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t ext_loop:3;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_asxx_rld_bypass अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rld_bypass_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t bypass:1;
#अन्यथा
		uपूर्णांक64_t bypass:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_rld_bypass_setting अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rld_bypass_setting_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t setting:5;
#अन्यथा
		uपूर्णांक64_t setting:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_rld_comp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rld_comp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t nctl:4;
#अन्यथा
		uपूर्णांक64_t nctl:4;
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_asxx_rld_comp_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t pctl:4;
		uपूर्णांक64_t nctl:4;
#अन्यथा
		uपूर्णांक64_t nctl:4;
		uपूर्णांक64_t pctl:4;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण cn38xx;
पूर्ण;

जोड़ cvmx_asxx_rld_data_drv अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rld_data_drv_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t pctl:4;
		uपूर्णांक64_t nctl:4;
#अन्यथा
		uपूर्णांक64_t nctl:4;
		uपूर्णांक64_t pctl:4;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_rld_fcram_mode अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rld_fcram_mode_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t mode:1;
#अन्यथा
		uपूर्णांक64_t mode:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_rld_nctl_strong अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rld_nctl_strong_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t nctl:5;
#अन्यथा
		uपूर्णांक64_t nctl:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_rld_nctl_weak अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rld_nctl_weak_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t nctl:5;
#अन्यथा
		uपूर्णांक64_t nctl:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_rld_pctl_strong अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rld_pctl_strong_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t pctl:5;
#अन्यथा
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_rld_pctl_weak अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rld_pctl_weak_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t pctl:5;
#अन्यथा
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_rld_setting अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rld_setting_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t dfaset:5;
		uपूर्णांक64_t dfalag:1;
		uपूर्णांक64_t dfalead:1;
		uपूर्णांक64_t dfalock:1;
		uपूर्णांक64_t setting:5;
#अन्यथा
		uपूर्णांक64_t setting:5;
		uपूर्णांक64_t dfalock:1;
		uपूर्णांक64_t dfalead:1;
		uपूर्णांक64_t dfalag:1;
		uपूर्णांक64_t dfaset:5;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_asxx_rld_setting_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t setting:5;
#अन्यथा
		uपूर्णांक64_t setting:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण cn38xx;
पूर्ण;

जोड़ cvmx_asxx_rx_clk_setx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rx_clk_setx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t setting:5;
#अन्यथा
		uपूर्णांक64_t setting:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_rx_prt_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rx_prt_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t prt_en:4;
#अन्यथा
		uपूर्णांक64_t prt_en:4;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_asxx_rx_prt_en_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t prt_en:3;
#अन्यथा
		uपूर्णांक64_t prt_en:3;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_asxx_rx_wol अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rx_wol_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t status:1;
		uपूर्णांक64_t enable:1;
#अन्यथा
		uपूर्णांक64_t enable:1;
		uपूर्णांक64_t status:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_rx_wol_msk अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rx_wol_msk_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t msk:64;
#अन्यथा
		uपूर्णांक64_t msk:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_rx_wol_घातok अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rx_wol_घातok_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t घातerok:1;
#अन्यथा
		uपूर्णांक64_t घातerok:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_rx_wol_sig अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_rx_wol_sig_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t sig:32;
#अन्यथा
		uपूर्णांक64_t sig:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_tx_clk_setx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_tx_clk_setx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t setting:5;
#अन्यथा
		uपूर्णांक64_t setting:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_asxx_tx_comp_byp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_tx_comp_byp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_asxx_tx_comp_byp_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t bypass:1;
		uपूर्णांक64_t pctl:4;
		uपूर्णांक64_t nctl:4;
#अन्यथा
		uपूर्णांक64_t nctl:4;
		uपूर्णांक64_t pctl:4;
		uपूर्णांक64_t bypass:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_asxx_tx_comp_byp_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t pctl:4;
		uपूर्णांक64_t nctl:4;
#अन्यथा
		uपूर्णांक64_t nctl:4;
		uपूर्णांक64_t pctl:4;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_asxx_tx_comp_byp_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t bypass:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t nctl:5;
#अन्यथा
		uपूर्णांक64_t nctl:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t bypass:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_asxx_tx_comp_byp_cn58xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t nctl:5;
#अन्यथा
		uपूर्णांक64_t nctl:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण cn58xx;
पूर्ण;

जोड़ cvmx_asxx_tx_hi_waterx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_tx_hi_waterx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t mark:4;
#अन्यथा
		uपूर्णांक64_t mark:4;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_asxx_tx_hi_waterx_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t mark:3;
#अन्यथा
		uपूर्णांक64_t mark:3;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_asxx_tx_prt_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_asxx_tx_prt_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t prt_en:4;
#अन्यथा
		uपूर्णांक64_t prt_en:4;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_asxx_tx_prt_en_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t prt_en:3;
#अन्यथा
		uपूर्णांक64_t prt_en:3;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

#पूर्ण_अगर
