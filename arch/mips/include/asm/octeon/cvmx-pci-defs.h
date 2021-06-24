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

#अगर_अघोषित __CVMX_PCI_DEFS_H__
#घोषणा __CVMX_PCI_DEFS_H__

#घोषणा CVMX_PCI_BAR1_INDEXX(offset) (0x0000000000000100ull + ((offset) & 31) * 4)
#घोषणा CVMX_PCI_BIST_REG (0x00000000000001C0ull)
#घोषणा CVMX_PCI_CFG00 (0x0000000000000000ull)
#घोषणा CVMX_PCI_CFG01 (0x0000000000000004ull)
#घोषणा CVMX_PCI_CFG02 (0x0000000000000008ull)
#घोषणा CVMX_PCI_CFG03 (0x000000000000000Cull)
#घोषणा CVMX_PCI_CFG04 (0x0000000000000010ull)
#घोषणा CVMX_PCI_CFG05 (0x0000000000000014ull)
#घोषणा CVMX_PCI_CFG06 (0x0000000000000018ull)
#घोषणा CVMX_PCI_CFG07 (0x000000000000001Cull)
#घोषणा CVMX_PCI_CFG08 (0x0000000000000020ull)
#घोषणा CVMX_PCI_CFG09 (0x0000000000000024ull)
#घोषणा CVMX_PCI_CFG10 (0x0000000000000028ull)
#घोषणा CVMX_PCI_CFG11 (0x000000000000002Cull)
#घोषणा CVMX_PCI_CFG12 (0x0000000000000030ull)
#घोषणा CVMX_PCI_CFG13 (0x0000000000000034ull)
#घोषणा CVMX_PCI_CFG15 (0x000000000000003Cull)
#घोषणा CVMX_PCI_CFG16 (0x0000000000000040ull)
#घोषणा CVMX_PCI_CFG17 (0x0000000000000044ull)
#घोषणा CVMX_PCI_CFG18 (0x0000000000000048ull)
#घोषणा CVMX_PCI_CFG19 (0x000000000000004Cull)
#घोषणा CVMX_PCI_CFG20 (0x0000000000000050ull)
#घोषणा CVMX_PCI_CFG21 (0x0000000000000054ull)
#घोषणा CVMX_PCI_CFG22 (0x0000000000000058ull)
#घोषणा CVMX_PCI_CFG56 (0x00000000000000E0ull)
#घोषणा CVMX_PCI_CFG57 (0x00000000000000E4ull)
#घोषणा CVMX_PCI_CFG58 (0x00000000000000E8ull)
#घोषणा CVMX_PCI_CFG59 (0x00000000000000ECull)
#घोषणा CVMX_PCI_CFG60 (0x00000000000000F0ull)
#घोषणा CVMX_PCI_CFG61 (0x00000000000000F4ull)
#घोषणा CVMX_PCI_CFG62 (0x00000000000000F8ull)
#घोषणा CVMX_PCI_CFG63 (0x00000000000000FCull)
#घोषणा CVMX_PCI_CNT_REG (0x00000000000001B8ull)
#घोषणा CVMX_PCI_CTL_STATUS_2 (0x000000000000018Cull)
#घोषणा CVMX_PCI_DBELL_X(offset) (0x0000000000000080ull + ((offset) & 3) * 8)
#घोषणा CVMX_PCI_DMA_CNT0 CVMX_PCI_DMA_CNTX(0)
#घोषणा CVMX_PCI_DMA_CNT1 CVMX_PCI_DMA_CNTX(1)
#घोषणा CVMX_PCI_DMA_CNTX(offset) (0x00000000000000A0ull + ((offset) & 1) * 8)
#घोषणा CVMX_PCI_DMA_INT_LEV0 CVMX_PCI_DMA_INT_LEVX(0)
#घोषणा CVMX_PCI_DMA_INT_LEV1 CVMX_PCI_DMA_INT_LEVX(1)
#घोषणा CVMX_PCI_DMA_INT_LEVX(offset) (0x00000000000000A4ull + ((offset) & 1) * 8)
#घोषणा CVMX_PCI_DMA_TIME0 CVMX_PCI_DMA_TIMEX(0)
#घोषणा CVMX_PCI_DMA_TIME1 CVMX_PCI_DMA_TIMEX(1)
#घोषणा CVMX_PCI_DMA_TIMEX(offset) (0x00000000000000B0ull + ((offset) & 1) * 4)
#घोषणा CVMX_PCI_INSTR_COUNT0 CVMX_PCI_INSTR_COUNTX(0)
#घोषणा CVMX_PCI_INSTR_COUNT1 CVMX_PCI_INSTR_COUNTX(1)
#घोषणा CVMX_PCI_INSTR_COUNT2 CVMX_PCI_INSTR_COUNTX(2)
#घोषणा CVMX_PCI_INSTR_COUNT3 CVMX_PCI_INSTR_COUNTX(3)
#घोषणा CVMX_PCI_INSTR_COUNTX(offset) (0x0000000000000084ull + ((offset) & 3) * 8)
#घोषणा CVMX_PCI_INT_ENB (0x0000000000000038ull)
#घोषणा CVMX_PCI_INT_ENB2 (0x00000000000001A0ull)
#घोषणा CVMX_PCI_INT_SUM (0x0000000000000030ull)
#घोषणा CVMX_PCI_INT_SUM2 (0x0000000000000198ull)
#घोषणा CVMX_PCI_MSI_RCV (0x00000000000000F0ull)
#घोषणा CVMX_PCI_PKTS_SENT0 CVMX_PCI_PKTS_SENTX(0)
#घोषणा CVMX_PCI_PKTS_SENT1 CVMX_PCI_PKTS_SENTX(1)
#घोषणा CVMX_PCI_PKTS_SENT2 CVMX_PCI_PKTS_SENTX(2)
#घोषणा CVMX_PCI_PKTS_SENT3 CVMX_PCI_PKTS_SENTX(3)
#घोषणा CVMX_PCI_PKTS_SENTX(offset) (0x0000000000000040ull + ((offset) & 3) * 16)
#घोषणा CVMX_PCI_PKTS_SENT_INT_LEV0 CVMX_PCI_PKTS_SENT_INT_LEVX(0)
#घोषणा CVMX_PCI_PKTS_SENT_INT_LEV1 CVMX_PCI_PKTS_SENT_INT_LEVX(1)
#घोषणा CVMX_PCI_PKTS_SENT_INT_LEV2 CVMX_PCI_PKTS_SENT_INT_LEVX(2)
#घोषणा CVMX_PCI_PKTS_SENT_INT_LEV3 CVMX_PCI_PKTS_SENT_INT_LEVX(3)
#घोषणा CVMX_PCI_PKTS_SENT_INT_LEVX(offset) (0x0000000000000048ull + ((offset) & 3) * 16)
#घोषणा CVMX_PCI_PKTS_SENT_TIME0 CVMX_PCI_PKTS_SENT_TIMEX(0)
#घोषणा CVMX_PCI_PKTS_SENT_TIME1 CVMX_PCI_PKTS_SENT_TIMEX(1)
#घोषणा CVMX_PCI_PKTS_SENT_TIME2 CVMX_PCI_PKTS_SENT_TIMEX(2)
#घोषणा CVMX_PCI_PKTS_SENT_TIME3 CVMX_PCI_PKTS_SENT_TIMEX(3)
#घोषणा CVMX_PCI_PKTS_SENT_TIMEX(offset) (0x000000000000004Cull + ((offset) & 3) * 16)
#घोषणा CVMX_PCI_PKT_CREDITS0 CVMX_PCI_PKT_CREDITSX(0)
#घोषणा CVMX_PCI_PKT_CREDITS1 CVMX_PCI_PKT_CREDITSX(1)
#घोषणा CVMX_PCI_PKT_CREDITS2 CVMX_PCI_PKT_CREDITSX(2)
#घोषणा CVMX_PCI_PKT_CREDITS3 CVMX_PCI_PKT_CREDITSX(3)
#घोषणा CVMX_PCI_PKT_CREDITSX(offset) (0x0000000000000044ull + ((offset) & 3) * 16)
#घोषणा CVMX_PCI_READ_CMD_6 (0x0000000000000180ull)
#घोषणा CVMX_PCI_READ_CMD_C (0x0000000000000184ull)
#घोषणा CVMX_PCI_READ_CMD_E (0x0000000000000188ull)
#घोषणा CVMX_PCI_READ_TIMEOUT (CVMX_ADD_IO_SEG(0x00011F00000000B0ull))
#घोषणा CVMX_PCI_SCM_REG (0x00000000000001A8ull)
#घोषणा CVMX_PCI_TSR_REG (0x00000000000001B0ull)
#घोषणा CVMX_PCI_WIN_RD_ADDR (0x0000000000000008ull)
#घोषणा CVMX_PCI_WIN_RD_DATA (0x0000000000000020ull)
#घोषणा CVMX_PCI_WIN_WR_ADDR (0x0000000000000000ull)
#घोषणा CVMX_PCI_WIN_WR_DATA (0x0000000000000010ull)
#घोषणा CVMX_PCI_WIN_WR_MASK (0x0000000000000018ull)

