<शैली गुरु>
/*
 * Copyright (C) 2006 - 2007 Ivo van Doorn
 * Copyright (C) 2007 Dmitry Torokhov
 * Copyright 2009 Johannes Berg <johannes@sipsolutions.net>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#अगर_अघोषित _UAPI__RFKILL_H
#घोषणा _UAPI__RFKILL_H


#समावेश <linux/types.h>

/* define userspace visible states */
#घोषणा RFKILL_STATE_SOFT_BLOCKED	0
#घोषणा RFKILL_STATE_UNBLOCKED		1
#घोषणा RFKILL_STATE_HARD_BLOCKED	2

/**
 * क्रमागत rfसमाप्त_type - type of rfसमाप्त चयन.
 *
 * @RFKILL_TYPE_ALL: toggles all चयनes (requests only - not a चयन type)
 * @RFKILL_TYPE_WLAN: चयन is on a 802.11 wireless network device.
 * @RFKILL_TYPE_BLUETOOTH: चयन is on a bluetooth device.
 * @RFKILL_TYPE_UWB: चयन is on a ultra wideband device.
 * @RFKILL_TYPE_WIMAX: चयन is on a WiMAX device.
 * @RFKILL_TYPE_WWAN: चयन is on a wireless WAN device.
 * @RFKILL_TYPE_GPS: चयन is on a GPS device.
 * @RFKILL_TYPE_FM: चयन is on a FM radio device.
 * @RFKILL_TYPE_NFC: चयन is on an NFC device.
 * @NUM_RFKILL_TYPES: number of defined rfसमाप्त types
 */
क्रमागत rfसमाप्त_type अणु
	RFKILL_TYPE_ALL = 0,
	RFKILL_TYPE_WLAN,
	RFKILL_TYPE_BLUETOOTH,
	RFKILL_TYPE_UWB,
	RFKILL_TYPE_WIMAX,
	RFKILL_TYPE_WWAN,
	RFKILL_TYPE_GPS,
	RFKILL_TYPE_FM,
	RFKILL_TYPE_NFC,
	NUM_RFKILL_TYPES,
पूर्ण;

/**
 * क्रमागत rfसमाप्त_operation - operation types
 * @RFKILL_OP_ADD: a device was added
 * @RFKILL_OP_DEL: a device was हटाओd
 * @RFKILL_OP_CHANGE: a device's state changed -- userspace changes one device
 * @RFKILL_OP_CHANGE_ALL: userspace changes all devices (of a type, or all)
 *	पूर्णांकo a state, also updating the शेष state used क्रम devices that
 *	are hot-plugged later.
 */
क्रमागत rfसमाप्त_operation अणु
	RFKILL_OP_ADD = 0,
	RFKILL_OP_DEL,
	RFKILL_OP_CHANGE,
	RFKILL_OP_CHANGE_ALL,
पूर्ण;

/**
 * क्रमागत rfसमाप्त_hard_block_reasons - hard block reasons
 * @RFKILL_HARD_BLOCK_SIGNAL: the hardware rfसमाप्त संकेत is active
 * @RFKILL_HARD_BLOCK_NOT_OWNER: the NIC is not owned by the host
 */
क्रमागत rfसमाप्त_hard_block_reasons अणु
	RFKILL_HARD_BLOCK_SIGNAL	= 1 << 0,
	RFKILL_HARD_BLOCK_NOT_OWNER	= 1 << 1,
पूर्ण;

/**
 * काष्ठा rfसमाप्त_event - events क्रम userspace on /dev/rfसमाप्त
 * @idx: index of dev rfसमाप्त
 * @type: type of the rfसमाप्त काष्ठा
 * @op: operation code
 * @hard: hard state (0/1)
 * @soft: soft state (0/1)
 *
 * Structure used क्रम userspace communication on /dev/rfसमाप्त,
 * used क्रम events from the kernel and control to the kernel.
 */
