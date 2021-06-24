<शैली गुरु>
/*
 * dmxdev.h
 *
 * Copyright (C) 2000 Ralph Metzler & Marcus Metzler
 *                    क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#अगर_अघोषित _DMXDEV_H_
#घोषणा _DMXDEV_H_

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयr.h>
#समावेश <linux/रुको.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

#समावेश <linux/dvb/dmx.h>

#समावेश <media/dvbdev.h>
#समावेश <media/demux.h>
#समावेश <media/dvb_ringbuffer.h>
#समावेश <media/dvb_vb2.h>

/**
 * क्रमागत dmxdev_type - type of demux filter type.
 *
 * @DMXDEV_TYPE_NONE:	no filter set.
 * @DMXDEV_TYPE_SEC:	section filter.
 * @DMXDEV_TYPE_PES:	Program Elementary Stream (PES) filter.
 */
क्रमागत dmxdev_type अणु
	DMXDEV_TYPE_NONE,
	DMXDEV_TYPE_SEC,
	DMXDEV_TYPE_PES,
पूर्ण;

/**
 * क्रमागत dmxdev_state - state machine क्रम the dmxdev.
 *
 * @DMXDEV_STATE_FREE:		indicates that the filter is मुक्तd.
 * @DMXDEV_STATE_ALLOCATED:	indicates that the filter was allocated
 *				to be used.
 * @DMXDEV_STATE_SET:		indicates that the filter parameters are set.
 * @DMXDEV_STATE_GO:		indicates that the filter is running.
 * @DMXDEV_STATE_DONE:		indicates that a packet was alपढ़ोy filtered
 *				and the filter is now disabled.
 *				Set only अगर %DMX_ONESHOT. See
 *				&dmx_sct_filter_params.
 * @DMXDEV_STATE_TIMEDOUT:	Indicates a समयout condition.
 */
क्रमागत dmxdev_state अणु
	DMXDEV_STATE_FREE,
	DMXDEV_STATE_ALLOCATED,
	DMXDEV_STATE_SET,
	DMXDEV_STATE_GO,
	DMXDEV_STATE_DONE,
	DMXDEV_STATE_TIMEDOUT
पूर्ण;

/**
 * काष्ठा dmxdev_feed - digital TV dmxdev feed
 *
 * @pid:	Program ID to be filtered
 * @ts:		poपूर्णांकer to &काष्ठा dmx_ts_feed
 * @next:	&काष्ठा list_head poपूर्णांकing to the next feed.
 */

काष्ठा dmxdev_feed अणु
	u16 pid;
	काष्ठा dmx_ts_feed *ts;
	काष्ठा list_head next;
पूर्ण;

/**
 * काष्ठा dmxdev_filter - digital TV dmxdev filter
 *
 * @filter:	a जोड़ describing a dmxdev filter.
 *		Currently used only क्रम section filters.
 * @filter.sec: a &काष्ठा dmx_section_filter poपूर्णांकer.
 *		For section filter only.
 * @feed:	a जोड़ describing a dmxdev feed.
 *		Depending on the filter type, it can be either
 *		@feed.ts or @feed.sec.
 * @feed.ts:	a &काष्ठा list_head list.
 *		For TS and PES feeds.
 * @feed.sec:	a &काष्ठा dmx_section_feed poपूर्णांकer.
 *		For section feed only.
 * @params:	a जोड़ describing dmxdev filter parameters.
 *		Depending on the filter type, it can be either
 *		@params.sec or @params.pes.
 * @params.sec:	a &काष्ठा dmx_sct_filter_params embedded काष्ठा.
 *		For section filter only.
 * @params.pes:	a &काष्ठा dmx_pes_filter_params embedded काष्ठा.
 *		For PES filter only.
 * @type:	type of the dmxdev filter, as defined by &क्रमागत dmxdev_type.
 * @state:	state of the dmxdev filter, as defined by &क्रमागत dmxdev_state.
 * @dev:	poपूर्णांकer to &काष्ठा dmxdev.
 * @buffer:	an embedded &काष्ठा dvb_ringbuffer buffer.
 * @vb2_ctx:	control काष्ठा क्रम VB2 handler
 * @mutex:	protects the access to &काष्ठा dmxdev_filter.
 * @समयr:	&काष्ठा समयr_list embedded समयr, used to check क्रम
 *		feed समयouts.
 *		Only क्रम section filter.
 * @toकरो:	index क्रम the @secheader.
 *		Only क्रम section filter.
 * @secheader:	buffer cache to parse the section header.
 *		Only क्रम section filter.
 */
