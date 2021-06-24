<शैली गुरु>
/*
 * Copyright तऊ 2011-2016 Intel Corporation
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Jike Song <jike.song@पूर्णांकel.com>
 *
 * Contributors:
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 */

#अगर !defined(_GVT_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _GVT_TRACE_H_

#समावेश <linux/types.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <यंत्र/tsc.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM gvt

TRACE_EVENT(spt_alloc,
	TP_PROTO(पूर्णांक id, व्योम *spt, पूर्णांक type, अचिन्हित दीर्घ mfn,
		अचिन्हित दीर्घ gpt_gfn),

	TP_ARGS(id, spt, type, mfn, gpt_gfn),

	TP_STRUCT__entry(
		__field(पूर्णांक, id)
		__field(व्योम *, spt)
		__field(पूर्णांक, type)
		__field(अचिन्हित दीर्घ, mfn)
		__field(अचिन्हित दीर्घ, gpt_gfn)
		),

	TP_fast_assign(
		__entry->id = id;
		__entry->spt = spt;
		__entry->type = type;
		__entry->mfn = mfn;
		__entry->gpt_gfn = gpt_gfn;
	),

	TP_prपूर्णांकk("VM%d [alloc] spt %p type %d mfn 0x%lx gfn 0x%lx\n",
		__entry->id,
		__entry->spt,
		__entry->type,
		__entry->mfn,
		__entry->gpt_gfn)
);

TRACE_EVENT(spt_मुक्त,
	TP_PROTO(पूर्णांक id, व्योम *spt, पूर्णांक type),

	TP_ARGS(id, spt, type),

	TP_STRUCT__entry(
		__field(पूर्णांक, id)
		__field(व्योम *, spt)
		__field(पूर्णांक, type)
		),

	TP_fast_assign(
		__entry->id = id;
		__entry->spt = spt;
		__entry->type = type;
	),

	TP_prपूर्णांकk("VM%u [free] spt %p type %d\n",
		__entry->id,
		__entry->spt,
		__entry->type)
);

#घोषणा MAX_BUF_LEN 256

TRACE_EVENT(gma_index,
	TP_PROTO(स्थिर अक्षर *prefix, अचिन्हित दीर्घ gma,
		अचिन्हित दीर्घ index),

	TP_ARGS(prefix, gma, index),

	TP_STRUCT__entry(
		__array(अक्षर, buf, MAX_BUF_LEN)
	),

	TP_fast_assign(
		snम_लिखो(__entry->buf, MAX_BUF_LEN,
			"%s gma 0x%lx index 0x%lx\n", prefix, gma, index);
	),

	TP_prपूर्णांकk("%s", __entry->buf)
);

TRACE_EVENT(gma_translate,
	TP_PROTO(पूर्णांक id, अक्षर *type, पूर्णांक ring_id, पूर्णांक root_entry_type,
		अचिन्हित दीर्घ gma, अचिन्हित दीर्घ gpa),

	TP_ARGS(id, type, ring_id, root_entry_type, gma, gpa),

	TP_STRUCT__entry(
		__array(अक्षर, buf, MAX_BUF_LEN)
	),

	TP_fast_assign(
		snम_लिखो(__entry->buf, MAX_BUF_LEN,
			"VM%d %s ring %d root_entry_type %d gma 0x%lx -> gpa 0x%lx\n",
			id, type, ring_id, root_entry_type, gma, gpa);
	),

	TP_prपूर्णांकk("%s", __entry->buf)
);

TRACE_EVENT(spt_refcount,
	TP_PROTO(पूर्णांक id, अक्षर *action, व्योम *spt, पूर्णांक beक्रमe, पूर्णांक after),

	TP_ARGS(id, action, spt, beक्रमe, after),

	TP_STRUCT__entry(
		__array(अक्षर, buf, MAX_BUF_LEN)
	),

	TP_fast_assign(
		snम_लिखो(__entry->buf, MAX_BUF_LEN,
			"VM%d [%s] spt %p before %d -> after %d\n",
				id, action, spt, beक्रमe, after);
	),

	TP_prपूर्णांकk("%s", __entry->buf)
);

