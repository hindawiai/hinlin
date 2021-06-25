<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/drivers/dma/dma-api.c
 *
 * SuperH-specअगरic DMA management API
 *
 * Copyright (C) 2003, 2004, 2005  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/list.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/dma.h>

DEFINE_SPINLOCK(dma_spin_lock);
अटल LIST_HEAD(रेजिस्टरed_dmac_list);

काष्ठा dma_info *get_dma_info(अचिन्हित पूर्णांक chan)
अणु
	काष्ठा dma_info *info;

	/*
	 * Look क्रम each DMAC's range to determine who the owner of
	 * the channel is.
	 */
	list_क्रम_each_entry(info, &रेजिस्टरed_dmac_list, list) अणु
		अगर ((chan <  info->first_vchannel_nr) ||
		    (chan >= info->first_vchannel_nr + info->nr_channels))
			जारी;

		वापस info;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(get_dma_info);

काष्ठा dma_info *get_dma_info_by_name(स्थिर अक्षर *dmac_name)
अणु
	काष्ठा dma_info *info;

	list_क्रम_each_entry(info, &रेजिस्टरed_dmac_list, list) अणु
		अगर (dmac_name && (म_भेद(dmac_name, info->name) != 0))
			जारी;
		अन्यथा
			वापस info;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(get_dma_info_by_name);

अटल अचिन्हित पूर्णांक get_nr_channels(व्योम)
अणु
	काष्ठा dma_info *info;
	अचिन्हित पूर्णांक nr = 0;

	अगर (unlikely(list_empty(&रेजिस्टरed_dmac_list)))
		वापस nr;

	list_क्रम_each_entry(info, &रेजिस्टरed_dmac_list, list)
		nr += info->nr_channels;

	वापस nr;
पूर्ण

काष्ठा dma_channel *get_dma_channel(अचिन्हित पूर्णांक chan)
अणु
	काष्ठा dma_info *info = get_dma_info(chan);
	काष्ठा dma_channel *channel;
	पूर्णांक i;

	अगर (unlikely(!info))
		वापस ERR_PTR(-EINVAL);

	क्रम (i = 0; i < info->nr_channels; i++) अणु
		channel = &info->channels[i];
		अगर (channel->vchan == chan)
			वापस channel;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(get_dma_channel);

पूर्णांक get_dma_residue(अचिन्हित पूर्णांक chan)
अणु
	काष्ठा dma_info *info = get_dma_info(chan);
	काष्ठा dma_channel *channel = get_dma_channel(chan);

	अगर (info->ops->get_residue)
		वापस info->ops->get_residue(channel);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(get_dma_residue);

अटल पूर्णांक search_cap(स्थिर अक्षर **haystack, स्थिर अक्षर *needle)
अणु
	स्थिर अक्षर **p;

	क्रम (p = haystack; *p; p++)
		अगर (म_भेद(*p, needle) == 0)
			वापस 1;

	वापस 0;
पूर्ण

/**
 * request_dma_bycap - Allocate a DMA channel based on its capabilities
 * @dmac: List of DMA controllers to search
 * @caps: List of capabilities
 *
 * Search all channels of all DMA controllers to find a channel which
 * matches the requested capabilities. The result is the channel
 * number अगर a match is found, or %-ENODEV अगर no match is found.
 *
 * Note that not all DMA controllers export capabilities, in which
 * हाल they can never be allocated using this API, and so
 * request_dma() must be used specअगरying the channel number.
 */
पूर्णांक request_dma_bycap(स्थिर अक्षर **dmac, स्थिर अक्षर **caps, स्थिर अक्षर *dev_id)
अणु
	अचिन्हित पूर्णांक found = 0;
	काष्ठा dma_info *info;
	स्थिर अक्षर **p;
	पूर्णांक i;

	BUG_ON(!dmac || !caps);

	list_क्रम_each_entry(info, &रेजिस्टरed_dmac_list, list)
		अगर (म_भेद(*dmac, info->name) == 0) अणु
			found = 1;
			अवरोध;
		पूर्ण

	अगर (!found)
		वापस -ENODEV;

	क्रम (i = 0; i < info->nr_channels; i++) अणु
		काष्ठा dma_channel *channel = &info->channels[i];

		अगर (unlikely(!channel->caps))
			जारी;

		क्रम (p = caps; *p; p++) अणु
			अगर (!search_cap(channel->caps, *p))
				अवरोध;
			अगर (request_dma(channel->chan, dev_id) == 0)
				वापस channel->chan;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(request_dma_bycap);

