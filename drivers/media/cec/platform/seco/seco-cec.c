<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * CEC driver क्रम SECO X86 Boards
 *
 * Author:  Ettore Chimenti <ek5.chimenti@gmail.com>
 * Copyright (C) 2018, SECO SpA.
 * Copyright (C) 2018, Aidilab Srl.
 */

#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>

/* CEC Framework */
#समावेश <media/cec-notअगरier.h>

#समावेश "seco-cec.h"

काष्ठा secocec_data अणु
	काष्ठा device *dev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा cec_adapter *cec_adap;
	काष्ठा cec_notअगरier *notअगरier;
	काष्ठा rc_dev *ir;
	अक्षर ir_input_phys[32];
	पूर्णांक irq;
पूर्ण;

#घोषणा smb_wr16(cmd, data) smb_word_op(CMD_WORD_DATA, SECOCEC_MICRO_ADDRESS, \
					     cmd, data, SMBUS_WRITE, शून्य)
#घोषणा smb_rd16(cmd, res) smb_word_op(CMD_WORD_DATA, SECOCEC_MICRO_ADDRESS, \
				       cmd, 0, SMBUS_READ, res)

अटल पूर्णांक smb_word_op(लघु data_क्रमmat, u16 slave_addr, u8 cmd, u16 data,
		       u8 operation, u16 *result)
अणु
	अचिन्हित पूर्णांक count;
	लघु _data_क्रमmat;
	पूर्णांक status = 0;

	चयन (data_क्रमmat) अणु
	हाल CMD_BYTE_DATA:
		_data_क्रमmat = BRA_SMB_CMD_BYTE_DATA;
		अवरोध;
	हाल CMD_WORD_DATA:
		_data_क्रमmat = BRA_SMB_CMD_WORD_DATA;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Active रुको until पढ़ोy */
	क्रम (count = 0; count <= SMBTIMEOUT; ++count) अणु
		अगर (!(inb(HSTS) & BRA_INUSE_STS))
			अवरोध;
		udelay(SMB_POLL_UDELAY);
	पूर्ण

	अगर (count > SMBTIMEOUT)
		/* Reset the lock instead of failing */
		outb(0xff, HSTS);

	outb(0x00, HCNT);
	outb((u8)(slave_addr & 0xfe) | operation, XMIT_SLVA);
	outb(cmd, HCMD);
	inb(HCNT);

	अगर (operation == SMBUS_WRITE) अणु
		outb((u8)data, HDAT0);
		outb((u8)(data >> 8), HDAT1);
	पूर्ण

	outb(BRA_START + _data_क्रमmat, HCNT);

	क्रम (count = 0; count <= SMBTIMEOUT; count++) अणु
		अगर (!(inb(HSTS) & BRA_HOST_BUSY))
			अवरोध;
		udelay(SMB_POLL_UDELAY);
	पूर्ण

	अगर (count > SMBTIMEOUT) अणु
		status = -EBUSY;
		जाओ err;
	पूर्ण

	अगर (inb(HSTS) & BRA_HSTS_ERR_MASK) अणु
		status = -EIO;
		जाओ err;
	पूर्ण

	अगर (operation == SMBUS_READ)
		*result = ((inb(HDAT0) & 0xff) + ((inb(HDAT1) & 0xff) << 8));

err:
	outb(0xff, HSTS);
	वापस status;
पूर्ण

