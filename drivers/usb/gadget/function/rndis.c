<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RNDIS MSG parser
 *
 * Authors:	Benedikt Spranger, Pengutronix
 *		Robert Schwebel, Pengutronix
 *
 *		This software was originally developed in conक्रमmance with
 *		Microsoft's Remote NDIS Specअगरication License Agreement.
 *
 * 03/12/2004 Kai-Uwe Bloem <linux-development@auerswald.de>
 *		Fixed message length bug in init_response
 *
 * 03/25/2004 Kai-Uwe Bloem <linux-development@auerswald.de>
 *		Fixed rndis_rm_hdr length bug.
 *
 * Copyright (C) 2004 by David Brownell
 *		updates to merge with Linux 2.6, better match RNDIS spec
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/idr.h>
#समावेश <linux/list.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/netdevice.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "u_rndis.h"

#अघोषित	VERBOSE_DEBUG

#समावेश "rndis.h"


/* The driver क्रम your USB chip needs to support ep0 OUT to work with
 * RNDIS, plus all three CDC Ethernet endpoपूर्णांकs (पूर्णांकerrupt not optional).
 *
 * Winकरोws hosts need an INF file like Documentation/usb/linux.inf
 * and will be happier अगर you provide the host_addr module parameter.
 */

#अगर 0
अटल पूर्णांक rndis_debug = 0;
module_param (rndis_debug, पूर्णांक, 0);
MODULE_PARM_DESC (rndis_debug, "enable debugging");
#अन्यथा
#घोषणा rndis_debug		0
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS

#घोषणा	NAME_TEMPLATE "driver/rndis-%03d"

#पूर्ण_अगर /* CONFIG_USB_GADGET_DEBUG_खाताS */

अटल DEFINE_IDA(rndis_ida);

/* Driver Version */
अटल स्थिर __le32 rndis_driver_version = cpu_to_le32(1);

/* Function Prototypes */
अटल rndis_resp_t *rndis_add_response(काष्ठा rndis_params *params,
					u32 length);

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS

अटल स्थिर काष्ठा proc_ops rndis_proc_ops;

#पूर्ण_अगर /* CONFIG_USB_GADGET_DEBUG_खाताS */

/* supported OIDs */
अटल स्थिर u32 oid_supported_list[] = अणु
	/* the general stuff */
	RNDIS_OID_GEN_SUPPORTED_LIST,
	RNDIS_OID_GEN_HARDWARE_STATUS,
	RNDIS_OID_GEN_MEDIA_SUPPORTED,
	RNDIS_OID_GEN_MEDIA_IN_USE,
	RNDIS_OID_GEN_MAXIMUM_FRAME_SIZE,
	RNDIS_OID_GEN_LINK_SPEED,
	RNDIS_OID_GEN_TRANSMIT_BLOCK_SIZE,
	RNDIS_OID_GEN_RECEIVE_BLOCK_SIZE,
	RNDIS_OID_GEN_VENDOR_ID,
	RNDIS_OID_GEN_VENDOR_DESCRIPTION,
	RNDIS_OID_GEN_VENDOR_DRIVER_VERSION,
	RNDIS_OID_GEN_CURRENT_PACKET_FILTER,
	RNDIS_OID_GEN_MAXIMUM_TOTAL_SIZE,
	RNDIS_OID_GEN_MEDIA_CONNECT_STATUS,
	RNDIS_OID_GEN_PHYSICAL_MEDIUM,

	/* the statistical stuff */
	RNDIS_OID_GEN_XMIT_OK,
	RNDIS_OID_GEN_RCV_OK,
	RNDIS_OID_GEN_XMIT_ERROR,
	RNDIS_OID_GEN_RCV_ERROR,
	RNDIS_OID_GEN_RCV_NO_BUFFER,
#अगर_घोषित	RNDIS_OPTIONAL_STATS
	RNDIS_OID_GEN_सूचीECTED_BYTES_XMIT,
	RNDIS_OID_GEN_सूचीECTED_FRAMES_XMIT,
	RNDIS_OID_GEN_MULTICAST_BYTES_XMIT,
	RNDIS_OID_GEN_MULTICAST_FRAMES_XMIT,
	RNDIS_OID_GEN_BROADCAST_BYTES_XMIT,
	RNDIS_OID_GEN_BROADCAST_FRAMES_XMIT,
	RNDIS_OID_GEN_सूचीECTED_BYTES_RCV,
	RNDIS_OID_GEN_सूचीECTED_FRAMES_RCV,
	RNDIS_OID_GEN_MULTICAST_BYTES_RCV,
	RNDIS_OID_GEN_MULTICAST_FRAMES_RCV,
	RNDIS_OID_GEN_BROADCAST_BYTES_RCV,
	RNDIS_OID_GEN_BROADCAST_FRAMES_RCV,
	RNDIS_OID_GEN_RCV_CRC_ERROR,
	RNDIS_OID_GEN_TRANSMIT_QUEUE_LENGTH,
#पूर्ण_अगर	/* RNDIS_OPTIONAL_STATS */

	/* mandatory 802.3 */
	/* the general stuff */
	RNDIS_OID_802_3_PERMANENT_ADDRESS,
	RNDIS_OID_802_3_CURRENT_ADDRESS,
	RNDIS_OID_802_3_MULTICAST_LIST,
	RNDIS_OID_802_3_MAC_OPTIONS,
	RNDIS_OID_802_3_MAXIMUM_LIST_SIZE,

	/* the statistical stuff */
	RNDIS_OID_802_3_RCV_ERROR_ALIGNMENT,
	RNDIS_OID_802_3_XMIT_ONE_COLLISION,
	RNDIS_OID_802_3_XMIT_MORE_COLLISIONS,
