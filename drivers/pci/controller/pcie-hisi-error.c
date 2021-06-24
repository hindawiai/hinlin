<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम handling the PCIe controller errors on
 * HiSilicon HIP SoCs.
 *
 * Copyright (c) 2020 HiSilicon Limited.
 */

#समावेश <linux/acpi.h>
#समावेश <acpi/ghes.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/spinlock.h>

/* HISI PCIe controller error definitions */
#घोषणा HISI_PCIE_ERR_MISC_REGS	33

#घोषणा HISI_PCIE_LOCAL_VALID_VERSION		BIT(0)
#घोषणा HISI_PCIE_LOCAL_VALID_SOC_ID		BIT(1)
#घोषणा HISI_PCIE_LOCAL_VALID_SOCKET_ID		BIT(2)
#घोषणा HISI_PCIE_LOCAL_VALID_NIMBUS_ID		BIT(3)
#घोषणा HISI_PCIE_LOCAL_VALID_SUB_MODULE_ID	BIT(4)
#घोषणा HISI_PCIE_LOCAL_VALID_CORE_ID		BIT(5)
#घोषणा HISI_PCIE_LOCAL_VALID_PORT_ID		BIT(6)
#घोषणा HISI_PCIE_LOCAL_VALID_ERR_TYPE		BIT(7)
#घोषणा HISI_PCIE_LOCAL_VALID_ERR_SEVERITY	BIT(8)
#घोषणा HISI_PCIE_LOCAL_VALID_ERR_MISC		9

अटल guid_t hisi_pcie_sec_guid =
	GUID_INIT(0xB2889FC9, 0xE7D7, 0x4F9D,
		  0xA8, 0x67, 0xAF, 0x42, 0xE9, 0x8B, 0xE7, 0x72);

/*
 * Firmware reports the socket port ID where the error occurred.  These
 * macros convert that to the core ID and core port ID required by the
 * ACPI reset method.
 */
#घोषणा HISI_PCIE_PORT_ID(core, v)       (((v) >> 1) + ((core) << 3))
#घोषणा HISI_PCIE_CORE_ID(v)             ((v) >> 3)
#घोषणा HISI_PCIE_CORE_PORT_ID(v)        (((v) & 7) << 1)

काष्ठा hisi_pcie_error_data अणु
	u64	val_bits;
	u8	version;
	u8	soc_id;
	u8	socket_id;
	u8	nimbus_id;
	u8	sub_module_id;
	u8	core_id;
	u8	port_id;
	u8	err_severity;
	u16	err_type;
	u8	reserv[2];
	u32	err_misc[HISI_PCIE_ERR_MISC_REGS];
पूर्ण;

काष्ठा hisi_pcie_error_निजी अणु
	काष्ठा notअगरier_block	nb;
	काष्ठा device *dev;
पूर्ण;

क्रमागत hisi_pcie_submodule_id अणु
	HISI_PCIE_SUB_MODULE_ID_AP,
	HISI_PCIE_SUB_MODULE_ID_TL,
	HISI_PCIE_SUB_MODULE_ID_MAC,
	HISI_PCIE_SUB_MODULE_ID_DL,
	HISI_PCIE_SUB_MODULE_ID_SDI,
पूर्ण;

अटल स्थिर अक्षर * स्थिर hisi_pcie_sub_module[] = अणु
	[HISI_PCIE_SUB_MODULE_ID_AP]	= "AP Layer",
	[HISI_PCIE_SUB_MODULE_ID_TL]	= "TL Layer",
	[HISI_PCIE_SUB_MODULE_ID_MAC]	= "MAC Layer",
	[HISI_PCIE_SUB_MODULE_ID_DL]	= "DL Layer",
	[HISI_PCIE_SUB_MODULE_ID_SDI]	= "SDI Layer",
पूर्ण;

क्रमागत hisi_pcie_err_severity अणु
	HISI_PCIE_ERR_SEV_RECOVERABLE,
	HISI_PCIE_ERR_SEV_FATAL,
	HISI_PCIE_ERR_SEV_CORRECTED,
	HISI_PCIE_ERR_SEV_NONE,
पूर्ण;

अटल स्थिर अक्षर * स्थिर hisi_pcie_error_sev[] = अणु
	[HISI_PCIE_ERR_SEV_RECOVERABLE]	= "recoverable",
	[HISI_PCIE_ERR_SEV_FATAL]	= "fatal",
	[HISI_PCIE_ERR_SEV_CORRECTED]	= "corrected",
	[HISI_PCIE_ERR_SEV_NONE]	= "none",
पूर्ण;