अटल पूर्णांक secocec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा secocec_data *cec = cec_get_drvdata(adap);
	काष्ठा device *dev = cec->dev;
	u16 val = 0;
	पूर्णांक status;

	अगर (enable) अणु
		/* Clear the status रेजिस्टर */
		status = smb_rd16(SECOCEC_STATUS_REG_1, &val);
		अगर (status)
			जाओ err;

		status = smb_wr16(SECOCEC_STATUS_REG_1, val);
		अगर (status)
			जाओ err;

		/* Enable the पूर्णांकerrupts */
		status = smb_rd16(SECOCEC_ENABLE_REG_1, &val);
		अगर (status)
			जाओ err;

		status = smb_wr16(SECOCEC_ENABLE_REG_1,
				  val | SECOCEC_ENABLE_REG_1_CEC);
		अगर (status)
			जाओ err;

		dev_dbg(dev, "Device enabled");
	पूर्ण अन्यथा अणु
		/* Clear the status रेजिस्टर */
		status = smb_rd16(SECOCEC_STATUS_REG_1, &val);
		status = smb_wr16(SECOCEC_STATUS_REG_1, val);

		/* Disable the पूर्णांकerrupts */
		status = smb_rd16(SECOCEC_ENABLE_REG_1, &val);
		status = smb_wr16(SECOCEC_ENABLE_REG_1, val &
				  ~SECOCEC_ENABLE_REG_1_CEC &
				  ~SECOCEC_ENABLE_REG_1_IR);

		dev_dbg(dev, "Device disabled");
	पूर्ण

	वापस 0;
err:
	वापस status;
पूर्ण

अटल पूर्णांक secocec_adap_log_addr(काष्ठा cec_adapter *adap, u8 logical_addr)
अणु
	u16 enable_val = 0;
	पूर्णांक status;

	/* Disable device */
	status = smb_rd16(SECOCEC_ENABLE_REG_1, &enable_val);
	अगर (status)
		वापस status;

	status = smb_wr16(SECOCEC_ENABLE_REG_1,
			  enable_val & ~SECOCEC_ENABLE_REG_1_CEC);
	अगर (status)
		वापस status;

	/* Write logical address
	 * NOTE: CEC_LOG_ADDR_INVALID is mapped to the 'Unregistered' LA
	 */
	status = smb_wr16(SECOCEC_DEVICE_LA, logical_addr & 0xf);
	अगर (status)
		वापस status;

	/* Re-enable device */
	status = smb_wr16(SECOCEC_ENABLE_REG_1,
			  enable_val | SECOCEC_ENABLE_REG_1_CEC);
	अगर (status)
		वापस status;

	वापस 0;
पूर्ण

अटल पूर्णांक secocec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				 u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	u16 payload_len, payload_id_len, destination, val = 0;
	u8 *payload_msg;
	पूर्णांक status;
	u8 i;

	/* Device msg len alपढ़ोy accounts क्रम header */
	payload_id_len = msg->len - 1;

	/* Send data length */
	status = smb_wr16(SECOCEC_WRITE_DATA_LENGTH, payload_id_len);
	अगर (status)
		जाओ err;

	/* Send Operation ID अगर present */
	अगर (payload_id_len > 0) अणु
		status = smb_wr16(SECOCEC_WRITE_OPERATION_ID, msg->msg[1]);
		अगर (status)
			जाओ err;
	पूर्ण
	/* Send data अगर present */
	अगर (payload_id_len > 1) अणु
		/* Only data; */
		payload_len = msg->len - 2;
		payload_msg = &msg->msg[2];

		/* Copy message पूर्णांकo रेजिस्टरs */
		क्रम (i = 0; i < payload_len; i += 2) अणु
			/* hi byte */
			val = payload_msg[i + 1] << 8;

			/* lo byte */
			val |= payload_msg[i];

			status = smb_wr16(SECOCEC_WRITE_DATA_00 + i / 2, val);
			अगर (status)
				जाओ err;
		पूर्ण
	पूर्ण
	/* Send msg source/destination and fire msg */
	destination = msg->msg[0];
	status = smb_wr16(SECOCEC_WRITE_BYTE0, destination);
	अगर (status)
		जाओ err;

	वापस 0;

err:
	वापस status;
पूर्ण

