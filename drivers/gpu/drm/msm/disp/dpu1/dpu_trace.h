<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2014-2018, The Linux Foundation. All rights reserved.
 */

#अगर !defined(_DPU_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _DPU_TRACE_H_

#समावेश <linux/stringअगरy.h>
#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#समावेश <drm/drm_rect.h>
#समावेश "dpu_crtc.h"
#समावेश "dpu_encoder_phys.h"
#समावेश "dpu_hw_mdss.h"
#समावेश "dpu_hw_vbif.h"
#समावेश "dpu_plane.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM dpu
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता dpu_trace

TRACE_EVENT(dpu_perf_set_qos_luts,
	TP_PROTO(u32 pnum, u32 fmt, bool rt, u32 fl,
		u32 lut, u32 lut_usage),
	TP_ARGS(pnum, fmt, rt, fl, lut, lut_usage),
	TP_STRUCT__entry(
			__field(u32, pnum)
			__field(u32, fmt)
			__field(bool, rt)
			__field(u32, fl)
			__field(u64, lut)
			__field(u32, lut_usage)
	),
	TP_fast_assign(
			__entry->pnum = pnum;
			__entry->fmt = fmt;
			__entry->rt = rt;
			__entry->fl = fl;
			__entry->lut = lut;
			__entry->lut_usage = lut_usage;
	),
	TP_prपूर्णांकk("pnum=%d fmt=%x rt=%d fl=%d lut=0x%llx lut_usage=%d",
			__entry->pnum, __entry->fmt,
			__entry->rt, __entry->fl,
			__entry->lut, __entry->lut_usage)
);

TRACE_EVENT(dpu_perf_set_danger_luts,
	TP_PROTO(u32 pnum, u32 fmt, u32 mode, u32 danger_lut,
		u32 safe_lut),
	TP_ARGS(pnum, fmt, mode, danger_lut, safe_lut),
	TP_STRUCT__entry(
			__field(u32, pnum)
			__field(u32, fmt)
			__field(u32, mode)
			__field(u32, danger_lut)
			__field(u32, safe_lut)
	),
	TP_fast_assign(
			__entry->pnum = pnum;
			__entry->fmt = fmt;
			__entry->mode = mode;
			__entry->danger_lut = danger_lut;
			__entry->safe_lut = safe_lut;
	),
	TP_prपूर्णांकk("pnum=%d fmt=%x mode=%d luts[0x%x, 0x%x]",
			__entry->pnum, __entry->fmt,
			__entry->mode, __entry->danger_lut,
			__entry->safe_lut)
);

TRACE_EVENT(dpu_perf_set_ot,
	TP_PROTO(u32 pnum, u32 xin_id, u32 rd_lim, u32 vbअगर_idx),
	TP_ARGS(pnum, xin_id, rd_lim, vbअगर_idx),
	TP_STRUCT__entry(
			__field(u32, pnum)
			__field(u32, xin_id)
			__field(u32, rd_lim)
			__field(u32, vbअगर_idx)
	),
	TP_fast_assign(
			__entry->pnum = pnum;
			__entry->xin_id = xin_id;
			__entry->rd_lim = rd_lim;
			__entry->vbअगर_idx = vbअगर_idx;
	),
	TP_prपूर्णांकk("pnum:%d xin_id:%d ot:%d vbif:%d",
			__entry->pnum, __entry->xin_id, __entry->rd_lim,
			__entry->vbअगर_idx)
)

TRACE_EVENT(dpu_cmd_release_bw,
	TP_PROTO(u32 crtc_id),
	TP_ARGS(crtc_id),
	TP_STRUCT__entry(
			__field(u32, crtc_id)
	),
	TP_fast_assign(
			__entry->crtc_id = crtc_id;
	),
	TP_prपूर्णांकk("crtc:%d", __entry->crtc_id)
);

TRACE_EVENT(tracing_mark_ग_लिखो,
	TP_PROTO(पूर्णांक pid, स्थिर अक्षर *name, bool trace_begin),
	TP_ARGS(pid, name, trace_begin),
	TP_STRUCT__entry(
			__field(पूर्णांक, pid)
			__string(trace_name, name)
			__field(bool, trace_begin)
	),
	TP_fast_assign(
			__entry->pid = pid;
			__assign_str(trace_name, name);
			__entry->trace_begin = trace_begin;
	),
	TP_prपूर्णांकk("%s|%d|%s", __entry->trace_begin ? "B" : "E",
		__entry->pid, __get_str(trace_name))
)

TRACE_EVENT(dpu_trace_counter,
	TP_PROTO(पूर्णांक pid, अक्षर *name, पूर्णांक value),
	TP_ARGS(pid, name, value),
	TP_STRUCT__entry(
			__field(पूर्णांक, pid)
			__string(counter_name, name)
			__field(पूर्णांक, value)
	),
	TP_fast_assign(
			__entry->pid = current->tgid;
			__assign_str(counter_name, name);
			__entry->value = value;
	),
	TP_prपूर्णांकk("%d|%s|%d", __entry->pid,
			__get_str(counter_name), __entry->value)
)