जोड़ cvmx_pci_bar1_indexx अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_bar1_indexx_s अणु
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

जोड़ cvmx_pci_bist_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pci_bist_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t rsp_bs:1;
		uपूर्णांक64_t dma0_bs:1;
		uपूर्णांक64_t cmd0_bs:1;
		uपूर्णांक64_t cmd_bs:1;
		uपूर्णांक64_t csr2p_bs:1;
		uपूर्णांक64_t csrr_bs:1;
		uपूर्णांक64_t rsp2p_bs:1;
		uपूर्णांक64_t csr2n_bs:1;
		uपूर्णांक64_t dat2n_bs:1;
		uपूर्णांक64_t dbg2n_bs:1;
#अन्यथा
		uपूर्णांक64_t dbg2n_bs:1;
		uपूर्णांक64_t dat2n_bs:1;
		uपूर्णांक64_t csr2n_bs:1;
		uपूर्णांक64_t rsp2p_bs:1;
		uपूर्णांक64_t csrr_bs:1;
		uपूर्णांक64_t csr2p_bs:1;
		uपूर्णांक64_t cmd_bs:1;
		uपूर्णांक64_t cmd0_bs:1;
		uपूर्णांक64_t dma0_bs:1;
		uपूर्णांक64_t rsp_bs:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg00 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg00_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t devid:16;
		uपूर्णांक32_t vendid:16;
#अन्यथा
		uपूर्णांक32_t vendid:16;
		uपूर्णांक32_t devid:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg01 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg01_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t dpe:1;
		uपूर्णांक32_t sse:1;
		uपूर्णांक32_t rma:1;
		uपूर्णांक32_t rta:1;
		uपूर्णांक32_t sta:1;
		uपूर्णांक32_t devt:2;
		uपूर्णांक32_t mdpe:1;
		uपूर्णांक32_t fbb:1;
		uपूर्णांक32_t reserved_22_22:1;
		uपूर्णांक32_t m66:1;
		uपूर्णांक32_t cle:1;
		uपूर्णांक32_t i_stat:1;
		uपूर्णांक32_t reserved_11_18:8;
		uपूर्णांक32_t i_dis:1;
		uपूर्णांक32_t fbbe:1;
		uपूर्णांक32_t see:1;
		uपूर्णांक32_t ads:1;
		uपूर्णांक32_t pee:1;
		uपूर्णांक32_t vps:1;
		uपूर्णांक32_t mwice:1;
		uपूर्णांक32_t scse:1;
		uपूर्णांक32_t me:1;
		uपूर्णांक32_t msae:1;
		uपूर्णांक32_t isae:1;
#अन्यथा
		uपूर्णांक32_t isae:1;
		uपूर्णांक32_t msae:1;
		uपूर्णांक32_t me:1;
		uपूर्णांक32_t scse:1;
		uपूर्णांक32_t mwice:1;
		uपूर्णांक32_t vps:1;
		uपूर्णांक32_t pee:1;
		uपूर्णांक32_t ads:1;
		uपूर्णांक32_t see:1;
		uपूर्णांक32_t fbbe:1;
		uपूर्णांक32_t i_dis:1;
		uपूर्णांक32_t reserved_11_18:8;
		uपूर्णांक32_t i_stat:1;
		uपूर्णांक32_t cle:1;
		uपूर्णांक32_t m66:1;
		uपूर्णांक32_t reserved_22_22:1;
		uपूर्णांक32_t fbb:1;
		uपूर्णांक32_t mdpe:1;
		uपूर्णांक32_t devt:2;
		uपूर्णांक32_t sta:1;
		uपूर्णांक32_t rta:1;
		uपूर्णांक32_t rma:1;
		uपूर्णांक32_t sse:1;
		uपूर्णांक32_t dpe:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg02 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg02_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t cc:24;
		uपूर्णांक32_t rid:8;
#अन्यथा
		uपूर्णांक32_t rid:8;
		uपूर्णांक32_t cc:24;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg03 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg03_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t bcap:1;
		uपूर्णांक32_t brb:1;
		uपूर्णांक32_t reserved_28_29:2;
		uपूर्णांक32_t bcod:4;
		uपूर्णांक32_t ht:8;
		uपूर्णांक32_t lt:8;
		uपूर्णांक32_t cls:8;
#अन्यथा
		uपूर्णांक32_t cls:8;
		uपूर्णांक32_t lt:8;
		uपूर्णांक32_t ht:8;
		uपूर्णांक32_t bcod:4;
		uपूर्णांक32_t reserved_28_29:2;
		uपूर्णांक32_t brb:1;
		uपूर्णांक32_t bcap:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg04 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg04_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t lbase:20;
		uपूर्णांक32_t lbasez:8;
		uपूर्णांक32_t pf:1;
		uपूर्णांक32_t typ:2;
		uपूर्णांक32_t mspc:1;
#अन्यथा
		uपूर्णांक32_t mspc:1;
		uपूर्णांक32_t typ:2;
		uपूर्णांक32_t pf:1;
		uपूर्णांक32_t lbasez:8;
		uपूर्णांक32_t lbase:20;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg05 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg05_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t hbase:32;
#अन्यथा
		uपूर्णांक32_t hbase:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg06 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg06_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t lbase:5;
		uपूर्णांक32_t lbasez:23;
		uपूर्णांक32_t pf:1;
		uपूर्णांक32_t typ:2;
		uपूर्णांक32_t mspc:1;
#अन्यथा
		uपूर्णांक32_t mspc:1;
		uपूर्णांक32_t typ:2;
		uपूर्णांक32_t pf:1;
		uपूर्णांक32_t lbasez:23;
		uपूर्णांक32_t lbase:5;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg07 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg07_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t hbase:32;
#अन्यथा
		uपूर्णांक32_t hbase:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg08 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg08_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t lbasez:28;
		uपूर्णांक32_t pf:1;
		uपूर्णांक32_t typ:2;
		uपूर्णांक32_t mspc:1;
#अन्यथा
		uपूर्णांक32_t mspc:1;
		uपूर्णांक32_t typ:2;
		uपूर्णांक32_t pf:1;
		uपूर्णांक32_t lbasez:28;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg09 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg09_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t hbase:25;
		uपूर्णांक32_t hbasez:7;
#अन्यथा
		uपूर्णांक32_t hbasez:7;
		uपूर्णांक32_t hbase:25;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg10 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg10_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t cisp:32;
#अन्यथा
		uपूर्णांक32_t cisp:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg11 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg11_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t ssid:16;
		uपूर्णांक32_t ssvid:16;
#अन्यथा
		uपूर्णांक32_t ssvid:16;
		uपूर्णांक32_t ssid:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg12 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg12_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t erbar:16;
		uपूर्णांक32_t erbarz:5;
		uपूर्णांक32_t reserved_1_10:10;
		uपूर्णांक32_t erbar_en:1;
#अन्यथा
		uपूर्णांक32_t erbar_en:1;
		uपूर्णांक32_t reserved_1_10:10;
		uपूर्णांक32_t erbarz:5;
		uपूर्णांक32_t erbar:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg13 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg13_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t reserved_8_31:24;
		uपूर्णांक32_t cp:8;
#अन्यथा
		uपूर्णांक32_t cp:8;
		uपूर्णांक32_t reserved_8_31:24;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg15 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg15_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t ml:8;
		uपूर्णांक32_t mg:8;
		uपूर्णांक32_t पूर्णांकa:8;
		uपूर्णांक32_t il:8;
