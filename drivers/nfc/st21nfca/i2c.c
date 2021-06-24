<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C Link Layer क्रम ST21NFCA HCI based Driver
 * Copyright (C) 2014  STMicroelectronics SAS. All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/crc-ccitt.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/acpi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/nfc.h>
#समावेश <linux/firmware.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <net/nfc/hci.h>
#समावेश <net/nfc/llc.h>
#समावेश <net/nfc/nfc.h>

#समावेश "st21nfca.h"

/*
 * Every frame starts with ST21NFCA_SOF_खातापूर्ण and ends with ST21NFCA_SOF_खातापूर्ण.
 * Because ST21NFCA_SOF_खातापूर्ण is a possible data value, there is a mecanism
 * called byte stuffing has been पूर्णांकroduced.
 *
 * अगर byte == ST21NFCA_SOF_खातापूर्ण or ST21NFCA_ESCAPE_BYTE_STUFFING
 * - insert ST21NFCA_ESCAPE_BYTE_STUFFING (escape byte)
 * - xor byte with ST21NFCA_BYTE_STUFFING_MASK
 */
#घोषणा ST21NFCA_SOF_खातापूर्ण		0x7e
#घोषणा ST21NFCA_BYTE_STUFFING_MASK	0x20
#घोषणा ST21NFCA_ESCAPE_BYTE_STUFFING	0x7d

/* SOF + 00 */
#घोषणा ST21NFCA_FRAME_HEADROOM			2

/* 2 bytes crc + खातापूर्ण */
#घोषणा ST21NFCA_FRAME_TAILROOM 3
#घोषणा IS_START_OF_FRAME(buf) (buf[0] == ST21NFCA_SOF_खातापूर्ण && \
				buf[1] == 0)

#घोषणा ST21NFCA_HCI_DRIVER_NAME "st21nfca_hci"
#घोषणा ST21NFCA_HCI_I2C_DRIVER_NAME "st21nfca_hci_i2c"

काष्ठा st21nfca_i2c_phy अणु
	काष्ठा i2c_client *i2c_dev;
	काष्ठा nfc_hci_dev *hdev;

	काष्ठा gpio_desc *gpiod_ena;
	काष्ठा st21nfca_se_status se_status;

	काष्ठा sk_buff *pending_skb;
	पूर्णांक current_पढ़ो_len;
	/*
	 * crc might have fail because i2c macro
	 * is disable due to other पूर्णांकerface activity
	 */
	पूर्णांक crc_trials;

	पूर्णांक घातered;
	पूर्णांक run_mode;

	/*
	 * < 0 अगर hardware error occured (e.g. i2c err)
	 * and prevents normal operation.
	 */
	पूर्णांक hard_fault;
	काष्ठा mutex phy_lock;
पूर्ण;

अटल u8 len_seq[] = अणु 16, 24, 12, 29 पूर्ण;
अटल u16 रुको_tab[] = अणु 2, 3, 5, 15, 20, 40पूर्ण;

#घोषणा I2C_DUMP_SKB(info, skb)					\
करो अणु								\
	pr_debug("%s:\n", info);				\
	prपूर्णांक_hex_dump(KERN_DEBUG, "i2c: ", DUMP_PREFIX_OFFSET,	\
		       16, 1, (skb)->data, (skb)->len, 0);	\
पूर्ण जबतक (0)

/*
 * In order to get the CLF in a known state we generate an पूर्णांकernal reboot
 * using a proprietary command.
 * Once the reboot is completed, we expect to receive a ST21NFCA_SOF_खातापूर्ण
 * fill buffer.
 */
