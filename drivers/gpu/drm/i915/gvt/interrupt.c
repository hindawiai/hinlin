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

#समावेश "i915_drv.h"
#समावेश "gvt.h"
#समावेश "trace.h"

/* common offset among पूर्णांकerrupt control रेजिस्टरs */
#घोषणा regbase_to_isr(base)	(base)
#घोषणा regbase_to_imr(base)	(base + 0x4)
#घोषणा regbase_to_iir(base)	(base + 0x8)
#घोषणा regbase_to_ier(base)	(base + 0xC)

#घोषणा iir_to_regbase(iir)    (iir - 0x8)
#घोषणा ier_to_regbase(ier)    (ier - 0xC)

#घोषणा get_event_virt_handler(irq, e)	(irq->events[e].v_handler)
#घोषणा get_irq_info(irq, e)		(irq->events[e].info)

#घोषणा irq_to_gvt(irq) \
	container_of(irq, काष्ठा पूर्णांकel_gvt, irq)

अटल व्योम update_upstream_irq(काष्ठा पूर्णांकel_vgpu *vgpu,
		काष्ठा पूर्णांकel_gvt_irq_info *info);

अटल स्थिर अक्षर * स्थिर irq_name[INTEL_GVT_EVENT_MAX] = अणु
	[RCS_MI_USER_INTERRUPT] = "Render CS MI USER INTERRUPT",
	[RCS_DEBUG] = "Render EU debug from SVG",
	[RCS_MMIO_SYNC_FLUSH] = "Render MMIO sync flush status",
	[RCS_CMD_STREAMER_ERR] = "Render CS error interrupt",
	[RCS_PIPE_CONTROL] = "Render PIPE CONTROL notify",
	[RCS_WATCHDOG_EXCEEDED] = "Render CS Watchdog counter exceeded",
	[RCS_PAGE_सूचीECTORY_FAULT] = "Render page directory faults",
	[RCS_AS_CONTEXT_SWITCH] = "Render AS Context Switch Interrupt",

	[VCS_MI_USER_INTERRUPT] = "Video CS MI USER INTERRUPT",
	[VCS_MMIO_SYNC_FLUSH] = "Video MMIO sync flush status",
	[VCS_CMD_STREAMER_ERR] = "Video CS error interrupt",
	[VCS_MI_FLUSH_DW] = "Video MI FLUSH DW notify",
	[VCS_WATCHDOG_EXCEEDED] = "Video CS Watchdog counter exceeded",
	[VCS_PAGE_सूचीECTORY_FAULT] = "Video page directory faults",
	[VCS_AS_CONTEXT_SWITCH] = "Video AS Context Switch Interrupt",
	[VCS2_MI_USER_INTERRUPT] = "VCS2 Video CS MI USER INTERRUPT",
	[VCS2_MI_FLUSH_DW] = "VCS2 Video MI FLUSH DW notify",
	[VCS2_AS_CONTEXT_SWITCH] = "VCS2 Context Switch Interrupt",

	[BCS_MI_USER_INTERRUPT] = "Blitter CS MI USER INTERRUPT",
	[BCS_MMIO_SYNC_FLUSH] = "Billter MMIO sync flush status",
	[BCS_CMD_STREAMER_ERR] = "Blitter CS error interrupt",
	[BCS_MI_FLUSH_DW] = "Blitter MI FLUSH DW notify",
	[BCS_PAGE_सूचीECTORY_FAULT] = "Blitter page directory faults",
	[BCS_AS_CONTEXT_SWITCH] = "Blitter AS Context Switch Interrupt",

	[VECS_MI_FLUSH_DW] = "Video Enhanced Streamer MI FLUSH DW notify",
	[VECS_AS_CONTEXT_SWITCH] = "VECS Context Switch Interrupt",

	[PIPE_A_FIFO_UNDERRUN] = "Pipe A FIFO underrun",
	[PIPE_A_CRC_ERR] = "Pipe A CRC error",
	[PIPE_A_CRC_DONE] = "Pipe A CRC done",
	[PIPE_A_VSYNC] = "Pipe A vsync",
	[PIPE_A_LINE_COMPARE] = "Pipe A line compare",
	[PIPE_A_ODD_FIELD] = "Pipe A odd field",
	[PIPE_A_EVEN_FIELD] = "Pipe A even field",
	[PIPE_A_VBLANK] = "Pipe A vblank",
	[PIPE_B_FIFO_UNDERRUN] = "Pipe B FIFO underrun",
	[PIPE_B_CRC_ERR] = "Pipe B CRC error",
	[PIPE_B_CRC_DONE] = "Pipe B CRC done",
	[PIPE_B_VSYNC] = "Pipe B vsync",
	[PIPE_B_LINE_COMPARE] = "Pipe B line compare",
	[PIPE_B_ODD_FIELD] = "Pipe B odd field",
	[PIPE_B_EVEN_FIELD] = "Pipe B even field",
	[PIPE_B_VBLANK] = "Pipe B vblank",
	[PIPE_C_VBLANK] = "Pipe C vblank",
	[DPST_PHASE_IN] = "DPST phase in event",
	[DPST_HISTOGRAM] = "DPST histogram event",
	[GSE] = "GSE",
	[DP_A_HOTPLUG] = "DP A Hotplug",
	[AUX_CHANNEL_A] = "AUX Channel A",
	[PERF_COUNTER] = "Performance counter",
	[POISON] = "Poison",
	[GTT_FAULT] = "GTT fault",
	[PRIMARY_A_FLIP_DONE] = "Primary Plane A flip done",
	[PRIMARY_B_FLIP_DONE] = "Primary Plane B flip done",
	[PRIMARY_C_FLIP_DONE] = "Primary Plane C flip done",
	[SPRITE_A_FLIP_DONE] = "Sprite Plane A flip done",
	[SPRITE_B_FLIP_DONE] = "Sprite Plane B flip done",
	[SPRITE_C_FLIP_DONE] = "Sprite Plane C flip done",

	[PCU_THERMAL] = "PCU Thermal Event",
	[PCU_PCODE2DRIVER_MAILBOX] = "PCU pcode2driver mailbox event",

	[FDI_RX_INTERRUPTS_TRANSCODER_A] = "FDI RX Interrupts Combined A",
	[AUDIO_CP_CHANGE_TRANSCODER_A] = "Audio CP Change Transcoder A",
	[AUDIO_CP_REQUEST_TRANSCODER_A] = "Audio CP Request Transcoder A",
	[FDI_RX_INTERRUPTS_TRANSCODER_B] = "FDI RX Interrupts Combined B",
	[AUDIO_CP_CHANGE_TRANSCODER_B] = "Audio CP Change Transcoder B",
	[AUDIO_CP_REQUEST_TRANSCODER_B] = "Audio CP Request Transcoder B",
	[FDI_RX_INTERRUPTS_TRANSCODER_C] = "FDI RX Interrupts Combined C",
	[AUDIO_CP_CHANGE_TRANSCODER_C] = "Audio CP Change Transcoder C",
	[AUDIO_CP_REQUEST_TRANSCODER_C] = "Audio CP Request Transcoder C",
	[ERR_AND_DBG] = "South Error and Debug Interrupts Combined",
	[GMBUS] = "Gmbus",
	[SDVO_B_HOTPLUG] = "SDVO B hotplug",
	[CRT_HOTPLUG] = "CRT Hotplug",
	[DP_B_HOTPLUG] = "DisplayPort/HDMI/DVI B Hotplug",
	[DP_C_HOTPLUG] = "DisplayPort/HDMI/DVI C Hotplug",
	[DP_D_HOTPLUG] = "DisplayPort/HDMI/DVI D Hotplug",
	[AUX_CHANNEL_B] = "AUX Channel B",
	[AUX_CHANNEL_C] = "AUX Channel C",
	[AUX_CHANNEL_D] = "AUX Channel D",
	[AUDIO_POWER_STATE_CHANGE_B] = "Audio Power State change Port B",
	[AUDIO_POWER_STATE_CHANGE_C] = "Audio Power State change Port C",
	[AUDIO_POWER_STATE_CHANGE_D] = "Audio Power State change Port D",

	[INTEL_GVT_EVENT_RESERVED] = "RESERVED EVENTS!!!",
