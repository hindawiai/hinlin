<शैली गुरु>
/*
 * Legacy: Generic DRM Buffer Management
 *
 * Copyright 1999, 2000 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All Rights Reserved.
 *
 * Author: Rickard E. (Rik) Faith <faith@valinux.com>
 * Author: Gareth Hughes <gareth@valinux.com>
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/export.h>
#समावेश <linux/log2.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/nospec.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/shmparam.h>

#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_legacy.h"


अटल काष्ठा drm_map_list *drm_find_matching_map(काष्ठा drm_device *dev,
						  काष्ठा drm_local_map *map)
अणु
	काष्ठा drm_map_list *entry;

	list_क्रम_each_entry(entry, &dev->maplist, head) अणु
		/*
		 * Because the kernel-userspace ABI is fixed at a 32-bit offset
		 * जबतक PCI resources may live above that, we only compare the
		 * lower 32 bits of the map offset क्रम maps of type
		 * _DRM_FRAMEBUFFER or _DRM_REGISTERS.
		 * It is assumed that अगर a driver have more than one resource
		 * of each type, the lower 32 bits are dअगरferent.
		 */
		अगर (!entry->map ||
		    map->type != entry->map->type ||
		    entry->master != dev->master)
			जारी;
		चयन (map->type) अणु
		हाल _DRM_SHM:
			अगर (map->flags != _DRM_CONTAINS_LOCK)
				अवरोध;
			वापस entry;
		हाल _DRM_REGISTERS:
		हाल _DRM_FRAME_BUFFER:
			अगर ((entry->map->offset & 0xffffffff) ==
			    (map->offset & 0xffffffff))
				वापस entry;
			अवरोध;
		शेष: /* Make gcc happy */
			;
		पूर्ण
		अगर (entry->map->offset == map->offset)
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक drm_map_handle(काष्ठा drm_device *dev, काष्ठा drm_hash_item *hash,
			  अचिन्हित दीर्घ user_token, पूर्णांक hashed_handle, पूर्णांक shm)
अणु
	पूर्णांक use_hashed_handle, shअगरt;
	अचिन्हित दीर्घ add;

#अगर (BITS_PER_LONG == 64)
	use_hashed_handle = ((user_token & 0xFFFFFFFF00000000UL) || hashed_handle);
#या_अगर (BITS_PER_LONG == 32)
	use_hashed_handle = hashed_handle;
#अन्यथा
#त्रुटि Unsupported दीर्घ size. Neither 64 nor 32 bits.
#पूर्ण_अगर

	अगर (!use_hashed_handle) अणु
		पूर्णांक ret;

		hash->key = user_token >> PAGE_SHIFT;
		ret = drm_ht_insert_item(&dev->map_hash, hash);
		अगर (ret != -EINVAL)
			वापस ret;
	पूर्ण

	shअगरt = 0;
	add = DRM_MAP_HASH_OFFSET >> PAGE_SHIFT;
	अगर (shm && (SHMLBA > PAGE_SIZE)) अणु
		पूर्णांक bits = ilog2(SHMLBA >> PAGE_SHIFT) + 1;

		/* For shared memory, we have to preserve the SHMLBA
		 * bits of the eventual vma->vm_pgoff value during
		 * mmap().  Otherwise we run पूर्णांकo cache aliasing problems
		 * on some platक्रमms.  On these platक्रमms, the pgoff of
		 * a mmap() request is used to pick a suitable भव
		 * address क्रम the mmap() region such that it will not
		 * cause cache aliasing problems.
		 *
		 * Thereक्रमe, make sure the SHMLBA relevant bits of the
		 * hash value we use are equal to those in the original
		 * kernel भव address.
		 */
		shअगरt = bits;
		add |= ((user_token >> PAGE_SHIFT) & ((1UL << bits) - 1UL));
	पूर्ण

	वापस drm_ht_just_insert_please(&dev->map_hash, hash,
					 user_token, 32 - PAGE_SHIFT - 3,
					 shअगरt, add);
पूर्ण

/*
 * Core function to create a range of memory available क्रम mapping by a
 * non-root process.
 *
 * Adjusts the memory offset to its असलolute value according to the mapping
 * type.  Adds the map to the map list drm_device::maplist. Adds MTRR's where
 * applicable and अगर supported by the kernel.
 */
अटल पूर्णांक drm_addmap_core(काष्ठा drm_device *dev, resource_माप_प्रकार offset,
			   अचिन्हित पूर्णांक size, क्रमागत drm_map_type type,
			   क्रमागत drm_map_flags flags,
			   काष्ठा drm_map_list **maplist)
अणु
	काष्ठा drm_local_map *map;
	काष्ठा drm_map_list *list;
	अचिन्हित दीर्घ user_token;
	पूर्णांक ret;

	map = kदो_स्मृति(माप(*map), GFP_KERNEL);
	अगर (!map)
		वापस -ENOMEM;

	map->offset = offset;
	map->size = size;
	map->flags = flags;
	map->type = type;

	/* Only allow shared memory to be removable since we only keep enough
	 * book keeping inक्रमmation about shared memory to allow क्रम removal
	 * when processes विभाजन.
	 */
	अगर ((map->flags & _DRM_REMOVABLE) && map->type != _DRM_SHM) अणु
		kमुक्त(map);
		वापस -EINVAL;
	पूर्ण
	DRM_DEBUG("offset = 0x%08llx, size = 0x%08lx, type = %d\n",
		  (अचिन्हित दीर्घ दीर्घ)map->offset, map->size, map->type);

	/* page-align _DRM_SHM maps. They are allocated here so there is no security
	 * hole created by that and it works around various broken drivers that use
	 * a non-aligned quantity to map the SAREA. --BenH
	 */
	अगर (map->type == _DRM_SHM)
		map->size = PAGE_ALIGN(map->size);

	अगर ((map->offset & (~(resource_माप_प्रकार)PAGE_MASK)) || (map->size & (~PAGE_MASK))) अणु
		kमुक्त(map);
		वापस -EINVAL;
	पूर्ण
	map->mtrr = -1;
	map->handle = शून्य;

	चयन (map->type) अणु
	हाल _DRM_REGISTERS:
	हाल _DRM_FRAME_BUFFER:
#अगर !defined(__sparc__) && !defined(__alpha__) && !defined(__ia64__) && !defined(__घातerpc64__) && !defined(__x86_64__) && !defined(__arm__)
		अगर (map->offset + (map->size-1) < map->offset ||
		    map->offset < virt_to_phys(high_memory)) अणु
			kमुक्त(map);
			वापस -EINVAL;
		पूर्ण