अटल व्योम secocec_tx_करोne(काष्ठा cec_adapter *adap, u16 status_val)
अणु
	अगर (status_val & SECOCEC_STATUS_TX_ERROR_MASK) अणु
		अगर (status_val & SECOCEC_STATUS_TX_NACK_ERROR)
			cec_transmit_attempt_करोne(adap, CEC_TX_STATUS_NACK);
		अन्यथा
			cec_transmit_attempt_करोne(adap, CEC_TX_STATUS_ERROR);
	पूर्ण अन्यथा अणु
		cec_transmit_attempt_करोne(adap, CEC_TX_STATUS_OK);
	पूर्ण

	/* Reset status reg */
	status_val = SECOCEC_STATUS_TX_ERROR_MASK |
		SECOCEC_STATUS_MSG_SENT_MASK |
		SECOCEC_STATUS_TX_NACK_ERROR;
	smb_wr16(SECOCEC_STATUS, status_val);
पूर्ण

अटल व्योम secocec_rx_करोne(काष्ठा cec_adapter *adap, u16 status_val)
अणु
	काष्ठा secocec_data *cec = cec_get_drvdata(adap);
	काष्ठा device *dev = cec->dev;
	काष्ठा cec_msg msg = अणु पूर्ण;
	bool flag_overflow = false;
	u8 payload_len, i = 0;
	u8 *payload_msg;
	u16 val = 0;
	पूर्णांक status;

	अगर (status_val & SECOCEC_STATUS_RX_OVERFLOW_MASK) अणु
		/* NOTE: Untested, it also might not be necessary */
		dev_warn(dev, "Received more than 16 bytes. Discarding");
		flag_overflow = true;
	पूर्ण

	अगर (status_val & SECOCEC_STATUS_RX_ERROR_MASK) अणु
		dev_warn(dev, "Message received with errors. Discarding");
		status = -EIO;
		जाओ rxerr;
	पूर्ण

	/* Read message length */
	status = smb_rd16(SECOCEC_READ_DATA_LENGTH, &val);
	अगर (status)
		वापस;

	/* Device msg len alपढ़ोy accounts क्रम the header */
	msg.len = min(val + 1, CEC_MAX_MSG_SIZE);

	/* Read logical address */
	status = smb_rd16(SECOCEC_READ_BYTE0, &val);
	अगर (status)
		वापस;

	/* device stores source LA and destination */
	msg.msg[0] = val;

	/* Read operation ID */
	status = smb_rd16(SECOCEC_READ_OPERATION_ID, &val);
	अगर (status)
		वापस;

	msg.msg[1] = val;

	/* Read data अगर present */
	अगर (msg.len > 1) अणु
		payload_len = msg.len - 2;
		payload_msg = &msg.msg[2];

		/* device stores 2 bytes in every 16-bit val */
		क्रम (i = 0; i < payload_len; i += 2) अणु
			status = smb_rd16(SECOCEC_READ_DATA_00 + i / 2, &val);
			अगर (status)
				वापस;

			/* low byte, skipping header */
			payload_msg[i] = val & 0x00ff;

			/* hi byte */
			payload_msg[i + 1] = (val & 0xff00) >> 8;
		पूर्ण
	पूर्ण

	cec_received_msg(cec->cec_adap, &msg);

	/* Reset status reg */
	status_val = SECOCEC_STATUS_MSG_RECEIVED_MASK;
	अगर (flag_overflow)
		status_val |= SECOCEC_STATUS_RX_OVERFLOW_MASK;

	status = smb_wr16(SECOCEC_STATUS, status_val);

	वापस;

rxerr:
	/* Reset error reg */
	status_val = SECOCEC_STATUS_MSG_RECEIVED_MASK |
		SECOCEC_STATUS_RX_ERROR_MASK;
	अगर (flag_overflow)
		status_val |= SECOCEC_STATUS_RX_OVERFLOW_MASK;
	smb_wr16(SECOCEC_STATUS, status_val);
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops secocec_cec_adap_ops = अणु
	/* Low-level callbacks */
	.adap_enable = secocec_adap_enable,
	.adap_log_addr = secocec_adap_log_addr,
	.adap_transmit = secocec_adap_transmit,
