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
 * Simple allocate only memory allocator.  Used to allocate memory at
 * application start समय.
 */

#अगर_अघोषित __CVMX_BOOTMEM_H__
#घोषणा __CVMX_BOOTMEM_H__
/* Must be multiple of 8, changing अवरोधs ABI */
#घोषणा CVMX_BOOTMEM_NAME_LEN 128

/* Can change without अवरोधing ABI */
#घोषणा CVMX_BOOTMEM_NUM_NAMED_BLOCKS 64

/* minimum alignment of booपंचांगem alloced blocks */
#घोषणा CVMX_BOOTMEM_ALIGNMENT_SIZE	(16ull)

/* Flags क्रम cvmx_booपंचांगem_phy_mem* functions */
/* Allocate from end of block instead of beginning */
#घोषणा CVMX_BOOTMEM_FLAG_END_ALLOC    (1 << 0)

/* Don't करो any locking. */
#घोषणा CVMX_BOOTMEM_FLAG_NO_LOCKING   (1 << 1)

/* First bytes of each मुक्त physical block of memory contain this काष्ठाure,
 * which is used to मुख्यtain the मुक्त memory list.  Since the bootloader is
 * only 32 bits, there is a जोड़ providing 64 and 32 bit versions.  The
 * application init code converts addresses to 64 bit addresses beक्रमe the
 * application starts.
 */
काष्ठा cvmx_booपंचांगem_block_header अणु
	/*
	 * Note: these are referenced from assembly routines in the
	 * bootloader, so this काष्ठाure should not be changed
	 * without changing those routines as well.
	 */
	uपूर्णांक64_t next_block_addr;
	uपूर्णांक64_t size;

पूर्ण;

/*
 * Structure क्रम named memory blocks.  Number of descriptors available
 * can be changed without affecting compatibility, but name length
 * changes require a bump in the booपंचांगem descriptor version Note: This
 * काष्ठाure must be naturally 64 bit aligned, as a single memory
 * image will be used by both 32 and 64 bit programs.
 */
काष्ठा cvmx_booपंचांगem_named_block_desc अणु
	/* Base address of named block */
	uपूर्णांक64_t base_addr;
	/*
	 * Size actually allocated क्रम named block (may dअगरfer from
	 * requested).
	 */
	uपूर्णांक64_t size;
	/* name of named block */
	अक्षर name[CVMX_BOOTMEM_NAME_LEN];
पूर्ण;

/* Current descriptor versions */
/* CVMX booपंचांगem descriptor major version */
#घोषणा CVMX_BOOTMEM_DESC_MAJ_VER   3

/* CVMX booपंचांगem descriptor minor version */
#घोषणा CVMX_BOOTMEM_DESC_MIN_VER   0

/* First three members of cvmx_booपंचांगem_desc_t are left in original
 * positions क्रम backwards compatibility.
 */
काष्ठा cvmx_booपंचांगem_desc अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) || defined(CVMX_BUILD_FOR_LINUX_HOST)
	/* spinlock to control access to list */
	uपूर्णांक32_t lock;
	/* flags क्रम indicating various conditions */
	uपूर्णांक32_t flags;
	uपूर्णांक64_t head_addr;

	/* Incremented when incompatible changes made */
	uपूर्णांक32_t major_version;

	/*
	 * Incremented changed when compatible changes made, reset to
	 * zero when major incremented.
	 */
	uपूर्णांक32_t minor_version;

	uपूर्णांक64_t app_data_addr;
	uपूर्णांक64_t app_data_size;

	/* number of elements in named blocks array */
	uपूर्णांक32_t named_block_num_blocks;

	/* length of name array in booपंचांगem blocks */
	uपूर्णांक32_t named_block_name_len;
	/* address of named memory block descriptors */
	uपूर्णांक64_t named_block_array_addr;
#अन्यथा                           /* __LITTLE_ENDIAN */
	uपूर्णांक32_t flags;
	uपूर्णांक32_t lock;
	uपूर्णांक64_t head_addr;

	uपूर्णांक32_t minor_version;
	uपूर्णांक32_t major_version;
	uपूर्णांक64_t app_data_addr;
	uपूर्णांक64_t app_data_size;

	uपूर्णांक32_t named_block_name_len;
	uपूर्णांक32_t named_block_num_blocks;
	uपूर्णांक64_t named_block_array_addr;
#पूर्ण_अगर
पूर्ण;

/**
 * Initialize the boot alloc memory काष्ठाures. This is
 * normally called inside of cvmx_user_app_init()
 *
 * @mem_desc_ptr:	Address of the मुक्त memory list
 */
