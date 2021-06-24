<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * KP2000 SPI controller driver
 *
 * Copyright (C) 2014-2018 Daktronics
 * Author: Matt Sickler <matt.sickler@daktronics.com>
 * Very loosely based on spi-omap2-mcspi.c
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gcd.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>
#समावेश <linux/mtd/partitions.h>

#समावेश "kpc.h"

अटल काष्ठा mtd_partition p2kr0_spi0_parts[] = अणु
	अणु .name = "SLOT_0",	.size = 7798784,		.offset = 0,                पूर्ण,
	अणु .name = "SLOT_1",	.size = 7798784,		.offset = MTDPART_OFS_NXTBLKपूर्ण,
	अणु .name = "SLOT_2",	.size = 7798784,		.offset = MTDPART_OFS_NXTBLKपूर्ण,
	अणु .name = "SLOT_3",	.size = 7798784,		.offset = MTDPART_OFS_NXTBLKपूर्ण,
	अणु .name = "CS0_EXTRA",	.size = MTDPART_SIZ_FULL,	.offset = MTDPART_OFS_NXTBLKपूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition p2kr0_spi1_parts[] = अणु
	अणु .name = "SLOT_4",	.size = 7798784,		.offset = 0,                पूर्ण,
	अणु .name = "SLOT_5",	.size = 7798784,		.offset = MTDPART_OFS_NXTBLKपूर्ण,
	अणु .name = "SLOT_6",	.size = 7798784,		.offset = MTDPART_OFS_NXTBLKपूर्ण,
	अणु .name = "SLOT_7",	.size = 7798784,		.offset = MTDPART_OFS_NXTBLKपूर्ण,
	अणु .name = "CS1_EXTRA",	.size = MTDPART_SIZ_FULL,	.offset = MTDPART_OFS_NXTBLKपूर्ण,
पूर्ण;

अटल काष्ठा flash_platक्रमm_data p2kr0_spi0_pdata = अणु
	.name =		"SPI0",
	.nr_parts =	ARRAY_SIZE(p2kr0_spi0_parts),
	.parts =	p2kr0_spi0_parts,
पूर्ण;

अटल काष्ठा flash_platक्रमm_data p2kr0_spi1_pdata = अणु
	.name =		"SPI1",
	.nr_parts =	ARRAY_SIZE(p2kr0_spi1_parts),
	.parts =	p2kr0_spi1_parts,
पूर्ण;

अटल काष्ठा spi_board_info p2kr0_board_info[] = अणु
	अणु
		.modalias =		"n25q256a11",
		.bus_num =		1,
		.chip_select =		0,
		.mode =			SPI_MODE_0,
		.platक्रमm_data =	&p2kr0_spi0_pdata
	पूर्ण,
	अणु
		.modalias =		"n25q256a11",
		.bus_num =		1,
		.chip_select =		1,
		.mode =			SPI_MODE_0,
		.platक्रमm_data =	&p2kr0_spi1_pdata
	पूर्ण,
पूर्ण;

/***************
 * SPI Defines *
 ***************/
#घोषणा KP_SPI_REG_CONFIG 0x0 /* 0x00 */
#घोषणा KP_SPI_REG_STATUS 0x1 /* 0x08 */
#घोषणा KP_SPI_REG_FFCTRL 0x2 /* 0x10 */
#घोषणा KP_SPI_REG_TXDATA 0x3 /* 0x18 */
#घोषणा KP_SPI_REG_RXDATA 0x4 /* 0x20 */

#घोषणा KP_SPI_CLK           48000000
#घोषणा KP_SPI_MAX_FIFODEPTH 64
#घोषणा KP_SPI_MAX_FIFOWCNT  0xFFFF

#घोषणा KP_SPI_REG_CONFIG_TRM_TXRX 0
#घोषणा KP_SPI_REG_CONFIG_TRM_RX   1
#घोषणा KP_SPI_REG_CONFIG_TRM_TX   2

