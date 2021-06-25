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

#अगर_अघोषित __CVMX_IPD_DEFS_H__
#घोषणा __CVMX_IPD_DEFS_H__

#घोषणा CVMX_IPD_1ST_MBUFF_SKIP (CVMX_ADD_IO_SEG(0x00014F0000000000ull))
#घोषणा CVMX_IPD_1st_NEXT_PTR_BACK (CVMX_ADD_IO_SEG(0x00014F0000000150ull))
#घोषणा CVMX_IPD_2nd_NEXT_PTR_BACK (CVMX_ADD_IO_SEG(0x00014F0000000158ull))
#घोषणा CVMX_IPD_BIST_STATUS (CVMX_ADD_IO_SEG(0x00014F00000007F8ull))
#घोषणा CVMX_IPD_BPIDX_MBUF_TH(offset) (CVMX_ADD_IO_SEG(0x00014F0000002000ull) + ((offset) & 63) * 8)
#घोषणा CVMX_IPD_BPID_BP_COUNTERX(offset) (CVMX_ADD_IO_SEG(0x00014F0000003000ull) + ((offset) & 63) * 8)
#घोषणा CVMX_IPD_BP_PRT_RED_END (CVMX_ADD_IO_SEG(0x00014F0000000328ull))
#घोषणा CVMX_IPD_CLK_COUNT (CVMX_ADD_IO_SEG(0x00014F0000000338ull))
#घोषणा CVMX_IPD_CREDITS (CVMX_ADD_IO_SEG(0x00014F0000004410ull))
#घोषणा CVMX_IPD_CTL_STATUS (CVMX_ADD_IO_SEG(0x00014F0000000018ull))
#घोषणा CVMX_IPD_ECC_CTL (CVMX_ADD_IO_SEG(0x00014F0000004408ull))
#घोषणा CVMX_IPD_FREE_PTR_FIFO_CTL (CVMX_ADD_IO_SEG(0x00014F0000000780ull))
#घोषणा CVMX_IPD_FREE_PTR_VALUE (CVMX_ADD_IO_SEG(0x00014F0000000788ull))
#घोषणा CVMX_IPD_HOLD_PTR_FIFO_CTL (CVMX_ADD_IO_SEG(0x00014F0000000790ull))
#घोषणा CVMX_IPD_INT_ENB (CVMX_ADD_IO_SEG(0x00014F0000000160ull))
#घोषणा CVMX_IPD_INT_SUM (CVMX_ADD_IO_SEG(0x00014F0000000168ull))
#घोषणा CVMX_IPD_NEXT_PKT_PTR (CVMX_ADD_IO_SEG(0x00014F00000007A0ull))
#घोषणा CVMX_IPD_NEXT_WQE_PTR (CVMX_ADD_IO_SEG(0x00014F00000007A8ull))
#घोषणा CVMX_IPD_NOT_1ST_MBUFF_SKIP (CVMX_ADD_IO_SEG(0x00014F0000000008ull))
#घोषणा CVMX_IPD_ON_BP_DROP_PKTX(block_id) (CVMX_ADD_IO_SEG(0x00014F0000004100ull))
#घोषणा CVMX_IPD_PACKET_MBUFF_SIZE (CVMX_ADD_IO_SEG(0x00014F0000000010ull))
#घोषणा CVMX_IPD_PKT_ERR (CVMX_ADD_IO_SEG(0x00014F00000003F0ull))
#घोषणा CVMX_IPD_PKT_PTR_VALID (CVMX_ADD_IO_SEG(0x00014F0000000358ull))
#घोषणा CVMX_IPD_PORTX_BP_PAGE_CNT(offset) (CVMX_ADD_IO_SEG(0x00014F0000000028ull) + ((offset) & 63) * 8)
#घोषणा CVMX_IPD_PORTX_BP_PAGE_CNT2(offset) (CVMX_ADD_IO_SEG(0x00014F0000000368ull) + ((offset) & 63) * 8 - 8*36)
#घोषणा CVMX_IPD_PORTX_BP_PAGE_CNT3(offset) (CVMX_ADD_IO_SEG(0x00014F00000003D0ull) + ((offset) & 63) * 8 - 8*40)
#घोषणा CVMX_IPD_PORT_BP_COUNTERS2_PAIRX(offset) (CVMX_ADD_IO_SEG(0x00014F0000000388ull) + ((offset) & 63) * 8 - 8*36)
#घोषणा CVMX_IPD_PORT_BP_COUNTERS3_PAIRX(offset) (CVMX_ADD_IO_SEG(0x00014F00000003B0ull) + ((offset) & 63) * 8 - 8*40)
#घोषणा CVMX_IPD_PORT_BP_COUNTERS4_PAIRX(offset) (CVMX_ADD_IO_SEG(0x00014F0000000410ull) + ((offset) & 63) * 8 - 8*44)
#घोषणा CVMX_IPD_PORT_BP_COUNTERS_PAIRX(offset) (CVMX_ADD_IO_SEG(0x00014F00000001B8ull) + ((offset) & 63) * 8)
#घोषणा CVMX_IPD_PORT_PTR_FIFO_CTL (CVMX_ADD_IO_SEG(0x00014F0000000798ull))
#घोषणा CVMX_IPD_PORT_QOS_INTX(offset) (CVMX_ADD_IO_SEG(0x00014F0000000808ull) + ((offset) & 7) * 8)
#घोषणा CVMX_IPD_PORT_QOS_INT_ENBX(offset) (CVMX_ADD_IO_SEG(0x00014F0000000848ull) + ((offset) & 7) * 8)
#घोषणा CVMX_IPD_PORT_QOS_X_CNT(offset) (CVMX_ADD_IO_SEG(0x00014F0000000888ull) + ((offset) & 511) * 8)
#घोषणा CVMX_IPD_PORT_SOPX(block_id) (CVMX_ADD_IO_SEG(0x00014F0000004400ull))
#घोषणा CVMX_IPD_PRC_HOLD_PTR_FIFO_CTL (CVMX_ADD_IO_SEG(0x00014F0000000348ull))
#घोषणा CVMX_IPD_PRC_PORT_PTR_FIFO_CTL (CVMX_ADD_IO_SEG(0x00014F0000000350ull))
#घोषणा CVMX_IPD_PTR_COUNT (CVMX_ADD_IO_SEG(0x00014F0000000320ull))
#घोषणा CVMX_IPD_PWP_PTR_FIFO_CTL (CVMX_ADD_IO_SEG(0x00014F0000000340ull))
#घोषणा CVMX_IPD_QOS0_RED_MARKS CVMX_IPD_QOSX_RED_MARKS(0)
#घोषणा CVMX_IPD_QOS1_RED_MARKS CVMX_IPD_QOSX_RED_MARKS(1)
#घोषणा CVMX_IPD_QOS2_RED_MARKS CVMX_IPD_QOSX_RED_MARKS(2)
#घोषणा CVMX_IPD_QOS3_RED_MARKS CVMX_IPD_QOSX_RED_MARKS(3)
#घोषणा CVMX_IPD_QOS4_RED_MARKS CVMX_IPD_QOSX_RED_MARKS(4)
#घोषणा CVMX_IPD_QOS5_RED_MARKS CVMX_IPD_QOSX_RED_MARKS(5)
#घोषणा CVMX_IPD_QOS6_RED_MARKS CVMX_IPD_QOSX_RED_MARKS(6)
#घोषणा CVMX_IPD_QOS7_RED_MARKS CVMX_IPD_QOSX_RED_MARKS(7)
#घोषणा CVMX_IPD_QOSX_RED_MARKS(offset) (CVMX_ADD_IO_SEG(0x00014F0000000178ull) + ((offset) & 7) * 8)
#घोषणा CVMX_IPD_QUE0_FREE_PAGE_CNT (CVMX_ADD_IO_SEG(0x00014F0000000330ull))
#घोषणा CVMX_IPD_RED_BPID_ENABLEX(block_id) (CVMX_ADD_IO_SEG(0x00014F0000004200ull))
#घोषणा CVMX_IPD_RED_DELAY (CVMX_ADD_IO_SEG(0x00014F0000004300ull))
#घोषणा CVMX_IPD_RED_PORT_ENABLE (CVMX_ADD_IO_SEG(0x00014F00000002D8ull))
#घोषणा CVMX_IPD_RED_PORT_ENABLE2 (CVMX_ADD_IO_SEG(0x00014F00000003A8ull))
#घोषणा CVMX_IPD_RED_QUE0_PARAM CVMX_IPD_RED_QUEX_PARAM(0)
#घोषणा CVMX_IPD_RED_QUE1_PARAM CVMX_IPD_RED_QUEX_PARAM(1)
#घोषणा CVMX_IPD_RED_QUE2_PARAM CVMX_IPD_RED_QUEX_PARAM(2)
#घोषणा CVMX_IPD_RED_QUE3_PARAM CVMX_IPD_RED_QUEX_PARAM(3)
#घोषणा CVMX_IPD_RED_QUE4_PARAM CVMX_IPD_RED_QUEX_PARAM(4)
#घोषणा CVMX_IPD_RED_QUE5_PARAM CVMX_IPD_RED_QUEX_PARAM(5)
#घोषणा CVMX_IPD_RED_QUE6_PARAM CVMX_IPD_RED_QUEX_PARAM(6)
#घोषणा CVMX_IPD_RED_QUE7_PARAM CVMX_IPD_RED_QUEX_PARAM(7)
#घोषणा CVMX_IPD_RED_QUEX_PARAM(offset) (CVMX_ADD_IO_SEG(0x00014F00000002E0ull) + ((offset) & 7) * 8)
#घोषणा CVMX_IPD_REQ_WGT (CVMX_ADD_IO_SEG(0x00014F0000004418ull))
#घोषणा CVMX_IPD_SUB_PORT_BP_PAGE_CNT (CVMX_ADD_IO_SEG(0x00014F0000000148ull))
#घोषणा CVMX_IPD_SUB_PORT_FCS (CVMX_ADD_IO_SEG(0x00014F0000000170ull))
#घोषणा CVMX_IPD_SUB_PORT_QOS_CNT (CVMX_ADD_IO_SEG(0x00014F0000000800ull))
#घोषणा CVMX_IPD_WQE_FPA_QUEUE (CVMX_ADD_IO_SEG(0x00014F0000000020ull))
#घोषणा CVMX_IPD_WQE_PTR_VALID (CVMX_ADD_IO_SEG(0x00014F0000000360ull))