TRACE_EVENT(dpu_perf_crtc_update,
	TP_PROTO(u32 crtc, u64 bw_ctl, u32 core_clk_rate,
			bool stop_req, bool update_bus, bool update_clk),
	TP_ARGS(crtc, bw_ctl, core_clk_rate, stop_req, update_bus, update_clk),
	TP_STRUCT__entry(
			__field(u32, crtc)
			__field(u64, bw_ctl)
			__field(u32, core_clk_rate)
			__field(bool, stop_req)
			__field(u32, update_bus)
			__field(u32, update_clk)
	),
	TP_fast_assign(
			__entry->crtc = crtc;
			__entry->bw_ctl = bw_ctl;
			__entry->core_clk_rate = core_clk_rate;
			__entry->stop_req = stop_req;
			__entry->update_bus = update_bus;
			__entry->update_clk = update_clk;
	),
	 TP_prपूर्णांकk(
		"crtc=%d bw_ctl=%llu clk_rate=%u stop_req=%d u_bus=%d u_clk=%d",
			__entry->crtc,
			__entry->bw_ctl,
			__entry->core_clk_rate,
			__entry->stop_req,
			__entry->update_bus,
			__entry->update_clk)
);

DECLARE_EVENT_CLASS(dpu_enc_irq_ढाँचा,
	TP_PROTO(uपूर्णांक32_t drm_id, क्रमागत dpu_पूर्णांकr_idx पूर्णांकr_idx, पूर्णांक hw_idx,
		 पूर्णांक irq_idx),
	TP_ARGS(drm_id, पूर्णांकr_idx, hw_idx, irq_idx),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id		)
		__field(	क्रमागत dpu_पूर्णांकr_idx,	पूर्णांकr_idx	)
		__field(	पूर्णांक,			hw_idx		)
		__field(	पूर्णांक,			irq_idx		)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->पूर्णांकr_idx = पूर्णांकr_idx;
		__entry->hw_idx = hw_idx;
		__entry->irq_idx = irq_idx;
	),
	TP_prपूर्णांकk("id=%u, intr=%d, hw=%d, irq=%d",
		  __entry->drm_id, __entry->पूर्णांकr_idx, __entry->hw_idx,
		  __entry->irq_idx)
);
DEFINE_EVENT(dpu_enc_irq_ढाँचा, dpu_enc_irq_रेजिस्टर_success,
	TP_PROTO(uपूर्णांक32_t drm_id, क्रमागत dpu_पूर्णांकr_idx पूर्णांकr_idx, पूर्णांक hw_idx,
		 पूर्णांक irq_idx),
	TP_ARGS(drm_id, पूर्णांकr_idx, hw_idx, irq_idx)
);
DEFINE_EVENT(dpu_enc_irq_ढाँचा, dpu_enc_irq_unरेजिस्टर_success,
	TP_PROTO(uपूर्णांक32_t drm_id, क्रमागत dpu_पूर्णांकr_idx पूर्णांकr_idx, पूर्णांक hw_idx,
		 पूर्णांक irq_idx),
	TP_ARGS(drm_id, पूर्णांकr_idx, hw_idx, irq_idx)
);

TRACE_EVENT(dpu_enc_irq_रुको_success,
	TP_PROTO(uपूर्णांक32_t drm_id, क्रमागत dpu_पूर्णांकr_idx पूर्णांकr_idx, पूर्णांक hw_idx,
		 पूर्णांक irq_idx, क्रमागत dpu_pingpong pp_idx, पूर्णांक atomic_cnt),
	TP_ARGS(drm_id, पूर्णांकr_idx, hw_idx, irq_idx, pp_idx, atomic_cnt),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id		)
		__field(	क्रमागत dpu_पूर्णांकr_idx,	पूर्णांकr_idx	)
		__field(	पूर्णांक,			hw_idx		)
		__field(	पूर्णांक,			irq_idx		)
		__field(	क्रमागत dpu_pingpong,	pp_idx		)
		__field(	पूर्णांक,			atomic_cnt	)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->पूर्णांकr_idx = पूर्णांकr_idx;
		__entry->hw_idx = hw_idx;
		__entry->irq_idx = irq_idx;
		__entry->pp_idx = pp_idx;
		__entry->atomic_cnt = atomic_cnt;
	),
	TP_prपूर्णांकk("id=%u, intr=%d, hw=%d, irq=%d, pp=%d, atomic_cnt=%d",
		  __entry->drm_id, __entry->पूर्णांकr_idx, __entry->hw_idx,
		  __entry->irq_idx, __entry->pp_idx, __entry->atomic_cnt)
);

DECLARE_EVENT_CLASS(dpu_drm_obj_ढाँचा,
	TP_PROTO(uपूर्णांक32_t drm_id),
	TP_ARGS(drm_id),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id		)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
	),
	TP_prपूर्णांकk("id=%u", __entry->drm_id)
);
DEFINE_EVENT(dpu_drm_obj_ढाँचा, dpu_enc_atomic_check,
	TP_PROTO(uपूर्णांक32_t drm_id),
	TP_ARGS(drm_id)
);
DEFINE_EVENT(dpu_drm_obj_ढाँचा, dpu_enc_mode_set,
	TP_PROTO(uपूर्णांक32_t drm_id),
	TP_ARGS(drm_id)
);
DEFINE_EVENT(dpu_drm_obj_ढाँचा, dpu_enc_disable,
	TP_PROTO(uपूर्णांक32_t drm_id),
	TP_ARGS(drm_id)
);
DEFINE_EVENT(dpu_drm_obj_ढाँचा, dpu_enc_kickoff,
	TP_PROTO(uपूर्णांक32_t drm_id),
	TP_ARGS(drm_id)
);
DEFINE_EVENT(dpu_drm_obj_ढाँचा, dpu_enc_prepare_kickoff,
	TP_PROTO(uपूर्णांक32_t drm_id),
	TP_ARGS(drm_id)
);
DEFINE_EVENT(dpu_drm_obj_ढाँचा, dpu_enc_prepare_kickoff_reset,
	TP_PROTO(uपूर्णांक32_t drm_id),
	TP_ARGS(drm_id)
);
DEFINE_EVENT(dpu_drm_obj_ढाँचा, dpu_crtc_complete_flip,
	TP_PROTO(uपूर्णांक32_t drm_id),
	TP_ARGS(drm_id)
);
DEFINE_EVENT(dpu_drm_obj_ढाँचा, dpu_crtc_vblank_cb,
	TP_PROTO(uपूर्णांक32_t drm_id),
	TP_ARGS(drm_id)
);
DEFINE_EVENT(dpu_drm_obj_ढाँचा, dpu_crtc_complete_commit,
	TP_PROTO(uपूर्णांक32_t drm_id),
	TP_ARGS(drm_id)
);
DEFINE_EVENT(dpu_drm_obj_ढाँचा, dpu_kms_enc_enable,
	TP_PROTO(uपूर्णांक32_t drm_id),
	TP_ARGS(drm_id)
);
DEFINE_EVENT(dpu_drm_obj_ढाँचा, dpu_kms_commit,
	TP_PROTO(uपूर्णांक32_t drm_id),
	TP_ARGS(drm_id)
);
DEFINE_EVENT(dpu_drm_obj_ढाँचा, dpu_kms_रुको_क्रम_commit_करोne,
	TP_PROTO(uपूर्णांक32_t drm_id),
	TP_ARGS(drm_id)
);
DEFINE_EVENT(dpu_drm_obj_ढाँचा, dpu_crtc_runसमय_resume,
	TP_PROTO(uपूर्णांक32_t drm_id),
	TP_ARGS(drm_id)
);

