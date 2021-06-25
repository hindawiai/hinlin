<शैली गुरु>
/******************************************************************************
 * gntdev.c
 *
 * Device क्रम accessing (in user-space) pages that have been granted by other
 * करोमुख्यs.
 *
 * Copyright (c) 2006-2007, D G Murray.
 *           (c) 2009 Gerd Hoffmann <kraxel@redhat.com>
 *           (c) 2018 Oleksandr Andrushchenko, EPAM Systems Inc.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#अघोषित DEBUG

#घोषणा pr_fmt(fmt) "xen:" KBUILD_MODNAME ": " fmt

#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/refcount.h>

#समावेश <xen/xen.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/balloon.h>
#समावेश <xen/gntdev.h>
#समावेश <xen/events.h>
#समावेश <xen/page.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/xen/hypercall.h>

#समावेश "gntdev-common.h"
#अगर_घोषित CONFIG_XEN_GNTDEV_DMABUF
#समावेश "gntdev-dmabuf.h"
#पूर्ण_अगर

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Derek G. Murray <Derek.Murray@cl.cam.ac.uk>, "
	      "Gerd Hoffmann <kraxel@redhat.com>");
MODULE_DESCRIPTION("User-space granted page access driver");

अटल अचिन्हित पूर्णांक limit = 64*1024;
module_param(limit, uपूर्णांक, 0644);
MODULE_PARM_DESC(limit,
	"Maximum number of grants that may be mapped by one mapping request");

अटल पूर्णांक use_ptemod;

अटल पूर्णांक unmap_grant_pages(काष्ठा gntdev_grant_map *map,
			     पूर्णांक offset, पूर्णांक pages);

अटल काष्ठा miscdevice gntdev_miscdev;

/* ------------------------------------------------------------------ */

bool gntdev_test_page_count(अचिन्हित पूर्णांक count)
अणु
	वापस !count || count > limit;
पूर्ण

अटल व्योम gntdev_prपूर्णांक_maps(काष्ठा gntdev_priv *priv,
			      अक्षर *text, पूर्णांक text_index)
अणु
#अगर_घोषित DEBUG
	काष्ठा gntdev_grant_map *map;

	pr_debug("%s: maps list (priv %p)\n", __func__, priv);
	list_क्रम_each_entry(map, &priv->maps, next)
		pr_debug("  index %2d, count %2d %s\n",
		       map->index, map->count,
		       map->index == text_index && text ? text : "");
#पूर्ण_अगर
पूर्ण

अटल व्योम gntdev_मुक्त_map(काष्ठा gntdev_grant_map *map)
अणु
	अगर (map == शून्य)
		वापस;

#अगर_घोषित CONFIG_XEN_GRANT_DMA_ALLOC
	अगर (map->dma_vaddr) अणु
		काष्ठा gnttab_dma_alloc_args args;

		args.dev = map->dma_dev;
		args.coherent = !!(map->dma_flags & GNTDEV_DMA_FLAG_COHERENT);
		args.nr_pages = map->count;
		args.pages = map->pages;
		args.frames = map->frames;
		args.vaddr = map->dma_vaddr;
		args.dev_bus_addr = map->dma_bus_addr;

		gnttab_dma_मुक्त_pages(&args);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अगर (map->pages)
		gnttab_मुक्त_pages(map->count, map->pages);

#अगर_घोषित CONFIG_XEN_GRANT_DMA_ALLOC
	kvमुक्त(map->frames);
#पूर्ण_अगर
	kvमुक्त(map->pages);
	kvमुक्त(map->grants);
	kvमुक्त(map->map_ops);
	kvमुक्त(map->unmap_ops);
	kvमुक्त(map->kmap_ops);
	kvमुक्त(map->kunmap_ops);
	kमुक्त(map);
पूर्ण

काष्ठा gntdev_grant_map *gntdev_alloc_map(काष्ठा gntdev_priv *priv, पूर्णांक count,
					  पूर्णांक dma_flags)
अणु
	काष्ठा gntdev_grant_map *add;
	पूर्णांक i;

	add = kzalloc(माप(*add), GFP_KERNEL);
	अगर (शून्य == add)
		वापस शून्य;

	add->grants    = kvदो_स्मृति_array(count, माप(add->grants[0]),
					GFP_KERNEL);
	add->map_ops   = kvदो_स्मृति_array(count, माप(add->map_ops[0]),
					GFP_KERNEL);
	add->unmap_ops = kvदो_स्मृति_array(count, माप(add->unmap_ops[0]),
					GFP_KERNEL);
	add->pages     = kvसुस्मृति(count, माप(add->pages[0]), GFP_KERNEL);
	अगर (शून्य == add->grants    ||
	    शून्य == add->map_ops   ||
	    शून्य == add->unmap_ops ||
	    शून्य == add->pages)
		जाओ err;
	अगर (use_ptemod) अणु
		add->kmap_ops   = kvदो_स्मृति_array(count, माप(add->kmap_ops[0]),
						 GFP_KERNEL);
		add->kunmap_ops = kvदो_स्मृति_array(count, माप(add->kunmap_ops[0]),
						 GFP_KERNEL);
		अगर (शून्य == add->kmap_ops || शून्य == add->kunmap_ops)
			जाओ err;
	पूर्ण

