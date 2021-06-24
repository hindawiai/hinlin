<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ioport.c:  Simple io mapping allocator.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 1995 Miguel de Icaza (miguel@nuclecu.unam.mx)
 *
 * 1996: sparc_मुक्त_io, 1999: ioremap()/iounmap() by Pete Zaitcev.
 *
 * 2000/01/29
 * <rth> zait: as दीर्घ as pci_alloc_consistent produces something addressable, 
 *	things are ok.
 * <zaitcev> rth: no, it is relevant, because get_मुक्त_pages वापसs you a
 *	poपूर्णांकer पूर्णांकo the big page mapping
 * <rth> zait: so what?
 * <rth> zait: remap_it_my_way(virt_to_phys(get_मुक्त_page()))
 * <zaitcev> Hmm
 * <zaitcev> Suppose I did this remap_it_my_way(virt_to_phys(get_मुक्त_page())).
 *	So far so good.
 * <zaitcev> Now, driver calls pci_मुक्त_consistent(with result of
 *	remap_it_my_way()).
 * <zaitcev> How करो you find the address to pass to मुक्त_pages()?
 * <rth> zait: walk the page tables?  It's only two or three level after all.
 * <rth> zait: you have to walk them anyway to हटाओ the mapping.
 * <zaitcev> Hmm
 * <zaitcev> Sounds reasonable
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>		/* काष्ठा pci_dev */
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/vaddrs.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/io-unit.h>
#समावेश <यंत्र/leon.h>

/* This function must make sure that caches and memory are coherent after DMA
 * On LEON प्रणालीs without cache snooping it flushes the entire D-CACHE.
 */
अटल अंतरभूत व्योम dma_make_coherent(अचिन्हित दीर्घ pa, अचिन्हित दीर्घ len)
अणु
	अगर (sparc_cpu_model == sparc_leon) अणु
		अगर (!sparc_leon3_snooping_enabled())
			leon_flush_dcache_all();
	पूर्ण
पूर्ण

अटल व्योम __iomem *_sparc_ioremap(काष्ठा resource *res, u32 bus, u32 pa, पूर्णांक sz);
अटल व्योम __iomem *_sparc_alloc_io(अचिन्हित पूर्णांक busno, अचिन्हित दीर्घ phys,
    अचिन्हित दीर्घ size, अक्षर *name);
अटल व्योम _sparc_मुक्त_io(काष्ठा resource *res);

अटल व्योम रेजिस्टर_proc_sparc_ioport(व्योम);

/* This poपूर्णांकs to the next to use भव memory क्रम DVMA mappings */
अटल काष्ठा resource _sparc_dvma = अणु
	.name = "sparc_dvma", .start = DVMA_VADDR, .end = DVMA_END - 1
पूर्ण;
/* This poपूर्णांकs to the start of I/O mappings, cluable from outside. */
/*ext*/ काष्ठा resource sparc_iomap = अणु
	.name = "sparc_iomap", .start = IOBASE_VADDR, .end = IOBASE_END - 1
पूर्ण;

/*
 * Our mini-allocator...
 * Boy this is gross! We need it because we must map I/O क्रम
 * समयrs and पूर्णांकerrupt controller beक्रमe the kदो_स्मृति is available.
 */

#घोषणा XNMLN  15
#घोषणा XNRES  10	/* SS-10 uses 8 */

काष्ठा xresource अणु
	काष्ठा resource xres;	/* Must be first */
	पूर्णांक xflag;		/* 1 == used */
	अक्षर xname[XNMLN+1];
पूर्ण;

अटल काष्ठा xresource xresv[XNRES];

अटल काष्ठा xresource *xres_alloc(व्योम) अणु
	काष्ठा xresource *xrp;
	पूर्णांक n;

	xrp = xresv;
	क्रम (n = 0; n < XNRES; n++) अणु
		अगर (xrp->xflag == 0) अणु
			xrp->xflag = 1;
			वापस xrp;
		पूर्ण
		xrp++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम xres_मुक्त(काष्ठा xresource *xrp) अणु
	xrp->xflag = 0;
पूर्ण

/*
 * These are typically used in PCI drivers
 * which are trying to be cross-platक्रमm.
 *
 * Bus type is always zero on IIep.
 */
व्योम __iomem *ioremap(phys_addr_t offset, माप_प्रकार size)
अणु
	अक्षर name[14];

	प्र_लिखो(name, "phys_%08x", (u32)offset);
	वापस _sparc_alloc_io(0, (अचिन्हित दीर्घ)offset, size, name);
पूर्ण
EXPORT_SYMBOL(ioremap);

/*
 * Complementary to ioremap().
 */