TRACE_EVENT(dpu_enc_enable,
	TP_PROTO(uपूर्णांक32_t drm_id, पूर्णांक hdisplay, पूर्णांक vdisplay),
	TP_ARGS(drm_id, hdisplay, vdisplay),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id		)
		__field(	पूर्णांक,			hdisplay	)
		__field(	पूर्णांक,			vdisplay	)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->hdisplay = hdisplay;
		__entry->vdisplay = vdisplay;
	),
	TP_prपूर्णांकk("id=%u, mode=%dx%d",
		  __entry->drm_id, __entry->hdisplay, __entry->vdisplay)
);

DECLARE_EVENT_CLASS(dpu_enc_keyval_ढाँचा,
	TP_PROTO(uपूर्णांक32_t drm_id, पूर्णांक val),
	TP_ARGS(drm_id, val),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,	drm_id	)
		__field(	पूर्णांक,		val	)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->val = val;
	),
	TP_prपूर्णांकk("id=%u, val=%d", __entry->drm_id, __entry->val)
);
DEFINE_EVENT(dpu_enc_keyval_ढाँचा, dpu_enc_underrun_cb,
	TP_PROTO(uपूर्णांक32_t drm_id, पूर्णांक count),
	TP_ARGS(drm_id, count)
);
DEFINE_EVENT(dpu_enc_keyval_ढाँचा, dpu_enc_trigger_start,
	TP_PROTO(uपूर्णांक32_t drm_id, पूर्णांक ctl_idx),
	TP_ARGS(drm_id, ctl_idx)
);

TRACE_EVENT(dpu_enc_atomic_check_flags,
	TP_PROTO(uपूर्णांक32_t drm_id, अचिन्हित पूर्णांक flags),
	TP_ARGS(drm_id, flags),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id		)
		__field(	अचिन्हित पूर्णांक,		flags		)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->flags = flags;
	),
	TP_prपूर्णांकk("id=%u, flags=%u",
		  __entry->drm_id, __entry->flags)
);

DECLARE_EVENT_CLASS(dpu_enc_id_enable_ढाँचा,
	TP_PROTO(uपूर्णांक32_t drm_id, bool enable),
	TP_ARGS(drm_id, enable),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id		)
		__field(	bool,			enable		)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->enable = enable;
	),
	TP_prपूर्णांकk("id=%u, enable=%s",
		  __entry->drm_id, __entry->enable ? "true" : "false")
);
DEFINE_EVENT(dpu_enc_id_enable_ढाँचा, dpu_enc_rc_helper,
	TP_PROTO(uपूर्णांक32_t drm_id, bool enable),
	TP_ARGS(drm_id, enable)
);
DEFINE_EVENT(dpu_enc_id_enable_ढाँचा, dpu_enc_vblank_cb,
	TP_PROTO(uपूर्णांक32_t drm_id, bool enable),
	TP_ARGS(drm_id, enable)
);
DEFINE_EVENT(dpu_enc_id_enable_ढाँचा, dpu_enc_frame_event_cb,
	TP_PROTO(uपूर्णांक32_t drm_id, bool enable),
	TP_ARGS(drm_id, enable)
);
DEFINE_EVENT(dpu_enc_id_enable_ढाँचा, dpu_enc_phys_cmd_connect_te,
	TP_PROTO(uपूर्णांक32_t drm_id, bool enable),
	TP_ARGS(drm_id, enable)
);

TRACE_EVENT(dpu_enc_rc,
	TP_PROTO(uपूर्णांक32_t drm_id, u32 sw_event, bool idle_pc_supported,
		 पूर्णांक rc_state, स्थिर अक्षर *stage),
	TP_ARGS(drm_id, sw_event, idle_pc_supported, rc_state, stage),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,	drm_id			)
		__field(	u32,		sw_event		)
		__field(	bool,		idle_pc_supported	)
		__field(	पूर्णांक,		rc_state		)
		__string(	stage_str,	stage			)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->sw_event = sw_event;
		__entry->idle_pc_supported = idle_pc_supported;
		__entry->rc_state = rc_state;
		__assign_str(stage_str, stage);
	),
	TP_prपूर्णांकk("%s: id:%u, sw_event:%d, idle_pc_supported:%s, rc_state:%d",
		  __get_str(stage_str), __entry->drm_id, __entry->sw_event,
		  __entry->idle_pc_supported ? "true" : "false",
		  __entry->rc_state)
);

