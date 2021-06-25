<शैली गुरु>
/*
 * Copyright (C) 2015 Red Hat, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_file.h>

#समावेश "virtgpu_drv.h"

अटल व्योम virtio_gpu_add_bool(काष्ठा seq_file *m, स्थिर अक्षर *name,
				bool value)
अणु
	seq_म_लिखो(m, "%-16s : %s\n", name, value ? "yes" : "no");
पूर्ण

अटल व्योम virtio_gpu_add_पूर्णांक(काष्ठा seq_file *m, स्थिर अक्षर *name, पूर्णांक value)
अणु
	seq_म_लिखो(m, "%-16s : %d\n", name, value);
पूर्ण

अटल पूर्णांक virtio_gpu_features(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा virtio_gpu_device *vgdev = node->minor->dev->dev_निजी;

	virtio_gpu_add_bool(m, "virgl", vgdev->has_virgl_3d);
	virtio_gpu_add_bool(m, "edid", vgdev->has_edid);
	virtio_gpu_add_bool(m, "indirect", vgdev->has_indirect);

	virtio_gpu_add_bool(m, "resource uuid",
			    vgdev->has_resource_assign_uuid);

	virtio_gpu_add_bool(m, "blob resources", vgdev->has_resource_blob);
	virtio_gpu_add_पूर्णांक(m, "cap sets", vgdev->num_capsets);
	virtio_gpu_add_पूर्णांक(m, "scanouts", vgdev->num_scanouts);
	अगर (vgdev->host_visible_region.len) अणु
		seq_म_लिखो(m, "%-16s : 0x%lx +0x%lx\n", "host visible region",
			   (अचिन्हित दीर्घ)vgdev->host_visible_region.addr,
			   (अचिन्हित दीर्घ)vgdev->host_visible_region.len);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
virtio_gpu_debugfs_irq_info(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा virtio_gpu_device *vgdev = node->minor->dev->dev_निजी;

	seq_म_लिखो(m, "fence %llu %lld\n",
		   (u64)atomic64_पढ़ो(&vgdev->fence_drv.last_fence_id),
		   vgdev->fence_drv.current_fence_id);
	वापस 0;
पूर्ण

अटल पूर्णांक
virtio_gpu_debugfs_host_visible_mm(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा virtio_gpu_device *vgdev = node->minor->dev->dev_निजी;
	काष्ठा drm_prपूर्णांकer p;

	अगर (!vgdev->has_host_visible) अणु
		seq_माला_दो(m, "Host allocations not visible to guest\n");
		वापस 0;
	पूर्ण

	p = drm_seq_file_prपूर्णांकer(m);
	drm_mm_prपूर्णांक(&vgdev->host_visible_mm, &p);
	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list virtio_gpu_debugfs_list[] = अणु
	अणु "virtio-gpu-features", virtio_gpu_features पूर्ण,
	अणु "virtio-gpu-irq-fence", virtio_gpu_debugfs_irq_info, 0, शून्य पूर्ण,
	अणु "virtio-gpu-host-visible-mm", virtio_gpu_debugfs_host_visible_mm पूर्ण,
पूर्ण;

#घोषणा VIRTIO_GPU_DEBUGFS_ENTRIES ARRAY_SIZE(virtio_gpu_debugfs_list)

व्योम
virtio_gpu_debugfs_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(virtio_gpu_debugfs_list,
				 VIRTIO_GPU_DEBUGFS_ENTRIES,
				 minor->debugfs_root, minor);
पूर्ण
