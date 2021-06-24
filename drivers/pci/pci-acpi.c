<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI support in ACPI
 *
 * Copyright (C) 2005 David Shaohua Li <shaohua.li@पूर्णांकel.com>
 * Copyright (C) 2004 Tom Long Nguyen <tom.l.nguyen@पूर्णांकel.com>
 * Copyright (C) 2004 Intel Corp.
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/pci.h>
#समावेश <linux/msi.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/module.h>
#समावेश <linux/pci-acpi.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_qos.h>
#समावेश "pci.h"

/*
 * The GUID is defined in the PCI Firmware Specअगरication available here:
 * https://www.pcisig.com/members/करोwnloads/pcअगरw_r3_1_13Dec10.pdf
 */
स्थिर guid_t pci_acpi_dsm_guid =
	GUID_INIT(0xe5c937d0, 0x3553, 0x4d7a,
		  0x91, 0x17, 0xea, 0x4d, 0x19, 0xc3, 0x43, 0x4d);

#अगर defined(CONFIG_PCI_QUIRKS) && defined(CONFIG_ARM64)
अटल पूर्णांक acpi_get_rc_addr(काष्ठा acpi_device *adev, काष्ठा resource *res)
अणु
	काष्ठा device *dev = &adev->dev;
	काष्ठा resource_entry *entry;
	काष्ठा list_head list;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	INIT_LIST_HEAD(&list);
	flags = IORESOURCE_MEM;
	ret = acpi_dev_get_resources(adev, &list,
				     acpi_dev_filter_resource_type_cb,
				     (व्योम *) flags);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to parse _CRS method, error code %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (ret == 0) अणु
		dev_err(dev, "no IO and memory resources present in _CRS\n");
		वापस -EINVAL;
	पूर्ण

	entry = list_first_entry(&list, काष्ठा resource_entry, node);
	*res = *entry->res;
	acpi_dev_मुक्त_resource_list(&list);
	वापस 0;
पूर्ण

अटल acpi_status acpi_match_rc(acpi_handle handle, u32 lvl, व्योम *context,
				 व्योम **retval)
अणु
	u16 *segment = context;
	अचिन्हित दीर्घ दीर्घ uid;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(handle, "_UID", शून्य, &uid);
	अगर (ACPI_FAILURE(status) || uid != *segment)
		वापस AE_CTRL_DEPTH;

	*(acpi_handle *)retval = handle;
	वापस AE_CTRL_TERMINATE;
पूर्ण

पूर्णांक acpi_get_rc_resources(काष्ठा device *dev, स्थिर अक्षर *hid, u16 segment,
			  काष्ठा resource *res)
अणु
	काष्ठा acpi_device *adev;
	acpi_status status;
	acpi_handle handle;
	पूर्णांक ret;

	status = acpi_get_devices(hid, acpi_match_rc, &segment, &handle);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "can't find _HID %s device to locate resources\n",
			hid);
		वापस -ENODEV;
	पूर्ण

	ret = acpi_bus_get_device(handle, &adev);
	अगर (ret)
		वापस ret;

	ret = acpi_get_rc_addr(adev, res);
	अगर (ret) अणु
		dev_err(dev, "can't get resource from %s\n",
			dev_name(&adev->dev));
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

phys_addr_t acpi_pci_root_get_mcfg_addr(acpi_handle handle)
अणु
	acpi_status status = AE_NOT_EXIST;
	अचिन्हित दीर्घ दीर्घ mcfg_addr;

	अगर (handle)
		status = acpi_evaluate_पूर्णांकeger(handle, METHOD_NAME__CBA,
					       शून्य, &mcfg_addr);
	अगर (ACPI_FAILURE(status))
		वापस 0;

	वापस (phys_addr_t)mcfg_addr;
पूर्ण

/* _HPX PCI Setting Record (Type 0); same as _HPP */
काष्ठा hpx_type0 अणु
	u32 revision;		/* Not present in _HPP */
	u8  cache_line_size;	/* Not applicable to PCIe */
	u8  latency_समयr;	/* Not applicable to PCIe */
	u8  enable_serr;
	u8  enable_perr;
पूर्ण;

अटल काष्ठा hpx_type0 pci_शेष_type0 = अणु
	.revision = 1,
	.cache_line_size = 8,
	.latency_समयr = 0x40,
	.enable_serr = 0,
	.enable_perr = 0,
पूर्ण;

अटल व्योम program_hpx_type0(काष्ठा pci_dev *dev, काष्ठा hpx_type0 *hpx)
अणु
	u16 pci_cmd, pci_bctl;

	अगर (!hpx)
		hpx = &pci_शेष_type0;

	अगर (hpx->revision > 1) अणु
		pci_warn(dev, "PCI settings rev %d not supported; using defaults\n",
			 hpx->revision);
		hpx = &pci_शेष_type0;
	पूर्ण

	pci_ग_लिखो_config_byte(dev, PCI_CACHE_LINE_SIZE, hpx->cache_line_size);
	pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, hpx->latency_समयr);
	pci_पढ़ो_config_word(dev, PCI_COMMAND, &pci_cmd);
	अगर (hpx->enable_serr)
		pci_cmd |= PCI_COMMAND_SERR;
	अगर (hpx->enable_perr)
		pci_cmd |= PCI_COMMAND_PARITY;
	pci_ग_लिखो_config_word(dev, PCI_COMMAND, pci_cmd);

	/* Program bridge control value */
	अगर ((dev->class >> 8) == PCI_CLASS_BRIDGE_PCI) अणु
		pci_ग_लिखो_config_byte(dev, PCI_SEC_LATENCY_TIMER,
				      hpx->latency_समयr);
		pci_पढ़ो_config_word(dev, PCI_BRIDGE_CONTROL, &pci_bctl);
		अगर (hpx->enable_perr)
			pci_bctl |= PCI_BRIDGE_CTL_PARITY;
		pci_ग_लिखो_config_word(dev, PCI_BRIDGE_CONTROL, pci_bctl);
	पूर्ण
पूर्ण

अटल acpi_status decode_type0_hpx_record(जोड़ acpi_object *record,
					   काष्ठा hpx_type0 *hpx0)
अणु
	पूर्णांक i;
	जोड़ acpi_object *fields = record->package.elements;
	u32 revision = fields[1].पूर्णांकeger.value;

	चयन (revision) अणु
	हाल 1:
		अगर (record->package.count != 6)
			वापस AE_ERROR;
		क्रम (i = 2; i < 6; i++)
			अगर (fields[i].type != ACPI_TYPE_INTEGER)
				वापस AE_ERROR;
		hpx0->revision        = revision;
		hpx0->cache_line_size = fields[2].पूर्णांकeger.value;
		hpx0->latency_समयr   = fields[3].पूर्णांकeger.value;
		hpx0->enable_serr     = fields[4].पूर्णांकeger.value;
		hpx0->enable_perr     = fields[5].पूर्णांकeger.value;
		अवरोध;
	शेष:
		pr_warn("%s: Type 0 Revision %d record not supported\n",
		       __func__, revision);
		वापस AE_ERROR;
	पूर्ण
	वापस AE_OK;