पूर्ण;

#अगर_घोषित CONFIG_CEC_SECO_RC
अटल पूर्णांक secocec_ir_probe(व्योम *priv)
अणु
	काष्ठा secocec_data *cec = priv;
	काष्ठा device *dev = cec->dev;
	पूर्णांक status;
	u16 val;

	/* Prepare the RC input device */
	cec->ir = devm_rc_allocate_device(dev, RC_DRIVER_SCANCODE);
	अगर (!cec->ir)
		वापस -ENOMEM;

	snम_लिखो(cec->ir_input_phys, माप(cec->ir_input_phys),
		 "%s/input0", dev_name(dev));

	cec->ir->device_name = dev_name(dev);
	cec->ir->input_phys = cec->ir_input_phys;
	cec->ir->input_id.bustype = BUS_HOST;
	cec->ir->input_id.venकरोr = 0;
	cec->ir->input_id.product = 0;
	cec->ir->input_id.version = 1;
	cec->ir->driver_name = SECOCEC_DEV_NAME;
	cec->ir->allowed_protocols = RC_PROTO_BIT_RC5;
	cec->ir->priv = cec;
	cec->ir->map_name = RC_MAP_HAUPPAUGE;
	cec->ir->समयout = MS_TO_US(100);

	/* Clear the status रेजिस्टर */
	status = smb_rd16(SECOCEC_STATUS_REG_1, &val);
	अगर (status != 0)
		जाओ err;

	status = smb_wr16(SECOCEC_STATUS_REG_1, val);
	अगर (status != 0)
		जाओ err;

	/* Enable the पूर्णांकerrupts */
	status = smb_rd16(SECOCEC_ENABLE_REG_1, &val);
	अगर (status != 0)
		जाओ err;

	status = smb_wr16(SECOCEC_ENABLE_REG_1,
			  val | SECOCEC_ENABLE_REG_1_IR);
	अगर (status != 0)
		जाओ err;

	dev_dbg(dev, "IR enabled");

	status = devm_rc_रेजिस्टर_device(dev, cec->ir);

	अगर (status) अणु
		dev_err(dev, "Failed to prepare input device");
		cec->ir = शून्य;
		जाओ err;
	पूर्ण

	वापस 0;

err:
	smb_rd16(SECOCEC_ENABLE_REG_1, &val);

	smb_wr16(SECOCEC_ENABLE_REG_1,
		 val & ~SECOCEC_ENABLE_REG_1_IR);

	dev_dbg(dev, "IR disabled");
	वापस status;
पूर्ण

अटल पूर्णांक secocec_ir_rx(काष्ठा secocec_data *priv)
अणु
	काष्ठा secocec_data *cec = priv;
	काष्ठा device *dev = cec->dev;
	u16 val, status, key, addr, toggle;

	अगर (!cec->ir)
		वापस -ENODEV;

	status = smb_rd16(SECOCEC_IR_READ_DATA, &val);
	अगर (status != 0)
		जाओ err;

	key = val & SECOCEC_IR_COMMAND_MASK;
	addr = (val & SECOCEC_IR_ADDRESS_MASK) >> SECOCEC_IR_ADDRESS_SHL;
	toggle = (val & SECOCEC_IR_TOGGLE_MASK) >> SECOCEC_IR_TOGGLE_SHL;

	rc_keyकरोwn(cec->ir, RC_PROTO_RC5, RC_SCANCODE_RC5(addr, key), toggle);

	dev_dbg(dev, "IR key pressed: 0x%02x addr 0x%02x toggle 0x%02x", key,
		addr, toggle);

	वापस 0;

err:
	dev_err(dev, "IR Receive message failed (%d)", status);
	वापस -EIO;
