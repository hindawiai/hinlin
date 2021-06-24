<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2017 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#समावेश "vmwgfx_drv.h"
#समावेश <linux/highस्मृति.स>

/*
 * Template that implements find_first_dअगरf() क्रम a generic
 * अचिन्हित पूर्णांकeger type. @size and वापस value are in bytes.
 */
#घोषणा VMW_FIND_FIRST_DIFF(_type)			 \
अटल माप_प्रकार vmw_find_first_dअगरf_ ## _type		 \
	(स्थिर _type * dst, स्थिर _type * src, माप_प्रकार size)\
अणु							 \
	माप_प्रकार i;					 \
							 \
	क्रम (i = 0; i < size; i += माप(_type)) अणु	 \
		अगर (*dst++ != *src++)			 \
			अवरोध;				 \
	पूर्ण						 \
							 \
	वापस i;					 \
पूर्ण


/*
 * Template that implements find_last_dअगरf() क्रम a generic
 * अचिन्हित पूर्णांकeger type. Poपूर्णांकers poपूर्णांक to the item following the
 * *end* of the area to be examined. @size and वापस value are in
 * bytes.
 */
#घोषणा VMW_FIND_LAST_DIFF(_type)					\
अटल sमाप_प्रकार vmw_find_last_dअगरf_ ## _type(				\
	स्थिर _type * dst, स्थिर _type * src, माप_प्रकार size)		\
अणु									\
	जबतक (size) अणु							\
		अगर (*--dst != *--src)					\
			अवरोध;						\
									\
		size -= माप(_type);					\
	पूर्ण								\
	वापस size;							\
पूर्ण


/*
 * Instantiate find dअगरf functions क्रम relevant अचिन्हित पूर्णांकeger sizes,
 * assuming that wider पूर्णांकegers are faster (including aligning) up to the
 * architecture native width, which is assumed to be 32 bit unless
 * CONFIG_64BIT is defined.
 */
VMW_FIND_FIRST_DIFF(u8);
VMW_FIND_LAST_DIFF(u8);

VMW_FIND_FIRST_DIFF(u16);
VMW_FIND_LAST_DIFF(u16);

VMW_FIND_FIRST_DIFF(u32);
VMW_FIND_LAST_DIFF(u32);

#अगर_घोषित CONFIG_64BIT
VMW_FIND_FIRST_DIFF(u64);
VMW_FIND_LAST_DIFF(u64);
#पूर्ण_अगर


/* We use size aligned copies. This computes (addr - align(addr)) */
#घोषणा SPILL(_var, _type) ((अचिन्हित दीर्घ) _var & (माप(_type) - 1))


/*
 * Template to compute find_first_dअगरf() क्रम a certain पूर्णांकeger type
 * including a head copy क्रम alignment, and adjusपंचांगent of parameters
 * क्रम tail find or increased resolution find using an अचिन्हित पूर्णांकeger find
 * of smaller width. If finding is complete, and resolution is sufficient,
 * the macro executes a वापस statement. Otherwise it falls through.
 */
#घोषणा VMW_TRY_FIND_FIRST_DIFF(_type)					\
करो अणु									\
	अचिन्हित पूर्णांक spill = SPILL(dst, _type);				\
	माप_प्रकार dअगरf_offs;						\
									\
	अगर (spill && spill == SPILL(src, _type) &&			\
	    माप(_type) - spill <= size) अणु				\
		spill = माप(_type) - spill;				\
		dअगरf_offs = vmw_find_first_dअगरf_u8(dst, src, spill);	\
		अगर (dअगरf_offs < spill)					\
			वापस round_करोwn(offset + dअगरf_offs, granularity); \
									\
		dst += spill;						\
		src += spill;						\
		size -= spill;						\
		offset += spill;					\
		spill = 0;						\
	पूर्ण								\
	अगर (!spill && !SPILL(src, _type)) अणु				\
		माप_प्रकार to_copy = size &	 ~(माप(_type) - 1);		\
									\
		dअगरf_offs = vmw_find_first_dअगरf_ ## _type		\
			((_type *) dst, (_type *) src, to_copy);	\
		अगर (dअगरf_offs >= size || granularity == माप(_type))	\
			वापस (offset + dअगरf_offs);			\
									\
		dst += dअगरf_offs;					\
		src += dअगरf_offs;					\
		size -= dअगरf_offs;					\
		offset += dअगरf_offs;					\
	पूर्ण								\