पूर्ण

/* _HPX PCI-X Setting Record (Type 1) */
काष्ठा hpx_type1 अणु
	u32 revision;
	u8  max_mem_पढ़ो;
	u8  avg_max_split;
	u16 tot_max_split;
पूर्ण;

अटल व्योम program_hpx_type1(काष्ठा pci_dev *dev, काष्ठा hpx_type1 *hpx)
अणु
	पूर्णांक pos;

	अगर (!hpx)
		वापस;

	pos = pci_find_capability(dev, PCI_CAP_ID_PCIX);
	अगर (!pos)
		वापस;

	pci_warn(dev, "PCI-X settings not supported\n");
पूर्ण

अटल acpi_status decode_type1_hpx_record(जोड़ acpi_object *record,
					   काष्ठा hpx_type1 *hpx1)
अणु
	पूर्णांक i;
	जोड़ acpi_object *fields = record->package.elements;
	u32 revision = fields[1].पूर्णांकeger.value;

	चयन (revision) अणु
	हाल 1:
		अगर (record->package.count != 5)
			वापस AE_ERROR;
		क्रम (i = 2; i < 5; i++)
			अगर (fields[i].type != ACPI_TYPE_INTEGER)
				वापस AE_ERROR;
		hpx1->revision      = revision;
		hpx1->max_mem_पढ़ो  = fields[2].पूर्णांकeger.value;
		hpx1->avg_max_split = fields[3].पूर्णांकeger.value;
		hpx1->tot_max_split = fields[4].पूर्णांकeger.value;
		अवरोध;
	शेष:
		pr_warn("%s: Type 1 Revision %d record not supported\n",
		       __func__, revision);
		वापस AE_ERROR;
	पूर्ण
	वापस AE_OK;
पूर्ण

अटल bool pcie_root_rcb_set(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *rp = pcie_find_root_port(dev);
	u16 lnkctl;

	अगर (!rp)
		वापस false;

	pcie_capability_पढ़ो_word(rp, PCI_EXP_LNKCTL, &lnkctl);
	अगर (lnkctl & PCI_EXP_LNKCTL_RCB)
		वापस true;

	वापस false;
पूर्ण

/* _HPX PCI Express Setting Record (Type 2) */
काष्ठा hpx_type2 अणु
	u32 revision;
	u32 unc_err_mask_and;
	u32 unc_err_mask_or;
	u32 unc_err_sever_and;
	u32 unc_err_sever_or;
	u32 cor_err_mask_and;
	u32 cor_err_mask_or;
	u32 adv_err_cap_and;
	u32 adv_err_cap_or;
	u16 pci_exp_devctl_and;
	u16 pci_exp_devctl_or;
	u16 pci_exp_lnkctl_and;
	u16 pci_exp_lnkctl_or;
	u32 sec_unc_err_sever_and;
	u32 sec_unc_err_sever_or;
	u32 sec_unc_err_mask_and;
	u32 sec_unc_err_mask_or;
पूर्ण;

अटल व्योम program_hpx_type2(काष्ठा pci_dev *dev, काष्ठा hpx_type2 *hpx)
अणु
	पूर्णांक pos;
	u32 reg32;

	अगर (!hpx)
		वापस;

	अगर (!pci_is_pcie(dev))
		वापस;

	अगर (hpx->revision > 1) अणु
		pci_warn(dev, "PCIe settings rev %d not supported\n",
			 hpx->revision);
		वापस;
	पूर्ण

	/*
	 * Don't allow _HPX to change MPS or MRRS settings.  We manage
	 * those to make sure they're consistent with the rest of the
	 * platक्रमm.
	 */
	hpx->pci_exp_devctl_and |= PCI_EXP_DEVCTL_PAYLOAD |
				    PCI_EXP_DEVCTL_READRQ;
	hpx->pci_exp_devctl_or &= ~(PCI_EXP_DEVCTL_PAYLOAD |
				    PCI_EXP_DEVCTL_READRQ);

	/* Initialize Device Control Register */
	pcie_capability_clear_and_set_word(dev, PCI_EXP_DEVCTL,
			~hpx->pci_exp_devctl_and, hpx->pci_exp_devctl_or);

	/* Initialize Link Control Register */
	अगर (pcie_cap_has_lnkctl(dev)) अणु

		/*
		 * If the Root Port supports Read Completion Boundary of
		 * 128, set RCB to 128.  Otherwise, clear it.
		 */
		hpx->pci_exp_lnkctl_and |= PCI_EXP_LNKCTL_RCB;
		hpx->pci_exp_lnkctl_or &= ~PCI_EXP_LNKCTL_RCB;
		अगर (pcie_root_rcb_set(dev))
			hpx->pci_exp_lnkctl_or |= PCI_EXP_LNKCTL_RCB;

		pcie_capability_clear_and_set_word(dev, PCI_EXP_LNKCTL,
			~hpx->pci_exp_lnkctl_and, hpx->pci_exp_lnkctl_or);
	पूर्ण

	/* Find Advanced Error Reporting Enhanced Capability */
	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ERR);
	अगर (!pos)
		वापस;

	/* Initialize Uncorrectable Error Mask Register */
	pci_पढ़ो_config_dword(dev, pos + PCI_ERR_UNCOR_MASK, &reg32);
	reg32 = (reg32 & hpx->unc_err_mask_and) | hpx->unc_err_mask_or;
	pci_ग_लिखो_config_dword(dev, pos + PCI_ERR_UNCOR_MASK, reg32);

	/* Initialize Uncorrectable Error Severity Register */
	pci_पढ़ो_config_dword(dev, pos + PCI_ERR_UNCOR_SEVER, &reg32);
	reg32 = (reg32 & hpx->unc_err_sever_and) | hpx->unc_err_sever_or;
	pci_ग_लिखो_config_dword(dev, pos + PCI_ERR_UNCOR_SEVER, reg32);

	/* Initialize Correctable Error Mask Register */
	pci_पढ़ो_config_dword(dev, pos + PCI_ERR_COR_MASK, &reg32);
	reg32 = (reg32 & hpx->cor_err_mask_and) | hpx->cor_err_mask_or;
	pci_ग_लिखो_config_dword(dev, pos + PCI_ERR_COR_MASK, reg32);

	/* Initialize Advanced Error Capabilities and Control Register */
	pci_पढ़ो_config_dword(dev, pos + PCI_ERR_CAP, &reg32);
	reg32 = (reg32 & hpx->adv_err_cap_and) | hpx->adv_err_cap_or;

	/* Don't enable ECRC generation or checking अगर unsupported */
	अगर (!(reg32 & PCI_ERR_CAP_ECRC_GENC))
		reg32 &= ~PCI_ERR_CAP_ECRC_GENE;
	अगर (!(reg32 & PCI_ERR_CAP_ECRC_CHKC))
		reg32 &= ~PCI_ERR_CAP_ECRC_CHKE;
	pci_ग_लिखो_config_dword(dev, pos + PCI_ERR_CAP, reg32);

	/*
	 * FIXME: The following two रेजिस्टरs are not supported yet.
	 *
	 *   o Secondary Uncorrectable Error Severity Register
	 *   o Secondary Uncorrectable Error Mask Register
	 */
