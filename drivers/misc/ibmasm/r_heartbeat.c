<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 *
 * Copyright (C) IBM Corporation, 2004
 *
 * Author: Max Asbथघck <amax@us.ibm.com>
 */

#समावेश <linux/sched/संकेत.स>
#समावेश "ibmasm.h"
#समावेश "dot_command.h"

/*
 * Reverse Heartbeat, i.e. heartbeats sent from the driver to the
 * service processor.
 * These heartbeats are initiated by user level programs.
 */

/* the reverse heartbeat करोt command */
#आशय pack(1)
अटल काष्ठा अणु
	काष्ठा करोt_command_header	header;
	अचिन्हित अक्षर			command[3];
पूर्ण rhb_करोt_cmd = अणु
	.header = अणु
		.type =		sp_पढ़ो,
		.command_size = 3,
		.data_size =	0,
		.status =	0
	पूर्ण,
	.command = अणु 4, 3, 6 पूर्ण
पूर्ण;
#आशय pack()

व्योम ibmयंत्र_init_reverse_heartbeat(काष्ठा service_processor *sp, काष्ठा reverse_heartbeat *rhb)
अणु
	init_रुकोqueue_head(&rhb->रुको);
	rhb->stopped = 0;
पूर्ण

/*
 * start_reverse_heartbeat
 * Loop क्रमever, sending a reverse heartbeat करोt command to the service
 * processor, then sleeping. The loop comes to an end अगर the service
 * processor fails to respond 3 बार or we were पूर्णांकerrupted.
 */
पूर्णांक ibmयंत्र_start_reverse_heartbeat(काष्ठा service_processor *sp, काष्ठा reverse_heartbeat *rhb)
अणु
	काष्ठा command *cmd;
	पूर्णांक बार_failed = 0;
	पूर्णांक result = 1;

	cmd = ibmयंत्र_new_command(sp, माप rhb_करोt_cmd);
	अगर (!cmd)
		वापस -ENOMEM;

	जबतक (बार_failed < 3) अणु
		स_नकल(cmd->buffer, (व्योम *)&rhb_करोt_cmd, माप rhb_करोt_cmd);
		cmd->status = IBMASM_CMD_PENDING;
		ibmयंत्र_exec_command(sp, cmd);
		ibmयंत्र_रुको_क्रम_response(cmd, IBMASM_CMD_TIMEOUT_NORMAL);

		अगर (cmd->status != IBMASM_CMD_COMPLETE)
			बार_failed++;

		रुको_event_पूर्णांकerruptible_समयout(rhb->रुको,
			rhb->stopped,
			REVERSE_HEARTBEAT_TIMEOUT * HZ);

		अगर (संकेत_pending(current) || rhb->stopped) अणु
			result = -EINTR;
			अवरोध;
		पूर्ण
	पूर्ण
	command_put(cmd);
	rhb->stopped = 0;

	वापस result;
पूर्ण

व्योम ibmयंत्र_stop_reverse_heartbeat(काष्ठा reverse_heartbeat *rhb)
अणु
	rhb->stopped = 1;
	wake_up_पूर्णांकerruptible(&rhb->रुको);
पूर्ण