अटल पूर्णांक st21nfca_hci_platक्रमm_init(काष्ठा st21nfca_i2c_phy *phy)
अणु
	u16 रुको_reboot[] = अणु 50, 300, 1000 पूर्ण;
	अक्षर reboot_cmd[] = अणु 0x7E, 0x66, 0x48, 0xF6, 0x7E पूर्ण;
	u8 पंचांगp[ST21NFCA_HCI_LLC_MAX_SIZE];
	पूर्णांक i, r = -1;

	क्रम (i = 0; i < ARRAY_SIZE(रुको_reboot) && r < 0; i++) अणु
		r = i2c_master_send(phy->i2c_dev, reboot_cmd,
				    माप(reboot_cmd));
		अगर (r < 0)
			msleep(रुको_reboot[i]);
	पूर्ण
	अगर (r < 0)
		वापस r;

	/* CLF is spending about 20ms to करो an पूर्णांकernal reboot */
	msleep(20);
	r = -1;
	क्रम (i = 0; i < ARRAY_SIZE(रुको_reboot) && r < 0; i++) अणु
		r = i2c_master_recv(phy->i2c_dev, पंचांगp,
				    ST21NFCA_HCI_LLC_MAX_SIZE);
		अगर (r < 0)
			msleep(रुको_reboot[i]);
	पूर्ण
	अगर (r < 0)
		वापस r;

	क्रम (i = 0; i < ST21NFCA_HCI_LLC_MAX_SIZE &&
		पंचांगp[i] == ST21NFCA_SOF_खातापूर्ण; i++)
		;

	अगर (r != ST21NFCA_HCI_LLC_MAX_SIZE)
		वापस -ENODEV;

	usleep_range(1000, 1500);
	वापस 0;
पूर्ण

अटल पूर्णांक st21nfca_hci_i2c_enable(व्योम *phy_id)
अणु
	काष्ठा st21nfca_i2c_phy *phy = phy_id;

	gpiod_set_value(phy->gpiod_ena, 1);
	phy->घातered = 1;
	phy->run_mode = ST21NFCA_HCI_MODE;

	usleep_range(10000, 15000);

	वापस 0;
पूर्ण

अटल व्योम st21nfca_hci_i2c_disable(व्योम *phy_id)
अणु
	काष्ठा st21nfca_i2c_phy *phy = phy_id;

	gpiod_set_value(phy->gpiod_ena, 0);

	phy->घातered = 0;
पूर्ण

अटल व्योम st21nfca_hci_add_len_crc(काष्ठा sk_buff *skb)
अणु
	u16 crc;
	u8 पंचांगp;

	*(u8 *)skb_push(skb, 1) = 0;

	crc = crc_ccitt(0xffff, skb->data, skb->len);
	crc = ~crc;

	पंचांगp = crc & 0x00ff;
	skb_put_u8(skb, पंचांगp);

	पंचांगp = (crc >> 8) & 0x00ff;
	skb_put_u8(skb, पंचांगp);
पूर्ण

अटल व्योम st21nfca_hci_हटाओ_len_crc(काष्ठा sk_buff *skb)
अणु
	skb_pull(skb, ST21NFCA_FRAME_HEADROOM);
	skb_trim(skb, skb->len - ST21NFCA_FRAME_TAILROOM);
पूर्ण

/*
 * Writing a frame must not वापस the number of written bytes.
 * It must वापस either zero क्रम success, or <0 क्रम error.
 * In addition, it must not alter the skb
 */
