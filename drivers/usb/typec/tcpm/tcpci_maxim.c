<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020, Google LLC
 *
 * MAXIM TCPCI based TCPC driver
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/usb/pd.h>
#समावेश <linux/usb/tcpm.h>
#समावेश <linux/usb/typec.h>

#समावेश "tcpci.h"

#घोषणा PD_ACTIVITY_TIMEOUT_MS				10000

#घोषणा TCPC_VENDOR_ALERT				0x80
#घोषणा TCPC_VENDOR_USBSW_CTRL				0x93
#घोषणा TCPC_VENDOR_USBSW_CTRL_ENABLE_USB_DATA		0x9
#घोषणा TCPC_VENDOR_USBSW_CTRL_DISABLE_USB_DATA		0

#घोषणा TCPC_RECEIVE_BUFFER_COUNT_OFFSET		0
#घोषणा TCPC_RECEIVE_BUFFER_FRAME_TYPE_OFFSET		1
#घोषणा TCPC_RECEIVE_BUFFER_RX_BYTE_BUF_OFFSET		2

/*
 * LongMessage not supported, hence 32 bytes क्रम buf to be पढ़ो from RECEIVE_BUFFER.
 * DEVICE_CAPABILITIES_2.LongMessage = 0, the value in READABLE_BYTE_COUNT reg shall be
 * less than or equal to 31. Since, RECEIVE_BUFFER len = 31 + 1(READABLE_BYTE_COUNT).
 */
#घोषणा TCPC_RECEIVE_BUFFER_LEN				32

#घोषणा MAX_BUCK_BOOST_SID				0x69
#घोषणा MAX_BUCK_BOOST_OP				0xb9
#घोषणा MAX_BUCK_BOOST_OFF				0
#घोषणा MAX_BUCK_BOOST_SOURCE				0xa
#घोषणा MAX_BUCK_BOOST_SINK				0x5

काष्ठा max_tcpci_chip अणु
	काष्ठा tcpci_data data;
	काष्ठा tcpci *tcpci;
	काष्ठा device *dev;
	काष्ठा i2c_client *client;
	काष्ठा tcpm_port *port;
पूर्ण;

अटल स्थिर काष्ठा regmap_range max_tcpci_tcpci_range[] = अणु
	regmap_reg_range(0x00, 0x95)
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table max_tcpci_tcpci_ग_लिखो_table = अणु
	.yes_ranges = max_tcpci_tcpci_range,
	.n_yes_ranges = ARRAY_SIZE(max_tcpci_tcpci_range),
पूर्ण;

अटल स्थिर काष्ठा regmap_config max_tcpci_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x95,
	.wr_table = &max_tcpci_tcpci_ग_लिखो_table,
पूर्ण;

अटल काष्ठा max_tcpci_chip *tdata_to_max_tcpci(काष्ठा tcpci_data *tdata)
अणु
	वापस container_of(tdata, काष्ठा max_tcpci_chip, data);
पूर्ण

अटल पूर्णांक max_tcpci_पढ़ो16(काष्ठा max_tcpci_chip *chip, अचिन्हित पूर्णांक reg, u16 *val)
अणु
	वापस regmap_raw_पढ़ो(chip->data.regmap, reg, val, माप(u16));
पूर्ण

अटल पूर्णांक max_tcpci_ग_लिखो16(काष्ठा max_tcpci_chip *chip, अचिन्हित पूर्णांक reg, u16 val)
अणु
	वापस regmap_raw_ग_लिखो(chip->data.regmap, reg, &val, माप(u16));
पूर्ण

अटल पूर्णांक max_tcpci_पढ़ो8(काष्ठा max_tcpci_chip *chip, अचिन्हित पूर्णांक reg, u8 *val)
अणु
	वापस regmap_raw_पढ़ो(chip->data.regmap, reg, val, माप(u8));
पूर्ण

अटल पूर्णांक max_tcpci_ग_लिखो8(काष्ठा max_tcpci_chip *chip, अचिन्हित पूर्णांक reg, u8 val)
अणु
	वापस regmap_raw_ग_लिखो(chip->data.regmap, reg, &val, माप(u8));
पूर्ण

