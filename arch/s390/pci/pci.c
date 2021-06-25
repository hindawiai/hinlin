<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2012
 *
 * Author(s):
 *   Jan Glauber <jang@linux.vnet.ibm.com>
 *
 * The System z PCI code is a reग_लिखो from a prototype by
 * the following people (Kuकरोz!):
 *   Alexander Schmidt
 *   Christoph Raisch
 *   Hannes Hering
 *   Hoang-Nam Nguyen
 *   Jan-Bernd Themann
 *   Stefan Roscher
 *   Thomas Klein
 */

#घोषणा KMSG_COMPONENT "zpci"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/pci.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश <यंत्र/isc.h>
#समावेश <यंत्र/airq.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/pci_insn.h>
#समावेश <यंत्र/pci_clp.h>
#समावेश <यंत्र/pci_dma.h>

#समावेश "pci_bus.h"
#समावेश "pci_iov.h"

/* list of all detected zpci devices */
अटल LIST_HEAD(zpci_list);
अटल DEFINE_SPINLOCK(zpci_list_lock);

अटल DECLARE_BITMAP(zpci_करोमुख्य, ZPCI_DOMAIN_BITMAP_SIZE);
अटल DEFINE_SPINLOCK(zpci_करोमुख्य_lock);

#घोषणा ZPCI_IOMAP_ENTRIES						\
	min(((अचिन्हित दीर्घ) ZPCI_NR_DEVICES * PCI_STD_NUM_BARS / 2),	\
	    ZPCI_IOMAP_MAX_ENTRIES)

अचिन्हित पूर्णांक s390_pci_no_rid;

अटल DEFINE_SPINLOCK(zpci_iomap_lock);
अटल अचिन्हित दीर्घ *zpci_iomap_biपंचांगap;
काष्ठा zpci_iomap_entry *zpci_iomap_start;
EXPORT_SYMBOL_GPL(zpci_iomap_start);

DEFINE_STATIC_KEY_FALSE(have_mio);

अटल काष्ठा kmem_cache *zdev_fmb_cache;

काष्ठा zpci_dev *get_zdev_by_fid(u32 fid)
अणु
	काष्ठा zpci_dev *पंचांगp, *zdev = शून्य;

	spin_lock(&zpci_list_lock);
	list_क्रम_each_entry(पंचांगp, &zpci_list, entry) अणु
		अगर (पंचांगp->fid == fid) अणु
			zdev = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&zpci_list_lock);
	वापस zdev;
पूर्ण

व्योम zpci_हटाओ_reserved_devices(व्योम)
अणु
	काष्ठा zpci_dev *पंचांगp, *zdev;
	क्रमागत zpci_state state;
	LIST_HEAD(हटाओ);

	spin_lock(&zpci_list_lock);
	list_क्रम_each_entry_safe(zdev, पंचांगp, &zpci_list, entry) अणु
		अगर (zdev->state == ZPCI_FN_STATE_STANDBY &&
		    !clp_get_state(zdev->fid, &state) &&
		    state == ZPCI_FN_STATE_RESERVED)
			list_move_tail(&zdev->entry, &हटाओ);
	पूर्ण
	spin_unlock(&zpci_list_lock);

	list_क्रम_each_entry_safe(zdev, पंचांगp, &हटाओ, entry)
		zpci_zdev_put(zdev);
पूर्ण

पूर्णांक pci_करोमुख्य_nr(काष्ठा pci_bus *bus)
अणु
	वापस ((काष्ठा zpci_bus *) bus->sysdata)->करोमुख्य_nr;
पूर्ण
EXPORT_SYMBOL_GPL(pci_करोमुख्य_nr);

पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	वापस pci_करोमुख्य_nr(bus);
पूर्ण
EXPORT_SYMBOL_GPL(pci_proc_करोमुख्य);

/* Modअगरy PCI: Register I/O address translation parameters */
पूर्णांक zpci_रेजिस्टर_ioat(काष्ठा zpci_dev *zdev, u8 dmaas,
		       u64 base, u64 limit, u64 iota)
अणु
	u64 req = ZPCI_CREATE_REQ(zdev->fh, dmaas, ZPCI_MOD_FC_REG_IOAT);
	काष्ठा zpci_fib fib = अणु0पूर्ण;
	u8 status;

	WARN_ON_ONCE(iota & 0x3fff);
	fib.pba = base;
	fib.pal = limit;
	fib.iota = iota | ZPCI_IOTA_RTTO_FLAG;
	वापस zpci_mod_fc(req, &fib, &status) ? -EIO : 0;
पूर्ण