अटल पूर्णांक st21nfca_hci_i2c_ग_लिखो(व्योम *phy_id, काष्ठा sk_buff *skb)
अणु
	पूर्णांक r = -1, i, j;
	काष्ठा st21nfca_i2c_phy *phy = phy_id;
	काष्ठा i2c_client *client = phy->i2c_dev;
	u8 पंचांगp[ST21NFCA_HCI_LLC_MAX_SIZE * 2];

	I2C_DUMP_SKB("st21nfca_hci_i2c_write", skb);

	अगर (phy->hard_fault != 0)
		वापस phy->hard_fault;

	/*
	 * Compute CRC beक्रमe byte stuffing computation on frame
	 * Note st21nfca_hci_add_len_crc is करोing a byte stuffing
	 * on its own value
	 */
	st21nfca_hci_add_len_crc(skb);

	/* add ST21NFCA_SOF_खातापूर्ण on tail */
	skb_put_u8(skb, ST21NFCA_SOF_खातापूर्ण);
	/* add ST21NFCA_SOF_खातापूर्ण on head */
	*(u8 *)skb_push(skb, 1) = ST21NFCA_SOF_खातापूर्ण;

	/*
	 * Compute byte stuffing
	 * अगर byte == ST21NFCA_SOF_खातापूर्ण or ST21NFCA_ESCAPE_BYTE_STUFFING
	 * insert ST21NFCA_ESCAPE_BYTE_STUFFING (escape byte)
	 * xor byte with ST21NFCA_BYTE_STUFFING_MASK
	 */
	पंचांगp[0] = skb->data[0];
	क्रम (i = 1, j = 1; i < skb->len - 1; i++, j++) अणु
		अगर (skb->data[i] == ST21NFCA_SOF_खातापूर्ण
		    || skb->data[i] == ST21NFCA_ESCAPE_BYTE_STUFFING) अणु
			पंचांगp[j] = ST21NFCA_ESCAPE_BYTE_STUFFING;
			j++;
			पंचांगp[j] = skb->data[i] ^ ST21NFCA_BYTE_STUFFING_MASK;
		पूर्ण अन्यथा अणु
			पंचांगp[j] = skb->data[i];
		पूर्ण
	पूर्ण
	पंचांगp[j] = skb->data[i];
	j++;

	/*
	 * Manage sleep mode
	 * Try 3 बार to send data with delay between each
	 */
	mutex_lock(&phy->phy_lock);
	क्रम (i = 0; i < ARRAY_SIZE(रुको_tab) && r < 0; i++) अणु
		r = i2c_master_send(client, पंचांगp, j);
		अगर (r < 0)
			msleep(रुको_tab[i]);
	पूर्ण
	mutex_unlock(&phy->phy_lock);

	अगर (r >= 0) अणु
		अगर (r != j)
			r = -EREMOTEIO;
		अन्यथा
			r = 0;
	पूर्ण

	st21nfca_hci_हटाओ_len_crc(skb);

	वापस r;
पूर्ण

अटल पूर्णांक get_frame_size(u8 *buf, पूर्णांक buflen)
अणु
	पूर्णांक len = 0;

	अगर (buf[len + 1] == ST21NFCA_SOF_खातापूर्ण)
		वापस 0;

	क्रम (len = 1; len < buflen && buf[len] != ST21NFCA_SOF_खातापूर्ण; len++)
		;

	वापस len;
पूर्ण

अटल पूर्णांक check_crc(u8 *buf, पूर्णांक buflen)
अणु
	u16 crc;

	crc = crc_ccitt(0xffff, buf, buflen - 2);
	crc = ~crc;

	अगर (buf[buflen - 2] != (crc & 0xff) || buf[buflen - 1] != (crc >> 8)) अणु
		pr_err(ST21NFCA_HCI_DRIVER_NAME
		       ": CRC error 0x%x != 0x%x 0x%x\n", crc, buf[buflen - 1],
		       buf[buflen - 2]);

		pr_info(DRIVER_DESC ": %s : BAD CRC\n", __func__);
		prपूर्णांक_hex_dump(KERN_DEBUG, "crc: ", DUMP_PREFIX_NONE,
			       16, 2, buf, buflen, false);
		वापस -EPERM;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Prepare received data क्रम upper layer.
 * Received data include byte stuffing, crc and sof/eof
 * which is not usable by hci part.
 * वापसs:
 * frame size without sof/eof, header and byte stuffing
 * -EBADMSG : frame was incorrect and discarded
 */