#अगर_घोषित	RNDIS_OPTIONAL_STATS
	RNDIS_OID_802_3_XMIT_DEFERRED,
	RNDIS_OID_802_3_XMIT_MAX_COLLISIONS,
	RNDIS_OID_802_3_RCV_OVERRUN,
	RNDIS_OID_802_3_XMIT_UNDERRUN,
	RNDIS_OID_802_3_XMIT_HEARTBEAT_FAILURE,
	RNDIS_OID_802_3_XMIT_TIMES_CRS_LOST,
	RNDIS_OID_802_3_XMIT_LATE_COLLISIONS,
#पूर्ण_अगर	/* RNDIS_OPTIONAL_STATS */

#अगर_घोषित	RNDIS_PM
	/* PM and wakeup are "mandatory" क्रम USB, but the RNDIS specs
	 * करोn't say what they mean ... and the NDIS specs are often
	 * confusing and/or ambiguous in this context.  (That is, more
	 * so than their specs क्रम the other OIDs.)
	 *
	 * FIXME someone who knows what these should करो, please
	 * implement them!
	 */

	/* घातer management */
	OID_PNP_CAPABILITIES,
	OID_PNP_QUERY_POWER,
	OID_PNP_SET_POWER,

#अगर_घोषित	RNDIS_WAKEUP
	/* wake up host */
	OID_PNP_ENABLE_WAKE_UP,
	OID_PNP_ADD_WAKE_UP_PATTERN,
	OID_PNP_REMOVE_WAKE_UP_PATTERN,
#पूर्ण_अगर	/* RNDIS_WAKEUP */
#पूर्ण_अगर	/* RNDIS_PM */
पूर्ण;


/* NDIS Functions */
अटल पूर्णांक gen_ndis_query_resp(काष्ठा rndis_params *params, u32 OID, u8 *buf,
			       अचिन्हित buf_len, rndis_resp_t *r)