काष्ठा rfसमाप्त_event अणु
	__u32 idx;
	__u8  type;
	__u8  op;
	__u8  soft;
	__u8  hard;
पूर्ण __attribute__((packed));

/**
 * काष्ठा rfसमाप्त_event_ext - events क्रम userspace on /dev/rfसमाप्त
 * @idx: index of dev rfसमाप्त
 * @type: type of the rfसमाप्त काष्ठा
 * @op: operation code
 * @hard: hard state (0/1)
 * @soft: soft state (0/1)
 * @hard_block_reasons: valid अगर hard is set. One or several reasons from
 *	&क्रमागत rfसमाप्त_hard_block_reasons.
 *
 * Structure used क्रम userspace communication on /dev/rfसमाप्त,
 * used क्रम events from the kernel and control to the kernel.
 *
 * See the extensibility करोcs below.
 */
काष्ठा rfसमाप्त_event_ext अणु
	__u32 idx;
	__u8  type;
	__u8  op;
	__u8  soft;
	__u8  hard;

	/*
	 * older kernels will accept/send only up to this poपूर्णांक,
	 * and अगर extended further up to any chunk marked below
	 */

	__u8  hard_block_reasons;
पूर्ण __attribute__((packed));

/**
 * DOC: Extensibility
 *
 * Originally, we had planned to allow backward and क्रमward compatible
 * changes by just adding fields at the end of the काष्ठाure that are
 * then not reported on older kernels on पढ़ो(), and not written to by
 * older kernels on ग_लिखो(), with the kernel reporting the size it did
 * accept as the result.
 *
 * This would have allowed userspace to detect on पढ़ो() and ग_लिखो()
 * which kernel काष्ठाure version it was dealing with, and अगर was just
 * recompiled it would have gotten the new fields, but obviously not
 * accessed them, but things should've जारीd to work.
 *
 * Unक्रमtunately, जबतक actually exercising this mechanism to add the
 * hard block reasons field, we found that userspace (notably प्रणालीd)
 * did all kinds of fun things not in line with this scheme:
 *
 * 1. treat the (expected) लघु ग_लिखोs as an error;
 * 2. ask to पढ़ो माप(काष्ठा rfसमाप्त_event) but then compare the
 *    actual वापस value to RFKILL_EVENT_SIZE_V1 and treat any
 *    mismatch as an error.
 *
 * As a consequence, just recompiling with a new काष्ठा version caused
 * things to no दीर्घer work correctly on old and new kernels.
 *
 * Hence, we've rolled back &काष्ठा rfसमाप्त_event to the original version
 * and added &काष्ठा rfसमाप्त_event_ext. This effectively reverts to the
 * old behaviour क्रम all userspace, unless it explicitly opts in to the
 * rules outlined here by using the new &काष्ठा rfसमाप्त_event_ext.
 *
 * Userspace using &काष्ठा rfसमाप्त_event_ext must adhere to the following
 * rules
 *
 * 1. accept लघु ग_लिखोs, optionally using them to detect that it's
 *    running on an older kernel;
 * 2. accept लघु पढ़ोs, knowing that this means it's running on an
 *    older kernel;
 * 3. treat पढ़ोs that are as दीर्घ as requested as acceptable, not
 *    checking against RFKILL_EVENT_SIZE_V1 or such.
 */
#घोषणा RFKILL_EVENT_SIZE_V1	माप(काष्ठा rfसमाप्त_event)

/* ioctl क्रम turning off rfसमाप्त-input (अगर present) */
#घोषणा RFKILL_IOC_MAGIC	'R'
#घोषणा RFKILL_IOC_NOINPUT	1
#घोषणा RFKILL_IOCTL_NOINPUT	_IO(RFKILL_IOC_MAGIC, RFKILL_IOC_NOINPUT)

/* and that's all userspace माला_लो */

#पूर्ण_अगर /* _UAPI__RFKILL_H */
