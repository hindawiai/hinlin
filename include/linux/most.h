<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * most.h - API क्रम component and adapter drivers
 *
 * Copyright (C) 2013-2015, Microchip Technology Germany II GmbH & Co. KG
 */

#अगर_अघोषित __MOST_CORE_H__
#घोषणा __MOST_CORE_H__

#समावेश <linux/types.h>
#समावेश <linux/device.h>

काष्ठा module;
काष्ठा पूर्णांकerface_निजी;

/**
 * Interface type
 */
क्रमागत most_पूर्णांकerface_type अणु
	ITYPE_LOOPBACK = 1,
	ITYPE_I2C,
	ITYPE_I2S,
	ITYPE_TSI,
	ITYPE_HBI,
	ITYPE_MEDIALB_DIM,
	ITYPE_MEDIALB_DIM2,
	ITYPE_USB,
	ITYPE_PCIE
पूर्ण;

/**
 * Channel direction.
 */
क्रमागत most_channel_direction अणु
	MOST_CH_RX = 1 << 0,
	MOST_CH_TX = 1 << 1,
पूर्ण;

/**
 * Channel data type.
 */
क्रमागत most_channel_data_type अणु
	MOST_CH_CONTROL = 1 << 0,
	MOST_CH_ASYNC = 1 << 1,
	MOST_CH_ISOC = 1 << 2,
	MOST_CH_SYNC = 1 << 5,
पूर्ण;

क्रमागत most_status_flags अणु
	/* MBO was processed successfully (data was send or received )*/
	MBO_SUCCESS = 0,
	/* The MBO contains wrong or missing inक्रमmation.  */
	MBO_E_INVAL,
	/* MBO was completed as HDM Channel will be बंदd */
	MBO_E_CLOSE,
पूर्ण;

/**
 * काष्ठा most_channel_capability - Channel capability
 * @direction: Supported channel directions.
 * The value is bitwise OR-combination of the values from the
 * क्रमागतeration most_channel_direction. Zero is allowed value and means
 * "channel may not be used".
 * @data_type: Supported channel data types.
 * The value is bitwise OR-combination of the values from the
 * क्रमागतeration most_channel_data_type. Zero is allowed value and means
 * "channel may not be used".
 * @num_buffers_packet: Maximum number of buffers supported by this channel
 * क्रम packet data types (Async,Control,QoS)
 * @buffer_size_packet: Maximum buffer size supported by this channel
 * क्रम packet data types (Async,Control,QoS)
 * @num_buffers_streaming: Maximum number of buffers supported by this channel
 * क्रम streaming data types (Sync,AV Packetized)
 * @buffer_size_streaming: Maximum buffer size supported by this channel
 * क्रम streaming data types (Sync,AV Packetized)
 * @name_suffix: Optional suffix providean by an HDM that is attached to the
 * regular channel name.
 *
 * Describes the capabilities of a MOST channel like supported Data Types
 * and directions. This inक्रमmation is provided by an HDM क्रम the MostCore.
 *
 * The Core creates पढ़ो only sysfs attribute files in
 * /sys/devices/most/mdev#/<channel>/ with the
 * following attributes:
 *	-available_directions
 *	-available_datatypes
 *	-number_of_packet_buffers
 *	-number_of_stream_buffers
 *	-size_of_packet_buffer
 *	-size_of_stream_buffer
 * where content of each file is a string with all supported properties of this
 * very channel attribute.
 */
काष्ठा most_channel_capability अणु
	u16 direction;
	u16 data_type;
	u16 num_buffers_packet;
	u16 buffer_size_packet;
	u16 num_buffers_streaming;
	u16 buffer_size_streaming;
	स्थिर अक्षर *name_suffix;
पूर्ण;

