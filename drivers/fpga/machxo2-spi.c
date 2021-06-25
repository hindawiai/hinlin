<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Lattice MachXO2 Slave SPI Driver
 *
 * Manage Lattice FPGA firmware that is loaded over SPI using
 * the slave serial configuration पूर्णांकerface.
 *
 * Copyright (C) 2018 Paolo Pisati <p.pisati@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/spi/spi.h>

/* MachXO2 Programming Guide - sysCONFIG Programming Commands */
#घोषणा IDCODE_PUB		अणु0xe0, 0x00, 0x00, 0x00पूर्ण
#घोषणा ISC_ENABLE		अणु0xc6, 0x08, 0x00, 0x00पूर्ण
#घोषणा ISC_ERASE		अणु0x0e, 0x04, 0x00, 0x00पूर्ण
#घोषणा ISC_PROGRAMDONE		अणु0x5e, 0x00, 0x00, 0x00पूर्ण
#घोषणा LSC_INITADDRESS		अणु0x46, 0x00, 0x00, 0x00पूर्ण
#घोषणा LSC_PROGINCRNV		अणु0x70, 0x00, 0x00, 0x01पूर्ण
#घोषणा LSC_READ_STATUS		अणु0x3c, 0x00, 0x00, 0x00पूर्ण
#घोषणा LSC_REFRESH		अणु0x79, 0x00, 0x00, 0x00पूर्ण

/*
 * Max CCLK in Slave SPI mode according to 'MachXO2 Family Data
 * Sheet' sysCONFIG Port Timing Specअगरications (3-36)
 */
#घोषणा MACHXO2_MAX_SPEED		66000000

#घोषणा MACHXO2_LOW_DELAY_USEC		5
#घोषणा MACHXO2_HIGH_DELAY_USEC		200
#घोषणा MACHXO2_REFRESH_USEC		4800
#घोषणा MACHXO2_MAX_BUSY_LOOP		128
#घोषणा MACHXO2_MAX_REFRESH_LOOP	16

#घोषणा MACHXO2_PAGE_SIZE		16
#घोषणा MACHXO2_BUF_SIZE		(MACHXO2_PAGE_SIZE + 4)

/* Status रेजिस्टर bits, errors and error mask */
#घोषणा BUSY	12
#घोषणा DONE	8
#घोषणा DVER	27
#घोषणा ENAB	9
#घोषणा ERRBITS	23
#घोषणा ERRMASK	7
#घोषणा FAIL	13

#घोषणा ENOERR	0 /* no error */
#घोषणा EID	1
#घोषणा ECMD	2
#घोषणा ECRC	3
#घोषणा EPREAM	4 /* preamble error */
#घोषणा EABRT	5 /* पात error */
#घोषणा EOVERFL	6 /* overflow error */
#घोषणा ESDMखातापूर्ण	7 /* SDM खातापूर्ण */

अटल अंतरभूत u8 get_err(अचिन्हित दीर्घ *status)
अणु
	वापस (*status >> ERRBITS) & ERRMASK;
पूर्ण

अटल पूर्णांक get_status(काष्ठा spi_device *spi, अचिन्हित दीर्घ *status)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer rx, tx;
	अटल स्थिर u8 cmd[] = LSC_READ_STATUS;
	पूर्णांक ret;

	स_रखो(&rx, 0, माप(rx));
	स_रखो(&tx, 0, माप(tx));
	tx.tx_buf = cmd;
	tx.len = माप(cmd);
	rx.rx_buf = status;
	rx.len = 4;
	spi_message_init(&msg);
	spi_message_add_tail(&tx, &msg);
	spi_message_add_tail(&rx, &msg);
	ret = spi_sync(spi, &msg);
	अगर (ret)
		वापस ret;

	*status = be32_to_cpu(*status);

	वापस 0;
पूर्ण

#अगर_घोषित DEBUG
अटल स्थिर अक्षर *get_err_string(u8 err)
अणु
	चयन (err) अणु
	हाल ENOERR:	वापस "No Error";
	हाल EID:	वापस "ID ERR";
	हाल ECMD:	वापस "CMD ERR";
	हाल ECRC:	वापस "CRC ERR";
	हाल EPREAM:	वापस "Preamble ERR";
	हाल EABRT:	वापस "Abort ERR";
	हाल EOVERFL:	वापस "Overflow ERR";
	हाल ESDMखातापूर्ण:	वापस "SDM EOF";
	पूर्ण

	वापस "Default switch case";
पूर्ण
#पूर्ण_अगर