जोड़ cvmx_ipd_1st_mbuff_skip अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_1st_mbuff_skip_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t skip_sz:6;
#अन्यथा
		uपूर्णांक64_t skip_sz:6;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_1st_next_ptr_back अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_1st_next_ptr_back_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t back:4;
#अन्यथा
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_2nd_next_ptr_back अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_2nd_next_ptr_back_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t back:4;
#अन्यथा
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_bist_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_bist_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_23_63:41;
		uपूर्णांक64_t iiwo1:1;
		uपूर्णांक64_t iiwo0:1;
		uपूर्णांक64_t iio1:1;
		uपूर्णांक64_t iio0:1;
		uपूर्णांक64_t pbm4:1;
		uपूर्णांक64_t csr_mem:1;
		uपूर्णांक64_t csr_ncmd:1;
		uपूर्णांक64_t pwq_wqed:1;
		uपूर्णांक64_t pwq_wp1:1;
		uपूर्णांक64_t pwq_घात:1;
		uपूर्णांक64_t ipq_pbe1:1;
		uपूर्णांक64_t ipq_pbe0:1;
		uपूर्णांक64_t pbm3:1;
		uपूर्णांक64_t pbm2:1;
		uपूर्णांक64_t pbm1:1;
		uपूर्णांक64_t pbm0:1;
		uपूर्णांक64_t pbm_word:1;
		uपूर्णांक64_t pwq1:1;
		uपूर्णांक64_t pwq0:1;
		uपूर्णांक64_t prc_off:1;
		uपूर्णांक64_t ipd_old:1;
		uपूर्णांक64_t ipd_new:1;
		uपूर्णांक64_t pwp:1;