/**
 * काष्ठा most_channel_config - stores channel configuration
 * @direction: direction of the channel
 * @data_type: data type travelling over this channel
 * @num_buffers: number of buffers
 * @buffer_size: size of a buffer क्रम AIM.
 * Buffer size may be cutted करोwn by HDM in a configure callback
 * to match to a given पूर्णांकerface and channel type.
 * @extra_len: additional buffer space क्रम पूर्णांकernal HDM purposes like padding.
 * May be set by HDM in a configure callback अगर needed.
 * @subbuffer_size: size of a subbuffer
 * @packets_per_xact: number of MOST frames that are packet inside one USB
 *		      packet. This is USB specअगरic
 *
 * Describes the configuration क्रम a MOST channel. This inक्रमmation is
 * provided from the MostCore to a HDM (like the Medusa PCIe Interface) as a
 * parameter of the "configure" function call.
 */
काष्ठा most_channel_config अणु
	क्रमागत most_channel_direction direction;
	क्रमागत most_channel_data_type data_type;
	u16 num_buffers;
	u16 buffer_size;
	u16 extra_len;
	u16 subbuffer_size;
	u16 packets_per_xact;
	u16 dbr_size;
पूर्ण;

/*
 * काष्ठा mbo - MOST Buffer Object.
 * @context: context क्रम core completion handler
 * @priv: निजी data क्रम HDM
 *
 *	खुला: करोcumented fields that are used क्रम the communications
 *	between MostCore and HDMs
 *
 * @list: list head क्रम use by the mbo's current owner
 * @अगरp: (in) associated पूर्णांकerface instance
 * @num_buffers_ptr: amount of pool buffers
 * @hdm_channel_id: (in) HDM channel instance
 * @virt_address: (in) kernel भव address of the buffer
 * @bus_address: (in) bus address of the buffer
 * @buffer_length: (in) buffer payload length
 * @processed_length: (out) processed length
 * @status: (out) transfer status
 * @complete: (in) completion routine
 *
 * The core allocates and initializes the MBO.
 *
 * The HDM receives MBO क्रम transfer from the core with the call to enqueue().
 * The HDM copies the data to- or from the buffer depending on configured
 * channel direction, set "processed_length" and "status" and completes
 * the transfer procedure by calling the completion routine.
 *
 * Finally, the MBO is being deallocated or recycled क्रम further
 * transfers of the same or a dअगरferent HDM.
 *
 * Directions of usage:
 * The core driver should never access any MBO fields (even अगर marked
 * as "public") जबतक the MBO is owned by an HDM. The ownership starts with
 * the call of enqueue() and ends with the call of its complete() routine.
 *
 *					II.
 * Every HDM attached to the core driver _must_ ensure that it वापसs any MBO
 * it owns (due to a previous call to enqueue() by the core driver) beक्रमe it
 * de-रेजिस्टरs an पूर्णांकerface or माला_लो unloaded from the kernel. If this direction
 * is violated memory leaks will occur, since the core driver करोes _not_ track
 * MBOs it is currently not in control of.
 *
 */
काष्ठा mbo अणु
	व्योम *context;
	व्योम *priv;
	काष्ठा list_head list;
	काष्ठा most_पूर्णांकerface *अगरp;
	पूर्णांक *num_buffers_ptr;
	u16 hdm_channel_id;
	व्योम *virt_address;
	dma_addr_t bus_address;
	u16 buffer_length;
	u16 processed_length;
	क्रमागत most_status_flags status;
	व्योम (*complete)(काष्ठा mbo *mbo);
पूर्ण;

