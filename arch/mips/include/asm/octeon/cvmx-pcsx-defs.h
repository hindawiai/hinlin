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

#अगर_अघोषित __CVMX_PCSX_DEFS_H__
#घोषणा __CVMX_PCSX_DEFS_H__

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_ANX_ADV_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001010ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001010ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001010ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001010ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001010ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_ANX_EXT_ST_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001028ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001028ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001028ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001028ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001028ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_ANX_LP_ABIL_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001018ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001018ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001018ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001018ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001018ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_ANX_RESULTS_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001020ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001020ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001020ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001020ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001020ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_INTX_EN_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001088ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001088ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001088ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001088ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001088ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_INTX_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001080ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001080ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001080ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001080ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001080ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_LINKX_TIMER_COUNT_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001040ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001040ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001040ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001040ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001040ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_LOG_ANLX_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001090ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001090ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001090ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001090ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001090ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_MISCX_CTL_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001078ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001078ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001078ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001078ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001078ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_MRX_CONTROL_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001000ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001000ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001000ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001000ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001000ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_MRX_STATUS_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001008ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001008ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001008ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001008ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001008ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_RXX_STATES_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001058ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001058ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001058ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001058ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001058ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_RXX_SYNC_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001050ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001050ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001050ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001050ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001050ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_SGMX_AN_ADV_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001068ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001068ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001068ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001068ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001068ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_SGMX_LP_ADV_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001070ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001070ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001070ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001070ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001070ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_TXX_STATES_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001060ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001060ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001060ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001060ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001060ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSX_TX_RXX_POLARITY_REG(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001048ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001048ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001048ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0001048ull) + ((offset) + (block_id) * 0x4000ull) * 1024;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0001048ull) + ((offset) + (block_id) * 0x20000ull) * 1024;
पूर्ण

व्योम __cvmx_पूर्णांकerrupt_pcsx_पूर्णांकx_en_reg_enable(पूर्णांक index, पूर्णांक block);

जोड़ cvmx_pcsx_anx_adv_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_anx_adv_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t np:1;
		uपूर्णांक64_t reserved_14_14:1;
		uपूर्णांक64_t rem_flt:2;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t छोड़ो:2;
		uपूर्णांक64_t hfd:1;
		uपूर्णांक64_t fd:1;
		uपूर्णांक64_t reserved_0_4:5;
#अन्यथा
		uपूर्णांक64_t reserved_0_4:5;
		uपूर्णांक64_t fd:1;
		uपूर्णांक64_t hfd:1;
		uपूर्णांक64_t छोड़ो:2;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t rem_flt:2;
		uपूर्णांक64_t reserved_14_14:1;
		uपूर्णांक64_t np:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsx_anx_ext_st_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_anx_ext_st_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t thou_xfd:1;
		uपूर्णांक64_t thou_xhd:1;
		uपूर्णांक64_t thou_tfd:1;
		uपूर्णांक64_t thou_thd:1;
		uपूर्णांक64_t reserved_0_11:12;
#अन्यथा
		uपूर्णांक64_t reserved_0_11:12;
		uपूर्णांक64_t thou_thd:1;
		uपूर्णांक64_t thou_tfd:1;
		uपूर्णांक64_t thou_xhd:1;
		uपूर्णांक64_t thou_xfd:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsx_anx_lp_abil_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_anx_lp_abil_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t np:1;
		uपूर्णांक64_t ack:1;
		uपूर्णांक64_t rem_flt:2;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t छोड़ो:2;
		uपूर्णांक64_t hfd:1;
		uपूर्णांक64_t fd:1;
		uपूर्णांक64_t reserved_0_4:5;
#अन्यथा
		uपूर्णांक64_t reserved_0_4:5;
		uपूर्णांक64_t fd:1;
		uपूर्णांक64_t hfd:1;
		uपूर्णांक64_t छोड़ो:2;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t rem_flt:2;
		uपूर्णांक64_t ack:1;
		uपूर्णांक64_t np:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsx_anx_results_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_anx_results_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t छोड़ो:2;
		uपूर्णांक64_t spd:2;
		uपूर्णांक64_t an_cpt:1;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t link_ok:1;
