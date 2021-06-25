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

#अगर_अघोषित __CVMX_SPXX_DEFS_H__
#घोषणा __CVMX_SPXX_DEFS_H__

#घोषणा CVMX_SPXX_BCKPRS_CNT(block_id) (CVMX_ADD_IO_SEG(0x0001180090000340ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_BIST_STAT(block_id) (CVMX_ADD_IO_SEG(0x00011800900007F8ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_CLK_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180090000348ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_CLK_STAT(block_id) (CVMX_ADD_IO_SEG(0x0001180090000350ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_DBG_DESKEW_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180090000368ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_DBG_DESKEW_STATE(block_id) (CVMX_ADD_IO_SEG(0x0001180090000370ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_DRV_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180090000358ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_ERR_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180090000320ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_INT_DAT(block_id) (CVMX_ADD_IO_SEG(0x0001180090000318ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_INT_MSK(block_id) (CVMX_ADD_IO_SEG(0x0001180090000308ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_INT_REG(block_id) (CVMX_ADD_IO_SEG(0x0001180090000300ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_INT_SYNC(block_id) (CVMX_ADD_IO_SEG(0x0001180090000310ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_TPA_ACC(block_id) (CVMX_ADD_IO_SEG(0x0001180090000338ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_TPA_MAX(block_id) (CVMX_ADD_IO_SEG(0x0001180090000330ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_TPA_SEL(block_id) (CVMX_ADD_IO_SEG(0x0001180090000328ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_SPXX_TRN4_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180090000360ull) + ((block_id) & 1) * 0x8000000ull)

व्योम __cvmx_पूर्णांकerrupt_spxx_पूर्णांक_msk_enable(पूर्णांक index);

जोड़ cvmx_spxx_bckprs_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_bckprs_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_bist_stat अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_bist_stat_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t stat2:1;
		uपूर्णांक64_t stat1:1;
		uपूर्णांक64_t stat0:1;
#अन्यथा
		uपूर्णांक64_t stat0:1;
		uपूर्णांक64_t stat1:1;
		uपूर्णांक64_t stat2:1;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_clk_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_clk_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t seetrn:1;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t clkdly:5;
		uपूर्णांक64_t runbist:1;
		uपूर्णांक64_t statdrv:1;
		uपूर्णांक64_t statrcv:1;
		uपूर्णांक64_t sndtrn:1;
		uपूर्णांक64_t drptrn:1;
		uपूर्णांक64_t rcvtrn:1;
		uपूर्णांक64_t srxdlck:1;
#अन्यथा
		uपूर्णांक64_t srxdlck:1;
		uपूर्णांक64_t rcvtrn:1;
		uपूर्णांक64_t drptrn:1;
		uपूर्णांक64_t sndtrn:1;
		uपूर्णांक64_t statrcv:1;
		uपूर्णांक64_t statdrv:1;
		uपूर्णांक64_t runbist:1;
		uपूर्णांक64_t clkdly:5;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t seetrn:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_clk_stat अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_clk_stat_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t stxcal:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t srxtrn:1;
		uपूर्णांक64_t s4clk1:1;
		uपूर्णांक64_t s4clk0:1;
		uपूर्णांक64_t d4clk1:1;
		uपूर्णांक64_t d4clk0:1;
		uपूर्णांक64_t reserved_0_3:4;
#अन्यथा
		uपूर्णांक64_t reserved_0_3:4;
		uपूर्णांक64_t d4clk0:1;
		uपूर्णांक64_t d4clk1:1;
		uपूर्णांक64_t s4clk0:1;
		uपूर्णांक64_t s4clk1:1;
		uपूर्णांक64_t srxtrn:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t stxcal:1;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_dbg_deskew_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_dbg_deskew_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_30_63:34;
		uपूर्णांक64_t fallnop:1;
		uपूर्णांक64_t fall8:1;
		uपूर्णांक64_t reserved_26_27:2;
		uपूर्णांक64_t sstep_go:1;
		uपूर्णांक64_t sstep:1;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t clrdly:1;
		uपूर्णांक64_t dec:1;
		uपूर्णांक64_t inc:1;
		uपूर्णांक64_t mux:1;
		uपूर्णांक64_t offset:5;
		uपूर्णांक64_t bitsel:5;
		uपूर्णांक64_t offdly:6;
		uपूर्णांक64_t dllfrc:1;
		uपूर्णांक64_t dlldis:1;
#अन्यथा
		uपूर्णांक64_t dlldis:1;
		uपूर्णांक64_t dllfrc:1;
		uपूर्णांक64_t offdly:6;
		uपूर्णांक64_t bitsel:5;
		uपूर्णांक64_t offset:5;
		uपूर्णांक64_t mux:1;
		uपूर्णांक64_t inc:1;
		uपूर्णांक64_t dec:1;
		uपूर्णांक64_t clrdly:1;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t sstep:1;
		uपूर्णांक64_t sstep_go:1;
		uपूर्णांक64_t reserved_26_27:2;
		uपूर्णांक64_t fall8:1;
		uपूर्णांक64_t fallnop:1;
		uपूर्णांक64_t reserved_30_63:34;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_dbg_deskew_state अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_dbg_deskew_state_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t testres:1;
		uपूर्णांक64_t unxterm:1;
		uपूर्णांक64_t muxsel:2;
		uपूर्णांक64_t offset:5;
