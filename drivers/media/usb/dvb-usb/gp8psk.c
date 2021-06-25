<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB compliant Linux driver क्रम the
 *  - GENPIX 8pks/qpsk/DCII USB2.0 DVB-S module
 *
 * Copyright (C) 2006,2007 Alan Nisota (alannisota@gmail.com)
 * Copyright (C) 2006,2007 Genpix Electronics (genpix@genpix-electronics.com)
 *
 * Thanks to GENPIX क्रम the sample code used to implement this module.
 *
 * This module is based off the vp7045 and vp702x modules
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "gp8psk.h"
#समावेश "gp8psk-fe.h"

/* debug */
अटल अक्षर bcm4500_firmware[] = "dvb-usb-gp8psk-02.fw";
पूर्णांक dvb_usb_gp8psk_debug;
module_param_named(debug,dvb_usb_gp8psk_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info,xfer=2,rc=4 (or-able))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

काष्ठा gp8psk_state अणु
	अचिन्हित अक्षर data[80];
पूर्ण;

अटल पूर्णांक gp8psk_usb_in_op(काष्ठा dvb_usb_device *d, u8 req, u16 value,
			    u16 index, u8 *b, पूर्णांक blen)
अणु
	काष्ठा gp8psk_state *st = d->priv;
	पूर्णांक ret = 0,try = 0;

	अगर (blen > माप(st->data))
		वापस -EIO;

	अगर ((ret = mutex_lock_पूर्णांकerruptible(&d->usb_mutex)))
		वापस ret;

	जबतक (ret >= 0 && ret != blen && try < 3) अणु
		ret = usb_control_msg(d->udev,
			usb_rcvctrlpipe(d->udev,0),
			req,
			USB_TYPE_VENDOR | USB_सूची_IN,
			value, index, st->data, blen,
			2000);
		deb_info("reading number %d (ret: %d)\n",try,ret);
		try++;
	पूर्ण

	अगर (ret < 0 || ret != blen) अणु
		warn("usb in %d operation failed.", req);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		ret = 0;
		स_नकल(b, st->data, blen);
	पूर्ण

	deb_xfer("in: req. %x, val: %x, ind: %x, buffer: ",req,value,index);
	debug_dump(b,blen,deb_xfer);

	mutex_unlock(&d->usb_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक gp8psk_usb_out_op(काष्ठा dvb_usb_device *d, u8 req, u16 value,
			     u16 index, u8 *b, पूर्णांक blen)
अणु
	काष्ठा gp8psk_state *st = d->priv;
	पूर्णांक ret;

	deb_xfer("out: req. %x, val: %x, ind: %x, buffer: ",req,value,index);
	debug_dump(b,blen,deb_xfer);

	अगर (blen > माप(st->data))
		वापस -EIO;

	अगर ((ret = mutex_lock_पूर्णांकerruptible(&d->usb_mutex)))
		वापस ret;

	स_नकल(st->data, b, blen);
	अगर (usb_control_msg(d->udev,
			usb_sndctrlpipe(d->udev,0),
			req,
			USB_TYPE_VENDOR | USB_सूची_OUT,
			value, index, st->data, blen,
			2000) != blen) अणु
		warn("usb out operation failed.");
		ret = -EIO;
	पूर्ण अन्यथा
		ret = 0;
	mutex_unlock(&d->usb_mutex);

	वापस ret;
पूर्ण


अटल पूर्णांक gp8psk_get_fw_version(काष्ठा dvb_usb_device *d, u8 *fw_vers)
अणु
	वापस gp8psk_usb_in_op(d, GET_FW_VERS, 0, 0, fw_vers, 6);
पूर्ण

अटल पूर्णांक gp8psk_get_fpga_version(काष्ठा dvb_usb_device *d, u8 *fpga_vers)
अणु
	वापस gp8psk_usb_in_op(d, GET_FPGA_VERS, 0, 0, fpga_vers, 1);
पूर्ण

अटल व्योम gp8psk_info(काष्ठा dvb_usb_device *d)
अणु
	u8 fpga_vers, fw_vers[6];

	अगर (!gp8psk_get_fw_version(d, fw_vers))
		info("FW Version = %i.%02i.%i (0x%x)  Build %4i/%02i/%02i",
		fw_vers[2], fw_vers[1], fw_vers[0], GP8PSK_FW_VERS(fw_vers),
		2000 + fw_vers[5], fw_vers[4], fw_vers[3]);
	अन्यथा
		info("failed to get FW version");

	अगर (!gp8psk_get_fpga_version(d, &fpga_vers))
		info("FPGA Version = %i", fpga_vers);
	अन्यथा
		info("failed to get FPGA version");
पूर्ण

अटल पूर्णांक gp8psk_load_bcm4500fw(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा firmware *fw = शून्य;
	स्थिर u8 *ptr;
	u8 *buf;
	अगर ((ret = request_firmware(&fw, bcm4500_firmware,
					&d->udev->dev)) != 0) अणु
		err("did not find the bcm4500 firmware file '%s' (status %d). You can use <kernel_dir>/scripts/get_dvb_firmware to get the firmware",
			bcm4500_firmware,ret);
		वापस ret;
	पूर्ण

	ret = -EINVAL;

	अगर (gp8psk_usb_out_op(d, LOAD_BCM4500,1,0,शून्य, 0))
		जाओ out_rel_fw;

	info("downloading bcm4500 firmware from file '%s'",bcm4500_firmware);

	ptr = fw->data;
	buf = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ out_rel_fw;
	पूर्ण

	जबतक (ptr[0] != 0xff) अणु
		u16 buflen = ptr[0] + 4;
		अगर (ptr + buflen >= fw->data + fw->size) अणु
			err("failed to load bcm4500 firmware.");
			जाओ out_मुक्त;
		पूर्ण
		अगर (buflen > 64) अणु
			err("firmware chunk size bigger than 64 bytes.");
			जाओ out_मुक्त;
		पूर्ण

		स_नकल(buf, ptr, buflen);
		अगर (dvb_usb_generic_ग_लिखो(d, buf, buflen)) अणु
			err("failed to load bcm4500 firmware.");
			जाओ out_मुक्त;
		पूर्ण
		ptr += buflen;
	पूर्ण

	ret = 0;

out_मुक्त:
	kमुक्त(buf);
out_rel_fw:
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल पूर्णांक gp8psk_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	u8 status = 0, buf;
	पूर्णांक gp_product_id = le16_to_cpu(d->udev->descriptor.idProduct);

	अगर (onoff) अणु
		gp8psk_usb_in_op(d, GET_8PSK_CONFIG,0,0,&status,1);
		अगर (! (status & bm8pskStarted)) अणु  /* started */
			अगर(gp_product_id == USB_PID_GENPIX_SKYWALKER_CW3K)
				gp8psk_usb_out_op(d, CW3K_INIT, 1, 0, शून्य, 0);
			अगर (gp8psk_usb_in_op(d, BOOT_8PSK, 1, 0, &buf, 1))
				वापस -EINVAL;
			gp8psk_info(d);
		पूर्ण

		अगर (gp_product_id == USB_PID_GENPIX_8PSK_REV_1_WARM)
			अगर (! (status & bm8pskFW_Loaded)) /* BCM4500 firmware loaded */
				अगर(gp8psk_load_bcm4500fw(d))
					वापस -EINVAL;

		अगर (! (status & bmIntersilOn)) /* LNB Power */
			अगर (gp8psk_usb_in_op(d, START_INTERSIL, 1, 0,
					&buf, 1))
				वापस -EINVAL;

		/* Set DVB mode to 1 */
		अगर (gp_product_id == USB_PID_GENPIX_8PSK_REV_1_WARM)
			अगर (gp8psk_usb_out_op(d, SET_DVB_MODE, 1, 0, शून्य, 0))
				वापस -EINVAL;
		/* Abort possible TS (अगर previous tune crashed) */
		अगर (gp8psk_usb_out_op(d, ARM_TRANSFER, 0, 0, शून्य, 0))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Turn off LNB घातer */
		अगर (gp8psk_usb_in_op(d, START_INTERSIL, 0, 0, &buf, 1))
			वापस -EINVAL;
		/* Turn off 8psk घातer */
		अगर (gp8psk_usb_in_op(d, BOOT_8PSK, 0, 0, &buf, 1))
			वापस -EINVAL;
		अगर(gp_product_id == USB_PID_GENPIX_SKYWALKER_CW3K)
			gp8psk_usb_out_op(d, CW3K_INIT, 0, 0, शून्य, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gp8psk_bcm4500_reload(काष्ठा dvb_usb_device *d)
अणु
	u8 buf;
	पूर्णांक gp_product_id = le16_to_cpu(d->udev->descriptor.idProduct);

	deb_xfer("reloading firmware\n");

	/* Turn off 8psk घातer */
	अगर (gp8psk_usb_in_op(d, BOOT_8PSK, 0, 0, &buf, 1))
		वापस -EINVAL;
	/* Turn On 8psk घातer */
	अगर (gp8psk_usb_in_op(d, BOOT_8PSK, 1, 0, &buf, 1))
		वापस -EINVAL;
	/* load BCM4500 firmware */
	अगर (gp_product_id == USB_PID_GENPIX_8PSK_REV_1_WARM)
		अगर (gp8psk_load_bcm4500fw(d))
			वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक gp8psk_streaming_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	वापस gp8psk_usb_out_op(adap->dev, ARM_TRANSFER, onoff, 0 , शून्य, 0);
पूर्ण

/* Callbacks क्रम gp8psk-fe.c */

अटल पूर्णांक gp8psk_fe_in(व्योम *priv, u8 req, u16 value,
			    u16 index, u8 *b, पूर्णांक blen)
अणु
	काष्ठा dvb_usb_device *d = priv;

	वापस gp8psk_usb_in_op(d, req, value, index, b, blen);
पूर्ण

अटल पूर्णांक gp8psk_fe_out(व्योम *priv, u8 req, u16 value,
			    u16 index, u8 *b, पूर्णांक blen)
अणु
	काष्ठा dvb_usb_device *d = priv;

	वापस gp8psk_usb_out_op(d, req, value, index, b, blen);
पूर्ण

अटल पूर्णांक gp8psk_fe_reload(व्योम *priv)
अणु
	काष्ठा dvb_usb_device *d = priv;

	वापस gp8psk_bcm4500_reload(d);
पूर्ण

अटल स्थिर काष्ठा gp8psk_fe_ops gp8psk_fe_ops = अणु
	.in = gp8psk_fe_in,
	.out = gp8psk_fe_out,
	.reload = gp8psk_fe_reload,
पूर्ण;

अटल पूर्णांक gp8psk_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap->dev;
	पूर्णांक id = le16_to_cpu(d->udev->descriptor.idProduct);
	पूर्णांक is_rev1;

	is_rev1 = (id == USB_PID_GENPIX_8PSK_REV_1_WARM) ? true : false;

	adap->fe_adap[0].fe = dvb_attach(gp8psk_fe_attach,
					 &gp8psk_fe_ops, d, is_rev1);
	वापस 0;
पूर्ण

अटल काष्ठा dvb_usb_device_properties gp8psk_properties;

अटल पूर्णांक gp8psk_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	ret = dvb_usb_device_init(पूर्णांकf, &gp8psk_properties,
				  THIS_MODULE, शून्य, adapter_nr);
	अगर (ret == 0) अणु
		info("found Genpix USB device pID = %x (hex)",
			le16_to_cpu(udev->descriptor.idProduct));
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा usb_device_id gp8psk_usb_table [] = अणु
	    अणु USB_DEVICE(USB_VID_GENPIX, USB_PID_GENPIX_8PSK_REV_1_COLD) पूर्ण,
	    अणु USB_DEVICE(USB_VID_GENPIX, USB_PID_GENPIX_8PSK_REV_1_WARM) पूर्ण,
	    अणु USB_DEVICE(USB_VID_GENPIX, USB_PID_GENPIX_8PSK_REV_2) पूर्ण,
	    अणु USB_DEVICE(USB_VID_GENPIX, USB_PID_GENPIX_SKYWALKER_1) पूर्ण,
	    अणु USB_DEVICE(USB_VID_GENPIX, USB_PID_GENPIX_SKYWALKER_2) पूर्ण,
/*	    अणु USB_DEVICE(USB_VID_GENPIX, USB_PID_GENPIX_SKYWALKER_CW3K) पूर्ण, */
	    अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, gp8psk_usb_table);

अटल काष्ठा dvb_usb_device_properties gp8psk_properties = अणु
	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-gp8psk-01.fw",

	.size_of_priv = माप(काष्ठा gp8psk_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = gp8psk_streaming_ctrl,
			.frontend_attach  = gp8psk_frontend_attach,
			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = 7,
				.endpoपूर्णांक = 0x82,
				.u = अणु
					.bulk = अणु
						.buffersize = 8192,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,
	.घातer_ctrl       = gp8psk_घातer_ctrl,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 4,
	.devices = अणु
		अणु .name = "Genpix 8PSK-to-USB2 Rev.1 DVB-S receiver",
		  .cold_ids = अणु &gp8psk_usb_table[0], शून्य पूर्ण,
		  .warm_ids = अणु &gp8psk_usb_table[1], शून्य पूर्ण,
		पूर्ण,
		अणु .name = "Genpix 8PSK-to-USB2 Rev.2 DVB-S receiver",
		  .cold_ids = अणु शून्य पूर्ण,
		  .warm_ids = अणु &gp8psk_usb_table[2], शून्य पूर्ण,
		पूर्ण,
		अणु .name = "Genpix SkyWalker-1 DVB-S receiver",
		  .cold_ids = अणु शून्य पूर्ण,
		  .warm_ids = अणु &gp8psk_usb_table[3], शून्य पूर्ण,
		पूर्ण,
		अणु .name = "Genpix SkyWalker-2 DVB-S receiver",
		  .cold_ids = अणु शून्य पूर्ण,
		  .warm_ids = अणु &gp8psk_usb_table[4], शून्य पूर्ण,
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver gp8psk_usb_driver = अणु
	.name		= "dvb_usb_gp8psk",
	.probe		= gp8psk_usb_probe,
	.disconnect = dvb_usb_device_निकास,
	.id_table	= gp8psk_usb_table,
पूर्ण;

module_usb_driver(gp8psk_usb_driver);

MODULE_AUTHOR("Alan Nisota <alannisota@gamil.com>");
MODULE_DESCRIPTION("Driver for Genpix DVB-S");
MODULE_VERSION("1.1");
MODULE_LICENSE("GPL");
