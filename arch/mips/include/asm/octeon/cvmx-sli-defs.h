<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2017 Cavium, Inc.
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

#अगर_अघोषित __CVMX_SLI_DEFS_H__
#घोषणा __CVMX_SLI_DEFS_H__

#समावेश <uapi/यंत्र/bitfield.h>

#घोषणा CVMX_SLI_PCIE_MSI_RCV CVMX_SLI_PCIE_MSI_RCV_FUNC()
अटल अंतरभूत uपूर्णांक64_t CVMX_SLI_PCIE_MSI_RCV_FUNC(व्योम)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN70XX & OCTEON_FAMILY_MASK:
		वापस 0x0000000000003CB0ull;
	हाल OCTEON_CNF75XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN73XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN78XX & OCTEON_FAMILY_MASK:
		अगर (OCTEON_IS_MODEL(OCTEON_CN78XX_PASS1_X))
			वापस 0x0000000000003CB0ull;
		fallthrough;
	शेष:
		वापस 0x0000000000023CB0ull;
	पूर्ण
पूर्ण


जोड़ cvmx_sli_ctl_portx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sli_ctl_portx_s अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_22_63:42,
		__BITFIELD_FIELD(uपूर्णांक64_t पूर्णांकd:1,
		__BITFIELD_FIELD(uपूर्णांक64_t पूर्णांकc:1,
		__BITFIELD_FIELD(uपूर्णांक64_t पूर्णांकb:1,
		__BITFIELD_FIELD(uपूर्णांक64_t पूर्णांकa:1,
		__BITFIELD_FIELD(uपूर्णांक64_t dis_port:1,
		__BITFIELD_FIELD(uपूर्णांक64_t रुकोl_com:1,
		__BITFIELD_FIELD(uपूर्णांक64_t पूर्णांकd_map:2,
		__BITFIELD_FIELD(uपूर्णांक64_t पूर्णांकc_map:2,
		__BITFIELD_FIELD(uपूर्णांक64_t पूर्णांकb_map:2,
		__BITFIELD_FIELD(uपूर्णांक64_t पूर्णांकa_map:2,
		__BITFIELD_FIELD(uपूर्णांक64_t ctlp_ro:1,
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_6_6:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ptlp_ro:1,
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_1_4:4,
		__BITFIELD_FIELD(uपूर्णांक64_t रुको_com:1,
		;))))))))))))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sli_mem_access_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sli_mem_access_ctl_s अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_14_63:50,
		__BITFIELD_FIELD(uपूर्णांक64_t max_word:4,
		__BITFIELD_FIELD(uपूर्णांक64_t समयr:10,
		;)))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sli_s2m_portx_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sli_s2m_portx_ctl_s अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_5_63:59,
		__BITFIELD_FIELD(uपूर्णांक64_t wind_d:1,
		__BITFIELD_FIELD(uपूर्णांक64_t bar0_d:1,
		__BITFIELD_FIELD(uपूर्णांक64_t mrrs:3,
		;))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sli_mem_access_subidx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sli_mem_access_subidx_s अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_43_63:21,
		__BITFIELD_FIELD(uपूर्णांक64_t zero:1,
		__BITFIELD_FIELD(uपूर्णांक64_t port:3,
		__BITFIELD_FIELD(uपूर्णांक64_t nmerge:1,
		__BITFIELD_FIELD(uपूर्णांक64_t esr:2,
		__BITFIELD_FIELD(uपूर्णांक64_t esw:2,
		__BITFIELD_FIELD(uपूर्णांक64_t wtype:2,
		__BITFIELD_FIELD(uपूर्णांक64_t rtype:2,
		__BITFIELD_FIELD(uपूर्णांक64_t ba:30,
		;)))))))))
	पूर्ण s;
	काष्ठा cvmx_sli_mem_access_subidx_cn68xx अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_43_63:21,
		__BITFIELD_FIELD(uपूर्णांक64_t zero:1,
		__BITFIELD_FIELD(uपूर्णांक64_t port:3,
		__BITFIELD_FIELD(uपूर्णांक64_t nmerge:1,
		__BITFIELD_FIELD(uपूर्णांक64_t esr:2,
		__BITFIELD_FIELD(uपूर्णांक64_t esw:2,
		__BITFIELD_FIELD(uपूर्णांक64_t wtype:2,
		__BITFIELD_FIELD(uपूर्णांक64_t rtype:2,
		__BITFIELD_FIELD(uपूर्णांक64_t ba:28,
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_0_1:2,
		;))))))))))
	पूर्ण cn68xx;
पूर्ण;

#पूर्ण_अगर