#पूर्ण_अगर
		/* Some drivers preinitialize some maps, without the X Server
		 * needing to be aware of it.  Thereक्रमe, we just वापस success
		 * when the server tries to create a duplicate map.
		 */
		list = drm_find_matching_map(dev, map);
		अगर (list != शून्य) अणु
			अगर (list->map->size != map->size) अणु
				DRM_DEBUG("Matching maps of type %d with "
					  "mismatched sizes, (%ld vs %ld)\n",
					  map->type, map->size,
					  list->map->size);
				list->map->size = map->size;
			पूर्ण

			kमुक्त(map);
			*maplist = list;
			वापस 0;
		पूर्ण

		अगर (map->type == _DRM_FRAME_BUFFER ||
		    (map->flags & _DRM_WRITE_COMBINING)) अणु
			map->mtrr =
				arch_phys_wc_add(map->offset, map->size);
		पूर्ण
		अगर (map->type == _DRM_REGISTERS) अणु
			अगर (map->flags & _DRM_WRITE_COMBINING)
				map->handle = ioremap_wc(map->offset,
							 map->size);
			अन्यथा
				map->handle = ioremap(map->offset, map->size);
			अगर (!map->handle) अणु
				kमुक्त(map);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		अवरोध;
	हाल _DRM_SHM:
		list = drm_find_matching_map(dev, map);
		अगर (list != शून्य) अणु
			अगर (list->map->size != map->size) अणु
				DRM_DEBUG("Matching maps of type %d with "
					  "mismatched sizes, (%ld vs %ld)\n",
					  map->type, map->size, list->map->size);
				list->map->size = map->size;
			पूर्ण

			kमुक्त(map);
			*maplist = list;
			वापस 0;
		पूर्ण
		map->handle = vदो_स्मृति_user(map->size);
		DRM_DEBUG("%lu %d %p\n",
			  map->size, order_base_2(map->size), map->handle);
		अगर (!map->handle) अणु
			kमुक्त(map);
			वापस -ENOMEM;
		पूर्ण
		map->offset = (अचिन्हित दीर्घ)map->handle;
		अगर (map->flags & _DRM_CONTAINS_LOCK) अणु
			/* Prevent a 2nd X Server from creating a 2nd lock */
			अगर (dev->master->lock.hw_lock != शून्य) अणु
				vमुक्त(map->handle);
				kमुक्त(map);
				वापस -EBUSY;
			पूर्ण
			dev->sigdata.lock = dev->master->lock.hw_lock = map->handle;	/* Poपूर्णांकer to lock */
		पूर्ण
		अवरोध;
	हाल _DRM_AGP: अणु
		काष्ठा drm_agp_mem *entry;
		पूर्णांक valid = 0;

		अगर (!dev->agp) अणु
			kमुक्त(map);
			वापस -EINVAL;
		पूर्ण
#अगर_घोषित __alpha__
		map->offset += dev->hose->mem_space->start;
#पूर्ण_अगर
		/* In some हालs (i810 driver), user space may have alपढ़ोy
		 * added the AGP base itself, because dev->agp->base previously
		 * only got set during AGP enable.  So, only add the base
		 * address अगर the map's offset isn't alपढ़ोy within the
		 * aperture.
		 */
		अगर (map->offset < dev->agp->base ||
		    map->offset > dev->agp->base +
		    dev->agp->agp_info.aper_size * 1024 * 1024 - 1) अणु
			map->offset += dev->agp->base;
		पूर्ण
		map->mtrr = dev->agp->agp_mtrr;	/* क्रम geपंचांगap */

		/* This assumes the DRM is in total control of AGP space.
		 * It's not always the हाल as AGP can be in the control
		 * of user space (i.e. i810 driver). So this loop will get
		 * skipped and we द्विगुन check that dev->agp->memory is
		 * actually set as well as being invalid beक्रमe EPERM'ing
		 */
		list_क्रम_each_entry(entry, &dev->agp->memory, head) अणु
			अगर ((map->offset >= entry->bound) &&
			    (map->offset + map->size <= entry->bound + entry->pages * PAGE_SIZE)) अणु
				valid = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!list_empty(&dev->agp->memory) && !valid) अणु
			kमुक्त(map);
			वापस -EPERM;
		पूर्ण
		DRM_DEBUG("AGP offset = 0x%08llx, size = 0x%08lx\n",
			  (अचिन्हित दीर्घ दीर्घ)map->offset, map->size);

		अवरोध;
	पूर्ण
	हाल _DRM_SCATTER_GATHER:
		अगर (!dev->sg) अणु
			kमुक्त(map);
			वापस -EINVAL;
		पूर्ण
		map->offset += (अचिन्हित दीर्घ)dev->sg->भव;
		अवरोध;
	हाल _DRM_CONSISTENT:
		/* dma_addr_t is 64bit on i386 with CONFIG_HIGHMEM64G,
		 * As we're limiting the address to 2^32-1 (or less),
		 * casting it करोwn to 32 bits is no problem, but we
		 * need to poपूर्णांक to a 64bit variable first. */
		map->handle = dma_alloc_coherent(dev->dev,
						 map->size,
						 &map->offset,
						 GFP_KERNEL);
		अगर (!map->handle) अणु
			kमुक्त(map);
			वापस -ENOMEM;
		पूर्ण
		अवरोध;
	शेष:
		kमुक्त(map);
		वापस -EINVAL;
	पूर्ण

	list = kzalloc(माप(*list), GFP_KERNEL);
	अगर (!list) अणु
		अगर (map->type == _DRM_REGISTERS)
			iounmap(map->handle);
		kमुक्त(map);
		वापस -EINVAL;
	पूर्ण
	list->map = map;

	mutex_lock(&dev->काष्ठा_mutex);
	list_add(&list->head, &dev->maplist);

	/* Assign a 32-bit handle */
	/* We करो it here so that dev->काष्ठा_mutex protects the increment */
	user_token = (map->type == _DRM_SHM) ? (अचिन्हित दीर्घ)map->handle :
		map->offset;
	ret = drm_map_handle(dev, &list->hash, user_token, 0,
			     (map->type == _DRM_SHM));
	अगर (ret) अणु
		अगर (map->type == _DRM_REGISTERS)
			iounmap(map->handle);
		kमुक्त(map);
		kमुक्त(list);
		mutex_unlock(&dev->काष्ठा_mutex);
		वापस ret;
	पूर्ण

	list->user_token = list->hash.key << PAGE_SHIFT;
	mutex_unlock(&dev->काष्ठा_mutex);

	अगर (!(map->flags & _DRM_DRIVER))
		list->master = dev->master;
	*maplist = list;
	वापस 0;
पूर्ण

पूर्णांक drm_legacy_addmap(काष्ठा drm_device *dev, resource_माप_प्रकार offset,
		      अचिन्हित पूर्णांक size, क्रमागत drm_map_type type,
		      क्रमागत drm_map_flags flags, काष्ठा drm_local_map **map_ptr)
