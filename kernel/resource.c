<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	linux/kernel/resource.c
 *
 * Copyright (C) 1999	Linus Torvalds
 * Copyright (C) 1999	Martin Mares <mj@ucw.cz>
 *
 * Arbitrary resource management.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/fs.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/device.h>
#समावेश <linux/pfn.h>
#समावेश <linux/mm.h>
#समावेश <linux/mount.h>
#समावेश <linux/resource_ext.h>
#समावेश <uapi/linux/magic.h>
#समावेश <यंत्र/पन.स>


काष्ठा resource ioport_resource = अणु
	.name	= "PCI IO",
	.start	= 0,
	.end	= IO_SPACE_LIMIT,
	.flags	= IORESOURCE_IO,
पूर्ण;
EXPORT_SYMBOL(ioport_resource);

काष्ठा resource iomem_resource = अणु
	.name	= "PCI mem",
	.start	= 0,
	.end	= -1,
	.flags	= IORESOURCE_MEM,
पूर्ण;
EXPORT_SYMBOL(iomem_resource);

/* स्थिरraपूर्णांकs to be met जबतक allocating resources */
काष्ठा resource_स्थिरraपूर्णांक अणु
	resource_माप_प्रकार min, max, align;
	resource_माप_प्रकार (*alignf)(व्योम *, स्थिर काष्ठा resource *,
			resource_माप_प्रकार, resource_माप_प्रकार);
	व्योम *alignf_data;
पूर्ण;

अटल DEFINE_RWLOCK(resource_lock);

/*
 * For memory hotplug, there is no way to मुक्त resource entries allocated
 * by boot mem after the प्रणाली is up. So क्रम reusing the resource entry
 * we need to remember the resource.
 */
अटल काष्ठा resource *booपंचांगem_resource_मुक्त;
अटल DEFINE_SPINLOCK(booपंचांगem_resource_lock);

अटल काष्ठा resource *next_resource(काष्ठा resource *p)
अणु
	अगर (p->child)
		वापस p->child;
	जबतक (!p->sibling && p->parent)
		p = p->parent;
	वापस p->sibling;
पूर्ण

अटल व्योम *r_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा resource *p = v;
	(*pos)++;
	वापस (व्योम *)next_resource(p);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

क्रमागत अणु MAX_IORES_LEVEL = 5 पूर्ण;

अटल व्योम *r_start(काष्ठा seq_file *m, loff_t *pos)
	__acquires(resource_lock)
अणु
	काष्ठा resource *p = PDE_DATA(file_inode(m->file));
	loff_t l = 0;
	पढ़ो_lock(&resource_lock);
	क्रम (p = p->child; p && l < *pos; p = r_next(m, p, &l))
		;
	वापस p;
पूर्ण

अटल व्योम r_stop(काष्ठा seq_file *m, व्योम *v)
	__releases(resource_lock)
अणु
	पढ़ो_unlock(&resource_lock);
पूर्ण

अटल पूर्णांक r_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा resource *root = PDE_DATA(file_inode(m->file));
	काष्ठा resource *r = v, *p;
	अचिन्हित दीर्घ दीर्घ start, end;
	पूर्णांक width = root->end < 0x10000 ? 4 : 8;
	पूर्णांक depth;

	क्रम (depth = 0, p = r; depth < MAX_IORES_LEVEL; depth++, p = p->parent)
		अगर (p->parent == root)
			अवरोध;

	अगर (file_ns_capable(m->file, &init_user_ns, CAP_SYS_ADMIN)) अणु
		start = r->start;
		end = r->end;
	पूर्ण अन्यथा अणु
		start = end = 0;
	पूर्ण

	seq_म_लिखो(m, "%*s%0*llx-%0*llx : %s\n",
			depth * 2, "",
			width, start,
			width, end,
			r->name ? r->name : "<BAD>");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations resource_op = अणु
	.start	= r_start,
	.next	= r_next,
	.stop	= r_stop,
	.show	= r_show,
पूर्ण;

अटल पूर्णांक __init ioresources_init(व्योम)
अणु
	proc_create_seq_data("ioports", 0, शून्य, &resource_op,
			&ioport_resource);
	proc_create_seq_data("iomem", 0, शून्य, &resource_op, &iomem_resource);
	वापस 0;
पूर्ण
__initcall(ioresources_init);

#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल व्योम मुक्त_resource(काष्ठा resource *res)
अणु
	अगर (!res)
		वापस;

	अगर (!PageSlab(virt_to_head_page(res))) अणु
		spin_lock(&booपंचांगem_resource_lock);
		res->sibling = booपंचांगem_resource_मुक्त;
		booपंचांगem_resource_मुक्त = res;
		spin_unlock(&booपंचांगem_resource_lock);
	पूर्ण अन्यथा अणु
		kमुक्त(res);
	पूर्ण
पूर्ण

अटल काष्ठा resource *alloc_resource(gfp_t flags)
अणु
	काष्ठा resource *res = शून्य;

	spin_lock(&booपंचांगem_resource_lock);
	अगर (booपंचांगem_resource_मुक्त) अणु
		res = booपंचांगem_resource_मुक्त;
		booपंचांगem_resource_मुक्त = res->sibling;
	पूर्ण
	spin_unlock(&booपंचांगem_resource_lock);

	अगर (res)
		स_रखो(res, 0, माप(काष्ठा resource));
	अन्यथा
		res = kzalloc(माप(काष्ठा resource), flags);

	वापस res;
पूर्ण

/* Return the conflict entry अगर you can't request it */
अटल काष्ठा resource * __request_resource(काष्ठा resource *root, काष्ठा resource *new)
अणु
	resource_माप_प्रकार start = new->start;
	resource_माप_प्रकार end = new->end;
	काष्ठा resource *पंचांगp, **p;

	अगर (end < start)
		वापस root;
	अगर (start < root->start)
		वापस root;
	अगर (end > root->end)
		वापस root;
	p = &root->child;
	क्रम (;;) अणु
		पंचांगp = *p;
		अगर (!पंचांगp || पंचांगp->start > end) अणु
			new->sibling = पंचांगp;
			*p = new;
			new->parent = root;
			वापस शून्य;
		पूर्ण
		p = &पंचांगp->sibling;
		अगर (पंचांगp->end < start)
			जारी;
		वापस पंचांगp;
	पूर्ण
पूर्ण

अटल पूर्णांक __release_resource(काष्ठा resource *old, bool release_child)
अणु
	काष्ठा resource *पंचांगp, **p, *chd;

	p = &old->parent->child;
	क्रम (;;) अणु
		पंचांगp = *p;
		अगर (!पंचांगp)
			अवरोध;
		अगर (पंचांगp == old) अणु
			अगर (release_child || !(पंचांगp->child)) अणु
				*p = पंचांगp->sibling;
			पूर्ण अन्यथा अणु
				क्रम (chd = पंचांगp->child;; chd = chd->sibling) अणु
					chd->parent = पंचांगp->parent;
					अगर (!(chd->sibling))
						अवरोध;
				पूर्ण
				*p = पंचांगp->child;
				chd->sibling = पंचांगp->sibling;
			पूर्ण
			old->parent = शून्य;
			वापस 0;
		पूर्ण
		p = &पंचांगp->sibling;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम __release_child_resources(काष्ठा resource *r)
अणु
	काष्ठा resource *पंचांगp, *p;
	resource_माप_प्रकार size;

	p = r->child;
	r->child = शून्य;
	जबतक (p) अणु
		पंचांगp = p;
		p = p->sibling;

		पंचांगp->parent = शून्य;
		पंचांगp->sibling = शून्य;
		__release_child_resources(पंचांगp);

		prपूर्णांकk(KERN_DEBUG "release child resource %pR\n", पंचांगp);
		/* need to restore size, and keep flags */
		size = resource_size(पंचांगp);
		पंचांगp->start = 0;
		पंचांगp->end = size - 1;
	पूर्ण
पूर्ण

व्योम release_child_resources(काष्ठा resource *r)
अणु
	ग_लिखो_lock(&resource_lock);
	__release_child_resources(r);
	ग_लिखो_unlock(&resource_lock);
पूर्ण

