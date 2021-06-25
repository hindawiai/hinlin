<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001 Dave Engebretsen, IBM Corporation
 * Copyright (C) 2003 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 *
 * pSeries specअगरic routines क्रम PCI.
 */

#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/eeh.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/pci.h>
#समावेश "pseries.h"

#अगर 0
व्योम pcibios_name_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा device_node *dn;

	/*
	 * Add IBM loc code (slot) as a prefix to the device names क्रम service
	 */
	dn = pci_device_to_OF_node(dev);
	अगर (dn) अणु
		स्थिर अक्षर *loc_code = of_get_property(dn, "ibm,loc-code",
				शून्य);
		अगर (loc_code) अणु
			पूर्णांक loc_len = म_माप(loc_code);
			अगर (loc_len < माप(dev->dev.name)) अणु
				स_हटाओ(dev->dev.name+loc_len+1, dev->dev.name,
					माप(dev->dev.name)-loc_len-1);
				स_नकल(dev->dev.name, loc_code, loc_len);
				dev->dev.name[loc_len] = ' ';
				dev->dev.name[माप(dev->dev.name)-1] = '\0';
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_ANY_ID, PCI_ANY_ID, pcibios_name_device);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_IOV
#घोषणा MAX_VFS_FOR_MAP_PE 256
काष्ठा pe_map_bar_entry अणु
	__be64     bar;       /* Input:  Virtual Function BAR */
	__be16     rid;       /* Input:  Virtual Function Router ID */
	__be16     pe_num;    /* Output: Virtual Function PE Number */
	__be32     reserved;  /* Reserved Space */
पूर्ण;

अटल पूर्णांक pseries_send_map_pe(काष्ठा pci_dev *pdev, u16 num_vfs,
			       काष्ठा pe_map_bar_entry *vf_pe_array)
अणु
	काष्ठा pci_dn *pdn;
	पूर्णांक rc;
	अचिन्हित दीर्घ buid, addr;
	पूर्णांक ibm_map_pes = rtas_token("ibm,open-sriov-map-pe-number");

	अगर (ibm_map_pes == RTAS_UNKNOWN_SERVICE)
		वापस -EINVAL;

	pdn = pci_get_pdn(pdev);
	addr = rtas_config_addr(pdn->busno, pdn->devfn, 0);
	buid = pdn->phb->buid;
	spin_lock(&rtas_data_buf_lock);
	स_नकल(rtas_data_buf, vf_pe_array,
	       RTAS_DATA_BUF_SIZE);
	rc = rtas_call(ibm_map_pes, 5, 1, शून्य, addr,
		       BUID_HI(buid), BUID_LO(buid),
		       rtas_data_buf,
		       num_vfs * माप(काष्ठा pe_map_bar_entry));
	स_नकल(vf_pe_array, rtas_data_buf, RTAS_DATA_BUF_SIZE);
	spin_unlock(&rtas_data_buf_lock);

	अगर (rc)
		dev_err(&pdev->dev,
			"%s: Failed to associate pes PE#%lx, rc=%x\n",
			__func__,  addr, rc);

	वापस rc;
पूर्ण

अटल व्योम pseries_set_pe_num(काष्ठा pci_dev *pdev, u16 vf_index, __be16 pe_num)
अणु
	काष्ठा pci_dn *pdn;

	pdn = pci_get_pdn(pdev);
	pdn->pe_num_map[vf_index] = be16_to_cpu(pe_num);
	dev_dbg(&pdev->dev, "VF %04x:%02x:%02x.%x associated with PE#%x\n",
		pci_करोमुख्य_nr(pdev->bus),
		pdev->bus->number,
		PCI_SLOT(pci_iov_virtfn_devfn(pdev, vf_index)),
		PCI_FUNC(pci_iov_virtfn_devfn(pdev, vf_index)),
		pdn->pe_num_map[vf_index]);
पूर्ण

