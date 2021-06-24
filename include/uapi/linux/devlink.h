<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * include/uapi/linux/devlink.h - Network physical device Netlink पूर्णांकerface
 * Copyright (c) 2016 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2016 Jiri Pirko <jiri@mellanox.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#अगर_अघोषित _UAPI_LINUX_DEVLINK_H_
#घोषणा _UAPI_LINUX_DEVLINK_H_

#समावेश <linux/स्थिर.h>

#घोषणा DEVLINK_GENL_NAME "devlink"
#घोषणा DEVLINK_GENL_VERSION 0x1
#घोषणा DEVLINK_GENL_MCGRP_CONFIG_NAME "config"

क्रमागत devlink_command अणु
	/* करोn't change the order or add anything between, this is ABI! */
	DEVLINK_CMD_UNSPEC,

	DEVLINK_CMD_GET,		/* can dump */
	DEVLINK_CMD_SET,
	DEVLINK_CMD_NEW,
	DEVLINK_CMD_DEL,

	DEVLINK_CMD_PORT_GET,		/* can dump */
	DEVLINK_CMD_PORT_SET,
	DEVLINK_CMD_PORT_NEW,
	DEVLINK_CMD_PORT_DEL,

	DEVLINK_CMD_PORT_SPLIT,
	DEVLINK_CMD_PORT_UNSPLIT,

	DEVLINK_CMD_SB_GET,		/* can dump */
	DEVLINK_CMD_SB_SET,
	DEVLINK_CMD_SB_NEW,
	DEVLINK_CMD_SB_DEL,

	DEVLINK_CMD_SB_POOL_GET,	/* can dump */
	DEVLINK_CMD_SB_POOL_SET,
	DEVLINK_CMD_SB_POOL_NEW,
	DEVLINK_CMD_SB_POOL_DEL,

	DEVLINK_CMD_SB_PORT_POOL_GET,	/* can dump */
	DEVLINK_CMD_SB_PORT_POOL_SET,
	DEVLINK_CMD_SB_PORT_POOL_NEW,
	DEVLINK_CMD_SB_PORT_POOL_DEL,

	DEVLINK_CMD_SB_TC_POOL_BIND_GET,	/* can dump */
	DEVLINK_CMD_SB_TC_POOL_BIND_SET,
	DEVLINK_CMD_SB_TC_POOL_BIND_NEW,
	DEVLINK_CMD_SB_TC_POOL_BIND_DEL,

	/* Shared buffer occupancy monitoring commands */
	DEVLINK_CMD_SB_OCC_SNAPSHOT,
	DEVLINK_CMD_SB_OCC_MAX_CLEAR,

	DEVLINK_CMD_ESWITCH_GET,
#घोषणा DEVLINK_CMD_ESWITCH_MODE_GET /* obsolete, never use this! */ \
	DEVLINK_CMD_ESWITCH_GET

	DEVLINK_CMD_ESWITCH_SET,
