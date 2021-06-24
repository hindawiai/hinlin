<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// RPC-IF SPI/QSPI/Octa driver
//
// Copyright (C) 2018 ~ 2019 Renesas Solutions Corp.
// Copyright (C) 2019 Macronix International Co., Ltd.
// Copyright (C) 2019 - 2020 Cogent Embedded, Inc.
//

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>

#समावेश <memory/renesas-rpc-अगर.h>

#समावेश <यंत्र/unaligned.h>

अटल व्योम rpcअगर_spi_mem_prepare(काष्ठा spi_device *spi_dev,
				  स्थिर काष्ठा spi_mem_op *spi_op,
				  u64 *offs, माप_प्रकार *len)
अणु
	काष्ठा rpcअगर *rpc = spi_controller_get_devdata(spi_dev->controller);
	काष्ठा rpcअगर_op rpc_op = अणु पूर्ण;

	rpc_op.cmd.opcode = spi_op->cmd.opcode;
	rpc_op.cmd.buswidth = spi_op->cmd.buswidth;

	अगर (spi_op->addr.nbytes) अणु
		rpc_op.addr.buswidth = spi_op->addr.buswidth;
		rpc_op.addr.nbytes = spi_op->addr.nbytes;
		rpc_op.addr.val = spi_op->addr.val;
	पूर्ण

	अगर (spi_op->dummy.nbytes) अणु
		rpc_op.dummy.buswidth = spi_op->dummy.buswidth;
		rpc_op.dummy.ncycles  = spi_op->dummy.nbytes * 8 /
					spi_op->dummy.buswidth;
	पूर्ण

	अगर (spi_op->data.nbytes || (offs && len)) अणु
		rpc_op.data.buswidth = spi_op->data.buswidth;
		rpc_op.data.nbytes = spi_op->data.nbytes;
		चयन (spi_op->data.dir) अणु
		हाल SPI_MEM_DATA_IN:
			rpc_op.data.dir = RPCIF_DATA_IN;
			rpc_op.data.buf.in = spi_op->data.buf.in;
			अवरोध;
		हाल SPI_MEM_DATA_OUT:
			rpc_op.data.dir = RPCIF_DATA_OUT;
			rpc_op.data.buf.out = spi_op->data.buf.out;
			अवरोध;
		हाल SPI_MEM_NO_DATA:
			rpc_op.data.dir = RPCIF_NO_DATA;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा	अणु
		rpc_op.data.dir = RPCIF_NO_DATA;
	पूर्ण

	rpcअगर_prepare(rpc, &rpc_op, offs, len);
पूर्ण

अटल bool rpcअगर_spi_mem_supports_op(काष्ठा spi_mem *mem,
				      स्थिर काष्ठा spi_mem_op *op)
अणु
	अगर (!spi_mem_शेष_supports_op(mem, op))
		वापस false;

	अगर (op->data.buswidth > 4 || op->addr.buswidth > 4 ||
	    op->dummy.buswidth > 4 || op->cmd.buswidth > 4 ||
	    op->addr.nbytes > 4)
		वापस false;

	वापस true;
पूर्ण

अटल sमाप_प्रकार rpcअगर_spi_mem_dirmap_पढ़ो(काष्ठा spi_mem_dirmap_desc *desc,
					 u64 offs, माप_प्रकार len, व्योम *buf)
अणु
	काष्ठा rpcअगर *rpc =
		spi_controller_get_devdata(desc->mem->spi->controller);

	अगर (offs + desc->info.offset + len > U32_MAX)
		वापस -EINVAL;

	rpcअगर_spi_mem_prepare(desc->mem->spi, &desc->info.op_पंचांगpl, &offs, &len);

	वापस rpcअगर_dirmap_पढ़ो(rpc, offs, len, buf);
पूर्ण

