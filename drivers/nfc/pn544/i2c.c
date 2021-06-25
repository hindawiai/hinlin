<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C Link Layer क्रम PN544 HCI based Driver
 *
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/crc-ccitt.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/nfc.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <net/nfc/hci.h>
#समावेश <net/nfc/llc.h>
#समावेश <net/nfc/nfc.h>

#समावेश "pn544.h"

#घोषणा PN544_I2C_FRAME_HEADROOM 1
#घोषणा PN544_I2C_FRAME_TAILROOM 2

/* GPIO names */
#घोषणा PN544_GPIO_NAME_IRQ "pn544_irq"
#घोषणा PN544_GPIO_NAME_FW  "pn544_fw"
#घोषणा PN544_GPIO_NAME_EN  "pn544_en"

/* framing in HCI mode */
#घोषणा PN544_HCI_I2C_LLC_LEN		1
#घोषणा PN544_HCI_I2C_LLC_CRC		2
#घोषणा PN544_HCI_I2C_LLC_LEN_CRC	(PN544_HCI_I2C_LLC_LEN + \
					 PN544_HCI_I2C_LLC_CRC)
#घोषणा PN544_HCI_I2C_LLC_MIN_SIZE	(1 + PN544_HCI_I2C_LLC_LEN_CRC)
#घोषणा PN544_HCI_I2C_LLC_MAX_PAYLOAD	29
#घोषणा PN544_HCI_I2C_LLC_MAX_SIZE	(PN544_HCI_I2C_LLC_LEN_CRC + 1 + \
					 PN544_HCI_I2C_LLC_MAX_PAYLOAD)

अटल स्थिर काष्ठा i2c_device_id pn544_hci_i2c_id_table[] = अणु
	अणु"pn544", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, pn544_hci_i2c_id_table);

अटल स्थिर काष्ठा acpi_device_id pn544_hci_i2c_acpi_match[] = अणु
	अणु"NXP5440", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, pn544_hci_i2c_acpi_match);

#घोषणा PN544_HCI_I2C_DRIVER_NAME "pn544_hci_i2c"

/*
 * Exposed through the 4 most signअगरicant bytes
 * from the HCI SW_VERSION first byte, a.k.a.
 * SW RomLib.
 */
#घोषणा PN544_HW_VARIANT_C2 0xa
#घोषणा PN544_HW_VARIANT_C3 0xb

#घोषणा PN544_FW_CMD_RESET 0x01
#घोषणा PN544_FW_CMD_WRITE 0x08
#घोषणा PN544_FW_CMD_CHECK 0x06
#घोषणा PN544_FW_CMD_SECURE_WRITE 0x0C
#घोषणा PN544_FW_CMD_SECURE_CHUNK_WRITE 0x0D

काष्ठा pn544_i2c_fw_frame_ग_लिखो अणु
	u8 cmd;
	u16 be_length;
	u8 be_dest_addr[3];
	u16 be_datalen;
	u8 data[];
पूर्ण __packed;

काष्ठा pn544_i2c_fw_frame_check अणु
	u8 cmd;
	u16 be_length;
	u8 be_start_addr[3];
	u16 be_datalen;
	u16 be_crc;
पूर्ण __packed;

काष्ठा pn544_i2c_fw_frame_response अणु
	u8 status;
	u16 be_length;
पूर्ण __packed;

काष्ठा pn544_i2c_fw_blob अणु
	u32 be_size;
	u32 be_destaddr;
	u8 data[];
पूर्ण;

काष्ठा pn544_i2c_fw_secure_frame अणु
	u8 cmd;
	u16 be_datalen;
	u8 data[];
पूर्ण __packed;

काष्ठा pn544_i2c_fw_secure_blob अणु
	u64 header;
	u8 data[];
पूर्ण;

#घोषणा PN544_FW_CMD_RESULT_TIMEOUT 0x01
#घोषणा PN544_FW_CMD_RESULT_BAD_CRC 0x02
#घोषणा PN544_FW_CMD_RESULT_ACCESS_DENIED 0x08
#घोषणा PN544_FW_CMD_RESULT_PROTOCOL_ERROR 0x0B
#घोषणा PN544_FW_CMD_RESULT_INVALID_PARAMETER 0x11
#घोषणा PN544_FW_CMD_RESULT_UNSUPPORTED_COMMAND 0x13
#घोषणा PN544_FW_CMD_RESULT_INVALID_LENGTH 0x18
#घोषणा PN544_FW_CMD_RESULT_CRYPTOGRAPHIC_ERROR 0x19
#घोषणा PN544_FW_CMD_RESULT_VERSION_CONDITIONS_ERROR 0x1D
#घोषणा PN544_FW_CMD_RESULT_MEMORY_ERROR 0x20
#घोषणा PN544_FW_CMD_RESULT_CHUNK_OK 0x21
#घोषणा PN544_FW_CMD_RESULT_WRITE_FAILED 0x74
#घोषणा PN544_FW_CMD_RESULT_COMMAND_REJECTED 0xE0
#घोषणा PN544_FW_CMD_RESULT_CHUNK_ERROR 0xE6

