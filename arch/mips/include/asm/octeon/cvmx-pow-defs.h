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

#अगर_अघोषित __CVMX_POW_DEFS_H__
#घोषणा __CVMX_POW_DEFS_H__

#घोषणा CVMX_POW_BIST_STAT (CVMX_ADD_IO_SEG(0x00016700000003F8ull))
#घोषणा CVMX_POW_DS_PC (CVMX_ADD_IO_SEG(0x0001670000000398ull))
#घोषणा CVMX_POW_ECC_ERR (CVMX_ADD_IO_SEG(0x0001670000000218ull))
#घोषणा CVMX_POW_INT_CTL (CVMX_ADD_IO_SEG(0x0001670000000220ull))
#घोषणा CVMX_POW_IQ_CNTX(offset) (CVMX_ADD_IO_SEG(0x0001670000000340ull) + ((offset) & 7) * 8)
#घोषणा CVMX_POW_IQ_COM_CNT (CVMX_ADD_IO_SEG(0x0001670000000388ull))
#घोषणा CVMX_POW_IQ_INT (CVMX_ADD_IO_SEG(0x0001670000000238ull))
#घोषणा CVMX_POW_IQ_INT_EN (CVMX_ADD_IO_SEG(0x0001670000000240ull))
#घोषणा CVMX_POW_IQ_THRX(offset) (CVMX_ADD_IO_SEG(0x00016700000003A0ull) + ((offset) & 7) * 8)
#घोषणा CVMX_POW_NOS_CNT (CVMX_ADD_IO_SEG(0x0001670000000228ull))
#घोषणा CVMX_POW_NW_TIM (CVMX_ADD_IO_SEG(0x0001670000000210ull))
#घोषणा CVMX_POW_PF_RST_MSK (CVMX_ADD_IO_SEG(0x0001670000000230ull))
#घोषणा CVMX_POW_PP_GRP_MSKX(offset) (CVMX_ADD_IO_SEG(0x0001670000000000ull) + ((offset) & 15) * 8)
#घोषणा CVMX_POW_QOS_RNDX(offset) (CVMX_ADD_IO_SEG(0x00016700000001C0ull) + ((offset) & 7) * 8)
#घोषणा CVMX_POW_QOS_THRX(offset) (CVMX_ADD_IO_SEG(0x0001670000000180ull) + ((offset) & 7) * 8)
#घोषणा CVMX_POW_TS_PC (CVMX_ADD_IO_SEG(0x0001670000000390ull))
#घोषणा CVMX_POW_WA_COM_PC (CVMX_ADD_IO_SEG(0x0001670000000380ull))
#घोषणा CVMX_POW_WA_PCX(offset) (CVMX_ADD_IO_SEG(0x0001670000000300ull) + ((offset) & 7) * 8)
#घोषणा CVMX_POW_WQ_INT (CVMX_ADD_IO_SEG(0x0001670000000200ull))
#घोषणा CVMX_POW_WQ_INT_CNTX(offset) (CVMX_ADD_IO_SEG(0x0001670000000100ull) + ((offset) & 15) * 8)
#घोषणा CVMX_POW_WQ_INT_PC (CVMX_ADD_IO_SEG(0x0001670000000208ull))
#घोषणा CVMX_POW_WQ_INT_THRX(offset) (CVMX_ADD_IO_SEG(0x0001670000000080ull) + ((offset) & 15) * 8)
#घोषणा CVMX_POW_WS_PCX(offset) (CVMX_ADD_IO_SEG(0x0001670000000280ull) + ((offset) & 15) * 8)

#घोषणा CVMX_SSO_WQ_INT (CVMX_ADD_IO_SEG(0x0001670000001000ull))
#घोषणा CVMX_SSO_WQ_IQ_DIS (CVMX_ADD_IO_SEG(0x0001670000001010ull))
#घोषणा CVMX_SSO_WQ_INT_PC (CVMX_ADD_IO_SEG(0x0001670000001020ull))
#घोषणा CVMX_SSO_PPX_GRP_MSK(offset) (CVMX_ADD_IO_SEG(0x0001670000006000ull) + ((offset) & 31) * 8)
#घोषणा CVMX_SSO_WQ_INT_THRX(offset) (CVMX_ADD_IO_SEG(0x0001670000007000ull) + ((offset) & 63) * 8)

