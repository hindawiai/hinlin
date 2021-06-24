<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI-Engine SPI controller driver
 * Copyright 2015 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>

#घोषणा SPI_ENGINE_VERSION_MAJOR(x)	((x >> 16) & 0xff)
#घोषणा SPI_ENGINE_VERSION_MINOR(x)	((x >> 8) & 0xff)
#घोषणा SPI_ENGINE_VERSION_PATCH(x)	(x & 0xff)

#घोषणा SPI_ENGINE_REG_VERSION			0x00

#घोषणा SPI_ENGINE_REG_RESET			0x40

#घोषणा SPI_ENGINE_REG_INT_ENABLE		0x80
#घोषणा SPI_ENGINE_REG_INT_PENDING		0x84
#घोषणा SPI_ENGINE_REG_INT_SOURCE		0x88

#घोषणा SPI_ENGINE_REG_SYNC_ID			0xc0

#घोषणा SPI_ENGINE_REG_CMD_FIFO_ROOM		0xd0
#घोषणा SPI_ENGINE_REG_SDO_FIFO_ROOM		0xd4
#घोषणा SPI_ENGINE_REG_SDI_FIFO_LEVEL		0xd8

#घोषणा SPI_ENGINE_REG_CMD_FIFO			0xe0
#घोषणा SPI_ENGINE_REG_SDO_DATA_FIFO		0xe4
#घोषणा SPI_ENGINE_REG_SDI_DATA_FIFO		0xe8
#घोषणा SPI_ENGINE_REG_SDI_DATA_FIFO_PEEK	0xec

#घोषणा SPI_ENGINE_INT_CMD_ALMOST_EMPTY		BIT(0)
#घोषणा SPI_ENGINE_INT_SDO_ALMOST_EMPTY		BIT(1)
#घोषणा SPI_ENGINE_INT_SDI_ALMOST_FULL		BIT(2)
#घोषणा SPI_ENGINE_INT_SYNC			BIT(3)

#घोषणा SPI_ENGINE_CONFIG_CPHA			BIT(0)
#घोषणा SPI_ENGINE_CONFIG_CPOL			BIT(1)
#घोषणा SPI_ENGINE_CONFIG_3WIRE			BIT(2)

#घोषणा SPI_ENGINE_INST_TRANSFER		0x0
#घोषणा SPI_ENGINE_INST_ASSERT			0x1
#घोषणा SPI_ENGINE_INST_WRITE			0x2
#घोषणा SPI_ENGINE_INST_MISC			0x3

#घोषणा SPI_ENGINE_CMD_REG_CLK_DIV		0x0
#घोषणा SPI_ENGINE_CMD_REG_CONFIG		0x1

#घोषणा SPI_ENGINE_MISC_SYNC			0x0
#घोषणा SPI_ENGINE_MISC_SLEEP			0x1

#घोषणा SPI_ENGINE_TRANSFER_WRITE		0x1
#घोषणा SPI_ENGINE_TRANSFER_READ		0x2

#घोषणा SPI_ENGINE_CMD(inst, arg1, arg2) \
	(((inst) << 12) | ((arg1) << 8) | (arg2))

#घोषणा SPI_ENGINE_CMD_TRANSFER(flags, n) \
	SPI_ENGINE_CMD(SPI_ENGINE_INST_TRANSFER, (flags), (n))
#घोषणा SPI_ENGINE_CMD_ASSERT(delay, cs) \
	SPI_ENGINE_CMD(SPI_ENGINE_INST_ASSERT, (delay), (cs))
#घोषणा SPI_ENGINE_CMD_WRITE(reg, val) \
	SPI_ENGINE_CMD(SPI_ENGINE_INST_WRITE, (reg), (val))
#घोषणा SPI_ENGINE_CMD_SLEEP(delay) \
	SPI_ENGINE_CMD(SPI_ENGINE_INST_MISC, SPI_ENGINE_MISC_SLEEP, (delay))
#घोषणा SPI_ENGINE_CMD_SYNC(id) \
	SPI_ENGINE_CMD(SPI_ENGINE_INST_MISC, SPI_ENGINE_MISC_SYNC, (id))