व्योम iounmap(अस्थिर व्योम __iomem *भव)
अणु
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ) भव & PAGE_MASK;
	काष्ठा resource *res;

	/*
	 * XXX Too slow. Can have 8192 DVMA pages on sun4m in the worst हाल.
	 * This probably warrants some sort of hashing.
	*/
	अगर ((res = lookup_resource(&sparc_iomap, vaddr)) == शून्य) अणु
		prपूर्णांकk("free_io/iounmap: cannot free %lx\n", vaddr);
		वापस;
	पूर्ण
	_sparc_मुक्त_io(res);

	अगर ((अक्षर *)res >= (अक्षर*)xresv && (अक्षर *)res < (अक्षर *)&xresv[XNRES]) अणु
		xres_मुक्त((काष्ठा xresource *)res);
	पूर्ण अन्यथा अणु
		kमुक्त(res);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(iounmap);

व्योम __iomem *of_ioremap(काष्ठा resource *res, अचिन्हित दीर्घ offset,
			 अचिन्हित दीर्घ size, अक्षर *name)
अणु
	वापस _sparc_alloc_io(res->flags & 0xF,
			       res->start + offset,
			       size, name);
पूर्ण
EXPORT_SYMBOL(of_ioremap);

व्योम of_iounmap(काष्ठा resource *res, व्योम __iomem *base, अचिन्हित दीर्घ size)
अणु
	iounmap(base);
पूर्ण
EXPORT_SYMBOL(of_iounmap);

/*
 * Meat of mapping
 */
अटल व्योम __iomem *_sparc_alloc_io(अचिन्हित पूर्णांक busno, अचिन्हित दीर्घ phys,
    अचिन्हित दीर्घ size, अक्षर *name)
अणु
	अटल पूर्णांक prपूर्णांकed_full;
	काष्ठा xresource *xres;
	काष्ठा resource *res;
	अक्षर *tack;
	पूर्णांक tlen;
	व्योम __iomem *va;	/* P3 diag */

	अगर (name == शून्य) name = "???";

	अगर ((xres = xres_alloc()) != शून्य) अणु
		tack = xres->xname;
		res = &xres->xres;
	पूर्ण अन्यथा अणु
		अगर (!prपूर्णांकed_full) अणु
			prपूर्णांकk("ioremap: done with statics, switching to malloc\n");
			prपूर्णांकed_full = 1;
		पूर्ण
		tlen = म_माप(name);
		tack = kदो_स्मृति(माप (काष्ठा resource) + tlen + 1, GFP_KERNEL);
		अगर (tack == शून्य) वापस शून्य;
		स_रखो(tack, 0, माप(काष्ठा resource));
		res = (काष्ठा resource *) tack;
		tack += माप (काष्ठा resource);
	पूर्ण

	strlcpy(tack, name, XNMLN+1);
	res->name = tack;

	va = _sparc_ioremap(res, busno, phys, size);
	/* prपूर्णांकk("ioremap(0x%x:%08lx[0x%lx])=%p\n", busno, phys, size, va); */ /* P3 diag */
	वापस va;
पूर्ण

/*
 */
अटल व्योम __iomem *
_sparc_ioremap(काष्ठा resource *res, u32 bus, u32 pa, पूर्णांक sz)
अणु
	अचिन्हित दीर्घ offset = ((अचिन्हित दीर्घ) pa) & (~PAGE_MASK);

	अगर (allocate_resource(&sparc_iomap, res,
	    (offset + sz + PAGE_SIZE-1) & PAGE_MASK,
	    sparc_iomap.start, sparc_iomap.end, PAGE_SIZE, शून्य, शून्य) != 0) अणु
		/* Usually we cannot see prपूर्णांकks in this हाल. */
		prom_म_लिखो("alloc_io_res(%s): cannot occupy\n",
		    (res->name != शून्य)? res->name: "???");
		prom_halt();
	पूर्ण

	pa &= PAGE_MASK;
	srmmu_mapiorange(bus, pa, res->start, resource_size(res));

	वापस (व्योम __iomem *)(अचिन्हित दीर्घ)(res->start + offset);
पूर्ण

/*
 * Complementary to _sparc_ioremap().
 */
अटल व्योम _sparc_मुक्त_io(काष्ठा resource *res)
अणु
	अचिन्हित दीर्घ plen;

	plen = resource_size(res);
	BUG_ON((plen & (PAGE_SIZE-1)) != 0);
	srmmu_unmapiorange(res->start, plen);
	release_resource(res);
पूर्ण