जोड़ cvmx_घात_bist_stat अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_bist_stat_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t pp:16;
		uपूर्णांक64_t reserved_0_15:16;
#अन्यथा
		uपूर्णांक64_t reserved_0_15:16;
		uपूर्णांक64_t pp:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_घात_bist_stat_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t pp:1;
		uपूर्णांक64_t reserved_9_15:7;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t nbt1:1;
		uपूर्णांक64_t nbt0:1;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t nbr1:1;
		uपूर्णांक64_t nbr0:1;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t adr:1;
#अन्यथा
		uपूर्णांक64_t adr:1;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t nbr0:1;
		uपूर्णांक64_t nbr1:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t nbt0:1;
		uपूर्णांक64_t nbt1:1;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t reserved_9_15:7;
		uपूर्णांक64_t pp:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_घात_bist_stat_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t pp:2;
		uपूर्णांक64_t reserved_9_15:7;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t nbt1:1;
		uपूर्णांक64_t nbt0:1;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t nbr1:1;
		uपूर्णांक64_t nbr0:1;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t adr:1;
#अन्यथा
		uपूर्णांक64_t adr:1;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t nbr0:1;
		uपूर्णांक64_t nbr1:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t nbt0:1;
		uपूर्णांक64_t nbt1:1;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t reserved_9_15:7;
		uपूर्णांक64_t pp:2;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_घात_bist_stat_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t pp:16;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t nbt:1;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t nbr1:1;
		uपूर्णांक64_t nbr0:1;
		uपूर्णांक64_t pend1:1;
		uपूर्णांक64_t pend0:1;
		uपूर्णांक64_t adr1:1;
		uपूर्णांक64_t adr0:1;
#अन्यथा
		uपूर्णांक64_t adr0:1;
		uपूर्णांक64_t adr1:1;
		uपूर्णांक64_t pend0:1;
		uपूर्णांक64_t pend1:1;
		uपूर्णांक64_t nbr0:1;
		uपूर्णांक64_t nbr1:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t nbt:1;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t pp:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_घात_bist_stat_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t pp:4;
		uपूर्णांक64_t reserved_9_15:7;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t nbt1:1;
		uपूर्णांक64_t nbt0:1;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t nbr1:1;
		uपूर्णांक64_t nbr0:1;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t adr:1;
#अन्यथा
		uपूर्णांक64_t adr:1;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t nbr0:1;
		uपूर्णांक64_t nbr1:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t nbt0:1;
		uपूर्णांक64_t nbt1:1;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t reserved_9_15:7;
		uपूर्णांक64_t pp:4;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_घात_bist_stat_cn56xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t pp:12;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t nbt:1;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t nbr1:1;
		uपूर्णांक64_t nbr0:1;
		uपूर्णांक64_t pend1:1;
		uपूर्णांक64_t pend0:1;
		uपूर्णांक64_t adr1:1;
		uपूर्णांक64_t adr0:1;
#अन्यथा
		uपूर्णांक64_t adr0:1;
		uपूर्णांक64_t adr1:1;
		uपूर्णांक64_t pend0:1;
		uपूर्णांक64_t pend1:1;
		uपूर्णांक64_t nbr0:1;
		uपूर्णांक64_t nbr1:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t nbt:1;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t pp:12;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण cn56xx;
	काष्ठा cvmx_घात_bist_stat_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t pp:4;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t nbr:3;
		uपूर्णांक64_t nbt:4;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t adr:1;
#अन्यथा
		uपूर्णांक64_t adr:1;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t nbt:4;
		uपूर्णांक64_t nbr:3;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t pp:4;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_घात_bist_stat_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_22_63:42;
		uपूर्णांक64_t pp:6;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t nbr:3;
		uपूर्णांक64_t nbt:4;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t adr:1;
