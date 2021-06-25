<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Bus Services, see include/linux/pci.h क्रम further explanation.
 *
 * Copyright 1993 -- 1997 Drew Eckhardt, Frederic Potter,
 * David Mosberger-Tang
 *
 * Copyright 1997 -- 2000 Martin Mares <mj@ucw.cz>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/init.h>
#समावेश <linux/msi.h>
#समावेश <linux/of.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/log2.h>
#समावेश <linux/logic_pपन.स>
#समावेश <linux/pm_wakeup.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/dma.h>
#समावेश <linux/aer.h>
#समावेश "pci.h"

DEFINE_MUTEX(pci_slot_mutex);

स्थिर अक्षर *pci_घातer_names[] = अणु
	"error", "D0", "D1", "D2", "D3hot", "D3cold", "unknown",
पूर्ण;
EXPORT_SYMBOL_GPL(pci_घातer_names);

पूर्णांक isa_dma_bridge_buggy;
EXPORT_SYMBOL(isa_dma_bridge_buggy);

पूर्णांक pci_pci_problems;
EXPORT_SYMBOL(pci_pci_problems);

अचिन्हित पूर्णांक pci_pm_d3hot_delay;

अटल व्योम pci_pme_list_scan(काष्ठा work_काष्ठा *work);

अटल LIST_HEAD(pci_pme_list);
अटल DEFINE_MUTEX(pci_pme_list_mutex);
अटल DECLARE_DELAYED_WORK(pci_pme_work, pci_pme_list_scan);

काष्ठा pci_pme_device अणु
	काष्ठा list_head list;
	काष्ठा pci_dev *dev;
पूर्ण;

#घोषणा PME_TIMEOUT 1000 /* How दीर्घ between PME checks */

अटल व्योम pci_dev_d3_sleep(काष्ठा pci_dev *dev)
अणु
	अचिन्हित पूर्णांक delay = dev->d3hot_delay;

	अगर (delay < pci_pm_d3hot_delay)
		delay = pci_pm_d3hot_delay;

	अगर (delay)
		msleep(delay);
पूर्ण

#अगर_घोषित CONFIG_PCI_DOMAINS
पूर्णांक pci_करोमुख्यs_supported = 1;
#पूर्ण_अगर

#घोषणा DEFAULT_CARDBUS_IO_SIZE		(256)
#घोषणा DEFAULT_CARDBUS_MEM_SIZE	(64*1024*1024)
/* pci=cbmemsize=nnM,cbiosize=nn can override this */
अचिन्हित दीर्घ pci_cardbus_io_size = DEFAULT_CARDBUS_IO_SIZE;
अचिन्हित दीर्घ pci_cardbus_mem_size = DEFAULT_CARDBUS_MEM_SIZE;

#घोषणा DEFAULT_HOTPLUG_IO_SIZE		(256)
#घोषणा DEFAULT_HOTPLUG_MMIO_SIZE	(2*1024*1024)
#घोषणा DEFAULT_HOTPLUG_MMIO_PREF_SIZE	(2*1024*1024)
/* hpiosize=nn can override this */
अचिन्हित दीर्घ pci_hotplug_io_size  = DEFAULT_HOTPLUG_IO_SIZE;
/*
 * pci=hpmmiosize=nnM overrides non-prefetchable MMIO size,
 * pci=hpmmioprefsize=nnM overrides prefetchable MMIO size;
 * pci=hpmemsize=nnM overrides both
 */
अचिन्हित दीर्घ pci_hotplug_mmio_size = DEFAULT_HOTPLUG_MMIO_SIZE;
अचिन्हित दीर्घ pci_hotplug_mmio_pref_size = DEFAULT_HOTPLUG_MMIO_PREF_SIZE;

#घोषणा DEFAULT_HOTPLUG_BUS_SIZE	1
अचिन्हित दीर्घ pci_hotplug_bus_size = DEFAULT_HOTPLUG_BUS_SIZE;


/* PCIe MPS/MRRS strategy; can be overridden by kernel command-line param */
#अगर_घोषित CONFIG_PCIE_BUS_TUNE_OFF
क्रमागत pcie_bus_config_types pcie_bus_config = PCIE_BUS_TUNE_OFF;
#या_अगर defined CONFIG_PCIE_BUS_SAFE
क्रमागत pcie_bus_config_types pcie_bus_config = PCIE_BUS_SAFE;
#या_अगर defined CONFIG_PCIE_BUS_PERFORMANCE
क्रमागत pcie_bus_config_types pcie_bus_config = PCIE_BUS_PERFORMANCE;
#या_अगर defined CONFIG_PCIE_BUS_PEER2PEER
क्रमागत pcie_bus_config_types pcie_bus_config = PCIE_BUS_PEER2PEER;
#अन्यथा
क्रमागत pcie_bus_config_types pcie_bus_config = PCIE_BUS_DEFAULT;
#पूर्ण_अगर

/*
 * The शेष CLS is used अगर arch didn't set CLS explicitly and not
 * all pci devices agree on the same value.  Arch can override either
 * the dfl or actual value as it sees fit.  Don't क्रमget this is
 * measured in 32-bit words, not bytes.
 */
u8 pci_dfl_cache_line_size = L1_CACHE_BYTES >> 2;
u8 pci_cache_line_size;

/*
 * If we set up a device क्रम bus mastering, we need to check the latency
 * समयr as certain BIOSes क्रमget to set it properly.
 */
अचिन्हित पूर्णांक pcibios_max_latency = 255;

/* If set, the PCIe ARI capability will not be used. */
अटल bool pcie_ari_disabled;

/* If set, the PCIe ATS capability will not be used. */
अटल bool pcie_ats_disabled;

/* If set, the PCI config space of each device is prपूर्णांकed during boot. */
bool pci_early_dump;

bool pci_ats_disabled(व्योम)
अणु
	वापस pcie_ats_disabled;
पूर्ण
EXPORT_SYMBOL_GPL(pci_ats_disabled);

/* Disable bridge_d3 क्रम all PCIe ports */
अटल bool pci_bridge_d3_disable;
/* Force bridge_d3 क्रम all PCIe ports */
अटल bool pci_bridge_d3_क्रमce;

अटल पूर्णांक __init pcie_port_pm_setup(अक्षर *str)
अणु
	अगर (!म_भेद(str, "off"))
		pci_bridge_d3_disable = true;
	अन्यथा अगर (!म_भेद(str, "force"))
		pci_bridge_d3_क्रमce = true;
	वापस 1;
पूर्ण
__setup("pcie_port_pm=", pcie_port_pm_setup);

/* Time to रुको after a reset क्रम device to become responsive */
#घोषणा PCIE_RESET_READY_POLL_MS 60000

/**
 * pci_bus_max_busnr - वापसs maximum PCI bus number of given bus' children
 * @bus: poपूर्णांकer to PCI bus काष्ठाure to search
 *
 * Given a PCI bus, वापसs the highest PCI bus number present in the set
 * including the given PCI bus and its list of child PCI buses.
 */
अचिन्हित अक्षर pci_bus_max_busnr(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_bus *पंचांगp;
	अचिन्हित अक्षर max, n;

	max = bus->busn_res.end;
	list_क्रम_each_entry(पंचांगp, &bus->children, node) अणु
		n = pci_bus_max_busnr(पंचांगp);
		अगर (n > max)
			max = n;
	पूर्ण
	वापस max;
पूर्ण
EXPORT_SYMBOL_GPL(pci_bus_max_busnr);

/**
 * pci_status_get_and_clear_errors - वापस and clear error bits in PCI_STATUS
 * @pdev: the PCI device
 *
 * Returns error bits set in PCI_STATUS and clears them.
 */
पूर्णांक pci_status_get_and_clear_errors(काष्ठा pci_dev *pdev)
अणु
	u16 status;
	पूर्णांक ret;

	ret = pci_पढ़ो_config_word(pdev, PCI_STATUS, &status);
	अगर (ret != PCIBIOS_SUCCESSFUL)
		वापस -EIO;

	status &= PCI_STATUS_ERROR_BITS;
	अगर (status)
		pci_ग_लिखो_config_word(pdev, PCI_STATUS, status);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(pci_status_get_and_clear_errors);

#अगर_घोषित CONFIG_HAS_IOMEM
व्योम __iomem *pci_ioremap_bar(काष्ठा pci_dev *pdev, पूर्णांक bar)
अणु
	काष्ठा resource *res = &pdev->resource[bar];

	/*
	 * Make sure the BAR is actually a memory resource, not an IO resource
	 */
	अगर (res->flags & IORESOURCE_UNSET || !(res->flags & IORESOURCE_MEM)) अणु
		pci_warn(pdev, "can't ioremap BAR %d: %pR\n", bar, res);
		वापस शून्य;
	पूर्ण
	वापस ioremap(res->start, resource_size(res));
पूर्ण
EXPORT_SYMBOL_GPL(pci_ioremap_bar);

व्योम __iomem *pci_ioremap_wc_bar(काष्ठा pci_dev *pdev, पूर्णांक bar)
अणु
	/*
	 * Make sure the BAR is actually a memory resource, not an IO resource
	 */
	अगर (!(pci_resource_flags(pdev, bar) & IORESOURCE_MEM)) अणु
		WARN_ON(1);
		वापस शून्य;
	पूर्ण
	वापस ioremap_wc(pci_resource_start(pdev, bar),
			  pci_resource_len(pdev, bar));
पूर्ण
EXPORT_SYMBOL_GPL(pci_ioremap_wc_bar);
#पूर्ण_अगर

/**
 * pci_dev_str_match_path - test अगर a path string matches a device
 * @dev: the PCI device to test
 * @path: string to match the device against
 * @endptr: poपूर्णांकer to the string after the match
 *
 * Test अगर a string (typically from a kernel parameter) क्रमmatted as a
 * path of device/function addresses matches a PCI device. The string must
 * be of the क्रमm:
 *
 *   [<करोमुख्य>:]<bus>:<device>.<func>[/<device>.<func>]*
 *
 * A path क्रम a device can be obtained using 'lspci -t'.  Using a path
 * is more robust against bus rक्रमागतbering than using only a single bus,
 * device and function address.
 *
 * Returns 1 अगर the string matches the device, 0 अगर it करोes not and
 * a negative error code अगर it fails to parse the string.
 */
अटल पूर्णांक pci_dev_str_match_path(काष्ठा pci_dev *dev, स्थिर अक्षर *path,
				  स्थिर अक्षर **endptr)
अणु
	पूर्णांक ret;
	पूर्णांक seg, bus, slot, func;
	अक्षर *wpath, *p;
	अक्षर end;

	*endptr = म_अक्षरnul(path, ';');

	wpath = kmemdup_nul(path, *endptr - path, GFP_KERNEL);
	अगर (!wpath)
		वापस -ENOMEM;

	जबतक (1) अणु
		p = म_खोजप(wpath, '/');
		अगर (!p)
			अवरोध;
		ret = माला_पूछो(p, "/%x.%x%c", &slot, &func, &end);
		अगर (ret != 2) अणु
			ret = -EINVAL;
			जाओ मुक्त_and_निकास;
		पूर्ण

		अगर (dev->devfn != PCI_DEVFN(slot, func)) अणु
			ret = 0;
			जाओ मुक्त_and_निकास;
		पूर्ण

		/*
		 * Note: we करोn't need to get a reference to the upstream
		 * bridge because we hold a reference to the top level
		 * device which should hold a reference to the bridge,
		 * and so on.
		 */
		dev = pci_upstream_bridge(dev);
		अगर (!dev) अणु
			ret = 0;
			जाओ मुक्त_and_निकास;
		पूर्ण

		*p = 0;
	पूर्ण

	ret = माला_पूछो(wpath, "%x:%x:%x.%x%c", &seg, &bus, &slot,
		     &func, &end);
	अगर (ret != 4) अणु
		seg = 0;
		ret = माला_पूछो(wpath, "%x:%x.%x%c", &bus, &slot, &func, &end);
		अगर (ret != 3) अणु
			ret = -EINVAL;
			जाओ मुक्त_and_निकास;
		पूर्ण
	पूर्ण

	ret = (seg == pci_करोमुख्य_nr(dev->bus) &&
	       bus == dev->bus->number &&
	       dev->devfn == PCI_DEVFN(slot, func));

मुक्त_and_निकास:
	kमुक्त(wpath);
	वापस ret;
पूर्ण

/**
 * pci_dev_str_match - test अगर a string matches a device
 * @dev: the PCI device to test
 * @p: string to match the device against
 * @endptr: poपूर्णांकer to the string after the match
 *
 * Test अगर a string (typically from a kernel parameter) matches a specअगरied
 * PCI device. The string may be of one of the following क्रमmats:
 *
 *   [<करोमुख्य>:]<bus>:<device>.<func>[/<device>.<func>]*
 *   pci:<venकरोr>:<device>[:<subvenकरोr>:<subdevice>]
 *
 * The first क्रमmat specअगरies a PCI bus/device/function address which
 * may change अगर new hardware is inserted, अगर motherboard firmware changes,
 * or due to changes caused in kernel parameters. If the करोमुख्य is
 * left unspecअगरied, it is taken to be 0.  In order to be robust against
 * bus rक्रमागतbering issues, a path of PCI device/function numbers may be used
 * to address the specअगरic device.  The path क्रम a device can be determined
 * through the use of 'lspci -t'.
 *
 * The second क्रमmat matches devices using IDs in the configuration
 * space which may match multiple devices in the प्रणाली. A value of 0
 * क्रम any field will match all devices. (Note: this dअगरfers from
 * in-kernel code that uses PCI_ANY_ID which is ~0; this is क्रम
 * legacy reasons and convenience so users करोn't have to specअगरy
 * FFFFFFFFs on the command line.)
 *
 * Returns 1 अगर the string matches the device, 0 अगर it करोes not and
 * a negative error code अगर the string cannot be parsed.
 */
अटल पूर्णांक pci_dev_str_match(काष्ठा pci_dev *dev, स्थिर अक्षर *p,
			     स्थिर अक्षर **endptr)
अणु
	पूर्णांक ret;
	पूर्णांक count;
	अचिन्हित लघु venकरोr, device, subप्रणाली_venकरोr, subप्रणाली_device;

	अगर (म_भेदन(p, "pci:", 4) == 0) अणु
		/* PCI venकरोr/device (subvenकरोr/subdevice) IDs are specअगरied */
		p += 4;
		ret = माला_पूछो(p, "%hx:%hx:%hx:%hx%n", &venकरोr, &device,
			     &subप्रणाली_venकरोr, &subप्रणाली_device, &count);
		अगर (ret != 4) अणु
			ret = माला_पूछो(p, "%hx:%hx%n", &venकरोr, &device, &count);
			अगर (ret != 2)
				वापस -EINVAL;

			subप्रणाली_venकरोr = 0;
			subप्रणाली_device = 0;
		पूर्ण

		p += count;

		अगर ((!venकरोr || venकरोr == dev->venकरोr) &&
		    (!device || device == dev->device) &&
		    (!subप्रणाली_venकरोr ||
			    subप्रणाली_venकरोr == dev->subप्रणाली_venकरोr) &&
		    (!subप्रणाली_device ||
			    subप्रणाली_device == dev->subप्रणाली_device))
			जाओ found;
	पूर्ण अन्यथा अणु
		/*
		 * PCI Bus, Device, Function IDs are specअगरied
		 * (optionally, may include a path of devfns following it)
		 */
		ret = pci_dev_str_match_path(dev, p, &p);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret)
			जाओ found;
	पूर्ण

	*endptr = p;
	वापस 0;

found:
	*endptr = p;
	वापस 1;
पूर्ण

अटल u8 __pci_find_next_cap_ttl(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				  u8 pos, पूर्णांक cap, पूर्णांक *ttl)
अणु
	u8 id;
	u16 ent;

	pci_bus_पढ़ो_config_byte(bus, devfn, pos, &pos);

	जबतक ((*ttl)--) अणु
		अगर (pos < 0x40)
			अवरोध;
		pos &= ~3;
		pci_bus_पढ़ो_config_word(bus, devfn, pos, &ent);

		id = ent & 0xff;
		अगर (id == 0xff)
			अवरोध;
		अगर (id == cap)
			वापस pos;
		pos = (ent >> 8);
	पूर्ण
	वापस 0;
पूर्ण

अटल u8 __pci_find_next_cap(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      u8 pos, पूर्णांक cap)
अणु
	पूर्णांक ttl = PCI_FIND_CAP_TTL;

	वापस __pci_find_next_cap_ttl(bus, devfn, pos, cap, &ttl);
पूर्ण

u8 pci_find_next_capability(काष्ठा pci_dev *dev, u8 pos, पूर्णांक cap)
अणु
	वापस __pci_find_next_cap(dev->bus, dev->devfn,
				   pos + PCI_CAP_LIST_NEXT, cap);
पूर्ण
EXPORT_SYMBOL_GPL(pci_find_next_capability);

अटल u8 __pci_bus_find_cap_start(काष्ठा pci_bus *bus,
				    अचिन्हित पूर्णांक devfn, u8 hdr_type)
अणु
	u16 status;

	pci_bus_पढ़ो_config_word(bus, devfn, PCI_STATUS, &status);
	अगर (!(status & PCI_STATUS_CAP_LIST))
		वापस 0;

	चयन (hdr_type) अणु
	हाल PCI_HEADER_TYPE_NORMAL:
	हाल PCI_HEADER_TYPE_BRIDGE:
		वापस PCI_CAPABILITY_LIST;
	हाल PCI_HEADER_TYPE_CARDBUS:
		वापस PCI_CB_CAPABILITY_LIST;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pci_find_capability - query क्रम devices' capabilities
 * @dev: PCI device to query
 * @cap: capability code
 *
 * Tell अगर a device supports a given PCI capability.
 * Returns the address of the requested capability काष्ठाure within the
 * device's PCI configuration space or 0 in हाल the device करोes not
 * support it.  Possible values क्रम @cap include:
 *
 *  %PCI_CAP_ID_PM           Power Management
 *  %PCI_CAP_ID_AGP          Accelerated Graphics Port
 *  %PCI_CAP_ID_VPD          Vital Product Data
 *  %PCI_CAP_ID_SLOTID       Slot Identअगरication
 *  %PCI_CAP_ID_MSI          Message Signalled Interrupts
 *  %PCI_CAP_ID_CHSWP        CompactPCI HotSwap
 *  %PCI_CAP_ID_PCIX         PCI-X
 *  %PCI_CAP_ID_EXP          PCI Express
 */
u8 pci_find_capability(काष्ठा pci_dev *dev, पूर्णांक cap)
अणु
	u8 pos;

	pos = __pci_bus_find_cap_start(dev->bus, dev->devfn, dev->hdr_type);
	अगर (pos)
		pos = __pci_find_next_cap(dev->bus, dev->devfn, pos, cap);

	वापस pos;
पूर्ण
EXPORT_SYMBOL(pci_find_capability);

/**
 * pci_bus_find_capability - query क्रम devices' capabilities
 * @bus: the PCI bus to query
 * @devfn: PCI device to query
 * @cap: capability code
 *
 * Like pci_find_capability() but works क्रम PCI devices that करो not have a
 * pci_dev काष्ठाure set up yet.
 *
 * Returns the address of the requested capability काष्ठाure within the
 * device's PCI configuration space or 0 in हाल the device करोes not
 * support it.
 */
u8 pci_bus_find_capability(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक cap)
अणु
	u8 hdr_type, pos;

	pci_bus_पढ़ो_config_byte(bus, devfn, PCI_HEADER_TYPE, &hdr_type);

	pos = __pci_bus_find_cap_start(bus, devfn, hdr_type & 0x7f);
	अगर (pos)
		pos = __pci_find_next_cap(bus, devfn, pos, cap);

	वापस pos;
पूर्ण
EXPORT_SYMBOL(pci_bus_find_capability);

/**
 * pci_find_next_ext_capability - Find an extended capability
 * @dev: PCI device to query
 * @start: address at which to start looking (0 to start at beginning of list)
 * @cap: capability code
 *
 * Returns the address of the next matching extended capability काष्ठाure
 * within the device's PCI configuration space or 0 अगर the device करोes
 * not support it.  Some capabilities can occur several बार, e.g., the
 * venकरोr-specअगरic capability, and this provides a way to find them all.
 */
u16 pci_find_next_ext_capability(काष्ठा pci_dev *dev, u16 start, पूर्णांक cap)
अणु
	u32 header;
	पूर्णांक ttl;
	u16 pos = PCI_CFG_SPACE_SIZE;

	/* minimum 8 bytes per capability */
	ttl = (PCI_CFG_SPACE_EXP_SIZE - PCI_CFG_SPACE_SIZE) / 8;

	अगर (dev->cfg_size <= PCI_CFG_SPACE_SIZE)
		वापस 0;

	अगर (start)
		pos = start;

	अगर (pci_पढ़ो_config_dword(dev, pos, &header) != PCIBIOS_SUCCESSFUL)
		वापस 0;

	/*
	 * If we have no capabilities, this is indicated by cap ID,
	 * cap version and next poपूर्णांकer all being 0.
	 */
	अगर (header == 0)
		वापस 0;

	जबतक (ttl-- > 0) अणु
		अगर (PCI_EXT_CAP_ID(header) == cap && pos != start)
			वापस pos;

		pos = PCI_EXT_CAP_NEXT(header);
		अगर (pos < PCI_CFG_SPACE_SIZE)
			अवरोध;

		अगर (pci_पढ़ो_config_dword(dev, pos, &header) != PCIBIOS_SUCCESSFUL)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_find_next_ext_capability);

/**
 * pci_find_ext_capability - Find an extended capability
 * @dev: PCI device to query
 * @cap: capability code
 *
 * Returns the address of the requested extended capability काष्ठाure
 * within the device's PCI configuration space or 0 अगर the device करोes
 * not support it.  Possible values क्रम @cap include:
 *
 *  %PCI_EXT_CAP_ID_ERR		Advanced Error Reporting
 *  %PCI_EXT_CAP_ID_VC		Virtual Channel
 *  %PCI_EXT_CAP_ID_DSN		Device Serial Number
 *  %PCI_EXT_CAP_ID_PWR		Power Budgeting
 */
u16 pci_find_ext_capability(काष्ठा pci_dev *dev, पूर्णांक cap)
अणु
	वापस pci_find_next_ext_capability(dev, 0, cap);
पूर्ण
EXPORT_SYMBOL_GPL(pci_find_ext_capability);

/**
 * pci_get_dsn - Read and वापस the 8-byte Device Serial Number
 * @dev: PCI device to query
 *
 * Looks up the PCI_EXT_CAP_ID_DSN and पढ़ोs the 8 bytes of the Device Serial
 * Number.
 *
 * Returns the DSN, or zero अगर the capability करोes not exist.
 */
u64 pci_get_dsn(काष्ठा pci_dev *dev)
अणु
	u32 dword;
	u64 dsn;
	पूर्णांक pos;

	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_DSN);
	अगर (!pos)
		वापस 0;

	/*
	 * The Device Serial Number is two dwords offset 4 bytes from the
	 * capability position. The specअगरication says that the first dword is
	 * the lower half, and the second dword is the upper half.
	 */
	pos += 4;
	pci_पढ़ो_config_dword(dev, pos, &dword);
	dsn = (u64)dword;
	pci_पढ़ो_config_dword(dev, pos + 4, &dword);
	dsn |= ((u64)dword) << 32;

	वापस dsn;
पूर्ण
EXPORT_SYMBOL_GPL(pci_get_dsn);

अटल u8 __pci_find_next_ht_cap(काष्ठा pci_dev *dev, u8 pos, पूर्णांक ht_cap)
अणु
	पूर्णांक rc, ttl = PCI_FIND_CAP_TTL;
	u8 cap, mask;

	अगर (ht_cap == HT_CAPTYPE_SLAVE || ht_cap == HT_CAPTYPE_HOST)
		mask = HT_3BIT_CAP_MASK;
	अन्यथा
		mask = HT_5BIT_CAP_MASK;

	pos = __pci_find_next_cap_ttl(dev->bus, dev->devfn, pos,
				      PCI_CAP_ID_HT, &ttl);
	जबतक (pos) अणु
		rc = pci_पढ़ो_config_byte(dev, pos + 3, &cap);
		अगर (rc != PCIBIOS_SUCCESSFUL)
			वापस 0;

		अगर ((cap & mask) == ht_cap)
			वापस pos;

		pos = __pci_find_next_cap_ttl(dev->bus, dev->devfn,
					      pos + PCI_CAP_LIST_NEXT,
					      PCI_CAP_ID_HT, &ttl);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pci_find_next_ht_capability - query a device's HyperTransport capabilities
 * @dev: PCI device to query
 * @pos: Position from which to जारी searching
 * @ht_cap: HyperTransport capability code
 *
 * To be used in conjunction with pci_find_ht_capability() to search क्रम
 * all capabilities matching @ht_cap. @pos should always be a value वापसed
 * from pci_find_ht_capability().
 *
 * NB. To be 100% safe against broken PCI devices, the caller should take
 * steps to aव्योम an infinite loop.
 */
u8 pci_find_next_ht_capability(काष्ठा pci_dev *dev, u8 pos, पूर्णांक ht_cap)
अणु
	वापस __pci_find_next_ht_cap(dev, pos + PCI_CAP_LIST_NEXT, ht_cap);
पूर्ण
EXPORT_SYMBOL_GPL(pci_find_next_ht_capability);

/**
 * pci_find_ht_capability - query a device's HyperTransport capabilities
 * @dev: PCI device to query
 * @ht_cap: HyperTransport capability code
 *
 * Tell अगर a device supports a given HyperTransport capability.
 * Returns an address within the device's PCI configuration space
 * or 0 in हाल the device करोes not support the request capability.
 * The address poपूर्णांकs to the PCI capability, of type PCI_CAP_ID_HT,
 * which has a HyperTransport capability matching @ht_cap.
 */
u8 pci_find_ht_capability(काष्ठा pci_dev *dev, पूर्णांक ht_cap)
अणु
	u8 pos;

	pos = __pci_bus_find_cap_start(dev->bus, dev->devfn, dev->hdr_type);
	अगर (pos)
		pos = __pci_find_next_ht_cap(dev, pos, ht_cap);

	वापस pos;
पूर्ण
EXPORT_SYMBOL_GPL(pci_find_ht_capability);

/**
 * pci_find_vsec_capability - Find a venकरोr-specअगरic extended capability
 * @dev: PCI device to query
 * @venकरोr: Venकरोr ID क्रम which capability is defined
 * @cap: Venकरोr-specअगरic capability ID
 *
 * If @dev has Venकरोr ID @venकरोr, search क्रम a VSEC capability with
 * VSEC ID @cap. If found, वापस the capability offset in
 * config space; otherwise वापस 0.
 */
u16 pci_find_vsec_capability(काष्ठा pci_dev *dev, u16 venकरोr, पूर्णांक cap)
अणु
	u16 vsec = 0;
	u32 header;

	अगर (venकरोr != dev->venकरोr)
		वापस 0;

	जबतक ((vsec = pci_find_next_ext_capability(dev, vsec,
						     PCI_EXT_CAP_ID_VNDR))) अणु
		अगर (pci_पढ़ो_config_dword(dev, vsec + PCI_VNDR_HEADER,
					  &header) == PCIBIOS_SUCCESSFUL &&
		    PCI_VNDR_HEADER_ID(header) == cap)
			वापस vsec;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_find_vsec_capability);

/**
 * pci_find_parent_resource - वापस resource region of parent bus of given
 *			      region
 * @dev: PCI device काष्ठाure contains resources to be searched
 * @res: child resource record क्रम which parent is sought
 *
 * For given resource region of given device, वापस the resource region of
 * parent bus the given region is contained in.
 */
काष्ठा resource *pci_find_parent_resource(स्थिर काष्ठा pci_dev *dev,
					  काष्ठा resource *res)
अणु
	स्थिर काष्ठा pci_bus *bus = dev->bus;
	काष्ठा resource *r;
	पूर्णांक i;

	pci_bus_क्रम_each_resource(bus, r, i) अणु
		अगर (!r)
			जारी;
		अगर (resource_contains(r, res)) अणु

			/*
			 * If the winकरोw is prefetchable but the BAR is
			 * not, the allocator made a mistake.
			 */
			अगर (r->flags & IORESOURCE_PREFETCH &&
			    !(res->flags & IORESOURCE_PREFETCH))
				वापस शून्य;

			/*
			 * If we're below a transparent bridge, there may
			 * be both a positively-decoded aperture and a
			 * subtractively-decoded region that contain the BAR.
			 * We want the positively-decoded one, so this depends
			 * on pci_bus_क्रम_each_resource() giving us those
			 * first.
			 */
			वापस r;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(pci_find_parent_resource);

/**
 * pci_find_resource - Return matching PCI device resource
 * @dev: PCI device to query
 * @res: Resource to look क्रम
 *
 * Goes over standard PCI resources (BARs) and checks अगर the given resource
 * is partially or fully contained in any of them. In that हाल the
 * matching resource is वापसed, %शून्य otherwise.
 */
काष्ठा resource *pci_find_resource(काष्ठा pci_dev *dev, काष्ठा resource *res)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		काष्ठा resource *r = &dev->resource[i];

		अगर (r->start && resource_contains(r, res))
			वापस r;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(pci_find_resource);

/**
 * pci_रुको_क्रम_pending - रुको क्रम @mask bit(s) to clear in status word @pos
 * @dev: the PCI device to operate on
 * @pos: config space offset of status word
 * @mask: mask of bit(s) to care about in status word
 *
 * Return 1 when mask bit(s) in status word clear, 0 otherwise.
 */
पूर्णांक pci_रुको_क्रम_pending(काष्ठा pci_dev *dev, पूर्णांक pos, u16 mask)
अणु
	पूर्णांक i;

	/* Wait क्रम Transaction Pending bit clean */
	क्रम (i = 0; i < 4; i++) अणु
		u16 status;
		अगर (i)
			msleep((1 << (i - 1)) * 100);

		pci_पढ़ो_config_word(dev, pos, &status);
		अगर (!(status & mask))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci_acs_enable;

/**
 * pci_request_acs - ask क्रम ACS to be enabled अगर supported
 */
व्योम pci_request_acs(व्योम)
अणु
	pci_acs_enable = 1;
पूर्ण

