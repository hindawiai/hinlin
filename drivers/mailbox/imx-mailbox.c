<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 Pengutronix, Oleksij Rempel <o.rempel@pengutronix.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/firmware/imx/ipc.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

#घोषणा IMX_MU_xSR_GIPn(x)	BIT(28 + (3 - (x)))
#घोषणा IMX_MU_xSR_RFn(x)	BIT(24 + (3 - (x)))
#घोषणा IMX_MU_xSR_TEn(x)	BIT(20 + (3 - (x)))
#घोषणा IMX_MU_xSR_BRDIP	BIT(9)

/* General Purpose Interrupt Enable */
#घोषणा IMX_MU_xCR_GIEn(x)	BIT(28 + (3 - (x)))
/* Receive Interrupt Enable */
#घोषणा IMX_MU_xCR_RIEn(x)	BIT(24 + (3 - (x)))
/* Transmit Interrupt Enable */
#घोषणा IMX_MU_xCR_TIEn(x)	BIT(20 + (3 - (x)))
/* General Purpose Interrupt Request */
#घोषणा IMX_MU_xCR_GIRn(x)	BIT(16 + (3 - (x)))

#घोषणा IMX_MU_CHANS		16
/* TX0/RX0/RXDB[0-3] */
#घोषणा IMX_MU_SCU_CHANS	6
#घोषणा IMX_MU_CHAN_NAME_SIZE	20

क्रमागत imx_mu_chan_type अणु
	IMX_MU_TYPE_TX,		/* Tx */
	IMX_MU_TYPE_RX,		/* Rx */
	IMX_MU_TYPE_TXDB,	/* Tx करोorbell */
	IMX_MU_TYPE_RXDB,	/* Rx करोorbell */
पूर्ण;

काष्ठा imx_sc_rpc_msg_max अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u32 data[7];
पूर्ण;

काष्ठा imx_mu_con_priv अणु
	अचिन्हित पूर्णांक		idx;
	अक्षर			irq_desc[IMX_MU_CHAN_NAME_SIZE];
	क्रमागत imx_mu_chan_type	type;
	काष्ठा mbox_chan	*chan;
	काष्ठा tasklet_काष्ठा	txdb_tasklet;
पूर्ण;

काष्ठा imx_mu_priv अणु
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	spinlock_t		xcr_lock; /* control रेजिस्टर lock */

	काष्ठा mbox_controller	mbox;
	काष्ठा mbox_chan	mbox_chans[IMX_MU_CHANS];

	काष्ठा imx_mu_con_priv  con_priv[IMX_MU_CHANS];
	स्थिर काष्ठा imx_mu_dcfg	*dcfg;
	काष्ठा clk		*clk;
	पूर्णांक			irq;

	u32 xcr;

	bool			side_b;
पूर्ण;

काष्ठा imx_mu_dcfg अणु
	पूर्णांक (*tx)(काष्ठा imx_mu_priv *priv, काष्ठा imx_mu_con_priv *cp, व्योम *data);
	पूर्णांक (*rx)(काष्ठा imx_mu_priv *priv, काष्ठा imx_mu_con_priv *cp);
	व्योम (*init)(काष्ठा imx_mu_priv *priv);
	u32	xTR[4];		/* Transmit Registers */
	u32	xRR[4];		/* Receive Registers */
	u32	xSR;		/* Status Register */
	u32	xCR;		/* Control Register */
पूर्ण;

अटल काष्ठा imx_mu_priv *to_imx_mu_priv(काष्ठा mbox_controller *mbox)
अणु
	वापस container_of(mbox, काष्ठा imx_mu_priv, mbox);
पूर्ण

अटल व्योम imx_mu_ग_लिखो(काष्ठा imx_mu_priv *priv, u32 val, u32 offs)
अणु
	ioग_लिखो32(val, priv->base + offs);
पूर्ण

अटल u32 imx_mu_पढ़ो(काष्ठा imx_mu_priv *priv, u32 offs)
अणु
	वापस ioपढ़ो32(priv->base + offs);