पूर्ण

अटल acpi_status decode_type2_hpx_record(जोड़ acpi_object *record,
					   काष्ठा hpx_type2 *hpx2)
अणु
	पूर्णांक i;
	जोड़ acpi_object *fields = record->package.elements;
	u32 revision = fields[1].पूर्णांकeger.value;

	चयन (revision) अणु
	हाल 1:
		अगर (record->package.count != 18)
			वापस AE_ERROR;
		क्रम (i = 2; i < 18; i++)
			अगर (fields[i].type != ACPI_TYPE_INTEGER)
				वापस AE_ERROR;
		hpx2->revision      = revision;
		hpx2->unc_err_mask_and      = fields[2].पूर्णांकeger.value;
		hpx2->unc_err_mask_or       = fields[3].पूर्णांकeger.value;
		hpx2->unc_err_sever_and     = fields[4].पूर्णांकeger.value;
		hpx2->unc_err_sever_or      = fields[5].पूर्णांकeger.value;
		hpx2->cor_err_mask_and      = fields[6].पूर्णांकeger.value;
		hpx2->cor_err_mask_or       = fields[7].पूर्णांकeger.value;
		hpx2->adv_err_cap_and       = fields[8].पूर्णांकeger.value;
		hpx2->adv_err_cap_or        = fields[9].पूर्णांकeger.value;
		hpx2->pci_exp_devctl_and    = fields[10].पूर्णांकeger.value;
		hpx2->pci_exp_devctl_or     = fields[11].पूर्णांकeger.value;
		hpx2->pci_exp_lnkctl_and    = fields[12].पूर्णांकeger.value;
		hpx2->pci_exp_lnkctl_or     = fields[13].पूर्णांकeger.value;
		hpx2->sec_unc_err_sever_and = fields[14].पूर्णांकeger.value;
		hpx2->sec_unc_err_sever_or  = fields[15].पूर्णांकeger.value;
		hpx2->sec_unc_err_mask_and  = fields[16].पूर्णांकeger.value;
		hpx2->sec_unc_err_mask_or   = fields[17].पूर्णांकeger.value;
		अवरोध;
	शेष:
		pr_warn("%s: Type 2 Revision %d record not supported\n",
		       __func__, revision);
		वापस AE_ERROR;
	पूर्ण
	वापस AE_OK;
पूर्ण

/* _HPX PCI Express Setting Record (Type 3) */
काष्ठा hpx_type3 अणु
	u16 device_type;
	u16 function_type;
	u16 config_space_location;
	u16 pci_exp_cap_id;
	u16 pci_exp_cap_ver;
	u16 pci_exp_venकरोr_id;
	u16 dvsec_id;
	u16 dvsec_rev;
	u16 match_offset;
	u32 match_mask_and;
	u32 match_value;
	u16 reg_offset;
	u32 reg_mask_and;
	u32 reg_mask_or;
पूर्ण;

क्रमागत hpx_type3_dev_type अणु
	HPX_TYPE_ENDPOINT	= BIT(0),
	HPX_TYPE_LEG_END	= BIT(1),
	HPX_TYPE_RC_END		= BIT(2),
	HPX_TYPE_RC_EC		= BIT(3),
	HPX_TYPE_ROOT_PORT	= BIT(4),
	HPX_TYPE_UPSTREAM	= BIT(5),
	HPX_TYPE_DOWNSTREAM	= BIT(6),
	HPX_TYPE_PCI_BRIDGE	= BIT(7),
	HPX_TYPE_PCIE_BRIDGE	= BIT(8),
पूर्ण;

अटल u16 hpx3_device_type(काष्ठा pci_dev *dev)
अणु
	u16 pcie_type = pci_pcie_type(dev);
	अटल स्थिर पूर्णांक pcie_to_hpx3_type[] = अणु
		[PCI_EXP_TYPE_ENDPOINT]    = HPX_TYPE_ENDPOINT,
		[PCI_EXP_TYPE_LEG_END]     = HPX_TYPE_LEG_END,
		[PCI_EXP_TYPE_RC_END]      = HPX_TYPE_RC_END,
		[PCI_EXP_TYPE_RC_EC]       = HPX_TYPE_RC_EC,
		[PCI_EXP_TYPE_ROOT_PORT]   = HPX_TYPE_ROOT_PORT,
		[PCI_EXP_TYPE_UPSTREAM]    = HPX_TYPE_UPSTREAM,
		[PCI_EXP_TYPE_DOWNSTREAM]  = HPX_TYPE_DOWNSTREAM,
		[PCI_EXP_TYPE_PCI_BRIDGE]  = HPX_TYPE_PCI_BRIDGE,
		[PCI_EXP_TYPE_PCIE_BRIDGE] = HPX_TYPE_PCIE_BRIDGE,
	पूर्ण;

	अगर (pcie_type >= ARRAY_SIZE(pcie_to_hpx3_type))
		वापस 0;

	वापस pcie_to_hpx3_type[pcie_type];
पूर्ण

क्रमागत hpx_type3_fn_type अणु
	HPX_FN_NORMAL		= BIT(0),
	HPX_FN_SRIOV_PHYS	= BIT(1),
	HPX_FN_SRIOV_VIRT	= BIT(2),
पूर्ण;

अटल u8 hpx3_function_type(काष्ठा pci_dev *dev)
अणु
	अगर (dev->is_virtfn)
		वापस HPX_FN_SRIOV_VIRT;
	अन्यथा अगर (pci_find_ext_capability(dev, PCI_EXT_CAP_ID_SRIOV) > 0)
		वापस HPX_FN_SRIOV_PHYS;
	अन्यथा
		वापस HPX_FN_NORMAL;
पूर्ण

अटल bool hpx3_cap_ver_matches(u8 pcie_cap_id, u8 hpx3_cap_id)
अणु
	u8 cap_ver = hpx3_cap_id & 0xf;

	अगर ((hpx3_cap_id & BIT(4)) && cap_ver >= pcie_cap_id)
		वापस true;
	अन्यथा अगर (cap_ver == pcie_cap_id)
		वापस true;

	वापस false;
पूर्ण

