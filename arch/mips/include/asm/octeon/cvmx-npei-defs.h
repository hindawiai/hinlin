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

#अगर_अघोषित __CVMX_NPEI_DEFS_H__
#घोषणा __CVMX_NPEI_DEFS_H__

#घोषणा CVMX_NPEI_BAR1_INDEXX(offset) (0x0000000000000000ull + ((offset) & 31) * 16)
#घोषणा CVMX_NPEI_BIST_STATUS (0x0000000000000580ull)
#घोषणा CVMX_NPEI_BIST_STATUS2 (0x0000000000000680ull)
#घोषणा CVMX_NPEI_CTL_PORT0 (0x0000000000000250ull)
#घोषणा CVMX_NPEI_CTL_PORT1 (0x0000000000000260ull)
#घोषणा CVMX_NPEI_CTL_STATUS (0x0000000000000570ull)
#घोषणा CVMX_NPEI_CTL_STATUS2 (0x0000000000003C00ull)
#घोषणा CVMX_NPEI_DATA_OUT_CNT (0x00000000000005F0ull)
#घोषणा CVMX_NPEI_DBG_DATA (0x0000000000000510ull)
#घोषणा CVMX_NPEI_DBG_SELECT (0x0000000000000500ull)
#घोषणा CVMX_NPEI_DMA0_INT_LEVEL (0x00000000000005C0ull)
#घोषणा CVMX_NPEI_DMA1_INT_LEVEL (0x00000000000005D0ull)
#घोषणा CVMX_NPEI_DMAX_COUNTS(offset) (0x0000000000000450ull + ((offset) & 7) * 16)
#घोषणा CVMX_NPEI_DMAX_DBELL(offset) (0x00000000000003B0ull + ((offset) & 7) * 16)
#घोषणा CVMX_NPEI_DMAX_IBUFF_SADDR(offset) (0x0000000000000400ull + ((offset) & 7) * 16)
#घोषणा CVMX_NPEI_DMAX_NADDR(offset) (0x00000000000004A0ull + ((offset) & 7) * 16)
#घोषणा CVMX_NPEI_DMA_CNTS (0x00000000000005E0ull)
#घोषणा CVMX_NPEI_DMA_CONTROL (0x00000000000003A0ull)
#घोषणा CVMX_NPEI_DMA_PCIE_REQ_NUM (0x00000000000005B0ull)
#घोषणा CVMX_NPEI_DMA_STATE1 (0x00000000000006C0ull)
#घोषणा CVMX_NPEI_DMA_STATE1_P1 (0x0000000000000680ull)
#घोषणा CVMX_NPEI_DMA_STATE2 (0x00000000000006D0ull)
#घोषणा CVMX_NPEI_DMA_STATE2_P1 (0x0000000000000690ull)
#घोषणा CVMX_NPEI_DMA_STATE3_P1 (0x00000000000006A0ull)
#घोषणा CVMX_NPEI_DMA_STATE4_P1 (0x00000000000006B0ull)
#घोषणा CVMX_NPEI_DMA_STATE5_P1 (0x00000000000006C0ull)
#घोषणा CVMX_NPEI_INT_A_ENB (0x0000000000000560ull)
#घोषणा CVMX_NPEI_INT_A_ENB2 (0x0000000000003CE0ull)
#घोषणा CVMX_NPEI_INT_A_SUM (0x0000000000000550ull)
#घोषणा CVMX_NPEI_INT_ENB (0x0000000000000540ull)
#घोषणा CVMX_NPEI_INT_ENB2 (0x0000000000003CD0ull)
#घोषणा CVMX_NPEI_INT_INFO (0x0000000000000590ull)
#घोषणा CVMX_NPEI_INT_SUM (0x0000000000000530ull)
#घोषणा CVMX_NPEI_INT_SUM2 (0x0000000000003CC0ull)
#घोषणा CVMX_NPEI_LAST_WIN_RDATA0 (0x0000000000000600ull)
#घोषणा CVMX_NPEI_LAST_WIN_RDATA1 (0x0000000000000610ull)
#घोषणा CVMX_NPEI_MEM_ACCESS_CTL (0x00000000000004F0ull)
#घोषणा CVMX_NPEI_MEM_ACCESS_SUBIDX(offset) (0x0000000000000280ull + ((offset) & 31) * 16 - 16*12)
#घोषणा CVMX_NPEI_MSI_ENB0 (0x0000000000003C50ull)
#घोषणा CVMX_NPEI_MSI_ENB1 (0x0000000000003C60ull)
#घोषणा CVMX_NPEI_MSI_ENB2 (0x0000000000003C70ull)
#घोषणा CVMX_NPEI_MSI_ENB3 (0x0000000000003C80ull)
#घोषणा CVMX_NPEI_MSI_RCV0 (0x0000000000003C10ull)
#घोषणा CVMX_NPEI_MSI_RCV1 (0x0000000000003C20ull)
#घोषणा CVMX_NPEI_MSI_RCV2 (0x0000000000003C30ull)
#घोषणा CVMX_NPEI_MSI_RCV3 (0x0000000000003C40ull)
#घोषणा CVMX_NPEI_MSI_RD_MAP (0x0000000000003CA0ull)
#घोषणा CVMX_NPEI_MSI_W1C_ENB0 (0x0000000000003CF0ull)
#घोषणा CVMX_NPEI_MSI_W1C_ENB1 (0x0000000000003D00ull)
#घोषणा CVMX_NPEI_MSI_W1C_ENB2 (0x0000000000003D10ull)
#घोषणा CVMX_NPEI_MSI_W1C_ENB3 (0x0000000000003D20ull)
#घोषणा CVMX_NPEI_MSI_W1S_ENB0 (0x0000000000003D30ull)
#घोषणा CVMX_NPEI_MSI_W1S_ENB1 (0x0000000000003D40ull)
#घोषणा CVMX_NPEI_MSI_W1S_ENB2 (0x0000000000003D50ull)
#घोषणा CVMX_NPEI_MSI_W1S_ENB3 (0x0000000000003D60ull)
#घोषणा CVMX_NPEI_MSI_WR_MAP (0x0000000000003C90ull)
#घोषणा CVMX_NPEI_PCIE_CREDIT_CNT (0x0000000000003D70ull)
#घोषणा CVMX_NPEI_PCIE_MSI_RCV (0x0000000000003CB0ull)
#घोषणा CVMX_NPEI_PCIE_MSI_RCV_B1 (0x0000000000000650ull)
#घोषणा CVMX_NPEI_PCIE_MSI_RCV_B2 (0x0000000000000660ull)
#घोषणा CVMX_NPEI_PCIE_MSI_RCV_B3 (0x0000000000000670ull)
#घोषणा CVMX_NPEI_PKTX_CNTS(offset) (0x0000000000002400ull + ((offset) & 31) * 16)
#घोषणा CVMX_NPEI_PKTX_INSTR_BADDR(offset) (0x0000000000002800ull + ((offset) & 31) * 16)
#घोषणा CVMX_NPEI_PKTX_INSTR_BAOFF_DBELL(offset) (0x0000000000002C00ull + ((offset) & 31) * 16)
#घोषणा CVMX_NPEI_PKTX_INSTR_FIFO_RSIZE(offset) (0x0000000000003000ull + ((offset) & 31) * 16)
#घोषणा CVMX_NPEI_PKTX_INSTR_HEADER(offset) (0x0000000000003400ull + ((offset) & 31) * 16)
#घोषणा CVMX_NPEI_PKTX_IN_BP(offset) (0x0000000000003800ull + ((offset) & 31) * 16)
#घोषणा CVMX_NPEI_PKTX_SLIST_BADDR(offset) (0x0000000000001400ull + ((offset) & 31) * 16)
#घोषणा CVMX_NPEI_PKTX_SLIST_BAOFF_DBELL(offset) (0x0000000000001800ull + ((offset) & 31) * 16)
#घोषणा CVMX_NPEI_PKTX_SLIST_FIFO_RSIZE(offset) (0x0000000000001C00ull + ((offset) & 31) * 16)
#घोषणा CVMX_NPEI_PKT_CNT_INT (0x0000000000001110ull)
#घोषणा CVMX_NPEI_PKT_CNT_INT_ENB (0x0000000000001130ull)
#घोषणा CVMX_NPEI_PKT_DATA_OUT_ES (0x00000000000010B0ull)
#घोषणा CVMX_NPEI_PKT_DATA_OUT_NS (0x00000000000010A0ull)
#घोषणा CVMX_NPEI_PKT_DATA_OUT_ROR (0x0000000000001090ull)
#घोषणा CVMX_NPEI_PKT_DPADDR (0x0000000000001080ull)
#घोषणा CVMX_NPEI_PKT_INPUT_CONTROL (0x0000000000001150ull)
#घोषणा CVMX_NPEI_PKT_INSTR_ENB (0x0000000000001000ull)
#घोषणा CVMX_NPEI_PKT_INSTR_RD_SIZE (0x0000000000001190ull)
#घोषणा CVMX_NPEI_PKT_INSTR_SIZE (0x0000000000001020ull)
#घोषणा CVMX_NPEI_PKT_INT_LEVELS (0x0000000000001100ull)
#घोषणा CVMX_NPEI_PKT_IN_BP (0x00000000000006B0ull)
#घोषणा CVMX_NPEI_PKT_IN_DONEX_CNTS(offset) (0x0000000000002000ull + ((offset) & 31) * 16)
#घोषणा CVMX_NPEI_PKT_IN_INSTR_COUNTS (0x00000000000006A0ull)
#घोषणा CVMX_NPEI_PKT_IN_PCIE_PORT (0x00000000000011A0ull)
#घोषणा CVMX_NPEI_PKT_IPTR (0x0000000000001070ull)
#घोषणा CVMX_NPEI_PKT_OUTPUT_WMARK (0x0000000000001160ull)
#घोषणा CVMX_NPEI_PKT_OUT_BMODE (0x00000000000010D0ull)
#घोषणा CVMX_NPEI_PKT_OUT_ENB (0x0000000000001010ull)
#घोषणा CVMX_NPEI_PKT_PCIE_PORT (0x00000000000010E0ull)
#घोषणा CVMX_NPEI_PKT_PORT_IN_RST (0x0000000000000690ull)
#घोषणा CVMX_NPEI_PKT_SLIST_ES (0x0000000000001050ull)
#घोषणा CVMX_NPEI_PKT_SLIST_ID_SIZE (0x0000000000001180ull)
#घोषणा CVMX_NPEI_PKT_SLIST_NS (0x0000000000001040ull)
#घोषणा CVMX_NPEI_PKT_SLIST_ROR (0x0000000000001030ull)
#घोषणा CVMX_NPEI_PKT_TIME_INT (0x0000000000001120ull)
#घोषणा CVMX_NPEI_PKT_TIME_INT_ENB (0x0000000000001140ull)
#घोषणा CVMX_NPEI_RSL_INT_BLOCKS (0x0000000000000520ull)
#घोषणा CVMX_NPEI_SCRATCH_1 (0x0000000000000270ull)
#घोषणा CVMX_NPEI_STATE1 (0x0000000000000620ull)
#घोषणा CVMX_NPEI_STATE2 (0x0000000000000630ull)
#घोषणा CVMX_NPEI_STATE3 (0x0000000000000640ull)
#घोषणा CVMX_NPEI_WINDOW_CTL (0x0000000000000380ull)
#घोषणा CVMX_NPEI_WIN_RD_ADDR (0x0000000000000210ull)
#घोषणा CVMX_NPEI_WIN_RD_DATA (0x0000000000000240ull)
#घोषणा CVMX_NPEI_WIN_WR_ADDR (0x0000000000000200ull)
#घोषणा CVMX_NPEI_WIN_WR_DATA (0x0000000000000220ull)
#घोषणा CVMX_NPEI_WIN_WR_MASK (0x0000000000000230ull)