#अन्यथा
		uपूर्णांक64_t adr:1;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t nbt:4;
		uपूर्णांक64_t nbr:3;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t pp:6;
		uपूर्णांक64_t reserved_22_63:42;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_घात_bist_stat_cn66xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_26_63:38;
		uपूर्णांक64_t pp:10;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t nbr:3;
		uपूर्णांक64_t nbt:4;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t adr:1;
#अन्यथा
		uपूर्णांक64_t adr:1;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t fidx:1;
		uपूर्णांक64_t index:1;
		uपूर्णांक64_t nbt:4;
		uपूर्णांक64_t nbr:3;
		uपूर्णांक64_t cam:1;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t pp:10;
		uपूर्णांक64_t reserved_26_63:38;
#पूर्ण_अगर
	पूर्ण cn66xx;
पूर्ण;

जोड़ cvmx_घात_ds_pc अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_ds_pc_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t ds_pc:32;
#अन्यथा
		uपूर्णांक64_t ds_pc:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_ecc_err अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_ecc_err_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_45_63:19;
		uपूर्णांक64_t iop_ie:13;
		uपूर्णांक64_t reserved_29_31:3;
		uपूर्णांक64_t iop:13;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t rpe_ie:1;
		uपूर्णांक64_t rpe:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t syn:5;
		uपूर्णांक64_t dbe_ie:1;
		uपूर्णांक64_t sbe_ie:1;
		uपूर्णांक64_t dbe:1;
		uपूर्णांक64_t sbe:1;
#अन्यथा
		uपूर्णांक64_t sbe:1;
		uपूर्णांक64_t dbe:1;
		uपूर्णांक64_t sbe_ie:1;
		uपूर्णांक64_t dbe_ie:1;
		uपूर्णांक64_t syn:5;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t rpe:1;
		uपूर्णांक64_t rpe_ie:1;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t iop:13;
		uपूर्णांक64_t reserved_29_31:3;
		uपूर्णांक64_t iop_ie:13;
		uपूर्णांक64_t reserved_45_63:19;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_घात_ecc_err_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t rpe_ie:1;
		uपूर्णांक64_t rpe:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t syn:5;
		uपूर्णांक64_t dbe_ie:1;
		uपूर्णांक64_t sbe_ie:1;
		uपूर्णांक64_t dbe:1;
		uपूर्णांक64_t sbe:1;
#अन्यथा
		uपूर्णांक64_t sbe:1;
		uपूर्णांक64_t dbe:1;
		uपूर्णांक64_t sbe_ie:1;
		uपूर्णांक64_t dbe_ie:1;
		uपूर्णांक64_t syn:5;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t rpe:1;
		uपूर्णांक64_t rpe_ie:1;
		uपूर्णांक64_t reserved_14_63:50;
#पूर्ण_अगर
	पूर्ण cn31xx;
पूर्ण;

जोड़ cvmx_घात_पूर्णांक_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_पूर्णांक_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t pfr_dis:1;
		uपूर्णांक64_t nbr_thr:5;
#अन्यथा
		uपूर्णांक64_t nbr_thr:5;
		uपूर्णांक64_t pfr_dis:1;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_iq_cntx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_iq_cntx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t iq_cnt:32;
#अन्यथा
		uपूर्णांक64_t iq_cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_iq_com_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_iq_com_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t iq_cnt:32;
#अन्यथा
		uपूर्णांक64_t iq_cnt:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_iq_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_iq_पूर्णांक_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t iq_पूर्णांक:8;
#अन्यथा
		uपूर्णांक64_t iq_पूर्णांक:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_iq_पूर्णांक_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_iq_पूर्णांक_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t पूर्णांक_en:8;
#अन्यथा
		uपूर्णांक64_t पूर्णांक_en:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_iq_thrx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_iq_thrx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t iq_thr:32;
#अन्यथा
		uपूर्णांक64_t iq_thr:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_nos_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_nos_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t nos_cnt:12;
#अन्यथा
		uपूर्णांक64_t nos_cnt:12;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_घात_nos_cnt_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t nos_cnt:7;
#अन्यथा
		uपूर्णांक64_t nos_cnt:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_घात_nos_cnt_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t nos_cnt:9;