#घोषणा DEVLINK_CMD_ESWITCH_MODE_SET /* obsolete, never use this! */ \
	DEVLINK_CMD_ESWITCH_SET

	DEVLINK_CMD_DPIPE_TABLE_GET,
	DEVLINK_CMD_DPIPE_ENTRIES_GET,
	DEVLINK_CMD_DPIPE_HEADERS_GET,
	DEVLINK_CMD_DPIPE_TABLE_COUNTERS_SET,
	DEVLINK_CMD_RESOURCE_SET,
	DEVLINK_CMD_RESOURCE_DUMP,

	/* Hot driver reload, makes configuration changes take place. The
	 * devlink instance is not released during the process.
	 */
	DEVLINK_CMD_RELOAD,

	DEVLINK_CMD_PARAM_GET,		/* can dump */
	DEVLINK_CMD_PARAM_SET,
	DEVLINK_CMD_PARAM_NEW,
	DEVLINK_CMD_PARAM_DEL,

	DEVLINK_CMD_REGION_GET,
	DEVLINK_CMD_REGION_SET,
	DEVLINK_CMD_REGION_NEW,
	DEVLINK_CMD_REGION_DEL,
	DEVLINK_CMD_REGION_READ,

	DEVLINK_CMD_PORT_PARAM_GET,	/* can dump */
	DEVLINK_CMD_PORT_PARAM_SET,
	DEVLINK_CMD_PORT_PARAM_NEW,
	DEVLINK_CMD_PORT_PARAM_DEL,

	DEVLINK_CMD_INFO_GET,		/* can dump */

	DEVLINK_CMD_HEALTH_REPORTER_GET,
	DEVLINK_CMD_HEALTH_REPORTER_SET,
	DEVLINK_CMD_HEALTH_REPORTER_RECOVER,
	DEVLINK_CMD_HEALTH_REPORTER_DIAGNOSE,
	DEVLINK_CMD_HEALTH_REPORTER_DUMP_GET,
	DEVLINK_CMD_HEALTH_REPORTER_DUMP_CLEAR,

	DEVLINK_CMD_FLASH_UPDATE,
	DEVLINK_CMD_FLASH_UPDATE_END,		/* notअगरication only */
	DEVLINK_CMD_FLASH_UPDATE_STATUS,	/* notअगरication only */

	DEVLINK_CMD_TRAP_GET,		/* can dump */
	DEVLINK_CMD_TRAP_SET,
	DEVLINK_CMD_TRAP_NEW,
	DEVLINK_CMD_TRAP_DEL,

	DEVLINK_CMD_TRAP_GROUP_GET,	/* can dump */
	DEVLINK_CMD_TRAP_GROUP_SET,
	DEVLINK_CMD_TRAP_GROUP_NEW,
	DEVLINK_CMD_TRAP_GROUP_DEL,

	DEVLINK_CMD_TRAP_POLICER_GET,	/* can dump */
	DEVLINK_CMD_TRAP_POLICER_SET,
	DEVLINK_CMD_TRAP_POLICER_NEW,
	DEVLINK_CMD_TRAP_POLICER_DEL,

	DEVLINK_CMD_HEALTH_REPORTER_TEST,

	/* add new commands above here */
	__DEVLINK_CMD_MAX,
	DEVLINK_CMD_MAX = __DEVLINK_CMD_MAX - 1
पूर्ण;

क्रमागत devlink_port_type अणु
	DEVLINK_PORT_TYPE_NOTSET,
	DEVLINK_PORT_TYPE_AUTO,
	DEVLINK_PORT_TYPE_ETH,
	DEVLINK_PORT_TYPE_IB,
पूर्ण;

क्रमागत devlink_sb_pool_type अणु
	DEVLINK_SB_POOL_TYPE_INGRESS,
	DEVLINK_SB_POOL_TYPE_EGRESS,
पूर्ण;

/* अटल threshold - limiting the maximum number of bytes.
 * dynamic threshold - limiting the maximum number of bytes
 *   based on the currently available मुक्त space in the shared buffer pool.
 *   In this mode, the maximum quota is calculated based
 *   on the following क्रमmula:
 *     max_quota = alpha / (1 + alpha) * Free_Buffer
 *   While Free_Buffer is the amount of none-occupied buffer associated to
 *   the relevant pool.
 *   The value range which can be passed is 0-20 and serves
 *   क्रम computation of alpha by following क्रमmula:
 *     alpha = 2 ^ (passed_value - 10)
 */

क्रमागत devlink_sb_threshold_type अणु
	DEVLINK_SB_THRESHOLD_TYPE_STATIC,
	DEVLINK_SB_THRESHOLD_TYPE_DYNAMIC,
पूर्ण;

#घोषणा DEVLINK_SB_THRESHOLD_TO_ALPHA_MAX 20

क्रमागत devlink_eचयन_mode अणु
	DEVLINK_ESWITCH_MODE_LEGACY,
	DEVLINK_ESWITCH_MODE_SWITCHDEV,
पूर्ण;

क्रमागत devlink_eचयन_अंतरभूत_mode अणु
	DEVLINK_ESWITCH_INLINE_MODE_NONE,
	DEVLINK_ESWITCH_INLINE_MODE_LINK,
	DEVLINK_ESWITCH_INLINE_MODE_NETWORK,
	DEVLINK_ESWITCH_INLINE_MODE_TRANSPORT,
पूर्ण;

क्रमागत devlink_eचयन_encap_mode अणु
	DEVLINK_ESWITCH_ENCAP_MODE_NONE,
	DEVLINK_ESWITCH_ENCAP_MODE_BASIC,
पूर्ण;