जोड़ cvmx_npei_bar1_indexx अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_npei_bar1_indexx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t reserved_18_31:14;
		uपूर्णांक32_t addr_idx:14;
		uपूर्णांक32_t ca:1;
		uपूर्णांक32_t end_swp:2;
		uपूर्णांक32_t addr_v:1;
#अन्यथा
		uपूर्णांक32_t addr_v:1;
		uपूर्णांक32_t end_swp:2;
		uपूर्णांक32_t ca:1;
		uपूर्णांक32_t addr_idx:14;
		uपूर्णांक32_t reserved_18_31:14;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_bist_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_bist_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t pkt_rdf:1;
		uपूर्णांक64_t reserved_60_62:3;
		uपूर्णांक64_t pcr_gim:1;
		uपूर्णांक64_t pkt_pअगर:1;
		uपूर्णांक64_t pcsr_पूर्णांक:1;
		uपूर्णांक64_t pcsr_im:1;
		uपूर्णांक64_t pcsr_cnt:1;
		uपूर्णांक64_t pcsr_id:1;
		uपूर्णांक64_t pcsr_sl:1;
		uपूर्णांक64_t reserved_50_52:3;
		uपूर्णांक64_t pkt_ind:1;
		uपूर्णांक64_t pkt_slm:1;
		uपूर्णांक64_t reserved_36_47:12;
		uपूर्णांक64_t d0_pst:1;
		uपूर्णांक64_t d1_pst:1;
		uपूर्णांक64_t d2_pst:1;
		uपूर्णांक64_t d3_pst:1;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t n2p0_c:1;
		uपूर्णांक64_t n2p0_o:1;
		uपूर्णांक64_t n2p1_c:1;
		uपूर्णांक64_t n2p1_o:1;
		uपूर्णांक64_t cpl_p0:1;
		uपूर्णांक64_t cpl_p1:1;
		uपूर्णांक64_t p2n1_po:1;
		uपूर्णांक64_t p2n1_no:1;
		uपूर्णांक64_t p2n1_co:1;
		uपूर्णांक64_t p2n0_po:1;
		uपूर्णांक64_t p2n0_no:1;
		uपूर्णांक64_t p2n0_co:1;
		uपूर्णांक64_t p2n0_c0:1;
		uपूर्णांक64_t p2n0_c1:1;
		uपूर्णांक64_t p2n0_n:1;
		uपूर्णांक64_t p2n0_p0:1;
		uपूर्णांक64_t p2n0_p1:1;
		uपूर्णांक64_t p2n1_c0:1;
		uपूर्णांक64_t p2n1_c1:1;
		uपूर्णांक64_t p2n1_n:1;
		uपूर्णांक64_t p2n1_p0:1;
		uपूर्णांक64_t p2n1_p1:1;
		uपूर्णांक64_t csm0:1;
		uपूर्णांक64_t csm1:1;
		uपूर्णांक64_t dअगर0:1;
		uपूर्णांक64_t dअगर1:1;
		uपूर्णांक64_t dअगर2:1;
		uपूर्णांक64_t dअगर3:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t msi:1;
		uपूर्णांक64_t ncb_cmd:1;
#अन्यथा
		uपूर्णांक64_t ncb_cmd:1;
		uपूर्णांक64_t msi:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t dअगर3:1;
		uपूर्णांक64_t dअगर2:1;
		uपूर्णांक64_t dअगर1:1;
		uपूर्णांक64_t dअगर0:1;
		uपूर्णांक64_t csm1:1;
		uपूर्णांक64_t csm0:1;
		uपूर्णांक64_t p2n1_p1:1;
		uपूर्णांक64_t p2n1_p0:1;
		uपूर्णांक64_t p2n1_n:1;
		uपूर्णांक64_t p2n1_c1:1;
		uपूर्णांक64_t p2n1_c0:1;
		uपूर्णांक64_t p2n0_p1:1;
		uपूर्णांक64_t p2n0_p0:1;
		uपूर्णांक64_t p2n0_n:1;
		uपूर्णांक64_t p2n0_c1:1;
		uपूर्णांक64_t p2n0_c0:1;
		uपूर्णांक64_t p2n0_co:1;
		uपूर्णांक64_t p2n0_no:1;
		uपूर्णांक64_t p2n0_po:1;
		uपूर्णांक64_t p2n1_co:1;
		uपूर्णांक64_t p2n1_no:1;
		uपूर्णांक64_t p2n1_po:1;
		uपूर्णांक64_t cpl_p1:1;
		uपूर्णांक64_t cpl_p0:1;
		uपूर्णांक64_t n2p1_o:1;
		uपूर्णांक64_t n2p1_c:1;
		uपूर्णांक64_t n2p0_o:1;
		uपूर्णांक64_t n2p0_c:1;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t d3_pst:1;
		uपूर्णांक64_t d2_pst:1;
		uपूर्णांक64_t d1_pst:1;
		uपूर्णांक64_t d0_pst:1;
		uपूर्णांक64_t reserved_36_47:12;
		uपूर्णांक64_t pkt_slm:1;
		uपूर्णांक64_t pkt_ind:1;
		uपूर्णांक64_t reserved_50_52:3;
		uपूर्णांक64_t pcsr_sl:1;
		uपूर्णांक64_t pcsr_id:1;
		uपूर्णांक64_t pcsr_cnt:1;
		uपूर्णांक64_t pcsr_im:1;
		uपूर्णांक64_t pcsr_पूर्णांक:1;
		uपूर्णांक64_t pkt_pअगर:1;
		uपूर्णांक64_t pcr_gim:1;
		uपूर्णांक64_t reserved_60_62:3;
		uपूर्णांक64_t pkt_rdf:1;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npei_bist_status_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t pkt_rdf:1;
		uपूर्णांक64_t reserved_60_62:3;
		uपूर्णांक64_t pcr_gim:1;
		uपूर्णांक64_t pkt_pअगर:1;
		uपूर्णांक64_t pcsr_पूर्णांक:1;
		uपूर्णांक64_t pcsr_im:1;
		uपूर्णांक64_t pcsr_cnt:1;
		uपूर्णांक64_t pcsr_id:1;
		uपूर्णांक64_t pcsr_sl:1;
		uपूर्णांक64_t pkt_imem:1;
		uपूर्णांक64_t pkt_pfm:1;
		uपूर्णांक64_t pkt_pof:1;
		uपूर्णांक64_t reserved_48_49:2;
		uपूर्णांक64_t pkt_pop0:1;
		uपूर्णांक64_t pkt_pop1:1;
		uपूर्णांक64_t d0_mem:1;
		uपूर्णांक64_t d1_mem:1;
		uपूर्णांक64_t d2_mem:1;
		uपूर्णांक64_t d3_mem:1;
		uपूर्णांक64_t d4_mem:1;
		uपूर्णांक64_t ds_mem:1;
		uपूर्णांक64_t reserved_36_39:4;
		uपूर्णांक64_t d0_pst:1;
		uपूर्णांक64_t d1_pst:1;
		uपूर्णांक64_t d2_pst:1;
		uपूर्णांक64_t d3_pst:1;
		uपूर्णांक64_t d4_pst:1;
		uपूर्णांक64_t n2p0_c:1;
		uपूर्णांक64_t n2p0_o:1;
		uपूर्णांक64_t n2p1_c:1;
		uपूर्णांक64_t n2p1_o:1;
		uपूर्णांक64_t cpl_p0:1;
		uपूर्णांक64_t cpl_p1:1;
		uपूर्णांक64_t p2n1_po:1;
		uपूर्णांक64_t p2n1_no:1;
		uपूर्णांक64_t p2n1_co:1;
		uपूर्णांक64_t p2n0_po:1;
		uपूर्णांक64_t p2n0_no:1;
		uपूर्णांक64_t p2n0_co:1;
		uपूर्णांक64_t p2n0_c0:1;
		uपूर्णांक64_t p2n0_c1:1;
		uपूर्णांक64_t p2n0_n:1;
		uपूर्णांक64_t p2n0_p0:1;
		uपूर्णांक64_t p2n0_p1:1;
		uपूर्णांक64_t p2n1_c0:1;
		uपूर्णांक64_t p2n1_c1:1;
		uपूर्णांक64_t p2n1_n:1;
		uपूर्णांक64_t p2n1_p0:1;
		uपूर्णांक64_t p2n1_p1:1;
		uपूर्णांक64_t csm0:1;
		uपूर्णांक64_t csm1:1;
		uपूर्णांक64_t dअगर0:1;
		uपूर्णांक64_t dअगर1:1;
		uपूर्णांक64_t dअगर2:1;
		uपूर्णांक64_t dअगर3:1;
		uपूर्णांक64_t dअगर4:1;
		uपूर्णांक64_t msi:1;
		uपूर्णांक64_t ncb_cmd:1;
#अन्यथा
		uपूर्णांक64_t ncb_cmd:1;
		uपूर्णांक64_t msi:1;
		uपूर्णांक64_t dअगर4:1;
		uपूर्णांक64_t dअगर3:1;
		uपूर्णांक64_t dअगर2:1;
		uपूर्णांक64_t dअगर1:1;
		uपूर्णांक64_t dअगर0:1;
		uपूर्णांक64_t csm1:1;
		uपूर्णांक64_t csm0:1;
		uपूर्णांक64_t p2n1_p1:1;
		uपूर्णांक64_t p2n1_p0:1;
		uपूर्णांक64_t p2n1_n:1;
		uपूर्णांक64_t p2n1_c1:1;
		uपूर्णांक64_t p2n1_c0:1;
		uपूर्णांक64_t p2n0_p1:1;
		uपूर्णांक64_t p2n0_p0:1;
		uपूर्णांक64_t p2n0_n:1;
		uपूर्णांक64_t p2n0_c1:1;
		uपूर्णांक64_t p2n0_c0:1;
		uपूर्णांक64_t p2n0_co:1;
		uपूर्णांक64_t p2n0_no:1;
		uपूर्णांक64_t p2n0_po:1;
		uपूर्णांक64_t p2n1_co:1;
		uपूर्णांक64_t p2n1_no:1;
		uपूर्णांक64_t p2n1_po:1;
		uपूर्णांक64_t cpl_p1:1;
		uपूर्णांक64_t cpl_p0:1;
		uपूर्णांक64_t n2p1_o:1;
		uपूर्णांक64_t n2p1_c:1;
		uपूर्णांक64_t n2p0_o:1;
		uपूर्णांक64_t n2p0_c:1;
		uपूर्णांक64_t d4_pst:1;
		uपूर्णांक64_t d3_pst:1;
		uपूर्णांक64_t d2_pst:1;
		uपूर्णांक64_t d1_pst:1;
		uपूर्णांक64_t d0_pst:1;
		uपूर्णांक64_t reserved_36_39:4;
		uपूर्णांक64_t ds_mem:1;
		uपूर्णांक64_t d4_mem:1;
		uपूर्णांक64_t d3_mem:1;
		uपूर्णांक64_t d2_mem:1;
		uपूर्णांक64_t d1_mem:1;
		uपूर्णांक64_t d0_mem:1;
		uपूर्णांक64_t pkt_pop1:1;
		uपूर्णांक64_t pkt_pop0:1;
		uपूर्णांक64_t reserved_48_49:2;
		uपूर्णांक64_t pkt_pof:1;
		uपूर्णांक64_t pkt_pfm:1;
		uपूर्णांक64_t pkt_imem:1;
		uपूर्णांक64_t pcsr_sl:1;
		uपूर्णांक64_t pcsr_id:1;
		uपूर्णांक64_t pcsr_cnt:1;
		uपूर्णांक64_t pcsr_im:1;
		uपूर्णांक64_t pcsr_पूर्णांक:1;
		uपूर्णांक64_t pkt_pअगर:1;
		uपूर्णांक64_t pcr_gim:1;
		uपूर्णांक64_t reserved_60_62:3;
		uपूर्णांक64_t pkt_rdf:1;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_npei_bist_status_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_46_63:18;
		uपूर्णांक64_t d0_mem0:1;
		uपूर्णांक64_t d1_mem1:1;
		uपूर्णांक64_t d2_mem2:1;
		uपूर्णांक64_t d3_mem3:1;
		uपूर्णांक64_t dr0_mem:1;
		uपूर्णांक64_t d0_mem:1;
		uपूर्णांक64_t d1_mem:1;
		uपूर्णांक64_t d2_mem:1;
		uपूर्णांक64_t d3_mem:1;
		uपूर्णांक64_t dr1_mem:1;
		uपूर्णांक64_t d0_pst:1;
		uपूर्णांक64_t d1_pst:1;
		uपूर्णांक64_t d2_pst:1;
		uपूर्णांक64_t d3_pst:1;
		uपूर्णांक64_t dr2_mem:1;
		uपूर्णांक64_t n2p0_c:1;
		uपूर्णांक64_t n2p0_o:1;
		uपूर्णांक64_t n2p1_c:1;
		uपूर्णांक64_t n2p1_o:1;
		uपूर्णांक64_t cpl_p0:1;
		uपूर्णांक64_t cpl_p1:1;
		uपूर्णांक64_t p2n1_po:1;
		uपूर्णांक64_t p2n1_no:1;
		uपूर्णांक64_t p2n1_co:1;
		uपूर्णांक64_t p2n0_po:1;
		uपूर्णांक64_t p2n0_no:1;
		uपूर्णांक64_t p2n0_co:1;
		uपूर्णांक64_t p2n0_c0:1;
		uपूर्णांक64_t p2n0_c1:1;
		uपूर्णांक64_t p2n0_n:1;
		uपूर्णांक64_t p2n0_p0:1;
		uपूर्णांक64_t p2n0_p1:1;
		uपूर्णांक64_t p2n1_c0:1;
		uपूर्णांक64_t p2n1_c1:1;
		uपूर्णांक64_t p2n1_n:1;
		uपूर्णांक64_t p2n1_p0:1;
		uपूर्णांक64_t p2n1_p1:1;
		uपूर्णांक64_t csm0:1;
		uपूर्णांक64_t csm1:1;
		uपूर्णांक64_t dअगर0:1;
		uपूर्णांक64_t dअगर1:1;
		uपूर्णांक64_t dअगर2:1;
		uपूर्णांक64_t dअगर3:1;
		uपूर्णांक64_t dr3_mem:1;
		uपूर्णांक64_t msi:1;
		uपूर्णांक64_t ncb_cmd:1;
