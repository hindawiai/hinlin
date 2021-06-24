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

#अगर_अघोषित __CVMX_AGL_DEFS_H__
#घोषणा __CVMX_AGL_DEFS_H__

#घोषणा CVMX_AGL_GMX_BAD_REG (CVMX_ADD_IO_SEG(0x00011800E0000518ull))
#घोषणा CVMX_AGL_GMX_BIST (CVMX_ADD_IO_SEG(0x00011800E0000400ull))
#घोषणा CVMX_AGL_GMX_DRV_CTL (CVMX_ADD_IO_SEG(0x00011800E00007F0ull))
#घोषणा CVMX_AGL_GMX_INF_MODE (CVMX_ADD_IO_SEG(0x00011800E00007F8ull))
#घोषणा CVMX_AGL_GMX_PRTX_CFG(offset) (CVMX_ADD_IO_SEG(0x00011800E0000010ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_ADR_CAM0(offset) (CVMX_ADD_IO_SEG(0x00011800E0000180ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_ADR_CAM1(offset) (CVMX_ADD_IO_SEG(0x00011800E0000188ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_ADR_CAM2(offset) (CVMX_ADD_IO_SEG(0x00011800E0000190ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_ADR_CAM3(offset) (CVMX_ADD_IO_SEG(0x00011800E0000198ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_ADR_CAM4(offset) (CVMX_ADD_IO_SEG(0x00011800E00001A0ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_ADR_CAM5(offset) (CVMX_ADD_IO_SEG(0x00011800E00001A8ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_ADR_CAM_EN(offset) (CVMX_ADD_IO_SEG(0x00011800E0000108ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_ADR_CTL(offset) (CVMX_ADD_IO_SEG(0x00011800E0000100ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_DECISION(offset) (CVMX_ADD_IO_SEG(0x00011800E0000040ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_FRM_CHK(offset) (CVMX_ADD_IO_SEG(0x00011800E0000020ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_FRM_CTL(offset) (CVMX_ADD_IO_SEG(0x00011800E0000018ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_FRM_MAX(offset) (CVMX_ADD_IO_SEG(0x00011800E0000030ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_FRM_MIN(offset) (CVMX_ADD_IO_SEG(0x00011800E0000028ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_IFG(offset) (CVMX_ADD_IO_SEG(0x00011800E0000058ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_INT_EN(offset) (CVMX_ADD_IO_SEG(0x00011800E0000008ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_INT_REG(offset) (CVMX_ADD_IO_SEG(0x00011800E0000000ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_JABBER(offset) (CVMX_ADD_IO_SEG(0x00011800E0000038ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_PAUSE_DROP_TIME(offset) (CVMX_ADD_IO_SEG(0x00011800E0000068ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_RX_INBND(offset) (CVMX_ADD_IO_SEG(0x00011800E0000060ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_STATS_CTL(offset) (CVMX_ADD_IO_SEG(0x00011800E0000050ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_STATS_OCTS(offset) (CVMX_ADD_IO_SEG(0x00011800E0000088ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_STATS_OCTS_CTL(offset) (CVMX_ADD_IO_SEG(0x00011800E0000098ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_STATS_OCTS_DMAC(offset) (CVMX_ADD_IO_SEG(0x00011800E00000A8ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_STATS_OCTS_DRP(offset) (CVMX_ADD_IO_SEG(0x00011800E00000B8ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_STATS_PKTS(offset) (CVMX_ADD_IO_SEG(0x00011800E0000080ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_STATS_PKTS_BAD(offset) (CVMX_ADD_IO_SEG(0x00011800E00000C0ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_STATS_PKTS_CTL(offset) (CVMX_ADD_IO_SEG(0x00011800E0000090ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_STATS_PKTS_DMAC(offset) (CVMX_ADD_IO_SEG(0x00011800E00000A0ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_STATS_PKTS_DRP(offset) (CVMX_ADD_IO_SEG(0x00011800E00000B0ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RXX_UDD_SKP(offset) (CVMX_ADD_IO_SEG(0x00011800E0000048ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_RX_BP_DROPX(offset) (CVMX_ADD_IO_SEG(0x00011800E0000420ull) + ((offset) & 1) * 8)
#घोषणा CVMX_AGL_GMX_RX_BP_OFFX(offset) (CVMX_ADD_IO_SEG(0x00011800E0000460ull) + ((offset) & 1) * 8)
#घोषणा CVMX_AGL_GMX_RX_BP_ONX(offset) (CVMX_ADD_IO_SEG(0x00011800E0000440ull) + ((offset) & 1) * 8)
#घोषणा CVMX_AGL_GMX_RX_PRT_INFO (CVMX_ADD_IO_SEG(0x00011800E00004E8ull))
#घोषणा CVMX_AGL_GMX_RX_TX_STATUS (CVMX_ADD_IO_SEG(0x00011800E00007E8ull))
#घोषणा CVMX_AGL_GMX_SMACX(offset) (CVMX_ADD_IO_SEG(0x00011800E0000230ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_STAT_BP (CVMX_ADD_IO_SEG(0x00011800E0000520ull))
#घोषणा CVMX_AGL_GMX_TXX_APPEND(offset) (CVMX_ADD_IO_SEG(0x00011800E0000218ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_CLK(offset) (CVMX_ADD_IO_SEG(0x00011800E0000208ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_CTL(offset) (CVMX_ADD_IO_SEG(0x00011800E0000270ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_MIN_PKT(offset) (CVMX_ADD_IO_SEG(0x00011800E0000240ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_PAUSE_PKT_INTERVAL(offset) (CVMX_ADD_IO_SEG(0x00011800E0000248ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_PAUSE_PKT_TIME(offset) (CVMX_ADD_IO_SEG(0x00011800E0000238ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_PAUSE_TOGO(offset) (CVMX_ADD_IO_SEG(0x00011800E0000258ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_PAUSE_ZERO(offset) (CVMX_ADD_IO_SEG(0x00011800E0000260ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_SOFT_PAUSE(offset) (CVMX_ADD_IO_SEG(0x00011800E0000250ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_STAT0(offset) (CVMX_ADD_IO_SEG(0x00011800E0000280ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_STAT1(offset) (CVMX_ADD_IO_SEG(0x00011800E0000288ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_STAT2(offset) (CVMX_ADD_IO_SEG(0x00011800E0000290ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_STAT3(offset) (CVMX_ADD_IO_SEG(0x00011800E0000298ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_STAT4(offset) (CVMX_ADD_IO_SEG(0x00011800E00002A0ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_STAT5(offset) (CVMX_ADD_IO_SEG(0x00011800E00002A8ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_STAT6(offset) (CVMX_ADD_IO_SEG(0x00011800E00002B0ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_STAT7(offset) (CVMX_ADD_IO_SEG(0x00011800E00002B8ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_STAT8(offset) (CVMX_ADD_IO_SEG(0x00011800E00002C0ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_STAT9(offset) (CVMX_ADD_IO_SEG(0x00011800E00002C8ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_STATS_CTL(offset) (CVMX_ADD_IO_SEG(0x00011800E0000268ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TXX_THRESH(offset) (CVMX_ADD_IO_SEG(0x00011800E0000210ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_AGL_GMX_TX_BP (CVMX_ADD_IO_SEG(0x00011800E00004D0ull))
#घोषणा CVMX_AGL_GMX_TX_COL_ATTEMPT (CVMX_ADD_IO_SEG(0x00011800E0000498ull))
#घोषणा CVMX_AGL_GMX_TX_IFG (CVMX_ADD_IO_SEG(0x00011800E0000488ull))
#घोषणा CVMX_AGL_GMX_TX_INT_EN (CVMX_ADD_IO_SEG(0x00011800E0000508ull))
#घोषणा CVMX_AGL_GMX_TX_INT_REG (CVMX_ADD_IO_SEG(0x00011800E0000500ull))
#घोषणा CVMX_AGL_GMX_TX_JAM (CVMX_ADD_IO_SEG(0x00011800E0000490ull))
#घोषणा CVMX_AGL_GMX_TX_LFSR (CVMX_ADD_IO_SEG(0x00011800E00004F8ull))
#घोषणा CVMX_AGL_GMX_TX_OVR_BP (CVMX_ADD_IO_SEG(0x00011800E00004C8ull))
#घोषणा CVMX_AGL_GMX_TX_PAUSE_PKT_DMAC (CVMX_ADD_IO_SEG(0x00011800E00004A0ull))
#घोषणा CVMX_AGL_GMX_TX_PAUSE_PKT_TYPE (CVMX_ADD_IO_SEG(0x00011800E00004A8ull))
#घोषणा CVMX_AGL_PRTX_CTL(offset) (CVMX_ADD_IO_SEG(0x00011800E0002000ull) + ((offset) & 1) * 8)

