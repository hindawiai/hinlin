<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HD-audio core bus driver
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <sound/hdaudपन.स>
#समावेश "local.h"
#समावेश "trace.h"

अटल व्योम snd_hdac_bus_process_unsol_events(काष्ठा work_काष्ठा *work);

अटल स्थिर काष्ठा hdac_bus_ops शेष_ops = अणु
	.command = snd_hdac_bus_send_cmd,
	.get_response = snd_hdac_bus_get_response,
	.link_घातer = snd_hdac_bus_link_घातer,
पूर्ण;

/**
 * snd_hdac_bus_init - initialize a HD-audio bas bus
 * @bus: the poपूर्णांकer to bus object
 * @dev: device poपूर्णांकer
 * @ops: bus verb चालकs
 *
 * Returns 0 अगर successful, or a negative error code.
 */
पूर्णांक snd_hdac_bus_init(काष्ठा hdac_bus *bus, काष्ठा device *dev,
		      स्थिर काष्ठा hdac_bus_ops *ops)
अणु
	स_रखो(bus, 0, माप(*bus));
	bus->dev = dev;
	अगर (ops)
		bus->ops = ops;
	अन्यथा
		bus->ops = &शेष_ops;
	bus->dma_type = SNDRV_DMA_TYPE_DEV;
	INIT_LIST_HEAD(&bus->stream_list);
	INIT_LIST_HEAD(&bus->codec_list);
	INIT_WORK(&bus->unsol_work, snd_hdac_bus_process_unsol_events);
	spin_lock_init(&bus->reg_lock);
	mutex_init(&bus->cmd_mutex);
	mutex_init(&bus->lock);
	INIT_LIST_HEAD(&bus->hlink_list);
	init_रुकोqueue_head(&bus->rirb_wq);
	bus->irq = -1;

	/*
	 * Default value of '8' is as per the HD audio specअगरication (Rev 1.0a).
	 * Following relation is used to derive STRIPE control value.
	 *  For sample rate <= 48K:
	 *   अणु ((num_channels * bits_per_sample) / number of SDOs) >= 8 पूर्ण
	 *  For sample rate > 48K:
	 *   अणु ((num_channels * bits_per_sample * rate/48000) /
	 *	number of SDOs) >= 8 पूर्ण
	 */
	bus->sकरो_limit = 8;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_init);

/**
 * snd_hdac_bus_निकास - clean up a HD-audio bas bus
 * @bus: the poपूर्णांकer to bus object
 */
व्योम snd_hdac_bus_निकास(काष्ठा hdac_bus *bus)
अणु
	WARN_ON(!list_empty(&bus->stream_list));
	WARN_ON(!list_empty(&bus->codec_list));
	cancel_work_sync(&bus->unsol_work);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_निकास);

/**
 * snd_hdac_bus_exec_verb - execute a HD-audio verb on the given bus
 * @bus: bus object
 * @addr: the HDAC device address
 * @cmd: HD-audio encoded verb
 * @res: poपूर्णांकer to store the response, शून्य अगर perक्रमming asynchronously
 *
 * Returns 0 अगर successful, or a negative error code.
 */
पूर्णांक snd_hdac_bus_exec_verb(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक addr,
			   अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक *res)
अणु
	पूर्णांक err;

	mutex_lock(&bus->cmd_mutex);
	err = snd_hdac_bus_exec_verb_unlocked(bus, addr, cmd, res);
	mutex_unlock(&bus->cmd_mutex);
	वापस err;
पूर्ण

/**
 * snd_hdac_bus_exec_verb_unlocked - unlocked version
 * @bus: bus object
 * @addr: the HDAC device address
 * @cmd: HD-audio encoded verb
 * @res: poपूर्णांकer to store the response, शून्य अगर perक्रमming asynchronously
 *
 * Returns 0 अगर successful, or a negative error code.
 */
पूर्णांक snd_hdac_bus_exec_verb_unlocked(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक addr,
				    अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक *res)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक err;

	अगर (cmd == ~0)
		वापस -EINVAL;

	अगर (res)
		*res = -1;
	अन्यथा अगर (bus->sync_ग_लिखो)
		res = &पंचांगp;
	क्रम (;;) अणु
		trace_hda_send_cmd(bus, cmd);
		err = bus->ops->command(bus, cmd);
		अगर (err != -EAGAIN)
			अवरोध;
		/* process pending verbs */
		err = bus->ops->get_response(bus, addr, &पंचांगp);
		अगर (err)
			अवरोध;
	पूर्ण
	अगर (!err && res) अणु
		err = bus->ops->get_response(bus, addr, res);
		trace_hda_get_response(bus, addr, *res);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_exec_verb_unlocked);

/**
 * snd_hdac_bus_queue_event - add an unsolicited event to queue
 * @bus: the BUS
 * @res: unsolicited event (lower 32bit of RIRB entry)
 * @res_ex: codec addr and flags (upper 32bit or RIRB entry)
 *
 * Adds the given event to the queue.  The events are processed in
 * the workqueue asynchronously.  Call this function in the पूर्णांकerrupt
 * hanlder when RIRB receives an unsolicited event.
 */
व्योम snd_hdac_bus_queue_event(काष्ठा hdac_bus *bus, u32 res, u32 res_ex)
अणु
	अचिन्हित पूर्णांक wp;

	अगर (!bus)
		वापस;

	trace_hda_unsol_event(bus, res, res_ex);
	wp = (bus->unsol_wp + 1) % HDA_UNSOL_QUEUE_SIZE;
	bus->unsol_wp = wp;

	wp <<= 1;
	bus->unsol_queue[wp] = res;
	bus->unsol_queue[wp + 1] = res_ex;

	schedule_work(&bus->unsol_work);
