<शैली गुरु>
/*
 * SRAM protect-exec region helper functions
 *
 * Copyright (C) 2017 Texas Instruments Incorporated - https://www.ti.com/
 *	Dave Gerlach
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/device.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/mm.h>
#समावेश <linux/sram.h>

#समावेश <यंत्र/fncpy.h>
#समावेश <यंत्र/set_memory.h>

#समावेश "sram.h"

अटल DEFINE_MUTEX(exec_pool_list_mutex);
अटल LIST_HEAD(exec_pool_list);

पूर्णांक sram_check_protect_exec(काष्ठा sram_dev *sram, काष्ठा sram_reserve *block,
			    काष्ठा sram_partition *part)
अणु
	अचिन्हित दीर्घ base = (अचिन्हित दीर्घ)part->base;
	अचिन्हित दीर्घ end = base + block->size;

	अगर (!PAGE_ALIGNED(base) || !PAGE_ALIGNED(end)) अणु
		dev_err(sram->dev,
			"SRAM pool marked with 'protect-exec' is not page aligned and will not be created.\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sram_add_protect_exec(काष्ठा sram_partition *part)
अणु
	mutex_lock(&exec_pool_list_mutex);
	list_add_tail(&part->list, &exec_pool_list);
	mutex_unlock(&exec_pool_list_mutex);

	वापस 0;
पूर्ण

/**
 * sram_exec_copy - copy data to a रक्षित executable region of sram
 *
 * @pool: काष्ठा gen_pool retrieved that is part of this sram
 * @dst: Destination address क्रम the copy, that must be inside pool
 * @src: Source address क्रम the data to copy
 * @size: Size of copy to perक्रमm, which starting from dst, must reside in pool
 *
 * Return: Address क्रम copied data that can safely be called through function
 *	   poपूर्णांकer, or शून्य अगर problem.
 *
 * This helper function allows sram driver to act as central control location
 * of 'protect-exec' pools which are normal sram pools but are always set
 * पढ़ो-only and executable except when copying data to them, at which poपूर्णांक
 * they are set to पढ़ो-ग_लिखो non-executable, to make sure no memory is
 * ग_लिखोable and executable at the same समय. This region must be page-aligned
 * and is checked during probe, otherwise page attribute manipulation would
 * not be possible. Care must be taken to only call the वापसed address as
 * dst address is not guaranteed to be safely callable.
 *
 * NOTE: This function uses the fncpy macro to move code to the executable
 * region. Some architectures have strict requirements क्रम relocating
 * executable code, so fncpy is a macro that must be defined by any arch
 * making use of this functionality that guarantees a safe copy of exec
 * data and वापसs a safe address that can be called as a C function
 * poपूर्णांकer.
 */
व्योम *sram_exec_copy(काष्ठा gen_pool *pool, व्योम *dst, व्योम *src,
		     माप_प्रकार size)
अणु
	काष्ठा sram_partition *part = शून्य, *p;
	अचिन्हित दीर्घ base;
	पूर्णांक pages;
	व्योम *dst_cpy;
	पूर्णांक ret;

	mutex_lock(&exec_pool_list_mutex);
	list_क्रम_each_entry(p, &exec_pool_list, list) अणु
		अगर (p->pool == pool)
			part = p;
	पूर्ण
	mutex_unlock(&exec_pool_list_mutex);

	अगर (!part)
		वापस शून्य;

	अगर (!gen_pool_has_addr(pool, (अचिन्हित दीर्घ)dst, size))
		वापस शून्य;

	base = (अचिन्हित दीर्घ)part->base;
	pages = PAGE_ALIGN(size) / PAGE_SIZE;

	mutex_lock(&part->lock);

	ret = set_memory_nx((अचिन्हित दीर्घ)base, pages);
	अगर (ret)
		जाओ error_out;
	ret = set_memory_rw((अचिन्हित दीर्घ)base, pages);
	अगर (ret)
		जाओ error_out;

	dst_cpy = fncpy(dst, src, size);

	ret = set_memory_ro((अचिन्हित दीर्घ)base, pages);
	अगर (ret)
		जाओ error_out;
	ret = set_memory_x((अचिन्हित दीर्घ)base, pages);
	अगर (ret)
		जाओ error_out;

	mutex_unlock(&part->lock);

	वापस dst_cpy;

error_out:
	mutex_unlock(&part->lock);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(sram_exec_copy);
