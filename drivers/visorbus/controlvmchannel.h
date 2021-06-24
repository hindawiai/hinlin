<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2010 - 2015 UNISYS CORPORATION
 * All rights reserved.
 */

#अगर_अघोषित __CONTROLVMCHANNEL_H__
#घोषणा __CONTROLVMCHANNEL_H__

#समावेश <linux/uuid.h>
#समावेश <linux/visorbus.h>

/* अणु2B3C2D10-7EF5-4ad8-B966-3448B7386B3Dपूर्ण */
#घोषणा VISOR_CONTROLVM_CHANNEL_GUID \
	GUID_INIT(0x2b3c2d10, 0x7ef5, 0x4ad8, \
		  0xb9, 0x66, 0x34, 0x48, 0xb7, 0x38, 0x6b, 0x3d)

#घोषणा CONTROLVM_MESSAGE_MAX 64

/*
 * Must increment this whenever you insert or delete fields within this channel
 * काष्ठा.  Also increment whenever you change the meaning of fields within this
 * channel काष्ठा so as to अवरोध pre-existing software. Note that you can
 * usually add fields to the END of the channel काष्ठा withOUT needing to
 * increment this.
 */
#घोषणा VISOR_CONTROLVM_CHANNEL_VERSIONID 1

/* Defines क्रम various channel queues */
#घोषणा CONTROLVM_QUEUE_REQUEST		0
#घोषणा CONTROLVM_QUEUE_RESPONSE	1
#घोषणा CONTROLVM_QUEUE_EVENT		2
#घोषणा CONTROLVM_QUEUE_ACK		3

/* Max num of messages stored during IOVM creation to be reused after crash */
#घोषणा CONTROLVM_CRASHMSG_MAX 2

/*
 * काष्ठा visor_segment_state
 * @enabled:   May enter other states.
 * @active:    Asचिन्हित to active partition.
 * @alive:     Configure message sent to service/server.
 * @revoked:   Similar to partition state ShuttingDown.
 * @allocated: Memory (device/port number) has been selected by Command.
 * @known:     Has been पूर्णांकroduced to the service/guest partition.
 * @पढ़ोy:     Service/Guest partition has responded to पूर्णांकroduction.
 * @operating: Resource is configured and operating.
 * @reserved:  Natural alignment.
 *
 * Note: Don't use high bit unless we need to चयन to uलघु which is
 * non-compliant.
 */
काष्ठा visor_segment_state  अणु
	u16 enabled:1;
	u16 active:1;
	u16 alive:1;
	u16 revoked:1;
	u16 allocated:1;
	u16 known:1;
	u16 पढ़ोy:1;
	u16 operating:1;
	u16 reserved:8;
पूर्ण __packed;

अटल स्थिर काष्ठा visor_segment_state segment_state_running = अणु
	1, 1, 1, 0, 1, 1, 1, 1
पूर्ण;

अटल स्थिर काष्ठा visor_segment_state segment_state_छोड़ोd = अणु
	1, 1, 1, 0, 1, 1, 1, 0
पूर्ण;

अटल स्थिर काष्ठा visor_segment_state segment_state_standby = अणु
	1, 1, 0, 0, 1, 1, 1, 0
पूर्ण;

