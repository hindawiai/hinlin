<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Zodiac Inflight Innovations
 *
 * Author: Martyn Welch <martyn.welch@collabora.co.uk>
 *
 * Based on twl4030_wdt.c by Timo Kokkonen <timo.t.kokkonen at nokia.com>:
 *
 * Copyright (C) Nokia Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/ihex.h>
#समावेश <linux/firmware.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा ZIIRAVE_TIMEOUT_MIN	3
#घोषणा ZIIRAVE_TIMEOUT_MAX	255
#घोषणा ZIIRAVE_TIMEOUT_DEFAULT	30

#घोषणा ZIIRAVE_PING_VALUE	0x0

#घोषणा ZIIRAVE_STATE_INITIAL	0x0
#घोषणा ZIIRAVE_STATE_OFF	0x1
#घोषणा ZIIRAVE_STATE_ON	0x2

#घोषणा ZIIRAVE_FW_NAME		"ziirave_wdt.fw"

अटल अक्षर *ziirave_reasons[] = अणु"power cycle", "hw watchdog", शून्य, शून्य,
				  "host request", शून्य, "illegal configuration",
				  "illegal instruction", "illegal trap",
				  "unknown"पूर्ण;

#घोषणा ZIIRAVE_WDT_FIRM_VER_MAJOR	0x1
#घोषणा ZIIRAVE_WDT_BOOT_VER_MAJOR	0x3
#घोषणा ZIIRAVE_WDT_RESET_REASON	0x5
#घोषणा ZIIRAVE_WDT_STATE		0x6
#घोषणा ZIIRAVE_WDT_TIMEOUT		0x7
#घोषणा ZIIRAVE_WDT_TIME_LEFT		0x8
#घोषणा ZIIRAVE_WDT_PING		0x9
#घोषणा ZIIRAVE_WDT_RESET_DURATION	0xa

#घोषणा ZIIRAVE_FIRM_PKT_TOTAL_SIZE	20
#घोषणा ZIIRAVE_FIRM_PKT_DATA_SIZE	16
#घोषणा ZIIRAVE_FIRM_FLASH_MEMORY_START	(2 * 0x1600)
#घोषणा ZIIRAVE_FIRM_FLASH_MEMORY_END	(2 * 0x2bbf)
#घोषणा ZIIRAVE_FIRM_PAGE_SIZE		128

/* Received and पढ़ोy क्रम next Download packet. */
#घोषणा ZIIRAVE_FIRM_DOWNLOAD_ACK	1

/* Firmware commands */
#घोषणा ZIIRAVE_CMD_DOWNLOAD_START		0x10
#घोषणा ZIIRAVE_CMD_DOWNLOAD_END		0x11
#घोषणा ZIIRAVE_CMD_DOWNLOAD_SET_READ_ADDR	0x12
#घोषणा ZIIRAVE_CMD_DOWNLOAD_READ_BYTE		0x13
#घोषणा ZIIRAVE_CMD_RESET_PROCESSOR		0x0b
#घोषणा ZIIRAVE_CMD_JUMP_TO_BOOTLOADER		0x0c
#घोषणा ZIIRAVE_CMD_DOWNLOAD_PACKET		0x0e

#घोषणा ZIIRAVE_CMD_JUMP_TO_BOOTLOADER_MAGIC	1
#घोषणा ZIIRAVE_CMD_RESET_PROCESSOR_MAGIC	1

#घोषणा ZIIRAVE_FW_VERSION_FMT	"02.%02u.%02u"
#घोषणा ZIIRAVE_BL_VERSION_FMT	"01.%02u.%02u"

काष्ठा ziirave_wdt_rev अणु
	अचिन्हित अक्षर major;
	अचिन्हित अक्षर minor;
पूर्ण;

काष्ठा ziirave_wdt_data अणु
	काष्ठा mutex sysfs_mutex;
	काष्ठा watchकरोg_device wdd;
	काष्ठा ziirave_wdt_rev bootloader_rev;
	काष्ठा ziirave_wdt_rev firmware_rev;
	पूर्णांक reset_reason;
पूर्ण;

अटल पूर्णांक wdt_समयout;
module_param(wdt_समयout, पूर्णांक, 0);
MODULE_PARM_DESC(wdt_समयout, "Watchdog timeout in seconds");