अटल पूर्णांक st21nfca_hci_i2c_repack(काष्ठा sk_buff *skb)
अणु
	पूर्णांक i, j, r, size;

	अगर (skb->len < 1 || (skb->len > 1 && skb->data[1] != 0))
		वापस -EBADMSG;

	size = get_frame_size(skb->data, skb->len);
	अगर (size > 0) अणु
		skb_trim(skb, size);
		/* हटाओ ST21NFCA byte stuffing क्रम upper layer */
		क्रम (i = 1, j = 0; i < skb->len; i++) अणु
			अगर (skb->data[i + j] ==
					(u8) ST21NFCA_ESCAPE_BYTE_STUFFING) अणु
				skb->data[i] = skb->data[i + j + 1]
						| ST21NFCA_BYTE_STUFFING_MASK;
				i++;
				j++;
			पूर्ण
			skb->data[i] = skb->data[i + j];
		पूर्ण
		/* हटाओ byte stuffing useless byte */
		skb_trim(skb, i - j);
		/* हटाओ ST21NFCA_SOF_खातापूर्ण from head */
		skb_pull(skb, 1);

		r = check_crc(skb->data, skb->len);
		अगर (r != 0) अणु
			i = 0;
			वापस -EBADMSG;
		पूर्ण

		/* हटाओ headbyte */
		skb_pull(skb, 1);
		/* हटाओ crc. Byte Stuffing is alपढ़ोy हटाओd here */
		skb_trim(skb, skb->len - 2);
		वापस skb->len;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Reads an shdlc frame and वापसs it in a newly allocated sk_buff. Guarantees
 * that i2c bus will be flushed and that next पढ़ो will start on a new frame.
 * वापसed skb contains only LLC header and payload.
 * वापसs:
 * frame size : अगर received frame is complete (find ST21NFCA_SOF_खातापूर्ण at
 * end of पढ़ो)
 * -EAGAIN : अगर received frame is incomplete (not find ST21NFCA_SOF_खातापूर्ण
 * at end of पढ़ो)
 * -EREMOTEIO : i2c पढ़ो error (fatal)
 * -EBADMSG : frame was incorrect and discarded
 * (value वापसed from st21nfca_hci_i2c_repack)
 * -EIO : अगर no ST21NFCA_SOF_खातापूर्ण is found after reaching
 * the पढ़ो length end sequence
 */
अटल पूर्णांक st21nfca_hci_i2c_पढ़ो(काष्ठा st21nfca_i2c_phy *phy,
				 काष्ठा sk_buff *skb)
अणु
	पूर्णांक r, i;
	u8 len;
	u8 buf[ST21NFCA_HCI_LLC_MAX_PAYLOAD];
	काष्ठा i2c_client *client = phy->i2c_dev;

	अगर (phy->current_पढ़ो_len < ARRAY_SIZE(len_seq)) अणु
		len = len_seq[phy->current_पढ़ो_len];

		/*
		 * Add retry mecanism
		 * Operation on I2C पूर्णांकerface may fail in हाल of operation on
		 * RF or SWP पूर्णांकerface
		 */
		r = 0;
		mutex_lock(&phy->phy_lock);
		क्रम (i = 0; i < ARRAY_SIZE(रुको_tab) && r <= 0; i++) अणु
			r = i2c_master_recv(client, buf, len);
			अगर (r < 0)
				msleep(रुको_tab[i]);
		पूर्ण
		mutex_unlock(&phy->phy_lock);

		अगर (r != len) अणु
			phy->current_पढ़ो_len = 0;
			वापस -EREMOTEIO;
		पूर्ण

		/*
		 * The first पढ़ो sequence करोes not start with SOF.
		 * Data is corrupeted so we drop it.
		 */
		अगर (!phy->current_पढ़ो_len && !IS_START_OF_FRAME(buf)) अणु
			skb_trim(skb, 0);
			phy->current_पढ़ो_len = 0;
			वापस -EIO;
		पूर्ण अन्यथा अगर (phy->current_पढ़ो_len && IS_START_OF_FRAME(buf)) अणु
			/*
			 * Previous frame transmission was पूर्णांकerrupted and
			 * the frame got repeated.
			 * Received frame start with ST21NFCA_SOF_खातापूर्ण + 00.
			 */
			skb_trim(skb, 0);
			phy->current_पढ़ो_len = 0;
		पूर्ण

		skb_put_data(skb, buf, len);

		अगर (skb->data[skb->len - 1] == ST21NFCA_SOF_खातापूर्ण) अणु
			phy->current_पढ़ो_len = 0;
			वापस st21nfca_hci_i2c_repack(skb);
		पूर्ण
		phy->current_पढ़ो_len++;
		वापस -EAGAIN;
	पूर्ण
	वापस -EIO;