जोड़ cvmx_agl_gmx_bad_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_bad_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_38_63:26;
		uपूर्णांक64_t txpsh1:1;
		uपूर्णांक64_t txpop1:1;
		uपूर्णांक64_t ovrflw1:1;
		uपूर्णांक64_t txpsh:1;
		uपूर्णांक64_t txpop:1;
		uपूर्णांक64_t ovrflw:1;
		uपूर्णांक64_t reserved_27_31:5;
		uपूर्णांक64_t statovr:1;
		uपूर्णांक64_t reserved_24_25:2;
		uपूर्णांक64_t loststat:2;
		uपूर्णांक64_t reserved_4_21:18;
		uपूर्णांक64_t out_ovr:2;
		uपूर्णांक64_t reserved_0_1:2;
#अन्यथा
		uपूर्णांक64_t reserved_0_1:2;
		uपूर्णांक64_t out_ovr:2;
		uपूर्णांक64_t reserved_4_21:18;
		uपूर्णांक64_t loststat:2;
		uपूर्णांक64_t reserved_24_25:2;
		uपूर्णांक64_t statovr:1;
		uपूर्णांक64_t reserved_27_31:5;
		uपूर्णांक64_t ovrflw:1;
		uपूर्णांक64_t txpop:1;
		uपूर्णांक64_t txpsh:1;
		uपूर्णांक64_t ovrflw1:1;
		uपूर्णांक64_t txpop1:1;
		uपूर्णांक64_t txpsh1:1;
		uपूर्णांक64_t reserved_38_63:26;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_agl_gmx_bad_reg_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_38_63:26;
		uपूर्णांक64_t txpsh1:1;
		uपूर्णांक64_t txpop1:1;
		uपूर्णांक64_t ovrflw1:1;
		uपूर्णांक64_t txpsh:1;
		uपूर्णांक64_t txpop:1;
		uपूर्णांक64_t ovrflw:1;
		uपूर्णांक64_t reserved_27_31:5;
		uपूर्णांक64_t statovr:1;
		uपूर्णांक64_t reserved_23_25:3;
		uपूर्णांक64_t loststat:1;
		uपूर्णांक64_t reserved_4_21:18;
		uपूर्णांक64_t out_ovr:2;
		uपूर्णांक64_t reserved_0_1:2;
