<शैली गुरु>
/*
 * KVMGT - the implementation of Intel mediated pass-through framework क्रम KVM
 *
 * Copyright(c) 2014-2016 Intel Corporation. All rights reserved.
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *    Jike Song <jike.song@पूर्णांकel.com>
 *    Xiaoguang Chen <xiaoguang.chen@पूर्णांकel.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/mm.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/eventfd.h>
#समावेश <linux/uuid.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/mdev.h>
#समावेश <linux/debugfs.h>

#समावेश <linux/nospec.h>

#समावेश "i915_drv.h"
#समावेश "gvt.h"

अटल स्थिर काष्ठा पूर्णांकel_gvt_ops *पूर्णांकel_gvt_ops;

/* helper macros copied from vfio-pci */
#घोषणा VFIO_PCI_OFFSET_SHIFT   40
#घोषणा VFIO_PCI_OFFSET_TO_INDEX(off)   (off >> VFIO_PCI_OFFSET_SHIFT)
#घोषणा VFIO_PCI_INDEX_TO_OFFSET(index) ((u64)(index) << VFIO_PCI_OFFSET_SHIFT)
#घोषणा VFIO_PCI_OFFSET_MASK    (((u64)(1) << VFIO_PCI_OFFSET_SHIFT) - 1)

#घोषणा EDID_BLOB_OFFSET (PAGE_SIZE/2)

#घोषणा OPREGION_SIGNATURE "IntelGraphicsMem"

काष्ठा vfio_region;
काष्ठा पूर्णांकel_vgpu_regops अणु
	माप_प्रकार (*rw)(काष्ठा पूर्णांकel_vgpu *vgpu, अक्षर *buf,
			माप_प्रकार count, loff_t *ppos, bool isग_लिखो);
	व्योम (*release)(काष्ठा पूर्णांकel_vgpu *vgpu,
			काष्ठा vfio_region *region);
पूर्ण;

काष्ठा vfio_region अणु
	u32				type;
	u32				subtype;
	माप_प्रकार				size;
	u32				flags;
	स्थिर काष्ठा पूर्णांकel_vgpu_regops	*ops;
	व्योम				*data;
पूर्ण;

काष्ठा vfio_edid_region अणु
	काष्ठा vfio_region_gfx_edid vfio_edid_regs;
	व्योम *edid_blob;
पूर्ण;

काष्ठा kvmgt_pgfn अणु
	gfn_t gfn;
	काष्ठा hlist_node hnode;
पूर्ण;

काष्ठा kvmgt_guest_info अणु
	काष्ठा kvm *kvm;
	काष्ठा पूर्णांकel_vgpu *vgpu;
	काष्ठा kvm_page_track_notअगरier_node track_node;
#घोषणा NR_BKT (1 << 18)
	काष्ठा hlist_head ptable[NR_BKT];
#अघोषित NR_BKT
	काष्ठा dentry *debugfs_cache_entries;
पूर्ण;

काष्ठा gvt_dma अणु
	काष्ठा पूर्णांकel_vgpu *vgpu;
	काष्ठा rb_node gfn_node;
	काष्ठा rb_node dma_addr_node;
	gfn_t gfn;
	dma_addr_t dma_addr;
	अचिन्हित दीर्घ size;
	काष्ठा kref ref;
पूर्ण;

काष्ठा kvmgt_vdev अणु
	काष्ठा पूर्णांकel_vgpu *vgpu;
	काष्ठा mdev_device *mdev;
	काष्ठा vfio_region *region;
	पूर्णांक num_regions;
	काष्ठा eventfd_ctx *पूर्णांकx_trigger;
	काष्ठा eventfd_ctx *msi_trigger;

	/*
	 * Two caches are used to aव्योम mapping duplicated pages (eg.
	 * scratch pages). This help to reduce dma setup overhead.
	 */
	काष्ठा rb_root gfn_cache;
	काष्ठा rb_root dma_addr_cache;
	अचिन्हित दीर्घ nr_cache_entries;
	काष्ठा mutex cache_lock;

	काष्ठा notअगरier_block iommu_notअगरier;
	काष्ठा notअगरier_block group_notअगरier;
	काष्ठा kvm *kvm;
	काष्ठा work_काष्ठा release_work;
	atomic_t released;
	काष्ठा vfio_device *vfio_device;
	काष्ठा vfio_group *vfio_group;
पूर्ण;