अणु
	पूर्णांक retval = -ENOTSUPP;
	u32 length = 4;	/* usually */
	__le32 *outbuf;
	पूर्णांक i, count;
	rndis_query_cmplt_type *resp;
	काष्ठा net_device *net;
	काष्ठा rtnl_link_stats64 temp;
	स्थिर काष्ठा rtnl_link_stats64 *stats;

	अगर (!r) वापस -ENOMEM;
	resp = (rndis_query_cmplt_type *)r->buf;

	अगर (!resp) वापस -ENOMEM;

	अगर (buf_len && rndis_debug > 1) अणु
		pr_debug("query OID %08x value, len %d:\n", OID, buf_len);
		क्रम (i = 0; i < buf_len; i += 16) अणु
			pr_debug("%03d: %08x %08x %08x %08x\n", i,
				get_unaligned_le32(&buf[i]),
				get_unaligned_le32(&buf[i + 4]),
				get_unaligned_le32(&buf[i + 8]),
				get_unaligned_le32(&buf[i + 12]));
		पूर्ण
	पूर्ण

	/* response goes here, right after the header */
	outbuf = (__le32 *)&resp[1];
	resp->Inक्रमmationBufferOffset = cpu_to_le32(16);

	net = params->dev;
	stats = dev_get_stats(net, &temp);

	चयन (OID) अणु

	/* general oids (table 4-1) */

	/* mandatory */
	हाल RNDIS_OID_GEN_SUPPORTED_LIST:
		pr_debug("%s: RNDIS_OID_GEN_SUPPORTED_LIST\n", __func__);
		length = माप(oid_supported_list);
		count  = length / माप(u32);
		क्रम (i = 0; i < count; i++)
			outbuf[i] = cpu_to_le32(oid_supported_list[i]);
		retval = 0;
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_HARDWARE_STATUS:
		pr_debug("%s: RNDIS_OID_GEN_HARDWARE_STATUS\n", __func__);
		/* Bogus question!
		 * Hardware must be पढ़ोy to receive high level protocols.
		 * BTW:
		 * reddite ergo quae sunt Caesaris Caesari
		 * et quae sunt Dei Deo!
		 */
		*outbuf = cpu_to_le32(0);
		retval = 0;
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_MEDIA_SUPPORTED:
		pr_debug("%s: RNDIS_OID_GEN_MEDIA_SUPPORTED\n", __func__);
		*outbuf = cpu_to_le32(params->medium);
		retval = 0;
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_MEDIA_IN_USE:
		pr_debug("%s: RNDIS_OID_GEN_MEDIA_IN_USE\n", __func__);
		/* one medium, one transport... (maybe you करो it better) */
		*outbuf = cpu_to_le32(params->medium);
		retval = 0;
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_MAXIMUM_FRAME_SIZE:
		pr_debug("%s: RNDIS_OID_GEN_MAXIMUM_FRAME_SIZE\n", __func__);
		अगर (params->dev) अणु
			*outbuf = cpu_to_le32(params->dev->mtu);
			retval = 0;
		पूर्ण
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_LINK_SPEED:
		अगर (rndis_debug > 1)
			pr_debug("%s: RNDIS_OID_GEN_LINK_SPEED\n", __func__);
		अगर (params->media_state == RNDIS_MEDIA_STATE_DISCONNECTED)
			*outbuf = cpu_to_le32(0);
		अन्यथा
			*outbuf = cpu_to_le32(params->speed);
		retval = 0;
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_TRANSMIT_BLOCK_SIZE:
		pr_debug("%s: RNDIS_OID_GEN_TRANSMIT_BLOCK_SIZE\n", __func__);
		अगर (params->dev) अणु
			*outbuf = cpu_to_le32(params->dev->mtu);
			retval = 0;
		पूर्ण
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_RECEIVE_BLOCK_SIZE:
		pr_debug("%s: RNDIS_OID_GEN_RECEIVE_BLOCK_SIZE\n", __func__);
		अगर (params->dev) अणु
			*outbuf = cpu_to_le32(params->dev->mtu);
			retval = 0;
		पूर्ण
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_VENDOR_ID:
		pr_debug("%s: RNDIS_OID_GEN_VENDOR_ID\n", __func__);
		*outbuf = cpu_to_le32(params->venकरोrID);
		retval = 0;
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_VENDOR_DESCRIPTION:
		pr_debug("%s: RNDIS_OID_GEN_VENDOR_DESCRIPTION\n", __func__);
		अगर (params->venकरोrDescr) अणु
			length = म_माप(params->venकरोrDescr);
			स_नकल(outbuf, params->venकरोrDescr, length);
		पूर्ण अन्यथा अणु
			outbuf[0] = 0;
		पूर्ण
		retval = 0;
		अवरोध;

	हाल RNDIS_OID_GEN_VENDOR_DRIVER_VERSION:
		pr_debug("%s: RNDIS_OID_GEN_VENDOR_DRIVER_VERSION\n", __func__);
		/* Created as LE */
		*outbuf = rndis_driver_version;
		retval = 0;
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_CURRENT_PACKET_FILTER:
		pr_debug("%s: RNDIS_OID_GEN_CURRENT_PACKET_FILTER\n", __func__);
		*outbuf = cpu_to_le32(*params->filter);
		retval = 0;
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_MAXIMUM_TOTAL_SIZE:
		pr_debug("%s: RNDIS_OID_GEN_MAXIMUM_TOTAL_SIZE\n", __func__);
		*outbuf = cpu_to_le32(RNDIS_MAX_TOTAL_SIZE);
		retval = 0;
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_MEDIA_CONNECT_STATUS:
		अगर (rndis_debug > 1)
			pr_debug("%s: RNDIS_OID_GEN_MEDIA_CONNECT_STATUS\n", __func__);
		*outbuf = cpu_to_le32(params->media_state);
		retval = 0;
		अवरोध;

	हाल RNDIS_OID_GEN_PHYSICAL_MEDIUM:
		pr_debug("%s: RNDIS_OID_GEN_PHYSICAL_MEDIUM\n", __func__);
		*outbuf = cpu_to_le32(0);
		retval = 0;
		अवरोध;

	/* The RNDIS specअगरication is incomplete/wrong.   Some versions
	 * of MS-Winकरोws expect OIDs that aren't specअगरied there.  Other
	 * versions emit undefined RNDIS messages. DOCUMENT ALL THESE!
	 */
	हाल RNDIS_OID_GEN_MAC_OPTIONS:		/* from WinME */
		pr_debug("%s: RNDIS_OID_GEN_MAC_OPTIONS\n", __func__);
		*outbuf = cpu_to_le32(
			  RNDIS_MAC_OPTION_RECEIVE_SERIALIZED
			| RNDIS_MAC_OPTION_FULL_DUPLEX);
		retval = 0;
		अवरोध;

	/* statistics OIDs (table 4-2) */

	/* mandatory */
	हाल RNDIS_OID_GEN_XMIT_OK:
		अगर (rndis_debug > 1)
			pr_debug("%s: RNDIS_OID_GEN_XMIT_OK\n", __func__);
		अगर (stats) अणु
			*outbuf = cpu_to_le32(stats->tx_packets
				- stats->tx_errors - stats->tx_dropped);
			retval = 0;
		पूर्ण
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_RCV_OK:
		अगर (rndis_debug > 1)
			pr_debug("%s: RNDIS_OID_GEN_RCV_OK\n", __func__);
		अगर (stats) अणु
			*outbuf = cpu_to_le32(stats->rx_packets
				- stats->rx_errors - stats->rx_dropped);
			retval = 0;
		पूर्ण
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_XMIT_ERROR:
		अगर (rndis_debug > 1)
			pr_debug("%s: RNDIS_OID_GEN_XMIT_ERROR\n", __func__);
		अगर (stats) अणु
			*outbuf = cpu_to_le32(stats->tx_errors);
			retval = 0;
		पूर्ण
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_RCV_ERROR:
		अगर (rndis_debug > 1)
			pr_debug("%s: RNDIS_OID_GEN_RCV_ERROR\n", __func__);
		अगर (stats) अणु
			*outbuf = cpu_to_le32(stats->rx_errors);
			retval = 0;
		पूर्ण
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_GEN_RCV_NO_BUFFER:
		pr_debug("%s: RNDIS_OID_GEN_RCV_NO_BUFFER\n", __func__);
		अगर (stats) अणु
			*outbuf = cpu_to_le32(stats->rx_dropped);
			retval = 0;
		पूर्ण
		अवरोध;

	/* ieee802.3 OIDs (table 4-3) */

	/* mandatory */
	हाल RNDIS_OID_802_3_PERMANENT_ADDRESS:
		pr_debug("%s: RNDIS_OID_802_3_PERMANENT_ADDRESS\n", __func__);
		अगर (params->dev) अणु
			length = ETH_ALEN;
			स_नकल(outbuf, params->host_mac, length);
			retval = 0;
		पूर्ण
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_802_3_CURRENT_ADDRESS:
		pr_debug("%s: RNDIS_OID_802_3_CURRENT_ADDRESS\n", __func__);
		अगर (params->dev) अणु
			length = ETH_ALEN;
			स_नकल(outbuf, params->host_mac, length);
			retval = 0;
		पूर्ण
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_802_3_MULTICAST_LIST:
		pr_debug("%s: RNDIS_OID_802_3_MULTICAST_LIST\n", __func__);
		/* Multicast base address only */
		*outbuf = cpu_to_le32(0xE0000000);
		retval = 0;
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_802_3_MAXIMUM_LIST_SIZE:
		pr_debug("%s: RNDIS_OID_802_3_MAXIMUM_LIST_SIZE\n", __func__);
		/* Multicast base address only */
		*outbuf = cpu_to_le32(1);
		retval = 0;
		अवरोध;

	हाल RNDIS_OID_802_3_MAC_OPTIONS:
		pr_debug("%s: RNDIS_OID_802_3_MAC_OPTIONS\n", __func__);
		*outbuf = cpu_to_le32(0);
		retval = 0;
		अवरोध;

	/* ieee802.3 statistics OIDs (table 4-4) */

	/* mandatory */
	हाल RNDIS_OID_802_3_RCV_ERROR_ALIGNMENT:
		pr_debug("%s: RNDIS_OID_802_3_RCV_ERROR_ALIGNMENT\n", __func__);
		अगर (stats) अणु
			*outbuf = cpu_to_le32(stats->rx_frame_errors);
			retval = 0;
		पूर्ण
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_802_3_XMIT_ONE_COLLISION:
		pr_debug("%s: RNDIS_OID_802_3_XMIT_ONE_COLLISION\n", __func__);
		*outbuf = cpu_to_le32(0);
		retval = 0;
		अवरोध;

	/* mandatory */
	हाल RNDIS_OID_802_3_XMIT_MORE_COLLISIONS:
		pr_debug("%s: RNDIS_OID_802_3_XMIT_MORE_COLLISIONS\n", __func__);
		*outbuf = cpu_to_le32(0);
		retval = 0;
		अवरोध;

	शेष:
		pr_warn("%s: query unknown OID 0x%08X\n", __func__, OID);
	पूर्ण
	अगर (retval < 0)
		length = 0;

	resp->Inक्रमmationBufferLength = cpu_to_le32(length);
	r->length = length + माप(*resp);
	resp->MessageLength = cpu_to_le32(r->length);
	वापस retval;
