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

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/octeon/cvmx.h>
#समावेश <यंत्र/octeon/cvmx-spinlock.h>
#समावेश <यंत्र/octeon/cvmx-booपंचांगem.h>

/*#घोषणा DEBUG */


अटल काष्ठा cvmx_booपंचांगem_desc *cvmx_booपंचांगem_desc;

/* See header file क्रम descriptions of functions */

/**
 * This macro वापसs a member of the
 * cvmx_booपंचांगem_named_block_desc_t काष्ठाure. These members can't
 * be directly addressed as they might be in memory not directly
 * reachable. In the हाल where booपंचांगem is compiled with
 * LINUX_HOST, the काष्ठाure itself might be located on a remote
 * Octeon. The argument "field" is the member name of the
 * cvmx_booपंचांगem_named_block_desc_t to पढ़ो. Regardless of the type
 * of the field, the वापस type is always a uपूर्णांक64_t. The "addr"
 * parameter is the physical address of the काष्ठाure.
 */
#घोषणा CVMX_BOOTMEM_NAMED_GET_FIELD(addr, field)			\
	__cvmx_booपंचांगem_desc_get(addr,					\
		दुरत्व(काष्ठा cvmx_booपंचांगem_named_block_desc, field),	\
		माप_field(काष्ठा cvmx_booपंचांगem_named_block_desc, field))

/**
 * This function is the implementation of the get macros defined
 * क्रम inभागidual काष्ठाure members. The argument are generated
 * by the macros inorder to पढ़ो only the needed memory.
 *
 * @param base   64bit physical address of the complete काष्ठाure
 * @param offset Offset from the beginning of the काष्ठाure to the member being
 *               accessed.
 * @param size   Size of the काष्ठाure member.
 *
 * @वापस Value of the काष्ठाure member promoted पूर्णांकo a uपूर्णांक64_t.
 */
अटल अंतरभूत uपूर्णांक64_t __cvmx_booपंचांगem_desc_get(uपूर्णांक64_t base, पूर्णांक offset,
					       पूर्णांक size)
अणु
	base = (1ull << 63) | (base + offset);
	चयन (size) अणु
	हाल 4:
		वापस cvmx_पढ़ो64_uपूर्णांक32(base);
	हाल 8:
		वापस cvmx_पढ़ो64_uपूर्णांक64(base);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Wrapper functions are provided क्रम पढ़ोing/writing the size and
 * next block values as these may not be directly addressible (in 32
 * bit applications, क्रम instance.)  Offsets of data elements in
 * booपंचांगem list, must match cvmx_booपंचांगem_block_header_t.
 */
#घोषणा NEXT_OFFSET 0
#घोषणा SIZE_OFFSET 8

अटल व्योम cvmx_booपंचांगem_phy_set_size(uपूर्णांक64_t addr, uपूर्णांक64_t size)
अणु
	cvmx_ग_लिखो64_uपूर्णांक64((addr + SIZE_OFFSET) | (1ull << 63), size);
पूर्ण

अटल व्योम cvmx_booपंचांगem_phy_set_next(uपूर्णांक64_t addr, uपूर्णांक64_t next)
अणु
	cvmx_ग_लिखो64_uपूर्णांक64((addr + NEXT_OFFSET) | (1ull << 63), next);
पूर्ण

अटल uपूर्णांक64_t cvmx_booपंचांगem_phy_get_size(uपूर्णांक64_t addr)
अणु
	वापस cvmx_पढ़ो64_uपूर्णांक64((addr + SIZE_OFFSET) | (1ull << 63));
पूर्ण

अटल uपूर्णांक64_t cvmx_booपंचांगem_phy_get_next(uपूर्णांक64_t addr)
अणु
	वापस cvmx_पढ़ो64_uपूर्णांक64((addr + NEXT_OFFSET) | (1ull << 63));
पूर्ण

/**
 * Allocate a block of memory from the मुक्त list that was
 * passed to the application by the bootloader within a specअगरied
 * address range. This is an allocate-only algorithm, so
 * मुक्तing memory is not possible. Allocation will fail अगर
 * memory cannot be allocated in the requested range.
 *
 * @size:      Size in bytes of block to allocate
 * @min_addr:  defines the minimum address of the range
 * @max_addr:  defines the maximum address of the range
 * @alignment: Alignment required - must be घातer of 2
 * Returns poपूर्णांकer to block of memory, शून्य on error
 */
