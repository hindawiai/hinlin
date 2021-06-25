<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -------------------------------------------------------------------------
 * Copyright (C) 2014-2016, Intel Corporation
 *
 * -------------------------------------------------------------------------
 */

#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/nfc.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <net/nfc/nfc.h>
#समावेश <net/nfc/nci_core.h>

#समावेश "fdp.h"

#घोषणा FDP_I2C_DRIVER_NAME	"fdp_nci_i2c"

#घोषणा FDP_DP_CLOCK_TYPE_NAME	"clock-type"
#घोषणा FDP_DP_CLOCK_FREQ_NAME	"clock-freq"
#घोषणा FDP_DP_FW_VSC_CFG_NAME	"fw-vsc-cfg"

#घोषणा FDP_FRAME_HEADROOM	2
#घोषणा FDP_FRAME_TAILROOM	1

#घोषणा FDP_NCI_I2C_MIN_PAYLOAD	5
#घोषणा FDP_NCI_I2C_MAX_PAYLOAD	261

#घोषणा FDP_POWER_OFF		0
#घोषणा FDP_POWER_ON		1

#घोषणा fdp_nci_i2c_dump_skb(dev, prefix, skb)				\
	prपूर्णांक_hex_dump(KERN_DEBUG, prefix": ", DUMP_PREFIX_OFFSET,	\
		       16, 1, (skb)->data, (skb)->len, 0)

अटल व्योम fdp_nci_i2c_reset(काष्ठा fdp_i2c_phy *phy)
अणु
	/* Reset RST/WakeUP क्रम at least 100 micro-second */
	gpiod_set_value_cansleep(phy->घातer_gpio, FDP_POWER_OFF);
	usleep_range(1000, 4000);
	gpiod_set_value_cansleep(phy->घातer_gpio, FDP_POWER_ON);
	usleep_range(10000, 14000);
पूर्ण

अटल पूर्णांक fdp_nci_i2c_enable(व्योम *phy_id)
अणु
	काष्ठा fdp_i2c_phy *phy = phy_id;

	dev_dbg(&phy->i2c_dev->dev, "%s\n", __func__);
	fdp_nci_i2c_reset(phy);

	वापस 0;
पूर्ण

अटल व्योम fdp_nci_i2c_disable(व्योम *phy_id)
अणु
	काष्ठा fdp_i2c_phy *phy = phy_id;

	dev_dbg(&phy->i2c_dev->dev, "%s\n", __func__);
	fdp_nci_i2c_reset(phy);
पूर्ण

अटल व्योम fdp_nci_i2c_add_len_lrc(काष्ठा sk_buff *skb)
अणु
	u8 lrc = 0;
	u16 len, i;

	/* Add length header */
	len = skb->len;
	*(u8 *)skb_push(skb, 1) = len & 0xff;
	*(u8 *)skb_push(skb, 1) = len >> 8;

	/* Compute and add lrc */
	क्रम (i = 0; i < len + 2; i++)
		lrc ^= skb->data[i];

	skb_put_u8(skb, lrc);
पूर्ण

अटल व्योम fdp_nci_i2c_हटाओ_len_lrc(काष्ठा sk_buff *skb)
अणु
	skb_pull(skb, FDP_FRAME_HEADROOM);
	skb_trim(skb, skb->len - FDP_FRAME_TAILROOM);
पूर्ण

अटल पूर्णांक fdp_nci_i2c_ग_लिखो(व्योम *phy_id, काष्ठा sk_buff *skb)
अणु
	काष्ठा fdp_i2c_phy *phy = phy_id;
	काष्ठा i2c_client *client = phy->i2c_dev;
	पूर्णांक r;

	अगर (phy->hard_fault != 0)
		वापस phy->hard_fault;

	fdp_nci_i2c_add_len_lrc(skb);
	fdp_nci_i2c_dump_skb(&client->dev, "fdp_wr", skb);

	r = i2c_master_send(client, skb->data, skb->len);
	अगर (r == -EREMOTEIO) अणु  /* Retry, chip was in standby */
		usleep_range(1000, 4000);
		r = i2c_master_send(client, skb->data, skb->len);
	पूर्ण

	अगर (r < 0 || r != skb->len)
		dev_dbg(&client->dev, "%s: error err=%d len=%d\n",
			__func__, r, skb->len);

	अगर (r >= 0) अणु
		अगर (r != skb->len) अणु
			phy->hard_fault = r;
			r = -EREMOTEIO;
		पूर्ण अन्यथा अणु
			r = 0;
		पूर्ण
	पूर्ण

	fdp_nci_i2c_हटाओ_len_lrc(skb);

	वापस r;
पूर्ण

