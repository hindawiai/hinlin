<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/mmc/host/sdhci.c - Secure Digital Host Controller Interface driver
 *
 *  Copyright (C) 2005-2008 Pierre Ossman, All Rights Reserved.
 *
 * Thanks to the following companies क्रम their support:
 *
 *     - JMicron (hardware and technical support)
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/sizes.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>

#समावेश <linux/leds.h>

#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/slot-gpपन.स>

#समावेश "sdhci.h"

#घोषणा DRIVER_NAME "sdhci"

#घोषणा DBG(f, x...) \
	pr_debug("%s: " DRIVER_NAME ": " f, mmc_hostname(host->mmc), ## x)

#घोषणा SDHCI_DUMP(f, x...) \
	pr_err("%s: " DRIVER_NAME ": " f, mmc_hostname(host->mmc), ## x)

#घोषणा MAX_TUNING_LOOP 40

अटल अचिन्हित पूर्णांक debug_quirks = 0;
अटल अचिन्हित पूर्णांक debug_quirks2;

अटल व्योम sdhci_enable_preset_value(काष्ठा sdhci_host *host, bool enable);

अटल bool sdhci_send_command(काष्ठा sdhci_host *host, काष्ठा mmc_command *cmd);

व्योम sdhci_dumpregs(काष्ठा sdhci_host *host)
अणु
	SDHCI_DUMP("============ SDHCI REGISTER DUMP ===========\n");

	SDHCI_DUMP("Sys addr:  0x%08x | Version:  0x%08x\n",
		   sdhci_पढ़ोl(host, SDHCI_DMA_ADDRESS),
		   sdhci_पढ़ोw(host, SDHCI_HOST_VERSION));
	SDHCI_DUMP("Blk size:  0x%08x | Blk cnt:  0x%08x\n",
		   sdhci_पढ़ोw(host, SDHCI_BLOCK_SIZE),
		   sdhci_पढ़ोw(host, SDHCI_BLOCK_COUNT));
	SDHCI_DUMP("Argument:  0x%08x | Trn mode: 0x%08x\n",
		   sdhci_पढ़ोl(host, SDHCI_ARGUMENT),
		   sdhci_पढ़ोw(host, SDHCI_TRANSFER_MODE));
	SDHCI_DUMP("Present:   0x%08x | Host ctl: 0x%08x\n",
		   sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE),
		   sdhci_पढ़ोb(host, SDHCI_HOST_CONTROL));
	SDHCI_DUMP("Power:     0x%08x | Blk gap:  0x%08x\n",
		   sdhci_पढ़ोb(host, SDHCI_POWER_CONTROL),
		   sdhci_पढ़ोb(host, SDHCI_BLOCK_GAP_CONTROL));
	SDHCI_DUMP("Wake-up:   0x%08x | Clock:    0x%08x\n",
		   sdhci_पढ़ोb(host, SDHCI_WAKE_UP_CONTROL),
		   sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL));
	SDHCI_DUMP("Timeout:   0x%08x | Int stat: 0x%08x\n",
		   sdhci_पढ़ोb(host, SDHCI_TIMEOUT_CONTROL),
		   sdhci_पढ़ोl(host, SDHCI_INT_STATUS));
	SDHCI_DUMP("Int enab:  0x%08x | Sig enab: 0x%08x\n",
		   sdhci_पढ़ोl(host, SDHCI_INT_ENABLE),
		   sdhci_पढ़ोl(host, SDHCI_SIGNAL_ENABLE));
	SDHCI_DUMP("ACmd stat: 0x%08x | Slot int: 0x%08x\n",
		   sdhci_पढ़ोw(host, SDHCI_AUTO_CMD_STATUS),
		   sdhci_पढ़ोw(host, SDHCI_SLOT_INT_STATUS));
	SDHCI_DUMP("Caps:      0x%08x | Caps_1:   0x%08x\n",
		   sdhci_पढ़ोl(host, SDHCI_CAPABILITIES),
		   sdhci_पढ़ोl(host, SDHCI_CAPABILITIES_1));
	SDHCI_DUMP("Cmd:       0x%08x | Max curr: 0x%08x\n",
		   sdhci_पढ़ोw(host, SDHCI_COMMAND),
		   sdhci_पढ़ोl(host, SDHCI_MAX_CURRENT));
	SDHCI_DUMP("Resp[0]:   0x%08x | Resp[1]:  0x%08x\n",
		   sdhci_पढ़ोl(host, SDHCI_RESPONSE),
		   sdhci_पढ़ोl(host, SDHCI_RESPONSE + 4));
	SDHCI_DUMP("Resp[2]:   0x%08x | Resp[3]:  0x%08x\n",
		   sdhci_पढ़ोl(host, SDHCI_RESPONSE + 8),
		   sdhci_पढ़ोl(host, SDHCI_RESPONSE + 12));
	SDHCI_DUMP("Host ctl2: 0x%08x\n",
		   sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2));

	अगर (host->flags & SDHCI_USE_ADMA) अणु
		अगर (host->flags & SDHCI_USE_64_BIT_DMA) अणु
			SDHCI_DUMP("ADMA Err:  0x%08x | ADMA Ptr: 0x%08x%08x\n",
				   sdhci_पढ़ोl(host, SDHCI_ADMA_ERROR),
				   sdhci_पढ़ोl(host, SDHCI_ADMA_ADDRESS_HI),
				   sdhci_पढ़ोl(host, SDHCI_ADMA_ADDRESS));
		पूर्ण अन्यथा अणु
			SDHCI_DUMP("ADMA Err:  0x%08x | ADMA Ptr: 0x%08x\n",
				   sdhci_पढ़ोl(host, SDHCI_ADMA_ERROR),
				   sdhci_पढ़ोl(host, SDHCI_ADMA_ADDRESS));
		पूर्ण
	पूर्ण

	अगर (host->ops->dump_venकरोr_regs)
		host->ops->dump_venकरोr_regs(host);

	SDHCI_DUMP("============================================\n");
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_dumpregs);

/*****************************************************************************\
 *                                                                           *
 * Low level functions                                                       *
 *                                                                           *
\*****************************************************************************/

अटल व्योम sdhci_करो_enable_v4_mode(काष्ठा sdhci_host *host)
अणु
	u16 ctrl2;

	ctrl2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	अगर (ctrl2 & SDHCI_CTRL_V4_MODE)
		वापस;

	ctrl2 |= SDHCI_CTRL_V4_MODE;
	sdhci_ग_लिखोw(host, ctrl2, SDHCI_HOST_CONTROL2);
पूर्ण

/*
 * This can be called beक्रमe sdhci_add_host() by Venकरोr's host controller
 * driver to enable v4 mode अगर supported.
 */
व्योम sdhci_enable_v4_mode(काष्ठा sdhci_host *host)
अणु
	host->v4_mode = true;
	sdhci_करो_enable_v4_mode(host);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_enable_v4_mode);

अटल अंतरभूत bool sdhci_data_line_cmd(काष्ठा mmc_command *cmd)
अणु
	वापस cmd->data || cmd->flags & MMC_RSP_BUSY;
पूर्ण

अटल व्योम sdhci_set_card_detection(काष्ठा sdhci_host *host, bool enable)
अणु
	u32 present;

	अगर ((host->quirks & SDHCI_QUIRK_BROKEN_CARD_DETECTION) ||
	    !mmc_card_is_removable(host->mmc) || mmc_can_gpio_cd(host->mmc))
		वापस;

	अगर (enable) अणु
		present = sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE) &
				      SDHCI_CARD_PRESENT;

		host->ier |= present ? SDHCI_INT_CARD_REMOVE :
				       SDHCI_INT_CARD_INSERT;
	पूर्ण अन्यथा अणु
		host->ier &= ~(SDHCI_INT_CARD_REMOVE | SDHCI_INT_CARD_INSERT);
	पूर्ण

	sdhci_ग_लिखोl(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, host->ier, SDHCI_SIGNAL_ENABLE);
पूर्ण

अटल व्योम sdhci_enable_card_detection(काष्ठा sdhci_host *host)
अणु
	sdhci_set_card_detection(host, true);
पूर्ण

अटल व्योम sdhci_disable_card_detection(काष्ठा sdhci_host *host)
अणु
	sdhci_set_card_detection(host, false);
पूर्ण

अटल व्योम sdhci_runसमय_pm_bus_on(काष्ठा sdhci_host *host)
अणु
	अगर (host->bus_on)
		वापस;
	host->bus_on = true;
	pm_runसमय_get_noresume(mmc_dev(host->mmc));
पूर्ण

अटल व्योम sdhci_runसमय_pm_bus_off(काष्ठा sdhci_host *host)
अणु
	अगर (!host->bus_on)
		वापस;
	host->bus_on = false;
	pm_runसमय_put_noidle(mmc_dev(host->mmc));
पूर्ण

व्योम sdhci_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	kसमय_प्रकार समयout;

	sdhci_ग_लिखोb(host, mask, SDHCI_SOFTWARE_RESET);

	अगर (mask & SDHCI_RESET_ALL) अणु
		host->घड़ी = 0;
		/* Reset-all turns off SD Bus Power */
		अगर (host->quirks2 & SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
			sdhci_runसमय_pm_bus_off(host);
	पूर्ण

	/* Wait max 100 ms */
	समयout = kसमय_add_ms(kसमय_get(), 100);

	/* hw clears the bit when it's करोne */
	जबतक (1) अणु
		bool समयकरोut = kसमय_after(kसमय_get(), समयout);

		अगर (!(sdhci_पढ़ोb(host, SDHCI_SOFTWARE_RESET) & mask))
			अवरोध;
		अगर (समयकरोut) अणु
			pr_err("%s: Reset 0x%x never completed.\n",
				mmc_hostname(host->mmc), (पूर्णांक)mask);
			sdhci_dumpregs(host);
			वापस;
		पूर्ण
		udelay(10);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_reset);

अटल व्योम sdhci_करो_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	अगर (host->quirks & SDHCI_QUIRK_NO_CARD_NO_RESET) अणु
		काष्ठा mmc_host *mmc = host->mmc;

		अगर (!mmc->ops->get_cd(mmc))
			वापस;
	पूर्ण

	host->ops->reset(host, mask);

	अगर (mask & SDHCI_RESET_ALL) अणु
		अगर (host->flags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA)) अणु
			अगर (host->ops->enable_dma)
				host->ops->enable_dma(host);
		पूर्ण

		/* Resetting the controller clears many */
		host->preset_enabled = false;
	पूर्ण
पूर्ण

अटल व्योम sdhci_set_शेष_irqs(काष्ठा sdhci_host *host)
अणु
	host->ier = SDHCI_INT_BUS_POWER | SDHCI_INT_DATA_END_BIT |
		    SDHCI_INT_DATA_CRC | SDHCI_INT_DATA_TIMEOUT |
		    SDHCI_INT_INDEX | SDHCI_INT_END_BIT | SDHCI_INT_CRC |
		    SDHCI_INT_TIMEOUT | SDHCI_INT_DATA_END |
		    SDHCI_INT_RESPONSE;

	अगर (host->tuning_mode == SDHCI_TUNING_MODE_2 ||
	    host->tuning_mode == SDHCI_TUNING_MODE_3)
		host->ier |= SDHCI_INT_RETUNE;

	sdhci_ग_लिखोl(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, host->ier, SDHCI_SIGNAL_ENABLE);
पूर्ण

अटल व्योम sdhci_config_dma(काष्ठा sdhci_host *host)
अणु
	u8 ctrl;
	u16 ctrl2;

	अगर (host->version < SDHCI_SPEC_200)
		वापस;

	ctrl = sdhci_पढ़ोb(host, SDHCI_HOST_CONTROL);

	/*
	 * Always adjust the DMA selection as some controllers
	 * (e.g. JMicron) can't करो PIO properly when the selection
	 * is ADMA.
	 */
	ctrl &= ~SDHCI_CTRL_DMA_MASK;
	अगर (!(host->flags & SDHCI_REQ_USE_DMA))
		जाओ out;

	/* Note अगर DMA Select is zero then SDMA is selected */
	अगर (host->flags & SDHCI_USE_ADMA)
		ctrl |= SDHCI_CTRL_ADMA32;

	अगर (host->flags & SDHCI_USE_64_BIT_DMA) अणु
		/*
		 * If v4 mode, all supported DMA can be 64-bit addressing अगर
		 * controller supports 64-bit प्रणाली address, otherwise only
		 * ADMA can support 64-bit addressing.
		 */
		अगर (host->v4_mode) अणु
			ctrl2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
			ctrl2 |= SDHCI_CTRL_64BIT_ADDR;
			sdhci_ग_लिखोw(host, ctrl2, SDHCI_HOST_CONTROL2);
		पूर्ण अन्यथा अगर (host->flags & SDHCI_USE_ADMA) अणु
			/*
			 * Don't need to unकरो SDHCI_CTRL_ADMA32 in order to
			 * set SDHCI_CTRL_ADMA64.
			 */
			ctrl |= SDHCI_CTRL_ADMA64;
		पूर्ण
	पूर्ण

out:
	sdhci_ग_लिखोb(host, ctrl, SDHCI_HOST_CONTROL);
पूर्ण

अटल व्योम sdhci_init(काष्ठा sdhci_host *host, पूर्णांक soft)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	अचिन्हित दीर्घ flags;

	अगर (soft)
		sdhci_करो_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
	अन्यथा
		sdhci_करो_reset(host, SDHCI_RESET_ALL);

	अगर (host->v4_mode)
		sdhci_करो_enable_v4_mode(host);

	spin_lock_irqsave(&host->lock, flags);
	sdhci_set_शेष_irqs(host);
	spin_unlock_irqrestore(&host->lock, flags);

	host->cqe_on = false;

	अगर (soft) अणु
		/* क्रमce घड़ी reconfiguration */
		host->घड़ी = 0;
		mmc->ops->set_ios(mmc, &mmc->ios);
	पूर्ण
पूर्ण

अटल व्योम sdhci_reinit(काष्ठा sdhci_host *host)
अणु
	u32 cd = host->ier & (SDHCI_INT_CARD_REMOVE | SDHCI_INT_CARD_INSERT);

	sdhci_init(host, 0);
	sdhci_enable_card_detection(host);

	/*
	 * A change to the card detect bits indicates a change in present state,
	 * refer sdhci_set_card_detection(). A card detect पूर्णांकerrupt might have
	 * been missed जबतक the host controller was being reset, so trigger a
	 * rescan to check.
	 */
	अगर (cd != (host->ier & (SDHCI_INT_CARD_REMOVE | SDHCI_INT_CARD_INSERT)))
		mmc_detect_change(host->mmc, msecs_to_jअगरfies(200));
पूर्ण

अटल व्योम __sdhci_led_activate(काष्ठा sdhci_host *host)
अणु
	u8 ctrl;

	अगर (host->quirks & SDHCI_QUIRK_NO_LED)
		वापस;

	ctrl = sdhci_पढ़ोb(host, SDHCI_HOST_CONTROL);
	ctrl |= SDHCI_CTRL_LED;
	sdhci_ग_लिखोb(host, ctrl, SDHCI_HOST_CONTROL);
पूर्ण

अटल व्योम __sdhci_led_deactivate(काष्ठा sdhci_host *host)
अणु
	u8 ctrl;

	अगर (host->quirks & SDHCI_QUIRK_NO_LED)
		वापस;

	ctrl = sdhci_पढ़ोb(host, SDHCI_HOST_CONTROL);
	ctrl &= ~SDHCI_CTRL_LED;
	sdhci_ग_लिखोb(host, ctrl, SDHCI_HOST_CONTROL);
पूर्ण

#अगर IS_REACHABLE(CONFIG_LEDS_CLASS)
अटल व्योम sdhci_led_control(काष्ठा led_classdev *led,
			      क्रमागत led_brightness brightness)
अणु
	काष्ठा sdhci_host *host = container_of(led, काष्ठा sdhci_host, led);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);

	अगर (host->runसमय_suspended)
		जाओ out;

	अगर (brightness == LED_OFF)
		__sdhci_led_deactivate(host);
	अन्यथा
		__sdhci_led_activate(host);
out:
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल पूर्णांक sdhci_led_रेजिस्टर(काष्ठा sdhci_host *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;

	अगर (host->quirks & SDHCI_QUIRK_NO_LED)
		वापस 0;

	snम_लिखो(host->led_name, माप(host->led_name),
		 "%s::", mmc_hostname(mmc));

	host->led.name = host->led_name;
	host->led.brightness = LED_OFF;
	host->led.शेष_trigger = mmc_hostname(mmc);
	host->led.brightness_set = sdhci_led_control;

	वापस led_classdev_रेजिस्टर(mmc_dev(mmc), &host->led);
पूर्ण

अटल व्योम sdhci_led_unरेजिस्टर(काष्ठा sdhci_host *host)
अणु
	अगर (host->quirks & SDHCI_QUIRK_NO_LED)
		वापस;

	led_classdev_unरेजिस्टर(&host->led);
पूर्ण

अटल अंतरभूत व्योम sdhci_led_activate(काष्ठा sdhci_host *host)
अणु
पूर्ण

अटल अंतरभूत व्योम sdhci_led_deactivate(काष्ठा sdhci_host *host)
अणु
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक sdhci_led_रेजिस्टर(काष्ठा sdhci_host *host)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sdhci_led_unरेजिस्टर(काष्ठा sdhci_host *host)
अणु
पूर्ण

अटल अंतरभूत व्योम sdhci_led_activate(काष्ठा sdhci_host *host)
अणु
	__sdhci_led_activate(host);
पूर्ण

अटल अंतरभूत व्योम sdhci_led_deactivate(काष्ठा sdhci_host *host)
अणु
	__sdhci_led_deactivate(host);
पूर्ण

#पूर्ण_अगर

अटल व्योम sdhci_mod_समयr(काष्ठा sdhci_host *host, काष्ठा mmc_request *mrq,
			    अचिन्हित दीर्घ समयout)
अणु
	अगर (sdhci_data_line_cmd(mrq->cmd))
		mod_समयr(&host->data_समयr, समयout);
	अन्यथा
		mod_समयr(&host->समयr, समयout);
पूर्ण

अटल व्योम sdhci_del_समयr(काष्ठा sdhci_host *host, काष्ठा mmc_request *mrq)
अणु
	अगर (sdhci_data_line_cmd(mrq->cmd))
		del_समयr(&host->data_समयr);
	अन्यथा
		del_समयr(&host->समयr);
पूर्ण

अटल अंतरभूत bool sdhci_has_requests(काष्ठा sdhci_host *host)
अणु
	वापस host->cmd || host->data_cmd;
पूर्ण

/*****************************************************************************\
 *                                                                           *
 * Core functions                                                            *
 *                                                                           *
\*****************************************************************************/

अटल व्योम sdhci_पढ़ो_block_pio(काष्ठा sdhci_host *host)
अणु
	अचिन्हित दीर्घ flags;
	माप_प्रकार blksize, len, chunk;
	u32 scratch;
	u8 *buf;

	DBG("PIO reading\n");

	blksize = host->data->blksz;
	chunk = 0;

	local_irq_save(flags);

	जबतक (blksize) अणु
		BUG_ON(!sg_miter_next(&host->sg_miter));

		len = min(host->sg_miter.length, blksize);

		blksize -= len;
		host->sg_miter.consumed = len;

		buf = host->sg_miter.addr;

		जबतक (len) अणु
			अगर (chunk == 0) अणु
				scratch = sdhci_पढ़ोl(host, SDHCI_BUFFER);
				chunk = 4;
			पूर्ण

			*buf = scratch & 0xFF;

			buf++;
			scratch >>= 8;
			chunk--;
			len--;
		पूर्ण
	पूर्ण

	sg_miter_stop(&host->sg_miter);

	local_irq_restore(flags);
पूर्ण

अटल व्योम sdhci_ग_लिखो_block_pio(काष्ठा sdhci_host *host)
अणु
	अचिन्हित दीर्घ flags;
	माप_प्रकार blksize, len, chunk;
	u32 scratch;
	u8 *buf;

	DBG("PIO writing\n");

	blksize = host->data->blksz;
	chunk = 0;
	scratch = 0;

	local_irq_save(flags);

	जबतक (blksize) अणु
		BUG_ON(!sg_miter_next(&host->sg_miter));

		len = min(host->sg_miter.length, blksize);

		blksize -= len;
		host->sg_miter.consumed = len;

		buf = host->sg_miter.addr;

		जबतक (len) अणु
			scratch |= (u32)*buf << (chunk * 8);

			buf++;
			chunk++;
			len--;

			अगर ((chunk == 4) || ((len == 0) && (blksize == 0))) अणु
				sdhci_ग_लिखोl(host, scratch, SDHCI_BUFFER);
				chunk = 0;
				scratch = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	sg_miter_stop(&host->sg_miter);

	local_irq_restore(flags);
पूर्ण

अटल व्योम sdhci_transfer_pio(काष्ठा sdhci_host *host)
अणु
	u32 mask;

	अगर (host->blocks == 0)
		वापस;

	अगर (host->data->flags & MMC_DATA_READ)
		mask = SDHCI_DATA_AVAILABLE;
	अन्यथा
		mask = SDHCI_SPACE_AVAILABLE;

	/*
	 * Some controllers (JMicron JMB38x) mess up the buffer bits
	 * क्रम transfers < 4 bytes. As दीर्घ as it is just one block,
	 * we can ignore the bits.
	 */
	अगर ((host->quirks & SDHCI_QUIRK_BROKEN_SMALL_PIO) &&
		(host->data->blocks == 1))
		mask = ~0;

	जबतक (sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE) & mask) अणु
		अगर (host->quirks & SDHCI_QUIRK_PIO_NEEDS_DELAY)
			udelay(100);

		अगर (host->data->flags & MMC_DATA_READ)
			sdhci_पढ़ो_block_pio(host);
		अन्यथा
			sdhci_ग_लिखो_block_pio(host);

		host->blocks--;
		अगर (host->blocks == 0)
			अवरोध;
	पूर्ण

	DBG("PIO transfer complete.\n");
पूर्ण

अटल पूर्णांक sdhci_pre_dma_transfer(काष्ठा sdhci_host *host,
				  काष्ठा mmc_data *data, पूर्णांक cookie)
