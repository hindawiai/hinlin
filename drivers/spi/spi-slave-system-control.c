<शैली गुरु>
/*
 * SPI slave handler controlling प्रणाली state
 *
 * This SPI slave handler allows remote control of प्रणाली reboot, घातer off,
 * halt, and suspend.
 *
 * Copyright (C) 2016-2017 Glider bvba
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Usage (assuming /dev/spidev2.0 corresponds to the SPI master on the remote
 * प्रणाली):
 *
 *   # reboot='\x7c\x50'
 *   # घातeroff='\x71\x3f'
 *   # halt='\x38\x76'
 *   # suspend='\x1b\x1b'
 *   # spidev_test -D /dev/spidev2.0 -p $suspend # or $reboot, $घातeroff, $halt
 */

#समावेश <linux/completion.h>
#समावेश <linux/module.h>
#समावेश <linux/reboot.h>
#समावेश <linux/suspend.h>
#समावेश <linux/spi/spi.h>

/*
 * The numbers are chosen to display something human-पढ़ोable on two 7-segment
 * displays connected to two 74HC595 shअगरt रेजिस्टरs
 */
#घोषणा CMD_REBOOT	0x7c50	/* rb */
#घोषणा CMD_POWEROFF	0x713f	/* OF */
#घोषणा CMD_HALT	0x3876	/* HL */
#घोषणा CMD_SUSPEND	0x1b1b	/* ZZ */

काष्ठा spi_slave_प्रणाली_control_priv अणु
	काष्ठा spi_device *spi;
	काष्ठा completion finished;
	काष्ठा spi_transfer xfer;
	काष्ठा spi_message msg;
	__be16 cmd;
पूर्ण;

अटल
पूर्णांक spi_slave_प्रणाली_control_submit(काष्ठा spi_slave_प्रणाली_control_priv *priv);

अटल व्योम spi_slave_प्रणाली_control_complete(व्योम *arg)
अणु
	काष्ठा spi_slave_प्रणाली_control_priv *priv = arg;
	u16 cmd;
	पूर्णांक ret;

	अगर (priv->msg.status)
		जाओ terminate;

	cmd = be16_to_cpu(priv->cmd);
	चयन (cmd) अणु
	हाल CMD_REBOOT:
		dev_info(&priv->spi->dev, "Rebooting system...\n");
		kernel_restart(शून्य);
		अवरोध;

	हाल CMD_POWEROFF:
		dev_info(&priv->spi->dev, "Powering off system...\n");
		kernel_घातer_off();
		अवरोध;

	हाल CMD_HALT:
		dev_info(&priv->spi->dev, "Halting system...\n");
		kernel_halt();
		अवरोध;

	हाल CMD_SUSPEND:
		dev_info(&priv->spi->dev, "Suspending system...\n");
		pm_suspend(PM_SUSPEND_MEM);
		अवरोध;

	शेष:
		dev_warn(&priv->spi->dev, "Unknown command 0x%x\n", cmd);
		अवरोध;
	पूर्ण

	ret = spi_slave_प्रणाली_control_submit(priv);
	अगर (ret)
		जाओ terminate;

	वापस;

terminate:
	dev_info(&priv->spi->dev, "Terminating\n");
	complete(&priv->finished);
पूर्ण

अटल
पूर्णांक spi_slave_प्रणाली_control_submit(काष्ठा spi_slave_प्रणाली_control_priv *priv)
अणु
	पूर्णांक ret;

	spi_message_init_with_transfers(&priv->msg, &priv->xfer, 1);

	priv->msg.complete = spi_slave_प्रणाली_control_complete;
	priv->msg.context = priv;

	ret = spi_async(priv->spi, &priv->msg);
	अगर (ret)
		dev_err(&priv->spi->dev, "spi_async() failed %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक spi_slave_प्रणाली_control_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_slave_प्रणाली_control_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&spi->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->spi = spi;
	init_completion(&priv->finished);
	priv->xfer.rx_buf = &priv->cmd;
	priv->xfer.len = माप(priv->cmd);

	ret = spi_slave_प्रणाली_control_submit(priv);
	अगर (ret)
		वापस ret;

	spi_set_drvdata(spi, priv);
	वापस 0;
पूर्ण

अटल पूर्णांक spi_slave_प्रणाली_control_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_slave_प्रणाली_control_priv *priv = spi_get_drvdata(spi);

	spi_slave_पात(spi);
	रुको_क्रम_completion(&priv->finished);
	वापस 0;
पूर्ण

अटल काष्ठा spi_driver spi_slave_प्रणाली_control_driver = अणु
	.driver = अणु
		.name	= "spi-slave-system-control",
	पूर्ण,
	.probe		= spi_slave_प्रणाली_control_probe,
	.हटाओ		= spi_slave_प्रणाली_control_हटाओ,
पूर्ण;
module_spi_driver(spi_slave_प्रणाली_control_driver);

MODULE_AUTHOR("Geert Uytterhoeven <geert+renesas@glider.be>");
MODULE_DESCRIPTION("SPI slave handler controlling system state");
MODULE_LICENSE("GPL v2");
