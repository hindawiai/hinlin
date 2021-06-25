<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ipmi_smic_sm.c
 *
 * The state-machine driver क्रम an IPMI SMIC driver
 *
 * It started as a copy of Corey Minyard's driver क्रम the KSC पूर्णांकerface
 * and the kernel patch "mmcdev-patch-245" by HP
 *
 * modअगरied by:	Hannes Schulz <schulz@schwaar.com>
 *		ipmi@schwaar.com
 *
 *
 * Corey Minyard's driver क्रम the KSC पूर्णांकerface has the following
 * copyright notice:
 *   Copyright 2002 MontaVista Software Inc.
 *
 * the kernel patch "mmcdev-patch-245" by HP has the following
 * copyright notice:
 * (c) Copyright 2001 Grant Grundler (c) Copyright
 * 2001 Hewlett-Packard Company
 */

#घोषणा DEBUG /* So dev_dbg() is always available. */

#समावेश <linux/kernel.h> /* For prपूर्णांकk. */
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/ipmi_msgdefs.h>		/* क्रम completion codes */
#समावेश "ipmi_si_sm.h"

/* smic_debug is a bit-field
 *	SMIC_DEBUG_ENABLE -	turned on क्रम now
 *	SMIC_DEBUG_MSG -	commands and their responses
 *	SMIC_DEBUG_STATES -	state machine
*/
#घोषणा SMIC_DEBUG_STATES	4
#घोषणा SMIC_DEBUG_MSG		2
#घोषणा	SMIC_DEBUG_ENABLE	1