क्रमागत hpx_type3_cfg_loc अणु
	HPX_CFG_PCICFG		= 0,
	HPX_CFG_PCIE_CAP	= 1,
	HPX_CFG_PCIE_CAP_EXT	= 2,
	HPX_CFG_VEND_CAP	= 3,
	HPX_CFG_DVSEC		= 4,
	HPX_CFG_MAX,
पूर्ण;

अटल व्योम program_hpx_type3_रेजिस्टर(काष्ठा pci_dev *dev,
				       स्थिर काष्ठा hpx_type3 *reg)
अणु
	u32 match_reg, ग_लिखो_reg, header, orig_value;
	u16 pos;

	अगर (!(hpx3_device_type(dev) & reg->device_type))
		वापस;

	अगर (!(hpx3_function_type(dev) & reg->function_type))
		वापस;

	चयन (reg->config_space_location) अणु
	हाल HPX_CFG_PCICFG:
		pos = 0;
		अवरोध;
	हाल HPX_CFG_PCIE_CAP:
		pos = pci_find_capability(dev, reg->pci_exp_cap_id);
		अगर (pos == 0)
			वापस;

		अवरोध;
	हाल HPX_CFG_PCIE_CAP_EXT:
		pos = pci_find_ext_capability(dev, reg->pci_exp_cap_id);
		अगर (pos == 0)
			वापस;

		pci_पढ़ो_config_dword(dev, pos, &header);
		अगर (!hpx3_cap_ver_matches(PCI_EXT_CAP_VER(header),
					  reg->pci_exp_cap_ver))
			वापस;

		अवरोध;
	हाल HPX_CFG_VEND_CAP:
	हाल HPX_CFG_DVSEC:
	शेष:
		pci_warn(dev, "Encountered _HPX type 3 with unsupported config space location");
		वापस;
	पूर्ण

	pci_पढ़ो_config_dword(dev, pos + reg->match_offset, &match_reg);

	अगर ((match_reg & reg->match_mask_and) != reg->match_value)
		वापस;

	pci_पढ़ो_config_dword(dev, pos + reg->reg_offset, &ग_लिखो_reg);
	orig_value = ग_लिखो_reg;
	ग_लिखो_reg &= reg->reg_mask_and;
	ग_लिखो_reg |= reg->reg_mask_or;

	अगर (orig_value == ग_लिखो_reg)
		वापस;

	pci_ग_लिखो_config_dword(dev, pos + reg->reg_offset, ग_लिखो_reg);

	pci_dbg(dev, "Applied _HPX3 at [0x%x]: 0x%08x -> 0x%08x",
		pos, orig_value, ग_लिखो_reg);
पूर्ण

अटल व्योम program_hpx_type3(काष्ठा pci_dev *dev, काष्ठा hpx_type3 *hpx)
अणु
	अगर (!hpx)
		वापस;

	अगर (!pci_is_pcie(dev))
		वापस;

	program_hpx_type3_रेजिस्टर(dev, hpx);
पूर्ण

अटल व्योम parse_hpx3_रेजिस्टर(काष्ठा hpx_type3 *hpx3_reg,
				जोड़ acpi_object *reg_fields)
अणु
	hpx3_reg->device_type            = reg_fields[0].पूर्णांकeger.value;
	hpx3_reg->function_type          = reg_fields[1].पूर्णांकeger.value;
	hpx3_reg->config_space_location  = reg_fields[2].पूर्णांकeger.value;
	hpx3_reg->pci_exp_cap_id         = reg_fields[3].पूर्णांकeger.value;
	hpx3_reg->pci_exp_cap_ver        = reg_fields[4].पूर्णांकeger.value;
	hpx3_reg->pci_exp_venकरोr_id      = reg_fields[5].पूर्णांकeger.value;
	hpx3_reg->dvsec_id               = reg_fields[6].पूर्णांकeger.value;
	hpx3_reg->dvsec_rev              = reg_fields[7].पूर्णांकeger.value;
	hpx3_reg->match_offset           = reg_fields[8].पूर्णांकeger.value;
	hpx3_reg->match_mask_and         = reg_fields[9].पूर्णांकeger.value;
	hpx3_reg->match_value            = reg_fields[10].पूर्णांकeger.value;
	hpx3_reg->reg_offset             = reg_fields[11].पूर्णांकeger.value;
	hpx3_reg->reg_mask_and           = reg_fields[12].पूर्णांकeger.value;
	hpx3_reg->reg_mask_or            = reg_fields[13].पूर्णांकeger.value;
पूर्ण

अटल acpi_status program_type3_hpx_record(काष्ठा pci_dev *dev,
					   जोड़ acpi_object *record)
अणु
	जोड़ acpi_object *fields = record->package.elements;
	u32 desc_count, expected_length, revision;
	जोड़ acpi_object *reg_fields;
	काष्ठा hpx_type3 hpx3;
	पूर्णांक i;

	revision = fields[1].पूर्णांकeger.value;
	चयन (revision) अणु
	हाल 1:
		desc_count = fields[2].पूर्णांकeger.value;
		expected_length = 3 + desc_count * 14;

		अगर (record->package.count != expected_length)
			वापस AE_ERROR;

		क्रम (i = 2; i < expected_length; i++)
			अगर (fields[i].type != ACPI_TYPE_INTEGER)
				वापस AE_ERROR;

		क्रम (i = 0; i < desc_count; i++) अणु
			reg_fields = fields + 3 + i * 14;
			parse_hpx3_रेजिस्टर(&hpx3, reg_fields);
			program_hpx_type3(dev, &hpx3);
		पूर्ण

		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING
			"%s: Type 3 Revision %d record not supported\n",
			__func__, revision);
		वापस AE_ERROR;
	पूर्ण
	वापस AE_OK;
पूर्ण