#अन्यथा
		uपूर्णांक64_t reserved_0_1:2;
		uपूर्णांक64_t out_ovr:2;
		uपूर्णांक64_t reserved_4_21:18;
		uपूर्णांक64_t loststat:1;
		uपूर्णांक64_t reserved_23_25:3;
		uपूर्णांक64_t statovr:1;
		uपूर्णांक64_t reserved_27_31:5;
		uपूर्णांक64_t ovrflw:1;
		uपूर्णांक64_t txpop:1;
		uपूर्णांक64_t txpsh:1;
		uपूर्णांक64_t ovrflw1:1;
		uपूर्णांक64_t txpop1:1;
		uपूर्णांक64_t txpsh1:1;
		uपूर्णांक64_t reserved_38_63:26;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_agl_gmx_bad_reg_cn56xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_35_63:29;
		uपूर्णांक64_t txpsh:1;
		uपूर्णांक64_t txpop:1;
		uपूर्णांक64_t ovrflw:1;
		uपूर्णांक64_t reserved_27_31:5;
		uपूर्णांक64_t statovr:1;
		uपूर्णांक64_t reserved_23_25:3;
		uपूर्णांक64_t loststat:1;
		uपूर्णांक64_t reserved_3_21:19;
		uपूर्णांक64_t out_ovr:1;
		uपूर्णांक64_t reserved_0_1:2;
