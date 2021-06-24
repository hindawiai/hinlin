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

#अगर_अघोषित __CVMX_DPI_DEFS_H__
#घोषणा __CVMX_DPI_DEFS_H__

#घोषणा CVMX_DPI_BIST_STATUS (CVMX_ADD_IO_SEG(0x0001DF0000000000ull))
#घोषणा CVMX_DPI_CTL (CVMX_ADD_IO_SEG(0x0001DF0000000040ull))
#घोषणा CVMX_DPI_DMAX_COUNTS(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000300ull) + ((offset) & 7) * 8)
#घोषणा CVMX_DPI_DMAX_DBELL(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000200ull) + ((offset) & 7) * 8)
#घोषणा CVMX_DPI_DMAX_ERR_RSP_STATUS(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000A80ull) + ((offset) & 7) * 8)
#घोषणा CVMX_DPI_DMAX_IBUFF_SADDR(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000280ull) + ((offset) & 7) * 8)
#घोषणा CVMX_DPI_DMAX_IFLIGHT(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000A00ull) + ((offset) & 7) * 8)
#घोषणा CVMX_DPI_DMAX_NADDR(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000380ull) + ((offset) & 7) * 8)
#घोषणा CVMX_DPI_DMAX_REQBNK0(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000400ull) + ((offset) & 7) * 8)
#घोषणा CVMX_DPI_DMAX_REQBNK1(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000480ull) + ((offset) & 7) * 8)
#घोषणा CVMX_DPI_DMA_CONTROL (CVMX_ADD_IO_SEG(0x0001DF0000000048ull))
#घोषणा CVMX_DPI_DMA_ENGX_EN(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000080ull) + ((offset) & 7) * 8)
#घोषणा CVMX_DPI_DMA_PPX_CNT(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000B00ull) + ((offset) & 31) * 8)
#घोषणा CVMX_DPI_ENGX_BUF(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000880ull) + ((offset) & 7) * 8)
#घोषणा CVMX_DPI_INFO_REG (CVMX_ADD_IO_SEG(0x0001DF0000000980ull))
#घोषणा CVMX_DPI_INT_EN (CVMX_ADD_IO_SEG(0x0001DF0000000010ull))
#घोषणा CVMX_DPI_INT_REG (CVMX_ADD_IO_SEG(0x0001DF0000000008ull))
#घोषणा CVMX_DPI_NCBX_CFG(block_id) (CVMX_ADD_IO_SEG(0x0001DF0000000800ull))
#घोषणा CVMX_DPI_PINT_INFO (CVMX_ADD_IO_SEG(0x0001DF0000000830ull))
#घोषणा CVMX_DPI_PKT_ERR_RSP (CVMX_ADD_IO_SEG(0x0001DF0000000078ull))
#घोषणा CVMX_DPI_REQ_ERR_RSP (CVMX_ADD_IO_SEG(0x0001DF0000000058ull))
#घोषणा CVMX_DPI_REQ_ERR_RSP_EN (CVMX_ADD_IO_SEG(0x0001DF0000000068ull))
#घोषणा CVMX_DPI_REQ_ERR_RST (CVMX_ADD_IO_SEG(0x0001DF0000000060ull))
#घोषणा CVMX_DPI_REQ_ERR_RST_EN (CVMX_ADD_IO_SEG(0x0001DF0000000070ull))
#घोषणा CVMX_DPI_REQ_ERR_SKIP_COMP (CVMX_ADD_IO_SEG(0x0001DF0000000838ull))
#घोषणा CVMX_DPI_REQ_GBL_EN (CVMX_ADD_IO_SEG(0x0001DF0000000050ull))
#घोषणा CVMX_DPI_SLI_PRTX_CFG(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000900ull) + ((offset) & 3) * 8)
अटल अंतरभूत uपूर्णांक64_t CVMX_DPI_SLI_PRTX_ERR(अचिन्हित दीर्घ offset)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001DF0000000920ull) + (offset) * 8;
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:

		अगर (OCTEON_IS_MODEL(OCTEON_CN68XX_PASS1))
			वापस CVMX_ADD_IO_SEG(0x0001DF0000000928ull) + (offset) * 8;

		अगर (OCTEON_IS_MODEL(OCTEON_CN68XX_PASS2))
			वापस CVMX_ADD_IO_SEG(0x0001DF0000000920ull) + (offset) * 8;
		वापस CVMX_ADD_IO_SEG(0x0001DF0000000920ull) + (offset) * 8;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001DF0000000928ull) + (offset) * 8;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001DF0000000920ull) + (offset) * 8;
