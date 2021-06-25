<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	Copyright (C) 2004 - 2009 Gertjan van Wingerde <gwingerde@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00lib
	Abstract: rt2x00 firmware loading routines.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00lib.h"

अटल पूर्णांक rt2x00lib_request_firmware(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा device *device = wiphy_dev(rt2x00dev->hw->wiphy);
	स्थिर काष्ठा firmware *fw;
	अक्षर *fw_name;
	पूर्णांक retval;

	/*
	 * Read correct firmware from harddisk.
	 */
	fw_name = rt2x00dev->ops->lib->get_firmware_name(rt2x00dev);
	अगर (!fw_name) अणु
		rt2x00_err(rt2x00dev,
			   "Invalid firmware filename\n"
			   "Please file bug report to %s\n", DRV_PROJECT);
		वापस -EINVAL;
	पूर्ण

	rt2x00_info(rt2x00dev, "Loading firmware file '%s'\n", fw_name);

	retval = request_firmware(&fw, fw_name, device);
	अगर (retval) अणु
		rt2x00_err(rt2x00dev, "Failed to request Firmware\n");
		वापस retval;
	पूर्ण

	अगर (!fw || !fw->size || !fw->data) अणु
		rt2x00_err(rt2x00dev, "Failed to read Firmware\n");
		release_firmware(fw);
		वापस -ENOENT;
	पूर्ण

	rt2x00_info(rt2x00dev, "Firmware detected - version: %d.%d\n",
		    fw->data[fw->size - 4], fw->data[fw->size - 3]);
	snम_लिखो(rt2x00dev->hw->wiphy->fw_version,
			माप(rt2x00dev->hw->wiphy->fw_version), "%d.%d",
			fw->data[fw->size - 4], fw->data[fw->size - 3]);

	retval = rt2x00dev->ops->lib->check_firmware(rt2x00dev, fw->data, fw->size);
	चयन (retval) अणु
	हाल FW_OK:
		अवरोध;
	हाल FW_BAD_CRC:
		rt2x00_err(rt2x00dev, "Firmware checksum error\n");
		जाओ निकास;
	हाल FW_BAD_LENGTH:
		rt2x00_err(rt2x00dev, "Invalid firmware file length (len=%zu)\n",
			   fw->size);
		जाओ निकास;
	हाल FW_BAD_VERSION:
		rt2x00_err(rt2x00dev, "Current firmware does not support detected chipset\n");
		जाओ निकास;
	पूर्ण

	rt2x00dev->fw = fw;

	वापस 0;

निकास:
	release_firmware(fw);

	वापस -ENOENT;
पूर्ण

पूर्णांक rt2x00lib_load_firmware(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक retval;

	अगर (!rt2x00_has_cap_flag(rt2x00dev, REQUIRE_FIRMWARE))
		वापस 0;

	अगर (!rt2x00dev->fw) अणु
		retval = rt2x00lib_request_firmware(rt2x00dev);
		अगर (retval)
			वापस retval;
	पूर्ण

	/*
	 * Send firmware to the device.
	 */
	retval = rt2x00dev->ops->lib->load_firmware(rt2x00dev,
						    rt2x00dev->fw->data,
						    rt2x00dev->fw->size);

	/*
	 * When the firmware is uploaded to the hardware the LED
	 * association status might have been triggered, क्रम correct
	 * LED handling it should now be reset.
	 */
	rt2x00leds_led_assoc(rt2x00dev, false);

	वापस retval;
पूर्ण

व्योम rt2x00lib_मुक्त_firmware(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	release_firmware(rt2x00dev->fw);
	rt2x00dev->fw = शून्य;
पूर्ण
