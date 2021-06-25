<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* pci_common.c: PCI controller common support.
 *
 * Copyright (C) 1999, 2007 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/oplib.h>

#समावेश "pci_impl.h"
#समावेश "pci_sun4v.h"

अटल पूर्णांक config_out_of_range(काष्ठा pci_pbm_info *pbm,
			       अचिन्हित दीर्घ bus,
			       अचिन्हित दीर्घ devfn,
			       अचिन्हित दीर्घ reg)
अणु
	अगर (bus < pbm->pci_first_busno ||
	    bus > pbm->pci_last_busno)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम *sun4u_config_mkaddr(काष्ठा pci_pbm_info *pbm,
				 अचिन्हित दीर्घ bus,
				 अचिन्हित दीर्घ devfn,
				 अचिन्हित दीर्घ reg)
अणु
	अचिन्हित दीर्घ rbits = pbm->config_space_reg_bits;

	अगर (config_out_of_range(pbm, bus, devfn, reg))
		वापस शून्य;

	reg = (reg & ((1 << rbits) - 1));
	devfn <<= rbits;
	bus <<= rbits + 8;

	वापस (व्योम *)	(pbm->config_space | bus | devfn | reg);
पूर्ण

/* At least on Sabre, it is necessary to access all PCI host controller
 * रेजिस्टरs at their natural size, otherwise zeros are वापसed.
 * Strange but true, and I see no language in the UltraSPARC-IIi
 * programmer's manual that mentions this even indirectly.
 */
अटल पूर्णांक sun4u_पढ़ो_pci_cfg_host(काष्ठा pci_pbm_info *pbm,
				   अचिन्हित अक्षर bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक where, पूर्णांक size, u32 *value)
अणु
	u32 पंचांगp32, *addr;
	u16 पंचांगp16;
	u8 पंचांगp8;

	addr = sun4u_config_mkaddr(pbm, bus, devfn, where);
	अगर (!addr)
		वापस PCIBIOS_SUCCESSFUL;

	चयन (size) अणु
	हाल 1:
		अगर (where < 8) अणु
			अचिन्हित दीर्घ align = (अचिन्हित दीर्घ) addr;

			align &= ~1;
			pci_config_पढ़ो16((u16 *)align, &पंचांगp16);
			अगर (where & 1)
				*value = पंचांगp16 >> 8;
			अन्यथा
				*value = पंचांगp16 & 0xff;
		पूर्ण अन्यथा अणु
			pci_config_पढ़ो8((u8 *)addr, &पंचांगp8);
			*value = (u32) पंचांगp8;
		पूर्ण
		अवरोध;

	हाल 2:
		अगर (where < 8) अणु
			pci_config_पढ़ो16((u16 *)addr, &पंचांगp16);
			*value = (u32) पंचांगp16;
		पूर्ण अन्यथा अणु
			pci_config_पढ़ो8((u8 *)addr, &पंचांगp8);
			*value = (u32) पंचांगp8;
			pci_config_पढ़ो8(((u8 *)addr) + 1, &पंचांगp8);
			*value |= ((u32) पंचांगp8) << 8;
		पूर्ण
		अवरोध;

	हाल 4:
		पंचांगp32 = 0xffffffff;
		sun4u_पढ़ो_pci_cfg_host(pbm, bus, devfn,
					where, 2, &पंचांगp32);
		*value = पंचांगp32;

		पंचांगp32 = 0xffffffff;
		sun4u_पढ़ो_pci_cfg_host(pbm, bus, devfn,
					where + 2, 2, &पंचांगp32);
		*value |= पंचांगp32 << 16;
		अवरोध;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक sun4u_पढ़ो_pci_cfg(काष्ठा pci_bus *bus_dev, अचिन्हित पूर्णांक devfn,
			      पूर्णांक where, पूर्णांक size, u32 *value)