#घोषणा MIN(X, Y) ((X) < (Y) ? (X) : (Y))

#घोषणा PN544_FW_WRITE_BUFFER_MAX_LEN 0x9f7
#घोषणा PN544_FW_I2C_MAX_PAYLOAD PN544_HCI_I2C_LLC_MAX_SIZE
#घोषणा PN544_FW_I2C_WRITE_FRAME_HEADER_LEN 8
#घोषणा PN544_FW_I2C_WRITE_DATA_MAX_LEN MIN((PN544_FW_I2C_MAX_PAYLOAD -\
					 PN544_FW_I2C_WRITE_FRAME_HEADER_LEN),\
					 PN544_FW_WRITE_BUFFER_MAX_LEN)
#घोषणा PN544_FW_SECURE_CHUNK_WRITE_HEADER_LEN 3
#घोषणा PN544_FW_SECURE_CHUNK_WRITE_DATA_MAX_LEN (PN544_FW_I2C_MAX_PAYLOAD -\
			PN544_FW_SECURE_CHUNK_WRITE_HEADER_LEN)
#घोषणा PN544_FW_SECURE_FRAME_HEADER_LEN 3
#घोषणा PN544_FW_SECURE_BLOB_HEADER_LEN 8

#घोषणा FW_WORK_STATE_IDLE 1
#घोषणा FW_WORK_STATE_START 2
#घोषणा FW_WORK_STATE_WAIT_WRITE_ANSWER 3
#घोषणा FW_WORK_STATE_WAIT_CHECK_ANSWER 4
#घोषणा FW_WORK_STATE_WAIT_SECURE_WRITE_ANSWER 5

काष्ठा pn544_i2c_phy अणु
	काष्ठा i2c_client *i2c_dev;
	काष्ठा nfc_hci_dev *hdev;

	काष्ठा gpio_desc *gpiod_en;
	काष्ठा gpio_desc *gpiod_fw;

	अचिन्हित पूर्णांक en_polarity;

	u8 hw_variant;

	काष्ठा work_काष्ठा fw_work;
	पूर्णांक fw_work_state;
	अक्षर firmware_name[NFC_FIRMWARE_NAME_MAXSIZE + 1];
	स्थिर काष्ठा firmware *fw;
	u32 fw_blob_dest_addr;
	माप_प्रकार fw_blob_size;
	स्थिर u8 *fw_blob_data;
	माप_प्रकार fw_written;
	माप_प्रकार fw_size;

	पूर्णांक fw_cmd_result;

	पूर्णांक घातered;
	पूर्णांक run_mode;

	पूर्णांक hard_fault;		/*
				 * < 0 अगर hardware error occured (e.g. i2c err)
				 * and prevents normal operation.
				 */
पूर्ण;

#घोषणा I2C_DUMP_SKB(info, skb)					\
करो अणु								\
	pr_debug("%s:\n", info);				\
	prपूर्णांक_hex_dump(KERN_DEBUG, "i2c: ", DUMP_PREFIX_OFFSET,	\
		       16, 1, (skb)->data, (skb)->len, 0);	\
पूर्ण जबतक (0)

अटल व्योम pn544_hci_i2c_platक्रमm_init(काष्ठा pn544_i2c_phy *phy)
अणु
	पूर्णांक polarity, retry, ret;
	अक्षर rset_cmd[] = अणु 0x05, 0xF9, 0x04, 0x00, 0xC3, 0xE5 पूर्ण;
	पूर्णांक count = माप(rset_cmd);

	nfc_info(&phy->i2c_dev->dev, "Detecting nfc_en polarity\n");

	/* Disable fw करोwnload */
	gpiod_set_value_cansleep(phy->gpiod_fw, 0);

	क्रम (polarity = 0; polarity < 2; polarity++) अणु
		phy->en_polarity = polarity;
		retry = 3;
		जबतक (retry--) अणु
			/* घातer off */
			gpiod_set_value_cansleep(phy->gpiod_en, !phy->en_polarity);
			usleep_range(10000, 15000);

			/* घातer on */
			gpiod_set_value_cansleep(phy->gpiod_en, phy->en_polarity);
			usleep_range(10000, 15000);

			/* send reset */
			dev_dbg(&phy->i2c_dev->dev, "Sending reset cmd\n");
			ret = i2c_master_send(phy->i2c_dev, rset_cmd, count);
			अगर (ret == count) अणु
				nfc_info(&phy->i2c_dev->dev,
					 "nfc_en polarity : active %s\n",
					 (polarity == 0 ? "low" : "high"));
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	nfc_err(&phy->i2c_dev->dev,
		"Could not detect nfc_en polarity, fallback to active high\n");

