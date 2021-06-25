<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011-2016 Synaptics Incorporated
 * Copyright (c) 2011 Unixphere
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/rmi.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/of.h>
#समावेश "rmi_driver.h"

#घोषणा RMI_SPI_DEFAULT_XFER_BUF_SIZE	64

#घोषणा RMI_PAGE_SELECT_REGISTER	0x00FF
#घोषणा RMI_SPI_PAGE(addr)		(((addr) >> 8) & 0x80)
#घोषणा RMI_SPI_XFER_SIZE_LIMIT		255

#घोषणा BUFFER_SIZE_INCREMENT 32

क्रमागत rmi_spi_op अणु
	RMI_SPI_WRITE = 0,
	RMI_SPI_READ,
	RMI_SPI_V2_READ_UNIFIED,
	RMI_SPI_V2_READ_SPLIT,
	RMI_SPI_V2_WRITE,
पूर्ण;

काष्ठा rmi_spi_cmd अणु
	क्रमागत rmi_spi_op op;
	u16 addr;
पूर्ण;

काष्ठा rmi_spi_xport अणु
	काष्ठा rmi_transport_dev xport;
	काष्ठा spi_device *spi;

	काष्ठा mutex page_mutex;
	पूर्णांक page;

	u8 *rx_buf;
	u8 *tx_buf;
	पूर्णांक xfer_buf_size;

	काष्ठा spi_transfer *rx_xfers;
	काष्ठा spi_transfer *tx_xfers;
	पूर्णांक rx_xfer_count;
	पूर्णांक tx_xfer_count;
पूर्ण;

अटल पूर्णांक rmi_spi_manage_pools(काष्ठा rmi_spi_xport *rmi_spi, पूर्णांक len)
अणु
	काष्ठा spi_device *spi = rmi_spi->spi;
	पूर्णांक buf_size = rmi_spi->xfer_buf_size
		? rmi_spi->xfer_buf_size : RMI_SPI_DEFAULT_XFER_BUF_SIZE;
	काष्ठा spi_transfer *xfer_buf;
	व्योम *buf;
	व्योम *पंचांगp;

	जबतक (buf_size < len)
		buf_size *= 2;

	अगर (buf_size > RMI_SPI_XFER_SIZE_LIMIT)
		buf_size = RMI_SPI_XFER_SIZE_LIMIT;

	पंचांगp = rmi_spi->rx_buf;
	buf = devm_kसुस्मृति(&spi->dev, buf_size, 2,
				GFP_KERNEL | GFP_DMA);
	अगर (!buf)
		वापस -ENOMEM;

	rmi_spi->rx_buf = buf;
	rmi_spi->tx_buf = &rmi_spi->rx_buf[buf_size];
	rmi_spi->xfer_buf_size = buf_size;

	अगर (पंचांगp)
		devm_kमुक्त(&spi->dev, पंचांगp);

	अगर (rmi_spi->xport.pdata.spi_data.पढ़ो_delay_us)
		rmi_spi->rx_xfer_count = buf_size;
	अन्यथा
		rmi_spi->rx_xfer_count = 1;

	अगर (rmi_spi->xport.pdata.spi_data.ग_लिखो_delay_us)
		rmi_spi->tx_xfer_count = buf_size;
	अन्यथा
		rmi_spi->tx_xfer_count = 1;

	/*
	 * Allocate a pool of spi_transfer buffers क्रम devices which need
	 * per byte delays.
	 */
	पंचांगp = rmi_spi->rx_xfers;
	xfer_buf = devm_kसुस्मृति(&spi->dev,
		rmi_spi->rx_xfer_count + rmi_spi->tx_xfer_count,
		माप(काष्ठा spi_transfer),
		GFP_KERNEL);
	अगर (!xfer_buf)
		वापस -ENOMEM;

	rmi_spi->rx_xfers = xfer_buf;
	rmi_spi->tx_xfers = &xfer_buf[rmi_spi->rx_xfer_count];

	अगर (पंचांगp)
		devm_kमुक्त(&spi->dev, पंचांगp);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_spi_xfer(काष्ठा rmi_spi_xport *rmi_spi,
			स्थिर काष्ठा rmi_spi_cmd *cmd, स्थिर u8 *tx_buf,
			पूर्णांक tx_len, u8 *rx_buf, पूर्णांक rx_len)
