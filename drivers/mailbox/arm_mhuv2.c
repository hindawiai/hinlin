<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ARM Message Handling Unit Version 2 (MHUv2) driver.
 *
 * Copyright (C) 2020 ARM Ltd.
 * Copyright (C) 2020 Linaro Ltd.
 *
 * An MHUv2 mailbox controller can provide up to 124 channel winकरोws (each 32
 * bit दीर्घ) and the driver allows any combination of both the transport
 * protocol modes: data-transfer and करोorbell, to be used on those channel
 * winकरोws.
 *
 * The transport protocols should be specअगरied in the device tree entry क्रम the
 * device. The transport protocols determine how the underlying hardware
 * resources of the device are utilized when transmitting data. Refer to the
 * device tree bindings of the ARM MHUv2 controller क्रम more details.
 *
 * The number of रेजिस्टरed mailbox channels is dependent on both the underlying
 * hardware - मुख्यly the number of channel winकरोws implemented by the platक्रमm,
 * as well as the selected transport protocols.
 *
 * The MHUv2 controller can work both as a sender and receiver, but the driver
 * and the DT bindings support unidirectional transfers क्रम better allocation of
 * the channels. That is, this driver will be probed क्रम two separate devices
 * क्रम each mailbox controller, a sender device and a receiver device.
 */

#समावेश <linux/amba/bus.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/mailbox/arm_mhuv2_message.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/spinlock.h>

/* ====== MHUv2 Registers ====== */

/* Maximum number of channel winकरोws */
#घोषणा MHUV2_CH_WN_MAX			124
/* Number of combined पूर्णांकerrupt status रेजिस्टरs */
#घोषणा MHUV2_CMB_INT_ST_REG_CNT	4
#घोषणा MHUV2_STAT_BYTES		(माप(u32))
#घोषणा MHUV2_STAT_BITS			(MHUV2_STAT_BYTES * __अक्षर_बिट__)

#घोषणा LSB_MASK(n)			((1 << (n * __अक्षर_बिट__)) - 1)
#घोषणा MHUV2_PROTOCOL_PROP		"arm,mhuv2-protocols"

/* Register Message Handling Unit Configuration fields */
काष्ठा mhu_cfg_t अणु
	u32 num_ch : 7;
	u32 pad : 25;
पूर्ण __packed;

/* रेजिस्टर Interrupt Status fields */
काष्ठा पूर्णांक_st_t अणु
	u32 nr2r : 1;
	u32 r2nr : 1;
	u32 pad : 30;
पूर्ण __packed;

/* Register Interrupt Clear fields */
काष्ठा पूर्णांक_clr_t अणु
	u32 nr2r : 1;
	u32 r2nr : 1;
	u32 pad : 30;
पूर्ण __packed;

/* Register Interrupt Enable fields */
काष्ठा पूर्णांक_en_t अणु
	u32 r2nr : 1;
	u32 nr2r : 1;
	u32 chcomb : 1;
	u32 pad : 29;
पूर्ण __packed;

/* Register Implementer Identअगरication fields */
काष्ठा iidr_t अणु
	u32 implementer : 12;
	u32 revision : 4;
	u32 variant : 4;
	u32 product_id : 12;
पूर्ण __packed;

/* Register Architecture Identअगरication Register fields */
काष्ठा aidr_t अणु
	u32 arch_minor_rev : 4;
	u32 arch_major_rev : 4;
	u32 pad : 24;
पूर्ण __packed;

/* Sender Channel Winकरोw fields */
काष्ठा mhu2_send_ch_wn_reg अणु
	u32 stat;
	u8 pad1[0x0C - 0x04];
	u32 stat_set;
	u32 पूर्णांक_st;
	u32 पूर्णांक_clr;
	u32 पूर्णांक_en;
	u8 pad2[0x20 - 0x1C];
पूर्ण __packed;

/* Sender frame रेजिस्टर fields */
काष्ठा mhu2_send_frame_reg अणु
	काष्ठा mhu2_send_ch_wn_reg ch_wn[MHUV2_CH_WN_MAX];
	काष्ठा mhu_cfg_t mhu_cfg;
	u32 resp_cfg;
	u32 access_request;
	u32 access_पढ़ोy;
	काष्ठा पूर्णांक_st_t पूर्णांक_st;
	काष्ठा पूर्णांक_clr_t पूर्णांक_clr;
	काष्ठा पूर्णांक_en_t पूर्णांक_en;
	u32 reserved0;
	u32 chcomb_पूर्णांक_st[MHUV2_CMB_INT_ST_REG_CNT];
	u8 pad[0xFC8 - 0xFB0];
	काष्ठा iidr_t iidr;
	काष्ठा aidr_t aidr;
पूर्ण __packed;

/* Receiver Channel Winकरोw fields */
काष्ठा mhu2_recv_ch_wn_reg अणु
	u32 stat;
	u32 stat_masked;
	u32 stat_clear;
	u8 reserved0[0x10 - 0x0C];
	u32 mask;
	u32 mask_set;
	u32 mask_clear;
	u8 pad[0x20 - 0x1C];
पूर्ण __packed;

/* Receiver frame रेजिस्टर fields */
काष्ठा mhu2_recv_frame_reg अणु
	काष्ठा mhu2_recv_ch_wn_reg ch_wn[MHUV2_CH_WN_MAX];
	काष्ठा mhu_cfg_t mhu_cfg;
	u8 reserved0[0xF90 - 0xF84];
	काष्ठा पूर्णांक_st_t पूर्णांक_st;
	काष्ठा पूर्णांक_clr_t पूर्णांक_clr;
	काष्ठा पूर्णांक_en_t पूर्णांक_en;
	u32 pad;
	u32 chcomb_पूर्णांक_st[MHUV2_CMB_INT_ST_REG_CNT];
	u8 reserved2[0xFC8 - 0xFB0];
	काष्ठा iidr_t iidr;
	काष्ठा aidr_t aidr;
