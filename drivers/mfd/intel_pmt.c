<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Platक्रमm Monitoring Technology PMT driver
 *
 * Copyright (c) 2020, Intel Corporation.
 * All Rights Reserved.
 *
 * Author: David E. Box <david.e.box@linux.पूर्णांकel.com>
 */

#समावेश <linux/bits.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/types.h>

/* Intel DVSEC capability venकरोr space offsets */
#घोषणा INTEL_DVSEC_ENTRIES		0xA
#घोषणा INTEL_DVSEC_SIZE		0xB
#घोषणा INTEL_DVSEC_TABLE		0xC
#घोषणा INTEL_DVSEC_TABLE_BAR(x)	((x) & GENMASK(2, 0))
#घोषणा INTEL_DVSEC_TABLE_OFFSET(x)	((x) & GENMASK(31, 3))
#घोषणा INTEL_DVSEC_ENTRY_SIZE		4

/* PMT capabilities */
#घोषणा DVSEC_INTEL_ID_TELEMETRY	2
#घोषणा DVSEC_INTEL_ID_WATCHER		3
#घोषणा DVSEC_INTEL_ID_CRASHLOG		4

काष्ठा पूर्णांकel_dvsec_header अणु
	u16	length;
	u16	id;
	u8	num_entries;
	u8	entry_size;
	u8	tbir;
	u32	offset;
पूर्ण;

क्रमागत pmt_quirks अणु
	/* Watcher capability not supported */
	PMT_QUIRK_NO_WATCHER	= BIT(0),

	/* Crashlog capability not supported */
	PMT_QUIRK_NO_CRASHLOG	= BIT(1),

	/* Use shअगरt instead of mask to पढ़ो discovery table offset */
	PMT_QUIRK_TABLE_SHIFT	= BIT(2),

	/* DVSEC not present (provided in driver data) */
	PMT_QUIRK_NO_DVSEC	= BIT(3),
पूर्ण;

काष्ठा pmt_platक्रमm_info अणु
	अचिन्हित दीर्घ quirks;
	काष्ठा पूर्णांकel_dvsec_header **capabilities;
पूर्ण;

अटल स्थिर काष्ठा pmt_platक्रमm_info tgl_info = अणु
	.quirks = PMT_QUIRK_NO_WATCHER | PMT_QUIRK_NO_CRASHLOG |
		  PMT_QUIRK_TABLE_SHIFT,
पूर्ण;

/* DG1 Platक्रमm with DVSEC quirk*/
अटल काष्ठा पूर्णांकel_dvsec_header dg1_telemetry = अणु
	.length = 0x10,
	.id = 2,
	.num_entries = 1,
	.entry_size = 3,
	.tbir = 0,
	.offset = 0x466000,
पूर्ण;

अटल काष्ठा पूर्णांकel_dvsec_header *dg1_capabilities[] = अणु
	&dg1_telemetry,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा pmt_platक्रमm_info dg1_info = अणु
	.quirks = PMT_QUIRK_NO_DVSEC,
	.capabilities = dg1_capabilities,
पूर्ण;

