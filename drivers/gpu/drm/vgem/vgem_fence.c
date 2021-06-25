<शैली गुरु>
/*
 * Copyright 2016 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software")
 * to deal in the software without restriction, including without limitation
 * on the rights to use, copy, modअगरy, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * them Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTIBILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/dma-resv.h>

#समावेश <drm/drm_file.h>

#समावेश "vgem_drv.h"

#घोषणा VGEM_FENCE_TIMEOUT (10*HZ)

काष्ठा vgem_fence अणु
	काष्ठा dma_fence base;
	काष्ठा spinlock lock;
	काष्ठा समयr_list समयr;
पूर्ण;

अटल स्थिर अक्षर *vgem_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "vgem";
पूर्ण

अटल स्थिर अक्षर *vgem_fence_get_समयline_name(काष्ठा dma_fence *fence)
अणु
	वापस "unbound";
पूर्ण

अटल व्योम vgem_fence_release(काष्ठा dma_fence *base)
अणु
	काष्ठा vgem_fence *fence = container_of(base, typeof(*fence), base);

	del_समयr_sync(&fence->समयr);
	dma_fence_मुक्त(&fence->base);
पूर्ण

अटल व्योम vgem_fence_value_str(काष्ठा dma_fence *fence, अक्षर *str, पूर्णांक size)
अणु
	snम_लिखो(str, size, "%llu", fence->seqno);
पूर्ण

अटल व्योम vgem_fence_समयline_value_str(काष्ठा dma_fence *fence, अक्षर *str,
					  पूर्णांक size)
अणु
	snम_लिखो(str, size, "%llu",
		 dma_fence_is_संकेतed(fence) ? fence->seqno : 0);
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops vgem_fence_ops = अणु
	.get_driver_name = vgem_fence_get_driver_name,
	.get_समयline_name = vgem_fence_get_समयline_name,
	.release = vgem_fence_release,

	.fence_value_str = vgem_fence_value_str,
	.समयline_value_str = vgem_fence_समयline_value_str,
पूर्ण;

अटल व्योम vgem_fence_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा vgem_fence *fence = from_समयr(fence, t, समयr);

	dma_fence_संकेत(&fence->base);
पूर्ण

अटल काष्ठा dma_fence *vgem_fence_create(काष्ठा vgem_file *vfile,
					   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा vgem_fence *fence;

	fence = kzalloc(माप(*fence), GFP_KERNEL);
	अगर (!fence)
		वापस शून्य;

	spin_lock_init(&fence->lock);
	dma_fence_init(&fence->base, &vgem_fence_ops, &fence->lock,
		       dma_fence_context_alloc(1), 1);

	समयr_setup(&fence->समयr, vgem_fence_समयout, 0);

	/* We क्रमce the fence to expire within 10s to prevent driver hangs */
	mod_समयr(&fence->समयr, jअगरfies + VGEM_FENCE_TIMEOUT);

	वापस &fence->base;
पूर्ण

/*
 * vgem_fence_attach_ioctl (DRM_IOCTL_VGEM_FENCE_ATTACH):
 *
 * Create and attach a fence to the vGEM handle. This fence is then exposed
 * via the dma-buf reservation object and visible to consumers of the exported
 * dma-buf. If the flags contain VGEM_FENCE_WRITE, the fence indicates the
 * vGEM buffer is being written to by the client and is exposed as an exclusive
 * fence, otherwise the fence indicates the client is current पढ़ोing from the
 * buffer and all future ग_लिखोs should रुको क्रम the client to संकेत its
 * completion. Note that अगर a conflicting fence is alपढ़ोy on the dma-buf (i.e.
 * an exclusive fence when adding a पढ़ो, or any fence when adding a ग_लिखो),
 * -EBUSY is reported. Serialisation between operations should be handled
 * by रुकोing upon the dma-buf.
 *
 * This वापसs the handle क्रम the new fence that must be संकेतed within 10
 * seconds (or otherwise it will स्वतःmatically expire). See
 * vgem_fence_संकेत_ioctl (DRM_IOCTL_VGEM_FENCE_SIGNAL).
 *
 * If the vGEM handle करोes not exist, vgem_fence_attach_ioctl वापसs -ENOENT.
 */
पूर्णांक vgem_fence_attach_ioctl(काष्ठा drm_device *dev,
			    व्योम *data,
			    काष्ठा drm_file *file)
