<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**************************************************************************
 *
 * Copyright (c) 2006-2009 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/
/*
 * Authors: Thomas Hellstrom <thellstrom-at-vmware-करोt-com>
 *          Keith Packard.
 */

#घोषणा pr_fmt(fmt) "[TTM] " fmt

#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/agp.h>

काष्ठा tपंचांग_agp_backend अणु
	काष्ठा tपंचांग_tt tपंचांग;
	काष्ठा agp_memory *mem;
	काष्ठा agp_bridge_data *bridge;
पूर्ण;

पूर्णांक tपंचांग_agp_bind(काष्ठा tपंचांग_tt *tपंचांग, काष्ठा tपंचांग_resource *bo_mem)
अणु
	काष्ठा tपंचांग_agp_backend *agp_be = container_of(tपंचांग, काष्ठा tपंचांग_agp_backend, tपंचांग);
	काष्ठा page *dummy_पढ़ो_page = tपंचांग_glob.dummy_पढ़ो_page;
	काष्ठा drm_mm_node *node = bo_mem->mm_node;
	काष्ठा agp_memory *mem;
	पूर्णांक ret, cached = tपंचांग->caching == tपंचांग_cached;
	अचिन्हित i;

	अगर (agp_be->mem)
		वापस 0;

	mem = agp_allocate_memory(agp_be->bridge, tपंचांग->num_pages, AGP_USER_MEMORY);
	अगर (unlikely(mem == शून्य))
		वापस -ENOMEM;

	mem->page_count = 0;
	क्रम (i = 0; i < tपंचांग->num_pages; i++) अणु
		काष्ठा page *page = tपंचांग->pages[i];

		अगर (!page)
			page = dummy_पढ़ो_page;

		mem->pages[mem->page_count++] = page;
	पूर्ण
	agp_be->mem = mem;

	mem->is_flushed = 1;
	mem->type = (cached) ? AGP_USER_CACHED_MEMORY : AGP_USER_MEMORY;

	ret = agp_bind_memory(mem, node->start);
	अगर (ret)
		pr_err("AGP Bind memory failed\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL(tपंचांग_agp_bind);

व्योम tपंचांग_agp_unbind(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा tपंचांग_agp_backend *agp_be = container_of(tपंचांग, काष्ठा tपंचांग_agp_backend, tपंचांग);

	अगर (agp_be->mem) अणु
		अगर (agp_be->mem->is_bound) अणु
			agp_unbind_memory(agp_be->mem);
			वापस;
		पूर्ण
		agp_मुक्त_memory(agp_be->mem);
		agp_be->mem = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tपंचांग_agp_unbind);

bool tपंचांग_agp_is_bound(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा tपंचांग_agp_backend *agp_be = container_of(tपंचांग, काष्ठा tपंचांग_agp_backend, tपंचांग);

	अगर (!tपंचांग)
		वापस false;

	वापस (agp_be->mem != शून्य);
पूर्ण
EXPORT_SYMBOL(tपंचांग_agp_is_bound);

व्योम tपंचांग_agp_destroy(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा tपंचांग_agp_backend *agp_be = container_of(tपंचांग, काष्ठा tपंचांग_agp_backend, tपंचांग);

	अगर (agp_be->mem)
		tपंचांग_agp_unbind(tपंचांग);
	tपंचांग_tt_fini(tपंचांग);
	kमुक्त(agp_be);
पूर्ण
EXPORT_SYMBOL(tपंचांग_agp_destroy);

काष्ठा tपंचांग_tt *tपंचांग_agp_tt_create(काष्ठा tपंचांग_buffer_object *bo,
				 काष्ठा agp_bridge_data *bridge,
				 uपूर्णांक32_t page_flags)
अणु
	काष्ठा tपंचांग_agp_backend *agp_be;

	agp_be = kदो_स्मृति(माप(*agp_be), GFP_KERNEL);
	अगर (!agp_be)
		वापस शून्य;

	agp_be->mem = शून्य;
	agp_be->bridge = bridge;

	अगर (tपंचांग_tt_init(&agp_be->tपंचांग, bo, page_flags, tपंचांग_ग_लिखो_combined)) अणु
		kमुक्त(agp_be);
		वापस शून्य;
	पूर्ण

	वापस &agp_be->tपंचांग;
पूर्ण
EXPORT_SYMBOL(tपंचांग_agp_tt_create);
