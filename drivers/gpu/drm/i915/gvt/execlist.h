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
 *    Zhiyuan Lv <zhiyuan.lv@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 * Contributors:
 *    Min He <min.he@पूर्णांकel.com>
 *    Bing Niu <bing.niu@पूर्णांकel.com>
 *    Ping Gao <ping.a.gao@पूर्णांकel.com>
 *    Tina Zhang <tina.zhang@पूर्णांकel.com>
 *
 */

#अगर_अघोषित _GVT_EXECLIST_H_
#घोषणा _GVT_EXECLIST_H_

#समावेश <linux/types.h>

काष्ठा execlist_ctx_descriptor_क्रमmat अणु
	जोड़ अणु
		u32 ldw;
		काष्ठा अणु
			u32 valid                  : 1;
			u32 क्रमce_pd_restore       : 1;
			u32 क्रमce_restore          : 1;
			u32 addressing_mode        : 2;
			u32 llc_coherency          : 1;
			u32 fault_handling         : 2;
			u32 privilege_access       : 1;
			u32 reserved               : 3;
			u32 lrca                   : 20;
		पूर्ण;
	पूर्ण;
	जोड़ अणु
		u32 udw;
		u32 context_id;
	पूर्ण;
पूर्ण;

काष्ठा execlist_status_क्रमmat अणु
	जोड़ अणु
		u32 ldw;
		काष्ठा अणु
			u32 current_execlist_poपूर्णांकer       :1;
			u32 execlist_ग_लिखो_poपूर्णांकer         :1;
			u32 execlist_queue_full            :1;
			u32 execlist_1_valid               :1;
			u32 execlist_0_valid               :1;
			u32 last_ctx_चयन_reason         :9;
			u32 current_active_elm_status      :2;
			u32 arbitration_enable             :1;
			u32 execlist_1_active              :1;
			u32 execlist_0_active              :1;
			u32 reserved                       :13;
		पूर्ण;
	पूर्ण;
	जोड़ अणु
		u32 udw;
		u32 context_id;
	पूर्ण;
पूर्ण;

काष्ठा execlist_context_status_poपूर्णांकer_क्रमmat अणु
	जोड़ अणु
		u32 dw;
		काष्ठा अणु
			u32 ग_लिखो_ptr              :3;
			u32 reserved               :5;
			u32 पढ़ो_ptr               :3;
			u32 reserved2              :5;
			u32 mask                   :16;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा execlist_context_status_क्रमmat अणु
	जोड़ अणु
		u32 ldw;
		काष्ठा अणु
			u32 idle_to_active         :1;
			u32 preempted              :1;
			u32 element_चयन         :1;
			u32 active_to_idle         :1;
			u32 context_complete       :1;
			u32 रुको_on_sync_flip      :1;
			u32 रुको_on_vblank         :1;
			u32 रुको_on_semaphore      :1;
			u32 रुको_on_scanline       :1;
			u32 reserved               :2;
			u32 semaphore_रुको_mode    :1;
			u32 display_plane          :3;
			u32 lite_restore           :1;
			u32 reserved_2             :16;
		पूर्ण;
	पूर्ण;
	जोड़ अणु
		u32 udw;
		u32 context_id;
	पूर्ण;
पूर्ण;

काष्ठा execlist_mmio_pair अणु
	u32 addr;
	u32 val;
पूर्ण;

/* The first 52 dwords in रेजिस्टर state context */
काष्ठा execlist_ring_context अणु
	u32 nop1;
	u32 lri_cmd_1;
	काष्ठा execlist_mmio_pair ctx_ctrl;
	काष्ठा execlist_mmio_pair ring_header;
	काष्ठा execlist_mmio_pair ring_tail;
	काष्ठा execlist_mmio_pair rb_start;
	काष्ठा execlist_mmio_pair rb_ctrl;
	काष्ठा execlist_mmio_pair bb_cur_head_UDW;
	काष्ठा execlist_mmio_pair bb_cur_head_LDW;
	काष्ठा execlist_mmio_pair bb_state;
	काष्ठा execlist_mmio_pair second_bb_addr_UDW;
	काष्ठा execlist_mmio_pair second_bb_addr_LDW;
	काष्ठा execlist_mmio_pair second_bb_state;
	काष्ठा execlist_mmio_pair bb_per_ctx_ptr;
	काष्ठा execlist_mmio_pair rcs_indirect_ctx;
	काष्ठा execlist_mmio_pair rcs_indirect_ctx_offset;
	u32 nop2;
	u32 nop3;
	u32 nop4;
	u32 lri_cmd_2;
	काष्ठा execlist_mmio_pair ctx_बारtamp;
	/*
	 * pdps[8]=अणु pdp3_UDW, pdp3_LDW, pdp2_UDW, pdp2_LDW,
	 *           pdp1_UDW, pdp1_LDW, pdp0_UDW, pdp0_LDWपूर्ण
	 */
	काष्ठा execlist_mmio_pair pdps[8];
पूर्ण;

काष्ठा पूर्णांकel_vgpu_elsp_dwords अणु
	u32 data[4];
	u32 index;
पूर्ण;

काष्ठा पूर्णांकel_vgpu_execlist_slot अणु
	काष्ठा execlist_ctx_descriptor_क्रमmat ctx[2];
	u32 index;
पूर्ण;

काष्ठा पूर्णांकel_vgpu_execlist अणु
	काष्ठा पूर्णांकel_vgpu_execlist_slot slot[2];
	काष्ठा पूर्णांकel_vgpu_execlist_slot *running_slot;
	काष्ठा पूर्णांकel_vgpu_execlist_slot *pending_slot;
	काष्ठा execlist_ctx_descriptor_क्रमmat *running_context;
	काष्ठा पूर्णांकel_vgpu *vgpu;
	काष्ठा पूर्णांकel_vgpu_elsp_dwords elsp_dwords;
	स्थिर काष्ठा पूर्णांकel_engine_cs *engine;
पूर्ण;

व्योम पूर्णांकel_vgpu_clean_execlist(काष्ठा पूर्णांकel_vgpu *vgpu);

पूर्णांक पूर्णांकel_vgpu_init_execlist(काष्ठा पूर्णांकel_vgpu *vgpu);

पूर्णांक पूर्णांकel_vgpu_submit_execlist(काष्ठा पूर्णांकel_vgpu *vgpu,
			       स्थिर काष्ठा पूर्णांकel_engine_cs *engine);

#पूर्ण_अगर /*_GVT_EXECLIST_H_*/
