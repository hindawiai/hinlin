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
 */

#अगर_अघोषित __GVT_DEBUG_H__
#घोषणा __GVT_DEBUG_H__

#घोषणा gvt_err(fmt, args...) \
	pr_err("gvt: "fmt, ##args)

#घोषणा gvt_vgpu_err(fmt, args...)					\
करो अणु									\
	अगर (IS_ERR_OR_शून्य(vgpu))					\
		pr_err("gvt: "fmt, ##args);			\
	अन्यथा								\
		pr_err("gvt: vgpu %d: "fmt, vgpu->id, ##args);\
पूर्ण जबतक (0)

#घोषणा gvt_dbg_core(fmt, args...) \
	pr_debug("gvt: core: "fmt, ##args)

#घोषणा gvt_dbg_irq(fmt, args...) \
	pr_debug("gvt: irq: "fmt, ##args)

#घोषणा gvt_dbg_mm(fmt, args...) \
	pr_debug("gvt: mm: "fmt, ##args)

#घोषणा gvt_dbg_mmio(fmt, args...) \
	pr_debug("gvt: mmio: "fmt, ##args)

#घोषणा gvt_dbg_dpy(fmt, args...) \
	pr_debug("gvt: dpy: "fmt, ##args)

#घोषणा gvt_dbg_el(fmt, args...) \
	pr_debug("gvt: el: "fmt, ##args)

#घोषणा gvt_dbg_sched(fmt, args...) \
	pr_debug("gvt: sched: "fmt, ##args)

#घोषणा gvt_dbg_render(fmt, args...) \
	pr_debug("gvt: render: "fmt, ##args)

#घोषणा gvt_dbg_cmd(fmt, args...) \
	pr_debug("gvt: cmd: "fmt, ##args)

#पूर्ण_अगर