/*
 * क्रमागत controlvm_id
 * @CONTROLVM_INVALID:
 * @CONTROLVM_BUS_CREATE:		CP --> SP, GP.
 * @CONTROLVM_BUS_DESTROY:		CP --> SP, GP.
 * @CONTROLVM_BUS_CONFIGURE:		CP --> SP.
 * @CONTROLVM_BUS_CHANGESTATE:		CP --> SP, GP.
 * @CONTROLVM_BUS_CHANGESTATE_EVENT:	SP, GP --> CP.
 * @CONTROLVM_DEVICE_CREATE:		CP --> SP, GP.
 * @CONTROLVM_DEVICE_DESTROY:		CP --> SP, GP.
 * @CONTROLVM_DEVICE_CONFIGURE:		CP --> SP.
 * @CONTROLVM_DEVICE_CHANGESTATE:	CP --> SP, GP.
 * @CONTROLVM_DEVICE_CHANGESTATE_EVENT:	SP, GP --> CP.
 * @CONTROLVM_DEVICE_RECONFIGURE:	CP --> Boot.
 * @CONTROLVM_CHIPSET_INIT:		CP --> SP, GP.
 * @CONTROLVM_CHIPSET_STOP:		CP --> SP, GP.
 * @CONTROLVM_CHIPSET_READY:		CP --> SP.
 * @CONTROLVM_CHIPSET_SELFTEST:		CP --> SP.
 *
 * Ids क्रम commands that may appear in either queue of a ControlVm channel.
 *
 * Commands that are initiated by the command partition (CP), by an IO or
 * console service partition (SP), or by a guest partition (GP) are:
 * - issued on the RequestQueue queue (q #0) in the ControlVm channel
 * - responded to on the ResponseQueue queue (q #1) in the ControlVm channel
 *
 * Events that are initiated by an IO or console service partition (SP) or
 * by a guest partition (GP) are:
 * - issued on the EventQueue queue (q #2) in the ControlVm channel
 * - responded to on the EventAckQueue queue (q #3) in the ControlVm channel
 */
क्रमागत controlvm_id अणु
	CONTROLVM_INVALID = 0,
	/*
	 * SWITCH commands required Parameter: SwitchNumber.
	 * BUS commands required Parameter: BusNumber
	 */
	CONTROLVM_BUS_CREATE = 0x101,
	CONTROLVM_BUS_DESTROY = 0x102,
	CONTROLVM_BUS_CONFIGURE = 0x104,
	CONTROLVM_BUS_CHANGESTATE = 0x105,
	CONTROLVM_BUS_CHANGESTATE_EVENT = 0x106,
	/* DEVICE commands required Parameter: BusNumber, DeviceNumber */
	CONTROLVM_DEVICE_CREATE = 0x201,
	CONTROLVM_DEVICE_DESTROY = 0x202,
	CONTROLVM_DEVICE_CONFIGURE = 0x203,
	CONTROLVM_DEVICE_CHANGESTATE = 0x204,
	CONTROLVM_DEVICE_CHANGESTATE_EVENT = 0x205,
	CONTROLVM_DEVICE_RECONFIGURE = 0x206,
	/* CHIPSET commands */
	CONTROLVM_CHIPSET_INIT = 0x301,
	CONTROLVM_CHIPSET_STOP = 0x302,
	CONTROLVM_CHIPSET_READY = 0x304,
	CONTROLVM_CHIPSET_SELFTEST = 0x305,
पूर्ण;

/*
 * काष्ठा irq_info
 * @reserved1:	     Natural alignment purposes
 * @recv_irq_handle: Specअगरies पूर्णांकerrupt handle. It is used to retrieve the
 *		     corresponding पूर्णांकerrupt pin from Monitor; and the पूर्णांकerrupt
 *		     pin is used to connect to the corresponding पूर्णांकerrupt.
 *		     Used by IOPart-GP only.
 * @recv_irq_vector: Specअगरies पूर्णांकerrupt vector. It, पूर्णांकerrupt pin, and shared
 *		     are used to connect to the corresponding पूर्णांकerrupt.
 *		     Used by IOPart-GP only.
 * @recv_irq_shared: Specअगरies अगर the recvInterrupt is shared.  It, पूर्णांकerrupt
 *		     pin and vector are used to connect to 0 = not shared;
 *		     1 = shared the corresponding पूर्णांकerrupt.
 *		     Used by IOPart-GP only.
 * @reserved:	     Natural alignment purposes
 */
काष्ठा irq_info अणु
	u64 reserved1;
	u64 recv_irq_handle;
	u32 recv_irq_vector;
	u8 recv_irq_shared;
	u8 reserved[3];
