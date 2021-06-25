<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <drm/drm_file.h>

#समावेश "i915_drv.h"
#समावेश "igt_mmap.h"

अचिन्हित दीर्घ igt_mmap_node(काष्ठा drm_i915_निजी *i915,
			    काष्ठा drm_vma_offset_node *node,
			    अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ prot,
			    अचिन्हित दीर्घ flags)
अणु
	काष्ठा file *file;
	पूर्णांक err;

	/* Pretend to खोलो("/dev/dri/card0") */
	file = mock_drm_getfile(i915->drm.primary, O_RDWR);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	err = drm_vma_node_allow(node, file->निजी_data);
	अगर (err) अणु
		addr = err;
		जाओ out_file;
	पूर्ण

	addr = vm_mmap(file, addr, drm_vma_node_size(node) << PAGE_SHIFT,
		       prot, flags, drm_vma_node_offset_addr(node));

	drm_vma_node_revoke(node, file->निजी_data);
out_file:
	fput(file);
	वापस addr;
पूर्ण
