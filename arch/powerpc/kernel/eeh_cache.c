<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PCI address cache; allows the lookup of PCI devices based on I/O address
 *
 * Copyright IBM Corporation 2004
 * Copyright Linas Vepstas <linas@austin.ibm.com> 2004
 */

#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/ppc-pci.h>


/**
 * DOC: Overview
 *
 * The pci address cache subप्रणाली.  This subप्रणाली places
 * PCI device address resources पूर्णांकo a red-black tree, sorted
 * according to the address range, so that given only an i/o
 * address, the corresponding PCI device can be **quickly**
 * found. It is safe to perक्रमm an address lookup in an पूर्णांकerrupt
 * context; this ability is an important feature.
 *
 * Currently, the only customer of this code is the EEH subप्रणाली;
 * thus, this code has been somewhat tailored to suit EEH better.
 * In particular, the cache करोes *not* hold the addresses of devices
 * क्रम which EEH is not enabled.
 *
 * (Implementation Note: The RB tree seems to be better/faster
 * than any hash algo I could think of क्रम this problem, even
 * with the penalty of slow poपूर्णांकer chases क्रम d-cache misses).
 */

काष्ठा pci_io_addr_range अणु
	काष्ठा rb_node rb_node;
	resource_माप_प्रकार addr_lo;
	resource_माप_प्रकार addr_hi;
	काष्ठा eeh_dev *edev;
	काष्ठा pci_dev *pcidev;
	अचिन्हित दीर्घ flags;
पूर्ण;

अटल काष्ठा pci_io_addr_cache अणु
	काष्ठा rb_root rb_root;
	spinlock_t piar_lock;
पूर्ण pci_io_addr_cache_root;

अटल अंतरभूत काष्ठा eeh_dev *__eeh_addr_cache_get_device(अचिन्हित दीर्घ addr)
अणु
	काष्ठा rb_node *n = pci_io_addr_cache_root.rb_root.rb_node;

	जबतक (n) अणु
		काष्ठा pci_io_addr_range *piar;
		piar = rb_entry(n, काष्ठा pci_io_addr_range, rb_node);

		अगर (addr < piar->addr_lo)
			n = n->rb_left;
		अन्यथा अगर (addr > piar->addr_hi)
			n = n->rb_right;
		अन्यथा
			वापस piar->edev;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * eeh_addr_cache_get_dev - Get device, given only address
 * @addr: mmio (PIO) phys address or i/o port number
 *
 * Given an mmio phys address, or a port number, find a pci device
 * that implements this address.  I/O port numbers are assumed to be offset
 * from zero (that is, they करो *not* have pci_io_addr added in).
 * It is safe to call this function within an पूर्णांकerrupt.
 */
काष्ठा eeh_dev *eeh_addr_cache_get_dev(अचिन्हित दीर्घ addr)
अणु
	काष्ठा eeh_dev *edev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pci_io_addr_cache_root.piar_lock, flags);
	edev = __eeh_addr_cache_get_device(addr);
	spin_unlock_irqrestore(&pci_io_addr_cache_root.piar_lock, flags);
	वापस edev;
पूर्ण

#अगर_घोषित DEBUG
/*
 * Handy-dandy debug prपूर्णांक routine, करोes nothing more
 * than prपूर्णांक out the contents of our addr cache.
 */
अटल व्योम eeh_addr_cache_prपूर्णांक(काष्ठा pci_io_addr_cache *cache)
अणु
	काष्ठा rb_node *n;
	पूर्णांक cnt = 0;

	n = rb_first(&cache->rb_root);
	जबतक (n) अणु
		काष्ठा pci_io_addr_range *piar;
		piar = rb_entry(n, काष्ठा pci_io_addr_range, rb_node);
		pr_info("PCI: %s addr range %d [%pap-%pap]: %s\n",
		       (piar->flags & IORESOURCE_IO) ? "i/o" : "mem", cnt,
		       &piar->addr_lo, &piar->addr_hi, pci_name(piar->pcidev));
		cnt++;
		n = rb_next(n);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/* Insert address range पूर्णांकo the rb tree. */
अटल काष्ठा pci_io_addr_range *
eeh_addr_cache_insert(काष्ठा pci_dev *dev, resource_माप_प्रकार alo,
		      resource_माप_प्रकार ahi, अचिन्हित दीर्घ flags)
अणु
	काष्ठा rb_node **p = &pci_io_addr_cache_root.rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा pci_io_addr_range *piar;

	/* Walk tree, find a place to insert पूर्णांकo tree */
	जबतक (*p) अणु
		parent = *p;
		piar = rb_entry(parent, काष्ठा pci_io_addr_range, rb_node);
		अगर (ahi < piar->addr_lo) अणु
			p = &parent->rb_left;
		पूर्ण अन्यथा अगर (alo > piar->addr_hi) अणु
			p = &parent->rb_right;
		पूर्ण अन्यथा अणु
			अगर (dev != piar->pcidev ||
			    alo != piar->addr_lo || ahi != piar->addr_hi) अणु
				pr_warn("PIAR: overlapping address range\n");
			पूर्ण
			वापस piar;
		पूर्ण
	पूर्ण
	piar = kzalloc(माप(काष्ठा pci_io_addr_range), GFP_ATOMIC);
	अगर (!piar)
		वापस शून्य;

	piar->addr_lo = alo;
	piar->addr_hi = ahi;
	piar->edev = pci_dev_to_eeh_dev(dev);
	piar->pcidev = dev;
	piar->flags = flags;

	eeh_edev_dbg(piar->edev, "PIAR: insert range=[%pap:%pap]\n",
		 &alo, &ahi);

	rb_link_node(&piar->rb_node, parent, p);
	rb_insert_color(&piar->rb_node, &pci_io_addr_cache_root.rb_root);

	वापस piar;
