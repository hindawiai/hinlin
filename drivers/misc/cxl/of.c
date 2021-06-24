<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 IBM Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश "cxl.h"


अटल स्थिर __be32 *पढ़ो_prop_string(स्थिर काष्ठा device_node *np,
				स्थिर अक्षर *prop_name)
अणु
	स्थिर __be32 *prop;

	prop = of_get_property(np, prop_name, शून्य);
	अगर (cxl_verbose && prop)
		pr_info("%s: %s\n", prop_name, (अक्षर *) prop);
	वापस prop;
पूर्ण

अटल स्थिर __be32 *पढ़ो_prop_dword(स्थिर काष्ठा device_node *np,
				स्थिर अक्षर *prop_name, u32 *val)
अणु
	स्थिर __be32 *prop;

	prop = of_get_property(np, prop_name, शून्य);
	अगर (prop)
		*val = be32_to_cpu(prop[0]);
	अगर (cxl_verbose && prop)
		pr_info("%s: %#x (%u)\n", prop_name, *val, *val);
	वापस prop;
पूर्ण

अटल स्थिर __be64 *पढ़ो_prop64_dword(स्थिर काष्ठा device_node *np,
				स्थिर अक्षर *prop_name, u64 *val)
अणु
	स्थिर __be64 *prop;

	prop = of_get_property(np, prop_name, शून्य);
	अगर (prop)
		*val = be64_to_cpu(prop[0]);
	अगर (cxl_verbose && prop)
		pr_info("%s: %#llx (%llu)\n", prop_name, *val, *val);
	वापस prop;
पूर्ण


अटल पूर्णांक पढ़ो_handle(काष्ठा device_node *np, u64 *handle)
अणु
	स्थिर __be32 *prop;
	u64 size;

	/* Get address and size of the node */
	prop = of_get_address(np, 0, &size, शून्य);
	अगर (size)
		वापस -EINVAL;

	/* Helper to पढ़ो a big number; size is in cells (not bytes) */
	*handle = of_पढ़ो_number(prop, of_n_addr_cells(np));
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_phys_addr(काष्ठा device_node *np, अक्षर *prop_name,
			काष्ठा cxl_afu *afu)
अणु
	पूर्णांक i, len, entry_size, naddr, nsize, type;
	u64 addr, size;
	स्थिर __be32 *prop;

	naddr = of_n_addr_cells(np);
	nsize = of_n_size_cells(np);

	prop = of_get_property(np, prop_name, &len);
	अगर (prop) अणु
		entry_size = naddr + nsize;
		क्रम (i = 0; i < (len / 4); i += entry_size, prop += entry_size) अणु
			type = be32_to_cpu(prop[0]);
			addr = of_पढ़ो_number(prop, naddr);
			size = of_पढ़ो_number(&prop[naddr], nsize);
			चयन (type) अणु
			हाल 0: /* unit address */
				afu->guest->handle = addr;
				अवरोध;
			हाल 1: /* p2 area */
				afu->guest->p2n_phys += addr;
				afu->guest->p2n_size = size;
				अवरोध;
			हाल 2: /* problem state area */
				afu->psn_phys += addr;
				afu->adapter->ps_size = size;
				अवरोध;
			शेष:
				pr_err("Invalid address type %d found in %s property of AFU\n",
					type, prop_name);
				वापस -EINVAL;
			पूर्ण
			अगर (cxl_verbose)
				pr_info("%s: %#x %#llx (size %#llx)\n",
					prop_name, type, addr, size);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_vpd(काष्ठा cxl *adapter, काष्ठा cxl_afu *afu)
अणु
	अक्षर vpd[256];
	पूर्णांक rc;
	माप_प्रकार len = माप(vpd);

	स_रखो(vpd, 0, len);

	अगर (adapter)
		rc = cxl_guest_पढ़ो_adapter_vpd(adapter, vpd, len);
	अन्यथा
		rc = cxl_guest_पढ़ो_afu_vpd(afu, vpd, len);

	अगर (rc > 0) अणु
		cxl_dump_debug_buffer(vpd, rc);
		rc = 0;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक cxl_of_पढ़ो_afu_handle(काष्ठा cxl_afu *afu, काष्ठा device_node *afu_np)
अणु
	अगर (पढ़ो_handle(afu_np, &afu->guest->handle))
		वापस -EINVAL;
	pr_devel("AFU handle: 0x%.16llx\n", afu->guest->handle);

	वापस 0;
पूर्ण

