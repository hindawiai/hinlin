<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2019 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश "mt76.h"

काष्ठा sk_buff *
mt76_mcu_msg_alloc(काष्ठा mt76_dev *dev, स्थिर व्योम *data,
		   पूर्णांक data_len)
अणु
	स्थिर काष्ठा mt76_mcu_ops *ops = dev->mcu_ops;
	पूर्णांक length = ops->headroom + data_len + ops->tailroom;
	काष्ठा sk_buff *skb;

	skb = alloc_skb(length, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	स_रखो(skb->head, 0, length);
	skb_reserve(skb, ops->headroom);

	अगर (data && data_len)
		skb_put_data(skb, data, data_len);

	वापस skb;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_mcu_msg_alloc);

काष्ठा sk_buff *mt76_mcu_get_response(काष्ठा mt76_dev *dev,
				      अचिन्हित दीर्घ expires)
अणु
	अचिन्हित दीर्घ समयout;

	अगर (!समय_is_after_jअगरfies(expires))
		वापस शून्य;

	समयout = expires - jअगरfies;
	रुको_event_समयout(dev->mcu.रुको,
			   (!skb_queue_empty(&dev->mcu.res_q) ||
			    test_bit(MT76_MCU_RESET, &dev->phy.state)),
			   समयout);
	वापस skb_dequeue(&dev->mcu.res_q);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_mcu_get_response);

व्योम mt76_mcu_rx_event(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb)
अणु
	skb_queue_tail(&dev->mcu.res_q, skb);
	wake_up(&dev->mcu.रुको);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_mcu_rx_event);

पूर्णांक mt76_mcu_send_and_get_msg(काष्ठा mt76_dev *dev, पूर्णांक cmd, स्थिर व्योम *data,
			      पूर्णांक len, bool रुको_resp, काष्ठा sk_buff **ret_skb)
अणु
	काष्ठा sk_buff *skb;

	अगर (dev->mcu_ops->mcu_send_msg)
		वापस dev->mcu_ops->mcu_send_msg(dev, cmd, data, len, रुको_resp);

	skb = mt76_mcu_msg_alloc(dev, data, len);
	अगर (!skb)
		वापस -ENOMEM;

	वापस mt76_mcu_skb_send_and_get_msg(dev, skb, cmd, रुको_resp, ret_skb);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_mcu_send_and_get_msg);

पूर्णांक mt76_mcu_skb_send_and_get_msg(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
				  पूर्णांक cmd, bool रुको_resp,
				  काष्ठा sk_buff **ret_skb)
अणु
	अचिन्हित दीर्घ expires;
	पूर्णांक ret, seq;

	अगर (ret_skb)
		*ret_skb = शून्य;

	mutex_lock(&dev->mcu.mutex);

	ret = dev->mcu_ops->mcu_skb_send_msg(dev, skb, cmd, &seq);
	अगर (ret < 0)
		जाओ out;

	अगर (!रुको_resp) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	expires = jअगरfies + dev->mcu.समयout;

	करो अणु
		skb = mt76_mcu_get_response(dev, expires);
		ret = dev->mcu_ops->mcu_parse_response(dev, cmd, skb, seq);
		अगर (!ret && ret_skb)
			*ret_skb = skb;
		अन्यथा
			dev_kमुक्त_skb(skb);
	पूर्ण जबतक (ret == -EAGAIN);

out:
	mutex_unlock(&dev->mcu.mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_mcu_skb_send_and_get_msg);

पूर्णांक mt76_mcu_send_firmware(काष्ठा mt76_dev *dev, पूर्णांक cmd, स्थिर व्योम *data,
			   पूर्णांक len)
अणु
	पूर्णांक err, cur_len;

	जबतक (len > 0) अणु
		cur_len = min_t(पूर्णांक, 4096 - dev->mcu_ops->headroom, len);

		err = mt76_mcu_send_msg(dev, cmd, data, cur_len, false);
		अगर (err)
			वापस err;

		data += cur_len;
		len -= cur_len;

		अगर (dev->queue_ops->tx_cleanup)
			dev->queue_ops->tx_cleanup(dev,
						   dev->q_mcu[MT_MCUQ_FWDL],
						   false);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_mcu_send_firmware);