अटल पूर्णांक smic_debug = 1;
module_param(smic_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(smic_debug, "debug bitmask, 1=enable, 2=messages, 4=states");

क्रमागत smic_states अणु
	SMIC_IDLE,
	SMIC_START_OP,
	SMIC_OP_OK,
	SMIC_WRITE_START,
	SMIC_WRITE_NEXT,
	SMIC_WRITE_END,
	SMIC_WRITE2READ,
	SMIC_READ_START,
	SMIC_READ_NEXT,
	SMIC_READ_END,
	SMIC_HOSED
पूर्ण;

#घोषणा MAX_SMIC_READ_SIZE 80
#घोषणा MAX_SMIC_WRITE_SIZE 80
#घोषणा SMIC_MAX_ERROR_RETRIES 3

/* Timeouts in microseconds. */
#घोषणा SMIC_RETRY_TIMEOUT (2*USEC_PER_SEC)

/* SMIC Flags Register Bits */
#घोषणा SMIC_RX_DATA_READY	0x80
#घोषणा SMIC_TX_DATA_READY	0x40

/*
 * SMIC_SMI and SMIC_EVM_DATA_AVAIL are only used by
 * a few प्रणालीs, and then only by Systems Management
 * Interrupts, not by the OS.  Always ignore these bits.
 *
 */
#घोषणा SMIC_SMI		0x10
#घोषणा SMIC_EVM_DATA_AVAIL	0x08
#घोषणा SMIC_SMS_DATA_AVAIL	0x04
#घोषणा SMIC_FLAG_BSY		0x01

/* SMIC Error Codes */
#घोषणा	EC_NO_ERROR		0x00
#घोषणा	EC_ABORTED		0x01
#घोषणा	EC_ILLEGAL_CONTROL	0x02
#घोषणा	EC_NO_RESPONSE		0x03
#घोषणा	EC_ILLEGAL_COMMAND	0x04
#घोषणा	EC_BUFFER_FULL		0x05

काष्ठा si_sm_data अणु
	क्रमागत smic_states state;
	काष्ठा si_sm_io *io;
	अचिन्हित अक्षर	 ग_लिखो_data[MAX_SMIC_WRITE_SIZE];
	पूर्णांक		 ग_लिखो_pos;
	पूर्णांक		 ग_लिखो_count;
	पूर्णांक		 orig_ग_लिखो_count;
	अचिन्हित अक्षर	 पढ़ो_data[MAX_SMIC_READ_SIZE];
	पूर्णांक		 पढ़ो_pos;
	पूर्णांक		 truncated;
	अचिन्हित पूर्णांक	 error_retries;
	दीर्घ		 smic_समयout;
पूर्ण;

अटल अचिन्हित पूर्णांक init_smic_data(काष्ठा si_sm_data *smic,
				   काष्ठा si_sm_io *io)
अणु
	smic->state = SMIC_IDLE;
	smic->io = io;
	smic->ग_लिखो_pos = 0;
	smic->ग_लिखो_count = 0;
	smic->orig_ग_लिखो_count = 0;
	smic->पढ़ो_pos = 0;
	smic->error_retries = 0;
	smic->truncated = 0;
	smic->smic_समयout = SMIC_RETRY_TIMEOUT;

	/* We use 3 bytes of I/O. */
	वापस 3;
पूर्ण

अटल पूर्णांक start_smic_transaction(काष्ठा si_sm_data *smic,
				  अचिन्हित अक्षर *data, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;

	अगर (size < 2)
		वापस IPMI_REQ_LEN_INVALID_ERR;
	अगर (size > MAX_SMIC_WRITE_SIZE)
		वापस IPMI_REQ_LEN_EXCEEDED_ERR;

	अगर ((smic->state != SMIC_IDLE) && (smic->state != SMIC_HOSED)) अणु
		dev_warn(smic->io->dev,
			 "SMIC in invalid state %d\n", smic->state);
		वापस IPMI_NOT_IN_MY_STATE_ERR;
	पूर्ण

	अगर (smic_debug & SMIC_DEBUG_MSG) अणु
		dev_dbg(smic->io->dev, "%s -", __func__);
		क्रम (i = 0; i < size; i++)
			pr_cont(" %02x", data[i]);
		pr_cont("\n");
	पूर्ण
	smic->error_retries = 0;
	स_नकल(smic->ग_लिखो_data, data, size);
	smic->ग_लिखो_count = size;
	smic->orig_ग_लिखो_count = size;
	smic->ग_लिखो_pos = 0;
	smic->पढ़ो_pos = 0;
	smic->state = SMIC_START_OP;
	smic->smic_समयout = SMIC_RETRY_TIMEOUT;
	वापस 0;
पूर्ण

अटल पूर्णांक smic_get_result(काष्ठा si_sm_data *smic,
			   अचिन्हित अक्षर *data, अचिन्हित पूर्णांक length)
अणु
	पूर्णांक i;

	अगर (smic_debug & SMIC_DEBUG_MSG) अणु
		dev_dbg(smic->io->dev, "smic_get result -");
		क्रम (i = 0; i < smic->पढ़ो_pos; i++)
			pr_cont(" %02x", smic->पढ़ो_data[i]);
		pr_cont("\n");
	पूर्ण
	अगर (length < smic->पढ़ो_pos) अणु
		smic->पढ़ो_pos = length;
		smic->truncated = 1;
	पूर्ण
	स_नकल(data, smic->पढ़ो_data, smic->पढ़ो_pos);

	अगर ((length >= 3) && (smic->पढ़ो_pos < 3)) अणु
		data[2] = IPMI_ERR_UNSPECIFIED;
		smic->पढ़ो_pos = 3;
	पूर्ण
	अगर (smic->truncated) अणु
		data[2] = IPMI_ERR_MSG_TRUNCATED;
		smic->truncated = 0;
	पूर्ण
	वापस smic->पढ़ो_pos;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर पढ़ो_smic_flags(काष्ठा si_sm_data *smic)
अणु
	वापस smic->io->inputb(smic->io, 2);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर पढ़ो_smic_status(काष्ठा si_sm_data *smic)
अणु
	वापस smic->io->inputb(smic->io, 1);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर पढ़ो_smic_data(काष्ठा si_sm_data *smic)
अणु
	वापस smic->io->inputb(smic->io, 0);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_smic_flags(काष्ठा si_sm_data *smic,
				    अचिन्हित अक्षर   flags)
अणु
	smic->io->outputb(smic->io, 2, flags);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_smic_control(काष्ठा si_sm_data *smic,
				      अचिन्हित अक्षर   control)
अणु
	smic->io->outputb(smic->io, 1, control);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_si_sm_data(काष्ठा si_sm_data *smic,
				    अचिन्हित अक्षर   data)
अणु
	smic->io->outputb(smic->io, 0, data);
पूर्ण

अटल अंतरभूत व्योम start_error_recovery(काष्ठा si_sm_data *smic, अक्षर *reason)
अणु
	(smic->error_retries)++;
	अगर (smic->error_retries > SMIC_MAX_ERROR_RETRIES) अणु
		अगर (smic_debug & SMIC_DEBUG_ENABLE)
			pr_warn("ipmi_smic_drv: smic hosed: %s\n", reason);
		smic->state = SMIC_HOSED;
	पूर्ण अन्यथा अणु
		smic->ग_लिखो_count = smic->orig_ग_लिखो_count;
		smic->ग_लिखो_pos = 0;
		smic->पढ़ो_pos = 0;
		smic->state = SMIC_START_OP;
		smic->smic_समयout = SMIC_RETRY_TIMEOUT;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_next_byte(काष्ठा si_sm_data *smic)
अणु
	ग_लिखो_si_sm_data(smic, smic->ग_लिखो_data[smic->ग_लिखो_pos]);
	(smic->ग_लिखो_pos)++;
	(smic->ग_लिखो_count)--;
पूर्ण

अटल अंतरभूत व्योम पढ़ो_next_byte(काष्ठा si_sm_data *smic)
अणु
	अगर (smic->पढ़ो_pos >= MAX_SMIC_READ_SIZE) अणु
		पढ़ो_smic_data(smic);
		smic->truncated = 1;
	पूर्ण अन्यथा अणु
		smic->पढ़ो_data[smic->पढ़ो_pos] = पढ़ो_smic_data(smic);
		smic->पढ़ो_pos++;
	पूर्ण
पूर्ण

/*  SMIC Control/Status Code Components */
#घोषणा	SMIC_GET_STATUS		0x00	/* Control क्रमm's name */
#घोषणा	SMIC_READY		0x00	/* Status  क्रमm's name */
#घोषणा	SMIC_WR_START		0x01	/* Unअगरied Control/Status names... */
#घोषणा	SMIC_WR_NEXT		0x02
#घोषणा	SMIC_WR_END		0x03
#घोषणा	SMIC_RD_START		0x04
#घोषणा	SMIC_RD_NEXT		0x05
#घोषणा	SMIC_RD_END		0x06
#घोषणा	SMIC_CODE_MASK		0x0f

#घोषणा	SMIC_CONTROL		0x00
#घोषणा	SMIC_STATUS		0x80
#घोषणा	SMIC_CS_MASK		0x80

#घोषणा	SMIC_SMS		0x40
#घोषणा	SMIC_SMM		0x60
#घोषणा	SMIC_STREAM_MASK	0x60

/*  SMIC Control Codes */
#घोषणा	SMIC_CC_SMS_GET_STATUS	(SMIC_CONTROL|SMIC_SMS|SMIC_GET_STATUS)
#घोषणा	SMIC_CC_SMS_WR_START	(SMIC_CONTROL|SMIC_SMS|SMIC_WR_START)
#घोषणा	SMIC_CC_SMS_WR_NEXT	(SMIC_CONTROL|SMIC_SMS|SMIC_WR_NEXT)
#घोषणा	SMIC_CC_SMS_WR_END	(SMIC_CONTROL|SMIC_SMS|SMIC_WR_END)
#घोषणा	SMIC_CC_SMS_RD_START	(SMIC_CONTROL|SMIC_SMS|SMIC_RD_START)
#घोषणा	SMIC_CC_SMS_RD_NEXT	(SMIC_CONTROL|SMIC_SMS|SMIC_RD_NEXT)
#घोषणा	SMIC_CC_SMS_RD_END	(SMIC_CONTROL|SMIC_SMS|SMIC_RD_END)

#घोषणा	SMIC_CC_SMM_GET_STATUS	(SMIC_CONTROL|SMIC_SMM|SMIC_GET_STATUS)
#घोषणा	SMIC_CC_SMM_WR_START	(SMIC_CONTROL|SMIC_SMM|SMIC_WR_START)
#घोषणा	SMIC_CC_SMM_WR_NEXT	(SMIC_CONTROL|SMIC_SMM|SMIC_WR_NEXT)
#घोषणा	SMIC_CC_SMM_WR_END	(SMIC_CONTROL|SMIC_SMM|SMIC_WR_END)
#घोषणा	SMIC_CC_SMM_RD_START	(SMIC_CONTROL|SMIC_SMM|SMIC_RD_START)
#घोषणा	SMIC_CC_SMM_RD_NEXT	(SMIC_CONTROL|SMIC_SMM|SMIC_RD_NEXT)
#घोषणा	SMIC_CC_SMM_RD_END	(SMIC_CONTROL|SMIC_SMM|SMIC_RD_END)

/*  SMIC Status Codes */
#घोषणा	SMIC_SC_SMS_READY	(SMIC_STATUS|SMIC_SMS|SMIC_READY)
#घोषणा	SMIC_SC_SMS_WR_START	(SMIC_STATUS|SMIC_SMS|SMIC_WR_START)
#घोषणा	SMIC_SC_SMS_WR_NEXT	(SMIC_STATUS|SMIC_SMS|SMIC_WR_NEXT)
#घोषणा	SMIC_SC_SMS_WR_END	(SMIC_STATUS|SMIC_SMS|SMIC_WR_END)
#घोषणा	SMIC_SC_SMS_RD_START	(SMIC_STATUS|SMIC_SMS|SMIC_RD_START)
#घोषणा	SMIC_SC_SMS_RD_NEXT	(SMIC_STATUS|SMIC_SMS|SMIC_RD_NEXT)
#घोषणा	SMIC_SC_SMS_RD_END	(SMIC_STATUS|SMIC_SMS|SMIC_RD_END)

#घोषणा	SMIC_SC_SMM_READY	(SMIC_STATUS|SMIC_SMM|SMIC_READY)
#घोषणा	SMIC_SC_SMM_WR_START	(SMIC_STATUS|SMIC_SMM|SMIC_WR_START)
#घोषणा	SMIC_SC_SMM_WR_NEXT	(SMIC_STATUS|SMIC_SMM|SMIC_WR_NEXT)
#घोषणा	SMIC_SC_SMM_WR_END	(SMIC_STATUS|SMIC_SMM|SMIC_WR_END)
#घोषणा	SMIC_SC_SMM_RD_START	(SMIC_STATUS|SMIC_SMM|SMIC_RD_START)
#घोषणा	SMIC_SC_SMM_RD_NEXT	(SMIC_STATUS|SMIC_SMM|SMIC_RD_NEXT)
#घोषणा	SMIC_SC_SMM_RD_END	(SMIC_STATUS|SMIC_SMM|SMIC_RD_END)

/* these are the control/status codes we actually use
	SMIC_CC_SMS_GET_STATUS	0x40
	SMIC_CC_SMS_WR_START	0x41
	SMIC_CC_SMS_WR_NEXT	0x42
	SMIC_CC_SMS_WR_END	0x43
	SMIC_CC_SMS_RD_START	0x44
	SMIC_CC_SMS_RD_NEXT	0x45
	SMIC_CC_SMS_RD_END	0x46

	SMIC_SC_SMS_READY	0xC0
	SMIC_SC_SMS_WR_START	0xC1
	SMIC_SC_SMS_WR_NEXT	0xC2
	SMIC_SC_SMS_WR_END	0xC3
	SMIC_SC_SMS_RD_START	0xC4
	SMIC_SC_SMS_RD_NEXT	0xC5
	SMIC_SC_SMS_RD_END	0xC6
*/

अटल क्रमागत si_sm_result smic_event(काष्ठा si_sm_data *smic, दीर्घ समय)
अणु
	अचिन्हित अक्षर status;
	अचिन्हित अक्षर flags;
	अचिन्हित अक्षर data;

	अगर (smic->state == SMIC_HOSED) अणु
		init_smic_data(smic, smic->io);
		वापस SI_SM_HOSED;
	पूर्ण
	अगर (smic->state != SMIC_IDLE) अणु
		अगर (smic_debug & SMIC_DEBUG_STATES)
			dev_dbg(smic->io->dev,
				"%s - smic->smic_timeout = %ld, time = %ld\n",
				__func__, smic->smic_समयout, समय);
		/*
		 * FIXME: smic_event is someबार called with समय >
		 * SMIC_RETRY_TIMEOUT
		 */
		अगर (समय < SMIC_RETRY_TIMEOUT) अणु
			smic->smic_समयout -= समय;
			अगर (smic->smic_समयout < 0) अणु
				start_error_recovery(smic, "smic timed out.");
				वापस SI_SM_CALL_WITH_DELAY;
			पूर्ण
		पूर्ण
	पूर्ण
	flags = पढ़ो_smic_flags(smic);
	अगर (flags & SMIC_FLAG_BSY)
		वापस SI_SM_CALL_WITH_DELAY;

	status = पढ़ो_smic_status(smic);
	अगर (smic_debug & SMIC_DEBUG_STATES)
		dev_dbg(smic->io->dev,
			"%s - state = %d, flags = 0x%02x, status = 0x%02x\n",
			__func__, smic->state, flags, status);

	चयन (smic->state) अणु
	हाल SMIC_IDLE:
		/* in IDLE we check क्रम available messages */
		अगर (flags & SMIC_SMS_DATA_AVAIL)
			वापस SI_SM_ATTN;
		वापस SI_SM_IDLE;

	हाल SMIC_START_OP:
		/* sanity check whether smic is really idle */
		ग_लिखो_smic_control(smic, SMIC_CC_SMS_GET_STATUS);
		ग_लिखो_smic_flags(smic, flags | SMIC_FLAG_BSY);
		smic->state = SMIC_OP_OK;
		अवरोध;

	हाल SMIC_OP_OK:
		अगर (status != SMIC_SC_SMS_READY) अणु
			/* this should not happen */
			start_error_recovery(smic,
					     "state = SMIC_OP_OK,"
					     " status != SMIC_SC_SMS_READY");
			वापस SI_SM_CALL_WITH_DELAY;
		पूर्ण
		/* OK so far; smic is idle let us start ... */
		ग_लिखो_smic_control(smic, SMIC_CC_SMS_WR_START);
		ग_लिखो_next_byte(smic);
		ग_लिखो_smic_flags(smic, flags | SMIC_FLAG_BSY);
		smic->state = SMIC_WRITE_START;
		अवरोध;

	हाल SMIC_WRITE_START:
		अगर (status != SMIC_SC_SMS_WR_START) अणु
			start_error_recovery(smic,
					     "state = SMIC_WRITE_START, "
					     "status != SMIC_SC_SMS_WR_START");
			वापस SI_SM_CALL_WITH_DELAY;
		पूर्ण
		/*
		 * we must not issue WR_(NEXT|END) unless
		 * TX_DATA_READY is set
		 * */
		अगर (flags & SMIC_TX_DATA_READY) अणु
			अगर (smic->ग_लिखो_count == 1) अणु
				/* last byte */
				ग_लिखो_smic_control(smic, SMIC_CC_SMS_WR_END);
				smic->state = SMIC_WRITE_END;
			पूर्ण अन्यथा अणु
				ग_लिखो_smic_control(smic, SMIC_CC_SMS_WR_NEXT);
				smic->state = SMIC_WRITE_NEXT;
			पूर्ण
			ग_लिखो_next_byte(smic);
			ग_लिखो_smic_flags(smic, flags | SMIC_FLAG_BSY);
		पूर्ण अन्यथा
			वापस SI_SM_CALL_WITH_DELAY;
		अवरोध;

	हाल SMIC_WRITE_NEXT:
		अगर (status != SMIC_SC_SMS_WR_NEXT) अणु
			start_error_recovery(smic,
					     "state = SMIC_WRITE_NEXT, "
					     "status != SMIC_SC_SMS_WR_NEXT");
			वापस SI_SM_CALL_WITH_DELAY;
		पूर्ण
		/* this is the same code as in SMIC_WRITE_START */
		अगर (flags & SMIC_TX_DATA_READY) अणु
			अगर (smic->ग_लिखो_count == 1) अणु
				ग_लिखो_smic_control(smic, SMIC_CC_SMS_WR_END);
				smic->state = SMIC_WRITE_END;
			पूर्ण अन्यथा अणु
				ग_लिखो_smic_control(smic, SMIC_CC_SMS_WR_NEXT);
				smic->state = SMIC_WRITE_NEXT;
			पूर्ण
			ग_लिखो_next_byte(smic);
			ग_लिखो_smic_flags(smic, flags | SMIC_FLAG_BSY);
		पूर्ण अन्यथा
			वापस SI_SM_CALL_WITH_DELAY;
		अवरोध;

	हाल SMIC_WRITE_END:
		अगर (status != SMIC_SC_SMS_WR_END) अणु
			start_error_recovery(smic,
					     "state = SMIC_WRITE_END, "
					     "status != SMIC_SC_SMS_WR_END");
			वापस SI_SM_CALL_WITH_DELAY;
		पूर्ण
		/* data रेजिस्टर holds an error code */
		data = पढ़ो_smic_data(smic);
		अगर (data != 0) अणु
			अगर (smic_debug & SMIC_DEBUG_ENABLE)
				dev_dbg(smic->io->dev,
					"SMIC_WRITE_END: data = %02x\n",
					data);
			start_error_recovery(smic,
					     "state = SMIC_WRITE_END, "
					     "data != SUCCESS");
			वापस SI_SM_CALL_WITH_DELAY;
		पूर्ण अन्यथा
			smic->state = SMIC_WRITE2READ;
		अवरोध;

	हाल SMIC_WRITE2READ:
		/*
		 * we must रुको क्रम RX_DATA_READY to be set beक्रमe we
		 * can जारी
		 */
		अगर (flags & SMIC_RX_DATA_READY) अणु
			ग_लिखो_smic_control(smic, SMIC_CC_SMS_RD_START);
			ग_लिखो_smic_flags(smic, flags | SMIC_FLAG_BSY);
			smic->state = SMIC_READ_START;
		पूर्ण अन्यथा
			वापस SI_SM_CALL_WITH_DELAY;
		अवरोध;

	हाल SMIC_READ_START:
		अगर (status != SMIC_SC_SMS_RD_START) अणु
			start_error_recovery(smic,
					     "state = SMIC_READ_START, "
					     "status != SMIC_SC_SMS_RD_START");
			वापस SI_SM_CALL_WITH_DELAY;
		पूर्ण
		अगर (flags & SMIC_RX_DATA_READY) अणु
			पढ़ो_next_byte(smic);
			ग_लिखो_smic_control(smic, SMIC_CC_SMS_RD_NEXT);
			ग_लिखो_smic_flags(smic, flags | SMIC_FLAG_BSY);
			smic->state = SMIC_READ_NEXT;
		पूर्ण अन्यथा
			वापस SI_SM_CALL_WITH_DELAY;
		अवरोध;

	हाल SMIC_READ_NEXT:
		चयन (status) अणु
		/*
		 * smic tells us that this is the last byte to be पढ़ो
		 * --> clean up
		 */
		हाल SMIC_SC_SMS_RD_END:
			पढ़ो_next_byte(smic);
			ग_लिखो_smic_control(smic, SMIC_CC_SMS_RD_END);
			ग_लिखो_smic_flags(smic, flags | SMIC_FLAG_BSY);
			smic->state = SMIC_READ_END;
			अवरोध;
		हाल SMIC_SC_SMS_RD_NEXT:
			अगर (flags & SMIC_RX_DATA_READY) अणु
				पढ़ो_next_byte(smic);
				ग_लिखो_smic_control(smic, SMIC_CC_SMS_RD_NEXT);
				ग_लिखो_smic_flags(smic, flags | SMIC_FLAG_BSY);
				smic->state = SMIC_READ_NEXT;
			पूर्ण अन्यथा
				वापस SI_SM_CALL_WITH_DELAY;
			अवरोध;
		शेष:
			start_error_recovery(
				smic,
				"state = SMIC_READ_NEXT, "
				"status != SMIC_SC_SMS_RD_(NEXT|END)");
			वापस SI_SM_CALL_WITH_DELAY;
		पूर्ण
		अवरोध;

	हाल SMIC_READ_END:
		अगर (status != SMIC_SC_SMS_READY) अणु
			start_error_recovery(smic,
					     "state = SMIC_READ_END, "
					     "status != SMIC_SC_SMS_READY");
			वापस SI_SM_CALL_WITH_DELAY;
		पूर्ण
		data = पढ़ो_smic_data(smic);
		/* data रेजिस्टर holds an error code */
		अगर (data != 0) अणु
			अगर (smic_debug & SMIC_DEBUG_ENABLE)
				dev_dbg(smic->io->dev,
					"SMIC_READ_END: data = %02x\n",
					data);
			start_error_recovery(smic,
					     "state = SMIC_READ_END, "
					     "data != SUCCESS");
			वापस SI_SM_CALL_WITH_DELAY;
		पूर्ण अन्यथा अणु
			smic->state = SMIC_IDLE;
			वापस SI_SM_TRANSACTION_COMPLETE;
		पूर्ण

	हाल SMIC_HOSED:
		init_smic_data(smic, smic->io);
		वापस SI_SM_HOSED;

	शेष:
		अगर (smic_debug & SMIC_DEBUG_ENABLE) अणु
			dev_dbg(smic->io->dev,
				"smic->state = %d\n", smic->state);
			start_error_recovery(smic, "state = UNKNOWN");
			वापस SI_SM_CALL_WITH_DELAY;
		पूर्ण
	पूर्ण
	smic->smic_समयout = SMIC_RETRY_TIMEOUT;
	वापस SI_SM_CALL_WITHOUT_DELAY;
पूर्ण

अटल पूर्णांक smic_detect(काष्ठा si_sm_data *smic)
अणु
	/*
	 * It's impossible for the SMIC fnags register to be all 1's,
	 * (assuming a properly functioning, self-initialized BMC)
	 * but that's what you get from पढ़ोing a bogus address, so we
	 * test that first.
	 */
	अगर (पढ़ो_smic_flags(smic) == 0xff)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम smic_cleanup(काष्ठा si_sm_data *kcs)
अणु
पूर्ण

अटल पूर्णांक smic_size(व्योम)
अणु
	वापस माप(काष्ठा si_sm_data);
पूर्ण

स्थिर काष्ठा si_sm_handlers smic_smi_handlers = अणु
	.init_data         = init_smic_data,
	.start_transaction = start_smic_transaction,
	.get_result        = smic_get_result,
	.event             = smic_event,
	.detect            = smic_detect,
	.cleanup           = smic_cleanup,
	.size              = smic_size,
पूर्ण;
