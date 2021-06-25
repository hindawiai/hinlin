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

#अगर_अघोषित __CVMX_UCTLX_DEFS_H__
#घोषणा __CVMX_UCTLX_DEFS_H__

#घोषणा CVMX_UCTLX_BIST_STATUS(block_id) (CVMX_ADD_IO_SEG(0x000118006F0000A0ull))
#घोषणा CVMX_UCTLX_CLK_RST_CTL(block_id) (CVMX_ADD_IO_SEG(0x000118006F000000ull))
#घोषणा CVMX_UCTLX_EHCI_CTL(block_id) (CVMX_ADD_IO_SEG(0x000118006F000080ull))
#घोषणा CVMX_UCTLX_EHCI_FLA(block_id) (CVMX_ADD_IO_SEG(0x000118006F0000A8ull))
#घोषणा CVMX_UCTLX_ERTO_CTL(block_id) (CVMX_ADD_IO_SEG(0x000118006F000090ull))
#घोषणा CVMX_UCTLX_IF_ENA(block_id) (CVMX_ADD_IO_SEG(0x000118006F000030ull))
#घोषणा CVMX_UCTLX_INT_ENA(block_id) (CVMX_ADD_IO_SEG(0x000118006F000028ull))
#घोषणा CVMX_UCTLX_INT_REG(block_id) (CVMX_ADD_IO_SEG(0x000118006F000020ull))
#घोषणा CVMX_UCTLX_OHCI_CTL(block_id) (CVMX_ADD_IO_SEG(0x000118006F000088ull))
#घोषणा CVMX_UCTLX_ORTO_CTL(block_id) (CVMX_ADD_IO_SEG(0x000118006F000098ull))
#घोषणा CVMX_UCTLX_PPAF_WM(block_id) (CVMX_ADD_IO_SEG(0x000118006F000038ull))
#घोषणा CVMX_UCTLX_UPHY_CTL_STATUS(block_id) (CVMX_ADD_IO_SEG(0x000118006F000008ull))
#घोषणा CVMX_UCTLX_UPHY_PORTX_CTL_STATUS(offset, block_id) (CVMX_ADD_IO_SEG(0x000118006F000010ull) + (((offset) & 1) + ((block_id) & 0) * 0x0ull) * 8)

जोड़ cvmx_uctlx_bist_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_uctlx_bist_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t data_bis:1;
		uपूर्णांक64_t desc_bis:1;
		uपूर्णांक64_t erbm_bis:1;
		uपूर्णांक64_t orbm_bis:1;
		uपूर्णांक64_t wrbm_bis:1;
		uपूर्णांक64_t ppaf_bis:1;
#अन्यथा
		uपूर्णांक64_t ppaf_bis:1;
		uपूर्णांक64_t wrbm_bis:1;
		uपूर्णांक64_t orbm_bis:1;
		uपूर्णांक64_t erbm_bis:1;
		uपूर्णांक64_t desc_bis:1;
		uपूर्णांक64_t data_bis:1;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_uctlx_clk_rst_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_uctlx_clk_rst_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t clear_bist:1;
		uपूर्णांक64_t start_bist:1;
		uपूर्णांक64_t ehci_sm:1;
		uपूर्णांक64_t ohci_clkcktrst:1;
		uपूर्णांक64_t ohci_sm:1;
		uपूर्णांक64_t ohci_susp_lgcy:1;
		uपूर्णांक64_t app_start_clk:1;
		uपूर्णांक64_t o_clkभाग_rst:1;
		uपूर्णांक64_t h_clkभाग_byp:1;
		uपूर्णांक64_t h_clkभाग_rst:1;
		uपूर्णांक64_t h_clkभाग_en:1;
		uपूर्णांक64_t o_clkभाग_en:1;
		uपूर्णांक64_t h_भाग:4;
		uपूर्णांक64_t p_refclk_sel:2;
		uपूर्णांक64_t p_refclk_भाग:2;
		uपूर्णांक64_t reserved_4_4:1;
		uपूर्णांक64_t p_com_on:1;
		uपूर्णांक64_t p_por:1;
		uपूर्णांक64_t p_prst:1;
		uपूर्णांक64_t hrst:1;
