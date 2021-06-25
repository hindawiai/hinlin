<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2016 Broadcom
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/slab.h>

/*
 * On 64-bit प्रणालीs, we करो a single ioremap क्रम the whole config space
 * since we have enough भव address range available.  On 32-bit, we
 * ioremap the config space क्रम each bus inभागidually.
 */
अटल स्थिर bool per_bus_mapping = !IS_ENABLED(CONFIG_64BIT);

/*
 * Create a PCI config space winकरोw
 *  - reserve mem region
 *  - alloc काष्ठा pci_config_winकरोw with space क्रम all mappings
 *  - ioremap the config space
 */
काष्ठा pci_config_winकरोw *pci_ecam_create(काष्ठा device *dev,
		काष्ठा resource *cfgres, काष्ठा resource *busr,
		स्थिर काष्ठा pci_ecam_ops *ops)
अणु
	अचिन्हित पूर्णांक bus_shअगरt = ops->bus_shअगरt;
	काष्ठा pci_config_winकरोw *cfg;
	अचिन्हित पूर्णांक bus_range, bus_range_max, bsz;
	काष्ठा resource *conflict;
	पूर्णांक i, err;

	अगर (busr->start > busr->end)
		वापस ERR_PTR(-EINVAL);

	cfg = kzalloc(माप(*cfg), GFP_KERNEL);
	अगर (!cfg)
		वापस ERR_PTR(-ENOMEM);

	/* ECAM-compliant platक्रमms need not supply ops->bus_shअगरt */
	अगर (!bus_shअगरt)
		bus_shअगरt = PCIE_ECAM_BUS_SHIFT;

	cfg->parent = dev;
	cfg->ops = ops;
	cfg->busr.start = busr->start;
	cfg->busr.end = busr->end;
	cfg->busr.flags = IORESOURCE_BUS;
	bus_range = resource_size(&cfg->busr);
	bus_range_max = resource_size(cfgres) >> bus_shअगरt;
	अगर (bus_range > bus_range_max) अणु
		bus_range = bus_range_max;
		cfg->busr.end = busr->start + bus_range - 1;
		dev_warn(dev, "ECAM area %pR can only accommodate %pR (reduced from %pR desired)\n",
			 cfgres, &cfg->busr, busr);
	पूर्ण
	bsz = 1 << bus_shअगरt;

	cfg->res.start = cfgres->start;
	cfg->res.end = cfgres->end;
	cfg->res.flags = IORESOURCE_MEM | IORESOURCE_BUSY;
	cfg->res.name = "PCI ECAM";

	conflict = request_resource_conflict(&iomem_resource, &cfg->res);
	अगर (conflict) अणु
		err = -EBUSY;
		dev_err(dev, "can't claim ECAM area %pR: address conflict with %s %pR\n",
			&cfg->res, conflict->name, conflict);
		जाओ err_निकास;
	पूर्ण

	अगर (per_bus_mapping) अणु
		cfg->winp = kसुस्मृति(bus_range, माप(*cfg->winp), GFP_KERNEL);
		अगर (!cfg->winp)
			जाओ err_निकास_दो_स्मृति;
		क्रम (i = 0; i < bus_range; i++) अणु
			cfg->winp[i] =
				pci_remap_cfgspace(cfgres->start + i * bsz,
						   bsz);
			अगर (!cfg->winp[i])
				जाओ err_निकास_iomap;
		पूर्ण
	पूर्ण अन्यथा अणु
		cfg->win = pci_remap_cfgspace(cfgres->start, bus_range * bsz);
		अगर (!cfg->win)
			जाओ err_निकास_iomap;
	पूर्ण

	अगर (ops->init) अणु
		err = ops->init(cfg);
		अगर (err)
			जाओ err_निकास;
	पूर्ण
	dev_info(dev, "ECAM at %pR for %pR\n", &cfg->res, &cfg->busr);
	वापस cfg;

err_निकास_iomap:
	dev_err(dev, "ECAM ioremap failed\n");
err_निकास_दो_स्मृति:
	err = -ENOMEM;
err_निकास:
	pci_ecam_मुक्त(cfg);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(pci_ecam_create);

व्योम pci_ecam_मुक्त(काष्ठा pci_config_winकरोw *cfg)
अणु
	पूर्णांक i;

	अगर (per_bus_mapping) अणु
		अगर (cfg->winp) अणु
			क्रम (i = 0; i < resource_size(&cfg->busr); i++)
				अगर (cfg->winp[i])
					iounmap(cfg->winp[i]);
			kमुक्त(cfg->winp);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cfg->win)
			iounmap(cfg->win);
	पूर्ण
	अगर (cfg->res.parent)
		release_resource(&cfg->res);
	kमुक्त(cfg);
पूर्ण
EXPORT_SYMBOL_GPL(pci_ecam_मुक्त);

/*
 * Function to implement the pci_ops ->map_bus method
 */
व्योम __iomem *pci_ecam_map_bus(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			       पूर्णांक where)
अणु
	काष्ठा pci_config_winकरोw *cfg = bus->sysdata;
	अचिन्हित पूर्णांक bus_shअगरt = cfg->ops->bus_shअगरt;
	अचिन्हित पूर्णांक devfn_shअगरt = cfg->ops->bus_shअगरt - 8;
	अचिन्हित पूर्णांक busn = bus->number;
	व्योम __iomem *base;
	u32 bus_offset, devfn_offset;

	अगर (busn < cfg->busr.start || busn > cfg->busr.end)
		वापस शून्य;

	busn -= cfg->busr.start;
	अगर (per_bus_mapping) अणु
		base = cfg->winp[busn];
		busn = 0;
	पूर्ण अन्यथा
		base = cfg->win;

	अगर (cfg->ops->bus_shअगरt) अणु
		bus_offset = (busn & PCIE_ECAM_BUS_MASK) << bus_shअगरt;
		devfn_offset = (devfn & PCIE_ECAM_DEVFN_MASK) << devfn_shअगरt;
		where &= PCIE_ECAM_REG_MASK;

		वापस base + (bus_offset | devfn_offset | where);
	पूर्ण

	वापस base + PCIE_ECAM_OFFSET(busn, devfn, where);
पूर्ण
EXPORT_SYMBOL_GPL(pci_ecam_map_bus);

/* ECAM ops */
स्थिर काष्ठा pci_ecam_ops pci_generic_ecam_ops = अणु
	.pci_ops	= अणु
		.map_bus	= pci_ecam_map_bus,
		.पढ़ो		= pci_generic_config_पढ़ो,
		.ग_लिखो		= pci_generic_config_ग_लिखो,
	पूर्ण
पूर्ण;
EXPORT_SYMBOL_GPL(pci_generic_ecam_ops);

#अगर defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIRKS)
/* ECAM ops क्रम 32-bit access only (non-compliant) */
स्थिर काष्ठा pci_ecam_ops pci_32b_ops = अणु
	.pci_ops	= अणु
		.map_bus	= pci_ecam_map_bus,
		.पढ़ो		= pci_generic_config_पढ़ो32,
		.ग_लिखो		= pci_generic_config_ग_लिखो32,
	पूर्ण
पूर्ण;

/* ECAM ops क्रम 32-bit पढ़ो only (non-compliant) */
स्थिर काष्ठा pci_ecam_ops pci_32b_पढ़ो_ops = अणु
	.pci_ops	= अणु
		.map_bus	= pci_ecam_map_bus,
		.पढ़ो		= pci_generic_config_पढ़ो32,
		.ग_लिखो		= pci_generic_config_ग_लिखो,
	पूर्ण
पूर्ण;
#पूर्ण_अगर
