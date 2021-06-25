<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tegra host1x Channel
 *
 * Copyright (c) 2010-2013, NVIDIA Corporation.
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश "channel.h"
#समावेश "dev.h"
#समावेश "job.h"

/* Conकाष्ठाor क्रम the host1x device list */
पूर्णांक host1x_channel_list_init(काष्ठा host1x_channel_list *chlist,
			     अचिन्हित पूर्णांक num_channels)
अणु
	chlist->channels = kसुस्मृति(num_channels, माप(काष्ठा host1x_channel),
				   GFP_KERNEL);
	अगर (!chlist->channels)
		वापस -ENOMEM;

	chlist->allocated_channels =
		kसुस्मृति(BITS_TO_LONGS(num_channels), माप(अचिन्हित दीर्घ),
			GFP_KERNEL);
	अगर (!chlist->allocated_channels) अणु
		kमुक्त(chlist->channels);
		वापस -ENOMEM;
	पूर्ण

	biपंचांगap_zero(chlist->allocated_channels, num_channels);

	वापस 0;
पूर्ण

व्योम host1x_channel_list_मुक्त(काष्ठा host1x_channel_list *chlist)
अणु
	kमुक्त(chlist->allocated_channels);
	kमुक्त(chlist->channels);
पूर्ण

पूर्णांक host1x_job_submit(काष्ठा host1x_job *job)
अणु
	काष्ठा host1x *host = dev_get_drvdata(job->channel->dev->parent);

	वापस host1x_hw_channel_submit(host, job);
पूर्ण
EXPORT_SYMBOL(host1x_job_submit);

काष्ठा host1x_channel *host1x_channel_get(काष्ठा host1x_channel *channel)
अणु
	kref_get(&channel->refcount);

	वापस channel;
पूर्ण
EXPORT_SYMBOL(host1x_channel_get);

/**
 * host1x_channel_get_index() - Attempt to get channel reference by index
 * @host: Host1x device object
 * @index: Index of channel
 *
 * If channel number @index is currently allocated, increase its refcount
 * and वापस a poपूर्णांकer to it. Otherwise, वापस शून्य.
 */
काष्ठा host1x_channel *host1x_channel_get_index(काष्ठा host1x *host,
						अचिन्हित पूर्णांक index)
अणु
	काष्ठा host1x_channel *ch = &host->channel_list.channels[index];

	अगर (!kref_get_unless_zero(&ch->refcount))
		वापस शून्य;

	वापस ch;
पूर्ण

अटल व्योम release_channel(काष्ठा kref *kref)
अणु
	काष्ठा host1x_channel *channel =
		container_of(kref, काष्ठा host1x_channel, refcount);
	काष्ठा host1x *host = dev_get_drvdata(channel->dev->parent);
	काष्ठा host1x_channel_list *chlist = &host->channel_list;

	host1x_hw_cdma_stop(host, &channel->cdma);
	host1x_cdma_deinit(&channel->cdma);

	clear_bit(channel->id, chlist->allocated_channels);
पूर्ण

व्योम host1x_channel_put(काष्ठा host1x_channel *channel)
अणु
	kref_put(&channel->refcount, release_channel);
पूर्ण
EXPORT_SYMBOL(host1x_channel_put);

अटल काष्ठा host1x_channel *acquire_unused_channel(काष्ठा host1x *host)
अणु
	काष्ठा host1x_channel_list *chlist = &host->channel_list;
	अचिन्हित पूर्णांक max_channels = host->info->nb_channels;
	अचिन्हित पूर्णांक index;

	index = find_first_zero_bit(chlist->allocated_channels, max_channels);
	अगर (index >= max_channels) अणु
		dev_err(host->dev, "failed to find free channel\n");
		वापस शून्य;
	पूर्ण

	chlist->channels[index].id = index;

	set_bit(index, chlist->allocated_channels);

	वापस &chlist->channels[index];
पूर्ण

/**
 * host1x_channel_request() - Allocate a channel
 * @client: Host1x client this channel will be used to send commands to
 *
 * Allocates a new host1x channel क्रम @client. May वापस शून्य अगर CDMA
 * initialization fails.
 */
काष्ठा host1x_channel *host1x_channel_request(काष्ठा host1x_client *client)
अणु
	काष्ठा host1x *host = dev_get_drvdata(client->dev->parent);
	काष्ठा host1x_channel_list *chlist = &host->channel_list;
	काष्ठा host1x_channel *channel;
	पूर्णांक err;

	channel = acquire_unused_channel(host);
	अगर (!channel)
		वापस शून्य;

	kref_init(&channel->refcount);
	mutex_init(&channel->submitlock);
	channel->client = client;
	channel->dev = client->dev;

	err = host1x_hw_channel_init(host, channel, channel->id);
	अगर (err < 0)
		जाओ fail;

	err = host1x_cdma_init(&channel->cdma);
	अगर (err < 0)
		जाओ fail;

	वापस channel;

fail:
	clear_bit(channel->id, chlist->allocated_channels);

	dev_err(client->dev, "failed to initialize channel\n");

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(host1x_channel_request);