पूर्ण

/*
 * Reads an shdlc frame from the chip. This is not as straightक्रमward as it
 * seems. The frame क्रमmat is data-crc, and corruption can occur anywhere
 * जबतक transiting on i2c bus, such that we could पढ़ो an invalid data.
 * The tricky हाल is when we पढ़ो a corrupted data or crc. We must detect
 * this here in order to determine that data can be transmitted to the hci
 * core. This is the reason why we check the crc here.
 * The CLF will repeat a frame until we send a RR on that frame.
 *
 * On ST21NFCA, IRQ goes in idle when पढ़ो starts. As no size inक्रमmation are
 * available in the incoming data, other IRQ might come. Every IRQ will trigger
 * a पढ़ो sequence with dअगरferent length and will fill the current frame.
 * The reception is complete once we reach a ST21NFCA_SOF_खातापूर्ण.
 */
अटल irqवापस_t st21nfca_hci_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *phy_id)
अणु
	काष्ठा st21nfca_i2c_phy *phy = phy_id;
	काष्ठा i2c_client *client;

	पूर्णांक r;

	अगर (!phy || irq != phy->i2c_dev->irq) अणु
		WARN_ON_ONCE(1);
		वापस IRQ_NONE;
	पूर्ण

	client = phy->i2c_dev;
	dev_dbg(&client->dev, "IRQ\n");

	अगर (phy->hard_fault != 0)
		वापस IRQ_HANDLED;

	r = st21nfca_hci_i2c_पढ़ो(phy, phy->pending_skb);
	अगर (r == -EREMOTEIO) अणु
		phy->hard_fault = r;

		nfc_hci_recv_frame(phy->hdev, शून्य);

		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अगर (r == -EAGAIN || r == -EIO) अणु
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अगर (r == -EBADMSG && phy->crc_trials < ARRAY_SIZE(रुको_tab)) अणु
		/*
		 * With ST21NFCA, only one पूर्णांकerface (I2C, RF or SWP)
		 * may be active at a समय.
		 * Having incorrect crc is usually due to i2c macrocell
		 * deactivation in the middle of a transmission.
		 * It may generate corrupted data on i2c.
		 * We give someसमय to get i2c back.
		 * The complete frame will be repeated.
		 */
		msleep(रुको_tab[phy->crc_trials]);
		phy->crc_trials++;
		phy->current_पढ़ो_len = 0;
		kमुक्त_skb(phy->pending_skb);
	पूर्ण अन्यथा अगर (r > 0) अणु
		/*
		 * We succeeded to पढ़ो data from the CLF and
		 * data is valid.
		 * Reset counter.
		 */
		nfc_hci_recv_frame(phy->hdev, phy->pending_skb);
		phy->crc_trials = 0;
	पूर्ण अन्यथा अणु
		kमुक्त_skb(phy->pending_skb);
	पूर्ण

	phy->pending_skb = alloc_skb(ST21NFCA_HCI_LLC_MAX_SIZE * 2, GFP_KERNEL);
	अगर (phy->pending_skb == शून्य) अणु
		phy->hard_fault = -ENOMEM;
		nfc_hci_recv_frame(phy->hdev, शून्य);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा nfc_phy_ops i2c_phy_ops = अणु
	.ग_लिखो = st21nfca_hci_i2c_ग_लिखो,
	.enable = st21nfca_hci_i2c_enable,
	.disable = st21nfca_hci_i2c_disable,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_params enable_gpios = अणु 1, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_st21nfca_gpios[] = अणु
	अणु "enable-gpios", &enable_gpios, 1 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक st21nfca_hci_i2c_probe(काष्ठा i2c_client *client,
				  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा st21nfca_i2c_phy *phy;
	पूर्णांक r;

	dev_dbg(&client->dev, "%s\n", __func__);
	dev_dbg(&client->dev, "IRQ: %d\n", client->irq);

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		nfc_err(&client->dev, "Need I2C_FUNC_I2C\n");
		वापस -ENODEV;
	पूर्ण

	phy = devm_kzalloc(&client->dev, माप(काष्ठा st21nfca_i2c_phy),
			   GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->i2c_dev = client;
	phy->pending_skb = alloc_skb(ST21NFCA_HCI_LLC_MAX_SIZE * 2, GFP_KERNEL);
	अगर (phy->pending_skb == शून्य)
		वापस -ENOMEM;

	phy->current_पढ़ो_len = 0;
	phy->crc_trials = 0;
	mutex_init(&phy->phy_lock);
	i2c_set_clientdata(client, phy);

	r = devm_acpi_dev_add_driver_gpios(dev, acpi_st21nfca_gpios);
	अगर (r)
		dev_dbg(dev, "Unable to add GPIO mapping table\n");

	/* Get EN GPIO from resource provider */
	phy->gpiod_ena = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(phy->gpiod_ena)) अणु
		nfc_err(dev, "Unable to get ENABLE GPIO\n");
		वापस PTR_ERR(phy->gpiod_ena);
	पूर्ण

	phy->se_status.is_ese_present =
			device_property_पढ़ो_bool(&client->dev, "ese-present");
	phy->se_status.is_uicc_present =
			device_property_पढ़ो_bool(&client->dev, "uicc-present");

	r = st21nfca_hci_platक्रमm_init(phy);
	अगर (r < 0) अणु
		nfc_err(&client->dev, "Unable to reboot st21nfca\n");
		वापस r;
	पूर्ण

	r = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
				st21nfca_hci_irq_thपढ़ो_fn,
				IRQF_ONESHOT,
				ST21NFCA_HCI_DRIVER_NAME, phy);
	अगर (r < 0) अणु
		nfc_err(&client->dev, "Unable to register IRQ handler\n");
		वापस r;
	पूर्ण

	वापस st21nfca_hci_probe(phy, &i2c_phy_ops, LLC_SHDLC_NAME,
					ST21NFCA_FRAME_HEADROOM,
					ST21NFCA_FRAME_TAILROOM,
					ST21NFCA_HCI_LLC_MAX_PAYLOAD,
					&phy->hdev,
					&phy->se_status);