पूर्ण
#अन्यथा
अटल व्योम secocec_ir_rx(काष्ठा secocec_data *priv)
अणु
पूर्ण

अटल पूर्णांक secocec_ir_probe(व्योम *priv)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल irqवापस_t secocec_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा secocec_data *cec = priv;
	काष्ठा device *dev = cec->dev;
	u16 status_val, cec_val, val = 0;
	पूर्णांक status;

	/*  Read status रेजिस्टर */
	status = smb_rd16(SECOCEC_STATUS_REG_1, &status_val);
	अगर (status)
		जाओ err;

	अगर (status_val & SECOCEC_STATUS_REG_1_CEC) अणु
		/* Read CEC status रेजिस्टर */
		status = smb_rd16(SECOCEC_STATUS, &cec_val);
		अगर (status)
			जाओ err;

		अगर (cec_val & SECOCEC_STATUS_MSG_RECEIVED_MASK)
			secocec_rx_करोne(cec->cec_adap, cec_val);

		अगर (cec_val & SECOCEC_STATUS_MSG_SENT_MASK)
			secocec_tx_करोne(cec->cec_adap, cec_val);

		अगर ((~cec_val & SECOCEC_STATUS_MSG_SENT_MASK) &&
		    (~cec_val & SECOCEC_STATUS_MSG_RECEIVED_MASK))
			dev_warn_once(dev,
				      "Message not received or sent, but interrupt fired");

		val = SECOCEC_STATUS_REG_1_CEC;
	पूर्ण

	अगर (status_val & SECOCEC_STATUS_REG_1_IR) अणु
		val |= SECOCEC_STATUS_REG_1_IR;

		secocec_ir_rx(cec);
	पूर्ण

	/*  Reset status रेजिस्टर */
	status = smb_wr16(SECOCEC_STATUS_REG_1, val);
	अगर (status)
		जाओ err;

	वापस IRQ_HANDLED;

err:
	dev_err_once(dev, "IRQ: R/W SMBus operation failed (%d)", status);

	/*  Reset status रेजिस्टर */
	val = SECOCEC_STATUS_REG_1_CEC | SECOCEC_STATUS_REG_1_IR;
	smb_wr16(SECOCEC_STATUS_REG_1, val);

	वापस IRQ_HANDLED;
पूर्ण

काष्ठा cec_dmi_match अणु
	स्थिर अक्षर *sys_venकरोr;
	स्थिर अक्षर *product_name;
	स्थिर अक्षर *devname;
	स्थिर अक्षर *conn;
पूर्ण;

अटल स्थिर काष्ठा cec_dmi_match secocec_dmi_match_table[] = अणु
	/* UDOO X86 */
	अणु "SECO", "UDOO x86", "0000:00:02.0", "Port B" पूर्ण,
पूर्ण;

अटल काष्ठा device *secocec_cec_find_hdmi_dev(काष्ठा device *dev,
						स्थिर अक्षर **conn)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < ARRAY_SIZE(secocec_dmi_match_table) ; ++i) अणु
		स्थिर काष्ठा cec_dmi_match *m = &secocec_dmi_match_table[i];

		अगर (dmi_match(DMI_SYS_VENDOR, m->sys_venकरोr) &&
		    dmi_match(DMI_PRODUCT_NAME, m->product_name)) अणु
			काष्ठा device *d;

			/* Find the device, bail out अगर not yet रेजिस्टरed */
			d = bus_find_device_by_name(&pci_bus_type, शून्य,
						    m->devname);
			अगर (!d)
				वापस ERR_PTR(-EPROBE_DEFER);

			put_device(d);
			*conn = m->conn;
			वापस d;
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक secocec_acpi_probe(काष्ठा secocec_data *sdev)
अणु
	काष्ठा device *dev = sdev->dev;
	काष्ठा gpio_desc *gpio;
	पूर्णांक irq = 0;

	gpio = devm_gpiod_get(dev, शून्य, GPIOF_IN);
	अगर (IS_ERR(gpio)) अणु
		dev_err(dev, "Cannot request interrupt gpio");
		वापस PTR_ERR(gpio);
	पूर्ण

	irq = gpiod_to_irq(gpio);
	अगर (irq < 0) अणु
		dev_err(dev, "Cannot find valid irq");
		वापस -ENODEV;
	पूर्ण
	dev_dbg(dev, "irq-gpio is bound to IRQ %d", irq);

	sdev->irq = irq;

	वापस 0;
