<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Address translation पूर्णांकerface via ACPI DSM.
 * Copyright (C) 2018 Intel Corporation
 *
 * Specअगरication क्रम this पूर्णांकerface is available at:
 *
 *	https://cdrdv2.पूर्णांकel.com/v1/dl/getContent/603354
 */

#समावेश <linux/acpi.h>
#समावेश <linux/adxl.h>

#घोषणा ADXL_REVISION			0x1
#घोषणा ADXL_IDX_GET_ADDR_PARAMS	0x1
#घोषणा ADXL_IDX_FORWARD_TRANSLATE	0x2
#घोषणा ACPI_ADXL_PATH			"\\_SB.ADXL"

/*
 * The specअगरication करोesn't provide a limit on how many
 * components are in a memory address. But since we allocate
 * memory based on the number the BIOS tells us, we should
 * defend against insane values.
 */
#घोषणा ADXL_MAX_COMPONENTS		500

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "ADXL: " fmt

अटल acpi_handle handle;
अटल जोड़ acpi_object *params;
अटल स्थिर guid_t adxl_guid =
	GUID_INIT(0xAA3C050A, 0x7EA4, 0x4C1F,
		  0xAF, 0xDA, 0x12, 0x67, 0xDF, 0xD3, 0xD4, 0x8D);

अटल पूर्णांक adxl_count;
अटल अक्षर **adxl_component_names;

अटल जोड़ acpi_object *adxl_dsm(पूर्णांक cmd, जोड़ acpi_object argv[])
अणु
	जोड़ acpi_object *obj, *o;

	obj = acpi_evaluate_dsm_typed(handle, &adxl_guid, ADXL_REVISION,
				      cmd, argv, ACPI_TYPE_PACKAGE);
	अगर (!obj) अणु
		pr_info("DSM call failed for cmd=%d\n", cmd);
		वापस शून्य;
	पूर्ण

	अगर (obj->package.count != 2) अणु
		pr_info("Bad pkg count %d\n", obj->package.count);
		जाओ err;
	पूर्ण

	o = obj->package.elements;
	अगर (o->type != ACPI_TYPE_INTEGER) अणु
		pr_info("Bad 1st element type %d\n", o->type);
		जाओ err;
	पूर्ण
	अगर (o->पूर्णांकeger.value) अणु
		pr_info("Bad ret val %llu\n", o->पूर्णांकeger.value);
		जाओ err;
	पूर्ण

	o = obj->package.elements + 1;
	अगर (o->type != ACPI_TYPE_PACKAGE) अणु
		pr_info("Bad 2nd element type %d\n", o->type);
		जाओ err;
	पूर्ण
	वापस obj;

err:
	ACPI_FREE(obj);
	वापस शून्य;
पूर्ण

/**
 * adxl_get_component_names - get list of memory component names
 * Returns शून्य terminated list of string names
 *
 * Give the caller a poपूर्णांकer to the list of memory component names
 * e.g. अणु "SystemAddress", "ProcessorSocketId", "ChannelId", ... शून्य पूर्ण
 * Caller should count how many strings in order to allocate a buffer
 * क्रम the वापस from adxl_decode().
 */
स्थिर अक्षर * स्थिर *adxl_get_component_names(व्योम)
अणु
	वापस (स्थिर अक्षर * स्थिर *)adxl_component_names;
पूर्ण
EXPORT_SYMBOL_GPL(adxl_get_component_names);

/**
 * adxl_decode - ask BIOS to decode a प्रणाली address to memory address
 * @addr: the address to decode
 * @component_values: poपूर्णांकer to array of values क्रम each component
 * Returns 0 on success, negative error code otherwise
 *
 * The index of each value वापसed in the array matches the index of
 * each component name वापसed by adxl_get_component_names().
 * Components that are not defined क्रम this address translation (e.g.
 * mirror channel number क्रम a non-mirrored address) are set to ~0ull.
 */
पूर्णांक adxl_decode(u64 addr, u64 component_values[])
अणु
	जोड़ acpi_object argv4[2], *results, *r;
	पूर्णांक i, cnt;

	अगर (!adxl_component_names)
		वापस -EOPNOTSUPP;

	argv4[0].type = ACPI_TYPE_PACKAGE;
	argv4[0].package.count = 1;
	argv4[0].package.elements = &argv4[1];
	argv4[1].पूर्णांकeger.type = ACPI_TYPE_INTEGER;
	argv4[1].पूर्णांकeger.value = addr;

	results = adxl_dsm(ADXL_IDX_FORWARD_TRANSLATE, argv4);
	अगर (!results)
		वापस -EINVAL;

	r = results->package.elements + 1;
	cnt = r->package.count;
	अगर (cnt != adxl_count) अणु
		ACPI_FREE(results);
		वापस -EINVAL;
	पूर्ण
	r = r->package.elements;

	क्रम (i = 0; i < cnt; i++)
		component_values[i] = r[i].पूर्णांकeger.value;

	ACPI_FREE(results);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adxl_decode);

अटल पूर्णांक __init adxl_init(व्योम)
अणु
	अक्षर *path = ACPI_ADXL_PATH;
	जोड़ acpi_object *p;
	acpi_status status;
	पूर्णांक i;

	status = acpi_get_handle(शून्य, path, &handle);
	अगर (ACPI_FAILURE(status)) अणु
		pr_debug("No ACPI handle for path %s\n", path);
		वापस -ENODEV;
	पूर्ण

	अगर (!acpi_has_method(handle, "_DSM")) अणु
		pr_info("No DSM method\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!acpi_check_dsm(handle, &adxl_guid, ADXL_REVISION,
			    ADXL_IDX_GET_ADDR_PARAMS |
			    ADXL_IDX_FORWARD_TRANSLATE)) अणु
		pr_info("DSM method does not support forward translate\n");
		वापस -ENODEV;
	पूर्ण

	params = adxl_dsm(ADXL_IDX_GET_ADDR_PARAMS, शून्य);
	अगर (!params) अणु
		pr_info("Failed to get component names\n");
		वापस -ENODEV;
	पूर्ण

	p = params->package.elements + 1;
	adxl_count = p->package.count;
	अगर (adxl_count > ADXL_MAX_COMPONENTS) अणु
		pr_info("Insane number of address component names %d\n", adxl_count);
		ACPI_FREE(params);
		वापस -ENODEV;
	पूर्ण
	p = p->package.elements;

	/*
	 * Allocate one extra क्रम शून्य termination.
	 */
	adxl_component_names = kसुस्मृति(adxl_count + 1, माप(अक्षर *), GFP_KERNEL);
	अगर (!adxl_component_names) अणु
		ACPI_FREE(params);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < adxl_count; i++)
		adxl_component_names[i] = p[i].string.poपूर्णांकer;

	वापस 0;
पूर्ण
subsys_initcall(adxl_init);
