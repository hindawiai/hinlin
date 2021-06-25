<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Architecture-specअगरic ACPI-based support क्रम suspend-to-idle.
 *
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 * Author: Srinivas Pandruvada <srinivas.pandruvada@linux.पूर्णांकel.com>
 * Author: Shyam Sundar S K <Shyam-sundar.S-k@amd.com>
 *
 * On platक्रमms supporting the Low Power S0 Idle पूर्णांकerface there is an ACPI
 * device object with the PNP0D80 compatible device ID (System Power Management
 * Controller) and a specअगरic _DSM method under it.  That method, अगर present,
 * can be used to indicate to the platक्रमm that the OS is transitioning पूर्णांकo a
 * low-घातer state in which certain types of activity are not desirable or that
 * it is leaving such a state, which allows the platक्रमm to adjust its operation
 * mode accordingly.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/suspend.h>

#समावेश "../sleep.h"

#अगर_घोषित CONFIG_SUSPEND

अटल bool sleep_no_lps0 __पढ़ो_mostly;
module_param(sleep_no_lps0, bool, 0644);
MODULE_PARM_DESC(sleep_no_lps0, "Do not use the special LPS0 device interface");

अटल स्थिर काष्ठा acpi_device_id lps0_device_ids[] = अणु
	अणु"PNP0D80", पूर्ण,
	अणु"", पूर्ण,
पूर्ण;

#घोषणा ACPI_LPS0_DSM_UUID	"c4eb40a0-6cd2-11e2-bcfd-0800200c9a66"

#घोषणा ACPI_LPS0_GET_DEVICE_CONSTRAINTS	1
#घोषणा ACPI_LPS0_SCREEN_OFF	3
#घोषणा ACPI_LPS0_SCREEN_ON	4
#घोषणा ACPI_LPS0_ENTRY		5
#घोषणा ACPI_LPS0_EXIT		6

/* AMD */
#घोषणा ACPI_LPS0_DSM_UUID_AMD      "e3f32452-febc-43ce-9039-932122d37721"
#घोषणा ACPI_LPS0_SCREEN_OFF_AMD    4
#घोषणा ACPI_LPS0_SCREEN_ON_AMD     5

अटल acpi_handle lps0_device_handle;
अटल guid_t lps0_dsm_guid;
अटल अक्षर lps0_dsm_func_mask;

/* Device स्थिरraपूर्णांक entry काष्ठाure */
काष्ठा lpi_device_info अणु
	अक्षर *name;
	पूर्णांक enabled;
	जोड़ acpi_object *package;
पूर्ण;

/* Constraपूर्णांक package काष्ठाure */
काष्ठा lpi_device_स्थिरraपूर्णांक अणु
	पूर्णांक uid;
	पूर्णांक min_dstate;
	पूर्णांक function_states;
पूर्ण;

काष्ठा lpi_स्थिरraपूर्णांकs अणु
	acpi_handle handle;
	पूर्णांक min_dstate;
पूर्ण;

/* AMD */
/* Device स्थिरraपूर्णांक entry काष्ठाure */
काष्ठा lpi_device_info_amd अणु
	पूर्णांक revision;
	पूर्णांक count;
	जोड़ acpi_object *package;
पूर्ण;

/* Constraपूर्णांक package काष्ठाure */
काष्ठा lpi_device_स्थिरraपूर्णांक_amd अणु
	अक्षर *name;
	पूर्णांक enabled;
	पूर्णांक function_states;
	पूर्णांक min_dstate;
पूर्ण;

अटल काष्ठा lpi_स्थिरraपूर्णांकs *lpi_स्थिरraपूर्णांकs_table;
अटल पूर्णांक lpi_स्थिरraपूर्णांकs_table_size;
अटल पूर्णांक rev_id;