अटल स्थिर अक्षर *disable_acs_redir_param;

/**
 * pci_disable_acs_redir - disable ACS redirect capabilities
 * @dev: the PCI device
 *
 * For only devices specअगरied in the disable_acs_redir parameter.
 */
अटल व्योम pci_disable_acs_redir(काष्ठा pci_dev *dev)
अणु
	पूर्णांक ret = 0;
	स्थिर अक्षर *p;
	पूर्णांक pos;
	u16 ctrl;

	अगर (!disable_acs_redir_param)
		वापस;

	p = disable_acs_redir_param;
	जबतक (*p) अणु
		ret = pci_dev_str_match(dev, p, &p);
		अगर (ret < 0) अणु
			pr_info_once("PCI: Can't parse disable_acs_redir parameter: %s\n",
				     disable_acs_redir_param);

			अवरोध;
		पूर्ण अन्यथा अगर (ret == 1) अणु
			/* Found a match */
			अवरोध;
		पूर्ण

		अगर (*p != ';' && *p != ',') अणु
			/* End of param or invalid क्रमmat */
			अवरोध;
		पूर्ण
		p++;
	पूर्ण

	अगर (ret != 1)
		वापस;

	अगर (!pci_dev_specअगरic_disable_acs_redir(dev))
		वापस;

	pos = dev->acs_cap;
	अगर (!pos) अणु
		pci_warn(dev, "cannot disable ACS redirect for this hardware as it does not have ACS capabilities\n");
		वापस;
	पूर्ण

	pci_पढ़ो_config_word(dev, pos + PCI_ACS_CTRL, &ctrl);

	/* P2P Request & Completion Redirect */
	ctrl &= ~(PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_EC);

	pci_ग_लिखो_config_word(dev, pos + PCI_ACS_CTRL, ctrl);

	pci_info(dev, "disabled ACS redirect\n");
पूर्ण

/**
 * pci_std_enable_acs - enable ACS on devices using standard ACS capabilities
 * @dev: the PCI device
 */
अटल व्योम pci_std_enable_acs(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pos;
	u16 cap;
	u16 ctrl;

	pos = dev->acs_cap;
	अगर (!pos)
		वापस;

	pci_पढ़ो_config_word(dev, pos + PCI_ACS_CAP, &cap);
	pci_पढ़ो_config_word(dev, pos + PCI_ACS_CTRL, &ctrl);

	/* Source Validation */
	ctrl |= (cap & PCI_ACS_SV);

	/* P2P Request Redirect */
	ctrl |= (cap & PCI_ACS_RR);

	/* P2P Completion Redirect */
	ctrl |= (cap & PCI_ACS_CR);

	/* Upstream Forwarding */
	ctrl |= (cap & PCI_ACS_UF);

	/* Enable Translation Blocking क्रम बाह्यal devices */
	अगर (dev->बाह्यal_facing || dev->untrusted)
		ctrl |= (cap & PCI_ACS_TB);

	pci_ग_लिखो_config_word(dev, pos + PCI_ACS_CTRL, ctrl);
पूर्ण

/**
 * pci_enable_acs - enable ACS अगर hardware support it
 * @dev: the PCI device
 */
अटल व्योम pci_enable_acs(काष्ठा pci_dev *dev)
अणु
	अगर (!pci_acs_enable)
		जाओ disable_acs_redir;

	अगर (!pci_dev_specअगरic_enable_acs(dev))
		जाओ disable_acs_redir;

	pci_std_enable_acs(dev);

disable_acs_redir:
	/*
	 * Note: pci_disable_acs_redir() must be called even अगर ACS was not
	 * enabled by the kernel because it may have been enabled by
	 * platक्रमm firmware.  So अगर we are told to disable it, we should
	 * always disable it after setting the kernel's शेष
	 * preferences.
	 */
	pci_disable_acs_redir(dev);
पूर्ण

/**
 * pci_restore_bars - restore a device's BAR values (e.g. after wake-up)
 * @dev: PCI device to have its BARs restored
 *
 * Restore the BAR values क्रम a given device, so as to make it
 * accessible by its driver.
 */
अटल व्योम pci_restore_bars(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PCI_BRIDGE_RESOURCES; i++)
		pci_update_resource(dev, i);
पूर्ण

अटल स्थिर काष्ठा pci_platक्रमm_pm_ops *pci_platक्रमm_pm;

पूर्णांक pci_set_platक्रमm_pm(स्थिर काष्ठा pci_platक्रमm_pm_ops *ops)
अणु
	अगर (!ops->is_manageable || !ops->set_state  || !ops->get_state ||
	    !ops->choose_state  || !ops->set_wakeup || !ops->need_resume)
		वापस -EINVAL;
	pci_platक्रमm_pm = ops;
	वापस 0;
पूर्ण

अटल अंतरभूत bool platक्रमm_pci_घातer_manageable(काष्ठा pci_dev *dev)
अणु
	वापस pci_platक्रमm_pm ? pci_platक्रमm_pm->is_manageable(dev) : false;
पूर्ण

अटल अंतरभूत पूर्णांक platक्रमm_pci_set_घातer_state(काष्ठा pci_dev *dev,
					       pci_घातer_t t)
अणु
	वापस pci_platक्रमm_pm ? pci_platक्रमm_pm->set_state(dev, t) : -ENOSYS;
पूर्ण

अटल अंतरभूत pci_घातer_t platक्रमm_pci_get_घातer_state(काष्ठा pci_dev *dev)
अणु
	वापस pci_platक्रमm_pm ? pci_platक्रमm_pm->get_state(dev) : PCI_UNKNOWN;
पूर्ण

अटल अंतरभूत व्योम platक्रमm_pci_refresh_घातer_state(काष्ठा pci_dev *dev)
अणु
	अगर (pci_platक्रमm_pm && pci_platक्रमm_pm->refresh_state)
		pci_platक्रमm_pm->refresh_state(dev);
पूर्ण

अटल अंतरभूत pci_घातer_t platक्रमm_pci_choose_state(काष्ठा pci_dev *dev)
अणु
	वापस pci_platक्रमm_pm ?
			pci_platक्रमm_pm->choose_state(dev) : PCI_POWER_ERROR;
पूर्ण

अटल अंतरभूत पूर्णांक platक्रमm_pci_set_wakeup(काष्ठा pci_dev *dev, bool enable)
अणु
	वापस pci_platक्रमm_pm ?
			pci_platक्रमm_pm->set_wakeup(dev, enable) : -ENODEV;
पूर्ण

अटल अंतरभूत bool platक्रमm_pci_need_resume(काष्ठा pci_dev *dev)
अणु
	वापस pci_platक्रमm_pm ? pci_platक्रमm_pm->need_resume(dev) : false;
पूर्ण

अटल अंतरभूत bool platक्रमm_pci_bridge_d3(काष्ठा pci_dev *dev)
अणु
	अगर (pci_platक्रमm_pm && pci_platक्रमm_pm->bridge_d3)
		वापस pci_platक्रमm_pm->bridge_d3(dev);
	वापस false;
पूर्ण

/**
 * pci_raw_set_घातer_state - Use PCI PM रेजिस्टरs to set the घातer state of
 *			     given PCI device
 * @dev: PCI device to handle.
 * @state: PCI घातer state (D0, D1, D2, D3hot) to put the device पूर्णांकo.
 *
 * RETURN VALUE:
 * -EINVAL अगर the requested state is invalid.
 * -EIO अगर device करोes not support PCI PM or its PM capabilities रेजिस्टर has a
 * wrong version, or device करोesn't support the requested state.
 * 0 अगर device alपढ़ोy is in the requested state.
 * 0 अगर device's घातer state has been successfully changed.
 */
अटल पूर्णांक pci_raw_set_घातer_state(काष्ठा pci_dev *dev, pci_घातer_t state)
अणु
	u16 pmcsr;
	bool need_restore = false;

	/* Check अगर we're alपढ़ोy there */
	अगर (dev->current_state == state)
		वापस 0;

	अगर (!dev->pm_cap)
		वापस -EIO;

	अगर (state < PCI_D0 || state > PCI_D3hot)
		वापस -EINVAL;

	/*
	 * Validate transition: We can enter D0 from any state, but अगर
	 * we're alपढ़ोy in a low-घातer state, we can only go deeper.  E.g.,
	 * we can go from D1 to D3, but we can't go directly from D3 to D1;
	 * we'd have to go from D3 to D0, then to D1.
	 */
	अगर (state != PCI_D0 && dev->current_state <= PCI_D3cold
	    && dev->current_state > state) अणु
		pci_err(dev, "invalid power transition (from %s to %s)\n",
			pci_घातer_name(dev->current_state),
			pci_घातer_name(state));
		वापस -EINVAL;
	पूर्ण

	/* Check अगर this device supports the desired state */
	अगर ((state == PCI_D1 && !dev->d1_support)
	   || (state == PCI_D2 && !dev->d2_support))
		वापस -EIO;

	pci_पढ़ो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pmcsr);
	अगर (pmcsr == (u16) ~0) अणु
		pci_err(dev, "can't change power state from %s to %s (config space inaccessible)\n",
			pci_घातer_name(dev->current_state),
			pci_घातer_name(state));
		वापस -EIO;
	पूर्ण

	/*
	 * If we're (effectively) in D3, क्रमce entire word to 0.
	 * This करोesn't affect PME_Status, disables PME_En, and
	 * sets PowerState to 0.
	 */
	चयन (dev->current_state) अणु
	हाल PCI_D0:
	हाल PCI_D1:
	हाल PCI_D2:
		pmcsr &= ~PCI_PM_CTRL_STATE_MASK;
		pmcsr |= state;
		अवरोध;
	हाल PCI_D3hot:
	हाल PCI_D3cold:
	हाल PCI_UNKNOWN: /* Boot-up */
		अगर ((pmcsr & PCI_PM_CTRL_STATE_MASK) == PCI_D3hot
		 && !(pmcsr & PCI_PM_CTRL_NO_SOFT_RESET))
			need_restore = true;
		fallthrough;	/* क्रमce to D0 */
	शेष:
		pmcsr = 0;
		अवरोध;
	पूर्ण

	/* Enter specअगरied state */
	pci_ग_लिखो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, pmcsr);

	/*
	 * Mandatory घातer management transition delays; see PCI PM 1.1
	 * 5.6.1 table 18
	 */
	अगर (state == PCI_D3hot || dev->current_state == PCI_D3hot)
		pci_dev_d3_sleep(dev);
	अन्यथा अगर (state == PCI_D2 || dev->current_state == PCI_D2)
		udelay(PCI_PM_D2_DELAY);

	pci_पढ़ो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pmcsr);
	dev->current_state = (pmcsr & PCI_PM_CTRL_STATE_MASK);
	अगर (dev->current_state != state)
		pci_info_ratelimited(dev, "refused to change power state from %s to %s\n",
			 pci_घातer_name(dev->current_state),
			 pci_घातer_name(state));

	/*
	 * According to section 5.4.1 of the "PCI BUS POWER MANAGEMENT
	 * INTERFACE SPECIFICATION, REV. 1.2", a device transitioning
	 * from D3hot to D0 _may_ perक्रमm an पूर्णांकernal reset, thereby
	 * going to "D0 Uninitialized" rather than "D0 Initialized".
	 * For example, at least some versions of the 3c905B and the
	 * 3c556B exhibit this behaviour.
	 *
	 * At least some laptop BIOSen (e.g. the Thinkpad T21) leave
	 * devices in a D3hot state at boot.  Consequently, we need to
	 * restore at least the BARs so that the device will be
	 * accessible to its driver.
	 */
	अगर (need_restore)
		pci_restore_bars(dev);

	अगर (dev->bus->self)
		pcie_aspm_pm_state_change(dev->bus->self);

	वापस 0;
पूर्ण

/**
 * pci_update_current_state - Read घातer state of given device and cache it
 * @dev: PCI device to handle.
 * @state: State to cache in हाल the device करोesn't have the PM capability
 *
 * The घातer state is पढ़ो from the PMCSR रेजिस्टर, which however is
 * inaccessible in D3cold.  The platक्रमm firmware is thereक्रमe queried first
 * to detect accessibility of the रेजिस्टर.  In हाल the platक्रमm firmware
 * reports an incorrect state or the device isn't घातer manageable by the
 * platक्रमm at all, we try to detect D3cold by testing accessibility of the
 * venकरोr ID in config space.
 */
व्योम pci_update_current_state(काष्ठा pci_dev *dev, pci_घातer_t state)
अणु
	अगर (platक्रमm_pci_get_घातer_state(dev) == PCI_D3cold ||
	    !pci_device_is_present(dev)) अणु
		dev->current_state = PCI_D3cold;
	पूर्ण अन्यथा अगर (dev->pm_cap) अणु
		u16 pmcsr;

		pci_पढ़ो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pmcsr);
		dev->current_state = (pmcsr & PCI_PM_CTRL_STATE_MASK);
	पूर्ण अन्यथा अणु
		dev->current_state = state;
	पूर्ण
पूर्ण

/**
 * pci_refresh_घातer_state - Refresh the given device's घातer state data
 * @dev: Target PCI device.
 *
 * Ask the platक्रमm to refresh the devices घातer state inक्रमmation and invoke
 * pci_update_current_state() to update its current PCI घातer state.
 */
व्योम pci_refresh_घातer_state(काष्ठा pci_dev *dev)
अणु
	अगर (platक्रमm_pci_घातer_manageable(dev))
		platक्रमm_pci_refresh_घातer_state(dev);

	pci_update_current_state(dev, dev->current_state);
पूर्ण

/**
 * pci_platक्रमm_घातer_transition - Use platक्रमm to change device घातer state
 * @dev: PCI device to handle.
 * @state: State to put the device पूर्णांकo.
 */
पूर्णांक pci_platक्रमm_घातer_transition(काष्ठा pci_dev *dev, pci_घातer_t state)
अणु
	पूर्णांक error;

	अगर (platक्रमm_pci_घातer_manageable(dev)) अणु
		error = platक्रमm_pci_set_घातer_state(dev, state);
		अगर (!error)
			pci_update_current_state(dev, state);
	पूर्ण अन्यथा
		error = -ENODEV;

	अगर (error && !dev->pm_cap) /* Fall back to PCI_D0 */
		dev->current_state = PCI_D0;

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(pci_platक्रमm_घातer_transition);

अटल पूर्णांक pci_resume_one(काष्ठा pci_dev *pci_dev, व्योम *ign)
अणु
	pm_request_resume(&pci_dev->dev);
	वापस 0;
पूर्ण

/**
 * pci_resume_bus - Walk given bus and runसमय resume devices on it
 * @bus: Top bus of the subtree to walk.
 */
व्योम pci_resume_bus(काष्ठा pci_bus *bus)
अणु
	अगर (bus)
		pci_walk_bus(bus, pci_resume_one, शून्य);
पूर्ण

अटल पूर्णांक pci_dev_रुको(काष्ठा pci_dev *dev, अक्षर *reset_type, पूर्णांक समयout)
अणु
	पूर्णांक delay = 1;
	u32 id;

	/*
	 * After reset, the device should not silently discard config
	 * requests, but it may still indicate that it needs more समय by
	 * responding to them with CRS completions.  The Root Port will
	 * generally synthesize ~0 data to complete the पढ़ो (except when
	 * CRS SV is enabled and the पढ़ो was क्रम the Venकरोr ID; in that
	 * हाल it synthesizes 0x0001 data).
	 *
	 * Wait क्रम the device to वापस a non-CRS completion.  Read the
	 * Command रेजिस्टर instead of Venकरोr ID so we करोn't have to
	 * contend with the CRS SV value.
	 */
	pci_पढ़ो_config_dword(dev, PCI_COMMAND, &id);
	जबतक (id == ~0) अणु
		अगर (delay > समयout) अणु
			pci_warn(dev, "not ready %dms after %s; giving up\n",
				 delay - 1, reset_type);
			वापस -ENOTTY;
		पूर्ण

		अगर (delay > 1000)
			pci_info(dev, "not ready %dms after %s; waiting\n",
				 delay - 1, reset_type);

		msleep(delay);
		delay *= 2;
		pci_पढ़ो_config_dword(dev, PCI_COMMAND, &id);
	पूर्ण

	अगर (delay > 1000)
		pci_info(dev, "ready %dms after %s\n", delay - 1,
			 reset_type);

	वापस 0;
पूर्ण

/**
 * pci_घातer_up - Put the given device पूर्णांकo D0
 * @dev: PCI device to घातer up
 */
पूर्णांक pci_घातer_up(काष्ठा pci_dev *dev)
अणु
	pci_platक्रमm_घातer_transition(dev, PCI_D0);

	/*
	 * Mandatory घातer management transition delays are handled in
	 * pci_pm_resume_noirq() and pci_pm_runसमय_resume() of the
	 * corresponding bridge.
	 */
	अगर (dev->runसमय_d3cold) अणु
		/*
		 * When घातering on a bridge from D3cold, the whole hierarchy
		 * may be घातered on पूर्णांकo D0uninitialized state, resume them to
		 * give them a chance to suspend again
		 */
		pci_resume_bus(dev->subordinate);
	पूर्ण

	वापस pci_raw_set_घातer_state(dev, PCI_D0);
पूर्ण

/**
 * __pci_dev_set_current_state - Set current state of a PCI device
 * @dev: Device to handle
 * @data: poपूर्णांकer to state to be set
 */
अटल पूर्णांक __pci_dev_set_current_state(काष्ठा pci_dev *dev, व्योम *data)
अणु
	pci_घातer_t state = *(pci_घातer_t *)data;

	dev->current_state = state;
	वापस 0;
पूर्ण

/**
 * pci_bus_set_current_state - Walk given bus and set current state of devices
 * @bus: Top bus of the subtree to walk.
 * @state: state to be set
 */
व्योम pci_bus_set_current_state(काष्ठा pci_bus *bus, pci_घातer_t state)
अणु
	अगर (bus)
		pci_walk_bus(bus, __pci_dev_set_current_state, &state);
पूर्ण

/**
 * pci_set_घातer_state - Set the घातer state of a PCI device
 * @dev: PCI device to handle.
 * @state: PCI घातer state (D0, D1, D2, D3hot) to put the device पूर्णांकo.
 *
 * Transition a device to a new घातer state, using the platक्रमm firmware and/or
 * the device's PCI PM रेजिस्टरs.
 *
 * RETURN VALUE:
 * -EINVAL अगर the requested state is invalid.
 * -EIO अगर device करोes not support PCI PM or its PM capabilities रेजिस्टर has a
 * wrong version, or device करोesn't support the requested state.
 * 0 अगर the transition is to D1 or D2 but D1 and D2 are not supported.
 * 0 अगर device alपढ़ोy is in the requested state.
 * 0 अगर the transition is to D3 but D3 is not supported.
 * 0 अगर device's घातer state has been successfully changed.
 */
पूर्णांक pci_set_घातer_state(काष्ठा pci_dev *dev, pci_घातer_t state)
अणु
	पूर्णांक error;

	/* Bound the state we're entering */
	अगर (state > PCI_D3cold)
		state = PCI_D3cold;
	अन्यथा अगर (state < PCI_D0)
		state = PCI_D0;
	अन्यथा अगर ((state == PCI_D1 || state == PCI_D2) && pci_no_d1d2(dev))

		/*
		 * If the device or the parent bridge करो not support PCI
		 * PM, ignore the request अगर we're करोing anything other
		 * than putting it पूर्णांकo D0 (which would only happen on
		 * boot).
		 */
		वापस 0;

	/* Check अगर we're alपढ़ोy there */
	अगर (dev->current_state == state)
		वापस 0;

	अगर (state == PCI_D0)
		वापस pci_घातer_up(dev);

	/*
	 * This device is quirked not to be put पूर्णांकo D3, so करोn't put it in
	 * D3
	 */
	अगर (state >= PCI_D3hot && (dev->dev_flags & PCI_DEV_FLAGS_NO_D3))
		वापस 0;

	/*
	 * To put device in D3cold, we put device पूर्णांकo D3hot in native
	 * way, then put device पूर्णांकo D3cold with platक्रमm ops
	 */
	error = pci_raw_set_घातer_state(dev, state > PCI_D3hot ?
					PCI_D3hot : state);

	अगर (pci_platक्रमm_घातer_transition(dev, state))
		वापस error;

	/* Powering off a bridge may घातer off the whole hierarchy */
	अगर (state == PCI_D3cold)
		pci_bus_set_current_state(dev->subordinate, PCI_D3cold);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pci_set_घातer_state);

/**
 * pci_choose_state - Choose the घातer state of a PCI device
 * @dev: PCI device to be suspended
 * @state: target sleep state क्रम the whole प्रणाली. This is the value
 *	   that is passed to suspend() function.
 *
 * Returns PCI घातer state suitable क्रम given device and given प्रणाली
 * message.
 */
pci_घातer_t pci_choose_state(काष्ठा pci_dev *dev, pm_message_t state)
अणु
	pci_घातer_t ret;

	अगर (!dev->pm_cap)
		वापस PCI_D0;

	ret = platक्रमm_pci_choose_state(dev);
	अगर (ret != PCI_POWER_ERROR)
		वापस ret;

	चयन (state.event) अणु
	हाल PM_EVENT_ON:
		वापस PCI_D0;
	हाल PM_EVENT_FREEZE:
	हाल PM_EVENT_PRETHAW:
		/* REVISIT both मुक्तze and pre-thaw "should" use D0 */
	हाल PM_EVENT_SUSPEND:
	हाल PM_EVENT_HIBERNATE:
		वापस PCI_D3hot;
	शेष:
		pci_info(dev, "unrecognized suspend event %d\n",
			 state.event);
		BUG();
	पूर्ण
	वापस PCI_D0;
पूर्ण
EXPORT_SYMBOL(pci_choose_state);

#घोषणा PCI_EXP_SAVE_REGS	7

अटल काष्ठा pci_cap_saved_state *_pci_find_saved_cap(काष्ठा pci_dev *pci_dev,
						       u16 cap, bool extended)
अणु
	काष्ठा pci_cap_saved_state *पंचांगp;

	hlist_क्रम_each_entry(पंचांगp, &pci_dev->saved_cap_space, next) अणु
		अगर (पंचांगp->cap.cap_extended == extended && पंचांगp->cap.cap_nr == cap)
			वापस पंचांगp;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा pci_cap_saved_state *pci_find_saved_cap(काष्ठा pci_dev *dev, अक्षर cap)
अणु
	वापस _pci_find_saved_cap(dev, cap, false);
पूर्ण

काष्ठा pci_cap_saved_state *pci_find_saved_ext_cap(काष्ठा pci_dev *dev, u16 cap)
अणु
	वापस _pci_find_saved_cap(dev, cap, true);
पूर्ण

