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

#घोषणा pr_fmt(fmt) "[TTM] " fmt

#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/tपंचांग/tपंचांग_device.h>

#समावेश "ttm_memory.h"

#घोषणा TTM_MEMORY_ALLOC_RETRIES 4

काष्ठा tपंचांग_mem_global tपंचांग_mem_glob;
EXPORT_SYMBOL(tपंचांग_mem_glob);

काष्ठा tपंचांग_mem_zone अणु
	काष्ठा kobject kobj;
	काष्ठा tपंचांग_mem_global *glob;
	स्थिर अक्षर *name;
	uपूर्णांक64_t zone_mem;
	uपूर्णांक64_t emer_mem;
	uपूर्णांक64_t max_mem;
	uपूर्णांक64_t swap_limit;
	uपूर्णांक64_t used_mem;
पूर्ण;

अटल काष्ठा attribute tपंचांग_mem_sys = अणु
	.name = "zone_memory",
	.mode = S_IRUGO
पूर्ण;
अटल काष्ठा attribute tपंचांग_mem_emer = अणु
	.name = "emergency_memory",
	.mode = S_IRUGO | S_IWUSR
पूर्ण;
अटल काष्ठा attribute tपंचांग_mem_max = अणु
	.name = "available_memory",
	.mode = S_IRUGO | S_IWUSR
पूर्ण;
अटल काष्ठा attribute tपंचांग_mem_swap = अणु
	.name = "swap_limit",
	.mode = S_IRUGO | S_IWUSR
पूर्ण;
अटल काष्ठा attribute tपंचांग_mem_used = अणु
	.name = "used_memory",
	.mode = S_IRUGO
पूर्ण;

अटल व्योम tपंचांग_mem_zone_kobj_release(काष्ठा kobject *kobj)
अणु
	काष्ठा tपंचांग_mem_zone *zone =
		container_of(kobj, काष्ठा tपंचांग_mem_zone, kobj);

	pr_info("Zone %7s: Used memory at exit: %llu KiB\n",
		zone->name, (अचिन्हित दीर्घ दीर्घ)zone->used_mem >> 10);
	kमुक्त(zone);
पूर्ण

अटल sमाप_प्रकार tपंचांग_mem_zone_show(काष्ठा kobject *kobj,
				 काष्ठा attribute *attr,
				 अक्षर *buffer)
अणु
	काष्ठा tपंचांग_mem_zone *zone =
		container_of(kobj, काष्ठा tपंचांग_mem_zone, kobj);
	uपूर्णांक64_t val = 0;

	spin_lock(&zone->glob->lock);
	अगर (attr == &tपंचांग_mem_sys)
		val = zone->zone_mem;
	अन्यथा अगर (attr == &tपंचांग_mem_emer)
		val = zone->emer_mem;
	अन्यथा अगर (attr == &tपंचांग_mem_max)
		val = zone->max_mem;
	अन्यथा अगर (attr == &tपंचांग_mem_swap)
		val = zone->swap_limit;
	अन्यथा अगर (attr == &tपंचांग_mem_used)
		val = zone->used_mem;
	spin_unlock(&zone->glob->lock);

	वापस snम_लिखो(buffer, PAGE_SIZE, "%llu\n",
			(अचिन्हित दीर्घ दीर्घ) val >> 10);
पूर्ण

अटल व्योम tपंचांग_check_swapping(काष्ठा tपंचांग_mem_global *glob);

अटल sमाप_प्रकार tपंचांग_mem_zone_store(काष्ठा kobject *kobj,
				  काष्ठा attribute *attr,
				  स्थिर अक्षर *buffer,
				  माप_प्रकार size)
