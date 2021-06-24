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

#अगर_अघोषित __CVMX_NPI_DEFS_H__
#घोषणा __CVMX_NPI_DEFS_H__

#घोषणा CVMX_NPI_BASE_ADDR_INPUT0 CVMX_NPI_BASE_ADDR_INPUTX(0)
#घोषणा CVMX_NPI_BASE_ADDR_INPUT1 CVMX_NPI_BASE_ADDR_INPUTX(1)
#घोषणा CVMX_NPI_BASE_ADDR_INPUT2 CVMX_NPI_BASE_ADDR_INPUTX(2)
#घोषणा CVMX_NPI_BASE_ADDR_INPUT3 CVMX_NPI_BASE_ADDR_INPUTX(3)
#घोषणा CVMX_NPI_BASE_ADDR_INPUTX(offset) (CVMX_ADD_IO_SEG(0x00011F0000000070ull) + ((offset) & 3) * 16)
#घोषणा CVMX_NPI_BASE_ADDR_OUTPUT0 CVMX_NPI_BASE_ADDR_OUTPUTX(0)
#घोषणा CVMX_NPI_BASE_ADDR_OUTPUT1 CVMX_NPI_BASE_ADDR_OUTPUTX(1)
#घोषणा CVMX_NPI_BASE_ADDR_OUTPUT2 CVMX_NPI_BASE_ADDR_OUTPUTX(2)
#घोषणा CVMX_NPI_BASE_ADDR_OUTPUT3 CVMX_NPI_BASE_ADDR_OUTPUTX(3)
#घोषणा CVMX_NPI_BASE_ADDR_OUTPUTX(offset) (CVMX_ADD_IO_SEG(0x00011F00000000B8ull) + ((offset) & 3) * 8)
#घोषणा CVMX_NPI_BIST_STATUS (CVMX_ADD_IO_SEG(0x00011F00000003F8ull))
#घोषणा CVMX_NPI_BUFF_SIZE_OUTPUT0 CVMX_NPI_BUFF_SIZE_OUTPUTX(0)
#घोषणा CVMX_NPI_BUFF_SIZE_OUTPUT1 CVMX_NPI_BUFF_SIZE_OUTPUTX(1)
#घोषणा CVMX_NPI_BUFF_SIZE_OUTPUT2 CVMX_NPI_BUFF_SIZE_OUTPUTX(2)
#घोषणा CVMX_NPI_BUFF_SIZE_OUTPUT3 CVMX_NPI_BUFF_SIZE_OUTPUTX(3)
#घोषणा CVMX_NPI_BUFF_SIZE_OUTPUTX(offset) (CVMX_ADD_IO_SEG(0x00011F00000000E0ull) + ((offset) & 3) * 8)
#घोषणा CVMX_NPI_COMP_CTL (CVMX_ADD_IO_SEG(0x00011F0000000218ull))
#घोषणा CVMX_NPI_CTL_STATUS (CVMX_ADD_IO_SEG(0x00011F0000000010ull))
#घोषणा CVMX_NPI_DBG_SELECT (CVMX_ADD_IO_SEG(0x00011F0000000008ull))
#घोषणा CVMX_NPI_DMA_CONTROL (CVMX_ADD_IO_SEG(0x00011F0000000128ull))
#घोषणा CVMX_NPI_DMA_HIGHP_COUNTS (CVMX_ADD_IO_SEG(0x00011F0000000148ull))
#घोषणा CVMX_NPI_DMA_HIGHP_NADDR (CVMX_ADD_IO_SEG(0x00011F0000000158ull))
#घोषणा CVMX_NPI_DMA_LOWP_COUNTS (CVMX_ADD_IO_SEG(0x00011F0000000140ull))
#घोषणा CVMX_NPI_DMA_LOWP_NADDR (CVMX_ADD_IO_SEG(0x00011F0000000150ull))
#घोषणा CVMX_NPI_HIGHP_DBELL (CVMX_ADD_IO_SEG(0x00011F0000000120ull))
#घोषणा CVMX_NPI_HIGHP_IBUFF_SADDR (CVMX_ADD_IO_SEG(0x00011F0000000110ull))
#घोषणा CVMX_NPI_INPUT_CONTROL (CVMX_ADD_IO_SEG(0x00011F0000000138ull))
#घोषणा CVMX_NPI_INT_ENB (CVMX_ADD_IO_SEG(0x00011F0000000020ull))
#घोषणा CVMX_NPI_INT_SUM (CVMX_ADD_IO_SEG(0x00011F0000000018ull))
#घोषणा CVMX_NPI_LOWP_DBELL (CVMX_ADD_IO_SEG(0x00011F0000000118ull))
#घोषणा CVMX_NPI_LOWP_IBUFF_SADDR (CVMX_ADD_IO_SEG(0x00011F0000000108ull))
#घोषणा CVMX_NPI_MEM_ACCESS_SUBID3 CVMX_NPI_MEM_ACCESS_SUBIDX(3)
#घोषणा CVMX_NPI_MEM_ACCESS_SUBID4 CVMX_NPI_MEM_ACCESS_SUBIDX(4)
#घोषणा CVMX_NPI_MEM_ACCESS_SUBID5 CVMX_NPI_MEM_ACCESS_SUBIDX(5)
#घोषणा CVMX_NPI_MEM_ACCESS_SUBID6 CVMX_NPI_MEM_ACCESS_SUBIDX(6)
#घोषणा CVMX_NPI_MEM_ACCESS_SUBIDX(offset) (CVMX_ADD_IO_SEG(0x00011F0000000028ull) + ((offset) & 7) * 8 - 8*3)
#घोषणा CVMX_NPI_MSI_RCV (0x0000000000000190ull)
#घोषणा CVMX_NPI_NPI_MSI_RCV (CVMX_ADD_IO_SEG(0x00011F0000001190ull))
#घोषणा CVMX_NPI_NUM_DESC_OUTPUT0 CVMX_NPI_NUM_DESC_OUTPUTX(0)
#घोषणा CVMX_NPI_NUM_DESC_OUTPUT1 CVMX_NPI_NUM_DESC_OUTPUTX(1)
#घोषणा CVMX_NPI_NUM_DESC_OUTPUT2 CVMX_NPI_NUM_DESC_OUTPUTX(2)
#घोषणा CVMX_NPI_NUM_DESC_OUTPUT3 CVMX_NPI_NUM_DESC_OUTPUTX(3)
#घोषणा CVMX_NPI_NUM_DESC_OUTPUTX(offset) (CVMX_ADD_IO_SEG(0x00011F0000000050ull) + ((offset) & 3) * 8)
#घोषणा CVMX_NPI_OUTPUT_CONTROL (CVMX_ADD_IO_SEG(0x00011F0000000100ull))
#घोषणा CVMX_NPI_P0_DBPAIR_ADDR CVMX_NPI_PX_DBPAIR_ADDR(0)
#घोषणा CVMX_NPI_P0_INSTR_ADDR CVMX_NPI_PX_INSTR_ADDR(0)
#घोषणा CVMX_NPI_P0_INSTR_CNTS CVMX_NPI_PX_INSTR_CNTS(0)
#घोषणा CVMX_NPI_P0_PAIR_CNTS CVMX_NPI_PX_PAIR_CNTS(0)
#घोषणा CVMX_NPI_P1_DBPAIR_ADDR CVMX_NPI_PX_DBPAIR_ADDR(1)
#घोषणा CVMX_NPI_P1_INSTR_ADDR CVMX_NPI_PX_INSTR_ADDR(1)
#घोषणा CVMX_NPI_P1_INSTR_CNTS CVMX_NPI_PX_INSTR_CNTS(1)
#घोषणा CVMX_NPI_P1_PAIR_CNTS CVMX_NPI_PX_PAIR_CNTS(1)
#घोषणा CVMX_NPI_P2_DBPAIR_ADDR CVMX_NPI_PX_DBPAIR_ADDR(2)
#घोषणा CVMX_NPI_P2_INSTR_ADDR CVMX_NPI_PX_INSTR_ADDR(2)
#घोषणा CVMX_NPI_P2_INSTR_CNTS CVMX_NPI_PX_INSTR_CNTS(2)
#घोषणा CVMX_NPI_P2_PAIR_CNTS CVMX_NPI_PX_PAIR_CNTS(2)
#घोषणा CVMX_NPI_P3_DBPAIR_ADDR CVMX_NPI_PX_DBPAIR_ADDR(3)
#घोषणा CVMX_NPI_P3_INSTR_ADDR CVMX_NPI_PX_INSTR_ADDR(3)
#घोषणा CVMX_NPI_P3_INSTR_CNTS CVMX_NPI_PX_INSTR_CNTS(3)
#घोषणा CVMX_NPI_P3_PAIR_CNTS CVMX_NPI_PX_PAIR_CNTS(3)
#घोषणा CVMX_NPI_PCI_BAR1_INDEXX(offset) (CVMX_ADD_IO_SEG(0x00011F0000001100ull) + ((offset) & 31) * 4)
#घोषणा CVMX_NPI_PCI_BIST_REG (CVMX_ADD_IO_SEG(0x00011F00000011C0ull))
#घोषणा CVMX_NPI_PCI_BURST_SIZE (CVMX_ADD_IO_SEG(0x00011F00000000D8ull))
#घोषणा CVMX_NPI_PCI_CFG00 (CVMX_ADD_IO_SEG(0x00011F0000001800ull))
#घोषणा CVMX_NPI_PCI_CFG01 (CVMX_ADD_IO_SEG(0x00011F0000001804ull))
#घोषणा CVMX_NPI_PCI_CFG02 (CVMX_ADD_IO_SEG(0x00011F0000001808ull))
#घोषणा CVMX_NPI_PCI_CFG03 (CVMX_ADD_IO_SEG(0x00011F000000180Cull))
#घोषणा CVMX_NPI_PCI_CFG04 (CVMX_ADD_IO_SEG(0x00011F0000001810ull))
#घोषणा CVMX_NPI_PCI_CFG05 (CVMX_ADD_IO_SEG(0x00011F0000001814ull))
#घोषणा CVMX_NPI_PCI_CFG06 (CVMX_ADD_IO_SEG(0x00011F0000001818ull))
#घोषणा CVMX_NPI_PCI_CFG07 (CVMX_ADD_IO_SEG(0x00011F000000181Cull))
#घोषणा CVMX_NPI_PCI_CFG08 (CVMX_ADD_IO_SEG(0x00011F0000001820ull))
#घोषणा CVMX_NPI_PCI_CFG09 (CVMX_ADD_IO_SEG(0x00011F0000001824ull))
#घोषणा CVMX_NPI_PCI_CFG10 (CVMX_ADD_IO_SEG(0x00011F0000001828ull))
#घोषणा CVMX_NPI_PCI_CFG11 (CVMX_ADD_IO_SEG(0x00011F000000182Cull))
#घोषणा CVMX_NPI_PCI_CFG12 (CVMX_ADD_IO_SEG(0x00011F0000001830ull))
#घोषणा CVMX_NPI_PCI_CFG13 (CVMX_ADD_IO_SEG(0x00011F0000001834ull))
#घोषणा CVMX_NPI_PCI_CFG15 (CVMX_ADD_IO_SEG(0x00011F000000183Cull))
#घोषणा CVMX_NPI_PCI_CFG16 (CVMX_ADD_IO_SEG(0x00011F0000001840ull))
#घोषणा CVMX_NPI_PCI_CFG17 (CVMX_ADD_IO_SEG(0x00011F0000001844ull))
#घोषणा CVMX_NPI_PCI_CFG18 (CVMX_ADD_IO_SEG(0x00011F0000001848ull))
#घोषणा CVMX_NPI_PCI_CFG19 (CVMX_ADD_IO_SEG(0x00011F000000184Cull))
#घोषणा CVMX_NPI_PCI_CFG20 (CVMX_ADD_IO_SEG(0x00011F0000001850ull))
#घोषणा CVMX_NPI_PCI_CFG21 (CVMX_ADD_IO_SEG(0x00011F0000001854ull))
#घोषणा CVMX_NPI_PCI_CFG22 (CVMX_ADD_IO_SEG(0x00011F0000001858ull))
#घोषणा CVMX_NPI_PCI_CFG56 (CVMX_ADD_IO_SEG(0x00011F00000018E0ull))
#घोषणा CVMX_NPI_PCI_CFG57 (CVMX_ADD_IO_SEG(0x00011F00000018E4ull))
#घोषणा CVMX_NPI_PCI_CFG58 (CVMX_ADD_IO_SEG(0x00011F00000018E8ull))
#घोषणा CVMX_NPI_PCI_CFG59 (CVMX_ADD_IO_SEG(0x00011F00000018ECull))
#घोषणा CVMX_NPI_PCI_CFG60 (CVMX_ADD_IO_SEG(0x00011F00000018F0ull))
#घोषणा CVMX_NPI_PCI_CFG61 (CVMX_ADD_IO_SEG(0x00011F00000018F4ull))
#घोषणा CVMX_NPI_PCI_CFG62 (CVMX_ADD_IO_SEG(0x00011F00000018F8ull))
#घोषणा CVMX_NPI_PCI_CFG63 (CVMX_ADD_IO_SEG(0x00011F00000018FCull))
#घोषणा CVMX_NPI_PCI_CNT_REG (CVMX_ADD_IO_SEG(0x00011F00000011B8ull))
#घोषणा CVMX_NPI_PCI_CTL_STATUS_2 (CVMX_ADD_IO_SEG(0x00011F000000118Cull))
#घोषणा CVMX_NPI_PCI_INT_ARB_CFG (CVMX_ADD_IO_SEG(0x00011F0000000130ull))
#घोषणा CVMX_NPI_PCI_INT_ENB2 (CVMX_ADD_IO_SEG(0x00011F00000011A0ull))
#घोषणा CVMX_NPI_PCI_INT_SUM2 (CVMX_ADD_IO_SEG(0x00011F0000001198ull))
#घोषणा CVMX_NPI_PCI_READ_CMD (CVMX_ADD_IO_SEG(0x00011F0000000048ull))
#घोषणा CVMX_NPI_PCI_READ_CMD_6 (CVMX_ADD_IO_SEG(0x00011F0000001180ull))
#घोषणा CVMX_NPI_PCI_READ_CMD_C (CVMX_ADD_IO_SEG(0x00011F0000001184ull))
#घोषणा CVMX_NPI_PCI_READ_CMD_E (CVMX_ADD_IO_SEG(0x00011F0000001188ull))
#घोषणा CVMX_NPI_PCI_SCM_REG (CVMX_ADD_IO_SEG(0x00011F00000011A8ull))
#घोषणा CVMX_NPI_PCI_TSR_REG (CVMX_ADD_IO_SEG(0x00011F00000011B0ull))
#घोषणा CVMX_NPI_PORT32_INSTR_HDR (CVMX_ADD_IO_SEG(0x00011F00000001F8ull))
#घोषणा CVMX_NPI_PORT33_INSTR_HDR (CVMX_ADD_IO_SEG(0x00011F0000000200ull))
#घोषणा CVMX_NPI_PORT34_INSTR_HDR (CVMX_ADD_IO_SEG(0x00011F0000000208ull))
#घोषणा CVMX_NPI_PORT35_INSTR_HDR (CVMX_ADD_IO_SEG(0x00011F0000000210ull))
#घोषणा CVMX_NPI_PORT_BP_CONTROL (CVMX_ADD_IO_SEG(0x00011F00000001F0ull))
#घोषणा CVMX_NPI_PX_DBPAIR_ADDR(offset) (CVMX_ADD_IO_SEG(0x00011F0000000180ull) + ((offset) & 3) * 8)
#घोषणा CVMX_NPI_PX_INSTR_ADDR(offset) (CVMX_ADD_IO_SEG(0x00011F00000001C0ull) + ((offset) & 3) * 8)
#घोषणा CVMX_NPI_PX_INSTR_CNTS(offset) (CVMX_ADD_IO_SEG(0x00011F00000001A0ull) + ((offset) & 3) * 8)
#घोषणा CVMX_NPI_PX_PAIR_CNTS(offset) (CVMX_ADD_IO_SEG(0x00011F0000000160ull) + ((offset) & 3) * 8)
#घोषणा CVMX_NPI_RSL_INT_BLOCKS (CVMX_ADD_IO_SEG(0x00011F0000000000ull))
#घोषणा CVMX_NPI_SIZE_INPUT0 CVMX_NPI_SIZE_INPUTX(0)
#घोषणा CVMX_NPI_SIZE_INPUT1 CVMX_NPI_SIZE_INPUTX(1)
#घोषणा CVMX_NPI_SIZE_INPUT2 CVMX_NPI_SIZE_INPUTX(2)
#घोषणा CVMX_NPI_SIZE_INPUT3 CVMX_NPI_SIZE_INPUTX(3)
#घोषणा CVMX_NPI_SIZE_INPUTX(offset) (CVMX_ADD_IO_SEG(0x00011F0000000078ull) + ((offset) & 3) * 16)
#घोषणा CVMX_NPI_WIN_READ_TO (CVMX_ADD_IO_SEG(0x00011F00000001E0ull))