काष्ठा spi_engine_program अणु
	अचिन्हित पूर्णांक length;
	uपूर्णांक16_t inकाष्ठाions[];
पूर्ण;

काष्ठा spi_engine अणु
	काष्ठा clk *clk;
	काष्ठा clk *ref_clk;

	spinlock_t lock;

	व्योम __iomem *base;

	काष्ठा spi_message *msg;
	काष्ठा spi_engine_program *p;
	अचिन्हित cmd_length;
	स्थिर uपूर्णांक16_t *cmd_buf;

	काष्ठा spi_transfer *tx_xfer;
	अचिन्हित पूर्णांक tx_length;
	स्थिर uपूर्णांक8_t *tx_buf;

	काष्ठा spi_transfer *rx_xfer;
	अचिन्हित पूर्णांक rx_length;
	uपूर्णांक8_t *rx_buf;

	अचिन्हित पूर्णांक sync_id;
	अचिन्हित पूर्णांक completed_id;

	अचिन्हित पूर्णांक पूर्णांक_enable;
पूर्ण;

अटल व्योम spi_engine_program_add_cmd(काष्ठा spi_engine_program *p,
	bool dry, uपूर्णांक16_t cmd)
अणु
	अगर (!dry)
		p->inकाष्ठाions[p->length] = cmd;
	p->length++;
पूर्ण

अटल अचिन्हित पूर्णांक spi_engine_get_config(काष्ठा spi_device *spi)
अणु
	अचिन्हित पूर्णांक config = 0;

	अगर (spi->mode & SPI_CPOL)
		config |= SPI_ENGINE_CONFIG_CPOL;
	अगर (spi->mode & SPI_CPHA)
		config |= SPI_ENGINE_CONFIG_CPHA;
	अगर (spi->mode & SPI_3WIRE)
		config |= SPI_ENGINE_CONFIG_3WIRE;

	वापस config;
पूर्ण

अटल अचिन्हित पूर्णांक spi_engine_get_clk_भाग(काष्ठा spi_engine *spi_engine,
	काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer)
अणु
	अचिन्हित पूर्णांक clk_भाग;

	clk_भाग = DIV_ROUND_UP(clk_get_rate(spi_engine->ref_clk),
		xfer->speed_hz * 2);
	अगर (clk_भाग > 255)
		clk_भाग = 255;
	अन्यथा अगर (clk_भाग > 0)
		clk_भाग -= 1;

	वापस clk_भाग;
पूर्ण

अटल व्योम spi_engine_gen_xfer(काष्ठा spi_engine_program *p, bool dry,
	काष्ठा spi_transfer *xfer)
अणु
	अचिन्हित पूर्णांक len = xfer->len;

	जबतक (len) अणु
		अचिन्हित पूर्णांक n = min(len, 256U);
		अचिन्हित पूर्णांक flags = 0;

		अगर (xfer->tx_buf)
			flags |= SPI_ENGINE_TRANSFER_WRITE;
		अगर (xfer->rx_buf)
			flags |= SPI_ENGINE_TRANSFER_READ;

		spi_engine_program_add_cmd(p, dry,
			SPI_ENGINE_CMD_TRANSFER(flags, n - 1));
		len -= n;
	पूर्ण
पूर्ण

अटल व्योम spi_engine_gen_sleep(काष्ठा spi_engine_program *p, bool dry,
	काष्ठा spi_engine *spi_engine, अचिन्हित पूर्णांक clk_भाग,
	काष्ठा spi_transfer *xfer)
अणु
	अचिन्हित पूर्णांक spi_clk = clk_get_rate(spi_engine->ref_clk);
	अचिन्हित पूर्णांक t;
	पूर्णांक delay;

	delay = spi_delay_to_ns(&xfer->delay, xfer);
	अगर (delay < 0)
		वापस;
	delay /= 1000;

	अगर (delay == 0)
		वापस;

	t = DIV_ROUND_UP(delay * spi_clk, (clk_भाग + 1) * 2);
	जबतक (t) अणु
		अचिन्हित पूर्णांक n = min(t, 256U);

		spi_engine_program_add_cmd(p, dry, SPI_ENGINE_CMD_SLEEP(n - 1));
		t -= n;
	पूर्ण