#अगर_घोषित CONFIG_XEN_GRANT_DMA_ALLOC
	add->dma_flags = dma_flags;

	/*
	 * Check अगर this mapping is requested to be backed
	 * by a DMA buffer.
	 */
	अगर (dma_flags & (GNTDEV_DMA_FLAG_WC | GNTDEV_DMA_FLAG_COHERENT)) अणु
		काष्ठा gnttab_dma_alloc_args args;

		add->frames = kvसुस्मृति(count, माप(add->frames[0]),
				       GFP_KERNEL);
		अगर (!add->frames)
			जाओ err;

		/* Remember the device, so we can मुक्त DMA memory. */
		add->dma_dev = priv->dma_dev;

		args.dev = priv->dma_dev;
		args.coherent = !!(dma_flags & GNTDEV_DMA_FLAG_COHERENT);
		args.nr_pages = count;
		args.pages = add->pages;
		args.frames = add->frames;

		अगर (gnttab_dma_alloc_pages(&args))
			जाओ err;

		add->dma_vaddr = args.vaddr;
		add->dma_bus_addr = args.dev_bus_addr;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अगर (gnttab_alloc_pages(count, add->pages))
		जाओ err;

	क्रम (i = 0; i < count; i++) अणु
		add->grants[i].करोmid = DOMID_INVALID;
		add->grants[i].ref = INVALID_GRANT_REF;
		add->map_ops[i].handle = INVALID_GRANT_HANDLE;
		add->unmap_ops[i].handle = INVALID_GRANT_HANDLE;
		अगर (use_ptemod) अणु
			add->kmap_ops[i].handle = INVALID_GRANT_HANDLE;
			add->kunmap_ops[i].handle = INVALID_GRANT_HANDLE;
		पूर्ण
	पूर्ण

	add->index = 0;
	add->count = count;
	refcount_set(&add->users, 1);

	वापस add;

err:
	gntdev_मुक्त_map(add);
	वापस शून्य;
पूर्ण

व्योम gntdev_add_map(काष्ठा gntdev_priv *priv, काष्ठा gntdev_grant_map *add)
अणु
	काष्ठा gntdev_grant_map *map;

	list_क्रम_each_entry(map, &priv->maps, next) अणु
		अगर (add->index + add->count < map->index) अणु
			list_add_tail(&add->next, &map->next);
			जाओ करोne;
		पूर्ण
		add->index = map->index + map->count;
	पूर्ण
	list_add_tail(&add->next, &priv->maps);

करोne:
	gntdev_prपूर्णांक_maps(priv, "[new]", add->index);
पूर्ण

अटल काष्ठा gntdev_grant_map *gntdev_find_map_index(काष्ठा gntdev_priv *priv,
						      पूर्णांक index, पूर्णांक count)
अणु
	काष्ठा gntdev_grant_map *map;

	list_क्रम_each_entry(map, &priv->maps, next) अणु
		अगर (map->index != index)
			जारी;
		अगर (count && map->count != count)
			जारी;
		वापस map;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम gntdev_put_map(काष्ठा gntdev_priv *priv, काष्ठा gntdev_grant_map *map)