जोड़ cvmx_npi_base_addr_inputx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_base_addr_inputx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t baddr:61;
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t baddr:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_base_addr_outputx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_base_addr_outputx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t baddr:61;
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t baddr:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_bist_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_bist_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t csr_bs:1;
		uपूर्णांक64_t dअगर_bs:1;
		uपूर्णांक64_t rdp_bs:1;
		uपूर्णांक64_t pcnc_bs:1;
		uपूर्णांक64_t pcn_bs:1;
		uपूर्णांक64_t rdn_bs:1;
		uपूर्णांक64_t pcac_bs:1;
		uपूर्णांक64_t pcad_bs:1;
		uपूर्णांक64_t rdnl_bs:1;
		uपूर्णांक64_t pgf_bs:1;
		uपूर्णांक64_t pig_bs:1;
		uपूर्णांक64_t pof0_bs:1;
		uपूर्णांक64_t pof1_bs:1;
		uपूर्णांक64_t pof2_bs:1;
		uपूर्णांक64_t pof3_bs:1;
		uपूर्णांक64_t pos_bs:1;
		uपूर्णांक64_t nus_bs:1;
		uपूर्णांक64_t करोb_bs:1;
		uपूर्णांक64_t pdf_bs:1;
		uपूर्णांक64_t dpi_bs:1;
#अन्यथा
		uपूर्णांक64_t dpi_bs:1;
		uपूर्णांक64_t pdf_bs:1;
		uपूर्णांक64_t करोb_bs:1;
		uपूर्णांक64_t nus_bs:1;
		uपूर्णांक64_t pos_bs:1;
		uपूर्णांक64_t pof3_bs:1;
		uपूर्णांक64_t pof2_bs:1;
		uपूर्णांक64_t pof1_bs:1;
		uपूर्णांक64_t pof0_bs:1;
		uपूर्णांक64_t pig_bs:1;
		uपूर्णांक64_t pgf_bs:1;
		uपूर्णांक64_t rdnl_bs:1;
		uपूर्णांक64_t pcad_bs:1;
		uपूर्णांक64_t pcac_bs:1;
		uपूर्णांक64_t rdn_bs:1;
		uपूर्णांक64_t pcn_bs:1;
		uपूर्णांक64_t pcnc_bs:1;
		uपूर्णांक64_t rdp_bs:1;
		uपूर्णांक64_t dअगर_bs:1;
		uपूर्णांक64_t csr_bs:1;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npi_bist_status_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t csr_bs:1;
		uपूर्णांक64_t dअगर_bs:1;
		uपूर्णांक64_t rdp_bs:1;
		uपूर्णांक64_t pcnc_bs:1;
		uपूर्णांक64_t pcn_bs:1;
		uपूर्णांक64_t rdn_bs:1;
		uपूर्णांक64_t pcac_bs:1;
		uपूर्णांक64_t pcad_bs:1;
		uपूर्णांक64_t rdnl_bs:1;
		uपूर्णांक64_t pgf_bs:1;
		uपूर्णांक64_t pig_bs:1;
		uपूर्णांक64_t pof0_bs:1;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t pos_bs:1;
		uपूर्णांक64_t nus_bs:1;
		uपूर्णांक64_t करोb_bs:1;
		uपूर्णांक64_t pdf_bs:1;
		uपूर्णांक64_t dpi_bs:1;
#अन्यथा
		uपूर्णांक64_t dpi_bs:1;
		uपूर्णांक64_t pdf_bs:1;
		uपूर्णांक64_t करोb_bs:1;
		uपूर्णांक64_t nus_bs:1;
		uपूर्णांक64_t pos_bs:1;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t pof0_bs:1;
		uपूर्णांक64_t pig_bs:1;
		uपूर्णांक64_t pgf_bs:1;
		uपूर्णांक64_t rdnl_bs:1;
		uपूर्णांक64_t pcad_bs:1;
		uपूर्णांक64_t pcac_bs:1;
		uपूर्णांक64_t rdn_bs:1;
		uपूर्णांक64_t pcn_bs:1;
		uपूर्णांक64_t pcnc_bs:1;
		uपूर्णांक64_t rdp_bs:1;
		uपूर्णांक64_t dअगर_bs:1;
		uपूर्णांक64_t csr_bs:1;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_npi_bist_status_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t csr_bs:1;
		uपूर्णांक64_t dअगर_bs:1;
		uपूर्णांक64_t rdp_bs:1;
		uपूर्णांक64_t pcnc_bs:1;
		uपूर्णांक64_t pcn_bs:1;
		uपूर्णांक64_t rdn_bs:1;
		uपूर्णांक64_t pcac_bs:1;
		uपूर्णांक64_t pcad_bs:1;
		uपूर्णांक64_t rdnl_bs:1;
		uपूर्णांक64_t pgf_bs:1;
		uपूर्णांक64_t pig_bs:1;
		uपूर्णांक64_t pof0_bs:1;
		uपूर्णांक64_t pof1_bs:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t pos_bs:1;
		uपूर्णांक64_t nus_bs:1;
		uपूर्णांक64_t करोb_bs:1;
		uपूर्णांक64_t pdf_bs:1;
		uपूर्णांक64_t dpi_bs:1;
#अन्यथा
		uपूर्णांक64_t dpi_bs:1;
		uपूर्णांक64_t pdf_bs:1;
		uपूर्णांक64_t करोb_bs:1;
		uपूर्णांक64_t nus_bs:1;
		uपूर्णांक64_t pos_bs:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t pof1_bs:1;
		uपूर्णांक64_t pof0_bs:1;
		uपूर्णांक64_t pig_bs:1;
		uपूर्णांक64_t pgf_bs:1;
		uपूर्णांक64_t rdnl_bs:1;
		uपूर्णांक64_t pcad_bs:1;
		uपूर्णांक64_t pcac_bs:1;
		uपूर्णांक64_t rdn_bs:1;
		uपूर्णांक64_t pcn_bs:1;
		uपूर्णांक64_t pcnc_bs:1;
		uपूर्णांक64_t rdp_bs:1;
		uपूर्णांक64_t dअगर_bs:1;
		uपूर्णांक64_t csr_bs:1;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_npi_buff_size_outputx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_buff_size_outputx_s अणु
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

जोड़ cvmx_npi_comp_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_comp_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t nctl:5;
#अन्यथा
		uपूर्णांक64_t nctl:5;
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_ctl_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_ctl_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_63_63:1;
		uपूर्णांक64_t chip_rev:8;
		uपूर्णांक64_t dis_pniw:1;
		uपूर्णांक64_t out3_enb:1;
		uपूर्णांक64_t out2_enb:1;
		uपूर्णांक64_t out1_enb:1;
		uपूर्णांक64_t out0_enb:1;
		uपूर्णांक64_t ins3_enb:1;
		uपूर्णांक64_t ins2_enb:1;
		uपूर्णांक64_t ins1_enb:1;
		uपूर्णांक64_t ins0_enb:1;
		uपूर्णांक64_t ins3_64b:1;
		uपूर्णांक64_t ins2_64b:1;
		uपूर्णांक64_t ins1_64b:1;
		uपूर्णांक64_t ins0_64b:1;
		uपूर्णांक64_t pci_wdis:1;
		uपूर्णांक64_t रुको_com:1;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t max_word:5;
		uपूर्णांक64_t reserved_10_31:22;
		uपूर्णांक64_t समयr:10;
