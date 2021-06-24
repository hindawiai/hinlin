<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/reboot.h>
#समावेश <linux/delay.h>

#अगर_घोषित CONFIG_PCI
अटल व्योम acpi_pci_reboot(काष्ठा acpi_generic_address *rr, u8 reset_value)
अणु
	अचिन्हित पूर्णांक devfn;
	काष्ठा pci_bus *bus0;

	/* The reset रेजिस्टर can only live on bus 0. */
	bus0 = pci_find_bus(0, 0);
	अगर (!bus0)
		वापस;
	/* Form PCI device/function pair. */
	devfn = PCI_DEVFN((rr->address >> 32) & 0xffff,
			  (rr->address >> 16) & 0xffff);
	pr_debug("Resetting with ACPI PCI RESET_REG.\n");
	/* Write the value that resets us. */
	pci_bus_ग_लिखो_config_byte(bus0, devfn,
			(rr->address & 0xffff), reset_value);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम acpi_pci_reboot(काष्ठा acpi_generic_address *rr,
				   u8 reset_value)
अणु
	pr_warn_once("PCI configuration space access is not supported\n");
पूर्ण
#पूर्ण_अगर

व्योम acpi_reboot(व्योम)
अणु
	काष्ठा acpi_generic_address *rr;
	u8 reset_value;

	अगर (acpi_disabled)
		वापस;

	rr = &acpi_gbl_FADT.reset_रेजिस्टर;

	/* ACPI reset रेजिस्टर was only पूर्णांकroduced with v2 of the FADT */

	अगर (acpi_gbl_FADT.header.revision < 2)
		वापस;

	/* Is the reset रेजिस्टर supported? The spec says we should be
	 * checking the bit width and bit offset, but Winकरोws ignores
	 * these fields */
	अगर (!(acpi_gbl_FADT.flags & ACPI_FADT_RESET_REGISTER))
		वापस;

	reset_value = acpi_gbl_FADT.reset_value;

	/* The reset रेजिस्टर can only exist in I/O, Memory or PCI config space
	 * on a device on bus 0. */
	चयन (rr->space_id) अणु
	हाल ACPI_ADR_SPACE_PCI_CONFIG:
		acpi_pci_reboot(rr, reset_value);
		अवरोध;

	हाल ACPI_ADR_SPACE_SYSTEM_MEMORY:
	हाल ACPI_ADR_SPACE_SYSTEM_IO:
		prपूर्णांकk(KERN_DEBUG "ACPI MEMORY or I/O RESET_REG.\n");
		acpi_reset();
		अवरोध;
	पूर्ण

	/*
	 * Some platक्रमms करो not shut करोwn immediately after writing to the
	 * ACPI reset रेजिस्टर, and this results in racing with the
	 * subsequent reboot mechanism.
	 *
	 * The 15ms delay has been found to be दीर्घ enough क्रम the प्रणाली
	 * to reboot on the affected platक्रमms.
	 */
	mdelay(15);
पूर्ण
