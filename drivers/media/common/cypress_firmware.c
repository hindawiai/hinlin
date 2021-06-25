<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*  cypress_firmware.c is part of the DVB USB library.
 *
 * Copyright (C) 2004-6 Patrick Boettcher (patrick.boettcher@posteo.de)
 * see dvb-usb-init.c क्रम copyright inक्रमmation.
 *
 * This file contains functions क्रम करोwnloading the firmware to Cypress FX 1
 * and 2 based devices.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/firmware.h>
#समावेश "cypress_firmware.h"

काष्ठा usb_cypress_controller अणु
	u8 id;
	स्थिर अक्षर *name;	/* name of the usb controller */
	u16 cs_reg;		/* needs to be restarted,
				 * when the firmware has been करोwnloaded */
पूर्ण;

अटल स्थिर काष्ठा usb_cypress_controller cypress[] = अणु
	अणु .id = CYPRESS_AN2135, .name = "Cypress AN2135", .cs_reg = 0x7f92 पूर्ण,
	अणु .id = CYPRESS_AN2235, .name = "Cypress AN2235", .cs_reg = 0x7f92 पूर्ण,
	अणु .id = CYPRESS_FX2,    .name = "Cypress FX2",    .cs_reg = 0xe600 पूर्ण,
पूर्ण;

/*
 * load a firmware packet to the device
 */
अटल पूर्णांक usb_cypress_ग_लिखोmem(काष्ठा usb_device *udev, u16 addr, u8 *data,
		u8 len)
अणु
	वापस usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			0xa0, USB_TYPE_VENDOR, addr, 0x00, data, len, 5000);
पूर्ण

अटल पूर्णांक cypress_get_hexline(स्थिर काष्ठा firmware *fw,
				काष्ठा hexline *hx, पूर्णांक *pos)
अणु
	u8 *b = (u8 *) &fw->data[*pos];
	पूर्णांक data_offs = 4;

	अगर (*pos >= fw->size)
		वापस 0;

	स_रखो(hx, 0, माप(काष्ठा hexline));
	hx->len = b[0];

	अगर ((*pos + hx->len + 4) >= fw->size)
		वापस -EINVAL;

	hx->addr = b[1] | (b[2] << 8);
	hx->type = b[3];

	अगर (hx->type == 0x04) अणु
		/* b[4] and b[5] are the Extended linear address record data
		 * field */
		hx->addr |= (b[4] << 24) | (b[5] << 16);
	पूर्ण

	स_नकल(hx->data, &b[data_offs], hx->len);
	hx->chk = b[hx->len + data_offs];
	*pos += hx->len + 5;

	वापस *pos;
पूर्ण

पूर्णांक cypress_load_firmware(काष्ठा usb_device *udev,
		स्थिर काष्ठा firmware *fw, पूर्णांक type)
अणु
	काष्ठा hexline *hx;
	पूर्णांक ret, pos = 0;

	hx = kदो_स्मृति(माप(*hx), GFP_KERNEL);
	अगर (!hx)
		वापस -ENOMEM;

	/* stop the CPU */
	hx->data[0] = 1;
	ret = usb_cypress_ग_लिखोmem(udev, cypress[type].cs_reg, hx->data, 1);
	अगर (ret != 1) अणु
		dev_err(&udev->dev, "%s: CPU stop failed=%d\n",
				KBUILD_MODNAME, ret);
		ret = -EIO;
		जाओ err_kमुक्त;
	पूर्ण

	/* ग_लिखो firmware to memory */
	क्रम (;;) अणु
		ret = cypress_get_hexline(fw, hx, &pos);
		अगर (ret < 0)
			जाओ err_kमुक्त;
		अन्यथा अगर (ret == 0)
			अवरोध;

		ret = usb_cypress_ग_लिखोmem(udev, hx->addr, hx->data, hx->len);
		अगर (ret < 0) अणु
			जाओ err_kमुक्त;
		पूर्ण अन्यथा अगर (ret != hx->len) अणु
			dev_err(&udev->dev,
					"%s: error while transferring firmware (transferred size=%d, block size=%d)\n",
					KBUILD_MODNAME, ret, hx->len);
			ret = -EIO;
			जाओ err_kमुक्त;
		पूर्ण
	पूर्ण

	/* start the CPU */
	hx->data[0] = 0;
	ret = usb_cypress_ग_लिखोmem(udev, cypress[type].cs_reg, hx->data, 1);
	अगर (ret != 1) अणु
		dev_err(&udev->dev, "%s: CPU start failed=%d\n",
				KBUILD_MODNAME, ret);
		ret = -EIO;
		जाओ err_kमुक्त;
	पूर्ण

	ret = 0;
err_kमुक्त:
	kमुक्त(hx);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(cypress_load_firmware);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Cypress firmware download");
MODULE_LICENSE("GPL");