अणु
	काष्ठा tपंचांग_mem_zone *zone =
		container_of(kobj, काष्ठा tपंचांग_mem_zone, kobj);
	पूर्णांक अक्षरs;
	अचिन्हित दीर्घ val;
	uपूर्णांक64_t val64;

	अक्षरs = माला_पूछो(buffer, "%lu", &val);
	अगर (अक्षरs == 0)
		वापस size;

	val64 = val;
	val64 <<= 10;

	spin_lock(&zone->glob->lock);
	अगर (val64 > zone->zone_mem)
		val64 = zone->zone_mem;
	अगर (attr == &tपंचांग_mem_emer) अणु
		zone->emer_mem = val64;
		अगर (zone->max_mem > val64)
			zone->max_mem = val64;
	पूर्ण अन्यथा अगर (attr == &tपंचांग_mem_max) अणु
		zone->max_mem = val64;
		अगर (zone->emer_mem < val64)
			zone->emer_mem = val64;
	पूर्ण अन्यथा अगर (attr == &tपंचांग_mem_swap)
		zone->swap_limit = val64;
	spin_unlock(&zone->glob->lock);

	tपंचांग_check_swapping(zone->glob);

	वापस size;
पूर्ण

अटल काष्ठा attribute *tपंचांग_mem_zone_attrs[] = अणु
	&tपंचांग_mem_sys,
	&tपंचांग_mem_emer,
	&tपंचांग_mem_max,
	&tपंचांग_mem_swap,
	&tपंचांग_mem_used,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा sysfs_ops tपंचांग_mem_zone_ops = अणु
	.show = &tपंचांग_mem_zone_show,
	.store = &tपंचांग_mem_zone_store
पूर्ण;

अटल काष्ठा kobj_type tपंचांग_mem_zone_kobj_type = अणु
	.release = &tपंचांग_mem_zone_kobj_release,
	.sysfs_ops = &tपंचांग_mem_zone_ops,
	.शेष_attrs = tपंचांग_mem_zone_attrs,
पूर्ण;

अटल काष्ठा attribute tपंचांग_mem_global_lower_mem_limit = अणु
	.name = "lower_mem_limit",
	.mode = S_IRUGO | S_IWUSR
पूर्ण;

अटल sमाप_प्रकार tपंचांग_mem_global_show(काष्ठा kobject *kobj,
				 काष्ठा attribute *attr,
				 अक्षर *buffer)
अणु
	काष्ठा tपंचांग_mem_global *glob =
		container_of(kobj, काष्ठा tपंचांग_mem_global, kobj);
	uपूर्णांक64_t val = 0;

	spin_lock(&glob->lock);
	val = glob->lower_mem_limit;
	spin_unlock(&glob->lock);
	/* convert from number of pages to KB */
	val <<= (PAGE_SHIFT - 10);
	वापस snम_लिखो(buffer, PAGE_SIZE, "%llu\n",
			(अचिन्हित दीर्घ दीर्घ) val);
पूर्ण

अटल sमाप_प्रकार tपंचांग_mem_global_store(काष्ठा kobject *kobj,
				  काष्ठा attribute *attr,
				  स्थिर अक्षर *buffer,
				  माप_प्रकार size)
अणु
	पूर्णांक अक्षरs;
	uपूर्णांक64_t val64;
	अचिन्हित दीर्घ val;
	काष्ठा tपंचांग_mem_global *glob =
		container_of(kobj, काष्ठा tपंचांग_mem_global, kobj);

	अक्षरs = माला_पूछो(buffer, "%lu", &val);
	अगर (अक्षरs == 0)
		वापस size;

	val64 = val;
	/* convert from KB to number of pages */
	val64 >>= (PAGE_SHIFT - 10);

	spin_lock(&glob->lock);
	glob->lower_mem_limit = val64;
	spin_unlock(&glob->lock);

	वापस size;
पूर्ण

अटल काष्ठा attribute *tपंचांग_mem_global_attrs[] = अणु
	&tपंचांग_mem_global_lower_mem_limit,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा sysfs_ops tपंचांग_mem_global_ops = अणु
	.show = &tपंचांग_mem_global_show,
	.store = &tपंचांग_mem_global_store,
पूर्ण;

