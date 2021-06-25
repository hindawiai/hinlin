<शैली गुरु>
/*
 * AGPGART driver backend routines.
 * Copyright (C) 2004 Silicon Graphics, Inc.
 * Copyright (C) 2002-2003 Dave Jones.
 * Copyright (C) 1999 Jeff Harपंचांगann.
 * Copyright (C) 1999 Precision Insight, Inc.
 * Copyright (C) 1999 Xi Graphics, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * JEFF HARTMANN, DAVE JONES, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * TODO:
 * - Allocate more than order 0 pages to aव्योम too much linear map splitting.
 */
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/pm.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/agpgart.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/पन.स>
#समावेश "agp.h"

/* Due to XFree86 brain-damage, we can't go to 1.0 until they
 * fix some real stupidity. It's only by chance we can bump
 * past 0.99 at all due to some boolean logic error. */
#घोषणा AGPGART_VERSION_MAJOR 0
#घोषणा AGPGART_VERSION_MINOR 103
अटल स्थिर काष्ठा agp_version agp_current_version =
अणु
	.major = AGPGART_VERSION_MAJOR,
	.minor = AGPGART_VERSION_MINOR,
पूर्ण;

काष्ठा agp_bridge_data *(*agp_find_bridge)(काष्ठा pci_dev *) =
	&agp_generic_find_bridge;

काष्ठा agp_bridge_data *agp_bridge;
LIST_HEAD(agp_bridges);
EXPORT_SYMBOL(agp_bridge);
EXPORT_SYMBOL(agp_bridges);
EXPORT_SYMBOL(agp_find_bridge);

/**
 *	agp_backend_acquire  -  attempt to acquire an agp backend.
 *
 */
