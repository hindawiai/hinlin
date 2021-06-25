<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 2001, 2007
 * Authors: 	Fritz Elfert (felfert@millenux.com)
 * 		Peter Tiedemann (ptiedem@de.ibm.com)
 * 	MPC additions :
 *		Belinda Thompson (belindat@us.ibm.com)
 *		Andy Richter (richtera@us.ibm.com)
 */
#अगर_अघोषित _CTCM_FSMS_H_
#घोषणा _CTCM_FSMS_H_

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/bitops.h>

#समावेश <linux/संकेत.स>
#समावेश <linux/माला.स>

#समावेश <linux/ip.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/प्रकार.स>
#समावेश <net/dst.h>

#समावेश <linux/पन.स>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/ccwgroup.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/idals.h>

#समावेश "fsm.h"
#समावेश "ctcm_main.h"

/*
 * Definitions क्रम the channel statemachine(s) क्रम ctc and ctcmpc
 *
 * To allow better kerntyping, prefix-less definitions क्रम channel states
 * and channel events have been replaced :
 * ch_event... -> ctc_ch_event...
 * CH_EVENT... -> CTC_EVENT...
 * ch_state... -> ctc_ch_state...
 * CH_STATE... -> CTC_STATE...
 */
/*
 * Events of the channel statemachine(s) क्रम ctc and ctcmpc
 */
क्रमागत ctc_ch_events अणु
	/*
	 * Events, representing वापस code of
	 * I/O operations (ccw_device_start, ccw_device_halt et al.)
	 */
	CTC_EVENT_IO_SUCCESS,
	CTC_EVENT_IO_EBUSY,
	CTC_EVENT_IO_ENODEV,
	CTC_EVENT_IO_UNKNOWN,

	CTC_EVENT_ATTNBUSY,
	CTC_EVENT_ATTN,
	CTC_EVENT_BUSY,
	/*
	 * Events, representing unit-check
	 */
	CTC_EVENT_UC_RCRESET,
	CTC_EVENT_UC_RSRESET,
	CTC_EVENT_UC_TXTIMEOUT,
	CTC_EVENT_UC_TXPARITY,
	CTC_EVENT_UC_HWFAIL,
	CTC_EVENT_UC_RXPARITY,
	CTC_EVENT_UC_ZERO,
	CTC_EVENT_UC_UNKNOWN,
	/*
	 * Events, representing subchannel-check
	 */
	CTC_EVENT_SC_UNKNOWN,
	/*
	 * Events, representing machine checks
	 */
	CTC_EVENT_MC_FAIL,
	CTC_EVENT_MC_GOOD,
	/*
	 * Event, representing normal IRQ
	 */
	CTC_EVENT_IRQ,
	CTC_EVENT_FINSTAT,
	/*
	 * Event, representing समयr expiry.
	 */
	CTC_EVENT_TIMER,
	/*
	 * Events, representing commands from upper levels.
	 */
	CTC_EVENT_START,
	CTC_EVENT_STOP,
	CTC_NR_EVENTS,
	/*
	 * additional MPC events
	 */
	CTC_EVENT_SEND_XID = CTC_NR_EVENTS,
	CTC_EVENT_RSWEEP_TIMER,
	/*
	 * MUST be always the last element!!
	 */
	CTC_MPC_NR_EVENTS,
पूर्ण;

/*
 * States of the channel statemachine(s) क्रम ctc and ctcmpc.
 */
