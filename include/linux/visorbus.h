<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2010 - 2013 UNISYS CORPORATION
 * All rights reserved.
 */

/*
 *  This header file is to be included by other kernel mode components that
 *  implement a particular kind of visor_device.  Each of these other kernel
 *  mode components is called a visor device driver.  Refer to visorढाँचा
 *  क्रम a minimal sample visor device driver.
 *
 *  There should be nothing in this file that is निजी to the visorbus
 *  bus implementation itself.
 */

#अगर_अघोषित __VISORBUS_H__
#घोषणा __VISORBUS_H__

#समावेश <linux/device.h>

#घोषणा VISOR_CHANNEL_SIGNATURE ('L' << 24 | 'N' << 16 | 'C' << 8 | 'E')

/*
 * क्रमागत channel_serverstate
 * @CHANNELSRV_UNINITIALIZED: Channel is in an undefined state.
 * @CHANNELSRV_READY:	      Channel has been initialized by server.
 */
क्रमागत channel_serverstate अणु
	CHANNELSRV_UNINITIALIZED = 0,
	CHANNELSRV_READY = 1
पूर्ण;

/*
 * क्रमागत channel_clientstate
 * @CHANNELCLI_DETACHED:
 * @CHANNELCLI_DISABLED:  Client can see channel but is NOT allowed to use it
 *			  unless given TBD* explicit request
 *			  (should actually be < DETACHED).
 * @CHANNELCLI_ATTACHING: Legacy EFI client request क्रम EFI server to attach.
 * @CHANNELCLI_ATTACHED:  Idle, but client may want to use channel any समय.
 * @CHANNELCLI_BUSY:	  Client either wants to use or is using channel.
 * @CHANNELCLI_OWNED:	  "No worries" state - client can access channel
 *			  anyसमय.
 */
क्रमागत channel_clientstate अणु
	CHANNELCLI_DETACHED = 0,
	CHANNELCLI_DISABLED = 1,
	CHANNELCLI_ATTACHING = 2,
	CHANNELCLI_ATTACHED = 3,
	CHANNELCLI_BUSY = 4,
	CHANNELCLI_OWNED = 5
पूर्ण;

/*
 * Values क्रम VISOR_CHANNEL_PROTOCOL.Features: This define exists so that
 * a guest can look at the FeatureFlags in the io channel, and configure the
 * driver to use पूर्णांकerrupts or not based on this setting. All feature bits क्रम
 * all channels should be defined here. The io channel feature bits are defined
 * below.
 */
#घोषणा VISOR_DRIVER_ENABLES_INTS (0x1ULL << 1)
#घोषणा VISOR_CHANNEL_IS_POLLING (0x1ULL << 3)
#घोषणा VISOR_IOVM_OK_DRIVER_DISABLING_INTS (0x1ULL << 4)
#घोषणा VISOR_DRIVER_DISABLES_INTS (0x1ULL << 5)
#घोषणा VISOR_DRIVER_ENHANCED_RCVBUF_CHECKING (0x1ULL << 6)

/*
 * काष्ठा channel_header - Common Channel Header
 * @signature:	       Signature.
 * @legacy_state:      DEPRECATED - being replaced by.
 * @header_size:       माप(काष्ठा channel_header).
 * @size:	       Total size of this channel in bytes.
 * @features:	       Flags to modअगरy behavior.
 * @chtype:	       Channel type: data, bus, control, etc..
 * @partition_handle:  ID of guest partition.
 * @handle:	       Device number of this channel in client.
 * @ch_space_offset:   Offset in bytes to channel specअगरic area.
 * @version_id:	       Struct channel_header Version ID.
 * @partition_index:   Index of guest partition.
 * @zone_uuid:	       Guid of Channel's zone.
 * @cli_str_offset:    Offset from channel header to null-terminated
 *		       ClientString (0 अगर ClientString not present).
 * @cli_state_boot:    CHANNEL_CLIENTSTATE of pre-boot EFI client of this
 *		       channel.
 * @cmd_state_cli:     CHANNEL_COMMANDSTATE (overloaded in Winकरोws drivers, see
 *		       ServerStateUp, ServerStateDown, etc).
 * @cli_state_os:      CHANNEL_CLIENTSTATE of Guest OS client of this channel.
 * @ch_अक्षरacteristic: CHANNEL_CHARACTERISTIC_<xxx>.
 * @cmd_state_srv:     CHANNEL_COMMANDSTATE (overloaded in Winकरोws drivers, see
 *		       ServerStateUp, ServerStateDown, etc).
 * @srv_state:	       CHANNEL_SERVERSTATE.
 * @cli_error_boot:    Bits to indicate err states क्रम boot clients, so err
 *		       messages can be throttled.
 * @cli_error_os:      Bits to indicate err states क्रम OS clients, so err
 *		       messages can be throttled.
 * @filler:	       Pad out to 128 byte cacheline.
 * @recover_channel:   Please add all new single-byte values below here.
 */