अणु
	पूर्णांक sg_count;

	/*
	 * If the data buffers are alपढ़ोy mapped, वापस the previous
	 * dma_map_sg() result.
	 */
	अगर (data->host_cookie == COOKIE_PRE_MAPPED)
		वापस data->sg_count;

	/* Bounce ग_लिखो requests to the bounce buffer */
	अगर (host->bounce_buffer) अणु
		अचिन्हित पूर्णांक length = data->blksz * data->blocks;

		अगर (length > host->bounce_buffer_size) अणु
			pr_err("%s: asked for transfer of %u bytes exceeds bounce buffer %u bytes\n",
			       mmc_hostname(host->mmc), length,
			       host->bounce_buffer_size);
			वापस -EIO;
		पूर्ण
		अगर (mmc_get_dma_dir(data) == DMA_TO_DEVICE) अणु
			/* Copy the data to the bounce buffer */
			अगर (host->ops->copy_to_bounce_buffer) अणु
				host->ops->copy_to_bounce_buffer(host,
								 data, length);
			पूर्ण अन्यथा अणु
				sg_copy_to_buffer(data->sg, data->sg_len,
						  host->bounce_buffer, length);
			पूर्ण
		पूर्ण
		/* Switch ownership to the DMA */
		dma_sync_single_क्रम_device(mmc_dev(host->mmc),
					   host->bounce_addr,
					   host->bounce_buffer_size,
					   mmc_get_dma_dir(data));
		/* Just a dummy value */
		sg_count = 1;
	पूर्ण अन्यथा अणु
		/* Just access the data directly from memory */
		sg_count = dma_map_sg(mmc_dev(host->mmc),
				      data->sg, data->sg_len,
				      mmc_get_dma_dir(data));
	पूर्ण

	अगर (sg_count == 0)
		वापस -ENOSPC;

	data->sg_count = sg_count;
	data->host_cookie = cookie;

	वापस sg_count;
पूर्ण

अटल अक्षर *sdhci_kmap_atomic(काष्ठा scatterlist *sg, अचिन्हित दीर्घ *flags)
अणु
	local_irq_save(*flags);
	वापस kmap_atomic(sg_page(sg)) + sg->offset;
पूर्ण

अटल व्योम sdhci_kunmap_atomic(व्योम *buffer, अचिन्हित दीर्घ *flags)
अणु
	kunmap_atomic(buffer);
	local_irq_restore(*flags);
पूर्ण

व्योम sdhci_adma_ग_लिखो_desc(काष्ठा sdhci_host *host, व्योम **desc,
			   dma_addr_t addr, पूर्णांक len, अचिन्हित पूर्णांक cmd)
अणु
	काष्ठा sdhci_adma2_64_desc *dma_desc = *desc;

	/* 32-bit and 64-bit descriptors have these members in same position */
	dma_desc->cmd = cpu_to_le16(cmd);
	dma_desc->len = cpu_to_le16(len);
	dma_desc->addr_lo = cpu_to_le32(lower_32_bits(addr));

	अगर (host->flags & SDHCI_USE_64_BIT_DMA)
		dma_desc->addr_hi = cpu_to_le32(upper_32_bits(addr));

	*desc += host->desc_sz;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_adma_ग_लिखो_desc);

अटल अंतरभूत व्योम __sdhci_adma_ग_लिखो_desc(काष्ठा sdhci_host *host,
					   व्योम **desc, dma_addr_t addr,
					   पूर्णांक len, अचिन्हित पूर्णांक cmd)
अणु
	अगर (host->ops->adma_ग_लिखो_desc)
		host->ops->adma_ग_लिखो_desc(host, desc, addr, len, cmd);
	अन्यथा
		sdhci_adma_ग_लिखो_desc(host, desc, addr, len, cmd);
पूर्ण

अटल व्योम sdhci_adma_mark_end(व्योम *desc)
अणु
	काष्ठा sdhci_adma2_64_desc *dma_desc = desc;

	/* 32-bit and 64-bit descriptors have 'cmd' in same position */
	dma_desc->cmd |= cpu_to_le16(ADMA2_END);
पूर्ण

अटल व्योम sdhci_adma_table_pre(काष्ठा sdhci_host *host,
	काष्ठा mmc_data *data, पूर्णांक sg_count)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित दीर्घ flags;
	dma_addr_t addr, align_addr;
	व्योम *desc, *align;
	अक्षर *buffer;
	पूर्णांक len, offset, i;

	/*
	 * The spec करोes not specअगरy endianness of descriptor table.
	 * We currently guess that it is LE.
	 */

	host->sg_count = sg_count;

	desc = host->adma_table;
	align = host->align_buffer;

	align_addr = host->align_addr;

	क्रम_each_sg(data->sg, sg, host->sg_count, i) अणु
		addr = sg_dma_address(sg);
		len = sg_dma_len(sg);

		/*
		 * The SDHCI specअगरication states that ADMA addresses must
		 * be 32-bit aligned. If they aren't, then we use a bounce
		 * buffer क्रम the (up to three) bytes that screw up the
		 * alignment.
		 */
		offset = (SDHCI_ADMA2_ALIGN - (addr & SDHCI_ADMA2_MASK)) &
			 SDHCI_ADMA2_MASK;
		अगर (offset) अणु
			अगर (data->flags & MMC_DATA_WRITE) अणु
				buffer = sdhci_kmap_atomic(sg, &flags);
				स_नकल(align, buffer, offset);
				sdhci_kunmap_atomic(buffer, &flags);
			पूर्ण

			/* tran, valid */
			__sdhci_adma_ग_लिखो_desc(host, &desc, align_addr,
						offset, ADMA2_TRAN_VALID);

			BUG_ON(offset > 65536);

			align += SDHCI_ADMA2_ALIGN;
			align_addr += SDHCI_ADMA2_ALIGN;

			addr += offset;
			len -= offset;
		पूर्ण

		BUG_ON(len > 65536);

		/* tran, valid */
		अगर (len)
			__sdhci_adma_ग_लिखो_desc(host, &desc, addr, len,
						ADMA2_TRAN_VALID);

		/*
		 * If this triggers then we have a calculation bug
		 * somewhere. :/
		 */
		WARN_ON((desc - host->adma_table) >= host->adma_table_sz);
	पूर्ण

	अगर (host->quirks & SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC) अणु
		/* Mark the last descriptor as the terminating descriptor */
		अगर (desc != host->adma_table) अणु
			desc -= host->desc_sz;
			sdhci_adma_mark_end(desc);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Add a terminating entry - nop, end, valid */
		__sdhci_adma_ग_लिखो_desc(host, &desc, 0, 0, ADMA2_NOP_END_VALID);
	पूर्ण
पूर्ण

अटल व्योम sdhci_adma_table_post(काष्ठा sdhci_host *host,
	काष्ठा mmc_data *data)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i, size;
	व्योम *align;
	अक्षर *buffer;
	अचिन्हित दीर्घ flags;

	अगर (data->flags & MMC_DATA_READ) अणु
		bool has_unaligned = false;

		/* Do a quick scan of the SG list क्रम any unaligned mappings */
		क्रम_each_sg(data->sg, sg, host->sg_count, i)
			अगर (sg_dma_address(sg) & SDHCI_ADMA2_MASK) अणु
				has_unaligned = true;
				अवरोध;
			पूर्ण

		अगर (has_unaligned) अणु
			dma_sync_sg_क्रम_cpu(mmc_dev(host->mmc), data->sg,
					    data->sg_len, DMA_FROM_DEVICE);

			align = host->align_buffer;

			क्रम_each_sg(data->sg, sg, host->sg_count, i) अणु
				अगर (sg_dma_address(sg) & SDHCI_ADMA2_MASK) अणु
					size = SDHCI_ADMA2_ALIGN -
					       (sg_dma_address(sg) & SDHCI_ADMA2_MASK);

					buffer = sdhci_kmap_atomic(sg, &flags);
					स_नकल(buffer, align, size);
					sdhci_kunmap_atomic(buffer, &flags);

					align += SDHCI_ADMA2_ALIGN;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sdhci_set_adma_addr(काष्ठा sdhci_host *host, dma_addr_t addr)
अणु
	sdhci_ग_लिखोl(host, lower_32_bits(addr), SDHCI_ADMA_ADDRESS);
	अगर (host->flags & SDHCI_USE_64_BIT_DMA)
		sdhci_ग_लिखोl(host, upper_32_bits(addr), SDHCI_ADMA_ADDRESS_HI);
पूर्ण

अटल dma_addr_t sdhci_sdma_address(काष्ठा sdhci_host *host)
अणु
	अगर (host->bounce_buffer)
		वापस host->bounce_addr;
	अन्यथा
		वापस sg_dma_address(host->data->sg);
पूर्ण

अटल व्योम sdhci_set_sdma_addr(काष्ठा sdhci_host *host, dma_addr_t addr)
अणु
	अगर (host->v4_mode)
		sdhci_set_adma_addr(host, addr);
	अन्यथा
		sdhci_ग_लिखोl(host, addr, SDHCI_DMA_ADDRESS);
पूर्ण

अटल अचिन्हित पूर्णांक sdhci_target_समयout(काष्ठा sdhci_host *host,
					 काष्ठा mmc_command *cmd,
					 काष्ठा mmc_data *data)
अणु
	अचिन्हित पूर्णांक target_समयout;

	/* समयout in us */
	अगर (!data) अणु
		target_समयout = cmd->busy_समयout * 1000;
	पूर्ण अन्यथा अणु
		target_समयout = DIV_ROUND_UP(data->समयout_ns, 1000);
		अगर (host->घड़ी && data->समयout_clks) अणु
			अचिन्हित दीर्घ दीर्घ val;

			/*
			 * data->समयout_clks is in units of घड़ी cycles.
			 * host->घड़ी is in Hz.  target_समयout is in us.
			 * Hence, us = 1000000 * cycles / Hz.  Round up.
			 */
			val = 1000000ULL * data->समयout_clks;
			अगर (करो_भाग(val, host->घड़ी))
				target_समयout++;
			target_समयout += val;
		पूर्ण
	पूर्ण

	वापस target_समयout;
पूर्ण

अटल व्योम sdhci_calc_sw_समयout(काष्ठा sdhci_host *host,
				  काष्ठा mmc_command *cmd)
अणु
	काष्ठा mmc_data *data = cmd->data;
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा mmc_ios *ios = &mmc->ios;
	अचिन्हित अक्षर bus_width = 1 << ios->bus_width;
	अचिन्हित पूर्णांक blksz;
	अचिन्हित पूर्णांक freq;
	u64 target_समयout;
	u64 transfer_समय;

	target_समयout = sdhci_target_समयout(host, cmd, data);
	target_समयout *= NSEC_PER_USEC;

	अगर (data) अणु
		blksz = data->blksz;
		freq = mmc->actual_घड़ी ? : host->घड़ी;
		transfer_समय = (u64)blksz * NSEC_PER_SEC * (8 / bus_width);
		करो_भाग(transfer_समय, freq);
		/* multiply by '2' to account क्रम any unknowns */
		transfer_समय = transfer_समय * 2;
		/* calculate समयout क्रम the entire data */
		host->data_समयout = data->blocks * target_समयout +
				     transfer_समय;
	पूर्ण अन्यथा अणु
		host->data_समयout = target_समयout;
	पूर्ण

	अगर (host->data_समयout)
		host->data_समयout += MMC_CMD_TRANSFER_TIME;
पूर्ण

अटल u8 sdhci_calc_समयout(काष्ठा sdhci_host *host, काष्ठा mmc_command *cmd,
			     bool *too_big)
अणु
	u8 count;
	काष्ठा mmc_data *data;
	अचिन्हित target_समयout, current_समयout;

	*too_big = true;

	/*
	 * If the host controller provides us with an incorrect समयout
	 * value, just skip the check and use 0xE.  The hardware may take
	 * दीर्घer to समय out, but that's much better than having a too-लघु
	 * समयout value.
	 */
	अगर (host->quirks & SDHCI_QUIRK_BROKEN_TIMEOUT_VAL)
		वापस 0xE;

	/* Unspecअगरied command, asume max */
	अगर (cmd == शून्य)
		वापस 0xE;

	data = cmd->data;
	/* Unspecअगरied समयout, assume max */
	अगर (!data && !cmd->busy_समयout)
		वापस 0xE;

	/* समयout in us */
	target_समयout = sdhci_target_समयout(host, cmd, data);

	/*
	 * Figure out needed cycles.
	 * We करो this in steps in order to fit inside a 32 bit पूर्णांक.
	 * The first step is the minimum समयout, which will have a
	 * minimum resolution of 6 bits:
	 * (1) 2^13*1000 > 2^22,
	 * (2) host->समयout_clk < 2^16
	 *     =>
	 *     (1) / (2) > 2^6
	 */
	count = 0;
	current_समयout = (1 << 13) * 1000 / host->समयout_clk;
	जबतक (current_समयout < target_समयout) अणु
		count++;
		current_समयout <<= 1;
		अगर (count >= 0xF)
			अवरोध;
	पूर्ण

	अगर (count >= 0xF) अणु
		अगर (!(host->quirks2 & SDHCI_QUIRK2_DISABLE_HW_TIMEOUT))
			DBG("Too large timeout 0x%x requested for CMD%d!\n",
			    count, cmd->opcode);
		count = 0xE;
	पूर्ण अन्यथा अणु
		*too_big = false;
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम sdhci_set_transfer_irqs(काष्ठा sdhci_host *host)
अणु
	u32 pio_irqs = SDHCI_INT_DATA_AVAIL | SDHCI_INT_SPACE_AVAIL;
	u32 dma_irqs = SDHCI_INT_DMA_END | SDHCI_INT_ADMA_ERROR;

	अगर (host->flags & SDHCI_REQ_USE_DMA)
		host->ier = (host->ier & ~pio_irqs) | dma_irqs;
	अन्यथा
		host->ier = (host->ier & ~dma_irqs) | pio_irqs;

	अगर (host->flags & (SDHCI_AUTO_CMD23 | SDHCI_AUTO_CMD12))
		host->ier |= SDHCI_INT_AUTO_CMD_ERR;
	अन्यथा
		host->ier &= ~SDHCI_INT_AUTO_CMD_ERR;

	sdhci_ग_लिखोl(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, host->ier, SDHCI_SIGNAL_ENABLE);
पूर्ण

व्योम sdhci_set_data_समयout_irq(काष्ठा sdhci_host *host, bool enable)
अणु
	अगर (enable)
		host->ier |= SDHCI_INT_DATA_TIMEOUT;
	अन्यथा
		host->ier &= ~SDHCI_INT_DATA_TIMEOUT;
	sdhci_ग_लिखोl(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, host->ier, SDHCI_SIGNAL_ENABLE);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_set_data_समयout_irq);

व्योम __sdhci_set_समयout(काष्ठा sdhci_host *host, काष्ठा mmc_command *cmd)
अणु
	bool too_big = false;
	u8 count = sdhci_calc_समयout(host, cmd, &too_big);

	अगर (too_big &&
	    host->quirks2 & SDHCI_QUIRK2_DISABLE_HW_TIMEOUT) अणु
		sdhci_calc_sw_समयout(host, cmd);
		sdhci_set_data_समयout_irq(host, false);
	पूर्ण अन्यथा अगर (!(host->ier & SDHCI_INT_DATA_TIMEOUT)) अणु
		sdhci_set_data_समयout_irq(host, true);
	पूर्ण

	sdhci_ग_लिखोb(host, count, SDHCI_TIMEOUT_CONTROL);
पूर्ण
EXPORT_SYMBOL_GPL(__sdhci_set_समयout);

अटल व्योम sdhci_set_समयout(काष्ठा sdhci_host *host, काष्ठा mmc_command *cmd)
अणु
	अगर (host->ops->set_समयout)
		host->ops->set_समयout(host, cmd);
	अन्यथा
		__sdhci_set_समयout(host, cmd);
पूर्ण

अटल व्योम sdhci_initialize_data(काष्ठा sdhci_host *host,
				  काष्ठा mmc_data *data)
अणु
	WARN_ON(host->data);

	/* Sanity checks */
	BUG_ON(data->blksz * data->blocks > 524288);
	BUG_ON(data->blksz > host->mmc->max_blk_size);
	BUG_ON(data->blocks > 65535);

	host->data = data;
	host->data_early = 0;
	host->data->bytes_xfered = 0;
पूर्ण

अटल अंतरभूत व्योम sdhci_set_block_info(काष्ठा sdhci_host *host,
					काष्ठा mmc_data *data)
अणु
	/* Set the DMA boundary value and block size */
	sdhci_ग_लिखोw(host,
		     SDHCI_MAKE_BLKSZ(host->sdma_boundary, data->blksz),
		     SDHCI_BLOCK_SIZE);
	/*
	 * For Version 4.10 onwards, अगर v4 mode is enabled, 32-bit Block Count
	 * can be supported, in that हाल 16-bit block count रेजिस्टर must be 0.
	 */
	अगर (host->version >= SDHCI_SPEC_410 && host->v4_mode &&
	    (host->quirks2 & SDHCI_QUIRK2_USE_32BIT_BLK_CNT)) अणु
		अगर (sdhci_पढ़ोw(host, SDHCI_BLOCK_COUNT))
			sdhci_ग_लिखोw(host, 0, SDHCI_BLOCK_COUNT);
		sdhci_ग_लिखोw(host, data->blocks, SDHCI_32BIT_BLK_CNT);
	पूर्ण अन्यथा अणु
		sdhci_ग_लिखोw(host, data->blocks, SDHCI_BLOCK_COUNT);
	पूर्ण
पूर्ण

अटल व्योम sdhci_prepare_data(काष्ठा sdhci_host *host, काष्ठा mmc_command *cmd)
अणु
	काष्ठा mmc_data *data = cmd->data;

	sdhci_initialize_data(host, data);

	अगर (host->flags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA)) अणु
		काष्ठा scatterlist *sg;
		अचिन्हित पूर्णांक length_mask, offset_mask;
		पूर्णांक i;

		host->flags |= SDHCI_REQ_USE_DMA;

		/*
		 * FIXME: This करोesn't account क्रम merging when mapping the
		 * scatterlist.
		 *
		 * The assumption here being that alignment and lengths are
		 * the same after DMA mapping to device address space.
		 */
		length_mask = 0;
		offset_mask = 0;
		अगर (host->flags & SDHCI_USE_ADMA) अणु
			अगर (host->quirks & SDHCI_QUIRK_32BIT_ADMA_SIZE) अणु
				length_mask = 3;
				/*
				 * As we use up to 3 byte chunks to work
				 * around alignment problems, we need to
				 * check the offset as well.
				 */
				offset_mask = 3;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (host->quirks & SDHCI_QUIRK_32BIT_DMA_SIZE)
				length_mask = 3;
			अगर (host->quirks & SDHCI_QUIRK_32BIT_DMA_ADDR)
				offset_mask = 3;
		पूर्ण

		अगर (unlikely(length_mask | offset_mask)) अणु
			क्रम_each_sg(data->sg, sg, data->sg_len, i) अणु
				अगर (sg->length & length_mask) अणु
					DBG("Reverting to PIO because of transfer size (%d)\n",
					    sg->length);
					host->flags &= ~SDHCI_REQ_USE_DMA;
					अवरोध;
				पूर्ण
				अगर (sg->offset & offset_mask) अणु
					DBG("Reverting to PIO because of bad alignment\n");
					host->flags &= ~SDHCI_REQ_USE_DMA;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (host->flags & SDHCI_REQ_USE_DMA) अणु
		पूर्णांक sg_cnt = sdhci_pre_dma_transfer(host, data, COOKIE_MAPPED);

		अगर (sg_cnt <= 0) अणु
			/*
			 * This only happens when someone fed
			 * us an invalid request.
			 */
			WARN_ON(1);
			host->flags &= ~SDHCI_REQ_USE_DMA;
		पूर्ण अन्यथा अगर (host->flags & SDHCI_USE_ADMA) अणु
			sdhci_adma_table_pre(host, data, sg_cnt);
			sdhci_set_adma_addr(host, host->adma_addr);
		पूर्ण अन्यथा अणु
			WARN_ON(sg_cnt != 1);
			sdhci_set_sdma_addr(host, sdhci_sdma_address(host));
		पूर्ण
	पूर्ण

	sdhci_config_dma(host);

	अगर (!(host->flags & SDHCI_REQ_USE_DMA)) अणु
		पूर्णांक flags;

		flags = SG_MITER_ATOMIC;
		अगर (host->data->flags & MMC_DATA_READ)
			flags |= SG_MITER_TO_SG;
		अन्यथा
			flags |= SG_MITER_FROM_SG;
		sg_miter_start(&host->sg_miter, data->sg, data->sg_len, flags);
		host->blocks = data->blocks;
	पूर्ण

	sdhci_set_transfer_irqs(host);

	sdhci_set_block_info(host, data);
पूर्ण

#अगर IS_ENABLED(CONFIG_MMC_SDHCI_EXTERNAL_DMA)

अटल पूर्णांक sdhci_बाह्यal_dma_init(काष्ठा sdhci_host *host)
अणु
	पूर्णांक ret = 0;
	काष्ठा mmc_host *mmc = host->mmc;

	host->tx_chan = dma_request_chan(mmc_dev(mmc), "tx");
	अगर (IS_ERR(host->tx_chan)) अणु
		ret = PTR_ERR(host->tx_chan);
		अगर (ret != -EPROBE_DEFER)
			pr_warn("Failed to request TX DMA channel.\n");
		host->tx_chan = शून्य;
		वापस ret;
	पूर्ण

	host->rx_chan = dma_request_chan(mmc_dev(mmc), "rx");
	अगर (IS_ERR(host->rx_chan)) अणु
		अगर (host->tx_chan) अणु
			dma_release_channel(host->tx_chan);
			host->tx_chan = शून्य;
		पूर्ण

		ret = PTR_ERR(host->rx_chan);
		अगर (ret != -EPROBE_DEFER)
			pr_warn("Failed to request RX DMA channel.\n");
		host->rx_chan = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा dma_chan *sdhci_बाह्यal_dma_channel(काष्ठा sdhci_host *host,
						   काष्ठा mmc_data *data)
अणु
	वापस data->flags & MMC_DATA_WRITE ? host->tx_chan : host->rx_chan;
पूर्ण

अटल पूर्णांक sdhci_बाह्यal_dma_setup(काष्ठा sdhci_host *host,
				    काष्ठा mmc_command *cmd)
अणु
	पूर्णांक ret, i;
	क्रमागत dma_transfer_direction dir;
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा mmc_data *data = cmd->data;
	काष्ठा dma_chan *chan;
	काष्ठा dma_slave_config cfg;
	dma_cookie_t cookie;
	पूर्णांक sg_cnt;

	अगर (!host->mapbase)
		वापस -EINVAL;

	cfg.src_addr = host->mapbase + SDHCI_BUFFER;
	cfg.dst_addr = host->mapbase + SDHCI_BUFFER;
	cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	cfg.src_maxburst = data->blksz / 4;
	cfg.dst_maxburst = data->blksz / 4;

	/* Sanity check: all the SG entries must be aligned by block size. */
	क्रम (i = 0; i < data->sg_len; i++) अणु
		अगर ((data->sg + i)->length % data->blksz)
			वापस -EINVAL;
	पूर्ण

	chan = sdhci_बाह्यal_dma_channel(host, data);

	ret = dmaengine_slave_config(chan, &cfg);
	अगर (ret)
		वापस ret;

	sg_cnt = sdhci_pre_dma_transfer(host, data, COOKIE_MAPPED);
	अगर (sg_cnt <= 0)
		वापस -EINVAL;

	dir = data->flags & MMC_DATA_WRITE ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;
	desc = dmaengine_prep_slave_sg(chan, data->sg, data->sg_len, dir,
				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc)
		वापस -EINVAL;

	desc->callback = शून्य;
	desc->callback_param = शून्य;

	cookie = dmaengine_submit(desc);
	अगर (dma_submit_error(cookie))
		ret = cookie;

	वापस ret;
