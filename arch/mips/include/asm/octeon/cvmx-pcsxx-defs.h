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

#अगर_अघोषित __CVMX_PCSXX_DEFS_H__
#घोषणा __CVMX_PCSXX_DEFS_H__

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_10GBX_STATUS_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000828ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000828ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000828ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000828ull) + (block_id) * 0x1000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_BIST_STATUS_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000870ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000870ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000870ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000870ull) + (block_id) * 0x1000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_BIT_LOCK_STATUS_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000850ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000850ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000850ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000850ull) + (block_id) * 0x1000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_CONTROL1_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000800ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000800ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000800ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000800ull) + (block_id) * 0x1000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_CONTROL2_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000818ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000818ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000818ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000818ull) + (block_id) * 0x1000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_INT_EN_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000860ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000860ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000860ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000860ull) + (block_id) * 0x1000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_INT_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000858ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000858ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000858ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000858ull) + (block_id) * 0x1000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_LOG_ANL_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000868ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000868ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000868ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000868ull) + (block_id) * 0x1000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_MISC_CTL_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000848ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000848ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000848ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000848ull) + (block_id) * 0x1000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_RX_SYNC_STATES_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000838ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000838ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000838ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000838ull) + (block_id) * 0x1000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_SPD_ABIL_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000810ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000810ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000810ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000810ull) + (block_id) * 0x1000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_STATUS1_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000808ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000808ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000808ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000808ull) + (block_id) * 0x1000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_STATUS2_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000820ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000820ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000820ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000820ull) + (block_id) * 0x1000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_TX_RX_POLARITY_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000840ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000840ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000840ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000840ull) + (block_id) * 0x1000000ull;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t CVMX_PCSXX_TX_RX_STATES_REG(अचिन्हित दीर्घ block_id)
अणु
	चयन (cvmx_get_octeon_family()) अणु
	हाल OCTEON_CN56XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN66XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000830ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN52XX & OCTEON_FAMILY_MASK:
	हाल OCTEON_CN63XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000830ull) + (block_id) * 0x8000000ull;
	हाल OCTEON_CN68XX & OCTEON_FAMILY_MASK:
		वापस CVMX_ADD_IO_SEG(0x00011800B0000830ull) + (block_id) * 0x1000000ull;
	पूर्ण
	वापस CVMX_ADD_IO_SEG(0x00011800B0000830ull) + (block_id) * 0x1000000ull;
पूर्ण

व्योम __cvmx_पूर्णांकerrupt_pcsxx_पूर्णांक_en_reg_enable(पूर्णांक index);

जोड़ cvmx_pcsxx_10gbx_status_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_10gbx_status_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t alignd:1;
		uपूर्णांक64_t pattst:1;
		uपूर्णांक64_t reserved_4_10:7;
		uपूर्णांक64_t l3sync:1;
		uपूर्णांक64_t l2sync:1;
		uपूर्णांक64_t l1sync:1;
		uपूर्णांक64_t l0sync:1;
#अन्यथा
		uपूर्णांक64_t l0sync:1;
		uपूर्णांक64_t l1sync:1;
		uपूर्णांक64_t l2sync:1;
		uपूर्णांक64_t l3sync:1;
		uपूर्णांक64_t reserved_4_10:7;
		uपूर्णांक64_t pattst:1;
		uपूर्णांक64_t alignd:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsxx_bist_status_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_bist_status_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t bist_status:1;
#अन्यथा
		uपूर्णांक64_t bist_status:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsxx_bit_lock_status_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_bit_lock_status_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t bitlck3:1;
		uपूर्णांक64_t bitlck2:1;
		uपूर्णांक64_t bitlck1:1;
		uपूर्णांक64_t bitlck0:1;
#अन्यथा
		uपूर्णांक64_t bitlck0:1;
		uपूर्णांक64_t bitlck1:1;
		uपूर्णांक64_t bitlck2:1;
		uपूर्णांक64_t bitlck3:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsxx_control1_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_control1_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t loopbck1:1;
		uपूर्णांक64_t spdsel1:1;
		uपूर्णांक64_t reserved_12_12:1;
		uपूर्णांक64_t lo_pwr:1;
		uपूर्णांक64_t reserved_7_10:4;
		uपूर्णांक64_t spdsel0:1;
		uपूर्णांक64_t spd:4;
		uपूर्णांक64_t reserved_0_1:2;
#अन्यथा
		uपूर्णांक64_t reserved_0_1:2;
		uपूर्णांक64_t spd:4;
		uपूर्णांक64_t spdsel0:1;
		uपूर्णांक64_t reserved_7_10:4;
		uपूर्णांक64_t lo_pwr:1;
		uपूर्णांक64_t reserved_12_12:1;
		uपूर्णांक64_t spdsel1:1;
		uपूर्णांक64_t loopbck1:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsxx_control2_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_control2_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t type:2;