अटल पूर्णांक pci_save_pcie_state(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i = 0;
	काष्ठा pci_cap_saved_state *save_state;
	u16 *cap;

	अगर (!pci_is_pcie(dev))
		वापस 0;

	save_state = pci_find_saved_cap(dev, PCI_CAP_ID_EXP);
	अगर (!save_state) अणु
		pci_err(dev, "buffer not found in %s\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	cap = (u16 *)&save_state->cap.data[0];
	pcie_capability_पढ़ो_word(dev, PCI_EXP_DEVCTL, &cap[i++]);
	pcie_capability_पढ़ो_word(dev, PCI_EXP_LNKCTL, &cap[i++]);
	pcie_capability_पढ़ो_word(dev, PCI_EXP_SLTCTL, &cap[i++]);
	pcie_capability_पढ़ो_word(dev, PCI_EXP_RTCTL,  &cap[i++]);
	pcie_capability_पढ़ो_word(dev, PCI_EXP_DEVCTL2, &cap[i++]);
	pcie_capability_पढ़ो_word(dev, PCI_EXP_LNKCTL2, &cap[i++]);
	pcie_capability_पढ़ो_word(dev, PCI_EXP_SLTCTL2, &cap[i++]);

	वापस 0;
पूर्ण

अटल व्योम pci_restore_pcie_state(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i = 0;
	काष्ठा pci_cap_saved_state *save_state;
	u16 *cap;

	save_state = pci_find_saved_cap(dev, PCI_CAP_ID_EXP);
	अगर (!save_state)
		वापस;

	cap = (u16 *)&save_state->cap.data[0];
	pcie_capability_ग_लिखो_word(dev, PCI_EXP_DEVCTL, cap[i++]);
	pcie_capability_ग_लिखो_word(dev, PCI_EXP_LNKCTL, cap[i++]);
	pcie_capability_ग_लिखो_word(dev, PCI_EXP_SLTCTL, cap[i++]);
	pcie_capability_ग_लिखो_word(dev, PCI_EXP_RTCTL, cap[i++]);
	pcie_capability_ग_लिखो_word(dev, PCI_EXP_DEVCTL2, cap[i++]);
	pcie_capability_ग_लिखो_word(dev, PCI_EXP_LNKCTL2, cap[i++]);
	pcie_capability_ग_लिखो_word(dev, PCI_EXP_SLTCTL2, cap[i++]);
पूर्ण

अटल पूर्णांक pci_save_pcix_state(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pos;
	काष्ठा pci_cap_saved_state *save_state;

	pos = pci_find_capability(dev, PCI_CAP_ID_PCIX);
	अगर (!pos)
		वापस 0;

	save_state = pci_find_saved_cap(dev, PCI_CAP_ID_PCIX);
	अगर (!save_state) अणु
		pci_err(dev, "buffer not found in %s\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	pci_पढ़ो_config_word(dev, pos + PCI_X_CMD,
			     (u16 *)save_state->cap.data);

	वापस 0;
पूर्ण

अटल व्योम pci_restore_pcix_state(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i = 0, pos;
	काष्ठा pci_cap_saved_state *save_state;
	u16 *cap;

	save_state = pci_find_saved_cap(dev, PCI_CAP_ID_PCIX);
	pos = pci_find_capability(dev, PCI_CAP_ID_PCIX);
	अगर (!save_state || !pos)
		वापस;
	cap = (u16 *)&save_state->cap.data[0];

	pci_ग_लिखो_config_word(dev, pos + PCI_X_CMD, cap[i++]);
पूर्ण

अटल व्योम pci_save_ltr_state(काष्ठा pci_dev *dev)
अणु
	पूर्णांक ltr;
	काष्ठा pci_cap_saved_state *save_state;
	u16 *cap;

	अगर (!pci_is_pcie(dev))
		वापस;

	ltr = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_LTR);
	अगर (!ltr)
		वापस;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_LTR);
	अगर (!save_state) अणु
		pci_err(dev, "no suspend buffer for LTR; ASPM issues possible after resume\n");
		वापस;
	पूर्ण

	cap = (u16 *)&save_state->cap.data[0];
	pci_पढ़ो_config_word(dev, ltr + PCI_LTR_MAX_SNOOP_LAT, cap++);
	pci_पढ़ो_config_word(dev, ltr + PCI_LTR_MAX_NOSNOOP_LAT, cap++);
पूर्ण

अटल व्योम pci_restore_ltr_state(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_cap_saved_state *save_state;
	पूर्णांक ltr;
	u16 *cap;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_LTR);
	ltr = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_LTR);
	अगर (!save_state || !ltr)
		वापस;

	cap = (u16 *)&save_state->cap.data[0];
	pci_ग_लिखो_config_word(dev, ltr + PCI_LTR_MAX_SNOOP_LAT, *cap++);
	pci_ग_लिखो_config_word(dev, ltr + PCI_LTR_MAX_NOSNOOP_LAT, *cap++);
पूर्ण

/**
 * pci_save_state - save the PCI configuration space of a device beक्रमe
 *		    suspending
 * @dev: PCI device that we're dealing with
 */
पूर्णांक pci_save_state(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;
	/* XXX: 100% dword access ok here? */
	क्रम (i = 0; i < 16; i++) अणु
		pci_पढ़ो_config_dword(dev, i * 4, &dev->saved_config_space[i]);
		pci_dbg(dev, "saving config space at offset %#x (reading %#x)\n",
			i * 4, dev->saved_config_space[i]);
	पूर्ण
	dev->state_saved = true;

	i = pci_save_pcie_state(dev);
	अगर (i != 0)
		वापस i;

	i = pci_save_pcix_state(dev);
	अगर (i != 0)
		वापस i;

	pci_save_ltr_state(dev);
	pci_save_dpc_state(dev);
	pci_save_aer_state(dev);
	pci_save_pपंचांग_state(dev);
	वापस pci_save_vc_state(dev);
पूर्ण
EXPORT_SYMBOL(pci_save_state);

अटल व्योम pci_restore_config_dword(काष्ठा pci_dev *pdev, पूर्णांक offset,
				     u32 saved_val, पूर्णांक retry, bool क्रमce)
अणु
	u32 val;

	pci_पढ़ो_config_dword(pdev, offset, &val);
	अगर (!क्रमce && val == saved_val)
		वापस;

	क्रम (;;) अणु
		pci_dbg(pdev, "restoring config space at offset %#x (was %#x, writing %#x)\n",
			offset, val, saved_val);
		pci_ग_लिखो_config_dword(pdev, offset, saved_val);
		अगर (retry-- <= 0)
			वापस;

		pci_पढ़ो_config_dword(pdev, offset, &val);
		अगर (val == saved_val)
			वापस;

		mdelay(1);
	पूर्ण
पूर्ण

अटल व्योम pci_restore_config_space_range(काष्ठा pci_dev *pdev,
					   पूर्णांक start, पूर्णांक end, पूर्णांक retry,
					   bool क्रमce)
अणु
	पूर्णांक index;

	क्रम (index = end; index >= start; index--)
		pci_restore_config_dword(pdev, 4 * index,
					 pdev->saved_config_space[index],
					 retry, क्रमce);
पूर्ण

अटल व्योम pci_restore_config_space(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->hdr_type == PCI_HEADER_TYPE_NORMAL) अणु
		pci_restore_config_space_range(pdev, 10, 15, 0, false);
		/* Restore BARs beक्रमe the command रेजिस्टर. */
		pci_restore_config_space_range(pdev, 4, 9, 10, false);
		pci_restore_config_space_range(pdev, 0, 3, 0, false);
	पूर्ण अन्यथा अगर (pdev->hdr_type == PCI_HEADER_TYPE_BRIDGE) अणु
		pci_restore_config_space_range(pdev, 12, 15, 0, false);

		/*
		 * Force rewriting of prefetch रेजिस्टरs to aव्योम S3 resume
		 * issues on Intel PCI bridges that occur when these
		 * रेजिस्टरs are not explicitly written.
		 */
		pci_restore_config_space_range(pdev, 9, 11, 0, true);
		pci_restore_config_space_range(pdev, 0, 8, 0, false);
	पूर्ण अन्यथा अणु
		pci_restore_config_space_range(pdev, 0, 15, 0, false);
	पूर्ण
पूर्ण

अटल व्योम pci_restore_rebar_state(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित पूर्णांक pos, nbars, i;
	u32 ctrl;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_REBAR);
	अगर (!pos)
		वापस;

	pci_पढ़ो_config_dword(pdev, pos + PCI_REBAR_CTRL, &ctrl);
	nbars = (ctrl & PCI_REBAR_CTRL_NBAR_MASK) >>
		    PCI_REBAR_CTRL_NBAR_SHIFT;

	क्रम (i = 0; i < nbars; i++, pos += 8) अणु
		काष्ठा resource *res;
		पूर्णांक bar_idx, size;

		pci_पढ़ो_config_dword(pdev, pos + PCI_REBAR_CTRL, &ctrl);
		bar_idx = ctrl & PCI_REBAR_CTRL_BAR_IDX;
		res = pdev->resource + bar_idx;
		size = pci_rebar_bytes_to_size(resource_size(res));
		ctrl &= ~PCI_REBAR_CTRL_BAR_SIZE;
		ctrl |= size << PCI_REBAR_CTRL_BAR_SHIFT;
		pci_ग_लिखो_config_dword(pdev, pos + PCI_REBAR_CTRL, ctrl);
	पूर्ण
पूर्ण

/**
 * pci_restore_state - Restore the saved state of a PCI device
 * @dev: PCI device that we're dealing with
 */
व्योम pci_restore_state(काष्ठा pci_dev *dev)
अणु
	अगर (!dev->state_saved)
		वापस;

	/*
	 * Restore max latencies (in the LTR capability) beक्रमe enabling
	 * LTR itself (in the PCIe capability).
	 */
	pci_restore_ltr_state(dev);

	pci_restore_pcie_state(dev);
	pci_restore_pasid_state(dev);
	pci_restore_pri_state(dev);
	pci_restore_ats_state(dev);
	pci_restore_vc_state(dev);
	pci_restore_rebar_state(dev);
	pci_restore_dpc_state(dev);
	pci_restore_pपंचांग_state(dev);

	pci_aer_clear_status(dev);
	pci_restore_aer_state(dev);

	pci_restore_config_space(dev);

	pci_restore_pcix_state(dev);
	pci_restore_msi_state(dev);

	/* Restore ACS and IOV configuration state */
	pci_enable_acs(dev);
	pci_restore_iov_state(dev);

	dev->state_saved = false;
पूर्ण
EXPORT_SYMBOL(pci_restore_state);

काष्ठा pci_saved_state अणु
	u32 config_space[16];
	काष्ठा pci_cap_saved_data cap[];
पूर्ण;

/**
 * pci_store_saved_state - Allocate and वापस an opaque काष्ठा containing
 *			   the device saved state.
 * @dev: PCI device that we're dealing with
 *
 * Return शून्य अगर no state or error.
 */
काष्ठा pci_saved_state *pci_store_saved_state(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_saved_state *state;
	काष्ठा pci_cap_saved_state *पंचांगp;
	काष्ठा pci_cap_saved_data *cap;
	माप_प्रकार size;

	अगर (!dev->state_saved)
		वापस शून्य;

	size = माप(*state) + माप(काष्ठा pci_cap_saved_data);

	hlist_क्रम_each_entry(पंचांगp, &dev->saved_cap_space, next)
		size += माप(काष्ठा pci_cap_saved_data) + पंचांगp->cap.size;

	state = kzalloc(size, GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	स_नकल(state->config_space, dev->saved_config_space,
	       माप(state->config_space));

	cap = state->cap;
	hlist_क्रम_each_entry(पंचांगp, &dev->saved_cap_space, next) अणु
		माप_प्रकार len = माप(काष्ठा pci_cap_saved_data) + पंचांगp->cap.size;
		स_नकल(cap, &पंचांगp->cap, len);
		cap = (काष्ठा pci_cap_saved_data *)((u8 *)cap + len);
	पूर्ण
	/* Empty cap_save terminates list */

	वापस state;
पूर्ण
EXPORT_SYMBOL_GPL(pci_store_saved_state);

/**
 * pci_load_saved_state - Reload the provided save state पूर्णांकo काष्ठा pci_dev.
 * @dev: PCI device that we're dealing with
 * @state: Saved state वापसed from pci_store_saved_state()
 */
पूर्णांक pci_load_saved_state(काष्ठा pci_dev *dev,
			 काष्ठा pci_saved_state *state)
अणु
	काष्ठा pci_cap_saved_data *cap;

	dev->state_saved = false;

	अगर (!state)
		वापस 0;

	स_नकल(dev->saved_config_space, state->config_space,
	       माप(state->config_space));

	cap = state->cap;
	जबतक (cap->size) अणु
		काष्ठा pci_cap_saved_state *पंचांगp;

		पंचांगp = _pci_find_saved_cap(dev, cap->cap_nr, cap->cap_extended);
		अगर (!पंचांगp || पंचांगp->cap.size != cap->size)
			वापस -EINVAL;

		स_नकल(पंचांगp->cap.data, cap->data, पंचांगp->cap.size);
		cap = (काष्ठा pci_cap_saved_data *)((u8 *)cap +
		       माप(काष्ठा pci_cap_saved_data) + cap->size);
	पूर्ण

	dev->state_saved = true;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_load_saved_state);

/**
 * pci_load_and_मुक्त_saved_state - Reload the save state poपूर्णांकed to by state,
 *				   and मुक्त the memory allocated क्रम it.
 * @dev: PCI device that we're dealing with
 * @state: Poपूर्णांकer to saved state वापसed from pci_store_saved_state()
 */
पूर्णांक pci_load_and_मुक्त_saved_state(काष्ठा pci_dev *dev,
				  काष्ठा pci_saved_state **state)
अणु
	पूर्णांक ret = pci_load_saved_state(dev, *state);
	kमुक्त(*state);
	*state = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pci_load_and_मुक्त_saved_state);

पूर्णांक __weak pcibios_enable_device(काष्ठा pci_dev *dev, पूर्णांक bars)
अणु
	वापस pci_enable_resources(dev, bars);
पूर्ण

अटल पूर्णांक करो_pci_enable_device(काष्ठा pci_dev *dev, पूर्णांक bars)
अणु
	पूर्णांक err;
	काष्ठा pci_dev *bridge;
	u16 cmd;
	u8 pin;

	err = pci_set_घातer_state(dev, PCI_D0);
	अगर (err < 0 && err != -EIO)
		वापस err;

	bridge = pci_upstream_bridge(dev);
	अगर (bridge)
		pcie_aspm_घातersave_config_link(bridge);

	err = pcibios_enable_device(dev, bars);
	अगर (err < 0)
		वापस err;
	pci_fixup_device(pci_fixup_enable, dev);

	अगर (dev->msi_enabled || dev->msix_enabled)
		वापस 0;

	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_PIN, &pin);
	अगर (pin) अणु
		pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
		अगर (cmd & PCI_COMMAND_INTX_DISABLE)
			pci_ग_लिखो_config_word(dev, PCI_COMMAND,
					      cmd & ~PCI_COMMAND_INTX_DISABLE);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pci_reenable_device - Resume abanकरोned device
 * @dev: PCI device to be resumed
 *
 * NOTE: This function is a backend of pci_शेष_resume() and is not supposed
 * to be called by normal code, ग_लिखो proper resume handler and use it instead.
 */
पूर्णांक pci_reenable_device(काष्ठा pci_dev *dev)
अणु
	अगर (pci_is_enabled(dev))
		वापस करो_pci_enable_device(dev, (1 << PCI_NUM_RESOURCES) - 1);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(pci_reenable_device);

अटल व्योम pci_enable_bridge(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *bridge;
	पूर्णांक retval;

	bridge = pci_upstream_bridge(dev);
	अगर (bridge)
		pci_enable_bridge(bridge);

	अगर (pci_is_enabled(dev)) अणु
		अगर (!dev->is_busmaster)
			pci_set_master(dev);
		वापस;
	पूर्ण

	retval = pci_enable_device(dev);
	अगर (retval)
		pci_err(dev, "Error enabling bridge (%d), continuing\n",
			retval);
	pci_set_master(dev);
पूर्ण

अटल पूर्णांक pci_enable_device_flags(काष्ठा pci_dev *dev, अचिन्हित दीर्घ flags)
अणु
	काष्ठा pci_dev *bridge;
	पूर्णांक err;
	पूर्णांक i, bars = 0;

	/*
	 * Power state could be unknown at this poपूर्णांक, either due to a fresh
	 * boot or a device removal call.  So get the current घातer state
	 * so that things like MSI message writing will behave as expected
	 * (e.g. अगर the device really is in D0 at enable समय).
	 */
	अगर (dev->pm_cap) अणु
		u16 pmcsr;
		pci_पढ़ो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pmcsr);
		dev->current_state = (pmcsr & PCI_PM_CTRL_STATE_MASK);
	पूर्ण

	अगर (atomic_inc_वापस(&dev->enable_cnt) > 1)
		वापस 0;		/* alपढ़ोy enabled */

	bridge = pci_upstream_bridge(dev);
	अगर (bridge)
		pci_enable_bridge(bridge);

	/* only skip sriov related */
	क्रम (i = 0; i <= PCI_ROM_RESOURCE; i++)
		अगर (dev->resource[i].flags & flags)
			bars |= (1 << i);
	क्रम (i = PCI_BRIDGE_RESOURCES; i < DEVICE_COUNT_RESOURCE; i++)
		अगर (dev->resource[i].flags & flags)
			bars |= (1 << i);

	err = करो_pci_enable_device(dev, bars);
	अगर (err < 0)
		atomic_dec(&dev->enable_cnt);
	वापस err;
पूर्ण

/**
 * pci_enable_device_io - Initialize a device क्रम use with IO space
 * @dev: PCI device to be initialized
 *
 * Initialize device beक्रमe it's used by a driver. Ask low-level code
 * to enable I/O resources. Wake up the device अगर it was suspended.
 * Beware, this function can fail.
 */
पूर्णांक pci_enable_device_io(काष्ठा pci_dev *dev)
अणु
	वापस pci_enable_device_flags(dev, IORESOURCE_IO);
पूर्ण
EXPORT_SYMBOL(pci_enable_device_io);

/**
 * pci_enable_device_mem - Initialize a device क्रम use with Memory space
 * @dev: PCI device to be initialized
 *
 * Initialize device beक्रमe it's used by a driver. Ask low-level code
 * to enable Memory resources. Wake up the device अगर it was suspended.
 * Beware, this function can fail.
 */
पूर्णांक pci_enable_device_mem(काष्ठा pci_dev *dev)
अणु
	वापस pci_enable_device_flags(dev, IORESOURCE_MEM);
पूर्ण
EXPORT_SYMBOL(pci_enable_device_mem);

/**
 * pci_enable_device - Initialize device beक्रमe it's used by a driver.
 * @dev: PCI device to be initialized
 *
 * Initialize device beक्रमe it's used by a driver. Ask low-level code
 * to enable I/O and memory. Wake up the device अगर it was suspended.
 * Beware, this function can fail.
 *
 * Note we करोn't actually enable the device many बार अगर we call
 * this function repeatedly (we just increment the count).
 */
पूर्णांक pci_enable_device(काष्ठा pci_dev *dev)
अणु
	वापस pci_enable_device_flags(dev, IORESOURCE_MEM | IORESOURCE_IO);
पूर्ण
EXPORT_SYMBOL(pci_enable_device);

/*
 * Managed PCI resources.  This manages device on/off, INTx/MSI/MSI-X
 * on/off and BAR regions.  pci_dev itself records MSI/MSI-X status, so
 * there's no need to track it separately.  pci_devres is initialized
 * when a device is enabled using managed PCI device enable पूर्णांकerface.
 */
काष्ठा pci_devres अणु
	अचिन्हित पूर्णांक enabled:1;
	अचिन्हित पूर्णांक pinned:1;
	अचिन्हित पूर्णांक orig_पूर्णांकx:1;
	अचिन्हित पूर्णांक restore_पूर्णांकx:1;
	अचिन्हित पूर्णांक mwi:1;
	u32 region_mask;
पूर्ण;

अटल व्योम pcim_release(काष्ठा device *gendev, व्योम *res)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(gendev);
	काष्ठा pci_devres *this = res;
	पूर्णांक i;

	अगर (dev->msi_enabled)
		pci_disable_msi(dev);
	अगर (dev->msix_enabled)
		pci_disable_msix(dev);

	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++)
		अगर (this->region_mask & (1 << i))
			pci_release_region(dev, i);

	अगर (this->mwi)
		pci_clear_mwi(dev);

	अगर (this->restore_पूर्णांकx)
		pci_पूर्णांकx(dev, this->orig_पूर्णांकx);

	अगर (this->enabled && !this->pinned)
		pci_disable_device(dev);
पूर्ण

अटल काष्ठा pci_devres *get_pci_dr(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_devres *dr, *new_dr;

	dr = devres_find(&pdev->dev, pcim_release, शून्य, शून्य);
	अगर (dr)
		वापस dr;

	new_dr = devres_alloc(pcim_release, माप(*new_dr), GFP_KERNEL);
	अगर (!new_dr)
		वापस शून्य;
	वापस devres_get(&pdev->dev, new_dr, शून्य, शून्य);
पूर्ण

अटल काष्ठा pci_devres *find_pci_dr(काष्ठा pci_dev *pdev)
अणु
	अगर (pci_is_managed(pdev))
		वापस devres_find(&pdev->dev, pcim_release, शून्य, शून्य);
	वापस शून्य;
पूर्ण

/**
 * pcim_enable_device - Managed pci_enable_device()
 * @pdev: PCI device to be initialized
 *
 * Managed pci_enable_device().
 */
पूर्णांक pcim_enable_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_devres *dr;
	पूर्णांक rc;

	dr = get_pci_dr(pdev);
	अगर (unlikely(!dr))
		वापस -ENOMEM;
	अगर (dr->enabled)
		वापस 0;

	rc = pci_enable_device(pdev);
	अगर (!rc) अणु
		pdev->is_managed = 1;
		dr->enabled = 1;
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL(pcim_enable_device);

/**
 * pcim_pin_device - Pin managed PCI device
 * @pdev: PCI device to pin
 *
 * Pin managed PCI device @pdev.  Pinned device won't be disabled on
 * driver detach.  @pdev must have been enabled with
 * pcim_enable_device().
 */
व्योम pcim_pin_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_devres *dr;

	dr = find_pci_dr(pdev);
	WARN_ON(!dr || !dr->enabled);
	अगर (dr)
		dr->pinned = 1;
पूर्ण
EXPORT_SYMBOL(pcim_pin_device);

/*
 * pcibios_add_device - provide arch specअगरic hooks when adding device dev
 * @dev: the PCI device being added
 *
 * Permits the platक्रमm to provide architecture specअगरic functionality when
 * devices are added. This is the शेष implementation. Architecture
 * implementations can override this.
 */
पूर्णांक __weak pcibios_add_device(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण

/**
 * pcibios_release_device - provide arch specअगरic hooks when releasing
 *			    device dev
 * @dev: the PCI device being released
 *
 * Permits the platक्रमm to provide architecture specअगरic functionality when
 * devices are released. This is the शेष implementation. Architecture
 * implementations can override this.
 */
व्योम __weak pcibios_release_device(काष्ठा pci_dev *dev) अणुपूर्ण

/**
 * pcibios_disable_device - disable arch specअगरic PCI resources क्रम device dev
 * @dev: the PCI device to disable
 *
 * Disables architecture specअगरic PCI resources क्रम the device. This
 * is the शेष implementation. Architecture implementations can
 * override this.
 */
व्योम __weak pcibios_disable_device(काष्ठा pci_dev *dev) अणुपूर्ण

/**
 * pcibios_penalize_isa_irq - penalize an ISA IRQ
 * @irq: ISA IRQ to penalize
 * @active: IRQ active or not
 *
 * Permits the platक्रमm to provide architecture-specअगरic functionality when
 * penalizing ISA IRQs. This is the शेष implementation. Architecture
 * implementations can override this.
 */
व्योम __weak pcibios_penalize_isa_irq(पूर्णांक irq, पूर्णांक active) अणुपूर्ण

अटल व्योम करो_pci_disable_device(काष्ठा pci_dev *dev)
अणु
	u16 pci_command;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &pci_command);
	अगर (pci_command & PCI_COMMAND_MASTER) अणु
		pci_command &= ~PCI_COMMAND_MASTER;
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, pci_command);
	पूर्ण

	pcibios_disable_device(dev);
पूर्ण

/**
 * pci_disable_enabled_device - Disable device without updating enable_cnt
 * @dev: PCI device to disable
 *
 * NOTE: This function is a backend of PCI घातer management routines and is
 * not supposed to be called drivers.
 */
व्योम pci_disable_enabled_device(काष्ठा pci_dev *dev)
अणु
	अगर (pci_is_enabled(dev))
		करो_pci_disable_device(dev);
पूर्ण

/**
 * pci_disable_device - Disable PCI device after use
 * @dev: PCI device to be disabled
 *
 * Signal to the प्रणाली that the PCI device is not in use by the प्रणाली
 * anymore.  This only involves disabling PCI bus-mastering, अगर active.
 *
 * Note we करोn't actually disable the device until all callers of
 * pci_enable_device() have called pci_disable_device().
 */
व्योम pci_disable_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_devres *dr;

	dr = find_pci_dr(dev);
	अगर (dr)
		dr->enabled = 0;

	dev_WARN_ONCE(&dev->dev, atomic_पढ़ो(&dev->enable_cnt) <= 0,
		      "disabling already-disabled device");

	अगर (atomic_dec_वापस(&dev->enable_cnt) != 0)
		वापस;

	करो_pci_disable_device(dev);

	dev->is_busmaster = 0;
पूर्ण
EXPORT_SYMBOL(pci_disable_device);

/**
 * pcibios_set_pcie_reset_state - set reset state क्रम device dev
 * @dev: the PCIe device reset
 * @state: Reset state to enter पूर्णांकo
 *
 * Set the PCIe reset state क्रम the device. This is the शेष
 * implementation. Architecture implementations can override this.
 */
पूर्णांक __weak pcibios_set_pcie_reset_state(काष्ठा pci_dev *dev,
					क्रमागत pcie_reset_state state)
अणु
	वापस -EINVAL;
पूर्ण

/**
 * pci_set_pcie_reset_state - set reset state क्रम device dev
 * @dev: the PCIe device reset
 * @state: Reset state to enter पूर्णांकo
 *
 * Sets the PCI reset state क्रम the device.
 */
पूर्णांक pci_set_pcie_reset_state(काष्ठा pci_dev *dev, क्रमागत pcie_reset_state state)
अणु
	वापस pcibios_set_pcie_reset_state(dev, state);
पूर्ण
EXPORT_SYMBOL_GPL(pci_set_pcie_reset_state);

व्योम pcie_clear_device_status(काष्ठा pci_dev *dev)
अणु
	u16 sta;

	pcie_capability_पढ़ो_word(dev, PCI_EXP_DEVSTA, &sta);
	pcie_capability_ग_लिखो_word(dev, PCI_EXP_DEVSTA, sta);
पूर्ण

/**
 * pcie_clear_root_pme_status - Clear root port PME पूर्णांकerrupt status.
 * @dev: PCIe root port or event collector.
 */
व्योम pcie_clear_root_pme_status(काष्ठा pci_dev *dev)
अणु
	pcie_capability_set_dword(dev, PCI_EXP_RTSTA, PCI_EXP_RTSTA_PME);
पूर्ण

/**
 * pci_check_pme_status - Check अगर given device has generated PME.
 * @dev: Device to check.
 *
 * Check the PME status of the device and अगर set, clear it and clear PME enable
 * (अगर set).  Return 'true' अगर PME status and PME enable were both set or
 * 'false' otherwise.
 */
bool pci_check_pme_status(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pmcsr_pos;
	u16 pmcsr;
	bool ret = false;

	अगर (!dev->pm_cap)
		वापस false;

	pmcsr_pos = dev->pm_cap + PCI_PM_CTRL;
	pci_पढ़ो_config_word(dev, pmcsr_pos, &pmcsr);
	अगर (!(pmcsr & PCI_PM_CTRL_PME_STATUS))
		वापस false;

	/* Clear PME status. */
	pmcsr |= PCI_PM_CTRL_PME_STATUS;
	अगर (pmcsr & PCI_PM_CTRL_PME_ENABLE) अणु
		/* Disable PME to aव्योम पूर्णांकerrupt flood. */
		pmcsr &= ~PCI_PM_CTRL_PME_ENABLE;
		ret = true;
	पूर्ण

	pci_ग_लिखो_config_word(dev, pmcsr_pos, pmcsr);

	वापस ret;
पूर्ण

/**
 * pci_pme_wakeup - Wake up a PCI device अगर its PME Status bit is set.
 * @dev: Device to handle.
 * @pme_poll_reset: Whether or not to reset the device's pme_poll flag.
 *
 * Check अगर @dev has generated PME and queue a resume request क्रम it in that
 * हाल.
 */
अटल पूर्णांक pci_pme_wakeup(काष्ठा pci_dev *dev, व्योम *pme_poll_reset)
अणु
	अगर (pme_poll_reset && dev->pme_poll)
		dev->pme_poll = false;

	अगर (pci_check_pme_status(dev)) अणु
		pci_wakeup_event(dev);
		pm_request_resume(&dev->dev);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pci_pme_wakeup_bus - Walk given bus and wake up devices on it, अगर necessary.
 * @bus: Top bus of the subtree to walk.
 */
व्योम pci_pme_wakeup_bus(काष्ठा pci_bus *bus)
अणु
	अगर (bus)
		pci_walk_bus(bus, pci_pme_wakeup, (व्योम *)true);
पूर्ण


/**
 * pci_pme_capable - check the capability of PCI device to generate PME#
 * @dev: PCI device to handle.
 * @state: PCI state from which device will issue PME#.
 */
bool pci_pme_capable(काष्ठा pci_dev *dev, pci_घातer_t state)
अणु
	अगर (!dev->pm_cap)
		वापस false;

	वापस !!(dev->pme_support & (1 << state));
पूर्ण
EXPORT_SYMBOL(pci_pme_capable);

अटल व्योम pci_pme_list_scan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pci_pme_device *pme_dev, *n;

	mutex_lock(&pci_pme_list_mutex);
	list_क्रम_each_entry_safe(pme_dev, n, &pci_pme_list, list) अणु
		अगर (pme_dev->dev->pme_poll) अणु
			काष्ठा pci_dev *bridge;

			bridge = pme_dev->dev->bus->self;
			/*
			 * If bridge is in low घातer state, the
			 * configuration space of subordinate devices
			 * may be not accessible
			 */
			अगर (bridge && bridge->current_state != PCI_D0)
				जारी;
			/*
			 * If the device is in D3cold it should not be
			 * polled either.
			 */
			अगर (pme_dev->dev->current_state == PCI_D3cold)
				जारी;

			pci_pme_wakeup(pme_dev->dev, शून्य);
		पूर्ण अन्यथा अणु
			list_del(&pme_dev->list);
			kमुक्त(pme_dev);
		पूर्ण
	पूर्ण
	अगर (!list_empty(&pci_pme_list))
		queue_delayed_work(प्रणाली_मुक्तzable_wq, &pci_pme_work,
				   msecs_to_jअगरfies(PME_TIMEOUT));
	mutex_unlock(&pci_pme_list_mutex);
पूर्ण

अटल व्योम __pci_pme_active(काष्ठा pci_dev *dev, bool enable)
अणु
	u16 pmcsr;

	अगर (!dev->pme_support)
		वापस;

	pci_पढ़ो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pmcsr);
	/* Clear PME_Status by writing 1 to it and enable PME# */
	pmcsr |= PCI_PM_CTRL_PME_STATUS | PCI_PM_CTRL_PME_ENABLE;
	अगर (!enable)
		pmcsr &= ~PCI_PM_CTRL_PME_ENABLE;

	pci_ग_लिखो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, pmcsr);
पूर्ण

/**
 * pci_pme_restore - Restore PME configuration after config space restore.
 * @dev: PCI device to update.
 */
व्योम pci_pme_restore(काष्ठा pci_dev *dev)
अणु
	u16 pmcsr;

	अगर (!dev->pme_support)
		वापस;

	pci_पढ़ो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pmcsr);
	अगर (dev->wakeup_prepared) अणु
		pmcsr |= PCI_PM_CTRL_PME_ENABLE;
		pmcsr &= ~PCI_PM_CTRL_PME_STATUS;
	पूर्ण अन्यथा अणु
		pmcsr &= ~PCI_PM_CTRL_PME_ENABLE;
		pmcsr |= PCI_PM_CTRL_PME_STATUS;
	पूर्ण
	pci_ग_लिखो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, pmcsr);
पूर्ण

/**
 * pci_pme_active - enable or disable PCI device's PME# function
 * @dev: PCI device to handle.
 * @enable: 'true' to enable PME# generation; 'false' to disable it.
 *
 * The caller must verअगरy that the device is capable of generating PME# beक्रमe
 * calling this function with @enable equal to 'true'.
 */
व्योम pci_pme_active(काष्ठा pci_dev *dev, bool enable)
अणु
	__pci_pme_active(dev, enable);

	/*
	 * PCI (as opposed to PCIe) PME requires that the device have
	 * its PME# line hooked up correctly. Not all hardware venकरोrs
	 * करो this, so the PME never माला_लो delivered and the device
	 * reमुख्यs asleep. The easiest way around this is to
	 * periodically walk the list of suspended devices and check
	 * whether any have their PME flag set. The assumption is that
	 * we'll wake up often enough anyway that this won't be a huge
	 * hit, and the घातer savings from the devices will still be a
	 * win.
	 *
	 * Although PCIe uses in-band PME message instead of PME# line
	 * to report PME, PME करोes not work क्रम some PCIe devices in
	 * reality.  For example, there are devices that set their PME
	 * status bits, but करोn't really bother to send a PME message;
	 * there are PCI Express Root Ports that करोn't bother to
	 * trigger पूर्णांकerrupts when they receive PME messages from the
	 * devices below.  So PME poll is used क्रम PCIe devices too.
	 */

	अगर (dev->pme_poll) अणु
		काष्ठा pci_pme_device *pme_dev;
		अगर (enable) अणु
			pme_dev = kदो_स्मृति(माप(काष्ठा pci_pme_device),
					  GFP_KERNEL);
			अगर (!pme_dev) अणु
				pci_warn(dev, "can't enable PME#\n");
				वापस;
			पूर्ण
			pme_dev->dev = dev;
			mutex_lock(&pci_pme_list_mutex);
			list_add(&pme_dev->list, &pci_pme_list);
			अगर (list_is_singular(&pci_pme_list))
				queue_delayed_work(प्रणाली_मुक्तzable_wq,
						   &pci_pme_work,
						   msecs_to_jअगरfies(PME_TIMEOUT));
			mutex_unlock(&pci_pme_list_mutex);
		पूर्ण अन्यथा अणु
			mutex_lock(&pci_pme_list_mutex);
			list_क्रम_each_entry(pme_dev, &pci_pme_list, list) अणु
				अगर (pme_dev->dev == dev) अणु
					list_del(&pme_dev->list);
					kमुक्त(pme_dev);
					अवरोध;
				पूर्ण
			पूर्ण
			mutex_unlock(&pci_pme_list_mutex);
		पूर्ण
	पूर्ण

	pci_dbg(dev, "PME# %s\n", enable ? "enabled" : "disabled");
पूर्ण
EXPORT_SYMBOL(pci_pme_active);

/**
 * __pci_enable_wake - enable PCI device as wakeup event source
 * @dev: PCI device affected
 * @state: PCI state from which device will issue wakeup events
 * @enable: True to enable event generation; false to disable
 *
 * This enables the device as a wakeup event source, or disables it.
 * When such events involves platक्रमm-specअगरic hooks, those hooks are
 * called स्वतःmatically by this routine.
 *
 * Devices with legacy घातer management (no standard PCI PM capabilities)
 * always require such platक्रमm hooks.
 *
 * RETURN VALUE:
 * 0 is वापसed on success
 * -EINVAL is वापसed अगर device is not supposed to wake up the प्रणाली
 * Error code depending on the platक्रमm is वापसed अगर both the platक्रमm and
 * the native mechanism fail to enable the generation of wake-up events
 */
अटल पूर्णांक __pci_enable_wake(काष्ठा pci_dev *dev, pci_घातer_t state, bool enable)
अणु
	पूर्णांक ret = 0;

	/*
	 * Bridges that are not घातer-manageable directly only संकेत
	 * wakeup on behalf of subordinate devices which is set up
	 * अन्यथाwhere, so skip them. However, bridges that are
	 * घातer-manageable may संकेत wakeup क्रम themselves (क्रम example,
	 * on a hotplug event) and they need to be covered here.
	 */
	अगर (!pci_घातer_manageable(dev))
		वापस 0;

	/* Don't करो the same thing twice in a row क्रम one device. */
	अगर (!!enable == !!dev->wakeup_prepared)
		वापस 0;

	/*
	 * According to "PCI System Architecture" 4th ed. by Tom Shanley & Don
	 * Anderson we should be करोing PME# wake enable followed by ACPI wake
	 * enable.  To disable wake-up we call the platक्रमm first, क्रम symmetry.
	 */

	अगर (enable) अणु
		पूर्णांक error;

		अगर (pci_pme_capable(dev, state))
			pci_pme_active(dev, true);
		अन्यथा
			ret = 1;
		error = platक्रमm_pci_set_wakeup(dev, true);
		अगर (ret)
			ret = error;
		अगर (!ret)
			dev->wakeup_prepared = true;
	पूर्ण अन्यथा अणु
		platक्रमm_pci_set_wakeup(dev, false);
		pci_pme_active(dev, false);
		dev->wakeup_prepared = false;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * pci_enable_wake - change wakeup settings क्रम a PCI device
 * @pci_dev: Target device
 * @state: PCI state from which device will issue wakeup events
 * @enable: Whether or not to enable event generation
 *
 * If @enable is set, check device_may_wakeup() क्रम the device beक्रमe calling
 * __pci_enable_wake() क्रम it.
 */