out:
	gpiod_set_value_cansleep(phy->gpiod_en, !phy->en_polarity);
	usleep_range(10000, 15000);
पूर्ण

अटल व्योम pn544_hci_i2c_enable_mode(काष्ठा pn544_i2c_phy *phy, पूर्णांक run_mode)
अणु
	gpiod_set_value_cansleep(phy->gpiod_fw, run_mode == PN544_FW_MODE ? 1 : 0);
	gpiod_set_value_cansleep(phy->gpiod_en, phy->en_polarity);
	usleep_range(10000, 15000);

	phy->run_mode = run_mode;
पूर्ण

अटल पूर्णांक pn544_hci_i2c_enable(व्योम *phy_id)
अणु
	काष्ठा pn544_i2c_phy *phy = phy_id;

	pr_info("%s\n", __func__);

	pn544_hci_i2c_enable_mode(phy, PN544_HCI_MODE);

	phy->घातered = 1;

	वापस 0;
पूर्ण

अटल व्योम pn544_hci_i2c_disable(व्योम *phy_id)
अणु
	काष्ठा pn544_i2c_phy *phy = phy_id;

	gpiod_set_value_cansleep(phy->gpiod_fw, 0);
	gpiod_set_value_cansleep(phy->gpiod_en, !phy->en_polarity);
	usleep_range(10000, 15000);

	gpiod_set_value_cansleep(phy->gpiod_en, phy->en_polarity);
	usleep_range(10000, 15000);

	gpiod_set_value_cansleep(phy->gpiod_en, !phy->en_polarity);
	usleep_range(10000, 15000);

	phy->घातered = 0;
पूर्ण

अटल व्योम pn544_hci_i2c_add_len_crc(काष्ठा sk_buff *skb)
अणु
	u16 crc;
	पूर्णांक len;

	len = skb->len + 2;
	*(u8 *)skb_push(skb, 1) = len;

	crc = crc_ccitt(0xffff, skb->data, skb->len);
	crc = ~crc;
	skb_put_u8(skb, crc & 0xff);
	skb_put_u8(skb, crc >> 8);
पूर्ण

अटल व्योम pn544_hci_i2c_हटाओ_len_crc(काष्ठा sk_buff *skb)
अणु
	skb_pull(skb, PN544_I2C_FRAME_HEADROOM);
	skb_trim(skb, PN544_I2C_FRAME_TAILROOM);
पूर्ण

/*
 * Writing a frame must not वापस the number of written bytes.
 * It must वापस either zero क्रम success, or <0 क्रम error.
 * In addition, it must not alter the skb
 */
अटल पूर्णांक pn544_hci_i2c_ग_लिखो(व्योम *phy_id, काष्ठा sk_buff *skb)
अणु
	पूर्णांक r;
	काष्ठा pn544_i2c_phy *phy = phy_id;
	काष्ठा i2c_client *client = phy->i2c_dev;

	अगर (phy->hard_fault != 0)
		वापस phy->hard_fault;

	usleep_range(3000, 6000);

	pn544_hci_i2c_add_len_crc(skb);

	I2C_DUMP_SKB("i2c frame written", skb);

	r = i2c_master_send(client, skb->data, skb->len);

	अगर (r == -EREMOTEIO) अणु	/* Retry, chip was in standby */
		usleep_range(6000, 10000);
		r = i2c_master_send(client, skb->data, skb->len);
	पूर्ण

	अगर (r >= 0) अणु
		अगर (r != skb->len)
			r = -EREMOTEIO;
		अन्यथा
			r = 0;
	पूर्ण

	pn544_hci_i2c_हटाओ_len_crc(skb);

	वापस r;
पूर्ण

अटल पूर्णांक check_crc(u8 *buf, पूर्णांक buflen)
अणु
	पूर्णांक len;
	u16 crc;

	len = buf[0] + 1;
	crc = crc_ccitt(0xffff, buf, len - 2);
	crc = ~crc;

	अगर (buf[len - 2] != (crc & 0xff) || buf[len - 1] != (crc >> 8)) अणु
		pr_err("CRC error 0x%x != 0x%x 0x%x\n",
		       crc, buf[len - 1], buf[len - 2]);
		pr_info("%s: BAD CRC\n", __func__);
		prपूर्णांक_hex_dump(KERN_DEBUG, "crc: ", DUMP_PREFIX_NONE,
			       16, 2, buf, buflen, false);
		वापस -EPERM;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Reads an shdlc frame and वापसs it in a newly allocated sk_buff. Guarantees
 * that i2c bus will be flushed and that next पढ़ो will start on a new frame.
 * वापसed skb contains only LLC header and payload.
 * वापसs:
 * -EREMOTEIO : i2c पढ़ो error (fatal)
 * -EBADMSG : frame was incorrect and discarded
 * -ENOMEM : cannot allocate skb, frame dropped
 */