अटल पूर्णांक pmt_add_dev(काष्ठा pci_dev *pdev, काष्ठा पूर्णांकel_dvsec_header *header,
		       अचिन्हित दीर्घ quirks)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res, *पंचांगp;
	काष्ठा mfd_cell *cell;
	स्थिर अक्षर *name;
	पूर्णांक count = header->num_entries;
	पूर्णांक size = header->entry_size;
	पूर्णांक id = header->id;
	पूर्णांक i;

	चयन (id) अणु
	हाल DVSEC_INTEL_ID_TELEMETRY:
		name = "pmt_telemetry";
		अवरोध;
	हाल DVSEC_INTEL_ID_WATCHER:
		अगर (quirks & PMT_QUIRK_NO_WATCHER) अणु
			dev_info(dev, "Watcher not supported\n");
			वापस -EINVAL;
		पूर्ण
		name = "pmt_watcher";
		अवरोध;
	हाल DVSEC_INTEL_ID_CRASHLOG:
		अगर (quirks & PMT_QUIRK_NO_CRASHLOG) अणु
			dev_info(dev, "Crashlog not supported\n");
			वापस -EINVAL;
		पूर्ण
		name = "pmt_crashlog";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!header->num_entries || !header->entry_size) अणु
		dev_err(dev, "Invalid count or size for %s header\n", name);
		वापस -EINVAL;
	पूर्ण

	cell = devm_kzalloc(dev, माप(*cell), GFP_KERNEL);
	अगर (!cell)
		वापस -ENOMEM;

	res = devm_kसुस्मृति(dev, count, माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस -ENOMEM;

	अगर (quirks & PMT_QUIRK_TABLE_SHIFT)
		header->offset >>= 3;

	/*
	 * The PMT DVSEC contains the starting offset and count क्रम a block of
	 * discovery tables, each providing access to monitoring facilities क्रम
	 * a section of the device. Create a resource list of these tables to
	 * provide to the driver.
	 */
	क्रम (i = 0, पंचांगp = res; i < count; i++, पंचांगp++) अणु
		पंचांगp->start = pdev->resource[header->tbir].start +
			     header->offset + i * (size << 2);
		पंचांगp->end = पंचांगp->start + (size << 2) - 1;
		पंचांगp->flags = IORESOURCE_MEM;
	पूर्ण

	cell->resources = res;
	cell->num_resources = count;
	cell->name = name;

	वापस devm_mfd_add_devices(dev, PLATFORM_DEVID_AUTO, cell, 1, शून्य, 0,
				    शून्य);
पूर्ण

अटल पूर्णांक pmt_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा pmt_platक्रमm_info *info;
	अचिन्हित दीर्घ quirks = 0;
	bool found_devices = false;
	पूर्णांक ret, pos = 0;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	info = (काष्ठा pmt_platक्रमm_info *)id->driver_data;

	अगर (info)
		quirks = info->quirks;

	अगर (info && (info->quirks & PMT_QUIRK_NO_DVSEC)) अणु
		काष्ठा पूर्णांकel_dvsec_header **header;

		header = info->capabilities;
		जबतक (*header) अणु
			ret = pmt_add_dev(pdev, *header, quirks);
			अगर (ret)
				dev_warn(&pdev->dev,
					 "Failed to add device for DVSEC id %d\n",
					 (*header)->id);
			अन्यथा
				found_devices = true;

			++header;
		पूर्ण
	पूर्ण अन्यथा अणु
		करो अणु
			काष्ठा पूर्णांकel_dvsec_header header;
			u32 table;
			u16 vid;

			pos = pci_find_next_ext_capability(pdev, pos, PCI_EXT_CAP_ID_DVSEC);
			अगर (!pos)
				अवरोध;

			pci_पढ़ो_config_word(pdev, pos + PCI_DVSEC_HEADER1, &vid);
			अगर (vid != PCI_VENDOR_ID_INTEL)
				जारी;

			pci_पढ़ो_config_word(pdev, pos + PCI_DVSEC_HEADER2,
					     &header.id);
			pci_पढ़ो_config_byte(pdev, pos + INTEL_DVSEC_ENTRIES,
					     &header.num_entries);
			pci_पढ़ो_config_byte(pdev, pos + INTEL_DVSEC_SIZE,
					     &header.entry_size);
			pci_पढ़ो_config_dword(pdev, pos + INTEL_DVSEC_TABLE,
					      &table);

			header.tbir = INTEL_DVSEC_TABLE_BAR(table);
			header.offset = INTEL_DVSEC_TABLE_OFFSET(table);

			ret = pmt_add_dev(pdev, &header, quirks);
			अगर (ret)
				जारी;

			found_devices = true;
		पूर्ण जबतक (true);
	पूर्ण

	अगर (!found_devices)
		वापस -ENODEV;

	pm_runसमय_put(&pdev->dev);
	pm_runसमय_allow(&pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम pmt_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	pm_runसमय_क्रमbid(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);
पूर्ण

#घोषणा PCI_DEVICE_ID_INTEL_PMT_ADL	0x467d
#घोषणा PCI_DEVICE_ID_INTEL_PMT_DG1	0x490e
#घोषणा PCI_DEVICE_ID_INTEL_PMT_OOBMSM	0x09a7
#घोषणा PCI_DEVICE_ID_INTEL_PMT_TGL	0x9a0d
अटल स्थिर काष्ठा pci_device_id pmt_pci_ids[] = अणु
	अणु PCI_DEVICE_DATA(INTEL, PMT_ADL, &tgl_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, PMT_DG1, &dg1_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, PMT_OOBMSM, शून्य) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, PMT_TGL, &tgl_info) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pmt_pci_ids);

अटल काष्ठा pci_driver pmt_pci_driver = अणु
	.name = "intel-pmt",
	.id_table = pmt_pci_ids,
	.probe = pmt_pci_probe,
	.हटाओ = pmt_pci_हटाओ,
पूर्ण;
module_pci_driver(pmt_pci_driver);

MODULE_AUTHOR("David E. Box <david.e.box@linux.intel.com>");
MODULE_DESCRIPTION("Intel Platform Monitoring Technology PMT driver");
MODULE_LICENSE("GPL v2");