#घोषणा KP_SPI_REG_STATUS_RXS   0x01
#घोषणा KP_SPI_REG_STATUS_TXS   0x02
#घोषणा KP_SPI_REG_STATUS_EOT   0x04
#घोषणा KP_SPI_REG_STATUS_TXFFE 0x10
#घोषणा KP_SPI_REG_STATUS_TXFFF 0x20
#घोषणा KP_SPI_REG_STATUS_RXFFE 0x40
#घोषणा KP_SPI_REG_STATUS_RXFFF 0x80

/******************
 * SPI Structures *
 ******************/
काष्ठा kp_spi अणु
	काष्ठा spi_master  *master;
	u64 __iomem        *base;
	काष्ठा device      *dev;
पूर्ण;

काष्ठा kp_spi_controller_state अणु
	व्योम __iomem   *base;
	s64             conf_cache;
पूर्ण;

जोड़ kp_spi_config अणु
	/* use this to access inभागidual elements */
	काष्ठा __packed spi_config_bitfield अणु
		अचिन्हित पूर्णांक pha       : 1; /* spim_clk Phase      */
		अचिन्हित पूर्णांक pol       : 1; /* spim_clk Polarity   */
		अचिन्हित पूर्णांक epol      : 1; /* spim_csx Polarity   */
		अचिन्हित पूर्णांक dpe       : 1; /* Transmission Enable */
		अचिन्हित पूर्णांक wl        : 5; /* Word Length         */
		अचिन्हित पूर्णांक           : 3;
		अचिन्हित पूर्णांक trm       : 2; /* TxRx Mode           */
		अचिन्हित पूर्णांक cs        : 4; /* Chip Select         */
		अचिन्हित पूर्णांक wcnt      : 7; /* Word Count          */
		अचिन्हित पूर्णांक ffen      : 1; /* FIFO Enable         */
		अचिन्हित पूर्णांक spi_en    : 1; /* SPI Enable          */
		अचिन्हित पूर्णांक           : 5;
	पूर्ण bitfield;
	/* use this to grab the whole रेजिस्टर */
	u32 reg;
पूर्ण;

जोड़ kp_spi_status अणु
	काष्ठा __packed spi_status_bitfield अणु
		अचिन्हित पूर्णांक rx    :  1; /* Rx Status       */
		अचिन्हित पूर्णांक tx    :  1; /* Tx Status       */
		अचिन्हित पूर्णांक eo    :  1; /* End of Transfer */
		अचिन्हित पूर्णांक       :  1;
		अचिन्हित पूर्णांक txffe :  1; /* Tx FIFO Empty   */
		अचिन्हित पूर्णांक txfff :  1; /* Tx FIFO Full    */
		अचिन्हित पूर्णांक rxffe :  1; /* Rx FIFO Empty   */
		अचिन्हित पूर्णांक rxfff :  1; /* Rx FIFO Full    */
		अचिन्हित पूर्णांक       : 24;
	पूर्ण bitfield;
	u32 reg;
पूर्ण;

जोड़ kp_spi_ffctrl अणु
	काष्ठा __packed spi_ffctrl_bitfield अणु
		अचिन्हित पूर्णांक ffstart :  1; /* FIFO Start */
		अचिन्हित पूर्णांक         : 31;
	पूर्ण bitfield;
	u32 reg;
पूर्ण;

/***************
 * SPI Helpers *
 ***************/
	अटल अंतरभूत u64
kp_spi_पढ़ो_reg(काष्ठा kp_spi_controller_state *cs, पूर्णांक idx)
अणु
	u64 __iomem *addr = cs->base;

	addr += idx;
	अगर ((idx == KP_SPI_REG_CONFIG) && (cs->conf_cache >= 0))
		वापस cs->conf_cache;

	वापस पढ़ोq(addr);
पूर्ण

	अटल अंतरभूत व्योम
kp_spi_ग_लिखो_reg(काष्ठा kp_spi_controller_state *cs, पूर्णांक idx, u64 val)
अणु
	u64 __iomem *addr = cs->base;

	addr += idx;
	ग_लिखोq(val, addr);
	अगर (idx == KP_SPI_REG_CONFIG)
		cs->conf_cache = val;
