<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005 Dmitry Torokhov
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित __LINUX_USB_INPUT_H
#घोषणा __LINUX_USB_INPUT_H

#समावेश <linux/usb.h>
#समावेश <linux/input.h>
#समावेश <यंत्र/byteorder.h>

अटल अंतरभूत व्योम
usb_to_input_id(स्थिर काष्ठा usb_device *dev, काष्ठा input_id *id)
अणु
	id->bustype = BUS_USB;
	id->venकरोr = le16_to_cpu(dev->descriptor.idVenकरोr);
	id->product = le16_to_cpu(dev->descriptor.idProduct);
	id->version = le16_to_cpu(dev->descriptor.bcdDevice);
पूर्ण

#पूर्ण_अगर /* __LINUX_USB_INPUT_H */