#अन्यथा
		uपूर्णांक64_t pwp:1;
		uपूर्णांक64_t ipd_new:1;
		uपूर्णांक64_t ipd_old:1;
		uपूर्णांक64_t prc_off:1;
		uपूर्णांक64_t pwq0:1;
		uपूर्णांक64_t pwq1:1;
		uपूर्णांक64_t pbm_word:1;
		uपूर्णांक64_t pbm0:1;
		uपूर्णांक64_t pbm1:1;
		uपूर्णांक64_t pbm2:1;
		uपूर्णांक64_t pbm3:1;
		uपूर्णांक64_t ipq_pbe0:1;
		uपूर्णांक64_t ipq_pbe1:1;
		uपूर्णांक64_t pwq_घात:1;
		uपूर्णांक64_t pwq_wp1:1;
		uपूर्णांक64_t pwq_wqed:1;
		uपूर्णांक64_t csr_ncmd:1;
		uपूर्णांक64_t csr_mem:1;
		uपूर्णांक64_t pbm4:1;
		uपूर्णांक64_t iio0:1;
		uपूर्णांक64_t iio1:1;
		uपूर्णांक64_t iiwo0:1;
		uपूर्णांक64_t iiwo1:1;
		uपूर्णांक64_t reserved_23_63:41;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_ipd_bist_status_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t pwq_wqed:1;
		uपूर्णांक64_t pwq_wp1:1;
		uपूर्णांक64_t pwq_घात:1;
		uपूर्णांक64_t ipq_pbe1:1;
		uपूर्णांक64_t ipq_pbe0:1;
		uपूर्णांक64_t pbm3:1;
		uपूर्णांक64_t pbm2:1;
		uपूर्णांक64_t pbm1:1;
		uपूर्णांक64_t pbm0:1;
		uपूर्णांक64_t pbm_word:1;
		uपूर्णांक64_t pwq1:1;
		uपूर्णांक64_t pwq0:1;
		uपूर्णांक64_t prc_off:1;
		uपूर्णांक64_t ipd_old:1;
		uपूर्णांक64_t ipd_new:1;
		uपूर्णांक64_t pwp:1;
#अन्यथा
		uपूर्णांक64_t pwp:1;
		uपूर्णांक64_t ipd_new:1;
		uपूर्णांक64_t ipd_old:1;
		uपूर्णांक64_t prc_off:1;
		uपूर्णांक64_t pwq0:1;
		uपूर्णांक64_t pwq1:1;
		uपूर्णांक64_t pbm_word:1;
		uपूर्णांक64_t pbm0:1;
		uपूर्णांक64_t pbm1:1;
		uपूर्णांक64_t pbm2:1;
		uपूर्णांक64_t pbm3:1;
		uपूर्णांक64_t ipq_pbe0:1;
		uपूर्णांक64_t ipq_pbe1:1;
		uपूर्णांक64_t pwq_घात:1;
		uपूर्णांक64_t pwq_wp1:1;
		uपूर्णांक64_t pwq_wqed:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_ipd_bist_status_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t csr_mem:1;
		uपूर्णांक64_t csr_ncmd:1;
		uपूर्णांक64_t pwq_wqed:1;
		uपूर्णांक64_t pwq_wp1:1;
		uपूर्णांक64_t pwq_घात:1;
		uपूर्णांक64_t ipq_pbe1:1;
		uपूर्णांक64_t ipq_pbe0:1;
		uपूर्णांक64_t pbm3:1;
		uपूर्णांक64_t pbm2:1;
		uपूर्णांक64_t pbm1:1;
		uपूर्णांक64_t pbm0:1;
		uपूर्णांक64_t pbm_word:1;
		uपूर्णांक64_t pwq1:1;
		uपूर्णांक64_t pwq0:1;
		uपूर्णांक64_t prc_off:1;
		uपूर्णांक64_t ipd_old:1;
		uपूर्णांक64_t ipd_new:1;
		uपूर्णांक64_t pwp:1;
