<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ipmi_kcs_sm.c
 *
 * State machine क्रम handling IPMI KCS पूर्णांकerfaces.
 *
 * Author: MontaVista Software, Inc.
 *         Corey Minyard <minyard@mvista.com>
 *         source@mvista.com
 *
 * Copyright 2002 MontaVista Software Inc.
 */

/*
 * This state machine is taken from the state machine in the IPMI spec,
 * pretty much verbatim.  If you have questions about the states, see
 * that करोcument.
 */

#घोषणा DEBUG /* So dev_dbg() is always available. */

#समावेश <linux/kernel.h> /* For prपूर्णांकk. */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/माला.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/ipmi_msgdefs.h>		/* क्रम completion codes */
#समावेश "ipmi_si_sm.h"

/* kcs_debug is a bit-field
 *	KCS_DEBUG_ENABLE -	turned on क्रम now
 *	KCS_DEBUG_MSG    -	commands and their responses
 *	KCS_DEBUG_STATES -	state machine
 */
#घोषणा KCS_DEBUG_STATES	4
#घोषणा KCS_DEBUG_MSG		2
#घोषणा	KCS_DEBUG_ENABLE	1

अटल पूर्णांक kcs_debug;
module_param(kcs_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(kcs_debug, "debug bitmask, 1=enable, 2=messages, 4=states");

/* The states the KCS driver may be in. */
क्रमागत kcs_states अणु
	/* The KCS पूर्णांकerface is currently करोing nothing. */
	KCS_IDLE,

	/*
	 * We are starting an operation.  The data is in the output
	 * buffer, but nothing has been करोne to the पूर्णांकerface yet.  This
	 * was added to the state machine in the spec to रुको क्रम the
	 * initial IBF.
	 */
	KCS_START_OP,

	/* We have written a ग_लिखो cmd to the पूर्णांकerface. */
	KCS_WAIT_WRITE_START,

	/* We are writing bytes to the पूर्णांकerface. */
	KCS_WAIT_WRITE,

	/*
	 * We have written the ग_लिखो end cmd to the पूर्णांकerface, and
	 * still need to ग_लिखो the last byte.
	 */
	KCS_WAIT_WRITE_END,

	/* We are रुकोing to पढ़ो data from the पूर्णांकerface. */
	KCS_WAIT_READ,

	/*
	 * State to transition to the error handler, this was added to
	 * the state machine in the spec to be sure IBF was there.
	 */
	KCS_ERROR0,

	/*
	 * First stage error handler, रुको क्रम the पूर्णांकerface to
	 * respond.
	 */
	KCS_ERROR1,

	/*
	 * The पात cmd has been written, रुको क्रम the पूर्णांकerface to
	 * respond.
	 */
	KCS_ERROR2,

	/*
	 * We wrote some data to the पूर्णांकerface, रुको क्रम it to चयन
	 * to पढ़ो mode.
	 */
	KCS_ERROR3,

	/* The hardware failed to follow the state machine. */
	KCS_HOSED
पूर्ण;

#घोषणा MAX_KCS_READ_SIZE IPMI_MAX_MSG_LENGTH
#घोषणा MAX_KCS_WRITE_SIZE IPMI_MAX_MSG_LENGTH

/* Timeouts in microseconds. */
#घोषणा IBF_RETRY_TIMEOUT (5*USEC_PER_SEC)
#घोषणा OBF_RETRY_TIMEOUT (5*USEC_PER_SEC)
#घोषणा MAX_ERROR_RETRIES 10
#घोषणा ERROR0_OBF_WAIT_JIFFIES (2*HZ)

काष्ठा si_sm_data अणु
	क्रमागत kcs_states  state;
	काष्ठा si_sm_io *io;
	अचिन्हित अक्षर    ग_लिखो_data[MAX_KCS_WRITE_SIZE];
	पूर्णांक              ग_लिखो_pos;
	पूर्णांक              ग_लिखो_count;
	पूर्णांक              orig_ग_लिखो_count;
	अचिन्हित अक्षर    पढ़ो_data[MAX_KCS_READ_SIZE];
	पूर्णांक              पढ़ो_pos;
	पूर्णांक	         truncated;

	अचिन्हित पूर्णांक  error_retries;
	दीर्घ          ibf_समयout;
	दीर्घ          obf_समयout;
	अचिन्हित दीर्घ  error0_समयout;
पूर्ण;

अटल अचिन्हित पूर्णांक init_kcs_data(काष्ठा si_sm_data *kcs,
				  काष्ठा si_sm_io *io)
अणु
	kcs->state = KCS_IDLE;
	kcs->io = io;
	kcs->ग_लिखो_pos = 0;
	kcs->ग_लिखो_count = 0;
	kcs->orig_ग_लिखो_count = 0;
	kcs->पढ़ो_pos = 0;
	kcs->error_retries = 0;
	kcs->truncated = 0;
	kcs->ibf_समयout = IBF_RETRY_TIMEOUT;
	kcs->obf_समयout = OBF_RETRY_TIMEOUT;

	/* Reserve 2 I/O bytes. */
	वापस 2;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर पढ़ो_status(काष्ठा si_sm_data *kcs)
अणु
	वापस kcs->io->inputb(kcs->io, 1);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर पढ़ो_data(काष्ठा si_sm_data *kcs)
अणु
	वापस kcs->io->inputb(kcs->io, 0);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_cmd(काष्ठा si_sm_data *kcs, अचिन्हित अक्षर data)
अणु
	kcs->io->outputb(kcs->io, 1, data);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_data(काष्ठा si_sm_data *kcs, अचिन्हित अक्षर data)
अणु
	kcs->io->outputb(kcs->io, 0, data);
पूर्ण

/* Control codes. */
#घोषणा KCS_GET_STATUS_ABORT	0x60
#घोषणा KCS_WRITE_START		0x61
#घोषणा KCS_WRITE_END		0x62
#घोषणा KCS_READ_BYTE		0x68

/* Status bits. */
#घोषणा GET_STATUS_STATE(status) (((status) >> 6) & 0x03)
#घोषणा KCS_IDLE_STATE	0
#घोषणा KCS_READ_STATE	1
#घोषणा KCS_WRITE_STATE	2
#घोषणा KCS_ERROR_STATE	3
#घोषणा GET_STATUS_ATN(status) ((status) & 0x04)
#घोषणा GET_STATUS_IBF(status) ((status) & 0x02)
#घोषणा GET_STATUS_OBF(status) ((status) & 0x01)


अटल अंतरभूत व्योम ग_लिखो_next_byte(काष्ठा si_sm_data *kcs)
अणु
	ग_लिखो_data(kcs, kcs->ग_लिखो_data[kcs->ग_लिखो_pos]);
	(kcs->ग_लिखो_pos)++;
	(kcs->ग_लिखो_count)--;
पूर्ण

अटल अंतरभूत व्योम start_error_recovery(काष्ठा si_sm_data *kcs, अक्षर *reason)
अणु
	(kcs->error_retries)++;
	अगर (kcs->error_retries > MAX_ERROR_RETRIES) अणु
		अगर (kcs_debug & KCS_DEBUG_ENABLE)
			dev_dbg(kcs->io->dev, "ipmi_kcs_sm: kcs hosed: %s\n",
				reason);
		kcs->state = KCS_HOSED;
	पूर्ण अन्यथा अणु
		kcs->error0_समयout = jअगरfies + ERROR0_OBF_WAIT_JIFFIES;
		kcs->state = KCS_ERROR0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम पढ़ो_next_byte(काष्ठा si_sm_data *kcs)
अणु
	अगर (kcs->पढ़ो_pos >= MAX_KCS_READ_SIZE) अणु
		/* Throw the data away and mark it truncated. */
		पढ़ो_data(kcs);
		kcs->truncated = 1;
	पूर्ण अन्यथा अणु
		kcs->पढ़ो_data[kcs->पढ़ो_pos] = पढ़ो_data(kcs);
		(kcs->पढ़ो_pos)++;
	पूर्ण
	ग_लिखो_data(kcs, KCS_READ_BYTE);
पूर्ण

अटल अंतरभूत पूर्णांक check_ibf(काष्ठा si_sm_data *kcs, अचिन्हित अक्षर status,
			    दीर्घ समय)
अणु
	अगर (GET_STATUS_IBF(status)) अणु
		kcs->ibf_समयout -= समय;
		अगर (kcs->ibf_समयout < 0) अणु
			start_error_recovery(kcs, "IBF not ready in time");
			kcs->ibf_समयout = IBF_RETRY_TIMEOUT;
			वापस 1;
		पूर्ण
		वापस 0;
	पूर्ण
	kcs->ibf_समयout = IBF_RETRY_TIMEOUT;
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक check_obf(काष्ठा si_sm_data *kcs, अचिन्हित अक्षर status,
			    दीर्घ समय)
अणु
	अगर (!GET_STATUS_OBF(status)) अणु
		kcs->obf_समयout -= समय;
		अगर (kcs->obf_समयout < 0) अणु
			kcs->obf_समयout = OBF_RETRY_TIMEOUT;
			start_error_recovery(kcs, "OBF not ready in time");
			वापस 1;
		पूर्ण
		वापस 0;
	पूर्ण
	kcs->obf_समयout = OBF_RETRY_TIMEOUT;
	वापस 1;
पूर्ण

अटल व्योम clear_obf(काष्ठा si_sm_data *kcs, अचिन्हित अक्षर status)
अणु
	अगर (GET_STATUS_OBF(status))
		पढ़ो_data(kcs);
पूर्ण

अटल व्योम restart_kcs_transaction(काष्ठा si_sm_data *kcs)
अणु
	kcs->ग_लिखो_count = kcs->orig_ग_लिखो_count;
	kcs->ग_लिखो_pos = 0;
	kcs->पढ़ो_pos = 0;
	kcs->state = KCS_WAIT_WRITE_START;
	kcs->ibf_समयout = IBF_RETRY_TIMEOUT;
	kcs->obf_समयout = OBF_RETRY_TIMEOUT;
	ग_लिखो_cmd(kcs, KCS_WRITE_START);
पूर्ण

अटल पूर्णांक start_kcs_transaction(काष्ठा si_sm_data *kcs, अचिन्हित अक्षर *data,
				 अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;

	अगर (size < 2)
		वापस IPMI_REQ_LEN_INVALID_ERR;
	अगर (size > MAX_KCS_WRITE_SIZE)
		वापस IPMI_REQ_LEN_EXCEEDED_ERR;

	अगर ((kcs->state != KCS_IDLE) && (kcs->state != KCS_HOSED)) अणु
		dev_warn(kcs->io->dev, "KCS in invalid state %d\n", kcs->state);
		वापस IPMI_NOT_IN_MY_STATE_ERR;
	पूर्ण

	अगर (kcs_debug & KCS_DEBUG_MSG) अणु
		dev_dbg(kcs->io->dev, "%s -", __func__);
		क्रम (i = 0; i < size; i++)
			pr_cont(" %02x", data[i]);
		pr_cont("\n");
	पूर्ण
	kcs->error_retries = 0;
	स_नकल(kcs->ग_लिखो_data, data, size);
	kcs->ग_लिखो_count = size;
	kcs->orig_ग_लिखो_count = size;
	kcs->ग_लिखो_pos = 0;
	kcs->पढ़ो_pos = 0;
	kcs->state = KCS_START_OP;
	kcs->ibf_समयout = IBF_RETRY_TIMEOUT;
	kcs->obf_समयout = OBF_RETRY_TIMEOUT;
	वापस 0;
पूर्ण

अटल पूर्णांक get_kcs_result(काष्ठा si_sm_data *kcs, अचिन्हित अक्षर *data,
			  अचिन्हित पूर्णांक length)
अणु
	अगर (length < kcs->पढ़ो_pos) अणु
		kcs->पढ़ो_pos = length;
		kcs->truncated = 1;
	पूर्ण

	स_नकल(data, kcs->पढ़ो_data, kcs->पढ़ो_pos);

	अगर ((length >= 3) && (kcs->पढ़ो_pos < 3)) अणु
		/* Guarantee that we वापस at least 3 bytes, with an
		   error in the third byte अगर it is too लघु. */
		data[2] = IPMI_ERR_UNSPECIFIED;
		kcs->पढ़ो_pos = 3;
	पूर्ण
	अगर (kcs->truncated) अणु
		/*
		 * Report a truncated error.  We might overग_लिखो
		 * another error, but that's too bad, the user needs
		 * to know it was truncated.
		 */
		data[2] = IPMI_ERR_MSG_TRUNCATED;
		kcs->truncated = 0;
	पूर्ण

	वापस kcs->पढ़ो_pos;
पूर्ण

/*
 * This implements the state machine defined in the IPMI manual, see
 * that क्रम details on how this works.  Divide that flowअक्षरt पूर्णांकo
 * sections delimited by "Wait for IBF" and this will become clear.
 */
अटल क्रमागत si_sm_result kcs_event(काष्ठा si_sm_data *kcs, दीर्घ समय)
अणु
	अचिन्हित अक्षर status;
	अचिन्हित अक्षर state;

	status = पढ़ो_status(kcs);

	अगर (kcs_debug & KCS_DEBUG_STATES)
		dev_dbg(kcs->io->dev,
			"KCS: State = %d, %x\n", kcs->state, status);

	/* All states रुको क्रम ibf, so just करो it here. */
	अगर (!check_ibf(kcs, status, समय))
		वापस SI_SM_CALL_WITH_DELAY;

	/* Just about everything looks at the KCS state, so grab that, too. */
	state = GET_STATUS_STATE(status);

	चयन (kcs->state) अणु
	हाल KCS_IDLE:
		/* If there's and पूर्णांकerrupt source, turn it off. */
		clear_obf(kcs, status);

		अगर (GET_STATUS_ATN(status))
			वापस SI_SM_ATTN;
		अन्यथा
			वापस SI_SM_IDLE;

	हाल KCS_START_OP:
		अगर (state != KCS_IDLE_STATE) अणु
			start_error_recovery(kcs,
					     "State machine not idle at start");
			अवरोध;
		पूर्ण

		clear_obf(kcs, status);
		ग_लिखो_cmd(kcs, KCS_WRITE_START);
		kcs->state = KCS_WAIT_WRITE_START;
		अवरोध;

	हाल KCS_WAIT_WRITE_START:
		अगर (state != KCS_WRITE_STATE) अणु
			start_error_recovery(
				kcs,
				"Not in write state at write start");
			अवरोध;
		पूर्ण
		पढ़ो_data(kcs);
		अगर (kcs->ग_लिखो_count == 1) अणु
			ग_लिखो_cmd(kcs, KCS_WRITE_END);
			kcs->state = KCS_WAIT_WRITE_END;
		पूर्ण अन्यथा अणु
			ग_लिखो_next_byte(kcs);
			kcs->state = KCS_WAIT_WRITE;
		पूर्ण
		अवरोध;

	हाल KCS_WAIT_WRITE:
		अगर (state != KCS_WRITE_STATE) अणु
			start_error_recovery(kcs,
					     "Not in write state for write");
			अवरोध;
		पूर्ण
		clear_obf(kcs, status);
		अगर (kcs->ग_लिखो_count == 1) अणु
			ग_लिखो_cmd(kcs, KCS_WRITE_END);
			kcs->state = KCS_WAIT_WRITE_END;
		पूर्ण अन्यथा अणु
			ग_लिखो_next_byte(kcs);
		पूर्ण
		अवरोध;

	हाल KCS_WAIT_WRITE_END:
		अगर (state != KCS_WRITE_STATE) अणु
			start_error_recovery(kcs,
					     "Not in write state"
					     " for write end");
			अवरोध;
		पूर्ण
		clear_obf(kcs, status);
		ग_लिखो_next_byte(kcs);
		kcs->state = KCS_WAIT_READ;
		अवरोध;

	हाल KCS_WAIT_READ:
		अगर ((state != KCS_READ_STATE) && (state != KCS_IDLE_STATE)) अणु
			start_error_recovery(
				kcs,
				"Not in read or idle in read state");
			अवरोध;
		पूर्ण

		अगर (state == KCS_READ_STATE) अणु
			अगर (!check_obf(kcs, status, समय))
				वापस SI_SM_CALL_WITH_DELAY;
			पढ़ो_next_byte(kcs);
		पूर्ण अन्यथा अणु
			/*
			 * We करोn't implement this exactly like the state
			 * machine in the spec.  Some broken hardware
			 * करोes not ग_लिखो the final dummy byte to the
			 * पढ़ो रेजिस्टर.  Thus obf will never go high
			 * here.  We just go straight to idle, and we
			 * handle clearing out obf in idle state अगर it
			 * happens to come in.
			 */
			clear_obf(kcs, status);
			kcs->orig_ग_लिखो_count = 0;
			kcs->state = KCS_IDLE;
			वापस SI_SM_TRANSACTION_COMPLETE;
		पूर्ण
		अवरोध;

	हाल KCS_ERROR0:
		clear_obf(kcs, status);
		status = पढ़ो_status(kcs);
		अगर (GET_STATUS_OBF(status))
			/* controller isn't responding */
			अगर (समय_beक्रमe(jअगरfies, kcs->error0_समयout))
				वापस SI_SM_CALL_WITH_TICK_DELAY;
		ग_लिखो_cmd(kcs, KCS_GET_STATUS_ABORT);
		kcs->state = KCS_ERROR1;
		अवरोध;

	हाल KCS_ERROR1:
		clear_obf(kcs, status);
		ग_लिखो_data(kcs, 0);
		kcs->state = KCS_ERROR2;
		अवरोध;

	हाल KCS_ERROR2:
		अगर (state != KCS_READ_STATE) अणु
			start_error_recovery(kcs,
					     "Not in read state for error2");
			अवरोध;
		पूर्ण
		अगर (!check_obf(kcs, status, समय))
			वापस SI_SM_CALL_WITH_DELAY;

		clear_obf(kcs, status);
		ग_लिखो_data(kcs, KCS_READ_BYTE);
		kcs->state = KCS_ERROR3;
		अवरोध;

	हाल KCS_ERROR3:
		अगर (state != KCS_IDLE_STATE) अणु
			start_error_recovery(kcs,
					     "Not in idle state for error3");
			अवरोध;
		पूर्ण

		अगर (!check_obf(kcs, status, समय))
			वापस SI_SM_CALL_WITH_DELAY;

		clear_obf(kcs, status);
		अगर (kcs->orig_ग_लिखो_count) अणु
			restart_kcs_transaction(kcs);
		पूर्ण अन्यथा अणु
			kcs->state = KCS_IDLE;
			वापस SI_SM_TRANSACTION_COMPLETE;
		पूर्ण
		अवरोध;

	हाल KCS_HOSED:
		अवरोध;
	पूर्ण

	अगर (kcs->state == KCS_HOSED) अणु
		init_kcs_data(kcs, kcs->io);
		वापस SI_SM_HOSED;
	पूर्ण

	वापस SI_SM_CALL_WITHOUT_DELAY;
पूर्ण

अटल पूर्णांक kcs_size(व्योम)
अणु
	वापस माप(काष्ठा si_sm_data);
पूर्ण

अटल पूर्णांक kcs_detect(काष्ठा si_sm_data *kcs)
अणु
	/*
	 * It's impossible for the KCS status register to be all 1's,
	 * (assuming a properly functioning, self-initialized BMC)
	 * but that's what you get from पढ़ोing a bogus address, so we
	 * test that first.
	 */
	अगर (पढ़ो_status(kcs) == 0xff)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम kcs_cleanup(काष्ठा si_sm_data *kcs)
अणु
पूर्ण

स्थिर काष्ठा si_sm_handlers kcs_smi_handlers = अणु
	.init_data         = init_kcs_data,
	.start_transaction = start_kcs_transaction,
	.get_result        = get_kcs_result,
	.event             = kcs_event,
	.detect            = kcs_detect,
	.cleanup           = kcs_cleanup,
	.size              = kcs_size,
पूर्ण;
