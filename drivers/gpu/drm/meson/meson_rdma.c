<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/dma-mapping.h>

#समावेश "meson_drv.h"
#समावेश "meson_registers.h"
#समावेश "meson_rdma.h"

/*
 * The VPU embeds a "Register DMA" that can ग_लिखो a sequence of रेजिस्टरs
 * on the VPU AHB bus, either manually or triggered by an पूर्णांकernal IRQ
 * event like VSYNC or a line input counter.
 * The initial implementation handles a single channel (over 8), triggered
 * by the VSYNC irq and करोes not handle the RDMA irq.
 */

#घोषणा RDMA_DESC_SIZE	(माप(uपूर्णांक32_t) * 2)

पूर्णांक meson_rdma_init(काष्ठा meson_drm *priv)
अणु
	अगर (!priv->rdma.addr) अणु
		/* Allocate a PAGE buffer */
		priv->rdma.addr =
			dma_alloc_coherent(priv->dev, SZ_4K,
					   &priv->rdma.addr_dma,
					   GFP_KERNEL);
		अगर (!priv->rdma.addr)
			वापस -ENOMEM;
	पूर्ण

	priv->rdma.offset = 0;

	ग_लिखोl_relaxed(RDMA_CTRL_SW_RESET,
		       priv->io_base + _REG(RDMA_CTRL));
	ग_लिखोl_relaxed(RDMA_DEFAULT_CONFIG |
		       FIELD_PREP(RDMA_CTRL_AHB_WR_BURST, 3) |
		       FIELD_PREP(RDMA_CTRL_AHB_RD_BURST, 0),
		       priv->io_base + _REG(RDMA_CTRL));

	वापस 0;
पूर्ण

व्योम meson_rdma_मुक्त(काष्ठा meson_drm *priv)
अणु
	अगर (!priv->rdma.addr && !priv->rdma.addr_dma)
		वापस;

	meson_rdma_stop(priv);

	dma_मुक्त_coherent(priv->dev, SZ_4K,
			  priv->rdma.addr, priv->rdma.addr_dma);

	priv->rdma.addr = शून्य;
	priv->rdma.addr_dma = (dma_addr_t)0;
पूर्ण

व्योम meson_rdma_setup(काष्ठा meson_drm *priv)
अणु
	/* Channel 1: Write Flag, No Address Increment */
	ग_लिखोl_bits_relaxed(RDMA_ACCESS_RW_FLAG_CHAN1 |
			    RDMA_ACCESS_ADDR_INC_CHAN1,
			    RDMA_ACCESS_RW_FLAG_CHAN1,
			    priv->io_base + _REG(RDMA_ACCESS_AUTO));
पूर्ण

व्योम meson_rdma_stop(काष्ठा meson_drm *priv)
अणु
	ग_लिखोl_bits_relaxed(RDMA_IRQ_CLEAR_CHAN1,
			    RDMA_IRQ_CLEAR_CHAN1,
			    priv->io_base + _REG(RDMA_CTRL));

	/* Stop Channel 1 */
	ग_लिखोl_bits_relaxed(RDMA_ACCESS_TRIGGER_CHAN1,
			    FIELD_PREP(RDMA_ACCESS_ADDR_INC_CHAN1,
				       RDMA_ACCESS_TRIGGER_STOP),
			    priv->io_base + _REG(RDMA_ACCESS_AUTO));
पूर्ण

व्योम meson_rdma_reset(काष्ठा meson_drm *priv)
अणु
	meson_rdma_stop(priv);

	priv->rdma.offset = 0;
पूर्ण

अटल व्योम meson_rdma_ग_लिखोl(काष्ठा meson_drm *priv, uपूर्णांक32_t val,
			      uपूर्णांक32_t reg)
अणु
	अगर (priv->rdma.offset >= (SZ_4K / RDMA_DESC_SIZE)) अणु
		dev_warn_once(priv->dev, "%s: overflow\n", __func__);
		वापस;
	पूर्ण

	priv->rdma.addr[priv->rdma.offset++] = reg;
	priv->rdma.addr[priv->rdma.offset++] = val;
पूर्ण

/*
 * This will add the रेजिस्टर to the RDMA buffer and ग_लिखो it to the
 * hardware at the same समय.
 * When meson_rdma_flush is called, the RDMA will replay the रेजिस्टर
 * ग_लिखोs in order.
 */
व्योम meson_rdma_ग_लिखोl_sync(काष्ठा meson_drm *priv, uपूर्णांक32_t val, uपूर्णांक32_t reg)
अणु
	meson_rdma_ग_लिखोl(priv, val, reg);

	ग_लिखोl_relaxed(val, priv->io_base + _REG(reg));
पूर्ण

व्योम meson_rdma_flush(काष्ठा meson_drm *priv)
अणु
	meson_rdma_stop(priv);

	/* Start of Channel 1 रेजिस्टर ग_लिखोs buffer */
	ग_लिखोl(priv->rdma.addr_dma,
	       priv->io_base + _REG(RDMA_AHB_START_ADDR_1));

	/* Last byte on Channel 1 रेजिस्टर ग_लिखोs buffer */
	ग_लिखोl(priv->rdma.addr_dma + (priv->rdma.offset * RDMA_DESC_SIZE) - 1,
	       priv->io_base + _REG(RDMA_AHB_END_ADDR_1));

	/* Trigger Channel 1 on VSYNC event */
	ग_लिखोl_bits_relaxed(RDMA_ACCESS_TRIGGER_CHAN1,
			    FIELD_PREP(RDMA_ACCESS_TRIGGER_CHAN1,
				       RDMA_ACCESS_TRIGGER_VSYNC),
			    priv->io_base + _REG(RDMA_ACCESS_AUTO));

	priv->rdma.offset = 0;
पूर्ण