#अन्यथा
		uपूर्णांक64_t hrst:1;
		uपूर्णांक64_t p_prst:1;
		uपूर्णांक64_t p_por:1;
		uपूर्णांक64_t p_com_on:1;
		uपूर्णांक64_t reserved_4_4:1;
		uपूर्णांक64_t p_refclk_भाग:2;
		uपूर्णांक64_t p_refclk_sel:2;
		uपूर्णांक64_t h_भाग:4;
		uपूर्णांक64_t o_clkभाग_en:1;
		uपूर्णांक64_t h_clkभाग_en:1;
		uपूर्णांक64_t h_clkभाग_rst:1;
		uपूर्णांक64_t h_clkभाग_byp:1;
		uपूर्णांक64_t o_clkभाग_rst:1;
		uपूर्णांक64_t app_start_clk:1;
		uपूर्णांक64_t ohci_susp_lgcy:1;
		uपूर्णांक64_t ohci_sm:1;
		uपूर्णांक64_t ohci_clkcktrst:1;
		uपूर्णांक64_t ehci_sm:1;
		uपूर्णांक64_t start_bist:1;
		uपूर्णांक64_t clear_bist:1;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_uctlx_ehci_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_uctlx_ehci_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t desc_rbm:1;
		uपूर्णांक64_t reg_nb:1;
		uपूर्णांक64_t l2c_dc:1;
		uपूर्णांक64_t l2c_bc:1;
		uपूर्णांक64_t l2c_0pag:1;
		uपूर्णांक64_t l2c_stt:1;
		uपूर्णांक64_t l2c_buff_emod:2;
		uपूर्णांक64_t l2c_desc_emod:2;
		uपूर्णांक64_t inv_reg_a2:1;
		uपूर्णांक64_t ehci_64b_addr_en:1;
		uपूर्णांक64_t l2c_addr_msb:8;
#अन्यथा
		uपूर्णांक64_t l2c_addr_msb:8;
		uपूर्णांक64_t ehci_64b_addr_en:1;
		uपूर्णांक64_t inv_reg_a2:1;
		uपूर्णांक64_t l2c_desc_emod:2;
		uपूर्णांक64_t l2c_buff_emod:2;
		uपूर्णांक64_t l2c_stt:1;
		uपूर्णांक64_t l2c_0pag:1;
		uपूर्णांक64_t l2c_bc:1;
		uपूर्णांक64_t l2c_dc:1;
		uपूर्णांक64_t reg_nb:1;
		uपूर्णांक64_t desc_rbm:1;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_uctlx_ehci_fla अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_uctlx_ehci_fla_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t fla:6;
#अन्यथा
		uपूर्णांक64_t fla:6;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_uctlx_erto_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_uctlx_erto_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t to_val:27;
		uपूर्णांक64_t reserved_0_4:5;
#अन्यथा
		uपूर्णांक64_t reserved_0_4:5;
		uपूर्णांक64_t to_val:27;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_uctlx_अगर_ena अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_uctlx_अगर_ena_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t en:1;
#अन्यथा
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_uctlx_पूर्णांक_ena अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_uctlx_पूर्णांक_ena_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t ec_ovf_e:1;
		uपूर्णांक64_t oc_ovf_e:1;
		uपूर्णांक64_t wb_pop_e:1;
		uपूर्णांक64_t wb_psh_f:1;
		uपूर्णांक64_t cf_psh_f:1;
		uपूर्णांक64_t or_psh_f:1;
		uपूर्णांक64_t er_psh_f:1;
		uपूर्णांक64_t pp_psh_f:1;
#अन्यथा
		uपूर्णांक64_t pp_psh_f:1;
		uपूर्णांक64_t er_psh_f:1;
		uपूर्णांक64_t or_psh_f:1;
		uपूर्णांक64_t cf_psh_f:1;
		uपूर्णांक64_t wb_psh_f:1;
		uपूर्णांक64_t wb_pop_e:1;
		uपूर्णांक64_t oc_ovf_e:1;
		uपूर्णांक64_t ec_ovf_e:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_uctlx_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_uctlx_पूर्णांक_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t ec_ovf_e:1;
		uपूर्णांक64_t oc_ovf_e:1;
		uपूर्णांक64_t wb_pop_e:1;
		uपूर्णांक64_t wb_psh_f:1;
		uपूर्णांक64_t cf_psh_f:1;
		uपूर्णांक64_t or_psh_f:1;
		uपूर्णांक64_t er_psh_f:1;
		uपूर्णांक64_t pp_psh_f:1;
#अन्यथा
		uपूर्णांक64_t pp_psh_f:1;
		uपूर्णांक64_t er_psh_f:1;
		uपूर्णांक64_t or_psh_f:1;
		uपूर्णांक64_t cf_psh_f:1;
		uपूर्णांक64_t wb_psh_f:1;
		uपूर्णांक64_t wb_pop_e:1;
		uपूर्णांक64_t oc_ovf_e:1;
		uपूर्णांक64_t ec_ovf_e:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_uctlx_ohci_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_uctlx_ohci_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_19_63:45;
		uपूर्णांक64_t reg_nb:1;
		uपूर्णांक64_t l2c_dc:1;
		uपूर्णांक64_t l2c_bc:1;
		uपूर्णांक64_t l2c_0pag:1;
		uपूर्णांक64_t l2c_stt:1;
		uपूर्णांक64_t l2c_buff_emod:2;
		uपूर्णांक64_t l2c_desc_emod:2;
		uपूर्णांक64_t inv_reg_a2:1;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t l2c_addr_msb:8;
