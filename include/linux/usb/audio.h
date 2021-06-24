<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * <linux/usb/audपन.स> -- USB Audio definitions.
 *
 * Copyright (C) 2006 Thumtronics Pty Ltd.
 * Developed क्रम Thumtronics by Grey Innovation
 * Ben Williamson <ben.williamson@greyinnovation.com>
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 2, as published by the Free Software Foundation.
 *
 * This file holds USB स्थिरants and काष्ठाures defined
 * by the USB Device Class Definition क्रम Audio Devices.
 * Comments below reference relevant sections of that करोcument:
 *
 * http://www.usb.org/developers/devclass_करोcs/audio10.pdf
 *
 * Types and defines in this file are either specअगरic to version 1.0 of
 * this standard or common क्रम newer versions.
 */
#अगर_अघोषित __LINUX_USB_AUDIO_H
#घोषणा __LINUX_USB_AUDIO_H

#समावेश <uapi/linux/usb/audपन.स>


काष्ठा usb_audio_control अणु
	काष्ठा list_head list;
	स्थिर अक्षर *name;
	u8 type;
	पूर्णांक data[5];
	पूर्णांक (*set)(काष्ठा usb_audio_control *con, u8 cmd, पूर्णांक value);
	पूर्णांक (*get)(काष्ठा usb_audio_control *con, u8 cmd);
पूर्ण;

काष्ठा usb_audio_control_selector अणु
	काष्ठा list_head list;
	काष्ठा list_head control;
	u8 id;
	स्थिर अक्षर *name;
	u8 type;
	काष्ठा usb_descriptor_header *desc;
पूर्ण;

#पूर्ण_अगर /* __LINUX_USB_AUDIO_H */
