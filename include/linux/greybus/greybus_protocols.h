<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/*
 * Copyright(c) 2014 - 2015 Google Inc. All rights reserved.
 * Copyright(c) 2014 - 2015 Linaro Ltd. All rights reserved.
 */

#अगर_अघोषित __GREYBUS_PROTOCOLS_H
#घोषणा __GREYBUS_PROTOCOLS_H

#समावेश <linux/types.h>

/* Fixed IDs क्रम control/svc protocols */

/* SVC चयन-port device ids */
#घोषणा GB_SVC_DEVICE_ID_SVC			0
#घोषणा GB_SVC_DEVICE_ID_AP			1
#घोषणा GB_SVC_DEVICE_ID_MIN			2
#घोषणा GB_SVC_DEVICE_ID_MAX			31

#घोषणा GB_SVC_CPORT_ID				0
#घोषणा GB_CONTROL_BUNDLE_ID			0
#घोषणा GB_CONTROL_CPORT_ID			0


/*
 * All operation messages (both requests and responses) begin with
 * a header that encodes the size of the message (header included).
 * This header also contains a unique identअगरier, that associates a
 * response message with its operation.  The header contains an
 * operation type field, whose पूर्णांकerpretation is dependent on what
 * type of protocol is used over the connection.  The high bit
 * (0x80) of the operation type field is used to indicate whether
 * the message is a request (clear) or a response (set).
 *
 * Response messages include an additional result byte, which
 * communicates the result of the corresponding request.  A zero
 * result value means the operation completed successfully.  Any
 * other value indicates an error; in this हाल, the payload of the
 * response message (अगर any) is ignored.  The result byte must be
 * zero in the header क्रम a request message.
 *
 * The wire क्रमmat क्रम all numeric fields in the header is little
 * endian.  Any operation-specअगरic data begins immediately after the
 * header.
 */
काष्ठा gb_operation_msg_hdr अणु
	__le16	size;		/* Size in bytes of header + payload */
	__le16	operation_id;	/* Operation unique id */
	__u8	type;		/* E.g GB_I2C_TYPE_* or GB_GPIO_TYPE_* */
	__u8	result;		/* Result of request (in responses only) */
	__u8	pad[2];		/* must be zero (ignore when पढ़ो) */
पूर्ण __packed;


/* Generic request types */
#घोषणा GB_REQUEST_TYPE_CPORT_SHUTDOWN		0x00
#घोषणा GB_REQUEST_TYPE_INVALID			0x7f

काष्ठा gb_cport_shutकरोwn_request अणु
	__u8 phase;
पूर्ण __packed;


/* Control Protocol */

/* Greybus control request types */
#घोषणा GB_CONTROL_TYPE_VERSION			0x01
#घोषणा GB_CONTROL_TYPE_PROBE_AP		0x02
#घोषणा GB_CONTROL_TYPE_GET_MANIFEST_SIZE	0x03
#घोषणा GB_CONTROL_TYPE_GET_MANIFEST		0x04
#घोषणा GB_CONTROL_TYPE_CONNECTED		0x05
#घोषणा GB_CONTROL_TYPE_DISCONNECTED		0x06
#घोषणा GB_CONTROL_TYPE_TIMESYNC_ENABLE		0x07
#घोषणा GB_CONTROL_TYPE_TIMESYNC_DISABLE	0x08
#घोषणा GB_CONTROL_TYPE_TIMESYNC_AUTHORITATIVE	0x09
/*	Unused					0x0a */
#घोषणा GB_CONTROL_TYPE_BUNDLE_VERSION		0x0b
#घोषणा GB_CONTROL_TYPE_DISCONNECTING		0x0c
#घोषणा GB_CONTROL_TYPE_TIMESYNC_GET_LAST_EVENT	0x0d
#घोषणा GB_CONTROL_TYPE_MODE_SWITCH		0x0e
#घोषणा GB_CONTROL_TYPE_BUNDLE_SUSPEND		0x0f
#घोषणा GB_CONTROL_TYPE_BUNDLE_RESUME		0x10
#घोषणा GB_CONTROL_TYPE_BUNDLE_DEACTIVATE	0x11
#घोषणा GB_CONTROL_TYPE_BUNDLE_ACTIVATE		0x12
#घोषणा GB_CONTROL_TYPE_INTF_SUSPEND_PREPARE		0x13
#घोषणा GB_CONTROL_TYPE_INTF_DEACTIVATE_PREPARE	0x14
#घोषणा GB_CONTROL_TYPE_INTF_HIBERNATE_ABORT	0x15

काष्ठा gb_control_version_request अणु
	__u8	major;
	__u8	minor;
पूर्ण __packed;

काष्ठा gb_control_version_response अणु
	__u8	major;
	__u8	minor;
पूर्ण __packed;

काष्ठा gb_control_bundle_version_request अणु
	__u8	bundle_id;
पूर्ण __packed;

काष्ठा gb_control_bundle_version_response अणु
	__u8	major;
	__u8	minor;
पूर्ण __packed;

/* Control protocol manअगरest get size request has no payload*/
काष्ठा gb_control_get_manअगरest_size_response अणु
	__le16			size;
पूर्ण __packed;

/* Control protocol manअगरest get request has no payload */
काष्ठा gb_control_get_manअगरest_response अणु
	__u8			data[0];
पूर्ण __packed;

/* Control protocol [dis]connected request */
काष्ठा gb_control_connected_request अणु
	__le16			cport_id;
पूर्ण __packed;

काष्ठा gb_control_disconnecting_request अणु
	__le16			cport_id;
पूर्ण __packed;
/* disconnecting response has no payload */

काष्ठा gb_control_disconnected_request अणु
	__le16			cport_id;
पूर्ण __packed;
/* Control protocol [dis]connected response has no payload */

/*
 * All Bundle घातer management operations use the same request and response
 * layout and status codes.
 */

#घोषणा GB_CONTROL_BUNDLE_PM_OK		0x00
#घोषणा GB_CONTROL_BUNDLE_PM_INVAL	0x01
#घोषणा GB_CONTROL_BUNDLE_PM_BUSY	0x02
#घोषणा GB_CONTROL_BUNDLE_PM_FAIL	0x03
#घोषणा GB_CONTROL_BUNDLE_PM_NA		0x04

काष्ठा gb_control_bundle_pm_request अणु
	__u8	bundle_id;
पूर्ण __packed;

काष्ठा gb_control_bundle_pm_response अणु
	__u8	status;
पूर्ण __packed;

/*
 * Interface Suspend Prepare and Deactivate Prepare operations use the same
 * response layout and error codes. Define a single response काष्ठाure and reuse
 * it. Both operations have no payload.
 */

#घोषणा GB_CONTROL_INTF_PM_OK		0x00
#घोषणा GB_CONTROL_INTF_PM_BUSY		0x01
#घोषणा GB_CONTROL_INTF_PM_NA		0x02

काष्ठा gb_control_पूर्णांकf_pm_response अणु
	__u8	status;
पूर्ण __packed;

/* APBridge protocol */

/* request APB1 log */
#घोषणा GB_APB_REQUEST_LOG			0x02

/* request to map a cport to bulk in and bulk out endpoपूर्णांकs */
#घोषणा GB_APB_REQUEST_EP_MAPPING		0x03

/* request to get the number of cports available */
#घोषणा GB_APB_REQUEST_CPORT_COUNT		0x04

/* request to reset a cport state */
#घोषणा GB_APB_REQUEST_RESET_CPORT		0x05

/* request to समय the latency of messages on a given cport */
#घोषणा GB_APB_REQUEST_LATENCY_TAG_EN		0x06
#घोषणा GB_APB_REQUEST_LATENCY_TAG_DIS		0x07

/* request to control the CSI transmitter */
#घोषणा GB_APB_REQUEST_CSI_TX_CONTROL		0x08

/* request to control audio streaming */
#घोषणा GB_APB_REQUEST_AUDIO_CONTROL		0x09

/* TimeSync requests */
#घोषणा GB_APB_REQUEST_TIMESYNC_ENABLE		0x0d
#घोषणा GB_APB_REQUEST_TIMESYNC_DISABLE		0x0e
#घोषणा GB_APB_REQUEST_TIMESYNC_AUTHORITATIVE	0x0f
#घोषणा GB_APB_REQUEST_TIMESYNC_GET_LAST_EVENT	0x10

/* requests to set Greybus CPort flags */
#घोषणा GB_APB_REQUEST_CPORT_FLAGS		0x11

/* ARPC request */
#घोषणा GB_APB_REQUEST_ARPC_RUN			0x12

काष्ठा gb_apb_request_cport_flags अणु
	__le32	flags;
#घोषणा GB_APB_CPORT_FLAG_CONTROL		0x01
#घोषणा GB_APB_CPORT_FLAG_HIGH_PRIO		0x02
पूर्ण __packed;


/* Firmware Download Protocol */

/* Request Types */
#घोषणा GB_FW_DOWNLOAD_TYPE_FIND_FIRMWARE	0x01
#घोषणा GB_FW_DOWNLOAD_TYPE_FETCH_FIRMWARE	0x02
#घोषणा GB_FW_DOWNLOAD_TYPE_RELEASE_FIRMWARE	0x03

#घोषणा GB_FIRMWARE_TAG_MAX_SIZE		10

/* firmware करोwnload find firmware request/response */
काष्ठा gb_fw_करोwnload_find_firmware_request अणु
	__u8			firmware_tag[GB_FIRMWARE_TAG_MAX_SIZE];
पूर्ण __packed;

काष्ठा gb_fw_करोwnload_find_firmware_response अणु
	__u8			firmware_id;
	__le32			size;
पूर्ण __packed;

/* firmware करोwnload fetch firmware request/response */
काष्ठा gb_fw_करोwnload_fetch_firmware_request अणु
	__u8			firmware_id;
	__le32			offset;
	__le32			size;
पूर्ण __packed;

काष्ठा gb_fw_करोwnload_fetch_firmware_response अणु
	__u8			data[0];
पूर्ण __packed;

/* firmware करोwnload release firmware request */
काष्ठा gb_fw_करोwnload_release_firmware_request अणु
	__u8			firmware_id;
पूर्ण __packed;
/* firmware करोwnload release firmware response has no payload */


/* Firmware Management Protocol */

/* Request Types */
#घोषणा GB_FW_MGMT_TYPE_INTERFACE_FW_VERSION	0x01
#घोषणा GB_FW_MGMT_TYPE_LOAD_AND_VALIDATE_FW	0x02
#घोषणा GB_FW_MGMT_TYPE_LOADED_FW		0x03
#घोषणा GB_FW_MGMT_TYPE_BACKEND_FW_VERSION	0x04
#घोषणा GB_FW_MGMT_TYPE_BACKEND_FW_UPDATE	0x05
#घोषणा GB_FW_MGMT_TYPE_BACKEND_FW_UPDATED	0x06

#घोषणा GB_FW_LOAD_METHOD_UNIPRO		0x01
#घोषणा GB_FW_LOAD_METHOD_INTERNAL		0x02

#घोषणा GB_FW_LOAD_STATUS_FAILED		0x00
#घोषणा GB_FW_LOAD_STATUS_UNVALIDATED		0x01
#घोषणा GB_FW_LOAD_STATUS_VALIDATED		0x02
#घोषणा GB_FW_LOAD_STATUS_VALIDATION_FAILED	0x03

#घोषणा GB_FW_BACKEND_FW_STATUS_SUCCESS		0x01
#घोषणा GB_FW_BACKEND_FW_STATUS_FAIL_FIND	0x02
#घोषणा GB_FW_BACKEND_FW_STATUS_FAIL_FETCH	0x03
#घोषणा GB_FW_BACKEND_FW_STATUS_FAIL_WRITE	0x04
#घोषणा GB_FW_BACKEND_FW_STATUS_INT		0x05
#घोषणा GB_FW_BACKEND_FW_STATUS_RETRY		0x06
#घोषणा GB_FW_BACKEND_FW_STATUS_NOT_SUPPORTED	0x07

#घोषणा GB_FW_BACKEND_VERSION_STATUS_SUCCESS		0x01
#घोषणा GB_FW_BACKEND_VERSION_STATUS_NOT_AVAILABLE	0x02
#घोषणा GB_FW_BACKEND_VERSION_STATUS_NOT_SUPPORTED	0x03
#घोषणा GB_FW_BACKEND_VERSION_STATUS_RETRY		0x04
#घोषणा GB_FW_BACKEND_VERSION_STATUS_FAIL_INT		0x05

/* firmware management पूर्णांकerface firmware version request has no payload */
काष्ठा gb_fw_mgmt_पूर्णांकerface_fw_version_response अणु
	__u8			firmware_tag[GB_FIRMWARE_TAG_MAX_SIZE];
	__le16			major;
	__le16			minor;