पूर्ण __packed;

/*
 * काष्ठा efi_visor_indication
 * @boot_to_fw_ui: Stop in UEFI UI
 * @clear_nvram:   Clear NVRAM
 * @clear_cmos:	   Clear CMOS
 * @boot_to_tool:  Run install tool
 * @reserved:	   Natural alignment
 */
काष्ठा efi_visor_indication  अणु
	u64 boot_to_fw_ui:1;
	u64 clear_nvram:1;
	u64 clear_cmos:1;
	u64 boot_to_tool:1;
	/* Reमुख्यing bits are available */
	u64 reserved:60;
पूर्ण __packed;

क्रमागत visor_chipset_feature अणु
	VISOR_CHIPSET_FEATURE_REPLY = 0x00000001,
	VISOR_CHIPSET_FEATURE_PARA_HOTPLUG = 0x00000002,
पूर्ण;

/*
 * काष्ठा controlvm_message_header
 * @id:		       See CONTROLVM_ID.
 * @message_size:      Includes size of this काष्ठा + size of message.
 * @segment_index:     Index of segment containing Vm message/inक्रमmation.
 * @completion_status: Error status code or result of  message completion.
 * @काष्ठा flags:
 *	@failed:	     =1 in a response to signअगरy failure.
 *	@response_expected:  =1 in all messages that expect a response.
 *	@server:	     =1 in all bus & device-related messages where the
 *			     message receiver is to act as the bus or device
 *			     server.
 *	@test_message:	     =1 क्रम testing use only (Control and Command
 *			     ignore this).
 *	@partial_completion: =1 अगर there are क्रमthcoming responses/acks
 *                           associated with this message.
 *      @preserve:	     =1 this is to let us know to preserve channel
 *			     contents.
 *	@ग_लिखोr_in_diag:     =1 the DiagWriter is active in the Diagnostic
 *			     Partition.
 *	@reserve:	     Natural alignment.
 * @reserved:	       Natural alignment.
 * @message_handle:    Identअगरies the particular message instance.
 * @payload_vm_offset: Offset of payload area from start of this instance.
 * @payload_max_bytes: Maximum bytes allocated in payload area of ControlVm
 *		       segment.
 * @payload_bytes:     Actual number of bytes of payload area to copy between
 *		       IO/Command. If non-zero, there is a payload to copy.
 *
 * This is the common काष्ठाure that is at the beginning of every
 * ControlVm message (both commands and responses) in any ControlVm
 * queue.  Commands are easily distinguished from responses by
 * looking at the flags.response field.
 */
काष्ठा controlvm_message_header  अणु
	u32 id;
	/*
	 * For requests, indicates the message type. For responses, indicates
	 * the type of message we are responding to.
	 */
	u32 message_size;
	u32 segment_index;
	u32 completion_status;
	काष्ठा  अणु
		u32 failed:1;
		u32 response_expected:1;
		u32 server:1;
		u32 test_message:1;
		u32 partial_completion:1;
		u32 preserve:1;
		u32 ग_लिखोr_in_diag:1;
		u32 reserve:25;
	पूर्ण __packed flags;
	u32 reserved;
	u64 message_handle;
	u64 payload_vm_offset;
	u32 payload_max_bytes;
	u32 payload_bytes;
पूर्ण __packed;

/*
 * काष्ठा controlvm_packet_device_create - For CONTROLVM_DEVICE_CREATE
 * @bus_no:	    Bus # (0..n-1) from the msg receiver's end.
 * @dev_no:	    Bus-relative (0..n-1) device number.
 * @channel_addr:   Guest physical address of the channel, which can be
 *		    dereferenced by the receiver of this ControlVm command.
 * @channel_bytes:  Specअगरies size of the channel in bytes.
 * @data_type_uuid: Specअगरies क्रमmat of data in channel.
 * @dev_inst_uuid:  Instance guid क्रम the device.
 * @irq_info पूर्णांकr:  Specअगरies पूर्णांकerrupt inक्रमmation.
 */