पूर्णांक pci_enable_wake(काष्ठा pci_dev *pci_dev, pci_घातer_t state, bool enable)
अणु
	अगर (enable && !device_may_wakeup(&pci_dev->dev))
		वापस -EINVAL;

	वापस __pci_enable_wake(pci_dev, state, enable);
पूर्ण
EXPORT_SYMBOL(pci_enable_wake);

/**
 * pci_wake_from_d3 - enable/disable device to wake up from D3_hot or D3_cold
 * @dev: PCI device to prepare
 * @enable: True to enable wake-up event generation; false to disable
 *
 * Many drivers want the device to wake up the प्रणाली from D3_hot or D3_cold
 * and this function allows them to set that up cleanly - pci_enable_wake()
 * should not be called twice in a row to enable wake-up due to PCI PM vs ACPI
 * ordering स्थिरraपूर्णांकs.
 *
 * This function only वापसs error code अगर the device is not allowed to wake
 * up the प्रणाली from sleep or it is not capable of generating PME# from both
 * D3_hot and D3_cold and the platक्रमm is unable to enable wake-up घातer क्रम it.
 */
पूर्णांक pci_wake_from_d3(काष्ठा pci_dev *dev, bool enable)
अणु
	वापस pci_pme_capable(dev, PCI_D3cold) ?
			pci_enable_wake(dev, PCI_D3cold, enable) :
			pci_enable_wake(dev, PCI_D3hot, enable);
पूर्ण
EXPORT_SYMBOL(pci_wake_from_d3);

/**
 * pci_target_state - find an appropriate low घातer state क्रम a given PCI dev
 * @dev: PCI device
 * @wakeup: Whether or not wakeup functionality will be enabled क्रम the device.
 *
 * Use underlying platक्रमm code to find a supported low घातer state क्रम @dev.
 * If the platक्रमm can't manage @dev, वापस the deepest state from which it
 * can generate wake events, based on any available PME info.
 */
अटल pci_घातer_t pci_target_state(काष्ठा pci_dev *dev, bool wakeup)
अणु
	pci_घातer_t target_state = PCI_D3hot;

	अगर (platक्रमm_pci_घातer_manageable(dev)) अणु
		/*
		 * Call the platक्रमm to find the target state क्रम the device.
		 */
		pci_घातer_t state = platक्रमm_pci_choose_state(dev);

		चयन (state) अणु
		हाल PCI_POWER_ERROR:
		हाल PCI_UNKNOWN:
			अवरोध;
		हाल PCI_D1:
		हाल PCI_D2:
			अगर (pci_no_d1d2(dev))
				अवरोध;
			fallthrough;
		शेष:
			target_state = state;
		पूर्ण

		वापस target_state;
	पूर्ण

	अगर (!dev->pm_cap)
		target_state = PCI_D0;

	/*
	 * If the device is in D3cold even though it's not घातer-manageable by
	 * the platक्रमm, it may have been घातered करोwn by non-standard means.
	 * Best to let it slumber.
	 */
	अगर (dev->current_state == PCI_D3cold)
		target_state = PCI_D3cold;

	अगर (wakeup) अणु
		/*
		 * Find the deepest state from which the device can generate
		 * PME#.
		 */
		अगर (dev->pme_support) अणु
			जबतक (target_state
			      && !(dev->pme_support & (1 << target_state)))
				target_state--;
		पूर्ण
	पूर्ण

	वापस target_state;
पूर्ण

/**
 * pci_prepare_to_sleep - prepare PCI device क्रम प्रणाली-wide transition
 *			  पूर्णांकo a sleep state
 * @dev: Device to handle.
 *
 * Choose the घातer state appropriate क्रम the device depending on whether
 * it can wake up the प्रणाली and/or is घातer manageable by the platक्रमm
 * (PCI_D3hot is the शेष) and put the device पूर्णांकo that state.
 */
पूर्णांक pci_prepare_to_sleep(काष्ठा pci_dev *dev)
अणु
	bool wakeup = device_may_wakeup(&dev->dev);
	pci_घातer_t target_state = pci_target_state(dev, wakeup);
	पूर्णांक error;

	अगर (target_state == PCI_POWER_ERROR)
		वापस -EIO;

	/*
	 * There are प्रणालीs (क्रम example, Intel mobile chips since Coffee
	 * Lake) where the घातer drawn जबतक suspended can be signअगरicantly
	 * reduced by disabling PTM on PCIe root ports as this allows the
	 * port to enter a lower-घातer PM state and the SoC to reach a
	 * lower-घातer idle state as a whole.
	 */
	अगर (pci_pcie_type(dev) == PCI_EXP_TYPE_ROOT_PORT)
		pci_disable_pपंचांग(dev);

	pci_enable_wake(dev, target_state, wakeup);

	error = pci_set_घातer_state(dev, target_state);

	अगर (error) अणु
		pci_enable_wake(dev, target_state, false);
		pci_restore_pपंचांग_state(dev);
	पूर्ण

	वापस error;
पूर्ण
EXPORT_SYMBOL(pci_prepare_to_sleep);

/**
 * pci_back_from_sleep - turn PCI device on during प्रणाली-wide transition
 *			 पूर्णांकo working state
 * @dev: Device to handle.
 *
 * Disable device's प्रणाली wake-up capability and put it पूर्णांकo D0.
 */
पूर्णांक pci_back_from_sleep(काष्ठा pci_dev *dev)
अणु
	pci_enable_wake(dev, PCI_D0, false);
	वापस pci_set_घातer_state(dev, PCI_D0);
पूर्ण
EXPORT_SYMBOL(pci_back_from_sleep);

/**
 * pci_finish_runसमय_suspend - Carry out PCI-specअगरic part of runसमय suspend.
 * @dev: PCI device being suspended.
 *
 * Prepare @dev to generate wake-up events at run समय and put it पूर्णांकo a low
 * घातer state.
 */
पूर्णांक pci_finish_runसमय_suspend(काष्ठा pci_dev *dev)
अणु
	pci_घातer_t target_state;
	पूर्णांक error;

	target_state = pci_target_state(dev, device_can_wakeup(&dev->dev));
	अगर (target_state == PCI_POWER_ERROR)
		वापस -EIO;

	dev->runसमय_d3cold = target_state == PCI_D3cold;

	/*
	 * There are प्रणालीs (क्रम example, Intel mobile chips since Coffee
	 * Lake) where the घातer drawn जबतक suspended can be signअगरicantly
	 * reduced by disabling PTM on PCIe root ports as this allows the
	 * port to enter a lower-घातer PM state and the SoC to reach a
	 * lower-घातer idle state as a whole.
	 */
	अगर (pci_pcie_type(dev) == PCI_EXP_TYPE_ROOT_PORT)
		pci_disable_pपंचांग(dev);

	__pci_enable_wake(dev, target_state, pci_dev_run_wake(dev));

	error = pci_set_घातer_state(dev, target_state);

	अगर (error) अणु
		pci_enable_wake(dev, target_state, false);
		pci_restore_pपंचांग_state(dev);
		dev->runसमय_d3cold = false;
	पूर्ण

	वापस error;
पूर्ण

/**
 * pci_dev_run_wake - Check अगर device can generate run-समय wake-up events.
 * @dev: Device to check.
 *
 * Return true अगर the device itself is capable of generating wake-up events
 * (through the platक्रमm or using the native PCIe PME) or अगर the device supports
 * PME and one of its upstream bridges can generate wake-up events.
 */