पूर्ण

#घोषणा CVMX_DPI_SLI_PRTX_ERR_INFO(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000940ull) + ((offset) & 3) * 8)

जोड़ cvmx_dpi_bist_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_bist_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_47_63:17;
		uपूर्णांक64_t bist:47;
#अन्यथा
		uपूर्णांक64_t bist:47;
		uपूर्णांक64_t reserved_47_63:17;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_dpi_bist_status_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_45_63:19;
		uपूर्णांक64_t bist:45;
#अन्यथा
		uपूर्णांक64_t bist:45;
		uपूर्णांक64_t reserved_45_63:19;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_dpi_bist_status_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_37_63:27;
		uपूर्णांक64_t bist:37;
#अन्यथा
		uपूर्णांक64_t bist:37;
		uपूर्णांक64_t reserved_37_63:27;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_dpi_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t clk:1;
		uपूर्णांक64_t en:1;
#अन्यथा
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t clk:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_dpi_ctl_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t en:1;
#अन्यथा
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_dpi_dmax_counts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_dmax_counts_s अणु
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

जोड़ cvmx_dpi_dmax_dbell अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_dmax_dbell_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t dbell:16;
#अन्यथा
		uपूर्णांक64_t dbell:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_dmax_err_rsp_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_dmax_err_rsp_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t status:6;
#अन्यथा
		uपूर्णांक64_t status:6;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_dmax_ibuff_saddr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_dmax_ibuff_saddr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t csize:14;
		uपूर्णांक64_t reserved_41_47:7;
		uपूर्णांक64_t idle:1;
		uपूर्णांक64_t saddr:33;
		uपूर्णांक64_t reserved_0_6:7;
#अन्यथा
		uपूर्णांक64_t reserved_0_6:7;
		uपूर्णांक64_t saddr:33;
		uपूर्णांक64_t idle:1;
		uपूर्णांक64_t reserved_41_47:7;
		uपूर्णांक64_t csize:14;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_dpi_dmax_ibuff_saddr_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t csize:14;
		uपूर्णांक64_t reserved_41_47:7;
		uपूर्णांक64_t idle:1;
		uपूर्णांक64_t reserved_36_39:4;
		uपूर्णांक64_t saddr:29;
		uपूर्णांक64_t reserved_0_6:7;
#अन्यथा
		uपूर्णांक64_t reserved_0_6:7;
		uपूर्णांक64_t saddr:29;
		uपूर्णांक64_t reserved_36_39:4;
		uपूर्णांक64_t idle:1;
		uपूर्णांक64_t reserved_41_47:7;
		uपूर्णांक64_t csize:14;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_dpi_dmax_अगरlight अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_dmax_अगरlight_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t cnt:3;
#अन्यथा
		uपूर्णांक64_t cnt:3;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_dmax_naddr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_dmax_naddr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t addr:40;
#अन्यथा
		uपूर्णांक64_t addr:40;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_dpi_dmax_naddr_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_36_63:28;
		uपूर्णांक64_t addr:36;
#अन्यथा
		uपूर्णांक64_t addr:36;
		uपूर्णांक64_t reserved_36_63:28;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_dpi_dmax_reqbnk0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_dmax_reqbnk0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t state:64;
#अन्यथा
		uपूर्णांक64_t state:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_dmax_reqbnk1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_dmax_reqbnk1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t state:64;