#अन्यथा
		uपूर्णांक32_t il:8;
		uपूर्णांक32_t पूर्णांकa:8;
		uपूर्णांक32_t mg:8;
		uपूर्णांक32_t ml:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg16 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg16_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t trdnpr:1;
		uपूर्णांक32_t trdard:1;
		uपूर्णांक32_t rdsati:1;
		uपूर्णांक32_t trdrs:1;
		uपूर्णांक32_t trtae:1;
		uपूर्णांक32_t twsei:1;
		uपूर्णांक32_t twsen:1;
		uपूर्णांक32_t twtae:1;
		uपूर्णांक32_t पंचांगae:1;
		uपूर्णांक32_t tslte:3;
		uपूर्णांक32_t tilt:4;
		uपूर्णांक32_t pbe:12;
		uपूर्णांक32_t dppmr:1;
		uपूर्णांक32_t reserved_2_2:1;
		uपूर्णांक32_t tswc:1;
		uपूर्णांक32_t mltd:1;
#अन्यथा
		uपूर्णांक32_t mltd:1;
		uपूर्णांक32_t tswc:1;
		uपूर्णांक32_t reserved_2_2:1;
		uपूर्णांक32_t dppmr:1;
		uपूर्णांक32_t pbe:12;
		uपूर्णांक32_t tilt:4;
		uपूर्णांक32_t tslte:3;
		uपूर्णांक32_t पंचांगae:1;
		uपूर्णांक32_t twtae:1;
		uपूर्णांक32_t twsen:1;
		uपूर्णांक32_t twsei:1;
		uपूर्णांक32_t trtae:1;
		uपूर्णांक32_t trdrs:1;
		uपूर्णांक32_t rdsati:1;
		uपूर्णांक32_t trdard:1;
		uपूर्णांक32_t trdnpr:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg17 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg17_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t tscme:32;
#अन्यथा
		uपूर्णांक32_t tscme:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg18 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg18_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t tdsrps:32;
#अन्यथा
		uपूर्णांक32_t tdsrps:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg19 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg19_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t mrbcm:1;
		uपूर्णांक32_t mrbci:1;
		uपूर्णांक32_t mdwe:1;
		uपूर्णांक32_t mdre:1;
		uपूर्णांक32_t mdrimc:1;
		uपूर्णांक32_t mdrrmc:3;
		uपूर्णांक32_t पंचांगes:8;
		uपूर्णांक32_t teci:1;
		uपूर्णांक32_t पंचांगei:1;
		uपूर्णांक32_t पंचांगse:1;
		uपूर्णांक32_t पंचांगdpes:1;
		uपूर्णांक32_t पंचांगapes:1;
		uपूर्णांक32_t reserved_9_10:2;
		uपूर्णांक32_t tibcd:1;
		uपूर्णांक32_t tibde:1;
		uपूर्णांक32_t reserved_6_6:1;
		uपूर्णांक32_t tiकरोmc:1;
		uपूर्णांक32_t tकरोmc:5;
#अन्यथा
		uपूर्णांक32_t tकरोmc:5;
		uपूर्णांक32_t tiकरोmc:1;
		uपूर्णांक32_t reserved_6_6:1;
		uपूर्णांक32_t tibde:1;
		uपूर्णांक32_t tibcd:1;
		uपूर्णांक32_t reserved_9_10:2;
		uपूर्णांक32_t पंचांगapes:1;
		uपूर्णांक32_t पंचांगdpes:1;
		uपूर्णांक32_t पंचांगse:1;
		uपूर्णांक32_t पंचांगei:1;
		uपूर्णांक32_t teci:1;
		uपूर्णांक32_t पंचांगes:8;
		uपूर्णांक32_t mdrrmc:3;
		uपूर्णांक32_t mdrimc:1;
		uपूर्णांक32_t mdre:1;
		uपूर्णांक32_t mdwe:1;
		uपूर्णांक32_t mrbci:1;
		uपूर्णांक32_t mrbcm:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg20 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg20_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t mdsp:32;
#अन्यथा
		uपूर्णांक32_t mdsp:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg21 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg21_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t scmre:32;
#अन्यथा
		uपूर्णांक32_t scmre:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg22 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg22_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t mac:7;
		uपूर्णांक32_t reserved_19_24:6;
		uपूर्णांक32_t flush:1;
		uपूर्णांक32_t mra:1;
		uपूर्णांक32_t mtta:1;
		uपूर्णांक32_t mrv:8;
		uपूर्णांक32_t mttv:8;
#अन्यथा
		uपूर्णांक32_t mttv:8;
		uपूर्णांक32_t mrv:8;
		uपूर्णांक32_t mtta:1;
		uपूर्णांक32_t mra:1;
		uपूर्णांक32_t flush:1;
		uपूर्णांक32_t reserved_19_24:6;
		uपूर्णांक32_t mac:7;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg56 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg56_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t reserved_23_31:9;
		uपूर्णांक32_t most:3;
		uपूर्णांक32_t mmbc:2;
		uपूर्णांक32_t roe:1;
		uपूर्णांक32_t dpere:1;
		uपूर्णांक32_t ncp:8;
		uपूर्णांक32_t pxcid:8;
#अन्यथा
		uपूर्णांक32_t pxcid:8;
		uपूर्णांक32_t ncp:8;
		uपूर्णांक32_t dpere:1;
		uपूर्णांक32_t roe:1;
		uपूर्णांक32_t mmbc:2;
		uपूर्णांक32_t most:3;
		uपूर्णांक32_t reserved_23_31:9;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg57 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg57_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t reserved_30_31:2;
		uपूर्णांक32_t scemr:1;
		uपूर्णांक32_t mcrsd:3;
		uपूर्णांक32_t mostd:3;
		uपूर्णांक32_t mmrbcd:2;
		uपूर्णांक32_t dc:1;
		uपूर्णांक32_t usc:1;
		uपूर्णांक32_t scd:1;
		uपूर्णांक32_t m133:1;
		uपूर्णांक32_t w64:1;
		uपूर्णांक32_t bn:8;
		uपूर्णांक32_t dn:5;
		uपूर्णांक32_t fn:3;
#अन्यथा
		uपूर्णांक32_t fn:3;
		uपूर्णांक32_t dn:5;
		uपूर्णांक32_t bn:8;
		uपूर्णांक32_t w64:1;
		uपूर्णांक32_t m133:1;
		uपूर्णांक32_t scd:1;
		uपूर्णांक32_t usc:1;
		uपूर्णांक32_t dc:1;
		uपूर्णांक32_t mmrbcd:2;
		uपूर्णांक32_t mostd:3;
		uपूर्णांक32_t mcrsd:3;
		uपूर्णांक32_t scemr:1;
		uपूर्णांक32_t reserved_30_31:2;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg58 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg58_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t pmes:5;
		uपूर्णांक32_t d2s:1;
		uपूर्णांक32_t d1s:1;
		uपूर्णांक32_t auxc:3;
		uपूर्णांक32_t dsi:1;
		uपूर्णांक32_t reserved_20_20:1;
		uपूर्णांक32_t pmec:1;
		uपूर्णांक32_t pcimiv:3;
		uपूर्णांक32_t ncp:8;
		uपूर्णांक32_t pmcid:8;
#अन्यथा
		uपूर्णांक32_t pmcid:8;
		uपूर्णांक32_t ncp:8;
		uपूर्णांक32_t pcimiv:3;
		uपूर्णांक32_t pmec:1;
		uपूर्णांक32_t reserved_20_20:1;
		uपूर्णांक32_t dsi:1;
		uपूर्णांक32_t auxc:3;
		uपूर्णांक32_t d1s:1;
		uपूर्णांक32_t d2s:1;
		uपूर्णांक32_t pmes:5;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg59 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg59_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t pmdia:8;
		uपूर्णांक32_t bpccen:1;
		uपूर्णांक32_t bd3h:1;
		uपूर्णांक32_t reserved_16_21:6;
		uपूर्णांक32_t pmess:1;
		uपूर्णांक32_t pmedsia:2;
		uपूर्णांक32_t pmds:4;
		uपूर्णांक32_t pmeens:1;
		uपूर्णांक32_t reserved_2_7:6;
		uपूर्णांक32_t ps:2;
#अन्यथा
		uपूर्णांक32_t ps:2;
		uपूर्णांक32_t reserved_2_7:6;
		uपूर्णांक32_t pmeens:1;
		uपूर्णांक32_t pmds:4;
		uपूर्णांक32_t pmedsia:2;
		uपूर्णांक32_t pmess:1;
		uपूर्णांक32_t reserved_16_21:6;
		uपूर्णांक32_t bd3h:1;
		uपूर्णांक32_t bpccen:1;
		uपूर्णांक32_t pmdia:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg60 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg60_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t reserved_24_31:8;
		uपूर्णांक32_t m64:1;
		uपूर्णांक32_t mme:3;
		uपूर्णांक32_t mmc:3;
		uपूर्णांक32_t msien:1;
		uपूर्णांक32_t ncp:8;
		uपूर्णांक32_t msicid:8;
