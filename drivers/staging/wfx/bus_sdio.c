<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SDIO पूर्णांकerface.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#समावेश <linux/module.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irq.h>

#समावेश "bus.h"
#समावेश "wfx.h"
#समावेश "hwio.h"
#समावेश "main.h"
#समावेश "bh.h"

अटल स्थिर काष्ठा wfx_platक्रमm_data wfx_sdio_pdata = अणु
	.file_fw = "wfm_wf200",
	.file_pds = "wf200.pds",
पूर्ण;

काष्ठा wfx_sdio_priv अणु
	काष्ठा sdio_func *func;
	काष्ठा wfx_dev *core;
	u8 buf_id_tx;
	u8 buf_id_rx;
	पूर्णांक of_irq;
पूर्ण;

अटल पूर्णांक wfx_sdio_copy_from_io(व्योम *priv, अचिन्हित पूर्णांक reg_id,
				 व्योम *dst, माप_प्रकार count)
अणु
	काष्ठा wfx_sdio_priv *bus = priv;
	अचिन्हित पूर्णांक sdio_addr = reg_id << 2;
	पूर्णांक ret;

	WARN(reg_id > 7, "chip only has 7 registers");
	WARN(((uपूर्णांकptr_t)dst) & 3, "unaligned buffer size");
	WARN(count & 3, "unaligned buffer address");

	/* Use queue mode buffers */
	अगर (reg_id == WFX_REG_IN_OUT_QUEUE)
		sdio_addr |= (bus->buf_id_rx + 1) << 7;
	ret = sdio_स_नकल_fromio(bus->func, dst, sdio_addr, count);
	अगर (!ret && reg_id == WFX_REG_IN_OUT_QUEUE)
		bus->buf_id_rx = (bus->buf_id_rx + 1) % 4;

	वापस ret;
पूर्ण

अटल पूर्णांक wfx_sdio_copy_to_io(व्योम *priv, अचिन्हित पूर्णांक reg_id,
			       स्थिर व्योम *src, माप_प्रकार count)
अणु
	काष्ठा wfx_sdio_priv *bus = priv;
	अचिन्हित पूर्णांक sdio_addr = reg_id << 2;
	पूर्णांक ret;

	WARN(reg_id > 7, "chip only has 7 registers");
	WARN(((uपूर्णांकptr_t)src) & 3, "unaligned buffer size");
	WARN(count & 3, "unaligned buffer address");

	/* Use queue mode buffers */
	अगर (reg_id == WFX_REG_IN_OUT_QUEUE)
		sdio_addr |= bus->buf_id_tx << 7;
	// FIXME: discards 'const' qualअगरier क्रम src
	ret = sdio_स_नकल_toio(bus->func, sdio_addr, (व्योम *)src, count);
	अगर (!ret && reg_id == WFX_REG_IN_OUT_QUEUE)
		bus->buf_id_tx = (bus->buf_id_tx + 1) % 32;

	वापस ret;
पूर्ण

अटल व्योम wfx_sdio_lock(व्योम *priv)
अणु
	काष्ठा wfx_sdio_priv *bus = priv;

	sdio_claim_host(bus->func);
पूर्ण

अटल व्योम wfx_sdio_unlock(व्योम *priv)
अणु
	काष्ठा wfx_sdio_priv *bus = priv;

	sdio_release_host(bus->func);
पूर्ण

अटल व्योम wfx_sdio_irq_handler(काष्ठा sdio_func *func)
अणु
	काष्ठा wfx_sdio_priv *bus = sdio_get_drvdata(func);

	wfx_bh_request_rx(bus->core);
पूर्ण