#अन्यथा
		uपूर्णांक64_t समयr:10;
		uपूर्णांक64_t reserved_10_31:22;
		uपूर्णांक64_t max_word:5;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t रुको_com:1;
		uपूर्णांक64_t pci_wdis:1;
		uपूर्णांक64_t ins0_64b:1;
		uपूर्णांक64_t ins1_64b:1;
		uपूर्णांक64_t ins2_64b:1;
		uपूर्णांक64_t ins3_64b:1;
		uपूर्णांक64_t ins0_enb:1;
		uपूर्णांक64_t ins1_enb:1;
		uपूर्णांक64_t ins2_enb:1;
		uपूर्णांक64_t ins3_enb:1;
		uपूर्णांक64_t out0_enb:1;
		uपूर्णांक64_t out1_enb:1;
		uपूर्णांक64_t out2_enb:1;
		uपूर्णांक64_t out3_enb:1;
		uपूर्णांक64_t dis_pniw:1;
		uपूर्णांक64_t chip_rev:8;
		uपूर्णांक64_t reserved_63_63:1;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npi_ctl_status_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_63_63:1;
		uपूर्णांक64_t chip_rev:8;
		uपूर्णांक64_t dis_pniw:1;
		uपूर्णांक64_t reserved_51_53:3;
		uपूर्णांक64_t out0_enb:1;
		uपूर्णांक64_t reserved_47_49:3;
		uपूर्णांक64_t ins0_enb:1;
		uपूर्णांक64_t reserved_43_45:3;
		uपूर्णांक64_t ins0_64b:1;
		uपूर्णांक64_t pci_wdis:1;
		uपूर्णांक64_t रुको_com:1;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t max_word:5;
		uपूर्णांक64_t reserved_10_31:22;
		uपूर्णांक64_t समयr:10;
#अन्यथा
		uपूर्णांक64_t समयr:10;
		uपूर्णांक64_t reserved_10_31:22;
		uपूर्णांक64_t max_word:5;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t रुको_com:1;
		uपूर्णांक64_t pci_wdis:1;
		uपूर्णांक64_t ins0_64b:1;
		uपूर्णांक64_t reserved_43_45:3;
		uपूर्णांक64_t ins0_enb:1;
		uपूर्णांक64_t reserved_47_49:3;
		uपूर्णांक64_t out0_enb:1;
		uपूर्णांक64_t reserved_51_53:3;
		uपूर्णांक64_t dis_pniw:1;
		uपूर्णांक64_t chip_rev:8;
		uपूर्णांक64_t reserved_63_63:1;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_npi_ctl_status_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_63_63:1;
		uपूर्णांक64_t chip_rev:8;
		uपूर्णांक64_t dis_pniw:1;
		uपूर्णांक64_t reserved_52_53:2;
		uपूर्णांक64_t out1_enb:1;
		uपूर्णांक64_t out0_enb:1;
		uपूर्णांक64_t reserved_48_49:2;
		uपूर्णांक64_t ins1_enb:1;
		uपूर्णांक64_t ins0_enb:1;
		uपूर्णांक64_t reserved_44_45:2;
		uपूर्णांक64_t ins1_64b:1;
		uपूर्णांक64_t ins0_64b:1;
		uपूर्णांक64_t pci_wdis:1;
		uपूर्णांक64_t रुको_com:1;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t max_word:5;
		uपूर्णांक64_t reserved_10_31:22;
		uपूर्णांक64_t समयr:10;
#अन्यथा
		uपूर्णांक64_t समयr:10;
		uपूर्णांक64_t reserved_10_31:22;
		uपूर्णांक64_t max_word:5;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t रुको_com:1;
		uपूर्णांक64_t pci_wdis:1;
		uपूर्णांक64_t ins0_64b:1;
		uपूर्णांक64_t ins1_64b:1;
		uपूर्णांक64_t reserved_44_45:2;
		uपूर्णांक64_t ins0_enb:1;
		uपूर्णांक64_t ins1_enb:1;
		uपूर्णांक64_t reserved_48_49:2;
		uपूर्णांक64_t out0_enb:1;
		uपूर्णांक64_t out1_enb:1;
		uपूर्णांक64_t reserved_52_53:2;
		uपूर्णांक64_t dis_pniw:1;
		uपूर्णांक64_t chip_rev:8;
		uपूर्णांक64_t reserved_63_63:1;
#पूर्ण_अगर
	पूर्ण cn31xx;
पूर्ण;

जोड़ cvmx_npi_dbg_select अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_dbg_select_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t dbg_sel:16;
#अन्यथा
		uपूर्णांक64_t dbg_sel:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_dma_control अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_dma_control_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_36_63:28;
		uपूर्णांक64_t b0_lend:1;
		uपूर्णांक64_t dwb_denb:1;
		uपूर्णांक64_t dwb_ichk:9;
		uपूर्णांक64_t fpa_que:3;
		uपूर्णांक64_t o_add1:1;
		uपूर्णांक64_t o_ro:1;
		uपूर्णांक64_t o_ns:1;
		uपूर्णांक64_t o_es:2;
		uपूर्णांक64_t o_mode:1;
		uपूर्णांक64_t hp_enb:1;
		uपूर्णांक64_t lp_enb:1;
		uपूर्णांक64_t csize:14;
#अन्यथा
		uपूर्णांक64_t csize:14;
		uपूर्णांक64_t lp_enb:1;
		uपूर्णांक64_t hp_enb:1;
		uपूर्णांक64_t o_mode:1;
		uपूर्णांक64_t o_es:2;
		uपूर्णांक64_t o_ns:1;
		uपूर्णांक64_t o_ro:1;
		uपूर्णांक64_t o_add1:1;
		uपूर्णांक64_t fpa_que:3;
		uपूर्णांक64_t dwb_ichk:9;
		uपूर्णांक64_t dwb_denb:1;
		uपूर्णांक64_t b0_lend:1;
		uपूर्णांक64_t reserved_36_63:28;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_dma_highp_counts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_dma_highp_counts_s अणु
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

जोड़ cvmx_npi_dma_highp_naddr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_dma_highp_naddr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t state:4;
		uपूर्णांक64_t addr:36;
#अन्यथा
		uपूर्णांक64_t addr:36;
		uपूर्णांक64_t state:4;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_dma_lowp_counts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_dma_lowp_counts_s अणु
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

जोड़ cvmx_npi_dma_lowp_naddr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_dma_lowp_naddr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t state:4;
		uपूर्णांक64_t addr:36;
#अन्यथा
		uपूर्णांक64_t addr:36;
		uपूर्णांक64_t state:4;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_highp_dbell अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_highp_dbell_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t dbell:16;
#अन्यथा
		uपूर्णांक64_t dbell:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_highp_ibuff_saddr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_highp_ibuff_saddr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_36_63:28;
		uपूर्णांक64_t saddr:36;