अटल व्योम lpi_device_get_स्थिरraपूर्णांकs_amd(व्योम)
अणु
	जोड़ acpi_object *out_obj;
	पूर्णांक i, j, k;

	out_obj = acpi_evaluate_dsm_typed(lps0_device_handle, &lps0_dsm_guid,
					  1, ACPI_LPS0_GET_DEVICE_CONSTRAINTS,
					  शून्य, ACPI_TYPE_PACKAGE);

	अगर (!out_obj)
		वापस;

	acpi_handle_debug(lps0_device_handle, "_DSM function 1 eval %s\n",
			  out_obj ? "successful" : "failed");

	क्रम (i = 0; i < out_obj->package.count; i++) अणु
		जोड़ acpi_object *package = &out_obj->package.elements[i];

		अगर (package->type == ACPI_TYPE_PACKAGE) अणु
			lpi_स्थिरraपूर्णांकs_table = kसुस्मृति(package->package.count,
							माप(*lpi_स्थिरraपूर्णांकs_table),
							GFP_KERNEL);

			अगर (!lpi_स्थिरraपूर्णांकs_table)
				जाओ मुक्त_acpi_buffer;

			acpi_handle_debug(lps0_device_handle,
					  "LPI: constraints list begin:\n");

			क्रम (j = 0; j < package->package.count; ++j) अणु
				जोड़ acpi_object *info_obj = &package->package.elements[j];
				काष्ठा lpi_device_स्थिरraपूर्णांक_amd dev_info = अणुपूर्ण;
				काष्ठा lpi_स्थिरraपूर्णांकs *list;
				acpi_status status;

				क्रम (k = 0; k < info_obj->package.count; ++k) अणु
					जोड़ acpi_object *obj = &info_obj->package.elements[k];

					list = &lpi_स्थिरraपूर्णांकs_table[lpi_स्थिरraपूर्णांकs_table_size];
					list->min_dstate = -1;

					चयन (k) अणु
					हाल 0:
						dev_info.enabled = obj->पूर्णांकeger.value;
						अवरोध;
					हाल 1:
						dev_info.name = obj->string.poपूर्णांकer;
						अवरोध;
					हाल 2:
						dev_info.function_states = obj->पूर्णांकeger.value;
						अवरोध;
					हाल 3:
						dev_info.min_dstate = obj->पूर्णांकeger.value;
						अवरोध;
					पूर्ण

					अगर (!dev_info.enabled || !dev_info.name ||
					    !dev_info.min_dstate)
						जारी;

					status = acpi_get_handle(शून्य, dev_info.name,
								 &list->handle);
					अगर (ACPI_FAILURE(status))
						जारी;

					acpi_handle_debug(lps0_device_handle,
							  "Name:%s\n", dev_info.name);

					list->min_dstate = dev_info.min_dstate;

					अगर (list->min_dstate < 0) अणु
						acpi_handle_debug(lps0_device_handle,
								  "Incomplete constraint defined\n");
						जारी;
					पूर्ण
				पूर्ण
				lpi_स्थिरraपूर्णांकs_table_size++;
			पूर्ण
		पूर्ण
	पूर्ण

	acpi_handle_debug(lps0_device_handle, "LPI: constraints list end\n");

मुक्त_acpi_buffer:
	ACPI_FREE(out_obj);
पूर्ण