पूर्ण

अटल व्योम spi_engine_gen_cs(काष्ठा spi_engine_program *p, bool dry,
		काष्ठा spi_device *spi, bool निश्चित)
अणु
	अचिन्हित पूर्णांक mask = 0xff;

	अगर (निश्चित)
		mask ^= BIT(spi->chip_select);

	spi_engine_program_add_cmd(p, dry, SPI_ENGINE_CMD_ASSERT(1, mask));
पूर्ण

अटल पूर्णांक spi_engine_compile_message(काष्ठा spi_engine *spi_engine,
	काष्ठा spi_message *msg, bool dry, काष्ठा spi_engine_program *p)
अणु
	काष्ठा spi_device *spi = msg->spi;
	काष्ठा spi_transfer *xfer;
	पूर्णांक clk_भाग, new_clk_भाग;
	bool cs_change = true;

	clk_भाग = -1;

	spi_engine_program_add_cmd(p, dry,
		SPI_ENGINE_CMD_WRITE(SPI_ENGINE_CMD_REG_CONFIG,
			spi_engine_get_config(spi)));

	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		new_clk_भाग = spi_engine_get_clk_भाग(spi_engine, spi, xfer);
		अगर (new_clk_भाग != clk_भाग) अणु
			clk_भाग = new_clk_भाग;
			spi_engine_program_add_cmd(p, dry,
				SPI_ENGINE_CMD_WRITE(SPI_ENGINE_CMD_REG_CLK_DIV,
					clk_भाग));
		पूर्ण

		अगर (cs_change)
			spi_engine_gen_cs(p, dry, spi, true);

		spi_engine_gen_xfer(p, dry, xfer);
		spi_engine_gen_sleep(p, dry, spi_engine, clk_भाग, xfer);

		cs_change = xfer->cs_change;
		अगर (list_is_last(&xfer->transfer_list, &msg->transfers))
			cs_change = !cs_change;

		अगर (cs_change)
			spi_engine_gen_cs(p, dry, spi, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम spi_engine_xfer_next(काष्ठा spi_engine *spi_engine,
	काष्ठा spi_transfer **_xfer)
अणु
	काष्ठा spi_message *msg = spi_engine->msg;
	काष्ठा spi_transfer *xfer = *_xfer;

	अगर (!xfer) अणु
		xfer = list_first_entry(&msg->transfers,
			काष्ठा spi_transfer, transfer_list);
	पूर्ण अन्यथा अगर (list_is_last(&xfer->transfer_list, &msg->transfers)) अणु
		xfer = शून्य;
	पूर्ण अन्यथा अणु
		xfer = list_next_entry(xfer, transfer_list);
	पूर्ण

	*_xfer = xfer;
पूर्ण

अटल व्योम spi_engine_tx_next(काष्ठा spi_engine *spi_engine)
अणु
	काष्ठा spi_transfer *xfer = spi_engine->tx_xfer;

	करो अणु
		spi_engine_xfer_next(spi_engine, &xfer);
	पूर्ण जबतक (xfer && !xfer->tx_buf);

	spi_engine->tx_xfer = xfer;
	अगर (xfer) अणु
		spi_engine->tx_length = xfer->len;
		spi_engine->tx_buf = xfer->tx_buf;
	पूर्ण अन्यथा अणु
		spi_engine->tx_buf = शून्य;
	पूर्ण
पूर्ण

अटल व्योम spi_engine_rx_next(काष्ठा spi_engine *spi_engine)
अणु
	काष्ठा spi_transfer *xfer = spi_engine->rx_xfer;

	करो अणु
		spi_engine_xfer_next(spi_engine, &xfer);
	पूर्ण जबतक (xfer && !xfer->rx_buf);

	spi_engine->rx_xfer = xfer;
	अगर (xfer) अणु
		spi_engine->rx_length = xfer->len;
		spi_engine->rx_buf = xfer->rx_buf;
	पूर्ण अन्यथा अणु
		spi_engine->rx_buf = शून्य;
	पूर्ण
पूर्ण

अटल bool spi_engine_ग_लिखो_cmd_fअगरo(काष्ठा spi_engine *spi_engine)
अणु
	व्योम __iomem *addr = spi_engine->base + SPI_ENGINE_REG_CMD_FIFO;
	अचिन्हित पूर्णांक n, m, i;
	स्थिर uपूर्णांक16_t *buf;

	n = पढ़ोl_relaxed(spi_engine->base + SPI_ENGINE_REG_CMD_FIFO_ROOM);
	जबतक (n && spi_engine->cmd_length) अणु
		m = min(n, spi_engine->cmd_length);
		buf = spi_engine->cmd_buf;
		क्रम (i = 0; i < m; i++)
			ग_लिखोl_relaxed(buf[i], addr);
		spi_engine->cmd_buf += m;
		spi_engine->cmd_length -= m;
		n -= m;
	पूर्ण

	वापस spi_engine->cmd_length != 0;
पूर्ण

अटल bool spi_engine_ग_लिखो_tx_fअगरo(काष्ठा spi_engine *spi_engine)
अणु
	व्योम __iomem *addr = spi_engine->base + SPI_ENGINE_REG_SDO_DATA_FIFO;
	अचिन्हित पूर्णांक n, m, i;
	स्थिर uपूर्णांक8_t *buf;

	n = पढ़ोl_relaxed(spi_engine->base + SPI_ENGINE_REG_SDO_FIFO_ROOM);
	जबतक (n && spi_engine->tx_length) अणु
		m = min(n, spi_engine->tx_length);
		buf = spi_engine->tx_buf;
		क्रम (i = 0; i < m; i++)
			ग_लिखोl_relaxed(buf[i], addr);
		spi_engine->tx_buf += m;
		spi_engine->tx_length -= m;
		n -= m;
		अगर (spi_engine->tx_length == 0)
			spi_engine_tx_next(spi_engine);
	पूर्ण

	वापस spi_engine->tx_length != 0;
पूर्ण

अटल bool spi_engine_पढ़ो_rx_fअगरo(काष्ठा spi_engine *spi_engine)
अणु
	व्योम __iomem *addr = spi_engine->base + SPI_ENGINE_REG_SDI_DATA_FIFO;
	अचिन्हित पूर्णांक n, m, i;
	uपूर्णांक8_t *buf;

	n = पढ़ोl_relaxed(spi_engine->base + SPI_ENGINE_REG_SDI_FIFO_LEVEL);
	जबतक (n && spi_engine->rx_length) अणु
		m = min(n, spi_engine->rx_length);
		buf = spi_engine->rx_buf;
		क्रम (i = 0; i < m; i++)
			buf[i] = पढ़ोl_relaxed(addr);
		spi_engine->rx_buf += m;
		spi_engine->rx_length -= m;
		n -= m;
		अगर (spi_engine->rx_length == 0)
			spi_engine_rx_next(spi_engine);
	पूर्ण

	वापस spi_engine->rx_length != 0;
पूर्ण

अटल irqवापस_t spi_engine_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा spi_master *master = devid;
	काष्ठा spi_engine *spi_engine = spi_master_get_devdata(master);
	अचिन्हित पूर्णांक disable_पूर्णांक = 0;
	अचिन्हित पूर्णांक pending;

	pending = पढ़ोl_relaxed(spi_engine->base + SPI_ENGINE_REG_INT_PENDING);

	अगर (pending & SPI_ENGINE_INT_SYNC) अणु
		ग_लिखोl_relaxed(SPI_ENGINE_INT_SYNC,
			spi_engine->base + SPI_ENGINE_REG_INT_PENDING);
		spi_engine->completed_id = पढ़ोl_relaxed(
			spi_engine->base + SPI_ENGINE_REG_SYNC_ID);
	पूर्ण

	spin_lock(&spi_engine->lock);

	अगर (pending & SPI_ENGINE_INT_CMD_ALMOST_EMPTY) अणु
		अगर (!spi_engine_ग_लिखो_cmd_fअगरo(spi_engine))
			disable_पूर्णांक |= SPI_ENGINE_INT_CMD_ALMOST_EMPTY;
	पूर्ण

	अगर (pending & SPI_ENGINE_INT_SDO_ALMOST_EMPTY) अणु
		अगर (!spi_engine_ग_लिखो_tx_fअगरo(spi_engine))
			disable_पूर्णांक |= SPI_ENGINE_INT_SDO_ALMOST_EMPTY;
	पूर्ण

	अगर (pending & (SPI_ENGINE_INT_SDI_ALMOST_FULL | SPI_ENGINE_INT_SYNC)) अणु
		अगर (!spi_engine_पढ़ो_rx_fअगरo(spi_engine))
			disable_पूर्णांक |= SPI_ENGINE_INT_SDI_ALMOST_FULL;
	पूर्ण

	अगर (pending & SPI_ENGINE_INT_SYNC) अणु
		अगर (spi_engine->msg &&
		    spi_engine->completed_id == spi_engine->sync_id) अणु
			काष्ठा spi_message *msg = spi_engine->msg;

			kमुक्त(spi_engine->p);
			msg->status = 0;
			msg->actual_length = msg->frame_length;
			spi_engine->msg = शून्य;
			spi_finalize_current_message(master);
			disable_पूर्णांक |= SPI_ENGINE_INT_SYNC;
		पूर्ण
	पूर्ण

	अगर (disable_पूर्णांक) अणु
		spi_engine->पूर्णांक_enable &= ~disable_पूर्णांक;
		ग_लिखोl_relaxed(spi_engine->पूर्णांक_enable,
			spi_engine->base + SPI_ENGINE_REG_INT_ENABLE);
	पूर्ण

	spin_unlock(&spi_engine->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक spi_engine_transfer_one_message(काष्ठा spi_master *master,
	काष्ठा spi_message *msg)
अणु
	काष्ठा spi_engine_program p_dry, *p;
	काष्ठा spi_engine *spi_engine = spi_master_get_devdata(master);
	अचिन्हित पूर्णांक पूर्णांक_enable = 0;
	अचिन्हित दीर्घ flags;
	माप_प्रकार size;

	p_dry.length = 0;
	spi_engine_compile_message(spi_engine, msg, true, &p_dry);

	size = माप(*p->inकाष्ठाions) * (p_dry.length + 1);
	p = kzalloc(माप(*p) + size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;
	spi_engine_compile_message(spi_engine, msg, false, p);

	spin_lock_irqsave(&spi_engine->lock, flags);
	spi_engine->sync_id = (spi_engine->sync_id + 1) & 0xff;
	spi_engine_program_add_cmd(p, false,
		SPI_ENGINE_CMD_SYNC(spi_engine->sync_id));

	spi_engine->msg = msg;
	spi_engine->p = p;

	spi_engine->cmd_buf = p->inकाष्ठाions;
	spi_engine->cmd_length = p->length;
	अगर (spi_engine_ग_लिखो_cmd_fअगरo(spi_engine))
		पूर्णांक_enable |= SPI_ENGINE_INT_CMD_ALMOST_EMPTY;

	spi_engine_tx_next(spi_engine);
	अगर (spi_engine_ग_लिखो_tx_fअगरo(spi_engine))
		पूर्णांक_enable |= SPI_ENGINE_INT_SDO_ALMOST_EMPTY;

	spi_engine_rx_next(spi_engine);
	अगर (spi_engine->rx_length != 0)
		पूर्णांक_enable |= SPI_ENGINE_INT_SDI_ALMOST_FULL;

	पूर्णांक_enable |= SPI_ENGINE_INT_SYNC;

	ग_लिखोl_relaxed(पूर्णांक_enable,
		spi_engine->base + SPI_ENGINE_REG_INT_ENABLE);
	spi_engine->पूर्णांक_enable = पूर्णांक_enable;
	spin_unlock_irqrestore(&spi_engine->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक spi_engine_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_engine *spi_engine;
	काष्ठा spi_master *master;
	अचिन्हित पूर्णांक version;
	पूर्णांक irq;
	पूर्णांक ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस -ENXIO;

	spi_engine = devm_kzalloc(&pdev->dev, माप(*spi_engine), GFP_KERNEL);
	अगर (!spi_engine)
		वापस -ENOMEM;

	master = spi_alloc_master(&pdev->dev, 0);
	अगर (!master)
		वापस -ENOMEM;

	spi_master_set_devdata(master, spi_engine);

	spin_lock_init(&spi_engine->lock);

	spi_engine->clk = devm_clk_get(&pdev->dev, "s_axi_aclk");
	अगर (IS_ERR(spi_engine->clk)) अणु
		ret = PTR_ERR(spi_engine->clk);
		जाओ err_put_master;
	पूर्ण

	spi_engine->ref_clk = devm_clk_get(&pdev->dev, "spi_clk");
	अगर (IS_ERR(spi_engine->ref_clk)) अणु
		ret = PTR_ERR(spi_engine->ref_clk);
		जाओ err_put_master;
	पूर्ण

	ret = clk_prepare_enable(spi_engine->clk);
	अगर (ret)
		जाओ err_put_master;

	ret = clk_prepare_enable(spi_engine->ref_clk);
	अगर (ret)
		जाओ err_clk_disable;

	spi_engine->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(spi_engine->base)) अणु
		ret = PTR_ERR(spi_engine->base);
		जाओ err_ref_clk_disable;
	पूर्ण

	version = पढ़ोl(spi_engine->base + SPI_ENGINE_REG_VERSION);
	अगर (SPI_ENGINE_VERSION_MAJOR(version) != 1) अणु
		dev_err(&pdev->dev, "Unsupported peripheral version %u.%u.%c\n",
			SPI_ENGINE_VERSION_MAJOR(version),
			SPI_ENGINE_VERSION_MINOR(version),
			SPI_ENGINE_VERSION_PATCH(version));
		ret = -ENODEV;
		जाओ err_ref_clk_disable;
	पूर्ण

	ग_लिखोl_relaxed(0x00, spi_engine->base + SPI_ENGINE_REG_RESET);
	ग_लिखोl_relaxed(0xff, spi_engine->base + SPI_ENGINE_REG_INT_PENDING);
	ग_लिखोl_relaxed(0x00, spi_engine->base + SPI_ENGINE_REG_INT_ENABLE);

	ret = request_irq(irq, spi_engine_irq, 0, pdev->name, master);
	अगर (ret)
		जाओ err_ref_clk_disable;

	master->dev.of_node = pdev->dev.of_node;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_3WIRE;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->max_speed_hz = clk_get_rate(spi_engine->ref_clk) / 2;
	master->transfer_one_message = spi_engine_transfer_one_message;
	master->num_chipselect = 8;

	ret = spi_रेजिस्टर_master(master);
	अगर (ret)
		जाओ err_मुक्त_irq;

	platक्रमm_set_drvdata(pdev, master);

	वापस 0;
err_मुक्त_irq:
	मुक्त_irq(irq, master);
err_ref_clk_disable:
	clk_disable_unprepare(spi_engine->ref_clk);
err_clk_disable:
	clk_disable_unprepare(spi_engine->clk);
err_put_master:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक spi_engine_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = spi_master_get(platक्रमm_get_drvdata(pdev));
	काष्ठा spi_engine *spi_engine = spi_master_get_devdata(master);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	spi_unरेजिस्टर_master(master);

	मुक्त_irq(irq, master);

	spi_master_put(master);

	ग_लिखोl_relaxed(0xff, spi_engine->base + SPI_ENGINE_REG_INT_PENDING);
	ग_लिखोl_relaxed(0x00, spi_engine->base + SPI_ENGINE_REG_INT_ENABLE);
	ग_लिखोl_relaxed(0x01, spi_engine->base + SPI_ENGINE_REG_RESET);

	clk_disable_unprepare(spi_engine->ref_clk);
	clk_disable_unprepare(spi_engine->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id spi_engine_match_table[] = अणु
	अणु .compatible = "adi,axi-spi-engine-1.00.a" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, spi_engine_match_table);

अटल काष्ठा platक्रमm_driver spi_engine_driver = अणु
	.probe = spi_engine_probe,
	.हटाओ = spi_engine_हटाओ,
	.driver = अणु
		.name = "spi-engine",
		.of_match_table = spi_engine_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(spi_engine_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices SPI engine peripheral driver");
MODULE_LICENSE("GPL");