#अन्यथा
		uपूर्णांक32_t msicid:8;
		uपूर्णांक32_t ncp:8;
		uपूर्णांक32_t msien:1;
		uपूर्णांक32_t mmc:3;
		uपूर्णांक32_t mme:3;
		uपूर्णांक32_t m64:1;
		uपूर्णांक32_t reserved_24_31:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg61 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg61_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t msi31t2:30;
		uपूर्णांक32_t reserved_0_1:2;
#अन्यथा
		uपूर्णांक32_t reserved_0_1:2;
		uपूर्णांक32_t msi31t2:30;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg62 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg62_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t msi:32;
#अन्यथा
		uपूर्णांक32_t msi:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cfg63 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_cfg63_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t reserved_16_31:16;
		uपूर्णांक32_t msimd:16;
#अन्यथा
		uपूर्णांक32_t msimd:16;
		uपूर्णांक32_t reserved_16_31:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_cnt_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pci_cnt_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_38_63:26;
		uपूर्णांक64_t hm_pcix:1;
		uपूर्णांक64_t hm_speed:2;
		uपूर्णांक64_t ap_pcix:1;
		uपूर्णांक64_t ap_speed:2;
		uपूर्णांक64_t pcicnt:32;
#अन्यथा
		uपूर्णांक64_t pcicnt:32;
		uपूर्णांक64_t ap_speed:2;
		uपूर्णांक64_t ap_pcix:1;
		uपूर्णांक64_t hm_speed:2;
		uपूर्णांक64_t hm_pcix:1;
		uपूर्णांक64_t reserved_38_63:26;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_ctl_status_2 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_ctl_status_2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t reserved_29_31:3;
		uपूर्णांक32_t bb1_hole:3;
		uपूर्णांक32_t bb1_siz:1;
		uपूर्णांक32_t bb_ca:1;
		uपूर्णांक32_t bb_es:2;
		uपूर्णांक32_t bb1:1;
		uपूर्णांक32_t bb0:1;
		uपूर्णांक32_t erst_n:1;
		uपूर्णांक32_t bar2pres:1;
		uपूर्णांक32_t scmtyp:1;
		uपूर्णांक32_t scm:1;
		uपूर्णांक32_t en_wfilt:1;
		uपूर्णांक32_t reserved_14_14:1;
		uपूर्णांक32_t ap_pcix:1;
		uपूर्णांक32_t ap_64ad:1;
		uपूर्णांक32_t b12_bist:1;
		uपूर्णांक32_t pmo_amod:1;
		uपूर्णांक32_t pmo_fpc:3;
		uपूर्णांक32_t tsr_hwm:3;
		uपूर्णांक32_t bar2_enb:1;
		uपूर्णांक32_t bar2_esx:2;
		uपूर्णांक32_t bar2_cax:1;
#अन्यथा
		uपूर्णांक32_t bar2_cax:1;
		uपूर्णांक32_t bar2_esx:2;
		uपूर्णांक32_t bar2_enb:1;
		uपूर्णांक32_t tsr_hwm:3;
		uपूर्णांक32_t pmo_fpc:3;
		uपूर्णांक32_t pmo_amod:1;
		uपूर्णांक32_t b12_bist:1;
		uपूर्णांक32_t ap_64ad:1;
		uपूर्णांक32_t ap_pcix:1;
		uपूर्णांक32_t reserved_14_14:1;
		uपूर्णांक32_t en_wfilt:1;
		uपूर्णांक32_t scm:1;
		uपूर्णांक32_t scmtyp:1;
		uपूर्णांक32_t bar2pres:1;
		uपूर्णांक32_t erst_n:1;
		uपूर्णांक32_t bb0:1;
		uपूर्णांक32_t bb1:1;
		uपूर्णांक32_t bb_es:2;
		uपूर्णांक32_t bb_ca:1;
		uपूर्णांक32_t bb1_siz:1;
		uपूर्णांक32_t bb1_hole:3;
		uपूर्णांक32_t reserved_29_31:3;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pci_ctl_status_2_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t reserved_20_31:12;
		uपूर्णांक32_t erst_n:1;
		uपूर्णांक32_t bar2pres:1;
		uपूर्णांक32_t scmtyp:1;
		uपूर्णांक32_t scm:1;
		uपूर्णांक32_t en_wfilt:1;
		uपूर्णांक32_t reserved_14_14:1;
		uपूर्णांक32_t ap_pcix:1;
		uपूर्णांक32_t ap_64ad:1;
		uपूर्णांक32_t b12_bist:1;
		uपूर्णांक32_t pmo_amod:1;
		uपूर्णांक32_t pmo_fpc:3;
		uपूर्णांक32_t tsr_hwm:3;
		uपूर्णांक32_t bar2_enb:1;
		uपूर्णांक32_t bar2_esx:2;
		uपूर्णांक32_t bar2_cax:1;
#अन्यथा
		uपूर्णांक32_t bar2_cax:1;
		uपूर्णांक32_t bar2_esx:2;
		uपूर्णांक32_t bar2_enb:1;
		uपूर्णांक32_t tsr_hwm:3;
		uपूर्णांक32_t pmo_fpc:3;
		uपूर्णांक32_t pmo_amod:1;
		uपूर्णांक32_t b12_bist:1;
		uपूर्णांक32_t ap_64ad:1;
		uपूर्णांक32_t ap_pcix:1;
		uपूर्णांक32_t reserved_14_14:1;
		uपूर्णांक32_t en_wfilt:1;
		uपूर्णांक32_t scm:1;
		uपूर्णांक32_t scmtyp:1;
		uपूर्णांक32_t bar2pres:1;
		uपूर्णांक32_t erst_n:1;
		uपूर्णांक32_t reserved_20_31:12;
#पूर्ण_अगर
	पूर्ण cn31xx;
पूर्ण;

जोड़ cvmx_pci_dbellx अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_dbellx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t reserved_16_31:16;
		uपूर्णांक32_t inc_val:16;
#अन्यथा
		uपूर्णांक32_t inc_val:16;
		uपूर्णांक32_t reserved_16_31:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_dma_cntx अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_dma_cntx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t dma_cnt:32;
#अन्यथा
		uपूर्णांक32_t dma_cnt:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_dma_पूर्णांक_levx अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_dma_पूर्णांक_levx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t pkt_cnt:32;
#अन्यथा
		uपूर्णांक32_t pkt_cnt:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_dma_समयx अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_dma_समयx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t dma_समय:32;
#अन्यथा
		uपूर्णांक32_t dma_समय:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_instr_countx अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_instr_countx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t icnt:32;
#अन्यथा
		uपूर्णांक32_t icnt:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_पूर्णांक_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pci_पूर्णांक_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t idसमय1:1;
		uपूर्णांक64_t idसमय0:1;
		uपूर्णांक64_t idcnt1:1;
		uपूर्णांक64_t idcnt0:1;
		uपूर्णांक64_t ipसमय3:1;
		uपूर्णांक64_t ipसमय2:1;
		uपूर्णांक64_t ipसमय1:1;
		uपूर्णांक64_t ipसमय0:1;
		uपूर्णांक64_t ipcnt3:1;
		uपूर्णांक64_t ipcnt2:1;
		uपूर्णांक64_t ipcnt1:1;
		uपूर्णांक64_t ipcnt0:1;
		uपूर्णांक64_t irsl_पूर्णांक:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t idperr:1;
		uपूर्णांक64_t iaperr:1;
		uपूर्णांक64_t iserr:1;
		uपूर्णांक64_t itsr_abt:1;
		uपूर्णांक64_t imsc_msg:1;
		uपूर्णांक64_t imsi_mabt:1;
		uपूर्णांक64_t imsi_tabt:1;
		uपूर्णांक64_t imsi_per:1;
		uपूर्णांक64_t imr_tto:1;
		uपूर्णांक64_t imr_abt:1;
		uपूर्णांक64_t itr_abt:1;
		uपूर्णांक64_t imr_wtto:1;
		uपूर्णांक64_t imr_wabt:1;
		uपूर्णांक64_t itr_wabt:1;