पूर्ण

अटल व्योम sdhci_बाह्यal_dma_release(काष्ठा sdhci_host *host)
अणु
	अगर (host->tx_chan) अणु
		dma_release_channel(host->tx_chan);
		host->tx_chan = शून्य;
	पूर्ण

	अगर (host->rx_chan) अणु
		dma_release_channel(host->rx_chan);
		host->rx_chan = शून्य;
	पूर्ण

	sdhci_चयन_बाह्यal_dma(host, false);
पूर्ण

अटल व्योम __sdhci_बाह्यal_dma_prepare_data(काष्ठा sdhci_host *host,
					      काष्ठा mmc_command *cmd)
अणु
	काष्ठा mmc_data *data = cmd->data;

	sdhci_initialize_data(host, data);

	host->flags |= SDHCI_REQ_USE_DMA;
	sdhci_set_transfer_irqs(host);

	sdhci_set_block_info(host, data);
पूर्ण

अटल व्योम sdhci_बाह्यal_dma_prepare_data(काष्ठा sdhci_host *host,
					    काष्ठा mmc_command *cmd)
अणु
	अगर (!sdhci_बाह्यal_dma_setup(host, cmd)) अणु
		__sdhci_बाह्यal_dma_prepare_data(host, cmd);
	पूर्ण अन्यथा अणु
		sdhci_बाह्यal_dma_release(host);
		pr_err("%s: Cannot use external DMA, switch to the DMA/PIO which standard SDHCI provides.\n",
		       mmc_hostname(host->mmc));
		sdhci_prepare_data(host, cmd);
	पूर्ण
पूर्ण

अटल व्योम sdhci_बाह्यal_dma_pre_transfer(काष्ठा sdhci_host *host,
					    काष्ठा mmc_command *cmd)
अणु
	काष्ठा dma_chan *chan;

	अगर (!cmd->data)
		वापस;

	chan = sdhci_बाह्यal_dma_channel(host, cmd->data);
	अगर (chan)
		dma_async_issue_pending(chan);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक sdhci_बाह्यal_dma_init(काष्ठा sdhci_host *host)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम sdhci_बाह्यal_dma_release(काष्ठा sdhci_host *host)
अणु
पूर्ण

अटल अंतरभूत व्योम sdhci_बाह्यal_dma_prepare_data(काष्ठा sdhci_host *host,
						   काष्ठा mmc_command *cmd)
अणु
	/* This should never happen */
	WARN_ON_ONCE(1);
पूर्ण

अटल अंतरभूत व्योम sdhci_बाह्यal_dma_pre_transfer(काष्ठा sdhci_host *host,
						   काष्ठा mmc_command *cmd)
अणु
पूर्ण

अटल अंतरभूत काष्ठा dma_chan *sdhci_बाह्यal_dma_channel(काष्ठा sdhci_host *host,
							  काष्ठा mmc_data *data)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर

व्योम sdhci_चयन_बाह्यal_dma(काष्ठा sdhci_host *host, bool en)
अणु
	host->use_बाह्यal_dma = en;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_चयन_बाह्यal_dma);

अटल अंतरभूत bool sdhci_स्वतः_cmd12(काष्ठा sdhci_host *host,
				    काष्ठा mmc_request *mrq)
अणु
	वापस !mrq->sbc && (host->flags & SDHCI_AUTO_CMD12) &&
	       !mrq->cap_cmd_during_tfr;
पूर्ण

अटल अंतरभूत bool sdhci_स्वतः_cmd23(काष्ठा sdhci_host *host,
				    काष्ठा mmc_request *mrq)
अणु
	वापस mrq->sbc && (host->flags & SDHCI_AUTO_CMD23);
पूर्ण

अटल अंतरभूत bool sdhci_manual_cmd23(काष्ठा sdhci_host *host,
				      काष्ठा mmc_request *mrq)
अणु
	वापस mrq->sbc && !(host->flags & SDHCI_AUTO_CMD23);
पूर्ण

अटल अंतरभूत व्योम sdhci_स्वतः_cmd_select(काष्ठा sdhci_host *host,
					 काष्ठा mmc_command *cmd,
					 u16 *mode)
अणु
	bool use_cmd12 = sdhci_स्वतः_cmd12(host, cmd->mrq) &&
			 (cmd->opcode != SD_IO_RW_EXTENDED);
	bool use_cmd23 = sdhci_स्वतः_cmd23(host, cmd->mrq);
	u16 ctrl2;

	/*
	 * In हाल of Version 4.10 or later, use of 'Auto CMD Auto
	 * Select' is recommended rather than use of 'Auto CMD12
	 * Enable' or 'Auto CMD23 Enable'. We require Version 4 Mode
	 * here because some controllers (e.g sdhci-of-dwmshc) expect it.
	 */
	अगर (host->version >= SDHCI_SPEC_410 && host->v4_mode &&
	    (use_cmd12 || use_cmd23)) अणु
		*mode |= SDHCI_TRNS_AUTO_SEL;

		ctrl2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
		अगर (use_cmd23)
			ctrl2 |= SDHCI_CMD23_ENABLE;
		अन्यथा
			ctrl2 &= ~SDHCI_CMD23_ENABLE;
		sdhci_ग_लिखोw(host, ctrl2, SDHCI_HOST_CONTROL2);

		वापस;
	पूर्ण

	/*
	 * If we are sending CMD23, CMD12 never माला_लो sent
	 * on successful completion (so no Auto-CMD12).
	 */
	अगर (use_cmd12)
		*mode |= SDHCI_TRNS_AUTO_CMD12;
	अन्यथा अगर (use_cmd23)
		*mode |= SDHCI_TRNS_AUTO_CMD23;
पूर्ण

अटल व्योम sdhci_set_transfer_mode(काष्ठा sdhci_host *host,
	काष्ठा mmc_command *cmd)
अणु
	u16 mode = 0;
	काष्ठा mmc_data *data = cmd->data;

	अगर (data == शून्य) अणु
		अगर (host->quirks2 &
			SDHCI_QUIRK2_CLEAR_TRANSFERMODE_REG_BEFORE_CMD) अणु
			/* must not clear SDHCI_TRANSFER_MODE when tuning */
			अगर (cmd->opcode != MMC_SEND_TUNING_BLOCK_HS200)
				sdhci_ग_लिखोw(host, 0x0, SDHCI_TRANSFER_MODE);
		पूर्ण अन्यथा अणु
		/* clear Auto CMD settings क्रम no data CMDs */
			mode = sdhci_पढ़ोw(host, SDHCI_TRANSFER_MODE);
			sdhci_ग_लिखोw(host, mode & ~(SDHCI_TRNS_AUTO_CMD12 |
				SDHCI_TRNS_AUTO_CMD23), SDHCI_TRANSFER_MODE);
		पूर्ण
		वापस;
	पूर्ण

	WARN_ON(!host->data);

	अगर (!(host->quirks2 & SDHCI_QUIRK2_SUPPORT_SINGLE))
		mode = SDHCI_TRNS_BLK_CNT_EN;

	अगर (mmc_op_multi(cmd->opcode) || data->blocks > 1) अणु
		mode = SDHCI_TRNS_BLK_CNT_EN | SDHCI_TRNS_MULTI;
		sdhci_स्वतः_cmd_select(host, cmd, &mode);
		अगर (sdhci_स्वतः_cmd23(host, cmd->mrq))
			sdhci_ग_लिखोl(host, cmd->mrq->sbc->arg, SDHCI_ARGUMENT2);
	पूर्ण

	अगर (data->flags & MMC_DATA_READ)
		mode |= SDHCI_TRNS_READ;
	अगर (host->flags & SDHCI_REQ_USE_DMA)
		mode |= SDHCI_TRNS_DMA;

	sdhci_ग_लिखोw(host, mode, SDHCI_TRANSFER_MODE);
पूर्ण

अटल bool sdhci_needs_reset(काष्ठा sdhci_host *host, काष्ठा mmc_request *mrq)
अणु
	वापस (!(host->flags & SDHCI_DEVICE_DEAD) &&
		((mrq->cmd && mrq->cmd->error) ||
		 (mrq->sbc && mrq->sbc->error) ||
		 (mrq->data && mrq->data->stop && mrq->data->stop->error) ||
		 (host->quirks & SDHCI_QUIRK_RESET_AFTER_REQUEST)));
पूर्ण

अटल व्योम sdhci_set_mrq_करोne(काष्ठा sdhci_host *host, काष्ठा mmc_request *mrq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SDHCI_MAX_MRQS; i++) अणु
		अगर (host->mrqs_करोne[i] == mrq) अणु
			WARN_ON(1);
			वापस;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < SDHCI_MAX_MRQS; i++) अणु
		अगर (!host->mrqs_करोne[i]) अणु
			host->mrqs_करोne[i] = mrq;
			अवरोध;
		पूर्ण
	पूर्ण

	WARN_ON(i >= SDHCI_MAX_MRQS);
पूर्ण

अटल व्योम __sdhci_finish_mrq(काष्ठा sdhci_host *host, काष्ठा mmc_request *mrq)
अणु
	अगर (host->cmd && host->cmd->mrq == mrq)
		host->cmd = शून्य;

	अगर (host->data_cmd && host->data_cmd->mrq == mrq)
		host->data_cmd = शून्य;

	अगर (host->deferred_cmd && host->deferred_cmd->mrq == mrq)
		host->deferred_cmd = शून्य;

	अगर (host->data && host->data->mrq == mrq)
		host->data = शून्य;

	अगर (sdhci_needs_reset(host, mrq))
		host->pending_reset = true;

	sdhci_set_mrq_करोne(host, mrq);

	sdhci_del_समयr(host, mrq);

	अगर (!sdhci_has_requests(host))
		sdhci_led_deactivate(host);
पूर्ण

अटल व्योम sdhci_finish_mrq(काष्ठा sdhci_host *host, काष्ठा mmc_request *mrq)
अणु
	__sdhci_finish_mrq(host, mrq);

	queue_work(host->complete_wq, &host->complete_work);
पूर्ण

अटल व्योम __sdhci_finish_data(काष्ठा sdhci_host *host, bool sw_data_समयout)
अणु
	काष्ठा mmc_command *data_cmd = host->data_cmd;
	काष्ठा mmc_data *data = host->data;

	host->data = शून्य;
	host->data_cmd = शून्य;

	/*
	 * The controller needs a reset of पूर्णांकernal state machines upon error
	 * conditions.
	 */
	अगर (data->error) अणु
		अगर (!host->cmd || host->cmd == data_cmd)
			sdhci_करो_reset(host, SDHCI_RESET_CMD);
		sdhci_करो_reset(host, SDHCI_RESET_DATA);
	पूर्ण

	अगर ((host->flags & (SDHCI_REQ_USE_DMA | SDHCI_USE_ADMA)) ==
	    (SDHCI_REQ_USE_DMA | SDHCI_USE_ADMA))
		sdhci_adma_table_post(host, data);

	/*
	 * The specअगरication states that the block count रेजिस्टर must
	 * be updated, but it करोes not specअगरy at what poपूर्णांक in the
	 * data flow. That makes the रेजिस्टर entirely useless to पढ़ो
	 * back so we have to assume that nothing made it to the card
	 * in the event of an error.
	 */
	अगर (data->error)
		data->bytes_xfered = 0;
	अन्यथा
		data->bytes_xfered = data->blksz * data->blocks;

	/*
	 * Need to send CMD12 अगर -
	 * a) खोलो-ended multiblock transfer not using स्वतः CMD12 (no CMD23)
	 * b) error in multiblock transfer
	 */
	अगर (data->stop &&
	    ((!data->mrq->sbc && !sdhci_स्वतः_cmd12(host, data->mrq)) ||
	     data->error)) अणु
		/*
		 * 'cap_cmd_during_tfr' request must not use the command line
		 * after mmc_command_करोne() has been called. It is upper layer's
		 * responsibility to send the stop command अगर required.
		 */
		अगर (data->mrq->cap_cmd_during_tfr) अणु
			__sdhci_finish_mrq(host, data->mrq);
		पूर्ण अन्यथा अणु
			/* Aव्योम triggering warning in sdhci_send_command() */
			host->cmd = शून्य;
			अगर (!sdhci_send_command(host, data->stop)) अणु
				अगर (sw_data_समयout) अणु
					/*
					 * This is anyway a sw data समयout, so
					 * give up now.
					 */
					data->stop->error = -EIO;
					__sdhci_finish_mrq(host, data->mrq);
				पूर्ण अन्यथा अणु
					WARN_ON(host->deferred_cmd);
					host->deferred_cmd = data->stop;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		__sdhci_finish_mrq(host, data->mrq);
	पूर्ण
पूर्ण

अटल व्योम sdhci_finish_data(काष्ठा sdhci_host *host)
अणु
	__sdhci_finish_data(host, false);
पूर्ण

अटल bool sdhci_send_command(काष्ठा sdhci_host *host, काष्ठा mmc_command *cmd)
अणु
	पूर्णांक flags;
	u32 mask;
	अचिन्हित दीर्घ समयout;

	WARN_ON(host->cmd);

	/* Initially, a command has no error */
	cmd->error = 0;

	अगर ((host->quirks2 & SDHCI_QUIRK2_STOP_WITH_TC) &&
	    cmd->opcode == MMC_STOP_TRANSMISSION)
		cmd->flags |= MMC_RSP_BUSY;

	mask = SDHCI_CMD_INHIBIT;
	अगर (sdhci_data_line_cmd(cmd))
		mask |= SDHCI_DATA_INHIBIT;

	/* We shouldn't रुको क्रम data inihibit क्रम stop commands, even
	   though they might use busy संकेतing */
	अगर (cmd->mrq->data && (cmd == cmd->mrq->data->stop))
		mask &= ~SDHCI_DATA_INHIBIT;

	अगर (sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE) & mask)
		वापस false;

	host->cmd = cmd;
	host->data_समयout = 0;
	अगर (sdhci_data_line_cmd(cmd)) अणु
		WARN_ON(host->data_cmd);
		host->data_cmd = cmd;
		sdhci_set_समयout(host, cmd);
	पूर्ण

	अगर (cmd->data) अणु
		अगर (host->use_बाह्यal_dma)
			sdhci_बाह्यal_dma_prepare_data(host, cmd);
		अन्यथा
			sdhci_prepare_data(host, cmd);
	पूर्ण

	sdhci_ग_लिखोl(host, cmd->arg, SDHCI_ARGUMENT);

	sdhci_set_transfer_mode(host, cmd);

	अगर ((cmd->flags & MMC_RSP_136) && (cmd->flags & MMC_RSP_BUSY)) अणु
		WARN_ONCE(1, "Unsupported response type!\n");
		/*
		 * This करोes not happen in practice because 136-bit response
		 * commands never have busy रुकोing, so rather than complicate
		 * the error path, just हटाओ busy रुकोing and जारी.
		 */
		cmd->flags &= ~MMC_RSP_BUSY;
	पूर्ण

	अगर (!(cmd->flags & MMC_RSP_PRESENT))
		flags = SDHCI_CMD_RESP_NONE;
	अन्यथा अगर (cmd->flags & MMC_RSP_136)
		flags = SDHCI_CMD_RESP_LONG;
	अन्यथा अगर (cmd->flags & MMC_RSP_BUSY)
		flags = SDHCI_CMD_RESP_SHORT_BUSY;
	अन्यथा
		flags = SDHCI_CMD_RESP_SHORT;

	अगर (cmd->flags & MMC_RSP_CRC)
		flags |= SDHCI_CMD_CRC;
	अगर (cmd->flags & MMC_RSP_OPCODE)
		flags |= SDHCI_CMD_INDEX;

	/* CMD19 is special in that the Data Present Select should be set */
	अगर (cmd->data || cmd->opcode == MMC_SEND_TUNING_BLOCK ||
	    cmd->opcode == MMC_SEND_TUNING_BLOCK_HS200)
		flags |= SDHCI_CMD_DATA;

	समयout = jअगरfies;
	अगर (host->data_समयout)
		समयout += nsecs_to_jअगरfies(host->data_समयout);
	अन्यथा अगर (!cmd->data && cmd->busy_समयout > 9000)
		समयout += DIV_ROUND_UP(cmd->busy_समयout, 1000) * HZ + HZ;
	अन्यथा
		समयout += 10 * HZ;
	sdhci_mod_समयr(host, cmd->mrq, समयout);

	अगर (host->use_बाह्यal_dma)
		sdhci_बाह्यal_dma_pre_transfer(host, cmd);

	sdhci_ग_लिखोw(host, SDHCI_MAKE_CMD(cmd->opcode, flags), SDHCI_COMMAND);

	वापस true;
पूर्ण

अटल bool sdhci_present_error(काष्ठा sdhci_host *host,
				काष्ठा mmc_command *cmd, bool present)
अणु
	अगर (!present || host->flags & SDHCI_DEVICE_DEAD) अणु
		cmd->error = -ENOMEDIUM;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool sdhci_send_command_retry(काष्ठा sdhci_host *host,
				     काष्ठा mmc_command *cmd,
				     अचिन्हित दीर्घ flags)
	__releases(host->lock)
	__acquires(host->lock)
अणु
	काष्ठा mmc_command *deferred_cmd = host->deferred_cmd;
	पूर्णांक समयout = 10; /* Approx. 10 ms */
	bool present;

	जबतक (!sdhci_send_command(host, cmd)) अणु
		अगर (!समयout--) अणु
			pr_err("%s: Controller never released inhibit bit(s).\n",
			       mmc_hostname(host->mmc));
			sdhci_dumpregs(host);
			cmd->error = -EIO;
			वापस false;
		पूर्ण

		spin_unlock_irqrestore(&host->lock, flags);

		usleep_range(1000, 1250);

		present = host->mmc->ops->get_cd(host->mmc);

		spin_lock_irqsave(&host->lock, flags);

		/* A deferred command might disappear, handle that */
		अगर (cmd == deferred_cmd && cmd != host->deferred_cmd)
			वापस true;

		अगर (sdhci_present_error(host, cmd, present))
			वापस false;
	पूर्ण

	अगर (cmd == host->deferred_cmd)
		host->deferred_cmd = शून्य;

	वापस true;
पूर्ण

अटल व्योम sdhci_पढ़ो_rsp_136(काष्ठा sdhci_host *host, काष्ठा mmc_command *cmd)
अणु
	पूर्णांक i, reg;

	क्रम (i = 0; i < 4; i++) अणु
		reg = SDHCI_RESPONSE + (3 - i) * 4;
		cmd->resp[i] = sdhci_पढ़ोl(host, reg);
	पूर्ण

	अगर (host->quirks2 & SDHCI_QUIRK2_RSP_136_HAS_CRC)
		वापस;

	/* CRC is stripped so we need to करो some shअगरting */
	क्रम (i = 0; i < 4; i++) अणु
		cmd->resp[i] <<= 8;
		अगर (i != 3)
			cmd->resp[i] |= cmd->resp[i + 1] >> 24;
	पूर्ण
पूर्ण

अटल व्योम sdhci_finish_command(काष्ठा sdhci_host *host)
अणु
	काष्ठा mmc_command *cmd = host->cmd;

	host->cmd = शून्य;

	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अगर (cmd->flags & MMC_RSP_136) अणु
			sdhci_पढ़ो_rsp_136(host, cmd);
		पूर्ण अन्यथा अणु
			cmd->resp[0] = sdhci_पढ़ोl(host, SDHCI_RESPONSE);
		पूर्ण
	पूर्ण

	अगर (cmd->mrq->cap_cmd_during_tfr && cmd == cmd->mrq->cmd)
		mmc_command_करोne(host->mmc, cmd->mrq);

	/*
	 * The host can send and पूर्णांकerrupt when the busy state has
	 * ended, allowing us to रुको without wasting CPU cycles.
	 * The busy संकेत uses DAT0 so this is similar to रुकोing
	 * क्रम data to complete.
	 *
	 * Note: The 1.0 specअगरication is a bit ambiguous about this
	 *       feature so there might be some problems with older
	 *       controllers.
	 */
	अगर (cmd->flags & MMC_RSP_BUSY) अणु
		अगर (cmd->data) अणु
			DBG("Cannot wait for busy signal when also doing a data transfer");
		पूर्ण अन्यथा अगर (!(host->quirks & SDHCI_QUIRK_NO_BUSY_IRQ) &&
			   cmd == host->data_cmd) अणु
			/* Command complete beक्रमe busy is ended */
			वापस;
		पूर्ण
	पूर्ण

	/* Finished CMD23, now send actual command. */
	अगर (cmd == cmd->mrq->sbc) अणु
		अगर (!sdhci_send_command(host, cmd->mrq->cmd)) अणु
			WARN_ON(host->deferred_cmd);
			host->deferred_cmd = cmd->mrq->cmd;
		पूर्ण
	पूर्ण अन्यथा अणु

		/* Processed actual command. */
		अगर (host->data && host->data_early)
			sdhci_finish_data(host);

		अगर (!cmd->data)
			__sdhci_finish_mrq(host, cmd->mrq);
	पूर्ण
पूर्ण

अटल u16 sdhci_get_preset_value(काष्ठा sdhci_host *host)
अणु
	u16 preset = 0;

	चयन (host->timing) अणु
	हाल MMC_TIMING_UHS_SDR12:
		preset = sdhci_पढ़ोw(host, SDHCI_PRESET_FOR_SDR12);
		अवरोध;
	हाल MMC_TIMING_UHS_SDR25:
		preset = sdhci_पढ़ोw(host, SDHCI_PRESET_FOR_SDR25);
		अवरोध;
	हाल MMC_TIMING_UHS_SDR50:
		preset = sdhci_पढ़ोw(host, SDHCI_PRESET_FOR_SDR50);
		अवरोध;
	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_MMC_HS200:
		preset = sdhci_पढ़ोw(host, SDHCI_PRESET_FOR_SDR104);
		अवरोध;
	हाल MMC_TIMING_UHS_DDR50:
	हाल MMC_TIMING_MMC_DDR52:
		preset = sdhci_पढ़ोw(host, SDHCI_PRESET_FOR_DDR50);
		अवरोध;
	हाल MMC_TIMING_MMC_HS400:
		preset = sdhci_पढ़ोw(host, SDHCI_PRESET_FOR_HS400);
		अवरोध;
	शेष:
		pr_warn("%s: Invalid UHS-I mode selected\n",
			mmc_hostname(host->mmc));
		preset = sdhci_पढ़ोw(host, SDHCI_PRESET_FOR_SDR12);
		अवरोध;
	पूर्ण
	वापस preset;