#अन्यथा
		uपूर्णांक64_t saddr:36;
		uपूर्णांक64_t reserved_36_63:28;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_input_control अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_input_control_s अणु
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
	काष्ठा cvmx_npi_input_control_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_22_63:42;
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
		uपूर्णांक64_t reserved_22_63:42;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_npi_पूर्णांक_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_पूर्णांक_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t q1_a_f:1;
		uपूर्णांक64_t q1_s_e:1;
		uपूर्णांक64_t pdf_p_f:1;
		uपूर्णांक64_t pdf_p_e:1;
		uपूर्णांक64_t pcf_p_f:1;
		uपूर्णांक64_t pcf_p_e:1;
		uपूर्णांक64_t rdx_s_e:1;
		uपूर्णांक64_t rwx_s_e:1;
		uपूर्णांक64_t pnc_a_f:1;
		uपूर्णांक64_t pnc_s_e:1;
		uपूर्णांक64_t com_a_f:1;
		uपूर्णांक64_t com_s_e:1;
		uपूर्णांक64_t q3_a_f:1;
		uपूर्णांक64_t q3_s_e:1;
		uपूर्णांक64_t q2_a_f:1;
		uपूर्णांक64_t q2_s_e:1;
		uपूर्णांक64_t pcr_a_f:1;
		uपूर्णांक64_t pcr_s_e:1;
		uपूर्णांक64_t fcr_a_f:1;
		uपूर्णांक64_t fcr_s_e:1;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t i3_pperr:1;
		uपूर्णांक64_t i2_pperr:1;
		uपूर्णांक64_t i1_pperr:1;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t p3_ptout:1;
		uपूर्णांक64_t p2_ptout:1;
		uपूर्णांक64_t p1_ptout:1;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t p3_pperr:1;
		uपूर्णांक64_t p2_pperr:1;
		uपूर्णांक64_t p1_pperr:1;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t g3_rtout:1;
		uपूर्णांक64_t g2_rtout:1;
		uपूर्णांक64_t g1_rtout:1;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t p3_perr:1;
		uपूर्णांक64_t p2_perr:1;
		uपूर्णांक64_t p1_perr:1;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t p3_rtout:1;
		uपूर्णांक64_t p2_rtout:1;
		uपूर्णांक64_t p1_rtout:1;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t i3_overf:1;
		uपूर्णांक64_t i2_overf:1;
		uपूर्णांक64_t i1_overf:1;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t i3_rtout:1;
		uपूर्णांक64_t i2_rtout:1;
		uपूर्णांक64_t i1_rtout:1;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t po3_2sml:1;
		uपूर्णांक64_t po2_2sml:1;
		uपूर्णांक64_t po1_2sml:1;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t po1_2sml:1;
		uपूर्णांक64_t po2_2sml:1;
		uपूर्णांक64_t po3_2sml:1;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t i1_rtout:1;
		uपूर्णांक64_t i2_rtout:1;
		uपूर्णांक64_t i3_rtout:1;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t i1_overf:1;
		uपूर्णांक64_t i2_overf:1;
		uपूर्णांक64_t i3_overf:1;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t p1_rtout:1;
		uपूर्णांक64_t p2_rtout:1;
		uपूर्णांक64_t p3_rtout:1;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t p1_perr:1;
		uपूर्णांक64_t p2_perr:1;
		uपूर्णांक64_t p3_perr:1;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t g1_rtout:1;
		uपूर्णांक64_t g2_rtout:1;
		uपूर्णांक64_t g3_rtout:1;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t p1_pperr:1;
		uपूर्णांक64_t p2_pperr:1;
		uपूर्णांक64_t p3_pperr:1;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t p1_ptout:1;
		uपूर्णांक64_t p2_ptout:1;
		uपूर्णांक64_t p3_ptout:1;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t i1_pperr:1;
		uपूर्णांक64_t i2_pperr:1;
		uपूर्णांक64_t i3_pperr:1;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t fcr_s_e:1;
		uपूर्णांक64_t fcr_a_f:1;
		uपूर्णांक64_t pcr_s_e:1;
		uपूर्णांक64_t pcr_a_f:1;
		uपूर्णांक64_t q2_s_e:1;
		uपूर्णांक64_t q2_a_f:1;
		uपूर्णांक64_t q3_s_e:1;
		uपूर्णांक64_t q3_a_f:1;
		uपूर्णांक64_t com_s_e:1;
		uपूर्णांक64_t com_a_f:1;
		uपूर्णांक64_t pnc_s_e:1;
		uपूर्णांक64_t pnc_a_f:1;
		uपूर्णांक64_t rwx_s_e:1;
		uपूर्णांक64_t rdx_s_e:1;
		uपूर्णांक64_t pcf_p_e:1;
		uपूर्णांक64_t pcf_p_f:1;
		uपूर्णांक64_t pdf_p_e:1;
		uपूर्णांक64_t pdf_p_f:1;
		uपूर्णांक64_t q1_s_e:1;
		uपूर्णांक64_t q1_a_f:1;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npi_पूर्णांक_enb_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t q1_a_f:1;
		uपूर्णांक64_t q1_s_e:1;
		uपूर्णांक64_t pdf_p_f:1;
		uपूर्णांक64_t pdf_p_e:1;
		uपूर्णांक64_t pcf_p_f:1;
		uपूर्णांक64_t pcf_p_e:1;
		uपूर्णांक64_t rdx_s_e:1;
		uपूर्णांक64_t rwx_s_e:1;
		uपूर्णांक64_t pnc_a_f:1;
		uपूर्णांक64_t pnc_s_e:1;
		uपूर्णांक64_t com_a_f:1;
		uपूर्णांक64_t com_s_e:1;
		uपूर्णांक64_t q3_a_f:1;
		uपूर्णांक64_t q3_s_e:1;
		uपूर्णांक64_t q2_a_f:1;
		uपूर्णांक64_t q2_s_e:1;
		uपूर्णांक64_t pcr_a_f:1;
		uपूर्णांक64_t pcr_s_e:1;
		uपूर्णांक64_t fcr_a_f:1;
		uपूर्णांक64_t fcr_s_e:1;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t reserved_36_38:3;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t reserved_32_34:3;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t reserved_28_30:3;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t reserved_24_26:3;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t reserved_20_22:3;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t reserved_12_14:3;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t reserved_8_10:3;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t reserved_4_6:3;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t reserved_4_6:3;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t reserved_8_10:3;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t reserved_12_14:3;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t reserved_20_22:3;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t reserved_24_26:3;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t reserved_28_30:3;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t reserved_32_34:3;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t reserved_36_38:3;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t fcr_s_e:1;
		uपूर्णांक64_t fcr_a_f:1;
		uपूर्णांक64_t pcr_s_e:1;
		uपूर्णांक64_t pcr_a_f:1;
		uपूर्णांक64_t q2_s_e:1;
		uपूर्णांक64_t q2_a_f:1;
		uपूर्णांक64_t q3_s_e:1;
		uपूर्णांक64_t q3_a_f:1;
		uपूर्णांक64_t com_s_e:1;
		uपूर्णांक64_t com_a_f:1;
		uपूर्णांक64_t pnc_s_e:1;
		uपूर्णांक64_t pnc_a_f:1;
		uपूर्णांक64_t rwx_s_e:1;
		uपूर्णांक64_t rdx_s_e:1;
		uपूर्णांक64_t pcf_p_e:1;
		uपूर्णांक64_t pcf_p_f:1;
		uपूर्णांक64_t pdf_p_e:1;
		uपूर्णांक64_t pdf_p_f:1;
		uपूर्णांक64_t q1_s_e:1;
		uपूर्णांक64_t q1_a_f:1;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_npi_पूर्णांक_enb_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t q1_a_f:1;
		uपूर्णांक64_t q1_s_e:1;
		uपूर्णांक64_t pdf_p_f:1;
		uपूर्णांक64_t pdf_p_e:1;
		uपूर्णांक64_t pcf_p_f:1;
		uपूर्णांक64_t pcf_p_e:1;
		uपूर्णांक64_t rdx_s_e:1;
		uपूर्णांक64_t rwx_s_e:1;
		uपूर्णांक64_t pnc_a_f:1;
		uपूर्णांक64_t pnc_s_e:1;
		uपूर्णांक64_t com_a_f:1;
		uपूर्णांक64_t com_s_e:1;
		uपूर्णांक64_t q3_a_f:1;
		uपूर्णांक64_t q3_s_e:1;
		uपूर्णांक64_t q2_a_f:1;
		uपूर्णांक64_t q2_s_e:1;
		uपूर्णांक64_t pcr_a_f:1;
		uपूर्णांक64_t pcr_s_e:1;
		uपूर्णांक64_t fcr_a_f:1;
		uपूर्णांक64_t fcr_s_e:1;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t reserved_37_38:2;
		uपूर्णांक64_t i1_pperr:1;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t reserved_33_34:2;
		uपूर्णांक64_t p1_ptout:1;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t reserved_29_30:2;
		uपूर्णांक64_t p1_pperr:1;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t reserved_25_26:2;
		uपूर्णांक64_t g1_rtout:1;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t reserved_21_22:2;
		uपूर्णांक64_t p1_perr:1;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t reserved_17_18:2;
		uपूर्णांक64_t p1_rtout:1;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t reserved_13_14:2;
		uपूर्णांक64_t i1_overf:1;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t reserved_9_10:2;
		uपूर्णांक64_t i1_rtout:1;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t po1_2sml:1;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t po1_2sml:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t i1_rtout:1;
		uपूर्णांक64_t reserved_9_10:2;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t i1_overf:1;
		uपूर्णांक64_t reserved_13_14:2;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t p1_rtout:1;
		uपूर्णांक64_t reserved_17_18:2;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t p1_perr:1;
		uपूर्णांक64_t reserved_21_22:2;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t g1_rtout:1;
		uपूर्णांक64_t reserved_25_26:2;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t p1_pperr:1;
		uपूर्णांक64_t reserved_29_30:2;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t p1_ptout:1;
		uपूर्णांक64_t reserved_33_34:2;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t i1_pperr:1;
		uपूर्णांक64_t reserved_37_38:2;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t fcr_s_e:1;
		uपूर्णांक64_t fcr_a_f:1;
		uपूर्णांक64_t pcr_s_e:1;
		uपूर्णांक64_t pcr_a_f:1;
		uपूर्णांक64_t q2_s_e:1;
		uपूर्णांक64_t q2_a_f:1;
		uपूर्णांक64_t q3_s_e:1;
		uपूर्णांक64_t q3_a_f:1;
		uपूर्णांक64_t com_s_e:1;
		uपूर्णांक64_t com_a_f:1;
		uपूर्णांक64_t pnc_s_e:1;
		uपूर्णांक64_t pnc_a_f:1;
		uपूर्णांक64_t rwx_s_e:1;
		uपूर्णांक64_t rdx_s_e:1;
		uपूर्णांक64_t pcf_p_e:1;
		uपूर्णांक64_t pcf_p_f:1;
		uपूर्णांक64_t pdf_p_e:1;
		uपूर्णांक64_t pdf_p_f:1;
		uपूर्णांक64_t q1_s_e:1;
		uपूर्णांक64_t q1_a_f:1;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_npi_पूर्णांक_enb_cn38xxp2 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_42_63:22;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t i3_pperr:1;
		uपूर्णांक64_t i2_pperr:1;
		uपूर्णांक64_t i1_pperr:1;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t p3_ptout:1;
		uपूर्णांक64_t p2_ptout:1;
		uपूर्णांक64_t p1_ptout:1;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t p3_pperr:1;
		uपूर्णांक64_t p2_pperr:1;
		uपूर्णांक64_t p1_pperr:1;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t g3_rtout:1;
		uपूर्णांक64_t g2_rtout:1;
		uपूर्णांक64_t g1_rtout:1;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t p3_perr:1;
		uपूर्णांक64_t p2_perr:1;
		uपूर्णांक64_t p1_perr:1;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t p3_rtout:1;
		uपूर्णांक64_t p2_rtout:1;
		uपूर्णांक64_t p1_rtout:1;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t i3_overf:1;
		uपूर्णांक64_t i2_overf:1;
		uपूर्णांक64_t i1_overf:1;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t i3_rtout:1;
		uपूर्णांक64_t i2_rtout:1;
		uपूर्णांक64_t i1_rtout:1;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t po3_2sml:1;
		uपूर्णांक64_t po2_2sml:1;
		uपूर्णांक64_t po1_2sml:1;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t po1_2sml:1;
		uपूर्णांक64_t po2_2sml:1;
		uपूर्णांक64_t po3_2sml:1;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t i1_rtout:1;
		uपूर्णांक64_t i2_rtout:1;
		uपूर्णांक64_t i3_rtout:1;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t i1_overf:1;
		uपूर्णांक64_t i2_overf:1;
		uपूर्णांक64_t i3_overf:1;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t p1_rtout:1;
		uपूर्णांक64_t p2_rtout:1;
		uपूर्णांक64_t p3_rtout:1;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t p1_perr:1;
		uपूर्णांक64_t p2_perr:1;
		uपूर्णांक64_t p3_perr:1;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t g1_rtout:1;
		uपूर्णांक64_t g2_rtout:1;
		uपूर्णांक64_t g3_rtout:1;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t p1_pperr:1;
		uपूर्णांक64_t p2_pperr:1;
		uपूर्णांक64_t p3_pperr:1;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t p1_ptout:1;
		uपूर्णांक64_t p2_ptout:1;
		uपूर्णांक64_t p3_ptout:1;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t i1_pperr:1;
		uपूर्णांक64_t i2_pperr:1;
		uपूर्णांक64_t i3_pperr:1;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t reserved_42_63:22;
#पूर्ण_अगर
	पूर्ण cn38xxp2;
पूर्ण;