अटल व्योम dump_status_reg(अचिन्हित दीर्घ *status)
अणु
#अगर_घोषित DEBUG
	pr_debug("machxo2 status: 0x%08lX - done=%d, cfgena=%d, busy=%d, fail=%d, devver=%d, err=%s\n",
		 *status, test_bit(DONE, status), test_bit(ENAB, status),
		 test_bit(BUSY, status), test_bit(FAIL, status),
		 test_bit(DVER, status), get_err_string(get_err(status)));
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक रुको_until_not_busy(काष्ठा spi_device *spi)
अणु
	अचिन्हित दीर्घ status;
	पूर्णांक ret, loop = 0;

	करो अणु
		ret = get_status(spi, &status);
		अगर (ret)
			वापस ret;
		अगर (++loop >= MACHXO2_MAX_BUSY_LOOP)
			वापस -EBUSY;
	पूर्ण जबतक (test_bit(BUSY, &status));

	वापस 0;
पूर्ण

अटल पूर्णांक machxo2_cleanup(काष्ठा fpga_manager *mgr)
अणु
	काष्ठा spi_device *spi = mgr->priv;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer tx[2];
	अटल स्थिर u8 erase[] = ISC_ERASE;
	अटल स्थिर u8 refresh[] = LSC_REFRESH;
	पूर्णांक ret;

	स_रखो(tx, 0, माप(tx));
	spi_message_init(&msg);
	tx[0].tx_buf = &erase;
	tx[0].len = माप(erase);
	spi_message_add_tail(&tx[0], &msg);
	ret = spi_sync(spi, &msg);
	अगर (ret)
		जाओ fail;

	ret = रुको_until_not_busy(spi);
	अगर (ret)
		जाओ fail;

	spi_message_init(&msg);
	tx[1].tx_buf = &refresh;
	tx[1].len = माप(refresh);
	tx[1].delay.value = MACHXO2_REFRESH_USEC;
	tx[1].delay.unit = SPI_DELAY_UNIT_USECS;
	spi_message_add_tail(&tx[1], &msg);
	ret = spi_sync(spi, &msg);
	अगर (ret)
		जाओ fail;

	वापस 0;
fail:
	dev_err(&mgr->dev, "Cleanup failed\n");

	वापस ret;
पूर्ण

अटल क्रमागत fpga_mgr_states machxo2_spi_state(काष्ठा fpga_manager *mgr)
अणु
	काष्ठा spi_device *spi = mgr->priv;
	अचिन्हित दीर्घ status;

	get_status(spi, &status);
	अगर (!test_bit(BUSY, &status) && test_bit(DONE, &status) &&
	    get_err(&status) == ENOERR)
		वापस FPGA_MGR_STATE_OPERATING;

	वापस FPGA_MGR_STATE_UNKNOWN;
पूर्ण