/**
 * request_resource_conflict - request and reserve an I/O or memory resource
 * @root: root resource descriptor
 * @new: resource descriptor desired by caller
 *
 * Returns 0 क्रम success, conflict resource on error.
 */
काष्ठा resource *request_resource_conflict(काष्ठा resource *root, काष्ठा resource *new)
अणु
	काष्ठा resource *conflict;

	ग_लिखो_lock(&resource_lock);
	conflict = __request_resource(root, new);
	ग_लिखो_unlock(&resource_lock);
	वापस conflict;
पूर्ण

/**
 * request_resource - request and reserve an I/O or memory resource
 * @root: root resource descriptor
 * @new: resource descriptor desired by caller
 *
 * Returns 0 क्रम success, negative error code on error.
 */
पूर्णांक request_resource(काष्ठा resource *root, काष्ठा resource *new)
अणु
	काष्ठा resource *conflict;

	conflict = request_resource_conflict(root, new);
	वापस conflict ? -EBUSY : 0;
पूर्ण

EXPORT_SYMBOL(request_resource);

/**
 * release_resource - release a previously reserved resource
 * @old: resource poपूर्णांकer
 */
पूर्णांक release_resource(काष्ठा resource *old)
अणु
	पूर्णांक retval;

	ग_लिखो_lock(&resource_lock);
	retval = __release_resource(old, true);
	ग_लिखो_unlock(&resource_lock);
	वापस retval;
पूर्ण

EXPORT_SYMBOL(release_resource);

/**
 * find_next_iomem_res - Finds the lowest iomem resource that covers part of
 *			 [@start..@end].
 *
 * If a resource is found, वापसs 0 and @*res is overwritten with the part
 * of the resource that's within [@start..@end]; अगर none is found, वापसs
 * -ENODEV.  Returns -EINVAL क्रम invalid parameters.
 *
 * @start:	start address of the resource searched क्रम
 * @end:	end address of same resource
 * @flags:	flags which the resource must have
 * @desc:	descriptor the resource must have
 * @res:	वापस ptr, अगर resource found
 *
 * The caller must specअगरy @start, @end, @flags, and @desc
 * (which may be IORES_DESC_NONE).
 */
अटल पूर्णांक find_next_iomem_res(resource_माप_प्रकार start, resource_माप_प्रकार end,
			       अचिन्हित दीर्घ flags, अचिन्हित दीर्घ desc,
			       काष्ठा resource *res)
अणु
	काष्ठा resource *p;

	अगर (!res)
		वापस -EINVAL;

	अगर (start >= end)
		वापस -EINVAL;

	पढ़ो_lock(&resource_lock);

	क्रम (p = iomem_resource.child; p; p = next_resource(p)) अणु
		/* If we passed the resource we are looking क्रम, stop */
		अगर (p->start > end) अणु
			p = शून्य;
			अवरोध;
		पूर्ण

		/* Skip until we find a range that matches what we look क्रम */
		अगर (p->end < start)
			जारी;

		अगर ((p->flags & flags) != flags)
			जारी;
		अगर ((desc != IORES_DESC_NONE) && (desc != p->desc))
			जारी;

		/* Found a match, अवरोध */
		अवरोध;
	पूर्ण

	अगर (p) अणु
		/* copy data */
		*res = (काष्ठा resource) अणु
			.start = max(start, p->start),
			.end = min(end, p->end),
			.flags = p->flags,
			.desc = p->desc,
			.parent = p->parent,
		पूर्ण;
	पूर्ण

	पढ़ो_unlock(&resource_lock);
	वापस p ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक __walk_iomem_res_desc(resource_माप_प्रकार start, resource_माप_प्रकार end,
				 अचिन्हित दीर्घ flags, अचिन्हित दीर्घ desc,
				 व्योम *arg,
				 पूर्णांक (*func)(काष्ठा resource *, व्योम *))
अणु
	काष्ठा resource res;
	पूर्णांक ret = -EINVAL;

	जबतक (start < end &&
	       !find_next_iomem_res(start, end, flags, desc, &res)) अणु
		ret = (*func)(&res, arg);
		अगर (ret)
			अवरोध;

		start = res.end + 1;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * walk_iomem_res_desc - Walks through iomem resources and calls func()
 *			 with matching resource ranges.
 * *
 * @desc: I/O resource descriptor. Use IORES_DESC_NONE to skip @desc check.
 * @flags: I/O resource flags
 * @start: start addr
 * @end: end addr
 * @arg: function argument क्रम the callback @func
 * @func: callback function that is called क्रम each qualअगरying resource area
 *
 * All the memory ranges which overlap start,end and also match flags and
 * desc are valid candidates.
 *
 * NOTE: For a new descriptor search, define a new IORES_DESC in
 * <linux/ioport.h> and set it in 'desc' of a target resource entry.
 */
पूर्णांक walk_iomem_res_desc(अचिन्हित दीर्घ desc, अचिन्हित दीर्घ flags, u64 start,
		u64 end, व्योम *arg, पूर्णांक (*func)(काष्ठा resource *, व्योम *))
अणु
	वापस __walk_iomem_res_desc(start, end, flags, desc, arg, func);
पूर्ण
EXPORT_SYMBOL_GPL(walk_iomem_res_desc);

/*
 * This function calls the @func callback against all memory ranges of type
 * System RAM which are marked as IORESOURCE_SYSTEM_RAM and IORESOUCE_BUSY.
 * Now, this function is only क्रम System RAM, it deals with full ranges and
 * not PFNs. If resources are not PFN-aligned, dealing with PFNs can truncate
 * ranges.
 */
पूर्णांक walk_प्रणाली_ram_res(u64 start, u64 end, व्योम *arg,
			पूर्णांक (*func)(काष्ठा resource *, व्योम *))
अणु
	अचिन्हित दीर्घ flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;

	वापस __walk_iomem_res_desc(start, end, flags, IORES_DESC_NONE, arg,
				     func);
पूर्ण

/*
 * This function calls the @func callback against all memory ranges, which
 * are ranges marked as IORESOURCE_MEM and IORESOUCE_BUSY.
 */
पूर्णांक walk_mem_res(u64 start, u64 end, व्योम *arg,
		 पूर्णांक (*func)(काष्ठा resource *, व्योम *))
अणु
	अचिन्हित दीर्घ flags = IORESOURCE_MEM | IORESOURCE_BUSY;

	वापस __walk_iomem_res_desc(start, end, flags, IORES_DESC_NONE, arg,
				     func);
पूर्ण

/*
 * This function calls the @func callback against all memory ranges of type
 * System RAM which are marked as IORESOURCE_SYSTEM_RAM and IORESOUCE_BUSY.
 * It is to be used only क्रम System RAM.
 */
पूर्णांक walk_प्रणाली_ram_range(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages,
			  व्योम *arg, पूर्णांक (*func)(अचिन्हित दीर्घ, अचिन्हित दीर्घ, व्योम *))
अणु
	resource_माप_प्रकार start, end;
	अचिन्हित दीर्घ flags;
	काष्ठा resource res;
	अचिन्हित दीर्घ pfn, end_pfn;
	पूर्णांक ret = -EINVAL;

	start = (u64) start_pfn << PAGE_SHIFT;
	end = ((u64)(start_pfn + nr_pages) << PAGE_SHIFT) - 1;
	flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;
	जबतक (start < end &&
	       !find_next_iomem_res(start, end, flags, IORES_DESC_NONE, &res)) अणु
		pfn = PFN_UP(res.start);
		end_pfn = PFN_DOWN(res.end + 1);
		अगर (end_pfn > pfn)
			ret = (*func)(pfn, end_pfn - pfn, arg);
		अगर (ret)
			अवरोध;
		start = res.end + 1;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __is_ram(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages, व्योम *arg)
अणु
	वापस 1;
पूर्ण

/*
 * This generic page_is_ram() वापसs true अगर specअगरied address is
 * रेजिस्टरed as System RAM in iomem_resource list.
 */
पूर्णांक __weak page_is_ram(अचिन्हित दीर्घ pfn)
अणु
	वापस walk_प्रणाली_ram_range(pfn, 1, शून्य, __is_ram) == 1;