पूर्ण

u16 sdhci_calc_clk(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी,
		   अचिन्हित पूर्णांक *actual_घड़ी)
अणु
	पूर्णांक भाग = 0; /* Initialized क्रम compiler warning */
	पूर्णांक real_भाग = भाग, clk_mul = 1;
	u16 clk = 0;
	bool चयन_base_clk = false;

	अगर (host->version >= SDHCI_SPEC_300) अणु
		अगर (host->preset_enabled) अणु
			u16 pre_val;

			clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
			pre_val = sdhci_get_preset_value(host);
			भाग = FIELD_GET(SDHCI_PRESET_SDCLK_FREQ_MASK, pre_val);
			अगर (host->clk_mul &&
				(pre_val & SDHCI_PRESET_CLKGEN_SEL)) अणु
				clk = SDHCI_PROG_CLOCK_MODE;
				real_भाग = भाग + 1;
				clk_mul = host->clk_mul;
			पूर्ण अन्यथा अणु
				real_भाग = max_t(पूर्णांक, 1, भाग << 1);
			पूर्ण
			जाओ घड़ी_set;
		पूर्ण

		/*
		 * Check अगर the Host Controller supports Programmable Clock
		 * Mode.
		 */
		अगर (host->clk_mul) अणु
			क्रम (भाग = 1; भाग <= 1024; भाग++) अणु
				अगर ((host->max_clk * host->clk_mul / भाग)
					<= घड़ी)
					अवरोध;
			पूर्ण
			अगर ((host->max_clk * host->clk_mul / भाग) <= घड़ी) अणु
				/*
				 * Set Programmable Clock Mode in the Clock
				 * Control रेजिस्टर.
				 */
				clk = SDHCI_PROG_CLOCK_MODE;
				real_भाग = भाग;
				clk_mul = host->clk_mul;
				भाग--;
			पूर्ण अन्यथा अणु
				/*
				 * Divisor can be too small to reach घड़ी
				 * speed requirement. Then use the base घड़ी.
				 */
				चयन_base_clk = true;
			पूर्ण
		पूर्ण

		अगर (!host->clk_mul || चयन_base_clk) अणु
			/* Version 3.00 भागisors must be a multiple of 2. */
			अगर (host->max_clk <= घड़ी)
				भाग = 1;
			अन्यथा अणु
				क्रम (भाग = 2; भाग < SDHCI_MAX_DIV_SPEC_300;
				     भाग += 2) अणु
					अगर ((host->max_clk / भाग) <= घड़ी)
						अवरोध;
				पूर्ण
			पूर्ण
			real_भाग = भाग;
			भाग >>= 1;
			अगर ((host->quirks2 & SDHCI_QUIRK2_CLOCK_DIV_ZERO_BROKEN)
				&& !भाग && host->max_clk <= 25000000)
				भाग = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Version 2.00 भागisors must be a घातer of 2. */
		क्रम (भाग = 1; भाग < SDHCI_MAX_DIV_SPEC_200; भाग *= 2) अणु
			अगर ((host->max_clk / भाग) <= घड़ी)
				अवरोध;
		पूर्ण
		real_भाग = भाग;
		भाग >>= 1;
	पूर्ण

घड़ी_set:
	अगर (real_भाग)
		*actual_घड़ी = (host->max_clk * clk_mul) / real_भाग;
	clk |= (भाग & SDHCI_DIV_MASK) << SDHCI_DIVIDER_SHIFT;
	clk |= ((भाग & SDHCI_DIV_HI_MASK) >> SDHCI_DIV_MASK_LEN)
		<< SDHCI_DIVIDER_HI_SHIFT;

	वापस clk;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_calc_clk);

व्योम sdhci_enable_clk(काष्ठा sdhci_host *host, u16 clk)
अणु
	kसमय_प्रकार समयout;

	clk |= SDHCI_CLOCK_INT_EN;
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);

	/* Wait max 150 ms */
	समयout = kसमय_add_ms(kसमय_get(), 150);
	जबतक (1) अणु
		bool समयकरोut = kसमय_after(kसमय_get(), समयout);

		clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
		अगर (clk & SDHCI_CLOCK_INT_STABLE)
			अवरोध;
		अगर (समयकरोut) अणु
			pr_err("%s: Internal clock never stabilised.\n",
			       mmc_hostname(host->mmc));
			sdhci_dumpregs(host);
			वापस;
		पूर्ण
		udelay(10);
	पूर्ण

	अगर (host->version >= SDHCI_SPEC_410 && host->v4_mode) अणु
		clk |= SDHCI_CLOCK_PLL_EN;
		clk &= ~SDHCI_CLOCK_INT_STABLE;
		sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);

		/* Wait max 150 ms */
		समयout = kसमय_add_ms(kसमय_get(), 150);
		जबतक (1) अणु
			bool समयकरोut = kसमय_after(kसमय_get(), समयout);

			clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
			अगर (clk & SDHCI_CLOCK_INT_STABLE)
				अवरोध;
			अगर (समयकरोut) अणु
				pr_err("%s: PLL clock never stabilised.\n",
				       mmc_hostname(host->mmc));
				sdhci_dumpregs(host);
				वापस;
			पूर्ण
			udelay(10);
		पूर्ण
	पूर्ण

	clk |= SDHCI_CLOCK_CARD_EN;
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_enable_clk);

व्योम sdhci_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	u16 clk;

	host->mmc->actual_घड़ी = 0;

	sdhci_ग_लिखोw(host, 0, SDHCI_CLOCK_CONTROL);

	अगर (घड़ी == 0)
		वापस;

	clk = sdhci_calc_clk(host, घड़ी, &host->mmc->actual_घड़ी);
	sdhci_enable_clk(host, clk);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_set_घड़ी);

अटल व्योम sdhci_set_घातer_reg(काष्ठा sdhci_host *host, अचिन्हित अक्षर mode,
				अचिन्हित लघु vdd)
अणु
	काष्ठा mmc_host *mmc = host->mmc;

	mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, vdd);

	अगर (mode != MMC_POWER_OFF)
		sdhci_ग_लिखोb(host, SDHCI_POWER_ON, SDHCI_POWER_CONTROL);
	अन्यथा
		sdhci_ग_लिखोb(host, 0, SDHCI_POWER_CONTROL);
पूर्ण

व्योम sdhci_set_घातer_noreg(काष्ठा sdhci_host *host, अचिन्हित अक्षर mode,
			   अचिन्हित लघु vdd)
अणु
	u8 pwr = 0;

	अगर (mode != MMC_POWER_OFF) अणु
		चयन (1 << vdd) अणु
		हाल MMC_VDD_165_195:
		/*
		 * Without a regulator, SDHCI करोes not support 2.0v
		 * so we only get here अगर the driver deliberately
		 * added the 2.0v range to ocr_avail. Map it to 1.8v
		 * क्रम the purpose of turning on the घातer.
		 */
		हाल MMC_VDD_20_21:
			pwr = SDHCI_POWER_180;
			अवरोध;
		हाल MMC_VDD_29_30:
		हाल MMC_VDD_30_31:
			pwr = SDHCI_POWER_300;
			अवरोध;
		हाल MMC_VDD_32_33:
		हाल MMC_VDD_33_34:
			pwr = SDHCI_POWER_330;
			अवरोध;
		शेष:
			WARN(1, "%s: Invalid vdd %#x\n",
			     mmc_hostname(host->mmc), vdd);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (host->pwr == pwr)
		वापस;

	host->pwr = pwr;

	अगर (pwr == 0) अणु
		sdhci_ग_लिखोb(host, 0, SDHCI_POWER_CONTROL);
		अगर (host->quirks2 & SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
			sdhci_runसमय_pm_bus_off(host);
	पूर्ण अन्यथा अणु
		/*
		 * Spec says that we should clear the घातer reg beक्रमe setting
		 * a new value. Some controllers करोn't seem to like this though.
		 */
		अगर (!(host->quirks & SDHCI_QUIRK_SINGLE_POWER_WRITE))
			sdhci_ग_लिखोb(host, 0, SDHCI_POWER_CONTROL);

		/*
		 * At least the Marvell CaFe chip माला_लो confused अगर we set the
		 * voltage and set turn on घातer at the same समय, so set the
		 * voltage first.
		 */
		अगर (host->quirks & SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER)
			sdhci_ग_लिखोb(host, pwr, SDHCI_POWER_CONTROL);

		pwr |= SDHCI_POWER_ON;

		sdhci_ग_लिखोb(host, pwr, SDHCI_POWER_CONTROL);

		अगर (host->quirks2 & SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
			sdhci_runसमय_pm_bus_on(host);

		/*
		 * Some controllers need an extra 10ms delay of 10ms beक्रमe
		 * they can apply घड़ी after applying घातer
		 */
		अगर (host->quirks & SDHCI_QUIRK_DELAY_AFTER_POWER)
			mdelay(10);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_set_घातer_noreg);

व्योम sdhci_set_घातer(काष्ठा sdhci_host *host, अचिन्हित अक्षर mode,
		     अचिन्हित लघु vdd)
अणु
	अगर (IS_ERR(host->mmc->supply.vmmc))
		sdhci_set_घातer_noreg(host, mode, vdd);
	अन्यथा
		sdhci_set_घातer_reg(host, mode, vdd);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_set_घातer);

/*
 * Some controllers need to configure a valid bus voltage on their घातer
 * रेजिस्टर regardless of whether an बाह्यal regulator is taking care of घातer
 * supply. This helper function takes care of it अगर set as the controller's
 * sdhci_ops.set_घातer callback.
 */
व्योम sdhci_set_घातer_and_bus_voltage(काष्ठा sdhci_host *host,
				     अचिन्हित अक्षर mode,
				     अचिन्हित लघु vdd)
अणु
	अगर (!IS_ERR(host->mmc->supply.vmmc)) अणु
		काष्ठा mmc_host *mmc = host->mmc;

		mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, vdd);
	पूर्ण
	sdhci_set_घातer_noreg(host, mode, vdd);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_set_घातer_and_bus_voltage);

/*****************************************************************************\
 *                                                                           *
 * MMC callbacks                                                             *
 *                                                                           *
\*****************************************************************************/

व्योम sdhci_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा mmc_command *cmd;
	अचिन्हित दीर्घ flags;
	bool present;

	/* Firstly check card presence */
	present = mmc->ops->get_cd(mmc);

	spin_lock_irqsave(&host->lock, flags);

	sdhci_led_activate(host);

	अगर (sdhci_present_error(host, mrq->cmd, present))
		जाओ out_finish;

	cmd = sdhci_manual_cmd23(host, mrq) ? mrq->sbc : mrq->cmd;

	अगर (!sdhci_send_command_retry(host, cmd, flags))
		जाओ out_finish;

	spin_unlock_irqrestore(&host->lock, flags);

	वापस;

out_finish:
	sdhci_finish_mrq(host, mrq);
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_request);

पूर्णांक sdhci_request_atomic(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा mmc_command *cmd;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&host->lock, flags);

	अगर (sdhci_present_error(host, mrq->cmd, true)) अणु
		sdhci_finish_mrq(host, mrq);
		जाओ out_finish;
	पूर्ण

	cmd = sdhci_manual_cmd23(host, mrq) ? mrq->sbc : mrq->cmd;

	/*
	 * The HSQ may send a command in पूर्णांकerrupt context without polling
	 * the busy संकेतing, which means we should वापस BUSY अगर controller
	 * has not released inhibit bits to allow HSQ trying to send request
	 * again in non-atomic context. So we should not finish this request
	 * here.
	 */
	अगर (!sdhci_send_command(host, cmd))
		ret = -EBUSY;
	अन्यथा
		sdhci_led_activate(host);

out_finish:
	spin_unlock_irqrestore(&host->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_request_atomic);

व्योम sdhci_set_bus_width(काष्ठा sdhci_host *host, पूर्णांक width)
अणु
	u8 ctrl;

	ctrl = sdhci_पढ़ोb(host, SDHCI_HOST_CONTROL);
	अगर (width == MMC_BUS_WIDTH_8) अणु
		ctrl &= ~SDHCI_CTRL_4BITBUS;
		ctrl |= SDHCI_CTRL_8BITBUS;
	पूर्ण अन्यथा अणु
		अगर (host->mmc->caps & MMC_CAP_8_BIT_DATA)
			ctrl &= ~SDHCI_CTRL_8BITBUS;
		अगर (width == MMC_BUS_WIDTH_4)
			ctrl |= SDHCI_CTRL_4BITBUS;
		अन्यथा
			ctrl &= ~SDHCI_CTRL_4BITBUS;
	पूर्ण
	sdhci_ग_लिखोb(host, ctrl, SDHCI_HOST_CONTROL);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_set_bus_width);

व्योम sdhci_set_uhs_संकेतing(काष्ठा sdhci_host *host, अचिन्हित timing)
अणु
	u16 ctrl_2;

	ctrl_2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	/* Select Bus Speed Mode क्रम host */
	ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
	अगर ((timing == MMC_TIMING_MMC_HS200) ||
	    (timing == MMC_TIMING_UHS_SDR104))
		ctrl_2 |= SDHCI_CTRL_UHS_SDR104;
	अन्यथा अगर (timing == MMC_TIMING_UHS_SDR12)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR12;
	अन्यथा अगर (timing == MMC_TIMING_UHS_SDR25)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR25;
	अन्यथा अगर (timing == MMC_TIMING_UHS_SDR50)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR50;
	अन्यथा अगर ((timing == MMC_TIMING_UHS_DDR50) ||
		 (timing == MMC_TIMING_MMC_DDR52))
		ctrl_2 |= SDHCI_CTRL_UHS_DDR50;
	अन्यथा अगर (timing == MMC_TIMING_MMC_HS400)
		ctrl_2 |= SDHCI_CTRL_HS400; /* Non-standard */
	sdhci_ग_लिखोw(host, ctrl_2, SDHCI_HOST_CONTROL2);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_set_uhs_संकेतing);

व्योम sdhci_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	u8 ctrl;

	अगर (ios->घातer_mode == MMC_POWER_UNDEFINED)
		वापस;

	अगर (host->flags & SDHCI_DEVICE_DEAD) अणु
		अगर (!IS_ERR(mmc->supply.vmmc) &&
		    ios->घातer_mode == MMC_POWER_OFF)
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);
		वापस;
	पूर्ण

	/*
	 * Reset the chip on each घातer off.
	 * Should clear out any weird states.
	 */
	अगर (ios->घातer_mode == MMC_POWER_OFF) अणु
		sdhci_ग_लिखोl(host, 0, SDHCI_SIGNAL_ENABLE);
		sdhci_reinit(host);
	पूर्ण

	अगर (host->version >= SDHCI_SPEC_300 &&
		(ios->घातer_mode == MMC_POWER_UP) &&
		!(host->quirks2 & SDHCI_QUIRK2_PRESET_VALUE_BROKEN))
		sdhci_enable_preset_value(host, false);

	अगर (!ios->घड़ी || ios->घड़ी != host->घड़ी) अणु
		host->ops->set_घड़ी(host, ios->घड़ी);
		host->घड़ी = ios->घड़ी;

		अगर (host->quirks & SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK &&
		    host->घड़ी) अणु
			host->समयout_clk = mmc->actual_घड़ी ?
						mmc->actual_घड़ी / 1000 :
						host->घड़ी / 1000;
			mmc->max_busy_समयout =
				host->ops->get_max_समयout_count ?
				host->ops->get_max_समयout_count(host) :
				1 << 27;
			mmc->max_busy_समयout /= host->समयout_clk;
		पूर्ण
	पूर्ण

	अगर (host->ops->set_घातer)
		host->ops->set_घातer(host, ios->घातer_mode, ios->vdd);
	अन्यथा
		sdhci_set_घातer(host, ios->घातer_mode, ios->vdd);

	अगर (host->ops->platक्रमm_send_init_74_घड़ीs)
		host->ops->platक्रमm_send_init_74_घड़ीs(host, ios->घातer_mode);

	host->ops->set_bus_width(host, ios->bus_width);

	ctrl = sdhci_पढ़ोb(host, SDHCI_HOST_CONTROL);

	अगर (!(host->quirks & SDHCI_QUIRK_NO_HISPD_BIT)) अणु
		अगर (ios->timing == MMC_TIMING_SD_HS ||
		     ios->timing == MMC_TIMING_MMC_HS ||
		     ios->timing == MMC_TIMING_MMC_HS400 ||
		     ios->timing == MMC_TIMING_MMC_HS200 ||
		     ios->timing == MMC_TIMING_MMC_DDR52 ||
		     ios->timing == MMC_TIMING_UHS_SDR50 ||
		     ios->timing == MMC_TIMING_UHS_SDR104 ||
		     ios->timing == MMC_TIMING_UHS_DDR50 ||
		     ios->timing == MMC_TIMING_UHS_SDR25)
			ctrl |= SDHCI_CTRL_HISPD;
		अन्यथा
			ctrl &= ~SDHCI_CTRL_HISPD;
	पूर्ण

	अगर (host->version >= SDHCI_SPEC_300) अणु
		u16 clk, ctrl_2;

		अगर (!host->preset_enabled) अणु
			sdhci_ग_लिखोb(host, ctrl, SDHCI_HOST_CONTROL);
			/*
			 * We only need to set Driver Strength अगर the
			 * preset value enable is not set.
			 */
			ctrl_2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
			ctrl_2 &= ~SDHCI_CTRL_DRV_TYPE_MASK;
			अगर (ios->drv_type == MMC_SET_DRIVER_TYPE_A)
				ctrl_2 |= SDHCI_CTRL_DRV_TYPE_A;
			अन्यथा अगर (ios->drv_type == MMC_SET_DRIVER_TYPE_B)
				ctrl_2 |= SDHCI_CTRL_DRV_TYPE_B;
			अन्यथा अगर (ios->drv_type == MMC_SET_DRIVER_TYPE_C)
				ctrl_2 |= SDHCI_CTRL_DRV_TYPE_C;
			अन्यथा अगर (ios->drv_type == MMC_SET_DRIVER_TYPE_D)
				ctrl_2 |= SDHCI_CTRL_DRV_TYPE_D;
			अन्यथा अणु
				pr_warn("%s: invalid driver type, default to driver type B\n",
					mmc_hostname(mmc));
				ctrl_2 |= SDHCI_CTRL_DRV_TYPE_B;
			पूर्ण

			sdhci_ग_लिखोw(host, ctrl_2, SDHCI_HOST_CONTROL2);
		पूर्ण अन्यथा अणु
			/*
			 * According to SDHC Spec v3.00, अगर the Preset Value
			 * Enable in the Host Control 2 रेजिस्टर is set, we
			 * need to reset SD Clock Enable beक्रमe changing High
			 * Speed Enable to aव्योम generating घड़ी gliches.
			 */

			/* Reset SD Clock Enable */
			clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
			clk &= ~SDHCI_CLOCK_CARD_EN;
			sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);

			sdhci_ग_लिखोb(host, ctrl, SDHCI_HOST_CONTROL);

			/* Re-enable SD Clock */
			host->ops->set_घड़ी(host, host->घड़ी);
		पूर्ण

		/* Reset SD Clock Enable */
		clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
		clk &= ~SDHCI_CLOCK_CARD_EN;
		sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);

		host->ops->set_uhs_संकेतing(host, ios->timing);
		host->timing = ios->timing;

		अगर (!(host->quirks2 & SDHCI_QUIRK2_PRESET_VALUE_BROKEN) &&
				((ios->timing == MMC_TIMING_UHS_SDR12) ||
				 (ios->timing == MMC_TIMING_UHS_SDR25) ||
				 (ios->timing == MMC_TIMING_UHS_SDR50) ||
				 (ios->timing == MMC_TIMING_UHS_SDR104) ||
				 (ios->timing == MMC_TIMING_UHS_DDR50) ||
				 (ios->timing == MMC_TIMING_MMC_DDR52))) अणु
			u16 preset;

			sdhci_enable_preset_value(host, true);
			preset = sdhci_get_preset_value(host);
			ios->drv_type = FIELD_GET(SDHCI_PRESET_DRV_MASK,
						  preset);
		पूर्ण

		/* Re-enable SD Clock */
		host->ops->set_घड़ी(host, host->घड़ी);
	पूर्ण अन्यथा
		sdhci_ग_लिखोb(host, ctrl, SDHCI_HOST_CONTROL);

	/*
	 * Some (ENE) controllers go apeshit on some ios operation,
	 * संकेतling समयout and CRC errors even on CMD0. Resetting
	 * it on each ios seems to solve the problem.
	 */
	अगर (host->quirks & SDHCI_QUIRK_RESET_CMD_DATA_ON_IOS)
		sdhci_करो_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_set_ios);

अटल पूर्णांक sdhci_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	पूर्णांक gpio_cd = mmc_gpio_get_cd(mmc);

	अगर (host->flags & SDHCI_DEVICE_DEAD)
		वापस 0;

	/* If nonremovable, assume that the card is always present. */
	अगर (!mmc_card_is_removable(mmc))
		वापस 1;

	/*
	 * Try slot gpio detect, अगर defined it take precedence
	 * over build in controller functionality
	 */
	अगर (gpio_cd >= 0)
		वापस !!gpio_cd;

	/* If polling, assume that the card is always present. */
	अगर (host->quirks & SDHCI_QUIRK_BROKEN_CARD_DETECTION)
		वापस 1;

	/* Host native card detect */
	वापस !!(sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE) & SDHCI_CARD_PRESENT);
पूर्ण

अटल पूर्णांक sdhci_check_ro(काष्ठा sdhci_host *host)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक is_पढ़ोonly;

	spin_lock_irqsave(&host->lock, flags);

	अगर (host->flags & SDHCI_DEVICE_DEAD)
		is_पढ़ोonly = 0;
	अन्यथा अगर (host->ops->get_ro)
		is_पढ़ोonly = host->ops->get_ro(host);
	अन्यथा अगर (mmc_can_gpio_ro(host->mmc))
		is_पढ़ोonly = mmc_gpio_get_ro(host->mmc);
	अन्यथा
		is_पढ़ोonly = !(sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE)
				& SDHCI_WRITE_PROTECT);

	spin_unlock_irqrestore(&host->lock, flags);

	/* This quirk needs to be replaced by a callback-function later */
	वापस host->quirks & SDHCI_QUIRK_INVERTED_WRITE_PROTECT ?
		!is_पढ़ोonly : is_पढ़ोonly;
