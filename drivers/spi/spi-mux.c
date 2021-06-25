<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// General Purpose SPI multiplexer

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mux/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>

#घोषणा SPI_MUX_NO_CS	((अचिन्हित पूर्णांक)-1)

/**
 * DOC: Driver description
 *
 * This driver supports a MUX on an SPI bus. This can be useful when you need
 * more chip selects than the hardware peripherals support, or than are
 * available in a particular board setup.
 *
 * The driver will create an additional SPI controller. Devices added under the
 * mux will be handled as 'chip selects' on this controller.
 */

/**
 * काष्ठा spi_mux_priv - the basic spi_mux काष्ठाure
 * @spi:		poपूर्णांकer to the device काष्ठा attached to the parent
 *			spi controller
 * @current_cs:		The current chip select set in the mux
 * @child_msg_complete: The mux replaces the complete callback in the child's
 *			message to its own callback; this field is used by the
 *			driver to store the child's callback during a transfer
 * @child_msg_context:	Used to store the child's context to the callback
 * @child_msg_dev:	Used to store the spi_device poपूर्णांकer to the child
 * @mux:		mux_control काष्ठाure used to provide chip selects क्रम
 *			करोwnstream spi devices
 */
काष्ठा spi_mux_priv अणु
	काष्ठा spi_device	*spi;
	अचिन्हित पूर्णांक		current_cs;

	व्योम			(*child_msg_complete)(व्योम *context);
	व्योम			*child_msg_context;
	काष्ठा spi_device	*child_msg_dev;
	काष्ठा mux_control	*mux;
पूर्ण;

/* should not get called when the parent controller is करोing a transfer */
अटल पूर्णांक spi_mux_select(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_mux_priv *priv = spi_controller_get_devdata(spi->controller);
	पूर्णांक ret;

	ret = mux_control_select(priv->mux, spi->chip_select);
	अगर (ret)
		वापस ret;

	अगर (priv->current_cs == spi->chip_select)
		वापस 0;

	dev_dbg(&priv->spi->dev, "setting up the mux for cs %d\n",
		spi->chip_select);

	/* copy the child device's settings except क्रम the cs */
	priv->spi->max_speed_hz = spi->max_speed_hz;
	priv->spi->mode = spi->mode;
	priv->spi->bits_per_word = spi->bits_per_word;

	priv->current_cs = spi->chip_select;

	वापस 0;
पूर्ण

अटल पूर्णांक spi_mux_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_mux_priv *priv = spi_controller_get_devdata(spi->controller);

	/*
	 * can be called multiple बार, won't करो a valid setup now but we will
	 * change the settings when we करो a transfer (necessary because we
	 * can't predict from which device it will be anyway)
	 */
	वापस spi_setup(priv->spi);
पूर्ण

अटल व्योम spi_mux_complete_cb(व्योम *context)
अणु
	काष्ठा spi_mux_priv *priv = (काष्ठा spi_mux_priv *)context;
	काष्ठा spi_controller *ctlr = spi_get_drvdata(priv->spi);
	काष्ठा spi_message *m = ctlr->cur_msg;

	m->complete = priv->child_msg_complete;
	m->context = priv->child_msg_context;
	m->spi = priv->child_msg_dev;
	spi_finalize_current_message(ctlr);
	mux_control_deselect(priv->mux);
पूर्ण

अटल पूर्णांक spi_mux_transfer_one_message(काष्ठा spi_controller *ctlr,
						काष्ठा spi_message *m)
अणु
	काष्ठा spi_mux_priv *priv = spi_controller_get_devdata(ctlr);
	काष्ठा spi_device *spi = m->spi;
	पूर्णांक ret;

	ret = spi_mux_select(spi);
	अगर (ret)
		वापस ret;

	/*
	 * Replace the complete callback, context and spi_device with our own
	 * poपूर्णांकers. Save originals
	 */
	priv->child_msg_complete = m->complete;
	priv->child_msg_context = m->context;
	priv->child_msg_dev = m->spi;

	m->complete = spi_mux_complete_cb;
	m->context = priv;
	m->spi = priv->spi;

	/* करो the transfer */
	वापस spi_async(priv->spi, m);
पूर्ण

अटल पूर्णांक spi_mux_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_controller *ctlr;
	काष्ठा spi_mux_priv *priv;
	पूर्णांक ret;

	ctlr = spi_alloc_master(&spi->dev, माप(*priv));
	अगर (!ctlr)
		वापस -ENOMEM;

	spi_set_drvdata(spi, ctlr);
	priv = spi_controller_get_devdata(ctlr);
	priv->spi = spi;

	priv->mux = devm_mux_control_get(&spi->dev, शून्य);
	अगर (IS_ERR(priv->mux)) अणु
		ret = dev_err_probe(&spi->dev, PTR_ERR(priv->mux),
				    "failed to get control-mux\n");
		जाओ err_put_ctlr;
	पूर्ण

	priv->current_cs = SPI_MUX_NO_CS;

	/* supported modes are the same as our parent's */
	ctlr->mode_bits = spi->controller->mode_bits;
	ctlr->flags = spi->controller->flags;
	ctlr->transfer_one_message = spi_mux_transfer_one_message;
	ctlr->setup = spi_mux_setup;
	ctlr->num_chipselect = mux_control_states(priv->mux);
	ctlr->bus_num = -1;
	ctlr->dev.of_node = spi->dev.of_node;

	ret = devm_spi_रेजिस्टर_controller(&spi->dev, ctlr);
	अगर (ret)
		जाओ err_put_ctlr;

	वापस 0;

err_put_ctlr:
	spi_controller_put(ctlr);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id spi_mux_of_match[] = अणु
	अणु .compatible = "spi-mux" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा spi_driver spi_mux_driver = अणु
	.probe  = spi_mux_probe,
	.driver = अणु
		.name   = "spi-mux",
		.of_match_table = spi_mux_of_match,
	पूर्ण,
पूर्ण;

module_spi_driver(spi_mux_driver);

MODULE_DESCRIPTION("SPI multiplexer");
MODULE_LICENSE("GPL");
