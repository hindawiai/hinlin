<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2017 IBM Corp.
#समावेश <linux/pci.h>
#समावेश <यंत्र/pnv-ocxl.h>
#समावेश <misc/ocxl-config.h>
#समावेश "ocxl_internal.h"

#घोषणा EXTRACT_BIT(val, bit) (!!(val & BIT(bit)))
#घोषणा EXTRACT_BITS(val, s, e) ((val & GENMASK(e, s)) >> s)

#घोषणा OCXL_DVSEC_AFU_IDX_MASK              GENMASK(5, 0)
#घोषणा OCXL_DVSEC_ACTAG_MASK                GENMASK(11, 0)
#घोषणा OCXL_DVSEC_PASID_MASK                GENMASK(19, 0)
#घोषणा OCXL_DVSEC_PASID_LOG_MASK            GENMASK(4, 0)

#घोषणा OCXL_DVSEC_TEMPL_VERSION         0x0
#घोषणा OCXL_DVSEC_TEMPL_NAME            0x4
#घोषणा OCXL_DVSEC_TEMPL_AFU_VERSION     0x1C
#घोषणा OCXL_DVSEC_TEMPL_MMIO_GLOBAL     0x20
#घोषणा OCXL_DVSEC_TEMPL_MMIO_GLOBAL_SZ  0x28
#घोषणा OCXL_DVSEC_TEMPL_MMIO_PP         0x30
#घोषणा OCXL_DVSEC_TEMPL_MMIO_PP_SZ      0x38
#घोषणा OCXL_DVSEC_TEMPL_ALL_MEM_SZ      0x3C
#घोषणा OCXL_DVSEC_TEMPL_LPC_MEM_START   0x40
#घोषणा OCXL_DVSEC_TEMPL_WWID            0x48
#घोषणा OCXL_DVSEC_TEMPL_LPC_MEM_SZ      0x58

#घोषणा OCXL_MAX_AFU_PER_FUNCTION 64
#घोषणा OCXL_TEMPL_LEN_1_0        0x58
#घोषणा OCXL_TEMPL_LEN_1_1        0x60
#घोषणा OCXL_TEMPL_NAME_LEN       24
#घोषणा OCXL_CFG_TIMEOUT     3

अटल पूर्णांक find_dvsec(काष्ठा pci_dev *dev, पूर्णांक dvsec_id)
अणु
	पूर्णांक vsec = 0;
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
	u16 venकरोr, id;
	u8 idx;

	जबतक ((vsec = pci_find_next_ext_capability(dev, vsec,
						    OCXL_EXT_CAP_ID_DVSEC))) अणु
		pci_पढ़ो_config_word(dev, vsec + OCXL_DVSEC_VENDOR_OFFSET,
				&venकरोr);
		pci_पढ़ो_config_word(dev, vsec + OCXL_DVSEC_ID_OFFSET, &id);

		अगर (venकरोr == PCI_VENDOR_ID_IBM &&
			id == OCXL_DVSEC_AFU_CTRL_ID) अणु
			pci_पढ़ो_config_byte(dev,
					vsec + OCXL_DVSEC_AFU_CTRL_AFU_IDX,
					&idx);
			अगर (idx == afu_idx)
				वापस vsec;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * get_function_0() - Find a related PCI device (function 0)
 * @dev: PCI device to match
 *
 * Returns a poपूर्णांकer to the related device, or null अगर not found
 */
अटल काष्ठा pci_dev *get_function_0(काष्ठा pci_dev *dev)
अणु
	अचिन्हित पूर्णांक devfn = PCI_DEVFN(PCI_SLOT(dev->devfn), 0);

	वापस pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(dev->bus),
					   dev->bus->number, devfn);
पूर्ण

अटल व्योम पढ़ो_pasid(काष्ठा pci_dev *dev, काष्ठा ocxl_fn_config *fn)
अणु
	u16 val;
	पूर्णांक pos;

	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_PASID);
	अगर (!pos) अणु
		/*
		 * PASID capability is not mandatory, but there
		 * shouldn't be any AFU
		 */
		dev_dbg(&dev->dev, "Function doesn't require any PASID\n");
		fn->max_pasid_log = -1;
		जाओ out;
	पूर्ण
	pci_पढ़ो_config_word(dev, pos + PCI_PASID_CAP, &val);
	fn->max_pasid_log = EXTRACT_BITS(val, 8, 12);

out:
	dev_dbg(&dev->dev, "PASID capability:\n");
	dev_dbg(&dev->dev, "  Max PASID log = %d\n", fn->max_pasid_log);
पूर्ण

