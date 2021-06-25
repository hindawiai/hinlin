<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* OMAP SSI पूर्णांकernal पूर्णांकerface.
 *
 * Copyright (C) 2010 Nokia Corporation. All rights reserved.
 * Copyright (C) 2013 Sebastian Reichel
 *
 * Contact: Carlos Chinea <carlos.chinea@nokia.com>
 */

#अगर_अघोषित __LINUX_HSI_OMAP_SSI_H__
#घोषणा __LINUX_HSI_OMAP_SSI_H__

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hsi/hsi.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

#घोषणा SSI_MAX_CHANNELS	8
#घोषणा SSI_MAX_GDD_LCH		8
#घोषणा SSI_BYTES_TO_FRAMES(x) ((((x) - 1) >> 2) + 1)

#घोषणा SSI_WAKE_EN 0

/**
 * काष्ठा omap_ssm_ctx - OMAP synchronous serial module (TX/RX) context
 * @mode: Bit transmission mode
 * @channels: Number of channels
 * @framesize: Frame size in bits
 * @समयout: RX frame समयout
 * @भागisor: TX भागider
 * @arb_mode: Arbitration mode क्रम TX frame (Round robin, priority)
 */
काष्ठा omap_ssm_ctx अणु
	u32	mode;
	u32	channels;
	u32	frame_size;
	जोड़	अणु
			u32	समयout; /* Rx Only */
			काष्ठा	अणु
					u32	arb_mode;
					u32	भागisor;
			पूर्ण; /* Tx only */
	पूर्ण;
पूर्ण;

/**
 * काष्ठा omap_ssi_port - OMAP SSI port data
 * @dev: device associated to the port (HSI port)
 * @pdev: platक्रमm device associated to the port
 * @sst_dma: SSI transmitter physical base address
 * @ssr_dma: SSI receiver physical base address
 * @sst_base: SSI transmitter base address
 * @ssr_base: SSI receiver base address
 * @wk_lock: spin lock to serialize access to the wake lines
 * @lock: Spin lock to serialize access to the SSI port
 * @channels: Current number of channels configured (1,2,4 or 8)
 * @txqueue: TX message queues
 * @rxqueue: RX message queues
 * @brkqueue: Queue of incoming HWBREAK requests (FRAME mode)
 * @errqueue: Queue क्रम failed messages
 * @errqueue_work: Delayed Work क्रम failed messages
 * @irq: IRQ number
 * @wake_irq: IRQ number क्रम incoming wake line (-1 अगर none)
 * @wake_gpio: GPIO number क्रम incoming wake line (-1 अगर none)
 * @flags: flags to keep track of states
 * @wk_refcount: Reference count क्रम output wake line
 * @work: worker क्रम starting TX
 * @sys_mpu_enable: Context क्रम the पूर्णांकerrupt enable रेजिस्टर क्रम irq 0
 * @sst: Context क्रम the synchronous serial transmitter
 * @ssr: Context क्रम the synchronous serial receiver
 */
काष्ठा omap_ssi_port अणु
	काष्ठा device		*dev;
	काष्ठा device           *pdev;
	dma_addr_t		sst_dma;
	dma_addr_t		ssr_dma;
	व्योम __iomem		*sst_base;
	व्योम __iomem		*ssr_base;
	spinlock_t		wk_lock;
	spinlock_t		lock;
	अचिन्हित पूर्णांक		channels;
	काष्ठा list_head	txqueue[SSI_MAX_CHANNELS];
	काष्ठा list_head	rxqueue[SSI_MAX_CHANNELS];
	काष्ठा list_head	brkqueue;
	काष्ठा list_head	errqueue;
	काष्ठा delayed_work	errqueue_work;
	अचिन्हित पूर्णांक		irq;
	पूर्णांक			wake_irq;
	काष्ठा gpio_desc	*wake_gpio;
	bool			wktest:1; /* FIXME: HACK to be हटाओd */
	अचिन्हित दीर्घ		flags;
	अचिन्हित पूर्णांक		wk_refcount;
	काष्ठा work_काष्ठा	work;
	/* OMAP SSI port context */
	u32			sys_mpu_enable; /* We use only one irq */
	काष्ठा omap_ssm_ctx	sst;
	काष्ठा omap_ssm_ctx	ssr;
	u32			loss_count;
	u32			port_id;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *dir;
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा gdd_trn - GDD transaction data
 * @msg: Poपूर्णांकer to the HSI message being served
 * @sg: Poपूर्णांकer to the current sg entry being served
 */
काष्ठा gdd_trn अणु
	काष्ठा hsi_msg		*msg;
	काष्ठा scatterlist	*sg;
पूर्ण;

/**
 * काष्ठा omap_ssi_controller - OMAP SSI controller data
 * @dev: device associated to the controller (HSI controller)
 * @sys: SSI I/O base address
 * @gdd: GDD I/O base address
 * @fck: SSI functional घड़ी
 * @gdd_irq: IRQ line क्रम GDD
 * @gdd_tasklet: bottom half क्रम DMA transfers
 * @gdd_trn: Array of GDD transaction data क्रम ongoing GDD transfers
 * @lock: lock to serialize access to GDD
 * @fck_nb: DVFS notfअगरier block
 * @fck_rate: घड़ी rate
 * @loss_count: To follow अगर we need to restore context or not
 * @max_speed: Maximum TX speed (Kb/s) set by the clients.
 * @gdd_gcr: SSI GDD saved context
 * @get_loss: Poपूर्णांकer to omap_pm_get_dev_context_loss_count, अगर any
 * @port: Array of poपूर्णांकers of the ports of the controller
 * @dir: Debugfs SSI root directory
 */
काष्ठा omap_ssi_controller अणु
	काष्ठा device		*dev;
	व्योम __iomem		*sys;
	व्योम __iomem		*gdd;
	काष्ठा clk		*fck;
	अचिन्हित पूर्णांक		gdd_irq;
	काष्ठा tasklet_काष्ठा	gdd_tasklet;
	काष्ठा gdd_trn		gdd_trn[SSI_MAX_GDD_LCH];
	spinlock_t		lock;
	काष्ठा notअगरier_block	fck_nb;
	अचिन्हित दीर्घ		fck_rate;
	u32			loss_count;
	u32			max_speed;
	/* OMAP SSI Controller context */
	u32			gdd_gcr;
	पूर्णांक			(*get_loss)(काष्ठा device *dev);
	काष्ठा omap_ssi_port	**port;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *dir;
#पूर्ण_अगर
पूर्ण;

व्योम omap_ssi_port_update_fclk(काष्ठा hsi_controller *ssi,
			       काष्ठा omap_ssi_port *omap_port);

बाह्य काष्ठा platक्रमm_driver ssi_port_pdriver;

#पूर्ण_अगर /* __LINUX_HSI_OMAP_SSI_H__ */
