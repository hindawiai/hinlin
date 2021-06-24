<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  hdac-ext-stream.c - HD-audio extended stream operations.
 *
 *  Copyright (C) 2015 Intel Corp
 *  Author: Jeeja KP <jeeja.kp@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/hda_रेजिस्टर.h>
#समावेश <sound/hdaudio_ext.h>

/**
 * snd_hdac_ext_stream_init - initialize each stream (aka device)
 * @bus: HD-audio core bus
 * @stream: HD-audio ext core stream object to initialize
 * @idx: stream index number
 * @direction: stream direction (SNDRV_PCM_STREAM_PLAYBACK or SNDRV_PCM_STREAM_CAPTURE)
 * @tag: the tag id to assign
 *
 * initialize the stream, अगर ppcap is enabled then init those and then
 * invoke hdac stream initialization routine
 */
व्योम snd_hdac_ext_stream_init(काष्ठा hdac_bus *bus,
				काष्ठा hdac_ext_stream *stream,
				पूर्णांक idx, पूर्णांक direction, पूर्णांक tag)
अणु
	अगर (bus->ppcap) अणु
		stream->pphc_addr = bus->ppcap + AZX_PPHC_BASE +
				AZX_PPHC_INTERVAL * idx;

		stream->pplc_addr = bus->ppcap + AZX_PPLC_BASE +
				AZX_PPLC_MULTI * bus->num_streams +
				AZX_PPLC_INTERVAL * idx;
	पूर्ण

	अगर (bus->spbcap) अणु
		stream->spib_addr = bus->spbcap + AZX_SPB_BASE +
					AZX_SPB_INTERVAL * idx +
					AZX_SPB_SPIB;

		stream->fअगरo_addr = bus->spbcap + AZX_SPB_BASE +
					AZX_SPB_INTERVAL * idx +
					AZX_SPB_MAXFIFO;
	पूर्ण

	अगर (bus->drsmcap)
		stream->dpibr_addr = bus->drsmcap + AZX_DRSM_BASE +
					AZX_DRSM_INTERVAL * idx;

	stream->decoupled = false;
	snd_hdac_stream_init(bus, &stream->hstream, idx, direction, tag);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_stream_init);

/**
 * snd_hdac_ext_stream_init_all - create and initialize the stream objects
 *   क्रम an extended hda bus
 * @bus: HD-audio core bus
 * @start_idx: start index क्रम streams
 * @num_stream: number of streams to initialize
 * @dir: direction of streams
 */
पूर्णांक snd_hdac_ext_stream_init_all(काष्ठा hdac_bus *bus, पूर्णांक start_idx,
		पूर्णांक num_stream, पूर्णांक dir)
अणु
	पूर्णांक stream_tag = 0;
	पूर्णांक i, tag, idx = start_idx;

	क्रम (i = 0; i < num_stream; i++) अणु
		काष्ठा hdac_ext_stream *stream =
				kzalloc(माप(*stream), GFP_KERNEL);
		अगर (!stream)
			वापस -ENOMEM;
		tag = ++stream_tag;
		snd_hdac_ext_stream_init(bus, stream, idx, dir, tag);
		idx++;
	पूर्ण

	वापस 0;

पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_stream_init_all);

/**
 * snd_hdac_stream_मुक्त_all - मुक्त hdac extended stream objects
 *
 * @bus: HD-audio core bus
 */
व्योम snd_hdac_stream_मुक्त_all(काष्ठा hdac_bus *bus)
अणु
	काष्ठा hdac_stream *s, *_s;
	काष्ठा hdac_ext_stream *stream;

	list_क्रम_each_entry_safe(s, _s, &bus->stream_list, list) अणु
		stream = stream_to_hdac_ext_stream(s);
		snd_hdac_ext_stream_decouple(bus, stream, false);
		list_del(&s->list);
		kमुक्त(stream);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_मुक्त_all);

