<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>

#समावेश <xen/xen.h>
#समावेश <xen/hvm.h>
#समावेश <xen/features.h>
#समावेश <xen/पूर्णांकerface/features.h>

#समावेश "xen-ops.h"

व्योम xen_hvm_post_suspend(पूर्णांक suspend_cancelled)
अणु
	अगर (!suspend_cancelled) अणु
		xen_hvm_init_shared_info();
		xen_vcpu_restore();
	पूर्ण
	xen_setup_callback_vector();
	xen_unplug_emulated_devices();
पूर्ण