पूर्ण

#घोषणा SAMPLE_COUNT	5

अटल पूर्णांक sdhci_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	पूर्णांक i, ro_count;

	अगर (!(host->quirks & SDHCI_QUIRK_UNSTABLE_RO_DETECT))
		वापस sdhci_check_ro(host);

	ro_count = 0;
	क्रम (i = 0; i < SAMPLE_COUNT; i++) अणु
		अगर (sdhci_check_ro(host)) अणु
			अगर (++ro_count > SAMPLE_COUNT / 2)
				वापस 1;
		पूर्ण
		msleep(30);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sdhci_hw_reset(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);

	अगर (host->ops && host->ops->hw_reset)
		host->ops->hw_reset(host);
पूर्ण

अटल व्योम sdhci_enable_sdio_irq_nolock(काष्ठा sdhci_host *host, पूर्णांक enable)
अणु
	अगर (!(host->flags & SDHCI_DEVICE_DEAD)) अणु
		अगर (enable)
			host->ier |= SDHCI_INT_CARD_INT;
		अन्यथा
			host->ier &= ~SDHCI_INT_CARD_INT;

		sdhci_ग_लिखोl(host, host->ier, SDHCI_INT_ENABLE);
		sdhci_ग_लिखोl(host, host->ier, SDHCI_SIGNAL_ENABLE);
	पूर्ण
पूर्ण

व्योम sdhci_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;

	अगर (enable)
		pm_runसमय_get_noresume(mmc_dev(mmc));

	spin_lock_irqsave(&host->lock, flags);
	sdhci_enable_sdio_irq_nolock(host, enable);
	spin_unlock_irqrestore(&host->lock, flags);

	अगर (!enable)
		pm_runसमय_put_noidle(mmc_dev(mmc));
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_enable_sdio_irq);

अटल व्योम sdhci_ack_sdio_irq(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);
	sdhci_enable_sdio_irq_nolock(host, true);
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

पूर्णांक sdhci_start_संकेत_voltage_चयन(काष्ठा mmc_host *mmc,
				      काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	u16 ctrl;
	पूर्णांक ret;

	/*
	 * Signal Voltage Switching is only applicable क्रम Host Controllers
	 * v3.00 and above.
	 */
	अगर (host->version < SDHCI_SPEC_300)
		वापस 0;

	ctrl = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);

	चयन (ios->संकेत_voltage) अणु
	हाल MMC_SIGNAL_VOLTAGE_330:
		अगर (!(host->flags & SDHCI_SIGNALING_330))
			वापस -EINVAL;
		/* Set 1.8V Signal Enable in the Host Control2 रेजिस्टर to 0 */
		ctrl &= ~SDHCI_CTRL_VDD_180;
		sdhci_ग_लिखोw(host, ctrl, SDHCI_HOST_CONTROL2);

		अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
			ret = mmc_regulator_set_vqmmc(mmc, ios);
			अगर (ret < 0) अणु
				pr_warn("%s: Switching to 3.3V signalling voltage failed\n",
					mmc_hostname(mmc));
				वापस -EIO;
			पूर्ण
		पूर्ण
		/* Wait क्रम 5ms */
		usleep_range(5000, 5500);

		/* 3.3V regulator output should be stable within 5 ms */
		ctrl = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
		अगर (!(ctrl & SDHCI_CTRL_VDD_180))
			वापस 0;

		pr_warn("%s: 3.3V regulator output did not become stable\n",
			mmc_hostname(mmc));

		वापस -EAGAIN;
	हाल MMC_SIGNAL_VOLTAGE_180:
		अगर (!(host->flags & SDHCI_SIGNALING_180))
			वापस -EINVAL;
		अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
			ret = mmc_regulator_set_vqmmc(mmc, ios);
			अगर (ret < 0) अणु
				pr_warn("%s: Switching to 1.8V signalling voltage failed\n",
					mmc_hostname(mmc));
				वापस -EIO;
			पूर्ण
		पूर्ण

		/*
		 * Enable 1.8V Signal Enable in the Host Control2
		 * रेजिस्टर
		 */
		ctrl |= SDHCI_CTRL_VDD_180;
		sdhci_ग_लिखोw(host, ctrl, SDHCI_HOST_CONTROL2);

		/* Some controller need to करो more when चयनing */
		अगर (host->ops->voltage_चयन)
			host->ops->voltage_चयन(host);

		/* 1.8V regulator output should be stable within 5 ms */
		ctrl = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
		अगर (ctrl & SDHCI_CTRL_VDD_180)
			वापस 0;

		pr_warn("%s: 1.8V regulator output did not become stable\n",
			mmc_hostname(mmc));

		वापस -EAGAIN;
	हाल MMC_SIGNAL_VOLTAGE_120:
		अगर (!(host->flags & SDHCI_SIGNALING_120))
			वापस -EINVAL;
		अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
			ret = mmc_regulator_set_vqmmc(mmc, ios);
			अगर (ret < 0) अणु
				pr_warn("%s: Switching to 1.2V signalling voltage failed\n",
					mmc_hostname(mmc));
				वापस -EIO;
			पूर्ण
		पूर्ण
		वापस 0;
	शेष:
		/* No संकेत voltage चयन required */
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_start_संकेत_voltage_चयन);

अटल पूर्णांक sdhci_card_busy(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	u32 present_state;

	/* Check whether DAT[0] is 0 */
	present_state = sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE);

	वापस !(present_state & SDHCI_DATA_0_LVL_MASK);
पूर्ण

अटल पूर्णांक sdhci_prepare_hs400_tuning(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);
	host->flags |= SDHCI_HS400_TUNING;
	spin_unlock_irqrestore(&host->lock, flags);

	वापस 0;
पूर्ण

व्योम sdhci_start_tuning(काष्ठा sdhci_host *host)
अणु
	u16 ctrl;

	ctrl = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	ctrl |= SDHCI_CTRL_EXEC_TUNING;
	अगर (host->quirks2 & SDHCI_QUIRK2_TUNING_WORK_AROUND)
		ctrl |= SDHCI_CTRL_TUNED_CLK;
	sdhci_ग_लिखोw(host, ctrl, SDHCI_HOST_CONTROL2);

	/*
	 * As per the Host Controller spec v3.00, tuning command
	 * generates Buffer Read Ready पूर्णांकerrupt, so enable that.
	 *
	 * Note: The spec clearly says that when tuning sequence
	 * is being perक्रमmed, the controller करोes not generate
	 * पूर्णांकerrupts other than Buffer Read Ready पूर्णांकerrupt. But
	 * to make sure we करोn't hit a controller bug, we _only_
	 * enable Buffer Read Ready पूर्णांकerrupt here.
	 */
	sdhci_ग_लिखोl(host, SDHCI_INT_DATA_AVAIL, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, SDHCI_INT_DATA_AVAIL, SDHCI_SIGNAL_ENABLE);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_start_tuning);

व्योम sdhci_end_tuning(काष्ठा sdhci_host *host)
अणु
	sdhci_ग_लिखोl(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, host->ier, SDHCI_SIGNAL_ENABLE);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_end_tuning);

व्योम sdhci_reset_tuning(काष्ठा sdhci_host *host)
अणु
	u16 ctrl;

	ctrl = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	ctrl &= ~SDHCI_CTRL_TUNED_CLK;
	ctrl &= ~SDHCI_CTRL_EXEC_TUNING;
	sdhci_ग_लिखोw(host, ctrl, SDHCI_HOST_CONTROL2);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_reset_tuning);

व्योम sdhci_पात_tuning(काष्ठा sdhci_host *host, u32 opcode)
अणु
	sdhci_reset_tuning(host);

	sdhci_करो_reset(host, SDHCI_RESET_CMD);
	sdhci_करो_reset(host, SDHCI_RESET_DATA);

	sdhci_end_tuning(host);

	mmc_पात_tuning(host->mmc, opcode);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_पात_tuning);

/*
 * We use sdhci_send_tuning() because mmc_send_tuning() is not a good fit. SDHCI
 * tuning command करोes not have a data payload (or rather the hardware करोes it
 * स्वतःmatically) so mmc_send_tuning() will वापस -EIO. Also the tuning command
 * पूर्णांकerrupt setup is dअगरferent to other commands and there is no समयout
 * पूर्णांकerrupt so special handling is needed.
 */
व्योम sdhci_send_tuning(काष्ठा sdhci_host *host, u32 opcode)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	काष्ठा mmc_request mrq = अणुपूर्ण;
	अचिन्हित दीर्घ flags;
	u32 b = host->sdma_boundary;

	spin_lock_irqsave(&host->lock, flags);

	cmd.opcode = opcode;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_ADTC;
	cmd.mrq = &mrq;

	mrq.cmd = &cmd;
	/*
	 * In response to CMD19, the card sends 64 bytes of tuning
	 * block to the Host Controller. So we set the block size
	 * to 64 here.
	 */
	अगर (cmd.opcode == MMC_SEND_TUNING_BLOCK_HS200 &&
	    mmc->ios.bus_width == MMC_BUS_WIDTH_8)
		sdhci_ग_लिखोw(host, SDHCI_MAKE_BLKSZ(b, 128), SDHCI_BLOCK_SIZE);
	अन्यथा
		sdhci_ग_लिखोw(host, SDHCI_MAKE_BLKSZ(b, 64), SDHCI_BLOCK_SIZE);

	/*
	 * The tuning block is sent by the card to the host controller.
	 * So we set the TRNS_READ bit in the Transfer Mode रेजिस्टर.
	 * This also takes care of setting DMA Enable and Multi Block
	 * Select in the same रेजिस्टर to 0.
	 */
	sdhci_ग_लिखोw(host, SDHCI_TRNS_READ, SDHCI_TRANSFER_MODE);

	अगर (!sdhci_send_command_retry(host, &cmd, flags)) अणु
		spin_unlock_irqrestore(&host->lock, flags);
		host->tuning_करोne = 0;
		वापस;
	पूर्ण

	host->cmd = शून्य;

	sdhci_del_समयr(host, &mrq);

	host->tuning_करोne = 0;

	spin_unlock_irqrestore(&host->lock, flags);

	/* Wait क्रम Buffer Read Ready पूर्णांकerrupt */
	रुको_event_समयout(host->buf_पढ़ोy_पूर्णांक, (host->tuning_करोne == 1),
			   msecs_to_jअगरfies(50));

पूर्ण
EXPORT_SYMBOL_GPL(sdhci_send_tuning);

अटल पूर्णांक __sdhci_execute_tuning(काष्ठा sdhci_host *host, u32 opcode)
अणु
	पूर्णांक i;

	/*
	 * Issue opcode repeatedly till Execute Tuning is set to 0 or the number
	 * of loops reaches tuning loop count.
	 */
	क्रम (i = 0; i < host->tuning_loop_count; i++) अणु
		u16 ctrl;

		sdhci_send_tuning(host, opcode);

		अगर (!host->tuning_करोne) अणु
			pr_debug("%s: Tuning timeout, falling back to fixed sampling clock\n",
				 mmc_hostname(host->mmc));
			sdhci_पात_tuning(host, opcode);
			वापस -ETIMEDOUT;
		पूर्ण

		/* Spec करोes not require a delay between tuning cycles */
		अगर (host->tuning_delay > 0)
			mdelay(host->tuning_delay);

		ctrl = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
		अगर (!(ctrl & SDHCI_CTRL_EXEC_TUNING)) अणु
			अगर (ctrl & SDHCI_CTRL_TUNED_CLK)
				वापस 0; /* Success! */
			अवरोध;
		पूर्ण

	पूर्ण

	pr_info("%s: Tuning failed, falling back to fixed sampling clock\n",
		mmc_hostname(host->mmc));
	sdhci_reset_tuning(host);
	वापस -EAGAIN;
पूर्ण

पूर्णांक sdhci_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक tuning_count = 0;
	bool hs400_tuning;

	hs400_tuning = host->flags & SDHCI_HS400_TUNING;

	अगर (host->tuning_mode == SDHCI_TUNING_MODE_1)
		tuning_count = host->tuning_count;

	/*
	 * The Host Controller needs tuning in हाल of SDR104 and DDR50
	 * mode, and क्रम SDR50 mode when Use Tuning क्रम SDR50 is set in
	 * the Capabilities रेजिस्टर.
	 * If the Host Controller supports the HS200 mode then the
	 * tuning function has to be executed.
	 */
	चयन (host->timing) अणु
	/* HS400 tuning is करोne in HS200 mode */
	हाल MMC_TIMING_MMC_HS400:
		err = -EINVAL;
		जाओ out;

	हाल MMC_TIMING_MMC_HS200:
		/*
		 * Periodic re-tuning क्रम HS400 is not expected to be needed, so
		 * disable it here.
		 */
		अगर (hs400_tuning)
			tuning_count = 0;
		अवरोध;

	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_UHS_DDR50:
		अवरोध;

	हाल MMC_TIMING_UHS_SDR50:
		अगर (host->flags & SDHCI_SDR50_NEEDS_TUNING)
			अवरोध;
		fallthrough;

	शेष:
		जाओ out;
	पूर्ण

	अगर (host->ops->platक्रमm_execute_tuning) अणु
		err = host->ops->platक्रमm_execute_tuning(host, opcode);
		जाओ out;
	पूर्ण

	mmc->retune_period = tuning_count;

	अगर (host->tuning_delay < 0)
		host->tuning_delay = opcode == MMC_SEND_TUNING_BLOCK;

	sdhci_start_tuning(host);

	host->tuning_err = __sdhci_execute_tuning(host, opcode);

	sdhci_end_tuning(host);
out:
	host->flags &= ~SDHCI_HS400_TUNING;

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_execute_tuning);

अटल व्योम sdhci_enable_preset_value(काष्ठा sdhci_host *host, bool enable)
अणु
	/* Host Controller v3.00 defines preset value रेजिस्टरs */
	अगर (host->version < SDHCI_SPEC_300)
		वापस;

	/*
	 * We only enable or disable Preset Value अगर they are not alपढ़ोy
	 * enabled or disabled respectively. Otherwise, we bail out.
	 */
	अगर (host->preset_enabled != enable) अणु
		u16 ctrl = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);

		अगर (enable)
			ctrl |= SDHCI_CTRL_PRESET_VAL_ENABLE;
		अन्यथा
			ctrl &= ~SDHCI_CTRL_PRESET_VAL_ENABLE;

		sdhci_ग_लिखोw(host, ctrl, SDHCI_HOST_CONTROL2);

		अगर (enable)
			host->flags |= SDHCI_PV_ENABLED;
		अन्यथा
			host->flags &= ~SDHCI_PV_ENABLED;

		host->preset_enabled = enable;
	पूर्ण
पूर्ण

अटल व्योम sdhci_post_req(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq,
				पूर्णांक err)
अणु
	काष्ठा mmc_data *data = mrq->data;

	अगर (data->host_cookie != COOKIE_UNMAPPED)
		dma_unmap_sg(mmc_dev(mmc), data->sg, data->sg_len,
			     mmc_get_dma_dir(data));

	data->host_cookie = COOKIE_UNMAPPED;
पूर्ण

अटल व्योम sdhci_pre_req(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);

	mrq->data->host_cookie = COOKIE_UNMAPPED;

	/*
	 * No pre-mapping in the pre hook अगर we're using the bounce buffer,
	 * क्रम that we would need two bounce buffers since one buffer is
	 * in flight when this is getting called.
	 */
	अगर (host->flags & SDHCI_REQ_USE_DMA && !host->bounce_buffer)
		sdhci_pre_dma_transfer(host, mrq->data, COOKIE_PRE_MAPPED);
पूर्ण

अटल व्योम sdhci_error_out_mrqs(काष्ठा sdhci_host *host, पूर्णांक err)
अणु
	अगर (host->data_cmd) अणु
		host->data_cmd->error = err;
		sdhci_finish_mrq(host, host->data_cmd->mrq);
	पूर्ण

	अगर (host->cmd) अणु
		host->cmd->error = err;
		sdhci_finish_mrq(host, host->cmd->mrq);
	पूर्ण
पूर्ण

