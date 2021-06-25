<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_ncm.c -- USB CDC Network (NCM) link function driver
 *
 * Copyright (C) 2010 Nokia Corporation
 * Contact: Yauheni Kaliuta <yauheni.kaliuta@nokia.com>
 *
 * The driver borrows from f_ecm.c which is:
 *
 * Copyright (C) 2003-2005,2008 David Brownell
 * Copyright (C) 2008 Nokia Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/crc32.h>

#समावेश <linux/usb/cdc.h>

#समावेश "u_ether.h"
#समावेश "u_ether_configfs.h"
#समावेश "u_ncm.h"
#समावेश "configfs.h"

/*
 * This function is a "CDC Network Control Model" (CDC NCM) Ethernet link.
 * NCM is पूर्णांकended to be used with high-speed network attachments.
 *
 * Note that NCM requires the use of "alternate settings" क्रम its data
 * पूर्णांकerface.  This means that the set_alt() method has real work to करो,
 * and also means that a get_alt() method is required.
 */

/* to trigger crc/non-crc ndp signature */

#घोषणा NCM_NDP_HDR_CRC		0x01000000

क्रमागत ncm_notअगरy_state अणु
	NCM_NOTIFY_NONE,		/* करोn't notअगरy */
	NCM_NOTIFY_CONNECT,		/* issue CONNECT next */
	NCM_NOTIFY_SPEED,		/* issue SPEED_CHANGE next */
पूर्ण;

काष्ठा f_ncm अणु
	काष्ठा gether			port;
	u8				ctrl_id, data_id;

	अक्षर				ethaddr[14];

	काष्ठा usb_ep			*notअगरy;
	काष्ठा usb_request		*notअगरy_req;
	u8				notअगरy_state;
	atomic_t			notअगरy_count;
	bool				is_खोलो;

	स्थिर काष्ठा ndp_parser_opts	*parser_opts;
	bool				is_crc;
	u32				ndp_sign;

	/*
	 * क्रम notअगरication, it is accessed from both
	 * callback and ethernet खोलो/बंद
	 */
	spinlock_t			lock;

	काष्ठा net_device		*netdev;

	/* For multi-frame NDP TX */
	काष्ठा sk_buff			*skb_tx_data;
	काष्ठा sk_buff			*skb_tx_ndp;
	u16				ndp_dgram_count;
	bool				समयr_क्रमce_tx;
	काष्ठा hrसमयr			task_समयr;
	bool				समयr_stopping;
पूर्ण;

अटल अंतरभूत काष्ठा f_ncm *func_to_ncm(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_ncm, port.func);
पूर्ण

/* peak (theoretical) bulk transfer rate in bits-per-second */
अटल अंतरभूत अचिन्हित ncm_bitrate(काष्ठा usb_gadget *g)
अणु
	अगर (gadget_is_superspeed(g) && g->speed >= USB_SPEED_SUPER_PLUS)
		वापस 4250000000U;
	अन्यथा अगर (gadget_is_superspeed(g) && g->speed == USB_SPEED_SUPER)
		वापस 3750000000U;
	अन्यथा अगर (gadget_is_dualspeed(g) && g->speed == USB_SPEED_HIGH)
		वापस 13 * 512 * 8 * 1000 * 8;
	अन्यथा
		वापस 19 *  64 * 1 * 1000 * 8;
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * We cannot group frames so use just the minimal size which ok to put
 * one max-size ethernet frame.
 * If the host can group frames, allow it to करो that, 16K is selected,
 * because it's used by शेष by the current linux host driver
 */
#घोषणा NTB_DEFAULT_IN_SIZE	16384
#घोषणा NTB_OUT_SIZE		16384

/* Allocation क्रम storing the NDP, 32 should suffice क्रम a
 * 16k packet. This allows a maximum of 32 * 507 Byte packets to
 * be transmitted in a single 16kB skb, though when sending full size
 * packets this limit will be plenty.
 * Smaller packets are not likely to be trying to maximize the
 * throughput and will be mstly sending smaller infrequent frames.
 */
#घोषणा TX_MAX_NUM_DPE		32

/* Delay क्रम the transmit to रुको beक्रमe sending an unfilled NTB frame. */
#घोषणा TX_TIMEOUT_NSECS	300000

#घोषणा FORMATS_SUPPORTED	(USB_CDC_NCM_NTB16_SUPPORTED |	\
				 USB_CDC_NCM_NTB32_SUPPORTED)

अटल काष्ठा usb_cdc_ncm_ntb_parameters ntb_parameters = अणु
	.wLength = cpu_to_le16(माप(ntb_parameters)),
	.bmNtbFormatsSupported = cpu_to_le16(FORMATS_SUPPORTED),
	.dwNtbInMaxSize = cpu_to_le32(NTB_DEFAULT_IN_SIZE),
	.wNdpInDivisor = cpu_to_le16(4),
	.wNdpInPayloadReमुख्यder = cpu_to_le16(0),
	.wNdpInAlignment = cpu_to_le16(4),

	.dwNtbOutMaxSize = cpu_to_le32(NTB_OUT_SIZE),
	.wNdpOutDivisor = cpu_to_le16(4),
	.wNdpOutPayloadReमुख्यder = cpu_to_le16(0),
	.wNdpOutAlignment = cpu_to_le16(4),
पूर्ण;

/*
 * Use wMaxPacketSize big enough to fit CDC_NOTIFY_SPEED_CHANGE in one
 * packet, to simplअगरy cancellation; and a big transfer पूर्णांकerval, to
 * waste less bandwidth.
 */

#घोषणा NCM_STATUS_INTERVAL_MS		32
#घोषणा NCM_STATUS_BYTECOUNT		16	/* 8 byte header + data */

अटल काष्ठा usb_पूर्णांकerface_assoc_descriptor ncm_iad_desc = अणु
	.bLength =		माप ncm_iad_desc,
	.bDescriptorType =	USB_DT_INTERFACE_ASSOCIATION,

	/* .bFirstInterface =	DYNAMIC, */
	.bInterfaceCount =	2,	/* control + data */
	.bFunctionClass =	USB_CLASS_COMM,
	.bFunctionSubClass =	USB_CDC_SUBCLASS_NCM,
	.bFunctionProtocol =	USB_CDC_PROTO_NONE,
	/* .iFunction =		DYNAMIC */
पूर्ण;

/* पूर्णांकerface descriptor: */

अटल काष्ठा usb_पूर्णांकerface_descriptor ncm_control_पूर्णांकf = अणु
	.bLength =		माप ncm_control_पूर्णांकf,
	.bDescriptorType =	USB_DT_INTERFACE,

	/* .bInterfaceNumber = DYNAMIC */
	.bNumEndpoपूर्णांकs =	1,
	.bInterfaceClass =	USB_CLASS_COMM,
	.bInterfaceSubClass =	USB_CDC_SUBCLASS_NCM,
	.bInterfaceProtocol =	USB_CDC_PROTO_NONE,
	/* .iInterface = DYNAMIC */
पूर्ण;

अटल काष्ठा usb_cdc_header_desc ncm_header_desc = अणु
	.bLength =		माप ncm_header_desc,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_HEADER_TYPE,

	.bcdCDC =		cpu_to_le16(0x0110),
पूर्ण;

अटल काष्ठा usb_cdc_जोड़_desc ncm_जोड़_desc = अणु
	.bLength =		माप(ncm_जोड़_desc),
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_UNION_TYPE,
	/* .bMasterInterface0 =	DYNAMIC */
	/* .bSlaveInterface0 =	DYNAMIC */
पूर्ण;

अटल काष्ठा usb_cdc_ether_desc ecm_desc = अणु
	.bLength =		माप ecm_desc,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_ETHERNET_TYPE,

	/* this descriptor actually adds value, surprise! */
	/* .iMACAddress = DYNAMIC */
	.bmEthernetStatistics =	cpu_to_le32(0), /* no statistics */
	.wMaxSegmentSize =	cpu_to_le16(ETH_FRAME_LEN),
	.wNumberMCFilters =	cpu_to_le16(0),
	.bNumberPowerFilters =	0,
पूर्ण;

#घोषणा NCAPS	(USB_CDC_NCM_NCAP_ETH_FILTER | USB_CDC_NCM_NCAP_CRC_MODE)