अणु
	काष्ठा drm_map_list *list;
	पूर्णांक rc;

	rc = drm_addmap_core(dev, offset, size, type, flags, &list);
	अगर (!rc)
		*map_ptr = list->map;
	वापस rc;
पूर्ण
EXPORT_SYMBOL(drm_legacy_addmap);

काष्ठा drm_local_map *drm_legacy_findmap(काष्ठा drm_device *dev,
					 अचिन्हित पूर्णांक token)
अणु
	काष्ठा drm_map_list *_entry;

	list_क्रम_each_entry(_entry, &dev->maplist, head)
		अगर (_entry->user_token == token)
			वापस _entry->map;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drm_legacy_findmap);

/*
 * Ioctl to specअगरy a range of memory that is available क्रम mapping by a
 * non-root process.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg poपूर्णांकer to a drm_map काष्ठाure.
 * \लeturn zero on success or a negative value on error.
 *
 */
पूर्णांक drm_legacy_addmap_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_map *map = data;
	काष्ठा drm_map_list *maplist;
	पूर्णांक err;

	अगर (!(capable(CAP_SYS_ADMIN) || map->type == _DRM_AGP || map->type == _DRM_SHM))
		वापस -EPERM;

	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	err = drm_addmap_core(dev, map->offset, map->size, map->type,
			      map->flags, &maplist);

	अगर (err)
		वापस err;

	/* aव्योम a warning on 64-bit, this casting isn't very nice, but the API is set so too late */
	map->handle = (व्योम *)(अचिन्हित दीर्घ)maplist->user_token;

	/*
	 * It appears that there are no users of this value whatsoever --
	 * drmAddMap just discards it.  Let's not encourage its use.
	 * (Keeping drm_addmap_core's वापसed mtrr value would be wrong --
	 *  it's not a real mtrr index anymore.)
	 */
	map->mtrr = -1;

	वापस 0;
पूर्ण

/*
 * Get a mapping inक्रमmation.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument, poपूर्णांकing to a drm_map काष्ठाure.
 *
 * \लeturn zero on success or a negative number on failure.
 *
 * Searches क्रम the mapping with the specअगरied offset and copies its inक्रमmation
 * पूर्णांकo userspace
 */
पूर्णांक drm_legacy_geपंचांगap_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_map *map = data;
	काष्ठा drm_map_list *r_list = शून्य;
	काष्ठा list_head *list;
	पूर्णांक idx;
	पूर्णांक i;

	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	idx = map->offset;
	अगर (idx < 0)
		वापस -EINVAL;

	i = 0;
	mutex_lock(&dev->काष्ठा_mutex);
	list_क्रम_each(list, &dev->maplist) अणु
		अगर (i == idx) अणु
			r_list = list_entry(list, काष्ठा drm_map_list, head);
			अवरोध;
		पूर्ण
		i++;
	पूर्ण
	अगर (!r_list || !r_list->map) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		वापस -EINVAL;
	पूर्ण

	map->offset = r_list->map->offset;
	map->size = r_list->map->size;
	map->type = r_list->map->type;
	map->flags = r_list->map->flags;
	map->handle = (व्योम *)(अचिन्हित दीर्घ) r_list->user_token;
	map->mtrr = arch_phys_wc_index(r_list->map->mtrr);

	mutex_unlock(&dev->काष्ठा_mutex);

	वापस 0;
पूर्ण

/*
 * Remove a map निजी from list and deallocate resources अगर the mapping
 * isn't in use.
 *
 * Searches the map on drm_device::maplist, हटाओs it from the list, see अगर
 * it's being used, and free any associated resource (such as MTRR's) if it's not
 * being on use.
 *
 * \sa drm_legacy_addmap
 */
पूर्णांक drm_legacy_rmmap_locked(काष्ठा drm_device *dev, काष्ठा drm_local_map *map)
अणु
	काष्ठा drm_map_list *r_list = शून्य, *list_t;
	पूर्णांक found = 0;
	काष्ठा drm_master *master;

	/* Find the list entry क्रम the map and हटाओ it */
	list_क्रम_each_entry_safe(r_list, list_t, &dev->maplist, head) अणु
		अगर (r_list->map == map) अणु
			master = r_list->master;
			list_del(&r_list->head);
			drm_ht_हटाओ_key(&dev->map_hash,
					  r_list->user_token >> PAGE_SHIFT);
			kमुक्त(r_list);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस -EINVAL;

	चयन (map->type) अणु
	हाल _DRM_REGISTERS:
		iounmap(map->handle);
		fallthrough;
	हाल _DRM_FRAME_BUFFER:
		arch_phys_wc_del(map->mtrr);
		अवरोध;
	हाल _DRM_SHM:
		vमुक्त(map->handle);
		अगर (master) अणु
			अगर (dev->sigdata.lock == master->lock.hw_lock)
				dev->sigdata.lock = शून्य;
			master->lock.hw_lock = शून्य;   /* SHM हटाओd */
			master->lock.file_priv = शून्य;
			wake_up_पूर्णांकerruptible_all(&master->lock.lock_queue);
		पूर्ण
		अवरोध;
	हाल _DRM_AGP:
	हाल _DRM_SCATTER_GATHER:
		अवरोध;
	हाल _DRM_CONSISTENT:
		dma_मुक्त_coherent(dev->dev,
				  map->size,
				  map->handle,
				  map->offset);
		अवरोध;
	पूर्ण
	kमुक्त(map);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_legacy_rmmap_locked);

व्योम drm_legacy_rmmap(काष्ठा drm_device *dev, काष्ठा drm_local_map *map)
अणु
	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस;

	mutex_lock(&dev->काष्ठा_mutex);
	drm_legacy_rmmap_locked(dev, map);
	mutex_unlock(&dev->काष्ठा_mutex);
पूर्ण
EXPORT_SYMBOL(drm_legacy_rmmap);

व्योम drm_legacy_master_rmmaps(काष्ठा drm_device *dev, काष्ठा drm_master *master)
अणु
	काष्ठा drm_map_list *r_list, *list_temp;

	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस;

	mutex_lock(&dev->काष्ठा_mutex);
	list_क्रम_each_entry_safe(r_list, list_temp, &dev->maplist, head) अणु
		अगर (r_list->master == master) अणु
			drm_legacy_rmmap_locked(dev, r_list->map);
			r_list = शून्य;
		पूर्ण
	पूर्ण
	mutex_unlock(&dev->काष्ठा_mutex);
पूर्ण