#अन्यथा
		uपूर्णांक64_t type:2;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsxx_पूर्णांक_en_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_पूर्णांक_en_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t dbg_sync_en:1;
		uपूर्णांक64_t algnlos_en:1;
		uपूर्णांक64_t synlos_en:1;
		uपूर्णांक64_t bitlckls_en:1;
		uपूर्णांक64_t rxsynbad_en:1;
		uपूर्णांक64_t rxbad_en:1;
		uपूर्णांक64_t txflt_en:1;
#अन्यथा
		uपूर्णांक64_t txflt_en:1;
		uपूर्णांक64_t rxbad_en:1;
		uपूर्णांक64_t rxsynbad_en:1;
		uपूर्णांक64_t bitlckls_en:1;
		uपूर्णांक64_t synlos_en:1;
		uपूर्णांक64_t algnlos_en:1;
		uपूर्णांक64_t dbg_sync_en:1;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pcsxx_पूर्णांक_en_reg_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t algnlos_en:1;
		uपूर्णांक64_t synlos_en:1;
		uपूर्णांक64_t bitlckls_en:1;
		uपूर्णांक64_t rxsynbad_en:1;
		uपूर्णांक64_t rxbad_en:1;
		uपूर्णांक64_t txflt_en:1;
#अन्यथा
		uपूर्णांक64_t txflt_en:1;
		uपूर्णांक64_t rxbad_en:1;
		uपूर्णांक64_t rxsynbad_en:1;
		uपूर्णांक64_t bitlckls_en:1;
		uपूर्णांक64_t synlos_en:1;
		uपूर्णांक64_t algnlos_en:1;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_pcsxx_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_पूर्णांक_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t dbg_sync:1;
		uपूर्णांक64_t algnlos:1;
		uपूर्णांक64_t synlos:1;
		uपूर्णांक64_t bitlckls:1;
		uपूर्णांक64_t rxsynbad:1;
		uपूर्णांक64_t rxbad:1;
		uपूर्णांक64_t txflt:1;
#अन्यथा
		uपूर्णांक64_t txflt:1;
		uपूर्णांक64_t rxbad:1;
		uपूर्णांक64_t rxsynbad:1;
		uपूर्णांक64_t bitlckls:1;
		uपूर्णांक64_t synlos:1;
		uपूर्णांक64_t algnlos:1;
		uपूर्णांक64_t dbg_sync:1;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pcsxx_पूर्णांक_reg_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t algnlos:1;
		uपूर्णांक64_t synlos:1;
		uपूर्णांक64_t bitlckls:1;
		uपूर्णांक64_t rxsynbad:1;
		uपूर्णांक64_t rxbad:1;
		uपूर्णांक64_t txflt:1;
#अन्यथा
		uपूर्णांक64_t txflt:1;
		uपूर्णांक64_t rxbad:1;
		uपूर्णांक64_t rxsynbad:1;
		uपूर्णांक64_t bitlckls:1;
		uपूर्णांक64_t synlos:1;
		uपूर्णांक64_t algnlos:1;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_pcsxx_log_anl_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_log_anl_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t enc_mode:1;
		uपूर्णांक64_t drop_ln:2;
		uपूर्णांक64_t lafअगरovfl:1;
		uपूर्णांक64_t la_en:1;
		uपूर्णांक64_t pkt_sz:2;
#अन्यथा
		uपूर्णांक64_t pkt_sz:2;
		uपूर्णांक64_t la_en:1;
		uपूर्णांक64_t lafअगरovfl:1;
		uपूर्णांक64_t drop_ln:2;
		uपूर्णांक64_t enc_mode:1;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsxx_misc_ctl_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_misc_ctl_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t tx_swap:1;
		uपूर्णांक64_t rx_swap:1;
		uपूर्णांक64_t xaui:1;
		uपूर्णांक64_t gmxeno:1;
#अन्यथा
		uपूर्णांक64_t gmxeno:1;
		uपूर्णांक64_t xaui:1;
		uपूर्णांक64_t rx_swap:1;
		uपूर्णांक64_t tx_swap:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsxx_rx_sync_states_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_rx_sync_states_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t sync3st:4;
		uपूर्णांक64_t sync2st:4;
		uपूर्णांक64_t sync1st:4;
		uपूर्णांक64_t sync0st:4;