/* Modअगरy PCI: Unरेजिस्टर I/O address translation parameters */
पूर्णांक zpci_unरेजिस्टर_ioat(काष्ठा zpci_dev *zdev, u8 dmaas)
अणु
	u64 req = ZPCI_CREATE_REQ(zdev->fh, dmaas, ZPCI_MOD_FC_DEREG_IOAT);
	काष्ठा zpci_fib fib = अणु0पूर्ण;
	u8 cc, status;

	cc = zpci_mod_fc(req, &fib, &status);
	अगर (cc == 3) /* Function alपढ़ोy gone. */
		cc = 0;
	वापस cc ? -EIO : 0;
पूर्ण

/* Modअगरy PCI: Set PCI function measurement parameters */
पूर्णांक zpci_fmb_enable_device(काष्ठा zpci_dev *zdev)
अणु
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 0, ZPCI_MOD_FC_SET_MEASURE);
	काष्ठा zpci_fib fib = अणु0पूर्ण;
	u8 cc, status;

	अगर (zdev->fmb || माप(*zdev->fmb) < zdev->fmb_length)
		वापस -EINVAL;

	zdev->fmb = kmem_cache_zalloc(zdev_fmb_cache, GFP_KERNEL);
	अगर (!zdev->fmb)
		वापस -ENOMEM;
	WARN_ON((u64) zdev->fmb & 0xf);

	/* reset software counters */
	atomic64_set(&zdev->allocated_pages, 0);
	atomic64_set(&zdev->mapped_pages, 0);
	atomic64_set(&zdev->unmapped_pages, 0);

	fib.fmb_addr = virt_to_phys(zdev->fmb);
	cc = zpci_mod_fc(req, &fib, &status);
	अगर (cc) अणु
		kmem_cache_मुक्त(zdev_fmb_cache, zdev->fmb);
		zdev->fmb = शून्य;
	पूर्ण
	वापस cc ? -EIO : 0;
पूर्ण

/* Modअगरy PCI: Disable PCI function measurement */
पूर्णांक zpci_fmb_disable_device(काष्ठा zpci_dev *zdev)
अणु
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 0, ZPCI_MOD_FC_SET_MEASURE);
	काष्ठा zpci_fib fib = अणु0पूर्ण;
	u8 cc, status;

	अगर (!zdev->fmb)
		वापस -EINVAL;

	/* Function measurement is disabled अगर fmb address is zero */
	cc = zpci_mod_fc(req, &fib, &status);
	अगर (cc == 3) /* Function alपढ़ोy gone. */
		cc = 0;

	अगर (!cc) अणु
		kmem_cache_मुक्त(zdev_fmb_cache, zdev->fmb);
		zdev->fmb = शून्य;
	पूर्ण
	वापस cc ? -EIO : 0;
पूर्ण

अटल पूर्णांक zpci_cfg_load(काष्ठा zpci_dev *zdev, पूर्णांक offset, u32 *val, u8 len)
अणु
	u64 req = ZPCI_CREATE_REQ(zdev->fh, ZPCI_PCIAS_CFGSPC, len);
	u64 data;
	पूर्णांक rc;

	rc = __zpci_load(&data, req, offset);
	अगर (!rc) अणु
		data = le64_to_cpu((__क्रमce __le64) data);
		data >>= (8 - len) * 8;
		*val = (u32) data;
	पूर्ण अन्यथा
		*val = 0xffffffff;
	वापस rc;
पूर्ण

अटल पूर्णांक zpci_cfg_store(काष्ठा zpci_dev *zdev, पूर्णांक offset, u32 val, u8 len)
अणु
	u64 req = ZPCI_CREATE_REQ(zdev->fh, ZPCI_PCIAS_CFGSPC, len);
	u64 data = val;
	पूर्णांक rc;

	data <<= (8 - len) * 8;
	data = (__क्रमce u64) cpu_to_le64(data);
	rc = __zpci_store(data, req, offset);
	वापस rc;
पूर्ण

resource_माप_प्रकार pcibios_align_resource(व्योम *data, स्थिर काष्ठा resource *res,
				       resource_माप_प्रकार size,
				       resource_माप_प्रकार align)
अणु
	वापस 0;
पूर्ण

/* combine single ग_लिखोs by using store-block insn */
व्योम __ioग_लिखो64_copy(व्योम __iomem *to, स्थिर व्योम *from, माप_प्रकार count)
अणु
       zpci_स_नकल_toio(to, from, count);
पूर्ण

