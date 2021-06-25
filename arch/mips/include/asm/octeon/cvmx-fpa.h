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
 * @file
 *
 * Interface to the hardware Free Pool Allocator.
 *
 *
 */

#अगर_अघोषित __CVMX_FPA_H__
#घोषणा __CVMX_FPA_H__

#समावेश <linux/delay.h>

#समावेश <यंत्र/octeon/cvmx-address.h>
#समावेश <यंत्र/octeon/cvmx-fpa-defs.h>

#घोषणा CVMX_FPA_NUM_POOLS	8
#घोषणा CVMX_FPA_MIN_BLOCK_SIZE 128
#घोषणा CVMX_FPA_ALIGNMENT	128

/**
 * Structure describing the data क्रमmat used क्रम stores to the FPA.
 */
प्रकार जोड़ अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/*
		 * the (64-bit word) location in scratchpad to ग_लिखो
		 * to (अगर len != 0)
		 */
		uपूर्णांक64_t scraddr:8;
		/* the number of words in the response (0 => no response) */
		uपूर्णांक64_t len:8;
		/* the ID of the device on the non-coherent bus */
		uपूर्णांक64_t did:8;
		/*
		 * the address that will appear in the first tick on
		 * the NCB bus.
		 */
		uपूर्णांक64_t addr:40;
#अन्यथा
		uपूर्णांक64_t addr:40;
		uपूर्णांक64_t did:8;
		uपूर्णांक64_t len:8;
		uपूर्णांक64_t scraddr:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण cvmx_fpa_iobdma_data_t;

/**
 * Structure describing the current state of a FPA pool.
 */
प्रकार काष्ठा अणु
	/* Name it was created under */
	स्थिर अक्षर *name;
	/* Size of each block */
	uपूर्णांक64_t size;
	/* The base memory address of whole block */
	व्योम *base;
	/* The number of elements in the pool at creation */
	uपूर्णांक64_t starting_element_count;
पूर्ण cvmx_fpa_pool_info_t;

/**
 * Current state of all the pools. Use access functions
 * instead of using it directly.
 */
बाह्य cvmx_fpa_pool_info_t cvmx_fpa_pool_info[CVMX_FPA_NUM_POOLS];

/* CSR प्रकारs have been moved to cvmx-csr-*.h */

/**
 * Return the name of the pool
 *
 * @pool:   Pool to get the name of
 * Returns The name
 */
अटल अंतरभूत स्थिर अक्षर *cvmx_fpa_get_name(uपूर्णांक64_t pool)
अणु
	वापस cvmx_fpa_pool_info[pool].name;
पूर्ण

/**
 * Return the base of the pool
 *
 * @pool:   Pool to get the base of
 * Returns The base
 */
अटल अंतरभूत व्योम *cvmx_fpa_get_base(uपूर्णांक64_t pool)
अणु
	वापस cvmx_fpa_pool_info[pool].base;
पूर्ण

/**
 * Check अगर a poपूर्णांकer beदीर्घs to an FPA pool. Return non-zero
 * अगर the supplied poपूर्णांकer is inside the memory controlled by
 * an FPA pool.
 *
 * @pool:   Pool to check
 * @ptr:    Poपूर्णांकer to check
 * Returns Non-zero अगर poपूर्णांकer is in the pool. Zero अगर not
 */
अटल अंतरभूत पूर्णांक cvmx_fpa_is_member(uपूर्णांक64_t pool, व्योम *ptr)
अणु
	वापस ((ptr >= cvmx_fpa_pool_info[pool].base) &&
		((अक्षर *)ptr <
		 ((अक्षर *)(cvmx_fpa_pool_info[pool].base)) +
		 cvmx_fpa_pool_info[pool].size *
		 cvmx_fpa_pool_info[pool].starting_element_count));
पूर्ण

/**
 * Enable the FPA क्रम use. Must be perक्रमmed after any CSR
 * configuration but beक्रमe any other FPA functions.
 */
अटल अंतरभूत व्योम cvmx_fpa_enable(व्योम)
अणु
	जोड़ cvmx_fpa_ctl_status status;

	status.u64 = cvmx_पढ़ो_csr(CVMX_FPA_CTL_STATUS);
	अगर (status.s.enb) अणु
		cvmx_dम_लिखो
		    ("Warning: Enabling FPA when FPA already enabled.\n");
	पूर्ण

	/*
	 * Do runसमय check as we allow pass1 compiled code to run on
	 * pass2 chips.
	 */
	अगर (cvmx_octeon_is_pass1()) अणु
		जोड़ cvmx_fpa_fpfx_marks marks;
		पूर्णांक i;
		क्रम (i = 1; i < 8; i++) अणु
			marks.u64 =
			    cvmx_पढ़ो_csr(CVMX_FPA_FPF1_MARKS + (i - 1) * 8ull);
			marks.s.fpf_wr = 0xe0;
			cvmx_ग_लिखो_csr(CVMX_FPA_FPF1_MARKS + (i - 1) * 8ull,
				       marks.u64);
		पूर्ण

		/* Enक्रमce a 10 cycle delay between config and enable */
		__delay(10);
	पूर्ण

	/* FIXME: CVMX_FPA_CTL_STATUS पढ़ो is unmodelled */
	status.u64 = 0;
	status.s.enb = 1;
	cvmx_ग_लिखो_csr(CVMX_FPA_CTL_STATUS, status.u64);