काष्ठा controlvm_packet_device_create  अणु
	u32 bus_no;
	u32 dev_no;
	u64 channel_addr;
	u64 channel_bytes;
	guid_t data_type_guid;
	guid_t dev_inst_guid;
	काष्ठा irq_info पूर्णांकr;
पूर्ण __packed;

/*
 * काष्ठा controlvm_packet_device_configure - For CONTROLVM_DEVICE_CONFIGURE
 * @bus_no: Bus number (0..n-1) from the msg receiver's perspective.
 * @dev_no: Bus-relative (0..n-1) device number.
 */
काष्ठा controlvm_packet_device_configure  अणु
	u32 bus_no;
	u32 dev_no;
पूर्ण __packed;

/* Total 128 bytes */
काष्ठा controlvm_message_device_create अणु
	काष्ठा controlvm_message_header header;
	काष्ठा controlvm_packet_device_create packet;
पूर्ण __packed;

/* Total 56 bytes */
काष्ठा controlvm_message_device_configure  अणु
	काष्ठा controlvm_message_header header;
	काष्ठा controlvm_packet_device_configure packet;
पूर्ण __packed;

/*
 * काष्ठा controlvm_message_packet - This is the क्रमmat क्रम a message in any
 *                                   ControlVm queue.
 * @काष्ठा create_bus:		For CONTROLVM_BUS_CREATE.
 *	@bus_no:	     Bus # (0..n-1) from the msg receiver's perspective.
 *	@dev_count:	     Indicates the max number of devices on this bus.
 *	@channel_addr:	     Guest physical address of the channel, which can be
 *			     dereferenced by the receiver of this ControlVM
 *			     command.
 *	@channel_bytes:	     Size of the channel.
 *	@bus_data_type_uuid: Indicates क्रमmat of data in bus channel.
 *	@bus_inst_uuid:	     Instance uuid क्रम the bus.
 *
 * @काष्ठा destroy_bus:		For CONTROLVM_BUS_DESTROY.
 *	@bus_no: Bus # (0..n-1) from the msg receiver's perspective.
 *	@reserved: Natural alignment purposes.
 *
 * @काष्ठा configure_bus:	For CONTROLVM_BUS_CONFIGURE.
 *	@bus_no:	      Bus # (0..n-1) from the receiver's perspective.
 *	@reserved1:	      For alignment purposes.
 *	@guest_handle:	      This is used to convert guest physical address to
 *			      physical address.
 *	@recv_bus_irq_handle: Specअगरies पूर्णांकerrupt info. It is used by SP to
 *			      रेजिस्टर to receive पूर्णांकerrupts from the CP. This
 *			      पूर्णांकerrupt is used क्रम bus level notअगरications.
 *			      The corresponding sendBusInterruptHandle is kept
 *			      in CP.
 *
 * @काष्ठा create_device:	For CONTROLVM_DEVICE_CREATE.
 *
 * @काष्ठा destroy_device:	For CONTROLVM_DEVICE_DESTROY.
 *	@bus_no: Bus # (0..n-1) from the msg receiver's perspective.
 *	@dev_no: Bus-relative (0..n-1) device number.
 *
 * @काष्ठा configure_device:	For CONTROLVM_DEVICE_CONFIGURE.
 *
 * @काष्ठा reconfigure_device:	For CONTROLVM_DEVICE_RECONFIGURE.
 *	@bus_no: Bus # (0..n-1) from the msg receiver's perspective.
 *	@dev_no: Bus-relative (0..n-1) device number.
 *
 * @काष्ठा bus_change_state:	For CONTROLVM_BUS_CHANGESTATE.
 *	@bus_no:
 *	@काष्ठा state:
 *	@reserved: Natural alignment purposes.
 *
 * @काष्ठा device_change_state:	For CONTROLVM_DEVICE_CHANGESTATE.
 *	@bus_no:
 *	@dev_no:
 *	@काष्ठा state:
 *	@काष्ठा flags:
 *		@phys_device: =1 अगर message is क्रम a physical device.
 *		@reserved:    Natural alignment.
 *		@reserved1:   Natural alignment.
 *	@reserved:    Natural alignment purposes.
 *
 * @काष्ठा device_change_state_event:	For CONTROLVM_DEVICE_CHANGESTATE_EVENT.
 *	@bus_no:
 *	@dev_no:
 *	@काष्ठा state:
 *	@reserved:     Natural alignment purposes.
 *
 * @काष्ठा init_chipset:	For CONTROLVM_CHIPSET_INIT.
 *	@bus_count:	  Indicates the max number of busses.
 *	@चयन_count:    Indicates the max number of चयनes.
 *	@क्रमागत features:
 *	@platक्रमm_number:
 *
 * @काष्ठा chipset_selftest:	For CONTROLVM_CHIPSET_SELFTEST.
 *      @options: Reserved.
 *      @test:	  Bit 0 set to run embedded selftest.
 *
 * @addr:   A physical address of something, that can be dereferenced by the
 *	    receiver of this ControlVm command.
 *
 * @handle: A handle of something (depends on command id).
 */
