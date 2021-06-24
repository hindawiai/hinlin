<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* sstate.c: System soft state support.
 *
 * Copyright (C) 2007, 2008 David S. Miller <davem@davemloft.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/spitfire.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/head.h>
#समावेश <यंत्र/पन.स>

#समावेश "kernel.h"

अटल पूर्णांक hv_supports_soft_state;

अटल व्योम करो_set_sstate(अचिन्हित दीर्घ state, स्थिर अक्षर *msg)
अणु
	अचिन्हित दीर्घ err;

	अगर (!hv_supports_soft_state)
		वापस;

	err = sun4v_mach_set_soft_state(state, kimage_addr_to_ra(msg));
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "SSTATE: Failed to set soft-state to "
		       "state[%lx] msg[%s], err=%lu\n",
		       state, msg, err);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर booting_msg[32] __attribute__((aligned(32))) =
	"Linux booting";
अटल स्थिर अक्षर running_msg[32] __attribute__((aligned(32))) =
	"Linux running";
अटल स्थिर अक्षर halting_msg[32] __attribute__((aligned(32))) =
	"Linux halting";
अटल स्थिर अक्षर घातeroff_msg[32] __attribute__((aligned(32))) =
	"Linux powering off";
अटल स्थिर अक्षर rebooting_msg[32] __attribute__((aligned(32))) =
	"Linux rebooting";
अटल स्थिर अक्षर panicking_msg[32] __attribute__((aligned(32))) =
	"Linux panicking";

अटल पूर्णांक sstate_reboot_call(काष्ठा notअगरier_block *np, अचिन्हित दीर्घ type, व्योम *_unused)
अणु
	स्थिर अक्षर *msg;

	चयन (type) अणु
	हाल SYS_DOWN:
	शेष:
		msg = rebooting_msg;
		अवरोध;

	हाल SYS_HALT:
		msg = halting_msg;
		अवरोध;

	हाल SYS_POWER_OFF:
		msg = घातeroff_msg;
		अवरोध;
	पूर्ण

	करो_set_sstate(HV_SOFT_STATE_TRANSITION, msg);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block sstate_reboot_notअगरier = अणु
	.notअगरier_call = sstate_reboot_call,
पूर्ण;

अटल पूर्णांक sstate_panic_event(काष्ठा notअगरier_block *n, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	करो_set_sstate(HV_SOFT_STATE_TRANSITION, panicking_msg);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block sstate_panic_block = अणु
	.notअगरier_call	=	sstate_panic_event,
	.priority	=	पूर्णांक_उच्च,
पूर्ण;

अटल पूर्णांक __init sstate_init(व्योम)
अणु
	अचिन्हित दीर्घ major, minor;

	अगर (tlb_type != hypervisor)
		वापस 0;

	major = 1;
	minor = 0;
	अगर (sun4v_hvapi_रेजिस्टर(HV_GRP_SOFT_STATE, major, &minor))
		वापस 0;

	hv_supports_soft_state = 1;

	prom_sun4v_guest_soft_state();

	करो_set_sstate(HV_SOFT_STATE_TRANSITION, booting_msg);

	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
				       &sstate_panic_block);
	रेजिस्टर_reboot_notअगरier(&sstate_reboot_notअगरier);

	वापस 0;
पूर्ण

core_initcall(sstate_init);

अटल पूर्णांक __init sstate_running(व्योम)
अणु
	करो_set_sstate(HV_SOFT_STATE_NORMAL, running_msg);
	वापस 0;
पूर्ण

late_initcall(sstate_running);