अटल काष्ठा nfc_phy_ops i2c_phy_ops = अणु
	.ग_लिखो = fdp_nci_i2c_ग_लिखो,
	.enable = fdp_nci_i2c_enable,
	.disable = fdp_nci_i2c_disable,
पूर्ण;

अटल पूर्णांक fdp_nci_i2c_पढ़ो(काष्ठा fdp_i2c_phy *phy, काष्ठा sk_buff **skb)
अणु
	पूर्णांक r, len;
	u8 पंचांगp[FDP_NCI_I2C_MAX_PAYLOAD], lrc, k;
	u16 i;
	काष्ठा i2c_client *client = phy->i2c_dev;

	*skb = शून्य;

	/* Read the length packet and the data packet */
	क्रम (k = 0; k < 2; k++) अणु

		len = phy->next_पढ़ो_size;

		r = i2c_master_recv(client, पंचांगp, len);
		अगर (r != len) अणु
			dev_dbg(&client->dev, "%s: i2c recv err: %d\n",
				__func__, r);
			जाओ flush;
		पूर्ण

		/* Check packet पूर्णांकegruty */
		क्रम (lrc = i = 0; i < r; i++)
			lrc ^= पंचांगp[i];

		/*
		 * LRC check failed. This may due to transmission error or
		 * desynchronization between driver and FDP. Drop the packet
		 * and क्रमce resynchronization
		 */
		अगर (lrc) अणु
			dev_dbg(&client->dev, "%s: corrupted packet\n",
				__func__);
			phy->next_पढ़ो_size = 5;
			जाओ flush;
		पूर्ण

		/* Packet that contains a length */
		अगर (पंचांगp[0] == 0 && पंचांगp[1] == 0) अणु
			phy->next_पढ़ो_size = (पंचांगp[2] << 8) + पंचांगp[3] + 3;
		पूर्ण अन्यथा अणु
			phy->next_पढ़ो_size = FDP_NCI_I2C_MIN_PAYLOAD;

			*skb = alloc_skb(len, GFP_KERNEL);
			अगर (*skb == शून्य) अणु
				r = -ENOMEM;
				जाओ flush;
			पूर्ण

			skb_put_data(*skb, पंचांगp, len);
			fdp_nci_i2c_dump_skb(&client->dev, "fdp_rd", *skb);

			fdp_nci_i2c_हटाओ_len_lrc(*skb);
		पूर्ण
	पूर्ण

	वापस 0;

flush:
	/* Flush the reमुख्यing data */
	अगर (i2c_master_recv(client, पंचांगp, माप(पंचांगp)) < 0)
		r = -EREMOTEIO;

	वापस r;
पूर्ण

अटल irqवापस_t fdp_nci_i2c_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *phy_id)
अणु
	काष्ठा fdp_i2c_phy *phy = phy_id;
	काष्ठा i2c_client *client;
	काष्ठा sk_buff *skb;
	पूर्णांक r;

	अगर (!phy || irq != phy->i2c_dev->irq) अणु
		WARN_ON_ONCE(1);
		वापस IRQ_NONE;
	पूर्ण

	client = phy->i2c_dev;
	dev_dbg(&client->dev, "%s\n", __func__);

	r = fdp_nci_i2c_पढ़ो(phy, &skb);

	अगर (r == -EREMOTEIO)
		वापस IRQ_HANDLED;
	अन्यथा अगर (r == -ENOMEM || r == -EBADMSG)
		वापस IRQ_HANDLED;

	अगर (skb != शून्य)
		fdp_nci_recv_frame(phy->ndev, skb);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम fdp_nci_i2c_पढ़ो_device_properties(काष्ठा device *dev,
					       u8 *घड़ी_प्रकारype, u32 *घड़ी_freq,
					       u8 **fw_vsc_cfg)
अणु
	पूर्णांक r;
	u8 len;

	r = device_property_पढ़ो_u8(dev, FDP_DP_CLOCK_TYPE_NAME, घड़ी_प्रकारype);
	अगर (r) अणु
		dev_dbg(dev, "Using default clock type");
		*घड़ी_प्रकारype = 0;
	पूर्ण

	r = device_property_पढ़ो_u32(dev, FDP_DP_CLOCK_FREQ_NAME, घड़ी_freq);
	अगर (r) अणु
		dev_dbg(dev, "Using default clock frequency\n");
		*घड़ी_freq = 26000;
	पूर्ण

	अगर (device_property_present(dev, FDP_DP_FW_VSC_CFG_NAME)) अणु
		r = device_property_पढ़ो_u8(dev, FDP_DP_FW_VSC_CFG_NAME,
					    &len);

		अगर (r || len <= 0)
			जाओ vsc_पढ़ो_err;

		/* Add 1 to the length to inclue the length byte itself */
		len++;

		*fw_vsc_cfg = devm_kदो_स्मृति_array(dev,
					   len, माप(**fw_vsc_cfg),
					   GFP_KERNEL);

		r = device_property_पढ़ो_u8_array(dev, FDP_DP_FW_VSC_CFG_NAME,
						  *fw_vsc_cfg, len);

		अगर (r) अणु
			devm_kमुक्त(dev, *fw_vsc_cfg);
			जाओ vsc_पढ़ो_err;
		पूर्ण
	पूर्ण अन्यथा अणु