#अन्यथा
		uपूर्णांक64_t state:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_dma_control अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_dma_control_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t dici_mode:1;
		uपूर्णांक64_t pkt_en1:1;
		uपूर्णांक64_t ffp_dis:1;
		uपूर्णांक64_t commit_mode:1;
		uपूर्णांक64_t pkt_hp:1;
		uपूर्णांक64_t pkt_en:1;
		uपूर्णांक64_t reserved_54_55:2;
		uपूर्णांक64_t dma_enb:6;
		uपूर्णांक64_t reserved_34_47:14;
		uपूर्णांक64_t b0_lend:1;
		uपूर्णांक64_t dwb_denb:1;
		uपूर्णांक64_t dwb_ichk:9;
		uपूर्णांक64_t fpa_que:3;
		uपूर्णांक64_t o_add1:1;
		uपूर्णांक64_t o_ro:1;
		uपूर्णांक64_t o_ns:1;
		uपूर्णांक64_t o_es:2;
		uपूर्णांक64_t o_mode:1;
		uपूर्णांक64_t reserved_0_13:14;
#अन्यथा
		uपूर्णांक64_t reserved_0_13:14;
		uपूर्णांक64_t o_mode:1;
		uपूर्णांक64_t o_es:2;
		uपूर्णांक64_t o_ns:1;
		uपूर्णांक64_t o_ro:1;
		uपूर्णांक64_t o_add1:1;
		uपूर्णांक64_t fpa_que:3;
		uपूर्णांक64_t dwb_ichk:9;
		uपूर्णांक64_t dwb_denb:1;
		uपूर्णांक64_t b0_lend:1;
		uपूर्णांक64_t reserved_34_47:14;
		uपूर्णांक64_t dma_enb:6;
		uपूर्णांक64_t reserved_54_55:2;
		uपूर्णांक64_t pkt_en:1;
		uपूर्णांक64_t pkt_hp:1;
		uपूर्णांक64_t commit_mode:1;
		uपूर्णांक64_t ffp_dis:1;
		uपूर्णांक64_t pkt_en1:1;
		uपूर्णांक64_t dici_mode:1;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_dpi_dma_control_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_61_63:3;
		uपूर्णांक64_t pkt_en1:1;
		uपूर्णांक64_t ffp_dis:1;
		uपूर्णांक64_t commit_mode:1;
		uपूर्णांक64_t pkt_hp:1;
		uपूर्णांक64_t pkt_en:1;
		uपूर्णांक64_t reserved_54_55:2;
		uपूर्णांक64_t dma_enb:6;
		uपूर्णांक64_t reserved_34_47:14;
		uपूर्णांक64_t b0_lend:1;
		uपूर्णांक64_t dwb_denb:1;
		uपूर्णांक64_t dwb_ichk:9;
		uपूर्णांक64_t fpa_que:3;
		uपूर्णांक64_t o_add1:1;
		uपूर्णांक64_t o_ro:1;
		uपूर्णांक64_t o_ns:1;
		uपूर्णांक64_t o_es:2;
		uपूर्णांक64_t o_mode:1;
		uपूर्णांक64_t reserved_0_13:14;
