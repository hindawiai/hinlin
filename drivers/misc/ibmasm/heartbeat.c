<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 * IBM ASM Service Processor Device Driver
 *
 * Copyright (C) IBM Corporation, 2004
 *
 * Author: Max Asbथघck <amax@us.ibm.com>
 */

#समावेश <linux/notअगरier.h>
#समावेश "ibmasm.h"
#समावेश "dot_command.h"
#समावेश "lowlevel.h"

अटल पूर्णांक suspend_heartbeats = 0;

/*
 * Once the driver indicates to the service processor that it is running
 * - see send_os_state() - the service processor sends periodic heartbeats
 * to the driver. The driver must respond to the heartbeats or अन्यथा the OS
 * will be rebooted.
 * In the हाल of a panic the पूर्णांकerrupt handler जारीs to work and thus
 * जारीs to respond to heartbeats, making the service processor believe
 * the OS is still running and thus preventing a reboot.
 * To prevent this from happening a callback is added the panic_notअगरier_list.
 * Beक्रमe responding to a heartbeat the driver checks अगर a panic has happened,
 * अगर yes it suspends heartbeat, causing the service processor to reboot as
 * expected.
 */
अटल पूर्णांक panic_happened(काष्ठा notअगरier_block *n, अचिन्हित दीर्घ val, व्योम *v)
अणु
	suspend_heartbeats = 1;
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block panic_notअगरier = अणु panic_happened, शून्य, 1 पूर्ण;

व्योम ibmयंत्र_रेजिस्टर_panic_notअगरier(व्योम)
अणु
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &panic_notअगरier);
पूर्ण

व्योम ibmयंत्र_unरेजिस्टर_panic_notअगरier(व्योम)
अणु
	atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list,
			&panic_notअगरier);
पूर्ण


पूर्णांक ibmयंत्र_heartbeat_init(काष्ठा service_processor *sp)
अणु
	sp->heartbeat = ibmयंत्र_new_command(sp, HEARTBEAT_BUFFER_SIZE);
	अगर (sp->heartbeat == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम ibmयंत्र_heartbeat_निकास(काष्ठा service_processor *sp)
अणु
	अक्षर tsbuf[32];

	dbg("%s:%d at %s\n", __func__, __LINE__, get_बारtamp(tsbuf));
	ibmयंत्र_रुको_क्रम_response(sp->heartbeat, IBMASM_CMD_TIMEOUT_NORMAL);
	dbg("%s:%d at %s\n", __func__, __LINE__, get_बारtamp(tsbuf));
	suspend_heartbeats = 1;
	command_put(sp->heartbeat);
पूर्ण

व्योम ibmयंत्र_receive_heartbeat(काष्ठा service_processor *sp,  व्योम *message, माप_प्रकार size)
अणु
	काष्ठा command *cmd = sp->heartbeat;
	काष्ठा करोt_command_header *header = (काष्ठा करोt_command_header *)cmd->buffer;
	अक्षर tsbuf[32];

	dbg("%s:%d at %s\n", __func__, __LINE__, get_बारtamp(tsbuf));
	अगर (suspend_heartbeats)
		वापस;

	/* वापस the received करोt command to sender */
	cmd->status = IBMASM_CMD_PENDING;
	size = min(size, cmd->buffer_size);
	स_नकल_fromio(cmd->buffer, message, size);
	header->type = sp_ग_लिखो;
	ibmयंत्र_exec_command(sp, cmd);
पूर्ण
