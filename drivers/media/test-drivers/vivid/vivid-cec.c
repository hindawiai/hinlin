<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-cec.c - A Virtual Video Test Driver, cec emulation
 *
 * Copyright 2016 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <media/cec.h>

#समावेश "vivid-core.h"
#समावेश "vivid-cec.h"

#घोषणा CEC_TIM_START_BIT_TOTAL		4500
#घोषणा CEC_TIM_START_BIT_LOW		3700
#घोषणा CEC_TIM_START_BIT_HIGH		800
#घोषणा CEC_TIM_DATA_BIT_TOTAL		2400
#घोषणा CEC_TIM_DATA_BIT_0_LOW		1500
#घोषणा CEC_TIM_DATA_BIT_0_HIGH		900
#घोषणा CEC_TIM_DATA_BIT_1_LOW		600
#घोषणा CEC_TIM_DATA_BIT_1_HIGH		1800

व्योम vivid_cec_bus_मुक्त_work(काष्ठा vivid_dev *dev)
अणु
	spin_lock(&dev->cec_slock);
	जबतक (!list_empty(&dev->cec_work_list)) अणु
		काष्ठा vivid_cec_work *cw =
			list_first_entry(&dev->cec_work_list,
					 काष्ठा vivid_cec_work, list);

		spin_unlock(&dev->cec_slock);
		cancel_delayed_work_sync(&cw->work);
		spin_lock(&dev->cec_slock);
		list_del(&cw->list);
		cec_transmit_attempt_करोne(cw->adap, CEC_TX_STATUS_LOW_DRIVE);
		kमुक्त(cw);
	पूर्ण
	spin_unlock(&dev->cec_slock);
पूर्ण

अटल bool vivid_cec_find_dest_adap(काष्ठा vivid_dev *dev,
				     काष्ठा cec_adapter *adap, u8 dest)
अणु
	अचिन्हित पूर्णांक i;

	अगर (dest >= 0xf)
		वापस false;

	अगर (adap != dev->cec_rx_adap && dev->cec_rx_adap &&
	    dev->cec_rx_adap->is_configured &&
	    cec_has_log_addr(dev->cec_rx_adap, dest))
		वापस true;

	क्रम (i = 0; i < MAX_OUTPUTS && dev->cec_tx_adap[i]; i++) अणु
		अगर (adap == dev->cec_tx_adap[i])
			जारी;
		अगर (!dev->cec_tx_adap[i]->is_configured)
			जारी;
		अगर (cec_has_log_addr(dev->cec_tx_adap[i], dest))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम vivid_cec_pin_adap_events(काष्ठा cec_adapter *adap, kसमय_प्रकार ts,
				      स्थिर काष्ठा cec_msg *msg, bool nacked)
अणु
	अचिन्हित पूर्णांक len = nacked ? 1 : msg->len;
	अचिन्हित पूर्णांक i;
	bool bit;

	अगर (adap == शून्य)
		वापस;

	/*
	 * Suffix ULL on स्थिरant 10 makes the expression
	 * CEC_TIM_START_BIT_TOTAL + 10ULL * len * CEC_TIM_DATA_BIT_TOTAL
	 * to be evaluated using 64-bit अचिन्हित arithmetic (u64), which
	 * is what kसमय_sub_us expects as second argument.
	 */
	ts = kसमय_sub_us(ts, CEC_TIM_START_BIT_TOTAL +
			       10ULL * len * CEC_TIM_DATA_BIT_TOTAL);
	cec_queue_pin_cec_event(adap, false, false, ts);
	ts = kसमय_add_us(ts, CEC_TIM_START_BIT_LOW);
	cec_queue_pin_cec_event(adap, true, false, ts);
	ts = kसमय_add_us(ts, CEC_TIM_START_BIT_HIGH);

	क्रम (i = 0; i < 10 * len; i++) अणु
		चयन (i % 10) अणु
		हाल 0 ... 7:
			bit = msg->msg[i / 10] & (0x80 >> (i % 10));
			अवरोध;
		हाल 8: /* EOM */
			bit = i / 10 == msg->len - 1;
			अवरोध;
		हाल 9: /* ACK */
			bit = cec_msg_is_broadcast(msg) ^ nacked;
			अवरोध;
		पूर्ण
		cec_queue_pin_cec_event(adap, false, false, ts);
		अगर (bit)
			ts = kसमय_add_us(ts, CEC_TIM_DATA_BIT_1_LOW);
		अन्यथा
			ts = kसमय_add_us(ts, CEC_TIM_DATA_BIT_0_LOW);
		cec_queue_pin_cec_event(adap, true, false, ts);
		अगर (bit)
			ts = kसमय_add_us(ts, CEC_TIM_DATA_BIT_1_HIGH);
		अन्यथा
			ts = kसमय_add_us(ts, CEC_TIM_DATA_BIT_0_HIGH);
	पूर्ण
