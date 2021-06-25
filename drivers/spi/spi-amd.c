<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
//
// AMD SPI controller driver
//
// Copyright (c) 2020, Advanced Micro Devices, Inc.
//
// Author: Sanjay R Mehta <sanju.mehta@amd.com>

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/spi/spi.h>

#घोषणा AMD_SPI_CTRL0_REG	0x00
#घोषणा AMD_SPI_EXEC_CMD	BIT(16)
#घोषणा AMD_SPI_FIFO_CLEAR	BIT(20)
#घोषणा AMD_SPI_BUSY		BIT(31)

#घोषणा AMD_SPI_OPCODE_MASK	0xFF

#घोषणा AMD_SPI_ALT_CS_REG	0x1D
#घोषणा AMD_SPI_ALT_CS_MASK	0x3

#घोषणा AMD_SPI_FIFO_BASE	0x80
#घोषणा AMD_SPI_TX_COUNT_REG	0x48
#घोषणा AMD_SPI_RX_COUNT_REG	0x4B
#घोषणा AMD_SPI_STATUS_REG	0x4C

#घोषणा AMD_SPI_MEM_SIZE	200

/* M_CMD OP codes क्रम SPI */
#घोषणा AMD_SPI_XFER_TX		1
#घोषणा AMD_SPI_XFER_RX		2

काष्ठा amd_spi अणु
	व्योम __iomem *io_remap_addr;
	अचिन्हित दीर्घ io_base_addr;
	u32 rom_addr;
	u8 chip_select;
पूर्ण;

अटल अंतरभूत u8 amd_spi_पढ़ोreg8(काष्ठा spi_master *master, पूर्णांक idx)
अणु
	काष्ठा amd_spi *amd_spi = spi_master_get_devdata(master);

	वापस ioपढ़ो8((u8 __iomem *)amd_spi->io_remap_addr + idx);
पूर्ण

अटल अंतरभूत व्योम amd_spi_ग_लिखोreg8(काष्ठा spi_master *master, पूर्णांक idx,
				     u8 val)
अणु
	काष्ठा amd_spi *amd_spi = spi_master_get_devdata(master);

	ioग_लिखो8(val, ((u8 __iomem *)amd_spi->io_remap_addr + idx));
पूर्ण

अटल अंतरभूत व्योम amd_spi_setclear_reg8(काष्ठा spi_master *master, पूर्णांक idx,
					 u8 set, u8 clear)
अणु
	u8 पंचांगp = amd_spi_पढ़ोreg8(master, idx);

	पंचांगp = (पंचांगp & ~clear) | set;
	amd_spi_ग_लिखोreg8(master, idx, पंचांगp);
पूर्ण

अटल अंतरभूत u32 amd_spi_पढ़ोreg32(काष्ठा spi_master *master, पूर्णांक idx)
अणु
	काष्ठा amd_spi *amd_spi = spi_master_get_devdata(master);

	वापस ioपढ़ो32((u8 __iomem *)amd_spi->io_remap_addr + idx);
पूर्ण

अटल अंतरभूत व्योम amd_spi_ग_लिखोreg32(काष्ठा spi_master *master, पूर्णांक idx,
				      u32 val)
अणु
	काष्ठा amd_spi *amd_spi = spi_master_get_devdata(master);

	ioग_लिखो32(val, ((u8 __iomem *)amd_spi->io_remap_addr + idx));
पूर्ण

अटल अंतरभूत व्योम amd_spi_setclear_reg32(काष्ठा spi_master *master, पूर्णांक idx,
					  u32 set, u32 clear)
अणु
	u32 पंचांगp = amd_spi_पढ़ोreg32(master, idx);

	पंचांगp = (पंचांगp & ~clear) | set;
	amd_spi_ग_लिखोreg32(master, idx, पंचांगp);
पूर्ण