अटल व्योम sdhci_card_event(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;
	पूर्णांक present;

	/* First check अगर client has provided their own card event */
	अगर (host->ops->card_event)
		host->ops->card_event(host);

	present = mmc->ops->get_cd(mmc);

	spin_lock_irqsave(&host->lock, flags);

	/* Check sdhci_has_requests() first in हाल we are runसमय suspended */
	अगर (sdhci_has_requests(host) && !present) अणु
		pr_err("%s: Card removed during transfer!\n",
			mmc_hostname(mmc));
		pr_err("%s: Resetting controller.\n",
			mmc_hostname(mmc));

		sdhci_करो_reset(host, SDHCI_RESET_CMD);
		sdhci_करो_reset(host, SDHCI_RESET_DATA);

		sdhci_error_out_mrqs(host, -ENOMEDIUM);
	पूर्ण

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops sdhci_ops = अणु
	.request	= sdhci_request,
	.post_req	= sdhci_post_req,
	.pre_req	= sdhci_pre_req,
	.set_ios	= sdhci_set_ios,
	.get_cd		= sdhci_get_cd,
	.get_ro		= sdhci_get_ro,
	.hw_reset	= sdhci_hw_reset,
	.enable_sdio_irq = sdhci_enable_sdio_irq,
	.ack_sdio_irq    = sdhci_ack_sdio_irq,
	.start_संकेत_voltage_चयन	= sdhci_start_संकेत_voltage_चयन,
	.prepare_hs400_tuning		= sdhci_prepare_hs400_tuning,
	.execute_tuning			= sdhci_execute_tuning,
	.card_event			= sdhci_card_event,
	.card_busy	= sdhci_card_busy,
पूर्ण;

/*****************************************************************************\
 *                                                                           *
 * Request करोne                                                              *
 *                                                                           *
\*****************************************************************************/

अटल bool sdhci_request_करोne(काष्ठा sdhci_host *host)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mmc_request *mrq;
	पूर्णांक i;

	spin_lock_irqsave(&host->lock, flags);

	क्रम (i = 0; i < SDHCI_MAX_MRQS; i++) अणु
		mrq = host->mrqs_करोne[i];
		अगर (mrq)
			अवरोध;
	पूर्ण

	अगर (!mrq) अणु
		spin_unlock_irqrestore(&host->lock, flags);
		वापस true;
	पूर्ण

	/*
	 * The controller needs a reset of पूर्णांकernal state machines
	 * upon error conditions.
	 */
	अगर (sdhci_needs_reset(host, mrq)) अणु
		/*
		 * Do not finish until command and data lines are available क्रम
		 * reset. Note there can only be one other mrq, so it cannot
		 * also be in mrqs_करोne, otherwise host->cmd and host->data_cmd
		 * would both be null.
		 */
		अगर (host->cmd || host->data_cmd) अणु
			spin_unlock_irqrestore(&host->lock, flags);
			वापस true;
		पूर्ण

		/* Some controllers need this kick or reset won't work here */
		अगर (host->quirks & SDHCI_QUIRK_CLOCK_BEFORE_RESET)
			/* This is to क्रमce an update */
			host->ops->set_घड़ी(host, host->घड़ी);

		/*
		 * Spec says we should करो both at the same समय, but Ricoh
		 * controllers करो not like that.
		 */
		sdhci_करो_reset(host, SDHCI_RESET_CMD);
		sdhci_करो_reset(host, SDHCI_RESET_DATA);

		host->pending_reset = false;
	पूर्ण

	/*
	 * Always unmap the data buffers अगर they were mapped by
	 * sdhci_prepare_data() whenever we finish with a request.
	 * This aव्योमs leaking DMA mappings on error.
	 */
	अगर (host->flags & SDHCI_REQ_USE_DMA) अणु
		काष्ठा mmc_data *data = mrq->data;

		अगर (host->use_बाह्यal_dma && data &&
		    (mrq->cmd->error || data->error)) अणु
			काष्ठा dma_chan *chan = sdhci_बाह्यal_dma_channel(host, data);

			host->mrqs_करोne[i] = शून्य;
			spin_unlock_irqrestore(&host->lock, flags);
			dmaengine_terminate_sync(chan);
			spin_lock_irqsave(&host->lock, flags);
			sdhci_set_mrq_करोne(host, mrq);
		पूर्ण

		अगर (data && data->host_cookie == COOKIE_MAPPED) अणु
			अगर (host->bounce_buffer) अणु
				/*
				 * On पढ़ोs, copy the bounced data पूर्णांकo the
				 * sglist
				 */
				अगर (mmc_get_dma_dir(data) == DMA_FROM_DEVICE) अणु
					अचिन्हित पूर्णांक length = data->bytes_xfered;

					अगर (length > host->bounce_buffer_size) अणु
						pr_err("%s: bounce buffer is %u bytes but DMA claims to have transferred %u bytes\n",
						       mmc_hostname(host->mmc),
						       host->bounce_buffer_size,
						       data->bytes_xfered);
						/* Cap it करोwn and जारी */
						length = host->bounce_buffer_size;
					पूर्ण
					dma_sync_single_क्रम_cpu(
						mmc_dev(host->mmc),
						host->bounce_addr,
						host->bounce_buffer_size,
						DMA_FROM_DEVICE);
					sg_copy_from_buffer(data->sg,
						data->sg_len,
						host->bounce_buffer,
						length);
				पूर्ण अन्यथा अणु
					/* No copying, just चयन ownership */
					dma_sync_single_क्रम_cpu(
						mmc_dev(host->mmc),
						host->bounce_addr,
						host->bounce_buffer_size,
						mmc_get_dma_dir(data));
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Unmap the raw data */
				dma_unmap_sg(mmc_dev(host->mmc), data->sg,
					     data->sg_len,
					     mmc_get_dma_dir(data));
			पूर्ण
			data->host_cookie = COOKIE_UNMAPPED;
		पूर्ण
	पूर्ण

	host->mrqs_करोne[i] = शून्य;

	spin_unlock_irqrestore(&host->lock, flags);

	अगर (host->ops->request_करोne)
		host->ops->request_करोne(host, mrq);
	अन्यथा
		mmc_request_करोne(host->mmc, mrq);

	वापस false;
पूर्ण

अटल व्योम sdhci_complete_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sdhci_host *host = container_of(work, काष्ठा sdhci_host,
					       complete_work);

	जबतक (!sdhci_request_करोne(host))
		;
पूर्ण

अटल व्योम sdhci_समयout_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sdhci_host *host;
	अचिन्हित दीर्घ flags;

	host = from_समयr(host, t, समयr);

	spin_lock_irqsave(&host->lock, flags);

	अगर (host->cmd && !sdhci_data_line_cmd(host->cmd)) अणु
		pr_err("%s: Timeout waiting for hardware cmd interrupt.\n",
		       mmc_hostname(host->mmc));
		sdhci_dumpregs(host);

		host->cmd->error = -ETIMEDOUT;
		sdhci_finish_mrq(host, host->cmd->mrq);
	पूर्ण

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम sdhci_समयout_data_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sdhci_host *host;
	अचिन्हित दीर्घ flags;

	host = from_समयr(host, t, data_समयr);

	spin_lock_irqsave(&host->lock, flags);

	अगर (host->data || host->data_cmd ||
	    (host->cmd && sdhci_data_line_cmd(host->cmd))) अणु
		pr_err("%s: Timeout waiting for hardware interrupt.\n",
		       mmc_hostname(host->mmc));
		sdhci_dumpregs(host);

		अगर (host->data) अणु
			host->data->error = -ETIMEDOUT;
			__sdhci_finish_data(host, true);
			queue_work(host->complete_wq, &host->complete_work);
		पूर्ण अन्यथा अगर (host->data_cmd) अणु
			host->data_cmd->error = -ETIMEDOUT;
			sdhci_finish_mrq(host, host->data_cmd->mrq);
		पूर्ण अन्यथा अणु
			host->cmd->error = -ETIMEDOUT;
			sdhci_finish_mrq(host, host->cmd->mrq);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

/*****************************************************************************\
 *                                                                           *
 * Interrupt handling                                                        *
 *                                                                           *
\*****************************************************************************/

अटल व्योम sdhci_cmd_irq(काष्ठा sdhci_host *host, u32 पूर्णांकmask, u32 *पूर्णांकmask_p)
अणु
	/* Handle स्वतः-CMD12 error */
	अगर (पूर्णांकmask & SDHCI_INT_AUTO_CMD_ERR && host->data_cmd) अणु
		काष्ठा mmc_request *mrq = host->data_cmd->mrq;
		u16 स्वतः_cmd_status = sdhci_पढ़ोw(host, SDHCI_AUTO_CMD_STATUS);
		पूर्णांक data_err_bit = (स्वतः_cmd_status & SDHCI_AUTO_CMD_TIMEOUT) ?
				   SDHCI_INT_DATA_TIMEOUT :
				   SDHCI_INT_DATA_CRC;

		/* Treat स्वतः-CMD12 error the same as data error */
		अगर (!mrq->sbc && (host->flags & SDHCI_AUTO_CMD12)) अणु
			*पूर्णांकmask_p |= data_err_bit;
			वापस;
		पूर्ण
	पूर्ण

	अगर (!host->cmd) अणु
		/*
		 * SDHCI recovers from errors by resetting the cmd and data
		 * circuits.  Until that is करोne, there very well might be more
		 * पूर्णांकerrupts, so ignore them in that हाल.
		 */
		अगर (host->pending_reset)
			वापस;
		pr_err("%s: Got command interrupt 0x%08x even though no command operation was in progress.\n",
		       mmc_hostname(host->mmc), (अचिन्हित)पूर्णांकmask);
		sdhci_dumpregs(host);
		वापस;
	पूर्ण

	अगर (पूर्णांकmask & (SDHCI_INT_TIMEOUT | SDHCI_INT_CRC |
		       SDHCI_INT_END_BIT | SDHCI_INT_INDEX)) अणु
		अगर (पूर्णांकmask & SDHCI_INT_TIMEOUT)
			host->cmd->error = -ETIMEDOUT;
		अन्यथा
			host->cmd->error = -EILSEQ;

		/* Treat data command CRC error the same as data CRC error */
		अगर (host->cmd->data &&
		    (पूर्णांकmask & (SDHCI_INT_CRC | SDHCI_INT_TIMEOUT)) ==
		     SDHCI_INT_CRC) अणु
			host->cmd = शून्य;
			*पूर्णांकmask_p |= SDHCI_INT_DATA_CRC;
			वापस;
		पूर्ण

		__sdhci_finish_mrq(host, host->cmd->mrq);
		वापस;
	पूर्ण

	/* Handle स्वतः-CMD23 error */
	अगर (पूर्णांकmask & SDHCI_INT_AUTO_CMD_ERR) अणु
		काष्ठा mmc_request *mrq = host->cmd->mrq;
		u16 स्वतः_cmd_status = sdhci_पढ़ोw(host, SDHCI_AUTO_CMD_STATUS);
		पूर्णांक err = (स्वतः_cmd_status & SDHCI_AUTO_CMD_TIMEOUT) ?
			  -ETIMEDOUT :
			  -EILSEQ;

		अगर (mrq->sbc && (host->flags & SDHCI_AUTO_CMD23)) अणु
			mrq->sbc->error = err;
			__sdhci_finish_mrq(host, mrq);
			वापस;
		पूर्ण
	पूर्ण

	अगर (पूर्णांकmask & SDHCI_INT_RESPONSE)
		sdhci_finish_command(host);
पूर्ण

अटल व्योम sdhci_adma_show_error(काष्ठा sdhci_host *host)
अणु
	व्योम *desc = host->adma_table;
	dma_addr_t dma = host->adma_addr;

	sdhci_dumpregs(host);

	जबतक (true) अणु
		काष्ठा sdhci_adma2_64_desc *dma_desc = desc;

		अगर (host->flags & SDHCI_USE_64_BIT_DMA)
			SDHCI_DUMP("%08llx: DMA 0x%08x%08x, LEN 0x%04x, Attr=0x%02x\n",
			    (अचिन्हित दीर्घ दीर्घ)dma,
			    le32_to_cpu(dma_desc->addr_hi),
			    le32_to_cpu(dma_desc->addr_lo),
			    le16_to_cpu(dma_desc->len),
			    le16_to_cpu(dma_desc->cmd));
		अन्यथा
			SDHCI_DUMP("%08llx: DMA 0x%08x, LEN 0x%04x, Attr=0x%02x\n",
			    (अचिन्हित दीर्घ दीर्घ)dma,
			    le32_to_cpu(dma_desc->addr_lo),
			    le16_to_cpu(dma_desc->len),
			    le16_to_cpu(dma_desc->cmd));

		desc += host->desc_sz;
		dma += host->desc_sz;

		अगर (dma_desc->cmd & cpu_to_le16(ADMA2_END))
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sdhci_data_irq(काष्ठा sdhci_host *host, u32 पूर्णांकmask)
अणु
	u32 command;

	/* CMD19 generates _only_ Buffer Read Ready पूर्णांकerrupt */
	अगर (पूर्णांकmask & SDHCI_INT_DATA_AVAIL) अणु
		command = SDHCI_GET_CMD(sdhci_पढ़ोw(host, SDHCI_COMMAND));
		अगर (command == MMC_SEND_TUNING_BLOCK ||
		    command == MMC_SEND_TUNING_BLOCK_HS200) अणु
			host->tuning_करोne = 1;
			wake_up(&host->buf_पढ़ोy_पूर्णांक);
			वापस;
		पूर्ण
	पूर्ण

	अगर (!host->data) अणु
		काष्ठा mmc_command *data_cmd = host->data_cmd;

		/*
		 * The "data complete" पूर्णांकerrupt is also used to
		 * indicate that a busy state has ended. See comment
		 * above in sdhci_cmd_irq().
		 */
		अगर (data_cmd && (data_cmd->flags & MMC_RSP_BUSY)) अणु
			अगर (पूर्णांकmask & SDHCI_INT_DATA_TIMEOUT) अणु
				host->data_cmd = शून्य;
				data_cmd->error = -ETIMEDOUT;
				__sdhci_finish_mrq(host, data_cmd->mrq);
				वापस;
			पूर्ण
			अगर (पूर्णांकmask & SDHCI_INT_DATA_END) अणु
				host->data_cmd = शून्य;
				/*
				 * Some cards handle busy-end पूर्णांकerrupt
				 * beक्रमe the command completed, so make
				 * sure we करो things in the proper order.
				 */
				अगर (host->cmd == data_cmd)
					वापस;

				__sdhci_finish_mrq(host, data_cmd->mrq);
				वापस;
			पूर्ण
		पूर्ण

		/*
		 * SDHCI recovers from errors by resetting the cmd and data
		 * circuits. Until that is करोne, there very well might be more
		 * पूर्णांकerrupts, so ignore them in that हाल.
		 */
		अगर (host->pending_reset)
			वापस;

		pr_err("%s: Got data interrupt 0x%08x even though no data operation was in progress.\n",
		       mmc_hostname(host->mmc), (अचिन्हित)पूर्णांकmask);
		sdhci_dumpregs(host);

		वापस;
	पूर्ण

	अगर (पूर्णांकmask & SDHCI_INT_DATA_TIMEOUT)
		host->data->error = -ETIMEDOUT;
	अन्यथा अगर (पूर्णांकmask & SDHCI_INT_DATA_END_BIT)
		host->data->error = -EILSEQ;
	अन्यथा अगर ((पूर्णांकmask & SDHCI_INT_DATA_CRC) &&
		SDHCI_GET_CMD(sdhci_पढ़ोw(host, SDHCI_COMMAND))
			!= MMC_BUS_TEST_R)
		host->data->error = -EILSEQ;
	अन्यथा अगर (पूर्णांकmask & SDHCI_INT_ADMA_ERROR) अणु
		pr_err("%s: ADMA error: 0x%08x\n", mmc_hostname(host->mmc),
		       पूर्णांकmask);
		sdhci_adma_show_error(host);
		host->data->error = -EIO;
		अगर (host->ops->adma_workaround)
			host->ops->adma_workaround(host, पूर्णांकmask);
	पूर्ण

	अगर (host->data->error)
		sdhci_finish_data(host);
	अन्यथा अणु
		अगर (पूर्णांकmask & (SDHCI_INT_DATA_AVAIL | SDHCI_INT_SPACE_AVAIL))
			sdhci_transfer_pio(host);

		/*
		 * We currently करोn't करो anything fancy with DMA
		 * boundaries, but as we can't disable the feature
		 * we need to at least restart the transfer.
		 *
		 * According to the spec sdhci_पढ़ोl(host, SDHCI_DMA_ADDRESS)
		 * should वापस a valid address to जारी from, but as
		 * some controllers are faulty, करोn't trust them.
		 */
		अगर (पूर्णांकmask & SDHCI_INT_DMA_END) अणु
			dma_addr_t dmastart, dmanow;

			dmastart = sdhci_sdma_address(host);
			dmanow = dmastart + host->data->bytes_xfered;
			/*
			 * Force update to the next DMA block boundary.
			 */
			dmanow = (dmanow &
				~((dma_addr_t)SDHCI_DEFAULT_BOUNDARY_SIZE - 1)) +
				SDHCI_DEFAULT_BOUNDARY_SIZE;
			host->data->bytes_xfered = dmanow - dmastart;
			DBG("DMA base %pad, transferred 0x%06x bytes, next %pad\n",
			    &dmastart, host->data->bytes_xfered, &dmanow);
			sdhci_set_sdma_addr(host, dmanow);
		पूर्ण

		अगर (पूर्णांकmask & SDHCI_INT_DATA_END) अणु
			अगर (host->cmd == host->data_cmd) अणु
				/*
				 * Data managed to finish beक्रमe the
				 * command completed. Make sure we करो
				 * things in the proper order.
				 */
				host->data_early = 1;
			पूर्ण अन्यथा अणु
				sdhci_finish_data(host);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत bool sdhci_defer_करोne(काष्ठा sdhci_host *host,
				    काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmc_data *data = mrq->data;

	वापस host->pending_reset || host->always_defer_करोne ||
	       ((host->flags & SDHCI_REQ_USE_DMA) && data &&
		data->host_cookie == COOKIE_MAPPED);
पूर्ण

अटल irqवापस_t sdhci_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mmc_request *mrqs_करोne[SDHCI_MAX_MRQS] = अणु0पूर्ण;
	irqवापस_t result = IRQ_NONE;
	काष्ठा sdhci_host *host = dev_id;
	u32 पूर्णांकmask, mask, unexpected = 0;
	पूर्णांक max_loops = 16;
	पूर्णांक i;

	spin_lock(&host->lock);

	अगर (host->runसमय_suspended) अणु
		spin_unlock(&host->lock);
		वापस IRQ_NONE;
	पूर्ण

	पूर्णांकmask = sdhci_पढ़ोl(host, SDHCI_INT_STATUS);
	अगर (!पूर्णांकmask || पूर्णांकmask == 0xffffffff) अणु
		result = IRQ_NONE;
		जाओ out;
	पूर्ण

	करो अणु
		DBG("IRQ status 0x%08x\n", पूर्णांकmask);

		अगर (host->ops->irq) अणु
			पूर्णांकmask = host->ops->irq(host, पूर्णांकmask);
			अगर (!पूर्णांकmask)
				जाओ cont;
		पूर्ण

		/* Clear selected पूर्णांकerrupts. */
		mask = पूर्णांकmask & (SDHCI_INT_CMD_MASK | SDHCI_INT_DATA_MASK |
				  SDHCI_INT_BUS_POWER);
		sdhci_ग_लिखोl(host, mask, SDHCI_INT_STATUS);

		अगर (पूर्णांकmask & (SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE)) अणु
			u32 present = sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE) &
				      SDHCI_CARD_PRESENT;

			/*
			 * There is a observation on i.mx esdhc.  INSERT
			 * bit will be immediately set again when it माला_लो
			 * cleared, अगर a card is inserted.  We have to mask
			 * the irq to prevent पूर्णांकerrupt storm which will
			 * मुक्तze the प्रणाली.  And the REMOVE माला_लो the
			 * same situation.
			 *
			 * More testing are needed here to ensure it works
			 * क्रम other platक्रमms though.
			 */
			host->ier &= ~(SDHCI_INT_CARD_INSERT |
				       SDHCI_INT_CARD_REMOVE);
			host->ier |= present ? SDHCI_INT_CARD_REMOVE :
					       SDHCI_INT_CARD_INSERT;
			sdhci_ग_लिखोl(host, host->ier, SDHCI_INT_ENABLE);
			sdhci_ग_लिखोl(host, host->ier, SDHCI_SIGNAL_ENABLE);

			sdhci_ग_लिखोl(host, पूर्णांकmask & (SDHCI_INT_CARD_INSERT |
				     SDHCI_INT_CARD_REMOVE), SDHCI_INT_STATUS);

			host->thपढ़ो_isr |= पूर्णांकmask & (SDHCI_INT_CARD_INSERT |
						       SDHCI_INT_CARD_REMOVE);
			result = IRQ_WAKE_THREAD;
		पूर्ण

		अगर (पूर्णांकmask & SDHCI_INT_CMD_MASK)
			sdhci_cmd_irq(host, पूर्णांकmask & SDHCI_INT_CMD_MASK, &पूर्णांकmask);

		अगर (पूर्णांकmask & SDHCI_INT_DATA_MASK)
			sdhci_data_irq(host, पूर्णांकmask & SDHCI_INT_DATA_MASK);

		अगर (पूर्णांकmask & SDHCI_INT_BUS_POWER)
			pr_err("%s: Card is consuming too much power!\n",
				mmc_hostname(host->mmc));

		अगर (पूर्णांकmask & SDHCI_INT_RETUNE)
			mmc_retune_needed(host->mmc);

		अगर ((पूर्णांकmask & SDHCI_INT_CARD_INT) &&
		    (host->ier & SDHCI_INT_CARD_INT)) अणु
			sdhci_enable_sdio_irq_nolock(host, false);
			sdio_संकेत_irq(host->mmc);
		पूर्ण

		पूर्णांकmask &= ~(SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE |
			     SDHCI_INT_CMD_MASK | SDHCI_INT_DATA_MASK |
			     SDHCI_INT_ERROR | SDHCI_INT_BUS_POWER |
			     SDHCI_INT_RETUNE | SDHCI_INT_CARD_INT);

		अगर (पूर्णांकmask) अणु
			unexpected |= पूर्णांकmask;
			sdhci_ग_लिखोl(host, पूर्णांकmask, SDHCI_INT_STATUS);
		पूर्ण
cont:
		अगर (result == IRQ_NONE)
			result = IRQ_HANDLED;

		पूर्णांकmask = sdhci_पढ़ोl(host, SDHCI_INT_STATUS);
	पूर्ण जबतक (पूर्णांकmask && --max_loops);

	/* Determine अगर mrqs can be completed immediately */
	क्रम (i = 0; i < SDHCI_MAX_MRQS; i++) अणु
		काष्ठा mmc_request *mrq = host->mrqs_करोne[i];

		अगर (!mrq)
			जारी;

		अगर (sdhci_defer_करोne(host, mrq)) अणु
			result = IRQ_WAKE_THREAD;
		पूर्ण अन्यथा अणु
			mrqs_करोne[i] = mrq;
			host->mrqs_करोne[i] = शून्य;
		पूर्ण
	पूर्ण
out:
	अगर (host->deferred_cmd)
		result = IRQ_WAKE_THREAD;

	spin_unlock(&host->lock);

	/* Process mrqs पढ़ोy क्रम immediate completion */
	क्रम (i = 0; i < SDHCI_MAX_MRQS; i++) अणु
		अगर (!mrqs_करोne[i])
			जारी;

		अगर (host->ops->request_करोne)
			host->ops->request_करोne(host, mrqs_करोne[i]);
		अन्यथा
			mmc_request_करोne(host->mmc, mrqs_करोne[i]);
	पूर्ण

	अगर (unexpected) अणु
		pr_err("%s: Unexpected interrupt 0x%08x.\n",
			   mmc_hostname(host->mmc), unexpected);
		sdhci_dumpregs(host);
	पूर्ण

	वापस result;
पूर्ण

अटल irqवापस_t sdhci_thपढ़ो_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sdhci_host *host = dev_id;
	काष्ठा mmc_command *cmd;
	अचिन्हित दीर्घ flags;
	u32 isr;

	जबतक (!sdhci_request_करोne(host))
		;

	spin_lock_irqsave(&host->lock, flags);

	isr = host->thपढ़ो_isr;
	host->thपढ़ो_isr = 0;

	cmd = host->deferred_cmd;
	अगर (cmd && !sdhci_send_command_retry(host, cmd, flags))
		sdhci_finish_mrq(host, cmd->mrq);

	spin_unlock_irqrestore(&host->lock, flags);

	अगर (isr & (SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE)) अणु
		काष्ठा mmc_host *mmc = host->mmc;

		mmc->ops->card_event(mmc);
		mmc_detect_change(mmc, msecs_to_jअगरfies(200));
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*****************************************************************************\
 *                                                                           *
 * Suspend/resume                                                            *
 *                                                                           *
\*****************************************************************************/

#अगर_घोषित CONFIG_PM

अटल bool sdhci_cd_irq_can_wakeup(काष्ठा sdhci_host *host)
अणु
	वापस mmc_card_is_removable(host->mmc) &&
	       !(host->quirks & SDHCI_QUIRK_BROKEN_CARD_DETECTION) &&
	       !mmc_can_gpio_cd(host->mmc);
पूर्ण

/*
 * To enable wakeup events, the corresponding events have to be enabled in
 * the Interrupt Status Enable रेजिस्टर too. See 'Table 1-6: Wakeup Signal
 * Table' in the SD Host Controller Standard Specअगरication.
 * It is useless to restore SDHCI_INT_ENABLE state in
 * sdhci_disable_irq_wakeups() since it will be set by
 * sdhci_enable_card_detection() or sdhci_init().
 */
अटल bool sdhci_enable_irq_wakeups(काष्ठा sdhci_host *host)
अणु
	u8 mask = SDHCI_WAKE_ON_INSERT | SDHCI_WAKE_ON_REMOVE |
		  SDHCI_WAKE_ON_INT;
	u32 irq_val = 0;
	u8 wake_val = 0;
	u8 val;

	अगर (sdhci_cd_irq_can_wakeup(host)) अणु
		wake_val |= SDHCI_WAKE_ON_INSERT | SDHCI_WAKE_ON_REMOVE;
		irq_val |= SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE;
	पूर्ण

	अगर (mmc_card_wake_sdio_irq(host->mmc)) अणु
		wake_val |= SDHCI_WAKE_ON_INT;
		irq_val |= SDHCI_INT_CARD_INT;
	पूर्ण

	अगर (!irq_val)
		वापस false;

	val = sdhci_पढ़ोb(host, SDHCI_WAKE_UP_CONTROL);
	val &= ~mask;
	val |= wake_val;
	sdhci_ग_लिखोb(host, val, SDHCI_WAKE_UP_CONTROL);

	sdhci_ग_लिखोl(host, irq_val, SDHCI_INT_ENABLE);

	host->irq_wake_enabled = !enable_irq_wake(host->irq);

	वापस host->irq_wake_enabled;
पूर्ण

अटल व्योम sdhci_disable_irq_wakeups(काष्ठा sdhci_host *host)
अणु
	u8 val;
	u8 mask = SDHCI_WAKE_ON_INSERT | SDHCI_WAKE_ON_REMOVE
			| SDHCI_WAKE_ON_INT;

	val = sdhci_पढ़ोb(host, SDHCI_WAKE_UP_CONTROL);
	val &= ~mask;
	sdhci_ग_लिखोb(host, val, SDHCI_WAKE_UP_CONTROL);

	disable_irq_wake(host->irq);

	host->irq_wake_enabled = false;
पूर्ण

पूर्णांक sdhci_suspend_host(काष्ठा sdhci_host *host)
अणु
	sdhci_disable_card_detection(host);

	mmc_retune_समयr_stop(host->mmc);

	अगर (!device_may_wakeup(mmc_dev(host->mmc)) ||
	    !sdhci_enable_irq_wakeups(host)) अणु
		host->ier = 0;
		sdhci_ग_लिखोl(host, 0, SDHCI_INT_ENABLE);
		sdhci_ग_लिखोl(host, 0, SDHCI_SIGNAL_ENABLE);
		मुक्त_irq(host->irq, host);
	पूर्ण

	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(sdhci_suspend_host);

पूर्णांक sdhci_resume_host(काष्ठा sdhci_host *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	पूर्णांक ret = 0;

	अगर (host->flags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA)) अणु
		अगर (host->ops->enable_dma)
			host->ops->enable_dma(host);
	पूर्ण

	अगर ((mmc->pm_flags & MMC_PM_KEEP_POWER) &&
	    (host->quirks2 & SDHCI_QUIRK2_HOST_OFF_CARD_ON)) अणु
		/* Card keeps घातer but host controller करोes not */
		sdhci_init(host, 0);
		host->pwr = 0;
		host->घड़ी = 0;
		mmc->ops->set_ios(mmc, &mmc->ios);
	पूर्ण अन्यथा अणु
		sdhci_init(host, (mmc->pm_flags & MMC_PM_KEEP_POWER));
	पूर्ण

	अगर (host->irq_wake_enabled) अणु
		sdhci_disable_irq_wakeups(host);
	पूर्ण अन्यथा अणु
		ret = request_thपढ़ोed_irq(host->irq, sdhci_irq,
					   sdhci_thपढ़ो_irq, IRQF_SHARED,
					   mmc_hostname(mmc), host);
		अगर (ret)
			वापस ret;
	पूर्ण

	sdhci_enable_card_detection(host);

	वापस ret;
पूर्ण

EXPORT_SYMBOL_GPL(sdhci_resume_host);

पूर्णांक sdhci_runसमय_suspend_host(काष्ठा sdhci_host *host)
अणु
	अचिन्हित दीर्घ flags;

	mmc_retune_समयr_stop(host->mmc);

	spin_lock_irqsave(&host->lock, flags);
	host->ier &= SDHCI_INT_CARD_INT;
	sdhci_ग_लिखोl(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, host->ier, SDHCI_SIGNAL_ENABLE);
	spin_unlock_irqrestore(&host->lock, flags);

	synchronize_hardirq(host->irq);

	spin_lock_irqsave(&host->lock, flags);
	host->runसमय_suspended = true;
	spin_unlock_irqrestore(&host->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_runसमय_suspend_host);

पूर्णांक sdhci_runसमय_resume_host(काष्ठा sdhci_host *host, पूर्णांक soft_reset)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	अचिन्हित दीर्घ flags;
	पूर्णांक host_flags = host->flags;

	अगर (host_flags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA)) अणु
		अगर (host->ops->enable_dma)
			host->ops->enable_dma(host);
	पूर्ण

	sdhci_init(host, soft_reset);

	अगर (mmc->ios.घातer_mode != MMC_POWER_UNDEFINED &&
	    mmc->ios.घातer_mode != MMC_POWER_OFF) अणु
		/* Force घड़ी and घातer re-program */
		host->pwr = 0;
		host->घड़ी = 0;
		mmc->ops->start_संकेत_voltage_चयन(mmc, &mmc->ios);
		mmc->ops->set_ios(mmc, &mmc->ios);

		अगर ((host_flags & SDHCI_PV_ENABLED) &&
		    !(host->quirks2 & SDHCI_QUIRK2_PRESET_VALUE_BROKEN)) अणु
			spin_lock_irqsave(&host->lock, flags);
			sdhci_enable_preset_value(host, true);
			spin_unlock_irqrestore(&host->lock, flags);
		पूर्ण

		अगर ((mmc->caps2 & MMC_CAP2_HS400_ES) &&
		    mmc->ops->hs400_enhanced_strobe)
			mmc->ops->hs400_enhanced_strobe(mmc, &mmc->ios);
	पूर्ण

	spin_lock_irqsave(&host->lock, flags);

	host->runसमय_suspended = false;

	/* Enable SDIO IRQ */
	अगर (sdio_irq_claimed(mmc))
		sdhci_enable_sdio_irq_nolock(host, true);

	/* Enable Card Detection */
	sdhci_enable_card_detection(host);

	spin_unlock_irqrestore(&host->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_runसमय_resume_host);

