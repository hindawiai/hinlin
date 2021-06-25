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

#अगर_अघोषित __CVMX_FPA_DEFS_H__
#घोषणा __CVMX_FPA_DEFS_H__

#घोषणा CVMX_FPA_ADDR_RANGE_ERROR (CVMX_ADD_IO_SEG(0x0001180028000458ull))
#घोषणा CVMX_FPA_BIST_STATUS (CVMX_ADD_IO_SEG(0x00011800280000E8ull))
#घोषणा CVMX_FPA_CTL_STATUS (CVMX_ADD_IO_SEG(0x0001180028000050ull))
#घोषणा CVMX_FPA_FPF0_MARKS (CVMX_ADD_IO_SEG(0x0001180028000000ull))
#घोषणा CVMX_FPA_FPF0_SIZE (CVMX_ADD_IO_SEG(0x0001180028000058ull))
#घोषणा CVMX_FPA_FPF1_MARKS CVMX_FPA_FPFX_MARKS(1)
#घोषणा CVMX_FPA_FPF2_MARKS CVMX_FPA_FPFX_MARKS(2)
#घोषणा CVMX_FPA_FPF3_MARKS CVMX_FPA_FPFX_MARKS(3)
#घोषणा CVMX_FPA_FPF4_MARKS CVMX_FPA_FPFX_MARKS(4)
#घोषणा CVMX_FPA_FPF5_MARKS CVMX_FPA_FPFX_MARKS(5)
#घोषणा CVMX_FPA_FPF6_MARKS CVMX_FPA_FPFX_MARKS(6)
#घोषणा CVMX_FPA_FPF7_MARKS CVMX_FPA_FPFX_MARKS(7)
#घोषणा CVMX_FPA_FPF8_MARKS (CVMX_ADD_IO_SEG(0x0001180028000240ull))
#घोषणा CVMX_FPA_FPF8_SIZE (CVMX_ADD_IO_SEG(0x0001180028000248ull))
#घोषणा CVMX_FPA_FPFX_MARKS(offset) (CVMX_ADD_IO_SEG(0x0001180028000008ull) + ((offset) & 7) * 8 - 8*1)
#घोषणा CVMX_FPA_FPFX_SIZE(offset) (CVMX_ADD_IO_SEG(0x0001180028000060ull) + ((offset) & 7) * 8 - 8*1)
#घोषणा CVMX_FPA_INT_ENB (CVMX_ADD_IO_SEG(0x0001180028000048ull))
#घोषणा CVMX_FPA_INT_SUM (CVMX_ADD_IO_SEG(0x0001180028000040ull))
#घोषणा CVMX_FPA_PACKET_THRESHOLD (CVMX_ADD_IO_SEG(0x0001180028000460ull))
#घोषणा CVMX_FPA_POOLX_END_ADDR(offset) (CVMX_ADD_IO_SEG(0x0001180028000358ull) + ((offset) & 15) * 8)
#घोषणा CVMX_FPA_POOLX_START_ADDR(offset) (CVMX_ADD_IO_SEG(0x0001180028000258ull) + ((offset) & 15) * 8)
#घोषणा CVMX_FPA_POOLX_THRESHOLD(offset) (CVMX_ADD_IO_SEG(0x0001180028000140ull) + ((offset) & 15) * 8)
#घोषणा CVMX_FPA_QUE0_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(0)
#घोषणा CVMX_FPA_QUE1_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(1)
#घोषणा CVMX_FPA_QUE2_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(2)
#घोषणा CVMX_FPA_QUE3_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(3)
#घोषणा CVMX_FPA_QUE4_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(4)
#घोषणा CVMX_FPA_QUE5_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(5)
#घोषणा CVMX_FPA_QUE6_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(6)
#घोषणा CVMX_FPA_QUE7_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(7)
#घोषणा CVMX_FPA_QUE8_PAGE_INDEX (CVMX_ADD_IO_SEG(0x0001180028000250ull))
#घोषणा CVMX_FPA_QUEX_AVAILABLE(offset) (CVMX_ADD_IO_SEG(0x0001180028000098ull) + ((offset) & 15) * 8)
#घोषणा CVMX_FPA_QUEX_PAGE_INDEX(offset) (CVMX_ADD_IO_SEG(0x00011800280000F0ull) + ((offset) & 7) * 8)
#घोषणा CVMX_FPA_QUE_ACT (CVMX_ADD_IO_SEG(0x0001180028000138ull))
#घोषणा CVMX_FPA_QUE_EXP (CVMX_ADD_IO_SEG(0x0001180028000130ull))
#घोषणा CVMX_FPA_WART_CTL (CVMX_ADD_IO_SEG(0x00011800280000D8ull))
#घोषणा CVMX_FPA_WART_STATUS (CVMX_ADD_IO_SEG(0x00011800280000E0ull))
#घोषणा CVMX_FPA_WQE_THRESHOLD (CVMX_ADD_IO_SEG(0x0001180028000468ull))
#घोषणा CVMX_FPA_CLK_COUNT (CVMX_ADD_IO_SEG(0x00012800000000F0ull))