पूर्णांक cxl_of_पढ़ो_afu_properties(काष्ठा cxl_afu *afu, काष्ठा device_node *np)
अणु
	पूर्णांक i, len, rc;
	अक्षर *p;
	स्थिर __be32 *prop;
	u16 device_id, venकरोr_id;
	u32 val = 0, class_code;

	/* Properties are पढ़ो in the same order as listed in PAPR */

	अगर (cxl_verbose) अणु
		pr_info("Dump of the 'ibm,coherent-platform-function' node properties:\n");

		prop = of_get_property(np, "compatible", &len);
		i = 0;
		जबतक (i < len) अणु
			p = (अक्षर *) prop + i;
			pr_info("compatible: %s\n", p);
			i += म_माप(p) + 1;
		पूर्ण
		पढ़ो_prop_string(np, "name");
	पूर्ण

	rc = पढ़ो_phys_addr(np, "reg", afu);
	अगर (rc)
		वापस rc;

	rc = पढ़ो_phys_addr(np, "assigned-addresses", afu);
	अगर (rc)
		वापस rc;

	अगर (afu->psn_phys == 0)
		afu->psa = false;
	अन्यथा
		afu->psa = true;

	अगर (cxl_verbose) अणु
		पढ़ो_prop_string(np, "ibm,loc-code");
		पढ़ो_prop_string(np, "device_type");
	पूर्ण

	पढ़ो_prop_dword(np, "ibm,#processes", &afu->max_procs_भवised);

	अगर (cxl_verbose) अणु
		पढ़ो_prop_dword(np, "ibm,scratchpad-size", &val);
		पढ़ो_prop_dword(np, "ibm,programmable", &val);
		पढ़ो_prop_string(np, "ibm,phandle");
		पढ़ो_vpd(शून्य, afu);
	पूर्ण

	पढ़ो_prop_dword(np, "ibm,max-ints-per-process", &afu->guest->max_पूर्णांकs);
	afu->irqs_max = afu->guest->max_पूर्णांकs;

	prop = पढ़ो_prop_dword(np, "ibm,min-ints-per-process", &afu->pp_irqs);
	अगर (prop) अणु
		/* One extra पूर्णांकerrupt क्रम the PSL पूर्णांकerrupt is alपढ़ोy
		 * included. Remove it now to keep only AFU पूर्णांकerrupts and
		 * match the native हाल.
		 */
		afu->pp_irqs--;
	पूर्ण

	अगर (cxl_verbose) अणु
		पढ़ो_prop_dword(np, "ibm,max-ints", &val);
		पढ़ो_prop_dword(np, "ibm,vpd-size", &val);
	पूर्ण

	पढ़ो_prop64_dword(np, "ibm,error-buffer-size", &afu->eb_len);
	afu->eb_offset = 0;

	अगर (cxl_verbose)
		पढ़ो_prop_dword(np, "ibm,config-record-type", &val);

	पढ़ो_prop64_dword(np, "ibm,config-record-size", &afu->crs_len);
	afu->crs_offset = 0;

	पढ़ो_prop_dword(np, "ibm,#config-records", &afu->crs_num);

	अगर (cxl_verbose) अणु
		क्रम (i = 0; i < afu->crs_num; i++) अणु
			rc = cxl_ops->afu_cr_पढ़ो16(afu, i, PCI_DEVICE_ID,
						&device_id);
			अगर (!rc)
				pr_info("record %d - device-id: %#x\n",
					i, device_id);
			rc = cxl_ops->afu_cr_पढ़ो16(afu, i, PCI_VENDOR_ID,
						&venकरोr_id);
			अगर (!rc)
				pr_info("record %d - vendor-id: %#x\n",
					i, venकरोr_id);
			rc = cxl_ops->afu_cr_पढ़ो32(afu, i, PCI_CLASS_REVISION,
						&class_code);
			अगर (!rc) अणु
				class_code >>= 8;
				pr_info("record %d - class-code: %#x\n",
					i, class_code);
			पूर्ण
		पूर्ण

		पढ़ो_prop_dword(np, "ibm,function-number", &val);
		पढ़ो_prop_dword(np, "ibm,privileged-function", &val);
		पढ़ो_prop_dword(np, "vendor-id", &val);
		पढ़ो_prop_dword(np, "device-id", &val);
		पढ़ो_prop_dword(np, "revision-id", &val);
		पढ़ो_prop_dword(np, "class-code", &val);
		पढ़ो_prop_dword(np, "subsystem-vendor-id", &val);
		पढ़ो_prop_dword(np, "subsystem-id", &val);
	पूर्ण
	/*
	 * अगर "ibm,process-mmio" करोesn't exist then per-process mmio is
	 * not supported
	 */
	val = 0;
	prop = पढ़ो_prop_dword(np, "ibm,process-mmio", &val);
	अगर (prop && val == 1)
		afu->pp_psa = true;
	अन्यथा
		afu->pp_psa = false;

	अगर (cxl_verbose) अणु
		पढ़ो_prop_dword(np, "ibm,supports-aur", &val);
		पढ़ो_prop_dword(np, "ibm,supports-csrp", &val);
		पढ़ो_prop_dword(np, "ibm,supports-prr", &val);
	पूर्ण

	prop = पढ़ो_prop_dword(np, "ibm,function-error-interrupt", &val);
	अगर (prop)
		afu->serr_hwirq = val;

	pr_devel("AFU handle: %#llx\n", afu->guest->handle);
	pr_devel("p2n_phys: %#llx (size %#llx)\n",
		afu->guest->p2n_phys, afu->guest->p2n_size);
	pr_devel("psn_phys: %#llx (size %#llx)\n",
		afu->psn_phys, afu->adapter->ps_size);
	pr_devel("Max number of processes virtualised=%i\n",
		afu->max_procs_भवised);
	pr_devel("Per-process irqs min=%i, max=%i\n", afu->pp_irqs,
		 afu->irqs_max);
	pr_devel("Slice error interrupt=%#lx\n", afu->serr_hwirq);

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_adapter_irq_config(काष्ठा cxl *adapter, काष्ठा device_node *np)
अणु
	स्थिर __be32 *ranges;
	पूर्णांक len, nranges, i;
	काष्ठा irq_avail *cur;

	ranges = of_get_property(np, "interrupt-ranges", &len);
	अगर (ranges == शून्य || len < (2 * माप(पूर्णांक)))
		वापस -EINVAL;

	/*
	 * encoded array of two cells per entry, each cell encoded as
	 * with encode-पूर्णांक
	 */
	nranges = len / (2 * माप(पूर्णांक));
	अगर (nranges == 0 || (nranges * 2 * माप(पूर्णांक)) != len)
		वापस -EINVAL;

	adapter->guest->irq_avail = kसुस्मृति(nranges, माप(काष्ठा irq_avail),
					    GFP_KERNEL);
	अगर (adapter->guest->irq_avail == शून्य)
		वापस -ENOMEM;

	adapter->guest->irq_base_offset = be32_to_cpu(ranges[0]);
	क्रम (i = 0; i < nranges; i++) अणु
		cur = &adapter->guest->irq_avail[i];
		cur->offset = be32_to_cpu(ranges[i * 2]);
		cur->range  = be32_to_cpu(ranges[i * 2 + 1]);
		cur->biपंचांगap = kसुस्मृति(BITS_TO_LONGS(cur->range),
				माप(*cur->biपंचांगap), GFP_KERNEL);
		अगर (cur->biपंचांगap == शून्य)
			जाओ err;
		अगर (cur->offset < adapter->guest->irq_base_offset)
			adapter->guest->irq_base_offset = cur->offset;
		अगर (cxl_verbose)
			pr_info("available IRQ range: %#lx-%#lx (%lu)\n",
				cur->offset, cur->offset + cur->range - 1,
				cur->range);
	पूर्ण
	adapter->guest->irq_nranges = nranges;
	spin_lock_init(&adapter->guest->irq_alloc_lock);

	वापस 0;