पूर्ण

अटल पूर्णांक gen_ndis_set_resp(काष्ठा rndis_params *params, u32 OID,
			     u8 *buf, u32 buf_len, rndis_resp_t *r)
अणु
	rndis_set_cmplt_type *resp;
	पूर्णांक i, retval = -ENOTSUPP;

	अगर (!r)
		वापस -ENOMEM;
	resp = (rndis_set_cmplt_type *)r->buf;
	अगर (!resp)
		वापस -ENOMEM;

	अगर (buf_len && rndis_debug > 1) अणु
		pr_debug("set OID %08x value, len %d:\n", OID, buf_len);
		क्रम (i = 0; i < buf_len; i += 16) अणु
			pr_debug("%03d: %08x %08x %08x %08x\n", i,
				get_unaligned_le32(&buf[i]),
				get_unaligned_le32(&buf[i + 4]),
				get_unaligned_le32(&buf[i + 8]),
				get_unaligned_le32(&buf[i + 12]));
		पूर्ण
	पूर्ण

	चयन (OID) अणु
	हाल RNDIS_OID_GEN_CURRENT_PACKET_FILTER:

		/* these NDIS_PACKET_TYPE_* bitflags are shared with
		 * cdc_filter; it's not RNDIS-specअगरic
		 * NDIS_PACKET_TYPE_x == USB_CDC_PACKET_TYPE_x क्रम x in:
		 *	PROMISCUOUS, सूचीECTED,
		 *	MULTICAST, ALL_MULTICAST, BROADCAST
		 */
		*params->filter = (u16)get_unaligned_le32(buf);
		pr_debug("%s: RNDIS_OID_GEN_CURRENT_PACKET_FILTER %08x\n",
			__func__, *params->filter);

		/* this call has a signअगरicant side effect:  it's
		 * what makes the packet flow start and stop, like
		 * activating the CDC Ethernet altsetting.
		 */
		retval = 0;
		अगर (*params->filter) अणु
			params->state = RNDIS_DATA_INITIALIZED;
			netअगर_carrier_on(params->dev);
			अगर (netअगर_running(params->dev))
				netअगर_wake_queue(params->dev);
		पूर्ण अन्यथा अणु
			params->state = RNDIS_INITIALIZED;
			netअगर_carrier_off(params->dev);
			netअगर_stop_queue(params->dev);
		पूर्ण
		अवरोध;

	हाल RNDIS_OID_802_3_MULTICAST_LIST:
		/* I think we can ignore this */
		pr_debug("%s: RNDIS_OID_802_3_MULTICAST_LIST\n", __func__);
		retval = 0;
		अवरोध;

	शेष:
		pr_warn("%s: set unknown OID 0x%08X, size %d\n",
			__func__, OID, buf_len);
	पूर्ण

	वापस retval;