अणु
	अगर (!map)
		वापस;

	अगर (!refcount_dec_and_test(&map->users))
		वापस;

	अगर (map->notअगरy.flags & UNMAP_NOTIFY_SEND_EVENT) अणु
		notअगरy_remote_via_evtchn(map->notअगरy.event);
		evtchn_put(map->notअगरy.event);
	पूर्ण

	अगर (map->pages && !use_ptemod)
		unmap_grant_pages(map, 0, map->count);
	gntdev_मुक्त_map(map);
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक find_grant_ptes(pte_t *pte, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	काष्ठा gntdev_grant_map *map = data;
	अचिन्हित पूर्णांक pgnr = (addr - map->vma->vm_start) >> PAGE_SHIFT;
	पूर्णांक flags = map->flags | GNTMAP_application_map | GNTMAP_contains_pte;
	u64 pte_maddr;

	BUG_ON(pgnr >= map->count);
	pte_maddr = arbitrary_virt_to_machine(pte).maddr;

	/*
	 * Set the PTE as special to क्रमce get_user_pages_fast() fall
	 * back to the slow path.  If this is not supported as part of
	 * the grant map, it will be करोne afterwards.
	 */
	अगर (xen_feature(XENFEAT_gnttab_map_avail_bits))
		flags |= (1 << _GNTMAP_guest_avail0);

	gnttab_set_map_op(&map->map_ops[pgnr], pte_maddr, flags,
			  map->grants[pgnr].ref,
			  map->grants[pgnr].करोmid);
	gnttab_set_unmap_op(&map->unmap_ops[pgnr], pte_maddr, flags,
			    INVALID_GRANT_HANDLE);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_X86
अटल पूर्णांक set_grant_ptes_as_special(pte_t *pte, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	set_pte_at(current->mm, addr, pte, pte_mkspecial(*pte));
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक gntdev_map_grant_pages(काष्ठा gntdev_grant_map *map)
अणु
	पूर्णांक i, err = 0;

	अगर (!use_ptemod) अणु
		/* Note: it could alपढ़ोy be mapped */
		अगर (map->map_ops[0].handle != INVALID_GRANT_HANDLE)
			वापस 0;
		क्रम (i = 0; i < map->count; i++) अणु
			अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)
				pfn_to_kaddr(page_to_pfn(map->pages[i]));
			gnttab_set_map_op(&map->map_ops[i], addr, map->flags,
				map->grants[i].ref,
				map->grants[i].करोmid);
			gnttab_set_unmap_op(&map->unmap_ops[i], addr,
				map->flags, INVALID_GRANT_HANDLE);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Setup the map_ops corresponding to the pte entries poपूर्णांकing
		 * to the kernel linear addresses of the काष्ठा pages.
		 * These ptes are completely dअगरferent from the user ptes dealt
		 * with find_grant_ptes.
		 * Note that GNTMAP_device_map isn't needed here: The
		 * dev_bus_addr output field माला_लो consumed only from ->map_ops,
		 * and by not requesting it when mapping we also aव्योम needing
		 * to mirror dev_bus_addr पूर्णांकo ->unmap_ops (and holding an extra
		 * reference to the page in the hypervisor).
		 */
		अचिन्हित पूर्णांक flags = (map->flags & ~GNTMAP_device_map) |
				     GNTMAP_host_map;

		क्रम (i = 0; i < map->count; i++) अणु
			अचिन्हित दीर्घ address = (अचिन्हित दीर्घ)
				pfn_to_kaddr(page_to_pfn(map->pages[i]));
			BUG_ON(PageHighMem(map->pages[i]));

			gnttab_set_map_op(&map->kmap_ops[i], address, flags,
				map->grants[i].ref,
				map->grants[i].करोmid);
			gnttab_set_unmap_op(&map->kunmap_ops[i], address,
				flags, INVALID_GRANT_HANDLE);
		पूर्ण
	पूर्ण

	pr_debug("map %d+%d\n", map->index, map->count);
	err = gnttab_map_refs(map->map_ops, map->kmap_ops, map->pages,
			map->count);

	क्रम (i = 0; i < map->count; i++) अणु
		अगर (map->map_ops[i].status == GNTST_okay)
			map->unmap_ops[i].handle = map->map_ops[i].handle;
		अन्यथा अगर (!err)
			err = -EINVAL;

		अगर (map->flags & GNTMAP_device_map)
			map->unmap_ops[i].dev_bus_addr = map->map_ops[i].dev_bus_addr;

		अगर (use_ptemod) अणु
			अगर (map->kmap_ops[i].status == GNTST_okay)
				map->kunmap_ops[i].handle = map->kmap_ops[i].handle;
			अन्यथा अगर (!err)
				err = -EINVAL;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __unmap_grant_pages(काष्ठा gntdev_grant_map *map, पूर्णांक offset,
			       पूर्णांक pages)
अणु
	पूर्णांक i, err = 0;
	काष्ठा gntab_unmap_queue_data unmap_data;

	अगर (map->notअगरy.flags & UNMAP_NOTIFY_CLEAR_BYTE) अणु
		पूर्णांक pgno = (map->notअगरy.addr >> PAGE_SHIFT);
		अगर (pgno >= offset && pgno < offset + pages) अणु
			/* No need क्रम kmap, pages are in lowmem */
			uपूर्णांक8_t *पंचांगp = pfn_to_kaddr(page_to_pfn(map->pages[pgno]));
			पंचांगp[map->notअगरy.addr & (PAGE_SIZE-1)] = 0;
			map->notअगरy.flags &= ~UNMAP_NOTIFY_CLEAR_BYTE;
		पूर्ण
	पूर्ण

	unmap_data.unmap_ops = map->unmap_ops + offset;
	unmap_data.kunmap_ops = use_ptemod ? map->kunmap_ops + offset : शून्य;
	unmap_data.pages = map->pages + offset;
	unmap_data.count = pages;

	err = gnttab_unmap_refs_sync(&unmap_data);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < pages; i++) अणु
		अगर (map->unmap_ops[offset+i].status)
			err = -EINVAL;
		pr_debug("unmap handle=%d st=%d\n",
			map->unmap_ops[offset+i].handle,
			map->unmap_ops[offset+i].status);
		map->unmap_ops[offset+i].handle = INVALID_GRANT_HANDLE;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक unmap_grant_pages(काष्ठा gntdev_grant_map *map, पूर्णांक offset,
			     पूर्णांक pages)
