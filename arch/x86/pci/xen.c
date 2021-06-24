<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Xen PCI - handle PCI (INTx) and MSI infraकाष्ठाure calls क्रम PV, HVM and
 * initial करोमुख्य support. We also handle the DSDT _PRT callbacks क्रम GSI's
 * used in HVM and initial करोमुख्य mode (PV करोes not parse ACPI, so it has no
 * concept of GSIs). Under PV we hook under the pnbbios API क्रम IRQs and
 * 0xcf8 PCI configuration पढ़ो/ग_लिखो.
 *
 *   Author: Ryan Wilson <hap9@epoch.ncsc.mil>
 *           Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
 *           Stefano Stabellini <stefano.stabellini@eu.citrix.com>
 */
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>

#समावेश <linux/पन.स>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/pci_x86.h>

#समावेश <यंत्र/xen/hypervisor.h>

#समावेश <xen/features.h>
#समावेश <xen/events.h>
#समावेश <यंत्र/xen/pci.h>
#समावेश <यंत्र/xen/cpuid.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/i8259.h>

अटल पूर्णांक xen_pcअगरront_enable_irq(काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc;
	पूर्णांक share = 1;
	पूर्णांक pirq;
	u8 gsi;

	rc = pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_LINE, &gsi);
	अगर (rc < 0) अणु
		dev_warn(&dev->dev, "Xen PCI: failed to read interrupt line: %d\n",
			 rc);
		वापस rc;
	पूर्ण
	/* In PV DomU the Xen PCI backend माला_दो the PIRQ in the पूर्णांकerrupt line.*/
	pirq = gsi;

	अगर (gsi < nr_legacy_irqs())
		share = 0;

	rc = xen_bind_pirq_gsi_to_irq(gsi, pirq, share, "pcifront");
	अगर (rc < 0) अणु
		dev_warn(&dev->dev, "Xen PCI: failed to bind GSI%d (PIRQ%d) to IRQ: %d\n",
			 gsi, pirq, rc);
		वापस rc;
	पूर्ण

	dev->irq = rc;
	dev_info(&dev->dev, "Xen PCI mapped GSI%d to IRQ%d\n", gsi, dev->irq);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक xen_रेजिस्टर_pirq(u32 gsi, पूर्णांक triggering, bool set_pirq)
अणु
	पूर्णांक rc, pirq = -1, irq;
	काष्ठा physdev_map_pirq map_irq;
	पूर्णांक shareable = 0;
	अक्षर *name;

	irq = xen_irq_from_gsi(gsi);
	अगर (irq > 0)
		वापस irq;

	अगर (set_pirq)
		pirq = gsi;

	map_irq.करोmid = DOMID_SELF;
	map_irq.type = MAP_PIRQ_TYPE_GSI;
	map_irq.index = gsi;
	map_irq.pirq = pirq;

	rc = HYPERVISOR_physdev_op(PHYSDEVOP_map_pirq, &map_irq);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "xen map irq failed %d\n", rc);
		वापस -1;
	पूर्ण

	अगर (triggering == ACPI_EDGE_SENSITIVE) अणु
		shareable = 0;
		name = "ioapic-edge";
	पूर्ण अन्यथा अणु
		shareable = 1;
		name = "ioapic-level";
	पूर्ण

	irq = xen_bind_pirq_gsi_to_irq(gsi, map_irq.pirq, shareable, name);
	अगर (irq < 0)
		जाओ out;

	prपूर्णांकk(KERN_DEBUG "xen: --> pirq=%d -> irq=%d (gsi=%d)\n", map_irq.pirq, irq, gsi);
out:
	वापस irq;
पूर्ण

अटल पूर्णांक acpi_रेजिस्टर_gsi_xen_hvm(काष्ठा device *dev, u32 gsi,
				     पूर्णांक trigger, पूर्णांक polarity)