अटल स्थिर अक्षर *hisi_pcie_get_string(स्थिर अक्षर * स्थिर *array,
					माप_प्रकार n, u32 id)
अणु
	u32 index;

	क्रम (index = 0; index < n; index++) अणु
		अगर (index == id && array[index])
			वापस array[index];
	पूर्ण

	वापस "unknown";
पूर्ण

अटल पूर्णांक hisi_pcie_port_reset(काष्ठा platक्रमm_device *pdev,
				u32 chip_id, u32 port_id)
अणु
	काष्ठा device *dev = &pdev->dev;
	acpi_handle handle = ACPI_HANDLE(dev);
	जोड़ acpi_object arg[3];
	काष्ठा acpi_object_list arg_list;
	acpi_status s;
	अचिन्हित दीर्घ दीर्घ data = 0;

	arg[0].type = ACPI_TYPE_INTEGER;
	arg[0].पूर्णांकeger.value = chip_id;
	arg[1].type = ACPI_TYPE_INTEGER;
	arg[1].पूर्णांकeger.value = HISI_PCIE_CORE_ID(port_id);
	arg[2].type = ACPI_TYPE_INTEGER;
	arg[2].पूर्णांकeger.value = HISI_PCIE_CORE_PORT_ID(port_id);

	arg_list.count = 3;
	arg_list.poपूर्णांकer = arg;

	s = acpi_evaluate_पूर्णांकeger(handle, "RST", &arg_list, &data);
	अगर (ACPI_FAILURE(s)) अणु
		dev_err(dev, "No RST method\n");
		वापस -EIO;
	पूर्ण

	अगर (data) अणु
		dev_err(dev, "Failed to Reset\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_pcie_port_करो_recovery(काष्ठा platक्रमm_device *dev,
				      u32 chip_id, u32 port_id)
अणु
	acpi_status s;
	काष्ठा device *device = &dev->dev;
	acpi_handle root_handle = ACPI_HANDLE(device);
	काष्ठा acpi_pci_root *pci_root;
	काष्ठा pci_bus *root_bus;
	काष्ठा pci_dev *pdev;
	u32 करोमुख्य, busnr, devfn;

	s = acpi_get_parent(root_handle, &root_handle);
	अगर (ACPI_FAILURE(s))
		वापस -ENODEV;
	pci_root = acpi_pci_find_root(root_handle);
	अगर (!pci_root)
		वापस -ENODEV;
	root_bus = pci_root->bus;
	करोमुख्य = pci_root->segment;

	busnr = root_bus->number;
	devfn = PCI_DEVFN(port_id, 0);
	pdev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, busnr, devfn);
	अगर (!pdev) अणु
		dev_info(device, "Fail to get root port %04x:%02x:%02x.%d device\n",
			 करोमुख्य, busnr, PCI_SLOT(devfn), PCI_FUNC(devfn));
		वापस -ENODEV;
	पूर्ण

	pci_stop_and_हटाओ_bus_device_locked(pdev);
	pci_dev_put(pdev);

	अगर (hisi_pcie_port_reset(dev, chip_id, port_id))
		वापस -EIO;

	/*
	 * The initialization समय of subordinate devices after
	 * hot reset is no more than 1s, which is required by
	 * the PCI spec v5.0 sec 6.6.1. The समय will लघुen
	 * अगर Readiness Notअगरications mechanisms are used. But
	 * रुको 1s here to adapt any conditions.
	 */
	ssleep(1UL);

	/* add root port and करोwnstream devices */
	pci_lock_rescan_हटाओ();
	pci_rescan_bus(root_bus);
	pci_unlock_rescan_हटाओ();

	वापस 0;
पूर्ण

