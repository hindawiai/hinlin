<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  acpi_drivers.h  ($Revision: 31 $)
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 */

#अगर_अघोषित __ACPI_DRIVERS_H__
#घोषणा __ACPI_DRIVERS_H__

#घोषणा ACPI_MAX_STRING			80

/*
 * _HID definitions
 * HIDs must conक्रमm to ACPI spec(6.1.4)
 * Linux specअगरic HIDs करो not apply to this and begin with LNX:
 */

#घोषणा ACPI_POWER_HID			"LNXPOWER"
#घोषणा ACPI_PROCESSOR_OBJECT_HID	"LNXCPU"
#घोषणा ACPI_SYSTEM_HID			"LNXSYSTM"
#घोषणा ACPI_THERMAL_HID		"LNXTHERM"
#घोषणा ACPI_BUTTON_HID_POWERF		"LNXPWRBN"
#घोषणा ACPI_BUTTON_HID_SLEEPF		"LNXSLPBN"
#घोषणा ACPI_VIDEO_HID			"LNXVIDEO"
#घोषणा ACPI_BAY_HID			"LNXIOBAY"
#घोषणा ACPI_DOCK_HID			"LNXDOCK"
#घोषणा ACPI_ECDT_HID			"LNXEC"
/* Quirk क्रम broken IBM BIOSes */
#घोषणा ACPI_SMBUS_IBM_HID		"SMBUSIBM"

/*
 * For fixed hardware buttons, we fabricate acpi_devices with HID
 * ACPI_BUTTON_HID_POWERF or ACPI_BUTTON_HID_SLEEPF.  Fixed hardware
 * संकेतs only an event; it करोesn't supply a notअगरication value.
 * To allow drivers to treat notअगरications from fixed hardware the
 * same as those from real devices, we turn the events पूर्णांकo this
 * notअगरication value.
 */
#घोषणा ACPI_FIXED_HARDWARE_EVENT	0x100

/* --------------------------------------------------------------------------
                                       PCI
   -------------------------------------------------------------------------- */


/* ACPI PCI Interrupt Link */

पूर्णांक acpi_irq_penalty_init(व्योम);
पूर्णांक acpi_pci_link_allocate_irq(acpi_handle handle, पूर्णांक index, पूर्णांक *triggering,
			       पूर्णांक *polarity, अक्षर **name);
पूर्णांक acpi_pci_link_मुक्त_irq(acpi_handle handle);

/* ACPI PCI Device Binding */

काष्ठा pci_bus;

#अगर_घोषित CONFIG_PCI
काष्ठा pci_dev *acpi_get_pci_dev(acpi_handle);
#अन्यथा
अटल अंतरभूत काष्ठा pci_dev *acpi_get_pci_dev(acpi_handle handle)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/* Arch-defined function to add a bus to the प्रणाली */

काष्ठा pci_bus *pci_acpi_scan_root(काष्ठा acpi_pci_root *root);

#अगर_घोषित CONFIG_X86
व्योम pci_acpi_crs_quirks(व्योम);
#अन्यथा
अटल अंतरभूत व्योम pci_acpi_crs_quirks(व्योम) अणु पूर्ण
#पूर्ण_अगर

/*--------------------------------------------------------------------------
                                  Dock Station
  -------------------------------------------------------------------------- */

#अगर_घोषित CONFIG_ACPI_DOCK
बाह्य पूर्णांक is_करोck_device(काष्ठा acpi_device *adev);
#अन्यथा
अटल अंतरभूत पूर्णांक is_करोck_device(काष्ठा acpi_device *adev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_DOCK */

#पूर्ण_अगर /*__ACPI_DRIVERS_H__*/
