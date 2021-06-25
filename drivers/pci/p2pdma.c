<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Peer 2 Peer DMA support.
 *
 * Copyright (c) 2016-2018, Logan Gunthorpe
 * Copyright (c) 2016-2017, Microsemi Corporation
 * Copyright (c) 2017, Christoph Hellwig
 * Copyright (c) 2018, Eideticom Inc.
 */

#घोषणा pr_fmt(fmt) "pci-p2pdma: " fmt
#समावेश <linux/प्रकार.स>
#समावेश <linux/pci-p2pdma.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/memremap.h>
#समावेश <linux/percpu-refcount.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/seq_buf.h>
#समावेश <linux/xarray.h>

क्रमागत pci_p2pdma_map_type अणु
	PCI_P2PDMA_MAP_UNKNOWN = 0,
	PCI_P2PDMA_MAP_NOT_SUPPORTED,
	PCI_P2PDMA_MAP_BUS_ADDR,
	PCI_P2PDMA_MAP_THRU_HOST_BRIDGE,
पूर्ण;

काष्ठा pci_p2pdma अणु
	काष्ठा gen_pool *pool;
	bool p2pmem_published;
	काष्ठा xarray map_types;
पूर्ण;

काष्ठा pci_p2pdma_pagemap अणु
	काष्ठा dev_pagemap pgmap;
	काष्ठा pci_dev *provider;
	u64 bus_offset;
पूर्ण;

अटल काष्ठा pci_p2pdma_pagemap *to_p2p_pgmap(काष्ठा dev_pagemap *pgmap)
अणु
	वापस container_of(pgmap, काष्ठा pci_p2pdma_pagemap, pgmap);
पूर्ण

अटल sमाप_प्रकार size_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	माप_प्रकार size = 0;

	अगर (pdev->p2pdma->pool)
		size = gen_pool_size(pdev->p2pdma->pool);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%zd\n", size);
पूर्ण
अटल DEVICE_ATTR_RO(size);

अटल sमाप_प्रकार available_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	माप_प्रकार avail = 0;

	अगर (pdev->p2pdma->pool)
		avail = gen_pool_avail(pdev->p2pdma->pool);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%zd\n", avail);
पूर्ण
अटल DEVICE_ATTR_RO(available);

अटल sमाप_प्रकार published_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n",
			 pdev->p2pdma->p2pmem_published);
पूर्ण
अटल DEVICE_ATTR_RO(published);

अटल काष्ठा attribute *p2pmem_attrs[] = अणु
	&dev_attr_size.attr,
	&dev_attr_available.attr,
	&dev_attr_published.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group p2pmem_group = अणु
	.attrs = p2pmem_attrs,
	.name = "p2pmem",
पूर्ण;

अटल व्योम pci_p2pdma_release(व्योम *data)
अणु
	काष्ठा pci_dev *pdev = data;
	काष्ठा pci_p2pdma *p2pdma = pdev->p2pdma;

	अगर (!p2pdma)
		वापस;

	/* Flush and disable pci_alloc_p2p_mem() */
	pdev->p2pdma = शून्य;
	synchronize_rcu();

	gen_pool_destroy(p2pdma->pool);
	sysfs_हटाओ_group(&pdev->dev.kobj, &p2pmem_group);
	xa_destroy(&p2pdma->map_types);
पूर्ण

