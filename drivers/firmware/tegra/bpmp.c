<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk/tegra.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/sched/घड़ी.h>

#समावेश <soc/tegra/bpmp.h>
#समावेश <soc/tegra/bpmp-abi.h>
#समावेश <soc/tegra/ivc.h>

#समावेश "bpmp-private.h"

#घोषणा MSG_ACK		BIT(0)
#घोषणा MSG_RING	BIT(1)
#घोषणा TAG_SZ		32

अटल अंतरभूत काष्ठा tegra_bpmp *
mbox_client_to_bpmp(काष्ठा mbox_client *client)
अणु
	वापस container_of(client, काष्ठा tegra_bpmp, mbox.client);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा tegra_bpmp_ops *
channel_to_ops(काष्ठा tegra_bpmp_channel *channel)
अणु
	काष्ठा tegra_bpmp *bpmp = channel->bpmp;

	वापस bpmp->soc->ops;
पूर्ण

काष्ठा tegra_bpmp *tegra_bpmp_get(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा tegra_bpmp *bpmp;
	काष्ठा device_node *np;

	np = of_parse_phandle(dev->of_node, "nvidia,bpmp", 0);
	अगर (!np)
		वापस ERR_PTR(-ENOENT);

	pdev = of_find_device_by_node(np);
	अगर (!pdev) अणु
		bpmp = ERR_PTR(-ENODEV);
		जाओ put;
	पूर्ण

	bpmp = platक्रमm_get_drvdata(pdev);
	अगर (!bpmp) अणु
		bpmp = ERR_PTR(-EPROBE_DEFER);
		put_device(&pdev->dev);
		जाओ put;
	पूर्ण

put:
	of_node_put(np);
	वापस bpmp;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_bpmp_get);

व्योम tegra_bpmp_put(काष्ठा tegra_bpmp *bpmp)
अणु
	अगर (bpmp)
		put_device(bpmp->dev);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_bpmp_put);

अटल पूर्णांक
tegra_bpmp_channel_get_thपढ़ो_index(काष्ठा tegra_bpmp_channel *channel)
अणु
	काष्ठा tegra_bpmp *bpmp = channel->bpmp;
	अचिन्हित पूर्णांक count;
	पूर्णांक index;

	count = bpmp->soc->channels.thपढ़ो.count;

	index = channel - channel->bpmp->thपढ़ोed_channels;
	अगर (index < 0 || index >= count)
		वापस -EINVAL;

	वापस index;
पूर्ण

अटल bool tegra_bpmp_message_valid(स्थिर काष्ठा tegra_bpmp_message *msg)
अणु
	वापस (msg->tx.size <= MSG_DATA_MIN_SZ) &&
	       (msg->rx.size <= MSG_DATA_MIN_SZ) &&
	       (msg->tx.size == 0 || msg->tx.data) &&
	       (msg->rx.size == 0 || msg->rx.data);
पूर्ण

अटल bool tegra_bpmp_is_response_पढ़ोy(काष्ठा tegra_bpmp_channel *channel)
अणु
	स्थिर काष्ठा tegra_bpmp_ops *ops = channel_to_ops(channel);

	वापस ops->is_response_पढ़ोy(channel);
पूर्ण

अटल bool tegra_bpmp_is_request_पढ़ोy(काष्ठा tegra_bpmp_channel *channel)
अणु
	स्थिर काष्ठा tegra_bpmp_ops *ops = channel_to_ops(channel);

	वापस ops->is_request_पढ़ोy(channel);
पूर्ण

अटल पूर्णांक tegra_bpmp_रुको_response(काष्ठा tegra_bpmp_channel *channel)
अणु
	अचिन्हित दीर्घ समयout = channel->bpmp->soc->channels.cpu_tx.समयout;
	kसमय_प्रकार end;

	end = kसमय_add_us(kसमय_get(), समयout);

	करो अणु
		अगर (tegra_bpmp_is_response_पढ़ोy(channel))
			वापस 0;
	पूर्ण जबतक (kसमय_beक्रमe(kसमय_get(), end));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक tegra_bpmp_ack_response(काष्ठा tegra_bpmp_channel *channel)
अणु
	स्थिर काष्ठा tegra_bpmp_ops *ops = channel_to_ops(channel);

	वापस ops->ack_response(channel);