अटल काष्ठा kobj_type tपंचांग_mem_glob_kobj_type = अणु
	.sysfs_ops = &tपंचांग_mem_global_ops,
	.शेष_attrs = tपंचांग_mem_global_attrs,
पूर्ण;

अटल bool tपंचांग_zones_above_swap_target(काष्ठा tपंचांग_mem_global *glob,
					bool from_wq, uपूर्णांक64_t extra)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा tपंचांग_mem_zone *zone;
	uपूर्णांक64_t target;

	क्रम (i = 0; i < glob->num_zones; ++i) अणु
		zone = glob->zones[i];

		अगर (from_wq)
			target = zone->swap_limit;
		अन्यथा अगर (capable(CAP_SYS_ADMIN))
			target = zone->emer_mem;
		अन्यथा
			target = zone->max_mem;

		target = (extra > target) ? 0ULL : target;

		अगर (zone->used_mem > target)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * At this poपूर्णांक we only support a single shrink callback.
 * Extend this अगर needed, perhaps using a linked list of callbacks.
 * Note that this function is reentrant:
 * many thपढ़ोs may try to swap out at any given समय.
 */

अटल व्योम tपंचांग_shrink(काष्ठा tपंचांग_mem_global *glob, bool from_wq,
			uपूर्णांक64_t extra, काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	पूर्णांक ret;

	spin_lock(&glob->lock);

	जबतक (tपंचांग_zones_above_swap_target(glob, from_wq, extra)) अणु
		spin_unlock(&glob->lock);
		ret = tपंचांग_global_swapout(ctx, GFP_KERNEL);
		spin_lock(&glob->lock);
		अगर (unlikely(ret <= 0))
			अवरोध;
	पूर्ण

	spin_unlock(&glob->lock);
पूर्ण

अटल व्योम tपंचांग_shrink_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = false,
		.no_रुको_gpu = false
	पूर्ण;
	काष्ठा tपंचांग_mem_global *glob =
	    container_of(work, काष्ठा tपंचांग_mem_global, work);

	tपंचांग_shrink(glob, true, 0ULL, &ctx);
पूर्ण

अटल पूर्णांक tपंचांग_mem_init_kernel_zone(काष्ठा tपंचांग_mem_global *glob,
				    स्थिर काष्ठा sysinfo *si)
अणु
	काष्ठा tपंचांग_mem_zone *zone = kzalloc(माप(*zone), GFP_KERNEL);
	uपूर्णांक64_t mem;
	पूर्णांक ret;

	अगर (unlikely(!zone))
		वापस -ENOMEM;

	mem = si->totalram - si->totalhigh;
	mem *= si->mem_unit;

	zone->name = "kernel";
	zone->zone_mem = mem;
	zone->max_mem = mem >> 1;
	zone->emer_mem = (mem >> 1) + (mem >> 2);
	zone->swap_limit = zone->max_mem - (mem >> 3);
	zone->used_mem = 0;
	zone->glob = glob;
	glob->zone_kernel = zone;
	ret = kobject_init_and_add(
		&zone->kobj, &tपंचांग_mem_zone_kobj_type, &glob->kobj, zone->name);
	अगर (unlikely(ret != 0)) अणु
		kobject_put(&zone->kobj);
		वापस ret;
	पूर्ण
	glob->zones[glob->num_zones++] = zone;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
अटल पूर्णांक tपंचांग_mem_init_highmem_zone(काष्ठा tपंचांग_mem_global *glob,
				     स्थिर काष्ठा sysinfo *si)
अणु
	काष्ठा tपंचांग_mem_zone *zone;
	uपूर्णांक64_t mem;
	पूर्णांक ret;

	अगर (si->totalhigh == 0)
		वापस 0;

	zone = kzalloc(माप(*zone), GFP_KERNEL);
	अगर (unlikely(!zone))
		वापस -ENOMEM;

	mem = si->totalram;
	mem *= si->mem_unit;

	zone->name = "highmem";
	zone->zone_mem = mem;
	zone->max_mem = mem >> 1;
	zone->emer_mem = (mem >> 1) + (mem >> 2);
	zone->swap_limit = zone->max_mem - (mem >> 3);
	zone->used_mem = 0;
	zone->glob = glob;
	glob->zone_highmem = zone;
	ret = kobject_init_and_add(
		&zone->kobj, &tपंचांग_mem_zone_kobj_type, &glob->kobj, "%s",
		zone->name);
	अगर (unlikely(ret != 0)) अणु
		kobject_put(&zone->kobj);
		वापस ret;
	पूर्ण
	glob->zones[glob->num_zones++] = zone;
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक tपंचांग_mem_init_dma32_zone(काष्ठा tपंचांग_mem_global *glob,
				   स्थिर काष्ठा sysinfo *si)
अणु
	काष्ठा tपंचांग_mem_zone *zone = kzalloc(माप(*zone), GFP_KERNEL);
	uपूर्णांक64_t mem;
	पूर्णांक ret;

	अगर (unlikely(!zone))
		वापस -ENOMEM;

	mem = si->totalram;
	mem *= si->mem_unit;

	/**
	 * No special dma32 zone needed.
	 */

	अगर (mem <= ((uपूर्णांक64_t) 1ULL << 32)) अणु
		kमुक्त(zone);
		वापस 0;
	पूर्ण

	/*
	 * Limit max dma32 memory to 4GB क्रम now
	 * until we can figure out how big this
	 * zone really is.
	 */

	mem = ((uपूर्णांक64_t) 1ULL << 32);
	zone->name = "dma32";
	zone->zone_mem = mem;
	zone->max_mem = mem >> 1;
	zone->emer_mem = (mem >> 1) + (mem >> 2);
	zone->swap_limit = zone->max_mem - (mem >> 3);
	zone->used_mem = 0;
	zone->glob = glob;
	glob->zone_dma32 = zone;
	ret = kobject_init_and_add(
		&zone->kobj, &tपंचांग_mem_zone_kobj_type, &glob->kobj, zone->name);
	अगर (unlikely(ret != 0)) अणु
		kobject_put(&zone->kobj);
		वापस ret;
	पूर्ण
	glob->zones[glob->num_zones++] = zone;
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक tपंचांग_mem_global_init(काष्ठा tपंचांग_mem_global *glob, काष्ठा device *dev)
अणु
	काष्ठा sysinfo si;
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा tपंचांग_mem_zone *zone;

	spin_lock_init(&glob->lock);
	glob->swap_queue = create_singlethपढ़ो_workqueue("ttm_swap");
	INIT_WORK(&glob->work, tपंचांग_shrink_work);

	ret = kobject_init_and_add(&glob->kobj, &tपंचांग_mem_glob_kobj_type,
				   &dev->kobj, "memory_accounting");
	अगर (unlikely(ret != 0)) अणु
		kobject_put(&glob->kobj);
		वापस ret;
	पूर्ण

	si_meminfo(&si);

	/* set it as 0 by शेष to keep original behavior of OOM */
	glob->lower_mem_limit = 0;

	ret = tपंचांग_mem_init_kernel_zone(glob, &si);
	अगर (unlikely(ret != 0))
		जाओ out_no_zone;
#अगर_घोषित CONFIG_HIGHMEM
	ret = tपंचांग_mem_init_highmem_zone(glob, &si);
	अगर (unlikely(ret != 0))
		जाओ out_no_zone;
#अन्यथा
	ret = tपंचांग_mem_init_dma32_zone(glob, &si);
	अगर (unlikely(ret != 0))
		जाओ out_no_zone;
#पूर्ण_अगर
	क्रम (i = 0; i < glob->num_zones; ++i) अणु
		zone = glob->zones[i];
		pr_info("Zone %7s: Available graphics memory: %llu KiB\n",
			zone->name, (अचिन्हित दीर्घ दीर्घ)zone->max_mem >> 10);
	पूर्ण
	वापस 0;
out_no_zone:
	tपंचांग_mem_global_release(glob);
	वापस ret;
पूर्ण

व्योम tपंचांग_mem_global_release(काष्ठा tपंचांग_mem_global *glob)
अणु
	काष्ठा tपंचांग_mem_zone *zone;
	अचिन्हित पूर्णांक i;

	flush_workqueue(glob->swap_queue);
	destroy_workqueue(glob->swap_queue);
	glob->swap_queue = शून्य;
	क्रम (i = 0; i < glob->num_zones; ++i) अणु
		zone = glob->zones[i];
		kobject_del(&zone->kobj);
		kobject_put(&zone->kobj);
	पूर्ण
	kobject_del(&glob->kobj);
	kobject_put(&glob->kobj);
	स_रखो(glob, 0, माप(*glob));
पूर्ण

अटल व्योम tपंचांग_check_swapping(काष्ठा tपंचांग_mem_global *glob)
अणु
	bool needs_swapping = false;
	अचिन्हित पूर्णांक i;
	काष्ठा tपंचांग_mem_zone *zone;

	spin_lock(&glob->lock);
	क्रम (i = 0; i < glob->num_zones; ++i) अणु
		zone = glob->zones[i];
		अगर (zone->used_mem > zone->swap_limit) अणु
			needs_swapping = true;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&glob->lock);

	अगर (unlikely(needs_swapping))
		(व्योम)queue_work(glob->swap_queue, &glob->work);