जोड़ cvmx_fpa_addr_range_error अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_addr_range_error_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_38_63:26;
		uपूर्णांक64_t pool:5;
		uपूर्णांक64_t addr:33;
#अन्यथा
		uपूर्णांक64_t addr:33;
		uपूर्णांक64_t pool:5;
		uपूर्णांक64_t reserved_38_63:26;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_bist_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_bist_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t frd:1;
		uपूर्णांक64_t fpf0:1;
		uपूर्णांक64_t fpf1:1;
		uपूर्णांक64_t ffr:1;
		uपूर्णांक64_t fdr:1;
#अन्यथा
		uपूर्णांक64_t fdr:1;
		uपूर्णांक64_t ffr:1;
		uपूर्णांक64_t fpf1:1;
		uपूर्णांक64_t fpf0:1;
		uपूर्णांक64_t frd:1;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_ctl_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_ctl_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_21_63:43;
		uपूर्णांक64_t मुक्त_en:1;
		uपूर्णांक64_t ret_off:1;
		uपूर्णांक64_t req_off:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t use_ldt:1;
		uपूर्णांक64_t use_stt:1;
		uपूर्णांक64_t enb:1;
		uपूर्णांक64_t mem1_err:7;
		uपूर्णांक64_t mem0_err:7;
#अन्यथा
		uपूर्णांक64_t mem0_err:7;
		uपूर्णांक64_t mem1_err:7;
		uपूर्णांक64_t enb:1;
		uपूर्णांक64_t use_stt:1;
		uपूर्णांक64_t use_ldt:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t req_off:1;
		uपूर्णांक64_t ret_off:1;
		uपूर्णांक64_t मुक्त_en:1;
		uपूर्णांक64_t reserved_21_63:43;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_fpa_ctl_status_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t use_ldt:1;
		uपूर्णांक64_t use_stt:1;
		uपूर्णांक64_t enb:1;
		uपूर्णांक64_t mem1_err:7;
		uपूर्णांक64_t mem0_err:7;
#अन्यथा
		uपूर्णांक64_t mem0_err:7;
		uपूर्णांक64_t mem1_err:7;
		uपूर्णांक64_t enb:1;
		uपूर्णांक64_t use_stt:1;
		uपूर्णांक64_t use_ldt:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_fpa_fpfx_marks अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_fpfx_marks_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_22_63:42;
		uपूर्णांक64_t fpf_wr:11;
		uपूर्णांक64_t fpf_rd:11;
#अन्यथा
		uपूर्णांक64_t fpf_rd:11;
		uपूर्णांक64_t fpf_wr:11;
		uपूर्णांक64_t reserved_22_63:42;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_fpfx_size अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_fpfx_size_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t fpf_siz:11;
