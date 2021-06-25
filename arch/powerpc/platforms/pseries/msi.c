<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2006 Jake Moilanen <moilanen@austin.ibm.com>, IBM Corp.
 * Copyright 2006-2007 Michael Ellerman, IBM Corp.
 */

#समावेश <linux/crash_dump.h>
#समावेश <linux/device.h>
#समावेश <linux/irq.h>
#समावेश <linux/msi.h>

#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/machdep.h>

#समावेश "pseries.h"

अटल पूर्णांक query_token, change_token;

#घोषणा RTAS_QUERY_FN		0
#घोषणा RTAS_CHANGE_FN		1
#घोषणा RTAS_RESET_FN		2
#घोषणा RTAS_CHANGE_MSI_FN	3
#घोषणा RTAS_CHANGE_MSIX_FN	4
#घोषणा RTAS_CHANGE_32MSI_FN	5

/* RTAS Helpers */

अटल पूर्णांक rtas_change_msi(काष्ठा pci_dn *pdn, u32 func, u32 num_irqs)
अणु
	u32 addr, seq_num, rtas_ret[3];
	अचिन्हित दीर्घ buid;
	पूर्णांक rc;

	addr = rtas_config_addr(pdn->busno, pdn->devfn, 0);
	buid = pdn->phb->buid;

	seq_num = 1;
	करो अणु
		अगर (func == RTAS_CHANGE_MSI_FN || func == RTAS_CHANGE_MSIX_FN ||
		    func == RTAS_CHANGE_32MSI_FN)
			rc = rtas_call(change_token, 6, 4, rtas_ret, addr,
					BUID_HI(buid), BUID_LO(buid),
					func, num_irqs, seq_num);
		अन्यथा
			rc = rtas_call(change_token, 6, 3, rtas_ret, addr,
					BUID_HI(buid), BUID_LO(buid),
					func, num_irqs, seq_num);

		seq_num = rtas_ret[1];
	पूर्ण जबतक (rtas_busy_delay(rc));

	/*
	 * If the RTAS call succeeded, वापस the number of irqs allocated.
	 * If not, make sure we वापस a negative error code.
	 */
	अगर (rc == 0)
		rc = rtas_ret[0];
	अन्यथा अगर (rc > 0)
		rc = -rc;

	pr_debug("rtas_msi: ibm,change_msi(func=%d,num=%d), got %d rc = %d\n",
		 func, num_irqs, rtas_ret[0], rc);

	वापस rc;
पूर्ण