#अन्यथा
		uपूर्णांक64_t nos_cnt:9;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_घात_nos_cnt_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t nos_cnt:10;
#अन्यथा
		uपूर्णांक64_t nos_cnt:10;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_घात_nos_cnt_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t nos_cnt:11;
#अन्यथा
		uपूर्णांक64_t nos_cnt:11;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_घात_nw_tim अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_nw_tim_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t nw_tim:10;
#अन्यथा
		uपूर्णांक64_t nw_tim:10;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_pf_rst_msk अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_pf_rst_msk_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t rst_msk:8;
#अन्यथा
		uपूर्णांक64_t rst_msk:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_pp_grp_mskx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_pp_grp_mskx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t qos7_pri:4;
		uपूर्णांक64_t qos6_pri:4;
		uपूर्णांक64_t qos5_pri:4;
		uपूर्णांक64_t qos4_pri:4;
		uपूर्णांक64_t qos3_pri:4;
		uपूर्णांक64_t qos2_pri:4;
		uपूर्णांक64_t qos1_pri:4;
		uपूर्णांक64_t qos0_pri:4;
		uपूर्णांक64_t grp_msk:16;
#अन्यथा
		uपूर्णांक64_t grp_msk:16;
		uपूर्णांक64_t qos0_pri:4;
		uपूर्णांक64_t qos1_pri:4;
		uपूर्णांक64_t qos2_pri:4;
		uपूर्णांक64_t qos3_pri:4;
		uपूर्णांक64_t qos4_pri:4;
		uपूर्णांक64_t qos5_pri:4;
		uपूर्णांक64_t qos6_pri:4;
		uपूर्णांक64_t qos7_pri:4;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_घात_pp_grp_mskx_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t grp_msk:16;
#अन्यथा
		uपूर्णांक64_t grp_msk:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_घात_qos_rndx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_qos_rndx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t rnd_p3:8;
		uपूर्णांक64_t rnd_p2:8;
		uपूर्णांक64_t rnd_p1:8;
		uपूर्णांक64_t rnd:8;
#अन्यथा
		uपूर्णांक64_t rnd:8;
		uपूर्णांक64_t rnd_p1:8;
		uपूर्णांक64_t rnd_p2:8;
		uपूर्णांक64_t rnd_p3:8;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_qos_thrx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_qos_thrx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_60_63:4;
		uपूर्णांक64_t des_cnt:12;
		uपूर्णांक64_t buf_cnt:12;
		uपूर्णांक64_t मुक्त_cnt:12;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t max_thr:11;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t min_thr:11;
#अन्यथा
		uपूर्णांक64_t min_thr:11;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t max_thr:11;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t मुक्त_cnt:12;
		uपूर्णांक64_t buf_cnt:12;
		uपूर्णांक64_t des_cnt:12;
		uपूर्णांक64_t reserved_60_63:4;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_घात_qos_thrx_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_55_63:9;
		uपूर्णांक64_t des_cnt:7;
		uपूर्णांक64_t reserved_43_47:5;
		uपूर्णांक64_t buf_cnt:7;
		uपूर्णांक64_t reserved_31_35:5;
		uपूर्णांक64_t मुक्त_cnt:7;
		uपूर्णांक64_t reserved_18_23:6;
		uपूर्णांक64_t max_thr:6;
		uपूर्णांक64_t reserved_6_11:6;
		uपूर्णांक64_t min_thr:6;
#अन्यथा
		uपूर्णांक64_t min_thr:6;
		uपूर्णांक64_t reserved_6_11:6;
		uपूर्णांक64_t max_thr:6;
		uपूर्णांक64_t reserved_18_23:6;
		uपूर्णांक64_t मुक्त_cnt:7;
		uपूर्णांक64_t reserved_31_35:5;
		uपूर्णांक64_t buf_cnt:7;
		uपूर्णांक64_t reserved_43_47:5;
		uपूर्णांक64_t des_cnt:7;
		uपूर्णांक64_t reserved_55_63:9;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_घात_qos_thrx_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_57_63:7;
		uपूर्णांक64_t des_cnt:9;
		uपूर्णांक64_t reserved_45_47:3;
		uपूर्णांक64_t buf_cnt:9;
		uपूर्णांक64_t reserved_33_35:3;
		uपूर्णांक64_t मुक्त_cnt:9;
		uपूर्णांक64_t reserved_20_23:4;
		uपूर्णांक64_t max_thr:8;
		uपूर्णांक64_t reserved_8_11:4;
		uपूर्णांक64_t min_thr:8;