#अन्यथा
		uपूर्णांक64_t itr_wabt:1;
		uपूर्णांक64_t imr_wabt:1;
		uपूर्णांक64_t imr_wtto:1;
		uपूर्णांक64_t itr_abt:1;
		uपूर्णांक64_t imr_abt:1;
		uपूर्णांक64_t imr_tto:1;
		uपूर्णांक64_t imsi_per:1;
		uपूर्णांक64_t imsi_tabt:1;
		uपूर्णांक64_t imsi_mabt:1;
		uपूर्णांक64_t imsc_msg:1;
		uपूर्णांक64_t itsr_abt:1;
		uपूर्णांक64_t iserr:1;
		uपूर्णांक64_t iaperr:1;
		uपूर्णांक64_t idperr:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t irsl_पूर्णांक:1;
		uपूर्णांक64_t ipcnt0:1;
		uपूर्णांक64_t ipcnt1:1;
		uपूर्णांक64_t ipcnt2:1;
		uपूर्णांक64_t ipcnt3:1;
		uपूर्णांक64_t ipसमय0:1;
		uपूर्णांक64_t ipसमय1:1;
		uपूर्णांक64_t ipसमय2:1;
		uपूर्णांक64_t ipसमय3:1;
		uपूर्णांक64_t idcnt0:1;
		uपूर्णांक64_t idcnt1:1;
		uपूर्णांक64_t idसमय0:1;
		uपूर्णांक64_t idसमय1:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pci_पूर्णांक_enb_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t idसमय1:1;
		uपूर्णांक64_t idसमय0:1;
		uपूर्णांक64_t idcnt1:1;
		uपूर्णांक64_t idcnt0:1;
		uपूर्णांक64_t reserved_22_24:3;
		uपूर्णांक64_t ipसमय0:1;
		uपूर्णांक64_t reserved_18_20:3;
		uपूर्णांक64_t ipcnt0:1;
		uपूर्णांक64_t irsl_पूर्णांक:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t idperr:1;
		uपूर्णांक64_t iaperr:1;
		uपूर्णांक64_t iserr:1;
		uपूर्णांक64_t itsr_abt:1;
		uपूर्णांक64_t imsc_msg:1;
		uपूर्णांक64_t imsi_mabt:1;
		uपूर्णांक64_t imsi_tabt:1;
		uपूर्णांक64_t imsi_per:1;
		uपूर्णांक64_t imr_tto:1;
		uपूर्णांक64_t imr_abt:1;
		uपूर्णांक64_t itr_abt:1;
		uपूर्णांक64_t imr_wtto:1;
		uपूर्णांक64_t imr_wabt:1;
		uपूर्णांक64_t itr_wabt:1;
#अन्यथा
		uपूर्णांक64_t itr_wabt:1;
		uपूर्णांक64_t imr_wabt:1;
		uपूर्णांक64_t imr_wtto:1;
		uपूर्णांक64_t itr_abt:1;
		uपूर्णांक64_t imr_abt:1;
		uपूर्णांक64_t imr_tto:1;
		uपूर्णांक64_t imsi_per:1;
		uपूर्णांक64_t imsi_tabt:1;
		uपूर्णांक64_t imsi_mabt:1;
		uपूर्णांक64_t imsc_msg:1;
		uपूर्णांक64_t itsr_abt:1;
		uपूर्णांक64_t iserr:1;
		uपूर्णांक64_t iaperr:1;
		uपूर्णांक64_t idperr:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t irsl_पूर्णांक:1;
		uपूर्णांक64_t ipcnt0:1;
		uपूर्णांक64_t reserved_18_20:3;
		uपूर्णांक64_t ipसमय0:1;
		uपूर्णांक64_t reserved_22_24:3;
		uपूर्णांक64_t idcnt0:1;
		uपूर्णांक64_t idcnt1:1;
		uपूर्णांक64_t idसमय0:1;
		uपूर्णांक64_t idसमय1:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pci_पूर्णांक_enb_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t idसमय1:1;
		uपूर्णांक64_t idसमय0:1;
		uपूर्णांक64_t idcnt1:1;
		uपूर्णांक64_t idcnt0:1;
		uपूर्णांक64_t reserved_23_24:2;
		uपूर्णांक64_t ipसमय1:1;
		uपूर्णांक64_t ipसमय0:1;
		uपूर्णांक64_t reserved_19_20:2;
		uपूर्णांक64_t ipcnt1:1;
		uपूर्णांक64_t ipcnt0:1;
		uपूर्णांक64_t irsl_पूर्णांक:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t idperr:1;
		uपूर्णांक64_t iaperr:1;
		uपूर्णांक64_t iserr:1;
		uपूर्णांक64_t itsr_abt:1;
		uपूर्णांक64_t imsc_msg:1;
		uपूर्णांक64_t imsi_mabt:1;
		uपूर्णांक64_t imsi_tabt:1;
		uपूर्णांक64_t imsi_per:1;
		uपूर्णांक64_t imr_tto:1;
		uपूर्णांक64_t imr_abt:1;
		uपूर्णांक64_t itr_abt:1;
		uपूर्णांक64_t imr_wtto:1;
		uपूर्णांक64_t imr_wabt:1;
		uपूर्णांक64_t itr_wabt:1;
#अन्यथा
		uपूर्णांक64_t itr_wabt:1;
		uपूर्णांक64_t imr_wabt:1;
		uपूर्णांक64_t imr_wtto:1;
		uपूर्णांक64_t itr_abt:1;
		uपूर्णांक64_t imr_abt:1;
		uपूर्णांक64_t imr_tto:1;
		uपूर्णांक64_t imsi_per:1;
		uपूर्णांक64_t imsi_tabt:1;
		uपूर्णांक64_t imsi_mabt:1;
		uपूर्णांक64_t imsc_msg:1;
		uपूर्णांक64_t itsr_abt:1;
		uपूर्णांक64_t iserr:1;
		uपूर्णांक64_t iaperr:1;
		uपूर्णांक64_t idperr:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t irsl_पूर्णांक:1;
		uपूर्णांक64_t ipcnt0:1;
		uपूर्णांक64_t ipcnt1:1;
		uपूर्णांक64_t reserved_19_20:2;
		uपूर्णांक64_t ipसमय0:1;
		uपूर्णांक64_t ipसमय1:1;
		uपूर्णांक64_t reserved_23_24:2;
		uपूर्णांक64_t idcnt0:1;
		uपूर्णांक64_t idcnt1:1;
		uपूर्णांक64_t idसमय0:1;
		uपूर्णांक64_t idसमय1:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण cn31xx;
पूर्ण;

जोड़ cvmx_pci_पूर्णांक_enb2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pci_पूर्णांक_enb2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t rdसमय1:1;
		uपूर्णांक64_t rdसमय0:1;
		uपूर्णांक64_t rdcnt1:1;
		uपूर्णांक64_t rdcnt0:1;
		uपूर्णांक64_t rpसमय3:1;
		uपूर्णांक64_t rpसमय2:1;
		uपूर्णांक64_t rpसमय1:1;
		uपूर्णांक64_t rpसमय0:1;
		uपूर्णांक64_t rpcnt3:1;
		uपूर्णांक64_t rpcnt2:1;
		uपूर्णांक64_t rpcnt1:1;
		uपूर्णांक64_t rpcnt0:1;
		uपूर्णांक64_t rrsl_पूर्णांक:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t rdperr:1;
		uपूर्णांक64_t raperr:1;
		uपूर्णांक64_t rserr:1;
		uपूर्णांक64_t rtsr_abt:1;
		uपूर्णांक64_t rmsc_msg:1;
		uपूर्णांक64_t rmsi_mabt:1;
		uपूर्णांक64_t rmsi_tabt:1;
		uपूर्णांक64_t rmsi_per:1;
		uपूर्णांक64_t rmr_tto:1;
		uपूर्णांक64_t rmr_abt:1;
		uपूर्णांक64_t rtr_abt:1;
		uपूर्णांक64_t rmr_wtto:1;
		uपूर्णांक64_t rmr_wabt:1;
		uपूर्णांक64_t rtr_wabt:1;