काष्ठा channel_header अणु
	u64 signature;
	u32 legacy_state;
	/* SrvState, CliStateBoot, and CliStateOS below */
	u32 header_size;
	u64 size;
	u64 features;
	guid_t chtype;
	u64 partition_handle;
	u64 handle;
	u64 ch_space_offset;
	u32 version_id;
	u32 partition_index;
	guid_t zone_guid;
	u32 cli_str_offset;
	u32 cli_state_boot;
	u32 cmd_state_cli;
	u32 cli_state_os;
	u32 ch_अक्षरacteristic;
	u32 cmd_state_srv;
	u32 srv_state;
	u8 cli_error_boot;
	u8 cli_error_os;
	u8 filler[1];
	u8 recover_channel;
पूर्ण __packed;

#घोषणा VISOR_CHANNEL_ENABLE_INTS (0x1ULL << 0)

/*
 * काष्ठा संकेत_queue_header - Subheader क्रम the Signal Type variation of the
 *                              Common Channel.
 * @version:	      SIGNAL_QUEUE_HEADER Version ID.
 * @chtype:	      Queue type: storage, network.
 * @size:	      Total size of this queue in bytes.
 * @sig_base_offset:  Offset to संकेत queue area.
 * @features:	      Flags to modअगरy behavior.
 * @num_sent:	      Total # of संकेतs placed in this queue.
 * @num_overflows:    Total # of inserts failed due to full queue.
 * @संकेत_size:      Total size of a संकेत क्रम this queue.
 * @max_slots:        Max # of slots in queue, 1 slot is always empty.
 * @max_संकेतs:      Max # of संकेतs in queue (MaxSignalSlots-1).
 * @head:	      Queue head संकेत #.
 * @num_received:     Total # of संकेतs हटाओd from this queue.
 * @tail:	      Queue tail संकेत.
 * @reserved1:	      Reserved field.
 * @reserved2:	      Reserved field.
 * @client_queue:
 * @num_irq_received: Total # of Interrupts received. This is incremented by the
 *		      ISR in the guest winकरोws driver.
 * @num_empty:	      Number of बार that visor_संकेत_हटाओ is called and
 *		      वापसed Empty Status.
 * @errorflags:	      Error bits set during SignalReinit to denote trouble with
 *		      client's fields.
 * @filler:	      Pad out to 64 byte cacheline.
 */
काष्ठा संकेत_queue_header अणु
	/* 1st cache line */
	u32 version;
	u32 chtype;
	u64 size;
	u64 sig_base_offset;
	u64 features;
	u64 num_sent;
	u64 num_overflows;
	u32 संकेत_size;
	u32 max_slots;
	u32 max_संकेतs;
	u32 head;
	/* 2nd cache line */
	u64 num_received;
	u32 tail;
	u32 reserved1;
	u64 reserved2;
	u64 client_queue;
	u64 num_irq_received;
	u64 num_empty;
	u32 errorflags;
	u8 filler[12];
पूर्ण __packed;