अटल पूर्णांक pci_p2pdma_setup(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक error = -ENOMEM;
	काष्ठा pci_p2pdma *p2p;

	p2p = devm_kzalloc(&pdev->dev, माप(*p2p), GFP_KERNEL);
	अगर (!p2p)
		वापस -ENOMEM;

	xa_init(&p2p->map_types);

	p2p->pool = gen_pool_create(PAGE_SHIFT, dev_to_node(&pdev->dev));
	अगर (!p2p->pool)
		जाओ out;

	error = devm_add_action_or_reset(&pdev->dev, pci_p2pdma_release, pdev);
	अगर (error)
		जाओ out_pool_destroy;

	pdev->p2pdma = p2p;

	error = sysfs_create_group(&pdev->dev.kobj, &p2pmem_group);
	अगर (error)
		जाओ out_pool_destroy;

	वापस 0;

out_pool_destroy:
	pdev->p2pdma = शून्य;
	gen_pool_destroy(p2p->pool);
out:
	devm_kमुक्त(&pdev->dev, p2p);
	वापस error;
पूर्ण

/**
 * pci_p2pdma_add_resource - add memory क्रम use as p2p memory
 * @pdev: the device to add the memory to
 * @bar: PCI BAR to add
 * @size: size of the memory to add, may be zero to use the whole BAR
 * @offset: offset पूर्णांकo the PCI BAR
 *
 * The memory will be given ZONE_DEVICE काष्ठा pages so that it may
 * be used with any DMA request.
 */
पूर्णांक pci_p2pdma_add_resource(काष्ठा pci_dev *pdev, पूर्णांक bar, माप_प्रकार size,
			    u64 offset)
अणु
	काष्ठा pci_p2pdma_pagemap *p2p_pgmap;
	काष्ठा dev_pagemap *pgmap;
	व्योम *addr;
	पूर्णांक error;

	अगर (!(pci_resource_flags(pdev, bar) & IORESOURCE_MEM))
		वापस -EINVAL;

	अगर (offset >= pci_resource_len(pdev, bar))
		वापस -EINVAL;

	अगर (!size)
		size = pci_resource_len(pdev, bar) - offset;

	अगर (size + offset > pci_resource_len(pdev, bar))
		वापस -EINVAL;

	अगर (!pdev->p2pdma) अणु
		error = pci_p2pdma_setup(pdev);
		अगर (error)
			वापस error;
	पूर्ण

	p2p_pgmap = devm_kzalloc(&pdev->dev, माप(*p2p_pgmap), GFP_KERNEL);
	अगर (!p2p_pgmap)
		वापस -ENOMEM;

	pgmap = &p2p_pgmap->pgmap;
	pgmap->range.start = pci_resource_start(pdev, bar) + offset;
	pgmap->range.end = pgmap->range.start + size - 1;
	pgmap->nr_range = 1;
	pgmap->type = MEMORY_DEVICE_PCI_P2PDMA;

	p2p_pgmap->provider = pdev;
	p2p_pgmap->bus_offset = pci_bus_address(pdev, bar) -
		pci_resource_start(pdev, bar);

	addr = devm_memremap_pages(&pdev->dev, pgmap);
	अगर (IS_ERR(addr)) अणु
		error = PTR_ERR(addr);
		जाओ pgmap_मुक्त;
	पूर्ण

	error = gen_pool_add_owner(pdev->p2pdma->pool, (अचिन्हित दीर्घ)addr,
			pci_bus_address(pdev, bar) + offset,
			range_len(&pgmap->range), dev_to_node(&pdev->dev),
			pgmap->ref);
	अगर (error)
		जाओ pages_मुक्त;

	pci_info(pdev, "added peer-to-peer DMA memory %#llx-%#llx\n",
		 pgmap->range.start, pgmap->range.end);

	वापस 0;

pages_मुक्त:
	devm_memunmap_pages(&pdev->dev, pgmap);
pgmap_मुक्त:
	devm_kमुक्त(&pdev->dev, pgmap);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(pci_p2pdma_add_resource);

/*
 * Note this function वापसs the parent PCI device with a
 * reference taken. It is the caller's responsibility to drop
 * the reference.
 */
अटल काष्ठा pci_dev *find_parent_pci_dev(काष्ठा device *dev)
अणु
	काष्ठा device *parent;

	dev = get_device(dev);

	जबतक (dev) अणु
		अगर (dev_is_pci(dev))
			वापस to_pci_dev(dev);

		parent = get_device(dev->parent);
		put_device(dev);
		dev = parent;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Check अगर a PCI bridge has its ACS redirection bits set to redirect P2P
 * TLPs upstream via ACS. Returns 1 अगर the packets will be redirected
 * upstream, 0 otherwise.
 */
अटल पूर्णांक pci_bridge_has_acs_redir(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक pos;
	u16 ctrl;

	pos = pdev->acs_cap;
	अगर (!pos)
		वापस 0;

	pci_पढ़ो_config_word(pdev, pos + PCI_ACS_CTRL, &ctrl);

	अगर (ctrl & (PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_EC))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम seq_buf_prपूर्णांक_bus_devfn(काष्ठा seq_buf *buf, काष्ठा pci_dev *pdev)
अणु
	अगर (!buf)
		वापस;

	seq_buf_म_लिखो(buf, "%s;", pci_name(pdev));
पूर्ण

अटल bool cpu_supports_p2pdma(व्योम)
अणु
#अगर_घोषित CONFIG_X86
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);

	/* Any AMD CPU whose family ID is Zen or newer supports p2pdma */
	अगर (c->x86_venकरोr == X86_VENDOR_AMD && c->x86 >= 0x17)
		वापस true;
#पूर्ण_अगर

	वापस false;
पूर्ण

अटल स्थिर काष्ठा pci_p2pdma_whitelist_entry अणु
	अचिन्हित लघु venकरोr;
	अचिन्हित लघु device;
	क्रमागत अणु
		REQ_SAME_HOST_BRIDGE	= 1 << 0,
	पूर्ण flags;
पूर्ण pci_p2pdma_whitelist[] = अणु
	/* Intel Xeon E5/Core i7 */
	अणुPCI_VENDOR_ID_INTEL,	0x3c00, REQ_SAME_HOST_BRIDGEपूर्ण,
	अणुPCI_VENDOR_ID_INTEL,	0x3c01, REQ_SAME_HOST_BRIDGEपूर्ण,
	/* Intel Xeon E7 v3/Xeon E5 v3/Core i7 */
	अणुPCI_VENDOR_ID_INTEL,	0x2f00, REQ_SAME_HOST_BRIDGEपूर्ण,
	अणुPCI_VENDOR_ID_INTEL,	0x2f01, REQ_SAME_HOST_BRIDGEपूर्ण,
	/* Intel SkyLake-E */
	अणुPCI_VENDOR_ID_INTEL,	0x2030, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL,	0x2031, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL,	0x2032, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL,	0x2033, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL,	0x2020, 0पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल bool __host_bridge_whitelist(काष्ठा pci_host_bridge *host,
				    bool same_host_bridge)
अणु
	काष्ठा pci_dev *root = pci_get_slot(host->bus, PCI_DEVFN(0, 0));
	स्थिर काष्ठा pci_p2pdma_whitelist_entry *entry;
	अचिन्हित लघु venकरोr, device;

	अगर (!root)
		वापस false;

	venकरोr = root->venकरोr;
	device = root->device;
	pci_dev_put(root);

	क्रम (entry = pci_p2pdma_whitelist; entry->venकरोr; entry++) अणु
		अगर (venकरोr != entry->venकरोr || device != entry->device)
			जारी;
		अगर (entry->flags & REQ_SAME_HOST_BRIDGE && !same_host_bridge)
			वापस false;

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * If we can't find a common upstream bridge take a look at the root
 * complex and compare it to a whitelist of known good hardware.
 */
अटल bool host_bridge_whitelist(काष्ठा pci_dev *a, काष्ठा pci_dev *b)
अणु
	काष्ठा pci_host_bridge *host_a = pci_find_host_bridge(a->bus);
	काष्ठा pci_host_bridge *host_b = pci_find_host_bridge(b->bus);

	अगर (host_a == host_b)
		वापस __host_bridge_whitelist(host_a, true);

	अगर (__host_bridge_whitelist(host_a, false) &&
	    __host_bridge_whitelist(host_b, false))
		वापस true;

	वापस false;
पूर्ण

अटल क्रमागत pci_p2pdma_map_type
__upstream_bridge_distance(काष्ठा pci_dev *provider, काष्ठा pci_dev *client,
		पूर्णांक *dist, bool *acs_redirects, काष्ठा seq_buf *acs_list)
अणु
	काष्ठा pci_dev *a = provider, *b = client, *bb;
	पूर्णांक dist_a = 0;
	पूर्णांक dist_b = 0;
	पूर्णांक acs_cnt = 0;

	अगर (acs_redirects)
		*acs_redirects = false;

	/*
	 * Note, we करोn't need to take references to devices वापसed by
	 * pci_upstream_bridge() seeing we hold a reference to a child
	 * device which will alपढ़ोy hold a reference to the upstream bridge.
	 */

	जबतक (a) अणु
		dist_b = 0;

		अगर (pci_bridge_has_acs_redir(a)) अणु
			seq_buf_prपूर्णांक_bus_devfn(acs_list, a);
			acs_cnt++;
		पूर्ण

		bb = b;

		जबतक (bb) अणु
			अगर (a == bb)
				जाओ check_b_path_acs;

			bb = pci_upstream_bridge(bb);
			dist_b++;
		पूर्ण

		a = pci_upstream_bridge(a);
		dist_a++;
	पूर्ण

	अगर (dist)
		*dist = dist_a + dist_b;

	वापस PCI_P2PDMA_MAP_THRU_HOST_BRIDGE;

check_b_path_acs:
	bb = b;

	जबतक (bb) अणु
		अगर (a == bb)
			अवरोध;

		अगर (pci_bridge_has_acs_redir(bb)) अणु
			seq_buf_prपूर्णांक_bus_devfn(acs_list, bb);
			acs_cnt++;
		पूर्ण

		bb = pci_upstream_bridge(bb);
	पूर्ण

	अगर (dist)
		*dist = dist_a + dist_b;

	अगर (acs_cnt) अणु
		अगर (acs_redirects)
			*acs_redirects = true;

		वापस PCI_P2PDMA_MAP_THRU_HOST_BRIDGE;
	पूर्ण

	वापस PCI_P2PDMA_MAP_BUS_ADDR;
पूर्ण

अटल अचिन्हित दीर्घ map_types_idx(काष्ठा pci_dev *client)
अणु
	वापस (pci_करोमुख्य_nr(client->bus) << 16) |
		(client->bus->number << 8) | client->devfn;
पूर्ण

/*
 * Find the distance through the nearest common upstream bridge between
 * two PCI devices.
 *
 * If the two devices are the same device then 0 will be वापसed.
 *
 * If there are two भव functions of the same device behind the same
 * bridge port then 2 will be वापसed (one step करोwn to the PCIe चयन,
 * then one step back to the same device).
 *
 * In the हाल where two devices are connected to the same PCIe चयन, the
 * value 4 will be वापसed. This corresponds to the following PCI tree:
 *
 *     -+  Root Port
 *      \+ Switch Upstream Port
 *       +-+ Switch Downstream Port
 *       + \- Device A
 *       \-+ Switch Downstream Port
 *         \- Device B
 *
 * The distance is 4 because we traverse from Device A through the करोwnstream
 * port of the चयन, to the common upstream port, back up to the second
 * करोwnstream port and then to Device B.
 *
 * Any two devices that cannot communicate using p2pdma will वापस
 * PCI_P2PDMA_MAP_NOT_SUPPORTED.
 *
 * Any two devices that have a data path that goes through the host bridge
 * will consult a whitelist. If the host bridges are on the whitelist,
 * this function will वापस PCI_P2PDMA_MAP_THRU_HOST_BRIDGE.
 *
 * If either bridge is not on the whitelist this function वापसs
 * PCI_P2PDMA_MAP_NOT_SUPPORTED.
 *
 * If a bridge which has any ACS redirection bits set is in the path,
 * acs_redirects will be set to true. In this हाल, a list of all infringing
 * bridge addresses will be populated in acs_list (assuming it's non-null)
 * क्रम prपूर्णांकk purposes.
 */
अटल क्रमागत pci_p2pdma_map_type
upstream_bridge_distance(काष्ठा pci_dev *provider, काष्ठा pci_dev *client,
		पूर्णांक *dist, bool *acs_redirects, काष्ठा seq_buf *acs_list)
अणु
	क्रमागत pci_p2pdma_map_type map_type;

	map_type = __upstream_bridge_distance(provider, client, dist,
					      acs_redirects, acs_list);

	अगर (map_type == PCI_P2PDMA_MAP_THRU_HOST_BRIDGE) अणु
		अगर (!cpu_supports_p2pdma() &&
		    !host_bridge_whitelist(provider, client))
			map_type = PCI_P2PDMA_MAP_NOT_SUPPORTED;
	पूर्ण

	अगर (provider->p2pdma)
		xa_store(&provider->p2pdma->map_types, map_types_idx(client),
			 xa_mk_value(map_type), GFP_KERNEL);

	वापस map_type;
पूर्ण

अटल क्रमागत pci_p2pdma_map_type
upstream_bridge_distance_warn(काष्ठा pci_dev *provider, काष्ठा pci_dev *client,
			      पूर्णांक *dist)
अणु
	काष्ठा seq_buf acs_list;
	bool acs_redirects;
	पूर्णांक ret;

	seq_buf_init(&acs_list, kदो_स्मृति(PAGE_SIZE, GFP_KERNEL), PAGE_SIZE);
	अगर (!acs_list.buffer)
		वापस -ENOMEM;

	ret = upstream_bridge_distance(provider, client, dist, &acs_redirects,
				       &acs_list);
	अगर (acs_redirects) अणु
		pci_warn(client, "ACS redirect is set between the client and provider (%s)\n",
			 pci_name(provider));
		/* Drop final semicolon */
		acs_list.buffer[acs_list.len-1] = 0;
		pci_warn(client, "to disable ACS redirect for this path, add the kernel parameter: pci=disable_acs_redir=%s\n",
			 acs_list.buffer);
	पूर्ण

	अगर (ret == PCI_P2PDMA_MAP_NOT_SUPPORTED) अणु
		pci_warn(client, "cannot be used for peer-to-peer DMA as the client and provider (%s) do not share an upstream bridge or whitelisted host bridge\n",
			 pci_name(provider));
	पूर्ण

	kमुक्त(acs_list.buffer);

	वापस ret;
पूर्ण

/**
 * pci_p2pdma_distance_many - Determine the cumulative distance between
 *	a p2pdma provider and the clients in use.
 * @provider: p2pdma provider to check against the client list
 * @clients: array of devices to check (शून्य-terminated)
 * @num_clients: number of clients in the array
 * @verbose: अगर true, prपूर्णांक warnings क्रम devices when we वापस -1
 *
 * Returns -1 अगर any of the clients are not compatible, otherwise वापसs a
 * positive number where a lower number is the preferable choice. (If there's
 * one client that's the same as the provider it will वापस 0, which is best
 * choice).
 *
 * "compatible" means the provider and the clients are either all behind
 * the same PCI root port or the host bridges connected to each of the devices
 * are listed in the 'pci_p2pdma_whitelist'.
 */
पूर्णांक pci_p2pdma_distance_many(काष्ठा pci_dev *provider, काष्ठा device **clients,
			     पूर्णांक num_clients, bool verbose)
अणु
	bool not_supported = false;
	काष्ठा pci_dev *pci_client;
	पूर्णांक total_dist = 0;
	पूर्णांक distance;
	पूर्णांक i, ret;

	अगर (num_clients == 0)
		वापस -1;

	क्रम (i = 0; i < num_clients; i++) अणु
		pci_client = find_parent_pci_dev(clients[i]);
		अगर (!pci_client) अणु
			अगर (verbose)
				dev_warn(clients[i],
					 "cannot be used for peer-to-peer DMA as it is not a PCI device\n");
			वापस -1;
		पूर्ण

		अगर (verbose)
			ret = upstream_bridge_distance_warn(provider,
					pci_client, &distance);
		अन्यथा
			ret = upstream_bridge_distance(provider, pci_client,
						       &distance, शून्य, शून्य);

		pci_dev_put(pci_client);

		अगर (ret == PCI_P2PDMA_MAP_NOT_SUPPORTED)
			not_supported = true;

		अगर (not_supported && !verbose)
			अवरोध;

		total_dist += distance;
	पूर्ण

	अगर (not_supported)
		वापस -1;

	वापस total_dist;
पूर्ण
EXPORT_SYMBOL_GPL(pci_p2pdma_distance_many);

/**
 * pci_has_p2pmem - check अगर a given PCI device has published any p2pmem
 * @pdev: PCI device to check
 */
bool pci_has_p2pmem(काष्ठा pci_dev *pdev)
अणु
	वापस pdev->p2pdma && pdev->p2pdma->p2pmem_published;
पूर्ण
EXPORT_SYMBOL_GPL(pci_has_p2pmem);

/**
 * pci_p2pmem_find_many - find a peer-to-peer DMA memory device compatible with
 *	the specअगरied list of clients and लघुest distance (as determined
 *	by pci_p2pmem_dma())
 * @clients: array of devices to check (शून्य-terminated)
 * @num_clients: number of client devices in the list
 *
 * If multiple devices are behind the same चयन, the one "closest" to the
 * client devices in use will be chosen first. (So अगर one of the providers is
 * the same as one of the clients, that provider will be used ahead of any
 * other providers that are unrelated). If multiple providers are an equal
 * distance away, one will be chosen at अक्रमom.
 *
 * Returns a poपूर्णांकer to the PCI device with a reference taken (use pci_dev_put
 * to वापस the reference) or शून्य अगर no compatible device is found. The
 * found provider will also be asचिन्हित to the client list.
 */
काष्ठा pci_dev *pci_p2pmem_find_many(काष्ठा device **clients, पूर्णांक num_clients)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	पूर्णांक distance;
	पूर्णांक बंदst_distance = पूर्णांक_उच्च;
	काष्ठा pci_dev **बंदst_pdevs;
	पूर्णांक dev_cnt = 0;
	स्थिर पूर्णांक max_devs = PAGE_SIZE / माप(*बंदst_pdevs);
	पूर्णांक i;

	बंदst_pdevs = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!बंदst_pdevs)
		वापस शून्य;

	जबतक ((pdev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, pdev))) अणु
		अगर (!pci_has_p2pmem(pdev))
			जारी;

		distance = pci_p2pdma_distance_many(pdev, clients,
						    num_clients, false);
		अगर (distance < 0 || distance > बंदst_distance)
			जारी;

		अगर (distance == बंदst_distance && dev_cnt >= max_devs)
			जारी;

		अगर (distance < बंदst_distance) अणु
			क्रम (i = 0; i < dev_cnt; i++)
				pci_dev_put(बंदst_pdevs[i]);

			dev_cnt = 0;
			बंदst_distance = distance;
		पूर्ण

		बंदst_pdevs[dev_cnt++] = pci_dev_get(pdev);
	पूर्ण

	अगर (dev_cnt)
		pdev = pci_dev_get(बंदst_pdevs[pअक्रमom_u32_max(dev_cnt)]);

	क्रम (i = 0; i < dev_cnt; i++)
		pci_dev_put(बंदst_pdevs[i]);

	kमुक्त(बंदst_pdevs);
	वापस pdev;