पूर्ण;

अटल अंतरभूत काष्ठा पूर्णांकel_gvt_irq_info *regbase_to_irq_info(
		काष्ठा पूर्णांकel_gvt *gvt,
		अचिन्हित पूर्णांक reg)
अणु
	काष्ठा पूर्णांकel_gvt_irq *irq = &gvt->irq;
	पूर्णांक i;

	क्रम_each_set_bit(i, irq->irq_info_biपंचांगap, INTEL_GVT_IRQ_INFO_MAX) अणु
		अगर (i915_mmio_reg_offset(irq->info[i]->reg_base) == reg)
			वापस irq->info[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * पूर्णांकel_vgpu_reg_imr_handler - Generic IMR रेजिस्टर emulation ग_लिखो handler
 * @vgpu: a vGPU
 * @reg: रेजिस्टर offset written by guest
 * @p_data: रेजिस्टर data written by guest
 * @bytes: रेजिस्टर data length
 *
 * This function is used to emulate the generic IMR रेजिस्टर bit change
 * behavior.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 *
 */
पूर्णांक पूर्णांकel_vgpu_reg_imr_handler(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक reg, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_irq_ops *ops = gvt->irq.ops;
	u32 imr = *(u32 *)p_data;

	trace_ग_लिखो_ir(vgpu->id, "IMR", reg, imr, vgpu_vreg(vgpu, reg),
		       (vgpu_vreg(vgpu, reg) ^ imr));

	vgpu_vreg(vgpu, reg) = imr;

	ops->check_pending_irq(vgpu);

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_vgpu_reg_master_irq_handler - master IRQ ग_लिखो emulation handler
 * @vgpu: a vGPU
 * @reg: रेजिस्टर offset written by guest
 * @p_data: रेजिस्टर data written by guest
 * @bytes: रेजिस्टर data length
 *
 * This function is used to emulate the master IRQ रेजिस्टर on gen8+.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 *
 */
पूर्णांक पूर्णांकel_vgpu_reg_master_irq_handler(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक reg, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_irq_ops *ops = gvt->irq.ops;
	u32 ier = *(u32 *)p_data;
	u32 भव_ier = vgpu_vreg(vgpu, reg);

	trace_ग_लिखो_ir(vgpu->id, "MASTER_IRQ", reg, ier, भव_ier,
		       (भव_ier ^ ier));

	/*
	 * GEN8_MASTER_IRQ is a special irq रेजिस्टर,
	 * only bit 31 is allowed to be modअगरied
	 * and treated as an IER bit.
	 */
	ier &= GEN8_MASTER_IRQ_CONTROL;
	भव_ier &= GEN8_MASTER_IRQ_CONTROL;
	vgpu_vreg(vgpu, reg) &= ~GEN8_MASTER_IRQ_CONTROL;
	vgpu_vreg(vgpu, reg) |= ier;

	ops->check_pending_irq(vgpu);

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_vgpu_reg_ier_handler - Generic IER ग_लिखो emulation handler
 * @vgpu: a vGPU
 * @reg: रेजिस्टर offset written by guest
 * @p_data: रेजिस्टर data written by guest
 * @bytes: रेजिस्टर data length
 *
 * This function is used to emulate the generic IER रेजिस्टर behavior.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 *
 */
पूर्णांक पूर्णांकel_vgpu_reg_ier_handler(काष्ठा पूर्णांकel_vgpu *vgpu,
	अचिन्हित पूर्णांक reg, व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा drm_i915_निजी *i915 = gvt->gt->i915;
	काष्ठा पूर्णांकel_gvt_irq_ops *ops = gvt->irq.ops;
	काष्ठा पूर्णांकel_gvt_irq_info *info;
	u32 ier = *(u32 *)p_data;

	trace_ग_लिखो_ir(vgpu->id, "IER", reg, ier, vgpu_vreg(vgpu, reg),
		       (vgpu_vreg(vgpu, reg) ^ ier));

	vgpu_vreg(vgpu, reg) = ier;

	info = regbase_to_irq_info(gvt, ier_to_regbase(reg));
	अगर (drm_WARN_ON(&i915->drm, !info))
		वापस -EINVAL;

	अगर (info->has_upstream_irq)
		update_upstream_irq(vgpu, info);

	ops->check_pending_irq(vgpu);

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_vgpu_reg_iir_handler - Generic IIR ग_लिखो emulation handler
 * @vgpu: a vGPU
 * @reg: रेजिस्टर offset written by guest
 * @p_data: रेजिस्टर data written by guest
 * @bytes: रेजिस्टर data length
 *
 * This function is used to emulate the generic IIR रेजिस्टर behavior.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 *
 */
पूर्णांक पूर्णांकel_vgpu_reg_iir_handler(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक reg,
	व्योम *p_data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	काष्ठा पूर्णांकel_gvt_irq_info *info = regbase_to_irq_info(vgpu->gvt,
		iir_to_regbase(reg));
	u32 iir = *(u32 *)p_data;

	trace_ग_लिखो_ir(vgpu->id, "IIR", reg, iir, vgpu_vreg(vgpu, reg),
		       (vgpu_vreg(vgpu, reg) ^ iir));

	अगर (drm_WARN_ON(&i915->drm, !info))
		वापस -EINVAL;

	vgpu_vreg(vgpu, reg) &= ~iir;

	अगर (info->has_upstream_irq)
		update_upstream_irq(vgpu, info);
	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_gvt_irq_map gen8_irq_map[] = अणु
	अणु INTEL_GVT_IRQ_INFO_MASTER, 0, INTEL_GVT_IRQ_INFO_GT0, 0xffff पूर्ण,
	अणु INTEL_GVT_IRQ_INFO_MASTER, 1, INTEL_GVT_IRQ_INFO_GT0, 0xffff0000 पूर्ण,
	अणु INTEL_GVT_IRQ_INFO_MASTER, 2, INTEL_GVT_IRQ_INFO_GT1, 0xffff पूर्ण,
	अणु INTEL_GVT_IRQ_INFO_MASTER, 3, INTEL_GVT_IRQ_INFO_GT1, 0xffff0000 पूर्ण,
	अणु INTEL_GVT_IRQ_INFO_MASTER, 4, INTEL_GVT_IRQ_INFO_GT2, 0xffff पूर्ण,
	अणु INTEL_GVT_IRQ_INFO_MASTER, 6, INTEL_GVT_IRQ_INFO_GT3, 0xffff पूर्ण,
	अणु INTEL_GVT_IRQ_INFO_MASTER, 16, INTEL_GVT_IRQ_INFO_DE_PIPE_A, ~0 पूर्ण,
	अणु INTEL_GVT_IRQ_INFO_MASTER, 17, INTEL_GVT_IRQ_INFO_DE_PIPE_B, ~0 पूर्ण,
	अणु INTEL_GVT_IRQ_INFO_MASTER, 18, INTEL_GVT_IRQ_INFO_DE_PIPE_C, ~0 पूर्ण,
	अणु INTEL_GVT_IRQ_INFO_MASTER, 20, INTEL_GVT_IRQ_INFO_DE_PORT, ~0 पूर्ण,
	अणु INTEL_GVT_IRQ_INFO_MASTER, 22, INTEL_GVT_IRQ_INFO_DE_MISC, ~0 पूर्ण,
	अणु INTEL_GVT_IRQ_INFO_MASTER, 23, INTEL_GVT_IRQ_INFO_PCH, ~0 पूर्ण,
	अणु INTEL_GVT_IRQ_INFO_MASTER, 30, INTEL_GVT_IRQ_INFO_PCU, ~0 पूर्ण,
	अणु -1, -1, ~0 पूर्ण,
पूर्ण;

अटल व्योम update_upstream_irq(काष्ठा पूर्णांकel_vgpu *vgpu,
		काष्ठा पूर्णांकel_gvt_irq_info *info)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	काष्ठा पूर्णांकel_gvt_irq *irq = &vgpu->gvt->irq;
	काष्ठा पूर्णांकel_gvt_irq_map *map = irq->irq_map;
	काष्ठा पूर्णांकel_gvt_irq_info *up_irq_info = शून्य;
	u32 set_bits = 0;
	u32 clear_bits = 0;
	पूर्णांक bit;
	u32 val = vgpu_vreg(vgpu,
			regbase_to_iir(i915_mmio_reg_offset(info->reg_base)))
		& vgpu_vreg(vgpu,
			regbase_to_ier(i915_mmio_reg_offset(info->reg_base)));

	अगर (!info->has_upstream_irq)
		वापस;

	क्रम (map = irq->irq_map; map->up_irq_bit != -1; map++) अणु
		अगर (info->group != map->करोwn_irq_group)
			जारी;

		अगर (!up_irq_info)
			up_irq_info = irq->info[map->up_irq_group];
		अन्यथा
			drm_WARN_ON(&i915->drm, up_irq_info !=
				    irq->info[map->up_irq_group]);

		bit = map->up_irq_bit;

		अगर (val & map->करोwn_irq_biपंचांगask)
			set_bits |= (1 << bit);
		अन्यथा
			clear_bits |= (1 << bit);
	पूर्ण

	अगर (drm_WARN_ON(&i915->drm, !up_irq_info))
		वापस;

	अगर (up_irq_info->group == INTEL_GVT_IRQ_INFO_MASTER) अणु
		u32 isr = i915_mmio_reg_offset(up_irq_info->reg_base);

		vgpu_vreg(vgpu, isr) &= ~clear_bits;
		vgpu_vreg(vgpu, isr) |= set_bits;
	पूर्ण अन्यथा अणु
		u32 iir = regbase_to_iir(
			i915_mmio_reg_offset(up_irq_info->reg_base));
		u32 imr = regbase_to_imr(
			i915_mmio_reg_offset(up_irq_info->reg_base));

		vgpu_vreg(vgpu, iir) |= (set_bits & ~vgpu_vreg(vgpu, imr));
	पूर्ण

	अगर (up_irq_info->has_upstream_irq)
		update_upstream_irq(vgpu, up_irq_info);
पूर्ण

अटल व्योम init_irq_map(काष्ठा पूर्णांकel_gvt_irq *irq)
अणु
	काष्ठा पूर्णांकel_gvt_irq_map *map;
	काष्ठा पूर्णांकel_gvt_irq_info *up_info, *करोwn_info;
	पूर्णांक up_bit;

	क्रम (map = irq->irq_map; map->up_irq_bit != -1; map++) अणु
		up_info = irq->info[map->up_irq_group];
		up_bit = map->up_irq_bit;
		करोwn_info = irq->info[map->करोwn_irq_group];

		set_bit(up_bit, up_info->करोwnstream_irq_biपंचांगap);
		करोwn_info->has_upstream_irq = true;

		gvt_dbg_irq("[up] grp %d bit %d -> [down] grp %d bitmask %x\n",
			up_info->group, up_bit,
			करोwn_info->group, map->करोwn_irq_biपंचांगask);
	पूर्ण
पूर्ण

/* =======================vEvent injection===================== */
अटल पूर्णांक inject_भव_पूर्णांकerrupt(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	वापस पूर्णांकel_gvt_hypervisor_inject_msi(vgpu);
पूर्ण

अटल व्योम propagate_event(काष्ठा पूर्णांकel_gvt_irq *irq,
	क्रमागत पूर्णांकel_gvt_event_type event, काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_gvt_irq_info *info;
	अचिन्हित पूर्णांक reg_base;
	पूर्णांक bit;

	info = get_irq_info(irq, event);
	अगर (WARN_ON(!info))
		वापस;

	reg_base = i915_mmio_reg_offset(info->reg_base);
	bit = irq->events[event].bit;

	अगर (!test_bit(bit, (व्योम *)&vgpu_vreg(vgpu,
					regbase_to_imr(reg_base)))) अणु
		trace_propagate_event(vgpu->id, irq_name[event], bit);
		set_bit(bit, (व्योम *)&vgpu_vreg(vgpu,
					regbase_to_iir(reg_base)));
	पूर्ण
पूर्ण

/* =======================vEvent Handlers===================== */
अटल व्योम handle_शेष_event_virt(काष्ठा पूर्णांकel_gvt_irq *irq,
	क्रमागत पूर्णांकel_gvt_event_type event, काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	अगर (!vgpu->irq.irq_warn_once[event]) अणु
		gvt_dbg_core("vgpu%d: IRQ receive event %d (%s)\n",
			vgpu->id, event, irq_name[event]);
		vgpu->irq.irq_warn_once[event] = true;
	पूर्ण
	propagate_event(irq, event, vgpu);
पूर्ण

/* =====================GEN specअगरic logic======================= */
/* GEN8 पूर्णांकerrupt routines. */

#घोषणा DEFINE_GVT_GEN8_INTEL_GVT_IRQ_INFO(regname, regbase) \
अटल काष्ठा पूर्णांकel_gvt_irq_info gen8_##regname##_info = अणु \
	.name = #regname"-IRQ", \
	.reg_base = (regbase), \
	.bit_to_event = अणु[0 ... INTEL_GVT_IRQ_BITWIDTH-1] = \
		INTEL_GVT_EVENT_RESERVEDपूर्ण, \
पूर्ण

DEFINE_GVT_GEN8_INTEL_GVT_IRQ_INFO(gt0, GEN8_GT_ISR(0));
DEFINE_GVT_GEN8_INTEL_GVT_IRQ_INFO(gt1, GEN8_GT_ISR(1));
DEFINE_GVT_GEN8_INTEL_GVT_IRQ_INFO(gt2, GEN8_GT_ISR(2));
DEFINE_GVT_GEN8_INTEL_GVT_IRQ_INFO(gt3, GEN8_GT_ISR(3));
DEFINE_GVT_GEN8_INTEL_GVT_IRQ_INFO(de_pipe_a, GEN8_DE_PIPE_ISR(PIPE_A));
DEFINE_GVT_GEN8_INTEL_GVT_IRQ_INFO(de_pipe_b, GEN8_DE_PIPE_ISR(PIPE_B));
DEFINE_GVT_GEN8_INTEL_GVT_IRQ_INFO(de_pipe_c, GEN8_DE_PIPE_ISR(PIPE_C));
DEFINE_GVT_GEN8_INTEL_GVT_IRQ_INFO(de_port, GEN8_DE_PORT_ISR);
DEFINE_GVT_GEN8_INTEL_GVT_IRQ_INFO(de_misc, GEN8_DE_MISC_ISR);
DEFINE_GVT_GEN8_INTEL_GVT_IRQ_INFO(pcu, GEN8_PCU_ISR);
DEFINE_GVT_GEN8_INTEL_GVT_IRQ_INFO(master, GEN8_MASTER_IRQ);

अटल काष्ठा पूर्णांकel_gvt_irq_info gvt_base_pch_info = अणु
	.name = "PCH-IRQ",
	.reg_base = SDEISR,
	.bit_to_event = अणु[0 ... INTEL_GVT_IRQ_BITWIDTH-1] =
		INTEL_GVT_EVENT_RESERVEDपूर्ण,
पूर्ण;

अटल व्योम gen8_check_pending_irq(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_gvt_irq *irq = &vgpu->gvt->irq;
	पूर्णांक i;

	अगर (!(vgpu_vreg(vgpu, i915_mmio_reg_offset(GEN8_MASTER_IRQ)) &
				GEN8_MASTER_IRQ_CONTROL))
		वापस;

	क्रम_each_set_bit(i, irq->irq_info_biपंचांगap, INTEL_GVT_IRQ_INFO_MAX) अणु
		काष्ठा पूर्णांकel_gvt_irq_info *info = irq->info[i];
		u32 reg_base;

		अगर (!info->has_upstream_irq)
			जारी;

		reg_base = i915_mmio_reg_offset(info->reg_base);
		अगर ((vgpu_vreg(vgpu, regbase_to_iir(reg_base))
				& vgpu_vreg(vgpu, regbase_to_ier(reg_base))))
			update_upstream_irq(vgpu, info);
	पूर्ण

	अगर (vgpu_vreg(vgpu, i915_mmio_reg_offset(GEN8_MASTER_IRQ))
			& ~GEN8_MASTER_IRQ_CONTROL)
		inject_भव_पूर्णांकerrupt(vgpu);
पूर्ण

अटल व्योम gen8_init_irq(
		काष्ठा पूर्णांकel_gvt_irq *irq)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = irq_to_gvt(irq);

#घोषणा SET_BIT_INFO(s, b, e, i)		\
	करो अणु					\
		s->events[e].bit = b;		\
		s->events[e].info = s->info[i];	\
		s->info[i]->bit_to_event[b] = e;\
	पूर्ण जबतक (0)

#घोषणा SET_IRQ_GROUP(s, g, i) \
	करो अणु \
		s->info[g] = i; \
		(i)->group = g; \
		set_bit(g, s->irq_info_biपंचांगap); \
	पूर्ण जबतक (0)

	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_MASTER, &gen8_master_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_GT0, &gen8_gt0_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_GT1, &gen8_gt1_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_GT2, &gen8_gt2_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_GT3, &gen8_gt3_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_DE_PIPE_A, &gen8_de_pipe_a_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_DE_PIPE_B, &gen8_de_pipe_b_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_DE_PIPE_C, &gen8_de_pipe_c_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_DE_PORT, &gen8_de_port_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_DE_MISC, &gen8_de_misc_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_PCU, &gen8_pcu_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_PCH, &gvt_base_pch_info);

	/* GEN8 level 2 पूर्णांकerrupts. */

	/* GEN8 पूर्णांकerrupt GT0 events */
	SET_BIT_INFO(irq, 0, RCS_MI_USER_INTERRUPT, INTEL_GVT_IRQ_INFO_GT0);
	SET_BIT_INFO(irq, 4, RCS_PIPE_CONTROL, INTEL_GVT_IRQ_INFO_GT0);
	SET_BIT_INFO(irq, 8, RCS_AS_CONTEXT_SWITCH, INTEL_GVT_IRQ_INFO_GT0);

	SET_BIT_INFO(irq, 16, BCS_MI_USER_INTERRUPT, INTEL_GVT_IRQ_INFO_GT0);
	SET_BIT_INFO(irq, 20, BCS_MI_FLUSH_DW, INTEL_GVT_IRQ_INFO_GT0);
	SET_BIT_INFO(irq, 24, BCS_AS_CONTEXT_SWITCH, INTEL_GVT_IRQ_INFO_GT0);

	/* GEN8 पूर्णांकerrupt GT1 events */
	SET_BIT_INFO(irq, 0, VCS_MI_USER_INTERRUPT, INTEL_GVT_IRQ_INFO_GT1);
	SET_BIT_INFO(irq, 4, VCS_MI_FLUSH_DW, INTEL_GVT_IRQ_INFO_GT1);
	SET_BIT_INFO(irq, 8, VCS_AS_CONTEXT_SWITCH, INTEL_GVT_IRQ_INFO_GT1);

	अगर (HAS_ENGINE(gvt->gt, VCS1)) अणु
		SET_BIT_INFO(irq, 16, VCS2_MI_USER_INTERRUPT,
			INTEL_GVT_IRQ_INFO_GT1);
		SET_BIT_INFO(irq, 20, VCS2_MI_FLUSH_DW,
			INTEL_GVT_IRQ_INFO_GT1);
		SET_BIT_INFO(irq, 24, VCS2_AS_CONTEXT_SWITCH,
			INTEL_GVT_IRQ_INFO_GT1);
	पूर्ण

	/* GEN8 पूर्णांकerrupt GT3 events */
	SET_BIT_INFO(irq, 0, VECS_MI_USER_INTERRUPT, INTEL_GVT_IRQ_INFO_GT3);
	SET_BIT_INFO(irq, 4, VECS_MI_FLUSH_DW, INTEL_GVT_IRQ_INFO_GT3);
	SET_BIT_INFO(irq, 8, VECS_AS_CONTEXT_SWITCH, INTEL_GVT_IRQ_INFO_GT3);

	SET_BIT_INFO(irq, 0, PIPE_A_VBLANK, INTEL_GVT_IRQ_INFO_DE_PIPE_A);
	SET_BIT_INFO(irq, 0, PIPE_B_VBLANK, INTEL_GVT_IRQ_INFO_DE_PIPE_B);
	SET_BIT_INFO(irq, 0, PIPE_C_VBLANK, INTEL_GVT_IRQ_INFO_DE_PIPE_C);

	/* GEN8 पूर्णांकerrupt DE PORT events */
	SET_BIT_INFO(irq, 0, AUX_CHANNEL_A, INTEL_GVT_IRQ_INFO_DE_PORT);
	SET_BIT_INFO(irq, 3, DP_A_HOTPLUG, INTEL_GVT_IRQ_INFO_DE_PORT);

	/* GEN8 पूर्णांकerrupt DE MISC events */
	SET_BIT_INFO(irq, 0, GSE, INTEL_GVT_IRQ_INFO_DE_MISC);

	/* PCH events */
	SET_BIT_INFO(irq, 17, GMBUS, INTEL_GVT_IRQ_INFO_PCH);
	SET_BIT_INFO(irq, 19, CRT_HOTPLUG, INTEL_GVT_IRQ_INFO_PCH);
	SET_BIT_INFO(irq, 21, DP_B_HOTPLUG, INTEL_GVT_IRQ_INFO_PCH);
	SET_BIT_INFO(irq, 22, DP_C_HOTPLUG, INTEL_GVT_IRQ_INFO_PCH);
	SET_BIT_INFO(irq, 23, DP_D_HOTPLUG, INTEL_GVT_IRQ_INFO_PCH);

	अगर (IS_BROADWELL(gvt->gt->i915)) अणु
		SET_BIT_INFO(irq, 25, AUX_CHANNEL_B, INTEL_GVT_IRQ_INFO_PCH);
		SET_BIT_INFO(irq, 26, AUX_CHANNEL_C, INTEL_GVT_IRQ_INFO_PCH);
		SET_BIT_INFO(irq, 27, AUX_CHANNEL_D, INTEL_GVT_IRQ_INFO_PCH);

		SET_BIT_INFO(irq, 4, PRIMARY_A_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_A);
		SET_BIT_INFO(irq, 5, SPRITE_A_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_A);

		SET_BIT_INFO(irq, 4, PRIMARY_B_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_B);
		SET_BIT_INFO(irq, 5, SPRITE_B_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_B);

		SET_BIT_INFO(irq, 4, PRIMARY_C_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_C);
		SET_BIT_INFO(irq, 5, SPRITE_C_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_C);
	पूर्ण अन्यथा अगर (INTEL_GEN(gvt->gt->i915) >= 9) अणु
		SET_BIT_INFO(irq, 25, AUX_CHANNEL_B, INTEL_GVT_IRQ_INFO_DE_PORT);
		SET_BIT_INFO(irq, 26, AUX_CHANNEL_C, INTEL_GVT_IRQ_INFO_DE_PORT);
		SET_BIT_INFO(irq, 27, AUX_CHANNEL_D, INTEL_GVT_IRQ_INFO_DE_PORT);

		SET_BIT_INFO(irq, 3, PRIMARY_A_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_A);
		SET_BIT_INFO(irq, 3, PRIMARY_B_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_B);
		SET_BIT_INFO(irq, 3, PRIMARY_C_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_C);

		SET_BIT_INFO(irq, 4, SPRITE_A_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_A);
		SET_BIT_INFO(irq, 4, SPRITE_B_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_B);
		SET_BIT_INFO(irq, 4, SPRITE_C_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_C);
	पूर्ण

	/* GEN8 पूर्णांकerrupt PCU events */
	SET_BIT_INFO(irq, 24, PCU_THERMAL, INTEL_GVT_IRQ_INFO_PCU);
	SET_BIT_INFO(irq, 25, PCU_PCODE2DRIVER_MAILBOX, INTEL_GVT_IRQ_INFO_PCU);
पूर्ण

अटल काष्ठा पूर्णांकel_gvt_irq_ops gen8_irq_ops = अणु
	.init_irq = gen8_init_irq,
	.check_pending_irq = gen8_check_pending_irq,
पूर्ण;

/**
 * पूर्णांकel_vgpu_trigger_भव_event - Trigger a भव event क्रम a vGPU
 * @vgpu: a vGPU
 * @event: पूर्णांकerrupt event
 *
 * This function is used to trigger a भव पूर्णांकerrupt event क्रम vGPU.
 * The caller provides the event to be triggered, the framework itself
 * will emulate the IRQ रेजिस्टर bit change.
 *
 */
व्योम पूर्णांकel_vgpu_trigger_भव_event(काष्ठा पूर्णांकel_vgpu *vgpu,
	क्रमागत पूर्णांकel_gvt_event_type event)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_irq *irq = &gvt->irq;
	gvt_event_virt_handler_t handler;
	काष्ठा पूर्णांकel_gvt_irq_ops *ops = gvt->irq.ops;

	handler = get_event_virt_handler(irq, event);
	drm_WARN_ON(&i915->drm, !handler);

	handler(irq, event, vgpu);

	ops->check_pending_irq(vgpu);
पूर्ण

अटल व्योम init_events(
	काष्ठा पूर्णांकel_gvt_irq *irq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < INTEL_GVT_EVENT_MAX; i++) अणु
		irq->events[i].info = शून्य;
		irq->events[i].v_handler = handle_शेष_event_virt;
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_gvt_init_irq - initialize GVT-g IRQ emulation subप्रणाली
 * @gvt: a GVT device
 *
 * This function is called at driver loading stage, to initialize the GVT-g IRQ
 * emulation subप्रणाली.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 */
पूर्णांक पूर्णांकel_gvt_init_irq(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_gvt_irq *irq = &gvt->irq;

	gvt_dbg_core("init irq framework\n");

	irq->ops = &gen8_irq_ops;
	irq->irq_map = gen8_irq_map;

	/* common event initialization */
	init_events(irq);

	/* gen specअगरic initialization */
	irq->ops->init_irq(irq);

	init_irq_map(irq);

	वापस 0;
पूर्ण