अटल व्योम lpi_device_get_स्थिरraपूर्णांकs(व्योम)
अणु
	जोड़ acpi_object *out_obj;
	पूर्णांक i;

	out_obj = acpi_evaluate_dsm_typed(lps0_device_handle, &lps0_dsm_guid,
					  1, ACPI_LPS0_GET_DEVICE_CONSTRAINTS,
					  शून्य, ACPI_TYPE_PACKAGE);

	acpi_handle_debug(lps0_device_handle, "_DSM function 1 eval %s\n",
			  out_obj ? "successful" : "failed");

	अगर (!out_obj)
		वापस;

	lpi_स्थिरraपूर्णांकs_table = kसुस्मृति(out_obj->package.count,
					माप(*lpi_स्थिरraपूर्णांकs_table),
					GFP_KERNEL);
	अगर (!lpi_स्थिरraपूर्णांकs_table)
		जाओ मुक्त_acpi_buffer;

	acpi_handle_debug(lps0_device_handle, "LPI: constraints list begin:\n");

	क्रम (i = 0; i < out_obj->package.count; i++) अणु
		काष्ठा lpi_स्थिरraपूर्णांकs *स्थिरraपूर्णांक;
		acpi_status status;
		जोड़ acpi_object *package = &out_obj->package.elements[i];
		काष्ठा lpi_device_info info = अणु पूर्ण;
		पूर्णांक package_count = 0, j;

		अगर (!package)
			जारी;

		क्रम (j = 0; j < package->package.count; ++j) अणु
			जोड़ acpi_object *element =
					&(package->package.elements[j]);

			चयन (element->type) अणु
			हाल ACPI_TYPE_INTEGER:
				info.enabled = element->पूर्णांकeger.value;
				अवरोध;
			हाल ACPI_TYPE_STRING:
				info.name = element->string.poपूर्णांकer;
				अवरोध;
			हाल ACPI_TYPE_PACKAGE:
				package_count = element->package.count;
				info.package = element->package.elements;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!info.enabled || !info.package || !info.name)
			जारी;

		स्थिरraपूर्णांक = &lpi_स्थिरraपूर्णांकs_table[lpi_स्थिरraपूर्णांकs_table_size];

		status = acpi_get_handle(शून्य, info.name, &स्थिरraपूर्णांक->handle);
		अगर (ACPI_FAILURE(status))
			जारी;

		acpi_handle_debug(lps0_device_handle,
				  "index:%d Name:%s\n", i, info.name);

		स्थिरraपूर्णांक->min_dstate = -1;

		क्रम (j = 0; j < package_count; ++j) अणु
			जोड़ acpi_object *info_obj = &info.package[j];
			जोड़ acpi_object *cnstr_pkg;
			जोड़ acpi_object *obj;
			काष्ठा lpi_device_स्थिरraपूर्णांक dev_info;

			चयन (info_obj->type) अणु
			हाल ACPI_TYPE_INTEGER:
				/* version */
				अवरोध;
			हाल ACPI_TYPE_PACKAGE:
				अगर (info_obj->package.count < 2)
					अवरोध;

				cnstr_pkg = info_obj->package.elements;
				obj = &cnstr_pkg[0];
				dev_info.uid = obj->पूर्णांकeger.value;
				obj = &cnstr_pkg[1];
				dev_info.min_dstate = obj->पूर्णांकeger.value;

				acpi_handle_debug(lps0_device_handle,
					"uid:%d min_dstate:%s\n",
					dev_info.uid,
					acpi_घातer_state_string(dev_info.min_dstate));

				स्थिरraपूर्णांक->min_dstate = dev_info.min_dstate;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (स्थिरraपूर्णांक->min_dstate < 0) अणु
			acpi_handle_debug(lps0_device_handle,
					  "Incomplete constraint defined\n");
			जारी;
		पूर्ण

		lpi_स्थिरraपूर्णांकs_table_size++;
	पूर्ण

	acpi_handle_debug(lps0_device_handle, "LPI: constraints list end\n");

मुक्त_acpi_buffer:
	ACPI_FREE(out_obj);
पूर्ण

अटल व्योम lpi_check_स्थिरraपूर्णांकs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < lpi_स्थिरraपूर्णांकs_table_size; ++i) अणु
		acpi_handle handle = lpi_स्थिरraपूर्णांकs_table[i].handle;
		काष्ठा acpi_device *adev;

		अगर (!handle || acpi_bus_get_device(handle, &adev))
			जारी;

		acpi_handle_debug(handle,
			"LPI: required min power state:%s current power state:%s\n",
			acpi_घातer_state_string(lpi_स्थिरraपूर्णांकs_table[i].min_dstate),
			acpi_घातer_state_string(adev->घातer.state));

		अगर (!adev->flags.घातer_manageable) अणु
			acpi_handle_info(handle, "LPI: Device not power manageable\n");
			lpi_स्थिरraपूर्णांकs_table[i].handle = शून्य;
			जारी;
		पूर्ण

		अगर (adev->घातer.state < lpi_स्थिरraपूर्णांकs_table[i].min_dstate)
			acpi_handle_info(handle,
				"LPI: Constraint not met; min power state:%s current power state:%s\n",
				acpi_घातer_state_string(lpi_स्थिरraपूर्णांकs_table[i].min_dstate),
				acpi_घातer_state_string(adev->घातer.state));
	पूर्ण
पूर्ण

अटल व्योम acpi_sleep_run_lps0_dsm(अचिन्हित पूर्णांक func)
अणु
	जोड़ acpi_object *out_obj;

	अगर (!(lps0_dsm_func_mask & (1 << func)))
		वापस;

	out_obj = acpi_evaluate_dsm(lps0_device_handle, &lps0_dsm_guid, rev_id, func, शून्य);
	ACPI_FREE(out_obj);

	acpi_handle_debug(lps0_device_handle, "_DSM function %u evaluation %s\n",
			  func, out_obj ? "successful" : "failed");
पूर्ण

अटल bool acpi_s2idle_venकरोr_amd(व्योम)
अणु
	वापस boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD;
पूर्ण

अटल पूर्णांक lps0_device_attach(काष्ठा acpi_device *adev,
			      स्थिर काष्ठा acpi_device_id *not_used)
