<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2017 IBM Corp.
#समावेश <यंत्र/pnv-ocxl.h>
#समावेश <यंत्र/opal.h>
#समावेश <misc/ocxl-config.h>
#समावेश "pci.h"

#घोषणा PNV_OCXL_TL_P9_RECV_CAP		0x000000000000000Full
#घोषणा PNV_OCXL_ACTAG_MAX		64
/* PASIDs are 20-bit, but on P9, NPU can only handle 15 bits */
#घोषणा PNV_OCXL_PASID_BITS		15
#घोषणा PNV_OCXL_PASID_MAX		((1 << PNV_OCXL_PASID_BITS) - 1)

#घोषणा AFU_PRESENT (1 << 31)
#घोषणा AFU_INDEX_MASK 0x3F000000
#घोषणा AFU_INDEX_SHIFT 24
#घोषणा ACTAG_MASK 0xFFF


काष्ठा actag_range अणु
	u16 start;
	u16 count;
पूर्ण;

काष्ठा npu_link अणु
	काष्ठा list_head list;
	पूर्णांक करोमुख्य;
	पूर्णांक bus;
	पूर्णांक dev;
	u16 fn_desired_actags[8];
	काष्ठा actag_range fn_actags[8];
	bool assignment_करोne;
पूर्ण;
अटल काष्ठा list_head links_list = LIST_HEAD_INIT(links_list);
अटल DEFINE_MUTEX(links_list_lock);


/*
 * खोलोcapi actags handling:
 *
 * When sending commands, the खोलोcapi device references the memory
 * context it's targeting with an 'actag', which is really an alias
 * क्रम a (BDF, pasid) combination. When it receives a command, the NPU
 * must करो a lookup of the actag to identअगरy the memory context. The
 * hardware supports a finite number of actags per link (64 क्रम
 * POWER9).
 *
 * The device can carry multiple functions, and each function can have
 * multiple AFUs. Each AFU advertises in its config space the number
 * of desired actags. The host must configure in the config space of
 * the AFU how many actags the AFU is really allowed to use (which can
 * be less than what the AFU desires).
 *
 * When a PCI function is probed by the driver, it has no visibility
 * about the other PCI functions and how many actags they'd like,
 * which makes it impossible to distribute actags fairly among AFUs.
 *
 * Unक्रमtunately, the only way to know how many actags a function
 * desires is by looking at the data क्रम each AFU in the config space
 * and add them up. Similarly, the only way to know how many actags
 * all the functions of the physical device desire is by adding the
 * previously computed function counts. Then we can match that against
 * what the hardware supports.
 *
 * To get a comprehensive view, we use a 'pci fixup': at the end of
 * PCI क्रमागतeration, each function counts how many actags its AFUs
 * desire and we save it in a 'npu_link' काष्ठाure, shared between all
 * the PCI functions of a same device. Thereक्रमe, when the first
 * function is probed by the driver, we can get an idea of the total
 * count of desired actags क्रम the device, and assign the actags to
 * the AFUs, by pro-rating अगर needed.
 */

अटल पूर्णांक find_dvsec_from_pos(काष्ठा pci_dev *dev, पूर्णांक dvsec_id, पूर्णांक pos)
अणु
	पूर्णांक vsec = pos;
	u16 venकरोr, id;

	जबतक ((vsec = pci_find_next_ext_capability(dev, vsec,
						    OCXL_EXT_CAP_ID_DVSEC))) अणु
		pci_पढ़ो_config_word(dev, vsec + OCXL_DVSEC_VENDOR_OFFSET,
				&venकरोr);
		pci_पढ़ो_config_word(dev, vsec + OCXL_DVSEC_ID_OFFSET, &id);
		अगर (venकरोr == PCI_VENDOR_ID_IBM && id == dvsec_id)
			वापस vsec;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक find_dvsec_afu_ctrl(काष्ठा pci_dev *dev, u8 afu_idx)
अणु
	पूर्णांक vsec = 0;
	u8 idx;

	जबतक ((vsec = find_dvsec_from_pos(dev, OCXL_DVSEC_AFU_CTRL_ID,
					   vsec))) अणु
		pci_पढ़ो_config_byte(dev, vsec + OCXL_DVSEC_AFU_CTRL_AFU_IDX,
				&idx);
		अगर (idx == afu_idx)
			वापस vsec;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक get_max_afu_index(काष्ठा pci_dev *dev, पूर्णांक *afu_idx)
