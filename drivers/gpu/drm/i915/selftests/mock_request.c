<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
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
 */

#समावेश "gem/selftests/igt_gem_utils.h"
#समावेश "gt/mock_engine.h"

#समावेश "mock_request.h"

काष्ठा i915_request *
mock_request(काष्ठा पूर्णांकel_context *ce, अचिन्हित दीर्घ delay)
अणु
	काष्ठा i915_request *request;

	/* NB the i915->requests slab cache is enlarged to fit mock_request */
	request = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(request))
		वापस शून्य;

	request->mock.delay = delay;
	वापस request;
पूर्ण

bool mock_cancel_request(काष्ठा i915_request *request)
अणु
	काष्ठा mock_engine *engine =
		container_of(request->engine, typeof(*engine), base);
	bool was_queued;

	spin_lock_irq(&engine->hw_lock);
	was_queued = !list_empty(&request->mock.link);
	list_del_init(&request->mock.link);
	spin_unlock_irq(&engine->hw_lock);

	अगर (was_queued)
		i915_request_unsubmit(request);

	वापस was_queued;
पूर्ण