पूर्णांक dmac_search_मुक्त_channel(स्थिर अक्षर *dev_id)
अणु
	काष्ठा dma_channel *channel = अणु 0 पूर्ण;
	काष्ठा dma_info *info = get_dma_info(0);
	पूर्णांक i;

	क्रम (i = 0; i < info->nr_channels; i++) अणु
		channel = &info->channels[i];
		अगर (unlikely(!channel))
			वापस -ENODEV;

		अगर (atomic_पढ़ो(&channel->busy) == 0)
			अवरोध;
	पूर्ण

	अगर (info->ops->request) अणु
		पूर्णांक result = info->ops->request(channel);
		अगर (result)
			वापस result;

		atomic_set(&channel->busy, 1);
		वापस channel->chan;
	पूर्ण

	वापस -ENOSYS;
पूर्ण

पूर्णांक request_dma(अचिन्हित पूर्णांक chan, स्थिर अक्षर *dev_id)
अणु
	काष्ठा dma_channel *channel = अणु 0 पूर्ण;
	काष्ठा dma_info *info = get_dma_info(chan);
	पूर्णांक result;

	channel = get_dma_channel(chan);
	अगर (atomic_xchg(&channel->busy, 1))
		वापस -EBUSY;

	strlcpy(channel->dev_id, dev_id, माप(channel->dev_id));

	अगर (info->ops->request) अणु
		result = info->ops->request(channel);
		अगर (result)
			atomic_set(&channel->busy, 0);

		वापस result;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(request_dma);

व्योम मुक्त_dma(अचिन्हित पूर्णांक chan)
अणु
	काष्ठा dma_info *info = get_dma_info(chan);
	काष्ठा dma_channel *channel = get_dma_channel(chan);

	अगर (info->ops->मुक्त)
		info->ops->मुक्त(channel);

	atomic_set(&channel->busy, 0);
पूर्ण
EXPORT_SYMBOL(मुक्त_dma);

व्योम dma_रुको_क्रम_completion(अचिन्हित पूर्णांक chan)
अणु
	काष्ठा dma_info *info = get_dma_info(chan);
	काष्ठा dma_channel *channel = get_dma_channel(chan);

	अगर (channel->flags & DMA_TEI_CAPABLE) अणु
		रुको_event(channel->रुको_queue,
			   (info->ops->get_residue(channel) == 0));
		वापस;
	पूर्ण

	जबतक (info->ops->get_residue(channel))
		cpu_relax();
पूर्ण
EXPORT_SYMBOL(dma_रुको_क्रम_completion);

पूर्णांक रेजिस्टर_chan_caps(स्थिर अक्षर *dmac, काष्ठा dma_chan_caps *caps)
अणु
	काष्ठा dma_info *info;
	अचिन्हित पूर्णांक found = 0;
	पूर्णांक i;

	list_क्रम_each_entry(info, &रेजिस्टरed_dmac_list, list)
		अगर (म_भेद(dmac, info->name) == 0) अणु
			found = 1;
			अवरोध;
		पूर्ण

	अगर (unlikely(!found))
		वापस -ENODEV;

	क्रम (i = 0; i < info->nr_channels; i++, caps++) अणु
		काष्ठा dma_channel *channel;

		अगर ((info->first_channel_nr + i) != caps->ch_num)
			वापस -EINVAL;

		channel = &info->channels[i];
		channel->caps = caps->caplist;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_chan_caps);

व्योम dma_configure_channel(अचिन्हित पूर्णांक chan, अचिन्हित दीर्घ flags)
अणु
	काष्ठा dma_info *info = get_dma_info(chan);
	काष्ठा dma_channel *channel = get_dma_channel(chan);

	अगर (info->ops->configure)
		info->ops->configure(channel, flags);
पूर्ण
EXPORT_SYMBOL(dma_configure_channel);