अणु
	काष्ठा spi_device *spi = rmi_spi->spi;
	काष्ठा rmi_device_platक्रमm_data_spi *spi_data =
					&rmi_spi->xport.pdata.spi_data;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer *xfer;
	पूर्णांक ret = 0;
	पूर्णांक len;
	पूर्णांक cmd_len = 0;
	पूर्णांक total_tx_len;
	पूर्णांक i;
	u16 addr = cmd->addr;

	spi_message_init(&msg);

	चयन (cmd->op) अणु
	हाल RMI_SPI_WRITE:
	हाल RMI_SPI_READ:
		cmd_len += 2;
		अवरोध;
	हाल RMI_SPI_V2_READ_UNIFIED:
	हाल RMI_SPI_V2_READ_SPLIT:
	हाल RMI_SPI_V2_WRITE:
		cmd_len += 4;
		अवरोध;
	पूर्ण

	total_tx_len = cmd_len + tx_len;
	len = max(total_tx_len, rx_len);

	अगर (len > RMI_SPI_XFER_SIZE_LIMIT)
		वापस -EINVAL;

	अगर (rmi_spi->xfer_buf_size < len) अणु
		ret = rmi_spi_manage_pools(rmi_spi, len);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (addr == 0)
		/*
		 * SPI needs an address. Use 0x7FF अगर we want to keep
		 * पढ़ोing from the last position of the रेजिस्टर poपूर्णांकer.
		 */
		addr = 0x7FF;

	चयन (cmd->op) अणु
	हाल RMI_SPI_WRITE:
		rmi_spi->tx_buf[0] = (addr >> 8);
		rmi_spi->tx_buf[1] = addr & 0xFF;
		अवरोध;
	हाल RMI_SPI_READ:
		rmi_spi->tx_buf[0] = (addr >> 8) | 0x80;
		rmi_spi->tx_buf[1] = addr & 0xFF;
		अवरोध;
	हाल RMI_SPI_V2_READ_UNIFIED:
		अवरोध;
	हाल RMI_SPI_V2_READ_SPLIT:
		अवरोध;
	हाल RMI_SPI_V2_WRITE:
		rmi_spi->tx_buf[0] = 0x40;
		rmi_spi->tx_buf[1] = (addr >> 8) & 0xFF;
		rmi_spi->tx_buf[2] = addr & 0xFF;
		rmi_spi->tx_buf[3] = tx_len;
		अवरोध;
	पूर्ण

	अगर (tx_buf)
		स_नकल(&rmi_spi->tx_buf[cmd_len], tx_buf, tx_len);

	अगर (rmi_spi->tx_xfer_count > 1) अणु
		क्रम (i = 0; i < total_tx_len; i++) अणु
			xfer = &rmi_spi->tx_xfers[i];
			स_रखो(xfer, 0,	माप(काष्ठा spi_transfer));
			xfer->tx_buf = &rmi_spi->tx_buf[i];
			xfer->len = 1;
			xfer->delay.value = spi_data->ग_लिखो_delay_us;
			xfer->delay.unit = SPI_DELAY_UNIT_USECS;
			spi_message_add_tail(xfer, &msg);
		पूर्ण
	पूर्ण अन्यथा अणु
		xfer = rmi_spi->tx_xfers;
		स_रखो(xfer, 0, माप(काष्ठा spi_transfer));
		xfer->tx_buf = rmi_spi->tx_buf;
		xfer->len = total_tx_len;
		spi_message_add_tail(xfer, &msg);
	पूर्ण

	rmi_dbg(RMI_DEBUG_XPORT, &spi->dev, "%s: cmd: %s tx_buf len: %d tx_buf: %*ph\n",
		__func__, cmd->op == RMI_SPI_WRITE ? "WRITE" : "READ",
		total_tx_len, total_tx_len, rmi_spi->tx_buf);

	अगर (rx_buf) अणु
		अगर (rmi_spi->rx_xfer_count > 1) अणु
			क्रम (i = 0; i < rx_len; i++) अणु
				xfer = &rmi_spi->rx_xfers[i];
				स_रखो(xfer, 0, माप(काष्ठा spi_transfer));
				xfer->rx_buf = &rmi_spi->rx_buf[i];
				xfer->len = 1;
				xfer->delay.value = spi_data->पढ़ो_delay_us;
				xfer->delay.unit = SPI_DELAY_UNIT_USECS;
				spi_message_add_tail(xfer, &msg);
			पूर्ण
		पूर्ण अन्यथा अणु
			xfer = rmi_spi->rx_xfers;
			स_रखो(xfer, 0, माप(काष्ठा spi_transfer));
			xfer->rx_buf = rmi_spi->rx_buf;
			xfer->len = rx_len;
			spi_message_add_tail(xfer, &msg);
		पूर्ण
	पूर्ण

	ret = spi_sync(spi, &msg);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "spi xfer failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (rx_buf) अणु
		स_नकल(rx_buf, rmi_spi->rx_buf, rx_len);
		rmi_dbg(RMI_DEBUG_XPORT, &spi->dev, "%s: (%d) %*ph\n",
			__func__, rx_len, rx_len, rx_buf);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * rmi_set_page - Set RMI page
 * @xport: The poपूर्णांकer to the rmi_transport_dev काष्ठा
 * @page: The new page address.
 *
 * RMI devices have 16-bit addressing, but some of the transport
 * implementations (like SMBus) only have 8-bit addressing. So RMI implements
 * a page address at 0xff of every page so we can reliable page addresses
 * every 256 रेजिस्टरs.
 *
 * The page_mutex lock must be held when this function is entered.
 *
 * Returns zero on success, non-zero on failure.
 */
