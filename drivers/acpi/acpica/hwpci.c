<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: hwpci - Obtain PCI bus, device, and function numbers
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("hwpci")

/* PCI configuration space values */
#घोषणा PCI_CFG_HEADER_TYPE_REG             0x0E
#घोषणा PCI_CFG_PRIMARY_BUS_NUMBER_REG      0x18
#घोषणा PCI_CFG_SECONDARY_BUS_NUMBER_REG    0x19
/* PCI header values */
#घोषणा PCI_HEADER_TYPE_MASK                0x7F
#घोषणा PCI_TYPE_BRIDGE                     0x01
#घोषणा PCI_TYPE_CARDBUS_BRIDGE             0x02
प्रकार काष्ठा acpi_pci_device अणु
	acpi_handle device;
	काष्ठा acpi_pci_device *next;

पूर्ण acpi_pci_device;

/* Local prototypes */

अटल acpi_status
acpi_hw_build_pci_list(acpi_handle root_pci_device,
		       acpi_handle pci_region,
		       काष्ठा acpi_pci_device **वापस_list_head);

अटल acpi_status
acpi_hw_process_pci_list(काष्ठा acpi_pci_id *pci_id,
			 काष्ठा acpi_pci_device *list_head);

अटल व्योम acpi_hw_delete_pci_list(काष्ठा acpi_pci_device *list_head);

अटल acpi_status
acpi_hw_get_pci_device_info(काष्ठा acpi_pci_id *pci_id,
			    acpi_handle pci_device,
			    u16 *bus_number, u8 *is_bridge);

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_derive_pci_id
 *
 * PARAMETERS:  pci_id              - Initial values क्रम the PCI ID. May be
 *                                    modअगरied by this function.
 *              root_pci_device     - A handle to a PCI device object. This
 *                                    object must be a PCI Root Bridge having a
 *                                    _HID value of either PNP0A03 or PNP0A08
 *              pci_region          - A handle to a PCI configuration space
 *                                    Operation Region being initialized
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function derives a full PCI ID क्रम a PCI device,
 *              consisting of a Segment number, Bus number, Device number,
 *              and function code.
 *
 *              The PCI hardware dynamically configures PCI bus numbers
 *              depending on the bus topology discovered during प्रणाली
 *              initialization. This function is invoked during configuration
 *              of a PCI_Config Operation Region in order to (possibly) update
 *              the Bus/Device/Function numbers in the pci_id with the actual
 *              values as determined by the hardware and operating प्रणाली
 *              configuration.
 *
 *              The pci_id parameter is initially populated during the Operation
 *              Region initialization. This function is then called, and is
 *              will make any necessary modअगरications to the Bus, Device, or
 *              Function number PCI ID subfields as appropriate क्रम the
 *              current hardware and OS configuration.
 *
 * NOTE:        Created 08/2010. Replaces the previous OSL acpi_os_derive_pci_id
 *              पूर्णांकerface since this feature is OS-independent. This module
 *              specअगरically aव्योमs any use of recursion by building a local
 *              temporary device list.
 *
 ******************************************************************************/

acpi_status
acpi_hw_derive_pci_id(काष्ठा acpi_pci_id *pci_id,
		      acpi_handle root_pci_device, acpi_handle pci_region)
अणु
	acpi_status status;
	काष्ठा acpi_pci_device *list_head;

	ACPI_FUNCTION_TRACE(hw_derive_pci_id);

	अगर (!pci_id) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Build a list of PCI devices, from pci_region up to root_pci_device */

	status =
	    acpi_hw_build_pci_list(root_pci_device, pci_region, &list_head);
	अगर (ACPI_SUCCESS(status)) अणु

		/* Walk the list, updating the PCI device/function/bus numbers */

		status = acpi_hw_process_pci_list(pci_id, list_head);

		/* Delete the list */

		acpi_hw_delete_pci_list(list_head);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_build_pci_list
 *
 * PARAMETERS:  root_pci_device     - A handle to a PCI device object. This
 *                                    object is guaranteed to be a PCI Root
 *                                    Bridge having a _HID value of either
 *                                    PNP0A03 or PNP0A08
 *              pci_region          - A handle to the PCI configuration space
 *                                    Operation Region
 *              वापस_list_head    - Where the PCI device list is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Builds a list of devices from the input PCI region up to the
 *              Root PCI device क्रम this namespace subtree.
 *
 ******************************************************************************/