पूर्ण जबतक (0)								\


/**
 * vmw_find_first_dअगरf - find the first dअगरference between dst and src
 *
 * @dst: The destination address
 * @src: The source address
 * @size: Number of bytes to compare
 * @granularity: The granularity needed क्रम the वापस value in bytes.
 * वापस: The offset from find start where the first dअगरference was
 * encountered in bytes. If no dअगरference was found, the function वापसs
 * a value >= @size.
 */
अटल माप_प्रकार vmw_find_first_dअगरf(स्थिर u8 *dst, स्थिर u8 *src, माप_प्रकार size,
				  माप_प्रकार granularity)
अणु
	माप_प्रकार offset = 0;

	/*
	 * Try finding with large पूर्णांकegers अगर alignment allows, or we can
	 * fix it. Fall through अगर we need better resolution or alignment
	 * was bad.
	 */
#अगर_घोषित CONFIG_64BIT
	VMW_TRY_FIND_FIRST_DIFF(u64);
#पूर्ण_अगर
	VMW_TRY_FIND_FIRST_DIFF(u32);
	VMW_TRY_FIND_FIRST_DIFF(u16);

	वापस round_करोwn(offset + vmw_find_first_dअगरf_u8(dst, src, size),
			  granularity);
पूर्ण


/*
 * Template to compute find_last_dअगरf() क्रम a certain पूर्णांकeger type
 * including a tail copy क्रम alignment, and adjusपंचांगent of parameters
 * क्रम head find or increased resolution find using an अचिन्हित पूर्णांकeger find
 * of smaller width. If finding is complete, and resolution is sufficient,
 * the macro executes a वापस statement. Otherwise it falls through.
 */
#घोषणा VMW_TRY_FIND_LAST_DIFF(_type)					\
करो अणु									\
	अचिन्हित पूर्णांक spill = SPILL(dst, _type);				\
	sमाप_प्रकार location;						\
	sमाप_प्रकार dअगरf_offs;						\
									\
	अगर (spill && spill <= size && spill == SPILL(src, _type)) अणु	\
		dअगरf_offs = vmw_find_last_dअगरf_u8(dst, src, spill);	\
		अगर (dअगरf_offs) अणु					\
			location = size - spill + dअगरf_offs - 1;	\
			वापस round_करोwn(location, granularity);	\
		पूर्ण							\
									\
		dst -= spill;						\
		src -= spill;						\
		size -= spill;						\
		spill = 0;						\
	पूर्ण								\
	अगर (!spill && !SPILL(src, _type)) अणु				\
		माप_प्रकार to_copy = round_करोwn(size, माप(_type));	\
									\
		dअगरf_offs = vmw_find_last_dअगरf_ ## _type		\
			((_type *) dst, (_type *) src, to_copy);	\
		location = size - to_copy + dअगरf_offs - माप(_type);	\
		अगर (location < 0 || granularity == माप(_type))	\
			वापस location;				\
									\
		dst -= to_copy - dअगरf_offs;				\
		src -= to_copy - dअगरf_offs;				\
		size -= to_copy - dअगरf_offs;				\
	पूर्ण								\
पूर्ण जबतक (0)


/**
 * vmw_find_last_dअगरf - find the last dअगरference between dst and src
 *
 * @dst: The destination address
 * @src: The source address
 * @size: Number of bytes to compare
 * @granularity: The granularity needed क्रम the वापस value in bytes.
 * वापस: The offset from find start where the last dअगरference was
 * encountered in bytes, or a negative value अगर no dअगरference was found.
 */
अटल sमाप_प्रकार vmw_find_last_dअगरf(स्थिर u8 *dst, स्थिर u8 *src, माप_प्रकार size,
				  माप_प्रकार granularity)