अणु
	पूर्णांक pos;
	u32 val;

	pos = find_dvsec_from_pos(dev, OCXL_DVSEC_FUNC_ID, 0);
	अगर (!pos)
		वापस -ESRCH;

	pci_पढ़ो_config_dword(dev, pos + OCXL_DVSEC_FUNC_OFF_INDEX, &val);
	अगर (val & AFU_PRESENT)
		*afu_idx = (val & AFU_INDEX_MASK) >> AFU_INDEX_SHIFT;
	अन्यथा
		*afu_idx = -1;
	वापस 0;
पूर्ण

अटल पूर्णांक get_actag_count(काष्ठा pci_dev *dev, पूर्णांक afu_idx, पूर्णांक *actag)
अणु
	पूर्णांक pos;
	u16 actag_sup;

	pos = find_dvsec_afu_ctrl(dev, afu_idx);
	अगर (!pos)
		वापस -ESRCH;

	pci_पढ़ो_config_word(dev, pos + OCXL_DVSEC_AFU_CTRL_ACTAG_SUP,
			&actag_sup);
	*actag = actag_sup & ACTAG_MASK;
	वापस 0;
पूर्ण

अटल काष्ठा npu_link *find_link(काष्ठा pci_dev *dev)
अणु
	काष्ठा npu_link *link;

	list_क्रम_each_entry(link, &links_list, list) अणु
		/* The functions of a device all share the same link */
		अगर (link->करोमुख्य == pci_करोमुख्य_nr(dev->bus) &&
			link->bus == dev->bus->number &&
			link->dev == PCI_SLOT(dev->devfn)) अणु
			वापस link;
		पूर्ण
	पूर्ण

	/* link करोesn't exist yet. Allocate one */
	link = kzalloc(माप(काष्ठा npu_link), GFP_KERNEL);
	अगर (!link)
		वापस शून्य;
	link->करोमुख्य = pci_करोमुख्य_nr(dev->bus);
	link->bus = dev->bus->number;
	link->dev = PCI_SLOT(dev->devfn);
	list_add(&link->list, &links_list);
	वापस link;
पूर्ण

अटल व्योम pnv_ocxl_fixup_actag(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);
	काष्ठा pnv_phb *phb = hose->निजी_data;
	काष्ठा npu_link *link;
	पूर्णांक rc, afu_idx = -1, i, actag;

	अगर (!machine_is(घातernv))
		वापस;

	अगर (phb->type != PNV_PHB_NPU_OCAPI)
		वापस;

	mutex_lock(&links_list_lock);

	link = find_link(dev);
	अगर (!link) अणु
		dev_warn(&dev->dev, "couldn't update actag information\n");
		mutex_unlock(&links_list_lock);
		वापस;
	पूर्ण

	/*
	 * Check how many actags are desired क्रम the AFUs under that
	 * function and add it to the count क्रम the link
	 */
	rc = get_max_afu_index(dev, &afu_idx);
	अगर (rc) अणु
		/* Most likely an invalid config space */
		dev_dbg(&dev->dev, "couldn't find AFU information\n");
		afu_idx = -1;
	पूर्ण

	link->fn_desired_actags[PCI_FUNC(dev->devfn)] = 0;
	क्रम (i = 0; i <= afu_idx; i++) अणु
		/*
		 * AFU index 'holes' are allowed. So don't fail अगर we
		 * can't पढ़ो the actag info क्रम an index
		 */
		rc = get_actag_count(dev, i, &actag);
		अगर (rc)
			जारी;
		link->fn_desired_actags[PCI_FUNC(dev->devfn)] += actag;
	पूर्ण
	dev_dbg(&dev->dev, "total actags for function: %d\n",
		link->fn_desired_actags[PCI_FUNC(dev->devfn)]);

	mutex_unlock(&links_list_lock);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_ANY_ID, PCI_ANY_ID, pnv_ocxl_fixup_actag);

अटल u16 assign_fn_actags(u16 desired, u16 total)
अणु
	u16 count;

	अगर (total <= PNV_OCXL_ACTAG_MAX)
		count = desired;
	अन्यथा
		count = PNV_OCXL_ACTAG_MAX * desired / total;

	वापस count;
पूर्ण

अटल व्योम assign_actags(काष्ठा npu_link *link)
अणु
	u16 actag_count, range_start = 0, total_desired = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		total_desired += link->fn_desired_actags[i];

	क्रम (i = 0; i < 8; i++) अणु
		अगर (link->fn_desired_actags[i]) अणु
			actag_count = assign_fn_actags(
				link->fn_desired_actags[i],
				total_desired);
			link->fn_actags[i].start = range_start;
			link->fn_actags[i].count = actag_count;
			range_start += actag_count;
			WARN_ON(range_start >= PNV_OCXL_ACTAG_MAX);
		पूर्ण
		pr_debug("link %x:%x:%x fct %d actags: start=%d count=%d (desired=%d)\n",
			link->करोमुख्य, link->bus, link->dev, i,
			link->fn_actags[i].start, link->fn_actags[i].count,
			link->fn_desired_actags[i]);
	पूर्ण
	link->assignment_करोne = true;
