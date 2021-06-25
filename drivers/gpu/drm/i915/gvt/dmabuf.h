<शैली गुरु>
/*
 * Copyright(c) 2017 Intel Corporation. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Zhiyuan Lv <zhiyuan.lv@पूर्णांकel.com>
 *
 * Contributors:
 *    Xiaoguang Chen
 *    Tina Zhang <tina.zhang@पूर्णांकel.com>
 */

#अगर_अघोषित _GVT_DMABUF_H_
#घोषणा _GVT_DMABUF_H_
#समावेश <linux/vfपन.स>

काष्ठा पूर्णांकel_vgpu_fb_info अणु
	__u64 start;
	__u64 start_gpa;
	__u64 drm_क्रमmat_mod;
	__u32 drm_क्रमmat;	/* drm क्रमmat of plane */
	__u32 width;	/* width of plane */
	__u32 height;	/* height of plane */
	__u32 stride;	/* stride of plane */
	__u32 size;	/* size of plane in bytes, align on page */
	__u32 x_pos;	/* horizontal position of cursor plane */
	__u32 y_pos;	/* vertical position of cursor plane */
	__u32 x_hot;    /* horizontal position of cursor hotspot */
	__u32 y_hot;    /* vertical position of cursor hotspot */
	काष्ठा पूर्णांकel_vgpu_dmabuf_obj *obj;
पूर्ण;

/**
 * काष्ठा पूर्णांकel_vgpu_dmabuf_obj- Intel vGPU device buffer object
 */
काष्ठा पूर्णांकel_vgpu_dmabuf_obj अणु
	काष्ठा पूर्णांकel_vgpu *vgpu;
	काष्ठा पूर्णांकel_vgpu_fb_info *info;
	__u32 dmabuf_id;
	काष्ठा kref kref;
	bool initref;
	काष्ठा list_head list;
पूर्ण;

पूर्णांक पूर्णांकel_vgpu_query_plane(काष्ठा पूर्णांकel_vgpu *vgpu, व्योम *args);
पूर्णांक पूर्णांकel_vgpu_get_dmabuf(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक dmabuf_id);
व्योम पूर्णांकel_vgpu_dmabuf_cleanup(काष्ठा पूर्णांकel_vgpu *vgpu);

#पूर्ण_अगर