TRACE_EVENT(dpu_enc_frame_करोne_cb_not_busy,
	TP_PROTO(uपूर्णांक32_t drm_id, u32 event, क्रमागत dpu_पूर्णांकf पूर्णांकf_idx),
	TP_ARGS(drm_id, event, पूर्णांकf_idx),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,	drm_id		)
		__field(	u32,		event		)
		__field(	क्रमागत dpu_पूर्णांकf,	पूर्णांकf_idx	)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->event = event;
		__entry->पूर्णांकf_idx = पूर्णांकf_idx;
	),
	TP_prपूर्णांकk("id=%u, event=%u, intf=%d", __entry->drm_id, __entry->event,
		  __entry->पूर्णांकf_idx)
);

TRACE_EVENT(dpu_enc_frame_करोne_cb,
	TP_PROTO(uपूर्णांक32_t drm_id, अचिन्हित पूर्णांक idx,
		 अचिन्हित दीर्घ frame_busy_mask),
	TP_ARGS(drm_id, idx, frame_busy_mask),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id		)
		__field(	अचिन्हित पूर्णांक,		idx		)
		__field(	अचिन्हित दीर्घ,		frame_busy_mask	)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->idx = idx;
		__entry->frame_busy_mask = frame_busy_mask;
	),
	TP_prपूर्णांकk("id=%u, idx=%u, frame_busy_mask=%lx", __entry->drm_id,
		  __entry->idx, __entry->frame_busy_mask)
);

TRACE_EVENT(dpu_enc_trigger_flush,
	TP_PROTO(uपूर्णांक32_t drm_id, क्रमागत dpu_पूर्णांकf पूर्णांकf_idx,
		 पूर्णांक pending_kickoff_cnt, पूर्णांक ctl_idx, u32 extra_flush_bits,
		 u32 pending_flush_ret),
	TP_ARGS(drm_id, पूर्णांकf_idx, pending_kickoff_cnt, ctl_idx,
		extra_flush_bits, pending_flush_ret),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,	drm_id			)
		__field(	क्रमागत dpu_पूर्णांकf,	पूर्णांकf_idx		)
		__field(	पूर्णांक,		pending_kickoff_cnt	)
		__field(	पूर्णांक,		ctl_idx			)
		__field(	u32,		extra_flush_bits	)
		__field(	u32,		pending_flush_ret	)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->पूर्णांकf_idx = पूर्णांकf_idx;
		__entry->pending_kickoff_cnt = pending_kickoff_cnt;
		__entry->ctl_idx = ctl_idx;
		__entry->extra_flush_bits = extra_flush_bits;
		__entry->pending_flush_ret = pending_flush_ret;
	),
	TP_prपूर्णांकk("id=%u, intf_idx=%d, pending_kickoff_cnt=%d ctl_idx=%d "
		  "extra_flush_bits=0x%x pending_flush_ret=0x%x",
		  __entry->drm_id, __entry->पूर्णांकf_idx,
		  __entry->pending_kickoff_cnt, __entry->ctl_idx,
		  __entry->extra_flush_bits, __entry->pending_flush_ret)
);

DECLARE_EVENT_CLASS(dpu_enc_kसमय_प्रकारemplate,
	TP_PROTO(uपूर्णांक32_t drm_id, kसमय_प्रकार समय),
	TP_ARGS(drm_id, समय),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,	drm_id	)
		__field(	kसमय_प्रकार,	समय	)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->समय = समय;
	),
	TP_prपूर्णांकk("id=%u, time=%lld", __entry->drm_id,
		  kसमय_प्रकारo_ms(__entry->समय))
);
DEFINE_EVENT(dpu_enc_kसमय_प्रकारemplate, dpu_enc_vsync_event_work,
	TP_PROTO(uपूर्णांक32_t drm_id, kसमय_प्रकार समय),
	TP_ARGS(drm_id, समय)
);
DEFINE_EVENT(dpu_enc_kसमय_प्रकारemplate, dpu_enc_early_kickoff,
	TP_PROTO(uपूर्णांक32_t drm_id, kसमय_प्रकार समय),
	TP_ARGS(drm_id, समय)
);

DECLARE_EVENT_CLASS(dpu_id_event_ढाँचा,
	TP_PROTO(uपूर्णांक32_t drm_id, u32 event),
	TP_ARGS(drm_id, event),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,	drm_id	)
		__field(	u32,		event	)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->event = event;
	),
	TP_prपूर्णांकk("id=%u, event=%u", __entry->drm_id, __entry->event)
);
DEFINE_EVENT(dpu_id_event_ढाँचा, dpu_enc_frame_करोne_समयout,
	TP_PROTO(uपूर्णांक32_t drm_id, u32 event),
	TP_ARGS(drm_id, event)
);
DEFINE_EVENT(dpu_id_event_ढाँचा, dpu_crtc_frame_event_cb,
	TP_PROTO(uपूर्णांक32_t drm_id, u32 event),
	TP_ARGS(drm_id, event)
);
DEFINE_EVENT(dpu_id_event_ढाँचा, dpu_crtc_frame_event_करोne,
	TP_PROTO(uपूर्णांक32_t drm_id, u32 event),
	TP_ARGS(drm_id, event)
);
DEFINE_EVENT(dpu_id_event_ढाँचा, dpu_crtc_frame_event_more_pending,
	TP_PROTO(uपूर्णांक32_t drm_id, u32 event),
	TP_ARGS(drm_id, event)
);

