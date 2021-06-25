<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux driver क्रम TerraTec DMX 6Fire USB
 *
 * Firmware loader
 *
 * Author:	Torsten Schenk <torsten.schenk@zoho.com>
 * Created:	Jan 01, 2011
 * Copyright:	(C) Torsten Schenk
 */

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/kernel.h>

#समावेश "firmware.h"
#समावेश "chip.h"

MODULE_FIRMWARE("6fire/dmx6firel2.ihx");
MODULE_FIRMWARE("6fire/dmx6fireap.ihx");
MODULE_FIRMWARE("6fire/dmx6firecf.bin");

क्रमागत अणु
	FPGA_बफ_मानE = 512, FPGA_EP = 2
पूर्ण;

/*
 * wMaxPacketSize of pcm endpoपूर्णांकs.
 * keep synced with rates_in_packet_size and rates_out_packet_size in pcm.c
 * fpp: frames per isopacket
 *
 * CAUTION: keep माप <= buffer[] in usb6fire_fw_init
 */
अटल स्थिर u8 ep_w_max_packet_size[] = अणु
	0xe4, 0x00, 0xe4, 0x00, /* alt 1: 228 EP2 and EP6 (7 fpp) */
	0xa4, 0x01, 0xa4, 0x01, /* alt 2: 420 EP2 and EP6 (13 fpp)*/
	0x94, 0x01, 0x5c, 0x02  /* alt 3: 404 EP2 and 604 EP6 (25 fpp) */
पूर्ण;

अटल स्थिर u8 known_fw_versions[][2] = अणु
	अणु 0x03, 0x01 पूर्ण
पूर्ण;

काष्ठा ihex_record अणु
	u16 address;
	u8 len;
	u8 data[256];
	अक्षर error; /* true अगर an error occurred parsing this record */

	u8 max_len; /* maximum record length in whole ihex */

	/* निजी */
	स्थिर अक्षर *txt_data;
	अचिन्हित पूर्णांक txt_length;
	अचिन्हित पूर्णांक txt_offset; /* current position in txt_data */
पूर्ण;

अटल u8 usb6fire_fw_ihex_hex(स्थिर u8 *data, u8 *crc)
अणु
	u8 val = 0;
	पूर्णांक hval;

	hval = hex_to_bin(data[0]);
	अगर (hval >= 0)
		val |= (hval << 4);

	hval = hex_to_bin(data[1]);
	अगर (hval >= 0)
		val |= hval;

	*crc += val;
	वापस val;
पूर्ण

/*
 * वापसs true अगर record is available, false otherwise.
 * अगरf an error occurred, false will be वापसed and record->error will be true.
 */
अटल bool usb6fire_fw_ihex_next_record(काष्ठा ihex_record *record)
अणु
	u8 crc = 0;
	u8 type;
	पूर्णांक i;

	record->error = false;

	/* find begin of record (marked by a colon) */
	जबतक (record->txt_offset < record->txt_length
			&& record->txt_data[record->txt_offset] != ':')
		record->txt_offset++;
	अगर (record->txt_offset == record->txt_length)
		वापस false;

	/* number of अक्षरacters needed क्रम len, addr and type entries */
	record->txt_offset++;
	अगर (record->txt_offset + 8 > record->txt_length) अणु
		record->error = true;
		वापस false;
	पूर्ण

	record->len = usb6fire_fw_ihex_hex(record->txt_data +
			record->txt_offset, &crc);
	record->txt_offset += 2;
	record->address = usb6fire_fw_ihex_hex(record->txt_data +
			record->txt_offset, &crc) << 8;
	record->txt_offset += 2;
	record->address |= usb6fire_fw_ihex_hex(record->txt_data +
			record->txt_offset, &crc);
	record->txt_offset += 2;
	type = usb6fire_fw_ihex_hex(record->txt_data +
			record->txt_offset, &crc);
	record->txt_offset += 2;

	/* number of अक्षरacters needed क्रम data and crc entries */
	अगर (record->txt_offset + 2 * (record->len + 1) > record->txt_length) अणु
		record->error = true;
		वापस false;
	पूर्ण
	क्रम (i = 0; i < record->len; i++) अणु
		record->data[i] = usb6fire_fw_ihex_hex(record->txt_data
				+ record->txt_offset, &crc);
		record->txt_offset += 2;
	पूर्ण
	usb6fire_fw_ihex_hex(record->txt_data + record->txt_offset, &crc);
	अगर (crc) अणु
		record->error = true;
		वापस false;
	पूर्ण

	अगर (type == 1 || !record->len) /* eof */
		वापस false;
	अन्यथा अगर (type == 0)
		वापस true;
	अन्यथा अणु
		record->error = true;
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक usb6fire_fw_ihex_init(स्थिर काष्ठा firmware *fw,
		काष्ठा ihex_record *record)