#अन्यथा
		uपूर्णांक64_t min_thr:8;
		uपूर्णांक64_t reserved_8_11:4;
		uपूर्णांक64_t max_thr:8;
		uपूर्णांक64_t reserved_20_23:4;
		uपूर्णांक64_t मुक्त_cnt:9;
		uपूर्णांक64_t reserved_33_35:3;
		uपूर्णांक64_t buf_cnt:9;
		uपूर्णांक64_t reserved_45_47:3;
		uपूर्णांक64_t des_cnt:9;
		uपूर्णांक64_t reserved_57_63:7;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_घात_qos_thrx_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_58_63:6;
		uपूर्णांक64_t des_cnt:10;
		uपूर्णांक64_t reserved_46_47:2;
		uपूर्णांक64_t buf_cnt:10;
		uपूर्णांक64_t reserved_34_35:2;
		uपूर्णांक64_t मुक्त_cnt:10;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t max_thr:9;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t min_thr:9;
#अन्यथा
		uपूर्णांक64_t min_thr:9;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t max_thr:9;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t मुक्त_cnt:10;
		uपूर्णांक64_t reserved_34_35:2;
		uपूर्णांक64_t buf_cnt:10;
		uपूर्णांक64_t reserved_46_47:2;
		uपूर्णांक64_t des_cnt:10;
		uपूर्णांक64_t reserved_58_63:6;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_घात_qos_thrx_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_59_63:5;
		uपूर्णांक64_t des_cnt:11;
		uपूर्णांक64_t reserved_47_47:1;
		uपूर्णांक64_t buf_cnt:11;
		uपूर्णांक64_t reserved_35_35:1;
		uपूर्णांक64_t मुक्त_cnt:11;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t max_thr:10;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t min_thr:10;
#अन्यथा
		uपूर्णांक64_t min_thr:10;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t max_thr:10;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t मुक्त_cnt:11;
		uपूर्णांक64_t reserved_35_35:1;
		uपूर्णांक64_t buf_cnt:11;
		uपूर्णांक64_t reserved_47_47:1;
		uपूर्णांक64_t des_cnt:11;
		uपूर्णांक64_t reserved_59_63:5;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_घात_ts_pc अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_ts_pc_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t ts_pc:32;
#अन्यथा
		uपूर्णांक64_t ts_pc:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_wa_com_pc अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_wa_com_pc_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t wa_pc:32;
#अन्यथा
		uपूर्णांक64_t wa_pc:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_wa_pcx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_wa_pcx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t wa_pc:32;
#अन्यथा
		uपूर्णांक64_t wa_pc:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_wq_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_wq_पूर्णांक_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t iq_dis:16;
		uपूर्णांक64_t wq_पूर्णांक:16;
#अन्यथा
		uपूर्णांक64_t wq_पूर्णांक:16;
		uपूर्णांक64_t iq_dis:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_wq_पूर्णांक_cntx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_wq_पूर्णांक_cntx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t tc_cnt:4;
		uपूर्णांक64_t ds_cnt:12;
		uपूर्णांक64_t iq_cnt:12;
#अन्यथा
		uपूर्णांक64_t iq_cnt:12;
		uपूर्णांक64_t ds_cnt:12;
		uपूर्णांक64_t tc_cnt:4;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_घात_wq_पूर्णांक_cntx_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t tc_cnt:4;
		uपूर्णांक64_t reserved_19_23:5;
		uपूर्णांक64_t ds_cnt:7;
		uपूर्णांक64_t reserved_7_11:5;
		uपूर्णांक64_t iq_cnt:7;