पूर्ण
EXPORT_SYMBOL_GPL(pci_p2pmem_find_many);

/**
 * pci_alloc_p2pmem - allocate peer-to-peer DMA memory
 * @pdev: the device to allocate memory from
 * @size: number of bytes to allocate
 *
 * Returns the allocated memory or शून्य on error.
 */
व्योम *pci_alloc_p2pmem(काष्ठा pci_dev *pdev, माप_प्रकार size)
अणु
	व्योम *ret = शून्य;
	काष्ठा percpu_ref *ref;

	/*
	 * Pairs with synchronize_rcu() in pci_p2pdma_release() to
	 * ensure pdev->p2pdma is non-शून्य क्रम the duration of the
	 * पढ़ो-lock.
	 */
	rcu_पढ़ो_lock();
	अगर (unlikely(!pdev->p2pdma))
		जाओ out;

	ret = (व्योम *)gen_pool_alloc_owner(pdev->p2pdma->pool, size,
			(व्योम **) &ref);
	अगर (!ret)
		जाओ out;

	अगर (unlikely(!percpu_ref_tryget_live(ref))) अणु
		gen_pool_मुक्त(pdev->p2pdma->pool, (अचिन्हित दीर्घ) ret, size);
		ret = शून्य;
		जाओ out;
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pci_alloc_p2pmem);

