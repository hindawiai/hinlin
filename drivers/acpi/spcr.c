<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, Intel Corporation
 * Copyright (c) 2015, Red Hat, Inc.
 * Copyright (c) 2015, 2016 Linaro Ltd.
 */

#घोषणा pr_fmt(fmt) "ACPI: SPCR: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/console.h>
#समावेश <linux/kernel.h>
#समावेश <linux/serial_core.h>

/*
 * Erratum 44 क्रम QDF2432v1 and QDF2400v1 SoCs describes the BUSY bit as
 * occasionally getting stuck as 1. To aव्योम the potential क्रम a hang, check
 * TXFE == 0 instead of BUSY == 1. This may not be suitable क्रम all UART
 * implementations, so only करो so अगर an affected platक्रमm is detected in
 * acpi_parse_spcr().
 */
bool qdf2400_e44_present;
EXPORT_SYMBOL(qdf2400_e44_present);

/*
 * Some Qualcomm Datacenter Technologies SoCs have a defective UART BUSY bit.
 * Detect them by examining the OEM fields in the SPCR header, similar to PCI
 * quirk detection in pci_mcfg.c.
 */
अटल bool qdf2400_erratum_44_present(काष्ठा acpi_table_header *h)
अणु
	अगर (स_भेद(h->oem_id, "QCOM  ", ACPI_OEM_ID_SIZE))
		वापस false;

	अगर (!स_भेद(h->oem_table_id, "QDF2432 ", ACPI_OEM_TABLE_ID_SIZE))
		वापस true;

	अगर (!स_भेद(h->oem_table_id, "QDF2400 ", ACPI_OEM_TABLE_ID_SIZE) &&
			h->oem_revision == 1)
		वापस true;

	वापस false;
पूर्ण

/*
 * APM X-Gene v1 and v2 UART hardware is an 16550 like device but has its
 * रेजिस्टर aligned to 32-bit. In addition, the BIOS also encoded the
 * access width to be 8 bits. This function detects this errata condition.
 */
अटल bool xgene_8250_erratum_present(काष्ठा acpi_table_spcr *tb)
अणु
	bool xgene_8250 = false;

	अगर (tb->पूर्णांकerface_type != ACPI_DBG2_16550_COMPATIBLE)
		वापस false;

	अगर (स_भेद(tb->header.oem_id, "APMC0D", ACPI_OEM_ID_SIZE) &&
	    स_भेद(tb->header.oem_id, "HPE   ", ACPI_OEM_ID_SIZE))
		वापस false;

	अगर (!स_भेद(tb->header.oem_table_id, "XGENESPC",
	    ACPI_OEM_TABLE_ID_SIZE) && tb->header.oem_revision == 0)
		xgene_8250 = true;

	अगर (!स_भेद(tb->header.oem_table_id, "ProLiant",
	    ACPI_OEM_TABLE_ID_SIZE) && tb->header.oem_revision == 1)
		xgene_8250 = true;

	वापस xgene_8250;
पूर्ण

/**
 * acpi_parse_spcr() - parse ACPI SPCR table and add preferred console
 *
 * @enable_earlycon: set up earlycon क्रम the console specअगरied by the table
 * @enable_console: setup the console specअगरied by the table.
 *
 * For the architectures with support क्रम ACPI, CONFIG_ACPI_SPCR_TABLE may be
 * defined to parse ACPI SPCR table.  As a result of the parsing preferred
 * console is रेजिस्टरed and अगर @enable_earlycon is true, earlycon is set up.
 * If @enable_console is true the प्रणाली console is also configured.
 *
 * When CONFIG_ACPI_SPCR_TABLE is defined, this function should be called
 * from arch initialization code as soon as the DT/ACPI decision is made.
 *
 */