पूर्ण

अटल व्योम vivid_cec_pin_events(काष्ठा vivid_dev *dev,
				 स्थिर काष्ठा cec_msg *msg, bool nacked)
अणु
	kसमय_प्रकार ts = kसमय_get();
	अचिन्हित पूर्णांक i;

	vivid_cec_pin_adap_events(dev->cec_rx_adap, ts, msg, nacked);
	क्रम (i = 0; i < MAX_OUTPUTS; i++)
		vivid_cec_pin_adap_events(dev->cec_tx_adap[i], ts, msg, nacked);
पूर्ण

अटल व्योम vivid_cec_xfer_करोne_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vivid_cec_work *cw =
		container_of(work, काष्ठा vivid_cec_work, work.work);
	काष्ठा vivid_dev *dev = cw->dev;
	काष्ठा cec_adapter *adap = cw->adap;
	u8 dest = cec_msg_destination(&cw->msg);
	bool valid_dest;
	अचिन्हित पूर्णांक i;

	valid_dest = cec_msg_is_broadcast(&cw->msg);
	अगर (!valid_dest)
		valid_dest = vivid_cec_find_dest_adap(dev, adap, dest);

	cw->tx_status = valid_dest ? CEC_TX_STATUS_OK : CEC_TX_STATUS_NACK;
	spin_lock(&dev->cec_slock);
	dev->cec_xfer_समय_jअगरfies = 0;
	dev->cec_xfer_start_jअगरfies = 0;
	list_del(&cw->list);
	spin_unlock(&dev->cec_slock);
	vivid_cec_pin_events(dev, &cw->msg, !valid_dest);
	cec_transmit_attempt_करोne(cw->adap, cw->tx_status);

	/* Broadcast message */
	अगर (adap != dev->cec_rx_adap)
		cec_received_msg(dev->cec_rx_adap, &cw->msg);
	क्रम (i = 0; i < MAX_OUTPUTS && dev->cec_tx_adap[i]; i++)
		अगर (adap != dev->cec_tx_adap[i])
			cec_received_msg(dev->cec_tx_adap[i], &cw->msg);
	kमुक्त(cw);
पूर्ण

अटल व्योम vivid_cec_xfer_try_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vivid_cec_work *cw =
		container_of(work, काष्ठा vivid_cec_work, work.work);
	काष्ठा vivid_dev *dev = cw->dev;

	spin_lock(&dev->cec_slock);
	अगर (dev->cec_xfer_समय_jअगरfies) अणु
		list_del(&cw->list);
		spin_unlock(&dev->cec_slock);
		cec_transmit_attempt_करोne(cw->adap, CEC_TX_STATUS_ARB_LOST);
		kमुक्त(cw);
	पूर्ण अन्यथा अणु
		INIT_DELAYED_WORK(&cw->work, vivid_cec_xfer_करोne_worker);
		dev->cec_xfer_start_jअगरfies = jअगरfies;
		dev->cec_xfer_समय_jअगरfies = usecs_to_jअगरfies(cw->usecs);
		spin_unlock(&dev->cec_slock);
		schedule_delayed_work(&cw->work, dev->cec_xfer_समय_jअगरfies);
	पूर्ण
पूर्ण

अटल पूर्णांक vivid_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	adap->cec_pin_is_high = true;
	वापस 0;
पूर्ण

अटल पूर्णांक vivid_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 log_addr)
अणु
	वापस 0;
पूर्ण

/*
 * One data bit takes 2400 us, each byte needs 10 bits so that's 24000 us
 * per byte.
 */
#घोषणा USECS_PER_BYTE 24000