#अन्यथा
		uपूर्णांक64_t reserved_0_13:14;
		uपूर्णांक64_t o_mode:1;
		uपूर्णांक64_t o_es:2;
		uपूर्णांक64_t o_ns:1;
		uपूर्णांक64_t o_ro:1;
		uपूर्णांक64_t o_add1:1;
		uपूर्णांक64_t fpa_que:3;
		uपूर्णांक64_t dwb_ichk:9;
		uपूर्णांक64_t dwb_denb:1;
		uपूर्णांक64_t b0_lend:1;
		uपूर्णांक64_t reserved_34_47:14;
		uपूर्णांक64_t dma_enb:6;
		uपूर्णांक64_t reserved_54_55:2;
		uपूर्णांक64_t pkt_en:1;
		uपूर्णांक64_t pkt_hp:1;
		uपूर्णांक64_t commit_mode:1;
		uपूर्णांक64_t ffp_dis:1;
		uपूर्णांक64_t pkt_en1:1;
		uपूर्णांक64_t reserved_61_63:3;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_dpi_dma_control_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_59_63:5;
		uपूर्णांक64_t commit_mode:1;
		uपूर्णांक64_t pkt_hp:1;
		uपूर्णांक64_t pkt_en:1;
		uपूर्णांक64_t reserved_54_55:2;
		uपूर्णांक64_t dma_enb:6;
		uपूर्णांक64_t reserved_34_47:14;
		uपूर्णांक64_t b0_lend:1;
		uपूर्णांक64_t dwb_denb:1;
		uपूर्णांक64_t dwb_ichk:9;
		uपूर्णांक64_t fpa_que:3;
		uपूर्णांक64_t o_add1:1;
		uपूर्णांक64_t o_ro:1;
		uपूर्णांक64_t o_ns:1;
		uपूर्णांक64_t o_es:2;
		uपूर्णांक64_t o_mode:1;
		uपूर्णांक64_t reserved_0_13:14;
#अन्यथा
		uपूर्णांक64_t reserved_0_13:14;
		uपूर्णांक64_t o_mode:1;
		uपूर्णांक64_t o_es:2;
		uपूर्णांक64_t o_ns:1;
		uपूर्णांक64_t o_ro:1;
		uपूर्णांक64_t o_add1:1;
		uपूर्णांक64_t fpa_que:3;
		uपूर्णांक64_t dwb_ichk:9;
		uपूर्णांक64_t dwb_denb:1;
		uपूर्णांक64_t b0_lend:1;
		uपूर्णांक64_t reserved_34_47:14;
		uपूर्णांक64_t dma_enb:6;
		uपूर्णांक64_t reserved_54_55:2;
		uपूर्णांक64_t pkt_en:1;
		uपूर्णांक64_t pkt_hp:1;
		uपूर्णांक64_t commit_mode:1;
		uपूर्णांक64_t reserved_59_63:5;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_dpi_dma_engx_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_dma_engx_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t qen:8;
#अन्यथा
		uपूर्णांक64_t qen:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_dma_ppx_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_dma_ppx_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t cnt:16;
#अन्यथा
		uपूर्णांक64_t cnt:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_engx_buf अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_engx_buf_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_37_63:27;
		uपूर्णांक64_t compblks:5;
		uपूर्णांक64_t reserved_9_31:23;
		uपूर्णांक64_t base:5;
		uपूर्णांक64_t blks:4;
#अन्यथा
		uपूर्णांक64_t blks:4;
		uपूर्णांक64_t base:5;
		uपूर्णांक64_t reserved_9_31:23;
		uपूर्णांक64_t compblks:5;
		uपूर्णांक64_t reserved_37_63:27;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_dpi_engx_buf_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t base:4;
		uपूर्णांक64_t blks:4;
#अन्यथा
		uपूर्णांक64_t blks:4;
		uपूर्णांक64_t base:4;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_dpi_info_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_info_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t ffp:4;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t ncb:1;
		uपूर्णांक64_t rsl:1;
#अन्यथा
		uपूर्णांक64_t rsl:1;
		uपूर्णांक64_t ncb:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t ffp:4;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_dpi_info_reg_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t ncb:1;
		uपूर्णांक64_t rsl:1;
#अन्यथा
		uपूर्णांक64_t rsl:1;
		uपूर्णांक64_t ncb:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_dpi_पूर्णांक_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_पूर्णांक_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t sprt3_rst:1;
		uपूर्णांक64_t sprt2_rst:1;
		uपूर्णांक64_t sprt1_rst:1;
		uपूर्णांक64_t sprt0_rst:1;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t req_badfil:1;
		uपूर्णांक64_t req_inull:1;
		uपूर्णांक64_t req_anull:1;
		uपूर्णांक64_t req_undflw:1;
		uपूर्णांक64_t req_ovrflw:1;
		uपूर्णांक64_t req_badlen:1;
		uपूर्णांक64_t req_badadr:1;
		uपूर्णांक64_t dmadbo:8;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t nfovr:1;
		uपूर्णांक64_t nderr:1;
