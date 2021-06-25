<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alon Levy
 */

#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>

#समावेश "qxl_drv.h"
#समावेश "qxl_object.h"

अटल पूर्णांक
qxl_allocate_chunk(काष्ठा qxl_device *qdev,
		   काष्ठा qxl_release *release,
		   काष्ठा qxl_drm_image *image,
		   अचिन्हित पूर्णांक chunk_size)
अणु
	काष्ठा qxl_drm_chunk *chunk;
	पूर्णांक ret;

	chunk = kदो_स्मृति(माप(काष्ठा qxl_drm_chunk), GFP_KERNEL);
	अगर (!chunk)
		वापस -ENOMEM;

	ret = qxl_alloc_bo_reserved(qdev, release, chunk_size, &chunk->bo);
	अगर (ret) अणु
		kमुक्त(chunk);
		वापस ret;
	पूर्ण

	list_add_tail(&chunk->head, &image->chunk_list);
	वापस 0;
पूर्ण

पूर्णांक
qxl_image_alloc_objects(काष्ठा qxl_device *qdev,
			काष्ठा qxl_release *release,
			काष्ठा qxl_drm_image **image_ptr,
			पूर्णांक height, पूर्णांक stride)
अणु
	काष्ठा qxl_drm_image *image;
	पूर्णांक ret;

	image = kदो_स्मृति(माप(काष्ठा qxl_drm_image), GFP_KERNEL);
	अगर (!image)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&image->chunk_list);

	ret = qxl_alloc_bo_reserved(qdev, release, माप(काष्ठा qxl_image), &image->bo);
	अगर (ret) अणु
		kमुक्त(image);
		वापस ret;
	पूर्ण

	ret = qxl_allocate_chunk(qdev, release, image, माप(काष्ठा qxl_data_chunk) + stride * height);
	अगर (ret) अणु
		qxl_bo_unref(&image->bo);
		kमुक्त(image);
		वापस ret;
	पूर्ण
	*image_ptr = image;
	वापस 0;
पूर्ण

व्योम qxl_image_मुक्त_objects(काष्ठा qxl_device *qdev, काष्ठा qxl_drm_image *dimage)
अणु
	काष्ठा qxl_drm_chunk *chunk, *पंचांगp;

	list_क्रम_each_entry_safe(chunk, पंचांगp, &dimage->chunk_list, head) अणु
		qxl_bo_unref(&chunk->bo);
		kमुक्त(chunk);
	पूर्ण

	qxl_bo_unref(&dimage->bo);
	kमुक्त(dimage);
पूर्ण

अटल पूर्णांक
qxl_image_init_helper(काष्ठा qxl_device *qdev,
		      काष्ठा qxl_release *release,
		      काष्ठा qxl_drm_image *dimage,
		      स्थिर uपूर्णांक8_t *data,
		      पूर्णांक width, पूर्णांक height,
		      पूर्णांक depth, अचिन्हित पूर्णांक hash,
		      पूर्णांक stride)