#अन्यथा
		uपूर्णांक64_t rtr_wabt:1;
		uपूर्णांक64_t rmr_wabt:1;
		uपूर्णांक64_t rmr_wtto:1;
		uपूर्णांक64_t rtr_abt:1;
		uपूर्णांक64_t rmr_abt:1;
		uपूर्णांक64_t rmr_tto:1;
		uपूर्णांक64_t rmsi_per:1;
		uपूर्णांक64_t rmsi_tabt:1;
		uपूर्णांक64_t rmsi_mabt:1;
		uपूर्णांक64_t rmsc_msg:1;
		uपूर्णांक64_t rtsr_abt:1;
		uपूर्णांक64_t rserr:1;
		uपूर्णांक64_t raperr:1;
		uपूर्णांक64_t rdperr:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t rrsl_पूर्णांक:1;
		uपूर्णांक64_t rpcnt0:1;
		uपूर्णांक64_t rpcnt1:1;
		uपूर्णांक64_t rpcnt2:1;
		uपूर्णांक64_t rpcnt3:1;
		uपूर्णांक64_t rpसमय0:1;
		uपूर्णांक64_t rpसमय1:1;
		uपूर्णांक64_t rpसमय2:1;
		uपूर्णांक64_t rpसमय3:1;
		uपूर्णांक64_t rdcnt0:1;
		uपूर्णांक64_t rdcnt1:1;
		uपूर्णांक64_t rdसमय0:1;
		uपूर्णांक64_t rdसमय1:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pci_पूर्णांक_enb2_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t rdसमय1:1;
		uपूर्णांक64_t rdसमय0:1;
		uपूर्णांक64_t rdcnt1:1;
		uपूर्णांक64_t rdcnt0:1;
		uपूर्णांक64_t reserved_22_24:3;
		uपूर्णांक64_t rpसमय0:1;
		uपूर्णांक64_t reserved_18_20:3;
		uपूर्णांक64_t rpcnt0:1;
		uपूर्णांक64_t rrsl_पूर्णांक:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t rdperr:1;
		uपूर्णांक64_t raperr:1;
		uपूर्णांक64_t rserr:1;
		uपूर्णांक64_t rtsr_abt:1;
		uपूर्णांक64_t rmsc_msg:1;
		uपूर्णांक64_t rmsi_mabt:1;
		uपूर्णांक64_t rmsi_tabt:1;
		uपूर्णांक64_t rmsi_per:1;
		uपूर्णांक64_t rmr_tto:1;
		uपूर्णांक64_t rmr_abt:1;
		uपूर्णांक64_t rtr_abt:1;
		uपूर्णांक64_t rmr_wtto:1;
		uपूर्णांक64_t rmr_wabt:1;
		uपूर्णांक64_t rtr_wabt:1;
#अन्यथा
		uपूर्णांक64_t rtr_wabt:1;
		uपूर्णांक64_t rmr_wabt:1;
		uपूर्णांक64_t rmr_wtto:1;
		uपूर्णांक64_t rtr_abt:1;
		uपूर्णांक64_t rmr_abt:1;
		uपूर्णांक64_t rmr_tto:1;
		uपूर्णांक64_t rmsi_per:1;
		uपूर्णांक64_t rmsi_tabt:1;
		uपूर्णांक64_t rmsi_mabt:1;
		uपूर्णांक64_t rmsc_msg:1;
		uपूर्णांक64_t rtsr_abt:1;
		uपूर्णांक64_t rserr:1;
		uपूर्णांक64_t raperr:1;
		uपूर्णांक64_t rdperr:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t rrsl_पूर्णांक:1;
		uपूर्णांक64_t rpcnt0:1;
		uपूर्णांक64_t reserved_18_20:3;
		uपूर्णांक64_t rpसमय0:1;
		uपूर्णांक64_t reserved_22_24:3;
		uपूर्णांक64_t rdcnt0:1;
		uपूर्णांक64_t rdcnt1:1;
		uपूर्णांक64_t rdसमय0:1;
		uपूर्णांक64_t rdसमय1:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pci_पूर्णांक_enb2_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t rdसमय1:1;
		uपूर्णांक64_t rdसमय0:1;
		uपूर्णांक64_t rdcnt1:1;
		uपूर्णांक64_t rdcnt0:1;
		uपूर्णांक64_t reserved_23_24:2;
		uपूर्णांक64_t rpसमय1:1;
		uपूर्णांक64_t rpसमय0:1;
		uपूर्णांक64_t reserved_19_20:2;
		uपूर्णांक64_t rpcnt1:1;
		uपूर्णांक64_t rpcnt0:1;
		uपूर्णांक64_t rrsl_पूर्णांक:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t rdperr:1;
		uपूर्णांक64_t raperr:1;
		uपूर्णांक64_t rserr:1;
		uपूर्णांक64_t rtsr_abt:1;
		uपूर्णांक64_t rmsc_msg:1;
		uपूर्णांक64_t rmsi_mabt:1;
		uपूर्णांक64_t rmsi_tabt:1;
		uपूर्णांक64_t rmsi_per:1;
		uपूर्णांक64_t rmr_tto:1;
		uपूर्णांक64_t rmr_abt:1;
		uपूर्णांक64_t rtr_abt:1;
		uपूर्णांक64_t rmr_wtto:1;
		uपूर्णांक64_t rmr_wabt:1;
		uपूर्णांक64_t rtr_wabt:1;
#अन्यथा
		uपूर्णांक64_t rtr_wabt:1;
		uपूर्णांक64_t rmr_wabt:1;
		uपूर्णांक64_t rmr_wtto:1;
		uपूर्णांक64_t rtr_abt:1;
		uपूर्णांक64_t rmr_abt:1;
		uपूर्णांक64_t rmr_tto:1;
		uपूर्णांक64_t rmsi_per:1;
		uपूर्णांक64_t rmsi_tabt:1;
		uपूर्णांक64_t rmsi_mabt:1;
		uपूर्णांक64_t rmsc_msg:1;
		uपूर्णांक64_t rtsr_abt:1;
		uपूर्णांक64_t rserr:1;
		uपूर्णांक64_t raperr:1;
		uपूर्णांक64_t rdperr:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t rrsl_पूर्णांक:1;
		uपूर्णांक64_t rpcnt0:1;
		uपूर्णांक64_t rpcnt1:1;
		uपूर्णांक64_t reserved_19_20:2;
		uपूर्णांक64_t rpसमय0:1;
		uपूर्णांक64_t rpसमय1:1;
		uपूर्णांक64_t reserved_23_24:2;
		uपूर्णांक64_t rdcnt0:1;
		uपूर्णांक64_t rdcnt1:1;
		uपूर्णांक64_t rdसमय0:1;
		uपूर्णांक64_t rdसमय1:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण cn31xx;
पूर्ण;

जोड़ cvmx_pci_पूर्णांक_sum अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pci_पूर्णांक_sum_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t pसमय3:1;
		uपूर्णांक64_t pसमय2:1;
		uपूर्णांक64_t pसमय1:1;
		uपूर्णांक64_t pसमय0:1;
		uपूर्णांक64_t pcnt3:1;
		uपूर्णांक64_t pcnt2:1;
		uपूर्णांक64_t pcnt1:1;
		uपूर्णांक64_t pcnt0:1;
		uपूर्णांक64_t rsl_पूर्णांक:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t dperr:1;
		uपूर्णांक64_t aperr:1;
		uपूर्णांक64_t serr:1;
		uपूर्णांक64_t tsr_abt:1;
		uपूर्णांक64_t msc_msg:1;
		uपूर्णांक64_t msi_mabt:1;
		uपूर्णांक64_t msi_tabt:1;
		uपूर्णांक64_t msi_per:1;
		uपूर्णांक64_t mr_tto:1;
		uपूर्णांक64_t mr_abt:1;
		uपूर्णांक64_t tr_abt:1;
		uपूर्णांक64_t mr_wtto:1;
		uपूर्णांक64_t mr_wabt:1;
		uपूर्णांक64_t tr_wabt:1;