पूर्ण

पूर्णांक pnv_ocxl_get_actag(काष्ठा pci_dev *dev, u16 *base, u16 *enabled,
		u16 *supported)
अणु
	काष्ठा npu_link *link;

	mutex_lock(&links_list_lock);

	link = find_link(dev);
	अगर (!link) अणु
		dev_err(&dev->dev, "actag information not found\n");
		mutex_unlock(&links_list_lock);
		वापस -ENODEV;
	पूर्ण
	/*
	 * On p9, we only have 64 actags per link, so they must be
	 * shared by all the functions of the same adapter. We counted
	 * the desired actag counts during PCI क्रमागतeration, so that we
	 * can allocate a pro-rated number of actags to each function.
	 */
	अगर (!link->assignment_करोne)
		assign_actags(link);

	*base      = link->fn_actags[PCI_FUNC(dev->devfn)].start;
	*enabled   = link->fn_actags[PCI_FUNC(dev->devfn)].count;
	*supported = link->fn_desired_actags[PCI_FUNC(dev->devfn)];

	mutex_unlock(&links_list_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_ocxl_get_actag);

पूर्णांक pnv_ocxl_get_pasid_count(काष्ठा pci_dev *dev, पूर्णांक *count)
अणु
	काष्ठा npu_link *link;
	पूर्णांक i, rc = -EINVAL;

	/*
	 * The number of PASIDs (process address space ID) which can
	 * be used by a function depends on how many functions exist
	 * on the device. The NPU needs to be configured to know how
	 * many bits are available to PASIDs and how many are to be
	 * used by the function BDF indentअगरier.
	 *
	 * We only support one AFU-carrying function क्रम now.
	 */
	mutex_lock(&links_list_lock);

	link = find_link(dev);
	अगर (!link) अणु
		dev_err(&dev->dev, "actag information not found\n");
		mutex_unlock(&links_list_lock);
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < 8; i++)
		अगर (link->fn_desired_actags[i] && (i == PCI_FUNC(dev->devfn))) अणु
			*count = PNV_OCXL_PASID_MAX;
			rc = 0;
			अवरोध;
		पूर्ण

	mutex_unlock(&links_list_lock);
	dev_dbg(&dev->dev, "%d PASIDs available for function\n",
		rc ? 0 : *count);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_ocxl_get_pasid_count);

अटल व्योम set_templ_rate(अचिन्हित पूर्णांक templ, अचिन्हित पूर्णांक rate, अक्षर *buf)
अणु
	पूर्णांक shअगरt, idx;

	WARN_ON(templ > PNV_OCXL_TL_MAX_TEMPLATE);
	idx = (PNV_OCXL_TL_MAX_TEMPLATE - templ) / 2;
	shअगरt = 4 * (1 - ((PNV_OCXL_TL_MAX_TEMPLATE - templ) % 2));
	buf[idx] |= rate << shअगरt;
पूर्ण

पूर्णांक pnv_ocxl_get_tl_cap(काष्ठा pci_dev *dev, दीर्घ *cap,
			अक्षर *rate_buf, पूर्णांक rate_buf_size)
अणु
	अगर (rate_buf_size != PNV_OCXL_TL_RATE_BUF_SIZE)
		वापस -EINVAL;
	/*
	 * The TL capabilities are a अक्षरacteristic of the NPU, so
	 * we go with hard-coded values.
	 *
	 * The receiving rate of each ढाँचा is encoded on 4 bits.
	 *
	 * On P9:
	 * - ढाँचाs 0 -> 3 are supported
	 * - ढाँचाs 0, 1 and 3 have a 0 receiving rate
	 * - ढाँचा 2 has receiving rate of 1 (extra cycle)
	 */
	स_रखो(rate_buf, 0, rate_buf_size);
	set_templ_rate(2, 1, rate_buf);
	*cap = PNV_OCXL_TL_P9_RECV_CAP;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_ocxl_get_tl_cap);