पूर्ण

/**
 * Get a new block from the FPA
 *
 * @pool:   Pool to get the block from
 * Returns Poपूर्णांकer to the block or शून्य on failure
 */
अटल अंतरभूत व्योम *cvmx_fpa_alloc(uपूर्णांक64_t pool)
अणु
	uपूर्णांक64_t address =
	    cvmx_पढ़ो_csr(CVMX_ADDR_DID(CVMX_FULL_DID(CVMX_OCT_DID_FPA, pool)));
	अगर (address)
		वापस cvmx_phys_to_ptr(address);
	अन्यथा
		वापस शून्य;
पूर्ण

/**
 * Asynchronously get a new block from the FPA
 *
 * @scr_addr: Local scratch address to put response in.	 This is a byte address,
 *		    but must be 8 byte aligned.
 * @pool:      Pool to get the block from
 */
अटल अंतरभूत व्योम cvmx_fpa_async_alloc(uपूर्णांक64_t scr_addr, uपूर्णांक64_t pool)
अणु
	cvmx_fpa_iobdma_data_t data;

	/*
	 * Hardware only uses 64 bit aligned locations, so convert
	 * from byte address to 64-bit index
	 */
	data.s.scraddr = scr_addr >> 3;
	data.s.len = 1;
	data.s.did = CVMX_FULL_DID(CVMX_OCT_DID_FPA, pool);
	data.s.addr = 0;
	cvmx_send_single(data.u64);
पूर्ण

/**
 * Free a block allocated with a FPA pool.  Does NOT provide memory
 * ordering in हालs where the memory block was modअगरied by the core.
 *
 * @ptr:    Block to मुक्त
 * @pool:   Pool to put it in
 * @num_cache_lines:
 *		 Cache lines to invalidate
 */
अटल अंतरभूत व्योम cvmx_fpa_मुक्त_nosync(व्योम *ptr, uपूर्णांक64_t pool,
					uपूर्णांक64_t num_cache_lines)
अणु
	cvmx_addr_t newptr;
	newptr.u64 = cvmx_ptr_to_phys(ptr);
	newptr.sfilldidspace.didspace =
	    CVMX_ADDR_DIDSPACE(CVMX_FULL_DID(CVMX_OCT_DID_FPA, pool));
	/* Prevent GCC from reordering around मुक्त */
	barrier();
	/* value written is number of cache lines not written back */
	cvmx_ग_लिखो_io(newptr.u64, num_cache_lines);
पूर्ण

/**
 * Free a block allocated with a FPA pool.  Provides required memory
 * ordering in हालs where memory block was modअगरied by core.
 *
 * @ptr:    Block to मुक्त
 * @pool:   Pool to put it in
 * @num_cache_lines:
 *		 Cache lines to invalidate
 */
अटल अंतरभूत व्योम cvmx_fpa_मुक्त(व्योम *ptr, uपूर्णांक64_t pool,
				 uपूर्णांक64_t num_cache_lines)
अणु
	cvmx_addr_t newptr;
	newptr.u64 = cvmx_ptr_to_phys(ptr);
	newptr.sfilldidspace.didspace =
	    CVMX_ADDR_DIDSPACE(CVMX_FULL_DID(CVMX_OCT_DID_FPA, pool));
	/*
	 * Make sure that any previous ग_लिखोs to memory go out beक्रमe
	 * we मुक्त this buffer.	 This also serves as a barrier to
	 * prevent GCC from reordering operations to after the
	 * मुक्त.
	 */
	CVMX_SYNCWS;
	/* value written is number of cache lines not written back */
	cvmx_ग_लिखो_io(newptr.u64, num_cache_lines);
पूर्ण

/**
 * Setup a FPA pool to control a new block of memory.
 * This can only be called once per pool. Make sure proper
 * locking enक्रमces this.
 *
 * @pool:	Pool to initialize
 *		     0 <= pool < 8
 * @name:	Constant अक्षरacter string to name this pool.
 *		     String is not copied.
 * @buffer:	Poपूर्णांकer to the block of memory to use. This must be
 *		     accessible by all processors and बाह्यal hardware.
 * @block_size: Size क्रम each block controlled by the FPA
 * @num_blocks: Number of blocks
 *
 * Returns 0 on Success,
 *	   -1 on failure
 */
बाह्य पूर्णांक cvmx_fpa_setup_pool(uपूर्णांक64_t pool, स्थिर अक्षर *name, व्योम *buffer,
			       uपूर्णांक64_t block_size, uपूर्णांक64_t num_blocks);

/**
 * Shutकरोwn a Memory pool and validate that it had all of
 * the buffers originally placed in it. This should only be
 * called by one processor after all hardware has finished
 * using the pool.
 *
 * @pool:   Pool to shutकरोwn
 * Returns Zero on success
 *	   - Positive is count of missing buffers
 *	   - Negative is too many buffers or corrupted poपूर्णांकers
 */
बाह्य uपूर्णांक64_t cvmx_fpa_shutकरोwn_pool(uपूर्णांक64_t pool);

/**
 * Get the size of blocks controlled by the pool
 * This is resolved to a स्थिरant at compile समय.
 *
 * @pool:   Pool to access
 * Returns Size of the block in bytes
 */
uपूर्णांक64_t cvmx_fpa_get_block_size(uपूर्णांक64_t pool);

#पूर्ण_अगर /*  __CVM_FPA_H__ */