पूर्ण __packed;

/* firmware management load and validate firmware request/response */
काष्ठा gb_fw_mgmt_load_and_validate_fw_request अणु
	__u8			request_id;
	__u8			load_method;
	__u8			firmware_tag[GB_FIRMWARE_TAG_MAX_SIZE];
पूर्ण __packed;
/* firmware management load and validate firmware response has no payload*/

/* firmware management loaded firmware request */
काष्ठा gb_fw_mgmt_loaded_fw_request अणु
	__u8			request_id;
	__u8			status;
	__le16			major;
	__le16			minor;
पूर्ण __packed;
/* firmware management loaded firmware response has no payload */

/* firmware management backend firmware version request/response */
काष्ठा gb_fw_mgmt_backend_fw_version_request अणु
	__u8			firmware_tag[GB_FIRMWARE_TAG_MAX_SIZE];
पूर्ण __packed;

काष्ठा gb_fw_mgmt_backend_fw_version_response अणु
	__le16			major;
	__le16			minor;
	__u8			status;
पूर्ण __packed;

/* firmware management backend firmware update request */
काष्ठा gb_fw_mgmt_backend_fw_update_request अणु
	__u8			request_id;
	__u8			firmware_tag[GB_FIRMWARE_TAG_MAX_SIZE];
पूर्ण __packed;
/* firmware management backend firmware update response has no payload */

/* firmware management backend firmware updated request */
काष्ठा gb_fw_mgmt_backend_fw_updated_request अणु
	__u8			request_id;
	__u8			status;
पूर्ण __packed;
/* firmware management backend firmware updated response has no payload */


/* Component Authentication Protocol (CAP) */

/* Request Types */
#घोषणा GB_CAP_TYPE_GET_ENDPOINT_UID	0x01
#घोषणा GB_CAP_TYPE_GET_IMS_CERTIFICATE	0x02
#घोषणा GB_CAP_TYPE_AUTHENTICATE	0x03

/* CAP get endpoपूर्णांक uid request has no payload */
काष्ठा gb_cap_get_endpoपूर्णांक_uid_response अणु
	__u8			uid[8];
पूर्ण __packed;

/* CAP get endpoपूर्णांक ims certअगरicate request/response */
काष्ठा gb_cap_get_ims_certअगरicate_request अणु
	__le32			certअगरicate_class;
	__le32			certअगरicate_id;
पूर्ण __packed;

काष्ठा gb_cap_get_ims_certअगरicate_response अणु
	__u8			result_code;
	__u8			certअगरicate[];
पूर्ण __packed;

/* CAP authenticate request/response */
काष्ठा gb_cap_authenticate_request अणु
	__le32			auth_type;
	__u8			uid[8];
	__u8			challenge[32];
पूर्ण __packed;

काष्ठा gb_cap_authenticate_response अणु
	__u8			result_code;
	__u8			response[64];
	__u8			signature[];
पूर्ण __packed;


/* Bootrom Protocol */

/* Version of the Greybus bootrom protocol we support */
#घोषणा GB_BOOTROM_VERSION_MAJOR		0x00
#घोषणा GB_BOOTROM_VERSION_MINOR		0x01

/* Greybus bootrom request types */
#घोषणा GB_BOOTROM_TYPE_VERSION			0x01
#घोषणा GB_BOOTROM_TYPE_FIRMWARE_SIZE		0x02
#घोषणा GB_BOOTROM_TYPE_GET_FIRMWARE		0x03
#घोषणा GB_BOOTROM_TYPE_READY_TO_BOOT		0x04
#घोषणा GB_BOOTROM_TYPE_AP_READY		0x05	/* Request with no-payload */
#घोषणा GB_BOOTROM_TYPE_GET_VID_PID		0x06	/* Request with no-payload */

/* Greybus bootrom boot stages */
#घोषणा GB_BOOTROM_BOOT_STAGE_ONE		0x01 /* Reserved क्रम the boot ROM */
#घोषणा GB_BOOTROM_BOOT_STAGE_TWO		0x02 /* Bootrom package to be loaded by the boot ROM */
#घोषणा GB_BOOTROM_BOOT_STAGE_THREE		0x03 /* Module personality package loaded by Stage 2 firmware */

/* Greybus bootrom पढ़ोy to boot status */
#घोषणा GB_BOOTROM_BOOT_STATUS_INVALID		0x00 /* Firmware blob could not be validated */
#घोषणा GB_BOOTROM_BOOT_STATUS_INSECURE		0x01 /* Firmware blob is valid but insecure */
#घोषणा GB_BOOTROM_BOOT_STATUS_SECURE		0x02 /* Firmware blob is valid and secure */

/* Max bootrom data fetch size in bytes */
#घोषणा GB_BOOTROM_FETCH_MAX			2000

काष्ठा gb_bootrom_version_request अणु
	__u8	major;
	__u8	minor;
पूर्ण __packed;

काष्ठा gb_bootrom_version_response अणु
	__u8	major;
	__u8	minor;
पूर्ण __packed;

/* Bootrom protocol firmware size request/response */
काष्ठा gb_bootrom_firmware_size_request अणु
	__u8			stage;
पूर्ण __packed;

काष्ठा gb_bootrom_firmware_size_response अणु
	__le32			size;
पूर्ण __packed;

/* Bootrom protocol get firmware request/response */
काष्ठा gb_bootrom_get_firmware_request अणु
	__le32			offset;
	__le32			size;
पूर्ण __packed;

काष्ठा gb_bootrom_get_firmware_response अणु
	__u8			data[0];
पूर्ण __packed;

/* Bootrom protocol Ready to boot request */
काष्ठा gb_bootrom_पढ़ोy_to_boot_request अणु
	__u8			status;
पूर्ण __packed;
/* Bootrom protocol Ready to boot response has no payload */

/* Bootrom protocol get VID/PID request has no payload */
काष्ठा gb_bootrom_get_vid_pid_response अणु
	__le32			venकरोr_id;
	__le32			product_id;
पूर्ण __packed;


/* Power Supply */

/* Greybus घातer supply request types */
#घोषणा GB_POWER_SUPPLY_TYPE_GET_SUPPLIES		0x02
#घोषणा GB_POWER_SUPPLY_TYPE_GET_DESCRIPTION		0x03
#घोषणा GB_POWER_SUPPLY_TYPE_GET_PROP_DESCRIPTORS	0x04
#घोषणा GB_POWER_SUPPLY_TYPE_GET_PROPERTY		0x05
#घोषणा GB_POWER_SUPPLY_TYPE_SET_PROPERTY		0x06
#घोषणा GB_POWER_SUPPLY_TYPE_EVENT			0x07

/* Greybus घातer supply battery technologies types */
#घोषणा GB_POWER_SUPPLY_TECH_UNKNOWN			0x0000
#घोषणा GB_POWER_SUPPLY_TECH_NiMH			0x0001
#घोषणा GB_POWER_SUPPLY_TECH_LION			0x0002
#घोषणा GB_POWER_SUPPLY_TECH_LIPO			0x0003
#घोषणा GB_POWER_SUPPLY_TECH_LiFe			0x0004
#घोषणा GB_POWER_SUPPLY_TECH_NiCd			0x0005
#घोषणा GB_POWER_SUPPLY_TECH_LiMn			0x0006

/* Greybus घातer supply types */
#घोषणा GB_POWER_SUPPLY_UNKNOWN_TYPE			0x0000
#घोषणा GB_POWER_SUPPLY_BATTERY_TYPE			0x0001
#घोषणा GB_POWER_SUPPLY_UPS_TYPE			0x0002
#घोषणा GB_POWER_SUPPLY_MAINS_TYPE			0x0003
#घोषणा GB_POWER_SUPPLY_USB_TYPE			0x0004
#घोषणा GB_POWER_SUPPLY_USB_DCP_TYPE			0x0005
#घोषणा GB_POWER_SUPPLY_USB_CDP_TYPE			0x0006
#घोषणा GB_POWER_SUPPLY_USB_ACA_TYPE			0x0007

/* Greybus घातer supply health values */
#घोषणा GB_POWER_SUPPLY_HEALTH_UNKNOWN			0x0000
#घोषणा GB_POWER_SUPPLY_HEALTH_GOOD			0x0001
#घोषणा GB_POWER_SUPPLY_HEALTH_OVERHEAT			0x0002
#घोषणा GB_POWER_SUPPLY_HEALTH_DEAD			0x0003
#घोषणा GB_POWER_SUPPLY_HEALTH_OVERVOLTAGE		0x0004
#घोषणा GB_POWER_SUPPLY_HEALTH_UNSPEC_FAILURE		0x0005
#घोषणा GB_POWER_SUPPLY_HEALTH_COLD			0x0006
#घोषणा GB_POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE	0x0007
#घोषणा GB_POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE	0x0008

/* Greybus घातer supply status values */
#घोषणा GB_POWER_SUPPLY_STATUS_UNKNOWN			0x0000
#घोषणा GB_POWER_SUPPLY_STATUS_CHARGING			0x0001
#घोषणा GB_POWER_SUPPLY_STATUS_DISCHARGING		0x0002
#घोषणा GB_POWER_SUPPLY_STATUS_NOT_CHARGING		0x0003
#घोषणा GB_POWER_SUPPLY_STATUS_FULL			0x0004

/* Greybus घातer supply capacity level values */
#घोषणा GB_POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN		0x0000
#घोषणा GB_POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL		0x0001
#घोषणा GB_POWER_SUPPLY_CAPACITY_LEVEL_LOW		0x0002
#घोषणा GB_POWER_SUPPLY_CAPACITY_LEVEL_NORMAL		0x0003
#घोषणा GB_POWER_SUPPLY_CAPACITY_LEVEL_HIGH		0x0004
#घोषणा GB_POWER_SUPPLY_CAPACITY_LEVEL_FULL		0x0005

/* Greybus घातer supply scope values */
#घोषणा GB_POWER_SUPPLY_SCOPE_UNKNOWN			0x0000
#घोषणा GB_POWER_SUPPLY_SCOPE_SYSTEM			0x0001
#घोषणा GB_POWER_SUPPLY_SCOPE_DEVICE			0x0002

काष्ठा gb_घातer_supply_get_supplies_response अणु
	__u8	supplies_count;
पूर्ण __packed;

काष्ठा gb_घातer_supply_get_description_request अणु
	__u8	psy_id;
पूर्ण __packed;

काष्ठा gb_घातer_supply_get_description_response अणु
	__u8	manufacturer[32];
	__u8	model[32];
	__u8	serial_number[32];
	__le16	type;
	__u8	properties_count;
पूर्ण __packed;

काष्ठा gb_घातer_supply_props_desc अणु
	__u8	property;
