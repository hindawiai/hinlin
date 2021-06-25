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

#अगर_अघोषित __CVMX_GPIO_DEFS_H__
#घोषणा __CVMX_GPIO_DEFS_H__

#घोषणा CVMX_GPIO_BIT_CFGX(offset) (CVMX_ADD_IO_SEG(0x0001070000000800ull) + ((offset) & 15) * 8)
#घोषणा CVMX_GPIO_BOOT_ENA (CVMX_ADD_IO_SEG(0x00010700000008A8ull))
#घोषणा CVMX_GPIO_CLK_GENX(offset) (CVMX_ADD_IO_SEG(0x00010700000008C0ull) + ((offset) & 3) * 8)
#घोषणा CVMX_GPIO_CLK_QLMX(offset) (CVMX_ADD_IO_SEG(0x00010700000008E0ull) + ((offset) & 1) * 8)
#घोषणा CVMX_GPIO_DBG_ENA (CVMX_ADD_IO_SEG(0x00010700000008A0ull))
#घोषणा CVMX_GPIO_INT_CLR (CVMX_ADD_IO_SEG(0x0001070000000898ull))
#घोषणा CVMX_GPIO_MULTI_CAST (CVMX_ADD_IO_SEG(0x00010700000008B0ull))
#घोषणा CVMX_GPIO_PIN_ENA (CVMX_ADD_IO_SEG(0x00010700000008B8ull))
#घोषणा CVMX_GPIO_RX_DAT (CVMX_ADD_IO_SEG(0x0001070000000880ull))
#घोषणा CVMX_GPIO_TIM_CTL (CVMX_ADD_IO_SEG(0x00010700000008A0ull))
#घोषणा CVMX_GPIO_TX_CLR (CVMX_ADD_IO_SEG(0x0001070000000890ull))
#घोषणा CVMX_GPIO_TX_SET (CVMX_ADD_IO_SEG(0x0001070000000888ull))
#घोषणा CVMX_GPIO_XBIT_CFGX(offset) (CVMX_ADD_IO_SEG(0x0001070000000900ull) + ((offset) & 31) * 8 - 8*16)

जोड़ cvmx_gpio_bit_cfgx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gpio_bit_cfgx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_21_63:42;
		uपूर्णांक64_t output_sel:5;
		uपूर्णांक64_t synce_sel:2;
		uपूर्णांक64_t clk_gen:1;
		uपूर्णांक64_t clk_sel:2;
		uपूर्णांक64_t fil_sel:4;
		uपूर्णांक64_t fil_cnt:4;
		uपूर्णांक64_t पूर्णांक_type:1;
		uपूर्णांक64_t पूर्णांक_en:1;
		uपूर्णांक64_t rx_xor:1;
		uपूर्णांक64_t tx_oe:1;
#अन्यथा
		uपूर्णांक64_t tx_oe:1;
		uपूर्णांक64_t rx_xor:1;
		uपूर्णांक64_t पूर्णांक_en:1;
		uपूर्णांक64_t पूर्णांक_type:1;
		uपूर्णांक64_t fil_cnt:4;
		uपूर्णांक64_t fil_sel:4;
		uपूर्णांक64_t clk_sel:2;
		uपूर्णांक64_t clk_gen:1;
		uपूर्णांक64_t synce_sel:2;
		uपूर्णांक64_t output_sel:5;
		uपूर्णांक64_t reserved_21_63:42;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gpio_bit_cfgx_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t fil_sel:4;
		uपूर्णांक64_t fil_cnt:4;
		uपूर्णांक64_t पूर्णांक_type:1;
		uपूर्णांक64_t पूर्णांक_en:1;
		uपूर्णांक64_t rx_xor:1;
		uपूर्णांक64_t tx_oe:1;
#अन्यथा
		uपूर्णांक64_t tx_oe:1;
		uपूर्णांक64_t rx_xor:1;
		uपूर्णांक64_t पूर्णांक_en:1;
		uपूर्णांक64_t पूर्णांक_type:1;
		uपूर्णांक64_t fil_cnt:4;
		uपूर्णांक64_t fil_sel:4;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_gpio_bit_cfgx_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_15_63:49;
		uपूर्णांक64_t clk_gen:1;
		uपूर्णांक64_t clk_sel:2;
		uपूर्णांक64_t fil_sel:4;
		uपूर्णांक64_t fil_cnt:4;
		uपूर्णांक64_t पूर्णांक_type:1;
		uपूर्णांक64_t पूर्णांक_en:1;
		uपूर्णांक64_t rx_xor:1;
		uपूर्णांक64_t tx_oe:1;
#अन्यथा
		uपूर्णांक64_t tx_oe:1;
		uपूर्णांक64_t rx_xor:1;
		uपूर्णांक64_t पूर्णांक_en:1;
		uपूर्णांक64_t पूर्णांक_type:1;
		uपूर्णांक64_t fil_cnt:4;
		uपूर्णांक64_t fil_sel:4;
		uपूर्णांक64_t clk_sel:2;
		uपूर्णांक64_t clk_gen:1;
		uपूर्णांक64_t reserved_15_63:49;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_gpio_boot_ena अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gpio_boot_ena_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t boot_ena:4;
		uपूर्णांक64_t reserved_0_7:8;
