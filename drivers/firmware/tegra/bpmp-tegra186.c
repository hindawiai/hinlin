<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, NVIDIA CORPORATION.
 */

#समावेश <linux/genभाग.स>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <soc/tegra/bpmp.h>
#समावेश <soc/tegra/bpmp-abi.h>
#समावेश <soc/tegra/ivc.h>

#समावेश "bpmp-private.h"

काष्ठा tegra186_bpmp अणु
	काष्ठा tegra_bpmp *parent;

	काष्ठा अणु
		काष्ठा gen_pool *pool;
		dma_addr_t phys;
		व्योम *virt;
	पूर्ण tx, rx;

	काष्ठा अणु
		काष्ठा mbox_client client;
		काष्ठा mbox_chan *channel;
	पूर्ण mbox;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_bpmp *
mbox_client_to_bpmp(काष्ठा mbox_client *client)
अणु
	काष्ठा tegra186_bpmp *priv;

	priv = container_of(client, काष्ठा tegra186_bpmp, mbox.client);

	वापस priv->parent;
पूर्ण

अटल bool tegra186_bpmp_is_message_पढ़ोy(काष्ठा tegra_bpmp_channel *channel)
अणु
	व्योम *frame;

	frame = tegra_ivc_पढ़ो_get_next_frame(channel->ivc);
	अगर (IS_ERR(frame)) अणु
		channel->ib = शून्य;
		वापस false;
	पूर्ण

	channel->ib = frame;

	वापस true;
पूर्ण

अटल bool tegra186_bpmp_is_channel_मुक्त(काष्ठा tegra_bpmp_channel *channel)
अणु
	व्योम *frame;

	frame = tegra_ivc_ग_लिखो_get_next_frame(channel->ivc);
	अगर (IS_ERR(frame)) अणु
		channel->ob = शून्य;
		वापस false;
	पूर्ण

	channel->ob = frame;

	वापस true;
पूर्ण

अटल पूर्णांक tegra186_bpmp_ack_message(काष्ठा tegra_bpmp_channel *channel)
अणु
	वापस tegra_ivc_पढ़ो_advance(channel->ivc);
पूर्ण

अटल पूर्णांक tegra186_bpmp_post_message(काष्ठा tegra_bpmp_channel *channel)
अणु
	वापस tegra_ivc_ग_लिखो_advance(channel->ivc);
पूर्ण

अटल पूर्णांक tegra186_bpmp_ring_करोorbell(काष्ठा tegra_bpmp *bpmp)
अणु
	काष्ठा tegra186_bpmp *priv = bpmp->priv;
	पूर्णांक err;

	err = mbox_send_message(priv->mbox.channel, शून्य);
	अगर (err < 0)
		वापस err;

	mbox_client_txकरोne(priv->mbox.channel, 0);

	वापस 0;
पूर्ण

अटल व्योम tegra186_bpmp_ivc_notअगरy(काष्ठा tegra_ivc *ivc, व्योम *data)
अणु
	काष्ठा tegra_bpmp *bpmp = data;
	काष्ठा tegra186_bpmp *priv = bpmp->priv;

	अगर (WARN_ON(priv->mbox.channel == शून्य))
		वापस;

	tegra186_bpmp_ring_करोorbell(bpmp);
पूर्ण

