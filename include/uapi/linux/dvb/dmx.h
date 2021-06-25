<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1+ WITH Linux-syscall-note */
/*
 * dmx.h
 *
 * Copyright (C) 2000 Marcus Metzler <marcus@convergence.de>
 *                  & Ralph  Metzler <ralph@convergence.de>
 *                    क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#अगर_अघोषित _UAPI_DVBDMX_H_
#घोषणा _UAPI_DVBDMX_H_

#समावेश <linux/types.h>
#अगर_अघोषित __KERNEL__
#समावेश <समय.स>
#पूर्ण_अगर


#घोषणा DMX_FILTER_SIZE 16

/**
 * क्रमागत dmx_output - Output क्रम the demux.
 *
 * @DMX_OUT_DECODER:
 *	Streaming directly to decoder.
 * @DMX_OUT_TAP:
 *	Output going to a memory buffer (to be retrieved via the पढ़ो command).
 *	Delivers the stream output to the demux device on which the ioctl
 *	is called.
 * @DMX_OUT_TS_TAP:
 *	Output multiplexed पूर्णांकo a new TS (to be retrieved by पढ़ोing from the
 *	logical DVR device). Routes output to the logical DVR device
 *	``/dev/dvb/adapter?/dvr?``, which delivers a TS multiplexed from all
 *	filters क्रम which @DMX_OUT_TS_TAP was specअगरied.
 * @DMX_OUT_TSDEMUX_TAP:
 *	Like @DMX_OUT_TS_TAP but retrieved from the DMX device.
 */
क्रमागत dmx_output अणु
	DMX_OUT_DECODER,
	DMX_OUT_TAP,
	DMX_OUT_TS_TAP,
	DMX_OUT_TSDEMUX_TAP
पूर्ण;


/**
 * क्रमागत dmx_input - Input from the demux.
 *
 * @DMX_IN_FRONTEND:	Input from a front-end device.
 * @DMX_IN_DVR:		Input from the logical DVR device.
 */
क्रमागत dmx_input अणु
	DMX_IN_FRONTEND,
	DMX_IN_DVR
पूर्ण;

/**
 * क्रमागत dmx_ts_pes - type of the PES filter.
 *
 * @DMX_PES_AUDIO0:	first audio PID. Also referred as @DMX_PES_AUDIO.
 * @DMX_PES_VIDEO0:	first video PID. Also referred as @DMX_PES_VIDEO.
 * @DMX_PES_TELETEXT0:	first teletext PID. Also referred as @DMX_PES_TELETEXT.
 * @DMX_PES_SUBTITLE0:	first subtitle PID. Also referred as @DMX_PES_SUBTITLE.
 * @DMX_PES_PCR0:	first Program Clock Reference PID.
 *			Also referred as @DMX_PES_PCR.
 *
 * @DMX_PES_AUDIO1:	second audio PID.
 * @DMX_PES_VIDEO1:	second video PID.
 * @DMX_PES_TELETEXT1:	second teletext PID.
 * @DMX_PES_SUBTITLE1:	second subtitle PID.
 * @DMX_PES_PCR1:	second Program Clock Reference PID.
 *
 * @DMX_PES_AUDIO2:	third audio PID.
 * @DMX_PES_VIDEO2:	third video PID.
 * @DMX_PES_TELETEXT2:	third teletext PID.
 * @DMX_PES_SUBTITLE2:	third subtitle PID.
 * @DMX_PES_PCR2:	third Program Clock Reference PID.
 *
 * @DMX_PES_AUDIO3:	fourth audio PID.
 * @DMX_PES_VIDEO3:	fourth video PID.
 * @DMX_PES_TELETEXT3:	fourth teletext PID.
 * @DMX_PES_SUBTITLE3:	fourth subtitle PID.
 * @DMX_PES_PCR3:	fourth Program Clock Reference PID.
 *
 * @DMX_PES_OTHER:	any other PID.
 */

क्रमागत dmx_ts_pes अणु
	DMX_PES_AUDIO0,
	DMX_PES_VIDEO0,
	DMX_PES_TELETEXT0,
	DMX_PES_SUBTITLE0,
	DMX_PES_PCR0,

	DMX_PES_AUDIO1,
	DMX_PES_VIDEO1,
	DMX_PES_TELETEXT1,
	DMX_PES_SUBTITLE1,
	DMX_PES_PCR1,

	DMX_PES_AUDIO2,
	DMX_PES_VIDEO2,
	DMX_PES_TELETEXT2,
	DMX_PES_SUBTITLE2,
	DMX_PES_PCR2,

	DMX_PES_AUDIO3,
	DMX_PES_VIDEO3,
	DMX_PES_TELETEXT3,
	DMX_PES_SUBTITLE3,
	DMX_PES_PCR3,

	DMX_PES_OTHER