अणु
	अगर (!xen_hvm_करोमुख्य())
		वापस -1;

	वापस xen_रेजिस्टर_pirq(gsi, trigger,
				 false /* no mapping of GSI to PIRQ */);
पूर्ण

#अगर_घोषित CONFIG_XEN_DOM0
अटल पूर्णांक xen_रेजिस्टर_gsi(u32 gsi, पूर्णांक triggering, पूर्णांक polarity)
अणु
	पूर्णांक rc, irq;
	काष्ठा physdev_setup_gsi setup_gsi;

	अगर (!xen_pv_करोमुख्य())
		वापस -1;

	prपूर्णांकk(KERN_DEBUG "xen: registering gsi %u triggering %d polarity %d\n",
			gsi, triggering, polarity);

	irq = xen_रेजिस्टर_pirq(gsi, triggering, true);

	setup_gsi.gsi = gsi;
	setup_gsi.triggering = (triggering == ACPI_EDGE_SENSITIVE ? 0 : 1);
	setup_gsi.polarity = (polarity == ACPI_ACTIVE_HIGH ? 0 : 1);

	rc = HYPERVISOR_physdev_op(PHYSDEVOP_setup_gsi, &setup_gsi);
	अगर (rc == -EEXIST)
		prपूर्णांकk(KERN_INFO "Already setup the GSI :%d\n", gsi);
	अन्यथा अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Failed to setup GSI :%d, err_code:%d\n",
				gsi, rc);
	पूर्ण

	वापस irq;
पूर्ण

अटल पूर्णांक acpi_रेजिस्टर_gsi_xen(काष्ठा device *dev, u32 gsi,
				 पूर्णांक trigger, पूर्णांक polarity)
अणु
	वापस xen_रेजिस्टर_gsi(gsi, trigger, polarity);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर defined(CONFIG_PCI_MSI)
#समावेश <linux/msi.h>

काष्ठा xen_pci_frontend_ops *xen_pci_frontend;
EXPORT_SYMBOL_GPL(xen_pci_frontend);

काष्ठा xen_msi_ops अणु
	पूर्णांक (*setup_msi_irqs)(काष्ठा pci_dev *dev, पूर्णांक nvec, पूर्णांक type);
	व्योम (*tearकरोwn_msi_irqs)(काष्ठा pci_dev *dev);
पूर्ण;

अटल काष्ठा xen_msi_ops xen_msi_ops __ro_after_init;

अटल पूर्णांक xen_setup_msi_irqs(काष्ठा pci_dev *dev, पूर्णांक nvec, पूर्णांक type)
अणु
	पूर्णांक irq, ret, i;
	काष्ठा msi_desc *msidesc;
	पूर्णांक *v;

	अगर (type == PCI_CAP_ID_MSI && nvec > 1)
		वापस 1;

	v = kसुस्मृति(max(1, nvec), माप(पूर्णांक), GFP_KERNEL);
	अगर (!v)
		वापस -ENOMEM;

	अगर (type == PCI_CAP_ID_MSIX)
		ret = xen_pci_frontend_enable_msix(dev, v, nvec);
	अन्यथा
		ret = xen_pci_frontend_enable_msi(dev, v);
	अगर (ret)
		जाओ error;
	i = 0;
	क्रम_each_pci_msi_entry(msidesc, dev) अणु
		irq = xen_bind_pirq_msi_to_irq(dev, msidesc, v[i],
					       (type == PCI_CAP_ID_MSI) ? nvec : 1,
					       (type == PCI_CAP_ID_MSIX) ?
					       "pcifront-msi-x" :
					       "pcifront-msi",
						DOMID_SELF);
		अगर (irq < 0) अणु
			ret = irq;
			जाओ मुक्त;
		पूर्ण
		i++;
	पूर्ण
	kमुक्त(v);
	वापस 0;