अटल पूर्णांक rmi_set_page(काष्ठा rmi_spi_xport *rmi_spi, u8 page)
अणु
	काष्ठा rmi_spi_cmd cmd;
	पूर्णांक ret;

	cmd.op = RMI_SPI_WRITE;
	cmd.addr = RMI_PAGE_SELECT_REGISTER;

	ret = rmi_spi_xfer(rmi_spi, &cmd, &page, 1, शून्य, 0);

	अगर (ret)
		rmi_spi->page = page;

	वापस ret;
पूर्ण

अटल पूर्णांक rmi_spi_ग_लिखो_block(काष्ठा rmi_transport_dev *xport, u16 addr,
			       स्थिर व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा rmi_spi_xport *rmi_spi =
		container_of(xport, काष्ठा rmi_spi_xport, xport);
	काष्ठा rmi_spi_cmd cmd;
	पूर्णांक ret;

	mutex_lock(&rmi_spi->page_mutex);

	अगर (RMI_SPI_PAGE(addr) != rmi_spi->page) अणु
		ret = rmi_set_page(rmi_spi, RMI_SPI_PAGE(addr));
		अगर (ret)
			जाओ निकास;
	पूर्ण

	cmd.op = RMI_SPI_WRITE;
	cmd.addr = addr;

	ret = rmi_spi_xfer(rmi_spi, &cmd, buf, len, शून्य, 0);

निकास:
	mutex_unlock(&rmi_spi->page_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक rmi_spi_पढ़ो_block(काष्ठा rmi_transport_dev *xport, u16 addr,
			      व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा rmi_spi_xport *rmi_spi =
		container_of(xport, काष्ठा rmi_spi_xport, xport);
	काष्ठा rmi_spi_cmd cmd;
	पूर्णांक ret;

	mutex_lock(&rmi_spi->page_mutex);

	अगर (RMI_SPI_PAGE(addr) != rmi_spi->page) अणु
		ret = rmi_set_page(rmi_spi, RMI_SPI_PAGE(addr));
		अगर (ret)
			जाओ निकास;
	पूर्ण

	cmd.op = RMI_SPI_READ;
	cmd.addr = addr;

	ret = rmi_spi_xfer(rmi_spi, &cmd, शून्य, 0, buf, len);

निकास:
	mutex_unlock(&rmi_spi->page_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rmi_transport_ops rmi_spi_ops = अणु
	.ग_लिखो_block	= rmi_spi_ग_लिखो_block,
	.पढ़ो_block	= rmi_spi_पढ़ो_block,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल पूर्णांक rmi_spi_of_probe(काष्ठा spi_device *spi,
			काष्ठा rmi_device_platक्रमm_data *pdata)
अणु
	काष्ठा device *dev = &spi->dev;
	पूर्णांक retval;

	retval = rmi_of_property_पढ़ो_u32(dev,
			&pdata->spi_data.पढ़ो_delay_us,
			"spi-rx-delay-us", 1);
	अगर (retval)
		वापस retval;

	retval = rmi_of_property_पढ़ो_u32(dev,
			&pdata->spi_data.ग_लिखो_delay_us,
			"spi-tx-delay-us", 1);
	अगर (retval)
		वापस retval;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rmi_spi_of_match[] = अणु
	अणु .compatible = "syna,rmi4-spi" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rmi_spi_of_match);
#अन्यथा
अटल अंतरभूत पूर्णांक rmi_spi_of_probe(काष्ठा spi_device *spi,
				काष्ठा rmi_device_platक्रमm_data *pdata)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल व्योम rmi_spi_unरेजिस्टर_transport(व्योम *data)
अणु
	काष्ठा rmi_spi_xport *rmi_spi = data;

	rmi_unरेजिस्टर_transport_device(&rmi_spi->xport);
पूर्ण

अटल पूर्णांक rmi_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा rmi_spi_xport *rmi_spi;
	काष्ठा rmi_device_platक्रमm_data *pdata;
	काष्ठा rmi_device_platक्रमm_data *spi_pdata = spi->dev.platक्रमm_data;
	पूर्णांक error;

	अगर (spi->master->flags & SPI_MASTER_HALF_DUPLEX)
		वापस -EINVAL;

	rmi_spi = devm_kzalloc(&spi->dev, माप(काष्ठा rmi_spi_xport),
			GFP_KERNEL);
	अगर (!rmi_spi)
		वापस -ENOMEM;

	pdata = &rmi_spi->xport.pdata;

	अगर (spi->dev.of_node) अणु
		error = rmi_spi_of_probe(spi, pdata);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अगर (spi_pdata) अणु
		*pdata = *spi_pdata;
	पूर्ण

	अगर (pdata->spi_data.bits_per_word)
		spi->bits_per_word = pdata->spi_data.bits_per_word;

	अगर (pdata->spi_data.mode)
		spi->mode = pdata->spi_data.mode;

	error = spi_setup(spi);
	अगर (error < 0) अणु
		dev_err(&spi->dev, "spi_setup failed!\n");
		वापस error;
	पूर्ण

	pdata->irq = spi->irq;

	rmi_spi->spi = spi;
	mutex_init(&rmi_spi->page_mutex);

	rmi_spi->xport.dev = &spi->dev;
	rmi_spi->xport.proto_name = "spi";
	rmi_spi->xport.ops = &rmi_spi_ops;

	spi_set_drvdata(spi, rmi_spi);

	error = rmi_spi_manage_pools(rmi_spi, RMI_SPI_DEFAULT_XFER_BUF_SIZE);
	अगर (error)
		वापस error;

	/*
	 * Setting the page to zero will (a) make sure the PSR is in a
	 * known state, and (b) make sure we can talk to the device.
	 */
	error = rmi_set_page(rmi_spi, 0);
	अगर (error) अणु
		dev_err(&spi->dev, "Failed to set page select to 0.\n");
		वापस error;
	पूर्ण

	dev_info(&spi->dev, "registering SPI-connected sensor\n");

	error = rmi_रेजिस्टर_transport_device(&rmi_spi->xport);
	अगर (error) अणु
		dev_err(&spi->dev, "failed to register sensor: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_add_action_or_reset(&spi->dev,
					  rmi_spi_unरेजिस्टर_transport,
					  rmi_spi);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rmi_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा rmi_spi_xport *rmi_spi = spi_get_drvdata(spi);
	पूर्णांक ret;

	ret = rmi_driver_suspend(rmi_spi->xport.rmi_dev, true);
	अगर (ret)
		dev_warn(dev, "Failed to resume device: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक rmi_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा rmi_spi_xport *rmi_spi = spi_get_drvdata(spi);
	पूर्णांक ret;

	ret = rmi_driver_resume(rmi_spi->xport.rmi_dev, true);
	अगर (ret)
		dev_warn(dev, "Failed to resume device: %d\n", ret);

	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rmi_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा rmi_spi_xport *rmi_spi = spi_get_drvdata(spi);
	पूर्णांक ret;

	ret = rmi_driver_suspend(rmi_spi->xport.rmi_dev, false);
	अगर (ret)
		dev_warn(dev, "Failed to resume device: %d\n", ret);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा rmi_spi_xport *rmi_spi = spi_get_drvdata(spi);
	पूर्णांक ret;

	ret = rmi_driver_resume(rmi_spi->xport.rmi_dev, false);
	अगर (ret)
		dev_warn(dev, "Failed to resume device: %d\n", ret);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops rmi_spi_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rmi_spi_suspend, rmi_spi_resume)
	SET_RUNTIME_PM_OPS(rmi_spi_runसमय_suspend, rmi_spi_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा spi_device_id rmi_id[] = अणु
	अणु "rmi4_spi", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, rmi_id);

अटल काष्ठा spi_driver rmi_spi_driver = अणु
	.driver = अणु
		.name	= "rmi4_spi",
		.pm	= &rmi_spi_pm,
		.of_match_table = of_match_ptr(rmi_spi_of_match),
	पूर्ण,
	.id_table	= rmi_id,
	.probe		= rmi_spi_probe,
पूर्ण;

module_spi_driver(rmi_spi_driver);

MODULE_AUTHOR("Christopher Heiny <cheiny@synaptics.com>");
MODULE_AUTHOR("Andrew Duggan <aduggan@synaptics.com>");
MODULE_DESCRIPTION("RMI SPI driver");
MODULE_LICENSE("GPL");