#अन्यथा
		uपूर्णांक64_t tr_wabt:1;
		uपूर्णांक64_t mr_wabt:1;
		uपूर्णांक64_t mr_wtto:1;
		uपूर्णांक64_t tr_abt:1;
		uपूर्णांक64_t mr_abt:1;
		uपूर्णांक64_t mr_tto:1;
		uपूर्णांक64_t msi_per:1;
		uपूर्णांक64_t msi_tabt:1;
		uपूर्णांक64_t msi_mabt:1;
		uपूर्णांक64_t msc_msg:1;
		uपूर्णांक64_t tsr_abt:1;
		uपूर्णांक64_t serr:1;
		uपूर्णांक64_t aperr:1;
		uपूर्णांक64_t dperr:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t rsl_पूर्णांक:1;
		uपूर्णांक64_t pcnt0:1;
		uपूर्णांक64_t pcnt1:1;
		uपूर्णांक64_t pcnt2:1;
		uपूर्णांक64_t pcnt3:1;
		uपूर्णांक64_t pसमय0:1;
		uपूर्णांक64_t pसमय1:1;
		uपूर्णांक64_t pसमय2:1;
		uपूर्णांक64_t pसमय3:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pci_पूर्णांक_sum_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t reserved_22_24:3;
		uपूर्णांक64_t pसमय0:1;
		uपूर्णांक64_t reserved_18_20:3;
		uपूर्णांक64_t pcnt0:1;
		uपूर्णांक64_t rsl_पूर्णांक:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t dperr:1;
		uपूर्णांक64_t aperr:1;
		uपूर्णांक64_t serr:1;
		uपूर्णांक64_t tsr_abt:1;
		uपूर्णांक64_t msc_msg:1;
		uपूर्णांक64_t msi_mabt:1;
		uपूर्णांक64_t msi_tabt:1;
		uपूर्णांक64_t msi_per:1;
		uपूर्णांक64_t mr_tto:1;
		uपूर्णांक64_t mr_abt:1;
		uपूर्णांक64_t tr_abt:1;
		uपूर्णांक64_t mr_wtto:1;
		uपूर्णांक64_t mr_wabt:1;
		uपूर्णांक64_t tr_wabt:1;
#अन्यथा
		uपूर्णांक64_t tr_wabt:1;
		uपूर्णांक64_t mr_wabt:1;
		uपूर्णांक64_t mr_wtto:1;
		uपूर्णांक64_t tr_abt:1;
		uपूर्णांक64_t mr_abt:1;
		uपूर्णांक64_t mr_tto:1;
		uपूर्णांक64_t msi_per:1;
		uपूर्णांक64_t msi_tabt:1;
		uपूर्णांक64_t msi_mabt:1;
		uपूर्णांक64_t msc_msg:1;
		uपूर्णांक64_t tsr_abt:1;
		uपूर्णांक64_t serr:1;
		uपूर्णांक64_t aperr:1;
		uपूर्णांक64_t dperr:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t rsl_पूर्णांक:1;
		uपूर्णांक64_t pcnt0:1;
		uपूर्णांक64_t reserved_18_20:3;
		uपूर्णांक64_t pसमय0:1;
		uपूर्णांक64_t reserved_22_24:3;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pci_पूर्णांक_sum_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t reserved_23_24:2;
		uपूर्णांक64_t pसमय1:1;
		uपूर्णांक64_t pसमय0:1;
		uपूर्णांक64_t reserved_19_20:2;
		uपूर्णांक64_t pcnt1:1;
		uपूर्णांक64_t pcnt0:1;
		uपूर्णांक64_t rsl_पूर्णांक:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t dperr:1;
		uपूर्णांक64_t aperr:1;
		uपूर्णांक64_t serr:1;
		uपूर्णांक64_t tsr_abt:1;
		uपूर्णांक64_t msc_msg:1;
		uपूर्णांक64_t msi_mabt:1;
		uपूर्णांक64_t msi_tabt:1;
		uपूर्णांक64_t msi_per:1;
		uपूर्णांक64_t mr_tto:1;
		uपूर्णांक64_t mr_abt:1;
		uपूर्णांक64_t tr_abt:1;
		uपूर्णांक64_t mr_wtto:1;
		uपूर्णांक64_t mr_wabt:1;
		uपूर्णांक64_t tr_wabt:1;
#अन्यथा
		uपूर्णांक64_t tr_wabt:1;
		uपूर्णांक64_t mr_wabt:1;
		uपूर्णांक64_t mr_wtto:1;
		uपूर्णांक64_t tr_abt:1;
		uपूर्णांक64_t mr_abt:1;
		uपूर्णांक64_t mr_tto:1;
		uपूर्णांक64_t msi_per:1;
		uपूर्णांक64_t msi_tabt:1;
		uपूर्णांक64_t msi_mabt:1;
		uपूर्णांक64_t msc_msg:1;
		uपूर्णांक64_t tsr_abt:1;
		uपूर्णांक64_t serr:1;
		uपूर्णांक64_t aperr:1;
		uपूर्णांक64_t dperr:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t rsl_पूर्णांक:1;
		uपूर्णांक64_t pcnt0:1;
		uपूर्णांक64_t pcnt1:1;
		uपूर्णांक64_t reserved_19_20:2;
		uपूर्णांक64_t pसमय0:1;
		uपूर्णांक64_t pसमय1:1;
		uपूर्णांक64_t reserved_23_24:2;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण cn31xx;
पूर्ण;

जोड़ cvmx_pci_पूर्णांक_sum2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pci_पूर्णांक_sum2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t pसमय3:1;
		uपूर्णांक64_t pसमय2:1;
		uपूर्णांक64_t pसमय1:1;
		uपूर्णांक64_t pसमय0:1;
		uपूर्णांक64_t pcnt3:1;
		uपूर्णांक64_t pcnt2:1;
		uपूर्णांक64_t pcnt1:1;
		uपूर्णांक64_t pcnt0:1;
		uपूर्णांक64_t rsl_पूर्णांक:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t dperr:1;
		uपूर्णांक64_t aperr:1;
		uपूर्णांक64_t serr:1;
		uपूर्णांक64_t tsr_abt:1;
		uपूर्णांक64_t msc_msg:1;
		uपूर्णांक64_t msi_mabt:1;
		uपूर्णांक64_t msi_tabt:1;
		uपूर्णांक64_t msi_per:1;
		uपूर्णांक64_t mr_tto:1;
		uपूर्णांक64_t mr_abt:1;
		uपूर्णांक64_t tr_abt:1;
		uपूर्णांक64_t mr_wtto:1;
		uपूर्णांक64_t mr_wabt:1;
		uपूर्णांक64_t tr_wabt:1;
#अन्यथा
		uपूर्णांक64_t tr_wabt:1;
		uपूर्णांक64_t mr_wabt:1;
		uपूर्णांक64_t mr_wtto:1;
		uपूर्णांक64_t tr_abt:1;
		uपूर्णांक64_t mr_abt:1;
		uपूर्णांक64_t mr_tto:1;
		uपूर्णांक64_t msi_per:1;
		uपूर्णांक64_t msi_tabt:1;
		uपूर्णांक64_t msi_mabt:1;
		uपूर्णांक64_t msc_msg:1;
		uपूर्णांक64_t tsr_abt:1;
		uपूर्णांक64_t serr:1;
		uपूर्णांक64_t aperr:1;
		uपूर्णांक64_t dperr:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t rsl_पूर्णांक:1;
		uपूर्णांक64_t pcnt0:1;
		uपूर्णांक64_t pcnt1:1;
		uपूर्णांक64_t pcnt2:1;
		uपूर्णांक64_t pcnt3:1;
		uपूर्णांक64_t pसमय0:1;
		uपूर्णांक64_t pसमय1:1;
		uपूर्णांक64_t pसमय2:1;
		uपूर्णांक64_t pसमय3:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pci_पूर्णांक_sum2_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t reserved_22_24:3;
		uपूर्णांक64_t pसमय0:1;
		uपूर्णांक64_t reserved_18_20:3;
		uपूर्णांक64_t pcnt0:1;
		uपूर्णांक64_t rsl_पूर्णांक:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t dperr:1;
		uपूर्णांक64_t aperr:1;
		uपूर्णांक64_t serr:1;
		uपूर्णांक64_t tsr_abt:1;
		uपूर्णांक64_t msc_msg:1;
		uपूर्णांक64_t msi_mabt:1;
		uपूर्णांक64_t msi_tabt:1;
		uपूर्णांक64_t msi_per:1;
		uपूर्णांक64_t mr_tto:1;
		uपूर्णांक64_t mr_abt:1;
		uपूर्णांक64_t tr_abt:1;
		uपूर्णांक64_t mr_wtto:1;
		uपूर्णांक64_t mr_wabt:1;
		uपूर्णांक64_t tr_wabt:1;
