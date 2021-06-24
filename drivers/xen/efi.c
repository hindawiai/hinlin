<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * EFI support क्रम Xen.
 *
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 * Copyright (C) 1999-2002 Hewlett-Packard Co.
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Stephane Eranian <eranian@hpl.hp.com>
 * Copyright (C) 2005-2008 Intel Co.
 *	Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 *	Bibo Mao <bibo.mao@पूर्णांकel.com>
 *	Chandramouli Narayanan <mouli@linux.पूर्णांकel.com>
 *	Huang Ying <ying.huang@पूर्णांकel.com>
 * Copyright (C) 2011 Novell Co.
 *	Jan Beulich <JBeulich@suse.com>
 * Copyright (C) 2011-2012 Oracle Co.
 *	Liang Tang <liang.tang@oracle.com>
 * Copyright (c) 2014 Oracle Co., Daniel Kiper
 */

#समावेश <linux/bug.h>
#समावेश <linux/efi.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>

#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/platक्रमm.h>
#समावेश <xen/xen.h>
#समावेश <xen/xen-ops.h>

#समावेश <यंत्र/page.h>

#समावेश <यंत्र/xen/hypercall.h>

#घोषणा INIT_EFI_OP(name) \
	अणु.cmd = XENPF_efi_runसमय_call, \
	 .u.efi_runसमय_call.function = XEN_EFI_##name, \
	 .u.efi_runसमय_call.misc = 0पूर्ण

#घोषणा efi_data(op)	(op.u.efi_runसमय_call)

अटल efi_status_t xen_efi_get_समय(efi_समय_प्रकार *पंचांग, efi_समय_cap_t *tc)
अणु
	काष्ठा xen_platक्रमm_op op = INIT_EFI_OP(get_समय);

	अगर (HYPERVISOR_platक्रमm_op(&op) < 0)
		वापस EFI_UNSUPPORTED;

	अगर (पंचांग) अणु
		BUILD_BUG_ON(माप(*पंचांग) != माप(efi_data(op).u.get_समय.समय));
		स_नकल(पंचांग, &efi_data(op).u.get_समय.समय, माप(*पंचांग));
	पूर्ण

	अगर (tc) अणु
		tc->resolution = efi_data(op).u.get_समय.resolution;
		tc->accuracy = efi_data(op).u.get_समय.accuracy;
		tc->sets_to_zero = !!(efi_data(op).misc &
				      XEN_EFI_GET_TIME_SET_CLEARS_NS);
	पूर्ण

	वापस efi_data(op).status;
पूर्ण

अटल efi_status_t xen_efi_set_समय(efi_समय_प्रकार *पंचांग)
अणु
	काष्ठा xen_platक्रमm_op op = INIT_EFI_OP(set_समय);

	BUILD_BUG_ON(माप(*पंचांग) != माप(efi_data(op).u.set_समय));
	स_नकल(&efi_data(op).u.set_समय, पंचांग, माप(*पंचांग));

	अगर (HYPERVISOR_platक्रमm_op(&op) < 0)
		वापस EFI_UNSUPPORTED;

	वापस efi_data(op).status;
पूर्ण

अटल efi_status_t xen_efi_get_wakeup_समय(efi_bool_t *enabled,
					    efi_bool_t *pending,
					    efi_समय_प्रकार *पंचांग)
अणु
	काष्ठा xen_platक्रमm_op op = INIT_EFI_OP(get_wakeup_समय);

	अगर (HYPERVISOR_platक्रमm_op(&op) < 0)
		वापस EFI_UNSUPPORTED;

	अगर (पंचांग) अणु
		BUILD_BUG_ON(माप(*पंचांग) != माप(efi_data(op).u.get_wakeup_समय));
		स_नकल(पंचांग, &efi_data(op).u.get_wakeup_समय, माप(*पंचांग));
	पूर्ण

	अगर (enabled)
		*enabled = !!(efi_data(op).misc & XEN_EFI_GET_WAKEUP_TIME_ENABLED);

	अगर (pending)
		*pending = !!(efi_data(op).misc & XEN_EFI_GET_WAKEUP_TIME_PENDING);

	वापस efi_data(op).status;
पूर्ण

