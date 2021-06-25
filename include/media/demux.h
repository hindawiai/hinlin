<शैली गुरु>
/*
 * demux.h
 *
 * The Kernel Digital TV Demux kABI defines a driver-पूर्णांकernal पूर्णांकerface क्रम
 * रेजिस्टरing low-level, hardware specअगरic driver to a hardware independent
 * demux layer.
 *
 * Copyright (c) 2002 Convergence GmbH
 *
 * based on code:
 * Copyright (c) 2000 Nokia Research Center
 *                    Tampere, FINLAND
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

#अगर_अघोषित __DEMUX_H
#घोषणा __DEMUX_H

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/समय.स>
#समावेश <linux/dvb/dmx.h>

/*
 * Common definitions
 */

/*
 * DMX_MAX_FILTER_SIZE: Maximum length (in bytes) of a section/PES filter.
 */

#अगर_अघोषित DMX_MAX_FILTER_SIZE
#घोषणा DMX_MAX_FILTER_SIZE 18
#पूर्ण_अगर

/*
 * DMX_MAX_SECFEED_SIZE: Maximum length (in bytes) of a निजी section feed
 * filter.
 */

#अगर_अघोषित DMX_MAX_SECTION_SIZE
#घोषणा DMX_MAX_SECTION_SIZE 4096
#पूर्ण_अगर
#अगर_अघोषित DMX_MAX_SECFEED_SIZE
#घोषणा DMX_MAX_SECFEED_SIZE (DMX_MAX_SECTION_SIZE + 188)
#पूर्ण_अगर

/*
 * TS packet reception
 */

/**
 * क्रमागत ts_filter_type - filter type biपंचांगap क्रम dmx_ts_feed.set\(\)
 *
 * @TS_PACKET:		Send TS packets (188 bytes) to callback (शेष).
 * @TS_PAYLOAD_ONLY:	In हाल TS_PACKET is set, only send the TS payload
 *			(<=184 bytes per packet) to callback
 * @TS_DECODER:		Send stream to built-in decoder (अगर present).
 * @TS_DEMUX:		In हाल TS_PACKET is set, send the TS to the demux
 *			device, not to the dvr device
 */
क्रमागत ts_filter_type अणु
	TS_PACKET = 1,
	TS_PAYLOAD_ONLY = 2,
	TS_DECODER = 4,
	TS_DEMUX = 8,
पूर्ण;

/**
 * काष्ठा dmx_ts_feed - Structure that contains a TS feed filter
 *
 * @is_filtering:	Set to non-zero when filtering in progress
 * @parent:		poपूर्णांकer to काष्ठा dmx_demux
 * @priv:		poपूर्णांकer to निजी data of the API client
 * @set:		sets the TS filter
 * @start_filtering:	starts TS filtering
 * @stop_filtering:	stops TS filtering
 *
 * A TS feed is typically mapped to a hardware PID filter on the demux chip.
 * Using this API, the client can set the filtering properties to start/stop
 * filtering TS packets on a particular TS feed.
 */
काष्ठा dmx_ts_feed अणु
	पूर्णांक is_filtering;
	काष्ठा dmx_demux *parent;
	व्योम *priv;
	पूर्णांक (*set)(काष्ठा dmx_ts_feed *feed,
		   u16 pid,
		   पूर्णांक type,
		   क्रमागत dmx_ts_pes pes_type,
		   kसमय_प्रकार समयout);
	पूर्णांक (*start_filtering)(काष्ठा dmx_ts_feed *feed);
	पूर्णांक (*stop_filtering)(काष्ठा dmx_ts_feed *feed);
पूर्ण;

/*
 * Section reception
 */

/**
 * काष्ठा dmx_section_filter - Structure that describes a section filter
 *
 * @filter_value: Contains up to 16 bytes (128 bits) of the TS section header
 *		  that will be matched by the section filter
 * @filter_mask:  Contains a 16 bytes (128 bits) filter mask with the bits
 *		  specअगरied by @filter_value that will be used on the filter
 *		  match logic.
 * @filter_mode:  Contains a 16 bytes (128 bits) filter mode.
 * @parent:	  Back-poपूर्णांकer to काष्ठा dmx_section_feed.
 * @priv:	  Poपूर्णांकer to निजी data of the API client.
 *
 *
 * The @filter_mask controls which bits of @filter_value are compared with
 * the section headers/payload. On a binary value of 1 in filter_mask, the
 * corresponding bits are compared. The filter only accepts sections that are
 * equal to filter_value in all the tested bit positions.
 */