अटल पूर्णांक पढ़ो_dvsec_tl(काष्ठा pci_dev *dev, काष्ठा ocxl_fn_config *fn)
अणु
	पूर्णांक pos;

	pos = find_dvsec(dev, OCXL_DVSEC_TL_ID);
	अगर (!pos && PCI_FUNC(dev->devfn) == 0) अणु
		dev_err(&dev->dev, "Can't find TL DVSEC\n");
		वापस -ENODEV;
	पूर्ण
	अगर (pos && PCI_FUNC(dev->devfn) != 0) अणु
		dev_err(&dev->dev, "TL DVSEC is only allowed on function 0\n");
		वापस -ENODEV;
	पूर्ण
	fn->dvsec_tl_pos = pos;
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_dvsec_function(काष्ठा pci_dev *dev, काष्ठा ocxl_fn_config *fn)
अणु
	पूर्णांक pos, afu_present;
	u32 val;

	pos = find_dvsec(dev, OCXL_DVSEC_FUNC_ID);
	अगर (!pos) अणु
		dev_err(&dev->dev, "Can't find function DVSEC\n");
		वापस -ENODEV;
	पूर्ण
	fn->dvsec_function_pos = pos;

	pci_पढ़ो_config_dword(dev, pos + OCXL_DVSEC_FUNC_OFF_INDEX, &val);
	afu_present = EXTRACT_BIT(val, 31);
	अगर (!afu_present) अणु
		fn->max_afu_index = -1;
		dev_dbg(&dev->dev, "Function doesn't define any AFU\n");
		जाओ out;
	पूर्ण
	fn->max_afu_index = EXTRACT_BITS(val, 24, 29);

out:
	dev_dbg(&dev->dev, "Function DVSEC:\n");
	dev_dbg(&dev->dev, "  Max AFU index = %d\n", fn->max_afu_index);
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_dvsec_afu_info(काष्ठा pci_dev *dev, काष्ठा ocxl_fn_config *fn)
अणु
	पूर्णांक pos;

	अगर (fn->max_afu_index < 0) अणु
		fn->dvsec_afu_info_pos = -1;
		वापस 0;
	पूर्ण

	pos = find_dvsec(dev, OCXL_DVSEC_AFU_INFO_ID);
	अगर (!pos) अणु
		dev_err(&dev->dev, "Can't find AFU information DVSEC\n");
		वापस -ENODEV;
	पूर्ण
	fn->dvsec_afu_info_pos = pos;
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_dvsec_venकरोr(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pos;
	u32 cfg, tlx, dlx, reset_reload;

	/*
	 * venकरोr specअगरic DVSEC, क्रम IBM images only. Some older
	 * images may not have it
	 *
	 * It's only used on function 0 to specअगरy the version of some
	 * logic blocks and to give access to special रेजिस्टरs to
	 * enable host-based flashing.
	 */
	अगर (PCI_FUNC(dev->devfn) != 0)
		वापस 0;

	pos = find_dvsec(dev, OCXL_DVSEC_VENDOR_ID);
	अगर (!pos)
		वापस 0;

	pci_पढ़ो_config_dword(dev, pos + OCXL_DVSEC_VENDOR_CFG_VERS, &cfg);
	pci_पढ़ो_config_dword(dev, pos + OCXL_DVSEC_VENDOR_TLX_VERS, &tlx);
	pci_पढ़ो_config_dword(dev, pos + OCXL_DVSEC_VENDOR_DLX_VERS, &dlx);
	pci_पढ़ो_config_dword(dev, pos + OCXL_DVSEC_VENDOR_RESET_RELOAD,
			      &reset_reload);

	dev_dbg(&dev->dev, "Vendor specific DVSEC:\n");
	dev_dbg(&dev->dev, "  CFG version = 0x%x\n", cfg);
	dev_dbg(&dev->dev, "  TLX version = 0x%x\n", tlx);
	dev_dbg(&dev->dev, "  DLX version = 0x%x\n", dlx);
	dev_dbg(&dev->dev, "  ResetReload = 0x%x\n", reset_reload);
	वापस 0;
पूर्ण

अटल पूर्णांक get_dvsec_venकरोr0(काष्ठा pci_dev *dev, काष्ठा pci_dev **dev0,
			     पूर्णांक *out_pos)
अणु
	पूर्णांक pos;

	अगर (PCI_FUNC(dev->devfn) != 0) अणु
		dev = get_function_0(dev);
		अगर (!dev)
			वापस -1;
	पूर्ण
	pos = find_dvsec(dev, OCXL_DVSEC_VENDOR_ID);
	अगर (!pos)
		वापस -1;
	*dev0 = dev;
	*out_pos = pos;
	वापस 0;
पूर्ण

पूर्णांक ocxl_config_get_reset_reload(काष्ठा pci_dev *dev, पूर्णांक *val)
अणु
	काष्ठा pci_dev *dev0;
	u32 reset_reload;
	पूर्णांक pos;

	अगर (get_dvsec_venकरोr0(dev, &dev0, &pos))
		वापस -1;

	pci_पढ़ो_config_dword(dev0, pos + OCXL_DVSEC_VENDOR_RESET_RELOAD,
			      &reset_reload);
	*val = !!(reset_reload & BIT(0));
	वापस 0;
पूर्ण

पूर्णांक ocxl_config_set_reset_reload(काष्ठा pci_dev *dev, पूर्णांक val)
अणु
	काष्ठा pci_dev *dev0;
	u32 reset_reload;
	पूर्णांक pos;

	अगर (get_dvsec_venकरोr0(dev, &dev0, &pos))
		वापस -1;

	pci_पढ़ो_config_dword(dev0, pos + OCXL_DVSEC_VENDOR_RESET_RELOAD,
			      &reset_reload);
	अगर (val)
		reset_reload |= BIT(0);
	अन्यथा
		reset_reload &= ~BIT(0);
	pci_ग_लिखो_config_dword(dev0, pos + OCXL_DVSEC_VENDOR_RESET_RELOAD,
			       reset_reload);
	वापस 0;
पूर्ण

अटल पूर्णांक validate_function(काष्ठा pci_dev *dev, काष्ठा ocxl_fn_config *fn)
अणु
	अगर (fn->max_pasid_log == -1 && fn->max_afu_index >= 0) अणु
		dev_err(&dev->dev,
			"AFUs are defined but no PASIDs are requested\n");
		वापस -EINVAL;
	पूर्ण

	अगर (fn->max_afu_index > OCXL_MAX_AFU_PER_FUNCTION) अणु
		dev_err(&dev->dev,
			"Max AFU index out of architectural limit (%d vs %d)\n",
			fn->max_afu_index, OCXL_MAX_AFU_PER_FUNCTION);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ocxl_config_पढ़ो_function(काष्ठा pci_dev *dev, काष्ठा ocxl_fn_config *fn)
अणु
	पूर्णांक rc;

	पढ़ो_pasid(dev, fn);

	rc = पढ़ो_dvsec_tl(dev, fn);
	अगर (rc) अणु
		dev_err(&dev->dev,
			"Invalid Transaction Layer DVSEC configuration: %d\n",
			rc);
		वापस -ENODEV;
	पूर्ण

	rc = पढ़ो_dvsec_function(dev, fn);
	अगर (rc) अणु
		dev_err(&dev->dev,
			"Invalid Function DVSEC configuration: %d\n", rc);
		वापस -ENODEV;
	पूर्ण

	rc = पढ़ो_dvsec_afu_info(dev, fn);
	अगर (rc) अणु
		dev_err(&dev->dev, "Invalid AFU configuration: %d\n", rc);
		वापस -ENODEV;
	पूर्ण

	rc = पढ़ो_dvsec_venकरोr(dev);
	अगर (rc) अणु
		dev_err(&dev->dev,
			"Invalid vendor specific DVSEC configuration: %d\n",
			rc);
		वापस -ENODEV;
	पूर्ण

	rc = validate_function(dev, fn);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_config_पढ़ो_function);