पूर्ण

	अटल पूर्णांक
kp_spi_रुको_क्रम_reg_bit(काष्ठा kp_spi_controller_state *cs, पूर्णांक idx,
			अचिन्हित दीर्घ bit)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(1000);
	जबतक (!(kp_spi_पढ़ो_reg(cs, idx) & bit)) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			अगर (!(kp_spi_पढ़ो_reg(cs, idx) & bit))
				वापस -ETIMEDOUT;
			अन्यथा
				वापस 0;
		पूर्ण
		cpu_relax();
	पूर्ण
	वापस 0;
पूर्ण

	अटल अचिन्हित
kp_spi_txrx_pio(काष्ठा spi_device *spidev, काष्ठा spi_transfer *transfer)
अणु
	काष्ठा kp_spi_controller_state *cs = spidev->controller_state;
	अचिन्हित पूर्णांक count = transfer->len;
	अचिन्हित पूर्णांक c = count;

	पूर्णांक i;
	पूर्णांक res;
	u8 *rx       = transfer->rx_buf;
	स्थिर u8 *tx = transfer->tx_buf;
	पूर्णांक processed = 0;

	अगर (tx) अणु
		क्रम (i = 0 ; i < c ; i++) अणु
			अक्षर val = *tx++;

			res = kp_spi_रुको_क्रम_reg_bit(cs, KP_SPI_REG_STATUS,
						      KP_SPI_REG_STATUS_TXS);
			अगर (res < 0)
				जाओ out;

			kp_spi_ग_लिखो_reg(cs, KP_SPI_REG_TXDATA, val);
			processed++;
		पूर्ण
	पूर्ण अन्यथा अगर (rx) अणु
		क्रम (i = 0 ; i < c ; i++) अणु
			अक्षर test = 0;

			kp_spi_ग_लिखो_reg(cs, KP_SPI_REG_TXDATA, 0x00);
			res = kp_spi_रुको_क्रम_reg_bit(cs, KP_SPI_REG_STATUS,
						      KP_SPI_REG_STATUS_RXS);
			अगर (res < 0)
				जाओ out;

			test = kp_spi_पढ़ो_reg(cs, KP_SPI_REG_RXDATA);
			*rx++ = test;
			processed++;
		पूर्ण
	पूर्ण

	अगर (kp_spi_रुको_क्रम_reg_bit(cs, KP_SPI_REG_STATUS,
				    KP_SPI_REG_STATUS_EOT) < 0) अणु
		//TODO: Figure out how to पात transaction??
		//Ths has never happened in practice though...
	पूर्ण

out:
	वापस processed;
पूर्ण

/*****************
 * SPI Functions *
 *****************/
	अटल पूर्णांक
kp_spi_setup(काष्ठा spi_device *spidev)
अणु
	जोड़ kp_spi_config sc;
	काष्ठा kp_spi *kpspi = spi_master_get_devdata(spidev->master);
	काष्ठा kp_spi_controller_state *cs;

	/* setup controller state */
	cs = spidev->controller_state;
	अगर (!cs) अणु
		cs = kzalloc(माप(*cs), GFP_KERNEL);
		अगर (!cs)
			वापस -ENOMEM;
		cs->base = kpspi->base;
		cs->conf_cache = -1;
		spidev->controller_state = cs;
	पूर्ण

	/* set config रेजिस्टर */
	sc.bitfield.wl = spidev->bits_per_word - 1;
	sc.bitfield.cs = spidev->chip_select;
	sc.bitfield.spi_en = 0;
	sc.bitfield.trm = 0;
	sc.bitfield.ffen = 0;
	kp_spi_ग_लिखो_reg(spidev->controller_state, KP_SPI_REG_CONFIG, sc.reg);
	वापस 0;
पूर्ण

	अटल पूर्णांक