अटल पूर्णांक pseries_associate_pes(काष्ठा pci_dev *pdev, u16 num_vfs)
अणु
	काष्ठा pci_dn *pdn;
	पूर्णांक i, rc, vf_index;
	काष्ठा pe_map_bar_entry *vf_pe_array;
	काष्ठा resource *res;
	u64 size;

	vf_pe_array = kzalloc(RTAS_DATA_BUF_SIZE, GFP_KERNEL);
	अगर (!vf_pe_array)
		वापस -ENOMEM;

	pdn = pci_get_pdn(pdev);
	/* create firmware काष्ठाure to associate pes */
	क्रम (vf_index = 0; vf_index < num_vfs; vf_index++) अणु
		pdn->pe_num_map[vf_index] = IODA_INVALID_PE;
		क्रम (i = 0; i < PCI_SRIOV_NUM_BARS; i++) अणु
			res = &pdev->resource[i + PCI_IOV_RESOURCES];
			अगर (!res->parent)
				जारी;
			size = pcibios_iov_resource_alignment(pdev, i +
					PCI_IOV_RESOURCES);
			vf_pe_array[vf_index].bar =
				cpu_to_be64(res->start + size * vf_index);
			vf_pe_array[vf_index].rid =
				cpu_to_be16((pci_iov_virtfn_bus(pdev, vf_index)
					    << 8) | pci_iov_virtfn_devfn(pdev,
					    vf_index));
			vf_pe_array[vf_index].pe_num =
				cpu_to_be16(IODA_INVALID_PE);
		पूर्ण
	पूर्ण

	rc = pseries_send_map_pe(pdev, num_vfs, vf_pe_array);
	/* Only zero is success */
	अगर (!rc)
		क्रम (vf_index = 0; vf_index < num_vfs; vf_index++)
			pseries_set_pe_num(pdev, vf_index,
					   vf_pe_array[vf_index].pe_num);

	kमुक्त(vf_pe_array);
	वापस rc;
पूर्ण

अटल पूर्णांक pseries_pci_sriov_enable(काष्ठा pci_dev *pdev, u16 num_vfs)
अणु
	काष्ठा pci_dn         *pdn;
	पूर्णांक                    rc;
	स्थिर पूर्णांक *max_vfs;
	पूर्णांक max_config_vfs;
	काष्ठा device_node *dn = pci_device_to_OF_node(pdev);

	max_vfs = of_get_property(dn, "ibm,number-of-configurable-vfs", शून्य);

	अगर (!max_vfs)
		वापस -EINVAL;

	/* First पूर्णांकeger stores max config */
	max_config_vfs = of_पढ़ो_number(&max_vfs[0], 1);
	अगर (max_config_vfs < num_vfs && num_vfs > MAX_VFS_FOR_MAP_PE) अणु
		dev_err(&pdev->dev,
			"Num VFs %x > %x Configurable VFs\n",
			num_vfs, (num_vfs > MAX_VFS_FOR_MAP_PE) ?
			MAX_VFS_FOR_MAP_PE : max_config_vfs);
		वापस -EINVAL;
	पूर्ण

	pdn = pci_get_pdn(pdev);
	pdn->pe_num_map = kदो_स्मृति_array(num_vfs,
					माप(*pdn->pe_num_map),
					GFP_KERNEL);
	अगर (!pdn->pe_num_map)
		वापस -ENOMEM;

	rc = pseries_associate_pes(pdev, num_vfs);

	/* Anything other than zero is failure */
	अगर (rc) अणु
		dev_err(&pdev->dev, "Failure to enable sriov: %x\n", rc);
		kमुक्त(pdn->pe_num_map);
	पूर्ण अन्यथा अणु
		pci_vf_drivers_स्वतःprobe(pdev, false);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक pseries_pcibios_sriov_enable(काष्ठा pci_dev *pdev, u16 num_vfs)
अणु
	/* Allocate PCI data */
	add_sriov_vf_pdns(pdev);
	वापस pseries_pci_sriov_enable(pdev, num_vfs);
पूर्ण