जोड़ cvmx_npi_पूर्णांक_sum अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_पूर्णांक_sum_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t q1_a_f:1;
		uपूर्णांक64_t q1_s_e:1;
		uपूर्णांक64_t pdf_p_f:1;
		uपूर्णांक64_t pdf_p_e:1;
		uपूर्णांक64_t pcf_p_f:1;
		uपूर्णांक64_t pcf_p_e:1;
		uपूर्णांक64_t rdx_s_e:1;
		uपूर्णांक64_t rwx_s_e:1;
		uपूर्णांक64_t pnc_a_f:1;
		uपूर्णांक64_t pnc_s_e:1;
		uपूर्णांक64_t com_a_f:1;
		uपूर्णांक64_t com_s_e:1;
		uपूर्णांक64_t q3_a_f:1;
		uपूर्णांक64_t q3_s_e:1;
		uपूर्णांक64_t q2_a_f:1;
		uपूर्णांक64_t q2_s_e:1;
		uपूर्णांक64_t pcr_a_f:1;
		uपूर्णांक64_t pcr_s_e:1;
		uपूर्णांक64_t fcr_a_f:1;
		uपूर्णांक64_t fcr_s_e:1;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t i3_pperr:1;
		uपूर्णांक64_t i2_pperr:1;
		uपूर्णांक64_t i1_pperr:1;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t p3_ptout:1;
		uपूर्णांक64_t p2_ptout:1;
		uपूर्णांक64_t p1_ptout:1;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t p3_pperr:1;
		uपूर्णांक64_t p2_pperr:1;
		uपूर्णांक64_t p1_pperr:1;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t g3_rtout:1;
		uपूर्णांक64_t g2_rtout:1;
		uपूर्णांक64_t g1_rtout:1;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t p3_perr:1;
		uपूर्णांक64_t p2_perr:1;
		uपूर्णांक64_t p1_perr:1;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t p3_rtout:1;
		uपूर्णांक64_t p2_rtout:1;
		uपूर्णांक64_t p1_rtout:1;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t i3_overf:1;
		uपूर्णांक64_t i2_overf:1;
		uपूर्णांक64_t i1_overf:1;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t i3_rtout:1;
		uपूर्णांक64_t i2_rtout:1;
		uपूर्णांक64_t i1_rtout:1;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t po3_2sml:1;
		uपूर्णांक64_t po2_2sml:1;
		uपूर्णांक64_t po1_2sml:1;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t po1_2sml:1;
		uपूर्णांक64_t po2_2sml:1;
		uपूर्णांक64_t po3_2sml:1;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t i1_rtout:1;
		uपूर्णांक64_t i2_rtout:1;
		uपूर्णांक64_t i3_rtout:1;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t i1_overf:1;
		uपूर्णांक64_t i2_overf:1;
		uपूर्णांक64_t i3_overf:1;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t p1_rtout:1;
		uपूर्णांक64_t p2_rtout:1;
		uपूर्णांक64_t p3_rtout:1;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t p1_perr:1;
		uपूर्णांक64_t p2_perr:1;
		uपूर्णांक64_t p3_perr:1;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t g1_rtout:1;
		uपूर्णांक64_t g2_rtout:1;
		uपूर्णांक64_t g3_rtout:1;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t p1_pperr:1;
		uपूर्णांक64_t p2_pperr:1;
		uपूर्णांक64_t p3_pperr:1;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t p1_ptout:1;
		uपूर्णांक64_t p2_ptout:1;
		uपूर्णांक64_t p3_ptout:1;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t i1_pperr:1;
		uपूर्णांक64_t i2_pperr:1;
		uपूर्णांक64_t i3_pperr:1;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t fcr_s_e:1;
		uपूर्णांक64_t fcr_a_f:1;
		uपूर्णांक64_t pcr_s_e:1;
		uपूर्णांक64_t pcr_a_f:1;
		uपूर्णांक64_t q2_s_e:1;
		uपूर्णांक64_t q2_a_f:1;
		uपूर्णांक64_t q3_s_e:1;
		uपूर्णांक64_t q3_a_f:1;
		uपूर्णांक64_t com_s_e:1;
		uपूर्णांक64_t com_a_f:1;
		uपूर्णांक64_t pnc_s_e:1;
		uपूर्णांक64_t pnc_a_f:1;
		uपूर्णांक64_t rwx_s_e:1;
		uपूर्णांक64_t rdx_s_e:1;
		uपूर्णांक64_t pcf_p_e:1;
		uपूर्णांक64_t pcf_p_f:1;
		uपूर्णांक64_t pdf_p_e:1;
		uपूर्णांक64_t pdf_p_f:1;
		uपूर्णांक64_t q1_s_e:1;
		uपूर्णांक64_t q1_a_f:1;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npi_पूर्णांक_sum_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t q1_a_f:1;
		uपूर्णांक64_t q1_s_e:1;
		uपूर्णांक64_t pdf_p_f:1;
		uपूर्णांक64_t pdf_p_e:1;
		uपूर्णांक64_t pcf_p_f:1;
		uपूर्णांक64_t pcf_p_e:1;
		uपूर्णांक64_t rdx_s_e:1;
		uपूर्णांक64_t rwx_s_e:1;
		uपूर्णांक64_t pnc_a_f:1;
		uपूर्णांक64_t pnc_s_e:1;
		uपूर्णांक64_t com_a_f:1;
		uपूर्णांक64_t com_s_e:1;
		uपूर्णांक64_t q3_a_f:1;
		uपूर्णांक64_t q3_s_e:1;
		uपूर्णांक64_t q2_a_f:1;
		uपूर्णांक64_t q2_s_e:1;
		uपूर्णांक64_t pcr_a_f:1;
		uपूर्णांक64_t pcr_s_e:1;
		uपूर्णांक64_t fcr_a_f:1;
		uपूर्णांक64_t fcr_s_e:1;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t reserved_36_38:3;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t reserved_32_34:3;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t reserved_28_30:3;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t reserved_24_26:3;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t reserved_20_22:3;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t reserved_12_14:3;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t reserved_8_10:3;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t reserved_4_6:3;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t reserved_4_6:3;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t reserved_8_10:3;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t reserved_12_14:3;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t reserved_20_22:3;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t reserved_24_26:3;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t reserved_28_30:3;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t reserved_32_34:3;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t reserved_36_38:3;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t fcr_s_e:1;
		uपूर्णांक64_t fcr_a_f:1;
		uपूर्णांक64_t pcr_s_e:1;
		uपूर्णांक64_t pcr_a_f:1;
		uपूर्णांक64_t q2_s_e:1;
		uपूर्णांक64_t q2_a_f:1;
		uपूर्णांक64_t q3_s_e:1;
		uपूर्णांक64_t q3_a_f:1;
		uपूर्णांक64_t com_s_e:1;
		uपूर्णांक64_t com_a_f:1;
		uपूर्णांक64_t pnc_s_e:1;
		uपूर्णांक64_t pnc_a_f:1;
		uपूर्णांक64_t rwx_s_e:1;
		uपूर्णांक64_t rdx_s_e:1;
		uपूर्णांक64_t pcf_p_e:1;
		uपूर्णांक64_t pcf_p_f:1;
		uपूर्णांक64_t pdf_p_e:1;
		uपूर्णांक64_t pdf_p_f:1;
		uपूर्णांक64_t q1_s_e:1;
		uपूर्णांक64_t q1_a_f:1;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_npi_पूर्णांक_sum_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t q1_a_f:1;
		uपूर्णांक64_t q1_s_e:1;
		uपूर्णांक64_t pdf_p_f:1;
		uपूर्णांक64_t pdf_p_e:1;
		uपूर्णांक64_t pcf_p_f:1;
		uपूर्णांक64_t pcf_p_e:1;
		uपूर्णांक64_t rdx_s_e:1;
		uपूर्णांक64_t rwx_s_e:1;
		uपूर्णांक64_t pnc_a_f:1;
		uपूर्णांक64_t pnc_s_e:1;
		uपूर्णांक64_t com_a_f:1;
		uपूर्णांक64_t com_s_e:1;
		uपूर्णांक64_t q3_a_f:1;
		uपूर्णांक64_t q3_s_e:1;
		uपूर्णांक64_t q2_a_f:1;
		uपूर्णांक64_t q2_s_e:1;
		uपूर्णांक64_t pcr_a_f:1;
		uपूर्णांक64_t pcr_s_e:1;
		uपूर्णांक64_t fcr_a_f:1;
		uपूर्णांक64_t fcr_s_e:1;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t reserved_37_38:2;
		uपूर्णांक64_t i1_pperr:1;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t reserved_33_34:2;
		uपूर्णांक64_t p1_ptout:1;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t reserved_29_30:2;
		uपूर्णांक64_t p1_pperr:1;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t reserved_25_26:2;
		uपूर्णांक64_t g1_rtout:1;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t reserved_21_22:2;
		uपूर्णांक64_t p1_perr:1;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t reserved_17_18:2;
		uपूर्णांक64_t p1_rtout:1;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t reserved_13_14:2;
		uपूर्णांक64_t i1_overf:1;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t reserved_9_10:2;
		uपूर्णांक64_t i1_rtout:1;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t po1_2sml:1;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t po1_2sml:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t i1_rtout:1;
		uपूर्णांक64_t reserved_9_10:2;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t i1_overf:1;
		uपूर्णांक64_t reserved_13_14:2;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t p1_rtout:1;
		uपूर्णांक64_t reserved_17_18:2;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t p1_perr:1;
		uपूर्णांक64_t reserved_21_22:2;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t g1_rtout:1;
		uपूर्णांक64_t reserved_25_26:2;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t p1_pperr:1;
		uपूर्णांक64_t reserved_29_30:2;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t p1_ptout:1;
		uपूर्णांक64_t reserved_33_34:2;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t i1_pperr:1;
		uपूर्णांक64_t reserved_37_38:2;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t fcr_s_e:1;
		uपूर्णांक64_t fcr_a_f:1;
		uपूर्णांक64_t pcr_s_e:1;
		uपूर्णांक64_t pcr_a_f:1;
		uपूर्णांक64_t q2_s_e:1;
		uपूर्णांक64_t q2_a_f:1;
		uपूर्णांक64_t q3_s_e:1;
		uपूर्णांक64_t q3_a_f:1;
		uपूर्णांक64_t com_s_e:1;
		uपूर्णांक64_t com_a_f:1;
		uपूर्णांक64_t pnc_s_e:1;
		uपूर्णांक64_t pnc_a_f:1;
		uपूर्णांक64_t rwx_s_e:1;
		uपूर्णांक64_t rdx_s_e:1;
		uपूर्णांक64_t pcf_p_e:1;
		uपूर्णांक64_t pcf_p_f:1;
		uपूर्णांक64_t pdf_p_e:1;
		uपूर्णांक64_t pdf_p_f:1;
		uपूर्णांक64_t q1_s_e:1;
		uपूर्णांक64_t q1_a_f:1;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_npi_पूर्णांक_sum_cn38xxp2 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_42_63:22;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t i3_pperr:1;
		uपूर्णांक64_t i2_pperr:1;
		uपूर्णांक64_t i1_pperr:1;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t p3_ptout:1;
		uपूर्णांक64_t p2_ptout:1;
		uपूर्णांक64_t p1_ptout:1;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t p3_pperr:1;
		uपूर्णांक64_t p2_pperr:1;
		uपूर्णांक64_t p1_pperr:1;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t g3_rtout:1;
		uपूर्णांक64_t g2_rtout:1;
		uपूर्णांक64_t g1_rtout:1;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t p3_perr:1;
		uपूर्णांक64_t p2_perr:1;
		uपूर्णांक64_t p1_perr:1;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t p3_rtout:1;
		uपूर्णांक64_t p2_rtout:1;
		uपूर्णांक64_t p1_rtout:1;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t i3_overf:1;
		uपूर्णांक64_t i2_overf:1;
		uपूर्णांक64_t i1_overf:1;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t i3_rtout:1;
		uपूर्णांक64_t i2_rtout:1;
		uपूर्णांक64_t i1_rtout:1;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t po3_2sml:1;
		uपूर्णांक64_t po2_2sml:1;
		uपूर्णांक64_t po1_2sml:1;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t rml_rto:1;
#अन्यथा
		uपूर्णांक64_t rml_rto:1;
		uपूर्णांक64_t rml_wto:1;
		uपूर्णांक64_t pci_rsl:1;
		uपूर्णांक64_t po0_2sml:1;
		uपूर्णांक64_t po1_2sml:1;
		uपूर्णांक64_t po2_2sml:1;
		uपूर्णांक64_t po3_2sml:1;
		uपूर्णांक64_t i0_rtout:1;
		uपूर्णांक64_t i1_rtout:1;
		uपूर्णांक64_t i2_rtout:1;
		uपूर्णांक64_t i3_rtout:1;
		uपूर्णांक64_t i0_overf:1;
		uपूर्णांक64_t i1_overf:1;
		uपूर्णांक64_t i2_overf:1;
		uपूर्णांक64_t i3_overf:1;
		uपूर्णांक64_t p0_rtout:1;
		uपूर्णांक64_t p1_rtout:1;
		uपूर्णांक64_t p2_rtout:1;
		uपूर्णांक64_t p3_rtout:1;
		uपूर्णांक64_t p0_perr:1;
		uपूर्णांक64_t p1_perr:1;
		uपूर्णांक64_t p2_perr:1;
		uपूर्णांक64_t p3_perr:1;
		uपूर्णांक64_t g0_rtout:1;
		uपूर्णांक64_t g1_rtout:1;
		uपूर्णांक64_t g2_rtout:1;
		uपूर्णांक64_t g3_rtout:1;
		uपूर्णांक64_t p0_pperr:1;
		uपूर्णांक64_t p1_pperr:1;
		uपूर्णांक64_t p2_pperr:1;
		uपूर्णांक64_t p3_pperr:1;
		uपूर्णांक64_t p0_ptout:1;
		uपूर्णांक64_t p1_ptout:1;
		uपूर्णांक64_t p2_ptout:1;
		uपूर्णांक64_t p3_ptout:1;
		uपूर्णांक64_t i0_pperr:1;
		uपूर्णांक64_t i1_pperr:1;
		uपूर्णांक64_t i2_pperr:1;
		uपूर्णांक64_t i3_pperr:1;
		uपूर्णांक64_t win_rto:1;
		uपूर्णांक64_t p_dperr:1;
		uपूर्णांक64_t iobdma:1;
		uपूर्णांक64_t reserved_42_63:22;
#पूर्ण_अगर
	पूर्ण cn38xxp2;
पूर्ण;

जोड़ cvmx_npi_lowp_dbell अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_lowp_dbell_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t dbell:16;
#अन्यथा
		uपूर्णांक64_t dbell:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_lowp_ibuff_saddr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_lowp_ibuff_saddr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_36_63:28;
		uपूर्णांक64_t saddr:36;