अटल पूर्णांक rpcअगर_spi_mem_dirmap_create(काष्ठा spi_mem_dirmap_desc *desc)
अणु
	काष्ठा rpcअगर *rpc =
		spi_controller_get_devdata(desc->mem->spi->controller);

	अगर (desc->info.offset + desc->info.length > U32_MAX)
		वापस -ENOTSUPP;

	अगर (!rpcअगर_spi_mem_supports_op(desc->mem, &desc->info.op_पंचांगpl))
		वापस -ENOTSUPP;

	अगर (!rpc->dirmap && desc->info.op_पंचांगpl.data.dir == SPI_MEM_DATA_IN)
		वापस -ENOTSUPP;

	अगर (desc->info.op_पंचांगpl.data.dir == SPI_MEM_DATA_OUT)
		वापस -ENOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक rpcअगर_spi_mem_exec_op(काष्ठा spi_mem *mem,
				 स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा rpcअगर *rpc =
		spi_controller_get_devdata(mem->spi->controller);

	rpcअगर_spi_mem_prepare(mem->spi, op, शून्य, शून्य);

	वापस rpcअगर_manual_xfer(rpc);
पूर्ण

अटल स्थिर काष्ठा spi_controller_mem_ops rpcअगर_spi_mem_ops = अणु
	.supports_op	= rpcअगर_spi_mem_supports_op,
	.exec_op	= rpcअगर_spi_mem_exec_op,
	.dirmap_create	= rpcअगर_spi_mem_dirmap_create,
	.dirmap_पढ़ो	= rpcअगर_spi_mem_dirmap_पढ़ो,
पूर्ण;

अटल पूर्णांक rpcअगर_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *parent = pdev->dev.parent;
	काष्ठा spi_controller *ctlr;
	काष्ठा rpcअगर *rpc;
	पूर्णांक error;

	ctlr = devm_spi_alloc_master(&pdev->dev, माप(*rpc));
	अगर (!ctlr)
		वापस -ENOMEM;

	rpc = spi_controller_get_devdata(ctlr);
	rpcअगर_sw_init(rpc, parent);

	platक्रमm_set_drvdata(pdev, ctlr);

	ctlr->dev.of_node = parent->of_node;

	rpcअगर_enable_rpm(rpc);

	ctlr->num_chipselect = 1;
	ctlr->mem_ops = &rpcअगर_spi_mem_ops;

	ctlr->bits_per_word_mask = SPI_BPW_MASK(8);
	ctlr->mode_bits = SPI_CPOL | SPI_CPHA | SPI_TX_QUAD | SPI_RX_QUAD;
	ctlr->flags = SPI_CONTROLLER_HALF_DUPLEX;

	rpcअगर_hw_init(rpc, false);

	error = spi_रेजिस्टर_controller(ctlr);
	अगर (error) अणु
		dev_err(&pdev->dev, "spi_register_controller failed\n");
		rpcअगर_disable_rpm(rpc);
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक rpcअगर_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctlr = platक्रमm_get_drvdata(pdev);
	काष्ठा rpcअगर *rpc = spi_controller_get_devdata(ctlr);

	spi_unरेजिस्टर_controller(ctlr);
	rpcअगर_disable_rpm(rpc);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rpcअगर_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctlr = dev_get_drvdata(dev);

	वापस spi_controller_suspend(ctlr);
पूर्ण

अटल पूर्णांक __maybe_unused rpcअगर_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctlr = dev_get_drvdata(dev);

	वापस spi_controller_resume(ctlr);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rpcअगर_spi_pm_ops, rpcअगर_spi_suspend, rpcअगर_spi_resume);

अटल काष्ठा platक्रमm_driver rpcअगर_spi_driver = अणु
	.probe	= rpcअगर_spi_probe,
	.हटाओ	= rpcअगर_spi_हटाओ,
	.driver = अणु
		.name	= "rpc-if-spi",
#अगर_घोषित CONFIG_PM_SLEEP
		.pm	= &rpcअगर_spi_pm_ops,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rpcअगर_spi_driver);

MODULE_DESCRIPTION("Renesas RPC-IF SPI driver");
MODULE_LICENSE("GPL v2");