#अन्यथा
		uपूर्णांक64_t fpf_siz:11;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_fpf0_marks अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_fpf0_marks_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t fpf_wr:12;
		uपूर्णांक64_t fpf_rd:12;
#अन्यथा
		uपूर्णांक64_t fpf_rd:12;
		uपूर्णांक64_t fpf_wr:12;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_fpf0_size अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_fpf0_size_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t fpf_siz:12;
#अन्यथा
		uपूर्णांक64_t fpf_siz:12;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_fpf8_marks अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_fpf8_marks_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_22_63:42;
		uपूर्णांक64_t fpf_wr:11;
		uपूर्णांक64_t fpf_rd:11;
#अन्यथा
		uपूर्णांक64_t fpf_rd:11;
		uपूर्णांक64_t fpf_wr:11;
		uपूर्णांक64_t reserved_22_63:42;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_fpf8_size अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_fpf8_size_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t fpf_siz:12;
#अन्यथा
		uपूर्णांक64_t fpf_siz:12;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_पूर्णांक_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_पूर्णांक_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_50_63:14;
		uपूर्णांक64_t paddr_e:1;
		uपूर्णांक64_t reserved_44_48:5;
		uपूर्णांक64_t मुक्त7:1;
		uपूर्णांक64_t मुक्त6:1;
		uपूर्णांक64_t मुक्त5:1;
		uपूर्णांक64_t मुक्त4:1;
		uपूर्णांक64_t मुक्त3:1;
		uपूर्णांक64_t मुक्त2:1;
		uपूर्णांक64_t मुक्त1:1;
		uपूर्णांक64_t मुक्त0:1;
		uपूर्णांक64_t pool7th:1;
		uपूर्णांक64_t pool6th:1;
		uपूर्णांक64_t pool5th:1;
		uपूर्णांक64_t pool4th:1;
		uपूर्णांक64_t pool3th:1;
		uपूर्णांक64_t pool2th:1;
		uपूर्णांक64_t pool1th:1;
		uपूर्णांक64_t pool0th:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed0_sbe:1;
#अन्यथा
		uपूर्णांक64_t fed0_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t pool0th:1;
		uपूर्णांक64_t pool1th:1;
		uपूर्णांक64_t pool2th:1;
		uपूर्णांक64_t pool3th:1;
		uपूर्णांक64_t pool4th:1;
		uपूर्णांक64_t pool5th:1;
		uपूर्णांक64_t pool6th:1;
		uपूर्णांक64_t pool7th:1;
		uपूर्णांक64_t मुक्त0:1;
		uपूर्णांक64_t मुक्त1:1;
		uपूर्णांक64_t मुक्त2:1;
		uपूर्णांक64_t मुक्त3:1;
		uपूर्णांक64_t मुक्त4:1;
		uपूर्णांक64_t मुक्त5:1;
		uपूर्णांक64_t मुक्त6:1;
		uपूर्णांक64_t मुक्त7:1;
		uपूर्णांक64_t reserved_44_48:5;
		uपूर्णांक64_t paddr_e:1;
		uपूर्णांक64_t reserved_50_63:14;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_fpa_पूर्णांक_enb_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed0_sbe:1;
#अन्यथा
		uपूर्णांक64_t fed0_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_fpa_पूर्णांक_enb_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_50_63:14;
		uपूर्णांक64_t paddr_e:1;
		uपूर्णांक64_t res_44:5;
		uपूर्णांक64_t मुक्त7:1;
		uपूर्णांक64_t मुक्त6:1;
		uपूर्णांक64_t मुक्त5:1;
		uपूर्णांक64_t मुक्त4:1;
		uपूर्णांक64_t मुक्त3:1;
		uपूर्णांक64_t मुक्त2:1;
		uपूर्णांक64_t मुक्त1:1;
		uपूर्णांक64_t मुक्त0:1;
		uपूर्णांक64_t pool7th:1;
		uपूर्णांक64_t pool6th:1;
		uपूर्णांक64_t pool5th:1;
		uपूर्णांक64_t pool4th:1;
		uपूर्णांक64_t pool3th:1;
		uपूर्णांक64_t pool2th:1;
		uपूर्णांक64_t pool1th:1;
		uपूर्णांक64_t pool0th:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed0_sbe:1;