#घोषणा GB_POWER_SUPPLY_PROP_STATUS				0x00
#घोषणा GB_POWER_SUPPLY_PROP_CHARGE_TYPE			0x01
#घोषणा GB_POWER_SUPPLY_PROP_HEALTH				0x02
#घोषणा GB_POWER_SUPPLY_PROP_PRESENT				0x03
#घोषणा GB_POWER_SUPPLY_PROP_ONLINE				0x04
#घोषणा GB_POWER_SUPPLY_PROP_AUTHENTIC				0x05
#घोषणा GB_POWER_SUPPLY_PROP_TECHNOLOGY				0x06
#घोषणा GB_POWER_SUPPLY_PROP_CYCLE_COUNT			0x07
#घोषणा GB_POWER_SUPPLY_PROP_VOLTAGE_MAX			0x08
#घोषणा GB_POWER_SUPPLY_PROP_VOLTAGE_MIN			0x09
#घोषणा GB_POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN			0x0A
#घोषणा GB_POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN			0x0B
#घोषणा GB_POWER_SUPPLY_PROP_VOLTAGE_NOW			0x0C
#घोषणा GB_POWER_SUPPLY_PROP_VOLTAGE_AVG			0x0D
#घोषणा GB_POWER_SUPPLY_PROP_VOLTAGE_OCV			0x0E
#घोषणा GB_POWER_SUPPLY_PROP_VOLTAGE_BOOT			0x0F
#घोषणा GB_POWER_SUPPLY_PROP_CURRENT_MAX			0x10
#घोषणा GB_POWER_SUPPLY_PROP_CURRENT_NOW			0x11
#घोषणा GB_POWER_SUPPLY_PROP_CURRENT_AVG			0x12
#घोषणा GB_POWER_SUPPLY_PROP_CURRENT_BOOT			0x13
#घोषणा GB_POWER_SUPPLY_PROP_POWER_NOW				0x14
#घोषणा GB_POWER_SUPPLY_PROP_POWER_AVG				0x15
#घोषणा GB_POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN			0x16
#घोषणा GB_POWER_SUPPLY_PROP_CHARGE_EMPTY_DESIGN		0x17
#घोषणा GB_POWER_SUPPLY_PROP_CHARGE_FULL			0x18
#घोषणा GB_POWER_SUPPLY_PROP_CHARGE_EMPTY			0x19
#घोषणा GB_POWER_SUPPLY_PROP_CHARGE_NOW				0x1A
#घोषणा GB_POWER_SUPPLY_PROP_CHARGE_AVG				0x1B
#घोषणा GB_POWER_SUPPLY_PROP_CHARGE_COUNTER			0x1C
#घोषणा GB_POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT		0x1D
#घोषणा GB_POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX	0x1E
#घोषणा GB_POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE		0x1F
#घोषणा GB_POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX	0x20
#घोषणा GB_POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT		0x21
#घोषणा GB_POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT_MAX		0x22
#घोषणा GB_POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT		0x23
#घोषणा GB_POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN			0x24
#घोषणा GB_POWER_SUPPLY_PROP_ENERGY_EMPTY_DESIGN		0x25
#घोषणा GB_POWER_SUPPLY_PROP_ENERGY_FULL			0x26
#घोषणा GB_POWER_SUPPLY_PROP_ENERGY_EMPTY			0x27
#घोषणा GB_POWER_SUPPLY_PROP_ENERGY_NOW				0x28
#घोषणा GB_POWER_SUPPLY_PROP_ENERGY_AVG				0x29
#घोषणा GB_POWER_SUPPLY_PROP_CAPACITY				0x2A
#घोषणा GB_POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN			0x2B
#घोषणा GB_POWER_SUPPLY_PROP_CAPACITY_ALERT_MAX			0x2C
#घोषणा GB_POWER_SUPPLY_PROP_CAPACITY_LEVEL			0x2D
#घोषणा GB_POWER_SUPPLY_PROP_TEMP				0x2E
#घोषणा GB_POWER_SUPPLY_PROP_TEMP_MAX				0x2F
#घोषणा GB_POWER_SUPPLY_PROP_TEMP_MIN				0x30
#घोषणा GB_POWER_SUPPLY_PROP_TEMP_ALERT_MIN			0x31
#घोषणा GB_POWER_SUPPLY_PROP_TEMP_ALERT_MAX			0x32
#घोषणा GB_POWER_SUPPLY_PROP_TEMP_AMBIENT			0x33
#घोषणा GB_POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MIN		0x34
#घोषणा GB_POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MAX		0x35
#घोषणा GB_POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW			0x36
#घोषणा GB_POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG			0x37
#घोषणा GB_POWER_SUPPLY_PROP_TIME_TO_FULL_NOW			0x38
#घोषणा GB_POWER_SUPPLY_PROP_TIME_TO_FULL_AVG			0x39
#घोषणा GB_POWER_SUPPLY_PROP_TYPE				0x3A
#घोषणा GB_POWER_SUPPLY_PROP_SCOPE				0x3B
#घोषणा GB_POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT		0x3C
#घोषणा GB_POWER_SUPPLY_PROP_CALIBRATE				0x3D
	__u8	is_ग_लिखोable;
पूर्ण __packed;

काष्ठा gb_घातer_supply_get_property_descriptors_request अणु
	__u8	psy_id;
पूर्ण __packed;

काष्ठा gb_घातer_supply_get_property_descriptors_response अणु
	__u8	properties_count;
	काष्ठा gb_घातer_supply_props_desc props[];
पूर्ण __packed;

काष्ठा gb_घातer_supply_get_property_request अणु
	__u8	psy_id;
	__u8	property;
पूर्ण __packed;

काष्ठा gb_घातer_supply_get_property_response अणु
	__le32	prop_val;
पूर्ण;

काष्ठा gb_घातer_supply_set_property_request अणु
	__u8	psy_id;
	__u8	property;
	__le32	prop_val;
पूर्ण __packed;

काष्ठा gb_घातer_supply_event_request अणु
	__u8	psy_id;
	__u8	event;
#घोषणा GB_POWER_SUPPLY_UPDATE		0x01
पूर्ण __packed;


/* HID */

/* Greybus HID operation types */
#घोषणा GB_HID_TYPE_GET_DESC		0x02
#घोषणा GB_HID_TYPE_GET_REPORT_DESC	0x03
#घोषणा GB_HID_TYPE_PWR_ON		0x04
#घोषणा GB_HID_TYPE_PWR_OFF		0x05
#घोषणा GB_HID_TYPE_GET_REPORT		0x06
#घोषणा GB_HID_TYPE_SET_REPORT		0x07
#घोषणा GB_HID_TYPE_IRQ_EVENT		0x08

/* Report type */
#घोषणा GB_HID_INPUT_REPORT		0
#घोषणा GB_HID_OUTPUT_REPORT		1
#घोषणा GB_HID_FEATURE_REPORT		2

/* Dअगरferent request/response काष्ठाures */
/* HID get descriptor response */
काष्ठा gb_hid_desc_response अणु
	__u8				bLength;
	__le16				wReportDescLength;
	__le16				bcdHID;
	__le16				wProductID;
	__le16				wVenकरोrID;
	__u8				bCountryCode;
पूर्ण __packed;

/* HID get report request/response */
काष्ठा gb_hid_get_report_request अणु
	__u8				report_type;
	__u8				report_id;
पूर्ण __packed;

/* HID set report request */
काष्ठा gb_hid_set_report_request अणु
	__u8				report_type;
	__u8				report_id;
	__u8				report[];
पूर्ण __packed;

/* HID input report request, via पूर्णांकerrupt pipe */
काष्ठा gb_hid_input_report_request अणु
	__u8				report[0];
पूर्ण __packed;


/* I2C */

/* Greybus i2c request types */
#घोषणा GB_I2C_TYPE_FUNCTIONALITY	0x02
#घोषणा GB_I2C_TYPE_TRANSFER		0x05

/* functionality request has no payload */
काष्ठा gb_i2c_functionality_response अणु
	__le32	functionality;
पूर्ण __packed;

/*
 * Outgoing data immediately follows the op count and ops array.
 * The data क्रम each ग_लिखो (master -> slave) op in the array is sent
 * in order, with no (e.g. pad) bytes separating them.
 *
 * Short पढ़ोs cause the entire transfer request to fail So response
 * payload consists only of bytes पढ़ो, and the number of bytes is
 * exactly what was specअगरied in the corresponding op.  Like
 * outgoing data, the incoming data is in order and contiguous.
 */
काष्ठा gb_i2c_transfer_op अणु
	__le16	addr;
	__le16	flags;
	__le16	size;
पूर्ण __packed;

काष्ठा gb_i2c_transfer_request अणु
	__le16				op_count;
	काष्ठा gb_i2c_transfer_op	ops[];		/* op_count of these */
पूर्ण __packed;
काष्ठा gb_i2c_transfer_response अणु
	__u8				data[0];	/* inbound data */
पूर्ण __packed;


/* GPIO */

/* Greybus GPIO request types */
#घोषणा GB_GPIO_TYPE_LINE_COUNT		0x02
#घोषणा GB_GPIO_TYPE_ACTIVATE		0x03
#घोषणा GB_GPIO_TYPE_DEACTIVATE		0x04
#घोषणा GB_GPIO_TYPE_GET_सूचीECTION	0x05
#घोषणा GB_GPIO_TYPE_सूचीECTION_IN	0x06
#घोषणा GB_GPIO_TYPE_सूचीECTION_OUT	0x07
#घोषणा GB_GPIO_TYPE_GET_VALUE		0x08
#घोषणा GB_GPIO_TYPE_SET_VALUE		0x09
#घोषणा GB_GPIO_TYPE_SET_DEBOUNCE	0x0a
#घोषणा GB_GPIO_TYPE_IRQ_TYPE		0x0b
#घोषणा GB_GPIO_TYPE_IRQ_MASK		0x0c
#घोषणा GB_GPIO_TYPE_IRQ_UNMASK		0x0d
#घोषणा GB_GPIO_TYPE_IRQ_EVENT		0x0e

#घोषणा GB_GPIO_IRQ_TYPE_NONE		0x00
#घोषणा GB_GPIO_IRQ_TYPE_EDGE_RISING	0x01
#घोषणा GB_GPIO_IRQ_TYPE_EDGE_FALLING	0x02
#घोषणा GB_GPIO_IRQ_TYPE_EDGE_BOTH	0x03
#घोषणा GB_GPIO_IRQ_TYPE_LEVEL_HIGH	0x04
#घोषणा GB_GPIO_IRQ_TYPE_LEVEL_LOW	0x08

/* line count request has no payload */
काष्ठा gb_gpio_line_count_response अणु
	__u8	count;
पूर्ण __packed;

काष्ठा gb_gpio_activate_request अणु
	__u8	which;
पूर्ण __packed;
/* activate response has no payload */

काष्ठा gb_gpio_deactivate_request अणु
	__u8	which;
पूर्ण __packed;
/* deactivate response has no payload */

काष्ठा gb_gpio_get_direction_request अणु
	__u8	which;
पूर्ण __packed;
काष्ठा gb_gpio_get_direction_response अणु
	__u8	direction;
पूर्ण __packed;

काष्ठा gb_gpio_direction_in_request अणु
	__u8	which;
पूर्ण __packed;
/* direction in response has no payload */

काष्ठा gb_gpio_direction_out_request अणु
	__u8	which;
	__u8	value;
पूर्ण __packed;
/* direction out response has no payload */

काष्ठा gb_gpio_get_value_request अणु
	__u8	which;
पूर्ण __packed;
काष्ठा gb_gpio_get_value_response अणु
	__u8	value;
पूर्ण __packed;

काष्ठा gb_gpio_set_value_request अणु
	__u8	which;
	__u8	value;
पूर्ण __packed;
/* set value response has no payload */

काष्ठा gb_gpio_set_debounce_request अणु
	__u8	which;
	__le16	usec;
पूर्ण __packed;
/* debounce response has no payload */

काष्ठा gb_gpio_irq_type_request अणु
	__u8	which;
	__u8	type;
पूर्ण __packed;
/* irq type response has no payload */

काष्ठा gb_gpio_irq_mask_request अणु
	__u8	which;
पूर्ण __packed;
/* irq mask response has no payload */

काष्ठा gb_gpio_irq_unmask_request अणु
	__u8	which;
पूर्ण __packed;
/* irq unmask response has no payload */

/* irq event requests originate on another module and are handled on the AP */
काष्ठा gb_gpio_irq_event_request अणु
	__u8	which;
पूर्ण __packed;
/* irq event has no response */


/* PWM */

/* Greybus PWM operation types */
#घोषणा GB_PWM_TYPE_PWM_COUNT		0x02
#घोषणा GB_PWM_TYPE_ACTIVATE		0x03
#घोषणा GB_PWM_TYPE_DEACTIVATE		0x04
#घोषणा GB_PWM_TYPE_CONFIG		0x05
#घोषणा GB_PWM_TYPE_POLARITY		0x06
#घोषणा GB_PWM_TYPE_ENABLE		0x07
#घोषणा GB_PWM_TYPE_DISABLE		0x08

/* pwm count request has no payload */
काष्ठा gb_pwm_count_response अणु
	__u8	count;
पूर्ण __packed;

काष्ठा gb_pwm_activate_request अणु
	__u8	which;
पूर्ण __packed;

काष्ठा gb_pwm_deactivate_request अणु
	__u8	which;
पूर्ण __packed;

काष्ठा gb_pwm_config_request अणु
	__u8	which;
	__le32	duty;
	__le32	period;
पूर्ण __packed;

काष्ठा gb_pwm_polarity_request अणु
	__u8	which;
	__u8	polarity;
पूर्ण __packed;

काष्ठा gb_pwm_enable_request अणु
	__u8	which;
पूर्ण __packed;

काष्ठा gb_pwm_disable_request अणु
	__u8	which;
पूर्ण __packed;

/* SPI */