अटल पूर्णांक पढ़ो_afu_info(काष्ठा pci_dev *dev, काष्ठा ocxl_fn_config *fn,
			पूर्णांक offset, u32 *data)
अणु
	u32 val;
	अचिन्हित दीर्घ समयout = jअगरfies + (HZ * OCXL_CFG_TIMEOUT);
	पूर्णांक pos = fn->dvsec_afu_info_pos;

	/* Protect 'data valid' bit */
	अगर (EXTRACT_BIT(offset, 31)) अणु
		dev_err(&dev->dev, "Invalid offset in AFU info DVSEC\n");
		वापस -EINVAL;
	पूर्ण

	pci_ग_लिखो_config_dword(dev, pos + OCXL_DVSEC_AFU_INFO_OFF, offset);
	pci_पढ़ो_config_dword(dev, pos + OCXL_DVSEC_AFU_INFO_OFF, &val);
	जबतक (!EXTRACT_BIT(val, 31)) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			dev_err(&dev->dev,
				"Timeout while reading AFU info DVSEC (offset=%d)\n",
				offset);
			वापस -EBUSY;
		पूर्ण
		cpu_relax();
		pci_पढ़ो_config_dword(dev, pos + OCXL_DVSEC_AFU_INFO_OFF, &val);
	पूर्ण
	pci_पढ़ो_config_dword(dev, pos + OCXL_DVSEC_AFU_INFO_DATA, data);
	वापस 0;
पूर्ण

