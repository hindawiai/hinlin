<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2010 Cavium Networks
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>

#समावेश "octeon-ethernet.h"
#समावेश "ethernet-mem.h"
#समावेश "ethernet-defines.h"

/**
 * cvm_oct_fill_hw_skbuff - fill the supplied hardware pool with skbuffs
 * @pool:     Pool to allocate an skbuff क्रम
 * @size:     Size of the buffer needed क्रम the pool
 * @elements: Number of buffers to allocate
 *
 * Returns the actual number of buffers allocated.
 */
अटल पूर्णांक cvm_oct_fill_hw_skbuff(पूर्णांक pool, पूर्णांक size, पूर्णांक elements)
अणु
	पूर्णांक मुक्तd = elements;

	जबतक (मुक्तd) अणु
		काष्ठा sk_buff *skb = dev_alloc_skb(size + 256);

		अगर (unlikely(!skb))
			अवरोध;
		skb_reserve(skb, 256 - (((अचिन्हित दीर्घ)skb->data) & 0x7f));
		*(काष्ठा sk_buff **)(skb->data - माप(व्योम *)) = skb;
		cvmx_fpa_मुक्त(skb->data, pool, size / 128);
		मुक्तd--;
	पूर्ण
	वापस elements - मुक्तd;
पूर्ण

/**
 * cvm_oct_मुक्त_hw_skbuff- मुक्त hardware pool skbuffs
 * @pool:     Pool to allocate an skbuff क्रम
 * @size:     Size of the buffer needed क्रम the pool
 * @elements: Number of buffers to allocate
 */
अटल व्योम cvm_oct_मुक्त_hw_skbuff(पूर्णांक pool, पूर्णांक size, पूर्णांक elements)
अणु
	अक्षर *memory;

	करो अणु
		memory = cvmx_fpa_alloc(pool);
		अगर (memory) अणु
			काष्ठा sk_buff *skb =
			    *(काष्ठा sk_buff **)(memory - माप(व्योम *));
			elements--;
			dev_kमुक्त_skb(skb);
		पूर्ण
	पूर्ण जबतक (memory);

	अगर (elements < 0)
		pr_warn("Freeing of pool %u had too many skbuffs (%d)\n",
			pool, elements);
	अन्यथा अगर (elements > 0)
		pr_warn("Freeing of pool %u is missing %d skbuffs\n",
			pool, elements);
पूर्ण

/**
 * cvm_oct_fill_hw_memory - fill a hardware pool with memory.
 * @pool:     Pool to populate
 * @size:     Size of each buffer in the pool
 * @elements: Number of buffers to allocate
 *
 * Returns the actual number of buffers allocated.
 */
अटल पूर्णांक cvm_oct_fill_hw_memory(पूर्णांक pool, पूर्णांक size, पूर्णांक elements)
अणु
	अक्षर *memory;
	अक्षर *fpa;
	पूर्णांक मुक्तd = elements;

	जबतक (मुक्तd) अणु
		/*
		 * FPA memory must be 128 byte aligned.  Since we are
		 * aligning we need to save the original poपूर्णांकer so we
		 * can feed it to kमुक्त when the memory is वापसed to
		 * the kernel.
		 *
		 * We allocate an extra 256 bytes to allow क्रम
		 * alignment and space क्रम the original poपूर्णांकer saved
		 * just beक्रमe the block.
		 */
		memory = kदो_स्मृति(size + 256, GFP_ATOMIC);
		अगर (unlikely(!memory)) अणु
			pr_warn("Unable to allocate %u bytes for FPA pool %d\n",
				elements * size, pool);
			अवरोध;
		पूर्ण
		fpa = (अक्षर *)(((अचिन्हित दीर्घ)memory + 256) & ~0x7fUL);
		*((अक्षर **)fpa - 1) = memory;
		cvmx_fpa_मुक्त(fpa, pool, 0);
		मुक्तd--;
	पूर्ण
	वापस elements - मुक्तd;
पूर्ण

/**
 * cvm_oct_मुक्त_hw_memory - Free memory allocated by cvm_oct_fill_hw_memory
 * @pool:     FPA pool to मुक्त
 * @size:     Size of each buffer in the pool
 * @elements: Number of buffers that should be in the pool
 */
अटल व्योम cvm_oct_मुक्त_hw_memory(पूर्णांक pool, पूर्णांक size, पूर्णांक elements)
अणु
	अक्षर *memory;
	अक्षर *fpa;

	करो अणु
		fpa = cvmx_fpa_alloc(pool);
		अगर (fpa) अणु
			elements--;
			fpa = (अक्षर *)phys_to_virt(cvmx_ptr_to_phys(fpa));
			memory = *((अक्षर **)fpa - 1);
			kमुक्त(memory);
		पूर्ण
	पूर्ण जबतक (fpa);

	अगर (elements < 0)
		pr_warn("Freeing of pool %u had too many buffers (%d)\n",
			pool, elements);
	अन्यथा अगर (elements > 0)
		pr_warn("Warning: Freeing of pool %u is missing %d buffers\n",
			pool, elements);
पूर्ण

पूर्णांक cvm_oct_mem_fill_fpa(पूर्णांक pool, पूर्णांक size, पूर्णांक elements)
अणु
	पूर्णांक मुक्तd;

	अगर (pool == CVMX_FPA_PACKET_POOL)
		मुक्तd = cvm_oct_fill_hw_skbuff(pool, size, elements);
	अन्यथा
		मुक्तd = cvm_oct_fill_hw_memory(pool, size, elements);
	वापस मुक्तd;
पूर्ण

व्योम cvm_oct_mem_empty_fpa(पूर्णांक pool, पूर्णांक size, पूर्णांक elements)
अणु
	अगर (pool == CVMX_FPA_PACKET_POOL)
		cvm_oct_मुक्त_hw_skbuff(pool, size, elements);
	अन्यथा
		cvm_oct_मुक्त_hw_memory(pool, size, elements);
पूर्ण
