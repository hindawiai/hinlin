<शैली गुरु>
/*
 * IEEE 1394 स्थिरants.
 *
 * Copyright (C) 2005-2007  Kristian Hoegsberg <krh@bitplanet.net>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित _LINUX_FIREWIRE_CONSTANTS_H
#घोषणा _LINUX_FIREWIRE_CONSTANTS_H

#घोषणा TCODE_WRITE_QUADLET_REQUEST	0x0
#घोषणा TCODE_WRITE_BLOCK_REQUEST	0x1
#घोषणा TCODE_WRITE_RESPONSE		0x2
#घोषणा TCODE_READ_QUADLET_REQUEST	0x4
#घोषणा TCODE_READ_BLOCK_REQUEST	0x5
#घोषणा TCODE_READ_QUADLET_RESPONSE	0x6
#घोषणा TCODE_READ_BLOCK_RESPONSE	0x7
#घोषणा TCODE_CYCLE_START		0x8
#घोषणा TCODE_LOCK_REQUEST		0x9
#घोषणा TCODE_STREAM_DATA		0xa
#घोषणा TCODE_LOCK_RESPONSE		0xb

#घोषणा EXTCODE_MASK_SWAP		0x1
#घोषणा EXTCODE_COMPARE_SWAP		0x2
#घोषणा EXTCODE_FETCH_ADD		0x3
#घोषणा EXTCODE_LITTLE_ADD		0x4
#घोषणा EXTCODE_BOUNDED_ADD		0x5
#घोषणा EXTCODE_WRAP_ADD		0x6
#घोषणा EXTCODE_VENDOR_DEPENDENT	0x7

/* Linux firewire-core (Juju) specअगरic tcodes */
#घोषणा TCODE_LOCK_MASK_SWAP		(0x10 | EXTCODE_MASK_SWAP)
#घोषणा TCODE_LOCK_COMPARE_SWAP		(0x10 | EXTCODE_COMPARE_SWAP)
#घोषणा TCODE_LOCK_FETCH_ADD		(0x10 | EXTCODE_FETCH_ADD)
#घोषणा TCODE_LOCK_LITTLE_ADD		(0x10 | EXTCODE_LITTLE_ADD)
#घोषणा TCODE_LOCK_BOUNDED_ADD		(0x10 | EXTCODE_BOUNDED_ADD)
#घोषणा TCODE_LOCK_WRAP_ADD		(0x10 | EXTCODE_WRAP_ADD)
#घोषणा TCODE_LOCK_VENDOR_DEPENDENT	(0x10 | EXTCODE_VENDOR_DEPENDENT)

#घोषणा RCODE_COMPLETE			0x0
#घोषणा RCODE_CONFLICT_ERROR		0x4
#घोषणा RCODE_DATA_ERROR		0x5
#घोषणा RCODE_TYPE_ERROR		0x6
#घोषणा RCODE_ADDRESS_ERROR		0x7

/* Linux firewire-core (Juju) specअगरic rcodes */
#घोषणा RCODE_SEND_ERROR		0x10
#घोषणा RCODE_CANCELLED			0x11
#घोषणा RCODE_BUSY			0x12
#घोषणा RCODE_GENERATION		0x13
#घोषणा RCODE_NO_ACK			0x14

#घोषणा SCODE_100			0x0
#घोषणा SCODE_200			0x1
#घोषणा SCODE_400			0x2
#घोषणा SCODE_800			0x3
#घोषणा SCODE_1600			0x4
#घोषणा SCODE_3200			0x5
#घोषणा SCODE_BETA			0x3

#घोषणा ACK_COMPLETE			0x1
#घोषणा ACK_PENDING			0x2
#घोषणा ACK_BUSY_X			0x4
#घोषणा ACK_BUSY_A			0x5
#घोषणा ACK_BUSY_B			0x6
#घोषणा ACK_DATA_ERROR			0xd
#घोषणा ACK_TYPE_ERROR			0xe

#घोषणा RETRY_1				0x00
#घोषणा RETRY_X				0x01
#घोषणा RETRY_A				0x02
#घोषणा RETRY_B				0x03

#पूर्ण_अगर /* _LINUX_FIREWIRE_CONSTANTS_H */