/**
 * पढ़ो_ढाँचा_version() - Read the ढाँचा version from the AFU
 * @dev: the device क्रम the AFU
 * @fn: the AFU offsets
 * @len: outमाला_दो the ढाँचा length
 * @version: outमाला_दो the major<<8,minor version
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक पढ़ो_ढाँचा_version(काष्ठा pci_dev *dev, काष्ठा ocxl_fn_config *fn,
				 u16 *len, u16 *version)
अणु
	u32 val32;
	u8 major, minor;
	पूर्णांक rc;

	rc = पढ़ो_afu_info(dev, fn, OCXL_DVSEC_TEMPL_VERSION, &val32);
	अगर (rc)
		वापस rc;

	*len = EXTRACT_BITS(val32, 16, 31);
	major = EXTRACT_BITS(val32, 8, 15);
	minor = EXTRACT_BITS(val32, 0, 7);
	*version = (major << 8) + minor;
	वापस 0;
पूर्ण

पूर्णांक ocxl_config_check_afu_index(काष्ठा pci_dev *dev,
				काष्ठा ocxl_fn_config *fn, पूर्णांक afu_idx)
अणु
	पूर्णांक rc;
	u16 templ_version;
	u16 len, expected_len;

	pci_ग_लिखो_config_byte(dev,
			fn->dvsec_afu_info_pos + OCXL_DVSEC_AFU_INFO_AFU_IDX,
			afu_idx);

	rc = पढ़ो_ढाँचा_version(dev, fn, &len, &templ_version);
	अगर (rc)
		वापस rc;

	/* AFU index map can have holes, in which हाल we पढ़ो all 0's */
	अगर (!templ_version && !len)
		वापस 0;

	dev_dbg(&dev->dev, "AFU descriptor template version %d.%d\n",
		templ_version >> 8, templ_version & 0xFF);

	चयन (templ_version) अणु
	हाल 0x0005: // v0.5 was used prior to the spec approval
	हाल 0x0100:
		expected_len = OCXL_TEMPL_LEN_1_0;
		अवरोध;
	हाल 0x0101:
		expected_len = OCXL_TEMPL_LEN_1_1;
		अवरोध;
	शेष:
		dev_warn(&dev->dev, "Unknown AFU template version %#x\n",
			templ_version);
		expected_len = len;
	पूर्ण
	अगर (len != expected_len)
		dev_warn(&dev->dev,
			"Unexpected template length %#x in AFU information, expected %#x for version %#x\n",
			len, expected_len, templ_version);
	वापस 1;
पूर्ण

अटल पूर्णांक पढ़ो_afu_name(काष्ठा pci_dev *dev, काष्ठा ocxl_fn_config *fn,
			काष्ठा ocxl_afu_config *afu)
अणु
	पूर्णांक i, rc;
	u32 val, *ptr;

	BUILD_BUG_ON(OCXL_AFU_NAME_SZ < OCXL_TEMPL_NAME_LEN);
	क्रम (i = 0; i < OCXL_TEMPL_NAME_LEN; i += 4) अणु
		rc = पढ़ो_afu_info(dev, fn, OCXL_DVSEC_TEMPL_NAME + i, &val);
		अगर (rc)
			वापस rc;
		ptr = (u32 *) &afu->name[i];
		*ptr = le32_to_cpu((__क्रमce __le32) val);
	पूर्ण
	afu->name[OCXL_AFU_NAME_SZ - 1] = '\0'; /* play safe */
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_afu_mmio(काष्ठा pci_dev *dev, काष्ठा ocxl_fn_config *fn,
			काष्ठा ocxl_afu_config *afu)
अणु
	पूर्णांक rc;
	u32 val;

	/*
	 * Global MMIO
	 */
	rc = पढ़ो_afu_info(dev, fn, OCXL_DVSEC_TEMPL_MMIO_GLOBAL, &val);
	अगर (rc)
		वापस rc;
	afu->global_mmio_bar = EXTRACT_BITS(val, 0, 2);
	afu->global_mmio_offset = EXTRACT_BITS(val, 16, 31) << 16;

	rc = पढ़ो_afu_info(dev, fn, OCXL_DVSEC_TEMPL_MMIO_GLOBAL + 4, &val);
	अगर (rc)
		वापस rc;
	afu->global_mmio_offset += (u64) val << 32;

	rc = पढ़ो_afu_info(dev, fn, OCXL_DVSEC_TEMPL_MMIO_GLOBAL_SZ, &val);
	अगर (rc)
		वापस rc;
	afu->global_mmio_size = val;

	/*
	 * Per-process MMIO
	 */
	rc = पढ़ो_afu_info(dev, fn, OCXL_DVSEC_TEMPL_MMIO_PP, &val);
	अगर (rc)
		वापस rc;
	afu->pp_mmio_bar = EXTRACT_BITS(val, 0, 2);
	afu->pp_mmio_offset = EXTRACT_BITS(val, 16, 31) << 16;

	rc = पढ़ो_afu_info(dev, fn, OCXL_DVSEC_TEMPL_MMIO_PP + 4, &val);
	अगर (rc)
		वापस rc;
	afu->pp_mmio_offset += (u64) val << 32;

	rc = पढ़ो_afu_info(dev, fn, OCXL_DVSEC_TEMPL_MMIO_PP_SZ, &val);
	अगर (rc)
		वापस rc;
	afu->pp_mmio_stride = val;

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_afu_control(काष्ठा pci_dev *dev, काष्ठा ocxl_afu_config *afu)
अणु
	पूर्णांक pos;
	u8 val8;
	u16 val16;

	pos = find_dvsec_afu_ctrl(dev, afu->idx);
	अगर (!pos) अणु
		dev_err(&dev->dev, "Can't find AFU control DVSEC for AFU %d\n",
			afu->idx);
		वापस -ENODEV;
	पूर्ण
	afu->dvsec_afu_control_pos = pos;

	pci_पढ़ो_config_byte(dev, pos + OCXL_DVSEC_AFU_CTRL_PASID_SUP, &val8);
	afu->pasid_supported_log = EXTRACT_BITS(val8, 0, 4);

	pci_पढ़ो_config_word(dev, pos + OCXL_DVSEC_AFU_CTRL_ACTAG_SUP, &val16);
	afu->actag_supported = EXTRACT_BITS(val16, 0, 11);
	वापस 0;