bool pci_dev_run_wake(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_bus *bus = dev->bus;

	अगर (!dev->pme_support)
		वापस false;

	/* PME-capable in principle, but not from the target घातer state */
	अगर (!pci_pme_capable(dev, pci_target_state(dev, true)))
		वापस false;

	अगर (device_can_wakeup(&dev->dev))
		वापस true;

	जबतक (bus->parent) अणु
		काष्ठा pci_dev *bridge = bus->self;

		अगर (device_can_wakeup(&bridge->dev))
			वापस true;

		bus = bus->parent;
	पूर्ण

	/* We have reached the root bus. */
	अगर (bus->bridge)
		वापस device_can_wakeup(bus->bridge);

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(pci_dev_run_wake);

/**
 * pci_dev_need_resume - Check अगर it is necessary to resume the device.
 * @pci_dev: Device to check.
 *
 * Return 'true' अगर the device is not runसमय-suspended or it has to be
 * reconfigured due to wakeup settings dअगरference between प्रणाली and runसमय
 * suspend, or the current घातer state of it is not suitable क्रम the upcoming
 * (प्रणाली-wide) transition.
 */
bool pci_dev_need_resume(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा device *dev = &pci_dev->dev;
	pci_घातer_t target_state;

	अगर (!pm_runसमय_suspended(dev) || platक्रमm_pci_need_resume(pci_dev))
		वापस true;

	target_state = pci_target_state(pci_dev, device_may_wakeup(dev));

	/*
	 * If the earlier platक्रमm check has not triggered, D3cold is just घातer
	 * removal on top of D3hot, so no need to resume the device in that
	 * हाल.
	 */
	वापस target_state != pci_dev->current_state &&
		target_state != PCI_D3cold &&
		pci_dev->current_state != PCI_D3hot;
पूर्ण

/**
 * pci_dev_adjust_pme - Adjust PME setting क्रम a suspended device.
 * @pci_dev: Device to check.
 *
 * If the device is suspended and it is not configured क्रम प्रणाली wakeup,
 * disable PME क्रम it to prevent it from waking up the प्रणाली unnecessarily.
 *
 * Note that अगर the device's घातer state is D3cold and the platक्रमm check in
 * pci_dev_need_resume() has not triggered, the device's configuration need not
 * be changed.
 */
व्योम pci_dev_adjust_pme(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा device *dev = &pci_dev->dev;

	spin_lock_irq(&dev->घातer.lock);

	अगर (pm_runसमय_suspended(dev) && !device_may_wakeup(dev) &&
	    pci_dev->current_state < PCI_D3cold)
		__pci_pme_active(pci_dev, false);

	spin_unlock_irq(&dev->घातer.lock);
पूर्ण

/**
 * pci_dev_complete_resume - Finalize resume from प्रणाली sleep क्रम a device.
 * @pci_dev: Device to handle.
 *
 * If the device is runसमय suspended and wakeup-capable, enable PME क्रम it as
 * it might have been disabled during the prepare phase of प्रणाली suspend अगर
 * the device was not configured क्रम प्रणाली wakeup.
 */
व्योम pci_dev_complete_resume(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा device *dev = &pci_dev->dev;

	अगर (!pci_dev_run_wake(pci_dev))
		वापस;

	spin_lock_irq(&dev->घातer.lock);

	अगर (pm_runसमय_suspended(dev) && pci_dev->current_state < PCI_D3cold)
		__pci_pme_active(pci_dev, true);

	spin_unlock_irq(&dev->घातer.lock);
पूर्ण

व्योम pci_config_pm_runसमय_get(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *parent = dev->parent;

	अगर (parent)
		pm_runसमय_get_sync(parent);
	pm_runसमय_get_noresume(dev);
	/*
	 * pdev->current_state is set to PCI_D3cold during suspending,
	 * so रुको until suspending completes
	 */
	pm_runसमय_barrier(dev);
	/*
	 * Only need to resume devices in D3cold, because config
	 * रेजिस्टरs are still accessible क्रम devices suspended but
	 * not in D3cold.
	 */
	अगर (pdev->current_state == PCI_D3cold)
		pm_runसमय_resume(dev);
पूर्ण

व्योम pci_config_pm_runसमय_put(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *parent = dev->parent;

	pm_runसमय_put(dev);
	अगर (parent)
		pm_runसमय_put_sync(parent);
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id bridge_d3_blacklist[] = अणु
#अगर_घोषित CONFIG_X86
	अणु
		/*
		 * Gigabyte X299 root port is not marked as hotplug capable
		 * which allows Linux to घातer manage it.  However, this
		 * confuses the BIOS SMI handler so करोn't घातer manage root
		 * ports on that प्रणाली.
		 */
		.ident = "X299 DESIGNARE EX-CF",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Gigabyte Technology Co., Ltd."),
			DMI_MATCH(DMI_BOARD_NAME, "X299 DESIGNARE EX-CF"),
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

/**
 * pci_bridge_d3_possible - Is it possible to put the bridge पूर्णांकo D3
 * @bridge: Bridge to check
 *
 * This function checks अगर it is possible to move the bridge to D3.
 * Currently we only allow D3 क्रम recent enough PCIe ports and Thunderbolt.
 */
bool pci_bridge_d3_possible(काष्ठा pci_dev *bridge)
अणु
	अगर (!pci_is_pcie(bridge))
		वापस false;

	चयन (pci_pcie_type(bridge)) अणु
	हाल PCI_EXP_TYPE_ROOT_PORT:
	हाल PCI_EXP_TYPE_UPSTREAM:
	हाल PCI_EXP_TYPE_DOWNSTREAM:
		अगर (pci_bridge_d3_disable)
			वापस false;

		/*
		 * Hotplug ports handled by firmware in System Management Mode
		 * may not be put पूर्णांकo D3 by the OS (Thunderbolt on non-Macs).
		 */
		अगर (bridge->is_hotplug_bridge && !pciehp_is_native(bridge))
			वापस false;

		अगर (pci_bridge_d3_क्रमce)
			वापस true;

		/* Even the oldest 2010 Thunderbolt controller supports D3. */
		अगर (bridge->is_thunderbolt)
			वापस true;

		/* Platक्रमm might know better अगर the bridge supports D3 */
		अगर (platक्रमm_pci_bridge_d3(bridge))
			वापस true;

		/*
		 * Hotplug ports handled natively by the OS were not validated
		 * by venकरोrs क्रम runसमय D3 at least until 2018 because there
		 * was no OS support.
		 */
		अगर (bridge->is_hotplug_bridge)
			वापस false;

		अगर (dmi_check_प्रणाली(bridge_d3_blacklist))
			वापस false;

		/*
		 * It should be safe to put PCIe ports from 2015 or newer
		 * to D3.
		 */
		अगर (dmi_get_bios_year() >= 2015)
			वापस true;
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक pci_dev_check_d3cold(काष्ठा pci_dev *dev, व्योम *data)
अणु
	bool *d3cold_ok = data;

	अगर (/* The device needs to be allowed to go D3cold ... */
	    dev->no_d3cold || !dev->d3cold_allowed ||

	    /* ... and अगर it is wakeup capable to करो so from D3cold. */
	    (device_may_wakeup(&dev->dev) &&
	     !pci_pme_capable(dev, PCI_D3cold)) ||

	    /* If it is a bridge it must be allowed to go to D3. */
	    !pci_घातer_manageable(dev))

		*d3cold_ok = false;

	वापस !*d3cold_ok;
पूर्ण

/*
 * pci_bridge_d3_update - Update bridge D3 capabilities
 * @dev: PCI device which is changed
 *
 * Update upstream bridge PM capabilities accordingly depending on अगर the
 * device PM configuration was changed or the device is being हटाओd.  The
 * change is also propagated upstream.
 */
व्योम pci_bridge_d3_update(काष्ठा pci_dev *dev)
अणु
	bool हटाओ = !device_is_रेजिस्टरed(&dev->dev);
	काष्ठा pci_dev *bridge;
	bool d3cold_ok = true;

	bridge = pci_upstream_bridge(dev);
	अगर (!bridge || !pci_bridge_d3_possible(bridge))
		वापस;

	/*
	 * If D3 is currently allowed क्रम the bridge, removing one of its
	 * children won't change that.
	 */
	अगर (हटाओ && bridge->bridge_d3)
		वापस;

	/*
	 * If D3 is currently allowed क्रम the bridge and a child is added or
	 * changed, disallowance of D3 can only be caused by that child, so
	 * we only need to check that single device, not any of its siblings.
	 *
	 * If D3 is currently not allowed क्रम the bridge, checking the device
	 * first may allow us to skip checking its siblings.
	 */
	अगर (!हटाओ)
		pci_dev_check_d3cold(dev, &d3cold_ok);

	/*
	 * If D3 is currently not allowed क्रम the bridge, this may be caused
	 * either by the device being changed/हटाओd or any of its siblings,
	 * so we need to go through all children to find out अगर one of them
	 * जारीs to block D3.
	 */
	अगर (d3cold_ok && !bridge->bridge_d3)
		pci_walk_bus(bridge->subordinate, pci_dev_check_d3cold,
			     &d3cold_ok);

	अगर (bridge->bridge_d3 != d3cold_ok) अणु
		bridge->bridge_d3 = d3cold_ok;
		/* Propagate change to upstream bridges */
		pci_bridge_d3_update(bridge);
	पूर्ण
पूर्ण

/**
 * pci_d3cold_enable - Enable D3cold क्रम device
 * @dev: PCI device to handle
 *
 * This function can be used in drivers to enable D3cold from the device
 * they handle.  It also updates upstream PCI bridge PM capabilities
 * accordingly.
 */
व्योम pci_d3cold_enable(काष्ठा pci_dev *dev)
अणु
	अगर (dev->no_d3cold) अणु
		dev->no_d3cold = false;
		pci_bridge_d3_update(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pci_d3cold_enable);

/**
 * pci_d3cold_disable - Disable D3cold क्रम device
 * @dev: PCI device to handle
 *
 * This function can be used in drivers to disable D3cold from the device
 * they handle.  It also updates upstream PCI bridge PM capabilities
 * accordingly.
 */
व्योम pci_d3cold_disable(काष्ठा pci_dev *dev)
अणु
	अगर (!dev->no_d3cold) अणु
		dev->no_d3cold = true;
		pci_bridge_d3_update(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pci_d3cold_disable);

/**
 * pci_pm_init - Initialize PM functions of given PCI device
 * @dev: PCI device to handle.
 */
व्योम pci_pm_init(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pm;
	u16 status;
	u16 pmc;

	pm_runसमय_क्रमbid(&dev->dev);
	pm_runसमय_set_active(&dev->dev);
	pm_runसमय_enable(&dev->dev);
	device_enable_async_suspend(&dev->dev);
	dev->wakeup_prepared = false;

	dev->pm_cap = 0;
	dev->pme_support = 0;

	/* find PCI PM capability in list */
	pm = pci_find_capability(dev, PCI_CAP_ID_PM);
	अगर (!pm)
		वापस;
	/* Check device's ability to generate PME# */
	pci_पढ़ो_config_word(dev, pm + PCI_PM_PMC, &pmc);

	अगर ((pmc & PCI_PM_CAP_VER_MASK) > 3) अणु
		pci_err(dev, "unsupported PM cap regs version (%u)\n",
			pmc & PCI_PM_CAP_VER_MASK);
		वापस;
	पूर्ण

	dev->pm_cap = pm;
	dev->d3hot_delay = PCI_PM_D3HOT_WAIT;
	dev->d3cold_delay = PCI_PM_D3COLD_WAIT;
	dev->bridge_d3 = pci_bridge_d3_possible(dev);
	dev->d3cold_allowed = true;

	dev->d1_support = false;
	dev->d2_support = false;
	अगर (!pci_no_d1d2(dev)) अणु
		अगर (pmc & PCI_PM_CAP_D1)
			dev->d1_support = true;
		अगर (pmc & PCI_PM_CAP_D2)
			dev->d2_support = true;

		अगर (dev->d1_support || dev->d2_support)
			pci_info(dev, "supports%s%s\n",
				   dev->d1_support ? " D1" : "",
				   dev->d2_support ? " D2" : "");
	पूर्ण

	pmc &= PCI_PM_CAP_PME_MASK;
	अगर (pmc) अणु
		pci_info(dev, "PME# supported from%s%s%s%s%s\n",
			 (pmc & PCI_PM_CAP_PME_D0) ? " D0" : "",
			 (pmc & PCI_PM_CAP_PME_D1) ? " D1" : "",
			 (pmc & PCI_PM_CAP_PME_D2) ? " D2" : "",
			 (pmc & PCI_PM_CAP_PME_D3hot) ? " D3hot" : "",
			 (pmc & PCI_PM_CAP_PME_D3cold) ? " D3cold" : "");
		dev->pme_support = pmc >> PCI_PM_CAP_PME_SHIFT;
		dev->pme_poll = true;
		/*
		 * Make device's PM flags reflect the wake-up capability, but
		 * let the user space enable it to wake up the प्रणाली as needed.
		 */
		device_set_wakeup_capable(&dev->dev, true);
		/* Disable the PME# generation functionality */
		pci_pme_active(dev, false);
	पूर्ण

	pci_पढ़ो_config_word(dev, PCI_STATUS, &status);
	अगर (status & PCI_STATUS_IMM_READY)
		dev->imm_पढ़ोy = 1;
पूर्ण

अटल अचिन्हित दीर्घ pci_ea_flags(काष्ठा pci_dev *dev, u8 prop)
अणु
	अचिन्हित दीर्घ flags = IORESOURCE_PCI_FIXED | IORESOURCE_PCI_EA_BEI;

	चयन (prop) अणु
	हाल PCI_EA_P_MEM:
	हाल PCI_EA_P_VF_MEM:
		flags |= IORESOURCE_MEM;
		अवरोध;
	हाल PCI_EA_P_MEM_PREFETCH:
	हाल PCI_EA_P_VF_MEM_PREFETCH:
		flags |= IORESOURCE_MEM | IORESOURCE_PREFETCH;
		अवरोध;
	हाल PCI_EA_P_IO:
		flags |= IORESOURCE_IO;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस flags;
पूर्ण

अटल काष्ठा resource *pci_ea_get_resource(काष्ठा pci_dev *dev, u8 bei,
					    u8 prop)
अणु
	अगर (bei <= PCI_EA_BEI_BAR5 && prop <= PCI_EA_P_IO)
		वापस &dev->resource[bei];
#अगर_घोषित CONFIG_PCI_IOV
	अन्यथा अगर (bei >= PCI_EA_BEI_VF_BAR0 && bei <= PCI_EA_BEI_VF_BAR5 &&
		 (prop == PCI_EA_P_VF_MEM || prop == PCI_EA_P_VF_MEM_PREFETCH))
		वापस &dev->resource[PCI_IOV_RESOURCES +
				      bei - PCI_EA_BEI_VF_BAR0];
#पूर्ण_अगर
	अन्यथा अगर (bei == PCI_EA_BEI_ROM)
		वापस &dev->resource[PCI_ROM_RESOURCE];
	अन्यथा
		वापस शून्य;
पूर्ण

/* Read an Enhanced Allocation (EA) entry */
अटल पूर्णांक pci_ea_पढ़ो(काष्ठा pci_dev *dev, पूर्णांक offset)
अणु
	काष्ठा resource *res;
	पूर्णांक ent_size, ent_offset = offset;
	resource_माप_प्रकार start, end;
	अचिन्हित दीर्घ flags;
	u32 dw0, bei, base, max_offset;
	u8 prop;
	bool support_64 = (माप(resource_माप_प्रकार) >= 8);

	pci_पढ़ो_config_dword(dev, ent_offset, &dw0);
	ent_offset += 4;

	/* Entry size field indicates DWORDs after 1st */
	ent_size = ((dw0 & PCI_EA_ES) + 1) << 2;

	अगर (!(dw0 & PCI_EA_ENABLE)) /* Entry not enabled */
		जाओ out;

	bei = (dw0 & PCI_EA_BEI) >> 4;
	prop = (dw0 & PCI_EA_PP) >> 8;

	/*
	 * If the Property is in the reserved range, try the Secondary
	 * Property instead.
	 */
	अगर (prop > PCI_EA_P_BRIDGE_IO && prop < PCI_EA_P_MEM_RESERVED)
		prop = (dw0 & PCI_EA_SP) >> 16;
	अगर (prop > PCI_EA_P_BRIDGE_IO)
		जाओ out;

	res = pci_ea_get_resource(dev, bei, prop);
	अगर (!res) अणु
		pci_err(dev, "Unsupported EA entry BEI: %u\n", bei);
		जाओ out;
	पूर्ण

	flags = pci_ea_flags(dev, prop);
	अगर (!flags) अणु
		pci_err(dev, "Unsupported EA properties: %#x\n", prop);
		जाओ out;
	पूर्ण

	/* Read Base */
	pci_पढ़ो_config_dword(dev, ent_offset, &base);
	start = (base & PCI_EA_FIELD_MASK);
	ent_offset += 4;

	/* Read MaxOffset */
	pci_पढ़ो_config_dword(dev, ent_offset, &max_offset);
	ent_offset += 4;

	/* Read Base MSBs (अगर 64-bit entry) */
	अगर (base & PCI_EA_IS_64) अणु
		u32 base_upper;

		pci_पढ़ो_config_dword(dev, ent_offset, &base_upper);
		ent_offset += 4;

		flags |= IORESOURCE_MEM_64;

		/* entry starts above 32-bit boundary, can't use */
		अगर (!support_64 && base_upper)
			जाओ out;

		अगर (support_64)
			start |= ((u64)base_upper << 32);
	पूर्ण

	end = start + (max_offset | 0x03);

	/* Read MaxOffset MSBs (अगर 64-bit entry) */
	अगर (max_offset & PCI_EA_IS_64) अणु
		u32 max_offset_upper;

		pci_पढ़ो_config_dword(dev, ent_offset, &max_offset_upper);
		ent_offset += 4;

		flags |= IORESOURCE_MEM_64;

		/* entry too big, can't use */
		अगर (!support_64 && max_offset_upper)
			जाओ out;

		अगर (support_64)
			end += ((u64)max_offset_upper << 32);
	पूर्ण

	अगर (end < start) अणु
		pci_err(dev, "EA Entry crosses address boundary\n");
		जाओ out;
	पूर्ण

	अगर (ent_size != ent_offset - offset) अणु
		pci_err(dev, "EA Entry Size (%d) does not match length read (%d)\n",
			ent_size, ent_offset - offset);
		जाओ out;
	पूर्ण

	res->name = pci_name(dev);
	res->start = start;
	res->end = end;
	res->flags = flags;

	अगर (bei <= PCI_EA_BEI_BAR5)
		pci_info(dev, "BAR %d: %pR (from Enhanced Allocation, properties %#02x)\n",
			   bei, res, prop);
	अन्यथा अगर (bei == PCI_EA_BEI_ROM)
		pci_info(dev, "ROM: %pR (from Enhanced Allocation, properties %#02x)\n",
			   res, prop);
	अन्यथा अगर (bei >= PCI_EA_BEI_VF_BAR0 && bei <= PCI_EA_BEI_VF_BAR5)
		pci_info(dev, "VF BAR %d: %pR (from Enhanced Allocation, properties %#02x)\n",
			   bei - PCI_EA_BEI_VF_BAR0, res, prop);
	अन्यथा
		pci_info(dev, "BEI %d res: %pR (from Enhanced Allocation, properties %#02x)\n",
			   bei, res, prop);

out:
	वापस offset + ent_size;
पूर्ण

/* Enhanced Allocation Initialization */
व्योम pci_ea_init(काष्ठा pci_dev *dev)
अणु
	पूर्णांक ea;
	u8 num_ent;
	पूर्णांक offset;
	पूर्णांक i;

	/* find PCI EA capability in list */
	ea = pci_find_capability(dev, PCI_CAP_ID_EA);
	अगर (!ea)
		वापस;

	/* determine the number of entries */
	pci_bus_पढ़ो_config_byte(dev->bus, dev->devfn, ea + PCI_EA_NUM_ENT,
					&num_ent);
	num_ent &= PCI_EA_NUM_ENT_MASK;

	offset = ea + PCI_EA_FIRST_ENT;

	/* Skip DWORD 2 क्रम type 1 functions */
	अगर (dev->hdr_type == PCI_HEADER_TYPE_BRIDGE)
		offset += 4;

	/* parse each EA entry */
	क्रम (i = 0; i < num_ent; ++i)
		offset = pci_ea_पढ़ो(dev, offset);
पूर्ण

अटल व्योम pci_add_saved_cap(काष्ठा pci_dev *pci_dev,
	काष्ठा pci_cap_saved_state *new_cap)
अणु
	hlist_add_head(&new_cap->next, &pci_dev->saved_cap_space);
पूर्ण

/**
 * _pci_add_cap_save_buffer - allocate buffer क्रम saving given
 *			      capability रेजिस्टरs
 * @dev: the PCI device
 * @cap: the capability to allocate the buffer क्रम
 * @extended: Standard or Extended capability ID
 * @size: requested size of the buffer
 */
अटल पूर्णांक _pci_add_cap_save_buffer(काष्ठा pci_dev *dev, u16 cap,
				    bool extended, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक pos;
	काष्ठा pci_cap_saved_state *save_state;

	अगर (extended)
		pos = pci_find_ext_capability(dev, cap);
	अन्यथा
		pos = pci_find_capability(dev, cap);

	अगर (!pos)
		वापस 0;

	save_state = kzalloc(माप(*save_state) + size, GFP_KERNEL);
	अगर (!save_state)
		वापस -ENOMEM;

	save_state->cap.cap_nr = cap;
	save_state->cap.cap_extended = extended;
	save_state->cap.size = size;
	pci_add_saved_cap(dev, save_state);

	वापस 0;
पूर्ण

पूर्णांक pci_add_cap_save_buffer(काष्ठा pci_dev *dev, अक्षर cap, अचिन्हित पूर्णांक size)
अणु
	वापस _pci_add_cap_save_buffer(dev, cap, false, size);
पूर्ण

पूर्णांक pci_add_ext_cap_save_buffer(काष्ठा pci_dev *dev, u16 cap, अचिन्हित पूर्णांक size)
अणु
	वापस _pci_add_cap_save_buffer(dev, cap, true, size);
पूर्ण

/**
 * pci_allocate_cap_save_buffers - allocate buffers क्रम saving capabilities
 * @dev: the PCI device
 */
व्योम pci_allocate_cap_save_buffers(काष्ठा pci_dev *dev)
अणु
	पूर्णांक error;

	error = pci_add_cap_save_buffer(dev, PCI_CAP_ID_EXP,
					PCI_EXP_SAVE_REGS * माप(u16));
	अगर (error)
		pci_err(dev, "unable to preallocate PCI Express save buffer\n");

	error = pci_add_cap_save_buffer(dev, PCI_CAP_ID_PCIX, माप(u16));
	अगर (error)
		pci_err(dev, "unable to preallocate PCI-X save buffer\n");

	error = pci_add_ext_cap_save_buffer(dev, PCI_EXT_CAP_ID_LTR,
					    2 * माप(u16));
	अगर (error)
		pci_err(dev, "unable to allocate suspend buffer for LTR\n");

	pci_allocate_vc_save_buffers(dev);
पूर्ण

व्योम pci_मुक्त_cap_save_buffers(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_cap_saved_state *पंचांगp;
	काष्ठा hlist_node *n;

	hlist_क्रम_each_entry_safe(पंचांगp, n, &dev->saved_cap_space, next)
		kमुक्त(पंचांगp);
पूर्ण

/**
 * pci_configure_ari - enable or disable ARI क्रमwarding
 * @dev: the PCI device
 *
 * If @dev and its upstream bridge both support ARI, enable ARI in the
 * bridge.  Otherwise, disable ARI in the bridge.
 */
व्योम pci_configure_ari(काष्ठा pci_dev *dev)
अणु
	u32 cap;
	काष्ठा pci_dev *bridge;

	अगर (pcie_ari_disabled || !pci_is_pcie(dev) || dev->devfn)
		वापस;

	bridge = dev->bus->self;
	अगर (!bridge)
		वापस;

	pcie_capability_पढ़ो_dword(bridge, PCI_EXP_DEVCAP2, &cap);
	अगर (!(cap & PCI_EXP_DEVCAP2_ARI))
		वापस;

	अगर (pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ARI)) अणु
		pcie_capability_set_word(bridge, PCI_EXP_DEVCTL2,
					 PCI_EXP_DEVCTL2_ARI);
		bridge->ari_enabled = 1;
	पूर्ण अन्यथा अणु
		pcie_capability_clear_word(bridge, PCI_EXP_DEVCTL2,
					   PCI_EXP_DEVCTL2_ARI);
		bridge->ari_enabled = 0;
	पूर्ण
पूर्ण

अटल bool pci_acs_flags_enabled(काष्ठा pci_dev *pdev, u16 acs_flags)
अणु
	पूर्णांक pos;
	u16 cap, ctrl;

	pos = pdev->acs_cap;
	अगर (!pos)
		वापस false;

	/*
	 * Except क्रम egress control, capabilities are either required
	 * or only required अगर controllable.  Features missing from the
	 * capability field can thereक्रमe be assumed as hard-wired enabled.
	 */
	pci_पढ़ो_config_word(pdev, pos + PCI_ACS_CAP, &cap);
	acs_flags &= (cap | PCI_ACS_EC);

	pci_पढ़ो_config_word(pdev, pos + PCI_ACS_CTRL, &ctrl);
	वापस (ctrl & acs_flags) == acs_flags;
पूर्ण

/**
 * pci_acs_enabled - test ACS against required flags क्रम a given device
 * @pdev: device to test
 * @acs_flags: required PCI ACS flags
 *
 * Return true अगर the device supports the provided flags.  Automatically
 * filters out flags that are not implemented on multअगरunction devices.
 *
 * Note that this पूर्णांकerface checks the effective ACS capabilities of the
 * device rather than the actual capabilities.  For instance, most single
 * function endpoपूर्णांकs are not required to support ACS because they have no
 * opportunity क्रम peer-to-peer access.  We thereक्रमe वापस 'true'
 * regardless of whether the device exposes an ACS capability.  This makes
 * it much easier क्रम callers of this function to ignore the actual type
 * or topology of the device when testing ACS support.
 */
bool pci_acs_enabled(काष्ठा pci_dev *pdev, u16 acs_flags)
अणु
	पूर्णांक ret;

	ret = pci_dev_specअगरic_acs_enabled(pdev, acs_flags);
	अगर (ret >= 0)
		वापस ret > 0;

	/*
	 * Conventional PCI and PCI-X devices never support ACS, either
	 * effectively or actually.  The shared bus topology implies that
	 * any device on the bus can receive or snoop DMA.
	 */
	अगर (!pci_is_pcie(pdev))
		वापस false;

	चयन (pci_pcie_type(pdev)) अणु
	/*
	 * PCI/X-to-PCIe bridges are not specअगरically mentioned by the spec,
	 * but since their primary पूर्णांकerface is PCI/X, we conservatively
	 * handle them as we would a non-PCIe device.
	 */
	हाल PCI_EXP_TYPE_PCIE_BRIDGE:
	/*
	 * PCIe 3.0, 6.12.1 excludes ACS on these devices.  "ACS is never
	 * applicable... must never implement an ACS Extended Capability...".
	 * This seems arbitrary, but we take a conservative पूर्णांकerpretation
	 * of this statement.
	 */
	हाल PCI_EXP_TYPE_PCI_BRIDGE:
	हाल PCI_EXP_TYPE_RC_EC:
		वापस false;
	/*
	 * PCIe 3.0, 6.12.1.1 specअगरies that करोwnstream and root ports should
	 * implement ACS in order to indicate their peer-to-peer capabilities,
	 * regardless of whether they are single- or multi-function devices.
	 */
	हाल PCI_EXP_TYPE_DOWNSTREAM:
	हाल PCI_EXP_TYPE_ROOT_PORT:
		वापस pci_acs_flags_enabled(pdev, acs_flags);
	/*
	 * PCIe 3.0, 6.12.1.2 specअगरies ACS capabilities that should be
	 * implemented by the reमुख्यing PCIe types to indicate peer-to-peer
	 * capabilities, but only when they are part of a multअगरunction
	 * device.  The footnote क्रम section 6.12 indicates the specअगरic
	 * PCIe types included here.
	 */
	हाल PCI_EXP_TYPE_ENDPOINT:
	हाल PCI_EXP_TYPE_UPSTREAM:
	हाल PCI_EXP_TYPE_LEG_END:
	हाल PCI_EXP_TYPE_RC_END:
		अगर (!pdev->multअगरunction)
			अवरोध;

		वापस pci_acs_flags_enabled(pdev, acs_flags);
	पूर्ण

	/*
	 * PCIe 3.0, 6.12.1.3 specअगरies no ACS capabilities are applicable
	 * to single function devices with the exception of करोwnstream ports.
	 */
	वापस true;
पूर्ण

/**
 * pci_acs_path_enabled - test ACS flags from start to end in a hierarchy
 * @start: starting करोwnstream device
 * @end: ending upstream device or शून्य to search to the root bus
 * @acs_flags: required flags
 *
 * Walk up a device tree from start to end testing PCI ACS support.  If
 * any step aदीर्घ the way करोes not support the required flags, वापस false.
 */
bool pci_acs_path_enabled(काष्ठा pci_dev *start,
			  काष्ठा pci_dev *end, u16 acs_flags)
अणु
	काष्ठा pci_dev *pdev, *parent = start;

	करो अणु
		pdev = parent;

		अगर (!pci_acs_enabled(pdev, acs_flags))
			वापस false;

		अगर (pci_is_root_bus(pdev->bus))
			वापस (end == शून्य);

		parent = pdev->bus->self;
	पूर्ण जबतक (pdev != end);

	वापस true;
पूर्ण

/**
 * pci_acs_init - Initialize ACS अगर hardware supports it
 * @dev: the PCI device
 */
व्योम pci_acs_init(काष्ठा pci_dev *dev)
अणु
	dev->acs_cap = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ACS);

	/*
	 * Attempt to enable ACS regardless of capability because some Root
	 * Ports (e.g. those quirked with *_पूर्णांकel_pch_acs_*) करो not have
	 * the standard ACS capability but still support ACS via those
	 * quirks.
	 */
	pci_enable_acs(dev);
पूर्ण

/**
 * pci_rebar_find_pos - find position of resize ctrl reg क्रम BAR
 * @pdev: PCI device
 * @bar: BAR to find
 *
 * Helper to find the position of the ctrl रेजिस्टर क्रम a BAR.
 * Returns -ENOTSUPP अगर resizable BARs are not supported at all.
 * Returns -ENOENT अगर no ctrl रेजिस्टर क्रम the BAR could be found.
 */
अटल पूर्णांक pci_rebar_find_pos(काष्ठा pci_dev *pdev, पूर्णांक bar)
अणु
	अचिन्हित पूर्णांक pos, nbars, i;
	u32 ctrl;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_REBAR);
	अगर (!pos)
		वापस -ENOTSUPP;

	pci_पढ़ो_config_dword(pdev, pos + PCI_REBAR_CTRL, &ctrl);
	nbars = (ctrl & PCI_REBAR_CTRL_NBAR_MASK) >>
		    PCI_REBAR_CTRL_NBAR_SHIFT;

	क्रम (i = 0; i < nbars; i++, pos += 8) अणु
		पूर्णांक bar_idx;

		pci_पढ़ो_config_dword(pdev, pos + PCI_REBAR_CTRL, &ctrl);
		bar_idx = ctrl & PCI_REBAR_CTRL_BAR_IDX;
		अगर (bar_idx == bar)
			वापस pos;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/**
 * pci_rebar_get_possible_sizes - get possible sizes क्रम BAR
 * @pdev: PCI device
 * @bar: BAR to query
 *
 * Get the possible sizes of a resizable BAR as biपंचांगask defined in the spec
 * (bit 0=1MB, bit 19=512GB). Returns 0 अगर BAR isn't resizable.
 */
u32 pci_rebar_get_possible_sizes(काष्ठा pci_dev *pdev, पूर्णांक bar)
अणु
	पूर्णांक pos;
	u32 cap;

	pos = pci_rebar_find_pos(pdev, bar);
	अगर (pos < 0)
		वापस 0;

	pci_पढ़ो_config_dword(pdev, pos + PCI_REBAR_CAP, &cap);
	cap &= PCI_REBAR_CAP_SIZES;

	/* Sapphire RX 5600 XT Pulse has an invalid cap dword क्रम BAR 0 */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_ATI && pdev->device == 0x731f &&
	    bar == 0 && cap == 0x7000)
		cap = 0x3f000;

	वापस cap >> 4;
पूर्ण
EXPORT_SYMBOL(pci_rebar_get_possible_sizes);

/**
 * pci_rebar_get_current_size - get the current size of a BAR
 * @pdev: PCI device
 * @bar: BAR to set size to
 *
 * Read the size of a BAR from the resizable BAR config.
 * Returns size अगर found or negative error code.
 */
पूर्णांक pci_rebar_get_current_size(काष्ठा pci_dev *pdev, पूर्णांक bar)
अणु
	पूर्णांक pos;
	u32 ctrl;

	pos = pci_rebar_find_pos(pdev, bar);
	अगर (pos < 0)
		वापस pos;

	pci_पढ़ो_config_dword(pdev, pos + PCI_REBAR_CTRL, &ctrl);
	वापस (ctrl & PCI_REBAR_CTRL_BAR_SIZE) >> PCI_REBAR_CTRL_BAR_SHIFT;
पूर्ण

/**
 * pci_rebar_set_size - set a new size क्रम a BAR
 * @pdev: PCI device
 * @bar: BAR to set size to
 * @size: new size as defined in the spec (0=1MB, 19=512GB)
 *
 * Set the new size of a BAR as defined in the spec.
 * Returns zero अगर resizing was successful, error code otherwise.
 */
पूर्णांक pci_rebar_set_size(काष्ठा pci_dev *pdev, पूर्णांक bar, पूर्णांक size)
अणु
	पूर्णांक pos;
	u32 ctrl;

	pos = pci_rebar_find_pos(pdev, bar);
	अगर (pos < 0)
		वापस pos;

	pci_पढ़ो_config_dword(pdev, pos + PCI_REBAR_CTRL, &ctrl);
	ctrl &= ~PCI_REBAR_CTRL_BAR_SIZE;
	ctrl |= size << PCI_REBAR_CTRL_BAR_SHIFT;
	pci_ग_लिखो_config_dword(pdev, pos + PCI_REBAR_CTRL, ctrl);
	वापस 0;
पूर्ण

/**
 * pci_enable_atomic_ops_to_root - enable AtomicOp requests to root port
 * @dev: the PCI device
 * @cap_mask: mask of desired AtomicOp sizes, including one or more of:
 *	PCI_EXP_DEVCAP2_ATOMIC_COMP32
 *	PCI_EXP_DEVCAP2_ATOMIC_COMP64
 *	PCI_EXP_DEVCAP2_ATOMIC_COMP128
 *
 * Return 0 अगर all upstream bridges support AtomicOp routing, egress
 * blocking is disabled on all upstream ports, and the root port supports
 * the requested completion capabilities (32-bit, 64-bit and/or 128-bit
 * AtomicOp completion), or negative otherwise.
 */
पूर्णांक pci_enable_atomic_ops_to_root(काष्ठा pci_dev *dev, u32 cap_mask)
अणु
	काष्ठा pci_bus *bus = dev->bus;
	काष्ठा pci_dev *bridge;
	u32 cap, ctl2;

	अगर (!pci_is_pcie(dev))
		वापस -EINVAL;

	/*
	 * Per PCIe r4.0, sec 6.15, endpoपूर्णांकs and root ports may be
	 * AtomicOp requesters.  For now, we only support endpoपूर्णांकs as
	 * requesters and root ports as completers.  No endpoपूर्णांकs as
	 * completers, and no peer-to-peer.
	 */

	चयन (pci_pcie_type(dev)) अणु
	हाल PCI_EXP_TYPE_ENDPOINT:
	हाल PCI_EXP_TYPE_LEG_END:
	हाल PCI_EXP_TYPE_RC_END:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	जबतक (bus->parent) अणु
		bridge = bus->self;

		pcie_capability_पढ़ो_dword(bridge, PCI_EXP_DEVCAP2, &cap);

		चयन (pci_pcie_type(bridge)) अणु
		/* Ensure चयन ports support AtomicOp routing */
		हाल PCI_EXP_TYPE_UPSTREAM:
		हाल PCI_EXP_TYPE_DOWNSTREAM:
			अगर (!(cap & PCI_EXP_DEVCAP2_ATOMIC_ROUTE))
				वापस -EINVAL;
			अवरोध;

		/* Ensure root port supports all the sizes we care about */
		हाल PCI_EXP_TYPE_ROOT_PORT:
			अगर ((cap & cap_mask) != cap_mask)
				वापस -EINVAL;
			अवरोध;
		पूर्ण

		/* Ensure upstream ports करोn't block AtomicOps on egress */
		अगर (pci_pcie_type(bridge) == PCI_EXP_TYPE_UPSTREAM) अणु
			pcie_capability_पढ़ो_dword(bridge, PCI_EXP_DEVCTL2,
						   &ctl2);
			अगर (ctl2 & PCI_EXP_DEVCTL2_ATOMIC_EGRESS_BLOCK)
				वापस -EINVAL;
		पूर्ण

		bus = bus->parent;
	पूर्ण

	pcie_capability_set_word(dev, PCI_EXP_DEVCTL2,
				 PCI_EXP_DEVCTL2_ATOMIC_REQ);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(pci_enable_atomic_ops_to_root);

/**
 * pci_swizzle_पूर्णांकerrupt_pin - swizzle INTx क्रम device behind bridge
 * @dev: the PCI device
 * @pin: the INTx pin (1=INTA, 2=INTB, 3=INTC, 4=INTD)
 *
 * Perक्रमm INTx swizzling क्रम a device behind one level of bridge.  This is
 * required by section 9.1 of the PCI-to-PCI bridge specअगरication क्रम devices
 * behind bridges on add-in cards.  For devices with ARI enabled, the slot
 * number is always 0 (see the Implementation Note in section 2.2.8.1 of
 * the PCI Express Base Specअगरication, Revision 2.1)
 */
u8 pci_swizzle_पूर्णांकerrupt_pin(स्थिर काष्ठा pci_dev *dev, u8 pin)
अणु
	पूर्णांक slot;

	अगर (pci_ari_enabled(dev->bus))
		slot = 0;
	अन्यथा
		slot = PCI_SLOT(dev->devfn);

	वापस (((pin - 1) + slot) % 4) + 1;
पूर्ण

पूर्णांक pci_get_पूर्णांकerrupt_pin(काष्ठा pci_dev *dev, काष्ठा pci_dev **bridge)
अणु
	u8 pin;

	pin = dev->pin;
	अगर (!pin)
		वापस -1;

	जबतक (!pci_is_root_bus(dev->bus)) अणु
		pin = pci_swizzle_पूर्णांकerrupt_pin(dev, pin);
		dev = dev->bus->self;
	पूर्ण
	*bridge = dev;
	वापस pin;
पूर्ण

/**
 * pci_common_swizzle - swizzle INTx all the way to root bridge
 * @dev: the PCI device
 * @pinp: poपूर्णांकer to the INTx pin value (1=INTA, 2=INTB, 3=INTD, 4=INTD)
 *
 * Perक्रमm INTx swizzling क्रम a device.  This traverses through all PCI-to-PCI
 * bridges all the way up to a PCI root bus.
 */
u8 pci_common_swizzle(काष्ठा pci_dev *dev, u8 *pinp)
अणु
	u8 pin = *pinp;

	जबतक (!pci_is_root_bus(dev->bus)) अणु
		pin = pci_swizzle_पूर्णांकerrupt_pin(dev, pin);
		dev = dev->bus->self;
	पूर्ण
	*pinp = pin;
	वापस PCI_SLOT(dev->devfn);
पूर्ण
EXPORT_SYMBOL_GPL(pci_common_swizzle);

/**
 * pci_release_region - Release a PCI bar
 * @pdev: PCI device whose resources were previously reserved by
 *	  pci_request_region()
 * @bar: BAR to release
 *
 * Releases the PCI I/O and memory resources previously reserved by a
 * successful call to pci_request_region().  Call this function only
 * after all use of the PCI regions has ceased.
 */
व्योम pci_release_region(काष्ठा pci_dev *pdev, पूर्णांक bar)
अणु
	काष्ठा pci_devres *dr;

	अगर (pci_resource_len(pdev, bar) == 0)
		वापस;
	अगर (pci_resource_flags(pdev, bar) & IORESOURCE_IO)
		release_region(pci_resource_start(pdev, bar),
				pci_resource_len(pdev, bar));
	अन्यथा अगर (pci_resource_flags(pdev, bar) & IORESOURCE_MEM)
		release_mem_region(pci_resource_start(pdev, bar),
				pci_resource_len(pdev, bar));

	dr = find_pci_dr(pdev);
	अगर (dr)
		dr->region_mask &= ~(1 << bar);
पूर्ण
EXPORT_SYMBOL(pci_release_region);

/**
 * __pci_request_region - Reserved PCI I/O and memory resource
 * @pdev: PCI device whose resources are to be reserved
 * @bar: BAR to be reserved
 * @res_name: Name to be associated with resource.
 * @exclusive: whether the region access is exclusive or not
 *
 * Mark the PCI region associated with PCI device @pdev BAR @bar as
 * being reserved by owner @res_name.  Do not access any
 * address inside the PCI regions unless this call वापसs
 * successfully.
 *
 * If @exclusive is set, then the region is marked so that userspace
 * is explicitly not allowed to map the resource via /dev/mem or
 * sysfs MMIO access.
 *
 * Returns 0 on success, or %EBUSY on error.  A warning
 * message is also prपूर्णांकed on failure.
 */
अटल पूर्णांक __pci_request_region(काष्ठा pci_dev *pdev, पूर्णांक bar,
				स्थिर अक्षर *res_name, पूर्णांक exclusive)
अणु
	काष्ठा pci_devres *dr;

	अगर (pci_resource_len(pdev, bar) == 0)
		वापस 0;

	अगर (pci_resource_flags(pdev, bar) & IORESOURCE_IO) अणु
		अगर (!request_region(pci_resource_start(pdev, bar),
			    pci_resource_len(pdev, bar), res_name))
			जाओ err_out;
	पूर्ण अन्यथा अगर (pci_resource_flags(pdev, bar) & IORESOURCE_MEM) अणु
		अगर (!__request_mem_region(pci_resource_start(pdev, bar),
					pci_resource_len(pdev, bar), res_name,
					exclusive))
			जाओ err_out;
	पूर्ण

	dr = find_pci_dr(pdev);
	अगर (dr)
		dr->region_mask |= 1 << bar;

	वापस 0;

err_out:
	pci_warn(pdev, "BAR %d: can't reserve %pR\n", bar,
		 &pdev->resource[bar]);
	वापस -EBUSY;
पूर्ण

/**
 * pci_request_region - Reserve PCI I/O and memory resource
 * @pdev: PCI device whose resources are to be reserved
 * @bar: BAR to be reserved
 * @res_name: Name to be associated with resource
 *
 * Mark the PCI region associated with PCI device @pdev BAR @bar as
 * being reserved by owner @res_name.  Do not access any
 * address inside the PCI regions unless this call वापसs
 * successfully.
 *
 * Returns 0 on success, or %EBUSY on error.  A warning
 * message is also prपूर्णांकed on failure.
 */
पूर्णांक pci_request_region(काष्ठा pci_dev *pdev, पूर्णांक bar, स्थिर अक्षर *res_name)
अणु
	वापस __pci_request_region(pdev, bar, res_name, 0);
पूर्ण
EXPORT_SYMBOL(pci_request_region);

/**
 * pci_release_selected_regions - Release selected PCI I/O and memory resources
 * @pdev: PCI device whose resources were previously reserved
 * @bars: Biपंचांगask of BARs to be released
 *
 * Release selected PCI I/O and memory resources previously reserved.
 * Call this function only after all use of the PCI regions has ceased.
 */
व्योम pci_release_selected_regions(काष्ठा pci_dev *pdev, पूर्णांक bars)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++)
		अगर (bars & (1 << i))
			pci_release_region(pdev, i);
पूर्ण
EXPORT_SYMBOL(pci_release_selected_regions);

अटल पूर्णांक __pci_request_selected_regions(काष्ठा pci_dev *pdev, पूर्णांक bars,
					  स्थिर अक्षर *res_name, पूर्णांक excl)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++)
		अगर (bars & (1 << i))
			अगर (__pci_request_region(pdev, i, res_name, excl))
				जाओ err_out;
	वापस 0;

err_out:
	जबतक (--i >= 0)
		अगर (bars & (1 << i))
			pci_release_region(pdev, i);

	वापस -EBUSY;
पूर्ण


/**
 * pci_request_selected_regions - Reserve selected PCI I/O and memory resources
 * @pdev: PCI device whose resources are to be reserved
 * @bars: Biपंचांगask of BARs to be requested
 * @res_name: Name to be associated with resource
 */
पूर्णांक pci_request_selected_regions(काष्ठा pci_dev *pdev, पूर्णांक bars,
				 स्थिर अक्षर *res_name)
अणु
	वापस __pci_request_selected_regions(pdev, bars, res_name, 0);
पूर्ण
EXPORT_SYMBOL(pci_request_selected_regions);

पूर्णांक pci_request_selected_regions_exclusive(काष्ठा pci_dev *pdev, पूर्णांक bars,
					   स्थिर अक्षर *res_name)
अणु
	वापस __pci_request_selected_regions(pdev, bars, res_name,
			IORESOURCE_EXCLUSIVE);
पूर्ण
EXPORT_SYMBOL(pci_request_selected_regions_exclusive);

/**
 * pci_release_regions - Release reserved PCI I/O and memory resources
 * @pdev: PCI device whose resources were previously reserved by
 *	  pci_request_regions()
 *
 * Releases all PCI I/O and memory resources previously reserved by a
 * successful call to pci_request_regions().  Call this function only
 * after all use of the PCI regions has ceased.
 */

व्योम pci_release_regions(काष्ठा pci_dev *pdev)
अणु
	pci_release_selected_regions(pdev, (1 << PCI_STD_NUM_BARS) - 1);
पूर्ण
EXPORT_SYMBOL(pci_release_regions);

/**
 * pci_request_regions - Reserve PCI I/O and memory resources
 * @pdev: PCI device whose resources are to be reserved
 * @res_name: Name to be associated with resource.
 *
 * Mark all PCI regions associated with PCI device @pdev as
 * being reserved by owner @res_name.  Do not access any
 * address inside the PCI regions unless this call वापसs
 * successfully.
 *
 * Returns 0 on success, or %EBUSY on error.  A warning
 * message is also prपूर्णांकed on failure.
 */
पूर्णांक pci_request_regions(काष्ठा pci_dev *pdev, स्थिर अक्षर *res_name)
अणु
	वापस pci_request_selected_regions(pdev,
			((1 << PCI_STD_NUM_BARS) - 1), res_name);
पूर्ण
EXPORT_SYMBOL(pci_request_regions);

/**
 * pci_request_regions_exclusive - Reserve PCI I/O and memory resources
 * @pdev: PCI device whose resources are to be reserved
 * @res_name: Name to be associated with resource.
 *
 * Mark all PCI regions associated with PCI device @pdev as being reserved
 * by owner @res_name.  Do not access any address inside the PCI regions
 * unless this call वापसs successfully.
 *
 * pci_request_regions_exclusive() will mark the region so that /dev/mem
 * and the sysfs MMIO access will not be allowed.
 *
 * Returns 0 on success, or %EBUSY on error.  A warning message is also
 * prपूर्णांकed on failure.
 */
पूर्णांक pci_request_regions_exclusive(काष्ठा pci_dev *pdev, स्थिर अक्षर *res_name)
अणु
	वापस pci_request_selected_regions_exclusive(pdev,
				((1 << PCI_STD_NUM_BARS) - 1), res_name);
पूर्ण
EXPORT_SYMBOL(pci_request_regions_exclusive);

/*
 * Record the PCI IO range (expressed as CPU physical address + size).
 * Return a negative value अगर an error has occurred, zero otherwise
 */
पूर्णांक pci_रेजिस्टर_io_range(काष्ठा fwnode_handle *fwnode, phys_addr_t addr,
			resource_माप_प्रकार	size)
अणु
	पूर्णांक ret = 0;
#अगर_घोषित PCI_IOBASE
	काष्ठा logic_pio_hwaddr *range;

	अगर (!size || addr + size < addr)
		वापस -EINVAL;

	range = kzalloc(माप(*range), GFP_ATOMIC);
	अगर (!range)
		वापस -ENOMEM;

	range->fwnode = fwnode;
	range->size = size;
	range->hw_start = addr;
	range->flags = LOGIC_PIO_CPU_MMIO;

	ret = logic_pio_रेजिस्टर_range(range);
	अगर (ret)
		kमुक्त(range);

	/* Ignore duplicates due to deferred probing */
	अगर (ret == -EEXIST)
		ret = 0;
#पूर्ण_अगर

	वापस ret;
पूर्ण

phys_addr_t pci_pio_to_address(अचिन्हित दीर्घ pio)
अणु
	phys_addr_t address = (phys_addr_t)OF_BAD_ADDR;

#अगर_घोषित PCI_IOBASE
	अगर (pio >= MMIO_UPPER_LIMIT)
		वापस address;

	address = logic_pio_to_hwaddr(pio);
#पूर्ण_अगर

	वापस address;
पूर्ण
EXPORT_SYMBOL_GPL(pci_pio_to_address);

अचिन्हित दीर्घ __weak pci_address_to_pio(phys_addr_t address)
अणु
#अगर_घोषित PCI_IOBASE
	वापस logic_pio_trans_cpuaddr(address);
#अन्यथा
	अगर (address > IO_SPACE_LIMIT)
		वापस (अचिन्हित दीर्घ)-1;

	वापस (अचिन्हित दीर्घ) address;
#पूर्ण_अगर
पूर्ण

/**
 * pci_remap_iospace - Remap the memory mapped I/O space
 * @res: Resource describing the I/O space
 * @phys_addr: physical address of range to be mapped
 *
 * Remap the memory mapped I/O space described by the @res and the CPU
 * physical address @phys_addr पूर्णांकo भव address space.  Only
 * architectures that have memory mapped IO functions defined (and the
 * PCI_IOBASE value defined) should call this function.
 */
पूर्णांक pci_remap_iospace(स्थिर काष्ठा resource *res, phys_addr_t phys_addr)
अणु
#अगर defined(PCI_IOBASE) && defined(CONFIG_MMU)
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)PCI_IOBASE + res->start;

	अगर (!(res->flags & IORESOURCE_IO))
		वापस -EINVAL;

	अगर (res->end > IO_SPACE_LIMIT)
		वापस -EINVAL;

	वापस ioremap_page_range(vaddr, vaddr + resource_size(res), phys_addr,
				  pgprot_device(PAGE_KERNEL));
#अन्यथा
	/*
	 * This architecture करोes not have memory mapped I/O space,
	 * so this function should never be called
	 */
	WARN_ONCE(1, "This architecture does not support memory mapped I/O\n");
	वापस -ENODEV;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(pci_remap_iospace);

/**
 * pci_unmap_iospace - Unmap the memory mapped I/O space
 * @res: resource to be unmapped
 *
 * Unmap the CPU भव address @res from भव address space.  Only
 * architectures that have memory mapped IO functions defined (and the
 * PCI_IOBASE value defined) should call this function.
 */
व्योम pci_unmap_iospace(काष्ठा resource *res)
अणु
#अगर defined(PCI_IOBASE) && defined(CONFIG_MMU)
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)PCI_IOBASE + res->start;

	vunmap_range(vaddr, vaddr + resource_size(res));
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(pci_unmap_iospace);

अटल व्योम devm_pci_unmap_iospace(काष्ठा device *dev, व्योम *ptr)
अणु
	काष्ठा resource **res = ptr;

	pci_unmap_iospace(*res);
पूर्ण

/**
 * devm_pci_remap_iospace - Managed pci_remap_iospace()
 * @dev: Generic device to remap IO address क्रम
 * @res: Resource describing the I/O space
 * @phys_addr: physical address of range to be mapped
 *
 * Managed pci_remap_iospace().  Map is स्वतःmatically unmapped on driver
 * detach.
 */
पूर्णांक devm_pci_remap_iospace(काष्ठा device *dev, स्थिर काष्ठा resource *res,
			   phys_addr_t phys_addr)
अणु
	स्थिर काष्ठा resource **ptr;
	पूर्णांक error;

	ptr = devres_alloc(devm_pci_unmap_iospace, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	error = pci_remap_iospace(res, phys_addr);
	अगर (error) अणु
		devres_मुक्त(ptr);
	पूर्ण अन्यथा	अणु
		*ptr = res;
		devres_add(dev, ptr);
	पूर्ण

	वापस error;
पूर्ण
EXPORT_SYMBOL(devm_pci_remap_iospace);

/**
 * devm_pci_remap_cfgspace - Managed pci_remap_cfgspace()
 * @dev: Generic device to remap IO address क्रम
 * @offset: Resource address to map
 * @size: Size of map
 *
 * Managed pci_remap_cfgspace().  Map is स्वतःmatically unmapped on driver
 * detach.
 */
व्योम __iomem *devm_pci_remap_cfgspace(काष्ठा device *dev,
				      resource_माप_प्रकार offset,
				      resource_माप_प्रकार size)
अणु
	व्योम __iomem **ptr, *addr;

	ptr = devres_alloc(devm_ioremap_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	addr = pci_remap_cfgspace(offset, size);
	अगर (addr) अणु
		*ptr = addr;
		devres_add(dev, ptr);
	पूर्ण अन्यथा
		devres_मुक्त(ptr);

	वापस addr;
पूर्ण
EXPORT_SYMBOL(devm_pci_remap_cfgspace);

/**
 * devm_pci_remap_cfg_resource - check, request region and ioremap cfg resource
 * @dev: generic device to handle the resource क्रम
 * @res: configuration space resource to be handled
 *
 * Checks that a resource is a valid memory region, requests the memory
 * region and ioremaps with pci_remap_cfgspace() API that ensures the
 * proper PCI configuration space memory attributes are guaranteed.
 *
 * All operations are managed and will be unकरोne on driver detach.
 *
 * Returns a poपूर्णांकer to the remapped memory or an ERR_PTR() encoded error code
 * on failure. Usage example::
 *
 *	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
 *	base = devm_pci_remap_cfg_resource(&pdev->dev, res);
 *	अगर (IS_ERR(base))
 *		वापस PTR_ERR(base);
 */
व्योम __iomem *devm_pci_remap_cfg_resource(काष्ठा device *dev,
					  काष्ठा resource *res)
अणु
	resource_माप_प्रकार size;
	स्थिर अक्षर *name;
	व्योम __iomem *dest_ptr;

	BUG_ON(!dev);

	अगर (!res || resource_type(res) != IORESOURCE_MEM) अणु
		dev_err(dev, "invalid resource\n");
		वापस IOMEM_ERR_PTR(-EINVAL);
	पूर्ण

	size = resource_size(res);

	अगर (res->name)
		name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s %s", dev_name(dev),
				      res->name);
	अन्यथा
		name = devm_kstrdup(dev, dev_name(dev), GFP_KERNEL);
	अगर (!name)
		वापस IOMEM_ERR_PTR(-ENOMEM);

	अगर (!devm_request_mem_region(dev, res->start, size, name)) अणु
		dev_err(dev, "can't request region for resource %pR\n", res);
		वापस IOMEM_ERR_PTR(-EBUSY);
	पूर्ण

	dest_ptr = devm_pci_remap_cfgspace(dev, res->start, size);
	अगर (!dest_ptr) अणु
		dev_err(dev, "ioremap failed for resource %pR\n", res);
		devm_release_mem_region(dev, res->start, size);
		dest_ptr = IOMEM_ERR_PTR(-ENOMEM);
	पूर्ण

	वापस dest_ptr;
पूर्ण
EXPORT_SYMBOL(devm_pci_remap_cfg_resource);

अटल व्योम __pci_set_master(काष्ठा pci_dev *dev, bool enable)
अणु
	u16 old_cmd, cmd;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &old_cmd);
	अगर (enable)
		cmd = old_cmd | PCI_COMMAND_MASTER;
	अन्यथा
		cmd = old_cmd & ~PCI_COMMAND_MASTER;
	अगर (cmd != old_cmd) अणु
		pci_dbg(dev, "%s bus mastering\n",
			enable ? "enabling" : "disabling");
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
	पूर्ण
	dev->is_busmaster = enable;
पूर्ण

/**
 * pcibios_setup - process "pci=" kernel boot arguments
 * @str: string used to pass in "pci=" kernel boot arguments
 *
 * Process kernel boot arguments.  This is the शेष implementation.
 * Architecture specअगरic implementations can override this as necessary.
 */
अक्षर * __weak __init pcibios_setup(अक्षर *str)
अणु
	वापस str;
पूर्ण

/**
 * pcibios_set_master - enable PCI bus-mastering क्रम device dev
 * @dev: the PCI device to enable
 *
 * Enables PCI bus-mastering क्रम the device.  This is the शेष
 * implementation.  Architecture specअगरic implementations can override
 * this अगर necessary.
 */
व्योम __weak pcibios_set_master(काष्ठा pci_dev *dev)
अणु
	u8 lat;

	/* The latency समयr करोesn't apply to PCIe (either Type 0 or Type 1) */
	अगर (pci_is_pcie(dev))
		वापस;

	pci_पढ़ो_config_byte(dev, PCI_LATENCY_TIMER, &lat);
	अगर (lat < 16)
		lat = (64 <= pcibios_max_latency) ? 64 : pcibios_max_latency;
	अन्यथा अगर (lat > pcibios_max_latency)
		lat = pcibios_max_latency;
	अन्यथा
		वापस;

	pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, lat);
