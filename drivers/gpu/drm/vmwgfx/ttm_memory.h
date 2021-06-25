<शैली गुरु>
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

#अगर_अघोषित TTM_MEMORY_H
#घोषणा TTM_MEMORY_H

#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bug.h>
#समावेश <linux/रुको.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kobject.h>
#समावेश <linux/mm.h>

#समावेश <drm/tपंचांग/tपंचांग_bo_api.h>

/**
 * काष्ठा tपंचांग_mem_global - Global memory accounting काष्ठाure.
 *
 * @shrink: A single callback to shrink TTM memory usage. Extend this
 * to a linked list to be able to handle multiple callbacks when needed.
 * @swap_queue: A workqueue to handle shrinking in low memory situations. We
 * need a separate workqueue since it will spend a lot of समय रुकोing
 * क्रम the GPU, and this will otherwise block other workqueue tasks(?)
 * At this poपूर्णांक we use only a single-thपढ़ोed workqueue.
 * @work: The workqueue callback क्रम the shrink queue.
 * @lock: Lock to protect the @shrink - and the memory accounting members,
 * that is, essentially the whole काष्ठाure with some exceptions.
 * @lower_mem_limit: include lower limit of swap space and lower limit of
 * प्रणाली memory.
 * @zones: Array of poपूर्णांकers to accounting zones.
 * @num_zones: Number of populated entries in the @zones array.
 * @zone_kernel: Poपूर्णांकer to the kernel zone.
 * @zone_highmem: Poपूर्णांकer to the highmem zone अगर there is one.
 * @zone_dma32: Poपूर्णांकer to the dma32 zone अगर there is one.
 *
 * Note that this काष्ठाure is not per device. It should be global क्रम all
 * graphics devices.
 */

#घोषणा TTM_MEM_MAX_ZONES 2
काष्ठा tपंचांग_mem_zone;
बाह्य काष्ठा tपंचांग_mem_global अणु
	काष्ठा kobject kobj;
	काष्ठा workqueue_काष्ठा *swap_queue;
	काष्ठा work_काष्ठा work;
	spinlock_t lock;
	uपूर्णांक64_t lower_mem_limit;
	काष्ठा tपंचांग_mem_zone *zones[TTM_MEM_MAX_ZONES];
	अचिन्हित पूर्णांक num_zones;
	काष्ठा tपंचांग_mem_zone *zone_kernel;
#अगर_घोषित CONFIG_HIGHMEM
	काष्ठा tपंचांग_mem_zone *zone_highmem;
#अन्यथा
	काष्ठा tपंचांग_mem_zone *zone_dma32;
#पूर्ण_अगर
पूर्ण tपंचांग_mem_glob;

पूर्णांक tपंचांग_mem_global_init(काष्ठा tपंचांग_mem_global *glob, काष्ठा device *dev);
व्योम tपंचांग_mem_global_release(काष्ठा tपंचांग_mem_global *glob);
पूर्णांक tपंचांग_mem_global_alloc(काष्ठा tपंचांग_mem_global *glob, uपूर्णांक64_t memory,
			 काष्ठा tपंचांग_operation_ctx *ctx);
व्योम tपंचांग_mem_global_मुक्त(काष्ठा tपंचांग_mem_global *glob, uपूर्णांक64_t amount);
पूर्णांक tपंचांग_mem_global_alloc_page(काष्ठा tपंचांग_mem_global *glob,
			      काष्ठा page *page, uपूर्णांक64_t size,
			      काष्ठा tपंचांग_operation_ctx *ctx);
व्योम tपंचांग_mem_global_मुक्त_page(काष्ठा tपंचांग_mem_global *glob,
			      काष्ठा page *page, uपूर्णांक64_t size);
माप_प्रकार tपंचांग_round_pot(माप_प्रकार size);
bool tपंचांग_check_under_lowerlimit(काष्ठा tपंचांग_mem_global *glob, uपूर्णांक64_t num_pages,
				काष्ठा tपंचांग_operation_ctx *ctx);
#पूर्ण_अगर