पूर्ण

/*
 * Response Functions
 */

अटल पूर्णांक rndis_init_response(काष्ठा rndis_params *params,
			       rndis_init_msg_type *buf)
अणु
	rndis_init_cmplt_type *resp;
	rndis_resp_t *r;

	अगर (!params->dev)
		वापस -ENOTSUPP;

	r = rndis_add_response(params, माप(rndis_init_cmplt_type));
	अगर (!r)
		वापस -ENOMEM;
	resp = (rndis_init_cmplt_type *)r->buf;

	resp->MessageType = cpu_to_le32(RNDIS_MSG_INIT_C);
	resp->MessageLength = cpu_to_le32(52);
	resp->RequestID = buf->RequestID; /* Still LE in msg buffer */
	resp->Status = cpu_to_le32(RNDIS_STATUS_SUCCESS);
	resp->MajorVersion = cpu_to_le32(RNDIS_MAJOR_VERSION);
	resp->MinorVersion = cpu_to_le32(RNDIS_MINOR_VERSION);
	resp->DeviceFlags = cpu_to_le32(RNDIS_DF_CONNECTIONLESS);
	resp->Medium = cpu_to_le32(RNDIS_MEDIUM_802_3);
	resp->MaxPacketsPerTransfer = cpu_to_le32(1);
	resp->MaxTransferSize = cpu_to_le32(
		  params->dev->mtu
		+ माप(काष्ठा ethhdr)
		+ माप(काष्ठा rndis_packet_msg_type)
		+ 22);
	resp->PacketAlignmentFactor = cpu_to_le32(0);
	resp->AFListOffset = cpu_to_le32(0);
	resp->AFListSize = cpu_to_le32(0);

	params->resp_avail(params->v);
	वापस 0;
पूर्ण

अटल पूर्णांक rndis_query_response(काष्ठा rndis_params *params,
				rndis_query_msg_type *buf)
अणु
	rndis_query_cmplt_type *resp;
	rndis_resp_t *r;

	/* pr_debug("%s: OID = %08X\n", __func__, cpu_to_le32(buf->OID)); */
	अगर (!params->dev)
		वापस -ENOTSUPP;

	/*
	 * we need more memory:
	 * gen_ndis_query_resp expects enough space क्रम
	 * rndis_query_cmplt_type followed by data.
	 * oid_supported_list is the largest data reply
	 */
	r = rndis_add_response(params,
		माप(oid_supported_list) + माप(rndis_query_cmplt_type));
	अगर (!r)
		वापस -ENOMEM;
	resp = (rndis_query_cmplt_type *)r->buf;

	resp->MessageType = cpu_to_le32(RNDIS_MSG_QUERY_C);
	resp->RequestID = buf->RequestID; /* Still LE in msg buffer */

	अगर (gen_ndis_query_resp(params, le32_to_cpu(buf->OID),
			le32_to_cpu(buf->Inक्रमmationBufferOffset)
					+ 8 + (u8 *)buf,
			le32_to_cpu(buf->Inक्रमmationBufferLength),
			r)) अणु
		/* OID not supported */
		resp->Status = cpu_to_le32(RNDIS_STATUS_NOT_SUPPORTED);
		resp->MessageLength = cpu_to_le32(माप *resp);
		resp->Inक्रमmationBufferLength = cpu_to_le32(0);
		resp->Inक्रमmationBufferOffset = cpu_to_le32(0);
	पूर्ण अन्यथा
		resp->Status = cpu_to_le32(RNDIS_STATUS_SUCCESS);

	params->resp_avail(params->v);
	वापस 0;
पूर्ण

अटल पूर्णांक rndis_set_response(काष्ठा rndis_params *params,
			      rndis_set_msg_type *buf)
अणु
	u32 BufLength, BufOffset;
	rndis_set_cmplt_type *resp;
	rndis_resp_t *r;

	r = rndis_add_response(params, माप(rndis_set_cmplt_type));
	अगर (!r)
		वापस -ENOMEM;
	resp = (rndis_set_cmplt_type *)r->buf;

	BufLength = le32_to_cpu(buf->Inक्रमmationBufferLength);
	BufOffset = le32_to_cpu(buf->Inक्रमmationBufferOffset);

#अगर_घोषित	VERBOSE_DEBUG
	pr_debug("%s: Length: %d\n", __func__, BufLength);
	pr_debug("%s: Offset: %d\n", __func__, BufOffset);
	pr_debug("%s: InfoBuffer: ", __func__);

	क्रम (i = 0; i < BufLength; i++) अणु
		pr_debug("%02x ", *(((u8 *) buf) + i + 8 + BufOffset));
	पूर्ण

	pr_debug("\n");
#पूर्ण_अगर

	resp->MessageType = cpu_to_le32(RNDIS_MSG_SET_C);
	resp->MessageLength = cpu_to_le32(16);
	resp->RequestID = buf->RequestID; /* Still LE in msg buffer */
	अगर (gen_ndis_set_resp(params, le32_to_cpu(buf->OID),
			((u8 *)buf) + 8 + BufOffset, BufLength, r))
		resp->Status = cpu_to_le32(RNDIS_STATUS_NOT_SUPPORTED);
	अन्यथा
		resp->Status = cpu_to_le32(RNDIS_STATUS_SUCCESS);

	params->resp_avail(params->v);
	वापस 0;
पूर्ण

अटल पूर्णांक rndis_reset_response(काष्ठा rndis_params *params,
				rndis_reset_msg_type *buf)