व्योम drm_legacy_rmmaps(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_map_list *r_list, *list_temp;

	list_क्रम_each_entry_safe(r_list, list_temp, &dev->maplist, head)
		drm_legacy_rmmap(dev, r_list->map);
पूर्ण

/* The rmmap ioctl appears to be unnecessary.  All mappings are torn करोwn on
 * the last बंद of the device, and this is necessary क्रम cleanup when things
 * निकास uncleanly.  Thereक्रमe, having userland manually हटाओ mappings seems
 * like a poपूर्णांकless exercise since they're going away anyway.
 *
 * One use हाल might be after addmap is allowed क्रम normal users क्रम SHM and
 * माला_लो used by drivers that the server करोesn't need to care about.  This seems
 * unlikely.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg poपूर्णांकer to a काष्ठा drm_map काष्ठाure.
 * \लeturn zero on success or a negative value on error.
 */
पूर्णांक drm_legacy_rmmap_ioctl(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_map *request = data;
	काष्ठा drm_local_map *map = शून्य;
	काष्ठा drm_map_list *r_list;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	mutex_lock(&dev->काष्ठा_mutex);
	list_क्रम_each_entry(r_list, &dev->maplist, head) अणु
		अगर (r_list->map &&
		    r_list->user_token == (अचिन्हित दीर्घ)request->handle &&
		    r_list->map->flags & _DRM_REMOVABLE) अणु
			map = r_list->map;
			अवरोध;
		पूर्ण
	पूर्ण

	/* List has wrapped around to the head poपूर्णांकer, or it's empty we didn't
	 * find anything.
	 */
	अगर (list_empty(&dev->maplist) || !map) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		वापस -EINVAL;
	पूर्ण

	/* Register and framebuffer maps are permanent */
	अगर ((map->type == _DRM_REGISTERS) || (map->type == _DRM_FRAME_BUFFER)) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		वापस 0;
	पूर्ण

	ret = drm_legacy_rmmap_locked(dev, map);

	mutex_unlock(&dev->काष्ठा_mutex);

	वापस ret;
पूर्ण

/*
 * Cleanup after an error on one of the addbufs() functions.
 *
 * \param dev DRM device.
 * \param entry buffer entry where the error occurred.
 *
 * Frees any pages and buffers associated with the given entry.
 */
अटल व्योम drm_cleanup_buf_error(काष्ठा drm_device *dev,
				  काष्ठा drm_buf_entry *entry)
अणु
	पूर्णांक i;

	अगर (entry->seg_count) अणु
		क्रम (i = 0; i < entry->seg_count; i++) अणु
			अगर (entry->seglist[i]) अणु
				drm_pci_मुक्त(dev, entry->seglist[i]);
			पूर्ण
		पूर्ण
		kमुक्त(entry->seglist);

		entry->seg_count = 0;
	पूर्ण

	अगर (entry->buf_count) अणु
		क्रम (i = 0; i < entry->buf_count; i++) अणु
			kमुक्त(entry->buflist[i].dev_निजी);
		पूर्ण
		kमुक्त(entry->buflist);

		entry->buf_count = 0;
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_AGP)
/*
 * Add AGP buffers क्रम DMA transfers.
 *
 * \param dev काष्ठा drm_device to which the buffers are to be added.
 * \param request poपूर्णांकer to a काष्ठा drm_buf_desc describing the request.
 * \लeturn zero on success or a negative number on failure.
 *
 * After some sanity checks creates a drm_buf काष्ठाure क्रम each buffer and
 * पुनः_स्मृतिates the buffer list of the same size order to accommodate the new
 * buffers.
 */
पूर्णांक drm_legacy_addbufs_agp(काष्ठा drm_device *dev,
			   काष्ठा drm_buf_desc *request)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	काष्ठा drm_buf_entry *entry;
	काष्ठा drm_agp_mem *agp_entry;
	काष्ठा drm_buf *buf;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ agp_offset;
	पूर्णांक count;
	पूर्णांक order;
	पूर्णांक size;
	पूर्णांक alignment;
	पूर्णांक page_order;
	पूर्णांक total;
	पूर्णांक byte_count;
	पूर्णांक i, valid;
	काष्ठा drm_buf **temp_buflist;

	अगर (!dma)
		वापस -EINVAL;

	count = request->count;
	order = order_base_2(request->size);
	size = 1 << order;

	alignment = (request->flags & _DRM_PAGE_ALIGN)
	    ? PAGE_ALIGN(size) : size;
	page_order = order - PAGE_SHIFT > 0 ? order - PAGE_SHIFT : 0;
	total = PAGE_SIZE << page_order;

	byte_count = 0;
	agp_offset = dev->agp->base + request->agp_start;

	DRM_DEBUG("count:      %d\n", count);
	DRM_DEBUG("order:      %d\n", order);
	DRM_DEBUG("size:       %d\n", size);
	DRM_DEBUG("agp_offset: %lx\n", agp_offset);
	DRM_DEBUG("alignment:  %d\n", alignment);
	DRM_DEBUG("page_order: %d\n", page_order);
	DRM_DEBUG("total:      %d\n", total);

	अगर (order < DRM_MIN_ORDER || order > DRM_MAX_ORDER)
		वापस -EINVAL;

	/* Make sure buffers are located in AGP memory that we own */
	valid = 0;
	list_क्रम_each_entry(agp_entry, &dev->agp->memory, head) अणु
		अगर ((agp_offset >= agp_entry->bound) &&
		    (agp_offset + total * count <= agp_entry->bound + agp_entry->pages * PAGE_SIZE)) अणु
			valid = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!list_empty(&dev->agp->memory) && !valid) अणु
		DRM_DEBUG("zone invalid\n");
		वापस -EINVAL;
	पूर्ण
	spin_lock(&dev->buf_lock);
	अगर (dev->buf_use) अणु
		spin_unlock(&dev->buf_lock);
		वापस -EBUSY;
	पूर्ण
	atomic_inc(&dev->buf_alloc);
	spin_unlock(&dev->buf_lock);

	mutex_lock(&dev->काष्ठा_mutex);
	entry = &dma->bufs[order];
	अगर (entry->buf_count) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		atomic_dec(&dev->buf_alloc);
		वापस -ENOMEM;	/* May only call once क्रम each order */
	पूर्ण

	अगर (count < 0 || count > 4096) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		atomic_dec(&dev->buf_alloc);
		वापस -EINVAL;
	पूर्ण

	entry->buflist = kसुस्मृति(count, माप(*entry->buflist), GFP_KERNEL);
	अगर (!entry->buflist) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		atomic_dec(&dev->buf_alloc);
		वापस -ENOMEM;
	पूर्ण

	entry->buf_size = size;
	entry->page_order = page_order;

	offset = 0;

	जबतक (entry->buf_count < count) अणु
		buf = &entry->buflist[entry->buf_count];
		buf->idx = dma->buf_count + entry->buf_count;
		buf->total = alignment;
		buf->order = order;
		buf->used = 0;

		buf->offset = (dma->byte_count + offset);
		buf->bus_address = agp_offset + offset;
		buf->address = (व्योम *)(agp_offset + offset);
		buf->next = शून्य;
		buf->रुकोing = 0;
		buf->pending = 0;
		buf->file_priv = शून्य;

		buf->dev_priv_size = dev->driver->dev_priv_size;
		buf->dev_निजी = kzalloc(buf->dev_priv_size, GFP_KERNEL);
		अगर (!buf->dev_निजी) अणु
			/* Set count correctly so we मुक्त the proper amount. */
			entry->buf_count = count;
			drm_cleanup_buf_error(dev, entry);
			mutex_unlock(&dev->काष्ठा_mutex);
			atomic_dec(&dev->buf_alloc);
			वापस -ENOMEM;
		पूर्ण

		DRM_DEBUG("buffer %d @ %p\n", entry->buf_count, buf->address);

		offset += alignment;
		entry->buf_count++;
		byte_count += PAGE_SIZE << page_order;
	पूर्ण

	DRM_DEBUG("byte_count: %d\n", byte_count);

	temp_buflist = kपुनः_स्मृति(dma->buflist,
				(dma->buf_count + entry->buf_count) *
				माप(*dma->buflist), GFP_KERNEL);
	अगर (!temp_buflist) अणु
		/* Free the entry because it isn't valid */
		drm_cleanup_buf_error(dev, entry);
		mutex_unlock(&dev->काष्ठा_mutex);
		atomic_dec(&dev->buf_alloc);
		वापस -ENOMEM;
	पूर्ण
	dma->buflist = temp_buflist;

	क्रम (i = 0; i < entry->buf_count; i++) अणु
		dma->buflist[i + dma->buf_count] = &entry->buflist[i];
	पूर्ण

	dma->buf_count += entry->buf_count;
	dma->seg_count += entry->seg_count;
	dma->page_count += byte_count >> PAGE_SHIFT;
	dma->byte_count += byte_count;

	DRM_DEBUG("dma->buf_count : %d\n", dma->buf_count);
	DRM_DEBUG("entry->buf_count : %d\n", entry->buf_count);

	mutex_unlock(&dev->काष्ठा_mutex);

	request->count = entry->buf_count;
	request->size = size;

	dma->flags = _DRM_DMA_USE_AGP;

	atomic_dec(&dev->buf_alloc);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_legacy_addbufs_agp);