अणु
	record->txt_data = fw->data;
	record->txt_length = fw->size;
	record->txt_offset = 0;
	record->max_len = 0;
	/* पढ़ो all records, अगर loop ends, record->error indicates,
	 * whether ihex is valid. */
	जबतक (usb6fire_fw_ihex_next_record(record))
		record->max_len = max(record->len, record->max_len);
	अगर (record->error)
		वापस -EINVAL;
	record->txt_offset = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_fw_ezusb_ग_लिखो(काष्ठा usb_device *device,
		पूर्णांक type, पूर्णांक value, अक्षर *data, पूर्णांक len)
अणु
	वापस usb_control_msg_send(device, 0, type,
				    USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				    value, 0, data, len, HZ, GFP_KERNEL);
पूर्ण

अटल पूर्णांक usb6fire_fw_ezusb_पढ़ो(काष्ठा usb_device *device,
		पूर्णांक type, पूर्णांक value, अक्षर *data, पूर्णांक len)
अणु
	वापस usb_control_msg_recv(device, 0, type,
				    USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				    value, 0, data, len, HZ, GFP_KERNEL);
पूर्ण

अटल पूर्णांक usb6fire_fw_fpga_ग_लिखो(काष्ठा usb_device *device,
		अक्षर *data, पूर्णांक len)
अणु
	पूर्णांक actual_len;
	पूर्णांक ret;

	ret = usb_bulk_msg(device, usb_sndbulkpipe(device, FPGA_EP), data, len,
			&actual_len, HZ);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (actual_len != len)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_fw_ezusb_upload(
		काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर अक्षर *fwname,
		अचिन्हित पूर्णांक postaddr, u8 *postdata, अचिन्हित पूर्णांक postlen)
अणु
	पूर्णांक ret;
	u8 data;
	काष्ठा usb_device *device = पूर्णांकerface_to_usbdev(पूर्णांकf);
	स्थिर काष्ठा firmware *fw = शून्य;
	काष्ठा ihex_record *rec = kदो_स्मृति(माप(काष्ठा ihex_record),
			GFP_KERNEL);

	अगर (!rec)
		वापस -ENOMEM;

	ret = request_firmware(&fw, fwname, &device->dev);
	अगर (ret < 0) अणु
		kमुक्त(rec);
		dev_err(&पूर्णांकf->dev,
			"error requesting ezusb firmware %s.\n", fwname);
		वापस ret;
	पूर्ण
	ret = usb6fire_fw_ihex_init(fw, rec);
	अगर (ret < 0) अणु
		kमुक्त(rec);
		release_firmware(fw);
		dev_err(&पूर्णांकf->dev,
			"error validating ezusb firmware %s.\n", fwname);
		वापस ret;
	पूर्ण
	/* upload firmware image */
	data = 0x01; /* stop ezusb cpu */
	ret = usb6fire_fw_ezusb_ग_लिखो(device, 0xa0, 0xe600, &data, 1);
	अगर (ret) अणु
		kमुक्त(rec);
		release_firmware(fw);
		dev_err(&पूर्णांकf->dev,
			"unable to upload ezusb firmware %s: begin message.\n",
			fwname);
		वापस ret;
	पूर्ण

	जबतक (usb6fire_fw_ihex_next_record(rec)) अणु /* ग_लिखो firmware */
		ret = usb6fire_fw_ezusb_ग_लिखो(device, 0xa0, rec->address,
				rec->data, rec->len);
		अगर (ret) अणु
			kमुक्त(rec);
			release_firmware(fw);
			dev_err(&पूर्णांकf->dev,
				"unable to upload ezusb firmware %s: data urb.\n",
				fwname);
			वापस ret;
		पूर्ण
	पूर्ण

	release_firmware(fw);
	kमुक्त(rec);
	अगर (postdata) अणु /* ग_लिखो data after firmware has been uploaded */
		ret = usb6fire_fw_ezusb_ग_लिखो(device, 0xa0, postaddr,
				postdata, postlen);
		अगर (ret) अणु
			dev_err(&पूर्णांकf->dev,
				"unable to upload ezusb firmware %s: post urb.\n",
				fwname);
			वापस ret;
		पूर्ण
	पूर्ण

	data = 0x00; /* resume ezusb cpu */
	ret = usb6fire_fw_ezusb_ग_लिखो(device, 0xa0, 0xe600, &data, 1);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev,
			"unable to upload ezusb firmware %s: end message.\n",
			fwname);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_fw_fpga_upload(
		काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर अक्षर *fwname)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा usb_device *device = पूर्णांकerface_to_usbdev(पूर्णांकf);
	u8 *buffer = kदो_स्मृति(FPGA_बफ_मानE, GFP_KERNEL);
	स्थिर अक्षर *c;
	स्थिर अक्षर *end;
	स्थिर काष्ठा firmware *fw;

	अगर (!buffer)
		वापस -ENOMEM;

	ret = request_firmware(&fw, fwname, &device->dev);
	अगर (ret < 0) अणु
		dev_err(&पूर्णांकf->dev, "unable to get fpga firmware %s.\n",
				fwname);
		kमुक्त(buffer);
		वापस -EIO;
	पूर्ण

	c = fw->data;
	end = fw->data + fw->size;

	ret = usb6fire_fw_ezusb_ग_लिखो(device, 8, 0, शून्य, 0);
	अगर (ret) अणु
		kमुक्त(buffer);
		release_firmware(fw);
		dev_err(&पूर्णांकf->dev,
			"unable to upload fpga firmware: begin urb.\n");
		वापस ret;
	पूर्ण

	जबतक (c != end) अणु
		क्रम (i = 0; c != end && i < FPGA_बफ_मानE; i++, c++)
			buffer[i] = bitrev8((u8)*c);

		ret = usb6fire_fw_fpga_ग_लिखो(device, buffer, i);
		अगर (ret < 0) अणु
			release_firmware(fw);
			kमुक्त(buffer);
			dev_err(&पूर्णांकf->dev,
				"unable to upload fpga firmware: fw urb.\n");
			वापस ret;
		पूर्ण
	पूर्ण
	release_firmware(fw);
	kमुक्त(buffer);

	ret = usb6fire_fw_ezusb_ग_लिखो(device, 9, 0, शून्य, 0);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev,
			"unable to upload fpga firmware: end urb.\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* check, अगर the firmware version the devices has currently loaded
 * is known by this driver. 'version' needs to have 4 bytes version
 * info data. */