/* Should match up with modes in linux/spi/spi.h */
#घोषणा GB_SPI_MODE_CPHA		0x01		/* घड़ी phase */
#घोषणा GB_SPI_MODE_CPOL		0x02		/* घड़ी polarity */
#घोषणा GB_SPI_MODE_MODE_0		(0 | 0)		/* (original MicroWire) */
#घोषणा GB_SPI_MODE_MODE_1		(0 | GB_SPI_MODE_CPHA)
#घोषणा GB_SPI_MODE_MODE_2		(GB_SPI_MODE_CPOL | 0)
#घोषणा GB_SPI_MODE_MODE_3		(GB_SPI_MODE_CPOL | GB_SPI_MODE_CPHA)
#घोषणा GB_SPI_MODE_CS_HIGH		0x04		/* chipselect active high? */
#घोषणा GB_SPI_MODE_LSB_FIRST		0x08		/* per-word bits-on-wire */
#घोषणा GB_SPI_MODE_3WIRE		0x10		/* SI/SO संकेतs shared */
#घोषणा GB_SPI_MODE_LOOP		0x20		/* loopback mode */
#घोषणा GB_SPI_MODE_NO_CS		0x40		/* 1 dev/bus, no chipselect */
#घोषणा GB_SPI_MODE_READY		0x80		/* slave pulls low to छोड़ो */

/* Should match up with flags in linux/spi/spi.h */
#घोषणा GB_SPI_FLAG_HALF_DUPLEX		BIT(0)		/* can't करो full duplex */
#घोषणा GB_SPI_FLAG_NO_RX		BIT(1)		/* can't करो buffer पढ़ो */
#घोषणा GB_SPI_FLAG_NO_TX		BIT(2)		/* can't करो buffer ग_लिखो */

/* Greybus spi operation types */
#घोषणा GB_SPI_TYPE_MASTER_CONFIG	0x02
#घोषणा GB_SPI_TYPE_DEVICE_CONFIG	0x03
#घोषणा GB_SPI_TYPE_TRANSFER		0x04

/* mode request has no payload */
काष्ठा gb_spi_master_config_response अणु
	__le32	bits_per_word_mask;
	__le32	min_speed_hz;
	__le32	max_speed_hz;
	__le16	mode;
	__le16	flags;
	__u8	num_chipselect;
पूर्ण __packed;

काष्ठा gb_spi_device_config_request अणु
	__u8	chip_select;
पूर्ण __packed;

काष्ठा gb_spi_device_config_response अणु
	__le16	mode;
	__u8	bits_per_word;
	__le32	max_speed_hz;
	__u8	device_type;
#घोषणा GB_SPI_SPI_DEV		0x00
#घोषणा GB_SPI_SPI_NOR		0x01
#घोषणा GB_SPI_SPI_MODALIAS	0x02
	__u8	name[32];
पूर्ण __packed;

/**
 * काष्ठा gb_spi_transfer - a पढ़ो/ग_लिखो buffer pair
 * @speed_hz: Select a speed other than the device शेष क्रम this transfer. If
 *	0 the शेष (from @spi_device) is used.
 * @len: size of rx and tx buffers (in bytes)
 * @delay_usecs: microseconds to delay after this transfer beक्रमe (optionally)
 * 	changing the chipselect status, then starting the next transfer or
 * 	completing this spi_message.
 * @cs_change: affects chipselect after this transfer completes
 * @bits_per_word: select a bits_per_word other than the device शेष क्रम this
 *	transfer. If 0 the शेष (from @spi_device) is used.
 */
काष्ठा gb_spi_transfer अणु
	__le32		speed_hz;
	__le32		len;
	__le16		delay_usecs;
	__u8		cs_change;
	__u8		bits_per_word;
	__u8		xfer_flags;
#घोषणा GB_SPI_XFER_READ	0x01
#घोषणा GB_SPI_XFER_WRITE	0x02
#घोषणा GB_SPI_XFER_INPROGRESS	0x04
पूर्ण __packed;

काष्ठा gb_spi_transfer_request अणु
	__u8			chip_select;	/* of the spi device */
	__u8			mode;		/* of the spi device */
	__le16			count;
	काष्ठा gb_spi_transfer	transfers[];	/* count of these */
पूर्ण __packed;

काष्ठा gb_spi_transfer_response अणु
	__u8			data[0];	/* inbound data */
पूर्ण __packed;

/* Version of the Greybus SVC protocol we support */
#घोषणा GB_SVC_VERSION_MAJOR		0x00
#घोषणा GB_SVC_VERSION_MINOR		0x01

/* Greybus SVC request types */
#घोषणा GB_SVC_TYPE_PROTOCOL_VERSION		0x01
#घोषणा GB_SVC_TYPE_SVC_HELLO			0x02
#घोषणा GB_SVC_TYPE_INTF_DEVICE_ID		0x03
#घोषणा GB_SVC_TYPE_INTF_RESET			0x06
#घोषणा GB_SVC_TYPE_CONN_CREATE			0x07
#घोषणा GB_SVC_TYPE_CONN_DESTROY		0x08
#घोषणा GB_SVC_TYPE_DME_PEER_GET		0x09
#घोषणा GB_SVC_TYPE_DME_PEER_SET		0x0a
#घोषणा GB_SVC_TYPE_ROUTE_CREATE		0x0b
#घोषणा GB_SVC_TYPE_ROUTE_DESTROY		0x0c
#घोषणा GB_SVC_TYPE_TIMESYNC_ENABLE		0x0d
#घोषणा GB_SVC_TYPE_TIMESYNC_DISABLE		0x0e
#घोषणा GB_SVC_TYPE_TIMESYNC_AUTHORITATIVE	0x0f
#घोषणा GB_SVC_TYPE_INTF_SET_PWRM		0x10
#घोषणा GB_SVC_TYPE_INTF_EJECT			0x11
#घोषणा GB_SVC_TYPE_PING			0x13
#घोषणा GB_SVC_TYPE_PWRMON_RAIL_COUNT_GET	0x14
#घोषणा GB_SVC_TYPE_PWRMON_RAIL_NAMES_GET	0x15
#घोषणा GB_SVC_TYPE_PWRMON_SAMPLE_GET		0x16
#घोषणा GB_SVC_TYPE_PWRMON_INTF_SAMPLE_GET	0x17
#घोषणा GB_SVC_TYPE_TIMESYNC_WAKE_PINS_ACQUIRE	0x18
#घोषणा GB_SVC_TYPE_TIMESYNC_WAKE_PINS_RELEASE	0x19
#घोषणा GB_SVC_TYPE_TIMESYNC_PING		0x1a
#घोषणा GB_SVC_TYPE_MODULE_INSERTED		0x1f
#घोषणा GB_SVC_TYPE_MODULE_REMOVED		0x20
#घोषणा GB_SVC_TYPE_INTF_VSYS_ENABLE		0x21
#घोषणा GB_SVC_TYPE_INTF_VSYS_DISABLE		0x22
#घोषणा GB_SVC_TYPE_INTF_REFCLK_ENABLE		0x23
#घोषणा GB_SVC_TYPE_INTF_REFCLK_DISABLE		0x24
#घोषणा GB_SVC_TYPE_INTF_UNIPRO_ENABLE		0x25
#घोषणा GB_SVC_TYPE_INTF_UNIPRO_DISABLE		0x26
#घोषणा GB_SVC_TYPE_INTF_ACTIVATE		0x27
#घोषणा GB_SVC_TYPE_INTF_RESUME			0x28
#घोषणा GB_SVC_TYPE_INTF_MAILBOX_EVENT		0x29
#घोषणा GB_SVC_TYPE_INTF_OOPS			0x2a

/* Greybus SVC protocol status values */
#घोषणा GB_SVC_OP_SUCCESS			0x00
#घोषणा GB_SVC_OP_UNKNOWN_ERROR			0x01
#घोषणा GB_SVC_INTF_NOT_DETECTED		0x02
#घोषणा GB_SVC_INTF_NO_UPRO_LINK		0x03
#घोषणा GB_SVC_INTF_UPRO_NOT_DOWN		0x04
#घोषणा GB_SVC_INTF_UPRO_NOT_HIBERNATED		0x05
#घोषणा GB_SVC_INTF_NO_V_SYS			0x06
#घोषणा GB_SVC_INTF_V_CHG			0x07
#घोषणा GB_SVC_INTF_WAKE_BUSY			0x08
#घोषणा GB_SVC_INTF_NO_REFCLK			0x09
#घोषणा GB_SVC_INTF_RELEASING			0x0a
#घोषणा GB_SVC_INTF_NO_ORDER			0x0b
#घोषणा GB_SVC_INTF_MBOX_SET			0x0c
#घोषणा GB_SVC_INTF_BAD_MBOX			0x0d
#घोषणा GB_SVC_INTF_OP_TIMEOUT			0x0e
#घोषणा GB_SVC_PWRMON_OP_NOT_PRESENT		0x0f

काष्ठा gb_svc_version_request अणु
	__u8	major;
	__u8	minor;
पूर्ण __packed;

काष्ठा gb_svc_version_response अणु
	__u8	major;
	__u8	minor;
पूर्ण __packed;

/* SVC protocol hello request */
काष्ठा gb_svc_hello_request अणु
	__le16			enकरो_id;
	__u8			पूर्णांकerface_id;
पूर्ण __packed;
/* hello response has no payload */

काष्ठा gb_svc_पूर्णांकf_device_id_request अणु
	__u8	पूर्णांकf_id;
	__u8	device_id;
पूर्ण __packed;
/* device id response has no payload */

काष्ठा gb_svc_पूर्णांकf_reset_request अणु
	__u8	पूर्णांकf_id;
पूर्ण __packed;
/* पूर्णांकerface reset response has no payload */

काष्ठा gb_svc_पूर्णांकf_eject_request अणु
	__u8	पूर्णांकf_id;
पूर्ण __packed;
/* पूर्णांकerface eject response has no payload */

काष्ठा gb_svc_conn_create_request अणु
	__u8	पूर्णांकf1_id;
	__le16	cport1_id;
	__u8	पूर्णांकf2_id;
	__le16	cport2_id;
	__u8	tc;
	__u8	flags;
पूर्ण __packed;
/* connection create response has no payload */

काष्ठा gb_svc_conn_destroy_request अणु
	__u8	पूर्णांकf1_id;
	__le16	cport1_id;
	__u8	पूर्णांकf2_id;
	__le16	cport2_id;
पूर्ण __packed;
/* connection destroy response has no payload */

काष्ठा gb_svc_dme_peer_get_request अणु
	__u8	पूर्णांकf_id;
	__le16	attr;
	__le16	selector;
पूर्ण __packed;

काष्ठा gb_svc_dme_peer_get_response अणु
	__le16	result_code;
	__le32	attr_value;
पूर्ण __packed;

काष्ठा gb_svc_dme_peer_set_request अणु
	__u8	पूर्णांकf_id;
	__le16	attr;
	__le16	selector;
	__le32	value;
पूर्ण __packed;

काष्ठा gb_svc_dme_peer_set_response अणु
	__le16	result_code;
पूर्ण __packed;

/* Greybus init-status values, currently retrieved using DME peer माला_लो. */
#घोषणा GB_INIT_SPI_BOOT_STARTED			0x02
#घोषणा GB_INIT_TRUSTED_SPI_BOOT_FINISHED		0x03
#घोषणा GB_INIT_UNTRUSTED_SPI_BOOT_FINISHED		0x04
#घोषणा GB_INIT_BOOTROM_UNIPRO_BOOT_STARTED		0x06
#घोषणा GB_INIT_BOOTROM_FALLBACK_UNIPRO_BOOT_STARTED	0x09
#घोषणा GB_INIT_S2_LOADER_BOOT_STARTED			0x0D

काष्ठा gb_svc_route_create_request अणु
	__u8	पूर्णांकf1_id;
	__u8	dev1_id;
	__u8	पूर्णांकf2_id;
	__u8	dev2_id;
पूर्ण __packed;
/* route create response has no payload */

काष्ठा gb_svc_route_destroy_request अणु
	__u8	पूर्णांकf1_id;
	__u8	पूर्णांकf2_id;
पूर्ण __packed;
/* route destroy response has no payload */

/* used क्रम svc_पूर्णांकf_vsys_अणुenable,disableपूर्ण */
काष्ठा gb_svc_पूर्णांकf_vsys_request अणु
	__u8	पूर्णांकf_id;
पूर्ण __packed;

काष्ठा gb_svc_पूर्णांकf_vsys_response अणु
	__u8	result_code;
#घोषणा GB_SVC_INTF_VSYS_OK				0x00
	/* 0x01 is reserved */
#घोषणा GB_SVC_INTF_VSYS_FAIL				0x02
पूर्ण __packed;

/* used क्रम svc_पूर्णांकf_refclk_अणुenable,disableपूर्ण */
काष्ठा gb_svc_पूर्णांकf_refclk_request अणु
	__u8	पूर्णांकf_id;
पूर्ण __packed;

काष्ठा gb_svc_पूर्णांकf_refclk_response अणु
	__u8	result_code;
#घोषणा GB_SVC_INTF_REFCLK_OK				0x00
	/* 0x01 is reserved */