#अन्यथा
		uपूर्णांक64_t nderr:1;
		uपूर्णांक64_t nfovr:1;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t dmadbo:8;
		uपूर्णांक64_t req_badadr:1;
		uपूर्णांक64_t req_badlen:1;
		uपूर्णांक64_t req_ovrflw:1;
		uपूर्णांक64_t req_undflw:1;
		uपूर्णांक64_t req_anull:1;
		uपूर्णांक64_t req_inull:1;
		uपूर्णांक64_t req_badfil:1;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t sprt0_rst:1;
		uपूर्णांक64_t sprt1_rst:1;
		uपूर्णांक64_t sprt2_rst:1;
		uपूर्णांक64_t sprt3_rst:1;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_dpi_पूर्णांक_en_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_26_63:38;
		uपूर्णांक64_t sprt1_rst:1;
		uपूर्णांक64_t sprt0_rst:1;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t req_badfil:1;
		uपूर्णांक64_t req_inull:1;
		uपूर्णांक64_t req_anull:1;
		uपूर्णांक64_t req_undflw:1;
		uपूर्णांक64_t req_ovrflw:1;
		uपूर्णांक64_t req_badlen:1;
		uपूर्णांक64_t req_badadr:1;
		uपूर्णांक64_t dmadbo:8;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t nfovr:1;
		uपूर्णांक64_t nderr:1;
#अन्यथा
		uपूर्णांक64_t nderr:1;
		uपूर्णांक64_t nfovr:1;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t dmadbo:8;
		uपूर्णांक64_t req_badadr:1;
		uपूर्णांक64_t req_badlen:1;
		uपूर्णांक64_t req_ovrflw:1;
		uपूर्णांक64_t req_undflw:1;
		uपूर्णांक64_t req_anull:1;
		uपूर्णांक64_t req_inull:1;
		uपूर्णांक64_t req_badfil:1;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t sprt0_rst:1;
		uपूर्णांक64_t sprt1_rst:1;
		uपूर्णांक64_t reserved_26_63:38;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_dpi_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_पूर्णांक_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t sprt3_rst:1;
		uपूर्णांक64_t sprt2_rst:1;
		uपूर्णांक64_t sprt1_rst:1;
		uपूर्णांक64_t sprt0_rst:1;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t req_badfil:1;
		uपूर्णांक64_t req_inull:1;
		uपूर्णांक64_t req_anull:1;
		uपूर्णांक64_t req_undflw:1;
		uपूर्णांक64_t req_ovrflw:1;
		uपूर्णांक64_t req_badlen:1;
		uपूर्णांक64_t req_badadr:1;
		uपूर्णांक64_t dmadbo:8;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t nfovr:1;
		uपूर्णांक64_t nderr:1;
#अन्यथा
		uपूर्णांक64_t nderr:1;
		uपूर्णांक64_t nfovr:1;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t dmadbo:8;
		uपूर्णांक64_t req_badadr:1;
		uपूर्णांक64_t req_badlen:1;
		uपूर्णांक64_t req_ovrflw:1;
		uपूर्णांक64_t req_undflw:1;
		uपूर्णांक64_t req_anull:1;
		uपूर्णांक64_t req_inull:1;
		uपूर्णांक64_t req_badfil:1;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t sprt0_rst:1;
		uपूर्णांक64_t sprt1_rst:1;
		uपूर्णांक64_t sprt2_rst:1;
		uपूर्णांक64_t sprt3_rst:1;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_dpi_पूर्णांक_reg_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_26_63:38;
		uपूर्णांक64_t sprt1_rst:1;
		uपूर्णांक64_t sprt0_rst:1;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t req_badfil:1;
		uपूर्णांक64_t req_inull:1;
		uपूर्णांक64_t req_anull:1;
		uपूर्णांक64_t req_undflw:1;
		uपूर्णांक64_t req_ovrflw:1;
		uपूर्णांक64_t req_badlen:1;
		uपूर्णांक64_t req_badadr:1;
		uपूर्णांक64_t dmadbo:8;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t nfovr:1;
		uपूर्णांक64_t nderr:1;
