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

#अगर_अघोषित __CVMX_PESCX_DEFS_H__
#घोषणा __CVMX_PESCX_DEFS_H__

#घोषणा CVMX_PESCX_BIST_STATUS(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000018ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_PESCX_BIST_STATUS2(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000418ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_PESCX_CFG_RD(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000030ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_PESCX_CFG_WR(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000028ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_PESCX_CPL_LUT_VALID(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000098ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_PESCX_CTL_STATUS(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000000ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_PESCX_CTL_STATUS2(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000400ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_PESCX_DBG_INFO(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000008ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_PESCX_DBG_INFO_EN(block_id) (CVMX_ADD_IO_SEG(0x00011800C80000A0ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_PESCX_DIAG_STATUS(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000020ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_PESCX_P2N_BAR0_START(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000080ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_PESCX_P2N_BAR1_START(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000088ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_PESCX_P2N_BAR2_START(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000090ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_PESCX_P2P_BARX_END(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800C8000048ull) + (((offset) & 3) + ((block_id) & 1) * 0x800000ull) * 16)
#घोषणा CVMX_PESCX_P2P_BARX_START(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800C8000040ull) + (((offset) & 3) + ((block_id) & 1) * 0x800000ull) * 16)
#घोषणा CVMX_PESCX_TLP_CREDITS(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000038ull) + ((block_id) & 1) * 0x8000000ull)

जोड़ cvmx_pescx_bist_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_bist_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t rqdata5:1;
		uपूर्णांक64_t ctlp_or:1;
		uपूर्णांक64_t ntlp_or:1;
		uपूर्णांक64_t ptlp_or:1;
		uपूर्णांक64_t retry:1;
		uपूर्णांक64_t rqdata0:1;
		uपूर्णांक64_t rqdata1:1;
		uपूर्णांक64_t rqdata2:1;
		uपूर्णांक64_t rqdata3:1;
		uपूर्णांक64_t rqdata4:1;
		uपूर्णांक64_t rqhdr1:1;
		uपूर्णांक64_t rqhdr0:1;
		uपूर्णांक64_t sot:1;
#अन्यथा
		uपूर्णांक64_t sot:1;
		uपूर्णांक64_t rqhdr0:1;
		uपूर्णांक64_t rqhdr1:1;
		uपूर्णांक64_t rqdata4:1;
		uपूर्णांक64_t rqdata3:1;
		uपूर्णांक64_t rqdata2:1;
		uपूर्णांक64_t rqdata1:1;
		uपूर्णांक64_t rqdata0:1;
		uपूर्णांक64_t retry:1;
		uपूर्णांक64_t ptlp_or:1;
		uपूर्णांक64_t ntlp_or:1;
		uपूर्णांक64_t ctlp_or:1;
		uपूर्णांक64_t rqdata5:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pescx_bist_status_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t ctlp_or:1;
		uपूर्णांक64_t ntlp_or:1;
		uपूर्णांक64_t ptlp_or:1;
		uपूर्णांक64_t retry:1;
		uपूर्णांक64_t rqdata0:1;
		uपूर्णांक64_t rqdata1:1;
		uपूर्णांक64_t rqdata2:1;
		uपूर्णांक64_t rqdata3:1;
		uपूर्णांक64_t rqdata4:1;
		uपूर्णांक64_t rqhdr1:1;
		uपूर्णांक64_t rqhdr0:1;
		uपूर्णांक64_t sot:1;
#अन्यथा
		uपूर्णांक64_t sot:1;
		uपूर्णांक64_t rqhdr0:1;
		uपूर्णांक64_t rqhdr1:1;
		uपूर्णांक64_t rqdata4:1;
		uपूर्णांक64_t rqdata3:1;
		uपूर्णांक64_t rqdata2:1;
		uपूर्णांक64_t rqdata1:1;
		uपूर्णांक64_t rqdata0:1;
		uपूर्णांक64_t retry:1;
		uपूर्णांक64_t ptlp_or:1;
		uपूर्णांक64_t ntlp_or:1;
		uपूर्णांक64_t ctlp_or:1;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