kp_spi_transfer_one_message(काष्ठा spi_master *master, काष्ठा spi_message *m)
अणु
	काष्ठा kp_spi_controller_state *cs;
	काष्ठा spi_device   *spidev;
	काष्ठा kp_spi       *kpspi;
	काष्ठा spi_transfer *transfer;
	जोड़ kp_spi_config sc;
	पूर्णांक status = 0;

	spidev = m->spi;
	kpspi = spi_master_get_devdata(master);
	m->actual_length = 0;
	m->status = 0;

	cs = spidev->controller_state;

	/* reject invalid messages and transfers */
	अगर (list_empty(&m->transfers))
		वापस -EINVAL;

	/* validate input */
	list_क्रम_each_entry(transfer, &m->transfers, transfer_list) अणु
		स्थिर व्योम *tx_buf = transfer->tx_buf;
		व्योम       *rx_buf = transfer->rx_buf;
		अचिन्हित पूर्णांक len = transfer->len;

		अगर (transfer->speed_hz > KP_SPI_CLK ||
		    (len && !(rx_buf || tx_buf))) अणु
			dev_dbg(kpspi->dev, "  transfer: %d Hz, %d %s%s, %d bpw\n",
				transfer->speed_hz,
				len,
				tx_buf ? "tx" : "",
				rx_buf ? "rx" : "",
				transfer->bits_per_word);
			dev_dbg(kpspi->dev, "  transfer -EINVAL\n");
			वापस -EINVAL;
		पूर्ण
		अगर (transfer->speed_hz &&
		    transfer->speed_hz < (KP_SPI_CLK >> 15)) अणु
			dev_dbg(kpspi->dev, "speed_hz %d below minimum %d Hz\n",
				transfer->speed_hz,
				KP_SPI_CLK >> 15);
			dev_dbg(kpspi->dev, "  speed_hz -EINVAL\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* निश्चित chip select to start the sequence*/
	sc.reg = kp_spi_पढ़ो_reg(cs, KP_SPI_REG_CONFIG);
	sc.bitfield.spi_en = 1;
	kp_spi_ग_लिखो_reg(cs, KP_SPI_REG_CONFIG, sc.reg);

	/* work */
	अगर (kp_spi_रुको_क्रम_reg_bit(cs, KP_SPI_REG_STATUS,
				    KP_SPI_REG_STATUS_EOT) < 0) अणु
		dev_info(kpspi->dev, "EOT timed out\n");
		जाओ out;
	पूर्ण

	/* करो the transfers क्रम this message */
	list_क्रम_each_entry(transfer, &m->transfers, transfer_list) अणु
		अगर (!transfer->tx_buf && !transfer->rx_buf &&
		    transfer->len) अणु
			status = -EINVAL;
			जाओ error;
		पूर्ण

		/* transfer */
		अगर (transfer->len) अणु
			अचिन्हित पूर्णांक word_len = spidev->bits_per_word;
			अचिन्हित पूर्णांक count;

			/* set up the transfer... */
			sc.reg = kp_spi_पढ़ो_reg(cs, KP_SPI_REG_CONFIG);

			/* ...direction */
			अगर (transfer->tx_buf)
				sc.bitfield.trm = KP_SPI_REG_CONFIG_TRM_TX;
			अन्यथा अगर (transfer->rx_buf)
				sc.bitfield.trm = KP_SPI_REG_CONFIG_TRM_RX;

			/* ...word length */
			अगर (transfer->bits_per_word)
				word_len = transfer->bits_per_word;
			sc.bitfield.wl = word_len - 1;

			/* ...chip select */
			sc.bitfield.cs = spidev->chip_select;

			/* ...and ग_लिखो the new settings */
			kp_spi_ग_लिखो_reg(cs, KP_SPI_REG_CONFIG, sc.reg);

			/* करो the transfer */
			count = kp_spi_txrx_pio(spidev, transfer);
			m->actual_length += count;

			अगर (count != transfer->len) अणु
				status = -EIO;
				जाओ error;
			पूर्ण
		पूर्ण

		अगर (transfer->delay.value)
			ndelay(spi_delay_to_ns(&transfer->delay, transfer));
	पूर्ण

	/* de-निश्चित chip select to end the sequence */
	sc.reg = kp_spi_पढ़ो_reg(cs, KP_SPI_REG_CONFIG);
	sc.bitfield.spi_en = 0;
	kp_spi_ग_लिखो_reg(cs, KP_SPI_REG_CONFIG, sc.reg);

out:
	/* करोne work */
	spi_finalize_current_message(master);
	वापस 0;

error:
	m->status = status;
	वापस status;
पूर्ण

	अटल व्योम
kp_spi_cleanup(काष्ठा spi_device *spidev)
अणु
	काष्ठा kp_spi_controller_state *cs = spidev->controller_state;

	kमुक्त(cs);
पूर्ण

/******************
 * Probe / Remove *
 ******************/
	अटल पूर्णांक
kp_spi_probe(काष्ठा platक्रमm_device *pldev)
अणु
	काष्ठा kpc_core_device_platdata *drvdata;
	काष्ठा spi_master *master;
	काष्ठा kp_spi *kpspi;
	काष्ठा resource *r;
	पूर्णांक status = 0;
	पूर्णांक i;

	drvdata = pldev->dev.platक्रमm_data;
	अगर (!drvdata) अणु
		dev_err(&pldev->dev, "%s: platform_data is NULL\n", __func__);
		वापस -ENODEV;
	पूर्ण

	master = spi_alloc_master(&pldev->dev, माप(काष्ठा kp_spi));
	अगर (!master) अणु
		dev_err(&pldev->dev, "%s: master allocation failed\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	/* set up the spi functions */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->bits_per_word_mask = (अचिन्हित पूर्णांक)SPI_BPW_RANGE_MASK(4, 32);
	master->setup = kp_spi_setup;
	master->transfer_one_message = kp_spi_transfer_one_message;
	master->cleanup = kp_spi_cleanup;

	platक्रमm_set_drvdata(pldev, master);

	kpspi = spi_master_get_devdata(master);
	kpspi->master = master;
	kpspi->dev = &pldev->dev;

	master->num_chipselect = 4;
	अगर (pldev->id != -1)
		master->bus_num = pldev->id;

	r = platक्रमm_get_resource(pldev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pldev->dev, "%s: Unable to get platform resources\n",
			__func__);
		status = -ENODEV;
		जाओ मुक्त_master;
	पूर्ण

	kpspi->base = devm_ioremap(&pldev->dev, r->start,
				   resource_size(r));

	status = spi_रेजिस्टर_master(master);
	अगर (status < 0) अणु
		dev_err(&pldev->dev, "Unable to register SPI device\n");
		जाओ मुक्त_master;
	पूर्ण

	/* रेजिस्टर the slave boards */
#घोषणा NEW_SPI_DEVICE_FROM_BOARD_INFO_TABLE(table) \
	क्रम (i = 0 ; i < ARRAY_SIZE(table) ; i++) अणु \
		spi_new_device(master, &table[i]); \
	पूर्ण

	चयन ((drvdata->card_id & 0xFFFF0000) >> 16) अणु
	हाल PCI_DEVICE_ID_DAKTRONICS_KADOKA_P2KR0:
		NEW_SPI_DEVICE_FROM_BOARD_INFO_TABLE(p2kr0_board_info);
		अवरोध;
	शेष:
		dev_err(&pldev->dev, "Unknown hardware, cant know what partition table to use!\n");
		जाओ मुक्त_master;
	पूर्ण

	वापस status;

मुक्त_master:
	spi_master_put(master);
	वापस status;
पूर्ण

	अटल पूर्णांक
kp_spi_हटाओ(काष्ठा platक्रमm_device *pldev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pldev);

	spi_unरेजिस्टर_master(master);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver kp_spi_driver = अणु
	.driver = अणु
		.name =     KP_DRIVER_NAME_SPI,
	पूर्ण,
	.probe =    kp_spi_probe,
	.हटाओ =   kp_spi_हटाओ,
पूर्ण;

module_platक्रमm_driver(kp_spi_driver);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:kp_spi");