#अन्यथा
		uपूर्णांक64_t ncb_cmd:1;
		uपूर्णांक64_t msi:1;
		uपूर्णांक64_t dr3_mem:1;
		uपूर्णांक64_t dअगर3:1;
		uपूर्णांक64_t dअगर2:1;
		uपूर्णांक64_t dअगर1:1;
		uपूर्णांक64_t dअगर0:1;
		uपूर्णांक64_t csm1:1;
		uपूर्णांक64_t csm0:1;
		uपूर्णांक64_t p2n1_p1:1;
		uपूर्णांक64_t p2n1_p0:1;
		uपूर्णांक64_t p2n1_n:1;
		uपूर्णांक64_t p2n1_c1:1;
		uपूर्णांक64_t p2n1_c0:1;
		uपूर्णांक64_t p2n0_p1:1;
		uपूर्णांक64_t p2n0_p0:1;
		uपूर्णांक64_t p2n0_n:1;
		uपूर्णांक64_t p2n0_c1:1;
		uपूर्णांक64_t p2n0_c0:1;
		uपूर्णांक64_t p2n0_co:1;
		uपूर्णांक64_t p2n0_no:1;
		uपूर्णांक64_t p2n0_po:1;
		uपूर्णांक64_t p2n1_co:1;
		uपूर्णांक64_t p2n1_no:1;
		uपूर्णांक64_t p2n1_po:1;
		uपूर्णांक64_t cpl_p1:1;
		uपूर्णांक64_t cpl_p0:1;
		uपूर्णांक64_t n2p1_o:1;
		uपूर्णांक64_t n2p1_c:1;
		uपूर्णांक64_t n2p0_o:1;
		uपूर्णांक64_t n2p0_c:1;
		uपूर्णांक64_t dr2_mem:1;
		uपूर्णांक64_t d3_pst:1;
		uपूर्णांक64_t d2_pst:1;
		uपूर्णांक64_t d1_pst:1;
		uपूर्णांक64_t d0_pst:1;
		uपूर्णांक64_t dr1_mem:1;
		uपूर्णांक64_t d3_mem:1;
		uपूर्णांक64_t d2_mem:1;
		uपूर्णांक64_t d1_mem:1;
		uपूर्णांक64_t d0_mem:1;
		uपूर्णांक64_t dr0_mem:1;
		uपूर्णांक64_t d3_mem3:1;
		uपूर्णांक64_t d2_mem2:1;
		uपूर्णांक64_t d1_mem1:1;
		uपूर्णांक64_t d0_mem0:1;
		uपूर्णांक64_t reserved_46_63:18;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
	काष्ठा cvmx_npei_bist_status_cn56xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_58_63:6;
		uपूर्णांक64_t pcsr_पूर्णांक:1;
		uपूर्णांक64_t pcsr_im:1;
		uपूर्णांक64_t pcsr_cnt:1;
		uपूर्णांक64_t pcsr_id:1;
		uपूर्णांक64_t pcsr_sl:1;
		uपूर्णांक64_t pkt_pout:1;
		uपूर्णांक64_t pkt_imem:1;
		uपूर्णांक64_t pkt_cnपंचांग:1;
		uपूर्णांक64_t pkt_ind:1;
		uपूर्णांक64_t pkt_slm:1;
		uपूर्णांक64_t pkt_odf:1;
		uपूर्णांक64_t pkt_oअगर:1;
		uपूर्णांक64_t pkt_out:1;
		uपूर्णांक64_t pkt_i0:1;
		uपूर्णांक64_t pkt_i1:1;
		uपूर्णांक64_t pkt_s0:1;
		uपूर्णांक64_t pkt_s1:1;
		uपूर्णांक64_t d0_mem:1;
		uपूर्णांक64_t d1_mem:1;
		uपूर्णांक64_t d2_mem:1;
		uपूर्णांक64_t d3_mem:1;
		uपूर्णांक64_t d4_mem:1;
		uपूर्णांक64_t d0_pst:1;
		uपूर्णांक64_t d1_pst:1;
		uपूर्णांक64_t d2_pst:1;
		uपूर्णांक64_t d3_pst:1;
		uपूर्णांक64_t d4_pst:1;
		uपूर्णांक64_t n2p0_c:1;
		uपूर्णांक64_t n2p0_o:1;
		uपूर्णांक64_t n2p1_c:1;
		uपूर्णांक64_t n2p1_o:1;
		uपूर्णांक64_t cpl_p0:1;
		uपूर्णांक64_t cpl_p1:1;
		uपूर्णांक64_t p2n1_po:1;
		uपूर्णांक64_t p2n1_no:1;
		uपूर्णांक64_t p2n1_co:1;
		uपूर्णांक64_t p2n0_po:1;
		uपूर्णांक64_t p2n0_no:1;
		uपूर्णांक64_t p2n0_co:1;
		uपूर्णांक64_t p2n0_c0:1;
		uपूर्णांक64_t p2n0_c1:1;
		uपूर्णांक64_t p2n0_n:1;
		uपूर्णांक64_t p2n0_p0:1;
		uपूर्णांक64_t p2n0_p1:1;
		uपूर्णांक64_t p2n1_c0:1;
		uपूर्णांक64_t p2n1_c1:1;
		uपूर्णांक64_t p2n1_n:1;
		uपूर्णांक64_t p2n1_p0:1;
		uपूर्णांक64_t p2n1_p1:1;
		uपूर्णांक64_t csm0:1;
		uपूर्णांक64_t csm1:1;
		uपूर्णांक64_t dअगर0:1;
		uपूर्णांक64_t dअगर1:1;
		uपूर्णांक64_t dअगर2:1;
		uपूर्णांक64_t dअगर3:1;
		uपूर्णांक64_t dअगर4:1;
		uपूर्णांक64_t msi:1;
		uपूर्णांक64_t ncb_cmd:1;
#अन्यथा
		uपूर्णांक64_t ncb_cmd:1;
		uपूर्णांक64_t msi:1;
		uपूर्णांक64_t dअगर4:1;
		uपूर्णांक64_t dअगर3:1;
		uपूर्णांक64_t dअगर2:1;
		uपूर्णांक64_t dअगर1:1;
		uपूर्णांक64_t dअगर0:1;
		uपूर्णांक64_t csm1:1;
		uपूर्णांक64_t csm0:1;
		uपूर्णांक64_t p2n1_p1:1;
		uपूर्णांक64_t p2n1_p0:1;
		uपूर्णांक64_t p2n1_n:1;
		uपूर्णांक64_t p2n1_c1:1;
		uपूर्णांक64_t p2n1_c0:1;
		uपूर्णांक64_t p2n0_p1:1;
		uपूर्णांक64_t p2n0_p0:1;
		uपूर्णांक64_t p2n0_n:1;
		uपूर्णांक64_t p2n0_c1:1;
		uपूर्णांक64_t p2n0_c0:1;
		uपूर्णांक64_t p2n0_co:1;
		uपूर्णांक64_t p2n0_no:1;
		uपूर्णांक64_t p2n0_po:1;
		uपूर्णांक64_t p2n1_co:1;
		uपूर्णांक64_t p2n1_no:1;
		uपूर्णांक64_t p2n1_po:1;
		uपूर्णांक64_t cpl_p1:1;
		uपूर्णांक64_t cpl_p0:1;
		uपूर्णांक64_t n2p1_o:1;
		uपूर्णांक64_t n2p1_c:1;
		uपूर्णांक64_t n2p0_o:1;
		uपूर्णांक64_t n2p0_c:1;
		uपूर्णांक64_t d4_pst:1;
		uपूर्णांक64_t d3_pst:1;
		uपूर्णांक64_t d2_pst:1;
		uपूर्णांक64_t d1_pst:1;
		uपूर्णांक64_t d0_pst:1;
		uपूर्णांक64_t d4_mem:1;
		uपूर्णांक64_t d3_mem:1;
		uपूर्णांक64_t d2_mem:1;
		uपूर्णांक64_t d1_mem:1;
		uपूर्णांक64_t d0_mem:1;
		uपूर्णांक64_t pkt_s1:1;
		uपूर्णांक64_t pkt_s0:1;
		uपूर्णांक64_t pkt_i1:1;
		uपूर्णांक64_t pkt_i0:1;
		uपूर्णांक64_t pkt_out:1;
		uपूर्णांक64_t pkt_oअगर:1;
		uपूर्णांक64_t pkt_odf:1;
		uपूर्णांक64_t pkt_slm:1;
		uपूर्णांक64_t pkt_ind:1;
		uपूर्णांक64_t pkt_cnपंचांग:1;
		uपूर्णांक64_t pkt_imem:1;
		uपूर्णांक64_t pkt_pout:1;
		uपूर्णांक64_t pcsr_sl:1;
		uपूर्णांक64_t pcsr_id:1;
		uपूर्णांक64_t pcsr_cnt:1;
		uपूर्णांक64_t pcsr_im:1;
		uपूर्णांक64_t pcsr_पूर्णांक:1;
		uपूर्णांक64_t reserved_58_63:6;
#पूर्ण_अगर
	पूर्ण cn56xxp1;
पूर्ण;