error:
	अगर (ret == -ENOSYS)
		dev_err(&dev->dev, "Xen PCI frontend has not registered MSI/MSI-X support!\n");
	अन्यथा अगर (ret)
		dev_err(&dev->dev, "Xen PCI frontend error: %d!\n", ret);
मुक्त:
	kमुक्त(v);
	वापस ret;
पूर्ण

अटल व्योम xen_msi_compose_msg(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक pirq,
		काष्ठा msi_msg *msg)
अणु
	/*
	 * We set vector == 0 to tell the hypervisor we करोn't care about
	 * it, but we want a pirq setup instead.  We use the dest_id fields
	 * to pass the pirq that we want.
	 */
	स_रखो(msg, 0, माप(*msg));
	msg->address_hi = X86_MSI_BASE_ADDRESS_HIGH;
	msg->arch_addr_hi.destid_8_31 = pirq >> 8;
	msg->arch_addr_lo.destid_0_7 = pirq & 0xFF;
	msg->arch_addr_lo.base_address = X86_MSI_BASE_ADDRESS_LOW;
	msg->arch_data.delivery_mode = APIC_DELIVERY_MODE_EXTINT;
पूर्ण

अटल पूर्णांक xen_hvm_setup_msi_irqs(काष्ठा pci_dev *dev, पूर्णांक nvec, पूर्णांक type)
अणु
	पूर्णांक irq, pirq;
	काष्ठा msi_desc *msidesc;
	काष्ठा msi_msg msg;

	अगर (type == PCI_CAP_ID_MSI && nvec > 1)
		वापस 1;

	क्रम_each_pci_msi_entry(msidesc, dev) अणु
		pirq = xen_allocate_pirq_msi(dev, msidesc);
		अगर (pirq < 0) अणु
			irq = -ENODEV;
			जाओ error;
		पूर्ण
		xen_msi_compose_msg(dev, pirq, &msg);
		__pci_ग_लिखो_msi_msg(msidesc, &msg);
		dev_dbg(&dev->dev, "xen: msi bound to pirq=%d\n", pirq);
		irq = xen_bind_pirq_msi_to_irq(dev, msidesc, pirq,
					       (type == PCI_CAP_ID_MSI) ? nvec : 1,
					       (type == PCI_CAP_ID_MSIX) ?
					       "msi-x" : "msi",
					       DOMID_SELF);
		अगर (irq < 0)
			जाओ error;
		dev_dbg(&dev->dev,
			"xen: msi --> pirq=%d --> irq=%d\n", pirq, irq);
	पूर्ण
	वापस 0;

error:
	dev_err(&dev->dev, "Failed to create MSI%s! ret=%d!\n",
		type == PCI_CAP_ID_MSI ? "" : "-X", irq);
	वापस irq;
पूर्ण

#अगर_घोषित CONFIG_XEN_DOM0
अटल bool __पढ़ो_mostly pci_seg_supported = true;