अटल व्योम __iomem *__ioremap(phys_addr_t addr, माप_प्रकार size, pgprot_t prot)
अणु
	अचिन्हित दीर्घ offset, vaddr;
	काष्ठा vm_काष्ठा *area;
	phys_addr_t last_addr;

	last_addr = addr + size - 1;
	अगर (!size || last_addr < addr)
		वापस शून्य;

	अगर (!अटल_branch_unlikely(&have_mio))
		वापस (व्योम __iomem *) addr;

	offset = addr & ~PAGE_MASK;
	addr &= PAGE_MASK;
	size = PAGE_ALIGN(size + offset);
	area = get_vm_area(size, VM_IOREMAP);
	अगर (!area)
		वापस शून्य;

	vaddr = (अचिन्हित दीर्घ) area->addr;
	अगर (ioremap_page_range(vaddr, vaddr + size, addr, prot)) अणु
		मुक्त_vm_area(area);
		वापस शून्य;
	पूर्ण
	वापस (व्योम __iomem *) ((अचिन्हित दीर्घ) area->addr + offset);
पूर्ण

व्योम __iomem *ioremap_prot(phys_addr_t addr, माप_प्रकार size, अचिन्हित दीर्घ prot)
अणु
	वापस __ioremap(addr, size, __pgprot(prot));
पूर्ण
EXPORT_SYMBOL(ioremap_prot);

व्योम __iomem *ioremap(phys_addr_t addr, माप_प्रकार size)
अणु
	वापस __ioremap(addr, size, PAGE_KERNEL);
पूर्ण
EXPORT_SYMBOL(ioremap);

व्योम __iomem *ioremap_wc(phys_addr_t addr, माप_प्रकार size)
अणु
	वापस __ioremap(addr, size, pgprot_ग_लिखोcombine(PAGE_KERNEL));
पूर्ण
EXPORT_SYMBOL(ioremap_wc);

व्योम __iomem *ioremap_wt(phys_addr_t addr, माप_प्रकार size)
अणु
	वापस __ioremap(addr, size, pgprot_ग_लिखोthrough(PAGE_KERNEL));
पूर्ण
EXPORT_SYMBOL(ioremap_wt);

व्योम iounmap(अस्थिर व्योम __iomem *addr)
अणु
	अगर (अटल_branch_likely(&have_mio))
		vunmap((__क्रमce व्योम *) ((अचिन्हित दीर्घ) addr & PAGE_MASK));
पूर्ण
EXPORT_SYMBOL(iounmap);

/* Create a भव mapping cookie क्रम a PCI BAR */
अटल व्योम __iomem *pci_iomap_range_fh(काष्ठा pci_dev *pdev, पूर्णांक bar,
					अचिन्हित दीर्घ offset, अचिन्हित दीर्घ max)
अणु
	काष्ठा zpci_dev *zdev =	to_zpci(pdev);
	पूर्णांक idx;

	idx = zdev->bars[bar].map_idx;
	spin_lock(&zpci_iomap_lock);
	/* Detect overrun */
	WARN_ON(!++zpci_iomap_start[idx].count);
	zpci_iomap_start[idx].fh = zdev->fh;
	zpci_iomap_start[idx].bar = bar;
	spin_unlock(&zpci_iomap_lock);

	वापस (व्योम __iomem *) ZPCI_ADDR(idx) + offset;
पूर्ण

अटल व्योम __iomem *pci_iomap_range_mio(काष्ठा pci_dev *pdev, पूर्णांक bar,
					 अचिन्हित दीर्घ offset,
					 अचिन्हित दीर्घ max)
अणु
	अचिन्हित दीर्घ barsize = pci_resource_len(pdev, bar);
	काष्ठा zpci_dev *zdev = to_zpci(pdev);
	व्योम __iomem *iova;

	iova = ioremap((अचिन्हित दीर्घ) zdev->bars[bar].mio_wt, barsize);
	वापस iova ? iova + offset : iova;
पूर्ण

व्योम __iomem *pci_iomap_range(काष्ठा pci_dev *pdev, पूर्णांक bar,
			      अचिन्हित दीर्घ offset, अचिन्हित दीर्घ max)
अणु
	अगर (bar >= PCI_STD_NUM_BARS || !pci_resource_len(pdev, bar))
		वापस शून्य;

	अगर (अटल_branch_likely(&have_mio))
		वापस pci_iomap_range_mio(pdev, bar, offset, max);
	अन्यथा
		वापस pci_iomap_range_fh(pdev, bar, offset, max);
पूर्ण
EXPORT_SYMBOL(pci_iomap_range);