अणु
	काष्ठा pci_pbm_info *pbm = bus_dev->sysdata;
	अचिन्हित अक्षर bus = bus_dev->number;
	u32 *addr;
	u16 पंचांगp16;
	u8 पंचांगp8;

	चयन (size) अणु
	हाल 1:
		*value = 0xff;
		अवरोध;
	हाल 2:
		*value = 0xffff;
		अवरोध;
	हाल 4:
		*value = 0xffffffff;
		अवरोध;
	पूर्ण

	अगर (!bus_dev->number && !PCI_SLOT(devfn))
		वापस sun4u_पढ़ो_pci_cfg_host(pbm, bus, devfn, where,
					       size, value);

	addr = sun4u_config_mkaddr(pbm, bus, devfn, where);
	अगर (!addr)
		वापस PCIBIOS_SUCCESSFUL;

	चयन (size) अणु
	हाल 1:
		pci_config_पढ़ो8((u8 *)addr, &पंचांगp8);
		*value = (u32) पंचांगp8;
		अवरोध;

	हाल 2:
		अगर (where & 0x01) अणु
			prपूर्णांकk("pci_read_config_word: misaligned reg [%x]\n",
			       where);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
		pci_config_पढ़ो16((u16 *)addr, &पंचांगp16);
		*value = (u32) पंचांगp16;
		अवरोध;

	हाल 4:
		अगर (where & 0x03) अणु
			prपूर्णांकk("pci_read_config_dword: misaligned reg [%x]\n",
			       where);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
		pci_config_पढ़ो32(addr, value);
		अवरोध;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक sun4u_ग_लिखो_pci_cfg_host(काष्ठा pci_pbm_info *pbm,
				    अचिन्हित अक्षर bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक where, पूर्णांक size, u32 value)
अणु
	u32 *addr;

	addr = sun4u_config_mkaddr(pbm, bus, devfn, where);
	अगर (!addr)
		वापस PCIBIOS_SUCCESSFUL;

	चयन (size) अणु
	हाल 1:
		अगर (where < 8) अणु
			अचिन्हित दीर्घ align = (अचिन्हित दीर्घ) addr;
			u16 पंचांगp16;

			align &= ~1;
			pci_config_पढ़ो16((u16 *)align, &पंचांगp16);
			अगर (where & 1) अणु
				पंचांगp16 &= 0x00ff;
				पंचांगp16 |= value << 8;
			पूर्ण अन्यथा अणु
				पंचांगp16 &= 0xff00;
				पंचांगp16 |= value;
			पूर्ण
			pci_config_ग_लिखो16((u16 *)align, पंचांगp16);
		पूर्ण अन्यथा
			pci_config_ग_लिखो8((u8 *)addr, value);
		अवरोध;
	हाल 2:
		अगर (where < 8) अणु
			pci_config_ग_लिखो16((u16 *)addr, value);
		पूर्ण अन्यथा अणु
			pci_config_ग_लिखो8((u8 *)addr, value & 0xff);
			pci_config_ग_लिखो8(((u8 *)addr) + 1, value >> 8);
		पूर्ण
		अवरोध;
	हाल 4:
		sun4u_ग_लिखो_pci_cfg_host(pbm, bus, devfn,
					 where, 2, value & 0xffff);
		sun4u_ग_लिखो_pci_cfg_host(pbm, bus, devfn,
					 where + 2, 2, value >> 16);
		अवरोध;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक sun4u_ग_लिखो_pci_cfg(काष्ठा pci_bus *bus_dev, अचिन्हित पूर्णांक devfn,
			       पूर्णांक where, पूर्णांक size, u32 value)
अणु
	काष्ठा pci_pbm_info *pbm = bus_dev->sysdata;
	अचिन्हित अक्षर bus = bus_dev->number;
	u32 *addr;

	अगर (!bus_dev->number && !PCI_SLOT(devfn))
		वापस sun4u_ग_लिखो_pci_cfg_host(pbm, bus, devfn, where,
						size, value);

	addr = sun4u_config_mkaddr(pbm, bus, devfn, where);
	अगर (!addr)
		वापस PCIBIOS_SUCCESSFUL;

	चयन (size) अणु
	हाल 1:
		pci_config_ग_लिखो8((u8 *)addr, value);
		अवरोध;

	हाल 2:
		अगर (where & 0x01) अणु
			prपूर्णांकk("pci_write_config_word: misaligned reg [%x]\n",
			       where);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
		pci_config_ग_लिखो16((u16 *)addr, value);
		अवरोध;

	हाल 4:
		अगर (where & 0x03) अणु
			prपूर्णांकk("pci_write_config_dword: misaligned reg [%x]\n",
			       where);
			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
		pci_config_ग_लिखो32(addr, value);
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops sun4u_pci_ops = अणु
	.पढ़ो =		sun4u_पढ़ो_pci_cfg,
	.ग_लिखो =	sun4u_ग_लिखो_pci_cfg,
