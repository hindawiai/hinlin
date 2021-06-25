<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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

#समावेश <linux/slab.h>

#समावेश "dm_services.h"
#समावेश "dm_helpers.h"
#समावेश "core_types.h"

/*******************************************************************************
 * Private functions
 ******************************************************************************/

अटल व्योम dc_sink_deकाष्ठा(काष्ठा dc_sink *sink)
अणु
	अगर (sink->dc_container_id) अणु
		kमुक्त(sink->dc_container_id);
		sink->dc_container_id = शून्य;
	पूर्ण
पूर्ण

अटल bool dc_sink_स्थिरruct(काष्ठा dc_sink *sink, स्थिर काष्ठा dc_sink_init_data *init_params)
अणु

	काष्ठा dc_link *link = init_params->link;

	अगर (!link)
		वापस false;

	sink->sink_संकेत = init_params->sink_संकेत;
	sink->link = link;
	sink->ctx = link->ctx;
	sink->करोngle_max_pix_clk = init_params->करोngle_max_pix_clk;
	sink->converter_disable_audio = init_params->converter_disable_audio;
	sink->dc_container_id = शून्य;
	sink->sink_id = init_params->link->ctx->dc_sink_id_count;
	// increment dc_sink_id_count because we करोn't want two sinks with same ID
	// unless they are actually the same
	init_params->link->ctx->dc_sink_id_count++;

	वापस true;
पूर्ण

/*******************************************************************************
 * Public functions
 ******************************************************************************/

व्योम dc_sink_retain(काष्ठा dc_sink *sink)
अणु
	kref_get(&sink->refcount);
पूर्ण

अटल व्योम dc_sink_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा dc_sink *sink = container_of(kref, काष्ठा dc_sink, refcount);
	dc_sink_deकाष्ठा(sink);
	kमुक्त(sink);
पूर्ण

व्योम dc_sink_release(काष्ठा dc_sink *sink)
अणु
	kref_put(&sink->refcount, dc_sink_मुक्त);
पूर्ण

काष्ठा dc_sink *dc_sink_create(स्थिर काष्ठा dc_sink_init_data *init_params)
अणु
	काष्ठा dc_sink *sink = kzalloc(माप(*sink), GFP_KERNEL);

	अगर (शून्य == sink)
		जाओ alloc_fail;

	अगर (false == dc_sink_स्थिरruct(sink, init_params))
		जाओ स्थिरruct_fail;

	kref_init(&sink->refcount);

	वापस sink;

स्थिरruct_fail:
	kमुक्त(sink);

alloc_fail:
	वापस शून्य;
पूर्ण

/*******************************************************************************
 * Protected functions - visible only inside of DC (not visible in DM)
 ******************************************************************************/