अणु
	rndis_reset_cmplt_type *resp;
	rndis_resp_t *r;
	u8 *xbuf;
	u32 length;

	/* drain the response queue */
	जबतक ((xbuf = rndis_get_next_response(params, &length)))
		rndis_मुक्त_response(params, xbuf);

	r = rndis_add_response(params, माप(rndis_reset_cmplt_type));
	अगर (!r)
		वापस -ENOMEM;
	resp = (rndis_reset_cmplt_type *)r->buf;

	resp->MessageType = cpu_to_le32(RNDIS_MSG_RESET_C);
	resp->MessageLength = cpu_to_le32(16);
	resp->Status = cpu_to_le32(RNDIS_STATUS_SUCCESS);
	/* resent inक्रमmation */
	resp->AddressingReset = cpu_to_le32(1);

	params->resp_avail(params->v);
	वापस 0;
पूर्ण

अटल पूर्णांक rndis_keepalive_response(काष्ठा rndis_params *params,
				    rndis_keepalive_msg_type *buf)
अणु
	rndis_keepalive_cmplt_type *resp;
	rndis_resp_t *r;

	/* host "should" check only in RNDIS_DATA_INITIALIZED state */

	r = rndis_add_response(params, माप(rndis_keepalive_cmplt_type));
	अगर (!r)
		वापस -ENOMEM;
	resp = (rndis_keepalive_cmplt_type *)r->buf;

	resp->MessageType = cpu_to_le32(RNDIS_MSG_KEEPALIVE_C);
	resp->MessageLength = cpu_to_le32(16);
	resp->RequestID = buf->RequestID; /* Still LE in msg buffer */
	resp->Status = cpu_to_le32(RNDIS_STATUS_SUCCESS);

	params->resp_avail(params->v);
	वापस 0;
पूर्ण


/*
 * Device to Host Comunication
 */
अटल पूर्णांक rndis_indicate_status_msg(काष्ठा rndis_params *params, u32 status)
अणु
	rndis_indicate_status_msg_type *resp;
	rndis_resp_t *r;

	अगर (params->state == RNDIS_UNINITIALIZED)
		वापस -ENOTSUPP;

	r = rndis_add_response(params, माप(rndis_indicate_status_msg_type));
	अगर (!r)
		वापस -ENOMEM;
	resp = (rndis_indicate_status_msg_type *)r->buf;

	resp->MessageType = cpu_to_le32(RNDIS_MSG_INDICATE);
	resp->MessageLength = cpu_to_le32(20);
	resp->Status = cpu_to_le32(status);
	resp->StatusBufferLength = cpu_to_le32(0);
	resp->StatusBufferOffset = cpu_to_le32(0);

	params->resp_avail(params->v);
	वापस 0;
पूर्ण

पूर्णांक rndis_संकेत_connect(काष्ठा rndis_params *params)
अणु
	params->media_state = RNDIS_MEDIA_STATE_CONNECTED;
	वापस rndis_indicate_status_msg(params, RNDIS_STATUS_MEDIA_CONNECT);
पूर्ण
EXPORT_SYMBOL_GPL(rndis_संकेत_connect);

पूर्णांक rndis_संकेत_disconnect(काष्ठा rndis_params *params)
अणु
	params->media_state = RNDIS_MEDIA_STATE_DISCONNECTED;
	वापस rndis_indicate_status_msg(params, RNDIS_STATUS_MEDIA_DISCONNECT);
पूर्ण
EXPORT_SYMBOL_GPL(rndis_संकेत_disconnect);

व्योम rndis_uninit(काष्ठा rndis_params *params)
अणु
	u8 *buf;
	u32 length;

	अगर (!params)
		वापस;
	params->state = RNDIS_UNINITIALIZED;

	/* drain the response queue */
	जबतक ((buf = rndis_get_next_response(params, &length)))
		rndis_मुक्त_response(params, buf);
पूर्ण
EXPORT_SYMBOL_GPL(rndis_uninit);

व्योम rndis_set_host_mac(काष्ठा rndis_params *params, स्थिर u8 *addr)
अणु
	params->host_mac = addr;
पूर्ण
EXPORT_SYMBOL_GPL(rndis_set_host_mac);

/*
 * Message Parser
 */