अटल पूर्णांक pn544_hci_i2c_पढ़ो(काष्ठा pn544_i2c_phy *phy, काष्ठा sk_buff **skb)
अणु
	पूर्णांक r;
	u8 len;
	u8 पंचांगp[PN544_HCI_I2C_LLC_MAX_SIZE - 1];
	काष्ठा i2c_client *client = phy->i2c_dev;

	r = i2c_master_recv(client, &len, 1);
	अगर (r != 1) अणु
		nfc_err(&client->dev, "cannot read len byte\n");
		वापस -EREMOTEIO;
	पूर्ण

	अगर ((len < (PN544_HCI_I2C_LLC_MIN_SIZE - 1)) ||
	    (len > (PN544_HCI_I2C_LLC_MAX_SIZE - 1))) अणु
		nfc_err(&client->dev, "invalid len byte\n");
		r = -EBADMSG;
		जाओ flush;
	पूर्ण

	*skb = alloc_skb(1 + len, GFP_KERNEL);
	अगर (*skb == शून्य) अणु
		r = -ENOMEM;
		जाओ flush;
	पूर्ण

	skb_put_u8(*skb, len);

	r = i2c_master_recv(client, skb_put(*skb, len), len);
	अगर (r != len) अणु
		kमुक्त_skb(*skb);
		वापस -EREMOTEIO;
	पूर्ण

	I2C_DUMP_SKB("i2c frame read", *skb);

	r = check_crc((*skb)->data, (*skb)->len);
	अगर (r != 0) अणु
		kमुक्त_skb(*skb);
		r = -EBADMSG;
		जाओ flush;
	पूर्ण

	skb_pull(*skb, 1);
	skb_trim(*skb, (*skb)->len - 2);

	usleep_range(3000, 6000);

	वापस 0;

flush:
	अगर (i2c_master_recv(client, पंचांगp, माप(पंचांगp)) < 0)
		r = -EREMOTEIO;

	usleep_range(3000, 6000);

	वापस r;
पूर्ण

अटल पूर्णांक pn544_hci_i2c_fw_पढ़ो_status(काष्ठा pn544_i2c_phy *phy)
अणु
	पूर्णांक r;
	काष्ठा pn544_i2c_fw_frame_response response;
	काष्ठा i2c_client *client = phy->i2c_dev;

	r = i2c_master_recv(client, (अक्षर *) &response, माप(response));
	अगर (r != माप(response)) अणु
		nfc_err(&client->dev, "cannot read fw status\n");
		वापस -EIO;
	पूर्ण

	usleep_range(3000, 6000);

	चयन (response.status) अणु
	हाल 0:
		वापस 0;
	हाल PN544_FW_CMD_RESULT_CHUNK_OK:
		वापस response.status;
	हाल PN544_FW_CMD_RESULT_TIMEOUT:
		वापस -ETIMEDOUT;
	हाल PN544_FW_CMD_RESULT_BAD_CRC:
		वापस -ENODATA;
	हाल PN544_FW_CMD_RESULT_ACCESS_DENIED:
		वापस -EACCES;
	हाल PN544_FW_CMD_RESULT_PROTOCOL_ERROR:
		वापस -EPROTO;
	हाल PN544_FW_CMD_RESULT_INVALID_PARAMETER:
		वापस -EINVAL;
	हाल PN544_FW_CMD_RESULT_UNSUPPORTED_COMMAND:
		वापस -ENOTSUPP;
	हाल PN544_FW_CMD_RESULT_INVALID_LENGTH:
		वापस -EBADMSG;
	हाल PN544_FW_CMD_RESULT_CRYPTOGRAPHIC_ERROR:
		वापस -ENOKEY;
	हाल PN544_FW_CMD_RESULT_VERSION_CONDITIONS_ERROR:
		वापस -EINVAL;
	हाल PN544_FW_CMD_RESULT_MEMORY_ERROR:
		वापस -ENOMEM;
	हाल PN544_FW_CMD_RESULT_COMMAND_REJECTED:
		वापस -EACCES;
	हाल PN544_FW_CMD_RESULT_WRITE_FAILED:
	हाल PN544_FW_CMD_RESULT_CHUNK_ERROR:
		वापस -EIO;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