पूर्ण
EXPORT_SYMBOL_GPL(page_is_ram);

अटल पूर्णांक __region_पूर्णांकersects(resource_माप_प्रकार start, माप_प्रकार size,
			अचिन्हित दीर्घ flags, अचिन्हित दीर्घ desc)
अणु
	काष्ठा resource res;
	पूर्णांक type = 0; पूर्णांक other = 0;
	काष्ठा resource *p;

	res.start = start;
	res.end = start + size - 1;

	क्रम (p = iomem_resource.child; p ; p = p->sibling) अणु
		bool is_type = (((p->flags & flags) == flags) &&
				((desc == IORES_DESC_NONE) ||
				 (desc == p->desc)));

		अगर (resource_overlaps(p, &res))
			is_type ? type++ : other++;
	पूर्ण

	अगर (type == 0)
		वापस REGION_DISJOINT;

	अगर (other == 0)
		वापस REGION_INTERSECTS;

	वापस REGION_MIXED;
पूर्ण

/**
 * region_पूर्णांकersects() - determine पूर्णांकersection of region with known resources
 * @start: region start address
 * @size: size of region
 * @flags: flags of resource (in iomem_resource)
 * @desc: descriptor of resource (in iomem_resource) or IORES_DESC_NONE
 *
 * Check अगर the specअगरied region partially overlaps or fully eclipses a
 * resource identअगरied by @flags and @desc (optional with IORES_DESC_NONE).
 * Return REGION_DISJOINT अगर the region करोes not overlap @flags/@desc,
 * वापस REGION_MIXED अगर the region overlaps @flags/@desc and another
 * resource, and वापस REGION_INTERSECTS अगर the region overlaps @flags/@desc
 * and no other defined resource. Note that REGION_INTERSECTS is also
 * वापसed in the हाल when the specअगरied region overlaps RAM and undefined
 * memory holes.
 *
 * region_पूर्णांकersect() is used by memory remapping functions to ensure
 * the user is not remapping RAM and is a vast speed up over walking
 * through the resource table page by page.
 */
पूर्णांक region_पूर्णांकersects(resource_माप_प्रकार start, माप_प्रकार size, अचिन्हित दीर्घ flags,
		      अचिन्हित दीर्घ desc)