पूर्णांक rndis_msg_parser(काष्ठा rndis_params *params, u8 *buf)
अणु
	u32 MsgType, MsgLength;
	__le32 *पंचांगp;

	अगर (!buf)
		वापस -ENOMEM;

	पंचांगp = (__le32 *)buf;
	MsgType   = get_unaligned_le32(पंचांगp++);
	MsgLength = get_unaligned_le32(पंचांगp++);

	अगर (!params)
		वापस -ENOTSUPP;

	/* NOTE: RNDIS is *EXTREMELY* chatty ... Winकरोws स्थिरantly polls क्रम
	 * rx/tx statistics and link status, in addition to KEEPALIVE traffic
	 * and normal HC level polling to see अगर there's any IN traffic.
	 */

	/* For USB: responses may take up to 10 seconds */
	चयन (MsgType) अणु
	हाल RNDIS_MSG_INIT:
		pr_debug("%s: RNDIS_MSG_INIT\n",
			__func__);
		params->state = RNDIS_INITIALIZED;
		वापस rndis_init_response(params, (rndis_init_msg_type *)buf);

	हाल RNDIS_MSG_HALT:
		pr_debug("%s: RNDIS_MSG_HALT\n",
			__func__);
		params->state = RNDIS_UNINITIALIZED;
		अगर (params->dev) अणु
			netअगर_carrier_off(params->dev);
			netअगर_stop_queue(params->dev);
		पूर्ण
		वापस 0;

	हाल RNDIS_MSG_QUERY:
		वापस rndis_query_response(params,
					(rndis_query_msg_type *)buf);

	हाल RNDIS_MSG_SET:
		वापस rndis_set_response(params, (rndis_set_msg_type *)buf);

	हाल RNDIS_MSG_RESET:
		pr_debug("%s: RNDIS_MSG_RESET\n",
			__func__);
		वापस rndis_reset_response(params,
					(rndis_reset_msg_type *)buf);

	हाल RNDIS_MSG_KEEPALIVE:
		/* For USB: host करोes this every 5 seconds */
		अगर (rndis_debug > 1)
			pr_debug("%s: RNDIS_MSG_KEEPALIVE\n",
				__func__);
		वापस rndis_keepalive_response(params,
						 (rndis_keepalive_msg_type *)
						 buf);

	शेष:
		/* At least Winकरोws XP emits some undefined RNDIS messages.
		 * In one हाल those messages seemed to relate to the host
		 * suspending itself.
		 */
		pr_warn("%s: unknown RNDIS message 0x%08X len %d\n",
			__func__, MsgType, MsgLength);
		/* Garbled message can be huge, so limit what we display */
		अगर (MsgLength > 16)
			MsgLength = 16;
		prपूर्णांक_hex_dump_bytes(__func__, DUMP_PREFIX_OFFSET,
				     buf, MsgLength);
		अवरोध;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL_GPL(rndis_msg_parser);

अटल अंतरभूत पूर्णांक rndis_get_nr(व्योम)
अणु
	वापस ida_simple_get(&rndis_ida, 0, 0, GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम rndis_put_nr(पूर्णांक nr)
अणु
	ida_simple_हटाओ(&rndis_ida, nr);
पूर्ण

काष्ठा rndis_params *rndis_रेजिस्टर(व्योम (*resp_avail)(व्योम *v), व्योम *v)
अणु
	काष्ठा rndis_params *params;
	पूर्णांक i;

	अगर (!resp_avail)
		वापस ERR_PTR(-EINVAL);

	i = rndis_get_nr();
	अगर (i < 0) अणु
		pr_debug("failed\n");

		वापस ERR_PTR(-ENODEV);
	पूर्ण

	params = kzalloc(माप(*params), GFP_KERNEL);
	अगर (!params) अणु
		rndis_put_nr(i);

		वापस ERR_PTR(-ENOMEM);
	पूर्ण

#अगर_घोषित	CONFIG_USB_GADGET_DEBUG_खाताS
	अणु
		काष्ठा proc_dir_entry *proc_entry;
		अक्षर name[20];

		प्र_लिखो(name, NAME_TEMPLATE, i);
		proc_entry = proc_create_data(name, 0660, शून्य,
					      &rndis_proc_ops, params);
		अगर (!proc_entry) अणु
			kमुक्त(params);
			rndis_put_nr(i);

			वापस ERR_PTR(-EIO);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	params->confignr = i;
	params->used = 1;
	params->state = RNDIS_UNINITIALIZED;
	params->media_state = RNDIS_MEDIA_STATE_DISCONNECTED;
	params->resp_avail = resp_avail;
	params->v = v;
	INIT_LIST_HEAD(&params->resp_queue);
	pr_debug("%s: configNr = %d\n", __func__, i);

	वापस params;
पूर्ण
EXPORT_SYMBOL_GPL(rndis_रेजिस्टर);

व्योम rndis_deरेजिस्टर(काष्ठा rndis_params *params)
अणु
	पूर्णांक i;

	pr_debug("%s:\n", __func__);

	अगर (!params)
		वापस;

	i = params->confignr;

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS
	अणु
		अक्षर name[20];

		प्र_लिखो(name, NAME_TEMPLATE, i);
		हटाओ_proc_entry(name, शून्य);
	पूर्ण
#पूर्ण_अगर

	kमुक्त(params);
	rndis_put_nr(i);
पूर्ण
EXPORT_SYMBOL_GPL(rndis_deरेजिस्टर);
पूर्णांक rndis_set_param_dev(काष्ठा rndis_params *params, काष्ठा net_device *dev,
			u16 *cdc_filter)
अणु
	pr_debug("%s:\n", __func__);
	अगर (!dev)
		वापस -EINVAL;
	अगर (!params)
		वापस -1;

	params->dev = dev;
	params->filter = cdc_filter;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rndis_set_param_dev);

पूर्णांक rndis_set_param_venकरोr(काष्ठा rndis_params *params, u32 venकरोrID,
			   स्थिर अक्षर *venकरोrDescr)
अणु
	pr_debug("%s:\n", __func__);
	अगर (!venकरोrDescr) वापस -1;
	अगर (!params)
		वापस -1;

	params->venकरोrID = venकरोrID;
	params->venकरोrDescr = venकरोrDescr;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rndis_set_param_venकरोr);

पूर्णांक rndis_set_param_medium(काष्ठा rndis_params *params, u32 medium, u32 speed)
अणु
	pr_debug("%s: %u %u\n", __func__, medium, speed);
	अगर (!params)
		वापस -1;

	params->medium = medium;
	params->speed = speed;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rndis_set_param_medium);