काष्ठा dmx_section_filter अणु
	u8 filter_value[DMX_MAX_FILTER_SIZE];
	u8 filter_mask[DMX_MAX_FILTER_SIZE];
	u8 filter_mode[DMX_MAX_FILTER_SIZE];
	काष्ठा dmx_section_feed *parent;

	व्योम *priv;
पूर्ण;

/**
 * काष्ठा dmx_section_feed - Structure that contains a section feed filter
 *
 * @is_filtering:	Set to non-zero when filtering in progress
 * @parent:		poपूर्णांकer to काष्ठा dmx_demux
 * @priv:		poपूर्णांकer to निजी data of the API client
 * @check_crc:		If non-zero, check the CRC values of filtered sections.
 * @set:		sets the section filter
 * @allocate_filter:	This function is used to allocate a section filter on
 *			the demux. It should only be called when no filtering
 *			is in progress on this section feed. If a filter cannot
 *			be allocated, the function fails with -ENOSPC.
 * @release_filter:	This function releases all the resources of a
 *			previously allocated section filter. The function
 *			should not be called जबतक filtering is in progress
 *			on this section feed. After calling this function,
 *			the caller should not try to dereference the filter
 *			poपूर्णांकer.
 * @start_filtering:	starts section filtering
 * @stop_filtering:	stops section filtering
 *
 * A TS feed is typically mapped to a hardware PID filter on the demux chip.
 * Using this API, the client can set the filtering properties to start/stop
 * filtering TS packets on a particular TS feed.
 */
काष्ठा dmx_section_feed अणु
	पूर्णांक is_filtering;
	काष्ठा dmx_demux *parent;
	व्योम *priv;

	पूर्णांक check_crc;

	/* निजी: Used पूर्णांकernally at dvb_demux.c */
	u32 crc_val;

	u8 *secbuf;
	u8 secbuf_base[DMX_MAX_SECFEED_SIZE];
	u16 secbufp, seclen, tsfeedp;

	/* खुला: */
	पूर्णांक (*set)(काष्ठा dmx_section_feed *feed,
		   u16 pid,
		   पूर्णांक check_crc);
	पूर्णांक (*allocate_filter)(काष्ठा dmx_section_feed *feed,
			       काष्ठा dmx_section_filter **filter);
	पूर्णांक (*release_filter)(काष्ठा dmx_section_feed *feed,
			      काष्ठा dmx_section_filter *filter);
	पूर्णांक (*start_filtering)(काष्ठा dmx_section_feed *feed);
	पूर्णांक (*stop_filtering)(काष्ठा dmx_section_feed *feed);
पूर्ण;

/**
 * प्रकार dmx_ts_cb - DVB demux TS filter callback function prototype
 *
 * @buffer1:		Poपूर्णांकer to the start of the filtered TS packets.
 * @buffer1_length:	Length of the TS data in buffer1.
 * @buffer2:		Poपूर्णांकer to the tail of the filtered TS packets, or शून्य.
 * @buffer2_length:	Length of the TS data in buffer2.
 * @source:		Indicates which TS feed is the source of the callback.
 * @buffer_flags:	Address where buffer flags are stored. Those are
 *			used to report discontinuity users via DVB
 *			memory mapped API, as defined by
 *			&क्रमागत dmx_buffer_flags.
 *
 * This function callback prototype, provided by the client of the demux API,
 * is called from the demux code. The function is only called when filtering
 * on a TS feed has been enabled using the start_filtering\(\) function at
 * the &dmx_demux.
 * Any TS packets that match the filter settings are copied to a circular
 * buffer. The filtered TS packets are delivered to the client using this
 * callback function.
 * It is expected that the @buffer1 and @buffer2 callback parameters poपूर्णांक to
 * addresses within the circular buffer, but other implementations are also
 * possible. Note that the called party should not try to मुक्त the memory
 * the @buffer1 and @buffer2 parameters poपूर्णांक to.
 *
 * When this function is called, the @buffer1 parameter typically poपूर्णांकs to
 * the start of the first undelivered TS packet within a circular buffer.
 * The @buffer2 buffer parameter is normally शून्य, except when the received
 * TS packets have crossed the last address of the circular buffer and
 * "wrapped" to the beginning of the buffer. In the latter हाल the @buffer1
 * parameter would contain an address within the circular buffer, जबतक the
 * @buffer2 parameter would contain the first address of the circular buffer.
 * The number of bytes delivered with this function (i.e. @buffer1_length +
 * @buffer2_length) is usually equal to the value of callback_length parameter
 * given in the set() function, with one exception: अगर a समयout occurs beक्रमe
 * receiving callback_length bytes of TS data, any undelivered packets are
 * immediately delivered to the client by calling this function. The समयout
 * duration is controlled by the set() function in the TS Feed API.
 *
 * If a TS packet is received with errors that could not be fixed by the
 * TS-level क्रमward error correction (FEC), the Transport_error_indicator
 * flag of the TS packet header should be set. The TS packet should not be
 * discarded, as the error can possibly be corrected by a higher layer
 * protocol. If the called party is slow in processing the callback, it
 * is possible that the circular buffer eventually fills up. If this happens,
 * the demux driver should discard any TS packets received जबतक the buffer
 * is full and वापस -EOVERFLOW.
 *
 * The type of data वापसed to the callback can be selected by the
 * &dmx_ts_feed.@set function. The type parameter decides अगर the raw
 * TS packet (TS_PACKET) or just the payload (TS_PACKET|TS_PAYLOAD_ONLY)
 * should be वापसed. If additionally the TS_DECODER bit is set the stream
 * will also be sent to the hardware MPEG decoder.
 *
 * Return:
 *
 * - 0, on success;
 *
 * - -EOVERFLOW, on buffer overflow.
 */