पूर्ण

अटल व्योम __eeh_addr_cache_insert_dev(काष्ठा pci_dev *dev)
अणु
	काष्ठा eeh_dev *edev;
	पूर्णांक i;

	edev = pci_dev_to_eeh_dev(dev);
	अगर (!edev) अणु
		pr_warn("PCI: no EEH dev found for %s\n",
			pci_name(dev));
		वापस;
	पूर्ण

	/* Skip any devices क्रम which EEH is not enabled. */
	अगर (!edev->pe) अणु
		dev_dbg(&dev->dev, "EEH: Skip building address cache\n");
		वापस;
	पूर्ण

	/*
	 * Walk resources on this device, poke the first 7 (6 normal BAR and 1
	 * ROM BAR) पूर्णांकo the tree.
	 */
	क्रम (i = 0; i <= PCI_ROM_RESOURCE; i++) अणु
		resource_माप_प्रकार start = pci_resource_start(dev,i);
		resource_माप_प्रकार end = pci_resource_end(dev,i);
		अचिन्हित दीर्घ flags = pci_resource_flags(dev,i);

		/* We are पूर्णांकerested only bus addresses, not dma or other stuff */
		अगर (0 == (flags & (IORESOURCE_IO | IORESOURCE_MEM)))
			जारी;
		अगर (start == 0 || ~start == 0 || end == 0 || ~end == 0)
			 जारी;
		eeh_addr_cache_insert(dev, start, end, flags);
	पूर्ण
पूर्ण

/**
 * eeh_addr_cache_insert_dev - Add a device to the address cache
 * @dev: PCI device whose I/O addresses we are पूर्णांकerested in.
 *
 * In order to support the fast lookup of devices based on addresses,
 * we मुख्यtain a cache of devices that can be quickly searched.
 * This routine adds a device to that cache.
 */
व्योम eeh_addr_cache_insert_dev(काष्ठा pci_dev *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pci_io_addr_cache_root.piar_lock, flags);
	__eeh_addr_cache_insert_dev(dev);
	spin_unlock_irqrestore(&pci_io_addr_cache_root.piar_lock, flags);
पूर्ण

अटल अंतरभूत व्योम __eeh_addr_cache_rmv_dev(काष्ठा pci_dev *dev)
अणु
	काष्ठा rb_node *n;

restart:
	n = rb_first(&pci_io_addr_cache_root.rb_root);
	जबतक (n) अणु
		काष्ठा pci_io_addr_range *piar;
		piar = rb_entry(n, काष्ठा pci_io_addr_range, rb_node);

		अगर (piar->pcidev == dev) अणु
			eeh_edev_dbg(piar->edev, "PIAR: remove range=[%pap:%pap]\n",
				 &piar->addr_lo, &piar->addr_hi);
			rb_erase(n, &pci_io_addr_cache_root.rb_root);
			kमुक्त(piar);
			जाओ restart;
		पूर्ण
		n = rb_next(n);
	पूर्ण
पूर्ण

/**
 * eeh_addr_cache_rmv_dev - हटाओ pci device from addr cache
 * @dev: device to हटाओ
 *
 * Remove a device from the addr-cache tree.
 * This is potentially expensive, since it will walk
 * the tree multiple बार (once per resource).
 * But so what; device removal करोesn't need to be that fast.
 */
व्योम eeh_addr_cache_rmv_dev(काष्ठा pci_dev *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pci_io_addr_cache_root.piar_lock, flags);
	__eeh_addr_cache_rmv_dev(dev);
	spin_unlock_irqrestore(&pci_io_addr_cache_root.piar_lock, flags);
पूर्ण

/**
 * eeh_addr_cache_init - Initialize a cache of I/O addresses
 *
 * Initialize a cache of pci i/o addresses.  This cache will be used to
 * find the pci device that corresponds to a given address.
 */
व्योम eeh_addr_cache_init(व्योम)
अणु
	spin_lock_init(&pci_io_addr_cache_root.piar_lock);
पूर्ण

अटल पूर्णांक eeh_addr_cache_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा pci_io_addr_range *piar;
	काष्ठा rb_node *n;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pci_io_addr_cache_root.piar_lock, flags);
	क्रम (n = rb_first(&pci_io_addr_cache_root.rb_root); n; n = rb_next(n)) अणु
		piar = rb_entry(n, काष्ठा pci_io_addr_range, rb_node);

		seq_म_लिखो(s, "%s addr range [%pap-%pap]: %s\n",
		       (piar->flags & IORESOURCE_IO) ? "i/o" : "mem",
		       &piar->addr_lo, &piar->addr_hi, pci_name(piar->pcidev));
	पूर्ण
	spin_unlock_irqrestore(&pci_io_addr_cache_root.piar_lock, flags);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(eeh_addr_cache);

व्योम eeh_cache_debugfs_init(व्योम)
अणु
	debugfs_create_file_unsafe("eeh_address_cache", 0400,
			घातerpc_debugfs_root, शून्य,
			&eeh_addr_cache_fops);
पूर्ण
