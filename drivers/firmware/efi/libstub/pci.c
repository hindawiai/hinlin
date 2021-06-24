<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI-related functions used by the EFI stub on multiple
 * architectures.
 *
 * Copyright 2019 Google, LLC
 */

#समावेश <linux/efi.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/efi.h>

#समावेश "efistub.h"

व्योम efi_pci_disable_bridge_busmaster(व्योम)
अणु
	efi_guid_t pci_proto = EFI_PCI_IO_PROTOCOL_GUID;
	अचिन्हित दीर्घ pci_handle_size = 0;
	efi_handle_t *pci_handle = शून्य;
	efi_handle_t handle;
	efi_status_t status;
	u16 class, command;
	पूर्णांक i;

	status = efi_bs_call(locate_handle, EFI_LOCATE_BY_PROTOCOL, &pci_proto,
			     शून्य, &pci_handle_size, शून्य);

	अगर (status != EFI_BUFFER_TOO_SMALL) अणु
		अगर (status != EFI_SUCCESS && status != EFI_NOT_FOUND)
			efi_err("Failed to locate PCI I/O handles'\n");
		वापस;
	पूर्ण

	status = efi_bs_call(allocate_pool, EFI_LOADER_DATA, pci_handle_size,
			     (व्योम **)&pci_handle);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to allocate memory for 'pci_handle'\n");
		वापस;
	पूर्ण

	status = efi_bs_call(locate_handle, EFI_LOCATE_BY_PROTOCOL, &pci_proto,
			     शून्य, &pci_handle_size, pci_handle);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to locate PCI I/O handles'\n");
		जाओ मुक्त_handle;
	पूर्ण

	क्रम_each_efi_handle(handle, pci_handle, pci_handle_size, i) अणु
		efi_pci_io_protocol_t *pci;
		अचिन्हित दीर्घ segment_nr, bus_nr, device_nr, func_nr;

		status = efi_bs_call(handle_protocol, handle, &pci_proto,
				     (व्योम **)&pci);
		अगर (status != EFI_SUCCESS)
			जारी;

		/*
		 * Disregard devices living on bus 0 - these are not behind a
		 * bridge so no poपूर्णांक in disconnecting them from their drivers.
		 */
		status = efi_call_proto(pci, get_location, &segment_nr, &bus_nr,
					&device_nr, &func_nr);
		अगर (status != EFI_SUCCESS || bus_nr == 0)
			जारी;

		/*
		 * Don't disconnect VGA controllers so we don't risk losing
		 * access to the framebuffer. Drivers क्रम true PCIe graphics
		 * controllers that are behind a PCIe root port करो not use
		 * DMA to implement the GOP framebuffer anyway [although they
		 * may use it in their implementation of Gop->Blt()], and so
		 * disabling DMA in the PCI bridge should not पूर्णांकerfere with
		 * normal operation of the device.
		 */
		status = efi_call_proto(pci, pci.पढ़ो, EfiPciIoWidthUपूर्णांक16,
					PCI_CLASS_DEVICE, 1, &class);
		अगर (status != EFI_SUCCESS || class == PCI_CLASS_DISPLAY_VGA)
			जारी;

		/* Disconnect this handle from all its drivers */
		efi_bs_call(disconnect_controller, handle, शून्य, शून्य);
	पूर्ण

	क्रम_each_efi_handle(handle, pci_handle, pci_handle_size, i) अणु
		efi_pci_io_protocol_t *pci;

		status = efi_bs_call(handle_protocol, handle, &pci_proto,
				     (व्योम **)&pci);
		अगर (status != EFI_SUCCESS || !pci)
			जारी;

		status = efi_call_proto(pci, pci.पढ़ो, EfiPciIoWidthUपूर्णांक16,
					PCI_CLASS_DEVICE, 1, &class);

		अगर (status != EFI_SUCCESS || class != PCI_CLASS_BRIDGE_PCI)
			जारी;

		/* Disable busmastering */
		status = efi_call_proto(pci, pci.पढ़ो, EfiPciIoWidthUपूर्णांक16,
					PCI_COMMAND, 1, &command);
		अगर (status != EFI_SUCCESS || !(command & PCI_COMMAND_MASTER))
			जारी;

		command &= ~PCI_COMMAND_MASTER;
		status = efi_call_proto(pci, pci.ग_लिखो, EfiPciIoWidthUपूर्णांक16,
					PCI_COMMAND, 1, &command);
		अगर (status != EFI_SUCCESS)
			efi_err("Failed to disable PCI busmastering\n");
	पूर्ण

मुक्त_handle:
	efi_bs_call(मुक्त_pool, pci_handle);
पूर्ण
