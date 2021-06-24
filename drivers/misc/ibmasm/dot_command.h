<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * IBM ASM Service Processor Device Driver
 *
 * Copyright (C) IBM Corporation, 2004
 *
 * Author: Max Asbथघck <amax@us.ibm.com>
 */

#अगर_अघोषित __DOT_COMMAND_H__
#घोषणा __DOT_COMMAND_H__

/*
 * करोt commands are the protocol used to communicate with the service
 * processor.
 * They consist of header, a command of variable length and data of
 * variable length.
 */

/* करोt command types */
#घोषणा sp_ग_लिखो		0
#घोषणा sp_ग_लिखो_next		1
#घोषणा sp_पढ़ो			2
#घोषणा sp_पढ़ो_next		3
#घोषणा sp_command_response	4
#घोषणा sp_event		5
#घोषणा sp_heartbeat		6

#आशय pack(1)
काष्ठा करोt_command_header अणु
	u8	type;
	u8	command_size;
	u16	data_size;
	u8	status;
	u8	reserved;
पूर्ण;
#आशय pack()

अटल अंतरभूत माप_प्रकार get_करोt_command_size(व्योम *buffer)
अणु
	काष्ठा करोt_command_header *cmd = (काष्ठा करोt_command_header *)buffer;
	वापस माप(काष्ठा करोt_command_header) + cmd->command_size + cmd->data_size;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_करोt_command_समयout(व्योम *buffer)
अणु
	काष्ठा करोt_command_header *header = (काष्ठा करोt_command_header *)buffer;
	अचिन्हित अक्षर *cmd = buffer + माप(काष्ठा करोt_command_header);

	/* करोt commands 6.3.1, 7.1 and 8.x need a दीर्घer समयout */

	अगर (header->command_size == 3) अणु
		अगर ((cmd[0] == 6) && (cmd[1] == 3) && (cmd[2] == 1))
			वापस IBMASM_CMD_TIMEOUT_EXTRA;
	पूर्ण अन्यथा अगर (header->command_size == 2) अणु
		अगर ((cmd[0] == 7) && (cmd[1] == 1))
			वापस IBMASM_CMD_TIMEOUT_EXTRA;
		अगर (cmd[0] == 8)
			वापस IBMASM_CMD_TIMEOUT_EXTRA;
	पूर्ण
	वापस IBMASM_CMD_TIMEOUT_NORMAL;
पूर्ण

#पूर्ण_अगर /* __DOT_COMMAND_H__ */