जोड़ cvmx_npei_bist_status2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_bist_status2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t prd_tag:1;
		uपूर्णांक64_t prd_st0:1;
		uपूर्णांक64_t prd_st1:1;
		uपूर्णांक64_t prd_err:1;
		uपूर्णांक64_t nrd_st:1;
		uपूर्णांक64_t nwe_st:1;
		uपूर्णांक64_t nwe_wr0:1;
		uपूर्णांक64_t nwe_wr1:1;
		uपूर्णांक64_t pkt_rd:1;
		uपूर्णांक64_t psc_p0:1;
		uपूर्णांक64_t psc_p1:1;
		uपूर्णांक64_t pkt_gd:1;
		uपूर्णांक64_t pkt_gl:1;
		uपूर्णांक64_t pkt_blk:1;
#अन्यथा
		uपूर्णांक64_t pkt_blk:1;
		uपूर्णांक64_t pkt_gl:1;
		uपूर्णांक64_t pkt_gd:1;
		uपूर्णांक64_t psc_p1:1;
		uपूर्णांक64_t psc_p0:1;
		uपूर्णांक64_t pkt_rd:1;
		uपूर्णांक64_t nwe_wr1:1;
		uपूर्णांक64_t nwe_wr0:1;
		uपूर्णांक64_t nwe_st:1;
		uपूर्णांक64_t nrd_st:1;
		uपूर्णांक64_t prd_err:1;
		uपूर्णांक64_t prd_st1:1;
		uपूर्णांक64_t prd_st0:1;
		uपूर्णांक64_t prd_tag:1;
		uपूर्णांक64_t reserved_14_63:50;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_ctl_port0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_ctl_port0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_21_63:43;
		uपूर्णांक64_t रुकोl_com:1;
		uपूर्णांक64_t पूर्णांकd:1;
		uपूर्णांक64_t पूर्णांकc:1;
		uपूर्णांक64_t पूर्णांकb:1;
		uपूर्णांक64_t पूर्णांकa:1;
		uपूर्णांक64_t पूर्णांकd_map:2;
		uपूर्णांक64_t पूर्णांकc_map:2;
		uपूर्णांक64_t पूर्णांकb_map:2;
		uपूर्णांक64_t पूर्णांकa_map:2;
		uपूर्णांक64_t ctlp_ro:1;
		uपूर्णांक64_t reserved_6_6:1;
		uपूर्णांक64_t ptlp_ro:1;
		uपूर्णांक64_t bar2_enb:1;
		uपूर्णांक64_t bar2_esx:2;
		uपूर्णांक64_t bar2_cax:1;
		uपूर्णांक64_t रुको_com:1;
#अन्यथा
		uपूर्णांक64_t रुको_com:1;
		uपूर्णांक64_t bar2_cax:1;
		uपूर्णांक64_t bar2_esx:2;
		uपूर्णांक64_t bar2_enb:1;
		uपूर्णांक64_t ptlp_ro:1;
		uपूर्णांक64_t reserved_6_6:1;
		uपूर्णांक64_t ctlp_ro:1;
		uपूर्णांक64_t पूर्णांकa_map:2;
		uपूर्णांक64_t पूर्णांकb_map:2;
		uपूर्णांक64_t पूर्णांकc_map:2;
		uपूर्णांक64_t पूर्णांकd_map:2;
		uपूर्णांक64_t पूर्णांकa:1;
		uपूर्णांक64_t पूर्णांकb:1;
		uपूर्णांक64_t पूर्णांकc:1;
		uपूर्णांक64_t पूर्णांकd:1;
		uपूर्णांक64_t रुकोl_com:1;
		uपूर्णांक64_t reserved_21_63:43;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_ctl_port1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_ctl_port1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_21_63:43;
		uपूर्णांक64_t रुकोl_com:1;
		uपूर्णांक64_t पूर्णांकd:1;
		uपूर्णांक64_t पूर्णांकc:1;
		uपूर्णांक64_t पूर्णांकb:1;
		uपूर्णांक64_t पूर्णांकa:1;
		uपूर्णांक64_t पूर्णांकd_map:2;
		uपूर्णांक64_t पूर्णांकc_map:2;
		uपूर्णांक64_t पूर्णांकb_map:2;
		uपूर्णांक64_t पूर्णांकa_map:2;
		uपूर्णांक64_t ctlp_ro:1;
		uपूर्णांक64_t reserved_6_6:1;
		uपूर्णांक64_t ptlp_ro:1;
		uपूर्णांक64_t bar2_enb:1;
		uपूर्णांक64_t bar2_esx:2;
		uपूर्णांक64_t bar2_cax:1;
		uपूर्णांक64_t रुको_com:1;
#अन्यथा
		uपूर्णांक64_t रुको_com:1;
		uपूर्णांक64_t bar2_cax:1;
		uपूर्णांक64_t bar2_esx:2;
		uपूर्णांक64_t bar2_enb:1;
		uपूर्णांक64_t ptlp_ro:1;
		uपूर्णांक64_t reserved_6_6:1;
		uपूर्णांक64_t ctlp_ro:1;
		uपूर्णांक64_t पूर्णांकa_map:2;
		uपूर्णांक64_t पूर्णांकb_map:2;
		uपूर्णांक64_t पूर्णांकc_map:2;
		uपूर्णांक64_t पूर्णांकd_map:2;
		uपूर्णांक64_t पूर्णांकa:1;
		uपूर्णांक64_t पूर्णांकb:1;
		uपूर्णांक64_t पूर्णांकc:1;
		uपूर्णांक64_t पूर्णांकd:1;
		uपूर्णांक64_t रुकोl_com:1;
		uपूर्णांक64_t reserved_21_63:43;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_ctl_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_ctl_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t p1_ntags:6;
		uपूर्णांक64_t p0_ntags:6;
		uपूर्णांक64_t cfg_rtry:16;
		uपूर्णांक64_t ring_en:1;
		uपूर्णांक64_t lnk_rst:1;
		uपूर्णांक64_t arb:1;
		uपूर्णांक64_t pkt_bp:4;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t chip_rev:8;
#अन्यथा
		uपूर्णांक64_t chip_rev:8;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t pkt_bp:4;
		uपूर्णांक64_t arb:1;
		uपूर्णांक64_t lnk_rst:1;
		uपूर्णांक64_t ring_en:1;
		uपूर्णांक64_t cfg_rtry:16;
		uपूर्णांक64_t p0_ntags:6;
		uपूर्णांक64_t p1_ntags:6;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npei_ctl_status_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t p1_ntags:6;
		uपूर्णांक64_t p0_ntags:6;
		uपूर्णांक64_t cfg_rtry:16;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t lnk_rst:1;
		uपूर्णांक64_t arb:1;
		uपूर्णांक64_t reserved_9_12:4;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t chip_rev:8;
#अन्यथा
		uपूर्णांक64_t chip_rev:8;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t reserved_9_12:4;
		uपूर्णांक64_t arb:1;
		uपूर्णांक64_t lnk_rst:1;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t cfg_rtry:16;
		uपूर्णांक64_t p0_ntags:6;
		uपूर्णांक64_t p1_ntags:6;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
	काष्ठा cvmx_npei_ctl_status_cn56xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_15_63:49;
		uपूर्णांक64_t lnk_rst:1;
		uपूर्णांक64_t arb:1;
		uपूर्णांक64_t pkt_bp:4;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t chip_rev:8;
#अन्यथा
		uपूर्णांक64_t chip_rev:8;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t pkt_bp:4;
		uपूर्णांक64_t arb:1;
		uपूर्णांक64_t lnk_rst:1;
		uपूर्णांक64_t reserved_15_63:49;
#पूर्ण_अगर
	पूर्ण cn56xxp1;
पूर्ण;

जोड़ cvmx_npei_ctl_status2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_ctl_status2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t mps:1;
		uपूर्णांक64_t mrrs:3;
		uपूर्णांक64_t c1_w_flt:1;
		uपूर्णांक64_t c0_w_flt:1;
		uपूर्णांक64_t c1_b1_s:3;
		uपूर्णांक64_t c0_b1_s:3;
		uपूर्णांक64_t c1_wi_d:1;
		uपूर्णांक64_t c1_b0_d:1;
		uपूर्णांक64_t c0_wi_d:1;
		uपूर्णांक64_t c0_b0_d:1;
#अन्यथा
		uपूर्णांक64_t c0_b0_d:1;
		uपूर्णांक64_t c0_wi_d:1;
		uपूर्णांक64_t c1_b0_d:1;
		uपूर्णांक64_t c1_wi_d:1;
		uपूर्णांक64_t c0_b1_s:3;
		uपूर्णांक64_t c1_b1_s:3;
		uपूर्णांक64_t c0_w_flt:1;
		uपूर्णांक64_t c1_w_flt:1;
		uपूर्णांक64_t mrrs:3;
		uपूर्णांक64_t mps:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_data_out_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_data_out_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t p1_ucnt:16;
		uपूर्णांक64_t p1_fcnt:6;
		uपूर्णांक64_t p0_ucnt:16;
		uपूर्णांक64_t p0_fcnt:6;
#अन्यथा
		uपूर्णांक64_t p0_fcnt:6;
		uपूर्णांक64_t p0_ucnt:16;
		uपूर्णांक64_t p1_fcnt:6;
		uपूर्णांक64_t p1_ucnt:16;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_dbg_data अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dbg_data_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t qlm0_rev_lanes:1;
		uपूर्णांक64_t reserved_25_26:2;
		uपूर्णांक64_t qlm1_spd:2;
		uपूर्णांक64_t c_mul:5;
		uपूर्णांक64_t dsel_ext:1;
		uपूर्णांक64_t data:17;
#अन्यथा
		uपूर्णांक64_t data:17;
		uपूर्णांक64_t dsel_ext:1;
		uपूर्णांक64_t c_mul:5;
		uपूर्णांक64_t qlm1_spd:2;
		uपूर्णांक64_t reserved_25_26:2;
		uपूर्णांक64_t qlm0_rev_lanes:1;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npei_dbg_data_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t qlm0_link_width:1;
		uपूर्णांक64_t qlm0_rev_lanes:1;
		uपूर्णांक64_t qlm1_mode:2;
		uपूर्णांक64_t qlm1_spd:2;
		uपूर्णांक64_t c_mul:5;
		uपूर्णांक64_t dsel_ext:1;
		uपूर्णांक64_t data:17;
#अन्यथा
		uपूर्णांक64_t data:17;
		uपूर्णांक64_t dsel_ext:1;
		uपूर्णांक64_t c_mul:5;
		uपूर्णांक64_t qlm1_spd:2;
		uपूर्णांक64_t qlm1_mode:2;
		uपूर्णांक64_t qlm0_rev_lanes:1;
		uपूर्णांक64_t qlm0_link_width:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_npei_dbg_data_cn56xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t qlm2_rev_lanes:1;
		uपूर्णांक64_t qlm0_rev_lanes:1;
		uपूर्णांक64_t qlm3_spd:2;
		uपूर्णांक64_t qlm1_spd:2;
		uपूर्णांक64_t c_mul:5;
		uपूर्णांक64_t dsel_ext:1;
		uपूर्णांक64_t data:17;
#अन्यथा
		uपूर्णांक64_t data:17;
		uपूर्णांक64_t dsel_ext:1;
		uपूर्णांक64_t c_mul:5;
		uपूर्णांक64_t qlm1_spd:2;
		uपूर्णांक64_t qlm3_spd:2;
		uपूर्णांक64_t qlm0_rev_lanes:1;
		uपूर्णांक64_t qlm2_rev_lanes:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn56xx;
पूर्ण;

जोड़ cvmx_npei_dbg_select अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dbg_select_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t dbg_sel:16;
#अन्यथा
		uपूर्णांक64_t dbg_sel:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_dmax_counts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dmax_counts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_39_63:25;
		uपूर्णांक64_t fcnt:7;
		uपूर्णांक64_t dbell:32;
