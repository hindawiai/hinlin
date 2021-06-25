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
 * Interface to the hardware Fetch and Add Unit.
 */

#अगर_अघोषित __CVMX_FAU_H__
#घोषणा __CVMX_FAU_H__

/*
 * Octeon Fetch and Add Unit (FAU)
 */

#घोषणा CVMX_FAU_LOAD_IO_ADDRESS    cvmx_build_io_address(0x1e, 0)
#घोषणा CVMX_FAU_BITS_SCRADDR	    63, 56
#घोषणा CVMX_FAU_BITS_LEN	    55, 48
#घोषणा CVMX_FAU_BITS_INEVAL	    35, 14
#घोषणा CVMX_FAU_BITS_TAGWAIT	    13, 13
#घोषणा CVMX_FAU_BITS_NOADD	    13, 13
#घोषणा CVMX_FAU_BITS_SIZE	    12, 11
#घोषणा CVMX_FAU_BITS_REGISTER	    10, 0

प्रकार क्रमागत अणु
	CVMX_FAU_OP_SIZE_8 = 0,
	CVMX_FAU_OP_SIZE_16 = 1,
	CVMX_FAU_OP_SIZE_32 = 2,
	CVMX_FAU_OP_SIZE_64 = 3
पूर्ण cvmx_fau_op_माप_प्रकार;

/**
 * Tagरुको वापस definition. If a समयout occurs, the error
 * bit will be set. Otherwise the value of the रेजिस्टर beक्रमe
 * the update will be वापसed.
 */
प्रकार काष्ठा अणु
	uपूर्णांक64_t error:1;
	पूर्णांक64_t value:63;
पूर्ण cvmx_fau_tagरुको64_t;

/**
 * Tagरुको वापस definition. If a समयout occurs, the error
 * bit will be set. Otherwise the value of the रेजिस्टर beक्रमe
 * the update will be वापसed.
 */
प्रकार काष्ठा अणु
	uपूर्णांक64_t error:1;
	पूर्णांक32_t value:31;
पूर्ण cvmx_fau_tagरुको32_t;

/**
 * Tagरुको वापस definition. If a समयout occurs, the error
 * bit will be set. Otherwise the value of the रेजिस्टर beक्रमe
 * the update will be वापसed.
 */
प्रकार काष्ठा अणु
	uपूर्णांक64_t error:1;
	पूर्णांक16_t value:15;
पूर्ण cvmx_fau_tagरुको16_t;

/**
 * Tagरुको वापस definition. If a समयout occurs, the error
 * bit will be set. Otherwise the value of the रेजिस्टर beक्रमe
 * the update will be वापसed.
 */
प्रकार काष्ठा अणु
	uपूर्णांक64_t error:1;
	पूर्णांक8_t value:7;
पूर्ण cvmx_fau_tagरुको8_t;

/**
 * Asynchronous tagरुको वापस definition. If a समयout occurs,
 * the error bit will be set. Otherwise the value of the
 * रेजिस्टर beक्रमe the update will be वापसed.
 */
प्रकार जोड़ अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
		uपूर्णांक64_t invalid:1;
		uपूर्णांक64_t data:63;	/* unpredictable अगर invalid is set */
	पूर्ण s;
पूर्ण cvmx_fau_async_tagरुको_result_t;

#अगर_घोषित __BIG_ENDIAN_BITFIELD
#घोषणा SWIZZLE_8  0
#घोषणा SWIZZLE_16 0
#घोषणा SWIZZLE_32 0
#अन्यथा
#घोषणा SWIZZLE_8  0x7
#घोषणा SWIZZLE_16 0x6
#घोषणा SWIZZLE_32 0x4
#पूर्ण_अगर

/**
 * Builds a store I/O address क्रम writing to the FAU
 *
 * @noadd:  0 = Store value is atomically added to the current value
 *		 1 = Store value is atomically written over the current value
 * @reg:    FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		 - Step by 2 क्रम 16 bit access.
 *		 - Step by 4 क्रम 32 bit access.
 *		 - Step by 8 क्रम 64 bit access.
 * Returns Address to store क्रम atomic update
 */