#घोषणा GB_SVC_INTF_REFCLK_FAIL				0x02
पूर्ण __packed;

/* used क्रम svc_पूर्णांकf_unipro_अणुenable,disableपूर्ण */
काष्ठा gb_svc_पूर्णांकf_unipro_request अणु
	__u8	पूर्णांकf_id;
पूर्ण __packed;

काष्ठा gb_svc_पूर्णांकf_unipro_response अणु
	__u8	result_code;
#घोषणा GB_SVC_INTF_UNIPRO_OK				0x00
	/* 0x01 is reserved */
#घोषणा GB_SVC_INTF_UNIPRO_FAIL				0x02
#घोषणा GB_SVC_INTF_UNIPRO_NOT_OFF			0x03
पूर्ण __packed;

#घोषणा GB_SVC_UNIPRO_FAST_MODE			0x01
#घोषणा GB_SVC_UNIPRO_SLOW_MODE			0x02
#घोषणा GB_SVC_UNIPRO_FAST_AUTO_MODE		0x04
#घोषणा GB_SVC_UNIPRO_SLOW_AUTO_MODE		0x05
#घोषणा GB_SVC_UNIPRO_MODE_UNCHANGED		0x07
#घोषणा GB_SVC_UNIPRO_HIBERNATE_MODE		0x11
#घोषणा GB_SVC_UNIPRO_OFF_MODE			0x12

#घोषणा GB_SVC_SMALL_AMPLITUDE          0x01
#घोषणा GB_SVC_LARGE_AMPLITUDE          0x02

#घोषणा GB_SVC_NO_DE_EMPHASIS           0x00
#घोषणा GB_SVC_SMALL_DE_EMPHASIS        0x01
#घोषणा GB_SVC_LARGE_DE_EMPHASIS        0x02

#घोषणा GB_SVC_PWRM_RXTERMINATION		0x01
#घोषणा GB_SVC_PWRM_TXTERMINATION		0x02
#घोषणा GB_SVC_PWRM_LINE_RESET			0x04
#घोषणा GB_SVC_PWRM_SCRAMBLING			0x20

#घोषणा GB_SVC_PWRM_QUIRK_HSSER			0x00000001

#घोषणा GB_SVC_UNIPRO_HS_SERIES_A		0x01
#घोषणा GB_SVC_UNIPRO_HS_SERIES_B		0x02

#घोषणा GB_SVC_SETPWRM_PWR_OK           0x00
#घोषणा GB_SVC_SETPWRM_PWR_LOCAL        0x01
#घोषणा GB_SVC_SETPWRM_PWR_REMOTE       0x02
#घोषणा GB_SVC_SETPWRM_PWR_BUSY         0x03
#घोषणा GB_SVC_SETPWRM_PWR_ERROR_CAP    0x04
#घोषणा GB_SVC_SETPWRM_PWR_FATAL_ERROR  0x05

काष्ठा gb_svc_l2_समयr_cfg अणु
	__le16 tsb_fc0_protection_समयout;
	__le16 tsb_tc0_replay_समयout;
	__le16 tsb_afc0_req_समयout;
	__le16 tsb_fc1_protection_समयout;
	__le16 tsb_tc1_replay_समयout;
	__le16 tsb_afc1_req_समयout;
	__le16 reserved_क्रम_tc2[3];
	__le16 reserved_क्रम_tc3[3];
पूर्ण __packed;

काष्ठा gb_svc_पूर्णांकf_set_pwrm_request अणु
	__u8	पूर्णांकf_id;
	__u8	hs_series;
	__u8	tx_mode;
	__u8	tx_gear;
	__u8	tx_nlanes;
	__u8	tx_amplitude;
	__u8	tx_hs_equalizer;
	__u8	rx_mode;
	__u8	rx_gear;
	__u8	rx_nlanes;
	__u8	flags;
	__le32	quirks;
	काष्ठा gb_svc_l2_समयr_cfg local_l2समयrdata, remote_l2समयrdata;
पूर्ण __packed;

काष्ठा gb_svc_पूर्णांकf_set_pwrm_response अणु
	__u8	result_code;
पूर्ण __packed;

काष्ठा gb_svc_key_event_request अणु
	__le16  key_code;
#घोषणा GB_KEYCODE_ARA         0x00

	__u8    key_event;
#घोषणा GB_SVC_KEY_RELEASED    0x00
#घोषणा GB_SVC_KEY_PRESSED     0x01
पूर्ण __packed;

#घोषणा GB_SVC_PWRMON_MAX_RAIL_COUNT		254

काष्ठा gb_svc_pwrmon_rail_count_get_response अणु
	__u8	rail_count;
पूर्ण __packed;

#घोषणा GB_SVC_PWRMON_RAIL_NAME_बफ_मानE		32

काष्ठा gb_svc_pwrmon_rail_names_get_response अणु
	__u8	status;
	__u8	name[][GB_SVC_PWRMON_RAIL_NAME_बफ_मानE];
पूर्ण __packed;

#घोषणा GB_SVC_PWRMON_TYPE_CURR			0x01
#घोषणा GB_SVC_PWRMON_TYPE_VOL			0x02
#घोषणा GB_SVC_PWRMON_TYPE_PWR			0x03

#घोषणा GB_SVC_PWRMON_GET_SAMPLE_OK		0x00
#घोषणा GB_SVC_PWRMON_GET_SAMPLE_INVAL		0x01
#घोषणा GB_SVC_PWRMON_GET_SAMPLE_NOSUPP		0x02
#घोषणा GB_SVC_PWRMON_GET_SAMPLE_HWERR		0x03

काष्ठा gb_svc_pwrmon_sample_get_request अणु
	__u8	rail_id;
	__u8	measurement_type;
पूर्ण __packed;

काष्ठा gb_svc_pwrmon_sample_get_response अणु
	__u8	result;
	__le32	measurement;
पूर्ण __packed;

काष्ठा gb_svc_pwrmon_पूर्णांकf_sample_get_request अणु
	__u8	पूर्णांकf_id;
	__u8	measurement_type;
पूर्ण __packed;

काष्ठा gb_svc_pwrmon_पूर्णांकf_sample_get_response अणु
	__u8	result;
	__le32	measurement;
पूर्ण __packed;

#घोषणा GB_SVC_MODULE_INSERTED_FLAG_NO_PRIMARY	0x0001

काष्ठा gb_svc_module_inserted_request अणु
	__u8	primary_पूर्णांकf_id;
	__u8	पूर्णांकf_count;
	__le16	flags;
पूर्ण __packed;
/* module_inserted response has no payload */

काष्ठा gb_svc_module_हटाओd_request अणु
	__u8	primary_पूर्णांकf_id;
पूर्ण __packed;
/* module_हटाओd response has no payload */

काष्ठा gb_svc_पूर्णांकf_activate_request अणु
	__u8	पूर्णांकf_id;
पूर्ण __packed;

#घोषणा GB_SVC_INTF_TYPE_UNKNOWN		0x00
#घोषणा GB_SVC_INTF_TYPE_DUMMY			0x01
#घोषणा GB_SVC_INTF_TYPE_UNIPRO			0x02
#घोषणा GB_SVC_INTF_TYPE_GREYBUS		0x03

काष्ठा gb_svc_पूर्णांकf_activate_response अणु
	__u8	status;
	__u8	पूर्णांकf_type;
पूर्ण __packed;

काष्ठा gb_svc_पूर्णांकf_resume_request अणु
	__u8	पूर्णांकf_id;
पूर्ण __packed;

काष्ठा gb_svc_पूर्णांकf_resume_response अणु
	__u8	status;
पूर्ण __packed;

#घोषणा GB_SVC_INTF_MAILBOX_NONE		0x00
#घोषणा GB_SVC_INTF_MAILBOX_AP			0x01
#घोषणा GB_SVC_INTF_MAILBOX_GREYBUS		0x02

काष्ठा gb_svc_पूर्णांकf_mailbox_event_request अणु
	__u8	पूर्णांकf_id;
	__le16	result_code;
	__le32	mailbox;
पूर्ण __packed;
/* पूर्णांकf_mailbox_event response has no payload */

काष्ठा gb_svc_पूर्णांकf_oops_request अणु
	__u8	पूर्णांकf_id;
	__u8	reason;
पूर्ण __packed;
/* पूर्णांकf_oops response has no payload */


/* RAW */

/* Greybus raw request types */
#घोषणा	GB_RAW_TYPE_SEND			0x02

काष्ठा gb_raw_send_request अणु
	__le32	len;
	__u8	data[];
पूर्ण __packed;


/* UART */

/* Greybus UART operation types */
#घोषणा GB_UART_TYPE_SEND_DATA			0x02
#घोषणा GB_UART_TYPE_RECEIVE_DATA		0x03	/* Unsolicited data */
#घोषणा GB_UART_TYPE_SET_LINE_CODING		0x04
#घोषणा GB_UART_TYPE_SET_CONTROL_LINE_STATE	0x05
#घोषणा GB_UART_TYPE_SEND_BREAK			0x06
#घोषणा GB_UART_TYPE_SERIAL_STATE		0x07	/* Unsolicited data */
#घोषणा GB_UART_TYPE_RECEIVE_CREDITS		0x08
#घोषणा GB_UART_TYPE_FLUSH_FIFOS		0x09

/* Represents data from AP -> Module */
काष्ठा gb_uart_send_data_request अणु
	__le16	size;
	__u8	data[];
पूर्ण __packed;

/* recv-data-request flags */
#घोषणा GB_UART_RECV_FLAG_FRAMING		0x01	/* Framing error */
#घोषणा GB_UART_RECV_FLAG_PARITY		0x02	/* Parity error */
#घोषणा GB_UART_RECV_FLAG_OVERRUN		0x04	/* Overrun error */
#घोषणा GB_UART_RECV_FLAG_BREAK			0x08	/* Break */

/* Represents data from Module -> AP */
काष्ठा gb_uart_recv_data_request अणु
	__le16	size;
	__u8	flags;
	__u8	data[];
पूर्ण __packed;

काष्ठा gb_uart_receive_credits_request अणु
	__le16  count;
पूर्ण __packed;

काष्ठा gb_uart_set_line_coding_request अणु
	__le32	rate;
	__u8	क्रमmat;
#घोषणा GB_SERIAL_1_STOP_BITS			0
#घोषणा GB_SERIAL_1_5_STOP_BITS			1
#घोषणा GB_SERIAL_2_STOP_BITS			2

	__u8	parity;
#घोषणा GB_SERIAL_NO_PARITY			0
#घोषणा GB_SERIAL_ODD_PARITY			1
#घोषणा GB_SERIAL_EVEN_PARITY			2
#घोषणा GB_SERIAL_MARK_PARITY			3
#घोषणा GB_SERIAL_SPACE_PARITY			4

	__u8	data_bits;

	__u8	flow_control;
#घोषणा GB_SERIAL_AUTO_RTSCTS_EN		0x1
पूर्ण __packed;

/* output control lines */
#घोषणा GB_UART_CTRL_DTR			0x01
#घोषणा GB_UART_CTRL_RTS			0x02

काष्ठा gb_uart_set_control_line_state_request अणु
	__u8	control;
पूर्ण __packed;

काष्ठा gb_uart_set_अवरोध_request अणु
	__u8	state;
पूर्ण __packed;

/* input control lines and line errors */
#घोषणा GB_UART_CTRL_DCD			0x01
#घोषणा GB_UART_CTRL_DSR			0x02
#घोषणा GB_UART_CTRL_RI				0x04

काष्ठा gb_uart_serial_state_request अणु
	__u8	control;
पूर्ण __packed;

काष्ठा gb_uart_serial_flush_request अणु
	__u8    flags;
#घोषणा GB_SERIAL_FLAG_FLUSH_TRANSMITTER	0x01
#घोषणा GB_SERIAL_FLAG_FLUSH_RECEIVER		0x02
पूर्ण __packed;

/* Loopback */

/* Greybus loopback request types */
#घोषणा GB_LOOPBACK_TYPE_PING			0x02
#घोषणा GB_LOOPBACK_TYPE_TRANSFER		0x03
#घोषणा GB_LOOPBACK_TYPE_SINK			0x04

/*
 * Loopback request/response header क्रमmat should be identical
 * to simplअगरy bandwidth and data movement analysis.
 */
काष्ठा gb_loopback_transfer_request अणु
	__le32	len;
	__le32  reserved0;
	__le32  reserved1;
	__u8	data[];
पूर्ण __packed;

काष्ठा gb_loopback_transfer_response अणु
	__le32	len;
	__le32	reserved0;
	__le32	reserved1;
	__u8	data[];
पूर्ण __packed;