#अन्यथा
		uपूर्णांक64_t dbell:32;
		uपूर्णांक64_t fcnt:7;
		uपूर्णांक64_t reserved_39_63:25;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_dmax_dbell अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_npei_dmax_dbell_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t reserved_16_31:16;
		uपूर्णांक32_t dbell:16;
#अन्यथा
		uपूर्णांक32_t dbell:16;
		uपूर्णांक32_t reserved_16_31:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_dmax_ibuff_saddr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dmax_ibuff_saddr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_37_63:27;
		uपूर्णांक64_t idle:1;
		uपूर्णांक64_t saddr:29;
		uपूर्णांक64_t reserved_0_6:7;
#अन्यथा
		uपूर्णांक64_t reserved_0_6:7;
		uपूर्णांक64_t saddr:29;
		uपूर्णांक64_t idle:1;
		uपूर्णांक64_t reserved_37_63:27;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npei_dmax_ibuff_saddr_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_36_63:28;
		uपूर्णांक64_t saddr:29;
		uपूर्णांक64_t reserved_0_6:7;
#अन्यथा
		uपूर्णांक64_t reserved_0_6:7;
		uपूर्णांक64_t saddr:29;
		uपूर्णांक64_t reserved_36_63:28;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
पूर्ण;

जोड़ cvmx_npei_dmax_naddr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dmax_naddr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_36_63:28;
		uपूर्णांक64_t addr:36;
#अन्यथा
		uपूर्णांक64_t addr:36;
		uपूर्णांक64_t reserved_36_63:28;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_dma0_पूर्णांक_level अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dma0_पूर्णांक_level_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t समय:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t समय:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_dma1_पूर्णांक_level अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dma1_पूर्णांक_level_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t समय:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t समय:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_dma_cnts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dma_cnts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t dma1:32;
		uपूर्णांक64_t dma0:32;
#अन्यथा
		uपूर्णांक64_t dma0:32;
		uपूर्णांक64_t dma1:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_dma_control अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dma_control_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t p_32b_m:1;
		uपूर्णांक64_t dma4_enb:1;
		uपूर्णांक64_t dma3_enb:1;
		uपूर्णांक64_t dma2_enb:1;
		uपूर्णांक64_t dma1_enb:1;
		uपूर्णांक64_t dma0_enb:1;
		uपूर्णांक64_t b0_lend:1;
		uपूर्णांक64_t dwb_denb:1;
		uपूर्णांक64_t dwb_ichk:9;
		uपूर्णांक64_t fpa_que:3;
		uपूर्णांक64_t o_add1:1;
		uपूर्णांक64_t o_ro:1;
		uपूर्णांक64_t o_ns:1;
		uपूर्णांक64_t o_es:2;
		uपूर्णांक64_t o_mode:1;
		uपूर्णांक64_t csize:14;
#अन्यथा
		uपूर्णांक64_t csize:14;
		uपूर्णांक64_t o_mode:1;
		uपूर्णांक64_t o_es:2;
		uपूर्णांक64_t o_ns:1;
		uपूर्णांक64_t o_ro:1;
		uपूर्णांक64_t o_add1:1;
		uपूर्णांक64_t fpa_que:3;
		uपूर्णांक64_t dwb_ichk:9;
		uपूर्णांक64_t dwb_denb:1;
		uपूर्णांक64_t b0_lend:1;
		uपूर्णांक64_t dma0_enb:1;
		uपूर्णांक64_t dma1_enb:1;
		uपूर्णांक64_t dma2_enb:1;
		uपूर्णांक64_t dma3_enb:1;
		uपूर्णांक64_t dma4_enb:1;
		uपूर्णांक64_t p_32b_m:1;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npei_dma_control_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_38_63:26;
		uपूर्णांक64_t dma3_enb:1;
		uपूर्णांक64_t dma2_enb:1;
		uपूर्णांक64_t dma1_enb:1;
		uपूर्णांक64_t dma0_enb:1;
		uपूर्णांक64_t b0_lend:1;
		uपूर्णांक64_t dwb_denb:1;
		uपूर्णांक64_t dwb_ichk:9;
		uपूर्णांक64_t fpa_que:3;
		uपूर्णांक64_t o_add1:1;
		uपूर्णांक64_t o_ro:1;
		uपूर्णांक64_t o_ns:1;
		uपूर्णांक64_t o_es:2;
		uपूर्णांक64_t o_mode:1;
		uपूर्णांक64_t csize:14;
#अन्यथा
		uपूर्णांक64_t csize:14;
		uपूर्णांक64_t o_mode:1;
		uपूर्णांक64_t o_es:2;
		uपूर्णांक64_t o_ns:1;
		uपूर्णांक64_t o_ro:1;
		uपूर्णांक64_t o_add1:1;
		uपूर्णांक64_t fpa_que:3;
		uपूर्णांक64_t dwb_ichk:9;
		uपूर्णांक64_t dwb_denb:1;
		uपूर्णांक64_t b0_lend:1;
		uपूर्णांक64_t dma0_enb:1;
		uपूर्णांक64_t dma1_enb:1;
		uपूर्णांक64_t dma2_enb:1;
		uपूर्णांक64_t dma3_enb:1;
		uपूर्णांक64_t reserved_38_63:26;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
	काष्ठा cvmx_npei_dma_control_cn56xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_39_63:25;
		uपूर्णांक64_t dma4_enb:1;
		uपूर्णांक64_t dma3_enb:1;
		uपूर्णांक64_t dma2_enb:1;
		uपूर्णांक64_t dma1_enb:1;
		uपूर्णांक64_t dma0_enb:1;
		uपूर्णांक64_t b0_lend:1;
		uपूर्णांक64_t dwb_denb:1;
		uपूर्णांक64_t dwb_ichk:9;
		uपूर्णांक64_t fpa_que:3;
		uपूर्णांक64_t o_add1:1;
		uपूर्णांक64_t o_ro:1;
		uपूर्णांक64_t o_ns:1;
		uपूर्णांक64_t o_es:2;
		uपूर्णांक64_t o_mode:1;
		uपूर्णांक64_t csize:14;
#अन्यथा
		uपूर्णांक64_t csize:14;
		uपूर्णांक64_t o_mode:1;
		uपूर्णांक64_t o_es:2;
		uपूर्णांक64_t o_ns:1;
		uपूर्णांक64_t o_ro:1;
		uपूर्णांक64_t o_add1:1;
		uपूर्णांक64_t fpa_que:3;
		uपूर्णांक64_t dwb_ichk:9;
		uपूर्णांक64_t dwb_denb:1;
		uपूर्णांक64_t b0_lend:1;
		uपूर्णांक64_t dma0_enb:1;
		uपूर्णांक64_t dma1_enb:1;
		uपूर्णांक64_t dma2_enb:1;
		uपूर्णांक64_t dma3_enb:1;
		uपूर्णांक64_t dma4_enb:1;
		uपूर्णांक64_t reserved_39_63:25;
#पूर्ण_अगर
	पूर्ण cn56xxp1;
पूर्ण;

जोड़ cvmx_npei_dma_pcie_req_num अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dma_pcie_req_num_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t dma_arb:1;
		uपूर्णांक64_t reserved_53_62:10;
		uपूर्णांक64_t pkt_cnt:5;
		uपूर्णांक64_t reserved_45_47:3;
		uपूर्णांक64_t dma4_cnt:5;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t dma3_cnt:5;
		uपूर्णांक64_t reserved_29_31:3;
		uपूर्णांक64_t dma2_cnt:5;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t dma1_cnt:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t dma0_cnt:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t dma_cnt:5;
#अन्यथा
		uपूर्णांक64_t dma_cnt:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t dma0_cnt:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t dma1_cnt:5;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t dma2_cnt:5;
		uपूर्णांक64_t reserved_29_31:3;
		uपूर्णांक64_t dma3_cnt:5;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t dma4_cnt:5;
		uपूर्णांक64_t reserved_45_47:3;
		uपूर्णांक64_t pkt_cnt:5;
		uपूर्णांक64_t reserved_53_62:10;
		uपूर्णांक64_t dma_arb:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_dma_state1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dma_state1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t d4_dwe:8;
		uपूर्णांक64_t d3_dwe:8;
		uपूर्णांक64_t d2_dwe:8;
		uपूर्णांक64_t d1_dwe:8;
		uपूर्णांक64_t d0_dwe:8;
#अन्यथा
		uपूर्णांक64_t d0_dwe:8;
		uपूर्णांक64_t d1_dwe:8;
		uपूर्णांक64_t d2_dwe:8;
		uपूर्णांक64_t d3_dwe:8;
		uपूर्णांक64_t d4_dwe:8;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_dma_state1_p1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dma_state1_p1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_60_63:4;
		uपूर्णांक64_t d0_dअगरst:7;
		uपूर्णांक64_t d1_dअगरst:7;
		uपूर्णांक64_t d2_dअगरst:7;
		uपूर्णांक64_t d3_dअगरst:7;
		uपूर्णांक64_t d4_dअगरst:7;
		uपूर्णांक64_t d0_reqst:5;
		uपूर्णांक64_t d1_reqst:5;
		uपूर्णांक64_t d2_reqst:5;
		uपूर्णांक64_t d3_reqst:5;
		uपूर्णांक64_t d4_reqst:5;
#अन्यथा
		uपूर्णांक64_t d4_reqst:5;
		uपूर्णांक64_t d3_reqst:5;
		uपूर्णांक64_t d2_reqst:5;
		uपूर्णांक64_t d1_reqst:5;
		uपूर्णांक64_t d0_reqst:5;
		uपूर्णांक64_t d4_dअगरst:7;
		uपूर्णांक64_t d3_dअगरst:7;
		uपूर्णांक64_t d2_dअगरst:7;
		uपूर्णांक64_t d1_dअगरst:7;
		uपूर्णांक64_t d0_dअगरst:7;
		uपूर्णांक64_t reserved_60_63:4;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npei_dma_state1_p1_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_60_63:4;
		uपूर्णांक64_t d0_dअगरst:7;
		uपूर्णांक64_t d1_dअगरst:7;
		uपूर्णांक64_t d2_dअगरst:7;
		uपूर्णांक64_t d3_dअगरst:7;
		uपूर्णांक64_t reserved_25_31:7;
		uपूर्णांक64_t d0_reqst:5;
		uपूर्णांक64_t d1_reqst:5;
		uपूर्णांक64_t d2_reqst:5;
		uपूर्णांक64_t d3_reqst:5;
		uपूर्णांक64_t reserved_0_4:5;
#अन्यथा
		uपूर्णांक64_t reserved_0_4:5;
		uपूर्णांक64_t d3_reqst:5;
		uपूर्णांक64_t d2_reqst:5;
		uपूर्णांक64_t d1_reqst:5;
		uपूर्णांक64_t d0_reqst:5;
		uपूर्णांक64_t reserved_25_31:7;
		uपूर्णांक64_t d3_dअगरst:7;
		uपूर्णांक64_t d2_dअगरst:7;
		uपूर्णांक64_t d1_dअगरst:7;
		uपूर्णांक64_t d0_dअगरst:7;
		uपूर्णांक64_t reserved_60_63:4;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
पूर्ण;

जोड़ cvmx_npei_dma_state2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dma_state2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t ndwe:4;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t ndre:5;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t prd:10;
#अन्यथा
		uपूर्णांक64_t prd:10;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t ndre:5;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t ndwe:4;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_dma_state2_p1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dma_state2_p1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_45_63:19;
		uपूर्णांक64_t d0_dffst:9;
		uपूर्णांक64_t d1_dffst:9;
		uपूर्णांक64_t d2_dffst:9;
		uपूर्णांक64_t d3_dffst:9;
		uपूर्णांक64_t d4_dffst:9;