पूर्ण

अटल bool अक्षर_allowed(पूर्णांक c)
अणु
	/*
	 * Permitted Characters : Alphanumeric, hyphen, underscore, comma
	 */
	अगर ((c >= 0x30 && c <= 0x39) /* digits */ ||
		(c >= 0x41 && c <= 0x5A) /* upper हाल */ ||
		(c >= 0x61 && c <= 0x7A) /* lower हाल */ ||
		c == 0 /* शून्य */ ||
		c == 0x2D /* - */ ||
		c == 0x5F /* _ */ ||
		c == 0x2C /* , */)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक validate_afu(काष्ठा pci_dev *dev, काष्ठा ocxl_afu_config *afu)
अणु
	पूर्णांक i;

	अगर (!afu->name[0]) अणु
		dev_err(&dev->dev, "Empty AFU name\n");
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < OCXL_TEMPL_NAME_LEN; i++) अणु
		अगर (!अक्षर_allowed(afu->name[i])) अणु
			dev_err(&dev->dev,
				"Invalid character in AFU name\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (afu->global_mmio_bar != 0 &&
		afu->global_mmio_bar != 2 &&
		afu->global_mmio_bar != 4) अणु
		dev_err(&dev->dev, "Invalid global MMIO bar number\n");
		वापस -EINVAL;
	पूर्ण
	अगर (afu->pp_mmio_bar != 0 &&
		afu->pp_mmio_bar != 2 &&
		afu->pp_mmio_bar != 4) अणु
		dev_err(&dev->dev, "Invalid per-process MMIO bar number\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * पढ़ो_afu_lpc_memory_info() - Populate AFU metadata regarding LPC memory
 * @dev: the device क्रम the AFU
 * @fn: the AFU offsets
 * @afu: the AFU काष्ठा to populate the LPC metadata पूर्णांकo
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक पढ़ो_afu_lpc_memory_info(काष्ठा pci_dev *dev,
				    काष्ठा ocxl_fn_config *fn,
				    काष्ठा ocxl_afu_config *afu)
अणु
	पूर्णांक rc;
	u32 val32;
	u16 templ_version;
	u16 templ_len;
	u64 total_mem_size = 0;
	u64 lpc_mem_size = 0;

	afu->lpc_mem_offset = 0;
	afu->lpc_mem_size = 0;
	afu->special_purpose_mem_offset = 0;
	afu->special_purpose_mem_size = 0;
	/*
	 * For AFUs following ढाँचा v1.0, the LPC memory covers the
	 * total memory. Its size is a घातer of 2.
	 *
	 * For AFUs with ढाँचा >= v1.01, the total memory size is
	 * still a घातer of 2, but it is split in 2 parts:
	 * - the LPC memory, whose size can now be anything
	 * - the reमुख्यder memory is a special purpose memory, whose
	 *   definition is AFU-dependent. It is not accessible through
	 *   the usual commands क्रम LPC memory
	 */
	rc = पढ़ो_afu_info(dev, fn, OCXL_DVSEC_TEMPL_ALL_MEM_SZ, &val32);
	अगर (rc)
		वापस rc;

	val32 = EXTRACT_BITS(val32, 0, 7);
	अगर (!val32)
		वापस 0; /* No LPC memory */

	/*
	 * The configuration space spec allows क्रम a memory size of up
	 * to 2^255 bytes.
	 *
	 * Current generation hardware uses 56-bit physical addresses,
	 * but we won't be able to get near close to that, as we won't
	 * have a hole big enough in the memory map.  Let it pass in
	 * the driver क्रम now. We'll get an error from the firmware
	 * when trying to configure something too big.
	 */
	total_mem_size = 1ull << val32;

	rc = पढ़ो_afu_info(dev, fn, OCXL_DVSEC_TEMPL_LPC_MEM_START, &val32);
	अगर (rc)
		वापस rc;

	afu->lpc_mem_offset = val32;

	rc = पढ़ो_afu_info(dev, fn, OCXL_DVSEC_TEMPL_LPC_MEM_START + 4, &val32);
	अगर (rc)
		वापस rc;

	afu->lpc_mem_offset |= (u64) val32 << 32;

	rc = पढ़ो_ढाँचा_version(dev, fn, &templ_len, &templ_version);
	अगर (rc)
		वापस rc;

	अगर (templ_version >= 0x0101) अणु
		rc = पढ़ो_afu_info(dev, fn,
				OCXL_DVSEC_TEMPL_LPC_MEM_SZ, &val32);
		अगर (rc)
			वापस rc;
		lpc_mem_size = val32;

		rc = पढ़ो_afu_info(dev, fn,
				OCXL_DVSEC_TEMPL_LPC_MEM_SZ + 4, &val32);
		अगर (rc)
			वापस rc;
		lpc_mem_size |= (u64) val32 << 32;
	पूर्ण अन्यथा अणु
		lpc_mem_size = total_mem_size;
	पूर्ण
	afu->lpc_mem_size = lpc_mem_size;

	अगर (lpc_mem_size < total_mem_size) अणु
		afu->special_purpose_mem_offset =
			afu->lpc_mem_offset + lpc_mem_size;
		afu->special_purpose_mem_size =
			total_mem_size - lpc_mem_size;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ocxl_config_पढ़ो_afu(काष्ठा pci_dev *dev, काष्ठा ocxl_fn_config *fn,
			काष्ठा ocxl_afu_config *afu, u8 afu_idx)
अणु
	पूर्णांक rc;
	u32 val32;

	/*
	 * First, we need to ग_लिखो the AFU idx क्रम the AFU we want to
	 * access.
	 */
	WARN_ON((afu_idx & OCXL_DVSEC_AFU_IDX_MASK) != afu_idx);
	afu->idx = afu_idx;
	pci_ग_लिखो_config_byte(dev,
			fn->dvsec_afu_info_pos + OCXL_DVSEC_AFU_INFO_AFU_IDX,
			afu->idx);

	rc = पढ़ो_afu_name(dev, fn, afu);
	अगर (rc)
		वापस rc;

	rc = पढ़ो_afu_info(dev, fn, OCXL_DVSEC_TEMPL_AFU_VERSION, &val32);
	अगर (rc)
		वापस rc;
	afu->version_major = EXTRACT_BITS(val32, 24, 31);
	afu->version_minor = EXTRACT_BITS(val32, 16, 23);
	afu->afuc_type = EXTRACT_BITS(val32, 14, 15);
	afu->afum_type = EXTRACT_BITS(val32, 12, 13);
	afu->profile = EXTRACT_BITS(val32, 0, 7);

	rc = पढ़ो_afu_mmio(dev, fn, afu);
	अगर (rc)
		वापस rc;

	rc = पढ़ो_afu_lpc_memory_info(dev, fn, afu);
	अगर (rc)
		वापस rc;

	rc = पढ़ो_afu_control(dev, afu);
	अगर (rc)
		वापस rc;

	dev_dbg(&dev->dev, "AFU configuration:\n");
	dev_dbg(&dev->dev, "  name = %s\n", afu->name);
	dev_dbg(&dev->dev, "  version = %d.%d\n", afu->version_major,
		afu->version_minor);
	dev_dbg(&dev->dev, "  global mmio bar = %hhu\n", afu->global_mmio_bar);
	dev_dbg(&dev->dev, "  global mmio offset = %#llx\n",
		afu->global_mmio_offset);
	dev_dbg(&dev->dev, "  global mmio size = %#x\n", afu->global_mmio_size);
	dev_dbg(&dev->dev, "  pp mmio bar = %hhu\n", afu->pp_mmio_bar);
	dev_dbg(&dev->dev, "  pp mmio offset = %#llx\n", afu->pp_mmio_offset);
	dev_dbg(&dev->dev, "  pp mmio stride = %#x\n", afu->pp_mmio_stride);
	dev_dbg(&dev->dev, "  lpc_mem offset = %#llx\n", afu->lpc_mem_offset);
	dev_dbg(&dev->dev, "  lpc_mem size = %#llx\n", afu->lpc_mem_size);
	dev_dbg(&dev->dev, "  special purpose mem offset = %#llx\n",
		afu->special_purpose_mem_offset);
	dev_dbg(&dev->dev, "  special purpose mem size = %#llx\n",
		afu->special_purpose_mem_size);
	dev_dbg(&dev->dev, "  pasid supported (log) = %u\n",
		afu->pasid_supported_log);
	dev_dbg(&dev->dev, "  actag supported = %u\n",
		afu->actag_supported);

	rc = validate_afu(dev, afu);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_config_पढ़ो_afu);