पूर्ण

अटल पूर्णांक st21nfca_hci_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा st21nfca_i2c_phy *phy = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "%s\n", __func__);

	st21nfca_hci_हटाओ(phy->hdev);

	अगर (phy->घातered)
		st21nfca_hci_i2c_disable(phy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id st21nfca_hci_i2c_id_table[] = अणु
	अणुST21NFCA_HCI_DRIVER_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, st21nfca_hci_i2c_id_table);

अटल स्थिर काष्ठा acpi_device_id st21nfca_hci_i2c_acpi_match[] = अणु
	अणु"SMO2100", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, st21nfca_hci_i2c_acpi_match);

अटल स्थिर काष्ठा of_device_id of_st21nfca_i2c_match[] = अणु
	अणु .compatible = "st,st21nfca-i2c", पूर्ण,
	अणु .compatible = "st,st21nfca_i2c", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_st21nfca_i2c_match);

अटल काष्ठा i2c_driver st21nfca_hci_i2c_driver = अणु
	.driver = अणु
		.name = ST21NFCA_HCI_I2C_DRIVER_NAME,
		.of_match_table = of_match_ptr(of_st21nfca_i2c_match),
		.acpi_match_table = ACPI_PTR(st21nfca_hci_i2c_acpi_match),
	पूर्ण,
	.probe = st21nfca_hci_i2c_probe,
	.id_table = st21nfca_hci_i2c_id_table,
	.हटाओ = st21nfca_hci_i2c_हटाओ,
पूर्ण;
module_i2c_driver(st21nfca_hci_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