/**
 * snd_hdac_ext_stream_decouple - decouple the hdac stream
 * @bus: HD-audio core bus
 * @stream: HD-audio ext core stream object to initialize
 * @decouple: flag to decouple
 */
व्योम snd_hdac_ext_stream_decouple(काष्ठा hdac_bus *bus,
				काष्ठा hdac_ext_stream *stream, bool decouple)
अणु
	काष्ठा hdac_stream *hstream = &stream->hstream;
	u32 val;
	पूर्णांक mask = AZX_PPCTL_PROCEN(hstream->index);

	spin_lock_irq(&bus->reg_lock);
	val = पढ़ोw(bus->ppcap + AZX_REG_PP_PPCTL) & mask;

	अगर (decouple && !val)
		snd_hdac_updatel(bus->ppcap, AZX_REG_PP_PPCTL, mask, mask);
	अन्यथा अगर (!decouple && val)
		snd_hdac_updatel(bus->ppcap, AZX_REG_PP_PPCTL, mask, 0);

	stream->decoupled = decouple;
	spin_unlock_irq(&bus->reg_lock);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_stream_decouple);

/**
 * snd_hdac_ext_link_stream_start - start a stream
 * @stream: HD-audio ext core stream to start
 */
व्योम snd_hdac_ext_link_stream_start(काष्ठा hdac_ext_stream *stream)
अणु
	snd_hdac_updatel(stream->pplc_addr, AZX_REG_PPLCCTL,
			 AZX_PPLCCTL_RUN, AZX_PPLCCTL_RUN);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_link_stream_start);

/**
 * snd_hdac_ext_link_stream_clear - stop a stream DMA
 * @stream: HD-audio ext core stream to stop
 */
व्योम snd_hdac_ext_link_stream_clear(काष्ठा hdac_ext_stream *stream)
अणु
	snd_hdac_updatel(stream->pplc_addr, AZX_REG_PPLCCTL, AZX_PPLCCTL_RUN, 0);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_link_stream_clear);

/**
 * snd_hdac_ext_link_stream_reset - reset a stream
 * @stream: HD-audio ext core stream to reset
 */
व्योम snd_hdac_ext_link_stream_reset(काष्ठा hdac_ext_stream *stream)
अणु
	अचिन्हित अक्षर val;
	पूर्णांक समयout;

	snd_hdac_ext_link_stream_clear(stream);

	snd_hdac_updatel(stream->pplc_addr, AZX_REG_PPLCCTL,
			 AZX_PPLCCTL_STRST, AZX_PPLCCTL_STRST);
	udelay(3);
	समयout = 50;
	करो अणु
		val = पढ़ोl(stream->pplc_addr + AZX_REG_PPLCCTL) &
				AZX_PPLCCTL_STRST;
		अगर (val)
			अवरोध;
		udelay(3);
	पूर्ण जबतक (--समयout);
	val &= ~AZX_PPLCCTL_STRST;
	ग_लिखोl(val, stream->pplc_addr + AZX_REG_PPLCCTL);
	udelay(3);

	समयout = 50;
	/* रुकोing क्रम hardware to report that the stream is out of reset */
	करो अणु
		val = पढ़ोl(stream->pplc_addr + AZX_REG_PPLCCTL) & AZX_PPLCCTL_STRST;
		अगर (!val)
			अवरोध;
		udelay(3);
	पूर्ण जबतक (--समयout);

पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_link_stream_reset);

/**
 * snd_hdac_ext_link_stream_setup -  set up the SD क्रम streaming
 * @stream: HD-audio ext core stream to set up
 * @fmt: stream क्रमmat
 */
