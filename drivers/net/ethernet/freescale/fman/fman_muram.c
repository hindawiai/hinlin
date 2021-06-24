<शैली गुरु>
/*
 * Copyright 2008-2015 Freescale Semiconductor Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश "fman_muram.h"

#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/genभाग.स>

काष्ठा muram_info अणु
	काष्ठा gen_pool *pool;
	व्योम __iomem *vbase;
	माप_प्रकार size;
	phys_addr_t pbase;
पूर्ण;

अटल अचिन्हित दीर्घ fman_muram_vbase_to_offset(काष्ठा muram_info *muram,
						अचिन्हित दीर्घ vaddr)
अणु
	वापस vaddr - (अचिन्हित दीर्घ)muram->vbase;
पूर्ण

/**
 * fman_muram_init
 * @base:	Poपूर्णांकer to base of memory mapped FM-MURAM.
 * @size:	Size of the FM-MURAM partition.
 *
 * Creates partition in the MURAM.
 * The routine वापसs a poपूर्णांकer to the MURAM partition.
 * This poपूर्णांकer must be passed as to all other FM-MURAM function calls.
 * No actual initialization or configuration of FM_MURAM hardware is करोne by
 * this routine.
 *
 * Return: poपूर्णांकer to FM-MURAM object, or शून्य क्रम Failure.
 */
काष्ठा muram_info *fman_muram_init(phys_addr_t base, माप_प्रकार size)
अणु
	काष्ठा muram_info *muram;
	व्योम __iomem *vaddr;
	पूर्णांक ret;

	muram = kzalloc(माप(*muram), GFP_KERNEL);
	अगर (!muram)
		वापस शून्य;

	muram->pool = gen_pool_create(ilog2(64), -1);
	अगर (!muram->pool) अणु
		pr_err("%s(): MURAM pool create failed\n", __func__);
		जाओ  muram_मुक्त;
	पूर्ण

	vaddr = ioremap(base, size);
	अगर (!vaddr) अणु
		pr_err("%s(): MURAM ioremap failed\n", __func__);
		जाओ pool_destroy;
	पूर्ण

	ret = gen_pool_add_virt(muram->pool, (अचिन्हित दीर्घ)vaddr,
				base, size, -1);
	अगर (ret < 0) अणु
		pr_err("%s(): MURAM pool add failed\n", __func__);
		iounmap(vaddr);
		जाओ pool_destroy;
	पूर्ण

	स_रखो_io(vaddr, 0, (पूर्णांक)size);

	muram->vbase = vaddr;
	muram->pbase = base;
	वापस muram;

pool_destroy:
	gen_pool_destroy(muram->pool);
muram_मुक्त:
	kमुक्त(muram);
	वापस शून्य;
पूर्ण

/**
 * fman_muram_offset_to_vbase
 * @muram:	FM-MURAM module poपूर्णांकer.
 * @offset:	the offset of the memory block
 *
 * Gives the address of the memory region from specअगरic offset
 *
 * Return: The address of the memory block
 */
अचिन्हित दीर्घ fman_muram_offset_to_vbase(काष्ठा muram_info *muram,
					 अचिन्हित दीर्घ offset)
अणु
	वापस offset + (अचिन्हित दीर्घ)muram->vbase;
पूर्ण

/**
 * fman_muram_alloc
 * @muram:	FM-MURAM module poपूर्णांकer.
 * @size:	Size of the memory to be allocated.
 *
 * Allocate some memory from FM-MURAM partition.
 *
 * Return: address of the allocated memory; शून्य otherwise.
 */
अचिन्हित दीर्घ fman_muram_alloc(काष्ठा muram_info *muram, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ vaddr;

	vaddr = gen_pool_alloc(muram->pool, size);
	अगर (!vaddr)
		वापस -ENOMEM;

	स_रखो_io((व्योम __iomem *)vaddr, 0, size);

	वापस fman_muram_vbase_to_offset(muram, vaddr);
पूर्ण

/**
 * fman_muram_मुक्त_mem
 * @muram:	FM-MURAM module poपूर्णांकer.
 * @offset:	offset of the memory region to be मुक्तd.
 * @size:	size of the memory to be मुक्तd.
 *
 * Free an allocated memory from FM-MURAM partition.
 */
व्योम fman_muram_मुक्त_mem(काष्ठा muram_info *muram, अचिन्हित दीर्घ offset,
			 माप_प्रकार size)
अणु
	अचिन्हित दीर्घ addr = fman_muram_offset_to_vbase(muram, offset);

	gen_pool_मुक्त(muram->pool, addr, size);
पूर्ण