अटल पूर्णांक usb6fire_fw_check(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर u8 *version)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(known_fw_versions); i++)
		अगर (!स_भेद(version, known_fw_versions + i, 2))
			वापस 0;

	dev_err(&पूर्णांकf->dev, "invalid firmware version in device: %4ph. "
			"please reconnect to power. if this failure "
			"still happens, check your firmware installation.",
			version);
	वापस -EINVAL;
पूर्ण

पूर्णांक usb6fire_fw_init(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा usb_device *device = पूर्णांकerface_to_usbdev(पूर्णांकf);
	/* buffer: 8 receiving bytes from device and
	 * माप(EP_W_MAX_PACKET_SIZE) bytes क्रम non-स्थिर copy */
	u8 buffer[12];

	ret = usb6fire_fw_ezusb_पढ़ो(device, 1, 0, buffer, 8);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev,
			"unable to receive device firmware state.\n");
		वापस ret;
	पूर्ण
	अगर (buffer[0] != 0xeb || buffer[1] != 0xaa || buffer[2] != 0x55) अणु
		dev_err(&पूर्णांकf->dev,
			"unknown device firmware state received from device:");
		क्रम (i = 0; i < 8; i++)
			prपूर्णांकk(KERN_CONT "%02x ", buffer[i]);
		prपूर्णांकk(KERN_CONT "\n");
		वापस -EIO;
	पूर्ण
	/* करो we need fpga loader ezusb firmware? */
	अगर (buffer[3] == 0x01) अणु
		ret = usb6fire_fw_ezusb_upload(पूर्णांकf,
				"6fire/dmx6firel2.ihx", 0, शून्य, 0);
		अगर (ret < 0)
			वापस ret;
		वापस FW_NOT_READY;
	पूर्ण
	/* करो we need fpga firmware and application ezusb firmware? */
	अन्यथा अगर (buffer[3] == 0x02) अणु
		ret = usb6fire_fw_check(पूर्णांकf, buffer + 4);
		अगर (ret < 0)
			वापस ret;
		ret = usb6fire_fw_fpga_upload(पूर्णांकf, "6fire/dmx6firecf.bin");
		अगर (ret < 0)
			वापस ret;
		स_नकल(buffer, ep_w_max_packet_size,
				माप(ep_w_max_packet_size));
		ret = usb6fire_fw_ezusb_upload(पूर्णांकf, "6fire/dmx6fireap.ihx",
				0x0003,	buffer, माप(ep_w_max_packet_size));
		अगर (ret < 0)
			वापस ret;
		वापस FW_NOT_READY;
	पूर्ण
	/* all fw loaded? */
	अन्यथा अगर (buffer[3] == 0x03)
		वापस usb6fire_fw_check(पूर्णांकf, buffer + 4);
	/* unknown data? */
	अन्यथा अणु
		dev_err(&पूर्णांकf->dev,
			"unknown device firmware state received from device: ");
		क्रम (i = 0; i < 8; i++)
			prपूर्णांकk(KERN_CONT "%02x ", buffer[i]);
		prपूर्णांकk(KERN_CONT "\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