पूर्ण

अटल पूर्णांक secocec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा secocec_data *secocec;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *hdmi_dev;
	स्थिर अक्षर *conn = शून्य;
	पूर्णांक ret;
	u16 val;

	hdmi_dev = secocec_cec_find_hdmi_dev(&pdev->dev, &conn);
	अगर (IS_ERR(hdmi_dev))
		वापस PTR_ERR(hdmi_dev);

	secocec = devm_kzalloc(dev, माप(*secocec), GFP_KERNEL);
	अगर (!secocec)
		वापस -ENOMEM;

	dev_set_drvdata(dev, secocec);

	/* Request SMBus regions */
	अगर (!request_muxed_region(BRA_SMB_BASE_ADDR, 7, "CEC00001")) अणु
		dev_err(dev, "Request memory region failed");
		वापस -ENXIO;
	पूर्ण

	secocec->pdev = pdev;
	secocec->dev = dev;

	अगर (!has_acpi_companion(dev)) अणु
		dev_dbg(dev, "Cannot find any ACPI companion");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	ret = secocec_acpi_probe(secocec);
	अगर (ret) अणु
		dev_err(dev, "Cannot assign gpio to IRQ");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/* Firmware version check */
	ret = smb_rd16(SECOCEC_VERSION, &val);
	अगर (ret) अणु
		dev_err(dev, "Cannot check fw version");
		जाओ err;
	पूर्ण
	अगर (val < SECOCEC_LATEST_FW) अणु
		dev_err(dev, "CEC Firmware not supported (v.%04x). Use ver > v.%04x",
			val, SECOCEC_LATEST_FW);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev,
					secocec->irq,
					शून्य,
					secocec_irq_handler,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dev_name(&pdev->dev), secocec);

	अगर (ret) अणु
		dev_err(dev, "Cannot request IRQ %d", secocec->irq);
		ret = -EIO;
		जाओ err;
	पूर्ण

	/* Allocate CEC adapter */
	secocec->cec_adap = cec_allocate_adapter(&secocec_cec_adap_ops,
						 secocec,
						 dev_name(dev),
						 CEC_CAP_DEFAULTS |
						 CEC_CAP_CONNECTOR_INFO,
						 SECOCEC_MAX_ADDRS);

	अगर (IS_ERR(secocec->cec_adap)) अणु
		ret = PTR_ERR(secocec->cec_adap);
		जाओ err;
	पूर्ण

	secocec->notअगरier = cec_notअगरier_cec_adap_रेजिस्टर(hdmi_dev, conn,
							   secocec->cec_adap);
	अगर (!secocec->notअगरier) अणु
		ret = -ENOMEM;
		जाओ err_delete_adapter;
	पूर्ण

	ret = cec_रेजिस्टर_adapter(secocec->cec_adap, dev);
	अगर (ret)
		जाओ err_notअगरier;

	ret = secocec_ir_probe(secocec);
	अगर (ret)
		जाओ err_notअगरier;

	platक्रमm_set_drvdata(pdev, secocec);

	dev_dbg(dev, "Device registered");

	वापस ret;

err_notअगरier:
	cec_notअगरier_cec_adap_unरेजिस्टर(secocec->notअगरier, secocec->cec_adap);
err_delete_adapter:
	cec_delete_adapter(secocec->cec_adap);
