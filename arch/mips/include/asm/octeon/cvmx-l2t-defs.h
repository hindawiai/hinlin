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

#अगर_अघोषित __CVMX_L2T_DEFS_H__
#घोषणा __CVMX_L2T_DEFS_H__

#समावेश <uapi/यंत्र/bitfield.h>

#घोषणा CVMX_L2T_ERR	(CVMX_ADD_IO_SEG(0x0001180080000008ull))


जोड़ cvmx_l2t_err अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_l2t_err_s अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_29_63:35,
		__BITFIELD_FIELD(uपूर्णांक64_t fadru:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lck_पूर्णांकena2:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lckerr2:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lck_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lckerr:1,
		__BITFIELD_FIELD(uपूर्णांक64_t fset:3,
		__BITFIELD_FIELD(uपूर्णांक64_t fadr:10,
		__BITFIELD_FIELD(uपूर्णांक64_t fsyn:6,
		__BITFIELD_FIELD(uपूर्णांक64_t ded_err:1,
		__BITFIELD_FIELD(uपूर्णांक64_t sec_err:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ded_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t sec_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ecc_ena:1,
		;))))))))))))))
	पूर्ण s;
	काष्ठा cvmx_l2t_err_cn30xx अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_28_63:36,
		__BITFIELD_FIELD(uपूर्णांक64_t lck_पूर्णांकena2:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lckerr2:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lck_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lckerr:1,
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_23_23:1,
		__BITFIELD_FIELD(uपूर्णांक64_t fset:2,
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_19_20:2,
		__BITFIELD_FIELD(uपूर्णांक64_t fadr:8,
		__BITFIELD_FIELD(uपूर्णांक64_t fsyn:6,
		__BITFIELD_FIELD(uपूर्णांक64_t ded_err:1,
		__BITFIELD_FIELD(uपूर्णांक64_t sec_err:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ded_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t sec_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ecc_ena:1,
		;)))))))))))))))
	पूर्ण cn30xx;
	काष्ठा cvmx_l2t_err_cn31xx अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_28_63:36,
		__BITFIELD_FIELD(uपूर्णांक64_t lck_पूर्णांकena2:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lckerr2:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lck_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lckerr:1,
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_23_23:1,
		__BITFIELD_FIELD(uपूर्णांक64_t fset:2,
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_20_20:1,
		__BITFIELD_FIELD(uपूर्णांक64_t fadr:9,
		__BITFIELD_FIELD(uपूर्णांक64_t fsyn:6,
		__BITFIELD_FIELD(uपूर्णांक64_t ded_err:1,
		__BITFIELD_FIELD(uपूर्णांक64_t sec_err:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ded_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t sec_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ecc_ena:1,
		;)))))))))))))))
	पूर्ण cn31xx;
	काष्ठा cvmx_l2t_err_cn38xx अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_28_63:36,
		__BITFIELD_FIELD(uपूर्णांक64_t lck_पूर्णांकena2:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lckerr2:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lck_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lckerr:1,
		__BITFIELD_FIELD(uपूर्णांक64_t fset:3,
		__BITFIELD_FIELD(uपूर्णांक64_t fadr:10,
		__BITFIELD_FIELD(uपूर्णांक64_t fsyn:6,
		__BITFIELD_FIELD(uपूर्णांक64_t ded_err:1,
		__BITFIELD_FIELD(uपूर्णांक64_t sec_err:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ded_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t sec_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ecc_ena:1,
		;)))))))))))))
	पूर्ण cn38xx;
	काष्ठा cvmx_l2t_err_cn50xx अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_28_63:36,
		__BITFIELD_FIELD(uपूर्णांक64_t lck_पूर्णांकena2:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lckerr2:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lck_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lckerr:1,
		__BITFIELD_FIELD(uपूर्णांक64_t fset:3,
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_18_20:3,
		__BITFIELD_FIELD(uपूर्णांक64_t fadr:7,
		__BITFIELD_FIELD(uपूर्णांक64_t fsyn:6,
		__BITFIELD_FIELD(uपूर्णांक64_t ded_err:1,
		__BITFIELD_FIELD(uपूर्णांक64_t sec_err:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ded_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t sec_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ecc_ena:1,
		;))))))))))))))
	पूर्ण cn50xx;
	काष्ठा cvmx_l2t_err_cn52xx अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_28_63:36,
		__BITFIELD_FIELD(uपूर्णांक64_t lck_पूर्णांकena2:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lckerr2:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lck_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t lckerr:1,
		__BITFIELD_FIELD(uपूर्णांक64_t fset:3,
		__BITFIELD_FIELD(uपूर्णांक64_t reserved_20_20:1,
		__BITFIELD_FIELD(uपूर्णांक64_t fadr:9,
		__BITFIELD_FIELD(uपूर्णांक64_t fsyn:6,
		__BITFIELD_FIELD(uपूर्णांक64_t ded_err:1,
		__BITFIELD_FIELD(uपूर्णांक64_t sec_err:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ded_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t sec_पूर्णांकena:1,
		__BITFIELD_FIELD(uपूर्णांक64_t ecc_ena:1,
		;))))))))))))))
	पूर्ण cn52xx;
पूर्ण;

#पूर्ण_अगर