अटल अंतरभूत uपूर्णांक64_t __cvmx_fau_store_address(uपूर्णांक64_t noadd, uपूर्णांक64_t reg)
अणु
	वापस CVMX_ADD_IO_SEG(CVMX_FAU_LOAD_IO_ADDRESS) |
	       cvmx_build_bits(CVMX_FAU_BITS_NOADD, noadd) |
	       cvmx_build_bits(CVMX_FAU_BITS_REGISTER, reg);
पूर्ण

/**
 * Builds a I/O address क्रम accessing the FAU
 *
 * @tagरुको: Should the atomic add रुको क्रम the current tag चयन
 *		  operation to complete.
 *		  - 0 = Don't रुको
 *		  - 1 = Wait क्रम tag चयन to complete
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 2 क्रम 16 bit access.
 *		  - Step by 4 क्रम 32 bit access.
 *		  - Step by 8 क्रम 64 bit access.
 * @value:   Signed value to add.
 *		  Note: When perक्रमming 32 and 64 bit access, only the low
 *		  22 bits are available.
 * Returns Address to पढ़ो from क्रम atomic update
 */
अटल अंतरभूत uपूर्णांक64_t __cvmx_fau_atomic_address(uपूर्णांक64_t tagरुको, uपूर्णांक64_t reg,
						 पूर्णांक64_t value)
अणु
	वापस CVMX_ADD_IO_SEG(CVMX_FAU_LOAD_IO_ADDRESS) |
	       cvmx_build_bits(CVMX_FAU_BITS_INEVAL, value) |
	       cvmx_build_bits(CVMX_FAU_BITS_TAGWAIT, tagरुको) |
	       cvmx_build_bits(CVMX_FAU_BITS_REGISTER, reg);
पूर्ण

/**
 * Perक्रमm an atomic 64 bit add
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 8 क्रम 64 bit access.
 * @value:   Signed value to add.
 *		  Note: Only the low 22 bits are available.
 * Returns Value of the रेजिस्टर beक्रमe the update
 */
अटल अंतरभूत पूर्णांक64_t cvmx_fau_fetch_and_add64(cvmx_fau_reg_64_t reg,
					       पूर्णांक64_t value)
अणु
	वापस cvmx_पढ़ो64_पूर्णांक64(__cvmx_fau_atomic_address(0, reg, value));
पूर्ण

/**
 * Perक्रमm an atomic 32 bit add
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 4 क्रम 32 bit access.
 * @value:   Signed value to add.
 *		  Note: Only the low 22 bits are available.
 * Returns Value of the रेजिस्टर beक्रमe the update
 */
अटल अंतरभूत पूर्णांक32_t cvmx_fau_fetch_and_add32(cvmx_fau_reg_32_t reg,
					       पूर्णांक32_t value)
अणु
	reg ^= SWIZZLE_32;
	वापस cvmx_पढ़ो64_पूर्णांक32(__cvmx_fau_atomic_address(0, reg, value));
पूर्ण

/**
 * Perक्रमm an atomic 16 bit add
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 2 क्रम 16 bit access.
 * @value:   Signed value to add.
 * Returns Value of the रेजिस्टर beक्रमe the update
 */
अटल अंतरभूत पूर्णांक16_t cvmx_fau_fetch_and_add16(cvmx_fau_reg_16_t reg,
					       पूर्णांक16_t value)
अणु
	reg ^= SWIZZLE_16;
	वापस cvmx_पढ़ो64_पूर्णांक16(__cvmx_fau_atomic_address(0, reg, value));
पूर्ण

/**
 * Perक्रमm an atomic 8 bit add
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 * @value:   Signed value to add.
 * Returns Value of the रेजिस्टर beक्रमe the update
 */
अटल अंतरभूत पूर्णांक8_t cvmx_fau_fetch_and_add8(cvmx_fau_reg_8_t reg, पूर्णांक8_t value)
अणु
	reg ^= SWIZZLE_8;
	वापस cvmx_पढ़ो64_पूर्णांक8(__cvmx_fau_atomic_address(0, reg, value));
पूर्ण