TRACE_EVENT(dpu_enc_रुको_event_समयout,
	TP_PROTO(uपूर्णांक32_t drm_id, पूर्णांक32_t hw_id, पूर्णांक rc, s64 समय,
		 s64 expected_समय, पूर्णांक atomic_cnt),
	TP_ARGS(drm_id, hw_id, rc, समय, expected_समय, atomic_cnt),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,	drm_id		)
		__field(	पूर्णांक32_t,	hw_id		)
		__field(	पूर्णांक,		rc		)
		__field(	s64,		समय		)
		__field(	s64,		expected_समय	)
		__field(	पूर्णांक,		atomic_cnt	)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->hw_id = hw_id;
		__entry->rc = rc;
		__entry->समय = समय;
		__entry->expected_समय = expected_समय;
		__entry->atomic_cnt = atomic_cnt;
	),
	TP_prपूर्णांकk("id=%u, hw_id=%d, rc=%d, time=%lld, expected=%lld cnt=%d",
		  __entry->drm_id, __entry->hw_id, __entry->rc, __entry->समय,
		  __entry->expected_समय, __entry->atomic_cnt)
);

TRACE_EVENT(dpu_enc_phys_cmd_irq_ctrl,
	TP_PROTO(uपूर्णांक32_t drm_id, क्रमागत dpu_pingpong pp, bool enable,
		 पूर्णांक refcnt),
	TP_ARGS(drm_id, pp, enable, refcnt),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id	)
		__field(	क्रमागत dpu_pingpong,	pp	)
		__field(	bool,			enable	)
		__field(	पूर्णांक,			refcnt	)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->pp = pp;
		__entry->enable = enable;
		__entry->refcnt = refcnt;
	),
	TP_prपूर्णांकk("id=%u, pp=%d, enable=%s, refcnt=%d", __entry->drm_id,
		  __entry->pp, __entry->enable ? "true" : "false",
		  __entry->refcnt)
);

TRACE_EVENT(dpu_enc_phys_cmd_pp_tx_करोne,
	TP_PROTO(uपूर्णांक32_t drm_id, क्रमागत dpu_pingpong pp, पूर्णांक new_count,
		 u32 event),
	TP_ARGS(drm_id, pp, new_count, event),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id		)
		__field(	क्रमागत dpu_pingpong,	pp		)
		__field(	पूर्णांक,			new_count	)
		__field(	u32,			event		)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->pp = pp;
		__entry->new_count = new_count;
		__entry->event = event;
	),
	TP_prपूर्णांकk("id=%u, pp=%d, new_count=%d, event=%u", __entry->drm_id,
		  __entry->pp, __entry->new_count, __entry->event)
);

TRACE_EVENT(dpu_enc_phys_cmd_pकरोne_समयout,
	TP_PROTO(uपूर्णांक32_t drm_id, क्रमागत dpu_pingpong pp, पूर्णांक समयout_count,
		 पूर्णांक kickoff_count, u32 event),
	TP_ARGS(drm_id, pp, समयout_count, kickoff_count, event),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id		)
		__field(	क्रमागत dpu_pingpong,	pp		)
		__field(	पूर्णांक,			समयout_count	)
		__field(	पूर्णांक,			kickoff_count	)
		__field(	u32,			event		)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->pp = pp;
		__entry->समयout_count = समयout_count;
		__entry->kickoff_count = kickoff_count;
		__entry->event = event;
	),
	TP_prपूर्णांकk("id=%u, pp=%d, timeout_count=%d, kickoff_count=%d, event=%u",
		  __entry->drm_id, __entry->pp, __entry->समयout_count,
		  __entry->kickoff_count, __entry->event)
);

TRACE_EVENT(dpu_enc_phys_vid_post_kickoff,
	TP_PROTO(uपूर्णांक32_t drm_id, क्रमागत dpu_पूर्णांकf पूर्णांकf_idx),
	TP_ARGS(drm_id, पूर्णांकf_idx),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,	drm_id			)
		__field(	क्रमागत dpu_पूर्णांकf,	पूर्णांकf_idx		)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->पूर्णांकf_idx = पूर्णांकf_idx;
	),
	TP_prपूर्णांकk("id=%u, intf_idx=%d", __entry->drm_id, __entry->पूर्णांकf_idx)
);

TRACE_EVENT(dpu_enc_phys_vid_irq_ctrl,
	TP_PROTO(uपूर्णांक32_t drm_id, क्रमागत dpu_पूर्णांकf पूर्णांकf_idx, bool enable,
		 पूर्णांक refcnt),
	TP_ARGS(drm_id, पूर्णांकf_idx, enable, refcnt),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,	drm_id		)
		__field(	क्रमागत dpu_पूर्णांकf,	पूर्णांकf_idx	)
		__field(	bool,		enable		)
		__field(	पूर्णांक,		refcnt		)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->पूर्णांकf_idx = पूर्णांकf_idx;
		__entry->enable = enable;
		__entry->refcnt = refcnt;
	),
	TP_prपूर्णांकk("id=%u, intf_idx=%d enable=%s refcnt=%d", __entry->drm_id,
		  __entry->पूर्णांकf_idx, __entry->enable ? "true" : "false",
		  __entry->drm_id)
);