#अन्यथा
		uपूर्णांक64_t reserved_0_1:2;
		uपूर्णांक64_t out_ovr:1;
		uपूर्णांक64_t reserved_3_21:19;
		uपूर्णांक64_t loststat:1;
		uपूर्णांक64_t reserved_23_25:3;
		uपूर्णांक64_t statovr:1;
		uपूर्णांक64_t reserved_27_31:5;
		uपूर्णांक64_t ovrflw:1;
		uपूर्णांक64_t txpop:1;
		uपूर्णांक64_t txpsh:1;
		uपूर्णांक64_t reserved_35_63:29;
#पूर्ण_अगर
	पूर्ण cn56xx;
पूर्ण;

जोड़ cvmx_agl_gmx_bist अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_bist_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t status:25;
#अन्यथा
		uपूर्णांक64_t status:25;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_agl_gmx_bist_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t status:10;
#अन्यथा
		uपूर्णांक64_t status:10;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_agl_gmx_drv_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_drv_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_49_63:15;
		uपूर्णांक64_t byp_en1:1;
		uपूर्णांक64_t reserved_45_47:3;
		uपूर्णांक64_t pctl1:5;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t nctl1:5;
		uपूर्णांक64_t reserved_17_31:15;
		uपूर्णांक64_t byp_en:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t nctl:5;
#अन्यथा
		uपूर्णांक64_t nctl:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t byp_en:1;
		uपूर्णांक64_t reserved_17_31:15;
		uपूर्णांक64_t nctl1:5;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t pctl1:5;
		uपूर्णांक64_t reserved_45_47:3;
		uपूर्णांक64_t byp_en1:1;
		uपूर्णांक64_t reserved_49_63:15;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_agl_gmx_drv_ctl_cn56xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t byp_en:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t nctl:5;
#अन्यथा
		uपूर्णांक64_t nctl:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t byp_en:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण cn56xx;
पूर्ण;

जोड़ cvmx_agl_gmx_inf_mode अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_inf_mode_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_0_0:1;
#अन्यथा
		uपूर्णांक64_t reserved_0_0:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_prtx_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_prtx_cfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t tx_idle:1;
		uपूर्णांक64_t rx_idle:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t speed_msb:1;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t burst:1;
		uपूर्णांक64_t tx_en:1;
		uपूर्णांक64_t rx_en:1;
		uपूर्णांक64_t slotसमय:1;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t speed:1;
		uपूर्णांक64_t en:1;
#अन्यथा
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t speed:1;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t slotसमय:1;
		uपूर्णांक64_t rx_en:1;
		uपूर्णांक64_t tx_en:1;
		uपूर्णांक64_t burst:1;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t speed_msb:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t rx_idle:1;
		uपूर्णांक64_t tx_idle:1;
		uपूर्णांक64_t reserved_14_63:50;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_agl_gmx_prtx_cfg_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t tx_en:1;
		uपूर्णांक64_t rx_en:1;
		uपूर्णांक64_t slotसमय:1;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t speed:1;
		uपूर्णांक64_t en:1;
#अन्यथा
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t speed:1;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t slotसमय:1;
		uपूर्णांक64_t rx_en:1;
		uपूर्णांक64_t tx_en:1;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_adr_cam0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_adr_cam0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t adr:64;
#अन्यथा
		uपूर्णांक64_t adr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_adr_cam1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_adr_cam1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t adr:64;
#अन्यथा
		uपूर्णांक64_t adr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_adr_cam2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_adr_cam2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t adr:64;