अटल व्योम max_tcpci_init_regs(काष्ठा max_tcpci_chip *chip)
अणु
	u16 alert_mask = 0;
	पूर्णांक ret;

	ret = max_tcpci_ग_लिखो16(chip, TCPC_ALERT, 0xffff);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Error writing to TCPC_ALERT ret:%d\n", ret);
		वापस;
	पूर्ण

	ret = max_tcpci_ग_लिखो16(chip, TCPC_VENDOR_ALERT, 0xffff);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Error writing to TCPC_VENDOR_ALERT ret:%d\n", ret);
		वापस;
	पूर्ण

	ret = max_tcpci_ग_लिखो8(chip, TCPC_ALERT_EXTENDED, 0xff);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Unable to clear TCPC_ALERT_EXTENDED ret:%d\n", ret);
		वापस;
	पूर्ण

	/* Enable VSAFE0V detection */
	ret = max_tcpci_ग_लिखो8(chip, TCPC_EXTENDED_STATUS_MASK, TCPC_EXTENDED_STATUS_VSAFE0V);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Unable to unmask TCPC_EXTENDED_STATUS_VSAFE0V ret:%d\n", ret);
		वापस;
	पूर्ण

	alert_mask = TCPC_ALERT_TX_SUCCESS | TCPC_ALERT_TX_DISCARDED | TCPC_ALERT_TX_FAILED |
		TCPC_ALERT_RX_HARD_RST | TCPC_ALERT_RX_STATUS | TCPC_ALERT_CC_STATUS |
		TCPC_ALERT_VBUS_DISCNCT | TCPC_ALERT_RX_BUF_OVF | TCPC_ALERT_POWER_STATUS |
		/* Enable Extended alert क्रम detecting Fast Role Swap Signal */
		TCPC_ALERT_EXTND | TCPC_ALERT_EXTENDED_STATUS;

	ret = max_tcpci_ग_लिखो16(chip, TCPC_ALERT_MASK, alert_mask);
	अगर (ret < 0) अणु
		dev_err(chip->dev,
			"Error enabling TCPC_ALERT: TCPC_ALERT_MASK write failed ret:%d\n", ret);
		वापस;
	पूर्ण

	/* Enable vbus voltage monitoring and voltage alerts */
	ret = max_tcpci_ग_लिखो8(chip, TCPC_POWER_CTRL, 0);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Error writing to TCPC_POWER_CTRL ret:%d\n", ret);
		वापस;
	पूर्ण

	ret = max_tcpci_ग_लिखो8(chip, TCPC_ALERT_EXTENDED_MASK, TCPC_SINK_FAST_ROLE_SWAP);
	अगर (ret < 0)
		वापस;
पूर्ण

अटल व्योम process_rx(काष्ठा max_tcpci_chip *chip, u16 status)
अणु
	काष्ठा pd_message msg;
	u8 count, frame_type, rx_buf[TCPC_RECEIVE_BUFFER_LEN];
	पूर्णांक ret, payload_index;
	u8 *rx_buf_ptr;

	/*
	 * READABLE_BYTE_COUNT: Indicates the number of bytes in the RX_BUF_BYTE_x रेजिस्टरs
	 * plus one (क्रम the RX_BUF_FRAME_TYPE) Table 4-36.
	 * Read the count and frame type.
	 */
	ret = regmap_raw_पढ़ो(chip->data.regmap, TCPC_RX_BYTE_CNT, rx_buf, 2);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "TCPC_RX_BYTE_CNT read failed ret:%d\n", ret);
		वापस;
	पूर्ण

	count = rx_buf[TCPC_RECEIVE_BUFFER_COUNT_OFFSET];
	frame_type = rx_buf[TCPC_RECEIVE_BUFFER_FRAME_TYPE_OFFSET];

	अगर (count == 0 || frame_type != TCPC_RX_BUF_FRAME_TYPE_SOP) अणु
		max_tcpci_ग_लिखो16(chip, TCPC_ALERT, TCPC_ALERT_RX_STATUS);
		dev_err(chip->dev, "%s\n", count ==  0 ? "error: count is 0" :
			"error frame_type is not SOP");
		वापस;
	पूर्ण

	अगर (count > माप(काष्ठा pd_message) || count + 1 > TCPC_RECEIVE_BUFFER_LEN) अणु
		dev_err(chip->dev, "Invalid TCPC_RX_BYTE_CNT %d\n", count);
		वापस;
	पूर्ण

	/*
	 * Read count + 1 as RX_BUF_BYTE_x is hidden and can only be पढ़ो through
	 * TCPC_RX_BYTE_CNT
	 */
	count += 1;
	ret = regmap_raw_पढ़ो(chip->data.regmap, TCPC_RX_BYTE_CNT, rx_buf, count);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Error: TCPC_RX_BYTE_CNT read failed: %d\n", ret);
		वापस;
	पूर्ण

	rx_buf_ptr = rx_buf + TCPC_RECEIVE_BUFFER_RX_BYTE_BUF_OFFSET;
	msg.header = cpu_to_le16(*(u16 *)rx_buf_ptr);
	rx_buf_ptr = rx_buf_ptr + माप(msg.header);
	क्रम (payload_index = 0; payload_index < pd_header_cnt_le(msg.header); payload_index++,
	     rx_buf_ptr += माप(msg.payload[0]))
		msg.payload[payload_index] = cpu_to_le32(*(u32 *)rx_buf_ptr);

	/*
	 * Read complete, clear RX status alert bit.
	 * Clear overflow as well अगर set.
	 */
	ret = max_tcpci_ग_लिखो16(chip, TCPC_ALERT, status & TCPC_ALERT_RX_BUF_OVF ?
				TCPC_ALERT_RX_STATUS | TCPC_ALERT_RX_BUF_OVF :
				TCPC_ALERT_RX_STATUS);
	अगर (ret < 0)
		वापस;

	tcpm_pd_receive(chip->port, &msg);