पूर्ण __packed;


/* ====== MHUv2 data काष्ठाures ====== */

क्रमागत mhuv2_transport_protocol अणु
	DOORBELL = 0,
	DATA_TRANSFER = 1
पूर्ण;

क्रमागत mhuv2_frame अणु
	RECEIVER_FRAME,
	SENDER_FRAME
पूर्ण;

/**
 * काष्ठा mhuv2 - MHUv2 mailbox controller data
 *
 * @mbox:	Mailbox controller beदीर्घing to the MHU frame.
 * @send/recv:	Base address of the रेजिस्टर mapping region.
 * @frame:	Frame type: RECEIVER_FRAME or SENDER_FRAME.
 * @irq:	Interrupt.
 * @winकरोws:	Channel winकरोws implemented by the platक्रमm.
 * @minor:	Minor version of the controller.
 * @length:	Length of the protocols array in bytes.
 * @protocols:	Raw protocol inक्रमmation, derived from device tree.
 * @करोorbell_pending_lock: spinlock required क्रम correct operation of Tx
 *		पूर्णांकerrupt क्रम करोorbells.
 */
काष्ठा mhuv2 अणु
	काष्ठा mbox_controller mbox;
	जोड़ अणु
		काष्ठा mhu2_send_frame_reg __iomem *send;
		काष्ठा mhu2_recv_frame_reg __iomem *recv;
	पूर्ण;
	क्रमागत mhuv2_frame frame;
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक winकरोws;
	अचिन्हित पूर्णांक minor;
	अचिन्हित पूर्णांक length;
	u32 *protocols;

	spinlock_t करोorbell_pending_lock;
पूर्ण;

#घोषणा mhu_from_mbox(_mbox) container_of(_mbox, काष्ठा mhuv2, mbox)

/**
 * काष्ठा mhuv2_protocol_ops - MHUv2 operations
 *
 * Each transport protocol must provide an implementation of the operations
 * provided here.
 *
 * @rx_startup: Startup callback क्रम receiver.
 * @rx_shutकरोwn: Shutकरोwn callback क्रम receiver.
 * @पढ़ो_data: Reads and clears newly available data.
 * @tx_startup: Startup callback क्रम receiver.
 * @tx_shutकरोwn: Shutकरोwn callback क्रम receiver.
 * @last_tx_करोne: Report back अगर the last tx is completed or not.
 * @send_data: Send data to the receiver.
 */
काष्ठा mhuv2_protocol_ops अणु
	पूर्णांक (*rx_startup)(काष्ठा mhuv2 *mhu, काष्ठा mbox_chan *chan);
	व्योम (*rx_shutकरोwn)(काष्ठा mhuv2 *mhu, काष्ठा mbox_chan *chan);
	व्योम *(*पढ़ो_data)(काष्ठा mhuv2 *mhu, काष्ठा mbox_chan *chan);

	व्योम (*tx_startup)(काष्ठा mhuv2 *mhu, काष्ठा mbox_chan *chan);
	व्योम (*tx_shutकरोwn)(काष्ठा mhuv2 *mhu, काष्ठा mbox_chan *chan);
	पूर्णांक (*last_tx_करोne)(काष्ठा mhuv2 *mhu, काष्ठा mbox_chan *chan);
	पूर्णांक (*send_data)(काष्ठा mhuv2 *mhu, काष्ठा mbox_chan *chan, व्योम *arg);
पूर्ण;

/*
 * MHUv2 mailbox channel's निजी inक्रमmation
 *
 * @ops:	protocol specअगरic ops क्रम the channel.
 * @ch_wn_idx:	Channel winकरोw index allocated to the channel.
 * @winकरोws:	Total number of winकरोws consumed by the channel, only relevant
 *		in DATA_TRANSFER protocol.
 * @करोorbell:	Doorbell bit number within the ch_wn_idx winकरोw, only relevant
 *		in DOORBELL protocol.
 * @pending:	Flag indicating pending करोorbell पूर्णांकerrupt, only relevant in
 *		DOORBELL protocol.
 */
काष्ठा mhuv2_mbox_chan_priv अणु
	स्थिर काष्ठा mhuv2_protocol_ops *ops;
	u32 ch_wn_idx;
	जोड़ अणु
		u32 winकरोws;
		काष्ठा अणु
			u32 करोorbell;
			u32 pending;
		पूर्ण;
	पूर्ण;
पूर्ण;

/* Macro क्रम पढ़ोing a bitfield within a physically mapped packed काष्ठा */
#घोषणा पढ़ोl_relaxed_bitfield(_regptr, _type, _field)			\
	(अणु								\
		u32 _regval;						\
		_regval = पढ़ोl_relaxed((_regptr));			\
		(*(_type *)(&_regval))._field;				\
	पूर्ण)

/* Macro क्रम writing a bitfield within a physically mapped packed काष्ठा */
#घोषणा ग_लिखोl_relaxed_bitfield(_value, _regptr, _type, _field)		\
	(अणु								\
		u32 _regval;						\
		_regval = पढ़ोl_relaxed(_regptr);			\
		(*(_type *)(&_regval))._field = _value;			\
		ग_लिखोl_relaxed(_regval, _regptr);			\
	पूर्ण)


/* =================== Doorbell transport protocol operations =============== */