अणु
	पूर्णांक ret;

	पढ़ो_lock(&resource_lock);
	ret = __region_पूर्णांकersects(start, size, flags, desc);
	पढ़ो_unlock(&resource_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(region_पूर्णांकersects);

व्योम __weak arch_हटाओ_reservations(काष्ठा resource *avail)
अणु
पूर्ण

अटल resource_माप_प्रकार simple_align_resource(व्योम *data,
					     स्थिर काष्ठा resource *avail,
					     resource_माप_प्रकार size,
					     resource_माप_प्रकार align)
अणु
	वापस avail->start;
पूर्ण

अटल व्योम resource_clip(काष्ठा resource *res, resource_माप_प्रकार min,
			  resource_माप_प्रकार max)
अणु
	अगर (res->start < min)
		res->start = min;
	अगर (res->end > max)
		res->end = max;
पूर्ण

/*
 * Find empty slot in the resource tree with the given range and
 * alignment स्थिरraपूर्णांकs
 */
अटल पूर्णांक __find_resource(काष्ठा resource *root, काष्ठा resource *old,
			 काष्ठा resource *new,
			 resource_माप_प्रकार  size,
			 काष्ठा resource_स्थिरraपूर्णांक *स्थिरraपूर्णांक)
अणु
	काष्ठा resource *this = root->child;
	काष्ठा resource पंचांगp = *new, avail, alloc;

	पंचांगp.start = root->start;
	/*
	 * Skip past an allocated resource that starts at 0, since the assignment
	 * of this->start - 1 to पंचांगp->end below would cause an underflow.
	 */
	अगर (this && this->start == root->start) अणु
		पंचांगp.start = (this == old) ? old->start : this->end + 1;
		this = this->sibling;
	पूर्ण
	क्रम(;;) अणु
		अगर (this)
			पंचांगp.end = (this == old) ?  this->end : this->start - 1;
		अन्यथा
			पंचांगp.end = root->end;

		अगर (पंचांगp.end < पंचांगp.start)
			जाओ next;

		resource_clip(&पंचांगp, स्थिरraपूर्णांक->min, स्थिरraपूर्णांक->max);
		arch_हटाओ_reservations(&पंचांगp);

		/* Check क्रम overflow after ALIGN() */
		avail.start = ALIGN(पंचांगp.start, स्थिरraपूर्णांक->align);
		avail.end = पंचांगp.end;
		avail.flags = new->flags & ~IORESOURCE_UNSET;
		अगर (avail.start >= पंचांगp.start) अणु
			alloc.flags = avail.flags;
			alloc.start = स्थिरraपूर्णांक->alignf(स्थिरraपूर्णांक->alignf_data, &avail,
					size, स्थिरraपूर्णांक->align);
			alloc.end = alloc.start + size - 1;
			अगर (alloc.start <= alloc.end &&
			    resource_contains(&avail, &alloc)) अणु
				new->start = alloc.start;
				new->end = alloc.end;
				वापस 0;
			पूर्ण
		पूर्ण

next:		अगर (!this || this->end == root->end)
			अवरोध;

		अगर (this != old)
			पंचांगp.start = this->end + 1;
		this = this->sibling;
	पूर्ण
	वापस -EBUSY;
पूर्ण

/*
 * Find empty slot in the resource tree given range and alignment.
 */
अटल पूर्णांक find_resource(काष्ठा resource *root, काष्ठा resource *new,
			resource_माप_प्रकार size,
			काष्ठा resource_स्थिरraपूर्णांक  *स्थिरraपूर्णांक)
अणु
	वापस  __find_resource(root, शून्य, new, size, स्थिरraपूर्णांक);
पूर्ण

/**
 * पुनः_स्मृतिate_resource - allocate a slot in the resource tree given range & alignment.
 *	The resource will be relocated अगर the new size cannot be पुनः_स्मृतिated in the
 *	current location.
 *
 * @root: root resource descriptor
 * @old:  resource descriptor desired by caller
 * @newsize: new size of the resource descriptor
 * @स्थिरraपूर्णांक: the size and alignment स्थिरraपूर्णांकs to be met.
 */
अटल पूर्णांक पुनः_स्मृतिate_resource(काष्ठा resource *root, काष्ठा resource *old,
			       resource_माप_प्रकार newsize,
			       काष्ठा resource_स्थिरraपूर्णांक *स्थिरraपूर्णांक)
अणु
	पूर्णांक err=0;
	काष्ठा resource new = *old;
	काष्ठा resource *conflict;

	ग_लिखो_lock(&resource_lock);

	अगर ((err = __find_resource(root, old, &new, newsize, स्थिरraपूर्णांक)))
		जाओ out;

	अगर (resource_contains(&new, old)) अणु
		old->start = new.start;
		old->end = new.end;
		जाओ out;
	पूर्ण

	अगर (old->child) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (resource_contains(old, &new)) अणु
		old->start = new.start;
		old->end = new.end;
	पूर्ण अन्यथा अणु
		__release_resource(old, true);
		*old = new;
		conflict = __request_resource(root, old);
		BUG_ON(conflict);
	पूर्ण
out:
	ग_लिखो_unlock(&resource_lock);
	वापस err;
पूर्ण


/**
 * allocate_resource - allocate empty slot in the resource tree given range & alignment.
 * 	The resource will be पुनः_स्मृतिated with a new size अगर it was alपढ़ोy allocated
 * @root: root resource descriptor
 * @new: resource descriptor desired by caller
 * @size: requested resource region size
 * @min: minimum boundary to allocate
 * @max: maximum boundary to allocate
 * @align: alignment requested, in bytes
 * @alignf: alignment function, optional, called अगर not शून्य
 * @alignf_data: arbitrary data to pass to the @alignf function
 */
पूर्णांक allocate_resource(काष्ठा resource *root, काष्ठा resource *new,
		      resource_माप_प्रकार size, resource_माप_प्रकार min,
		      resource_माप_प्रकार max, resource_माप_प्रकार align,
		      resource_माप_प्रकार (*alignf)(व्योम *,
						स्थिर काष्ठा resource *,
						resource_माप_प्रकार,
						resource_माप_प्रकार),
		      व्योम *alignf_data)
अणु
	पूर्णांक err;
	काष्ठा resource_स्थिरraपूर्णांक स्थिरraपूर्णांक;

	अगर (!alignf)
		alignf = simple_align_resource;

	स्थिरraपूर्णांक.min = min;
	स्थिरraपूर्णांक.max = max;
	स्थिरraपूर्णांक.align = align;
	स्थिरraपूर्णांक.alignf = alignf;
	स्थिरraपूर्णांक.alignf_data = alignf_data;

	अगर ( new->parent ) अणु
		/* resource is alपढ़ोy allocated, try पुनः_स्मृतिating with
		   the new स्थिरraपूर्णांकs */
		वापस पुनः_स्मृतिate_resource(root, new, size, &स्थिरraपूर्णांक);
	पूर्ण

	ग_लिखो_lock(&resource_lock);
	err = find_resource(root, new, size, &स्थिरraपूर्णांक);
	अगर (err >= 0 && __request_resource(root, new))
		err = -EBUSY;
	ग_लिखो_unlock(&resource_lock);
	वापस err;
पूर्ण

EXPORT_SYMBOL(allocate_resource);

/**
 * lookup_resource - find an existing resource by a resource start address
 * @root: root resource descriptor
 * @start: resource start address
 *
 * Returns a poपूर्णांकer to the resource अगर found, शून्य otherwise
 */
काष्ठा resource *lookup_resource(काष्ठा resource *root, resource_माप_प्रकार start)
अणु
	काष्ठा resource *res;

	पढ़ो_lock(&resource_lock);
	क्रम (res = root->child; res; res = res->sibling) अणु
		अगर (res->start == start)
			अवरोध;
	पूर्ण
	पढ़ो_unlock(&resource_lock);

	वापस res;
पूर्ण

/*
 * Insert a resource पूर्णांकo the resource tree. If successful, वापस शून्य,
 * otherwise वापस the conflicting resource (compare to __request_resource())
 */
अटल काष्ठा resource * __insert_resource(काष्ठा resource *parent, काष्ठा resource *new)
अणु
	काष्ठा resource *first, *next;

	क्रम (;; parent = first) अणु
		first = __request_resource(parent, new);
		अगर (!first)
			वापस first;

		अगर (first == parent)
			वापस first;
		अगर (WARN_ON(first == new))	/* duplicated insertion */
			वापस first;

		अगर ((first->start > new->start) || (first->end < new->end))
			अवरोध;
		अगर ((first->start == new->start) && (first->end == new->end))
			अवरोध;
	पूर्ण

	क्रम (next = first; ; next = next->sibling) अणु
		/* Partial overlap? Bad, and unfixable */
		अगर (next->start < new->start || next->end > new->end)
			वापस next;
		अगर (!next->sibling)
			अवरोध;
		अगर (next->sibling->start > new->end)
			अवरोध;
	पूर्ण

	new->parent = parent;
	new->sibling = next->sibling;
	new->child = first;

	next->sibling = शून्य;
	क्रम (next = first; next; next = next->sibling)
		next->parent = new;

	अगर (parent->child == first) अणु
		parent->child = new;
	पूर्ण अन्यथा अणु
		next = parent->child;
		जबतक (next->sibling != first)
			next = next->sibling;
		next->sibling = new;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * insert_resource_conflict - Inserts resource in the resource tree
 * @parent: parent of the new resource
 * @new: new resource to insert
 *
 * Returns 0 on success, conflict resource अगर the resource can't be inserted.
 *
 * This function is equivalent to request_resource_conflict when no conflict
 * happens. If a conflict happens, and the conflicting resources
 * entirely fit within the range of the new resource, then the new
 * resource is inserted and the conflicting resources become children of
 * the new resource.
 *
 * This function is पूर्णांकended क्रम producers of resources, such as FW modules
 * and bus drivers.
 */
काष्ठा resource *insert_resource_conflict(काष्ठा resource *parent, काष्ठा resource *new)
अणु
	काष्ठा resource *conflict;

	ग_लिखो_lock(&resource_lock);
	conflict = __insert_resource(parent, new);
	ग_लिखो_unlock(&resource_lock);
	वापस conflict;
पूर्ण

/**
 * insert_resource - Inserts a resource in the resource tree
 * @parent: parent of the new resource
 * @new: new resource to insert
 *
 * Returns 0 on success, -EBUSY अगर the resource can't be inserted.
 *
 * This function is पूर्णांकended क्रम producers of resources, such as FW modules
 * and bus drivers.
 */
पूर्णांक insert_resource(काष्ठा resource *parent, काष्ठा resource *new)
अणु
	काष्ठा resource *conflict;

	conflict = insert_resource_conflict(parent, new);
	वापस conflict ? -EBUSY : 0;
पूर्ण
EXPORT_SYMBOL_GPL(insert_resource);

/**
 * insert_resource_expand_to_fit - Insert a resource पूर्णांकo the resource tree
 * @root: root resource descriptor
 * @new: new resource to insert
 *
 * Insert a resource पूर्णांकo the resource tree, possibly expanding it in order
 * to make it encompass any conflicting resources.
 */
व्योम insert_resource_expand_to_fit(काष्ठा resource *root, काष्ठा resource *new)
अणु
	अगर (new->parent)
		वापस;

	ग_लिखो_lock(&resource_lock);
	क्रम (;;) अणु
		काष्ठा resource *conflict;

		conflict = __insert_resource(root, new);
		अगर (!conflict)
			अवरोध;
		अगर (conflict == root)
			अवरोध;

		/* Ok, expand resource to cover the conflict, then try again .. */
		अगर (conflict->start < new->start)
			new->start = conflict->start;
		अगर (conflict->end > new->end)
			new->end = conflict->end;

		prपूर्णांकk("Expanded resource %s due to conflict with %s\n", new->name, conflict->name);
	पूर्ण
	ग_लिखो_unlock(&resource_lock);
पूर्ण

/**
 * हटाओ_resource - Remove a resource in the resource tree
 * @old: resource to हटाओ
 *
 * Returns 0 on success, -EINVAL अगर the resource is not valid.
 *
 * This function हटाओs a resource previously inserted by insert_resource()
 * or insert_resource_conflict(), and moves the children (अगर any) up to
 * where they were beक्रमe.  insert_resource() and insert_resource_conflict()
 * insert a new resource, and move any conflicting resources करोwn to the
 * children of the new resource.
 *
 * insert_resource(), insert_resource_conflict() and हटाओ_resource() are
 * पूर्णांकended क्रम producers of resources, such as FW modules and bus drivers.
 */
पूर्णांक हटाओ_resource(काष्ठा resource *old)
अणु
	पूर्णांक retval;

	ग_लिखो_lock(&resource_lock);
	retval = __release_resource(old, false);
	ग_लिखो_unlock(&resource_lock);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(हटाओ_resource);

अटल पूर्णांक __adjust_resource(काष्ठा resource *res, resource_माप_प्रकार start,
				resource_माप_प्रकार size)
अणु
	काष्ठा resource *पंचांगp, *parent = res->parent;
	resource_माप_प्रकार end = start + size - 1;
	पूर्णांक result = -EBUSY;

	अगर (!parent)
		जाओ skip;

	अगर ((start < parent->start) || (end > parent->end))
		जाओ out;

	अगर (res->sibling && (res->sibling->start <= end))
		जाओ out;

	पंचांगp = parent->child;
	अगर (पंचांगp != res) अणु
		जबतक (पंचांगp->sibling != res)
			पंचांगp = पंचांगp->sibling;
		अगर (start <= पंचांगp->end)
			जाओ out;
	पूर्ण

skip:
	क्रम (पंचांगp = res->child; पंचांगp; पंचांगp = पंचांगp->sibling)
		अगर ((पंचांगp->start < start) || (पंचांगp->end > end))
			जाओ out;

	res->start = start;
	res->end = end;
	result = 0;

 out:
	वापस result;
पूर्ण

/**
 * adjust_resource - modअगरy a resource's start and size
 * @res: resource to modअगरy
 * @start: new start value
 * @size: new size
 *
 * Given an existing resource, change its start and size to match the
 * arguments.  Returns 0 on success, -EBUSY अगर it can't fit.
 * Existing children of the resource are assumed to be immutable.
 */
पूर्णांक adjust_resource(काष्ठा resource *res, resource_माप_प्रकार start,
		    resource_माप_प्रकार size)
अणु
	पूर्णांक result;

	ग_लिखो_lock(&resource_lock);
	result = __adjust_resource(res, start, size);
	ग_लिखो_unlock(&resource_lock);
	वापस result;
पूर्ण
EXPORT_SYMBOL(adjust_resource);

अटल व्योम __init
__reserve_region_with_split(काष्ठा resource *root, resource_माप_प्रकार start,
			    resource_माप_प्रकार end, स्थिर अक्षर *name)
अणु
	काष्ठा resource *parent = root;
	काष्ठा resource *conflict;
	काष्ठा resource *res = alloc_resource(GFP_ATOMIC);
	काष्ठा resource *next_res = शून्य;
	पूर्णांक type = resource_type(root);

	अगर (!res)
		वापस;

	res->name = name;
	res->start = start;
	res->end = end;
	res->flags = type | IORESOURCE_BUSY;
	res->desc = IORES_DESC_NONE;

	जबतक (1) अणु

		conflict = __request_resource(parent, res);
		अगर (!conflict) अणु
			अगर (!next_res)
				अवरोध;
			res = next_res;
			next_res = शून्य;
			जारी;
		पूर्ण

		/* conflict covered whole area */
		अगर (conflict->start <= res->start &&
				conflict->end >= res->end) अणु
			मुक्त_resource(res);
			WARN_ON(next_res);
			अवरोध;
		पूर्ण

		/* failed, split and try again */
		अगर (conflict->start > res->start) अणु
			end = res->end;
			res->end = conflict->start - 1;
			अगर (conflict->end < end) अणु
				next_res = alloc_resource(GFP_ATOMIC);
				अगर (!next_res) अणु
					मुक्त_resource(res);
					अवरोध;
				पूर्ण
				next_res->name = name;
				next_res->start = conflict->end + 1;
				next_res->end = end;
				next_res->flags = type | IORESOURCE_BUSY;
				next_res->desc = IORES_DESC_NONE;
			पूर्ण
		पूर्ण अन्यथा अणु
			res->start = conflict->end + 1;
		पूर्ण
	पूर्ण

पूर्ण

व्योम __init
reserve_region_with_split(काष्ठा resource *root, resource_माप_प्रकार start,
			  resource_माप_प्रकार end, स्थिर अक्षर *name)
अणु
	पूर्णांक पात = 0;

	ग_लिखो_lock(&resource_lock);
	अगर (root->start > start || root->end < end) अणु
		pr_err("requested range [0x%llx-0x%llx] not in root %pr\n",
		       (अचिन्हित दीर्घ दीर्घ)start, (अचिन्हित दीर्घ दीर्घ)end,
		       root);
		अगर (start > root->end || end < root->start)
			पात = 1;
		अन्यथा अणु
			अगर (end > root->end)
				end = root->end;
			अगर (start < root->start)
				start = root->start;
			pr_err("fixing request to [0x%llx-0x%llx]\n",
			       (अचिन्हित दीर्घ दीर्घ)start,
			       (अचिन्हित दीर्घ दीर्घ)end);
		पूर्ण
		dump_stack();
	पूर्ण
	अगर (!पात)
		__reserve_region_with_split(root, start, end, name);
	ग_लिखो_unlock(&resource_lock);
पूर्ण

/**
 * resource_alignment - calculate resource's alignment
 * @res: resource poपूर्णांकer
 *
 * Returns alignment on success, 0 (invalid alignment) on failure.
 */
resource_माप_प्रकार resource_alignment(काष्ठा resource *res)
अणु
	चयन (res->flags & (IORESOURCE_SIZEALIGN | IORESOURCE_STARTALIGN)) अणु
	हाल IORESOURCE_SIZEALIGN:
		वापस resource_size(res);
	हाल IORESOURCE_STARTALIGN:
		वापस res->start;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * This is compatibility stuff क्रम IO resources.
 *
 * Note how this, unlike the above, knows about
 * the IO flag meanings (busy etc).
 *
 * request_region creates a new busy region.
 *
 * release_region releases a matching busy region.
 */

अटल DECLARE_WAIT_QUEUE_HEAD(muxed_resource_रुको);

अटल काष्ठा inode *iomem_inode;

#अगर_घोषित CONFIG_IO_STRICT_DEVMEM
अटल व्योम revoke_iomem(काष्ठा resource *res)
अणु
	/* pairs with smp_store_release() in iomem_init_inode() */
	काष्ठा inode *inode = smp_load_acquire(&iomem_inode);

	/*
	 * Check that the initialization has completed. Losing the race
	 * is ok because it means drivers are claiming resources beक्रमe
	 * the fs_initcall level of init and prevent iomem_get_mapping users
	 * from establishing mappings.
	 */
	अगर (!inode)
		वापस;

	/*
	 * The expectation is that the driver has successfully marked
	 * the resource busy by this poपूर्णांक, so devmem_is_allowed()
	 * should start वापसing false, however क्रम perक्रमmance this
	 * करोes not iterate the entire resource range.
	 */
	अगर (devmem_is_allowed(PHYS_PFN(res->start)) &&
	    devmem_is_allowed(PHYS_PFN(res->end))) अणु
		/*
		 * *cringe* iomem=relaxed says "go ahead, what's the
		 * worst that can happen?"
		 */
		वापस;
	पूर्ण

	unmap_mapping_range(inode->i_mapping, res->start, resource_size(res), 1);
पूर्ण
#अन्यथा
अटल व्योम revoke_iomem(काष्ठा resource *res) अणुपूर्ण
#पूर्ण_अगर

काष्ठा address_space *iomem_get_mapping(व्योम)
अणु
	/*
	 * This function is only called from file खोलो paths, hence guaranteed
	 * that fs_initcalls have completed and no need to check क्रम शून्य. But
	 * since revoke_iomem can be called beक्रमe the initcall we still need
	 * the barrier to appease checkers.
	 */
	वापस smp_load_acquire(&iomem_inode)->i_mapping;
पूर्ण

अटल पूर्णांक __request_region_locked(काष्ठा resource *res, काष्ठा resource *parent,
				   resource_माप_प्रकार start, resource_माप_प्रकार n,
				   स्थिर अक्षर *name, पूर्णांक flags)
अणु
	DECLARE_WAITQUEUE(रुको, current);

	res->name = name;
	res->start = start;
	res->end = start + n - 1;

	क्रम (;;) अणु
		काष्ठा resource *conflict;

		res->flags = resource_type(parent) | resource_ext_type(parent);
		res->flags |= IORESOURCE_BUSY | flags;
		res->desc = parent->desc;

		conflict = __request_resource(parent, res);
		अगर (!conflict)
			अवरोध;
		/*
		 * mm/hmm.c reserves physical addresses which then
		 * become unavailable to other users.  Conflicts are
		 * not expected.  Warn to aid debugging अगर encountered.
		 */
		अगर (conflict->desc == IORES_DESC_DEVICE_PRIVATE_MEMORY) अणु
			pr_warn("Unaddressable device %s %pR conflicts with %pR",
				conflict->name, conflict, res);
		पूर्ण
		अगर (conflict != parent) अणु
			अगर (!(conflict->flags & IORESOURCE_BUSY)) अणु
				parent = conflict;
				जारी;
			पूर्ण
		पूर्ण
		अगर (conflict->flags & flags & IORESOURCE_MUXED) अणु
			add_रुको_queue(&muxed_resource_रुको, &रुको);
			ग_लिखो_unlock(&resource_lock);
			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule();
			हटाओ_रुको_queue(&muxed_resource_रुको, &रुको);
			ग_लिखो_lock(&resource_lock);
			जारी;
		पूर्ण
		/* Uhhuh, that didn't work out.. */
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * __request_region - create a new busy resource region
 * @parent: parent resource descriptor
 * @start: resource start address
 * @n: resource region size
 * @name: reserving caller's ID string
 * @flags: IO resource flags
 */
काष्ठा resource *__request_region(काष्ठा resource *parent,
				  resource_माप_प्रकार start, resource_माप_प्रकार n,
				  स्थिर अक्षर *name, पूर्णांक flags)
अणु
	काष्ठा resource *res = alloc_resource(GFP_KERNEL);
	पूर्णांक ret;

	अगर (!res)
		वापस शून्य;

	ग_लिखो_lock(&resource_lock);
	ret = __request_region_locked(res, parent, start, n, name, flags);
	ग_लिखो_unlock(&resource_lock);

	अगर (ret) अणु
		मुक्त_resource(res);
		वापस शून्य;
	पूर्ण

	अगर (parent == &iomem_resource)
		revoke_iomem(res);

	वापस res;
पूर्ण
EXPORT_SYMBOL(__request_region);

/**
 * __release_region - release a previously reserved resource region
 * @parent: parent resource descriptor
 * @start: resource start address
 * @n: resource region size
 *
 * The described resource region must match a currently busy region.
 */
व्योम __release_region(काष्ठा resource *parent, resource_माप_प्रकार start,
		      resource_माप_प्रकार n)
अणु
	काष्ठा resource **p;
	resource_माप_प्रकार end;

	p = &parent->child;
	end = start + n - 1;

	ग_लिखो_lock(&resource_lock);

	क्रम (;;) अणु
		काष्ठा resource *res = *p;

		अगर (!res)
			अवरोध;
		अगर (res->start <= start && res->end >= end) अणु
			अगर (!(res->flags & IORESOURCE_BUSY)) अणु
				p = &res->child;
				जारी;
			पूर्ण
			अगर (res->start != start || res->end != end)
				अवरोध;
			*p = res->sibling;
			ग_लिखो_unlock(&resource_lock);
			अगर (res->flags & IORESOURCE_MUXED)
				wake_up(&muxed_resource_रुको);
			मुक्त_resource(res);
			वापस;
		पूर्ण
		p = &res->sibling;
	पूर्ण

	ग_लिखो_unlock(&resource_lock);

	prपूर्णांकk(KERN_WARNING "Trying to free nonexistent resource "
		"<%016llx-%016llx>\n", (अचिन्हित दीर्घ दीर्घ)start,
		(अचिन्हित दीर्घ दीर्घ)end);
पूर्ण
EXPORT_SYMBOL(__release_region);

#अगर_घोषित CONFIG_MEMORY_HOTREMOVE
/**
 * release_mem_region_adjustable - release a previously reserved memory region
 * @start: resource start address
 * @size: resource region size
 *
 * This पूर्णांकerface is पूर्णांकended क्रम memory hot-delete.  The requested region
 * is released from a currently busy memory resource.  The requested region
 * must either match exactly or fit पूर्णांकo a single busy resource entry.  In
 * the latter हाल, the reमुख्यing resource is adjusted accordingly.
 * Existing children of the busy memory resource must be immutable in the
 * request.
 *
 * Note:
 * - Additional release conditions, such as overlapping region, can be
 *   supported after they are confirmed as valid हालs.
 * - When a busy memory resource माला_लो split पूर्णांकo two entries, the code
 *   assumes that all children reमुख्य in the lower address entry क्रम
 *   simplicity.  Enhance this logic when necessary.
 */
व्योम release_mem_region_adjustable(resource_माप_प्रकार start, resource_माप_प्रकार size)
अणु
	काष्ठा resource *parent = &iomem_resource;
	काष्ठा resource *new_res = शून्य;
	bool alloc_nofail = false;
	काष्ठा resource **p;
	काष्ठा resource *res;
	resource_माप_प्रकार end;

	end = start + size - 1;
	अगर (WARN_ON_ONCE((start < parent->start) || (end > parent->end)))
		वापस;

	/*
	 * We मुक्त up quite a lot of memory on memory hotunplug (esp., memap),
	 * just beक्रमe releasing the region. This is highly unlikely to
	 * fail - let's play save and make it never fail as the caller cannot
	 * perक्रमm any error handling (e.g., trying to re-add memory will fail
	 * similarly).
	 */
retry:
	new_res = alloc_resource(GFP_KERNEL | (alloc_nofail ? __GFP_NOFAIL : 0));

	p = &parent->child;
	ग_लिखो_lock(&resource_lock);

	जबतक ((res = *p)) अणु
		अगर (res->start >= end)
			अवरोध;

		/* look क्रम the next resource अगर it करोes not fit पूर्णांकo */
		अगर (res->start > start || res->end < end) अणु
			p = &res->sibling;
			जारी;
		पूर्ण

		/*
		 * All memory regions added from memory-hotplug path have the
		 * flag IORESOURCE_SYSTEM_RAM. If the resource करोes not have
		 * this flag, we know that we are dealing with a resource coming
		 * from HMM/devm. HMM/devm use another mechanism to add/release
		 * a resource. This goes via devm_request_mem_region and
		 * devm_release_mem_region.
		 * HMM/devm take care to release their resources when they want,
		 * so अगर we are dealing with them, let us just back off here.
		 */
		अगर (!(res->flags & IORESOURCE_SYSRAM)) अणु
			अवरोध;
		पूर्ण

		अगर (!(res->flags & IORESOURCE_MEM))
			अवरोध;

		अगर (!(res->flags & IORESOURCE_BUSY)) अणु
			p = &res->child;
			जारी;
		पूर्ण

		/* found the target resource; let's adjust accordingly */
		अगर (res->start == start && res->end == end) अणु
			/* मुक्त the whole entry */
			*p = res->sibling;
			मुक्त_resource(res);
		पूर्ण अन्यथा अगर (res->start == start && res->end != end) अणु
			/* adjust the start */
			WARN_ON_ONCE(__adjust_resource(res, end + 1,
						       res->end - end));
		पूर्ण अन्यथा अगर (res->start != start && res->end == end) अणु
			/* adjust the end */
			WARN_ON_ONCE(__adjust_resource(res, res->start,
						       start - res->start));
		पूर्ण अन्यथा अणु
			/* split पूर्णांकo two entries - we need a new resource */
			अगर (!new_res) अणु
				new_res = alloc_resource(GFP_ATOMIC);
				अगर (!new_res) अणु
					alloc_nofail = true;
					ग_लिखो_unlock(&resource_lock);
					जाओ retry;
				पूर्ण
			पूर्ण
			new_res->name = res->name;
			new_res->start = end + 1;
			new_res->end = res->end;
			new_res->flags = res->flags;
			new_res->desc = res->desc;
			new_res->parent = res->parent;
			new_res->sibling = res->sibling;
			new_res->child = शून्य;

			अगर (WARN_ON_ONCE(__adjust_resource(res, res->start,
							   start - res->start)))
				अवरोध;
			res->sibling = new_res;
			new_res = शून्य;
		पूर्ण

		अवरोध;
	पूर्ण

	ग_लिखो_unlock(&resource_lock);
	मुक्त_resource(new_res);
पूर्ण
#पूर्ण_अगर	/* CONFIG_MEMORY_HOTREMOVE */

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
अटल bool प्रणाली_ram_resources_mergeable(काष्ठा resource *r1,
					   काष्ठा resource *r2)
अणु
	/* We assume either r1 or r2 is IORESOURCE_SYSRAM_MERGEABLE. */
	वापस r1->flags == r2->flags && r1->end + 1 == r2->start &&
	       r1->name == r2->name && r1->desc == r2->desc &&
	       !r1->child && !r2->child;
पूर्ण

/**
 * merge_प्रणाली_ram_resource - mark the System RAM resource mergeable and try to
 *	merge it with adjacent, mergeable resources
 * @res: resource descriptor
 *
 * This पूर्णांकerface is पूर्णांकended क्रम memory hotplug, whereby lots of contiguous
 * प्रणाली ram resources are added (e.g., via add_memory*()) by a driver, and
 * the actual resource boundaries are not of पूर्णांकerest (e.g., it might be
 * relevant क्रम DIMMs). Only resources that are marked mergeable, that have the
 * same parent, and that करोn't have any children are considered. All mergeable
 * resources must be immutable during the request.
 *
 * Note:
 * - The caller has to make sure that no poपूर्णांकers to resources that are
 *   marked mergeable are used anymore after this call - the resource might
 *   be मुक्तd and the poपूर्णांकer might be stale!
 * - release_mem_region_adjustable() will split on demand on memory hotunplug
 */
व्योम merge_प्रणाली_ram_resource(काष्ठा resource *res)
अणु
	स्थिर अचिन्हित दीर्घ flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;
	काष्ठा resource *cur;

	अगर (WARN_ON_ONCE((res->flags & flags) != flags))
		वापस;

	ग_लिखो_lock(&resource_lock);
	res->flags |= IORESOURCE_SYSRAM_MERGEABLE;

	/* Try to merge with next item in the list. */
	cur = res->sibling;
	अगर (cur && प्रणाली_ram_resources_mergeable(res, cur)) अणु
		res->end = cur->end;
		res->sibling = cur->sibling;
		मुक्त_resource(cur);
	पूर्ण

	/* Try to merge with previous item in the list. */
	cur = res->parent->child;
	जबतक (cur && cur->sibling != res)
		cur = cur->sibling;
	अगर (cur && प्रणाली_ram_resources_mergeable(cur, res)) अणु
		cur->end = res->end;
		cur->sibling = res->sibling;
		मुक्त_resource(res);
	पूर्ण
	ग_लिखो_unlock(&resource_lock);
पूर्ण
#पूर्ण_अगर	/* CONFIG_MEMORY_HOTPLUG */

/*
 * Managed region resource
 */
अटल व्योम devm_resource_release(काष्ठा device *dev, व्योम *ptr)
अणु
	काष्ठा resource **r = ptr;

	release_resource(*r);
पूर्ण

/**
 * devm_request_resource() - request and reserve an I/O or memory resource
 * @dev: device क्रम which to request the resource
 * @root: root of the resource tree from which to request the resource
 * @new: descriptor of the resource to request
 *
 * This is a device-managed version of request_resource(). There is usually
 * no need to release resources requested by this function explicitly since
 * that will be taken care of when the device is unbound from its driver.
 * If क्रम some reason the resource needs to be released explicitly, because
 * of ordering issues क्रम example, drivers must call devm_release_resource()
 * rather than the regular release_resource().
 *
 * When a conflict is detected between any existing resources and the newly
 * requested resource, an error message will be prपूर्णांकed.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक devm_request_resource(काष्ठा device *dev, काष्ठा resource *root,
			  काष्ठा resource *new)
अणु
	काष्ठा resource *conflict, **ptr;

	ptr = devres_alloc(devm_resource_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	*ptr = new;

	conflict = request_resource_conflict(root, new);
	अगर (conflict) अणु
		dev_err(dev, "resource collision: %pR conflicts with %s %pR\n",
			new, conflict->name, conflict);
		devres_मुक्त(ptr);
		वापस -EBUSY;
	पूर्ण

	devres_add(dev, ptr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(devm_request_resource);

अटल पूर्णांक devm_resource_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा resource **ptr = res;

	वापस *ptr == data;
पूर्ण

/**
 * devm_release_resource() - release a previously requested resource
 * @dev: device क्रम which to release the resource
 * @new: descriptor of the resource to release
 *
 * Releases a resource previously requested using devm_request_resource().
 */
व्योम devm_release_resource(काष्ठा device *dev, काष्ठा resource *new)
अणु
	WARN_ON(devres_release(dev, devm_resource_release, devm_resource_match,
			       new));
पूर्ण
EXPORT_SYMBOL(devm_release_resource);

काष्ठा region_devres अणु
	काष्ठा resource *parent;
	resource_माप_प्रकार start;
	resource_माप_प्रकार n;
पूर्ण;

अटल व्योम devm_region_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा region_devres *this = res;

	__release_region(this->parent, this->start, this->n);
पूर्ण

अटल पूर्णांक devm_region_match(काष्ठा device *dev, व्योम *res, व्योम *match_data)
अणु
	काष्ठा region_devres *this = res, *match = match_data;

	वापस this->parent == match->parent &&
		this->start == match->start && this->n == match->n;
पूर्ण

काष्ठा resource *
__devm_request_region(काष्ठा device *dev, काष्ठा resource *parent,
		      resource_माप_प्रकार start, resource_माप_प्रकार n, स्थिर अक्षर *name)
अणु
	काष्ठा region_devres *dr = शून्य;
	काष्ठा resource *res;

	dr = devres_alloc(devm_region_release, माप(काष्ठा region_devres),
			  GFP_KERNEL);
	अगर (!dr)
		वापस शून्य;

	dr->parent = parent;
	dr->start = start;
	dr->n = n;

	res = __request_region(parent, start, n, name, 0);
	अगर (res)
		devres_add(dev, dr);
	अन्यथा
		devres_मुक्त(dr);

	वापस res;
पूर्ण
EXPORT_SYMBOL(__devm_request_region);

व्योम __devm_release_region(काष्ठा device *dev, काष्ठा resource *parent,
			   resource_माप_प्रकार start, resource_माप_प्रकार n)
अणु
	काष्ठा region_devres match_data = अणु parent, start, n पूर्ण;

	__release_region(parent, start, n);
	WARN_ON(devres_destroy(dev, devm_region_release, devm_region_match,
			       &match_data));
पूर्ण
EXPORT_SYMBOL(__devm_release_region);

/*
 * Reserve I/O ports or memory based on "reserve=" kernel parameter.
 */
#घोषणा MAXRESERVE 4
अटल पूर्णांक __init reserve_setup(अक्षर *str)
अणु
	अटल पूर्णांक reserved;
	अटल काष्ठा resource reserve[MAXRESERVE];

	क्रम (;;) अणु
		अचिन्हित पूर्णांक io_start, io_num;
		पूर्णांक x = reserved;
		काष्ठा resource *parent;

		अगर (get_option(&str, &io_start) != 2)
			अवरोध;
		अगर (get_option(&str, &io_num) == 0)
			अवरोध;
		अगर (x < MAXRESERVE) अणु
			काष्ठा resource *res = reserve + x;

			/*
			 * If the region starts below 0x10000, we assume it's
			 * I/O port space; otherwise assume it's memory.
			 */
			अगर (io_start < 0x10000) अणु
				res->flags = IORESOURCE_IO;
				parent = &ioport_resource;
			पूर्ण अन्यथा अणु
				res->flags = IORESOURCE_MEM;
				parent = &iomem_resource;
			पूर्ण
			res->name = "reserved";
			res->start = io_start;
			res->end = io_start + io_num - 1;
			res->flags |= IORESOURCE_BUSY;
			res->desc = IORES_DESC_NONE;
			res->child = शून्य;
			अगर (request_resource(parent, res) == 0)
				reserved = x+1;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण
__setup("reserve=", reserve_setup);

/*
 * Check अगर the requested addr and size spans more than any slot in the
 * iomem resource tree.
 */
पूर्णांक iomem_map_sanity_check(resource_माप_प्रकार addr, अचिन्हित दीर्घ size)
अणु
	काष्ठा resource *p = &iomem_resource;
	पूर्णांक err = 0;
	loff_t l;

	पढ़ो_lock(&resource_lock);
	क्रम (p = p->child; p ; p = r_next(शून्य, p, &l)) अणु
		/*
		 * We can probably skip the resources without
		 * IORESOURCE_IO attribute?
		 */
		अगर (p->start >= addr + size)
			जारी;
		अगर (p->end < addr)
			जारी;
		अगर (PFN_DOWN(p->start) <= PFN_DOWN(addr) &&
		    PFN_DOWN(p->end) >= PFN_DOWN(addr + size - 1))
			जारी;
		/*
		 * अगर a resource is "BUSY", it's not a hardware resource
		 * but a driver mapping of such a resource; we करोn't want
		 * to warn क्रम those; some drivers legitimately map only
		 * partial hardware resources. (example: vesafb)
		 */
		अगर (p->flags & IORESOURCE_BUSY)
			जारी;

		prपूर्णांकk(KERN_WARNING "resource sanity check: requesting [mem %#010llx-%#010llx], which spans more than %s %pR\n",
		       (अचिन्हित दीर्घ दीर्घ)addr,
		       (अचिन्हित दीर्घ दीर्घ)(addr + size - 1),
		       p->name, p);
		err = -1;
		अवरोध;
	पूर्ण
	पढ़ो_unlock(&resource_lock);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_STRICT_DEVMEM
अटल पूर्णांक strict_iomem_checks = 1;
#अन्यथा
अटल पूर्णांक strict_iomem_checks;
#पूर्ण_अगर

/*
 * check अगर an address is reserved in the iomem resource tree
 * वापसs true अगर reserved, false अगर not reserved.
 */
bool iomem_is_exclusive(u64 addr)
अणु
	काष्ठा resource *p = &iomem_resource;
	bool err = false;
	loff_t l;
	पूर्णांक size = PAGE_SIZE;

	अगर (!strict_iomem_checks)
		वापस false;

	addr = addr & PAGE_MASK;

	पढ़ो_lock(&resource_lock);
	क्रम (p = p->child; p ; p = r_next(शून्य, p, &l)) अणु
		/*
		 * We can probably skip the resources without
		 * IORESOURCE_IO attribute?
		 */
		अगर (p->start >= addr + size)
			अवरोध;
		अगर (p->end < addr)
			जारी;
		/*
		 * A resource is exclusive अगर IORESOURCE_EXCLUSIVE is set
		 * or CONFIG_IO_STRICT_DEVMEM is enabled and the
		 * resource is busy.
		 */
		अगर ((p->flags & IORESOURCE_BUSY) == 0)
			जारी;
		अगर (IS_ENABLED(CONFIG_IO_STRICT_DEVMEM)
				|| p->flags & IORESOURCE_EXCLUSIVE) अणु
			err = true;
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&resource_lock);

	वापस err;