पूर्णांक snd_hdac_ext_link_stream_setup(काष्ठा hdac_ext_stream *stream, पूर्णांक fmt)
अणु
	काष्ठा hdac_stream *hstream = &stream->hstream;
	अचिन्हित पूर्णांक val;

	/* make sure the run bit is zero क्रम SD */
	snd_hdac_ext_link_stream_clear(stream);
	/* program the stream_tag */
	val = पढ़ोl(stream->pplc_addr + AZX_REG_PPLCCTL);
	val = (val & ~AZX_PPLCCTL_STRM_MASK) |
		(hstream->stream_tag << AZX_PPLCCTL_STRM_SHIFT);
	ग_लिखोl(val, stream->pplc_addr + AZX_REG_PPLCCTL);

	/* program the stream क्रमmat */
	ग_लिखोw(fmt, stream->pplc_addr + AZX_REG_PPLCFMT);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_link_stream_setup);

/**
 * snd_hdac_ext_link_set_stream_id - maps stream id to link output
 * @link: HD-audio ext link to set up
 * @stream: stream id
 */
व्योम snd_hdac_ext_link_set_stream_id(काष्ठा hdac_ext_link *link,
				 पूर्णांक stream)
अणु
	snd_hdac_updatew(link->ml_addr, AZX_REG_ML_LOSIDV, (1 << stream), 1 << stream);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_link_set_stream_id);

/**
 * snd_hdac_ext_link_clear_stream_id - maps stream id to link output
 * @link: HD-audio ext link to set up
 * @stream: stream id
 */
व्योम snd_hdac_ext_link_clear_stream_id(काष्ठा hdac_ext_link *link,
				 पूर्णांक stream)
अणु
	snd_hdac_updatew(link->ml_addr, AZX_REG_ML_LOSIDV, (1 << stream), 0);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_link_clear_stream_id);