पूर्ण;

अटल पूर्णांक sun4v_पढ़ो_pci_cfg(काष्ठा pci_bus *bus_dev, अचिन्हित पूर्णांक devfn,
			      पूर्णांक where, पूर्णांक size, u32 *value)
अणु
	काष्ठा pci_pbm_info *pbm = bus_dev->sysdata;
	u32 devhandle = pbm->devhandle;
	अचिन्हित पूर्णांक bus = bus_dev->number;
	अचिन्हित पूर्णांक device = PCI_SLOT(devfn);
	अचिन्हित पूर्णांक func = PCI_FUNC(devfn);
	अचिन्हित दीर्घ ret;

	अगर (config_out_of_range(pbm, bus, devfn, where)) अणु
		ret = ~0UL;
	पूर्ण अन्यथा अणु
		ret = pci_sun4v_config_get(devhandle,
				HV_PCI_DEVICE_BUILD(bus, device, func),
				where, size);
	पूर्ण
	चयन (size) अणु
	हाल 1:
		*value = ret & 0xff;
		अवरोध;
	हाल 2:
		*value = ret & 0xffff;
		अवरोध;
	हाल 4:
		*value = ret & 0xffffffff;
		अवरोध;
	पूर्ण


	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक sun4v_ग_लिखो_pci_cfg(काष्ठा pci_bus *bus_dev, अचिन्हित पूर्णांक devfn,
			       पूर्णांक where, पूर्णांक size, u32 value)
अणु
	काष्ठा pci_pbm_info *pbm = bus_dev->sysdata;
	u32 devhandle = pbm->devhandle;
	अचिन्हित पूर्णांक bus = bus_dev->number;
	अचिन्हित पूर्णांक device = PCI_SLOT(devfn);
	अचिन्हित पूर्णांक func = PCI_FUNC(devfn);

	अगर (config_out_of_range(pbm, bus, devfn, where)) अणु
		/* Do nothing. */
	पूर्ण अन्यथा अणु
		/* We करोn't check क्रम hypervisor errors here, but perhaps
		 * we should and influence our वापस value depending upon
		 * what kind of error is thrown.
		 */
		pci_sun4v_config_put(devhandle,
				     HV_PCI_DEVICE_BUILD(bus, device, func),
				     where, size, value);
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops sun4v_pci_ops = अणु
	.पढ़ो =		sun4v_पढ़ो_pci_cfg,
	.ग_लिखो =	sun4v_ग_लिखो_pci_cfg,
पूर्ण;

व्योम pci_get_pbm_props(काष्ठा pci_pbm_info *pbm)
अणु
	स्थिर u32 *val = of_get_property(pbm->op->dev.of_node, "bus-range", शून्य);

	pbm->pci_first_busno = val[0];
	pbm->pci_last_busno = val[1];

	val = of_get_property(pbm->op->dev.of_node, "ino-bitmap", शून्य);
	अगर (val) अणु
		pbm->ino_biपंचांगap = (((u64)val[1] << 32UL) |
				   ((u64)val[0] <<  0UL));
	पूर्ण
पूर्ण