#अन्यथा
		uपूर्णांक64_t adr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_adr_cam3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_adr_cam3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t adr:64;
#अन्यथा
		uपूर्णांक64_t adr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_adr_cam4 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_adr_cam4_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t adr:64;
#अन्यथा
		uपूर्णांक64_t adr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_adr_cam5 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_adr_cam5_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t adr:64;
#अन्यथा
		uपूर्णांक64_t adr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_adr_cam_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_adr_cam_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t en:8;
#अन्यथा
		uपूर्णांक64_t en:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_adr_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_adr_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t cam_mode:1;
		uपूर्णांक64_t mcst:2;
		uपूर्णांक64_t bcst:1;
#अन्यथा
		uपूर्णांक64_t bcst:1;
		uपूर्णांक64_t mcst:2;
		uपूर्णांक64_t cam_mode:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_decision अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_decision_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t cnt:5;
#अन्यथा
		uपूर्णांक64_t cnt:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_frm_chk अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_frm_chk_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t minerr:1;
#अन्यथा
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_agl_gmx_rxx_frm_chk_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t minerr:1;
#अन्यथा
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_frm_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_frm_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t ptp_mode:1;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t null_dis:1;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t pre_chk:1;
#अन्यथा
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t null_dis:1;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t ptp_mode:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_agl_gmx_rxx_frm_ctl_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t pre_chk:1;
#अन्यथा
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_frm_max अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_frm_max_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t len:16;
#अन्यथा
		uपूर्णांक64_t len:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_frm_min अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_frm_min_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t len:16;
#अन्यथा
		uपूर्णांक64_t len:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_अगरg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_अगरg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t अगरg:4;
#अन्यथा
		uपूर्णांक64_t अगरg:4;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_पूर्णांक_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_पूर्णांक_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t minerr:1;
#अन्यथा
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_agl_gmx_rxx_पूर्णांक_en_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t minerr:1;
#अन्यथा
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_पूर्णांक_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t minerr:1;
#अन्यथा
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_agl_gmx_rxx_पूर्णांक_reg_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t minerr:1;
#अन्यथा
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_jabber अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_jabber_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t cnt:16;
#अन्यथा
		uपूर्णांक64_t cnt:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_छोड़ो_drop_समय अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_छोड़ो_drop_समय_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t status:16;
#अन्यथा
		uपूर्णांक64_t status:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_rx_inbnd अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_rx_inbnd_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t speed:2;
		uपूर्णांक64_t status:1;
#अन्यथा
		uपूर्णांक64_t status:1;
		uपूर्णांक64_t speed:2;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_stats_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_stats_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t rd_clr:1;
#अन्यथा
		uपूर्णांक64_t rd_clr:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_stats_octs अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_stats_octs_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t cnt:48;
#अन्यथा
		uपूर्णांक64_t cnt:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_stats_octs_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_stats_octs_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t cnt:48;
#अन्यथा
		uपूर्णांक64_t cnt:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_stats_octs_dmac अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_stats_octs_dmac_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t cnt:48;
#अन्यथा
		uपूर्णांक64_t cnt:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_stats_octs_drp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_stats_octs_drp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t cnt:48;
#अन्यथा
		uपूर्णांक64_t cnt:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_stats_pkts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_stats_pkts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_stats_pkts_bad अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_stats_pkts_bad_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_stats_pkts_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_stats_pkts_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_stats_pkts_dmac अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_stats_pkts_dmac_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_stats_pkts_drp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_stats_pkts_drp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rxx_udd_skp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rxx_udd_skp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t fcssel:1;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t len:7;
#अन्यथा
		uपूर्णांक64_t len:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t fcssel:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rx_bp_dropx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rx_bp_dropx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t mark:6;
#अन्यथा
		uपूर्णांक64_t mark:6;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rx_bp_offx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rx_bp_offx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t mark:6;
#अन्यथा
		uपूर्णांक64_t mark:6;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rx_bp_onx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rx_bp_onx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t mark:9;