#अन्यथा
		uपूर्णांक64_t pwp:1;
		uपूर्णांक64_t ipd_new:1;
		uपूर्णांक64_t ipd_old:1;
		uपूर्णांक64_t prc_off:1;
		uपूर्णांक64_t pwq0:1;
		uपूर्णांक64_t pwq1:1;
		uपूर्णांक64_t pbm_word:1;
		uपूर्णांक64_t pbm0:1;
		uपूर्णांक64_t pbm1:1;
		uपूर्णांक64_t pbm2:1;
		uपूर्णांक64_t pbm3:1;
		uपूर्णांक64_t ipq_pbe0:1;
		uपूर्णांक64_t ipq_pbe1:1;
		uपूर्णांक64_t pwq_घात:1;
		uपूर्णांक64_t pwq_wp1:1;
		uपूर्णांक64_t pwq_wqed:1;
		uपूर्णांक64_t csr_ncmd:1;
		uपूर्णांक64_t csr_mem:1;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_ipd_bp_prt_red_end अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_bp_prt_red_end_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t prt_enb:48;
#अन्यथा
		uपूर्णांक64_t prt_enb:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_ipd_bp_prt_red_end_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_36_63:28;
		uपूर्णांक64_t prt_enb:36;
#अन्यथा
		uपूर्णांक64_t prt_enb:36;
		uपूर्णांक64_t reserved_36_63:28;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_ipd_bp_prt_red_end_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t prt_enb:40;
#अन्यथा
		uपूर्णांक64_t prt_enb:40;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_ipd_bp_prt_red_end_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t prt_enb:44;
#अन्यथा
		uपूर्णांक64_t prt_enb:44;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_ipd_bpidx_mbuf_th अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_bpidx_mbuf_th_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t bp_enb:1;
		uपूर्णांक64_t page_cnt:17;
#अन्यथा
		uपूर्णांक64_t page_cnt:17;
		uपूर्णांक64_t bp_enb:1;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_bpid_bp_counterx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_bpid_bp_counterx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t cnt_val:25;
#अन्यथा
		uपूर्णांक64_t cnt_val:25;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_clk_count अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_clk_count_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t clk_cnt:64;
#अन्यथा
		uपूर्णांक64_t clk_cnt:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t iob_wrc:8;
		uपूर्णांक64_t iob_wr:8;
#अन्यथा
		uपूर्णांक64_t iob_wr:8;
		uपूर्णांक64_t iob_wrc:8;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_ctl_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_ctl_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t use_sop:1;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t clken:1;
		uपूर्णांक64_t no_wptr:1;
		uपूर्णांक64_t pq_apkt:1;
		uपूर्णांक64_t pq_nabuf:1;
		uपूर्णांक64_t ipd_full:1;
		uपूर्णांक64_t pkt_off:1;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t ipd_en:1;
#अन्यथा
		uपूर्णांक64_t ipd_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t pkt_off:1;
		uपूर्णांक64_t ipd_full:1;
		uपूर्णांक64_t pq_nabuf:1;
		uपूर्णांक64_t pq_apkt:1;
		uपूर्णांक64_t no_wptr:1;
		uपूर्णांक64_t clken:1;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t use_sop:1;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_ipd_ctl_status_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t ipd_en:1;
#अन्यथा
		uपूर्णांक64_t ipd_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_ipd_ctl_status_cn38xxp2 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t ipd_en:1;
#अन्यथा
		uपूर्णांक64_t ipd_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn38xxp2;
	काष्ठा cvmx_ipd_ctl_status_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_15_63:49;
		uपूर्णांक64_t no_wptr:1;
		uपूर्णांक64_t pq_apkt:1;
		uपूर्णांक64_t pq_nabuf:1;
		uपूर्णांक64_t ipd_full:1;
		uपूर्णांक64_t pkt_off:1;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t ipd_en:1;
#अन्यथा
		uपूर्णांक64_t ipd_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t pkt_off:1;
		uपूर्णांक64_t ipd_full:1;
		uपूर्णांक64_t pq_nabuf:1;
		uपूर्णांक64_t pq_apkt:1;
		uपूर्णांक64_t no_wptr:1;
		uपूर्णांक64_t reserved_15_63:49;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_ipd_ctl_status_cn58xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t ipd_full:1;
		uपूर्णांक64_t pkt_off:1;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t ipd_en:1;
#अन्यथा
		uपूर्णांक64_t ipd_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t pkt_off:1;
		uपूर्णांक64_t ipd_full:1;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn58xx;
	काष्ठा cvmx_ipd_ctl_status_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t clken:1;
		uपूर्णांक64_t no_wptr:1;
		uपूर्णांक64_t pq_apkt:1;
		uपूर्णांक64_t pq_nabuf:1;
		uपूर्णांक64_t ipd_full:1;
		uपूर्णांक64_t pkt_off:1;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t ipd_en:1;
