<शैली गुरु>
/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
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
 *    Eddie Dong <eddie.करोng@पूर्णांकel.com>
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *
 * Contributors:
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *    Changbin Du <changbin.du@पूर्णांकel.com>
 *    Zhenyu Wang <zhenyuw@linux.पूर्णांकel.com>
 *    Tina Zhang <tina.zhang@पूर्णांकel.com>
 *    Bing Niu <bing.niu@पूर्णांकel.com>
 *
 */

#अगर_अघोषित __GVT_RENDER_H__
#घोषणा __GVT_RENDER_H__

#समावेश <linux/types.h>

#समावेश "gt/intel_engine_types.h"
#समावेश "gt/intel_lrc_reg.h"
#समावेश "i915_reg.h"

काष्ठा i915_request;
काष्ठा पूर्णांकel_context;
काष्ठा पूर्णांकel_engine_cs;
काष्ठा पूर्णांकel_gvt;
काष्ठा पूर्णांकel_vgpu;

काष्ठा engine_mmio अणु
	क्रमागत पूर्णांकel_engine_id id;
	i915_reg_t reg;
	u32 mask;
	bool in_context;
	u32 value;
पूर्ण;

व्योम पूर्णांकel_gvt_चयन_mmio(काष्ठा पूर्णांकel_vgpu *pre,
			   काष्ठा पूर्णांकel_vgpu *next,
			   स्थिर काष्ठा पूर्णांकel_engine_cs *engine);

व्योम पूर्णांकel_gvt_init_engine_mmio_context(काष्ठा पूर्णांकel_gvt *gvt);

bool is_inhibit_context(काष्ठा पूर्णांकel_context *ce);

पूर्णांक पूर्णांकel_vgpu_restore_inhibit_context(काष्ठा पूर्णांकel_vgpu *vgpu,
				       काष्ठा i915_request *req);

#घोषणा IS_RESTORE_INHIBIT(a) \
	IS_MASKED_BITS_ENABLED(a, CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT)

#पूर्ण_अगर