पूर्ण

अटल पूर्णांक tegra_bpmp_ack_request(काष्ठा tegra_bpmp_channel *channel)
अणु
	स्थिर काष्ठा tegra_bpmp_ops *ops = channel_to_ops(channel);

	वापस ops->ack_request(channel);
पूर्ण

अटल bool
tegra_bpmp_is_request_channel_मुक्त(काष्ठा tegra_bpmp_channel *channel)
अणु
	स्थिर काष्ठा tegra_bpmp_ops *ops = channel_to_ops(channel);

	वापस ops->is_request_channel_मुक्त(channel);
पूर्ण

अटल bool
tegra_bpmp_is_response_channel_मुक्त(काष्ठा tegra_bpmp_channel *channel)
अणु
	स्थिर काष्ठा tegra_bpmp_ops *ops = channel_to_ops(channel);

	वापस ops->is_response_channel_मुक्त(channel);
पूर्ण

अटल पूर्णांक
tegra_bpmp_रुको_request_channel_मुक्त(काष्ठा tegra_bpmp_channel *channel)
अणु
	अचिन्हित दीर्घ समयout = channel->bpmp->soc->channels.cpu_tx.समयout;
	kसमय_प्रकार start, now;

	start = ns_to_kसमय(local_घड़ी());

	करो अणु
		अगर (tegra_bpmp_is_request_channel_मुक्त(channel))
			वापस 0;

		now = ns_to_kसमय(local_घड़ी());
	पूर्ण जबतक (kसमय_us_delta(now, start) < समयout);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक tegra_bpmp_post_request(काष्ठा tegra_bpmp_channel *channel)
अणु
	स्थिर काष्ठा tegra_bpmp_ops *ops = channel_to_ops(channel);

	वापस ops->post_request(channel);
पूर्ण

अटल पूर्णांक tegra_bpmp_post_response(काष्ठा tegra_bpmp_channel *channel)
अणु
	स्थिर काष्ठा tegra_bpmp_ops *ops = channel_to_ops(channel);

	वापस ops->post_response(channel);
पूर्ण

अटल पूर्णांक tegra_bpmp_ring_करोorbell(काष्ठा tegra_bpmp *bpmp)
अणु
	वापस bpmp->soc->ops->ring_करोorbell(bpmp);
पूर्ण

अटल sमाप_प्रकार __tegra_bpmp_channel_पढ़ो(काष्ठा tegra_bpmp_channel *channel,
					 व्योम *data, माप_प्रकार size, पूर्णांक *ret)
अणु
	पूर्णांक err;

	अगर (data && size > 0)
		स_नकल(data, channel->ib->data, size);

	err = tegra_bpmp_ack_response(channel);
	अगर (err < 0)
		वापस err;

	*ret = channel->ib->code;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार tegra_bpmp_channel_पढ़ो(काष्ठा tegra_bpmp_channel *channel,
				       व्योम *data, माप_प्रकार size, पूर्णांक *ret)
अणु
	काष्ठा tegra_bpmp *bpmp = channel->bpmp;
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार err;
	पूर्णांक index;

	index = tegra_bpmp_channel_get_thपढ़ो_index(channel);
	अगर (index < 0) अणु
		err = index;
		जाओ unlock;
	पूर्ण

	spin_lock_irqsave(&bpmp->lock, flags);
	err = __tegra_bpmp_channel_पढ़ो(channel, data, size, ret);
	clear_bit(index, bpmp->thपढ़ोed.allocated);
	spin_unlock_irqrestore(&bpmp->lock, flags);

unlock:
	up(&bpmp->thपढ़ोed.lock);

	वापस err;
पूर्ण

अटल sमाप_प्रकार __tegra_bpmp_channel_ग_लिखो(काष्ठा tegra_bpmp_channel *channel,
					  अचिन्हित पूर्णांक mrq, अचिन्हित दीर्घ flags,
					  स्थिर व्योम *data, माप_प्रकार size)
अणु
	channel->ob->code = mrq;
	channel->ob->flags = flags;

	अगर (data && size > 0)
		स_नकल(channel->ob->data, data, size);

	वापस tegra_bpmp_post_request(channel);
पूर्ण