बाह्य पूर्णांक cvmx_booपंचांगem_init(व्योम *mem_desc_ptr);

/**
 * Allocate a block of memory from the मुक्त list that was
 * passed to the application by the bootloader at a specअगरic
 * address. This is an allocate-only algorithm, so
 * मुक्तing memory is not possible. Allocation will fail अगर
 * memory cannot be allocated at the specअगरied address.
 *
 * @size:      Size in bytes of block to allocate
 * @address:   Physical address to allocate memory at.	If this memory is not
 *		    available, the allocation fails.
 * @alignment: Alignment required - must be घातer of 2
 * Returns poपूर्णांकer to block of memory, शून्य on error
 */
बाह्य व्योम *cvmx_booपंचांगem_alloc_address(uपूर्णांक64_t size, uपूर्णांक64_t address,
					uपूर्णांक64_t alignment);

/**
 * Frees a previously allocated named booपंचांगem block.
 *
 * @name:   name of block to मुक्त
 *
 * Returns 0 on failure,
 *	   !0 on success
 */


/**
 * Allocate a block of memory from the मुक्त list that was passed
 * to the application by the bootloader, and assign it a name in the
 * global named block table.  (part of the cvmx_booपंचांगem_descriptor_t काष्ठाure)
 * Named blocks can later be मुक्तd.
 *
 * @size:      Size in bytes of block to allocate
 * @alignment: Alignment required - must be घातer of 2
 * @name:      name of block - must be less than CVMX_BOOTMEM_NAME_LEN bytes
 *
 * Returns a poपूर्णांकer to block of memory, शून्य on error
 */
बाह्य व्योम *cvmx_booपंचांगem_alloc_named(uपूर्णांक64_t size, uपूर्णांक64_t alignment,
				      अक्षर *name);

/**
 * Allocate a block of memory from a specअगरic range of the मुक्त list
 * that was passed to the application by the bootloader, and assign it
 * a name in the global named block table.  (part of the
 * cvmx_booपंचांगem_descriptor_t काष्ठाure) Named blocks can later be
 * मुक्तd.  If request cannot be satisfied within the address range
 * specअगरied, शून्य is वापसed
 *
 * @size:      Size in bytes of block to allocate
 * @min_addr:  minimum address of range
 * @max_addr:  maximum address of range
 * @align:     Alignment of memory to be allocated. (must be a घातer of 2)
 * @name:      name of block - must be less than CVMX_BOOTMEM_NAME_LEN bytes
 *
 * Returns a poपूर्णांकer to block of memory, शून्य on error
 */
बाह्य व्योम *cvmx_booपंचांगem_alloc_named_range(uपूर्णांक64_t size, uपूर्णांक64_t min_addr,
					    uपूर्णांक64_t max_addr, uपूर्णांक64_t align,
					    अक्षर *name);

/**
 * Allocate अगर needed a block of memory from a specअगरic range of the
 * मुक्त list that was passed to the application by the bootloader, and
 * assign it a name in the global named block table.  (part of the
 * cvmx_booपंचांगem_descriptor_t काष्ठाure) Named blocks can later be
 * मुक्तd.  If the requested name block is alपढ़ोy allocated, वापस
 * the poपूर्णांकer to block of memory.  If request cannot be satisfied
 * within the address range specअगरied, शून्य is वापसed
 *
 * @param size   Size in bytes of block to allocate
 * @param min_addr  minimum address of range
 * @param max_addr  maximum address of range
 * @param align  Alignment of memory to be allocated. (must be a घातer of 2)
 * @param name   name of block - must be less than CVMX_BOOTMEM_NAME_LEN bytes
 * @param init   Initialization function
 *
 * The initialization function is optional, अगर omitted the named block
 * is initialized to all zeros when it is created, i.e. once.
 *
 * @वापस poपूर्णांकer to block of memory, शून्य on error
 */
व्योम *cvmx_booपंचांगem_alloc_named_range_once(uपूर्णांक64_t size,
					  uपूर्णांक64_t min_addr,
					  uपूर्णांक64_t max_addr,
					  uपूर्णांक64_t align,
					  अक्षर *name,
					  व्योम (*init) (व्योम *));

बाह्य पूर्णांक cvmx_booपंचांगem_मुक्त_named(अक्षर *name);

/**
 * Finds a named booपंचांगem block by name.
 *
 * @name:   name of block to मुक्त
 *
 * Returns poपूर्णांकer to named block descriptor on success
 *	   0 on failure
 */
