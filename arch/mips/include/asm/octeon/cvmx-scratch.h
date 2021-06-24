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

/**
 *
 * This file provides support क्रम the processor local scratch memory.
 * Scratch memory is byte addressable - all addresses are byte addresses.
 *
 */

#अगर_अघोषित __CVMX_SCRATCH_H__
#घोषणा __CVMX_SCRATCH_H__

/*
 * Note: This define must be a दीर्घ, not a दीर्घ दीर्घ in order to
 * compile without warnings क्रम both 32bit and 64bit.
 */
#घोषणा CVMX_SCRATCH_BASE	(-32768l)	/* 0xffffffffffff8000 */

/**
 * Reads an 8 bit value from the processor local scratchpad memory.
 *
 * @address: byte address to पढ़ो from
 *
 * Returns value पढ़ो
 */
अटल अंतरभूत uपूर्णांक8_t cvmx_scratch_पढ़ो8(uपूर्णांक64_t address)
अणु
	वापस *CASTPTR(अस्थिर uपूर्णांक8_t, CVMX_SCRATCH_BASE + address);
पूर्ण

/**
 * Reads a 16 bit value from the processor local scratchpad memory.
 *
 * @address: byte address to पढ़ो from
 *
 * Returns value पढ़ो
 */
अटल अंतरभूत uपूर्णांक16_t cvmx_scratch_पढ़ो16(uपूर्णांक64_t address)
अणु
	वापस *CASTPTR(अस्थिर uपूर्णांक16_t, CVMX_SCRATCH_BASE + address);
पूर्ण

/**
 * Reads a 32 bit value from the processor local scratchpad memory.
 *
 * @address: byte address to पढ़ो from
 *
 * Returns value पढ़ो
 */
अटल अंतरभूत uपूर्णांक32_t cvmx_scratch_पढ़ो32(uपूर्णांक64_t address)
अणु
	वापस *CASTPTR(अस्थिर uपूर्णांक32_t, CVMX_SCRATCH_BASE + address);
पूर्ण

/**
 * Reads a 64 bit value from the processor local scratchpad memory.
 *
 * @address: byte address to पढ़ो from
 *
 * Returns value पढ़ो
 */
अटल अंतरभूत uपूर्णांक64_t cvmx_scratch_पढ़ो64(uपूर्णांक64_t address)
अणु
	वापस *CASTPTR(अस्थिर uपूर्णांक64_t, CVMX_SCRATCH_BASE + address);
पूर्ण

/**
 * Writes an 8 bit value to the processor local scratchpad memory.
 *
 * @address: byte address to ग_लिखो to
 * @value:   value to ग_लिखो
 */
अटल अंतरभूत व्योम cvmx_scratch_ग_लिखो8(uपूर्णांक64_t address, uपूर्णांक64_t value)
अणु
	*CASTPTR(अस्थिर uपूर्णांक8_t, CVMX_SCRATCH_BASE + address) =
	    (uपूर्णांक8_t) value;
पूर्ण

/**
 * Writes a 32 bit value to the processor local scratchpad memory.
 *
 * @address: byte address to ग_लिखो to
 * @value:   value to ग_लिखो
 */
अटल अंतरभूत व्योम cvmx_scratch_ग_लिखो16(uपूर्णांक64_t address, uपूर्णांक64_t value)
अणु
	*CASTPTR(अस्थिर uपूर्णांक16_t, CVMX_SCRATCH_BASE + address) =
	    (uपूर्णांक16_t) value;
पूर्ण

/**
 * Writes a 16 bit value to the processor local scratchpad memory.
 *
 * @address: byte address to ग_लिखो to
 * @value:   value to ग_लिखो
 */
अटल अंतरभूत व्योम cvmx_scratch_ग_लिखो32(uपूर्णांक64_t address, uपूर्णांक64_t value)
अणु
	*CASTPTR(अस्थिर uपूर्णांक32_t, CVMX_SCRATCH_BASE + address) =
	    (uपूर्णांक32_t) value;
पूर्ण

/**
 * Writes a 64 bit value to the processor local scratchpad memory.
 *
 * @address: byte address to ग_लिखो to
 * @value:   value to ग_लिखो
 */
अटल अंतरभूत व्योम cvmx_scratch_ग_लिखो64(uपूर्णांक64_t address, uपूर्णांक64_t value)
अणु
	*CASTPTR(अस्थिर uपूर्णांक64_t, CVMX_SCRATCH_BASE + address) = value;
पूर्ण

#पूर्ण_अगर /* __CVMX_SCRATCH_H__ */