/**
 * Interface instance description.
 *
 * Describes an पूर्णांकerface of a MOST device the core driver is bound to.
 * This काष्ठाure is allocated and initialized in the HDM. MostCore may not
 * modअगरy this काष्ठाure.
 *
 * @dev: the actual device
 * @mod: module
 * @पूर्णांकerface Interface type. \sa most_पूर्णांकerface_type.
 * @description PRELIMINARY.
 *   Unique description of the device instance from poपूर्णांक of view of the
 *   पूर्णांकerface in मुक्त text क्रमm (ASCII).
 *   It may be a hexadecimal presentation of the memory address क्रम the MediaLB
 *   IP or USB device ID with USB properties क्रम USB पूर्णांकerface, etc.
 * @num_channels Number of channels and size of the channel_vector.
 * @channel_vector Properties of the channels.
 *   Array index represents channel ID by the driver.
 * @configure Callback to change data type क्रम the channel of the
 *   पूर्णांकerface instance. May be zero अगर the instance of the पूर्णांकerface is not
 *   configurable. Parameter channel_config describes direction and data
 *   type क्रम the channel, configured by the higher level. The content of
 * @enqueue Delivers MBO to the HDM क्रम processing.
 *   After HDM completes Rx- or Tx- operation the processed MBO shall
 *   be वापसed back to the MostCore using completion routine.
 *   The reason to get the MBO delivered from the MostCore after the channel
 *   is poisoned is the re-खोलोing of the channel by the application.
 *   In this हाल the HDM shall hold MBOs and service the channel as usual.
 *   The HDM must be able to hold at least one MBO क्रम each channel.
 *   The callback वापसs a negative value on error, otherwise 0.
 * @poison_channel Inक्रमms HDM about closing the channel. The HDM shall
 *   cancel all transfers and synchronously or asynchronously वापस
 *   all enqueued क्रम this channel MBOs using the completion routine.
 *   The callback वापसs a negative value on error, otherwise 0.
 * @request_netinfo: triggers retrieving of network info from the HDM by
 *   means of "Message exchange over MDP/MEP"
 *   The call of the function request_netinfo with the parameter on_netinfo as
 *   शून्य prohibits use of the previously obtained function poपूर्णांकer.
 * @priv Private field used by mostcore to store context inक्रमmation.
 */
काष्ठा most_पूर्णांकerface अणु
	काष्ठा device *dev;
	काष्ठा device *driver_dev;
	काष्ठा module *mod;
	क्रमागत most_पूर्णांकerface_type पूर्णांकerface;
	स्थिर अक्षर *description;
	अचिन्हित पूर्णांक num_channels;
	काष्ठा most_channel_capability *channel_vector;
	व्योम *(*dma_alloc)(काष्ठा mbo *mbo, u32 size);
	व्योम (*dma_मुक्त)(काष्ठा mbo *mbo, u32 size);
	पूर्णांक (*configure)(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx,
			 काष्ठा most_channel_config *channel_config);
	पूर्णांक (*enqueue)(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx,
		       काष्ठा mbo *mbo);
	पूर्णांक (*poison_channel)(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx);
	व्योम (*request_netinfo)(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx,
				व्योम (*on_netinfo)(काष्ठा most_पूर्णांकerface *अगरace,
						   अचिन्हित अक्षर link_stat,
						   अचिन्हित अक्षर *mac_addr));
	व्योम *priv;
	काष्ठा पूर्णांकerface_निजी *p;
पूर्ण;

/**
 * काष्ठा most_component - identअगरies a loadable component क्रम the mostcore
 * @list: list_head
 * @name: component name
 * @probe_channel: function क्रम core to notअगरy driver about channel connection
 * @disconnect_channel: callback function to disconnect a certain channel
 * @rx_completion: completion handler क्रम received packets
 * @tx_completion: completion handler क्रम transmitted packets
 */
काष्ठा most_component अणु
	काष्ठा list_head list;
	स्थिर अक्षर *name;
	काष्ठा module *mod;
	पूर्णांक (*probe_channel)(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx,
			     काष्ठा most_channel_config *cfg, अक्षर *name,
			     अक्षर *param);
	पूर्णांक (*disconnect_channel)(काष्ठा most_पूर्णांकerface *अगरace,
				  पूर्णांक channel_idx);
	पूर्णांक (*rx_completion)(काष्ठा mbo *mbo);
	पूर्णांक (*tx_completion)(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx);
	पूर्णांक (*cfg_complete)(व्योम);