/**
 * pci_मुक्त_p2pmem - मुक्त peer-to-peer DMA memory
 * @pdev: the device the memory was allocated from
 * @addr: address of the memory that was allocated
 * @size: number of bytes that were allocated
 */
व्योम pci_मुक्त_p2pmem(काष्ठा pci_dev *pdev, व्योम *addr, माप_प्रकार size)
अणु
	काष्ठा percpu_ref *ref;

	gen_pool_मुक्त_owner(pdev->p2pdma->pool, (uपूर्णांकptr_t)addr, size,
			(व्योम **) &ref);
	percpu_ref_put(ref);
पूर्ण
EXPORT_SYMBOL_GPL(pci_मुक्त_p2pmem);

/**
 * pci_p2pmem_virt_to_bus - वापस the PCI bus address क्रम a given भव
 *	address obtained with pci_alloc_p2pmem()
 * @pdev: the device the memory was allocated from
 * @addr: address of the memory that was allocated
 */
pci_bus_addr_t pci_p2pmem_virt_to_bus(काष्ठा pci_dev *pdev, व्योम *addr)
अणु
	अगर (!addr)
		वापस 0;
	अगर (!pdev->p2pdma)
		वापस 0;

	/*
	 * Note: when we added the memory to the pool we used the PCI
	 * bus address as the physical address. So gen_pool_virt_to_phys()
	 * actually वापसs the bus address despite the misleading name.
	 */
	वापस gen_pool_virt_to_phys(pdev->p2pdma->pool, (अचिन्हित दीर्घ)addr);