/* SDIO */
/* Greybus SDIO operation types */
#घोषणा GB_SDIO_TYPE_GET_CAPABILITIES		0x02
#घोषणा GB_SDIO_TYPE_SET_IOS			0x03
#घोषणा GB_SDIO_TYPE_COMMAND			0x04
#घोषणा GB_SDIO_TYPE_TRANSFER			0x05
#घोषणा GB_SDIO_TYPE_EVENT			0x06

/* get caps response: request has no payload */
काष्ठा gb_sdio_get_caps_response अणु
	__le32	caps;
#घोषणा GB_SDIO_CAP_NONREMOVABLE	0x00000001
#घोषणा GB_SDIO_CAP_4_BIT_DATA		0x00000002
#घोषणा GB_SDIO_CAP_8_BIT_DATA		0x00000004
#घोषणा GB_SDIO_CAP_MMC_HS		0x00000008
#घोषणा GB_SDIO_CAP_SD_HS		0x00000010
#घोषणा GB_SDIO_CAP_ERASE		0x00000020
#घोषणा GB_SDIO_CAP_1_2V_DDR		0x00000040
#घोषणा GB_SDIO_CAP_1_8V_DDR		0x00000080
#घोषणा GB_SDIO_CAP_POWER_OFF_CARD	0x00000100
#घोषणा GB_SDIO_CAP_UHS_SDR12		0x00000200
#घोषणा GB_SDIO_CAP_UHS_SDR25		0x00000400
#घोषणा GB_SDIO_CAP_UHS_SDR50		0x00000800
#घोषणा GB_SDIO_CAP_UHS_SDR104		0x00001000
#घोषणा GB_SDIO_CAP_UHS_DDR50		0x00002000
#घोषणा GB_SDIO_CAP_DRIVER_TYPE_A	0x00004000
#घोषणा GB_SDIO_CAP_DRIVER_TYPE_C	0x00008000
#घोषणा GB_SDIO_CAP_DRIVER_TYPE_D	0x00010000
#घोषणा GB_SDIO_CAP_HS200_1_2V		0x00020000
#घोषणा GB_SDIO_CAP_HS200_1_8V		0x00040000
#घोषणा GB_SDIO_CAP_HS400_1_2V		0x00080000
#घोषणा GB_SDIO_CAP_HS400_1_8V		0x00100000

	/* see possible values below at vdd */
	__le32 ocr;
	__le32 f_min;
	__le32 f_max;
	__le16 max_blk_count;
	__le16 max_blk_size;
पूर्ण __packed;

/* set ios request: response has no payload */
काष्ठा gb_sdio_set_ios_request अणु
	__le32	घड़ी;
	__le32	vdd;
#घोषणा GB_SDIO_VDD_165_195	0x00000001
#घोषणा GB_SDIO_VDD_20_21	0x00000002
#घोषणा GB_SDIO_VDD_21_22	0x00000004
#घोषणा GB_SDIO_VDD_22_23	0x00000008
#घोषणा GB_SDIO_VDD_23_24	0x00000010
#घोषणा GB_SDIO_VDD_24_25	0x00000020
#घोषणा GB_SDIO_VDD_25_26	0x00000040
#घोषणा GB_SDIO_VDD_26_27	0x00000080
#घोषणा GB_SDIO_VDD_27_28	0x00000100
#घोषणा GB_SDIO_VDD_28_29	0x00000200
#घोषणा GB_SDIO_VDD_29_30	0x00000400
#घोषणा GB_SDIO_VDD_30_31	0x00000800
#घोषणा GB_SDIO_VDD_31_32	0x00001000
#घोषणा GB_SDIO_VDD_32_33	0x00002000
#घोषणा GB_SDIO_VDD_33_34	0x00004000
#घोषणा GB_SDIO_VDD_34_35	0x00008000
#घोषणा GB_SDIO_VDD_35_36	0x00010000

	__u8	bus_mode;
#घोषणा GB_SDIO_BUSMODE_OPENDRAIN	0x00
#घोषणा GB_SDIO_BUSMODE_PUSHPULL	0x01

	__u8	घातer_mode;
#घोषणा GB_SDIO_POWER_OFF	0x00
#घोषणा GB_SDIO_POWER_UP	0x01
#घोषणा GB_SDIO_POWER_ON	0x02
#घोषणा GB_SDIO_POWER_UNDEFINED	0x03

	__u8	bus_width;
#घोषणा GB_SDIO_BUS_WIDTH_1	0x00
#घोषणा GB_SDIO_BUS_WIDTH_4	0x02
#घोषणा GB_SDIO_BUS_WIDTH_8	0x03

	__u8	timing;
#घोषणा GB_SDIO_TIMING_LEGACY		0x00
#घोषणा GB_SDIO_TIMING_MMC_HS		0x01
#घोषणा GB_SDIO_TIMING_SD_HS		0x02
#घोषणा GB_SDIO_TIMING_UHS_SDR12	0x03
#घोषणा GB_SDIO_TIMING_UHS_SDR25	0x04
#घोषणा GB_SDIO_TIMING_UHS_SDR50	0x05
#घोषणा GB_SDIO_TIMING_UHS_SDR104	0x06
#घोषणा GB_SDIO_TIMING_UHS_DDR50	0x07
#घोषणा GB_SDIO_TIMING_MMC_DDR52	0x08
#घोषणा GB_SDIO_TIMING_MMC_HS200	0x09
#घोषणा GB_SDIO_TIMING_MMC_HS400	0x0A

	__u8	संकेत_voltage;
#घोषणा GB_SDIO_SIGNAL_VOLTAGE_330	0x00
#घोषणा GB_SDIO_SIGNAL_VOLTAGE_180	0x01
#घोषणा GB_SDIO_SIGNAL_VOLTAGE_120	0x02

	__u8	drv_type;
#घोषणा GB_SDIO_SET_DRIVER_TYPE_B	0x00
#घोषणा GB_SDIO_SET_DRIVER_TYPE_A	0x01
#घोषणा GB_SDIO_SET_DRIVER_TYPE_C	0x02
#घोषणा GB_SDIO_SET_DRIVER_TYPE_D	0x03
पूर्ण __packed;

/* command request */
काष्ठा gb_sdio_command_request अणु
	__u8	cmd;
	__u8	cmd_flags;
#घोषणा GB_SDIO_RSP_NONE		0x00
#घोषणा GB_SDIO_RSP_PRESENT		0x01
#घोषणा GB_SDIO_RSP_136			0x02
#घोषणा GB_SDIO_RSP_CRC			0x04
#घोषणा GB_SDIO_RSP_BUSY		0x08
#घोषणा GB_SDIO_RSP_OPCODE		0x10

	__u8	cmd_type;
#घोषणा GB_SDIO_CMD_AC		0x00
#घोषणा GB_SDIO_CMD_ADTC	0x01
#घोषणा GB_SDIO_CMD_BC		0x02
#घोषणा GB_SDIO_CMD_BCR		0x03

	__le32	cmd_arg;
	__le16	data_blocks;
	__le16	data_blksz;
पूर्ण __packed;

काष्ठा gb_sdio_command_response अणु
	__le32	resp[4];
पूर्ण __packed;

/* transfer request */
काष्ठा gb_sdio_transfer_request अणु
	__u8	data_flags;
#घोषणा GB_SDIO_DATA_WRITE	0x01
#घोषणा GB_SDIO_DATA_READ	0x02
#घोषणा GB_SDIO_DATA_STREAM	0x04

	__le16	data_blocks;
	__le16	data_blksz;
	__u8	data[];
पूर्ण __packed;

काष्ठा gb_sdio_transfer_response अणु
	__le16	data_blocks;
	__le16	data_blksz;
	__u8	data[];
पूर्ण __packed;

/* event request: generated by module and is defined as unidirectional */
काष्ठा gb_sdio_event_request अणु
	__u8	event;
#घोषणा GB_SDIO_CARD_INSERTED	0x01
#घोषणा GB_SDIO_CARD_REMOVED	0x02
#घोषणा GB_SDIO_WP		0x04
पूर्ण __packed;

/* Camera */

/* Greybus Camera request types */
#घोषणा GB_CAMERA_TYPE_CAPABILITIES		0x02
#घोषणा GB_CAMERA_TYPE_CONFIGURE_STREAMS	0x03
#घोषणा GB_CAMERA_TYPE_CAPTURE			0x04
#घोषणा GB_CAMERA_TYPE_FLUSH			0x05
#घोषणा GB_CAMERA_TYPE_METADATA			0x06

#घोषणा GB_CAMERA_MAX_STREAMS			4
#घोषणा GB_CAMERA_MAX_SETTINGS_SIZE		8192

/* Greybus Camera Configure Streams request payload */
काष्ठा gb_camera_stream_config_request अणु
	__le16 width;
	__le16 height;
	__le16 क्रमmat;
	__le16 padding;
पूर्ण __packed;

काष्ठा gb_camera_configure_streams_request अणु
	__u8 num_streams;
	__u8 flags;
#घोषणा GB_CAMERA_CONFIGURE_STREAMS_TEST_ONLY	0x01
	__le16 padding;
	काष्ठा gb_camera_stream_config_request config[];
पूर्ण __packed;

/* Greybus Camera Configure Streams response payload */
काष्ठा gb_camera_stream_config_response अणु
	__le16 width;
	__le16 height;
	__le16 क्रमmat;
	__u8 भव_channel;
	__u8 data_type[2];
	__le16 max_pkt_size;
	__u8 padding;
	__le32 max_size;
पूर्ण __packed;

काष्ठा gb_camera_configure_streams_response अणु
	__u8 num_streams;
#घोषणा GB_CAMERA_CONFIGURE_STREAMS_ADJUSTED	0x01
	__u8 flags;
	__u8 padding[2];
	__le32 data_rate;
	काष्ठा gb_camera_stream_config_response config[];
पूर्ण;

/* Greybus Camera Capture request payload - response has no payload */
काष्ठा gb_camera_capture_request अणु
	__le32 request_id;
	__u8 streams;
	__u8 padding;
	__le16 num_frames;
	__u8 settings[];
पूर्ण __packed;

/* Greybus Camera Flush response payload - request has no payload */
काष्ठा gb_camera_flush_response अणु
	__le32 request_id;
पूर्ण __packed;

/* Greybus Camera Metadata request payload - operation has no response */
काष्ठा gb_camera_metadata_request अणु
	__le32 request_id;
	__le16 frame_number;
	__u8 stream;
	__u8 padding;
	__u8 metadata[];
पूर्ण __packed;

/* Lights */

/* Greybus Lights request types */
#घोषणा GB_LIGHTS_TYPE_GET_LIGHTS		0x02
#घोषणा GB_LIGHTS_TYPE_GET_LIGHT_CONFIG		0x03
#घोषणा GB_LIGHTS_TYPE_GET_CHANNEL_CONFIG	0x04
#घोषणा GB_LIGHTS_TYPE_GET_CHANNEL_FLASH_CONFIG	0x05
#घोषणा GB_LIGHTS_TYPE_SET_BRIGHTNESS		0x06
#घोषणा GB_LIGHTS_TYPE_SET_BLINK		0x07
#घोषणा GB_LIGHTS_TYPE_SET_COLOR		0x08
#घोषणा GB_LIGHTS_TYPE_SET_FADE			0x09
#घोषणा GB_LIGHTS_TYPE_EVENT			0x0A
#घोषणा GB_LIGHTS_TYPE_SET_FLASH_INTENSITY	0x0B
#घोषणा GB_LIGHTS_TYPE_SET_FLASH_STROBE		0x0C
#घोषणा GB_LIGHTS_TYPE_SET_FLASH_TIMEOUT	0x0D
#घोषणा GB_LIGHTS_TYPE_GET_FLASH_FAULT		0x0E

/* Greybus Light modes */

/*
 * अगर you add any specअगरic mode below, update also the
 * GB_CHANNEL_MODE_DEFINED_RANGE value accordingly
 */
#घोषणा GB_CHANNEL_MODE_NONE		0x00000000
#घोषणा GB_CHANNEL_MODE_BATTERY		0x00000001
#घोषणा GB_CHANNEL_MODE_POWER		0x00000002
#घोषणा GB_CHANNEL_MODE_WIRELESS	0x00000004
#घोषणा GB_CHANNEL_MODE_BLUETOOTH	0x00000008
#घोषणा GB_CHANNEL_MODE_KEYBOARD	0x00000010
#घोषणा GB_CHANNEL_MODE_BUTTONS		0x00000020
#घोषणा GB_CHANNEL_MODE_NOTIFICATION	0x00000040
#घोषणा GB_CHANNEL_MODE_ATTENTION	0x00000080
#घोषणा GB_CHANNEL_MODE_FLASH		0x00000100
#घोषणा GB_CHANNEL_MODE_TORCH		0x00000200
#घोषणा GB_CHANNEL_MODE_INDICATOR	0x00000400