अणु
	पूर्णांक range, err = 0;

	pr_debug("unmap %d+%d [%d+%d]\n", map->index, map->count, offset, pages);

	/* It is possible the requested range will have a "hole" where we
	 * alपढ़ोy unmapped some of the grants. Only unmap valid ranges.
	 */
	जबतक (pages && !err) अणु
		जबतक (pages &&
		       map->unmap_ops[offset].handle == INVALID_GRANT_HANDLE) अणु
			offset++;
			pages--;
		पूर्ण
		range = 0;
		जबतक (range < pages) अणु
			अगर (map->unmap_ops[offset + range].handle ==
			    INVALID_GRANT_HANDLE)
				अवरोध;
			range++;
		पूर्ण
		err = __unmap_grant_pages(map, offset, range);
		offset += range;
		pages -= range;
	पूर्ण

	वापस err;
पूर्ण

/* ------------------------------------------------------------------ */

अटल व्योम gntdev_vma_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा gntdev_grant_map *map = vma->vm_निजी_data;

	pr_debug("gntdev_vma_open %p\n", vma);
	refcount_inc(&map->users);
पूर्ण

अटल व्योम gntdev_vma_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा gntdev_grant_map *map = vma->vm_निजी_data;
	काष्ठा file *file = vma->vm_file;
	काष्ठा gntdev_priv *priv = file->निजी_data;

	pr_debug("gntdev_vma_close %p\n", vma);
	अगर (use_ptemod) अणु
		WARN_ON(map->vma != vma);
		mmu_पूर्णांकerval_notअगरier_हटाओ(&map->notअगरier);
		map->vma = शून्य;
	पूर्ण
	vma->vm_निजी_data = शून्य;
	gntdev_put_map(priv, map);
पूर्ण

अटल काष्ठा page *gntdev_vma_find_special_page(काष्ठा vm_area_काष्ठा *vma,
						 अचिन्हित दीर्घ addr)
अणु
	काष्ठा gntdev_grant_map *map = vma->vm_निजी_data;

	वापस map->pages[(addr - map->pages_vm_start) >> PAGE_SHIFT];
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा gntdev_vmops = अणु
	.खोलो = gntdev_vma_खोलो,
	.बंद = gntdev_vma_बंद,
	.find_special_page = gntdev_vma_find_special_page,
पूर्ण;

/* ------------------------------------------------------------------ */

अटल bool gntdev_invalidate(काष्ठा mmu_पूर्णांकerval_notअगरier *mn,
			      स्थिर काष्ठा mmu_notअगरier_range *range,
			      अचिन्हित दीर्घ cur_seq)
अणु
	काष्ठा gntdev_grant_map *map =
		container_of(mn, काष्ठा gntdev_grant_map, notअगरier);
	अचिन्हित दीर्घ mstart, mend;
	पूर्णांक err;

	अगर (!mmu_notअगरier_range_blockable(range))
		वापस false;

	/*
	 * If the VMA is split or otherwise changed the notअगरier is not
	 * updated, but we करोn't want to process VA's outside the modअगरied
	 * VMA. FIXME: It would be much more understandable to just prevent
	 * modअगरying the VMA in the first place.
	 */
	अगर (map->vma->vm_start >= range->end ||
	    map->vma->vm_end <= range->start)
		वापस true;

	mstart = max(range->start, map->vma->vm_start);
	mend = min(range->end, map->vma->vm_end);
	pr_debug("map %d+%d (%lx %lx), range %lx %lx, mrange %lx %lx\n",
			map->index, map->count,
			map->vma->vm_start, map->vma->vm_end,
			range->start, range->end, mstart, mend);
	err = unmap_grant_pages(map,
				(mstart - map->vma->vm_start) >> PAGE_SHIFT,
				(mend - mstart) >> PAGE_SHIFT);
	WARN_ON(err);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops gntdev_mmu_ops = अणु
	.invalidate = gntdev_invalidate,
पूर्ण;

/* ------------------------------------------------------------------ */

अटल पूर्णांक gntdev_खोलो(काष्ठा inode *inode, काष्ठा file *flip)
अणु
	काष्ठा gntdev_priv *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&priv->maps);
	mutex_init(&priv->lock);

#अगर_घोषित CONFIG_XEN_GNTDEV_DMABUF
	priv->dmabuf_priv = gntdev_dmabuf_init(flip);
	अगर (IS_ERR(priv->dmabuf_priv)) अणु
		पूर्णांक ret = PTR_ERR(priv->dmabuf_priv);

		kमुक्त(priv);
		वापस ret;
	पूर्ण
#पूर्ण_अगर

	flip->निजी_data = priv;
#अगर_घोषित CONFIG_XEN_GRANT_DMA_ALLOC
	priv->dma_dev = gntdev_miscdev.this_device;
	dma_coerce_mask_and_coherent(priv->dma_dev, DMA_BIT_MASK(64));
#पूर्ण_अगर
	pr_debug("priv %p\n", priv);

	वापस 0;
पूर्ण

अटल पूर्णांक gntdev_release(काष्ठा inode *inode, काष्ठा file *flip)
अणु
	काष्ठा gntdev_priv *priv = flip->निजी_data;
	काष्ठा gntdev_grant_map *map;

	pr_debug("priv %p\n", priv);

	mutex_lock(&priv->lock);
	जबतक (!list_empty(&priv->maps)) अणु
		map = list_entry(priv->maps.next,
				 काष्ठा gntdev_grant_map, next);
		list_del(&map->next);
		gntdev_put_map(शून्य /* alपढ़ोy हटाओd */, map);
	पूर्ण
	mutex_unlock(&priv->lock);