अटल पूर्णांक reset_duration;
module_param(reset_duration, पूर्णांक, 0);
MODULE_PARM_DESC(reset_duration,
		 "Watchdog reset pulse duration in milliseconds");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल पूर्णांक ziirave_wdt_revision(काष्ठा i2c_client *client,
				काष्ठा ziirave_wdt_rev *rev, u8 command)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, command);
	अगर (ret < 0)
		वापस ret;

	rev->major = ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, command + 1);
	अगर (ret < 0)
		वापस ret;

	rev->minor = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ziirave_wdt_set_state(काष्ठा watchकरोg_device *wdd, पूर्णांक state)
अणु
	काष्ठा i2c_client *client = to_i2c_client(wdd->parent);

	वापस i2c_smbus_ग_लिखो_byte_data(client, ZIIRAVE_WDT_STATE, state);
पूर्ण

अटल पूर्णांक ziirave_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	वापस ziirave_wdt_set_state(wdd, ZIIRAVE_STATE_ON);
पूर्ण

अटल पूर्णांक ziirave_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	वापस ziirave_wdt_set_state(wdd, ZIIRAVE_STATE_OFF);
पूर्ण

अटल पूर्णांक ziirave_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा i2c_client *client = to_i2c_client(wdd->parent);

	वापस i2c_smbus_ग_लिखो_byte_data(client, ZIIRAVE_WDT_PING,
					 ZIIRAVE_PING_VALUE);
पूर्ण

