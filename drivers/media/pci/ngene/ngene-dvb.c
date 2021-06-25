<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ngene-dvb.c: nGene PCIe bridge driver - DVB functions
 *
 * Copyright (C) 2005-2007 Micronas
 *
 * Copyright (C) 2008-2009 Ralph Metzler <rjkm@metzlerbros.de>
 *                         Modअगरications क्रम new nGene firmware,
 *                         support क्रम EEPROM-copying,
 *                         support क्रम new dual DVB-S2 card prototype
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/भाग64.h>
#समावेश <linux/pci.h>
#समावेश <linux/समयr.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/firmware.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "ngene.h"

अटल पूर्णांक ci_tsfix = 1;
module_param(ci_tsfix, पूर्णांक, 0444);
MODULE_PARM_DESC(ci_tsfix, "Detect and fix TS buffer offset shifts in conjunction with CI expansions (default: 1/enabled)");

/****************************************************************************/
/* COMMAND API पूर्णांकerface ****************************************************/
/****************************************************************************/

अटल sमाप_प्रकार ts_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा ngene_channel *chan = dvbdev->priv;
	काष्ठा ngene *dev = chan->dev;

	अगर (रुको_event_पूर्णांकerruptible(dev->tsout_rbuf.queue,
				     dvb_ringbuffer_मुक्त
				     (&dev->tsout_rbuf) >= count) < 0)
		वापस 0;

	dvb_ringbuffer_ग_लिखो_user(&dev->tsout_rbuf, buf, count);

	वापस count;
पूर्ण

अटल sमाप_प्रकार ts_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा ngene_channel *chan = dvbdev->priv;
	काष्ठा ngene *dev = chan->dev;
	पूर्णांक left, avail;

	left = count;
	जबतक (left) अणु
		अगर (रुको_event_पूर्णांकerruptible(
			    dev->tsin_rbuf.queue,
			    dvb_ringbuffer_avail(&dev->tsin_rbuf) > 0) < 0)
			वापस -EAGAIN;
		avail = dvb_ringbuffer_avail(&dev->tsin_rbuf);
		अगर (avail > left)
			avail = left;
		dvb_ringbuffer_पढ़ो_user(&dev->tsin_rbuf, buf, avail);
		left -= avail;
		buf += avail;
	पूर्ण
	वापस count;
पूर्ण

अटल __poll_t ts_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा ngene_channel *chan = dvbdev->priv;
	काष्ठा ngene *dev = chan->dev;
	काष्ठा dvb_ringbuffer *rbuf = &dev->tsin_rbuf;
	काष्ठा dvb_ringbuffer *wbuf = &dev->tsout_rbuf;
	__poll_t mask = 0;

	poll_रुको(file, &rbuf->queue, रुको);
	poll_रुको(file, &wbuf->queue, रुको);

	अगर (!dvb_ringbuffer_empty(rbuf))
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (dvb_ringbuffer_मुक्त(wbuf) >= 188)
		mask |= EPOLLOUT | EPOLLWRNORM;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations ci_fops = अणु
	.owner   = THIS_MODULE,
	.पढ़ो    = ts_पढ़ो,
	.ग_लिखो   = ts_ग_लिखो,
	.खोलो    = dvb_generic_खोलो,
	.release = dvb_generic_release,
	.poll    = ts_poll,
	.mmap    = शून्य,
पूर्ण;

काष्ठा dvb_device ngene_dvbdev_ci = अणु
	.priv    = शून्य,
	.पढ़ोers = 1,
	.ग_लिखोrs = 1,
	.users   = 2,
	.fops    = &ci_fops,
पूर्ण;


/****************************************************************************/
/* DVB functions and API पूर्णांकerface ******************************************/
/****************************************************************************/

अटल व्योम swap_buffer(u32 *p, u32 len)
अणु
	जबतक (len) अणु
		*p = swab32(*p);
		p++;
		len -= 4;
	पूर्ण
पूर्ण

/* start of filler packet */
अटल u8 fill_ts[] = अणु 0x47, 0x1f, 0xff, 0x10, TS_FILLER पूर्ण;

अटल पूर्णांक tsin_find_offset(व्योम *buf, u32 len)
अणु
	पूर्णांक i, l;

	l = len - माप(fill_ts);
	अगर (l <= 0)
		वापस -1;

	क्रम (i = 0; i < l; i++) अणु
		अगर (((अक्षर *)buf)[i] == 0x47) अणु
			अगर (!स_भेद(buf + i, fill_ts, माप(fill_ts)))
				वापस i % 188;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल अंतरभूत व्योम tsin_copy_stripped(काष्ठा ngene *dev, व्योम *buf)
अणु
	अगर (स_भेद(buf, fill_ts, माप(fill_ts)) != 0) अणु
		अगर (dvb_ringbuffer_मुक्त(&dev->tsin_rbuf) >= 188) अणु
			dvb_ringbuffer_ग_लिखो(&dev->tsin_rbuf, buf, 188);
			wake_up(&dev->tsin_rbuf.queue);
		पूर्ण
	पूर्ण
पूर्ण