TRACE_EVENT(dpu_crtc_setup_mixer,
	TP_PROTO(uपूर्णांक32_t crtc_id, uपूर्णांक32_t plane_id,
		 काष्ठा drm_plane_state *state, काष्ठा dpu_plane_state *pstate,
		 uपूर्णांक32_t stage_idx, क्रमागत dpu_sspp sspp, uपूर्णांक32_t pixel_क्रमmat,
		 uपूर्णांक64_t modअगरier),
	TP_ARGS(crtc_id, plane_id, state, pstate, stage_idx, sspp,
		pixel_क्रमmat, modअगरier),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		crtc_id		)
		__field(	uपूर्णांक32_t,		plane_id	)
		__field(	uपूर्णांक32_t,		fb_id		)
		__field_काष्ठा(	काष्ठा drm_rect,	src_rect	)
		__field_काष्ठा(	काष्ठा drm_rect,	dst_rect	)
		__field(	uपूर्णांक32_t,		stage_idx	)
		__field(	क्रमागत dpu_stage,		stage		)
		__field(	क्रमागत dpu_sspp,		sspp		)
		__field(	uपूर्णांक32_t,		multirect_idx	)
		__field(	uपूर्णांक32_t,		multirect_mode	)
		__field(	uपूर्णांक32_t,		pixel_क्रमmat	)
		__field(	uपूर्णांक64_t,		modअगरier	)
	),
	TP_fast_assign(
		__entry->crtc_id = crtc_id;
		__entry->plane_id = plane_id;
		__entry->fb_id = state ? state->fb->base.id : 0;
		__entry->src_rect = drm_plane_state_src(state);
		__entry->dst_rect = drm_plane_state_dest(state);
		__entry->stage_idx = stage_idx;
		__entry->stage = pstate->stage;
		__entry->sspp = sspp;
		__entry->multirect_idx = pstate->multirect_index;
		__entry->multirect_mode = pstate->multirect_mode;
		__entry->pixel_क्रमmat = pixel_क्रमmat;
		__entry->modअगरier = modअगरier;
	),
	TP_prपूर्णांकk("crtc_id:%u plane_id:%u fb_id:%u src:" DRM_RECT_FP_FMT
		  " dst:" DRM_RECT_FMT " stage_idx:%u stage:%d, sspp:%d "
		  "multirect_index:%d multirect_mode:%u pix_format:%u "
		  "modifier:%llu",
		  __entry->crtc_id, __entry->plane_id, __entry->fb_id,
		  DRM_RECT_FP_ARG(&__entry->src_rect),
		  DRM_RECT_ARG(&__entry->dst_rect),
		  __entry->stage_idx, __entry->stage, __entry->sspp,
		  __entry->multirect_idx, __entry->multirect_mode,
		  __entry->pixel_क्रमmat, __entry->modअगरier)
);

TRACE_EVENT(dpu_crtc_setup_lm_bounds,
	TP_PROTO(uपूर्णांक32_t drm_id, पूर्णांक mixer, काष्ठा drm_rect *bounds),
	TP_ARGS(drm_id, mixer, bounds),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id	)
		__field(	पूर्णांक,			mixer	)
		__field_काष्ठा(	काष्ठा drm_rect,	bounds	)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->mixer = mixer;
		__entry->bounds = *bounds;
	),
	TP_prपूर्णांकk("id:%u mixer:%d bounds:" DRM_RECT_FMT, __entry->drm_id,
		  __entry->mixer, DRM_RECT_ARG(&__entry->bounds))
);

TRACE_EVENT(dpu_crtc_vblank_enable,
	TP_PROTO(uपूर्णांक32_t drm_id, uपूर्णांक32_t enc_id, bool enable,
		 काष्ठा dpu_crtc *crtc),
	TP_ARGS(drm_id, enc_id, enable, crtc),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id	)
		__field(	uपूर्णांक32_t,		enc_id	)
		__field(	bool,			enable	)
		__field(	bool,			enabled )
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->enc_id = enc_id;
		__entry->enable = enable;
		__entry->enabled = crtc->enabled;
	),
	TP_prपूर्णांकk("id:%u encoder:%u enable:%s state{enabled:%s}",
		  __entry->drm_id, __entry->enc_id,
		  __entry->enable ? "true" : "false",
		  __entry->enabled ? "true" : "false")
);

DECLARE_EVENT_CLASS(dpu_crtc_enable_ढाँचा,
	TP_PROTO(uपूर्णांक32_t drm_id, bool enable, काष्ठा dpu_crtc *crtc),
	TP_ARGS(drm_id, enable, crtc),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id	)
		__field(	bool,			enable	)
		__field(	bool,			enabled )
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->enable = enable;
		__entry->enabled = crtc->enabled;
	),
	TP_prपूर्णांकk("id:%u enable:%s state{enabled:%s}",
		  __entry->drm_id, __entry->enable ? "true" : "false",
		  __entry->enabled ? "true" : "false")
);
DEFINE_EVENT(dpu_crtc_enable_ढाँचा, dpu_crtc_enable,
	TP_PROTO(uपूर्णांक32_t drm_id, bool enable, काष्ठा dpu_crtc *crtc),
	TP_ARGS(drm_id, enable, crtc)
);
DEFINE_EVENT(dpu_crtc_enable_ढाँचा, dpu_crtc_disable,
	TP_PROTO(uपूर्णांक32_t drm_id, bool enable, काष्ठा dpu_crtc *crtc),
	TP_ARGS(drm_id, enable, crtc)
);
DEFINE_EVENT(dpu_crtc_enable_ढाँचा, dpu_crtc_vblank,
	TP_PROTO(uपूर्णांक32_t drm_id, bool enable, काष्ठा dpu_crtc *crtc),
	TP_ARGS(drm_id, enable, crtc)
);

TRACE_EVENT(dpu_crtc_disable_frame_pending,
	TP_PROTO(uपूर्णांक32_t drm_id, पूर्णांक frame_pending),
	TP_ARGS(drm_id, frame_pending),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id		)
		__field(	पूर्णांक,			frame_pending	)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->frame_pending = frame_pending;
	),
	TP_prपूर्णांकk("id:%u frame_pending:%d", __entry->drm_id,
		  __entry->frame_pending)
);

