<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * IBM ASM Service Processor Device Driver
 *
 * Copyright (C) IBM Corporation, 2004
 *
 * Author: Max Asbथघck <amax@us.ibm.com>
 */

#आशय pack(1)
काष्ठा i2o_header अणु
	u8	version;
	u8	message_flags;
	u16	message_size;
	u8	target;
	u8	initiator_and_target;
	u8	initiator;
	u8	function;
	u32	initiator_context;
पूर्ण;
#आशय pack()

#घोषणा I2O_HEADER_TEMPLATE \
      अणु .version              = 0x01, \
	.message_flags        = 0x00, \
	.function             = 0xFF, \
	.initiator            = 0x00, \
	.initiator_and_target = 0x40, \
	.target               = 0x00, \
	.initiator_context    = 0x0 पूर्ण

#घोषणा I2O_MESSAGE_SIZE	0x1000
#घोषणा I2O_COMMAND_SIZE	(I2O_MESSAGE_SIZE - माप(काष्ठा i2o_header))

#आशय pack(1)
काष्ठा i2o_message अणु
	काष्ठा i2o_header	header;
	व्योम			*data;
पूर्ण;
#आशय pack()

अटल अंतरभूत अचिन्हित लघु outgoing_message_size(अचिन्हित पूर्णांक data_size)
अणु
	अचिन्हित पूर्णांक size;
	अचिन्हित लघु i2o_size;

	अगर (data_size > I2O_COMMAND_SIZE)
		data_size = I2O_COMMAND_SIZE;

	size = माप(काष्ठा i2o_header) + data_size;

	i2o_size = size / माप(u32);

	अगर (size % माप(u32))
	       i2o_size++;

	वापस i2o_size;
पूर्ण

अटल अंतरभूत u32 incoming_data_size(काष्ठा i2o_message *i2o_message)
अणु
	वापस (माप(u32) * i2o_message->header.message_size);
पूर्ण