अटल acpi_status acpi_run_hpx(काष्ठा pci_dev *dev, acpi_handle handle)
अणु
	acpi_status status;
	काष्ठा acpi_buffer buffer = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	जोड़ acpi_object *package, *record, *fields;
	काष्ठा hpx_type0 hpx0;
	काष्ठा hpx_type1 hpx1;
	काष्ठा hpx_type2 hpx2;
	u32 type;
	पूर्णांक i;

	status = acpi_evaluate_object(handle, "_HPX", शून्य, &buffer);
	अगर (ACPI_FAILURE(status))
		वापस status;

	package = (जोड़ acpi_object *)buffer.poपूर्णांकer;
	अगर (package->type != ACPI_TYPE_PACKAGE) अणु
		status = AE_ERROR;
		जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < package->package.count; i++) अणु
		record = &package->package.elements[i];
		अगर (record->type != ACPI_TYPE_PACKAGE) अणु
			status = AE_ERROR;
			जाओ निकास;
		पूर्ण

		fields = record->package.elements;
		अगर (fields[0].type != ACPI_TYPE_INTEGER ||
		    fields[1].type != ACPI_TYPE_INTEGER) अणु
			status = AE_ERROR;
			जाओ निकास;
		पूर्ण

		type = fields[0].पूर्णांकeger.value;
		चयन (type) अणु
		हाल 0:
			स_रखो(&hpx0, 0, माप(hpx0));
			status = decode_type0_hpx_record(record, &hpx0);
			अगर (ACPI_FAILURE(status))
				जाओ निकास;
			program_hpx_type0(dev, &hpx0);
			अवरोध;
		हाल 1:
			स_रखो(&hpx1, 0, माप(hpx1));
			status = decode_type1_hpx_record(record, &hpx1);
			अगर (ACPI_FAILURE(status))
				जाओ निकास;
			program_hpx_type1(dev, &hpx1);
			अवरोध;
		हाल 2:
			स_रखो(&hpx2, 0, माप(hpx2));
			status = decode_type2_hpx_record(record, &hpx2);
			अगर (ACPI_FAILURE(status))
				जाओ निकास;
			program_hpx_type2(dev, &hpx2);
			अवरोध;
		हाल 3:
			status = program_type3_hpx_record(dev, record);
			अगर (ACPI_FAILURE(status))
				जाओ निकास;
			अवरोध;
		शेष:
			pr_err("%s: Type %d record not supported\n",
			       __func__, type);
			status = AE_ERROR;
			जाओ निकास;
		पूर्ण
	पूर्ण
 निकास:
	kमुक्त(buffer.poपूर्णांकer);
	वापस status;
पूर्ण

अटल acpi_status acpi_run_hpp(काष्ठा pci_dev *dev, acpi_handle handle)
अणु
	acpi_status status;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *package, *fields;
	काष्ठा hpx_type0 hpx0;
	पूर्णांक i;

	स_रखो(&hpx0, 0, माप(hpx0));

	status = acpi_evaluate_object(handle, "_HPP", शून्य, &buffer);
	अगर (ACPI_FAILURE(status))
		वापस status;

	package = (जोड़ acpi_object *) buffer.poपूर्णांकer;
	अगर (package->type != ACPI_TYPE_PACKAGE ||
	    package->package.count != 4) अणु
		status = AE_ERROR;
		जाओ निकास;
	पूर्ण

	fields = package->package.elements;
	क्रम (i = 0; i < 4; i++) अणु
		अगर (fields[i].type != ACPI_TYPE_INTEGER) अणु
			status = AE_ERROR;
			जाओ निकास;
		पूर्ण
	पूर्ण

	hpx0.revision        = 1;
	hpx0.cache_line_size = fields[0].पूर्णांकeger.value;
	hpx0.latency_समयr   = fields[1].पूर्णांकeger.value;
	hpx0.enable_serr     = fields[2].पूर्णांकeger.value;
	hpx0.enable_perr     = fields[3].पूर्णांकeger.value;

	program_hpx_type0(dev, &hpx0);

निकास:
	kमुक्त(buffer.poपूर्णांकer);
	वापस status;
पूर्ण

/* pci_acpi_program_hp_params
 *
 * @dev - the pci_dev क्रम which we want parameters
 */
पूर्णांक pci_acpi_program_hp_params(काष्ठा pci_dev *dev)
अणु
	acpi_status status;
	acpi_handle handle, phandle;
	काष्ठा pci_bus *pbus;

	अगर (acpi_pci_disabled)
		वापस -ENODEV;

	handle = शून्य;
	क्रम (pbus = dev->bus; pbus; pbus = pbus->parent) अणु
		handle = acpi_pci_get_bridge_handle(pbus);
		अगर (handle)
			अवरोध;
	पूर्ण

	/*
	 * _HPP settings apply to all child buses, until another _HPP is
	 * encountered. If we करोn't find an _HPP क्रम the input pci dev,
	 * look क्रम it in the parent device scope since that would apply to
	 * this pci dev.
	 */
	जबतक (handle) अणु
		status = acpi_run_hpx(dev, handle);
		अगर (ACPI_SUCCESS(status))
			वापस 0;
		status = acpi_run_hpp(dev, handle);
		अगर (ACPI_SUCCESS(status))
			वापस 0;
		अगर (acpi_is_root_bridge(handle))
			अवरोध;
		status = acpi_get_parent(handle, &phandle);
		अगर (ACPI_FAILURE(status))
			अवरोध;
		handle = phandle;
	पूर्ण
	वापस -ENODEV;
पूर्ण

/**
 * pciehp_is_native - Check whether a hotplug port is handled by the OS
 * @bridge: Hotplug port to check
 *
 * Returns true अगर the given @bridge is handled by the native PCIe hotplug
 * driver.
 */
bool pciehp_is_native(काष्ठा pci_dev *bridge)
अणु
	स्थिर काष्ठा pci_host_bridge *host;
	u32 slot_cap;

	अगर (!IS_ENABLED(CONFIG_HOTPLUG_PCI_PCIE))
		वापस false;

	pcie_capability_पढ़ो_dword(bridge, PCI_EXP_SLTCAP, &slot_cap);
	अगर (!(slot_cap & PCI_EXP_SLTCAP_HPC))
		वापस false;

	अगर (pcie_ports_native)
		वापस true;

	host = pci_find_host_bridge(bridge->bus);
	वापस host->native_pcie_hotplug;
पूर्ण

/**
 * shpchp_is_native - Check whether a hotplug port is handled by the OS
 * @bridge: Hotplug port to check
 *
 * Returns true अगर the given @bridge is handled by the native SHPC hotplug
 * driver.
 */
bool shpchp_is_native(काष्ठा pci_dev *bridge)
अणु
	वापस bridge->shpc_managed;
पूर्ण

/**
 * pci_acpi_wake_bus - Root bus wakeup notअगरication विभाजन function.
 * @context: Device wakeup context.
 */
अटल व्योम pci_acpi_wake_bus(काष्ठा acpi_device_wakeup_context *context)
अणु
	काष्ठा acpi_device *adev;
	काष्ठा acpi_pci_root *root;

	adev = container_of(context, काष्ठा acpi_device, wakeup.context);
	root = acpi_driver_data(adev);
	pci_pme_wakeup_bus(root->bus);
पूर्ण

/**
 * pci_acpi_wake_dev - PCI device wakeup notअगरication work function.
 * @context: Device wakeup context.
 */
अटल व्योम pci_acpi_wake_dev(काष्ठा acpi_device_wakeup_context *context)
अणु
	काष्ठा pci_dev *pci_dev;

	pci_dev = to_pci_dev(context->dev);

	अगर (pci_dev->pme_poll)
		pci_dev->pme_poll = false;

	अगर (pci_dev->current_state == PCI_D3cold) अणु
		pci_wakeup_event(pci_dev);
		pm_request_resume(&pci_dev->dev);
		वापस;
	पूर्ण

	/* Clear PME Status अगर set. */
	अगर (pci_dev->pme_support)
		pci_check_pme_status(pci_dev);

	pci_wakeup_event(pci_dev);
	pm_request_resume(&pci_dev->dev);

	pci_pme_wakeup_bus(pci_dev->subordinate);