पूर्ण
EXPORT_SYMBOL_GPL(pci_p2pmem_virt_to_bus);

/**
 * pci_p2pmem_alloc_sgl - allocate peer-to-peer DMA memory in a scatterlist
 * @pdev: the device to allocate memory from
 * @nents: the number of SG entries in the list
 * @length: number of bytes to allocate
 *
 * Return: %शून्य on error or &काष्ठा scatterlist poपूर्णांकer and @nents on success
 */
काष्ठा scatterlist *pci_p2pmem_alloc_sgl(काष्ठा pci_dev *pdev,
					 अचिन्हित पूर्णांक *nents, u32 length)
अणु
	काष्ठा scatterlist *sg;
	व्योम *addr;

	sg = kदो_स्मृति(माप(*sg), GFP_KERNEL);
	अगर (!sg)
		वापस शून्य;

	sg_init_table(sg, 1);

	addr = pci_alloc_p2pmem(pdev, length);
	अगर (!addr)
		जाओ out_मुक्त_sg;

	sg_set_buf(sg, addr, length);
	*nents = 1;
	वापस sg;

out_मुक्त_sg:
	kमुक्त(sg);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(pci_p2pmem_alloc_sgl);

/**
 * pci_p2pmem_मुक्त_sgl - मुक्त a scatterlist allocated by pci_p2pmem_alloc_sgl()
 * @pdev: the device to allocate memory from
 * @sgl: the allocated scatterlist
 */