/**
 * Perक्रमm an atomic 64 bit add after the current tag चयन
 * completes
 *
 * @reg:    FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		 - Step by 8 क्रम 64 bit access.
 * @value:  Signed value to add.
 *		 Note: Only the low 22 bits are available.
 * Returns If a समयout occurs, the error bit will be set. Otherwise
 *	   the value of the रेजिस्टर beक्रमe the update will be
 *	   वापसed
 */
अटल अंतरभूत cvmx_fau_tagरुको64_t
cvmx_fau_tagरुको_fetch_and_add64(cvmx_fau_reg_64_t reg, पूर्णांक64_t value)
अणु
	जोड़ अणु
		uपूर्णांक64_t i64;
		cvmx_fau_tagरुको64_t t;
	पूर्ण result;
	result.i64 =
	    cvmx_पढ़ो64_पूर्णांक64(__cvmx_fau_atomic_address(1, reg, value));
	वापस result.t;
पूर्ण

/**
 * Perक्रमm an atomic 32 bit add after the current tag चयन
 * completes
 *
 * @reg:    FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		 - Step by 4 क्रम 32 bit access.
 * @value:  Signed value to add.
 *		 Note: Only the low 22 bits are available.
 * Returns If a समयout occurs, the error bit will be set. Otherwise
 *	   the value of the रेजिस्टर beक्रमe the update will be
 *	   वापसed
 */
अटल अंतरभूत cvmx_fau_tagरुको32_t
cvmx_fau_tagरुको_fetch_and_add32(cvmx_fau_reg_32_t reg, पूर्णांक32_t value)
अणु
	जोड़ अणु
		uपूर्णांक64_t i32;
		cvmx_fau_tagरुको32_t t;
	पूर्ण result;
	reg ^= SWIZZLE_32;
	result.i32 =
	    cvmx_पढ़ो64_पूर्णांक32(__cvmx_fau_atomic_address(1, reg, value));
	वापस result.t;
पूर्ण

/**
 * Perक्रमm an atomic 16 bit add after the current tag चयन
 * completes
 *
 * @reg:    FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		 - Step by 2 क्रम 16 bit access.
 * @value:  Signed value to add.
 * Returns If a समयout occurs, the error bit will be set. Otherwise
 *	   the value of the रेजिस्टर beक्रमe the update will be
 *	   वापसed
 */
अटल अंतरभूत cvmx_fau_tagरुको16_t
cvmx_fau_tagरुको_fetch_and_add16(cvmx_fau_reg_16_t reg, पूर्णांक16_t value)
अणु
	जोड़ अणु
		uपूर्णांक64_t i16;
		cvmx_fau_tagरुको16_t t;
	पूर्ण result;
	reg ^= SWIZZLE_16;
	result.i16 =
	    cvmx_पढ़ो64_पूर्णांक16(__cvmx_fau_atomic_address(1, reg, value));
	वापस result.t;
पूर्ण

/**
 * Perक्रमm an atomic 8 bit add after the current tag चयन
 * completes
 *
 * @reg:    FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 * @value:  Signed value to add.
 * Returns If a समयout occurs, the error bit will be set. Otherwise
 *	   the value of the रेजिस्टर beक्रमe the update will be
 *	   वापसed
 */
अटल अंतरभूत cvmx_fau_tagरुको8_t
cvmx_fau_tagरुको_fetch_and_add8(cvmx_fau_reg_8_t reg, पूर्णांक8_t value)
अणु
	जोड़ अणु
		uपूर्णांक64_t i8;
		cvmx_fau_tagरुको8_t t;
	पूर्ण result;
	reg ^= SWIZZLE_8;
	result.i8 = cvmx_पढ़ो64_पूर्णांक8(__cvmx_fau_atomic_address(1, reg, value));
	वापस result.t;
पूर्ण

