<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2020 Linaro Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>

#समावेश "ipa.h"
#समावेश "ipa_clock.h"
#समावेश "ipa_uc.h"

/**
 * DOC:  The IPA embedded microcontroller
 *
 * The IPA incorporates a microcontroller that is able to करो some additional
 * handling/offloading of network activity.  The current code makes
 * essentially no use of the microcontroller, but it still requires some
 * initialization.  It needs to be notअगरied in the event the AP crashes.
 *
 * The microcontroller can generate two पूर्णांकerrupts to the AP.  One पूर्णांकerrupt
 * is used to indicate that a response to a request from the AP is available.
 * The other is used to notअगरy the AP of the occurrence of an event.  In
 * addition, the AP can पूर्णांकerrupt the microcontroller by writing a रेजिस्टर.
 *
 * A 128 byte block of काष्ठाured memory within the IPA SRAM is used together
 * with these पूर्णांकerrupts to implement the communication पूर्णांकerface between the
 * AP and the IPA microcontroller.  Each side ग_लिखोs data to the shared area
 * beक्रमe पूर्णांकerrupting its peer, which will पढ़ो the written data in response
 * to the पूर्णांकerrupt.  Some inक्रमmation found in the shared area is currently
 * unused.  All reमुख्यing space in the shared area is reserved, and must not
 * be पढ़ो or written by the AP.
 */
/* Supports hardware पूर्णांकerface version 0x2000 */

/* Delay to allow a the microcontroller to save state when crashing */
#घोषणा IPA_SEND_DELAY		100	/* microseconds */

/**
 * काष्ठा ipa_uc_mem_area - AP/microcontroller shared memory area
 * @command:		command code (AP->microcontroller)
 * @reserved0:		reserved bytes; aव्योम पढ़ोing or writing
 * @command_param:	low 32 bits of command parameter (AP->microcontroller)
 * @command_param_hi:	high 32 bits of command parameter (AP->microcontroller)
 *
 * @response:		response code (microcontroller->AP)
 * @reserved1:		reserved bytes; aव्योम पढ़ोing or writing
 * @response_param:	response parameter (microcontroller->AP)
 *
 * @event:		event code (microcontroller->AP)
 * @reserved2:		reserved bytes; aव्योम पढ़ोing or writing
 * @event_param:	event parameter (microcontroller->AP)
 *
 * @first_error_address: address of first error-source on SNOC
 * @hw_state:		state of hardware (including error type inक्रमmation)
 * @warning_counter:	counter of non-fatal hardware errors
 * @reserved3:		reserved bytes; aव्योम पढ़ोing or writing
 * @पूर्णांकerface_version:	hardware-reported पूर्णांकerface version
 * @reserved4:		reserved bytes; aव्योम पढ़ोing or writing
 *
 * A shared memory area at the base of IPA resident memory is used क्रम
 * communication with the microcontroller.  The region is 128 bytes in
 * size, but only the first 40 bytes (काष्ठाured this way) are used.
 */
काष्ठा ipa_uc_mem_area अणु
	u8 command;		/* क्रमागत ipa_uc_command */
	u8 reserved0[3];
	__le32 command_param;
	__le32 command_param_hi;
	u8 response;		/* क्रमागत ipa_uc_response */
	u8 reserved1[3];
	__le32 response_param;
	u8 event;		/* क्रमागत ipa_uc_event */
	u8 reserved2[3];

	__le32 event_param;
	__le32 first_error_address;
	u8 hw_state;
	u8 warning_counter;
	__le16 reserved3;
	__le16 पूर्णांकerface_version;
	__le16 reserved4;
पूर्ण;

/** क्रमागत ipa_uc_command - commands from the AP to the microcontroller */
क्रमागत ipa_uc_command अणु
	IPA_UC_COMMAND_NO_OP		= 0x0,
	IPA_UC_COMMAND_UPDATE_FLAGS	= 0x1,
	IPA_UC_COMMAND_DEBUG_RUN_TEST	= 0x2,
	IPA_UC_COMMAND_DEBUG_GET_INFO	= 0x3,
	IPA_UC_COMMAND_ERR_FATAL	= 0x4,
	IPA_UC_COMMAND_CLK_GATE		= 0x5,
	IPA_UC_COMMAND_CLK_UNGATE	= 0x6,
	IPA_UC_COMMAND_MEMCPY		= 0x7,
	IPA_UC_COMMAND_RESET_PIPE	= 0x8,
	IPA_UC_COMMAND_REG_WRITE	= 0x9,
	IPA_UC_COMMAND_GSI_CH_EMPTY	= 0xa,
पूर्ण;

/** क्रमागत ipa_uc_response - microcontroller response codes */
क्रमागत ipa_uc_response अणु
	IPA_UC_RESPONSE_NO_OP		= 0x0,
	IPA_UC_RESPONSE_INIT_COMPLETED	= 0x1,
	IPA_UC_RESPONSE_CMD_COMPLETED	= 0x2,
	IPA_UC_RESPONSE_DEBUG_GET_INFO	= 0x3,
पूर्ण;