अटल काष्ठा usb_cdc_ncm_desc ncm_desc = अणु
	.bLength =		माप ncm_desc,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_NCM_TYPE,

	.bcdNcmVersion =	cpu_to_le16(0x0100),
	/* can process SetEthernetPacketFilter */
	.bmNetworkCapabilities = NCAPS,
पूर्ण;

/* the शेष data पूर्णांकerface has no endpoपूर्णांकs ... */

अटल काष्ठा usb_पूर्णांकerface_descriptor ncm_data_nop_पूर्णांकf = अणु
	.bLength =		माप ncm_data_nop_पूर्णांकf,
	.bDescriptorType =	USB_DT_INTERFACE,

	.bInterfaceNumber =	1,
	.bAlternateSetting =	0,
	.bNumEndpoपूर्णांकs =	0,
	.bInterfaceClass =	USB_CLASS_CDC_DATA,
	.bInterfaceSubClass =	0,
	.bInterfaceProtocol =	USB_CDC_NCM_PROTO_NTB,
	/* .iInterface = DYNAMIC */
पूर्ण;

/* ... but the "real" data पूर्णांकerface has two bulk endpoपूर्णांकs */

अटल काष्ठा usb_पूर्णांकerface_descriptor ncm_data_पूर्णांकf = अणु
	.bLength =		माप ncm_data_पूर्णांकf,
	.bDescriptorType =	USB_DT_INTERFACE,

	.bInterfaceNumber =	1,
	.bAlternateSetting =	1,
	.bNumEndpoपूर्णांकs =	2,
	.bInterfaceClass =	USB_CLASS_CDC_DATA,
	.bInterfaceSubClass =	0,
	.bInterfaceProtocol =	USB_CDC_NCM_PROTO_NTB,
	/* .iInterface = DYNAMIC */
पूर्ण;

/* full speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_ncm_notअगरy_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize =	cpu_to_le16(NCM_STATUS_BYTECOUNT),
	.bInterval =		NCM_STATUS_INTERVAL_MS,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_ncm_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_ncm_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_descriptor_header *ncm_fs_function[] = अणु
	(काष्ठा usb_descriptor_header *) &ncm_iad_desc,
	/* CDC NCM control descriptors */
	(काष्ठा usb_descriptor_header *) &ncm_control_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ncm_header_desc,
	(काष्ठा usb_descriptor_header *) &ncm_जोड़_desc,
	(काष्ठा usb_descriptor_header *) &ecm_desc,
	(काष्ठा usb_descriptor_header *) &ncm_desc,
	(काष्ठा usb_descriptor_header *) &fs_ncm_notअगरy_desc,
	/* data पूर्णांकerface, altsettings 0 and 1 */
	(काष्ठा usb_descriptor_header *) &ncm_data_nop_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ncm_data_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &fs_ncm_in_desc,
	(काष्ठा usb_descriptor_header *) &fs_ncm_out_desc,
	शून्य,
पूर्ण;

/* high speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_ncm_notअगरy_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize =	cpu_to_le16(NCM_STATUS_BYTECOUNT),
	.bInterval =		USB_MS_TO_HS_INTERVAL(NCM_STATUS_INTERVAL_MS),
पूर्ण;
अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_ncm_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_ncm_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_descriptor_header *ncm_hs_function[] = अणु
	(काष्ठा usb_descriptor_header *) &ncm_iad_desc,
	/* CDC NCM control descriptors */
	(काष्ठा usb_descriptor_header *) &ncm_control_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ncm_header_desc,
	(काष्ठा usb_descriptor_header *) &ncm_जोड़_desc,
	(काष्ठा usb_descriptor_header *) &ecm_desc,
	(काष्ठा usb_descriptor_header *) &ncm_desc,
	(काष्ठा usb_descriptor_header *) &hs_ncm_notअगरy_desc,
	/* data पूर्णांकerface, altsettings 0 and 1 */
	(काष्ठा usb_descriptor_header *) &ncm_data_nop_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ncm_data_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &hs_ncm_in_desc,
	(काष्ठा usb_descriptor_header *) &hs_ncm_out_desc,
	शून्य,
पूर्ण;


/* super speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_ncm_notअगरy_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize =	cpu_to_le16(NCM_STATUS_BYTECOUNT),
	.bInterval =		USB_MS_TO_HS_INTERVAL(NCM_STATUS_INTERVAL_MS)
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_ncm_notअगरy_comp_desc = अणु
	.bLength =		माप(ss_ncm_notअगरy_comp_desc),
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,

	/* the following 3 values can be tweaked अगर necessary */
	/* .bMaxBurst =		0, */
	/* .bmAttributes =	0, */
	.wBytesPerInterval =	cpu_to_le16(NCM_STATUS_BYTECOUNT),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_ncm_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_ncm_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_ncm_bulk_comp_desc = अणु
	.bLength =		माप(ss_ncm_bulk_comp_desc),
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,

	/* the following 2 values can be tweaked अगर necessary */
	.bMaxBurst =		15,
	/* .bmAttributes =	0, */
पूर्ण;

अटल काष्ठा usb_descriptor_header *ncm_ss_function[] = अणु
	(काष्ठा usb_descriptor_header *) &ncm_iad_desc,
	/* CDC NCM control descriptors */
	(काष्ठा usb_descriptor_header *) &ncm_control_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ncm_header_desc,
	(काष्ठा usb_descriptor_header *) &ncm_जोड़_desc,
	(काष्ठा usb_descriptor_header *) &ecm_desc,
	(काष्ठा usb_descriptor_header *) &ncm_desc,
	(काष्ठा usb_descriptor_header *) &ss_ncm_notअगरy_desc,
	(काष्ठा usb_descriptor_header *) &ss_ncm_notअगरy_comp_desc,
	/* data पूर्णांकerface, altsettings 0 and 1 */
	(काष्ठा usb_descriptor_header *) &ncm_data_nop_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ncm_data_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ss_ncm_in_desc,
	(काष्ठा usb_descriptor_header *) &ss_ncm_bulk_comp_desc,
	(काष्ठा usb_descriptor_header *) &ss_ncm_out_desc,
	(काष्ठा usb_descriptor_header *) &ss_ncm_bulk_comp_desc,
	शून्य,
पूर्ण;

/* string descriptors: */

#घोषणा STRING_CTRL_IDX	0
#घोषणा STRING_MAC_IDX	1
#घोषणा STRING_DATA_IDX	2
#घोषणा STRING_IAD_IDX	3

अटल काष्ठा usb_string ncm_string_defs[] = अणु
	[STRING_CTRL_IDX].s = "CDC Network Control Model (NCM)",
	[STRING_MAC_IDX].s = "",
	[STRING_DATA_IDX].s = "CDC Network Data",
	[STRING_IAD_IDX].s = "CDC NCM",
	अणु  पूर्ण /* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings ncm_string_table = अणु
	.language =		0x0409,	/* en-us */
	.strings =		ncm_string_defs,
पूर्ण;

अटल काष्ठा usb_gadget_strings *ncm_strings[] = अणु
	&ncm_string_table,
	शून्य,
पूर्ण;

/*
 * Here are options क्रम NCM Datagram Poपूर्णांकer table (NDP) parser.
 * There are 2 dअगरferent क्रमmats: NDP16 and NDP32 in the spec (ch. 3),
 * in NDP16 offsets and sizes fields are 1 16bit word wide,
 * in NDP32 -- 2 16bit words wide. Also signatures are dअगरferent.
 * To make the parser code the same, put the dअगरferences in the काष्ठाure,
 * and चयन poपूर्णांकers to the काष्ठाures when the क्रमmat is changed.
 */

काष्ठा ndp_parser_opts अणु
	u32		nth_sign;
	u32		ndp_sign;
	अचिन्हित	nth_size;
	अचिन्हित	ndp_size;
	अचिन्हित	dpe_size;
	अचिन्हित	ndplen_align;
	/* sizes in u16 units */
	अचिन्हित	dgram_item_len; /* index or length */
	अचिन्हित	block_length;
	अचिन्हित	ndp_index;
	अचिन्हित	reserved1;
	अचिन्हित	reserved2;
	अचिन्हित	next_ndp_index;