अणु
	काष्ठा drm_vgem_fence_attach *arg = data;
	काष्ठा vgem_file *vfile = file->driver_priv;
	काष्ठा dma_resv *resv;
	काष्ठा drm_gem_object *obj;
	काष्ठा dma_fence *fence;
	पूर्णांक ret;

	अगर (arg->flags & ~VGEM_FENCE_WRITE)
		वापस -EINVAL;

	अगर (arg->pad)
		वापस -EINVAL;

	obj = drm_gem_object_lookup(file, arg->handle);
	अगर (!obj)
		वापस -ENOENT;

	fence = vgem_fence_create(vfile, arg->flags);
	अगर (!fence) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/* Check क्रम a conflicting fence */
	resv = obj->resv;
	अगर (!dma_resv_test_संकेतed_rcu(resv,
						  arg->flags & VGEM_FENCE_WRITE)) अणु
		ret = -EBUSY;
		जाओ err_fence;
	पूर्ण

	/* Expose the fence via the dma-buf */
	ret = 0;
	dma_resv_lock(resv, शून्य);
	अगर (arg->flags & VGEM_FENCE_WRITE)
		dma_resv_add_excl_fence(resv, fence);
	अन्यथा अगर ((ret = dma_resv_reserve_shared(resv, 1)) == 0)
		dma_resv_add_shared_fence(resv, fence);
	dma_resv_unlock(resv);

	/* Record the fence in our idr क्रम later संकेतing */
	अगर (ret == 0) अणु
		mutex_lock(&vfile->fence_mutex);
		ret = idr_alloc(&vfile->fence_idr, fence, 1, 0, GFP_KERNEL);
		mutex_unlock(&vfile->fence_mutex);
		अगर (ret > 0) अणु
			arg->out_fence = ret;
			ret = 0;
		पूर्ण
	पूर्ण
err_fence:
	अगर (ret) अणु
		dma_fence_संकेत(fence);
		dma_fence_put(fence);
	पूर्ण
err:
	drm_gem_object_put(obj);
	वापस ret;
पूर्ण

/*
 * vgem_fence_संकेत_ioctl (DRM_IOCTL_VGEM_FENCE_SIGNAL):
 *
 * Signal and consume a fence ealier attached to a vGEM handle using
 * vgem_fence_attach_ioctl (DRM_IOCTL_VGEM_FENCE_ATTACH).
 *
 * All fences must be संकेतed within 10s of attachment or otherwise they
 * will स्वतःmatically expire (and a vgem_fence_संकेत_ioctl वापसs -ETIMEDOUT).
 *
 * Signaling a fence indicates to all consumers of the dma-buf that the
 * client has completed the operation associated with the fence, and that the
 * buffer is then पढ़ोy क्रम consumption.
 *
 * If the fence करोes not exist (or has alपढ़ोy been संकेतed by the client),
 * vgem_fence_संकेत_ioctl वापसs -ENOENT.
 */
पूर्णांक vgem_fence_संकेत_ioctl(काष्ठा drm_device *dev,
			    व्योम *data,
			    काष्ठा drm_file *file)
अणु
	काष्ठा vgem_file *vfile = file->driver_priv;
	काष्ठा drm_vgem_fence_संकेत *arg = data;
	काष्ठा dma_fence *fence;
	पूर्णांक ret = 0;

	अगर (arg->flags)
		वापस -EINVAL;

	mutex_lock(&vfile->fence_mutex);
	fence = idr_replace(&vfile->fence_idr, शून्य, arg->fence);
	mutex_unlock(&vfile->fence_mutex);
	अगर (!fence)
		वापस -ENOENT;
	अगर (IS_ERR(fence))
		वापस PTR_ERR(fence);

	अगर (dma_fence_is_संकेतed(fence))
		ret = -ETIMEDOUT;

	dma_fence_संकेत(fence);
	dma_fence_put(fence);
	वापस ret;
पूर्ण

पूर्णांक vgem_fence_खोलो(काष्ठा vgem_file *vfile)
अणु
	mutex_init(&vfile->fence_mutex);
	idr_init_base(&vfile->fence_idr, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक __vgem_fence_idr_fini(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	dma_fence_संकेत(p);
	dma_fence_put(p);
	वापस 0;
पूर्ण

व्योम vgem_fence_बंद(काष्ठा vgem_file *vfile)
अणु
	idr_क्रम_each(&vfile->fence_idr, __vgem_fence_idr_fini, vfile);
	idr_destroy(&vfile->fence_idr);
पूर्ण