/*
 * Reads an shdlc frame from the chip. This is not as straightक्रमward as it
 * seems. There are हालs where we could loose the frame start synchronization.
 * The frame क्रमmat is len-data-crc, and corruption can occur anywhere जबतक
 * transiting on i2c bus, such that we could पढ़ो an invalid len.
 * In order to recover synchronization with the next frame, we must be sure
 * to पढ़ो the real amount of data without using the len byte. We करो this by
 * assuming the following:
 * - the chip will always present only one single complete frame on the bus
 *   beक्रमe triggering the पूर्णांकerrupt
 * - the chip will not present a new frame until we have completely पढ़ो
 *   the previous one (or until we have handled the पूर्णांकerrupt).
 * The tricky हाल is when we पढ़ो a corrupted len that is less than the real
 * len. We must detect this here in order to determine that we need to flush
 * the bus. This is the reason why we check the crc here.
 */
अटल irqवापस_t pn544_hci_i2c_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *phy_id)
अणु
	काष्ठा pn544_i2c_phy *phy = phy_id;
	काष्ठा i2c_client *client;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक r;

	अगर (!phy || irq != phy->i2c_dev->irq) अणु
		WARN_ON_ONCE(1);
		वापस IRQ_NONE;
	पूर्ण

	client = phy->i2c_dev;
	dev_dbg(&client->dev, "IRQ\n");

	अगर (phy->hard_fault != 0)
		वापस IRQ_HANDLED;

	अगर (phy->run_mode == PN544_FW_MODE) अणु
		phy->fw_cmd_result = pn544_hci_i2c_fw_पढ़ो_status(phy);
		schedule_work(&phy->fw_work);
	पूर्ण अन्यथा अणु
		r = pn544_hci_i2c_पढ़ो(phy, &skb);
		अगर (r == -EREMOTEIO) अणु
			phy->hard_fault = r;

			nfc_hci_recv_frame(phy->hdev, शून्य);

			वापस IRQ_HANDLED;
		पूर्ण अन्यथा अगर ((r == -ENOMEM) || (r == -EBADMSG)) अणु
			वापस IRQ_HANDLED;
		पूर्ण

		nfc_hci_recv_frame(phy->hdev, skb);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा nfc_phy_ops i2c_phy_ops = अणु
	.ग_लिखो = pn544_hci_i2c_ग_लिखो,
	.enable = pn544_hci_i2c_enable,
	.disable = pn544_hci_i2c_disable,
पूर्ण;

अटल पूर्णांक pn544_hci_i2c_fw_करोwnload(व्योम *phy_id, स्थिर अक्षर *firmware_name,
					u8 hw_variant)
अणु
	काष्ठा pn544_i2c_phy *phy = phy_id;

	pr_info("Starting Firmware Download (%s)\n", firmware_name);

	म_नकल(phy->firmware_name, firmware_name);

	phy->hw_variant = hw_variant;
	phy->fw_work_state = FW_WORK_STATE_START;

	schedule_work(&phy->fw_work);

	वापस 0;
पूर्ण

अटल व्योम pn544_hci_i2c_fw_work_complete(काष्ठा pn544_i2c_phy *phy,
					   पूर्णांक result)
अणु
	pr_info("Firmware Download Complete, result=%d\n", result);

	pn544_hci_i2c_disable(phy);

	phy->fw_work_state = FW_WORK_STATE_IDLE;

	अगर (phy->fw) अणु
		release_firmware(phy->fw);
		phy->fw = शून्य;
	पूर्ण

	nfc_fw_करोwnload_करोne(phy->hdev->ndev, phy->firmware_name, (u32) -result);
पूर्ण

अटल पूर्णांक pn544_hci_i2c_fw_ग_लिखो_cmd(काष्ठा i2c_client *client, u32 dest_addr,
				      स्थिर u8 *data, u16 datalen)
अणु
	u8 frame[PN544_FW_I2C_MAX_PAYLOAD];
	काष्ठा pn544_i2c_fw_frame_ग_लिखो *framep;
	u16 params_len;
	पूर्णांक framelen;
	पूर्णांक r;

	अगर (datalen > PN544_FW_I2C_WRITE_DATA_MAX_LEN)
		datalen = PN544_FW_I2C_WRITE_DATA_MAX_LEN;

	framep = (काष्ठा pn544_i2c_fw_frame_ग_लिखो *) frame;

	params_len = माप(framep->be_dest_addr) +
		     माप(framep->be_datalen) + datalen;
	framelen = params_len + माप(framep->cmd) +
			     माप(framep->be_length);

	framep->cmd = PN544_FW_CMD_WRITE;

	put_unaligned_be16(params_len, &framep->be_length);

	framep->be_dest_addr[0] = (dest_addr & 0xff0000) >> 16;
	framep->be_dest_addr[1] = (dest_addr & 0xff00) >> 8;
	framep->be_dest_addr[2] = dest_addr & 0xff;

	put_unaligned_be16(datalen, &framep->be_datalen);

	स_नकल(framep->data, data, datalen);

	r = i2c_master_send(client, frame, framelen);

	अगर (r == framelen)
		वापस datalen;
	अन्यथा अगर (r < 0)
		वापस r;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल पूर्णांक pn544_hci_i2c_fw_check_cmd(काष्ठा i2c_client *client, u32 start_addr,
				      स्थिर u8 *data, u16 datalen)