अटल व्योम *cvmx_booपंचांगem_alloc_range(uपूर्णांक64_t size, uपूर्णांक64_t alignment,
				      uपूर्णांक64_t min_addr, uपूर्णांक64_t max_addr)
अणु
	पूर्णांक64_t address;
	address =
	    cvmx_booपंचांगem_phy_alloc(size, min_addr, max_addr, alignment, 0);

	अगर (address > 0)
		वापस cvmx_phys_to_ptr(address);
	अन्यथा
		वापस शून्य;
पूर्ण

व्योम *cvmx_booपंचांगem_alloc_address(uपूर्णांक64_t size, uपूर्णांक64_t address,
				 uपूर्णांक64_t alignment)
अणु
	वापस cvmx_booपंचांगem_alloc_range(size, alignment, address,
					address + size);
पूर्ण

व्योम *cvmx_booपंचांगem_alloc_named_range(uपूर्णांक64_t size, uपूर्णांक64_t min_addr,
				     uपूर्णांक64_t max_addr, uपूर्णांक64_t align,
				     अक्षर *name)
अणु
	पूर्णांक64_t addr;

	addr = cvmx_booपंचांगem_phy_named_block_alloc(size, min_addr, max_addr,
						  align, name, 0);
	अगर (addr >= 0)
		वापस cvmx_phys_to_ptr(addr);
	अन्यथा
		वापस शून्य;
पूर्ण

व्योम *cvmx_booपंचांगem_alloc_named(uपूर्णांक64_t size, uपूर्णांक64_t alignment, अक्षर *name)
अणु
    वापस cvmx_booपंचांगem_alloc_named_range(size, 0, 0, alignment, name);
पूर्ण
EXPORT_SYMBOL(cvmx_booपंचांगem_alloc_named);

व्योम cvmx_booपंचांगem_lock(व्योम)
अणु
	cvmx_spinlock_lock((cvmx_spinlock_t *) &(cvmx_booपंचांगem_desc->lock));
पूर्ण

व्योम cvmx_booपंचांगem_unlock(व्योम)
अणु
	cvmx_spinlock_unlock((cvmx_spinlock_t *) &(cvmx_booपंचांगem_desc->lock));
पूर्ण

पूर्णांक cvmx_booपंचांगem_init(व्योम *mem_desc_ptr)
अणु
	/* Here we set the global poपूर्णांकer to the booपंचांगem descriptor
	 * block.  This poपूर्णांकer will be used directly, so we will set
	 * it up to be directly usable by the application.  It is set
	 * up as follows क्रम the various runसमय/ABI combinations:
	 *
	 * Linux 64 bit: Set XKPHYS bit
	 * Linux 32 bit: use mmap to create mapping, use भव address
	 * CVMX 64 bit:	 use physical address directly
	 * CVMX 32 bit:	 use physical address directly
	 *
	 * Note that the CVMX environment assumes the use of 1-1 TLB
	 * mappings so that the physical addresses can be used
	 * directly
	 */
	अगर (!cvmx_booपंचांगem_desc) अणु
#अगर   defined(CVMX_ABI_64)
		/* Set XKPHYS bit */
		cvmx_booपंचांगem_desc = cvmx_phys_to_ptr(CAST64(mem_desc_ptr));
#अन्यथा
		cvmx_booपंचांगem_desc = (काष्ठा cvmx_booपंचांगem_desc *) mem_desc_ptr;
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The cvmx_booपंचांगem_phy* functions below वापस 64 bit physical
 * addresses, and expose more features that the cvmx_booपंचांगem_functions
 * above.  These are required क्रम full memory space access in 32 bit
 * applications, as well as क्रम using some advance features.  Most
 * applications should not need to use these.
 */

पूर्णांक64_t cvmx_booपंचांगem_phy_alloc(uपूर्णांक64_t req_size, uपूर्णांक64_t address_min,
			       uपूर्णांक64_t address_max, uपूर्णांक64_t alignment,
			       uपूर्णांक32_t flags)