अणु
	काष्ठा qxl_drm_chunk *drv_chunk;
	काष्ठा qxl_image *image;
	काष्ठा qxl_data_chunk *chunk;
	पूर्णांक i;
	पूर्णांक chunk_stride;
	पूर्णांक linesize = width * depth / 8;
	काष्ठा qxl_bo *chunk_bo, *image_bo;
	व्योम *ptr;
	/* Chunk */
	/* FIXME: Check पूर्णांकeger overflow */
	/* TODO: variable number of chunks */

	drv_chunk = list_first_entry(&dimage->chunk_list, काष्ठा qxl_drm_chunk, head);

	chunk_bo = drv_chunk->bo;
	chunk_stride = stride; /* TODO: should use linesize, but it renders
				  wrong (check the biपंचांगaps are sent correctly
				  first) */

	ptr = qxl_bo_kmap_atomic_page(qdev, chunk_bo, 0);
	chunk = ptr;
	chunk->data_size = height * chunk_stride;
	chunk->prev_chunk = 0;
	chunk->next_chunk = 0;
	qxl_bo_kunmap_atomic_page(qdev, chunk_bo, ptr);

	अणु
		व्योम *k_data, *i_data;
		पूर्णांक reमुख्य;
		पूर्णांक page;
		पूर्णांक size;

		अगर (stride == linesize && chunk_stride == stride) अणु
			reमुख्य = linesize * height;
			page = 0;
			i_data = (व्योम *)data;

			जबतक (reमुख्य > 0) अणु
				ptr = qxl_bo_kmap_atomic_page(qdev, chunk_bo, page << PAGE_SHIFT);

				अगर (page == 0) अणु
					chunk = ptr;
					k_data = chunk->data;
					size = PAGE_SIZE - दुरत्व(काष्ठा qxl_data_chunk, data);
				पूर्ण अन्यथा अणु
					k_data = ptr;
					size = PAGE_SIZE;
				पूर्ण
				size = min(size, reमुख्य);

				स_नकल(k_data, i_data, size);

				qxl_bo_kunmap_atomic_page(qdev, chunk_bo, ptr);
				i_data += size;
				reमुख्य -= size;
				page++;
			पूर्ण
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक page_base, page_offset, out_offset;

			क्रम (i = 0 ; i < height ; ++i) अणु
				i_data = (व्योम *)data + i * stride;
				reमुख्य = linesize;
				out_offset = दुरत्व(काष्ठा qxl_data_chunk, data) + i * chunk_stride;

				जबतक (reमुख्य > 0) अणु
					page_base = out_offset & PAGE_MASK;
					page_offset = offset_in_page(out_offset);
					size = min((पूर्णांक)(PAGE_SIZE - page_offset), reमुख्य);

					ptr = qxl_bo_kmap_atomic_page(qdev, chunk_bo, page_base);
					k_data = ptr + page_offset;
					स_नकल(k_data, i_data, size);
					qxl_bo_kunmap_atomic_page(qdev, chunk_bo, ptr);
					reमुख्य -= size;
					i_data += size;
					out_offset += size;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	qxl_bo_vunmap_locked(chunk_bo);

	image_bo = dimage->bo;
	ptr = qxl_bo_kmap_atomic_page(qdev, image_bo, 0);
	image = ptr;

	image->descriptor.id = 0;
	image->descriptor.type = SPICE_IMAGE_TYPE_BITMAP;

	image->descriptor.flags = 0;
	image->descriptor.width = width;
	image->descriptor.height = height;

	चयन (depth) अणु
	हाल 1:
		/* TODO: BE? check by arch? */
		image->u.biपंचांगap.क्रमmat = SPICE_BITMAP_FMT_1BIT_BE;
		अवरोध;
	हाल 24:
		image->u.biपंचांगap.क्रमmat = SPICE_BITMAP_FMT_24BIT;
		अवरोध;
	हाल 32:
		image->u.biपंचांगap.क्रमmat = SPICE_BITMAP_FMT_32BIT;
		अवरोध;
	शेष:
		DRM_ERROR("unsupported image bit depth\n");
		qxl_bo_kunmap_atomic_page(qdev, image_bo, ptr);
		वापस -EINVAL;
	पूर्ण
	image->u.biपंचांगap.flags = QXL_BITMAP_TOP_DOWN;
	image->u.biपंचांगap.x = width;
	image->u.biपंचांगap.y = height;
	image->u.biपंचांगap.stride = chunk_stride;
	image->u.biपंचांगap.palette = 0;
	image->u.biपंचांगap.data = qxl_bo_physical_address(qdev, chunk_bo, 0);

	qxl_bo_kunmap_atomic_page(qdev, image_bo, ptr);

	वापस 0;
पूर्ण

पूर्णांक qxl_image_init(काष्ठा qxl_device *qdev,
		     काष्ठा qxl_release *release,
		     काष्ठा qxl_drm_image *dimage,
		     स्थिर uपूर्णांक8_t *data,
		     पूर्णांक x, पूर्णांक y, पूर्णांक width, पूर्णांक height,
		     पूर्णांक depth, पूर्णांक stride)
अणु
	data += y * stride + x * (depth / 8);
	वापस qxl_image_init_helper(qdev, release, dimage, data,
				       width, height, depth, 0, stride);
पूर्ण