अटल acpi_status
acpi_hw_build_pci_list(acpi_handle root_pci_device,
		       acpi_handle pci_region,
		       काष्ठा acpi_pci_device **वापस_list_head)
अणु
	acpi_handle current_device;
	acpi_handle parent_device;
	acpi_status status;
	काष्ठा acpi_pci_device *list_element;

	/*
	 * Ascend namespace branch until the root_pci_device is reached, building
	 * a list of device nodes. Loop will निकास when either the PCI device is
	 * found, or the root of the namespace is reached.
	 */
	*वापस_list_head = शून्य;
	current_device = pci_region;
	जबतक (1) अणु
		status = acpi_get_parent(current_device, &parent_device);
		अगर (ACPI_FAILURE(status)) अणु

			/* Must delete the list beक्रमe निकास */

			acpi_hw_delete_pci_list(*वापस_list_head);
			वापस (status);
		पूर्ण

		/* Finished when we reach the PCI root device (PNP0A03 or PNP0A08) */

		अगर (parent_device == root_pci_device) अणु
			वापस (AE_OK);
		पूर्ण

		list_element = ACPI_ALLOCATE(माप(काष्ठा acpi_pci_device));
		अगर (!list_element) अणु

			/* Must delete the list beक्रमe निकास */

			acpi_hw_delete_pci_list(*वापस_list_head);
			वापस (AE_NO_MEMORY);
		पूर्ण

		/* Put new element at the head of the list */

		list_element->next = *वापस_list_head;
		list_element->device = parent_device;
		*वापस_list_head = list_element;

		current_device = parent_device;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_process_pci_list
 *
 * PARAMETERS:  pci_id              - Initial values क्रम the PCI ID. May be
 *                                    modअगरied by this function.
 *              list_head           - Device list created by
 *                                    acpi_hw_build_pci_list
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Walk करोwnward through the PCI device list, getting the device
 *              info क्रम each, via the PCI configuration space and updating
 *              the PCI ID as necessary. Deletes the list during traversal.
 *
 ******************************************************************************/

अटल acpi_status
acpi_hw_process_pci_list(काष्ठा acpi_pci_id *pci_id,
			 काष्ठा acpi_pci_device *list_head)
अणु
	acpi_status status = AE_OK;
	काष्ठा acpi_pci_device *info;
	u16 bus_number;
	u8 is_bridge = TRUE;

	ACPI_FUNCTION_NAME(hw_process_pci_list);

	ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
			  "Input PciId:  Seg %4.4X Bus %4.4X Dev %4.4X Func %4.4X\n",
			  pci_id->segment, pci_id->bus, pci_id->device,
			  pci_id->function));

	bus_number = pci_id->bus;

	/*
	 * Descend करोwn the namespace tree, collecting PCI device, function,
	 * and bus numbers. bus_number is only important क्रम PCI bridges.
	 * Algorithm: As we descend the tree, use the last valid PCI device,
	 * function, and bus numbers that are discovered, and assign them
	 * to the PCI ID क्रम the target device.
	 */
	info = list_head;
	जबतक (info) अणु
		status = acpi_hw_get_pci_device_info(pci_id, info->device,
						     &bus_number, &is_bridge);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण

		info = info->next;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
			  "Output PciId: Seg %4.4X Bus %4.4X Dev %4.4X Func %4.4X "
			  "Status %X BusNumber %X IsBridge %X\n",
			  pci_id->segment, pci_id->bus, pci_id->device,
			  pci_id->function, status, bus_number, is_bridge));

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_delete_pci_list
 *
 * PARAMETERS:  list_head           - Device list created by
 *                                    acpi_hw_build_pci_list
 *
 * RETURN:      None
 *
 * DESCRIPTION: Free the entire PCI list.
 *
 ******************************************************************************/