क्रमागत devlink_port_flavour अणु
	DEVLINK_PORT_FLAVOUR_PHYSICAL, /* Any kind of a port physically
					* facing the user.
					*/
	DEVLINK_PORT_FLAVOUR_CPU, /* CPU port */
	DEVLINK_PORT_FLAVOUR_DSA, /* Distributed चयन architecture
				   * पूर्णांकerconnect port.
				   */
	DEVLINK_PORT_FLAVOUR_PCI_PF, /* Represents eचयन port क्रम
				      * the PCI PF. It is an पूर्णांकernal
				      * port that faces the PCI PF.
				      */
	DEVLINK_PORT_FLAVOUR_PCI_VF, /* Represents eचयन port
				      * क्रम the PCI VF. It is an पूर्णांकernal
				      * port that faces the PCI VF.
				      */
	DEVLINK_PORT_FLAVOUR_VIRTUAL, /* Any भव port facing the user. */
	DEVLINK_PORT_FLAVOUR_UNUSED, /* Port which exists in the चयन, but
				      * is not used in any way.
				      */
	DEVLINK_PORT_FLAVOUR_PCI_SF, /* Represents eचयन port
				      * क्रम the PCI SF. It is an पूर्णांकernal
				      * port that faces the PCI SF.
				      */
पूर्ण;

क्रमागत devlink_param_cmode अणु
	DEVLINK_PARAM_CMODE_RUNTIME,
	DEVLINK_PARAM_CMODE_DRIVERINIT,
	DEVLINK_PARAM_CMODE_PERMANENT,

	/* Add new configuration modes above */
	__DEVLINK_PARAM_CMODE_MAX,
	DEVLINK_PARAM_CMODE_MAX = __DEVLINK_PARAM_CMODE_MAX - 1
पूर्ण;

क्रमागत devlink_param_fw_load_policy_value अणु
	DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_DRIVER,
	DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_FLASH,
	DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_DISK,
	DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_UNKNOWN,
पूर्ण;

क्रमागत devlink_param_reset_dev_on_drv_probe_value अणु
	DEVLINK_PARAM_RESET_DEV_ON_DRV_PROBE_VALUE_UNKNOWN,
	DEVLINK_PARAM_RESET_DEV_ON_DRV_PROBE_VALUE_ALWAYS,
	DEVLINK_PARAM_RESET_DEV_ON_DRV_PROBE_VALUE_NEVER,
	DEVLINK_PARAM_RESET_DEV_ON_DRV_PROBE_VALUE_DISK,
पूर्ण;

क्रमागत अणु
	DEVLINK_ATTR_STATS_RX_PACKETS,		/* u64 */
	DEVLINK_ATTR_STATS_RX_BYTES,		/* u64 */
	DEVLINK_ATTR_STATS_RX_DROPPED,		/* u64 */

	__DEVLINK_ATTR_STATS_MAX,
	DEVLINK_ATTR_STATS_MAX = __DEVLINK_ATTR_STATS_MAX - 1
पूर्ण;

/* Specअगरy what sections of a flash component can be overwritten when
 * perक्रमming an update. Overwriting of firmware binary sections is always
 * implicitly assumed to be allowed.
 *
 * Each section must be करोcumented in
 * Documentation/networking/devlink/devlink-flash.rst
 *
 */
क्रमागत अणु
	DEVLINK_FLASH_OVERWRITE_SETTINGS_BIT,
	DEVLINK_FLASH_OVERWRITE_IDENTIFIERS_BIT,

	__DEVLINK_FLASH_OVERWRITE_MAX_BIT,
	DEVLINK_FLASH_OVERWRITE_MAX_BIT = __DEVLINK_FLASH_OVERWRITE_MAX_BIT - 1
पूर्ण;

#घोषणा DEVLINK_FLASH_OVERWRITE_SETTINGS _BITUL(DEVLINK_FLASH_OVERWRITE_SETTINGS_BIT)
#घोषणा DEVLINK_FLASH_OVERWRITE_IDENTIFIERS _BITUL(DEVLINK_FLASH_OVERWRITE_IDENTIFIERS_BIT)

#घोषणा DEVLINK_SUPPORTED_FLASH_OVERWRITE_SECTIONS \
	(_BITUL(__DEVLINK_FLASH_OVERWRITE_MAX_BIT) - 1)