अटल पूर्णांक ziirave_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				   अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा i2c_client *client = to_i2c_client(wdd->parent);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, ZIIRAVE_WDT_TIMEOUT, समयout);
	अगर (!ret)
		wdd->समयout = समयout;

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक ziirave_wdt_get_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा i2c_client *client = to_i2c_client(wdd->parent);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, ZIIRAVE_WDT_TIME_LEFT);
	अगर (ret < 0)
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक ziirave_firm_पढ़ो_ack(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा i2c_client *client = to_i2c_client(wdd->parent);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte(client);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to read status byte\n");
		वापस ret;
	पूर्ण

	वापस ret == ZIIRAVE_FIRM_DOWNLOAD_ACK ? 0 : -EIO;
पूर्ण

अटल पूर्णांक ziirave_firm_set_पढ़ो_addr(काष्ठा watchकरोg_device *wdd, u32 addr)
अणु
	काष्ठा i2c_client *client = to_i2c_client(wdd->parent);
	स्थिर u16 addr16 = (u16)addr / 2;
	u8 address[2];

	put_unaligned_le16(addr16, address);

	वापस i2c_smbus_ग_लिखो_block_data(client,
					  ZIIRAVE_CMD_DOWNLOAD_SET_READ_ADDR,
					  माप(address), address);
पूर्ण

अटल bool ziirave_firm_addr_पढ़ोonly(u32 addr)
अणु
	वापस addr < ZIIRAVE_FIRM_FLASH_MEMORY_START ||
	       addr > ZIIRAVE_FIRM_FLASH_MEMORY_END;
पूर्ण

/*
 * ziirave_firm_ग_लिखो_pkt() - Build and ग_लिखो a firmware packet
 *
 * A packet to send to the firmware is composed by following bytes:
 *     Length | Addr0 | Addr1 | Data0 .. Data15 | Checksum |
 * Where,
 *     Length: A data byte containing the length of the data.
 *     Addr0: Low byte of the address.
 *     Addr1: High byte of the address.
 *     Data0 .. Data15: Array of 16 bytes of data.
 *     Checksum: Checksum byte to verअगरy data पूर्णांकegrity.
 */
अटल पूर्णांक __ziirave_firm_ग_लिखो_pkt(काष्ठा watchकरोg_device *wdd,
				    u32 addr, स्थिर u8 *data, u8 len)
अणु
	स्थिर u16 addr16 = (u16)addr / 2;
	काष्ठा i2c_client *client = to_i2c_client(wdd->parent);
	u8 i, checksum = 0, packet[ZIIRAVE_FIRM_PKT_TOTAL_SIZE];
	पूर्णांक ret;

	/* Check max data size */
	अगर (len > ZIIRAVE_FIRM_PKT_DATA_SIZE) अणु
		dev_err(&client->dev, "Firmware packet too long (%d)\n",
			len);
		वापस -EMSGSIZE;
	पूर्ण

	/*
	 * Ignore packets that are targeting program memory outisde of
	 * app partition, since they will be ignored by the
	 * bootloader. At the same समय, we need to make sure we'll
	 * allow zero length packet that will be sent as the last step
	 * of firmware update
	 */
	अगर (len && ziirave_firm_addr_पढ़ोonly(addr))
		वापस 0;

	/* Packet length */
	packet[0] = len;
	/* Packet address */
	put_unaligned_le16(addr16, packet + 1);

	स_नकल(packet + 3, data, len);
	स_रखो(packet + 3 + len, 0, ZIIRAVE_FIRM_PKT_DATA_SIZE - len);

	/* Packet checksum */
	क्रम (i = 0; i < len + 3; i++)
		checksum += packet[i];
	packet[ZIIRAVE_FIRM_PKT_TOTAL_SIZE - 1] = checksum;

	ret = i2c_smbus_ग_लिखो_block_data(client, ZIIRAVE_CMD_DOWNLOAD_PACKET,
					 माप(packet), packet);
	अगर (ret) अणु
		dev_err(&client->dev,
			"Failed to send DOWNLOAD_PACKET: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ziirave_firm_पढ़ो_ack(wdd);
	अगर (ret)
		dev_err(&client->dev,
		      "Failed to write firmware packet at address 0x%04x: %d\n",
		      addr, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ziirave_firm_ग_लिखो_pkt(काष्ठा watchकरोg_device *wdd,
				  u32 addr, स्थिर u8 *data, u8 len)
अणु
	स्थिर u8 max_ग_लिखो_len = ZIIRAVE_FIRM_PAGE_SIZE -
		(addr - ALIGN_DOWN(addr, ZIIRAVE_FIRM_PAGE_SIZE));
	पूर्णांक ret;

	अगर (len > max_ग_लिखो_len) अणु
		/*
		 * If data crossed page boundary we need to split this
		 * ग_लिखो in two
		 */
		ret = __ziirave_firm_ग_लिखो_pkt(wdd, addr, data, max_ग_लिखो_len);
		अगर (ret)
			वापस ret;

		addr += max_ग_लिखो_len;
		data += max_ग_लिखो_len;
		len  -= max_ग_लिखो_len;
	पूर्ण

	वापस __ziirave_firm_ग_लिखो_pkt(wdd, addr, data, len);
पूर्ण

अटल पूर्णांक ziirave_firm_verअगरy(काष्ठा watchकरोg_device *wdd,
			       स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा i2c_client *client = to_i2c_client(wdd->parent);
	स्थिर काष्ठा ihex_binrec *rec;
	पूर्णांक i, ret;
	u8 data[ZIIRAVE_FIRM_PKT_DATA_SIZE];

	क्रम (rec = (व्योम *)fw->data; rec; rec = ihex_next_binrec(rec)) अणु
		स्थिर u16 len = be16_to_cpu(rec->len);
		स्थिर u32 addr = be32_to_cpu(rec->addr);

		अगर (ziirave_firm_addr_पढ़ोonly(addr))
			जारी;

		ret = ziirave_firm_set_पढ़ो_addr(wdd, addr);
		अगर (ret) अणु
			dev_err(&client->dev,
				"Failed to send SET_READ_ADDR command: %d\n",
				ret);
			वापस ret;
		पूर्ण

		क्रम (i = 0; i < len; i++) अणु
			ret = i2c_smbus_पढ़ो_byte_data(client,
						ZIIRAVE_CMD_DOWNLOAD_READ_BYTE);
			अगर (ret < 0) अणु
				dev_err(&client->dev,
					"Failed to READ DATA: %d\n", ret);
				वापस ret;
			पूर्ण
			data[i] = ret;
		पूर्ण

		अगर (स_भेद(data, rec->data, len)) अणु
			dev_err(&client->dev,
				"Firmware mismatch at address 0x%04x\n", addr);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ziirave_firm_upload(काष्ठा watchकरोg_device *wdd,
			       स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा i2c_client *client = to_i2c_client(wdd->parent);
	स्थिर काष्ठा ihex_binrec *rec;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client,
					ZIIRAVE_CMD_JUMP_TO_BOOTLOADER,
					ZIIRAVE_CMD_JUMP_TO_BOOTLOADER_MAGIC);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to jump to bootloader\n");
		वापस ret;
	पूर्ण

	msleep(500);

	ret = i2c_smbus_ग_लिखो_byte(client, ZIIRAVE_CMD_DOWNLOAD_START);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to start download\n");
		वापस ret;
	पूर्ण

	ret = ziirave_firm_पढ़ो_ack(wdd);
	अगर (ret) अणु
		dev_err(&client->dev, "No ACK for start download\n");
		वापस ret;
	पूर्ण

	msleep(500);

	क्रम (rec = (व्योम *)fw->data; rec; rec = ihex_next_binrec(rec)) अणु
		ret = ziirave_firm_ग_लिखो_pkt(wdd, be32_to_cpu(rec->addr),
					     rec->data, be16_to_cpu(rec->len));
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Finish firmware करोwnload process by sending a zero length
	 * payload
	 */
	ret = ziirave_firm_ग_लिखो_pkt(wdd, 0, शून्य, 0);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to send EMPTY packet: %d\n", ret);
		वापस ret;
	पूर्ण

	/* This sleep seems to be required */
	msleep(20);

	/* Start firmware verअगरication */
	ret = ziirave_firm_verअगरy(wdd, fw);
	अगर (ret) अणु
		dev_err(&client->dev,
			"Failed to verify firmware: %d\n", ret);
		वापस ret;
	पूर्ण

	/* End करोwnload operation */
	ret = i2c_smbus_ग_लिखो_byte(client, ZIIRAVE_CMD_DOWNLOAD_END);
	अगर (ret) अणु
		dev_err(&client->dev,
			"Failed to end firmware download: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Reset the processor */
	ret = i2c_smbus_ग_लिखो_byte_data(client,
					ZIIRAVE_CMD_RESET_PROCESSOR,
					ZIIRAVE_CMD_RESET_PROCESSOR_MAGIC);
	अगर (ret) अणु
		dev_err(&client->dev,
			"Failed to reset the watchdog: %d\n", ret);
		वापस ret;
	पूर्ण

	msleep(500);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ziirave_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING,
	.identity = "RAVE Switch Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops ziirave_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= ziirave_wdt_start,
	.stop		= ziirave_wdt_stop,
	.ping		= ziirave_wdt_ping,
	.set_समयout	= ziirave_wdt_set_समयout,
	.get_समयleft	= ziirave_wdt_get_समयleft,
पूर्ण;

अटल sमाप_प्रकार ziirave_wdt_sysfs_show_firm(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	काष्ठा ziirave_wdt_data *w_priv = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&w_priv->sysfs_mutex);
	अगर (ret)
		वापस ret;

	ret = प्र_लिखो(buf, ZIIRAVE_FW_VERSION_FMT, w_priv->firmware_rev.major,
		      w_priv->firmware_rev.minor);

	mutex_unlock(&w_priv->sysfs_mutex);

	वापस ret;
पूर्ण

अटल DEVICE_ATTR(firmware_version, S_IRUGO, ziirave_wdt_sysfs_show_firm,
		   शून्य);

अटल sमाप_प्रकार ziirave_wdt_sysfs_show_boot(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	काष्ठा ziirave_wdt_data *w_priv = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&w_priv->sysfs_mutex);
	अगर (ret)
		वापस ret;

	ret = प्र_लिखो(buf, ZIIRAVE_BL_VERSION_FMT, w_priv->bootloader_rev.major,
		      w_priv->bootloader_rev.minor);

	mutex_unlock(&w_priv->sysfs_mutex);

	वापस ret;
पूर्ण

अटल DEVICE_ATTR(bootloader_version, S_IRUGO, ziirave_wdt_sysfs_show_boot,
		   शून्य);

अटल sमाप_प्रकार ziirave_wdt_sysfs_show_reason(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	काष्ठा ziirave_wdt_data *w_priv = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&w_priv->sysfs_mutex);
	अगर (ret)
		वापस ret;

	ret = प्र_लिखो(buf, "%s", ziirave_reasons[w_priv->reset_reason]);

	mutex_unlock(&w_priv->sysfs_mutex);

	वापस ret;
पूर्ण

अटल DEVICE_ATTR(reset_reason, S_IRUGO, ziirave_wdt_sysfs_show_reason,
		   शून्य);

अटल sमाप_प्रकार ziirave_wdt_sysfs_store_firm(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	काष्ठा ziirave_wdt_data *w_priv = i2c_get_clientdata(client);
	स्थिर काष्ठा firmware *fw;
	पूर्णांक err;

	err = request_ihex_firmware(&fw, ZIIRAVE_FW_NAME, dev);
	अगर (err) अणु
		dev_err(&client->dev, "Failed to request ihex firmware\n");
		वापस err;
	पूर्ण

	err = mutex_lock_पूर्णांकerruptible(&w_priv->sysfs_mutex);
	अगर (err)
		जाओ release_firmware;

	err = ziirave_firm_upload(&w_priv->wdd, fw);
	अगर (err) अणु
		dev_err(&client->dev, "The firmware update failed: %d\n", err);
		जाओ unlock_mutex;
	पूर्ण

	/* Update firmware version */
	err = ziirave_wdt_revision(client, &w_priv->firmware_rev,
				   ZIIRAVE_WDT_FIRM_VER_MAJOR);
	अगर (err) अणु
		dev_err(&client->dev, "Failed to read firmware version: %d\n",
			err);
		जाओ unlock_mutex;
	पूर्ण

	dev_info(&client->dev,
		 "Firmware updated to version " ZIIRAVE_FW_VERSION_FMT "\n",
		 w_priv->firmware_rev.major, w_priv->firmware_rev.minor);

	/* Restore the watchकरोg समयout */
	err = ziirave_wdt_set_समयout(&w_priv->wdd, w_priv->wdd.समयout);
	अगर (err)
		dev_err(&client->dev, "Failed to set timeout: %d\n", err);

unlock_mutex:
	mutex_unlock(&w_priv->sysfs_mutex);

release_firmware:
	release_firmware(fw);

	वापस err ? err : count;
पूर्ण

अटल DEVICE_ATTR(update_firmware, S_IWUSR, शून्य,
		   ziirave_wdt_sysfs_store_firm);

अटल काष्ठा attribute *ziirave_wdt_attrs[] = अणु
	&dev_attr_firmware_version.attr,
	&dev_attr_bootloader_version.attr,
	&dev_attr_reset_reason.attr,
	&dev_attr_update_firmware.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(ziirave_wdt);

अटल पूर्णांक ziirave_wdt_init_duration(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	अगर (!reset_duration) अणु
		/* See अगर the reset pulse duration is provided in an of_node */
		अगर (!client->dev.of_node)
			ret = -ENODEV;
		अन्यथा
			ret = of_property_पढ़ो_u32(client->dev.of_node,
						   "reset-duration-ms",
						   &reset_duration);
		अगर (ret) अणु
			dev_info(&client->dev,
			 "No reset pulse duration specified, using default\n");
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (reset_duration < 1 || reset_duration > 255)
		वापस -EINVAL;

	dev_info(&client->dev, "Setting reset duration to %dms",
		 reset_duration);

	वापस i2c_smbus_ग_लिखो_byte_data(client, ZIIRAVE_WDT_RESET_DURATION,
					 reset_duration);
पूर्ण

अटल पूर्णांक ziirave_wdt_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा ziirave_wdt_data *w_priv;
	पूर्णांक val;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE |
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WRITE_BLOCK_DATA))
		वापस -ENODEV;

	w_priv = devm_kzalloc(&client->dev, माप(*w_priv), GFP_KERNEL);
	अगर (!w_priv)
		वापस -ENOMEM;

	mutex_init(&w_priv->sysfs_mutex);

	w_priv->wdd.info = &ziirave_wdt_info;
	w_priv->wdd.ops = &ziirave_wdt_ops;
	w_priv->wdd.min_समयout = ZIIRAVE_TIMEOUT_MIN;
	w_priv->wdd.max_समयout = ZIIRAVE_TIMEOUT_MAX;
	w_priv->wdd.parent = &client->dev;
	w_priv->wdd.groups = ziirave_wdt_groups;

	watchकरोg_init_समयout(&w_priv->wdd, wdt_समयout, &client->dev);

	/*
	 * The शेष value set in the watchकरोg should be perfectly valid, so
	 * pass that in अगर we haven't provided one via the module parameter or
	 * of property.
	 */
	अगर (w_priv->wdd.समयout == 0) अणु
		val = i2c_smbus_पढ़ो_byte_data(client, ZIIRAVE_WDT_TIMEOUT);
		अगर (val < 0) अणु
			dev_err(&client->dev, "Failed to read timeout\n");
			वापस val;
		पूर्ण

		अगर (val > ZIIRAVE_TIMEOUT_MAX ||
		    val < ZIIRAVE_TIMEOUT_MIN)
			val = ZIIRAVE_TIMEOUT_DEFAULT;

		w_priv->wdd.समयout = val;
	पूर्ण

	ret = ziirave_wdt_set_समयout(&w_priv->wdd, w_priv->wdd.समयout);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to set timeout\n");
		वापस ret;
	पूर्ण

	dev_info(&client->dev, "Timeout set to %ds\n", w_priv->wdd.समयout);

	watchकरोg_set_nowayout(&w_priv->wdd, nowayout);

	i2c_set_clientdata(client, w_priv);

	/* If in unconfigured state, set to stopped */
	val = i2c_smbus_पढ़ो_byte_data(client, ZIIRAVE_WDT_STATE);
	अगर (val < 0) अणु
		dev_err(&client->dev, "Failed to read state\n");
		वापस val;
	पूर्ण

	अगर (val == ZIIRAVE_STATE_INITIAL)
		ziirave_wdt_stop(&w_priv->wdd);

	ret = ziirave_wdt_init_duration(client);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to init duration\n");
		वापस ret;
	पूर्ण

	ret = ziirave_wdt_revision(client, &w_priv->firmware_rev,
				   ZIIRAVE_WDT_FIRM_VER_MAJOR);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to read firmware version\n");
		वापस ret;
	पूर्ण

	dev_info(&client->dev,
		 "Firmware version: " ZIIRAVE_FW_VERSION_FMT "\n",
		 w_priv->firmware_rev.major, w_priv->firmware_rev.minor);

	ret = ziirave_wdt_revision(client, &w_priv->bootloader_rev,
				   ZIIRAVE_WDT_BOOT_VER_MAJOR);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to read bootloader version\n");
		वापस ret;
	पूर्ण

	dev_info(&client->dev,
		 "Bootloader version: " ZIIRAVE_BL_VERSION_FMT "\n",
		 w_priv->bootloader_rev.major, w_priv->bootloader_rev.minor);

	w_priv->reset_reason = i2c_smbus_पढ़ो_byte_data(client,
						ZIIRAVE_WDT_RESET_REASON);
	अगर (w_priv->reset_reason < 0) अणु
		dev_err(&client->dev, "Failed to read reset reason\n");
		वापस w_priv->reset_reason;
	पूर्ण

	अगर (w_priv->reset_reason >= ARRAY_SIZE(ziirave_reasons) ||
	    !ziirave_reasons[w_priv->reset_reason]) अणु
		dev_err(&client->dev, "Invalid reset reason\n");
		वापस -ENODEV;
	पूर्ण

	ret = watchकरोg_रेजिस्टर_device(&w_priv->wdd);

	वापस ret;
पूर्ण

अटल पूर्णांक ziirave_wdt_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ziirave_wdt_data *w_priv = i2c_get_clientdata(client);

	watchकरोg_unरेजिस्टर_device(&w_priv->wdd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ziirave_wdt_id[] = अणु
	अणु "rave-wdt", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ziirave_wdt_id);

अटल स्थिर काष्ठा of_device_id zrv_wdt_of_match[] = अणु
	अणु .compatible = "zii,rave-wdt", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, zrv_wdt_of_match);

अटल काष्ठा i2c_driver ziirave_wdt_driver = अणु
	.driver = अणु
		.name = "ziirave_wdt",
		.of_match_table = zrv_wdt_of_match,
	पूर्ण,
	.probe = ziirave_wdt_probe,
	.हटाओ = ziirave_wdt_हटाओ,
	.id_table = ziirave_wdt_id,
पूर्ण;

module_i2c_driver(ziirave_wdt_driver);

MODULE_AUTHOR("Martyn Welch <martyn.welch@collabora.co.uk");
MODULE_DESCRIPTION("Zodiac Aerospace RAVE Switch Watchdog Processor Driver");
MODULE_LICENSE("GPL");