अणु
	dst += size;
	src += size;

#अगर_घोषित CONFIG_64BIT
	VMW_TRY_FIND_LAST_DIFF(u64);
#पूर्ण_अगर
	VMW_TRY_FIND_LAST_DIFF(u32);
	VMW_TRY_FIND_LAST_DIFF(u16);

	वापस round_करोwn(vmw_find_last_dअगरf_u8(dst, src, size) - 1,
			  granularity);
पूर्ण


/**
 * vmw_स_नकल - A wrapper around kernel स_नकल with allowing to plug it पूर्णांकo a
 * काष्ठा vmw_dअगरf_cpy.
 *
 * @dअगरf: The काष्ठा vmw_dअगरf_cpy closure argument (unused).
 * @dest: The copy destination.
 * @src: The copy source.
 * @n: Number of bytes to copy.
 */
व्योम vmw_स_नकल(काष्ठा vmw_dअगरf_cpy *dअगरf, u8 *dest, स्थिर u8 *src, माप_प्रकार n)
अणु
	स_नकल(dest, src, n);
पूर्ण


/**
 * vmw_adjust_rect - Adjust rectangle coordinates क्रम newly found dअगरference
 *
 * @dअगरf: The काष्ठा vmw_dअगरf_cpy used to track the modअगरied bounding box.
 * @dअगरf_offs: The offset from @dअगरf->line_offset where the dअगरference was
 * found.
 */
अटल व्योम vmw_adjust_rect(काष्ठा vmw_dअगरf_cpy *dअगरf, माप_प्रकार dअगरf_offs)
अणु
	माप_प्रकार offs = (dअगरf_offs + dअगरf->line_offset) / dअगरf->cpp;
	काष्ठा drm_rect *rect = &dअगरf->rect;

	rect->x1 = min_t(पूर्णांक, rect->x1, offs);
	rect->x2 = max_t(पूर्णांक, rect->x2, offs + 1);
	rect->y1 = min_t(पूर्णांक, rect->y1, dअगरf->line);
	rect->y2 = max_t(पूर्णांक, rect->y2, dअगरf->line + 1);
पूर्ण

/**
 * vmw_dअगरf_स_नकल - स_नकल that creates a bounding box of modअगरied content.
 *
 * @dअगरf: The काष्ठा vmw_dअगरf_cpy used to track the modअगरied bounding box.
 * @dest: The copy destination.
 * @src: The copy source.
 * @n: Number of bytes to copy.
 *
 * In order to correctly track the modअगरied content, the field @dअगरf->line must
 * be pre-loaded with the current line number, the field @dअगरf->line_offset must
 * be pre-loaded with the line offset in bytes where the copy starts, and
 * finally the field @dअगरf->cpp need to be preloaded with the number of bytes
 * per unit in the horizontal direction of the area we're examining.
 * Typically bytes per pixel.
 * This is needed to know the needed granularity of the dअगरference computing
 * operations. A higher cpp generally leads to faster execution at the cost of
 * bounding box width precision.
 */
व्योम vmw_dअगरf_स_नकल(काष्ठा vmw_dअगरf_cpy *dअगरf, u8 *dest, स्थिर u8 *src,
		     माप_प्रकार n)
अणु
	sमाप_प्रकार csize, byte_len;

	अगर (WARN_ON_ONCE(round_करोwn(n, dअगरf->cpp) != n))
		वापस;

	/* TODO: Possibly use a single vmw_find_first_dअगरf per line? */
	csize = vmw_find_first_dअगरf(dest, src, n, dअगरf->cpp);
	अगर (csize < n) अणु
		vmw_adjust_rect(dअगरf, csize);
		byte_len = dअगरf->cpp;

		/*
		 * Starting from where first dअगरference was found, find
		 * location of last dअगरference, and then copy.
		 */
		dअगरf->line_offset += csize;
		dest += csize;
		src += csize;
		n -= csize;
		csize = vmw_find_last_dअगरf(dest, src, n, dअगरf->cpp);
		अगर (csize >= 0) अणु
			byte_len += csize;
			vmw_adjust_rect(dअगरf, csize);
		पूर्ण
		स_नकल(dest, src, byte_len);
	पूर्ण
	dअगरf->line_offset += n;