अटल काष्ठा tegra_bpmp_channel *
tegra_bpmp_ग_लिखो_thपढ़ोed(काष्ठा tegra_bpmp *bpmp, अचिन्हित पूर्णांक mrq,
			  स्थिर व्योम *data, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ समयout = bpmp->soc->channels.thपढ़ो.समयout;
	अचिन्हित पूर्णांक count = bpmp->soc->channels.thपढ़ो.count;
	काष्ठा tegra_bpmp_channel *channel;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक index;
	पूर्णांक err;

	err = करोwn_समयout(&bpmp->thपढ़ोed.lock, usecs_to_jअगरfies(समयout));
	अगर (err < 0)
		वापस ERR_PTR(err);

	spin_lock_irqsave(&bpmp->lock, flags);

	index = find_first_zero_bit(bpmp->thपढ़ोed.allocated, count);
	अगर (index == count) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण

	channel = &bpmp->thपढ़ोed_channels[index];

	अगर (!tegra_bpmp_is_request_channel_मुक्त(channel)) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण

	set_bit(index, bpmp->thपढ़ोed.allocated);

	err = __tegra_bpmp_channel_ग_लिखो(channel, mrq, MSG_ACK | MSG_RING,
					 data, size);
	अगर (err < 0)
		जाओ clear_allocated;

	set_bit(index, bpmp->thपढ़ोed.busy);

	spin_unlock_irqrestore(&bpmp->lock, flags);
	वापस channel;

clear_allocated:
	clear_bit(index, bpmp->thपढ़ोed.allocated);
unlock:
	spin_unlock_irqrestore(&bpmp->lock, flags);
	up(&bpmp->thपढ़ोed.lock);

	वापस ERR_PTR(err);
पूर्ण

अटल sमाप_प्रकार tegra_bpmp_channel_ग_लिखो(काष्ठा tegra_bpmp_channel *channel,
					अचिन्हित पूर्णांक mrq, अचिन्हित दीर्घ flags,
					स्थिर व्योम *data, माप_प्रकार size)
अणु
	पूर्णांक err;

	err = tegra_bpmp_रुको_request_channel_मुक्त(channel);
	अगर (err < 0)
		वापस err;

	वापस __tegra_bpmp_channel_ग_लिखो(channel, mrq, flags, data, size);
पूर्ण

पूर्णांक tegra_bpmp_transfer_atomic(काष्ठा tegra_bpmp *bpmp,
			       काष्ठा tegra_bpmp_message *msg)
अणु
	काष्ठा tegra_bpmp_channel *channel;
	पूर्णांक err;

	अगर (WARN_ON(!irqs_disabled()))
		वापस -EPERM;

	अगर (!tegra_bpmp_message_valid(msg))
		वापस -EINVAL;

	channel = bpmp->tx_channel;

	spin_lock(&bpmp->atomic_tx_lock);

	err = tegra_bpmp_channel_ग_लिखो(channel, msg->mrq, MSG_ACK,
				       msg->tx.data, msg->tx.size);
	अगर (err < 0) अणु
		spin_unlock(&bpmp->atomic_tx_lock);
		वापस err;
	पूर्ण

	spin_unlock(&bpmp->atomic_tx_lock);

	err = tegra_bpmp_ring_करोorbell(bpmp);
	अगर (err < 0)
		वापस err;

	err = tegra_bpmp_रुको_response(channel);
	अगर (err < 0)
		वापस err;

	वापस __tegra_bpmp_channel_पढ़ो(channel, msg->rx.data, msg->rx.size,
					 &msg->rx.ret);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_bpmp_transfer_atomic);

पूर्णांक tegra_bpmp_transfer(काष्ठा tegra_bpmp *bpmp,
			काष्ठा tegra_bpmp_message *msg)
अणु
	काष्ठा tegra_bpmp_channel *channel;
	अचिन्हित दीर्घ समयout;
	पूर्णांक err;

	अगर (WARN_ON(irqs_disabled()))
		वापस -EPERM;

	अगर (!tegra_bpmp_message_valid(msg))
		वापस -EINVAL;

	channel = tegra_bpmp_ग_लिखो_thपढ़ोed(bpmp, msg->mrq, msg->tx.data,
					    msg->tx.size);
	अगर (IS_ERR(channel))
		वापस PTR_ERR(channel);

	err = tegra_bpmp_ring_करोorbell(bpmp);
	अगर (err < 0)
		वापस err;

	समयout = usecs_to_jअगरfies(bpmp->soc->channels.thपढ़ो.समयout);

	err = रुको_क्रम_completion_समयout(&channel->completion, समयout);
	अगर (err == 0)
		वापस -ETIMEDOUT;

	वापस tegra_bpmp_channel_पढ़ो(channel, msg->rx.data, msg->rx.size,
				       &msg->rx.ret);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_bpmp_transfer);

