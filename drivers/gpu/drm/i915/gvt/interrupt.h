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
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 * Contributors:
 *    Min he <min.he@पूर्णांकel.com>
 *
 */

#अगर_अघोषित _GVT_INTERRUPT_H_
#घोषणा _GVT_INTERRUPT_H_

#समावेश <linux/hrसमयr.h>
#समावेश <linux/kernel.h>

#समावेश "i915_reg.h"

क्रमागत पूर्णांकel_gvt_event_type अणु
	RCS_MI_USER_INTERRUPT = 0,
	RCS_DEBUG,
	RCS_MMIO_SYNC_FLUSH,
	RCS_CMD_STREAMER_ERR,
	RCS_PIPE_CONTROL,
	RCS_L3_PARITY_ERR,
	RCS_WATCHDOG_EXCEEDED,
	RCS_PAGE_सूचीECTORY_FAULT,
	RCS_AS_CONTEXT_SWITCH,
	RCS_MONITOR_BUFF_HALF_FULL,

	VCS_MI_USER_INTERRUPT,
	VCS_MMIO_SYNC_FLUSH,
	VCS_CMD_STREAMER_ERR,
	VCS_MI_FLUSH_DW,
	VCS_WATCHDOG_EXCEEDED,
	VCS_PAGE_सूचीECTORY_FAULT,
	VCS_AS_CONTEXT_SWITCH,

	VCS2_MI_USER_INTERRUPT,
	VCS2_MI_FLUSH_DW,
	VCS2_AS_CONTEXT_SWITCH,

	BCS_MI_USER_INTERRUPT,
	BCS_MMIO_SYNC_FLUSH,
	BCS_CMD_STREAMER_ERR,
	BCS_MI_FLUSH_DW,
	BCS_PAGE_सूचीECTORY_FAULT,
	BCS_AS_CONTEXT_SWITCH,

	VECS_MI_USER_INTERRUPT,
	VECS_MI_FLUSH_DW,
	VECS_AS_CONTEXT_SWITCH,

	PIPE_A_FIFO_UNDERRUN,
	PIPE_B_FIFO_UNDERRUN,
	PIPE_A_CRC_ERR,
	PIPE_B_CRC_ERR,
	PIPE_A_CRC_DONE,
	PIPE_B_CRC_DONE,
	PIPE_A_ODD_FIELD,
	PIPE_B_ODD_FIELD,
	PIPE_A_EVEN_FIELD,
	PIPE_B_EVEN_FIELD,
	PIPE_A_LINE_COMPARE,
	PIPE_B_LINE_COMPARE,
	PIPE_C_LINE_COMPARE,
	PIPE_A_VBLANK,
	PIPE_B_VBLANK,
	PIPE_C_VBLANK,
	PIPE_A_VSYNC,
	PIPE_B_VSYNC,
	PIPE_C_VSYNC,
	PRIMARY_A_FLIP_DONE,
	PRIMARY_B_FLIP_DONE,
	PRIMARY_C_FLIP_DONE,
	SPRITE_A_FLIP_DONE,
	SPRITE_B_FLIP_DONE,
	SPRITE_C_FLIP_DONE,

	PCU_THERMAL,
	PCU_PCODE2DRIVER_MAILBOX,

	DPST_PHASE_IN,
	DPST_HISTOGRAM,
	GSE,
	DP_A_HOTPLUG,
	AUX_CHANNEL_A,
	PERF_COUNTER,
	POISON,
	GTT_FAULT,
	ERROR_INTERRUPT_COMBINED,

	FDI_RX_INTERRUPTS_TRANSCODER_A,
	AUDIO_CP_CHANGE_TRANSCODER_A,
	AUDIO_CP_REQUEST_TRANSCODER_A,
	FDI_RX_INTERRUPTS_TRANSCODER_B,
	AUDIO_CP_CHANGE_TRANSCODER_B,
	AUDIO_CP_REQUEST_TRANSCODER_B,
	FDI_RX_INTERRUPTS_TRANSCODER_C,
	AUDIO_CP_CHANGE_TRANSCODER_C,
	AUDIO_CP_REQUEST_TRANSCODER_C,
	ERR_AND_DBG,
	GMBUS,
	SDVO_B_HOTPLUG,
	CRT_HOTPLUG,
	DP_B_HOTPLUG,
	DP_C_HOTPLUG,
	DP_D_HOTPLUG,
	AUX_CHANNEL_B,
	AUX_CHANNEL_C,
	AUX_CHANNEL_D,
	AUDIO_POWER_STATE_CHANGE_B,
	AUDIO_POWER_STATE_CHANGE_C,
	AUDIO_POWER_STATE_CHANGE_D,

	INTEL_GVT_EVENT_RESERVED,
	INTEL_GVT_EVENT_MAX,
पूर्ण;

काष्ठा पूर्णांकel_gvt_irq;
काष्ठा पूर्णांकel_gvt;
काष्ठा पूर्णांकel_vgpu;

प्रकार व्योम (*gvt_event_virt_handler_t)(काष्ठा पूर्णांकel_gvt_irq *irq,
	क्रमागत पूर्णांकel_gvt_event_type event, काष्ठा पूर्णांकel_vgpu *vgpu);

