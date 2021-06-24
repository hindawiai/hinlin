<शैली गुरु>
/*
 * dvb_demux.h: DVB kernel demux API
 *
 * Copyright (C) 2000-2001 Marcus Metzler & Ralph Metzler
 *                         क्रम convergence पूर्णांकegrated media GmbH
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

#अगर_अघोषित _DVB_DEMUX_H_
#घोषणा _DVB_DEMUX_H_

#समावेश <linux/समय.स>
#समावेश <linux/समयr.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>

#समावेश <media/demux.h>

/**
 * क्रमागत dvb_dmx_filter_type - type of demux feed.
 *
 * @DMX_TYPE_TS:	feed is in TS mode.
 * @DMX_TYPE_SEC:	feed is in Section mode.
 */
क्रमागत dvb_dmx_filter_type अणु
	DMX_TYPE_TS,
	DMX_TYPE_SEC,
पूर्ण;

/**
 * क्रमागत dvb_dmx_state - state machine क्रम a demux filter.
 *
 * @DMX_STATE_FREE:		indicates that the filter is मुक्तd.
 * @DMX_STATE_ALLOCATED:	indicates that the filter was allocated
 *				to be used.
 * @DMX_STATE_READY:		indicates that the filter is पढ़ोy
 *				to be used.
 * @DMX_STATE_GO:		indicates that the filter is running.
 */
क्रमागत dvb_dmx_state अणु
	DMX_STATE_FREE,
	DMX_STATE_ALLOCATED,
	DMX_STATE_READY,
	DMX_STATE_GO,
पूर्ण;

#घोषणा DVB_DEMUX_MASK_MAX 18

#घोषणा MAX_PID 0x1fff

#घोषणा SPEED_PKTS_INTERVAL 50000

/**
 * काष्ठा dvb_demux_filter - Describes a DVB demux section filter.
 *
 * @filter:		Section filter as defined by &काष्ठा dmx_section_filter.
 * @maskandmode:	logical ``and`` bit mask.
 * @maskandnoपंचांगode:	logical ``and not`` bit mask.
 * @करोneq:		flag that indicates when a filter is पढ़ोy.
 * @next:		poपूर्णांकer to the next section filter.
 * @feed:		&काष्ठा dvb_demux_feed poपूर्णांकer.
 * @index:		index of the used demux filter.
 * @state:		state of the filter as described by &क्रमागत dvb_dmx_state.
 * @type:		type of the filter as described
 *			by &क्रमागत dvb_dmx_filter_type.
 */

काष्ठा dvb_demux_filter अणु
	काष्ठा dmx_section_filter filter;
	u8 maskandmode[DMX_MAX_FILTER_SIZE];
	u8 maskandnoपंचांगode[DMX_MAX_FILTER_SIZE];
	bool करोneq;

	काष्ठा dvb_demux_filter *next;
	काष्ठा dvb_demux_feed *feed;
	पूर्णांक index;
	क्रमागत dvb_dmx_state state;
	क्रमागत dvb_dmx_filter_type type;

	/* निजी: used only by av7110 */
	u16 hw_handle;
पूर्ण;

/**
 * काष्ठा dvb_demux_feed - describes a DVB field
 *
 * @feed:	a जोड़ describing a digital TV feed.
 *		Depending on the feed type, it can be either
 *		@feed.ts or @feed.sec.
 * @feed.ts:	a &काष्ठा dmx_ts_feed poपूर्णांकer.
 *		For TS feed only.
 * @feed.sec:	a &काष्ठा dmx_section_feed poपूर्णांकer.
 *		For section feed only.
 * @cb:		a जोड़ describing digital TV callbacks.
 *		Depending on the feed type, it can be either
 *		@cb.ts or @cb.sec.
 * @cb.ts:	a dmx_ts_cb() calback function poपूर्णांकer.
 *		For TS feed only.
 * @cb.sec:	a dmx_section_cb() callback function poपूर्णांकer.
 *		For section feed only.
 * @demux:	poपूर्णांकer to &काष्ठा dvb_demux.
 * @priv:	निजी data that can optionally be used by a DVB driver.
 * @type:	type of the filter, as defined by &क्रमागत dvb_dmx_filter_type.
 * @state:	state of the filter as defined by &क्रमागत dvb_dmx_state.
 * @pid:	PID to be filtered.
 * @समयout:	feed समयout.
 * @filter:	poपूर्णांकer to &काष्ठा dvb_demux_filter.
 * @buffer_flags: Buffer flags used to report discontinuity users via DVB
 *		  memory mapped API, as defined by &क्रमागत dmx_buffer_flags.
 * @ts_type:	type of TS, as defined by &क्रमागत ts_filter_type.
 * @pes_type:	type of PES, as defined by &क्रमागत dmx_ts_pes.
 * @cc:		MPEG-TS packet continuity counter
 * @pusi_seen:	अगर true, indicates that a discontinuity was detected.
 *		it is used to prevent feeding of garbage from previous section.
 * @peslen:	length of the PES (Packet Elementary Stream).
 * @list_head:	head क्रम the list of digital TV demux feeds.
 * @index:	a unique index क्रम each feed. Can be used as hardware
 *		pid filter index.
 */