पूर्णांक pnv_ocxl_set_tl_conf(काष्ठा pci_dev *dev, दीर्घ cap,
			uपूर्णांक64_t rate_buf_phys, पूर्णांक rate_buf_size)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);
	काष्ठा pnv_phb *phb = hose->निजी_data;
	पूर्णांक rc;

	अगर (rate_buf_size != PNV_OCXL_TL_RATE_BUF_SIZE)
		वापस -EINVAL;

	rc = opal_npu_tl_set(phb->opal_id, dev->devfn, cap,
			rate_buf_phys, rate_buf_size);
	अगर (rc) अणु
		dev_err(&dev->dev, "Can't configure host TL: %d\n", rc);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_ocxl_set_tl_conf);

पूर्णांक pnv_ocxl_get_xsl_irq(काष्ठा pci_dev *dev, पूर्णांक *hwirq)
अणु
	पूर्णांक rc;

	rc = of_property_पढ़ो_u32(dev->dev.of_node, "ibm,opal-xsl-irq", hwirq);
	अगर (rc) अणु
		dev_err(&dev->dev,
			"Can't get translation interrupt for device\n");
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_ocxl_get_xsl_irq);

व्योम pnv_ocxl_unmap_xsl_regs(व्योम __iomem *dsisr, व्योम __iomem *dar,
			व्योम __iomem *tfc, व्योम __iomem *pe_handle)
अणु
	iounmap(dsisr);
	iounmap(dar);
	iounmap(tfc);
	iounmap(pe_handle);
पूर्ण
EXPORT_SYMBOL_GPL(pnv_ocxl_unmap_xsl_regs);

पूर्णांक pnv_ocxl_map_xsl_regs(काष्ठा pci_dev *dev, व्योम __iomem **dsisr,
			व्योम __iomem **dar, व्योम __iomem **tfc,
			व्योम __iomem **pe_handle)
अणु
	u64 reg;
	पूर्णांक i, j, rc = 0;
	व्योम __iomem *regs[4];

	/*
	 * opal stores the mmio addresses of the DSISR, DAR, TFC and
	 * PE_HANDLE रेजिस्टरs in a device tree property, in that
	 * order
	 */
	क्रम (i = 0; i < 4; i++) अणु
		rc = of_property_पढ़ो_u64_index(dev->dev.of_node,
						"ibm,opal-xsl-mmio", i, &reg);
		अगर (rc)
			अवरोध;
		regs[i] = ioremap(reg, 8);
		अगर (!regs[i]) अणु
			rc = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (rc) अणु
		dev_err(&dev->dev, "Can't map translation mmio registers\n");
		क्रम (j = i - 1; j >= 0; j--)
			iounmap(regs[j]);
	पूर्ण अन्यथा अणु
		*dsisr = regs[0];
		*dar = regs[1];
		*tfc = regs[2];
		*pe_handle = regs[3];
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_ocxl_map_xsl_regs);

काष्ठा spa_data अणु
	u64 phb_opal_id;
	u32 bdfn;
पूर्ण;

पूर्णांक pnv_ocxl_spa_setup(काष्ठा pci_dev *dev, व्योम *spa_mem, पूर्णांक PE_mask,
		व्योम **platक्रमm_data)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);
	काष्ठा pnv_phb *phb = hose->निजी_data;
	काष्ठा spa_data *data;
	u32 bdfn;
	पूर्णांक rc;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	bdfn = (dev->bus->number << 8) | dev->devfn;
	rc = opal_npu_spa_setup(phb->opal_id, bdfn, virt_to_phys(spa_mem),
				PE_mask);
	अगर (rc) अणु
		dev_err(&dev->dev, "Can't setup Shared Process Area: %d\n", rc);
		kमुक्त(data);
		वापस rc;
	पूर्ण
	data->phb_opal_id = phb->opal_id;
	data->bdfn = bdfn;
	*platक्रमm_data = (व्योम *) data;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_ocxl_spa_setup);

व्योम pnv_ocxl_spa_release(व्योम *platक्रमm_data)
अणु
	काष्ठा spa_data *data = (काष्ठा spa_data *) platक्रमm_data;
	पूर्णांक rc;

	rc = opal_npu_spa_setup(data->phb_opal_id, data->bdfn, 0, 0);
	WARN_ON(rc);
	kमुक्त(data);
पूर्ण
EXPORT_SYMBOL_GPL(pnv_ocxl_spa_release);

पूर्णांक pnv_ocxl_spa_हटाओ_pe_from_cache(व्योम *platक्रमm_data, पूर्णांक pe_handle)
अणु
	काष्ठा spa_data *data = (काष्ठा spa_data *) platक्रमm_data;
	पूर्णांक rc;

	rc = opal_npu_spa_clear_cache(data->phb_opal_id, data->bdfn, pe_handle);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_ocxl_spa_हटाओ_pe_from_cache);

