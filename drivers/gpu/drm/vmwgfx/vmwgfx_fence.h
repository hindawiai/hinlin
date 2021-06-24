<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**************************************************************************
 *
 * Copyright 2011-2012 VMware, Inc., Palo Alto, CA., USA
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

#अगर_अघोषित _VMWGFX_FENCE_H_

#समावेश <linux/dma-fence.h>
#समावेश <linux/dma-fence-array.h>

#घोषणा VMW_FENCE_WAIT_TIMEOUT (5*HZ)

काष्ठा drm_device;
काष्ठा drm_file;
काष्ठा drm_pending_event;

काष्ठा vmw_निजी;
काष्ठा vmw_fence_manager;

/**
 *
 *
 */
क्रमागत vmw_action_type अणु
	VMW_ACTION_EVENT = 0,
	VMW_ACTION_MAX
पूर्ण;

काष्ठा vmw_fence_action अणु
	काष्ठा list_head head;
	क्रमागत vmw_action_type type;
	व्योम (*seq_passed) (काष्ठा vmw_fence_action *action);
	व्योम (*cleanup) (काष्ठा vmw_fence_action *action);
पूर्ण;

काष्ठा vmw_fence_obj अणु
	काष्ठा dma_fence base;

	काष्ठा list_head head;
	काष्ठा list_head seq_passed_actions;
	व्योम (*destroy)(काष्ठा vmw_fence_obj *fence);
पूर्ण;

बाह्य काष्ठा vmw_fence_manager *
vmw_fence_manager_init(काष्ठा vmw_निजी *dev_priv);

बाह्य व्योम vmw_fence_manager_takeकरोwn(काष्ठा vmw_fence_manager *fman);

अटल अंतरभूत व्योम
vmw_fence_obj_unreference(काष्ठा vmw_fence_obj **fence_p)
अणु
	काष्ठा vmw_fence_obj *fence = *fence_p;

	*fence_p = शून्य;
	अगर (fence)
		dma_fence_put(&fence->base);
पूर्ण

अटल अंतरभूत काष्ठा vmw_fence_obj *
vmw_fence_obj_reference(काष्ठा vmw_fence_obj *fence)
अणु
	अगर (fence)
		dma_fence_get(&fence->base);
	वापस fence;
पूर्ण

बाह्य व्योम vmw_fences_update(काष्ठा vmw_fence_manager *fman);

बाह्य bool vmw_fence_obj_संकेतed(काष्ठा vmw_fence_obj *fence);

बाह्य पूर्णांक vmw_fence_obj_रुको(काष्ठा vmw_fence_obj *fence,
			      bool lazy,
			      bool पूर्णांकerruptible, अचिन्हित दीर्घ समयout);

बाह्य व्योम vmw_fence_obj_flush(काष्ठा vmw_fence_obj *fence);

बाह्य पूर्णांक vmw_fence_create(काष्ठा vmw_fence_manager *fman,
			    uपूर्णांक32_t seqno,
			    काष्ठा vmw_fence_obj **p_fence);

बाह्य पूर्णांक vmw_user_fence_create(काष्ठा drm_file *file_priv,
				 काष्ठा vmw_fence_manager *fman,
				 uपूर्णांक32_t sequence,
				 काष्ठा vmw_fence_obj **p_fence,
				 uपूर्णांक32_t *p_handle);

बाह्य पूर्णांक vmw_रुको_dma_fence(काष्ठा vmw_fence_manager *fman,
			      काष्ठा dma_fence *fence);

बाह्य व्योम vmw_fence_fअगरo_up(काष्ठा vmw_fence_manager *fman);

बाह्य व्योम vmw_fence_fअगरo_करोwn(काष्ठा vmw_fence_manager *fman);

बाह्य पूर्णांक vmw_fence_obj_रुको_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file_priv);

बाह्य पूर्णांक vmw_fence_obj_संकेतed_ioctl(काष्ठा drm_device *dev, व्योम *data,
					काष्ठा drm_file *file_priv);

बाह्य पूर्णांक vmw_fence_obj_unref_ioctl(काष्ठा drm_device *dev, व्योम *data,
				     काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_fence_event_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_event_fence_action_queue(काष्ठा drm_file *filee_priv,
					काष्ठा vmw_fence_obj *fence,
					काष्ठा drm_pending_event *event,
					uपूर्णांक32_t *tv_sec,
					uपूर्णांक32_t *tv_usec,
					bool पूर्णांकerruptible);
#पूर्ण_अगर /* _VMWGFX_FENCE_H_ */