#अन्यथा
		uपूर्णांक64_t mark:9;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_rx_prt_info अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rx_prt_info_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t drop:2;
		uपूर्णांक64_t reserved_2_15:14;
		uपूर्णांक64_t commit:2;
#अन्यथा
		uपूर्णांक64_t commit:2;
		uपूर्णांक64_t reserved_2_15:14;
		uपूर्णांक64_t drop:2;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_agl_gmx_rx_prt_info_cn56xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t drop:1;
		uपूर्णांक64_t reserved_1_15:15;
		uपूर्णांक64_t commit:1;
#अन्यथा
		uपूर्णांक64_t commit:1;
		uपूर्णांक64_t reserved_1_15:15;
		uपूर्णांक64_t drop:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण cn56xx;
पूर्ण;

जोड़ cvmx_agl_gmx_rx_tx_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_rx_tx_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t tx:2;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t rx:2;
#अन्यथा
		uपूर्णांक64_t rx:2;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t tx:2;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_agl_gmx_rx_tx_status_cn56xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t tx:1;
		uपूर्णांक64_t reserved_1_3:3;
		uपूर्णांक64_t rx:1;
#अन्यथा
		uपूर्णांक64_t rx:1;
		uपूर्णांक64_t reserved_1_3:3;
		uपूर्णांक64_t tx:1;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण cn56xx;
पूर्ण;

जोड़ cvmx_agl_gmx_smacx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_smacx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t smac:48;
#अन्यथा
		uपूर्णांक64_t smac:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_stat_bp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_stat_bp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t bp:1;
		uपूर्णांक64_t cnt:16;
#अन्यथा
		uपूर्णांक64_t cnt:16;
		uपूर्णांक64_t bp:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_append अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_append_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t क्रमce_fcs:1;
		uपूर्णांक64_t fcs:1;
		uपूर्णांक64_t pad:1;
		uपूर्णांक64_t preamble:1;
#अन्यथा
		uपूर्णांक64_t preamble:1;
		uपूर्णांक64_t pad:1;
		uपूर्णांक64_t fcs:1;
		uपूर्णांक64_t क्रमce_fcs:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_clk अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_clk_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t clk_cnt:6;
#अन्यथा
		uपूर्णांक64_t clk_cnt:6;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t xsdef_en:1;
		uपूर्णांक64_t xscol_en:1;
#अन्यथा
		uपूर्णांक64_t xscol_en:1;
		uपूर्णांक64_t xsdef_en:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_min_pkt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_min_pkt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t min_size:8;
#अन्यथा
		uपूर्णांक64_t min_size:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_छोड़ो_pkt_पूर्णांकerval अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_छोड़ो_pkt_पूर्णांकerval_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t पूर्णांकerval:16;
#अन्यथा
		uपूर्णांक64_t पूर्णांकerval:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_छोड़ो_pkt_समय अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_छोड़ो_pkt_समय_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t समय:16;
#अन्यथा
		uपूर्णांक64_t समय:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_छोड़ो_togo अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_छोड़ो_togo_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t समय:16;
#अन्यथा
		uपूर्णांक64_t समय:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_छोड़ो_zero अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_छोड़ो_zero_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t send:1;
#अन्यथा
		uपूर्णांक64_t send:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_soft_छोड़ो अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_soft_छोड़ो_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t समय:16;
#अन्यथा
		uपूर्णांक64_t समय:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_stat0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_stat0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t xsdef:32;
		uपूर्णांक64_t xscol:32;
#अन्यथा
		uपूर्णांक64_t xscol:32;
		uपूर्णांक64_t xsdef:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_stat1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_stat1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t scol:32;
		uपूर्णांक64_t mcol:32;
#अन्यथा
		uपूर्णांक64_t mcol:32;
		uपूर्णांक64_t scol:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_stat2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_stat2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t octs:48;
#अन्यथा
		uपूर्णांक64_t octs:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_stat3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_stat3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t pkts:32;