अटल काष्ठा tegra_bpmp_mrq *tegra_bpmp_find_mrq(काष्ठा tegra_bpmp *bpmp,
						  अचिन्हित पूर्णांक mrq)
अणु
	काष्ठा tegra_bpmp_mrq *entry;

	list_क्रम_each_entry(entry, &bpmp->mrqs, list)
		अगर (entry->mrq == mrq)
			वापस entry;

	वापस शून्य;
पूर्ण

व्योम tegra_bpmp_mrq_वापस(काष्ठा tegra_bpmp_channel *channel, पूर्णांक code,
			   स्थिर व्योम *data, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ flags = channel->ib->flags;
	काष्ठा tegra_bpmp *bpmp = channel->bpmp;
	पूर्णांक err;

	अगर (WARN_ON(size > MSG_DATA_MIN_SZ))
		वापस;

	err = tegra_bpmp_ack_request(channel);
	अगर (WARN_ON(err < 0))
		वापस;

	अगर ((flags & MSG_ACK) == 0)
		वापस;

	अगर (WARN_ON(!tegra_bpmp_is_response_channel_मुक्त(channel)))
		वापस;

	channel->ob->code = code;

	अगर (data && size > 0)
		स_नकल(channel->ob->data, data, size);

	err = tegra_bpmp_post_response(channel);
	अगर (WARN_ON(err < 0))
		वापस;

	अगर (flags & MSG_RING) अणु
		err = tegra_bpmp_ring_करोorbell(bpmp);
		अगर (WARN_ON(err < 0))
			वापस;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tegra_bpmp_mrq_वापस);

अटल व्योम tegra_bpmp_handle_mrq(काष्ठा tegra_bpmp *bpmp,
				  अचिन्हित पूर्णांक mrq,
				  काष्ठा tegra_bpmp_channel *channel)
अणु
	काष्ठा tegra_bpmp_mrq *entry;
	u32 zero = 0;

	spin_lock(&bpmp->lock);

	entry = tegra_bpmp_find_mrq(bpmp, mrq);
	अगर (!entry) अणु
		spin_unlock(&bpmp->lock);
		tegra_bpmp_mrq_वापस(channel, -EINVAL, &zero, माप(zero));
		वापस;
	पूर्ण

	entry->handler(mrq, channel, entry->data);

	spin_unlock(&bpmp->lock);
पूर्ण

पूर्णांक tegra_bpmp_request_mrq(काष्ठा tegra_bpmp *bpmp, अचिन्हित पूर्णांक mrq,
			   tegra_bpmp_mrq_handler_t handler, व्योम *data)
अणु
	काष्ठा tegra_bpmp_mrq *entry;
	अचिन्हित दीर्घ flags;

	अगर (!handler)
		वापस -EINVAL;

	entry = devm_kzalloc(bpmp->dev, माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	spin_lock_irqsave(&bpmp->lock, flags);

	entry->mrq = mrq;
	entry->handler = handler;
	entry->data = data;
	list_add(&entry->list, &bpmp->mrqs);

	spin_unlock_irqrestore(&bpmp->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_bpmp_request_mrq);

व्योम tegra_bpmp_मुक्त_mrq(काष्ठा tegra_bpmp *bpmp, अचिन्हित पूर्णांक mrq, व्योम *data)
अणु
	काष्ठा tegra_bpmp_mrq *entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bpmp->lock, flags);

	entry = tegra_bpmp_find_mrq(bpmp, mrq);
	अगर (!entry)
		जाओ unlock;

	list_del(&entry->list);
	devm_kमुक्त(bpmp->dev, entry);

unlock:
	spin_unlock_irqrestore(&bpmp->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_bpmp_मुक्त_mrq);