vsc_पढ़ो_err:
		dev_dbg(dev, "FW vendor specific commands not present\n");
		*fw_vsc_cfg = शून्य;
	पूर्ण

	dev_dbg(dev, "Clock type: %d, clock frequency: %d, VSC: %s",
		*घड़ी_प्रकारype, *घड़ी_freq, *fw_vsc_cfg != शून्य ? "yes" : "no");
पूर्ण

अटल स्थिर काष्ठा acpi_gpio_params घातer_gpios = अणु 0, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_fdp_gpios[] = अणु
	अणु "power-gpios", &घातer_gpios, 1 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक fdp_nci_i2c_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा fdp_i2c_phy *phy;
	काष्ठा device *dev = &client->dev;
	u8 *fw_vsc_cfg;
	u8 घड़ी_प्रकारype;
	u32 घड़ी_freq;
	पूर्णांक r = 0;

	dev_dbg(dev, "%s\n", __func__);

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		nfc_err(dev, "No I2C_FUNC_I2C support\n");
		वापस -ENODEV;
	पूर्ण

	/* Checking अगर we have an irq */
	अगर (client->irq <= 0) अणु
		nfc_err(dev, "IRQ not present\n");
		वापस -ENODEV;
	पूर्ण

	phy = devm_kzalloc(dev, माप(काष्ठा fdp_i2c_phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->i2c_dev = client;
	phy->next_पढ़ो_size = FDP_NCI_I2C_MIN_PAYLOAD;
	i2c_set_clientdata(client, phy);

	r = devm_request_thपढ़ोed_irq(dev, client->irq,
				      शून्य, fdp_nci_i2c_irq_thपढ़ो_fn,
				      IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				      FDP_I2C_DRIVER_NAME, phy);

	अगर (r < 0) अणु
		nfc_err(&client->dev, "Unable to register IRQ handler\n");
		वापस r;
	पूर्ण

	r = devm_acpi_dev_add_driver_gpios(dev, acpi_fdp_gpios);
	अगर (r)
		dev_dbg(dev, "Unable to add GPIO mapping table\n");

	/* Requesting the घातer gpio */
	phy->घातer_gpio = devm_gpiod_get(dev, "power", GPIOD_OUT_LOW);
	अगर (IS_ERR(phy->घातer_gpio)) अणु
		nfc_err(dev, "Power GPIO request failed\n");
		वापस PTR_ERR(phy->घातer_gpio);
	पूर्ण

	/* पढ़ो device properties to get the घड़ी and production settings */
	fdp_nci_i2c_पढ़ो_device_properties(dev, &घड़ी_प्रकारype, &घड़ी_freq,
					   &fw_vsc_cfg);

	/* Call the NFC specअगरic probe function */
	r = fdp_nci_probe(phy, &i2c_phy_ops, &phy->ndev,
			  FDP_FRAME_HEADROOM, FDP_FRAME_TAILROOM,
			  घड़ी_प्रकारype, घड़ी_freq, fw_vsc_cfg);
	अगर (r < 0) अणु
		nfc_err(dev, "NCI probing error\n");
		वापस r;
	पूर्ण

	dev_dbg(dev, "I2C driver loaded\n");
	वापस 0;
पूर्ण

अटल पूर्णांक fdp_nci_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा fdp_i2c_phy *phy = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "%s\n", __func__);

	fdp_nci_हटाओ(phy->ndev);
	fdp_nci_i2c_disable(phy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id fdp_nci_i2c_acpi_match[] = अणु
	अणु"INT339A", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, fdp_nci_i2c_acpi_match);

अटल काष्ठा i2c_driver fdp_nci_i2c_driver = अणु
	.driver = अणु
		   .name = FDP_I2C_DRIVER_NAME,
		   .acpi_match_table = ACPI_PTR(fdp_nci_i2c_acpi_match),
		  पूर्ण,
	.probe_new = fdp_nci_i2c_probe,
	.हटाओ = fdp_nci_i2c_हटाओ,
पूर्ण;
module_i2c_driver(fdp_nci_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("I2C driver for Intel Fields Peak NFC controller");
MODULE_AUTHOR("Robert Dolca <robert.dolca@intel.com>");
