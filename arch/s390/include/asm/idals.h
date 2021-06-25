<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 *		    Martin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 2000
 *
 * History of changes
 * 07/24/00 new file
 * 05/04/02 code reकाष्ठाuring.
 */

#अगर_अघोषित _S390_IDALS_H
#घोषणा _S390_IDALS_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/cपन.स>
#समावेश <linux/uaccess.h>

#घोषणा IDA_SIZE_LOG 12 /* 11 क्रम 2k , 12 क्रम 4k */
#घोषणा IDA_BLOCK_SIZE (1L<<IDA_SIZE_LOG)

/*
 * Test अगर an address/length pair needs an idal list.
 */
अटल अंतरभूत पूर्णांक
idal_is_needed(व्योम *vaddr, अचिन्हित पूर्णांक length)
अणु
	वापस ((__pa(vaddr) + length - 1) >> 31) != 0;
पूर्ण


/*
 * Return the number of idal words needed क्रम an address/length pair.
 */
अटल अंतरभूत अचिन्हित पूर्णांक idal_nr_words(व्योम *vaddr, अचिन्हित पूर्णांक length)
अणु
	वापस ((__pa(vaddr) & (IDA_BLOCK_SIZE-1)) + length +
		(IDA_BLOCK_SIZE-1)) >> IDA_SIZE_LOG;
पूर्ण

/*
 * Create the list of idal words क्रम an address/length pair.
 */
अटल अंतरभूत अचिन्हित दीर्घ *idal_create_words(अचिन्हित दीर्घ *idaws,
					       व्योम *vaddr, अचिन्हित पूर्णांक length)
अणु
	अचिन्हित दीर्घ paddr;
	अचिन्हित पूर्णांक cidaw;

	paddr = __pa(vaddr);
	cidaw = ((paddr & (IDA_BLOCK_SIZE-1)) + length + 
		 (IDA_BLOCK_SIZE-1)) >> IDA_SIZE_LOG;
	*idaws++ = paddr;
	paddr &= -IDA_BLOCK_SIZE;
	जबतक (--cidaw > 0) अणु
		paddr += IDA_BLOCK_SIZE;
		*idaws++ = paddr;
	पूर्ण
	वापस idaws;
पूर्ण

/*
 * Sets the address of the data in CCW.
 * If necessary it allocates an IDAL and sets the appropriate flags.
 */
अटल अंतरभूत पूर्णांक
set_normalized_cda(काष्ठा ccw1 * ccw, व्योम *vaddr)
अणु
	अचिन्हित पूर्णांक nridaws;
	अचिन्हित दीर्घ *idal;

	अगर (ccw->flags & CCW_FLAG_IDA)
		वापस -EINVAL;
	nridaws = idal_nr_words(vaddr, ccw->count);
	अगर (nridaws > 0) अणु
		idal = kदो_स्मृति(nridaws * माप(अचिन्हित दीर्घ),
			       GFP_ATOMIC | GFP_DMA );
		अगर (idal == शून्य)
			वापस -ENOMEM;
		idal_create_words(idal, vaddr, ccw->count);
		ccw->flags |= CCW_FLAG_IDA;
		vaddr = idal;
	पूर्ण
	ccw->cda = (__u32)(अचिन्हित दीर्घ) vaddr;
	वापस 0;
पूर्ण

/*
 * Releases any allocated IDAL related to the CCW.
 */
अटल अंतरभूत व्योम
clear_normalized_cda(काष्ठा ccw1 * ccw)
अणु
	अगर (ccw->flags & CCW_FLAG_IDA) अणु
		kमुक्त((व्योम *)(अचिन्हित दीर्घ) ccw->cda);
		ccw->flags &= ~CCW_FLAG_IDA;
	पूर्ण
	ccw->cda = 0;
पूर्ण

/*
 * Idal buffer extension
 */
काष्ठा idal_buffer अणु
	माप_प्रकार size;
	माप_प्रकार page_order;
	व्योम *data[0];
पूर्ण;

/*
 * Allocate an idal buffer
 */