#अन्यथा
		uपूर्णांक64_t saddr:36;
		uपूर्णांक64_t reserved_36_63:28;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_mem_access_subidx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_mem_access_subidx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_38_63:26;
		uपूर्णांक64_t लघुl:1;
		uपूर्णांक64_t nmerge:1;
		uपूर्णांक64_t esr:2;
		uपूर्णांक64_t esw:2;
		uपूर्णांक64_t nsr:1;
		uपूर्णांक64_t nsw:1;
		uपूर्णांक64_t ror:1;
		uपूर्णांक64_t row:1;
		uपूर्णांक64_t ba:28;
#अन्यथा
		uपूर्णांक64_t ba:28;
		uपूर्णांक64_t row:1;
		uपूर्णांक64_t ror:1;
		uपूर्णांक64_t nsw:1;
		uपूर्णांक64_t nsr:1;
		uपूर्णांक64_t esw:2;
		uपूर्णांक64_t esr:2;
		uपूर्णांक64_t nmerge:1;
		uपूर्णांक64_t लघुl:1;
		uपूर्णांक64_t reserved_38_63:26;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npi_mem_access_subidx_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_36_63:28;
		uपूर्णांक64_t esr:2;
		uपूर्णांक64_t esw:2;
		uपूर्णांक64_t nsr:1;
		uपूर्णांक64_t nsw:1;
		uपूर्णांक64_t ror:1;
		uपूर्णांक64_t row:1;
		uपूर्णांक64_t ba:28;
#अन्यथा
		uपूर्णांक64_t ba:28;
		uपूर्णांक64_t row:1;
		uपूर्णांक64_t ror:1;
		uपूर्णांक64_t nsw:1;
		uपूर्णांक64_t nsr:1;
		uपूर्णांक64_t esw:2;
		uपूर्णांक64_t esr:2;
		uपूर्णांक64_t reserved_36_63:28;
#पूर्ण_अगर
	पूर्ण cn31xx;
पूर्ण;

जोड़ cvmx_npi_msi_rcv अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_msi_rcv_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t पूर्णांक_vec:64;
#अन्यथा
		uपूर्णांक64_t पूर्णांक_vec:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_num_desc_outputx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_num_desc_outputx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t size:32;
#अन्यथा
		uपूर्णांक64_t size:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_output_control अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_output_control_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_49_63:15;
		uपूर्णांक64_t pkt_rr:1;
		uपूर्णांक64_t p3_bmode:1;
		uपूर्णांक64_t p2_bmode:1;
		uपूर्णांक64_t p1_bmode:1;
		uपूर्णांक64_t p0_bmode:1;
		uपूर्णांक64_t o3_es:2;
		uपूर्णांक64_t o3_ns:1;
		uपूर्णांक64_t o3_ro:1;
		uपूर्णांक64_t o2_es:2;
		uपूर्णांक64_t o2_ns:1;
		uपूर्णांक64_t o2_ro:1;
		uपूर्णांक64_t o1_es:2;
		uपूर्णांक64_t o1_ns:1;
		uपूर्णांक64_t o1_ro:1;
		uपूर्णांक64_t o0_es:2;
		uपूर्णांक64_t o0_ns:1;
		uपूर्णांक64_t o0_ro:1;
		uपूर्णांक64_t o3_csrm:1;
		uपूर्णांक64_t o2_csrm:1;
		uपूर्णांक64_t o1_csrm:1;
		uपूर्णांक64_t o0_csrm:1;
		uपूर्णांक64_t reserved_20_23:4;
		uपूर्णांक64_t iptr_o3:1;
		uपूर्णांक64_t iptr_o2:1;
		uपूर्णांक64_t iptr_o1:1;
		uपूर्णांक64_t iptr_o0:1;
		uपूर्णांक64_t esr_sl3:2;
		uपूर्णांक64_t nsr_sl3:1;
		uपूर्णांक64_t ror_sl3:1;
		uपूर्णांक64_t esr_sl2:2;
		uपूर्णांक64_t nsr_sl2:1;
		uपूर्णांक64_t ror_sl2:1;
		uपूर्णांक64_t esr_sl1:2;
		uपूर्णांक64_t nsr_sl1:1;
		uपूर्णांक64_t ror_sl1:1;
		uपूर्णांक64_t esr_sl0:2;
		uपूर्णांक64_t nsr_sl0:1;
		uपूर्णांक64_t ror_sl0:1;
#अन्यथा
		uपूर्णांक64_t ror_sl0:1;
		uपूर्णांक64_t nsr_sl0:1;
		uपूर्णांक64_t esr_sl0:2;
		uपूर्णांक64_t ror_sl1:1;
		uपूर्णांक64_t nsr_sl1:1;
		uपूर्णांक64_t esr_sl1:2;
		uपूर्णांक64_t ror_sl2:1;
		uपूर्णांक64_t nsr_sl2:1;
		uपूर्णांक64_t esr_sl2:2;
		uपूर्णांक64_t ror_sl3:1;
		uपूर्णांक64_t nsr_sl3:1;
		uपूर्णांक64_t esr_sl3:2;
		uपूर्णांक64_t iptr_o0:1;
		uपूर्णांक64_t iptr_o1:1;
		uपूर्णांक64_t iptr_o2:1;
		uपूर्णांक64_t iptr_o3:1;
		uपूर्णांक64_t reserved_20_23:4;
		uपूर्णांक64_t o0_csrm:1;
		uपूर्णांक64_t o1_csrm:1;
		uपूर्णांक64_t o2_csrm:1;
		uपूर्णांक64_t o3_csrm:1;
		uपूर्णांक64_t o0_ro:1;
		uपूर्णांक64_t o0_ns:1;
		uपूर्णांक64_t o0_es:2;
		uपूर्णांक64_t o1_ro:1;
		uपूर्णांक64_t o1_ns:1;
		uपूर्णांक64_t o1_es:2;
		uपूर्णांक64_t o2_ro:1;
		uपूर्णांक64_t o2_ns:1;
		uपूर्णांक64_t o2_es:2;
		uपूर्णांक64_t o3_ro:1;
		uपूर्णांक64_t o3_ns:1;
		uपूर्णांक64_t o3_es:2;
		uपूर्णांक64_t p0_bmode:1;
		uपूर्णांक64_t p1_bmode:1;
		uपूर्णांक64_t p2_bmode:1;
		uपूर्णांक64_t p3_bmode:1;
		uपूर्णांक64_t pkt_rr:1;
		uपूर्णांक64_t reserved_49_63:15;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npi_output_control_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_45_63:19;
		uपूर्णांक64_t p0_bmode:1;
		uपूर्णांक64_t reserved_32_43:12;
		uपूर्णांक64_t o0_es:2;
		uपूर्णांक64_t o0_ns:1;
		uपूर्णांक64_t o0_ro:1;
		uपूर्णांक64_t reserved_25_27:3;
		uपूर्णांक64_t o0_csrm:1;
		uपूर्णांक64_t reserved_17_23:7;
		uपूर्णांक64_t iptr_o0:1;
		uपूर्णांक64_t reserved_4_15:12;
		uपूर्णांक64_t esr_sl0:2;
		uपूर्णांक64_t nsr_sl0:1;
		uपूर्णांक64_t ror_sl0:1;
#अन्यथा
		uपूर्णांक64_t ror_sl0:1;
		uपूर्णांक64_t nsr_sl0:1;
		uपूर्णांक64_t esr_sl0:2;
		uपूर्णांक64_t reserved_4_15:12;
		uपूर्णांक64_t iptr_o0:1;
		uपूर्णांक64_t reserved_17_23:7;
		uपूर्णांक64_t o0_csrm:1;
		uपूर्णांक64_t reserved_25_27:3;
		uपूर्णांक64_t o0_ro:1;
		uपूर्णांक64_t o0_ns:1;
		uपूर्णांक64_t o0_es:2;
		uपूर्णांक64_t reserved_32_43:12;
		uपूर्णांक64_t p0_bmode:1;
		uपूर्णांक64_t reserved_45_63:19;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_npi_output_control_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_46_63:18;
		uपूर्णांक64_t p1_bmode:1;
		uपूर्णांक64_t p0_bmode:1;
		uपूर्णांक64_t reserved_36_43:8;
		uपूर्णांक64_t o1_es:2;
		uपूर्णांक64_t o1_ns:1;
		uपूर्णांक64_t o1_ro:1;
		uपूर्णांक64_t o0_es:2;
		uपूर्णांक64_t o0_ns:1;
		uपूर्णांक64_t o0_ro:1;
		uपूर्णांक64_t reserved_26_27:2;
		uपूर्णांक64_t o1_csrm:1;
		uपूर्णांक64_t o0_csrm:1;
		uपूर्णांक64_t reserved_18_23:6;
		uपूर्णांक64_t iptr_o1:1;
		uपूर्णांक64_t iptr_o0:1;
		uपूर्णांक64_t reserved_8_15:8;
		uपूर्णांक64_t esr_sl1:2;
		uपूर्णांक64_t nsr_sl1:1;
		uपूर्णांक64_t ror_sl1:1;
		uपूर्णांक64_t esr_sl0:2;
		uपूर्णांक64_t nsr_sl0:1;
		uपूर्णांक64_t ror_sl0:1;
#अन्यथा
		uपूर्णांक64_t ror_sl0:1;
		uपूर्णांक64_t nsr_sl0:1;
		uपूर्णांक64_t esr_sl0:2;
		uपूर्णांक64_t ror_sl1:1;
		uपूर्णांक64_t nsr_sl1:1;
		uपूर्णांक64_t esr_sl1:2;
		uपूर्णांक64_t reserved_8_15:8;
		uपूर्णांक64_t iptr_o0:1;
		uपूर्णांक64_t iptr_o1:1;
		uपूर्णांक64_t reserved_18_23:6;
		uपूर्णांक64_t o0_csrm:1;
		uपूर्णांक64_t o1_csrm:1;
		uपूर्णांक64_t reserved_26_27:2;
		uपूर्णांक64_t o0_ro:1;
		uपूर्णांक64_t o0_ns:1;
		uपूर्णांक64_t o0_es:2;
		uपूर्णांक64_t o1_ro:1;
		uपूर्णांक64_t o1_ns:1;
		uपूर्णांक64_t o1_es:2;
		uपूर्णांक64_t reserved_36_43:8;
		uपूर्णांक64_t p0_bmode:1;
		uपूर्णांक64_t p1_bmode:1;
		uपूर्णांक64_t reserved_46_63:18;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_npi_output_control_cn38xxp2 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t p3_bmode:1;
		uपूर्णांक64_t p2_bmode:1;
		uपूर्णांक64_t p1_bmode:1;
		uपूर्णांक64_t p0_bmode:1;
		uपूर्णांक64_t o3_es:2;
		uपूर्णांक64_t o3_ns:1;
		uपूर्णांक64_t o3_ro:1;
		uपूर्णांक64_t o2_es:2;
		uपूर्णांक64_t o2_ns:1;
		uपूर्णांक64_t o2_ro:1;
		uपूर्णांक64_t o1_es:2;
		uपूर्णांक64_t o1_ns:1;
		uपूर्णांक64_t o1_ro:1;
		uपूर्णांक64_t o0_es:2;
		uपूर्णांक64_t o0_ns:1;
		uपूर्णांक64_t o0_ro:1;
		uपूर्णांक64_t o3_csrm:1;
		uपूर्णांक64_t o2_csrm:1;
		uपूर्णांक64_t o1_csrm:1;
		uपूर्णांक64_t o0_csrm:1;
		uपूर्णांक64_t reserved_20_23:4;
		uपूर्णांक64_t iptr_o3:1;
		uपूर्णांक64_t iptr_o2:1;
		uपूर्णांक64_t iptr_o1:1;
		uपूर्णांक64_t iptr_o0:1;
		uपूर्णांक64_t esr_sl3:2;
		uपूर्णांक64_t nsr_sl3:1;
		uपूर्णांक64_t ror_sl3:1;
		uपूर्णांक64_t esr_sl2:2;
		uपूर्णांक64_t nsr_sl2:1;
		uपूर्णांक64_t ror_sl2:1;
		uपूर्णांक64_t esr_sl1:2;
		uपूर्णांक64_t nsr_sl1:1;
		uपूर्णांक64_t ror_sl1:1;
		uपूर्णांक64_t esr_sl0:2;
		uपूर्णांक64_t nsr_sl0:1;
		uपूर्णांक64_t ror_sl0:1;
