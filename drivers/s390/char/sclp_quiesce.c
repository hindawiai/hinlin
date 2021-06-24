<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *     संकेत quiesce handler
 *
 *  Copyright IBM Corp. 1999, 2004
 *  Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 *             Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/smp.h>
#समावेश <linux/init.h>
#समावेश <linux/reboot.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/smp.h>

#समावेश "sclp.h"

अटल व्योम (*old_machine_restart)(अक्षर *);
अटल व्योम (*old_machine_halt)(व्योम);
अटल व्योम (*old_machine_घातer_off)(व्योम);

/* Shutकरोwn handler. Signal completion of shutकरोwn by loading special PSW. */
अटल व्योम करो_machine_quiesce(व्योम)
अणु
	psw_t quiesce_psw;

	smp_send_stop();
	quiesce_psw.mask =
		PSW_MASK_BASE | PSW_MASK_EA | PSW_MASK_BA | PSW_MASK_WAIT;
	quiesce_psw.addr = 0xfff;
	__load_psw(quiesce_psw);
पूर्ण

/* Handler क्रम quiesce event. Start shutकरोwn procedure. */
अटल व्योम sclp_quiesce_handler(काष्ठा evbuf_header *evbuf)
अणु
	अगर (_machine_restart != (व्योम *) करो_machine_quiesce) अणु
		old_machine_restart = _machine_restart;
		old_machine_halt = _machine_halt;
		old_machine_घातer_off = _machine_घातer_off;
		_machine_restart = (व्योम *) करो_machine_quiesce;
		_machine_halt = करो_machine_quiesce;
		_machine_घातer_off = करो_machine_quiesce;
	पूर्ण
	ctrl_alt_del();
पूर्ण

/* Unकरो machine restart/halt/घातer_off modअगरication on resume */
अटल व्योम sclp_quiesce_pm_event(काष्ठा sclp_रेजिस्टर *reg,
				  क्रमागत sclp_pm_event sclp_pm_event)
अणु
	चयन (sclp_pm_event) अणु
	हाल SCLP_PM_EVENT_RESTORE:
		अगर (old_machine_restart) अणु
			_machine_restart = old_machine_restart;
			_machine_halt = old_machine_halt;
			_machine_घातer_off = old_machine_घातer_off;
			old_machine_restart = शून्य;
			old_machine_halt = शून्य;
			old_machine_घातer_off = शून्य;
		पूर्ण
		अवरोध;
	हाल SCLP_PM_EVENT_FREEZE:
	हाल SCLP_PM_EVENT_THAW:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा sclp_रेजिस्टर sclp_quiesce_event = अणु
	.receive_mask = EVTYP_SIGQUIESCE_MASK,
	.receiver_fn = sclp_quiesce_handler,
	.pm_event_fn = sclp_quiesce_pm_event
पूर्ण;

/* Initialize quiesce driver. */
अटल पूर्णांक __init sclp_quiesce_init(व्योम)
अणु
	वापस sclp_रेजिस्टर(&sclp_quiesce_event);
पूर्ण
device_initcall(sclp_quiesce_init);