#अन्यथा
		uपूर्णांक64_t ipd_en:1;
		uपूर्णांक64_t opc_mode:2;
		uपूर्णांक64_t pbp_en:1;
		uपूर्णांक64_t wqe_lend:1;
		uपूर्णांक64_t pkt_lend:1;
		uपूर्णांक64_t naddbuf:1;
		uपूर्णांक64_t addpkt:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t len_m8:1;
		uपूर्णांक64_t pkt_off:1;
		uपूर्णांक64_t ipd_full:1;
		uपूर्णांक64_t pq_nabuf:1;
		uपूर्णांक64_t pq_apkt:1;
		uपूर्णांक64_t no_wptr:1;
		uपूर्णांक64_t clken:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_ipd_ecc_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_ecc_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t pm3_syn:2;
		uपूर्णांक64_t pm2_syn:2;
		uपूर्णांक64_t pm1_syn:2;
		uपूर्णांक64_t pm0_syn:2;
#अन्यथा
		uपूर्णांक64_t pm0_syn:2;
		uपूर्णांक64_t pm1_syn:2;
		uपूर्णांक64_t pm2_syn:2;
		uपूर्णांक64_t pm3_syn:2;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_मुक्त_ptr_fअगरo_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_मुक्त_ptr_fअगरo_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t max_cnts:7;
		uपूर्णांक64_t wraddr:8;
		uपूर्णांक64_t praddr:8;
		uपूर्णांक64_t cena:1;
		uपूर्णांक64_t raddr:8;
#अन्यथा
		uपूर्णांक64_t raddr:8;
		uपूर्णांक64_t cena:1;
		uपूर्णांक64_t praddr:8;
		uपूर्णांक64_t wraddr:8;
		uपूर्णांक64_t max_cnts:7;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_मुक्त_ptr_value अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_मुक्त_ptr_value_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_33_63:31;
		uपूर्णांक64_t ptr:33;
#अन्यथा
		uपूर्णांक64_t ptr:33;
		uपूर्णांक64_t reserved_33_63:31;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_hold_ptr_fअगरo_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_hold_ptr_fअगरo_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_43_63:21;
		uपूर्णांक64_t ptr:33;
		uपूर्णांक64_t max_pkt:3;
		uपूर्णांक64_t praddr:3;
		uपूर्णांक64_t cena:1;
		uपूर्णांक64_t raddr:3;
#अन्यथा
		uपूर्णांक64_t raddr:3;
		uपूर्णांक64_t cena:1;
		uपूर्णांक64_t praddr:3;
		uपूर्णांक64_t max_pkt:3;
		uपूर्णांक64_t ptr:33;
		uपूर्णांक64_t reserved_43_63:21;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_पूर्णांक_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_पूर्णांक_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_23_63:41;
		uपूर्णांक64_t pw3_dbe:1;
		uपूर्णांक64_t pw3_sbe:1;
		uपूर्णांक64_t pw2_dbe:1;
		uपूर्णांक64_t pw2_sbe:1;
		uपूर्णांक64_t pw1_dbe:1;
		uपूर्णांक64_t pw1_sbe:1;
		uपूर्णांक64_t pw0_dbe:1;
		uपूर्णांक64_t pw0_sbe:1;
		uपूर्णांक64_t dat:1;
		uपूर्णांक64_t eop:1;
		uपूर्णांक64_t sop:1;
		uपूर्णांक64_t pq_sub:1;
		uपूर्णांक64_t pq_add:1;
		uपूर्णांक64_t bc_ovr:1;
		uपूर्णांक64_t d_coll:1;
		uपूर्णांक64_t c_coll:1;
		uपूर्णांक64_t cc_ovr:1;
		uपूर्णांक64_t dc_ovr:1;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par0:1;
#अन्यथा
		uपूर्णांक64_t prc_par0:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t dc_ovr:1;
		uपूर्णांक64_t cc_ovr:1;
		uपूर्णांक64_t c_coll:1;
		uपूर्णांक64_t d_coll:1;
		uपूर्णांक64_t bc_ovr:1;
		uपूर्णांक64_t pq_add:1;
		uपूर्णांक64_t pq_sub:1;
		uपूर्णांक64_t sop:1;
		uपूर्णांक64_t eop:1;
		uपूर्णांक64_t dat:1;
		uपूर्णांक64_t pw0_sbe:1;
		uपूर्णांक64_t pw0_dbe:1;
		uपूर्णांक64_t pw1_sbe:1;
		uपूर्णांक64_t pw1_dbe:1;
		uपूर्णांक64_t pw2_sbe:1;
		uपूर्णांक64_t pw2_dbe:1;
		uपूर्णांक64_t pw3_sbe:1;
		uपूर्णांक64_t pw3_dbe:1;
		uपूर्णांक64_t reserved_23_63:41;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_ipd_पूर्णांक_enb_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par0:1;
#अन्यथा
		uपूर्णांक64_t prc_par0:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_ipd_पूर्णांक_enb_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t bc_ovr:1;
		uपूर्णांक64_t d_coll:1;
		uपूर्णांक64_t c_coll:1;
		uपूर्णांक64_t cc_ovr:1;
		uपूर्णांक64_t dc_ovr:1;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par0:1;
