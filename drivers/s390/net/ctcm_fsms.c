<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2001, 2007
 * Authors:	Fritz Elfert (felfert@millenux.com)
 * 		Peter Tiedemann (ptiedem@de.ibm.com)
 *	MPC additions :
 *		Belinda Thompson (belindat@us.ibm.com)
 *		Andy Richter (richtera@us.ibm.com)
 */

#अघोषित DEBUG
#अघोषित DEBUGDATA
#अघोषित DEBUGCCW

#घोषणा KMSG_COMPONENT "ctcm"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

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

#समावेश "ctcm_dbug.h"
#समावेश "ctcm_main.h"
#समावेश "ctcm_fsms.h"

स्थिर अक्षर *dev_state_names[] = अणु
	[DEV_STATE_STOPPED]		= "Stopped",
	[DEV_STATE_STARTWAIT_RXTX]	= "StartWait RXTX",
	[DEV_STATE_STARTWAIT_RX]	= "StartWait RX",
	[DEV_STATE_STARTWAIT_TX]	= "StartWait TX",
	[DEV_STATE_STOPWAIT_RXTX]	= "StopWait RXTX",
	[DEV_STATE_STOPWAIT_RX]		= "StopWait RX",
	[DEV_STATE_STOPWAIT_TX]		= "StopWait TX",
	[DEV_STATE_RUNNING]		= "Running",
पूर्ण;

स्थिर अक्षर *dev_event_names[] = अणु
	[DEV_EVENT_START]	= "Start",
	[DEV_EVENT_STOP]	= "Stop",
	[DEV_EVENT_RXUP]	= "RX up",
	[DEV_EVENT_TXUP]	= "TX up",
	[DEV_EVENT_RXDOWN]	= "RX down",
	[DEV_EVENT_TXDOWN]	= "TX down",
	[DEV_EVENT_RESTART]	= "Restart",
पूर्ण;

स्थिर अक्षर *ctc_ch_event_names[] = अणु
	[CTC_EVENT_IO_SUCCESS]	= "ccw_device success",
	[CTC_EVENT_IO_EBUSY]	= "ccw_device busy",
	[CTC_EVENT_IO_ENODEV]	= "ccw_device enodev",
	[CTC_EVENT_IO_UNKNOWN]	= "ccw_device unknown",
	[CTC_EVENT_ATTNBUSY]	= "Status ATTN & BUSY",
	[CTC_EVENT_ATTN]	= "Status ATTN",
	[CTC_EVENT_BUSY]	= "Status BUSY",
	[CTC_EVENT_UC_RCRESET]	= "Unit check remote reset",
	[CTC_EVENT_UC_RSRESET]	= "Unit check remote system reset",
	[CTC_EVENT_UC_TXTIMEOUT] = "Unit check TX timeout",
	[CTC_EVENT_UC_TXPARITY]	= "Unit check TX parity",
	[CTC_EVENT_UC_HWFAIL]	= "Unit check Hardware failure",
	[CTC_EVENT_UC_RXPARITY]	= "Unit check RX parity",
	[CTC_EVENT_UC_ZERO]	= "Unit check ZERO",
	[CTC_EVENT_UC_UNKNOWN]	= "Unit check Unknown",
	[CTC_EVENT_SC_UNKNOWN]	= "SubChannel check Unknown",
	[CTC_EVENT_MC_FAIL]	= "Machine check failure",
	[CTC_EVENT_MC_GOOD]	= "Machine check operational",
	[CTC_EVENT_IRQ]		= "IRQ normal",
	[CTC_EVENT_FINSTAT]	= "IRQ final",
	[CTC_EVENT_TIMER]	= "Timer",
	[CTC_EVENT_START]	= "Start",
	[CTC_EVENT_STOP]	= "Stop",
	/*
	* additional MPC events
	*/
	[CTC_EVENT_SEND_XID]	= "XID Exchange",
	[CTC_EVENT_RSWEEP_TIMER] = "MPC Group Sweep Timer",
पूर्ण;

स्थिर अक्षर *ctc_ch_state_names[] = अणु
	[CTC_STATE_IDLE]	= "Idle",
	[CTC_STATE_STOPPED]	= "Stopped",
	[CTC_STATE_STARTWAIT]	= "StartWait",
	[CTC_STATE_STARTRETRY]	= "StartRetry",
	[CTC_STATE_SETUPWAIT]	= "SetupWait",
	[CTC_STATE_RXINIT]	= "RX init",
	[CTC_STATE_TXINIT]	= "TX init",
	[CTC_STATE_RX]		= "RX",
	[CTC_STATE_TX]		= "TX",
	[CTC_STATE_RXIDLE]	= "RX idle",
	[CTC_STATE_TXIDLE]	= "TX idle",
	[CTC_STATE_RXERR]	= "RX error",
	[CTC_STATE_TXERR]	= "TX error",
	[CTC_STATE_TERM]	= "Terminating",
	[CTC_STATE_DTERM]	= "Restarting",
	[CTC_STATE_NOTOP]	= "Not operational",
	/*
	* additional MPC states
	*/
	[CH_XID0_PENDING]	= "Pending XID0 Start",
	[CH_XID0_INPROGRESS]	= "In XID0 Negotiations ",
	[CH_XID7_PENDING]	= "Pending XID7 P1 Start",
	[CH_XID7_PENDING1]	= "Active XID7 P1 Exchange ",
	[CH_XID7_PENDING2]	= "Pending XID7 P2 Start ",
	[CH_XID7_PENDING3]	= "Active XID7 P2 Exchange ",
	[CH_XID7_PENDING4]	= "XID7 Complete - Pending READY ",
पूर्ण;

अटल व्योम ctcm_action_nop(fsm_instance *fi, पूर्णांक event, व्योम *arg);