पूर्ण

अटल पूर्णांक max_tcpci_set_vbus(काष्ठा tcpci *tcpci, काष्ठा tcpci_data *tdata, bool source, bool sink)
अणु
	काष्ठा max_tcpci_chip *chip = tdata_to_max_tcpci(tdata);
	u8 buffer_source[2] = अणुMAX_BUCK_BOOST_OP, MAX_BUCK_BOOST_SOURCEपूर्ण;
	u8 buffer_sink[2] = अणुMAX_BUCK_BOOST_OP, MAX_BUCK_BOOST_SINKपूर्ण;
	u8 buffer_none[2] = अणुMAX_BUCK_BOOST_OP, MAX_BUCK_BOOST_OFFपूर्ण;
	काष्ठा i2c_client *i2c = chip->client;
	पूर्णांक ret;

	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = MAX_BUCK_BOOST_SID,
			.flags = i2c->flags & I2C_M_TEN,
			.len = 2,
			.buf = source ? buffer_source : sink ? buffer_sink : buffer_none,
		पूर्ण,
	पूर्ण;

	अगर (source && sink) अणु
		dev_err(chip->dev, "Both source and sink set\n");
		वापस -EINVAL;
	पूर्ण

	ret = i2c_transfer(i2c->adapter, msgs, 1);

	वापस  ret < 0 ? ret : 1;
पूर्ण

अटल व्योम process_घातer_status(काष्ठा max_tcpci_chip *chip)
अणु
	u8 pwr_status;
	पूर्णांक ret;

	ret = max_tcpci_पढ़ो8(chip, TCPC_POWER_STATUS, &pwr_status);
	अगर (ret < 0)
		वापस;

	अगर (pwr_status == 0xff)
		max_tcpci_init_regs(chip);
	अन्यथा अगर (pwr_status & TCPC_POWER_STATUS_SOURCING_VBUS)
		tcpm_sourcing_vbus(chip->port);
	अन्यथा
		tcpm_vbus_change(chip->port);
पूर्ण

अटल व्योम max_tcpci_frs_sourcing_vbus(काष्ठा tcpci *tcpci, काष्ठा tcpci_data *tdata)
अणु
	/*
	 * For Fast Role Swap हाल, Boost turns on स्वतःnomously without
	 * AP पूर्णांकervention, but, needs AP to enable source mode explicitly
	 * क्रम AP to regain control.
	 */
	max_tcpci_set_vbus(tcpci, tdata, true, false);
पूर्ण

अटल व्योम process_tx(काष्ठा max_tcpci_chip *chip, u16 status)
अणु
	अगर (status & TCPC_ALERT_TX_SUCCESS)
		tcpm_pd_transmit_complete(chip->port, TCPC_TX_SUCCESS);
	अन्यथा अगर (status & TCPC_ALERT_TX_DISCARDED)
		tcpm_pd_transmit_complete(chip->port, TCPC_TX_DISCARDED);
	अन्यथा अगर (status & TCPC_ALERT_TX_FAILED)
		tcpm_pd_transmit_complete(chip->port, TCPC_TX_FAILED);

	/* Reinit regs as Hard reset sets them to शेष value */
	अगर ((status & TCPC_ALERT_TX_SUCCESS) && (status & TCPC_ALERT_TX_FAILED))
		max_tcpci_init_regs(chip);
पूर्ण

/* Enable USB चयनes when partner is USB communications capable */
अटल व्योम max_tcpci_set_partner_usb_comm_capable(काष्ठा tcpci *tcpci, काष्ठा tcpci_data *data,
						   bool capable)