/**
 * क्रमागत devlink_trap_action - Packet trap action.
 * @DEVLINK_TRAP_ACTION_DROP: Packet is dropped by the device and a copy is not
 *                            sent to the CPU.
 * @DEVLINK_TRAP_ACTION_TRAP: The sole copy of the packet is sent to the CPU.
 * @DEVLINK_TRAP_ACTION_MIRROR: Packet is क्रमwarded by the device and a copy is
 *                              sent to the CPU.
 */
क्रमागत devlink_trap_action अणु
	DEVLINK_TRAP_ACTION_DROP,
	DEVLINK_TRAP_ACTION_TRAP,
	DEVLINK_TRAP_ACTION_MIRROR,
पूर्ण;

/**
 * क्रमागत devlink_trap_type - Packet trap type.
 * @DEVLINK_TRAP_TYPE_DROP: Trap reason is a drop. Trapped packets are only
 *                          processed by devlink and not injected to the
 *                          kernel's Rx path.
 * @DEVLINK_TRAP_TYPE_EXCEPTION: Trap reason is an exception. Packet was not
 *                               क्रमwarded as पूर्णांकended due to an exception
 *                               (e.g., missing neighbour entry) and trapped to
 *                               control plane क्रम resolution. Trapped packets
 *                               are processed by devlink and injected to
 *                               the kernel's Rx path.
 * @DEVLINK_TRAP_TYPE_CONTROL: Packet was trapped because it is required क्रम
 *                             the correct functioning of the control plane.
 *                             For example, an ARP request packet. Trapped
 *                             packets are injected to the kernel's Rx path,
 *                             but not reported to drop monitor.
 */
क्रमागत devlink_trap_type अणु
	DEVLINK_TRAP_TYPE_DROP,
	DEVLINK_TRAP_TYPE_EXCEPTION,
	DEVLINK_TRAP_TYPE_CONTROL,
पूर्ण;

क्रमागत अणु
	/* Trap can report input port as metadata */
	DEVLINK_ATTR_TRAP_METADATA_TYPE_IN_PORT,
	/* Trap can report flow action cookie as metadata */
	DEVLINK_ATTR_TRAP_METADATA_TYPE_FA_COOKIE,
पूर्ण;

क्रमागत devlink_reload_action अणु
	DEVLINK_RELOAD_ACTION_UNSPEC,
	DEVLINK_RELOAD_ACTION_DRIVER_REINIT,	/* Driver entities re-instantiation */
	DEVLINK_RELOAD_ACTION_FW_ACTIVATE,	/* FW activate */

	/* Add new reload actions above */
	__DEVLINK_RELOAD_ACTION_MAX,
	DEVLINK_RELOAD_ACTION_MAX = __DEVLINK_RELOAD_ACTION_MAX - 1
पूर्ण;

क्रमागत devlink_reload_limit अणु
	DEVLINK_RELOAD_LIMIT_UNSPEC,	/* unspecअगरied, no स्थिरraपूर्णांकs */
	DEVLINK_RELOAD_LIMIT_NO_RESET,	/* No reset allowed, no करोwn समय allowed,
					 * no link flap and no configuration is lost.
					 */

	/* Add new reload limit above */
	__DEVLINK_RELOAD_LIMIT_MAX,
	DEVLINK_RELOAD_LIMIT_MAX = __DEVLINK_RELOAD_LIMIT_MAX - 1
पूर्ण;

#घोषणा DEVLINK_RELOAD_LIMITS_VALID_MASK (_BITUL(__DEVLINK_RELOAD_LIMIT_MAX) - 1)