/*
 * ----- अटल ctcm actions क्रम channel statemachine -----
 *
*/
अटल व्योम chx_txकरोne(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम chx_rx(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम chx_rxidle(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम chx_firstio(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_seपंचांगode(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_start(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_haltio(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_stopped(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_stop(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_fail(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_setuperr(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_restart(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_rxiniterr(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_rxinitfail(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_rxdisc(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_txiniterr(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_txretry(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_iofatal(fsm_instance *fi, पूर्णांक event, व्योम *arg);

/*
 * ----- अटल ctcmpc actions क्रम ctcmpc channel statemachine -----
 *
*/
अटल व्योम ctcmpc_chx_txकरोne(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcmpc_chx_rx(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcmpc_chx_firstio(fsm_instance *fi, पूर्णांक event, व्योम *arg);
/* shared :
अटल व्योम ctcm_chx_seपंचांगode(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_start(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_haltio(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_stopped(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_stop(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_fail(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_setuperr(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_restart(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_rxiniterr(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_rxinitfail(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_rxdisc(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_txiniterr(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_txretry(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम ctcm_chx_iofatal(fsm_instance *fi, पूर्णांक event, व्योम *arg);
*/
अटल व्योम ctcmpc_chx_attn(fsm_instance *fsm, पूर्णांक event, व्योम *arg);
अटल व्योम ctcmpc_chx_attnbusy(fsm_instance *, पूर्णांक, व्योम *);
अटल व्योम ctcmpc_chx_resend(fsm_instance *, पूर्णांक, व्योम *);
अटल व्योम ctcmpc_chx_send_sweep(fsm_instance *fsm, पूर्णांक event, व्योम *arg);

/**
 * Check वापस code of a preceding ccw_device call, halt_IO etc...
 *
 * ch	:	The channel, the error beदीर्घs to.
 * Returns the error code (!= 0) to inspect.
 */
व्योम ctcm_ccw_check_rc(काष्ठा channel *ch, पूर्णांक rc, अक्षर *msg)
अणु
	CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
		"%s(%s): %s: %04x\n",
		CTCM_FUNTAIL, ch->id, msg, rc);
	चयन (rc) अणु
	हाल -EBUSY:
		pr_info("%s: The communication peer is busy\n",
			ch->id);
		fsm_event(ch->fsm, CTC_EVENT_IO_EBUSY, ch);
		अवरोध;
	हाल -ENODEV:
		pr_err("%s: The specified target device is not valid\n",
		       ch->id);
		fsm_event(ch->fsm, CTC_EVENT_IO_ENODEV, ch);
		अवरोध;
	शेष:
		pr_err("An I/O operation resulted in error %04x\n",
		       rc);
		fsm_event(ch->fsm, CTC_EVENT_IO_UNKNOWN, ch);
	पूर्ण
पूर्ण

व्योम ctcm_purge_skb_queue(काष्ठा sk_buff_head *q)
अणु
	काष्ठा sk_buff *skb;

	CTCM_DBF_TEXT(TRACE, CTC_DBF_DEBUG, __func__);

	जबतक ((skb = skb_dequeue(q))) अणु
		refcount_dec(&skb->users);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

/**
 * NOP action क्रम statemachines
 */
अटल व्योम ctcm_action_nop(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
पूर्ण

/*
 * Actions क्रम channel - statemachines.
 */

/**
 * Normal data has been send. Free the corresponding
 * skb (it's in io_queue), reset dev->tbusy and
 * revert to idle state.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम chx_txकरोne(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	काष्ठा sk_buff *skb;
	पूर्णांक first = 1;
	पूर्णांक i;
	अचिन्हित दीर्घ duration;
	अचिन्हित दीर्घ करोne_stamp = jअगरfies;

	CTCM_PR_DEBUG("%s(%s): %s\n", __func__, ch->id, dev->name);

	duration = करोne_stamp - ch->prof.send_stamp;
	अगर (duration > ch->prof.tx_समय)
		ch->prof.tx_समय = duration;

	अगर (ch->irb->scsw.cmd.count != 0)
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_DEBUG,
			"%s(%s): TX not complete, remaining %d bytes",
			     CTCM_FUNTAIL, dev->name, ch->irb->scsw.cmd.count);
	fsm_delसमयr(&ch->समयr);
	जबतक ((skb = skb_dequeue(&ch->io_queue))) अणु
		priv->stats.tx_packets++;
		priv->stats.tx_bytes += skb->len - LL_HEADER_LENGTH;
		अगर (first) अणु
			priv->stats.tx_bytes += 2;
			first = 0;
		पूर्ण
		refcount_dec(&skb->users);
		dev_kमुक्त_skb_irq(skb);
	पूर्ण
	spin_lock(&ch->collect_lock);
	clear_normalized_cda(&ch->ccw[4]);
	अगर (ch->collect_len > 0) अणु
		पूर्णांक rc;

		अगर (ctcm_checkalloc_buffer(ch)) अणु
			spin_unlock(&ch->collect_lock);
			वापस;
		पूर्ण
		ch->trans_skb->data = ch->trans_skb_data;
		skb_reset_tail_poपूर्णांकer(ch->trans_skb);
		ch->trans_skb->len = 0;
		अगर (ch->prof.maxmulti < (ch->collect_len + 2))
			ch->prof.maxmulti = ch->collect_len + 2;
		अगर (ch->prof.maxcqueue < skb_queue_len(&ch->collect_queue))
			ch->prof.maxcqueue = skb_queue_len(&ch->collect_queue);
		*((__u16 *)skb_put(ch->trans_skb, 2)) = ch->collect_len + 2;
		i = 0;
		जबतक ((skb = skb_dequeue(&ch->collect_queue))) अणु
			skb_copy_from_linear_data(skb,
				skb_put(ch->trans_skb, skb->len), skb->len);
			priv->stats.tx_packets++;
			priv->stats.tx_bytes += skb->len - LL_HEADER_LENGTH;
			refcount_dec(&skb->users);
			dev_kमुक्त_skb_irq(skb);
			i++;
		पूर्ण
		ch->collect_len = 0;
		spin_unlock(&ch->collect_lock);
		ch->ccw[1].count = ch->trans_skb->len;
		fsm_addसमयr(&ch->समयr, CTCM_TIME_5_SEC, CTC_EVENT_TIMER, ch);
		ch->prof.send_stamp = jअगरfies;
		rc = ccw_device_start(ch->cdev, &ch->ccw[0], 0, 0xff, 0);
		ch->prof.करोios_multi++;
		अगर (rc != 0) अणु
			priv->stats.tx_dropped += i;
			priv->stats.tx_errors += i;
			fsm_delसमयr(&ch->समयr);
			ctcm_ccw_check_rc(ch, rc, "chained TX");
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock(&ch->collect_lock);
		fsm_newstate(fi, CTC_STATE_TXIDLE);
	पूर्ण
	ctcm_clear_busy_करो(dev);
पूर्ण

/**
 * Initial data is sent.
 * Notअगरy device statemachine that we are up and
 * running.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
व्योम ctcm_chx_txidle(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;

	CTCM_PR_DEBUG("%s(%s): %s\n", __func__, ch->id, dev->name);

	fsm_delसमयr(&ch->समयr);
	fsm_newstate(fi, CTC_STATE_TXIDLE);
	fsm_event(priv->fsm, DEV_EVENT_TXUP, ch->netdev);
पूर्ण

/**
 * Got normal data, check क्रम sanity, queue it up, allocate new buffer
 * trigger bottom half, and initiate next पढ़ो.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम chx_rx(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	पूर्णांक len = ch->max_bufsize - ch->irb->scsw.cmd.count;
	काष्ठा sk_buff *skb = ch->trans_skb;
	__u16 block_len = *((__u16 *)skb->data);
	पूर्णांक check_len;
	पूर्णांक rc;

	fsm_delसमयr(&ch->समयr);
	अगर (len < 8) अणु
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_NOTICE,
			"%s(%s): got packet with length %d < 8\n",
					CTCM_FUNTAIL, dev->name, len);
		priv->stats.rx_dropped++;
		priv->stats.rx_length_errors++;
						जाओ again;
	पूर्ण
	अगर (len > ch->max_bufsize) अणु
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_NOTICE,
			"%s(%s): got packet with length %d > %d\n",
				CTCM_FUNTAIL, dev->name, len, ch->max_bufsize);
		priv->stats.rx_dropped++;
		priv->stats.rx_length_errors++;
						जाओ again;
	पूर्ण

	/*
	 * VM TCP seems to have a bug sending 2 trailing bytes of garbage.
	 */
	चयन (ch->protocol) अणु
	हाल CTCM_PROTO_S390:
	हाल CTCM_PROTO_OS390:
		check_len = block_len + 2;
		अवरोध;
	शेष:
		check_len = block_len;
		अवरोध;
	पूर्ण
	अगर ((len < block_len) || (len > check_len)) अणु
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_NOTICE,
			"%s(%s): got block length %d != rx length %d\n",
				CTCM_FUNTAIL, dev->name, block_len, len);
		अगर (करो_debug)
			ctcmpc_dump_skb(skb, 0);

		*((__u16 *)skb->data) = len;
		priv->stats.rx_dropped++;
		priv->stats.rx_length_errors++;
						जाओ again;
	पूर्ण
	अगर (block_len > 2) अणु
		*((__u16 *)skb->data) = block_len - 2;
		ctcm_unpack_skb(ch, skb);
	पूर्ण
 again:
	skb->data = ch->trans_skb_data;
	skb_reset_tail_poपूर्णांकer(skb);
	skb->len = 0;
	अगर (ctcm_checkalloc_buffer(ch))
		वापस;
	ch->ccw[1].count = ch->max_bufsize;
	rc = ccw_device_start(ch->cdev, &ch->ccw[0], 0, 0xff, 0);
	अगर (rc != 0)
		ctcm_ccw_check_rc(ch, rc, "normal RX");
पूर्ण

/**
 * Initialize connection by sending a __u16 of value 0.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम chx_firstio(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	पूर्णांक rc;
	काष्ठा channel *ch = arg;
	पूर्णांक fsmstate = fsm_माला_लोtate(fi);

	CTCM_DBF_TEXT_(TRACE, CTC_DBF_NOTICE,
		"%s(%s) : %02x",
		CTCM_FUNTAIL, ch->id, fsmstate);

	ch->sense_rc = 0;	/* reset unit check report control */
	अगर (fsmstate == CTC_STATE_TXIDLE)
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_DEBUG,
			"%s(%s): remote side issued READ?, init.\n",
				CTCM_FUNTAIL, ch->id);
	fsm_delसमयr(&ch->समयr);
	अगर (ctcm_checkalloc_buffer(ch))
		वापस;
	अगर ((fsmstate == CTC_STATE_SETUPWAIT) &&
	    (ch->protocol == CTCM_PROTO_OS390)) अणु
		/* OS/390 resp. z/OS */
		अगर (CHANNEL_सूचीECTION(ch->flags) == CTCM_READ) अणु
			*((__u16 *)ch->trans_skb->data) = CTCM_INITIAL_BLOCKLEN;
			fsm_addसमयr(&ch->समयr, CTCM_TIME_5_SEC,
				     CTC_EVENT_TIMER, ch);
			chx_rxidle(fi, event, arg);
		पूर्ण अन्यथा अणु
			काष्ठा net_device *dev = ch->netdev;
			काष्ठा ctcm_priv *priv = dev->ml_priv;
			fsm_newstate(fi, CTC_STATE_TXIDLE);
			fsm_event(priv->fsm, DEV_EVENT_TXUP, dev);
		पूर्ण
		वापस;
	पूर्ण
	/*
	 * Don't setup a समयr क्रम receiving the initial RX frame
	 * अगर in compatibility mode, since VM TCP delays the initial
	 * frame until it has some data to send.
	 */
	अगर ((CHANNEL_सूचीECTION(ch->flags) == CTCM_WRITE) ||
	    (ch->protocol != CTCM_PROTO_S390))
		fsm_addसमयr(&ch->समयr, CTCM_TIME_5_SEC, CTC_EVENT_TIMER, ch);

	*((__u16 *)ch->trans_skb->data) = CTCM_INITIAL_BLOCKLEN;
	ch->ccw[1].count = 2;	/* Transfer only length */

	fsm_newstate(fi, (CHANNEL_सूचीECTION(ch->flags) == CTCM_READ)
		     ? CTC_STATE_RXINIT : CTC_STATE_TXINIT);
	rc = ccw_device_start(ch->cdev, &ch->ccw[0], 0, 0xff, 0);
	अगर (rc != 0) अणु
		fsm_delसमयr(&ch->समयr);
		fsm_newstate(fi, CTC_STATE_SETUPWAIT);
		ctcm_ccw_check_rc(ch, rc, "init IO");
	पूर्ण
	/*
	 * If in compatibility mode since we करोn't setup a समयr, we
	 * also संकेत RX channel up immediately. This enables us
	 * to send packets early which in turn usually triggers some
	 * reply from VM TCP which brings up the RX channel to it's
	 * final state.
	 */
	अगर ((CHANNEL_सूचीECTION(ch->flags) == CTCM_READ) &&
	    (ch->protocol == CTCM_PROTO_S390)) अणु
		काष्ठा net_device *dev = ch->netdev;
		काष्ठा ctcm_priv *priv = dev->ml_priv;
		fsm_event(priv->fsm, DEV_EVENT_RXUP, dev);
	पूर्ण
पूर्ण

/**
 * Got initial data, check it. If OK,
 * notअगरy device statemachine that we are up and
 * running.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम chx_rxidle(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	__u16 buflen;
	पूर्णांक rc;

	fsm_delसमयr(&ch->समयr);
	buflen = *((__u16 *)ch->trans_skb->data);
	CTCM_PR_DEBUG("%s: %s: Initial RX count = %d\n",
			__func__, dev->name, buflen);

	अगर (buflen >= CTCM_INITIAL_BLOCKLEN) अणु
		अगर (ctcm_checkalloc_buffer(ch))
			वापस;
		ch->ccw[1].count = ch->max_bufsize;
		fsm_newstate(fi, CTC_STATE_RXIDLE);
		rc = ccw_device_start(ch->cdev, &ch->ccw[0], 0, 0xff, 0);
		अगर (rc != 0) अणु
			fsm_newstate(fi, CTC_STATE_RXINIT);
			ctcm_ccw_check_rc(ch, rc, "initial RX");
		पूर्ण अन्यथा
			fsm_event(priv->fsm, DEV_EVENT_RXUP, dev);
	पूर्ण अन्यथा अणु
		CTCM_PR_DEBUG("%s: %s: Initial RX count %d not %d\n",
				__func__, dev->name,
					buflen, CTCM_INITIAL_BLOCKLEN);
		chx_firstio(fi, event, arg);
	पूर्ण
पूर्ण

/**
 * Set channel पूर्णांकo extended mode.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcm_chx_seपंचांगode(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	पूर्णांक rc;
	अचिन्हित दीर्घ saveflags = 0;
	पूर्णांक समयout = CTCM_TIME_5_SEC;

	fsm_delसमयr(&ch->समयr);
	अगर (IS_MPC(ch)) अणु
		समयout = 1500;
		CTCM_PR_DEBUG("enter %s: cp=%i ch=0x%p id=%s\n",
				__func__, smp_processor_id(), ch, ch->id);
	पूर्ण
	fsm_addसमयr(&ch->समयr, समयout, CTC_EVENT_TIMER, ch);
	fsm_newstate(fi, CTC_STATE_SETUPWAIT);
	CTCM_CCW_DUMP((अक्षर *)&ch->ccw[6], माप(काष्ठा ccw1) * 2);

	अगर (event == CTC_EVENT_TIMER)	/* only क्रम समयr not yet locked */
		spin_lock_irqsave(get_ccwdev_lock(ch->cdev), saveflags);
			/* Such conditional locking is undeterministic in
			 * अटल view. => ignore sparse warnings here. */

	rc = ccw_device_start(ch->cdev, &ch->ccw[6], 0, 0xff, 0);
	अगर (event == CTC_EVENT_TIMER)	/* see above comments */
		spin_unlock_irqrestore(get_ccwdev_lock(ch->cdev), saveflags);
	अगर (rc != 0) अणु
		fsm_delसमयr(&ch->समयr);
		fsm_newstate(fi, CTC_STATE_STARTWAIT);
		ctcm_ccw_check_rc(ch, rc, "set Mode");
	पूर्ण अन्यथा
		ch->retry = 0;
पूर्ण

/**
 * Setup channel.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcm_chx_start(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch	= arg;
	अचिन्हित दीर्घ saveflags;
	पूर्णांक rc;

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO, "%s(%s): %s",
		CTCM_FUNTAIL, ch->id,
		(CHANNEL_सूचीECTION(ch->flags) == CTCM_READ) ? "RX" : "TX");

	अगर (ch->trans_skb != शून्य) अणु
		clear_normalized_cda(&ch->ccw[1]);
		dev_kमुक्त_skb(ch->trans_skb);
		ch->trans_skb = शून्य;
	पूर्ण
	अगर (CHANNEL_सूचीECTION(ch->flags) == CTCM_READ) अणु
		ch->ccw[1].cmd_code = CCW_CMD_READ;
		ch->ccw[1].flags = CCW_FLAG_SLI;
		ch->ccw[1].count = 0;
	पूर्ण अन्यथा अणु
		ch->ccw[1].cmd_code = CCW_CMD_WRITE;
		ch->ccw[1].flags = CCW_FLAG_SLI | CCW_FLAG_CC;
		ch->ccw[1].count = 0;
	पूर्ण
	अगर (ctcm_checkalloc_buffer(ch)) अणु
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_DEBUG,
			"%s(%s): %s trans_skb alloc delayed "
			"until first transfer",
			CTCM_FUNTAIL, ch->id,
			(CHANNEL_सूचीECTION(ch->flags) == CTCM_READ) ?
				"RX" : "TX");
	पूर्ण
	ch->ccw[0].cmd_code = CCW_CMD_PREPARE;
	ch->ccw[0].flags = CCW_FLAG_SLI | CCW_FLAG_CC;
	ch->ccw[0].count = 0;
	ch->ccw[0].cda = 0;
	ch->ccw[2].cmd_code = CCW_CMD_NOOP;	/* joपूर्णांकed CE + DE */
	ch->ccw[2].flags = CCW_FLAG_SLI;
	ch->ccw[2].count = 0;
	ch->ccw[2].cda = 0;
	स_नकल(&ch->ccw[3], &ch->ccw[0], माप(काष्ठा ccw1) * 3);
	ch->ccw[4].cda = 0;
	ch->ccw[4].flags &= ~CCW_FLAG_IDA;

	fsm_newstate(fi, CTC_STATE_STARTWAIT);
	fsm_addसमयr(&ch->समयr, 1000, CTC_EVENT_TIMER, ch);
	spin_lock_irqsave(get_ccwdev_lock(ch->cdev), saveflags);
	rc = ccw_device_halt(ch->cdev, 0);
	spin_unlock_irqrestore(get_ccwdev_lock(ch->cdev), saveflags);
	अगर (rc != 0) अणु
		अगर (rc != -EBUSY)
			fsm_delसमयr(&ch->समयr);
		ctcm_ccw_check_rc(ch, rc, "initial HaltIO");
	पूर्ण
पूर्ण

/**
 * Shutकरोwn a channel.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcm_chx_haltio(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	अचिन्हित दीर्घ saveflags = 0;
	पूर्णांक rc;
	पूर्णांक oldstate;

	fsm_delसमयr(&ch->समयr);
	अगर (IS_MPC(ch))
		fsm_delसमयr(&ch->sweep_समयr);

	fsm_addसमयr(&ch->समयr, CTCM_TIME_5_SEC, CTC_EVENT_TIMER, ch);

	अगर (event == CTC_EVENT_STOP)	/* only क्रम STOP not yet locked */
		spin_lock_irqsave(get_ccwdev_lock(ch->cdev), saveflags);
			/* Such conditional locking is undeterministic in
			 * अटल view. => ignore sparse warnings here. */
	oldstate = fsm_माला_लोtate(fi);
	fsm_newstate(fi, CTC_STATE_TERM);
	rc = ccw_device_halt(ch->cdev, 0);

	अगर (event == CTC_EVENT_STOP)
		spin_unlock_irqrestore(get_ccwdev_lock(ch->cdev), saveflags);
			/* see remark above about conditional locking */

	अगर (rc != 0 && rc != -EBUSY) अणु
		fsm_delसमयr(&ch->समयr);
		अगर (event != CTC_EVENT_STOP) अणु
			fsm_newstate(fi, oldstate);
			ctcm_ccw_check_rc(ch, rc, (अक्षर *)__func__);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * Cleanup helper क्रम chx_fail and chx_stopped
 * cleanup channels queue and notअगरy पूर्णांकerface statemachine.
 *
 * fi		An instance of a channel statemachine.
 * state	The next state (depending on caller).
 * ch		The channel to operate on.
 */
अटल व्योम ctcm_chx_cleanup(fsm_instance *fi, पूर्णांक state,
		काष्ठा channel *ch)
अणु
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_NOTICE,
			"%s(%s): %s[%d]\n",
			CTCM_FUNTAIL, dev->name, ch->id, state);

	fsm_delसमयr(&ch->समयr);
	अगर (IS_MPC(ch))
		fsm_delसमयr(&ch->sweep_समयr);

	fsm_newstate(fi, state);
	अगर (state == CTC_STATE_STOPPED && ch->trans_skb != शून्य) अणु
		clear_normalized_cda(&ch->ccw[1]);
		dev_kमुक्त_skb_any(ch->trans_skb);
		ch->trans_skb = शून्य;
	पूर्ण

	ch->th_seg = 0x00;
	ch->th_seq_num = 0x00;
	अगर (CHANNEL_सूचीECTION(ch->flags) == CTCM_READ) अणु
		skb_queue_purge(&ch->io_queue);
		fsm_event(priv->fsm, DEV_EVENT_RXDOWN, dev);
	पूर्ण अन्यथा अणु
		ctcm_purge_skb_queue(&ch->io_queue);
		अगर (IS_MPC(ch))
			ctcm_purge_skb_queue(&ch->sweep_queue);
		spin_lock(&ch->collect_lock);
		ctcm_purge_skb_queue(&ch->collect_queue);
		ch->collect_len = 0;
		spin_unlock(&ch->collect_lock);
		fsm_event(priv->fsm, DEV_EVENT_TXDOWN, dev);
	पूर्ण
पूर्ण

/**
 * A channel has successfully been halted.
 * Cleanup it's queue and notअगरy पूर्णांकerface statemachine.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcm_chx_stopped(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	ctcm_chx_cleanup(fi, CTC_STATE_STOPPED, arg);
पूर्ण

/**
 * A stop command from device statemachine arrived and we are in
 * not operational mode. Set state to stopped.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcm_chx_stop(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	fsm_newstate(fi, CTC_STATE_STOPPED);
पूर्ण

/**
 * A machine check क्रम no path, not operational status or gone device has
 * happened.
 * Cleanup queue and notअगरy पूर्णांकerface statemachine.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcm_chx_fail(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	ctcm_chx_cleanup(fi, CTC_STATE_NOTOP, arg);
पूर्ण

/**
 * Handle error during setup of channel.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcm_chx_setuperr(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;

	/*
	 * Special हाल: Got UC_RCRESET on seपंचांगode.
	 * This means that remote side isn't setup. In this हाल
	 * simply retry after some 10 secs...
	 */
	अगर ((fsm_माला_लोtate(fi) == CTC_STATE_SETUPWAIT) &&
	    ((event == CTC_EVENT_UC_RCRESET) ||
	     (event == CTC_EVENT_UC_RSRESET))) अणु
		fsm_newstate(fi, CTC_STATE_STARTRETRY);
		fsm_delसमयr(&ch->समयr);
		fsm_addसमयr(&ch->समयr, CTCM_TIME_5_SEC, CTC_EVENT_TIMER, ch);
		अगर (!IS_MPC(ch) &&
		    (CHANNEL_सूचीECTION(ch->flags) == CTCM_READ)) अणु
			पूर्णांक rc = ccw_device_halt(ch->cdev, 0);
			अगर (rc != 0)
				ctcm_ccw_check_rc(ch, rc,
					"HaltIO in chx_setuperr");
		पूर्ण
		वापस;
	पूर्ण

	CTCM_DBF_TEXT_(ERROR, CTC_DBF_CRIT,
		"%s(%s) : %s error during %s channel setup state=%s\n",
		CTCM_FUNTAIL, dev->name, ctc_ch_event_names[event],
		(CHANNEL_सूचीECTION(ch->flags) == CTCM_READ) ? "RX" : "TX",
		fsm_माला_लोtate_str(fi));

	अगर (CHANNEL_सूचीECTION(ch->flags) == CTCM_READ) अणु
		fsm_newstate(fi, CTC_STATE_RXERR);
		fsm_event(priv->fsm, DEV_EVENT_RXDOWN, dev);
	पूर्ण अन्यथा अणु
		fsm_newstate(fi, CTC_STATE_TXERR);
		fsm_event(priv->fsm, DEV_EVENT_TXDOWN, dev);
	पूर्ण
पूर्ण

/**
 * Restart a channel after an error.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcm_chx_restart(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	काष्ठा net_device *dev = ch->netdev;
	अचिन्हित दीर्घ saveflags = 0;
	पूर्णांक oldstate;
	पूर्णांक rc;

	CTCM_DBF_TEXT_(TRACE, CTC_DBF_NOTICE,
		"%s: %s[%d] of %s\n",
			CTCM_FUNTAIL, ch->id, event, dev->name);

	fsm_delसमयr(&ch->समयr);

	fsm_addसमयr(&ch->समयr, CTCM_TIME_5_SEC, CTC_EVENT_TIMER, ch);
	oldstate = fsm_माला_लोtate(fi);
	fsm_newstate(fi, CTC_STATE_STARTWAIT);
	अगर (event == CTC_EVENT_TIMER)	/* only क्रम समयr not yet locked */
		spin_lock_irqsave(get_ccwdev_lock(ch->cdev), saveflags);
			/* Such conditional locking is a known problem क्रम
			 * sparse because its undeterministic in अटल view.
			 * Warnings should be ignored here. */
	rc = ccw_device_halt(ch->cdev, 0);
	अगर (event == CTC_EVENT_TIMER)
		spin_unlock_irqrestore(get_ccwdev_lock(ch->cdev), saveflags);
	अगर (rc != 0) अणु
		अगर (rc != -EBUSY) अणु
		    fsm_delसमयr(&ch->समयr);
		    fsm_newstate(fi, oldstate);
		पूर्ण
		ctcm_ccw_check_rc(ch, rc, "HaltIO in ctcm_chx_restart");
	पूर्ण
पूर्ण

/**
 * Handle error during RX initial handshake (exchange of
 * 0-length block header)
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcm_chx_rxiniterr(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;

	अगर (event == CTC_EVENT_TIMER) अणु
		अगर (!IS_MPCDEV(dev))
			/* TODO : check अगर MPC deletes समयr somewhere */
			fsm_delसमयr(&ch->समयr);
		अगर (ch->retry++ < 3)
			ctcm_chx_restart(fi, event, arg);
		अन्यथा अणु
			fsm_newstate(fi, CTC_STATE_RXERR);
			fsm_event(priv->fsm, DEV_EVENT_RXDOWN, dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
			"%s(%s): %s in %s", CTCM_FUNTAIL, ch->id,
			ctc_ch_event_names[event], fsm_माला_लोtate_str(fi));

		dev_warn(&dev->dev,
			"Initialization failed with RX/TX init handshake "
			"error %s\n", ctc_ch_event_names[event]);
	पूर्ण
पूर्ण

/**
 * Notअगरy device statemachine अगर we gave up initialization
 * of RX channel.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcm_chx_rxinitfail(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;

	CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
			"%s(%s): RX %s busy, init. fail",
				CTCM_FUNTAIL, dev->name, ch->id);
	fsm_newstate(fi, CTC_STATE_RXERR);
	fsm_event(priv->fsm, DEV_EVENT_RXDOWN, dev);
पूर्ण

/**
 * Handle RX Unit check remote reset (remote disconnected)
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcm_chx_rxdisc(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	काष्ठा channel *ch2;
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;

	CTCM_DBF_TEXT_(TRACE, CTC_DBF_NOTICE,
			"%s: %s: remote disconnect - re-init ...",
				CTCM_FUNTAIL, dev->name);
	fsm_delसमयr(&ch->समयr);
	/*
	 * Notअगरy device statemachine
	 */
	fsm_event(priv->fsm, DEV_EVENT_RXDOWN, dev);
	fsm_event(priv->fsm, DEV_EVENT_TXDOWN, dev);

	fsm_newstate(fi, CTC_STATE_DTERM);
	ch2 = priv->channel[CTCM_WRITE];
	fsm_newstate(ch2->fsm, CTC_STATE_DTERM);

	ccw_device_halt(ch->cdev, 0);
	ccw_device_halt(ch2->cdev, 0);
पूर्ण

/**
 * Handle error during TX channel initialization.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcm_chx_txiniterr(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;

	अगर (event == CTC_EVENT_TIMER) अणु
		fsm_delसमयr(&ch->समयr);
		अगर (ch->retry++ < 3)
			ctcm_chx_restart(fi, event, arg);
		अन्यथा अणु
			fsm_newstate(fi, CTC_STATE_TXERR);
			fsm_event(priv->fsm, DEV_EVENT_TXDOWN, dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
			"%s(%s): %s in %s", CTCM_FUNTAIL, ch->id,
			ctc_ch_event_names[event], fsm_माला_लोtate_str(fi));

		dev_warn(&dev->dev,
			"Initialization failed with RX/TX init handshake "
			"error %s\n", ctc_ch_event_names[event]);
	पूर्ण
पूर्ण

/**
 * Handle TX समयout by retrying operation.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcm_chx_txretry(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	काष्ठा sk_buff *skb;

	CTCM_PR_DEBUG("Enter: %s: cp=%i ch=0x%p id=%s\n",
			__func__, smp_processor_id(), ch, ch->id);

	fsm_delसमयr(&ch->समयr);
	अगर (ch->retry++ > 3) अणु
		काष्ठा mpc_group *gptr = priv->mpcg;
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_INFO,
				"%s: %s: retries exceeded",
					CTCM_FUNTAIL, ch->id);
		fsm_event(priv->fsm, DEV_EVENT_TXDOWN, dev);
		/* call restart अगर not MPC or अगर MPC and mpcg fsm is पढ़ोy.
			use gptr as mpc indicator */
		अगर (!(gptr && (fsm_माला_लोtate(gptr->fsm) != MPCG_STATE_READY)))
			ctcm_chx_restart(fi, event, arg);
				जाओ करोne;
	पूर्ण

	CTCM_DBF_TEXT_(TRACE, CTC_DBF_DEBUG,
			"%s : %s: retry %d",
				CTCM_FUNTAIL, ch->id, ch->retry);
	skb = skb_peek(&ch->io_queue);
	अगर (skb) अणु
		पूर्णांक rc = 0;
		अचिन्हित दीर्घ saveflags = 0;
		clear_normalized_cda(&ch->ccw[4]);
		ch->ccw[4].count = skb->len;
		अगर (set_normalized_cda(&ch->ccw[4], skb->data)) अणु
			CTCM_DBF_TEXT_(TRACE, CTC_DBF_INFO,
				"%s: %s: IDAL alloc failed",
						CTCM_FUNTAIL, ch->id);
			fsm_event(priv->fsm, DEV_EVENT_TXDOWN, dev);
			ctcm_chx_restart(fi, event, arg);
				जाओ करोne;
		पूर्ण
		fsm_addसमयr(&ch->समयr, 1000, CTC_EVENT_TIMER, ch);
		अगर (event == CTC_EVENT_TIMER) /* क्रम TIMER not yet locked */
			spin_lock_irqsave(get_ccwdev_lock(ch->cdev), saveflags);
			/* Such conditional locking is a known problem क्रम
			 * sparse because its undeterministic in अटल view.
			 * Warnings should be ignored here. */
		अगर (करो_debug_ccw)
			ctcmpc_dumpit((अक्षर *)&ch->ccw[3],
					माप(काष्ठा ccw1) * 3);

		rc = ccw_device_start(ch->cdev, &ch->ccw[3], 0, 0xff, 0);
		अगर (event == CTC_EVENT_TIMER)
			spin_unlock_irqrestore(get_ccwdev_lock(ch->cdev),
					saveflags);
		अगर (rc != 0) अणु
			fsm_delसमयr(&ch->समयr);
			ctcm_ccw_check_rc(ch, rc, "TX in chx_txretry");
			ctcm_purge_skb_queue(&ch->io_queue);
		पूर्ण
	पूर्ण
करोne:
	वापस;
पूर्ण

/**
 * Handle fatal errors during an I/O command.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcm_chx_iofatal(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	पूर्णांक rd = CHANNEL_सूचीECTION(ch->flags);

	fsm_delसमयr(&ch->समयr);
	CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
		"%s: %s: %s unrecoverable channel error",
			CTCM_FUNTAIL, ch->id, rd == CTCM_READ ? "RX" : "TX");

	अगर (IS_MPC(ch)) अणु
		priv->stats.tx_dropped++;
		priv->stats.tx_errors++;
	पूर्ण
	अगर (rd == CTCM_READ) अणु
		fsm_newstate(fi, CTC_STATE_RXERR);
		fsm_event(priv->fsm, DEV_EVENT_RXDOWN, dev);
	पूर्ण अन्यथा अणु
		fsm_newstate(fi, CTC_STATE_TXERR);
		fsm_event(priv->fsm, DEV_EVENT_TXDOWN, dev);
	पूर्ण
पूर्ण

/*
 * The ctcm statemachine क्रम a channel.
 */
स्थिर fsm_node ch_fsm[] = अणु
	अणु CTC_STATE_STOPPED,	CTC_EVENT_STOP,		ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_STOPPED,	CTC_EVENT_START,	ctcm_chx_start  पूर्ण,
	अणु CTC_STATE_STOPPED,	CTC_EVENT_FINSTAT,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_STOPPED,	CTC_EVENT_MC_FAIL,	ctcm_action_nop  पूर्ण,

	अणु CTC_STATE_NOTOP,	CTC_EVENT_STOP,		ctcm_chx_stop  पूर्ण,
	अणु CTC_STATE_NOTOP,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_NOTOP,	CTC_EVENT_FINSTAT,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_NOTOP,	CTC_EVENT_MC_FAIL,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_NOTOP,	CTC_EVENT_MC_GOOD,	ctcm_chx_start  पूर्ण,

	अणु CTC_STATE_STARTWAIT,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_STARTWAIT,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_STARTWAIT,	CTC_EVENT_FINSTAT,	ctcm_chx_seपंचांगode  पूर्ण,
	अणु CTC_STATE_STARTWAIT,	CTC_EVENT_TIMER,	ctcm_chx_setuperr  पूर्ण,
	अणु CTC_STATE_STARTWAIT,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_STARTWAIT,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,

	अणु CTC_STATE_STARTRETRY,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_STARTRETRY,	CTC_EVENT_TIMER,	ctcm_chx_seपंचांगode  पूर्ण,
	अणु CTC_STATE_STARTRETRY,	CTC_EVENT_FINSTAT,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_STARTRETRY,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,

	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_FINSTAT,	chx_firstio  पूर्ण,
	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_UC_RCRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_UC_RSRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_TIMER,	ctcm_chx_seपंचांगode  पूर्ण,
	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,

	अणु CTC_STATE_RXINIT,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_FINSTAT,	chx_rxidle  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_UC_RCRESET,	ctcm_chx_rxiniterr  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_UC_RSRESET,	ctcm_chx_rxiniterr  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_TIMER,	ctcm_chx_rxiniterr  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_ATTNBUSY,	ctcm_chx_rxinitfail  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_UC_ZERO,	chx_firstio  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,

	अणु CTC_STATE_RXIDLE,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_RXIDLE,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_RXIDLE,	CTC_EVENT_FINSTAT,	chx_rx  पूर्ण,
	अणु CTC_STATE_RXIDLE,	CTC_EVENT_UC_RCRESET,	ctcm_chx_rxdisc  पूर्ण,
	अणु CTC_STATE_RXIDLE,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_RXIDLE,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_RXIDLE,	CTC_EVENT_UC_ZERO,	chx_rx  पूर्ण,

	अणु CTC_STATE_TXINIT,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_FINSTAT,	ctcm_chx_txidle  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_UC_RCRESET,	ctcm_chx_txiniterr  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_UC_RSRESET,	ctcm_chx_txiniterr  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_TIMER,	ctcm_chx_txiniterr  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,

	अणु CTC_STATE_TXIDLE,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_TXIDLE,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_TXIDLE,	CTC_EVENT_FINSTAT,	chx_firstio  पूर्ण,
	अणु CTC_STATE_TXIDLE,	CTC_EVENT_UC_RCRESET,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_TXIDLE,	CTC_EVENT_UC_RSRESET,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_TXIDLE,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_TXIDLE,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,

	अणु CTC_STATE_TERM,	CTC_EVENT_STOP,		ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_TERM,	CTC_EVENT_START,	ctcm_chx_restart  पूर्ण,
	अणु CTC_STATE_TERM,	CTC_EVENT_FINSTAT,	ctcm_chx_stopped  पूर्ण,
	अणु CTC_STATE_TERM,	CTC_EVENT_UC_RCRESET,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_TERM,	CTC_EVENT_UC_RSRESET,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_TERM,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,

	अणु CTC_STATE_DTERM,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_DTERM,	CTC_EVENT_START,	ctcm_chx_restart  पूर्ण,
	अणु CTC_STATE_DTERM,	CTC_EVENT_FINSTAT,	ctcm_chx_seपंचांगode  पूर्ण,
	अणु CTC_STATE_DTERM,	CTC_EVENT_UC_RCRESET,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_DTERM,	CTC_EVENT_UC_RSRESET,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_DTERM,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,

	अणु CTC_STATE_TX,		CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_FINSTAT,	chx_txकरोne  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_UC_RCRESET,	ctcm_chx_txretry  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_UC_RSRESET,	ctcm_chx_txretry  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_TIMER,	ctcm_chx_txretry  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,

	अणु CTC_STATE_RXERR,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_TXERR,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_TXERR,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_RXERR,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
पूर्ण;

पूर्णांक ch_fsm_len = ARRAY_SIZE(ch_fsm);

/*
 * MPC actions क्रम mpc channel statemachine
 * handling of MPC protocol requires extra
 * statemachine and actions which are prefixed ctcmpc_ .
 * The ctc_ch_states and ctc_ch_state_names,
 * ctc_ch_events and ctc_ch_event_names share the ctcm definitions
 * which are expanded by some elements.
 */

/*
 * Actions क्रम mpc channel statemachine.
 */

/**
 * Normal data has been send. Free the corresponding
 * skb (it's in io_queue), reset dev->tbusy and
 * revert to idle state.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcmpc_chx_txकरोne(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel		*ch = arg;
	काष्ठा net_device	*dev = ch->netdev;
	काष्ठा ctcm_priv	*priv = dev->ml_priv;
	काष्ठा mpc_group	*grp = priv->mpcg;
	काष्ठा sk_buff		*skb;
	पूर्णांक		first = 1;
	पूर्णांक		i;
	__u32		data_space;
	अचिन्हित दीर्घ	duration;
	काष्ठा sk_buff	*peekskb;
	पूर्णांक		rc;
	काष्ठा th_header *header;
	काष्ठा pdu	*p_header;
	अचिन्हित दीर्घ करोne_stamp = jअगरfies;

	CTCM_PR_DEBUG("Enter %s: %s cp:%i\n",
			__func__, dev->name, smp_processor_id());

	duration = करोne_stamp - ch->prof.send_stamp;
	अगर (duration > ch->prof.tx_समय)
		ch->prof.tx_समय = duration;

	अगर (ch->irb->scsw.cmd.count != 0)
		CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_DEBUG,
			"%s(%s): TX not complete, remaining %d bytes",
			     CTCM_FUNTAIL, dev->name, ch->irb->scsw.cmd.count);
	fsm_delसमयr(&ch->समयr);
	जबतक ((skb = skb_dequeue(&ch->io_queue))) अणु
		priv->stats.tx_packets++;
		priv->stats.tx_bytes += skb->len - TH_HEADER_LENGTH;
		अगर (first) अणु
			priv->stats.tx_bytes += 2;
			first = 0;
		पूर्ण
		refcount_dec(&skb->users);
		dev_kमुक्त_skb_irq(skb);
	पूर्ण
	spin_lock(&ch->collect_lock);
	clear_normalized_cda(&ch->ccw[4]);
	अगर ((ch->collect_len <= 0) || (grp->in_sweep != 0)) अणु
		spin_unlock(&ch->collect_lock);
		fsm_newstate(fi, CTC_STATE_TXIDLE);
				जाओ करोne;
	पूर्ण

	अगर (ctcm_checkalloc_buffer(ch)) अणु
		spin_unlock(&ch->collect_lock);
				जाओ करोne;
	पूर्ण
	ch->trans_skb->data = ch->trans_skb_data;
	skb_reset_tail_poपूर्णांकer(ch->trans_skb);
	ch->trans_skb->len = 0;
	अगर (ch->prof.maxmulti < (ch->collect_len + TH_HEADER_LENGTH))
		ch->prof.maxmulti = ch->collect_len + TH_HEADER_LENGTH;
	अगर (ch->prof.maxcqueue < skb_queue_len(&ch->collect_queue))
		ch->prof.maxcqueue = skb_queue_len(&ch->collect_queue);
	i = 0;
	p_header = शून्य;
	data_space = grp->group_max_buflen - TH_HEADER_LENGTH;

	CTCM_PR_DBGDATA("%s: building trans_skb from collect_q"
		       " data_space:%04x\n",
		       __func__, data_space);

	जबतक ((skb = skb_dequeue(&ch->collect_queue))) अणु
		skb_put_data(ch->trans_skb, skb->data, skb->len);
		p_header = (काष्ठा pdu *)
			(skb_tail_poपूर्णांकer(ch->trans_skb) - skb->len);
		p_header->pdu_flag = 0x00;
		अगर (be16_to_cpu(skb->protocol) == ETH_P_SNAP)
			p_header->pdu_flag |= 0x60;
		अन्यथा
			p_header->pdu_flag |= 0x20;

		CTCM_PR_DBGDATA("%s: trans_skb len:%04x \n",
				__func__, ch->trans_skb->len);
		CTCM_PR_DBGDATA("%s: pdu header and data for up"
				" to 32 bytes sent to vtam\n", __func__);
		CTCM_D3_DUMP((अक्षर *)p_header, min_t(पूर्णांक, skb->len, 32));

		ch->collect_len -= skb->len;
		data_space -= skb->len;
		priv->stats.tx_packets++;
		priv->stats.tx_bytes += skb->len;
		refcount_dec(&skb->users);
		dev_kमुक्त_skb_any(skb);
		peekskb = skb_peek(&ch->collect_queue);
		अगर (peekskb->len > data_space)
			अवरोध;
		i++;
	पूर्ण
	/* p_header poपूर्णांकs to the last one we handled */
	अगर (p_header)
		p_header->pdu_flag |= PDU_LAST;	/*Say it's the last one*/

	header = skb_push(ch->trans_skb, TH_HEADER_LENGTH);
	स_रखो(header, 0, TH_HEADER_LENGTH);

	header->th_ch_flag = TH_HAS_PDU;  /* Normal data */
	ch->th_seq_num++;
	header->th_seq_num = ch->th_seq_num;

	CTCM_PR_DBGDATA("%s: ToVTAM_th_seq= %08x\n" ,
					__func__, ch->th_seq_num);

	CTCM_PR_DBGDATA("%s: trans_skb len:%04x \n",
		       __func__, ch->trans_skb->len);
	CTCM_PR_DBGDATA("%s: up-to-50 bytes of trans_skb "
			"data to vtam from collect_q\n", __func__);
	CTCM_D3_DUMP((अक्षर *)ch->trans_skb->data,
				min_t(पूर्णांक, ch->trans_skb->len, 50));

	spin_unlock(&ch->collect_lock);
	clear_normalized_cda(&ch->ccw[1]);

	CTCM_PR_DBGDATA("ccwcda=0x%p data=0x%p\n",
			(व्योम *)(अचिन्हित दीर्घ)ch->ccw[1].cda,
			ch->trans_skb->data);
	ch->ccw[1].count = ch->max_bufsize;

	अगर (set_normalized_cda(&ch->ccw[1], ch->trans_skb->data)) अणु
		dev_kमुक्त_skb_any(ch->trans_skb);
		ch->trans_skb = शून्य;
		CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_ERROR,
			"%s: %s: IDAL alloc failed",
				CTCM_FUNTAIL, ch->id);
		fsm_event(priv->mpcg->fsm, MPCG_EVENT_INOP, dev);
		वापस;
	पूर्ण

	CTCM_PR_DBGDATA("ccwcda=0x%p data=0x%p\n",
			(व्योम *)(अचिन्हित दीर्घ)ch->ccw[1].cda,
			ch->trans_skb->data);

	ch->ccw[1].count = ch->trans_skb->len;
	fsm_addसमयr(&ch->समयr, CTCM_TIME_5_SEC, CTC_EVENT_TIMER, ch);
	ch->prof.send_stamp = jअगरfies;
	अगर (करो_debug_ccw)
		ctcmpc_dumpit((अक्षर *)&ch->ccw[0], माप(काष्ठा ccw1) * 3);
	rc = ccw_device_start(ch->cdev, &ch->ccw[0], 0, 0xff, 0);
	ch->prof.करोios_multi++;
	अगर (rc != 0) अणु
		priv->stats.tx_dropped += i;
		priv->stats.tx_errors += i;
		fsm_delसमयr(&ch->समयr);
		ctcm_ccw_check_rc(ch, rc, "chained TX");
	पूर्ण
करोne:
	ctcm_clear_busy(dev);
	वापस;
पूर्ण

/**
 * Got normal data, check क्रम sanity, queue it up, allocate new buffer
 * trigger bottom half, and initiate next पढ़ो.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcmpc_chx_rx(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel		*ch = arg;
	काष्ठा net_device	*dev = ch->netdev;
	काष्ठा ctcm_priv	*priv = dev->ml_priv;
	काष्ठा mpc_group	*grp = priv->mpcg;
	काष्ठा sk_buff		*skb = ch->trans_skb;
	काष्ठा sk_buff		*new_skb;
	अचिन्हित दीर्घ		saveflags = 0;	/* aव्योमs compiler warning */
	पूर्णांक len	= ch->max_bufsize - ch->irb->scsw.cmd.count;

	CTCM_PR_DEBUG("%s: %s: cp:%i %s maxbuf : %04x, len: %04x\n",
			CTCM_FUNTAIL, dev->name, smp_processor_id(),
				ch->id, ch->max_bufsize, len);
	fsm_delसमयr(&ch->समयr);

	अगर (skb == शून्य) अणु
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): TRANS_SKB = NULL",
				CTCM_FUNTAIL, dev->name);
			जाओ again;
	पूर्ण

	अगर (len < TH_HEADER_LENGTH) अणु
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%s): packet length %d to short",
					CTCM_FUNTAIL, dev->name, len);
		priv->stats.rx_dropped++;
		priv->stats.rx_length_errors++;
	पूर्ण अन्यथा अणु
		/* must have valid th header or game over */
		__u32	block_len = len;
		len = TH_HEADER_LENGTH + XID2_LENGTH + 4;
		new_skb = __dev_alloc_skb(ch->max_bufsize, GFP_ATOMIC);

		अगर (new_skb == शून्य) अणु
			CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%d): skb allocation failed",
						CTCM_FUNTAIL, dev->name);
			fsm_event(priv->mpcg->fsm, MPCG_EVENT_INOP, dev);
					जाओ again;
		पूर्ण
		चयन (fsm_माला_लोtate(grp->fsm)) अणु
		हाल MPCG_STATE_RESET:
		हाल MPCG_STATE_INOP:
			dev_kमुक्त_skb_any(new_skb);
			अवरोध;
		हाल MPCG_STATE_FLOWC:
		हाल MPCG_STATE_READY:
			skb_put_data(new_skb, skb->data, block_len);
			skb_queue_tail(&ch->io_queue, new_skb);
			tasklet_schedule(&ch->ch_tasklet);
			अवरोध;
		शेष:
			skb_put_data(new_skb, skb->data, len);
			skb_queue_tail(&ch->io_queue, new_skb);
			tasklet_hi_schedule(&ch->ch_tasklet);
			अवरोध;
		पूर्ण
	पूर्ण

again:
	चयन (fsm_माला_लोtate(grp->fsm)) अणु
	पूर्णांक rc, करोlock;
	हाल MPCG_STATE_FLOWC:
	हाल MPCG_STATE_READY:
		अगर (ctcm_checkalloc_buffer(ch))
			अवरोध;
		ch->trans_skb->data = ch->trans_skb_data;
		skb_reset_tail_poपूर्णांकer(ch->trans_skb);
		ch->trans_skb->len = 0;
		ch->ccw[1].count = ch->max_bufsize;
			अगर (करो_debug_ccw)
			ctcmpc_dumpit((अक्षर *)&ch->ccw[0],
					माप(काष्ठा ccw1) * 3);
		करोlock = !in_irq();
		अगर (करोlock)
			spin_lock_irqsave(
				get_ccwdev_lock(ch->cdev), saveflags);
		rc = ccw_device_start(ch->cdev, &ch->ccw[0], 0, 0xff, 0);
		अगर (करोlock) /* see remark about conditional locking */
			spin_unlock_irqrestore(
				get_ccwdev_lock(ch->cdev), saveflags);
		अगर (rc != 0)
			ctcm_ccw_check_rc(ch, rc, "normal RX");
	शेष:
		अवरोध;
	पूर्ण

	CTCM_PR_DEBUG("Exit %s: %s, ch=0x%p, id=%s\n",
			__func__, dev->name, ch, ch->id);

पूर्ण

/**
 * Initialize connection by sending a __u16 of value 0.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
अटल व्योम ctcmpc_chx_firstio(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel		*ch = arg;
	काष्ठा net_device	*dev = ch->netdev;
	काष्ठा ctcm_priv	*priv = dev->ml_priv;
	काष्ठा mpc_group	*gptr = priv->mpcg;

	CTCM_PR_DEBUG("Enter %s: id=%s, ch=0x%p\n",
				__func__, ch->id, ch);

	CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_INFO,
			"%s: %s: chstate:%i, grpstate:%i, prot:%i\n",
			CTCM_FUNTAIL, ch->id, fsm_माला_लोtate(fi),
			fsm_माला_लोtate(gptr->fsm), ch->protocol);

	अगर (fsm_माला_लोtate(fi) == CTC_STATE_TXIDLE)
		MPC_DBF_DEV_NAME(TRACE, dev, "remote side issued READ? ");

	fsm_delसमयr(&ch->समयr);
	अगर (ctcm_checkalloc_buffer(ch))
				जाओ करोne;

	चयन (fsm_माला_लोtate(fi)) अणु
	हाल CTC_STATE_STARTRETRY:
	हाल CTC_STATE_SETUPWAIT:
		अगर (CHANNEL_सूचीECTION(ch->flags) == CTCM_READ) अणु
			ctcmpc_chx_rxidle(fi, event, arg);
		पूर्ण अन्यथा अणु
			fsm_newstate(fi, CTC_STATE_TXIDLE);
			fsm_event(priv->fsm, DEV_EVENT_TXUP, dev);
		पूर्ण
				जाओ करोne;
	शेष:
		अवरोध;
	पूर्ण

	fsm_newstate(fi, (CHANNEL_सूचीECTION(ch->flags) == CTCM_READ)
		     ? CTC_STATE_RXINIT : CTC_STATE_TXINIT);

करोne:
	CTCM_PR_DEBUG("Exit %s: id=%s, ch=0x%p\n",
				__func__, ch->id, ch);
	वापस;
पूर्ण

/**
 * Got initial data, check it. If OK,
 * notअगरy device statemachine that we are up and
 * running.
 *
 * fi		An instance of a channel statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from channel * upon call.
 */
व्योम ctcmpc_chx_rxidle(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ch = arg;
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv  *priv = dev->ml_priv;
	काष्ठा mpc_group  *grp = priv->mpcg;
	पूर्णांक rc;
	अचिन्हित दीर्घ saveflags = 0;	/* aव्योमs compiler warning */

	fsm_delसमयr(&ch->समयr);
	CTCM_PR_DEBUG("%s: %s: %s: cp:%i, chstate:%i grpstate:%i\n",
			__func__, ch->id, dev->name, smp_processor_id(),
				fsm_माला_लोtate(fi), fsm_माला_लोtate(grp->fsm));

	fsm_newstate(fi, CTC_STATE_RXIDLE);
	/* XID processing complete */

	चयन (fsm_माला_लोtate(grp->fsm)) अणु
	हाल MPCG_STATE_FLOWC:
	हाल MPCG_STATE_READY:
		अगर (ctcm_checkalloc_buffer(ch))
				जाओ करोne;
		ch->trans_skb->data = ch->trans_skb_data;
		skb_reset_tail_poपूर्णांकer(ch->trans_skb);
		ch->trans_skb->len = 0;
		ch->ccw[1].count = ch->max_bufsize;
		CTCM_CCW_DUMP((अक्षर *)&ch->ccw[0], माप(काष्ठा ccw1) * 3);
		अगर (event == CTC_EVENT_START)
			/* see remark about conditional locking */
			spin_lock_irqsave(get_ccwdev_lock(ch->cdev), saveflags);
		rc = ccw_device_start(ch->cdev, &ch->ccw[0], 0, 0xff, 0);
		अगर (event == CTC_EVENT_START)
			spin_unlock_irqrestore(
					get_ccwdev_lock(ch->cdev), saveflags);
		अगर (rc != 0) अणु
			fsm_newstate(fi, CTC_STATE_RXINIT);
			ctcm_ccw_check_rc(ch, rc, "initial RX");
				जाओ करोne;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	fsm_event(priv->fsm, DEV_EVENT_RXUP, dev);
करोne:
	वापस;
पूर्ण

/*
 * ctcmpc channel FSM action
 * called from several poपूर्णांकs in ctcmpc_ch_fsm
 * ctcmpc only
 */
अटल व्योम ctcmpc_chx_attn(fsm_instance *fsm, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel	  *ch     = arg;
	काष्ठा net_device *dev    = ch->netdev;
	काष्ठा ctcm_priv  *priv   = dev->ml_priv;
	काष्ठा mpc_group  *grp = priv->mpcg;

	CTCM_PR_DEBUG("%s(%s): %s(ch=0x%p), cp=%i, ChStat:%s, GrpStat:%s\n",
		__func__, dev->name, ch->id, ch, smp_processor_id(),
			fsm_माला_लोtate_str(ch->fsm), fsm_माला_लोtate_str(grp->fsm));

	चयन (fsm_माला_लोtate(grp->fsm)) अणु
	हाल MPCG_STATE_XID2INITW:
		/* ok..start yside xid exchanges */
		अगर (!ch->in_mpcgroup)
			अवरोध;
		अगर (fsm_माला_लोtate(ch->fsm) ==  CH_XID0_PENDING) अणु
			fsm_delसमयr(&grp->समयr);
			fsm_addसमयr(&grp->समयr,
				MPC_XID_TIMEOUT_VALUE,
				MPCG_EVENT_TIMER, dev);
			fsm_event(grp->fsm, MPCG_EVENT_XID0DO, ch);

		पूर्ण अन्यथा अगर (fsm_माला_लोtate(ch->fsm) < CH_XID7_PENDING1)
			/* attn rcvd beक्रमe xid0 processed via bh */
			fsm_newstate(ch->fsm, CH_XID7_PENDING1);
		अवरोध;
	हाल MPCG_STATE_XID2INITX:
	हाल MPCG_STATE_XID0IOWAIT:
	हाल MPCG_STATE_XID0IOWAIX:
		/* attn rcvd beक्रमe xid0 processed on ch
		but mid-xid0 processing क्रम group    */
		अगर (fsm_माला_लोtate(ch->fsm) < CH_XID7_PENDING1)
			fsm_newstate(ch->fsm, CH_XID7_PENDING1);
		अवरोध;
	हाल MPCG_STATE_XID7INITW:
	हाल MPCG_STATE_XID7INITX:
	हाल MPCG_STATE_XID7INITI:
	हाल MPCG_STATE_XID7INITZ:
		चयन (fsm_माला_लोtate(ch->fsm)) अणु
		हाल CH_XID7_PENDING:
			fsm_newstate(ch->fsm, CH_XID7_PENDING1);
			अवरोध;
		हाल CH_XID7_PENDING2:
			fsm_newstate(ch->fsm, CH_XID7_PENDING3);
			अवरोध;
		पूर्ण
		fsm_event(grp->fsm, MPCG_EVENT_XID7DONE, dev);
		अवरोध;
	पूर्ण

	वापस;
पूर्ण

/*
 * ctcmpc channel FSM action
 * called from one poपूर्णांक in ctcmpc_ch_fsm
 * ctcmpc only
 */
अटल व्योम ctcmpc_chx_attnbusy(fsm_instance *fsm, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel	  *ch     = arg;
	काष्ठा net_device *dev    = ch->netdev;
	काष्ठा ctcm_priv  *priv   = dev->ml_priv;
	काष्ठा mpc_group  *grp    = priv->mpcg;

	CTCM_PR_DEBUG("%s(%s): %s\n  ChState:%s GrpState:%s\n",
			__func__, dev->name, ch->id,
			fsm_माला_लोtate_str(ch->fsm), fsm_माला_लोtate_str(grp->fsm));

	fsm_delसमयr(&ch->समयr);

	चयन (fsm_माला_लोtate(grp->fsm)) अणु
	हाल MPCG_STATE_XID0IOWAIT:
		/* vtam wants to be primary.start yside xid exchanges*/
		/* only receive one attn-busy at a समय so must not  */
		/* change state each समय			     */
		grp->changed_side = 1;
		fsm_newstate(grp->fsm, MPCG_STATE_XID2INITW);
		अवरोध;
	हाल MPCG_STATE_XID2INITW:
		अगर (grp->changed_side == 1) अणु
			grp->changed_side = 2;
			अवरोध;
		पूर्ण
		/* process began via call to establish_conn	 */
		/* so must report failure instead of reverting	 */
		/* back to पढ़ोy-क्रम-xid passive state		 */
		अगर (grp->estconnfunc)
				जाओ करोne;
		/* this attnbusy is NOT the result of xside xid  */
		/* collisions so yside must have been triggered  */
		/* by an ATTN that was not पूर्णांकended to start XID */
		/* processing. Revert back to पढ़ोy-क्रम-xid and  */
		/* रुको क्रम ATTN पूर्णांकerrupt to संकेत xid start	 */
		अगर (fsm_माला_लोtate(ch->fsm) == CH_XID0_INPROGRESS) अणु
			fsm_newstate(ch->fsm, CH_XID0_PENDING) ;
			fsm_delसमयr(&grp->समयr);
				जाओ करोne;
		पूर्ण
		fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
				जाओ करोne;
	हाल MPCG_STATE_XID2INITX:
		/* XID2 was received beक्रमe ATTN Busy क्रम second
		   channel.Send yside xid क्रम second channel.
		*/
		अगर (grp->changed_side == 1) अणु
			grp->changed_side = 2;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल MPCG_STATE_XID0IOWAIX:
	हाल MPCG_STATE_XID7INITW:
	हाल MPCG_STATE_XID7INITX:
	हाल MPCG_STATE_XID7INITI:
	हाल MPCG_STATE_XID7INITZ:
	शेष:
		/* multiple attn-busy indicates too out-of-sync      */
		/* and they are certainly not being received as part */
		/* of valid mpc group negotiations..		     */
		fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
				जाओ करोne;
	पूर्ण

	अगर (grp->changed_side == 1) अणु
		fsm_delसमयr(&grp->समयr);
		fsm_addसमयr(&grp->समयr, MPC_XID_TIMEOUT_VALUE,
			     MPCG_EVENT_TIMER, dev);
	पूर्ण
	अगर (ch->in_mpcgroup)
		fsm_event(grp->fsm, MPCG_EVENT_XID0DO, ch);
	अन्यथा
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): channel %s not added to group",
				CTCM_FUNTAIL, dev->name, ch->id);

करोne:
	वापस;
पूर्ण

/*
 * ctcmpc channel FSM action
 * called from several poपूर्णांकs in ctcmpc_ch_fsm
 * ctcmpc only
 */
अटल व्योम ctcmpc_chx_resend(fsm_instance *fsm, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel	   *ch	   = arg;
	काष्ठा net_device  *dev    = ch->netdev;
	काष्ठा ctcm_priv   *priv   = dev->ml_priv;
	काष्ठा mpc_group   *grp    = priv->mpcg;

	fsm_event(grp->fsm, MPCG_EVENT_XID0DO, ch);
	वापस;
पूर्ण

/*
 * ctcmpc channel FSM action
 * called from several poपूर्णांकs in ctcmpc_ch_fsm
 * ctcmpc only
 */
अटल व्योम ctcmpc_chx_send_sweep(fsm_instance *fsm, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel *ach = arg;
	काष्ठा net_device *dev = ach->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	काष्ठा mpc_group *grp = priv->mpcg;
	काष्ठा channel *wch = priv->channel[CTCM_WRITE];
	काष्ठा channel *rch = priv->channel[CTCM_READ];
	काष्ठा sk_buff *skb;
	काष्ठा th_sweep *header;
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ saveflags = 0;

	CTCM_PR_DEBUG("ctcmpc enter: %s(): cp=%i ch=0x%p id=%s\n",
			__func__, smp_processor_id(), ach, ach->id);

	अगर (grp->in_sweep == 0)
				जाओ करोne;

	CTCM_PR_DBGDATA("%s: 1: ToVTAM_th_seq= %08x\n" ,
				__func__, wch->th_seq_num);
	CTCM_PR_DBGDATA("%s: 1: FromVTAM_th_seq= %08x\n" ,
				__func__, rch->th_seq_num);

	अगर (fsm_माला_लोtate(wch->fsm) != CTC_STATE_TXIDLE) अणु
		/* give the previous IO समय to complete */
		fsm_addसमयr(&wch->sweep_समयr,
			200, CTC_EVENT_RSWEEP_TIMER, wch);
				जाओ करोne;
	पूर्ण

	skb = skb_dequeue(&wch->sweep_queue);
	अगर (!skb)
				जाओ करोne;

	अगर (set_normalized_cda(&wch->ccw[4], skb->data)) अणु
		grp->in_sweep = 0;
		ctcm_clear_busy_करो(dev);
		dev_kमुक्त_skb_any(skb);
		fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
				जाओ करोne;
	पूर्ण अन्यथा अणु
		refcount_inc(&skb->users);
		skb_queue_tail(&wch->io_queue, skb);
	पूर्ण

	/* send out the sweep */
	wch->ccw[4].count = skb->len;

	header = (काष्ठा th_sweep *)skb->data;
	चयन (header->th.th_ch_flag) अणु
	हाल TH_SWEEP_REQ:
		grp->sweep_req_pend_num--;
		अवरोध;
	हाल TH_SWEEP_RESP:
		grp->sweep_rsp_pend_num--;
		अवरोध;
	पूर्ण

	header->sw.th_last_seq = wch->th_seq_num;

	CTCM_CCW_DUMP((अक्षर *)&wch->ccw[3], माप(काष्ठा ccw1) * 3);
	CTCM_PR_DBGDATA("%s: sweep packet\n", __func__);
	CTCM_D3_DUMP((अक्षर *)header, TH_SWEEP_LENGTH);

	fsm_addसमयr(&wch->समयr, CTCM_TIME_5_SEC, CTC_EVENT_TIMER, wch);
	fsm_newstate(wch->fsm, CTC_STATE_TX);

	spin_lock_irqsave(get_ccwdev_lock(wch->cdev), saveflags);
	wch->prof.send_stamp = jअगरfies;
	rc = ccw_device_start(wch->cdev, &wch->ccw[3], 0, 0xff, 0);
	spin_unlock_irqrestore(get_ccwdev_lock(wch->cdev), saveflags);

	अगर ((grp->sweep_req_pend_num == 0) &&
	   (grp->sweep_rsp_pend_num == 0)) अणु
		grp->in_sweep = 0;
		rch->th_seq_num = 0x00;
		wch->th_seq_num = 0x00;
		ctcm_clear_busy_करो(dev);
	पूर्ण

	CTCM_PR_DBGDATA("%s: To-/From-VTAM_th_seq = %08x/%08x\n" ,
			__func__, wch->th_seq_num, rch->th_seq_num);

	अगर (rc != 0)
		ctcm_ccw_check_rc(wch, rc, "send sweep");

करोne:
	वापस;
पूर्ण


/*
 * The ctcmpc statemachine क्रम a channel.
 */

स्थिर fsm_node ctcmpc_ch_fsm[] = अणु
	अणु CTC_STATE_STOPPED,	CTC_EVENT_STOP,		ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_STOPPED,	CTC_EVENT_START,	ctcm_chx_start  पूर्ण,
	अणु CTC_STATE_STOPPED,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_STOPPED,	CTC_EVENT_FINSTAT,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_STOPPED,	CTC_EVENT_MC_FAIL,	ctcm_action_nop  पूर्ण,

	अणु CTC_STATE_NOTOP,	CTC_EVENT_STOP,		ctcm_chx_stop  पूर्ण,
	अणु CTC_STATE_NOTOP,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_NOTOP,	CTC_EVENT_FINSTAT,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_NOTOP,	CTC_EVENT_MC_FAIL,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_NOTOP,	CTC_EVENT_MC_GOOD,	ctcm_chx_start  पूर्ण,
	अणु CTC_STATE_NOTOP,	CTC_EVENT_UC_RCRESET,	ctcm_chx_stop  पूर्ण,
	अणु CTC_STATE_NOTOP,	CTC_EVENT_UC_RSRESET,	ctcm_chx_stop  पूर्ण,
	अणु CTC_STATE_NOTOP,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,

	अणु CTC_STATE_STARTWAIT,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_STARTWAIT,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_STARTWAIT,	CTC_EVENT_FINSTAT,	ctcm_chx_seपंचांगode  पूर्ण,
	अणु CTC_STATE_STARTWAIT,	CTC_EVENT_TIMER,	ctcm_chx_setuperr  पूर्ण,
	अणु CTC_STATE_STARTWAIT,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_STARTWAIT,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,

	अणु CTC_STATE_STARTRETRY,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_STARTRETRY,	CTC_EVENT_TIMER,	ctcm_chx_seपंचांगode  पूर्ण,
	अणु CTC_STATE_STARTRETRY,	CTC_EVENT_FINSTAT,	ctcm_chx_seपंचांगode  पूर्ण,
	अणु CTC_STATE_STARTRETRY,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_STARTRETRY,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,

	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_FINSTAT,	ctcmpc_chx_firstio  पूर्ण,
	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_UC_RCRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_UC_RSRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_TIMER,	ctcm_chx_seपंचांगode  पूर्ण,
	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_SETUPWAIT,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,

	अणु CTC_STATE_RXINIT,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_FINSTAT,	ctcmpc_chx_rxidle  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_UC_RCRESET,	ctcm_chx_rxiniterr  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_UC_RSRESET,	ctcm_chx_rxiniterr  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_TIMER,	ctcm_chx_rxiniterr  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_ATTNBUSY,	ctcm_chx_rxinitfail  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_UC_ZERO,	ctcmpc_chx_firstio  पूर्ण,
	अणु CTC_STATE_RXINIT,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,

	अणु CH_XID0_PENDING,	CTC_EVENT_FINSTAT,	ctcm_action_nop  पूर्ण,
	अणु CH_XID0_PENDING,	CTC_EVENT_ATTN,		ctcmpc_chx_attn  पूर्ण,
	अणु CH_XID0_PENDING,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CH_XID0_PENDING,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CH_XID0_PENDING,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CH_XID0_PENDING,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CH_XID0_PENDING,	CTC_EVENT_UC_RCRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CH_XID0_PENDING,	CTC_EVENT_UC_RSRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CH_XID0_PENDING,	CTC_EVENT_UC_RSRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CH_XID0_PENDING,	CTC_EVENT_ATTNBUSY,	ctcm_chx_iofatal  पूर्ण,

	अणु CH_XID0_INPROGRESS,	CTC_EVENT_FINSTAT,	ctcmpc_chx_rx  पूर्ण,
	अणु CH_XID0_INPROGRESS,	CTC_EVENT_ATTN,		ctcmpc_chx_attn  पूर्ण,
	अणु CH_XID0_INPROGRESS,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CH_XID0_INPROGRESS,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CH_XID0_INPROGRESS,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CH_XID0_INPROGRESS,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CH_XID0_INPROGRESS,	CTC_EVENT_UC_ZERO,	ctcmpc_chx_rx  पूर्ण,
	अणु CH_XID0_INPROGRESS,	CTC_EVENT_UC_RCRESET,	ctcm_chx_setuperr पूर्ण,
	अणु CH_XID0_INPROGRESS,	CTC_EVENT_ATTNBUSY,	ctcmpc_chx_attnbusy  पूर्ण,
	अणु CH_XID0_INPROGRESS,	CTC_EVENT_TIMER,	ctcmpc_chx_resend  पूर्ण,
	अणु CH_XID0_INPROGRESS,	CTC_EVENT_IO_EBUSY,	ctcm_chx_fail  पूर्ण,

	अणु CH_XID7_PENDING,	CTC_EVENT_FINSTAT,	ctcmpc_chx_rx  पूर्ण,
	अणु CH_XID7_PENDING,	CTC_EVENT_ATTN,		ctcmpc_chx_attn  पूर्ण,
	अणु CH_XID7_PENDING,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CH_XID7_PENDING,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CH_XID7_PENDING,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CH_XID7_PENDING,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CH_XID7_PENDING,	CTC_EVENT_UC_ZERO,	ctcmpc_chx_rx  पूर्ण,
	अणु CH_XID7_PENDING,	CTC_EVENT_UC_RCRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CH_XID7_PENDING,	CTC_EVENT_UC_RSRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CH_XID7_PENDING,	CTC_EVENT_UC_RSRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CH_XID7_PENDING,	CTC_EVENT_ATTNBUSY,	ctcm_chx_iofatal  पूर्ण,
	अणु CH_XID7_PENDING,	CTC_EVENT_TIMER,	ctcmpc_chx_resend  पूर्ण,
	अणु CH_XID7_PENDING,	CTC_EVENT_IO_EBUSY,	ctcm_chx_fail  पूर्ण,

	अणु CH_XID7_PENDING1,	CTC_EVENT_FINSTAT,	ctcmpc_chx_rx  पूर्ण,
	अणु CH_XID7_PENDING1,	CTC_EVENT_ATTN,		ctcmpc_chx_attn  पूर्ण,
	अणु CH_XID7_PENDING1,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CH_XID7_PENDING1,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CH_XID7_PENDING1,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CH_XID7_PENDING1,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CH_XID7_PENDING1,	CTC_EVENT_UC_ZERO,	ctcmpc_chx_rx  पूर्ण,
	अणु CH_XID7_PENDING1,	CTC_EVENT_UC_RCRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CH_XID7_PENDING1,	CTC_EVENT_UC_RSRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CH_XID7_PENDING1,	CTC_EVENT_ATTNBUSY,	ctcm_chx_iofatal  पूर्ण,
	अणु CH_XID7_PENDING1,	CTC_EVENT_TIMER,	ctcmpc_chx_resend  पूर्ण,
	अणु CH_XID7_PENDING1,	CTC_EVENT_IO_EBUSY,	ctcm_chx_fail  पूर्ण,

	अणु CH_XID7_PENDING2,	CTC_EVENT_FINSTAT,	ctcmpc_chx_rx  पूर्ण,
	अणु CH_XID7_PENDING2,	CTC_EVENT_ATTN,		ctcmpc_chx_attn  पूर्ण,
	अणु CH_XID7_PENDING2,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CH_XID7_PENDING2,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CH_XID7_PENDING2,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CH_XID7_PENDING2,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CH_XID7_PENDING2,	CTC_EVENT_UC_ZERO,	ctcmpc_chx_rx  पूर्ण,
	अणु CH_XID7_PENDING2,	CTC_EVENT_UC_RCRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CH_XID7_PENDING2,	CTC_EVENT_UC_RSRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CH_XID7_PENDING2,	CTC_EVENT_ATTNBUSY,	ctcm_chx_iofatal  पूर्ण,
	अणु CH_XID7_PENDING2,	CTC_EVENT_TIMER,	ctcmpc_chx_resend  पूर्ण,
	अणु CH_XID7_PENDING2,	CTC_EVENT_IO_EBUSY,	ctcm_chx_fail  पूर्ण,

	अणु CH_XID7_PENDING3,	CTC_EVENT_FINSTAT,	ctcmpc_chx_rx  पूर्ण,
	अणु CH_XID7_PENDING3,	CTC_EVENT_ATTN,		ctcmpc_chx_attn  पूर्ण,
	अणु CH_XID7_PENDING3,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CH_XID7_PENDING3,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CH_XID7_PENDING3,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CH_XID7_PENDING3,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CH_XID7_PENDING3,	CTC_EVENT_UC_ZERO,	ctcmpc_chx_rx  पूर्ण,
	अणु CH_XID7_PENDING3,	CTC_EVENT_UC_RCRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CH_XID7_PENDING3,	CTC_EVENT_UC_RSRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CH_XID7_PENDING3,	CTC_EVENT_ATTNBUSY,	ctcm_chx_iofatal  पूर्ण,
	अणु CH_XID7_PENDING3,	CTC_EVENT_TIMER,	ctcmpc_chx_resend  पूर्ण,
	अणु CH_XID7_PENDING3,	CTC_EVENT_IO_EBUSY,	ctcm_chx_fail  पूर्ण,

	अणु CH_XID7_PENDING4,	CTC_EVENT_FINSTAT,	ctcmpc_chx_rx  पूर्ण,
	अणु CH_XID7_PENDING4,	CTC_EVENT_ATTN,		ctcmpc_chx_attn  पूर्ण,
	अणु CH_XID7_PENDING4,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CH_XID7_PENDING4,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CH_XID7_PENDING4,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CH_XID7_PENDING4,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CH_XID7_PENDING4,	CTC_EVENT_UC_ZERO,	ctcmpc_chx_rx  पूर्ण,
	अणु CH_XID7_PENDING4,	CTC_EVENT_UC_RCRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CH_XID7_PENDING4,	CTC_EVENT_UC_RSRESET,	ctcm_chx_setuperr  पूर्ण,
	अणु CH_XID7_PENDING4,	CTC_EVENT_ATTNBUSY,	ctcm_chx_iofatal  पूर्ण,
	अणु CH_XID7_PENDING4,	CTC_EVENT_TIMER,	ctcmpc_chx_resend  पूर्ण,
	अणु CH_XID7_PENDING4,	CTC_EVENT_IO_EBUSY,	ctcm_chx_fail  पूर्ण,

	अणु CTC_STATE_RXIDLE,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_RXIDLE,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_RXIDLE,	CTC_EVENT_FINSTAT,	ctcmpc_chx_rx  पूर्ण,
	अणु CTC_STATE_RXIDLE,	CTC_EVENT_UC_RCRESET,	ctcm_chx_rxdisc  पूर्ण,
	अणु CTC_STATE_RXIDLE,	CTC_EVENT_UC_RSRESET,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_RXIDLE,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_RXIDLE,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_RXIDLE,	CTC_EVENT_UC_ZERO,	ctcmpc_chx_rx  पूर्ण,

	अणु CTC_STATE_TXINIT,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_FINSTAT,	ctcm_chx_txidle  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_UC_RCRESET,	ctcm_chx_txiniterr  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_UC_RSRESET,	ctcm_chx_txiniterr  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_TIMER,	ctcm_chx_txiniterr  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_TXINIT,	CTC_EVENT_RSWEEP_TIMER,	ctcmpc_chx_send_sweep पूर्ण,

	अणु CTC_STATE_TXIDLE,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_TXIDLE,	CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_TXIDLE,	CTC_EVENT_FINSTAT,	ctcmpc_chx_firstio  पूर्ण,
	अणु CTC_STATE_TXIDLE,	CTC_EVENT_UC_RCRESET,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_TXIDLE,	CTC_EVENT_UC_RSRESET,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_TXIDLE,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_TXIDLE,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_TXIDLE,	CTC_EVENT_RSWEEP_TIMER,	ctcmpc_chx_send_sweep पूर्ण,

	अणु CTC_STATE_TERM,	CTC_EVENT_STOP,		ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_TERM,	CTC_EVENT_START,	ctcm_chx_restart  पूर्ण,
	अणु CTC_STATE_TERM,	CTC_EVENT_FINSTAT,	ctcm_chx_stopped  पूर्ण,
	अणु CTC_STATE_TERM,	CTC_EVENT_UC_RCRESET,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_TERM,	CTC_EVENT_UC_RSRESET,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_TERM,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_TERM,	CTC_EVENT_IO_EBUSY,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_TERM,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,

	अणु CTC_STATE_DTERM,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_DTERM,	CTC_EVENT_START,	ctcm_chx_restart  पूर्ण,
	अणु CTC_STATE_DTERM,	CTC_EVENT_FINSTAT,	ctcm_chx_seपंचांगode  पूर्ण,
	अणु CTC_STATE_DTERM,	CTC_EVENT_UC_RCRESET,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_DTERM,	CTC_EVENT_UC_RSRESET,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_DTERM,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_DTERM,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,

	अणु CTC_STATE_TX,		CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_START,	ctcm_action_nop  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_FINSTAT,	ctcmpc_chx_txकरोne  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_UC_RCRESET,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_UC_RSRESET,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_TIMER,	ctcm_chx_txretry  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_RSWEEP_TIMER,	ctcmpc_chx_send_sweep पूर्ण,
	अणु CTC_STATE_TX,		CTC_EVENT_IO_EBUSY,	ctcm_chx_fail  पूर्ण,

	अणु CTC_STATE_RXERR,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_TXERR,	CTC_EVENT_STOP,		ctcm_chx_haltio  पूर्ण,
	अणु CTC_STATE_TXERR,	CTC_EVENT_IO_ENODEV,	ctcm_chx_iofatal  पूर्ण,
	अणु CTC_STATE_TXERR,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
	अणु CTC_STATE_RXERR,	CTC_EVENT_MC_FAIL,	ctcm_chx_fail  पूर्ण,
पूर्ण;

पूर्णांक mpc_ch_fsm_len = ARRAY_SIZE(ctcmpc_ch_fsm);

/*
 * Actions क्रम पूर्णांकerface - statemachine.
 */

/**
 * Startup channels by sending CTC_EVENT_START to each channel.
 *
 * fi		An instance of an पूर्णांकerface statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from काष्ठा net_device * upon call.
 */
अटल व्योम dev_action_start(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा net_device *dev = arg;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	पूर्णांक direction;

	CTCMY_DBF_DEV_NAME(SETUP, dev, "");

	fsm_delसमयr(&priv->restart_समयr);
	fsm_newstate(fi, DEV_STATE_STARTWAIT_RXTX);
	अगर (IS_MPC(priv))
		priv->mpcg->channels_terminating = 0;
	क्रम (direction = CTCM_READ; direction <= CTCM_WRITE; direction++) अणु
		काष्ठा channel *ch = priv->channel[direction];
		fsm_event(ch->fsm, CTC_EVENT_START, ch);
	पूर्ण
पूर्ण

/**
 * Shutकरोwn channels by sending CTC_EVENT_STOP to each channel.
 *
 * fi		An instance of an पूर्णांकerface statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from काष्ठा net_device * upon call.
 */
अटल व्योम dev_action_stop(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	पूर्णांक direction;
	काष्ठा net_device *dev = arg;
	काष्ठा ctcm_priv *priv = dev->ml_priv;

	CTCMY_DBF_DEV_NAME(SETUP, dev, "");

	fsm_newstate(fi, DEV_STATE_STOPWAIT_RXTX);
	क्रम (direction = CTCM_READ; direction <= CTCM_WRITE; direction++) अणु
		काष्ठा channel *ch = priv->channel[direction];
		fsm_event(ch->fsm, CTC_EVENT_STOP, ch);
		ch->th_seq_num = 0x00;
		CTCM_PR_DEBUG("%s: CH_th_seq= %08x\n",
				__func__, ch->th_seq_num);
	पूर्ण
	अगर (IS_MPC(priv))
		fsm_newstate(priv->mpcg->fsm, MPCG_STATE_RESET);
पूर्ण

अटल व्योम dev_action_restart(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	पूर्णांक restart_समयr;
	काष्ठा net_device *dev = arg;
	काष्ठा ctcm_priv *priv = dev->ml_priv;

	CTCMY_DBF_DEV_NAME(TRACE, dev, "");

	अगर (IS_MPC(priv)) अणु
		restart_समयr = CTCM_TIME_1_SEC;
	पूर्ण अन्यथा अणु
		restart_समयr = CTCM_TIME_5_SEC;
	पूर्ण
	dev_info(&dev->dev, "Restarting device\n");

	dev_action_stop(fi, event, arg);
	fsm_event(priv->fsm, DEV_EVENT_STOP, dev);
	अगर (IS_MPC(priv))
		fsm_newstate(priv->mpcg->fsm, MPCG_STATE_RESET);

	/* going back पूर्णांकo start sequence too quickly can	  */
	/* result in the other side becoming unreachable   due	  */
	/* to sense reported when IO is पातed			  */
	fsm_addसमयr(&priv->restart_समयr, restart_समयr,
			DEV_EVENT_START, dev);
पूर्ण

/**
 * Called from channel statemachine
 * when a channel is up and running.
 *
 * fi		An instance of an पूर्णांकerface statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from काष्ठा net_device * upon call.
 */
अटल व्योम dev_action_chup(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा net_device *dev = arg;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	पूर्णांक dev_stat = fsm_माला_लोtate(fi);

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_NOTICE,
			"%s(%s): priv = %p [%d,%d]\n ",	CTCM_FUNTAIL,
				dev->name, dev->ml_priv, dev_stat, event);

	चयन (fsm_माला_लोtate(fi)) अणु
	हाल DEV_STATE_STARTWAIT_RXTX:
		अगर (event == DEV_EVENT_RXUP)
			fsm_newstate(fi, DEV_STATE_STARTWAIT_TX);
		अन्यथा
			fsm_newstate(fi, DEV_STATE_STARTWAIT_RX);
		अवरोध;
	हाल DEV_STATE_STARTWAIT_RX:
		अगर (event == DEV_EVENT_RXUP) अणु
			fsm_newstate(fi, DEV_STATE_RUNNING);
			dev_info(&dev->dev,
				"Connected with remote side\n");
			ctcm_clear_busy(dev);
		पूर्ण
		अवरोध;
	हाल DEV_STATE_STARTWAIT_TX:
		अगर (event == DEV_EVENT_TXUP) अणु
			fsm_newstate(fi, DEV_STATE_RUNNING);
			dev_info(&dev->dev,
				"Connected with remote side\n");
			ctcm_clear_busy(dev);
		पूर्ण
		अवरोध;
	हाल DEV_STATE_STOPWAIT_TX:
		अगर (event == DEV_EVENT_RXUP)
			fsm_newstate(fi, DEV_STATE_STOPWAIT_RXTX);
		अवरोध;
	हाल DEV_STATE_STOPWAIT_RX:
		अगर (event == DEV_EVENT_TXUP)
			fsm_newstate(fi, DEV_STATE_STOPWAIT_RXTX);
		अवरोध;
	पूर्ण

	अगर (IS_MPC(priv)) अणु
		अगर (event == DEV_EVENT_RXUP)
			mpc_channel_action(priv->channel[CTCM_READ],
				CTCM_READ, MPC_CHANNEL_ADD);
		अन्यथा
			mpc_channel_action(priv->channel[CTCM_WRITE],
				CTCM_WRITE, MPC_CHANNEL_ADD);
	पूर्ण
पूर्ण

/**
 * Called from device statemachine
 * when a channel has been shutकरोwn.
 *
 * fi		An instance of an पूर्णांकerface statemachine.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from काष्ठा net_device * upon call.
 */
अटल व्योम dev_action_chकरोwn(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु

	काष्ठा net_device *dev = arg;
	काष्ठा ctcm_priv *priv = dev->ml_priv;

	CTCMY_DBF_DEV_NAME(SETUP, dev, "");

	चयन (fsm_माला_लोtate(fi)) अणु
	हाल DEV_STATE_RUNNING:
		अगर (event == DEV_EVENT_TXDOWN)
			fsm_newstate(fi, DEV_STATE_STARTWAIT_TX);
		अन्यथा
			fsm_newstate(fi, DEV_STATE_STARTWAIT_RX);
		अवरोध;
	हाल DEV_STATE_STARTWAIT_RX:
		अगर (event == DEV_EVENT_TXDOWN)
			fsm_newstate(fi, DEV_STATE_STARTWAIT_RXTX);
		अवरोध;
	हाल DEV_STATE_STARTWAIT_TX:
		अगर (event == DEV_EVENT_RXDOWN)
			fsm_newstate(fi, DEV_STATE_STARTWAIT_RXTX);
		अवरोध;
	हाल DEV_STATE_STOPWAIT_RXTX:
		अगर (event == DEV_EVENT_TXDOWN)
			fsm_newstate(fi, DEV_STATE_STOPWAIT_RX);
		अन्यथा
			fsm_newstate(fi, DEV_STATE_STOPWAIT_TX);
		अवरोध;
	हाल DEV_STATE_STOPWAIT_RX:
		अगर (event == DEV_EVENT_RXDOWN)
			fsm_newstate(fi, DEV_STATE_STOPPED);
		अवरोध;
	हाल DEV_STATE_STOPWAIT_TX:
		अगर (event == DEV_EVENT_TXDOWN)
			fsm_newstate(fi, DEV_STATE_STOPPED);
		अवरोध;
	पूर्ण
	अगर (IS_MPC(priv)) अणु
		अगर (event == DEV_EVENT_RXDOWN)
			mpc_channel_action(priv->channel[CTCM_READ],
				CTCM_READ, MPC_CHANNEL_REMOVE);
		अन्यथा
			mpc_channel_action(priv->channel[CTCM_WRITE],
				CTCM_WRITE, MPC_CHANNEL_REMOVE);
	पूर्ण
पूर्ण

स्थिर fsm_node dev_fsm[] = अणु
	अणु DEV_STATE_STOPPED,        DEV_EVENT_START,   dev_action_start   पूर्ण,
	अणु DEV_STATE_STOPWAIT_RXTX,  DEV_EVENT_START,   dev_action_start   पूर्ण,
	अणु DEV_STATE_STOPWAIT_RXTX,  DEV_EVENT_RXDOWN,  dev_action_chकरोwn  पूर्ण,
	अणु DEV_STATE_STOPWAIT_RXTX,  DEV_EVENT_TXDOWN,  dev_action_chकरोwn  पूर्ण,
	अणु DEV_STATE_STOPWAIT_RXTX,  DEV_EVENT_RESTART, dev_action_restart पूर्ण,
	अणु DEV_STATE_STOPWAIT_RX,    DEV_EVENT_START,   dev_action_start   पूर्ण,
	अणु DEV_STATE_STOPWAIT_RX,    DEV_EVENT_RXUP,    dev_action_chup    पूर्ण,
	अणु DEV_STATE_STOPWAIT_RX,    DEV_EVENT_TXUP,    dev_action_chup    पूर्ण,
	अणु DEV_STATE_STOPWAIT_RX,    DEV_EVENT_RXDOWN,  dev_action_chकरोwn  पूर्ण,
	अणु DEV_STATE_STOPWAIT_RX,    DEV_EVENT_RESTART, dev_action_restart पूर्ण,
	अणु DEV_STATE_STOPWAIT_TX,    DEV_EVENT_START,   dev_action_start   पूर्ण,
	अणु DEV_STATE_STOPWAIT_TX,    DEV_EVENT_RXUP,    dev_action_chup    पूर्ण,
	अणु DEV_STATE_STOPWAIT_TX,    DEV_EVENT_TXUP,    dev_action_chup    पूर्ण,
	अणु DEV_STATE_STOPWAIT_TX,    DEV_EVENT_TXDOWN,  dev_action_chकरोwn  पूर्ण,
	अणु DEV_STATE_STOPWAIT_TX,    DEV_EVENT_RESTART, dev_action_restart पूर्ण,
	अणु DEV_STATE_STARTWAIT_RXTX, DEV_EVENT_STOP,    dev_action_stop    पूर्ण,
	अणु DEV_STATE_STARTWAIT_RXTX, DEV_EVENT_RXUP,    dev_action_chup    पूर्ण,
	अणु DEV_STATE_STARTWAIT_RXTX, DEV_EVENT_TXUP,    dev_action_chup    पूर्ण,
	अणु DEV_STATE_STARTWAIT_RXTX, DEV_EVENT_RXDOWN,  dev_action_chकरोwn  पूर्ण,
	अणु DEV_STATE_STARTWAIT_RXTX, DEV_EVENT_TXDOWN,  dev_action_chकरोwn  पूर्ण,
	अणु DEV_STATE_STARTWAIT_RXTX, DEV_EVENT_RESTART, dev_action_restart पूर्ण,
	अणु DEV_STATE_STARTWAIT_TX,   DEV_EVENT_STOP,    dev_action_stop    पूर्ण,
	अणु DEV_STATE_STARTWAIT_TX,   DEV_EVENT_RXUP,    dev_action_chup    पूर्ण,
	अणु DEV_STATE_STARTWAIT_TX,   DEV_EVENT_TXUP,    dev_action_chup    पूर्ण,
	अणु DEV_STATE_STARTWAIT_TX,   DEV_EVENT_RXDOWN,  dev_action_chकरोwn  पूर्ण,
	अणु DEV_STATE_STARTWAIT_TX,   DEV_EVENT_RESTART, dev_action_restart पूर्ण,
	अणु DEV_STATE_STARTWAIT_RX,   DEV_EVENT_STOP,    dev_action_stop    पूर्ण,
	अणु DEV_STATE_STARTWAIT_RX,   DEV_EVENT_RXUP,    dev_action_chup    पूर्ण,
	अणु DEV_STATE_STARTWAIT_RX,   DEV_EVENT_TXUP,    dev_action_chup    पूर्ण,
	अणु DEV_STATE_STARTWAIT_RX,   DEV_EVENT_TXDOWN,  dev_action_chकरोwn  पूर्ण,
	अणु DEV_STATE_STARTWAIT_RX,   DEV_EVENT_RESTART, dev_action_restart पूर्ण,
	अणु DEV_STATE_RUNNING,        DEV_EVENT_STOP,    dev_action_stop    पूर्ण,
	अणु DEV_STATE_RUNNING,        DEV_EVENT_RXDOWN,  dev_action_chकरोwn  पूर्ण,
	अणु DEV_STATE_RUNNING,        DEV_EVENT_TXDOWN,  dev_action_chकरोwn  पूर्ण,
	अणु DEV_STATE_RUNNING,        DEV_EVENT_TXUP,    ctcm_action_nop    पूर्ण,
	अणु DEV_STATE_RUNNING,        DEV_EVENT_RXUP,    ctcm_action_nop    पूर्ण,
	अणु DEV_STATE_RUNNING,        DEV_EVENT_RESTART, dev_action_restart पूर्ण,
पूर्ण;

पूर्णांक dev_fsm_len = ARRAY_SIZE(dev_fsm);

/* --- This is the END my मित्र --- */