पूर्णांक __init acpi_parse_spcr(bool enable_earlycon, bool enable_console)
अणु
	अटल अक्षर opts[64];
	काष्ठा acpi_table_spcr *table;
	acpi_status status;
	अक्षर *uart;
	अक्षर *iotype;
	पूर्णांक baud_rate;
	पूर्णांक err;

	अगर (acpi_disabled)
		वापस -ENODEV;

	status = acpi_get_table(ACPI_SIG_SPCR, 0,
				(काष्ठा acpi_table_header **)&table);

	अगर (ACPI_FAILURE(status))
		वापस -ENOENT;

	अगर (table->header.revision < 2)
		pr_info("SPCR table version %d\n", table->header.revision);

	अगर (table->serial_port.space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY) अणु
		चयन (ACPI_ACCESS_BIT_WIDTH((
			table->serial_port.access_width))) अणु
		शेष:
			pr_err("Unexpected SPCR Access Width.  Defaulting to byte size\n");
			fallthrough;
		हाल 8:
			iotype = "mmio";
			अवरोध;
		हाल 16:
			iotype = "mmio16";
			अवरोध;
		हाल 32:
			iotype = "mmio32";
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		iotype = "io";

	चयन (table->पूर्णांकerface_type) अणु
	हाल ACPI_DBG2_ARM_SBSA_32BIT:
		iotype = "mmio32";
		fallthrough;
	हाल ACPI_DBG2_ARM_PL011:
	हाल ACPI_DBG2_ARM_SBSA_GENERIC:
	हाल ACPI_DBG2_BCM2835:
		uart = "pl011";
		अवरोध;
	हाल ACPI_DBG2_16550_COMPATIBLE:
	हाल ACPI_DBG2_16550_SUBSET:
		uart = "uart";
		अवरोध;
	शेष:
		err = -ENOENT;
		जाओ करोne;
	पूर्ण

	चयन (table->baud_rate) अणु
	हाल 0:
		/*
		 * SPCR 1.04 defines 0 as a preconfigured state of UART.
		 * Assume firmware or bootloader configures console correctly.
		 */
		baud_rate = 0;
		अवरोध;
	हाल 3:
		baud_rate = 9600;
		अवरोध;
	हाल 4:
		baud_rate = 19200;
		अवरोध;
	हाल 6:
		baud_rate = 57600;
		अवरोध;
	हाल 7:
		baud_rate = 115200;
		अवरोध;
	शेष:
		err = -ENOENT;
		जाओ करोne;
	पूर्ण

	/*
	 * If the E44 erratum is required, then we need to tell the pl011
	 * driver to implement the work-around.
	 *
	 * The global variable is used by the probe function when it
	 * creates the UARTs, whether or not they're used as a console.
	 *
	 * If the user specअगरies "traditional" earlycon, the qdf2400_e44
	 * console name matches the EARLYCON_DECLARE() statement, and
	 * SPCR is not used.  Parameter "earlycon" is false.
	 *
	 * If the user specअगरies "SPCR" earlycon, then we need to update
	 * the console name so that it also says "qdf2400_e44".  Parameter
	 * "earlycon" is true.
	 *
	 * For consistency, अगर we change the console name, then we करो it
	 * क्रम everyone, not just earlycon.
	 */
	अगर (qdf2400_erratum_44_present(&table->header)) अणु
		qdf2400_e44_present = true;
		अगर (enable_earlycon)
			uart = "qdf2400_e44";
	पूर्ण

	अगर (xgene_8250_erratum_present(table)) अणु
		iotype = "mmio32";

		/* क्रम xgene v1 and v2 we करोn't know the घड़ी rate of the
		 * UART so करोn't attempt to change to the baud rate state
		 * in the table because driver cannot calculate the भागiders
		 */
		baud_rate = 0;
	पूर्ण

	अगर (!baud_rate) अणु
		snम_लिखो(opts, माप(opts), "%s,%s,0x%llx", uart, iotype,
			 table->serial_port.address);
	पूर्ण अन्यथा अणु
		snम_लिखो(opts, माप(opts), "%s,%s,0x%llx,%d", uart, iotype,
			 table->serial_port.address, baud_rate);
	पूर्ण

	pr_info("console: %s\n", opts);

	अगर (enable_earlycon)
		setup_earlycon(opts);

	अगर (enable_console)
		err = add_preferred_console(uart, 0, opts + म_माप(uart) + 1);
	अन्यथा
		err = 0;
करोne:
	acpi_put_table((काष्ठा acpi_table_header *)table);
	वापस err;
पूर्ण