अटल काष्ठा hdac_ext_stream *
hdac_ext_link_stream_assign(काष्ठा hdac_bus *bus,
				काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdac_ext_stream *res = शून्य;
	काष्ठा hdac_stream *stream = शून्य;

	अगर (!bus->ppcap) अणु
		dev_err(bus->dev, "stream type not supported\n");
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(stream, &bus->stream_list, list) अणु
		काष्ठा hdac_ext_stream *hstream = container_of(stream,
						काष्ठा hdac_ext_stream,
						hstream);
		अगर (stream->direction != substream->stream)
			जारी;

		/* check अगर decoupled stream and not in use is available */
		अगर (hstream->decoupled && !hstream->link_locked) अणु
			res = hstream;
			अवरोध;
		पूर्ण

		अगर (!hstream->link_locked) अणु
			snd_hdac_ext_stream_decouple(bus, hstream, true);
			res = hstream;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (res) अणु
		spin_lock_irq(&bus->reg_lock);
		res->link_locked = 1;
		res->link_substream = substream;
		spin_unlock_irq(&bus->reg_lock);
	पूर्ण
	वापस res;
पूर्ण

अटल काष्ठा hdac_ext_stream *
hdac_ext_host_stream_assign(काष्ठा hdac_bus *bus,
				काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdac_ext_stream *res = शून्य;
	काष्ठा hdac_stream *stream = शून्य;

	अगर (!bus->ppcap) अणु
		dev_err(bus->dev, "stream type not supported\n");
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(stream, &bus->stream_list, list) अणु
		काष्ठा hdac_ext_stream *hstream = container_of(stream,
						काष्ठा hdac_ext_stream,
						hstream);
		अगर (stream->direction != substream->stream)
			जारी;

		अगर (!stream->खोलोed) अणु
			अगर (!hstream->decoupled)
				snd_hdac_ext_stream_decouple(bus, hstream, true);
			res = hstream;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (res) अणु
		spin_lock_irq(&bus->reg_lock);
		res->hstream.खोलोed = 1;
		res->hstream.running = 0;
		res->hstream.substream = substream;
		spin_unlock_irq(&bus->reg_lock);
	पूर्ण

	वापस res;
पूर्ण

/**
 * snd_hdac_ext_stream_assign - assign a stream क्रम the PCM
 * @bus: HD-audio core bus
 * @substream: PCM substream to assign
 * @type: type of stream (coupled, host or link stream)
 *
 * This assigns the stream based on the type (coupled/host/link), क्रम the
 * given PCM substream, assigns it and वापसs the stream object
 *
 * coupled: Looks क्रम an unused stream
 * host: Looks क्रम an unused decoupled host stream
 * link: Looks क्रम an unused decoupled link stream
 *
 * If no stream is मुक्त, वापसs शून्य. The function tries to keep using
 * the same stream object when it's used beक्रमehand.  when a stream is
 * decoupled, it becomes a host stream and link stream.
 */
काष्ठा hdac_ext_stream *snd_hdac_ext_stream_assign(काष्ठा hdac_bus *bus,
					   काष्ठा snd_pcm_substream *substream,
					   पूर्णांक type)
अणु
	काष्ठा hdac_ext_stream *hstream = शून्य;
	काष्ठा hdac_stream *stream = शून्य;

	चयन (type) अणु
	हाल HDAC_EXT_STREAM_TYPE_COUPLED:
		stream = snd_hdac_stream_assign(bus, substream);
		अगर (stream)
			hstream = container_of(stream,
					काष्ठा hdac_ext_stream, hstream);
		वापस hstream;

	हाल HDAC_EXT_STREAM_TYPE_HOST:
		वापस hdac_ext_host_stream_assign(bus, substream);

	हाल HDAC_EXT_STREAM_TYPE_LINK:
		वापस hdac_ext_link_stream_assign(bus, substream);

	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_stream_assign);

/**
 * snd_hdac_ext_stream_release - release the asचिन्हित stream
 * @stream: HD-audio ext core stream to release
 * @type: type of stream (coupled, host or link stream)
 *
 * Release the stream that has been asचिन्हित by snd_hdac_ext_stream_assign().
 */
व्योम snd_hdac_ext_stream_release(काष्ठा hdac_ext_stream *stream, पूर्णांक type)
अणु
	काष्ठा hdac_bus *bus = stream->hstream.bus;

	चयन (type) अणु
	हाल HDAC_EXT_STREAM_TYPE_COUPLED:
		snd_hdac_stream_release(&stream->hstream);
		अवरोध;

	हाल HDAC_EXT_STREAM_TYPE_HOST:
		अगर (stream->decoupled && !stream->link_locked)
			snd_hdac_ext_stream_decouple(bus, stream, false);
		snd_hdac_stream_release(&stream->hstream);
		अवरोध;

	हाल HDAC_EXT_STREAM_TYPE_LINK:
		अगर (stream->decoupled && !stream->hstream.खोलोed)
			snd_hdac_ext_stream_decouple(bus, stream, false);
		spin_lock_irq(&bus->reg_lock);
		stream->link_locked = 0;
		stream->link_substream = शून्य;
		spin_unlock_irq(&bus->reg_lock);
		अवरोध;

	शेष:
		dev_dbg(bus->dev, "Invalid type %d\n", type);
	पूर्ण

पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_stream_release);

/**
 * snd_hdac_ext_stream_spbcap_enable - enable SPIB क्रम a stream
 * @bus: HD-audio core bus
 * @enable: flag to enable/disable SPIB
 * @index: stream index क्रम which SPIB need to be enabled
 */
व्योम snd_hdac_ext_stream_spbcap_enable(काष्ठा hdac_bus *bus,
				 bool enable, पूर्णांक index)
अणु
	u32 mask = 0;

	अगर (!bus->spbcap) अणु
		dev_err(bus->dev, "Address of SPB capability is NULL\n");
		वापस;
	पूर्ण

	mask |= (1 << index);

	अगर (enable)
		snd_hdac_updatel(bus->spbcap, AZX_REG_SPB_SPBFCCTL, mask, mask);
	अन्यथा
		snd_hdac_updatel(bus->spbcap, AZX_REG_SPB_SPBFCCTL, mask, 0);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_stream_spbcap_enable);

