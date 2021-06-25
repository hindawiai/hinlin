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

#अगर_अघोषित __CVMX_DBG_DEFS_H__
#घोषणा __CVMX_DBG_DEFS_H__

#घोषणा CVMX_DBG_DATA (CVMX_ADD_IO_SEG(0x00011F00000001E8ull))

जोड़ cvmx_dbg_data अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_dbg_data_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_23_63:41;
		uपूर्णांक64_t c_mul:5;
		uपूर्णांक64_t dsel_ext:1;
		uपूर्णांक64_t data:17;
#अन्यथा
		uपूर्णांक64_t data:17;
		uपूर्णांक64_t dsel_ext:1;
		uपूर्णांक64_t c_mul:5;
		uपूर्णांक64_t reserved_23_63:41;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_dbg_data_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_31_63:33;
		uपूर्णांक64_t pll_mul:3;
		uपूर्णांक64_t reserved_23_27:5;
		uपूर्णांक64_t c_mul:5;
		uपूर्णांक64_t dsel_ext:1;
		uपूर्णांक64_t data:17;
#अन्यथा
		uपूर्णांक64_t data:17;
		uपूर्णांक64_t dsel_ext:1;
		uपूर्णांक64_t c_mul:5;
		uपूर्णांक64_t reserved_23_27:5;
		uपूर्णांक64_t pll_mul:3;
		uपूर्णांक64_t reserved_31_63:33;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_dbg_data_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t d_mul:4;
		uपूर्णांक64_t dclk_mul2:1;
		uपूर्णांक64_t cclk_भाग2:1;
		uपूर्णांक64_t c_mul:5;
		uपूर्णांक64_t dsel_ext:1;
		uपूर्णांक64_t data:17;
#अन्यथा
		uपूर्णांक64_t data:17;
		uपूर्णांक64_t dsel_ext:1;
		uपूर्णांक64_t c_mul:5;
		uपूर्णांक64_t cclk_भाग2:1;
		uपूर्णांक64_t dclk_mul2:1;
		uपूर्णांक64_t d_mul:4;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_dbg_data_cn58xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t rem:6;
		uपूर्णांक64_t c_mul:5;
		uपूर्णांक64_t dsel_ext:1;
		uपूर्णांक64_t data:17;
#अन्यथा
		uपूर्णांक64_t data:17;
		uपूर्णांक64_t dsel_ext:1;
		uपूर्णांक64_t c_mul:5;
		uपूर्णांक64_t rem:6;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn58xx;
पूर्ण;

#पूर्ण_अगर