पूर्णांक ocxl_config_get_actag_info(काष्ठा pci_dev *dev, u16 *base, u16 *enabled,
			u16 *supported)
अणु
	पूर्णांक rc;

	/*
	 * This is really a simple wrapper क्रम the kernel API, to
	 * aव्योम an बाह्यal driver using ocxl as a library to call
	 * platक्रमm-dependent code
	 */
	rc = pnv_ocxl_get_actag(dev, base, enabled, supported);
	अगर (rc) अणु
		dev_err(&dev->dev, "Can't get actag for device: %d\n", rc);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_config_get_actag_info);

व्योम ocxl_config_set_afu_actag(काष्ठा pci_dev *dev, पूर्णांक pos, पूर्णांक actag_base,
			पूर्णांक actag_count)
अणु
	u16 val;

	val = actag_count & OCXL_DVSEC_ACTAG_MASK;
	pci_ग_लिखो_config_byte(dev, pos + OCXL_DVSEC_AFU_CTRL_ACTAG_EN, val);

	val = actag_base & OCXL_DVSEC_ACTAG_MASK;
	pci_ग_लिखो_config_dword(dev, pos + OCXL_DVSEC_AFU_CTRL_ACTAG_BASE, val);
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_config_set_afu_actag);

पूर्णांक ocxl_config_get_pasid_info(काष्ठा pci_dev *dev, पूर्णांक *count)
अणु
	वापस pnv_ocxl_get_pasid_count(dev, count);
