<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * kmsg dumper that ensures the OPAL console fully flushes panic messages
 *
 * Author: Russell Currey <ruscur@russell.cc>
 *
 * Copyright 2015 IBM Corporation.
 */

#समावेश <linux/kmsg_dump.h>

#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/opal-api.h>

/*
 * Console output is controlled by OPAL firmware.  The kernel regularly calls
 * OPAL_POLL_EVENTS, which flushes some console output.  In a panic state,
 * however, the kernel no दीर्घer calls OPAL_POLL_EVENTS and the panic message
 * may not be completely prपूर्णांकed.  This function करोes not actually dump the
 * message, it just ensures that OPAL completely flushes the console buffer.
 */
अटल व्योम kmsg_dump_opal_console_flush(काष्ठा kmsg_dumper *dumper,
				     क्रमागत kmsg_dump_reason reason)
अणु
	/*
	 * Outside of a panic context the pollers will जारी to run,
	 * so we करोn't need to करो any special flushing.
	 */
	अगर (reason != KMSG_DUMP_PANIC)
		वापस;

	opal_flush_console(0);
पूर्ण

अटल काष्ठा kmsg_dumper opal_kmsg_dumper = अणु
	.dump = kmsg_dump_opal_console_flush
पूर्ण;

व्योम __init opal_kmsg_init(व्योम)
अणु
	पूर्णांक rc;

	/* Add our dumper to the list */
	rc = kmsg_dump_रेजिस्टर(&opal_kmsg_dumper);
	अगर (rc != 0)
		pr_err("opal: kmsg_dump_register failed; returned %d\n", rc);
पूर्ण