#अन्यथा
		uपूर्णांक64_t fed0_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t pool0th:1;
		uपूर्णांक64_t pool1th:1;
		uपूर्णांक64_t pool2th:1;
		uपूर्णांक64_t pool3th:1;
		uपूर्णांक64_t pool4th:1;
		uपूर्णांक64_t pool5th:1;
		uपूर्णांक64_t pool6th:1;
		uपूर्णांक64_t pool7th:1;
		uपूर्णांक64_t मुक्त0:1;
		uपूर्णांक64_t मुक्त1:1;
		uपूर्णांक64_t मुक्त2:1;
		uपूर्णांक64_t मुक्त3:1;
		uपूर्णांक64_t मुक्त4:1;
		uपूर्णांक64_t मुक्त5:1;
		uपूर्णांक64_t मुक्त6:1;
		uपूर्णांक64_t मुक्त7:1;
		uपूर्णांक64_t res_44:5;
		uपूर्णांक64_t paddr_e:1;
		uपूर्णांक64_t reserved_50_63:14;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_fpa_पूर्णांक_enb_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t मुक्त7:1;
		uपूर्णांक64_t मुक्त6:1;
		uपूर्णांक64_t मुक्त5:1;
		uपूर्णांक64_t मुक्त4:1;
		uपूर्णांक64_t मुक्त3:1;
		uपूर्णांक64_t मुक्त2:1;
		uपूर्णांक64_t मुक्त1:1;
		uपूर्णांक64_t मुक्त0:1;
		uपूर्णांक64_t pool7th:1;
		uपूर्णांक64_t pool6th:1;
		uपूर्णांक64_t pool5th:1;
		uपूर्णांक64_t pool4th:1;
		uपूर्णांक64_t pool3th:1;
		uपूर्णांक64_t pool2th:1;
		uपूर्णांक64_t pool1th:1;
		uपूर्णांक64_t pool0th:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed0_sbe:1;
#अन्यथा
		uपूर्णांक64_t fed0_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t pool0th:1;
		uपूर्णांक64_t pool1th:1;
		uपूर्णांक64_t pool2th:1;
		uपूर्णांक64_t pool3th:1;
		uपूर्णांक64_t pool4th:1;
		uपूर्णांक64_t pool5th:1;
		uपूर्णांक64_t pool6th:1;
		uपूर्णांक64_t pool7th:1;
		uपूर्णांक64_t मुक्त0:1;
		uपूर्णांक64_t मुक्त1:1;
		uपूर्णांक64_t मुक्त2:1;
		uपूर्णांक64_t मुक्त3:1;
		uपूर्णांक64_t मुक्त4:1;
		uपूर्णांक64_t मुक्त5:1;
		uपूर्णांक64_t मुक्त6:1;
		uपूर्णांक64_t मुक्त7:1;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_fpa_पूर्णांक_enb_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_50_63:14;
		uपूर्णांक64_t paddr_e:1;
		uपूर्णांक64_t pool8th:1;
		uपूर्णांक64_t q8_perr:1;
		uपूर्णांक64_t q8_coff:1;
		uपूर्णांक64_t q8_und:1;
		uपूर्णांक64_t मुक्त8:1;
		uपूर्णांक64_t मुक्त7:1;
		uपूर्णांक64_t मुक्त6:1;
		uपूर्णांक64_t मुक्त5:1;
		uपूर्णांक64_t मुक्त4:1;
		uपूर्णांक64_t मुक्त3:1;
		uपूर्णांक64_t मुक्त2:1;
		uपूर्णांक64_t मुक्त1:1;
		uपूर्णांक64_t मुक्त0:1;
		uपूर्णांक64_t pool7th:1;
		uपूर्णांक64_t pool6th:1;
		uपूर्णांक64_t pool5th:1;
		uपूर्णांक64_t pool4th:1;
		uपूर्णांक64_t pool3th:1;
		uपूर्णांक64_t pool2th:1;
		uपूर्णांक64_t pool1th:1;
		uपूर्णांक64_t pool0th:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed0_sbe:1;