#अन्यथा
		uपूर्णांक64_t d4_dffst:9;
		uपूर्णांक64_t d3_dffst:9;
		uपूर्णांक64_t d2_dffst:9;
		uपूर्णांक64_t d1_dffst:9;
		uपूर्णांक64_t d0_dffst:9;
		uपूर्णांक64_t reserved_45_63:19;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npei_dma_state2_p1_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_45_63:19;
		uपूर्णांक64_t d0_dffst:9;
		uपूर्णांक64_t d1_dffst:9;
		uपूर्णांक64_t d2_dffst:9;
		uपूर्णांक64_t d3_dffst:9;
		uपूर्णांक64_t reserved_0_8:9;
#अन्यथा
		uपूर्णांक64_t reserved_0_8:9;
		uपूर्णांक64_t d3_dffst:9;
		uपूर्णांक64_t d2_dffst:9;
		uपूर्णांक64_t d1_dffst:9;
		uपूर्णांक64_t d0_dffst:9;
		uपूर्णांक64_t reserved_45_63:19;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
पूर्ण;

जोड़ cvmx_npei_dma_state3_p1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dma_state3_p1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_60_63:4;
		uपूर्णांक64_t d0_drest:15;
		uपूर्णांक64_t d1_drest:15;
		uपूर्णांक64_t d2_drest:15;
		uपूर्णांक64_t d3_drest:15;
#अन्यथा
		uपूर्णांक64_t d3_drest:15;
		uपूर्णांक64_t d2_drest:15;
		uपूर्णांक64_t d1_drest:15;
		uपूर्णांक64_t d0_drest:15;
		uपूर्णांक64_t reserved_60_63:4;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_dma_state4_p1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dma_state4_p1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_52_63:12;
		uपूर्णांक64_t d0_dwest:13;
		uपूर्णांक64_t d1_dwest:13;
		uपूर्णांक64_t d2_dwest:13;
		uपूर्णांक64_t d3_dwest:13;
#अन्यथा
		uपूर्णांक64_t d3_dwest:13;
		uपूर्णांक64_t d2_dwest:13;
		uपूर्णांक64_t d1_dwest:13;
		uपूर्णांक64_t d0_dwest:13;
		uपूर्णांक64_t reserved_52_63:12;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_dma_state5_p1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_dma_state5_p1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t d4_drest:15;
		uपूर्णांक64_t d4_dwest:13;
#अन्यथा
		uपूर्णांक64_t d4_dwest:13;
		uपूर्णांक64_t d4_drest:15;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_पूर्णांक_a_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_पूर्णांक_a_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t pout_err:1;
		uपूर्णांक64_t pin_bp:1;
		uपूर्णांक64_t p1_rdlk:1;
		uपूर्णांक64_t p0_rdlk:1;
		uपूर्णांक64_t pgl_err:1;
		uपूर्णांक64_t pdi_err:1;
		uपूर्णांक64_t pop_err:1;
		uपूर्णांक64_t pins_err:1;
		uपूर्णांक64_t dma1_cpl:1;
		uपूर्णांक64_t dma0_cpl:1;
#अन्यथा
		uपूर्णांक64_t dma0_cpl:1;
		uपूर्णांक64_t dma1_cpl:1;
		uपूर्णांक64_t pins_err:1;
		uपूर्णांक64_t pop_err:1;
		uपूर्णांक64_t pdi_err:1;
		uपूर्णांक64_t pgl_err:1;
		uपूर्णांक64_t p0_rdlk:1;
		uपूर्णांक64_t p1_rdlk:1;
		uपूर्णांक64_t pin_bp:1;
		uपूर्णांक64_t pout_err:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npei_पूर्णांक_a_enb_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t dma1_cpl:1;
		uपूर्णांक64_t dma0_cpl:1;
#अन्यथा
		uपूर्णांक64_t dma0_cpl:1;
		uपूर्णांक64_t dma1_cpl:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
पूर्ण;

जोड़ cvmx_npei_पूर्णांक_a_enb2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_पूर्णांक_a_enb2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t pout_err:1;
		uपूर्णांक64_t pin_bp:1;
		uपूर्णांक64_t p1_rdlk:1;
		uपूर्णांक64_t p0_rdlk:1;
		uपूर्णांक64_t pgl_err:1;
		uपूर्णांक64_t pdi_err:1;
		uपूर्णांक64_t pop_err:1;
		uपूर्णांक64_t pins_err:1;
		uपूर्णांक64_t dma1_cpl:1;
		uपूर्णांक64_t dma0_cpl:1;
#अन्यथा
		uपूर्णांक64_t dma0_cpl:1;
		uपूर्णांक64_t dma1_cpl:1;
		uपूर्णांक64_t pins_err:1;
		uपूर्णांक64_t pop_err:1;
		uपूर्णांक64_t pdi_err:1;
		uपूर्णांक64_t pgl_err:1;
		uपूर्णांक64_t p0_rdlk:1;
		uपूर्णांक64_t p1_rdlk:1;
		uपूर्णांक64_t pin_bp:1;
		uपूर्णांक64_t pout_err:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npei_पूर्णांक_a_enb2_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t dma1_cpl:1;
		uपूर्णांक64_t dma0_cpl:1;
#अन्यथा
		uपूर्णांक64_t dma0_cpl:1;
		uपूर्णांक64_t dma1_cpl:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
पूर्ण;

जोड़ cvmx_npei_पूर्णांक_a_sum अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_पूर्णांक_a_sum_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t pout_err:1;
		uपूर्णांक64_t pin_bp:1;
		uपूर्णांक64_t p1_rdlk:1;
		uपूर्णांक64_t p0_rdlk:1;
		uपूर्णांक64_t pgl_err:1;
		uपूर्णांक64_t pdi_err:1;
		uपूर्णांक64_t pop_err:1;
		uपूर्णांक64_t pins_err:1;
		uपूर्णांक64_t dma1_cpl:1;
		uपूर्णांक64_t dma0_cpl:1;
#अन्यथा
		uपूर्णांक64_t dma0_cpl:1;
		uपूर्णांक64_t dma1_cpl:1;
		uपूर्णांक64_t pins_err:1;
		uपूर्णांक64_t pop_err:1;
		uपूर्णांक64_t pdi_err:1;
		uपूर्णांक64_t pgl_err:1;
		uपूर्णांक64_t p0_rdlk:1;
		uपूर्णांक64_t p1_rdlk:1;
		uपूर्णांक64_t pin_bp:1;
		uपूर्णांक64_t pout_err:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npei_पूर्णांक_a_sum_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t dma1_cpl:1;
		uपूर्णांक64_t dma0_cpl:1;
#अन्यथा
		uपूर्णांक64_t dma0_cpl:1;
		uपूर्णांक64_t dma1_cpl:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
पूर्ण;

जोड़ cvmx_npei_पूर्णांक_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_पूर्णांक_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t mio_पूर्णांकa:1;
		uपूर्णांक64_t reserved_62_62:1;
		uपूर्णांक64_t पूर्णांक_a:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t crs1_dr:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t crs1_er:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t crs0_dr:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t crs0_er:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t pcnt:1;
		uपूर्णांक64_t pidbof:1;
		uपूर्णांक64_t psldbof:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma4dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma4dbo:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t psldbof:1;
		uपूर्णांक64_t pidbof:1;
		uपूर्णांक64_t pcnt:1;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t crs0_er:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t crs0_dr:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t crs1_er:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t crs1_dr:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t पूर्णांक_a:1;
		uपूर्णांक64_t reserved_62_62:1;
		uपूर्णांक64_t mio_पूर्णांकa:1;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npei_पूर्णांक_enb_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t mio_पूर्णांकa:1;
		uपूर्णांक64_t reserved_62_62:1;
		uपूर्णांक64_t पूर्णांक_a:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t crs1_dr:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t crs1_er:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t crs0_dr:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t crs0_er:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t pcnt:1;
		uपूर्णांक64_t pidbof:1;
		uपूर्णांक64_t psldbof:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t psldbof:1;
		uपूर्णांक64_t pidbof:1;
		uपूर्णांक64_t pcnt:1;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t crs0_er:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t crs0_dr:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t crs1_er:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t crs1_dr:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t पूर्णांक_a:1;
		uपूर्णांक64_t reserved_62_62:1;
		uपूर्णांक64_t mio_पूर्णांकa:1;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
	काष्ठा cvmx_npei_पूर्णांक_enb_cn56xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t mio_पूर्णांकa:1;
		uपूर्णांक64_t reserved_61_62:2;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t reserved_29_29:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t reserved_22_22:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t reserved_20_20:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t pcnt:1;
		uपूर्णांक64_t pidbof:1;
		uपूर्णांक64_t psldbof:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma4dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma4dbo:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t psldbof:1;
		uपूर्णांक64_t pidbof:1;
		uपूर्णांक64_t pcnt:1;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t reserved_20_20:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t reserved_22_22:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t reserved_29_29:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t reserved_61_62:2;
		uपूर्णांक64_t mio_पूर्णांकa:1;
#पूर्ण_अगर
	पूर्ण cn56xxp1;
पूर्ण;

जोड़ cvmx_npei_पूर्णांक_enb2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_पूर्णांक_enb2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t पूर्णांक_a:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t crs1_dr:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t crs1_er:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t crs0_dr:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t crs0_er:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t pcnt:1;
		uपूर्णांक64_t pidbof:1;
		uपूर्णांक64_t psldbof:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma4dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma4dbo:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t psldbof:1;
		uपूर्णांक64_t pidbof:1;
		uपूर्णांक64_t pcnt:1;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t crs0_er:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t crs0_dr:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t crs1_er:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t crs1_dr:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t पूर्णांक_a:1;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npei_पूर्णांक_enb2_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t पूर्णांक_a:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t crs1_dr:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t crs1_er:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t crs0_dr:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t crs0_er:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t pcnt:1;
		uपूर्णांक64_t pidbof:1;
		uपूर्णांक64_t psldbof:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t psldbof:1;
		uपूर्णांक64_t pidbof:1;
		uपूर्णांक64_t pcnt:1;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t crs0_er:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t crs0_dr:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t crs1_er:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t crs1_dr:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t पूर्णांक_a:1;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
	काष्ठा cvmx_npei_पूर्णांक_enb2_cn56xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_61_63:3;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t reserved_29_29:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t reserved_22_22:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t reserved_20_20:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t pcnt:1;
		uपूर्णांक64_t pidbof:1;
		uपूर्णांक64_t psldbof:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma4dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma4dbo:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t psldbof:1;
		uपूर्णांक64_t pidbof:1;
		uपूर्णांक64_t pcnt:1;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t reserved_20_20:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t reserved_22_22:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t reserved_29_29:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t reserved_61_63:3;
#पूर्ण_अगर
	पूर्ण cn56xxp1;
पूर्ण;

जोड़ cvmx_npei_पूर्णांक_info अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_पूर्णांक_info_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t pidbof:6;
		uपूर्णांक64_t psldbof:6;