व्योम __iomem *pci_iomap(काष्ठा pci_dev *dev, पूर्णांक bar, अचिन्हित दीर्घ maxlen)
अणु
	वापस pci_iomap_range(dev, bar, 0, maxlen);
पूर्ण
EXPORT_SYMBOL(pci_iomap);

अटल व्योम __iomem *pci_iomap_wc_range_mio(काष्ठा pci_dev *pdev, पूर्णांक bar,
					    अचिन्हित दीर्घ offset, अचिन्हित दीर्घ max)
अणु
	अचिन्हित दीर्घ barsize = pci_resource_len(pdev, bar);
	काष्ठा zpci_dev *zdev = to_zpci(pdev);
	व्योम __iomem *iova;

	iova = ioremap((अचिन्हित दीर्घ) zdev->bars[bar].mio_wb, barsize);
	वापस iova ? iova + offset : iova;
पूर्ण

व्योम __iomem *pci_iomap_wc_range(काष्ठा pci_dev *pdev, पूर्णांक bar,
				 अचिन्हित दीर्घ offset, अचिन्हित दीर्घ max)
अणु
	अगर (bar >= PCI_STD_NUM_BARS || !pci_resource_len(pdev, bar))
		वापस शून्य;

	अगर (अटल_branch_likely(&have_mio))
		वापस pci_iomap_wc_range_mio(pdev, bar, offset, max);
	अन्यथा
		वापस pci_iomap_range_fh(pdev, bar, offset, max);
पूर्ण
EXPORT_SYMBOL(pci_iomap_wc_range);

व्योम __iomem *pci_iomap_wc(काष्ठा pci_dev *dev, पूर्णांक bar, अचिन्हित दीर्घ maxlen)
अणु
	वापस pci_iomap_wc_range(dev, bar, 0, maxlen);
पूर्ण
EXPORT_SYMBOL(pci_iomap_wc);

अटल व्योम pci_iounmap_fh(काष्ठा pci_dev *pdev, व्योम __iomem *addr)
अणु
	अचिन्हित पूर्णांक idx = ZPCI_IDX(addr);

	spin_lock(&zpci_iomap_lock);
	/* Detect underrun */
	WARN_ON(!zpci_iomap_start[idx].count);
	अगर (!--zpci_iomap_start[idx].count) अणु
		zpci_iomap_start[idx].fh = 0;
		zpci_iomap_start[idx].bar = 0;
	पूर्ण
	spin_unlock(&zpci_iomap_lock);
पूर्ण

अटल व्योम pci_iounmap_mio(काष्ठा pci_dev *pdev, व्योम __iomem *addr)
अणु
	iounmap(addr);
पूर्ण

व्योम pci_iounmap(काष्ठा pci_dev *pdev, व्योम __iomem *addr)
अणु
	अगर (अटल_branch_likely(&have_mio))
		pci_iounmap_mio(pdev, addr);
	अन्यथा
		pci_iounmap_fh(pdev, addr);
पूर्ण
EXPORT_SYMBOL(pci_iounmap);

अटल पूर्णांक pci_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		    पूर्णांक size, u32 *val)
अणु
	काष्ठा zpci_dev *zdev = get_zdev_by_bus(bus, devfn);

	वापस (zdev) ? zpci_cfg_load(zdev, where, val, size) : -ENODEV;
पूर्ण

अटल पूर्णांक pci_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		     पूर्णांक size, u32 val)
अणु
	काष्ठा zpci_dev *zdev = get_zdev_by_bus(bus, devfn);

	वापस (zdev) ? zpci_cfg_store(zdev, where, val, size) : -ENODEV;
पूर्ण

अटल काष्ठा pci_ops pci_root_ops = अणु
	.पढ़ो = pci_पढ़ो,
	.ग_लिखो = pci_ग_लिखो,
पूर्ण;

अटल व्योम zpci_map_resources(काष्ठा pci_dev *pdev)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(pdev);
	resource_माप_प्रकार len;
	पूर्णांक i;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		len = pci_resource_len(pdev, i);
		अगर (!len)
			जारी;

		अगर (zpci_use_mio(zdev))
			pdev->resource[i].start =
				(resource_माप_प्रकार __क्रमce) zdev->bars[i].mio_wt;
		अन्यथा
			pdev->resource[i].start = (resource_माप_प्रकार __क्रमce)
				pci_iomap_range_fh(pdev, i, 0, 0);
		pdev->resource[i].end = pdev->resource[i].start + len - 1;
	पूर्ण

	zpci_iov_map_resources(pdev);
पूर्ण

