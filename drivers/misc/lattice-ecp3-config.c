<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012 Stefan Roese <sr@denx.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा FIRMWARE_NAME	"lattice-ecp3.bit"

/*
 * The JTAG ID's of the supported FPGA's. The ID is 32bit wide
 * reversed as noted in the manual.
 */
#घोषणा ID_ECP3_17	0xc2088080
#घोषणा ID_ECP3_35	0xc2048080

/* FPGA commands */
#घोषणा FPGA_CMD_READ_ID	0x07	/* plus 24 bits */
#घोषणा FPGA_CMD_READ_STATUS	0x09	/* plus 24 bits */
#घोषणा FPGA_CMD_CLEAR		0x70
#घोषणा FPGA_CMD_REFRESH	0x71
#घोषणा FPGA_CMD_WRITE_EN	0x4a	/* plus 2 bits */
#घोषणा FPGA_CMD_WRITE_DIS	0x4f	/* plus 8 bits */
#घोषणा FPGA_CMD_WRITE_INC	0x41	/* plus 0 bits */

/*
 * The status रेजिस्टर is 32bit revered, DONE is bit 17 from the TN1222.pdf
 * (LatticeECP3 Slave SPI Port User's Guide)
 */
#घोषणा FPGA_STATUS_DONE	0x00004000
#घोषणा FPGA_STATUS_CLEARED	0x00010000

#घोषणा FPGA_CLEAR_TIMEOUT	5000	/* max. 5000ms क्रम FPGA clear */
#घोषणा FPGA_CLEAR_MSLEEP	10
#घोषणा FPGA_CLEAR_LOOP_COUNT	(FPGA_CLEAR_TIMEOUT / FPGA_CLEAR_MSLEEP)

काष्ठा fpga_data अणु
	काष्ठा completion fw_loaded;
पूर्ण;

काष्ठा ecp3_dev अणु
	u32 jedec_id;
	अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा ecp3_dev ecp3_dev[] = अणु
	अणु
		.jedec_id = ID_ECP3_17,
		.name = "Lattice ECP3-17",
	पूर्ण,
	अणु
		.jedec_id = ID_ECP3_35,
		.name = "Lattice ECP3-35",
	पूर्ण,
पूर्ण;

