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
 *    Ke Yu
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *    Dexuan Cui
 *
 * Contributors:
 *    Tina Zhang <tina.zhang@पूर्णांकel.com>
 *    Min He <min.he@पूर्णांकel.com>
 *    Niu Bing <bing.niu@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 */

#अगर_अघोषित _GVT_MMIO_H_
#घोषणा _GVT_MMIO_H_

#समावेश <linux/types.h>

काष्ठा पूर्णांकel_gvt;
काष्ठा पूर्णांकel_vgpu;

#घोषणा D_BDW   (1 << 0)
#घोषणा D_SKL	(1 << 1)
#घोषणा D_KBL	(1 << 2)
#घोषणा D_BXT	(1 << 3)
#घोषणा D_CFL	(1 << 4)

#घोषणा D_GEN9PLUS	(D_SKL | D_KBL | D_BXT | D_CFL)
#घोषणा D_GEN8PLUS	(D_BDW | D_SKL | D_KBL | D_BXT | D_CFL)

#घोषणा D_SKL_PLUS	(D_SKL | D_KBL | D_BXT | D_CFL)
#घोषणा D_BDW_PLUS	(D_BDW | D_SKL | D_KBL | D_BXT | D_CFL)

#घोषणा D_PRE_SKL	(D_BDW)
#घोषणा D_ALL		(D_BDW | D_SKL | D_KBL | D_BXT | D_CFL)

प्रकार पूर्णांक (*gvt_mmio_func)(काष्ठा पूर्णांकel_vgpu *, अचिन्हित पूर्णांक, व्योम *,
			     अचिन्हित पूर्णांक);

काष्ठा पूर्णांकel_gvt_mmio_info अणु
	u32 offset;
	u64 ro_mask;
	u32 device;
	gvt_mmio_func पढ़ो;
	gvt_mmio_func ग_लिखो;
	u32 addr_range;
	काष्ठा hlist_node node;
पूर्ण;

स्थिर काष्ठा पूर्णांकel_engine_cs *
पूर्णांकel_gvt_render_mmio_to_engine(काष्ठा पूर्णांकel_gvt *gvt, अचिन्हित पूर्णांक reg);
अचिन्हित दीर्घ पूर्णांकel_gvt_get_device_type(काष्ठा पूर्णांकel_gvt *gvt);
bool पूर्णांकel_gvt_match_device(काष्ठा पूर्णांकel_gvt *gvt, अचिन्हित दीर्घ device);

पूर्णांक पूर्णांकel_gvt_setup_mmio_info(काष्ठा पूर्णांकel_gvt *gvt);
व्योम पूर्णांकel_gvt_clean_mmio_info(काष्ठा पूर्णांकel_gvt *gvt);
पूर्णांक पूर्णांकel_gvt_क्रम_each_tracked_mmio(काष्ठा पूर्णांकel_gvt *gvt,
	पूर्णांक (*handler)(काष्ठा पूर्णांकel_gvt *gvt, u32 offset, व्योम *data),
	व्योम *data);

काष्ठा पूर्णांकel_gvt_mmio_info *पूर्णांकel_gvt_find_mmio_info(काष्ठा पूर्णांकel_gvt *gvt,
						  अचिन्हित पूर्णांक offset);

पूर्णांक पूर्णांकel_vgpu_init_mmio(काष्ठा पूर्णांकel_vgpu *vgpu);
व्योम पूर्णांकel_vgpu_reset_mmio(काष्ठा पूर्णांकel_vgpu *vgpu, bool dmlr);
व्योम पूर्णांकel_vgpu_clean_mmio(काष्ठा पूर्णांकel_vgpu *vgpu);

पूर्णांक पूर्णांकel_vgpu_gpa_to_mmio_offset(काष्ठा पूर्णांकel_vgpu *vgpu, u64 gpa);

पूर्णांक पूर्णांकel_vgpu_emulate_mmio_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, u64 pa,
				व्योम *p_data, अचिन्हित पूर्णांक bytes);
पूर्णांक पूर्णांकel_vgpu_emulate_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, u64 pa,
				व्योम *p_data, अचिन्हित पूर्णांक bytes);

पूर्णांक पूर्णांकel_vgpu_शेष_mmio_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
				 व्योम *p_data, अचिन्हित पूर्णांक bytes);
पूर्णांक पूर्णांकel_vgpu_शेष_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
				  व्योम *p_data, अचिन्हित पूर्णांक bytes);

bool पूर्णांकel_gvt_in_क्रमce_nonpriv_whitelist(काष्ठा पूर्णांकel_gvt *gvt,
					  अचिन्हित पूर्णांक offset);

पूर्णांक पूर्णांकel_vgpu_mmio_reg_rw(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
			   व्योम *pdata, अचिन्हित पूर्णांक bytes, bool is_पढ़ो);

पूर्णांक पूर्णांकel_vgpu_mask_mmio_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
				  व्योम *p_data, अचिन्हित पूर्णांक bytes);

व्योम पूर्णांकel_gvt_restore_fence(काष्ठा पूर्णांकel_gvt *gvt);
व्योम पूर्णांकel_gvt_restore_mmio(काष्ठा पूर्णांकel_gvt *gvt);

#पूर्ण_अगर
