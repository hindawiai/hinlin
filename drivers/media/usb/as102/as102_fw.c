<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2008 Pierrick Hascoet <pierrick.hascoet@abilis.com>
 * Copyright (C) 2010 Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>

#समावेश "as102_drv.h"
#समावेश "as102_fw.h"

अटल स्थिर अक्षर as102_st_fw1[] = "as102_data1_st.hex";
अटल स्थिर अक्षर as102_st_fw2[] = "as102_data2_st.hex";
अटल स्थिर अक्षर as102_dt_fw1[] = "as102_data1_dt.hex";
अटल स्थिर अक्षर as102_dt_fw2[] = "as102_data2_dt.hex";

अटल अचिन्हित अक्षर atohx(अचिन्हित अक्षर *dst, अक्षर *src)
अणु
	अचिन्हित अक्षर value = 0;

	अक्षर msb = छोटे(*src) - '0';
	अक्षर lsb = छोटे(*(src + 1)) - '0';

	अगर (msb > 9)
		msb -= 7;
	अगर (lsb > 9)
		lsb -= 7;

	*dst = value = ((msb & 0xF) << 4) | (lsb & 0xF);
	वापस value;
पूर्ण

/*
 * Parse INTEL HEX firmware file to extract address and data.
 */
अटल पूर्णांक parse_hex_line(अचिन्हित अक्षर *fw_data, अचिन्हित अक्षर *addr,
			  अचिन्हित अक्षर *data, पूर्णांक *dataLength,
			  अचिन्हित अक्षर *addr_has_changed) अणु

	पूर्णांक count = 0;
	अचिन्हित अक्षर *src, dst;

	अगर (*fw_data++ != ':') अणु
		pr_err("invalid firmware file\n");
		वापस -EFAULT;
	पूर्ण

	/* locate end of line */
	क्रम (src = fw_data; *src != '\n'; src += 2) अणु
		atohx(&dst, src);
		/* parse line to split addr / data */
		चयन (count) अणु
		हाल 0:
			*dataLength = dst;
			अवरोध;
		हाल 1:
			addr[2] = dst;
			अवरोध;
		हाल 2:
			addr[3] = dst;
			अवरोध;
		हाल 3:
			/* check अगर data is an address */
			अगर (dst == 0x04)
				*addr_has_changed = 1;
			अन्यथा
				*addr_has_changed = 0;
			अवरोध;
		हाल  4:
		हाल  5:
			अगर (*addr_has_changed)
				addr[(count - 4)] = dst;
			अन्यथा
				data[(count - 4)] = dst;
			अवरोध;
		शेष:
			data[(count - 4)] = dst;
			अवरोध;
		पूर्ण
		count++;
	पूर्ण

	/* वापस पढ़ो value + ':' + '\n' */
	वापस (count * 2) + 2;
पूर्ण

अटल पूर्णांक as102_firmware_upload(काष्ठा as10x_bus_adapter_t *bus_adap,
				 अचिन्हित अक्षर *cmd,
				 स्थिर काष्ठा firmware *firmware) अणु

	काष्ठा as10x_fw_pkt_t *fw_pkt;
	पूर्णांक total_पढ़ो_bytes = 0, त्रुटि_सं = 0;
	अचिन्हित अक्षर addr_has_changed = 0;

	fw_pkt = kदो_स्मृति(माप(*fw_pkt), GFP_KERNEL);
	अगर (!fw_pkt)
		वापस -ENOMEM;


	क्रम (total_पढ़ो_bytes = 0; total_पढ़ो_bytes < firmware->size; ) अणु
		पूर्णांक पढ़ो_bytes = 0, data_len = 0;

		/* parse पूर्णांकel hex line */
		पढ़ो_bytes = parse_hex_line(
				(u8 *) (firmware->data + total_पढ़ो_bytes),
				fw_pkt->raw.address,
				fw_pkt->raw.data,
				&data_len,
				&addr_has_changed);

		अगर (पढ़ो_bytes <= 0)
			जाओ error;

		/* detect the end of file */
		total_पढ़ो_bytes += पढ़ो_bytes;
		अगर (total_पढ़ो_bytes == firmware->size) अणु
			fw_pkt->u.request[0] = 0x00;
			fw_pkt->u.request[1] = 0x03;

			/* send खातापूर्ण command */
			त्रुटि_सं = bus_adap->ops->upload_fw_pkt(bus_adap,
							     (uपूर्णांक8_t *)
							     fw_pkt, 2, 0);
			अगर (त्रुटि_सं < 0)
				जाओ error;
		पूर्ण अन्यथा अणु
			अगर (!addr_has_changed) अणु
				/* prepare command to send */
				fw_pkt->u.request[0] = 0x00;
				fw_pkt->u.request[1] = 0x01;

				data_len += माप(fw_pkt->u.request);
				data_len += माप(fw_pkt->raw.address);

				/* send cmd to device */
				त्रुटि_सं = bus_adap->ops->upload_fw_pkt(bus_adap,
								     (uपूर्णांक8_t *)
								     fw_pkt,
								     data_len,
								     0);
				अगर (त्रुटि_सं < 0)
					जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण
error:
	kमुक्त(fw_pkt);
	वापस (त्रुटि_सं == 0) ? total_पढ़ो_bytes : त्रुटि_सं;
पूर्ण

पूर्णांक as102_fw_upload(काष्ठा as10x_bus_adapter_t *bus_adap)
अणु
	पूर्णांक त्रुटि_सं = -EFAULT;
	स्थिर काष्ठा firmware *firmware = शून्य;
	अचिन्हित अक्षर *cmd_buf = शून्य;
	स्थिर अक्षर *fw1, *fw2;
	काष्ठा usb_device *dev = bus_adap->usb_dev;

	/* select fw file to upload */
	अगर (dual_tuner) अणु
		fw1 = as102_dt_fw1;
		fw2 = as102_dt_fw2;
	पूर्ण अन्यथा अणु
		fw1 = as102_st_fw1;
		fw2 = as102_st_fw2;
	पूर्ण

	/* allocate buffer to store firmware upload command and data */
	cmd_buf = kzalloc(MAX_FW_PKT_SIZE, GFP_KERNEL);
	अगर (cmd_buf == शून्य) अणु
		त्रुटि_सं = -ENOMEM;
		जाओ error;
	पूर्ण

	/* request kernel to locate firmware file: part1 */
	त्रुटि_सं = request_firmware(&firmware, fw1, &dev->dev);
	अगर (त्रुटि_सं < 0) अणु
		pr_err("%s: unable to locate firmware file: %s\n",
		       DRIVER_NAME, fw1);
		जाओ error;
	पूर्ण

	/* initiate firmware upload */
	त्रुटि_सं = as102_firmware_upload(bus_adap, cmd_buf, firmware);
	अगर (त्रुटि_सं < 0) अणु
		pr_err("%s: error during firmware upload part1\n",
		       DRIVER_NAME);
		जाओ error;
	पूर्ण

	pr_info("%s: firmware: %s loaded with success\n",
		DRIVER_NAME, fw1);
	release_firmware(firmware);
	firmware = शून्य;

	/* रुको क्रम boot to complete */
	mdelay(100);

	/* request kernel to locate firmware file: part2 */
	त्रुटि_सं = request_firmware(&firmware, fw2, &dev->dev);
	अगर (त्रुटि_सं < 0) अणु
		pr_err("%s: unable to locate firmware file: %s\n",
		       DRIVER_NAME, fw2);
		जाओ error;
	पूर्ण

	/* initiate firmware upload */
	त्रुटि_सं = as102_firmware_upload(bus_adap, cmd_buf, firmware);
	अगर (त्रुटि_सं < 0) अणु
		pr_err("%s: error during firmware upload part2\n",
		       DRIVER_NAME);
		जाओ error;
	पूर्ण

	pr_info("%s: firmware: %s loaded with success\n",
		DRIVER_NAME, fw2);
error:
	kमुक्त(cmd_buf);
	release_firmware(firmware);

	वापस त्रुटि_सं;
पूर्ण