/* Lights Mode valid bit values */
#घोषणा GB_CHANNEL_MODE_DEFINED_RANGE	0x000004FF
#घोषणा GB_CHANNEL_MODE_VENDOR_RANGE	0x00F00000

/* Greybus Light Channels Flags */
#घोषणा GB_LIGHT_CHANNEL_MULTICOLOR	0x00000001
#घोषणा GB_LIGHT_CHANNEL_FADER		0x00000002
#घोषणा GB_LIGHT_CHANNEL_BLINK		0x00000004

/* get count of lights in module */
काष्ठा gb_lights_get_lights_response अणु
	__u8	lights_count;
पूर्ण __packed;

/* light config request payload */
काष्ठा gb_lights_get_light_config_request अणु
	__u8	id;
पूर्ण __packed;

/* light config response payload */
काष्ठा gb_lights_get_light_config_response अणु
	__u8	channel_count;
	__u8	name[32];
पूर्ण __packed;

/* channel config request payload */
काष्ठा gb_lights_get_channel_config_request अणु
	__u8	light_id;
	__u8	channel_id;
पूर्ण __packed;

/* channel flash config request payload */
काष्ठा gb_lights_get_channel_flash_config_request अणु
	__u8	light_id;
	__u8	channel_id;
पूर्ण __packed;

/* channel config response payload */
काष्ठा gb_lights_get_channel_config_response अणु
	__u8	max_brightness;
	__le32	flags;
	__le32	color;
	__u8	color_name[32];
	__le32	mode;
	__u8	mode_name[32];
पूर्ण __packed;

/* channel flash config response payload */
काष्ठा gb_lights_get_channel_flash_config_response अणु
	__le32	पूर्णांकensity_min_uA;
	__le32	पूर्णांकensity_max_uA;
	__le32	पूर्णांकensity_step_uA;
	__le32	समयout_min_us;
	__le32	समयout_max_us;
	__le32	समयout_step_us;
पूर्ण __packed;

/* blink request payload: response have no payload */
काष्ठा gb_lights_blink_request अणु
	__u8	light_id;
	__u8	channel_id;
	__le16	समय_on_ms;
	__le16	समय_off_ms;
पूर्ण __packed;

/* set brightness request payload: response have no payload */
काष्ठा gb_lights_set_brightness_request अणु
	__u8	light_id;
	__u8	channel_id;
	__u8	brightness;
पूर्ण __packed;

/* set color request payload: response have no payload */
काष्ठा gb_lights_set_color_request अणु
	__u8	light_id;
	__u8	channel_id;
	__le32	color;
पूर्ण __packed;

/* set fade request payload: response have no payload */
काष्ठा gb_lights_set_fade_request अणु
	__u8	light_id;
	__u8	channel_id;
	__u8	fade_in;
	__u8	fade_out;
पूर्ण __packed;

/* event request: generated by module */
काष्ठा gb_lights_event_request अणु
	__u8	light_id;
	__u8	event;
#घोषणा GB_LIGHTS_LIGHT_CONFIG		0x01
पूर्ण __packed;

/* set flash पूर्णांकensity request payload: response have no payload */
काष्ठा gb_lights_set_flash_पूर्णांकensity_request अणु
	__u8	light_id;
	__u8	channel_id;
	__le32	पूर्णांकensity_uA;
पूर्ण __packed;

/* set flash strobe state request payload: response have no payload */
काष्ठा gb_lights_set_flash_strobe_request अणु
	__u8	light_id;
	__u8	channel_id;
	__u8	state;
पूर्ण __packed;

/* set flash समयout request payload: response have no payload */
काष्ठा gb_lights_set_flash_समयout_request अणु
	__u8	light_id;
	__u8	channel_id;
	__le32	समयout_us;
पूर्ण __packed;

/* get flash fault request payload */
काष्ठा gb_lights_get_flash_fault_request अणु
	__u8	light_id;
	__u8	channel_id;
पूर्ण __packed;

/* get flash fault response payload */
काष्ठा gb_lights_get_flash_fault_response अणु
	__le32	fault;
#घोषणा GB_LIGHTS_FLASH_FAULT_OVER_VOLTAGE		0x00000000
#घोषणा GB_LIGHTS_FLASH_FAULT_TIMEOUT			0x00000001
#घोषणा GB_LIGHTS_FLASH_FAULT_OVER_TEMPERATURE		0x00000002
#घोषणा GB_LIGHTS_FLASH_FAULT_SHORT_CIRCUIT		0x00000004
#घोषणा GB_LIGHTS_FLASH_FAULT_OVER_CURRENT		0x00000008
#घोषणा GB_LIGHTS_FLASH_FAULT_INDICATOR			0x00000010
#घोषणा GB_LIGHTS_FLASH_FAULT_UNDER_VOLTAGE		0x00000020
#घोषणा GB_LIGHTS_FLASH_FAULT_INPUT_VOLTAGE		0x00000040
#घोषणा GB_LIGHTS_FLASH_FAULT_LED_OVER_TEMPERATURE	0x00000080
पूर्ण __packed;

/* Audio */

#घोषणा GB_AUDIO_TYPE_GET_TOPOLOGY_SIZE		0x02
#घोषणा GB_AUDIO_TYPE_GET_TOPOLOGY		0x03
#घोषणा GB_AUDIO_TYPE_GET_CONTROL		0x04
#घोषणा GB_AUDIO_TYPE_SET_CONTROL		0x05
#घोषणा GB_AUDIO_TYPE_ENABLE_WIDGET		0x06
#घोषणा GB_AUDIO_TYPE_DISABLE_WIDGET		0x07
#घोषणा GB_AUDIO_TYPE_GET_PCM			0x08
#घोषणा GB_AUDIO_TYPE_SET_PCM			0x09
#घोषणा GB_AUDIO_TYPE_SET_TX_DATA_SIZE		0x0a
						/* 0x0b unused */
#घोषणा GB_AUDIO_TYPE_ACTIVATE_TX		0x0c
#घोषणा GB_AUDIO_TYPE_DEACTIVATE_TX		0x0d
#घोषणा GB_AUDIO_TYPE_SET_RX_DATA_SIZE		0x0e
						/* 0x0f unused */
#घोषणा GB_AUDIO_TYPE_ACTIVATE_RX		0x10
#घोषणा GB_AUDIO_TYPE_DEACTIVATE_RX		0x11
#घोषणा GB_AUDIO_TYPE_JACK_EVENT		0x12
#घोषणा GB_AUDIO_TYPE_BUTTON_EVENT		0x13
#घोषणा GB_AUDIO_TYPE_STREAMING_EVENT		0x14
#घोषणा GB_AUDIO_TYPE_SEND_DATA			0x15

/* Module must be able to buffer 10ms of audio data, minimum */
#घोषणा GB_AUDIO_SAMPLE_BUFFER_MIN_US		10000

#घोषणा GB_AUDIO_PCM_NAME_MAX			32
#घोषणा AUDIO_DAI_NAME_MAX			32
#घोषणा AUDIO_CONTROL_NAME_MAX			32
#घोषणा AUDIO_CTL_ELEM_NAME_MAX			44
#घोषणा AUDIO_ENUM_NAME_MAX			64
#घोषणा AUDIO_WIDGET_NAME_MAX			32

/* See SNDRV_PCM_FMTBIT_* in Linux source */
#घोषणा GB_AUDIO_PCM_FMT_S8			BIT(0)
#घोषणा GB_AUDIO_PCM_FMT_U8			BIT(1)
#घोषणा GB_AUDIO_PCM_FMT_S16_LE			BIT(2)
#घोषणा GB_AUDIO_PCM_FMT_S16_BE			BIT(3)
#घोषणा GB_AUDIO_PCM_FMT_U16_LE			BIT(4)
#घोषणा GB_AUDIO_PCM_FMT_U16_BE			BIT(5)
#घोषणा GB_AUDIO_PCM_FMT_S24_LE			BIT(6)
#घोषणा GB_AUDIO_PCM_FMT_S24_BE			BIT(7)
#घोषणा GB_AUDIO_PCM_FMT_U24_LE			BIT(8)
#घोषणा GB_AUDIO_PCM_FMT_U24_BE			BIT(9)
#घोषणा GB_AUDIO_PCM_FMT_S32_LE			BIT(10)
#घोषणा GB_AUDIO_PCM_FMT_S32_BE			BIT(11)
#घोषणा GB_AUDIO_PCM_FMT_U32_LE			BIT(12)
#घोषणा GB_AUDIO_PCM_FMT_U32_BE			BIT(13)

/* See SNDRV_PCM_RATE_* in Linux source */
#घोषणा GB_AUDIO_PCM_RATE_5512			BIT(0)
#घोषणा GB_AUDIO_PCM_RATE_8000			BIT(1)
#घोषणा GB_AUDIO_PCM_RATE_11025			BIT(2)
#घोषणा GB_AUDIO_PCM_RATE_16000			BIT(3)
#घोषणा GB_AUDIO_PCM_RATE_22050			BIT(4)
#घोषणा GB_AUDIO_PCM_RATE_32000			BIT(5)
#घोषणा GB_AUDIO_PCM_RATE_44100			BIT(6)
#घोषणा GB_AUDIO_PCM_RATE_48000			BIT(7)
#घोषणा GB_AUDIO_PCM_RATE_64000			BIT(8)
#घोषणा GB_AUDIO_PCM_RATE_88200			BIT(9)
#घोषणा GB_AUDIO_PCM_RATE_96000			BIT(10)
#घोषणा GB_AUDIO_PCM_RATE_176400		BIT(11)
#घोषणा GB_AUDIO_PCM_RATE_192000		BIT(12)

#घोषणा GB_AUDIO_STREAM_TYPE_CAPTURE		0x1
#घोषणा GB_AUDIO_STREAM_TYPE_PLAYBACK		0x2

#घोषणा GB_AUDIO_CTL_ELEM_ACCESS_READ		BIT(0)
#घोषणा GB_AUDIO_CTL_ELEM_ACCESS_WRITE		BIT(1)

/* See SNDRV_CTL_ELEM_TYPE_* in Linux source */
#घोषणा GB_AUDIO_CTL_ELEM_TYPE_BOOLEAN		0x01
#घोषणा GB_AUDIO_CTL_ELEM_TYPE_INTEGER		0x02
#घोषणा GB_AUDIO_CTL_ELEM_TYPE_ENUMERATED	0x03
#घोषणा GB_AUDIO_CTL_ELEM_TYPE_INTEGER64	0x06

/* See SNDRV_CTL_ELEM_IFACE_* in Linux source */
#घोषणा GB_AUDIO_CTL_ELEM_IFACE_CARD		0x00
#घोषणा GB_AUDIO_CTL_ELEM_IFACE_HWDEP		0x01
#घोषणा GB_AUDIO_CTL_ELEM_IFACE_MIXER		0x02
#घोषणा GB_AUDIO_CTL_ELEM_IFACE_PCM		0x03
#घोषणा GB_AUDIO_CTL_ELEM_IFACE_RAWMIDI		0x04
#घोषणा GB_AUDIO_CTL_ELEM_IFACE_TIMER		0x05
#घोषणा GB_AUDIO_CTL_ELEM_IFACE_SEQUENCER	0x06

/* SNDRV_CTL_ELEM_ACCESS_* in Linux source */
#घोषणा GB_AUDIO_ACCESS_READ			BIT(0)
#घोषणा GB_AUDIO_ACCESS_WRITE			BIT(1)
#घोषणा GB_AUDIO_ACCESS_VOLATILE		BIT(2)
#घोषणा GB_AUDIO_ACCESS_TIMESTAMP		BIT(3)
#घोषणा GB_AUDIO_ACCESS_TLV_READ		BIT(4)
#घोषणा GB_AUDIO_ACCESS_TLV_WRITE		BIT(5)
#घोषणा GB_AUDIO_ACCESS_TLV_COMMAND		BIT(6)
#घोषणा GB_AUDIO_ACCESS_INACTIVE		BIT(7)
#घोषणा GB_AUDIO_ACCESS_LOCK			BIT(8)
#घोषणा GB_AUDIO_ACCESS_OWNER			BIT(9)