काष्ठा dmxdev_filter अणु
	जोड़ अणु
		काष्ठा dmx_section_filter *sec;
	पूर्ण filter;

	जोड़ अणु
		/* list of TS and PES feeds (काष्ठा dmxdev_feed) */
		काष्ठा list_head ts;
		काष्ठा dmx_section_feed *sec;
	पूर्ण feed;

	जोड़ अणु
		काष्ठा dmx_sct_filter_params sec;
		काष्ठा dmx_pes_filter_params pes;
	पूर्ण params;

	क्रमागत dmxdev_type type;
	क्रमागत dmxdev_state state;
	काष्ठा dmxdev *dev;
	काष्ठा dvb_ringbuffer buffer;
	काष्ठा dvb_vb2_ctx vb2_ctx;

	काष्ठा mutex mutex;

	/* only क्रम sections */
	काष्ठा समयr_list समयr;
	पूर्णांक toकरो;
	u8 secheader[3];
पूर्ण;

/**
 * काष्ठा dmxdev - Describes a digital TV demux device.
 *
 * @dvbdev:		poपूर्णांकer to &काष्ठा dvb_device associated with
 *			the demux device node.
 * @dvr_dvbdev:		poपूर्णांकer to &काष्ठा dvb_device associated with
 *			the dvr device node.
 * @filter:		poपूर्णांकer to &काष्ठा dmxdev_filter.
 * @demux:		poपूर्णांकer to &काष्ठा dmx_demux.
 * @filternum:		number of filters.
 * @capabilities:	demux capabilities as defined by &क्रमागत dmx_demux_caps.
 * @may_करो_mmap:	flag used to indicate अगर the device may करो mmap.
 * @निकास:		flag to indicate that the demux is being released.
 * @dvr_orig_fe:	poपूर्णांकer to &काष्ठा dmx_frontend.
 * @dvr_buffer:		embedded &काष्ठा dvb_ringbuffer क्रम DVB output.
 * @dvr_vb2_ctx:	control काष्ठा क्रम VB2 handler
 * @mutex:		protects the usage of this काष्ठाure.
 * @lock:		protects access to &dmxdev->filter->data.
 */
काष्ठा dmxdev अणु
	काष्ठा dvb_device *dvbdev;
	काष्ठा dvb_device *dvr_dvbdev;

	काष्ठा dmxdev_filter *filter;
	काष्ठा dmx_demux *demux;

	पूर्णांक filternum;
	पूर्णांक capabilities;

	अचिन्हित पूर्णांक may_करो_mmap:1;
	अचिन्हित पूर्णांक निकास:1;
#घोषणा DMXDEV_CAP_DUPLEX 1
	काष्ठा dmx_frontend *dvr_orig_fe;

	काष्ठा dvb_ringbuffer dvr_buffer;
#घोषणा DVR_BUFFER_SIZE (10*188*1024)

	काष्ठा dvb_vb2_ctx dvr_vb2_ctx;

	काष्ठा mutex mutex;
	spinlock_t lock;
पूर्ण;

/**
 * dvb_dmxdev_init - initializes a digital TV demux and रेजिस्टरs both demux
 *	and DVR devices.
 *
 * @dmxdev: poपूर्णांकer to &काष्ठा dmxdev.
 * @adap: poपूर्णांकer to &काष्ठा dvb_adapter.
 */
पूर्णांक dvb_dmxdev_init(काष्ठा dmxdev *dmxdev, काष्ठा dvb_adapter *adap);

/**
 * dvb_dmxdev_release - releases a digital TV demux and unरेजिस्टरs it.
 *
 * @dmxdev: poपूर्णांकer to &काष्ठा dmxdev.
 */
व्योम dvb_dmxdev_release(काष्ठा dmxdev *dmxdev);

#पूर्ण_अगर /* _DMXDEV_H_ */
