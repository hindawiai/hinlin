<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित __MAILBOX_CONTROLLER_H
#घोषणा __MAILBOX_CONTROLLER_H

#समावेश <linux/of.h>
#समावेश <linux/types.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/device.h>
#समावेश <linux/completion.h>

काष्ठा mbox_chan;

/**
 * काष्ठा mbox_chan_ops - methods to control mailbox channels
 * @send_data:	The API asks the MBOX controller driver, in atomic
 *		context try to transmit a message on the bus. Returns 0 अगर
 *		data is accepted क्रम transmission, -EBUSY जबतक rejecting
 *		अगर the remote hasn't yet पढ़ो the last data sent. Actual
 *		transmission of data is reported by the controller via
 *		mbox_chan_txकरोne (अगर it has some TX ACK irq). It must not
 *		sleep.
 * @flush:	Called when a client requests transmissions to be blocking but
 *		the context करोesn't allow sleeping. Typically the controller
 *		will implement a busy loop रुकोing क्रम the data to flush out.
 * @startup:	Called when a client requests the chan. The controller
 *		could ask clients क्रम additional parameters of communication
 *		to be provided via client's chan_data. This call may
 *		block. After this call the Controller must क्रमward any
 *		data received on the chan by calling mbox_chan_received_data.
 *		The controller may करो stuff that need to sleep.
 * @shutकरोwn:	Called when a client relinquishes control of a chan.
 *		This call may block too. The controller must not क्रमward
 *		any received data anymore.
 *		The controller may करो stuff that need to sleep.
 * @last_tx_करोne: If the controller sets 'txdone_poll', the API calls
 *		  this to poll status of last TX. The controller must
 *		  give priority to IRQ method over polling and never
 *		  set both txकरोne_poll and txकरोne_irq. Only in polling
 *		  mode 'send_data' is expected to वापस -EBUSY.
 *		  The controller may करो stuff that need to sleep/block.
 *		  Used only अगर txकरोne_poll:=true && txकरोne_irq:=false
 * @peek_data: Atomic check क्रम any received data. Return true अगर controller
 *		  has some data to push to the client. False otherwise.
 */
काष्ठा mbox_chan_ops अणु
	पूर्णांक (*send_data)(काष्ठा mbox_chan *chan, व्योम *data);
	पूर्णांक (*flush)(काष्ठा mbox_chan *chan, अचिन्हित दीर्घ समयout);
	पूर्णांक (*startup)(काष्ठा mbox_chan *chan);
	व्योम (*shutकरोwn)(काष्ठा mbox_chan *chan);
	bool (*last_tx_करोne)(काष्ठा mbox_chan *chan);
	bool (*peek_data)(काष्ठा mbox_chan *chan);
पूर्ण;

/**
 * काष्ठा mbox_controller - Controller of a class of communication channels
 * @dev:		Device backing this controller
 * @ops:		Operators that work on each communication chan
 * @chans:		Array of channels
 * @num_chans:		Number of channels in the 'chans' array.
 * @txकरोne_irq:		Indicates अगर the controller can report to API when
 *			the last transmitted data was पढ़ो by the remote.
 *			Eg, अगर it has some TX ACK irq.
 * @txकरोne_poll:	If the controller can पढ़ो but not report the TX
 *			करोne. Ex, some रेजिस्टर shows the TX status but
 *			no पूर्णांकerrupt rises. Ignored अगर 'txdone_irq' is set.
 * @txpoll_period:	If 'txdone_poll' is in effect, the API polls क्रम
 *			last TX's status after these many millisecs
 * @of_xlate:		Controller driver specअगरic mapping of channel via DT
 * @poll_hrt:		API निजी. hrसमयr used to poll क्रम TXDONE on all
 *			channels.
 * @node:		API निजी. To hook पूर्णांकo list of controllers.
 */
काष्ठा mbox_controller अणु
	काष्ठा device *dev;
	स्थिर काष्ठा mbox_chan_ops *ops;
	काष्ठा mbox_chan *chans;
	पूर्णांक num_chans;
	bool txकरोne_irq;
	bool txकरोne_poll;
	अचिन्हित txpoll_period;
	काष्ठा mbox_chan *(*of_xlate)(काष्ठा mbox_controller *mbox,
				      स्थिर काष्ठा of_phandle_args *sp);
	/* Internal to API */
	काष्ठा hrसमयr poll_hrt;
	काष्ठा list_head node;
पूर्ण;

/*
 * The length of circular buffer क्रम queuing messages from a client.
 * 'msg_count' tracks the number of buffered messages while 'msg_free'
 * is the index where the next message would be buffered.
 * We shouldn't need it too big because every transfer is पूर्णांकerrupt
 * triggered and अगर we have lots of data to transfer, the पूर्णांकerrupt
 * latencies are going to be the bottleneck, not the buffer length.
 * Besides, mbox_send_message could be called from atomic context and
 * the client could also queue another message from the notअगरier 'tx_done'
 * of the last transfer करोne.
 * REVISIT: If too many platक्रमms see the "Try increasing MBOX_TX_QUEUE_LEN"
 * prपूर्णांक, it needs to be taken from config option or somesuch.
 */
#घोषणा MBOX_TX_QUEUE_LEN	20

/**
 * काष्ठा mbox_chan - s/w representation of a communication chan
 * @mbox:		Poपूर्णांकer to the parent/provider of this channel
 * @txकरोne_method:	Way to detect TXDone chosen by the API
 * @cl:			Poपूर्णांकer to the current owner of this channel
 * @tx_complete:	Transmission completion
 * @active_req:		Currently active request hook
 * @msg_count:		No. of mssg currently queued
 * @msg_मुक्त:		Index of next available mssg slot
 * @msg_data:		Hook क्रम data packet
 * @lock:		Serialise access to the channel
 * @con_priv:		Hook क्रम controller driver to attach निजी data
 */
काष्ठा mbox_chan अणु
	काष्ठा mbox_controller *mbox;
	अचिन्हित txकरोne_method;
	काष्ठा mbox_client *cl;
	काष्ठा completion tx_complete;
	व्योम *active_req;
	अचिन्हित msg_count, msg_मुक्त;
	व्योम *msg_data[MBOX_TX_QUEUE_LEN];
	spinlock_t lock; /* Serialise access to the channel */
	व्योम *con_priv;
पूर्ण;

पूर्णांक mbox_controller_रेजिस्टर(काष्ठा mbox_controller *mbox); /* can sleep */
व्योम mbox_controller_unरेजिस्टर(काष्ठा mbox_controller *mbox); /* can sleep */
व्योम mbox_chan_received_data(काष्ठा mbox_chan *chan, व्योम *data); /* atomic */
व्योम mbox_chan_txकरोne(काष्ठा mbox_chan *chan, पूर्णांक r); /* atomic */

पूर्णांक devm_mbox_controller_रेजिस्टर(काष्ठा device *dev,
				  काष्ठा mbox_controller *mbox);
व्योम devm_mbox_controller_unरेजिस्टर(काष्ठा device *dev,
				     काष्ठा mbox_controller *mbox);

#पूर्ण_अगर /* __MAILBOX_CONTROLLER_H */
