<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2004-6 Patrick Boettcher (patrick.boettcher@posteo.de)
 * see dvb-usb-init.c क्रम copyright inक्रमmation.
 *
 * This file contains functions क्रम करोwnloading the firmware to Cypress FX 1
 * and 2 based devices.
 *
 */

#अगर_अघोषित CYPRESS_FIRMWARE_H
#घोषणा CYPRESS_FIRMWARE_H

#घोषणा CYPRESS_AN2135  0
#घोषणा CYPRESS_AN2235  1
#घोषणा CYPRESS_FX2     2

/* commonly used firmware करोwnload types and function */
काष्ठा hexline अणु
	u8 len;
	u32 addr;
	u8 type;
	u8 data[255];
	u8 chk;
पूर्ण;

पूर्णांक cypress_load_firmware(काष्ठा usb_device *, स्थिर काष्ठा firmware *, पूर्णांक);

#पूर्ण_अगर