पूर्ण;

जोड़ cvmx_pescx_bist_status2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_bist_status2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t cto_p2e:1;
		uपूर्णांक64_t e2p_cpl:1;
		uपूर्णांक64_t e2p_n:1;
		uपूर्णांक64_t e2p_p:1;
		uपूर्णांक64_t e2p_rsl:1;
		uपूर्णांक64_t dbg_p2e:1;
		uपूर्णांक64_t peai_p2e:1;
		uपूर्णांक64_t rsl_p2e:1;
		uपूर्णांक64_t pef_tpf1:1;
		uपूर्णांक64_t pef_tpf0:1;
		uपूर्णांक64_t pef_tnf:1;
		uपूर्णांक64_t pef_tcf1:1;
		uपूर्णांक64_t pef_tc0:1;
		uपूर्णांक64_t ppf:1;
#अन्यथा
		uपूर्णांक64_t ppf:1;
		uपूर्णांक64_t pef_tc0:1;
		uपूर्णांक64_t pef_tcf1:1;
		uपूर्णांक64_t pef_tnf:1;
		uपूर्णांक64_t pef_tpf0:1;
		uपूर्णांक64_t pef_tpf1:1;
		uपूर्णांक64_t rsl_p2e:1;
		uपूर्णांक64_t peai_p2e:1;
		uपूर्णांक64_t dbg_p2e:1;
		uपूर्णांक64_t e2p_rsl:1;
		uपूर्णांक64_t e2p_p:1;
		uपूर्णांक64_t e2p_n:1;
		uपूर्णांक64_t e2p_cpl:1;
		uपूर्णांक64_t cto_p2e:1;
		uपूर्णांक64_t reserved_14_63:50;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pescx_cfg_rd अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_cfg_rd_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t data:32;
		uपूर्णांक64_t addr:32;
#अन्यथा
		uपूर्णांक64_t addr:32;
		uपूर्णांक64_t data:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pescx_cfg_wr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_cfg_wr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t data:32;
		uपूर्णांक64_t addr:32;
#अन्यथा
		uपूर्णांक64_t addr:32;
		uपूर्णांक64_t data:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pescx_cpl_lut_valid अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_cpl_lut_valid_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t tag:32;
#अन्यथा
		uपूर्णांक64_t tag:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pescx_ctl_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_ctl_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t dnum:5;
		uपूर्णांक64_t pbus:8;
		uपूर्णांक64_t qlm_cfg:2;
		uपूर्णांक64_t lane_swp:1;
		uपूर्णांक64_t pm_xtoff:1;
		uपूर्णांक64_t pm_xpme:1;
		uपूर्णांक64_t ob_p_cmd:1;
		uपूर्णांक64_t reserved_7_8:2;
		uपूर्णांक64_t nf_ecrc:1;
		uपूर्णांक64_t dly_one:1;
		uपूर्णांक64_t lnk_enb:1;
		uपूर्णांक64_t ro_ctlp:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t inv_ecrc:1;
		uपूर्णांक64_t inv_lcrc:1;
#अन्यथा
		uपूर्णांक64_t inv_lcrc:1;
		uपूर्णांक64_t inv_ecrc:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t ro_ctlp:1;
		uपूर्णांक64_t lnk_enb:1;
		uपूर्णांक64_t dly_one:1;
		uपूर्णांक64_t nf_ecrc:1;
		uपूर्णांक64_t reserved_7_8:2;
		uपूर्णांक64_t ob_p_cmd:1;
		uपूर्णांक64_t pm_xpme:1;
		uपूर्णांक64_t pm_xtoff:1;
		uपूर्णांक64_t lane_swp:1;
		uपूर्णांक64_t qlm_cfg:2;
		uपूर्णांक64_t pbus:8;
		uपूर्णांक64_t dnum:5;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pescx_ctl_status_cn56xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t dnum:5;
		uपूर्णांक64_t pbus:8;
		uपूर्णांक64_t qlm_cfg:2;
		uपूर्णांक64_t reserved_12_12:1;
		uपूर्णांक64_t pm_xtoff:1;
		uपूर्णांक64_t pm_xpme:1;
		uपूर्णांक64_t ob_p_cmd:1;
		uपूर्णांक64_t reserved_7_8:2;
		uपूर्णांक64_t nf_ecrc:1;
		uपूर्णांक64_t dly_one:1;
		uपूर्णांक64_t lnk_enb:1;
		uपूर्णांक64_t ro_ctlp:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t inv_ecrc:1;
		uपूर्णांक64_t inv_lcrc:1;