#अन्यथा
		uपूर्णांक64_t nderr:1;
		uपूर्णांक64_t nfovr:1;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t dmadbo:8;
		uपूर्णांक64_t req_badadr:1;
		uपूर्णांक64_t req_badlen:1;
		uपूर्णांक64_t req_ovrflw:1;
		uपूर्णांक64_t req_undflw:1;
		uपूर्णांक64_t req_anull:1;
		uपूर्णांक64_t req_inull:1;
		uपूर्णांक64_t req_badfil:1;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t sprt0_rst:1;
		uपूर्णांक64_t sprt1_rst:1;
		uपूर्णांक64_t reserved_26_63:38;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_dpi_ncbx_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_ncbx_cfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t molr:6;
#अन्यथा
		uपूर्णांक64_t molr:6;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_pपूर्णांक_info अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_pपूर्णांक_info_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t iinfo:6;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t sinfo:6;
#अन्यथा
		uपूर्णांक64_t sinfo:6;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t iinfo:6;
		uपूर्णांक64_t reserved_14_63:50;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_pkt_err_rsp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_pkt_err_rsp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t pkterr:1;
#अन्यथा
		uपूर्णांक64_t pkterr:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_req_err_rsp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_req_err_rsp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t qerr:8;
#अन्यथा
		uपूर्णांक64_t qerr:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_req_err_rsp_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_req_err_rsp_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t en:8;
#अन्यथा
		uपूर्णांक64_t en:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_req_err_rst अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_req_err_rst_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t qerr:8;
#अन्यथा
		uपूर्णांक64_t qerr:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_req_err_rst_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_req_err_rst_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t en:8;
#अन्यथा
		uपूर्णांक64_t en:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_req_err_skip_comp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_req_err_skip_comp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t en_rst:8;
		uपूर्णांक64_t reserved_8_15:8;
		uपूर्णांक64_t en_rsp:8;
#अन्यथा
		uपूर्णांक64_t en_rsp:8;
		uपूर्णांक64_t reserved_8_15:8;
		uपूर्णांक64_t en_rst:8;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_req_gbl_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_req_gbl_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t qen:8;
#अन्यथा
		uपूर्णांक64_t qen:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_sli_prtx_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_sli_prtx_cfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t halt:1;
		uपूर्णांक64_t qlm_cfg:4;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t rd_mode:1;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t molr:6;
		uपूर्णांक64_t mps_lim:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t mps:1;
		uपूर्णांक64_t mrrs_lim:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t mrrs:2;
#अन्यथा
		uपूर्णांक64_t mrrs:2;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t mrrs_lim:1;
		uपूर्णांक64_t mps:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t mps_lim:1;
		uपूर्णांक64_t molr:6;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t rd_mode:1;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t qlm_cfg:4;
		uपूर्णांक64_t halt:1;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_dpi_sli_prtx_cfg_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t halt:1;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t qlm_cfg:1;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t rd_mode:1;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t molr:6;
		uपूर्णांक64_t mps_lim:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t mps:1;
		uपूर्णांक64_t mrrs_lim:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t mrrs:2;
#अन्यथा
		uपूर्णांक64_t mrrs:2;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t mrrs_lim:1;
		uपूर्णांक64_t mps:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t mps_lim:1;
		uपूर्णांक64_t molr:6;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t rd_mode:1;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t qlm_cfg:1;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t halt:1;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_dpi_sli_prtx_err अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_sli_prtx_err_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t addr:61;
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t addr:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_dpi_sli_prtx_err_info अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dpi_sli_prtx_err_info_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t lock:1;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t type:1;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t reqq:3;
#अन्यथा
		uपूर्णांक64_t reqq:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t type:1;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t lock:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