bool tegra_bpmp_mrq_is_supported(काष्ठा tegra_bpmp *bpmp, अचिन्हित पूर्णांक mrq)
अणु
	काष्ठा mrq_query_abi_request req = अणु .mrq = cpu_to_le32(mrq) पूर्ण;
	काष्ठा mrq_query_abi_response resp;
	काष्ठा tegra_bpmp_message msg = अणु
		.mrq = MRQ_QUERY_ABI,
		.tx = अणु
			.data = &req,
			.size = माप(req),
		पूर्ण,
		.rx = अणु
			.data = &resp,
			.size = माप(resp),
		पूर्ण,
	पूर्ण;
	पूर्णांक err;

	err = tegra_bpmp_transfer(bpmp, &msg);
	अगर (err || msg.rx.ret)
		वापस false;

	वापस resp.status == 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_bpmp_mrq_is_supported);

अटल व्योम tegra_bpmp_mrq_handle_ping(अचिन्हित पूर्णांक mrq,
				       काष्ठा tegra_bpmp_channel *channel,
				       व्योम *data)
अणु
	काष्ठा mrq_ping_request *request;
	काष्ठा mrq_ping_response response;

	request = (काष्ठा mrq_ping_request *)channel->ib->data;

	स_रखो(&response, 0, माप(response));
	response.reply = request->challenge << 1;

	tegra_bpmp_mrq_वापस(channel, 0, &response, माप(response));
पूर्ण

अटल पूर्णांक tegra_bpmp_ping(काष्ठा tegra_bpmp *bpmp)
अणु
	काष्ठा mrq_ping_response response;
	काष्ठा mrq_ping_request request;
	काष्ठा tegra_bpmp_message msg;
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार start, end;
	पूर्णांक err;

	स_रखो(&request, 0, माप(request));
	request.challenge = 1;

	स_रखो(&response, 0, माप(response));

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_PING;
	msg.tx.data = &request;
	msg.tx.size = माप(request);
	msg.rx.data = &response;
	msg.rx.size = माप(response);

	local_irq_save(flags);
	start = kसमय_get();
	err = tegra_bpmp_transfer_atomic(bpmp, &msg);
	end = kसमय_get();
	local_irq_restore(flags);

	अगर (!err)
		dev_dbg(bpmp->dev,
			"ping ok: challenge: %u, response: %u, time: %lld\n",
			request.challenge, response.reply,
			kसमय_प्रकारo_us(kसमय_sub(end, start)));

	वापस err;
पूर्ण

/* deprecated version of tag query */
अटल पूर्णांक tegra_bpmp_get_firmware_tag_old(काष्ठा tegra_bpmp *bpmp, अक्षर *tag,
					   माप_प्रकार size)
अणु
	काष्ठा mrq_query_tag_request request;
	काष्ठा tegra_bpmp_message msg;
	अचिन्हित दीर्घ flags;
	dma_addr_t phys;
	व्योम *virt;
	पूर्णांक err;

	अगर (size != TAG_SZ)
		वापस -EINVAL;

	virt = dma_alloc_coherent(bpmp->dev, TAG_SZ, &phys,
				  GFP_KERNEL | GFP_DMA32);
	अगर (!virt)
		वापस -ENOMEM;

	स_रखो(&request, 0, माप(request));
	request.addr = phys;

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_QUERY_TAG;
	msg.tx.data = &request;
	msg.tx.size = माप(request);

	local_irq_save(flags);
	err = tegra_bpmp_transfer_atomic(bpmp, &msg);
	local_irq_restore(flags);

	अगर (err == 0)
		स_नकल(tag, virt, TAG_SZ);

	dma_मुक्त_coherent(bpmp->dev, TAG_SZ, virt, phys);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_bpmp_get_firmware_tag(काष्ठा tegra_bpmp *bpmp, अक्षर *tag,
				       माप_प्रकार size)
अणु
	अगर (tegra_bpmp_mrq_is_supported(bpmp, MRQ_QUERY_FW_TAG)) अणु
		काष्ठा mrq_query_fw_tag_response resp;
		काष्ठा tegra_bpmp_message msg = अणु
			.mrq = MRQ_QUERY_FW_TAG,
			.rx = अणु
				.data = &resp,
				.size = माप(resp),
			पूर्ण,
		पूर्ण;
		पूर्णांक err;

		अगर (size != माप(resp.tag))
			वापस -EINVAL;

		err = tegra_bpmp_transfer(bpmp, &msg);

		अगर (err)
			वापस err;
		अगर (msg.rx.ret < 0)
			वापस -EINVAL;

		स_नकल(tag, resp.tag, माप(resp.tag));
		वापस 0;
	पूर्ण

	वापस tegra_bpmp_get_firmware_tag_old(bpmp, tag, size);