TRACE_EVENT(dpu_plane_set_scanout,
	TP_PROTO(क्रमागत dpu_sspp index, काष्ठा dpu_hw_fmt_layout *layout,
		 क्रमागत dpu_sspp_multirect_index multirect_index),
	TP_ARGS(index, layout, multirect_index),
	TP_STRUCT__entry(
		__field(	क्रमागत dpu_sspp,			index	)
		__field_काष्ठा(	काष्ठा dpu_hw_fmt_layout,	layout	)
		__field(	क्रमागत dpu_sspp_multirect_index,	multirect_index)
	),
	TP_fast_assign(
		__entry->index = index;
		__entry->layout = *layout;
		__entry->multirect_index = multirect_index;
	),
	TP_prपूर्णांकk("index:%d layout:{%ux%u @ [%u/%u, %u/%u, %u/%u, %u/%u]} "
		  "multirect_index:%d", __entry->index, __entry->layout.width,
		  __entry->layout.height, __entry->layout.plane_addr[0],
		  __entry->layout.plane_size[0],
		  __entry->layout.plane_addr[1],
		  __entry->layout.plane_size[1],
		  __entry->layout.plane_addr[2],
		  __entry->layout.plane_size[2],
		  __entry->layout.plane_addr[3],
		  __entry->layout.plane_size[3], __entry->multirect_index)
);

TRACE_EVENT(dpu_plane_disable,
	TP_PROTO(uपूर्णांक32_t drm_id, bool is_भव, uपूर्णांक32_t multirect_mode),
	TP_ARGS(drm_id, is_भव, multirect_mode),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		drm_id		)
		__field(	bool,			is_भव	)
		__field(	uपूर्णांक32_t,		multirect_mode	)
	),
	TP_fast_assign(
		__entry->drm_id = drm_id;
		__entry->is_भव = is_भव;
		__entry->multirect_mode = multirect_mode;
	),
	TP_prपूर्णांकk("id:%u is_virtual:%s multirect_mode:%u", __entry->drm_id,
		  __entry->is_भव ? "true" : "false",
		  __entry->multirect_mode)
);

DECLARE_EVENT_CLASS(dpu_rm_iter_ढाँचा,
	TP_PROTO(uपूर्णांक32_t id, uपूर्णांक32_t enc_id),
	TP_ARGS(id, enc_id),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		id	)
		__field(	uपूर्णांक32_t,		enc_id	)
	),
	TP_fast_assign(
		__entry->id = id;
		__entry->enc_id = enc_id;
	),
	TP_prपूर्णांकk("id:%d enc_id:%u", __entry->id, __entry->enc_id)
);
DEFINE_EVENT(dpu_rm_iter_ढाँचा, dpu_rm_reserve_पूर्णांकf,
	TP_PROTO(uपूर्णांक32_t id, uपूर्णांक32_t enc_id),
	TP_ARGS(id, enc_id)
);
DEFINE_EVENT(dpu_rm_iter_ढाँचा, dpu_rm_reserve_ctls,
	TP_PROTO(uपूर्णांक32_t id, uपूर्णांक32_t enc_id),
	TP_ARGS(id, enc_id)
);

TRACE_EVENT(dpu_rm_reserve_lms,
	TP_PROTO(uपूर्णांक32_t id, uपूर्णांक32_t enc_id, uपूर्णांक32_t pp_id),
	TP_ARGS(id, enc_id, pp_id),
	TP_STRUCT__entry(
		__field(	uपूर्णांक32_t,		id	)
		__field(	uपूर्णांक32_t,		enc_id	)
		__field(	uपूर्णांक32_t,		pp_id	)
	),
	TP_fast_assign(
		__entry->id = id;
		__entry->enc_id = enc_id;
		__entry->pp_id = pp_id;
	),
	TP_prपूर्णांकk("id:%d enc_id:%u pp_id:%u", __entry->id,
		  __entry->enc_id, __entry->pp_id)
);

TRACE_EVENT(dpu_vbअगर_रुको_xin_halt_fail,
	TP_PROTO(क्रमागत dpu_vbअगर index, u32 xin_id),
	TP_ARGS(index, xin_id),
	TP_STRUCT__entry(
		__field(	क्रमागत dpu_vbअगर,	index	)
		__field(	u32,		xin_id	)
	),
	TP_fast_assign(
		__entry->index = index;
		__entry->xin_id = xin_id;
	),
	TP_prपूर्णांकk("index:%d xin_id:%u", __entry->index, __entry->xin_id)
);

TRACE_EVENT(dpu_pp_connect_ext_te,
	TP_PROTO(क्रमागत dpu_pingpong pp, u32 cfg),
	TP_ARGS(pp, cfg),
	TP_STRUCT__entry(
		__field(	क्रमागत dpu_pingpong,	pp	)
		__field(	u32,			cfg	)
	),
	TP_fast_assign(
		__entry->pp = pp;
		__entry->cfg = cfg;
	),
	TP_prपूर्णांकk("pp:%d cfg:%u", __entry->pp, __entry->cfg)
);