पूर्ण

अटल u32 imx_mu_xcr_rmw(काष्ठा imx_mu_priv *priv, u32 set, u32 clr)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&priv->xcr_lock, flags);
	val = imx_mu_पढ़ो(priv, priv->dcfg->xCR);
	val &= ~clr;
	val |= set;
	imx_mu_ग_लिखो(priv, val, priv->dcfg->xCR);
	spin_unlock_irqrestore(&priv->xcr_lock, flags);

	वापस val;
पूर्ण

अटल पूर्णांक imx_mu_generic_tx(काष्ठा imx_mu_priv *priv,
			     काष्ठा imx_mu_con_priv *cp,
			     व्योम *data)
अणु
	u32 *arg = data;

	चयन (cp->type) अणु
	हाल IMX_MU_TYPE_TX:
		imx_mu_ग_लिखो(priv, *arg, priv->dcfg->xTR[cp->idx]);
		imx_mu_xcr_rmw(priv, IMX_MU_xCR_TIEn(cp->idx), 0);
		अवरोध;
	हाल IMX_MU_TYPE_TXDB:
		imx_mu_xcr_rmw(priv, IMX_MU_xCR_GIRn(cp->idx), 0);
		tasklet_schedule(&cp->txdb_tasklet);
		अवरोध;
	शेष:
		dev_warn_ratelimited(priv->dev, "Send data on wrong channel type: %d\n", cp->type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx_mu_generic_rx(काष्ठा imx_mu_priv *priv,
			     काष्ठा imx_mu_con_priv *cp)
अणु
	u32 dat;

	dat = imx_mu_पढ़ो(priv, priv->dcfg->xRR[cp->idx]);
	mbox_chan_received_data(cp->chan, (व्योम *)&dat);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_mu_scu_tx(काष्ठा imx_mu_priv *priv,
			 काष्ठा imx_mu_con_priv *cp,
			 व्योम *data)
अणु
	काष्ठा imx_sc_rpc_msg_max *msg = data;
	u32 *arg = data;
	पूर्णांक i, ret;
	u32 xsr;

	चयन (cp->type) अणु
	हाल IMX_MU_TYPE_TX:
		/*
		 * msg->hdr.size specअगरies the number of u32 words जबतक
		 * माप yields bytes.
		 */

		अगर (msg->hdr.size > माप(*msg) / 4) अणु
			/*
			 * The real message size can be dअगरferent to
			 * काष्ठा imx_sc_rpc_msg_max size
			 */
			dev_err(priv->dev, "Maximal message size (%zu bytes) exceeded on TX; got: %i bytes\n", माप(*msg), msg->hdr.size << 2);
			वापस -EINVAL;
		पूर्ण

		क्रम (i = 0; i < 4 && i < msg->hdr.size; i++)
			imx_mu_ग_लिखो(priv, *arg++, priv->dcfg->xTR[i % 4]);
		क्रम (; i < msg->hdr.size; i++) अणु
			ret = पढ़ोl_poll_समयout(priv->base + priv->dcfg->xSR,
						 xsr,
						 xsr & IMX_MU_xSR_TEn(i % 4),
						 0, 100);
			अगर (ret) अणु
				dev_err(priv->dev, "Send data index: %d timeout\n", i);
				वापस ret;
			पूर्ण
			imx_mu_ग_लिखो(priv, *arg++, priv->dcfg->xTR[i % 4]);
		पूर्ण

		imx_mu_xcr_rmw(priv, IMX_MU_xCR_TIEn(cp->idx), 0);
		अवरोध;
	शेष:
		dev_warn_ratelimited(priv->dev, "Send data on wrong channel type: %d\n", cp->type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx_mu_scu_rx(काष्ठा imx_mu_priv *priv,
			 काष्ठा imx_mu_con_priv *cp)
अणु
	काष्ठा imx_sc_rpc_msg_max msg;
	u32 *data = (u32 *)&msg;
	पूर्णांक i, ret;
	u32 xsr;

	imx_mu_xcr_rmw(priv, 0, IMX_MU_xCR_RIEn(0));
	*data++ = imx_mu_पढ़ो(priv, priv->dcfg->xRR[0]);

	अगर (msg.hdr.size > माप(msg) / 4) अणु
		dev_err(priv->dev, "Maximal message size (%zu bytes) exceeded on RX; got: %i bytes\n", माप(msg), msg.hdr.size << 2);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 1; i < msg.hdr.size; i++) अणु
		ret = पढ़ोl_poll_समयout(priv->base + priv->dcfg->xSR, xsr,
					 xsr & IMX_MU_xSR_RFn(i % 4), 0, 100);
		अगर (ret) अणु
			dev_err(priv->dev, "timeout read idx %d\n", i);
			वापस ret;
		पूर्ण
		*data++ = imx_mu_पढ़ो(priv, priv->dcfg->xRR[i % 4]);
	पूर्ण

	imx_mu_xcr_rmw(priv, IMX_MU_xCR_RIEn(0), 0);
	mbox_chan_received_data(cp->chan, (व्योम *)&msg);

	वापस 0;
पूर्ण

अटल व्योम imx_mu_txdb_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा imx_mu_con_priv *cp = (काष्ठा imx_mu_con_priv *)data;

	mbox_chan_txकरोne(cp->chan, 0);
पूर्ण

अटल irqवापस_t imx_mu_isr(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा mbox_chan *chan = p;
	काष्ठा imx_mu_priv *priv = to_imx_mu_priv(chan->mbox);
	काष्ठा imx_mu_con_priv *cp = chan->con_priv;
	u32 val, ctrl;

	ctrl = imx_mu_पढ़ो(priv, priv->dcfg->xCR);
	val = imx_mu_पढ़ो(priv, priv->dcfg->xSR);

	चयन (cp->type) अणु
	हाल IMX_MU_TYPE_TX:
		val &= IMX_MU_xSR_TEn(cp->idx) &
			(ctrl & IMX_MU_xCR_TIEn(cp->idx));
		अवरोध;
	हाल IMX_MU_TYPE_RX:
		val &= IMX_MU_xSR_RFn(cp->idx) &
			(ctrl & IMX_MU_xCR_RIEn(cp->idx));
		अवरोध;
	हाल IMX_MU_TYPE_RXDB:
		val &= IMX_MU_xSR_GIPn(cp->idx) &
			(ctrl & IMX_MU_xCR_GIEn(cp->idx));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!val)
		वापस IRQ_NONE;

	अगर (val == IMX_MU_xSR_TEn(cp->idx)) अणु
		imx_mu_xcr_rmw(priv, 0, IMX_MU_xCR_TIEn(cp->idx));
		mbox_chan_txकरोne(chan, 0);
	पूर्ण अन्यथा अगर (val == IMX_MU_xSR_RFn(cp->idx)) अणु
		priv->dcfg->rx(priv, cp);
	पूर्ण अन्यथा अगर (val == IMX_MU_xSR_GIPn(cp->idx)) अणु
		imx_mu_ग_लिखो(priv, IMX_MU_xSR_GIPn(cp->idx), priv->dcfg->xSR);
		mbox_chan_received_data(chan, शून्य);
	पूर्ण अन्यथा अणु
		dev_warn_ratelimited(priv->dev, "Not handled interrupt\n");
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक imx_mu_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा imx_mu_priv *priv = to_imx_mu_priv(chan->mbox);
	काष्ठा imx_mu_con_priv *cp = chan->con_priv;

	वापस priv->dcfg->tx(priv, cp, data);
पूर्ण

अटल पूर्णांक imx_mu_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा imx_mu_priv *priv = to_imx_mu_priv(chan->mbox);
	काष्ठा imx_mu_con_priv *cp = chan->con_priv;
	अचिन्हित दीर्घ irq_flag = IRQF_SHARED;
	पूर्णांक ret;

	pm_runसमय_get_sync(priv->dev);
	अगर (cp->type == IMX_MU_TYPE_TXDB) अणु
		/* Tx करोorbell करोn't have ACK support */
		tasklet_init(&cp->txdb_tasklet, imx_mu_txdb_tasklet,
			     (अचिन्हित दीर्घ)cp);
		वापस 0;
	पूर्ण

	/* IPC MU should be with IRQF_NO_SUSPEND set */
	अगर (!priv->dev->pm_करोमुख्य)
		irq_flag |= IRQF_NO_SUSPEND;

	ret = request_irq(priv->irq, imx_mu_isr, irq_flag,
			  cp->irq_desc, chan);
	अगर (ret) अणु
		dev_err(priv->dev,
			"Unable to acquire IRQ %d\n", priv->irq);
		वापस ret;
	पूर्ण

	चयन (cp->type) अणु
	हाल IMX_MU_TYPE_RX:
		imx_mu_xcr_rmw(priv, IMX_MU_xCR_RIEn(cp->idx), 0);
		अवरोध;
	हाल IMX_MU_TYPE_RXDB:
		imx_mu_xcr_rmw(priv, IMX_MU_xCR_GIEn(cp->idx), 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम imx_mu_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा imx_mu_priv *priv = to_imx_mu_priv(chan->mbox);
	काष्ठा imx_mu_con_priv *cp = chan->con_priv;

	अगर (cp->type == IMX_MU_TYPE_TXDB) अणु
		tasklet_समाप्त(&cp->txdb_tasklet);
		pm_runसमय_put_sync(priv->dev);
		वापस;
	पूर्ण

	चयन (cp->type) अणु
	हाल IMX_MU_TYPE_TX:
		imx_mu_xcr_rmw(priv, 0, IMX_MU_xCR_TIEn(cp->idx));
		अवरोध;
	हाल IMX_MU_TYPE_RX:
		imx_mu_xcr_rmw(priv, 0, IMX_MU_xCR_RIEn(cp->idx));
		अवरोध;
	हाल IMX_MU_TYPE_RXDB:
		imx_mu_xcr_rmw(priv, 0, IMX_MU_xCR_GIEn(cp->idx));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	मुक्त_irq(priv->irq, chan);
	pm_runसमय_put_sync(priv->dev);
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops imx_mu_ops = अणु
	.send_data = imx_mu_send_data,
	.startup = imx_mu_startup,
	.shutकरोwn = imx_mu_shutकरोwn,
पूर्ण;

अटल काष्ठा mbox_chan *imx_mu_scu_xlate(काष्ठा mbox_controller *mbox,
					  स्थिर काष्ठा of_phandle_args *sp)
अणु
	u32 type, idx, chan;

	अगर (sp->args_count != 2) अणु
		dev_err(mbox->dev, "Invalid argument count %d\n", sp->args_count);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	type = sp->args[0]; /* channel type */
	idx = sp->args[1]; /* index */

	चयन (type) अणु
	हाल IMX_MU_TYPE_TX:
	हाल IMX_MU_TYPE_RX:
		अगर (idx != 0)
			dev_err(mbox->dev, "Invalid chan idx: %d\n", idx);
		chan = type;
		अवरोध;
	हाल IMX_MU_TYPE_RXDB:
		chan = 2 + idx;
		अवरोध;
	शेष:
		dev_err(mbox->dev, "Invalid chan type: %d\n", type);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (chan >= mbox->num_chans) अणु
		dev_err(mbox->dev, "Not supported channel number: %d. (type: %d, idx: %d)\n", chan, type, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस &mbox->chans[chan];
पूर्ण

अटल काष्ठा mbox_chan * imx_mu_xlate(काष्ठा mbox_controller *mbox,
				       स्थिर काष्ठा of_phandle_args *sp)
अणु
	u32 type, idx, chan;

	अगर (sp->args_count != 2) अणु
		dev_err(mbox->dev, "Invalid argument count %d\n", sp->args_count);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	type = sp->args[0]; /* channel type */
	idx = sp->args[1]; /* index */
	chan = type * 4 + idx;

	अगर (chan >= mbox->num_chans) अणु
		dev_err(mbox->dev, "Not supported channel number: %d. (type: %d, idx: %d)\n", chan, type, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस &mbox->chans[chan];
पूर्ण

अटल व्योम imx_mu_init_generic(काष्ठा imx_mu_priv *priv)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IMX_MU_CHANS; i++) अणु
		काष्ठा imx_mu_con_priv *cp = &priv->con_priv[i];

		cp->idx = i % 4;
		cp->type = i >> 2;
		cp->chan = &priv->mbox_chans[i];
		priv->mbox_chans[i].con_priv = cp;
		snम_लिखो(cp->irq_desc, माप(cp->irq_desc),
			 "imx_mu_chan[%i-%i]", cp->type, cp->idx);
	पूर्ण

	priv->mbox.num_chans = IMX_MU_CHANS;
	priv->mbox.of_xlate = imx_mu_xlate;

	अगर (priv->side_b)
		वापस;

	/* Set शेष MU configuration */
	imx_mu_ग_लिखो(priv, 0, priv->dcfg->xCR);
पूर्ण

अटल व्योम imx_mu_init_scu(काष्ठा imx_mu_priv *priv)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IMX_MU_SCU_CHANS; i++) अणु
		काष्ठा imx_mu_con_priv *cp = &priv->con_priv[i];

		cp->idx = i < 2 ? 0 : i - 2;
		cp->type = i < 2 ? i : IMX_MU_TYPE_RXDB;
		cp->chan = &priv->mbox_chans[i];
		priv->mbox_chans[i].con_priv = cp;
		snम_लिखो(cp->irq_desc, माप(cp->irq_desc),
			 "imx_mu_chan[%i-%i]", cp->type, cp->idx);
	पूर्ण

	priv->mbox.num_chans = IMX_MU_SCU_CHANS;
	priv->mbox.of_xlate = imx_mu_scu_xlate;

	/* Set शेष MU configuration */
	imx_mu_ग_लिखो(priv, 0, priv->dcfg->xCR);
पूर्ण

अटल पूर्णांक imx_mu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा imx_mu_priv *priv;
	स्थिर काष्ठा imx_mu_dcfg *dcfg;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->irq = platक्रमm_get_irq(pdev, 0);
	अगर (priv->irq < 0)
		वापस priv->irq;

	dcfg = of_device_get_match_data(dev);
	अगर (!dcfg)
		वापस -EINVAL;
	priv->dcfg = dcfg;

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		अगर (PTR_ERR(priv->clk) != -ENOENT)
			वापस PTR_ERR(priv->clk);

		priv->clk = शून्य;
	पूर्ण

	ret = clk_prepare_enable(priv->clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable clock\n");
		वापस ret;
	पूर्ण

	priv->side_b = of_property_पढ़ो_bool(np, "fsl,mu-side-b");

	priv->dcfg->init(priv);

	spin_lock_init(&priv->xcr_lock);

	priv->mbox.dev = dev;
	priv->mbox.ops = &imx_mu_ops;
	priv->mbox.chans = priv->mbox_chans;
	priv->mbox.txकरोne_irq = true;

	platक्रमm_set_drvdata(pdev, priv);

	ret = devm_mbox_controller_रेजिस्टर(dev, &priv->mbox);
	अगर (ret) अणु
		clk_disable_unprepare(priv->clk);
		वापस ret;
	पूर्ण

	pm_runसमय_enable(dev);

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		जाओ disable_runसमय_pm;
	पूर्ण

	ret = pm_runसमय_put_sync(dev);
	अगर (ret < 0)
		जाओ disable_runसमय_pm;

	clk_disable_unprepare(priv->clk);

	वापस 0;

disable_runसमय_pm:
	pm_runसमय_disable(dev);
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक imx_mu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_mu_priv *priv = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(priv->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा imx_mu_dcfg imx_mu_cfg_imx6sx = अणु
	.tx	= imx_mu_generic_tx,
	.rx	= imx_mu_generic_rx,
	.init	= imx_mu_init_generic,
	.xTR	= अणु0x0, 0x4, 0x8, 0xcपूर्ण,
	.xRR	= अणु0x10, 0x14, 0x18, 0x1cपूर्ण,
	.xSR	= 0x20,
	.xCR	= 0x24,
पूर्ण;

अटल स्थिर काष्ठा imx_mu_dcfg imx_mu_cfg_imx7ulp = अणु
	.tx	= imx_mu_generic_tx,
	.rx	= imx_mu_generic_rx,
	.init	= imx_mu_init_generic,
	.xTR	= अणु0x20, 0x24, 0x28, 0x2cपूर्ण,
	.xRR	= अणु0x40, 0x44, 0x48, 0x4cपूर्ण,
	.xSR	= 0x60,
	.xCR	= 0x64,
पूर्ण;

अटल स्थिर काष्ठा imx_mu_dcfg imx_mu_cfg_imx8_scu = अणु
	.tx	= imx_mu_scu_tx,
	.rx	= imx_mu_scu_rx,
	.init	= imx_mu_init_scu,
	.xTR	= अणु0x0, 0x4, 0x8, 0xcपूर्ण,
	.xRR	= अणु0x10, 0x14, 0x18, 0x1cपूर्ण,
	.xSR	= 0x20,
	.xCR	= 0x24,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_mu_dt_ids[] = अणु
	अणु .compatible = "fsl,imx7ulp-mu", .data = &imx_mu_cfg_imx7ulp पूर्ण,
	अणु .compatible = "fsl,imx6sx-mu", .data = &imx_mu_cfg_imx6sx पूर्ण,
	अणु .compatible = "fsl,imx8-mu-scu", .data = &imx_mu_cfg_imx8_scu पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_mu_dt_ids);

अटल पूर्णांक __maybe_unused imx_mu_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा imx_mu_priv *priv = dev_get_drvdata(dev);

	अगर (!priv->clk)
		priv->xcr = imx_mu_पढ़ो(priv, priv->dcfg->xCR);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_mu_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा imx_mu_priv *priv = dev_get_drvdata(dev);

	/*
	 * ONLY restore MU when context lost, the TIE could
	 * be set during noirq resume as there is MU data
	 * communication going on, and restore the saved
	 * value will overग_लिखो the TIE and cause MU data
	 * send failed, may lead to प्रणाली मुक्तze. This issue
	 * is observed by testing मुक्तze mode suspend.
	 */
	अगर (!imx_mu_पढ़ो(priv, priv->dcfg->xCR) && !priv->clk)
		imx_mu_ग_लिखो(priv, priv->xcr, priv->dcfg->xCR);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_mu_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा imx_mu_priv *priv = dev_get_drvdata(dev);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_mu_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा imx_mu_priv *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		dev_err(dev, "failed to enable clock\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops imx_mu_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(imx_mu_suspend_noirq,
				      imx_mu_resume_noirq)
	SET_RUNTIME_PM_OPS(imx_mu_runसमय_suspend,
			   imx_mu_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver imx_mu_driver = अणु
	.probe		= imx_mu_probe,
	.हटाओ		= imx_mu_हटाओ,
	.driver = अणु
		.name	= "imx_mu",
		.of_match_table = imx_mu_dt_ids,
		.pm = &imx_mu_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx_mu_driver);

MODULE_AUTHOR("Oleksij Rempel <o.rempel@pengutronix.de>");
MODULE_DESCRIPTION("Message Unit driver for i.MX");
MODULE_LICENSE("GPL v2");