#पूर्ण_अगर /* CONFIG_AGP */

पूर्णांक drm_legacy_addbufs_pci(काष्ठा drm_device *dev,
			   काष्ठा drm_buf_desc *request)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	पूर्णांक count;
	पूर्णांक order;
	पूर्णांक size;
	पूर्णांक total;
	पूर्णांक page_order;
	काष्ठा drm_buf_entry *entry;
	drm_dma_handle_t *dmah;
	काष्ठा drm_buf *buf;
	पूर्णांक alignment;
	अचिन्हित दीर्घ offset;
	पूर्णांक i;
	पूर्णांक byte_count;
	पूर्णांक page_count;
	अचिन्हित दीर्घ *temp_pagelist;
	काष्ठा drm_buf **temp_buflist;

	अगर (!drm_core_check_feature(dev, DRIVER_PCI_DMA))
		वापस -EOPNOTSUPP;

	अगर (!dma)
		वापस -EINVAL;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	count = request->count;
	order = order_base_2(request->size);
	size = 1 << order;

	DRM_DEBUG("count=%d, size=%d (%d), order=%d\n",
		  request->count, request->size, size, order);

	अगर (order < DRM_MIN_ORDER || order > DRM_MAX_ORDER)
		वापस -EINVAL;

	alignment = (request->flags & _DRM_PAGE_ALIGN)
	    ? PAGE_ALIGN(size) : size;
	page_order = order - PAGE_SHIFT > 0 ? order - PAGE_SHIFT : 0;
	total = PAGE_SIZE << page_order;

	spin_lock(&dev->buf_lock);
	अगर (dev->buf_use) अणु
		spin_unlock(&dev->buf_lock);
		वापस -EBUSY;
	पूर्ण
	atomic_inc(&dev->buf_alloc);
	spin_unlock(&dev->buf_lock);

	mutex_lock(&dev->काष्ठा_mutex);
	entry = &dma->bufs[order];
	अगर (entry->buf_count) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		atomic_dec(&dev->buf_alloc);
		वापस -ENOMEM;	/* May only call once क्रम each order */
	पूर्ण

	अगर (count < 0 || count > 4096) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		atomic_dec(&dev->buf_alloc);
		वापस -EINVAL;
	पूर्ण

	entry->buflist = kसुस्मृति(count, माप(*entry->buflist), GFP_KERNEL);
	अगर (!entry->buflist) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		atomic_dec(&dev->buf_alloc);
		वापस -ENOMEM;
	पूर्ण

	entry->seglist = kसुस्मृति(count, माप(*entry->seglist), GFP_KERNEL);
	अगर (!entry->seglist) अणु
		kमुक्त(entry->buflist);
		mutex_unlock(&dev->काष्ठा_mutex);
		atomic_dec(&dev->buf_alloc);
		वापस -ENOMEM;
	पूर्ण

	/* Keep the original pagelist until we know all the allocations
	 * have succeeded
	 */
	temp_pagelist = kदो_स्मृति_array(dma->page_count + (count << page_order),
				      माप(*dma->pagelist),
				      GFP_KERNEL);
	अगर (!temp_pagelist) अणु
		kमुक्त(entry->buflist);
		kमुक्त(entry->seglist);
		mutex_unlock(&dev->काष्ठा_mutex);
		atomic_dec(&dev->buf_alloc);
		वापस -ENOMEM;
	पूर्ण
	स_नकल(temp_pagelist,
	       dma->pagelist, dma->page_count * माप(*dma->pagelist));
	DRM_DEBUG("pagelist: %d entries\n",
		  dma->page_count + (count << page_order));

	entry->buf_size = size;
	entry->page_order = page_order;
	byte_count = 0;
	page_count = 0;

	जबतक (entry->buf_count < count) अणु

		dmah = drm_pci_alloc(dev, PAGE_SIZE << page_order, 0x1000);

		अगर (!dmah) अणु
			/* Set count correctly so we मुक्त the proper amount. */
			entry->buf_count = count;
			entry->seg_count = count;
			drm_cleanup_buf_error(dev, entry);
			kमुक्त(temp_pagelist);
			mutex_unlock(&dev->काष्ठा_mutex);
			atomic_dec(&dev->buf_alloc);
			वापस -ENOMEM;
		पूर्ण
		entry->seglist[entry->seg_count++] = dmah;
		क्रम (i = 0; i < (1 << page_order); i++) अणु
			DRM_DEBUG("page %d @ 0x%08lx\n",
				  dma->page_count + page_count,
				  (अचिन्हित दीर्घ)dmah->vaddr + PAGE_SIZE * i);
			temp_pagelist[dma->page_count + page_count++]
				= (अचिन्हित दीर्घ)dmah->vaddr + PAGE_SIZE * i;
		पूर्ण
		क्रम (offset = 0;
		     offset + size <= total && entry->buf_count < count;
		     offset += alignment, ++entry->buf_count) अणु
			buf = &entry->buflist[entry->buf_count];
			buf->idx = dma->buf_count + entry->buf_count;
			buf->total = alignment;
			buf->order = order;
			buf->used = 0;
			buf->offset = (dma->byte_count + byte_count + offset);
			buf->address = (व्योम *)(dmah->vaddr + offset);
			buf->bus_address = dmah->busaddr + offset;
			buf->next = शून्य;
			buf->रुकोing = 0;
			buf->pending = 0;
			buf->file_priv = शून्य;

			buf->dev_priv_size = dev->driver->dev_priv_size;
			buf->dev_निजी = kzalloc(buf->dev_priv_size,
						GFP_KERNEL);
			अगर (!buf->dev_निजी) अणु
				/* Set count correctly so we मुक्त the proper amount. */
				entry->buf_count = count;
				entry->seg_count = count;
				drm_cleanup_buf_error(dev, entry);
				kमुक्त(temp_pagelist);
				mutex_unlock(&dev->काष्ठा_mutex);
				atomic_dec(&dev->buf_alloc);
				वापस -ENOMEM;
			पूर्ण

			DRM_DEBUG("buffer %d @ %p\n",
				  entry->buf_count, buf->address);
		पूर्ण
		byte_count += PAGE_SIZE << page_order;
	पूर्ण

	temp_buflist = kपुनः_स्मृति(dma->buflist,
				(dma->buf_count + entry->buf_count) *
				माप(*dma->buflist), GFP_KERNEL);
	अगर (!temp_buflist) अणु
		/* Free the entry because it isn't valid */
		drm_cleanup_buf_error(dev, entry);
		kमुक्त(temp_pagelist);
		mutex_unlock(&dev->काष्ठा_mutex);
		atomic_dec(&dev->buf_alloc);
		वापस -ENOMEM;
	पूर्ण
	dma->buflist = temp_buflist;

	क्रम (i = 0; i < entry->buf_count; i++) अणु
		dma->buflist[i + dma->buf_count] = &entry->buflist[i];
	पूर्ण

	/* No allocations failed, so now we can replace the original pagelist
	 * with the new one.
	 */
	अगर (dma->page_count) अणु
		kमुक्त(dma->pagelist);
	पूर्ण
	dma->pagelist = temp_pagelist;

	dma->buf_count += entry->buf_count;
	dma->seg_count += entry->seg_count;
	dma->page_count += entry->seg_count << page_order;
	dma->byte_count += PAGE_SIZE * (entry->seg_count << page_order);

	mutex_unlock(&dev->काष्ठा_mutex);

	request->count = entry->buf_count;
	request->size = size;

	अगर (request->flags & _DRM_PCI_BUFFER_RO)
		dma->flags = _DRM_DMA_USE_PCI_RO;

	atomic_dec(&dev->buf_alloc);
	वापस 0;