#अन्यथा
		uपूर्णांक64_t prc_par0:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t dc_ovr:1;
		uपूर्णांक64_t cc_ovr:1;
		uपूर्णांक64_t c_coll:1;
		uपूर्णांक64_t d_coll:1;
		uपूर्णांक64_t bc_ovr:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_ipd_पूर्णांक_enb_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t pq_sub:1;
		uपूर्णांक64_t pq_add:1;
		uपूर्णांक64_t bc_ovr:1;
		uपूर्णांक64_t d_coll:1;
		uपूर्णांक64_t c_coll:1;
		uपूर्णांक64_t cc_ovr:1;
		uपूर्णांक64_t dc_ovr:1;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par0:1;
#अन्यथा
		uपूर्णांक64_t prc_par0:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t dc_ovr:1;
		uपूर्णांक64_t cc_ovr:1;
		uपूर्णांक64_t c_coll:1;
		uपूर्णांक64_t d_coll:1;
		uपूर्णांक64_t bc_ovr:1;
		uपूर्णांक64_t pq_add:1;
		uपूर्णांक64_t pq_sub:1;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_ipd_पूर्णांक_sum अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_पूर्णांक_sum_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_23_63:41;
		uपूर्णांक64_t pw3_dbe:1;
		uपूर्णांक64_t pw3_sbe:1;
		uपूर्णांक64_t pw2_dbe:1;
		uपूर्णांक64_t pw2_sbe:1;
		uपूर्णांक64_t pw1_dbe:1;
		uपूर्णांक64_t pw1_sbe:1;
		uपूर्णांक64_t pw0_dbe:1;
		uपूर्णांक64_t pw0_sbe:1;
		uपूर्णांक64_t dat:1;
		uपूर्णांक64_t eop:1;
		uपूर्णांक64_t sop:1;
		uपूर्णांक64_t pq_sub:1;
		uपूर्णांक64_t pq_add:1;
		uपूर्णांक64_t bc_ovr:1;
		uपूर्णांक64_t d_coll:1;
		uपूर्णांक64_t c_coll:1;
		uपूर्णांक64_t cc_ovr:1;
		uपूर्णांक64_t dc_ovr:1;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par0:1;
#अन्यथा
		uपूर्णांक64_t prc_par0:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t dc_ovr:1;
		uपूर्णांक64_t cc_ovr:1;
		uपूर्णांक64_t c_coll:1;
		uपूर्णांक64_t d_coll:1;
		uपूर्णांक64_t bc_ovr:1;
		uपूर्णांक64_t pq_add:1;
		uपूर्णांक64_t pq_sub:1;
		uपूर्णांक64_t sop:1;
		uपूर्णांक64_t eop:1;
		uपूर्णांक64_t dat:1;
		uपूर्णांक64_t pw0_sbe:1;
		uपूर्णांक64_t pw0_dbe:1;
		uपूर्णांक64_t pw1_sbe:1;
		uपूर्णांक64_t pw1_dbe:1;
		uपूर्णांक64_t pw2_sbe:1;
		uपूर्णांक64_t pw2_dbe:1;
		uपूर्णांक64_t pw3_sbe:1;
		uपूर्णांक64_t pw3_dbe:1;
		uपूर्णांक64_t reserved_23_63:41;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_ipd_पूर्णांक_sum_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par0:1;
#अन्यथा
		uपूर्णांक64_t prc_par0:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_ipd_पूर्णांक_sum_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t bc_ovr:1;
		uपूर्णांक64_t d_coll:1;
		uपूर्णांक64_t c_coll:1;
		uपूर्णांक64_t cc_ovr:1;
		uपूर्णांक64_t dc_ovr:1;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par0:1;
#अन्यथा
		uपूर्णांक64_t prc_par0:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t dc_ovr:1;
		uपूर्णांक64_t cc_ovr:1;
		uपूर्णांक64_t c_coll:1;
		uपूर्णांक64_t d_coll:1;
		uपूर्णांक64_t bc_ovr:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_ipd_पूर्णांक_sum_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t pq_sub:1;
		uपूर्णांक64_t pq_add:1;
		uपूर्णांक64_t bc_ovr:1;
		uपूर्णांक64_t d_coll:1;
		uपूर्णांक64_t c_coll:1;
		uपूर्णांक64_t cc_ovr:1;
		uपूर्णांक64_t dc_ovr:1;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par0:1;
#अन्यथा
		uपूर्णांक64_t prc_par0:1;
		uपूर्णांक64_t prc_par1:1;
		uपूर्णांक64_t prc_par2:1;
		uपूर्णांक64_t prc_par3:1;
		uपूर्णांक64_t bp_sub:1;
		uपूर्णांक64_t dc_ovr:1;
		uपूर्णांक64_t cc_ovr:1;
		uपूर्णांक64_t c_coll:1;
		uपूर्णांक64_t d_coll:1;
		uपूर्णांक64_t bc_ovr:1;
		uपूर्णांक64_t pq_add:1;
		uपूर्णांक64_t pq_sub:1;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_ipd_next_pkt_ptr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_next_pkt_ptr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_33_63:31;
		uपूर्णांक64_t ptr:33;
#अन्यथा
		uपूर्णांक64_t ptr:33;
		uपूर्णांक64_t reserved_33_63:31;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_next_wqe_ptr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_next_wqe_ptr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_33_63:31;
		uपूर्णांक64_t ptr:33;