#अन्यथा
		uपूर्णांक64_t offset:5;
		uपूर्णांक64_t muxsel:2;
		uपूर्णांक64_t unxterm:1;
		uपूर्णांक64_t testres:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_drv_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_drv_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_spxx_drv_ctl_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t stx4ncmp:4;
		uपूर्णांक64_t stx4pcmp:4;
		uपूर्णांक64_t srx4cmp:8;
#अन्यथा
		uपूर्णांक64_t srx4cmp:8;
		uपूर्णांक64_t stx4pcmp:4;
		uपूर्णांक64_t stx4ncmp:4;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_spxx_drv_ctl_cn58xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t stx4ncmp:4;
		uपूर्णांक64_t stx4pcmp:4;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t srx4cmp:10;
#अन्यथा
		uपूर्णांक64_t srx4cmp:10;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t stx4pcmp:4;
		uपूर्णांक64_t stx4ncmp:4;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण cn58xx;
पूर्ण;

जोड़ cvmx_spxx_err_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_err_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t dipcls:1;
		uपूर्णांक64_t dippay:1;
		uपूर्णांक64_t reserved_4_5:2;
		uपूर्णांक64_t errcnt:4;
#अन्यथा
		uपूर्णांक64_t errcnt:4;
		uपूर्णांक64_t reserved_4_5:2;
		uपूर्णांक64_t dippay:1;
		uपूर्णांक64_t dipcls:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_पूर्णांक_dat अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_पूर्णांक_dat_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t mul:1;
		uपूर्णांक64_t reserved_14_30:17;
		uपूर्णांक64_t calbnk:2;
		uपूर्णांक64_t rsvop:4;
		uपूर्णांक64_t prt:8;
#अन्यथा
		uपूर्णांक64_t prt:8;
		uपूर्णांक64_t rsvop:4;
		uपूर्णांक64_t calbnk:2;
		uपूर्णांक64_t reserved_14_30:17;
		uपूर्णांक64_t mul:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_पूर्णांक_msk अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_पूर्णांक_msk_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t calerr:1;
		uपूर्णांक64_t syncerr:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t tpaovr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t drwnng:1;
		uपूर्णांक64_t clserr:1;
		uपूर्णांक64_t spiovr:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t abnorm:1;
		uपूर्णांक64_t prtnxa:1;
#अन्यथा
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t abnorm:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t spiovr:1;
		uपूर्णांक64_t clserr:1;
		uपूर्णांक64_t drwnng:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t tpaovr:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t syncerr:1;
		uपूर्णांक64_t calerr:1;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_पूर्णांक_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t spf:1;
		uपूर्णांक64_t reserved_12_30:19;
		uपूर्णांक64_t calerr:1;
		uपूर्णांक64_t syncerr:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t tpaovr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t drwnng:1;
		uपूर्णांक64_t clserr:1;
		uपूर्णांक64_t spiovr:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t abnorm:1;
		uपूर्णांक64_t prtnxa:1;
#अन्यथा
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t abnorm:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t spiovr:1;
		uपूर्णांक64_t clserr:1;
		uपूर्णांक64_t drwnng:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t tpaovr:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t syncerr:1;
		uपूर्णांक64_t calerr:1;
		uपूर्णांक64_t reserved_12_30:19;
		uपूर्णांक64_t spf:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_पूर्णांक_sync अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_पूर्णांक_sync_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t calerr:1;
		uपूर्णांक64_t syncerr:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t tpaovr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t drwnng:1;
		uपूर्णांक64_t clserr:1;
		uपूर्णांक64_t spiovr:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t abnorm:1;
		uपूर्णांक64_t prtnxa:1;
#अन्यथा
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t abnorm:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t spiovr:1;
		uपूर्णांक64_t clserr:1;
		uपूर्णांक64_t drwnng:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t tpaovr:1;
		uपूर्णांक64_t diperr:1;
		uपूर्णांक64_t syncerr:1;
		uपूर्णांक64_t calerr:1;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_tpa_acc अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_tpa_acc_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t cnt:32;
#अन्यथा
		uपूर्णांक64_t cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_tpa_max अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_tpa_max_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t max:32;
#अन्यथा
		uपूर्णांक64_t max:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_tpa_sel अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_tpa_sel_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t prtsel:4;
#अन्यथा
		uपूर्णांक64_t prtsel:4;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_spxx_trn4_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_spxx_trn4_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t trntest:1;
		uपूर्णांक64_t jitter:3;
		uपूर्णांक64_t clr_boot:1;
		uपूर्णांक64_t set_boot:1;
		uपूर्णांक64_t maxdist:5;
		uपूर्णांक64_t macro_en:1;
		uपूर्णांक64_t mux_en:1;
#अन्यथा
		uपूर्णांक64_t mux_en:1;
		uपूर्णांक64_t macro_en:1;
		uपूर्णांक64_t maxdist:5;
		uपूर्णांक64_t set_boot:1;
		uपूर्णांक64_t clr_boot:1;
		uपूर्णांक64_t jitter:3;
		uपूर्णांक64_t trntest:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