अटल व्योम hisi_pcie_handle_error(काष्ठा platक्रमm_device *pdev,
				   स्थिर काष्ठा hisi_pcie_error_data *edata)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक idx, rc;
	स्थिर अचिन्हित दीर्घ valid_bits[] = अणुBITMAP_FROM_U64(edata->val_bits)पूर्ण;

	अगर (edata->val_bits == 0) अणु
		dev_warn(dev, "%s: no valid error information\n", __func__);
		वापस;
	पूर्ण

	dev_info(dev, "\nHISI : HIP : PCIe controller error\n");
	अगर (edata->val_bits & HISI_PCIE_LOCAL_VALID_SOC_ID)
		dev_info(dev, "Table version = %d\n", edata->version);
	अगर (edata->val_bits & HISI_PCIE_LOCAL_VALID_SOCKET_ID)
		dev_info(dev, "Socket ID = %d\n", edata->socket_id);
	अगर (edata->val_bits & HISI_PCIE_LOCAL_VALID_NIMBUS_ID)
		dev_info(dev, "Nimbus ID = %d\n", edata->nimbus_id);
	अगर (edata->val_bits & HISI_PCIE_LOCAL_VALID_SUB_MODULE_ID)
		dev_info(dev, "Sub Module = %s\n",
			 hisi_pcie_get_string(hisi_pcie_sub_module,
					      ARRAY_SIZE(hisi_pcie_sub_module),
					      edata->sub_module_id));
	अगर (edata->val_bits & HISI_PCIE_LOCAL_VALID_CORE_ID)
		dev_info(dev, "Core ID = core%d\n", edata->core_id);
	अगर (edata->val_bits & HISI_PCIE_LOCAL_VALID_PORT_ID)
		dev_info(dev, "Port ID = port%d\n", edata->port_id);
	अगर (edata->val_bits & HISI_PCIE_LOCAL_VALID_ERR_SEVERITY)
		dev_info(dev, "Error severity = %s\n",
			 hisi_pcie_get_string(hisi_pcie_error_sev,
					      ARRAY_SIZE(hisi_pcie_error_sev),
					      edata->err_severity));
	अगर (edata->val_bits & HISI_PCIE_LOCAL_VALID_ERR_TYPE)
		dev_info(dev, "Error type = 0x%x\n", edata->err_type);

	dev_info(dev, "Reg Dump:\n");
	idx = HISI_PCIE_LOCAL_VALID_ERR_MISC;
	क्रम_each_set_bit_from(idx, valid_bits,
			      HISI_PCIE_LOCAL_VALID_ERR_MISC + HISI_PCIE_ERR_MISC_REGS)
		dev_info(dev, "ERR_MISC_%d = 0x%x\n", idx - HISI_PCIE_LOCAL_VALID_ERR_MISC,
			 edata->err_misc[idx - HISI_PCIE_LOCAL_VALID_ERR_MISC]);

	अगर (edata->err_severity != HISI_PCIE_ERR_SEV_RECOVERABLE)
		वापस;

	/* Recovery क्रम the PCIe controller errors, try reset
	 * PCI port क्रम the error recovery
	 */
	rc = hisi_pcie_port_करो_recovery(pdev, edata->socket_id,
			HISI_PCIE_PORT_ID(edata->core_id, edata->port_id));
	अगर (rc)
		dev_info(dev, "fail to do hisi pcie port reset\n");
पूर्ण

अटल पूर्णांक hisi_pcie_notअगरy_error(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा acpi_hest_generic_data *gdata = data;
	स्थिर काष्ठा hisi_pcie_error_data *error_data = acpi_hest_get_payload(gdata);
	काष्ठा hisi_pcie_error_निजी *priv;
	काष्ठा device *dev;
	काष्ठा platक्रमm_device *pdev;
	guid_t err_sec_guid;
	u8 socket;

	import_guid(&err_sec_guid, gdata->section_type);
	अगर (!guid_equal(&err_sec_guid, &hisi_pcie_sec_guid))
		वापस NOTIFY_DONE;

	priv = container_of(nb, काष्ठा hisi_pcie_error_निजी, nb);
	dev = priv->dev;

	अगर (device_property_पढ़ो_u8(dev, "socket", &socket))
		वापस NOTIFY_DONE;

	अगर (error_data->socket_id != socket)
		वापस NOTIFY_DONE;

	pdev = container_of(dev, काष्ठा platक्रमm_device, dev);
	hisi_pcie_handle_error(pdev, error_data);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक hisi_pcie_error_handler_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_pcie_error_निजी *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->nb.notअगरier_call = hisi_pcie_notअगरy_error;
	priv->dev = &pdev->dev;
	ret = ghes_रेजिस्टर_venकरोr_record_notअगरier(&priv->nb);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Failed to register hisi pcie controller error handler with apei\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_pcie_error_handler_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_pcie_error_निजी *priv = platक्रमm_get_drvdata(pdev);

	ghes_unरेजिस्टर_venकरोr_record_notअगरier(&priv->nb);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hisi_pcie_acpi_match[] = अणु
	अणु "HISI0361", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver hisi_pcie_error_handler_driver = अणु
	.driver = अणु
		.name	= "hisi-pcie-error-handler",
		.acpi_match_table = hisi_pcie_acpi_match,
	पूर्ण,
	.probe		= hisi_pcie_error_handler_probe,
	.हटाओ		= hisi_pcie_error_handler_हटाओ,
पूर्ण;
module_platक्रमm_driver(hisi_pcie_error_handler_driver);

MODULE_DESCRIPTION("HiSilicon HIP PCIe controller error handling driver");
MODULE_LICENSE("GPL v2");