प्रकार पूर्णांक (*dmx_ts_cb)(स्थिर u8 *buffer1,
			 माप_प्रकार buffer1_length,
			 स्थिर u8 *buffer2,
			 माप_प्रकार buffer2_length,
			 काष्ठा dmx_ts_feed *source,
			 u32 *buffer_flags);

/**
 * प्रकार dmx_section_cb - DVB demux TS filter callback function prototype
 *
 * @buffer1:		Poपूर्णांकer to the start of the filtered section, e.g.
 *			within the circular buffer of the demux driver.
 * @buffer1_len:	Length of the filtered section data in @buffer1,
 *			including headers and CRC.
 * @buffer2:		Poपूर्णांकer to the tail of the filtered section data,
 *			or शून्य. Useful to handle the wrapping of a
 *			circular buffer.
 * @buffer2_len:	Length of the filtered section data in @buffer2,
 *			including headers and CRC.
 * @source:		Indicates which section feed is the source of the
 *			callback.
 * @buffer_flags:	Address where buffer flags are stored. Those are
 *			used to report discontinuity users via DVB
 *			memory mapped API, as defined by
 *			&क्रमागत dmx_buffer_flags.
 *
 * This function callback prototype, provided by the client of the demux API,
 * is called from the demux code. The function is only called when
 * filtering of sections has been enabled using the function
 * &dmx_ts_feed.@start_filtering. When the demux driver has received a
 * complete section that matches at least one section filter, the client
 * is notअगरied via this callback function. Normally this function is called
 * क्रम each received section; however, it is also possible to deliver
 * multiple sections with one callback, क्रम example when the प्रणाली load
 * is high. If an error occurs जबतक receiving a section, this
 * function should be called with the corresponding error type set in the
 * success field, whether or not there is data to deliver. The Section Feed
 * implementation should मुख्यtain a circular buffer क्रम received sections.
 * However, this is not necessary अगर the Section Feed API is implemented as
 * a client of the TS Feed API, because the TS Feed implementation then
 * buffers the received data. The size of the circular buffer can be
 * configured using the &dmx_ts_feed.@set function in the Section Feed API.
 * If there is no room in the circular buffer when a new section is received,
 * the section must be discarded. If this happens, the value of the success
 * parameter should be DMX_OVERRUN_ERROR on the next callback.
 */
प्रकार पूर्णांक (*dmx_section_cb)(स्थिर u8 *buffer1,
			      माप_प्रकार buffer1_len,
			      स्थिर u8 *buffer2,
			      माप_प्रकार buffer2_len,
			      काष्ठा dmx_section_filter *source,
			      u32 *buffer_flags);

/*
 * DVB Front-End
 */

/**
 * क्रमागत dmx_frontend_source - Used to identअगरy the type of frontend
 *
 * @DMX_MEMORY_FE:	The source of the demux is memory. It means that
 *			the MPEG-TS to be filtered comes from userspace,
 *			via ग_लिखो() syscall.
 *
 * @DMX_FRONTEND_0:	The source of the demux is a frontend connected
 *			to the demux.
 */
क्रमागत dmx_frontend_source अणु
	DMX_MEMORY_FE,
	DMX_FRONTEND_0,
पूर्ण;

