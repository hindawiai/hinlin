<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * 	connector.h
 * 
 * 2004-2005 Copyright (c) Evgeniy Polyakov <zbr@ioremap.net>
 * All rights reserved.
 * 
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#अगर_अघोषित _UAPI__CONNECTOR_H
#घोषणा _UAPI__CONNECTOR_H

#समावेश <linux/types.h>

/*
 * Process Events connector unique ids -- used क्रम message routing
 */
#घोषणा CN_IDX_PROC			0x1
#घोषणा CN_VAL_PROC			0x1
#घोषणा CN_IDX_CIFS			0x2
#घोषणा CN_VAL_CIFS                     0x1
#घोषणा CN_W1_IDX			0x3	/* w1 communication */
#घोषणा CN_W1_VAL			0x1
#घोषणा CN_IDX_V86D			0x4
#घोषणा CN_VAL_V86D_UVESAFB		0x1
#घोषणा CN_IDX_BB			0x5	/* BlackBoard, from the TSP GPL sampling framework */
#घोषणा CN_DST_IDX			0x6
#घोषणा CN_DST_VAL			0x1
#घोषणा CN_IDX_DM			0x7	/* Device Mapper */
#घोषणा CN_VAL_DM_USERSPACE_LOG		0x1
#घोषणा CN_IDX_DRBD			0x8
#घोषणा CN_VAL_DRBD			0x1
#घोषणा CN_KVP_IDX			0x9	/* HyperV KVP */
#घोषणा CN_KVP_VAL			0x1	/* queries from the kernel */
#घोषणा CN_VSS_IDX			0xA     /* HyperV VSS */
#घोषणा CN_VSS_VAL			0x1     /* queries from the kernel */


#घोषणा CN_NETLINK_USERS		11	/* Highest index + 1 */

/*
 * Maximum connector's message size.
 */
#घोषणा CONNECTOR_MAX_MSG_SIZE		16384

/*
 * idx and val are unique identअगरiers which 
 * are used क्रम message routing and 
 * must be रेजिस्टरed in connector.h क्रम in-kernel usage.
 */

काष्ठा cb_id अणु
	__u32 idx;
	__u32 val;
पूर्ण;

काष्ठा cn_msg अणु
	काष्ठा cb_id id;

	__u32 seq;
	__u32 ack;

	__u16 len;		/* Length of the following data */
	__u16 flags;
	__u8 data[0];
पूर्ण;

#पूर्ण_अगर /* _UAPI__CONNECTOR_H */