अटल irqवापस_t wfx_sdio_irq_handler_ext(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा wfx_sdio_priv *bus = priv;

	sdio_claim_host(bus->func);
	wfx_bh_request_rx(bus->core);
	sdio_release_host(bus->func);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wfx_sdio_irq_subscribe(व्योम *priv)
अणु
	काष्ठा wfx_sdio_priv *bus = priv;
	u32 flags;
	पूर्णांक ret;
	u8 cccr;

	अगर (!bus->of_irq) अणु
		sdio_claim_host(bus->func);
		ret = sdio_claim_irq(bus->func, wfx_sdio_irq_handler);
		sdio_release_host(bus->func);
		वापस ret;
	पूर्ण

	sdio_claim_host(bus->func);
	cccr = sdio_f0_पढ़ोb(bus->func, SDIO_CCCR_IENx, शून्य);
	cccr |= BIT(0);
	cccr |= BIT(bus->func->num);
	sdio_f0_ग_लिखोb(bus->func, cccr, SDIO_CCCR_IENx, शून्य);
	sdio_release_host(bus->func);
	flags = irq_get_trigger_type(bus->of_irq);
	अगर (!flags)
		flags = IRQF_TRIGGER_HIGH;
	flags |= IRQF_ONESHOT;
	वापस devm_request_thपढ़ोed_irq(&bus->func->dev, bus->of_irq, शून्य,
					 wfx_sdio_irq_handler_ext, flags,
					 "wfx", bus);
पूर्ण

अटल पूर्णांक wfx_sdio_irq_unsubscribe(व्योम *priv)
अणु
	काष्ठा wfx_sdio_priv *bus = priv;
	पूर्णांक ret;

	अगर (bus->of_irq)
		devm_मुक्त_irq(&bus->func->dev, bus->of_irq, bus);
	sdio_claim_host(bus->func);
	ret = sdio_release_irq(bus->func);
	sdio_release_host(bus->func);
	वापस ret;
पूर्ण

अटल माप_प्रकार wfx_sdio_align_size(व्योम *priv, माप_प्रकार size)
अणु
	काष्ठा wfx_sdio_priv *bus = priv;

	वापस sdio_align_size(bus->func, size);
पूर्ण

अटल स्थिर काष्ठा hwbus_ops wfx_sdio_hwbus_ops = अणु
	.copy_from_io = wfx_sdio_copy_from_io,
	.copy_to_io = wfx_sdio_copy_to_io,
	.irq_subscribe = wfx_sdio_irq_subscribe,
	.irq_unsubscribe = wfx_sdio_irq_unsubscribe,
	.lock			= wfx_sdio_lock,
	.unlock			= wfx_sdio_unlock,
	.align_size		= wfx_sdio_align_size,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wfx_sdio_of_match[] = अणु
	अणु .compatible = "silabs,wfx-sdio" पूर्ण,
	अणु .compatible = "silabs,wf200" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, wfx_sdio_of_match);

अटल पूर्णांक wfx_sdio_probe(काष्ठा sdio_func *func,
			  स्थिर काष्ठा sdio_device_id *id)
अणु
	काष्ठा device_node *np = func->dev.of_node;
	काष्ठा wfx_sdio_priv *bus;
	पूर्णांक ret;

	अगर (func->num != 1) अणु
		dev_err(&func->dev, "SDIO function number is %d while it should always be 1 (unsupported chip?)\n",
			func->num);
		वापस -ENODEV;
	पूर्ण

	bus = devm_kzalloc(&func->dev, माप(*bus), GFP_KERNEL);
	अगर (!bus)
		वापस -ENOMEM;

	अगर (np) अणु
		अगर (!of_match_node(wfx_sdio_of_match, np)) अणु
			dev_warn(&func->dev, "no compatible device found in DT\n");
			वापस -ENODEV;
		पूर्ण
		bus->of_irq = irq_of_parse_and_map(np, 0);
	पूर्ण अन्यथा अणु
		dev_warn(&func->dev,
			 "device is not declared in DT, features will be limited\n");
		// FIXME: ignore VID/PID and only rely on device tree
		// वापस -ENODEV;
	पूर्ण

	bus->func = func;
	sdio_set_drvdata(func, bus);
	func->card->quirks |= MMC_QUIRK_LENIENT_FN0 |
			      MMC_QUIRK_BLKSZ_FOR_BYTE_MODE |
			      MMC_QUIRK_BROKEN_BYTE_MODE_512;

	sdio_claim_host(func);
	ret = sdio_enable_func(func);
	// Block of 64 bytes is more efficient than 512B क्रम frame sizes < 4k
	sdio_set_block_size(func, 64);
	sdio_release_host(func);
	अगर (ret)
		जाओ err0;

	bus->core = wfx_init_common(&func->dev, &wfx_sdio_pdata,
				    &wfx_sdio_hwbus_ops, bus);
	अगर (!bus->core) अणु
		ret = -EIO;
		जाओ err1;
	पूर्ण

	ret = wfx_probe(bus->core);
	अगर (ret)
		जाओ err1;

	वापस 0;

err1:
	sdio_claim_host(func);
	sdio_disable_func(func);
	sdio_release_host(func);
err0:
	वापस ret;
पूर्ण

अटल व्योम wfx_sdio_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा wfx_sdio_priv *bus = sdio_get_drvdata(func);

	wfx_release(bus->core);
	sdio_claim_host(func);
	sdio_disable_func(func);
	sdio_release_host(func);
पूर्ण

#घोषणा SDIO_VENDOR_ID_SILABS        0x0000
#घोषणा SDIO_DEVICE_ID_SILABS_WF200  0x1000
अटल स्थिर काष्ठा sdio_device_id wfx_sdio_ids[] = अणु
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_SILABS, SDIO_DEVICE_ID_SILABS_WF200) पूर्ण,
	// FIXME: ignore VID/PID and only rely on device tree
	// अणु SDIO_DEVICE(SDIO_ANY_ID, SDIO_ANY_ID) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(sdio, wfx_sdio_ids);

काष्ठा sdio_driver wfx_sdio_driver = अणु
	.name = "wfx-sdio",
	.id_table = wfx_sdio_ids,
	.probe = wfx_sdio_probe,
	.हटाओ = wfx_sdio_हटाओ,
	.drv = अणु
		.owner = THIS_MODULE,
		.of_match_table = wfx_sdio_of_match,
	पूर्ण
पूर्ण;