पूर्ण

काष्ठा resource_entry *resource_list_create_entry(काष्ठा resource *res,
						  माप_प्रकार extra_size)
अणु
	काष्ठा resource_entry *entry;

	entry = kzalloc(माप(*entry) + extra_size, GFP_KERNEL);
	अगर (entry) अणु
		INIT_LIST_HEAD(&entry->node);
		entry->res = res ? res : &entry->__res;
	पूर्ण

	वापस entry;
पूर्ण
EXPORT_SYMBOL(resource_list_create_entry);

व्योम resource_list_मुक्त(काष्ठा list_head *head)
अणु
	काष्ठा resource_entry *entry, *पंचांगp;

	list_क्रम_each_entry_safe(entry, पंचांगp, head, node)
		resource_list_destroy_entry(entry);
पूर्ण
EXPORT_SYMBOL(resource_list_मुक्त);

#अगर_घोषित CONFIG_DEVICE_PRIVATE
अटल काष्ठा resource *__request_मुक्त_mem_region(काष्ठा device *dev,
		काष्ठा resource *base, अचिन्हित दीर्घ size, स्थिर अक्षर *name)
अणु
	resource_माप_प्रकार end, addr;
	काष्ठा resource *res;
	काष्ठा region_devres *dr = शून्य;

	size = ALIGN(size, 1UL << PA_SECTION_SHIFT);
	end = min_t(अचिन्हित दीर्घ, base->end, (1UL << MAX_PHYSMEM_BITS) - 1);
	addr = end - size + 1UL;

	res = alloc_resource(GFP_KERNEL);
	अगर (!res)
		वापस ERR_PTR(-ENOMEM);

	अगर (dev) अणु
		dr = devres_alloc(devm_region_release,
				माप(काष्ठा region_devres), GFP_KERNEL);
		अगर (!dr) अणु
			मुक्त_resource(res);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण

	ग_लिखो_lock(&resource_lock);
	क्रम (; addr > size && addr >= base->start; addr -= size) अणु
		अगर (__region_पूर्णांकersects(addr, size, 0, IORES_DESC_NONE) !=
				REGION_DISJOINT)
			जारी;

		अगर (__request_region_locked(res, &iomem_resource, addr, size,
						name, 0))
			अवरोध;

		अगर (dev) अणु
			dr->parent = &iomem_resource;
			dr->start = addr;
			dr->n = size;
			devres_add(dev, dr);
		पूर्ण

		res->desc = IORES_DESC_DEVICE_PRIVATE_MEMORY;
		ग_लिखो_unlock(&resource_lock);

		/*
		 * A driver is claiming this region so revoke any mappings.
		 */
		revoke_iomem(res);
		वापस res;
	पूर्ण
	ग_लिखो_unlock(&resource_lock);

	मुक्त_resource(res);
	अगर (dr)
		devres_मुक्त(dr);

	वापस ERR_PTR(-दुस्फल);
