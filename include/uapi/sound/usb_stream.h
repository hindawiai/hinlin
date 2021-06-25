<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright (C) 2007, 2008 Karsten Wiese <fzu@wemgehoertderstaat.de>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software Foundation,
 * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित _UAPI__SOUND_USB_STREAM_H
#घोषणा _UAPI__SOUND_USB_STREAM_H

#घोषणा USB_STREAM_INTERFACE_VERSION 2

#घोषणा SNDRV_USB_STREAM_IOCTL_SET_PARAMS \
	_IOW('H', 0x90, काष्ठा usb_stream_config)

काष्ठा usb_stream_packet अणु
	अचिन्हित offset;
	अचिन्हित length;
पूर्ण;


काष्ठा usb_stream_config अणु
	अचिन्हित version;
	अचिन्हित sample_rate;
	अचिन्हित period_frames;
	अचिन्हित frame_size;
पूर्ण;

काष्ठा usb_stream अणु
	काष्ठा usb_stream_config cfg;
	अचिन्हित पढ़ो_size;
	अचिन्हित ग_लिखो_size;

	पूर्णांक period_size;

	अचिन्हित state;

	पूर्णांक idle_insize;
	पूर्णांक idle_outsize;
	पूर्णांक sync_packet;
	अचिन्हित insize_करोne;
	अचिन्हित periods_करोne;
	अचिन्हित periods_polled;

	काष्ठा usb_stream_packet outpacket[2];
	अचिन्हित		 inpackets;
	अचिन्हित		 inpacket_head;
	अचिन्हित		 inpacket_split;
	अचिन्हित		 inpacket_split_at;
	अचिन्हित		 next_inpacket_split;
	अचिन्हित		 next_inpacket_split_at;
	काष्ठा usb_stream_packet inpacket[0];
पूर्ण;

क्रमागत usb_stream_state अणु
	usb_stream_invalid,
	usb_stream_stopped,
	usb_stream_sync0,
	usb_stream_sync1,
	usb_stream_पढ़ोy,
	usb_stream_running,
	usb_stream_xrun,
पूर्ण;

#पूर्ण_अगर /* _UAPI__SOUND_USB_STREAM_H */