पूर्ण

/**
 * काष्ठा vmw_bo_blit_line_data - Convenience argument to vmw_bo_cpu_blit_line
 *
 * @mapped_dst: Alपढ़ोy mapped destination page index in @dst_pages.
 * @dst_addr: Kernel भव address of mapped destination page.
 * @dst_pages: Array of destination bo pages.
 * @dst_num_pages: Number of destination bo pages.
 * @dst_prot: Destination bo page protection.
 * @mapped_src: Alपढ़ोy mapped source page index in @dst_pages.
 * @src_addr: Kernel भव address of mapped source page.
 * @src_pages: Array of source bo pages.
 * @src_num_pages: Number of source bo pages.
 * @src_prot: Source bo page protection.
 * @dअगरf: Struct vmw_dअगरf_cpy, in the end क्रमwarded to the स_नकल routine.
 */
काष्ठा vmw_bo_blit_line_data अणु
	u32 mapped_dst;
	u8 *dst_addr;
	काष्ठा page **dst_pages;
	u32 dst_num_pages;
	pgprot_t dst_prot;
	u32 mapped_src;
	u8 *src_addr;
	काष्ठा page **src_pages;
	u32 src_num_pages;
	pgprot_t src_prot;
	काष्ठा vmw_dअगरf_cpy *dअगरf;
पूर्ण;

/**
 * vmw_bo_cpu_blit_line - Blit part of a line from one bo to another.
 *
 * @d: Blit data as described above.
 * @dst_offset: Destination copy start offset from start of bo.
 * @src_offset: Source copy start offset from start of bo.
 * @bytes_to_copy: Number of bytes to copy in this line.
 */
अटल पूर्णांक vmw_bo_cpu_blit_line(काष्ठा vmw_bo_blit_line_data *d,
				u32 dst_offset,
				u32 src_offset,
				u32 bytes_to_copy)
अणु
	काष्ठा vmw_dअगरf_cpy *dअगरf = d->dअगरf;

	जबतक (bytes_to_copy) अणु
		u32 copy_size = bytes_to_copy;
		u32 dst_page = dst_offset >> PAGE_SHIFT;
		u32 src_page = src_offset >> PAGE_SHIFT;
		u32 dst_page_offset = dst_offset & ~PAGE_MASK;
		u32 src_page_offset = src_offset & ~PAGE_MASK;
		bool unmap_dst = d->dst_addr && dst_page != d->mapped_dst;
		bool unmap_src = d->src_addr && (src_page != d->mapped_src ||
						 unmap_dst);

		copy_size = min_t(u32, copy_size, PAGE_SIZE - dst_page_offset);
		copy_size = min_t(u32, copy_size, PAGE_SIZE - src_page_offset);

		अगर (unmap_src) अणु
			kunmap_atomic(d->src_addr);
			d->src_addr = शून्य;
		पूर्ण

		अगर (unmap_dst) अणु
			kunmap_atomic(d->dst_addr);
			d->dst_addr = शून्य;
		पूर्ण

		अगर (!d->dst_addr) अणु
			अगर (WARN_ON_ONCE(dst_page >= d->dst_num_pages))
				वापस -EINVAL;

			d->dst_addr =
				kmap_atomic_prot(d->dst_pages[dst_page],
						 d->dst_prot);
			अगर (!d->dst_addr)
				वापस -ENOMEM;

			d->mapped_dst = dst_page;
		पूर्ण

		अगर (!d->src_addr) अणु
			अगर (WARN_ON_ONCE(src_page >= d->src_num_pages))
				वापस -EINVAL;

			d->src_addr =
				kmap_atomic_prot(d->src_pages[src_page],
						 d->src_prot);
			अगर (!d->src_addr)
				वापस -ENOMEM;

			d->mapped_src = src_page;
		पूर्ण
		dअगरf->करो_cpy(dअगरf, d->dst_addr + dst_page_offset,
			     d->src_addr + src_page_offset, copy_size);

		bytes_to_copy -= copy_size;
		dst_offset += copy_size;
		src_offset += copy_size;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * tपंचांग_bo_cpu_blit - in-kernel cpu blit.
 *
 * @dst: Destination buffer object.
 * @dst_offset: Destination offset of blit start in bytes.
 * @dst_stride: Destination stride in bytes.
 * @src: Source buffer object.
 * @src_offset: Source offset of blit start in bytes.
 * @src_stride: Source stride in bytes.
 * @w: Width of blit.
 * @h: Height of blit.
 * @dअगरf: The काष्ठा vmw_dअगरf_cpy used to track the modअगरied bounding box.
 * वापस: Zero on success. Negative error value on failure. Will prपूर्णांक out
 * kernel warnings on caller bugs.
 *
 * Perक्रमms a CPU blit from one buffer object to another aव्योमing a full
 * bo vmap which may exhaust- or fragment vदो_स्मृति space.
 * On supported architectures (x86), we're using kmap_atomic which aव्योमs
 * cross-processor TLB- and cache flushes and may, on non-HIGHMEM प्रणालीs
 * reference alपढ़ोy set-up mappings.
 *
 * Neither of the buffer objects may be placed in PCI memory
 * (Fixed memory in TTM terminology) when using this function.
 */