#अन्यथा
		uपूर्णांक64_t fed0_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t pool0th:1;
		uपूर्णांक64_t pool1th:1;
		uपूर्णांक64_t pool2th:1;
		uपूर्णांक64_t pool3th:1;
		uपूर्णांक64_t pool4th:1;
		uपूर्णांक64_t pool5th:1;
		uपूर्णांक64_t pool6th:1;
		uपूर्णांक64_t pool7th:1;
		uपूर्णांक64_t मुक्त0:1;
		uपूर्णांक64_t मुक्त1:1;
		uपूर्णांक64_t मुक्त2:1;
		uपूर्णांक64_t मुक्त3:1;
		uपूर्णांक64_t मुक्त4:1;
		uपूर्णांक64_t मुक्त5:1;
		uपूर्णांक64_t मुक्त6:1;
		uपूर्णांक64_t मुक्त7:1;
		uपूर्णांक64_t मुक्त8:1;
		uपूर्णांक64_t q8_und:1;
		uपूर्णांक64_t q8_coff:1;
		uपूर्णांक64_t q8_perr:1;
		uपूर्णांक64_t pool8th:1;
		uपूर्णांक64_t paddr_e:1;
		uपूर्णांक64_t reserved_50_63:14;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_fpa_पूर्णांक_sum अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_पूर्णांक_sum_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_50_63:14;
		uपूर्णांक64_t paddr_e:1;
		uपूर्णांक64_t pool8th:1;
		uपूर्णांक64_t q8_perr:1;
		uपूर्णांक64_t q8_coff:1;
		uपूर्णांक64_t q8_und:1;
		uपूर्णांक64_t मुक्त8:1;
		uपूर्णांक64_t मुक्त7:1;
		uपूर्णांक64_t मुक्त6:1;
		uपूर्णांक64_t मुक्त5:1;
		uपूर्णांक64_t मुक्त4:1;
		uपूर्णांक64_t मुक्त3:1;
		uपूर्णांक64_t मुक्त2:1;
		uपूर्णांक64_t मुक्त1:1;
		uपूर्णांक64_t मुक्त0:1;
		uपूर्णांक64_t pool7th:1;
		uपूर्णांक64_t pool6th:1;
		uपूर्णांक64_t pool5th:1;
		uपूर्णांक64_t pool4th:1;
		uपूर्णांक64_t pool3th:1;
		uपूर्णांक64_t pool2th:1;
		uपूर्णांक64_t pool1th:1;
		uपूर्णांक64_t pool0th:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed0_sbe:1;
#अन्यथा
		uपूर्णांक64_t fed0_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t pool0th:1;
		uपूर्णांक64_t pool1th:1;
		uपूर्णांक64_t pool2th:1;
		uपूर्णांक64_t pool3th:1;
		uपूर्णांक64_t pool4th:1;
		uपूर्णांक64_t pool5th:1;
		uपूर्णांक64_t pool6th:1;
		uपूर्णांक64_t pool7th:1;
		uपूर्णांक64_t मुक्त0:1;
		uपूर्णांक64_t मुक्त1:1;
		uपूर्णांक64_t मुक्त2:1;
		uपूर्णांक64_t मुक्त3:1;
		uपूर्णांक64_t मुक्त4:1;
		uपूर्णांक64_t मुक्त5:1;
		uपूर्णांक64_t मुक्त6:1;
		uपूर्णांक64_t मुक्त7:1;
		uपूर्णांक64_t मुक्त8:1;
		uपूर्णांक64_t q8_und:1;
		uपूर्णांक64_t q8_coff:1;
		uपूर्णांक64_t q8_perr:1;
		uपूर्णांक64_t pool8th:1;
		uपूर्णांक64_t paddr_e:1;
		uपूर्णांक64_t reserved_50_63:14;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_fpa_पूर्णांक_sum_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed0_sbe:1;