अटल पूर्णांक mhuv2_करोorbell_rx_startup(काष्ठा mhuv2 *mhu, काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;

	ग_लिखोl_relaxed(BIT(priv->करोorbell),
		       &mhu->recv->ch_wn[priv->ch_wn_idx].mask_clear);
	वापस 0;
पूर्ण

अटल व्योम mhuv2_करोorbell_rx_shutकरोwn(काष्ठा mhuv2 *mhu,
				       काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;

	ग_लिखोl_relaxed(BIT(priv->करोorbell),
		       &mhu->recv->ch_wn[priv->ch_wn_idx].mask_set);
पूर्ण

अटल व्योम *mhuv2_करोorbell_पढ़ो_data(काष्ठा mhuv2 *mhu, काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;

	ग_लिखोl_relaxed(BIT(priv->करोorbell),
		       &mhu->recv->ch_wn[priv->ch_wn_idx].stat_clear);
	वापस शून्य;
पूर्ण

अटल पूर्णांक mhuv2_करोorbell_last_tx_करोne(काष्ठा mhuv2 *mhu,
				       काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;

	वापस !(पढ़ोl_relaxed(&mhu->send->ch_wn[priv->ch_wn_idx].stat) &
		 BIT(priv->करोorbell));
पूर्ण

अटल पूर्णांक mhuv2_करोorbell_send_data(काष्ठा mhuv2 *mhu, काष्ठा mbox_chan *chan,
				    व्योम *arg)
अणु
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mhu->करोorbell_pending_lock, flags);

	priv->pending = 1;
	ग_लिखोl_relaxed(BIT(priv->करोorbell),
		       &mhu->send->ch_wn[priv->ch_wn_idx].stat_set);

	spin_unlock_irqrestore(&mhu->करोorbell_pending_lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mhuv2_protocol_ops mhuv2_करोorbell_ops = अणु
	.rx_startup = mhuv2_करोorbell_rx_startup,
	.rx_shutकरोwn = mhuv2_करोorbell_rx_shutकरोwn,
	.पढ़ो_data = mhuv2_करोorbell_पढ़ो_data,
	.last_tx_करोne = mhuv2_करोorbell_last_tx_करोne,
	.send_data = mhuv2_करोorbell_send_data,
पूर्ण;
#घोषणा IS_PROTOCOL_DOORBELL(_priv) (_priv->ops == &mhuv2_करोorbell_ops)

/* ============= Data transfer transport protocol operations ================ */

अटल पूर्णांक mhuv2_data_transfer_rx_startup(काष्ठा mhuv2 *mhu,
					  काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;
	पूर्णांक i = priv->ch_wn_idx + priv->winकरोws - 1;

	/*
	 * The protocol mandates that all but the last status रेजिस्टर must be
	 * masked.
	 */
	ग_लिखोl_relaxed(0xFFFFFFFF, &mhu->recv->ch_wn[i].mask_clear);
	वापस 0;
पूर्ण

अटल व्योम mhuv2_data_transfer_rx_shutकरोwn(काष्ठा mhuv2 *mhu,
					    काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;
	पूर्णांक i = priv->ch_wn_idx + priv->winकरोws - 1;

	ग_लिखोl_relaxed(0xFFFFFFFF, &mhu->recv->ch_wn[i].mask_set);
पूर्ण

अटल व्योम *mhuv2_data_transfer_पढ़ो_data(काष्ठा mhuv2 *mhu,
					   काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;
	स्थिर पूर्णांक winकरोws = priv->winकरोws;
	काष्ठा arm_mhuv2_mbox_msg *msg;
	u32 *data;
	पूर्णांक i, idx;

	msg = kzalloc(माप(*msg) + winकरोws * MHUV2_STAT_BYTES, GFP_KERNEL);
	अगर (!msg)
		वापस ERR_PTR(-ENOMEM);

	data = msg->data = msg + 1;
	msg->len = winकरोws * MHUV2_STAT_BYTES;

	/*
	 * Messages are expected in order of most signअगरicant word to least
	 * signअगरicant word. Refer mhuv2_data_transfer_send_data() क्रम more
	 * details.
	 *
	 * We also need to पढ़ो the stat रेजिस्टर instead of stat_masked, as we
	 * masked all but the last winकरोw.
	 *
	 * Last channel winकरोw must be cleared as the final operation. Upon
	 * clearing the last channel winकरोw रेजिस्टर, which is unmasked in
	 * data-transfer protocol, the पूर्णांकerrupt is de-निश्चितed.
	 */
	क्रम (i = 0; i < winकरोws; i++) अणु
		idx = priv->ch_wn_idx + i;
		data[winकरोws - 1 - i] = पढ़ोl_relaxed(&mhu->recv->ch_wn[idx].stat);
		ग_लिखोl_relaxed(0xFFFFFFFF, &mhu->recv->ch_wn[idx].stat_clear);
	पूर्ण

	वापस msg;
पूर्ण

अटल व्योम mhuv2_data_transfer_tx_startup(काष्ठा mhuv2 *mhu,
					   काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;
	पूर्णांक i = priv->ch_wn_idx + priv->winकरोws - 1;

	/* Enable पूर्णांकerrupts only क्रम the last winकरोw */
	अगर (mhu->minor) अणु
		ग_लिखोl_relaxed(0x1, &mhu->send->ch_wn[i].पूर्णांक_clr);
		ग_लिखोl_relaxed(0x1, &mhu->send->ch_wn[i].पूर्णांक_en);
	पूर्ण
पूर्ण

अटल व्योम mhuv2_data_transfer_tx_shutकरोwn(काष्ठा mhuv2 *mhu,
					    काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;
	पूर्णांक i = priv->ch_wn_idx + priv->winकरोws - 1;

	अगर (mhu->minor)
		ग_लिखोl_relaxed(0x0, &mhu->send->ch_wn[i].पूर्णांक_en);
पूर्ण

अटल पूर्णांक mhuv2_data_transfer_last_tx_करोne(काष्ठा mhuv2 *mhu,
					    काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;
	पूर्णांक i = priv->ch_wn_idx + priv->winकरोws - 1;

	/* Just checking the last channel winकरोw should be enough */
	वापस !पढ़ोl_relaxed(&mhu->send->ch_wn[i].stat);
पूर्ण

/*
 * Message will be transmitted from most signअगरicant to least signअगरicant word.
 * This is to allow क्रम messages लघुer than channel winकरोws to still trigger
 * the receiver पूर्णांकerrupt which माला_लो activated when the last stat रेजिस्टर is
 * written. As an example, a 6-word message is to be written on a 4-channel MHU
 * connection: Registers marked with '*' are masked, and will not generate an
 * पूर्णांकerrupt on the receiver side once written.
 *
 * u32 *data =	[0x00000001], [0x00000002], [0x00000003], [0x00000004],
 *		[0x00000005], [0x00000006]
 *
 * ROUND 1:
 * stat reg		To ग_लिखो	Write sequence
 * [ stat 3 ]	<-	[0x00000001]	4 <- triggers पूर्णांकerrupt on receiver
 * [ stat 2 ]	<-	[0x00000002]	3
 * [ stat 1 ]	<-	[0x00000003]	2
 * [ stat 0 ]	<-	[0x00000004]	1
 *
 * data += 4 // Increment data poपूर्णांकer by number of stat regs
 *
 * ROUND 2:
 * stat reg		To ग_लिखो	Write sequence
 * [ stat 3 ]	<-	[0x00000005]	2 <- triggers पूर्णांकerrupt on receiver
 * [ stat 2 ]	<-	[0x00000006]	1
 * [ stat 1 ]	<-	[0x00000000]
 * [ stat 0 ]	<-	[0x00000000]
 */
अटल पूर्णांक mhuv2_data_transfer_send_data(काष्ठा mhuv2 *mhu,
					 काष्ठा mbox_chan *chan, व्योम *arg)
अणु
	स्थिर काष्ठा arm_mhuv2_mbox_msg *msg = arg;
	पूर्णांक bytes_left = msg->len, bytes_to_send, bytes_in_round, i;
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;
	पूर्णांक winकरोws = priv->winकरोws;
	u32 *data = msg->data, word;

	जबतक (bytes_left) अणु
		अगर (!data[0]) अणु
			dev_err(mhu->mbox.dev, "Data aligned at first window can't be zero to guarantee interrupt generation at receiver");
			वापस -EINVAL;
		पूर्ण

		जबतक(!mhuv2_data_transfer_last_tx_करोne(mhu, chan))
			जारी;

		bytes_in_round = min(bytes_left, (पूर्णांक)(winकरोws * MHUV2_STAT_BYTES));

		क्रम (i = winकरोws - 1; i >= 0; i--) अणु
			/* Data less than winकरोws can transfer ? */
			अगर (unlikely(bytes_in_round <= i * MHUV2_STAT_BYTES))
				जारी;

			word = data[i];
			bytes_to_send = bytes_in_round & (MHUV2_STAT_BYTES - 1);
			अगर (unlikely(bytes_to_send))
				word &= LSB_MASK(bytes_to_send);
			अन्यथा
				bytes_to_send = MHUV2_STAT_BYTES;

			ग_लिखोl_relaxed(word, &mhu->send->ch_wn[priv->ch_wn_idx + winकरोws - 1 - i].stat_set);
			bytes_left -= bytes_to_send;
			bytes_in_round -= bytes_to_send;
		पूर्ण

		data += winकरोws;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mhuv2_protocol_ops mhuv2_data_transfer_ops = अणु
	.rx_startup = mhuv2_data_transfer_rx_startup,
	.rx_shutकरोwn = mhuv2_data_transfer_rx_shutकरोwn,
	.पढ़ो_data = mhuv2_data_transfer_पढ़ो_data,
	.tx_startup = mhuv2_data_transfer_tx_startup,
	.tx_shutकरोwn = mhuv2_data_transfer_tx_shutकरोwn,
	.last_tx_करोne = mhuv2_data_transfer_last_tx_करोne,
	.send_data = mhuv2_data_transfer_send_data,
पूर्ण;

/* Interrupt handlers */

अटल काष्ठा mbox_chan *get_irq_chan_comb(काष्ठा mhuv2 *mhu, u32 __iomem *reg)
अणु
	काष्ठा mbox_chan *chans = mhu->mbox.chans;
	पूर्णांक channel = 0, i, offset = 0, winकरोws, protocol, ch_wn;
	u32 stat;

	क्रम (i = 0; i < MHUV2_CMB_INT_ST_REG_CNT; i++) अणु
		stat = पढ़ोl_relaxed(reg + i);
		अगर (!stat)
			जारी;

		ch_wn = i * MHUV2_STAT_BITS + __builtin_ctz(stat);

		क्रम (i = 0; i < mhu->length; i += 2) अणु
			protocol = mhu->protocols[i];
			winकरोws = mhu->protocols[i + 1];

			अगर (ch_wn >= offset + winकरोws) अणु
				अगर (protocol == DOORBELL)
					channel += MHUV2_STAT_BITS * winकरोws;
				अन्यथा
					channel++;

				offset += winकरोws;
				जारी;
			पूर्ण

			/* Return first chan of the winकरोw in करोorbell mode */
			अगर (protocol == DOORBELL)
				channel += MHUV2_STAT_BITS * (ch_wn - offset);

			वापस &chans[channel];
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-EIO);
पूर्ण

अटल irqवापस_t mhuv2_sender_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mhuv2 *mhu = data;
	काष्ठा device *dev = mhu->mbox.dev;
	काष्ठा mhuv2_mbox_chan_priv *priv;
	काष्ठा mbox_chan *chan;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, found = 0;
	u32 stat;

	chan = get_irq_chan_comb(mhu, mhu->send->chcomb_पूर्णांक_st);
	अगर (IS_ERR(chan)) अणु
		dev_warn(dev, "Failed to find channel for the Tx interrupt\n");
		वापस IRQ_NONE;
	पूर्ण
	priv = chan->con_priv;

	अगर (!IS_PROTOCOL_DOORBELL(priv)) अणु
		ग_लिखोl_relaxed(1, &mhu->send->ch_wn[priv->ch_wn_idx + priv->winकरोws - 1].पूर्णांक_clr);

		अगर (chan->cl) अणु
			mbox_chan_txकरोne(chan, 0);
			वापस IRQ_HANDLED;
		पूर्ण

		dev_warn(dev, "Tx interrupt Received on channel (%u) not currently attached to a mailbox client\n",
			 priv->ch_wn_idx);
		वापस IRQ_NONE;
	पूर्ण

	/* Clear the पूर्णांकerrupt first, so we करोn't miss any करोorbell later */
	ग_लिखोl_relaxed(1, &mhu->send->ch_wn[priv->ch_wn_idx].पूर्णांक_clr);

	/*
	 * In Doorbell mode, make sure no new transitions happen जबतक the
	 * पूर्णांकerrupt handler is trying to find the finished करोorbell tx
	 * operations, अन्यथा we may think few of the transfers were complete
	 * beक्रमe they actually were.
	 */
	spin_lock_irqsave(&mhu->करोorbell_pending_lock, flags);

	/*
	 * In हाल of करोorbell mode, the first channel of the winकरोw is वापसed
	 * by get_irq_chan_comb(). Find all the pending channels here.
	 */
	stat = पढ़ोl_relaxed(&mhu->send->ch_wn[priv->ch_wn_idx].stat);

	क्रम (i = 0; i < MHUV2_STAT_BITS; i++) अणु
		priv = chan[i].con_priv;

		/* Find हालs where pending was 1, but stat's bit is cleared */
		अगर (priv->pending ^ ((stat >> i) & 0x1)) अणु
			BUG_ON(!priv->pending);

			अगर (!chan->cl) अणु
				dev_warn(dev, "Tx interrupt received on doorbell (%u : %u) channel not currently attached to a mailbox client\n",
					 priv->ch_wn_idx, i);
				जारी;
			पूर्ण

			mbox_chan_txकरोne(&chan[i], 0);
			priv->pending = 0;
			found++;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&mhu->करोorbell_pending_lock, flags);

	अगर (!found) अणु
		/*
		 * We may have alपढ़ोy processed the करोorbell in the previous
		 * iteration अगर the पूर्णांकerrupt came right after we cleared it but
		 * beक्रमe we पढ़ो the stat रेजिस्टर.
		 */
		dev_dbg(dev, "Couldn't find the doorbell (%u) for the Tx interrupt interrupt\n",
			priv->ch_wn_idx);
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा mbox_chan *get_irq_chan_comb_rx(काष्ठा mhuv2 *mhu)
अणु
	काष्ठा mhuv2_mbox_chan_priv *priv;
	काष्ठा mbox_chan *chan;
	u32 stat;

	chan = get_irq_chan_comb(mhu, mhu->recv->chcomb_पूर्णांक_st);
	अगर (IS_ERR(chan))
		वापस chan;

	priv = chan->con_priv;
	अगर (!IS_PROTOCOL_DOORBELL(priv))
		वापस chan;

	/*
	 * In हाल of करोorbell mode, the first channel of the winकरोw is वापसed
	 * by the routine. Find the exact channel here.
	 */
	stat = पढ़ोl_relaxed(&mhu->recv->ch_wn[priv->ch_wn_idx].stat_masked);
	BUG_ON(!stat);

	वापस chan + __builtin_ctz(stat);
पूर्ण

अटल काष्ठा mbox_chan *get_irq_chan_stat_rx(काष्ठा mhuv2 *mhu)
अणु
	काष्ठा mbox_chan *chans = mhu->mbox.chans;
	काष्ठा mhuv2_mbox_chan_priv *priv;
	u32 stat;
	पूर्णांक i = 0;

	जबतक (i < mhu->mbox.num_chans) अणु
		priv = chans[i].con_priv;
		stat = पढ़ोl_relaxed(&mhu->recv->ch_wn[priv->ch_wn_idx].stat_masked);

		अगर (stat) अणु
			अगर (IS_PROTOCOL_DOORBELL(priv))
				i += __builtin_ctz(stat);
			वापस &chans[i];
		पूर्ण

		i += IS_PROTOCOL_DOORBELL(priv) ? MHUV2_STAT_BITS : 1;
	पूर्ण

	वापस ERR_PTR(-EIO);
पूर्ण

अटल काष्ठा mbox_chan *get_irq_chan_rx(काष्ठा mhuv2 *mhu)
अणु
	अगर (!mhu->minor)
		वापस get_irq_chan_stat_rx(mhu);

	वापस get_irq_chan_comb_rx(mhu);
पूर्ण

अटल irqवापस_t mhuv2_receiver_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा mhuv2 *mhu = arg;
	काष्ठा mbox_chan *chan = get_irq_chan_rx(mhu);
	काष्ठा device *dev = mhu->mbox.dev;
	काष्ठा mhuv2_mbox_chan_priv *priv;
	पूर्णांक ret = IRQ_NONE;
	व्योम *data;

	अगर (IS_ERR(chan)) अणु
		dev_warn(dev, "Failed to find channel for the rx interrupt\n");
		वापस IRQ_NONE;
	पूर्ण
	priv = chan->con_priv;

	/* Read and clear the data first */
	data = priv->ops->पढ़ो_data(mhu, chan);

	अगर (!chan->cl) अणु
		dev_warn(dev, "Received data on channel (%u) not currently attached to a mailbox client\n",
			 priv->ch_wn_idx);
	पूर्ण अन्यथा अगर (IS_ERR(data)) अणु
		dev_err(dev, "Failed to read data: %lu\n", PTR_ERR(data));
	पूर्ण अन्यथा अणु
		mbox_chan_received_data(chan, data);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (!IS_ERR(data))
		kमुक्त(data);

	वापस ret;
पूर्ण

/* Sender and receiver ops */
अटल bool mhuv2_sender_last_tx_करोne(काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2 *mhu = mhu_from_mbox(chan->mbox);
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;

	वापस priv->ops->last_tx_करोne(mhu, chan);
पूर्ण

अटल पूर्णांक mhuv2_sender_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा mhuv2 *mhu = mhu_from_mbox(chan->mbox);
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;

	अगर (!priv->ops->last_tx_करोne(mhu, chan))
		वापस -EBUSY;

	वापस priv->ops->send_data(mhu, chan, data);
पूर्ण

अटल पूर्णांक mhuv2_sender_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2 *mhu = mhu_from_mbox(chan->mbox);
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;

	अगर (priv->ops->tx_startup)
		priv->ops->tx_startup(mhu, chan);
	वापस 0;
पूर्ण

अटल व्योम mhuv2_sender_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2 *mhu = mhu_from_mbox(chan->mbox);
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;

	अगर (priv->ops->tx_shutकरोwn)
		priv->ops->tx_shutकरोwn(mhu, chan);
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops mhuv2_sender_ops = अणु
	.send_data = mhuv2_sender_send_data,
	.startup = mhuv2_sender_startup,
	.shutकरोwn = mhuv2_sender_shutकरोwn,
	.last_tx_करोne = mhuv2_sender_last_tx_करोne,
पूर्ण;

अटल पूर्णांक mhuv2_receiver_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2 *mhu = mhu_from_mbox(chan->mbox);
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;

	वापस priv->ops->rx_startup(mhu, chan);
पूर्ण

अटल व्योम mhuv2_receiver_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhuv2 *mhu = mhu_from_mbox(chan->mbox);
	काष्ठा mhuv2_mbox_chan_priv *priv = chan->con_priv;

	priv->ops->rx_shutकरोwn(mhu, chan);
पूर्ण

अटल पूर्णांक mhuv2_receiver_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	dev_err(chan->mbox->dev,
		"Trying to transmit on a receiver MHU frame\n");
	वापस -EIO;
पूर्ण

अटल bool mhuv2_receiver_last_tx_करोne(काष्ठा mbox_chan *chan)
अणु
	dev_err(chan->mbox->dev, "Trying to Tx poll on a receiver MHU frame\n");
	वापस true;
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops mhuv2_receiver_ops = अणु
	.send_data = mhuv2_receiver_send_data,
	.startup = mhuv2_receiver_startup,
	.shutकरोwn = mhuv2_receiver_shutकरोwn,
	.last_tx_करोne = mhuv2_receiver_last_tx_करोne,
पूर्ण;

अटल काष्ठा mbox_chan *mhuv2_mbox_of_xlate(काष्ठा mbox_controller *mbox,
					     स्थिर काष्ठा of_phandle_args *pa)
अणु
	काष्ठा mhuv2 *mhu = mhu_from_mbox(mbox);
	काष्ठा mbox_chan *chans = mbox->chans;
	पूर्णांक channel = 0, i, offset, करोorbell, protocol, winकरोws;

	अगर (pa->args_count != 2)
		वापस ERR_PTR(-EINVAL);

	offset = pa->args[0];
	करोorbell = pa->args[1];
	अगर (करोorbell >= MHUV2_STAT_BITS)
		जाओ out;

	क्रम (i = 0; i < mhu->length; i += 2) अणु
		protocol = mhu->protocols[i];
		winकरोws = mhu->protocols[i + 1];

		अगर (protocol == DOORBELL) अणु
			अगर (offset < winकरोws)
				वापस &chans[channel + MHUV2_STAT_BITS * offset + करोorbell];

			channel += MHUV2_STAT_BITS * winकरोws;
			offset -= winकरोws;
		पूर्ण अन्यथा अणु
			अगर (offset == 0) अणु
				अगर (करोorbell)
					जाओ out;

				वापस &chans[channel];
			पूर्ण

			channel++;
			offset--;
		पूर्ण
	पूर्ण

out:
	dev_err(mbox->dev, "Couldn't xlate to a valid channel (%d: %d)\n",
		pa->args[0], करोorbell);
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल पूर्णांक mhuv2_verअगरy_protocol(काष्ठा mhuv2 *mhu)
अणु
	काष्ठा device *dev = mhu->mbox.dev;
	पूर्णांक protocol, winकरोws, channels = 0, total_winकरोws = 0, i;

	क्रम (i = 0; i < mhu->length; i += 2) अणु
		protocol = mhu->protocols[i];
		winकरोws = mhu->protocols[i + 1];

		अगर (!winकरोws) अणु
			dev_err(dev, "Window size can't be zero (%d)\n", i);
			वापस -EINVAL;
		पूर्ण
		total_winकरोws += winकरोws;

		अगर (protocol == DOORBELL) अणु
			channels += MHUV2_STAT_BITS * winकरोws;
		पूर्ण अन्यथा अगर (protocol == DATA_TRANSFER) अणु
			channels++;
		पूर्ण अन्यथा अणु
			dev_err(dev, "Invalid protocol (%d) present in %s property at index %d\n",
				protocol, MHUV2_PROTOCOL_PROP, i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (total_winकरोws > mhu->winकरोws) अणु
		dev_err(dev, "Channel windows can't be more than what's implemented by the hardware ( %d: %d)\n",
			total_winकरोws, mhu->winकरोws);
		वापस -EINVAL;
	पूर्ण

	mhu->mbox.num_chans = channels;
	वापस 0;
पूर्ण

अटल पूर्णांक mhuv2_allocate_channels(काष्ठा mhuv2 *mhu)
अणु
	काष्ठा mbox_controller *mbox = &mhu->mbox;
	काष्ठा mhuv2_mbox_chan_priv *priv;
	काष्ठा device *dev = mbox->dev;
	काष्ठा mbox_chan *chans;
	पूर्णांक protocol, winकरोws = 0, next_winकरोw = 0, i, j, k;

	chans = devm_kसुस्मृति(dev, mbox->num_chans, माप(*chans), GFP_KERNEL);
	अगर (!chans)
		वापस -ENOMEM;

	mbox->chans = chans;

	क्रम (i = 0; i < mhu->length; i += 2) अणु
		next_winकरोw += winकरोws;

		protocol = mhu->protocols[i];
		winकरोws = mhu->protocols[i + 1];

		अगर (protocol == DATA_TRANSFER) अणु
			priv = devm_kदो_स्मृति(dev, माप(*priv), GFP_KERNEL);
			अगर (!priv)
				वापस -ENOMEM;

			priv->ch_wn_idx = next_winकरोw;
			priv->ops = &mhuv2_data_transfer_ops;
			priv->winकरोws = winकरोws;
			chans++->con_priv = priv;
			जारी;
		पूर्ण

		क्रम (j = 0; j < winकरोws; j++) अणु
			क्रम (k = 0; k < MHUV2_STAT_BITS; k++) अणु
				priv = devm_kदो_स्मृति(dev, माप(*priv), GFP_KERNEL);
				अगर (!priv)
					वापस -ENOMEM;

				priv->ch_wn_idx = next_winकरोw + j;
				priv->ops = &mhuv2_करोorbell_ops;
				priv->करोorbell = k;
				chans++->con_priv = priv;
			पूर्ण

			/*
			 * Permanently enable पूर्णांकerrupt as we can't
			 * control it per करोorbell.
			 */
			अगर (mhu->frame == SENDER_FRAME && mhu->minor)
				ग_लिखोl_relaxed(0x1, &mhu->send->ch_wn[priv->ch_wn_idx].पूर्णांक_en);
		पूर्ण
	पूर्ण

	/* Make sure we have initialized all channels */
	BUG_ON(chans - mbox->chans != mbox->num_chans);

	वापस 0;
पूर्ण

अटल पूर्णांक mhuv2_parse_channels(काष्ठा mhuv2 *mhu)
अणु
	काष्ठा device *dev = mhu->mbox.dev;
	स्थिर काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret, count;
	u32 *protocols;

	count = of_property_count_u32_elems(np, MHUV2_PROTOCOL_PROP);
	अगर (count <= 0 || count % 2) अणु
		dev_err(dev, "Invalid %s property (%d)\n", MHUV2_PROTOCOL_PROP,
			count);
		वापस -EINVAL;
	पूर्ण

	protocols = devm_kदो_स्मृति_array(dev, count, माप(*protocols), GFP_KERNEL);
	अगर (!protocols)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32_array(np, MHUV2_PROTOCOL_PROP, protocols, count);
	अगर (ret) अणु
		dev_err(dev, "Failed to read %s property: %d\n",
			MHUV2_PROTOCOL_PROP, ret);
		वापस ret;
	पूर्ण

	mhu->protocols = protocols;
	mhu->length = count;

	ret = mhuv2_verअगरy_protocol(mhu);
	अगर (ret)
		वापस ret;

	वापस mhuv2_allocate_channels(mhu);
पूर्ण

अटल पूर्णांक mhuv2_tx_init(काष्ठा amba_device *adev, काष्ठा mhuv2 *mhu,
			 व्योम __iomem *reg)
अणु
	काष्ठा device *dev = mhu->mbox.dev;
	पूर्णांक ret, i;

	mhu->frame = SENDER_FRAME;
	mhu->mbox.ops = &mhuv2_sender_ops;
	mhu->send = reg;

	mhu->winकरोws = पढ़ोl_relaxed_bitfield(&mhu->send->mhu_cfg, काष्ठा mhu_cfg_t, num_ch);
	mhu->minor = पढ़ोl_relaxed_bitfield(&mhu->send->aidr, काष्ठा aidr_t, arch_minor_rev);

	spin_lock_init(&mhu->करोorbell_pending_lock);

	/*
	 * For minor version 1 and क्रमward, tx पूर्णांकerrupt is provided by
	 * the controller.
	 */
	अगर (mhu->minor && adev->irq[0]) अणु
		ret = devm_request_thपढ़ोed_irq(dev, adev->irq[0], शून्य,
						mhuv2_sender_पूर्णांकerrupt,
						IRQF_ONESHOT, "mhuv2-tx", mhu);
		अगर (ret) अणु
			dev_err(dev, "Failed to request tx IRQ, fallback to polling mode: %d\n",
				ret);
		पूर्ण अन्यथा अणु
			mhu->mbox.txकरोne_irq = true;
			mhu->mbox.txकरोne_poll = false;
			mhu->irq = adev->irq[0];

			ग_लिखोl_relaxed_bitfield(1, &mhu->send->पूर्णांक_en, काष्ठा पूर्णांक_en_t, chcomb);

			/* Disable all channel पूर्णांकerrupts */
			क्रम (i = 0; i < mhu->winकरोws; i++)
				ग_लिखोl_relaxed(0x0, &mhu->send->ch_wn[i].पूर्णांक_en);

			जाओ out;
		पूर्ण
	पूर्ण

	mhu->mbox.txकरोne_irq = false;
	mhu->mbox.txकरोne_poll = true;
	mhu->mbox.txpoll_period = 1;

out:
	/* Wait क्रम receiver to be पढ़ोy */
	ग_लिखोl_relaxed(0x1, &mhu->send->access_request);
	जबतक (!पढ़ोl_relaxed(&mhu->send->access_पढ़ोy))
		जारी;

	वापस 0;
पूर्ण

अटल पूर्णांक mhuv2_rx_init(काष्ठा amba_device *adev, काष्ठा mhuv2 *mhu,
			 व्योम __iomem *reg)
अणु
	काष्ठा device *dev = mhu->mbox.dev;
	पूर्णांक ret, i;

	mhu->frame = RECEIVER_FRAME;
	mhu->mbox.ops = &mhuv2_receiver_ops;
	mhu->recv = reg;

	mhu->winकरोws = पढ़ोl_relaxed_bitfield(&mhu->recv->mhu_cfg, काष्ठा mhu_cfg_t, num_ch);
	mhu->minor = पढ़ोl_relaxed_bitfield(&mhu->recv->aidr, काष्ठा aidr_t, arch_minor_rev);

	mhu->irq = adev->irq[0];
	अगर (!mhu->irq) अणु
		dev_err(dev, "Missing receiver IRQ\n");
		वापस -EINVAL;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, mhu->irq, शून्य,
					mhuv2_receiver_पूर्णांकerrupt, IRQF_ONESHOT,
					"mhuv2-rx", mhu);
	अगर (ret) अणु
		dev_err(dev, "Failed to request rx IRQ\n");
		वापस ret;
	पूर्ण

	/* Mask all the channel winकरोws */
	क्रम (i = 0; i < mhu->winकरोws; i++)
		ग_लिखोl_relaxed(0xFFFFFFFF, &mhu->recv->ch_wn[i].mask_set);

	अगर (mhu->minor)
		ग_लिखोl_relaxed_bitfield(1, &mhu->recv->पूर्णांक_en, काष्ठा पूर्णांक_en_t, chcomb);

	वापस 0;
पूर्ण

अटल पूर्णांक mhuv2_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा device *dev = &adev->dev;
	स्थिर काष्ठा device_node *np = dev->of_node;
	काष्ठा mhuv2 *mhu;
	व्योम __iomem *reg;
	पूर्णांक ret = -EINVAL;

	reg = devm_of_iomap(dev, dev->of_node, 0, शून्य);
	अगर (!reg)
		वापस -ENOMEM;

	mhu = devm_kzalloc(dev, माप(*mhu), GFP_KERNEL);
	अगर (!mhu)
		वापस -ENOMEM;

	mhu->mbox.dev = dev;
	mhu->mbox.of_xlate = mhuv2_mbox_of_xlate;

	अगर (of_device_is_compatible(np, "arm,mhuv2-tx"))
		ret = mhuv2_tx_init(adev, mhu, reg);
	अन्यथा अगर (of_device_is_compatible(np, "arm,mhuv2-rx"))
		ret = mhuv2_rx_init(adev, mhu, reg);
	अन्यथा
		dev_err(dev, "Invalid compatible property\n");

	अगर (ret)
		वापस ret;

	/* Channel winकरोws can't be 0 */
	BUG_ON(!mhu->winकरोws);

	ret = mhuv2_parse_channels(mhu);
	अगर (ret)
		वापस ret;

	amba_set_drvdata(adev, mhu);

	ret = devm_mbox_controller_रेजिस्टर(dev, &mhu->mbox);
	अगर (ret)
		dev_err(dev, "failed to register ARM MHUv2 driver %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम mhuv2_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा mhuv2 *mhu = amba_get_drvdata(adev);

	अगर (mhu->frame == SENDER_FRAME)
		ग_लिखोl_relaxed(0x0, &mhu->send->access_request);
पूर्ण

अटल काष्ठा amba_id mhuv2_ids[] = अणु
	अणु
		/* 2.0 */
		.id = 0xbb0d1,
		.mask = 0xfffff,
	पूर्ण,
	अणु
		/* 2.1 */
		.id = 0xbb076,
		.mask = 0xfffff,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(amba, mhuv2_ids);

अटल काष्ठा amba_driver mhuv2_driver = अणु
	.drv = अणु
		.name	= "arm-mhuv2",
	पूर्ण,
	.id_table	= mhuv2_ids,
	.probe		= mhuv2_probe,
	.हटाओ		= mhuv2_हटाओ,
पूर्ण;
module_amba_driver(mhuv2_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ARM MHUv2 Driver");
MODULE_AUTHOR("Viresh Kumar <viresh.kumar@linaro.org>");
MODULE_AUTHOR("Tushar Khandelwal <tushar.khandelwal@arm.com>");