अटल व्योम acpi_hw_delete_pci_list(काष्ठा acpi_pci_device *list_head)
अणु
	काष्ठा acpi_pci_device *next;
	काष्ठा acpi_pci_device *previous;

	next = list_head;
	जबतक (next) अणु
		previous = next;
		next = previous->next;
		ACPI_FREE(previous);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_get_pci_device_info
 *
 * PARAMETERS:  pci_id              - Initial values क्रम the PCI ID. May be
 *                                    modअगरied by this function.
 *              pci_device          - Handle क्रम the PCI device object
 *              bus_number          - Where a PCI bridge bus number is वापसed
 *              is_bridge           - Return value, indicates अगर this PCI
 *                                    device is a PCI bridge
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get the device info क्रम a single PCI device object. Get the
 *              _ADR (contains PCI device and function numbers), and क्रम PCI
 *              bridge devices, get the bus number from PCI configuration
 *              space.
 *
 ******************************************************************************/

अटल acpi_status
acpi_hw_get_pci_device_info(काष्ठा acpi_pci_id *pci_id,
			    acpi_handle pci_device,
			    u16 *bus_number, u8 *is_bridge)
अणु
	acpi_status status;
	acpi_object_type object_type;
	u64 वापस_value;
	u64 pci_value;

	/* We only care about objects of type Device */

	status = acpi_get_type(pci_device, &object_type);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	अगर (object_type != ACPI_TYPE_DEVICE) अणु
		वापस (AE_OK);
	पूर्ण

	/* We need an _ADR. Ignore device अगर not present */

	status = acpi_ut_evaluate_numeric_object(METHOD_NAME__ADR,
						 pci_device, &वापस_value);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (AE_OK);
	पूर्ण

	/*
	 * From _ADR, get the PCI Device and Function and
	 * update the PCI ID.
	 */
	pci_id->device = ACPI_HIWORD(ACPI_LODWORD(वापस_value));
	pci_id->function = ACPI_LOWORD(ACPI_LODWORD(वापस_value));

	/*
	 * If the previous device was a bridge, use the previous
	 * device bus number
	 */
	अगर (*is_bridge) अणु
		pci_id->bus = *bus_number;
	पूर्ण

	/*
	 * Get the bus numbers from PCI Config space:
	 *
	 * First, get the PCI header_type
	 */
	*is_bridge = FALSE;
	status = acpi_os_पढ़ो_pci_configuration(pci_id,
						PCI_CFG_HEADER_TYPE_REG,
						&pci_value, 8);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* We only care about bridges (1=pci_bridge, 2=card_bus_bridge) */

	pci_value &= PCI_HEADER_TYPE_MASK;

	अगर ((pci_value != PCI_TYPE_BRIDGE) &&
	    (pci_value != PCI_TYPE_CARDBUS_BRIDGE)) अणु
		वापस (AE_OK);
	पूर्ण

	/* Bridge: Get the Primary bus_number */

	status = acpi_os_पढ़ो_pci_configuration(pci_id,
						PCI_CFG_PRIMARY_BUS_NUMBER_REG,
						&pci_value, 8);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	*is_bridge = TRUE;
	pci_id->bus = (u16)pci_value;

	/* Bridge: Get the Secondary bus_number */

	status = acpi_os_पढ़ो_pci_configuration(pci_id,
						PCI_CFG_SECONDARY_BUS_NUMBER_REG,
						&pci_value, 8);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	*bus_number = (u16)pci_value;
	वापस (AE_OK);
पूर्ण
