<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001 Dave Engebretsen, IBM Corporation
 * Copyright (C) 2003 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 *
 * RTAS specअगरic routines क्रम PCI.
 *
 * Based on code from pci.c, chrp_pci.c and pSeries_pci.c
 */

#समावेश <linux/kernel.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/eeh.h>

/* RTAS tokens */
अटल पूर्णांक पढ़ो_pci_config;
अटल पूर्णांक ग_लिखो_pci_config;
अटल पूर्णांक ibm_पढ़ो_pci_config;
अटल पूर्णांक ibm_ग_लिखो_pci_config;

अटल अंतरभूत पूर्णांक config_access_valid(काष्ठा pci_dn *dn, पूर्णांक where)
अणु
	अगर (where < 256)
		वापस 1;
	अगर (where < 4096 && dn->pci_ext_config_space)
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक rtas_पढ़ो_config(काष्ठा pci_dn *pdn, पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	पूर्णांक वापसval = -1;
	अचिन्हित दीर्घ buid, addr;
	पूर्णांक ret;

	अगर (!pdn)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	अगर (!config_access_valid(pdn, where))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
#अगर_घोषित CONFIG_EEH
	अगर (pdn->edev && pdn->edev->pe &&
	    (pdn->edev->pe->state & EEH_PE_CFG_BLOCKED))
		वापस PCIBIOS_SET_FAILED;
#पूर्ण_अगर

	addr = rtas_config_addr(pdn->busno, pdn->devfn, where);
	buid = pdn->phb->buid;
	अगर (buid) अणु
		ret = rtas_call(ibm_पढ़ो_pci_config, 4, 2, &वापसval,
				addr, BUID_HI(buid), BUID_LO(buid), size);
	पूर्ण अन्यथा अणु
		ret = rtas_call(पढ़ो_pci_config, 2, 2, &वापसval, addr, size);
	पूर्ण
	*val = वापसval;

	अगर (ret)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक rtas_pci_पढ़ो_config(काष्ठा pci_bus *bus,
				अचिन्हित पूर्णांक devfn,
				पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा pci_dn *pdn;
	पूर्णांक ret;

	*val = 0xFFFFFFFF;

	pdn = pci_get_pdn_by_devfn(bus, devfn);

	/* Validity of pdn is checked in here */
	ret = rtas_पढ़ो_config(pdn, where, size, val);
	अगर (*val == EEH_IO_ERROR_VALUE(size) &&
	    eeh_dev_check_failure(pdn_to_eeh_dev(pdn)))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस ret;
पूर्ण

पूर्णांक rtas_ग_लिखो_config(काष्ठा pci_dn *pdn, पूर्णांक where, पूर्णांक size, u32 val)
अणु
	अचिन्हित दीर्घ buid, addr;
	पूर्णांक ret;

	अगर (!pdn)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	अगर (!config_access_valid(pdn, where))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
#अगर_घोषित CONFIG_EEH
	अगर (pdn->edev && pdn->edev->pe &&
	    (pdn->edev->pe->state & EEH_PE_CFG_BLOCKED))
		वापस PCIBIOS_SET_FAILED;
#पूर्ण_अगर

	addr = rtas_config_addr(pdn->busno, pdn->devfn, where);
	buid = pdn->phb->buid;
	अगर (buid) अणु
		ret = rtas_call(ibm_ग_लिखो_pci_config, 5, 1, शून्य, addr,
			BUID_HI(buid), BUID_LO(buid), size, (uदीर्घ) val);
	पूर्ण अन्यथा अणु
		ret = rtas_call(ग_लिखो_pci_config, 3, 1, शून्य, addr, size, (uदीर्घ)val);
	पूर्ण

	अगर (ret)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक rtas_pci_ग_लिखो_config(काष्ठा pci_bus *bus,
				 अचिन्हित पूर्णांक devfn,
				 पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा pci_dn *pdn;

	pdn = pci_get_pdn_by_devfn(bus, devfn);

	/* Validity of pdn is checked in here. */
	वापस rtas_ग_लिखो_config(pdn, where, size, val);
पूर्ण

अटल काष्ठा pci_ops rtas_pci_ops = अणु
	.पढ़ो = rtas_pci_पढ़ो_config,
	.ग_लिखो = rtas_pci_ग_लिखो_config,
पूर्ण;

अटल पूर्णांक is_python(काष्ठा device_node *dev)
अणु
	स्थिर अक्षर *model = of_get_property(dev, "model", शून्य);

	अगर (model && म_माला(model, "Python"))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम python_countermeasures(काष्ठा device_node *dev)
अणु
	काष्ठा resource रेजिस्टरs;
	व्योम __iomem *chip_regs;
	अस्थिर u32 val;

	अगर (of_address_to_resource(dev, 0, &रेजिस्टरs)) अणु
		prपूर्णांकk(KERN_ERR "Can't get address for Python workarounds !\n");
		वापस;
	पूर्ण

	/* Python's रेजिस्टर file is 1 MB in size. */
	chip_regs = ioremap(रेजिस्टरs.start & ~(0xfffffUL), 0x100000);

	/*
	 * Firmware करोesn't always clear this bit which is critical
	 * क्रम good perक्रमmance - Anton
	 */

#घोषणा PRG_CL_RESET_VALID 0x00010000

	val = in_be32(chip_regs + 0xf6030);
	अगर (val & PRG_CL_RESET_VALID) अणु
		prपूर्णांकk(KERN_INFO "Python workaround: ");
		val &= ~PRG_CL_RESET_VALID;
		out_be32(chip_regs + 0xf6030, val);
		/*
		 * We must पढ़ो it back क्रम changes to
		 * take effect
		 */
		val = in_be32(chip_regs + 0xf6030);
		prपूर्णांकk("reg0: %x\n", val);
	पूर्ण

	iounmap(chip_regs);
पूर्ण

व्योम __init init_pci_config_tokens(व्योम)
अणु
	पढ़ो_pci_config = rtas_token("read-pci-config");
	ग_लिखो_pci_config = rtas_token("write-pci-config");
	ibm_पढ़ो_pci_config = rtas_token("ibm,read-pci-config");
	ibm_ग_लिखो_pci_config = rtas_token("ibm,write-pci-config");
पूर्ण

अचिन्हित दीर्घ get_phb_buid(काष्ठा device_node *phb)
अणु
	काष्ठा resource r;

	अगर (ibm_पढ़ो_pci_config == -1)
		वापस 0;
	अगर (of_address_to_resource(phb, 0, &r))
		वापस 0;
	वापस r.start;
पूर्ण

अटल पूर्णांक phb_set_bus_ranges(काष्ठा device_node *dev,
			      काष्ठा pci_controller *phb)
अणु
	स्थिर __be32 *bus_range;
	अचिन्हित पूर्णांक len;

	bus_range = of_get_property(dev, "bus-range", &len);
	अगर (bus_range == शून्य || len < 2 * माप(पूर्णांक)) अणु
		वापस 1;
 	पूर्ण

	phb->first_busno = be32_to_cpu(bus_range[0]);
	phb->last_busno  = be32_to_cpu(bus_range[1]);

	वापस 0;
पूर्ण

पूर्णांक rtas_setup_phb(काष्ठा pci_controller *phb)
अणु
	काष्ठा device_node *dev = phb->dn;

	अगर (is_python(dev))
		python_countermeasures(dev);

	अगर (phb_set_bus_ranges(dev, phb))
		वापस 1;

	phb->ops = &rtas_pci_ops;
	phb->buid = get_phb_buid(dev);

	वापस 0;
पूर्ण
