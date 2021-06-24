<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ISHTP-HID glue driver's definitions.
 *
 * Copyright (c) 2014-2016, Intel Corporation.
 */
#अगर_अघोषित ISHTP_HID__H
#घोषणा	ISHTP_HID__H

/* The fixed ISH product and venकरोr id */
#घोषणा	ISH_HID_VENDOR	0x8086
#घोषणा	ISH_HID_PRODUCT	0x22D8
#घोषणा	ISH_HID_VERSION	0x0200

#घोषणा	CMD_MASK	0x7F
#घोषणा	IS_RESPONSE	0x80

/* Used to dump to Linux trace buffer, अगर enabled */
बाह्य व्योम (*hid_prपूर्णांक_trace)(व्योम *unused, स्थिर अक्षर *क्रमmat, ...);
#घोषणा hid_ishtp_trace(client, ...) \
		(hid_prपूर्णांक_trace)(शून्य, __VA_ARGS__)

/* ISH Transport protocol (ISHTP in लघु) GUID */
अटल स्थिर guid_t hid_ishtp_guid =
	GUID_INIT(0x33AECD58, 0xB679, 0x4E54,
		  0x9B, 0xD9, 0xA0, 0x4D, 0x34, 0xF0, 0xC2, 0x26);

/* ISH HID message काष्ठाure */
काष्ठा hostअगर_msg_hdr अणु
	uपूर्णांक8_t	command; /* Bit 7: is_response */
	uपूर्णांक8_t	device_id;
	uपूर्णांक8_t	status;
	uपूर्णांक8_t	flags;
	uपूर्णांक16_t size;
पूर्ण __packed;

काष्ठा hostअगर_msg अणु
	काष्ठा hostअगर_msg_hdr	hdr;
पूर्ण __packed;

काष्ठा hostअगर_msg_to_sensor अणु
	काष्ठा hostअगर_msg_hdr	hdr;
	uपूर्णांक8_t	report_id;
पूर्ण __packed;

काष्ठा device_info अणु
	uपूर्णांक32_t dev_id;
	uपूर्णांक8_t dev_class;
	uपूर्णांक16_t pid;
	uपूर्णांक16_t vid;
पूर्ण __packed;

काष्ठा ishtp_version अणु
	uपूर्णांक8_t	major;
	uपूर्णांक8_t	minor;
	uपूर्णांक8_t	hotfix;
	uपूर्णांक16_t build;
पूर्ण __packed;

/* काष्ठा क्रम ISHTP aggregated input data */
काष्ठा report_list अणु
	uपूर्णांक16_t total_size;
	uपूर्णांक8_t	num_of_reports;
	uपूर्णांक8_t	flags;
	काष्ठा अणु
		uपूर्णांक16_t	size_of_report;
		uपूर्णांक8_t report[1];
	पूर्ण __packed reports[1];
पूर्ण __packed;

/* HOSTIF commands */
#घोषणा	HOSTIF_HID_COMMAND_BASE			0
#घोषणा	HOSTIF_GET_HID_DESCRIPTOR		0
#घोषणा	HOSTIF_GET_REPORT_DESCRIPTOR		1
#घोषणा HOSTIF_GET_FEATURE_REPORT		2
#घोषणा	HOSTIF_SET_FEATURE_REPORT		3
#घोषणा	HOSTIF_GET_INPUT_REPORT			4
#घोषणा	HOSTIF_PUBLISH_INPUT_REPORT		5
#घोषणा	HOSTIF_PUBLISH_INPUT_REPORT_LIST	6
#घोषणा	HOSTIF_DM_COMMAND_BASE			32
#घोषणा	HOSTIF_DM_ENUM_DEVICES			33
#घोषणा	HOSTIF_DM_ADD_DEVICE			34

#घोषणा	MAX_HID_DEVICES				32

