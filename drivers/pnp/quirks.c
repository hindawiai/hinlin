<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  This file contains quirk handling code क्रम PnP devices
 *  Some devices करो not report all their resources, and need to have extra
 *  resources added. This is most easily accomplished at initialisation समय
 *  when building up the resource काष्ठाure क्रम the first समय.
 *
 *  Copyright (c) 2000 Peter Denison <peterd@pnd-pc.demon.co.uk>
 *  Copyright (C) 2008 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 *
 *  Heavily based on PCI quirks handling which is
 *
 *  Copyright (c) 1999 Martin Mares <mj@ucw.cz>
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/pnp.h>
#समावेश <linux/पन.स>
#समावेश "base.h"

अटल व्योम quirk_awe32_add_ports(काष्ठा pnp_dev *dev,
				  काष्ठा pnp_option *option,
				  अचिन्हित पूर्णांक offset)
अणु
	काष्ठा pnp_option *new_option;

	new_option = kदो_स्मृति(माप(काष्ठा pnp_option), GFP_KERNEL);
	अगर (!new_option) अणु
		dev_err(&dev->dev, "couldn't add ioport region to option set "
			"%d\n", pnp_option_set(option));
		वापस;
	पूर्ण

	*new_option = *option;
	new_option->u.port.min += offset;
	new_option->u.port.max += offset;
	list_add(&new_option->list, &option->list);

	dev_info(&dev->dev, "added ioport region %#llx-%#llx to set %d\n",
		(अचिन्हित दीर्घ दीर्घ) new_option->u.port.min,
		(अचिन्हित दीर्घ दीर्घ) new_option->u.port.max,
		pnp_option_set(option));
पूर्ण

