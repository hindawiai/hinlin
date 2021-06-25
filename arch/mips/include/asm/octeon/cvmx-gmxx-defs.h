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

#अगर_अघोषित __CVMX_GMXX_DEFS_H__
#घोषणा __CVMX_GMXX_DEFS_H__

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_HG2_CONTROL(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000550ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000550ull) + (block_id) * 0x8000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_INF_MODE(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800080007F8ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800080007F8ull) + (block_id) * 0x8000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_PRTX_CFG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000010ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000010ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000010ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_RXX_ADR_CAM0(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000180ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000180ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000180ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_RXX_ADR_CAM1(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000188ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000188ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000188ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_RXX_ADR_CAM2(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000190ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000190ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000190ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_RXX_ADR_CAM3(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000198ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000198ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000198ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_RXX_ADR_CAM4(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800080001A0ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800080001A0ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800080001A0ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_RXX_ADR_CAM5(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800080001A8ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800080001A8ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800080001A8ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_RXX_ADR_CAM_EN(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000108ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000108ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000108ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_RXX_ADR_CTL(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000100ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000100ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000100ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_RXX_FRM_CTL(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000018ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000018ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000018ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

#घोषणा CVMX_GMXX_RXX_FRM_MAX(offset, block_id) (CVMX_ADD_IO_SEG(0x0001180008000030ull) + (((offset) & 3) + ((block_id) & 1) * 0x10000ull) * 2048)
#घोषणा CVMX_GMXX_RXX_FRM_MIN(offset, block_id) (CVMX_ADD_IO_SEG(0x0001180008000028ull) + (((offset) & 3) + ((block_id) & 1) * 0x10000ull) * 2048)

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_RXX_INT_EN(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000008ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000008ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000008ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_RXX_INT_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000000ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000000ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000000ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_RXX_JABBER(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000038ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000038ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000038ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

#घोषणा CVMX_GMXX_RXX_RX_INBND(offset, block_id) (CVMX_ADD_IO_SEG(0x0001180008000060ull) + (((offset) & 3) + ((block_id) & 1) * 0x10000ull) * 2048)

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_RX_PRTS(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000410ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000410ull) + (block_id) * 0x8000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_RX_XAUI_CTL(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000530ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000530ull) + (block_id) * 0x8000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_SMACX(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000230ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000230ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000230ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_TXX_BURST(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000228ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000228ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000228ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

#घोषणा CVMX_GMXX_TXX_CLK(offset, block_id) (CVMX_ADD_IO_SEG(0x0001180008000208ull) + (((offset) & 3) + ((block_id) & 1) * 0x10000ull) * 2048)
अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_TXX_CTL(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000270ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000270ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000270ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_TXX_PAUSE_PKT_INTERVAL(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000248ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000248ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000248ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_TXX_PAUSE_PKT_TIME(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000238ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000238ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000238ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_TXX_SLOT(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000220ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000220ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000220ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_TXX_THRESH(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000210ull) + ((offset) + (block_id) * 0x0ull) * 2048;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000210ull) + ((offset) + (block_id) * 0x2000ull) * 2048;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000210ull) + ((offset) + (block_id) * 0x10000ull) * 2048;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_TX_INT_EN(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000508ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000508ull) + (block_id) * 0x8000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_TX_INT_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000500ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000500ull) + (block_id) * 0x8000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_TX_OVR_BP(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800080004C8ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800080004C8ull) + (block_id) * 0x8000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_TX_PRTS(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000480ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000480ull) + (block_id) * 0x8000000ull;
पूर्ण

#घोषणा CVMX_GMXX_TX_SPI_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800080004C0ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_GMXX_TX_SPI_MAX(block_id) (CVMX_ADD_IO_SEG(0x00011800080004B0ull) + ((block_id) & 1) * 0x8000000ull)
#घोषणा CVMX_GMXX_TX_SPI_THRESH(block_id) (CVMX_ADD_IO_SEG(0x00011800080004B8ull) + ((block_id) & 1) * 0x8000000ull)
अटल अंतरभूत uपूर्णांक64_t CVMX_GMXX_TX_XAUI_CTL(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x0001180008000528ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x0001180008000528ull) + (block_id) * 0x8000000ull;
पूर्ण

व्योम __cvmx_पूर्णांकerrupt_gmxx_enable(पूर्णांक पूर्णांकerface);

जोड़ cvmx_gmxx_hg2_control अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_hg2_control_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_19_63:45;
		uपूर्णांक64_t hg2tx_en:1;
		uपूर्णांक64_t hg2rx_en:1;
		uपूर्णांक64_t phys_en:1;
		uपूर्णांक64_t logl_en:16;
#अन्यथा
		uपूर्णांक64_t logl_en:16;
		uपूर्णांक64_t phys_en:1;
		uपूर्णांक64_t hg2rx_en:1;
		uपूर्णांक64_t hg2tx_en:1;
		uपूर्णांक64_t reserved_19_63:45;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gmxx_inf_mode अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_inf_mode_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t rate:4;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t speed:4;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t mode:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t p0mii:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t type:1;
#अन्यथा
		uपूर्णांक64_t type:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t p0mii:1;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t mode:3;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t speed:4;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t rate:4;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gmxx_inf_mode_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t p0mii:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t type:1;
#अन्यथा
		uपूर्णांक64_t type:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t p0mii:1;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_gmxx_inf_mode_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t type:1;
#अन्यथा
		uपूर्णांक64_t type:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_gmxx_inf_mode_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t speed:2;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t type:1;
#अन्यथा
		uपूर्णांक64_t type:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t speed:2;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_gmxx_inf_mode_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t speed:4;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t mode:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t type:1;
#अन्यथा
		uपूर्णांक64_t type:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t mode:1;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t speed:4;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_gmxx_inf_mode_cn66xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t rate:4;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t speed:4;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t mode:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t type:1;
#अन्यथा
		uपूर्णांक64_t type:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t mode:1;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t speed:4;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t rate:4;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn66xx;
	काष्ठा cvmx_gmxx_inf_mode_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t speed:4;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t mode:3;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t type:1;
#अन्यथा
		uपूर्णांक64_t type:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t mode:3;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t speed:4;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_gmxx_prtx_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_prtx_cfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_22_63:42;
		uपूर्णांक64_t pknd:6;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t tx_idle:1;
		uपूर्णांक64_t rx_idle:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t speed_msb:1;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t slotसमय:1;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t speed:1;
		uपूर्णांक64_t en:1;
#अन्यथा
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t speed:1;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t slotसमय:1;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t speed_msb:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t rx_idle:1;
		uपूर्णांक64_t tx_idle:1;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t pknd:6;
		uपूर्णांक64_t reserved_22_63:42;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gmxx_prtx_cfg_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t slotसमय:1;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t speed:1;
		uपूर्णांक64_t en:1;
#अन्यथा
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t speed:1;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t slotसमय:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_gmxx_prtx_cfg_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t tx_idle:1;
		uपूर्णांक64_t rx_idle:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t speed_msb:1;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t slotसमय:1;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t speed:1;
		uपूर्णांक64_t en:1;
#अन्यथा
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t speed:1;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t slotसमय:1;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t speed_msb:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t rx_idle:1;
		uपूर्णांक64_t tx_idle:1;
		uपूर्णांक64_t reserved_14_63:50;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_gmxx_rxx_adr_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_rxx_adr_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t cam_mode:1;
		uपूर्णांक64_t mcst:2;
		uपूर्णांक64_t bcst:1;
#अन्यथा
		uपूर्णांक64_t bcst:1;
		uपूर्णांक64_t mcst:2;
		uपूर्णांक64_t cam_mode:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gmxx_rxx_frm_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_rxx_frm_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t ptp_mode:1;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t null_dis:1;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t pre_chk:1;
#अन्यथा
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t null_dis:1;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t ptp_mode:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gmxx_rxx_frm_ctl_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t pre_chk:1;
#अन्यथा
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_gmxx_rxx_frm_ctl_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t pre_chk:1;
#अन्यथा
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_gmxx_rxx_frm_ctl_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t null_dis:1;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t reserved_7_8:2;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t pre_chk:1;
#अन्यथा
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t reserved_7_8:2;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t null_dis:1;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_gmxx_rxx_frm_ctl_cn56xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t reserved_7_8:2;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t pre_chk:1;
#अन्यथा
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t reserved_7_8:2;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn56xxp1;
	काष्ठा cvmx_gmxx_rxx_frm_ctl_cn58xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t null_dis:1;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t pre_chk:1;
#अन्यथा
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t null_dis:1;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण cn58xx;
	काष्ठा cvmx_gmxx_rxx_frm_ctl_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t ptp_mode:1;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t null_dis:1;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t reserved_7_8:2;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t pre_chk:1;
#अन्यथा
		uपूर्णांक64_t pre_chk:1;
		uपूर्णांक64_t pre_strp:1;
		uपूर्णांक64_t ctl_drp:1;
		uपूर्णांक64_t ctl_bck:1;
		uपूर्णांक64_t ctl_mcst:1;
		uपूर्णांक64_t ctl_smac:1;
		uपूर्णांक64_t pre_मुक्त:1;
		uपूर्णांक64_t reserved_7_8:2;
		uपूर्णांक64_t pre_align:1;
		uपूर्णांक64_t null_dis:1;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t ptp_mode:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_gmxx_rxx_frm_max अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_rxx_frm_max_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t len:16;
#अन्यथा
		uपूर्णांक64_t len:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gmxx_rxx_frm_min अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_rxx_frm_min_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t len:16;
#अन्यथा
		uपूर्णांक64_t len:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gmxx_rxx_पूर्णांक_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t minerr:1;
#अन्यथा
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_en_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_19_63:45;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t minerr:1;
#अन्यथा
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t reserved_19_63:45;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_en_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t reserved_6_6:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_0_0:1;
#अन्यथा
		uपूर्णांक64_t reserved_0_0:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t reserved_6_6:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_en_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_0_0:1;
#अन्यथा
		uपूर्णांक64_t reserved_0_0:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_en_cn56xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_27_63:37;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_0_0:1;
#अन्यथा
		uपूर्णांक64_t reserved_0_0:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t reserved_27_63:37;
#पूर्ण_अगर
	पूर्ण cn56xxp1;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_en_cn58xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t minerr:1;
#अन्यथा
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn58xx;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_en_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t minerr:1;
#अन्यथा
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_gmxx_rxx_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t minerr:1;
#अन्यथा
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_reg_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_19_63:45;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t minerr:1;
#अन्यथा
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t reserved_19_63:45;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_reg_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t reserved_6_6:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_0_0:1;
#अन्यथा
		uपूर्णांक64_t reserved_0_0:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t reserved_6_6:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_reg_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_0_0:1;
#अन्यथा
		uपूर्णांक64_t reserved_0_0:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_reg_cn56xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_27_63:37;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_0_0:1;
#अन्यथा
		uपूर्णांक64_t reserved_0_0:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t reserved_27_63:37;
#पूर्ण_अगर
	पूर्ण cn56xxp1;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_reg_cn58xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t minerr:1;
#अन्यथा
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t alnerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t niberr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t phy_link:1;
		uपूर्णांक64_t phy_spd:1;
		uपूर्णांक64_t phy_dupx:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn58xx;
	काष्ठा cvmx_gmxx_rxx_पूर्णांक_reg_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t minerr:1;
#अन्यथा
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t carext:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t jabber:1;
		uपूर्णांक64_t fcserr:1;
		uपूर्णांक64_t reserved_5_6:2;
		uपूर्णांक64_t rcverr:1;
		uपूर्णांक64_t skperr:1;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t ovrerr:1;
		uपूर्णांक64_t pcterr:1;
		uपूर्णांक64_t rsverr:1;
		uपूर्णांक64_t falerr:1;
		uपूर्णांक64_t coldet:1;
		uपूर्णांक64_t अगरgerr:1;
		uपूर्णांक64_t reserved_16_18:3;
		uपूर्णांक64_t छोड़ो_drp:1;
		uपूर्णांक64_t loc_fault:1;
		uपूर्णांक64_t rem_fault:1;
		uपूर्णांक64_t bad_seq:1;
		uपूर्णांक64_t bad_term:1;
		uपूर्णांक64_t unsop:1;
		uपूर्णांक64_t uneop:1;
		uपूर्णांक64_t undat:1;
		uपूर्णांक64_t hg2fld:1;
		uपूर्णांक64_t hg2cc:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_gmxx_rxx_jabber अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_rxx_jabber_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t cnt:16;
#अन्यथा
		uपूर्णांक64_t cnt:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gmxx_rxx_rx_inbnd अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_rxx_rx_inbnd_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t speed:2;
		uपूर्णांक64_t status:1;
#अन्यथा
		uपूर्णांक64_t status:1;
		uपूर्णांक64_t speed:2;
		uपूर्णांक64_t duplex:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gmxx_rx_prts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_rx_prts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t prts:3;
#अन्यथा
		uपूर्णांक64_t prts:3;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gmxx_rx_xaui_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_rx_xaui_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t status:2;
#अन्यथा
		uपूर्णांक64_t status:2;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gmxx_txx_thresh अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_txx_thresh_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t cnt:10;
#अन्यथा
		uपूर्णांक64_t cnt:10;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gmxx_txx_thresh_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t cnt:7;
#अन्यथा
		uपूर्णांक64_t cnt:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_gmxx_txx_thresh_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t cnt:9;
#अन्यथा
		uपूर्णांक64_t cnt:9;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn38xx;
पूर्ण;

जोड़ cvmx_gmxx_tx_पूर्णांक_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t xchange:1;
		uपूर्णांक64_t ptp_lost:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t ptp_lost:4;
		uपूर्णांक64_t xchange:1;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_en_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_19_63:45;
		uपूर्णांक64_t late_col:3;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t xsdef:3;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t xscol:3;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t undflw:3;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:3;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t xscol:3;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t xsdef:3;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t late_col:3;
		uपूर्णांक64_t reserved_19_63:45;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_en_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_15_63:49;
		uपूर्णांक64_t xsdef:3;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t xscol:3;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t undflw:3;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:3;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t xscol:3;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t xsdef:3;
		uपूर्णांक64_t reserved_15_63:49;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_en_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t ncb_nxa:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t ncb_nxa:1;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_en_cn38xxp2 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t ncb_nxa:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t ncb_nxa:1;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण cn38xxp2;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_en_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_en_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t ptp_lost:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t ptp_lost:4;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_en_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t xchange:1;
		uपूर्णांक64_t ptp_lost:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t pko_nxp:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t pko_nxp:1;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t ptp_lost:4;
		uपूर्णांक64_t xchange:1;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण cn68xx;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_en_cnf71xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t xchange:1;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t ptp_lost:2;
		uपूर्णांक64_t reserved_18_19:2;
		uपूर्णांक64_t late_col:2;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t xsdef:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t xscol:2;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t undflw:2;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:2;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t xscol:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t xsdef:2;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t late_col:2;
		uपूर्णांक64_t reserved_18_19:2;
		uपूर्णांक64_t ptp_lost:2;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t xchange:1;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण cnf71xx;
पूर्ण;

जोड़ cvmx_gmxx_tx_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t xchange:1;
		uपूर्णांक64_t ptp_lost:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t ptp_lost:4;
		uपूर्णांक64_t xchange:1;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_reg_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_19_63:45;
		uपूर्णांक64_t late_col:3;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t xsdef:3;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t xscol:3;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t undflw:3;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:3;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t xscol:3;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t xsdef:3;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t late_col:3;
		uपूर्णांक64_t reserved_19_63:45;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_reg_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_15_63:49;
		uपूर्णांक64_t xsdef:3;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t xscol:3;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t undflw:3;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:3;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t xscol:3;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t xsdef:3;
		uपूर्णांक64_t reserved_15_63:49;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_reg_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t ncb_nxa:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t ncb_nxa:1;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_reg_cn38xxp2 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t ncb_nxa:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t ncb_nxa:1;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण cn38xxp2;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_reg_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_reg_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t ptp_lost:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t ptp_lost:4;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_reg_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t xchange:1;
		uपूर्णांक64_t ptp_lost:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t pko_nxp:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t pko_nxp:1;
		uपूर्णांक64_t undflw:4;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t xscol:4;
		uपूर्णांक64_t xsdef:4;
		uपूर्णांक64_t late_col:4;
		uपूर्णांक64_t ptp_lost:4;
		uपूर्णांक64_t xchange:1;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण cn68xx;
	काष्ठा cvmx_gmxx_tx_पूर्णांक_reg_cnf71xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_25_63:39;
		uपूर्णांक64_t xchange:1;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t ptp_lost:2;
		uपूर्णांक64_t reserved_18_19:2;
		uपूर्णांक64_t late_col:2;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t xsdef:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t xscol:2;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t undflw:2;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pko_nxa:1;
#अन्यथा
		uपूर्णांक64_t pko_nxa:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t undflw:2;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t xscol:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t xsdef:2;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t late_col:2;
		uपूर्णांक64_t reserved_18_19:2;
		uपूर्णांक64_t ptp_lost:2;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t xchange:1;
		uपूर्णांक64_t reserved_25_63:39;
#पूर्ण_अगर
	पूर्ण cnf71xx;
पूर्ण;

जोड़ cvmx_gmxx_tx_ovr_bp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_tx_ovr_bp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t tx_prt_bp:16;
		uपूर्णांक64_t reserved_12_31:20;
		uपूर्णांक64_t en:4;
		uपूर्णांक64_t bp:4;
		uपूर्णांक64_t ign_full:4;
#अन्यथा
		uपूर्णांक64_t ign_full:4;
		uपूर्णांक64_t bp:4;
		uपूर्णांक64_t en:4;
		uपूर्णांक64_t reserved_12_31:20;
		uपूर्णांक64_t tx_prt_bp:16;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gmxx_tx_ovr_bp_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t en:3;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t bp:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t ign_full:3;
#अन्यथा
		uपूर्णांक64_t ign_full:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t bp:3;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t en:3;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_gmxx_tx_ovr_bp_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t en:4;
		uपूर्णांक64_t bp:4;
		uपूर्णांक64_t ign_full:4;
#अन्यथा
		uपूर्णांक64_t ign_full:4;
		uपूर्णांक64_t bp:4;
		uपूर्णांक64_t en:4;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_gmxx_tx_ovr_bp_cnf71xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t tx_prt_bp:16;
		uपूर्णांक64_t reserved_10_31:22;
		uपूर्णांक64_t en:2;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t bp:2;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t ign_full:2;
#अन्यथा
		uपूर्णांक64_t ign_full:2;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t bp:2;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t en:2;
		uपूर्णांक64_t reserved_10_31:22;
		uपूर्णांक64_t tx_prt_bp:16;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण cnf71xx;
पूर्ण;

जोड़ cvmx_gmxx_tx_prts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_tx_prts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t prts:5;
#अन्यथा
		uपूर्णांक64_t prts:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gmxx_tx_spi_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_tx_spi_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t tpa_clr:1;
		uपूर्णांक64_t cont_pkt:1;
#अन्यथा
		uपूर्णांक64_t cont_pkt:1;
		uपूर्णांक64_t tpa_clr:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gmxx_tx_spi_max अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_tx_spi_max_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_23_63:41;
		uपूर्णांक64_t slice:7;
		uपूर्णांक64_t max2:8;
		uपूर्णांक64_t max1:8;
#अन्यथा
		uपूर्णांक64_t max1:8;
		uपूर्णांक64_t max2:8;
		uपूर्णांक64_t slice:7;
		uपूर्णांक64_t reserved_23_63:41;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_gmxx_tx_spi_max_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t max2:8;
		uपूर्णांक64_t max1:8;
#अन्यथा
		uपूर्णांक64_t max1:8;
		uपूर्णांक64_t max2:8;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण cn38xx;
पूर्ण;

जोड़ cvmx_gmxx_tx_spi_thresh अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_tx_spi_thresh_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t thresh:6;
#अन्यथा
		uपूर्णांक64_t thresh:6;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_gmxx_tx_xaui_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_gmxx_tx_xaui_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t hg_छोड़ो_hgi:2;
		uपूर्णांक64_t hg_en:1;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t ls_byp:1;
		uपूर्णांक64_t ls:2;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t uni_en:1;
		uपूर्णांक64_t dic_en:1;
#अन्यथा
		uपूर्णांक64_t dic_en:1;
		uपूर्णांक64_t uni_en:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t ls:2;
		uपूर्णांक64_t ls_byp:1;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t hg_en:1;
		uपूर्णांक64_t hg_छोड़ो_hgi:2;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