पूर्ण

अटल व्योम tegra_bpmp_channel_संकेत(काष्ठा tegra_bpmp_channel *channel)
अणु
	अचिन्हित दीर्घ flags = channel->ob->flags;

	अगर ((flags & MSG_RING) == 0)
		वापस;

	complete(&channel->completion);
पूर्ण

व्योम tegra_bpmp_handle_rx(काष्ठा tegra_bpmp *bpmp)
अणु
	काष्ठा tegra_bpmp_channel *channel;
	अचिन्हित पूर्णांक i, count;
	अचिन्हित दीर्घ *busy;

	channel = bpmp->rx_channel;
	count = bpmp->soc->channels.thपढ़ो.count;
	busy = bpmp->thपढ़ोed.busy;

	अगर (tegra_bpmp_is_request_पढ़ोy(channel))
		tegra_bpmp_handle_mrq(bpmp, channel->ib->code, channel);

	spin_lock(&bpmp->lock);

	क्रम_each_set_bit(i, busy, count) अणु
		काष्ठा tegra_bpmp_channel *channel;

		channel = &bpmp->thपढ़ोed_channels[i];

		अगर (tegra_bpmp_is_response_पढ़ोy(channel)) अणु
			tegra_bpmp_channel_संकेत(channel);
			clear_bit(i, busy);
		पूर्ण
	पूर्ण

	spin_unlock(&bpmp->lock);
पूर्ण

अटल पूर्णांक tegra_bpmp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_bpmp *bpmp;
	अक्षर tag[TAG_SZ];
	माप_प्रकार size;
	पूर्णांक err;

	bpmp = devm_kzalloc(&pdev->dev, माप(*bpmp), GFP_KERNEL);
	अगर (!bpmp)
		वापस -ENOMEM;

	bpmp->soc = of_device_get_match_data(&pdev->dev);
	bpmp->dev = &pdev->dev;

	INIT_LIST_HEAD(&bpmp->mrqs);
	spin_lock_init(&bpmp->lock);

	bpmp->thपढ़ोed.count = bpmp->soc->channels.thपढ़ो.count;
	sema_init(&bpmp->thपढ़ोed.lock, bpmp->thपढ़ोed.count);

	size = BITS_TO_LONGS(bpmp->thपढ़ोed.count) * माप(दीर्घ);

	bpmp->thपढ़ोed.allocated = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (!bpmp->thपढ़ोed.allocated)
		वापस -ENOMEM;

	bpmp->thपढ़ोed.busy = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (!bpmp->thपढ़ोed.busy)
		वापस -ENOMEM;

	spin_lock_init(&bpmp->atomic_tx_lock);
	bpmp->tx_channel = devm_kzalloc(&pdev->dev, माप(*bpmp->tx_channel),
					GFP_KERNEL);
	अगर (!bpmp->tx_channel)
		वापस -ENOMEM;

	bpmp->rx_channel = devm_kzalloc(&pdev->dev, माप(*bpmp->rx_channel),
	                                GFP_KERNEL);
	अगर (!bpmp->rx_channel)
		वापस -ENOMEM;

	bpmp->thपढ़ोed_channels = devm_kसुस्मृति(&pdev->dev, bpmp->thपढ़ोed.count,
					       माप(*bpmp->thपढ़ोed_channels),
					       GFP_KERNEL);
	अगर (!bpmp->thपढ़ोed_channels)
		वापस -ENOMEM;

	err = bpmp->soc->ops->init(bpmp);
	अगर (err < 0)
		वापस err;

	err = tegra_bpmp_request_mrq(bpmp, MRQ_PING,
				     tegra_bpmp_mrq_handle_ping, bpmp);
	अगर (err < 0)
		जाओ deinit;

	err = tegra_bpmp_ping(bpmp);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to ping BPMP: %d\n", err);
		जाओ मुक्त_mrq;
	पूर्ण

	err = tegra_bpmp_get_firmware_tag(bpmp, tag, माप(tag));
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to get firmware tag: %d\n", err);
		जाओ मुक्त_mrq;
	पूर्ण

	dev_info(&pdev->dev, "firmware: %.*s\n", (पूर्णांक)माप(tag), tag);

	platक्रमm_set_drvdata(pdev, bpmp);

	err = of_platक्रमm_शेष_populate(pdev->dev.of_node, शून्य, &pdev->dev);
	अगर (err < 0)
		जाओ मुक्त_mrq;

	अगर (of_find_property(pdev->dev.of_node, "#clock-cells", शून्य)) अणु
		err = tegra_bpmp_init_घड़ीs(bpmp);
		अगर (err < 0)
			जाओ मुक्त_mrq;
	पूर्ण

	अगर (of_find_property(pdev->dev.of_node, "#reset-cells", शून्य)) अणु
		err = tegra_bpmp_init_resets(bpmp);
		अगर (err < 0)
			जाओ मुक्त_mrq;
	पूर्ण

	अगर (of_find_property(pdev->dev.of_node, "#power-domain-cells", शून्य)) अणु
		err = tegra_bpmp_init_घातergates(bpmp);
		अगर (err < 0)
			जाओ मुक्त_mrq;
	पूर्ण

	err = tegra_bpmp_init_debugfs(bpmp);
	अगर (err < 0)
		dev_err(&pdev->dev, "debugfs initialization failed: %d\n", err);

	वापस 0;

