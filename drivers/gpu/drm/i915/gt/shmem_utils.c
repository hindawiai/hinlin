<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/shmem_fs.h>

#समावेश "gem/i915_gem_object.h"
#समावेश "shmem_utils.h"

काष्ठा file *shmem_create_from_data(स्थिर अक्षर *name, व्योम *data, माप_प्रकार len)
अणु
	काष्ठा file *file;
	पूर्णांक err;

	file = shmem_file_setup(name, PAGE_ALIGN(len), VM_NORESERVE);
	अगर (IS_ERR(file))
		वापस file;

	err = shmem_ग_लिखो(file, 0, data, len);
	अगर (err) अणु
		fput(file);
		वापस ERR_PTR(err);
	पूर्ण

	वापस file;
पूर्ण

काष्ठा file *shmem_create_from_object(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा file *file;
	व्योम *ptr;

	अगर (i915_gem_object_is_shmem(obj)) अणु
		file = obj->base.filp;
		atomic_दीर्घ_inc(&file->f_count);
		वापस file;
	पूर्ण

	ptr = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WB);
	अगर (IS_ERR(ptr))
		वापस ERR_CAST(ptr);

	file = shmem_create_from_data("", ptr, obj->base.size);
	i915_gem_object_unpin_map(obj);

	वापस file;
पूर्ण

व्योम *shmem_pin_map(काष्ठा file *file)
अणु
	काष्ठा page **pages;
	माप_प्रकार n_pages, i;
	व्योम *vaddr;

	n_pages = file->f_mapping->host->i_size >> PAGE_SHIFT;
	pages = kvदो_स्मृति_array(n_pages, माप(*pages), GFP_KERNEL);
	अगर (!pages)
		वापस शून्य;

	क्रम (i = 0; i < n_pages; i++) अणु
		pages[i] = shmem_पढ़ो_mapping_page_gfp(file->f_mapping, i,
						       GFP_KERNEL);
		अगर (IS_ERR(pages[i]))
			जाओ err_page;
	पूर्ण

	vaddr = vmap(pages, n_pages, VM_MAP_PUT_PAGES, PAGE_KERNEL);
	अगर (!vaddr)
		जाओ err_page;
	mapping_set_unevictable(file->f_mapping);
	वापस vaddr;
err_page:
	जबतक (i--)
		put_page(pages[i]);
	kvमुक्त(pages);
	वापस शून्य;
पूर्ण

व्योम shmem_unpin_map(काष्ठा file *file, व्योम *ptr)
अणु
	mapping_clear_unevictable(file->f_mapping);
	vमुक्त(ptr);
पूर्ण

अटल पूर्णांक __shmem_rw(काष्ठा file *file, loff_t off,
		      व्योम *ptr, माप_प्रकार len,
		      bool ग_लिखो)
अणु
	अचिन्हित दीर्घ pfn;

	क्रम (pfn = off >> PAGE_SHIFT; len; pfn++) अणु
		अचिन्हित पूर्णांक this =
			min_t(माप_प्रकार, PAGE_SIZE - offset_in_page(off), len);
		काष्ठा page *page;
		व्योम *vaddr;

		page = shmem_पढ़ो_mapping_page_gfp(file->f_mapping, pfn,
						   GFP_KERNEL);
		अगर (IS_ERR(page))
			वापस PTR_ERR(page);

		vaddr = kmap(page);
		अगर (ग_लिखो) अणु
			स_नकल(vaddr + offset_in_page(off), ptr, this);
			set_page_dirty(page);
		पूर्ण अन्यथा अणु
			स_नकल(ptr, vaddr + offset_in_page(off), this);
		पूर्ण
		mark_page_accessed(page);
		kunmap(page);
		put_page(page);

		len -= this;
		ptr += this;
		off = 0;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक shmem_पढ़ो(काष्ठा file *file, loff_t off, व्योम *dst, माप_प्रकार len)
अणु
	वापस __shmem_rw(file, off, dst, len, false);
पूर्ण

पूर्णांक shmem_ग_लिखो(काष्ठा file *file, loff_t off, व्योम *src, माप_प्रकार len)
अणु
	वापस __shmem_rw(file, off, src, len, true);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "st_shmem_utils.c"
#पूर्ण_अगर