पूर्ण

/**
 * devm_request_मुक्त_mem_region - find मुक्त region क्रम device निजी memory
 *
 * @dev: device काष्ठा to bind the resource to
 * @size: size in bytes of the device memory to add
 * @base: resource tree to look in
 *
 * This function tries to find an empty range of physical address big enough to
 * contain the new resource, so that it can later be hotplugged as ZONE_DEVICE
 * memory, which in turn allocates काष्ठा pages.
 */
काष्ठा resource *devm_request_मुक्त_mem_region(काष्ठा device *dev,
		काष्ठा resource *base, अचिन्हित दीर्घ size)
अणु
	वापस __request_मुक्त_mem_region(dev, base, size, dev_name(dev));
पूर्ण
EXPORT_SYMBOL_GPL(devm_request_मुक्त_mem_region);

काष्ठा resource *request_मुक्त_mem_region(काष्ठा resource *base,
		अचिन्हित दीर्घ size, स्थिर अक्षर *name)
अणु
	वापस __request_मुक्त_mem_region(शून्य, base, size, name);
पूर्ण
EXPORT_SYMBOL_GPL(request_मुक्त_mem_region);

#पूर्ण_अगर /* CONFIG_DEVICE_PRIVATE */

अटल पूर्णांक __init strict_iomem(अक्षर *str)
अणु
	अगर (म_माला(str, "relaxed"))
		strict_iomem_checks = 0;
	अगर (म_माला(str, "strict"))
		strict_iomem_checks = 1;
	वापस 1;
