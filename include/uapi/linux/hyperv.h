<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *
 * Copyright (c) 2011, Microsoft Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ with
 * this program; अगर not, ग_लिखो to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307 USA.
 *
 * Authors:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *   Hank Janssen  <hjanssen@microsoft.com>
 *   K. Y. Srinivasan <kys@microsoft.com>
 *
 */

#अगर_अघोषित _UAPI_HYPERV_H
#घोषणा _UAPI_HYPERV_H

#समावेश <linux/uuid.h>

/*
 * Framework version क्रम util services.
 */
#घोषणा UTIL_FW_MINOR  0

#घोषणा UTIL_WS2K8_FW_MAJOR  1
#घोषणा UTIL_WS2K8_FW_VERSION     (UTIL_WS2K8_FW_MAJOR << 16 | UTIL_FW_MINOR)

#घोषणा UTIL_FW_MAJOR  3
#घोषणा UTIL_FW_VERSION     (UTIL_FW_MAJOR << 16 | UTIL_FW_MINOR)


/*
 * Implementation of host controlled snapshot of the guest.
 */

#घोषणा VSS_OP_REGISTER 128

/*
  Daemon code with full handshake support.
 */
#घोषणा VSS_OP_REGISTER1 129

क्रमागत hv_vss_op अणु
	VSS_OP_CREATE = 0,
	VSS_OP_DELETE,
	VSS_OP_HOT_BACKUP,
	VSS_OP_GET_DM_INFO,
	VSS_OP_BU_COMPLETE,
	/*
	 * Following operations are only supported with IC version >= 5.0
	 */
	VSS_OP_FREEZE, /* Freeze the file प्रणालीs in the VM */
	VSS_OP_THAW, /* Unमुक्तze the file प्रणालीs */
	VSS_OP_AUTO_RECOVER,
	VSS_OP_COUNT /* Number of operations, must be last */
पूर्ण;


/*
 * Header क्रम all VSS messages.
 */
काष्ठा hv_vss_hdr अणु
	__u8 operation;
	__u8 reserved[7];
पूर्ण __attribute__((packed));


/*
 * Flag values क्रम the hv_vss_check_feature. Linux supports only
 * one value.
 */
#घोषणा VSS_HBU_NO_AUTO_RECOVERY	0x00000005

काष्ठा hv_vss_check_feature अणु
	__u32 flags;
पूर्ण __attribute__((packed));

काष्ठा hv_vss_check_dm_info अणु
	__u32 flags;
पूर्ण __attribute__((packed));

काष्ठा hv_vss_msg अणु
	जोड़ अणु
		काष्ठा hv_vss_hdr vss_hdr;
		पूर्णांक error;
	पूर्ण;
	जोड़ अणु
		काष्ठा hv_vss_check_feature vss_cf;
		काष्ठा hv_vss_check_dm_info dm_info;
	पूर्ण;
पूर्ण __attribute__((packed));

/*
 * Implementation of a host to guest copy facility.
 */

#घोषणा FCOPY_VERSION_0 0
#घोषणा FCOPY_VERSION_1 1
#घोषणा FCOPY_CURRENT_VERSION FCOPY_VERSION_1
#घोषणा W_MAX_PATH 260

क्रमागत hv_fcopy_op अणु
	START_खाता_COPY = 0,
	WRITE_TO_खाता,
	COMPLETE_FCOPY,
	CANCEL_FCOPY,
पूर्ण;

काष्ठा hv_fcopy_hdr अणु
	__u32 operation;
	__u8 service_id0[16]; /* currently unused */
	__u8 service_id1[16]; /* currently unused */
पूर्ण __attribute__((packed));

#घोषणा OVER_WRITE	0x1
#घोषणा CREATE_PATH	0x2

काष्ठा hv_start_fcopy अणु
	काष्ठा hv_fcopy_hdr hdr;
	__u16 file_name[W_MAX_PATH];
	__u16 path_name[W_MAX_PATH];
	__u32 copy_flags;
	__u64 file_size;
पूर्ण __attribute__((packed));

/*
 * The file is chunked पूर्णांकo fragments.
 */
#घोषणा DATA_FRAGMENT	(6 * 1024)

काष्ठा hv_करो_fcopy अणु
	काष्ठा hv_fcopy_hdr hdr;
	__u32   pad;
	__u64	offset;
	__u32	size;
	__u8	data[DATA_FRAGMENT];
पूर्ण __attribute__((packed));

/*
 * An implementation of HyperV key value pair (KVP) functionality क्रम Linux.
 *
 *
 * Copyright (C) 2010, Novell, Inc.
 * Author : K. Y. Srinivasan <ksrinivasan@novell.com>
 *
 */