#अन्यथा
		uपूर्णांक64_t reserved_0_7:8;
		uपूर्णांक64_t boot_ena:4;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gpio_clk_genx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gpio_clk_genx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t n:32;
#अन्यथा
		uपूर्णांक64_t n:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gpio_clk_qlmx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gpio_clk_qlmx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t qlm_sel:3;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t भाग:1;
		uपूर्णांक64_t lane_sel:2;
#अन्यथा
		uपूर्णांक64_t lane_sel:2;
		uपूर्णांक64_t भाग:1;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t qlm_sel:3;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gpio_clk_qlmx_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t qlm_sel:2;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t भाग:1;
		uपूर्णांक64_t lane_sel:2;
#अन्यथा
		uपूर्णांक64_t lane_sel:2;
		uपूर्णांक64_t भाग:1;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t qlm_sel:2;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_gpio_clk_qlmx_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t भाग:1;
		uपूर्णांक64_t lane_sel:2;
#अन्यथा
		uपूर्णांक64_t lane_sel:2;
		uपूर्णांक64_t भाग:1;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_gpio_dbg_ena अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gpio_dbg_ena_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_21_63:43;
		uपूर्णांक64_t dbg_ena:21;
#अन्यथा
		uपूर्णांक64_t dbg_ena:21;
		uपूर्णांक64_t reserved_21_63:43;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gpio_पूर्णांक_clr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gpio_पूर्णांक_clr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t type:16;
#अन्यथा
		uपूर्णांक64_t type:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gpio_multi_cast अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gpio_multi_cast_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t en:1;
#अन्यथा
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gpio_pin_ena अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gpio_pin_ena_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t ena19:1;
		uपूर्णांक64_t ena18:1;
		uपूर्णांक64_t reserved_0_17:18;
#अन्यथा
		uपूर्णांक64_t reserved_0_17:18;
		uपूर्णांक64_t ena18:1;
		uपूर्णांक64_t ena19:1;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gpio_rx_dat अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gpio_rx_dat_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t dat:24;
#अन्यथा
		uपूर्णांक64_t dat:24;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gpio_rx_dat_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t dat:16;
#अन्यथा
		uपूर्णांक64_t dat:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_gpio_rx_dat_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t dat:20;
#अन्यथा
		uपूर्णांक64_t dat:20;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_gpio_tim_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gpio_tim_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t sel:4;
#अन्यथा
		uपूर्णांक64_t sel:4;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gpio_tx_clr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gpio_tx_clr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t clr:24;
#अन्यथा
		uपूर्णांक64_t clr:24;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gpio_tx_clr_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t clr:16;
#अन्यथा
		uपूर्णांक64_t clr:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_gpio_tx_clr_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t clr:20;
#अन्यथा
		uपूर्णांक64_t clr:20;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_gpio_tx_set अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gpio_tx_set_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t set:24;
#अन्यथा
		uपूर्णांक64_t set:24;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gpio_tx_set_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t set:16;
#अन्यथा
		uपूर्णांक64_t set:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_gpio_tx_set_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t set:20;
#अन्यथा
		uपूर्णांक64_t set:20;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_gpio_xbit_cfgx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gpio_xbit_cfgx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t synce_sel:2;
		uपूर्णांक64_t clk_gen:1;
		uपूर्णांक64_t clk_sel:2;
		uपूर्णांक64_t fil_sel:4;
		uपूर्णांक64_t fil_cnt:4;
		uपूर्णांक64_t पूर्णांक_type:1;
		uपूर्णांक64_t पूर्णांक_en:1;
		uपूर्णांक64_t rx_xor:1;
		uपूर्णांक64_t tx_oe:1;
#अन्यथा
		uपूर्णांक64_t tx_oe:1;
		uपूर्णांक64_t rx_xor:1;
		uपूर्णांक64_t पूर्णांक_en:1;
		uपूर्णांक64_t पूर्णांक_type:1;
		uपूर्णांक64_t fil_cnt:4;
		uपूर्णांक64_t fil_sel:4;
		uपूर्णांक64_t clk_sel:2;
		uपूर्णांक64_t clk_gen:1;
		uपूर्णांक64_t synce_sel:2;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gpio_xbit_cfgx_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t fil_sel:4;
		uपूर्णांक64_t fil_cnt:4;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t rx_xor:1;
		uपूर्णांक64_t tx_oe:1;
#अन्यथा
		uपूर्णांक64_t tx_oe:1;
		uपूर्णांक64_t rx_xor:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t fil_cnt:4;
		uपूर्णांक64_t fil_sel:4;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

#पूर्ण_अगर