#अन्यथा
		uपूर्णांक64_t psldbof:6;
		uपूर्णांक64_t pidbof:6;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_पूर्णांक_sum अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_पूर्णांक_sum_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t mio_पूर्णांकa:1;
		uपूर्णांक64_t reserved_62_62:1;
		uपूर्णांक64_t पूर्णांक_a:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t crs1_dr:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t crs1_er:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t crs0_dr:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t crs0_er:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t pcnt:1;
		uपूर्णांक64_t pidbof:1;
		uपूर्णांक64_t psldbof:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma4dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma4dbo:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t psldbof:1;
		uपूर्णांक64_t pidbof:1;
		uपूर्णांक64_t pcnt:1;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t crs0_er:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t crs0_dr:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t crs1_er:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t crs1_dr:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t पूर्णांक_a:1;
		uपूर्णांक64_t reserved_62_62:1;
		uपूर्णांक64_t mio_पूर्णांकa:1;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npei_पूर्णांक_sum_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t mio_पूर्णांकa:1;
		uपूर्णांक64_t reserved_62_62:1;
		uपूर्णांक64_t पूर्णांक_a:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t crs1_dr:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t crs1_er:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t crs0_dr:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t crs0_er:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t reserved_15_18:4;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t reserved_15_18:4;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t crs0_er:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t crs0_dr:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t crs1_er:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t crs1_dr:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t पूर्णांक_a:1;
		uपूर्णांक64_t reserved_62_62:1;
		uपूर्णांक64_t mio_पूर्णांकa:1;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
	काष्ठा cvmx_npei_पूर्णांक_sum_cn56xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t mio_पूर्णांकa:1;
		uपूर्णांक64_t reserved_61_62:2;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t reserved_29_29:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t reserved_22_22:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t reserved_20_20:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t reserved_15_18:4;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma4dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma4dbo:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t reserved_15_18:4;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t reserved_20_20:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t reserved_22_22:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t reserved_29_29:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t reserved_61_62:2;
		uपूर्णांक64_t mio_पूर्णांकa:1;
#पूर्ण_अगर
	पूर्ण cn56xxp1;
पूर्ण;

जोड़ cvmx_npei_पूर्णांक_sum2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_पूर्णांक_sum2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t mio_पूर्णांकa:1;
		uपूर्णांक64_t reserved_62_62:1;
		uपूर्णांक64_t पूर्णांक_a:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t crs1_dr:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t crs1_er:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t crs0_dr:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t crs0_er:1;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t reserved_15_18:4;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t bar0_to:1;
		uपूर्णांक64_t iob2big:1;
		uपूर्णांक64_t dma0dbo:1;
		uपूर्णांक64_t dma1dbo:1;
		uपूर्णांक64_t dma2dbo:1;
		uपूर्णांक64_t dma3dbo:1;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t dma0fi:1;
		uपूर्णांक64_t dma1fi:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t reserved_15_18:4;
		uपूर्णांक64_t c0_aeri:1;
		uपूर्णांक64_t crs0_er:1;
		uपूर्णांक64_t c0_se:1;
		uपूर्णांक64_t crs0_dr:1;
		uपूर्णांक64_t c0_wake:1;
		uपूर्णांक64_t c0_pmei:1;
		uपूर्णांक64_t c0_hpपूर्णांक:1;
		uपूर्णांक64_t c1_aeri:1;
		uपूर्णांक64_t crs1_er:1;
		uपूर्णांक64_t c1_se:1;
		uपूर्णांक64_t crs1_dr:1;
		uपूर्णांक64_t c1_wake:1;
		uपूर्णांक64_t c1_pmei:1;
		uपूर्णांक64_t c1_hpपूर्णांक:1;
		uपूर्णांक64_t c0_up_b0:1;
		uपूर्णांक64_t c0_up_b1:1;
		uपूर्णांक64_t c0_up_b2:1;
		uपूर्णांक64_t c0_up_wi:1;
		uपूर्णांक64_t c0_up_bx:1;
		uपूर्णांक64_t c0_un_b0:1;
		uपूर्णांक64_t c0_un_b1:1;
		uपूर्णांक64_t c0_un_b2:1;
		uपूर्णांक64_t c0_un_wi:1;
		uपूर्णांक64_t c0_un_bx:1;
		uपूर्णांक64_t c1_up_b0:1;
		uपूर्णांक64_t c1_up_b1:1;
		uपूर्णांक64_t c1_up_b2:1;
		uपूर्णांक64_t c1_up_wi:1;
		uपूर्णांक64_t c1_up_bx:1;
		uपूर्णांक64_t c1_un_b0:1;
		uपूर्णांक64_t c1_un_b1:1;
		uपूर्णांक64_t c1_un_b2:1;
		uपूर्णांक64_t c1_un_wi:1;
		uपूर्णांक64_t c1_un_bx:1;
		uपूर्णांक64_t c0_un_wf:1;
		uपूर्णांक64_t c1_un_wf:1;
		uपूर्णांक64_t c0_up_wf:1;
		uपूर्णांक64_t c1_up_wf:1;
		uपूर्णांक64_t c0_exc:1;
		uपूर्णांक64_t c1_exc:1;
		uपूर्णांक64_t c0_ldwn:1;
		uपूर्णांक64_t c1_ldwn:1;
		uपूर्णांक64_t पूर्णांक_a:1;
		uपूर्णांक64_t reserved_62_62:1;
		uपूर्णांक64_t mio_पूर्णांकa:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_last_win_rdata0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_last_win_rdata0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t data:64;
#अन्यथा
		uपूर्णांक64_t data:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_last_win_rdata1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_last_win_rdata1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t data:64;
#अन्यथा
		uपूर्णांक64_t data:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_mem_access_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_mem_access_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t max_word:4;
		uपूर्णांक64_t समयr:10;
#अन्यथा
		uपूर्णांक64_t समयr:10;
		uपूर्णांक64_t max_word:4;
		uपूर्णांक64_t reserved_14_63:50;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_mem_access_subidx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_mem_access_subidx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_42_63:22;
		uपूर्णांक64_t zero:1;
		uपूर्णांक64_t port:2;
		uपूर्णांक64_t nmerge:1;
		uपूर्णांक64_t esr:2;
		uपूर्णांक64_t esw:2;
		uपूर्णांक64_t nsr:1;
		uपूर्णांक64_t nsw:1;
		uपूर्णांक64_t ror:1;
		uपूर्णांक64_t row:1;
		uपूर्णांक64_t ba:30;
#अन्यथा
		uपूर्णांक64_t ba:30;
		uपूर्णांक64_t row:1;
		uपूर्णांक64_t ror:1;
		uपूर्णांक64_t nsw:1;
		uपूर्णांक64_t nsr:1;
		uपूर्णांक64_t esw:2;
		uपूर्णांक64_t esr:2;
		uपूर्णांक64_t nmerge:1;
		uपूर्णांक64_t port:2;
		uपूर्णांक64_t zero:1;
		uपूर्णांक64_t reserved_42_63:22;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_enb0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_enb0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t enb:64;
#अन्यथा
		uपूर्णांक64_t enb:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_enb1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_enb1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t enb:64;
#अन्यथा
		uपूर्णांक64_t enb:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_enb2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_enb2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t enb:64;
#अन्यथा
		uपूर्णांक64_t enb:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_enb3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_enb3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t enb:64;
#अन्यथा
		uपूर्णांक64_t enb:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_rcv0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_rcv0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t पूर्णांकr:64;
#अन्यथा
		uपूर्णांक64_t पूर्णांकr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_rcv1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_rcv1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t पूर्णांकr:64;
#अन्यथा
		uपूर्णांक64_t पूर्णांकr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_rcv2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_rcv2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t पूर्णांकr:64;
#अन्यथा
		uपूर्णांक64_t पूर्णांकr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_rcv3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_rcv3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t पूर्णांकr:64;
#अन्यथा
		uपूर्णांक64_t पूर्णांकr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_rd_map अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_rd_map_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t rd_पूर्णांक:8;
		uपूर्णांक64_t msi_पूर्णांक:8;
#अन्यथा
		uपूर्णांक64_t msi_पूर्णांक:8;
		uपूर्णांक64_t rd_पूर्णांक:8;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_w1c_enb0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_w1c_enb0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t clr:64;
#अन्यथा
		uपूर्णांक64_t clr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_w1c_enb1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_w1c_enb1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t clr:64;
#अन्यथा
		uपूर्णांक64_t clr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_w1c_enb2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_w1c_enb2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t clr:64;
#अन्यथा
		uपूर्णांक64_t clr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_w1c_enb3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_w1c_enb3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t clr:64;
#अन्यथा
		uपूर्णांक64_t clr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_w1s_enb0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_w1s_enb0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t set:64;
#अन्यथा
		uपूर्णांक64_t set:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_w1s_enb1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_w1s_enb1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t set:64;
#अन्यथा
		uपूर्णांक64_t set:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_w1s_enb2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_w1s_enb2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t set:64;
#अन्यथा
		uपूर्णांक64_t set:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_w1s_enb3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_w1s_enb3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t set:64;
#अन्यथा
		uपूर्णांक64_t set:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_msi_wr_map अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_msi_wr_map_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t ciu_पूर्णांक:8;
		uपूर्णांक64_t msi_पूर्णांक:8;
#अन्यथा
		uपूर्णांक64_t msi_पूर्णांक:8;
		uपूर्णांक64_t ciu_पूर्णांक:8;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pcie_credit_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pcie_credit_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t p1_ccnt:8;
		uपूर्णांक64_t p1_ncnt:8;
		uपूर्णांक64_t p1_pcnt:8;
		uपूर्णांक64_t p0_ccnt:8;
		uपूर्णांक64_t p0_ncnt:8;
		uपूर्णांक64_t p0_pcnt:8;
#अन्यथा
		uपूर्णांक64_t p0_pcnt:8;
		uपूर्णांक64_t p0_ncnt:8;
		uपूर्णांक64_t p0_ccnt:8;
		uपूर्णांक64_t p1_pcnt:8;
		uपूर्णांक64_t p1_ncnt:8;
		uपूर्णांक64_t p1_ccnt:8;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pcie_msi_rcv अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pcie_msi_rcv_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t पूर्णांकr:8;
#अन्यथा
		uपूर्णांक64_t पूर्णांकr:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pcie_msi_rcv_b1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pcie_msi_rcv_b1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t पूर्णांकr:8;
		uपूर्णांक64_t reserved_0_7:8;
#अन्यथा
		uपूर्णांक64_t reserved_0_7:8;
		uपूर्णांक64_t पूर्णांकr:8;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pcie_msi_rcv_b2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pcie_msi_rcv_b2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t पूर्णांकr:8;
		uपूर्णांक64_t reserved_0_15:16;
#अन्यथा
		uपूर्णांक64_t reserved_0_15:16;
		uपूर्णांक64_t पूर्णांकr:8;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pcie_msi_rcv_b3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pcie_msi_rcv_b3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t पूर्णांकr:8;
		uपूर्णांक64_t reserved_0_23:24;
#अन्यथा
		uपूर्णांक64_t reserved_0_23:24;
		uपूर्णांक64_t पूर्णांकr:8;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pktx_cnts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pktx_cnts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_54_63:10;
		uपूर्णांक64_t समयr:22;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t समयr:22;
		uपूर्णांक64_t reserved_54_63:10;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pktx_in_bp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pktx_in_bp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t wmark:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t wmark:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pktx_instr_baddr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pktx_instr_baddr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t addr:61;
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t addr:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pktx_instr_baoff_dbell अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pktx_instr_baoff_dbell_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t aoff:32;
		uपूर्णांक64_t dbell:32;
#अन्यथा
		uपूर्णांक64_t dbell:32;
		uपूर्णांक64_t aoff:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pktx_instr_fअगरo_rsize अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pktx_instr_fअगरo_rsize_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t max:9;
		uपूर्णांक64_t rrp:9;
		uपूर्णांक64_t wrp:9;
		uपूर्णांक64_t fcnt:5;
		uपूर्णांक64_t rsize:32;
#अन्यथा
		uपूर्णांक64_t rsize:32;
		uपूर्णांक64_t fcnt:5;
		uपूर्णांक64_t wrp:9;
		uपूर्णांक64_t rrp:9;
		uपूर्णांक64_t max:9;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pktx_instr_header अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pktx_instr_header_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t pbp:1;
		uपूर्णांक64_t reserved_38_42:5;
		uपूर्णांक64_t rparmode:2;
		uपूर्णांक64_t reserved_35_35:1;
		uपूर्णांक64_t rskp_len:7;
		uपूर्णांक64_t reserved_22_27:6;
		uपूर्णांक64_t use_ihdr:1;
		uपूर्णांक64_t reserved_16_20:5;
		uपूर्णांक64_t par_mode:2;
		uपूर्णांक64_t reserved_13_13:1;
		uपूर्णांक64_t skp_len:7;
		uपूर्णांक64_t reserved_0_5:6;
