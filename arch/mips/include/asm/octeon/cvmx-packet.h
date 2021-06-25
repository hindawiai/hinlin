<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2008 Cavium Networks
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

/*
 * Packet buffer defines.
 */

#अगर_अघोषित __CVMX_PACKET_H__
#घोषणा __CVMX_PACKET_H__

/**
 * This काष्ठाure defines a buffer poपूर्णांकer on Octeon
 */
जोड़ cvmx_buf_ptr अणु
	व्योम *ptr;
	uपूर्णांक64_t u64;
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/* अगर set, invert the "free" pick of the overall
		 * packet. HW always sets this bit to 0 on inbound
		 * packet */
		uपूर्णांक64_t i:1;

		/* Indicates the amount to back up to get to the
		 * buffer start in cache lines. In most हालs this is
		 * less than one complete cache line, so the value is
		 * zero */
		uपूर्णांक64_t back:4;
		/* The pool that the buffer came from / goes to */
		uपूर्णांक64_t pool:3;
		/* The size of the segment poपूर्णांकed to by addr (in bytes) */
		uपूर्णांक64_t size:16;
		/* Poपूर्णांकer to the first byte of the data, NOT buffer */
		uपूर्णांक64_t addr:40;
#अन्यथा
	        uपूर्णांक64_t addr:40;
	        uपूर्णांक64_t size:16;
	        uपूर्णांक64_t pool:3;
	        uपूर्णांक64_t back:4;
	        uपूर्णांक64_t i:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर /*  __CVMX_PACKET_H__ */