अटल पूर्णांक xen_initकरोm_setup_msi_irqs(काष्ठा pci_dev *dev, पूर्णांक nvec, पूर्णांक type)
अणु
	पूर्णांक ret = 0;
	काष्ठा msi_desc *msidesc;

	क्रम_each_pci_msi_entry(msidesc, dev) अणु
		काष्ठा physdev_map_pirq map_irq;
		करोmid_t करोmid;

		करोmid = ret = xen_find_device_करोमुख्य_owner(dev);
		/* N.B. Casting पूर्णांक's -ENODEV to uपूर्णांक16_t results in 0xFFED,
		 * hence check ret value क्रम < 0. */
		अगर (ret < 0)
			करोmid = DOMID_SELF;

		स_रखो(&map_irq, 0, माप(map_irq));
		map_irq.करोmid = करोmid;
		map_irq.type = MAP_PIRQ_TYPE_MSI_SEG;
		map_irq.index = -1;
		map_irq.pirq = -1;
		map_irq.bus = dev->bus->number |
			      (pci_करोमुख्य_nr(dev->bus) << 16);
		map_irq.devfn = dev->devfn;

		अगर (type == PCI_CAP_ID_MSI && nvec > 1) अणु
			map_irq.type = MAP_PIRQ_TYPE_MULTI_MSI;
			map_irq.entry_nr = nvec;
		पूर्ण अन्यथा अगर (type == PCI_CAP_ID_MSIX) अणु
			पूर्णांक pos;
			अचिन्हित दीर्घ flags;
			u32 table_offset, bir;

			pos = dev->msix_cap;
			pci_पढ़ो_config_dword(dev, pos + PCI_MSIX_TABLE,
					      &table_offset);
			bir = (u8)(table_offset & PCI_MSIX_TABLE_BIR);
			flags = pci_resource_flags(dev, bir);
			अगर (!flags || (flags & IORESOURCE_UNSET))
				वापस -EINVAL;

			map_irq.table_base = pci_resource_start(dev, bir);
			map_irq.entry_nr = msidesc->msi_attrib.entry_nr;
		पूर्ण

		ret = -EINVAL;
		अगर (pci_seg_supported)
			ret = HYPERVISOR_physdev_op(PHYSDEVOP_map_pirq,
						    &map_irq);
		अगर (type == PCI_CAP_ID_MSI && nvec > 1 && ret) अणु
			/*
			 * If MAP_PIRQ_TYPE_MULTI_MSI is not available
			 * there's nothing अन्यथा we can करो in this हाल.
			 * Just set ret > 0 so driver can retry with
			 * single MSI.
			 */
			ret = 1;
			जाओ out;
		पूर्ण
		अगर (ret == -EINVAL && !pci_करोमुख्य_nr(dev->bus)) अणु
			map_irq.type = MAP_PIRQ_TYPE_MSI;
			map_irq.index = -1;
			map_irq.pirq = -1;
			map_irq.bus = dev->bus->number;
			ret = HYPERVISOR_physdev_op(PHYSDEVOP_map_pirq,
						    &map_irq);
			अगर (ret != -EINVAL)
				pci_seg_supported = false;
		पूर्ण
		अगर (ret) अणु
			dev_warn(&dev->dev, "xen map irq failed %d for %d domain\n",
				 ret, करोmid);
			जाओ out;
		पूर्ण

		ret = xen_bind_pirq_msi_to_irq(dev, msidesc, map_irq.pirq,
		                               (type == PCI_CAP_ID_MSI) ? nvec : 1,
		                               (type == PCI_CAP_ID_MSIX) ? "msi-x" : "msi",
		                               करोmid);
		अगर (ret < 0)
			जाओ out;
	पूर्ण
	ret = 0;
out:
	वापस ret;
पूर्ण

अटल व्योम xen_initकरोm_restore_msi_irqs(काष्ठा pci_dev *dev)
अणु
	पूर्णांक ret = 0;

	अगर (pci_seg_supported) अणु
		काष्ठा physdev_pci_device restore_ext;

		restore_ext.seg = pci_करोमुख्य_nr(dev->bus);
		restore_ext.bus = dev->bus->number;
		restore_ext.devfn = dev->devfn;
		ret = HYPERVISOR_physdev_op(PHYSDEVOP_restore_msi_ext,
					&restore_ext);
		अगर (ret == -ENOSYS)
			pci_seg_supported = false;
		WARN(ret && ret != -ENOSYS, "restore_msi_ext -> %d\n", ret);
	पूर्ण
	अगर (!pci_seg_supported) अणु
		काष्ठा physdev_restore_msi restore;

		restore.bus = dev->bus->number;
		restore.devfn = dev->devfn;
		ret = HYPERVISOR_physdev_op(PHYSDEVOP_restore_msi, &restore);
		WARN(ret && ret != -ENOSYS, "restore_msi -> %d\n", ret);
	पूर्ण