अणु

	uपूर्णांक64_t head_addr;
	uपूर्णांक64_t ent_addr;
	/* poपूर्णांकs to previous list entry, शून्य current entry is head of list */
	uपूर्णांक64_t prev_addr = 0;
	uपूर्णांक64_t new_ent_addr = 0;
	uपूर्णांक64_t desired_min_addr;

#अगर_घोषित DEBUG
	cvmx_dम_लिखो("cvmx_bootmem_phy_alloc: req_size: 0x%llx, "
		     "min_addr: 0x%llx, max_addr: 0x%llx, align: 0x%llx\n",
		     (अचिन्हित दीर्घ दीर्घ)req_size,
		     (अचिन्हित दीर्घ दीर्घ)address_min,
		     (अचिन्हित दीर्घ दीर्घ)address_max,
		     (अचिन्हित दीर्घ दीर्घ)alignment);
#पूर्ण_अगर

	अगर (cvmx_booपंचांगem_desc->major_version > 3) अणु
		cvmx_dम_लिखो("ERROR: Incompatible bootmem descriptor "
			     "version: %d.%d at addr: %p\n",
			     (पूर्णांक)cvmx_booपंचांगem_desc->major_version,
			     (पूर्णांक)cvmx_booपंचांगem_desc->minor_version,
			     cvmx_booपंचांगem_desc);
		जाओ error_out;
	पूर्ण

	/*
	 * Do a variety of checks to validate the arguments.  The
	 * allocator code will later assume that these checks have
	 * been made.  We validate that the requested स्थिरraपूर्णांकs are
	 * not self-contradictory beक्रमe we look through the list of
	 * available memory.
	 */

	/* 0 is not a valid req_size क्रम this allocator */
	अगर (!req_size)
		जाओ error_out;

	/* Round req_size up to mult of minimum alignment bytes */
	req_size = (req_size + (CVMX_BOOTMEM_ALIGNMENT_SIZE - 1)) &
		~(CVMX_BOOTMEM_ALIGNMENT_SIZE - 1);

	/*
	 * Convert !0 address_min and 0 address_max to special हाल of
	 * range that specअगरies an exact memory block to allocate.  Do
	 * this beक्रमe other checks and adjusपंचांगents so that this
	 * tranक्रमmation will be validated.
	 */
	अगर (address_min && !address_max)
		address_max = address_min + req_size;
	अन्यथा अगर (!address_min && !address_max)
		address_max = ~0ull;  /* If no limits given, use max limits */


	/*
	 * Enक्रमce minimum alignment (this also keeps the minimum मुक्त block
	 * req_size the same as the alignment req_size.
	 */
	अगर (alignment < CVMX_BOOTMEM_ALIGNMENT_SIZE)
		alignment = CVMX_BOOTMEM_ALIGNMENT_SIZE;

	/*
	 * Adjust address minimum based on requested alignment (round
	 * up to meet alignment).  Do this here so we can reject
	 * impossible requests up front. (NOP क्रम address_min == 0)
	 */
	अगर (alignment)
		address_min = ALIGN(address_min, alignment);

	/*
	 * Reject inconsistent args.  We have adjusted these, so this
	 * may fail due to our पूर्णांकernal changes even अगर this check
	 * would pass क्रम the values the user supplied.
	 */
	अगर (req_size > address_max - address_min)
		जाओ error_out;

	/* Walk through the list entries - first fit found is वापसed */

	अगर (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
		cvmx_booपंचांगem_lock();
	head_addr = cvmx_booपंचांगem_desc->head_addr;
	ent_addr = head_addr;
	क्रम (; ent_addr;
	     prev_addr = ent_addr,
	     ent_addr = cvmx_booपंचांगem_phy_get_next(ent_addr)) अणु
		uपूर्णांक64_t usable_base, usable_max;
		uपूर्णांक64_t ent_size = cvmx_booपंचांगem_phy_get_size(ent_addr);

		अगर (cvmx_booपंचांगem_phy_get_next(ent_addr)
		    && ent_addr > cvmx_booपंचांगem_phy_get_next(ent_addr)) अणु
			cvmx_dम_लिखो("Internal bootmem_alloc() error: ent: "
				"0x%llx, next: 0x%llx\n",
				(अचिन्हित दीर्घ दीर्घ)ent_addr,
				(अचिन्हित दीर्घ दीर्घ)
				cvmx_booपंचांगem_phy_get_next(ent_addr));
			जाओ error_out;
		पूर्ण

		/*
		 * Determine अगर this is an entry that can satisअगरy the
		 * request Check to make sure entry is large enough to
		 * satisfy request.
		 */
		usable_base =
		    ALIGN(max(address_min, ent_addr), alignment);
		usable_max = min(address_max, ent_addr + ent_size);
		/*
		 * We should be able to allocate block at address
		 * usable_base.
		 */

		desired_min_addr = usable_base;
		/*
		 * Determine अगर request can be satisfied from the
		 * current entry.
		 */
		अगर (!((ent_addr + ent_size) > usable_base
				&& ent_addr < address_max
				&& req_size <= usable_max - usable_base))
			जारी;
		/*
		 * We have found an entry that has room to satisfy the
		 * request, so allocate it from this entry.  If end
		 * CVMX_BOOTMEM_FLAG_END_ALLOC set, then allocate from
		 * the end of this block rather than the beginning.
		 */
		अगर (flags & CVMX_BOOTMEM_FLAG_END_ALLOC) अणु
			desired_min_addr = usable_max - req_size;
			/*
			 * Align desired address करोwn to required
			 * alignment.
			 */
			desired_min_addr &= ~(alignment - 1);
		पूर्ण

		/* Match at start of entry */
		अगर (desired_min_addr == ent_addr) अणु
			अगर (req_size < ent_size) अणु
				/*
				 * big enough to create a new block
				 * from top portion of block.
				 */
				new_ent_addr = ent_addr + req_size;
				cvmx_booपंचांगem_phy_set_next(new_ent_addr,
					cvmx_booपंचांगem_phy_get_next(ent_addr));
				cvmx_booपंचांगem_phy_set_size(new_ent_addr,
							ent_size -
							req_size);

				/*
				 * Adjust next poपूर्णांकer as following
				 * code uses this.
				 */
				cvmx_booपंचांगem_phy_set_next(ent_addr,
							new_ent_addr);
			पूर्ण

			/*
			 * adjust prev ptr or head to हटाओ this
			 * entry from list.
			 */
			अगर (prev_addr)
				cvmx_booपंचांगem_phy_set_next(prev_addr,
					cvmx_booपंचांगem_phy_get_next(ent_addr));
			अन्यथा
				/*
				 * head of list being वापसed, so
				 * update head ptr.
				 */
				cvmx_booपंचांगem_desc->head_addr =
					cvmx_booपंचांगem_phy_get_next(ent_addr);

			अगर (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
				cvmx_booपंचांगem_unlock();
			वापस desired_min_addr;
		पूर्ण
		/*
		 * block वापसed करोesn't start at beginning of entry,
		 * so we know that we will be splitting a block off
		 * the front of this one.  Create a new block from the
		 * beginning, add to list, and go to top of loop
		 * again.
		 *
		 * create new block from high portion of
		 * block, so that top block starts at desired
		 * addr.
		 */
		new_ent_addr = desired_min_addr;
		cvmx_booपंचांगem_phy_set_next(new_ent_addr,
					cvmx_booपंचांगem_phy_get_next
					(ent_addr));
		cvmx_booपंचांगem_phy_set_size(new_ent_addr,
					cvmx_booपंचांगem_phy_get_size
					(ent_addr) -
					(desired_min_addr -
						ent_addr));
		cvmx_booपंचांगem_phy_set_size(ent_addr,
					desired_min_addr - ent_addr);
		cvmx_booपंचांगem_phy_set_next(ent_addr, new_ent_addr);
		/* Loop again to handle actual alloc from new block */
	पूर्ण
error_out:
	/* We didn't find anything, so वापस error */
	अगर (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
		cvmx_booपंचांगem_unlock();
	वापस -1;
पूर्ण

पूर्णांक __cvmx_booपंचांगem_phy_मुक्त(uपूर्णांक64_t phy_addr, uपूर्णांक64_t size, uपूर्णांक32_t flags)
अणु
	uपूर्णांक64_t cur_addr;
	uपूर्णांक64_t prev_addr = 0; /* zero is invalid */
	पूर्णांक retval = 0;

#अगर_घोषित DEBUG
	cvmx_dम_लिखो("__cvmx_bootmem_phy_free addr: 0x%llx, size: 0x%llx\n",
		     (अचिन्हित दीर्घ दीर्घ)phy_addr, (अचिन्हित दीर्घ दीर्घ)size);
#पूर्ण_अगर
	अगर (cvmx_booपंचांगem_desc->major_version > 3) अणु
		cvmx_dम_लिखो("ERROR: Incompatible bootmem descriptor "
			     "version: %d.%d at addr: %p\n",
			     (पूर्णांक)cvmx_booपंचांगem_desc->major_version,
			     (पूर्णांक)cvmx_booपंचांगem_desc->minor_version,
			     cvmx_booपंचांगem_desc);
		वापस 0;
	पूर्ण

	/* 0 is not a valid size क्रम this allocator */
	अगर (!size)
		वापस 0;

	अगर (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
		cvmx_booपंचांगem_lock();
	cur_addr = cvmx_booपंचांगem_desc->head_addr;
	अगर (cur_addr == 0 || phy_addr < cur_addr) अणु
		/* add at front of list - special हाल with changing head ptr */
		अगर (cur_addr && phy_addr + size > cur_addr)
			जाओ booपंचांगem_मुक्त_करोne; /* error, overlapping section */
		अन्यथा अगर (phy_addr + size == cur_addr) अणु
			/* Add to front of existing first block */
			cvmx_booपंचांगem_phy_set_next(phy_addr,
						  cvmx_booपंचांगem_phy_get_next
						  (cur_addr));
			cvmx_booपंचांगem_phy_set_size(phy_addr,
						  cvmx_booपंचांगem_phy_get_size
						  (cur_addr) + size);
			cvmx_booपंचांगem_desc->head_addr = phy_addr;

		पूर्ण अन्यथा अणु
			/* New block beक्रमe first block.  OK अगर cur_addr is 0 */
			cvmx_booपंचांगem_phy_set_next(phy_addr, cur_addr);
			cvmx_booपंचांगem_phy_set_size(phy_addr, size);
			cvmx_booपंचांगem_desc->head_addr = phy_addr;
		पूर्ण
		retval = 1;
		जाओ booपंचांगem_मुक्त_करोne;
	पूर्ण

	/* Find place in list to add block */
	जबतक (cur_addr && phy_addr > cur_addr) अणु
		prev_addr = cur_addr;
		cur_addr = cvmx_booपंचांगem_phy_get_next(cur_addr);
	पूर्ण

	अगर (!cur_addr) अणु
		/*
		 * We have reached the end of the list, add on to end,
		 * checking to see अगर we need to combine with last
		 * block
		 */
		अगर (prev_addr + cvmx_booपंचांगem_phy_get_size(prev_addr) ==
		    phy_addr) अणु
			cvmx_booपंचांगem_phy_set_size(prev_addr,
						  cvmx_booपंचांगem_phy_get_size
						  (prev_addr) + size);
		पूर्ण अन्यथा अणु
			cvmx_booपंचांगem_phy_set_next(prev_addr, phy_addr);
			cvmx_booपंचांगem_phy_set_size(phy_addr, size);
			cvmx_booपंचांगem_phy_set_next(phy_addr, 0);
		पूर्ण
		retval = 1;
		जाओ booपंचांगem_मुक्त_करोne;
	पूर्ण अन्यथा अणु
		/*
		 * insert between prev and cur nodes, checking क्रम
		 * merge with either/both.
		 */
		अगर (prev_addr + cvmx_booपंचांगem_phy_get_size(prev_addr) ==
		    phy_addr) अणु
			/* Merge with previous */
			cvmx_booपंचांगem_phy_set_size(prev_addr,
						  cvmx_booपंचांगem_phy_get_size
						  (prev_addr) + size);
			अगर (phy_addr + size == cur_addr) अणु
				/* Also merge with current */
				cvmx_booपंचांगem_phy_set_size(prev_addr,
					cvmx_booपंचांगem_phy_get_size(cur_addr) +
					cvmx_booपंचांगem_phy_get_size(prev_addr));
				cvmx_booपंचांगem_phy_set_next(prev_addr,
					cvmx_booपंचांगem_phy_get_next(cur_addr));
			पूर्ण
			retval = 1;
			जाओ booपंचांगem_मुक्त_करोne;
		पूर्ण अन्यथा अगर (phy_addr + size == cur_addr) अणु
			/* Merge with current */
			cvmx_booपंचांगem_phy_set_size(phy_addr,
						  cvmx_booपंचांगem_phy_get_size
						  (cur_addr) + size);
			cvmx_booपंचांगem_phy_set_next(phy_addr,
						  cvmx_booपंचांगem_phy_get_next
						  (cur_addr));
			cvmx_booपंचांगem_phy_set_next(prev_addr, phy_addr);
			retval = 1;
			जाओ booपंचांगem_मुक्त_करोne;
		पूर्ण

		/* It is a standalone block, add in between prev and cur */
		cvmx_booपंचांगem_phy_set_size(phy_addr, size);
		cvmx_booपंचांगem_phy_set_next(phy_addr, cur_addr);
		cvmx_booपंचांगem_phy_set_next(prev_addr, phy_addr);

	पूर्ण
	retval = 1;

booपंचांगem_मुक्त_करोne:
	अगर (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
		cvmx_booपंचांगem_unlock();
	वापस retval;

पूर्ण

/**
 * Finds a named memory block by name.
 * Also used क्रम finding an unused entry in the named block table.
 *
 * @name: Name of memory block to find.	 If शून्य poपूर्णांकer given, then
 *	  finds unused descriptor, अगर available.
 *
 * @flags: Flags to control options क्रम the allocation.
 *
 * Returns Poपूर्णांकer to memory block descriptor, शून्य अगर not found.
 *	   If शून्य वापसed when name parameter is शून्य, then no memory
 *	   block descriptors are available.
 */
अटल काष्ठा cvmx_booपंचांगem_named_block_desc *
	cvmx_booपंचांगem_phy_named_block_find(अक्षर *name, uपूर्णांक32_t flags)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा cvmx_booपंचांगem_named_block_desc *named_block_array_ptr;

#अगर_घोषित DEBUG
	cvmx_dम_लिखो("cvmx_bootmem_phy_named_block_find: %s\n", name);
#पूर्ण_अगर
	/*
	 * Lock the काष्ठाure to make sure that it is not being
	 * changed जबतक we are examining it.
	 */
	अगर (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
		cvmx_booपंचांगem_lock();

	/* Use XKPHYS क्रम 64 bit linux */
	named_block_array_ptr = (काष्ठा cvmx_booपंचांगem_named_block_desc *)
	    cvmx_phys_to_ptr(cvmx_booपंचांगem_desc->named_block_array_addr);

#अगर_घोषित DEBUG
	cvmx_dम_लिखो
	    ("cvmx_bootmem_phy_named_block_find: named_block_array_ptr: %p\n",
	     named_block_array_ptr);
#पूर्ण_अगर
	अगर (cvmx_booपंचांगem_desc->major_version == 3) अणु
		क्रम (i = 0;
		     i < cvmx_booपंचांगem_desc->named_block_num_blocks; i++) अणु
			अगर ((name && named_block_array_ptr[i].size
			     && !म_भेदन(name, named_block_array_ptr[i].name,
					 cvmx_booपंचांगem_desc->named_block_name_len
					 - 1))
			    || (!name && !named_block_array_ptr[i].size)) अणु
				अगर (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
					cvmx_booपंचांगem_unlock();

				वापस &(named_block_array_ptr[i]);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		cvmx_dम_लिखो("ERROR: Incompatible bootmem descriptor "
			     "version: %d.%d at addr: %p\n",
			     (पूर्णांक)cvmx_booपंचांगem_desc->major_version,
			     (पूर्णांक)cvmx_booपंचांगem_desc->minor_version,
			     cvmx_booपंचांगem_desc);
	पूर्ण
	अगर (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
		cvmx_booपंचांगem_unlock();

	वापस शून्य;
पूर्ण

व्योम *cvmx_booपंचांगem_alloc_named_range_once(uपूर्णांक64_t size, uपूर्णांक64_t min_addr,
					  uपूर्णांक64_t max_addr, uपूर्णांक64_t align,
					  अक्षर *name,
					  व्योम (*init) (व्योम *))
अणु
	पूर्णांक64_t addr;
	व्योम *ptr;
	uपूर्णांक64_t named_block_desc_addr;

	named_block_desc_addr = (uपूर्णांक64_t)
		cvmx_booपंचांगem_phy_named_block_find(name,
						  (uपूर्णांक32_t)CVMX_BOOTMEM_FLAG_NO_LOCKING);

	अगर (named_block_desc_addr) अणु
		addr = CVMX_BOOTMEM_NAMED_GET_FIELD(named_block_desc_addr,
						    base_addr);
		वापस cvmx_phys_to_ptr(addr);
	पूर्ण

	addr = cvmx_booपंचांगem_phy_named_block_alloc(size, min_addr, max_addr,
						  align, name,
						  (uपूर्णांक32_t)CVMX_BOOTMEM_FLAG_NO_LOCKING);

	अगर (addr < 0)
		वापस शून्य;
	ptr = cvmx_phys_to_ptr(addr);

	अगर (init)
		init(ptr);
	अन्यथा
		स_रखो(ptr, 0, size);

	वापस ptr;
पूर्ण
EXPORT_SYMBOL(cvmx_booपंचांगem_alloc_named_range_once);

काष्ठा cvmx_booपंचांगem_named_block_desc *cvmx_booपंचांगem_find_named_block(अक्षर *name)
अणु
	वापस cvmx_booपंचांगem_phy_named_block_find(name, 0);
पूर्ण
EXPORT_SYMBOL(cvmx_booपंचांगem_find_named_block);

/**
 * Frees a named block.
 *
 * @name:   name of block to मुक्त
 * @flags:  flags क्रम passing options
 *
 * Returns 0 on failure
 *	   1 on success
 */
अटल पूर्णांक cvmx_booपंचांगem_phy_named_block_मुक्त(अक्षर *name, uपूर्णांक32_t flags)
अणु
	काष्ठा cvmx_booपंचांगem_named_block_desc *named_block_ptr;

	अगर (cvmx_booपंचांगem_desc->major_version != 3) अणु
		cvmx_dम_लिखो("ERROR: Incompatible bootmem descriptor version: "
			     "%d.%d at addr: %p\n",
			     (पूर्णांक)cvmx_booपंचांगem_desc->major_version,
			     (पूर्णांक)cvmx_booपंचांगem_desc->minor_version,
			     cvmx_booपंचांगem_desc);
		वापस 0;
	पूर्ण
#अगर_घोषित DEBUG
	cvmx_dम_लिखो("cvmx_bootmem_phy_named_block_free: %s\n", name);
#पूर्ण_अगर

	/*
	 * Take lock here, as name lookup/block मुक्त/name मुक्त need to
	 * be atomic.
	 */
	cvmx_booपंचांगem_lock();

	named_block_ptr =
	    cvmx_booपंचांगem_phy_named_block_find(name,
					      CVMX_BOOTMEM_FLAG_NO_LOCKING);
	अगर (named_block_ptr) अणु
#अगर_घोषित DEBUG
		cvmx_dम_लिखो("cvmx_bootmem_phy_named_block_free: "
			     "%s, base: 0x%llx, size: 0x%llx\n",
			     name,
			     (अचिन्हित दीर्घ दीर्घ)named_block_ptr->base_addr,
			     (अचिन्हित दीर्घ दीर्घ)named_block_ptr->size);
#पूर्ण_अगर
		__cvmx_booपंचांगem_phy_मुक्त(named_block_ptr->base_addr,
					named_block_ptr->size,
					CVMX_BOOTMEM_FLAG_NO_LOCKING);
		named_block_ptr->size = 0;
		/* Set size to zero to indicate block not used. */
	पूर्ण

	cvmx_booपंचांगem_unlock();
	वापस named_block_ptr != शून्य; /* 0 on failure, 1 on success */
पूर्ण

पूर्णांक cvmx_booपंचांगem_मुक्त_named(अक्षर *name)
अणु
	वापस cvmx_booपंचांगem_phy_named_block_मुक्त(name, 0);
पूर्ण

पूर्णांक64_t cvmx_booपंचांगem_phy_named_block_alloc(uपूर्णांक64_t size, uपूर्णांक64_t min_addr,
					   uपूर्णांक64_t max_addr,
					   uपूर्णांक64_t alignment,
					   अक्षर *name,
					   uपूर्णांक32_t flags)
अणु
	पूर्णांक64_t addr_allocated;
	काष्ठा cvmx_booपंचांगem_named_block_desc *named_block_desc_ptr;

#अगर_घोषित DEBUG
	cvmx_dम_लिखो("cvmx_bootmem_phy_named_block_alloc: size: 0x%llx, min: "
		     "0x%llx, max: 0x%llx, align: 0x%llx, name: %s\n",
		     (अचिन्हित दीर्घ दीर्घ)size,
		     (अचिन्हित दीर्घ दीर्घ)min_addr,
		     (अचिन्हित दीर्घ दीर्घ)max_addr,
		     (अचिन्हित दीर्घ दीर्घ)alignment,
		     name);
#पूर्ण_अगर
	अगर (cvmx_booपंचांगem_desc->major_version != 3) अणु
		cvmx_dम_लिखो("ERROR: Incompatible bootmem descriptor version: "
			     "%d.%d at addr: %p\n",
			     (पूर्णांक)cvmx_booपंचांगem_desc->major_version,
			     (पूर्णांक)cvmx_booपंचांगem_desc->minor_version,
			     cvmx_booपंचांगem_desc);
		वापस -1;
	पूर्ण

	/*
	 * Take lock here, as name lookup/block alloc/name add need to
	 * be atomic.
	 */
	अगर (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
		cvmx_spinlock_lock((cvmx_spinlock_t *)&(cvmx_booपंचांगem_desc->lock));

	/* Get poपूर्णांकer to first available named block descriptor */
	named_block_desc_ptr =
		cvmx_booपंचांगem_phy_named_block_find(शून्य,
						  flags | CVMX_BOOTMEM_FLAG_NO_LOCKING);

	/*
	 * Check to see अगर name alपढ़ोy in use, वापस error अगर name
	 * not available or no more room क्रम blocks.
	 */
	अगर (cvmx_booपंचांगem_phy_named_block_find(name,
					      flags | CVMX_BOOTMEM_FLAG_NO_LOCKING) || !named_block_desc_ptr) अणु
		अगर (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
			cvmx_spinlock_unlock((cvmx_spinlock_t *)&(cvmx_booपंचांगem_desc->lock));
		वापस -1;
	पूर्ण


	/*
	 * Round size up to mult of minimum alignment bytes We need
	 * the actual size allocated to allow क्रम blocks to be
	 * coalesced when they are मुक्तd. The alloc routine करोes the
	 * same rounding up on all allocations.
	 */
	size = ALIGN(size, CVMX_BOOTMEM_ALIGNMENT_SIZE);

	addr_allocated = cvmx_booपंचांगem_phy_alloc(size, min_addr, max_addr,
						alignment,
						flags | CVMX_BOOTMEM_FLAG_NO_LOCKING);
	अगर (addr_allocated >= 0) अणु
		named_block_desc_ptr->base_addr = addr_allocated;
		named_block_desc_ptr->size = size;
		म_नकलन(named_block_desc_ptr->name, name,
			cvmx_booपंचांगem_desc->named_block_name_len);
		named_block_desc_ptr->name[cvmx_booपंचांगem_desc->named_block_name_len - 1] = 0;
	पूर्ण

	अगर (!(flags & CVMX_BOOTMEM_FLAG_NO_LOCKING))
		cvmx_spinlock_unlock((cvmx_spinlock_t *)&(cvmx_booपंचांगem_desc->lock));
	वापस addr_allocated;
पूर्ण

काष्ठा cvmx_booपंचांगem_desc *cvmx_booपंचांगem_get_desc(व्योम)
अणु
	वापस cvmx_booपंचांगem_desc;
पूर्ण