/* VISORCHANNEL Guids */
/* अणु414815ed-c58c-11da-95a9-00e08161165fपूर्ण */
#घोषणा VISOR_VHBA_CHANNEL_GUID \
	GUID_INIT(0x414815ed, 0xc58c, 0x11da, \
		  0x95, 0xa9, 0x0, 0xe0, 0x81, 0x61, 0x16, 0x5f)
#घोषणा VISOR_VHBA_CHANNEL_GUID_STR \
	"414815ed-c58c-11da-95a9-00e08161165f"
काष्ठा visorchipset_state अणु
	u32 created:1;
	u32 attached:1;
	u32 configured:1;
	u32 running:1;
	/* Reमुख्यing bits in this 32-bit word are reserved. */
पूर्ण;

/**
 * काष्ठा visor_device - A device type क्रम things "plugged" पूर्णांकo the visorbus
 *                       bus
 * @visorchannel:		Poपूर्णांकs to the channel that the device is
 *				associated with.
 * @channel_type_guid:		Identअगरies the channel type to the bus driver.
 * @device:			Device काष्ठा meant क्रम use by the bus driver
 *				only.
 * @list_all:			Used by the bus driver to क्रमागतerate devices.
 * @समयr:		        Timer fired periodically to करो पूर्णांकerrupt-type
 *				activity.
 * @being_हटाओd:		Indicates that the device is being हटाओd from
 *				the bus. Private bus driver use only.
 * @visordriver_callback_lock:	Used by the bus driver to lock when adding and
 *				removing devices.
 * @pausing:			Indicates that a change towards a छोड़ोd state.
 *				is in progress. Only modअगरied by the bus driver.
 * @resuming:			Indicates that a change towards a running state
 *				is in progress. Only modअगरied by the bus driver.
 * @chipset_bus_no:		Private field used by the bus driver.
 * @chipset_dev_no:		Private field used the bus driver.
 * @state:			Used to indicate the current state of the
 *				device.
 * @inst:			Unique GUID क्रम this instance of the device.
 * @name:			Name of the device.
 * @pending_msg_hdr:		For निजी use by bus driver to respond to
 *				hypervisor requests.
 * @vbus_hdr_info:		A poपूर्णांकer to header info. Private use by bus
 *				driver.
 * @partition_guid:		Indicates client partion id. This should be the
 *				same across all visor_devices in the current
 *				guest. Private use by bus driver only.
 */
काष्ठा visor_device अणु
	काष्ठा visorchannel *visorchannel;
	guid_t channel_type_guid;
	/* These fields are क्रम निजी use by the bus driver only. */
	काष्ठा device device;
	काष्ठा list_head list_all;
	काष्ठा समयr_list समयr;
	bool समयr_active;
	bool being_हटाओd;
	काष्ठा mutex visordriver_callback_lock; /* synchronize probe/हटाओ */
	bool pausing;
	bool resuming;
	u32 chipset_bus_no;
	u32 chipset_dev_no;
	काष्ठा visorchipset_state state;
	guid_t inst;
	u8 *name;
	काष्ठा controlvm_message_header *pending_msg_hdr;
	व्योम *vbus_hdr_info;
	guid_t partition_guid;
	काष्ठा dentry *debugfs_dir;
	काष्ठा dentry *debugfs_bus_info;
पूर्ण;

#घोषणा to_visor_device(x) container_of(x, काष्ठा visor_device, device)

प्रकार व्योम (*visorbus_state_complete_func) (काष्ठा visor_device *dev,
					      पूर्णांक status);

/*
 * This काष्ठा describes a specअगरic visor channel, by providing its GUID, name,
 * and sizes.
 */
काष्ठा visor_channeltype_descriptor अणु
	स्थिर guid_t guid;
	स्थिर अक्षर *name;
	u64 min_bytes;
	u32 version;
पूर्ण;