काष्ठा controlvm_message_packet  अणु
	जोड़  अणु
		काष्ठा  अणु
			u32 bus_no;
			u32 dev_count;
			u64 channel_addr;
			u64 channel_bytes;
			guid_t bus_data_type_guid;
			guid_t bus_inst_guid;
		पूर्ण __packed create_bus;
		काष्ठा  अणु
			u32 bus_no;
			u32 reserved;
		पूर्ण __packed destroy_bus;
		काष्ठा  अणु
			u32 bus_no;
			u32 reserved1;
			u64 guest_handle;
			u64 recv_bus_irq_handle;
		पूर्ण __packed configure_bus;
		काष्ठा controlvm_packet_device_create create_device;
		काष्ठा  अणु
			u32 bus_no;
			u32 dev_no;
		पूर्ण __packed destroy_device;
		काष्ठा controlvm_packet_device_configure configure_device;
		काष्ठा  अणु
			u32 bus_no;
			u32 dev_no;
		पूर्ण __packed reconfigure_device;
		काष्ठा  अणु
			u32 bus_no;
			काष्ठा visor_segment_state state;
			u8 reserved[2];
		पूर्ण __packed bus_change_state;
		काष्ठा  अणु
			u32 bus_no;
			u32 dev_no;
			काष्ठा visor_segment_state state;
			काष्ठा  अणु
				u32 phys_device:1;
				u32 reserved:31;
				u32 reserved1;
			पूर्ण __packed flags;
			u8 reserved[2];
		पूर्ण __packed device_change_state;
		काष्ठा  अणु
			u32 bus_no;
			u32 dev_no;
			काष्ठा visor_segment_state state;
			u8 reserved[6];
		पूर्ण __packed device_change_state_event;
		काष्ठा  अणु
			u32 bus_count;
			u32 चयन_count;
			क्रमागत visor_chipset_feature features;
			u32 platक्रमm_number;
		पूर्ण __packed init_chipset;
		काष्ठा  अणु
			u32 options;
			u32 test;
		पूर्ण __packed chipset_selftest;
		u64 addr;
		u64 handle;
	पूर्ण;
पूर्ण __packed;

/* All messages in any ControlVm queue have this layout. */
काष्ठा controlvm_message अणु
	काष्ठा controlvm_message_header hdr;
	काष्ठा controlvm_message_packet cmd;
पूर्ण __packed;