पूर्ण

अटल पूर्णांक iomem_fs_init_fs_context(काष्ठा fs_context *fc)
अणु
	वापस init_pseuकरो(fc, DEVMEM_MAGIC) ? 0 : -ENOMEM;
पूर्ण

अटल काष्ठा file_प्रणाली_type iomem_fs_type = अणु
	.name		= "iomem",
	.owner		= THIS_MODULE,
	.init_fs_context = iomem_fs_init_fs_context,
	.समाप्त_sb	= समाप्त_anon_super,
पूर्ण;

अटल पूर्णांक __init iomem_init_inode(व्योम)
अणु
	अटल काष्ठा vfsmount *iomem_vfs_mount;
	अटल पूर्णांक iomem_fs_cnt;
	काष्ठा inode *inode;
	पूर्णांक rc;

	rc = simple_pin_fs(&iomem_fs_type, &iomem_vfs_mount, &iomem_fs_cnt);
	अगर (rc < 0) अणु
		pr_err("Cannot mount iomem pseudo filesystem: %d\n", rc);
		वापस rc;
	पूर्ण

	inode = alloc_anon_inode(iomem_vfs_mount->mnt_sb);
	अगर (IS_ERR(inode)) अणु
		rc = PTR_ERR(inode);
		pr_err("Cannot allocate inode for iomem: %d\n", rc);
		simple_release_fs(&iomem_vfs_mount, &iomem_fs_cnt);
		वापस rc;
	पूर्ण

	/*
	 * Publish iomem revocation inode initialized.
	 * Pairs with smp_load_acquire() in revoke_iomem().
	 */
	smp_store_release(&iomem_inode, inode);

	वापस 0;
पूर्ण

fs_initcall(iomem_init_inode);

__setup("iomem=", strict_iomem);
