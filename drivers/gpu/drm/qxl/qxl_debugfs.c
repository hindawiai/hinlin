<शैली गुरु>
/*
 * Copyright (C) 2009 Red Hat <bskeggs@redhat.com>
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
 *
 */

/*
 * Authors:
 *  Alon Levy <alevy@redhat.com>
 */

#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_file.h>

#समावेश "qxl_drv.h"
#समावेश "qxl_object.h"

#अगर defined(CONFIG_DEBUG_FS)
अटल पूर्णांक
qxl_debugfs_irq_received(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा qxl_device *qdev = to_qxl(node->minor->dev);

	seq_म_लिखो(m, "%d\n", atomic_पढ़ो(&qdev->irq_received));
	seq_म_लिखो(m, "%d\n", atomic_पढ़ो(&qdev->irq_received_display));
	seq_म_लिखो(m, "%d\n", atomic_पढ़ो(&qdev->irq_received_cursor));
	seq_म_लिखो(m, "%d\n", atomic_पढ़ो(&qdev->irq_received_io_cmd));
	seq_म_लिखो(m, "%d\n", qdev->irq_received_error);
	वापस 0;
पूर्ण

अटल पूर्णांक
qxl_debugfs_buffers_info(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा qxl_device *qdev = to_qxl(node->minor->dev);
	काष्ठा qxl_bo *bo;

	list_क्रम_each_entry(bo, &qdev->gem.objects, list) अणु
		काष्ठा dma_resv_list *fobj;
		पूर्णांक rel;

		rcu_पढ़ो_lock();
		fobj = rcu_dereference(bo->tbo.base.resv->fence);
		rel = fobj ? fobj->shared_count : 0;
		rcu_पढ़ो_unlock();

		seq_म_लिखो(m, "size %ld, pc %d, num releases %d\n",
			   (अचिन्हित दीर्घ)bo->tbo.base.size,
			   bo->tbo.pin_count, rel);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list qxl_debugfs_list[] = अणु
	अणु "irq_received", qxl_debugfs_irq_received, 0, शून्य पूर्ण,
	अणु "qxl_buffers", qxl_debugfs_buffers_info, 0, शून्य पूर्ण,
पूर्ण;
#घोषणा QXL_DEBUGFS_ENTRIES ARRAY_SIZE(qxl_debugfs_list)
#पूर्ण_अगर

व्योम
qxl_debugfs_init(काष्ठा drm_minor *minor)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा qxl_device *dev = to_qxl(minor->dev);

	drm_debugfs_create_files(qxl_debugfs_list, QXL_DEBUGFS_ENTRIES,
				 minor->debugfs_root, minor);

	qxl_tपंचांग_debugfs_init(dev);
#पूर्ण_अगर
पूर्ण

व्योम qxl_debugfs_add_files(काष्ठा qxl_device *qdev,
			   काष्ठा drm_info_list *files,
			   अचिन्हित पूर्णांक nfiles)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < qdev->debugfs_count; i++) अणु
		अगर (qdev->debugfs[i].files == files) अणु
			/* Alपढ़ोy रेजिस्टरed */
			वापस;
		पूर्ण
	पूर्ण

	i = qdev->debugfs_count + 1;
	अगर (i > QXL_DEBUGFS_MAX_COMPONENTS) अणु
		DRM_ERROR("Reached maximum number of debugfs components.\n");
		DRM_ERROR("Report so we increase QXL_DEBUGFS_MAX_COMPONENTS.\n");
		वापस;
	पूर्ण
	qdev->debugfs[qdev->debugfs_count].files = files;
	qdev->debugfs[qdev->debugfs_count].num_files = nfiles;
	qdev->debugfs_count = i;
#अगर defined(CONFIG_DEBUG_FS)
	drm_debugfs_create_files(files, nfiles,
				 qdev->ddev.primary->debugfs_root,
				 qdev->ddev.primary);
#पूर्ण_अगर
पूर्ण