/**
 * काष्ठा dmx_frontend - Structure that lists the frontends associated with
 *			 a demux
 *
 * @connectivity_list:	List of front-ends that can be connected to a
 *			particular demux;
 * @source:		Type of the frontend.
 *
 * FIXME: this काष्ठाure should likely be replaced soon by some
 *	media-controller based logic.
 */
काष्ठा dmx_frontend अणु
	काष्ठा list_head connectivity_list;
	क्रमागत dmx_frontend_source source;
पूर्ण;

/*
 * MPEG-2 TS Demux
 */

/**
 * क्रमागत dmx_demux_caps - MPEG-2 TS Demux capabilities biपंचांगap
 *
 * @DMX_TS_FILTERING:		set अगर TS filtering is supported;
 * @DMX_SECTION_FILTERING:	set अगर section filtering is supported;
 * @DMX_MEMORY_BASED_FILTERING:	set अगर ग_लिखो() available.
 *
 * Those flags are OR'ed in the &dmx_demux.capabilities field
 */
क्रमागत dmx_demux_caps अणु
	DMX_TS_FILTERING = 1,
	DMX_SECTION_FILTERING = 4,
	DMX_MEMORY_BASED_FILTERING = 8,
पूर्ण;

/*
 * Demux resource type identअगरier.
 */

/**
 * DMX_FE_ENTRY - Casts elements in the list of रेजिस्टरed
 *		  front-ends from the generic type काष्ठा list_head
 *		  to the type * काष्ठा dmx_frontend
 *
 * @list: list of काष्ठा dmx_frontend
 */
#घोषणा DMX_FE_ENTRY(list) \
	list_entry(list, काष्ठा dmx_frontend, connectivity_list)