पूर्ण
EXPORT_SYMBOL(drm_legacy_addbufs_pci);

अटल पूर्णांक drm_legacy_addbufs_sg(काष्ठा drm_device *dev,
				 काष्ठा drm_buf_desc *request)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	काष्ठा drm_buf_entry *entry;
	काष्ठा drm_buf *buf;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ agp_offset;
	पूर्णांक count;
	पूर्णांक order;
	पूर्णांक size;
	पूर्णांक alignment;
	पूर्णांक page_order;
	पूर्णांक total;
	पूर्णांक byte_count;
	पूर्णांक i;
	काष्ठा drm_buf **temp_buflist;

	अगर (!drm_core_check_feature(dev, DRIVER_SG))
		वापस -EOPNOTSUPP;

	अगर (!dma)
		वापस -EINVAL;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	count = request->count;
	order = order_base_2(request->size);
	size = 1 << order;

	alignment = (request->flags & _DRM_PAGE_ALIGN)
	    ? PAGE_ALIGN(size) : size;
	page_order = order - PAGE_SHIFT > 0 ? order - PAGE_SHIFT : 0;
	total = PAGE_SIZE << page_order;

	byte_count = 0;
	agp_offset = request->agp_start;

	DRM_DEBUG("count:      %d\n", count);
	DRM_DEBUG("order:      %d\n", order);
	DRM_DEBUG("size:       %d\n", size);
	DRM_DEBUG("agp_offset: %lu\n", agp_offset);
	DRM_DEBUG("alignment:  %d\n", alignment);
	DRM_DEBUG("page_order: %d\n", page_order);
	DRM_DEBUG("total:      %d\n", total);

	अगर (order < DRM_MIN_ORDER || order > DRM_MAX_ORDER)
		वापस -EINVAL;

	spin_lock(&dev->buf_lock);
	अगर (dev->buf_use) अणु
		spin_unlock(&dev->buf_lock);
		वापस -EBUSY;
	पूर्ण
	atomic_inc(&dev->buf_alloc);
	spin_unlock(&dev->buf_lock);

	mutex_lock(&dev->काष्ठा_mutex);
	entry = &dma->bufs[order];
	अगर (entry->buf_count) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		atomic_dec(&dev->buf_alloc);
		वापस -ENOMEM;	/* May only call once क्रम each order */
	पूर्ण

	अगर (count < 0 || count > 4096) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		atomic_dec(&dev->buf_alloc);
		वापस -EINVAL;
	पूर्ण

	entry->buflist = kसुस्मृति(count, माप(*entry->buflist), GFP_KERNEL);
	अगर (!entry->buflist) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		atomic_dec(&dev->buf_alloc);
		वापस -ENOMEM;
	पूर्ण

	entry->buf_size = size;
	entry->page_order = page_order;

	offset = 0;

	जबतक (entry->buf_count < count) अणु
		buf = &entry->buflist[entry->buf_count];
		buf->idx = dma->buf_count + entry->buf_count;
		buf->total = alignment;
		buf->order = order;
		buf->used = 0;

		buf->offset = (dma->byte_count + offset);
		buf->bus_address = agp_offset + offset;
		buf->address = (व्योम *)(agp_offset + offset
					+ (अचिन्हित दीर्घ)dev->sg->भव);
		buf->next = शून्य;
		buf->रुकोing = 0;
		buf->pending = 0;
		buf->file_priv = शून्य;

		buf->dev_priv_size = dev->driver->dev_priv_size;
		buf->dev_निजी = kzalloc(buf->dev_priv_size, GFP_KERNEL);
		अगर (!buf->dev_निजी) अणु
			/* Set count correctly so we मुक्त the proper amount. */
			entry->buf_count = count;
			drm_cleanup_buf_error(dev, entry);
			mutex_unlock(&dev->काष्ठा_mutex);
			atomic_dec(&dev->buf_alloc);
			वापस -ENOMEM;
		पूर्ण

		DRM_DEBUG("buffer %d @ %p\n", entry->buf_count, buf->address);

		offset += alignment;
		entry->buf_count++;
		byte_count += PAGE_SIZE << page_order;
	पूर्ण

	DRM_DEBUG("byte_count: %d\n", byte_count);

	temp_buflist = kपुनः_स्मृति(dma->buflist,
				(dma->buf_count + entry->buf_count) *
				माप(*dma->buflist), GFP_KERNEL);
	अगर (!temp_buflist) अणु
		/* Free the entry because it isn't valid */
		drm_cleanup_buf_error(dev, entry);
		mutex_unlock(&dev->काष्ठा_mutex);
		atomic_dec(&dev->buf_alloc);
		वापस -ENOMEM;
	पूर्ण
	dma->buflist = temp_buflist;

	क्रम (i = 0; i < entry->buf_count; i++) अणु
		dma->buflist[i + dma->buf_count] = &entry->buflist[i];
	पूर्ण

	dma->buf_count += entry->buf_count;
	dma->seg_count += entry->seg_count;
	dma->page_count += byte_count >> PAGE_SHIFT;
	dma->byte_count += byte_count;

	DRM_DEBUG("dma->buf_count : %d\n", dma->buf_count);
	DRM_DEBUG("entry->buf_count : %d\n", entry->buf_count);

	mutex_unlock(&dev->काष्ठा_mutex);

	request->count = entry->buf_count;
	request->size = size;

	dma->flags = _DRM_DMA_USE_SG;

	atomic_dec(&dev->buf_alloc);
	वापस 0;