अटल पूर्णांक vivid_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				   u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा vivid_dev *dev = cec_get_drvdata(adap);
	काष्ठा vivid_cec_work *cw = kzalloc(माप(*cw), GFP_KERNEL);
	दीर्घ delta_jअगरfies = 0;

	अगर (cw == शून्य)
		वापस -ENOMEM;
	cw->dev = dev;
	cw->adap = adap;
	cw->usecs = CEC_FREE_TIME_TO_USEC(संकेत_मुक्त_समय) +
		    msg->len * USECS_PER_BYTE;
	cw->msg = *msg;

	spin_lock(&dev->cec_slock);
	list_add(&cw->list, &dev->cec_work_list);
	अगर (dev->cec_xfer_समय_jअगरfies == 0) अणु
		INIT_DELAYED_WORK(&cw->work, vivid_cec_xfer_करोne_worker);
		dev->cec_xfer_start_jअगरfies = jअगरfies;
		dev->cec_xfer_समय_jअगरfies = usecs_to_jअगरfies(cw->usecs);
		delta_jअगरfies = dev->cec_xfer_समय_jअगरfies;
	पूर्ण अन्यथा अणु
		INIT_DELAYED_WORK(&cw->work, vivid_cec_xfer_try_worker);
		delta_jअगरfies = dev->cec_xfer_start_jअगरfies +
			dev->cec_xfer_समय_jअगरfies - jअगरfies;
	पूर्ण
	spin_unlock(&dev->cec_slock);
	schedule_delayed_work(&cw->work, delta_jअगरfies < 0 ? 0 : delta_jअगरfies);
	वापस 0;
पूर्ण

अटल पूर्णांक vivid_received(काष्ठा cec_adapter *adap, काष्ठा cec_msg *msg)
अणु
	काष्ठा vivid_dev *dev = cec_get_drvdata(adap);
	काष्ठा cec_msg reply;
	u8 dest = cec_msg_destination(msg);
	u8 disp_ctl;
	अक्षर osd[14];

	अगर (cec_msg_is_broadcast(msg))
		dest = adap->log_addrs.log_addr[0];
	cec_msg_init(&reply, dest, cec_msg_initiator(msg));

	चयन (cec_msg_opcode(msg)) अणु
	हाल CEC_MSG_SET_OSD_STRING:
		अगर (!cec_is_sink(adap))
			वापस -ENOMSG;
		cec_ops_set_osd_string(msg, &disp_ctl, osd);
		चयन (disp_ctl) अणु
		हाल CEC_OP_DISP_CTL_DEFAULT:
			strscpy(dev->osd, osd, माप(dev->osd));
			dev->osd_jअगरfies = jअगरfies;
			अवरोध;
		हाल CEC_OP_DISP_CTL_UNTIL_CLEARED:
			strscpy(dev->osd, osd, माप(dev->osd));
			dev->osd_jअगरfies = 0;
			अवरोध;
		हाल CEC_OP_DISP_CTL_CLEAR:
			dev->osd[0] = 0;
			dev->osd_jअगरfies = 0;
			अवरोध;
		शेष:
			cec_msg_feature_पात(&reply, cec_msg_opcode(msg),
					      CEC_OP_ABORT_INVALID_OP);
			cec_transmit_msg(adap, &reply, false);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		वापस -ENOMSG;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops vivid_cec_adap_ops = अणु
	.adap_enable = vivid_cec_adap_enable,
	.adap_log_addr = vivid_cec_adap_log_addr,
	.adap_transmit = vivid_cec_adap_transmit,
	.received = vivid_received,
पूर्ण;

काष्ठा cec_adapter *vivid_cec_alloc_adap(काष्ठा vivid_dev *dev,
					 अचिन्हित पूर्णांक idx,
					 bool is_source)
अणु
	u32 caps = CEC_CAP_DEFAULTS | CEC_CAP_MONITOR_ALL | CEC_CAP_MONITOR_PIN;
	अक्षर name[32];

	snम_लिखो(name, माप(name), "vivid-%03d-vid-%s%d",
		 dev->inst, is_source ? "out" : "cap", idx);
	वापस cec_allocate_adapter(&vivid_cec_adap_ops, dev,
		name, caps, 1);
पूर्ण