#अन्यथा
		uपूर्णांक64_t ptr:33;
		uपूर्णांक64_t reserved_33_63:31;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_not_1st_mbuff_skip अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_not_1st_mbuff_skip_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t skip_sz:6;
#अन्यथा
		uपूर्णांक64_t skip_sz:6;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_on_bp_drop_pktx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_on_bp_drop_pktx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t prt_enb:64;
#अन्यथा
		uपूर्णांक64_t prt_enb:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_packet_mbuff_size अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_packet_mbuff_size_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t mb_size:12;
#अन्यथा
		uपूर्णांक64_t mb_size:12;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_pkt_err अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_pkt_err_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t reयंत्र:6;
#अन्यथा
		uपूर्णांक64_t reयंत्र:6;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_pkt_ptr_valid अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_pkt_ptr_valid_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t ptr:29;
#अन्यथा
		uपूर्णांक64_t ptr:29;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_portx_bp_page_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_portx_bp_page_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t bp_enb:1;
		uपूर्णांक64_t page_cnt:17;
#अन्यथा
		uपूर्णांक64_t page_cnt:17;
		uपूर्णांक64_t bp_enb:1;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_portx_bp_page_cnt2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_portx_bp_page_cnt2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t bp_enb:1;
		uपूर्णांक64_t page_cnt:17;
#अन्यथा
		uपूर्णांक64_t page_cnt:17;
		uपूर्णांक64_t bp_enb:1;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_portx_bp_page_cnt3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_portx_bp_page_cnt3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t bp_enb:1;
		uपूर्णांक64_t page_cnt:17;
#अन्यथा
		uपूर्णांक64_t page_cnt:17;
		uपूर्णांक64_t bp_enb:1;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_port_bp_counters2_pairx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_port_bp_counters2_pairx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t cnt_val:25;
#अन्यथा
		uपूर्णांक64_t cnt_val:25;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_port_bp_counters3_pairx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_port_bp_counters3_pairx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t cnt_val:25;
#अन्यथा
		uपूर्णांक64_t cnt_val:25;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_port_bp_counters4_pairx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_port_bp_counters4_pairx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t cnt_val:25;
#अन्यथा
		uपूर्णांक64_t cnt_val:25;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_port_bp_counters_pairx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_port_bp_counters_pairx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t cnt_val:25;
#अन्यथा
		uपूर्णांक64_t cnt_val:25;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_port_ptr_fअगरo_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_port_ptr_fअगरo_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t ptr:33;
		uपूर्णांक64_t max_pkt:7;
		uपूर्णांक64_t cena:1;
		uपूर्णांक64_t raddr:7;
#अन्यथा
		uपूर्णांक64_t raddr:7;
		uपूर्णांक64_t cena:1;
		uपूर्णांक64_t max_pkt:7;
		uपूर्णांक64_t ptr:33;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_port_qos_x_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_port_qos_x_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t wmark:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t wmark:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_port_qos_पूर्णांकx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_port_qos_पूर्णांकx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t पूर्णांकr:64;
#अन्यथा
		uपूर्णांक64_t पूर्णांकr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_port_qos_पूर्णांक_enbx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_port_qos_पूर्णांक_enbx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t enb:64;
#अन्यथा
		uपूर्णांक64_t enb:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_port_sopx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_port_sopx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t sop:64;
#अन्यथा
		uपूर्णांक64_t sop:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_prc_hold_ptr_fअगरo_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_prc_hold_ptr_fअगरo_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_39_63:25;
		uपूर्णांक64_t max_pkt:3;
		uपूर्णांक64_t praddr:3;
		uपूर्णांक64_t ptr:29;
		uपूर्णांक64_t cena:1;
		uपूर्णांक64_t raddr:3;
#अन्यथा
		uपूर्णांक64_t raddr:3;
		uपूर्णांक64_t cena:1;
		uपूर्णांक64_t ptr:29;
		uपूर्णांक64_t praddr:3;
		uपूर्णांक64_t max_pkt:3;
		uपूर्णांक64_t reserved_39_63:25;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_prc_port_ptr_fअगरo_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_prc_port_ptr_fअगरo_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t max_pkt:7;
		uपूर्णांक64_t ptr:29;
		uपूर्णांक64_t cena:1;
		uपूर्णांक64_t raddr:7;
#अन्यथा
		uपूर्णांक64_t raddr:7;
		uपूर्णांक64_t cena:1;
		uपूर्णांक64_t ptr:29;
		uपूर्णांक64_t max_pkt:7;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_ptr_count अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_ptr_count_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_19_63:45;
		uपूर्णांक64_t pktv_cnt:1;
		uपूर्णांक64_t wqev_cnt:1;
		uपूर्णांक64_t pfअगर_cnt:3;
		uपूर्णांक64_t pkt_pcnt:7;
		uपूर्णांक64_t wqe_pcnt:7;