पूर्ण;

#घोषणा DMX_PES_AUDIO    DMX_PES_AUDIO0
#घोषणा DMX_PES_VIDEO    DMX_PES_VIDEO0
#घोषणा DMX_PES_TELETEXT DMX_PES_TELETEXT0
#घोषणा DMX_PES_SUBTITLE DMX_PES_SUBTITLE0
#घोषणा DMX_PES_PCR      DMX_PES_PCR0



/**
 * काष्ठा dmx_filter - Specअगरies a section header filter.
 *
 * @filter: bit array with bits to be matched at the section header.
 * @mask: bits that are valid at the filter bit array.
 * @mode: mode of match: अगर bit is zero, it will match अगर equal (positive
 *	  match); अगर bit is one, it will match अगर the bit is negated.
 *
 * Note: All arrays in this काष्ठा have a size of DMX_FILTER_SIZE (16 bytes).
 */
काष्ठा dmx_filter अणु
	__u8  filter[DMX_FILTER_SIZE];
	__u8  mask[DMX_FILTER_SIZE];
	__u8  mode[DMX_FILTER_SIZE];
पूर्ण;

/**
 * काष्ठा dmx_sct_filter_params - Specअगरies a section filter.
 *
 * @pid: PID to be filtered.
 * @filter: section header filter, as defined by &काष्ठा dmx_filter.
 * @समयout: maximum समय to filter, in milliseconds.
 * @flags: extra flags क्रम the section filter.
 *
 * Carries the configuration क्रम a MPEG-TS section filter.
 *
 * The @flags can be:
 *
 *	- %DMX_CHECK_CRC - only deliver sections where the CRC check succeeded;
 *	- %DMX_ONESHOT - disable the section filter after one section
 *	  has been delivered;
 *	- %DMX_IMMEDIATE_START - Start filter immediately without requiring a
 *	  :ref:`DMX_START`.
 */
काष्ठा dmx_sct_filter_params अणु
	__u16             pid;
	काष्ठा dmx_filter filter;
	__u32             समयout;
	__u32             flags;
#घोषणा DMX_CHECK_CRC       1
#घोषणा DMX_ONESHOT         2
#घोषणा DMX_IMMEDIATE_START 4
पूर्ण;

/**
 * काष्ठा dmx_pes_filter_params - Specअगरies Packetized Elementary Stream (PES)
 *	filter parameters.
 *
 * @pid:	PID to be filtered.
 * @input:	Demux input, as specअगरied by &क्रमागत dmx_input.
 * @output:	Demux output, as specअगरied by &क्रमागत dmx_output.
 * @pes_type:	Type of the pes filter, as specअगरied by &क्रमागत dmx_pes_type.
 * @flags:	Demux PES flags.
 */
काष्ठा dmx_pes_filter_params अणु
	__u16           pid;
	क्रमागत dmx_input  input;
	क्रमागत dmx_output output;
	क्रमागत dmx_ts_pes pes_type;
	__u32           flags;
पूर्ण;

/**
 * काष्ठा dmx_stc - Stores System Time Counter (STC) inक्रमmation.
 *
 * @num: input data: number of the STC, from 0 to N.
 * @base: output: भागisor क्रम STC to get 90 kHz घड़ी.
 * @stc: output: stc in @base * 90 kHz units.
 */
काष्ठा dmx_stc अणु
	अचिन्हित पूर्णांक num;
	अचिन्हित पूर्णांक base;
	__u64 stc;
पूर्ण;

/**
 * क्रमागत dmx_buffer_flags - DMX memory-mapped buffer flags
 *
 * @DMX_BUFFER_FLAG_HAD_CRC32_DISCARD:
 *	Indicates that the Kernel discarded one or more frames due to wrong
 *	CRC32 checksum.
 * @DMX_BUFFER_FLAG_TEI:
 *	Indicates that the Kernel has detected a Transport Error indicator
 *	(TEI) on a filtered pid.
 * @DMX_BUFFER_PKT_COUNTER_MISMATCH:
 *	Indicates that the Kernel has detected a packet counter mismatch
 *	on a filtered pid.
 * @DMX_BUFFER_FLAG_DISCONTINUITY_DETECTED:
 *	Indicates that the Kernel has detected one or more frame discontinuity.
 * @DMX_BUFFER_FLAG_DISCONTINUITY_INDICATOR:
 *	Received at least one packet with a frame discontinuity indicator.
 */