क्रमागत devlink_attr अणु
	/* करोn't change the order or add anything between, this is ABI! */
	DEVLINK_ATTR_UNSPEC,

	/* bus name + dev name together are a handle क्रम devlink entity */
	DEVLINK_ATTR_BUS_NAME,			/* string */
	DEVLINK_ATTR_DEV_NAME,			/* string */

	DEVLINK_ATTR_PORT_INDEX,		/* u32 */
	DEVLINK_ATTR_PORT_TYPE,			/* u16 */
	DEVLINK_ATTR_PORT_DESIRED_TYPE,		/* u16 */
	DEVLINK_ATTR_PORT_NETDEV_IFINDEX,	/* u32 */
	DEVLINK_ATTR_PORT_NETDEV_NAME,		/* string */
	DEVLINK_ATTR_PORT_IBDEV_NAME,		/* string */
	DEVLINK_ATTR_PORT_SPLIT_COUNT,		/* u32 */
	DEVLINK_ATTR_PORT_SPLIT_GROUP,		/* u32 */
	DEVLINK_ATTR_SB_INDEX,			/* u32 */
	DEVLINK_ATTR_SB_SIZE,			/* u32 */
	DEVLINK_ATTR_SB_INGRESS_POOL_COUNT,	/* u16 */
	DEVLINK_ATTR_SB_EGRESS_POOL_COUNT,	/* u16 */
	DEVLINK_ATTR_SB_INGRESS_TC_COUNT,	/* u16 */
	DEVLINK_ATTR_SB_EGRESS_TC_COUNT,	/* u16 */
	DEVLINK_ATTR_SB_POOL_INDEX,		/* u16 */
	DEVLINK_ATTR_SB_POOL_TYPE,		/* u8 */
	DEVLINK_ATTR_SB_POOL_SIZE,		/* u32 */
	DEVLINK_ATTR_SB_POOL_THRESHOLD_TYPE,	/* u8 */
	DEVLINK_ATTR_SB_THRESHOLD,		/* u32 */
	DEVLINK_ATTR_SB_TC_INDEX,		/* u16 */
	DEVLINK_ATTR_SB_OCC_CUR,		/* u32 */
	DEVLINK_ATTR_SB_OCC_MAX,		/* u32 */
	DEVLINK_ATTR_ESWITCH_MODE,		/* u16 */
	DEVLINK_ATTR_ESWITCH_INLINE_MODE,	/* u8 */

	DEVLINK_ATTR_DPIPE_TABLES,		/* nested */
	DEVLINK_ATTR_DPIPE_TABLE,		/* nested */
	DEVLINK_ATTR_DPIPE_TABLE_NAME,		/* string */
	DEVLINK_ATTR_DPIPE_TABLE_SIZE,		/* u64 */
	DEVLINK_ATTR_DPIPE_TABLE_MATCHES,	/* nested */
	DEVLINK_ATTR_DPIPE_TABLE_ACTIONS,	/* nested */
	DEVLINK_ATTR_DPIPE_TABLE_COUNTERS_ENABLED,	/* u8 */

	DEVLINK_ATTR_DPIPE_ENTRIES,		/* nested */
	DEVLINK_ATTR_DPIPE_ENTRY,		/* nested */
	DEVLINK_ATTR_DPIPE_ENTRY_INDEX,		/* u64 */
	DEVLINK_ATTR_DPIPE_ENTRY_MATCH_VALUES,	/* nested */
	DEVLINK_ATTR_DPIPE_ENTRY_ACTION_VALUES,	/* nested */
	DEVLINK_ATTR_DPIPE_ENTRY_COUNTER,	/* u64 */

	DEVLINK_ATTR_DPIPE_MATCH,		/* nested */
	DEVLINK_ATTR_DPIPE_MATCH_VALUE,		/* nested */
	DEVLINK_ATTR_DPIPE_MATCH_TYPE,		/* u32 */

	DEVLINK_ATTR_DPIPE_ACTION,		/* nested */
	DEVLINK_ATTR_DPIPE_ACTION_VALUE,	/* nested */
	DEVLINK_ATTR_DPIPE_ACTION_TYPE,		/* u32 */

	DEVLINK_ATTR_DPIPE_VALUE,
	DEVLINK_ATTR_DPIPE_VALUE_MASK,
	DEVLINK_ATTR_DPIPE_VALUE_MAPPING,	/* u32 */

	DEVLINK_ATTR_DPIPE_HEADERS,		/* nested */
	DEVLINK_ATTR_DPIPE_HEADER,		/* nested */
	DEVLINK_ATTR_DPIPE_HEADER_NAME,		/* string */
	DEVLINK_ATTR_DPIPE_HEADER_ID,		/* u32 */
	DEVLINK_ATTR_DPIPE_HEADER_FIELDS,	/* nested */
	DEVLINK_ATTR_DPIPE_HEADER_GLOBAL,	/* u8 */
	DEVLINK_ATTR_DPIPE_HEADER_INDEX,	/* u32 */

	DEVLINK_ATTR_DPIPE_FIELD,		/* nested */
	DEVLINK_ATTR_DPIPE_FIELD_NAME,		/* string */
	DEVLINK_ATTR_DPIPE_FIELD_ID,		/* u32 */
	DEVLINK_ATTR_DPIPE_FIELD_BITWIDTH,	/* u32 */
	DEVLINK_ATTR_DPIPE_FIELD_MAPPING_TYPE,	/* u32 */

	DEVLINK_ATTR_PAD,

	DEVLINK_ATTR_ESWITCH_ENCAP_MODE,	/* u8 */
	DEVLINK_ATTR_RESOURCE_LIST,		/* nested */
	DEVLINK_ATTR_RESOURCE,			/* nested */
	DEVLINK_ATTR_RESOURCE_NAME,		/* string */
	DEVLINK_ATTR_RESOURCE_ID,		/* u64 */
	DEVLINK_ATTR_RESOURCE_SIZE,		/* u64 */
	DEVLINK_ATTR_RESOURCE_SIZE_NEW,		/* u64 */
	DEVLINK_ATTR_RESOURCE_SIZE_VALID,	/* u8 */
	DEVLINK_ATTR_RESOURCE_SIZE_MIN,		/* u64 */
	DEVLINK_ATTR_RESOURCE_SIZE_MAX,		/* u64 */
	DEVLINK_ATTR_RESOURCE_SIZE_GRAN,        /* u64 */
	DEVLINK_ATTR_RESOURCE_UNIT,		/* u8 */
	DEVLINK_ATTR_RESOURCE_OCC,		/* u64 */
	DEVLINK_ATTR_DPIPE_TABLE_RESOURCE_ID,	/* u64 */
	DEVLINK_ATTR_DPIPE_TABLE_RESOURCE_UNITS,/* u64 */

	DEVLINK_ATTR_PORT_FLAVOUR,		/* u16 */
	DEVLINK_ATTR_PORT_NUMBER,		/* u32 */
	DEVLINK_ATTR_PORT_SPLIT_SUBPORT_NUMBER,	/* u32 */

	DEVLINK_ATTR_PARAM,			/* nested */
	DEVLINK_ATTR_PARAM_NAME,		/* string */
	DEVLINK_ATTR_PARAM_GENERIC,		/* flag */
	DEVLINK_ATTR_PARAM_TYPE,		/* u8 */
	DEVLINK_ATTR_PARAM_VALUES_LIST,		/* nested */
	DEVLINK_ATTR_PARAM_VALUE,		/* nested */
	DEVLINK_ATTR_PARAM_VALUE_DATA,		/* dynamic */
	DEVLINK_ATTR_PARAM_VALUE_CMODE,		/* u8 */

	DEVLINK_ATTR_REGION_NAME,               /* string */
	DEVLINK_ATTR_REGION_SIZE,               /* u64 */
	DEVLINK_ATTR_REGION_SNAPSHOTS,          /* nested */
	DEVLINK_ATTR_REGION_SNAPSHOT,           /* nested */
	DEVLINK_ATTR_REGION_SNAPSHOT_ID,        /* u32 */

	DEVLINK_ATTR_REGION_CHUNKS,             /* nested */
	DEVLINK_ATTR_REGION_CHUNK,              /* nested */
	DEVLINK_ATTR_REGION_CHUNK_DATA,         /* binary */
	DEVLINK_ATTR_REGION_CHUNK_ADDR,         /* u64 */
	DEVLINK_ATTR_REGION_CHUNK_LEN,          /* u64 */

	DEVLINK_ATTR_INFO_DRIVER_NAME,		/* string */
	DEVLINK_ATTR_INFO_SERIAL_NUMBER,	/* string */
	DEVLINK_ATTR_INFO_VERSION_FIXED,	/* nested */
	DEVLINK_ATTR_INFO_VERSION_RUNNING,	/* nested */
	DEVLINK_ATTR_INFO_VERSION_STORED,	/* nested */
	DEVLINK_ATTR_INFO_VERSION_NAME,		/* string */
	DEVLINK_ATTR_INFO_VERSION_VALUE,	/* string */

	DEVLINK_ATTR_SB_POOL_CELL_SIZE,		/* u32 */

	DEVLINK_ATTR_FMSG,			/* nested */
	DEVLINK_ATTR_FMSG_OBJ_NEST_START,	/* flag */
	DEVLINK_ATTR_FMSG_PAIR_NEST_START,	/* flag */
	DEVLINK_ATTR_FMSG_ARR_NEST_START,	/* flag */
	DEVLINK_ATTR_FMSG_NEST_END,		/* flag */
	DEVLINK_ATTR_FMSG_OBJ_NAME,		/* string */
	DEVLINK_ATTR_FMSG_OBJ_VALUE_TYPE,	/* u8 */
	DEVLINK_ATTR_FMSG_OBJ_VALUE_DATA,	/* dynamic */

	DEVLINK_ATTR_HEALTH_REPORTER,			/* nested */
	DEVLINK_ATTR_HEALTH_REPORTER_NAME,		/* string */
	DEVLINK_ATTR_HEALTH_REPORTER_STATE,		/* u8 */
	DEVLINK_ATTR_HEALTH_REPORTER_ERR_COUNT,		/* u64 */
	DEVLINK_ATTR_HEALTH_REPORTER_RECOVER_COUNT,	/* u64 */
	DEVLINK_ATTR_HEALTH_REPORTER_DUMP_TS,		/* u64 */
	DEVLINK_ATTR_HEALTH_REPORTER_GRACEFUL_PERIOD,	/* u64 */
	DEVLINK_ATTR_HEALTH_REPORTER_AUTO_RECOVER,	/* u8 */

	DEVLINK_ATTR_FLASH_UPDATE_खाता_NAME,	/* string */
	DEVLINK_ATTR_FLASH_UPDATE_COMPONENT,	/* string */
	DEVLINK_ATTR_FLASH_UPDATE_STATUS_MSG,	/* string */
	DEVLINK_ATTR_FLASH_UPDATE_STATUS_DONE,	/* u64 */
	DEVLINK_ATTR_FLASH_UPDATE_STATUS_TOTAL,	/* u64 */

	DEVLINK_ATTR_PORT_PCI_PF_NUMBER,	/* u16 */
	DEVLINK_ATTR_PORT_PCI_VF_NUMBER,	/* u16 */

	DEVLINK_ATTR_STATS,				/* nested */

	DEVLINK_ATTR_TRAP_NAME,				/* string */
	/* क्रमागत devlink_trap_action */
	DEVLINK_ATTR_TRAP_ACTION,			/* u8 */
	/* क्रमागत devlink_trap_type */
	DEVLINK_ATTR_TRAP_TYPE,				/* u8 */
	DEVLINK_ATTR_TRAP_GENERIC,			/* flag */
	DEVLINK_ATTR_TRAP_METADATA,			/* nested */
	DEVLINK_ATTR_TRAP_GROUP_NAME,			/* string */

	DEVLINK_ATTR_RELOAD_FAILED,			/* u8 0 or 1 */

	DEVLINK_ATTR_HEALTH_REPORTER_DUMP_TS_NS,	/* u64 */

	DEVLINK_ATTR_NETNS_FD,			/* u32 */
	DEVLINK_ATTR_NETNS_PID,			/* u32 */
	DEVLINK_ATTR_NETNS_ID,			/* u32 */

	DEVLINK_ATTR_HEALTH_REPORTER_AUTO_DUMP,	/* u8 */

	DEVLINK_ATTR_TRAP_POLICER_ID,			/* u32 */
	DEVLINK_ATTR_TRAP_POLICER_RATE,			/* u64 */
	DEVLINK_ATTR_TRAP_POLICER_BURST,		/* u64 */

	DEVLINK_ATTR_PORT_FUNCTION,			/* nested */

	DEVLINK_ATTR_INFO_BOARD_SERIAL_NUMBER,	/* string */

	DEVLINK_ATTR_PORT_LANES,			/* u32 */
	DEVLINK_ATTR_PORT_SPLITTABLE,			/* u8 */

	DEVLINK_ATTR_PORT_EXTERNAL,		/* u8 */
	DEVLINK_ATTR_PORT_CONTROLLER_NUMBER,	/* u32 */

	DEVLINK_ATTR_FLASH_UPDATE_STATUS_TIMEOUT,	/* u64 */
	DEVLINK_ATTR_FLASH_UPDATE_OVERWRITE_MASK,	/* bitfield32 */

	DEVLINK_ATTR_RELOAD_ACTION,		/* u8 */
	DEVLINK_ATTR_RELOAD_ACTIONS_PERFORMED,	/* bitfield32 */
	DEVLINK_ATTR_RELOAD_LIMITS,		/* bitfield32 */

	DEVLINK_ATTR_DEV_STATS,			/* nested */
	DEVLINK_ATTR_RELOAD_STATS,		/* nested */
	DEVLINK_ATTR_RELOAD_STATS_ENTRY,	/* nested */
	DEVLINK_ATTR_RELOAD_STATS_LIMIT,	/* u8 */
	DEVLINK_ATTR_RELOAD_STATS_VALUE,	/* u32 */
	DEVLINK_ATTR_REMOTE_RELOAD_STATS,	/* nested */
	DEVLINK_ATTR_RELOAD_ACTION_INFO,        /* nested */
	DEVLINK_ATTR_RELOAD_ACTION_STATS,       /* nested */

	DEVLINK_ATTR_PORT_PCI_SF_NUMBER,	/* u32 */
	/* add new attributes above here, update the policy in devlink.c */

	__DEVLINK_ATTR_MAX,
	DEVLINK_ATTR_MAX = __DEVLINK_ATTR_MAX - 1