व्योम pci_p2pmem_मुक्त_sgl(काष्ठा pci_dev *pdev, काष्ठा scatterlist *sgl)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक count;

	क्रम_each_sg(sgl, sg, पूर्णांक_उच्च, count) अणु
		अगर (!sg)
			अवरोध;

		pci_मुक्त_p2pmem(pdev, sg_virt(sg), sg->length);
	पूर्ण
	kमुक्त(sgl);
पूर्ण
EXPORT_SYMBOL_GPL(pci_p2pmem_मुक्त_sgl);

/**
 * pci_p2pmem_publish - publish the peer-to-peer DMA memory क्रम use by
 *	other devices with pci_p2pmem_find()
 * @pdev: the device with peer-to-peer DMA memory to publish
 * @publish: set to true to publish the memory, false to unpublish it
 *
 * Published memory can be used by other PCI device drivers क्रम
 * peer-2-peer DMA operations. Non-published memory is reserved क्रम
 * exclusive use of the device driver that रेजिस्टरs the peer-to-peer
 * memory.
 */
व्योम pci_p2pmem_publish(काष्ठा pci_dev *pdev, bool publish)
अणु
	अगर (pdev->p2pdma)
		pdev->p2pdma->p2pmem_published = publish;
पूर्ण
EXPORT_SYMBOL_GPL(pci_p2pmem_publish);