/**
 * snd_hdac_ext_stream_set_spib - sets the spib value of a stream
 * @bus: HD-audio core bus
 * @stream: hdac_ext_stream
 * @value: spib value to set
 */
पूर्णांक snd_hdac_ext_stream_set_spib(काष्ठा hdac_bus *bus,
				 काष्ठा hdac_ext_stream *stream, u32 value)
अणु

	अगर (!bus->spbcap) अणु
		dev_err(bus->dev, "Address of SPB capability is NULL\n");
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(value, stream->spib_addr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_stream_set_spib);

/**
 * snd_hdac_ext_stream_get_spbmaxfअगरo - माला_लो the spib value of a stream
 * @bus: HD-audio core bus
 * @stream: hdac_ext_stream
 *
 * Return maxfअगरo क्रम the stream
 */
पूर्णांक snd_hdac_ext_stream_get_spbmaxfअगरo(काष्ठा hdac_bus *bus,
				 काष्ठा hdac_ext_stream *stream)
अणु

	अगर (!bus->spbcap) अणु
		dev_err(bus->dev, "Address of SPB capability is NULL\n");
		वापस -EINVAL;
	पूर्ण

	वापस पढ़ोl(stream->fअगरo_addr);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_stream_get_spbmaxfअगरo);


/**
 * snd_hdac_ext_stop_streams - stop all stream अगर running
 * @bus: HD-audio core bus
 */
व्योम snd_hdac_ext_stop_streams(काष्ठा hdac_bus *bus)
अणु
	काष्ठा hdac_stream *stream;

	अगर (bus->chip_init) अणु
		list_क्रम_each_entry(stream, &bus->stream_list, list)
			snd_hdac_stream_stop(stream);
		snd_hdac_bus_stop_chip(bus);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_stop_streams);

/**
 * snd_hdac_ext_stream_drsm_enable - enable DMA resume क्रम a stream
 * @bus: HD-audio core bus
 * @enable: flag to enable/disable DRSM
 * @index: stream index क्रम which DRSM need to be enabled
 */
व्योम snd_hdac_ext_stream_drsm_enable(काष्ठा hdac_bus *bus,
				bool enable, पूर्णांक index)
अणु
	u32 mask = 0;

	अगर (!bus->drsmcap) अणु
		dev_err(bus->dev, "Address of DRSM capability is NULL\n");
		वापस;
	पूर्ण

	mask |= (1 << index);

	अगर (enable)
		snd_hdac_updatel(bus->drsmcap, AZX_REG_DRSM_CTL, mask, mask);
	अन्यथा
		snd_hdac_updatel(bus->drsmcap, AZX_REG_DRSM_CTL, mask, 0);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_stream_drsm_enable);

/**
 * snd_hdac_ext_stream_set_dpibr - sets the dpibr value of a stream
 * @bus: HD-audio core bus
 * @stream: hdac_ext_stream
 * @value: dpib value to set
 */
पूर्णांक snd_hdac_ext_stream_set_dpibr(काष्ठा hdac_bus *bus,
				 काष्ठा hdac_ext_stream *stream, u32 value)
अणु

	अगर (!bus->drsmcap) अणु
		dev_err(bus->dev, "Address of DRSM capability is NULL\n");
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(value, stream->dpibr_addr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_stream_set_dpibr);

/**
 * snd_hdac_ext_stream_set_lpib - sets the lpib value of a stream
 * @stream: hdac_ext_stream
 * @value: lpib value to set
 */
पूर्णांक snd_hdac_ext_stream_set_lpib(काष्ठा hdac_ext_stream *stream, u32 value)
अणु
	snd_hdac_stream_ग_लिखोl(&stream->hstream, SD_LPIB, value);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_stream_set_lpib);