अटल व्योम pci_रेजिस्टर_iommu_region(काष्ठा pci_pbm_info *pbm)
अणु
	स्थिर u32 *vdma = of_get_property(pbm->op->dev.of_node, "virtual-dma",
					  शून्य);

	अगर (vdma) अणु
		काष्ठा resource *rp = kzalloc(माप(*rp), GFP_KERNEL);

		अगर (!rp) अणु
			pr_info("%s: Cannot allocate IOMMU resource.\n",
				pbm->name);
			वापस;
		पूर्ण
		rp->name = "IOMMU";
		rp->start = pbm->mem_space.start + (अचिन्हित दीर्घ) vdma[0];
		rp->end = rp->start + (अचिन्हित दीर्घ) vdma[1] - 1UL;
		rp->flags = IORESOURCE_BUSY;
		अगर (request_resource(&pbm->mem_space, rp)) अणु
			pr_info("%s: Unable to request IOMMU resource.\n",
				pbm->name);
			kमुक्त(rp);
		पूर्ण
	पूर्ण
पूर्ण

व्योम pci_determine_mem_io_space(काष्ठा pci_pbm_info *pbm)
अणु
	स्थिर काष्ठा linux_prom_pci_ranges *pbm_ranges;
	पूर्णांक i, saw_mem, saw_io;
	पूर्णांक num_pbm_ranges;

	/* Corresponding generic code in of_pci_get_host_bridge_resources() */

	saw_mem = saw_io = 0;
	pbm_ranges = of_get_property(pbm->op->dev.of_node, "ranges", &i);
	अगर (!pbm_ranges) अणु
		prom_म_लिखो("PCI: Fatal error, missing PBM ranges property "
			    " for %s\n",
			    pbm->name);
		prom_halt();
	पूर्ण

	num_pbm_ranges = i / माप(*pbm_ranges);
	स_रखो(&pbm->mem64_space, 0, माप(काष्ठा resource));

	क्रम (i = 0; i < num_pbm_ranges; i++) अणु
		स्थिर काष्ठा linux_prom_pci_ranges *pr = &pbm_ranges[i];
		अचिन्हित दीर्घ a, size, region_a;
		u32 parent_phys_hi, parent_phys_lo;
		u32 child_phys_mid, child_phys_lo;
		u32 size_hi, size_lo;
		पूर्णांक type;

		parent_phys_hi = pr->parent_phys_hi;
		parent_phys_lo = pr->parent_phys_lo;
		child_phys_mid = pr->child_phys_mid;
		child_phys_lo = pr->child_phys_lo;
		अगर (tlb_type == hypervisor)
			parent_phys_hi &= 0x0fffffff;

		size_hi = pr->size_hi;
		size_lo = pr->size_lo;

		type = (pr->child_phys_hi >> 24) & 0x3;
		a = (((अचिन्हित दीर्घ)parent_phys_hi << 32UL) |
		     ((अचिन्हित दीर्घ)parent_phys_lo  <<  0UL));
		region_a = (((अचिन्हित दीर्घ)child_phys_mid << 32UL) |
		     ((अचिन्हित दीर्घ)child_phys_lo  <<  0UL));
		size = (((अचिन्हित दीर्घ)size_hi << 32UL) |
			((अचिन्हित दीर्घ)size_lo  <<  0UL));

		चयन (type) अणु
		हाल 0:
			/* PCI config space, 16MB */
			pbm->config_space = a;
			अवरोध;

		हाल 1:
			/* 16-bit IO space, 16MB */
			pbm->io_space.start = a;
			pbm->io_space.end = a + size - 1UL;
			pbm->io_space.flags = IORESOURCE_IO;
			pbm->io_offset = a - region_a;
			saw_io = 1;
			अवरोध;

		हाल 2:
			/* 32-bit MEM space, 2GB */
			pbm->mem_space.start = a;
			pbm->mem_space.end = a + size - 1UL;
			pbm->mem_space.flags = IORESOURCE_MEM;
			pbm->mem_offset = a - region_a;
			saw_mem = 1;
			अवरोध;

		हाल 3:
			/* 64-bit MEM handling */
			pbm->mem64_space.start = a;
			pbm->mem64_space.end = a + size - 1UL;
			pbm->mem64_space.flags = IORESOURCE_MEM;
			pbm->mem64_offset = a - region_a;
			saw_mem = 1;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!saw_io || !saw_mem) अणु
		prom_म_लिखो("%s: Fatal error, missing %s PBM range.\n",
			    pbm->name,
			    (!saw_io ? "IO" : "MEM"));
		prom_halt();
	पूर्ण

	अगर (pbm->io_space.flags)
		prपूर्णांकk("%s: PCI IO %pR offset %llx\n",
		       pbm->name, &pbm->io_space, pbm->io_offset);
	अगर (pbm->mem_space.flags)
		prपूर्णांकk("%s: PCI MEM %pR offset %llx\n",
		       pbm->name, &pbm->mem_space, pbm->mem_offset);
	अगर (pbm->mem64_space.flags && pbm->mem_space.flags) अणु
		अगर (pbm->mem64_space.start <= pbm->mem_space.end)
			pbm->mem64_space.start = pbm->mem_space.end + 1;
		अगर (pbm->mem64_space.start > pbm->mem64_space.end)
			pbm->mem64_space.flags = 0;
	पूर्ण

	अगर (pbm->mem64_space.flags)
		prपूर्णांकk("%s: PCI MEM64 %pR offset %llx\n",
		       pbm->name, &pbm->mem64_space, pbm->mem64_offset);

	pbm->io_space.name = pbm->mem_space.name = pbm->name;
	pbm->mem64_space.name = pbm->name;

	request_resource(&ioport_resource, &pbm->io_space);
	request_resource(&iomem_resource, &pbm->mem_space);
	अगर (pbm->mem64_space.flags)
		request_resource(&iomem_resource, &pbm->mem64_space);

	pci_रेजिस्टर_iommu_region(pbm);