/**
 * काष्ठा ishtp_cl_data - Encapsulate per ISH TP HID Client
 * @क्रमागत_device_करोne:	Enum devices response complete flag
 * @hid_descr_करोne:	HID descriptor complete flag
 * @report_descr_करोne:	Get report descriptor complete flag
 * @init_करोne:		Init process completed successfully
 * @suspended:		System is under suspend state or in progress
 * @num_hid_devices:	Number of HID devices क्रमागतerated in this client
 * @cur_hid_dev:	This keeps track of the device index क्रम which
 *			initialization and registration with HID core
 *			in progress.
 * @hid_devices:	Store vid/pid/devid क्रम each क्रमागतerated HID device
 * @report_descr:	Stores the raw report descriptors क्रम each HID device
 * @report_descr_size:	Report description of size of above repo_descr[]
 * @hid_sensor_hubs:	Poपूर्णांकer to hid_device क्रम all HID device, so that
 *			when clients are हटाओd, they can be मुक्तd
 * @hid_descr:		Poपूर्णांकer to hid descriptor क्रम each क्रमागतerated hid
 *			device
 * @hid_descr_size:	Size of each above report descriptor
 * @init_रुको:		Wait queue to रुको during initialization, where the
 *			client send message to ISH FW and रुको क्रम response
 * @ishtp_hid_रुको:	The रुको क्रम get report during रुको callback from hid
 *			core
 * @bad_recv_cnt:	Running count of packets received with error
 * @multi_packet_cnt:	Count of fragmented packet count
 *
 * This काष्ठाure is used to store completion flags and per client data like
 * like report description, number of HID devices etc.
 */
काष्ठा ishtp_cl_data अणु
	/* completion flags */
	bool क्रमागत_devices_करोne;
	bool hid_descr_करोne;
	bool report_descr_करोne;
	bool init_करोne;
	bool suspended;

	अचिन्हित पूर्णांक num_hid_devices;
	अचिन्हित पूर्णांक cur_hid_dev;
	अचिन्हित पूर्णांक hid_dev_count;

	काष्ठा device_info *hid_devices;
	अचिन्हित अक्षर *report_descr[MAX_HID_DEVICES];
	पूर्णांक report_descr_size[MAX_HID_DEVICES];
	काष्ठा hid_device *hid_sensor_hubs[MAX_HID_DEVICES];
	अचिन्हित अक्षर *hid_descr[MAX_HID_DEVICES];
	पूर्णांक hid_descr_size[MAX_HID_DEVICES];

	रुको_queue_head_t init_रुको;
	रुको_queue_head_t ishtp_resume_रुको;
	काष्ठा ishtp_cl *hid_ishtp_cl;

	/* Statistics */
	अचिन्हित पूर्णांक bad_recv_cnt;
	पूर्णांक multi_packet_cnt;

	काष्ठा work_काष्ठा work;
	काष्ठा ishtp_cl_device *cl_device;
पूर्ण;

/**
 * काष्ठा ishtp_hid_data - Per instance HID data
 * @index:		Device index in the order of क्रमागतeration
 * @request_करोne:	Get Feature/Input report complete flag
 *			used during get/set request from hid core
 * @client_data:	Link to the client instance
 * @hid_रुको:		Completion रुकोq
 *
 * @raw_get_req:	Flag indicating raw get request ongoing
 * @raw_buf:		raw request buffer filled on receiving get report
 * @raw_buf_size:	raw request buffer size
 * Used to tie hid hid->driver data to driver client instance
 */
काष्ठा ishtp_hid_data अणु
	पूर्णांक index;
	bool request_करोne;
	काष्ठा ishtp_cl_data *client_data;
	रुको_queue_head_t hid_रुको;

	/* raw request */
	bool raw_get_req;
	u8 *raw_buf;
	माप_प्रकार raw_buf_size;
पूर्ण;

/* Interface functions between HID LL driver and ISH TP client */
व्योम hid_ishtp_set_feature(काष्ठा hid_device *hid, अक्षर *buf, अचिन्हित पूर्णांक len,
			   पूर्णांक report_id);
व्योम hid_ishtp_get_report(काष्ठा hid_device *hid, पूर्णांक report_id,
			  पूर्णांक report_type);
पूर्णांक ishtp_hid_probe(अचिन्हित पूर्णांक cur_hid_dev,
		    काष्ठा ishtp_cl_data *client_data);
व्योम ishtp_hid_हटाओ(काष्ठा ishtp_cl_data *client_data);
पूर्णांक ishtp_hid_link_पढ़ोy_रुको(काष्ठा ishtp_cl_data *client_data);
व्योम ishtp_hid_wakeup(काष्ठा hid_device *hid);

#पूर्ण_अगर	/* ISHTP_HID__H */