अटल क्रमागत pci_p2pdma_map_type pci_p2pdma_map_type(काष्ठा pci_dev *provider,
						    काष्ठा pci_dev *client)
अणु
	अगर (!provider->p2pdma)
		वापस PCI_P2PDMA_MAP_NOT_SUPPORTED;

	वापस xa_to_value(xa_load(&provider->p2pdma->map_types,
				   map_types_idx(client)));
पूर्ण

अटल पूर्णांक __pci_p2pdma_map_sg(काष्ठा pci_p2pdma_pagemap *p2p_pgmap,
		काष्ठा device *dev, काष्ठा scatterlist *sg, पूर्णांक nents)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक i;

	क्रम_each_sg(sg, s, nents, i) अणु
		s->dma_address = sg_phys(s) - p2p_pgmap->bus_offset;
		sg_dma_len(s) = s->length;
	पूर्ण

	वापस nents;
पूर्ण

/**
 * pci_p2pdma_map_sg_attrs - map a PCI peer-to-peer scatterlist क्रम DMA
 * @dev: device करोing the DMA request
 * @sg: scatter list to map
 * @nents: elements in the scatterlist
 * @dir: DMA direction
 * @attrs: DMA attributes passed to dma_map_sg() (अगर called)
 *
 * Scatterlists mapped with this function should be unmapped using
 * pci_p2pdma_unmap_sg_attrs().
 *
 * Returns the number of SG entries mapped or 0 on error.
 */
पूर्णांक pci_p2pdma_map_sg_attrs(काष्ठा device *dev, काष्ठा scatterlist *sg,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा pci_p2pdma_pagemap *p2p_pgmap =
		to_p2p_pgmap(sg_page(sg)->pgmap);
	काष्ठा pci_dev *client;

	अगर (WARN_ON_ONCE(!dev_is_pci(dev)))
		वापस 0;

	client = to_pci_dev(dev);

	चयन (pci_p2pdma_map_type(p2p_pgmap->provider, client)) अणु
	हाल PCI_P2PDMA_MAP_THRU_HOST_BRIDGE:
		वापस dma_map_sg_attrs(dev, sg, nents, dir, attrs);
	हाल PCI_P2PDMA_MAP_BUS_ADDR:
		वापस __pci_p2pdma_map_sg(p2p_pgmap, dev, sg, nents);
	शेष:
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pci_p2pdma_map_sg_attrs);