पूर्णांक pnv_ocxl_map_lpar(काष्ठा pci_dev *dev, uपूर्णांक64_t lparid,
		      uपूर्णांक64_t lpcr, व्योम __iomem **arva)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);
	काष्ठा pnv_phb *phb = hose->निजी_data;
	u64 mmio_atsd;
	पूर्णांक rc;

	/* ATSD physical address.
	 * ATSD LAUNCH रेजिस्टर: ग_लिखो access initiates a shoot करोwn to
	 * initiate the TLB Invalidate command.
	 */
	rc = of_property_पढ़ो_u64_index(hose->dn, "ibm,mmio-atsd",
					0, &mmio_atsd);
	अगर (rc) अणु
		dev_info(&dev->dev, "No available ATSD found\n");
		वापस rc;
	पूर्ण

	/* Assign a रेजिस्टर set to a Logical Partition and MMIO ATSD
	 * LPARID रेजिस्टर to the required value.
	 */
	rc = opal_npu_map_lpar(phb->opal_id, pci_dev_id(dev),
			       lparid, lpcr);
	अगर (rc) अणु
		dev_err(&dev->dev, "Error mapping device to LPAR: %d\n", rc);
		वापस rc;
	पूर्ण

	*arva = ioremap(mmio_atsd, 24);
	अगर (!(*arva)) अणु
		dev_warn(&dev->dev, "ioremap failed - mmio_atsd: %#llx\n", mmio_atsd);
		rc = -ENOMEM;
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_ocxl_map_lpar);

व्योम pnv_ocxl_unmap_lpar(व्योम __iomem *arva)
अणु
	iounmap(arva);
पूर्ण
EXPORT_SYMBOL_GPL(pnv_ocxl_unmap_lpar);

व्योम pnv_ocxl_tlb_invalidate(व्योम __iomem *arva,
			     अचिन्हित दीर्घ pid,
			     अचिन्हित दीर्घ addr,
			     अचिन्हित दीर्घ page_size)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + (HZ * PNV_OCXL_ATSD_TIMEOUT);
	u64 val = 0ull;
	पूर्णांक pend;
	u8 size;

	अगर (!(arva))
		वापस;

	अगर (addr) अणु
		/* load Abbreviated Virtual Address रेजिस्टर with
		 * the necessary value
		 */
		val |= FIELD_PREP(PNV_OCXL_ATSD_AVA_AVA, addr >> (63-51));
		out_be64(arva + PNV_OCXL_ATSD_AVA, val);
	पूर्ण

	/* Write access initiates a shoot करोwn to initiate the
	 * TLB Invalidate command
	 */
	val = PNV_OCXL_ATSD_LNCH_R;
	val |= FIELD_PREP(PNV_OCXL_ATSD_LNCH_RIC, 0b10);
	अगर (addr)
		val |= FIELD_PREP(PNV_OCXL_ATSD_LNCH_IS, 0b00);
	अन्यथा अणु
		val |= FIELD_PREP(PNV_OCXL_ATSD_LNCH_IS, 0b01);
		val |= PNV_OCXL_ATSD_LNCH_OCAPI_SINGLETON;
	पूर्ण
	val |= PNV_OCXL_ATSD_LNCH_PRS;
	/* Actual Page Size to be invalidated
	 * 000 4KB
	 * 101 64KB
	 * 001 2MB
	 * 010 1GB
	 */
	size = 0b101;
	अगर (page_size == 0x1000)
		size = 0b000;
	अगर (page_size == 0x200000)
		size = 0b001;
	अगर (page_size == 0x40000000)
		size = 0b010;
	val |= FIELD_PREP(PNV_OCXL_ATSD_LNCH_AP, size);
	val |= FIELD_PREP(PNV_OCXL_ATSD_LNCH_PID, pid);
	out_be64(arva + PNV_OCXL_ATSD_LNCH, val);

	/* Poll the ATSD status रेजिस्टर to determine when the
	 * TLB Invalidate has been completed.
	 */
	val = in_be64(arva + PNV_OCXL_ATSD_STAT);
	pend = val >> 63;

	जबतक (pend) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			pr_err("%s - Timeout while reading XTS MMIO ATSD status register (val=%#llx, pidr=0x%lx)\n",
			       __func__, val, pid);
			वापस;
		पूर्ण
		cpu_relax();
		val = in_be64(arva + PNV_OCXL_ATSD_STAT);
		pend = val >> 63;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pnv_ocxl_tlb_invalidate);