अटल व्योम zpci_unmap_resources(काष्ठा pci_dev *pdev)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(pdev);
	resource_माप_प्रकार len;
	पूर्णांक i;

	अगर (zpci_use_mio(zdev))
		वापस;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		len = pci_resource_len(pdev, i);
		अगर (!len)
			जारी;
		pci_iounmap_fh(pdev, (व्योम __iomem __क्रमce *)
			       pdev->resource[i].start);
	पूर्ण
पूर्ण

अटल पूर्णांक zpci_alloc_iomap(काष्ठा zpci_dev *zdev)
अणु
	अचिन्हित दीर्घ entry;

	spin_lock(&zpci_iomap_lock);
	entry = find_first_zero_bit(zpci_iomap_biपंचांगap, ZPCI_IOMAP_ENTRIES);
	अगर (entry == ZPCI_IOMAP_ENTRIES) अणु
		spin_unlock(&zpci_iomap_lock);
		वापस -ENOSPC;
	पूर्ण
	set_bit(entry, zpci_iomap_biपंचांगap);
	spin_unlock(&zpci_iomap_lock);
	वापस entry;
पूर्ण

अटल व्योम zpci_मुक्त_iomap(काष्ठा zpci_dev *zdev, पूर्णांक entry)
अणु
	spin_lock(&zpci_iomap_lock);
	स_रखो(&zpci_iomap_start[entry], 0, माप(काष्ठा zpci_iomap_entry));
	clear_bit(entry, zpci_iomap_biपंचांगap);
	spin_unlock(&zpci_iomap_lock);
पूर्ण

अटल काष्ठा resource *__alloc_res(काष्ठा zpci_dev *zdev, अचिन्हित दीर्घ start,
				    अचिन्हित दीर्घ size, अचिन्हित दीर्घ flags)
अणु
	काष्ठा resource *r;

	r = kzalloc(माप(*r), GFP_KERNEL);
	अगर (!r)
		वापस शून्य;

	r->start = start;
	r->end = r->start + size - 1;
	r->flags = flags;
	r->name = zdev->res_name;

	अगर (request_resource(&iomem_resource, r)) अणु
		kमुक्त(r);
		वापस शून्य;
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक zpci_setup_bus_resources(काष्ठा zpci_dev *zdev,
			     काष्ठा list_head *resources)
अणु
	अचिन्हित दीर्घ addr, size, flags;
	काष्ठा resource *res;
	पूर्णांक i, entry;

	snम_लिखो(zdev->res_name, माप(zdev->res_name),
		 "PCI Bus %04x:%02x", zdev->uid, ZPCI_BUS_NR);

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		अगर (!zdev->bars[i].size)
			जारी;
		entry = zpci_alloc_iomap(zdev);
		अगर (entry < 0)
			वापस entry;
		zdev->bars[i].map_idx = entry;

		/* only MMIO is supported */
		flags = IORESOURCE_MEM;
		अगर (zdev->bars[i].val & 8)
			flags |= IORESOURCE_PREFETCH;
		अगर (zdev->bars[i].val & 4)
			flags |= IORESOURCE_MEM_64;

		अगर (zpci_use_mio(zdev))
			addr = (अचिन्हित दीर्घ) zdev->bars[i].mio_wt;
		अन्यथा
			addr = ZPCI_ADDR(entry);
		size = 1UL << zdev->bars[i].size;

		res = __alloc_res(zdev, addr, size, flags);
		अगर (!res) अणु
			zpci_मुक्त_iomap(zdev, entry);
			वापस -ENOMEM;
		पूर्ण
		zdev->bars[i].res = res;
		pci_add_resource(resources, res);
	पूर्ण
	zdev->has_resources = 1;

	वापस 0;
पूर्ण