व्योम *tsin_exchange(व्योम *priv, व्योम *buf, u32 len, u32 घड़ी, u32 flags)
अणु
	काष्ठा ngene_channel *chan = priv;
	काष्ठा ngene *dev = chan->dev;
	पूर्णांक tsoff;

	अगर (flags & DF_SWAP32)
		swap_buffer(buf, len);

	अगर (dev->ci.en && chan->number == 2) अणु
		/* blindly copy buffers अगर ci_tsfix is disabled */
		अगर (!ci_tsfix) अणु
			जबतक (len >= 188) अणु
				tsin_copy_stripped(dev, buf);

				buf += 188;
				len -= 188;
			पूर्ण
			वापस शून्य;
		पूर्ण

		/* ci_tsfix = 1 */

		/*
		 * since the reमुख्यder of the TS packet which got cut off
		 * in the previous tsin_exchange() run is at the beginning
		 * of the new TS buffer, append this to the temp buffer and
		 * send it to the DVB ringbuffer afterwards.
		 */
		अगर (chan->tsin_offset) अणु
			स_नकल(&chan->tsin_buffer[(188 - chan->tsin_offset)],
			       buf, chan->tsin_offset);
			tsin_copy_stripped(dev, &chan->tsin_buffer);

			buf += chan->tsin_offset;
			len -= chan->tsin_offset;
		पूर्ण

		/*
		 * copy TS packets to the DVB ringbuffer and detect new offset
		 * shअगरts by checking क्रम a valid TS SYNC byte
		 */
		जबतक (len >= 188) अणु
			अगर (*((अक्षर *)buf) != 0x47) अणु
				/*
				 * no SYNC header, find new offset shअगरt
				 * (max. 188 bytes, tsoff will be mod 188)
				 */
				tsoff = tsin_find_offset(buf, len);
				अगर (tsoff > 0) अणु
					chan->tsin_offset += tsoff;
					chan->tsin_offset %= 188;

					buf += tsoff;
					len -= tsoff;

					dev_info(&dev->pci_dev->dev,
						 "%s(): tsin_offset shift by %d on channel %d\n",
						 __func__, tsoff,
						 chan->number);

					/*
					 * offset corrected. re-check reमुख्यing
					 * len क्रम a full TS frame, अवरोध and
					 * skip to fragment handling अगर < 188.
					 */
					अगर (len < 188)
						अवरोध;
				पूर्ण
			पूर्ण

			tsin_copy_stripped(dev, buf);

			buf += 188;
			len -= 188;
		पूर्ण

		/*
		 * अगर a fragment is left, copy to temp buffer. The reमुख्यder
		 * will be appended in the next tsin_exchange() iteration.
		 */
		अगर (len > 0 && len < 188)
			स_नकल(&chan->tsin_buffer, buf, len);

		वापस शून्य;
	पूर्ण

	अगर (chan->users > 0)
		dvb_dmx_swfilter(&chan->demux, buf, len);

	वापस शून्य;
पूर्ण

व्योम *tsout_exchange(व्योम *priv, व्योम *buf, u32 len, u32 घड़ी, u32 flags)
अणु
	काष्ठा ngene_channel *chan = priv;
	काष्ठा ngene *dev = chan->dev;
	u32 alen;

	alen = dvb_ringbuffer_avail(&dev->tsout_rbuf);
	alen -= alen % 188;

	अगर (alen < len)
		FillTSBuffer(buf + alen, len - alen, flags);
	अन्यथा
		alen = len;
	dvb_ringbuffer_पढ़ो(&dev->tsout_rbuf, buf, alen);
	अगर (flags & DF_SWAP32)
		swap_buffer((u32 *)buf, alen);
	wake_up_पूर्णांकerruptible(&dev->tsout_rbuf.queue);
	वापस buf;
पूर्ण



पूर्णांक ngene_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;
	काष्ठा ngene_channel *chan = dvbdmx->priv;

	अगर (chan->users == 0) अणु
		अगर (!chan->dev->cmd_समयout_workaround || !chan->running)
			set_transfer(chan, 1);
	पूर्ण

	वापस ++chan->users;
पूर्ण

पूर्णांक ngene_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;
	काष्ठा ngene_channel *chan = dvbdmx->priv;

	अगर (--chan->users)
		वापस chan->users;

	अगर (!chan->dev->cmd_समयout_workaround)
		set_transfer(chan, 0);

	वापस 0;
पूर्ण

पूर्णांक my_dvb_dmx_ts_card_init(काष्ठा dvb_demux *dvbdemux, अक्षर *id,
			    पूर्णांक (*start_feed)(काष्ठा dvb_demux_feed *),
			    पूर्णांक (*stop_feed)(काष्ठा dvb_demux_feed *),
			    व्योम *priv)
अणु
	dvbdemux->priv = priv;

	dvbdemux->filternum = 256;
	dvbdemux->feednum = 256;
	dvbdemux->start_feed = start_feed;
	dvbdemux->stop_feed = stop_feed;
	dvbdemux->ग_लिखो_to_decoder = शून्य;
	dvbdemux->dmx.capabilities = (DMX_TS_FILTERING |
				      DMX_SECTION_FILTERING |
				      DMX_MEMORY_BASED_FILTERING);
	वापस dvb_dmx_init(dvbdemux);
पूर्ण

पूर्णांक my_dvb_dmxdev_ts_card_init(काष्ठा dmxdev *dmxdev,
			       काष्ठा dvb_demux *dvbdemux,
			       काष्ठा dmx_frontend *hw_frontend,
			       काष्ठा dmx_frontend *mem_frontend,
			       काष्ठा dvb_adapter *dvb_adapter)
अणु
	पूर्णांक ret;

	dmxdev->filternum = 256;
	dmxdev->demux = &dvbdemux->dmx;
	dmxdev->capabilities = 0;
	ret = dvb_dmxdev_init(dmxdev, dvb_adapter);
	अगर (ret < 0)
		वापस ret;

	hw_frontend->source = DMX_FRONTEND_0;
	dvbdemux->dmx.add_frontend(&dvbdemux->dmx, hw_frontend);
	mem_frontend->source = DMX_MEMORY_FE;
	dvbdemux->dmx.add_frontend(&dvbdemux->dmx, mem_frontend);
	वापस dvbdemux->dmx.connect_frontend(&dvbdemux->dmx, hw_frontend);
पूर्ण