#अगर_घोषित CONFIG_XEN_GNTDEV_DMABUF
	gntdev_dmabuf_fini(priv->dmabuf_priv);
#पूर्ण_अगर

	kमुक्त(priv);
	वापस 0;
पूर्ण

अटल दीर्घ gntdev_ioctl_map_grant_ref(काष्ठा gntdev_priv *priv,
				       काष्ठा ioctl_gntdev_map_grant_ref __user *u)
अणु
	काष्ठा ioctl_gntdev_map_grant_ref op;
	काष्ठा gntdev_grant_map *map;
	पूर्णांक err;

	अगर (copy_from_user(&op, u, माप(op)) != 0)
		वापस -EFAULT;
	pr_debug("priv %p, add %d\n", priv, op.count);
	अगर (unlikely(gntdev_test_page_count(op.count)))
		वापस -EINVAL;

	err = -ENOMEM;
	map = gntdev_alloc_map(priv, op.count, 0 /* This is not a dma-buf. */);
	अगर (!map)
		वापस err;

	अगर (copy_from_user(map->grants, &u->refs,
			   माप(map->grants[0]) * op.count) != 0) अणु
		gntdev_put_map(शून्य, map);
		वापस -EFAULT;
	पूर्ण

	mutex_lock(&priv->lock);
	gntdev_add_map(priv, map);
	op.index = map->index << PAGE_SHIFT;
	mutex_unlock(&priv->lock);

	अगर (copy_to_user(u, &op, माप(op)) != 0)
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ gntdev_ioctl_unmap_grant_ref(काष्ठा gntdev_priv *priv,
					 काष्ठा ioctl_gntdev_unmap_grant_ref __user *u)
अणु
	काष्ठा ioctl_gntdev_unmap_grant_ref op;
	काष्ठा gntdev_grant_map *map;
	पूर्णांक err = -ENOENT;

	अगर (copy_from_user(&op, u, माप(op)) != 0)
		वापस -EFAULT;
	pr_debug("priv %p, del %d+%d\n", priv, (पूर्णांक)op.index, (पूर्णांक)op.count);

	mutex_lock(&priv->lock);
	map = gntdev_find_map_index(priv, op.index >> PAGE_SHIFT, op.count);
	अगर (map) अणु
		list_del(&map->next);
		err = 0;
	पूर्ण
	mutex_unlock(&priv->lock);
	अगर (map)
		gntdev_put_map(priv, map);
	वापस err;
पूर्ण

अटल दीर्घ gntdev_ioctl_get_offset_क्रम_vaddr(काष्ठा gntdev_priv *priv,
					      काष्ठा ioctl_gntdev_get_offset_क्रम_vaddr __user *u)
अणु
	काष्ठा ioctl_gntdev_get_offset_क्रम_vaddr op;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा gntdev_grant_map *map;
	पूर्णांक rv = -EINVAL;

	अगर (copy_from_user(&op, u, माप(op)) != 0)
		वापस -EFAULT;
	pr_debug("priv %p, offset for vaddr %lx\n", priv, (अचिन्हित दीर्घ)op.vaddr);

	mmap_पढ़ो_lock(current->mm);
	vma = find_vma(current->mm, op.vaddr);
	अगर (!vma || vma->vm_ops != &gntdev_vmops)
		जाओ out_unlock;

	map = vma->vm_निजी_data;
	अगर (!map)
		जाओ out_unlock;

	op.offset = map->index << PAGE_SHIFT;
	op.count = map->count;
	rv = 0;

 out_unlock:
	mmap_पढ़ो_unlock(current->mm);

	अगर (rv == 0 && copy_to_user(u, &op, माप(op)) != 0)
		वापस -EFAULT;
	वापस rv;
पूर्ण