पूर्ण

/**
 * pci_acpi_add_bus_pm_notअगरier - Register PM notअगरier क्रम root PCI bus.
 * @dev: PCI root bridge ACPI device.
 */
acpi_status pci_acpi_add_bus_pm_notअगरier(काष्ठा acpi_device *dev)
अणु
	वापस acpi_add_pm_notअगरier(dev, शून्य, pci_acpi_wake_bus);
पूर्ण

/**
 * pci_acpi_add_pm_notअगरier - Register PM notअगरier क्रम given PCI device.
 * @dev: ACPI device to add the notअगरier क्रम.
 * @pci_dev: PCI device to check क्रम the PME status अगर an event is संकेतed.
 */
acpi_status pci_acpi_add_pm_notअगरier(काष्ठा acpi_device *dev,
				     काष्ठा pci_dev *pci_dev)
अणु
	वापस acpi_add_pm_notअगरier(dev, &pci_dev->dev, pci_acpi_wake_dev);
पूर्ण

/*
 * _SxD वापसs the D-state with the highest घातer
 * (lowest D-state number) supported in the S-state "x".
 *
 * If the devices करोes not have a _PRW
 * (Power Resources क्रम Wake) supporting प्रणाली wakeup from "x"
 * then the OS is मुक्त to choose a lower घातer (higher number
 * D-state) than the वापस value from _SxD.
 *
 * But अगर _PRW is enabled at S-state "x", the OS
 * must not choose a घातer lower than _SxD --
 * unless the device has an _SxW method specअगरying
 * the lowest घातer (highest D-state number) the device
 * may enter जबतक still able to wake the प्रणाली.
 *
 * ie. depending on global OS policy:
 *
 * अगर (_PRW at S-state x)
 *	choose from highest घातer _SxD to lowest घातer _SxW
 * अन्यथा // no _PRW at S-state x
 *	choose highest घातer _SxD or any lower घातer
 */

अटल pci_घातer_t acpi_pci_choose_state(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक acpi_state, d_max;

	अगर (pdev->no_d3cold)
		d_max = ACPI_STATE_D3_HOT;
	अन्यथा
		d_max = ACPI_STATE_D3_COLD;
	acpi_state = acpi_pm_device_sleep_state(&pdev->dev, शून्य, d_max);
	अगर (acpi_state < 0)
		वापस PCI_POWER_ERROR;

	चयन (acpi_state) अणु
	हाल ACPI_STATE_D0:
		वापस PCI_D0;
	हाल ACPI_STATE_D1:
		वापस PCI_D1;
	हाल ACPI_STATE_D2:
		वापस PCI_D2;
	हाल ACPI_STATE_D3_HOT:
		वापस PCI_D3hot;
	हाल ACPI_STATE_D3_COLD:
		वापस PCI_D3cold;
	पूर्ण
	वापस PCI_POWER_ERROR;
पूर्ण

अटल काष्ठा acpi_device *acpi_pci_find_companion(काष्ठा device *dev);

अटल bool acpi_pci_bridge_d3(काष्ठा pci_dev *dev)
अणु
	स्थिर काष्ठा fwnode_handle *fwnode;
	काष्ठा acpi_device *adev;
	काष्ठा pci_dev *root;
	u8 val;

	अगर (!dev->is_hotplug_bridge)
		वापस false;

	/* Assume D3 support अगर the bridge is घातer-manageable by ACPI. */
	adev = ACPI_COMPANION(&dev->dev);
	अगर (!adev && !pci_dev_is_added(dev)) अणु
		adev = acpi_pci_find_companion(&dev->dev);
		ACPI_COMPANION_SET(&dev->dev, adev);
	पूर्ण

	अगर (adev && acpi_device_घातer_manageable(adev))
		वापस true;

	/*
	 * Look क्रम a special _DSD property क्रम the root port and अगर it
	 * is set we know the hierarchy behind it supports D3 just fine.
	 */
	root = pcie_find_root_port(dev);
	अगर (!root)
		वापस false;

	adev = ACPI_COMPANION(&root->dev);
	अगर (root == dev) अणु
		/*
		 * It is possible that the ACPI companion is not yet bound
		 * क्रम the root port so look it up manually here.
		 */
		अगर (!adev && !pci_dev_is_added(root))
			adev = acpi_pci_find_companion(&root->dev);
	पूर्ण

	अगर (!adev)
		वापस false;

	fwnode = acpi_fwnode_handle(adev);
	अगर (fwnode_property_पढ़ो_u8(fwnode, "HotPlugSupportInD3", &val))
		वापस false;

	वापस val == 1;
पूर्ण

अटल bool acpi_pci_घातer_manageable(काष्ठा pci_dev *dev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&dev->dev);
	वापस adev ? acpi_device_घातer_manageable(adev) : false;
पूर्ण

अटल पूर्णांक acpi_pci_set_घातer_state(काष्ठा pci_dev *dev, pci_घातer_t state)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&dev->dev);
	अटल स्थिर u8 state_conv[] = अणु
		[PCI_D0] = ACPI_STATE_D0,
		[PCI_D1] = ACPI_STATE_D1,
		[PCI_D2] = ACPI_STATE_D2,
		[PCI_D3hot] = ACPI_STATE_D3_HOT,
		[PCI_D3cold] = ACPI_STATE_D3_COLD,
	पूर्ण;
	पूर्णांक error = -EINVAL;

	/* If the ACPI device has _EJ0, ignore the device */
	अगर (!adev || acpi_has_method(adev->handle, "_EJ0"))
		वापस -ENODEV;

	चयन (state) अणु
	हाल PCI_D3cold:
		अगर (dev_pm_qos_flags(&dev->dev, PM_QOS_FLAG_NO_POWER_OFF) ==
				PM_QOS_FLAGS_ALL) अणु
			error = -EBUSY;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल PCI_D0:
	हाल PCI_D1:
	हाल PCI_D2:
	हाल PCI_D3hot:
		error = acpi_device_set_घातer(adev, state_conv[state]);
	पूर्ण

	अगर (!error)
		pci_dbg(dev, "power state changed by ACPI to %s\n",
		        acpi_घातer_state_string(adev->घातer.state));

	वापस error;
पूर्ण

