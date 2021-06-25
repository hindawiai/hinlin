<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00dump
	Abstract:
		Data काष्ठाures क्रम the rt2x00debug & userspace.

		The declarations in this file can be used by both rt2x00
		and userspace and thereक्रमe should be kept together in
		this file.
 */

#अगर_अघोषित RT2X00DUMP_H
#घोषणा RT2X00DUMP_H

/**
 * DOC: Introduction
 *
 * This header is पूर्णांकended to be exported to userspace,
 * to make the काष्ठाures and क्रमागतerations available to userspace
 * applications. This means that all data types should be exportable.
 *
 * When rt2x00 is compiled with debugfs support enabled,
 * it is possible to capture all data coming in and out of the device
 * by पढ़ोing the frame dump file. This file can have only a single पढ़ोer.
 * The following frames will be reported:
 *   - All incoming frames (rx)
 *   - All outgoing frames (tx, including beacon and atim)
 *   - All completed frames (txकरोne including atim)
 *
 * The data is send to the file using the following क्रमmat:
 *
 *   [rt2x00dump header][hardware descriptor][ieee802.11 frame]
 *
 * rt2x00dump header: The description of the dumped frame, as well as
 *	additional inक्रमmation useful क्रम debugging. See &rt2x00dump_hdr.
 * hardware descriptor: Descriptor that was used to receive or transmit
 *	the frame.
 * ieee802.11 frame: The actual frame that was received or transmitted.
 */

/**
 * क्रमागत rt2x00_dump_type - Frame type
 *
 * These values are used क्रम the @type member of &rt2x00dump_hdr.
 * @DUMP_FRAME_RXDONE: This frame has been received by the hardware.
 * @DUMP_FRAME_TX: This frame is queued क्रम transmission to the hardware.
 * @DUMP_FRAME_TXDONE: This frame indicates the device has handled
 *	the tx event which has either succeeded or failed. A frame
 *	with this type should also have been reported with as a
 *	%DUMP_FRAME_TX frame.
 * @DUMP_FRAME_BEACON: This beacon frame is queued क्रम transmission to the
 *	hardware.
 */
क्रमागत rt2x00_dump_type अणु
	DUMP_FRAME_RXDONE = 1,
	DUMP_FRAME_TX = 2,
	DUMP_FRAME_TXDONE = 3,
	DUMP_FRAME_BEACON = 4,
पूर्ण;

/**
 * काष्ठा rt2x00dump_hdr - Dump frame header
 *
 * Each frame dumped to the debugfs file starts with this header
 * attached. This header contains the description of the actual
 * frame which was dumped.
 *
 * New fields inside the काष्ठाure must be appended to the end of
 * the काष्ठाure. This way userspace tools compiled क्रम earlier
 * header versions can still correctly handle the frame dump
 * (although they will not handle all data passed to them in the dump).
 *
 * @version: Header version should always be set to %DUMP_HEADER_VERSION.
 *	This field must be checked by userspace to determine अगर it can
 *	handle this frame.
 * @header_length: The length of the &rt2x00dump_hdr काष्ठाure. This is
 *	used क्रम compatibility reasons so userspace can easily determine
 *	the location of the next field in the dump.
 * @desc_length: The length of the device descriptor.
 * @data_length: The length of the frame data (including the ieee802.11 header.
 * @chip_rt: RT chipset
 * @chip_rf: RF chipset
 * @chip_rev: Chipset revision
 * @type: The frame type (&rt2x00_dump_type)
 * @queue_index: The index number of the data queue.
 * @entry_index: The index number of the entry inside the data queue.
 * @बारtamp_sec: Timestamp - seconds
 * @बारtamp_usec: Timestamp - microseconds
 */
काष्ठा rt2x00dump_hdr अणु
	__le32 version;
#घोषणा DUMP_HEADER_VERSION	3

	__le32 header_length;
	__le32 desc_length;
	__le32 data_length;

	__le16 chip_rt;
	__le16 chip_rf;
	__le16 chip_rev;

	__le16 type;
	__u8 queue_index;
	__u8 entry_index;

	__le32 बारtamp_sec;
	__le32 बारtamp_usec;
पूर्ण;

#पूर्ण_अगर /* RT2X00DUMP_H */
