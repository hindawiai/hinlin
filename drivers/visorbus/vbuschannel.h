<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2010 - 2015 UNISYS CORPORATION
 * All rights reserved.
 */

#अगर_अघोषित __VBUSCHANNEL_H__
#घोषणा __VBUSCHANNEL_H__

/*
 * The vbus channel is the channel area provided via the BUS_CREATE controlvm
 * message क्रम each भव bus.  This channel area is provided to both server
 * and client ends of the bus.  The channel header area is initialized by
 * the server, and the reमुख्यing inक्रमmation is filled in by the client.
 * We currently use this क्रम the client to provide various inक्रमmation about
 * the client devices and client drivers क्रम the server end to see.
 */

#समावेश <linux/uuid.h>
#समावेश <linux/visorbus.h>

/* अणु193b331b-c58f-11da-95a9-00e08161165fपूर्ण */
#घोषणा VISOR_VBUS_CHANNEL_GUID						\
	GUID_INIT(0x193b331b, 0xc58f, 0x11da,				\
		  0x95, 0xa9, 0x0, 0xe0, 0x81, 0x61, 0x16, 0x5f)

/*
 * Must increment this whenever you insert or delete fields within this channel
 * काष्ठा.  Also increment whenever you change the meaning of fields within this
 * channel काष्ठा so as to अवरोध pre-existing software.  Note that you can
 * usually add fields to the END of the channel काष्ठा withOUT needing to
 * increment this.
 */
#घोषणा VISOR_VBUS_CHANNEL_VERSIONID 1

/*
 * काष्ठा visor_vbus_deviceinfo
 * @devtype:  Short string identअगरying the device type.
 * @drvname:  Driver .sys file name.
 * @infostrs: Kernel vversion.
 * @reserved: Pad size to 256 bytes.
 *
 * An array of this काष्ठा is present in the channel area क्रम each vbus. It is
 * filled in by the client side to provide info about the device and driver from
 * the client's perspective.
 */
काष्ठा visor_vbus_deviceinfo अणु
	u8 devtype[16];
	u8 drvname[16];
	u8 infostrs[96];
	u8 reserved[128];
पूर्ण __packed;

/*
 * काष्ठा visor_vbus_headerinfo
 * @काष्ठा_bytes:	      Size of this काष्ठा in bytes.
 * @device_info_काष्ठा_bytes: Size of VISOR_VBUS_DEVICEINFO.
 * @dev_info_count:	      Num of items in DevInfo member. This is the
 *			      allocated size.
 * @chp_info_offset:	      Byte offset from beginning of this काष्ठा to the
 *			      ChpInfo काष्ठा.
 * @bus_info_offset:	      Byte offset from beginning of this काष्ठा to the
 *			      BusInfo काष्ठा.
 * @dev_info_offset:	      Byte offset from beginning of this काष्ठा to the
 *			      DevInfo array.
 * @reserved:		      Natural alignment.
 */
काष्ठा visor_vbus_headerinfo अणु
	u32 काष्ठा_bytes;
	u32 device_info_काष्ठा_bytes;
	u32 dev_info_count;
	u32 chp_info_offset;
	u32 bus_info_offset;
	u32 dev_info_offset;
	u8 reserved[104];
पूर्ण __packed;

/*
 * काष्ठा visor_vbus_channel
 * @channel_header: Initialized by server.
 * @hdr_info:	    Initialized by server.
 * @chp_info:	    Describes client chipset device and driver.
 * @bus_info:	    Describes client bus device and driver.
 * @dev_info:	    Describes client device and driver क्रम each device on the
 *		    bus.
 */
काष्ठा visor_vbus_channel अणु
	काष्ठा channel_header channel_header;
	काष्ठा visor_vbus_headerinfo hdr_info;
	काष्ठा visor_vbus_deviceinfo chp_info;
	काष्ठा visor_vbus_deviceinfo bus_info;
	काष्ठा visor_vbus_deviceinfo dev_info[0];
पूर्ण __packed;

#पूर्ण_अगर