/* क्रमागत snd_soc_dapm_type */
#घोषणा GB_AUDIO_WIDGET_TYPE_INPUT		0x0
#घोषणा GB_AUDIO_WIDGET_TYPE_OUTPUT		0x1
#घोषणा GB_AUDIO_WIDGET_TYPE_MUX		0x2
#घोषणा GB_AUDIO_WIDGET_TYPE_VIRT_MUX		0x3
#घोषणा GB_AUDIO_WIDGET_TYPE_VALUE_MUX		0x4
#घोषणा GB_AUDIO_WIDGET_TYPE_MIXER		0x5
#घोषणा GB_AUDIO_WIDGET_TYPE_MIXER_NAMED_CTL	0x6
#घोषणा GB_AUDIO_WIDGET_TYPE_PGA		0x7
#घोषणा GB_AUDIO_WIDGET_TYPE_OUT_DRV		0x8
#घोषणा GB_AUDIO_WIDGET_TYPE_ADC		0x9
#घोषणा GB_AUDIO_WIDGET_TYPE_DAC		0xa
#घोषणा GB_AUDIO_WIDGET_TYPE_MICBIAS		0xb
#घोषणा GB_AUDIO_WIDGET_TYPE_MIC		0xc
#घोषणा GB_AUDIO_WIDGET_TYPE_HP			0xd
#घोषणा GB_AUDIO_WIDGET_TYPE_SPK		0xe
#घोषणा GB_AUDIO_WIDGET_TYPE_LINE		0xf
#घोषणा GB_AUDIO_WIDGET_TYPE_SWITCH		0x10
#घोषणा GB_AUDIO_WIDGET_TYPE_VMID		0x11
#घोषणा GB_AUDIO_WIDGET_TYPE_PRE		0x12
#घोषणा GB_AUDIO_WIDGET_TYPE_POST		0x13
#घोषणा GB_AUDIO_WIDGET_TYPE_SUPPLY		0x14
#घोषणा GB_AUDIO_WIDGET_TYPE_REGULATOR_SUPPLY	0x15
#घोषणा GB_AUDIO_WIDGET_TYPE_CLOCK_SUPPLY	0x16
#घोषणा GB_AUDIO_WIDGET_TYPE_AIF_IN		0x17
#घोषणा GB_AUDIO_WIDGET_TYPE_AIF_OUT		0x18
#घोषणा GB_AUDIO_WIDGET_TYPE_SIGGEN		0x19
#घोषणा GB_AUDIO_WIDGET_TYPE_DAI_IN		0x1a
#घोषणा GB_AUDIO_WIDGET_TYPE_DAI_OUT		0x1b
#घोषणा GB_AUDIO_WIDGET_TYPE_DAI_LINK		0x1c

#घोषणा GB_AUDIO_WIDGET_STATE_DISABLED		0x01
#घोषणा GB_AUDIO_WIDGET_STATE_ENAABLED		0x02

#घोषणा GB_AUDIO_JACK_EVENT_INSERTION		0x1
#घोषणा GB_AUDIO_JACK_EVENT_REMOVAL		0x2

#घोषणा GB_AUDIO_BUTTON_EVENT_PRESS		0x1
#घोषणा GB_AUDIO_BUTTON_EVENT_RELEASE		0x2

#घोषणा GB_AUDIO_STREAMING_EVENT_UNSPECIFIED	0x1
#घोषणा GB_AUDIO_STREAMING_EVENT_HALT		0x2
#घोषणा GB_AUDIO_STREAMING_EVENT_INTERNAL_ERROR	0x3
#घोषणा GB_AUDIO_STREAMING_EVENT_PROTOCOL_ERROR	0x4
#घोषणा GB_AUDIO_STREAMING_EVENT_FAILURE	0x5
#घोषणा GB_AUDIO_STREAMING_EVENT_UNDERRUN	0x6
#घोषणा GB_AUDIO_STREAMING_EVENT_OVERRUN	0x7
#घोषणा GB_AUDIO_STREAMING_EVENT_CLOCKING	0x8
#घोषणा GB_AUDIO_STREAMING_EVENT_DATA_LEN	0x9

#घोषणा GB_AUDIO_INVALID_INDEX			0xff

/* क्रमागत snd_jack_types */
#घोषणा GB_AUDIO_JACK_HEADPHONE			0x0000001
#घोषणा GB_AUDIO_JACK_MICROPHONE		0x0000002
#घोषणा GB_AUDIO_JACK_HEADSET			(GB_AUDIO_JACK_HEADPHONE | \
						 GB_AUDIO_JACK_MICROPHONE)
#घोषणा GB_AUDIO_JACK_LINEOUT			0x0000004
#घोषणा GB_AUDIO_JACK_MECHANICAL		0x0000008
#घोषणा GB_AUDIO_JACK_VIDEOOUT			0x0000010
#घोषणा GB_AUDIO_JACK_AVOUT			(GB_AUDIO_JACK_LINEOUT | \
						 GB_AUDIO_JACK_VIDEOOUT)
#घोषणा GB_AUDIO_JACK_LINEIN			0x0000020
#घोषणा GB_AUDIO_JACK_OC_HPHL			0x0000040
#घोषणा GB_AUDIO_JACK_OC_HPHR			0x0000080
#घोषणा GB_AUDIO_JACK_MICROPHONE2		0x0000200
#घोषणा GB_AUDIO_JACK_ANC_HEADPHONE		(GB_AUDIO_JACK_HEADPHONE | \
						 GB_AUDIO_JACK_MICROPHONE | \
						 GB_AUDIO_JACK_MICROPHONE2)
/* Kept separate from चयनes to facilitate implementation */
#घोषणा GB_AUDIO_JACK_BTN_0			0x4000000
#घोषणा GB_AUDIO_JACK_BTN_1			0x2000000
#घोषणा GB_AUDIO_JACK_BTN_2			0x1000000
#घोषणा GB_AUDIO_JACK_BTN_3			0x0800000

काष्ठा gb_audio_pcm अणु
	__u8	stream_name[GB_AUDIO_PCM_NAME_MAX];
	__le32	क्रमmats;	/* GB_AUDIO_PCM_FMT_* */
	__le32	rates;		/* GB_AUDIO_PCM_RATE_* */
	__u8	chan_min;
	__u8	chan_max;
	__u8	sig_bits;	/* number of bits of content */
पूर्ण __packed;

काष्ठा gb_audio_dai अणु
	__u8			name[AUDIO_DAI_NAME_MAX];
	__le16			data_cport;
	काष्ठा gb_audio_pcm	capture;
	काष्ठा gb_audio_pcm	playback;
पूर्ण __packed;

काष्ठा gb_audio_पूर्णांकeger अणु
	__le32	min;
	__le32	max;
	__le32	step;
पूर्ण __packed;

काष्ठा gb_audio_पूर्णांकeger64 अणु
	__le64	min;
	__le64	max;
	__le64	step;
पूर्ण __packed;

काष्ठा gb_audio_क्रमागतerated अणु
	__le32	items;
	__le16	names_length;
	__u8	names[];
पूर्ण __packed;

काष्ठा gb_audio_ctl_elem_info अणु /* See snd_ctl_elem_info in Linux source */
	__u8		type;		/* GB_AUDIO_CTL_ELEM_TYPE_* */
	__le16		dimen[4];
	जोड़ अणु
		काष्ठा gb_audio_पूर्णांकeger		पूर्णांकeger;
		काष्ठा gb_audio_पूर्णांकeger64	पूर्णांकeger64;
		काष्ठा gb_audio_क्रमागतerated	क्रमागतerated;
	पूर्ण value;
पूर्ण __packed;

काष्ठा gb_audio_ctl_elem_value अणु /* See snd_ctl_elem_value in Linux source */
	__le64				बारtamp; /* XXX needed? */
	जोड़ अणु
		__le32	पूर्णांकeger_value[2];	/* consider CTL_DOUBLE_xxx */
		__le64	पूर्णांकeger64_value[2];
		__le32	क्रमागतerated_item[2];
	पूर्ण value;
पूर्ण __packed;

काष्ठा gb_audio_control अणु
	__u8	name[AUDIO_CONTROL_NAME_MAX];
	__u8	id;		/* 0-63 */
	__u8	अगरace;		/* GB_AUDIO_IFACE_* */
	__le16	data_cport;
	__le32	access;		/* GB_AUDIO_ACCESS_* */
	__u8    count;		/* count of same elements */
	__u8	count_values;	/* count of values, max=2 क्रम CTL_DOUBLE_xxx */
	काष्ठा gb_audio_ctl_elem_info	info;
पूर्ण __packed;

काष्ठा gb_audio_widget अणु
	__u8	name[AUDIO_WIDGET_NAME_MAX];
	__u8	sname[AUDIO_WIDGET_NAME_MAX];
	__u8	id;
	__u8	type;		/* GB_AUDIO_WIDGET_TYPE_* */
	__u8	state;		/* GB_AUDIO_WIDGET_STATE_* */
	__u8	ncontrols;
	काष्ठा gb_audio_control	ctl[];	/* 'ncontrols' entries */
पूर्ण __packed;

काष्ठा gb_audio_route अणु
	__u8	source_id;	/* widget id */
	__u8	destination_id;	/* widget id */
	__u8	control_id;	/* 0-63 */
	__u8	index;		/* Selection within the control */
पूर्ण __packed;

काष्ठा gb_audio_topology अणु
	__u8	num_dais;
	__u8	num_controls;
	__u8	num_widमाला_लो;
	__u8	num_routes;
	__le32	size_dais;
	__le32	size_controls;
	__le32	size_widमाला_लो;
	__le32	size_routes;
	__le32	jack_type;
	/*
	 * काष्ठा gb_audio_dai		dai[num_dais];
	 * काष्ठा gb_audio_control	controls[num_controls];
	 * काष्ठा gb_audio_widget	widमाला_लो[num_widमाला_लो];
	 * काष्ठा gb_audio_route	routes[num_routes];
	 */
	__u8	data[];
पूर्ण __packed;

काष्ठा gb_audio_get_topology_size_response अणु
	__le16	size;
पूर्ण __packed;

काष्ठा gb_audio_get_topology_response अणु
	काष्ठा gb_audio_topology	topology;
पूर्ण __packed;

काष्ठा gb_audio_get_control_request अणु
	__u8	control_id;
	__u8	index;
पूर्ण __packed;

काष्ठा gb_audio_get_control_response अणु
	काष्ठा gb_audio_ctl_elem_value	value;
पूर्ण __packed;

काष्ठा gb_audio_set_control_request अणु
	__u8	control_id;
	__u8	index;
	काष्ठा gb_audio_ctl_elem_value	value;
पूर्ण __packed;

काष्ठा gb_audio_enable_widget_request अणु
	__u8	widget_id;
पूर्ण __packed;

काष्ठा gb_audio_disable_widget_request अणु
	__u8	widget_id;
पूर्ण __packed;

काष्ठा gb_audio_get_pcm_request अणु
	__le16	data_cport;
पूर्ण __packed;

काष्ठा gb_audio_get_pcm_response अणु
	__le32	क्रमmat;
	__le32	rate;
	__u8	channels;
	__u8	sig_bits;
पूर्ण __packed;

काष्ठा gb_audio_set_pcm_request अणु
	__le16	data_cport;
	__le32	क्रमmat;
	__le32	rate;
	__u8	channels;
	__u8	sig_bits;
पूर्ण __packed;

काष्ठा gb_audio_set_tx_data_size_request अणु
	__le16	data_cport;
	__le16	size;
पूर्ण __packed;

काष्ठा gb_audio_activate_tx_request अणु
	__le16	data_cport;
पूर्ण __packed;

काष्ठा gb_audio_deactivate_tx_request अणु
	__le16	data_cport;
पूर्ण __packed;

काष्ठा gb_audio_set_rx_data_size_request अणु
	__le16	data_cport;
	__le16	size;
पूर्ण __packed;

काष्ठा gb_audio_activate_rx_request अणु
	__le16	data_cport;
पूर्ण __packed;

काष्ठा gb_audio_deactivate_rx_request अणु
	__le16	data_cport;
पूर्ण __packed;

काष्ठा gb_audio_jack_event_request अणु
	__u8	widget_id;
	__u8	jack_attribute;
	__u8	event;
पूर्ण __packed;

काष्ठा gb_audio_button_event_request अणु
	__u8	widget_id;
	__u8	button_id;
	__u8	event;
पूर्ण __packed;

काष्ठा gb_audio_streaming_event_request अणु
	__le16	data_cport;
	__u8	event;
पूर्ण __packed;

काष्ठा gb_audio_send_data_request अणु
	__le64	बारtamp;
	__u8	data[];
पूर्ण __packed;


/* Log */

/* operations */
#घोषणा GB_LOG_TYPE_SEND_LOG	0x02

/* length */
#घोषणा GB_LOG_MAX_LEN		1024

काष्ठा gb_log_send_log_request अणु
	__le16	len;
	__u8    msg[];
पूर्ण __packed;

#पूर्ण_अगर /* __GREYBUS_PROTOCOLS_H */