अटल अंतरभूत काष्ठा idal_buffer *
idal_buffer_alloc(माप_प्रकार size, पूर्णांक page_order)
अणु
	काष्ठा idal_buffer *ib;
	पूर्णांक nr_chunks, nr_ptrs, i;

	nr_ptrs = (size + IDA_BLOCK_SIZE - 1) >> IDA_SIZE_LOG;
	nr_chunks = (4096 << page_order) >> IDA_SIZE_LOG;
	ib = kदो_स्मृति(काष्ठा_size(ib, data, nr_ptrs), GFP_DMA | GFP_KERNEL);
	अगर (ib == शून्य)
		वापस ERR_PTR(-ENOMEM);
	ib->size = size;
	ib->page_order = page_order;
	क्रम (i = 0; i < nr_ptrs; i++) अणु
		अगर ((i & (nr_chunks - 1)) != 0) अणु
			ib->data[i] = ib->data[i-1] + IDA_BLOCK_SIZE;
			जारी;
		पूर्ण
		ib->data[i] = (व्योम *)
			__get_मुक्त_pages(GFP_KERNEL, page_order);
		अगर (ib->data[i] != शून्य)
			जारी;
		// Not enough memory
		जबतक (i >= nr_chunks) अणु
			i -= nr_chunks;
			मुक्त_pages((अचिन्हित दीर्घ) ib->data[i],
				   ib->page_order);
		पूर्ण
		kमुक्त(ib);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	वापस ib;
पूर्ण

/*
 * Free an idal buffer.
 */
अटल अंतरभूत व्योम
idal_buffer_मुक्त(काष्ठा idal_buffer *ib)
अणु
	पूर्णांक nr_chunks, nr_ptrs, i;

	nr_ptrs = (ib->size + IDA_BLOCK_SIZE - 1) >> IDA_SIZE_LOG;
	nr_chunks = (4096 << ib->page_order) >> IDA_SIZE_LOG;
	क्रम (i = 0; i < nr_ptrs; i += nr_chunks)
		मुक्त_pages((अचिन्हित दीर्घ) ib->data[i], ib->page_order);
	kमुक्त(ib);
पूर्ण

/*
 * Test अगर a idal list is really needed.
 */
अटल अंतरभूत पूर्णांक
__idal_buffer_is_needed(काष्ठा idal_buffer *ib)
अणु
	वापस ib->size > (4096ul << ib->page_order) ||
		idal_is_needed(ib->data[0], ib->size);
पूर्ण

/*
 * Set channel data address to idal buffer.
 */
अटल अंतरभूत व्योम
idal_buffer_set_cda(काष्ठा idal_buffer *ib, काष्ठा ccw1 *ccw)
अणु
	अगर (__idal_buffer_is_needed(ib)) अणु
		// setup idals;
		ccw->cda = (u32)(addr_t) ib->data;
		ccw->flags |= CCW_FLAG_IDA;
	पूर्ण अन्यथा
		// we करो not need idals - use direct addressing
		ccw->cda = (u32)(addr_t) ib->data[0];
	ccw->count = ib->size;
पूर्ण

/*
 * Copy count bytes from an idal buffer to user memory
 */
अटल अंतरभूत माप_प्रकार
idal_buffer_to_user(काष्ठा idal_buffer *ib, व्योम __user *to, माप_प्रकार count)
अणु
	माप_प्रकार left;
	पूर्णांक i;

	BUG_ON(count > ib->size);
	क्रम (i = 0; count > IDA_BLOCK_SIZE; i++) अणु
		left = copy_to_user(to, ib->data[i], IDA_BLOCK_SIZE);
		अगर (left)
			वापस left + count - IDA_BLOCK_SIZE;
		to = (व्योम __user *) to + IDA_BLOCK_SIZE;
		count -= IDA_BLOCK_SIZE;
	पूर्ण
	वापस copy_to_user(to, ib->data[i], count);
पूर्ण

/*
 * Copy count bytes from user memory to an idal buffer
 */
अटल अंतरभूत माप_प्रकार
idal_buffer_from_user(काष्ठा idal_buffer *ib, स्थिर व्योम __user *from, माप_प्रकार count)
अणु
	माप_प्रकार left;
	पूर्णांक i;

	BUG_ON(count > ib->size);
	क्रम (i = 0; count > IDA_BLOCK_SIZE; i++) अणु
		left = copy_from_user(ib->data[i], from, IDA_BLOCK_SIZE);
		अगर (left)
			वापस left + count - IDA_BLOCK_SIZE;
		from = (व्योम __user *) from + IDA_BLOCK_SIZE;
		count -= IDA_BLOCK_SIZE;
	पूर्ण
	वापस copy_from_user(ib->data[i], from, count);
पूर्ण

#पूर्ण_अगर
