<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * cmt-speech पूर्णांकerface definitions
 *
 * Copyright (C) 2008,2009,2010 Nokia Corporation. All rights reserved.
 *
 * Contact: Kai Vehmanen <kai.vehmanen@nokia.com>
 * Original author: Peter Ujfalusi <peter.ujfalusi@nokia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA
 * 02110-1301 USA
 */

#अगर_अघोषित _CS_PROTOCOL_H
#घोषणा _CS_PROTOCOL_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/* अक्षरdev parameters */
#घोषणा CS_DEV_खाता_NAME		"/dev/cmt_speech"

/* user-space API versioning */
#घोषणा CS_IF_VERSION			2

/* APE kernel <-> user space messages */
#घोषणा CS_CMD_SHIFT			28
#घोषणा CS_DOMAIN_SHIFT			24

#घोषणा CS_CMD_MASK			0xff000000
#घोषणा CS_PARAM_MASK			0xffffff

#घोषणा CS_CMD(id, करोm) \
	(((id) << CS_CMD_SHIFT) | ((करोm) << CS_DOMAIN_SHIFT))

#घोषणा CS_ERROR			CS_CMD(1, 0)
#घोषणा CS_RX_DATA_RECEIVED		CS_CMD(2, 0)
#घोषणा CS_TX_DATA_READY		CS_CMD(3, 0)
#घोषणा CS_TX_DATA_SENT			CS_CMD(4, 0)

/* params to CS_ERROR indication */
#घोषणा CS_ERR_PEER_RESET		0

/* ioctl पूर्णांकerface */

/* parameters to CS_CONFIG_BUFS ioctl */
#घोषणा CS_FEAT_TSTAMP_RX_CTRL		(1 << 0)
#घोषणा CS_FEAT_ROLLING_RX_COUNTER	(2 << 0)

/* parameters to CS_GET_STATE ioctl */
#घोषणा CS_STATE_CLOSED			0
#घोषणा CS_STATE_OPENED			1 /* resource allocated */
#घोषणा CS_STATE_CONFIGURED		2 /* data path active */

/* maximum number of TX/RX buffers */
#घोषणा CS_MAX_BUFFERS_SHIFT		4
#घोषणा CS_MAX_BUFFERS			(1 << CS_MAX_BUFFERS_SHIFT)

/* Parameters क्रम setting up the data buffers */
काष्ठा cs_buffer_config अणु
	__u32 rx_bufs;	/* number of RX buffer slots */
	__u32 tx_bufs;	/* number of TX buffer slots */
	__u32 buf_size;	/* bytes */
	__u32 flags;	/* see CS_FEAT_* */
	__u32 reserved[4];
पूर्ण;

/*
 * काष्ठा क्रम monotonic बारtamp taken when the
 * last control command was received
 */
काष्ठा cs_बारtamp अणु
	__u32 tv_sec;  /* seconds */
	__u32 tv_nsec; /* nanoseconds */
पूर्ण;

/*
 * Struct describing the layout and contents of the driver mmap area.
 * This inक्रमmation is meant as पढ़ो-only inक्रमmation क्रम the application.
 */
काष्ठा cs_mmap_config_block अणु
	__u32 reserved1;
	__u32 buf_size;		/* 0=disabled, otherwise the transfer size */
	__u32 rx_bufs;		/* # of RX buffers */
	__u32 tx_bufs;		/* # of TX buffers */
	__u32 reserved2;
	/* array of offsets within the mmap area क्रम each RX and TX buffer */
	__u32 rx_offsets[CS_MAX_BUFFERS];
	__u32 tx_offsets[CS_MAX_BUFFERS];
	__u32 rx_ptr;
	__u32 rx_ptr_boundary;
	__u32 reserved3[2];
	/* enabled with CS_FEAT_TSTAMP_RX_CTRL */
	काष्ठा cs_बारtamp tstamp_rx_ctrl;
पूर्ण;

#घोषणा CS_IO_MAGIC		'C'

#घोषणा CS_IOW(num, dtype)	_IOW(CS_IO_MAGIC, num, dtype)
#घोषणा CS_IOR(num, dtype)	_IOR(CS_IO_MAGIC, num, dtype)
#घोषणा CS_IOWR(num, dtype)	_IOWR(CS_IO_MAGIC, num, dtype)
#घोषणा CS_IO(num)		_IO(CS_IO_MAGIC, num)

#घोषणा CS_GET_STATE		CS_IOR(21, अचिन्हित पूर्णांक)
#घोषणा CS_SET_WAKELINE		CS_IOW(23, अचिन्हित पूर्णांक)
#घोषणा CS_GET_IF_VERSION	CS_IOR(30, अचिन्हित पूर्णांक)
#घोषणा CS_CONFIG_BUFS		CS_IOW(31, काष्ठा cs_buffer_config)

#पूर्ण_अगर /* _CS_PROTOCOL_H */
