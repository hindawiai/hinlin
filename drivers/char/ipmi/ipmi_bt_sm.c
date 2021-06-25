<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  ipmi_bt_sm.c
 *
 *  The state machine क्रम an Open IPMI BT sub-driver under ipmi_si.c, part
 *  of the driver architecture at http://sourceक्रमge.net/projects/खोलोipmi 
 *
 *  Author:	Rocky Craig <first.last@hp.com>
 */

#घोषणा DEBUG /* So dev_dbg() is always available. */

#समावेश <linux/kernel.h> /* For prपूर्णांकk. */
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/ipmi_msgdefs.h>		/* क्रम completion codes */
#समावेश "ipmi_si_sm.h"

#घोषणा BT_DEBUG_OFF	0	/* Used in production */
#घोषणा BT_DEBUG_ENABLE	1	/* Generic messages */
#घोषणा BT_DEBUG_MSG	2	/* Prपूर्णांकs all request/response buffers */
#घोषणा BT_DEBUG_STATES	4	/* Verbose look at state changes */
/*
 * BT_DEBUG_OFF must be zero to correspond to the शेष uninitialized
 * value
 */

अटल पूर्णांक bt_debug; /* 0 == BT_DEBUG_OFF */

module_param(bt_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(bt_debug, "debug bitmask, 1=enable, 2=messages, 4=states");

/*
 * Typical "Get BT Capabilities" values are 2-3 retries, 5-10 seconds,
 * and 64 byte buffers.  However, one HP implementation wants 255 bytes of
 * buffer (with a करोcumented message of 160 bytes) so go क्रम the max.
 * Since the Open IPMI architecture is single-message oriented at this
 * stage, the queue depth of BT is of no concern.
 */

#घोषणा BT_NORMAL_TIMEOUT	5	/* seconds */
#घोषणा BT_NORMAL_RETRY_LIMIT	2
#घोषणा BT_RESET_DELAY		6	/* seconds after warm reset */

/*
 * States are written in chronological order and usually cover
 * multiple rows of the state table discussion in the IPMI spec.
 */

क्रमागत bt_states अणु
	BT_STATE_IDLE = 0,	/* Order is critical in this list */
	BT_STATE_XACTION_START,
	BT_STATE_WRITE_BYTES,
	BT_STATE_WRITE_CONSUME,
	BT_STATE_READ_WAIT,
	BT_STATE_CLEAR_B2H,
	BT_STATE_READ_BYTES,
	BT_STATE_RESET1,	/* These must come last */
	BT_STATE_RESET2,
	BT_STATE_RESET3,
	BT_STATE_RESTART,
	BT_STATE_PRINTME,
	BT_STATE_LONG_BUSY	/* BT करोesn't get hosed :-) */
पूर्ण;

/*
 * Macros seen at the end of state "case" blocks.  They help with legibility
 * and debugging.
 */

#घोषणा BT_STATE_CHANGE(X, Y) अणु bt->state = X; वापस Y; पूर्ण

#घोषणा BT_SI_SM_RETURN(Y)   अणु last_prपूर्णांकed = BT_STATE_PRINTME; वापस Y; पूर्ण

काष्ठा si_sm_data अणु
	क्रमागत bt_states	state;
	अचिन्हित अक्षर	seq;		/* BT sequence number */
	काष्ठा si_sm_io	*io;
	अचिन्हित अक्षर	ग_लिखो_data[IPMI_MAX_MSG_LENGTH + 2]; /* +2 क्रम स_नकल */
	पूर्णांक		ग_लिखो_count;
	अचिन्हित अक्षर	पढ़ो_data[IPMI_MAX_MSG_LENGTH + 2]; /* +2 क्रम स_नकल */
	पूर्णांक		पढ़ो_count;
	पूर्णांक		truncated;
	दीर्घ		समयout;	/* microseconds countकरोwn */
	पूर्णांक		error_retries;	/* end of "common" fields */
	पूर्णांक		nonzero_status;	/* hung BMCs stay all 0 */
	क्रमागत bt_states	complete;	/* to भागert the state machine */
	दीर्घ		BT_CAP_req2rsp;
	पूर्णांक		BT_CAP_retries;	/* Recommended retries */
पूर्ण;

#घोषणा BT_CLR_WR_PTR	0x01	/* See IPMI 1.5 table 11.6.4 */
#घोषणा BT_CLR_RD_PTR	0x02
#घोषणा BT_H2B_ATN	0x04
#घोषणा BT_B2H_ATN	0x08
#घोषणा BT_SMS_ATN	0x10
#घोषणा BT_OEM0		0x20
#घोषणा BT_H_BUSY	0x40
#घोषणा BT_B_BUSY	0x80

/*
 * Some bits are toggled on each ग_लिखो: ग_लिखो once to set it, once
 * more to clear it; writing a zero करोes nothing.  To असलolutely
 * clear it, check its state and ग_लिखो अगर set.  This aव्योमs the "get
 * current then use as mask" scheme to modअगरy one bit.  Note that the
 * variable "bt" is hardcoded पूर्णांकo these macros.
 */

#घोषणा BT_STATUS	bt->io->inputb(bt->io, 0)
#घोषणा BT_CONTROL(x)	bt->io->outputb(bt->io, 0, x)

#घोषणा BMC2HOST	bt->io->inputb(bt->io, 1)
#घोषणा HOST2BMC(x)	bt->io->outputb(bt->io, 1, x)

#घोषणा BT_INTMASK_R	bt->io->inputb(bt->io, 2)
#घोषणा BT_INTMASK_W(x)	bt->io->outputb(bt->io, 2, x)

/*
 * Convenience routines क्रम debugging.  These are not multi-खोलो safe!
 * Note the macros have hardcoded variables in them.
 */

अटल अक्षर *state2txt(अचिन्हित अक्षर state)
अणु
	चयन (state) अणु
	हाल BT_STATE_IDLE:		वापस("IDLE");
	हाल BT_STATE_XACTION_START:	वापस("XACTION");
	हाल BT_STATE_WRITE_BYTES:	वापस("WR_BYTES");
	हाल BT_STATE_WRITE_CONSUME:	वापस("WR_CONSUME");
	हाल BT_STATE_READ_WAIT:	वापस("RD_WAIT");
	हाल BT_STATE_CLEAR_B2H:	वापस("CLEAR_B2H");
	हाल BT_STATE_READ_BYTES:	वापस("RD_BYTES");
	हाल BT_STATE_RESET1:		वापस("RESET1");
	हाल BT_STATE_RESET2:		वापस("RESET2");
	हाल BT_STATE_RESET3:		वापस("RESET3");
	हाल BT_STATE_RESTART:		वापस("RESTART");
	हाल BT_STATE_LONG_BUSY:	वापस("LONG_BUSY");
	पूर्ण
	वापस("BAD STATE");
पूर्ण
#घोषणा STATE2TXT state2txt(bt->state)

अटल अक्षर *status2txt(अचिन्हित अक्षर status)
अणु
	/*
	 * This cannot be called by two thपढ़ोs at the same समय and
	 * the buffer is always consumed immediately, so the अटल is
	 * safe to use.
	 */
	अटल अक्षर buf[40];

	म_नकल(buf, "[ ");
	अगर (status & BT_B_BUSY)
		म_जोड़ो(buf, "B_BUSY ");
	अगर (status & BT_H_BUSY)
		म_जोड़ो(buf, "H_BUSY ");
	अगर (status & BT_OEM0)
		म_जोड़ो(buf, "OEM0 ");
	अगर (status & BT_SMS_ATN)
		म_जोड़ो(buf, "SMS ");
	अगर (status & BT_B2H_ATN)
		म_जोड़ो(buf, "B2H ");
	अगर (status & BT_H2B_ATN)
		म_जोड़ो(buf, "H2B ");
	म_जोड़ो(buf, "]");
	वापस buf;
पूर्ण
#घोषणा STATUS2TXT status2txt(status)

/* called बाह्यally at insmod समय, and पूर्णांकernally on cleanup */

अटल अचिन्हित पूर्णांक bt_init_data(काष्ठा si_sm_data *bt, काष्ठा si_sm_io *io)
अणु
	स_रखो(bt, 0, माप(काष्ठा si_sm_data));
	अगर (bt->io != io) अणु
		/* बाह्यal: one-समय only things */
		bt->io = io;
		bt->seq = 0;
	पूर्ण
	bt->state = BT_STATE_IDLE;	/* start here */
	bt->complete = BT_STATE_IDLE;	/* end here */
	bt->BT_CAP_req2rsp = BT_NORMAL_TIMEOUT * USEC_PER_SEC;
	bt->BT_CAP_retries = BT_NORMAL_RETRY_LIMIT;
	वापस 3; /* We claim 3 bytes of space; ought to check SPMI table */
पूर्ण

/* Jam a completion code (probably an error) पूर्णांकo a response */

अटल व्योम क्रमce_result(काष्ठा si_sm_data *bt, अचिन्हित अक्षर completion_code)
अणु
	bt->पढ़ो_data[0] = 4;				/* # following bytes */
	bt->पढ़ो_data[1] = bt->ग_लिखो_data[1] | 4;	/* Odd NetFn/LUN */
	bt->पढ़ो_data[2] = bt->ग_लिखो_data[2];		/* seq (ignored) */
	bt->पढ़ो_data[3] = bt->ग_लिखो_data[3];		/* Command */
	bt->पढ़ो_data[4] = completion_code;
	bt->पढ़ो_count = 5;
पूर्ण

/* The upper state machine starts here */

अटल पूर्णांक bt_start_transaction(काष्ठा si_sm_data *bt,
				अचिन्हित अक्षर *data,
				अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;

	अगर (size < 2)
		वापस IPMI_REQ_LEN_INVALID_ERR;
	अगर (size > IPMI_MAX_MSG_LENGTH)
		वापस IPMI_REQ_LEN_EXCEEDED_ERR;

	अगर (bt->state == BT_STATE_LONG_BUSY)
		वापस IPMI_NODE_BUSY_ERR;

	अगर (bt->state != BT_STATE_IDLE) अणु
		dev_warn(bt->io->dev, "BT in invalid state %d\n", bt->state);
		वापस IPMI_NOT_IN_MY_STATE_ERR;
	पूर्ण

	अगर (bt_debug & BT_DEBUG_MSG) अणु
		dev_dbg(bt->io->dev, "+++++++++++++++++ New command\n");
		dev_dbg(bt->io->dev, "NetFn/LUN CMD [%d data]:", size - 2);
		क्रम (i = 0; i < size; i ++)
			pr_cont(" %02x", data[i]);
		pr_cont("\n");
	पूर्ण
	bt->ग_लिखो_data[0] = size + 1;	/* all data plus seq byte */
	bt->ग_लिखो_data[1] = *data;	/* NetFn/LUN */
	bt->ग_लिखो_data[2] = bt->seq++;
	स_नकल(bt->ग_लिखो_data + 3, data + 1, size - 1);
	bt->ग_लिखो_count = size + 2;
	bt->error_retries = 0;
	bt->nonzero_status = 0;
	bt->truncated = 0;
	bt->state = BT_STATE_XACTION_START;
	bt->समयout = bt->BT_CAP_req2rsp;
	क्रमce_result(bt, IPMI_ERR_UNSPECIFIED);
	वापस 0;
पूर्ण

/*
 * After the upper state machine has been told SI_SM_TRANSACTION_COMPLETE
 * it calls this.  Strip out the length and seq bytes.
 */

अटल पूर्णांक bt_get_result(काष्ठा si_sm_data *bt,
			 अचिन्हित अक्षर *data,
			 अचिन्हित पूर्णांक length)
अणु
	पूर्णांक i, msg_len;

	msg_len = bt->पढ़ो_count - 2;		/* account क्रम length & seq */
	अगर (msg_len < 3 || msg_len > IPMI_MAX_MSG_LENGTH) अणु
		क्रमce_result(bt, IPMI_ERR_UNSPECIFIED);
		msg_len = 3;
	पूर्ण
	data[0] = bt->पढ़ो_data[1];
	data[1] = bt->पढ़ो_data[3];
	अगर (length < msg_len || bt->truncated) अणु
		data[2] = IPMI_ERR_MSG_TRUNCATED;
		msg_len = 3;
	पूर्ण अन्यथा
		स_नकल(data + 2, bt->पढ़ो_data + 4, msg_len - 2);

	अगर (bt_debug & BT_DEBUG_MSG) अणु
		dev_dbg(bt->io->dev, "result %d bytes:", msg_len);
		क्रम (i = 0; i < msg_len; i++)
			pr_cont(" %02x", data[i]);
		pr_cont("\n");
	पूर्ण
	वापस msg_len;
पूर्ण

/* This bit's functionality is optional */
#घोषणा BT_BMC_HWRST	0x80

अटल व्योम reset_flags(काष्ठा si_sm_data *bt)
अणु
	अगर (bt_debug)
		dev_dbg(bt->io->dev, "flag reset %s\n", status2txt(BT_STATUS));
	अगर (BT_STATUS & BT_H_BUSY)
		BT_CONTROL(BT_H_BUSY);	/* क्रमce clear */
	BT_CONTROL(BT_CLR_WR_PTR);	/* always reset */
	BT_CONTROL(BT_SMS_ATN);		/* always clear */
	BT_INTMASK_W(BT_BMC_HWRST);
पूर्ण

/*
 * Get rid of an unwanted/stale response.  This should only be needed क्रम
 * BMCs that support multiple outstanding requests.
 */

अटल व्योम drain_BMC2HOST(काष्ठा si_sm_data *bt)
अणु
	पूर्णांक i, size;

	अगर (!(BT_STATUS & BT_B2H_ATN)) 	/* Not संकेतling a response */
		वापस;

	BT_CONTROL(BT_H_BUSY);		/* now set */
	BT_CONTROL(BT_B2H_ATN);		/* always clear */
	BT_STATUS;			/* छोड़ो */
	BT_CONTROL(BT_B2H_ATN);		/* some BMCs are stubborn */
	BT_CONTROL(BT_CLR_RD_PTR);	/* always reset */
	अगर (bt_debug)
		dev_dbg(bt->io->dev, "stale response %s; ",
			status2txt(BT_STATUS));
	size = BMC2HOST;
	क्रम (i = 0; i < size ; i++)
		BMC2HOST;
	BT_CONTROL(BT_H_BUSY);		/* now clear */
	अगर (bt_debug)
		pr_cont("drained %d bytes\n", size + 1);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_all_bytes(काष्ठा si_sm_data *bt)
अणु
	पूर्णांक i;

	अगर (bt_debug & BT_DEBUG_MSG) अणु
		dev_dbg(bt->io->dev, "write %d bytes seq=0x%02X",
			bt->ग_लिखो_count, bt->seq);
		क्रम (i = 0; i < bt->ग_लिखो_count; i++)
			pr_cont(" %02x", bt->ग_लिखो_data[i]);
		pr_cont("\n");
	पूर्ण
	क्रम (i = 0; i < bt->ग_लिखो_count; i++)
		HOST2BMC(bt->ग_लिखो_data[i]);
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_all_bytes(काष्ठा si_sm_data *bt)
अणु
	अचिन्हित पूर्णांक i;

	/*
	 * length is "framing info", minimum = 4: NetFn, Seq, Cmd, cCode.
	 * Keep layout of first four bytes aligned with ग_लिखो_data[]
	 */

	bt->पढ़ो_data[0] = BMC2HOST;
	bt->पढ़ो_count = bt->पढ़ो_data[0];

	अगर (bt->पढ़ो_count < 4 || bt->पढ़ो_count >= IPMI_MAX_MSG_LENGTH) अणु
		अगर (bt_debug & BT_DEBUG_MSG)
			dev_dbg(bt->io->dev,
				"bad raw rsp len=%d\n", bt->पढ़ो_count);
		bt->truncated = 1;
		वापस 1;	/* let next XACTION START clean it up */
	पूर्ण
	क्रम (i = 1; i <= bt->पढ़ो_count; i++)
		bt->पढ़ो_data[i] = BMC2HOST;
	bt->पढ़ो_count++;	/* Account पूर्णांकernally क्रम length byte */

	अगर (bt_debug & BT_DEBUG_MSG) अणु
		पूर्णांक max = bt->पढ़ो_count;

		dev_dbg(bt->io->dev,
			"got %d bytes seq=0x%02X", max, bt->पढ़ो_data[2]);
		अगर (max > 16)
			max = 16;
		क्रम (i = 0; i < max; i++)
			pr_cont(" %02x", bt->पढ़ो_data[i]);
		pr_cont("%s\n", bt->पढ़ो_count == max ? "" : " ...");
	पूर्ण

	/* per the spec, the (NetFn[1], Seq[2], Cmd[3]) tuples must match */
	अगर ((bt->पढ़ो_data[3] == bt->ग_लिखो_data[3]) &&
	    (bt->पढ़ो_data[2] == bt->ग_लिखो_data[2]) &&
	    ((bt->पढ़ो_data[1] & 0xF8) == (bt->ग_लिखो_data[1] & 0xF8)))
			वापस 1;

	अगर (bt_debug & BT_DEBUG_MSG)
		dev_dbg(bt->io->dev,
			"IPMI BT: bad packet: want 0x(%02X, %02X, %02X) got (%02X, %02X, %02X)\n",
			bt->ग_लिखो_data[1] | 0x04, bt->ग_लिखो_data[2],
			bt->ग_लिखो_data[3],
			bt->पढ़ो_data[1],  bt->पढ़ो_data[2],  bt->पढ़ो_data[3]);
	वापस 0;
पूर्ण

/* Restart अगर retries are left, or वापस an error completion code */

अटल क्रमागत si_sm_result error_recovery(काष्ठा si_sm_data *bt,
					अचिन्हित अक्षर status,
					अचिन्हित अक्षर cCode)
अणु
	अक्षर *reason;

	bt->समयout = bt->BT_CAP_req2rsp;

	चयन (cCode) अणु
	हाल IPMI_TIMEOUT_ERR:
		reason = "timeout";
		अवरोध;
	शेष:
		reason = "internal error";
		अवरोध;
	पूर्ण

	dev_warn(bt->io->dev, "IPMI BT: %s in %s %s ", /* खोलो-ended line */
		 reason, STATE2TXT, STATUS2TXT);

	/*
	 * Per the IPMI spec, retries are based on the sequence number
	 * known only to this module, so manage a restart here.
	 */
	(bt->error_retries)++;
	अगर (bt->error_retries < bt->BT_CAP_retries) अणु
		pr_cont("%d retries left\n",
			bt->BT_CAP_retries - bt->error_retries);
		bt->state = BT_STATE_RESTART;
		वापस SI_SM_CALL_WITHOUT_DELAY;
	पूर्ण

	dev_warn(bt->io->dev, "failed %d retries, sending error response\n",
		 bt->BT_CAP_retries);
	अगर (!bt->nonzero_status)
		dev_err(bt->io->dev, "stuck, try power cycle\n");

	/* this is most likely during insmod */
	अन्यथा अगर (bt->seq <= (अचिन्हित अक्षर)(bt->BT_CAP_retries & 0xFF)) अणु
		dev_warn(bt->io->dev, "BT reset (takes 5 secs)\n");
		bt->state = BT_STATE_RESET1;
		वापस SI_SM_CALL_WITHOUT_DELAY;
	पूर्ण

	/*
	 * Concoct a useful error message, set up the next state, and
	 * be करोne with this sequence.
	 */

	bt->state = BT_STATE_IDLE;
	चयन (cCode) अणु
	हाल IPMI_TIMEOUT_ERR:
		अगर (status & BT_B_BUSY) अणु
			cCode = IPMI_NODE_BUSY_ERR;
			bt->state = BT_STATE_LONG_BUSY;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	क्रमce_result(bt, cCode);
	वापस SI_SM_TRANSACTION_COMPLETE;
पूर्ण

/* Check status and (usually) take action and change this state machine. */

अटल क्रमागत si_sm_result bt_event(काष्ठा si_sm_data *bt, दीर्घ समय)
अणु
	अचिन्हित अक्षर status;
	अटल क्रमागत bt_states last_prपूर्णांकed = BT_STATE_PRINTME;
	पूर्णांक i;

	status = BT_STATUS;
	bt->nonzero_status |= status;
	अगर ((bt_debug & BT_DEBUG_STATES) && (bt->state != last_prपूर्णांकed)) अणु
		dev_dbg(bt->io->dev, "BT: %s %s TO=%ld - %ld\n",
			STATE2TXT,
			STATUS2TXT,
			bt->समयout,
			समय);
		last_prपूर्णांकed = bt->state;
	पूर्ण

	/*
	 * Commands that समय out may still (eventually) provide a response.
	 * This stale response will get in the way of a new response so हटाओ
	 * it अगर possible (hopefully during IDLE).  Even अगर it comes up later
	 * it will be rejected by its (now-क्रमgotten) seq number.
	 */

	अगर ((bt->state < BT_STATE_WRITE_BYTES) && (status & BT_B2H_ATN)) अणु
		drain_BMC2HOST(bt);
		BT_SI_SM_RETURN(SI_SM_CALL_WITH_DELAY);
	पूर्ण

	अगर ((bt->state != BT_STATE_IDLE) &&
	    (bt->state <  BT_STATE_PRINTME)) अणु
		/* check समयout */
		bt->समयout -= समय;
		अगर ((bt->समयout < 0) && (bt->state < BT_STATE_RESET1))
			वापस error_recovery(bt,
					      status,
					      IPMI_TIMEOUT_ERR);
	पूर्ण

	चयन (bt->state) अणु

	/*
	 * Idle state first checks क्रम asynchronous messages from another
	 * channel, then करोes some opportunistic housekeeping.
	 */

	हाल BT_STATE_IDLE:
		अगर (status & BT_SMS_ATN) अणु
			BT_CONTROL(BT_SMS_ATN);	/* clear it */
			वापस SI_SM_ATTN;
		पूर्ण

		अगर (status & BT_H_BUSY)		/* clear a leftover H_BUSY */
			BT_CONTROL(BT_H_BUSY);

		BT_SI_SM_RETURN(SI_SM_IDLE);

	हाल BT_STATE_XACTION_START:
		अगर (status & (BT_B_BUSY | BT_H2B_ATN))
			BT_SI_SM_RETURN(SI_SM_CALL_WITH_DELAY);
		अगर (BT_STATUS & BT_H_BUSY)
			BT_CONTROL(BT_H_BUSY);	/* क्रमce clear */
		BT_STATE_CHANGE(BT_STATE_WRITE_BYTES,
				SI_SM_CALL_WITHOUT_DELAY);

	हाल BT_STATE_WRITE_BYTES:
		अगर (status & BT_H_BUSY)
			BT_CONTROL(BT_H_BUSY);	/* clear */
		BT_CONTROL(BT_CLR_WR_PTR);
		ग_लिखो_all_bytes(bt);
		BT_CONTROL(BT_H2B_ATN);	/* can clear too fast to catch */
		BT_STATE_CHANGE(BT_STATE_WRITE_CONSUME,
				SI_SM_CALL_WITHOUT_DELAY);

	हाल BT_STATE_WRITE_CONSUME:
		अगर (status & (BT_B_BUSY | BT_H2B_ATN))
			BT_SI_SM_RETURN(SI_SM_CALL_WITH_DELAY);
		BT_STATE_CHANGE(BT_STATE_READ_WAIT,
				SI_SM_CALL_WITHOUT_DELAY);

	/* Spinning hard can suppress B2H_ATN and क्रमce a समयout */

	हाल BT_STATE_READ_WAIT:
		अगर (!(status & BT_B2H_ATN))
			BT_SI_SM_RETURN(SI_SM_CALL_WITH_DELAY);
		BT_CONTROL(BT_H_BUSY);		/* set */

		/*
		 * Uncached, ordered ग_लिखोs should just proceed serially but
		 * some BMCs करोn't clear B2H_ATN with one hit.  Fast-path a
		 * workaround without too much penalty to the general हाल.
		 */

		BT_CONTROL(BT_B2H_ATN);		/* clear it to ACK the BMC */
		BT_STATE_CHANGE(BT_STATE_CLEAR_B2H,
				SI_SM_CALL_WITHOUT_DELAY);

	हाल BT_STATE_CLEAR_B2H:
		अगर (status & BT_B2H_ATN) अणु
			/* keep hitting it */
			BT_CONTROL(BT_B2H_ATN);
			BT_SI_SM_RETURN(SI_SM_CALL_WITH_DELAY);
		पूर्ण
		BT_STATE_CHANGE(BT_STATE_READ_BYTES,
				SI_SM_CALL_WITHOUT_DELAY);

	हाल BT_STATE_READ_BYTES:
		अगर (!(status & BT_H_BUSY))
			/* check in हाल of retry */
			BT_CONTROL(BT_H_BUSY);
		BT_CONTROL(BT_CLR_RD_PTR);	/* start of BMC2HOST buffer */
		i = पढ़ो_all_bytes(bt);		/* true == packet seq match */
		BT_CONTROL(BT_H_BUSY);		/* NOW clear */
		अगर (!i) 			/* Not my message */
			BT_STATE_CHANGE(BT_STATE_READ_WAIT,
					SI_SM_CALL_WITHOUT_DELAY);
		bt->state = bt->complete;
		वापस bt->state == BT_STATE_IDLE ?	/* where to next? */
			SI_SM_TRANSACTION_COMPLETE :	/* normal */
			SI_SM_CALL_WITHOUT_DELAY;	/* Startup magic */

	हाल BT_STATE_LONG_BUSY:	/* For example: after FW update */
		अगर (!(status & BT_B_BUSY)) अणु
			reset_flags(bt);	/* next state is now IDLE */
			bt_init_data(bt, bt->io);
		पूर्ण
		वापस SI_SM_CALL_WITH_DELAY;	/* No repeat prपूर्णांकing */

	हाल BT_STATE_RESET1:
		reset_flags(bt);
		drain_BMC2HOST(bt);
		BT_STATE_CHANGE(BT_STATE_RESET2,
				SI_SM_CALL_WITH_DELAY);

	हाल BT_STATE_RESET2:		/* Send a soft reset */
		BT_CONTROL(BT_CLR_WR_PTR);
		HOST2BMC(3);		/* number of bytes following */
		HOST2BMC(0x18);		/* NetFn/LUN == Application, LUN 0 */
		HOST2BMC(42);		/* Sequence number */
		HOST2BMC(3);		/* Cmd == Soft reset */
		BT_CONTROL(BT_H2B_ATN);
		bt->समयout = BT_RESET_DELAY * USEC_PER_SEC;
		BT_STATE_CHANGE(BT_STATE_RESET3,
				SI_SM_CALL_WITH_DELAY);

	हाल BT_STATE_RESET3:		/* Hold off everything क्रम a bit */
		अगर (bt->समयout > 0)
			वापस SI_SM_CALL_WITH_DELAY;
		drain_BMC2HOST(bt);
		BT_STATE_CHANGE(BT_STATE_RESTART,
				SI_SM_CALL_WITH_DELAY);

	हाल BT_STATE_RESTART:		/* करोn't reset retries or seq! */
		bt->पढ़ो_count = 0;
		bt->nonzero_status = 0;
		bt->समयout = bt->BT_CAP_req2rsp;
		BT_STATE_CHANGE(BT_STATE_XACTION_START,
				SI_SM_CALL_WITH_DELAY);

	शेष:	/* should never occur */
		वापस error_recovery(bt,
				      status,
				      IPMI_ERR_UNSPECIFIED);
	पूर्ण
	वापस SI_SM_CALL_WITH_DELAY;
पूर्ण

अटल पूर्णांक bt_detect(काष्ठा si_sm_data *bt)
अणु
	अचिन्हित अक्षर GetBT_CAP[] = अणु 0x18, 0x36 पूर्ण;
	अचिन्हित अक्षर BT_CAP[8];
	क्रमागत si_sm_result smi_result;
	पूर्णांक rv;

	/*
	 * It's impossible क्रम the BT status and पूर्णांकerrupt रेजिस्टरs to be
	 * all 1's, (assuming a properly functioning, self-initialized BMC)
	 * but that's what you get from पढ़ोing a bogus address, so we
	 * test that first.  The calling routine uses negative logic.
	 */

	अगर ((BT_STATUS == 0xFF) && (BT_INTMASK_R == 0xFF))
		वापस 1;
	reset_flags(bt);

	/*
	 * Try getting the BT capabilities here.
	 */
	rv = bt_start_transaction(bt, GetBT_CAP, माप(GetBT_CAP));
	अगर (rv) अणु
		dev_warn(bt->io->dev,
			 "Can't start capabilities transaction: %d\n", rv);
		जाओ out_no_bt_cap;
	पूर्ण

	smi_result = SI_SM_CALL_WITHOUT_DELAY;
	क्रम (;;) अणु
		अगर (smi_result == SI_SM_CALL_WITH_DELAY ||
		    smi_result == SI_SM_CALL_WITH_TICK_DELAY) अणु
			schedule_समयout_unपूर्णांकerruptible(1);
			smi_result = bt_event(bt, jअगरfies_to_usecs(1));
		पूर्ण अन्यथा अगर (smi_result == SI_SM_CALL_WITHOUT_DELAY) अणु
			smi_result = bt_event(bt, 0);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	rv = bt_get_result(bt, BT_CAP, माप(BT_CAP));
	bt_init_data(bt, bt->io);
	अगर (rv < 8) अणु
		dev_warn(bt->io->dev, "bt cap response too short: %d\n", rv);
		जाओ out_no_bt_cap;
	पूर्ण

	अगर (BT_CAP[2]) अणु
		dev_warn(bt->io->dev, "Error fetching bt cap: %x\n", BT_CAP[2]);
out_no_bt_cap:
		dev_warn(bt->io->dev, "using default values\n");
	पूर्ण अन्यथा अणु
		bt->BT_CAP_req2rsp = BT_CAP[6] * USEC_PER_SEC;
		bt->BT_CAP_retries = BT_CAP[7];
	पूर्ण

	dev_info(bt->io->dev, "req2rsp=%ld secs retries=%d\n",
		 bt->BT_CAP_req2rsp / USEC_PER_SEC, bt->BT_CAP_retries);

	वापस 0;
पूर्ण

अटल व्योम bt_cleanup(काष्ठा si_sm_data *bt)
अणु
पूर्ण

अटल पूर्णांक bt_size(व्योम)
अणु
	वापस माप(काष्ठा si_sm_data);
पूर्ण

स्थिर काष्ठा si_sm_handlers bt_smi_handlers = अणु
	.init_data		= bt_init_data,
	.start_transaction	= bt_start_transaction,
	.get_result		= bt_get_result,
	.event			= bt_event,
	.detect			= bt_detect,
	.cleanup		= bt_cleanup,
	.size			= bt_size,
पूर्ण;