पूर्ण

/**
 * pci_set_master - enables bus-mastering क्रम device dev
 * @dev: the PCI device to enable
 *
 * Enables bus-mastering on the device and calls pcibios_set_master()
 * to करो the needed arch specअगरic settings.
 */
व्योम pci_set_master(काष्ठा pci_dev *dev)
अणु
	__pci_set_master(dev, true);
	pcibios_set_master(dev);
पूर्ण
EXPORT_SYMBOL(pci_set_master);

/**
 * pci_clear_master - disables bus-mastering क्रम device dev
 * @dev: the PCI device to disable
 */
व्योम pci_clear_master(काष्ठा pci_dev *dev)
अणु
	__pci_set_master(dev, false);
पूर्ण
EXPORT_SYMBOL(pci_clear_master);

/**
 * pci_set_cacheline_size - ensure the CACHE_LINE_SIZE रेजिस्टर is programmed
 * @dev: the PCI device क्रम which MWI is to be enabled
 *
 * Helper function क्रम pci_set_mwi.
 * Originally copied from drivers/net/acenic.c.
 * Copyright 1998-2001 by Jes Sorensen, <jes@trained-monkey.org>.
 *
 * RETURNS: An appropriate -ERRNO error value on error, or zero क्रम success.
 */
पूर्णांक pci_set_cacheline_size(काष्ठा pci_dev *dev)
अणु
	u8 cacheline_size;

	अगर (!pci_cache_line_size)
		वापस -EINVAL;

	/* Validate current setting: the PCI_CACHE_LINE_SIZE must be
	   equal to or multiple of the right value. */
	pci_पढ़ो_config_byte(dev, PCI_CACHE_LINE_SIZE, &cacheline_size);
	अगर (cacheline_size >= pci_cache_line_size &&
	    (cacheline_size % pci_cache_line_size) == 0)
		वापस 0;

	/* Write the correct value. */
	pci_ग_लिखो_config_byte(dev, PCI_CACHE_LINE_SIZE, pci_cache_line_size);
	/* Read it back. */
	pci_पढ़ो_config_byte(dev, PCI_CACHE_LINE_SIZE, &cacheline_size);
	अगर (cacheline_size == pci_cache_line_size)
		वापस 0;

	pci_dbg(dev, "cache line size of %d is not supported\n",
		   pci_cache_line_size << 2);

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(pci_set_cacheline_size);

/**
 * pci_set_mwi - enables memory-ग_लिखो-invalidate PCI transaction
 * @dev: the PCI device क्रम which MWI is enabled
 *
 * Enables the Memory-Write-Invalidate transaction in %PCI_COMMAND.
 *
 * RETURNS: An appropriate -ERRNO error value on error, or zero क्रम success.
 */
पूर्णांक pci_set_mwi(काष्ठा pci_dev *dev)
अणु
#अगर_घोषित PCI_DISABLE_MWI
	वापस 0;
#अन्यथा
	पूर्णांक rc;
	u16 cmd;

	rc = pci_set_cacheline_size(dev);
	अगर (rc)
		वापस rc;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	अगर (!(cmd & PCI_COMMAND_INVALIDATE)) अणु
		pci_dbg(dev, "enabling Mem-Wr-Inval\n");
		cmd |= PCI_COMMAND_INVALIDATE;
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
	पूर्ण
	वापस 0;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(pci_set_mwi);

/**
 * pcim_set_mwi - a device-managed pci_set_mwi()
 * @dev: the PCI device क्रम which MWI is enabled
 *
 * Managed pci_set_mwi().
 *
 * RETURNS: An appropriate -ERRNO error value on error, or zero क्रम success.
 */
पूर्णांक pcim_set_mwi(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_devres *dr;

	dr = find_pci_dr(dev);
	अगर (!dr)
		वापस -ENOMEM;

	dr->mwi = 1;
	वापस pci_set_mwi(dev);
पूर्ण
EXPORT_SYMBOL(pcim_set_mwi);

/**
 * pci_try_set_mwi - enables memory-ग_लिखो-invalidate PCI transaction
 * @dev: the PCI device क्रम which MWI is enabled
 *
 * Enables the Memory-Write-Invalidate transaction in %PCI_COMMAND.
 * Callers are not required to check the वापस value.
 *
 * RETURNS: An appropriate -ERRNO error value on error, or zero क्रम success.
 */
पूर्णांक pci_try_set_mwi(काष्ठा pci_dev *dev)
अणु
#अगर_घोषित PCI_DISABLE_MWI
	वापस 0;
#अन्यथा
	वापस pci_set_mwi(dev);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(pci_try_set_mwi);

/**
 * pci_clear_mwi - disables Memory-Write-Invalidate क्रम device dev
 * @dev: the PCI device to disable
 *
 * Disables PCI Memory-Write-Invalidate transaction on the device
 */
व्योम pci_clear_mwi(काष्ठा pci_dev *dev)
अणु
#अगर_अघोषित PCI_DISABLE_MWI
	u16 cmd;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	अगर (cmd & PCI_COMMAND_INVALIDATE) अणु
		cmd &= ~PCI_COMMAND_INVALIDATE;
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
	पूर्ण
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(pci_clear_mwi);

/**
 * pci_disable_parity - disable parity checking क्रम device
 * @dev: the PCI device to operate on
 *
 * Disable parity checking क्रम device @dev
 */
व्योम pci_disable_parity(काष्ठा pci_dev *dev)
अणु
	u16 cmd;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	अगर (cmd & PCI_COMMAND_PARITY) अणु
		cmd &= ~PCI_COMMAND_PARITY;
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
	पूर्ण
पूर्ण

/**
 * pci_पूर्णांकx - enables/disables PCI INTx क्रम device dev
 * @pdev: the PCI device to operate on
 * @enable: boolean: whether to enable or disable PCI INTx
 *
 * Enables/disables PCI INTx क्रम device @pdev
 */
व्योम pci_पूर्णांकx(काष्ठा pci_dev *pdev, पूर्णांक enable)
अणु
	u16 pci_command, new;

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &pci_command);

	अगर (enable)
		new = pci_command & ~PCI_COMMAND_INTX_DISABLE;
	अन्यथा
		new = pci_command | PCI_COMMAND_INTX_DISABLE;

	अगर (new != pci_command) अणु
		काष्ठा pci_devres *dr;

		pci_ग_लिखो_config_word(pdev, PCI_COMMAND, new);

		dr = find_pci_dr(pdev);
		अगर (dr && !dr->restore_पूर्णांकx) अणु
			dr->restore_पूर्णांकx = 1;
			dr->orig_पूर्णांकx = !enable;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pci_पूर्णांकx);

अटल bool pci_check_and_set_पूर्णांकx_mask(काष्ठा pci_dev *dev, bool mask)
अणु
	काष्ठा pci_bus *bus = dev->bus;
	bool mask_updated = true;
	u32 cmd_status_dword;
	u16 origcmd, newcmd;
	अचिन्हित दीर्घ flags;
	bool irq_pending;

	/*
	 * We करो a single dword पढ़ो to retrieve both command and status.
	 * Document assumptions that make this possible.
	 */
	BUILD_BUG_ON(PCI_COMMAND % 4);
	BUILD_BUG_ON(PCI_COMMAND + 2 != PCI_STATUS);

	raw_spin_lock_irqsave(&pci_lock, flags);

	bus->ops->पढ़ो(bus, dev->devfn, PCI_COMMAND, 4, &cmd_status_dword);

	irq_pending = (cmd_status_dword >> 16) & PCI_STATUS_INTERRUPT;

	/*
	 * Check पूर्णांकerrupt status रेजिस्टर to see whether our device
	 * triggered the पूर्णांकerrupt (when masking) or the next IRQ is
	 * alपढ़ोy pending (when unmasking).
	 */
	अगर (mask != irq_pending) अणु
		mask_updated = false;
		जाओ करोne;
	पूर्ण

	origcmd = cmd_status_dword;
	newcmd = origcmd & ~PCI_COMMAND_INTX_DISABLE;
	अगर (mask)
		newcmd |= PCI_COMMAND_INTX_DISABLE;
	अगर (newcmd != origcmd)
		bus->ops->ग_लिखो(bus, dev->devfn, PCI_COMMAND, 2, newcmd);

करोne:
	raw_spin_unlock_irqrestore(&pci_lock, flags);

	वापस mask_updated;
पूर्ण

/**
 * pci_check_and_mask_पूर्णांकx - mask INTx on pending पूर्णांकerrupt
 * @dev: the PCI device to operate on
 *
 * Check अगर the device dev has its INTx line निश्चितed, mask it and वापस
 * true in that हाल. False is वापसed अगर no पूर्णांकerrupt was pending.
 */
bool pci_check_and_mask_पूर्णांकx(काष्ठा pci_dev *dev)
अणु
	वापस pci_check_and_set_पूर्णांकx_mask(dev, true);
पूर्ण
EXPORT_SYMBOL_GPL(pci_check_and_mask_पूर्णांकx);

/**
 * pci_check_and_unmask_पूर्णांकx - unmask INTx अगर no पूर्णांकerrupt is pending
 * @dev: the PCI device to operate on
 *
 * Check अगर the device dev has its INTx line निश्चितed, unmask it अगर not and
 * वापस true. False is वापसed and the mask reमुख्यs active अगर there was
 * still an पूर्णांकerrupt pending.
 */
bool pci_check_and_unmask_पूर्णांकx(काष्ठा pci_dev *dev)
अणु
	वापस pci_check_and_set_पूर्णांकx_mask(dev, false);
पूर्ण
EXPORT_SYMBOL_GPL(pci_check_and_unmask_पूर्णांकx);

/**
 * pci_रुको_क्रम_pending_transaction - रुको क्रम pending transaction
 * @dev: the PCI device to operate on
 *
 * Return 0 अगर transaction is pending 1 otherwise.
 */
पूर्णांक pci_रुको_क्रम_pending_transaction(काष्ठा pci_dev *dev)
अणु
	अगर (!pci_is_pcie(dev))
		वापस 1;

	वापस pci_रुको_क्रम_pending(dev, pci_pcie_cap(dev) + PCI_EXP_DEVSTA,
				    PCI_EXP_DEVSTA_TRPND);
पूर्ण
EXPORT_SYMBOL(pci_रुको_क्रम_pending_transaction);

/**
 * pcie_has_flr - check अगर a device supports function level resets
 * @dev: device to check
 *
 * Returns true अगर the device advertises support क्रम PCIe function level
 * resets.
 */
bool pcie_has_flr(काष्ठा pci_dev *dev)
अणु
	u32 cap;

	अगर (dev->dev_flags & PCI_DEV_FLAGS_NO_FLR_RESET)
		वापस false;

	pcie_capability_पढ़ो_dword(dev, PCI_EXP_DEVCAP, &cap);
	वापस cap & PCI_EXP_DEVCAP_FLR;
पूर्ण
EXPORT_SYMBOL_GPL(pcie_has_flr);

/**
 * pcie_flr - initiate a PCIe function level reset
 * @dev: device to reset
 *
 * Initiate a function level reset on @dev.  The caller should ensure the
 * device supports FLR beक्रमe calling this function, e.g. by using the
 * pcie_has_flr() helper.
 */
पूर्णांक pcie_flr(काष्ठा pci_dev *dev)
अणु
	अगर (!pci_रुको_क्रम_pending_transaction(dev))
		pci_err(dev, "timed out waiting for pending transaction; performing function level reset anyway\n");

	pcie_capability_set_word(dev, PCI_EXP_DEVCTL, PCI_EXP_DEVCTL_BCR_FLR);

	अगर (dev->imm_पढ़ोy)
		वापस 0;

	/*
	 * Per PCIe r4.0, sec 6.6.2, a device must complete an FLR within
	 * 100ms, but may silently discard requests जबतक the FLR is in
	 * progress.  Wait 100ms beक्रमe trying to access the device.
	 */
	msleep(100);

	वापस pci_dev_रुको(dev, "FLR", PCIE_RESET_READY_POLL_MS);
पूर्ण
EXPORT_SYMBOL_GPL(pcie_flr);

अटल पूर्णांक pci_af_flr(काष्ठा pci_dev *dev, पूर्णांक probe)
अणु
	पूर्णांक pos;
	u8 cap;

	pos = pci_find_capability(dev, PCI_CAP_ID_AF);
	अगर (!pos)
		वापस -ENOTTY;

	अगर (dev->dev_flags & PCI_DEV_FLAGS_NO_FLR_RESET)
		वापस -ENOTTY;

	pci_पढ़ो_config_byte(dev, pos + PCI_AF_CAP, &cap);
	अगर (!(cap & PCI_AF_CAP_TP) || !(cap & PCI_AF_CAP_FLR))
		वापस -ENOTTY;

	अगर (probe)
		वापस 0;

	/*
	 * Wait क्रम Transaction Pending bit to clear.  A word-aligned test
	 * is used, so we use the control offset rather than status and shअगरt
	 * the test bit to match.
	 */
	अगर (!pci_रुको_क्रम_pending(dev, pos + PCI_AF_CTRL,
				 PCI_AF_STATUS_TP << 8))
		pci_err(dev, "timed out waiting for pending transaction; performing AF function level reset anyway\n");

	pci_ग_लिखो_config_byte(dev, pos + PCI_AF_CTRL, PCI_AF_CTRL_FLR);

	अगर (dev->imm_पढ़ोy)
		वापस 0;

	/*
	 * Per Advanced Capabilities क्रम Conventional PCI ECN, 13 April 2006,
	 * updated 27 July 2006; a device must complete an FLR within
	 * 100ms, but may silently discard requests जबतक the FLR is in
	 * progress.  Wait 100ms beक्रमe trying to access the device.
	 */
	msleep(100);

	वापस pci_dev_रुको(dev, "AF_FLR", PCIE_RESET_READY_POLL_MS);
पूर्ण

/**
 * pci_pm_reset - Put device पूर्णांकo PCI_D3 and back पूर्णांकo PCI_D0.
 * @dev: Device to reset.
 * @probe: If set, only check अगर the device can be reset this way.
 *
 * If @dev supports native PCI PM and its PCI_PM_CTRL_NO_SOFT_RESET flag is
 * unset, it will be reinitialized पूर्णांकernally when going from PCI_D3hot to
 * PCI_D0.  If that's the हाल and the device is not in a low-घातer state
 * alपढ़ोy, क्रमce it पूर्णांकo PCI_D3hot and back to PCI_D0, causing it to be reset.
 *
 * NOTE: This causes the caller to sleep क्रम twice the device घातer transition
 * coolकरोwn period, which क्रम the D0->D3hot and D3hot->D0 transitions is 10 ms
 * by शेष (i.e. unless the @dev's d3hot_delay field has a dअगरferent value).
 * Moreover, only devices in D0 can be reset by this function.
 */
अटल पूर्णांक pci_pm_reset(काष्ठा pci_dev *dev, पूर्णांक probe)
अणु
	u16 csr;

	अगर (!dev->pm_cap || dev->dev_flags & PCI_DEV_FLAGS_NO_PM_RESET)
		वापस -ENOTTY;

	pci_पढ़ो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &csr);
	अगर (csr & PCI_PM_CTRL_NO_SOFT_RESET)
		वापस -ENOTTY;

	अगर (probe)
		वापस 0;

	अगर (dev->current_state != PCI_D0)
		वापस -EINVAL;

	csr &= ~PCI_PM_CTRL_STATE_MASK;
	csr |= PCI_D3hot;
	pci_ग_लिखो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, csr);
	pci_dev_d3_sleep(dev);

	csr &= ~PCI_PM_CTRL_STATE_MASK;
	csr |= PCI_D0;
	pci_ग_लिखो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, csr);
	pci_dev_d3_sleep(dev);

	वापस pci_dev_रुको(dev, "PM D3hot->D0", PCIE_RESET_READY_POLL_MS);
पूर्ण

/**
 * pcie_रुको_क्रम_link_delay - Wait until link is active or inactive
 * @pdev: Bridge device
 * @active: रुकोing क्रम active or inactive?
 * @delay: Delay to रुको after link has become active (in ms)
 *
 * Use this to रुको till link becomes active or inactive.
 */
अटल bool pcie_रुको_क्रम_link_delay(काष्ठा pci_dev *pdev, bool active,
				     पूर्णांक delay)
अणु
	पूर्णांक समयout = 1000;
	bool ret;
	u16 lnk_status;

	/*
	 * Some controllers might not implement link active reporting. In this
	 * हाल, we रुको क्रम 1000 ms + any delay requested by the caller.
	 */
	अगर (!pdev->link_active_reporting) अणु
		msleep(समयout + delay);
		वापस true;
	पूर्ण

	/*
	 * PCIe r4.0 sec 6.6.1, a component must enter LTSSM Detect within 20ms,
	 * after which we should expect an link active अगर the reset was
	 * successful. If so, software must रुको a minimum 100ms beक्रमe sending
	 * configuration requests to devices करोwnstream this port.
	 *
	 * If the link fails to activate, either the device was physically
	 * हटाओd or the link is permanently failed.
	 */
	अगर (active)
		msleep(20);
	क्रम (;;) अणु
		pcie_capability_पढ़ो_word(pdev, PCI_EXP_LNKSTA, &lnk_status);
		ret = !!(lnk_status & PCI_EXP_LNKSTA_DLLLA);
		अगर (ret == active)
			अवरोध;
		अगर (समयout <= 0)
			अवरोध;
		msleep(10);
		समयout -= 10;
	पूर्ण
	अगर (active && ret)
		msleep(delay);

	वापस ret == active;
पूर्ण

/**
 * pcie_रुको_क्रम_link - Wait until link is active or inactive
 * @pdev: Bridge device
 * @active: रुकोing क्रम active or inactive?
 *
 * Use this to रुको till link becomes active or inactive.
 */
bool pcie_रुको_क्रम_link(काष्ठा pci_dev *pdev, bool active)
अणु
	वापस pcie_रुको_क्रम_link_delay(pdev, active, 100);
पूर्ण

/*
 * Find maximum D3cold delay required by all the devices on the bus.  The
 * spec says 100 ms, but firmware can lower it and we allow drivers to
 * increase it as well.
 *
 * Called with @pci_bus_sem locked क्रम पढ़ोing.
 */
अटल पूर्णांक pci_bus_max_d3cold_delay(स्थिर काष्ठा pci_bus *bus)
अणु
	स्थिर काष्ठा pci_dev *pdev;
	पूर्णांक min_delay = 100;
	पूर्णांक max_delay = 0;

	list_क्रम_each_entry(pdev, &bus->devices, bus_list) अणु
		अगर (pdev->d3cold_delay < min_delay)
			min_delay = pdev->d3cold_delay;
		अगर (pdev->d3cold_delay > max_delay)
			max_delay = pdev->d3cold_delay;
	पूर्ण

	वापस max(min_delay, max_delay);
पूर्ण

/**
 * pci_bridge_रुको_क्रम_secondary_bus - Wait क्रम secondary bus to be accessible
 * @dev: PCI bridge
 *
 * Handle necessary delays beक्रमe access to the devices on the secondary
 * side of the bridge are permitted after D3cold to D0 transition.
 *
 * For PCIe this means the delays in PCIe 5.0 section 6.6.1. For
 * conventional PCI it means Tpvrh + Trhfa specअगरied in PCI 3.0 section
 * 4.3.2.
 */