अटल पूर्णांक tegra186_bpmp_channel_init(काष्ठा tegra_bpmp_channel *channel,
				      काष्ठा tegra_bpmp *bpmp,
				      अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra186_bpmp *priv = bpmp->priv;
	माप_प्रकार message_size, queue_size;
	अचिन्हित पूर्णांक offset;
	पूर्णांक err;

	channel->ivc = devm_kzalloc(bpmp->dev, माप(*channel->ivc),
				    GFP_KERNEL);
	अगर (!channel->ivc)
		वापस -ENOMEM;

	message_size = tegra_ivc_align(MSG_MIN_SZ);
	queue_size = tegra_ivc_total_queue_size(message_size);
	offset = queue_size * index;

	err = tegra_ivc_init(channel->ivc, शून्य,
			     priv->rx.virt + offset, priv->rx.phys + offset,
			     priv->tx.virt + offset, priv->tx.phys + offset,
			     1, message_size, tegra186_bpmp_ivc_notअगरy,
			     bpmp);
	अगर (err < 0) अणु
		dev_err(bpmp->dev, "failed to setup IVC for channel %u: %d\n",
			index, err);
		वापस err;
	पूर्ण

	init_completion(&channel->completion);
	channel->bpmp = bpmp;

	वापस 0;
पूर्ण

अटल व्योम tegra186_bpmp_channel_reset(काष्ठा tegra_bpmp_channel *channel)
अणु
	/* reset the channel state */
	tegra_ivc_reset(channel->ivc);

	/* sync the channel state with BPMP */
	जबतक (tegra_ivc_notअगरied(channel->ivc))
		;
पूर्ण

अटल व्योम tegra186_bpmp_channel_cleanup(काष्ठा tegra_bpmp_channel *channel)
अणु
	tegra_ivc_cleanup(channel->ivc);
पूर्ण

अटल व्योम mbox_handle_rx(काष्ठा mbox_client *client, व्योम *data)
अणु
	काष्ठा tegra_bpmp *bpmp = mbox_client_to_bpmp(client);

	tegra_bpmp_handle_rx(bpmp);
पूर्ण

अटल पूर्णांक tegra186_bpmp_init(काष्ठा tegra_bpmp *bpmp)
अणु
	काष्ठा tegra186_bpmp *priv;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	priv = devm_kzalloc(bpmp->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	bpmp->priv = priv;
	priv->parent = bpmp;

	priv->tx.pool = of_gen_pool_get(bpmp->dev->of_node, "shmem", 0);
	अगर (!priv->tx.pool) अणु
		dev_err(bpmp->dev, "TX shmem pool not found\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	priv->tx.virt = gen_pool_dma_alloc(priv->tx.pool, 4096, &priv->tx.phys);
	अगर (!priv->tx.virt) अणु
		dev_err(bpmp->dev, "failed to allocate from TX pool\n");
		वापस -ENOMEM;
	पूर्ण

	priv->rx.pool = of_gen_pool_get(bpmp->dev->of_node, "shmem", 1);
	अगर (!priv->rx.pool) अणु
		dev_err(bpmp->dev, "RX shmem pool not found\n");
		err = -EPROBE_DEFER;
		जाओ मुक्त_tx;
	पूर्ण

	priv->rx.virt = gen_pool_dma_alloc(priv->rx.pool, 4096, &priv->rx.phys);
	अगर (!priv->rx.virt) अणु
		dev_err(bpmp->dev, "failed to allocate from RX pool\n");
		err = -ENOMEM;
		जाओ मुक्त_tx;
	पूर्ण

	err = tegra186_bpmp_channel_init(bpmp->tx_channel, bpmp,
					 bpmp->soc->channels.cpu_tx.offset);
	अगर (err < 0)
		जाओ मुक्त_rx;

	err = tegra186_bpmp_channel_init(bpmp->rx_channel, bpmp,
					 bpmp->soc->channels.cpu_rx.offset);
	अगर (err < 0)
		जाओ cleanup_tx_channel;

	क्रम (i = 0; i < bpmp->thपढ़ोed.count; i++) अणु
		अचिन्हित पूर्णांक index = bpmp->soc->channels.thपढ़ो.offset + i;

		err = tegra186_bpmp_channel_init(&bpmp->thपढ़ोed_channels[i],
						 bpmp, index);
		अगर (err < 0)
			जाओ cleanup_channels;
	पूर्ण

	/* mbox registration */
	priv->mbox.client.dev = bpmp->dev;
	priv->mbox.client.rx_callback = mbox_handle_rx;
	priv->mbox.client.tx_block = false;
	priv->mbox.client.knows_txकरोne = false;

	priv->mbox.channel = mbox_request_channel(&priv->mbox.client, 0);
	अगर (IS_ERR(priv->mbox.channel)) अणु
		err = PTR_ERR(priv->mbox.channel);
		dev_err(bpmp->dev, "failed to get HSP mailbox: %d\n", err);
		जाओ cleanup_channels;
	पूर्ण

	tegra186_bpmp_channel_reset(bpmp->tx_channel);
	tegra186_bpmp_channel_reset(bpmp->rx_channel);

	क्रम (i = 0; i < bpmp->thपढ़ोed.count; i++)
		tegra186_bpmp_channel_reset(&bpmp->thपढ़ोed_channels[i]);

	वापस 0;

cleanup_channels:
	क्रम (i = 0; i < bpmp->thपढ़ोed.count; i++) अणु
		अगर (!bpmp->thपढ़ोed_channels[i].bpmp)
			जारी;

		tegra186_bpmp_channel_cleanup(&bpmp->thपढ़ोed_channels[i]);
	पूर्ण

	tegra186_bpmp_channel_cleanup(bpmp->rx_channel);
cleanup_tx_channel:
	tegra186_bpmp_channel_cleanup(bpmp->tx_channel);
मुक्त_rx:
	gen_pool_मुक्त(priv->rx.pool, (अचिन्हित दीर्घ)priv->rx.virt, 4096);
मुक्त_tx:
	gen_pool_मुक्त(priv->tx.pool, (अचिन्हित दीर्घ)priv->tx.virt, 4096);

	वापस err;
पूर्ण

अटल व्योम tegra186_bpmp_deinit(काष्ठा tegra_bpmp *bpmp)
अणु
	काष्ठा tegra186_bpmp *priv = bpmp->priv;
	अचिन्हित पूर्णांक i;

	mbox_मुक्त_channel(priv->mbox.channel);

	क्रम (i = 0; i < bpmp->thपढ़ोed.count; i++)
		tegra186_bpmp_channel_cleanup(&bpmp->thपढ़ोed_channels[i]);

	tegra186_bpmp_channel_cleanup(bpmp->rx_channel);
	tegra186_bpmp_channel_cleanup(bpmp->tx_channel);

	gen_pool_मुक्त(priv->rx.pool, (अचिन्हित दीर्घ)priv->rx.virt, 4096);
	gen_pool_मुक्त(priv->tx.pool, (अचिन्हित दीर्घ)priv->tx.virt, 4096);
पूर्ण

अटल पूर्णांक tegra186_bpmp_resume(काष्ठा tegra_bpmp *bpmp)
अणु
	अचिन्हित पूर्णांक i;

	/* reset message channels */
	tegra186_bpmp_channel_reset(bpmp->tx_channel);
	tegra186_bpmp_channel_reset(bpmp->rx_channel);

	क्रम (i = 0; i < bpmp->thपढ़ोed.count; i++)
		tegra186_bpmp_channel_reset(&bpmp->thपढ़ोed_channels[i]);

	वापस 0;
पूर्ण

स्थिर काष्ठा tegra_bpmp_ops tegra186_bpmp_ops = अणु
	.init = tegra186_bpmp_init,
	.deinit = tegra186_bpmp_deinit,
	.is_response_पढ़ोy = tegra186_bpmp_is_message_पढ़ोy,
	.is_request_पढ़ोy = tegra186_bpmp_is_message_पढ़ोy,
	.ack_response = tegra186_bpmp_ack_message,
	.ack_request = tegra186_bpmp_ack_message,
	.is_response_channel_मुक्त = tegra186_bpmp_is_channel_मुक्त,
	.is_request_channel_मुक्त = tegra186_bpmp_is_channel_मुक्त,
	.post_response = tegra186_bpmp_post_message,
	.post_request = tegra186_bpmp_post_message,
	.ring_करोorbell = tegra186_bpmp_ring_करोorbell,
	.resume = tegra186_bpmp_resume,
पूर्ण;