/*
 * काष्ठा visor_controlvm_channel
 * @काष्ठा header:
 * @gp_controlvm:			Guest phys addr of this channel.
 * @gp_partition_tables:		Guest phys addr of partition tables.
 * @gp_diag_guest:			Guest phys addr of diagnostic channel.
 * @gp_boot_romdisk:			Guest phys addr of (पढ़ो* only) Boot
 *					ROM disk.
 * @gp_boot_ramdisk:			Guest phys addr of writable Boot RAM
 *					disk.
 * @gp_acpi_table:			Guest phys addr of acpi table.
 * @gp_control_channel:			Guest phys addr of control channel.
 * @gp_diag_romdisk:			Guest phys addr of diagnostic ROM disk.
 * @gp_nvram:				Guest phys addr of NVRAM channel.
 * @request_payload_offset:		Offset to request payload area.
 * @event_payload_offset:		Offset to event payload area.
 * @request_payload_bytes:		Bytes available in request payload area.
 * @event_payload_bytes:		Bytes available in event payload area.
 * @control_channel_bytes:
 * @nvram_channel_bytes:		Bytes in PartitionNvram segment.
 * @message_bytes:			माप(CONTROLVM_MESSAGE).
 * @message_count:			CONTROLVM_MESSAGE_MAX.
 * @gp_smbios_table:			Guest phys addr of SMBIOS tables.
 * @gp_physical_smbios_table:		Guest phys addr of SMBIOS table.
 * @gp_reserved:			VISOR_MAX_GUESTS_PER_SERVICE.
 * @भव_guest_firmware_image_base:	Guest physical address of EFI firmware
 *					image base.
 * @भव_guest_firmware_entry_poपूर्णांक:	Guest physical address of EFI firmware
 *					entry poपूर्णांक.
 * @भव_guest_firmware_image_size:	Guest EFI firmware image size.
 * @भव_guest_firmware_boot_base:	GPA = 1MB where EFI firmware image is
 *					copied to.
 * @भव_guest_image_base:
 * @भव_guest_image_size:
 * @prototype_control_channel_offset:
 * @भव_guest_partition_handle:
 * @restore_action:			Restore Action field to restore the
 *					guest partition.
 * @dump_action:			For Winकरोws guests it shows अगर the
 *					visordisk is in dump mode.
 * @nvram_fail_count:
 * @saved_crash_message_count:		= CONTROLVM_CRASHMSG_MAX.
 * @saved_crash_message_offset:		Offset to request payload area needed
 *					क्रम crash dump.
 * @installation_error:			Type of error encountered during
 *					installation.
 * @installation_text_id:		Id of string to display.
 * @installation_reमुख्यing_steps:	Number of reमुख्यing installation steps
 *					(क्रम progress bars).
 * @tool_action:			VISOR_TOOL_ACTIONS Installation Action
 *					field.
 * @reserved: Alignment.
 * @काष्ठा efi_visor_ind:
 * @sp_reserved:
 * @reserved2:				Force संकेतs to begin on 128-byte
 *					cache line.
 * @काष्ठा request_queue:		Guest partition uses this queue to send
 *					requests to Control.
 * @काष्ठा response_queue:		Control uses this queue to respond to
 *					service or guest partition request.
 * @काष्ठा event_queue:			Control uses this queue to send events
 *					to guest partition.
 * @काष्ठा event_ack_queue:		Service or guest partition uses this
 *					queue to ack Control events.
 * @काष्ठा request_msg:			Request fixed-size message pool -
 *					करोes not include payload.
 * @काष्ठा response_msg:		Response fixed-size message pool -
 *					करोes not include payload.
 * @काष्ठा event_msg:			Event fixed-size message pool -
 *					करोes not include payload.
 * @काष्ठा event_ack_msg:		Ack fixed-size message pool -
 *					करोes not include payload.
 * @काष्ठा saved_crash_msg:		Message stored during IOVM creation to
 *					be reused after crash.
 */