व्योम rndis_add_hdr(काष्ठा sk_buff *skb)
अणु
	काष्ठा rndis_packet_msg_type *header;

	अगर (!skb)
		वापस;
	header = skb_push(skb, माप(*header));
	स_रखो(header, 0, माप *header);
	header->MessageType = cpu_to_le32(RNDIS_MSG_PACKET);
	header->MessageLength = cpu_to_le32(skb->len);
	header->DataOffset = cpu_to_le32(36);
	header->DataLength = cpu_to_le32(skb->len - माप(*header));
पूर्ण
EXPORT_SYMBOL_GPL(rndis_add_hdr);

व्योम rndis_मुक्त_response(काष्ठा rndis_params *params, u8 *buf)
अणु
	rndis_resp_t *r, *n;

	list_क्रम_each_entry_safe(r, n, &params->resp_queue, list) अणु
		अगर (r->buf == buf) अणु
			list_del(&r->list);
			kमुक्त(r);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rndis_मुक्त_response);

u8 *rndis_get_next_response(काष्ठा rndis_params *params, u32 *length)
अणु
	rndis_resp_t *r, *n;

	अगर (!length) वापस शून्य;

	list_क्रम_each_entry_safe(r, n, &params->resp_queue, list) अणु
		अगर (!r->send) अणु
			r->send = 1;
			*length = r->length;
			वापस r->buf;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(rndis_get_next_response);

अटल rndis_resp_t *rndis_add_response(काष्ठा rndis_params *params, u32 length)
अणु
	rndis_resp_t *r;

	/* NOTE: this माला_लो copied पूर्णांकo ether.c USB_बफ_मान bytes ... */
	r = kदो_स्मृति(माप(rndis_resp_t) + length, GFP_ATOMIC);
	अगर (!r) वापस शून्य;

	r->buf = (u8 *)(r + 1);
	r->length = length;
	r->send = 0;

	list_add_tail(&r->list, &params->resp_queue);
	वापस r;
पूर्ण

पूर्णांक rndis_rm_hdr(काष्ठा gether *port,
			काष्ठा sk_buff *skb,
			काष्ठा sk_buff_head *list)
अणु
	/* पंचांगp poपूर्णांकs to a काष्ठा rndis_packet_msg_type */
	__le32 *पंचांगp = (व्योम *)skb->data;

	/* MessageType, MessageLength */
	अगर (cpu_to_le32(RNDIS_MSG_PACKET)
			!= get_unaligned(पंचांगp++)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस -EINVAL;
	पूर्ण
	पंचांगp++;

	/* DataOffset, DataLength */
	अगर (!skb_pull(skb, get_unaligned_le32(पंचांगp++) + 8)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस -EOVERFLOW;
	पूर्ण
	skb_trim(skb, get_unaligned_le32(पंचांगp++));

	skb_queue_tail(list, skb);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rndis_rm_hdr);

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS

अटल पूर्णांक rndis_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	rndis_params *param = m->निजी;

	seq_म_लिखो(m,
			 "Config Nr. %d\n"
			 "used      : %s\n"
			 "state     : %s\n"
			 "medium    : 0x%08X\n"
			 "speed     : %d\n"
			 "cable     : %s\n"
			 "vendor ID : 0x%08X\n"
			 "vendor    : %s\n",
			 param->confignr, (param->used) ? "y" : "n",
			 (अणु अक्षर *s = "?";
			 चयन (param->state) अणु
			 हाल RNDIS_UNINITIALIZED:
				s = "RNDIS_UNINITIALIZED"; अवरोध;
			 हाल RNDIS_INITIALIZED:
				s = "RNDIS_INITIALIZED"; अवरोध;
			 हाल RNDIS_DATA_INITIALIZED:
				s = "RNDIS_DATA_INITIALIZED"; अवरोध;
			पूर्ण s; पूर्ण),
			 param->medium,
			 (param->media_state) ? 0 : param->speed*100,
			 (param->media_state) ? "disconnected" : "connected",
			 param->venकरोrID, param->venकरोrDescr);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार rndis_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				माप_प्रकार count, loff_t *ppos)
अणु
	rndis_params *p = PDE_DATA(file_inode(file));
	u32 speed = 0;
	पूर्णांक i, fl_speed = 0;

	क्रम (i = 0; i < count; i++) अणु
		अक्षर c;
		अगर (get_user(c, buffer))
			वापस -EFAULT;
		चयन (c) अणु
		हाल '0':
		हाल '1':
		हाल '2':
		हाल '3':
		हाल '4':
		हाल '5':
		हाल '6':
		हाल '7':
		हाल '8':
		हाल '9':
			fl_speed = 1;
			speed = speed * 10 + c - '0';
			अवरोध;
		हाल 'C':
		हाल 'c':
			rndis_संकेत_connect(p);
			अवरोध;
		हाल 'D':
		हाल 'd':
			rndis_संकेत_disconnect(p);
			अवरोध;
		शेष:
			अगर (fl_speed) p->speed = speed;
			अन्यथा pr_debug("%c is not valid\n", c);
			अवरोध;
		पूर्ण

		buffer++;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक rndis_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, rndis_proc_show, PDE_DATA(inode));
पूर्ण

अटल स्थिर काष्ठा proc_ops rndis_proc_ops = अणु
	.proc_खोलो	= rndis_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= rndis_proc_ग_लिखो,
पूर्ण;

#घोषणा	NAME_TEMPLATE "driver/rndis-%03d"

#पूर्ण_अगर /* CONFIG_USB_GADGET_DEBUG_खाताS */