#अन्यथा
		uपूर्णांक64_t link_ok:1;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t an_cpt:1;
		uपूर्णांक64_t spd:2;
		uपूर्णांक64_t छोड़ो:2;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsx_पूर्णांकx_en_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_पूर्णांकx_en_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t dbg_sync_en:1;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t sync_bad_en:1;
		uपूर्णांक64_t an_bad_en:1;
		uपूर्णांक64_t rxlock_en:1;
		uपूर्णांक64_t rxbad_en:1;
		uपूर्णांक64_t rxerr_en:1;
		uपूर्णांक64_t txbad_en:1;
		uपूर्णांक64_t txfअगरo_en:1;
		uपूर्णांक64_t txfअगरu_en:1;
		uपूर्णांक64_t an_err_en:1;
		uपूर्णांक64_t xmit_en:1;
		uपूर्णांक64_t lnkspd_en:1;
#अन्यथा
		uपूर्णांक64_t lnkspd_en:1;
		uपूर्णांक64_t xmit_en:1;
		uपूर्णांक64_t an_err_en:1;
		uपूर्णांक64_t txfअगरu_en:1;
		uपूर्णांक64_t txfअगरo_en:1;
		uपूर्णांक64_t txbad_en:1;
		uपूर्णांक64_t rxerr_en:1;
		uपूर्णांक64_t rxbad_en:1;
		uपूर्णांक64_t rxlock_en:1;
		uपूर्णांक64_t an_bad_en:1;
		uपूर्णांक64_t sync_bad_en:1;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t dbg_sync_en:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pcsx_पूर्णांकx_en_reg_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t sync_bad_en:1;
		uपूर्णांक64_t an_bad_en:1;
		uपूर्णांक64_t rxlock_en:1;
		uपूर्णांक64_t rxbad_en:1;
		uपूर्णांक64_t rxerr_en:1;
		uपूर्णांक64_t txbad_en:1;
		uपूर्णांक64_t txfअगरo_en:1;
		uपूर्णांक64_t txfअगरu_en:1;
		uपूर्णांक64_t an_err_en:1;
		uपूर्णांक64_t xmit_en:1;
		uपूर्णांक64_t lnkspd_en:1;
#अन्यथा
		uपूर्णांक64_t lnkspd_en:1;
		uपूर्णांक64_t xmit_en:1;
		uपूर्णांक64_t an_err_en:1;
		uपूर्णांक64_t txfअगरu_en:1;
		uपूर्णांक64_t txfअगरo_en:1;
		uपूर्णांक64_t txbad_en:1;
		uपूर्णांक64_t rxerr_en:1;
		uपूर्णांक64_t rxbad_en:1;
		uपूर्णांक64_t rxlock_en:1;
		uपूर्णांक64_t an_bad_en:1;
		uपूर्णांक64_t sync_bad_en:1;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_pcsx_पूर्णांकx_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_पूर्णांकx_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t dbg_sync:1;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t sync_bad:1;
		uपूर्णांक64_t an_bad:1;
		uपूर्णांक64_t rxlock:1;
		uपूर्णांक64_t rxbad:1;
		uपूर्णांक64_t rxerr:1;
		uपूर्णांक64_t txbad:1;
		uपूर्णांक64_t txfअगरo:1;
		uपूर्णांक64_t txfअगरu:1;
		uपूर्णांक64_t an_err:1;
		uपूर्णांक64_t xmit:1;
		uपूर्णांक64_t lnkspd:1;
