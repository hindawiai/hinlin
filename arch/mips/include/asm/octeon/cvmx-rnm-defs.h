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

#अगर_अघोषित __CVMX_RNM_DEFS_H__
#घोषणा __CVMX_RNM_DEFS_H__

#घोषणा CVMX_RNM_BIST_STATUS (CVMX_ADD_IO_SEG(0x0001180040000008ull))
#घोषणा CVMX_RNM_CTL_STATUS (CVMX_ADD_IO_SEG(0x0001180040000000ull))
#घोषणा CVMX_RNM_EER_DBG (CVMX_ADD_IO_SEG(0x0001180040000018ull))
#घोषणा CVMX_RNM_EER_KEY (CVMX_ADD_IO_SEG(0x0001180040000010ull))
#घोषणा CVMX_RNM_SERIAL_NUM (CVMX_ADD_IO_SEG(0x0001180040000020ull))

जोड़ cvmx_rnm_bist_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rnm_bist_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t rrc:1;
		uपूर्णांक64_t mem:1;
#अन्यथा
		uपूर्णांक64_t mem:1;
		uपूर्णांक64_t rrc:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_rnm_ctl_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rnm_ctl_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t dis_mak:1;
		uपूर्णांक64_t eer_lck:1;
		uपूर्णांक64_t eer_val:1;
		uपूर्णांक64_t ent_sel:4;
		uपूर्णांक64_t exp_ent:1;
		uपूर्णांक64_t rng_rst:1;
		uपूर्णांक64_t rnm_rst:1;
		uपूर्णांक64_t rng_en:1;
		uपूर्णांक64_t ent_en:1;
#अन्यथा
		uपूर्णांक64_t ent_en:1;
		uपूर्णांक64_t rng_en:1;
		uपूर्णांक64_t rnm_rst:1;
		uपूर्णांक64_t rng_rst:1;
		uपूर्णांक64_t exp_ent:1;
		uपूर्णांक64_t ent_sel:4;
		uपूर्णांक64_t eer_val:1;
		uपूर्णांक64_t eer_lck:1;
		uपूर्णांक64_t dis_mak:1;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_rnm_ctl_status_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t rng_rst:1;
		uपूर्णांक64_t rnm_rst:1;
		uपूर्णांक64_t rng_en:1;
		uपूर्णांक64_t ent_en:1;
#अन्यथा
		uपूर्णांक64_t ent_en:1;
		uपूर्णांक64_t rng_en:1;
		uपूर्णांक64_t rnm_rst:1;
		uपूर्णांक64_t rng_rst:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_rnm_ctl_status_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t ent_sel:4;
		uपूर्णांक64_t exp_ent:1;
		uपूर्णांक64_t rng_rst:1;
		uपूर्णांक64_t rnm_rst:1;
		uपूर्णांक64_t rng_en:1;
		uपूर्णांक64_t ent_en:1;
#अन्यथा
		uपूर्णांक64_t ent_en:1;
		uपूर्णांक64_t rng_en:1;
		uपूर्णांक64_t rnm_rst:1;
		uपूर्णांक64_t rng_rst:1;
		uपूर्णांक64_t exp_ent:1;
		uपूर्णांक64_t ent_sel:4;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_rnm_ctl_status_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t eer_lck:1;
		uपूर्णांक64_t eer_val:1;
		uपूर्णांक64_t ent_sel:4;
		uपूर्णांक64_t exp_ent:1;
		uपूर्णांक64_t rng_rst:1;
		uपूर्णांक64_t rnm_rst:1;
		uपूर्णांक64_t rng_en:1;
		uपूर्णांक64_t ent_en:1;
#अन्यथा
		uपूर्णांक64_t ent_en:1;
		uपूर्णांक64_t rng_en:1;
		uपूर्णांक64_t rnm_rst:1;
		uपूर्णांक64_t rng_rst:1;
		uपूर्णांक64_t exp_ent:1;
		uपूर्णांक64_t ent_sel:4;
		uपूर्णांक64_t eer_val:1;
		uपूर्णांक64_t eer_lck:1;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_rnm_eer_dbg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rnm_eer_dbg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t dat:64;
#अन्यथा
		uपूर्णांक64_t dat:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_rnm_eer_key अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rnm_eer_key_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t key:64;
#अन्यथा
		uपूर्णांक64_t key:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_rnm_serial_num अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_rnm_serial_num_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t dat:64;
#अन्यथा
		uपूर्णांक64_t dat:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