#अन्यथा
		uपूर्णांक64_t pkts:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_stat4 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_stat4_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t hist1:32;
		uपूर्णांक64_t hist0:32;
#अन्यथा
		uपूर्णांक64_t hist0:32;
		uपूर्णांक64_t hist1:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_stat5 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_stat5_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t hist3:32;
		uपूर्णांक64_t hist2:32;
#अन्यथा
		uपूर्णांक64_t hist2:32;
		uपूर्णांक64_t hist3:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_stat6 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_stat6_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t hist5:32;
		uपूर्णांक64_t hist4:32;
#अन्यथा
		uपूर्णांक64_t hist4:32;
		uपूर्णांक64_t hist5:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_stat7 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_stat7_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t hist7:32;
		uपूर्णांक64_t hist6:32;
#अन्यथा
		uपूर्णांक64_t hist6:32;
		uपूर्णांक64_t hist7:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_stat8 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_stat8_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t mcst:32;
		uपूर्णांक64_t bcst:32;
#अन्यथा
		uपूर्णांक64_t bcst:32;
		uपूर्णांक64_t mcst:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_stat9 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_stat9_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t undflw:32;
		uपूर्णांक64_t ctl:32;
#अन्यथा
		uपूर्णांक64_t ctl:32;
		uपूर्णांक64_t undflw:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_stats_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_stats_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t rd_clr:1;
#अन्यथा
		uपूर्णांक64_t rd_clr:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_txx_thresh अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_txx_thresh_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t cnt:6;
#अन्यथा
		uपूर्णांक64_t cnt:6;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_tx_bp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_tx_bp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t bp:2;
#अन्यथा
		uपूर्णांक64_t bp:2;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_agl_gmx_tx_bp_cn56xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t bp:1;
#अन्यथा
		uपूर्णांक64_t bp:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण cn56xx;
पूर्ण;

जोड़ cvmx_agl_gmx_tx_col_attempt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_tx_col_attempt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t limit:5;
#अन्यथा
		uपूर्णांक64_t limit:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_tx_अगरg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_tx_अगरg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t अगरg2:4;
		uपूर्णांक64_t अगरg1:4;
#अन्यथा
		uपूर्णांक64_t अगरg1:4;
		uपूर्णांक64_t अगरg2:4;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_tx_पूर्णांक_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_tx_पूर्णांक_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_22_63:42;
		uपूर्णांक64_t ptp_lost:2;
		uपूर्णांक64_t reserved_18_19:2;
		uपूर्णांक64_t late_col:2;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t xsdef:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t xscol:2;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t undflw:2;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:2;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t xscol:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t xsdef:2;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t late_col:2;
		uपूर्णांक64_t reserved_18_19:2;
		uपूर्णांक64_t ptp_lost:2;
		uपूर्णांक64_t reserved_22_63:42;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_agl_gmx_tx_पूर्णांक_en_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t late_col:2;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t xsdef:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t xscol:2;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t undflw:2;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:2;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t xscol:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t xsdef:2;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t late_col:2;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_agl_gmx_tx_पूर्णांक_en_cn56xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t late_col:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t xsdef:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t xscol:1;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t undflw:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:1;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t xscol:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t xsdef:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t late_col:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण cn56xx;
पूर्ण;

जोड़ cvmx_agl_gmx_tx_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_tx_पूर्णांक_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_22_63:42;
		uपूर्णांक64_t ptp_lost:2;
		uपूर्णांक64_t reserved_18_19:2;
		uपूर्णांक64_t late_col:2;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t xsdef:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t xscol:2;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t undflw:2;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:2;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t xscol:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t xsdef:2;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t late_col:2;
		uपूर्णांक64_t reserved_18_19:2;
		uपूर्णांक64_t ptp_lost:2;
		uपूर्णांक64_t reserved_22_63:42;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_agl_gmx_tx_पूर्णांक_reg_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t late_col:2;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t xsdef:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t xscol:2;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t undflw:2;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:2;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t xscol:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t xsdef:2;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t late_col:2;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_agl_gmx_tx_पूर्णांक_reg_cn56xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t late_col:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t xsdef:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t xscol:1;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t undflw:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:1;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t xscol:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t xsdef:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t late_col:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण cn56xx;