/** क्रमागत ipa_uc_event - common cpu events reported by the microcontroller */
क्रमागत ipa_uc_event अणु
	IPA_UC_EVENT_NO_OP		= 0x0,
	IPA_UC_EVENT_ERROR		= 0x1,
	IPA_UC_EVENT_LOG_INFO		= 0x2,
पूर्ण;

अटल काष्ठा ipa_uc_mem_area *ipa_uc_shared(काष्ठा ipa *ipa)
अणु
	u32 offset = ipa->mem_offset + ipa->mem[IPA_MEM_UC_SHARED].offset;

	वापस ipa->mem_virt + offset;
पूर्ण

/* Microcontroller event IPA पूर्णांकerrupt handler */
अटल व्योम ipa_uc_event_handler(काष्ठा ipa *ipa, क्रमागत ipa_irq_id irq_id)
अणु
	काष्ठा ipa_uc_mem_area *shared = ipa_uc_shared(ipa);
	काष्ठा device *dev = &ipa->pdev->dev;

	अगर (shared->event == IPA_UC_EVENT_ERROR)
		dev_err(dev, "microcontroller error event\n");
	अन्यथा अगर (shared->event != IPA_UC_EVENT_LOG_INFO)
		dev_err(dev, "unsupported microcontroller event %hhu\n",
			shared->event);
	/* The LOG_INFO event can be safely ignored */
पूर्ण

/* Microcontroller response IPA पूर्णांकerrupt handler */
अटल व्योम ipa_uc_response_hdlr(काष्ठा ipa *ipa, क्रमागत ipa_irq_id irq_id)
अणु
	काष्ठा ipa_uc_mem_area *shared = ipa_uc_shared(ipa);

	/* An INIT_COMPLETED response message is sent to the AP by the
	 * microcontroller when it is operational.  Other than this, the AP
	 * should only receive responses from the microcontroller when it has
	 * sent it a request message.
	 *
	 * We can drop the घड़ी reference taken in ipa_uc_setup() once we
	 * know the microcontroller has finished its initialization.
	 */
	चयन (shared->response) अणु
	हाल IPA_UC_RESPONSE_INIT_COMPLETED:
		ipa->uc_loaded = true;
		ipa_घड़ी_put(ipa);
		अवरोध;
	शेष:
		dev_warn(&ipa->pdev->dev,
			 "unsupported microcontroller response %hhu\n",
			 shared->response);
		अवरोध;
	पूर्ण
पूर्ण

/* ipa_uc_setup() - Set up the microcontroller */
व्योम ipa_uc_setup(काष्ठा ipa *ipa)
अणु
	/* The microcontroller needs the IPA घड़ी running until it has
	 * completed its initialization.  It संकेतs this by sending an
	 * INIT_COMPLETED response message to the AP.  This could occur after
	 * we have finished करोing the rest of the IPA initialization, so we
	 * need to take an extra "proxy" reference, and hold it until we've
	 * received that संकेत.  (This reference is dropped in
	 * ipa_uc_response_hdlr(), above.)
	 */
	ipa_घड़ी_get(ipa);

	ipa->uc_loaded = false;
	ipa_पूर्णांकerrupt_add(ipa->पूर्णांकerrupt, IPA_IRQ_UC_0, ipa_uc_event_handler);
	ipa_पूर्णांकerrupt_add(ipa->पूर्णांकerrupt, IPA_IRQ_UC_1, ipa_uc_response_hdlr);
पूर्ण

/* Inverse of ipa_uc_setup() */
व्योम ipa_uc_tearकरोwn(काष्ठा ipa *ipa)
अणु
	ipa_पूर्णांकerrupt_हटाओ(ipa->पूर्णांकerrupt, IPA_IRQ_UC_1);
	ipa_पूर्णांकerrupt_हटाओ(ipa->पूर्णांकerrupt, IPA_IRQ_UC_0);
	अगर (!ipa->uc_loaded)
		ipa_घड़ी_put(ipa);
पूर्ण

/* Send a command to the microcontroller */
अटल व्योम send_uc_command(काष्ठा ipa *ipa, u32 command, u32 command_param)
अणु
	काष्ठा ipa_uc_mem_area *shared = ipa_uc_shared(ipa);
	u32 offset;
	u32 val;

	/* Fill in the command data */
	shared->command = command;
	shared->command_param = cpu_to_le32(command_param);
	shared->command_param_hi = 0;
	shared->response = 0;
	shared->response_param = 0;

	/* Use an पूर्णांकerrupt to tell the microcontroller the command is पढ़ोy */
	val = u32_encode_bits(1, UC_INTR_FMASK);
	offset = ipa_reg_irq_uc_offset(ipa->version);
	ioग_लिखो32(val, ipa->reg_virt + offset);
पूर्ण

/* Tell the microcontroller the AP is shutting करोwn */
व्योम ipa_uc_panic_notअगरier(काष्ठा ipa *ipa)
अणु
	अगर (!ipa->uc_loaded)
		वापस;

	send_uc_command(ipa, IPA_UC_COMMAND_ERR_FATAL, 0);

	/* give uc enough समय to save state */
	udelay(IPA_SEND_DELAY);
पूर्ण