अटल पूर्णांक pseries_pcibios_sriov_disable(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dn         *pdn;

	pdn = pci_get_pdn(pdev);
	/* Releasing pe_num_map */
	kमुक्त(pdn->pe_num_map);
	/* Release PCI data */
	हटाओ_sriov_vf_pdns(pdev);
	pci_vf_drivers_स्वतःprobe(pdev, true);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम __init pSeries_request_regions(व्योम)
अणु
	अगर (!isa_io_base)
		वापस;

	request_region(0x20,0x20,"pic1");
	request_region(0xa0,0x20,"pic2");
	request_region(0x00,0x20,"dma1");
	request_region(0x40,0x20,"timer");
	request_region(0x80,0x10,"dma page reg");
	request_region(0xc0,0x20,"dma2");
पूर्ण

व्योम __init pSeries_final_fixup(व्योम)
अणु
	pSeries_request_regions();

	eeh_show_enabled();

#अगर_घोषित CONFIG_PCI_IOV
	ppc_md.pcibios_sriov_enable = pseries_pcibios_sriov_enable;
	ppc_md.pcibios_sriov_disable = pseries_pcibios_sriov_disable;
#पूर्ण_अगर
पूर्ण

/*
 * Assume the winbond 82c105 is the IDE controller on a
 * p610/p615/p630. We should probably be more careful in हाल
 * someone tries to plug in a similar adapter.
 */
अटल व्योम fixup_winbond_82c105(काष्ठा pci_dev* dev)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक reg;

	अगर (!machine_is(pseries))
		वापस;

	prपूर्णांकk("Using INTC for W82c105 IDE controller.\n");
	pci_पढ़ो_config_dword(dev, 0x40, &reg);
	/* Enable LEGIRQ to use INTC instead of ISA पूर्णांकerrupts */
	pci_ग_लिखो_config_dword(dev, 0x40, reg | (1<<11));

	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; ++i) अणु
		/* zap the 2nd function of the winbond chip */
		अगर (dev->resource[i].flags & IORESOURCE_IO
		    && dev->bus->number == 0 && dev->devfn == 0x81)
			dev->resource[i].flags &= ~IORESOURCE_IO;
		अगर (dev->resource[i].start == 0 && dev->resource[i].end) अणु
			dev->resource[i].flags = 0;
			dev->resource[i].end = 0;
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_WINBOND, PCI_DEVICE_ID_WINBOND_82C105,
			 fixup_winbond_82c105);

अटल क्रमागत pci_bus_speed prop_to_pci_speed(u32 prop)
अणु
	चयन (prop) अणु
	हाल 0x01:
		वापस PCIE_SPEED_2_5GT;
	हाल 0x02:
		वापस PCIE_SPEED_5_0GT;
	हाल 0x04:
		वापस PCIE_SPEED_8_0GT;
	हाल 0x08:
		वापस PCIE_SPEED_16_0GT;
	हाल 0x10:
		वापस PCIE_SPEED_32_0GT;
	शेष:
		pr_debug("Unexpected PCI link speed property value\n");
		वापस PCI_SPEED_UNKNOWN;
	पूर्ण
पूर्ण

पूर्णांक pseries_root_bridge_prepare(काष्ठा pci_host_bridge *bridge)
अणु
	काष्ठा device_node *dn, *pdn;
	काष्ठा pci_bus *bus;
	u32 pcie_link_speed_stats[2];
	पूर्णांक rc;

	bus = bridge->bus;

	/* Rely on the pcibios_मुक्त_controller_deferred() callback. */
	pci_set_host_bridge_release(bridge, pcibios_मुक्त_controller_deferred,
					(व्योम *) pci_bus_to_host(bus));

	dn = pcibios_get_phb_of_node(bus);
	अगर (!dn)
		वापस 0;

	क्रम (pdn = dn; pdn != शून्य; pdn = of_get_next_parent(pdn)) अणु
		rc = of_property_पढ़ो_u32_array(pdn,
				"ibm,pcie-link-speed-stats",
				&pcie_link_speed_stats[0], 2);
		अगर (!rc)
			अवरोध;
	पूर्ण

	of_node_put(pdn);

	अगर (rc) अणु
		pr_debug("no ibm,pcie-link-speed-stats property\n");
		वापस 0;
	पूर्ण

	bus->max_bus_speed = prop_to_pci_speed(pcie_link_speed_stats[0]);
	bus->cur_bus_speed = prop_to_pci_speed(pcie_link_speed_stats[1]);
	वापस 0;
पूर्ण