क्रमागत ctc_ch_states अणु
	/*
	 * Channel not asचिन्हित to any device,
	 * initial state, direction invalid
	 */
	CTC_STATE_IDLE,
	/*
	 * Channel asचिन्हित but not operating
	 */
	CTC_STATE_STOPPED,
	CTC_STATE_STARTWAIT,
	CTC_STATE_STARTRETRY,
	CTC_STATE_SETUPWAIT,
	CTC_STATE_RXINIT,
	CTC_STATE_TXINIT,
	CTC_STATE_RX,
	CTC_STATE_TX,
	CTC_STATE_RXIDLE,
	CTC_STATE_TXIDLE,
	CTC_STATE_RXERR,
	CTC_STATE_TXERR,
	CTC_STATE_TERM,
	CTC_STATE_DTERM,
	CTC_STATE_NOTOP,
	CTC_NR_STATES,     /* MUST be the last element of non-expanded states */
	/*
	 * additional MPC states
	 */
	CH_XID0_PENDING = CTC_NR_STATES,
	CH_XID0_INPROGRESS,
	CH_XID7_PENDING,
	CH_XID7_PENDING1,
	CH_XID7_PENDING2,
	CH_XID7_PENDING3,
	CH_XID7_PENDING4,
	CTC_MPC_NR_STATES, /* MUST be the last element of expanded mpc states */
पूर्ण;

बाह्य स्थिर अक्षर *ctc_ch_event_names[];

बाह्य स्थिर अक्षर *ctc_ch_state_names[];

व्योम ctcm_ccw_check_rc(काष्ठा channel *ch, पूर्णांक rc, अक्षर *msg);
व्योम ctcm_purge_skb_queue(काष्ठा sk_buff_head *q);

/*
 * ----- non-अटल actions क्रम ctcm channel statemachine -----
 *
 */
व्योम ctcm_chx_txidle(fsm_instance *fi, पूर्णांक event, व्योम *arg);

/*
 * ----- FSM (state/event/action) of the ctcm channel statemachine -----
 */
बाह्य स्थिर fsm_node ch_fsm[];
बाह्य पूर्णांक ch_fsm_len;


/*
 * ----- non-अटल actions क्रम ctcmpc channel statemachine ----
 *
 */
/* shared :
व्योम ctcm_chx_txidle(fsm_instance * fi, पूर्णांक event, व्योम *arg);
 */
व्योम ctcmpc_chx_rxidle(fsm_instance *fi, पूर्णांक event, व्योम *arg);

/*
 * ----- FSM (state/event/action) of the ctcmpc channel statemachine -----
 */
बाह्य स्थिर fsm_node ctcmpc_ch_fsm[];
बाह्य पूर्णांक mpc_ch_fsm_len;

/*
 * Definitions क्रम the device पूर्णांकerface statemachine क्रम ctc and mpc
 */

/*
 * States of the device पूर्णांकerface statemachine.
 */
क्रमागत dev_states अणु
	DEV_STATE_STOPPED,
	DEV_STATE_STARTWAIT_RXTX,
	DEV_STATE_STARTWAIT_RX,
	DEV_STATE_STARTWAIT_TX,
	DEV_STATE_STOPWAIT_RXTX,
	DEV_STATE_STOPWAIT_RX,
	DEV_STATE_STOPWAIT_TX,
	DEV_STATE_RUNNING,
	/*
	 * MUST be always the last element!!
	 */
	CTCM_NR_DEV_STATES
पूर्ण;

बाह्य स्थिर अक्षर *dev_state_names[];

/*
 * Events of the device पूर्णांकerface statemachine.
 * ctcm and ctcmpc
 */
क्रमागत dev_events अणु
	DEV_EVENT_START,
	DEV_EVENT_STOP,
	DEV_EVENT_RXUP,
	DEV_EVENT_TXUP,
	DEV_EVENT_RXDOWN,
	DEV_EVENT_TXDOWN,
	DEV_EVENT_RESTART,
	/*
	 * MUST be always the last element!!
	 */
	CTCM_NR_DEV_EVENTS
पूर्ण;

बाह्य स्थिर अक्षर *dev_event_names[];

/*
 * Actions क्रम the device पूर्णांकerface statemachine.
 * ctc and ctcmpc
 */
/*
अटल व्योम dev_action_start(fsm_instance * fi, पूर्णांक event, व्योम *arg);
अटल व्योम dev_action_stop(fsm_instance * fi, पूर्णांक event, व्योम *arg);
अटल व्योम dev_action_restart(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम dev_action_chup(fsm_instance * fi, पूर्णांक event, व्योम *arg);
अटल व्योम dev_action_chकरोwn(fsm_instance * fi, पूर्णांक event, व्योम *arg);
*/