#अन्यथा
		uपूर्णांक64_t sync0st:4;
		uपूर्णांक64_t sync1st:4;
		uपूर्णांक64_t sync2st:4;
		uपूर्णांक64_t sync3st:4;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsxx_spd_abil_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_spd_abil_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t tenpasst:1;
		uपूर्णांक64_t tengb:1;
#अन्यथा
		uपूर्णांक64_t tengb:1;
		uपूर्णांक64_t tenpasst:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsxx_status1_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_status1_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t flt:1;
		uपूर्णांक64_t reserved_3_6:4;
		uपूर्णांक64_t rcv_lnk:1;
		uपूर्णांक64_t lpable:1;
		uपूर्णांक64_t reserved_0_0:1;
#अन्यथा
		uपूर्णांक64_t reserved_0_0:1;
		uपूर्णांक64_t lpable:1;
		uपूर्णांक64_t rcv_lnk:1;
		uपूर्णांक64_t reserved_3_6:4;
		uपूर्णांक64_t flt:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsxx_status2_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_status2_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t dev:2;
		uपूर्णांक64_t reserved_12_13:2;
		uपूर्णांक64_t xmtflt:1;
		uपूर्णांक64_t rcvflt:1;
		uपूर्णांक64_t reserved_3_9:7;
		uपूर्णांक64_t tengb_w:1;
		uपूर्णांक64_t tengb_x:1;
		uपूर्णांक64_t tengb_r:1;
#अन्यथा
		uपूर्णांक64_t tengb_r:1;
		uपूर्णांक64_t tengb_x:1;
		uपूर्णांक64_t tengb_w:1;
		uपूर्णांक64_t reserved_3_9:7;
		uपूर्णांक64_t rcvflt:1;
		uपूर्णांक64_t xmtflt:1;
		uपूर्णांक64_t reserved_12_13:2;
		uपूर्णांक64_t dev:2;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pcsxx_tx_rx_polarity_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_tx_rx_polarity_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t xor_rxplrt:4;
		uपूर्णांक64_t xor_txplrt:4;
		uपूर्णांक64_t rxplrt:1;
		uपूर्णांक64_t txplrt:1;
#अन्यथा
		uपूर्णांक64_t txplrt:1;
		uपूर्णांक64_t rxplrt:1;
		uपूर्णांक64_t xor_txplrt:4;
		uपूर्णांक64_t xor_rxplrt:4;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pcsxx_tx_rx_polarity_reg_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t rxplrt:1;
		uपूर्णांक64_t txplrt:1;
#अन्यथा
		uपूर्णांक64_t txplrt:1;
		uपूर्णांक64_t rxplrt:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
पूर्ण;

जोड़ cvmx_pcsxx_tx_rx_states_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pcsxx_tx_rx_states_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t term_err:1;
		uपूर्णांक64_t syn3bad:1;
		uपूर्णांक64_t syn2bad:1;
		uपूर्णांक64_t syn1bad:1;
		uपूर्णांक64_t syn0bad:1;
		uपूर्णांक64_t rxbad:1;
		uपूर्णांक64_t algn_st:3;
		uपूर्णांक64_t rx_st:2;
		uपूर्णांक64_t tx_st:3;
#अन्यथा
		uपूर्णांक64_t tx_st:3;
		uपूर्णांक64_t rx_st:2;
		uपूर्णांक64_t algn_st:3;
		uपूर्णांक64_t rxbad:1;
		uपूर्णांक64_t syn0bad:1;
		uपूर्णांक64_t syn1bad:1;
		uपूर्णांक64_t syn2bad:1;
		uपूर्णांक64_t syn3bad:1;
		uपूर्णांक64_t term_err:1;
		uपूर्णांक64_t reserved_14_63:50;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pcsxx_tx_rx_states_reg_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t syn3bad:1;
		uपूर्णांक64_t syn2bad:1;
		uपूर्णांक64_t syn1bad:1;
		uपूर्णांक64_t syn0bad:1;
		uपूर्णांक64_t rxbad:1;
		uपूर्णांक64_t algn_st:3;
		uपूर्णांक64_t rx_st:2;
		uपूर्णांक64_t tx_st:3;
#अन्यथा
		uपूर्णांक64_t tx_st:3;
		uपूर्णांक64_t rx_st:2;
		uपूर्णांक64_t algn_st:3;
		uपूर्णांक64_t rxbad:1;
		uपूर्णांक64_t syn0bad:1;
		uपूर्णांक64_t syn1bad:1;
		uपूर्णांक64_t syn2bad:1;
		uपूर्णांक64_t syn3bad:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
पूर्ण;

#पूर्ण_अगर