अटल व्योम amd_spi_select_chip(काष्ठा spi_master *master)
अणु
	काष्ठा amd_spi *amd_spi = spi_master_get_devdata(master);
	u8 chip_select = amd_spi->chip_select;

	amd_spi_setclear_reg8(master, AMD_SPI_ALT_CS_REG, chip_select,
			      AMD_SPI_ALT_CS_MASK);
पूर्ण

अटल व्योम amd_spi_clear_fअगरo_ptr(काष्ठा spi_master *master)
अणु
	amd_spi_setclear_reg32(master, AMD_SPI_CTRL0_REG, AMD_SPI_FIFO_CLEAR,
			       AMD_SPI_FIFO_CLEAR);
पूर्ण

अटल व्योम amd_spi_set_opcode(काष्ठा spi_master *master, u8 cmd_opcode)
अणु
	amd_spi_setclear_reg32(master, AMD_SPI_CTRL0_REG, cmd_opcode,
			       AMD_SPI_OPCODE_MASK);
पूर्ण

अटल अंतरभूत व्योम amd_spi_set_rx_count(काष्ठा spi_master *master,
					u8 rx_count)
अणु
	amd_spi_setclear_reg8(master, AMD_SPI_RX_COUNT_REG, rx_count, 0xff);
पूर्ण

अटल अंतरभूत व्योम amd_spi_set_tx_count(काष्ठा spi_master *master,
					u8 tx_count)
अणु
	amd_spi_setclear_reg8(master, AMD_SPI_TX_COUNT_REG, tx_count, 0xff);
पूर्ण

अटल अंतरभूत पूर्णांक amd_spi_busy_रुको(काष्ठा amd_spi *amd_spi)
अणु
	bool spi_busy;
	पूर्णांक समयout = 100000;

	/* poll क्रम SPI bus to become idle */
	spi_busy = (ioपढ़ो32((u8 __iomem *)amd_spi->io_remap_addr +
		    AMD_SPI_CTRL0_REG) & AMD_SPI_BUSY) == AMD_SPI_BUSY;
	जबतक (spi_busy) अणु
		usleep_range(10, 20);
		अगर (समयout-- < 0)
			वापस -ETIMEDOUT;

		spi_busy = (ioपढ़ो32((u8 __iomem *)amd_spi->io_remap_addr +
			    AMD_SPI_CTRL0_REG) & AMD_SPI_BUSY) == AMD_SPI_BUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम amd_spi_execute_opcode(काष्ठा spi_master *master)
अणु
	काष्ठा amd_spi *amd_spi = spi_master_get_devdata(master);

	/* Set ExecuteOpCode bit in the CTRL0 रेजिस्टर */
	amd_spi_setclear_reg32(master, AMD_SPI_CTRL0_REG, AMD_SPI_EXEC_CMD,
			       AMD_SPI_EXEC_CMD);

	amd_spi_busy_रुको(amd_spi);
पूर्ण

अटल पूर्णांक amd_spi_master_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_master *master = spi->master;

	amd_spi_clear_fअगरo_ptr(master);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक amd_spi_fअगरo_xfer(काष्ठा amd_spi *amd_spi,
				    काष्ठा spi_master *master,
				    काष्ठा spi_message *message)
