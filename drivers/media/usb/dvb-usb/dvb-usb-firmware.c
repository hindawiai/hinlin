<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* dvb-usb-firmware.c is part of the DVB USB library.
 *
 * Copyright (C) 2004-6 Patrick Boettcher (patrick.boettcher@posteo.de)
 * see dvb-usb-init.c क्रम copyright inक्रमmation.
 *
 * This file contains functions क्रम करोwnloading the firmware to Cypress FX 1 and 2 based devices.
 *
 * FIXME: This part करोes actually not beदीर्घ to dvb-usb, but to the usb-subप्रणाली.
 */
#समावेश "dvb-usb-common.h"

#समावेश <linux/usb.h>

काष्ठा usb_cypress_controller अणु
	पूर्णांक id;
	स्थिर अक्षर *name;       /* name of the usb controller */
	u16 cpu_cs_रेजिस्टर;    /* needs to be restarted, when the firmware has been करोwnloaded. */
पूर्ण;

अटल काष्ठा usb_cypress_controller cypress[] = अणु
	अणु .id = DEVICE_SPECIFIC, .name = "Device specific", .cpu_cs_रेजिस्टर = 0 पूर्ण,
	अणु .id = CYPRESS_AN2135,  .name = "Cypress AN2135",  .cpu_cs_रेजिस्टर = 0x7f92 पूर्ण,
	अणु .id = CYPRESS_AN2235,  .name = "Cypress AN2235",  .cpu_cs_रेजिस्टर = 0x7f92 पूर्ण,
	अणु .id = CYPRESS_FX2,     .name = "Cypress FX2",     .cpu_cs_रेजिस्टर = 0xe600 पूर्ण,
पूर्ण;

/*
 * load a firmware packet to the device
 */
अटल पूर्णांक usb_cypress_ग_लिखोmem(काष्ठा usb_device *udev,u16 addr,u8 *data, u8 len)
अणु
	वापस usb_control_msg(udev, usb_sndctrlpipe(udev,0),
			0xa0, USB_TYPE_VENDOR, addr, 0x00, data, len, 5000);
पूर्ण

पूर्णांक usb_cypress_load_firmware(काष्ठा usb_device *udev, स्थिर काष्ठा firmware *fw, पूर्णांक type)
अणु
	काष्ठा hexline *hx;
	u8 *buf;
	पूर्णांक ret, pos = 0;
	u16 cpu_cs_रेजिस्टर = cypress[type].cpu_cs_रेजिस्टर;

	buf = kदो_स्मृति(माप(*hx), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	hx = (काष्ठा hexline *)buf;

	/* stop the CPU */
	buf[0] = 1;
	अगर (usb_cypress_ग_लिखोmem(udev, cpu_cs_रेजिस्टर, buf, 1) != 1)
		err("could not stop the USB controller CPU.");

	जबतक ((ret = dvb_usb_get_hexline(fw, hx, &pos)) > 0) अणु
		deb_fw("writing to address 0x%04x (buffer: 0x%02x %02x)\n", hx->addr, hx->len, hx->chk);
		ret = usb_cypress_ग_लिखोmem(udev, hx->addr, hx->data, hx->len);

		अगर (ret != hx->len) अणु
			err("error while transferring firmware (transferred size: %d, block size: %d)",
				ret, hx->len);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ret < 0) अणु
		err("firmware download failed at %d with %d",pos,ret);
		kमुक्त(buf);
		वापस ret;
	पूर्ण

	अगर (ret == 0) अणु
		/* restart the CPU */
		buf[0] = 0;
		अगर (usb_cypress_ग_लिखोmem(udev, cpu_cs_रेजिस्टर, buf, 1) != 1) अणु
			err("could not restart the USB controller CPU.");
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा
		ret = -EIO;

	kमुक्त(buf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(usb_cypress_load_firmware);

पूर्णांक dvb_usb_करोwnload_firmware(काष्ठा usb_device *udev,
			      स्थिर काष्ठा dvb_usb_device_properties *props)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा firmware *fw = शून्य;

	अगर ((ret = request_firmware(&fw, props->firmware, &udev->dev)) != 0) अणु
		err("did not find the firmware file '%s' (status %d). You can use <kernel_dir>/scripts/get_dvb_firmware to get the firmware",
			props->firmware,ret);
		वापस ret;
	पूर्ण

	info("downloading firmware from file '%s'",props->firmware);

	चयन (props->usb_ctrl) अणु
		हाल CYPRESS_AN2135:
		हाल CYPRESS_AN2235:
		हाल CYPRESS_FX2:
			ret = usb_cypress_load_firmware(udev, fw, props->usb_ctrl);
			अवरोध;
		हाल DEVICE_SPECIFIC:
			अगर (props->करोwnload_firmware)
				ret = props->करोwnload_firmware(udev,fw);
			अन्यथा अणु
				err("BUG: driver didn't specified a download_firmware-callback, although it claims to have a DEVICE_SPECIFIC one.");
				ret = -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
	पूर्ण

	release_firmware(fw);
	वापस ret;
पूर्ण

पूर्णांक dvb_usb_get_hexline(स्थिर काष्ठा firmware *fw, काष्ठा hexline *hx,
			       पूर्णांक *pos)
अणु
	u8 *b = (u8 *) &fw->data[*pos];
	पूर्णांक data_offs = 4;
	अगर (*pos >= fw->size)
		वापस 0;

	स_रखो(hx,0,माप(काष्ठा hexline));

	hx->len  = b[0];

	अगर ((*pos + hx->len + 4) >= fw->size)
		वापस -EINVAL;

	hx->addr = b[1] | (b[2] << 8);
	hx->type = b[3];

	अगर (hx->type == 0x04) अणु
		/* b[4] and b[5] are the Extended linear address record data field */
		hx->addr |= (b[4] << 24) | (b[5] << 16);
/*		hx->len -= 2;
		data_offs += 2; */
	पूर्ण
	स_नकल(hx->data,&b[data_offs],hx->len);
	hx->chk = b[hx->len + data_offs];

	*pos += hx->len + 5;

	वापस *pos;
पूर्ण
EXPORT_SYMBOL(dvb_usb_get_hexline);