काष्ठा agp_bridge_data *agp_backend_acquire(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge;

	bridge = agp_find_bridge(pdev);

	अगर (!bridge)
		वापस शून्य;

	अगर (atomic_पढ़ो(&bridge->agp_in_use))
		वापस शून्य;
	atomic_inc(&bridge->agp_in_use);
	वापस bridge;
पूर्ण
EXPORT_SYMBOL(agp_backend_acquire);


/**
 *	agp_backend_release  -  release the lock on the agp backend.
 *
 *	The caller must insure that the graphics aperture translation table
 *	is पढ़ो क्रम use by another entity.
 *
 *	(Ensure that all memory it bound is unbound.)
 */
व्योम agp_backend_release(काष्ठा agp_bridge_data *bridge)
अणु

	अगर (bridge)
		atomic_dec(&bridge->agp_in_use);
पूर्ण
EXPORT_SYMBOL(agp_backend_release);


अटल स्थिर काष्ठा अणु पूर्णांक mem, agp; पूर्ण maxes_table[] = अणु
	अणु0, 0पूर्ण,
	अणु32, 4पूर्ण,
	अणु64, 28पूर्ण,
	अणु128, 96पूर्ण,
	अणु256, 204पूर्ण,
	अणु512, 440पूर्ण,
	अणु1024, 942पूर्ण,
	अणु2048, 1920पूर्ण,
	अणु4096, 3932पूर्ण
पूर्ण;

अटल पूर्णांक agp_find_max(व्योम)
अणु
	दीर्घ memory, index, result;

#अगर PAGE_SHIFT < 20
	memory = totalram_pages() >> (20 - PAGE_SHIFT);
#अन्यथा
	memory = totalram_pages() << (PAGE_SHIFT - 20);
#पूर्ण_अगर
	index = 1;

	जबतक ((memory > maxes_table[index].mem) && (index < 8))
		index++;

	result = maxes_table[index - 1].agp +
	   ( (memory - maxes_table[index - 1].mem)  *
	     (maxes_table[index].agp - maxes_table[index - 1].agp)) /
	   (maxes_table[index].mem - maxes_table[index - 1].mem);

	result = result << (20 - PAGE_SHIFT);
	वापस result;
पूर्ण


अटल पूर्णांक agp_backend_initialize(काष्ठा agp_bridge_data *bridge)
अणु
	पूर्णांक size_value, rc, got_gatt=0, got_keylist=0;

	bridge->max_memory_agp = agp_find_max();
	bridge->version = &agp_current_version;

	अगर (bridge->driver->needs_scratch_page) अणु
		काष्ठा page *page = bridge->driver->agp_alloc_page(bridge);

		अगर (!page) अणु
			dev_err(&bridge->dev->dev,
				"can't get memory for scratch page\n");
			वापस -ENOMEM;
		पूर्ण

		bridge->scratch_page_page = page;
		bridge->scratch_page_dma = page_to_phys(page);

		bridge->scratch_page = bridge->driver->mask_memory(bridge,
						   bridge->scratch_page_dma, 0);
	पूर्ण

	size_value = bridge->driver->fetch_size();
	अगर (size_value == 0) अणु
		dev_err(&bridge->dev->dev, "can't determine aperture size\n");
		rc = -EINVAL;
		जाओ err_out;
	पूर्ण
	अगर (bridge->driver->create_gatt_table(bridge)) अणु
		dev_err(&bridge->dev->dev,
			"can't get memory for graphics translation table\n");
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण
	got_gatt = 1;

	bridge->key_list = vzalloc(PAGE_SIZE * 4);
	अगर (bridge->key_list == शून्य) अणु
		dev_err(&bridge->dev->dev,
			"can't allocate memory for key lists\n");
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण
	got_keylist = 1;

	/* FIXME vदो_स्मृति'd memory not guaranteed contiguous */

	अगर (bridge->driver->configure()) अणु
		dev_err(&bridge->dev->dev, "error configuring host chipset\n");
		rc = -EINVAL;
		जाओ err_out;
	पूर्ण
	INIT_LIST_HEAD(&bridge->mapped_list);
	spin_lock_init(&bridge->mapped_lock);

	वापस 0;

err_out:
	अगर (bridge->driver->needs_scratch_page) अणु
		काष्ठा page *page = bridge->scratch_page_page;

		bridge->driver->agp_destroy_page(page, AGP_PAGE_DESTROY_UNMAP);
		bridge->driver->agp_destroy_page(page, AGP_PAGE_DESTROY_FREE);
	पूर्ण
	अगर (got_gatt)
		bridge->driver->मुक्त_gatt_table(bridge);
	अगर (got_keylist) अणु
		vमुक्त(bridge->key_list);
		bridge->key_list = शून्य;
	पूर्ण
	वापस rc;
पूर्ण

/* cannot be __निकास b/c as it could be called from __init code */
अटल व्योम agp_backend_cleanup(काष्ठा agp_bridge_data *bridge)
अणु
	अगर (bridge->driver->cleanup)
		bridge->driver->cleanup();
	अगर (bridge->driver->मुक्त_gatt_table)
		bridge->driver->मुक्त_gatt_table(bridge);

	vमुक्त(bridge->key_list);
	bridge->key_list = शून्य;

	अगर (bridge->driver->agp_destroy_page &&
	    bridge->driver->needs_scratch_page) अणु
		काष्ठा page *page = bridge->scratch_page_page;

		bridge->driver->agp_destroy_page(page, AGP_PAGE_DESTROY_UNMAP);
		bridge->driver->agp_destroy_page(page, AGP_PAGE_DESTROY_FREE);
	पूर्ण
पूर्ण

/* When we हटाओ the global variable agp_bridge from all drivers
 * then agp_alloc_bridge and agp_generic_find_bridge need to be updated
 */

काष्ठा agp_bridge_data *agp_alloc_bridge(व्योम)
अणु
	काष्ठा agp_bridge_data *bridge;

	bridge = kzalloc(माप(*bridge), GFP_KERNEL);
	अगर (!bridge)
		वापस शून्य;

	atomic_set(&bridge->agp_in_use, 0);
	atomic_set(&bridge->current_memory_agp, 0);

	अगर (list_empty(&agp_bridges))
		agp_bridge = bridge;

	वापस bridge;
पूर्ण
EXPORT_SYMBOL(agp_alloc_bridge);


व्योम agp_put_bridge(काष्ठा agp_bridge_data *bridge)
अणु
        kमुक्त(bridge);

        अगर (list_empty(&agp_bridges))
                agp_bridge = शून्य;
पूर्ण
EXPORT_SYMBOL(agp_put_bridge);


पूर्णांक agp_add_bridge(काष्ठा agp_bridge_data *bridge)
अणु
	पूर्णांक error;

	अगर (agp_off) अणु
		error = -ENODEV;
		जाओ err_put_bridge;
	पूर्ण

	अगर (!bridge->dev) अणु
		prपूर्णांकk (KERN_DEBUG PFX "Erk, registering with no pci_dev!\n");
		error = -EINVAL;
		जाओ err_put_bridge;
	पूर्ण

	/* Grab reference on the chipset driver. */
	अगर (!try_module_get(bridge->driver->owner)) अणु
		dev_info(&bridge->dev->dev, "can't lock chipset driver\n");
		error = -EINVAL;
		जाओ err_put_bridge;
	पूर्ण

	error = agp_backend_initialize(bridge);
	अगर (error) अणु
		dev_info(&bridge->dev->dev,
			 "agp_backend_initialize() failed\n");
		जाओ err_out;
	पूर्ण

	अगर (list_empty(&agp_bridges)) अणु
		error = agp_frontend_initialize();
		अगर (error) अणु
			dev_info(&bridge->dev->dev,
				 "agp_frontend_initialize() failed\n");
			जाओ frontend_err;
		पूर्ण

		dev_info(&bridge->dev->dev, "AGP aperture is %dM @ 0x%lx\n",
			 bridge->driver->fetch_size(), bridge->gart_bus_addr);

	पूर्ण

	list_add(&bridge->list, &agp_bridges);
	वापस 0;

frontend_err:
	agp_backend_cleanup(bridge);
err_out:
	module_put(bridge->driver->owner);
err_put_bridge:
	agp_put_bridge(bridge);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(agp_add_bridge);


व्योम agp_हटाओ_bridge(काष्ठा agp_bridge_data *bridge)
अणु
	agp_backend_cleanup(bridge);
	list_del(&bridge->list);
	अगर (list_empty(&agp_bridges))
		agp_frontend_cleanup();
	module_put(bridge->driver->owner);
पूर्ण
EXPORT_SYMBOL_GPL(agp_हटाओ_bridge);

पूर्णांक agp_off;
पूर्णांक agp_try_unsupported_boot;
EXPORT_SYMBOL(agp_off);
EXPORT_SYMBOL(agp_try_unsupported_boot);

अटल पूर्णांक __init agp_init(व्योम)
अणु
	अगर (!agp_off)
		prपूर्णांकk(KERN_INFO "Linux agpgart interface v%d.%d\n",
			AGPGART_VERSION_MAJOR, AGPGART_VERSION_MINOR);
	वापस 0;
पूर्ण

अटल व्योम __निकास agp_निकास(व्योम)
अणु
पूर्ण

#अगर_अघोषित MODULE
अटल __init पूर्णांक agp_setup(अक्षर *s)
अणु
	अगर (!म_भेद(s,"off"))
		agp_off = 1;
	अगर (!म_भेद(s,"try_unsupported"))
		agp_try_unsupported_boot = 1;
	वापस 1;
पूर्ण
__setup("agp=", agp_setup);
#पूर्ण_अगर

MODULE_AUTHOR("Dave Jones, Jeff Hartmann");
MODULE_DESCRIPTION("AGP GART driver");
MODULE_LICENSE("GPL and additional rights");
MODULE_ALIAS_MISCDEV(AGPGART_MINOR);

module_init(agp_init);
module_निकास(agp_निकास);