अटल pci_घातer_t acpi_pci_get_घातer_state(काष्ठा pci_dev *dev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&dev->dev);
	अटल स्थिर pci_घातer_t state_conv[] = अणु
		[ACPI_STATE_D0]      = PCI_D0,
		[ACPI_STATE_D1]      = PCI_D1,
		[ACPI_STATE_D2]      = PCI_D2,
		[ACPI_STATE_D3_HOT]  = PCI_D3hot,
		[ACPI_STATE_D3_COLD] = PCI_D3cold,
	पूर्ण;
	पूर्णांक state;

	अगर (!adev || !acpi_device_घातer_manageable(adev))
		वापस PCI_UNKNOWN;

	state = adev->घातer.state;
	अगर (state == ACPI_STATE_UNKNOWN)
		वापस PCI_UNKNOWN;

	वापस state_conv[state];
पूर्ण

अटल व्योम acpi_pci_refresh_घातer_state(काष्ठा pci_dev *dev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&dev->dev);

	अगर (adev && acpi_device_घातer_manageable(adev))
		acpi_device_update_घातer(adev, शून्य);
पूर्ण

अटल पूर्णांक acpi_pci_propagate_wakeup(काष्ठा pci_bus *bus, bool enable)
अणु
	जबतक (bus->parent) अणु
		अगर (acpi_pm_device_can_wakeup(&bus->self->dev))
			वापस acpi_pm_set_device_wakeup(&bus->self->dev, enable);

		bus = bus->parent;
	पूर्ण

	/* We have reached the root bus. */
	अगर (bus->bridge) अणु
		अगर (acpi_pm_device_can_wakeup(bus->bridge))
			वापस acpi_pm_set_device_wakeup(bus->bridge, enable);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_pci_wakeup(काष्ठा pci_dev *dev, bool enable)
अणु
	अगर (acpi_pm_device_can_wakeup(&dev->dev))
		वापस acpi_pm_set_device_wakeup(&dev->dev, enable);

	वापस acpi_pci_propagate_wakeup(dev->bus, enable);
पूर्ण

अटल bool acpi_pci_need_resume(काष्ठा pci_dev *dev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&dev->dev);

	/*
	 * In some हालs (eg. Samsung 305V4A) leaving a bridge in suspend over
	 * प्रणाली-wide suspend/resume confuses the platक्रमm firmware, so aव्योम
	 * करोing that.  According to Section 16.1.6 of ACPI 6.2, endpoपूर्णांक
	 * devices are expected to be in D3 beक्रमe invoking the S3 entry path
	 * from the firmware, so they should not be affected by this issue.
	 */
	अगर (pci_is_bridge(dev) && acpi_target_प्रणाली_state() != ACPI_STATE_S0)
		वापस true;

	अगर (!adev || !acpi_device_घातer_manageable(adev))
		वापस false;

	अगर (adev->wakeup.flags.valid &&
	    device_may_wakeup(&dev->dev) != !!adev->wakeup.prepare_count)
		वापस true;

	अगर (acpi_target_प्रणाली_state() == ACPI_STATE_S0)
		वापस false;

	वापस !!adev->घातer.flags.dsw_present;
पूर्ण

अटल स्थिर काष्ठा pci_platक्रमm_pm_ops acpi_pci_platक्रमm_pm = अणु
	.bridge_d3 = acpi_pci_bridge_d3,
	.is_manageable = acpi_pci_घातer_manageable,
	.set_state = acpi_pci_set_घातer_state,
	.get_state = acpi_pci_get_घातer_state,
	.refresh_state = acpi_pci_refresh_घातer_state,
	.choose_state = acpi_pci_choose_state,
	.set_wakeup = acpi_pci_wakeup,
	.need_resume = acpi_pci_need_resume,
पूर्ण;

व्योम acpi_pci_add_bus(काष्ठा pci_bus *bus)
अणु
	जोड़ acpi_object *obj;
	काष्ठा pci_host_bridge *bridge;

	अगर (acpi_pci_disabled || !bus->bridge || !ACPI_HANDLE(bus->bridge))
		वापस;

	acpi_pci_slot_क्रमागतerate(bus);
	acpiphp_क्रमागतerate_slots(bus);

	/*
	 * For a host bridge, check its _DSM क्रम function 8 and अगर
	 * that is available, mark it in pci_host_bridge.
	 */
	अगर (!pci_is_root_bus(bus))
		वापस;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(bus->bridge), &pci_acpi_dsm_guid, 3,
				DSM_PCI_POWER_ON_RESET_DELAY, शून्य);
	अगर (!obj)
		वापस;

	अगर (obj->type == ACPI_TYPE_INTEGER && obj->पूर्णांकeger.value == 1) अणु
		bridge = pci_find_host_bridge(bus);
		bridge->ignore_reset_delay = 1;
	पूर्ण
	ACPI_FREE(obj);
पूर्ण

व्योम acpi_pci_हटाओ_bus(काष्ठा pci_bus *bus)
अणु
	अगर (acpi_pci_disabled || !bus->bridge)
		वापस;

	acpiphp_हटाओ_slots(bus);
	acpi_pci_slot_हटाओ(bus);
पूर्ण