/**
 * काष्ठा dmx_demux - Structure that contains the demux capabilities and
 *		      callbacks.
 *
 * @capabilities: Bitfield of capability flags.
 *
 * @frontend: Front-end connected to the demux
 *
 * @priv: Poपूर्णांकer to निजी data of the API client
 *
 * @खोलो: This function reserves the demux क्रम use by the caller and, अगर
 *	necessary, initializes the demux. When the demux is no दीर्घer needed,
 *	the function @बंद should be called. It should be possible क्रम
 *	multiple clients to access the demux at the same समय. Thus, the
 *	function implementation should increment the demux usage count when
 *	@खोलो is called and decrement it when @बंद is called.
 *	The @demux function parameter contains a poपूर्णांकer to the demux API and
 *	instance data.
 *	It वापसs:
 *	0 on success;
 *	-EUSERS, अगर maximum usage count was reached;
 *	-EINVAL, on bad parameter.
 *
 * @बंद: This function reserves the demux क्रम use by the caller and, अगर
 *	necessary, initializes the demux. When the demux is no दीर्घer needed,
 *	the function @बंद should be called. It should be possible क्रम
 *	multiple clients to access the demux at the same समय. Thus, the
 *	function implementation should increment the demux usage count when
 *	@खोलो is called and decrement it when @बंद is called.
 *	The @demux function parameter contains a poपूर्णांकer to the demux API and
 *	instance data.
 *	It वापसs:
 *	0 on success;
 *	-ENODEV, अगर demux was not in use (e. g. no users);
 *	-EINVAL, on bad parameter.
 *
 * @ग_लिखो: This function provides the demux driver with a memory buffer
 *	containing TS packets. Instead of receiving TS packets from the DVB
 *	front-end, the demux driver software will पढ़ो packets from memory.
 *	Any clients of this demux with active TS, PES or Section filters will
 *	receive filtered data via the Demux callback API (see 0). The function
 *	वापसs when all the data in the buffer has been consumed by the demux.
 *	Demux hardware typically cannot पढ़ो TS from memory. If this is the
 *	हाल, memory-based filtering has to be implemented entirely in software.
 *	The @demux function parameter contains a poपूर्णांकer to the demux API and
 *	instance data.
 *	The @buf function parameter contains a poपूर्णांकer to the TS data in
 *	kernel-space memory.
 *	The @count function parameter contains the length of the TS data.
 *	It वापसs:
 *	0 on success;
 *	-ERESTARTSYS, अगर mutex lock was पूर्णांकerrupted;
 *	-EINTR, अगर a संकेत handling is pending;
 *	-ENODEV, अगर demux was हटाओd;
 *	-EINVAL, on bad parameter.
 *
 * @allocate_ts_feed: Allocates a new TS feed, which is used to filter the TS
 *	packets carrying a certain PID. The TS feed normally corresponds to a
 *	hardware PID filter on the demux chip.
 *	The @demux function parameter contains a poपूर्णांकer to the demux API and
 *	instance data.
 *	The @feed function parameter contains a poपूर्णांकer to the TS feed API and
 *	instance data.
 *	The @callback function parameter contains a poपूर्णांकer to the callback
 *	function क्रम passing received TS packet.
 *	It वापसs:
 *	0 on success;
 *	-ERESTARTSYS, अगर mutex lock was पूर्णांकerrupted;
 *	-EBUSY, अगर no more TS feeds is available;
 *	-EINVAL, on bad parameter.
 *
 * @release_ts_feed: Releases the resources allocated with @allocate_ts_feed.
 *	Any filtering in progress on the TS feed should be stopped beक्रमe
 *	calling this function.
 *	The @demux function parameter contains a poपूर्णांकer to the demux API and
 *	instance data.
 *	The @feed function parameter contains a poपूर्णांकer to the TS feed API and
 *	instance data.
 *	It वापसs:
 *	0 on success;
 *	-EINVAL on bad parameter.
 *
 * @allocate_section_feed: Allocates a new section feed, i.e. a demux resource
 *	क्रम filtering and receiving sections. On platक्रमms with hardware
 *	support क्रम section filtering, a section feed is directly mapped to
 *	the demux HW. On other platक्रमms, TS packets are first PID filtered in
 *	hardware and a hardware section filter then emulated in software. The
 *	caller obtains an API poपूर्णांकer of type dmx_section_feed_t as an out
 *	parameter. Using this API the caller can set filtering parameters and
 *	start receiving sections.
 *	The @demux function parameter contains a poपूर्णांकer to the demux API and
 *	instance data.
 *	The @feed function parameter contains a poपूर्णांकer to the TS feed API and
 *	instance data.
 *	The @callback function parameter contains a poपूर्णांकer to the callback
 *	function क्रम passing received TS packet.
 *	It वापसs:
 *	0 on success;
 *	-EBUSY, अगर no more TS feeds is available;
 *	-EINVAL, on bad parameter.
 *
 * @release_section_feed: Releases the resources allocated with
 *	@allocate_section_feed, including allocated filters. Any filtering in
 *	progress on the section feed should be stopped beक्रमe calling this
 *	function.
 *	The @demux function parameter contains a poपूर्णांकer to the demux API and
 *	instance data.
 *	The @feed function parameter contains a poपूर्णांकer to the TS feed API and
 *	instance data.
 *	It वापसs:
 *	0 on success;
 *	-EINVAL, on bad parameter.
 *
 * @add_frontend: Registers a connectivity between a demux and a front-end,
 *	i.e., indicates that the demux can be connected via a call to
 *	@connect_frontend to use the given front-end as a TS source. The
 *	client of this function has to allocate dynamic or अटल memory क्रम
 *	the frontend काष्ठाure and initialize its fields beक्रमe calling this
 *	function. This function is normally called during the driver
 *	initialization. The caller must not मुक्त the memory of the frontend
 *	काष्ठा beक्रमe successfully calling @हटाओ_frontend.
 *	The @demux function parameter contains a poपूर्णांकer to the demux API and
 *	instance data.
 *	The @frontend function parameter contains a poपूर्णांकer to the front-end
 *	instance data.
 *	It वापसs:
 *	0 on success;
 *	-EINVAL, on bad parameter.
 *
 * @हटाओ_frontend: Indicates that the given front-end, रेजिस्टरed by a call
 *	to @add_frontend, can no दीर्घer be connected as a TS source by this
 *	demux. The function should be called when a front-end driver or a demux
 *	driver is हटाओd from the प्रणाली. If the front-end is in use, the
 *	function fails with the वापस value of -EBUSY. After successfully
 *	calling this function, the caller can मुक्त the memory of the frontend
 *	काष्ठा अगर it was dynamically allocated beक्रमe the @add_frontend
 *	operation.
 *	The @demux function parameter contains a poपूर्णांकer to the demux API and
 *	instance data.
 *	The @frontend function parameter contains a poपूर्णांकer to the front-end
 *	instance data.
 *	It वापसs:
 *	0 on success;
 *	-ENODEV, अगर the front-end was not found,
 *	-EINVAL, on bad parameter.
 *
 * @get_frontends: Provides the APIs of the front-ends that have been
 *	रेजिस्टरed क्रम this demux. Any of the front-ends obtained with this
 *	call can be used as a parameter क्रम @connect_frontend. The include
 *	file demux.h contains the macro DMX_FE_ENTRY() क्रम converting an
 *	element of the generic type काष्ठा &list_head * to the type
 *	काष्ठा &dmx_frontend *. The caller must not मुक्त the memory of any of
 *	the elements obtained via this function call.
 *	The @demux function parameter contains a poपूर्णांकer to the demux API and
 *	instance data.
 *	It वापसs a काष्ठा list_head poपूर्णांकer to the list of front-end
 *	पूर्णांकerfaces, or शून्य in the हाल of an empty list.
 *
 * @connect_frontend: Connects the TS output of the front-end to the input of
 *	the demux. A demux can only be connected to a front-end रेजिस्टरed to
 *	the demux with the function @add_frontend. It may or may not be
 *	possible to connect multiple demuxes to the same front-end, depending
 *	on the capabilities of the HW platक्रमm. When not used, the front-end
 *	should be released by calling @disconnect_frontend.
 *	The @demux function parameter contains a poपूर्णांकer to the demux API and
 *	instance data.
 *	The @frontend function parameter contains a poपूर्णांकer to the front-end
 *	instance data.
 *	It वापसs:
 *	0 on success;
 *	-EINVAL, on bad parameter.
 *
 * @disconnect_frontend: Disconnects the demux and a front-end previously
 *	connected by a @connect_frontend call.
 *	The @demux function parameter contains a poपूर्णांकer to the demux API and
 *	instance data.
 *	It वापसs:
 *	0 on success;
 *	-EINVAL on bad parameter.
 *
 * @get_pes_pids: Get the PIDs क्रम DMX_PES_AUDIO0, DMX_PES_VIDEO0,
 *	DMX_PES_TELETEXT0, DMX_PES_SUBTITLE0 and DMX_PES_PCR0.
 *	The @demux function parameter contains a poपूर्णांकer to the demux API and
 *	instance data.
 *	The @pids function parameter contains an array with five u16 elements
 *	where the PIDs will be stored.
 *	It वापसs:
 *	0 on success;
 *	-EINVAL on bad parameter.
 */
