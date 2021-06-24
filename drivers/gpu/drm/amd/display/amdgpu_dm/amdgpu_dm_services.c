<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#समावेश <linux/माला.स>
#समावेश <linux/acpi.h>

#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/amdgpu_drm.h>
#समावेश "dm_services.h"
#समावेश "amdgpu.h"
#समावेश "amdgpu_dm.h"
#समावेश "amdgpu_dm_irq.h"
#समावेश "amdgpu_pm.h"
#समावेश "amdgpu_dm_trace.h"

	अचिन्हित दीर्घ दीर्घ
	dm_get_elapse_समय_in_ns(काष्ठा dc_context *ctx,
				 अचिन्हित दीर्घ दीर्घ current_समय_stamp,
				 अचिन्हित दीर्घ दीर्घ last_समय_stamp)
अणु
	वापस current_समय_stamp - last_समय_stamp;
पूर्ण

व्योम dm_perf_trace_बारtamp(स्थिर अक्षर *func_name, अचिन्हित पूर्णांक line, काष्ठा dc_context *ctx)
अणु
	trace_amdgpu_dc_perक्रमmance(ctx->perf_trace->पढ़ो_count,
				    ctx->perf_trace->ग_लिखो_count,
				    &ctx->perf_trace->last_entry_पढ़ो,
				    &ctx->perf_trace->last_entry_ग_लिखो,
				    func_name, line);
पूर्ण

/**** घातer component पूर्णांकerfaces ****/
