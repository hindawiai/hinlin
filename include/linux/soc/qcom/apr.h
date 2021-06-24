<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __QCOM_APR_H_
#घोषणा __QCOM_APR_H_

#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <dt-bindings/soc/qcom,apr.h>

बाह्य काष्ठा bus_type aprbus;

#घोषणा APR_HDR_LEN(hdr_len) ((hdr_len)/4)

/*
 * HEADER field
 * version:0:3
 * header_size : 4:7
 * message_type : 8:9
 * reserved: 10:15
 */
#घोषणा APR_HDR_FIELD(msg_type, hdr_len, ver)\
	(((msg_type & 0x3) << 8) | ((hdr_len & 0xF) << 4) | (ver & 0xF))

#घोषणा APR_HDR_SIZE माप(काष्ठा apr_hdr)
#घोषणा APR_SEQ_CMD_HDR_FIELD APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD, \
					    APR_HDR_LEN(APR_HDR_SIZE), \
					    APR_PKT_VER)
/* Version */
#घोषणा APR_PKT_VER		0x0

/* Command and Response Types */
#घोषणा APR_MSG_TYPE_EVENT	0x0
#घोषणा APR_MSG_TYPE_CMD_RSP	0x1
#घोषणा APR_MSG_TYPE_SEQ_CMD	0x2
#घोषणा APR_MSG_TYPE_NSEQ_CMD	0x3
#घोषणा APR_MSG_TYPE_MAX	0x04

/* APR Basic Response Message */
#घोषणा APR_BASIC_RSP_RESULT 0x000110E8
#घोषणा APR_RSP_ACCEPTED     0x000100BE

काष्ठा aprv2_ibasic_rsp_result_t अणु
	uपूर्णांक32_t opcode;
	uपूर्णांक32_t status;
पूर्ण;

/* hdr field Ver [0:3], Size [4:7], Message type [8:10] */
#घोषणा APR_HDR_FIELD_VER(h)		(h & 0x000F)
#घोषणा APR_HDR_FIELD_SIZE(h)		((h & 0x00F0) >> 4)
#घोषणा APR_HDR_FIELD_SIZE_BYTES(h)	(((h & 0x00F0) >> 4) * 4)
#घोषणा APR_HDR_FIELD_MT(h)		((h & 0x0300) >> 8)

काष्ठा apr_hdr अणु
	uपूर्णांक16_t hdr_field;
	uपूर्णांक16_t pkt_size;
	uपूर्णांक8_t src_svc;
	uपूर्णांक8_t src_करोमुख्य;
	uपूर्णांक16_t src_port;
	uपूर्णांक8_t dest_svc;
	uपूर्णांक8_t dest_करोमुख्य;
	uपूर्णांक16_t dest_port;
	uपूर्णांक32_t token;
	uपूर्णांक32_t opcode;
पूर्ण __packed;

काष्ठा apr_pkt अणु
	काष्ठा apr_hdr hdr;
	uपूर्णांक8_t payload[];
पूर्ण;

काष्ठा apr_resp_pkt अणु
	काष्ठा apr_hdr hdr;
	व्योम *payload;
	पूर्णांक payload_size;
पूर्ण;

/* Bits 0 to 15 -- Minor version,  Bits 16 to 31 -- Major version */
#घोषणा APR_SVC_MAJOR_VERSION(v)	((v >> 16) & 0xFF)
#घोषणा APR_SVC_MINOR_VERSION(v)	(v & 0xFF)

काष्ठा apr_device अणु
	काष्ठा device	dev;
	uपूर्णांक16_t	svc_id;
	uपूर्णांक16_t	करोमुख्य_id;
	uपूर्णांक32_t	version;
	अक्षर name[APR_NAME_SIZE];
	स्थिर अक्षर *service_path;
	spinlock_t	lock;
	काष्ठा list_head node;
पूर्ण;

#घोषणा to_apr_device(d) container_of(d, काष्ठा apr_device, dev)

काष्ठा apr_driver अणु
	पूर्णांक	(*probe)(काष्ठा apr_device *sl);
	पूर्णांक	(*हटाओ)(काष्ठा apr_device *sl);
	पूर्णांक	(*callback)(काष्ठा apr_device *a,
			    काष्ठा apr_resp_pkt *d);
	काष्ठा device_driver		driver;
	स्थिर काष्ठा apr_device_id	*id_table;
पूर्ण;

#घोषणा to_apr_driver(d) container_of(d, काष्ठा apr_driver, driver)

/*
 * use a macro to aव्योम include chaining to get THIS_MODULE
 */
#घोषणा apr_driver_रेजिस्टर(drv) __apr_driver_रेजिस्टर(drv, THIS_MODULE)

पूर्णांक __apr_driver_रेजिस्टर(काष्ठा apr_driver *drv, काष्ठा module *owner);
व्योम apr_driver_unरेजिस्टर(काष्ठा apr_driver *drv);

/**
 * module_apr_driver() - Helper macro क्रम रेजिस्टरing a aprbus driver
 * @__apr_driver: apr_driver काष्ठा
 *
 * Helper macro क्रम aprbus drivers which करो not करो anything special in
 * module init/निकास. This eliminates a lot of boilerplate. Each module
 * may only use this macro once, and calling it replaces module_init()
 * and module_निकास()
 */
#घोषणा module_apr_driver(__apr_driver) \
	module_driver(__apr_driver, apr_driver_रेजिस्टर, \
			apr_driver_unरेजिस्टर)

पूर्णांक apr_send_pkt(काष्ठा apr_device *adev, काष्ठा apr_pkt *pkt);

#पूर्ण_अगर /* __QCOM_APR_H_ */