काष्ठा पूर्णांकel_gvt_irq_ops अणु
	व्योम (*init_irq)(काष्ठा पूर्णांकel_gvt_irq *irq);
	व्योम (*check_pending_irq)(काष्ठा पूर्णांकel_vgpu *vgpu);
पूर्ण;

/* the list of physical पूर्णांकerrupt control रेजिस्टर groups */
क्रमागत पूर्णांकel_gvt_irq_type अणु
	INTEL_GVT_IRQ_INFO_GT,
	INTEL_GVT_IRQ_INFO_DPY,
	INTEL_GVT_IRQ_INFO_PCH,
	INTEL_GVT_IRQ_INFO_PM,

	INTEL_GVT_IRQ_INFO_MASTER,
	INTEL_GVT_IRQ_INFO_GT0,
	INTEL_GVT_IRQ_INFO_GT1,
	INTEL_GVT_IRQ_INFO_GT2,
	INTEL_GVT_IRQ_INFO_GT3,
	INTEL_GVT_IRQ_INFO_DE_PIPE_A,
	INTEL_GVT_IRQ_INFO_DE_PIPE_B,
	INTEL_GVT_IRQ_INFO_DE_PIPE_C,
	INTEL_GVT_IRQ_INFO_DE_PORT,
	INTEL_GVT_IRQ_INFO_DE_MISC,
	INTEL_GVT_IRQ_INFO_AUD,
	INTEL_GVT_IRQ_INFO_PCU,

	INTEL_GVT_IRQ_INFO_MAX,
पूर्ण;

#घोषणा INTEL_GVT_IRQ_BITWIDTH	32

/* device specअगरic पूर्णांकerrupt bit definitions */
काष्ठा पूर्णांकel_gvt_irq_info अणु
	अक्षर *name;
	i915_reg_t reg_base;
	क्रमागत पूर्णांकel_gvt_event_type bit_to_event[INTEL_GVT_IRQ_BITWIDTH];
	अचिन्हित दीर्घ warned;
	पूर्णांक group;
	DECLARE_BITMAP(करोwnstream_irq_biपंचांगap, INTEL_GVT_IRQ_BITWIDTH);
	bool has_upstream_irq;
पूर्ण;

/* per-event inक्रमmation */
काष्ठा पूर्णांकel_gvt_event_info अणु
	पूर्णांक bit;				/* map to रेजिस्टर bit */
	पूर्णांक policy;				/* क्रमwarding policy */
	काष्ठा पूर्णांकel_gvt_irq_info *info;	/* रेजिस्टर info */
	gvt_event_virt_handler_t v_handler;	/* क्रम v_event */
पूर्ण;

काष्ठा पूर्णांकel_gvt_irq_map अणु
	पूर्णांक up_irq_group;
	पूर्णांक up_irq_bit;
	पूर्णांक करोwn_irq_group;
	u32 करोwn_irq_biपंचांगask;
पूर्ण;

/* काष्ठाure containing device specअगरic IRQ state */
काष्ठा पूर्णांकel_gvt_irq अणु
	काष्ठा पूर्णांकel_gvt_irq_ops *ops;
	काष्ठा पूर्णांकel_gvt_irq_info *info[INTEL_GVT_IRQ_INFO_MAX];
	DECLARE_BITMAP(irq_info_biपंचांगap, INTEL_GVT_IRQ_INFO_MAX);
	काष्ठा पूर्णांकel_gvt_event_info events[INTEL_GVT_EVENT_MAX];
	DECLARE_BITMAP(pending_events, INTEL_GVT_EVENT_MAX);
	काष्ठा पूर्णांकel_gvt_irq_map *irq_map;
पूर्ण;

पूर्णांक पूर्णांकel_gvt_init_irq(काष्ठा पूर्णांकel_gvt *gvt);

व्योम पूर्णांकel_vgpu_trigger_भव_event(काष्ठा पूर्णांकel_vgpu *vgpu,
	क्रमागत पूर्णांकel_gvt_event_type event);

पूर्णांक पूर्णांकel_vgpu_reg_iir_handler(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक reg,
	व्योम *p_data, अचिन्हित पूर्णांक bytes);
पूर्णांक पूर्णांकel_vgpu_reg_ier_handler(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक reg, व्योम *p_data, अचिन्हित पूर्णांक bytes);
पूर्णांक पूर्णांकel_vgpu_reg_master_irq_handler(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक reg, व्योम *p_data, अचिन्हित पूर्णांक bytes);
पूर्णांक पूर्णांकel_vgpu_reg_imr_handler(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक reg, व्योम *p_data, अचिन्हित पूर्णांक bytes);

पूर्णांक gvt_ring_id_to_pipe_control_notअगरy_event(पूर्णांक ring_id);
पूर्णांक gvt_ring_id_to_mi_flush_dw_event(पूर्णांक ring_id);
पूर्णांक gvt_ring_id_to_mi_user_पूर्णांकerrupt_event(पूर्णांक ring_id);

#पूर्ण_अगर /* _GVT_INTERRUPT_H_ */