अणु
	काष्ठा pn544_i2c_fw_frame_check frame;
	पूर्णांक r;
	u16 crc;

	/* calculate local crc क्रम the data we want to check */
	crc = crc_ccitt(0xffff, data, datalen);

	frame.cmd = PN544_FW_CMD_CHECK;

	put_unaligned_be16(माप(frame.be_start_addr) +
			   माप(frame.be_datalen) + माप(frame.be_crc),
			   &frame.be_length);

	/* tell the chip the memory region to which our crc applies */
	frame.be_start_addr[0] = (start_addr & 0xff0000) >> 16;
	frame.be_start_addr[1] = (start_addr & 0xff00) >> 8;
	frame.be_start_addr[2] = start_addr & 0xff;

	put_unaligned_be16(datalen, &frame.be_datalen);

	/*
	 * and give our local crc. Chip will calculate its own crc क्रम the
	 * region and compare with ours.
	 */
	put_unaligned_be16(crc, &frame.be_crc);

	r = i2c_master_send(client, (स्थिर अक्षर *) &frame, माप(frame));

	अगर (r == माप(frame))
		वापस 0;
	अन्यथा अगर (r < 0)
		वापस r;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल पूर्णांक pn544_hci_i2c_fw_ग_लिखो_chunk(काष्ठा pn544_i2c_phy *phy)
अणु
	पूर्णांक r;

	r = pn544_hci_i2c_fw_ग_लिखो_cmd(phy->i2c_dev,
				       phy->fw_blob_dest_addr + phy->fw_written,
				       phy->fw_blob_data + phy->fw_written,
				       phy->fw_blob_size - phy->fw_written);
	अगर (r < 0)
		वापस r;

	phy->fw_written += r;
	phy->fw_work_state = FW_WORK_STATE_WAIT_WRITE_ANSWER;

	वापस 0;
पूर्ण

अटल पूर्णांक pn544_hci_i2c_fw_secure_ग_लिखो_frame_cmd(काष्ठा pn544_i2c_phy *phy,
					स्थिर u8 *data, u16 datalen)
अणु
	u8 buf[PN544_FW_I2C_MAX_PAYLOAD];
	काष्ठा pn544_i2c_fw_secure_frame *chunk;
	पूर्णांक chunklen;
	पूर्णांक r;

	अगर (datalen > PN544_FW_SECURE_CHUNK_WRITE_DATA_MAX_LEN)
		datalen = PN544_FW_SECURE_CHUNK_WRITE_DATA_MAX_LEN;

	chunk = (काष्ठा pn544_i2c_fw_secure_frame *) buf;

	chunk->cmd = PN544_FW_CMD_SECURE_CHUNK_WRITE;

	put_unaligned_be16(datalen, &chunk->be_datalen);

	स_नकल(chunk->data, data, datalen);

	chunklen = माप(chunk->cmd) + माप(chunk->be_datalen) + datalen;

	r = i2c_master_send(phy->i2c_dev, buf, chunklen);

	अगर (r == chunklen)
		वापस datalen;
	अन्यथा अगर (r < 0)
		वापस r;
	अन्यथा
		वापस -EIO;

पूर्ण

अटल पूर्णांक pn544_hci_i2c_fw_secure_ग_लिखो_frame(काष्ठा pn544_i2c_phy *phy)
अणु
	काष्ठा pn544_i2c_fw_secure_frame *framep;
	पूर्णांक r;

	framep = (काष्ठा pn544_i2c_fw_secure_frame *) phy->fw_blob_data;
	अगर (phy->fw_written == 0)
		phy->fw_blob_size = get_unaligned_be16(&framep->be_datalen)
				+ PN544_FW_SECURE_FRAME_HEADER_LEN;

	/* Only secure ग_लिखो command can be chunked*/
	अगर (phy->fw_blob_size > PN544_FW_I2C_MAX_PAYLOAD &&
			framep->cmd != PN544_FW_CMD_SECURE_WRITE)
		वापस -EINVAL;

	/* The firmware also have other commands, we just send them directly */
	अगर (phy->fw_blob_size < PN544_FW_I2C_MAX_PAYLOAD) अणु
		r = i2c_master_send(phy->i2c_dev,
			(स्थिर अक्षर *) phy->fw_blob_data, phy->fw_blob_size);

		अगर (r == phy->fw_blob_size)
			जाओ निकास;
		अन्यथा अगर (r < 0)
			वापस r;
		अन्यथा
			वापस -EIO;
	पूर्ण

	r = pn544_hci_i2c_fw_secure_ग_लिखो_frame_cmd(phy,
				       phy->fw_blob_data + phy->fw_written,
				       phy->fw_blob_size - phy->fw_written);
	अगर (r < 0)
		वापस r;