/**
 * काष्ठा visor_driver - Inक्रमmation provided by each visor driver when it
 *                       रेजिस्टरs with the visorbus driver
 * @name:		Name of the visor driver.
 * @owner:		The module owner.
 * @channel_types:	Types of channels handled by this driver, ending with
 *			a zero GUID. Our specialized BUS.match() method knows
 *			about this list, and uses it to determine whether this
 *			driver will in fact handle a new device that it has
 *			detected.
 * @probe:		Called when a new device comes online, by our probe()
 *			function specअगरied by driver.probe() (triggered
 *			ultimately by some call to driver_रेजिस्टर(),
 *			bus_add_driver(), or driver_attach()).
 * @हटाओ:		Called when a new device is हटाओd, by our हटाओ()
 *			function specअगरied by driver.हटाओ() (triggered
 *			ultimately by some call to device_release_driver()).
 * @channel_पूर्णांकerrupt:	Called periodically, whenever there is a possiblity
 *			that "something interesting" may have happened to the
 *			channel.
 * @छोड़ो:		Called to initiate a change of the device's state.  If
 *			the वापस valu`e is < 0, there was an error and the
 *			state transition will NOT occur.  If the वापस value
 *			is >= 0, then the state transition was INITIATED
 *			successfully, and complete_func() will be called (or
 *			was just called) with the final status when either the
 *			state transition fails or completes successfully.
 * @resume:		Behaves similar to छोड़ो.
 * @driver:		Private reference to the device driver. For use by bus
 *			driver only.
 */
काष्ठा visor_driver अणु
	स्थिर अक्षर *name;
	काष्ठा module *owner;
	काष्ठा visor_channeltype_descriptor *channel_types;
	पूर्णांक (*probe)(काष्ठा visor_device *dev);
	व्योम (*हटाओ)(काष्ठा visor_device *dev);
	व्योम (*channel_पूर्णांकerrupt)(काष्ठा visor_device *dev);
	पूर्णांक (*छोड़ो)(काष्ठा visor_device *dev,
		     visorbus_state_complete_func complete_func);
	पूर्णांक (*resume)(काष्ठा visor_device *dev,
		      visorbus_state_complete_func complete_func);

	/* These fields are क्रम निजी use by the bus driver only. */
	काष्ठा device_driver driver;
पूर्ण;

#घोषणा to_visor_driver(x) (container_of(x, काष्ठा visor_driver, driver))

पूर्णांक visor_check_channel(काष्ठा channel_header *ch, काष्ठा device *dev,
			स्थिर guid_t *expected_uuid, अक्षर *chname,
			u64 expected_min_bytes,	u32 expected_version,
			u64 expected_signature);

पूर्णांक visorbus_रेजिस्टर_visor_driver(काष्ठा visor_driver *drv);
व्योम visorbus_unरेजिस्टर_visor_driver(काष्ठा visor_driver *drv);
पूर्णांक visorbus_पढ़ो_channel(काष्ठा visor_device *dev,
			  अचिन्हित दीर्घ offset, व्योम *dest,
			  अचिन्हित दीर्घ nbytes);
पूर्णांक visorbus_ग_लिखो_channel(काष्ठा visor_device *dev,
			   अचिन्हित दीर्घ offset, व्योम *src,
			   अचिन्हित दीर्घ nbytes);
पूर्णांक visorbus_enable_channel_पूर्णांकerrupts(काष्ठा visor_device *dev);
व्योम visorbus_disable_channel_पूर्णांकerrupts(काष्ठा visor_device *dev);

पूर्णांक visorchannel_संकेतहटाओ(काष्ठा visorchannel *channel, u32 queue,
			      व्योम *msg);
पूर्णांक visorchannel_संकेतinsert(काष्ठा visorchannel *channel, u32 queue,
			      व्योम *msg);
bool visorchannel_संकेतempty(काष्ठा visorchannel *channel, u32 queue);
स्थिर guid_t *visorchannel_get_guid(काष्ठा visorchannel *channel);

#घोषणा BUS_ROOT_DEVICE अच_पूर्णांक_उच्च
काष्ठा visor_device *visorbus_get_device_by_id(u32 bus_no, u32 dev_no,
					       काष्ठा visor_device *from);
#पूर्ण_अगर