पूर्ण
#अन्यथा /* CONFIG_XEN_DOM0 */
#घोषणा xen_initकरोm_setup_msi_irqs	शून्य
#घोषणा xen_initकरोm_restore_msi_irqs	शून्य
#पूर्ण_अगर /* !CONFIG_XEN_DOM0 */

अटल व्योम xen_tearकरोwn_msi_irqs(काष्ठा pci_dev *dev)
अणु
	काष्ठा msi_desc *msidesc;
	पूर्णांक i;

	क्रम_each_pci_msi_entry(msidesc, dev) अणु
		अगर (msidesc->irq) अणु
			क्रम (i = 0; i < msidesc->nvec_used; i++)
				xen_destroy_irq(msidesc->irq + i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम xen_pv_tearकरोwn_msi_irqs(काष्ठा pci_dev *dev)
अणु
	काष्ठा msi_desc *msidesc = first_pci_msi_entry(dev);

	अगर (msidesc->msi_attrib.is_msix)
		xen_pci_frontend_disable_msix(dev);
	अन्यथा
		xen_pci_frontend_disable_msi(dev);

	xen_tearकरोwn_msi_irqs(dev);
पूर्ण

अटल पूर्णांक xen_msi_करोमुख्य_alloc_irqs(काष्ठा irq_करोमुख्य *करोमुख्य,
				     काष्ठा device *dev,  पूर्णांक nvec)
अणु
	पूर्णांक type;

	अगर (WARN_ON_ONCE(!dev_is_pci(dev)))
		वापस -EINVAL;

	अगर (first_msi_entry(dev)->msi_attrib.is_msix)
		type = PCI_CAP_ID_MSIX;
	अन्यथा
		type = PCI_CAP_ID_MSI;

	वापस xen_msi_ops.setup_msi_irqs(to_pci_dev(dev), nvec, type);
पूर्ण

अटल व्योम xen_msi_करोमुख्य_मुक्त_irqs(काष्ठा irq_करोमुख्य *करोमुख्य,
				     काष्ठा device *dev)
अणु
	अगर (WARN_ON_ONCE(!dev_is_pci(dev)))
		वापस;

	xen_msi_ops.tearकरोwn_msi_irqs(to_pci_dev(dev));
पूर्ण

अटल काष्ठा msi_करोमुख्य_ops xen_pci_msi_करोमुख्य_ops = अणु
	.करोमुख्य_alloc_irqs	= xen_msi_करोमुख्य_alloc_irqs,
	.करोमुख्य_मुक्त_irqs	= xen_msi_करोमुख्य_मुक्त_irqs,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info xen_pci_msi_करोमुख्य_info = अणु
	.ops			= &xen_pci_msi_करोमुख्य_ops,
पूर्ण;

/*
 * This irq करोमुख्य is a blatant violation of the irq करोमुख्य design, but
 * distangling XEN पूर्णांकo real irq करोमुख्यs is not a job क्रम mere mortals with
 * limited XENology. But it's the least dangerous way क्रम a mere mortal to
 * get rid of the arch_*_msi_irqs() hackery in order to store the irq
 * करोमुख्य poपूर्णांकer in काष्ठा device. This irq करोमुख्य wrappery allows to करो
 * that without अवरोधing XEN terminally.
 */
अटल __init काष्ठा irq_करोमुख्य *xen_create_pci_msi_करोमुख्य(व्योम)
अणु
	काष्ठा irq_करोमुख्य *d = शून्य;
	काष्ठा fwnode_handle *fn;

	fn = irq_करोमुख्य_alloc_named_fwnode("XEN-MSI");
	अगर (fn)
		d = msi_create_irq_करोमुख्य(fn, &xen_pci_msi_करोमुख्य_info, शून्य);

	/* FIXME: No idea how to survive अगर this fails */
	BUG_ON(!d);

	वापस d;
पूर्ण

अटल __init व्योम xen_setup_pci_msi(व्योम)
अणु
	अगर (xen_pv_करोमुख्य()) अणु
		अगर (xen_initial_करोमुख्य()) अणु
			xen_msi_ops.setup_msi_irqs = xen_initकरोm_setup_msi_irqs;
			x86_msi.restore_msi_irqs = xen_initकरोm_restore_msi_irqs;
		पूर्ण अन्यथा अणु
			xen_msi_ops.setup_msi_irqs = xen_setup_msi_irqs;
		पूर्ण
		xen_msi_ops.tearकरोwn_msi_irqs = xen_pv_tearकरोwn_msi_irqs;
		pci_msi_ignore_mask = 1;
	पूर्ण अन्यथा अगर (xen_hvm_करोमुख्य()) अणु
		xen_msi_ops.setup_msi_irqs = xen_hvm_setup_msi_irqs;
		xen_msi_ops.tearकरोwn_msi_irqs = xen_tearकरोwn_msi_irqs;
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	/*
	 * Override the PCI/MSI irq करोमुख्य init function. No poपूर्णांक
	 * in allocating the native करोमुख्य and never use it.
	 */
	x86_init.irqs.create_pci_msi_करोमुख्य = xen_create_pci_msi_करोमुख्य;
पूर्ण

#अन्यथा /* CONFIG_PCI_MSI */
अटल अंतरभूत व्योम xen_setup_pci_msi(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_MSI */

पूर्णांक __init pci_xen_init(व्योम)
अणु
	अगर (!xen_pv_करोमुख्य() || xen_initial_करोमुख्य())
		वापस -ENODEV;

	prपूर्णांकk(KERN_INFO "PCI: setting up Xen PCI frontend stub\n");

	pcibios_set_cache_line_size();

	pcibios_enable_irq = xen_pcअगरront_enable_irq;
	pcibios_disable_irq = शून्य;

	/* Keep ACPI out of the picture */
	acpi_noirq_set();

	xen_setup_pci_msi();
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
अटल व्योम __init xen_hvm_msi_init(व्योम)
अणु
	अगर (!disable_apic) अणु
		/*
		 * If hardware supports (x2)APIC भवization (as indicated
		 * by hypervisor's leaf 4) then we don't need to use pirqs/
		 * event channels क्रम MSI handling and instead use regular
		 * APIC processing
		 */
		uपूर्णांक32_t eax = cpuid_eax(xen_cpuid_base() + 4);

		अगर (((eax & XEN_HVM_CPUID_X2APIC_VIRT) && x2apic_mode) ||
		    ((eax & XEN_HVM_CPUID_APIC_ACCESS_VIRT) && boot_cpu_has(X86_FEATURE_APIC)))
			वापस;
	पूर्ण
	xen_setup_pci_msi();
पूर्ण
#पूर्ण_अगर

पूर्णांक __init pci_xen_hvm_init(व्योम)
अणु
	अगर (!xen_have_vector_callback || !xen_feature(XENFEAT_hvm_pirqs))
		वापस 0;

#अगर_घोषित CONFIG_ACPI
	/*
	 * We करोn't want to change the actual ACPI delivery model,
	 * just how GSIs get रेजिस्टरed.
	 */
	__acpi_रेजिस्टर_gsi = acpi_रेजिस्टर_gsi_xen_hvm;
	__acpi_unरेजिस्टर_gsi = शून्य;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_MSI
	/*
	 * We need to रुको until after x2apic is initialized
	 * beक्रमe we can set MSI IRQ ops.
	 */
	x86_platक्रमm.apic_post_init = xen_hvm_msi_init;
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_XEN_DOM0
पूर्णांक __init pci_xen_initial_करोमुख्य(व्योम)
अणु
	पूर्णांक irq;

	xen_setup_pci_msi();
	__acpi_रेजिस्टर_gsi = acpi_रेजिस्टर_gsi_xen;
	__acpi_unरेजिस्टर_gsi = शून्य;
	/*
	 * Pre-allocate the legacy IRQs.  Use NR_LEGACY_IRQS here
	 * because we करोn't have a PIC and thus nr_legacy_irqs() is zero.
	 */
	क्रम (irq = 0; irq < NR_IRQS_LEGACY; irq++) अणु
		पूर्णांक trigger, polarity;

		अगर (acpi_get_override_irq(irq, &trigger, &polarity) == -1)
			जारी;

		xen_रेजिस्टर_pirq(irq,
			trigger ? ACPI_LEVEL_SENSITIVE : ACPI_EDGE_SENSITIVE,
			true /* Map GSI to PIRQ */);
	पूर्ण
	अगर (0 == nr_ioapics) अणु
		क्रम (irq = 0; irq < nr_legacy_irqs(); irq++)
			xen_bind_pirq_gsi_to_irq(irq, irq, 0, "xt-pic");
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा xen_device_करोमुख्य_owner अणु
	करोmid_t करोमुख्य;
	काष्ठा pci_dev *dev;
	काष्ठा list_head list;
पूर्ण;

अटल DEFINE_SPINLOCK(dev_करोमुख्य_list_spinlock);
अटल काष्ठा list_head dev_करोमुख्य_list = LIST_HEAD_INIT(dev_करोमुख्य_list);

अटल काष्ठा xen_device_करोमुख्य_owner *find_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा xen_device_करोमुख्य_owner *owner;

	list_क्रम_each_entry(owner, &dev_करोमुख्य_list, list) अणु
		अगर (owner->dev == dev)
			वापस owner;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक xen_find_device_करोमुख्य_owner(काष्ठा pci_dev *dev)
अणु
	काष्ठा xen_device_करोमुख्य_owner *owner;
	पूर्णांक करोमुख्य = -ENODEV;

	spin_lock(&dev_करोमुख्य_list_spinlock);
	owner = find_device(dev);
	अगर (owner)
		करोमुख्य = owner->करोमुख्य;
	spin_unlock(&dev_करोमुख्य_list_spinlock);
	वापस करोमुख्य;
पूर्ण
EXPORT_SYMBOL_GPL(xen_find_device_करोमुख्य_owner);

पूर्णांक xen_रेजिस्टर_device_करोमुख्य_owner(काष्ठा pci_dev *dev, uपूर्णांक16_t करोमुख्य)
अणु
	काष्ठा xen_device_करोमुख्य_owner *owner;

	owner = kzalloc(माप(काष्ठा xen_device_करोमुख्य_owner), GFP_KERNEL);
	अगर (!owner)
		वापस -ENODEV;

	spin_lock(&dev_करोमुख्य_list_spinlock);
	अगर (find_device(dev)) अणु
		spin_unlock(&dev_करोमुख्य_list_spinlock);
		kमुक्त(owner);
		वापस -EEXIST;
	पूर्ण
	owner->करोमुख्य = करोमुख्य;
	owner->dev = dev;
	list_add_tail(&owner->list, &dev_करोमुख्य_list);
	spin_unlock(&dev_करोमुख्य_list_spinlock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xen_रेजिस्टर_device_करोमुख्य_owner);

पूर्णांक xen_unरेजिस्टर_device_करोमुख्य_owner(काष्ठा pci_dev *dev)
अणु
	काष्ठा xen_device_करोमुख्य_owner *owner;

	spin_lock(&dev_करोमुख्य_list_spinlock);
	owner = find_device(dev);
	अगर (!owner) अणु
		spin_unlock(&dev_करोमुख्य_list_spinlock);
		वापस -ENODEV;
	पूर्ण
	list_del(&owner->list);
	spin_unlock(&dev_करोमुख्य_list_spinlock);
	kमुक्त(owner);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xen_unरेजिस्टर_device_करोमुख्य_owner);
#पूर्ण_अगर
