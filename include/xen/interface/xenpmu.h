<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __XEN_PUBLIC_XENPMU_H__
#घोषणा __XEN_PUBLIC_XENPMU_H__

#समावेश "xen.h"

#घोषणा XENPMU_VER_MAJ    0
#घोषणा XENPMU_VER_MIN    1

/*
 * ` क्रमागत neg_त्रुटि_संval
 * ` HYPERVISOR_xenpmu_op(क्रमागत xenpmu_op cmd, काष्ठा xenpmu_params *args);
 *
 * @cmd  == XENPMU_* (PMU operation)
 * @args == काष्ठा xenpmu_params
 */
/* ` क्रमागत xenpmu_op अणु */
#घोषणा XENPMU_mode_get        0 /* Also used क्रम getting PMU version */
#घोषणा XENPMU_mode_set        1
#घोषणा XENPMU_feature_get     2
#घोषणा XENPMU_feature_set     3
#घोषणा XENPMU_init            4
#घोषणा XENPMU_finish          5
#घोषणा XENPMU_lvtpc_set       6
#घोषणा XENPMU_flush           7

/* ` पूर्ण */

/* Parameters काष्ठाure क्रम HYPERVISOR_xenpmu_op call */
काष्ठा xen_pmu_params अणु
	/* IN/OUT parameters */
	काष्ठा अणु
		uपूर्णांक32_t maj;
		uपूर्णांक32_t min;
	पूर्ण version;
	uपूर्णांक64_t val;

	/* IN parameters */
	uपूर्णांक32_t vcpu;
	uपूर्णांक32_t pad;
पूर्ण;

/* PMU modes:
 * - XENPMU_MODE_OFF:   No PMU भवization
 * - XENPMU_MODE_SELF:  Guests can profile themselves
 * - XENPMU_MODE_HV:    Guests can profile themselves, करोm0 profiles
 *                      itself and Xen
 * - XENPMU_MODE_ALL:   Only करोm0 has access to VPMU and it profiles
 *                      everyone: itself, the hypervisor and the guests.
 */
#घोषणा XENPMU_MODE_OFF           0
#घोषणा XENPMU_MODE_SELF          (1<<0)
#घोषणा XENPMU_MODE_HV            (1<<1)
#घोषणा XENPMU_MODE_ALL           (1<<2)

/*
 * PMU features:
 * - XENPMU_FEATURE_INTEL_BTS: Intel BTS support (ignored on AMD)
 */
#घोषणा XENPMU_FEATURE_INTEL_BTS  1

/*
 * Shared PMU data between hypervisor and PV(H) करोमुख्यs.
 *
 * The hypervisor fills out this काष्ठाure during PMU पूर्णांकerrupt and sends an
 * पूर्णांकerrupt to appropriate VCPU.
 * Architecture-independent fields of xen_pmu_data are WO क्रम the hypervisor
 * and RO क्रम the guest but some fields in xen_pmu_arch can be writable
 * by both the hypervisor and the guest (see arch-$arch/pmu.h).
 */
काष्ठा xen_pmu_data अणु
	/* Interrupted VCPU */
	uपूर्णांक32_t vcpu_id;

	/*
	 * Physical processor on which the पूर्णांकerrupt occurred. On non-privileged
	 * guests set to vcpu_id;
	 */
	uपूर्णांक32_t pcpu_id;

	/*
	 * Doमुख्य that was पूर्णांकerrupted. On non-privileged guests set to
	 * DOMID_SELF.
	 * On privileged guests can be DOMID_SELF, DOMID_XEN, or, when in
	 * XENPMU_MODE_ALL mode, करोमुख्य ID of another करोमुख्य.
	 */
	करोmid_t  करोमुख्य_id;

	uपूर्णांक8_t pad[6];

	/* Architecture-specअगरic inक्रमmation */
	काष्ठा xen_pmu_arch pmu;
पूर्ण;

#पूर्ण_अगर /* __XEN_PUBLIC_XENPMU_H__ */
