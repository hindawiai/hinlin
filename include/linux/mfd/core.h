<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * drivers/mfd/mfd-core.h
 *
 * core MFD support
 * Copyright (c) 2006 Ian Molton
 * Copyright (c) 2007 Dmitry Baryshkov
 */

#अगर_अघोषित MFD_CORE_H
#घोषणा MFD_CORE_H

#समावेश <linux/platक्रमm_device.h>

#घोषणा MFD_RES_SIZE(arr) (माप(arr) / माप(काष्ठा resource))

#घोषणा MFD_CELL_ALL(_name, _res, _pdata, _pdsize, _id, _compat, _of_reg, _use_of_reg, _match) \
	अणु								\
		.name = (_name),					\
		.resources = (_res),					\
		.num_resources = MFD_RES_SIZE((_res)),			\
		.platक्रमm_data = (_pdata),				\
		.pdata_size = (_pdsize),				\
		.of_compatible = (_compat),				\
		.of_reg = (_of_reg),					\
		.use_of_reg = (_use_of_reg),				\
		.acpi_match = (_match),					\
		.id = (_id),						\
	पूर्ण

#घोषणा MFD_CELL_OF_REG(_name, _res, _pdata, _pdsize, _id, _compat, _of_reg) \
	MFD_CELL_ALL(_name, _res, _pdata, _pdsize, _id, _compat, _of_reg, true, शून्य)

#घोषणा MFD_CELL_OF(_name, _res, _pdata, _pdsize, _id, _compat) \
	MFD_CELL_ALL(_name, _res, _pdata, _pdsize, _id, _compat, 0, false, शून्य)

#घोषणा MFD_CELL_ACPI(_name, _res, _pdata, _pdsize, _id, _match) \
	MFD_CELL_ALL(_name, _res, _pdata, _pdsize, _id, शून्य, 0, false, _match)

#घोषणा MFD_CELL_BASIC(_name, _res, _pdata, _pdsize, _id) \
	MFD_CELL_ALL(_name, _res, _pdata, _pdsize, _id, शून्य, 0, false, शून्य)

#घोषणा MFD_CELL_RES(_name, _res) \
	MFD_CELL_ALL(_name, _res, शून्य, 0, 0, शून्य, 0, false, शून्य)

#घोषणा MFD_CELL_NAME(_name) \
	MFD_CELL_ALL(_name, शून्य, शून्य, 0, 0, शून्य, 0, false, शून्य)

#घोषणा MFD_DEP_LEVEL_NORMAL 0
#घोषणा MFD_DEP_LEVEL_HIGH 1

काष्ठा irq_करोमुख्य;
काष्ठा software_node;

/* Matches ACPI PNP id, either _HID or _CID, or ACPI _ADR */
काष्ठा mfd_cell_acpi_match अणु
	स्थिर अक्षर			*pnpid;
	स्थिर अचिन्हित दीर्घ दीर्घ	adr;
पूर्ण;

/*
 * This काष्ठा describes the MFD part ("cell").
 * After registration the copy of this काष्ठाure will become the platक्रमm data
 * of the resulting platक्रमm_device
 */
काष्ठा mfd_cell अणु
	स्थिर अक्षर		*name;
	पूर्णांक			id;
	पूर्णांक			level;

	पूर्णांक			(*enable)(काष्ठा platक्रमm_device *dev);
	पूर्णांक			(*disable)(काष्ठा platक्रमm_device *dev);

	पूर्णांक			(*suspend)(काष्ठा platक्रमm_device *dev);
	पूर्णांक			(*resume)(काष्ठा platक्रमm_device *dev);

	/* platक्रमm data passed to the sub devices drivers */
	व्योम			*platक्रमm_data;
	माप_प्रकार			pdata_size;

	/* Software node क्रम the device. */
	स्थिर काष्ठा software_node *swnode;

	/*
	 * Device Tree compatible string
	 * See: Documentation/devicetree/usage-model.rst Chapter 2.2 क्रम details
	 */
	स्थिर अक्षर		*of_compatible;

	/*
	 * Address as defined in Device Tree.  Used to compement 'of_compatible'
	 * (above) when matching OF nodes with devices that have identical
	 * compatible strings
	 */
	स्थिर u64 of_reg;

	/* Set to 'true' to use 'of_reg' (above) - allows क्रम of_reg=0 */
	bool use_of_reg;

	/* Matches ACPI */
	स्थिर काष्ठा mfd_cell_acpi_match	*acpi_match;

	/*
	 * These resources can be specअगरied relative to the parent device.
	 * For accessing hardware you should use resources from the platक्रमm dev
	 */
	पूर्णांक			num_resources;
	स्थिर काष्ठा resource	*resources;

	/* करोn't check क्रम resource conflicts */
	bool			ignore_resource_conflicts;

	/*
	 * Disable runसमय PM callbacks क्रम this subdevice - see
	 * pm_runसमय_no_callbacks().
	 */
	bool			pm_runसमय_no_callbacks;

	/* A list of regulator supplies that should be mapped to the MFD
	 * device rather than the child device when requested
	 */
	स्थिर अक्षर * स्थिर	*parent_supplies;
	पूर्णांक			num_parent_supplies;
पूर्ण;

/*
 * Convenience functions क्रम clients using shared cells.  Refcounting
 * happens स्वतःmatically, with the cell's enable/disable callbacks
 * being called only when a device is first being enabled or no other
 * clients are making use of it.
 */
बाह्य पूर्णांक mfd_cell_enable(काष्ठा platक्रमm_device *pdev);
बाह्य पूर्णांक mfd_cell_disable(काष्ठा platक्रमm_device *pdev);

/*
 * Given a platक्रमm device that's been created by mfd_add_devices(), fetch
 * the mfd_cell that created it.
 */
अटल अंतरभूत स्थिर काष्ठा mfd_cell *mfd_get_cell(काष्ठा platक्रमm_device *pdev)
अणु
	वापस pdev->mfd_cell;
पूर्ण

बाह्य पूर्णांक mfd_add_devices(काष्ठा device *parent, पूर्णांक id,
			   स्थिर काष्ठा mfd_cell *cells, पूर्णांक n_devs,
			   काष्ठा resource *mem_base,
			   पूर्णांक irq_base, काष्ठा irq_करोमुख्य *irq_करोमुख्य);

अटल अंतरभूत पूर्णांक mfd_add_hotplug_devices(काष्ठा device *parent,
		स्थिर काष्ठा mfd_cell *cells, पूर्णांक n_devs)
अणु
	वापस mfd_add_devices(parent, PLATFORM_DEVID_AUTO, cells, n_devs,
			शून्य, 0, शून्य);
पूर्ण

बाह्य व्योम mfd_हटाओ_devices(काष्ठा device *parent);
बाह्य व्योम mfd_हटाओ_devices_late(काष्ठा device *parent);

बाह्य पूर्णांक devm_mfd_add_devices(काष्ठा device *dev, पूर्णांक id,
				स्थिर काष्ठा mfd_cell *cells, पूर्णांक n_devs,
				काष्ठा resource *mem_base,
				पूर्णांक irq_base, काष्ठा irq_करोमुख्य *irq_करोमुख्य);
#पूर्ण_अगर
