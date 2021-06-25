<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 * IBM ASM Service Processor Device Driver
 *
 * Copyright (C) IBM Corporation, 2004
 *
 * Author: Max Asbथघck <amax@us.ibm.com>
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश "ibmasm.h"
#समावेश "lowlevel.h"

अटल व्योम exec_next_command(काष्ठा service_processor *sp);

अटल atomic_t command_count = ATOMIC_INIT(0);

काष्ठा command *ibmयंत्र_new_command(काष्ठा service_processor *sp, माप_प्रकार buffer_size)
अणु
	काष्ठा command *cmd;

	अगर (buffer_size > IBMASM_CMD_MAX_BUFFER_SIZE)
		वापस शून्य;

	cmd = kzalloc(माप(काष्ठा command), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस शून्य;


	cmd->buffer = kzalloc(buffer_size, GFP_KERNEL);
	अगर (cmd->buffer == शून्य) अणु
		kमुक्त(cmd);
		वापस शून्य;
	पूर्ण
	cmd->buffer_size = buffer_size;

	kref_init(&cmd->kref);
	cmd->lock = &sp->lock;

	cmd->status = IBMASM_CMD_PENDING;
	init_रुकोqueue_head(&cmd->रुको);
	INIT_LIST_HEAD(&cmd->queue_node);

	atomic_inc(&command_count);
	dbg("command count: %d\n", atomic_पढ़ो(&command_count));

	वापस cmd;
पूर्ण

व्योम ibmयंत्र_मुक्त_command(काष्ठा kref *kref)
अणु
	काष्ठा command *cmd = to_command(kref);

	list_del(&cmd->queue_node);
	atomic_dec(&command_count);
	dbg("command count: %d\n", atomic_पढ़ो(&command_count));
	kमुक्त(cmd->buffer);
	kमुक्त(cmd);
पूर्ण

अटल व्योम enqueue_command(काष्ठा service_processor *sp, काष्ठा command *cmd)
अणु
	list_add_tail(&cmd->queue_node, &sp->command_queue);
पूर्ण

अटल काष्ठा command *dequeue_command(काष्ठा service_processor *sp)
अणु
	काष्ठा command *cmd;
	काष्ठा list_head *next;

	अगर (list_empty(&sp->command_queue))
		वापस शून्य;

	next = sp->command_queue.next;
	list_del_init(next);
	cmd = list_entry(next, काष्ठा command, queue_node);

	वापस cmd;
पूर्ण

अटल अंतरभूत व्योम करो_exec_command(काष्ठा service_processor *sp)
अणु
	अक्षर tsbuf[32];

	dbg("%s:%d at %s\n", __func__, __LINE__, get_बारtamp(tsbuf));

	अगर (ibmयंत्र_send_i2o_message(sp)) अणु
		sp->current_command->status = IBMASM_CMD_FAILED;
		wake_up(&sp->current_command->रुको);
		command_put(sp->current_command);
		exec_next_command(sp);
	पूर्ण
पूर्ण

/*
 * exec_command
 * send a command to a service processor
 * Commands are executed sequentially. One command (sp->current_command)
 * is sent to the service processor. Once the पूर्णांकerrupt handler माला_लो a
 * message of type command_response, the message is copied पूर्णांकo
 * the current commands buffer,
 */
व्योम ibmयंत्र_exec_command(काष्ठा service_processor *sp, काष्ठा command *cmd)
अणु
	अचिन्हित दीर्घ flags;
	अक्षर tsbuf[32];

	dbg("%s:%d at %s\n", __func__, __LINE__, get_बारtamp(tsbuf));

	spin_lock_irqsave(&sp->lock, flags);

	अगर (!sp->current_command) अणु
		sp->current_command = cmd;
		command_get(sp->current_command);
		spin_unlock_irqrestore(&sp->lock, flags);
		करो_exec_command(sp);
	पूर्ण अन्यथा अणु
		enqueue_command(sp, cmd);
		spin_unlock_irqrestore(&sp->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम exec_next_command(काष्ठा service_processor *sp)
अणु
	अचिन्हित दीर्घ flags;
	अक्षर tsbuf[32];

	dbg("%s:%d at %s\n", __func__, __LINE__, get_बारtamp(tsbuf));

	spin_lock_irqsave(&sp->lock, flags);
	sp->current_command = dequeue_command(sp);
	अगर (sp->current_command) अणु
		command_get(sp->current_command);
		spin_unlock_irqrestore(&sp->lock, flags);
		करो_exec_command(sp);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&sp->lock, flags);
	पूर्ण
पूर्ण

/*
 * Sleep until a command has failed or a response has been received
 * and the command status been updated by the पूर्णांकerrupt handler.
 * (see receive_response).
 */
व्योम ibmयंत्र_रुको_क्रम_response(काष्ठा command *cmd, पूर्णांक समयout)
अणु
	रुको_event_पूर्णांकerruptible_समयout(cmd->रुको,
				cmd->status == IBMASM_CMD_COMPLETE ||
				cmd->status == IBMASM_CMD_FAILED,
				समयout * HZ);
पूर्ण

/*
 * receive_command_response
 * called by the पूर्णांकerrupt handler when a करोt command of type command_response
 * was received.
 */
व्योम ibmयंत्र_receive_command_response(काष्ठा service_processor *sp, व्योम *response, माप_प्रकार size)
अणु
	काष्ठा command *cmd = sp->current_command;

	अगर (!sp->current_command)
		वापस;

	स_नकल_fromio(cmd->buffer, response, min(size, cmd->buffer_size));
	cmd->status = IBMASM_CMD_COMPLETE;
	wake_up(&sp->current_command->रुको);
	command_put(sp->current_command);
	exec_next_command(sp);
पूर्ण
