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

#अगर_अघोषित __CVMX_MIXX_DEFS_H__
#घोषणा __CVMX_MIXX_DEFS_H__

#घोषणा CVMX_MIXX_BIST(offset) (CVMX_ADD_IO_SEG(0x0001070000100078ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_MIXX_CTL(offset) (CVMX_ADD_IO_SEG(0x0001070000100020ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_MIXX_INTENA(offset) (CVMX_ADD_IO_SEG(0x0001070000100050ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_MIXX_IRCNT(offset) (CVMX_ADD_IO_SEG(0x0001070000100030ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_MIXX_IRHWM(offset) (CVMX_ADD_IO_SEG(0x0001070000100028ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_MIXX_IRING1(offset) (CVMX_ADD_IO_SEG(0x0001070000100010ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_MIXX_IRING2(offset) (CVMX_ADD_IO_SEG(0x0001070000100018ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_MIXX_ISR(offset) (CVMX_ADD_IO_SEG(0x0001070000100048ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_MIXX_ORCNT(offset) (CVMX_ADD_IO_SEG(0x0001070000100040ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_MIXX_ORHWM(offset) (CVMX_ADD_IO_SEG(0x0001070000100038ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_MIXX_ORING1(offset) (CVMX_ADD_IO_SEG(0x0001070000100000ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_MIXX_ORING2(offset) (CVMX_ADD_IO_SEG(0x0001070000100008ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_MIXX_REMCNT(offset) (CVMX_ADD_IO_SEG(0x0001070000100058ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_MIXX_TSCTL(offset) (CVMX_ADD_IO_SEG(0x0001070000100068ull) + ((offset) & 1) * 2048)
#घोषणा CVMX_MIXX_TSTAMP(offset) (CVMX_ADD_IO_SEG(0x0001070000100060ull) + ((offset) & 1) * 2048)

जोड़ cvmx_mixx_bist अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_bist_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t opfdat:1;
		uपूर्णांक64_t mrgdat:1;
		uपूर्णांक64_t mrqdat:1;
		uपूर्णांक64_t ipfdat:1;
		uपूर्णांक64_t irfdat:1;
		uपूर्णांक64_t orfdat:1;
#अन्यथा
		uपूर्णांक64_t orfdat:1;
		uपूर्णांक64_t irfdat:1;
		uपूर्णांक64_t ipfdat:1;
		uपूर्णांक64_t mrqdat:1;
		uपूर्णांक64_t mrgdat:1;
		uपूर्णांक64_t opfdat:1;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mixx_bist_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t mrqdat:1;
		uपूर्णांक64_t ipfdat:1;
		uपूर्णांक64_t irfdat:1;
		uपूर्णांक64_t orfdat:1;
#अन्यथा
		uपूर्णांक64_t orfdat:1;
		uपूर्णांक64_t irfdat:1;
		uपूर्णांक64_t ipfdat:1;
		uपूर्णांक64_t mrqdat:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_mixx_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t ts_thresh:4;
		uपूर्णांक64_t crc_strip:1;
		uपूर्णांक64_t busy:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t lendian:1;
		uपूर्णांक64_t nbtarb:1;
		uपूर्णांक64_t mrq_hwm:2;
#अन्यथा
		uपूर्णांक64_t mrq_hwm:2;
		uपूर्णांक64_t nbtarb:1;
		uपूर्णांक64_t lendian:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t busy:1;
		uपूर्णांक64_t crc_strip:1;
		uपूर्णांक64_t ts_thresh:4;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mixx_ctl_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t crc_strip:1;
		uपूर्णांक64_t busy:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t lendian:1;
		uपूर्णांक64_t nbtarb:1;
		uपूर्णांक64_t mrq_hwm:2;
#अन्यथा
		uपूर्णांक64_t mrq_hwm:2;
		uपूर्णांक64_t nbtarb:1;
		uपूर्णांक64_t lendian:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t busy:1;
		uपूर्णांक64_t crc_strip:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_mixx_पूर्णांकena अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_पूर्णांकena_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t tsena:1;
		uपूर्णांक64_t orunena:1;
		uपूर्णांक64_t irunena:1;
		uपूर्णांक64_t data_drpena:1;
		uपूर्णांक64_t ithena:1;
		uपूर्णांक64_t othena:1;
		uपूर्णांक64_t ivfena:1;
		uपूर्णांक64_t ovfena:1;
#अन्यथा
		uपूर्णांक64_t ovfena:1;
		uपूर्णांक64_t ivfena:1;
		uपूर्णांक64_t othena:1;
		uपूर्णांक64_t ithena:1;
		uपूर्णांक64_t data_drpena:1;
		uपूर्णांक64_t irunena:1;
		uपूर्णांक64_t orunena:1;
		uपूर्णांक64_t tsena:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mixx_पूर्णांकena_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t orunena:1;
		uपूर्णांक64_t irunena:1;
		uपूर्णांक64_t data_drpena:1;
		uपूर्णांक64_t ithena:1;
		uपूर्णांक64_t othena:1;
		uपूर्णांक64_t ivfena:1;
		uपूर्णांक64_t ovfena:1;
#अन्यथा
		uपूर्णांक64_t ovfena:1;
		uपूर्णांक64_t ivfena:1;
		uपूर्णांक64_t othena:1;
		uपूर्णांक64_t ithena:1;
		uपूर्णांक64_t data_drpena:1;
		uपूर्णांक64_t irunena:1;
		uपूर्णांक64_t orunena:1;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_mixx_ircnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_ircnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t ircnt:20;