#अन्यथा
		uपूर्णांक64_t ror_sl0:1;
		uपूर्णांक64_t nsr_sl0:1;
		uपूर्णांक64_t esr_sl0:2;
		uपूर्णांक64_t ror_sl1:1;
		uपूर्णांक64_t nsr_sl1:1;
		uपूर्णांक64_t esr_sl1:2;
		uपूर्णांक64_t ror_sl2:1;
		uपूर्णांक64_t nsr_sl2:1;
		uपूर्णांक64_t esr_sl2:2;
		uपूर्णांक64_t ror_sl3:1;
		uपूर्णांक64_t nsr_sl3:1;
		uपूर्णांक64_t esr_sl3:2;
		uपूर्णांक64_t iptr_o0:1;
		uपूर्णांक64_t iptr_o1:1;
		uपूर्णांक64_t iptr_o2:1;
		uपूर्णांक64_t iptr_o3:1;
		uपूर्णांक64_t reserved_20_23:4;
		uपूर्णांक64_t o0_csrm:1;
		uपूर्णांक64_t o1_csrm:1;
		uपूर्णांक64_t o2_csrm:1;
		uपूर्णांक64_t o3_csrm:1;
		uपूर्णांक64_t o0_ro:1;
		uपूर्णांक64_t o0_ns:1;
		uपूर्णांक64_t o0_es:2;
		uपूर्णांक64_t o1_ro:1;
		uपूर्णांक64_t o1_ns:1;
		uपूर्णांक64_t o1_es:2;
		uपूर्णांक64_t o2_ro:1;
		uपूर्णांक64_t o2_ns:1;
		uपूर्णांक64_t o2_es:2;
		uपूर्णांक64_t o3_ro:1;
		uपूर्णांक64_t o3_ns:1;
		uपूर्णांक64_t o3_es:2;
		uपूर्णांक64_t p0_bmode:1;
		uपूर्णांक64_t p1_bmode:1;
		uपूर्णांक64_t p2_bmode:1;
		uपूर्णांक64_t p3_bmode:1;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण cn38xxp2;
	काष्ठा cvmx_npi_output_control_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_49_63:15;
		uपूर्णांक64_t pkt_rr:1;
		uपूर्णांक64_t reserved_46_47:2;
		uपूर्णांक64_t p1_bmode:1;
		uपूर्णांक64_t p0_bmode:1;
		uपूर्णांक64_t reserved_36_43:8;
		uपूर्णांक64_t o1_es:2;
		uपूर्णांक64_t o1_ns:1;
		uपूर्णांक64_t o1_ro:1;
		uपूर्णांक64_t o0_es:2;
		uपूर्णांक64_t o0_ns:1;
		uपूर्णांक64_t o0_ro:1;
		uपूर्णांक64_t reserved_26_27:2;
		uपूर्णांक64_t o1_csrm:1;
		uपूर्णांक64_t o0_csrm:1;
		uपूर्णांक64_t reserved_18_23:6;
		uपूर्णांक64_t iptr_o1:1;
		uपूर्णांक64_t iptr_o0:1;
		uपूर्णांक64_t reserved_8_15:8;
		uपूर्णांक64_t esr_sl1:2;
		uपूर्णांक64_t nsr_sl1:1;
		uपूर्णांक64_t ror_sl1:1;
		uपूर्णांक64_t esr_sl0:2;
		uपूर्णांक64_t nsr_sl0:1;
		uपूर्णांक64_t ror_sl0:1;
#अन्यथा
		uपूर्णांक64_t ror_sl0:1;
		uपूर्णांक64_t nsr_sl0:1;
		uपूर्णांक64_t esr_sl0:2;
		uपूर्णांक64_t ror_sl1:1;
		uपूर्णांक64_t nsr_sl1:1;
		uपूर्णांक64_t esr_sl1:2;
		uपूर्णांक64_t reserved_8_15:8;
		uपूर्णांक64_t iptr_o0:1;
		uपूर्णांक64_t iptr_o1:1;
		uपूर्णांक64_t reserved_18_23:6;
		uपूर्णांक64_t o0_csrm:1;
		uपूर्णांक64_t o1_csrm:1;
		uपूर्णांक64_t reserved_26_27:2;
		uपूर्णांक64_t o0_ro:1;
		uपूर्णांक64_t o0_ns:1;
		uपूर्णांक64_t o0_es:2;
		uपूर्णांक64_t o1_ro:1;
		uपूर्णांक64_t o1_ns:1;
		uपूर्णांक64_t o1_es:2;
		uपूर्णांक64_t reserved_36_43:8;
		uपूर्णांक64_t p0_bmode:1;
		uपूर्णांक64_t p1_bmode:1;
		uपूर्णांक64_t reserved_46_47:2;
		uपूर्णांक64_t pkt_rr:1;
		uपूर्णांक64_t reserved_49_63:15;
#पूर्ण_अगर
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_npi_px_dbpair_addr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_px_dbpair_addr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_63_63:1;
		uपूर्णांक64_t state:2;
		uपूर्णांक64_t naddr:61;
#अन्यथा
		uपूर्णांक64_t naddr:61;
		uपूर्णांक64_t state:2;
		uपूर्णांक64_t reserved_63_63:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_px_instr_addr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_px_instr_addr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t state:3;
		uपूर्णांक64_t naddr:61;
#अन्यथा
		uपूर्णांक64_t naddr:61;
		uपूर्णांक64_t state:3;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_px_instr_cnts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_px_instr_cnts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_38_63:26;
		uपूर्णांक64_t fcnt:6;
		uपूर्णांक64_t avail:32;
#अन्यथा
		uपूर्णांक64_t avail:32;
		uपूर्णांक64_t fcnt:6;
		uपूर्णांक64_t reserved_38_63:26;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_px_pair_cnts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_px_pair_cnts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_37_63:27;
		uपूर्णांक64_t fcnt:5;
		uपूर्णांक64_t avail:32;
#अन्यथा
		uपूर्णांक64_t avail:32;
		uपूर्णांक64_t fcnt:5;
		uपूर्णांक64_t reserved_37_63:27;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_pci_burst_size अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_pci_burst_size_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t wr_brst:7;
		uपूर्णांक64_t rd_brst:7;
#अन्यथा
		uपूर्णांक64_t rd_brst:7;
		uपूर्णांक64_t wr_brst:7;
		uपूर्णांक64_t reserved_14_63:50;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_pci_पूर्णांक_arb_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_pci_पूर्णांक_arb_cfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t hosपंचांगode:1;
		uपूर्णांक64_t pci_ovr:4;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t park_mod:1;
		uपूर्णांक64_t park_dev:3;
#अन्यथा
		uपूर्णांक64_t park_dev:3;
		uपूर्णांक64_t park_mod:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t pci_ovr:4;
		uपूर्णांक64_t hosपंचांगode:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npi_pci_पूर्णांक_arb_cfg_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t park_mod:1;
		uपूर्णांक64_t park_dev:3;
#अन्यथा
		uपूर्णांक64_t park_dev:3;
		uपूर्णांक64_t park_mod:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_npi_pci_पढ़ो_cmd अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_pci_पढ़ो_cmd_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t cmd_size:11;
#अन्यथा
		uपूर्णांक64_t cmd_size:11;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_port32_instr_hdr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_port32_instr_hdr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t pbp:1;
		uपूर्णांक64_t rsv_f:5;
		uपूर्णांक64_t rparmode:2;
		uपूर्णांक64_t rsv_e:1;
		uपूर्णांक64_t rskp_len:7;
		uपूर्णांक64_t rsv_d:6;
		uपूर्णांक64_t use_ihdr:1;
		uपूर्णांक64_t rsv_c:5;
		uपूर्णांक64_t par_mode:2;
		uपूर्णांक64_t rsv_b:1;
		uपूर्णांक64_t skp_len:7;
		uपूर्णांक64_t rsv_a:6;
#अन्यथा
		uपूर्णांक64_t rsv_a:6;
		uपूर्णांक64_t skp_len:7;
		uपूर्णांक64_t rsv_b:1;
		uपूर्णांक64_t par_mode:2;
		uपूर्णांक64_t rsv_c:5;
		uपूर्णांक64_t use_ihdr:1;
		uपूर्णांक64_t rsv_d:6;
		uपूर्णांक64_t rskp_len:7;
		uपूर्णांक64_t rsv_e:1;
		uपूर्णांक64_t rparmode:2;
		uपूर्णांक64_t rsv_f:5;
		uपूर्णांक64_t pbp:1;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_port33_instr_hdr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_port33_instr_hdr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t pbp:1;
		uपूर्णांक64_t rsv_f:5;
		uपूर्णांक64_t rparmode:2;
		uपूर्णांक64_t rsv_e:1;
		uपूर्णांक64_t rskp_len:7;
		uपूर्णांक64_t rsv_d:6;
		uपूर्णांक64_t use_ihdr:1;
		uपूर्णांक64_t rsv_c:5;
		uपूर्णांक64_t par_mode:2;
		uपूर्णांक64_t rsv_b:1;
		uपूर्णांक64_t skp_len:7;
		uपूर्णांक64_t rsv_a:6;
#अन्यथा
		uपूर्णांक64_t rsv_a:6;
		uपूर्णांक64_t skp_len:7;
		uपूर्णांक64_t rsv_b:1;
		uपूर्णांक64_t par_mode:2;
		uपूर्णांक64_t rsv_c:5;
		uपूर्णांक64_t use_ihdr:1;
		uपूर्णांक64_t rsv_d:6;
		uपूर्णांक64_t rskp_len:7;
		uपूर्णांक64_t rsv_e:1;
		uपूर्णांक64_t rparmode:2;
		uपूर्णांक64_t rsv_f:5;
		uपूर्णांक64_t pbp:1;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_port34_instr_hdr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_port34_instr_hdr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t pbp:1;
		uपूर्णांक64_t rsv_f:5;
		uपूर्णांक64_t rparmode:2;
		uपूर्णांक64_t rsv_e:1;
		uपूर्णांक64_t rskp_len:7;
		uपूर्णांक64_t rsv_d:6;
		uपूर्णांक64_t use_ihdr:1;
		uपूर्णांक64_t rsv_c:5;
		uपूर्णांक64_t par_mode:2;
		uपूर्णांक64_t rsv_b:1;
		uपूर्णांक64_t skp_len:7;
		uपूर्णांक64_t rsv_a:6;
#अन्यथा
		uपूर्णांक64_t rsv_a:6;
		uपूर्णांक64_t skp_len:7;
		uपूर्णांक64_t rsv_b:1;
		uपूर्णांक64_t par_mode:2;
		uपूर्णांक64_t rsv_c:5;
		uपूर्णांक64_t use_ihdr:1;
		uपूर्णांक64_t rsv_d:6;
		uपूर्णांक64_t rskp_len:7;
		uपूर्णांक64_t rsv_e:1;
		uपूर्णांक64_t rparmode:2;
		uपूर्णांक64_t rsv_f:5;
		uपूर्णांक64_t pbp:1;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_port35_instr_hdr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_port35_instr_hdr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t pbp:1;
		uपूर्णांक64_t rsv_f:5;
		uपूर्णांक64_t rparmode:2;
		uपूर्णांक64_t rsv_e:1;
		uपूर्णांक64_t rskp_len:7;
		uपूर्णांक64_t rsv_d:6;
		uपूर्णांक64_t use_ihdr:1;
		uपूर्णांक64_t rsv_c:5;
		uपूर्णांक64_t par_mode:2;
		uपूर्णांक64_t rsv_b:1;
		uपूर्णांक64_t skp_len:7;
		uपूर्णांक64_t rsv_a:6;