/**
 * Builds I/O data क्रम async operations
 *
 * @scraddr: Scratch pad byte address to ग_लिखो to.  Must be 8 byte aligned
 * @value:   Signed value to add.
 *		  Note: When perक्रमming 32 and 64 bit access, only the low
 *		  22 bits are available.
 * @tagरुको: Should the atomic add रुको क्रम the current tag चयन
 *		  operation to complete.
 *		  - 0 = Don't रुको
 *		  - 1 = Wait क्रम tag चयन to complete
 * @size:    The size of the operation:
 *		  - CVMX_FAU_OP_SIZE_8	(0) = 8 bits
 *		  - CVMX_FAU_OP_SIZE_16 (1) = 16 bits
 *		  - CVMX_FAU_OP_SIZE_32 (2) = 32 bits
 *		  - CVMX_FAU_OP_SIZE_64 (3) = 64 bits
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 2 क्रम 16 bit access.
 *		  - Step by 4 क्रम 32 bit access.
 *		  - Step by 8 क्रम 64 bit access.
 * Returns Data to ग_लिखो using cvmx_send_single
 */
अटल अंतरभूत uपूर्णांक64_t __cvmx_fau_iobdma_data(uपूर्णांक64_t scraddr, पूर्णांक64_t value,
					      uपूर्णांक64_t tagरुको,
					      cvmx_fau_op_माप_प्रकार size,
					      uपूर्णांक64_t reg)
अणु
	वापस CVMX_FAU_LOAD_IO_ADDRESS |
	       cvmx_build_bits(CVMX_FAU_BITS_SCRADDR, scraddr >> 3) |
	       cvmx_build_bits(CVMX_FAU_BITS_LEN, 1) |
	       cvmx_build_bits(CVMX_FAU_BITS_INEVAL, value) |
	       cvmx_build_bits(CVMX_FAU_BITS_TAGWAIT, tagरुको) |
	       cvmx_build_bits(CVMX_FAU_BITS_SIZE, size) |
	       cvmx_build_bits(CVMX_FAU_BITS_REGISTER, reg);
पूर्ण

/**
 * Perक्रमm an async atomic 64 bit add. The old value is
 * placed in the scratch memory at byte address scraddr.
 *
 * @scraddr: Scratch memory byte address to put response in.
 *		  Must be 8 byte aligned.
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 8 क्रम 64 bit access.
 * @value:   Signed value to add.
 *		  Note: Only the low 22 bits are available.
 * Returns Placed in the scratch pad रेजिस्टर
 */
अटल अंतरभूत व्योम cvmx_fau_async_fetch_and_add64(uपूर्णांक64_t scraddr,
						  cvmx_fau_reg_64_t reg,
						  पूर्णांक64_t value)
अणु
	cvmx_send_single(__cvmx_fau_iobdma_data
			 (scraddr, value, 0, CVMX_FAU_OP_SIZE_64, reg));
पूर्ण

/**
 * Perक्रमm an async atomic 32 bit add. The old value is
 * placed in the scratch memory at byte address scraddr.
 *
 * @scraddr: Scratch memory byte address to put response in.
 *		  Must be 8 byte aligned.
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 4 क्रम 32 bit access.
 * @value:   Signed value to add.
 *		  Note: Only the low 22 bits are available.
 * Returns Placed in the scratch pad रेजिस्टर
 */
अटल अंतरभूत व्योम cvmx_fau_async_fetch_and_add32(uपूर्णांक64_t scraddr,
						  cvmx_fau_reg_32_t reg,
						  पूर्णांक32_t value)
अणु
	cvmx_send_single(__cvmx_fau_iobdma_data
			 (scraddr, value, 0, CVMX_FAU_OP_SIZE_32, reg));
पूर्ण

/**
 * Perक्रमm an async atomic 16 bit add. The old value is
 * placed in the scratch memory at byte address scraddr.
 *
 * @scraddr: Scratch memory byte address to put response in.
 *		  Must be 8 byte aligned.
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 2 क्रम 16 bit access.
 * @value:   Signed value to add.
 * Returns Placed in the scratch pad रेजिस्टर
 */
अटल अंतरभूत व्योम cvmx_fau_async_fetch_and_add16(uपूर्णांक64_t scraddr,
						  cvmx_fau_reg_16_t reg,
						  पूर्णांक16_t value)
अणु
	cvmx_send_single(__cvmx_fau_iobdma_data
			 (scraddr, value, 0, CVMX_FAU_OP_SIZE_16, reg));
पूर्ण