पूर्ण

/*
 * process queued unsolicited events
 */
अटल व्योम snd_hdac_bus_process_unsol_events(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdac_bus *bus = container_of(work, काष्ठा hdac_bus, unsol_work);
	काष्ठा hdac_device *codec;
	काष्ठा hdac_driver *drv;
	अचिन्हित पूर्णांक rp, caddr, res;

	spin_lock_irq(&bus->reg_lock);
	जबतक (bus->unsol_rp != bus->unsol_wp) अणु
		rp = (bus->unsol_rp + 1) % HDA_UNSOL_QUEUE_SIZE;
		bus->unsol_rp = rp;
		rp <<= 1;
		res = bus->unsol_queue[rp];
		caddr = bus->unsol_queue[rp + 1];
		अगर (!(caddr & (1 << 4))) /* no unsolicited event? */
			जारी;
		codec = bus->caddr_tbl[caddr & 0x0f];
		अगर (!codec || !codec->dev.driver)
			जारी;
		spin_unlock_irq(&bus->reg_lock);
		drv = drv_to_hdac_driver(codec->dev.driver);
		अगर (drv->unsol_event)
			drv->unsol_event(codec, res);
		spin_lock_irq(&bus->reg_lock);
	पूर्ण
	spin_unlock_irq(&bus->reg_lock);
पूर्ण

/**
 * snd_hdac_bus_add_device - Add a codec to bus
 * @bus: HDA core bus
 * @codec: HDA core device to add
 *
 * Adds the given codec to the list in the bus.  The caddr_tbl array
 * and codec_घातered bits are updated, as well.
 * Returns zero अगर success, or a negative error code.
 */
पूर्णांक snd_hdac_bus_add_device(काष्ठा hdac_bus *bus, काष्ठा hdac_device *codec)
अणु
	अगर (bus->caddr_tbl[codec->addr]) अणु
		dev_err(bus->dev, "address 0x%x is already occupied\n",
			codec->addr);
		वापस -EBUSY;
	पूर्ण

	list_add_tail(&codec->list, &bus->codec_list);
	bus->caddr_tbl[codec->addr] = codec;
	set_bit(codec->addr, &bus->codec_घातered);
	bus->num_codecs++;
	वापस 0;
पूर्ण

/**
 * snd_hdac_bus_हटाओ_device - Remove a codec from bus
 * @bus: HDA core bus
 * @codec: HDA core device to हटाओ
 */
व्योम snd_hdac_bus_हटाओ_device(काष्ठा hdac_bus *bus,
				काष्ठा hdac_device *codec)
अणु
	WARN_ON(bus != codec->bus);
	अगर (list_empty(&codec->list))
		वापस;
	list_del_init(&codec->list);
	bus->caddr_tbl[codec->addr] = शून्य;
	clear_bit(codec->addr, &bus->codec_घातered);
	bus->num_codecs--;
	flush_work(&bus->unsol_work);
पूर्ण

#अगर_घोषित CONFIG_SND_HDA_ALIGNED_MMIO
/* Helpers क्रम aligned पढ़ो/ग_लिखो of mmio space, क्रम Tegra */
अचिन्हित पूर्णांक snd_hdac_aligned_पढ़ो(व्योम __iomem *addr, अचिन्हित पूर्णांक mask)
अणु
	व्योम __iomem *aligned_addr =
		(व्योम __iomem *)((अचिन्हित दीर्घ)(addr) & ~0x3);
	अचिन्हित पूर्णांक shअगरt = ((अचिन्हित दीर्घ)(addr) & 0x3) << 3;
	अचिन्हित पूर्णांक v;

	v = पढ़ोl(aligned_addr);
	वापस (v >> shअगरt) & mask;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_aligned_पढ़ो);

व्योम snd_hdac_aligned_ग_लिखो(अचिन्हित पूर्णांक val, व्योम __iomem *addr,
			    अचिन्हित पूर्णांक mask)
अणु
	व्योम __iomem *aligned_addr =
		(व्योम __iomem *)((अचिन्हित दीर्घ)(addr) & ~0x3);
	अचिन्हित पूर्णांक shअगरt = ((अचिन्हित दीर्घ)(addr) & 0x3) << 3;
	अचिन्हित पूर्णांक v;

	v = पढ़ोl(aligned_addr);
	v &= ~(mask << shअगरt);
	v |= val << shअगरt;
	ग_लिखोl(v, aligned_addr);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_aligned_ग_लिखो);
#पूर्ण_अगर /* CONFIG_SND_HDA_ALIGNED_MMIO */

व्योम snd_hdac_codec_link_up(काष्ठा hdac_device *codec)
अणु
	काष्ठा hdac_bus *bus = codec->bus;

	अगर (bus->ops->link_घातer)
		bus->ops->link_घातer(codec, true);
	अन्यथा
		snd_hdac_bus_link_घातer(codec, true);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_codec_link_up);

व्योम snd_hdac_codec_link_करोwn(काष्ठा hdac_device *codec)
अणु
	काष्ठा hdac_bus *bus = codec->bus;

	अगर (bus->ops->link_घातer)
		bus->ops->link_घातer(codec, false);
	अन्यथा
		snd_hdac_bus_link_घातer(codec, false);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_codec_link_करोwn);