#अन्यथा
		uपूर्णांक64_t inv_lcrc:1;
		uपूर्णांक64_t inv_ecrc:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t ro_ctlp:1;
		uपूर्णांक64_t lnk_enb:1;
		uपूर्णांक64_t dly_one:1;
		uपूर्णांक64_t nf_ecrc:1;
		uपूर्णांक64_t reserved_7_8:2;
		uपूर्णांक64_t ob_p_cmd:1;
		uपूर्णांक64_t pm_xpme:1;
		uपूर्णांक64_t pm_xtoff:1;
		uपूर्णांक64_t reserved_12_12:1;
		uपूर्णांक64_t qlm_cfg:2;
		uपूर्णांक64_t pbus:8;
		uपूर्णांक64_t dnum:5;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण cn56xx;
पूर्ण;

जोड़ cvmx_pescx_ctl_status2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_ctl_status2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t pclk_run:1;
		uपूर्णांक64_t pcierst:1;
#अन्यथा
		uपूर्णांक64_t pcierst:1;
		uपूर्णांक64_t pclk_run:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pescx_ctl_status2_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t pcierst:1;
#अन्यथा
		uपूर्णांक64_t pcierst:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
पूर्ण;

जोड़ cvmx_pescx_dbg_info अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_dbg_info_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_31_63:33;
		uपूर्णांक64_t ecrc_e:1;
		uपूर्णांक64_t rawwpp:1;
		uपूर्णांक64_t racpp:1;
		uपूर्णांक64_t ramtlp:1;
		uपूर्णांक64_t rarwdns:1;
		uपूर्णांक64_t caar:1;
		uपूर्णांक64_t racca:1;
		uपूर्णांक64_t racur:1;
		uपूर्णांक64_t rauc:1;
		uपूर्णांक64_t rqo:1;
		uपूर्णांक64_t fcuv:1;
		uपूर्णांक64_t rpe:1;
		uपूर्णांक64_t fcpvwt:1;
		uपूर्णांक64_t dpeoosd:1;
		uपूर्णांक64_t rtwdle:1;
		uपूर्णांक64_t rdwdle:1;
		uपूर्णांक64_t mre:1;
		uपूर्णांक64_t rte:1;
		uपूर्णांक64_t acto:1;
		uपूर्णांक64_t rvdm:1;
		uपूर्णांक64_t rumep:1;
		uपूर्णांक64_t rptamrc:1;
		uपूर्णांक64_t rpmerc:1;
		uपूर्णांक64_t rfemrc:1;
		uपूर्णांक64_t rnfemrc:1;
		uपूर्णांक64_t rcemrc:1;
		uपूर्णांक64_t rpoison:1;
		uपूर्णांक64_t recrce:1;
		uपूर्णांक64_t rtlplle:1;
		uपूर्णांक64_t rtlpmal:1;
		uपूर्णांक64_t spoison:1;