#अन्यथा
		uपूर्णांक64_t lnkspd:1;
		uपूर्णांक64_t xmit:1;
		uपूर्णांक64_t an_err:1;
		uपूर्णांक64_t txfअगरu:1;
		uपूर्णांक64_t txfअगरo:1;
		uपूर्णांक64_t txbad:1;
		uपूर्णांक64_t rxerr:1;
		uपूर्णांक64_t rxbad:1;
		uपूर्णांक64_t rxlock:1;
		uपूर्णांक64_t an_bad:1;
		uपूर्णांक64_t sync_bad:1;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t dbg_sync:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pcsx_पूर्णांकx_reg_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t sync_bad:1;
		uपूर्णांक64_t an_bad:1;
		uपूर्णांक64_t rxlock:1;
		uपूर्णांक64_t rxbad:1;
		uपूर्णांक64_t rxerr:1;
		uपूर्णांक64_t txbad:1;
		uपूर्णांक64_t txfअगरo:1;
		uपूर्णांक64_t txfअगरu:1;
		uपूर्णांक64_t an_err:1;
		uपूर्णांक64_t xmit:1;
		uपूर्णांक64_t lnkspd:1;
#अन्यथा
		uपूर्णांक64_t lnkspd:1;
		uपूर्णांक64_t xmit:1;
		uपूर्णांक64_t an_err:1;
		uपूर्णांक64_t txfअगरu:1;
		uपूर्णांक64_t txfअगरo:1;
		uपूर्णांक64_t txbad:1;
		uपूर्णांक64_t rxerr:1;
		uपूर्णांक64_t rxbad:1;
		uपूर्णांक64_t rxlock:1;
		uपूर्णांक64_t an_bad:1;
		uपूर्णांक64_t sync_bad:1;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_pcsx_linkx_समयr_count_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_linkx_समयr_count_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t count:16;
#अन्यथा
		uपूर्णांक64_t count:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsx_log_anlx_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_log_anlx_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t lafअगरovfl:1;
		uपूर्णांक64_t la_en:1;
		uपूर्णांक64_t pkt_sz:2;
#अन्यथा
		uपूर्णांक64_t pkt_sz:2;
		uपूर्णांक64_t la_en:1;
		uपूर्णांक64_t lafअगरovfl:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsx_miscx_ctl_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_miscx_ctl_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t sgmii:1;
		uपूर्णांक64_t gmxeno:1;
		uपूर्णांक64_t loopbck2:1;
		uपूर्णांक64_t mac_phy:1;
		uपूर्णांक64_t mode:1;
		uपूर्णांक64_t an_ovrd:1;
		uपूर्णांक64_t samp_pt:7;
#अन्यथा
		uपूर्णांक64_t samp_pt:7;
		uपूर्णांक64_t an_ovrd:1;
		uपूर्णांक64_t mode:1;
		uपूर्णांक64_t mac_phy:1;
		uपूर्णांक64_t loopbck2:1;
		uपूर्णांक64_t gmxeno:1;
		uपूर्णांक64_t sgmii:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsx_mrx_control_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_mrx_control_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t loopbck1:1;
		uपूर्णांक64_t spdlsb:1;
		uपूर्णांक64_t an_en:1;
		uपूर्णांक64_t pwr_dn:1;
		uपूर्णांक64_t reserved_10_10:1;
		uपूर्णांक64_t rst_an:1;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t coltst:1;
		uपूर्णांक64_t spdmsb:1;
		uपूर्णांक64_t uni:1;
		uपूर्णांक64_t reserved_0_4:5;
#अन्यथा
		uपूर्णांक64_t reserved_0_4:5;
		uपूर्णांक64_t uni:1;
		uपूर्णांक64_t spdmsb:1;
		uपूर्णांक64_t coltst:1;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t rst_an:1;
		uपूर्णांक64_t reserved_10_10:1;
		uपूर्णांक64_t pwr_dn:1;
		uपूर्णांक64_t an_en:1;
		uपूर्णांक64_t spdlsb:1;
		uपूर्णांक64_t loopbck1:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsx_mrx_status_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_mrx_status_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t hun_t4:1;
		uपूर्णांक64_t hun_xfd:1;
		uपूर्णांक64_t hun_xhd:1;
		uपूर्णांक64_t ten_fd:1;
		uपूर्णांक64_t ten_hd:1;
		uपूर्णांक64_t hun_t2fd:1;
		uपूर्णांक64_t hun_t2hd:1;
		uपूर्णांक64_t ext_st:1;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t prb_sup:1;
		uपूर्णांक64_t an_cpt:1;
		uपूर्णांक64_t rm_flt:1;
		uपूर्णांक64_t an_abil:1;
		uपूर्णांक64_t lnk_st:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t extnd:1;
