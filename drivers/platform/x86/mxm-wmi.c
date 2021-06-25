<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MXM WMI driver
 *
 * Copyright(C) 2010 Red Hat.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/mxm-wmi.h>
#समावेश <linux/acpi.h>

MODULE_AUTHOR("Dave Airlie");
MODULE_DESCRIPTION("MXM WMI Driver");
MODULE_LICENSE("GPL");

#घोषणा MXM_WMMX_GUID "F6CB5C3C-9CAE-4EBD-B577-931EA32A2CC0"

MODULE_ALIAS("wmi:"MXM_WMMX_GUID);

#घोषणा MXM_WMMX_FUNC_MXDS 0x5344584D /* "MXDS" */
#घोषणा MXM_WMMX_FUNC_MXMX 0x53445344 /* "MXMX" */

काष्ठा mxds_args अणु
	u32 func;
	u32 args;
	u32 xarg;
पूर्ण;

पूर्णांक mxm_wmi_call_mxds(पूर्णांक adapter)
अणु
	काष्ठा mxds_args args = अणु
		.func = MXM_WMMX_FUNC_MXDS,
		.args = 0,
		.xarg = 1,
	पूर्ण;
	काष्ठा acpi_buffer input = अणु (acpi_size)माप(args), &args पूर्ण;
	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	acpi_status status;

	prपूर्णांकk("calling mux switch %d\n", adapter);

	status = wmi_evaluate_method(MXM_WMMX_GUID, 0x0, adapter, &input,
				     &output);

	अगर (ACPI_FAILURE(status))
		वापस status;

	prपूर्णांकk("mux switched %d\n", status);
	वापस 0;
			    
पूर्ण
EXPORT_SYMBOL_GPL(mxm_wmi_call_mxds);

पूर्णांक mxm_wmi_call_mxmx(पूर्णांक adapter)
अणु
	काष्ठा mxds_args args = अणु
		.func = MXM_WMMX_FUNC_MXMX,
		.args = 0,
		.xarg = 1,
	पूर्ण;
	काष्ठा acpi_buffer input = अणु (acpi_size)माप(args), &args पूर्ण;
	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	acpi_status status;

	prपूर्णांकk("calling mux switch %d\n", adapter);

	status = wmi_evaluate_method(MXM_WMMX_GUID, 0x0, adapter, &input,
				     &output);

	अगर (ACPI_FAILURE(status))
		वापस status;

	prपूर्णांकk("mux mutex set switched %d\n", status);
	वापस 0;
			    
पूर्ण
EXPORT_SYMBOL_GPL(mxm_wmi_call_mxmx);

bool mxm_wmi_supported(व्योम)
अणु
	bool guid_valid;
	guid_valid = wmi_has_guid(MXM_WMMX_GUID);
	वापस guid_valid;
पूर्ण
EXPORT_SYMBOL_GPL(mxm_wmi_supported);

अटल पूर्णांक __init mxm_wmi_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __निकास mxm_wmi_निकास(व्योम)
अणु
पूर्ण

module_init(mxm_wmi_init);
module_निकास(mxm_wmi_निकास);