पूर्ण;

जोड़ cvmx_agl_gmx_tx_jam अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_tx_jam_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t jam:8;
#अन्यथा
		uपूर्णांक64_t jam:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_tx_lfsr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_tx_lfsr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t lfsr:16;
#अन्यथा
		uपूर्णांक64_t lfsr:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_tx_ovr_bp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_tx_ovr_bp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t en:2;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t bp:2;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t ign_full:2;
#अन्यथा
		uपूर्णांक64_t ign_full:2;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t bp:2;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t en:2;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_agl_gmx_tx_ovr_bp_cn56xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t bp:1;
		uपूर्णांक64_t reserved_1_3:3;
		uपूर्णांक64_t ign_full:1;
#अन्यथा
		uपूर्णांक64_t ign_full:1;
		uपूर्णांक64_t reserved_1_3:3;
		uपूर्णांक64_t bp:1;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn56xx;
पूर्ण;

जोड़ cvmx_agl_gmx_tx_छोड़ो_pkt_dmac अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_tx_छोड़ो_pkt_dmac_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t dmac:48;
#अन्यथा
		uपूर्णांक64_t dmac:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_gmx_tx_छोड़ो_pkt_type अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_gmx_tx_छोड़ो_pkt_type_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t type:16;
#अन्यथा
		uपूर्णांक64_t type:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_agl_prtx_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_agl_prtx_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t drv_byp:1;
		uपूर्णांक64_t reserved_62_62:1;
		uपूर्णांक64_t cmp_pctl:6;
		uपूर्णांक64_t reserved_54_55:2;
		uपूर्णांक64_t cmp_nctl:6;
		uपूर्णांक64_t reserved_46_47:2;
		uपूर्णांक64_t drv_pctl:6;
		uपूर्णांक64_t reserved_38_39:2;
		uपूर्णांक64_t drv_nctl:6;
		uपूर्णांक64_t reserved_29_31:3;
		uपूर्णांक64_t clk_set:5;
		uपूर्णांक64_t clkrx_byp:1;
		uपूर्णांक64_t reserved_21_22:2;
		uपूर्णांक64_t clkrx_set:5;
		uपूर्णांक64_t clktx_byp:1;
		uपूर्णांक64_t reserved_13_14:2;
		uपूर्णांक64_t clktx_set:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t dllrst:1;
		uपूर्णांक64_t comp:1;
		uपूर्णांक64_t enable:1;
		uपूर्णांक64_t clkrst:1;
		uपूर्णांक64_t mode:1;
#अन्यथा
		uपूर्णांक64_t mode:1;
		uपूर्णांक64_t clkrst:1;
		uपूर्णांक64_t enable:1;
		uपूर्णांक64_t comp:1;
		uपूर्णांक64_t dllrst:1;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t clktx_set:5;
		uपूर्णांक64_t reserved_13_14:2;
		uपूर्णांक64_t clktx_byp:1;
		uपूर्णांक64_t clkrx_set:5;
		uपूर्णांक64_t reserved_21_22:2;
		uपूर्णांक64_t clkrx_byp:1;
		uपूर्णांक64_t clk_set:5;
		uपूर्णांक64_t reserved_29_31:3;
		uपूर्णांक64_t drv_nctl:6;
		uपूर्णांक64_t reserved_38_39:2;
		uपूर्णांक64_t drv_pctl:6;
		uपूर्णांक64_t reserved_46_47:2;
		uपूर्णांक64_t cmp_nctl:6;
		uपूर्णांक64_t reserved_54_55:2;
		uपूर्णांक64_t cmp_pctl:6;
		uपूर्णांक64_t reserved_62_62:1;
		uपूर्णांक64_t drv_byp:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