पूर्ण;

#घोषणा INIT_NDP16_OPTS अणु					\
		.nth_sign = USB_CDC_NCM_NTH16_SIGN,		\
		.ndp_sign = USB_CDC_NCM_NDP16_NOCRC_SIGN,	\
		.nth_size = माप(काष्ठा usb_cdc_ncm_nth16),	\
		.ndp_size = माप(काष्ठा usb_cdc_ncm_ndp16),	\
		.dpe_size = माप(काष्ठा usb_cdc_ncm_dpe16),	\
		.ndplen_align = 4,				\
		.dgram_item_len = 1,				\
		.block_length = 1,				\
		.ndp_index = 1,					\
		.reserved1 = 0,					\
		.reserved2 = 0,					\
		.next_ndp_index = 1,				\
	पूर्ण


#घोषणा INIT_NDP32_OPTS अणु					\
		.nth_sign = USB_CDC_NCM_NTH32_SIGN,		\
		.ndp_sign = USB_CDC_NCM_NDP32_NOCRC_SIGN,	\
		.nth_size = माप(काष्ठा usb_cdc_ncm_nth32),	\
		.ndp_size = माप(काष्ठा usb_cdc_ncm_ndp32),	\
		.dpe_size = माप(काष्ठा usb_cdc_ncm_dpe32),	\
		.ndplen_align = 8,				\
		.dgram_item_len = 2,				\
		.block_length = 2,				\
		.ndp_index = 2,					\
		.reserved1 = 1,					\
		.reserved2 = 2,					\
		.next_ndp_index = 2,				\
	पूर्ण

अटल स्थिर काष्ठा ndp_parser_opts ndp16_opts = INIT_NDP16_OPTS;
अटल स्थिर काष्ठा ndp_parser_opts ndp32_opts = INIT_NDP32_OPTS;

अटल अंतरभूत व्योम put_ncm(__le16 **p, अचिन्हित size, अचिन्हित val)
अणु
	चयन (size) अणु
	हाल 1:
		put_unaligned_le16((u16)val, *p);
		अवरोध;
	हाल 2:
		put_unaligned_le32((u32)val, *p);

		अवरोध;
	शेष:
		BUG();
	पूर्ण

	*p += size;
पूर्ण

अटल अंतरभूत अचिन्हित get_ncm(__le16 **p, अचिन्हित size)
अणु
	अचिन्हित पंचांगp;

	चयन (size) अणु
	हाल 1:
		पंचांगp = get_unaligned_le16(*p);
		अवरोध;
	हाल 2:
		पंचांगp = get_unaligned_le32(*p);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	*p += size;
	वापस पंचांगp;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल अंतरभूत व्योम ncm_reset_values(काष्ठा f_ncm *ncm)
अणु
	ncm->parser_opts = &ndp16_opts;
	ncm->is_crc = false;
	ncm->ndp_sign = ncm->parser_opts->ndp_sign;
	ncm->port.cdc_filter = DEFAULT_FILTER;

	/* करोesn't make sense क्रम ncm, fixed size used */
	ncm->port.header_len = 0;

	ncm->port.fixed_out_len = le32_to_cpu(ntb_parameters.dwNtbOutMaxSize);
	ncm->port.fixed_in_len = NTB_DEFAULT_IN_SIZE;
पूर्ण

/*
 * Context: ncm->lock held
 */
अटल व्योम ncm_करो_notअगरy(काष्ठा f_ncm *ncm)
अणु
	काष्ठा usb_request		*req = ncm->notअगरy_req;
	काष्ठा usb_cdc_notअगरication	*event;
	काष्ठा usb_composite_dev	*cdev = ncm->port.func.config->cdev;
	__le32				*data;
	पूर्णांक				status;

	/* notअगरication alपढ़ोy in flight? */
	अगर (atomic_पढ़ो(&ncm->notअगरy_count))
		वापस;

	event = req->buf;
	चयन (ncm->notअगरy_state) अणु
	हाल NCM_NOTIFY_NONE:
		वापस;

	हाल NCM_NOTIFY_CONNECT:
		event->bNotअगरicationType = USB_CDC_NOTIFY_NETWORK_CONNECTION;
		अगर (ncm->is_खोलो)
			event->wValue = cpu_to_le16(1);
		अन्यथा
			event->wValue = cpu_to_le16(0);
		event->wLength = 0;
		req->length = माप *event;

		DBG(cdev, "notify connect %s\n",
				ncm->is_खोलो ? "true" : "false");
		ncm->notअगरy_state = NCM_NOTIFY_NONE;
		अवरोध;

	हाल NCM_NOTIFY_SPEED:
		event->bNotअगरicationType = USB_CDC_NOTIFY_SPEED_CHANGE;
		event->wValue = cpu_to_le16(0);
		event->wLength = cpu_to_le16(8);
		req->length = NCM_STATUS_BYTECOUNT;

		/* SPEED_CHANGE data is up/करोwn speeds in bits/sec */
		data = req->buf + माप *event;
		data[0] = cpu_to_le32(ncm_bitrate(cdev->gadget));
		data[1] = data[0];

		DBG(cdev, "notify speed %u\n", ncm_bitrate(cdev->gadget));
		ncm->notअगरy_state = NCM_NOTIFY_CONNECT;
		अवरोध;
	पूर्ण
	event->bmRequestType = 0xA1;
	event->wIndex = cpu_to_le16(ncm->ctrl_id);

	atomic_inc(&ncm->notअगरy_count);

	/*
	 * In द्विगुन buffering अगर there is a space in FIFO,
	 * completion callback can be called right after the call,
	 * so unlocking
	 */
	spin_unlock(&ncm->lock);
	status = usb_ep_queue(ncm->notअगरy, req, GFP_ATOMIC);
	spin_lock(&ncm->lock);
	अगर (status < 0) अणु
		atomic_dec(&ncm->notअगरy_count);
		DBG(cdev, "notify --> %d\n", status);
	पूर्ण
पूर्ण

/*
 * Context: ncm->lock held
 */
अटल व्योम ncm_notअगरy(काष्ठा f_ncm *ncm)
अणु
	/*
	 * NOTE on most versions of Linux, host side cdc-ethernet
	 * won't listen क्रम notअगरications until its netdevice खोलोs.
	 * The first notअगरication then sits in the FIFO क्रम a दीर्घ
	 * समय, and the second one is queued.
	 *
	 * If ncm_notअगरy() is called beक्रमe the second (CONNECT)
	 * notअगरication is sent, then it will reset to send the SPEED
	 * notअगरicaion again (and again, and again), but it's not a problem
	 */
	ncm->notअगरy_state = NCM_NOTIFY_SPEED;
	ncm_करो_notअगरy(ncm);
पूर्ण

अटल व्योम ncm_notअगरy_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_ncm			*ncm = req->context;
	काष्ठा usb_composite_dev	*cdev = ncm->port.func.config->cdev;
	काष्ठा usb_cdc_notअगरication	*event = req->buf;

	spin_lock(&ncm->lock);
	चयन (req->status) अणु
	हाल 0:
		VDBG(cdev, "Notification %02x sent\n",
		     event->bNotअगरicationType);
		atomic_dec(&ncm->notअगरy_count);
		अवरोध;
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		atomic_set(&ncm->notअगरy_count, 0);
		ncm->notअगरy_state = NCM_NOTIFY_NONE;
		अवरोध;
	शेष:
		DBG(cdev, "event %02x --> %d\n",
			event->bNotअगरicationType, req->status);
		atomic_dec(&ncm->notअगरy_count);
		अवरोध;
	पूर्ण
	ncm_करो_notअगरy(ncm);
	spin_unlock(&ncm->lock);
पूर्ण