TRACE_EVENT(spt_change,
	TP_PROTO(पूर्णांक id, अक्षर *action, व्योम *spt, अचिन्हित दीर्घ gfn,
		पूर्णांक type),

	TP_ARGS(id, action, spt, gfn, type),

	TP_STRUCT__entry(
		__array(अक्षर, buf, MAX_BUF_LEN)
	),

	TP_fast_assign(
		snम_लिखो(__entry->buf, MAX_BUF_LEN,
			"VM%d [%s] spt %p gfn 0x%lx type %d\n",
				id, action, spt, gfn, type);
	),

	TP_prपूर्णांकk("%s", __entry->buf)
);

TRACE_EVENT(spt_guest_change,
	TP_PROTO(पूर्णांक id, स्थिर अक्षर *tag, व्योम *spt, पूर्णांक type, u64 v,
		अचिन्हित दीर्घ index),

	TP_ARGS(id, tag, spt, type, v, index),

	TP_STRUCT__entry(
		__array(अक्षर, buf, MAX_BUF_LEN)
	),

	TP_fast_assign(
		snम_लिखो(__entry->buf, MAX_BUF_LEN,
		"VM%d [%s] spt %p type %d entry 0x%llx index 0x%lx\n",
			id, tag, spt, type, v, index);
	),

	TP_prपूर्णांकk("%s", __entry->buf)
);

TRACE_EVENT(oos_change,
	TP_PROTO(पूर्णांक id, स्थिर अक्षर *tag, पूर्णांक page_id, व्योम *gpt, पूर्णांक type),

	TP_ARGS(id, tag, page_id, gpt, type),

	TP_STRUCT__entry(
		__array(अक्षर, buf, MAX_BUF_LEN)
	),

	TP_fast_assign(
		snम_लिखो(__entry->buf, MAX_BUF_LEN,
		"VM%d [oos %s] page id %d gpt %p type %d\n",
			id, tag, page_id, gpt, type);
	),

	TP_prपूर्णांकk("%s", __entry->buf)
);

TRACE_EVENT(oos_sync,
	TP_PROTO(पूर्णांक id, पूर्णांक page_id, व्योम *gpt, पूर्णांक type, u64 v,
		अचिन्हित दीर्घ index),

	TP_ARGS(id, page_id, gpt, type, v, index),

	TP_STRUCT__entry(
		__array(अक्षर, buf, MAX_BUF_LEN)
	),

	TP_fast_assign(
	snम_लिखो(__entry->buf, MAX_BUF_LEN,
	"VM%d [oos sync] page id %d gpt %p type %d entry 0x%llx index 0x%lx\n",
				id, page_id, gpt, type, v, index);
	),

	TP_prपूर्णांकk("%s", __entry->buf)
);

#घोषणा GVT_CMD_STR_LEN 40
TRACE_EVENT(gvt_command,
	TP_PROTO(u8 vgpu_id, u8 ring_id, u32 ip_gma, u32 *cmd_va,
		u32 cmd_len,  u32 buf_type, u32 buf_addr_type,
		व्योम *workload, स्थिर अक्षर *cmd_name),

	TP_ARGS(vgpu_id, ring_id, ip_gma, cmd_va, cmd_len, buf_type,
		buf_addr_type, workload, cmd_name),

	TP_STRUCT__entry(
		__field(u8, vgpu_id)
		__field(u8, ring_id)
		__field(u32, ip_gma)
		__field(u32, buf_type)
		__field(u32, buf_addr_type)
		__field(u32, cmd_len)
		__field(व्योम*, workload)
		__dynamic_array(u32, raw_cmd, cmd_len)
		__array(अक्षर, cmd_name, GVT_CMD_STR_LEN)
	),

	TP_fast_assign(
		__entry->vgpu_id = vgpu_id;
		__entry->ring_id = ring_id;
		__entry->ip_gma = ip_gma;
		__entry->buf_type = buf_type;
		__entry->buf_addr_type = buf_addr_type;
		__entry->cmd_len = cmd_len;
		__entry->workload = workload;
		snम_लिखो(__entry->cmd_name, GVT_CMD_STR_LEN, "%s", cmd_name);
		स_नकल(__get_dynamic_array(raw_cmd), cmd_va, cmd_len * माप(*cmd_va));
	),


	TP_prपूर्णांकk("vgpu%d ring %d: address_type %u, buf_type %u, ip_gma %08x,cmd (name=%s,len=%u,raw cmd=%s), workload=%p\n",
		__entry->vgpu_id,
		__entry->ring_id,
		__entry->buf_addr_type,
		__entry->buf_type,
		__entry->ip_gma,
		__entry->cmd_name,
		__entry->cmd_len,
		__prपूर्णांक_array(__get_dynamic_array(raw_cmd),
			__entry->cmd_len, 4),
		__entry->workload)
);