अटल व्योम rtas_disable_msi(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dn *pdn;

	pdn = pci_get_pdn(pdev);
	अगर (!pdn)
		वापस;

	/*
	 * disabling MSI with the explicit पूर्णांकerface also disables MSI-X
	 */
	अगर (rtas_change_msi(pdn, RTAS_CHANGE_MSI_FN, 0) != 0) अणु
		/* 
		 * may have failed because explicit पूर्णांकerface is not
		 * present
		 */
		अगर (rtas_change_msi(pdn, RTAS_CHANGE_FN, 0) != 0) अणु
			pr_debug("rtas_msi: Setting MSIs to 0 failed!\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rtas_query_irq_number(काष्ठा pci_dn *pdn, पूर्णांक offset)
अणु
	u32 addr, rtas_ret[2];
	अचिन्हित दीर्घ buid;
	पूर्णांक rc;

	addr = rtas_config_addr(pdn->busno, pdn->devfn, 0);
	buid = pdn->phb->buid;

	करो अणु
		rc = rtas_call(query_token, 4, 3, rtas_ret, addr,
			       BUID_HI(buid), BUID_LO(buid), offset);
	पूर्ण जबतक (rtas_busy_delay(rc));

	अगर (rc) अणु
		pr_debug("rtas_msi: error (%d) querying source number\n", rc);
		वापस rc;
	पूर्ण

	वापस rtas_ret[0];
पूर्ण

अटल व्योम rtas_tearकरोwn_msi_irqs(काष्ठा pci_dev *pdev)
अणु
	काष्ठा msi_desc *entry;

	क्रम_each_pci_msi_entry(entry, pdev) अणु
		अगर (!entry->irq)
			जारी;

		irq_set_msi_desc(entry->irq, शून्य);
		irq_dispose_mapping(entry->irq);
	पूर्ण

	rtas_disable_msi(pdev);
पूर्ण

अटल पूर्णांक check_req(काष्ठा pci_dev *pdev, पूर्णांक nvec, अक्षर *prop_name)
अणु
	काष्ठा device_node *dn;
	स्थिर __be32 *p;
	u32 req_msi;

	dn = pci_device_to_OF_node(pdev);

	p = of_get_property(dn, prop_name, शून्य);
	अगर (!p) अणु
		pr_debug("rtas_msi: No %s on %pOF\n", prop_name, dn);
		वापस -ENOENT;
	पूर्ण

	req_msi = be32_to_cpup(p);
	अगर (req_msi < nvec) अणु
		pr_debug("rtas_msi: %s requests < %d MSIs\n", prop_name, nvec);

		अगर (req_msi == 0) /* Be paranoid */
			वापस -ENOSPC;

		वापस req_msi;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_req_msi(काष्ठा pci_dev *pdev, पूर्णांक nvec)
अणु
	वापस check_req(pdev, nvec, "ibm,req#msi");
पूर्ण

अटल पूर्णांक check_req_msix(काष्ठा pci_dev *pdev, पूर्णांक nvec)
अणु
	वापस check_req(pdev, nvec, "ibm,req#msi-x");
पूर्ण

/* Quota calculation */

अटल काष्ठा device_node *find_pe_total_msi(काष्ठा pci_dev *dev, पूर्णांक *total)
अणु
	काष्ठा device_node *dn;
	स्थिर __be32 *p;

	dn = of_node_get(pci_device_to_OF_node(dev));
	जबतक (dn) अणु
		p = of_get_property(dn, "ibm,pe-total-#msi", शून्य);
		अगर (p) अणु
			pr_debug("rtas_msi: found prop on dn %pOF\n",
				dn);
			*total = be32_to_cpup(p);
			वापस dn;
		पूर्ण

		dn = of_get_next_parent(dn);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा device_node *find_pe_dn(काष्ठा pci_dev *dev, पूर्णांक *total)
अणु
	काष्ठा device_node *dn;
	काष्ठा eeh_dev *edev;

	/* Found our PE and assume 8 at that poपूर्णांक. */

	dn = pci_device_to_OF_node(dev);
	अगर (!dn)
		वापस शून्य;

	/* Get the top level device in the PE */
	edev = pdn_to_eeh_dev(PCI_DN(dn));
	अगर (edev->pe)
		edev = list_first_entry(&edev->pe->edevs, काष्ठा eeh_dev,
					entry);
	dn = pci_device_to_OF_node(edev->pdev);
	अगर (!dn)
		वापस शून्य;

	/* We actually want the parent */
	dn = of_get_parent(dn);
	अगर (!dn)
		वापस शून्य;

	/* Hardcode of 8 क्रम old firmwares */
	*total = 8;
	pr_debug("rtas_msi: using PE dn %pOF\n", dn);

	वापस dn;
पूर्ण

काष्ठा msi_counts अणु
	काष्ठा device_node *requestor;
	पूर्णांक num_devices;
	पूर्णांक request;
	पूर्णांक quota;
	पूर्णांक spare;
	पूर्णांक over_quota;
पूर्ण;

अटल व्योम *count_non_bridge_devices(काष्ठा device_node *dn, व्योम *data)
अणु
	काष्ठा msi_counts *counts = data;
	स्थिर __be32 *p;
	u32 class;

	pr_debug("rtas_msi: counting %pOF\n", dn);

	p = of_get_property(dn, "class-code", शून्य);
	class = p ? be32_to_cpup(p) : 0;

	अगर ((class >> 8) != PCI_CLASS_BRIDGE_PCI)
		counts->num_devices++;

	वापस शून्य;
पूर्ण

अटल व्योम *count_spare_msis(काष्ठा device_node *dn, व्योम *data)
अणु
	काष्ठा msi_counts *counts = data;
	स्थिर __be32 *p;
	पूर्णांक req;

	अगर (dn == counts->requestor)
		req = counts->request;
	अन्यथा अणु
		/* We करोn't know अगर a driver will try to use MSI or MSI-X,
		 * so we just have to punt and use the larger of the two. */
		req = 0;
		p = of_get_property(dn, "ibm,req#msi", शून्य);
		अगर (p)
			req = be32_to_cpup(p);

		p = of_get_property(dn, "ibm,req#msi-x", शून्य);
		अगर (p)
			req = max(req, (पूर्णांक)be32_to_cpup(p));
	पूर्ण

	अगर (req < counts->quota)
		counts->spare += counts->quota - req;
	अन्यथा अगर (req > counts->quota)
		counts->over_quota++;

	वापस शून्य;
पूर्ण

अटल पूर्णांक msi_quota_क्रम_device(काष्ठा pci_dev *dev, पूर्णांक request)
अणु
	काष्ठा device_node *pe_dn;
	काष्ठा msi_counts counts;
	पूर्णांक total;

	pr_debug("rtas_msi: calc quota for %s, request %d\n", pci_name(dev),
		  request);

	pe_dn = find_pe_total_msi(dev, &total);
	अगर (!pe_dn)
		pe_dn = find_pe_dn(dev, &total);

	अगर (!pe_dn) अणु
		pr_err("rtas_msi: couldn't find PE for %s\n", pci_name(dev));
		जाओ out;
	पूर्ण

	pr_debug("rtas_msi: found PE %pOF\n", pe_dn);

	स_रखो(&counts, 0, माप(काष्ठा msi_counts));

	/* Work out how many devices we have below this PE */
	pci_traverse_device_nodes(pe_dn, count_non_bridge_devices, &counts);

	अगर (counts.num_devices == 0) अणु
		pr_err("rtas_msi: found 0 devices under PE for %s\n",
			pci_name(dev));
		जाओ out;
	पूर्ण

	counts.quota = total / counts.num_devices;
	अगर (request <= counts.quota)
		जाओ out;

	/* अन्यथा, we have some more calculating to करो */
	counts.requestor = pci_device_to_OF_node(dev);
	counts.request = request;
	pci_traverse_device_nodes(pe_dn, count_spare_msis, &counts);

	/* If the quota isn't an पूर्णांकeger multiple of the total, we can
	 * use the reमुख्यder as spare MSIs क्रम anyone that wants them. */
	counts.spare += total % counts.num_devices;

	/* Divide any spare by the number of over-quota requestors */
	अगर (counts.over_quota)
		counts.quota += counts.spare / counts.over_quota;

	/* And finally clamp the request to the possibly adjusted quota */
	request = min(counts.quota, request);

	pr_debug("rtas_msi: request clamped to quota %d\n", request);
out:
	of_node_put(pe_dn);

	वापस request;
पूर्ण

अटल पूर्णांक check_msix_entries(काष्ठा pci_dev *pdev)
अणु
	काष्ठा msi_desc *entry;
	पूर्णांक expected;

	/* There's no way क्रम us to express to firmware that we want
	 * a discontiguous, or non-zero based, range of MSI-X entries.
	 * So we must reject such requests. */

	expected = 0;
	क्रम_each_pci_msi_entry(entry, pdev) अणु
		अगर (entry->msi_attrib.entry_nr != expected) अणु
			pr_debug("rtas_msi: bad MSI-X entries.\n");
			वापस -EINVAL;
		पूर्ण
		expected++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtas_hack_32bit_msi_gen2(काष्ठा pci_dev *pdev)
अणु
	u32 addr_hi, addr_lo;

	/*
	 * We should only get in here क्रम IODA1 configs. This is based on the
	 * fact that we using RTAS क्रम MSIs, we करोn't have the 32 bit MSI RTAS
	 * support, and we are in a PCIe Gen2 slot.
	 */
	dev_info(&pdev->dev,
		 "rtas_msi: No 32 bit MSI firmware support, forcing 32 bit MSI\n");
	pci_पढ़ो_config_dword(pdev, pdev->msi_cap + PCI_MSI_ADDRESS_HI, &addr_hi);
	addr_lo = 0xffff0000 | ((addr_hi >> (48 - 32)) << 4);
	pci_ग_लिखो_config_dword(pdev, pdev->msi_cap + PCI_MSI_ADDRESS_LO, addr_lo);
	pci_ग_लिखो_config_dword(pdev, pdev->msi_cap + PCI_MSI_ADDRESS_HI, 0);
पूर्ण

अटल पूर्णांक rtas_setup_msi_irqs(काष्ठा pci_dev *pdev, पूर्णांक nvec_in, पूर्णांक type)
अणु
	काष्ठा pci_dn *pdn;
	पूर्णांक hwirq, virq, i, quota, rc;
	काष्ठा msi_desc *entry;
	काष्ठा msi_msg msg;
	पूर्णांक nvec = nvec_in;
	पूर्णांक use_32bit_msi_hack = 0;

	अगर (type == PCI_CAP_ID_MSIX)
		rc = check_req_msix(pdev, nvec);
	अन्यथा
		rc = check_req_msi(pdev, nvec);

	अगर (rc)
		वापस rc;

	quota = msi_quota_क्रम_device(pdev, nvec);

	अगर (quota && quota < nvec)
		वापस quota;

	अगर (type == PCI_CAP_ID_MSIX && check_msix_entries(pdev))
		वापस -EINVAL;

	/*
	 * Firmware currently refuse any non घातer of two allocation
	 * so we round up अगर the quota will allow it.
	 */
	अगर (type == PCI_CAP_ID_MSIX) अणु
		पूर्णांक m = roundup_घात_of_two(nvec);
		quota = msi_quota_क्रम_device(pdev, m);

		अगर (quota >= m)
			nvec = m;
	पूर्ण

	pdn = pci_get_pdn(pdev);

	/*
	 * Try the new more explicit firmware पूर्णांकerface, अगर that fails fall
	 * back to the old पूर्णांकerface. The old पूर्णांकerface is known to never
	 * वापस MSI-Xs.
	 */
again:
	अगर (type == PCI_CAP_ID_MSI) अणु
		अगर (pdev->no_64bit_msi) अणु
			rc = rtas_change_msi(pdn, RTAS_CHANGE_32MSI_FN, nvec);
			अगर (rc < 0) अणु
				/*
				 * We only want to run the 32 bit MSI hack below अगर
				 * the max bus speed is Gen2 speed
				 */
				अगर (pdev->bus->max_bus_speed != PCIE_SPEED_5_0GT)
					वापस rc;

				use_32bit_msi_hack = 1;
			पूर्ण
		पूर्ण अन्यथा
			rc = -1;

		अगर (rc < 0)
			rc = rtas_change_msi(pdn, RTAS_CHANGE_MSI_FN, nvec);

		अगर (rc < 0) अणु
			pr_debug("rtas_msi: trying the old firmware call.\n");
			rc = rtas_change_msi(pdn, RTAS_CHANGE_FN, nvec);
		पूर्ण

		अगर (use_32bit_msi_hack && rc > 0)
			rtas_hack_32bit_msi_gen2(pdev);
	पूर्ण अन्यथा
		rc = rtas_change_msi(pdn, RTAS_CHANGE_MSIX_FN, nvec);

	अगर (rc != nvec) अणु
		अगर (nvec != nvec_in) अणु
			nvec = nvec_in;
			जाओ again;
		पूर्ण
		pr_debug("rtas_msi: rtas_change_msi() failed\n");
		वापस rc;
	पूर्ण

	i = 0;
	क्रम_each_pci_msi_entry(entry, pdev) अणु
		hwirq = rtas_query_irq_number(pdn, i++);
		अगर (hwirq < 0) अणु
			pr_debug("rtas_msi: error (%d) getting hwirq\n", rc);
			वापस hwirq;
		पूर्ण

		/*
		 * Depending on the number of online CPUs in the original
		 * kernel, it is likely क्रम CPU #0 to be offline in a kdump
		 * kernel. The associated IRQs in the affinity mappings
		 * provided by irq_create_affinity_masks() are thus not
		 * started by irq_startup(), as per-design क्रम managed IRQs.
		 * This can be a problem with multi-queue block devices driven
		 * by blk-mq : such a non-started IRQ is very likely paired
		 * with the single queue enक्रमced by blk-mq during kdump (see
		 * blk_mq_alloc_tag_set()). This causes the device to reमुख्य
		 * silent and likely hangs the guest at some poपूर्णांक.
		 *
		 * We करोn't really care क्रम fine-grained affinity when करोing
		 * kdump actually : simply ignore the pre-computed affinity
		 * masks in this हाल and let the शेष mask with all CPUs
		 * be used when creating the IRQ mappings.
		 */
		अगर (is_kdump_kernel())
			virq = irq_create_mapping(शून्य, hwirq);
		अन्यथा
			virq = irq_create_mapping_affinity(शून्य, hwirq,
							   entry->affinity);

		अगर (!virq) अणु
			pr_debug("rtas_msi: Failed mapping hwirq %d\n", hwirq);
			वापस -ENOSPC;
		पूर्ण

		dev_dbg(&pdev->dev, "rtas_msi: allocated virq %d\n", virq);
		irq_set_msi_desc(virq, entry);

		/* Read config space back so we can restore after reset */
		__pci_पढ़ो_msi_msg(entry, &msg);
		entry->msg = msg;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtas_msi_pci_irq_fixup(काष्ठा pci_dev *pdev)
अणु
	/* No LSI -> leave MSIs (अगर any) configured */
	अगर (!pdev->irq) अणु
		dev_dbg(&pdev->dev, "rtas_msi: no LSI, nothing to do.\n");
		वापस;
	पूर्ण

	/* No MSI -> MSIs can't have been asचिन्हित by fw, leave LSI */
	अगर (check_req_msi(pdev, 1) && check_req_msix(pdev, 1)) अणु
		dev_dbg(&pdev->dev, "rtas_msi: no req#msi/x, nothing to do.\n");
		वापस;
	पूर्ण

	dev_dbg(&pdev->dev, "rtas_msi: disabling existing MSI.\n");
	rtas_disable_msi(pdev);
पूर्ण

अटल पूर्णांक rtas_msi_init(व्योम)
अणु
	काष्ठा pci_controller *phb;

	query_token  = rtas_token("ibm,query-interrupt-source-number");
	change_token = rtas_token("ibm,change-msi");

	अगर ((query_token == RTAS_UNKNOWN_SERVICE) ||
			(change_token == RTAS_UNKNOWN_SERVICE)) अणु
		pr_debug("rtas_msi: no RTAS tokens, no MSI support.\n");
		वापस -1;
	पूर्ण

	pr_debug("rtas_msi: Registering RTAS MSI callbacks.\n");

	WARN_ON(pseries_pci_controller_ops.setup_msi_irqs);
	pseries_pci_controller_ops.setup_msi_irqs = rtas_setup_msi_irqs;
	pseries_pci_controller_ops.tearकरोwn_msi_irqs = rtas_tearकरोwn_msi_irqs;

	list_क्रम_each_entry(phb, &hose_list, list_node) अणु
		WARN_ON(phb->controller_ops.setup_msi_irqs);
		phb->controller_ops.setup_msi_irqs = rtas_setup_msi_irqs;
		phb->controller_ops.tearकरोwn_msi_irqs = rtas_tearकरोwn_msi_irqs;
	पूर्ण

	WARN_ON(ppc_md.pci_irq_fixup);
	ppc_md.pci_irq_fixup = rtas_msi_pci_irq_fixup;

	वापस 0;
पूर्ण
machine_arch_initcall(pseries, rtas_msi_init);