/**
 * pci_p2pdma_unmap_sg_attrs - unmap a PCI peer-to-peer scatterlist that was
 *	mapped with pci_p2pdma_map_sg()
 * @dev: device करोing the DMA request
 * @sg: scatter list to map
 * @nents: number of elements वापसed by pci_p2pdma_map_sg()
 * @dir: DMA direction
 * @attrs: DMA attributes passed to dma_unmap_sg() (अगर called)
 */
व्योम pci_p2pdma_unmap_sg_attrs(काष्ठा device *dev, काष्ठा scatterlist *sg,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा pci_p2pdma_pagemap *p2p_pgmap =
		to_p2p_pgmap(sg_page(sg)->pgmap);
	क्रमागत pci_p2pdma_map_type map_type;
	काष्ठा pci_dev *client;

	अगर (WARN_ON_ONCE(!dev_is_pci(dev)))
		वापस;

	client = to_pci_dev(dev);

	map_type = pci_p2pdma_map_type(p2p_pgmap->provider, client);

	अगर (map_type == PCI_P2PDMA_MAP_THRU_HOST_BRIDGE)
		dma_unmap_sg_attrs(dev, sg, nents, dir, attrs);
पूर्ण
EXPORT_SYMBOL_GPL(pci_p2pdma_unmap_sg_attrs);

/**
 * pci_p2pdma_enable_store - parse a configfs/sysfs attribute store
 *		to enable p2pdma
 * @page: contents of the value to be stored
 * @p2p_dev: वापसs the PCI device that was selected to be used
 *		(अगर one was specअगरied in the stored value)
 * @use_p2pdma: वापसs whether to enable p2pdma or not
 *
 * Parses an attribute value to decide whether to enable p2pdma.
 * The value can select a PCI device (using its full BDF device
 * name) or a boolean (in any क्रमmat strtobool() accepts). A false
 * value disables p2pdma, a true value expects the caller
 * to स्वतःmatically find a compatible device and specअगरying a PCI device
 * expects the caller to use the specअगरic provider.
 *
 * pci_p2pdma_enable_show() should be used as the show operation क्रम
 * the attribute.
 *
 * Returns 0 on success
 */
पूर्णांक pci_p2pdma_enable_store(स्थिर अक्षर *page, काष्ठा pci_dev **p2p_dev,
			    bool *use_p2pdma)
अणु
	काष्ठा device *dev;

	dev = bus_find_device_by_name(&pci_bus_type, शून्य, page);
	अगर (dev) अणु
		*use_p2pdma = true;
		*p2p_dev = to_pci_dev(dev);

		अगर (!pci_has_p2pmem(*p2p_dev)) अणु
			pci_err(*p2p_dev,
				"PCI device has no peer-to-peer memory: %s\n",
				page);
			pci_dev_put(*p2p_dev);
			वापस -ENODEV;
		पूर्ण

		वापस 0;
	पूर्ण अन्यथा अगर ((page[0] == '0' || page[0] == '1') && !है_नियंत्रण(page[1])) अणु
		/*
		 * If the user enters a PCI device that  करोesn't exist
		 * like "0000:01:00.1", we करोn't want strtobool to think
		 * it's a '0' when it's clearly not what the user wanted.
		 * So we require 0's and 1's to be exactly one अक्षरacter.
		 */
	पूर्ण अन्यथा अगर (!strtobool(page, use_p2pdma)) अणु
		वापस 0;
	पूर्ण

	pr_err("No such PCI device: %.*s\n", (पूर्णांक)म_खोज(page, "\n"), page);
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(pci_p2pdma_enable_store);

/**
 * pci_p2pdma_enable_show - show a configfs/sysfs attribute indicating
 *		whether p2pdma is enabled
 * @page: contents of the stored value
 * @p2p_dev: the selected p2p device (शून्य अगर no device is selected)
 * @use_p2pdma: whether p2pdma has been enabled
 *
 * Attributes that use pci_p2pdma_enable_store() should use this function
 * to show the value of the attribute.
 *
 * Returns 0 on success
 */
sमाप_प्रकार pci_p2pdma_enable_show(अक्षर *page, काष्ठा pci_dev *p2p_dev,
			       bool use_p2pdma)
अणु
	अगर (!use_p2pdma)
		वापस प्र_लिखो(page, "0\n");

	अगर (!p2p_dev)
		वापस प्र_लिखो(page, "1\n");

	वापस प्र_लिखो(page, "%s\n", pci_name(p2p_dev));
पूर्ण
EXPORT_SYMBOL_GPL(pci_p2pdma_enable_show);