err:
	release_region(BRA_SMB_BASE_ADDR, 7);
	dev_err(dev, "%s device probe failed\n", dev_name(dev));

	वापस ret;
पूर्ण

अटल पूर्णांक secocec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा secocec_data *secocec = platक्रमm_get_drvdata(pdev);
	u16 val;

	अगर (secocec->ir) अणु
		smb_rd16(SECOCEC_ENABLE_REG_1, &val);

		smb_wr16(SECOCEC_ENABLE_REG_1, val & ~SECOCEC_ENABLE_REG_1_IR);

		dev_dbg(&pdev->dev, "IR disabled");
	पूर्ण
	cec_notअगरier_cec_adap_unरेजिस्टर(secocec->notअगरier, secocec->cec_adap);
	cec_unरेजिस्टर_adapter(secocec->cec_adap);

	release_region(BRA_SMB_BASE_ADDR, 7);

	dev_dbg(&pdev->dev, "CEC device removed");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक secocec_suspend(काष्ठा device *dev)
अणु
	पूर्णांक status;
	u16 val;

	dev_dbg(dev, "Device going to suspend, disabling");

	/* Clear the status रेजिस्टर */
	status = smb_rd16(SECOCEC_STATUS_REG_1, &val);
	अगर (status)
		जाओ err;

	status = smb_wr16(SECOCEC_STATUS_REG_1, val);
	अगर (status)
		जाओ err;

	/* Disable the पूर्णांकerrupts */
	status = smb_rd16(SECOCEC_ENABLE_REG_1, &val);
	अगर (status)
		जाओ err;

	status = smb_wr16(SECOCEC_ENABLE_REG_1, val &
			  ~SECOCEC_ENABLE_REG_1_CEC & ~SECOCEC_ENABLE_REG_1_IR);
	अगर (status)
		जाओ err;

	वापस 0;

err:
	dev_err(dev, "Suspend failed (err: %d)", status);
	वापस status;
पूर्ण

अटल पूर्णांक secocec_resume(काष्ठा device *dev)
अणु
	पूर्णांक status;
	u16 val;

	dev_dbg(dev, "Resuming device from suspend");

	/* Clear the status रेजिस्टर */
	status = smb_rd16(SECOCEC_STATUS_REG_1, &val);
	अगर (status)
		जाओ err;

	status = smb_wr16(SECOCEC_STATUS_REG_1, val);
	अगर (status)
		जाओ err;

	/* Enable the पूर्णांकerrupts */
	status = smb_rd16(SECOCEC_ENABLE_REG_1, &val);
	अगर (status)
		जाओ err;

	status = smb_wr16(SECOCEC_ENABLE_REG_1, val | SECOCEC_ENABLE_REG_1_CEC);
	अगर (status)
		जाओ err;

	dev_dbg(dev, "Device resumed from suspend");

	वापस 0;

err:
	dev_err(dev, "Resume failed (err: %d)", status);
	वापस status;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(secocec_pm_ops, secocec_suspend, secocec_resume);
#घोषणा SECOCEC_PM_OPS (&secocec_pm_ops)
#अन्यथा
#घोषणा SECOCEC_PM_OPS शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id secocec_acpi_match[] = अणु
	अणु"CEC00001", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, secocec_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver secocec_driver = अणु
	.driver = अणु
		   .name = SECOCEC_DEV_NAME,
		   .acpi_match_table = ACPI_PTR(secocec_acpi_match),
		   .pm = SECOCEC_PM_OPS,
	पूर्ण,
	.probe = secocec_probe,
	.हटाओ = secocec_हटाओ,
पूर्ण;

module_platक्रमm_driver(secocec_driver);

MODULE_DESCRIPTION("SECO CEC X86 Driver");
MODULE_AUTHOR("Ettore Chimenti <ek5.chimenti@gmail.com>");
MODULE_LICENSE("Dual BSD/GPL");