पूर्ण

अटल व्योम tपंचांग_mem_global_मुक्त_zone(काष्ठा tपंचांग_mem_global *glob,
				     काष्ठा tपंचांग_mem_zone *single_zone,
				     uपूर्णांक64_t amount)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा tपंचांग_mem_zone *zone;

	spin_lock(&glob->lock);
	क्रम (i = 0; i < glob->num_zones; ++i) अणु
		zone = glob->zones[i];
		अगर (single_zone && zone != single_zone)
			जारी;
		zone->used_mem -= amount;
	पूर्ण
	spin_unlock(&glob->lock);
पूर्ण

व्योम tपंचांग_mem_global_मुक्त(काष्ठा tपंचांग_mem_global *glob,
			 uपूर्णांक64_t amount)
अणु
	वापस tपंचांग_mem_global_मुक्त_zone(glob, glob->zone_kernel, amount);
पूर्ण
EXPORT_SYMBOL(tपंचांग_mem_global_मुक्त);

/*
 * check अगर the available mem is under lower memory limit
 *
 * a. अगर no swap disk at all or मुक्त swap space is under swap_mem_limit
 * but available प्रणाली mem is bigger than sys_mem_limit, allow TTM
 * allocation;
 *
 * b. अगर the available प्रणाली mem is less than sys_mem_limit but मुक्त
 * swap disk is bigger than swap_mem_limit, allow TTM allocation.
 */