अचिन्हित दीर्घ sparc_dma_alloc_resource(काष्ठा device *dev, माप_प्रकार len)
अणु
	काष्ठा resource *res;

	res = kzalloc(माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस 0;
	res->name = dev->of_node->full_name;

	अगर (allocate_resource(&_sparc_dvma, res, len, _sparc_dvma.start,
			      _sparc_dvma.end, PAGE_SIZE, शून्य, शून्य) != 0) अणु
		prपूर्णांकk("%s: cannot occupy 0x%zx", __func__, len);
		kमुक्त(res);
		वापस 0;
	पूर्ण

	वापस res->start;
पूर्ण

bool sparc_dma_मुक्त_resource(व्योम *cpu_addr, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)cpu_addr;
	काष्ठा resource *res;

	res = lookup_resource(&_sparc_dvma, addr);
	अगर (!res) अणु
		prपूर्णांकk("%s: cannot free %p\n", __func__, cpu_addr);
		वापस false;
	पूर्ण

	अगर ((addr & (PAGE_SIZE - 1)) != 0) अणु
		prपूर्णांकk("%s: unaligned va %p\n", __func__, cpu_addr);
		वापस false;
	पूर्ण

	size = PAGE_ALIGN(size);
	अगर (resource_size(res) != size) अणु
		prपूर्णांकk("%s: region 0x%lx asked 0x%zx\n",
			__func__, (दीर्घ)resource_size(res), size);
		वापस false;
	पूर्ण

	release_resource(res);
	kमुक्त(res);
	वापस true;
पूर्ण

#अगर_घोषित CONFIG_SBUS

व्योम sbus_set_sbus64(काष्ठा device *dev, पूर्णांक x)
अणु
	prपूर्णांकk("sbus_set_sbus64: unsupported\n");
पूर्ण
EXPORT_SYMBOL(sbus_set_sbus64);

अटल पूर्णांक __init sparc_रेजिस्टर_ioport(व्योम)
अणु
	रेजिस्टर_proc_sparc_ioport();

	वापस 0;
पूर्ण

arch_initcall(sparc_रेजिस्टर_ioport);

#पूर्ण_अगर /* CONFIG_SBUS */


/* Allocate and map kernel buffer using consistent mode DMA क्रम a device.
 * hwdev should be valid काष्ठा pci_dev poपूर्णांकer क्रम PCI devices.
 */
व्योम *arch_dma_alloc(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *dma_handle,
		gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित दीर्घ addr;
	व्योम *va;

	अगर (!size || size > 256 * 1024)	/* __get_मुक्त_pages() limit */
		वापस शून्य;

	size = PAGE_ALIGN(size);
	va = (व्योम *) __get_मुक्त_pages(gfp | __GFP_ZERO, get_order(size));
	अगर (!va) अणु
		prपूर्णांकk("%s: no %zd pages\n", __func__, size >> PAGE_SHIFT);
		वापस शून्य;
	पूर्ण

	addr = sparc_dma_alloc_resource(dev, size);
	अगर (!addr)
		जाओ err_nomem;

	srmmu_mapiorange(0, virt_to_phys(va), addr, size);

	*dma_handle = virt_to_phys(va);
	वापस (व्योम *)addr;

err_nomem:
	मुक्त_pages((अचिन्हित दीर्घ)va, get_order(size));
	वापस शून्य;
पूर्ण

/* Free and unmap a consistent DMA buffer.
 * cpu_addr is what was वापसed arch_dma_alloc, size must be the same as what
 * was passed पूर्णांकo arch_dma_alloc, and likewise dma_addr must be the same as
 * what *dma_ndler was set to.
 *
 * References to the memory and mappings associated with cpu_addr/dma_addr
 * past this call are illegal.
 */
व्योम arch_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
		dma_addr_t dma_addr, अचिन्हित दीर्घ attrs)
अणु
	अगर (!sparc_dma_मुक्त_resource(cpu_addr, PAGE_ALIGN(size)))
		वापस;

	dma_make_coherent(dma_addr, size);
	srmmu_unmapiorange((अचिन्हित दीर्घ)cpu_addr, size);
	मुक्त_pages((अचिन्हित दीर्घ)phys_to_virt(dma_addr), get_order(size));
पूर्ण

/* IIep is ग_लिखो-through, not flushing on cpu to device transfer. */

व्योम arch_sync_dma_क्रम_cpu(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	अगर (dir != PCI_DMA_TODEVICE)
		dma_make_coherent(paddr, PAGE_ALIGN(size));
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

अटल पूर्णांक sparc_io_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा resource *root = m->निजी, *r;
	स्थिर अक्षर *nm;

	क्रम (r = root->child; r != शून्य; r = r->sibling) अणु
		अगर ((nm = r->name) == शून्य) nm = "???";
		seq_म_लिखो(m, "%016llx-%016llx: %s\n",
				(अचिन्हित दीर्घ दीर्घ)r->start,
				(अचिन्हित दीर्घ दीर्घ)r->end, nm);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल व्योम रेजिस्टर_proc_sparc_ioport(व्योम)
अणु
#अगर_घोषित CONFIG_PROC_FS
	proc_create_single_data("io_map", 0, शून्य, sparc_io_proc_show,
			&sparc_iomap);
	proc_create_single_data("dvma_map", 0, शून्य, sparc_io_proc_show,
			&_sparc_dvma);
#पूर्ण_अगर
पूर्ण