#अन्यथा
		uपूर्णांक64_t reserved_0_5:6;
		uपूर्णांक64_t skp_len:7;
		uपूर्णांक64_t reserved_13_13:1;
		uपूर्णांक64_t par_mode:2;
		uपूर्णांक64_t reserved_16_20:5;
		uपूर्णांक64_t use_ihdr:1;
		uपूर्णांक64_t reserved_22_27:6;
		uपूर्णांक64_t rskp_len:7;
		uपूर्णांक64_t reserved_35_35:1;
		uपूर्णांक64_t rparmode:2;
		uपूर्णांक64_t reserved_38_42:5;
		uपूर्णांक64_t pbp:1;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pktx_slist_baddr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pktx_slist_baddr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t addr:60;
		uपूर्णांक64_t reserved_0_3:4;
#अन्यथा
		uपूर्णांक64_t reserved_0_3:4;
		uपूर्णांक64_t addr:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pktx_slist_baoff_dbell अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pktx_slist_baoff_dbell_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t aoff:32;
		uपूर्णांक64_t dbell:32;
#अन्यथा
		uपूर्णांक64_t dbell:32;
		uपूर्णांक64_t aoff:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pktx_slist_fअगरo_rsize अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pktx_slist_fअगरo_rsize_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t rsize:32;
#अन्यथा
		uपूर्णांक64_t rsize:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_cnt_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_cnt_पूर्णांक_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t port:32;
#अन्यथा
		uपूर्णांक64_t port:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_cnt_पूर्णांक_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_cnt_पूर्णांक_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t port:32;
#अन्यथा
		uपूर्णांक64_t port:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_data_out_es अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_data_out_es_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t es:64;
#अन्यथा
		uपूर्णांक64_t es:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_data_out_ns अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_data_out_ns_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t nsr:32;
#अन्यथा
		uपूर्णांक64_t nsr:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_data_out_ror अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_data_out_ror_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t ror:32;
#अन्यथा
		uपूर्णांक64_t ror:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_dpaddr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_dpaddr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t dptr:32;
#अन्यथा
		uपूर्णांक64_t dptr:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_in_bp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_in_bp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t bp:32;
#अन्यथा
		uपूर्णांक64_t bp:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_in_करोnex_cnts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_in_करोnex_cnts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_in_instr_counts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_in_instr_counts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t wr_cnt:32;
		uपूर्णांक64_t rd_cnt:32;
#अन्यथा
		uपूर्णांक64_t rd_cnt:32;
		uपूर्णांक64_t wr_cnt:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_in_pcie_port अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_in_pcie_port_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t pp:64;
#अन्यथा
		uपूर्णांक64_t pp:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_input_control अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_input_control_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_23_63:41;
		uपूर्णांक64_t pkt_rr:1;
		uपूर्णांक64_t pbp_dhi:13;
		uपूर्णांक64_t d_nsr:1;
		uपूर्णांक64_t d_esr:2;
		uपूर्णांक64_t d_ror:1;
		uपूर्णांक64_t use_csr:1;
		uपूर्णांक64_t nsr:1;
		uपूर्णांक64_t esr:2;
		uपूर्णांक64_t ror:1;
#अन्यथा
		uपूर्णांक64_t ror:1;
		uपूर्णांक64_t esr:2;
		uपूर्णांक64_t nsr:1;
		uपूर्णांक64_t use_csr:1;
		uपूर्णांक64_t d_ror:1;
		uपूर्णांक64_t d_esr:2;
		uपूर्णांक64_t d_nsr:1;
		uपूर्णांक64_t pbp_dhi:13;
		uपूर्णांक64_t pkt_rr:1;
		uपूर्णांक64_t reserved_23_63:41;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_instr_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_instr_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t enb:32;
#अन्यथा
		uपूर्णांक64_t enb:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_instr_rd_size अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_instr_rd_size_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t rdsize:64;
#अन्यथा
		uपूर्णांक64_t rdsize:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_instr_size अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_instr_size_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t is_64b:32;
#अन्यथा
		uपूर्णांक64_t is_64b:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_पूर्णांक_levels अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_पूर्णांक_levels_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_54_63:10;
		uपूर्णांक64_t समय:22;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t समय:22;
		uपूर्णांक64_t reserved_54_63:10;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_iptr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_iptr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t iptr:32;
#अन्यथा
		uपूर्णांक64_t iptr:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_out_bmode अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_out_bmode_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t bmode:32;
#अन्यथा
		uपूर्णांक64_t bmode:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_out_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_out_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t enb:32;
#अन्यथा
		uपूर्णांक64_t enb:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_output_wmark अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_output_wmark_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t wmark:32;
#अन्यथा
		uपूर्णांक64_t wmark:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_pcie_port अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_pcie_port_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t pp:64;
#अन्यथा
		uपूर्णांक64_t pp:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_port_in_rst अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_port_in_rst_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t in_rst:32;
		uपूर्णांक64_t out_rst:32;
#अन्यथा
		uपूर्णांक64_t out_rst:32;
		uपूर्णांक64_t in_rst:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_slist_es अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_slist_es_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t es:64;
#अन्यथा
		uपूर्णांक64_t es:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_slist_id_size अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_slist_id_size_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_23_63:41;
		uपूर्णांक64_t isize:7;
		uपूर्णांक64_t bsize:16;
#अन्यथा
		uपूर्णांक64_t bsize:16;
		uपूर्णांक64_t isize:7;
		uपूर्णांक64_t reserved_23_63:41;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_slist_ns अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_slist_ns_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t nsr:32;
#अन्यथा
		uपूर्णांक64_t nsr:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_slist_ror अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_slist_ror_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t ror:32;
#अन्यथा
		uपूर्णांक64_t ror:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_समय_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_समय_पूर्णांक_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t port:32;
#अन्यथा
		uपूर्णांक64_t port:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_pkt_समय_पूर्णांक_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_pkt_समय_पूर्णांक_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t port:32;
#अन्यथा
		uपूर्णांक64_t port:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_rsl_पूर्णांक_blocks अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_rsl_पूर्णांक_blocks_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_31_63:33;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t lmc1:1;
		uपूर्णांक64_t agl:1;
		uपूर्णांक64_t reserved_24_27:4;
		uपूर्णांक64_t asxpcs1:1;
		uपूर्णांक64_t asxpcs0:1;
		uपूर्णांक64_t reserved_21_21:1;
		uपूर्णांक64_t pip:1;
		uपूर्णांक64_t spx1:1;
		uपूर्णांक64_t spx0:1;
		uपूर्णांक64_t lmc0:1;
		uपूर्णांक64_t l2c:1;
		uपूर्णांक64_t usb1:1;
		uपूर्णांक64_t rad:1;
		uपूर्णांक64_t usb:1;
		uपूर्णांक64_t घात:1;
		uपूर्णांक64_t tim:1;
		uपूर्णांक64_t pko:1;
		uपूर्णांक64_t ipd:1;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t zip:1;
		uपूर्णांक64_t dfa:1;
		uपूर्णांक64_t fpa:1;
		uपूर्णांक64_t key:1;
		uपूर्णांक64_t npei:1;
		uपूर्णांक64_t gmx1:1;
		uपूर्णांक64_t gmx0:1;
		uपूर्णांक64_t mio:1;
#अन्यथा
		uपूर्णांक64_t mio:1;
		uपूर्णांक64_t gmx0:1;
		uपूर्णांक64_t gmx1:1;
		uपूर्णांक64_t npei:1;
		uपूर्णांक64_t key:1;
		uपूर्णांक64_t fpa:1;
		uपूर्णांक64_t dfa:1;
		uपूर्णांक64_t zip:1;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t ipd:1;
		uपूर्णांक64_t pko:1;
		uपूर्णांक64_t tim:1;
		uपूर्णांक64_t घात:1;
		uपूर्णांक64_t usb:1;
		uपूर्णांक64_t rad:1;
		uपूर्णांक64_t usb1:1;
		uपूर्णांक64_t l2c:1;
		uपूर्णांक64_t lmc0:1;
		uपूर्णांक64_t spx0:1;
		uपूर्णांक64_t spx1:1;
		uपूर्णांक64_t pip:1;
		uपूर्णांक64_t reserved_21_21:1;
		uपूर्णांक64_t asxpcs0:1;
		uपूर्णांक64_t asxpcs1:1;
		uपूर्णांक64_t reserved_24_27:4;
		uपूर्णांक64_t agl:1;
		uपूर्णांक64_t lmc1:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t reserved_31_63:33;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_scratch_1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_scratch_1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t data:64;
#अन्यथा
		uपूर्णांक64_t data:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_state1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_state1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t cpl1:12;
		uपूर्णांक64_t cpl0:12;
		uपूर्णांक64_t arb:1;
		uपूर्णांक64_t csr:39;
#अन्यथा
		uपूर्णांक64_t csr:39;
		uपूर्णांक64_t arb:1;
		uपूर्णांक64_t cpl0:12;
		uपूर्णांक64_t cpl1:12;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_state2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_state2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t npei:1;
		uपूर्णांक64_t rac:1;
		uपूर्णांक64_t csm1:15;
		uपूर्णांक64_t csm0:15;
		uपूर्णांक64_t nnp0:8;
		uपूर्णांक64_t nnd:8;
#अन्यथा
		uपूर्णांक64_t nnd:8;
		uपूर्णांक64_t nnp0:8;
		uपूर्णांक64_t csm0:15;
		uपूर्णांक64_t csm1:15;
		uपूर्णांक64_t rac:1;
		uपूर्णांक64_t npei:1;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_state3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_state3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_56_63:8;
		uपूर्णांक64_t psm1:15;
		uपूर्णांक64_t psm0:15;
		uपूर्णांक64_t nsm1:13;
		uपूर्णांक64_t nsm0:13;
#अन्यथा
		uपूर्णांक64_t nsm0:13;
		uपूर्णांक64_t nsm1:13;
		uपूर्णांक64_t psm0:15;
		uपूर्णांक64_t psm1:15;
		uपूर्णांक64_t reserved_56_63:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_win_rd_addr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_win_rd_addr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_51_63:13;
		uपूर्णांक64_t ld_cmd:2;
		uपूर्णांक64_t iobit:1;
		uपूर्णांक64_t rd_addr:48;
#अन्यथा
		uपूर्णांक64_t rd_addr:48;
		uपूर्णांक64_t iobit:1;
		uपूर्णांक64_t ld_cmd:2;
		uपूर्णांक64_t reserved_51_63:13;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_win_rd_data अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_win_rd_data_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t rd_data:64;
#अन्यथा
		uपूर्णांक64_t rd_data:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_win_wr_addr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_win_wr_addr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_49_63:15;
		uपूर्णांक64_t iobit:1;
		uपूर्णांक64_t wr_addr:46;
		uपूर्णांक64_t reserved_0_1:2;
#अन्यथा
		uपूर्णांक64_t reserved_0_1:2;
		uपूर्णांक64_t wr_addr:46;
		uपूर्णांक64_t iobit:1;
		uपूर्णांक64_t reserved_49_63:15;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_win_wr_data अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_win_wr_data_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t wr_data:64;
#अन्यथा
		uपूर्णांक64_t wr_data:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_win_wr_mask अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_win_wr_mask_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t wr_mask:8;
#अन्यथा
		uपूर्णांक64_t wr_mask:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npei_winकरोw_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npei_winकरोw_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t समय:32;
#अन्यथा
		uपूर्णांक64_t समय:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