अटल पूर्णांक machxo2_ग_लिखो_init(काष्ठा fpga_manager *mgr,
			      काष्ठा fpga_image_info *info,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा spi_device *spi = mgr->priv;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer tx[3];
	अटल स्थिर u8 enable[] = ISC_ENABLE;
	अटल स्थिर u8 erase[] = ISC_ERASE;
	अटल स्थिर u8 initaddr[] = LSC_INITADDRESS;
	अचिन्हित दीर्घ status;
	पूर्णांक ret;

	अगर ((info->flags & FPGA_MGR_PARTIAL_RECONFIG)) अणु
		dev_err(&mgr->dev,
			"Partial reconfiguration is not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	get_status(spi, &status);
	dump_status_reg(&status);
	स_रखो(tx, 0, माप(tx));
	spi_message_init(&msg);
	tx[0].tx_buf = &enable;
	tx[0].len = माप(enable);
	tx[0].delay.value = MACHXO2_LOW_DELAY_USEC;
	tx[0].delay.unit = SPI_DELAY_UNIT_USECS;
	spi_message_add_tail(&tx[0], &msg);

	tx[1].tx_buf = &erase;
	tx[1].len = माप(erase);
	spi_message_add_tail(&tx[1], &msg);
	ret = spi_sync(spi, &msg);
	अगर (ret)
		जाओ fail;

	ret = रुको_until_not_busy(spi);
	अगर (ret)
		जाओ fail;

	get_status(spi, &status);
	अगर (test_bit(FAIL, &status))
		जाओ fail;
	dump_status_reg(&status);

	spi_message_init(&msg);
	tx[2].tx_buf = &initaddr;
	tx[2].len = माप(initaddr);
	spi_message_add_tail(&tx[2], &msg);
	ret = spi_sync(spi, &msg);
	अगर (ret)
		जाओ fail;

	get_status(spi, &status);
	dump_status_reg(&status);

	वापस 0;
fail:
	dev_err(&mgr->dev, "Error during FPGA init.\n");

	वापस ret;
पूर्ण

अटल पूर्णांक machxo2_ग_लिखो(काष्ठा fpga_manager *mgr, स्थिर अक्षर *buf,
			 माप_प्रकार count)
अणु
	काष्ठा spi_device *spi = mgr->priv;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer tx;
	अटल स्थिर u8 progincr[] = LSC_PROGINCRNV;
	u8 payload[MACHXO2_BUF_SIZE];
	अचिन्हित दीर्घ status;
	पूर्णांक i, ret;

	अगर (count % MACHXO2_PAGE_SIZE != 0) अणु
		dev_err(&mgr->dev, "Malformed payload.\n");
		वापस -EINVAL;
	पूर्ण
	get_status(spi, &status);
	dump_status_reg(&status);
	स_नकल(payload, &progincr, माप(progincr));
	क्रम (i = 0; i < count; i += MACHXO2_PAGE_SIZE) अणु
		स_नकल(&payload[माप(progincr)], &buf[i], MACHXO2_PAGE_SIZE);
		स_रखो(&tx, 0, माप(tx));
		spi_message_init(&msg);
		tx.tx_buf = payload;
		tx.len = MACHXO2_BUF_SIZE;
		tx.delay.value = MACHXO2_HIGH_DELAY_USEC;
		tx.delay.unit = SPI_DELAY_UNIT_USECS;
		spi_message_add_tail(&tx, &msg);
		ret = spi_sync(spi, &msg);
		अगर (ret) अणु
			dev_err(&mgr->dev, "Error loading the bitstream.\n");
			वापस ret;
		पूर्ण
	पूर्ण
	get_status(spi, &status);
	dump_status_reg(&status);

	वापस 0;
पूर्ण

अटल पूर्णांक machxo2_ग_लिखो_complete(काष्ठा fpga_manager *mgr,
				  काष्ठा fpga_image_info *info)
अणु
	काष्ठा spi_device *spi = mgr->priv;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer tx[2];
	अटल स्थिर u8 progकरोne[] = ISC_PROGRAMDONE;
	अटल स्थिर u8 refresh[] = LSC_REFRESH;
	अचिन्हित दीर्घ status;
	पूर्णांक ret, refreshloop = 0;

	स_रखो(tx, 0, माप(tx));
	spi_message_init(&msg);
	tx[0].tx_buf = &progकरोne;
	tx[0].len = माप(progकरोne);
	spi_message_add_tail(&tx[0], &msg);
	ret = spi_sync(spi, &msg);
	अगर (ret)
		जाओ fail;
	ret = रुको_until_not_busy(spi);
	अगर (ret)
		जाओ fail;

	get_status(spi, &status);
	dump_status_reg(&status);
	अगर (!test_bit(DONE, &status)) अणु
		machxo2_cleanup(mgr);
		जाओ fail;
	पूर्ण

	करो अणु
		spi_message_init(&msg);
		tx[1].tx_buf = &refresh;
		tx[1].len = माप(refresh);
		tx[1].delay.value = MACHXO2_REFRESH_USEC;
		tx[1].delay.unit = SPI_DELAY_UNIT_USECS;
		spi_message_add_tail(&tx[1], &msg);
		ret = spi_sync(spi, &msg);
		अगर (ret)
			जाओ fail;

		/* check refresh status */
		get_status(spi, &status);
		dump_status_reg(&status);
		अगर (!test_bit(BUSY, &status) && test_bit(DONE, &status) &&
		    get_err(&status) == ENOERR)
			अवरोध;
		अगर (++refreshloop == MACHXO2_MAX_REFRESH_LOOP) अणु
			machxo2_cleanup(mgr);
			जाओ fail;
		पूर्ण
	पूर्ण जबतक (1);

	get_status(spi, &status);
	dump_status_reg(&status);

	वापस 0;
fail:
	dev_err(&mgr->dev, "Refresh failed.\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा fpga_manager_ops machxo2_ops = अणु
	.state = machxo2_spi_state,
	.ग_लिखो_init = machxo2_ग_लिखो_init,
	.ग_लिखो = machxo2_ग_लिखो,
	.ग_लिखो_complete = machxo2_ग_लिखो_complete,
पूर्ण;

अटल पूर्णांक machxo2_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा fpga_manager *mgr;

	अगर (spi->max_speed_hz > MACHXO2_MAX_SPEED) अणु
		dev_err(dev, "Speed is too high\n");
		वापस -EINVAL;
	पूर्ण

	mgr = devm_fpga_mgr_create(dev, "Lattice MachXO2 SPI FPGA Manager",
				   &machxo2_ops, spi);
	अगर (!mgr)
		वापस -ENOMEM;

	वापस devm_fpga_mgr_रेजिस्टर(dev, mgr);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_match[] = अणु
	अणु .compatible = "lattice,machxo2-slave-spi", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_match);

अटल स्थिर काष्ठा spi_device_id lattice_ids[] = अणु
	अणु "machxo2-slave-spi", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, lattice_ids);

अटल काष्ठा spi_driver machxo2_spi_driver = अणु
	.driver = अणु
		.name = "machxo2-slave-spi",
		.of_match_table = of_match_ptr(of_match),
	पूर्ण,
	.probe = machxo2_spi_probe,
	.id_table = lattice_ids,
पूर्ण;

module_spi_driver(machxo2_spi_driver)

MODULE_AUTHOR("Paolo Pisati <p.pisati@gmail.com>");
MODULE_DESCRIPTION("Load Lattice FPGA firmware over SPI");
MODULE_LICENSE("GPL v2");