क्रमागत dmx_buffer_flags अणु
	DMX_BUFFER_FLAG_HAD_CRC32_DISCARD		= 1 << 0,
	DMX_BUFFER_FLAG_TEI				= 1 << 1,
	DMX_BUFFER_PKT_COUNTER_MISMATCH			= 1 << 2,
	DMX_BUFFER_FLAG_DISCONTINUITY_DETECTED		= 1 << 3,
	DMX_BUFFER_FLAG_DISCONTINUITY_INDICATOR		= 1 << 4,
पूर्ण;

/**
 * काष्ठा dmx_buffer - dmx buffer info
 *
 * @index:	id number of the buffer
 * @bytesused:	number of bytes occupied by data in the buffer (payload);
 * @offset:	क्रम buffers with memory == DMX_MEMORY_MMAP;
 *		offset from the start of the device memory क्रम this plane,
 *		(or a "cookie" that should be passed to mmap() as offset)
 * @length:	size in bytes of the buffer
 * @flags:	bit array of buffer flags as defined by &क्रमागत dmx_buffer_flags.
 *		Filled only at &DMX_DQBUF.
 * @count:	monotonic counter क्रम filled buffers. Helps to identअगरy
 *		data stream loses. Filled only at &DMX_DQBUF.
 *
 * Contains data exchanged by application and driver using one of the streaming
 * I/O methods.
 *
 * Please notice that, क्रम &DMX_QBUF, only @index should be filled.
 * On &DMX_DQBUF calls, all fields will be filled by the Kernel.
 */
काष्ठा dmx_buffer अणु
	__u32			index;
	__u32			bytesused;
	__u32			offset;
	__u32			length;
	__u32			flags;
	__u32			count;
पूर्ण;

/**
 * काष्ठा dmx_requestbuffers - request dmx buffer inक्रमmation
 *
 * @count:	number of requested buffers,
 * @size:	size in bytes of the requested buffer
 *
 * Contains data used क्रम requesting a dmx buffer.
 * All reserved fields must be set to zero.
 */
काष्ठा dmx_requestbuffers अणु
	__u32			count;
	__u32			size;
पूर्ण;

/**
 * काष्ठा dmx_exportbuffer - export of dmx buffer as DMABUF file descriptor
 *
 * @index:	id number of the buffer
 * @flags:	flags क्रम newly created file, currently only O_CLOEXEC is
 *		supported, refer to manual of खोलो syscall क्रम more details
 * @fd:		file descriptor associated with DMABUF (set by driver)
 *
 * Contains data used क्रम exporting a dmx buffer as DMABUF file descriptor.
 * The buffer is identअगरied by a 'cookie' वापसed by DMX_QUERYBUF
 * (identical to the cookie used to mmap() the buffer to userspace). All
 * reserved fields must be set to zero. The field reserved0 is expected to
 * become a काष्ठाure 'type' allowing an alternative layout of the काष्ठाure
 * content. Thereक्रमe this field should not be used क्रम any other extensions.
 */
काष्ठा dmx_exportbuffer अणु
	__u32		index;
	__u32		flags;
	__s32		fd;
पूर्ण;

#घोषणा DMX_START                _IO('o', 41)
#घोषणा DMX_STOP                 _IO('o', 42)
#घोषणा DMX_SET_FILTER           _IOW('o', 43, काष्ठा dmx_sct_filter_params)
#घोषणा DMX_SET_PES_FILTER       _IOW('o', 44, काष्ठा dmx_pes_filter_params)
#घोषणा DMX_SET_BUFFER_SIZE      _IO('o', 45)
#घोषणा DMX_GET_PES_PIDS         _IOR('o', 47, __u16[5])
#घोषणा DMX_GET_STC              _IOWR('o', 50, काष्ठा dmx_stc)
#घोषणा DMX_ADD_PID              _IOW('o', 51, __u16)
#घोषणा DMX_REMOVE_PID           _IOW('o', 52, __u16)

#अगर !defined(__KERNEL__)

/* This is needed क्रम legacy userspace support */
प्रकार क्रमागत dmx_output dmx_output_t;
प्रकार क्रमागत dmx_input dmx_input_t;
प्रकार क्रमागत dmx_ts_pes dmx_pes_type_t;
प्रकार काष्ठा dmx_filter dmx_filter_t;

#पूर्ण_अगर

#घोषणा DMX_REQBUFS              _IOWR('o', 60, काष्ठा dmx_requestbuffers)
#घोषणा DMX_QUERYBUF             _IOWR('o', 61, काष्ठा dmx_buffer)
#घोषणा DMX_EXPBUF               _IOWR('o', 62, काष्ठा dmx_exportbuffer)
#घोषणा DMX_QBUF                 _IOWR('o', 63, काष्ठा dmx_buffer)
#घोषणा DMX_DQBUF                _IOWR('o', 64, काष्ठा dmx_buffer)

#पूर्ण_अगर /* _DVBDMX_H_ */