पूर्ण

व्योम ocxl_config_set_afu_pasid(काष्ठा pci_dev *dev, पूर्णांक pos, पूर्णांक pasid_base,
			u32 pasid_count_log)
अणु
	u8 val8;
	u32 val32;

	val8 = pasid_count_log & OCXL_DVSEC_PASID_LOG_MASK;
	pci_ग_लिखो_config_byte(dev, pos + OCXL_DVSEC_AFU_CTRL_PASID_EN, val8);

	pci_पढ़ो_config_dword(dev, pos + OCXL_DVSEC_AFU_CTRL_PASID_BASE,
			&val32);
	val32 &= ~OCXL_DVSEC_PASID_MASK;
	val32 |= pasid_base & OCXL_DVSEC_PASID_MASK;
	pci_ग_लिखो_config_dword(dev, pos + OCXL_DVSEC_AFU_CTRL_PASID_BASE,
			val32);
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_config_set_afu_pasid);

व्योम ocxl_config_set_afu_state(काष्ठा pci_dev *dev, पूर्णांक pos, पूर्णांक enable)
अणु
	u8 val;

	pci_पढ़ो_config_byte(dev, pos + OCXL_DVSEC_AFU_CTRL_ENABLE, &val);
	अगर (enable)
		val |= 1;
	अन्यथा
		val &= 0xFE;
	pci_ग_लिखो_config_byte(dev, pos + OCXL_DVSEC_AFU_CTRL_ENABLE, val);
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_config_set_afu_state);