#पूर्ण_अगर /* CONFIG_PM */

/*****************************************************************************\
 *                                                                           *
 * Command Queue Engine (CQE) helpers                                        *
 *                                                                           *
\*****************************************************************************/

व्योम sdhci_cqe_enable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;
	u8 ctrl;

	spin_lock_irqsave(&host->lock, flags);

	ctrl = sdhci_पढ़ोb(host, SDHCI_HOST_CONTROL);
	ctrl &= ~SDHCI_CTRL_DMA_MASK;
	/*
	 * Host from V4.10 supports ADMA3 DMA type.
	 * ADMA3 perक्रमms पूर्णांकegrated descriptor which is more suitable
	 * क्रम cmd queuing to fetch both command and transfer descriptors.
	 */
	अगर (host->v4_mode && (host->caps1 & SDHCI_CAN_DO_ADMA3))
		ctrl |= SDHCI_CTRL_ADMA3;
	अन्यथा अगर (host->flags & SDHCI_USE_64_BIT_DMA)
		ctrl |= SDHCI_CTRL_ADMA64;
	अन्यथा
		ctrl |= SDHCI_CTRL_ADMA32;
	sdhci_ग_लिखोb(host, ctrl, SDHCI_HOST_CONTROL);

	sdhci_ग_लिखोw(host, SDHCI_MAKE_BLKSZ(host->sdma_boundary, 512),
		     SDHCI_BLOCK_SIZE);

	/* Set maximum समयout */
	sdhci_set_समयout(host, शून्य);

	host->ier = host->cqe_ier;

	sdhci_ग_लिखोl(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, host->ier, SDHCI_SIGNAL_ENABLE);

	host->cqe_on = true;

	pr_debug("%s: sdhci: CQE on, IRQ mask %#x, IRQ status %#x\n",
		 mmc_hostname(mmc), host->ier,
		 sdhci_पढ़ोl(host, SDHCI_INT_STATUS));

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_cqe_enable);

व्योम sdhci_cqe_disable(काष्ठा mmc_host *mmc, bool recovery)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);

	sdhci_set_शेष_irqs(host);

	host->cqe_on = false;

	अगर (recovery) अणु
		sdhci_करो_reset(host, SDHCI_RESET_CMD);
		sdhci_करो_reset(host, SDHCI_RESET_DATA);
	पूर्ण

	pr_debug("%s: sdhci: CQE off, IRQ mask %#x, IRQ status %#x\n",
		 mmc_hostname(mmc), host->ier,
		 sdhci_पढ़ोl(host, SDHCI_INT_STATUS));

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_cqe_disable);

bool sdhci_cqe_irq(काष्ठा sdhci_host *host, u32 पूर्णांकmask, पूर्णांक *cmd_error,
		   पूर्णांक *data_error)
अणु
	u32 mask;

	अगर (!host->cqe_on)
		वापस false;

	अगर (पूर्णांकmask & (SDHCI_INT_INDEX | SDHCI_INT_END_BIT | SDHCI_INT_CRC))
		*cmd_error = -EILSEQ;
	अन्यथा अगर (पूर्णांकmask & SDHCI_INT_TIMEOUT)
		*cmd_error = -ETIMEDOUT;
	अन्यथा
		*cmd_error = 0;

	अगर (पूर्णांकmask & (SDHCI_INT_DATA_END_BIT | SDHCI_INT_DATA_CRC))
		*data_error = -EILSEQ;
	अन्यथा अगर (पूर्णांकmask & SDHCI_INT_DATA_TIMEOUT)
		*data_error = -ETIMEDOUT;
	अन्यथा अगर (पूर्णांकmask & SDHCI_INT_ADMA_ERROR)
		*data_error = -EIO;
	अन्यथा
		*data_error = 0;

	/* Clear selected पूर्णांकerrupts. */
	mask = पूर्णांकmask & host->cqe_ier;
	sdhci_ग_लिखोl(host, mask, SDHCI_INT_STATUS);

	अगर (पूर्णांकmask & SDHCI_INT_BUS_POWER)
		pr_err("%s: Card is consuming too much power!\n",
		       mmc_hostname(host->mmc));

	पूर्णांकmask &= ~(host->cqe_ier | SDHCI_INT_ERROR);
	अगर (पूर्णांकmask) अणु
		sdhci_ग_लिखोl(host, पूर्णांकmask, SDHCI_INT_STATUS);
		pr_err("%s: CQE: Unexpected interrupt 0x%08x.\n",
		       mmc_hostname(host->mmc), पूर्णांकmask);
		sdhci_dumpregs(host);
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_cqe_irq);

/*****************************************************************************\
 *                                                                           *
 * Device allocation/registration                                            *
 *                                                                           *
\*****************************************************************************/

काष्ठा sdhci_host *sdhci_alloc_host(काष्ठा device *dev,
	माप_प्रकार priv_size)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा sdhci_host *host;

	WARN_ON(dev == शून्य);

	mmc = mmc_alloc_host(माप(काष्ठा sdhci_host) + priv_size, dev);
	अगर (!mmc)
		वापस ERR_PTR(-ENOMEM);

	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->mmc_host_ops = sdhci_ops;
	mmc->ops = &host->mmc_host_ops;

	host->flags = SDHCI_SIGNALING_330;

	host->cqe_ier     = SDHCI_CQE_INT_MASK;
	host->cqe_err_ier = SDHCI_CQE_INT_ERR_MASK;

	host->tuning_delay = -1;
	host->tuning_loop_count = MAX_TUNING_LOOP;

	host->sdma_boundary = SDHCI_DEFAULT_BOUNDARY_ARG;

	/*
	 * The DMA table descriptor count is calculated as the maximum
	 * number of segments बार 2, to allow क्रम an alignment
	 * descriptor क्रम each segment, plus 1 क्रम a nop end descriptor.
	 */
	host->adma_table_cnt = SDHCI_MAX_SEGS * 2 + 1;

	वापस host;
पूर्ण

EXPORT_SYMBOL_GPL(sdhci_alloc_host);

अटल पूर्णांक sdhci_set_dma_mask(काष्ठा sdhci_host *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा device *dev = mmc_dev(mmc);
	पूर्णांक ret = -EINVAL;

	अगर (host->quirks2 & SDHCI_QUIRK2_BROKEN_64_BIT_DMA)
		host->flags &= ~SDHCI_USE_64_BIT_DMA;

	/* Try 64-bit mask अगर hardware is capable  of it */
	अगर (host->flags & SDHCI_USE_64_BIT_DMA) अणु
		ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
		अगर (ret) अणु
			pr_warn("%s: Failed to set 64-bit DMA mask.\n",
				mmc_hostname(mmc));
			host->flags &= ~SDHCI_USE_64_BIT_DMA;
		पूर्ण
	पूर्ण

	/* 32-bit mask as शेष & fallback */
	अगर (ret) अणु
		ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
		अगर (ret)
			pr_warn("%s: Failed to set 32-bit DMA mask.\n",
				mmc_hostname(mmc));
	पूर्ण

	वापस ret;
पूर्ण

व्योम __sdhci_पढ़ो_caps(काष्ठा sdhci_host *host, स्थिर u16 *ver,
		       स्थिर u32 *caps, स्थिर u32 *caps1)
अणु
	u16 v;
	u64 dt_caps_mask = 0;
	u64 dt_caps = 0;

	अगर (host->पढ़ो_caps)
		वापस;

	host->पढ़ो_caps = true;

	अगर (debug_quirks)
		host->quirks = debug_quirks;

	अगर (debug_quirks2)
		host->quirks2 = debug_quirks2;

	sdhci_करो_reset(host, SDHCI_RESET_ALL);

	अगर (host->v4_mode)
		sdhci_करो_enable_v4_mode(host);

	device_property_पढ़ो_u64(mmc_dev(host->mmc),
				 "sdhci-caps-mask", &dt_caps_mask);
	device_property_पढ़ो_u64(mmc_dev(host->mmc),
				 "sdhci-caps", &dt_caps);

	v = ver ? *ver : sdhci_पढ़ोw(host, SDHCI_HOST_VERSION);
	host->version = (v & SDHCI_SPEC_VER_MASK) >> SDHCI_SPEC_VER_SHIFT;

	अगर (host->quirks & SDHCI_QUIRK_MISSING_CAPS)
		वापस;

	अगर (caps) अणु
		host->caps = *caps;
	पूर्ण अन्यथा अणु
		host->caps = sdhci_पढ़ोl(host, SDHCI_CAPABILITIES);
		host->caps &= ~lower_32_bits(dt_caps_mask);
		host->caps |= lower_32_bits(dt_caps);
	पूर्ण

	अगर (host->version < SDHCI_SPEC_300)
		वापस;

	अगर (caps1) अणु
		host->caps1 = *caps1;
	पूर्ण अन्यथा अणु
		host->caps1 = sdhci_पढ़ोl(host, SDHCI_CAPABILITIES_1);
		host->caps1 &= ~upper_32_bits(dt_caps_mask);
		host->caps1 |= upper_32_bits(dt_caps);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__sdhci_पढ़ो_caps);