/*
 * Maximum value size - used क्रम both key names and value data, and includes
 * any applicable शून्य terminators.
 *
 * Note:  This limit is somewhat arbitrary, but falls easily within what is
 * supported क्रम all native guests (back to Win 2000) and what is reasonable
 * क्रम the IC KVP exchange functionality.  Note that Winकरोws Me/98/95 are
 * limited to 255 अक्षरacter key names.
 *
 * MSDN recommends not storing data values larger than 2048 bytes in the
 * registry.
 *
 * Note:  This value is used in defining the KVP exchange message - this value
 * cannot be modअगरied without affecting the message size and compatibility.
 */

/*
 * bytes, including any null terminators
 */
#घोषणा HV_KVP_EXCHANGE_MAX_VALUE_SIZE          (2048)


/*
 * Maximum key size - the registry limit क्रम the length of an entry name
 * is 256 अक्षरacters, including the null terminator
 */

#घोषणा HV_KVP_EXCHANGE_MAX_KEY_SIZE            (512)

/*
 * In Linux, we implement the KVP functionality in two components:
 * 1) The kernel component which is packaged as part of the hv_utils driver
 * is responsible क्रम communicating with the host and responsible क्रम
 * implementing the host/guest protocol. 2) A user level daemon that is
 * responsible क्रम data gathering.
 *
 * Host/Guest Protocol: The host iterates over an index and expects the guest
 * to assign a key name to the index and also वापस the value corresponding to
 * the key. The host will have aपंचांगost one KVP transaction outstanding at any
 * given poपूर्णांक in समय. The host side iteration stops when the guest वापसs
 * an error. Microsoft has specअगरied the following mapping of key names to
 * host specअगरied index:
 *
 *	Index		Key Name
 *	0		FullyQualअगरiedDoमुख्यName
 *	1		IntegrationServicesVersion
 *	2		NetworkAddressIPv4
 *	3		NetworkAddressIPv6
 *	4		OSBuildNumber
 *	5		OSName
 *	6		OSMajorVersion
 *	7		OSMinorVersion
 *	8		OSVersion
 *	9		ProcessorArchitecture
 *
 * The Winकरोws host expects the Key Name and Key Value to be encoded in utf16.
 *
 * Guest Kernel/KVP Daemon Protocol: As noted earlier, we implement all of the
 * data gathering functionality in a user mode daemon. The user level daemon
 * is also responsible क्रम binding the key name to the index as well. The
 * kernel and user-level daemon communicate using a connector channel.
 *
 * The user mode component first रेजिस्टरs with the
 * kernel component. Subsequently, the kernel component requests, data
 * क्रम the specअगरied keys. In response to this message the user mode component
 * fills in the value corresponding to the specअगरied key. We overload the
 * sequence field in the cn_msg header to define our KVP message types.
 *
 *
 * The kernel component simply acts as a conduit क्रम communication between the
 * Winकरोws host and the user-level daemon. The kernel component passes up the
 * index received from the Host to the user-level daemon. If the index is
 * valid (supported), the corresponding key as well as its
 * value (both are strings) is वापसed. If the index is invalid
 * (not supported), a शून्य key string is वापसed.
 */


/*
 * Registry value types.
 */

#घोषणा REG_SZ 1
#घोषणा REG_U32 4
#घोषणा REG_U64 8

/*
 * As we look at expanding the KVP functionality to include
 * IP injection functionality, we need to मुख्यtain binary
 * compatibility with older daemons.
 *
 * The KVP opcodes are defined by the host and it was unक्रमtunate
 * that I chose to treat the registration operation as part of the
 * KVP operations defined by the host.
 * Here is the level of compatibility
 * (between the user level daemon and the kernel KVP driver) that we
 * will implement:
 *
 * An older daemon will always be supported on a newer driver.
 * A given user level daemon will require a minimal version of the
 * kernel driver.
 * If we cannot handle the version dअगरferences, we will fail gracefully
 * (this can happen when we have a user level daemon that is more
 * advanced than the KVP driver.
 *
 * We will use values used in this handshake क्रम determining अगर we have
 * workable user level daemon and the kernel driver. We begin by taking the
 * registration opcode out of the KVP opcode namespace. We will however,
 * मुख्यtain compatibility with the existing user-level daemon code.
 */

/*
 * Daemon code not supporting IP injection (legacy daemon).
 */

#घोषणा KVP_OP_REGISTER	4

/*
 * Daemon code supporting IP injection.
 * The KVP opcode field is used to communicate the
 * registration inक्रमmation; so define a namespace that
 * will be distinct from the host defined KVP opcode.
 */

#घोषणा KVP_OP_REGISTER1 100