मुक्त_mrq:
	tegra_bpmp_मुक्त_mrq(bpmp, MRQ_PING, bpmp);
deinit:
	अगर (bpmp->soc->ops->deinit)
		bpmp->soc->ops->deinit(bpmp);

	वापस err;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_bpmp_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_bpmp *bpmp = dev_get_drvdata(dev);

	अगर (bpmp->soc->ops->resume)
		वापस bpmp->soc->ops->resume(bpmp);
	अन्यथा
		वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_bpmp_pm_ops = अणु
	.resume_noirq = tegra_bpmp_resume,
पूर्ण;

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_186_SOC) || \
    IS_ENABLED(CONFIG_ARCH_TEGRA_194_SOC)
अटल स्थिर काष्ठा tegra_bpmp_soc tegra186_soc = अणु
	.channels = अणु
		.cpu_tx = अणु
			.offset = 3,
			.समयout = 60 * USEC_PER_SEC,
		पूर्ण,
		.thपढ़ो = अणु
			.offset = 0,
			.count = 3,
			.समयout = 600 * USEC_PER_SEC,
		पूर्ण,
		.cpu_rx = अणु
			.offset = 13,
			.समयout = 0,
		पूर्ण,
	पूर्ण,
	.ops = &tegra186_bpmp_ops,
	.num_resets = 193,
पूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_210_SOC)
अटल स्थिर काष्ठा tegra_bpmp_soc tegra210_soc = अणु
	.channels = अणु
		.cpu_tx = अणु
			.offset = 0,
			.count = 1,
			.समयout = 60 * USEC_PER_SEC,
		पूर्ण,
		.thपढ़ो = अणु
			.offset = 4,
			.count = 1,
			.समयout = 600 * USEC_PER_SEC,
		पूर्ण,
		.cpu_rx = अणु
			.offset = 8,
			.count = 1,
			.समयout = 0,
		पूर्ण,
	पूर्ण,
	.ops = &tegra210_bpmp_ops,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id tegra_bpmp_match[] = अणु
#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_186_SOC) || \
    IS_ENABLED(CONFIG_ARCH_TEGRA_194_SOC) || \
    IS_ENABLED(CONFIG_ARCH_TEGRA_234_SOC)
	अणु .compatible = "nvidia,tegra186-bpmp", .data = &tegra186_soc पूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_210_SOC)
	अणु .compatible = "nvidia,tegra210-bpmp", .data = &tegra210_soc पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_bpmp_driver = अणु
	.driver = अणु
		.name = "tegra-bpmp",
		.of_match_table = tegra_bpmp_match,
		.pm = &tegra_bpmp_pm_ops,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = tegra_bpmp_probe,
पूर्ण;
builtin_platक्रमm_driver(tegra_bpmp_driver);