/* ACPI bus type */
अटल काष्ठा acpi_device *acpi_pci_find_companion(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा acpi_device *adev;
	bool check_children;
	u64 addr;

	check_children = pci_is_bridge(pci_dev);
	/* Please ref to ACPI spec क्रम the syntax of _ADR */
	addr = (PCI_SLOT(pci_dev->devfn) << 16) | PCI_FUNC(pci_dev->devfn);
	adev = acpi_find_child_device(ACPI_COMPANION(dev->parent), addr,
				      check_children);

	/*
	 * There may be ACPI device objects in the ACPI namespace that are
	 * children of the device object representing the host bridge, but करोn't
	 * represent PCI devices.  Both _HID and _ADR may be present क्रम them,
	 * even though that is against the specअगरication (क्रम example, see
	 * Section 6.1 of ACPI 6.3), but in many हालs the _ADR वापसs 0 which
	 * appears to indicate that they should not be taken पूर्णांकo consideration
	 * as potential companions of PCI devices on the root bus.
	 *
	 * To catch this special हाल, disregard the वापसed device object अगर
	 * it has a valid _HID, addr is 0 and the PCI device at hand is on the
	 * root bus.
	 */
	अगर (adev && adev->pnp.type.platक्रमm_id && !addr &&
	    pci_is_root_bus(pci_dev->bus))
		वापस शून्य;

	वापस adev;
पूर्ण

/**
 * pci_acpi_optimize_delay - optimize PCI D3 and D3cold delay from ACPI
 * @pdev: the PCI device whose delay is to be updated
 * @handle: ACPI handle of this device
 *
 * Update the d3hot_delay and d3cold_delay of a PCI device from the ACPI _DSM
 * control method of either the device itself or the PCI host bridge.
 *
 * Function 8, "Reset Delay," applies to the entire hierarchy below a PCI
 * host bridge.  If it वापसs one, the OS may assume that all devices in
 * the hierarchy have alपढ़ोy completed घातer-on reset delays.
 *
 * Function 9, "Device Readiness Durations," applies only to the object
 * where it is located.  It वापसs delay durations required after various
 * events अगर the device requires less समय than the spec requires.  Delays
 * from this function take precedence over the Reset Delay function.
 *
 * These _DSM functions are defined by the draft ECN of January 28, 2014,
 * titled "ACPI additions for FW latency optimizations."
 */
अटल व्योम pci_acpi_optimize_delay(काष्ठा pci_dev *pdev,
				    acpi_handle handle)
अणु
	काष्ठा pci_host_bridge *bridge = pci_find_host_bridge(pdev->bus);
	पूर्णांक value;
	जोड़ acpi_object *obj, *elements;

	अगर (bridge->ignore_reset_delay)
		pdev->d3cold_delay = 0;

	obj = acpi_evaluate_dsm(handle, &pci_acpi_dsm_guid, 3,
				DSM_PCI_DEVICE_READINESS_DURATIONS, शून्य);
	अगर (!obj)
		वापस;

	अगर (obj->type == ACPI_TYPE_PACKAGE && obj->package.count == 5) अणु
		elements = obj->package.elements;
		अगर (elements[0].type == ACPI_TYPE_INTEGER) अणु
			value = (पूर्णांक)elements[0].पूर्णांकeger.value / 1000;
			अगर (value < PCI_PM_D3COLD_WAIT)
				pdev->d3cold_delay = value;
		पूर्ण
		अगर (elements[3].type == ACPI_TYPE_INTEGER) अणु
			value = (पूर्णांक)elements[3].पूर्णांकeger.value / 1000;
			अगर (value < PCI_PM_D3HOT_WAIT)
				pdev->d3hot_delay = value;
		पूर्ण
	पूर्ण
	ACPI_FREE(obj);
पूर्ण

अटल व्योम pci_acpi_set_बाह्यal_facing(काष्ठा pci_dev *dev)
अणु
	u8 val;

	अगर (pci_pcie_type(dev) != PCI_EXP_TYPE_ROOT_PORT)
		वापस;
	अगर (device_property_पढ़ो_u8(&dev->dev, "ExternalFacingPort", &val))
		वापस;

	/*
	 * These root ports expose PCIe (including DMA) outside of the
	 * प्रणाली.  Everything करोwnstream from them is बाह्यal.
	 */
	अगर (val)
		dev->बाह्यal_facing = 1;
पूर्ण

अटल व्योम pci_acpi_setup(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);

	अगर (!adev)
		वापस;

	pci_acpi_optimize_delay(pci_dev, adev->handle);
	pci_acpi_set_बाह्यal_facing(pci_dev);
	pci_acpi_add_edr_notअगरier(pci_dev);

	pci_acpi_add_pm_notअगरier(adev, pci_dev);
	अगर (!adev->wakeup.flags.valid)
		वापस;

	device_set_wakeup_capable(dev, true);
	/*
	 * For bridges that can करो D3 we enable wake स्वतःmatically (as
	 * we करो क्रम the घातer management itself in that हाल). The
	 * reason is that the bridge may have additional methods such as
	 * _DSW that need to be called.
	 */
	अगर (pci_dev->bridge_d3)
		device_wakeup_enable(dev);

	acpi_pci_wakeup(pci_dev, false);
	acpi_device_घातer_add_dependent(adev, dev);
पूर्ण

अटल व्योम pci_acpi_cleanup(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);

	अगर (!adev)
		वापस;

	pci_acpi_हटाओ_edr_notअगरier(pci_dev);
	pci_acpi_हटाओ_pm_notअगरier(adev);
	अगर (adev->wakeup.flags.valid) अणु
		acpi_device_घातer_हटाओ_dependent(adev, dev);
		अगर (pci_dev->bridge_d3)
			device_wakeup_disable(dev);

		device_set_wakeup_capable(dev, false);
	पूर्ण
पूर्ण

अटल bool pci_acpi_bus_match(काष्ठा device *dev)
अणु
	वापस dev_is_pci(dev);
पूर्ण

अटल काष्ठा acpi_bus_type acpi_pci_bus = अणु
	.name = "PCI",
	.match = pci_acpi_bus_match,
	.find_companion = acpi_pci_find_companion,
	.setup = pci_acpi_setup,
	.cleanup = pci_acpi_cleanup,
पूर्ण;


अटल काष्ठा fwnode_handle *(*pci_msi_get_fwnode_cb)(काष्ठा device *dev);

/**
 * pci_msi_रेजिस्टर_fwnode_provider - Register callback to retrieve fwnode
 * @fn:       Callback matching a device to a fwnode that identअगरies a PCI
 *            MSI करोमुख्य.
 *
 * This should be called by irqchip driver, which is the parent of
 * the MSI करोमुख्य to provide callback पूर्णांकerface to query fwnode.
 */
व्योम
pci_msi_रेजिस्टर_fwnode_provider(काष्ठा fwnode_handle *(*fn)(काष्ठा device *))
अणु
	pci_msi_get_fwnode_cb = fn;
पूर्ण

/**
 * pci_host_bridge_acpi_msi_करोमुख्य - Retrieve MSI करोमुख्य of a PCI host bridge
 * @bus:      The PCI host bridge bus.
 *
 * This function uses the callback function रेजिस्टरed by
 * pci_msi_रेजिस्टर_fwnode_provider() to retrieve the irq_करोमुख्य with
 * type DOMAIN_BUS_PCI_MSI of the specअगरied host bridge bus.
 * This वापसs शून्य on error or when the करोमुख्य is not found.
 */
काष्ठा irq_करोमुख्य *pci_host_bridge_acpi_msi_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	काष्ठा fwnode_handle *fwnode;

	अगर (!pci_msi_get_fwnode_cb)
		वापस शून्य;

	fwnode = pci_msi_get_fwnode_cb(&bus->dev);
	अगर (!fwnode)
		वापस शून्य;

	वापस irq_find_matching_fwnode(fwnode, DOMAIN_BUS_PCI_MSI);
पूर्ण

अटल पूर्णांक __init acpi_pci_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (acpi_gbl_FADT.boot_flags & ACPI_FADT_NO_MSI) अणु
		pr_info("ACPI FADT declares the system doesn't support MSI, so disable it\n");
		pci_no_msi();
	पूर्ण

	अगर (acpi_gbl_FADT.boot_flags & ACPI_FADT_NO_ASPM) अणु
		pr_info("ACPI FADT declares the system doesn't support PCIe ASPM, so disable it\n");
		pcie_no_aspm();
	पूर्ण

	ret = रेजिस्टर_acpi_bus_type(&acpi_pci_bus);
	अगर (ret)
		वापस 0;

	pci_set_platक्रमm_pm(&acpi_pci_platक्रमm_pm);
	acpi_pci_slot_init();
	acpiphp_init();

	वापस 0;
पूर्ण
arch_initcall(acpi_pci_init);