अटल efi_status_t xen_efi_set_wakeup_समय(efi_bool_t enabled, efi_समय_प्रकार *पंचांग)
अणु
	काष्ठा xen_platक्रमm_op op = INIT_EFI_OP(set_wakeup_समय);

	BUILD_BUG_ON(माप(*पंचांग) != माप(efi_data(op).u.set_wakeup_समय));
	अगर (enabled)
		efi_data(op).misc = XEN_EFI_SET_WAKEUP_TIME_ENABLE;
	अगर (पंचांग)
		स_नकल(&efi_data(op).u.set_wakeup_समय, पंचांग, माप(*पंचांग));
	अन्यथा
		efi_data(op).misc |= XEN_EFI_SET_WAKEUP_TIME_ENABLE_ONLY;

	अगर (HYPERVISOR_platक्रमm_op(&op) < 0)
		वापस EFI_UNSUPPORTED;

	वापस efi_data(op).status;
पूर्ण

अटल efi_status_t xen_efi_get_variable(efi_अक्षर16_t *name, efi_guid_t *venकरोr,
					 u32 *attr, अचिन्हित दीर्घ *data_size,
					 व्योम *data)
अणु
	काष्ठा xen_platक्रमm_op op = INIT_EFI_OP(get_variable);

	set_xen_guest_handle(efi_data(op).u.get_variable.name, name);
	BUILD_BUG_ON(माप(*venकरोr) !=
		     माप(efi_data(op).u.get_variable.venकरोr_guid));
	स_नकल(&efi_data(op).u.get_variable.venकरोr_guid, venकरोr, माप(*venकरोr));
	efi_data(op).u.get_variable.size = *data_size;
	set_xen_guest_handle(efi_data(op).u.get_variable.data, data);

	अगर (HYPERVISOR_platक्रमm_op(&op) < 0)
		वापस EFI_UNSUPPORTED;

	*data_size = efi_data(op).u.get_variable.size;
	अगर (attr)
		*attr = efi_data(op).misc;

	वापस efi_data(op).status;
पूर्ण

अटल efi_status_t xen_efi_get_next_variable(अचिन्हित दीर्घ *name_size,
					      efi_अक्षर16_t *name,
					      efi_guid_t *venकरोr)
अणु
	काष्ठा xen_platक्रमm_op op = INIT_EFI_OP(get_next_variable_name);

	efi_data(op).u.get_next_variable_name.size = *name_size;
	set_xen_guest_handle(efi_data(op).u.get_next_variable_name.name, name);
	BUILD_BUG_ON(माप(*venकरोr) !=
		     माप(efi_data(op).u.get_next_variable_name.venकरोr_guid));
	स_नकल(&efi_data(op).u.get_next_variable_name.venकरोr_guid, venकरोr,
	       माप(*venकरोr));

	अगर (HYPERVISOR_platक्रमm_op(&op) < 0)
		वापस EFI_UNSUPPORTED;

	*name_size = efi_data(op).u.get_next_variable_name.size;
	स_नकल(venकरोr, &efi_data(op).u.get_next_variable_name.venकरोr_guid,
	       माप(*venकरोr));

	वापस efi_data(op).status;
पूर्ण

अटल efi_status_t xen_efi_set_variable(efi_अक्षर16_t *name, efi_guid_t *venकरोr,
					 u32 attr, अचिन्हित दीर्घ data_size,
					 व्योम *data)
अणु
	काष्ठा xen_platक्रमm_op op = INIT_EFI_OP(set_variable);

	set_xen_guest_handle(efi_data(op).u.set_variable.name, name);
	efi_data(op).misc = attr;
	BUILD_BUG_ON(माप(*venकरोr) !=
		     माप(efi_data(op).u.set_variable.venकरोr_guid));
	स_नकल(&efi_data(op).u.set_variable.venकरोr_guid, venकरोr, माप(*venकरोr));
	efi_data(op).u.set_variable.size = data_size;
	set_xen_guest_handle(efi_data(op).u.set_variable.data, data);

	अगर (HYPERVISOR_platक्रमm_op(&op) < 0)
		वापस EFI_UNSUPPORTED;

	वापस efi_data(op).status;
पूर्ण

अटल efi_status_t xen_efi_query_variable_info(u32 attr, u64 *storage_space,
						u64 *reमुख्यing_space,
						u64 *max_variable_size)
