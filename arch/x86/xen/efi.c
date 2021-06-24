<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Oracle Co., Daniel Kiper
 */

#समावेश <linux/bitops.h>
#समावेश <linux/efi.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>

#समावेश <xen/xen.h>
#समावेश <xen/xen-ops.h>
#समावेश <xen/पूर्णांकerface/platक्रमm.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/xen/hypercall.h>

अटल efi_अक्षर16_t venकरोr[100] __initdata;

अटल efi_प्रणाली_table_t efi_systab_xen __initdata = अणु
	.hdr = अणु
		.signature	= EFI_SYSTEM_TABLE_SIGNATURE,
		.revision	= 0, /* Initialized later. */
		.headersize	= 0, /* Ignored by Linux Kernel. */
		.crc32		= 0, /* Ignored by Linux Kernel. */
		.reserved	= 0
	पूर्ण,
	.fw_venकरोr	= EFI_INVALID_TABLE_ADDR, /* Initialized later. */
	.fw_revision	= 0,			  /* Initialized later. */
	.con_in_handle	= EFI_INVALID_TABLE_ADDR, /* Not used under Xen. */
	.con_in		= शून्य,			  /* Not used under Xen. */
	.con_out_handle	= EFI_INVALID_TABLE_ADDR, /* Not used under Xen. */
	.con_out	= शून्य, 		  /* Not used under Xen. */
	.मानक_त्रुटि_handle	= EFI_INVALID_TABLE_ADDR, /* Not used under Xen. */
	.मानक_त्रुटि		= EFI_INVALID_TABLE_ADDR, /* Not used under Xen. */
	.runसमय	= (efi_runसमय_services_t *)EFI_INVALID_TABLE_ADDR,
						  /* Not used under Xen. */
	.bootसमय	= (efi_boot_services_t *)EFI_INVALID_TABLE_ADDR,
						  /* Not used under Xen. */
	.nr_tables	= 0,			  /* Initialized later. */
	.tables		= EFI_INVALID_TABLE_ADDR  /* Initialized later. */
पूर्ण;

अटल efi_प्रणाली_table_t __init *xen_efi_probe(व्योम)
अणु
	काष्ठा xen_platक्रमm_op op = अणु
		.cmd = XENPF_firmware_info,
		.u.firmware_info = अणु
			.type = XEN_FW_EFI_INFO,
			.index = XEN_FW_EFI_CONFIG_TABLE
		पूर्ण
	पूर्ण;
	जोड़ xenpf_efi_info *info = &op.u.firmware_info.u.efi_info;

	अगर (!xen_initial_करोमुख्य() || HYPERVISOR_platक्रमm_op(&op) < 0)
		वापस शून्य;

	/* Here we know that Xen runs on EFI platक्रमm. */
	xen_efi_runसमय_setup();

	efi_systab_xen.tables = info->cfg.addr;
	efi_systab_xen.nr_tables = info->cfg.nent;

	op.cmd = XENPF_firmware_info;
	op.u.firmware_info.type = XEN_FW_EFI_INFO;
	op.u.firmware_info.index = XEN_FW_EFI_VENDOR;
	info->venकरोr.bufsz = माप(venकरोr);
	set_xen_guest_handle(info->venकरोr.name, venकरोr);

	अगर (HYPERVISOR_platक्रमm_op(&op) == 0) अणु
		efi_systab_xen.fw_venकरोr = __pa_symbol(venकरोr);
		efi_systab_xen.fw_revision = info->venकरोr.revision;
	पूर्ण अन्यथा
		efi_systab_xen.fw_venकरोr = __pa_symbol(L"UNKNOWN");

	op.cmd = XENPF_firmware_info;
	op.u.firmware_info.type = XEN_FW_EFI_INFO;
	op.u.firmware_info.index = XEN_FW_EFI_VERSION;

	अगर (HYPERVISOR_platक्रमm_op(&op) == 0)
		efi_systab_xen.hdr.revision = info->version;

	op.cmd = XENPF_firmware_info;
	op.u.firmware_info.type = XEN_FW_EFI_INFO;
	op.u.firmware_info.index = XEN_FW_EFI_RT_VERSION;

	अगर (HYPERVISOR_platक्रमm_op(&op) == 0)
		efi.runसमय_version = info->version;

	वापस &efi_systab_xen;
पूर्ण

/*
 * Determine whether we're in secure boot mode.
 */
अटल क्रमागत efi_secureboot_mode xen_efi_get_secureboot(व्योम)
अणु
	अटल efi_guid_t shim_guid = EFI_SHIM_LOCK_GUID;
	क्रमागत efi_secureboot_mode mode;
	efi_status_t status;
	u8 moksbstate;
	अचिन्हित दीर्घ size;

	mode = efi_get_secureboot_mode(efi.get_variable);
	अगर (mode == efi_secureboot_mode_unknown) अणु
		pr_err("Could not determine UEFI Secure Boot status.\n");
		वापस efi_secureboot_mode_unknown;
	पूर्ण
	अगर (mode != efi_secureboot_mode_enabled)
		वापस mode;

	/* See अगर a user has put the shim पूर्णांकo insecure mode. */
	size = माप(moksbstate);
	status = efi.get_variable(L"MokSBStateRT", &shim_guid,
				  शून्य, &size, &moksbstate);

	/* If it fails, we करोn't care why. Default to secure. */
	अगर (status != EFI_SUCCESS)
		जाओ secure_boot_enabled;

	अगर (moksbstate == 1)
		वापस efi_secureboot_mode_disabled;

 secure_boot_enabled:
	pr_info("UEFI Secure Boot is enabled.\n");
	वापस efi_secureboot_mode_enabled;
पूर्ण

व्योम __init xen_efi_init(काष्ठा boot_params *boot_params)
अणु
	efi_प्रणाली_table_t *efi_systab_xen;

	efi_systab_xen = xen_efi_probe();

	अगर (efi_systab_xen == शून्य)
		वापस;

	म_नकलन((अक्षर *)&boot_params->efi_info.efi_loader_signature, "Xen",
			माप(boot_params->efi_info.efi_loader_signature));
	boot_params->efi_info.efi_systab = (__u32)__pa(efi_systab_xen);
	boot_params->efi_info.efi_systab_hi = (__u32)(__pa(efi_systab_xen) >> 32);

	boot_params->secure_boot = xen_efi_get_secureboot();

	set_bit(EFI_BOOT, &efi.flags);
	set_bit(EFI_PARAVIRT, &efi.flags);
	set_bit(EFI_64BIT, &efi.flags);
पूर्ण