#अन्यथा
		uपूर्णांक64_t ircnt:20;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mixx_irhwm अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_irhwm_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t ibplwm:20;
		uपूर्णांक64_t irhwm:20;
#अन्यथा
		uपूर्णांक64_t irhwm:20;
		uपूर्णांक64_t ibplwm:20;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mixx_iring1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_iring1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_60_63:4;
		uपूर्णांक64_t isize:20;
		uपूर्णांक64_t ibase:37;
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t ibase:37;
		uपूर्णांक64_t isize:20;
		uपूर्णांक64_t reserved_60_63:4;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mixx_iring1_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_60_63:4;
		uपूर्णांक64_t isize:20;
		uपूर्णांक64_t reserved_36_39:4;
		uपूर्णांक64_t ibase:33;
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t ibase:33;
		uपूर्णांक64_t reserved_36_39:4;
		uपूर्णांक64_t isize:20;
		uपूर्णांक64_t reserved_60_63:4;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_mixx_iring2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_iring2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_52_63:12;
		uपूर्णांक64_t itlptr:20;
		uपूर्णांक64_t reserved_20_31:12;
		uपूर्णांक64_t idbell:20;
#अन्यथा
		uपूर्णांक64_t idbell:20;
		uपूर्णांक64_t reserved_20_31:12;
		uपूर्णांक64_t itlptr:20;
		uपूर्णांक64_t reserved_52_63:12;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mixx_isr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_isr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t ts:1;
		uपूर्णांक64_t orun:1;
		uपूर्णांक64_t irun:1;
		uपूर्णांक64_t data_drp:1;
		uपूर्णांक64_t irthresh:1;
		uपूर्णांक64_t orthresh:1;
		uपूर्णांक64_t idblovf:1;
		uपूर्णांक64_t odblovf:1;
#अन्यथा
		uपूर्णांक64_t odblovf:1;
		uपूर्णांक64_t idblovf:1;
		uपूर्णांक64_t orthresh:1;
		uपूर्णांक64_t irthresh:1;
		uपूर्णांक64_t data_drp:1;
		uपूर्णांक64_t irun:1;
		uपूर्णांक64_t orun:1;
		uपूर्णांक64_t ts:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mixx_isr_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t orun:1;
		uपूर्णांक64_t irun:1;
		uपूर्णांक64_t data_drp:1;
		uपूर्णांक64_t irthresh:1;
		uपूर्णांक64_t orthresh:1;
		uपूर्णांक64_t idblovf:1;
		uपूर्णांक64_t odblovf:1;
#अन्यथा
		uपूर्णांक64_t odblovf:1;
		uपूर्णांक64_t idblovf:1;
		uपूर्णांक64_t orthresh:1;
		uपूर्णांक64_t irthresh:1;
		uपूर्णांक64_t data_drp:1;
		uपूर्णांक64_t irun:1;
		uपूर्णांक64_t orun:1;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_mixx_orcnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_orcnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t orcnt:20;
#अन्यथा
		uपूर्णांक64_t orcnt:20;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mixx_orhwm अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_orhwm_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t orhwm:20;
#अन्यथा
		uपूर्णांक64_t orhwm:20;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mixx_oring1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_oring1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_60_63:4;
		uपूर्णांक64_t osize:20;
		uपूर्णांक64_t obase:37;
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t obase:37;
		uपूर्णांक64_t osize:20;
		uपूर्णांक64_t reserved_60_63:4;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mixx_oring1_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_60_63:4;
		uपूर्णांक64_t osize:20;
		uपूर्णांक64_t reserved_36_39:4;
		uपूर्णांक64_t obase:33;
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t obase:33;
		uपूर्णांक64_t reserved_36_39:4;
		uपूर्णांक64_t osize:20;
		uपूर्णांक64_t reserved_60_63:4;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_mixx_oring2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_oring2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_52_63:12;
		uपूर्णांक64_t otlptr:20;
		uपूर्णांक64_t reserved_20_31:12;
		uपूर्णांक64_t odbell:20;
#अन्यथा
		uपूर्णांक64_t odbell:20;
		uपूर्णांक64_t reserved_20_31:12;
		uपूर्णांक64_t otlptr:20;
		uपूर्णांक64_t reserved_52_63:12;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mixx_remcnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_remcnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_52_63:12;
		uपूर्णांक64_t iremcnt:20;
		uपूर्णांक64_t reserved_20_31:12;
		uपूर्णांक64_t oremcnt:20;
#अन्यथा
		uपूर्णांक64_t oremcnt:20;
		uपूर्णांक64_t reserved_20_31:12;
		uपूर्णांक64_t iremcnt:20;
		uपूर्णांक64_t reserved_52_63:12;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mixx_tsctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_tsctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_21_63:43;
		uपूर्णांक64_t tsavl:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t tstot:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t tscnt:5;
#अन्यथा
		uपूर्णांक64_t tscnt:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t tstot:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t tsavl:5;
		uपूर्णांक64_t reserved_21_63:43;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mixx_tstamp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mixx_tstamp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t tstamp:64;
#अन्यथा
		uपूर्णांक64_t tstamp:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
