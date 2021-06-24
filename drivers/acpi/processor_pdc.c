<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005 Intel Corporation
 * Copyright (C) 2009 Hewlett-Packard Development Company, L.P.
 *
 *      Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>
 *      - Added _PDC क्रम platक्रमms with Intel CPUs
 */

#घोषणा pr_fmt(fmt) "ACPI: " fmt

#समावेश <linux/dmi.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/processor.h>

#समावेश "internal.h"

अटल bool __init processor_physically_present(acpi_handle handle)
अणु
	पूर्णांक cpuid, type;
	u32 acpi_id;
	acpi_status status;
	acpi_object_type acpi_type;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	जोड़ acpi_object object = अणु 0 पूर्ण;
	काष्ठा acpi_buffer buffer = अणु माप(जोड़ acpi_object), &object पूर्ण;

	status = acpi_get_type(handle, &acpi_type);
	अगर (ACPI_FAILURE(status))
		वापस false;

	चयन (acpi_type) अणु
	हाल ACPI_TYPE_PROCESSOR:
		status = acpi_evaluate_object(handle, शून्य, शून्य, &buffer);
		अगर (ACPI_FAILURE(status))
			वापस false;
		acpi_id = object.processor.proc_id;
		अवरोध;
	हाल ACPI_TYPE_DEVICE:
		status = acpi_evaluate_पूर्णांकeger(handle, "_UID", शून्य, &पंचांगp);
		अगर (ACPI_FAILURE(status))
			वापस false;
		acpi_id = पंचांगp;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	type = (acpi_type == ACPI_TYPE_DEVICE) ? 1 : 0;
	cpuid = acpi_get_cpuid(handle, type, acpi_id);

	वापस !invalid_logical_cpuid(cpuid);
पूर्ण

अटल व्योम acpi_set_pdc_bits(u32 *buf)
अणु
	buf[0] = ACPI_PDC_REVISION_ID;
	buf[1] = 1;

	/* Enable coordination with firmware's _TSD info */
	buf[2] = ACPI_PDC_SMP_T_SWCOORD;

	/* Twiddle arch-specअगरic bits needed क्रम _PDC */
	arch_acpi_set_pdc_bits(buf);
पूर्ण

अटल काष्ठा acpi_object_list *acpi_processor_alloc_pdc(व्योम)
अणु
	काष्ठा acpi_object_list *obj_list;
	जोड़ acpi_object *obj;
	u32 *buf;

	/* allocate and initialize pdc. It will be used later. */
	obj_list = kदो_स्मृति(माप(काष्ठा acpi_object_list), GFP_KERNEL);
	अगर (!obj_list)
		जाओ out;

	obj = kदो_स्मृति(माप(जोड़ acpi_object), GFP_KERNEL);
	अगर (!obj) अणु
		kमुक्त(obj_list);
		जाओ out;
	पूर्ण

	buf = kदो_स्मृति(12, GFP_KERNEL);
	अगर (!buf) अणु
		kमुक्त(obj);
		kमुक्त(obj_list);
		जाओ out;
	पूर्ण

	acpi_set_pdc_bits(buf);

	obj->type = ACPI_TYPE_BUFFER;
	obj->buffer.length = 12;
	obj->buffer.poपूर्णांकer = (u8 *) buf;
	obj_list->count = 1;
	obj_list->poपूर्णांकer = obj;

	वापस obj_list;
out:
	pr_err("Memory allocation error\n");
	वापस शून्य;
पूर्ण

/*
 * _PDC is required क्रम a BIOS-OS handshake क्रम most of the newer
 * ACPI processor features.
 */
अटल acpi_status
acpi_processor_eval_pdc(acpi_handle handle, काष्ठा acpi_object_list *pdc_in)
अणु
	acpi_status status = AE_OK;

	अगर (boot_option_idle_override == IDLE_NOMWAIT) अणु
		/*
		 * If mरुको is disabled क्रम CPU C-states, the C2C3_FFH access
		 * mode will be disabled in the parameter of _PDC object.
		 * Of course C1_FFH access mode will also be disabled.
		 */
		जोड़ acpi_object *obj;
		u32 *buffer = शून्य;

		obj = pdc_in->poपूर्णांकer;
		buffer = (u32 *)(obj->buffer.poपूर्णांकer);
		buffer[2] &= ~(ACPI_PDC_C_C2C3_FFH | ACPI_PDC_C_C1_FFH);

	पूर्ण
	status = acpi_evaluate_object(handle, "_PDC", pdc_in, शून्य);

	अगर (ACPI_FAILURE(status))
		acpi_handle_debug(handle,
		    "Could not evaluate _PDC, using legacy perf control\n");

	वापस status;
पूर्ण

व्योम acpi_processor_set_pdc(acpi_handle handle)
अणु
	काष्ठा acpi_object_list *obj_list;

	अगर (arch_has_acpi_pdc() == false)
		वापस;

	obj_list = acpi_processor_alloc_pdc();
	अगर (!obj_list)
		वापस;

	acpi_processor_eval_pdc(handle, obj_list);

	kमुक्त(obj_list->poपूर्णांकer->buffer.poपूर्णांकer);
	kमुक्त(obj_list->poपूर्णांकer);
	kमुक्त(obj_list);
पूर्ण

अटल acpi_status __init
early_init_pdc(acpi_handle handle, u32 lvl, व्योम *context, व्योम **rv)
अणु
	अगर (processor_physically_present(handle) == false)
		वापस AE_OK;

	acpi_processor_set_pdc(handle);
	वापस AE_OK;
पूर्ण

अटल पूर्णांक __init set_no_mरुको(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pr_notice("%s detected - disabling mwait for CPU C-states\n",
		  id->ident);
	boot_option_idle_override = IDLE_NOMWAIT;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id processor_idle_dmi_table[] __initस्थिर = अणु
	अणु
	set_no_mरुको, "Extensa 5220", अणु
	DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies LTD"),
	DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
	DMI_MATCH(DMI_PRODUCT_VERSION, "0100"),
	DMI_MATCH(DMI_BOARD_NAME, "Columbia") पूर्ण, शून्यपूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम __init processor_dmi_check(व्योम)
अणु
	/*
	 * Check whether the प्रणाली is DMI table. If yes, OSPM
	 * should not use mरुको क्रम CPU-states.
	 */
	dmi_check_प्रणाली(processor_idle_dmi_table);
पूर्ण

व्योम __init acpi_early_processor_set_pdc(व्योम)
अणु
	processor_dmi_check();

	acpi_walk_namespace(ACPI_TYPE_PROCESSOR, ACPI_ROOT_OBJECT,
			    ACPI_UINT32_MAX,
			    early_init_pdc, शून्य, शून्य, शून्य);
	acpi_get_devices(ACPI_PROCESSOR_DEVICE_HID, early_init_pdc, शून्य, शून्य);
पूर्ण