अटल व्योम zpci_cleanup_bus_resources(काष्ठा zpci_dev *zdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		अगर (!zdev->bars[i].size || !zdev->bars[i].res)
			जारी;

		zpci_मुक्त_iomap(zdev, zdev->bars[i].map_idx);
		release_resource(zdev->bars[i].res);
		kमुक्त(zdev->bars[i].res);
	पूर्ण
	zdev->has_resources = 0;
पूर्ण

पूर्णांक pcibios_add_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा resource *res;
	पूर्णांक i;

	अगर (pdev->is_physfn)
		pdev->no_vf_scan = 1;

	pdev->dev.groups = zpci_attr_groups;
	pdev->dev.dma_ops = &s390_pci_dma_ops;
	zpci_map_resources(pdev);

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		res = &pdev->resource[i];
		अगर (res->parent || !res->flags)
			जारी;
		pci_claim_resource(pdev, i);
	पूर्ण

	वापस 0;
पूर्ण

व्योम pcibios_release_device(काष्ठा pci_dev *pdev)
अणु
	zpci_unmap_resources(pdev);
पूर्ण

पूर्णांक pcibios_enable_device(काष्ठा pci_dev *pdev, पूर्णांक mask)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(pdev);

	zpci_debug_init_device(zdev, dev_name(&pdev->dev));
	zpci_fmb_enable_device(zdev);

	वापस pci_enable_resources(pdev, mask);
पूर्ण

व्योम pcibios_disable_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(pdev);

	zpci_fmb_disable_device(zdev);
	zpci_debug_निकास_device(zdev);
पूर्ण

अटल पूर्णांक __zpci_रेजिस्टर_करोमुख्य(पूर्णांक करोमुख्य)
अणु
	spin_lock(&zpci_करोमुख्य_lock);
	अगर (test_bit(करोमुख्य, zpci_करोमुख्य)) अणु
		spin_unlock(&zpci_करोमुख्य_lock);
		pr_err("Domain %04x is already assigned\n", करोमुख्य);
		वापस -EEXIST;
	पूर्ण
	set_bit(करोमुख्य, zpci_करोमुख्य);
	spin_unlock(&zpci_करोमुख्य_lock);
	वापस करोमुख्य;
पूर्ण

अटल पूर्णांक __zpci_alloc_करोमुख्य(व्योम)
अणु
	पूर्णांक करोमुख्य;

	spin_lock(&zpci_करोमुख्य_lock);
	/*
	 * We can always स्वतः allocate करोमुख्यs below ZPCI_NR_DEVICES.
	 * There is either a मुक्त करोमुख्य or we have reached the maximum in
	 * which हाल we would have bailed earlier.
	 */
	करोमुख्य = find_first_zero_bit(zpci_करोमुख्य, ZPCI_NR_DEVICES);
	set_bit(करोमुख्य, zpci_करोमुख्य);
	spin_unlock(&zpci_करोमुख्य_lock);
	वापस करोमुख्य;
पूर्ण

पूर्णांक zpci_alloc_करोमुख्य(पूर्णांक करोमुख्य)
अणु
	अगर (zpci_unique_uid) अणु
		अगर (करोमुख्य)
			वापस __zpci_रेजिस्टर_करोमुख्य(करोमुख्य);
		pr_warn("UID checking was active but no UID is provided: switching to automatic domain allocation\n");
		update_uid_checking(false);
	पूर्ण
	वापस __zpci_alloc_करोमुख्य();
पूर्ण

व्योम zpci_मुक्त_करोमुख्य(पूर्णांक करोमुख्य)
अणु
	spin_lock(&zpci_करोमुख्य_lock);
	clear_bit(करोमुख्य, zpci_करोमुख्य);
	spin_unlock(&zpci_करोमुख्य_lock);
पूर्ण


पूर्णांक zpci_enable_device(काष्ठा zpci_dev *zdev)
अणु
	पूर्णांक rc;

	rc = clp_enable_fh(zdev, ZPCI_NR_DMA_SPACES);
	अगर (rc)
		जाओ out;

	rc = zpci_dma_init_device(zdev);
	अगर (rc)
		जाओ out_dma;

	वापस 0;

out_dma:
	clp_disable_fh(zdev);
out:
	वापस rc;
पूर्ण

पूर्णांक zpci_disable_device(काष्ठा zpci_dev *zdev)
अणु
	zpci_dma_निकास_device(zdev);
	/*
	 * The zPCI function may alपढ़ोy be disabled by the platक्रमm, this is
	 * detected in clp_disable_fh() which becomes a no-op.
	 */
	वापस clp_disable_fh(zdev);
पूर्ण

/**
 * zpci_create_device() - Create a new zpci_dev and add it to the zbus
 * @fid: Function ID of the device to be created
 * @fh: Current Function Handle of the device to be created
 * @state: Initial state after creation either Standby or Configured
 *
 * Creates a new zpci device and adds it to its, possibly newly created, zbus
 * as well as zpci_list.
 *
 * Returns: the zdev on success or an error poपूर्णांकer otherwise
 */
काष्ठा zpci_dev *zpci_create_device(u32 fid, u32 fh, क्रमागत zpci_state state)
अणु
	काष्ठा zpci_dev *zdev;
	पूर्णांक rc;

	zpci_dbg(3, "add fid:%x, fh:%x, c:%d\n", fid, fh, state);
	zdev = kzalloc(माप(*zdev), GFP_KERNEL);
	अगर (!zdev)
		वापस ERR_PTR(-ENOMEM);

	/* FID and Function Handle are the अटल/dynamic identअगरiers */
	zdev->fid = fid;
	zdev->fh = fh;

	/* Query function properties and update zdev */
	rc = clp_query_pci_fn(zdev);
	अगर (rc)
		जाओ error;
	zdev->state =  state;

	kref_init(&zdev->kref);
	mutex_init(&zdev->lock);

	rc = zpci_init_iommu(zdev);
	अगर (rc)
		जाओ error;

	rc = zpci_bus_device_रेजिस्टर(zdev, &pci_root_ops);
	अगर (rc)
		जाओ error_destroy_iommu;

	spin_lock(&zpci_list_lock);
	list_add_tail(&zdev->entry, &zpci_list);
	spin_unlock(&zpci_list_lock);

	वापस zdev;

error_destroy_iommu:
	zpci_destroy_iommu(zdev);
error:
	zpci_dbg(0, "add fid:%x, rc:%d\n", fid, rc);
	kमुक्त(zdev);
	वापस ERR_PTR(rc);
पूर्ण

/**
 * zpci_scan_configured_device() - Scan a freshly configured zpci_dev
 * @zdev: The zpci_dev to be configured
 * @fh: The general function handle supplied by the platक्रमm
 *
 * Given a device in the configuration state Configured, enables, scans and
 * adds it to the common code PCI subप्रणाली अगर possible. If the PCI device is
 * parked because we can not yet create a PCI bus because we have not seen
 * function 0, it is ignored but will be scanned once function 0 appears.
 * If any failure occurs, the zpci_dev is left disabled.
 *
 * Return: 0 on success, or an error code otherwise
 */
पूर्णांक zpci_scan_configured_device(काष्ठा zpci_dev *zdev, u32 fh)
अणु
	पूर्णांक rc;

	zdev->fh = fh;
	/* the PCI function will be scanned once function 0 appears */
	अगर (!zdev->zbus->bus)
		वापस 0;

	/* For function 0 on a multi-function bus scan whole bus as we might
	 * have to pick up existing functions रुकोing क्रम it to allow creating
	 * the PCI bus
	 */
	अगर (zdev->devfn == 0 && zdev->zbus->multअगरunction)
		rc = zpci_bus_scan_bus(zdev->zbus);
	अन्यथा
		rc = zpci_bus_scan_device(zdev);

	वापस rc;
पूर्ण

/**
 * zpci_deconfigure_device() - Deconfigure a zpci_dev
 * @zdev: The zpci_dev to configure
 *
 * Deconfigure a zPCI function that is currently configured and possibly known
 * to the common code PCI subप्रणाली.
 * If any failure occurs the device is left as is.
 *
 * Return: 0 on success, or an error code otherwise
 */
पूर्णांक zpci_deconfigure_device(काष्ठा zpci_dev *zdev)
अणु
	पूर्णांक rc;

	अगर (zdev->zbus->bus)
		zpci_bus_हटाओ_device(zdev, false);

	अगर (zdev_enabled(zdev)) अणु
		rc = zpci_disable_device(zdev);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = sclp_pci_deconfigure(zdev->fid);
	zpci_dbg(3, "deconf fid:%x, rc:%d\n", zdev->fid, rc);
	अगर (rc)
		वापस rc;
	zdev->state = ZPCI_FN_STATE_STANDBY;

	वापस 0;
पूर्ण

व्योम zpci_release_device(काष्ठा kref *kref)
अणु
	काष्ठा zpci_dev *zdev = container_of(kref, काष्ठा zpci_dev, kref);
	पूर्णांक ret;

	अगर (zdev->zbus->bus)
		zpci_bus_हटाओ_device(zdev, false);

	अगर (zdev_enabled(zdev))
		zpci_disable_device(zdev);

	चयन (zdev->state) अणु
	हाल ZPCI_FN_STATE_CONFIGURED:
		ret = sclp_pci_deconfigure(zdev->fid);
		zpci_dbg(3, "deconf fid:%x, rc:%d\n", zdev->fid, ret);
		fallthrough;
	हाल ZPCI_FN_STATE_STANDBY:
		अगर (zdev->has_hp_slot)
			zpci_निकास_slot(zdev);
		zpci_cleanup_bus_resources(zdev);
		zpci_bus_device_unरेजिस्टर(zdev);
		zpci_destroy_iommu(zdev);
		fallthrough;
	शेष:
		अवरोध;
	पूर्ण

	spin_lock(&zpci_list_lock);
	list_del(&zdev->entry);
	spin_unlock(&zpci_list_lock);
	zpci_dbg(3, "rem fid:%x\n", zdev->fid);
	kमुक्त(zdev);
पूर्ण

पूर्णांक zpci_report_error(काष्ठा pci_dev *pdev,
		      काष्ठा zpci_report_error_header *report)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(pdev);

	वापस sclp_pci_report(report, zdev->fh, zdev->fid);
पूर्ण
EXPORT_SYMBOL(zpci_report_error);

अटल पूर्णांक zpci_mem_init(व्योम)
अणु
	BUILD_BUG_ON(!is_घातer_of_2(__alignof__(काष्ठा zpci_fmb)) ||
		     __alignof__(काष्ठा zpci_fmb) < माप(काष्ठा zpci_fmb));

	zdev_fmb_cache = kmem_cache_create("PCI_FMB_cache", माप(काष्ठा zpci_fmb),
					   __alignof__(काष्ठा zpci_fmb), 0, शून्य);
	अगर (!zdev_fmb_cache)
		जाओ error_fmb;

	zpci_iomap_start = kसुस्मृति(ZPCI_IOMAP_ENTRIES,
				   माप(*zpci_iomap_start), GFP_KERNEL);
	अगर (!zpci_iomap_start)
		जाओ error_iomap;

	zpci_iomap_biपंचांगap = kसुस्मृति(BITS_TO_LONGS(ZPCI_IOMAP_ENTRIES),
				    माप(*zpci_iomap_biपंचांगap), GFP_KERNEL);
	अगर (!zpci_iomap_biपंचांगap)
		जाओ error_iomap_biपंचांगap;

	अगर (अटल_branch_likely(&have_mio))
		clp_setup_ग_लिखोback_mio();

	वापस 0;
error_iomap_biपंचांगap:
	kमुक्त(zpci_iomap_start);
error_iomap:
	kmem_cache_destroy(zdev_fmb_cache);
error_fmb:
	वापस -ENOMEM;
पूर्ण

अटल व्योम zpci_mem_निकास(व्योम)
अणु
	kमुक्त(zpci_iomap_biपंचांगap);
	kमुक्त(zpci_iomap_start);
	kmem_cache_destroy(zdev_fmb_cache);
पूर्ण

अटल अचिन्हित पूर्णांक s390_pci_probe __initdata = 1;
अटल अचिन्हित पूर्णांक s390_pci_no_mio __initdata;
अचिन्हित पूर्णांक s390_pci_क्रमce_भग्नing __initdata;
अटल अचिन्हित पूर्णांक s390_pci_initialized;

अक्षर * __init pcibios_setup(अक्षर *str)
अणु
	अगर (!म_भेद(str, "off")) अणु
		s390_pci_probe = 0;
		वापस शून्य;
	पूर्ण
	अगर (!म_भेद(str, "nomio")) अणु
		s390_pci_no_mio = 1;
		वापस शून्य;
	पूर्ण
	अगर (!म_भेद(str, "force_floating")) अणु
		s390_pci_क्रमce_भग्नing = 1;
		वापस शून्य;
	पूर्ण
	अगर (!म_भेद(str, "norid")) अणु
		s390_pci_no_rid = 1;
		वापस शून्य;
	पूर्ण
	वापस str;
पूर्ण

bool zpci_is_enabled(व्योम)
अणु
	वापस s390_pci_initialized;
पूर्ण

अटल पूर्णांक __init pci_base_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!s390_pci_probe)
		वापस 0;

	अगर (!test_facility(69) || !test_facility(71)) अणु
		pr_info("PCI is not supported because CPU facilities 69 or 71 are not available\n");
		वापस 0;
	पूर्ण

	अगर (test_facility(153) && !s390_pci_no_mio) अणु
		अटल_branch_enable(&have_mio);
		ctl_set_bit(2, 5);
	पूर्ण

	rc = zpci_debug_init();
	अगर (rc)
		जाओ out;

	rc = zpci_mem_init();
	अगर (rc)
		जाओ out_mem;

	rc = zpci_irq_init();
	अगर (rc)
		जाओ out_irq;

	rc = zpci_dma_init();
	अगर (rc)
		जाओ out_dma;

	rc = clp_scan_pci_devices();
	अगर (rc)
		जाओ out_find;
	zpci_bus_scan_busses();

	s390_pci_initialized = 1;
	वापस 0;

out_find:
	zpci_dma_निकास();
out_dma:
	zpci_irq_निकास();
out_irq:
	zpci_mem_निकास();
out_mem:
	zpci_debug_निकास();
out:
	वापस rc;
पूर्ण
subsys_initcall_sync(pci_base_init);
