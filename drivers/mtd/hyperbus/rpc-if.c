<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Linux driver क्रम RPC-IF HyperFlash
 *
 * Copyright (C) 2019-2020 Cogent Embedded, Inc.
 */

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/hyperbus.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mux/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

#समावेश <memory/renesas-rpc-अगर.h>

काष्ठा	rpcअगर_hyperbus अणु
	काष्ठा rpcअगर rpc;
	काष्ठा hyperbus_ctlr ctlr;
	काष्ठा hyperbus_device hbdev;
पूर्ण;

अटल स्थिर काष्ठा rpcअगर_op rpcअगर_op_पंचांगpl = अणु
	.cmd = अणु
		.buswidth = 8,
		.ddr = true,
	पूर्ण,
	.ocmd = अणु
		.buswidth = 8,
		.ddr = true,
	पूर्ण,
	.addr = अणु
		.nbytes = 1,
		.buswidth = 8,
		.ddr = true,
	पूर्ण,
	.data = अणु
		.buswidth = 8,
		.ddr = true,
	पूर्ण,
पूर्ण;

अटल व्योम rpcअगर_hb_prepare_पढ़ो(काष्ठा rpcअगर *rpc, व्योम *to,
				  अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	काष्ठा rpcअगर_op op = rpcअगर_op_पंचांगpl;

	op.cmd.opcode = HYPERBUS_RW_READ | HYPERBUS_AS_MEM;
	op.addr.val = from >> 1;
	op.dummy.buswidth = 1;
	op.dummy.ncycles = 15;
	op.data.dir = RPCIF_DATA_IN;
	op.data.nbytes = len;
	op.data.buf.in = to;

	rpcअगर_prepare(rpc, &op, शून्य, शून्य);
पूर्ण

अटल व्योम rpcअगर_hb_prepare_ग_लिखो(काष्ठा rpcअगर *rpc, अचिन्हित दीर्घ to,
				   व्योम *from, sमाप_प्रकार len)
अणु
	काष्ठा rpcअगर_op op = rpcअगर_op_पंचांगpl;

	op.cmd.opcode = HYPERBUS_RW_WRITE | HYPERBUS_AS_MEM;
	op.addr.val = to >> 1;
	op.data.dir = RPCIF_DATA_OUT;
	op.data.nbytes = len;
	op.data.buf.out = from;

	rpcअगर_prepare(rpc, &op, शून्य, शून्य);
पूर्ण

अटल u16 rpcअगर_hb_पढ़ो16(काष्ठा hyperbus_device *hbdev, अचिन्हित दीर्घ addr)
अणु
	काष्ठा rpcअगर_hyperbus *hyperbus =
		container_of(hbdev, काष्ठा rpcअगर_hyperbus, hbdev);
	map_word data;

	rpcअगर_hb_prepare_पढ़ो(&hyperbus->rpc, &data, addr, 2);

	rpcअगर_manual_xfer(&hyperbus->rpc);

	वापस data.x[0];
पूर्ण

अटल व्योम rpcअगर_hb_ग_लिखो16(काष्ठा hyperbus_device *hbdev, अचिन्हित दीर्घ addr,
			     u16 data)
अणु
	काष्ठा rpcअगर_hyperbus *hyperbus =
		container_of(hbdev, काष्ठा rpcअगर_hyperbus, hbdev);

	rpcअगर_hb_prepare_ग_लिखो(&hyperbus->rpc, addr, &data, 2);

	rpcअगर_manual_xfer(&hyperbus->rpc);
पूर्ण

अटल व्योम rpcअगर_hb_copy_from(काष्ठा hyperbus_device *hbdev, व्योम *to,
			       अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	काष्ठा rpcअगर_hyperbus *hyperbus =
		container_of(hbdev, काष्ठा rpcअगर_hyperbus, hbdev);

	rpcअगर_hb_prepare_पढ़ो(&hyperbus->rpc, to, from, len);

	rpcअगर_dirmap_पढ़ो(&hyperbus->rpc, from, len, to);
पूर्ण

अटल स्थिर काष्ठा hyperbus_ops rpcअगर_hb_ops = अणु
	.पढ़ो16 = rpcअगर_hb_पढ़ो16,
	.ग_लिखो16 = rpcअगर_hb_ग_लिखो16,
	.copy_from = rpcअगर_hb_copy_from,
पूर्ण;

अटल पूर्णांक rpcअगर_hb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rpcअगर_hyperbus *hyperbus;
	पूर्णांक error;

	hyperbus = devm_kzalloc(dev, माप(*hyperbus), GFP_KERNEL);
	अगर (!hyperbus)
		वापस -ENOMEM;

	rpcअगर_sw_init(&hyperbus->rpc, pdev->dev.parent);

	platक्रमm_set_drvdata(pdev, hyperbus);

	rpcअगर_enable_rpm(&hyperbus->rpc);

	rpcअगर_hw_init(&hyperbus->rpc, true);

	hyperbus->hbdev.map.size = hyperbus->rpc.size;
	hyperbus->hbdev.map.virt = hyperbus->rpc.dirmap;

	hyperbus->ctlr.dev = dev;
	hyperbus->ctlr.ops = &rpcअगर_hb_ops;
	hyperbus->hbdev.ctlr = &hyperbus->ctlr;
	hyperbus->hbdev.np = of_get_next_child(pdev->dev.parent->of_node, शून्य);
	error = hyperbus_रेजिस्टर_device(&hyperbus->hbdev);
	अगर (error)
		rpcअगर_disable_rpm(&hyperbus->rpc);

	वापस error;
पूर्ण

अटल पूर्णांक rpcअगर_hb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rpcअगर_hyperbus *hyperbus = platक्रमm_get_drvdata(pdev);
	पूर्णांक error = hyperbus_unरेजिस्टर_device(&hyperbus->hbdev);
	काष्ठा rpcअगर *rpc = dev_get_drvdata(pdev->dev.parent);

	rpcअगर_disable_rpm(rpc);
	वापस error;
पूर्ण

अटल काष्ठा platक्रमm_driver rpcअगर_platक्रमm_driver = अणु
	.probe	= rpcअगर_hb_probe,
	.हटाओ	= rpcअगर_hb_हटाओ,
	.driver	= अणु
		.name	= "rpc-if-hyperflash",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rpcअगर_platक्रमm_driver);

MODULE_DESCRIPTION("Renesas RPC-IF HyperFlash driver");
MODULE_LICENSE("GPL v2");