#अन्यथा
		uपूर्णांक64_t fed0_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_fpa_पूर्णांक_sum_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_50_63:14;
		uपूर्णांक64_t paddr_e:1;
		uपूर्णांक64_t reserved_44_48:5;
		uपूर्णांक64_t मुक्त7:1;
		uपूर्णांक64_t मुक्त6:1;
		uपूर्णांक64_t मुक्त5:1;
		uपूर्णांक64_t मुक्त4:1;
		uपूर्णांक64_t मुक्त3:1;
		uपूर्णांक64_t मुक्त2:1;
		uपूर्णांक64_t मुक्त1:1;
		uपूर्णांक64_t मुक्त0:1;
		uपूर्णांक64_t pool7th:1;
		uपूर्णांक64_t pool6th:1;
		uपूर्णांक64_t pool5th:1;
		uपूर्णांक64_t pool4th:1;
		uपूर्णांक64_t pool3th:1;
		uपूर्णांक64_t pool2th:1;
		uपूर्णांक64_t pool1th:1;
		uपूर्णांक64_t pool0th:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed0_sbe:1;
#अन्यथा
		uपूर्णांक64_t fed0_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t pool0th:1;
		uपूर्णांक64_t pool1th:1;
		uपूर्णांक64_t pool2th:1;
		uपूर्णांक64_t pool3th:1;
		uपूर्णांक64_t pool4th:1;
		uपूर्णांक64_t pool5th:1;
		uपूर्णांक64_t pool6th:1;
		uपूर्णांक64_t pool7th:1;
		uपूर्णांक64_t मुक्त0:1;
		uपूर्णांक64_t मुक्त1:1;
		uपूर्णांक64_t मुक्त2:1;
		uपूर्णांक64_t मुक्त3:1;
		uपूर्णांक64_t मुक्त4:1;
		uपूर्णांक64_t मुक्त5:1;
		uपूर्णांक64_t मुक्त6:1;
		uपूर्णांक64_t मुक्त7:1;
		uपूर्णांक64_t reserved_44_48:5;
		uपूर्णांक64_t paddr_e:1;
		uपूर्णांक64_t reserved_50_63:14;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_fpa_पूर्णांक_sum_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t मुक्त7:1;
		uपूर्णांक64_t मुक्त6:1;
		uपूर्णांक64_t मुक्त5:1;
		uपूर्णांक64_t मुक्त4:1;
		uपूर्णांक64_t मुक्त3:1;
		uपूर्णांक64_t मुक्त2:1;
		uपूर्णांक64_t मुक्त1:1;
		uपूर्णांक64_t मुक्त0:1;
		uपूर्णांक64_t pool7th:1;
		uपूर्णांक64_t pool6th:1;
		uपूर्णांक64_t pool5th:1;
		uपूर्णांक64_t pool4th:1;
		uपूर्णांक64_t pool3th:1;
		uपूर्णांक64_t pool2th:1;
		uपूर्णांक64_t pool1th:1;
		uपूर्णांक64_t pool0th:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed0_sbe:1;