पूर्ण;

/**
 * most_रेजिस्टर_पूर्णांकerface - Registers instance of the पूर्णांकerface.
 * @अगरace: Poपूर्णांकer to the पूर्णांकerface instance description.
 *
 * Returns a poपूर्णांकer to the kobject of the generated instance.
 *
 * Note: HDM has to ensure that any reference held on the kobj is
 * released beक्रमe deरेजिस्टरing the पूर्णांकerface.
 */
पूर्णांक most_रेजिस्टर_पूर्णांकerface(काष्ठा most_पूर्णांकerface *अगरace);

/**
 * Deरेजिस्टरs instance of the पूर्णांकerface.
 * @पूर्णांकf_instance Poपूर्णांकer to the पूर्णांकerface instance description.
 */
व्योम most_deरेजिस्टर_पूर्णांकerface(काष्ठा most_पूर्णांकerface *अगरace);
व्योम most_submit_mbo(काष्ठा mbo *mbo);

/**
 * most_stop_enqueue - prevents core from enqueing MBOs
 * @अगरace: poपूर्णांकer to पूर्णांकerface
 * @channel_idx: channel index
 */
व्योम most_stop_enqueue(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx);

/**
 * most_resume_enqueue - allow core to enqueue MBOs again
 * @अगरace: poपूर्णांकer to पूर्णांकerface
 * @channel_idx: channel index
 *
 * This clears the enqueue halt flag and enqueues all MBOs currently
 * in रुको fअगरo.
 */
व्योम most_resume_enqueue(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx);
पूर्णांक most_रेजिस्टर_component(काष्ठा most_component *comp);
पूर्णांक most_deरेजिस्टर_component(काष्ठा most_component *comp);
काष्ठा mbo *most_get_mbo(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx,
			 काष्ठा most_component *comp);
व्योम most_put_mbo(काष्ठा mbo *mbo);
पूर्णांक channel_has_mbo(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx,
		    काष्ठा most_component *comp);
पूर्णांक most_start_channel(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx,
		       काष्ठा most_component *comp);
पूर्णांक most_stop_channel(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx,
		      काष्ठा most_component *comp);
पूर्णांक __init configfs_init(व्योम);
पूर्णांक most_रेजिस्टर_configfs_subsys(काष्ठा most_component *comp);
व्योम most_deरेजिस्टर_configfs_subsys(काष्ठा most_component *comp);
पूर्णांक most_add_link(अक्षर *mdev, अक्षर *mdev_ch, अक्षर *comp_name, अक्षर *link_name,
		  अक्षर *comp_param);
पूर्णांक most_हटाओ_link(अक्षर *mdev, अक्षर *mdev_ch, अक्षर *comp_name);
पूर्णांक most_set_cfg_buffer_size(अक्षर *mdev, अक्षर *mdev_ch, u16 val);
पूर्णांक most_set_cfg_subbuffer_size(अक्षर *mdev, अक्षर *mdev_ch, u16 val);
पूर्णांक most_set_cfg_dbr_size(अक्षर *mdev, अक्षर *mdev_ch, u16 val);
पूर्णांक most_set_cfg_num_buffers(अक्षर *mdev, अक्षर *mdev_ch, u16 val);
पूर्णांक most_set_cfg_datatype(अक्षर *mdev, अक्षर *mdev_ch, अक्षर *buf);
पूर्णांक most_set_cfg_direction(अक्षर *mdev, अक्षर *mdev_ch, अक्षर *buf);
पूर्णांक most_set_cfg_packets_xact(अक्षर *mdev, अक्षर *mdev_ch, u16 val);
पूर्णांक most_cfg_complete(अक्षर *comp_name);
व्योम most_पूर्णांकerface_रेजिस्टर_notअगरy(स्थिर अक्षर *mdev_name);
#पूर्ण_अगर /* MOST_CORE_H_ */
