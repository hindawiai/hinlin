<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * vdpa device management पूर्णांकerface
 * Copyright (c) 2020 Mellanox Technologies Ltd. All rights reserved.
 */

#अगर_अघोषित _UAPI_LINUX_VDPA_H_
#घोषणा _UAPI_LINUX_VDPA_H_

#घोषणा VDPA_GENL_NAME "vdpa"
#घोषणा VDPA_GENL_VERSION 0x1

क्रमागत vdpa_command अणु
	VDPA_CMD_UNSPEC,
	VDPA_CMD_MGMTDEV_NEW,
	VDPA_CMD_MGMTDEV_GET,		/* can dump */
	VDPA_CMD_DEV_NEW,
	VDPA_CMD_DEV_DEL,
	VDPA_CMD_DEV_GET,		/* can dump */
पूर्ण;

क्रमागत vdpa_attr अणु
	VDPA_ATTR_UNSPEC,

	/* bus name (optional) + dev name together make the parent device handle */
	VDPA_ATTR_MGMTDEV_BUS_NAME,		/* string */
	VDPA_ATTR_MGMTDEV_DEV_NAME,		/* string */
	VDPA_ATTR_MGMTDEV_SUPPORTED_CLASSES,	/* u64 */

	VDPA_ATTR_DEV_NAME,			/* string */
	VDPA_ATTR_DEV_ID,			/* u32 */
	VDPA_ATTR_DEV_VENDOR_ID,		/* u32 */
	VDPA_ATTR_DEV_MAX_VQS,			/* u32 */
	VDPA_ATTR_DEV_MAX_VQ_SIZE,		/* u16 */

	/* new attributes must be added above here */
	VDPA_ATTR_MAX,
पूर्ण;

#पूर्ण_अगर