पूर्ण

/* Generic helper routines क्रम PCI error reporting. */
व्योम pci_scan_क्रम_target_पात(काष्ठा pci_pbm_info *pbm,
			       काष्ठा pci_bus *pbus)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा pci_bus *bus;

	list_क्रम_each_entry(pdev, &pbus->devices, bus_list) अणु
		u16 status, error_bits;

		pci_पढ़ो_config_word(pdev, PCI_STATUS, &status);
		error_bits =
			(status & (PCI_STATUS_SIG_TARGET_ABORT |
				   PCI_STATUS_REC_TARGET_ABORT));
		अगर (error_bits) अणु
			pci_ग_लिखो_config_word(pdev, PCI_STATUS, error_bits);
			pci_info(pdev, "%s: Device saw Target Abort [%016x]\n",
				 pbm->name, status);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(bus, &pbus->children, node)
		pci_scan_क्रम_target_पात(pbm, bus);
पूर्ण

व्योम pci_scan_क्रम_master_पात(काष्ठा pci_pbm_info *pbm,
			       काष्ठा pci_bus *pbus)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा pci_bus *bus;

	list_क्रम_each_entry(pdev, &pbus->devices, bus_list) अणु
		u16 status, error_bits;

		pci_पढ़ो_config_word(pdev, PCI_STATUS, &status);
		error_bits =
			(status & (PCI_STATUS_REC_MASTER_ABORT));
		अगर (error_bits) अणु
			pci_ग_लिखो_config_word(pdev, PCI_STATUS, error_bits);
			pci_info(pdev, "%s: Device received Master Abort "
				 "[%016x]\n", pbm->name, status);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(bus, &pbus->children, node)
		pci_scan_क्रम_master_पात(pbm, bus);
पूर्ण

व्योम pci_scan_क्रम_parity_error(काष्ठा pci_pbm_info *pbm,
			       काष्ठा pci_bus *pbus)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा pci_bus *bus;

	list_क्रम_each_entry(pdev, &pbus->devices, bus_list) अणु
		u16 status, error_bits;

		pci_पढ़ो_config_word(pdev, PCI_STATUS, &status);
		error_bits =
			(status & (PCI_STATUS_PARITY |
				   PCI_STATUS_DETECTED_PARITY));
		अगर (error_bits) अणु
			pci_ग_लिखो_config_word(pdev, PCI_STATUS, error_bits);
			pci_info(pdev, "%s: Device saw Parity Error [%016x]\n",
				 pbm->name, status);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(bus, &pbus->children, node)
		pci_scan_क्रम_parity_error(pbm, bus);
पूर्ण