अटल व्योम firmware_load(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा spi_device *spi = (काष्ठा spi_device *)context;
	काष्ठा fpga_data *data = spi_get_drvdata(spi);
	u8 *buffer;
	u8 txbuf[8];
	u8 rxbuf[8];
	पूर्णांक rx_len = 8;
	पूर्णांक i;
	u32 jedec_id;
	u32 status;

	अगर (fw == शून्य) अणु
		dev_err(&spi->dev, "Cannot load firmware, aborting\n");
		वापस;
	पूर्ण

	अगर (fw->size == 0) अणु
		dev_err(&spi->dev, "Error: Firmware size is 0!\n");
		वापस;
	पूर्ण

	/* Fill dummy data (24 stuffing bits क्रम commands) */
	txbuf[1] = 0x00;
	txbuf[2] = 0x00;
	txbuf[3] = 0x00;

	/* Trying to speak with the FPGA via SPI... */
	txbuf[0] = FPGA_CMD_READ_ID;
	spi_ग_लिखो_then_पढ़ो(spi, txbuf, 8, rxbuf, rx_len);
	jedec_id = get_unaligned_be32(&rxbuf[4]);
	dev_dbg(&spi->dev, "FPGA JTAG ID=%08x\n", jedec_id);

	क्रम (i = 0; i < ARRAY_SIZE(ecp3_dev); i++) अणु
		अगर (jedec_id == ecp3_dev[i].jedec_id)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(ecp3_dev)) अणु
		dev_err(&spi->dev,
			"Error: No supported FPGA detected (JEDEC_ID=%08x)!\n",
			jedec_id);
		वापस;
	पूर्ण

	dev_info(&spi->dev, "FPGA %s detected\n", ecp3_dev[i].name);

	txbuf[0] = FPGA_CMD_READ_STATUS;
	spi_ग_लिखो_then_पढ़ो(spi, txbuf, 8, rxbuf, rx_len);
	status = get_unaligned_be32(&rxbuf[4]);
	dev_dbg(&spi->dev, "FPGA Status=%08x\n", status);

	buffer = kzalloc(fw->size + 8, GFP_KERNEL);
	अगर (!buffer) अणु
		dev_err(&spi->dev, "Error: Can't allocate memory!\n");
		वापस;
	पूर्ण

	/*
	 * Insert WRITE_INC command पूर्णांकo stream (one SPI frame)
	 */
	buffer[0] = FPGA_CMD_WRITE_INC;
	buffer[1] = 0xff;
	buffer[2] = 0xff;
	buffer[3] = 0xff;
	स_नकल(buffer + 4, fw->data, fw->size);

	txbuf[0] = FPGA_CMD_REFRESH;
	spi_ग_लिखो(spi, txbuf, 4);

	txbuf[0] = FPGA_CMD_WRITE_EN;
	spi_ग_लिखो(spi, txbuf, 4);

	txbuf[0] = FPGA_CMD_CLEAR;
	spi_ग_लिखो(spi, txbuf, 4);

	/*
	 * Wait क्रम FPGA memory to become cleared
	 */
	क्रम (i = 0; i < FPGA_CLEAR_LOOP_COUNT; i++) अणु
		txbuf[0] = FPGA_CMD_READ_STATUS;
		spi_ग_लिखो_then_पढ़ो(spi, txbuf, 8, rxbuf, rx_len);
		status = get_unaligned_be32(&rxbuf[4]);
		अगर (status == FPGA_STATUS_CLEARED)
			अवरोध;

		msleep(FPGA_CLEAR_MSLEEP);
	पूर्ण

	अगर (i == FPGA_CLEAR_LOOP_COUNT) अणु
		dev_err(&spi->dev,
			"Error: Timeout waiting for FPGA to clear (status=%08x)!\n",
			status);
		kमुक्त(buffer);
		वापस;
	पूर्ण

	dev_info(&spi->dev, "Configuring the FPGA...\n");
	spi_ग_लिखो(spi, buffer, fw->size + 8);

	txbuf[0] = FPGA_CMD_WRITE_DIS;
	spi_ग_लिखो(spi, txbuf, 4);

	txbuf[0] = FPGA_CMD_READ_STATUS;
	spi_ग_लिखो_then_पढ़ो(spi, txbuf, 8, rxbuf, rx_len);
	status = get_unaligned_be32(&rxbuf[4]);
	dev_dbg(&spi->dev, "FPGA Status=%08x\n", status);

	/* Check result */
	अगर (status & FPGA_STATUS_DONE)
		dev_info(&spi->dev, "FPGA successfully configured!\n");
	अन्यथा
		dev_info(&spi->dev, "FPGA not configured (DONE not set)\n");

	/*
	 * Don't क्रमget to release the firmware again
	 */
	release_firmware(fw);

	kमुक्त(buffer);

	complete(&data->fw_loaded);
पूर्ण

अटल पूर्णांक lattice_ecp3_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा fpga_data *data;
	पूर्णांक err;

	data = devm_kzalloc(&spi->dev, माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		dev_err(&spi->dev, "Memory allocation for fpga_data failed\n");
		वापस -ENOMEM;
	पूर्ण
	spi_set_drvdata(spi, data);

	init_completion(&data->fw_loaded);
	err = request_firmware_noरुको(THIS_MODULE, FW_ACTION_HOTPLUG,
				      FIRMWARE_NAME, &spi->dev,
				      GFP_KERNEL, spi, firmware_load);
	अगर (err) अणु
		dev_err(&spi->dev, "Firmware loading failed with %d!\n", err);
		वापस err;
	पूर्ण

	dev_info(&spi->dev, "FPGA bitstream configuration driver registered\n");

	वापस 0;
पूर्ण

अटल पूर्णांक lattice_ecp3_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा fpga_data *data = spi_get_drvdata(spi);

	रुको_क्रम_completion(&data->fw_loaded);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id lattice_ecp3_id[] = अणु
	अणु "ecp3-17", 0 पूर्ण,
	अणु "ecp3-35", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, lattice_ecp3_id);

अटल काष्ठा spi_driver lattice_ecp3_driver = अणु
	.driver = अणु
		.name = "lattice-ecp3",
	पूर्ण,
	.probe = lattice_ecp3_probe,
	.हटाओ = lattice_ecp3_हटाओ,
	.id_table = lattice_ecp3_id,
पूर्ण;

module_spi_driver(lattice_ecp3_driver);

MODULE_AUTHOR("Stefan Roese <sr@denx.de>");
MODULE_DESCRIPTION("Lattice ECP3 FPGA configuration via SPI");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FIRMWARE_NAME);