काष्ठा visor_controlvm_channel अणु
	काष्ठा channel_header header;
	u64 gp_controlvm;
	u64 gp_partition_tables;
	u64 gp_diag_guest;
	u64 gp_boot_romdisk;
	u64 gp_boot_ramdisk;
	u64 gp_acpi_table;
	u64 gp_control_channel;
	u64 gp_diag_romdisk;
	u64 gp_nvram;
	u64 request_payload_offset;
	u64 event_payload_offset;
	u32 request_payload_bytes;
	u32 event_payload_bytes;
	u32 control_channel_bytes;
	u32 nvram_channel_bytes;
	u32 message_bytes;
	u32 message_count;
	u64 gp_smbios_table;
	u64 gp_physical_smbios_table;
	अक्षर gp_reserved[2688];
	u64 भव_guest_firmware_image_base;
	u64 भव_guest_firmware_entry_poपूर्णांक;
	u64 भव_guest_firmware_image_size;
	u64 भव_guest_firmware_boot_base;
	u64 भव_guest_image_base;
	u64 भव_guest_image_size;
	u64 prototype_control_channel_offset;
	u64 भव_guest_partition_handle;
	u16 restore_action;
	u16 dump_action;
	u16 nvram_fail_count;
	u16 saved_crash_message_count;
	u32 saved_crash_message_offset;
	u32 installation_error;
	u32 installation_text_id;
	u16 installation_reमुख्यing_steps;
	u8 tool_action;
	u8 reserved;
	काष्ठा efi_visor_indication efi_visor_ind;
	u32 sp_reserved;
	u8 reserved2[28];
	काष्ठा संकेत_queue_header request_queue;
	काष्ठा संकेत_queue_header response_queue;
	काष्ठा संकेत_queue_header event_queue;
	काष्ठा संकेत_queue_header event_ack_queue;
	काष्ठा controlvm_message request_msg[CONTROLVM_MESSAGE_MAX];
	काष्ठा controlvm_message response_msg[CONTROLVM_MESSAGE_MAX];
	काष्ठा controlvm_message event_msg[CONTROLVM_MESSAGE_MAX];
	काष्ठा controlvm_message event_ack_msg[CONTROLVM_MESSAGE_MAX];
	काष्ठा controlvm_message saved_crash_msg[CONTROLVM_CRASHMSG_MAX];
पूर्ण __packed;

/*
 * काष्ठा visor_controlvm_parameters_header
 *
 * The following header will be located at the beginning of PayloadVmOffset क्रम
 * various ControlVm commands. The receiver of a ControlVm command with a
 * PayloadVmOffset will dereference this address and then use connection_offset,
 * initiator_offset, and target_offset to get the location of UTF-8 क्रमmatted
 * strings that can be parsed to obtain command-specअगरic inक्रमmation. The value
 * of total_length should equal PayloadBytes. The क्रमmat of the strings at
 * PayloadVmOffset will take dअगरferent क्रमms depending on the message.
 */
काष्ठा visor_controlvm_parameters_header अणु
	u32 total_length;
	u32 header_length;
	u32 connection_offset;
	u32 connection_length;
	u32 initiator_offset;
	u32 initiator_length;
	u32 target_offset;
	u32 target_length;
	u32 client_offset;
	u32 client_length;
	u32 name_offset;
	u32 name_length;
	guid_t id;
	u32 revision;
	/* Natural alignment */
	u32 reserved;
पूर्ण __packed;