DECLARE_EVENT_CLASS(dpu_core_irq_idx_cnt_ढाँचा,
	TP_PROTO(पूर्णांक irq_idx, पूर्णांक enable_count),
	TP_ARGS(irq_idx, enable_count),
	TP_STRUCT__entry(
		__field(	पूर्णांक,	irq_idx		)
		__field(	पूर्णांक,	enable_count	)
	),
	TP_fast_assign(
		__entry->irq_idx = irq_idx;
		__entry->enable_count = enable_count;
	),
	TP_prपूर्णांकk("irq_idx:%d enable_count:%u", __entry->irq_idx,
		  __entry->enable_count)
);
DEFINE_EVENT(dpu_core_irq_idx_cnt_ढाँचा, dpu_core_irq_enable_idx,
	TP_PROTO(पूर्णांक irq_idx, पूर्णांक enable_count),
	TP_ARGS(irq_idx, enable_count)
);
DEFINE_EVENT(dpu_core_irq_idx_cnt_ढाँचा, dpu_core_irq_disable_idx,
	TP_PROTO(पूर्णांक irq_idx, पूर्णांक enable_count),
	TP_ARGS(irq_idx, enable_count)
);

DECLARE_EVENT_CLASS(dpu_core_irq_callback_ढाँचा,
	TP_PROTO(पूर्णांक irq_idx, काष्ठा dpu_irq_callback *callback),
	TP_ARGS(irq_idx, callback),
	TP_STRUCT__entry(
		__field(	पूर्णांक,				irq_idx	)
		__field(	काष्ठा dpu_irq_callback *,	callback)
	),
	TP_fast_assign(
		__entry->irq_idx = irq_idx;
		__entry->callback = callback;
	),
	TP_prपूर्णांकk("irq_idx:%d callback:%pK", __entry->irq_idx,
		  __entry->callback)
);
DEFINE_EVENT(dpu_core_irq_callback_ढाँचा, dpu_core_irq_रेजिस्टर_callback,
	TP_PROTO(पूर्णांक irq_idx, काष्ठा dpu_irq_callback *callback),
	TP_ARGS(irq_idx, callback)
);
DEFINE_EVENT(dpu_core_irq_callback_ढाँचा, dpu_core_irq_unरेजिस्टर_callback,
	TP_PROTO(पूर्णांक irq_idx, काष्ठा dpu_irq_callback *callback),
	TP_ARGS(irq_idx, callback)
);

TRACE_EVENT(dpu_core_perf_update_clk,
	TP_PROTO(काष्ठा drm_device *dev, bool stop_req, u64 clk_rate),
	TP_ARGS(dev, stop_req, clk_rate),
	TP_STRUCT__entry(
		__string(	dev_name,		dev->unique	)
		__field(	bool,			stop_req	)
		__field(	u64,			clk_rate	)
	),
	TP_fast_assign(
		__assign_str(dev_name, dev->unique);
		__entry->stop_req = stop_req;
		__entry->clk_rate = clk_rate;
	),
	TP_prपूर्णांकk("dev:%s stop_req:%s clk_rate:%llu", __get_str(dev_name),
		  __entry->stop_req ? "true" : "false", __entry->clk_rate)
);

TRACE_EVENT(dpu_hw_ctl_update_pending_flush,
	TP_PROTO(u32 new_bits, u32 pending_mask),
	TP_ARGS(new_bits, pending_mask),
	TP_STRUCT__entry(
		__field(	u32,			new_bits	)
		__field(	u32,			pending_mask	)
	),
	TP_fast_assign(
		__entry->new_bits = new_bits;
		__entry->pending_mask = pending_mask;
	),
	TP_prपूर्णांकk("new=%x existing=%x", __entry->new_bits,
		  __entry->pending_mask)
);

DECLARE_EVENT_CLASS(dpu_hw_ctl_pending_flush_ढाँचा,
	TP_PROTO(u32 pending_mask, u32 ctl_flush),
	TP_ARGS(pending_mask, ctl_flush),
	TP_STRUCT__entry(
		__field(	u32,			pending_mask	)
		__field(	u32,			ctl_flush	)
	),
	TP_fast_assign(
		__entry->pending_mask = pending_mask;
		__entry->ctl_flush = ctl_flush;
	),
	TP_prपूर्णांकk("pending_mask=%x CTL_FLUSH=%x", __entry->pending_mask,
		  __entry->ctl_flush)
);
DEFINE_EVENT(dpu_hw_ctl_pending_flush_ढाँचा, dpu_hw_ctl_clear_pending_flush,
	TP_PROTO(u32 pending_mask, u32 ctl_flush),
	TP_ARGS(pending_mask, ctl_flush)
);
DEFINE_EVENT(dpu_hw_ctl_pending_flush_ढाँचा,
	     dpu_hw_ctl_trigger_pending_flush,
	TP_PROTO(u32 pending_mask, u32 ctl_flush),
	TP_ARGS(pending_mask, ctl_flush)
);
DEFINE_EVENT(dpu_hw_ctl_pending_flush_ढाँचा, dpu_hw_ctl_trigger_prepare,
	TP_PROTO(u32 pending_mask, u32 ctl_flush),
	TP_ARGS(pending_mask, ctl_flush)
);
DEFINE_EVENT(dpu_hw_ctl_pending_flush_ढाँचा, dpu_hw_ctl_trigger_start,
	TP_PROTO(u32 pending_mask, u32 ctl_flush),
	TP_ARGS(pending_mask, ctl_flush)
);

#घोषणा DPU_ATRACE_END(name) trace_tracing_mark_ग_लिखो(current->tgid, name, 0)
#घोषणा DPU_ATRACE_BEGIN(name) trace_tracing_mark_ग_लिखो(current->tgid, name, 1)
#घोषणा DPU_ATRACE_FUNC() DPU_ATRACE_BEGIN(__func__)

#घोषणा DPU_ATRACE_INT(name, value) \
	trace_dpu_trace_counter(current->tgid, name, value)

#पूर्ण_अगर /* _DPU_TRACE_H_ */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#समावेश <trace/define_trace.h>