अटल अंतरभूत काष्ठा kvmgt_vdev *kvmgt_vdev(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	वापस पूर्णांकel_vgpu_vdev(vgpu);
पूर्ण

अटल अंतरभूत bool handle_valid(अचिन्हित दीर्घ handle)
अणु
	वापस !!(handle & ~0xff);
पूर्ण

अटल sमाप_प्रकार available_instances_show(काष्ठा mdev_type *mtype,
					काष्ठा mdev_type_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_vgpu_type *type;
	अचिन्हित पूर्णांक num = 0;
	काष्ठा पूर्णांकel_gvt *gvt = kdev_to_i915(mtype_get_parent_dev(mtype))->gvt;

	type = &gvt->types[mtype_get_type_group_id(mtype)];
	अगर (!type)
		num = 0;
	अन्यथा
		num = type->avail_instance;

	वापस प्र_लिखो(buf, "%u\n", num);
पूर्ण

अटल sमाप_प्रकार device_api_show(काष्ठा mdev_type *mtype,
			       काष्ठा mdev_type_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", VFIO_DEVICE_API_PCI_STRING);
पूर्ण

अटल sमाप_प्रकार description_show(काष्ठा mdev_type *mtype,
				काष्ठा mdev_type_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_vgpu_type *type;
	काष्ठा पूर्णांकel_gvt *gvt = kdev_to_i915(mtype_get_parent_dev(mtype))->gvt;

	type = &gvt->types[mtype_get_type_group_id(mtype)];
	अगर (!type)
		वापस 0;

	वापस प्र_लिखो(buf, "low_gm_size: %dMB\nhigh_gm_size: %dMB\n"
		       "fence: %d\nresolution: %s\n"
		       "weight: %d\n",
		       BYTES_TO_MB(type->low_gm_size),
		       BYTES_TO_MB(type->high_gm_size),
		       type->fence, vgpu_edid_str(type->resolution),
		       type->weight);
पूर्ण

अटल MDEV_TYPE_ATTR_RO(available_instances);
अटल MDEV_TYPE_ATTR_RO(device_api);
अटल MDEV_TYPE_ATTR_RO(description);

अटल काष्ठा attribute *gvt_type_attrs[] = अणु
	&mdev_type_attr_available_instances.attr,
	&mdev_type_attr_device_api.attr,
	&mdev_type_attr_description.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group *gvt_vgpu_type_groups[] = अणु
	[0 ... NR_MAX_INTEL_VGPU_TYPES - 1] = शून्य,
पूर्ण;

अटल पूर्णांक पूर्णांकel_gvt_init_vgpu_type_groups(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	पूर्णांक i, j;
	काष्ठा पूर्णांकel_vgpu_type *type;
	काष्ठा attribute_group *group;

	क्रम (i = 0; i < gvt->num_types; i++) अणु
		type = &gvt->types[i];

		group = kzalloc(माप(काष्ठा attribute_group), GFP_KERNEL);
		अगर (!group)
			जाओ unwind;

		group->name = type->name;
		group->attrs = gvt_type_attrs;
		gvt_vgpu_type_groups[i] = group;
	पूर्ण

	वापस 0;

unwind:
	क्रम (j = 0; j < i; j++) अणु
		group = gvt_vgpu_type_groups[j];
		kमुक्त(group);
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल व्योम पूर्णांकel_gvt_cleanup_vgpu_type_groups(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	पूर्णांक i;
	काष्ठा attribute_group *group;

	क्रम (i = 0; i < gvt->num_types; i++) अणु
		group = gvt_vgpu_type_groups[i];
		gvt_vgpu_type_groups[i] = शून्य;
		kमुक्त(group);
	पूर्ण
पूर्ण

अटल पूर्णांक kvmgt_guest_init(काष्ठा mdev_device *mdev);
अटल व्योम पूर्णांकel_vgpu_release_work(काष्ठा work_काष्ठा *work);
अटल bool kvmgt_guest_निकास(काष्ठा kvmgt_guest_info *info);

अटल व्योम gvt_unpin_guest_page(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn,
		अचिन्हित दीर्घ size)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);
	पूर्णांक total_pages;
	पूर्णांक npage;
	पूर्णांक ret;

	total_pages = roundup(size, PAGE_SIZE) / PAGE_SIZE;

	क्रम (npage = 0; npage < total_pages; npage++) अणु
		अचिन्हित दीर्घ cur_gfn = gfn + npage;

		ret = vfio_group_unpin_pages(vdev->vfio_group, &cur_gfn, 1);
		drm_WARN_ON(&i915->drm, ret != 1);
	पूर्ण
पूर्ण

/* Pin a normal or compound guest page क्रम dma. */
अटल पूर्णांक gvt_pin_guest_page(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn,
		अचिन्हित दीर्घ size, काष्ठा page **page)
अणु
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);
	अचिन्हित दीर्घ base_pfn = 0;
	पूर्णांक total_pages;
	पूर्णांक npage;
	पूर्णांक ret;

	total_pages = roundup(size, PAGE_SIZE) / PAGE_SIZE;
	/*
	 * We pin the pages one-by-one to aव्योम allocating a big arrary
	 * on stack to hold pfns.
	 */
	क्रम (npage = 0; npage < total_pages; npage++) अणु
		अचिन्हित दीर्घ cur_gfn = gfn + npage;
		अचिन्हित दीर्घ pfn;

		ret = vfio_group_pin_pages(vdev->vfio_group, &cur_gfn, 1,
					   IOMMU_READ | IOMMU_WRITE, &pfn);
		अगर (ret != 1) अणु
			gvt_vgpu_err("vfio_pin_pages failed for gfn 0x%lx, ret %d\n",
				     cur_gfn, ret);
			जाओ err;
		पूर्ण

		अगर (!pfn_valid(pfn)) अणु
			gvt_vgpu_err("pfn 0x%lx is not mem backed\n", pfn);
			npage++;
			ret = -EFAULT;
			जाओ err;
		पूर्ण

		अगर (npage == 0)
			base_pfn = pfn;
		अन्यथा अगर (base_pfn + npage != pfn) अणु
			gvt_vgpu_err("The pages are not continuous\n");
			ret = -EINVAL;
			npage++;
			जाओ err;
		पूर्ण
	पूर्ण

	*page = pfn_to_page(base_pfn);
	वापस 0;
err:
	gvt_unpin_guest_page(vgpu, gfn, npage * PAGE_SIZE);
	वापस ret;
पूर्ण

अटल पूर्णांक gvt_dma_map_page(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn,
		dma_addr_t *dma_addr, अचिन्हित दीर्घ size)
अणु
	काष्ठा device *dev = vgpu->gvt->gt->i915->drm.dev;
	काष्ठा page *page = शून्य;
	पूर्णांक ret;

	ret = gvt_pin_guest_page(vgpu, gfn, size, &page);
	अगर (ret)
		वापस ret;

	/* Setup DMA mapping. */
	*dma_addr = dma_map_page(dev, page, 0, size, PCI_DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, *dma_addr)) अणु
		gvt_vgpu_err("DMA mapping failed for pfn 0x%lx, ret %d\n",
			     page_to_pfn(page), ret);
		gvt_unpin_guest_page(vgpu, gfn, size);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gvt_dma_unmap_page(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ gfn,
		dma_addr_t dma_addr, अचिन्हित दीर्घ size)
अणु
	काष्ठा device *dev = vgpu->gvt->gt->i915->drm.dev;

	dma_unmap_page(dev, dma_addr, size, PCI_DMA_BIसूचीECTIONAL);
	gvt_unpin_guest_page(vgpu, gfn, size);
पूर्ण

अटल काष्ठा gvt_dma *__gvt_cache_find_dma_addr(काष्ठा पूर्णांकel_vgpu *vgpu,
		dma_addr_t dma_addr)
अणु
	काष्ठा rb_node *node = kvmgt_vdev(vgpu)->dma_addr_cache.rb_node;
	काष्ठा gvt_dma *itr;

	जबतक (node) अणु
		itr = rb_entry(node, काष्ठा gvt_dma, dma_addr_node);

		अगर (dma_addr < itr->dma_addr)
			node = node->rb_left;
		अन्यथा अगर (dma_addr > itr->dma_addr)
			node = node->rb_right;
		अन्यथा
			वापस itr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा gvt_dma *__gvt_cache_find_gfn(काष्ठा पूर्णांकel_vgpu *vgpu, gfn_t gfn)
अणु
	काष्ठा rb_node *node = kvmgt_vdev(vgpu)->gfn_cache.rb_node;
	काष्ठा gvt_dma *itr;

	जबतक (node) अणु
		itr = rb_entry(node, काष्ठा gvt_dma, gfn_node);

		अगर (gfn < itr->gfn)
			node = node->rb_left;
		अन्यथा अगर (gfn > itr->gfn)
			node = node->rb_right;
		अन्यथा
			वापस itr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक __gvt_cache_add(काष्ठा पूर्णांकel_vgpu *vgpu, gfn_t gfn,
		dma_addr_t dma_addr, अचिन्हित दीर्घ size)
अणु
	काष्ठा gvt_dma *new, *itr;
	काष्ठा rb_node **link, *parent = शून्य;
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);

	new = kzalloc(माप(काष्ठा gvt_dma), GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;

	new->vgpu = vgpu;
	new->gfn = gfn;
	new->dma_addr = dma_addr;
	new->size = size;
	kref_init(&new->ref);

	/* gfn_cache maps gfn to काष्ठा gvt_dma. */
	link = &vdev->gfn_cache.rb_node;
	जबतक (*link) अणु
		parent = *link;
		itr = rb_entry(parent, काष्ठा gvt_dma, gfn_node);

		अगर (gfn < itr->gfn)
			link = &parent->rb_left;
		अन्यथा
			link = &parent->rb_right;
	पूर्ण
	rb_link_node(&new->gfn_node, parent, link);
	rb_insert_color(&new->gfn_node, &vdev->gfn_cache);

	/* dma_addr_cache maps dma addr to काष्ठा gvt_dma. */
	parent = शून्य;
	link = &vdev->dma_addr_cache.rb_node;
	जबतक (*link) अणु
		parent = *link;
		itr = rb_entry(parent, काष्ठा gvt_dma, dma_addr_node);

		अगर (dma_addr < itr->dma_addr)
			link = &parent->rb_left;
		अन्यथा
			link = &parent->rb_right;
	पूर्ण
	rb_link_node(&new->dma_addr_node, parent, link);
	rb_insert_color(&new->dma_addr_node, &vdev->dma_addr_cache);

	vdev->nr_cache_entries++;
	वापस 0;
पूर्ण

अटल व्योम __gvt_cache_हटाओ_entry(काष्ठा पूर्णांकel_vgpu *vgpu,
				काष्ठा gvt_dma *entry)
अणु
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);

	rb_erase(&entry->gfn_node, &vdev->gfn_cache);
	rb_erase(&entry->dma_addr_node, &vdev->dma_addr_cache);
	kमुक्त(entry);
	vdev->nr_cache_entries--;
पूर्ण

अटल व्योम gvt_cache_destroy(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा gvt_dma *dma;
	काष्ठा rb_node *node = शून्य;
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);

	क्रम (;;) अणु
		mutex_lock(&vdev->cache_lock);
		node = rb_first(&vdev->gfn_cache);
		अगर (!node) अणु
			mutex_unlock(&vdev->cache_lock);
			अवरोध;
		पूर्ण
		dma = rb_entry(node, काष्ठा gvt_dma, gfn_node);
		gvt_dma_unmap_page(vgpu, dma->gfn, dma->dma_addr, dma->size);
		__gvt_cache_हटाओ_entry(vgpu, dma);
		mutex_unlock(&vdev->cache_lock);
	पूर्ण
पूर्ण

अटल व्योम gvt_cache_init(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);

	vdev->gfn_cache = RB_ROOT;
	vdev->dma_addr_cache = RB_ROOT;
	vdev->nr_cache_entries = 0;
	mutex_init(&vdev->cache_lock);
पूर्ण

अटल व्योम kvmgt_protect_table_init(काष्ठा kvmgt_guest_info *info)
अणु
	hash_init(info->ptable);
पूर्ण

अटल व्योम kvmgt_protect_table_destroy(काष्ठा kvmgt_guest_info *info)
अणु
	काष्ठा kvmgt_pgfn *p;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;

	hash_क्रम_each_safe(info->ptable, i, पंचांगp, p, hnode) अणु
		hash_del(&p->hnode);
		kमुक्त(p);
	पूर्ण
पूर्ण

अटल काष्ठा kvmgt_pgfn *
__kvmgt_protect_table_find(काष्ठा kvmgt_guest_info *info, gfn_t gfn)
अणु
	काष्ठा kvmgt_pgfn *p, *res = शून्य;

	hash_क्रम_each_possible(info->ptable, p, hnode, gfn) अणु
		अगर (gfn == p->gfn) अणु
			res = p;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल bool kvmgt_gfn_is_ग_लिखो_रक्षित(काष्ठा kvmgt_guest_info *info,
				gfn_t gfn)
अणु
	काष्ठा kvmgt_pgfn *p;

	p = __kvmgt_protect_table_find(info, gfn);
	वापस !!p;
पूर्ण

अटल व्योम kvmgt_protect_table_add(काष्ठा kvmgt_guest_info *info, gfn_t gfn)
अणु
	काष्ठा kvmgt_pgfn *p;

	अगर (kvmgt_gfn_is_ग_लिखो_रक्षित(info, gfn))
		वापस;

	p = kzalloc(माप(काष्ठा kvmgt_pgfn), GFP_ATOMIC);
	अगर (WARN(!p, "gfn: 0x%llx\n", gfn))
		वापस;

	p->gfn = gfn;
	hash_add(info->ptable, &p->hnode, gfn);
पूर्ण

अटल व्योम kvmgt_protect_table_del(काष्ठा kvmgt_guest_info *info,
				gfn_t gfn)
अणु
	काष्ठा kvmgt_pgfn *p;

	p = __kvmgt_protect_table_find(info, gfn);
	अगर (p) अणु
		hash_del(&p->hnode);
		kमुक्त(p);
	पूर्ण
पूर्ण

अटल माप_प्रकार पूर्णांकel_vgpu_reg_rw_opregion(काष्ठा पूर्णांकel_vgpu *vgpu, अक्षर *buf,
		माप_प्रकार count, loff_t *ppos, bool isग_लिखो)
अणु
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);
	अचिन्हित पूर्णांक i = VFIO_PCI_OFFSET_TO_INDEX(*ppos) -
			VFIO_PCI_NUM_REGIONS;
	व्योम *base = vdev->region[i].data;
	loff_t pos = *ppos & VFIO_PCI_OFFSET_MASK;


	अगर (pos >= vdev->region[i].size || isग_लिखो) अणु
		gvt_vgpu_err("invalid op or offset for Intel vgpu OpRegion\n");
		वापस -EINVAL;
	पूर्ण
	count = min(count, (माप_प्रकार)(vdev->region[i].size - pos));
	स_नकल(buf, base + pos, count);

	वापस count;
पूर्ण

अटल व्योम पूर्णांकel_vgpu_reg_release_opregion(काष्ठा पूर्णांकel_vgpu *vgpu,
		काष्ठा vfio_region *region)
अणु
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_vgpu_regops पूर्णांकel_vgpu_regops_opregion = अणु
	.rw = पूर्णांकel_vgpu_reg_rw_opregion,
	.release = पूर्णांकel_vgpu_reg_release_opregion,
पूर्ण;

अटल पूर्णांक handle_edid_regs(काष्ठा पूर्णांकel_vgpu *vgpu,
			काष्ठा vfio_edid_region *region, अक्षर *buf,
			माप_प्रकार count, u16 offset, bool is_ग_लिखो)
अणु
	काष्ठा vfio_region_gfx_edid *regs = &region->vfio_edid_regs;
	अचिन्हित पूर्णांक data;

	अगर (offset + count > माप(*regs))
		वापस -EINVAL;

	अगर (count != 4)
		वापस -EINVAL;

	अगर (is_ग_लिखो) अणु
		data = *((अचिन्हित पूर्णांक *)buf);
		चयन (offset) अणु
		हाल दुरत्व(काष्ठा vfio_region_gfx_edid, link_state):
			अगर (data == VFIO_DEVICE_GFX_LINK_STATE_UP) अणु
				अगर (!drm_edid_block_valid(
					(u8 *)region->edid_blob,
					0,
					true,
					शून्य)) अणु
					gvt_vgpu_err("invalid EDID blob\n");
					वापस -EINVAL;
				पूर्ण
				पूर्णांकel_gvt_ops->emulate_hotplug(vgpu, true);
			पूर्ण अन्यथा अगर (data == VFIO_DEVICE_GFX_LINK_STATE_DOWN)
				पूर्णांकel_gvt_ops->emulate_hotplug(vgpu, false);
			अन्यथा अणु
				gvt_vgpu_err("invalid EDID link state %d\n",
					regs->link_state);
				वापस -EINVAL;
			पूर्ण
			regs->link_state = data;
			अवरोध;
		हाल दुरत्व(काष्ठा vfio_region_gfx_edid, edid_size):
			अगर (data > regs->edid_max_size) अणु
				gvt_vgpu_err("EDID size is bigger than %d!\n",
					regs->edid_max_size);
				वापस -EINVAL;
			पूर्ण
			regs->edid_size = data;
			अवरोध;
		शेष:
			/* पढ़ो-only regs */
			gvt_vgpu_err("write read-only EDID region at offset %d\n",
				offset);
			वापस -EPERM;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(buf, (अक्षर *)regs + offset, count);
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक handle_edid_blob(काष्ठा vfio_edid_region *region, अक्षर *buf,
			माप_प्रकार count, u16 offset, bool is_ग_लिखो)
अणु
	अगर (offset + count > region->vfio_edid_regs.edid_size)
		वापस -EINVAL;

	अगर (is_ग_लिखो)
		स_नकल(region->edid_blob + offset, buf, count);
	अन्यथा
		स_नकल(buf, region->edid_blob + offset, count);

	वापस count;
पूर्ण

अटल माप_प्रकार पूर्णांकel_vgpu_reg_rw_edid(काष्ठा पूर्णांकel_vgpu *vgpu, अक्षर *buf,
		माप_प्रकार count, loff_t *ppos, bool isग_लिखो)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक i = VFIO_PCI_OFFSET_TO_INDEX(*ppos) -
			VFIO_PCI_NUM_REGIONS;
	काष्ठा vfio_edid_region *region =
		(काष्ठा vfio_edid_region *)kvmgt_vdev(vgpu)->region[i].data;
	loff_t pos = *ppos & VFIO_PCI_OFFSET_MASK;

	अगर (pos < region->vfio_edid_regs.edid_offset) अणु
		ret = handle_edid_regs(vgpu, region, buf, count, pos, isग_लिखो);
	पूर्ण अन्यथा अणु
		pos -= EDID_BLOB_OFFSET;
		ret = handle_edid_blob(region, buf, count, pos, isग_लिखो);
	पूर्ण

	अगर (ret < 0)
		gvt_vgpu_err("failed to access EDID region\n");

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_vgpu_reg_release_edid(काष्ठा पूर्णांकel_vgpu *vgpu,
					काष्ठा vfio_region *region)
अणु
	kमुक्त(region->data);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_vgpu_regops पूर्णांकel_vgpu_regops_edid = अणु
	.rw = पूर्णांकel_vgpu_reg_rw_edid,
	.release = पूर्णांकel_vgpu_reg_release_edid,
पूर्ण;

अटल पूर्णांक पूर्णांकel_vgpu_रेजिस्टर_reg(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक subtype,
		स्थिर काष्ठा पूर्णांकel_vgpu_regops *ops,
		माप_प्रकार size, u32 flags, व्योम *data)
अणु
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);
	काष्ठा vfio_region *region;

	region = kपुनः_स्मृति(vdev->region,
			(vdev->num_regions + 1) * माप(*region),
			GFP_KERNEL);
	अगर (!region)
		वापस -ENOMEM;

	vdev->region = region;
	vdev->region[vdev->num_regions].type = type;
	vdev->region[vdev->num_regions].subtype = subtype;
	vdev->region[vdev->num_regions].ops = ops;
	vdev->region[vdev->num_regions].size = size;
	vdev->region[vdev->num_regions].flags = flags;
	vdev->region[vdev->num_regions].data = data;
	vdev->num_regions++;
	वापस 0;
