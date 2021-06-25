<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#अगर_अघोषित CAIF_DEVICE_H_
#घोषणा CAIF_DEVICE_H_
#समावेश <linux/kernel.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/caअगर/caअगर_socket.h>
#समावेश <net/caअगर/caअगर_device.h>

/**
 * काष्ठा caअगर_dev_common - data shared between CAIF drivers and stack.
 * @flowctrl:		Flow Control callback function. This function is
 *                      supplied by CAIF Core Stack and is used by CAIF
 *                      Link Layer to send flow-stop to CAIF Core.
 *                      The flow inक्रमmation will be distributed to all
 *                      clients of CAIF.
 *
 * @link_select:	Profile of device, either high-bandwidth or
 *			low-latency. This member is set by CAIF Link
 *			Layer Device in	order to indicate अगर this device
 *			is a high bandwidth or low latency device.
 *
 * @use_frag:		CAIF Frames may be fragmented.
 *			Is set by CAIF Link Layer in order to indicate अगर the
 *			पूर्णांकerface receives fragmented frames that must be
 *			assembled by CAIF Core Layer.
 *
 * @use_fcs:		Indicate अगर Frame CheckSum (fcs) is used.
 *			Is set अगर the physical पूर्णांकerface is
 *			using Frame Checksum on the CAIF Frames.
 *
 * @use_stx:		Indicate STart of frame eXtension (stx) in use.
 *			Is set अगर the CAIF Link Layer expects
 *			CAIF Frames to start with the STX byte.
 *
 * This काष्ठाure is shared between the CAIF drivers and the CAIF stack.
 * It is used by the device to रेजिस्टर its behavior.
 * CAIF Core layer must set the member flowctrl in order to supply
 * CAIF Link Layer with the flow control function.
 *
 */
 काष्ठा caअगर_dev_common अणु
	व्योम (*flowctrl)(काष्ठा net_device *net, पूर्णांक on);
	क्रमागत caअगर_link_selector link_select;
	पूर्णांक use_frag;
	पूर्णांक use_fcs;
	पूर्णांक use_stx;
पूर्ण;

#पूर्ण_अगर	/* CAIF_DEVICE_H_ */
