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

#अगर_अघोषित __CVMX_L2D_DEFS_H__
#घोषणा __CVMX_L2D_DEFS_H__

#घोषणा CVMX_L2D_ERR	(CVMX_ADD_IO_SEG(0x0001180080000010ull))
#घोषणा CVMX_L2D_FUS3	(CVMX_ADD_IO_SEG(0x00011800800007B8ull))


जोड़ cvmx_l2d_err अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_l2d_err_s अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_6_63:58,
		__BITFIELD_FIELD(uपूर्णांक64_t bmhclsel:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ded_err:1,
		__BITFIELD_FIELD(uपूर्णांक64_t sec_err:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ded_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t sec_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ecc_ena:1,
		;)))))))
	पूर्ण s;
पूर्ण;

जोड़ cvmx_l2d_fus3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_l2d_fus3_s अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_40_63:24,
		__BITFIELD_FIELD(uपूर्णांक64_t ema_ctl:3,
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_34_36:3,
		__BITFIELD_FIELD(uपूर्णांक64_t q3fus:34,
		;))))
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