अणु
	जोड़ acpi_object *out_obj;

	अगर (lps0_device_handle)
		वापस 0;

	अगर (!(acpi_gbl_FADT.flags & ACPI_FADT_LOW_POWER_S0))
		वापस 0;

	अगर (acpi_s2idle_venकरोr_amd()) अणु
		guid_parse(ACPI_LPS0_DSM_UUID_AMD, &lps0_dsm_guid);
		out_obj = acpi_evaluate_dsm(adev->handle, &lps0_dsm_guid, 0, 0, शून्य);
		rev_id = 0;
	पूर्ण अन्यथा अणु
		guid_parse(ACPI_LPS0_DSM_UUID, &lps0_dsm_guid);
		out_obj = acpi_evaluate_dsm(adev->handle, &lps0_dsm_guid, 1, 0, शून्य);
		rev_id = 1;
	पूर्ण

	/* Check अगर the _DSM is present and as expected. */
	अगर (!out_obj || out_obj->type != ACPI_TYPE_BUFFER) अणु
		acpi_handle_debug(adev->handle,
				  "_DSM function 0 evaluation failed\n");
		वापस 0;
	पूर्ण

	lps0_dsm_func_mask = *(अक्षर *)out_obj->buffer.poपूर्णांकer;

	ACPI_FREE(out_obj);

	acpi_handle_debug(adev->handle, "_DSM function mask: 0x%x\n",
			  lps0_dsm_func_mask);

	lps0_device_handle = adev->handle;

	अगर (acpi_s2idle_venकरोr_amd())
		lpi_device_get_स्थिरraपूर्णांकs_amd();
	अन्यथा
		lpi_device_get_स्थिरraपूर्णांकs();

	/*
	 * Use suspend-to-idle by शेष अगर the शेष suspend mode was not
	 * set from the command line.
	 */
	अगर (mem_sleep_शेष > PM_SUSPEND_MEM && !acpi_sleep_शेष_s3)
		mem_sleep_current = PM_SUSPEND_TO_IDLE;

	/*
	 * Some LPS0 प्रणालीs, like ASUS Zenbook UX430UNR/i7-8550U, require the
	 * EC GPE to be enabled जबतक suspended क्रम certain wakeup devices to
	 * work, so mark it as wakeup-capable.
	 */
	acpi_ec_mark_gpe_क्रम_wake();

	वापस 0;
पूर्ण

अटल काष्ठा acpi_scan_handler lps0_handler = अणु
	.ids = lps0_device_ids,
	.attach = lps0_device_attach,
पूर्ण;

पूर्णांक acpi_s2idle_prepare_late(व्योम)
अणु
	अगर (!lps0_device_handle || sleep_no_lps0)
		वापस 0;

	अगर (pm_debug_messages_on)
		lpi_check_स्थिरraपूर्णांकs();

	अगर (acpi_s2idle_venकरोr_amd()) अणु
		acpi_sleep_run_lps0_dsm(ACPI_LPS0_SCREEN_OFF_AMD);
	पूर्ण अन्यथा अणु
		acpi_sleep_run_lps0_dsm(ACPI_LPS0_SCREEN_OFF);
		acpi_sleep_run_lps0_dsm(ACPI_LPS0_ENTRY);
	पूर्ण

	वापस 0;
पूर्ण

व्योम acpi_s2idle_restore_early(व्योम)
अणु
	अगर (!lps0_device_handle || sleep_no_lps0)
		वापस;

	अगर (acpi_s2idle_venकरोr_amd()) अणु
		acpi_sleep_run_lps0_dsm(ACPI_LPS0_SCREEN_ON_AMD);
	पूर्ण अन्यथा अणु
		acpi_sleep_run_lps0_dsm(ACPI_LPS0_EXIT);
		acpi_sleep_run_lps0_dsm(ACPI_LPS0_SCREEN_ON);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा platक्रमm_s2idle_ops acpi_s2idle_ops_lps0 = अणु
	.begin = acpi_s2idle_begin,
	.prepare = acpi_s2idle_prepare,
	.prepare_late = acpi_s2idle_prepare_late,
	.wake = acpi_s2idle_wake,
	.restore_early = acpi_s2idle_restore_early,
	.restore = acpi_s2idle_restore,
	.end = acpi_s2idle_end,
पूर्ण;

व्योम acpi_s2idle_setup(व्योम)
अणु
	acpi_scan_add_handler(&lps0_handler);
	s2idle_set_ops(&acpi_s2idle_ops_lps0);
पूर्ण

#पूर्ण_अगर /* CONFIG_SUSPEND */