/*
 * The (state/event/action) fsm table of the device पूर्णांकerface statemachine.
 * ctcm and ctcmpc
 */
बाह्य स्थिर fsm_node dev_fsm[];
बाह्य पूर्णांक dev_fsm_len;


/*
 * Definitions क्रम the MPC Group statemachine
 */

/*
 * MPC Group Station FSM States

State Name		When In This State
======================	=======================================
MPCG_STATE_RESET	Initial State When Driver Loaded
			We receive and send NOTHING

MPCG_STATE_INOP         INOP Received.
			Group level non-recoverable error

MPCG_STATE_READY	XID exchanges क्रम at least 1 ग_लिखो and
			1 पढ़ो channel have completed.
			Group is पढ़ोy क्रम data transfer.

States from ctc_mpc_alloc_channel
==============================================================
MPCG_STATE_XID2INITW	Aरुकोing XID2(0) Initiation
			      ATTN from other side will start
			      XID negotiations.
			      Y-side protocol only.

MPCG_STATE_XID2INITX	XID2(0) negotiations are in progress.
			      At least 1, but not all, XID2(0)'s
			      have been received from partner.

MPCG_STATE_XID7INITW	XID2(0) complete
			      No XID2(7)'s have yet been received.
			      XID2(7) negotiations pending.

MPCG_STATE_XID7INITX	XID2(7) negotiations in progress.
			      At least 1, but not all, XID2(7)'s
			      have been received from partner.

MPCG_STATE_XID7INITF	XID2(7) negotiations complete.
			      Transitioning to READY.

MPCG_STATE_READY	      Ready क्रम Data Transfer.


States from ctc_mpc_establish_connectivity call
==============================================================
MPCG_STATE_XID0IOWAIT	Initiating XID2(0) negotiations.
			      X-side protocol only.
			      ATTN-BUSY from other side will convert
			      this to Y-side protocol and the
			      ctc_mpc_alloc_channel flow will begin.

MPCG_STATE_XID0IOWAIX	XID2(0) negotiations are in progress.
			      At least 1, but not all, XID2(0)'s
			      have been received from partner.

MPCG_STATE_XID7INITI	XID2(0) complete
			      No XID2(7)'s have yet been received.
			      XID2(7) negotiations pending.

MPCG_STATE_XID7INITZ	XID2(7) negotiations in progress.
			      At least 1, but not all, XID2(7)'s
			      have been received from partner.

MPCG_STATE_XID7INITF	XID2(7) negotiations complete.
			      Transitioning to READY.

MPCG_STATE_READY	      Ready क्रम Data Transfer.

*/

क्रमागत mpcg_events अणु
	MPCG_EVENT_INOP,
	MPCG_EVENT_DISCONC,
	MPCG_EVENT_XID0DO,
	MPCG_EVENT_XID2,
	MPCG_EVENT_XID2DONE,
	MPCG_EVENT_XID7DONE,
	MPCG_EVENT_TIMER,
	MPCG_EVENT_DOIO,
	MPCG_NR_EVENTS,
पूर्ण;

क्रमागत mpcg_states अणु
	MPCG_STATE_RESET,
	MPCG_STATE_INOP,
	MPCG_STATE_XID2INITW,
	MPCG_STATE_XID2INITX,
	MPCG_STATE_XID7INITW,
	MPCG_STATE_XID7INITX,
	MPCG_STATE_XID0IOWAIT,
	MPCG_STATE_XID0IOWAIX,
	MPCG_STATE_XID7INITI,
	MPCG_STATE_XID7INITZ,
	MPCG_STATE_XID7INITF,
	MPCG_STATE_FLOWC,
	MPCG_STATE_READY,
	MPCG_NR_STATES,
पूर्ण;

#पूर्ण_अगर
/* --- This is the END my मित्र --- */