#अन्यथा
		uपूर्णांक64_t tr_wabt:1;
		uपूर्णांक64_t mr_wabt:1;
		uपूर्णांक64_t mr_wtto:1;
		uपूर्णांक64_t tr_abt:1;
		uपूर्णांक64_t mr_abt:1;
		uपूर्णांक64_t mr_tto:1;
		uपूर्णांक64_t msi_per:1;
		uपूर्णांक64_t msi_tabt:1;
		uपूर्णांक64_t msi_mabt:1;
		uपूर्णांक64_t msc_msg:1;
		uपूर्णांक64_t tsr_abt:1;
		uपूर्णांक64_t serr:1;
		uपूर्णांक64_t aperr:1;
		uपूर्णांक64_t dperr:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t rsl_पूर्णांक:1;
		uपूर्णांक64_t pcnt0:1;
		uपूर्णांक64_t reserved_18_20:3;
		uपूर्णांक64_t pसमय0:1;
		uपूर्णांक64_t reserved_22_24:3;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pci_पूर्णांक_sum2_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t reserved_23_24:2;
		uपूर्णांक64_t pसमय1:1;
		uपूर्णांक64_t pसमय0:1;
		uपूर्णांक64_t reserved_19_20:2;
		uपूर्णांक64_t pcnt1:1;
		uपूर्णांक64_t pcnt0:1;
		uपूर्णांक64_t rsl_पूर्णांक:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t dperr:1;
		uपूर्णांक64_t aperr:1;
		uपूर्णांक64_t serr:1;
		uपूर्णांक64_t tsr_abt:1;
		uपूर्णांक64_t msc_msg:1;
		uपूर्णांक64_t msi_mabt:1;
		uपूर्णांक64_t msi_tabt:1;
		uपूर्णांक64_t msi_per:1;
		uपूर्णांक64_t mr_tto:1;
		uपूर्णांक64_t mr_abt:1;
		uपूर्णांक64_t tr_abt:1;
		uपूर्णांक64_t mr_wtto:1;
		uपूर्णांक64_t mr_wabt:1;
		uपूर्णांक64_t tr_wabt:1;
#अन्यथा
		uपूर्णांक64_t tr_wabt:1;
		uपूर्णांक64_t mr_wabt:1;
		uपूर्णांक64_t mr_wtto:1;
		uपूर्णांक64_t tr_abt:1;
		uपूर्णांक64_t mr_abt:1;
		uपूर्णांक64_t mr_tto:1;
		uपूर्णांक64_t msi_per:1;
		uपूर्णांक64_t msi_tabt:1;
		uपूर्णांक64_t msi_mabt:1;
		uपूर्णांक64_t msc_msg:1;
		uपूर्णांक64_t tsr_abt:1;
		uपूर्णांक64_t serr:1;
		uपूर्णांक64_t aperr:1;
		uपूर्णांक64_t dperr:1;
		uपूर्णांक64_t ill_rwr:1;
		uपूर्णांक64_t ill_rrd:1;
		uपूर्णांक64_t rsl_पूर्णांक:1;
		uपूर्णांक64_t pcnt0:1;
		uपूर्णांक64_t pcnt1:1;
		uपूर्णांक64_t reserved_19_20:2;
		uपूर्णांक64_t pसमय0:1;
		uपूर्णांक64_t pसमय1:1;
		uपूर्णांक64_t reserved_23_24:2;
		uपूर्णांक64_t dcnt0:1;
		uपूर्णांक64_t dcnt1:1;
		uपूर्णांक64_t dसमय0:1;
		uपूर्णांक64_t dसमय1:1;
		uपूर्णांक64_t dma0_fi:1;
		uपूर्णांक64_t dma1_fi:1;
		uपूर्णांक64_t win_wr:1;
		uपूर्णांक64_t ill_wr:1;
		uपूर्णांक64_t ill_rd:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण cn31xx;
पूर्ण;

जोड़ cvmx_pci_msi_rcv अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_msi_rcv_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t reserved_6_31:26;
		uपूर्णांक32_t पूर्णांकr:6;
#अन्यथा
		uपूर्णांक32_t पूर्णांकr:6;
		uपूर्णांक32_t reserved_6_31:26;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_pkt_creditsx अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_pkt_creditsx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t pkt_cnt:16;
		uपूर्णांक32_t ptr_cnt:16;
#अन्यथा
		uपूर्णांक32_t ptr_cnt:16;
		uपूर्णांक32_t pkt_cnt:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_pkts_sentx अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_pkts_sentx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t pkt_cnt:32;
#अन्यथा
		uपूर्णांक32_t pkt_cnt:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_pkts_sent_पूर्णांक_levx अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_pkts_sent_पूर्णांक_levx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t pkt_cnt:32;
#अन्यथा
		uपूर्णांक32_t pkt_cnt:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_pkts_sent_समयx अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_pkts_sent_समयx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t pkt_समय:32;
#अन्यथा
		uपूर्णांक32_t pkt_समय:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_पढ़ो_cmd_6 अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_पढ़ो_cmd_6_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t reserved_9_31:23;
		uपूर्णांक32_t min_data:6;
		uपूर्णांक32_t prefetch:3;
#अन्यथा
		uपूर्णांक32_t prefetch:3;
		uपूर्णांक32_t min_data:6;
		uपूर्णांक32_t reserved_9_31:23;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_पढ़ो_cmd_c अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_पढ़ो_cmd_c_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t reserved_9_31:23;
		uपूर्णांक32_t min_data:6;
		uपूर्णांक32_t prefetch:3;
#अन्यथा
		uपूर्णांक32_t prefetch:3;
		uपूर्णांक32_t min_data:6;
		uपूर्णांक32_t reserved_9_31:23;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_पढ़ो_cmd_e अणु
	uपूर्णांक32_t u32;
	काष्ठा cvmx_pci_पढ़ो_cmd_e_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक32_t reserved_9_31:23;
		uपूर्णांक32_t min_data:6;
		uपूर्णांक32_t prefetch:3;
#अन्यथा
		uपूर्णांक32_t prefetch:3;
		uपूर्णांक32_t min_data:6;
		uपूर्णांक32_t reserved_9_31:23;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_पढ़ो_समयout अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pci_पढ़ो_समयout_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t enb:1;
		uपूर्णांक64_t cnt:31;
#अन्यथा
		uपूर्णांक64_t cnt:31;
		uपूर्णांक64_t enb:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_scm_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pci_scm_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t scm:32;
#अन्यथा
		uपूर्णांक64_t scm:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_tsr_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pci_tsr_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_36_63:28;
		uपूर्णांक64_t tsr:36;
#अन्यथा
		uपूर्णांक64_t tsr:36;
		uपूर्णांक64_t reserved_36_63:28;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_win_rd_addr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pci_win_rd_addr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_49_63:15;
		uपूर्णांक64_t iobit:1;
		uपूर्णांक64_t reserved_0_47:48;
#अन्यथा
		uपूर्णांक64_t reserved_0_47:48;
		uपूर्णांक64_t iobit:1;
		uपूर्णांक64_t reserved_49_63:15;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pci_win_rd_addr_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_49_63:15;
		uपूर्णांक64_t iobit:1;
		uपूर्णांक64_t rd_addr:46;
		uपूर्णांक64_t reserved_0_1:2;
#अन्यथा
		uपूर्णांक64_t reserved_0_1:2;
		uपूर्णांक64_t rd_addr:46;
		uपूर्णांक64_t iobit:1;
		uपूर्णांक64_t reserved_49_63:15;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pci_win_rd_addr_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_49_63:15;
		uपूर्णांक64_t iobit:1;
		uपूर्णांक64_t rd_addr:45;
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t rd_addr:45;
		uपूर्णांक64_t iobit:1;
		uपूर्णांक64_t reserved_49_63:15;
#पूर्ण_अगर
	पूर्ण cn38xx;
पूर्ण;

जोड़ cvmx_pci_win_rd_data अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pci_win_rd_data_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t rd_data:64;
#अन्यथा
		uपूर्णांक64_t rd_data:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_win_wr_addr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pci_win_wr_addr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_49_63:15;
		uपूर्णांक64_t iobit:1;
		uपूर्णांक64_t wr_addr:45;
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t wr_addr:45;
		uपूर्णांक64_t iobit:1;
		uपूर्णांक64_t reserved_49_63:15;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_win_wr_data अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pci_win_wr_data_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t wr_data:64;
#अन्यथा
		uपूर्णांक64_t wr_data:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pci_win_wr_mask अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pci_win_wr_mask_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t wr_mask:8;
#अन्यथा
		uपूर्णांक64_t wr_mask:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