पूर्ण

/*
 * Add buffers क्रम DMA transfers (ioctl).
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg poपूर्णांकer to a काष्ठा drm_buf_desc request.
 * \लeturn zero on success or a negative number on failure.
 *
 * According with the memory type specअगरied in drm_buf_desc::flags and the
 * build options, it dispatches the call either to addbufs_agp(),
 * addbufs_sg() or addbufs_pci() क्रम AGP, scatter-gather or consistent
 * PCI memory respectively.
 */
पूर्णांक drm_legacy_addbufs(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_buf_desc *request = data;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	अगर (!drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		वापस -EOPNOTSUPP;

#अगर IS_ENABLED(CONFIG_AGP)
	अगर (request->flags & _DRM_AGP_BUFFER)
		ret = drm_legacy_addbufs_agp(dev, request);
	अन्यथा
#पूर्ण_अगर
	अगर (request->flags & _DRM_SG_BUFFER)
		ret = drm_legacy_addbufs_sg(dev, request);
	अन्यथा अगर (request->flags & _DRM_FB_BUFFER)
		ret = -EINVAL;
	अन्यथा
		ret = drm_legacy_addbufs_pci(dev, request);

	वापस ret;
पूर्ण

/*
 * Get inक्रमmation about the buffer mappings.
 *
 * This was originally mean क्रम debugging purposes, or by a sophisticated
 * client library to determine how best to use the available buffers (e.g.,
 * large buffers can be used क्रम image transfer).
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg poपूर्णांकer to a drm_buf_info काष्ठाure.
 * \लeturn zero on success or a negative number on failure.
 *
 * Increments drm_device::buf_use जबतक holding the drm_device::buf_lock
 * lock, preventing of allocating more buffers after this call. Inक्रमmation
 * about each requested buffer is then copied पूर्णांकo user space.
 */
पूर्णांक __drm_legacy_infobufs(काष्ठा drm_device *dev,
			व्योम *data, पूर्णांक *p,
			पूर्णांक (*f)(व्योम *, पूर्णांक, काष्ठा drm_buf_entry *))
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	पूर्णांक i;
	पूर्णांक count;

	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	अगर (!drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		वापस -EOPNOTSUPP;

	अगर (!dma)
		वापस -EINVAL;

	spin_lock(&dev->buf_lock);
	अगर (atomic_पढ़ो(&dev->buf_alloc)) अणु
		spin_unlock(&dev->buf_lock);
		वापस -EBUSY;
	पूर्ण
	++dev->buf_use;		/* Can't allocate more after this call */
	spin_unlock(&dev->buf_lock);

	क्रम (i = 0, count = 0; i < DRM_MAX_ORDER + 1; i++) अणु
		अगर (dma->bufs[i].buf_count)
			++count;
	पूर्ण

	DRM_DEBUG("count = %d\n", count);

	अगर (*p >= count) अणु
		क्रम (i = 0, count = 0; i < DRM_MAX_ORDER + 1; i++) अणु
			काष्ठा drm_buf_entry *from = &dma->bufs[i];

			अगर (from->buf_count) अणु
				अगर (f(data, count, from) < 0)
					वापस -EFAULT;
				DRM_DEBUG("%d %d %d %d %d\n",
					  i,
					  dma->bufs[i].buf_count,
					  dma->bufs[i].buf_size,
					  dma->bufs[i].low_mark,
					  dma->bufs[i].high_mark);
				++count;
			पूर्ण
		पूर्ण
	पूर्ण
	*p = count;

	वापस 0;
पूर्ण

अटल पूर्णांक copy_one_buf(व्योम *data, पूर्णांक count, काष्ठा drm_buf_entry *from)
अणु
	काष्ठा drm_buf_info *request = data;
	काष्ठा drm_buf_desc __user *to = &request->list[count];
	काष्ठा drm_buf_desc v = अणु.count = from->buf_count,
				 .size = from->buf_size,
				 .low_mark = from->low_mark,
				 .high_mark = from->high_markपूर्ण;

	अगर (copy_to_user(to, &v, दुरत्व(काष्ठा drm_buf_desc, flags)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

पूर्णांक drm_legacy_infobufs(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_buf_info *request = data;

	वापस __drm_legacy_infobufs(dev, data, &request->count, copy_one_buf);
पूर्ण

/*
 * Specअगरies a low and high water mark क्रम buffer allocation
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg a poपूर्णांकer to a drm_buf_desc काष्ठाure.
 * \लeturn zero on success or a negative number on failure.
 *
 * Verअगरies that the size order is bounded between the admissible orders and
 * updates the respective drm_device_dma::bufs entry low and high water mark.
 *
 * \नote This ioctl is deprecated and mostly never used.
 */
पूर्णांक drm_legacy_markbufs(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	काष्ठा drm_buf_desc *request = data;
	पूर्णांक order;
	काष्ठा drm_buf_entry *entry;

	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	अगर (!drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		वापस -EOPNOTSUPP;

	अगर (!dma)
		वापस -EINVAL;

	DRM_DEBUG("%d, %d, %d\n",
		  request->size, request->low_mark, request->high_mark);
	order = order_base_2(request->size);
	अगर (order < DRM_MIN_ORDER || order > DRM_MAX_ORDER)
		वापस -EINVAL;
	entry = &dma->bufs[order];

	अगर (request->low_mark < 0 || request->low_mark > entry->buf_count)
		वापस -EINVAL;
	अगर (request->high_mark < 0 || request->high_mark > entry->buf_count)
		वापस -EINVAL;

	entry->low_mark = request->low_mark;
	entry->high_mark = request->high_mark;

	वापस 0;
पूर्ण

/*
 * Unreserve the buffers in list, previously reserved using drmDMA.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg poपूर्णांकer to a drm_buf_मुक्त काष्ठाure.
 * \लeturn zero on success or a negative number on failure.
 *
 * Calls मुक्त_buffer() क्रम each used buffer.
 * This function is primarily used क्रम debugging.
 */
पूर्णांक drm_legacy_मुक्तbufs(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	काष्ठा drm_buf_मुक्त *request = data;
	पूर्णांक i;
	पूर्णांक idx;
	काष्ठा drm_buf *buf;

	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	अगर (!drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		वापस -EOPNOTSUPP;

	अगर (!dma)
		वापस -EINVAL;

	DRM_DEBUG("%d\n", request->count);
	क्रम (i = 0; i < request->count; i++) अणु
		अगर (copy_from_user(&idx, &request->list[i], माप(idx)))
			वापस -EFAULT;
		अगर (idx < 0 || idx >= dma->buf_count) अणु
			DRM_ERROR("Index %d (of %d max)\n",
				  idx, dma->buf_count - 1);
			वापस -EINVAL;
		पूर्ण
		idx = array_index_nospec(idx, dma->buf_count);
		buf = dma->buflist[idx];
		अगर (buf->file_priv != file_priv) अणु
			DRM_ERROR("Process %d freeing buffer not owned\n",
				  task_pid_nr(current));
			वापस -EINVAL;
		पूर्ण
		drm_legacy_मुक्त_buffer(dev, buf);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Maps all of the DMA buffers पूर्णांकo client-भव space (ioctl).
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg poपूर्णांकer to a drm_buf_map काष्ठाure.
 * \लeturn zero on success or a negative number on failure.
 *
 * Maps the AGP, SG or PCI buffer region with vm_mmap(), and copies inक्रमmation
 * about each buffer पूर्णांकo user space. For PCI buffers, it calls vm_mmap() with
 * offset equal to 0, which drm_mmap() पूर्णांकerpretes as PCI buffers and calls
 * drm_mmap_dma().
 */
पूर्णांक __drm_legacy_mapbufs(काष्ठा drm_device *dev, व्योम *data, पूर्णांक *p,
			 व्योम __user **v,
			 पूर्णांक (*f)(व्योम *, पूर्णांक, अचिन्हित दीर्घ,
				 काष्ठा drm_buf *),
				 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_device_dma *dma = dev->dma;
	पूर्णांक retcode = 0;
	अचिन्हित दीर्घ भव;
	पूर्णांक i;

	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	अगर (!drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		वापस -EOPNOTSUPP;

	अगर (!dma)
		वापस -EINVAL;

	spin_lock(&dev->buf_lock);
	अगर (atomic_पढ़ो(&dev->buf_alloc)) अणु
		spin_unlock(&dev->buf_lock);
		वापस -EBUSY;
	पूर्ण
	dev->buf_use++;		/* Can't allocate more after this call */
	spin_unlock(&dev->buf_lock);

	अगर (*p >= dma->buf_count) अणु
		अगर ((dev->agp && (dma->flags & _DRM_DMA_USE_AGP))
		    || (drm_core_check_feature(dev, DRIVER_SG)
			&& (dma->flags & _DRM_DMA_USE_SG))) अणु
			काष्ठा drm_local_map *map = dev->agp_buffer_map;
			अचिन्हित दीर्घ token = dev->agp_buffer_token;

			अगर (!map) अणु
				retcode = -EINVAL;
				जाओ करोne;
			पूर्ण
			भव = vm_mmap(file_priv->filp, 0, map->size,
					  PROT_READ | PROT_WRITE,
					  MAP_SHARED,
					  token);
		पूर्ण अन्यथा अणु
			भव = vm_mmap(file_priv->filp, 0, dma->byte_count,
					  PROT_READ | PROT_WRITE,
					  MAP_SHARED, 0);
		पूर्ण
		अगर (भव > -1024UL) अणु
			/* Real error */
			retcode = (चिन्हित दीर्घ)भव;
			जाओ करोne;
		पूर्ण
		*v = (व्योम __user *)भव;

		क्रम (i = 0; i < dma->buf_count; i++) अणु
			अगर (f(data, i, भव, dma->buflist[i]) < 0) अणु
				retcode = -EFAULT;
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण
      करोne:
	*p = dma->buf_count;
	DRM_DEBUG("%d buffers, retcode = %d\n", *p, retcode);

	वापस retcode;
पूर्ण

अटल पूर्णांक map_one_buf(व्योम *data, पूर्णांक idx, अचिन्हित दीर्घ भव,
			काष्ठा drm_buf *buf)
अणु
	काष्ठा drm_buf_map *request = data;
	अचिन्हित दीर्घ address = भव + buf->offset;	/* *** */

	अगर (copy_to_user(&request->list[idx].idx, &buf->idx,
			 माप(request->list[0].idx)))
		वापस -EFAULT;
	अगर (copy_to_user(&request->list[idx].total, &buf->total,
			 माप(request->list[0].total)))
		वापस -EFAULT;
	अगर (clear_user(&request->list[idx].used, माप(पूर्णांक)))
		वापस -EFAULT;
	अगर (copy_to_user(&request->list[idx].address, &address,
			 माप(address)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

पूर्णांक drm_legacy_mapbufs(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_buf_map *request = data;

	वापस __drm_legacy_mapbufs(dev, data, &request->count,
				    &request->भव, map_one_buf,
				    file_priv);
पूर्ण

पूर्णांक drm_legacy_dma_ioctl(काष्ठा drm_device *dev, व्योम *data,
		  काष्ठा drm_file *file_priv)
अणु
	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	अगर (dev->driver->dma_ioctl)
		वापस dev->driver->dma_ioctl(dev, data, file_priv);
	अन्यथा
		वापस -EINVAL;
पूर्ण

काष्ठा drm_local_map *drm_legacy_माला_लोarea(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_map_list *entry;

	list_क्रम_each_entry(entry, &dev->maplist, head) अणु
		अगर (entry->map && entry->map->type == _DRM_SHM &&
		    (entry->map->flags & _DRM_CONTAINS_LOCK)) अणु
			वापस entry->map;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drm_legacy_माला_लोarea);