err:
	क्रम (i--; i >= 0; i--) अणु
		cur = &adapter->guest->irq_avail[i];
		kमुक्त(cur->biपंचांगap);
	पूर्ण
	kमुक्त(adapter->guest->irq_avail);
	adapter->guest->irq_avail = शून्य;
	वापस -ENOMEM;
पूर्ण

पूर्णांक cxl_of_पढ़ो_adapter_handle(काष्ठा cxl *adapter, काष्ठा device_node *np)
अणु
	अगर (पढ़ो_handle(np, &adapter->guest->handle))
		वापस -EINVAL;
	pr_devel("Adapter handle: 0x%.16llx\n", adapter->guest->handle);

	वापस 0;
पूर्ण

पूर्णांक cxl_of_पढ़ो_adapter_properties(काष्ठा cxl *adapter, काष्ठा device_node *np)
अणु
	पूर्णांक rc, len, naddr, i;
	अक्षर *p;
	स्थिर __be32 *prop;
	u32 val = 0;

	/* Properties are पढ़ो in the same order as listed in PAPR */

	naddr = of_n_addr_cells(np);

	अगर (cxl_verbose) अणु
		pr_info("Dump of the 'ibm,coherent-platform-facility' node properties:\n");

		पढ़ो_prop_dword(np, "#address-cells", &val);
		पढ़ो_prop_dword(np, "#size-cells", &val);

		prop = of_get_property(np, "compatible", &len);
		i = 0;
		जबतक (i < len) अणु
			p = (अक्षर *) prop + i;
			pr_info("compatible: %s\n", p);
			i += म_माप(p) + 1;
		पूर्ण
		पढ़ो_prop_string(np, "name");
		पढ़ो_prop_string(np, "model");

		prop = of_get_property(np, "reg", शून्य);
		अगर (prop) अणु
			pr_info("reg: addr:%#llx size:%#x\n",
				of_पढ़ो_number(prop, naddr),
				be32_to_cpu(prop[naddr]));
		पूर्ण

		पढ़ो_prop_string(np, "ibm,loc-code");
	पूर्ण

	अगर ((rc = पढ़ो_adapter_irq_config(adapter, np)))
		वापस rc;

	अगर (cxl_verbose) अणु
		पढ़ो_prop_string(np, "device_type");
		पढ़ो_prop_string(np, "ibm,phandle");
	पूर्ण

	prop = पढ़ो_prop_dword(np, "ibm,caia-version", &val);
	अगर (prop) अणु
		adapter->caia_major = (val & 0xFF00) >> 8;
		adapter->caia_minor = val & 0xFF;
	पूर्ण

	prop = पढ़ो_prop_dword(np, "ibm,psl-revision", &val);
	अगर (prop)
		adapter->psl_rev = val;

	prop = पढ़ो_prop_string(np, "status");
	अगर (prop) अणु
		adapter->guest->status = kaप्र_लिखो(GFP_KERNEL, "%s", (अक्षर *) prop);
		अगर (adapter->guest->status == शून्य)
			वापस -ENOMEM;
	पूर्ण

	prop = पढ़ो_prop_dword(np, "vendor-id", &val);
	अगर (prop)
		adapter->guest->venकरोr = val;

	prop = पढ़ो_prop_dword(np, "device-id", &val);
	अगर (prop)
		adapter->guest->device = val;

	अगर (cxl_verbose) अणु
		पढ़ो_prop_dword(np, "ibm,privileged-facility", &val);
		पढ़ो_prop_dword(np, "revision-id", &val);
		पढ़ो_prop_dword(np, "class-code", &val);
	पूर्ण

	prop = पढ़ो_prop_dword(np, "subsystem-vendor-id", &val);
	अगर (prop)
		adapter->guest->subप्रणाली_venकरोr = val;

	prop = पढ़ो_prop_dword(np, "subsystem-id", &val);
	अगर (prop)
		adapter->guest->subप्रणाली = val;

	अगर (cxl_verbose)
		पढ़ो_vpd(adapter, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक cxl_of_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cxl *adapter;
	पूर्णांक afu;

	adapter = dev_get_drvdata(&pdev->dev);
	क्रम (afu = 0; afu < adapter->slices; afu++)
		cxl_guest_हटाओ_afu(adapter->afu[afu]);

	cxl_guest_हटाओ_adapter(adapter);
	वापस 0;
पूर्ण

अटल व्योम cxl_of_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	cxl_of_हटाओ(pdev);
पूर्ण

पूर्णांक cxl_of_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = शून्य;
	काष्ठा device_node *afu_np = शून्य;
	काष्ठा cxl *adapter = शून्य;
	पूर्णांक ret;
	पूर्णांक slice = 0, slice_ok = 0;

	pr_devel("in %s\n", __func__);

	np = pdev->dev.of_node;
	अगर (np == शून्य)
		वापस -ENODEV;

	/* init adapter */
	adapter = cxl_guest_init_adapter(np, pdev);
	अगर (IS_ERR(adapter)) अणु
		dev_err(&pdev->dev, "guest_init_adapter failed: %li\n", PTR_ERR(adapter));
		वापस PTR_ERR(adapter);
	पूर्ण

	/* init afu */
	क्रम_each_child_of_node(np, afu_np) अणु
		अगर ((ret = cxl_guest_init_afu(adapter, slice, afu_np)))
			dev_err(&pdev->dev, "AFU %i failed to initialise: %i\n",
				slice, ret);
		अन्यथा
			slice_ok++;
		slice++;
	पूर्ण

	अगर (slice_ok == 0) अणु
		dev_info(&pdev->dev, "No active AFU");
		adapter->slices = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cxl_of_match[] = अणु
	अणु .compatible = "ibm,coherent-platform-facility",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cxl_of_match);

काष्ठा platक्रमm_driver cxl_of_driver = अणु
	.driver = अणु
		.name = "cxl_of",
		.of_match_table = cxl_of_match,
		.owner = THIS_MODULE
	पूर्ण,
	.probe = cxl_of_probe,
	.हटाओ = cxl_of_हटाओ,
	.shutकरोwn = cxl_of_shutकरोwn,
पूर्ण;