पूर्ण;

/* Mapping between पूर्णांकernal resource described by the field and प्रणाली
 * काष्ठाure
 */
क्रमागत devlink_dpipe_field_mapping_type अणु
	DEVLINK_DPIPE_FIELD_MAPPING_TYPE_NONE,
	DEVLINK_DPIPE_FIELD_MAPPING_TYPE_IFINDEX,
पूर्ण;

/* Match type - specअगरy the type of the match */
क्रमागत devlink_dpipe_match_type अणु
	DEVLINK_DPIPE_MATCH_TYPE_FIELD_EXACT,
पूर्ण;

/* Action type - specअगरy the action type */
क्रमागत devlink_dpipe_action_type अणु
	DEVLINK_DPIPE_ACTION_TYPE_FIELD_MODIFY,
पूर्ण;

क्रमागत devlink_dpipe_field_ethernet_id अणु
	DEVLINK_DPIPE_FIELD_ETHERNET_DST_MAC,
पूर्ण;

क्रमागत devlink_dpipe_field_ipv4_id अणु
	DEVLINK_DPIPE_FIELD_IPV4_DST_IP,
पूर्ण;

क्रमागत devlink_dpipe_field_ipv6_id अणु
	DEVLINK_DPIPE_FIELD_IPV6_DST_IP,