#अन्यथा
		uपूर्णांक64_t iq_cnt:7;
		uपूर्णांक64_t reserved_7_11:5;
		uपूर्णांक64_t ds_cnt:7;
		uपूर्णांक64_t reserved_19_23:5;
		uपूर्णांक64_t tc_cnt:4;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_घात_wq_पूर्णांक_cntx_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t tc_cnt:4;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t ds_cnt:9;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t iq_cnt:9;
#अन्यथा
		uपूर्णांक64_t iq_cnt:9;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t ds_cnt:9;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t tc_cnt:4;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_घात_wq_पूर्णांक_cntx_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t tc_cnt:4;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t ds_cnt:10;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t iq_cnt:10;
#अन्यथा
		uपूर्णांक64_t iq_cnt:10;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t ds_cnt:10;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t tc_cnt:4;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_घात_wq_पूर्णांक_cntx_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t tc_cnt:4;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t ds_cnt:11;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t iq_cnt:11;
#अन्यथा
		uपूर्णांक64_t iq_cnt:11;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t ds_cnt:11;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t tc_cnt:4;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_घात_wq_पूर्णांक_pc अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_wq_पूर्णांक_pc_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_60_63:4;
		uपूर्णांक64_t pc:28;
		uपूर्णांक64_t reserved_28_31:4;
		uपूर्णांक64_t pc_thr:20;
		uपूर्णांक64_t reserved_0_7:8;
#अन्यथा
		uपूर्णांक64_t reserved_0_7:8;
		uपूर्णांक64_t pc_thr:20;
		uपूर्णांक64_t reserved_28_31:4;
		uपूर्णांक64_t pc:28;
		uपूर्णांक64_t reserved_60_63:4;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_घात_wq_पूर्णांक_thrx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_wq_पूर्णांक_thrx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t ds_thr:11;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t iq_thr:11;
#अन्यथा
		uपूर्णांक64_t iq_thr:11;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t ds_thr:11;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_घात_wq_पूर्णांक_thrx_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t reserved_18_23:6;
		uपूर्णांक64_t ds_thr:6;
		uपूर्णांक64_t reserved_6_11:6;
		uपूर्णांक64_t iq_thr:6;
#अन्यथा
		uपूर्णांक64_t iq_thr:6;
		uपूर्णांक64_t reserved_6_11:6;
		uपूर्णांक64_t ds_thr:6;
		uपूर्णांक64_t reserved_18_23:6;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_घात_wq_पूर्णांक_thrx_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t reserved_20_23:4;
		uपूर्णांक64_t ds_thr:8;
		uपूर्णांक64_t reserved_8_11:4;
		uपूर्णांक64_t iq_thr:8;
#अन्यथा
		uपूर्णांक64_t iq_thr:8;
		uपूर्णांक64_t reserved_8_11:4;
		uपूर्णांक64_t ds_thr:8;
		uपूर्णांक64_t reserved_20_23:4;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_घात_wq_पूर्णांक_thrx_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t ds_thr:9;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t iq_thr:9;
#अन्यथा
		uपूर्णांक64_t iq_thr:9;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t ds_thr:9;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_घात_wq_पूर्णांक_thrx_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t ds_thr:10;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t iq_thr:10;
#अन्यथा
		uपूर्णांक64_t iq_thr:10;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t ds_thr:10;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_घात_ws_pcx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_घात_ws_pcx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t ws_pc:32;
#अन्यथा
		uपूर्णांक64_t ws_pc:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sso_wq_पूर्णांक_thrx अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_33_63:31;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t reserved_26_27:2;
		uपूर्णांक64_t ds_thr:12;
		uपूर्णांक64_t reserved_12_13:2;
		uपूर्णांक64_t iq_thr:12;
#अन्यथा
		uपूर्णांक64_t iq_thr:12;
		uपूर्णांक64_t reserved_12_13:2;
		uपूर्णांक64_t ds_thr:12;
		uपूर्णांक64_t reserved_26_27:2;
		uपूर्णांक64_t tc_thr:4;
		uपूर्णांक64_t tc_en:1;
		uपूर्णांक64_t reserved_33_63:31;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