अटल व्योम quirk_awe32_resources(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_option *option;
	अचिन्हित पूर्णांक set = ~0;

	/*
	 * Add two extra ioport regions (at offset 0x400 and 0x800 from the
	 * one given) to every dependent option set.
	 */
	list_क्रम_each_entry(option, &dev->options, list) अणु
		अगर (pnp_option_is_dependent(option) &&
		    pnp_option_set(option) != set) अणु
			set = pnp_option_set(option);
			quirk_awe32_add_ports(dev, option, 0x800);
			quirk_awe32_add_ports(dev, option, 0x400);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम quirk_cmi8330_resources(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_option *option;
	काष्ठा pnp_irq *irq;
	काष्ठा pnp_dma *dma;

	list_क्रम_each_entry(option, &dev->options, list) अणु
		अगर (!pnp_option_is_dependent(option))
			जारी;

		अगर (option->type == IORESOURCE_IRQ) अणु
			irq = &option->u.irq;
			biपंचांगap_zero(irq->map.bits, PNP_IRQ_NR);
			__set_bit(5, irq->map.bits);
			__set_bit(7, irq->map.bits);
			__set_bit(10, irq->map.bits);
			dev_info(&dev->dev, "set possible IRQs in "
				 "option set %d to 5, 7, 10\n",
				 pnp_option_set(option));
		पूर्ण अन्यथा अगर (option->type == IORESOURCE_DMA) अणु
			dma = &option->u.dma;
			अगर ((dma->flags & IORESOURCE_DMA_TYPE_MASK) ==
						IORESOURCE_DMA_8BIT &&
			    dma->map != 0x0A) अणु
				dev_info(&dev->dev, "changing possible "
					 "DMA channel mask in option set %d "
					 "from %#02x to 0x0A (1, 3)\n",
					 pnp_option_set(option), dma->map);
				dma->map = 0x0A;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम quirk_sb16audio_resources(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_option *option;
	अचिन्हित पूर्णांक prev_option_flags = ~0, n = 0;
	काष्ठा pnp_port *port;

	/*
	 * The शेष range on the OPL port क्रम these devices is 0x388-0x388.
	 * Here we increase that range so that two such cards can be
	 * स्वतः-configured.
	 */
	list_क्रम_each_entry(option, &dev->options, list) अणु
		अगर (prev_option_flags != option->flags) अणु
			prev_option_flags = option->flags;
			n = 0;
		पूर्ण

		अगर (pnp_option_is_dependent(option) &&
		    option->type == IORESOURCE_IO) अणु
			n++;
			port = &option->u.port;
			अगर (n == 3 && port->min == port->max) अणु
				port->max += 0x70;
				dev_info(&dev->dev, "increased option port "
					 "range from %#llx-%#llx to "
					 "%#llx-%#llx\n",
					 (अचिन्हित दीर्घ दीर्घ) port->min,
					 (अचिन्हित दीर्घ दीर्घ) port->min,
					 (अचिन्हित दीर्घ दीर्घ) port->min,
					 (अचिन्हित दीर्घ दीर्घ) port->max);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा pnp_option *pnp_clone_dependent_set(काष्ठा pnp_dev *dev,
						  अचिन्हित पूर्णांक set)
अणु
	काष्ठा pnp_option *tail = शून्य, *first_new_option = शून्य;
	काष्ठा pnp_option *option, *new_option;
	अचिन्हित पूर्णांक flags;

	list_क्रम_each_entry(option, &dev->options, list) अणु
		अगर (pnp_option_is_dependent(option))
			tail = option;
	पूर्ण
	अगर (!tail) अणु
		dev_err(&dev->dev, "no dependent option sets\n");
		वापस शून्य;
	पूर्ण

	flags = pnp_new_dependent_set(dev, PNP_RES_PRIORITY_FUNCTIONAL);
	list_क्रम_each_entry(option, &dev->options, list) अणु
		अगर (pnp_option_is_dependent(option) &&
		    pnp_option_set(option) == set) अणु
			new_option = kदो_स्मृति(माप(काष्ठा pnp_option),
					     GFP_KERNEL);
			अगर (!new_option) अणु
				dev_err(&dev->dev, "couldn't clone dependent "
					"set %d\n", set);
				वापस शून्य;
			पूर्ण

			*new_option = *option;
			new_option->flags = flags;
			अगर (!first_new_option)
				first_new_option = new_option;

			list_add(&new_option->list, &tail->list);
			tail = new_option;
		पूर्ण
	पूर्ण

	वापस first_new_option;
पूर्ण


अटल व्योम quirk_add_irq_optional_dependent_sets(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_option *new_option;
	अचिन्हित पूर्णांक num_sets, i, set;
	काष्ठा pnp_irq *irq;

	num_sets = dev->num_dependent_sets;
	क्रम (i = 0; i < num_sets; i++) अणु
		new_option = pnp_clone_dependent_set(dev, i);
		अगर (!new_option)
			वापस;

		set = pnp_option_set(new_option);
		जबतक (new_option && pnp_option_set(new_option) == set) अणु
			अगर (new_option->type == IORESOURCE_IRQ) अणु
				irq = &new_option->u.irq;
				irq->flags |= IORESOURCE_IRQ_OPTIONAL;
			पूर्ण
			dbg_pnp_show_option(dev, new_option);
			new_option = list_entry(new_option->list.next,
						काष्ठा pnp_option, list);
		पूर्ण

		dev_info(&dev->dev, "added dependent option set %d (same as "
			 "set %d except IRQ optional)\n", set, i);
	पूर्ण
पूर्ण

अटल व्योम quirk_ad1815_mpu_resources(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_option *option;
	काष्ठा pnp_irq *irq = शून्य;
	अचिन्हित पूर्णांक independent_irqs = 0;

	list_क्रम_each_entry(option, &dev->options, list) अणु
		अगर (option->type == IORESOURCE_IRQ &&
		    !pnp_option_is_dependent(option)) अणु
			independent_irqs++;
			irq = &option->u.irq;
		पूर्ण
	पूर्ण

	अगर (independent_irqs != 1)
		वापस;

	irq->flags |= IORESOURCE_IRQ_OPTIONAL;
	dev_info(&dev->dev, "made independent IRQ optional\n");
पूर्ण

अटल व्योम quirk_प्रणाली_pci_resources(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	काष्ठा resource *res;
	resource_माप_प्रकार pnp_start, pnp_end, pci_start, pci_end;
	पूर्णांक i, j;

	/*
	 * Some BIOSes have PNP motherboard devices with resources that
	 * partially overlap PCI BARs.  The PNP प्रणाली driver claims these
	 * motherboard resources, which prevents the normal PCI driver from
	 * requesting them later.
	 *
	 * This patch disables the PNP resources that conflict with PCI BARs
	 * so they won't be claimed by the PNP प्रणाली driver.
	 */
	क्रम_each_pci_dev(pdev) अणु
		क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
			अचिन्हित दीर्घ flags, type;

			flags = pci_resource_flags(pdev, i);
			type = flags & (IORESOURCE_IO | IORESOURCE_MEM);
			अगर (!type || pci_resource_len(pdev, i) == 0)
				जारी;

			अगर (flags & IORESOURCE_UNSET)
				जारी;

			pci_start = pci_resource_start(pdev, i);
			pci_end = pci_resource_end(pdev, i);
			क्रम (j = 0;
			     (res = pnp_get_resource(dev, type, j)); j++) अणु
				अगर (res->start == 0 && res->end == 0)
					जारी;

				pnp_start = res->start;
				pnp_end = res->end;

				/*
				 * If the PNP region करोesn't overlap the PCI
				 * region at all, there's no problem.
				 */
				अगर (pnp_end < pci_start || pnp_start > pci_end)
					जारी;

				/*
				 * If the PNP region completely enबंदs (or is
				 * at least as large as) the PCI region, that's
				 * also OK.  For example, this happens when the
				 * PNP device describes a bridge with PCI
				 * behind it.
				 */
				अगर (pnp_start <= pci_start &&
				    pnp_end >= pci_end)
					जारी;

				/*
				 * Otherwise, the PNP region overlaps *part* of
				 * the PCI region, and that might prevent a PCI
				 * driver from requesting its resources.
				 */
				dev_warn(&dev->dev,
					 "disabling %pR because it overlaps "
					 "%s BAR %d %pR\n", res,
					 pci_name(pdev), i, &pdev->resource[i]);
				res->flags |= IORESOURCE_DISABLED;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_AMD_NB

#समावेश <यंत्र/amd_nb.h>

अटल व्योम quirk_amd_mmconfig_area(काष्ठा pnp_dev *dev)
अणु
	resource_माप_प्रकार start, end;
	काष्ठा pnp_resource *pnp_res;
	काष्ठा resource *res;
	काष्ठा resource mmconfig_res, *mmconfig;

	mmconfig = amd_get_mmconfig_range(&mmconfig_res);
	अगर (!mmconfig)
		वापस;

	list_क्रम_each_entry(pnp_res, &dev->resources, list) अणु
		res = &pnp_res->res;
		अगर (res->end < mmconfig->start || res->start > mmconfig->end ||
		    (res->start == mmconfig->start && res->end == mmconfig->end))
			जारी;

		dev_info(&dev->dev, FW_BUG
			 "%pR covers only part of AMD MMCONFIG area %pR; adding more reservations\n",
			 res, mmconfig);
		अगर (mmconfig->start < res->start) अणु
			start = mmconfig->start;
			end = res->start - 1;
			pnp_add_mem_resource(dev, start, end, 0);
		पूर्ण
		अगर (mmconfig->end > res->end) अणु
			start = res->end + 1;
			end = mmconfig->end;
			pnp_add_mem_resource(dev, start, end, 0);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI
/* Device IDs of parts that have 32KB MCH space */
अटल स्थिर अचिन्हित पूर्णांक mch_quirk_devices[] = अणु
	0x0154,	/* Ivy Bridge */
	0x0a04, /* Haswell-ULT */
	0x0c00,	/* Haswell */
	0x1604, /* Broadwell */
पूर्ण;

अटल काष्ठा pci_dev *get_पूर्णांकel_host(व्योम)
अणु
	पूर्णांक i;
	काष्ठा pci_dev *host;

	क्रम (i = 0; i < ARRAY_SIZE(mch_quirk_devices); i++) अणु
		host = pci_get_device(PCI_VENDOR_ID_INTEL, mch_quirk_devices[i],
				      शून्य);
		अगर (host)
			वापस host;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम quirk_पूर्णांकel_mch(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pci_dev *host;
	u32 addr_lo, addr_hi;
	काष्ठा pci_bus_region region;
	काष्ठा resource mch;
	काष्ठा pnp_resource *pnp_res;
	काष्ठा resource *res;

	host = get_पूर्णांकel_host();
	अगर (!host)
		वापस;

	/*
	 * MCHBAR is not an architected PCI BAR, so MCH space is usually
	 * reported as a PNP0C02 resource.  The MCH space was originally
	 * 16KB, but is 32KB in newer parts.  Some BIOSes still report a
	 * PNP0C02 resource that is only 16KB, which means the rest of the
	 * MCH space is consumed but unreported.
	 */

	/*
	 * Read MCHBAR क्रम Host Member Mapped Register Range Base
	 * https://www-ssl.पूर्णांकel.com/content/www/us/en/processors/core/4th-gen-core-family-desktop-vol-2-datasheet
	 * Sec 3.1.12.
	 */
	pci_पढ़ो_config_dword(host, 0x48, &addr_lo);
	region.start = addr_lo & ~0x7fff;
	pci_पढ़ो_config_dword(host, 0x4c, &addr_hi);
	region.start |= (u64) addr_hi << 32;
	region.end = region.start + 32*1024 - 1;

	स_रखो(&mch, 0, माप(mch));
	mch.flags = IORESOURCE_MEM;
	pcibios_bus_to_resource(host->bus, &mch, &region);

	list_क्रम_each_entry(pnp_res, &dev->resources, list) अणु
		res = &pnp_res->res;
		अगर (res->end < mch.start || res->start > mch.end)
			जारी;	/* no overlap */
		अगर (res->start == mch.start && res->end == mch.end)
			जारी;	/* exact match */

		dev_info(&dev->dev, FW_BUG "PNP resource %pR covers only part of %s Intel MCH; extending to %pR\n",
			 res, pci_name(host), &mch);
		res->start = mch.start;
		res->end = mch.end;
		अवरोध;
	पूर्ण

	pci_dev_put(host);
पूर्ण
#पूर्ण_अगर

/*
 *  PnP Quirks
 *  Cards or devices that need some tweaking due to incomplete resource info
 */

अटल काष्ठा pnp_fixup pnp_fixups[] = अणु
	/* Soundblaster awe io port quirk */
	अणु"CTL0021", quirk_awe32_resourcesपूर्ण,
	अणु"CTL0022", quirk_awe32_resourcesपूर्ण,
	अणु"CTL0023", quirk_awe32_resourcesपूर्ण,
	/* CMI 8330 पूर्णांकerrupt and dma fix */
	अणु"@X@0001", quirk_cmi8330_resourcesपूर्ण,
	/* Soundblaster audio device io port range quirk */
	अणु"CTL0001", quirk_sb16audio_resourcesपूर्ण,
	अणु"CTL0031", quirk_sb16audio_resourcesपूर्ण,
	अणु"CTL0041", quirk_sb16audio_resourcesपूर्ण,
	अणु"CTL0042", quirk_sb16audio_resourcesपूर्ण,
	अणु"CTL0043", quirk_sb16audio_resourcesपूर्ण,
	अणु"CTL0044", quirk_sb16audio_resourcesपूर्ण,
	अणु"CTL0045", quirk_sb16audio_resourcesपूर्ण,
	/* Add IRQ-optional MPU options */
	अणु"ADS7151", quirk_ad1815_mpu_resourcesपूर्ण,
	अणु"ADS7181", quirk_add_irq_optional_dependent_setsपूर्ण,
	अणु"AZT0002", quirk_add_irq_optional_dependent_setsपूर्ण,
	/* PnP resources that might overlap PCI BARs */
	अणु"PNP0c01", quirk_प्रणाली_pci_resourcesपूर्ण,
	अणु"PNP0c02", quirk_प्रणाली_pci_resourcesपूर्ण,
#अगर_घोषित CONFIG_AMD_NB
	अणु"PNP0c01", quirk_amd_mmconfig_areaपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI
	अणु"PNP0c02", quirk_पूर्णांकel_mchपूर्ण,
#पूर्ण_अगर
	अणु""पूर्ण
पूर्ण;

व्योम pnp_fixup_device(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_fixup *f;

	क्रम (f = pnp_fixups; *f->id; f++) अणु
		अगर (!compare_pnp_id(dev->id, f->id))
			जारी;
		pnp_dbg(&dev->dev, "%s: calling %pS\n", f->id,
			f->quirk_function);
		f->quirk_function(dev);
	पूर्ण
पूर्ण