पूर्ण;

क्रमागत devlink_dpipe_header_id अणु
	DEVLINK_DPIPE_HEADER_ETHERNET,
	DEVLINK_DPIPE_HEADER_IPV4,
	DEVLINK_DPIPE_HEADER_IPV6,
पूर्ण;

क्रमागत devlink_resource_unit अणु
	DEVLINK_RESOURCE_UNIT_ENTRY,
पूर्ण;

क्रमागत devlink_port_function_attr अणु
	DEVLINK_PORT_FUNCTION_ATTR_UNSPEC,
	DEVLINK_PORT_FUNCTION_ATTR_HW_ADDR,	/* binary */
	DEVLINK_PORT_FN_ATTR_STATE,	/* u8 */
	DEVLINK_PORT_FN_ATTR_OPSTATE,	/* u8 */

	__DEVLINK_PORT_FUNCTION_ATTR_MAX,
	DEVLINK_PORT_FUNCTION_ATTR_MAX = __DEVLINK_PORT_FUNCTION_ATTR_MAX - 1
पूर्ण;

क्रमागत devlink_port_fn_state अणु
	DEVLINK_PORT_FN_STATE_INACTIVE,
	DEVLINK_PORT_FN_STATE_ACTIVE,
पूर्ण;

/**
 * क्रमागत devlink_port_fn_opstate - indicates operational state of the function
 * @DEVLINK_PORT_FN_OPSTATE_ATTACHED: Driver is attached to the function.
 * For graceful tear करोwn of the function, after inactivation of the
 * function, user should रुको क्रम operational state to turn DETACHED.
 * @DEVLINK_PORT_FN_OPSTATE_DETACHED: Driver is detached from the function.
 * It is safe to delete the port.
 */
क्रमागत devlink_port_fn_opstate अणु
	DEVLINK_PORT_FN_OPSTATE_DETACHED,
	DEVLINK_PORT_FN_OPSTATE_ATTACHED,
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_DEVLINK_H_ */
