<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hvcall.h>

#समावेश "hv-gpci.h"
#समावेश "hv-common.h"

अचिन्हित दीर्घ hv_perf_caps_get(काष्ठा hv_perf_caps *caps)
अणु
	अचिन्हित दीर्घ r;
	काष्ठा p अणु
		काष्ठा hv_get_perf_counter_info_params params;
		काष्ठा hv_gpci_प्रणाली_perक्रमmance_capabilities caps;
	पूर्ण __packed __aligned(माप(uपूर्णांक64_t));

	काष्ठा p arg = अणु
		.params = अणु
			.counter_request = cpu_to_be32(
				HV_GPCI_प्रणाली_perक्रमmance_capabilities),
			.starting_index = cpu_to_be32(-1),
			.counter_info_version_in = 0,
		पूर्ण
	पूर्ण;

	r = plpar_hcall_norets(H_GET_PERF_COUNTER_INFO,
			       virt_to_phys(&arg), माप(arg));

	अगर (r)
		वापस r;

	pr_devel("capability_mask: 0x%x\n", arg.caps.capability_mask);

	caps->version = arg.params.counter_info_version_out;
	caps->collect_privileged = !!arg.caps.perf_collect_privileged;
	caps->ga = !!(arg.caps.capability_mask & HV_GPCI_CM_GA);
	caps->expanded = !!(arg.caps.capability_mask & HV_GPCI_CM_EXPANDED);
	caps->lab = !!(arg.caps.capability_mask & HV_GPCI_CM_LAB);

	वापस r;
पूर्ण