#अन्यथा
		uपूर्णांक64_t spoison:1;
		uपूर्णांक64_t rtlpmal:1;
		uपूर्णांक64_t rtlplle:1;
		uपूर्णांक64_t recrce:1;
		uपूर्णांक64_t rpoison:1;
		uपूर्णांक64_t rcemrc:1;
		uपूर्णांक64_t rnfemrc:1;
		uपूर्णांक64_t rfemrc:1;
		uपूर्णांक64_t rpmerc:1;
		uपूर्णांक64_t rptamrc:1;
		uपूर्णांक64_t rumep:1;
		uपूर्णांक64_t rvdm:1;
		uपूर्णांक64_t acto:1;
		uपूर्णांक64_t rte:1;
		uपूर्णांक64_t mre:1;
		uपूर्णांक64_t rdwdle:1;
		uपूर्णांक64_t rtwdle:1;
		uपूर्णांक64_t dpeoosd:1;
		uपूर्णांक64_t fcpvwt:1;
		uपूर्णांक64_t rpe:1;
		uपूर्णांक64_t fcuv:1;
		uपूर्णांक64_t rqo:1;
		uपूर्णांक64_t rauc:1;
		uपूर्णांक64_t racur:1;
		uपूर्णांक64_t racca:1;
		uपूर्णांक64_t caar:1;
		uपूर्णांक64_t rarwdns:1;
		uपूर्णांक64_t ramtlp:1;
		uपूर्णांक64_t racpp:1;
		uपूर्णांक64_t rawwpp:1;
		uपूर्णांक64_t ecrc_e:1;
		uपूर्णांक64_t reserved_31_63:33;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pescx_dbg_info_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_dbg_info_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_31_63:33;
		uपूर्णांक64_t ecrc_e:1;
		uपूर्णांक64_t rawwpp:1;
		uपूर्णांक64_t racpp:1;
		uपूर्णांक64_t ramtlp:1;
		uपूर्णांक64_t rarwdns:1;
		uपूर्णांक64_t caar:1;
		uपूर्णांक64_t racca:1;
		uपूर्णांक64_t racur:1;
		uपूर्णांक64_t rauc:1;
		uपूर्णांक64_t rqo:1;
		uपूर्णांक64_t fcuv:1;
		uपूर्णांक64_t rpe:1;
		uपूर्णांक64_t fcpvwt:1;
		uपूर्णांक64_t dpeoosd:1;
		uपूर्णांक64_t rtwdle:1;
		uपूर्णांक64_t rdwdle:1;
		uपूर्णांक64_t mre:1;
		uपूर्णांक64_t rte:1;
		uपूर्णांक64_t acto:1;
		uपूर्णांक64_t rvdm:1;
		uपूर्णांक64_t rumep:1;
		uपूर्णांक64_t rptamrc:1;
		uपूर्णांक64_t rpmerc:1;
		uपूर्णांक64_t rfemrc:1;
		uपूर्णांक64_t rnfemrc:1;
		uपूर्णांक64_t rcemrc:1;
		uपूर्णांक64_t rpoison:1;
		uपूर्णांक64_t recrce:1;
		uपूर्णांक64_t rtlplle:1;
		uपूर्णांक64_t rtlpmal:1;
		uपूर्णांक64_t spoison:1;
#अन्यथा
		uपूर्णांक64_t spoison:1;
		uपूर्णांक64_t rtlpmal:1;
		uपूर्णांक64_t rtlplle:1;
		uपूर्णांक64_t recrce:1;
		uपूर्णांक64_t rpoison:1;
		uपूर्णांक64_t rcemrc:1;
		uपूर्णांक64_t rnfemrc:1;
		uपूर्णांक64_t rfemrc:1;
		uपूर्णांक64_t rpmerc:1;
		uपूर्णांक64_t rptamrc:1;
		uपूर्णांक64_t rumep:1;
		uपूर्णांक64_t rvdm:1;
		uपूर्णांक64_t acto:1;
		uपूर्णांक64_t rte:1;
		uपूर्णांक64_t mre:1;
		uपूर्णांक64_t rdwdle:1;
		uपूर्णांक64_t rtwdle:1;
		uपूर्णांक64_t dpeoosd:1;
		uपूर्णांक64_t fcpvwt:1;
		uपूर्णांक64_t rpe:1;
		uपूर्णांक64_t fcuv:1;
		uपूर्णांक64_t rqo:1;
		uपूर्णांक64_t rauc:1;
		uपूर्णांक64_t racur:1;
		uपूर्णांक64_t racca:1;
		uपूर्णांक64_t caar:1;
		uपूर्णांक64_t rarwdns:1;
		uपूर्णांक64_t ramtlp:1;
		uपूर्णांक64_t racpp:1;
		uपूर्णांक64_t rawwpp:1;
		uपूर्णांक64_t ecrc_e:1;
		uपूर्णांक64_t reserved_31_63:33;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pescx_diag_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_diag_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t pm_dst:1;
		uपूर्णांक64_t pm_stat:1;
		uपूर्णांक64_t pm_en:1;
		uपूर्णांक64_t aux_en:1;