व्योम pci_bridge_रुको_क्रम_secondary_bus(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *child;
	पूर्णांक delay;

	अगर (pci_dev_is_disconnected(dev))
		वापस;

	अगर (!pci_is_bridge(dev) || !dev->bridge_d3)
		वापस;

	करोwn_पढ़ो(&pci_bus_sem);

	/*
	 * We only deal with devices that are present currently on the bus.
	 * For any hot-added devices the access delay is handled in pciehp
	 * board_added(). In हाल of ACPI hotplug the firmware is expected
	 * to configure the devices beक्रमe OS is notअगरied.
	 */
	अगर (!dev->subordinate || list_empty(&dev->subordinate->devices)) अणु
		up_पढ़ो(&pci_bus_sem);
		वापस;
	पूर्ण

	/* Take d3cold_delay requirements पूर्णांकo account */
	delay = pci_bus_max_d3cold_delay(dev->subordinate);
	अगर (!delay) अणु
		up_पढ़ो(&pci_bus_sem);
		वापस;
	पूर्ण

	child = list_first_entry(&dev->subordinate->devices, काष्ठा pci_dev,
				 bus_list);
	up_पढ़ो(&pci_bus_sem);

	/*
	 * Conventional PCI and PCI-X we need to रुको Tpvrh + Trhfa beक्रमe
	 * accessing the device after reset (that is 1000 ms + 100 ms). In
	 * practice this should not be needed because we करोn't करो घातer
	 * management क्रम them (see pci_bridge_d3_possible()).
	 */
	अगर (!pci_is_pcie(dev)) अणु
		pci_dbg(dev, "waiting %d ms for secondary bus\n", 1000 + delay);
		msleep(1000 + delay);
		वापस;
	पूर्ण

	/*
	 * For PCIe करोwnstream and root ports that करो not support speeds
	 * greater than 5 GT/s need to रुको minimum 100 ms. For higher
	 * speeds (gen3) we need to रुको first क्रम the data link layer to
	 * become active.
	 *
	 * However, 100 ms is the minimum and the PCIe spec says the
	 * software must allow at least 1s beक्रमe it can determine that the
	 * device that did not respond is a broken device. There is
	 * evidence that 100 ms is not always enough, क्रम example certain
	 * Titan Ridge xHCI controller करोes not always respond to
	 * configuration requests अगर we only रुको क्रम 100 ms (see
	 * https://bugzilla.kernel.org/show_bug.cgi?id=203885).
	 *
	 * Thereक्रमe we रुको क्रम 100 ms and check क्रम the device presence.
	 * If it is still not present give it an additional 100 ms.
	 */
	अगर (!pcie_करोwnstream_port(dev))
		वापस;

	अगर (pcie_get_speed_cap(dev) <= PCIE_SPEED_5_0GT) अणु
		pci_dbg(dev, "waiting %d ms for downstream link\n", delay);
		msleep(delay);
	पूर्ण अन्यथा अणु
		pci_dbg(dev, "waiting %d ms for downstream link, after activation\n",
			delay);
		अगर (!pcie_रुको_क्रम_link_delay(dev, true, delay)) अणु
			/* Did not train, no need to रुको any further */
			pci_info(dev, "Data Link Layer Link Active not set in 1000 msec\n");
			वापस;
		पूर्ण
	पूर्ण

	अगर (!pci_device_is_present(child)) अणु
		pci_dbg(child, "waiting additional %d ms to become accessible\n", delay);
		msleep(delay);
	पूर्ण
पूर्ण

व्योम pci_reset_secondary_bus(काष्ठा pci_dev *dev)
अणु
	u16 ctrl;

	pci_पढ़ो_config_word(dev, PCI_BRIDGE_CONTROL, &ctrl);
	ctrl |= PCI_BRIDGE_CTL_BUS_RESET;
	pci_ग_लिखो_config_word(dev, PCI_BRIDGE_CONTROL, ctrl);

	/*
	 * PCI spec v3.0 7.6.4.2 requires minimum Trst of 1ms.  Double
	 * this to 2ms to ensure that we meet the minimum requirement.
	 */
	msleep(2);

	ctrl &= ~PCI_BRIDGE_CTL_BUS_RESET;
	pci_ग_लिखो_config_word(dev, PCI_BRIDGE_CONTROL, ctrl);

	/*
	 * Trhfa क्रम conventional PCI is 2^25 घड़ी cycles.
	 * Assuming a minimum 33MHz घड़ी this results in a 1s
	 * delay beक्रमe we can consider subordinate devices to
	 * be re-initialized.  PCIe has some ways to लघुen this,
	 * but we करोn't make use of them yet.
	 */
	ssleep(1);
पूर्ण

व्योम __weak pcibios_reset_secondary_bus(काष्ठा pci_dev *dev)
अणु
	pci_reset_secondary_bus(dev);
पूर्ण

/**
 * pci_bridge_secondary_bus_reset - Reset the secondary bus on a PCI bridge.
 * @dev: Bridge device
 *
 * Use the bridge control रेजिस्टर to निश्चित reset on the secondary bus.
 * Devices on the secondary bus are left in घातer-on state.
 */
पूर्णांक pci_bridge_secondary_bus_reset(काष्ठा pci_dev *dev)
अणु
	pcibios_reset_secondary_bus(dev);

	वापस pci_dev_रुको(dev, "bus reset", PCIE_RESET_READY_POLL_MS);
पूर्ण
EXPORT_SYMBOL_GPL(pci_bridge_secondary_bus_reset);

अटल पूर्णांक pci_parent_bus_reset(काष्ठा pci_dev *dev, पूर्णांक probe)
अणु
	काष्ठा pci_dev *pdev;

	अगर (pci_is_root_bus(dev->bus) || dev->subordinate ||
	    !dev->bus->self || dev->dev_flags & PCI_DEV_FLAGS_NO_BUS_RESET)
		वापस -ENOTTY;

	list_क्रम_each_entry(pdev, &dev->bus->devices, bus_list)
		अगर (pdev != dev)
			वापस -ENOTTY;

	अगर (probe)
		वापस 0;

	वापस pci_bridge_secondary_bus_reset(dev->bus->self);
पूर्ण

अटल पूर्णांक pci_reset_hotplug_slot(काष्ठा hotplug_slot *hotplug, पूर्णांक probe)
अणु
	पूर्णांक rc = -ENOTTY;

	अगर (!hotplug || !try_module_get(hotplug->owner))
		वापस rc;

	अगर (hotplug->ops->reset_slot)
		rc = hotplug->ops->reset_slot(hotplug, probe);

	module_put(hotplug->owner);

	वापस rc;
पूर्ण

अटल पूर्णांक pci_dev_reset_slot_function(काष्ठा pci_dev *dev, पूर्णांक probe)
अणु
	अगर (dev->multअगरunction || dev->subordinate || !dev->slot ||
	    dev->dev_flags & PCI_DEV_FLAGS_NO_BUS_RESET)
		वापस -ENOTTY;

	वापस pci_reset_hotplug_slot(dev->slot->hotplug, probe);
पूर्ण

अटल व्योम pci_dev_lock(काष्ठा pci_dev *dev)
अणु
	pci_cfg_access_lock(dev);
	/* block PM suspend, driver probe, etc. */
	device_lock(&dev->dev);
पूर्ण

/* Return 1 on successful lock, 0 on contention */
अटल पूर्णांक pci_dev_trylock(काष्ठा pci_dev *dev)
अणु
	अगर (pci_cfg_access_trylock(dev)) अणु
		अगर (device_trylock(&dev->dev))
			वापस 1;
		pci_cfg_access_unlock(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pci_dev_unlock(काष्ठा pci_dev *dev)
अणु
	device_unlock(&dev->dev);
	pci_cfg_access_unlock(dev);
पूर्ण

अटल व्योम pci_dev_save_and_disable(काष्ठा pci_dev *dev)
अणु
	स्थिर काष्ठा pci_error_handlers *err_handler =
			dev->driver ? dev->driver->err_handler : शून्य;

	/*
	 * dev->driver->err_handler->reset_prepare() is रक्षित against
	 * races with ->हटाओ() by the device lock, which must be held by
	 * the caller.
	 */
	अगर (err_handler && err_handler->reset_prepare)
		err_handler->reset_prepare(dev);

	/*
	 * Wake-up device prior to save.  PM रेजिस्टरs शेष to D0 after
	 * reset and a simple रेजिस्टर restore करोesn't reliably वापस
	 * to a non-D0 state anyway.
	 */
	pci_set_घातer_state(dev, PCI_D0);

	pci_save_state(dev);
	/*
	 * Disable the device by clearing the Command रेजिस्टर, except क्रम
	 * INTx-disable which is set.  This not only disables MMIO and I/O port
	 * BARs, but also prevents the device from being Bus Master, preventing
	 * DMA from the device including MSI/MSI-X पूर्णांकerrupts.  For PCI 2.3
	 * compliant devices, INTx-disable prevents legacy पूर्णांकerrupts.
	 */
	pci_ग_लिखो_config_word(dev, PCI_COMMAND, PCI_COMMAND_INTX_DISABLE);
पूर्ण

अटल व्योम pci_dev_restore(काष्ठा pci_dev *dev)
अणु
	स्थिर काष्ठा pci_error_handlers *err_handler =
			dev->driver ? dev->driver->err_handler : शून्य;

	pci_restore_state(dev);

	/*
	 * dev->driver->err_handler->reset_करोne() is रक्षित against
	 * races with ->हटाओ() by the device lock, which must be held by
	 * the caller.
	 */
	अगर (err_handler && err_handler->reset_करोne)
		err_handler->reset_करोne(dev);
पूर्ण

/**
 * __pci_reset_function_locked - reset a PCI device function जबतक holding
 * the @dev mutex lock.
 * @dev: PCI device to reset
 *
 * Some devices allow an inभागidual function to be reset without affecting
 * other functions in the same device.  The PCI device must be responsive
 * to PCI config space in order to use this function.
 *
 * The device function is presumed to be unused and the caller is holding
 * the device mutex lock when this function is called.
 *
 * Resetting the device will make the contents of PCI configuration space
 * अक्रमom, so any caller of this must be prepared to reinitialise the
 * device including MSI, bus mastering, BARs, decoding IO and memory spaces,
 * etc.
 *
 * Returns 0 अगर the device function was successfully reset or negative अगर the
 * device करोesn't support resetting a single function.
 */
पूर्णांक __pci_reset_function_locked(काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc;

	might_sleep();

	/*
	 * A reset method वापसs -ENOTTY अगर it करोesn't support this device
	 * and we should try the next method.
	 *
	 * If it वापसs 0 (success), we're finished.  If it वापसs any
	 * other error, we're also finished: this indicates that further
	 * reset mechanisms might be broken on the device.
	 */
	rc = pci_dev_specअगरic_reset(dev, 0);
	अगर (rc != -ENOTTY)
		वापस rc;
	अगर (pcie_has_flr(dev)) अणु
		rc = pcie_flr(dev);
		अगर (rc != -ENOTTY)
			वापस rc;
	पूर्ण
	rc = pci_af_flr(dev, 0);
	अगर (rc != -ENOTTY)
		वापस rc;
	rc = pci_pm_reset(dev, 0);
	अगर (rc != -ENOTTY)
		वापस rc;
	rc = pci_dev_reset_slot_function(dev, 0);
	अगर (rc != -ENOTTY)
		वापस rc;
	वापस pci_parent_bus_reset(dev, 0);
पूर्ण
EXPORT_SYMBOL_GPL(__pci_reset_function_locked);

/**
 * pci_probe_reset_function - check whether the device can be safely reset
 * @dev: PCI device to reset
 *
 * Some devices allow an inभागidual function to be reset without affecting
 * other functions in the same device.  The PCI device must be responsive
 * to PCI config space in order to use this function.
 *
 * Returns 0 अगर the device function can be reset or negative अगर the
 * device करोesn't support resetting a single function.
 */
पूर्णांक pci_probe_reset_function(काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc;

	might_sleep();

	rc = pci_dev_specअगरic_reset(dev, 1);
	अगर (rc != -ENOTTY)
		वापस rc;
	अगर (pcie_has_flr(dev))
		वापस 0;
	rc = pci_af_flr(dev, 1);
	अगर (rc != -ENOTTY)
		वापस rc;
	rc = pci_pm_reset(dev, 1);
	अगर (rc != -ENOTTY)
		वापस rc;
	rc = pci_dev_reset_slot_function(dev, 1);
	अगर (rc != -ENOTTY)
		वापस rc;

	वापस pci_parent_bus_reset(dev, 1);
पूर्ण

/**
 * pci_reset_function - quiesce and reset a PCI device function
 * @dev: PCI device to reset
 *
 * Some devices allow an inभागidual function to be reset without affecting
 * other functions in the same device.  The PCI device must be responsive
 * to PCI config space in order to use this function.
 *
 * This function करोes not just reset the PCI portion of a device, but
 * clears all the state associated with the device.  This function dअगरfers
 * from __pci_reset_function_locked() in that it saves and restores device state
 * over the reset and takes the PCI device lock.
 *
 * Returns 0 अगर the device function was successfully reset or negative अगर the
 * device करोesn't support resetting a single function.
 */
पूर्णांक pci_reset_function(काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc;

	अगर (!dev->reset_fn)
		वापस -ENOTTY;

	pci_dev_lock(dev);
	pci_dev_save_and_disable(dev);

	rc = __pci_reset_function_locked(dev);

	pci_dev_restore(dev);
	pci_dev_unlock(dev);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pci_reset_function);

/**
 * pci_reset_function_locked - quiesce and reset a PCI device function
 * @dev: PCI device to reset
 *
 * Some devices allow an inभागidual function to be reset without affecting
 * other functions in the same device.  The PCI device must be responsive
 * to PCI config space in order to use this function.
 *
 * This function करोes not just reset the PCI portion of a device, but
 * clears all the state associated with the device.  This function dअगरfers
 * from __pci_reset_function_locked() in that it saves and restores device state
 * over the reset.  It also dअगरfers from pci_reset_function() in that it
 * requires the PCI device lock to be held.
 *
 * Returns 0 अगर the device function was successfully reset or negative अगर the
 * device करोesn't support resetting a single function.
 */
पूर्णांक pci_reset_function_locked(काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc;

	अगर (!dev->reset_fn)
		वापस -ENOTTY;

	pci_dev_save_and_disable(dev);

	rc = __pci_reset_function_locked(dev);

	pci_dev_restore(dev);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pci_reset_function_locked);

/**
 * pci_try_reset_function - quiesce and reset a PCI device function
 * @dev: PCI device to reset
 *
 * Same as above, except वापस -EAGAIN अगर unable to lock device.
 */
पूर्णांक pci_try_reset_function(काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc;

	अगर (!dev->reset_fn)
		वापस -ENOTTY;

	अगर (!pci_dev_trylock(dev))
		वापस -EAGAIN;

	pci_dev_save_and_disable(dev);
	rc = __pci_reset_function_locked(dev);
	pci_dev_restore(dev);
	pci_dev_unlock(dev);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pci_try_reset_function);

/* Do any devices on or below this bus prevent a bus reset? */
अटल bool pci_bus_resetable(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;


	अगर (bus->self && (bus->self->dev_flags & PCI_DEV_FLAGS_NO_BUS_RESET))
		वापस false;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		अगर (dev->dev_flags & PCI_DEV_FLAGS_NO_BUS_RESET ||
		    (dev->subordinate && !pci_bus_resetable(dev->subordinate)))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Lock devices from the top of the tree करोwn */
अटल व्योम pci_bus_lock(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		pci_dev_lock(dev);
		अगर (dev->subordinate)
			pci_bus_lock(dev->subordinate);
	पूर्ण
पूर्ण

/* Unlock devices from the bottom of the tree up */
अटल व्योम pci_bus_unlock(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		अगर (dev->subordinate)
			pci_bus_unlock(dev->subordinate);
		pci_dev_unlock(dev);
	पूर्ण
पूर्ण

/* Return 1 on successful lock, 0 on contention */
अटल पूर्णांक pci_bus_trylock(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		अगर (!pci_dev_trylock(dev))
			जाओ unlock;
		अगर (dev->subordinate) अणु
			अगर (!pci_bus_trylock(dev->subordinate)) अणु
				pci_dev_unlock(dev);
				जाओ unlock;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 1;

unlock:
	list_क्रम_each_entry_जारी_reverse(dev, &bus->devices, bus_list) अणु
		अगर (dev->subordinate)
			pci_bus_unlock(dev->subordinate);
		pci_dev_unlock(dev);
	पूर्ण
	वापस 0;
पूर्ण

/* Do any devices on or below this slot prevent a bus reset? */
अटल bool pci_slot_resetable(काष्ठा pci_slot *slot)
अणु
	काष्ठा pci_dev *dev;

	अगर (slot->bus->self &&
	    (slot->bus->self->dev_flags & PCI_DEV_FLAGS_NO_BUS_RESET))
		वापस false;

	list_क्रम_each_entry(dev, &slot->bus->devices, bus_list) अणु
		अगर (!dev->slot || dev->slot != slot)
			जारी;
		अगर (dev->dev_flags & PCI_DEV_FLAGS_NO_BUS_RESET ||
		    (dev->subordinate && !pci_bus_resetable(dev->subordinate)))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Lock devices from the top of the tree करोwn */
अटल व्योम pci_slot_lock(काष्ठा pci_slot *slot)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &slot->bus->devices, bus_list) अणु
		अगर (!dev->slot || dev->slot != slot)
			जारी;
		pci_dev_lock(dev);
		अगर (dev->subordinate)
			pci_bus_lock(dev->subordinate);
	पूर्ण
पूर्ण

/* Unlock devices from the bottom of the tree up */
अटल व्योम pci_slot_unlock(काष्ठा pci_slot *slot)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &slot->bus->devices, bus_list) अणु
		अगर (!dev->slot || dev->slot != slot)
			जारी;
		अगर (dev->subordinate)
			pci_bus_unlock(dev->subordinate);
		pci_dev_unlock(dev);
	पूर्ण
पूर्ण

/* Return 1 on successful lock, 0 on contention */
अटल पूर्णांक pci_slot_trylock(काष्ठा pci_slot *slot)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &slot->bus->devices, bus_list) अणु
		अगर (!dev->slot || dev->slot != slot)
			जारी;
		अगर (!pci_dev_trylock(dev))
			जाओ unlock;
		अगर (dev->subordinate) अणु
			अगर (!pci_bus_trylock(dev->subordinate)) अणु
				pci_dev_unlock(dev);
				जाओ unlock;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 1;

unlock:
	list_क्रम_each_entry_जारी_reverse(dev,
					     &slot->bus->devices, bus_list) अणु
		अगर (!dev->slot || dev->slot != slot)
			जारी;
		अगर (dev->subordinate)
			pci_bus_unlock(dev->subordinate);
		pci_dev_unlock(dev);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Save and disable devices from the top of the tree करोwn जबतक holding
 * the @dev mutex lock क्रम the entire tree.
 */
अटल व्योम pci_bus_save_and_disable_locked(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		pci_dev_save_and_disable(dev);
		अगर (dev->subordinate)
			pci_bus_save_and_disable_locked(dev->subordinate);
	पूर्ण
पूर्ण

/*
 * Restore devices from top of the tree करोwn जबतक holding @dev mutex lock
 * क्रम the entire tree.  Parent bridges need to be restored beक्रमe we can
 * get to subordinate devices.
 */
अटल व्योम pci_bus_restore_locked(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		pci_dev_restore(dev);
		अगर (dev->subordinate)
			pci_bus_restore_locked(dev->subordinate);
	पूर्ण
पूर्ण

/*
 * Save and disable devices from the top of the tree करोwn जबतक holding
 * the @dev mutex lock क्रम the entire tree.
 */
अटल व्योम pci_slot_save_and_disable_locked(काष्ठा pci_slot *slot)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &slot->bus->devices, bus_list) अणु
		अगर (!dev->slot || dev->slot != slot)
			जारी;
		pci_dev_save_and_disable(dev);
		अगर (dev->subordinate)
			pci_bus_save_and_disable_locked(dev->subordinate);
	पूर्ण
पूर्ण

/*
 * Restore devices from top of the tree करोwn जबतक holding @dev mutex lock
 * क्रम the entire tree.  Parent bridges need to be restored beक्रमe we can
 * get to subordinate devices.
 */
अटल व्योम pci_slot_restore_locked(काष्ठा pci_slot *slot)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &slot->bus->devices, bus_list) अणु
		अगर (!dev->slot || dev->slot != slot)
			जारी;
		pci_dev_restore(dev);
		अगर (dev->subordinate)
			pci_bus_restore_locked(dev->subordinate);
	पूर्ण
पूर्ण

अटल पूर्णांक pci_slot_reset(काष्ठा pci_slot *slot, पूर्णांक probe)
अणु
	पूर्णांक rc;

	अगर (!slot || !pci_slot_resetable(slot))
		वापस -ENOTTY;

	अगर (!probe)
		pci_slot_lock(slot);

	might_sleep();

	rc = pci_reset_hotplug_slot(slot->hotplug, probe);

	अगर (!probe)
		pci_slot_unlock(slot);

	वापस rc;
पूर्ण

/**
 * pci_probe_reset_slot - probe whether a PCI slot can be reset
 * @slot: PCI slot to probe
 *
 * Return 0 अगर slot can be reset, negative अगर a slot reset is not supported.
 */
पूर्णांक pci_probe_reset_slot(काष्ठा pci_slot *slot)
अणु
	वापस pci_slot_reset(slot, 1);
पूर्ण
EXPORT_SYMBOL_GPL(pci_probe_reset_slot);

/**
 * __pci_reset_slot - Try to reset a PCI slot
 * @slot: PCI slot to reset
 *
 * A PCI bus may host multiple slots, each slot may support a reset mechanism
 * independent of other slots.  For instance, some slots may support slot घातer
 * control.  In the हाल of a 1:1 bus to slot architecture, this function may
 * wrap the bus reset to aव्योम spurious slot related events such as hotplug.
 * Generally a slot reset should be attempted beक्रमe a bus reset.  All of the
 * function of the slot and any subordinate buses behind the slot are reset
 * through this function.  PCI config space of all devices in the slot and
 * behind the slot is saved beक्रमe and restored after reset.
 *
 * Same as above except वापस -EAGAIN अगर the slot cannot be locked
 */
अटल पूर्णांक __pci_reset_slot(काष्ठा pci_slot *slot)
अणु
	पूर्णांक rc;

	rc = pci_slot_reset(slot, 1);
	अगर (rc)
		वापस rc;

	अगर (pci_slot_trylock(slot)) अणु
		pci_slot_save_and_disable_locked(slot);
		might_sleep();
		rc = pci_reset_hotplug_slot(slot->hotplug, 0);
		pci_slot_restore_locked(slot);
		pci_slot_unlock(slot);
	पूर्ण अन्यथा
		rc = -EAGAIN;

	वापस rc;
पूर्ण

अटल पूर्णांक pci_bus_reset(काष्ठा pci_bus *bus, पूर्णांक probe)
अणु
	पूर्णांक ret;

	अगर (!bus->self || !pci_bus_resetable(bus))
		वापस -ENOTTY;

	अगर (probe)
		वापस 0;

	pci_bus_lock(bus);

	might_sleep();

	ret = pci_bridge_secondary_bus_reset(bus->self);

	pci_bus_unlock(bus);

	वापस ret;
पूर्ण

/**
 * pci_bus_error_reset - reset the bridge's subordinate bus
 * @bridge: The parent device that connects to the bus to reset
 *
 * This function will first try to reset the slots on this bus अगर the method is
 * available. If slot reset fails or is not available, this will fall back to a
 * secondary bus reset.
 */
पूर्णांक pci_bus_error_reset(काष्ठा pci_dev *bridge)
अणु
	काष्ठा pci_bus *bus = bridge->subordinate;
	काष्ठा pci_slot *slot;

	अगर (!bus)
		वापस -ENOTTY;

	mutex_lock(&pci_slot_mutex);
	अगर (list_empty(&bus->slots))
		जाओ bus_reset;

	list_क्रम_each_entry(slot, &bus->slots, list)
		अगर (pci_probe_reset_slot(slot))
			जाओ bus_reset;

	list_क्रम_each_entry(slot, &bus->slots, list)
		अगर (pci_slot_reset(slot, 0))
			जाओ bus_reset;

	mutex_unlock(&pci_slot_mutex);
	वापस 0;
bus_reset:
	mutex_unlock(&pci_slot_mutex);
	वापस pci_bus_reset(bridge->subordinate, 0);
पूर्ण

/**
 * pci_probe_reset_bus - probe whether a PCI bus can be reset
 * @bus: PCI bus to probe
 *
 * Return 0 अगर bus can be reset, negative अगर a bus reset is not supported.
 */
पूर्णांक pci_probe_reset_bus(काष्ठा pci_bus *bus)
अणु
	वापस pci_bus_reset(bus, 1);
पूर्ण
EXPORT_SYMBOL_GPL(pci_probe_reset_bus);

/**
 * __pci_reset_bus - Try to reset a PCI bus
 * @bus: top level PCI bus to reset
 *
 * Same as above except वापस -EAGAIN अगर the bus cannot be locked
 */
अटल पूर्णांक __pci_reset_bus(काष्ठा pci_bus *bus)
अणु
	पूर्णांक rc;

	rc = pci_bus_reset(bus, 1);
	अगर (rc)
		वापस rc;

	अगर (pci_bus_trylock(bus)) अणु
		pci_bus_save_and_disable_locked(bus);
		might_sleep();
		rc = pci_bridge_secondary_bus_reset(bus->self);
		pci_bus_restore_locked(bus);
		pci_bus_unlock(bus);
	पूर्ण अन्यथा
		rc = -EAGAIN;

	वापस rc;
पूर्ण

/**
 * pci_reset_bus - Try to reset a PCI bus
 * @pdev: top level PCI device to reset via slot/bus
 *
 * Same as above except वापस -EAGAIN अगर the bus cannot be locked
 */
पूर्णांक pci_reset_bus(काष्ठा pci_dev *pdev)
अणु
	वापस (!pci_probe_reset_slot(pdev->slot)) ?
	    __pci_reset_slot(pdev->slot) : __pci_reset_bus(pdev->bus);
पूर्ण
EXPORT_SYMBOL_GPL(pci_reset_bus);

/**
 * pcix_get_max_mmrbc - get PCI-X maximum deचिन्हित memory पढ़ो byte count
 * @dev: PCI device to query
 *
 * Returns mmrbc: maximum deचिन्हित memory पढ़ो count in bytes or
 * appropriate error value.
 */
पूर्णांक pcix_get_max_mmrbc(काष्ठा pci_dev *dev)
अणु
	पूर्णांक cap;
	u32 stat;

	cap = pci_find_capability(dev, PCI_CAP_ID_PCIX);
	अगर (!cap)
		वापस -EINVAL;

	अगर (pci_पढ़ो_config_dword(dev, cap + PCI_X_STATUS, &stat))
		वापस -EINVAL;

	वापस 512 << ((stat & PCI_X_STATUS_MAX_READ) >> 21);
पूर्ण
EXPORT_SYMBOL(pcix_get_max_mmrbc);

/**
 * pcix_get_mmrbc - get PCI-X maximum memory पढ़ो byte count
 * @dev: PCI device to query
 *
 * Returns mmrbc: maximum memory पढ़ो count in bytes or appropriate error
 * value.
 */
पूर्णांक pcix_get_mmrbc(काष्ठा pci_dev *dev)
अणु
	पूर्णांक cap;
	u16 cmd;

	cap = pci_find_capability(dev, PCI_CAP_ID_PCIX);
	अगर (!cap)
		वापस -EINVAL;

	अगर (pci_पढ़ो_config_word(dev, cap + PCI_X_CMD, &cmd))
		वापस -EINVAL;

	वापस 512 << ((cmd & PCI_X_CMD_MAX_READ) >> 2);
पूर्ण
EXPORT_SYMBOL(pcix_get_mmrbc);

/**
 * pcix_set_mmrbc - set PCI-X maximum memory पढ़ो byte count
 * @dev: PCI device to query
 * @mmrbc: maximum memory पढ़ो count in bytes
 *    valid values are 512, 1024, 2048, 4096
 *
 * If possible sets maximum memory पढ़ो byte count, some bridges have errata
 * that prevent this.
 */
पूर्णांक pcix_set_mmrbc(काष्ठा pci_dev *dev, पूर्णांक mmrbc)
अणु
	पूर्णांक cap;
	u32 stat, v, o;
	u16 cmd;

	अगर (mmrbc < 512 || mmrbc > 4096 || !is_घातer_of_2(mmrbc))
		वापस -EINVAL;

	v = ffs(mmrbc) - 10;

	cap = pci_find_capability(dev, PCI_CAP_ID_PCIX);
	अगर (!cap)
		वापस -EINVAL;

	अगर (pci_पढ़ो_config_dword(dev, cap + PCI_X_STATUS, &stat))
		वापस -EINVAL;

	अगर (v > (stat & PCI_X_STATUS_MAX_READ) >> 21)
		वापस -E2BIG;

	अगर (pci_पढ़ो_config_word(dev, cap + PCI_X_CMD, &cmd))
		वापस -EINVAL;

	o = (cmd & PCI_X_CMD_MAX_READ) >> 2;
	अगर (o != v) अणु
		अगर (v > o && (dev->bus->bus_flags & PCI_BUS_FLAGS_NO_MMRBC))
			वापस -EIO;

		cmd &= ~PCI_X_CMD_MAX_READ;
		cmd |= v << 2;
		अगर (pci_ग_लिखो_config_word(dev, cap + PCI_X_CMD, cmd))
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(pcix_set_mmrbc);

/**
 * pcie_get_पढ़ोrq - get PCI Express पढ़ो request size
 * @dev: PCI device to query
 *
 * Returns maximum memory पढ़ो request in bytes or appropriate error value.
 */
पूर्णांक pcie_get_पढ़ोrq(काष्ठा pci_dev *dev)
अणु
	u16 ctl;

	pcie_capability_पढ़ो_word(dev, PCI_EXP_DEVCTL, &ctl);

	वापस 128 << ((ctl & PCI_EXP_DEVCTL_READRQ) >> 12);
पूर्ण
EXPORT_SYMBOL(pcie_get_पढ़ोrq);

/**
 * pcie_set_पढ़ोrq - set PCI Express maximum memory पढ़ो request
 * @dev: PCI device to query
 * @rq: maximum memory पढ़ो count in bytes
 *    valid values are 128, 256, 512, 1024, 2048, 4096
 *
 * If possible sets maximum memory पढ़ो request in bytes
 */
पूर्णांक pcie_set_पढ़ोrq(काष्ठा pci_dev *dev, पूर्णांक rq)
अणु
	u16 v;
	पूर्णांक ret;

	अगर (rq < 128 || rq > 4096 || !is_घातer_of_2(rq))
		वापस -EINVAL;

	/*
	 * If using the "performance" PCIe config, we clamp the पढ़ो rq
	 * size to the max packet size to keep the host bridge from
	 * generating requests larger than we can cope with.
	 */
	अगर (pcie_bus_config == PCIE_BUS_PERFORMANCE) अणु
		पूर्णांक mps = pcie_get_mps(dev);

		अगर (mps < rq)
			rq = mps;
	पूर्ण

	v = (ffs(rq) - 8) << 12;

	ret = pcie_capability_clear_and_set_word(dev, PCI_EXP_DEVCTL,
						  PCI_EXP_DEVCTL_READRQ, v);

	वापस pcibios_err_to_त्रुटि_सं(ret);
पूर्ण
EXPORT_SYMBOL(pcie_set_पढ़ोrq);

/**
 * pcie_get_mps - get PCI Express maximum payload size
 * @dev: PCI device to query
 *
 * Returns maximum payload size in bytes
 */
पूर्णांक pcie_get_mps(काष्ठा pci_dev *dev)
अणु
	u16 ctl;

	pcie_capability_पढ़ो_word(dev, PCI_EXP_DEVCTL, &ctl);

	वापस 128 << ((ctl & PCI_EXP_DEVCTL_PAYLOAD) >> 5);
पूर्ण
EXPORT_SYMBOL(pcie_get_mps);

/**
 * pcie_set_mps - set PCI Express maximum payload size
 * @dev: PCI device to query
 * @mps: maximum payload size in bytes
 *    valid values are 128, 256, 512, 1024, 2048, 4096
 *
 * If possible sets maximum payload size
 */
पूर्णांक pcie_set_mps(काष्ठा pci_dev *dev, पूर्णांक mps)
अणु
	u16 v;
	पूर्णांक ret;

	अगर (mps < 128 || mps > 4096 || !is_घातer_of_2(mps))
		वापस -EINVAL;

	v = ffs(mps) - 8;
	अगर (v > dev->pcie_mpss)
		वापस -EINVAL;
	v <<= 5;

	ret = pcie_capability_clear_and_set_word(dev, PCI_EXP_DEVCTL,
						  PCI_EXP_DEVCTL_PAYLOAD, v);

	वापस pcibios_err_to_त्रुटि_सं(ret);
पूर्ण
EXPORT_SYMBOL(pcie_set_mps);

/**
 * pcie_bandwidth_available - determine minimum link settings of a PCIe
 *			      device and its bandwidth limitation
 * @dev: PCI device to query
 * @limiting_dev: storage क्रम device causing the bandwidth limitation
 * @speed: storage क्रम speed of limiting device
 * @width: storage क्रम width of limiting device
 *
 * Walk up the PCI device chain and find the poपूर्णांक where the minimum
 * bandwidth is available.  Return the bandwidth available there and (अगर
 * limiting_dev, speed, and width poपूर्णांकers are supplied) inक्रमmation about
 * that poपूर्णांक.  The bandwidth वापसed is in Mb/s, i.e., megabits/second of
 * raw bandwidth.
 */
u32 pcie_bandwidth_available(काष्ठा pci_dev *dev, काष्ठा pci_dev **limiting_dev,
			     क्रमागत pci_bus_speed *speed,
			     क्रमागत pcie_link_width *width)
अणु
	u16 lnksta;
	क्रमागत pci_bus_speed next_speed;
	क्रमागत pcie_link_width next_width;
	u32 bw, next_bw;

	अगर (speed)
		*speed = PCI_SPEED_UNKNOWN;
	अगर (width)
		*width = PCIE_LNK_WIDTH_UNKNOWN;

	bw = 0;

	जबतक (dev) अणु
		pcie_capability_पढ़ो_word(dev, PCI_EXP_LNKSTA, &lnksta);

		next_speed = pcie_link_speed[lnksta & PCI_EXP_LNKSTA_CLS];
		next_width = (lnksta & PCI_EXP_LNKSTA_NLW) >>
			PCI_EXP_LNKSTA_NLW_SHIFT;

		next_bw = next_width * PCIE_SPEED2MBS_ENC(next_speed);

		/* Check अगर current device limits the total bandwidth */
		अगर (!bw || next_bw <= bw) अणु
			bw = next_bw;

			अगर (limiting_dev)
				*limiting_dev = dev;
			अगर (speed)
				*speed = next_speed;
			अगर (width)
				*width = next_width;
		पूर्ण

		dev = pci_upstream_bridge(dev);
	पूर्ण

	वापस bw;
पूर्ण
EXPORT_SYMBOL(pcie_bandwidth_available);

/**
 * pcie_get_speed_cap - query क्रम the PCI device's link speed capability
 * @dev: PCI device to query
 *
 * Query the PCI device speed capability.  Return the maximum link speed
 * supported by the device.
 */
क्रमागत pci_bus_speed pcie_get_speed_cap(काष्ठा pci_dev *dev)
अणु
	u32 lnkcap2, lnkcap;

	/*
	 * Link Capabilities 2 was added in PCIe r3.0, sec 7.8.18.  The
	 * implementation note there recommends using the Supported Link
	 * Speeds Vector in Link Capabilities 2 when supported.
	 *
	 * Without Link Capabilities 2, i.e., prior to PCIe r3.0, software
	 * should use the Supported Link Speeds field in Link Capabilities,
	 * where only 2.5 GT/s and 5.0 GT/s speeds were defined.
	 */
	pcie_capability_पढ़ो_dword(dev, PCI_EXP_LNKCAP2, &lnkcap2);

	/* PCIe r3.0-compliant */
	अगर (lnkcap2)
		वापस PCIE_LNKCAP2_SLS2SPEED(lnkcap2);

	pcie_capability_पढ़ो_dword(dev, PCI_EXP_LNKCAP, &lnkcap);
	अगर ((lnkcap & PCI_EXP_LNKCAP_SLS) == PCI_EXP_LNKCAP_SLS_5_0GB)
		वापस PCIE_SPEED_5_0GT;
	अन्यथा अगर ((lnkcap & PCI_EXP_LNKCAP_SLS) == PCI_EXP_LNKCAP_SLS_2_5GB)
		वापस PCIE_SPEED_2_5GT;

	वापस PCI_SPEED_UNKNOWN;
पूर्ण
EXPORT_SYMBOL(pcie_get_speed_cap);

/**
 * pcie_get_width_cap - query क्रम the PCI device's link width capability
 * @dev: PCI device to query
 *
 * Query the PCI device width capability.  Return the maximum link width
 * supported by the device.
 */
क्रमागत pcie_link_width pcie_get_width_cap(काष्ठा pci_dev *dev)
अणु
	u32 lnkcap;

	pcie_capability_पढ़ो_dword(dev, PCI_EXP_LNKCAP, &lnkcap);
	अगर (lnkcap)
		वापस (lnkcap & PCI_EXP_LNKCAP_MLW) >> 4;

	वापस PCIE_LNK_WIDTH_UNKNOWN;
पूर्ण
EXPORT_SYMBOL(pcie_get_width_cap);

/**
 * pcie_bandwidth_capable - calculate a PCI device's link bandwidth capability
 * @dev: PCI device
 * @speed: storage क्रम link speed
 * @width: storage क्रम link width
 *
 * Calculate a PCI device's link bandwidth by querying क्रम its link speed
 * and width, multiplying them, and applying encoding overhead.  The result
 * is in Mb/s, i.e., megabits/second of raw bandwidth.
 */
u32 pcie_bandwidth_capable(काष्ठा pci_dev *dev, क्रमागत pci_bus_speed *speed,
			   क्रमागत pcie_link_width *width)
अणु
	*speed = pcie_get_speed_cap(dev);
	*width = pcie_get_width_cap(dev);

	अगर (*speed == PCI_SPEED_UNKNOWN || *width == PCIE_LNK_WIDTH_UNKNOWN)
		वापस 0;

	वापस *width * PCIE_SPEED2MBS_ENC(*speed);
पूर्ण

/**
 * __pcie_prपूर्णांक_link_status - Report the PCI device's link speed and width
 * @dev: PCI device to query
 * @verbose: Prपूर्णांक info even when enough bandwidth is available
 *
 * If the available bandwidth at the device is less than the device is
 * capable of, report the device's maximum possible bandwidth and the
 * upstream link that limits its perक्रमmance.  If @verbose, always prपूर्णांक
 * the available bandwidth, even अगर the device isn't स्थिरrained.
 */
व्योम __pcie_prपूर्णांक_link_status(काष्ठा pci_dev *dev, bool verbose)
अणु
	क्रमागत pcie_link_width width, width_cap;
	क्रमागत pci_bus_speed speed, speed_cap;
	काष्ठा pci_dev *limiting_dev = शून्य;
	u32 bw_avail, bw_cap;

	bw_cap = pcie_bandwidth_capable(dev, &speed_cap, &width_cap);
	bw_avail = pcie_bandwidth_available(dev, &limiting_dev, &speed, &width);

	अगर (bw_avail >= bw_cap && verbose)
		pci_info(dev, "%u.%03u Gb/s available PCIe bandwidth (%s x%d link)\n",
			 bw_cap / 1000, bw_cap % 1000,
			 pci_speed_string(speed_cap), width_cap);
	अन्यथा अगर (bw_avail < bw_cap)
		pci_info(dev, "%u.%03u Gb/s available PCIe bandwidth, limited by %s x%d link at %s (capable of %u.%03u Gb/s with %s x%d link)\n",
			 bw_avail / 1000, bw_avail % 1000,
			 pci_speed_string(speed), width,
			 limiting_dev ? pci_name(limiting_dev) : "<unknown>",
			 bw_cap / 1000, bw_cap % 1000,
			 pci_speed_string(speed_cap), width_cap);
पूर्ण

/**
 * pcie_prपूर्णांक_link_status - Report the PCI device's link speed and width
 * @dev: PCI device to query
 *
 * Report the available bandwidth at the device.
 */
व्योम pcie_prपूर्णांक_link_status(काष्ठा pci_dev *dev)
अणु
	__pcie_prपूर्णांक_link_status(dev, true);
पूर्ण
EXPORT_SYMBOL(pcie_prपूर्णांक_link_status);

/**
 * pci_select_bars - Make BAR mask from the type of resource
 * @dev: the PCI device क्रम which BAR mask is made
 * @flags: resource type mask to be selected
 *
 * This helper routine makes bar mask from the type of resource.
 */
पूर्णांक pci_select_bars(काष्ठा pci_dev *dev, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक i, bars = 0;
	क्रम (i = 0; i < PCI_NUM_RESOURCES; i++)
		अगर (pci_resource_flags(dev, i) & flags)
			bars |= (1 << i);
	वापस bars;
पूर्ण
EXPORT_SYMBOL(pci_select_bars);

/* Some architectures require additional programming to enable VGA */
अटल arch_set_vga_state_t arch_set_vga_state;

व्योम __init pci_रेजिस्टर_set_vga_state(arch_set_vga_state_t func)
अणु
	arch_set_vga_state = func;	/* शून्य disables */
पूर्ण

अटल पूर्णांक pci_set_vga_state_arch(काष्ठा pci_dev *dev, bool decode,
				  अचिन्हित पूर्णांक command_bits, u32 flags)
अणु
	अगर (arch_set_vga_state)
		वापस arch_set_vga_state(dev, decode, command_bits,
						flags);
	वापस 0;
पूर्ण

/**
 * pci_set_vga_state - set VGA decode state on device and parents अगर requested
 * @dev: the PCI device
 * @decode: true = enable decoding, false = disable decoding
 * @command_bits: PCI_COMMAND_IO and/or PCI_COMMAND_MEMORY
 * @flags: traverse ancestors and change bridges
 * CHANGE_BRIDGE_ONLY / CHANGE_BRIDGE
 */
पूर्णांक pci_set_vga_state(काष्ठा pci_dev *dev, bool decode,
		      अचिन्हित पूर्णांक command_bits, u32 flags)
अणु
	काष्ठा pci_bus *bus;
	काष्ठा pci_dev *bridge;
	u16 cmd;
	पूर्णांक rc;

	WARN_ON((flags & PCI_VGA_STATE_CHANGE_DECODES) && (command_bits & ~(PCI_COMMAND_IO|PCI_COMMAND_MEMORY)));

	/* ARCH specअगरic VGA enables */
	rc = pci_set_vga_state_arch(dev, decode, command_bits, flags);
	अगर (rc)
		वापस rc;

	अगर (flags & PCI_VGA_STATE_CHANGE_DECODES) अणु
		pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
		अगर (decode)
			cmd |= command_bits;
		अन्यथा
			cmd &= ~command_bits;
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
	पूर्ण

	अगर (!(flags & PCI_VGA_STATE_CHANGE_BRIDGE))
		वापस 0;

	bus = dev->bus;
	जबतक (bus) अणु
		bridge = bus->self;
		अगर (bridge) अणु
			pci_पढ़ो_config_word(bridge, PCI_BRIDGE_CONTROL,
					     &cmd);
			अगर (decode)
				cmd |= PCI_BRIDGE_CTL_VGA;
			अन्यथा
				cmd &= ~PCI_BRIDGE_CTL_VGA;
			pci_ग_लिखो_config_word(bridge, PCI_BRIDGE_CONTROL,
					      cmd);
		पूर्ण
		bus = bus->parent;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
bool pci_pr3_present(काष्ठा pci_dev *pdev)
अणु
	काष्ठा acpi_device *adev;

	अगर (acpi_disabled)
		वापस false;

	adev = ACPI_COMPANION(&pdev->dev);
	अगर (!adev)
		वापस false;

	वापस adev->घातer.flags.घातer_resources &&
		acpi_has_method(adev->handle, "_PR3");
पूर्ण
EXPORT_SYMBOL_GPL(pci_pr3_present);
#पूर्ण_अगर

/**
 * pci_add_dma_alias - Add a DMA devfn alias क्रम a device
 * @dev: the PCI device क्रम which alias is added
 * @devfn_from: alias slot and function
 * @nr_devfns: number of subsequent devfns to alias
 *
 * This helper encodes an 8-bit devfn as a bit number in dma_alias_mask
 * which is used to program permissible bus-devfn source addresses क्रम DMA
 * requests in an IOMMU.  These aliases factor पूर्णांकo IOMMU group creation
 * and are useful क्रम devices generating DMA requests beyond or dअगरferent
 * from their logical bus-devfn.  Examples include device quirks where the
 * device simply uses the wrong devfn, as well as non-transparent bridges
 * where the alias may be a proxy क्रम devices in another करोमुख्य.
 *
 * IOMMU group creation is perक्रमmed during device discovery or addition,
 * prior to any potential DMA mapping and thereक्रमe prior to driver probing
 * (especially क्रम userspace asचिन्हित devices where IOMMU group definition
 * cannot be left as a userspace activity).  DMA aliases should thereक्रमe
 * be configured via quirks, such as the PCI fixup header quirk.
 */
व्योम pci_add_dma_alias(काष्ठा pci_dev *dev, u8 devfn_from, अचिन्हित nr_devfns)
अणु
	पूर्णांक devfn_to;

	nr_devfns = min(nr_devfns, (अचिन्हित) MAX_NR_DEVFNS - devfn_from);
	devfn_to = devfn_from + nr_devfns - 1;

	अगर (!dev->dma_alias_mask)
		dev->dma_alias_mask = biपंचांगap_zalloc(MAX_NR_DEVFNS, GFP_KERNEL);
	अगर (!dev->dma_alias_mask) अणु
		pci_warn(dev, "Unable to allocate DMA alias mask\n");
		वापस;
	पूर्ण

	biपंचांगap_set(dev->dma_alias_mask, devfn_from, nr_devfns);

	अगर (nr_devfns == 1)
		pci_info(dev, "Enabling fixed DMA alias to %02x.%d\n",
				PCI_SLOT(devfn_from), PCI_FUNC(devfn_from));
	अन्यथा अगर (nr_devfns > 1)
		pci_info(dev, "Enabling fixed DMA alias for devfn range from %02x.%d to %02x.%d\n",
				PCI_SLOT(devfn_from), PCI_FUNC(devfn_from),
				PCI_SLOT(devfn_to), PCI_FUNC(devfn_to));
पूर्ण

bool pci_devs_are_dma_aliases(काष्ठा pci_dev *dev1, काष्ठा pci_dev *dev2)
अणु
	वापस (dev1->dma_alias_mask &&
		test_bit(dev2->devfn, dev1->dma_alias_mask)) ||
	       (dev2->dma_alias_mask &&
		test_bit(dev1->devfn, dev2->dma_alias_mask)) ||
	       pci_real_dma_dev(dev1) == dev2 ||
	       pci_real_dma_dev(dev2) == dev1;
पूर्ण

bool pci_device_is_present(काष्ठा pci_dev *pdev)
अणु
	u32 v;

	अगर (pci_dev_is_disconnected(pdev))
		वापस false;
	वापस pci_bus_पढ़ो_dev_venकरोr_id(pdev->bus, pdev->devfn, &v, 0);
पूर्ण
EXPORT_SYMBOL_GPL(pci_device_is_present);

व्योम pci_ignore_hotplug(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *bridge = dev->bus->self;

	dev->ignore_hotplug = 1;
	/* Propagate the "ignore hotplug" setting to the parent bridge. */
	अगर (bridge)
		bridge->ignore_hotplug = 1;
पूर्ण
EXPORT_SYMBOL_GPL(pci_ignore_hotplug);

/**
 * pci_real_dma_dev - Get PCI DMA device क्रम PCI device
 * @dev: the PCI device that may have a PCI DMA alias
 *
 * Permits the platक्रमm to provide architecture-specअगरic functionality to
 * devices needing to alias DMA to another PCI device on another PCI bus. If
 * the PCI device is on the same bus, it is recommended to use
 * pci_add_dma_alias(). This is the शेष implementation. Architecture
 * implementations can override this.
 */
काष्ठा pci_dev __weak *pci_real_dma_dev(काष्ठा pci_dev *dev)
अणु
	वापस dev;
पूर्ण

resource_माप_प्रकार __weak pcibios_शेष_alignment(व्योम)
अणु
	वापस 0;
पूर्ण

/*
 * Arches that करोn't want to expose काष्ठा resource to userland as-is in
 * sysfs and /proc can implement their own pci_resource_to_user().
 */
व्योम __weak pci_resource_to_user(स्थिर काष्ठा pci_dev *dev, पूर्णांक bar,
				 स्थिर काष्ठा resource *rsrc,
				 resource_माप_प्रकार *start, resource_माप_प्रकार *end)
अणु
	*start = rsrc->start;
	*end = rsrc->end;
पूर्ण

अटल अक्षर *resource_alignment_param;
अटल DEFINE_SPINLOCK(resource_alignment_lock);

/**
 * pci_specअगरied_resource_alignment - get resource alignment specअगरied by user.
 * @dev: the PCI device to get
 * @resize: whether or not to change resources' size when reassigning alignment
 *
 * RETURNS: Resource alignment अगर it is specअगरied.
 *          Zero अगर it is not specअगरied.
 */
अटल resource_माप_प्रकार pci_specअगरied_resource_alignment(काष्ठा pci_dev *dev,
							bool *resize)
अणु
	पूर्णांक align_order, count;
	resource_माप_प्रकार align = pcibios_शेष_alignment();
	स्थिर अक्षर *p;
	पूर्णांक ret;

	spin_lock(&resource_alignment_lock);
	p = resource_alignment_param;
	अगर (!p || !*p)
		जाओ out;
	अगर (pci_has_flag(PCI_PROBE_ONLY)) अणु
		align = 0;
		pr_info_once("PCI: Ignoring requested alignments (PCI_PROBE_ONLY)\n");
		जाओ out;
	पूर्ण

	जबतक (*p) अणु
		count = 0;
		अगर (माला_पूछो(p, "%d%n", &align_order, &count) == 1 &&
		    p[count] == '@') अणु
			p += count + 1;
			अगर (align_order > 63) अणु
				pr_err("PCI: Invalid requested alignment (order %d)\n",
				       align_order);
				align_order = PAGE_SHIFT;
			पूर्ण
		पूर्ण अन्यथा अणु
			align_order = PAGE_SHIFT;
		पूर्ण

		ret = pci_dev_str_match(dev, p, &p);
		अगर (ret == 1) अणु
			*resize = true;
			align = 1ULL << align_order;
			अवरोध;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			pr_err("PCI: Can't parse resource_alignment parameter: %s\n",
			       p);
			अवरोध;
		पूर्ण

		अगर (*p != ';' && *p != ',') अणु
			/* End of param or invalid क्रमmat */
			अवरोध;
		पूर्ण
		p++;
	पूर्ण
out:
	spin_unlock(&resource_alignment_lock);
	वापस align;
पूर्ण

अटल व्योम pci_request_resource_alignment(काष्ठा pci_dev *dev, पूर्णांक bar,
					   resource_माप_प्रकार align, bool resize)
अणु
	काष्ठा resource *r = &dev->resource[bar];
	resource_माप_प्रकार size;

	अगर (!(r->flags & IORESOURCE_MEM))
		वापस;

	अगर (r->flags & IORESOURCE_PCI_FIXED) अणु
		pci_info(dev, "BAR%d %pR: ignoring requested alignment %#llx\n",
			 bar, r, (अचिन्हित दीर्घ दीर्घ)align);
		वापस;
	पूर्ण

	size = resource_size(r);
	अगर (size >= align)
		वापस;

	/*
	 * Increase the alignment of the resource.  There are two ways we
	 * can करो this:
	 *
	 * 1) Increase the size of the resource.  BARs are aligned on their
	 *    size, so when we पुनः_स्मृतिate space क्रम this resource, we'll
	 *    allocate it with the larger alignment.  This also prevents
	 *    assignment of any other BARs inside the alignment region, so
	 *    अगर we're requesting page alignment, this means no other BARs
	 *    will share the page.
	 *
	 *    The disadvantage is that this makes the resource larger than
	 *    the hardware BAR, which may अवरोध drivers that compute things
	 *    based on the resource size, e.g., to find रेजिस्टरs at a
	 *    fixed offset beक्रमe the end of the BAR.
	 *
	 * 2) Retain the resource size, but use IORESOURCE_STARTALIGN and
	 *    set r->start to the desired alignment.  By itself this
	 *    करोesn't prevent other BARs being put inside the alignment
	 *    region, but अगर we realign *every* resource of every device in
	 *    the प्रणाली, none of them will share an alignment region.
	 *
	 * When the user has requested alignment क्रम only some devices via
	 * the "pci=resource_alignment" argument, "resize" is true and we
	 * use the first method.  Otherwise we assume we're aligning all
	 * devices and we use the second.
	 */

	pci_info(dev, "BAR%d %pR: requesting alignment to %#llx\n",
		 bar, r, (अचिन्हित दीर्घ दीर्घ)align);

	अगर (resize) अणु
		r->start = 0;
		r->end = align - 1;
	पूर्ण अन्यथा अणु
		r->flags &= ~IORESOURCE_SIZEALIGN;
		r->flags |= IORESOURCE_STARTALIGN;
		r->start = align;
		r->end = r->start + size - 1;
	पूर्ण
	r->flags |= IORESOURCE_UNSET;
पूर्ण

/*
 * This function disables memory decoding and releases memory resources
 * of the device specअगरied by kernel's boot parameter 'pci=resource_alignment='.
 * It also rounds up size to specअगरied alignment.
 * Later on, the kernel will assign page-aligned memory resource back
 * to the device.
 */
व्योम pci_reassigndev_resource_alignment(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;
	काष्ठा resource *r;
	resource_माप_प्रकार align;
	u16 command;
	bool resize = false;

	/*
	 * VF BARs are पढ़ो-only zero according to SR-IOV spec r1.1, sec
	 * 3.4.1.11.  Their resources are allocated from the space
	 * described by the VF BARx रेजिस्टर in the PF's SR-IOV capability.
	 * We can't influence their alignment here.
	 */
	अगर (dev->is_virtfn)
		वापस;

	/* check अगर specअगरied PCI is target device to reassign */
	align = pci_specअगरied_resource_alignment(dev, &resize);
	अगर (!align)
		वापस;

	अगर (dev->hdr_type == PCI_HEADER_TYPE_NORMAL &&
	    (dev->class >> 8) == PCI_CLASS_BRIDGE_HOST) अणु
		pci_warn(dev, "Can't reassign resources to host bridge\n");
		वापस;
	पूर्ण

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &command);
	command &= ~PCI_COMMAND_MEMORY;
	pci_ग_लिखो_config_word(dev, PCI_COMMAND, command);

	क्रम (i = 0; i <= PCI_ROM_RESOURCE; i++)
		pci_request_resource_alignment(dev, i, align, resize);

	/*
	 * Need to disable bridge's resource winकरोw,
	 * to enable the kernel to reassign new resource
	 * winकरोw later on.
	 */
	अगर (dev->hdr_type == PCI_HEADER_TYPE_BRIDGE) अणु
		क्रम (i = PCI_BRIDGE_RESOURCES; i < PCI_NUM_RESOURCES; i++) अणु
			r = &dev->resource[i];
			अगर (!(r->flags & IORESOURCE_MEM))
				जारी;
			r->flags |= IORESOURCE_UNSET;
			r->end = resource_size(r) - 1;
			r->start = 0;
		पूर्ण
		pci_disable_bridge_winकरोw(dev);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार resource_alignment_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	माप_प्रकार count = 0;

	spin_lock(&resource_alignment_lock);
	अगर (resource_alignment_param)
		count = scnम_लिखो(buf, PAGE_SIZE, "%s", resource_alignment_param);
	spin_unlock(&resource_alignment_lock);

	/*
	 * When set by the command line, resource_alignment_param will not
	 * have a trailing line feed, which is ugly. So conditionally add
	 * it here.
	 */
	अगर (count >= 2 && buf[count - 2] != '\n' && count < PAGE_SIZE - 1) अणु
		buf[count - 1] = '\n';
		buf[count++] = 0;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार resource_alignment_store(काष्ठा bus_type *bus,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अक्षर *param = kstrndup(buf, count, GFP_KERNEL);

	अगर (!param)
		वापस -ENOMEM;

	spin_lock(&resource_alignment_lock);
	kमुक्त(resource_alignment_param);
	resource_alignment_param = param;
	spin_unlock(&resource_alignment_lock);
	वापस count;
पूर्ण

अटल BUS_ATTR_RW(resource_alignment);

अटल पूर्णांक __init pci_resource_alignment_sysfs_init(व्योम)
अणु
	वापस bus_create_file(&pci_bus_type,
					&bus_attr_resource_alignment);
पूर्ण
late_initcall(pci_resource_alignment_sysfs_init);

अटल व्योम pci_no_करोमुख्यs(व्योम)
अणु
#अगर_घोषित CONFIG_PCI_DOMAINS
	pci_करोमुख्यs_supported = 0;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_PCI_DOMAINS_GENERIC
अटल atomic_t __करोमुख्य_nr = ATOMIC_INIT(-1);

अटल पूर्णांक pci_get_new_करोमुख्य_nr(व्योम)
अणु
	वापस atomic_inc_वापस(&__करोमुख्य_nr);
पूर्ण

अटल पूर्णांक of_pci_bus_find_करोमुख्य_nr(काष्ठा device *parent)
अणु
	अटल पूर्णांक use_dt_करोमुख्यs = -1;
	पूर्णांक करोमुख्य = -1;

	अगर (parent)
		करोमुख्य = of_get_pci_करोमुख्य_nr(parent->of_node);

	/*
	 * Check DT करोमुख्य and use_dt_करोमुख्यs values.
	 *
	 * If DT करोमुख्य property is valid (करोमुख्य >= 0) and
	 * use_dt_करोमुख्यs != 0, the DT assignment is valid since this means
	 * we have not previously allocated a करोमुख्य number by using
	 * pci_get_new_करोमुख्य_nr(); we should also update use_dt_करोमुख्यs to
	 * 1, to indicate that we have just asचिन्हित a करोमुख्य number from
	 * DT.
	 *
	 * If DT करोमुख्य property value is not valid (ie करोमुख्य < 0), and we
	 * have not previously asचिन्हित a करोमुख्य number from DT
	 * (use_dt_करोमुख्यs != 1) we should assign a करोमुख्य number by
	 * using the:
	 *
	 * pci_get_new_करोमुख्य_nr()
	 *
	 * API and update the use_dt_करोमुख्यs value to keep track of method we
	 * are using to assign करोमुख्य numbers (use_dt_करोमुख्यs = 0).
	 *
	 * All other combinations imply we have a platक्रमm that is trying
	 * to mix करोमुख्य numbers obtained from DT and pci_get_new_करोमुख्य_nr(),
	 * which is a recipe क्रम करोमुख्य mishandling and it is prevented by
	 * invalidating the करोमुख्य value (करोमुख्य = -1) and prपूर्णांकing a
	 * corresponding error.
	 */
	अगर (करोमुख्य >= 0 && use_dt_करोमुख्यs) अणु
		use_dt_करोमुख्यs = 1;
	पूर्ण अन्यथा अगर (करोमुख्य < 0 && use_dt_करोमुख्यs != 1) अणु
		use_dt_करोमुख्यs = 0;
		करोमुख्य = pci_get_new_करोमुख्य_nr();
	पूर्ण अन्यथा अणु
		अगर (parent)
			pr_err("Node %pOF has ", parent->of_node);
		pr_err("Inconsistent \"linux,pci-domain\" property in DT\n");
		करोमुख्य = -1;
	पूर्ण

	वापस करोमुख्य;
पूर्ण

पूर्णांक pci_bus_find_करोमुख्य_nr(काष्ठा pci_bus *bus, काष्ठा device *parent)
अणु
	वापस acpi_disabled ? of_pci_bus_find_करोमुख्य_nr(parent) :
			       acpi_pci_bus_find_करोमुख्य_nr(bus);
पूर्ण
#पूर्ण_अगर

/**
 * pci_ext_cfg_avail - can we access extended PCI config space?
 *
 * Returns 1 अगर we can access PCI extended config space (offsets
 * greater than 0xff). This is the शेष implementation. Architecture
 * implementations can override this.
 */
पूर्णांक __weak pci_ext_cfg_avail(व्योम)
अणु
	वापस 1;
पूर्ण

व्योम __weak pci_fixup_cardbus(काष्ठा pci_bus *bus)
अणु
पूर्ण
EXPORT_SYMBOL(pci_fixup_cardbus);

अटल पूर्णांक __init pci_setup(अक्षर *str)
अणु
	जबतक (str) अणु
		अक्षर *k = म_अक्षर(str, ',');
		अगर (k)
			*k++ = 0;
		अगर (*str && (str = pcibios_setup(str)) && *str) अणु
			अगर (!म_भेद(str, "nomsi")) अणु
				pci_no_msi();
			पूर्ण अन्यथा अगर (!म_भेदन(str, "noats", 5)) अणु
				pr_info("PCIe: ATS is disabled\n");
				pcie_ats_disabled = true;
			पूर्ण अन्यथा अगर (!म_भेद(str, "noaer")) अणु
				pci_no_aer();
			पूर्ण अन्यथा अगर (!म_भेद(str, "earlydump")) अणु
				pci_early_dump = true;
			पूर्ण अन्यथा अगर (!म_भेदन(str, "realloc=", 8)) अणु
				pci_पुनः_स्मृति_get_opt(str + 8);
			पूर्ण अन्यथा अगर (!म_भेदन(str, "realloc", 7)) अणु
				pci_पुनः_स्मृति_get_opt("on");
			पूर्ण अन्यथा अगर (!म_भेद(str, "nodomains")) अणु
				pci_no_करोमुख्यs();
			पूर्ण अन्यथा अगर (!म_भेदन(str, "noari", 5)) अणु
				pcie_ari_disabled = true;
			पूर्ण अन्यथा अगर (!म_भेदन(str, "cbiosize=", 9)) अणु
				pci_cardbus_io_size = memparse(str + 9, &str);
			पूर्ण अन्यथा अगर (!म_भेदन(str, "cbmemsize=", 10)) अणु
				pci_cardbus_mem_size = memparse(str + 10, &str);
			पूर्ण अन्यथा अगर (!म_भेदन(str, "resource_alignment=", 19)) अणु
				resource_alignment_param = str + 19;
			पूर्ण अन्यथा अगर (!म_भेदन(str, "ecrc=", 5)) अणु
				pcie_ecrc_get_policy(str + 5);
			पूर्ण अन्यथा अगर (!म_भेदन(str, "hpiosize=", 9)) अणु
				pci_hotplug_io_size = memparse(str + 9, &str);
			पूर्ण अन्यथा अगर (!म_भेदन(str, "hpmmiosize=", 11)) अणु
				pci_hotplug_mmio_size = memparse(str + 11, &str);
			पूर्ण अन्यथा अगर (!म_भेदन(str, "hpmmioprefsize=", 15)) अणु
				pci_hotplug_mmio_pref_size = memparse(str + 15, &str);
			पूर्ण अन्यथा अगर (!म_भेदन(str, "hpmemsize=", 10)) अणु
				pci_hotplug_mmio_size = memparse(str + 10, &str);
				pci_hotplug_mmio_pref_size = pci_hotplug_mmio_size;
			पूर्ण अन्यथा अगर (!म_भेदन(str, "hpbussize=", 10)) अणु
				pci_hotplug_bus_size =
					simple_म_से_अदीर्घ(str + 10, &str, 0);
				अगर (pci_hotplug_bus_size > 0xff)
					pci_hotplug_bus_size = DEFAULT_HOTPLUG_BUS_SIZE;
			पूर्ण अन्यथा अगर (!म_भेदन(str, "pcie_bus_tune_off", 17)) अणु
				pcie_bus_config = PCIE_BUS_TUNE_OFF;
			पूर्ण अन्यथा अगर (!म_भेदन(str, "pcie_bus_safe", 13)) अणु
				pcie_bus_config = PCIE_BUS_SAFE;
			पूर्ण अन्यथा अगर (!म_भेदन(str, "pcie_bus_perf", 13)) अणु
				pcie_bus_config = PCIE_BUS_PERFORMANCE;
			पूर्ण अन्यथा अगर (!म_भेदन(str, "pcie_bus_peer2peer", 18)) अणु
				pcie_bus_config = PCIE_BUS_PEER2PEER;
			पूर्ण अन्यथा अगर (!म_भेदन(str, "pcie_scan_all", 13)) अणु
				pci_add_flags(PCI_SCAN_ALL_PCIE_DEVS);
			पूर्ण अन्यथा अगर (!म_भेदन(str, "disable_acs_redir=", 18)) अणु
				disable_acs_redir_param = str + 18;
			पूर्ण अन्यथा अणु
				pr_err("PCI: Unknown option `%s'\n", str);
			पूर्ण
		पूर्ण
		str = k;
	पूर्ण
	वापस 0;
पूर्ण
early_param("pci", pci_setup);

/*
 * 'resource_alignment_param' and 'disable_acs_redir_param' are initialized
 * in pci_setup(), above, to poपूर्णांक to data in the __initdata section which
 * will be मुक्तd after the init sequence is complete. We can't allocate memory
 * in pci_setup() because some architectures करो not have any memory allocation
 * service available during an early_param() call. So we allocate memory and
 * copy the variable here beक्रमe the init section is मुक्तd.
 *
 */
अटल पूर्णांक __init pci_पुनः_स्मृति_setup_params(व्योम)
अणु
	resource_alignment_param = kstrdup(resource_alignment_param,
					   GFP_KERNEL);
	disable_acs_redir_param = kstrdup(disable_acs_redir_param, GFP_KERNEL);

	वापस 0;
पूर्ण
pure_initcall(pci_पुनः_स्मृति_setup_params);