पूर्णांक dma_xfer(अचिन्हित पूर्णांक chan, अचिन्हित दीर्घ from,
	     अचिन्हित दीर्घ to, माप_प्रकार size, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा dma_info *info = get_dma_info(chan);
	काष्ठा dma_channel *channel = get_dma_channel(chan);

	channel->sar	= from;
	channel->dar	= to;
	channel->count	= size;
	channel->mode	= mode;

	वापस info->ops->xfer(channel);
पूर्ण
EXPORT_SYMBOL(dma_xfer);

पूर्णांक dma_extend(अचिन्हित पूर्णांक chan, अचिन्हित दीर्घ op, व्योम *param)
अणु
	काष्ठा dma_info *info = get_dma_info(chan);
	काष्ठा dma_channel *channel = get_dma_channel(chan);

	अगर (info->ops->extend)
		वापस info->ops->extend(channel, op, param);

	वापस -ENOSYS;
पूर्ण
EXPORT_SYMBOL(dma_extend);

अटल पूर्णांक dma_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा dma_info *info = v;

	अगर (list_empty(&रेजिस्टरed_dmac_list))
		वापस 0;

	/*
	 * Iterate over each रेजिस्टरed DMAC
	 */
	list_क्रम_each_entry(info, &रेजिस्टरed_dmac_list, list) अणु
		पूर्णांक i;

		/*
		 * Iterate over each channel
		 */
		क्रम (i = 0; i < info->nr_channels; i++) अणु
			काष्ठा dma_channel *channel = info->channels + i;

			अगर (!(channel->flags & DMA_CONFIGURED))
				जारी;

			seq_म_लिखो(m, "%2d: %14s    %s\n", i,
				   info->name, channel->dev_id);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक रेजिस्टर_dmac(काष्ठा dma_info *info)
अणु
	अचिन्हित पूर्णांक total_channels, i;

	INIT_LIST_HEAD(&info->list);

	prपूर्णांकk(KERN_INFO "DMA: Registering %s handler (%d channel%s).\n",
	       info->name, info->nr_channels, info->nr_channels > 1 ? "s" : "");

	BUG_ON((info->flags & DMAC_CHANNELS_CONFIGURED) && !info->channels);

	info->pdev = platक्रमm_device_रेजिस्टर_simple(info->name, -1,
						     शून्य, 0);
	अगर (IS_ERR(info->pdev))
		वापस PTR_ERR(info->pdev);

	/*
	 * Don't touch pre-configured channels
	 */
	अगर (!(info->flags & DMAC_CHANNELS_CONFIGURED)) अणु
		अचिन्हित पूर्णांक size;

		size = माप(काष्ठा dma_channel) * info->nr_channels;

		info->channels = kzalloc(size, GFP_KERNEL);
		अगर (!info->channels)
			वापस -ENOMEM;
	पूर्ण

	total_channels = get_nr_channels();
	info->first_vchannel_nr = total_channels;
	क्रम (i = 0; i < info->nr_channels; i++) अणु
		काष्ठा dma_channel *chan = &info->channels[i];

		atomic_set(&chan->busy, 0);

		chan->chan  = info->first_channel_nr + i;
		chan->vchan = info->first_channel_nr + i + total_channels;

		स_नकल(chan->dev_id, "Unused", 7);

		अगर (info->flags & DMAC_CHANNELS_TEI_CAPABLE)
			chan->flags |= DMA_TEI_CAPABLE;

		init_रुकोqueue_head(&chan->रुको_queue);
		dma_create_sysfs_files(chan, info);
	पूर्ण

	list_add(&info->list, &रेजिस्टरed_dmac_list);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_dmac);

व्योम unरेजिस्टर_dmac(काष्ठा dma_info *info)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < info->nr_channels; i++)
		dma_हटाओ_sysfs_files(info->channels + i, info);

	अगर (!(info->flags & DMAC_CHANNELS_CONFIGURED))
		kमुक्त(info->channels);

	list_del(&info->list);
	platक्रमm_device_unरेजिस्टर(info->pdev);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_dmac);

अटल पूर्णांक __init dma_api_init(व्योम)
अणु
	prपूर्णांकk(KERN_NOTICE "DMA: Registering DMA API.\n");
	वापस proc_create_single("dma", 0, शून्य, dma_proc_show) ? 0 : -ENOMEM;
पूर्ण
subsys_initcall(dma_api_init);

MODULE_AUTHOR("Paul Mundt <lethal@linux-sh.org>");
MODULE_DESCRIPTION("DMA API for SuperH");
MODULE_LICENSE("GPL v2");