#अन्यथा
		uपूर्णांक64_t wqe_pcnt:7;
		uपूर्णांक64_t pkt_pcnt:7;
		uपूर्णांक64_t pfअगर_cnt:3;
		uपूर्णांक64_t wqev_cnt:1;
		uपूर्णांक64_t pktv_cnt:1;
		uपूर्णांक64_t reserved_19_63:45;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_pwp_ptr_fअगरo_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_pwp_ptr_fअगरo_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_61_63:3;
		uपूर्णांक64_t max_cnts:7;
		uपूर्णांक64_t wraddr:8;
		uपूर्णांक64_t praddr:8;
		uपूर्णांक64_t ptr:29;
		uपूर्णांक64_t cena:1;
		uपूर्णांक64_t raddr:8;
#अन्यथा
		uपूर्णांक64_t raddr:8;
		uपूर्णांक64_t cena:1;
		uपूर्णांक64_t ptr:29;
		uपूर्णांक64_t praddr:8;
		uपूर्णांक64_t wraddr:8;
		uपूर्णांक64_t max_cnts:7;
		uपूर्णांक64_t reserved_61_63:3;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_qosx_red_marks अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_qosx_red_marks_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t drop:32;
		uपूर्णांक64_t pass:32;
#अन्यथा
		uपूर्णांक64_t pass:32;
		uपूर्णांक64_t drop:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_que0_मुक्त_page_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_que0_मुक्त_page_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t q0_pcnt:32;
#अन्यथा
		uपूर्णांक64_t q0_pcnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_red_bpid_enablex अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_red_bpid_enablex_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t prt_enb:64;
#अन्यथा
		uपूर्णांक64_t prt_enb:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_red_delay अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_red_delay_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t prb_dly:14;
		uपूर्णांक64_t avg_dly:14;
#अन्यथा
		uपूर्णांक64_t avg_dly:14;
		uपूर्णांक64_t prb_dly:14;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_red_port_enable अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_red_port_enable_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t prb_dly:14;
		uपूर्णांक64_t avg_dly:14;
		uपूर्णांक64_t prt_enb:36;
#अन्यथा
		uपूर्णांक64_t prt_enb:36;
		uपूर्णांक64_t avg_dly:14;
		uपूर्णांक64_t prb_dly:14;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_red_port_enable2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_red_port_enable2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t prt_enb:12;
#अन्यथा
		uपूर्णांक64_t prt_enb:12;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_ipd_red_port_enable2_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t prt_enb:4;
#अन्यथा
		uपूर्णांक64_t prt_enb:4;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_ipd_red_port_enable2_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t prt_enb:8;
#अन्यथा
		uपूर्णांक64_t prt_enb:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_ipd_red_quex_param अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_red_quex_param_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_49_63:15;
		uपूर्णांक64_t use_pcnt:1;
		uपूर्णांक64_t new_con:8;
		uपूर्णांक64_t avg_con:8;
		uपूर्णांक64_t prb_con:32;
#अन्यथा
		uपूर्णांक64_t prb_con:32;
		uपूर्णांक64_t avg_con:8;
		uपूर्णांक64_t new_con:8;
		uपूर्णांक64_t use_pcnt:1;
		uपूर्णांक64_t reserved_49_63:15;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_req_wgt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_req_wgt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t wgt7:8;
		uपूर्णांक64_t wgt6:8;
		uपूर्णांक64_t wgt5:8;
		uपूर्णांक64_t wgt4:8;
		uपूर्णांक64_t wgt3:8;
		uपूर्णांक64_t wgt2:8;
		uपूर्णांक64_t wgt1:8;
		uपूर्णांक64_t wgt0:8;
#अन्यथा
		uपूर्णांक64_t wgt0:8;
		uपूर्णांक64_t wgt1:8;
		uपूर्णांक64_t wgt2:8;
		uपूर्णांक64_t wgt3:8;
		uपूर्णांक64_t wgt4:8;
		uपूर्णांक64_t wgt5:8;
		uपूर्णांक64_t wgt6:8;
		uपूर्णांक64_t wgt7:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_sub_port_bp_page_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_sub_port_bp_page_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_31_63:33;
		uपूर्णांक64_t port:6;
		uपूर्णांक64_t page_cnt:25;
#अन्यथा
		uपूर्णांक64_t page_cnt:25;
		uपूर्णांक64_t port:6;
		uपूर्णांक64_t reserved_31_63:33;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_sub_port_fcs अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_sub_port_fcs_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t port_bit2:4;
		uपूर्णांक64_t reserved_32_35:4;
		uपूर्णांक64_t port_bit:32;
#अन्यथा
		uपूर्णांक64_t port_bit:32;
		uपूर्णांक64_t reserved_32_35:4;
		uपूर्णांक64_t port_bit2:4;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_ipd_sub_port_fcs_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t port_bit:3;
#अन्यथा
		uपूर्णांक64_t port_bit:3;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_ipd_sub_port_fcs_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t port_bit:32;
#अन्यथा
		uपूर्णांक64_t port_bit:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn38xx;
पूर्ण;

जोड़ cvmx_ipd_sub_port_qos_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_sub_port_qos_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_41_63:23;
		uपूर्णांक64_t port_qos:9;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t port_qos:9;
		uपूर्णांक64_t reserved_41_63:23;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_wqe_fpa_queue अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_wqe_fpa_queue_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t wqe_pool:3;
#अन्यथा
		uपूर्णांक64_t wqe_pool:3;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ipd_wqe_ptr_valid अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ipd_wqe_ptr_valid_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t ptr:29;
#अन्यथा
		uपूर्णांक64_t ptr:29;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