#अन्यथा
		uपूर्णांक64_t aux_en:1;
		uपूर्णांक64_t pm_en:1;
		uपूर्णांक64_t pm_stat:1;
		uपूर्णांक64_t pm_dst:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pescx_p2n_bar0_start अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_p2n_bar0_start_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t addr:50;
		uपूर्णांक64_t reserved_0_13:14;
#अन्यथा
		uपूर्णांक64_t reserved_0_13:14;
		uपूर्णांक64_t addr:50;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pescx_p2n_bar1_start अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_p2n_bar1_start_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t addr:38;
		uपूर्णांक64_t reserved_0_25:26;
#अन्यथा
		uपूर्णांक64_t reserved_0_25:26;
		uपूर्णांक64_t addr:38;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pescx_p2n_bar2_start अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_p2n_bar2_start_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t addr:25;
		uपूर्णांक64_t reserved_0_38:39;
#अन्यथा
		uपूर्णांक64_t reserved_0_38:39;
		uपूर्णांक64_t addr:25;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pescx_p2p_barx_end अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_p2p_barx_end_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t addr:52;
		uपूर्णांक64_t reserved_0_11:12;
#अन्यथा
		uपूर्णांक64_t reserved_0_11:12;
		uपूर्णांक64_t addr:52;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pescx_p2p_barx_start अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_p2p_barx_start_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t addr:52;
		uपूर्णांक64_t reserved_0_11:12;
#अन्यथा
		uपूर्णांक64_t reserved_0_11:12;
		uपूर्णांक64_t addr:52;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pescx_tlp_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pescx_tlp_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pescx_tlp_credits_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_56_63:8;
		uपूर्णांक64_t peai_ppf:8;
		uपूर्णांक64_t pesc_cpl:8;
		uपूर्णांक64_t pesc_np:8;
		uपूर्णांक64_t pesc_p:8;
		uपूर्णांक64_t npei_cpl:8;
		uपूर्णांक64_t npei_np:8;
		uपूर्णांक64_t npei_p:8;
#अन्यथा
		uपूर्णांक64_t npei_p:8;
		uपूर्णांक64_t npei_np:8;
		uपूर्णांक64_t npei_cpl:8;
		uपूर्णांक64_t pesc_p:8;
		uपूर्णांक64_t pesc_np:8;
		uपूर्णांक64_t pesc_cpl:8;
		uपूर्णांक64_t peai_ppf:8;
		uपूर्णांक64_t reserved_56_63:8;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_pescx_tlp_credits_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_38_63:26;
		uपूर्णांक64_t peai_ppf:8;
		uपूर्णांक64_t pesc_cpl:5;
		uपूर्णांक64_t pesc_np:5;
		uपूर्णांक64_t pesc_p:5;
		uपूर्णांक64_t npei_cpl:5;
		uपूर्णांक64_t npei_np:5;
		uपूर्णांक64_t npei_p:5;
#अन्यथा
		uपूर्णांक64_t npei_p:5;
		uपूर्णांक64_t npei_np:5;
		uपूर्णांक64_t npei_cpl:5;
		uपूर्णांक64_t pesc_p:5;
		uपूर्णांक64_t pesc_np:5;
		uपूर्णांक64_t pesc_cpl:5;
		uपूर्णांक64_t peai_ppf:8;
		uपूर्णांक64_t reserved_38_63:26;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
पूर्ण;

#पूर्ण_अगर