पूर्णांक vmw_bo_cpu_blit(काष्ठा tपंचांग_buffer_object *dst,
		    u32 dst_offset, u32 dst_stride,
		    काष्ठा tपंचांग_buffer_object *src,
		    u32 src_offset, u32 src_stride,
		    u32 w, u32 h,
		    काष्ठा vmw_dअगरf_cpy *dअगरf)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = false,
		.no_रुको_gpu = false
	पूर्ण;
	u32 j, initial_line = dst_offset / dst_stride;
	काष्ठा vmw_bo_blit_line_data d;
	पूर्णांक ret = 0;

	/* Buffer objects need to be either pinned or reserved: */
	अगर (!(dst->pin_count))
		dma_resv_निश्चित_held(dst->base.resv);
	अगर (!(src->pin_count))
		dma_resv_निश्चित_held(src->base.resv);

	अगर (!tपंचांग_tt_is_populated(dst->tपंचांग)) अणु
		ret = dst->bdev->funcs->tपंचांग_tt_populate(dst->bdev, dst->tपंचांग, &ctx);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!tपंचांग_tt_is_populated(src->tपंचांग)) अणु
		ret = src->bdev->funcs->tपंचांग_tt_populate(src->bdev, src->tपंचांग, &ctx);
		अगर (ret)
			वापस ret;
	पूर्ण

	d.mapped_dst = 0;
	d.mapped_src = 0;
	d.dst_addr = शून्य;
	d.src_addr = शून्य;
	d.dst_pages = dst->tपंचांग->pages;
	d.src_pages = src->tपंचांग->pages;
	d.dst_num_pages = dst->mem.num_pages;
	d.src_num_pages = src->mem.num_pages;
	d.dst_prot = tपंचांग_io_prot(dst, &dst->mem, PAGE_KERNEL);
	d.src_prot = tपंचांग_io_prot(src, &src->mem, PAGE_KERNEL);
	d.dअगरf = dअगरf;

	क्रम (j = 0; j < h; ++j) अणु
		dअगरf->line = j + initial_line;
		dअगरf->line_offset = dst_offset % dst_stride;
		ret = vmw_bo_cpu_blit_line(&d, dst_offset, src_offset, w);
		अगर (ret)
			जाओ out;

		dst_offset += dst_stride;
		src_offset += src_stride;
	पूर्ण
out:
	अगर (d.src_addr)
		kunmap_atomic(d.src_addr);
	अगर (d.dst_addr)
		kunmap_atomic(d.dst_addr);

	वापस ret;
पूर्ण
