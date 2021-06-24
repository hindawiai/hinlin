<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IBM ASM Service Processor Device Driver
 *
 * Copyright (C) IBM Corporation, 2004
 *
 * Author: Max Asbथघck <amax@us.ibm.com>
 */

#समावेश "ibmasm.h"
#समावेश "dot_command.h"

/*
 * Dispatch an incoming message to the specअगरic handler क्रम the message.
 * Called from पूर्णांकerrupt context.
 */
व्योम ibmयंत्र_receive_message(काष्ठा service_processor *sp, व्योम *message, पूर्णांक message_size)
अणु
	u32 size;
	काष्ठा करोt_command_header *header = (काष्ठा करोt_command_header *)message;

	अगर (message_size == 0)
		वापस;

	size = get_करोt_command_size(message);
	अगर (size == 0)
		वापस;

	अगर (size > message_size)
		size = message_size;

	चयन (header->type) अणु
	हाल sp_event:
		ibmयंत्र_receive_event(sp, message, size);
		अवरोध;
	हाल sp_command_response:
		ibmयंत्र_receive_command_response(sp, message, size);
		अवरोध;
	हाल sp_heartbeat:
		ibmयंत्र_receive_heartbeat(sp, message, size);
		अवरोध;
	शेष:
		dev_err(sp->dev, "Received unknown message from service processor\n");
	पूर्ण
पूर्ण


#घोषणा INIT_BUFFER_SIZE 32


/*
 * send the 4.3.5.10 करोt command (driver VPD) to the service processor
 */
पूर्णांक ibmयंत्र_send_driver_vpd(काष्ठा service_processor *sp)
अणु
	काष्ठा command *command;
	काष्ठा करोt_command_header *header;
	u8 *vpd_command;
	u8 *vpd_data;
	पूर्णांक result = 0;

	command = ibmयंत्र_new_command(sp, INIT_BUFFER_SIZE);
	अगर (command == शून्य)
		वापस -ENOMEM;

	header = (काष्ठा करोt_command_header *)command->buffer;
	header->type                = sp_ग_लिखो;
	header->command_size        = 4;
	header->data_size           = 16;
	header->status              = 0;
	header->reserved            = 0;

	vpd_command = command->buffer + माप(काष्ठा करोt_command_header);
	vpd_command[0] = 0x4;
	vpd_command[1] = 0x3;
	vpd_command[2] = 0x5;
	vpd_command[3] = 0xa;

	vpd_data = vpd_command + header->command_size;
	vpd_data[0] = 0;
	म_जोड़ो(vpd_data, IBMASM_DRIVER_VPD);
	vpd_data[10] = 0;
	vpd_data[15] = 0;

	ibmयंत्र_exec_command(sp, command);
	ibmयंत्र_रुको_क्रम_response(command, IBMASM_CMD_TIMEOUT_NORMAL);

	अगर (command->status != IBMASM_CMD_COMPLETE)
		result = -ENODEV;

	command_put(command);

	वापस result;
पूर्ण

काष्ठा os_state_command अणु
	काष्ठा करोt_command_header	header;
	अचिन्हित अक्षर			command[3];
	अचिन्हित अक्षर			data;
पूर्ण;

/*
 * send the 4.3.6 करोt command (os state) to the service processor
 * During driver init this function is called with os state "up".
 * This causes the service processor to start sending heartbeats the
 * driver.
 * During driver निकास the function is called with os state "down",
 * causing the service processor to stop the heartbeats.
 */
पूर्णांक ibmयंत्र_send_os_state(काष्ठा service_processor *sp, पूर्णांक os_state)
अणु
	काष्ठा command *cmd;
	काष्ठा os_state_command *os_state_cmd;
	पूर्णांक result = 0;

	cmd = ibmयंत्र_new_command(sp, माप(काष्ठा os_state_command));
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	os_state_cmd = (काष्ठा os_state_command *)cmd->buffer;
	os_state_cmd->header.type		= sp_ग_लिखो;
	os_state_cmd->header.command_size	= 3;
	os_state_cmd->header.data_size		= 1;
	os_state_cmd->header.status		= 0;
	os_state_cmd->command[0]		= 4;
	os_state_cmd->command[1]		= 3;
	os_state_cmd->command[2]		= 6;
	os_state_cmd->data			= os_state;

	ibmयंत्र_exec_command(sp, cmd);
	ibmयंत्र_रुको_क्रम_response(cmd, IBMASM_CMD_TIMEOUT_NORMAL);

	अगर (cmd->status != IBMASM_CMD_COMPLETE)
		result = -ENODEV;

	command_put(cmd);
	वापस result;
पूर्ण