#अन्यथा
		uपूर्णांक64_t extnd:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t lnk_st:1;
		uपूर्णांक64_t an_abil:1;
		uपूर्णांक64_t rm_flt:1;
		uपूर्णांक64_t an_cpt:1;
		uपूर्णांक64_t prb_sup:1;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t ext_st:1;
		uपूर्णांक64_t hun_t2hd:1;
		uपूर्णांक64_t hun_t2fd:1;
		uपूर्णांक64_t ten_hd:1;
		uपूर्णांक64_t ten_fd:1;
		uपूर्णांक64_t hun_xhd:1;
		uपूर्णांक64_t hun_xfd:1;
		uपूर्णांक64_t hun_t4:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsx_rxx_states_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_rxx_states_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t rx_bad:1;
		uपूर्णांक64_t rx_st:5;
		uपूर्णांक64_t sync_bad:1;
		uपूर्णांक64_t sync:4;
		uपूर्णांक64_t an_bad:1;
		uपूर्णांक64_t an_st:4;
#अन्यथा
		uपूर्णांक64_t an_st:4;
		uपूर्णांक64_t an_bad:1;
		uपूर्णांक64_t sync:4;
		uपूर्णांक64_t sync_bad:1;
		uपूर्णांक64_t rx_st:5;
		uपूर्णांक64_t rx_bad:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsx_rxx_sync_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_rxx_sync_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t sync:1;
		uपूर्णांक64_t bit_lock:1;
#अन्यथा
		uपूर्णांक64_t bit_lock:1;
		uपूर्णांक64_t sync:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsx_sgmx_an_adv_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_sgmx_an_adv_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t link:1;
		uपूर्णांक64_t ack:1;
		uपूर्णांक64_t reserved_13_13:1;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t speed:2;
		uपूर्णांक64_t reserved_1_9:9;
		uपूर्णांक64_t one:1;
#अन्यथा
		uपूर्णांक64_t one:1;
		uपूर्णांक64_t reserved_1_9:9;
		uपूर्णांक64_t speed:2;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t reserved_13_13:1;
		uपूर्णांक64_t ack:1;
		uपूर्णांक64_t link:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsx_sgmx_lp_adv_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_sgmx_lp_adv_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t link:1;
		uपूर्णांक64_t reserved_13_14:2;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t speed:2;
		uपूर्णांक64_t reserved_1_9:9;
		uपूर्णांक64_t one:1;
#अन्यथा
		uपूर्णांक64_t one:1;
		uपूर्णांक64_t reserved_1_9:9;
		uपूर्णांक64_t speed:2;
		uपूर्णांक64_t dup:1;
		uपूर्णांक64_t reserved_13_14:2;
		uपूर्णांक64_t link:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsx_txx_states_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_txx_states_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t xmit:2;
		uपूर्णांक64_t tx_bad:1;
		uपूर्णांक64_t ord_st:4;
#अन्यथा
		uपूर्णांक64_t ord_st:4;
		uपूर्णांक64_t tx_bad:1;
		uपूर्णांक64_t xmit:2;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsx_tx_rxx_polarity_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsx_tx_rxx_polarity_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t rxovrd:1;
		uपूर्णांक64_t स्वतःrxpl:1;
		uपूर्णांक64_t rxplrt:1;
		uपूर्णांक64_t txplrt:1;
#अन्यथा
		uपूर्णांक64_t txplrt:1;
		uपूर्णांक64_t rxplrt:1;
		uपूर्णांक64_t स्वतःrxpl:1;
		uपूर्णांक64_t rxovrd:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