काष्ठा dvb_demux_feed अणु
	जोड़ अणु
		काष्ठा dmx_ts_feed ts;
		काष्ठा dmx_section_feed sec;
	पूर्ण feed;

	जोड़ अणु
		dmx_ts_cb ts;
		dmx_section_cb sec;
	पूर्ण cb;

	काष्ठा dvb_demux *demux;
	व्योम *priv;
	क्रमागत dvb_dmx_filter_type type;
	क्रमागत dvb_dmx_state state;
	u16 pid;

	kसमय_प्रकार समयout;
	काष्ठा dvb_demux_filter *filter;

	u32 buffer_flags;

	क्रमागत ts_filter_type ts_type;
	क्रमागत dmx_ts_pes pes_type;

	पूर्णांक cc;
	bool pusi_seen;

	u16 peslen;

	काष्ठा list_head list_head;
	अचिन्हित पूर्णांक index;
पूर्ण;

/**
 * काष्ठा dvb_demux - represents a digital TV demux
 * @dmx:		embedded &काष्ठा dmx_demux with demux capabilities
 *			and callbacks.
 * @priv:		निजी data that can optionally be used by
 *			a DVB driver.
 * @filternum:		maximum amount of DVB filters.
 * @feednum:		maximum amount of DVB feeds.
 * @start_feed:		callback routine to be called in order to start
 *			a DVB feed.
 * @stop_feed:		callback routine to be called in order to stop
 *			a DVB feed.
 * @ग_लिखो_to_decoder:	callback routine to be called अगर the feed is TS and
 *			it is routed to an A/V decoder, when a new TS packet
 *			is received.
 *			Used only on av7110-av.c.
 * @check_crc32:	callback routine to check CRC. If not initialized,
 *			dvb_demux will use an पूर्णांकernal one.
 * @memcopy:		callback routine to memcopy received data.
 *			If not initialized, dvb_demux will शेष to स_नकल().
 * @users:		counter क्रम the number of demux खोलोed file descriptors.
 *			Currently, it is limited to 10 users.
 * @filter:		poपूर्णांकer to &काष्ठा dvb_demux_filter.
 * @feed:		poपूर्णांकer to &काष्ठा dvb_demux_feed.
 * @frontend_list:	&काष्ठा list_head with frontends used by the demux.
 * @pesfilter:		array of &काष्ठा dvb_demux_feed with the PES types
 *			that will be filtered.
 * @pids:		list of filtered program IDs.
 * @feed_list:		&काष्ठा list_head with feeds.
 * @tsbuf:		temporary buffer used पूर्णांकernally to store TS packets.
 * @tsbufp:		temporary buffer index used पूर्णांकernally.
 * @mutex:		poपूर्णांकer to &काष्ठा mutex used to protect feed set
 *			logic.
 * @lock:		poपूर्णांकer to &spinlock_t, used to protect buffer handling.
 * @cnt_storage:	buffer used क्रम TS/TEI continuity check.
 * @speed_last_समय:	&kसमय_प्रकार used क्रम TS speed check.
 * @speed_pkts_cnt:	packets count used क्रम TS speed check.
 */
काष्ठा dvb_demux अणु
	काष्ठा dmx_demux dmx;
	व्योम *priv;
	पूर्णांक filternum;
	पूर्णांक feednum;
	पूर्णांक (*start_feed)(काष्ठा dvb_demux_feed *feed);
	पूर्णांक (*stop_feed)(काष्ठा dvb_demux_feed *feed);
	पूर्णांक (*ग_लिखो_to_decoder)(काष्ठा dvb_demux_feed *feed,
				 स्थिर u8 *buf, माप_प्रकार len);
	u32 (*check_crc32)(काष्ठा dvb_demux_feed *feed,
			    स्थिर u8 *buf, माप_प्रकार len);
	व्योम (*memcopy)(काष्ठा dvb_demux_feed *feed, u8 *dst,
			 स्थिर u8 *src, माप_प्रकार len);

	पूर्णांक users;
#घोषणा MAX_DVB_DEMUX_USERS 10
	काष्ठा dvb_demux_filter *filter;
	काष्ठा dvb_demux_feed *feed;

	काष्ठा list_head frontend_list;

	काष्ठा dvb_demux_feed *pesfilter[DMX_PES_OTHER];
	u16 pids[DMX_PES_OTHER];

#घोषणा DMX_MAX_PID 0x2000
	काष्ठा list_head feed_list;
	u8 tsbuf[204];
	पूर्णांक tsbufp;

	काष्ठा mutex mutex;
	spinlock_t lock;

	uपूर्णांक8_t *cnt_storage; /* क्रम TS continuity check */

	kसमय_प्रकार speed_last_समय; /* क्रम TS speed check */
	uपूर्णांक32_t speed_pkts_cnt; /* क्रम TS speed check */

	/* निजी: used only on av7110 */
	पूर्णांक playing;
	पूर्णांक recording;