#अन्यथा
		uपूर्णांक64_t l2c_addr_msb:8;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t inv_reg_a2:1;
		uपूर्णांक64_t l2c_desc_emod:2;
		uपूर्णांक64_t l2c_buff_emod:2;
		uपूर्णांक64_t l2c_stt:1;
		uपूर्णांक64_t l2c_0pag:1;
		uपूर्णांक64_t l2c_bc:1;
		uपूर्णांक64_t l2c_dc:1;
		uपूर्णांक64_t reg_nb:1;
		uपूर्णांक64_t reserved_19_63:45;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_uctlx_orto_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_uctlx_orto_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t to_val:24;
		uपूर्णांक64_t reserved_0_7:8;
#अन्यथा
		uपूर्णांक64_t reserved_0_7:8;
		uपूर्णांक64_t to_val:24;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_uctlx_ppaf_wm अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_uctlx_ppaf_wm_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t wm:5;
#अन्यथा
		uपूर्णांक64_t wm:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_uctlx_uphy_ctl_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_uctlx_uphy_ctl_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t bist_करोne:1;
		uपूर्णांक64_t bist_err:1;
		uपूर्णांक64_t hsbist:1;
		uपूर्णांक64_t fsbist:1;
		uपूर्णांक64_t lsbist:1;
		uपूर्णांक64_t siddq:1;
		uपूर्णांक64_t vtest_en:1;
		uपूर्णांक64_t uphy_bist:1;
		uपूर्णांक64_t bist_en:1;
		uपूर्णांक64_t ate_reset:1;
#अन्यथा
		uपूर्णांक64_t ate_reset:1;
		uपूर्णांक64_t bist_en:1;
		uपूर्णांक64_t uphy_bist:1;
		uपूर्णांक64_t vtest_en:1;
		uपूर्णांक64_t siddq:1;
		uपूर्णांक64_t lsbist:1;
		uपूर्णांक64_t fsbist:1;
		uपूर्णांक64_t hsbist:1;
		uपूर्णांक64_t bist_err:1;
		uपूर्णांक64_t bist_करोne:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_uctlx_uphy_portx_ctl_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_uctlx_uphy_portx_ctl_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_43_63:21;
		uपूर्णांक64_t tdata_out:4;
		uपूर्णांक64_t txbiststuffenh:1;
		uपूर्णांक64_t txbiststuffen:1;
		uपूर्णांक64_t dmpullकरोwn:1;
		uपूर्णांक64_t dppullकरोwn:1;
		uपूर्णांक64_t vbusvldext:1;
		uपूर्णांक64_t portreset:1;
		uपूर्णांक64_t txhsvxtune:2;
		uपूर्णांक64_t txvreftune:4;
		uपूर्णांक64_t txrisetune:1;
		uपूर्णांक64_t txpreemphasistune:1;
		uपूर्णांक64_t txfslstune:4;
		uपूर्णांक64_t sqrxtune:3;
		uपूर्णांक64_t compdistune:3;
		uपूर्णांक64_t loop_en:1;
		uपूर्णांक64_t tclk:1;
		uपूर्णांक64_t tdata_sel:1;
		uपूर्णांक64_t taddr_in:4;
		uपूर्णांक64_t tdata_in:8;
#अन्यथा
		uपूर्णांक64_t tdata_in:8;
		uपूर्णांक64_t taddr_in:4;
		uपूर्णांक64_t tdata_sel:1;
		uपूर्णांक64_t tclk:1;
		uपूर्णांक64_t loop_en:1;
		uपूर्णांक64_t compdistune:3;
		uपूर्णांक64_t sqrxtune:3;
		uपूर्णांक64_t txfslstune:4;
		uपूर्णांक64_t txpreemphasistune:1;
		uपूर्णांक64_t txrisetune:1;
		uपूर्णांक64_t txvreftune:4;
		uपूर्णांक64_t txhsvxtune:2;
		uपूर्णांक64_t portreset:1;
		uपूर्णांक64_t vbusvldext:1;
		uपूर्णांक64_t dppullकरोwn:1;
		uपूर्णांक64_t dmpullकरोwn:1;
		uपूर्णांक64_t txbiststuffen:1;
		uपूर्णांक64_t txbiststuffenh:1;
		uपूर्णांक64_t tdata_out:4;
		uपूर्णांक64_t reserved_43_63:21;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