अणु
	काष्ठा max_tcpci_chip *chip = tdata_to_max_tcpci(data);
	पूर्णांक ret;

	ret = max_tcpci_ग_लिखो8(chip, TCPC_VENDOR_USBSW_CTRL, capable ?
			       TCPC_VENDOR_USBSW_CTRL_ENABLE_USB_DATA :
			       TCPC_VENDOR_USBSW_CTRL_DISABLE_USB_DATA);

	अगर (ret < 0)
		dev_err(chip->dev, "Failed to enable USB switches");
पूर्ण

अटल irqवापस_t _max_tcpci_irq(काष्ठा max_tcpci_chip *chip, u16 status)
अणु
	u16 mask;
	पूर्णांक ret;
	u8 reg_status;

	/*
	 * Clear alert status क्रम everything except RX_STATUS, which shouldn't
	 * be cleared until we have successfully retrieved message.
	 */
	अगर (status & ~TCPC_ALERT_RX_STATUS) अणु
		mask = status & TCPC_ALERT_RX_BUF_OVF ?
			status & ~(TCPC_ALERT_RX_STATUS | TCPC_ALERT_RX_BUF_OVF) :
			status & ~TCPC_ALERT_RX_STATUS;
		ret = max_tcpci_ग_लिखो16(chip, TCPC_ALERT, mask);
		अगर (ret < 0) अणु
			dev_err(chip->dev, "ALERT clear failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (status & TCPC_ALERT_RX_BUF_OVF && !(status & TCPC_ALERT_RX_STATUS)) अणु
		ret = max_tcpci_ग_लिखो16(chip, TCPC_ALERT, (TCPC_ALERT_RX_STATUS |
							  TCPC_ALERT_RX_BUF_OVF));
		अगर (ret < 0) अणु
			dev_err(chip->dev, "ALERT clear failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (status & TCPC_ALERT_EXTND) अणु
		ret = max_tcpci_पढ़ो8(chip, TCPC_ALERT_EXTENDED, &reg_status);
		अगर (ret < 0)
			वापस ret;

		ret = max_tcpci_ग_लिखो8(chip, TCPC_ALERT_EXTENDED, reg_status);
		अगर (ret < 0)
			वापस ret;

		अगर (reg_status & TCPC_SINK_FAST_ROLE_SWAP) अणु
			dev_info(chip->dev, "FRS Signal\n");
			tcpm_sink_frs(chip->port);
		पूर्ण
	पूर्ण

	अगर (status & TCPC_ALERT_EXTENDED_STATUS) अणु
		ret = max_tcpci_पढ़ो8(chip, TCPC_EXTENDED_STATUS, (u8 *)&reg_status);
		अगर (ret >= 0 && (reg_status & TCPC_EXTENDED_STATUS_VSAFE0V))
			tcpm_vbus_change(chip->port);
	पूर्ण

	अगर (status & TCPC_ALERT_RX_STATUS)
		process_rx(chip, status);

	अगर (status & TCPC_ALERT_VBUS_DISCNCT)
		tcpm_vbus_change(chip->port);

	अगर (status & TCPC_ALERT_CC_STATUS)
		tcpm_cc_change(chip->port);

	अगर (status & TCPC_ALERT_POWER_STATUS)
		process_घातer_status(chip);

	अगर (status & TCPC_ALERT_RX_HARD_RST) अणु
		tcpm_pd_hard_reset(chip->port);
		max_tcpci_init_regs(chip);
	पूर्ण

	अगर (status & TCPC_ALERT_TX_SUCCESS || status & TCPC_ALERT_TX_DISCARDED || status &
	    TCPC_ALERT_TX_FAILED)
		process_tx(chip, status);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t max_tcpci_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा max_tcpci_chip *chip = dev_id;
	u16 status;
	irqवापस_t irq_वापस = IRQ_HANDLED;
	पूर्णांक ret;

	अगर (!chip->port)
		वापस IRQ_HANDLED;

	ret = max_tcpci_पढ़ो16(chip, TCPC_ALERT, &status);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "ALERT read failed\n");
		वापस ret;
	पूर्ण
	जबतक (status) अणु
		irq_वापस = _max_tcpci_irq(chip, status);
		/* Do not वापस अगर the ALERT is alपढ़ोy set. */
		ret = max_tcpci_पढ़ो16(chip, TCPC_ALERT, &status);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस irq_वापस;
पूर्ण

अटल irqवापस_t max_tcpci_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा max_tcpci_chip *chip = dev_id;

	pm_wakeup_event(chip->dev, PD_ACTIVITY_TIMEOUT_MS);

	अगर (!chip->port)
		वापस IRQ_HANDLED;

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल पूर्णांक max_tcpci_init_alert(काष्ठा max_tcpci_chip *chip, काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	ret = devm_request_thपढ़ोed_irq(chip->dev, client->irq, max_tcpci_isr, max_tcpci_irq,
					(IRQF_TRIGGER_LOW | IRQF_ONESHOT), dev_name(chip->dev),
					chip);

	अगर (ret < 0)
		वापस ret;

	enable_irq_wake(client->irq);
	वापस 0;
पूर्ण

अटल पूर्णांक max_tcpci_start_toggling(काष्ठा tcpci *tcpci, काष्ठा tcpci_data *tdata,
				    क्रमागत typec_cc_status cc)
अणु
	काष्ठा max_tcpci_chip *chip = tdata_to_max_tcpci(tdata);

	max_tcpci_init_regs(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक tcpci_init(काष्ठा tcpci *tcpci, काष्ठा tcpci_data *data)
अणु
	/*
	 * Generic TCPCI overग_लिखोs the regs once this driver initializes
	 * them. Prevent this by वापसing -1.
	 */
	वापस -1;
पूर्ण

अटल पूर्णांक max_tcpci_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	पूर्णांक ret;
	काष्ठा max_tcpci_chip *chip;
	u8 घातer_status;

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->client = client;
	chip->data.regmap = devm_regmap_init_i2c(client, &max_tcpci_regmap_config);
	अगर (IS_ERR(chip->data.regmap)) अणु
		dev_err(&client->dev, "Regmap init failed\n");
		वापस PTR_ERR(chip->data.regmap);
	पूर्ण

	chip->dev = &client->dev;
	i2c_set_clientdata(client, chip);

	ret = max_tcpci_पढ़ो8(chip, TCPC_POWER_STATUS, &घातer_status);
	अगर (ret < 0)
		वापस ret;

	/* Chip level tcpci callbacks */
	chip->data.set_vbus = max_tcpci_set_vbus;
	chip->data.start_drp_toggling = max_tcpci_start_toggling;
	chip->data.TX_BUF_BYTE_x_hidden = true;
	chip->data.init = tcpci_init;
	chip->data.frs_sourcing_vbus = max_tcpci_frs_sourcing_vbus;
	chip->data.स्वतः_disअक्षरge_disconnect = true;
	chip->data.vbus_vsafe0v = true;
	chip->data.set_partner_usb_comm_capable = max_tcpci_set_partner_usb_comm_capable;

	max_tcpci_init_regs(chip);
	chip->tcpci = tcpci_रेजिस्टर_port(chip->dev, &chip->data);
	अगर (IS_ERR(chip->tcpci)) अणु
		dev_err(&client->dev, "TCPCI port registration failed\n");
		वापस PTR_ERR(chip->tcpci);
	पूर्ण
	chip->port = tcpci_get_tcpm_port(chip->tcpci);
	ret = max_tcpci_init_alert(chip, client);
	अगर (ret < 0)
		जाओ unreg_port;

	device_init_wakeup(chip->dev, true);
	वापस 0;

unreg_port:
	tcpci_unरेजिस्टर_port(chip->tcpci);

	वापस ret;
पूर्ण

अटल पूर्णांक max_tcpci_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा max_tcpci_chip *chip = i2c_get_clientdata(client);

	अगर (!IS_ERR_OR_शून्य(chip->tcpci))
		tcpci_unरेजिस्टर_port(chip->tcpci);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max_tcpci_id[] = अणु
	अणु "maxtcpc", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max_tcpci_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max_tcpci_of_match[] = अणु
	अणु .compatible = "maxim,max33359", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max_tcpci_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver max_tcpci_i2c_driver = अणु
	.driver = अणु
		.name = "maxtcpc",
		.of_match_table = of_match_ptr(max_tcpci_of_match),
	पूर्ण,
	.probe = max_tcpci_probe,
	.हटाओ = max_tcpci_हटाओ,
	.id_table = max_tcpci_id,
पूर्ण;
module_i2c_driver(max_tcpci_i2c_driver);

MODULE_AUTHOR("Badhri Jagan Sridharan <badhri@google.com>");
MODULE_DESCRIPTION("Maxim TCPCI based USB Type-C Port Controller Interface Driver");
MODULE_LICENSE("GPL v2");