पूर्ण;

/**
 * dvb_dmx_init - initialize a digital TV demux काष्ठा.
 *
 * @demux: &काष्ठा dvb_demux to be initialized.
 *
 * Beक्रमe being able to रेजिस्टर a digital TV demux काष्ठा, drivers
 * should call this routine. On its typical usage, some fields should
 * be initialized at the driver beक्रमe calling it.
 *
 * A typical useहाल is::
 *
 *	dvb->demux.dmx.capabilities =
 *		DMX_TS_FILTERING | DMX_SECTION_FILTERING |
 *		DMX_MEMORY_BASED_FILTERING;
 *	dvb->demux.priv       = dvb;
 *	dvb->demux.filternum  = 256;
 *	dvb->demux.feednum    = 256;
 *	dvb->demux.start_feed = driver_start_feed;
 *	dvb->demux.stop_feed  = driver_stop_feed;
 *	ret = dvb_dmx_init(&dvb->demux);
 *	अगर (ret < 0)
 *		वापस ret;
 */
पूर्णांक dvb_dmx_init(काष्ठा dvb_demux *demux);

/**
 * dvb_dmx_release - releases a digital TV demux पूर्णांकernal buffers.
 *
 * @demux: &काष्ठा dvb_demux to be released.
 *
 * The DVB core पूर्णांकernally allocates data at @demux. This routine
 * releases those data. Please notice that the काष्ठा itelf is not
 * released, as it can be embedded on other काष्ठाs.
 */
व्योम dvb_dmx_release(काष्ठा dvb_demux *demux);

/**
 * dvb_dmx_swfilter_packets - use dvb software filter क्रम a buffer with
 *	multiple MPEG-TS packets with 188 bytes each.
 *
 * @demux: poपूर्णांकer to &काष्ठा dvb_demux
 * @buf: buffer with data to be filtered
 * @count: number of MPEG-TS packets with size of 188.
 *
 * The routine will discard a DVB packet that करोn't start with 0x47.
 *
 * Use this routine अगर the DVB demux fills MPEG-TS buffers that are
 * alपढ़ोy aligned.
 *
 * NOTE: The @buf size should have size equal to ``count * 188``.
 */
व्योम dvb_dmx_swfilter_packets(काष्ठा dvb_demux *demux, स्थिर u8 *buf,
			      माप_प्रकार count);

/**
 * dvb_dmx_swfilter -  use dvb software filter क्रम a buffer with
 *	multiple MPEG-TS packets with 188 bytes each.
 *
 * @demux: poपूर्णांकer to &काष्ठा dvb_demux
 * @buf: buffer with data to be filtered
 * @count: number of MPEG-TS packets with size of 188.
 *
 * If a DVB packet करोesn't start with 0x47, it will seek क्रम the first
 * byte that starts with 0x47.
 *
 * Use this routine अगर the DVB demux fill buffers that may not start with
 * a packet start mark (0x47).
 *
 * NOTE: The @buf size should have size equal to ``count * 188``.
 */
व्योम dvb_dmx_swfilter(काष्ठा dvb_demux *demux, स्थिर u8 *buf, माप_प्रकार count);

/**
 * dvb_dmx_swfilter_204 -  use dvb software filter क्रम a buffer with
 *	multiple MPEG-TS packets with 204 bytes each.
 *
 * @demux: poपूर्णांकer to &काष्ठा dvb_demux
 * @buf: buffer with data to be filtered
 * @count: number of MPEG-TS packets with size of 204.
 *
 * If a DVB packet करोesn't start with 0x47, it will seek क्रम the first
 * byte that starts with 0x47.
 *
 * Use this routine अगर the DVB demux fill buffers that may not start with
 * a packet start mark (0x47).
 *
 * NOTE: The @buf size should have size equal to ``count * 204``.
 */
व्योम dvb_dmx_swfilter_204(काष्ठा dvb_demux *demux, स्थिर u8 *buf,
			  माप_प्रकार count);

/**
 * dvb_dmx_swfilter_raw -  make the raw data available to userspace without
 *	filtering
 *
 * @demux: poपूर्णांकer to &काष्ठा dvb_demux
 * @buf: buffer with data
 * @count: number of packets to be passed. The actual size of each packet
 *	depends on the &dvb_demux->feed->cb.ts logic.
 *
 * Use it अगर the driver needs to deliver the raw payload to userspace without
 * passing through the kernel demux. That is meant to support some
 * delivery प्रणालीs that aren't based on MPEG-TS.
 *
 * This function relies on &dvb_demux->feed->cb.ts to actually handle the
 * buffer.
 */
व्योम dvb_dmx_swfilter_raw(काष्ठा dvb_demux *demux, स्थिर u8 *buf,
			  माप_प्रकार count);

#पूर्ण_अगर /* _DVB_DEMUX_H_ */