क्रमागत hv_kvp_exchg_op अणु
	KVP_OP_GET = 0,
	KVP_OP_SET,
	KVP_OP_DELETE,
	KVP_OP_ENUMERATE,
	KVP_OP_GET_IP_INFO,
	KVP_OP_SET_IP_INFO,
	KVP_OP_COUNT /* Number of operations, must be last. */
पूर्ण;

क्रमागत hv_kvp_exchg_pool अणु
	KVP_POOL_EXTERNAL = 0,
	KVP_POOL_GUEST,
	KVP_POOL_AUTO,
	KVP_POOL_AUTO_EXTERNAL,
	KVP_POOL_AUTO_INTERNAL,
	KVP_POOL_COUNT /* Number of pools, must be last. */
पूर्ण;

/*
 * Some Hyper-V status codes.
 */

#घोषणा HV_S_OK				0x00000000
#घोषणा HV_E_FAIL			0x80004005
#घोषणा HV_S_CONT			0x80070103
#घोषणा HV_ERROR_NOT_SUPPORTED		0x80070032
#घोषणा HV_ERROR_MACHINE_LOCKED		0x800704F7
#घोषणा HV_ERROR_DEVICE_NOT_CONNECTED	0x8007048F
#घोषणा HV_INVALIDARG			0x80070057
#घोषणा HV_GUID_NOTFOUND		0x80041002
#घोषणा HV_ERROR_ALREADY_EXISTS		0x80070050
#घोषणा HV_ERROR_DISK_FULL		0x80070070

#घोषणा ADDR_FAMILY_NONE	0x00
#घोषणा ADDR_FAMILY_IPV4	0x01
#घोषणा ADDR_FAMILY_IPV6	0x02

#घोषणा MAX_ADAPTER_ID_SIZE	128
#घोषणा MAX_IP_ADDR_SIZE	1024
#घोषणा MAX_GATEWAY_SIZE	512


काष्ठा hv_kvp_ipaddr_value अणु
	__u16	adapter_id[MAX_ADAPTER_ID_SIZE];
	__u8	addr_family;
	__u8	dhcp_enabled;
	__u16	ip_addr[MAX_IP_ADDR_SIZE];
	__u16	sub_net[MAX_IP_ADDR_SIZE];
	__u16	gate_way[MAX_GATEWAY_SIZE];
	__u16	dns_addr[MAX_IP_ADDR_SIZE];
पूर्ण __attribute__((packed));


काष्ठा hv_kvp_hdr अणु
	__u8 operation;
	__u8 pool;
	__u16 pad;
पूर्ण __attribute__((packed));

काष्ठा hv_kvp_exchg_msg_value अणु
	__u32 value_type;
	__u32 key_size;
	__u32 value_size;
	__u8 key[HV_KVP_EXCHANGE_MAX_KEY_SIZE];
	जोड़ अणु
		__u8 value[HV_KVP_EXCHANGE_MAX_VALUE_SIZE];
		__u32 value_u32;
		__u64 value_u64;
	पूर्ण;
पूर्ण __attribute__((packed));

काष्ठा hv_kvp_msg_क्रमागतerate अणु
	__u32 index;
	काष्ठा hv_kvp_exchg_msg_value data;
पूर्ण __attribute__((packed));

काष्ठा hv_kvp_msg_get अणु
	काष्ठा hv_kvp_exchg_msg_value data;
पूर्ण;

काष्ठा hv_kvp_msg_set अणु
	काष्ठा hv_kvp_exchg_msg_value data;
पूर्ण;

काष्ठा hv_kvp_msg_delete अणु
	__u32 key_size;
	__u8 key[HV_KVP_EXCHANGE_MAX_KEY_SIZE];
पूर्ण;

काष्ठा hv_kvp_रेजिस्टर अणु
	__u8 version[HV_KVP_EXCHANGE_MAX_KEY_SIZE];
पूर्ण;

काष्ठा hv_kvp_msg अणु
	जोड़ अणु
		काष्ठा hv_kvp_hdr	kvp_hdr;
		पूर्णांक error;
	पूर्ण;
	जोड़ अणु
		काष्ठा hv_kvp_msg_get		kvp_get;
		काष्ठा hv_kvp_msg_set		kvp_set;
		काष्ठा hv_kvp_msg_delete	kvp_delete;
		काष्ठा hv_kvp_msg_क्रमागतerate	kvp_क्रमागत_data;
		काष्ठा hv_kvp_ipaddr_value      kvp_ip_val;
		काष्ठा hv_kvp_रेजिस्टर		kvp_रेजिस्टर;
	पूर्ण body;
पूर्ण __attribute__((packed));

काष्ठा hv_kvp_ip_msg अणु
	__u8 operation;
	__u8 pool;
	काष्ठा hv_kvp_ipaddr_value      kvp_ip_val;
पूर्ण __attribute__((packed));

#पूर्ण_अगर /* _UAPI_HYPERV_H */