/**
 * Perक्रमm an async atomic 8 bit add. The old value is
 * placed in the scratch memory at byte address scraddr.
 *
 * @scraddr: Scratch memory byte address to put response in.
 *		  Must be 8 byte aligned.
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 * @value:   Signed value to add.
 * Returns Placed in the scratch pad रेजिस्टर
 */
अटल अंतरभूत व्योम cvmx_fau_async_fetch_and_add8(uपूर्णांक64_t scraddr,
						 cvmx_fau_reg_8_t reg,
						 पूर्णांक8_t value)
अणु
	cvmx_send_single(__cvmx_fau_iobdma_data
			 (scraddr, value, 0, CVMX_FAU_OP_SIZE_8, reg));
पूर्ण

/**
 * Perक्रमm an async atomic 64 bit add after the current tag
 * चयन completes.
 *
 * @scraddr: Scratch memory byte address to put response in.  Must be
 *	     8 byte aligned.  If a समयout occurs, the error bit (63)
 *	     will be set. Otherwise the value of the रेजिस्टर beक्रमe
 *	     the update will be वापसed
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 8 क्रम 64 bit access.
 * @value:   Signed value to add.
 *		  Note: Only the low 22 bits are available.
 * Returns Placed in the scratch pad रेजिस्टर
 */
अटल अंतरभूत व्योम cvmx_fau_async_tagरुको_fetch_and_add64(uपूर्णांक64_t scraddr,
							  cvmx_fau_reg_64_t reg,
							  पूर्णांक64_t value)
अणु
	cvmx_send_single(__cvmx_fau_iobdma_data
			 (scraddr, value, 1, CVMX_FAU_OP_SIZE_64, reg));
पूर्ण

/**
 * Perक्रमm an async atomic 32 bit add after the current tag
 * चयन completes.
 *
 * @scraddr: Scratch memory byte address to put response in.  Must be
 *	     8 byte aligned.  If a समयout occurs, the error bit (63)
 *	     will be set. Otherwise the value of the रेजिस्टर beक्रमe
 *	     the update will be वापसed
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 4 क्रम 32 bit access.
 * @value:   Signed value to add.
 *		  Note: Only the low 22 bits are available.
 * Returns Placed in the scratch pad रेजिस्टर
 */
अटल अंतरभूत व्योम cvmx_fau_async_tagरुको_fetch_and_add32(uपूर्णांक64_t scraddr,
							  cvmx_fau_reg_32_t reg,
							  पूर्णांक32_t value)
अणु
	cvmx_send_single(__cvmx_fau_iobdma_data
			 (scraddr, value, 1, CVMX_FAU_OP_SIZE_32, reg));
पूर्ण

/**
 * Perक्रमm an async atomic 16 bit add after the current tag
 * चयन completes.
 *
 * @scraddr: Scratch memory byte address to put response in.  Must be
 *	     8 byte aligned.  If a समयout occurs, the error bit (63)
 *	     will be set. Otherwise the value of the रेजिस्टर beक्रमe
 *	     the update will be वापसed
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 2 क्रम 16 bit access.
 * @value:   Signed value to add.
 *
 * Returns Placed in the scratch pad रेजिस्टर
 */
अटल अंतरभूत व्योम cvmx_fau_async_tagरुको_fetch_and_add16(uपूर्णांक64_t scraddr,
							  cvmx_fau_reg_16_t reg,
							  पूर्णांक16_t value)
अणु
	cvmx_send_single(__cvmx_fau_iobdma_data
			 (scraddr, value, 1, CVMX_FAU_OP_SIZE_16, reg));
पूर्ण

/**
 * Perक्रमm an async atomic 8 bit add after the current tag
 * चयन completes.
 *
 * @scraddr: Scratch memory byte address to put response in.  Must be
 *	     8 byte aligned.  If a समयout occurs, the error bit (63)
 *	     will be set. Otherwise the value of the रेजिस्टर beक्रमe
 *	     the update will be वापसed
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 * @value:   Signed value to add.
 *
 * Returns Placed in the scratch pad रेजिस्टर
 */
अटल अंतरभूत व्योम cvmx_fau_async_tagरुको_fetch_and_add8(uपूर्णांक64_t scraddr,
							 cvmx_fau_reg_8_t reg,
							 पूर्णांक8_t value)