bool
tपंचांग_check_under_lowerlimit(काष्ठा tपंचांग_mem_global *glob,
			uपूर्णांक64_t num_pages,
			काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	पूर्णांक64_t available;

	/* We allow over commit during suspend */
	अगर (ctx->क्रमce_alloc)
		वापस false;

	available = get_nr_swap_pages() + si_mem_available();
	available -= num_pages;
	अगर (available < glob->lower_mem_limit)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक tपंचांग_mem_global_reserve(काष्ठा tपंचांग_mem_global *glob,
				  काष्ठा tपंचांग_mem_zone *single_zone,
				  uपूर्णांक64_t amount, bool reserve)
अणु
	uपूर्णांक64_t limit;
	पूर्णांक ret = -ENOMEM;
	अचिन्हित पूर्णांक i;
	काष्ठा tपंचांग_mem_zone *zone;

	spin_lock(&glob->lock);
	क्रम (i = 0; i < glob->num_zones; ++i) अणु
		zone = glob->zones[i];
		अगर (single_zone && zone != single_zone)
			जारी;

		limit = (capable(CAP_SYS_ADMIN)) ?
			zone->emer_mem : zone->max_mem;

		अगर (zone->used_mem > limit)
			जाओ out_unlock;
	पूर्ण

	अगर (reserve) अणु
		क्रम (i = 0; i < glob->num_zones; ++i) अणु
			zone = glob->zones[i];
			अगर (single_zone && zone != single_zone)
				जारी;
			zone->used_mem += amount;
		पूर्ण
	पूर्ण

	ret = 0;
out_unlock:
	spin_unlock(&glob->lock);
	tपंचांग_check_swapping(glob);

	वापस ret;
पूर्ण


अटल पूर्णांक tपंचांग_mem_global_alloc_zone(काष्ठा tपंचांग_mem_global *glob,
				     काष्ठा tपंचांग_mem_zone *single_zone,
				     uपूर्णांक64_t memory,
				     काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	पूर्णांक count = TTM_MEMORY_ALLOC_RETRIES;

	जबतक (unlikely(tपंचांग_mem_global_reserve(glob,
					       single_zone,
					       memory, true)
			!= 0)) अणु
		अगर (ctx->no_रुको_gpu)
			वापस -ENOMEM;
		अगर (unlikely(count-- == 0))
			वापस -ENOMEM;
		tपंचांग_shrink(glob, false, memory + (memory >> 2) + 16, ctx);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tपंचांग_mem_global_alloc(काष्ठा tपंचांग_mem_global *glob, uपूर्णांक64_t memory,
			 काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	/**
	 * Normal allocations of kernel memory are रेजिस्टरed in
	 * the kernel zone.
	 */

	वापस tपंचांग_mem_global_alloc_zone(glob, glob->zone_kernel, memory, ctx);
पूर्ण
EXPORT_SYMBOL(tपंचांग_mem_global_alloc);

पूर्णांक tपंचांग_mem_global_alloc_page(काष्ठा tपंचांग_mem_global *glob,
			      काष्ठा page *page, uपूर्णांक64_t size,
			      काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	काष्ठा tपंचांग_mem_zone *zone = शून्य;

	/**
	 * Page allocations may be registed in a single zone
	 * only अगर highmem or !dma32.
	 */

#अगर_घोषित CONFIG_HIGHMEM
	अगर (PageHighMem(page) && glob->zone_highmem != शून्य)
		zone = glob->zone_highmem;
#अन्यथा
	अगर (glob->zone_dma32 && page_to_pfn(page) > 0x00100000UL)
		zone = glob->zone_kernel;
#पूर्ण_अगर
	वापस tपंचांग_mem_global_alloc_zone(glob, zone, size, ctx);
पूर्ण

व्योम tपंचांग_mem_global_मुक्त_page(काष्ठा tपंचांग_mem_global *glob, काष्ठा page *page,
			      uपूर्णांक64_t size)
अणु
	काष्ठा tपंचांग_mem_zone *zone = शून्य;

#अगर_घोषित CONFIG_HIGHMEM
	अगर (PageHighMem(page) && glob->zone_highmem != शून्य)
		zone = glob->zone_highmem;
#अन्यथा
	अगर (glob->zone_dma32 && page_to_pfn(page) > 0x00100000UL)
		zone = glob->zone_kernel;
#पूर्ण_अगर
	tपंचांग_mem_global_मुक्त_zone(glob, zone, size);
पूर्ण

माप_प्रकार tपंचांग_round_pot(माप_प्रकार size)
अणु
	अगर ((size & (size - 1)) == 0)
		वापस size;
	अन्यथा अगर (size > PAGE_SIZE)
		वापस PAGE_ALIGN(size);
	अन्यथा अणु
		माप_प्रकार पंचांगp_size = 4;

		जबतक (पंचांगp_size < size)
			पंचांगp_size <<= 1;

		वापस पंचांगp_size;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_round_pot);