पूर्ण

अटल पूर्णांक kvmgt_get_vfio_device(व्योम *p_vgpu)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = (काष्ठा पूर्णांकel_vgpu *)p_vgpu;
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);

	vdev->vfio_device = vfio_device_get_from_dev(
		mdev_dev(vdev->mdev));
	अगर (!vdev->vfio_device) अणु
		gvt_vgpu_err("failed to get vfio device\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक kvmgt_set_opregion(व्योम *p_vgpu)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = (काष्ठा पूर्णांकel_vgpu *)p_vgpu;
	व्योम *base;
	पूर्णांक ret;

	/* Each vgpu has its own opregion, although VFIO would create another
	 * one later. This one is used to expose opregion to VFIO. And the
	 * other one created by VFIO later, is used by guest actually.
	 */
	base = vgpu_opregion(vgpu)->va;
	अगर (!base)
		वापस -ENOMEM;

	अगर (स_भेद(base, OPREGION_SIGNATURE, 16)) अणु
		memunmap(base);
		वापस -EINVAL;
	पूर्ण

	ret = पूर्णांकel_vgpu_रेजिस्टर_reg(vgpu,
			PCI_VENDOR_ID_INTEL | VFIO_REGION_TYPE_PCI_VENDOR_TYPE,
			VFIO_REGION_SUBTYPE_INTEL_IGD_OPREGION,
			&पूर्णांकel_vgpu_regops_opregion, OPREGION_SIZE,
			VFIO_REGION_INFO_FLAG_READ, base);

	वापस ret;
पूर्ण

अटल पूर्णांक kvmgt_set_edid(व्योम *p_vgpu, पूर्णांक port_num)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = (काष्ठा पूर्णांकel_vgpu *)p_vgpu;
	काष्ठा पूर्णांकel_vgpu_port *port = पूर्णांकel_vgpu_port(vgpu, port_num);
	काष्ठा vfio_edid_region *base;
	पूर्णांक ret;

	base = kzalloc(माप(*base), GFP_KERNEL);
	अगर (!base)
		वापस -ENOMEM;

	/* TODO: Add multi-port and EDID extension block support */
	base->vfio_edid_regs.edid_offset = EDID_BLOB_OFFSET;
	base->vfio_edid_regs.edid_max_size = EDID_SIZE;
	base->vfio_edid_regs.edid_size = EDID_SIZE;
	base->vfio_edid_regs.max_xres = vgpu_edid_xres(port->id);
	base->vfio_edid_regs.max_yres = vgpu_edid_yres(port->id);
	base->edid_blob = port->edid->edid_block;

	ret = पूर्णांकel_vgpu_रेजिस्टर_reg(vgpu,
			VFIO_REGION_TYPE_GFX,
			VFIO_REGION_SUBTYPE_GFX_EDID,
			&पूर्णांकel_vgpu_regops_edid, EDID_SIZE,
			VFIO_REGION_INFO_FLAG_READ |
			VFIO_REGION_INFO_FLAG_WRITE |
			VFIO_REGION_INFO_FLAG_CAPS, base);

	वापस ret;
पूर्ण

अटल व्योम kvmgt_put_vfio_device(व्योम *vgpu)
अणु
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev((काष्ठा पूर्णांकel_vgpu *)vgpu);

	अगर (WARN_ON(!vdev->vfio_device))
		वापस;

	vfio_device_put(vdev->vfio_device);
पूर्ण

अटल पूर्णांक पूर्णांकel_vgpu_create(काष्ठा mdev_device *mdev)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = शून्य;
	काष्ठा पूर्णांकel_vgpu_type *type;
	काष्ठा device *pdev;
	काष्ठा पूर्णांकel_gvt *gvt;
	पूर्णांक ret;

	pdev = mdev_parent_dev(mdev);
	gvt = kdev_to_i915(pdev)->gvt;

	type = &gvt->types[mdev_get_type_group_id(mdev)];
	अगर (!type) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	vgpu = पूर्णांकel_gvt_ops->vgpu_create(gvt, type);
	अगर (IS_ERR_OR_शून्य(vgpu)) अणु
		ret = vgpu == शून्य ? -EFAULT : PTR_ERR(vgpu);
		gvt_err("failed to create intel vgpu: %d\n", ret);
		जाओ out;
	पूर्ण

	INIT_WORK(&kvmgt_vdev(vgpu)->release_work, पूर्णांकel_vgpu_release_work);

	kvmgt_vdev(vgpu)->mdev = mdev;
	mdev_set_drvdata(mdev, vgpu);

	gvt_dbg_core("intel_vgpu_create succeeded for mdev: %s\n",
		     dev_name(mdev_dev(mdev)));
	ret = 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_vgpu_हटाओ(काष्ठा mdev_device *mdev)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = mdev_get_drvdata(mdev);

	अगर (handle_valid(vgpu->handle))
		वापस -EBUSY;

	पूर्णांकel_gvt_ops->vgpu_destroy(vgpu);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_vgpu_iommu_notअगरier(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा kvmgt_vdev *vdev = container_of(nb,
					       काष्ठा kvmgt_vdev,
					       iommu_notअगरier);
	काष्ठा पूर्णांकel_vgpu *vgpu = vdev->vgpu;

	अगर (action == VFIO_IOMMU_NOTIFY_DMA_UNMAP) अणु
		काष्ठा vfio_iommu_type1_dma_unmap *unmap = data;
		काष्ठा gvt_dma *entry;
		अचिन्हित दीर्घ iov_pfn, end_iov_pfn;

		iov_pfn = unmap->iova >> PAGE_SHIFT;
		end_iov_pfn = iov_pfn + unmap->size / PAGE_SIZE;

		mutex_lock(&vdev->cache_lock);
		क्रम (; iov_pfn < end_iov_pfn; iov_pfn++) अणु
			entry = __gvt_cache_find_gfn(vgpu, iov_pfn);
			अगर (!entry)
				जारी;

			gvt_dma_unmap_page(vgpu, entry->gfn, entry->dma_addr,
					   entry->size);
			__gvt_cache_हटाओ_entry(vgpu, entry);
		पूर्ण
		mutex_unlock(&vdev->cache_lock);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक पूर्णांकel_vgpu_group_notअगरier(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा kvmgt_vdev *vdev = container_of(nb,
					       काष्ठा kvmgt_vdev,
					       group_notअगरier);

	/* the only action we care about */
	अगर (action == VFIO_GROUP_NOTIFY_SET_KVM) अणु
		vdev->kvm = data;

		अगर (!data)
			schedule_work(&vdev->release_work);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक पूर्णांकel_vgpu_खोलो(काष्ठा mdev_device *mdev)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = mdev_get_drvdata(mdev);
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);
	अचिन्हित दीर्घ events;
	पूर्णांक ret;
	काष्ठा vfio_group *vfio_group;

	vdev->iommu_notअगरier.notअगरier_call = पूर्णांकel_vgpu_iommu_notअगरier;
	vdev->group_notअगरier.notअगरier_call = पूर्णांकel_vgpu_group_notअगरier;

	events = VFIO_IOMMU_NOTIFY_DMA_UNMAP;
	ret = vfio_रेजिस्टर_notअगरier(mdev_dev(mdev), VFIO_IOMMU_NOTIFY, &events,
				&vdev->iommu_notअगरier);
	अगर (ret != 0) अणु
		gvt_vgpu_err("vfio_register_notifier for iommu failed: %d\n",
			ret);
		जाओ out;
	पूर्ण

	events = VFIO_GROUP_NOTIFY_SET_KVM;
	ret = vfio_रेजिस्टर_notअगरier(mdev_dev(mdev), VFIO_GROUP_NOTIFY, &events,
				&vdev->group_notअगरier);
	अगर (ret != 0) अणु
		gvt_vgpu_err("vfio_register_notifier for group failed: %d\n",
			ret);
		जाओ unकरो_iommu;
	पूर्ण

	vfio_group = vfio_group_get_बाह्यal_user_from_dev(mdev_dev(mdev));
	अगर (IS_ERR_OR_शून्य(vfio_group)) अणु
		ret = !vfio_group ? -EFAULT : PTR_ERR(vfio_group);
		gvt_vgpu_err("vfio_group_get_external_user_from_dev failed\n");
		जाओ unकरो_रेजिस्टर;
	पूर्ण
	vdev->vfio_group = vfio_group;

	/* Take a module reference as mdev core करोesn't take
	 * a reference क्रम venकरोr driver.
	 */
	अगर (!try_module_get(THIS_MODULE)) अणु
		ret = -ENODEV;
		जाओ unकरो_group;
	पूर्ण

	ret = kvmgt_guest_init(mdev);
	अगर (ret)
		जाओ unकरो_group;

	पूर्णांकel_gvt_ops->vgpu_activate(vgpu);

	atomic_set(&vdev->released, 0);
	वापस ret;

unकरो_group:
	vfio_group_put_बाह्यal_user(vdev->vfio_group);
	vdev->vfio_group = शून्य;

unकरो_रेजिस्टर:
	vfio_unरेजिस्टर_notअगरier(mdev_dev(mdev), VFIO_GROUP_NOTIFY,
					&vdev->group_notअगरier);

unकरो_iommu:
	vfio_unरेजिस्टर_notअगरier(mdev_dev(mdev), VFIO_IOMMU_NOTIFY,
					&vdev->iommu_notअगरier);
out:
	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_vgpu_release_msi_eventfd_ctx(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);
	काष्ठा eventfd_ctx *trigger;

	trigger = vdev->msi_trigger;
	अगर (trigger) अणु
		eventfd_ctx_put(trigger);
		vdev->msi_trigger = शून्य;
	पूर्ण
पूर्ण

अटल व्योम __पूर्णांकel_vgpu_release(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	काष्ठा kvmgt_guest_info *info;
	पूर्णांक ret;

	अगर (!handle_valid(vgpu->handle))
		वापस;

	अगर (atomic_cmpxchg(&vdev->released, 0, 1))
		वापस;

	पूर्णांकel_gvt_ops->vgpu_release(vgpu);

	ret = vfio_unरेजिस्टर_notअगरier(mdev_dev(vdev->mdev), VFIO_IOMMU_NOTIFY,
					&vdev->iommu_notअगरier);
	drm_WARN(&i915->drm, ret,
		 "vfio_unregister_notifier for iommu failed: %d\n", ret);

	ret = vfio_unरेजिस्टर_notअगरier(mdev_dev(vdev->mdev), VFIO_GROUP_NOTIFY,
					&vdev->group_notअगरier);
	drm_WARN(&i915->drm, ret,
		 "vfio_unregister_notifier for group failed: %d\n", ret);

	/* dereference module reference taken at खोलो */
	module_put(THIS_MODULE);

	info = (काष्ठा kvmgt_guest_info *)vgpu->handle;
	kvmgt_guest_निकास(info);

	पूर्णांकel_vgpu_release_msi_eventfd_ctx(vgpu);
	vfio_group_put_बाह्यal_user(vdev->vfio_group);

	vdev->kvm = शून्य;
	vgpu->handle = 0;
पूर्ण

अटल व्योम पूर्णांकel_vgpu_release(काष्ठा mdev_device *mdev)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = mdev_get_drvdata(mdev);

	__पूर्णांकel_vgpu_release(vgpu);
पूर्ण

अटल व्योम पूर्णांकel_vgpu_release_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा kvmgt_vdev *vdev = container_of(work, काष्ठा kvmgt_vdev,
					       release_work);

	__पूर्णांकel_vgpu_release(vdev->vgpu);
पूर्ण

अटल u64 पूर्णांकel_vgpu_get_bar_addr(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांक bar)
अणु
	u32 start_lo, start_hi;
	u32 mem_type;

	start_lo = (*(u32 *)(vgpu->cfg_space.भव_cfg_space + bar)) &
			PCI_BASE_ADDRESS_MEM_MASK;
	mem_type = (*(u32 *)(vgpu->cfg_space.भव_cfg_space + bar)) &
			PCI_BASE_ADDRESS_MEM_TYPE_MASK;

	चयन (mem_type) अणु
	हाल PCI_BASE_ADDRESS_MEM_TYPE_64:
		start_hi = (*(u32 *)(vgpu->cfg_space.भव_cfg_space
						+ bar + 4));
		अवरोध;
	हाल PCI_BASE_ADDRESS_MEM_TYPE_32:
	हाल PCI_BASE_ADDRESS_MEM_TYPE_1M:
		/* 1M mem BAR treated as 32-bit BAR */
	शेष:
		/* mem unknown type treated as 32-bit BAR */
		start_hi = 0;
		अवरोध;
	पूर्ण

	वापस ((u64)start_hi << 32) | start_lo;
पूर्ण

अटल पूर्णांक पूर्णांकel_vgpu_bar_rw(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांक bar, u64 off,
			     व्योम *buf, अचिन्हित पूर्णांक count, bool is_ग_लिखो)
अणु
	u64 bar_start = पूर्णांकel_vgpu_get_bar_addr(vgpu, bar);
	पूर्णांक ret;

	अगर (is_ग_लिखो)
		ret = पूर्णांकel_gvt_ops->emulate_mmio_ग_लिखो(vgpu,
					bar_start + off, buf, count);
	अन्यथा
		ret = पूर्णांकel_gvt_ops->emulate_mmio_पढ़ो(vgpu,
					bar_start + off, buf, count);
	वापस ret;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_vgpu_in_aperture(काष्ठा पूर्णांकel_vgpu *vgpu, u64 off)
अणु
	वापस off >= vgpu_aperture_offset(vgpu) &&
	       off < vgpu_aperture_offset(vgpu) + vgpu_aperture_sz(vgpu);
पूर्ण

अटल पूर्णांक पूर्णांकel_vgpu_aperture_rw(काष्ठा पूर्णांकel_vgpu *vgpu, u64 off,
		व्योम *buf, अचिन्हित दीर्घ count, bool is_ग_लिखो)
अणु
	व्योम __iomem *aperture_va;

	अगर (!पूर्णांकel_vgpu_in_aperture(vgpu, off) ||
	    !पूर्णांकel_vgpu_in_aperture(vgpu, off + count)) अणु
		gvt_vgpu_err("Invalid aperture offset %llu\n", off);
		वापस -EINVAL;
	पूर्ण

	aperture_va = io_mapping_map_wc(&vgpu->gvt->gt->ggtt->iomap,
					ALIGN_DOWN(off, PAGE_SIZE),
					count + offset_in_page(off));
	अगर (!aperture_va)
		वापस -EIO;

	अगर (is_ग_लिखो)
		स_नकल_toio(aperture_va + offset_in_page(off), buf, count);
	अन्यथा
		स_नकल_fromio(buf, aperture_va + offset_in_page(off), count);

	io_mapping_unmap(aperture_va);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार पूर्णांकel_vgpu_rw(काष्ठा mdev_device *mdev, अक्षर *buf,
			माप_प्रकार count, loff_t *ppos, bool is_ग_लिखो)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = mdev_get_drvdata(mdev);
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);
	अचिन्हित पूर्णांक index = VFIO_PCI_OFFSET_TO_INDEX(*ppos);
	u64 pos = *ppos & VFIO_PCI_OFFSET_MASK;
	पूर्णांक ret = -EINVAL;


	अगर (index >= VFIO_PCI_NUM_REGIONS + vdev->num_regions) अणु
		gvt_vgpu_err("invalid index: %u\n", index);
		वापस -EINVAL;
	पूर्ण

	चयन (index) अणु
	हाल VFIO_PCI_CONFIG_REGION_INDEX:
		अगर (is_ग_लिखो)
			ret = पूर्णांकel_gvt_ops->emulate_cfg_ग_लिखो(vgpu, pos,
						buf, count);
		अन्यथा
			ret = पूर्णांकel_gvt_ops->emulate_cfg_पढ़ो(vgpu, pos,
						buf, count);
		अवरोध;
	हाल VFIO_PCI_BAR0_REGION_INDEX:
		ret = पूर्णांकel_vgpu_bar_rw(vgpu, PCI_BASE_ADDRESS_0, pos,
					buf, count, is_ग_लिखो);
		अवरोध;
	हाल VFIO_PCI_BAR2_REGION_INDEX:
		ret = पूर्णांकel_vgpu_aperture_rw(vgpu, pos, buf, count, is_ग_लिखो);
		अवरोध;
	हाल VFIO_PCI_BAR1_REGION_INDEX:
	हाल VFIO_PCI_BAR3_REGION_INDEX:
	हाल VFIO_PCI_BAR4_REGION_INDEX:
	हाल VFIO_PCI_BAR5_REGION_INDEX:
	हाल VFIO_PCI_VGA_REGION_INDEX:
	हाल VFIO_PCI_ROM_REGION_INDEX:
		अवरोध;
	शेष:
		अगर (index >= VFIO_PCI_NUM_REGIONS + vdev->num_regions)
			वापस -EINVAL;

		index -= VFIO_PCI_NUM_REGIONS;
		वापस vdev->region[index].ops->rw(vgpu, buf, count,
				ppos, is_ग_लिखो);
	पूर्ण

	वापस ret == 0 ? count : ret;
पूर्ण

अटल bool gtt_entry(काष्ठा mdev_device *mdev, loff_t *ppos)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = mdev_get_drvdata(mdev);
	अचिन्हित पूर्णांक index = VFIO_PCI_OFFSET_TO_INDEX(*ppos);
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	पूर्णांक offset;

	/* Only allow MMIO GGTT entry access */
	अगर (index != PCI_BASE_ADDRESS_0)
		वापस false;

	offset = (u64)(*ppos & VFIO_PCI_OFFSET_MASK) -
		पूर्णांकel_vgpu_get_bar_gpa(vgpu, PCI_BASE_ADDRESS_0);

	वापस (offset >= gvt->device_info.gtt_start_offset &&
		offset < gvt->device_info.gtt_start_offset + gvt_ggtt_sz(gvt)) ?
			true : false;
पूर्ण

अटल sमाप_प्रकार पूर्णांकel_vgpu_पढ़ो(काष्ठा mdev_device *mdev, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक करोne = 0;
	पूर्णांक ret;

	जबतक (count) अणु
		माप_प्रकार filled;

		/* Only support GGTT entry 8 bytes पढ़ो */
		अगर (count >= 8 && !(*ppos % 8) &&
			gtt_entry(mdev, ppos)) अणु
			u64 val;

			ret = पूर्णांकel_vgpu_rw(mdev, (अक्षर *)&val, माप(val),
					ppos, false);
			अगर (ret <= 0)
				जाओ पढ़ो_err;

			अगर (copy_to_user(buf, &val, माप(val)))
				जाओ पढ़ो_err;

			filled = 8;
		पूर्ण अन्यथा अगर (count >= 4 && !(*ppos % 4)) अणु
			u32 val;

			ret = पूर्णांकel_vgpu_rw(mdev, (अक्षर *)&val, माप(val),
					ppos, false);
			अगर (ret <= 0)
				जाओ पढ़ो_err;

			अगर (copy_to_user(buf, &val, माप(val)))
				जाओ पढ़ो_err;

			filled = 4;
		पूर्ण अन्यथा अगर (count >= 2 && !(*ppos % 2)) अणु
			u16 val;

			ret = पूर्णांकel_vgpu_rw(mdev, (अक्षर *)&val, माप(val),
					ppos, false);
			अगर (ret <= 0)
				जाओ पढ़ो_err;

			अगर (copy_to_user(buf, &val, माप(val)))
				जाओ पढ़ो_err;

			filled = 2;
		पूर्ण अन्यथा अणु
			u8 val;

			ret = पूर्णांकel_vgpu_rw(mdev, &val, माप(val), ppos,
					false);
			अगर (ret <= 0)
				जाओ पढ़ो_err;

			अगर (copy_to_user(buf, &val, माप(val)))
				जाओ पढ़ो_err;

			filled = 1;
		पूर्ण

		count -= filled;
		करोne += filled;
		*ppos += filled;
		buf += filled;
	पूर्ण

	वापस करोne;

पढ़ो_err:
	वापस -EFAULT;
पूर्ण

अटल sमाप_प्रकार पूर्णांकel_vgpu_ग_लिखो(काष्ठा mdev_device *mdev,
				स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक करोne = 0;
	पूर्णांक ret;

	जबतक (count) अणु
		माप_प्रकार filled;

		/* Only support GGTT entry 8 bytes ग_लिखो */
		अगर (count >= 8 && !(*ppos % 8) &&
			gtt_entry(mdev, ppos)) अणु
			u64 val;

			अगर (copy_from_user(&val, buf, माप(val)))
				जाओ ग_लिखो_err;

			ret = पूर्णांकel_vgpu_rw(mdev, (अक्षर *)&val, माप(val),
					ppos, true);
			अगर (ret <= 0)
				जाओ ग_लिखो_err;

			filled = 8;
		पूर्ण अन्यथा अगर (count >= 4 && !(*ppos % 4)) अणु
			u32 val;

			अगर (copy_from_user(&val, buf, माप(val)))
				जाओ ग_लिखो_err;

			ret = पूर्णांकel_vgpu_rw(mdev, (अक्षर *)&val, माप(val),
					ppos, true);
			अगर (ret <= 0)
				जाओ ग_लिखो_err;

			filled = 4;
		पूर्ण अन्यथा अगर (count >= 2 && !(*ppos % 2)) अणु
			u16 val;

			अगर (copy_from_user(&val, buf, माप(val)))
				जाओ ग_लिखो_err;

			ret = पूर्णांकel_vgpu_rw(mdev, (अक्षर *)&val,
					माप(val), ppos, true);
			अगर (ret <= 0)
				जाओ ग_लिखो_err;

			filled = 2;
		पूर्ण अन्यथा अणु
			u8 val;

			अगर (copy_from_user(&val, buf, माप(val)))
				जाओ ग_लिखो_err;

			ret = पूर्णांकel_vgpu_rw(mdev, &val, माप(val),
					ppos, true);
			अगर (ret <= 0)
				जाओ ग_लिखो_err;

			filled = 1;
		पूर्ण

		count -= filled;
		करोne += filled;
		*ppos += filled;
		buf += filled;
	पूर्ण

	वापस करोne;
ग_लिखो_err:
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक पूर्णांकel_vgpu_mmap(काष्ठा mdev_device *mdev, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित पूर्णांक index;
	u64 virtaddr;
	अचिन्हित दीर्घ req_size, pgoff, req_start;
	pgprot_t pg_prot;
	काष्ठा पूर्णांकel_vgpu *vgpu = mdev_get_drvdata(mdev);

	index = vma->vm_pgoff >> (VFIO_PCI_OFFSET_SHIFT - PAGE_SHIFT);
	अगर (index >= VFIO_PCI_ROM_REGION_INDEX)
		वापस -EINVAL;

	अगर (vma->vm_end < vma->vm_start)
		वापस -EINVAL;
	अगर ((vma->vm_flags & VM_SHARED) == 0)
		वापस -EINVAL;
	अगर (index != VFIO_PCI_BAR2_REGION_INDEX)
		वापस -EINVAL;

	pg_prot = vma->vm_page_prot;
	virtaddr = vma->vm_start;
	req_size = vma->vm_end - vma->vm_start;
	pgoff = vma->vm_pgoff &
		((1U << (VFIO_PCI_OFFSET_SHIFT - PAGE_SHIFT)) - 1);
	req_start = pgoff << PAGE_SHIFT;

	अगर (!पूर्णांकel_vgpu_in_aperture(vgpu, req_start))
		वापस -EINVAL;
	अगर (req_start + req_size >
	    vgpu_aperture_offset(vgpu) + vgpu_aperture_sz(vgpu))
		वापस -EINVAL;

	pgoff = (gvt_aperture_pa_base(vgpu->gvt) >> PAGE_SHIFT) + pgoff;

	वापस remap_pfn_range(vma, virtaddr, pgoff, req_size, pg_prot);
पूर्ण

अटल पूर्णांक पूर्णांकel_vgpu_get_irq_count(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांक type)
अणु
	अगर (type == VFIO_PCI_INTX_IRQ_INDEX || type == VFIO_PCI_MSI_IRQ_INDEX)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_vgpu_set_पूर्णांकx_mask(काष्ठा पूर्णांकel_vgpu *vgpu,
			अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक start,
			अचिन्हित पूर्णांक count, u32 flags,
			व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_vgpu_set_पूर्णांकx_unmask(काष्ठा पूर्णांकel_vgpu *vgpu,
			अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक start,
			अचिन्हित पूर्णांक count, u32 flags, व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_vgpu_set_पूर्णांकx_trigger(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक count,
		u32 flags, व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_vgpu_set_msi_trigger(काष्ठा पूर्णांकel_vgpu *vgpu,
		अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक count,
		u32 flags, व्योम *data)
अणु
	काष्ठा eventfd_ctx *trigger;

	अगर (flags & VFIO_IRQ_SET_DATA_EVENTFD) अणु
		पूर्णांक fd = *(पूर्णांक *)data;

		trigger = eventfd_ctx_fdget(fd);
		अगर (IS_ERR(trigger)) अणु
			gvt_vgpu_err("eventfd_ctx_fdget failed\n");
			वापस PTR_ERR(trigger);
		पूर्ण
		kvmgt_vdev(vgpu)->msi_trigger = trigger;
	पूर्ण अन्यथा अगर ((flags & VFIO_IRQ_SET_DATA_NONE) && !count)
		पूर्णांकel_vgpu_release_msi_eventfd_ctx(vgpu);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_vgpu_set_irqs(काष्ठा पूर्णांकel_vgpu *vgpu, u32 flags,
		अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक count,
		व्योम *data)
अणु
	पूर्णांक (*func)(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक index,
			अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक count, u32 flags,
			व्योम *data) = शून्य;

	चयन (index) अणु
	हाल VFIO_PCI_INTX_IRQ_INDEX:
		चयन (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) अणु
		हाल VFIO_IRQ_SET_ACTION_MASK:
			func = पूर्णांकel_vgpu_set_पूर्णांकx_mask;
			अवरोध;
		हाल VFIO_IRQ_SET_ACTION_UNMASK:
			func = पूर्णांकel_vgpu_set_पूर्णांकx_unmask;
			अवरोध;
		हाल VFIO_IRQ_SET_ACTION_TRIGGER:
			func = पूर्णांकel_vgpu_set_पूर्णांकx_trigger;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल VFIO_PCI_MSI_IRQ_INDEX:
		चयन (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) अणु
		हाल VFIO_IRQ_SET_ACTION_MASK:
		हाल VFIO_IRQ_SET_ACTION_UNMASK:
			/* XXX Need masking support exported */
			अवरोध;
		हाल VFIO_IRQ_SET_ACTION_TRIGGER:
			func = पूर्णांकel_vgpu_set_msi_trigger;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (!func)
		वापस -ENOTTY;

	वापस func(vgpu, index, start, count, flags, data);
पूर्ण

अटल दीर्घ पूर्णांकel_vgpu_ioctl(काष्ठा mdev_device *mdev, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = mdev_get_drvdata(mdev);
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);
	अचिन्हित दीर्घ minsz;

	gvt_dbg_core("vgpu%d ioctl, cmd: %d\n", vgpu->id, cmd);

	अगर (cmd == VFIO_DEVICE_GET_INFO) अणु
		काष्ठा vfio_device_info info;

		minsz = दुरत्वend(काष्ठा vfio_device_info, num_irqs);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		info.flags = VFIO_DEVICE_FLAGS_PCI;
		info.flags |= VFIO_DEVICE_FLAGS_RESET;
		info.num_regions = VFIO_PCI_NUM_REGIONS +
				vdev->num_regions;
		info.num_irqs = VFIO_PCI_NUM_IRQS;

		वापस copy_to_user((व्योम __user *)arg, &info, minsz) ?
			-EFAULT : 0;

	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_GET_REGION_INFO) अणु
		काष्ठा vfio_region_info info;
		काष्ठा vfio_info_cap caps = अणु .buf = शून्य, .size = 0 पूर्ण;
		अचिन्हित पूर्णांक i;
		पूर्णांक ret;
		काष्ठा vfio_region_info_cap_sparse_mmap *sparse = शून्य;
		पूर्णांक nr_areas = 1;
		पूर्णांक cap_type_id;

		minsz = दुरत्वend(काष्ठा vfio_region_info, offset);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		चयन (info.index) अणु
		हाल VFIO_PCI_CONFIG_REGION_INDEX:
			info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
			info.size = vgpu->gvt->device_info.cfg_space_size;
			info.flags = VFIO_REGION_INFO_FLAG_READ |
				     VFIO_REGION_INFO_FLAG_WRITE;
			अवरोध;
		हाल VFIO_PCI_BAR0_REGION_INDEX:
			info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
			info.size = vgpu->cfg_space.bar[info.index].size;
			अगर (!info.size) अणु
				info.flags = 0;
				अवरोध;
			पूर्ण

			info.flags = VFIO_REGION_INFO_FLAG_READ |
				     VFIO_REGION_INFO_FLAG_WRITE;
			अवरोध;
		हाल VFIO_PCI_BAR1_REGION_INDEX:
			info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
			info.size = 0;
			info.flags = 0;
			अवरोध;
		हाल VFIO_PCI_BAR2_REGION_INDEX:
			info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
			info.flags = VFIO_REGION_INFO_FLAG_CAPS |
					VFIO_REGION_INFO_FLAG_MMAP |
					VFIO_REGION_INFO_FLAG_READ |
					VFIO_REGION_INFO_FLAG_WRITE;
			info.size = gvt_aperture_sz(vgpu->gvt);

			sparse = kzalloc(काष्ठा_size(sparse, areas, nr_areas),
					 GFP_KERNEL);
			अगर (!sparse)
				वापस -ENOMEM;

			sparse->header.id = VFIO_REGION_INFO_CAP_SPARSE_MMAP;
			sparse->header.version = 1;
			sparse->nr_areas = nr_areas;
			cap_type_id = VFIO_REGION_INFO_CAP_SPARSE_MMAP;
			sparse->areas[0].offset =
					PAGE_ALIGN(vgpu_aperture_offset(vgpu));
			sparse->areas[0].size = vgpu_aperture_sz(vgpu);
			अवरोध;

		हाल VFIO_PCI_BAR3_REGION_INDEX ... VFIO_PCI_BAR5_REGION_INDEX:
			info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
			info.size = 0;
			info.flags = 0;

			gvt_dbg_core("get region info bar:%d\n", info.index);
			अवरोध;

		हाल VFIO_PCI_ROM_REGION_INDEX:
		हाल VFIO_PCI_VGA_REGION_INDEX:
			info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
			info.size = 0;
			info.flags = 0;

			gvt_dbg_core("get region info index:%d\n", info.index);
			अवरोध;
		शेष:
			अणु
				काष्ठा vfio_region_info_cap_type cap_type = अणु
					.header.id = VFIO_REGION_INFO_CAP_TYPE,
					.header.version = 1 पूर्ण;

				अगर (info.index >= VFIO_PCI_NUM_REGIONS +
						vdev->num_regions)
					वापस -EINVAL;
				info.index =
					array_index_nospec(info.index,
							VFIO_PCI_NUM_REGIONS +
							vdev->num_regions);

				i = info.index - VFIO_PCI_NUM_REGIONS;

				info.offset =
					VFIO_PCI_INDEX_TO_OFFSET(info.index);
				info.size = vdev->region[i].size;
				info.flags = vdev->region[i].flags;

				cap_type.type = vdev->region[i].type;
				cap_type.subtype = vdev->region[i].subtype;

				ret = vfio_info_add_capability(&caps,
							&cap_type.header,
							माप(cap_type));
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण

		अगर ((info.flags & VFIO_REGION_INFO_FLAG_CAPS) && sparse) अणु
			चयन (cap_type_id) अणु
			हाल VFIO_REGION_INFO_CAP_SPARSE_MMAP:
				ret = vfio_info_add_capability(&caps,
					&sparse->header,
					काष्ठा_size(sparse, areas,
						    sparse->nr_areas));
				अगर (ret) अणु
					kमुक्त(sparse);
					वापस ret;
				पूर्ण
				अवरोध;
			शेष:
				kमुक्त(sparse);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		अगर (caps.size) अणु
			info.flags |= VFIO_REGION_INFO_FLAG_CAPS;
			अगर (info.argsz < माप(info) + caps.size) अणु
				info.argsz = माप(info) + caps.size;
				info.cap_offset = 0;
			पूर्ण अन्यथा अणु
				vfio_info_cap_shअगरt(&caps, माप(info));
				अगर (copy_to_user((व्योम __user *)arg +
						  माप(info), caps.buf,
						  caps.size)) अणु
					kमुक्त(caps.buf);
					kमुक्त(sparse);
					वापस -EFAULT;
				पूर्ण
				info.cap_offset = माप(info);
			पूर्ण

			kमुक्त(caps.buf);
		पूर्ण

		kमुक्त(sparse);
		वापस copy_to_user((व्योम __user *)arg, &info, minsz) ?
			-EFAULT : 0;
	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_GET_IRQ_INFO) अणु
		काष्ठा vfio_irq_info info;

		minsz = दुरत्वend(काष्ठा vfio_irq_info, count);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz || info.index >= VFIO_PCI_NUM_IRQS)
			वापस -EINVAL;

		चयन (info.index) अणु
		हाल VFIO_PCI_INTX_IRQ_INDEX:
		हाल VFIO_PCI_MSI_IRQ_INDEX:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		info.flags = VFIO_IRQ_INFO_EVENTFD;

		info.count = पूर्णांकel_vgpu_get_irq_count(vgpu, info.index);

		अगर (info.index == VFIO_PCI_INTX_IRQ_INDEX)
			info.flags |= (VFIO_IRQ_INFO_MASKABLE |
				       VFIO_IRQ_INFO_AUTOMASKED);
		अन्यथा
			info.flags |= VFIO_IRQ_INFO_NORESIZE;

		वापस copy_to_user((व्योम __user *)arg, &info, minsz) ?
			-EFAULT : 0;
	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_SET_IRQS) अणु
		काष्ठा vfio_irq_set hdr;
		u8 *data = शून्य;
		पूर्णांक ret = 0;
		माप_प्रकार data_size = 0;

		minsz = दुरत्वend(काष्ठा vfio_irq_set, count);

		अगर (copy_from_user(&hdr, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (!(hdr.flags & VFIO_IRQ_SET_DATA_NONE)) अणु
			पूर्णांक max = पूर्णांकel_vgpu_get_irq_count(vgpu, hdr.index);

			ret = vfio_set_irqs_validate_and_prepare(&hdr, max,
						VFIO_PCI_NUM_IRQS, &data_size);
			अगर (ret) अणु
				gvt_vgpu_err("intel:vfio_set_irqs_validate_and_prepare failed\n");
				वापस -EINVAL;
			पूर्ण
			अगर (data_size) अणु
				data = memdup_user((व्योम __user *)(arg + minsz),
						   data_size);
				अगर (IS_ERR(data))
					वापस PTR_ERR(data);
			पूर्ण
		पूर्ण

		ret = पूर्णांकel_vgpu_set_irqs(vgpu, hdr.flags, hdr.index,
					hdr.start, hdr.count, data);
		kमुक्त(data);

		वापस ret;
	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_RESET) अणु
		पूर्णांकel_gvt_ops->vgpu_reset(vgpu);
		वापस 0;
	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_QUERY_GFX_PLANE) अणु
		काष्ठा vfio_device_gfx_plane_info dmabuf;
		पूर्णांक ret = 0;

		minsz = दुरत्वend(काष्ठा vfio_device_gfx_plane_info,
				    dmabuf_id);
		अगर (copy_from_user(&dmabuf, (व्योम __user *)arg, minsz))
			वापस -EFAULT;
		अगर (dmabuf.argsz < minsz)
			वापस -EINVAL;

		ret = पूर्णांकel_gvt_ops->vgpu_query_plane(vgpu, &dmabuf);
		अगर (ret != 0)
			वापस ret;

		वापस copy_to_user((व्योम __user *)arg, &dmabuf, minsz) ?
								-EFAULT : 0;
	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_GET_GFX_DMABUF) अणु
		__u32 dmabuf_id;
		__s32 dmabuf_fd;

		अगर (get_user(dmabuf_id, (__u32 __user *)arg))
			वापस -EFAULT;

		dmabuf_fd = पूर्णांकel_gvt_ops->vgpu_get_dmabuf(vgpu, dmabuf_id);
		वापस dmabuf_fd;

	पूर्ण

	वापस -ENOTTY;
पूर्ण

अटल sमाप_प्रकार
vgpu_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
	     अक्षर *buf)
अणु
	काष्ठा mdev_device *mdev = mdev_from_dev(dev);

	अगर (mdev) अणु
		काष्ठा पूर्णांकel_vgpu *vgpu = (काष्ठा पूर्णांकel_vgpu *)
			mdev_get_drvdata(mdev);
		वापस प्र_लिखो(buf, "%d\n", vgpu->id);
	पूर्ण
	वापस प्र_लिखो(buf, "\n");
पूर्ण

अटल DEVICE_ATTR_RO(vgpu_id);

अटल काष्ठा attribute *पूर्णांकel_vgpu_attrs[] = अणु
	&dev_attr_vgpu_id.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group पूर्णांकel_vgpu_group = अणु
	.name = "intel_vgpu",
	.attrs = पूर्णांकel_vgpu_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *पूर्णांकel_vgpu_groups[] = अणु
	&पूर्णांकel_vgpu_group,
	शून्य,
पूर्ण;

अटल काष्ठा mdev_parent_ops पूर्णांकel_vgpu_ops = अणु
	.mdev_attr_groups       = पूर्णांकel_vgpu_groups,
	.create			= पूर्णांकel_vgpu_create,
	.हटाओ			= पूर्णांकel_vgpu_हटाओ,

	.खोलो			= पूर्णांकel_vgpu_खोलो,
	.release		= पूर्णांकel_vgpu_release,

	.पढ़ो			= पूर्णांकel_vgpu_पढ़ो,
	.ग_लिखो			= पूर्णांकel_vgpu_ग_लिखो,
	.mmap			= पूर्णांकel_vgpu_mmap,
	.ioctl			= पूर्णांकel_vgpu_ioctl,
पूर्ण;

अटल पूर्णांक kvmgt_host_init(काष्ठा device *dev, व्योम *gvt, स्थिर व्योम *ops)
अणु
	पूर्णांक ret;

	ret = पूर्णांकel_gvt_init_vgpu_type_groups((काष्ठा पूर्णांकel_gvt *)gvt);
	अगर (ret)
		वापस ret;

	पूर्णांकel_gvt_ops = ops;
	पूर्णांकel_vgpu_ops.supported_type_groups = gvt_vgpu_type_groups;

	ret = mdev_रेजिस्टर_device(dev, &पूर्णांकel_vgpu_ops);
	अगर (ret)
		पूर्णांकel_gvt_cleanup_vgpu_type_groups((काष्ठा पूर्णांकel_gvt *)gvt);

	वापस ret;
पूर्ण

अटल व्योम kvmgt_host_निकास(काष्ठा device *dev, व्योम *gvt)
अणु
	mdev_unरेजिस्टर_device(dev);
	पूर्णांकel_gvt_cleanup_vgpu_type_groups((काष्ठा पूर्णांकel_gvt *)gvt);
पूर्ण

अटल पूर्णांक kvmgt_page_track_add(अचिन्हित दीर्घ handle, u64 gfn)
अणु
	काष्ठा kvmgt_guest_info *info;
	काष्ठा kvm *kvm;
	काष्ठा kvm_memory_slot *slot;
	पूर्णांक idx;

	अगर (!handle_valid(handle))
		वापस -ESRCH;

	info = (काष्ठा kvmgt_guest_info *)handle;
	kvm = info->kvm;

	idx = srcu_पढ़ो_lock(&kvm->srcu);
	slot = gfn_to_memslot(kvm, gfn);
	अगर (!slot) अणु
		srcu_पढ़ो_unlock(&kvm->srcu, idx);
		वापस -EINVAL;
	पूर्ण

	ग_लिखो_lock(&kvm->mmu_lock);

	अगर (kvmgt_gfn_is_ग_लिखो_रक्षित(info, gfn))
		जाओ out;

	kvm_slot_page_track_add_page(kvm, slot, gfn, KVM_PAGE_TRACK_WRITE);
	kvmgt_protect_table_add(info, gfn);

out:
	ग_लिखो_unlock(&kvm->mmu_lock);
	srcu_पढ़ो_unlock(&kvm->srcu, idx);
	वापस 0;
पूर्ण

अटल पूर्णांक kvmgt_page_track_हटाओ(अचिन्हित दीर्घ handle, u64 gfn)
अणु
	काष्ठा kvmgt_guest_info *info;
	काष्ठा kvm *kvm;
	काष्ठा kvm_memory_slot *slot;
	पूर्णांक idx;

	अगर (!handle_valid(handle))
		वापस 0;

	info = (काष्ठा kvmgt_guest_info *)handle;
	kvm = info->kvm;

	idx = srcu_पढ़ो_lock(&kvm->srcu);
	slot = gfn_to_memslot(kvm, gfn);
	अगर (!slot) अणु
		srcu_पढ़ो_unlock(&kvm->srcu, idx);
		वापस -EINVAL;
	पूर्ण

	ग_लिखो_lock(&kvm->mmu_lock);

	अगर (!kvmgt_gfn_is_ग_लिखो_रक्षित(info, gfn))
		जाओ out;

	kvm_slot_page_track_हटाओ_page(kvm, slot, gfn, KVM_PAGE_TRACK_WRITE);
	kvmgt_protect_table_del(info, gfn);

out:
	ग_लिखो_unlock(&kvm->mmu_lock);
	srcu_पढ़ो_unlock(&kvm->srcu, idx);
	वापस 0;
पूर्ण

अटल व्योम kvmgt_page_track_ग_लिखो(काष्ठा kvm_vcpu *vcpu, gpa_t gpa,
		स्थिर u8 *val, पूर्णांक len,
		काष्ठा kvm_page_track_notअगरier_node *node)
अणु
	काष्ठा kvmgt_guest_info *info = container_of(node,
					काष्ठा kvmgt_guest_info, track_node);

	अगर (kvmgt_gfn_is_ग_लिखो_रक्षित(info, gpa_to_gfn(gpa)))
		पूर्णांकel_gvt_ops->ग_लिखो_protect_handler(info->vgpu, gpa,
						     (व्योम *)val, len);
पूर्ण

अटल व्योम kvmgt_page_track_flush_slot(काष्ठा kvm *kvm,
		काष्ठा kvm_memory_slot *slot,
		काष्ठा kvm_page_track_notअगरier_node *node)
अणु
	पूर्णांक i;
	gfn_t gfn;
	काष्ठा kvmgt_guest_info *info = container_of(node,
					काष्ठा kvmgt_guest_info, track_node);

	ग_लिखो_lock(&kvm->mmu_lock);
	क्रम (i = 0; i < slot->npages; i++) अणु
		gfn = slot->base_gfn + i;
		अगर (kvmgt_gfn_is_ग_लिखो_रक्षित(info, gfn)) अणु
			kvm_slot_page_track_हटाओ_page(kvm, slot, gfn,
						KVM_PAGE_TRACK_WRITE);
			kvmgt_protect_table_del(info, gfn);
		पूर्ण
	पूर्ण
	ग_लिखो_unlock(&kvm->mmu_lock);
पूर्ण

अटल bool __kvmgt_vgpu_exist(काष्ठा पूर्णांकel_vgpu *vgpu, काष्ठा kvm *kvm)
अणु
	काष्ठा पूर्णांकel_vgpu *itr;
	काष्ठा kvmgt_guest_info *info;
	पूर्णांक id;
	bool ret = false;

	mutex_lock(&vgpu->gvt->lock);
	क्रम_each_active_vgpu(vgpu->gvt, itr, id) अणु
		अगर (!handle_valid(itr->handle))
			जारी;

		info = (काष्ठा kvmgt_guest_info *)itr->handle;
		अगर (kvm && kvm == info->kvm) अणु
			ret = true;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&vgpu->gvt->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक kvmgt_guest_init(काष्ठा mdev_device *mdev)
अणु
	काष्ठा kvmgt_guest_info *info;
	काष्ठा पूर्णांकel_vgpu *vgpu;
	काष्ठा kvmgt_vdev *vdev;
	काष्ठा kvm *kvm;

	vgpu = mdev_get_drvdata(mdev);
	अगर (handle_valid(vgpu->handle))
		वापस -EEXIST;

	vdev = kvmgt_vdev(vgpu);
	kvm = vdev->kvm;
	अगर (!kvm || kvm->mm != current->mm) अणु
		gvt_vgpu_err("KVM is required to use Intel vGPU\n");
		वापस -ESRCH;
	पूर्ण

	अगर (__kvmgt_vgpu_exist(vgpu, kvm))
		वापस -EEXIST;

	info = vzalloc(माप(काष्ठा kvmgt_guest_info));
	अगर (!info)
		वापस -ENOMEM;

	vgpu->handle = (अचिन्हित दीर्घ)info;
	info->vgpu = vgpu;
	info->kvm = kvm;
	kvm_get_kvm(info->kvm);

	kvmgt_protect_table_init(info);
	gvt_cache_init(vgpu);

	info->track_node.track_ग_लिखो = kvmgt_page_track_ग_लिखो;
	info->track_node.track_flush_slot = kvmgt_page_track_flush_slot;
	kvm_page_track_रेजिस्टर_notअगरier(kvm, &info->track_node);

	info->debugfs_cache_entries = debugfs_create_uदीर्घ(
						"kvmgt_nr_cache_entries",
						0444, vgpu->debugfs,
						&vdev->nr_cache_entries);
	वापस 0;
पूर्ण

अटल bool kvmgt_guest_निकास(काष्ठा kvmgt_guest_info *info)
अणु
	debugfs_हटाओ(info->debugfs_cache_entries);

	kvm_page_track_unरेजिस्टर_notअगरier(info->kvm, &info->track_node);
	kvm_put_kvm(info->kvm);
	kvmgt_protect_table_destroy(info);
	gvt_cache_destroy(info->vgpu);
	vमुक्त(info);

	वापस true;
पूर्ण

अटल पूर्णांक kvmgt_attach_vgpu(व्योम *p_vgpu, अचिन्हित दीर्घ *handle)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = (काष्ठा पूर्णांकel_vgpu *)p_vgpu;

	vgpu->vdev = kzalloc(माप(काष्ठा kvmgt_vdev), GFP_KERNEL);

	अगर (!vgpu->vdev)
		वापस -ENOMEM;

	kvmgt_vdev(vgpu)->vgpu = vgpu;

	वापस 0;
पूर्ण

अटल व्योम kvmgt_detach_vgpu(व्योम *p_vgpu)
अणु
	पूर्णांक i;
	काष्ठा पूर्णांकel_vgpu *vgpu = (काष्ठा पूर्णांकel_vgpu *)p_vgpu;
	काष्ठा kvmgt_vdev *vdev = kvmgt_vdev(vgpu);

	अगर (!vdev->region)
		वापस;

	क्रम (i = 0; i < vdev->num_regions; i++)
		अगर (vdev->region[i].ops->release)
			vdev->region[i].ops->release(vgpu,
					&vdev->region[i]);
	vdev->num_regions = 0;
	kमुक्त(vdev->region);
	vdev->region = शून्य;

	kमुक्त(vdev);
पूर्ण

अटल पूर्णांक kvmgt_inject_msi(अचिन्हित दीर्घ handle, u32 addr, u16 data)
अणु
	काष्ठा kvmgt_guest_info *info;
	काष्ठा पूर्णांकel_vgpu *vgpu;
	काष्ठा kvmgt_vdev *vdev;

	अगर (!handle_valid(handle))
		वापस -ESRCH;

	info = (काष्ठा kvmgt_guest_info *)handle;
	vgpu = info->vgpu;
	vdev = kvmgt_vdev(vgpu);

	/*
	 * When guest is घातeroff, msi_trigger is set to शून्य, but vgpu's
	 * config and mmio रेजिस्टर isn't restored to शेष during guest
	 * घातeroff. If this vgpu is still used in next vm, this vgpu's pipe
	 * may be enabled, then once this vgpu is active, it will get inject
	 * vblank पूर्णांकerrupt request. But msi_trigger is null until msi is
	 * enabled by guest. so अगर msi_trigger is null, success is still
	 * वापसed and करोn't inject पूर्णांकerrupt पूर्णांकo guest.
	 */
	अगर (vdev->msi_trigger == शून्य)
		वापस 0;

	अगर (eventfd_संकेत(vdev->msi_trigger, 1) == 1)
		वापस 0;

	वापस -EFAULT;
पूर्ण

अटल अचिन्हित दीर्घ kvmgt_gfn_to_pfn(अचिन्हित दीर्घ handle, अचिन्हित दीर्घ gfn)
अणु
	काष्ठा kvmgt_guest_info *info;
	kvm_pfn_t pfn;

	अगर (!handle_valid(handle))
		वापस INTEL_GVT_INVALID_ADDR;

	info = (काष्ठा kvmgt_guest_info *)handle;

	pfn = gfn_to_pfn(info->kvm, gfn);
	अगर (is_error_noslot_pfn(pfn))
		वापस INTEL_GVT_INVALID_ADDR;

	वापस pfn;
पूर्ण

अटल पूर्णांक kvmgt_dma_map_guest_page(अचिन्हित दीर्घ handle, अचिन्हित दीर्घ gfn,
		अचिन्हित दीर्घ size, dma_addr_t *dma_addr)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu;
	काष्ठा kvmgt_vdev *vdev;
	काष्ठा gvt_dma *entry;
	पूर्णांक ret;

	अगर (!handle_valid(handle))
		वापस -EINVAL;

	vgpu = ((काष्ठा kvmgt_guest_info *)handle)->vgpu;
	vdev = kvmgt_vdev(vgpu);

	mutex_lock(&vdev->cache_lock);

	entry = __gvt_cache_find_gfn(vgpu, gfn);
	अगर (!entry) अणु
		ret = gvt_dma_map_page(vgpu, gfn, dma_addr, size);
		अगर (ret)
			जाओ err_unlock;

		ret = __gvt_cache_add(vgpu, gfn, *dma_addr, size);
		अगर (ret)
			जाओ err_unmap;
	पूर्ण अन्यथा अगर (entry->size != size) अणु
		/* the same gfn with dअगरferent size: unmap and re-map */
		gvt_dma_unmap_page(vgpu, gfn, entry->dma_addr, entry->size);
		__gvt_cache_हटाओ_entry(vgpu, entry);

		ret = gvt_dma_map_page(vgpu, gfn, dma_addr, size);
		अगर (ret)
			जाओ err_unlock;

		ret = __gvt_cache_add(vgpu, gfn, *dma_addr, size);
		अगर (ret)
			जाओ err_unmap;
	पूर्ण अन्यथा अणु
		kref_get(&entry->ref);
		*dma_addr = entry->dma_addr;
	पूर्ण

	mutex_unlock(&vdev->cache_lock);
	वापस 0;

err_unmap:
	gvt_dma_unmap_page(vgpu, gfn, *dma_addr, size);
err_unlock:
	mutex_unlock(&vdev->cache_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक kvmgt_dma_pin_guest_page(अचिन्हित दीर्घ handle, dma_addr_t dma_addr)
अणु
	काष्ठा kvmgt_guest_info *info;
	काष्ठा kvmgt_vdev *vdev;
	काष्ठा gvt_dma *entry;
	पूर्णांक ret = 0;

	अगर (!handle_valid(handle))
		वापस -ENODEV;

	info = (काष्ठा kvmgt_guest_info *)handle;
	vdev = kvmgt_vdev(info->vgpu);

	mutex_lock(&vdev->cache_lock);
	entry = __gvt_cache_find_dma_addr(info->vgpu, dma_addr);
	अगर (entry)
		kref_get(&entry->ref);
	अन्यथा
		ret = -ENOMEM;
	mutex_unlock(&vdev->cache_lock);

	वापस ret;
पूर्ण

अटल व्योम __gvt_dma_release(काष्ठा kref *ref)
अणु
	काष्ठा gvt_dma *entry = container_of(ref, typeof(*entry), ref);

	gvt_dma_unmap_page(entry->vgpu, entry->gfn, entry->dma_addr,
			   entry->size);
	__gvt_cache_हटाओ_entry(entry->vgpu, entry);
पूर्ण

अटल व्योम kvmgt_dma_unmap_guest_page(अचिन्हित दीर्घ handle, dma_addr_t dma_addr)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu;
	काष्ठा kvmgt_vdev *vdev;
	काष्ठा gvt_dma *entry;

	अगर (!handle_valid(handle))
		वापस;

	vgpu = ((काष्ठा kvmgt_guest_info *)handle)->vgpu;
	vdev = kvmgt_vdev(vgpu);

	mutex_lock(&vdev->cache_lock);
	entry = __gvt_cache_find_dma_addr(vgpu, dma_addr);
	अगर (entry)
		kref_put(&entry->ref, __gvt_dma_release);
	mutex_unlock(&vdev->cache_lock);
पूर्ण

अटल पूर्णांक kvmgt_rw_gpa(अचिन्हित दीर्घ handle, अचिन्हित दीर्घ gpa,
			व्योम *buf, अचिन्हित दीर्घ len, bool ग_लिखो)
अणु
	काष्ठा kvmgt_guest_info *info;

	अगर (!handle_valid(handle))
		वापस -ESRCH;

	info = (काष्ठा kvmgt_guest_info *)handle;

	वापस vfio_dma_rw(kvmgt_vdev(info->vgpu)->vfio_group,
			   gpa, buf, len, ग_लिखो);
पूर्ण

अटल पूर्णांक kvmgt_पढ़ो_gpa(अचिन्हित दीर्घ handle, अचिन्हित दीर्घ gpa,
			व्योम *buf, अचिन्हित दीर्घ len)
अणु
	वापस kvmgt_rw_gpa(handle, gpa, buf, len, false);
पूर्ण

अटल पूर्णांक kvmgt_ग_लिखो_gpa(अचिन्हित दीर्घ handle, अचिन्हित दीर्घ gpa,
			व्योम *buf, अचिन्हित दीर्घ len)
अणु
	वापस kvmgt_rw_gpa(handle, gpa, buf, len, true);
पूर्ण

अटल अचिन्हित दीर्घ kvmgt_virt_to_pfn(व्योम *addr)
अणु
	वापस PFN_DOWN(__pa(addr));
पूर्ण

अटल bool kvmgt_is_valid_gfn(अचिन्हित दीर्घ handle, अचिन्हित दीर्घ gfn)
अणु
	काष्ठा kvmgt_guest_info *info;
	काष्ठा kvm *kvm;
	पूर्णांक idx;
	bool ret;

	अगर (!handle_valid(handle))
		वापस false;

	info = (काष्ठा kvmgt_guest_info *)handle;
	kvm = info->kvm;

	idx = srcu_पढ़ो_lock(&kvm->srcu);
	ret = kvm_is_visible_gfn(kvm, gfn);
	srcu_पढ़ो_unlock(&kvm->srcu, idx);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_gvt_mpt kvmgt_mpt = अणु
	.type = INTEL_GVT_HYPERVISOR_KVM,
	.host_init = kvmgt_host_init,
	.host_निकास = kvmgt_host_निकास,
	.attach_vgpu = kvmgt_attach_vgpu,
	.detach_vgpu = kvmgt_detach_vgpu,
	.inject_msi = kvmgt_inject_msi,
	.from_virt_to_mfn = kvmgt_virt_to_pfn,
	.enable_page_track = kvmgt_page_track_add,
	.disable_page_track = kvmgt_page_track_हटाओ,
	.पढ़ो_gpa = kvmgt_पढ़ो_gpa,
	.ग_लिखो_gpa = kvmgt_ग_लिखो_gpa,
	.gfn_to_mfn = kvmgt_gfn_to_pfn,
	.dma_map_guest_page = kvmgt_dma_map_guest_page,
	.dma_unmap_guest_page = kvmgt_dma_unmap_guest_page,
	.dma_pin_guest_page = kvmgt_dma_pin_guest_page,
	.set_opregion = kvmgt_set_opregion,
	.set_edid = kvmgt_set_edid,
	.get_vfio_device = kvmgt_get_vfio_device,
	.put_vfio_device = kvmgt_put_vfio_device,
	.is_valid_gfn = kvmgt_is_valid_gfn,
पूर्ण;

अटल पूर्णांक __init kvmgt_init(व्योम)
अणु
	अगर (पूर्णांकel_gvt_रेजिस्टर_hypervisor(&kvmgt_mpt) < 0)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल व्योम __निकास kvmgt_निकास(व्योम)
अणु
	पूर्णांकel_gvt_unरेजिस्टर_hypervisor();
पूर्ण

module_init(kvmgt_init);
module_निकास(kvmgt_निकास);

MODULE_LICENSE("GPL and additional rights");
MODULE_AUTHOR("Intel Corporation");