अटल दीर्घ gntdev_ioctl_notअगरy(काष्ठा gntdev_priv *priv, व्योम __user *u)
अणु
	काष्ठा ioctl_gntdev_unmap_notअगरy op;
	काष्ठा gntdev_grant_map *map;
	पूर्णांक rc;
	पूर्णांक out_flags;
	evtchn_port_t out_event;

	अगर (copy_from_user(&op, u, माप(op)))
		वापस -EFAULT;

	अगर (op.action & ~(UNMAP_NOTIFY_CLEAR_BYTE|UNMAP_NOTIFY_SEND_EVENT))
		वापस -EINVAL;

	/* We need to grab a reference to the event channel we are going to use
	 * to send the notअगरy beक्रमe releasing the reference we may alपढ़ोy have
	 * (अगर someone has called this ioctl twice). This is required so that
	 * it is possible to change the clear_byte part of the notअगरication
	 * without disturbing the event channel part, which may now be the last
	 * reference to that event channel.
	 */
	अगर (op.action & UNMAP_NOTIFY_SEND_EVENT) अणु
		अगर (evtchn_get(op.event_channel_port))
			वापस -EINVAL;
	पूर्ण

	out_flags = op.action;
	out_event = op.event_channel_port;

	mutex_lock(&priv->lock);

	list_क्रम_each_entry(map, &priv->maps, next) अणु
		uपूर्णांक64_t begin = map->index << PAGE_SHIFT;
		uपूर्णांक64_t end = (map->index + map->count) << PAGE_SHIFT;
		अगर (op.index >= begin && op.index < end)
			जाओ found;
	पूर्ण
	rc = -ENOENT;
	जाओ unlock_out;

 found:
	अगर ((op.action & UNMAP_NOTIFY_CLEAR_BYTE) &&
			(map->flags & GNTMAP_पढ़ोonly)) अणु
		rc = -EINVAL;
		जाओ unlock_out;
	पूर्ण

	out_flags = map->notअगरy.flags;
	out_event = map->notअगरy.event;

	map->notअगरy.flags = op.action;
	map->notअगरy.addr = op.index - (map->index << PAGE_SHIFT);
	map->notअगरy.event = op.event_channel_port;

	rc = 0;

 unlock_out:
	mutex_unlock(&priv->lock);

	/* Drop the reference to the event channel we did not save in the map */
	अगर (out_flags & UNMAP_NOTIFY_SEND_EVENT)
		evtchn_put(out_event);

	वापस rc;
पूर्ण

#घोषणा GNTDEV_COPY_BATCH 16

काष्ठा gntdev_copy_batch अणु
	काष्ठा gnttab_copy ops[GNTDEV_COPY_BATCH];
	काष्ठा page *pages[GNTDEV_COPY_BATCH];
	s16 __user *status[GNTDEV_COPY_BATCH];
	अचिन्हित पूर्णांक nr_ops;
	अचिन्हित पूर्णांक nr_pages;
	bool ग_लिखोable;
पूर्ण;

अटल पूर्णांक gntdev_get_page(काष्ठा gntdev_copy_batch *batch, व्योम __user *virt,
				अचिन्हित दीर्घ *gfn)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)virt;
	काष्ठा page *page;
	अचिन्हित दीर्घ xen_pfn;
	पूर्णांक ret;

	ret = pin_user_pages_fast(addr, 1, batch->ग_लिखोable ? FOLL_WRITE : 0, &page);
	अगर (ret < 0)
		वापस ret;

	batch->pages[batch->nr_pages++] = page;

	xen_pfn = page_to_xen_pfn(page) + XEN_PFN_DOWN(addr & ~PAGE_MASK);
	*gfn = pfn_to_gfn(xen_pfn);

	वापस 0;
पूर्ण

अटल व्योम gntdev_put_pages(काष्ठा gntdev_copy_batch *batch)
अणु
	unpin_user_pages_dirty_lock(batch->pages, batch->nr_pages, batch->ग_लिखोable);
	batch->nr_pages = 0;
	batch->ग_लिखोable = false;
पूर्ण

अटल पूर्णांक gntdev_copy(काष्ठा gntdev_copy_batch *batch)
अणु
	अचिन्हित पूर्णांक i;

	gnttab_batch_copy(batch->ops, batch->nr_ops);
	gntdev_put_pages(batch);

	/*
	 * For each completed op, update the status अगर the op failed
	 * and all previous ops क्रम the segment were successful.
	 */
	क्रम (i = 0; i < batch->nr_ops; i++) अणु
		s16 status = batch->ops[i].status;
		s16 old_status;

		अगर (status == GNTST_okay)
			जारी;

		अगर (__get_user(old_status, batch->status[i]))
			वापस -EFAULT;

		अगर (old_status != GNTST_okay)
			जारी;

		अगर (__put_user(status, batch->status[i]))
			वापस -EFAULT;
	पूर्ण

	batch->nr_ops = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक gntdev_grant_copy_seg(काष्ठा gntdev_copy_batch *batch,
				 काष्ठा gntdev_grant_copy_segment *seg,
				 s16 __user *status)