निकास:
	phy->fw_written += r;
	phy->fw_work_state = FW_WORK_STATE_WAIT_SECURE_WRITE_ANSWER;

	/* SW reset command will not trig any response from PN544 */
	अगर (framep->cmd == PN544_FW_CMD_RESET) अणु
		pn544_hci_i2c_enable_mode(phy, PN544_FW_MODE);
		phy->fw_cmd_result = 0;
		schedule_work(&phy->fw_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pn544_hci_i2c_fw_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pn544_i2c_phy *phy = container_of(work, काष्ठा pn544_i2c_phy,
						fw_work);
	पूर्णांक r;
	काष्ठा pn544_i2c_fw_blob *blob;
	काष्ठा pn544_i2c_fw_secure_blob *secure_blob;

	चयन (phy->fw_work_state) अणु
	हाल FW_WORK_STATE_START:
		pn544_hci_i2c_enable_mode(phy, PN544_FW_MODE);

		r = request_firmware(&phy->fw, phy->firmware_name,
				     &phy->i2c_dev->dev);
		अगर (r < 0)
			जाओ निकास_state_start;

		phy->fw_written = 0;

		चयन (phy->hw_variant) अणु
		हाल PN544_HW_VARIANT_C2:
			blob = (काष्ठा pn544_i2c_fw_blob *) phy->fw->data;
			phy->fw_blob_size = get_unaligned_be32(&blob->be_size);
			phy->fw_blob_dest_addr = get_unaligned_be32(
							&blob->be_destaddr);
			phy->fw_blob_data = blob->data;

			r = pn544_hci_i2c_fw_ग_लिखो_chunk(phy);
			अवरोध;
		हाल PN544_HW_VARIANT_C3:
			secure_blob = (काष्ठा pn544_i2c_fw_secure_blob *)
								phy->fw->data;
			phy->fw_blob_data = secure_blob->data;
			phy->fw_size = phy->fw->size;
			r = pn544_hci_i2c_fw_secure_ग_लिखो_frame(phy);
			अवरोध;
		शेष:
			r = -ENOTSUPP;
			अवरोध;
		पूर्ण

निकास_state_start:
		अगर (r < 0)
			pn544_hci_i2c_fw_work_complete(phy, r);
		अवरोध;

	हाल FW_WORK_STATE_WAIT_WRITE_ANSWER:
		r = phy->fw_cmd_result;
		अगर (r < 0)
			जाओ निकास_state_रुको_ग_लिखो_answer;

		अगर (phy->fw_written == phy->fw_blob_size) अणु
			r = pn544_hci_i2c_fw_check_cmd(phy->i2c_dev,
						       phy->fw_blob_dest_addr,
						       phy->fw_blob_data,
						       phy->fw_blob_size);
			अगर (r < 0)
				जाओ निकास_state_रुको_ग_लिखो_answer;
			phy->fw_work_state = FW_WORK_STATE_WAIT_CHECK_ANSWER;
			अवरोध;
		पूर्ण

		r = pn544_hci_i2c_fw_ग_लिखो_chunk(phy);

निकास_state_रुको_ग_लिखो_answer:
		अगर (r < 0)
			pn544_hci_i2c_fw_work_complete(phy, r);
		अवरोध;

	हाल FW_WORK_STATE_WAIT_CHECK_ANSWER:
		r = phy->fw_cmd_result;
		अगर (r < 0)
			जाओ निकास_state_रुको_check_answer;

		blob = (काष्ठा pn544_i2c_fw_blob *) (phy->fw_blob_data +
		       phy->fw_blob_size);
		phy->fw_blob_size = get_unaligned_be32(&blob->be_size);
		अगर (phy->fw_blob_size != 0) अणु
			phy->fw_blob_dest_addr =
					get_unaligned_be32(&blob->be_destaddr);
			phy->fw_blob_data = blob->data;

			phy->fw_written = 0;
			r = pn544_hci_i2c_fw_ग_लिखो_chunk(phy);
		पूर्ण

निकास_state_रुको_check_answer:
		अगर (r < 0 || phy->fw_blob_size == 0)
			pn544_hci_i2c_fw_work_complete(phy, r);
		अवरोध;

	हाल FW_WORK_STATE_WAIT_SECURE_WRITE_ANSWER:
		r = phy->fw_cmd_result;
		अगर (r < 0)
			जाओ निकास_state_रुको_secure_ग_लिखो_answer;

		अगर (r == PN544_FW_CMD_RESULT_CHUNK_OK) अणु
			r = pn544_hci_i2c_fw_secure_ग_लिखो_frame(phy);
			जाओ निकास_state_रुको_secure_ग_लिखो_answer;
		पूर्ण

		अगर (phy->fw_written == phy->fw_blob_size) अणु
			secure_blob = (काष्ठा pn544_i2c_fw_secure_blob *)
				(phy->fw_blob_data + phy->fw_blob_size);
			phy->fw_size -= phy->fw_blob_size +
				PN544_FW_SECURE_BLOB_HEADER_LEN;
			अगर (phy->fw_size >= PN544_FW_SECURE_BLOB_HEADER_LEN
					+ PN544_FW_SECURE_FRAME_HEADER_LEN) अणु
				phy->fw_blob_data = secure_blob->data;

				phy->fw_written = 0;
				r = pn544_hci_i2c_fw_secure_ग_लिखो_frame(phy);
			पूर्ण
		पूर्ण

निकास_state_रुको_secure_ग_लिखो_answer:
		अगर (r < 0 || phy->fw_size == 0)
			pn544_hci_i2c_fw_work_complete(phy, r);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा acpi_gpio_params enable_gpios = अणु 1, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params firmware_gpios = अणु 2, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_pn544_gpios[] = अणु
	अणु "enable-gpios", &enable_gpios, 1 पूर्ण,
	अणु "firmware-gpios", &firmware_gpios, 1 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक pn544_hci_i2c_probe(काष्ठा i2c_client *client,
			       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा pn544_i2c_phy *phy;
	पूर्णांक r = 0;

	dev_dbg(&client->dev, "%s\n", __func__);
	dev_dbg(&client->dev, "IRQ: %d\n", client->irq);

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		nfc_err(&client->dev, "Need I2C_FUNC_I2C\n");
		वापस -ENODEV;
	पूर्ण

	phy = devm_kzalloc(&client->dev, माप(काष्ठा pn544_i2c_phy),
			   GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	INIT_WORK(&phy->fw_work, pn544_hci_i2c_fw_work);
	phy->fw_work_state = FW_WORK_STATE_IDLE;

	phy->i2c_dev = client;
	i2c_set_clientdata(client, phy);

	r = devm_acpi_dev_add_driver_gpios(dev, acpi_pn544_gpios);
	अगर (r)
		dev_dbg(dev, "Unable to add GPIO mapping table\n");

	/* Get EN GPIO */
	phy->gpiod_en = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(phy->gpiod_en)) अणु
		nfc_err(dev, "Unable to get EN GPIO\n");
		वापस PTR_ERR(phy->gpiod_en);
	पूर्ण

	/* Get FW GPIO */
	phy->gpiod_fw = devm_gpiod_get(dev, "firmware", GPIOD_OUT_LOW);
	अगर (IS_ERR(phy->gpiod_fw)) अणु
		nfc_err(dev, "Unable to get FW GPIO\n");
		वापस PTR_ERR(phy->gpiod_fw);
	पूर्ण

	pn544_hci_i2c_platक्रमm_init(phy);

	r = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
				      pn544_hci_i2c_irq_thपढ़ो_fn,
				      IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				      PN544_HCI_I2C_DRIVER_NAME, phy);
	अगर (r < 0) अणु
		nfc_err(&client->dev, "Unable to register IRQ handler\n");
		वापस r;
	पूर्ण

	r = pn544_hci_probe(phy, &i2c_phy_ops, LLC_SHDLC_NAME,
			    PN544_I2C_FRAME_HEADROOM, PN544_I2C_FRAME_TAILROOM,
			    PN544_HCI_I2C_LLC_MAX_PAYLOAD,
			    pn544_hci_i2c_fw_करोwnload, &phy->hdev);
	अगर (r < 0)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक pn544_hci_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा pn544_i2c_phy *phy = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "%s\n", __func__);

	cancel_work_sync(&phy->fw_work);
	अगर (phy->fw_work_state != FW_WORK_STATE_IDLE)
		pn544_hci_i2c_fw_work_complete(phy, -ENODEV);

	pn544_hci_हटाओ(phy->hdev);

	अगर (phy->घातered)
		pn544_hci_i2c_disable(phy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_pn544_i2c_match[] = अणु
	अणु .compatible = "nxp,pn544-i2c", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_pn544_i2c_match);

अटल काष्ठा i2c_driver pn544_hci_i2c_driver = अणु
	.driver = अणु
		   .name = PN544_HCI_I2C_DRIVER_NAME,
		   .of_match_table = of_match_ptr(of_pn544_i2c_match),
		   .acpi_match_table = ACPI_PTR(pn544_hci_i2c_acpi_match),
		  पूर्ण,
	.probe = pn544_hci_i2c_probe,
	.id_table = pn544_hci_i2c_id_table,
	.हटाओ = pn544_hci_i2c_हटाओ,
पूर्ण;

module_i2c_driver(pn544_hci_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