अटल व्योम sdhci_allocate_bounce_buffer(काष्ठा sdhci_host *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	अचिन्हित पूर्णांक max_blocks;
	अचिन्हित पूर्णांक bounce_size;
	पूर्णांक ret;

	/*
	 * Cap the bounce buffer at 64KB. Using a bigger bounce buffer
	 * has diminishing वापसs, this is probably because SD/MMC
	 * cards are usually optimized to handle this size of requests.
	 */
	bounce_size = SZ_64K;
	/*
	 * Adjust करोwnwards to maximum request size अगर this is less
	 * than our segment size, अन्यथा hammer करोwn the maximum
	 * request size to the maximum buffer size.
	 */
	अगर (mmc->max_req_size < bounce_size)
		bounce_size = mmc->max_req_size;
	max_blocks = bounce_size / 512;

	/*
	 * When we just support one segment, we can get signअगरicant
	 * speedups by the help of a bounce buffer to group scattered
	 * पढ़ोs/ग_लिखोs together.
	 */
	host->bounce_buffer = devm_kदो_स्मृति(mmc_dev(mmc),
					   bounce_size,
					   GFP_KERNEL);
	अगर (!host->bounce_buffer) अणु
		pr_err("%s: failed to allocate %u bytes for bounce buffer, falling back to single segments\n",
		       mmc_hostname(mmc),
		       bounce_size);
		/*
		 * Exiting with zero here makes sure we proceed with
		 * mmc->max_segs == 1.
		 */
		वापस;
	पूर्ण

	host->bounce_addr = dma_map_single(mmc_dev(mmc),
					   host->bounce_buffer,
					   bounce_size,
					   DMA_BIसूचीECTIONAL);
	ret = dma_mapping_error(mmc_dev(mmc), host->bounce_addr);
	अगर (ret)
		/* Again fall back to max_segs == 1 */
		वापस;
	host->bounce_buffer_size = bounce_size;

	/* Lie about this since we're bouncing */
	mmc->max_segs = max_blocks;
	mmc->max_seg_size = bounce_size;
	mmc->max_req_size = bounce_size;

	pr_info("%s bounce up to %u segments into one, max segment size %u bytes\n",
		mmc_hostname(mmc), max_blocks, bounce_size);
पूर्ण

अटल अंतरभूत bool sdhci_can_64bit_dma(काष्ठा sdhci_host *host)
अणु
	/*
	 * According to SD Host Controller spec v4.10, bit[27] added from
	 * version 4.10 in Capabilities Register is used as 64-bit System
	 * Address support क्रम V4 mode.
	 */
	अगर (host->version >= SDHCI_SPEC_410 && host->v4_mode)
		वापस host->caps & SDHCI_CAN_64BIT_V4;

	वापस host->caps & SDHCI_CAN_64BIT;
पूर्ण

पूर्णांक sdhci_setup_host(काष्ठा sdhci_host *host)
अणु
	काष्ठा mmc_host *mmc;
	u32 max_current_caps;
	अचिन्हित पूर्णांक ocr_avail;
	अचिन्हित पूर्णांक override_समयout_clk;
	u32 max_clk;
	पूर्णांक ret = 0;
	bool enable_vqmmc = false;

	WARN_ON(host == शून्य);
	अगर (host == शून्य)
		वापस -EINVAL;

	mmc = host->mmc;

	/*
	 * If there are बाह्यal regulators, get them. Note this must be करोne
	 * early beक्रमe resetting the host and पढ़ोing the capabilities so that
	 * the host can take the appropriate action अगर regulators are not
	 * available.
	 */
	अगर (!mmc->supply.vqmmc) अणु
		ret = mmc_regulator_get_supply(mmc);
		अगर (ret)
			वापस ret;
		enable_vqmmc  = true;
	पूर्ण

	DBG("Version:   0x%08x | Present:  0x%08x\n",
	    sdhci_पढ़ोw(host, SDHCI_HOST_VERSION),
	    sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE));
	DBG("Caps:      0x%08x | Caps_1:   0x%08x\n",
	    sdhci_पढ़ोl(host, SDHCI_CAPABILITIES),
	    sdhci_पढ़ोl(host, SDHCI_CAPABILITIES_1));

	sdhci_पढ़ो_caps(host);

	override_समयout_clk = host->समयout_clk;

	अगर (host->version > SDHCI_SPEC_420) अणु
		pr_err("%s: Unknown controller version (%d). You may experience problems.\n",
		       mmc_hostname(mmc), host->version);
	पूर्ण

	अगर (host->quirks & SDHCI_QUIRK_FORCE_DMA)
		host->flags |= SDHCI_USE_SDMA;
	अन्यथा अगर (!(host->caps & SDHCI_CAN_DO_SDMA))
		DBG("Controller doesn't have SDMA capability\n");
	अन्यथा
		host->flags |= SDHCI_USE_SDMA;

	अगर ((host->quirks & SDHCI_QUIRK_BROKEN_DMA) &&
		(host->flags & SDHCI_USE_SDMA)) अणु
		DBG("Disabling DMA as it is marked broken\n");
		host->flags &= ~SDHCI_USE_SDMA;
	पूर्ण

	अगर ((host->version >= SDHCI_SPEC_200) &&
		(host->caps & SDHCI_CAN_DO_ADMA2))
		host->flags |= SDHCI_USE_ADMA;

	अगर ((host->quirks & SDHCI_QUIRK_BROKEN_ADMA) &&
		(host->flags & SDHCI_USE_ADMA)) अणु
		DBG("Disabling ADMA as it is marked broken\n");
		host->flags &= ~SDHCI_USE_ADMA;
	पूर्ण

	अगर (sdhci_can_64bit_dma(host))
		host->flags |= SDHCI_USE_64_BIT_DMA;

	अगर (host->use_बाह्यal_dma) अणु
		ret = sdhci_बाह्यal_dma_init(host);
		अगर (ret == -EPROBE_DEFER)
			जाओ unreg;
		/*
		 * Fall back to use the DMA/PIO पूर्णांकegrated in standard SDHCI
		 * instead of बाह्यal DMA devices.
		 */
		अन्यथा अगर (ret)
			sdhci_चयन_बाह्यal_dma(host, false);
		/* Disable पूर्णांकernal DMA sources */
		अन्यथा
			host->flags &= ~(SDHCI_USE_SDMA | SDHCI_USE_ADMA);
	पूर्ण

	अगर (host->flags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA)) अणु
		अगर (host->ops->set_dma_mask)
			ret = host->ops->set_dma_mask(host);
		अन्यथा
			ret = sdhci_set_dma_mask(host);

		अगर (!ret && host->ops->enable_dma)
			ret = host->ops->enable_dma(host);

		अगर (ret) अणु
			pr_warn("%s: No suitable DMA available - falling back to PIO\n",
				mmc_hostname(mmc));
			host->flags &= ~(SDHCI_USE_SDMA | SDHCI_USE_ADMA);

			ret = 0;
		पूर्ण
	पूर्ण

	/* SDMA करोes not support 64-bit DMA अगर v4 mode not set */
	अगर ((host->flags & SDHCI_USE_64_BIT_DMA) && !host->v4_mode)
		host->flags &= ~SDHCI_USE_SDMA;

	अगर (host->flags & SDHCI_USE_ADMA) अणु
		dma_addr_t dma;
		व्योम *buf;

		अगर (!(host->flags & SDHCI_USE_64_BIT_DMA))
			host->alloc_desc_sz = SDHCI_ADMA2_32_DESC_SZ;
		अन्यथा अगर (!host->alloc_desc_sz)
			host->alloc_desc_sz = SDHCI_ADMA2_64_DESC_SZ(host);

		host->desc_sz = host->alloc_desc_sz;
		host->adma_table_sz = host->adma_table_cnt * host->desc_sz;

		host->align_buffer_sz = SDHCI_MAX_SEGS * SDHCI_ADMA2_ALIGN;
		/*
		 * Use zalloc to zero the reserved high 32-bits of 128-bit
		 * descriptors so that they never need to be written.
		 */
		buf = dma_alloc_coherent(mmc_dev(mmc),
					 host->align_buffer_sz + host->adma_table_sz,
					 &dma, GFP_KERNEL);
		अगर (!buf) अणु
			pr_warn("%s: Unable to allocate ADMA buffers - falling back to standard DMA\n",
				mmc_hostname(mmc));
			host->flags &= ~SDHCI_USE_ADMA;
		पूर्ण अन्यथा अगर ((dma + host->align_buffer_sz) &
			   (SDHCI_ADMA2_DESC_ALIGN - 1)) अणु
			pr_warn("%s: unable to allocate aligned ADMA descriptor\n",
				mmc_hostname(mmc));
			host->flags &= ~SDHCI_USE_ADMA;
			dma_मुक्त_coherent(mmc_dev(mmc), host->align_buffer_sz +
					  host->adma_table_sz, buf, dma);
		पूर्ण अन्यथा अणु
			host->align_buffer = buf;
			host->align_addr = dma;

			host->adma_table = buf + host->align_buffer_sz;
			host->adma_addr = dma + host->align_buffer_sz;
		पूर्ण
	पूर्ण

	/*
	 * If we use DMA, then it's up to the caller to set the DMA
	 * mask, but PIO करोes not need the hw shim so we set a new
	 * mask here in that हाल.
	 */
	अगर (!(host->flags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA))) अणु
		host->dma_mask = DMA_BIT_MASK(64);
		mmc_dev(mmc)->dma_mask = &host->dma_mask;
	पूर्ण

	अगर (host->version >= SDHCI_SPEC_300)
		host->max_clk = FIELD_GET(SDHCI_CLOCK_V3_BASE_MASK, host->caps);
	अन्यथा
		host->max_clk = FIELD_GET(SDHCI_CLOCK_BASE_MASK, host->caps);

	host->max_clk *= 1000000;
	अगर (host->max_clk == 0 || host->quirks &
			SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN) अणु
		अगर (!host->ops->get_max_घड़ी) अणु
			pr_err("%s: Hardware doesn't specify base clock frequency.\n",
			       mmc_hostname(mmc));
			ret = -ENODEV;
			जाओ undma;
		पूर्ण
		host->max_clk = host->ops->get_max_घड़ी(host);
	पूर्ण

	/*
	 * In हाल of Host Controller v3.00, find out whether घड़ी
	 * multiplier is supported.
	 */
	host->clk_mul = FIELD_GET(SDHCI_CLOCK_MUL_MASK, host->caps1);

	/*
	 * In हाल the value in Clock Multiplier is 0, then programmable
	 * घड़ी mode is not supported, otherwise the actual घड़ी
	 * multiplier is one more than the value of Clock Multiplier
	 * in the Capabilities Register.
	 */
	अगर (host->clk_mul)
		host->clk_mul += 1;

	/*
	 * Set host parameters.
	 */
	max_clk = host->max_clk;

	अगर (host->ops->get_min_घड़ी)
		mmc->f_min = host->ops->get_min_घड़ी(host);
	अन्यथा अगर (host->version >= SDHCI_SPEC_300) अणु
		अगर (host->clk_mul)
			max_clk = host->max_clk * host->clk_mul;
		/*
		 * Divided Clock Mode minimum घड़ी rate is always less than
		 * Programmable Clock Mode minimum घड़ी rate.
		 */
		mmc->f_min = host->max_clk / SDHCI_MAX_DIV_SPEC_300;
	पूर्ण अन्यथा
		mmc->f_min = host->max_clk / SDHCI_MAX_DIV_SPEC_200;

	अगर (!mmc->f_max || mmc->f_max > max_clk)
		mmc->f_max = max_clk;

	अगर (!(host->quirks & SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK)) अणु
		host->समयout_clk = FIELD_GET(SDHCI_TIMEOUT_CLK_MASK, host->caps);

		अगर (host->caps & SDHCI_TIMEOUT_CLK_UNIT)
			host->समयout_clk *= 1000;

		अगर (host->समयout_clk == 0) अणु
			अगर (!host->ops->get_समयout_घड़ी) अणु
				pr_err("%s: Hardware doesn't specify timeout clock frequency.\n",
					mmc_hostname(mmc));
				ret = -ENODEV;
				जाओ undma;
			पूर्ण

			host->समयout_clk =
				DIV_ROUND_UP(host->ops->get_समयout_घड़ी(host),
					     1000);
		पूर्ण

		अगर (override_समयout_clk)
			host->समयout_clk = override_समयout_clk;

		mmc->max_busy_समयout = host->ops->get_max_समयout_count ?
			host->ops->get_max_समयout_count(host) : 1 << 27;
		mmc->max_busy_समयout /= host->समयout_clk;
	पूर्ण

	अगर (host->quirks2 & SDHCI_QUIRK2_DISABLE_HW_TIMEOUT &&
	    !host->ops->get_max_समयout_count)
		mmc->max_busy_समयout = 0;

	mmc->caps |= MMC_CAP_SDIO_IRQ | MMC_CAP_CMD23;
	mmc->caps2 |= MMC_CAP2_SDIO_IRQ_NOTHREAD;

	अगर (host->quirks & SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12)
		host->flags |= SDHCI_AUTO_CMD12;

	/*
	 * For v3 mode, Auto-CMD23 stuff only works in ADMA or PIO.
	 * For v4 mode, SDMA may use Auto-CMD23 as well.
	 */
	अगर ((host->version >= SDHCI_SPEC_300) &&
	    ((host->flags & SDHCI_USE_ADMA) ||
	     !(host->flags & SDHCI_USE_SDMA) || host->v4_mode) &&
	     !(host->quirks2 & SDHCI_QUIRK2_ACMD23_BROKEN)) अणु
		host->flags |= SDHCI_AUTO_CMD23;
		DBG("Auto-CMD23 available\n");
	पूर्ण अन्यथा अणु
		DBG("Auto-CMD23 unavailable\n");
	पूर्ण

	/*
	 * A controller may support 8-bit width, but the board itself
	 * might not have the pins brought out.  Boards that support
	 * 8-bit width must set "mmc->caps |= MMC_CAP_8_BIT_DATA;" in
	 * their platक्रमm code beक्रमe calling sdhci_add_host(), and we
	 * won't assume 8-bit width क्रम hosts without that CAP.
	 */
	अगर (!(host->quirks & SDHCI_QUIRK_FORCE_1_BIT_DATA))
		mmc->caps |= MMC_CAP_4_BIT_DATA;

	अगर (host->quirks2 & SDHCI_QUIRK2_HOST_NO_CMD23)
		mmc->caps &= ~MMC_CAP_CMD23;

	अगर (host->caps & SDHCI_CAN_DO_HISPD)
		mmc->caps |= MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED;

	अगर ((host->quirks & SDHCI_QUIRK_BROKEN_CARD_DETECTION) &&
	    mmc_card_is_removable(mmc) &&
	    mmc_gpio_get_cd(mmc) < 0)
		mmc->caps |= MMC_CAP_NEEDS_POLL;

	अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
		अगर (enable_vqmmc) अणु
			ret = regulator_enable(mmc->supply.vqmmc);
			host->sdhci_core_to_disable_vqmmc = !ret;
		पूर्ण

		/* If vqmmc provides no 1.8V संकेतling, then there's no UHS */
		अगर (!regulator_is_supported_voltage(mmc->supply.vqmmc, 1700000,
						    1950000))
			host->caps1 &= ~(SDHCI_SUPPORT_SDR104 |
					 SDHCI_SUPPORT_SDR50 |
					 SDHCI_SUPPORT_DDR50);

		/* In eMMC हाल vqmmc might be a fixed 1.8V regulator */
		अगर (!regulator_is_supported_voltage(mmc->supply.vqmmc, 2700000,
						    3600000))
			host->flags &= ~SDHCI_SIGNALING_330;

		अगर (ret) अणु
			pr_warn("%s: Failed to enable vqmmc regulator: %d\n",
				mmc_hostname(mmc), ret);
			mmc->supply.vqmmc = ERR_PTR(-EINVAL);
		पूर्ण

	पूर्ण

	अगर (host->quirks2 & SDHCI_QUIRK2_NO_1_8_V) अणु
		host->caps1 &= ~(SDHCI_SUPPORT_SDR104 | SDHCI_SUPPORT_SDR50 |
				 SDHCI_SUPPORT_DDR50);
		/*
		 * The SDHCI controller in a SoC might support HS200/HS400
		 * (indicated using mmc-hs200-1_8v/mmc-hs400-1_8v dt property),
		 * but अगर the board is modeled such that the IO lines are not
		 * connected to 1.8v then HS200/HS400 cannot be supported.
		 * Disable HS200/HS400 अगर the board करोes not have 1.8v connected
		 * to the IO lines. (Applicable क्रम other modes in 1.8v)
		 */
		mmc->caps2 &= ~(MMC_CAP2_HSX00_1_8V | MMC_CAP2_HS400_ES);
		mmc->caps &= ~(MMC_CAP_1_8V_DDR | MMC_CAP_UHS);
	पूर्ण

	/* Any UHS-I mode in caps implies SDR12 and SDR25 support. */
	अगर (host->caps1 & (SDHCI_SUPPORT_SDR104 | SDHCI_SUPPORT_SDR50 |
			   SDHCI_SUPPORT_DDR50))
		mmc->caps |= MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25;

	/* SDR104 supports also implies SDR50 support */
	अगर (host->caps1 & SDHCI_SUPPORT_SDR104) अणु
		mmc->caps |= MMC_CAP_UHS_SDR104 | MMC_CAP_UHS_SDR50;
		/* SD3.0: SDR104 is supported so (क्रम eMMC) the caps2
		 * field can be promoted to support HS200.
		 */
		अगर (!(host->quirks2 & SDHCI_QUIRK2_BROKEN_HS200))
			mmc->caps2 |= MMC_CAP2_HS200;
	पूर्ण अन्यथा अगर (host->caps1 & SDHCI_SUPPORT_SDR50) अणु
		mmc->caps |= MMC_CAP_UHS_SDR50;
	पूर्ण

	अगर (host->quirks2 & SDHCI_QUIRK2_CAPS_BIT63_FOR_HS400 &&
	    (host->caps1 & SDHCI_SUPPORT_HS400))
		mmc->caps2 |= MMC_CAP2_HS400;

	अगर ((mmc->caps2 & MMC_CAP2_HSX00_1_2V) &&
	    (IS_ERR(mmc->supply.vqmmc) ||
	     !regulator_is_supported_voltage(mmc->supply.vqmmc, 1100000,
					     1300000)))
		mmc->caps2 &= ~MMC_CAP2_HSX00_1_2V;

	अगर ((host->caps1 & SDHCI_SUPPORT_DDR50) &&
	    !(host->quirks2 & SDHCI_QUIRK2_BROKEN_DDR50))
		mmc->caps |= MMC_CAP_UHS_DDR50;

	/* Does the host need tuning क्रम SDR50? */
	अगर (host->caps1 & SDHCI_USE_SDR50_TUNING)
		host->flags |= SDHCI_SDR50_NEEDS_TUNING;

	/* Driver Type(s) (A, C, D) supported by the host */
	अगर (host->caps1 & SDHCI_DRIVER_TYPE_A)
		mmc->caps |= MMC_CAP_DRIVER_TYPE_A;
	अगर (host->caps1 & SDHCI_DRIVER_TYPE_C)
		mmc->caps |= MMC_CAP_DRIVER_TYPE_C;
	अगर (host->caps1 & SDHCI_DRIVER_TYPE_D)
		mmc->caps |= MMC_CAP_DRIVER_TYPE_D;

	/* Initial value क्रम re-tuning समयr count */
	host->tuning_count = FIELD_GET(SDHCI_RETUNING_TIMER_COUNT_MASK,
				       host->caps1);

	/*
	 * In हाल Re-tuning Timer is not disabled, the actual value of
	 * re-tuning समयr will be 2 ^ (n - 1).
	 */
	अगर (host->tuning_count)
		host->tuning_count = 1 << (host->tuning_count - 1);

	/* Re-tuning mode supported by the Host Controller */
	host->tuning_mode = FIELD_GET(SDHCI_RETUNING_MODE_MASK, host->caps1);

	ocr_avail = 0;

	/*
	 * According to SD Host Controller spec v3.00, अगर the Host System
	 * can afक्रमd more than 150mA, Host Driver should set XPC to 1. Also
	 * the value is meaningful only अगर Voltage Support in the Capabilities
	 * रेजिस्टर is set. The actual current value is 4 बार the रेजिस्टर
	 * value.
	 */
	max_current_caps = sdhci_पढ़ोl(host, SDHCI_MAX_CURRENT);
	अगर (!max_current_caps && !IS_ERR(mmc->supply.vmmc)) अणु
		पूर्णांक curr = regulator_get_current_limit(mmc->supply.vmmc);
		अगर (curr > 0) अणु

			/* convert to SDHCI_MAX_CURRENT क्रमmat */
			curr = curr/1000;  /* convert to mA */
			curr = curr/SDHCI_MAX_CURRENT_MULTIPLIER;

			curr = min_t(u32, curr, SDHCI_MAX_CURRENT_LIMIT);
			max_current_caps =
				FIELD_PREP(SDHCI_MAX_CURRENT_330_MASK, curr) |
				FIELD_PREP(SDHCI_MAX_CURRENT_300_MASK, curr) |
				FIELD_PREP(SDHCI_MAX_CURRENT_180_MASK, curr);
		पूर्ण
	पूर्ण

	अगर (host->caps & SDHCI_CAN_VDD_330) अणु
		ocr_avail |= MMC_VDD_32_33 | MMC_VDD_33_34;

		mmc->max_current_330 = FIELD_GET(SDHCI_MAX_CURRENT_330_MASK,
						 max_current_caps) *
						SDHCI_MAX_CURRENT_MULTIPLIER;
	पूर्ण
	अगर (host->caps & SDHCI_CAN_VDD_300) अणु
		ocr_avail |= MMC_VDD_29_30 | MMC_VDD_30_31;

		mmc->max_current_300 = FIELD_GET(SDHCI_MAX_CURRENT_300_MASK,
						 max_current_caps) *
						SDHCI_MAX_CURRENT_MULTIPLIER;
	पूर्ण
	अगर (host->caps & SDHCI_CAN_VDD_180) अणु
		ocr_avail |= MMC_VDD_165_195;

		mmc->max_current_180 = FIELD_GET(SDHCI_MAX_CURRENT_180_MASK,
						 max_current_caps) *
						SDHCI_MAX_CURRENT_MULTIPLIER;
	पूर्ण

	/* If OCR set by host, use it instead. */
	अगर (host->ocr_mask)
		ocr_avail = host->ocr_mask;

	/* If OCR set by बाह्यal regulators, give it highest prio. */
	अगर (mmc->ocr_avail)
		ocr_avail = mmc->ocr_avail;

	mmc->ocr_avail = ocr_avail;
	mmc->ocr_avail_sdio = ocr_avail;
	अगर (host->ocr_avail_sdio)
		mmc->ocr_avail_sdio &= host->ocr_avail_sdio;
	mmc->ocr_avail_sd = ocr_avail;
	अगर (host->ocr_avail_sd)
		mmc->ocr_avail_sd &= host->ocr_avail_sd;
	अन्यथा /* normal SD controllers करोn't support 1.8V */
		mmc->ocr_avail_sd &= ~MMC_VDD_165_195;
	mmc->ocr_avail_mmc = ocr_avail;
	अगर (host->ocr_avail_mmc)
		mmc->ocr_avail_mmc &= host->ocr_avail_mmc;

	अगर (mmc->ocr_avail == 0) अणु
		pr_err("%s: Hardware doesn't report any support voltages.\n",
		       mmc_hostname(mmc));
		ret = -ENODEV;
		जाओ unreg;
	पूर्ण

	अगर ((mmc->caps & (MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 |
			  MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR104 |
			  MMC_CAP_UHS_DDR50 | MMC_CAP_1_8V_DDR)) ||
	    (mmc->caps2 & (MMC_CAP2_HS200_1_8V_SDR | MMC_CAP2_HS400_1_8V)))
		host->flags |= SDHCI_SIGNALING_180;

	अगर (mmc->caps2 & MMC_CAP2_HSX00_1_2V)
		host->flags |= SDHCI_SIGNALING_120;

	spin_lock_init(&host->lock);

	/*
	 * Maximum number of sectors in one transfer. Limited by SDMA boundary
	 * size (512KiB). Note some tuning modes impose a 4MiB limit, but this
	 * is less anyway.
	 */
	mmc->max_req_size = 524288;

	/*
	 * Maximum number of segments. Depends on अगर the hardware
	 * can करो scatter/gather or not.
	 */
	अगर (host->flags & SDHCI_USE_ADMA) अणु
		mmc->max_segs = SDHCI_MAX_SEGS;
	पूर्ण अन्यथा अगर (host->flags & SDHCI_USE_SDMA) अणु
		mmc->max_segs = 1;
		mmc->max_req_size = min_t(माप_प्रकार, mmc->max_req_size,
					  dma_max_mapping_size(mmc_dev(mmc)));
	पूर्ण अन्यथा अणु /* PIO */
		mmc->max_segs = SDHCI_MAX_SEGS;
	पूर्ण

	/*
	 * Maximum segment size. Could be one segment with the maximum number
	 * of bytes. When करोing hardware scatter/gather, each entry cannot
	 * be larger than 64 KiB though.
	 */
	अगर (host->flags & SDHCI_USE_ADMA) अणु
		अगर (host->quirks & SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC)
			mmc->max_seg_size = 65535;
		अन्यथा
			mmc->max_seg_size = 65536;
	पूर्ण अन्यथा अणु
		mmc->max_seg_size = mmc->max_req_size;
	पूर्ण

	/*
	 * Maximum block size. This varies from controller to controller and
	 * is specअगरied in the capabilities रेजिस्टर.
	 */
	अगर (host->quirks & SDHCI_QUIRK_FORCE_BLK_SZ_2048) अणु
		mmc->max_blk_size = 2;
	पूर्ण अन्यथा अणु
		mmc->max_blk_size = (host->caps & SDHCI_MAX_BLOCK_MASK) >>
				SDHCI_MAX_BLOCK_SHIFT;
		अगर (mmc->max_blk_size >= 3) अणु
			pr_warn("%s: Invalid maximum block size, assuming 512 bytes\n",
				mmc_hostname(mmc));
			mmc->max_blk_size = 0;
		पूर्ण
	पूर्ण

	mmc->max_blk_size = 512 << mmc->max_blk_size;

	/*
	 * Maximum block count.
	 */
	mmc->max_blk_count = (host->quirks & SDHCI_QUIRK_NO_MULTIBLOCK) ? 1 : 65535;

	अगर (mmc->max_segs == 1)
		/* This may alter mmc->*_blk_* parameters */
		sdhci_allocate_bounce_buffer(host);

	वापस 0;

unreg:
	अगर (host->sdhci_core_to_disable_vqmmc)
		regulator_disable(mmc->supply.vqmmc);
undma:
	अगर (host->align_buffer)
		dma_मुक्त_coherent(mmc_dev(mmc), host->align_buffer_sz +
				  host->adma_table_sz, host->align_buffer,
				  host->align_addr);
	host->adma_table = शून्य;
	host->align_buffer = शून्य;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_setup_host);

व्योम sdhci_cleanup_host(काष्ठा sdhci_host *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;

	अगर (host->sdhci_core_to_disable_vqmmc)
		regulator_disable(mmc->supply.vqmmc);

	अगर (host->align_buffer)
		dma_मुक्त_coherent(mmc_dev(mmc), host->align_buffer_sz +
				  host->adma_table_sz, host->align_buffer,
				  host->align_addr);

	अगर (host->use_बाह्यal_dma)
		sdhci_बाह्यal_dma_release(host);

	host->adma_table = शून्य;
	host->align_buffer = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_cleanup_host);

पूर्णांक __sdhci_add_host(काष्ठा sdhci_host *host)
अणु
	अचिन्हित पूर्णांक flags = WQ_UNBOUND | WQ_MEM_RECLAIM | WQ_HIGHPRI;
	काष्ठा mmc_host *mmc = host->mmc;
	पूर्णांक ret;

	अगर ((mmc->caps2 & MMC_CAP2_CQE) &&
	    (host->quirks & SDHCI_QUIRK_BROKEN_CQE)) अणु
		mmc->caps2 &= ~MMC_CAP2_CQE;
		mmc->cqe_ops = शून्य;
	पूर्ण

	host->complete_wq = alloc_workqueue("sdhci", flags, 0);
	अगर (!host->complete_wq)
		वापस -ENOMEM;

	INIT_WORK(&host->complete_work, sdhci_complete_work);

	समयr_setup(&host->समयr, sdhci_समयout_समयr, 0);
	समयr_setup(&host->data_समयr, sdhci_समयout_data_समयr, 0);

	init_रुकोqueue_head(&host->buf_पढ़ोy_पूर्णांक);

	sdhci_init(host, 0);

	ret = request_thपढ़ोed_irq(host->irq, sdhci_irq, sdhci_thपढ़ो_irq,
				   IRQF_SHARED,	mmc_hostname(mmc), host);
	अगर (ret) अणु
		pr_err("%s: Failed to request IRQ %d: %d\n",
		       mmc_hostname(mmc), host->irq, ret);
		जाओ unwq;
	पूर्ण

	ret = sdhci_led_रेजिस्टर(host);
	अगर (ret) अणु
		pr_err("%s: Failed to register LED device: %d\n",
		       mmc_hostname(mmc), ret);
		जाओ unirq;
	पूर्ण

	ret = mmc_add_host(mmc);
	अगर (ret)
		जाओ unled;

	pr_info("%s: SDHCI controller on %s [%s] using %s\n",
		mmc_hostname(mmc), host->hw_name, dev_name(mmc_dev(mmc)),
		host->use_बाह्यal_dma ? "External DMA" :
		(host->flags & SDHCI_USE_ADMA) ?
		(host->flags & SDHCI_USE_64_BIT_DMA) ? "ADMA 64-bit" : "ADMA" :
		(host->flags & SDHCI_USE_SDMA) ? "DMA" : "PIO");

	sdhci_enable_card_detection(host);

	वापस 0;

unled:
	sdhci_led_unरेजिस्टर(host);
unirq:
	sdhci_करो_reset(host, SDHCI_RESET_ALL);
	sdhci_ग_लिखोl(host, 0, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, 0, SDHCI_SIGNAL_ENABLE);
	मुक्त_irq(host->irq, host);
unwq:
	destroy_workqueue(host->complete_wq);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__sdhci_add_host);

पूर्णांक sdhci_add_host(काष्ठा sdhci_host *host)
अणु
	पूर्णांक ret;

	ret = sdhci_setup_host(host);
	अगर (ret)
		वापस ret;

	ret = __sdhci_add_host(host);
	अगर (ret)
		जाओ cleanup;

	वापस 0;

cleanup:
	sdhci_cleanup_host(host);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_add_host);

व्योम sdhci_हटाओ_host(काष्ठा sdhci_host *host, पूर्णांक dead)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	अचिन्हित दीर्घ flags;

	अगर (dead) अणु
		spin_lock_irqsave(&host->lock, flags);

		host->flags |= SDHCI_DEVICE_DEAD;

		अगर (sdhci_has_requests(host)) अणु
			pr_err("%s: Controller removed during "
				" transfer!\n", mmc_hostname(mmc));
			sdhci_error_out_mrqs(host, -ENOMEDIUM);
		पूर्ण

		spin_unlock_irqrestore(&host->lock, flags);
	पूर्ण

	sdhci_disable_card_detection(host);

	mmc_हटाओ_host(mmc);

	sdhci_led_unरेजिस्टर(host);

	अगर (!dead)
		sdhci_करो_reset(host, SDHCI_RESET_ALL);

	sdhci_ग_लिखोl(host, 0, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, 0, SDHCI_SIGNAL_ENABLE);
	मुक्त_irq(host->irq, host);

	del_समयr_sync(&host->समयr);
	del_समयr_sync(&host->data_समयr);

	destroy_workqueue(host->complete_wq);

	अगर (host->sdhci_core_to_disable_vqmmc)
		regulator_disable(mmc->supply.vqmmc);

	अगर (host->align_buffer)
		dma_मुक्त_coherent(mmc_dev(mmc), host->align_buffer_sz +
				  host->adma_table_sz, host->align_buffer,
				  host->align_addr);

	अगर (host->use_बाह्यal_dma)
		sdhci_बाह्यal_dma_release(host);

	host->adma_table = शून्य;
	host->align_buffer = शून्य;
पूर्ण

EXPORT_SYMBOL_GPL(sdhci_हटाओ_host);

व्योम sdhci_मुक्त_host(काष्ठा sdhci_host *host)
अणु
	mmc_मुक्त_host(host->mmc);
पूर्ण

EXPORT_SYMBOL_GPL(sdhci_मुक्त_host);

/*****************************************************************************\
 *                                                                           *
 * Driver init/निकास                                                          *
 *                                                                           *
\*****************************************************************************/

अटल पूर्णांक __init sdhci_drv_init(व्योम)
अणु
	pr_info(DRIVER_NAME
		": Secure Digital Host Controller Interface driver\n");
	pr_info(DRIVER_NAME ": Copyright(c) Pierre Ossman\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास sdhci_drv_निकास(व्योम)
अणु
पूर्ण

module_init(sdhci_drv_init);
module_निकास(sdhci_drv_निकास);

module_param(debug_quirks, uपूर्णांक, 0444);
module_param(debug_quirks2, uपूर्णांक, 0444);

MODULE_AUTHOR("Pierre Ossman <pierre@ossman.eu>");
MODULE_DESCRIPTION("Secure Digital Host Controller Interface core driver");
MODULE_LICENSE("GPL");

MODULE_PARM_DESC(debug_quirks, "Force certain quirks.");
MODULE_PARM_DESC(debug_quirks2, "Force certain other quirks.");
