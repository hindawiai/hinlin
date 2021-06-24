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
#समावेश "lowlevel.h"
#समावेश "i2o.h"
#समावेश "dot_command.h"
#समावेश "remote.h"

अटल काष्ठा i2o_header header = I2O_HEADER_TEMPLATE;


पूर्णांक ibmयंत्र_send_i2o_message(काष्ठा service_processor *sp)
अणु
	u32 mfa;
	अचिन्हित पूर्णांक command_size;
	काष्ठा i2o_message *message;
	काष्ठा command *command = sp->current_command;

	mfa = get_mfa_inbound(sp->base_address);
	अगर (!mfa)
		वापस 1;

	command_size = get_करोt_command_size(command->buffer);
	header.message_size = outgoing_message_size(command_size);

	message = get_i2o_message(sp->base_address, mfa);

	स_नकल_toio(&message->header, &header, माप(काष्ठा i2o_header));
	स_नकल_toio(&message->data, command->buffer, command_size);

	set_mfa_inbound(sp->base_address, mfa);

	वापस 0;
पूर्ण

irqवापस_t ibmयंत्र_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम * dev_id)
अणु
	u32	mfa;
	काष्ठा service_processor *sp = (काष्ठा service_processor *)dev_id;
	व्योम __iomem *base_address = sp->base_address;
	अक्षर tsbuf[32];

	अगर (!sp_पूर्णांकerrupt_pending(base_address))
		वापस IRQ_NONE;

	dbg("respond to interrupt at %s\n", get_बारtamp(tsbuf));

	अगर (mouse_पूर्णांकerrupt_pending(sp)) अणु
		ibmयंत्र_handle_mouse_पूर्णांकerrupt(sp);
		clear_mouse_पूर्णांकerrupt(sp);
	पूर्ण

	mfa = get_mfa_outbound(base_address);
	अगर (valid_mfa(mfa)) अणु
		काष्ठा i2o_message *msg = get_i2o_message(base_address, mfa);
		ibmयंत्र_receive_message(sp, &msg->data, incoming_data_size(msg));
	पूर्ण अन्यथा
		dbg("didn't get a valid MFA\n");

	set_mfa_outbound(base_address, mfa);
	dbg("finished interrupt at   %s\n", get_बारtamp(tsbuf));

	वापस IRQ_HANDLED;
पूर्ण
