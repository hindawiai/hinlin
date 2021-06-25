<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Error Disconnect Recover support
 * Author: Kuppuswamy Sathyanarayanan <sathyanarayanan.kuppuswamy@linux.पूर्णांकel.com>
 *
 * Copyright (C) 2020 Intel Corp.
 */

#घोषणा dev_fmt(fmt) "EDR: " fmt

#समावेश <linux/pci.h>
#समावेश <linux/pci-acpi.h>

#समावेश "portdrv.h"
#समावेश "../pci.h"

#घोषणा EDR_PORT_DPC_ENABLE_DSM		0x0C
#घोषणा EDR_PORT_LOCATE_DSM		0x0D
#घोषणा EDR_OST_SUCCESS			0x80
#घोषणा EDR_OST_FAILED			0x81

/*
 * _DSM wrapper function to enable/disable DPC
 * @pdev   : PCI device काष्ठाure
 *
 * वापसs 0 on success or त्रुटि_सं on failure.
 */
अटल पूर्णांक acpi_enable_dpc(काष्ठा pci_dev *pdev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	जोड़ acpi_object *obj, argv4, req;
	पूर्णांक status = 0;

	/*
	 * Behavior when calling unsupported _DSM functions is undefined,
	 * so check whether EDR_PORT_DPC_ENABLE_DSM is supported.
	 */
	अगर (!acpi_check_dsm(adev->handle, &pci_acpi_dsm_guid, 5,
			    1ULL << EDR_PORT_DPC_ENABLE_DSM))
		वापस 0;

	req.type = ACPI_TYPE_INTEGER;
	req.पूर्णांकeger.value = 1;

	argv4.type = ACPI_TYPE_PACKAGE;
	argv4.package.count = 1;
	argv4.package.elements = &req;

	/*
	 * Per Downstream Port Containment Related Enhancements ECN to PCI
	 * Firmware Specअगरication r3.2, sec 4.6.12, EDR_PORT_DPC_ENABLE_DSM is
	 * optional.  Return success अगर it's not implemented.
	 */
	obj = acpi_evaluate_dsm(adev->handle, &pci_acpi_dsm_guid, 5,
				EDR_PORT_DPC_ENABLE_DSM, &argv4);
	अगर (!obj)
		वापस 0;

	अगर (obj->type != ACPI_TYPE_INTEGER) अणु
		pci_err(pdev, FW_BUG "Enable DPC _DSM returned non integer\n");
		status = -EIO;
	पूर्ण

	अगर (obj->पूर्णांकeger.value != 1) अणु
		pci_err(pdev, "Enable DPC _DSM failed to enable DPC\n");
		status = -EIO;
	पूर्ण

	ACPI_FREE(obj);

	वापस status;
पूर्ण

/*
 * _DSM wrapper function to locate DPC port
 * @pdev   : Device which received EDR event
 *
 * Returns pci_dev or शून्य.  Caller is responsible क्रम dropping a reference
 * on the वापसed pci_dev with pci_dev_put().
 */
अटल काष्ठा pci_dev *acpi_dpc_port_get(काष्ठा pci_dev *pdev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	जोड़ acpi_object *obj;
	u16 port;

	/*
	 * Behavior when calling unsupported _DSM functions is undefined,
	 * so check whether EDR_PORT_DPC_ENABLE_DSM is supported.
	 */
	अगर (!acpi_check_dsm(adev->handle, &pci_acpi_dsm_guid, 5,
			    1ULL << EDR_PORT_LOCATE_DSM))
		वापस pci_dev_get(pdev);

	obj = acpi_evaluate_dsm(adev->handle, &pci_acpi_dsm_guid, 5,
				EDR_PORT_LOCATE_DSM, शून्य);
	अगर (!obj)
		वापस pci_dev_get(pdev);

	अगर (obj->type != ACPI_TYPE_INTEGER) अणु
		ACPI_FREE(obj);
		pci_err(pdev, FW_BUG "Locate Port _DSM returned non integer\n");
		वापस शून्य;
	पूर्ण

	/*
	 * Firmware वापसs DPC port BDF details in following क्रमmat:
	 *	15:8 = bus
	 *	 7:3 = device
	 *	 2:0 = function
	 */
	port = obj->पूर्णांकeger.value;

	ACPI_FREE(obj);

	वापस pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(pdev->bus),
					   PCI_BUS_NUM(port), port & 0xff);
पूर्ण

/*
 * _OST wrapper function to let firmware know the status of EDR event
 * @pdev   : Device used to send _OST
 * @edev   : Device which experienced EDR event
 * @status : Status of EDR event
 */
अटल पूर्णांक acpi_send_edr_status(काष्ठा pci_dev *pdev, काष्ठा pci_dev *edev,
				u16 status)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	u32 ost_status;

	pci_dbg(pdev, "Status for %s: %#x\n", pci_name(edev), status);

	ost_status = PCI_DEVID(edev->bus->number, edev->devfn) << 16;
	ost_status |= status;

	status = acpi_evaluate_ost(adev->handle, ACPI_NOTIFY_DISCONNECT_RECOVER,
				   ost_status, शून्य);
	अगर (ACPI_FAILURE(status))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम edr_handle_event(acpi_handle handle, u32 event, व्योम *data)
अणु
	काष्ठा pci_dev *pdev = data, *edev;
	pci_ers_result_t estate = PCI_ERS_RESULT_DISCONNECT;
	u16 status;

	अगर (event != ACPI_NOTIFY_DISCONNECT_RECOVER)
		वापस;

	pci_info(pdev, "EDR event received\n");

	/* Locate the port which issued EDR event */
	edev = acpi_dpc_port_get(pdev);
	अगर (!edev) अणु
		pci_err(pdev, "Firmware failed to locate DPC port\n");
		वापस;
	पूर्ण

	pci_dbg(pdev, "Reported EDR dev: %s\n", pci_name(edev));

	/* If port करोes not support DPC, just send the OST */
	अगर (!edev->dpc_cap) अणु
		pci_err(edev, FW_BUG "This device doesn't support DPC\n");
		जाओ send_ost;
	पूर्ण

	/* Check अगर there is a valid DPC trigger */
	pci_पढ़ो_config_word(edev, edev->dpc_cap + PCI_EXP_DPC_STATUS, &status);
	अगर (!(status & PCI_EXP_DPC_STATUS_TRIGGER)) अणु
		pci_err(edev, "Invalid DPC trigger %#010x\n", status);
		जाओ send_ost;
	पूर्ण

	dpc_process_error(edev);
	pci_aer_raw_clear_status(edev);

	/*
	 * Irrespective of whether the DPC event is triggered by ERR_FATAL
	 * or ERR_NONFATAL, since the link is alपढ़ोy करोwn, use the FATAL
	 * error recovery path क्रम both हालs.
	 */
	estate = pcie_करो_recovery(edev, pci_channel_io_frozen, dpc_reset_link);

send_ost:

	/*
	 * If recovery is successful, send _OST(0xF, BDF << 16 | 0x80)
	 * to firmware. If not successful, send _OST(0xF, BDF << 16 | 0x81).
	 */
	अगर (estate == PCI_ERS_RESULT_RECOVERED) अणु
		pci_dbg(edev, "DPC port successfully recovered\n");
		acpi_send_edr_status(pdev, edev, EDR_OST_SUCCESS);
	पूर्ण अन्यथा अणु
		pci_dbg(edev, "DPC port recovery failed\n");
		acpi_send_edr_status(pdev, edev, EDR_OST_FAILED);
	पूर्ण

	pci_dev_put(edev);
पूर्ण

व्योम pci_acpi_add_edr_notअगरier(काष्ठा pci_dev *pdev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	acpi_status status;

	अगर (!adev) अणु
		pci_dbg(pdev, "No valid ACPI node, skipping EDR init\n");
		वापस;
	पूर्ण

	status = acpi_install_notअगरy_handler(adev->handle, ACPI_SYSTEM_NOTIFY,
					     edr_handle_event, pdev);
	अगर (ACPI_FAILURE(status)) अणु
		pci_err(pdev, "Failed to install notify handler\n");
		वापस;
	पूर्ण

	अगर (acpi_enable_dpc(pdev))
		acpi_हटाओ_notअगरy_handler(adev->handle, ACPI_SYSTEM_NOTIFY,
					   edr_handle_event);
	अन्यथा
		pci_dbg(pdev, "Notify handler installed\n");
पूर्ण

व्योम pci_acpi_हटाओ_edr_notअगरier(काष्ठा pci_dev *pdev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&pdev->dev);

	अगर (!adev)
		वापस;

	acpi_हटाओ_notअगरy_handler(adev->handle, ACPI_SYSTEM_NOTIFY,
				   edr_handle_event);
	pci_dbg(pdev, "Notify handler removed\n");
पूर्ण