#अन्यथा
		uपूर्णांक64_t rsv_a:6;
		uपूर्णांक64_t skp_len:7;
		uपूर्णांक64_t rsv_b:1;
		uपूर्णांक64_t par_mode:2;
		uपूर्णांक64_t rsv_c:5;
		uपूर्णांक64_t use_ihdr:1;
		uपूर्णांक64_t rsv_d:6;
		uपूर्णांक64_t rskp_len:7;
		uपूर्णांक64_t rsv_e:1;
		uपूर्णांक64_t rparmode:2;
		uपूर्णांक64_t rsv_f:5;
		uपूर्णांक64_t pbp:1;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_port_bp_control अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_port_bp_control_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t bp_on:4;
		uपूर्णांक64_t enb:4;
#अन्यथा
		uपूर्णांक64_t enb:4;
		uपूर्णांक64_t bp_on:4;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_rsl_पूर्णांक_blocks अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_rsl_पूर्णांक_blocks_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t rपूर्णांक_31:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t reserved_28_29:2;
		uपूर्णांक64_t rपूर्णांक_27:1;
		uपूर्णांक64_t rपूर्णांक_26:1;
		uपूर्णांक64_t rपूर्णांक_25:1;
		uपूर्णांक64_t rपूर्णांक_24:1;
		uपूर्णांक64_t asx1:1;
		uपूर्णांक64_t asx0:1;
		uपूर्णांक64_t rपूर्णांक_21:1;
		uपूर्णांक64_t pip:1;
		uपूर्णांक64_t spx1:1;
		uपूर्णांक64_t spx0:1;
		uपूर्णांक64_t lmc:1;
		uपूर्णांक64_t l2c:1;
		uपूर्णांक64_t rपूर्णांक_15:1;
		uपूर्णांक64_t reserved_13_14:2;
		uपूर्णांक64_t घात:1;
		uपूर्णांक64_t tim:1;
		uपूर्णांक64_t pko:1;
		uपूर्णांक64_t ipd:1;
		uपूर्णांक64_t rपूर्णांक_8:1;
		uपूर्णांक64_t zip:1;
		uपूर्णांक64_t dfa:1;
		uपूर्णांक64_t fpa:1;
		uपूर्णांक64_t key:1;
		uपूर्णांक64_t npi:1;
		uपूर्णांक64_t gmx1:1;
		uपूर्णांक64_t gmx0:1;
		uपूर्णांक64_t mio:1;
#अन्यथा
		uपूर्णांक64_t mio:1;
		uपूर्णांक64_t gmx0:1;
		uपूर्णांक64_t gmx1:1;
		uपूर्णांक64_t npi:1;
		uपूर्णांक64_t key:1;
		uपूर्णांक64_t fpa:1;
		uपूर्णांक64_t dfa:1;
		uपूर्णांक64_t zip:1;
		uपूर्णांक64_t rपूर्णांक_8:1;
		uपूर्णांक64_t ipd:1;
		uपूर्णांक64_t pko:1;
		uपूर्णांक64_t tim:1;
		uपूर्णांक64_t घात:1;
		uपूर्णांक64_t reserved_13_14:2;
		uपूर्णांक64_t rपूर्णांक_15:1;
		uपूर्णांक64_t l2c:1;
		uपूर्णांक64_t lmc:1;
		uपूर्णांक64_t spx0:1;
		uपूर्णांक64_t spx1:1;
		uपूर्णांक64_t pip:1;
		uपूर्णांक64_t rपूर्णांक_21:1;
		uपूर्णांक64_t asx0:1;
		uपूर्णांक64_t asx1:1;
		uपूर्णांक64_t rपूर्णांक_24:1;
		uपूर्णांक64_t rपूर्णांक_25:1;
		uपूर्णांक64_t rपूर्णांक_26:1;
		uपूर्णांक64_t rपूर्णांक_27:1;
		uपूर्णांक64_t reserved_28_29:2;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t rपूर्णांक_31:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_npi_rsl_पूर्णांक_blocks_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t rपूर्णांक_31:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t rपूर्णांक_29:1;
		uपूर्णांक64_t rपूर्णांक_28:1;
		uपूर्णांक64_t rपूर्णांक_27:1;
		uपूर्णांक64_t rपूर्णांक_26:1;
		uपूर्णांक64_t rपूर्णांक_25:1;
		uपूर्णांक64_t rपूर्णांक_24:1;
		uपूर्णांक64_t asx1:1;
		uपूर्णांक64_t asx0:1;
		uपूर्णांक64_t rपूर्णांक_21:1;
		uपूर्णांक64_t pip:1;
		uपूर्णांक64_t spx1:1;
		uपूर्णांक64_t spx0:1;
		uपूर्णांक64_t lmc:1;
		uपूर्णांक64_t l2c:1;
		uपूर्णांक64_t rपूर्णांक_15:1;
		uपूर्णांक64_t rपूर्णांक_14:1;
		uपूर्णांक64_t usb:1;
		uपूर्णांक64_t घात:1;
		uपूर्णांक64_t tim:1;
		uपूर्णांक64_t pko:1;
		uपूर्णांक64_t ipd:1;
		uपूर्णांक64_t rपूर्णांक_8:1;
		uपूर्णांक64_t zip:1;
		uपूर्णांक64_t dfa:1;
		uपूर्णांक64_t fpa:1;
		uपूर्णांक64_t key:1;
		uपूर्णांक64_t npi:1;
		uपूर्णांक64_t gmx1:1;
		uपूर्णांक64_t gmx0:1;
		uपूर्णांक64_t mio:1;
#अन्यथा
		uपूर्णांक64_t mio:1;
		uपूर्णांक64_t gmx0:1;
		uपूर्णांक64_t gmx1:1;
		uपूर्णांक64_t npi:1;
		uपूर्णांक64_t key:1;
		uपूर्णांक64_t fpa:1;
		uपूर्णांक64_t dfa:1;
		uपूर्णांक64_t zip:1;
		uपूर्णांक64_t rपूर्णांक_8:1;
		uपूर्णांक64_t ipd:1;
		uपूर्णांक64_t pko:1;
		uपूर्णांक64_t tim:1;
		uपूर्णांक64_t घात:1;
		uपूर्णांक64_t usb:1;
		uपूर्णांक64_t rपूर्णांक_14:1;
		uपूर्णांक64_t rपूर्णांक_15:1;
		uपूर्णांक64_t l2c:1;
		uपूर्णांक64_t lmc:1;
		uपूर्णांक64_t spx0:1;
		uपूर्णांक64_t spx1:1;
		uपूर्णांक64_t pip:1;
		uपूर्णांक64_t rपूर्णांक_21:1;
		uपूर्णांक64_t asx0:1;
		uपूर्णांक64_t asx1:1;
		uपूर्णांक64_t rपूर्णांक_24:1;
		uपूर्णांक64_t rपूर्णांक_25:1;
		uपूर्णांक64_t rपूर्णांक_26:1;
		uपूर्णांक64_t rपूर्णांक_27:1;
		uपूर्णांक64_t rपूर्णांक_28:1;
		uपूर्णांक64_t rपूर्णांक_29:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t rपूर्णांक_31:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_npi_rsl_पूर्णांक_blocks_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t rपूर्णांक_31:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t rपूर्णांक_29:1;
		uपूर्णांक64_t rपूर्णांक_28:1;
		uपूर्णांक64_t rपूर्णांक_27:1;
		uपूर्णांक64_t rपूर्णांक_26:1;
		uपूर्णांक64_t rपूर्णांक_25:1;
		uपूर्णांक64_t rपूर्णांक_24:1;
		uपूर्णांक64_t asx1:1;
		uपूर्णांक64_t asx0:1;
		uपूर्णांक64_t rपूर्णांक_21:1;
		uपूर्णांक64_t pip:1;
		uपूर्णांक64_t spx1:1;
		uपूर्णांक64_t spx0:1;
		uपूर्णांक64_t lmc:1;
		uपूर्णांक64_t l2c:1;
		uपूर्णांक64_t rपूर्णांक_15:1;
		uपूर्णांक64_t rपूर्णांक_14:1;
		uपूर्णांक64_t rपूर्णांक_13:1;
		uपूर्णांक64_t घात:1;
		uपूर्णांक64_t tim:1;
		uपूर्णांक64_t pko:1;
		uपूर्णांक64_t ipd:1;
		uपूर्णांक64_t rपूर्णांक_8:1;
		uपूर्णांक64_t zip:1;
		uपूर्णांक64_t dfa:1;
		uपूर्णांक64_t fpa:1;
		uपूर्णांक64_t key:1;
		uपूर्णांक64_t npi:1;
		uपूर्णांक64_t gmx1:1;
		uपूर्णांक64_t gmx0:1;
		uपूर्णांक64_t mio:1;
#अन्यथा
		uपूर्णांक64_t mio:1;
		uपूर्णांक64_t gmx0:1;
		uपूर्णांक64_t gmx1:1;
		uपूर्णांक64_t npi:1;
		uपूर्णांक64_t key:1;
		uपूर्णांक64_t fpa:1;
		uपूर्णांक64_t dfa:1;
		uपूर्णांक64_t zip:1;
		uपूर्णांक64_t rपूर्णांक_8:1;
		uपूर्णांक64_t ipd:1;
		uपूर्णांक64_t pko:1;
		uपूर्णांक64_t tim:1;
		uपूर्णांक64_t घात:1;
		uपूर्णांक64_t rपूर्णांक_13:1;
		uपूर्णांक64_t rपूर्णांक_14:1;
		uपूर्णांक64_t rपूर्णांक_15:1;
		uपूर्णांक64_t l2c:1;
		uपूर्णांक64_t lmc:1;
		uपूर्णांक64_t spx0:1;
		uपूर्णांक64_t spx1:1;
		uपूर्णांक64_t pip:1;
		uपूर्णांक64_t rपूर्णांक_21:1;
		uपूर्णांक64_t asx0:1;
		uपूर्णांक64_t asx1:1;
		uपूर्णांक64_t rपूर्णांक_24:1;
		uपूर्णांक64_t rपूर्णांक_25:1;
		uपूर्णांक64_t rपूर्णांक_26:1;
		uपूर्णांक64_t rपूर्णांक_27:1;
		uपूर्णांक64_t rपूर्णांक_28:1;
		uपूर्णांक64_t rपूर्णांक_29:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t rपूर्णांक_31:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_npi_rsl_पूर्णांक_blocks_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_31_63:33;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t lmc1:1;
		uपूर्णांक64_t agl:1;
		uपूर्णांक64_t reserved_24_27:4;
		uपूर्णांक64_t asx1:1;
		uपूर्णांक64_t asx0:1;
		uपूर्णांक64_t reserved_21_21:1;
		uपूर्णांक64_t pip:1;
		uपूर्णांक64_t spx1:1;
		uपूर्णांक64_t spx0:1;
		uपूर्णांक64_t lmc:1;
		uपूर्णांक64_t l2c:1;
		uपूर्णांक64_t reserved_15_15:1;
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
		uपूर्णांक64_t npi:1;
		uपूर्णांक64_t gmx1:1;
		uपूर्णांक64_t gmx0:1;
		uपूर्णांक64_t mio:1;
#अन्यथा
		uपूर्णांक64_t mio:1;
		uपूर्णांक64_t gmx0:1;
		uपूर्णांक64_t gmx1:1;
		uपूर्णांक64_t npi:1;
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
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t l2c:1;
		uपूर्णांक64_t lmc:1;
		uपूर्णांक64_t spx0:1;
		uपूर्णांक64_t spx1:1;
		uपूर्णांक64_t pip:1;
		uपूर्णांक64_t reserved_21_21:1;
		uपूर्णांक64_t asx0:1;
		uपूर्णांक64_t asx1:1;
		uपूर्णांक64_t reserved_24_27:4;
		uपूर्णांक64_t agl:1;
		uपूर्णांक64_t lmc1:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t reserved_31_63:33;
#पूर्ण_अगर
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_npi_size_inputx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_size_inputx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t size:32;
#अन्यथा
		uपूर्णांक64_t size:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_npi_win_पढ़ो_to अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_npi_win_पढ़ो_to_s अणु
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