अणु
	uपूर्णांक16_t copied = 0;

	/*
	 * Disallow local -> local copies since there is only space in
	 * batch->pages क्रम one page per-op and this would be a very
	 * expensive स_नकल().
	 */
	अगर (!(seg->flags & (GNTCOPY_source_gref | GNTCOPY_dest_gref)))
		वापस -EINVAL;

	/* Can't cross page अगर source/dest is a grant ref. */
	अगर (seg->flags & GNTCOPY_source_gref) अणु
		अगर (seg->source.क्रमeign.offset + seg->len > XEN_PAGE_SIZE)
			वापस -EINVAL;
	पूर्ण
	अगर (seg->flags & GNTCOPY_dest_gref) अणु
		अगर (seg->dest.क्रमeign.offset + seg->len > XEN_PAGE_SIZE)
			वापस -EINVAL;
	पूर्ण

	अगर (put_user(GNTST_okay, status))
		वापस -EFAULT;

	जबतक (copied < seg->len) अणु
		काष्ठा gnttab_copy *op;
		व्योम __user *virt;
		माप_प्रकार len, off;
		अचिन्हित दीर्घ gfn;
		पूर्णांक ret;

		अगर (batch->nr_ops >= GNTDEV_COPY_BATCH) अणु
			ret = gntdev_copy(batch);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		len = seg->len - copied;

		op = &batch->ops[batch->nr_ops];
		op->flags = 0;

		अगर (seg->flags & GNTCOPY_source_gref) अणु
			op->source.u.ref = seg->source.क्रमeign.ref;
			op->source.करोmid = seg->source.क्रमeign.करोmid;
			op->source.offset = seg->source.क्रमeign.offset + copied;
			op->flags |= GNTCOPY_source_gref;
		पूर्ण अन्यथा अणु
			virt = seg->source.virt + copied;
			off = (अचिन्हित दीर्घ)virt & ~XEN_PAGE_MASK;
			len = min(len, (माप_प्रकार)XEN_PAGE_SIZE - off);
			batch->ग_लिखोable = false;

			ret = gntdev_get_page(batch, virt, &gfn);
			अगर (ret < 0)
				वापस ret;

			op->source.u.gmfn = gfn;
			op->source.करोmid = DOMID_SELF;
			op->source.offset = off;
		पूर्ण

		अगर (seg->flags & GNTCOPY_dest_gref) अणु
			op->dest.u.ref = seg->dest.क्रमeign.ref;
			op->dest.करोmid = seg->dest.क्रमeign.करोmid;
			op->dest.offset = seg->dest.क्रमeign.offset + copied;
			op->flags |= GNTCOPY_dest_gref;
		पूर्ण अन्यथा अणु
			virt = seg->dest.virt + copied;
			off = (अचिन्हित दीर्घ)virt & ~XEN_PAGE_MASK;
			len = min(len, (माप_प्रकार)XEN_PAGE_SIZE - off);
			batch->ग_लिखोable = true;

			ret = gntdev_get_page(batch, virt, &gfn);
			अगर (ret < 0)
				वापस ret;

			op->dest.u.gmfn = gfn;
			op->dest.करोmid = DOMID_SELF;
			op->dest.offset = off;
		पूर्ण

		op->len = len;
		copied += len;

		batch->status[batch->nr_ops] = status;
		batch->nr_ops++;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ gntdev_ioctl_grant_copy(काष्ठा gntdev_priv *priv, व्योम __user *u)
अणु
	काष्ठा ioctl_gntdev_grant_copy copy;
	काष्ठा gntdev_copy_batch batch;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (copy_from_user(&copy, u, माप(copy)))
		वापस -EFAULT;

	batch.nr_ops = 0;
	batch.nr_pages = 0;

	क्रम (i = 0; i < copy.count; i++) अणु
		काष्ठा gntdev_grant_copy_segment seg;

		अगर (copy_from_user(&seg, &copy.segments[i], माप(seg))) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		ret = gntdev_grant_copy_seg(&batch, &seg, &copy.segments[i].status);
		अगर (ret < 0)
			जाओ out;

		cond_resched();
	पूर्ण
	अगर (batch.nr_ops)
		ret = gntdev_copy(&batch);
	वापस ret;

  out:
	gntdev_put_pages(&batch);
	वापस ret;
पूर्ण