अणु
	काष्ठा spi_transfer *xfer = शून्य;
	u8 cmd_opcode;
	u8 *buf = शून्य;
	u32 m_cmd = 0;
	u32 i = 0;
	u32 tx_len = 0, rx_len = 0;

	list_क्रम_each_entry(xfer, &message->transfers,
			    transfer_list) अणु
		अगर (xfer->rx_buf)
			m_cmd = AMD_SPI_XFER_RX;
		अगर (xfer->tx_buf)
			m_cmd = AMD_SPI_XFER_TX;

		अगर (m_cmd & AMD_SPI_XFER_TX) अणु
			buf = (u8 *)xfer->tx_buf;
			tx_len = xfer->len - 1;
			cmd_opcode = *(u8 *)xfer->tx_buf;
			buf++;
			amd_spi_set_opcode(master, cmd_opcode);

			/* Write data पूर्णांकo the FIFO. */
			क्रम (i = 0; i < tx_len; i++) अणु
				ioग_लिखो8(buf[i],
					 ((u8 __iomem *)amd_spi->io_remap_addr +
					 AMD_SPI_FIFO_BASE + i));
			पूर्ण

			amd_spi_set_tx_count(master, tx_len);
			amd_spi_clear_fअगरo_ptr(master);
			/* Execute command */
			amd_spi_execute_opcode(master);
		पूर्ण
		अगर (m_cmd & AMD_SPI_XFER_RX) अणु
			/*
			 * Store no. of bytes to be received from
			 * FIFO
			 */
			rx_len = xfer->len;
			buf = (u8 *)xfer->rx_buf;
			amd_spi_set_rx_count(master, rx_len);
			amd_spi_clear_fअगरo_ptr(master);
			/* Execute command */
			amd_spi_execute_opcode(master);
			/* Read data from FIFO to receive buffer  */
			क्रम (i = 0; i < rx_len; i++)
				buf[i] = amd_spi_पढ़ोreg8(master,
							  AMD_SPI_FIFO_BASE +
							  tx_len + i);
		पूर्ण
	पूर्ण

	/* Update statistics */
	message->actual_length = tx_len + rx_len + 1;
	/* complete the transaction */
	message->status = 0;
	spi_finalize_current_message(master);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_spi_master_transfer(काष्ठा spi_master *master,
				   काष्ठा spi_message *msg)
अणु
	काष्ठा amd_spi *amd_spi = spi_master_get_devdata(master);
	काष्ठा spi_device *spi = msg->spi;

	amd_spi->chip_select = spi->chip_select;
	amd_spi_select_chip(master);

	/*
	 * Extract spi_transfers from the spi message and
	 * program the controller.
	 */
	amd_spi_fअगरo_xfer(amd_spi, master, msg);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा spi_master *master;
	काष्ठा amd_spi *amd_spi;
	पूर्णांक err = 0;

	/* Allocate storage क्रम spi_master and driver निजी data */
	master = spi_alloc_master(dev, माप(काष्ठा amd_spi));
	अगर (!master) अणु
		dev_err(dev, "Error allocating SPI master\n");
		वापस -ENOMEM;
	पूर्ण

	amd_spi = spi_master_get_devdata(master);
	amd_spi->io_remap_addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(amd_spi->io_remap_addr)) अणु
		err = PTR_ERR(amd_spi->io_remap_addr);
		dev_err(dev, "error %d ioremap of SPI registers failed\n", err);
		जाओ err_मुक्त_master;
	पूर्ण
	dev_dbg(dev, "io_remap_address: %p\n", amd_spi->io_remap_addr);

	/* Initialize the spi_master fields */
	master->bus_num = 0;
	master->num_chipselect = 4;
	master->mode_bits = 0;
	master->flags = SPI_MASTER_HALF_DUPLEX;
	master->setup = amd_spi_master_setup;
	master->transfer_one_message = amd_spi_master_transfer;

	/* Register the controller with SPI framework */
	err = devm_spi_रेजिस्टर_master(dev, master);
	अगर (err) अणु
		dev_err(dev, "error %d registering SPI controller\n", err);
		जाओ err_मुक्त_master;
	पूर्ण

	वापस 0;

err_मुक्त_master:
	spi_master_put(master);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id spi_acpi_match[] = अणु
	अणु "AMDI0061", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, spi_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver amd_spi_driver = अणु
	.driver = अणु
		.name = "amd_spi",
		.acpi_match_table = ACPI_PTR(spi_acpi_match),
	पूर्ण,
	.probe = amd_spi_probe,
पूर्ण;

module_platक्रमm_driver(amd_spi_driver);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Sanjay Mehta <sanju.mehta@amd.com>");
MODULE_DESCRIPTION("AMD SPI Master Controller Driver");