/* General Errors------------------------------------------------------[0-99] */
#घोषणा CONTROLVM_RESP_SUCCESS			   0
#घोषणा CONTROLVM_RESP_ALREADY_DONE		   1
#घोषणा CONTROLVM_RESP_IOREMAP_FAILED		   2
#घोषणा CONTROLVM_RESP_KMALLOC_FAILED		   3
#घोषणा CONTROLVM_RESP_ID_UNKNOWN		   4
#घोषणा CONTROLVM_RESP_ID_INVALID_FOR_CLIENT	   5
/* CONTROLVM_INIT_CHIPSET-------------------------------------------[100-199] */
#घोषणा CONTROLVM_RESP_CLIENT_SWITCHCOUNT_NONZERO  100
#घोषणा CONTROLVM_RESP_EXPECTED_CHIPSET_INIT	   101
/* Maximum Limit----------------------------------------------------[200-299] */
/* BUS_CREATE */
#घोषणा CONTROLVM_RESP_ERROR_MAX_BUSES		   201
/* DEVICE_CREATE */
#घोषणा CONTROLVM_RESP_ERROR_MAX_DEVICES	   202
/* Payload and Parameter Related------------------------------------[400-499] */
/* SWITCH_ATTACHEXTPORT, DEVICE_CONFIGURE */
#घोषणा CONTROLVM_RESP_PAYLOAD_INVALID		   400
/* Multiple */
#घोषणा CONTROLVM_RESP_INITIATOR_PARAMETER_INVALID 401
/* DEVICE_CONFIGURE */
#घोषणा CONTROLVM_RESP_TARGET_PARAMETER_INVALID	   402
/* DEVICE_CONFIGURE */
#घोषणा CONTROLVM_RESP_CLIENT_PARAMETER_INVALID	   403
/* Specअगरied[Packet Structure] Value--------------------------------[500-599] */
/* SWITCH_ATTACHINTPORT */
/* BUS_CONFIGURE, DEVICE_CREATE, DEVICE_CONFIG, DEVICE_DESTROY */
#घोषणा CONTROLVM_RESP_BUS_INVALID		   500
/* SWITCH_ATTACHINTPORT*/
/* DEVICE_CREATE, DEVICE_CONFIGURE, DEVICE_DESTROY */
#घोषणा CONTROLVM_RESP_DEVICE_INVALID		   501
/* DEVICE_CREATE, DEVICE_CONFIGURE */
#घोषणा CONTROLVM_RESP_CHANNEL_INVALID		   502
/* Partition Driver Callback Interface------------------------------[600-699] */
/* BUS_CREATE, BUS_DESTROY, DEVICE_CREATE, DEVICE_DESTROY */
#घोषणा CONTROLVM_RESP_VIRTPCI_DRIVER_FAILURE	   604
/* Unable to invoke VIRTPCI callback. VIRTPCI Callback वापसed error. */
/* BUS_CREATE, BUS_DESTROY, DEVICE_CREATE, DEVICE_DESTROY */
#घोषणा CONTROLVM_RESP_VIRTPCI_DRIVER_CALLBACK_ERROR   605
/* Generic device callback वापसed error. */
/* SWITCH_ATTACHEXTPORT, SWITCH_DETACHEXTPORT, DEVICE_CONFIGURE */
#घोषणा CONTROLVM_RESP_GENERIC_DRIVER_CALLBACK_ERROR   606
/* Bus Related------------------------------------------------------[700-799] */
/* BUS_DESTROY */
#घोषणा CONTROLVM_RESP_ERROR_BUS_DEVICE_ATTACHED       700
/* Channel Related--------------------------------------------------[800-899] */
/* GET_CHANNELINFO, DEVICE_DESTROY */
#घोषणा CONTROLVM_RESP_CHANNEL_TYPE_UNKNOWN	       800
/* DEVICE_CREATE */
#घोषणा CONTROLVM_RESP_CHANNEL_SIZE_TOO_SMALL	       801
/* Chipset Shutकरोwn Related---------------------------------------[1000-1099] */
#घोषणा CONTROLVM_RESP_CHIPSET_SHUTDOWN_FAILED	       1000
#घोषणा CONTROLVM_RESP_CHIPSET_SHUTDOWN_ALREADY_ACTIVE 1001
/* Chipset Stop Related-------------------------------------------[1100-1199] */
#घोषणा CONTROLVM_RESP_CHIPSET_STOP_FAILED_BUS	       1100
#घोषणा CONTROLVM_RESP_CHIPSET_STOP_FAILED_SWITCH      1101
/* Device Related-------------------------------------------------[1400-1499] */
#घोषणा CONTROLVM_RESP_DEVICE_UDEV_TIMEOUT	       1400

/* __CONTROLVMCHANNEL_H__ */
#पूर्ण_अगर