काष्ठा dmx_demux अणु
	क्रमागत dmx_demux_caps capabilities;
	काष्ठा dmx_frontend *frontend;
	व्योम *priv;
	पूर्णांक (*खोलो)(काष्ठा dmx_demux *demux);
	पूर्णांक (*बंद)(काष्ठा dmx_demux *demux);
	पूर्णांक (*ग_लिखो)(काष्ठा dmx_demux *demux, स्थिर अक्षर __user *buf,
		     माप_प्रकार count);
	पूर्णांक (*allocate_ts_feed)(काष्ठा dmx_demux *demux,
				काष्ठा dmx_ts_feed **feed,
				dmx_ts_cb callback);
	पूर्णांक (*release_ts_feed)(काष्ठा dmx_demux *demux,
			       काष्ठा dmx_ts_feed *feed);
	पूर्णांक (*allocate_section_feed)(काष्ठा dmx_demux *demux,
				     काष्ठा dmx_section_feed **feed,
				     dmx_section_cb callback);
	पूर्णांक (*release_section_feed)(काष्ठा dmx_demux *demux,
				    काष्ठा dmx_section_feed *feed);
	पूर्णांक (*add_frontend)(काष्ठा dmx_demux *demux,
			    काष्ठा dmx_frontend *frontend);
	पूर्णांक (*हटाओ_frontend)(काष्ठा dmx_demux *demux,
			       काष्ठा dmx_frontend *frontend);
	काष्ठा list_head *(*get_frontends)(काष्ठा dmx_demux *demux);
	पूर्णांक (*connect_frontend)(काष्ठा dmx_demux *demux,
				काष्ठा dmx_frontend *frontend);
	पूर्णांक (*disconnect_frontend)(काष्ठा dmx_demux *demux);

	पूर्णांक (*get_pes_pids)(काष्ठा dmx_demux *demux, u16 *pids);

	/* निजी: */

	/*
	 * Only used at av7110, to पढ़ो some data from firmware.
	 * As this was never करोcumented, we have no clue about what's
	 * there, and its usage on other drivers aren't encouraged.
	 */
	पूर्णांक (*get_stc)(काष्ठा dmx_demux *demux, अचिन्हित पूर्णांक num,
		       u64 *stc, अचिन्हित पूर्णांक *base);
पूर्ण;

#पूर्ण_अगर /* #अगर_अघोषित __DEMUX_H */