काष्ठा cvmx_booपंचांगem_named_block_desc *cvmx_booपंचांगem_find_named_block(अक्षर *name);

/**
 * Allocates a block of physical memory from the मुक्त list, at
 * (optional) requested address and alignment.
 *
 * @req_size: size of region to allocate.  All requests are rounded up
 *	      to be a multiple CVMX_BOOTMEM_ALIGNMENT_SIZE bytes size
 *
 * @address_min: Minimum address that block can occupy.
 *
 * @address_max: Specअगरies the maximum address_min (inclusive) that
 *		 the allocation can use.
 *
 * @alignment: Requested alignment of the block.  If this alignment
 *	       cannot be met, the allocation fails.  This must be a
 *	       घातer of 2.  (Note: Alignment of
 *	       CVMX_BOOTMEM_ALIGNMENT_SIZE bytes is required, and
 *	       पूर्णांकernally enक्रमced.  Requested alignments of less than
 *	       CVMX_BOOTMEM_ALIGNMENT_SIZE are set to
 *	       CVMX_BOOTMEM_ALIGNMENT_SIZE.)
 *
 * @flags:     Flags to control options क्रम the allocation.
 *
 * Returns physical address of block allocated, or -1 on failure
 */
पूर्णांक64_t cvmx_booपंचांगem_phy_alloc(uपूर्णांक64_t req_size, uपूर्णांक64_t address_min,
			       uपूर्णांक64_t address_max, uपूर्णांक64_t alignment,
			       uपूर्णांक32_t flags);

/**
 * Allocates a named block of physical memory from the मुक्त list, at
 * (optional) requested address and alignment.
 *
 * @param size	    size of region to allocate.	 All requests are rounded
 *		    up to be a multiple CVMX_BOOTMEM_ALIGNMENT_SIZE
 *		    bytes size
 * @param min_addr Minimum address that block can occupy.
 * @param max_addr  Specअगरies the maximum address_min (inclusive) that
 *		    the allocation can use.
 * @param alignment Requested alignment of the block.  If this
 *		    alignment cannot be met, the allocation fails.
 *		    This must be a घातer of 2.	(Note: Alignment of
 *		    CVMX_BOOTMEM_ALIGNMENT_SIZE bytes is required, and
 *		    पूर्णांकernally enक्रमced.  Requested alignments of less
 *		    than CVMX_BOOTMEM_ALIGNMENT_SIZE are set to
 *		    CVMX_BOOTMEM_ALIGNMENT_SIZE.)
 * @param name	    name to assign to named block
 * @param flags	    Flags to control options क्रम the allocation.
 *
 * @वापस physical address of block allocated, or -1 on failure
 */
पूर्णांक64_t cvmx_booपंचांगem_phy_named_block_alloc(uपूर्णांक64_t size, uपूर्णांक64_t min_addr,
					   uपूर्णांक64_t max_addr,
					   uपूर्णांक64_t alignment,
					   अक्षर *name, uपूर्णांक32_t flags);

/**
 * Frees a block to the booपंचांगem allocator list.	 This must
 * be used with care, as the size provided must match the size
 * of the block that was allocated, or the list will become
 * corrupted.
 *
 * IMPORTANT:  This is only पूर्णांकended to be used as part of named block
 * मुक्तs and initial population of the मुक्त memory list.
 *							*
 *
 * @phy_addr: physical address of block
 * @size:     size of block in bytes.
 * @flags:    flags क्रम passing options
 *
 * Returns 1 on success,
 *	   0 on failure
 */
पूर्णांक __cvmx_booपंचांगem_phy_मुक्त(uपूर्णांक64_t phy_addr, uपूर्णांक64_t size, uपूर्णांक32_t flags);

/**
 * Locks the booपंचांगem allocator.	 This is useful in certain situations
 * where multiple allocations must be made without being पूर्णांकerrupted.
 * This should be used with the CVMX_BOOTMEM_FLAG_NO_LOCKING flag.
 *
 */
व्योम cvmx_booपंचांगem_lock(व्योम);

/**
 * Unlocks the booपंचांगem allocator.  This is useful in certain situations
 * where multiple allocations must be made without being पूर्णांकerrupted.
 * This should be used with the CVMX_BOOTMEM_FLAG_NO_LOCKING flag.
 *
 */
व्योम cvmx_booपंचांगem_unlock(व्योम);

बाह्य काष्ठा cvmx_booपंचांगem_desc *cvmx_booपंचांगem_get_desc(व्योम);

#पूर्ण_अगर /*   __CVMX_BOOTMEM_H__ */