अणु
	काष्ठा xen_platक्रमm_op op = INIT_EFI_OP(query_variable_info);

	अगर (efi.runसमय_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		वापस EFI_UNSUPPORTED;

	efi_data(op).u.query_variable_info.attr = attr;

	अगर (HYPERVISOR_platक्रमm_op(&op) < 0)
		वापस EFI_UNSUPPORTED;

	*storage_space = efi_data(op).u.query_variable_info.max_store_size;
	*reमुख्यing_space = efi_data(op).u.query_variable_info.reमुख्य_store_size;
	*max_variable_size = efi_data(op).u.query_variable_info.max_size;

	वापस efi_data(op).status;
पूर्ण

अटल efi_status_t xen_efi_get_next_high_mono_count(u32 *count)
अणु
	काष्ठा xen_platक्रमm_op op = INIT_EFI_OP(get_next_high_monotonic_count);

	अगर (HYPERVISOR_platक्रमm_op(&op) < 0)
		वापस EFI_UNSUPPORTED;

	*count = efi_data(op).misc;

	वापस efi_data(op).status;
पूर्ण

अटल efi_status_t xen_efi_update_capsule(efi_capsule_header_t **capsules,
				अचिन्हित दीर्घ count, अचिन्हित दीर्घ sg_list)
अणु
	काष्ठा xen_platक्रमm_op op = INIT_EFI_OP(update_capsule);

	अगर (efi.runसमय_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		वापस EFI_UNSUPPORTED;

	set_xen_guest_handle(efi_data(op).u.update_capsule.capsule_header_array,
			     capsules);
	efi_data(op).u.update_capsule.capsule_count = count;
	efi_data(op).u.update_capsule.sg_list = sg_list;

	अगर (HYPERVISOR_platक्रमm_op(&op) < 0)
		वापस EFI_UNSUPPORTED;

	वापस efi_data(op).status;
पूर्ण

अटल efi_status_t xen_efi_query_capsule_caps(efi_capsule_header_t **capsules,
			अचिन्हित दीर्घ count, u64 *max_size, पूर्णांक *reset_type)
अणु
	काष्ठा xen_platक्रमm_op op = INIT_EFI_OP(query_capsule_capabilities);

	अगर (efi.runसमय_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		वापस EFI_UNSUPPORTED;

	set_xen_guest_handle(efi_data(op).u.query_capsule_capabilities.capsule_header_array,
					capsules);
	efi_data(op).u.query_capsule_capabilities.capsule_count = count;

	अगर (HYPERVISOR_platक्रमm_op(&op) < 0)
		वापस EFI_UNSUPPORTED;

	*max_size = efi_data(op).u.query_capsule_capabilities.max_capsule_size;
	*reset_type = efi_data(op).u.query_capsule_capabilities.reset_type;

	वापस efi_data(op).status;
पूर्ण

अटल व्योम xen_efi_reset_प्रणाली(पूर्णांक reset_type, efi_status_t status,
				 अचिन्हित दीर्घ data_size, efi_अक्षर16_t *data)
अणु
	चयन (reset_type) अणु
	हाल EFI_RESET_COLD:
	हाल EFI_RESET_WARM:
		xen_reboot(SHUTDOWN_reboot);
		अवरोध;
	हाल EFI_RESET_SHUTDOWN:
		xen_reboot(SHUTDOWN_घातeroff);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * Set XEN EFI runसमय services function poपूर्णांकers. Other fields of काष्ठा efi,
 * e.g. efi.systab, will be set like normal EFI.
 */
व्योम __init xen_efi_runसमय_setup(व्योम)
अणु
	efi.get_समय			= xen_efi_get_समय;
	efi.set_समय			= xen_efi_set_समय;
	efi.get_wakeup_समय		= xen_efi_get_wakeup_समय;
	efi.set_wakeup_समय		= xen_efi_set_wakeup_समय;
	efi.get_variable		= xen_efi_get_variable;
	efi.get_next_variable		= xen_efi_get_next_variable;
	efi.set_variable		= xen_efi_set_variable;
	efi.set_variable_nonblocking	= xen_efi_set_variable;
	efi.query_variable_info		= xen_efi_query_variable_info;
	efi.query_variable_info_nonblocking = xen_efi_query_variable_info;
	efi.update_capsule		= xen_efi_update_capsule;
	efi.query_capsule_caps		= xen_efi_query_capsule_caps;
	efi.get_next_high_mono_count	= xen_efi_get_next_high_mono_count;
	efi.reset_प्रणाली		= xen_efi_reset_प्रणाली;
पूर्ण
