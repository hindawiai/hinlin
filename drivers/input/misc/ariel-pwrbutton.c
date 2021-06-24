<शैली गुरु>
// SPDX-License-Identअगरier: BSD-2-Clause OR GPL-2.0-or-later
/*
 * Dell Wyse 3020 a.k.a. "Ariel" Power Button Driver
 *
 * Copyright (C) 2020 Lubomir Rपूर्णांकel
 */

#समावेश <linux/device.h>
#समावेश <linux/gfp.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

#घोषणा RESP_COUNTER(response)	(response.header & 0x3)
#घोषणा RESP_SIZE(response)	((response.header >> 2) & 0x3)
#घोषणा RESP_TYPE(response)	((response.header >> 4) & 0xf)

काष्ठा ec_input_response अणु
	u8 reserved;
	u8 header;
	u8 data[3];
पूर्ण __packed;

काष्ठा ariel_pwrbutton अणु
	काष्ठा spi_device *client;
	काष्ठा input_dev *input;
	u8 msg_counter;
पूर्ण;

अटल पूर्णांक ec_input_पढ़ो(काष्ठा ariel_pwrbutton *priv,
			 काष्ठा ec_input_response *response)
अणु
	u8 पढ़ो_request[] = अणु 0x00, 0x5a, 0xa5, 0x00, 0x00 पूर्ण;
	काष्ठा spi_device *spi = priv->client;
	काष्ठा spi_transfer t = अणु
		.tx_buf = पढ़ो_request,
		.rx_buf = response,
		.len = माप(पढ़ो_request),
	पूर्ण;

	compileसमय_निश्चित(माप(पढ़ो_request) == माप(*response),
			   "SPI xfer request/response size mismatch");

	वापस spi_sync_transfer(spi, &t, 1);
पूर्ण

अटल irqवापस_t ec_input_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ariel_pwrbutton *priv = dev_id;
	काष्ठा spi_device *spi = priv->client;
	काष्ठा ec_input_response response;
	पूर्णांक error;
	पूर्णांक i;

	error = ec_input_पढ़ो(priv, &response);
	अगर (error < 0) अणु
		dev_err(&spi->dev, "EC read failed: %d\n", error);
		जाओ out;
	पूर्ण

	अगर (priv->msg_counter == RESP_COUNTER(response)) अणु
		dev_warn(&spi->dev, "No new data to read?\n");
		जाओ out;
	पूर्ण

	priv->msg_counter = RESP_COUNTER(response);

	अगर (RESP_TYPE(response) != 0x3 && RESP_TYPE(response) != 0xc) अणु
		dev_dbg(&spi->dev, "Ignoring message that's not kbd data\n");
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < RESP_SIZE(response); i++) अणु
		चयन (response.data[i]) अणु
		हाल 0x74:
			input_report_key(priv->input, KEY_POWER, 1);
			input_sync(priv->input);
			अवरोध;
		हाल 0xf4:
			input_report_key(priv->input, KEY_POWER, 0);
			input_sync(priv->input);
			अवरोध;
		शेष:
			dev_dbg(&spi->dev, "Unknown scan code: %02x\n",
				response.data[i]);
		पूर्ण
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ariel_pwrbutton_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ec_input_response response;
	काष्ठा ariel_pwrbutton *priv;
	पूर्णांक error;

	अगर (!spi->irq) अणु
		dev_err(&spi->dev, "Missing IRQ.\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(&spi->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->client = spi;
	spi_set_drvdata(spi, priv);

	priv->input = devm_input_allocate_device(&spi->dev);
	अगर (!priv->input)
		वापस -ENOMEM;
	priv->input->name = "Power Button";
	priv->input->dev.parent = &spi->dev;
	input_set_capability(priv->input, EV_KEY, KEY_POWER);
	error = input_रेजिस्टर_device(priv->input);
	अगर (error) अणु
		dev_err(&spi->dev, "error registering input device: %d\n", error);
		वापस error;
	पूर्ण

	error = ec_input_पढ़ो(priv, &response);
	अगर (error < 0) अणु
		dev_err(&spi->dev, "EC read failed: %d\n", error);
		वापस error;
	पूर्ण
	priv->msg_counter = RESP_COUNTER(response);

	error = devm_request_thपढ़ोed_irq(&spi->dev, spi->irq, शून्य,
					  ec_input_पूर्णांकerrupt,
					  IRQF_ONESHOT,
					  "Ariel EC Input", priv);

	अगर (error) अणु
		dev_err(&spi->dev, "Failed to request IRQ %d: %d\n",
			spi->irq, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ariel_pwrbutton_of_match[] = अणु
	अणु .compatible = "dell,wyse-ariel-ec-input" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ariel_pwrbutton_of_match);

अटल काष्ठा spi_driver ariel_pwrbutton_driver = अणु
	.driver = अणु
		.name = "dell-wyse-ariel-ec-input",
		.of_match_table = ariel_pwrbutton_of_match,
	पूर्ण,
	.probe = ariel_pwrbutton_probe,
पूर्ण;
module_spi_driver(ariel_pwrbutton_driver);

MODULE_AUTHOR("Lubomir Rintel <lkundrak@v3.sk>");
MODULE_DESCRIPTION("Dell Wyse 3020 Power Button Input Driver");
MODULE_LICENSE("Dual BSD/GPL");