पूर्णांक ocxl_config_set_TL(काष्ठा pci_dev *dev, पूर्णांक tl_dvsec)
अणु
	u32 val;
	__be32 *be32ptr;
	u8 समयrs;
	पूर्णांक i, rc;
	दीर्घ recv_cap;
	अक्षर *recv_rate;

	/*
	 * Skip on function != 0, as the TL can only be defined on 0
	 */
	अगर (PCI_FUNC(dev->devfn) != 0)
		वापस 0;

	recv_rate = kzalloc(PNV_OCXL_TL_RATE_BUF_SIZE, GFP_KERNEL);
	अगर (!recv_rate)
		वापस -ENOMEM;
	/*
	 * The spec defines 64 ढाँचाs क्रम messages in the
	 * Transaction Layer (TL).
	 *
	 * The host and device each support a subset, so we need to
	 * configure the transmitters on each side to send only
	 * ढाँचाs the receiver understands, at a rate the receiver
	 * can process.  Per the spec, ढाँचा 0 must be supported by
	 * everybody. That's the ढाँचा which has been used by the
	 * host and device so far.
	 *
	 * The sending rate limit must be set beक्रमe the ढाँचा is
	 * enabled.
	 */

	/*
	 * Device -> host
	 */
	rc = pnv_ocxl_get_tl_cap(dev, &recv_cap, recv_rate,
				PNV_OCXL_TL_RATE_BUF_SIZE);
	अगर (rc)
		जाओ out;

	क्रम (i = 0; i < PNV_OCXL_TL_RATE_BUF_SIZE; i += 4) अणु
		be32ptr = (__be32 *) &recv_rate[i];
		pci_ग_लिखो_config_dword(dev,
				tl_dvsec + OCXL_DVSEC_TL_SEND_RATE + i,
				be32_to_cpu(*be32ptr));
	पूर्ण
	val = recv_cap >> 32;
	pci_ग_लिखो_config_dword(dev, tl_dvsec + OCXL_DVSEC_TL_SEND_CAP, val);
	val = recv_cap & GENMASK(31, 0);
	pci_ग_लिखो_config_dword(dev, tl_dvsec + OCXL_DVSEC_TL_SEND_CAP + 4, val);

	/*
	 * Host -> device
	 */
	क्रम (i = 0; i < PNV_OCXL_TL_RATE_BUF_SIZE; i += 4) अणु
		pci_पढ़ो_config_dword(dev,
				tl_dvsec + OCXL_DVSEC_TL_RECV_RATE + i,
				&val);
		be32ptr = (__be32 *) &recv_rate[i];
		*be32ptr = cpu_to_be32(val);
	पूर्ण
	pci_पढ़ो_config_dword(dev, tl_dvsec + OCXL_DVSEC_TL_RECV_CAP, &val);
	recv_cap = (दीर्घ) val << 32;
	pci_पढ़ो_config_dword(dev, tl_dvsec + OCXL_DVSEC_TL_RECV_CAP + 4, &val);
	recv_cap |= val;

	rc = pnv_ocxl_set_tl_conf(dev, recv_cap, __pa(recv_rate),
				PNV_OCXL_TL_RATE_BUF_SIZE);
	अगर (rc)
		जाओ out;

	/*
	 * Opencapi commands needing to be retried are classअगरied per
	 * the TL in 2 groups: लघु and दीर्घ commands.
	 *
	 * The लघु back off समयr it not used क्रम now. It will be
	 * क्रम खोलोcapi 4.0.
	 *
	 * The दीर्घ back off समयr is typically used when an AFU hits
	 * a page fault but the NPU is alपढ़ोy processing one. So the
	 * AFU needs to रुको beक्रमe it can resubmit. Having a value
	 * too low करोesn't अवरोध anything, but can generate extra
	 * traffic on the link.
	 * We set it to 1.6 us क्रम now. It's लघुer than, but in the
	 * same order of magnitude as the समय spent to process a page
	 * fault.
	 */
	समयrs = 0x2 << 4; /* दीर्घ समयr = 1.6 us */
	pci_ग_लिखो_config_byte(dev, tl_dvsec + OCXL_DVSEC_TL_BACKOFF_TIMERS,
			समयrs);

	rc = 0;
out:
	kमुक्त(recv_rate);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_config_set_TL);

पूर्णांक ocxl_config_terminate_pasid(काष्ठा pci_dev *dev, पूर्णांक afu_control, पूर्णांक pasid)
अणु
	u32 val;
	अचिन्हित दीर्घ समयout;

	pci_पढ़ो_config_dword(dev, afu_control + OCXL_DVSEC_AFU_CTRL_TERM_PASID,
			&val);
	अगर (EXTRACT_BIT(val, 20)) अणु
		dev_err(&dev->dev,
			"Can't terminate PASID %#x, previous termination didn't complete\n",
			pasid);
		वापस -EBUSY;
	पूर्ण

	val &= ~OCXL_DVSEC_PASID_MASK;
	val |= pasid & OCXL_DVSEC_PASID_MASK;
	val |= BIT(20);
	pci_ग_लिखो_config_dword(dev,
			afu_control + OCXL_DVSEC_AFU_CTRL_TERM_PASID,
			val);

	समयout = jअगरfies + (HZ * OCXL_CFG_TIMEOUT);
	pci_पढ़ो_config_dword(dev, afu_control + OCXL_DVSEC_AFU_CTRL_TERM_PASID,
			&val);
	जबतक (EXTRACT_BIT(val, 20)) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			dev_err(&dev->dev,
				"Timeout while waiting for AFU to terminate PASID %#x\n",
				pasid);
			वापस -EBUSY;
		पूर्ण
		cpu_relax();
		pci_पढ़ो_config_dword(dev,
				afu_control + OCXL_DVSEC_AFU_CTRL_TERM_PASID,
				&val);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_config_terminate_pasid);

व्योम ocxl_config_set_actag(काष्ठा pci_dev *dev, पूर्णांक func_dvsec, u32 tag_first,
			u32 tag_count)
अणु
	u32 val;

	val = (tag_first & OCXL_DVSEC_ACTAG_MASK) << 16;
	val |= tag_count & OCXL_DVSEC_ACTAG_MASK;
	pci_ग_लिखो_config_dword(dev, func_dvsec + OCXL_DVSEC_FUNC_OFF_ACTAG,
			val);
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_config_set_actag);