#अन्यथा
		uपूर्णांक64_t fed0_sbe:1;
		uपूर्णांक64_t fed0_dbe:1;
		uपूर्णांक64_t fed1_sbe:1;
		uपूर्णांक64_t fed1_dbe:1;
		uपूर्णांक64_t q0_und:1;
		uपूर्णांक64_t q0_coff:1;
		uपूर्णांक64_t q0_perr:1;
		uपूर्णांक64_t q1_und:1;
		uपूर्णांक64_t q1_coff:1;
		uपूर्णांक64_t q1_perr:1;
		uपूर्णांक64_t q2_und:1;
		uपूर्णांक64_t q2_coff:1;
		uपूर्णांक64_t q2_perr:1;
		uपूर्णांक64_t q3_und:1;
		uपूर्णांक64_t q3_coff:1;
		uपूर्णांक64_t q3_perr:1;
		uपूर्णांक64_t q4_und:1;
		uपूर्णांक64_t q4_coff:1;
		uपूर्णांक64_t q4_perr:1;
		uपूर्णांक64_t q5_und:1;
		uपूर्णांक64_t q5_coff:1;
		uपूर्णांक64_t q5_perr:1;
		uपूर्णांक64_t q6_und:1;
		uपूर्णांक64_t q6_coff:1;
		uपूर्णांक64_t q6_perr:1;
		uपूर्णांक64_t q7_und:1;
		uपूर्णांक64_t q7_coff:1;
		uपूर्णांक64_t q7_perr:1;
		uपूर्णांक64_t pool0th:1;
		uपूर्णांक64_t pool1th:1;
		uपूर्णांक64_t pool2th:1;
		uपूर्णांक64_t pool3th:1;
		uपूर्णांक64_t pool4th:1;
		uपूर्णांक64_t pool5th:1;
		uपूर्णांक64_t pool6th:1;
		uपूर्णांक64_t pool7th:1;
		uपूर्णांक64_t मुक्त0:1;
		uपूर्णांक64_t मुक्त1:1;
		uपूर्णांक64_t मुक्त2:1;
		uपूर्णांक64_t मुक्त3:1;
		uपूर्णांक64_t मुक्त4:1;
		uपूर्णांक64_t मुक्त5:1;
		uपूर्णांक64_t मुक्त6:1;
		uपूर्णांक64_t मुक्त7:1;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_fpa_packet_threshold अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_packet_threshold_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t thresh:32;
#अन्यथा
		uपूर्णांक64_t thresh:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_poolx_end_addr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_poolx_end_addr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_33_63:31;
		uपूर्णांक64_t addr:33;
#अन्यथा
		uपूर्णांक64_t addr:33;
		uपूर्णांक64_t reserved_33_63:31;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_poolx_start_addr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_poolx_start_addr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_33_63:31;
		uपूर्णांक64_t addr:33;
#अन्यथा
		uपूर्णांक64_t addr:33;
		uपूर्णांक64_t reserved_33_63:31;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_poolx_threshold अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_poolx_threshold_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t thresh:32;
#अन्यथा
		uपूर्णांक64_t thresh:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_fpa_poolx_threshold_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t thresh:29;
#अन्यथा
		uपूर्णांक64_t thresh:29;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_fpa_quex_available अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_quex_available_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t que_siz:32;
#अन्यथा
		uपूर्णांक64_t que_siz:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_fpa_quex_available_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t que_siz:29;
#अन्यथा
		uपूर्णांक64_t que_siz:29;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_fpa_quex_page_index अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_quex_page_index_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t pg_num:25;
#अन्यथा
		uपूर्णांक64_t pg_num:25;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_que8_page_index अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_que8_page_index_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t pg_num:25;
#अन्यथा
		uपूर्णांक64_t pg_num:25;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_que_act अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_que_act_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t act_que:3;
		uपूर्णांक64_t act_indx:26;
#अन्यथा
		uपूर्णांक64_t act_indx:26;
		uपूर्णांक64_t act_que:3;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_que_exp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_que_exp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t exp_que:3;
		uपूर्णांक64_t exp_indx:26;
#अन्यथा
		uपूर्णांक64_t exp_indx:26;
		uपूर्णांक64_t exp_que:3;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_wart_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_wart_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t ctl:16;
#अन्यथा
		uपूर्णांक64_t ctl:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_wart_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_wart_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t status:32;
#अन्यथा
		uपूर्णांक64_t status:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_fpa_wqe_threshold अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_fpa_wqe_threshold_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t thresh:32;
#अन्यथा
		uपूर्णांक64_t thresh:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