अणु
	cvmx_send_single(__cvmx_fau_iobdma_data
			 (scraddr, value, 1, CVMX_FAU_OP_SIZE_8, reg));
पूर्ण

/**
 * Perक्रमm an atomic 64 bit add
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 8 क्रम 64 bit access.
 * @value:   Signed value to add.
 */
अटल अंतरभूत व्योम cvmx_fau_atomic_add64(cvmx_fau_reg_64_t reg, पूर्णांक64_t value)
अणु
	cvmx_ग_लिखो64_पूर्णांक64(__cvmx_fau_store_address(0, reg), value);
पूर्ण

/**
 * Perक्रमm an atomic 32 bit add
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 4 क्रम 32 bit access.
 * @value:   Signed value to add.
 */
अटल अंतरभूत व्योम cvmx_fau_atomic_add32(cvmx_fau_reg_32_t reg, पूर्णांक32_t value)
अणु
	reg ^= SWIZZLE_32;
	cvmx_ग_लिखो64_पूर्णांक32(__cvmx_fau_store_address(0, reg), value);
पूर्ण

/**
 * Perक्रमm an atomic 16 bit add
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 2 क्रम 16 bit access.
 * @value:   Signed value to add.
 */
अटल अंतरभूत व्योम cvmx_fau_atomic_add16(cvmx_fau_reg_16_t reg, पूर्णांक16_t value)
अणु
	reg ^= SWIZZLE_16;
	cvmx_ग_लिखो64_पूर्णांक16(__cvmx_fau_store_address(0, reg), value);
पूर्ण

/**
 * Perक्रमm an atomic 8 bit add
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 * @value:   Signed value to add.
 */
अटल अंतरभूत व्योम cvmx_fau_atomic_add8(cvmx_fau_reg_8_t reg, पूर्णांक8_t value)
अणु
	reg ^= SWIZZLE_8;
	cvmx_ग_लिखो64_पूर्णांक8(__cvmx_fau_store_address(0, reg), value);
पूर्ण

/**
 * Perक्रमm an atomic 64 bit ग_लिखो
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 8 क्रम 64 bit access.
 * @value:   Signed value to ग_लिखो.
 */
अटल अंतरभूत व्योम cvmx_fau_atomic_ग_लिखो64(cvmx_fau_reg_64_t reg, पूर्णांक64_t value)
अणु
	cvmx_ग_लिखो64_पूर्णांक64(__cvmx_fau_store_address(1, reg), value);
पूर्ण

/**
 * Perक्रमm an atomic 32 bit ग_लिखो
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 4 क्रम 32 bit access.
 * @value:   Signed value to ग_लिखो.
 */
अटल अंतरभूत व्योम cvmx_fau_atomic_ग_लिखो32(cvmx_fau_reg_32_t reg, पूर्णांक32_t value)
अणु
	reg ^= SWIZZLE_32;
	cvmx_ग_लिखो64_पूर्णांक32(__cvmx_fau_store_address(1, reg), value);
पूर्ण

/**
 * Perक्रमm an atomic 16 bit ग_लिखो
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 *		  - Step by 2 क्रम 16 bit access.
 * @value:   Signed value to ग_लिखो.
 */
अटल अंतरभूत व्योम cvmx_fau_atomic_ग_लिखो16(cvmx_fau_reg_16_t reg, पूर्णांक16_t value)
अणु
	reg ^= SWIZZLE_16;
	cvmx_ग_लिखो64_पूर्णांक16(__cvmx_fau_store_address(1, reg), value);
पूर्ण

/**
 * Perक्रमm an atomic 8 bit ग_लिखो
 *
 * @reg:     FAU atomic रेजिस्टर to access. 0 <= reg < 2048.
 * @value:   Signed value to ग_लिखो.
 */
अटल अंतरभूत व्योम cvmx_fau_atomic_ग_लिखो8(cvmx_fau_reg_8_t reg, पूर्णांक8_t value)
अणु
	reg ^= SWIZZLE_8;
	cvmx_ग_लिखो64_पूर्णांक8(__cvmx_fau_store_address(1, reg), value);
पूर्ण

#पूर्ण_अगर /* __CVMX_FAU_H__ */