अटल व्योम ncm_ep0out_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	/* now क्रम SET_NTB_INPUT_SIZE only */
	अचिन्हित		in_size;
	काष्ठा usb_function	*f = req->context;
	काष्ठा f_ncm		*ncm = func_to_ncm(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	req->context = शून्य;
	अगर (req->status || req->actual != req->length) अणु
		DBG(cdev, "Bad control-OUT transfer\n");
		जाओ invalid;
	पूर्ण

	in_size = get_unaligned_le32(req->buf);
	अगर (in_size < USB_CDC_NCM_NTB_MIN_IN_SIZE ||
	    in_size > le32_to_cpu(ntb_parameters.dwNtbInMaxSize)) अणु
		DBG(cdev, "Got wrong INPUT SIZE (%d) from host\n", in_size);
		जाओ invalid;
	पूर्ण

	ncm->port.fixed_in_len = in_size;
	VDBG(cdev, "Set NTB INPUT SIZE %d\n", in_size);
	वापस;

invalid:
	usb_ep_set_halt(ep);
	वापस;
पूर्ण

अटल पूर्णांक ncm_setup(काष्ठा usb_function *f, स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा f_ncm		*ncm = func_to_ncm(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा usb_request	*req = cdev->req;
	पूर्णांक			value = -EOPNOTSUPP;
	u16			w_index = le16_to_cpu(ctrl->wIndex);
	u16			w_value = le16_to_cpu(ctrl->wValue);
	u16			w_length = le16_to_cpu(ctrl->wLength);

	/*
	 * composite driver infraकाष्ठाure handles everything except
	 * CDC class messages; पूर्णांकerface activation uses set_alt().
	 */
	चयन ((ctrl->bRequestType << 8) | ctrl->bRequest) अणु
	हाल ((USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
			| USB_CDC_SET_ETHERNET_PACKET_FILTER:
		/*
		 * see 6.2.30: no data, wIndex = पूर्णांकerface,
		 * wValue = packet filter biपंचांगap
		 */
		अगर (w_length != 0 || w_index != ncm->ctrl_id)
			जाओ invalid;
		DBG(cdev, "packet filter %02x\n", w_value);
		/*
		 * REVISIT locking of cdc_filter.  This assumes the UDC
		 * driver won't have a concurrent packet TX irq running on
		 * another CPU; or that अगर it करोes, this ग_लिखो is atomic...
		 */
		ncm->port.cdc_filter = w_value;
		value = 0;
		अवरोध;
	/*
	 * and optionally:
	 * हाल USB_CDC_SEND_ENCAPSULATED_COMMAND:
	 * हाल USB_CDC_GET_ENCAPSULATED_RESPONSE:
	 * हाल USB_CDC_SET_ETHERNET_MULTICAST_FILTERS:
	 * हाल USB_CDC_SET_ETHERNET_PM_PATTERN_FILTER:
	 * हाल USB_CDC_GET_ETHERNET_PM_PATTERN_FILTER:
	 * हाल USB_CDC_GET_ETHERNET_STATISTIC:
	 */

	हाल ((USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
		| USB_CDC_GET_NTB_PARAMETERS:

		अगर (w_length == 0 || w_value != 0 || w_index != ncm->ctrl_id)
			जाओ invalid;
		value = w_length > माप ntb_parameters ?
			माप ntb_parameters : w_length;
		स_नकल(req->buf, &ntb_parameters, value);
		VDBG(cdev, "Host asked NTB parameters\n");
		अवरोध;

	हाल ((USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
		| USB_CDC_GET_NTB_INPUT_SIZE:

		अगर (w_length < 4 || w_value != 0 || w_index != ncm->ctrl_id)
			जाओ invalid;
		put_unaligned_le32(ncm->port.fixed_in_len, req->buf);
		value = 4;
		VDBG(cdev, "Host asked INPUT SIZE, sending %d\n",
		     ncm->port.fixed_in_len);
		अवरोध;

	हाल ((USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
		| USB_CDC_SET_NTB_INPUT_SIZE:
	अणु
		अगर (w_length != 4 || w_value != 0 || w_index != ncm->ctrl_id)
			जाओ invalid;
		req->complete = ncm_ep0out_complete;
		req->length = w_length;
		req->context = f;

		value = req->length;
		अवरोध;
	पूर्ण

	हाल ((USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
		| USB_CDC_GET_NTB_FORMAT:
	अणु
		uपूर्णांक16_t क्रमmat;

		अगर (w_length < 2 || w_value != 0 || w_index != ncm->ctrl_id)
			जाओ invalid;
		क्रमmat = (ncm->parser_opts == &ndp16_opts) ? 0x0000 : 0x0001;
		put_unaligned_le16(क्रमmat, req->buf);
		value = 2;
		VDBG(cdev, "Host asked NTB FORMAT, sending %d\n", क्रमmat);
		अवरोध;
	पूर्ण

	हाल ((USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
		| USB_CDC_SET_NTB_FORMAT:
	अणु
		अगर (w_length != 0 || w_index != ncm->ctrl_id)
			जाओ invalid;
		चयन (w_value) अणु
		हाल 0x0000:
			ncm->parser_opts = &ndp16_opts;
			DBG(cdev, "NCM16 selected\n");
			अवरोध;
		हाल 0x0001:
			ncm->parser_opts = &ndp32_opts;
			DBG(cdev, "NCM32 selected\n");
			अवरोध;
		शेष:
			जाओ invalid;
		पूर्ण
		value = 0;
		अवरोध;
	पूर्ण
	हाल ((USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
		| USB_CDC_GET_CRC_MODE:
	अणु
		uपूर्णांक16_t is_crc;

		अगर (w_length < 2 || w_value != 0 || w_index != ncm->ctrl_id)
			जाओ invalid;
		is_crc = ncm->is_crc ? 0x0001 : 0x0000;
		put_unaligned_le16(is_crc, req->buf);
		value = 2;
		VDBG(cdev, "Host asked CRC MODE, sending %d\n", is_crc);
		अवरोध;
	पूर्ण

	हाल ((USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
		| USB_CDC_SET_CRC_MODE:
	अणु
		अगर (w_length != 0 || w_index != ncm->ctrl_id)
			जाओ invalid;
		चयन (w_value) अणु
		हाल 0x0000:
			ncm->is_crc = false;
			DBG(cdev, "non-CRC mode selected\n");
			अवरोध;
		हाल 0x0001:
			ncm->is_crc = true;
			DBG(cdev, "CRC mode selected\n");
			अवरोध;
		शेष:
			जाओ invalid;
		पूर्ण
		value = 0;
		अवरोध;
	पूर्ण

	/* and disabled in ncm descriptor: */
	/* हाल USB_CDC_GET_NET_ADDRESS: */
	/* हाल USB_CDC_SET_NET_ADDRESS: */
	/* हाल USB_CDC_GET_MAX_DATAGRAM_SIZE: */
	/* हाल USB_CDC_SET_MAX_DATAGRAM_SIZE: */

	शेष:
invalid:
		DBG(cdev, "invalid control req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
	पूर्ण
	ncm->ndp_sign = ncm->parser_opts->ndp_sign |
		(ncm->is_crc ? NCM_NDP_HDR_CRC : 0);

	/* respond with data transfer or status phase? */
	अगर (value >= 0) अणु
		DBG(cdev, "ncm req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
		req->zero = 0;
		req->length = value;
		value = usb_ep_queue(cdev->gadget->ep0, req, GFP_ATOMIC);
		अगर (value < 0)
			ERROR(cdev, "ncm req %02x.%02x response err %d\n",
					ctrl->bRequestType, ctrl->bRequest,
					value);
	पूर्ण

	/* device either stalls (value < 0) or reports success */
	वापस value;
पूर्ण


अटल पूर्णांक ncm_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा f_ncm		*ncm = func_to_ncm(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	/* Control पूर्णांकerface has only altsetting 0 */
	अगर (पूर्णांकf == ncm->ctrl_id) अणु
		अगर (alt != 0)
			जाओ fail;

		DBG(cdev, "reset ncm control %d\n", पूर्णांकf);
		usb_ep_disable(ncm->notअगरy);

		अगर (!(ncm->notअगरy->desc)) अणु
			DBG(cdev, "init ncm ctrl %d\n", पूर्णांकf);
			अगर (config_ep_by_speed(cdev->gadget, f, ncm->notअगरy))
				जाओ fail;
		पूर्ण
		usb_ep_enable(ncm->notअगरy);

	/* Data पूर्णांकerface has two altsettings, 0 and 1 */
	पूर्ण अन्यथा अगर (पूर्णांकf == ncm->data_id) अणु
		अगर (alt > 1)
			जाओ fail;

		अगर (ncm->port.in_ep->enabled) अणु
			DBG(cdev, "reset ncm\n");
			ncm->समयr_stopping = true;
			ncm->netdev = शून्य;
			gether_disconnect(&ncm->port);
			ncm_reset_values(ncm);
		पूर्ण

		/*
		 * CDC Network only sends data in non-शेष altsettings.
		 * Changing altsettings resets filters, statistics, etc.
		 */
		अगर (alt == 1) अणु
			काष्ठा net_device	*net;

			अगर (!ncm->port.in_ep->desc ||
			    !ncm->port.out_ep->desc) अणु
				DBG(cdev, "init ncm\n");
				अगर (config_ep_by_speed(cdev->gadget, f,
						       ncm->port.in_ep) ||
				    config_ep_by_speed(cdev->gadget, f,
						       ncm->port.out_ep)) अणु
					ncm->port.in_ep->desc = शून्य;
					ncm->port.out_ep->desc = शून्य;
					जाओ fail;
				पूर्ण
			पूर्ण

			/* TODO */
			/* Enable zlps by शेष क्रम NCM conक्रमmance;
			 * override क्रम musb_hdrc (aव्योमs txdma ovhead)
			 */
			ncm->port.is_zlp_ok =
				gadget_is_zlp_supported(cdev->gadget);
			ncm->port.cdc_filter = DEFAULT_FILTER;
			DBG(cdev, "activate ncm\n");
			net = gether_connect(&ncm->port);
			अगर (IS_ERR(net))
				वापस PTR_ERR(net);
			ncm->netdev = net;
			ncm->समयr_stopping = false;
		पूर्ण

		spin_lock(&ncm->lock);
		ncm_notअगरy(ncm);
		spin_unlock(&ncm->lock);
	पूर्ण अन्यथा
		जाओ fail;

	वापस 0;
fail:
	वापस -EINVAL;
पूर्ण

/*
 * Because the data पूर्णांकerface supports multiple altsettings,
 * this NCM function *MUST* implement a get_alt() method.
 */
अटल पूर्णांक ncm_get_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf)
अणु
	काष्ठा f_ncm		*ncm = func_to_ncm(f);

	अगर (पूर्णांकf == ncm->ctrl_id)
		वापस 0;
	वापस ncm->port.in_ep->enabled ? 1 : 0;
पूर्ण

अटल काष्ठा sk_buff *package_क्रम_tx(काष्ठा f_ncm *ncm)
अणु
	__le16		*ntb_iter;
	काष्ठा sk_buff	*skb2 = शून्य;
	अचिन्हित	ndp_pad;
	अचिन्हित	ndp_index;
	अचिन्हित	new_len;

	स्थिर काष्ठा ndp_parser_opts *opts = ncm->parser_opts;
	स्थिर पूर्णांक ndp_align = le16_to_cpu(ntb_parameters.wNdpInAlignment);
	स्थिर पूर्णांक dgram_idx_len = 2 * 2 * opts->dgram_item_len;

	/* Stop the समयr */
	hrसमयr_try_to_cancel(&ncm->task_समयr);

	ndp_pad = ALIGN(ncm->skb_tx_data->len, ndp_align) -
			ncm->skb_tx_data->len;
	ndp_index = ncm->skb_tx_data->len + ndp_pad;
	new_len = ndp_index + dgram_idx_len + ncm->skb_tx_ndp->len;

	/* Set the final BlockLength and wNdpIndex */
	ntb_iter = (व्योम *) ncm->skb_tx_data->data;
	/* Increment poपूर्णांकer to BlockLength */
	ntb_iter += 2 + 1 + 1;
	put_ncm(&ntb_iter, opts->block_length, new_len);
	put_ncm(&ntb_iter, opts->ndp_index, ndp_index);

	/* Set the final NDP wLength */
	new_len = opts->ndp_size +
			(ncm->ndp_dgram_count * dgram_idx_len);
	ncm->ndp_dgram_count = 0;
	/* Increment from start to wLength */
	ntb_iter = (व्योम *) ncm->skb_tx_ndp->data;
	ntb_iter += 2;
	put_unaligned_le16(new_len, ntb_iter);

	/* Merge the skbs */
	swap(skb2, ncm->skb_tx_data);
	अगर (ncm->skb_tx_data) अणु
		dev_consume_skb_any(ncm->skb_tx_data);
		ncm->skb_tx_data = शून्य;
	पूर्ण

	/* Insert NDP alignment. */
	skb_put_zero(skb2, ndp_pad);

	/* Copy NTB across. */
	skb_put_data(skb2, ncm->skb_tx_ndp->data, ncm->skb_tx_ndp->len);
	dev_consume_skb_any(ncm->skb_tx_ndp);
	ncm->skb_tx_ndp = शून्य;

	/* Insert zero'd datagram. */
	skb_put_zero(skb2, dgram_idx_len);

	वापस skb2;
पूर्ण

अटल काष्ठा sk_buff *ncm_wrap_ntb(काष्ठा gether *port,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा f_ncm	*ncm = func_to_ncm(&port->func);
	काष्ठा sk_buff	*skb2 = शून्य;
	पूर्णांक		ncb_len = 0;
	__le16		*ntb_data;
	__le16		*ntb_ndp;
	पूर्णांक		dgram_pad;

	अचिन्हित	max_size = ncm->port.fixed_in_len;
	स्थिर काष्ठा ndp_parser_opts *opts = ncm->parser_opts;
	स्थिर पूर्णांक ndp_align = le16_to_cpu(ntb_parameters.wNdpInAlignment);
	स्थिर पूर्णांक भाग = le16_to_cpu(ntb_parameters.wNdpInDivisor);
	स्थिर पूर्णांक rem = le16_to_cpu(ntb_parameters.wNdpInPayloadReमुख्यder);
	स्थिर पूर्णांक dgram_idx_len = 2 * 2 * opts->dgram_item_len;

	अगर (!skb && !ncm->skb_tx_data)
		वापस शून्य;

	अगर (skb) अणु
		/* Add the CRC अगर required up front */
		अगर (ncm->is_crc) अणु
			uपूर्णांक32_t	crc;
			__le16		*crc_pos;

			crc = ~crc32_le(~0,
					skb->data,
					skb->len);
			crc_pos = skb_put(skb, माप(uपूर्णांक32_t));
			put_unaligned_le32(crc, crc_pos);
		पूर्ण

		/* If the new skb is too big क्रम the current NCM NTB then
		 * set the current stored skb to be sent now and clear it
		 * पढ़ोy क्रम new data.
		 * NOTE: Assume maximum align क्रम speed of calculation.
		 */
		अगर (ncm->skb_tx_data
		    && (ncm->ndp_dgram_count >= TX_MAX_NUM_DPE
		    || (ncm->skb_tx_data->len +
		    भाग + rem + skb->len +
		    ncm->skb_tx_ndp->len + ndp_align + (2 * dgram_idx_len))
		    > max_size)) अणु
			skb2 = package_क्रम_tx(ncm);
			अगर (!skb2)
				जाओ err;
		पूर्ण

		अगर (!ncm->skb_tx_data) अणु
			ncb_len = opts->nth_size;
			dgram_pad = ALIGN(ncb_len, भाग) + rem - ncb_len;
			ncb_len += dgram_pad;

			/* Create a new skb क्रम the NTH and datagrams. */
			ncm->skb_tx_data = alloc_skb(max_size, GFP_ATOMIC);
			अगर (!ncm->skb_tx_data)
				जाओ err;

			ncm->skb_tx_data->dev = ncm->netdev;
			ntb_data = skb_put_zero(ncm->skb_tx_data, ncb_len);
			/* dwSignature */
			put_unaligned_le32(opts->nth_sign, ntb_data);
			ntb_data += 2;
			/* wHeaderLength */
			put_unaligned_le16(opts->nth_size, ntb_data++);

			/* Allocate an skb क्रम storing the NDP,
			 * TX_MAX_NUM_DPE should easily suffice क्रम a
			 * 16k packet.
			 */
			ncm->skb_tx_ndp = alloc_skb((पूर्णांक)(opts->ndp_size
						    + opts->dpe_size
						    * TX_MAX_NUM_DPE),
						    GFP_ATOMIC);
			अगर (!ncm->skb_tx_ndp)
				जाओ err;

			ncm->skb_tx_ndp->dev = ncm->netdev;
			ntb_ndp = skb_put(ncm->skb_tx_ndp, opts->ndp_size);
			स_रखो(ntb_ndp, 0, ncb_len);
			/* dwSignature */
			put_unaligned_le32(ncm->ndp_sign, ntb_ndp);
			ntb_ndp += 2;

			/* There is always a zeroed entry */
			ncm->ndp_dgram_count = 1;

			/* Note: we skip opts->next_ndp_index */

			/* Start the समयr. */
			hrसमयr_start(&ncm->task_समयr, TX_TIMEOUT_NSECS,
				      HRTIMER_MODE_REL_SOFT);
		पूर्ण

		/* Add the datagram position entries */
		ntb_ndp = skb_put_zero(ncm->skb_tx_ndp, dgram_idx_len);

		ncb_len = ncm->skb_tx_data->len;
		dgram_pad = ALIGN(ncb_len, भाग) + rem - ncb_len;
		ncb_len += dgram_pad;

		/* (d)wDatagramIndex */
		put_ncm(&ntb_ndp, opts->dgram_item_len, ncb_len);
		/* (d)wDatagramLength */
		put_ncm(&ntb_ndp, opts->dgram_item_len, skb->len);
		ncm->ndp_dgram_count++;

		/* Add the new data to the skb */
		skb_put_zero(ncm->skb_tx_data, dgram_pad);
		skb_put_data(ncm->skb_tx_data, skb->data, skb->len);
		dev_consume_skb_any(skb);
		skb = शून्य;

	पूर्ण अन्यथा अगर (ncm->skb_tx_data && ncm->समयr_क्रमce_tx) अणु
		/* If the tx was requested because of a समयout then send */
		skb2 = package_क्रम_tx(ncm);
		अगर (!skb2)
			जाओ err;
	पूर्ण

	वापस skb2;

err:
	ncm->netdev->stats.tx_dropped++;

	अगर (skb)
		dev_kमुक्त_skb_any(skb);
	अगर (ncm->skb_tx_data)
		dev_kमुक्त_skb_any(ncm->skb_tx_data);
	अगर (ncm->skb_tx_ndp)
		dev_kमुक्त_skb_any(ncm->skb_tx_ndp);

	वापस शून्य;
पूर्ण

/*
 * The transmit should only be run अगर no skb data has been sent
 * क्रम a certain duration.
 */
अटल क्रमागत hrसमयr_restart ncm_tx_समयout(काष्ठा hrसमयr *data)
अणु
	काष्ठा f_ncm *ncm = container_of(data, काष्ठा f_ncm, task_समयr);

	/* Only send अगर data is available. */
	अगर (!ncm->समयr_stopping && ncm->skb_tx_data) अणु
		ncm->समयr_क्रमce_tx = true;

		/* XXX This allowance of a शून्य skb argument to nकरो_start_xmit
		 * XXX is not sane.  The gadget layer should be redeचिन्हित so
		 * XXX that the dev->wrap() invocations to build SKBs is transparent
		 * XXX and perक्रमmed in some way outside of the nकरो_start_xmit
		 * XXX पूर्णांकerface.
		 */
		ncm->netdev->netdev_ops->nकरो_start_xmit(शून्य, ncm->netdev);

		ncm->समयr_क्रमce_tx = false;
	पूर्ण
	वापस HRTIMER_NORESTART;
पूर्ण

अटल पूर्णांक ncm_unwrap_ntb(काष्ठा gether *port,
			  काष्ठा sk_buff *skb,
			  काष्ठा sk_buff_head *list)
अणु
	काष्ठा f_ncm	*ncm = func_to_ncm(&port->func);
	__le16		*पंचांगp = (व्योम *) skb->data;
	अचिन्हित	index, index2;
	पूर्णांक		ndp_index;
	अचिन्हित	dg_len, dg_len2;
	अचिन्हित	ndp_len;
	अचिन्हित	block_len;
	काष्ठा sk_buff	*skb2;
	पूर्णांक		ret = -EINVAL;
	अचिन्हित	ntb_max = le32_to_cpu(ntb_parameters.dwNtbOutMaxSize);
	अचिन्हित	frame_max = le16_to_cpu(ecm_desc.wMaxSegmentSize);
	स्थिर काष्ठा ndp_parser_opts *opts = ncm->parser_opts;
	अचिन्हित	crc_len = ncm->is_crc ? माप(uपूर्णांक32_t) : 0;
	पूर्णांक		dgram_counter;

	/* dwSignature */
	अगर (get_unaligned_le32(पंचांगp) != opts->nth_sign) अणु
		INFO(port->func.config->cdev, "Wrong NTH SIGN, skblen %d\n",
			skb->len);
		prपूर्णांक_hex_dump(KERN_INFO, "HEAD:", DUMP_PREFIX_ADDRESS, 32, 1,
			       skb->data, 32, false);

		जाओ err;
	पूर्ण
	पंचांगp += 2;
	/* wHeaderLength */
	अगर (get_unaligned_le16(पंचांगp++) != opts->nth_size) अणु
		INFO(port->func.config->cdev, "Wrong NTB headersize\n");
		जाओ err;
	पूर्ण
	पंचांगp++; /* skip wSequence */

	block_len = get_ncm(&पंचांगp, opts->block_length);
	/* (d)wBlockLength */
	अगर (block_len > ntb_max) अणु
		INFO(port->func.config->cdev, "OUT size exceeded\n");
		जाओ err;
	पूर्ण

	ndp_index = get_ncm(&पंचांगp, opts->ndp_index);

	/* Run through all the NDP's in the NTB */
	करो अणु
		/*
		 * NCM 3.2
		 * dwNdpIndex
		 */
		अगर (((ndp_index % 4) != 0) ||
				(ndp_index < opts->nth_size) ||
				(ndp_index > (block_len -
					      opts->ndp_size))) अणु
			INFO(port->func.config->cdev, "Bad index: %#X\n",
			     ndp_index);
			जाओ err;
		पूर्ण

		/*
		 * walk through NDP
		 * dwSignature
		 */
		पंचांगp = (व्योम *)(skb->data + ndp_index);
		अगर (get_unaligned_le32(पंचांगp) != ncm->ndp_sign) अणु
			INFO(port->func.config->cdev, "Wrong NDP SIGN\n");
			जाओ err;
		पूर्ण
		पंचांगp += 2;

		ndp_len = get_unaligned_le16(पंचांगp++);
		/*
		 * NCM 3.3.1
		 * wLength
		 * entry is 2 items
		 * item size is 16/32 bits, opts->dgram_item_len * 2 bytes
		 * minimal: काष्ठा usb_cdc_ncm_ndpX + normal entry + zero entry
		 * Each entry is a dgram index and a dgram length.
		 */
		अगर ((ndp_len < opts->ndp_size
				+ 2 * 2 * (opts->dgram_item_len * 2)) ||
				(ndp_len % opts->ndplen_align != 0)) अणु
			INFO(port->func.config->cdev, "Bad NDP length: %#X\n",
			     ndp_len);
			जाओ err;
		पूर्ण
		पंचांगp += opts->reserved1;
		/* Check क्रम another NDP (d)wNextNdpIndex */
		ndp_index = get_ncm(&पंचांगp, opts->next_ndp_index);
		पंचांगp += opts->reserved2;

		ndp_len -= opts->ndp_size;
		index2 = get_ncm(&पंचांगp, opts->dgram_item_len);
		dg_len2 = get_ncm(&पंचांगp, opts->dgram_item_len);
		dgram_counter = 0;

		करो अणु
			index = index2;
			/* wDatagramIndex[0] */
			अगर ((index < opts->nth_size) ||
					(index > block_len - opts->dpe_size)) अणु
				INFO(port->func.config->cdev,
				     "Bad index: %#X\n", index);
				जाओ err;
			पूर्ण

			dg_len = dg_len2;
			/*
			 * wDatagramLength[0]
			 * ethernet hdr + crc or larger than max frame size
			 */
			अगर ((dg_len < 14 + crc_len) ||
					(dg_len > frame_max)) अणु
				INFO(port->func.config->cdev,
				     "Bad dgram length: %#X\n", dg_len);
				जाओ err;
			पूर्ण
			अगर (ncm->is_crc) अणु
				uपूर्णांक32_t crc, crc2;

				crc = get_unaligned_le32(skb->data +
							 index + dg_len -
							 crc_len);
				crc2 = ~crc32_le(~0,
						 skb->data + index,
						 dg_len - crc_len);
				अगर (crc != crc2) अणु
					INFO(port->func.config->cdev,
					     "Bad CRC\n");
					जाओ err;
				पूर्ण
			पूर्ण

			index2 = get_ncm(&पंचांगp, opts->dgram_item_len);
			dg_len2 = get_ncm(&पंचांगp, opts->dgram_item_len);

			/* wDatagramIndex[1] */
			अगर (index2 > block_len - opts->dpe_size) अणु
				INFO(port->func.config->cdev,
				     "Bad index: %#X\n", index2);
				जाओ err;
			पूर्ण

			/*
			 * Copy the data पूर्णांकo a new skb.
			 * This ensures the truesize is correct
			 */
			skb2 = netdev_alloc_skb_ip_align(ncm->netdev,
							 dg_len - crc_len);
			अगर (skb2 == शून्य)
				जाओ err;
			skb_put_data(skb2, skb->data + index,
				     dg_len - crc_len);

			skb_queue_tail(list, skb2);

			ndp_len -= 2 * (opts->dgram_item_len * 2);

			dgram_counter++;
			अगर (index2 == 0 || dg_len2 == 0)
				अवरोध;
		पूर्ण जबतक (ndp_len > 2 * (opts->dgram_item_len * 2));
	पूर्ण जबतक (ndp_index);

	dev_consume_skb_any(skb);

	VDBG(port->func.config->cdev,
	     "Parsed NTB with %d frames\n", dgram_counter);
	वापस 0;
err:
	skb_queue_purge(list);
	dev_kमुक्त_skb_any(skb);
	वापस ret;
पूर्ण

अटल व्योम ncm_disable(काष्ठा usb_function *f)
अणु
	काष्ठा f_ncm		*ncm = func_to_ncm(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	DBG(cdev, "ncm deactivated\n");

	अगर (ncm->port.in_ep->enabled) अणु
		ncm->समयr_stopping = true;
		ncm->netdev = शून्य;
		gether_disconnect(&ncm->port);
	पूर्ण

	अगर (ncm->notअगरy->enabled) अणु
		usb_ep_disable(ncm->notअगरy);
		ncm->notअगरy->desc = शून्य;
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * Callbacks let us notअगरy the host about connect/disconnect when the
 * net device is खोलोed or बंदd.
 *
 * For testing, note that link states on this side include both खोलोed
 * and बंदd variants of:
 *
 *   - disconnected/unconfigured
 *   - configured but inactive (data alt 0)
 *   - configured and active (data alt 1)
 *
 * Each needs to be tested with unplug, rmmod, SET_CONFIGURATION, and
 * SET_INTERFACE (altsetting).  Remember also that "configured" करोesn't
 * imply the host is actually polling the notअगरication endpoपूर्णांक, and
 * likewise that "active" करोesn't imply it's actually using the data
 * endpoपूर्णांकs क्रम traffic.
 */

अटल व्योम ncm_खोलो(काष्ठा gether *geth)
अणु
	काष्ठा f_ncm		*ncm = func_to_ncm(&geth->func);

	DBG(ncm->port.func.config->cdev, "%s\n", __func__);

	spin_lock(&ncm->lock);
	ncm->is_खोलो = true;
	ncm_notअगरy(ncm);
	spin_unlock(&ncm->lock);
पूर्ण

अटल व्योम ncm_बंद(काष्ठा gether *geth)
अणु
	काष्ठा f_ncm		*ncm = func_to_ncm(&geth->func);

	DBG(ncm->port.func.config->cdev, "%s\n", __func__);

	spin_lock(&ncm->lock);
	ncm->is_खोलो = false;
	ncm_notअगरy(ncm);
	spin_unlock(&ncm->lock);
पूर्ण

/*-------------------------------------------------------------------------*/

/* ethernet function driver setup/binding */

अटल पूर्णांक ncm_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा f_ncm		*ncm = func_to_ncm(f);
	काष्ठा usb_string	*us;
	पूर्णांक			status;
	काष्ठा usb_ep		*ep;
	काष्ठा f_ncm_opts	*ncm_opts;

	अगर (!can_support_ecm(cdev->gadget))
		वापस -EINVAL;

	ncm_opts = container_of(f->fi, काष्ठा f_ncm_opts, func_inst);

	अगर (cdev->use_os_string) अणु
		f->os_desc_table = kzalloc(माप(*f->os_desc_table),
					   GFP_KERNEL);
		अगर (!f->os_desc_table)
			वापस -ENOMEM;
		f->os_desc_n = 1;
		f->os_desc_table[0].os_desc = &ncm_opts->ncm_os_desc;
	पूर्ण

	/*
	 * in drivers/usb/gadget/configfs.c:configfs_composite_bind()
	 * configurations are bound in sequence with list_क्रम_each_entry,
	 * in each configuration its functions are bound in sequence
	 * with list_क्रम_each_entry, so we assume no race condition
	 * with regard to ncm_opts->bound access
	 */
	अगर (!ncm_opts->bound) अणु
		mutex_lock(&ncm_opts->lock);
		gether_set_gadget(ncm_opts->net, cdev->gadget);
		status = gether_रेजिस्टर_netdev(ncm_opts->net);
		mutex_unlock(&ncm_opts->lock);
		अगर (status)
			जाओ fail;
		ncm_opts->bound = true;
	पूर्ण
	us = usb_gstrings_attach(cdev, ncm_strings,
				 ARRAY_SIZE(ncm_string_defs));
	अगर (IS_ERR(us)) अणु
		status = PTR_ERR(us);
		जाओ fail;
	पूर्ण
	ncm_control_पूर्णांकf.iInterface = us[STRING_CTRL_IDX].id;
	ncm_data_nop_पूर्णांकf.iInterface = us[STRING_DATA_IDX].id;
	ncm_data_पूर्णांकf.iInterface = us[STRING_DATA_IDX].id;
	ecm_desc.iMACAddress = us[STRING_MAC_IDX].id;
	ncm_iad_desc.iFunction = us[STRING_IAD_IDX].id;

	/* allocate instance-specअगरic पूर्णांकerface IDs */
	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	ncm->ctrl_id = status;
	ncm_iad_desc.bFirstInterface = status;

	ncm_control_पूर्णांकf.bInterfaceNumber = status;
	ncm_जोड़_desc.bMasterInterface0 = status;

	अगर (cdev->use_os_string)
		f->os_desc_table[0].अगर_id =
			ncm_iad_desc.bFirstInterface;

	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	ncm->data_id = status;

	ncm_data_nop_पूर्णांकf.bInterfaceNumber = status;
	ncm_data_पूर्णांकf.bInterfaceNumber = status;
	ncm_जोड़_desc.bSlaveInterface0 = status;

	status = -ENODEV;

	/* allocate instance-specअगरic endpoपूर्णांकs */
	ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_ncm_in_desc);
	अगर (!ep)
		जाओ fail;
	ncm->port.in_ep = ep;

	ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_ncm_out_desc);
	अगर (!ep)
		जाओ fail;
	ncm->port.out_ep = ep;

	ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_ncm_notअगरy_desc);
	अगर (!ep)
		जाओ fail;
	ncm->notअगरy = ep;

	status = -ENOMEM;

	/* allocate notअगरication request and buffer */
	ncm->notअगरy_req = usb_ep_alloc_request(ep, GFP_KERNEL);
	अगर (!ncm->notअगरy_req)
		जाओ fail;
	ncm->notअगरy_req->buf = kदो_स्मृति(NCM_STATUS_BYTECOUNT, GFP_KERNEL);
	अगर (!ncm->notअगरy_req->buf)
		जाओ fail;
	ncm->notअगरy_req->context = ncm;
	ncm->notअगरy_req->complete = ncm_notअगरy_complete;

	/*
	 * support all relevant hardware speeds... we expect that when
	 * hardware is dual speed, all bulk-capable endpoपूर्णांकs work at
	 * both speeds
	 */
	hs_ncm_in_desc.bEndpoपूर्णांकAddress = fs_ncm_in_desc.bEndpoपूर्णांकAddress;
	hs_ncm_out_desc.bEndpoपूर्णांकAddress = fs_ncm_out_desc.bEndpoपूर्णांकAddress;
	hs_ncm_notअगरy_desc.bEndpoपूर्णांकAddress =
		fs_ncm_notअगरy_desc.bEndpoपूर्णांकAddress;

	ss_ncm_in_desc.bEndpoपूर्णांकAddress = fs_ncm_in_desc.bEndpoपूर्णांकAddress;
	ss_ncm_out_desc.bEndpoपूर्णांकAddress = fs_ncm_out_desc.bEndpoपूर्णांकAddress;
	ss_ncm_notअगरy_desc.bEndpoपूर्णांकAddress =
		fs_ncm_notअगरy_desc.bEndpoपूर्णांकAddress;

	status = usb_assign_descriptors(f, ncm_fs_function, ncm_hs_function,
			ncm_ss_function, ncm_ss_function);
	अगर (status)
		जाओ fail;

	/*
	 * NOTE:  all that is करोne without knowing or caring about
	 * the network link ... which is unavailable to this code
	 * until we're activated via set_alt().
	 */

	ncm->port.खोलो = ncm_खोलो;
	ncm->port.बंद = ncm_बंद;

	hrसमयr_init(&ncm->task_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL_SOFT);
	ncm->task_समयr.function = ncm_tx_समयout;

	DBG(cdev, "CDC Network: %s speed IN/%s OUT/%s NOTIFY/%s\n",
			gadget_is_superspeed(c->cdev->gadget) ? "super" :
			gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full",
			ncm->port.in_ep->name, ncm->port.out_ep->name,
			ncm->notअगरy->name);
	वापस 0;

fail:
	kमुक्त(f->os_desc_table);
	f->os_desc_n = 0;

	अगर (ncm->notअगरy_req) अणु
		kमुक्त(ncm->notअगरy_req->buf);
		usb_ep_मुक्त_request(ncm->notअगरy, ncm->notअगरy_req);
	पूर्ण

	ERROR(cdev, "%s: can't bind, err %d\n", f->name, status);

	वापस status;
पूर्ण

अटल अंतरभूत काष्ठा f_ncm_opts *to_f_ncm_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_ncm_opts,
			    func_inst.group);
पूर्ण

/* f_ncm_item_ops */
USB_ETHERNET_CONFIGFS_ITEM(ncm);

/* f_ncm_opts_dev_addr */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_DEV_ADDR(ncm);

/* f_ncm_opts_host_addr */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_HOST_ADDR(ncm);

/* f_ncm_opts_qmult */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_QMULT(ncm);

/* f_ncm_opts_अगरname */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_IFNAME(ncm);

अटल काष्ठा configfs_attribute *ncm_attrs[] = अणु
	&ncm_opts_attr_dev_addr,
	&ncm_opts_attr_host_addr,
	&ncm_opts_attr_qmult,
	&ncm_opts_attr_अगरname,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type ncm_func_type = अणु
	.ct_item_ops	= &ncm_item_ops,
	.ct_attrs	= ncm_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम ncm_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_ncm_opts *opts;

	opts = container_of(f, काष्ठा f_ncm_opts, func_inst);
	अगर (opts->bound)
		gether_cleanup(netdev_priv(opts->net));
	अन्यथा
		मुक्त_netdev(opts->net);
	kमुक्त(opts->ncm_पूर्णांकerf_group);
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *ncm_alloc_inst(व्योम)
अणु
	काष्ठा f_ncm_opts *opts;
	काष्ठा usb_os_desc *descs[1];
	अक्षर *names[1];
	काष्ठा config_group *ncm_पूर्णांकerf_group;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);
	opts->ncm_os_desc.ext_compat_id = opts->ncm_ext_compat_id;

	mutex_init(&opts->lock);
	opts->func_inst.मुक्त_func_inst = ncm_मुक्त_inst;
	opts->net = gether_setup_शेष();
	अगर (IS_ERR(opts->net)) अणु
		काष्ठा net_device *net = opts->net;
		kमुक्त(opts);
		वापस ERR_CAST(net);
	पूर्ण
	INIT_LIST_HEAD(&opts->ncm_os_desc.ext_prop);

	descs[0] = &opts->ncm_os_desc;
	names[0] = "ncm";

	config_group_init_type_name(&opts->func_inst.group, "", &ncm_func_type);
	ncm_पूर्णांकerf_group =
		usb_os_desc_prepare_पूर्णांकerf_dir(&opts->func_inst.group, 1, descs,
					       names, THIS_MODULE);
	अगर (IS_ERR(ncm_पूर्णांकerf_group)) अणु
		ncm_मुक्त_inst(&opts->func_inst);
		वापस ERR_CAST(ncm_पूर्णांकerf_group);
	पूर्ण
	opts->ncm_पूर्णांकerf_group = ncm_पूर्णांकerf_group;

	वापस &opts->func_inst;
पूर्ण

अटल व्योम ncm_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा f_ncm *ncm;
	काष्ठा f_ncm_opts *opts;

	ncm = func_to_ncm(f);
	opts = container_of(f->fi, काष्ठा f_ncm_opts, func_inst);
	kमुक्त(ncm);
	mutex_lock(&opts->lock);
	opts->refcnt--;
	mutex_unlock(&opts->lock);
पूर्ण

अटल व्योम ncm_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा f_ncm *ncm = func_to_ncm(f);

	DBG(c->cdev, "ncm unbind\n");

	hrसमयr_cancel(&ncm->task_समयr);

	kमुक्त(f->os_desc_table);
	f->os_desc_n = 0;

	ncm_string_defs[0].id = 0;
	usb_मुक्त_all_descriptors(f);

	अगर (atomic_पढ़ो(&ncm->notअगरy_count)) अणु
		usb_ep_dequeue(ncm->notअगरy, ncm->notअगरy_req);
		atomic_set(&ncm->notअगरy_count, 0);
	पूर्ण

	kमुक्त(ncm->notअगरy_req->buf);
	usb_ep_मुक्त_request(ncm->notअगरy, ncm->notअगरy_req);
पूर्ण

अटल काष्ठा usb_function *ncm_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_ncm		*ncm;
	काष्ठा f_ncm_opts	*opts;
	पूर्णांक status;

	/* allocate and initialize one new instance */
	ncm = kzalloc(माप(*ncm), GFP_KERNEL);
	अगर (!ncm)
		वापस ERR_PTR(-ENOMEM);

	opts = container_of(fi, काष्ठा f_ncm_opts, func_inst);
	mutex_lock(&opts->lock);
	opts->refcnt++;

	/* export host's Ethernet address in CDC क्रमmat */
	status = gether_get_host_addr_cdc(opts->net, ncm->ethaddr,
				      माप(ncm->ethaddr));
	अगर (status < 12) अणु /* म_माप("01234567890a") */
		kमुक्त(ncm);
		mutex_unlock(&opts->lock);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	ncm_string_defs[STRING_MAC_IDX].s = ncm->ethaddr;

	spin_lock_init(&ncm->lock);
	ncm_reset_values(ncm);
	ncm->port.ioport = netdev_priv(opts->net);
	mutex_unlock(&opts->lock);
	ncm->port.is_fixed = true;
	ncm->port.supports_multi_frame = true;

	ncm->port.func.name = "cdc_network";
	/* descriptors are per-instance copies */
	ncm->port.func.bind = ncm_bind;
	ncm->port.func.unbind = ncm_unbind;
	ncm->port.func.set_alt = ncm_set_alt;
	ncm->port.func.get_alt = ncm_get_alt;
	ncm->port.func.setup = ncm_setup;
	ncm->port.func.disable = ncm_disable;
	ncm->port.func.मुक्त_func = ncm_मुक्त;

	ncm->port.wrap = ncm_wrap_ntb;
	ncm->port.unwrap = ncm_unwrap_ntb;

	वापस &ncm->port.func;
पूर्ण

DECLARE_USB_FUNCTION_INIT(ncm, ncm_alloc_inst, ncm_alloc);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yauheni Kaliuta");