#घोषणा GVT_TEMP_STR_LEN 10
TRACE_EVENT(ग_लिखो_ir,
	TP_PROTO(पूर्णांक id, अक्षर *reg_name, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक new_val,
		 अचिन्हित पूर्णांक old_val, bool changed),

	TP_ARGS(id, reg_name, reg, new_val, old_val, changed),

	TP_STRUCT__entry(
		__field(पूर्णांक, id)
		__array(अक्षर, buf, GVT_TEMP_STR_LEN)
		__field(अचिन्हित पूर्णांक, reg)
		__field(अचिन्हित पूर्णांक, new_val)
		__field(अचिन्हित पूर्णांक, old_val)
		__field(bool, changed)
	),

	TP_fast_assign(
		__entry->id = id;
		snम_लिखो(__entry->buf, GVT_TEMP_STR_LEN, "%s", reg_name);
		__entry->reg = reg;
		__entry->new_val = new_val;
		__entry->old_val = old_val;
		__entry->changed = changed;
	),

	TP_prपूर्णांकk("VM%u write [%s] %x, new %08x, old %08x, changed %08x\n",
		  __entry->id, __entry->buf, __entry->reg, __entry->new_val,
		  __entry->old_val, __entry->changed)
);

TRACE_EVENT(propagate_event,
	TP_PROTO(पूर्णांक id, स्थिर अक्षर *irq_name, पूर्णांक bit),

	TP_ARGS(id, irq_name, bit),

	TP_STRUCT__entry(
		__field(पूर्णांक, id)
		__array(अक्षर, buf, GVT_TEMP_STR_LEN)
		__field(पूर्णांक, bit)
	),

	TP_fast_assign(
		__entry->id = id;
		snम_लिखो(__entry->buf, GVT_TEMP_STR_LEN, "%s", irq_name);
		__entry->bit = bit;
	),

	TP_prपूर्णांकk("Set bit (%d) for (%s) for vgpu (%d)\n",
		  __entry->bit, __entry->buf, __entry->id)
);

TRACE_EVENT(inject_msi,
	TP_PROTO(पूर्णांक id, अचिन्हित पूर्णांक address, अचिन्हित पूर्णांक data),

	TP_ARGS(id, address, data),

	TP_STRUCT__entry(
		__field(पूर्णांक, id)
		__field(अचिन्हित पूर्णांक, address)
		__field(अचिन्हित पूर्णांक, data)
	),

	TP_fast_assign(
		__entry->id = id;
		__entry->address = address;
		__entry->data = data;
	),

	TP_prपूर्णांकk("vgpu%d:inject msi address %x data %x\n",
		  __entry->id, __entry->address, __entry->data)
);

TRACE_EVENT(render_mmio,
	TP_PROTO(पूर्णांक old_id, पूर्णांक new_id, अक्षर *action, अचिन्हित पूर्णांक reg,
		 अचिन्हित पूर्णांक old_val, अचिन्हित पूर्णांक new_val),

	TP_ARGS(old_id, new_id, action, reg, old_val, new_val),

	TP_STRUCT__entry(
		__field(पूर्णांक, old_id)
		__field(पूर्णांक, new_id)
		__array(अक्षर, buf, GVT_TEMP_STR_LEN)
		__field(अचिन्हित पूर्णांक, reg)
		__field(अचिन्हित पूर्णांक, old_val)
		__field(अचिन्हित पूर्णांक, new_val)
	),

	TP_fast_assign(
		__entry->old_id = old_id;
		__entry->new_id = new_id;
		snम_लिखो(__entry->buf, GVT_TEMP_STR_LEN, "%s", action);
		__entry->reg = reg;
		__entry->old_val = old_val;
		__entry->new_val = new_val;
	),

	TP_prपूर्णांकk("VM%u -> VM%u %s reg %x, old %08x new %08x\n",
		  __entry->old_id, __entry->new_id,
		  __entry->buf, __entry->reg,
		  __entry->old_val, __entry->new_val)
);

#पूर्ण_अगर /* _GVT_TRACE_H_ */

/* This part must be out of protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace
#समावेश <trace/define_trace.h>