अटल दीर्घ gntdev_ioctl(काष्ठा file *flip,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा gntdev_priv *priv = flip->निजी_data;
	व्योम __user *ptr = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल IOCTL_GNTDEV_MAP_GRANT_REF:
		वापस gntdev_ioctl_map_grant_ref(priv, ptr);

	हाल IOCTL_GNTDEV_UNMAP_GRANT_REF:
		वापस gntdev_ioctl_unmap_grant_ref(priv, ptr);

	हाल IOCTL_GNTDEV_GET_OFFSET_FOR_VADDR:
		वापस gntdev_ioctl_get_offset_क्रम_vaddr(priv, ptr);

	हाल IOCTL_GNTDEV_SET_UNMAP_NOTIFY:
		वापस gntdev_ioctl_notअगरy(priv, ptr);

	हाल IOCTL_GNTDEV_GRANT_COPY:
		वापस gntdev_ioctl_grant_copy(priv, ptr);

#अगर_घोषित CONFIG_XEN_GNTDEV_DMABUF
	हाल IOCTL_GNTDEV_DMABUF_EXP_FROM_REFS:
		वापस gntdev_ioctl_dmabuf_exp_from_refs(priv, use_ptemod, ptr);

	हाल IOCTL_GNTDEV_DMABUF_EXP_WAIT_RELEASED:
		वापस gntdev_ioctl_dmabuf_exp_रुको_released(priv, ptr);

	हाल IOCTL_GNTDEV_DMABUF_IMP_TO_REFS:
		वापस gntdev_ioctl_dmabuf_imp_to_refs(priv, ptr);

	हाल IOCTL_GNTDEV_DMABUF_IMP_RELEASE:
		वापस gntdev_ioctl_dmabuf_imp_release(priv, ptr);
#पूर्ण_अगर

	शेष:
		pr_debug("priv %p, unknown cmd %x\n", priv, cmd);
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gntdev_mmap(काष्ठा file *flip, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा gntdev_priv *priv = flip->निजी_data;
	पूर्णांक index = vma->vm_pgoff;
	पूर्णांक count = vma_pages(vma);
	काष्ठा gntdev_grant_map *map;
	पूर्णांक err = -EINVAL;

	अगर ((vma->vm_flags & VM_WRITE) && !(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	pr_debug("map %d+%d at %lx (pgoff %lx)\n",
			index, count, vma->vm_start, vma->vm_pgoff);

	mutex_lock(&priv->lock);
	map = gntdev_find_map_index(priv, index, count);
	अगर (!map)
		जाओ unlock_out;
	अगर (use_ptemod && map->vma)
		जाओ unlock_out;
	refcount_inc(&map->users);

	vma->vm_ops = &gntdev_vmops;

	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP | VM_MIXEDMAP;

	अगर (use_ptemod)
		vma->vm_flags |= VM_DONTCOPY;

	vma->vm_निजी_data = map;
	अगर (map->flags) अणु
		अगर ((vma->vm_flags & VM_WRITE) &&
				(map->flags & GNTMAP_पढ़ोonly))
			जाओ out_unlock_put;
	पूर्ण अन्यथा अणु
		map->flags = GNTMAP_host_map;
		अगर (!(vma->vm_flags & VM_WRITE))
			map->flags |= GNTMAP_पढ़ोonly;
	पूर्ण

	अगर (use_ptemod) अणु
		map->vma = vma;
		err = mmu_पूर्णांकerval_notअगरier_insert_locked(
			&map->notअगरier, vma->vm_mm, vma->vm_start,
			vma->vm_end - vma->vm_start, &gntdev_mmu_ops);
		अगर (err) अणु
			map->vma = शून्य;
			जाओ out_unlock_put;
		पूर्ण
	पूर्ण
	mutex_unlock(&priv->lock);

	अगर (use_ptemod) अणु
		/*
		 * gntdev takes the address of the PTE in find_grant_ptes() and
		 * passes it to the hypervisor in gntdev_map_grant_pages(). The
		 * purpose of the notअगरier is to prevent the hypervisor poपूर्णांकer
		 * to the PTE from going stale.
		 *
		 * Since this vma's mappings can't be touched without the
		 * mmap_lock, and we are holding it now, there is no need क्रम
		 * the notअगरier_range locking pattern.
		 */
		mmu_पूर्णांकerval_पढ़ो_begin(&map->notअगरier);

		map->pages_vm_start = vma->vm_start;
		err = apply_to_page_range(vma->vm_mm, vma->vm_start,
					  vma->vm_end - vma->vm_start,
					  find_grant_ptes, map);
		अगर (err) अणु
			pr_warn("find_grant_ptes() failure.\n");
			जाओ out_put_map;
		पूर्ण
	पूर्ण

	err = gntdev_map_grant_pages(map);
	अगर (err)
		जाओ out_put_map;

	अगर (!use_ptemod) अणु
		err = vm_map_pages_zero(vma, map->pages, map->count);
		अगर (err)
			जाओ out_put_map;
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_X86
		/*
		 * If the PTEs were not made special by the grant map
		 * hypercall, करो so here.
		 *
		 * This is racy since the mapping is alपढ़ोy visible
		 * to userspace but userspace should be well-behaved
		 * enough to not touch it until the mmap() call
		 * वापसs.
		 */
		अगर (!xen_feature(XENFEAT_gnttab_map_avail_bits)) अणु
			apply_to_page_range(vma->vm_mm, vma->vm_start,
					    vma->vm_end - vma->vm_start,
					    set_grant_ptes_as_special, शून्य);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	वापस 0;

unlock_out:
	mutex_unlock(&priv->lock);
	वापस err;

out_unlock_put:
	mutex_unlock(&priv->lock);
out_put_map:
	अगर (use_ptemod) अणु
		unmap_grant_pages(map, 0, map->count);
		अगर (map->vma) अणु
			mmu_पूर्णांकerval_notअगरier_हटाओ(&map->notअगरier);
			map->vma = शून्य;
		पूर्ण
	पूर्ण
	gntdev_put_map(priv, map);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations gntdev_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = gntdev_खोलो,
	.release = gntdev_release,
	.mmap = gntdev_mmap,
	.unlocked_ioctl = gntdev_ioctl
पूर्ण;

अटल काष्ठा miscdevice gntdev_miscdev = अणु
	.minor        = MISC_DYNAMIC_MINOR,
	.name         = "xen/gntdev",
	.fops         = &gntdev_fops,
पूर्ण;

/* ------------------------------------------------------------------ */

अटल पूर्णांक __init gntdev_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	use_ptemod = !xen_feature(XENFEAT_स्वतः_translated_physmap);

	err = misc_रेजिस्टर(&gntdev_miscdev);
	अगर (err != 0) अणु
		pr_err("Could not register gntdev device\n");
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास gntdev_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&gntdev_miscdev);
पूर्ण

module_init(gntdev_init);
module_निकास(gntdev_निकास);

/* ------------------------------------------------------------------ */
